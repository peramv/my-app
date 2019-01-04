///////////////////////////////////////////////////////////////////////////////
// gxexfmwr.cpp
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

#pragma warning(disable: 4244)

typedef BYTE uint8;
typedef WORD uint16;


// declarations

static uint8* gx_trans_to_ptg (formulaStruct* pFormulaStruct, gxExprNode *expr, gxExprPointer node, uint8 *bufp,
							   gxCell *cp);




extern XlsFuncRec func_table[];


typedef struct
	{
	uint16	 grbit;
	uint8	 cch;
	uint16	 cce;
	char	*rgch;
	uint8	*rgce;
	int		 is_local;
	void	*fm;
	} XlsName;


int	gx_xls_get_xlf_arg_count (int index)
{
	return func_table[index].num_xl_args;
}


void	gx_xls_set_dbl (void *addr, double dbl)
{
	uint8	*p;

	p = (uint8*)(&dbl);
	*((uint8*)addr+0) = *(p+0);
	*((uint8*)addr+1) = *(p+1);
	*((uint8*)addr+2) = *(p+2);
	*((uint8*)addr+3) = *(p+3);
	*((uint8*)addr+4) = *(p+4);
	*((uint8*)addr+5) = *(p+5);
	*((uint8*)addr+6) = *(p+6);
	*((uint8*)addr+7) = *(p+7);
}


void gx_xls_set_val16 (void *addr, uint16 val16)
{
	uint8	*p;

	p = (uint8*)(&val16);
	*((uint8*)addr) = *p;
	*((uint8*)addr+1) = *(p+1);
}


static uint16 gx_make_ptg_grbitRw1 (gxRange *range)
{
	uint16	rw = 0;

	if (!range->abs_r1)	rw |= 0x8000;
	if (!range->abs_c1)	rw |= 0x4000;
	rw |= (range->r1 - 1) & 0x3fff;

	return rw;
}


/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*  Writing XLS formulas															*/


/*----------------------------------------------------------------------------------*/
/*  Convert the current value of a formula into an 8-byte record.					*/

char* gx_xls_make_formula_val (formulaStruct* /*pFormulaStruct*/, gxCell *cp, uint8* buf)
{
	int			i;
	static char	cbuf[10];

	for (i=0; i<6; i++)
		buf[i] = 0;
	buf[6] = 0xff;
	buf[7] = 0xff;

	switch (cp->value_type)
		{
		case GX_VALUE_NA :
			buf[0] = 2;
			buf[2] = 42;
			return NULL;

		case GX_VALUE_ERROR :
			buf[0] = 2;
			buf[2] = 15;
			return NULL;

		case GX_VALUE_SHORT_STRING :
		case GX_VALUE_STRING :
			return NULL;
		case GX_VALUE_NUMERIC :
			gx_xls_set_dbl (buf, cp->value.number);
			return NULL;

		case GX_VALUE_NONE :
			return NULL;
		}
	
	return NULL;
}


/*----------------------------------------------------------------------------------*/
/*  Formula writing utilities														*/

static uint16	gx_make_ptg_grbitRw0 (gxRange *range)
{
	uint16	rw = 0;

	if (!range->abs_r0)	
		rw |= 0x8000;
	
	if (!range->abs_c0)
		rw |= 0x4000;
	
	rw |= (range->r0 - 1) & 0x3fff;

	return rw;
}

//
static WORD	gx_make_ptg_grbitRwgx0 (gxRange *range)
{
	WORD	rw = 0;

	rw = (WORD) range->r0 - 1;

	return rw;
}

static uint16	gx_make_ptg_grbitRwgx1 (gxRange *range)
{
	uint16	rw = 0;

	if (!range->abs_r0)	
		rw |= 0x8000;
	
	if (!range->abs_c0)
		rw |= 0x4000;
	
	rw |= (range->c0) & 0x3fff;

	return rw;
}

static uint16	gx_make_ptg_grbitRwgx2 (gxRange *range)
{
	uint16	rw = 0;

	rw |= (range->r1) -1;

	return rw;
}


static uint16	gx_make_ptg_grbitRwgx3 (gxRange *range)
{
	uint16	rw = 0;

	if (!range->abs_r0)	
		rw |= 0x8000;
	
	if (!range->abs_c0)
		rw |= 0x4000;
	
	rw |= (range->c1) & 0x3fff;

	return rw;
}

//

static uint8 * gx_write_ref (uint8 *bufp, gxRange *range, uint8 cell_only_ref)
{

#ifdef _DEBUG 
	BYTE* p = bufp;
#endif

	if (range->cell_only)
		*bufp++ = cell_only_ref;
	else
		*bufp++ = ptgArea;

	if (range->cell_only)
	{
		gx_xls_set_val16 (bufp, gx_make_ptg_grbitRwgx0(range));
		bufp += 2;

		
		gx_xls_set_val16 (bufp, gx_make_ptg_grbitRwgx1(range));
		bufp += 2;

		if (!range->cell_only)
			{
				gx_xls_set_val16 (bufp, gx_make_ptg_grbitRw1(range));
				bufp += 2;
			}
	}
	else
	{
		gx_xls_set_val16 (bufp, gx_make_ptg_grbitRwgx0(range));
		bufp += 2;

		
		gx_xls_set_val16 (bufp, gx_make_ptg_grbitRwgx2(range));
		bufp += 2;

		
		gx_xls_set_val16 (bufp, gx_make_ptg_grbitRwgx1(range));
		bufp += 2;

		
		gx_xls_set_val16 (bufp, gx_make_ptg_grbitRwgx3(range));
		bufp += 2;
	}

	GXEXDUMP(p, 10);

	return bufp;
}


static uint8* gx_write_int (uint8 *bufp, uint16 val)
{
	*bufp++ = ptgInt;
	gx_xls_set_val16 (bufp, val);
	return bufp+2;
}


/*----------------------------------------------------------------------------------*/
/*  Given a NeXS operator, translate it to the equivalent Excel operator or			*/
/*  function.																		*/

static int	gx_operator_trans[] =
	{
		ptgAdd,			/* PLUS */
		ptgSub,			/* MINUS */
		ptgUplus,		/* UNARY_PLUS */
		ptgUminus,		/* UNARY_MINUS */
		ptgMul,			/* MULTIPLY */
		ptgDiv,			/* DIVIDE */
		ptgPower,		/* POWER */
		xlfMod,			/* MODULUS */
		xlfAnd,			/* LOGICAL_AND */
		xlfOr,			/* LOGICAL_OR */
		xlfNot,			/* LOGICAL_NOT */
		-1,				/* BOOLEAN_AND */
		-1,				/* BOOLEAN_OR */
		-1,				/* BOOLEAN_XOR */
		-1,				/* BOOLEAN_NOT */
		-1,				/* SHIFT_LEFT */
		-1,				/* SHIFT_RIGHT */
		ptgEQ,			/* EQUAL */
		ptgNE,			/* NOT_EQUAL */
		ptgLT,			/* LESS_THAN */
		ptgGT,			/* GREATER_THAN */
		ptgLE,			/* LT_OR_EQUAL */
		ptgGE,			/* GT_OR_EQUAL */
		-1,				/* CONDITIONAL */
		ptgRange,		/* JOINRANGE */
		ptgPercent,		/* PERCENT */
		-1				/* ILLEGAL_OP */
	};


/*----------------------------------------------------------------------------------*/
/*  Given a NeXS operator, generate the equivalent Excel function call				*/

#pragma warning(push)
#pragma warning(disable: 4244)

static uint8 * gx_xl_func_for_op (formulaStruct* /*pFormulaStruct*/, gxExprNode* expr, gxExprPointer node, uint8 *bufp,
								 int argc)
{
#ifdef _WIN64
	INT_PTR op;
#else
	uint16	op;
#endif // _WIN64
	//int		num_args;

	op = gx_operator_trans[expr[node].value.operator_];
	if (gx_xls_get_xlf_arg_count(op) < 0)
		{
			*bufp++ = ptgFuncVarV;
			*bufp++ = argc;
		}
	else
		*bufp++ = ptgFuncV;
	
	gx_xls_set_val16 (bufp, op);
	bufp += 2;

	return bufp;
}

#pragma warning(pop) // 4244


/*----------------------------------------------------------------------------------*/
/*  Write a conditional expression													*/

static uint8	if_terminator[] = { 0x19, 0x08, 0x03, 0x00, 0x42, 0x03, 0x01, 0x00 };


static uint8* gx_write_conditional (formulaStruct* pFormulaStruct, gxExprNode *expr, gxExprPointer node, uint8 *bufp,
									gxCell *cp)
{
	uint8			*false_patch_addr;
	uint8			*true_patch_addr;
	gxExprPointer		 en;

	bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[node].left, bufp, cp);
	*bufp++ = ptgAttr;
	*bufp++ = 2;
	false_patch_addr = bufp;
	bufp += 2;

	en = expr[node].right;
	bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[en].left, bufp, cp);
	*bufp++ = ptgAttr;
	*bufp++ = 8;
	true_patch_addr = bufp;
	bufp += 2;
	gx_xls_set_val16 (false_patch_addr, (uint16)(bufp - (false_patch_addr + 2)));

	bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[en].right, bufp, cp);
	memcpy (bufp, if_terminator, 8);
	bufp += 8;
	gx_xls_set_val16 (true_patch_addr, (uint16)(bufp - (true_patch_addr + 2) - 1));

	return bufp;
}


/*----------------------------------------------------------------------------------*/
/*  Recursively translate a NeXS operator subtree into a XL ptg sequence			*/

#pragma warning (push)
#pragma warning (disable: 4244)
static uint8* gx_op_to_ptg (formulaStruct* pFormulaStruct, gxExprNode *expr, gxExprPointer node, uint8 *bufp, gxCell *cp)
{
	switch (expr[node].value.operator_)
		{
		case GX_PLUS :
		case GX_MINUS :
		case GX_MULTIPLY :
		case GX_DIVIDE :
		case GX_POWER :
		case GX_EQUAL :
		case GX_NOT_EQUAL :
		case GX_LESS_THAN :
		case GX_GREATER_THAN :
		case GX_LT_OR_EQUAL :
		case GX_GT_OR_EQUAL :
		case GX_JOINRANGE :
			bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[node].left, bufp, cp);
			bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[node].right, bufp, cp);
			*bufp++ = gx_operator_trans[expr[node].value.operator_];
			break;

		case GX_UNARY_PLUS :
		case GX_UNARY_MINUS :
		case GX_PERCENT :
			bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[node].right, bufp, cp);
			*bufp++ = gx_operator_trans[expr[node].value.operator_];
			break;

		case GX_MODULUS :
		case GX_LOGICAL_AND :
		case GX_LOGICAL_OR :
			bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[node].left, bufp, cp);
			bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[node].right, bufp, cp);
			bufp = gx_xl_func_for_op (pFormulaStruct, expr, node, bufp, 2);
			break;

		case GX_LOGICAL_NOT :
			bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[node].right, bufp, cp);
			bufp = gx_xl_func_for_op (pFormulaStruct, expr, node, bufp, 1);
			break;

		case GX_CONDITIONAL :
			bufp = gx_write_conditional (pFormulaStruct, expr, node, bufp, cp);
			break;

		case GX_BOOLEAN_AND :
		case GX_BOOLEAN_OR :
		case GX_BOOLEAN_XOR :
		case GX_BOOLEAN_NOT :
		case GX_SHIFT_LEFT :
		case GX_SHIFT_RIGHT :
			//xs_error (state->si, GX_MINOR_ERROR, GX_ERROR_BOX, gx_rc_to_text(cp->row,cp->col),
			//		  GX_XLS_NO_EQUIV_OP, NULL);
			break;

		case GX_ILLEGAL_OP :
			break;
		}

	return bufp;
}


/*----------------------------------------------------------------------------------*/
/*  Generate a function call														*/

static uint8* gx_generate_func_call (formulaStruct* pFormulaStruct, gxExprNode *expr, gxExprPointer node, uint8 *bufp,
									 gxCell *cp)
{
	gxExprPointer	 np;
	int			 acount;
	XlsFuncRec	*xlfp;

	acount = 0;
	for (np = expr[node].right; np != GX_ENULL; np = expr[np].right)
		{
			bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[np].left, bufp, cp);
			acount++;
		}

	

	//xlfp = gx_xls_func_lookup (expr[node].value.fnp->name);
	xlfp = gx_xls_func_lookup (expr[node].value.fnp->xlf);
	//xlfp = gx_xls_func_lookup (expr[node].value.fnp->xlf);
	
	if ((xlfp == NULL) || ((xlfp->num_xl_args >= 0) && (acount != xlfp->num_xl_args)))
		{
			//gx_xs_error (state->si, MINOR_ERROR, ERROR_BOX, rc_to_text(cp->row,cp->col),
			//	  XLS_NO_EQUIV_FUNC, NULL);
		}
	else
		{
			if (xlfp->num_xl_args >= 0)
				*bufp++ = ptgFuncV;
			else
			{
				*bufp++ = ptgFuncVarV;
				*bufp++ = (uint8) acount;
			}

			//gx_xls_set_val16 (bufp, expr[node].value.fnp->type);
			gx_xls_set_val16 (bufp, expr[node].value.fnp->xlf);
			bufp += 2;
		}

	return bufp;
}
#pragma warning(pop) // 4244

/*----------------------------------------------------------------------------------*/
/*  Generate an offset reference (from a RELATIVE_NODE) by calling Excel's offset()	*/

static uint8* gx_generate_offset_ref (formulaStruct* pFormulaStruct, gxExprNode *expr, gxExprPointer node, uint8 *bufp,
									gxCell *cp)
{
	gxRange	rng;

	rng.r0 = cp->row;
	rng.c0 = cp->col;
	rng.abs_r0 = 0;
	rng.abs_c0 = 0;
	rng.cell_only = 1;
	bufp = gx_write_ref (bufp, &rng, ptgRef);

	if (expr[node].value.rel.r_expr != GX_ENULL)
		bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[node].value.rel.r_expr, bufp, cp);
	else
		bufp = gx_write_int (bufp, 0);

	if (expr[node].value.rel.c_expr != GX_ENULL)
		bufp = gx_trans_to_ptg (pFormulaStruct, expr, expr[node].value.rel.c_expr, bufp, cp);
	else
		bufp = gx_write_int (bufp, 0);

	*bufp++ = ptgFuncVarV;
	*bufp++ = 3;
	
	gx_xls_set_val16 (bufp, xlfOffset);
	
	bufp += 2;

	return bufp;
}


/*----------------------------------------------------------------------------------*/
/*  Generate a reference to a named range or cell									*/

/*
static uint16	gx_find_name_index (formulaStruct* pFormulaStruct, char *name)
{
	int		i;

	for (i=0; i < state->name_count; i++)
		{
			if (strcmp(name, state->name_table[i]->u.name.rgch) == 0)
				return i+1;
		}

	return 0;
}


static uint8* gx_generate_namex (formulaStruct* pFormulaStruct, gxExprNode *expr, gxExprPointer node, uint8 *bufp)
{
	int		i;

	*bufp++ = ptgNameX;
	*bufp++ = 0xff;
	*bufp++ = 0xff;
	for (i=0; i<22; i++)
		bufp[i] = 0;
	bufp += 8;
	gx_xls_set_val16 (bufp, gx_find_name_index(pFormulaStruct, expr[node].value.rnp->name));
	bufp += 2;
	bufp += 12;

	return bufp;
}


static uint8 * gx_generate_name (formulaStruct* pFormulaStruct, gxExprNode *expr, gxExprPointer node, uint8 *bufp)
{
	int		i;

	*bufp++ = (expr[node].value.rnp->range.cell_only) ? ptgNameV : ptgName;
	gx_xls_set_val16 (bufp, gx_find_name_index(state, expr[node].value.rnp->name));
	
	bufp += 2;
	
	for (i=0; i<12; i++)
		*bufp++ = 0;

	return bufp;
}

*/
/*----------------------------------------------------------------------------------*/
/*  Build an XLS representation of a NeXS formula									*/

static uint8* gx_trans_to_ptg (formulaStruct* pFormulaStruct, gxExprNode *expr, gxExprPointer node, uint8 *bufp,
							   gxCell *cp)
{
	int			 slen;
	int			 wlen;

	switch (expr[node].node_type)
		{
		case GX_OPERATOR_NODE :
			bufp = gx_op_to_ptg (pFormulaStruct, expr, node, bufp, cp);
			break;

		case GX_NUMBER_NODE :
			*bufp++ = ptgNum;
			gx_xls_set_dbl (bufp, expr[node].value.operand);
			bufp += sizeof(expr[node].value.operand);
			break;

		case GX_STRING_NODE :
			slen = (int)strlen (expr[node].value.string);
			wlen = (slen < 256) ? slen : 255;
			*bufp++ = ptgStr;
			*bufp++ = (uint8) wlen;
			memcpy (bufp, expr[node].value.string, wlen);
			bufp += wlen;
			break;

		case GX_CELL_NODE :
		case GX_RANGE_NODE :
			bufp = gx_write_ref (bufp, &expr[node].value.range, ptgRefV);
			break;

		case GX_FUNCTION_NODE :
			bufp = gx_generate_func_call (pFormulaStruct, expr, node, bufp, cp);
			break;
		/*
		case GX_NAMED_CELL_NODE :
		case GX_NAMED_RANGE_NODE :
			bufp = gx_generate_name (pFormulaStruct, expr, node, bufp);
			break;
		*/
		case GX_RELATIVE_NODE :
			bufp = gx_generate_offset_ref (pFormulaStruct, expr, node, bufp, cp);
			break;

		case GX_NAME_NODE :
			/* Filtered out in parsing/evaluation */
		case GX_ARG_NODE :
		case GX_EXTENSION_NODE :
			/* Consumed by function nodes and condition operators, respectively */
			ASSERT (0);
			break;
		}

	if (expr[node].has_parens)
		*bufp++ = ptgParen;

	return bufp;
}


int		gx_xls_build_formula (formulaStruct* pFormulaStruct, gxCell *cp, uint8 *fbuf)
{
	uint8	*bufp = NULL;
	
	if(cp->formula == NULL)
		return 0;

	bufp = gx_trans_to_ptg (pFormulaStruct, cp->formula->expression, cp->formula->expr_start, fbuf, cp);
	return (int)(bufp - fbuf);
}


/*----------------------------------------------------------------------------------*/
/*  Set the definition in an XlsName given the range that it should refer to		*/

void	gx_xls_name_from_range (formulaStruct* /*pFormulaStruct*/, XlsName *xlname, gxRange *rngp)
{
	int		i;

	xlname->rgce = (uint8*) GX_XSmalloc (21*sizeof(uint8));

	if (rngp->cell_only)
		{
			xlname->cce = 18;
			xlname->rgce[0] = ptgRef3d;
		}
	else
		{
			xlname->cce = 21;
			xlname->rgce[0] = ptgArea3d;
		}

	xlname->rgce[1] = 0xff;
	xlname->rgce[2] = 0xff;
	
	for (i=0; i<12; i++)
		xlname->rgce[3+i] = 0;

	i = 15;
	gx_xls_set_val16 (xlname->rgce+i, gx_make_ptg_grbitRw0(rngp));
	i+=2;
	
	if (!rngp->cell_only)
		{
			gx_xls_set_val16 (xlname->rgce+i, gx_make_ptg_grbitRw1(rngp));
			i+=2;
		}
	
	xlname->rgce[i++] = (unsigned char) rngp->c0 & 0xff;
	
	if (!rngp->cell_only)
		xlname->rgce[i++] = (unsigned char) rngp->c1 & 0xff;
}
