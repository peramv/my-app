///////////////////////////////////////////////////////////////////////////////
// gxexfmrd.cpp
//
// Copyright (c) 1997-2012 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author: Daniel Jebaraj
//
// Portions Copyright (C) 1995-1998 X Engineering Software Systems Corp
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "grid\gxexman.h"
#include "grid\gxexlog.h"

#include "grid\gxsexpr.h"
#include "grid\gxexhnd.h"
#include "grid\gxexhdr.h"

#include "grid\gxexft.h"

#pragma warning(disable: 4244 4700)

typedef BYTE uint8;




/*----------------------------------------------------------------------------------*/
/*  Routines for managing the state													*/

#define PUSH(fs,x)      fs->stack[((fs)->sp)++] = x
#define POP(fs)         fs->stack[--((fs)->sp)]
#define TOS(fs)         fs->stack[((fs)->sp)-1]
#define REF(fs,x)       fs->nbuf[x]


/*----------------------------------------------------------------------------------*/
/*  Structure for maintaining the state of a formula traversal						*/

typedef struct
	{
		gxExprNode	nbuf[GX_MAX_NODES];
		gxExprPointer	nbuf_ptr;
		gxExprPointer	stack[GX_MAX_NODES];
		int			sp;
		int			error;
	} gxFormulaState;


static void	gx_xls_check_strictness (gxFormulaState *fs, gxExprPointer node, gxKeyword *fnp, int argc);

int	gx_do_attr (formulaStruct* pFormulaStruct, gxFormulaState *fs, int grbit, int w, 
						 uint8 *data);


static gxExprPointer  new_node (gxFormulaState *fs)
{
	fs->nbuf[fs->nbuf_ptr].left             = GX_ENULL;
	fs->nbuf[fs->nbuf_ptr].right            = GX_ENULL;
	fs->nbuf[fs->nbuf_ptr].has_parens       = 0;
	fs->nbuf[fs->nbuf_ptr].number_is_hex    = 0;
	fs->nbuf[fs->nbuf_ptr].arg_is_nonstrict = 0;
	fs->nbuf[fs->nbuf_ptr].is_typesafe      = 0;
	fs->nbuf[fs->nbuf_ptr].is_extern_ref    = 0;

	if (fs->nbuf_ptr >= GX_MAX_NODES)
		{
		fs->error = 1;
		}

	return (fs->nbuf_ptr)++;
}



/*----------------------------------------------------------------------------------*/
/*  Generic ptg stuff																*/

static void		push_number (gxFormulaState *fs, double val)
{
	gxExprPointer		num;

	num = new_node(fs);
	REF(fs,num).node_type = GX_NUMBER_NODE;
	REF(fs,num).value.operand = val;
	REF(fs,num).number_is_hex = 0;
	PUSH(fs,num);
}


static void		push_string (gxFormulaState *fs, char *str)
{
	gxExprPointer		s;

	s = new_node(fs);
	REF(fs,s).node_type = GX_STRING_NODE;
	REF(fs,s).value.string = str;
	PUSH(fs,s);
}


static void	 push_error (gxFormulaState *fs)
{
	gxExprPointer		e;

	e = new_node(fs);
	REF(fs,e).node_type = GX_OPERATOR_NODE;
	REF(fs,e).value.operator_ = GX_ILLEGAL_OP;
	PUSH(fs,e);
}


static gxRange	gx_xls_make_range (int er0, int c0, int er1, int c1)
{
	gxRange	range;

	range.r0 = (er0 & 0x3fff) + 1;
	range.c0 = c0;
	range.abs_r0 = (er0 & 0x8000) ? 0 : 1;
	range.abs_c0 = (er0 & 0x4000) ? 0 : 1;
	range.r1 = (er1 & 0x3fff) + 1;
	range.c1 = c1;
	range.abs_r1 = (er1 & 0x8000) ? 0 : 1;
	range.abs_c1 = (er1 & 0x4000) ? 0 : 1;
	range.cell_only = (er0 == er1) && (c0 == c1);

	return range;
}


static void	gx_push_range (gxFormulaState *fs, int er0, int c0, int er1, int c1)
{
	gxExprPointer	nn;
	gxRange		range;

	range = gx_xls_make_range (er0, c0, er1, c1);
	nn = new_node(fs);
	REF(fs,nn).node_type = (range.cell_only) ? GX_CELL_NODE : GX_RANGE_NODE;
	REF(fs,nn).value.range = range;
	PUSH(fs,nn);
}


static void	gx_push_rel_range (gxFormulaState *fs, int row_base, int col_base, int er0, int c0,
								int er1, int c1)
{
	gxRange		range;
	gxExprPointer	nn;
	int			r0, r1;

	r0 = (er0 & 0x2000) ? (er0 | 0xffffc000) : (er0 & 0x3fff);
	r1 = (er1 & 0x2000) ? (er1 | 0xffffc000) : (er1 & 0x3fff);
	c0 = (c0 & 0x80) ? (c0 | 0xffffff00) : c0;
	c1 = (c1 & 0x80) ? (c1 | 0xffffff00) : c1;

	if (er0 & 0x8000)
		{
		range.r0 = r0 + row_base;
		range.abs_r0 = 0;
		}
	else
		{
		range.r0 = r0 + 1;
		range.abs_r0 = 1;
		}

	if (er0 & 0x4000)
		{
		range.c0 = c0 + col_base;
		range.abs_c0 = 0;
		}
	else
		{
		range.c0 = c0;
		range.abs_c0 = 1;
		}

	if (er1 & 0x8000)
		{
		range.r1 = r1 + row_base;
		range.abs_r1 = 0;
		}
	else
		{
		range.r1 = r1 + 1;
		range.abs_r1 = 1;
		}

	if (er1 & 0x4000)
		{
		range.c1 = c1 + col_base;
		range.abs_c1 = 0;
		}
	else
		{
		range.c1 = c1;
		range.abs_c1 = 1;
		}

	range.cell_only = (er0 == er1) && (c0 == c1);

	nn = new_node(fs);
	REF(fs,nn).node_type = (range.cell_only) ? GX_CELL_NODE : GX_RANGE_NODE;
	REF(fs,nn).value.range = range;
	PUSH(fs,nn);
}


static void	gx_init_fstate (gxFormulaState *fs)
{
	fs->nbuf_ptr = 0;
	fs->sp = 0;
	fs->error = 0;
}

int	gx_xls_get_val16 (void *data)
{
	WORD	 val16;
	
	memcpy(&val16, data, sizeof(WORD));

	/*
	BYTE	*p;

	p = (BYTE*)(&val16);

	*p = *((BYTE*)data);
	*(p+1) = *((BYTE*)data+1);
	*/
	return val16;
}

double gx_xls_get_dbl (void *data)
{
	double	 dbl;
	BYTE*	 p;

	p = (BYTE*)(&dbl);
	*p = *((BYTE*)data);
	*(p+1) = *((BYTE*)data+1);
	*(p+2) = *((BYTE*)data+2);
	*(p+3) = *((BYTE*)data+3);
	*(p+4) = *((BYTE*)data+4);
	*(p+5) = *((BYTE*)data+5);
	*(p+6) = *((BYTE*)data+6);
	*(p+7) = *((BYTE*)data+7);

	return dbl;
}



static void	 gx_do_binary (gxFormulaState *fs, gxOpType oper)
{
	gxExprPointer		left;
	gxExprPointer		right;
	gxExprPointer		op;

	right = POP(fs);
	left  = POP(fs);

	op = new_node(fs);
	REF(fs,op).node_type = GX_OPERATOR_NODE;
	REF(fs,op).value.operator_ = oper;

	REF(fs,op).left  = left;
	REF(fs,op).right = right;

	PUSH(fs,op);
}


static void	gx_do_unary (gxFormulaState *fs, gxOpType oper)
{
	gxExprPointer     right;
	gxExprPointer     op;

	right = POP(fs);
	op = new_node(fs);
	REF(fs,op).node_type = GX_OPERATOR_NODE;
	REF(fs,op).value.operator_ = oper;
	REF(fs,op).right = right;
	PUSH(fs,op);
}


static void	gx_do_binary_func (gxFormulaState *fs, char *fn_name)
{
	gxExprPointer		 arg1;
	gxExprPointer		 arg2;
	gxExprPointer		 op1;
	gxExprPointer		 op2;
	gxExprPointer		 fp;
	gxKeyword			*fnp;

	op2 = POP(fs);
	op1 = POP(fs);
	fnp = _gx_fn_lookup (fn_name);
	assert (fnp != NULL);

	arg1 = new_node(fs);
	arg2 = new_node(fs);
	fp = new_node(fs);

	REF(fs,fp).node_type = GX_FUNCTION_NODE;
	REF(fs,fp).value.fnp = fnp;
	REF(fs,fp).right = arg1;

	REF(fs,arg1).node_type = GX_ARG_NODE;
	REF(fs,arg1).value.arg.back = fp;
	REF(fs,arg1).value.arg.decl_arg_type = fnp->args[0].type;
	REF(fs,arg1).right = arg2;
	REF(fs,arg1).left = op1;

	REF(fs,arg2).node_type = GX_ARG_NODE;
	REF(fs,arg2).value.arg.back = arg1;
	REF(fs,arg1).value.arg.decl_arg_type = fnp->args[1].type;
	REF(fs,arg2).right = GX_ENULL;
	REF(fs,arg2).left = op2;

	PUSH(fs,fp);
}



//support for functions

static int		do_xls_function (gxFormulaState *fs, int cargs, int iftab)
{
	XlsFuncRec	*xfr;
	gxExprPointer	 node;
	gxExprPointer	 nn = GX_ENULL;
	gxExprPointer	 on = GX_ENULL;
	int			 i;

	if (iftab == 1)		return 1;

	xfr = gx_xls_func_lookup (iftab);
	if ((xfr == NULL) || (xfr->nexs_func[0] == '\0'))
		{
		fs->error = ptgFunc;
		return 0;
		}

	if (cargs == -1)
		cargs = xfr->num_xl_args;

    on = GX_ENULL;
	for (i=0; i<cargs; i++)
		{
		assert (fs->sp > 0);
		node = POP(fs);
		nn = new_node(fs);
		REF(fs,nn).node_type = GX_ARG_NODE;
		if (on != GX_ENULL)  REF(fs,on).value.arg.back = nn;
		REF(fs,nn).right = on;
		REF(fs,nn).left = node;
		on = nn;
		}

	gx_xls_check_strictness (fs, nn, xfr->fnp, cargs);

	node = new_node(fs);
	REF(fs,node).node_type = GX_FUNCTION_NODE;
	REF(fs,node).value.fnp = xfr->fnp;
	REF(fs,node).right = nn;
	if (nn != GX_ENULL)  REF(fs,nn).value.arg.back = node;

	PUSH(fs,node);
	return 1;
}



/*----------------------------------------------------------------------------------*/
/*  Do function calls																*/
/*																					*/
/*	NOTE:																			*/
/*  The strictness checker below was copied and tweaked from the version in			*/
/*  expr_parser.c.  The guts of the checker should be factored out and two			*/
/*  separate wrappers added.														*/


#define  PC_REQUIRED	0		/*  Exactly one  */
#define  PC_OPTIONAL	1		/*  Zero or one  */
#define  PC_VARIABLE	2		/*  One or more  */

static void	gx_xls_check_strictness (gxFormulaState *fs, gxExprPointer node, gxKeyword *fnp, int argc)
{
	gxExprPointer	args[GX_MAX_ARGS];
	gxExprPointer	np;
	int			a, z;
	int			i, j;
	int			num_opt_args = 0;
	int			num_var_args = 0;

	if (argc > GX_MAX_ARGS)
		{
		fs->error = GX_PARSE_ERR_TOO_MANY_ARGS;
		return;
		}

	for (i=0, np=node; np!= GX_ENULL; np=REF(fs,np).right, ++i)
		args[i] = np;

	for (i=0; i<fnp->num_args; i++)
		if (fnp->args[i].presence == PC_OPTIONAL)	++num_opt_args;

	a = 0;
	for (i=0; i<fnp->num_args; i++)
		{
		if (i >= argc)  break;
		switch (fnp->args[i].presence)
			{
			case PC_REQUIRED :
				REF(fs,args[a]).arg_is_nonstrict = fnp->args[i].is_nonstrict;
				REF(fs,args[a]).value.arg.decl_arg_type = fnp->args[i].type;
				a++;
				break;

			case PC_OPTIONAL :	/* assumes optional args at end of list */
				REF(fs,args[a]).arg_is_nonstrict = fnp->args[i].is_nonstrict;
				REF(fs,args[a]).value.arg.decl_arg_type = fnp->args[i].type;
				a++;
				break;

			case PC_VARIABLE :	/* only one var arg in formal arg list */
				++num_var_args;
				if (i == (fnp->num_args - 1))	/* var args at end of list */
					{
					while (a < argc)
						{
						REF(fs,args[a]).arg_is_nonstrict = fnp->args[i].is_nonstrict;
						REF(fs,args[a]).value.arg.decl_arg_type = fnp->args[i].type;
						a++;
						}
					}
				else	/* var args at beginning (or middle) of list */
					{
					for (z=argc-1, j=fnp->num_args-1; j!=i; j--, z--)
						{
						REF(fs,args[z]).arg_is_nonstrict = fnp->args[j].is_nonstrict;
						REF(fs,args[z]).value.arg.decl_arg_type = fnp->args[j].type;
						}
					for (; z>=a; z--)
						{
						REF(fs,args[z]).arg_is_nonstrict = fnp->args[i].is_nonstrict;
						REF(fs,args[z]).value.arg.decl_arg_type = fnp->args[i].type;
						}
					i = fnp->num_args;	 /* fake multi-level break */
					}
				break;
			}
		}

	/*
 	* The following assumes that a function does not have both variable
 	* arguments and optional arguments.  This is true for all current
 	* (and most conceivable) functions.
 	*/

	if (argc < (fnp->num_args - num_opt_args))
		fs->error = GX_PARSE_ERR_TOO_FEW_ARGS;
	else if ((argc > fnp->num_args) && !num_var_args)
		fs->error = GX_PARSE_ERR_TOO_MANY_ARGS;
}

/*
static void	gx_process_range_name (gxFormulaState *state, int ilbl)
{
	gxExprPointer	 nn;
	gxRange		 range;
	gxRangeName	*rnp;
	XlsName		*nr;
	gxFormula		*fm;

	int sIndex = pCore->GetSheetContext()->m_nSheetContext;

	nr = &state->name_table[ilbl-1]->u.name;
	
	if (nr->is_local)
	{
		nn = new_node(fs);
		rnp = _gx_range_name_lookup (sIndex, nr->rgch, &range);
		if (rnp != NULL)
			{
				REF(fs,nn).node_type = (range.cell_only) ? GX_NAMED_CELL_NODE : GX_NAMED_RANGE_NODE;
				REF(fs,nn).value.rnp = rnp;
			}
		else
			{
				REF(fs,nn).node_type = GX_OPERATOR_NODE;
				REF(fs,nn).value.op = GX_ILLEGAL_OP;
			}
		PUSH(fs,nn);
	}
	else
		{
			fm = (gxFormula*) nr->fm;
			formula_insert (fs, fm);
		}
}
*/


//end support for functions implementation

static int	gx_do_ptg (formulaStruct* pFormulaStruct, gxFormulaState *fs, BYTE* data)
{
	int		 erow1, col1;
	int		 erow2, col2;
	//int		 ixals;
	//int		 itabFirst, itabLast;
	int		 val;
	//int		 ilbl;
	int		 iftab;
	int		 cargs;
	double	 dval;
	WORD	 cch;
	char	*str;
	int		 grbit;
	int		 w;

	WORD wcol1(0);

/*
if (row==46 && col==1)
printf ("ptg = %02x\n", *data);
*/
	switch (*data)
		{
		case 0:
			return 1;

		case ptgStr :
			cch = *(data+1);
			str = (char*) GX_XSmalloc (cch+1);
			memcpy (str, data+2, cch);
			str[cch] = '\0';
			push_string (fs, str);
			return cch+2;

		case ptgBool :
			val = *(data+1);
			push_number (fs, (double)val);
			return 3;

		case ptgInt :
			val = gx_xls_get_val16 (data+1);
			push_number (fs, (double)val);
			return 3;
		

		case ptgNum :
			dval = gx_xls_get_dbl (data+1);
			push_number (fs, dval);
			return 9;

		case ptgParen :
			REF(fs,TOS(fs)).has_parens = 1;
			return 1;

		case ptgRef :
		case ptgRefV :
			erow1 = gx_xls_get_val16 (data+1);
			wcol1 = gx_xls_get_val16 (data+3);
			wcol1 &= 0x3FFF;
			col1=wcol1;
			gx_push_range (fs, erow1, col1, erow1, col1);
			return 5;

		/*
		// we don't support 3d references
		case ptgRef3d :
		case ptgRef3dV :
			ixals = xls_get_val16 (data+1);
			itabFirst = xls_get_val16 (data+11);
			itabLast = xls_get_val16 (data+13);
			erow1 = xls_get_val16 (data+15);
			col1 = *(data+17);
			if (push_ext_sheet_name (state, fs, ixals, itabFirst, itabLast))
				{
				push_range (fs, erow1, col1, erow1, col1);
				do_binary_func (fs, "XVALUE");
				}
			else
				push_range (fs, erow1, col1, erow1, col1);
			return 18;
		*/
		case ptgArea :
		case ptgAreaV :
		case ptgAreaA :
			erow1 = gx_xls_get_val16 (data+1);
			erow2 = gx_xls_get_val16 (data+3);
			col1 = gx_xls_get_val16 (data+5);
			col2 = gx_xls_get_val16 (data+7);
			gx_push_range (fs, erow1, col1, erow2, col2);
			return 9;
		
		case ptgRefN :
		case ptgRefNV :
			erow1 = gx_xls_get_val16 (data+1);
			col1 = *(data+3);
			gx_push_rel_range (fs, pFormulaStruct->rw+1, pFormulaStruct->col, erow1, col1, erow1, col1);
			return 4;

		case ptgAreaN :
		case ptgAreaNV :
			erow1 = gx_xls_get_val16 (data+1);
			col1 = *(data+5);
			erow2 = gx_xls_get_val16 (data+3);
			col2 = *(data+6);
			gx_push_rel_range (fs, pFormulaStruct->rw+1, pFormulaStruct->col, erow1, col1, erow2, col2);
			return 7;

		case ptgErr :
			push_error (fs);
			return 2;

		case ptgRefErr :
		case ptgRefErrV :
			push_error (fs);
			return 4;

		case ptgAreaErr :
		case ptgAreaErrV :
			push_error (fs);
			return 7;

		case ptgFunc :
		case ptgFuncV :
			iftab = gx_xls_get_val16 (data+1);
			if (!do_xls_function (fs, -1, iftab))
				return 0;
			else
				return 3;

		case ptgFuncVar :
		case ptgFuncVarV :
			cargs = *(data+1) & 0x7f;
			iftab = gx_xls_get_val16 (data+2) & 0x7fff;
			if (!do_xls_function (fs, cargs, iftab))
				return 0;
			else
				return 4;
		
		/*
		case ptgName :
		case ptgNameV :
			ilbl = gx_xls_get_val16 (data+1);
			process_range_name (state, fs, ilbl);
			return 15;

		case ptgNameX :
		case ptgNameXV :
			if (gx_xls_get_val16(data+1) & 0x8000)
				{
				fs->error = *data;
				return 0;
				}
			ilbl = gx_xls_get_val16 (data+11);
			process_range_name (state, fs, ilbl);
			return 15;
		*/
		case ptgAttr :
			grbit = *(data+1);
			w = gx_xls_get_val16 (data+2);
			return 4 + gx_do_attr (pFormulaStruct, fs, grbit, w, data+4);
		
		case ptgUplus :		gx_do_unary (fs, GX_UNARY_PLUS);			return 1;
		case ptgUminus :	gx_do_unary (fs, GX_UNARY_MINUS);			return 1;
		case ptgPercent :	gx_do_unary (fs, GX_PERCENT);				return 1;

		case ptgConcat :	gx_do_binary_func (fs, "STRCAT");			return 1;
		case ptgIsect :		gx_do_binary_func (fs, "INTERSECT");		return 1;

		case ptgRange :		gx_do_binary (fs, GX_JOINRANGE);			return 1;
		
		case ptgAdd :		gx_do_binary (fs, GX_PLUS);					return 1;
		
		case ptgSub :		gx_do_binary (fs, GX_MINUS);				return 1;
		case ptgMul :		gx_do_binary (fs, GX_MULTIPLY);				return 1;
		case ptgDiv :		gx_do_binary (fs, GX_DIVIDE);				return 1;
		case ptgPower :		gx_do_binary (fs, GX_POWER);				return 1;
		case ptgLT :		gx_do_binary (fs, GX_LESS_THAN);			return 1;
		case ptgLE :		gx_do_binary (fs, GX_LT_OR_EQUAL);			return 1;
		case ptgEQ :		gx_do_binary (fs, GX_EQUAL);				return 1;
		case ptgGE :		gx_do_binary (fs, GX_GT_OR_EQUAL);			return 1;
		case ptgGT :		gx_do_binary (fs, GX_GREATER_THAN);			return 1;
		case ptgNE :		gx_do_binary (fs, GX_NOT_EQUAL);			return 1;
		
		default :
			fs->error = *data;
			return 0;
		}
}



static gxFormula	gx_extract_formula (formulaStruct* pFormulaStruct, gxFormulaState *fs)
{
	int				pc;
	gxFormula		fm;
	int				i;
	//char			tag[512];
	//char			mesg[512];

	BYTE* data = pFormulaStruct->pVarParsed;

	gx_init_fstate (fs);
	pc = 0;
	while (pc < pFormulaStruct->cce)
		{
		pc += gx_do_ptg (pFormulaStruct, fs, data+pc);
		if (fs->error)
			{
			//ptg_error (pFormulaStruct, row, col, *(data+pc));
			/* NOTE:  free the formula */
			return fm;
			}
		}

	fm.cons_start   = GX_ENULL;
	fm.depend_start = GX_ENULL;
	fm.comment      = NULL;
	fm.expr_start = POP((fs));
	fm.expr_size  = fs->nbuf_ptr;
	fm.expression = (gxExprNode *) GX_XSmalloc(fs->nbuf_ptr * sizeof(gxExprNode));
	for (i=0; i<fs->nbuf_ptr; i++)
		fm.expression[i] = fs->nbuf[i];

	return fm;
}


void gx_xls_put_formula (formulaStruct* /*pFormulaStruct*/, int row, int col, gxCellProp * /*cprop*/, void *vfm, void *vcv, CGXGridCore* pCore)
{
    gxCell	  *cp;
    //gxCellProp	   cprop1;
    gxCellValue	  *cv = (gxCellValue*) vcv;
    gxFormula	  *fm = (gxFormula*) vfm;
    gxSheetContext  *sc = _gx_get_context_ptr(pCore->GetSheetContext()->m_nSheetContext);

	int sIndex = pCore->GetSheetContext()->m_nSheetContext;

	/*
    if (cprop == NULL)
		cp = get_cell_properties(pCore->GetSheetContext()->m_nSheetContext, row, col, &cprop1);
    else
	*/
	cp = _gx_find_cell(sIndex, row, col);
	_gx_destroy_cell(sIndex, cp);

    if (_gx_references_cells(fm->expression,fm->expr_size) ||
	_gx_calls_functions(fm->expression,fm->expr_size))
	{
		cp = _gx_new_cell (&sc->recalc_list);
		cp->cell_type = GX_FORMULA_CELL;
	}
    else
	{
		cp = _gx_new_cell (&sc->constant_list);
		cp->cell_type = GX_CONSTANT_FORMULA_CELL;
	}
    cp->row = row;
    cp->col = col;
    cp->serial = sc->serial;
    cp->formula = (gxFormula *) GX_XSmalloc (sizeof(gxFormula));
    *(cp->formula) = *fm;
    cp->value_type = GX_VALUE_NONE;
   
	//if (cprop == NULL)
	//	set_cell_properties (cp, &cprop1, PROP_ALL);
    //else
	//	set_cell_properties (cp, cprop, PROP_ALL);

    if ((cp->cell_type == GX_FORMULA_CELL) && (cv != NULL))
	{
		_gx_set_cell_value (cp, cv);
		//if (!state->current_sheet->uncalced)
		//	CELL_SET_FLAG(cp, VISITED | UPDATED);
	}

    if (_gx_insert_cell(sIndex, cp))
	{
		//if (cp->cell_type == GX_CONSTANT_FORMULA_CELL)
			_gx_evaluate_cell (sIndex, cp);
	}
}

// helper to read the calculated value
// we don't use this. This may be used in a future version.
/*
static gxCellValue	gx_extract_cv (formulaStruct* pFormulaStruct, uint8 *val)
{
	gxCellValue	cv;
	XlRecord	rec;
	int			error;
	uint8		data[XLS_MAX_REC_LEN];

	if ((*(val+6) == 0xff) && (*(val+7) == 0xff))
		{
		switch (*val)
			{
			case 0 :
				rec.data = data;
				if (xls_read_record (state, 0, &error, &rec) == XLS_OK)
					{
						cv.type = GX_VALUE_STRING;
						cv.value.string = xls_extract_str (rec.data+2, xls_get_val16(rec.data));
					}
				else
					cv.type = GX_VALUE_NA;
				break;
			case 1 :
				cv.type = GX_VALUE_NUMERIC;
				cv.value.number = (Number) *(val+2);
				break;
			case 2 :
				break;
			}
		}
	else
		{
		cv.type = VALUE_NUMERIC;
		cv.value.number = xls_get_dbl(val);
		}

	return cv;
}

*/

void gx_xls_put_empty_formula (formulaStruct* pFormulaStruct, CGXGridCore* pCore, gxCellValue* vcv)
{
    gxCell	*cp;
    gxCellValue	*cv = (gxCellValue*) vcv;

	int sIndex = pCore->GetSheetContext()->m_nSheetContext;

    cp = _gx_find_cell (sIndex, pFormulaStruct->rw+1, pFormulaStruct->col);
    _gx_destroy_cell(sIndex, cp);
    cp = _gx_insert_empty_cell (sIndex, pFormulaStruct->rw+1, pFormulaStruct->col, NULL);
    if (cv != NULL)
    	_gx_set_cell_value (cp, cv);
}

void gx_rel_named_to_std(gxExprNode *ep)
/*
   Used by copy_formulas() to convert "relative" NAMED_CELL and NAMED_RANGE
   tokens to "standard" RANGE and CELL tokens for purposes of translation.

   also used by make_select_range in cutpaste.c WEW 5/28/90
   there is no longer a "make_select_range"     TAC 7/26/93
*/
  {
  gxRange *rp;
  if (ep->node_type == GX_NAMED_RANGE_NODE)
    {
    rp = &ep->value.rnp->range;
    if (!(rp->abs_r0 && rp->abs_c0 && rp->abs_r1 && rp->abs_c1))
      {
      ep->node_type = GX_RANGE_NODE;
      ep->value.range = *rp;
      }
    }
  else if (ep->node_type == GX_NAMED_CELL_NODE)
    {
    rp = &ep->value.rnp->range;
    if (!(rp->abs_r0 && rp->abs_c0))
      {
      ep->node_type = GX_CELL_NODE;
      ep->value.range = *rp;
      }
    }
  }


void gx_adjust_formula(gxFormula *fm, int dr, int dc)
/* THIS FUNCTION PROBABLY BELONGS SOMEWHERE ELSE */
  {
  register int i;
  register gxExprNode *ep;
  int do_sort = 0;

  ep = fm->expression;
  for (i=0; i<fm->expr_size; ep++, i++)
    {
    gx_rel_named_to_std(ep);	/* TKM 5/6/90 */
    if (ep->node_type == GX_CELL_NODE || ep->node_type == GX_RANGE_NODE)
      {
      if (!ep->value.range.abs_r0) ep->value.range.r0 += dr;
      else do_sort = 1;
      if (!ep->value.range.abs_c0) ep->value.range.c0 += dc;
      else do_sort = 1;
      if (!ep->value.range.abs_r1) ep->value.range.r1 += dr;
      else do_sort = 1;
      if (!ep->value.range.abs_c1) ep->value.range.c1 += dc;
      else do_sort = 1;
      if (!GX_RANGE_CHECK(ep->value.range))
	{
	ep->node_type = GX_OPERATOR_NODE;
	ep->value.operator_ = GX_ILLEGAL_OP;
	}
      else if (do_sort)
			_gx_sort_range(&ep->value.range);
      }
    }
  }

gxFormula	gx_xls_copy_shared_formula (formulaStruct* /*pFormulaStruct*/, int src_r, int src_c, int dst_r, int dst_c, CGXGridCore* pCore)
{
    gxCell	*cp;
    int		 dr;
    int		 dc;
    gxFormula	*fm;

	int sIndex = pCore->GetSheetContext()->m_nSheetContext;
    cp = _gx_find_cell (sIndex, src_r, src_c);
    
	ASSERT((cp!=NULL) && GX_CELL_HAS_FORMULA(cp));

    fm = _gx_formula_dup (cp->formula);
    dr = dst_r - src_r;
    dc = dst_c - src_c;
    gx_adjust_formula (fm, dr, dc);

    return *fm;
}

/*
void gx_xls_put_shared_formula (formulaStruct* pFormulaStruct)
{
    gxCell	*cp;
    gxCellProp	 cprop;
    gxCellValue	 cv;

	int sIndex = pCore->GetSheetContext()->m_nSheetContext;

    cp = gx_find_cell (sIndex, row, col);
    if (cp == NULL)
		gx_xls_put_formula (pFormulaStruct, row, col, NULL, vfm, NULL);
    else
	{
		//get_cell_properties (state->si, row, col, &cprop);
		//get_cell_value (state->si, row, col, &cv);
		destroy_cell (sIndex, cp);
		gx_xls_put_formula (sIndex, row, col, &cprop, vfm, &cv);
	}
}
*/



// helper function to read the formula
void gx_xls_do_formula (formulaStruct* pFormulaStruct, CGXGridCore* pCore)
{
	gxFormulaState	fs;
	gxFormula		fm;
	//gxCellValue		cv;
	//int				ptg_r;
	//int				ptg_c;

	//gxCell	*cp = NULL;

	//BYTE* data = pFormulaStruct->pVarParsed;

	/*
	if ((pFormulaStruct->num != NULL) && (pFormulaStruct->grbit & 0x08))
		{
			ptg_r = gx_xls_get_val16 (data+1) + 1;
			ptg_c = gx_xls_get_val16 (data+3);
		
			if ((ptg_r == pFormulaStruct->rw) && (ptg_c == pFormulaStruct->col))
				{
					gx_xls_put_empty_formula (pFormulaStruct, pCore, &cv);
					return;
				}
				else
				{
					int sIndex = pCore->GetSheetContext()->m_nSheetContext;
					cp = _gx_find_cell (sIndex, ptg_r, ptg_c);
					
					if(cp && cp->formula)
						fm = gx_xls_copy_shared_formula (pFormulaStruct, ptg_r, ptg_c, pFormulaStruct->rw, pFormulaStruct->col, pCore);
					else
					{
						gx_xls_put_empty_formula (pFormulaStruct, pCore, &cv);
						return;
					}
					fs.error = 0;
				}
		}
	else*/

			fm = gx_extract_formula (pFormulaStruct, &fs);

	
	if (fs.error)
		return;
	/*
	//we ignore CV (the calculated value). This may be changed in a future version
	else if (val != NULL)
		{
			cv = extract_cv (pFormulaStruct, val);
			gx_xls_put_formula (pFormulaStruct, row, col, &state->cell_props[ixfe], &fm, &cv, pCore);
		}
	else
	*/	

	gx_xls_put_formula (pFormulaStruct, pFormulaStruct->rw+1, pFormulaStruct->col, NULL, &fm, NULL, pCore);
}

void push_conditional (gxFormulaState *fs);

int	gx_do_attr (formulaStruct* pFormulaStruct, gxFormulaState *fs, int grbit, int w, 
						 uint8 *data)
{
	int		pc = 0;

	if (grbit & 0x02)			/*  If */
		{
		while (pc < w)
			{
			pc += gx_do_ptg (pFormulaStruct, fs, data+pc);
			if (fs->error)
				{
					//ptg_error (state, row, col, *(data+pc));
					return 0;
				}
			}
		w = pc + gx_xls_get_val16 (data+pc-2);
		while (pc < w)
			{
				pc += gx_do_ptg (pFormulaStruct, fs, data+pc);
				if (fs->error)
				{
					//ptg_error (state, row, col, *(data+pc));
					return 0;
				}
			}
			push_conditional (fs);
			return pc;
		}
	else if (grbit & 0x04)		/* Choose */
		{
			return 2*(w+1);
		}
	else if (grbit & 0x08)		/* Goto */
		{
			return 0;
		}
	else if (grbit & 0x10)		/* Sum */
		{
			do_xls_function (fs, 1, gxxlfSum);
			return 0;
		}
	else if (grbit & 0x20)
		{
		fs->error = ptgAttr;
		return 0;
		}

	return 0;
}

/*----------------------------------------------------------------------------------*/
/*  Handle ptgAttr																	*/

void push_conditional (gxFormulaState *fs)
{
	gxExprPointer		f_expr;
	gxExprPointer		t_expr;
	gxExprPointer		c_expr;
	gxExprPointer		cn;
	gxExprPointer		en;

	f_expr = POP(fs);
	t_expr = POP(fs);
	c_expr = POP(fs);

	cn = new_node(fs);
	en = new_node(fs);

	REF(fs,cn).node_type      = GX_OPERATOR_NODE;
	REF(fs,cn).value.operator_ = GX_CONDITIONAL;
	REF(fs,cn).has_parens     = 1;
	REF(fs,cn).left           = c_expr;
	REF(fs,cn).right          = en;

	REF(fs,en).node_type   = GX_EXTENSION_NODE;
	REF(fs,en).value.eback = cn;
	REF(fs,en).left        = t_expr;
	REF(fs,en).right       = f_expr;

	PUSH(fs,cn);
}
