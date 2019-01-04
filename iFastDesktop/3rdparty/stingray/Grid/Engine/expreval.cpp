///////////////////////////////////////////////////////////////////////////////
// expreval.cpp: Routines for expression evaluation
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
// Author: Stefan Hoenig
//
// Portions Copyright (C) 1995-1998 X Engineering Software Systems Corp
//

#define _OG_EXPORT_IMPL
#define _RW_IMPL

#include "stdafx.h"
#include "grid\gxsinc.h"
#include "grid\gxproc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#pragma warning (push)
#pragma warning (disable: 4701) // Potentially uninitialized variable used
#pragma warning (disable: 4702) // Unreachable code

#define MAX_WM  GX_MAX_WM  /* maximum concurrent working memory buffers */

struct GX_ALLOC_MEMOBJ;

void _gxFreeAllMemObj();

//struct GX_ALLOC_MEMOBJ
//{
//	void* pMemObj;
//	GX_ALLOC_MEMOBJ* pNextMemObj;
//};

struct GX_ENGINE_MEMOBJ_STATE: public CGXNoTrackObject
{
	CMapPtrToPtr ptrList;

	GX_ENGINE_MEMOBJ_STATE();
	virtual ~GX_ENGINE_MEMOBJ_STATE();
};                               

// GX_PROCESS_LOCAL(GX_ENGINE_MEMOBJ_STATE, _gxMemObjState)

GX_ENGINE_MEMOBJ_STATE* GXGetMemObjState()
{
	CGXAppData* pAppData = GXGetAppData();
	if (pAppData->m_pMemObjState == NULL)
		pAppData->m_pMemObjState = new GX_ENGINE_MEMOBJ_STATE;

	return (GX_ENGINE_MEMOBJ_STATE*) pAppData->m_pMemObjState;
}

GX_ENGINE_MEMOBJ_STATE::GX_ENGINE_MEMOBJ_STATE()
{
}

GX_ENGINE_MEMOBJ_STATE::~GX_ENGINE_MEMOBJ_STATE()
{
	_gxFreeAllMemObj();
}

void __cdecl _gxFreeObject(void* pObj)
{
	void* pVoid = NULL;
	if (GXGetMemObjState()->ptrList.Lookup(pObj, pVoid))
	{
		GXGetMemObjState()->ptrList.RemoveKey(pObj);
	}
	if (pObj)
	{
		GX_FREE_CATCH(pObj, _T("pObj"));
	}
} 

void _gxFreeAllMemObj()
{
#ifdef _DEBUG
	int n = 0;
#endif
	void* pObj = NULL;
	void* pOtherObj = NULL;

	POSITION pos = GXGetMemObjState()->ptrList.GetStartPosition();

	while (pos)
	{
		GXGetMemObjState()->ptrList.GetNextAssoc(pos, pObj, pOtherObj);

		if (pObj)
		{
			GX_FREE_CATCH(pObj, _T("pObj"));
			GXGetMemObjState()->ptrList.RemoveKey(pObj);
			
#ifdef _DEBUG
			n++;
#endif
		}
	}
	//TRACE("%d Engine Objects deleted.\n", n);
}

#if _TEST_

#define _gxAddMemObj(p) _gxAddMemObj2(__LINE__, p)
void _gxAddMemObj2(int line, void* pObj)
{
	TRACE("%d: %lx, %s\n", line, pObj, pObj);

#else

void* _gxAddMemObj(void* pObj)
{

#endif
	void *pVoid = NULL;
	
	if (GXGetMemObjState()->ptrList.Lookup(pObj, pVoid))
		return pObj;
	
	GXGetMemObjState()->ptrList.SetAt(pObj, pObj);

	return pObj;
}

/////////////////////////////////////////////////////////////////////

GX_EVAL_STATE::GX_EVAL_STATE()
{
	expr_si = 0;
	xs_fn_name = 0;
	expr_sbuf = 0;
	expr_r = 0;
	expr_c = 0;
	eval_err_code = 0;
	eval_err_fn = 0;
	fn_arg_ptr = 0;
	memset(wm, 0, sizeof(void*)*MAX_WM);   /* dynamically allocated working memory */
#if _MSC_VER <= 800
	memset(eval_jmp_buf, 0, sizeof(CATCHBUF));	
#else
	memset(eval_jmp_buf, 0, sizeof(jmp_buf));
#endif
}

void __cdecl _gx_si_show_cell_err_msg(int si, gxCell * cp, int /*audible*/)
{
	TCHAR line[512];
	wsprintf(line, _T("ERROR: %s %s "), cp->value.err.fn ? cp->value.err.fn : _T(""), _gx_xs_error_msg(cp->value.err.code));

	wsprintf(_gx_get_context_ptr(si)->szErrorText, _T("Cell %s%d: %s"),
//			_gx_col_to_text(cp->col - _gx_get_col_shift()), cp->row - _gx_get_row_shift(),
			_gx_col_to_text(cp->col), cp->row,
			line);
	TRACE(_T("%s\n"), _gx_get_context_ptr(si)->szErrorText);
}

#if _MSC_VER <= 800
#define setjmp Catch
#define longjmp Throw
#endif


GX_EVAL_STATE::~GX_EVAL_STATE()
{
}

const GX_EVAL_STATE& GX_EVAL_STATE::operator=(const GX_EVAL_STATE& eval)
{
	memcpy(this, &eval, sizeof(eval));
	return *this;
}

GX_EVAL_STATE* __cdecl GXGetEvalState()
{
	CGXAppData* pAppData = GXGetAppData();
	if (pAppData->m_pEvalState == NULL)
		pAppData->m_pEvalState = new GX_EVAL_STATE;

	return (GX_EVAL_STATE*) pAppData->m_pEvalState;
}


/*---------------------------------------------------------------------------*/
/*  Functions for examining parts of the evaluation state.                   */

int __cdecl _gx_get_expr_si(void)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	return estate.expr_si;
}

LPTSTR __cdecl _gx_get_xs_fn_name(void)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	return estate.xs_fn_name;
}

LPTSTR __cdecl _gx_get_expr_sbuf(void)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	return estate.expr_sbuf;
}

void __cdecl _gx_get_expr_rc(unsigned *r, unsigned *c)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	*r = estate.expr_r;
	*c = estate.expr_c;
}

int __cdecl _gx_get_expr_err_code(void)
{  /* named "expr" for historical reasons */
	GX_EVAL_STATE& estate = *GXGetEvalState();
	return estate.eval_err_code;
}

void __cdecl _gx_set_fn_arg_ptr(gxOperand * p)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	estate.fn_arg_ptr = p;
}

gxOperand * __cdecl  _gx_get_fn_arg_ptr(void)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	return estate.fn_arg_ptr;
}


/*---------------------------------------------------------------------------*/
/*  Functions for managing working memory buffers.                           */

void __cdecl _gx_mkwm(gxMatrix * m)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	register int i;

	for (i = 0; i < MAX_WM; i++)
		if (estate.wm[i] == NULL)
			break;
	assert(i < MAX_WM);
	estate.wm[i] = GX_XSmalloc(m->r_dim * m->c_dim * sizeof(double));
	m->data = (double *) estate.wm[i];
}

int __cdecl _gx_freewm(gxMatrix * m)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	register int i;

	for (i = 0; i < MAX_WM; i++)
		if (estate.wm[i] == m->data)
			break;
	if (i == MAX_WM)
		return 0;
	GX_XSfree(estate.wm[i]);
	estate.wm[i] = m->data = NULL;
	return 1;
}

void __cdecl _gx_cleanwm(void)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	register int i;

	for (i = 0; i < MAX_WM; i++)
		if (estate.wm[i] != NULL)
		{
			GX_XSfree(estate.wm[i]);
			estate.wm[i] = NULL;
		}
}

gxNumber * __cdecl _gx_mknumarray(int n)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	register int i;

	for (i = 0; i < MAX_WM; i++)
		if (estate.wm[i] == NULL)
			break;
	assert(i < MAX_WM);
	estate.wm[i] = GX_XSmalloc(n * sizeof(gxNumber));
	return (gxNumber *) estate.wm[i];
}


/*---------------------------------------------------------------------------*/
/*  Evaluation error handling.                                               */

void __cdecl _gx_eval_error(int code, LPTSTR fn_name)
{  /* must not be called outside *//* of evaluate()!             */
	GX_EVAL_STATE& estate = *GXGetEvalState();

	estate.eval_err_code = code;
	estate.eval_err_fn = fn_name;
	
#ifdef _WIN64
    if(estate.eval_jmp_buf[0].Part[0] == 0xff)
#else //WIN32
	if(estate.eval_jmp_buf[0] == 0xff)
#endif // _WIN64/WIN32
		throw nEvalError;
	
}


/*---------------------------------------------------------------------------*/
/*  Handler for floating-point exceptions.                                   */

static void __cdecl fpe_hndlr(int)
{
#if     defined(SYSV) || defined(VMS)
	_gx_fp_error_init();
#endif /* SYSV, VMS */
	_gx_eval_error(GX_FN_ERR_FLOAT, NULL);
}


void  __cdecl _gx_fp_error_init(void)
{
	signal(SIGFPE, (void (__cdecl *) (int)) fpe_hndlr);
}

/*---------------------------------------------------------------------------*/
/*  gxNumber acquisition.                                                      */

static int mk_constant(int si, gxOperand * opp)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	register gxCell *cp;

	switch (opp->type)
	{
	case GX_CELL:
		cp = _gx_find_cell(si, opp->val.range.r0, opp->val.range.c0);
		if (GX_CELL_IS_EMPTYVALUE(cp))
		{
//cb changed to conditionally treat blanks as zeros or errors 
			if( _gx_get_blanks_are_zeros(si)  )
            {
				opp->type = GX_NUMBER;
				opp->val.number = 0.;
			}
			else
			{
				opp->type = GX_OP_ERROR;
				opp->val.err.code = GX_FN_ERR_CELL_ERROR;
				opp->val.err.fn = NULL;
			}
// prior code implementation
//DJ
//			// changed this so that adding a blank and a number returns an error.
//			opp->type = GX_OP_ERROR;
//			opp->val.err.code = GX_FN_ERR_CELL_ERROR;
//			opp->val.err.fn = NULL;
//DJ
//			//opp->val.number = 0.;
//cb end of change
		}
		else
			switch (cp->value_type)
			{
			case GX_VALUE_NUMERIC:
				opp->type = GX_NUMBER;
				opp->val.number = cp->value.number;
				break;
			case GX_VALUE_STRING:
				opp->type = GX_STRING;
				_gxAddMemObj(opp->val.string = _gx_xs_strdup(cp->value.string));
				break;
			case GX_VALUE_SHORT_STRING:
				opp->type = GX_STRING;
				_gxAddMemObj(opp->val.string = _gx_xs_short_strdup(cp->value.short_string));
				break;
			case GX_VALUE_NA:
				opp->type = GX_OP_NA;
				break;
			case GX_VALUE_ERROR:
				if (estate.expr_si) // we are inside _gx_expr_eval()
					_gx_eval_error(GX_FN_ERR_OPRND_ERR, NULL);
				else
				{
					opp->type = GX_OP_ERROR;
					opp->val.err.code = GX_FN_ERR_CELL_ERROR;
					opp->val.err.fn = NULL;
				}
				break;
			default:
				assert(0);
			}
		return 1;
	case GX_NUMBER:
	case GX_STRING:
		return 1;
	case GX_OP_ERROR:
		if (estate.expr_si) /* we are inside _gx_expr_eval() */
			_gx_eval_error(opp->val.err.code, opp->val.err.fn);
	default:
		return 0;   /* can't be converted to constant */
	}
}


static gxNumber get_number(int si, gxOperand * opp)
{
	gxNumber x = 0;

	switch (opp->type)
	{
	case GX_NUMBER:
		x = opp->val.number;
		break;
	case GX_CELL:
		mk_constant(si, opp);
		switch (opp->type)
		{
		case GX_NUMBER:
			x = opp->val.number;
			break;
		case GX_STRING:
//cb changed to conditionally handle blanks as either errors or zeros
		    if( _gx_get_blanks_are_zeros(si) && _tcslen(opp->val.string)==0 )
                		x = 0.0; 
			else
			{
				GX_XSfree(opp->val.string);
				_gx_eval_error(GX_FN_ERR_NON_NUM_OPRND, NULL);
			}
//cb end of change
			GX_XSfree(opp->val.string);
			break; //cb break added
		default:
//DJ
			// changed this so that adding a atring and a number returns an error.
			_gx_eval_error(GX_FN_ERR_NON_NUM_OPRND, NULL);
			//x = 0.0;    /* assuming we count strings and blanks as zeros */
//DJ
		}
		break;
	case GX_STRING:
		// JLH: Code copied from case above.  This case is needed when
		// the operand is a string constant like ="Foo". Previously,
		// the string was not freed until the grid was destroyed,
		// instead of doing it here.
	        if( _gx_get_blanks_are_zeros(si) && _tcslen(opp->val.string)==0 )
               		x = 0.0; 
		else
			_gx_eval_error(GX_FN_ERR_NON_NUM_OPRND, NULL);
		GX_XSfree(opp->val.string);
		break;
	case GX_OP_ERROR:
		_gx_eval_error(opp->val.err.code, opp->val.err.fn);
	default:
		_gx_eval_error(GX_FN_ERR_NON_NUM_OPRND, NULL);
	}
	return (x);
}


static int get_int(int si, gxOperand * opp)
{
	int x = 0;
	switch (opp->type)
	{
	case GX_NUMBER:
		if (_gx_xs_int_check(opp->val.number))
			_gx_eval_error(GX_FN_ERR_OP_GT_32_BITS, NULL);
		else
			x = (int) opp->val.number;
		break;
	case GX_CELL:
		mk_constant(si, opp);
		switch (opp->type)
		{
		case GX_NUMBER:
			if (_gx_xs_int_check(opp->val.number))
				_gx_eval_error(GX_FN_ERR_OP_GT_32_BITS, NULL);
			else
				x = (int) opp->val.number;
			break;
		case GX_STRING:
			GX_XSfree(opp->val.string);
		default:
			x = 0;  /* assuming we count strings and blanks as zeros */
		}
		break;
	case GX_OP_ERROR:
		_gx_eval_error(opp->val.err.code, opp->val.err.fn);
	default:
		_gx_eval_error(GX_FN_ERR_NON_NUM_OPRND, NULL);
	}
	return x;
}


/*---------------------------------------------------------------------------*/
/*  Convert an gxOperand to the desired type                     */

static void convert_operand(int desired_type, gxOperand * opp)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	gxNumber x;

	switch (desired_type)
	{
	case GX_TC_NUMBER:
	case GX_TC_NUMERIC:
	case GX_TC_NUM_RNG:
		if (opp->type == GX_NUMBER)
			return;
		if (!mk_constant(estate.expr_si, opp))
			return;
		switch (opp->type)
		{
		case GX_NUMBER:
			break;
		case GX_STRING:
			x = _gxttof(opp->val.string);  /* NOTE:  check if string is numeric */
			opp->type = GX_NUMBER;
			GX_XSfree(opp->val.string);
			opp->val.number = x;
			break;
		default:
			_gx_eval_error(GX_FN_ERR_NON_NUM_OPRND, NULL);
			break;
		}
		break;
	}
}


/*---------------------------------------------------------------------------*/
/*  Convert an gxOperand to a gxCellValue.                                       */

static gxCellValue operand_to_cellvalue(int si, gxOperand op)
{
	gxCellValue result;

	mk_constant(si, &op);
	switch (op.type)
	{
	case GX_NUMBER:
		result.type = GX_VALUE_NUMERIC;
		result.value.number = op.val.number;
		break;
	case GX_STRING:
		result.type = GX_VALUE_STRING;
		result.value.string = op.val.string;
		break;
	case GX_CELL:
	case GX_RANGE:
		result.type = GX_VALUE_ERROR;
		result.value.err.code = GX_FN_ERR_RESULT_IS_RNG;
		result.value.err.fn = NULL;
		break;
	case GX_EXPR_TREE:
		assert(0);
		break;
	case GX_OP_ERROR:
		result.type = GX_VALUE_ERROR;
		result.value.err.code = op.val.err.code;
		result.value.err.fn = op.val.err.fn;
		break;
	case GX_OP_NA :
		result.type = GX_VALUE_NA;
		break;
	}
	return result;
}

/*---------------------------------------------------------------------------*/
/*  Constraint expression evaluator.                                         */

int  __cdecl _gx_evaluate_cexpr(int si, int row, int col, gxExprNode * nbuf, gxExprPointer start)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	gxOperand result;

	result = _gx_expr_eval(si, row, col, nbuf, start);
	switch (result.type)
	{
	case GX_NUMBER:
		return (result.val.number != 0.0);
	case GX_OP_ERROR:
		if (estate.xs_fn_name)  /* we are evaluating a conditional function */
			_gx_function_error(estate.eval_err_code);
		break;
	case GX_STRING:
		GX_XSfree(result.val.string);
	default:
		if (estate.xs_fn_name)  /* we are evaluating a conditional function */
			_gx_function_error(GX_FN_ERR_NON_NUM_OPRND);
		;
	}
	return 0;
}


/*---------------------------------------------------------------------------*/
/*  gxCell evaluator.                                                          */

int  __cdecl _gx_evaluate_cell(int si, gxCell * cp)
{
	gxOperand result_op;
	gxCellValue result;
	LPTSTR old_str = NULL;
	int keep_old_string = 0;

	if (GX_CELL_HAS_FORMULA(cp))
	{
		// SH - GX_CELL_CLEAR_FLAG(cp, GX_UPDATED);
		if (cp->value_type == GX_VALUE_STRING)
			old_str = cp->value.string;

		result_op = _gx_expr_eval(si, cp->row, cp->col, cp->formula->expression,
								  cp->formula->expr_start);
		result = operand_to_cellvalue(si, result_op);

		// TRACE(_T("Recalculated %d,%d\n"), cp->row, cp->col);
		switch (result.type)
		{
		case GX_VALUE_NUMERIC:
			if (cp->value_type == GX_VALUE_NUMERIC &&
				cp->value.number == result.value.number)
				break;
			cp->value.number = result.value.number;
			cp->value_type = GX_VALUE_NUMERIC;
			GX_CELL_SET_FLAG(cp, GX_UPDATED);
			break;
		case GX_VALUE_STRING:
			if (_tcslen(result.value.string) <= 8/sizeof(TCHAR))
			{
				if (cp->value_type == GX_VALUE_SHORT_STRING &&
					!_tcsncmp(cp->value.short_string, result.value.string, 8/sizeof(TCHAR)))
				{
					GX_XSfree(result.value.string);
					break;
				}
				_gx_xs_short_strcpy(cp->value.short_string, result.value.string, FALSE);
				cp->value_type = GX_VALUE_SHORT_STRING;
				GX_XSfree(result.value.string);
			}
			else
			{
				if (cp->value_type == GX_VALUE_STRING &&
					!_tcscmp(cp->value.string, result.value.string))
				{
					keep_old_string = 1;
					GX_XSfree(result.value.string);
					break;
				}
				cp->value.string = result.value.string;
				cp->value_type = GX_VALUE_STRING;
			}
			GX_CELL_SET_FLAG(cp, GX_UPDATED);
			break;
		case GX_VALUE_ERROR:
			{
				// Don't display error if error-state did not change
				if (cp->value_type == GX_VALUE_ERROR &&
					cp->value.err.code == result.value.err.code &&
					cp->value.err.fn == result.value.err.fn)
					break;

				// Else set error string
				cp->value_type = GX_VALUE_ERROR;
				cp->value.err.code = result.value.err.code;
				cp->value.err.fn = result.value.err.fn;

				if (_gx_get_context_ptr(si)->first_error)
				{   // display the error
					// message
					_gx_si_show_cell_err_msg(si, cp, 1);
					_gx_get_context_ptr(si)->first_error = 0;
				}
			}
			GX_CELL_SET_FLAG(cp, GX_UPDATED);
			break;
		
		case GX_VALUE_NA:
			cp->value_type = GX_VALUE_NA;
			break;

		default:
			assert(0);
		}
		if (old_str && !keep_old_string)
			GX_XSfree(old_str);

		return 1;
	}
	else
	{
		return 0;
	}
}


int  __cdecl _gx_evaluate_cell_constraint(int si, gxCell * cp)
{
	gxOperand result_op;
	gxCellValue result;
	int status = 1;
	int temp_flag;
	if (GX_CELL_HAS_FORMULA(cp) && cp->formula->cons_start != GX_ENULL)
	{
		temp_flag = GX_CELL_TEST_FLAG(cp, GX_CONSTRAINT_VIOL);
		result_op = _gx_expr_eval(si, cp->row, cp->col, cp->formula->expression,
								  cp->formula->cons_start);
		result = operand_to_cellvalue(si, result_op);
		if (result.type == GX_VALUE_NUMERIC && result.value.number == 0.0)
		{
			GX_CELL_SET_FLAG(cp, GX_CONSTRAINT_VIOL);
			status = 0;
		}
		else
		{
			GX_CELL_CLEAR_FLAG(cp, GX_CONSTRAINT_VIOL);
			status = 1;
		}

		// CHANGE 0907
		if (temp_flag != GX_CELL_TEST_FLAG(cp, GX_CONSTRAINT_VIOL))
			GX_CELL_SET_FLAG(cp, GX_UPDATED);
	}
	return status;
}

/*---------------------------------------------------------------------------*/
/*  String comparison for equality operators.                                */

static int xs_strcmp(LPCTSTR s1, LPCTSTR s2)
{
	TCHAR str1[GX_MAX_TEXT],
		  str2[GX_MAX_TEXT];
	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(str1, s1);
	_gx_str_trim(str1);

	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(str2, s2);
	_gx_str_trim(str2);

	return _tcscmp(str1, str2);
}


/*---------------------------------------------------------------------------*/
/*  Evaluate an operator subtree.                                            */

static gxOperand do_operator(gxExprNode * nbuf, gxExprPointer node)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	gxOperand op1,
			  op2;
	int int1,
		int2;
	gxNumber num1,
			 num2;
	gxOperand result;
	gxExprPointer ep;

	switch (nbuf[node].value.operator_)
	{
	case GX_PLUS:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		num1 = get_number(estate.expr_si, &op1);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		num2 = get_number(estate.expr_si, &op2);
		result.type = GX_NUMBER;
		result.val.number = num1 + num2;
		break;
	case GX_MINUS:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		num1 = get_number(estate.expr_si, &op1);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		num2 = get_number(estate.expr_si, &op2);
		result.type = GX_NUMBER;
		result.val.number = num1 - num2;
		break;
	case GX_UNARY_PLUS:
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		result.type = GX_NUMBER;
		result.val.number = get_number(estate.expr_si, &op2);
		break;
	case GX_UNARY_MINUS:
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		result.type = GX_NUMBER;
		result.val.number = -get_number(estate.expr_si, &op2);
		break;
	case GX_MULTIPLY:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		num1 = get_number(estate.expr_si, &op1);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		num2 = get_number(estate.expr_si, &op2);
		result.type = GX_NUMBER;
		result.val.number = num1 * num2;
		break;
	case GX_POWER:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		num1 = get_number(estate.expr_si, &op1);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		num2 = get_number(estate.expr_si, &op2);
		result.type = GX_NUMBER;
		errno = 0;
		result.val.number = pow(num1, num2);
		if (errno)
			_gx_eval_error(GX_FN_ERR_DIV_0, NULL);
		break;
	case GX_DIVIDE:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		num1 = get_number(estate.expr_si, &op1);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		num2 = get_number(estate.expr_si, &op2);
		if (num2 == 0.0)
			_gx_eval_error(GX_FN_ERR_DIV_0, NULL);
		result.type = GX_NUMBER;
		result.val.number = num1 / num2;
		break;
	case GX_MODULUS:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		int1 = get_int(estate.expr_si, &op1);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		int2 = get_int(estate.expr_si, &op2);
		if (int2 == 0)
			_gx_eval_error(GX_FN_ERR_MOD_DIV_0, NULL);
		result.type = GX_NUMBER;
		result.val.number = (gxNumber) (int1 % int2);
		break;
	case GX_LOGICAL_AND:
		result.type = GX_NUMBER;
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		num1 = get_number(estate.expr_si, &op1);
		if (num1 == 0.0)
			result.val.number = 0.0;
		else
		{
			op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
			num2 = get_number(estate.expr_si, &op2);
			result.val.number = (gxNumber) (num2 != 0.0);
		}
		break;
	case GX_LOGICAL_OR:
		result.type = GX_NUMBER;
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		num1 = get_number(estate.expr_si, &op1);
		if (num1 != 0.0)
			result.val.number = 1.0;
		else
		{
			op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
			num2 = get_number(estate.expr_si, &op2);
			result.val.number = (gxNumber) (num2 != 0.0);
		}
		break;
	case GX_LOGICAL_NOT:
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		num2 = get_number(estate.expr_si, &op2);
		result.type = GX_NUMBER;
		result.val.number = (gxNumber) (num2 == 0.0);
		break;
	case GX_BOOLEAN_AND:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		if (!mk_constant(estate.expr_si, &op1))
			_gx_eval_error(GX_FN_ERR_OPRND_OF_AMPSD, NULL);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		if (!mk_constant(estate.expr_si, &op2))
			_gx_eval_error(GX_FN_ERR_OPRND_OF_AMPSD, NULL);
		if (op1.type != op2.type)
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			if (op2.type == GX_STRING)
				GX_XSfree(op2.val.string);
			_gx_eval_error(GX_FN_ERR_OPRNDS_OF_AMPSD, NULL);
		}
		if (op1.type == GX_STRING)
		{   /* concatenate */
			if (_tcslen(op1.val.string) + _tcslen(op2.val.string) >= GX_MAX_TEXT)
			{
				GX_XSfree(op1.val.string);
				GX_XSfree(op2.val.string);
				_gx_eval_error(GX_FN_ERR_STR_TOO_LONG, NULL);
			}
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(estate.expr_sbuf, op1.val.string);
			_tcscat(estate.expr_sbuf, op2.val.string);
			GX_XSfree(op1.val.string);
			GX_XSfree(op2.val.string);
			result.type = GX_STRING;
			/**/_gxAddMemObj/**/(result.val.string = _gx_xs_strdup(estate.expr_sbuf));
		}
		else
		{   /* boolean_and */
			int1 = get_int(estate.expr_si, &op1);
			int2 = get_int(estate.expr_si, &op2);
			result.type = GX_NUMBER;
			result.val.number = (gxNumber) (int1 & int2);
		}
		break;
	case GX_BOOLEAN_OR:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		int1 = get_int(estate.expr_si, &op1);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		int2 = get_int(estate.expr_si, &op2);
		result.type = GX_NUMBER;
		result.val.number = (gxNumber) (int1 | int2);
		break;
	case GX_BOOLEAN_XOR:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		int1 = get_int(estate.expr_si, &op1);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		int2 = get_int(estate.expr_si, &op2);
		result.type = GX_NUMBER;
		result.val.number = (gxNumber) (int1 ^ int2);
		break;
	case GX_BOOLEAN_NOT:
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		int2 = get_int(estate.expr_si, &op2);
		result.type = GX_NUMBER;
		result.val.number = (gxNumber) (~int2);
		break;
	case GX_SHIFT_LEFT:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		int1 = get_int(estate.expr_si, &op1);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		int2 = get_int(estate.expr_si, &op2);
		result.type = GX_NUMBER;
		result.val.number = (gxNumber) (int1 << int2);
		break;
	case GX_SHIFT_RIGHT:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		int1 = get_int(estate.expr_si, &op1);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		int2 = get_int(estate.expr_si, &op2);
		result.type = GX_NUMBER;
		result.val.number = (gxNumber) (int1 >> int2);
		break;
	case GX_EQUAL:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		if (!mk_constant(estate.expr_si, &op1))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_EE, NULL);
		}
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		if (!mk_constant(estate.expr_si, &op2))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			if (op2.type == GX_STRING)
				GX_XSfree(op2.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_EE, NULL);
		}
		if (op1.type != op2.type)
			result.val.number = 0.0;
		else
		{
			if (op1.type == GX_STRING)
			{
				result.val.number = !xs_strcmp(op1.val.string,
											   op2.val.string);
			}
			else
			{
				num1 = op1.val.number;
				num2 = op2.val.number;
				result.val.number = (gxNumber) (num1 == num2);
			}
		}
		if (op1.type == GX_STRING)
			GX_XSfree(op1.val.string);
		if (op2.type == GX_STRING)
			GX_XSfree(op2.val.string);
		result.type = GX_NUMBER;
		break;
	case GX_NOT_EQUAL:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		if (!mk_constant(estate.expr_si, &op1))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_EE, NULL);
		}
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		if (!mk_constant(estate.expr_si, &op2))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			if (op2.type == GX_STRING)
				GX_XSfree(op2.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_NE, NULL);
		}
		if (op1.type != op2.type)
			result.val.number = 1.0;
		else
		{
			if (op1.type == GX_STRING)
			{
				result.val.number = !!xs_strcmp(op1.val.string,
												op2.val.string);
			}
			else
			{
				num1 = op1.val.number;
				num2 = op2.val.number;
				result.val.number = (gxNumber) (num1 != num2);
			}
		}
		if (op1.type == GX_STRING)
			GX_XSfree(op1.val.string);
		if (op2.type == GX_STRING)
			GX_XSfree(op2.val.string);
		result.type = GX_NUMBER;
		break;
	case GX_LESS_THAN:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		if (!mk_constant(estate.expr_si, &op1))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_EE, NULL);
		}
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		if (!mk_constant(estate.expr_si, &op2))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			if (op2.type == GX_STRING)
				GX_XSfree(op2.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_LT, NULL);
		}
		if (op1.type != op2.type)
		{
			if (op1.type == GX_STRING)
				result.val.number = 1.0;
			else
				result.val.number = 0.0;
		}
		else
		{
			if (op1.type == GX_STRING)
			{
				result.val.number =
					xs_strcmp(op1.val.string, op2.val.string) < 0;
			}
			else
			{
				num1 = op1.val.number;
				num2 = op2.val.number;
				result.val.number = (gxNumber) (num1 < num2);
			}
		}
		if (op1.type == GX_STRING)
			GX_XSfree(op1.val.string);
		if (op2.type == GX_STRING)
			GX_XSfree(op2.val.string);
		result.type = GX_NUMBER;
		break;
	case GX_GREATER_THAN:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		if (!mk_constant(estate.expr_si, &op1))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_EE, NULL);
		}
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		if (!mk_constant(estate.expr_si, &op2))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			if (op2.type == GX_STRING)
				GX_XSfree(op2.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_GT, NULL);
		}
		if (op1.type != op2.type)
		{
			if (op1.type == GX_STRING)
				result.val.number = 0.0;
			else
				result.val.number = 1.0;
		}
		else
		{
			if (op1.type == GX_STRING)
			{
				result.val.number =
					xs_strcmp(op1.val.string, op2.val.string) > 0;
			}
			else
			{
				num1 = op1.val.number;
				num2 = op2.val.number;
				result.val.number = (gxNumber) (num1 > num2);
			}
		}
		if (op1.type == GX_STRING)
			GX_XSfree(op1.val.string);
		if (op2.type == GX_STRING)
			GX_XSfree(op2.val.string);
		result.type = GX_NUMBER;
		break;
	case GX_LT_OR_EQUAL:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		if (!mk_constant(estate.expr_si, &op1))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_EE, NULL);
		}
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		if (!mk_constant(estate.expr_si, &op2))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			if (op2.type == GX_STRING)
				GX_XSfree(op2.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_LE, NULL);
		}
		if (op1.type != op2.type)
		{
			if (op1.type == GX_STRING)
				result.val.number = 1.0;
			else
				result.val.number = 0.0;
		}
		else
		{
			if (op1.type == GX_STRING)
			{
				result.val.number =
					xs_strcmp(op1.val.string, op2.val.string) <= 0;
			}
			else
			{
				num1 = op1.val.number;
				num2 = op2.val.number;
				result.val.number = (gxNumber) (num1 <= num2);
			}
		}
		if (op1.type == GX_STRING)
			GX_XSfree(op1.val.string);
		if (op2.type == GX_STRING)
			GX_XSfree(op2.val.string);
		result.type = GX_NUMBER;
		break;
	case GX_GT_OR_EQUAL:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		if (!mk_constant(estate.expr_si, &op1))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_EE, NULL);
		}
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		if (!mk_constant(estate.expr_si, &op2))
		{
			if (op1.type == GX_STRING)
				GX_XSfree(op1.val.string);
			if (op2.type == GX_STRING)
				GX_XSfree(op2.val.string);
			_gx_eval_error(GX_FN_ERR_OPRND_OF_GE, NULL);
		}
		if (op1.type != op2.type)
		{
			if (op1.type == GX_STRING)
				result.val.number = 0.0;
			else
				result.val.number = 1.0;
		}
		else
		{
			if (op1.type == GX_STRING)
			{
				result.val.number =
					xs_strcmp(op1.val.string, op2.val.string) >= 0;
			}
			else
			{
				num1 = op1.val.number;
				num2 = op2.val.number;
				result.val.number = (gxNumber) (num1 >= num2);
			}
		}
		if (op1.type == GX_STRING)
			GX_XSfree(op1.val.string);
		if (op2.type == GX_STRING)
			GX_XSfree(op2.val.string);
		result.type = GX_NUMBER;
		break;
	case GX_CONDITIONAL:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		if (get_number(estate.expr_si, &op1) == 0.0)
			ep = nbuf[nbuf[node].right].right;
		else
			ep = nbuf[nbuf[node].right].left;
		result = _gx_do_eval(nbuf, ep, 1);
		break;
	case GX_JOINRANGE:
		op1 = _gx_do_eval(nbuf, nbuf[node].left, 1);
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		if (op1.type != GX_CELL || op2.type != GX_CELL)
			_gx_eval_error(GX_FN_ERR_OPRNDS_OF_DOTDOT, NULL);
		result.type = GX_RANGE;
		result.val.range.r0 = op1.val.range.r0;
		result.val.range.c0 = op1.val.range.c0;
		result.val.range.r1 = op2.val.range.r0;
		result.val.range.c1 = op2.val.range.c0;
		result.val.range.abs_r0 = op1.val.range.abs_r0;
		result.val.range.abs_c0 = op1.val.range.abs_c0;
		result.val.range.abs_r1 = op2.val.range.abs_r0;
		result.val.range.abs_c1 = op2.val.range.abs_c0;
		result.val.range.cell_only = 0;
		_gx_sort_range(&(result.val.range));
		break;
	case GX_PERCENT:
		op2 = _gx_do_eval(nbuf, nbuf[node].right, 1);
		num2 = get_number(estate.expr_si, &op2);
		result.type = GX_NUMBER;
		result.val.number = num2 / 100.0;
		break;
	case GX_ILLEGAL_OP:
		result.type = GX_OP_ERROR;
		result.val.err.code = GX_FN_ERR_ILLEGAL_REF;
		result.val.err.fn = NULL;
		break;
	default:
		assert(0);
	}

	return result;
}


/*---------------------------------------------------------------------------*/
/*  Evaluate a function subtree.                                             */

static gxOperand do_function(gxExprNode * nbuf, gxExprPointer node, int bAddMem)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	gxOperand result;
	gxOperand arguments[GX_MAX_ARGS];
	int count;
	gxExprPointer np;

	count = 1;
	estate.xs_fn_name = nbuf[node].value.fnp->name;
	for (np = nbuf[node].right; np != GX_ENULL; np = nbuf[np].right, count++)
	{
		if (nbuf[np].arg_is_nonstrict)
		{
			arguments[count].type = GX_EXPR_TREE;
			arguments[count].val.etree.nbuf = nbuf;
			arguments[count].val.etree.start = nbuf[np].left;
		}
		else
		{
			arguments[count] = _gx_do_eval(nbuf, nbuf[np].left, 0);
			convert_operand(nbuf[np].value.arg.decl_arg_type, &arguments[count]);
		}
	}
	estate.xs_fn_name = nbuf[node].value.fnp->name;
	arguments[0].val.count = count - 1;

	_gx_set_fn_arg_ptr(arguments);
	if (nbuf[node].value.fnp->port == 0)
		result = (*(nbuf[node].value.fnp->function)) (arguments);
	// else
	// result = ext_function (nbuf[node].value.fnp, arguments);
	estate.eval_err_code = 0;
	_gx_clean_fn_args();
	if (result.type == GX_STRING)   /* functions use expr_sbuf for strings! */
	{
		result.val.string = _gx_xs_strdup(result.val.string);
		if (bAddMem)
			_gxAddMemObj(result.val.string);
	}
	return result;
}

/*---------------------------------------------------------------------------*/
/*  Workhorse expression evaluator.                                          */

gxOperand  __cdecl _gx_do_eval(gxExprNode * nbuf, gxExprPointer node, int bAddMem)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	gxOperand result;
	gxOperand op1,
			  op2;
	gxRange temp_rng;

	/* _gx_dump_node (nbuf[node], node); */
	switch (nbuf[node].node_type)
	{
	case GX_OPERATOR_NODE:
		result = do_operator(nbuf, node);
		break;
	case GX_NUMBER_NODE:
		result.type = GX_NUMBER;
		result.val.number = nbuf[node].value.operand;
		break;
	case GX_STRING_NODE:
		result.type = GX_STRING;
		result.val.string = _gx_xs_strdup(nbuf[node].value.string);
		if (bAddMem)
			_gxAddMemObj(result.val.string);
		break;
	case GX_CELL_NODE:
		result.type = GX_CELL;
		result.val.range = nbuf[node].value.range;
		break;
	case GX_RANGE_NODE:
		result.type = GX_RANGE;
		result.val.range = nbuf[node].value.range;
		break;
	case GX_NAME_NODE:
		_gx_eval_error(GX_FN_ERR_NAME_USED, NULL);
		break;
	case GX_NAMED_CELL_NODE:
		result.type = GX_CELL;
		result.val.range = nbuf[node].value.rnp->range;
		break;
	case GX_NAMED_RANGE_NODE:
		result.type = GX_RANGE;
		result.val.range = nbuf[node].value.rnp->range;
		break;
	case GX_FUNCTION_NODE:
		result = do_function(nbuf, node, bAddMem);
		break;
	case GX_RELATIVE_NODE:
		temp_rng.r0 = estate.expr_r;
		temp_rng.c0 = estate.expr_c;
		temp_rng.cell_only = 1;
		if (nbuf[node].value.rel.r_expr != GX_ENULL)
		{
			op1 = _gx_do_eval(nbuf, nbuf[node].value.rel.r_expr, 0);
			temp_rng.r0 += (unsigned) get_number(estate.expr_si, &op1);
		}
		if (nbuf[node].value.rel.c_expr != GX_ENULL)
		{
			op2 = _gx_do_eval(nbuf, nbuf[node].value.rel.c_expr, 0);
			temp_rng.c0 += (unsigned) get_number(estate.expr_si, &op2);
		}
		if (!GX_BOUNDS_CHECK(temp_rng.r0, temp_rng.c0))
			_gx_eval_error(GX_FN_ERR_INVALID_CELL_REF, NULL);
		result.type = GX_CELL;
		result.val.range = temp_rng;
		break;
	case GX_ARG_NODE:
	case GX_EXTENSION_NODE:
		_gx_eval_error(GX_FN_ERR_UNCONSUMED, NULL);
		break;
	}
	if (result.type == GX_NUMBER && _gx_ieee_infnan(&result.val.number))
	{
		result.type = GX_OP_ERROR;
		result.val.err.code = GX_FN_ERR_IEEE_INF_NAN;
		result.val.err.fn = NULL;   /* needs to be set if inside fn */
	}
	return result;
}

/*
* The following function traps error long jumps so that they can be
* passed back to the function, rather than trapping back to _gx_expr_eval.
* This is needed for the @ISERROR() function.
*/

#pragma warning(disable:4611)
// disable warning for interaction between '_setjmp' and C++ object destruction is non-portable
// It is safe here because engine does not use C++ objects.

gxOperand  __cdecl _gx_do_eval_et(gxExprNode * nbuf, gxExprPointer node)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	gxOperand result;
	GX_EVAL_STATE old_state;	
	
	old_state = estate; /* save the current estate */

	bool bError = false;
	try
	{
#ifdef _WIN64
		estate.eval_jmp_buf[0].Part[0] = 0xff;
		result = _gx_do_eval(nbuf, node, 0);
		estate.eval_jmp_buf[0].Part[0] = 0;
#else // WIN32
		estate.eval_jmp_buf[0] = 0xff;
		result = _gx_do_eval(nbuf, node, 0);
		estate.eval_jmp_buf[0] = 0;
#endif // _WIN64/WIN32
	}
	catch(...)
	{
		bError = true;	
		_gx_set_expr_err_flag(1);
		result.type = GX_OP_ERROR;
		result.val.err.code = estate.eval_err_code;
		result.val.err.fn = estate.eval_err_fn;
		_gx_cleanwm();
#ifdef _WIN64
		estate.eval_jmp_buf[0].Part[0] = 0;
#else // WIN32
		estate.eval_jmp_buf[0] = 0;
#endif // _WIN64/WIN32
		estate = old_state;
	}

	if(bError)
		return result;

	estate = old_state;
	return result;
}

/*---------------------------------------------------------------------------*/
/*  Primary expression evaluator.                                            */

gxOperand  __cdecl _gx_expr_eval(int si, int row, int col, gxExprNode * nbuf, gxExprPointer start)
{
	GX_EVAL_STATE& estate = *GXGetEvalState();
	gxOperand result;
	GX_EVAL_STATE old_state;
	TCHAR s1[GX_MAX_TEXT];

	/***  Save current evaluation state
	***/
	old_state = estate;

	/***  Set up new evaluation state
	***/
	_gx_set_expr_err_flag(0);
	estate.expr_si = si;
	estate.expr_r = row;
	estate.expr_c = col;
	estate.expr_sbuf = s1;
	estate.eval_err_code = 0;
	estate.xs_fn_name = NULL;
	estate.eval_err_fn = NULL;

	/***  Set up floating-point error handler
	***/

	bool bError = false;
	try
	{
#ifdef _WIN64
		estate.eval_jmp_buf[0].Part[0] = 0xff;
		result = _gx_do_eval(nbuf, start, 0);	
		estate.eval_jmp_buf[0].Part[0] = 0;
#else // WIN32
		estate.eval_jmp_buf[0] = 0xff;
		result = _gx_do_eval(nbuf, start, 0);	
		estate.eval_jmp_buf[0] = 0;
#endif // _WIN64/WIN32
	}
	catch(...)
	{
		bError = true;
		_gx_set_expr_err_flag(1);
		result.type = GX_OP_ERROR;
		result.val.err.code = estate.eval_err_code;
		result.val.err.fn = estate.eval_err_fn;
		_gx_cleanwm();
		_gx_set_error_reason(estate.eval_err_code);
#ifdef _WIN64
		estate.eval_jmp_buf[0].Part[0] = 0;
#else //WIN32
		estate.eval_jmp_buf[0] = 0;
#endif	// _WIN64/WIN32
		estate = old_state;			
	}
	
	if(bError)
		return result;
	
	/***  Restore previous evaluation state and exit
	***/
	_gx_cleanwm();
	_gx_set_error_reason(estate.eval_err_code);
	estate = old_state;
	return result;
}

#pragma warning (pop)
