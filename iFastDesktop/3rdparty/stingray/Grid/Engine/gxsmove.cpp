///////////////////////////////////////////////////////////////////////////////
// gxsmove.cpp: Move and copy cells in worksheet
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


void __cdecl _gx_set_doing_insert_or_delete(int value)
{
	GXGetEngineState()->doing_insert_or_delete = value;
}

gxRange  __cdecl _gx_figure_move_dest(gxRange * sp, int r, int c)
{
	gxRange dest;
	dest.r0 = r;
	dest.c0 = c;
	dest.r1 = (unsigned) GX_MIN(r + sp->r1 - sp->r0, GX_MAX_ROW);
	dest.c1 = (unsigned) GX_MIN(c + sp->c1 - sp->c0, GX_MAX_COL);
	return dest;
}

void __cdecl _gx_preserve_raw(int si, gxCell * cp)
{
	gxSheetContext *context;
	if (cp == NULL)
		return;

	// TRACE(_T("_gx_preserve_raw(gxCell = %d/%d)\n"), cp->row, cp->col);
	context = _gx_get_context_ptr(si);
	cp->next = context->preserve_list;
	context->preserve_list = cp;
}

void __cdecl _gx_set_undo_range(int si, gxRange dst)	/* needed for UNDO_PASTE */
{
    _gx_get_context_ptr(si)->undo_dst = dst;
}

int  __cdecl _gx_move_range(int si, gxRange src, int r, int c, int adjust_suppress)
{
	gxRange dst,
			orig_src;
	gxCell *cp,
		  *dp,
		  *next_cell,
		  *move_list = NULL,
		  *remove_list = NULL;
	gxSheetContext *context = _gx_get_context_ptr(si);
	gxCellBlockList temp_list;
	gxScanBuf scan;
	unsigned dr,
		dc,
		move_size;
	int i,
		flag,
		dup_flag;
	gxExprNode *ep,
			   expr_save[GX_MAX_NODES];
	gxFormula fm;

	dr = r - src.r0;
	dc = c - src.c0;
	dst = _gx_figure_move_dest(&src, r, c);
	move_size = (src.r1 - src.r0 + 1) * (src.c1 - src.c0 + 1);

	temp_list.head = temp_list.tail = NULL;
	temp_list._gx_cell_count = 0;
	temp_list.freeze_order = 0;
	temp_list.needs_reorder = 0;

	if (!adjust_suppress)
	{
		_gx_adjust_named_ranges(si, &src, dr, dc);  
	}

	int mask = _gx_freeze_list_order(si, GX_ALL_LISTS);

	orig_src = src;

	// if (_gx_limit_to_extent(si, &src))
	{
		/* cells to move */

		/* Put all cells from the consant_list which are in the src range in the
		 * move_list.  Put all cells from the constant list which are in the dst
		 * range but not in the src range in the remove_list. We pick the most
		 * efficient way to find all the constant_list cells in the src and dst
		 * ranges by comparing the range size to the size of the constant_list.
		 * If the range sizes are large compared to number of cells in the
		 * constant_list, then a single scan of the entire constant_list is
		 * probably better. */

		GX_MARK_MODIFIED(si);

		if (move_size * 2 > context->constant_list._gx_cell_count)
		{
			_gx_init_cell_list_scan(&context->constant_list, &scan);
			while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
			{
				if (!cp->inserted)
					continue;
				if (GX_IN_RANGE(src, cp->row, cp->col))
				{   /* put it in the move list */
					_gx_remove_cell(si, cp);
					if (context->keep_empties && !GX_IN_RANGE(dst, cp->row, cp->col))
					{
						_gx_insert_empty_cell(si, cp->row, cp->col, NULL);
					}
					cp->next = move_list;
					move_list = cp;
					GX_CELL_SET_FLAG(cp, GX_UPDATED);   // so we know it is up
					// to date
				}
				else if (GX_IN_RANGE(dst, cp->row, cp->col))
				{   /* put it in the _tremove list */
					_gx_remove_cell(si, cp);
					cp->next = remove_list;
					remove_list = cp;
					GX_CELL_SET_FLAG(cp, GX_UPDATED);   // so we know it is up
					// to date
				}
			}
		}
		else
		{   /* better to do two separate range scans */
			_gx_init_range_scan(si, src, &scan, GX_CONSTANT_LIST);  // | GRAPHIC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
			{
				if (!cp->inserted)
					continue;
				_gx_remove_cell(si, cp);
				if (context->keep_empties && !GX_IN_RANGE(dst, cp->row, cp->col))
				{
					_gx_insert_empty_cell(si, cp->row, cp->col, NULL);
				}
				cp->next = move_list;
				move_list = cp;
				GX_CELL_SET_FLAG(cp, GX_UPDATED);   // so we know it is up to
				// date
			}
			_gx_init_range_scan(si, dst, &scan, GX_CONSTANT_LIST);  // | GRAPHIC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
			{
				if (!cp->inserted)
					continue;
				if (!GX_IN_RANGE(src, cp->row, cp->col))
				{
					_gx_remove_cell(si, cp);
					cp->next = remove_list;
					remove_list = cp;
					GX_CELL_SET_FLAG(cp, GX_UPDATED);   // so we know it is up
					// to date
				}
			}
		}
	}

	/* We must scan the entire recalc_list and update all formulas which
	 * reference any cell being moved to point to the cell's new location. */

	_gx_init_cell_list_scan(&context->recalc_list, &scan);
	while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
	{
		if (!cp->inserted)
			continue;

		// TCHAR buf[512];
		// _gx_expr_print(si, cp->formula, buf);
		// TRACE(_T("%d,%d: %s"), cp->row, cp->col, buf);

		dup_flag = 0;   /* if set, must duplicate cell in case of undo */
		int update = 0;

		if (GX_IN_RANGE(dst, cp->row, cp->col) 
			&& !GX_IN_RANGE(src, cp->row, cp->col))
		{
			// Is this a tool or matrix result cell
			if (cp->formula->expression[0].node_type == GX_NUMBER_NODE
				&& cp->formula->expression[1].node_type == GX_CELL_NODE)
			{
				_gx_add_recalc_range(si, &cp->formula->expression[1].value.range);
			}
		}


		if (!adjust_suppress && !(GX_IN_RANGE(dst, cp->row, cp->col) &&
								  !GX_IN_RANGE(src, cp->row, cp->col)))
		{
			for (i = 0; i < cp->formula->expr_size; i++)
			{
				ep = cp->formula->expression + i;
				expr_save[i] = *ep;
				if ((ep->node_type == GX_CELL_NODE) || (ep->node_type == GX_RANGE_NODE))
				{
					flag = 0;
					if (GX_IN_RANGE(orig_src, ep->value.range.r0, ep->value.range.c0)
						&& GX_IN_RANGE(orig_src, ep->value.range.r1, ep->value.range.c1))
					{
						ep->value.range.r0 += dr;
						ep->value.range.c0 += dc;
						ep->value.range.r1 += dr;
						ep->value.range.c1 += dc;
						flag = 1;
						update = 1;
					}
					else if (GX_IN_RANGE(orig_src, ep->value.range.r0, ep->value.range.c0))
					{	// range size changing
						ep->value.range.r0 += dr;
						ep->value.range.c0 += dc;
						flag = 1;
						update = 1;
					}
					else if (GX_IN_RANGE(orig_src, ep->value.range.r1, ep->value.range.c1))
					{	// range size changing
						ep->value.range.r1 += dr;
						ep->value.range.c1 += dc;
						flag = 1;
						update = 1;
					}
					else if (GX_IN_RANGE(dst, ep->value.range.r0, ep->value.range.c0)
						|| GX_IN_RANGE(dst, ep->value.range.r1, ep->value.range.c1))
					{
						dup_flag = 1;
						update = 1;
					}
					if (flag)
					{
						_gx_sort_range(&(ep->value.range));
						if (!GX_RANGE_CHECK(ep->value.range))
						{
							ep->node_type = GX_OPERATOR_NODE;
							ep->value.operator_ = GX_ILLEGAL_OP;
						}
					}
				}
			}
		}
		if (update)
			GX_CELL_SET_FLAG(cp, GX_NEEDS_RECALC);  // so we know it is up
		// to date

		if (context->do_preserve && dup_flag)
		{   /* save for proper undo */
			dp = _gx_copy_cell_to_list(&temp_list, cp);
			if (cp->pStyle)
				dp->pStyle = cp->pStyle->Clone();
			else
				dp->pStyle = NULL;
			fm = *(cp->formula);
			fm.expression = expr_save;
			_gx_replace_cell_formula(dp, &fm);
		}
		if (GX_IN_RANGE(src, cp->row, cp->col))
		{   /* put it in the move list */
			_gx_remove_cell(si, cp);
			if (context->keep_empties && !GX_IN_RANGE(dst, cp->row, cp->col))
			{
				_gx_insert_empty_cell(si, cp->row, cp->col, NULL);
			}
			cp->next = move_list;
			move_list = cp;
		}
		else if (GX_IN_RANGE(dst, cp->row, cp->col))
		{   /* put it in the _tremove list */
			_gx_remove_cell(si, cp);
			cp->next = remove_list;
			remove_list = cp;
		}
	}

	/* Now we must move the cells in temp_list back to context->recalc_list
	 * and preserve them.  These cells contain formulas which reference the
	 * destination of the move operation.  Note that this list will be empty
	 * if context->do_preserve is not turned on. */

	_gx_init_cell_list_scan(&temp_list, &scan);
	while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
	{
		gxCell* dp = _gx_copy_cell_to_list(&context->recalc_list, cp);
		cp->pStyle = NULL;
		// if (cp->pStyle)
		//	dp->pStyle = cp->pStyle->Clone();
		_gx_preserve_raw(si, dp);
	}
	_gx_free_cell_block_list(&temp_list);

	/* Free the cells in the remove_list. */

	for (cp = remove_list; cp != (gxCell *) 0; cp = next_cell)
	{
		next_cell = cp->next;

		if (context->do_preserve)
			_gx_preserve_raw(si, cp);
		else
			_gx_free_cell(cp);
	}

	/* Move the cells in the move list to the destination. */

	for (cp = move_list; cp != (gxCell *) 0; cp = next_cell)
	{
		next_cell = cp->next;
		if (!GX_BOUNDS_CHECK(cp->row + dr, cp->col + dc))
		{
			// if (context->do_preserve)
			// _gx_preserve_raw(si, cp);
			// else
			_gx_free_cell(cp);
		}
		else
		{
			cp->row = (gxRowCol) (cp->row + dr);
			cp->col = (gxRowCol) (cp->col + dc);
			/* have to clean out any aliases or empties */
			_gx_destroy_cell(si, _gx_find_cell(si, cp->row, cp->col));
			_gx_insert_cell(si, cp);
		}
	}

/*	if (!adjust_suppress)
	{
		_gx_add_recalc_range(si, &src);
		_gx_add_recalc_range(si, &dst);
		_gx_recalc(si);
	}*/
	
	_gx_unfreeze_list_order(si, mask);

	return 1;
}


void  __cdecl _gx_figure_insert_col_src_dst(int c, int n, gxRange * src, gxRange * dst)
{

	src->r0 = GX_MIN_ROW;
	src->r1 = GX_MAX_ROW;
	src->c0 = c;
	src->c1 = GX_MAX_COL;   /* was GX_MAX_COL - n */
	dst->r0 = GX_MIN_ROW;
	dst->r1 = GX_MAX_ROW;
	dst->c0 = c + n;
	dst->c1 = (unsigned) (GX_MAX_COL + n);   /* was GX_MAX_COL */
}


int  __cdecl _gx_insert_columns(int si, int c, int n)
{
	gxRange src,
			dst;
	gxSheetContext *context = _gx_get_context_ptr(si);
	int status;
	int ke_save = context->keep_empties;

	GXGetEngineState()->doing_insert_or_delete = 1;
	_gx_figure_insert_col_src_dst(c, n, &src, &dst);
	context->keep_empties = 0;
	status = _gx_move_range(si, src, dst.r0, dst.c0, 0);
	context->keep_empties = ke_save;
	GXGetEngineState()->doing_insert_or_delete = 0;
	return status;
}


void  __cdecl _gx_figure_insert_row_src_dst(int r, int n, gxRange * src, gxRange * dst)
{
	src->r0 = r;
	src->r1 = GX_MAX_ROW;   /* was GX_MAX_ROW - n */
	src->c0 = GX_MIN_COL;
	src->c1 = GX_MAX_COL;
	dst->r0 = r + n;
	dst->r1 = (unsigned) (GX_MAX_ROW + n);   /* was GX_MAX_ROW */
	dst->c0 = GX_MIN_COL;
	dst->c1 = GX_MAX_COL;
}


int  __cdecl _gx_insert_rows(int si, int r, int n)
{
	gxRange src,
			dst;
	gxSheetContext *context = _gx_get_context_ptr(si);
	int status;
	int ke_save = context->keep_empties;

	GXGetEngineState()->doing_insert_or_delete = 1;
	_gx_figure_insert_row_src_dst(r, n, &src, &dst);
	context->keep_empties = 0;
	status = _gx_move_range(si, src, dst.r0, dst.c0, 0);
	context->keep_empties = ke_save;
	GXGetEngineState()->doing_insert_or_delete = 0;
	return status;
}


void  __cdecl _gx_figure_delete_col_src_dst(int c, int n, gxRange * src, gxRange * dst)
{
	dst->r0 = GX_MIN_ROW;
	dst->r1 = GX_MAX_ROW;
	dst->c0 = c;
	dst->c1 = GX_MAX_COL;   /* was GX_MAX_COL - n */
	src->r0 = GX_MIN_ROW;
	src->r1 = GX_MAX_ROW;
	src->c0 = c + n;
	src->c1 = (unsigned) (GX_MAX_COL + n);   /* was GX_MAX_COL */
}


int  __cdecl _gx_delete_cols(int si, int c, int n)
{
	gxRange src,
			dst;
	gxSheetContext *context = _gx_get_context_ptr(si);
	int status;
	int ke_save = context->keep_empties;

	GXGetEngineState()->doing_insert_or_delete = 1;
	context->keep_empties = 0;
	_gx_clear_range(si, _gx_make_range(GX_MIN_ROW, c, GX_MAX_ROW, c + n - 1, 0));
	_gx_figure_delete_col_src_dst(c, n, &src, &dst);
	status = _gx_move_range(si, src, dst.r0, dst.c0, 0);
	context->keep_empties = ke_save;
	GXGetEngineState()->doing_insert_or_delete = 0;
	return status;
}


void __cdecl _gx_figure_delete_row_src_dst(int r, int n, gxRange * src, gxRange * dst)
{
	dst->r0 = r;
	dst->r1 = GX_MAX_ROW;   /* was GX_MAX_ROW - n */
	dst->c0 = GX_MIN_COL;
	dst->c1 = GX_MAX_COL;
	src->r0 = r + n;
	src->r1 = (unsigned) (GX_MAX_ROW + n);   /* was GX_MAX_ROW */
	src->c0 = GX_MIN_COL;
	src->c1 = GX_MAX_COL;
}


int  __cdecl _gx_delete_rows(int si, int r, int n)
{
	gxRange src,
			dst;
	gxSheetContext *context = _gx_get_context_ptr(si);
	int status;
	int ke_save = context->keep_empties;
	int ke_preserve = context->do_preserve;

	GXGetEngineState()->doing_insert_or_delete = 1;
	context->keep_empties = 0;
	context->do_preserve = 0;
	_gx_clear_range(si, _gx_make_range(r, GX_MIN_COL, r + n - 1, GX_MAX_COL, 0));
	context->do_preserve = 1;
	_gx_figure_delete_row_src_dst(r, n, &src, &dst);
	status = _gx_move_range(si, src, dst.r0, dst.c0, 0);
	context->keep_empties = ke_save;
	context->do_preserve = ke_preserve;
	GXGetEngineState()->doing_insert_or_delete = 0;
	return status;
}

// NOTE - cell reference will only be adjusted if the whole range
// is part of the move operation

void  __cdecl _gx_adjust_value_move2(unsigned *c0, unsigned *c1, unsigned nFrom, unsigned nTo, unsigned nDest)
{
	int nCount = nTo - nFrom + 1;

	if (*c0 >= nFrom && *c0 <= nTo)
	{
		/* cell in range to be moved */
		*c0 = (unsigned) (nDest + (*c0 - nFrom));
		*c1 = (unsigned) (nDest + (*c1 - nFrom));
	}
	else if (nDest < nFrom && *c0 >= nDest && *c0 < nFrom)
	{
		/* cell left of range to be moved but right to dest */
		*c0 = (unsigned) (*c0 + nCount);
		*c1 = (unsigned) (*c1 + nCount);
	}
	else if (nDest > nTo && *c0 > nFrom && *c0 < nDest + nCount)
	{
		/* cell right of range to be left of dest */
		*c0 = (unsigned) (*c0 - nCount);
		*c1 = (unsigned) (*c1 - nCount);
	}
}

void  __cdecl _gx_adjust_value_move1(unsigned *c, unsigned nFrom, unsigned nTo, unsigned nDest)
{
	if (*c >= nFrom && *c <= nTo)
		*c = (unsigned) (*c - nFrom + nDest);

	else if (nDest < nFrom)
		*c = (unsigned) (*c + (nTo - nFrom + 1));

	else
		*c = (unsigned) (*c - (nTo - nFrom + 1));
}

int  __cdecl _gx_reorder_range(int si, int nRowOrCol, int nFrom, int nTo, int nDest)
{
	gxRange // dst,
			src,
			orig_src;
	gxCell *cp,
		  *dp,
		  *next_cell,
		  *move_list = NULL;
	gxSheetContext *context = _gx_get_context_ptr(si);
	gxCellBlockList temp_list;
	gxScanBuf scan;
	int
		i,
		flag,
		dup_flag;
	gxExprNode *ep,
			   expr_save[GX_MAX_NODES];
	gxFormula fm;

	if (nRowOrCol)
	{
		// reorder rows
		src.r0 = min(nFrom, nDest);
		src.r1 = max(nTo, nDest + (nTo - nFrom));
		src.c0 = GX_MIN_COL;
		src.c1 = GX_MAX_COL;
	}
	else
	{
		// reorder columns
		src.c0 = min(nFrom, nDest);
		src.c1 = max(nTo, nDest + (nTo - nFrom));
		src.r0 = GX_MIN_ROW;
		src.r1 = GX_MAX_ROW;
	}

	/* dr = r - src.r0; dc = c - src.c0; dst = _gx_figure_move_dest(&src, r,
	 * c); move_size = (src.r1 - src.r0 + 1) * (src.c1 - src.c0 + 1); */

	temp_list.head = temp_list.tail = NULL;
	temp_list._gx_cell_count = 0;
	temp_list.freeze_order = 0;
	temp_list.needs_reorder = 0;

//  if (!adjust_suppress)
	{
		_gx_adjust_reorder_named_ranges(si, &src, nRowOrCol, nFrom, nTo, nDest);
	}

	orig_src = src;
	if (!_gx_limit_to_extent(si, &src))
		return 1;   /* no cells to move */

	/* Put all cells from the consant_list which are in the src range in the
	 * move_list.  Put all cells from the constant list which are in the dst
	 * range but not in the src range in the remove_list. We pick the most
	 * efficient way to find all the constant_list cells in the src and dst
	 * ranges by comparing the range size to the size of the constant_list.
	 * If the range sizes are large compared to number of cells in the
	 * constant_list, then a single scan of the entire constant_list is
	 * probably better. */

	GX_MARK_MODIFIED(si);

	{
		_gx_init_cell_list_scan(&context->constant_list, &scan);
		while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
		{
			if (!cp->inserted)
				continue;
			if (GX_IN_RANGE(src, cp->row, cp->col))
			{   /* put it in the move list */
				_gx_remove_cell(si, cp);
				/*if (context->keep_empties && !GX_IN_RANGE(dst, cp->row, cp->col))
				{
					// get_properties_from_cell(cp, &cprop);
					_gx_insert_empty_cell(si, cp->row, cp->col, NULL);
				} */
				cp->next = move_list;
				move_list = cp;
			}
		}
	}

	/* We must scan the entire recalc_list and update all formulas which
	 * reference any cell being moved to point to the cell's new location. */

	_gx_init_cell_list_scan(&context->recalc_list, &scan);
	while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
	{
		if (!cp->inserted)
			continue;
		dup_flag = 0;   /* if set, must duplicate cell in case of undo */
//      if (!adjust_suppress)
		{
			for (i = 0; i < cp->formula->expr_size; i++)
			{
				ep = cp->formula->expression + i;
				expr_save[i] = *ep;
				if ((ep->node_type == GX_CELL_NODE) || (ep->node_type == GX_RANGE_NODE))
				{
					flag = 0;
					if (GX_IN_RANGE(orig_src, ep->value.range.r0, ep->value.range.c0)
						|| GX_IN_RANGE(orig_src, ep->value.range.r1, ep->value.range.c1))
					{
						unsigned r0,
							  r1;
						if (nRowOrCol)
							r0 = ep->value.range.r0, r1 = ep->value.range.r1;
						else
							r0 = ep->value.range.c0, r1 = ep->value.range.c1;

						_gx_adjust_value_move2(&r0, &r1, nFrom, nTo, nDest);

						if (nRowOrCol)
							ep->value.range.r0 = r0, ep->value.range.r1 = r1;
						else
							ep->value.range.c0 = r0, ep->value.range.c1 = r1;

						flag = 1;
					}
					if (flag)
					{
						_gx_sort_range(&(ep->value.range));
						if (!GX_RANGE_CHECK(ep->value.range))
						{
							ep->node_type = GX_OPERATOR_NODE;
							ep->value.operator_ = GX_ILLEGAL_OP;
						}
					}
				}
			}
		}
		if (context->do_preserve && dup_flag)
		{   /* save for proper undo */
			dp = _gx_copy_cell_to_list(&temp_list, cp);
			fm = *(cp->formula);
			fm.expression = expr_save;
			_gx_replace_cell_formula(dp, &fm);
			/* _gx_preserve_raw(dp); DO THIS LATER!!! */
		}
		if (GX_IN_RANGE(src, cp->row, cp->col))
		{   /* put it in the move list */
			_gx_remove_cell(si, cp);
			/*if (context->keep_empties && !GX_IN_RANGE(dst, cp->row, cp->col))
			{
				// get_properties_from_cell(cp, &cprop);
				_gx_insert_empty_cell(si, cp->row, cp->col, NULL);
			} */
			cp->next = move_list;
			move_list = cp;
		}
/*      nothing _getts removed - we only reorder!
				else if (GX_IN_RANGE(dst, cp->row, cp->col))    /* put it in the _tremove list /
				{
						//      check_alias_neighborhood(si, cp->row, cp->col);
						_gx_remove_cell(si, cp);
						cp->next = remove_list;
						remove_list = cp;
				}*/
	}

	/* Move the cells in the move list to the destination. */

	for (cp = move_list; cp != (gxCell *) 0; cp = next_cell)
	{
		next_cell = cp->next;

		unsigned r = cp->row, c = cp->col;

		if (nRowOrCol)
			_gx_adjust_value_move1(&r, nFrom, nTo, nDest);
		else
			_gx_adjust_value_move1(&c, nFrom, nTo, nDest);

		cp->row = (gxRowCol) r;
		cp->col = (gxRowCol) c;

		assert(GX_BOUNDS_CHECK(cp->row, cp->col));

		/* have to clean out any aliases or empties */
		_gx_destroy_cell(si, _gx_find_cell(si, cp->row, cp->col));
		_gx_insert_cell(si, cp);
	}

//  if (!adjust_suppress)
	{
//		_gx_add_recalc_range(si, &src);
//		_gx_recalc(si);
	}

	return 1;
}


int  __cdecl _gx_copy_range(int si, gxRange src, int r, int c, int adjust_suppress)
{
	gxRange dst,
			orig_src;
	gxCell *cp,
		  *next_cell,
		  *move_list = NULL;
	gxSheetContext *context = _gx_get_context_ptr(si);
	gxCellBlockList temp_list;
	gxScanBuf scan;
	int dr,
		dc,
		i,
		flag,
		move_size;
	gxExprNode *ep,
			   expr_save[GX_MAX_NODES];

	dr = r - src.r0;
	dc = c - src.c0;
	dst = _gx_figure_move_dest(&src, r, c);
	move_size = (src.r1 - src.r0 + 1) * (src.c1 - src.c0 + 1);

	temp_list.head = temp_list.tail = NULL;
	temp_list._gx_cell_count = 0;
	temp_list.freeze_order = 0;
	temp_list.needs_reorder = 0;

//  if (!adjust_suppress)
//    {
//      _gx_adjust_named_ranges(si, &src, dr, dc);  /* TKM 5/6/90 */
	// }

	// included this to prevent the problem of copy/pasting an 8X6 range in a fresh grid
	// (It causes the lists to be rearranged in the middle of copying resulting in erroneous copy)

	int mask = _gx_freeze_list_order(si, GX_ALL_LISTS);

	orig_src = src;
	if (!_gx_limit_to_extent(si, &src))
		return 1;   /* no cells to move */

	/* Put all cells from the consant_list which are in the src range in the
	 * move_list.  Put all cells from the constant list which are in the dst
	 * range but not in the src range in the remove_list. We pick the most
	 * efficient way to find all the constant_list cells in the src and dst
	 * ranges by comparing the range size to the size of the constant_list.
	 * If the range sizes are large compared to number of cells in the
	 * constant_list, then a single scan of the entire constant_list is
	 * probably better. */

	GX_MARK_MODIFIED(si);

	_gx_init_range_scan(si, src, &scan, GX_ALL_LISTS);  // | GRAPHIC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
	{
		gxCell *dp = _gx_cell_dup(cp);

		dp->row = (gxRowCol) (dp->row + dr);
		dp->col = (gxRowCol) (dp->col + dc);

		if (dp->formula)
		{
			for (i = 0; i < dp->formula->expr_size; i++)
			{
				ep = dp->formula->expression + i;
				expr_save[i] = *ep;
				if ((ep->node_type == GX_CELL_NODE) || (ep->node_type == GX_RANGE_NODE))
				{
					flag = 0;
					// if (GX_IN_RANGE(orig_src, ep->value.range.r0,
					// ep->value.range.c0))
					{
						if (!ep->value.range.abs_r0)
							ep->value.range.r0 += dr;

						if (!ep->value.range.abs_c0)
							ep->value.range.c0 += dc;
						flag = 1;
						// TRACE(_T("%d,%d\n"), ep->value.range.r0,
						// ep->value.range.c0);
					}
					// if (GX_IN_RANGE(orig_src, ep->value.range.r1,
					// ep->value.range.c1))
					{
						if (!ep->value.range.abs_r1)
							ep->value.range.r1 += dr;
						if (!ep->value.range.abs_c1)
							ep->value.range.c1 += dc;
						flag = 1;
					}
					if (flag)
					{
						_gx_sort_range(&(ep->value.range));
						if (!GX_RANGE_CHECK(ep->value.range))
						{
							ep->node_type = GX_OPERATOR_NODE;
							ep->value.operator_ = GX_ILLEGAL_OP;
						}
					}
				}
			}
		}
		dp->next = move_list;
		move_list = dp;
	}

	_gx_init_range_scan(si, dst, &scan, GX_ALL_LISTS);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
	{
		_gx_remove_cell(si, cp);
		if (context->do_preserve)
			_gx_preserve_raw(si, cp);
		else
			_gx_free_cell(cp);
	}

	for (cp = move_list; cp != (gxCell *) 0; cp = next_cell)
	{
		next_cell = cp->next;

		/* have to clean out any aliases or empties */
		_gx_destroy_cell(si, _gx_find_cell(si, cp->row, cp->col));
		_gx_insert_cell(si, cp);
	}

	if (!adjust_suppress)
	{
		_gx_add_recalc_range(si, &src);
		_gx_add_recalc_range(si, &dst);
		_gx_recalc(si);
	}

	_gx_unfreeze_list_order(si, mask);

	return 1;
}
