///////////////////////////////////////////////////////////////////////////////
// gxsrngn.cpp: Named Ranges
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

int  __cdecl _gx_range_name_set(int si, LPCTSTR name, gxRange * range)
/*
  Defines a new named range, or changes the value of an existing named range.
  Returns 0 if "name" is not a valid range name; 1 otherwise.
*/
{
	gxRangeName **rnpp;
	TCHAR name_buf[GX_MAX_NAME_LEN];

	// QA: 31989 - #if Secure Code Cleanup.
	_tcsncpy(name_buf, name, GX_MAX_NAME_LEN);
	name_buf[31] = _T('\0');
	if (!_gx_valid_range_name(name_buf))
		return 0;
	for (rnpp = &_gx_get_context_ptr(si)->range_name_list;
		 (*rnpp) != NULL; rnpp = &((*rnpp)->next))
		if (!_tcsicmp((*rnpp)->name, name_buf))
		{   /* name found */
			(*rnpp)->range = *range;
			break;
		}
	if (*rnpp == NULL)
	{   /* create a new entry */
		*rnpp = (gxRangeName *) GX_XSmalloc(sizeof(gxRangeName));
		(*rnpp)->next = NULL;
		(*rnpp)->name = _gx_xs_strdup(name_buf);
		(*rnpp)->range = *range;
	}
	GX_MARK_MODIFIED(si);
	// nr_insert_list(si, name_buf, range);  /* WEW */
	return 1;
}


int  __cdecl _gx_valid_range_name_char(TCHAR c)
{
	if (_istalnum(c) || c == _T('.') || c == _T('_') || c == _T('$'))
		return 1;
	else
		return 0;
}


int  __cdecl _gx_valid_range_name(LPCTSTR name)
//    Returns 1 if "name" is a valid range name.
//    gxRange names must start with an alphabetic character, followed by zero or
//     more characters from the set:
//{
//    A - Z, a - z, 0 - 9,., _, $
//}.
// gxRange names are case sensitive.
{
	if (!(_istalpha(*name) || *name == _T('_') || *name == _T('$')))
		return 0;
	while (*(++name))
		if (!_gx_valid_range_name_char(*name))
			return 0;
	return 1;
}


gxRangeName * __cdecl _gx_range_name_lookup(int si, LPCTSTR name, gxRange * range)
{
	register gxRangeName *rnp;

	for (rnp = _gx_get_context_ptr(si)->range_name_list;
		 rnp != NULL; rnp = rnp->next)
	{
		if (!_tcsicmp(rnp->name, name))
		{   /* name found */
			if (range != NULL)
				*range = rnp->range;
			break;
		}
	}
	return rnp; /* NULL if not found */
}

void  __cdecl _gx_adjust_reorder_named_ranges(int si, gxRange * range, int nRowOrCol, int nFrom, int nTo, int nDest)
{
	// Unused:
	si;

	register gxRangeName *rnp;

	for (rnp = _gx_get_context_ptr(si)->range_name_list;
		 rnp != NULL; rnp = rnp->next)
	{
		if (GX_IN_RANGE(*range, rnp->range.r0, rnp->range.c0))
		{
			unsigned r0,
				  r1;
			if (nRowOrCol)
				r0 = rnp->range.r0, r1 = rnp->range.r1;
			else
				r0 = rnp->range.c0, r1 = rnp->range.c1;

			_gx_adjust_value_move2(&r0, &r1, nFrom, nTo, nDest);

			if (nRowOrCol)
				rnp->range.r0 = r0, rnp->range.r1 = r1;
			else
				rnp->range.c0 = r0, rnp->range.c1 = r1;

			_gx_sort_range(&(rnp->range));
			// update dropdown listbox that shows all named ranges
			// nr_remove_list(si, rnp->name);
			// nr_insert_list(si, rnp->name, &(rnp->range));
		}
	}
}

void  __cdecl _gx_adjust_named_ranges(int si, gxRange * range, int dr, int dc)
/*
   If a region containing one or more named ranges moves, then the named
   ranges should be adjusted to reflect the move. (At least Lotus does!)
*/
{
	register gxRangeName *rnp;
	register int flag;

	for (rnp = _gx_get_context_ptr(si)->range_name_list;
		 rnp != NULL; rnp = rnp->next)
	{
		flag = 0;
		if (GX_IN_RANGE(*range, rnp->range.r0, rnp->range.c0))
		{
			rnp->range.r0 = (unsigned) (GX_LIMIT(rnp->range.r0 + dr, GX_MIN_ROW, GX_MAX_ROW));
			rnp->range.c0 = (unsigned) (GX_LIMIT(rnp->range.c0 + dc, GX_MIN_COL, GX_MAX_COL));
			flag = 1;
		}
		if (GX_IN_RANGE(*range, rnp->range.r1, rnp->range.c1))
		{
			rnp->range.r1 = (unsigned) (GX_LIMIT(rnp->range.r1 + dr, GX_MIN_ROW, GX_MAX_ROW));
			rnp->range.c1 = (unsigned) (GX_LIMIT(rnp->range.c1 + dc, GX_MIN_COL, GX_MAX_COL));
			flag = 1;
		}
		if (flag)
		{
			_gx_sort_range(&(rnp->range));
			// nr_remove_list(si, rnp->name);
			// nr_insert_list(si, rnp->name, &(rnp->range));
		}
	}
	GX_MARK_MODIFIED(si);
}


extern void __cdecl _gx_preserve_raw(int si, gxCell * cp);

static void salvage_references(int si, gxRangeName * rnp)
/*
 * Check for references to deleted rnp and convert to explicit
 * range/cell references.
 */
{
	gxSheetContext *context = _gx_get_context_ptr(si);
	int i;
	gxCell *cp;
	gxExprNode *ep;
	gxScanBuf scan;
	int dup_flag = 0;
	gxCellBlockList temp_list;

	temp_list.head = temp_list.tail = NULL;
	temp_list._gx_cell_count = 0;
	temp_list.freeze_order = 0;
	temp_list.needs_reorder = 0;

	_gx_init_cell_list_scan(&_gx_get_context_ptr(si)->recalc_list, &scan);
	while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
	{
		dup_flag = 0;   /* if set, must duplicate cell in case of undo */
		for (i = 0; i < cp->formula->expr_size; i++, ep++)
		{
			ep = cp->formula->expression + i;
			if (ep->node_type == GX_NAMED_RANGE_NODE && ep->value.rnp == rnp)
			{
				// copy cell before we change anything the first time 
				if (!dup_flag && context->do_preserve)
				{
					gxCell* dp = _gx_copy_cell_to_list(&temp_list, cp);
					if (cp->pStyle)
						dp->pStyle = cp->pStyle->Clone();
				}

				ep->node_type = GX_RANGE_NODE;
				ep->value.range = rnp->range;
				GX_MARK_MODIFIED(si);

				dup_flag = 1;
			}
			else if (ep->node_type == GX_NAMED_CELL_NODE && ep->value.rnp == rnp)
			{
				// copy cell before we change anything the first time 
				if (!dup_flag && context->do_preserve)
				{
					gxCell* dp = _gx_copy_cell_to_list(&temp_list, cp);
					if (cp->pStyle)
						dp->pStyle = cp->pStyle->Clone();
				}

				ep->node_type = GX_CELL_NODE;
				ep->value.range = rnp->range;
				GX_MARK_MODIFIED(si);
				
				dup_flag = 1;
			}
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
		_gx_preserve_raw(si, dp);
	}
	_gx_free_cell_block_list(&temp_list);
}

int  __cdecl _gx_range_name_delete(int si, LPCTSTR name)
{
	gxSheetContext *context = _gx_get_context_ptr(si);
	register gxRangeName **rnpp;

	for (rnpp = &context->range_name_list;
		 (*rnpp) != NULL; rnpp = &((*rnpp)->next))
		if (!_tcsicmp(name, (*rnpp)->name))
		{   /* name found */
			gxRangeName *temp = (*rnpp)->next;
			salvage_references(si, *rnpp);

			// save info
			if (context->do_preserve)
			{
				context->deleted_range_name = *rnpp;
			}
			else
			{
				GX_XSfree((*rnpp)->name);   /* free the name */
				GX_XSfree(*rnpp);   /* free the struct */
			}
			*rnpp = temp;   /* fix the link */
			GX_MARK_MODIFIED(si);
			// nr_remove_list(si, name);  /* WEW */
			return 1;
		}
	return 0;   // nothing deleted */
}

int  __cdecl _gx_range_name_undelete(int si, gxRangeName* rnp)
{
	gxSheetContext *context = _gx_get_context_ptr(si);

	if (rnp == 0)
		return 0;

	rnp->next = context->range_name_list;
	context->range_name_list = rnp;

	return 1;
}

void  __cdecl _gx_resolve_names(int si, gxFormula * fm)
{
	// Unused:
	si;

	int i;

	for (i = 0; i < fm->expr_size; i++)
	{
		switch (fm->expression[i].node_type)
		{
		case GX_NAMED_RANGE_NODE:
			fm->expression[i].node_type = GX_RANGE_NODE;
			fm->expression[i].value.range = fm->expression[i].value.rnp->range;
			break;
		case GX_NAMED_CELL_NODE:
			fm->expression[i].node_type = GX_CELL_NODE;
			fm->expression[i].value.range = fm->expression[i].value.rnp->range;
			break;
		}
	}
}


void  __cdecl _gx_free_range_name_list(int si)
{  // clears the range name list */
	gxRangeName *rnp,
			   *rnp_next;
	gxSheetContext *context = _gx_get_context_ptr(si);

	for (rnp = context->range_name_list;
		 rnp != NULL; rnp = rnp_next)
	{
		rnp_next = rnp->next;
		// nr_remove_list(si, rnp->name);
		GX_XSfree(rnp->name);
		GX_XSfree(rnp);
	}
	context->range_name_list = NULL;
}
