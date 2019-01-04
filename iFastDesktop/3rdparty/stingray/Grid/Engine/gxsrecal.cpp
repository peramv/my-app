///////////////////////////////////////////////////////////////////////////////
// gxsrecalc.cpp: Recalculate formulas
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


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

static int suppress_inside_range = 0;

static int recalc_check(int si, gxCell * cp);

static int recalc_1(int si);

void  __cdecl _gx_add_recalc_range(int si, gxRange * rp)
{
	register gxRangeList **rlpp;

	for (rlpp = &_gx_get_context_ptr(si)->recalc_rangelist;
		 (*rlpp) != NULL; rlpp = &((*rlpp)->next))
		if (_gx_same_range(rp, &((*rlpp)->range)))
			break;
	if (*rlpp == NULL)
	{   /* create a new entry */
		*rlpp = (gxRangeList *) GX_XSmalloc(sizeof(gxRangeList));
		(*rlpp)->next = NULL;
		(*rlpp)->range = *rp;
	}
}


void  __cdecl _gx_clear_recalc_rangelist(int si)
{
	register gxRangeList *rlp,
			   *next;
	gxSheetContext *context = _gx_get_context_ptr(si);

	for (rlp = context->recalc_rangelist; rlp != NULL; rlp = next)
	{
		next = rlp->next;
		GX_XSfree(rlp);
	}
	context->recalc_rangelist = NULL;
}


static int recalc_check(int si, gxCell * cp)
/*
  Determines whether the cell cp is either contained in, or depends
  on a cell which is contained in, one of the ranges in the
  recalc_rangelist.  A NULL recalc_rangelist always returns True,
  and signifies full recalculation.
*/
{
	gxExprNode *ep;
	int i = 0;
	gxRangeList *rlp;
	gxSheetContext *context = _gx_get_context_ptr(si);

	if (context->recalc_rangelist == NULL)
		return 1;

	if (!suppress_inside_range)
	{
		for (rlp = context->recalc_rangelist; rlp != NULL; rlp = rlp->next)
			if (GX_IN_RANGE(rlp->range, cp->row, cp->col))
				return 1;
	}
	for (i = 0; i < cp->formula->expr_size; i++)
	{
		ep = (cp->formula->expression) + i;
		switch (ep->node_type)
		{
		case GX_CELL_NODE:
			for (rlp = context->recalc_rangelist; rlp != NULL; rlp = rlp->next)
				if (GX_IN_RANGE(rlp->range, ep->value.range.r0, ep->value.range.c0))
					return 1;
			break;
		case GX_RANGE_NODE:
			for (rlp = context->recalc_rangelist; rlp != NULL; rlp = rlp->next)
				if (_gx_intersect(&(rlp->range), &(ep->value.range)))
					return 1;
			break;
		case GX_NAMED_CELL_NODE:
			for (rlp = context->recalc_rangelist; rlp != NULL; rlp = rlp->next)
				if (GX_IN_RANGE(rlp->range,
					  (ep->value.rnp)->range.r0, (ep->value.rnp)->range.c0))
					return 1;
			break;
		case GX_NAMED_RANGE_NODE:
			for (rlp = context->recalc_rangelist; rlp != NULL; rlp = rlp->next)
				if (_gx_intersect(&(rlp->range), &((ep->value.rnp)->range)))
					return 1;
			break;
		}
	}
	return 0;
}


int  __cdecl _gx_test_partial_recalc(int si)
{
	if (_gx_get_context_ptr(si)->recalc_rangelist == NULL)
		return 0;
	else
		return 1;
}

void  __cdecl _gx_back_calc(int si, gxCell * cp)
/* recursively back_calculate from cp */
{
	gxCell *dp;
	short propagate = 0,
		  i = 0,
		  c_start,
		  c_end;
	unsigned r,
		  c;

	if (GX_CELL_TEST_FLAG(cp, GX_VISITED))
		return;
	GX_CELL_SET_FLAGS(cp, GX_VISITED | GX_TOUCHED);
	if (GX_CELL_TEST_FLAG(cp, GX_NEEDS_RECALC))
		propagate = 1;

/*
 * Find the boudaries of the constraint part of the expression
 * by following the left and right pointers.  This is to avoid
 * looking at constraint dependencies during the evaluation of
 * the main formula.  This needs to be incorporated in the parser
 * rather than handled during _gx_recalc!!!
 */

	if ((c_start = c_end = cp->formula->cons_start) != GX_ENULL)
	{
		while (cp->formula->expression[c_start].left != GX_ENULL)
			c_start = cp->formula->expression[c_start].left;
		while (cp->formula->expression[c_end].right != GX_ENULL)
			c_end = cp->formula->expression[c_end].right;
	}
	for (i = 0; i < cp->formula->expr_size; i++)
	{
		if (GX_IN_LIMITS(i, c_start, c_end))
			continue;
		if (cp->formula->expression[i].is_extern_ref)
			continue;

		switch (cp->formula->expression[i].node_type)
		{
		case GX_CELL_NODE:
			r = cp->formula->expression[i].value.range.r0;
			c = cp->formula->expression[i].value.range.c0;
			dp = _gx_find_cell(si, r, c);
			if (GX_CELL_HAS_FORMULA(dp))
			{
				if (GX_CELL_TEST_FLAG(dp, GX_TOUCHED))
					GX_CELL_SET_FLAG(cp, GX_CYCLE);
				if (!GX_CELL_TEST_FLAG(dp, GX_VISITED))
					_gx_back_calc(si, dp);
				if (GX_CELL_TEST_FLAG(dp, GX_CYCLE))    // SH
					_gx_get_context_ptr(si)->bCycle = 1; // SH
//          GX_CELL_SET_FLAG(cp, GX_CYCLE));        //SH
				if (!cp->inserted)
					break;
				propagate |= dp->serial > cp->serial;
			}
			break;

		case GX_RANGE_NODE:
			{
				gxScanBuf scan;

				_gx_init_range_scan(si,
									cp->formula->expression[i].value.range, &scan, GX_RECALC_LIST);
				while ((dp = _gx_do_range_scan(&scan)) != NULL)
				{
					if (GX_CELL_HAS_FORMULA(dp))
					{
						if (GX_CELL_TEST_FLAG(dp, GX_TOUCHED))
							GX_CELL_SET_FLAG(cp, GX_CYCLE);
						if (!GX_CELL_TEST_FLAG(dp, GX_VISITED))
							_gx_back_calc(si, dp);
						if (GX_CELL_TEST_FLAG(dp, GX_CYCLE))    // SH
							_gx_get_context_ptr(si)->bCycle = 1; // SH
//          GX_CELL_SET_FLAG(cp, GX_CYCLE));        //SH
						if (!cp->inserted)
							break;
						propagate |= dp->serial > cp->serial;
					}
				}
				break;
			}

		case GX_NAMED_CELL_NODE:
			r = cp->formula->expression[i].value.rnp->range.r0;
			c = cp->formula->expression[i].value.rnp->range.c0;
			dp = _gx_find_cell(si, r, c);
			if (GX_CELL_HAS_FORMULA(dp))
			{
				if (GX_CELL_TEST_FLAG(dp, GX_TOUCHED))
					GX_CELL_SET_FLAG(cp, GX_CYCLE);
				if (!GX_CELL_TEST_FLAG(dp, GX_VISITED))
					_gx_back_calc(si, dp);
				if (GX_CELL_TEST_FLAG(dp, GX_CYCLE))    // SH
					_gx_get_context_ptr(si)->bCycle = 1; // SH
//          GX_CELL_SET_FLAG(cp, GX_CYCLE));        //SH
				if (!cp->inserted)
					break;
				propagate |= dp->serial > cp->serial;
			}
			break;

		case GX_NAMED_RANGE_NODE:
			{
				gxScanBuf scan;

				_gx_init_range_scan(si,
									cp->formula->expression[i].value.rnp->range, &scan, GX_RECALC_LIST);
				while ((dp = _gx_do_range_scan(&scan)) != NULL)
				{
					if (GX_CELL_HAS_FORMULA(dp))
					{
						if (GX_CELL_TEST_FLAG(dp, GX_TOUCHED))
							GX_CELL_SET_FLAG(cp, GX_CYCLE);
						if (!GX_CELL_TEST_FLAG(dp, GX_VISITED))
							_gx_back_calc(si, dp);
						if (GX_CELL_TEST_FLAG(dp, GX_CYCLE))    // SH
							_gx_get_context_ptr(si)->bCycle = 1; // SH
//          GX_CELL_SET_FLAG(cp, GX_CYCLE));        //SH
						if (!cp->inserted)
							break;
						propagate |= dp->serial > cp->serial;
						// if dp has been reevaluated, dp->serial =
						// _gx_get_context_ptr(si)->serial
						// and therefore dp->serial will be greather than
						// cp->serial because
						// _gx_get_context_ptr(si)->serial has been increased
						// before _gx_back_calc
						// is called for the first cell (see recalc_1)
					}
				}
				break;
			}
		}
		if (!cp->inserted)
		{   /* cell has gone away (embedded tool) */
			propagate = 0;
			break;
		}
	}

	if (propagate)
	{   // this cell has GX_NEEDS_RECALC flag or a
		// refereed cell was reevaluated
		_gx_evaluate_cell(si, cp);
		// TRACE(_T("%d/%d evaluated\n"), cp->row, cp->col);
		GX_CELL_CLEAR_FLAG(cp, GX_NEEDS_RECALC);
		cp->serial = _gx_get_context_ptr(si)->serial;
		if (!GX_CELL_TEST_FLAG(cp, GX_UPDATED))
			propagate = 0;
	}
	GX_CELL_CLEAR_FLAG(cp, GX_TOUCHED);
}


int  __cdecl _gx_check_recalc_status(int si)
{
	return _gx_get_context_ptr(si)->recalc_status;
}


void  __cdecl _gx_force_recalc(int si)
{
	gxSheetContext *context = _gx_get_context_ptr(si);
	int mode_save;
	mode_save = context->recalc_mode;
	context->recalc_mode = GX_RECALC_AUTO;
	context->recalc_status |= 2;
	_gx_recalc(si);
	context->recalc_status = 0;
	context->recalc_mode = mode_save;
}


int  __cdecl _gx_edit_recalc(int si)
/*
 * Called instead of "_gx_recalc()" when a cell is edited to avoid redundant
 * evaluation of the edited cell.
 */
{
	int status;
	suppress_inside_range = 1;
	status = _gx_recalc(si);
	suppress_inside_range = 0;
	return status;
}

int  __cdecl _gx_recalc(int si)
{
	int i,
		status;
	gxSheetContext *context = _gx_get_context_ptr(si);

	if (context->recalc_mode == GX_RECALC_MANUAL)
	{
		_gx_clear_recalc_rangelist(si);
		return 0;   /* manual recalculation */
	}
	context->recalc_status |= 1;
	_gx_get_context_ptr(si)->bCycle = 0;
	// if (context->iteration_limit == 0)   /* normal recalculation */
	recalc_1(si);
	// else
	if (_gx_get_context_ptr(si)->bCycle)
	{
		context->recalc_status |= 64;   /* indicate iteration */
		for (i = 1; i <= context->iteration_limit; i++)
		{
			// TRACE(_T("Iteration %d\n"), i);
			status = recalc_1(si);
			if (context->constraint_check && !status)
				break;
		}
	}
	_gx_clear_recalc_rangelist(si);
	context->recalc_status = 0;

	return 1;
}


static int recalc_1(int si)
{  /* perform one iteration of recalculation */
	gxCell *cp;
	int constraint_flag = 0,
		needs_recalc = 0;
	gxSheetContext *context = _gx_get_context_ptr(si);
	gxScanBuf scan;
	int mask;

	/* First, set all the appropriate flags */

	_gx_init_cell_list_scan(&context->recalc_list, &scan);
	while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
	{   /* clear the appropriate bits */
		if (!cp->inserted)
			continue;
		GX_CELL_CLEAR_FLAGS(cp, GX_VISITED | GX_TOUCHED | GX_CYCLE);  // GX_UPDATE flag not cleared out
		if (recalc_check(si, cp))
		{
			// TRACE(_T("%d/%d needs _gx_recalc\n"), cp->row, cp->col);
			GX_CELL_SET_FLAG(cp, GX_NEEDS_RECALC);
			needs_recalc = 1;
		}
	}

	mask = _gx_freeze_list_order(si, GX_ALL_LISTS); /* in case of cell
													 * allocate/free */

	if (needs_recalc)
	{
		++context->serial;
		if (_gx_get_recalc_method(si) == GX_RECALC_AS_NEEDED)
			NULL;  
		else if (_gx_get_recalc_method(si) == GX_RECALC_FOREGROUND)
		{
			_gx_init_cell_list_scan(&context->recalc_list, &scan);
			while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
			{
				if (!cp->inserted)
					continue;
				if (!GX_CELL_TEST_FLAG(cp, GX_VISITED))
					_gx_back_calc(si, cp);
			}
		}
	}
	_gx_unfreeze_list_order(si, mask);

	/* If constraint_check is turned on, check all cells for constraint
	 * violations. */

	if (_gx_get_constraint_check(si) && context->first_error)
	{
		constraint_flag += _gx_find_constraints(si, &context->constant_list);
		constraint_flag += _gx_find_constraints(si, &context->recalc_list);
		if (constraint_flag)
		{
			if (constraint_flag == 1)
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_tcscpy(_gx_get_context_ptr(si)->szErrorText, _T("There is 1 constraint violation!"));
			}else
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_stprintf(_gx_get_context_ptr(si)->szErrorText, _T("There are %d constraint violations!"), constraint_flag);
			}
			context->first_error = 0;   // so we won't erase the message
		}
	}
	return constraint_flag;
}


int  __cdecl _gx_find_constraints(int si, gxCellBlockList * gxlist)
{
	gxCell *cp;
	gxScanBuf scan;
	int violations = 0;
	int mask;

	mask = _gx_freeze_list_order(si, GX_ALL_LISTS);

	_gx_init_cell_list_scan(gxlist, &scan);
	while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
	{
		if (!cp->inserted)
			continue;
		if (!GX_CELL_CONTAINS_ERROR(cp))
		{
			if (!_gx_evaluate_cell_constraint(si, cp))
				violations++;
		}
	}

	_gx_unfreeze_list_order(si, mask);

	return (violations);
}


void  __cdecl _gx_check_tool_neighborhood(int si, gxCell* cp)
{
	// Is this a tool or matrix result cell
	if (cp->formula && cp->formula->expression[0].node_type == GX_NUMBER_NODE
		&& cp->formula->expression[1].node_type == GX_CELL_NODE)
	{
		TCHAR buf[512];
		_gx_expr_print(si, cp->formula, buf);
		// TRACE(_T("%d,%d: %s"), cp->row, cp->col, buf);

		_gx_add_recalc_range(si, &cp->formula->expression[1].value.range);
	}
}
