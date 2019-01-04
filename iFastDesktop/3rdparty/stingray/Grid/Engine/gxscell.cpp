///////////////////////////////////////////////////////////////////////////////
// gxscell.cpp: Formula Engine cell and worksheet info
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

/* static prototypes for cell.c */

static void zero_cell(gxCell cells[], int index);

static gxCellBlock *cell_block_ptr(gxCell * cp);

static void link_first(gxCellBlockList * gxlist, gxCellBlock * cbp);

static void link_last(gxCellBlockList * gxlist, gxCellBlock * cbp);

static void unlink2(gxCellBlock * cbp);

static gxCellBlock *new_cell_block(gxCellBlockList * gxlist);

static void free_cell_block(gxCellBlock * cbp);

static int set_next_list(gxScanBuf * scan);

static gxCellBlockList *get_current_list(gxScanBuf * scan);

static int check_type(gxCell * cp, gxScanBuf * scan);

static void update_extent_for_insert(int si, unsigned r, unsigned c);

static void update_extent_for_remove(int si, unsigned r, unsigned c);

/* end of static prototypes for cell.c */


static void zero_cell(gxCell cells[], int index)
{
	memset(cells + index, 0, sizeof(gxCell));   /* zero out the cell */
	cells[index].block_index = index;   /* and set the index */
}


static gxCellBlock *cell_block_ptr(gxCell * cp)
/*
  Computes the address of the gxCellBlock structure containing cp.
*/
{
	gxCellBlock cbtemp;
	ptrdiff_t offset;
	offset = (char *) (cbtemp.cells + cp->block_index) - (char *) &cbtemp;
	return (gxCellBlock *) ((char *) cp - offset);
}


static void link_first(gxCellBlockList * gxlist, gxCellBlock * cbp)
/*
  Link cbp onto the head of the specified list.
*/
{
	cbp->next = gxlist->head;
	cbp->prev = NULL;
	if (cbp->next)
		cbp->next->prev = cbp;
	else
		gxlist->tail = cbp;
	gxlist->head = cbp;
	cbp->gxlist = gxlist;
}


static void link_last(gxCellBlockList * gxlist, gxCellBlock * cbp)
/*
  Link cbp onto the tail of the specified list.
*/
{
	cbp->prev = gxlist->tail;
	cbp->next = NULL;
	if (cbp->prev)
		cbp->prev->next = cbp;
	else
		gxlist->head = cbp;
	gxlist->tail = cbp;
	cbp->gxlist = gxlist;
}


static void unlink2(gxCellBlock * cbp)
/*
  Unlink cell block from the list specified internally.
*/
{
	assert(cbp != NULL);
	if (cbp->next != NULL)
		cbp->next->prev = cbp->prev;
	else
		cbp->gxlist->tail = cbp->prev;
	if (cbp->prev != NULL)
		cbp->prev->next = cbp->next;
	else
		cbp->gxlist->head = cbp->next;
	cbp->next = NULL;
	cbp->prev = NULL;
	cbp->gxlist = NULL;
}


static gxCellBlock *new_cell_block(gxCellBlockList * gxlist)
/*
  Allocate a new cell block and place it at the beginning of the list.
*/
{
	gxCellBlock *cbp;

	cbp = (gxCellBlock *) GX_XSmalloc(sizeof(gxCellBlock));
	link_first(gxlist, cbp);
	cbp->in_use = 0;
	cbp->frozen = 0;
	return cbp;
}


static void free_cell_block(gxCellBlock * cbp)
{
	assert(cbp != NULL);
	assert(cbp->in_use == 0);
	unlink2(cbp);
	GX_XSfree(cbp);
}


void  __cdecl _gx_free_cell_block_list(gxCellBlockList * gxlist)
{
	int i;
	int nany = 1;
	unsigned long bit_mask;
	while (1)
	{
		bit_mask = 1;
		nany = 0;
		for (i = 0; i < GX_CELL_BLOCK_SIZE; i++)
		{
			if (gxlist->head == NULL)
				return;
			if (gxlist->head->in_use & bit_mask)
			{
				_gx_free_cell(gxlist->head->cells + i);
				nany = 1;
			}
			bit_mask <<= 1;
		}
		if (nany == 0)
			free_cell_block(gxlist->head);
	}
}


gxCell * __cdecl _gx_copy_cell_to_list(gxCellBlockList * dst, gxCell * cp)
/*
 * Creates a duplicate of *cp in the specified list and also duplicates
 * any dynamic appendages (string and formula).
 *
 */
{
	int index_save;
	gxCell *newcell = _gx_new_cell(dst);
	index_save = newcell->block_index;
	*newcell = *cp; /* do a block copy */
	newcell->block_index = index_save;  /* put the correct block index back */
	if (cp->value_type == GX_VALUE_STRING)  /* duplicate dynamic appendages */
		newcell->value.string = _gx_xs_strdup(cp->value.string);
	if (cp->formula)
		newcell->formula = _gx_formula_dup(cp->formula);
	newcell->inserted = 0;  /* because it's not! */
	return newcell;
}


gxCell * __cdecl _gx_cell_dup(gxCell * cp)
{
	gxCell* dp = _gx_copy_cell_to_list(cell_block_ptr(cp)->gxlist, cp);

	if (cp->pStyle)
		dp->pStyle = cp->pStyle->Clone();

	return dp;
}


gxCell * __cdecl _gx_move_cell_to_list(gxCellBlockList * dst, gxCell * cp)
/*
 * Creates a duplicate of *cp in the specified list and frees the original
 * cell.
 *
 */
{
	gxCell *newcell = _gx_copy_cell_to_list(dst, cp);
	cp->pStyle = NULL;
	_gx_free_cell(cp);
	return newcell;
}


int  __cdecl _gx_new_sheet_context(void)
{
	int nSize = (int)GXGetEngineState()->m_apSheetContext.GetSize();
	int i;
	for (i = 0; i < nSize; i++)
	{
		if (GXGetEngineState()->m_apSheetContext[i] == NULL)
			break;
	}

	gxSheetContext *pContext = (gxSheetContext *) GX_XScalloc(1, sizeof(gxSheetContext));
	GXGetEngineState()->m_apSheetContext.SetAtGrow(i, pContext);

	pContext->cell_limit = 0;
	pContext->default_format = GX_FMT_TEXT;
	pContext->row_cell_count = NULL;
	pContext->col_cell_count = NULL;
	pContext->keep_empties = 0; /* keep empty cells after move or
										 * clear range */
	pContext->highwater_rowcount = 0;
	pContext->highwater_colcount = 0;

	return i + 1;
}

static void __cdecl _gx_grow_highwater_row_col(gxRowCol nNewSize, gxRowCol& nMaxSize, gxRowCol*& pData)
{
	ASSERT(nNewSize >= 0);

	if (pData == NULL)
	{
		// create one with exact size
		pData = new gxRowCol[nNewSize];

		memset(pData, 0, nNewSize * sizeof(gxRowCol));  // zero fill

		nMaxSize = nNewSize;
	}
	else if (nNewSize > nMaxSize)
	{
		// heuristically determine growth when nGrowBy == 0
		//  (this avoids heap fragmentation in many situations)
		int nGrowBy = min(1024, max(4, nMaxSize / 8));

		int nNewMax;
		if (nNewSize < nMaxSize + nGrowBy)
			nNewMax = nMaxSize + nGrowBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		gxRowCol* pNewData = new gxRowCol[nNewMax];

		// copy new data from old
		memcpy(pNewData, pData, nMaxSize * sizeof(gxRowCol));

		// construct remaining elements
		ASSERT(nNewSize > nMaxSize);

		// memset(&pNewData[nMaxSize], 0, (nNewSize-nMaxSize) * sizeof(gxRowCol));

		// get rid of old stuff (note: no destructors called)
		delete[] pData;
		pData = pNewData;
		nMaxSize = nNewMax;

		// TRACE(_T("newSize=%ld\n"), nMaxSize);
	}
}

void  __cdecl _gx_grow_highwater_row_count(int si, gxRowCol nNewSize)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
										
	_gx_grow_highwater_row_col(nNewSize, pContext->highwater_rowcount, pContext->row_cell_count);
}

void  __cdecl _gx_grow_highwater_col_count(int si, gxRowCol nNewSize)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];

	_gx_grow_highwater_row_col(nNewSize+1, pContext->highwater_colcount, pContext->col_cell_count);
}

void  __cdecl _gx_free_sheet_context(int si)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	assert(pContext != NULL);
	_gx_clear_recalc_rangelist(si);
	delete[] pContext->row_cell_count;
	delete[] pContext->col_cell_count;
	_gx_free_cell_block_list(&pContext->constant_list);
	_gx_free_cell_block_list(&pContext->recalc_list);
	_gx_free_cell_block_list(&pContext->empty_list);
	_gx_free_range_name_list(si);
	GX_XSfree(pContext);
	GXGetEngineState()->m_apSheetContext[si - 1] = NULL;
}


gxSheetContext * __cdecl _gx_get_context_ptr(int si)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	assert(pContext != NULL);
	return pContext;
}


/*
 * The following function ensures that all non-full CellBlocks are
 * at the beginning of the list.
 */

static void reorder_list(gxCellBlockList * gxlist)
{
	gxCellBlock *cbp,
			   *next;

	gxlist->freeze_order = 0;
	if (!gxlist->needs_reorder)
		return;

	cbp = gxlist->head;
	if (cbp != NULL)
		cbp = cbp->next;
	while (cbp != NULL)
	{
		cbp->frozen = 0;
		next = cbp->next;
		if (cbp->in_use == 0)
		{
			free_cell_block(cbp);
		}
		else if (cbp->in_use != GX_CELL_BLOCK_MASK)
		{
			unlink2(cbp);
			link_first(gxlist, cbp);
		}
		cbp = next;
	}
	gxlist->needs_reorder = 0;
}


int  __cdecl _gx_freeze_list_order(int si, int mask)
{
	int out_mask = 0;

	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];

	if (mask & GX_CONSTANT_LIST)
	{
		if (pContext->constant_list.freeze_order == 0)
			out_mask |= GX_CONSTANT_LIST;
		pContext->constant_list.freeze_order = 1;
	}
	if (mask & GX_RECALC_LIST)
	{
		if (pContext->recalc_list.freeze_order == 0)
			out_mask |= GX_RECALC_LIST;
		pContext->recalc_list.freeze_order = 1;
	}
	if (mask & GX_EMPTY_LIST)
	{
		if (pContext->empty_list.freeze_order == 0)
			out_mask |= GX_EMPTY_LIST;
		pContext->empty_list.freeze_order = 1;
	}
	return out_mask;
}


void  __cdecl _gx_unfreeze_list_order(int si, int mask)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];

	if (mask & GX_CONSTANT_LIST)
		reorder_list(&pContext->constant_list);
	if (mask & GX_RECALC_LIST)
		reorder_list(&pContext->recalc_list);
	if (mask & GX_EMPTY_LIST)
		reorder_list(&pContext->empty_list);
}


static gxCellBlock *find_non_full_block(gxCellBlockList * gxlist)
{
	gxCellBlock *cbp;

	for (cbp = gxlist->head; cbp != NULL; cbp = cbp->next)
		if (cbp->in_use != GX_CELL_BLOCK_MASK && cbp->frozen == 0)
			break;
	if (cbp == NULL)
		cbp = new_cell_block(gxlist);
	return cbp;
}

gxCell * __cdecl _gx_new_cell(gxCellBlockList * gxlist)
{
	gxCellBlock *cbp;
	unsigned long bit_mask;
	int i;

	if (gxlist->freeze_order)
	{
		cbp = find_non_full_block(gxlist);
	}
	else
	{
		cbp = gxlist->head;
		if (cbp == NULL || cbp->in_use == GX_CELL_BLOCK_MASK)
			cbp = new_cell_block(gxlist);
	}

	bit_mask = 1;
	for (i = 0; i < GX_CELL_BLOCK_SIZE; i++)
	{
		if (!(bit_mask & cbp->in_use))
		{   /* we found a free cell */
			cbp->in_use |= bit_mask;    /* mark the cell in use */
			if (cbp->in_use == GX_CELL_BLOCK_MASK)
			{
				if (gxlist->tail != cbp)
				{
					if (gxlist->freeze_order)
						gxlist->needs_reorder = 1;
					else
					{
						unlink2(cbp);
						link_last(gxlist, cbp);
					}
				}
			}
			zero_cell(cbp->cells, i);   /* initialize it */
			gxlist->_gx_cell_count++; /* increment the cell count */
			return cbp->cells + i;  /* and return it */
		}
		bit_mask <<= 1; /* try the next cell */
	}
	return NULL;
}


void __cdecl _gx_free_cell(gxCell * cp)
/*
  Makes calls to free any dynamic structures attached to the cell
  and then marks the cell not "in_use".  If this was the last used
  cell in its cell block, the entire cell block is freed.  Otherwise,
  the cell block is moved to the beginning of its list so that the
  empty cell can be found by  _gx_new_cell().
*/
{
	gxCellBlock *cbp;
	gxCellBlockList *gxlist;

	cbp = cell_block_ptr(cp);
	gxlist = cbp->gxlist;

	if (cp->pStyle)
		delete cp->pStyle;
	cp->pStyle = NULL;
	switch (cp->cell_type)
	{
	case GX_FORMULA_CELL:
	case GX_CONSTANT_FORMULA_CELL:
		_gx_free_formula(cp->formula);
		cp->formula = NULL;
		if (gxlist->freeze_order)
			cbp->frozen = 1;    /* so we won't reuse the freed cell while
								 * frozen */
		break;
	}
	switch (cp->value_type)
	{
	case GX_VALUE_STRING:
		GX_XSfree(cp->value.string);
		break;
	}
	cbp->in_use &= ~(1 << cp->block_index);
	assert(gxlist->_gx_cell_count > 0);
	--gxlist->_gx_cell_count;
	if (cbp->in_use == 0)
	{
		if (gxlist->freeze_order)
			gxlist->needs_reorder = 1;
		else
			free_cell_block(cbp);
	}
	else
	{
		if (gxlist->head != cbp)
		{
			if (gxlist->freeze_order)
				gxlist->needs_reorder = 1;
			else
			{
				unlink2(cbp);
				link_first(gxlist, cbp);
			}
		}
	}
}


gxCell * __cdecl _gx_find_cell(int si, int r, int c)
/*
  Looks up a cell row-column index in the sheet hash table
  and returns a pointer to the cell found, or NULL if there
  is no cell at that location in the sheet.
*/
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	gxCell *cp;

	assert(pContext);
	unsigned nHash = GX_HASH_FUNCTION(r, c);
	for (cp = pContext->hash[nHash];
		 cp != NULL; cp = cp->next)
		if (cp->row == (unsigned) r && cp->col == (unsigned) c)
			break;

	return (cp);
}


int  __cdecl _gx_insert_cell(int si, gxCell * cp)
/*
  Inserts the cell in the sheet hash table
*/
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	int hash_val = (int) GX_HASH_FUNCTION(cp->row, cp->col);

	assert(pContext);
	assert(GX_BOUNDS_CHECK((int) cp->row, (int) cp->col));
	cp->next = pContext->hash[hash_val];
	cp->inserted = 1;
	pContext->hash[hash_val] = cp;
	(pContext->_gx_cell_count)++;
	update_extent_for_insert(si, cp->row, cp->col);
	pContext->modified = 1;
	return 1;
}

void  __cdecl _gx_remove_cell(int si, gxCell * cp)
/*
 * Removes the cell from the sheet hash table but leaves its contents intact.
 */
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	gxCell **cpp;
	int flag = 0;
	assert(pContext);
	if (cp == NULL)
		return;
	for (cpp = &(pContext->hash[GX_HASH_FUNCTION(cp->row, cp->col)]);
		 (*cpp) != NULL; cpp = &((*cpp)->next))
	{
		if (*cpp == cp)
		{
			*cpp = cp->next;
			flag = 1;
			break;
		}
	}
	if (!flag)
		return; /* cell not found in sheet */
	assert(pContext->_gx_cell_count > 0);
	cp->inserted = 0;
	--(pContext->_gx_cell_count);
	// sheet_context[si-1]->extent_cache_valid = 0;
	update_extent_for_remove(si, cp->row, cp->col);
	pContext->modified = 1;
}

void  __cdecl _gx_destroy_cell(int si, gxCell * cp)
/*
  Removes the cell from the sheet hash table and frees its contents.
*/
{
	if (cp != NULL)
	{
		_gx_remove_cell(si, cp);
		_gx_free_cell(cp);
	}
}

CGXStyle * __cdecl SafeDetachStyle(gxCell * cp)
{
	CGXStyle *pStyle = NULL;
	if (cp)
	{
		pStyle = cp->pStyle;
		cp->pStyle = 0;
	}
	return pStyle;
}

void __cdecl AttachStyle(gxCell * cp, CGXStyle * pStyle)
{
	assert(cp);

	if (cp->pStyle)
		delete cp->pStyle;

	cp->pStyle = pStyle;
}

int  __cdecl _gx_cell_put_formula(int si, int r, int c, LPCTSTR formula,
							 gxCellProp *, gxCellValue * cv)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	gxCell *cp;
	// gxCellProp cprop1;
	// int pcode;
	gxFormula fm;

	assert(pContext);
	assert(GX_BOUNDS_CHECK(r, c));
	if (!GX_BOUNDS_CHECK(r, c))
		return 0;
	// Change made on 3/4/99
	// Moved _gx_parse_formula above _gx_destroy_cell. Otherwise, if parse_formula failed, 
	// the previous state of the cell was lost!
	if (!_gx_parse_formula(si, formula, &fm))
		return 0;

	GX_MARK_MODIFIED(si);
	cp = _gx_find_cell(si, r, c);
	CGXStyle *pStyle = SafeDetachStyle(cp);
	_gx_destroy_cell(si, cp);

	if ((fm.expression[fm.expr_start].node_type == GX_NUMBER_NODE) &&
		(!fm.expression[fm.expr_start].number_is_hex) &&
		(fm.cons_start == GX_ENULL) &&
		(fm.depend_start == GX_ENULL) &&
		(fm.comment == NULL))
	{
		cp = _gx_new_cell(&pContext->constant_list);
		cp->row = (gxRowCol) r;
		cp->col = (gxRowCol) c;
		cp->cell_type = GX_NUMERIC_CELL;
		cp->value_type = GX_VALUE_NUMERIC;
		cp->value.number = fm.expression[fm.expr_start].value.operand;
		GX_XSfree(fm.expression);
	}
//  else if ((fm.expression[fm.expr_start].node_type == GX_NUMBER_NODE) &&
//           (fm.comment == NULL))
//     {
//     CONVERT GX_STRING TO LABEL HERE, IF DESIRED
//     }
	else
	{
		if (_gx_references_cells(fm.expression, fm.expr_size) ||
			_gx_calls_functions(fm.expression, fm.expr_size))
		{
			cp = _gx_new_cell(&pContext->recalc_list);
			cp->cell_type = GX_FORMULA_CELL;
		}
		else
		{
			cp = _gx_new_cell(&pContext->constant_list);
			cp->cell_type = GX_CONSTANT_FORMULA_CELL;
		}
		cp->row = (gxRowCol) r;
		cp->col = (gxRowCol) c;
		cp->formula = (gxFormula *) GX_XSmalloc(sizeof(gxFormula));
		*(cp->formula) = fm;
		cp->value_type = GX_VALUE_NONE; // it will be determined later
		cp->serial = pContext->serial;
	}

	if (cp->cell_type == GX_FORMULA_CELL && cv != NULL)
	{
		_gx_set_cell_value(cp, cv);
		GX_CELL_SET_FLAG(cp, GX_VISITED | GX_UPDATED);  // so we know it is up
		// to date
	}
	cp->pStyle = pStyle;
	if (_gx_insert_cell(si, cp))
	{
		if (cp->cell_type == GX_CONSTANT_FORMULA_CELL)
			_gx_evaluate_cell(si, cp);
		return 1;
	}
	else
		return 0;
}

int  __cdecl _gx_cell_put_number(int si, int r, int c, gxNumber number, gxCellProp * )
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	gxCell *cp;

	assert(pContext);
	assert(GX_BOUNDS_CHECK(r, c));
	if (!GX_BOUNDS_CHECK(r, c))
		return 0;
	GX_MARK_MODIFIED(si);
	cp = _gx_find_cell(si, r, c);
	CGXStyle *pStyle = SafeDetachStyle(cp);
	_gx_destroy_cell(si, cp);
	cp = _gx_new_cell(&pContext->constant_list);
	cp->row = (gxRowCol) r;
	cp->col = (gxRowCol) c;
	cp->cell_type = GX_NUMERIC_CELL;
	cp->value_type = GX_VALUE_NUMERIC;
	cp->value.number = number;
	cp->pStyle = pStyle;
	return _gx_insert_cell(si, cp);
}


int  __cdecl _gx_cell_put_label(int si, int r, int c, LPCTSTR label, gxCellProp *)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	gxCell *cp;
	int len;
	TCHAR buf[GX_MAX_TEXT];

	assert(pContext);
	assert(GX_BOUNDS_CHECK(r, c));
	if (!GX_BOUNDS_CHECK(r, c))
	{
		return 0;
	}
	GX_MARK_MODIFIED(si);
	cp = _gx_find_cell(si, r, c);
	CGXStyle *pStyle = SafeDetachStyle(cp);
	if (cp)
	{
		_gx_destroy_cell(si, cp);
	}
	if (!pContext->v2_string_mode)
	{
		_gx_xs_decode_string(buf, label);   /* interpret escape codes */
	}else
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(buf, label);
	}
	cp = _gx_new_cell(&pContext->constant_list);
	cp->row = (gxRowCol) r;
	cp->col = (gxRowCol) c;
	cp->cell_type = GX_LABEL_CELL;
	cp->pStyle = pStyle;
	if ((len = (int)_tcslen(buf)) <= 8/sizeof(TCHAR))
	{   /* make it a short label */
		cp->value_type = GX_VALUE_SHORT_STRING;
		_gx_xs_short_strcpy(cp->value.short_string, buf, FALSE);
	}
	else
	{
		cp->value_type = GX_VALUE_STRING;
		cp->value.string = (LPTSTR) GX_XSmalloc((len + 1)*sizeof(TCHAR));
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(cp->value.string, buf);
	}
	return _gx_insert_cell(si, cp);
}

static int set_next_list(gxScanBuf * scan)
{
	if (scan->mask & GX_CONSTANT_LIST)
	{
		scan->current_mask = GX_CONSTANT_LIST;
		scan->mask &= ~GX_CONSTANT_LIST;
	}
	else if (scan->mask & GX_RECALC_LIST)
	{
		scan->current_mask = GX_RECALC_LIST;
		scan->mask &= ~GX_RECALC_LIST;
	}
	else if (scan->mask & GX_EMPTY_LIST)
	{
		scan->current_mask = GX_EMPTY_LIST;
		scan->mask &= ~GX_EMPTY_LIST;
	}
	else
		scan->current_mask = 0;
	return scan->current_mask;
}


static gxCellBlockList *get_current_list(gxScanBuf * scan)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[scan->si - 1];
	if (scan->current_mask == GX_CONSTANT_LIST)
		return &pContext->constant_list;
	else if (scan->current_mask == GX_RECALC_LIST)
		return &pContext->recalc_list;
	else if (scan->current_mask == GX_EMPTY_LIST)
		return &pContext->empty_list;
	else
		return NULL;
}


static int check_type(gxCell * cp, gxScanBuf * scan)
/*
 * Used in type 1 range scans to see if cell type matches the
 * mask specified in _gx_init_range_scan().
 */
{
	gxCellBlockList *gxlist;

	if (cp == NULL)
		return 0;
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[scan->si - 1];
	gxlist = cell_block_ptr(cp)->gxlist;
	if ((scan->mask & GX_CONSTANT_LIST) &&
		(gxlist == &pContext->constant_list))
		return 1;
	else if ((scan->mask & GX_RECALC_LIST) &&
			 (gxlist == &pContext->recalc_list))
		return 1;
	else if ((scan->mask & GX_EMPTY_LIST) &&
			 (gxlist == &pContext->empty_list))
		return 1;
	else
		return 0;
}


unsigned  __cdecl _gx_cell_count(int si, unsigned mask)
{
	int count = 0;

	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	if (mask & GX_CONSTANT_LIST)
		count += pContext->constant_list._gx_cell_count;
	if (mask & GX_RECALC_LIST)
		count += pContext->recalc_list._gx_cell_count;
	if (mask & GX_EMPTY_LIST)
		count += pContext->empty_list._gx_cell_count;

	return count;
}


void  __cdecl _gx_init_range_scan(int si, gxRange range, gxScanBuf * scan, unsigned mask)
{
	int range_size = (range.r1 - range.r0 + 1) * (range.c1 - range.c0 + 1);
	int count;

	assert(GX_IS_SORTED(range));
	scan->si = si;
	scan->range = range;
	scan->mask = mask;

	count = _gx_cell_count(si, mask);

	if (range_size < count)
	{
		scan->type = 1;
		scan->row = range.r0 - 1;
		scan->col = range.c0;
	}
	else
	{
		scan->type = 2;
		set_next_list(scan);
		assert(scan->current_mask != 0);
		scan->cb = get_current_list(scan)->head;
		scan->bitmask = 1;
		scan->index = 0;
	}
}


gxCell * __cdecl _gx_do_range_scan(gxScanBuf * scan)
{
	gxCell *cp = NULL;
	switch (scan->type)
	{
	case 0:
		return NULL;
	case 1:
		while (!check_type(cp, scan))
		{
			if (++scan->row > scan->range.r1)
			{
				scan->row = scan->range.r0;
				if (++scan->col > scan->range.c1)
				{
					scan->type = 0;
					return NULL;
				}
			}
			cp = _gx_find_cell(scan->si, scan->row, scan->col);
		}
		return cp;
	case 2:
		while (scan->cb == NULL)
		{
			if (set_next_list(scan) == 0)
			{
				scan->type = 0;
				return NULL;
			}
			else
			{
				scan->cb = get_current_list(scan)->head;
			}
		}
		while (cp == NULL)
		{
			if (scan->index >= GX_CELL_BLOCK_SIZE)
			{
				scan->cb = scan->cb->next;
				while (scan->cb == NULL)
				{
					if (set_next_list(scan) == 0)
					{
						scan->type = 0;
						return NULL;
					}
					else
					{
						scan->cb = get_current_list(scan)->head;
					}
				}
				scan->index = 0;
				scan->bitmask = 1;
				if (!scan->cb->in_use)
					continue;
			}
			if (scan->cb->in_use & scan->bitmask)
			{
				cp = scan->cb->cells + scan->index;
				if (!cp->inserted || !GX_IN_RANGE(scan->range, cp->row, cp->col))
					cp = NULL;
			}
			++scan->index;
			scan->bitmask <<= 1;
		}
		return cp;
	default:
		assert(!scan->type);
	}
	return NULL;
}


void  __cdecl _gx_init_cell_list_scan(gxCellBlockList * gxlist, gxScanBuf * scan)
{
	scan->type = 3;
	scan->gxlist = gxlist;
	scan->cb = gxlist->head;
	scan->bitmask = 1;
	scan->index = 0;
}


gxCell * __cdecl _gx_do_cell_list_scan(gxScanBuf * scan)
{
	gxCell *cp = NULL;
	switch (scan->type)
	{
	case 3:
		if (scan->cb == NULL)
		{
			scan->type = 0;
			return NULL;
		}
		while (cp == NULL)
		{
			if (scan->index >= GX_CELL_BLOCK_SIZE)
			{
				scan->cb = scan->cb->next;
				if (scan->cb == NULL)
				{
					scan->type = 0;
					return NULL;
				}
				scan->index = 0;
				scan->bitmask = 1;
				if (!scan->cb->in_use)
					continue;
			}
			if (scan->cb->in_use & scan->bitmask)
				cp = scan->cb->cells + scan->index;
			++scan->index;
			scan->bitmask <<= 1;
		}
		return cp;
	default:
		return NULL;
	}
}

static void update_extent_for_insert(int si, unsigned r, unsigned c)
{
	gxSheetContext *context = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	_gx_grow_highwater_row_count(si, r);
	_gx_grow_highwater_col_count(si, c);
	context->row_cell_count[r - GX_MIN_ROW]++;
	context->col_cell_count[c - GX_MIN_COL]++;
	if (context->extent_cache_valid)
	{
		context->extent_cache.r0 = GX_MIN(context->extent_cache.r0, r);
		context->extent_cache.r1 = GX_MAX(context->extent_cache.r1, r);
		context->extent_cache.c0 = GX_MIN(context->extent_cache.c0, c);
		context->extent_cache.c1 = GX_MAX(context->extent_cache.c1, c);
	}
	else
	{
		context->extent_cache.r0 = r;
		context->extent_cache.r1 = r;
		context->extent_cache.c0 = c;
		context->extent_cache.c1 = c;
		context->extent_cache_valid = 1;
	}
}


static void update_extent_for_remove(int si, unsigned r, unsigned c)
{
	gxSheetContext *context = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	_gx_grow_highwater_row_count(si, r);
	_gx_grow_highwater_col_count(si, c);
	assert(context->row_cell_count[r - GX_MIN_ROW] > 0);
	assert(context->col_cell_count[c - GX_MIN_COL] > 0);
	if (--(context->row_cell_count[r - GX_MIN_ROW]) == 0)
	{
		if (r == context->extent_cache.r0)
		{   /* on extent min boundary */
			while (++r <= context->extent_cache.r1) /* find next non-empty
													 * row */
				if (context->row_cell_count[r - GX_MIN_ROW] > 0)
					break;
			if (r <= context->extent_cache.r1)
				context->extent_cache.r0 = r;
			else
			{   /* sheet is empty */
				context->extent_cache_valid = 0;
				return;
			}
		}
		else if (r == context->extent_cache.r1)
		{   /* on extent max boundary */
			while (--r >= context->extent_cache.r0) /* find prev non-empty
													 * row */
				if (context->row_cell_count[r - GX_MIN_ROW] > 0)
					break;
			if (r >= context->extent_cache.r0)
				context->extent_cache.r1 = r;
			else
			{   /* sheet is empty */
				context->extent_cache_valid = 0;
				return;
			}
		}
	}
	if (--(context->col_cell_count[c - GX_MIN_COL]) == 0)
	{
		if (c == context->extent_cache.c0)
		{   /* on extent min boundary */
			while (++c <= context->extent_cache.c1) /* find next non-empty
													 * col */
				if (context->col_cell_count[c - GX_MIN_COL] > 0)
					break;
			if (c <= context->extent_cache.c1)
				context->extent_cache.c0 = c;
			else
			{   /* sheet is empty */
				context->extent_cache_valid = 0;
				return;
			}
		}
		else if (c == context->extent_cache.c1)
		{   /* on extent max boundary */
			while (--c >= context->extent_cache.c0) /* find prev non-empty
													 * col */
				if (context->col_cell_count[c - GX_MIN_COL] > 0)
					break;
			if (c >= context->extent_cache.c0)
				context->extent_cache.c1 = c;
			else
			{   /* sheet is empty */
				context->extent_cache_valid = 0;
				return;
			}
		}
	}
}


int  __cdecl _gx_get_sheet_extent(int si, gxRange * all)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	if (pContext->extent_cache_valid)
	{
		*all = pContext->extent_cache;
		return 1;
	}
	else
		return 0;
}


int  __cdecl _gx_limit_to_extent(int si, gxRange * rng)
{
	gxRange all;
	if (_gx_get_sheet_extent(si, &all) == 0)
		return 0;
	if (!_gx_intersect(rng, &all))
		return 0;
	rng->r0 = GX_MAX(rng->r0, all.r0);
	rng->r1 = GX_MIN(rng->r1, all.r1);
	rng->c0 = GX_MAX(rng->c0, all.c0);
	rng->c1 = GX_MIN(rng->c1, all.c1);
	return 1;
}


void  __cdecl _gx_replace_cell_formula(gxCell * cp, gxFormula * fm)
{
	_gx_free_formula(cp->formula);
	cp->formula = _gx_formula_dup(fm);
}

gxCell * __cdecl _gx_insert_empty_cell(int si, int r, int c, gxCellProp *)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	gxCell *newcell = _gx_new_cell(&pContext->empty_list);
	newcell->row = (gxRowCol) r;
	newcell->col = (gxRowCol) c;
	_gx_insert_cell(si, newcell);
	return newcell;
}


gxCell * __cdecl _gx_get_cell_value(int si, int r, int c, gxCellValue * cv)
{
	gxCell *cp;
	int mask;

	assert(GX_BOUNDS_CHECK(r, c));
	if ((cp = _gx_find_cell(si, r, c)) == NULL)
		cv->type = GX_VALUE_NONE;
	else
	{
		if (cp->cell_type == GX_FORMULA_CELL && !GX_CELL_TEST_FLAG(cp, GX_VISITED))
		{
			mask = _gx_freeze_list_order(si, GX_ALL_LISTS);
			_gx_back_calc(si, cp);  /* make sure the value is current */
			_gx_unfreeze_list_order(si, mask);
		}
		cv->type = cp->value_type;
		switch (cv->type)
		{
		case GX_VALUE_NUMERIC:
			cv->value.number = cp->value.number;
			break;
		case GX_VALUE_STRING:
			cv->value.string = _gx_xs_strdup(cp->value.string);
			break;
		case GX_VALUE_SHORT_STRING:
			cv->value.string = _gx_xs_short_strdup(cp->value.short_string);
			cv->type = GX_VALUE_STRING;
			break;
		}
	}
	return cp;
}


void  __cdecl _gx_set_cell_value(gxCell * cp, gxCellValue * cv)
{
	int len;
	if (cp->value_type == GX_VALUE_STRING)
		GX_XSfree(cp->value.string);    /* free the old string */
	switch (cv->type)
	{
	case GX_VALUE_NUMERIC:
		cp->value.number = cv->value.number;
		cp->value_type = GX_VALUE_NUMERIC;
		break;
	case GX_VALUE_STRING:
		if ((len = (int)_tcslen(cv->value.string)) <= 8/sizeof(TCHAR))
		{
			_gx_xs_short_strcpy(cp->value.short_string, cv->value.string, FALSE);
			cp->value_type = GX_VALUE_SHORT_STRING;
		}
		else
		{
			if (len < GX_MAX_TEXT)
			{
				cp->value.string = (LPTSTR) GX_XSmalloc((len + 1)*sizeof(TCHAR));
				// QA: 31989 - #if Secure Code Cleanup.
				_tcscpy(cp->value.string, cv->value.string);
			}
			else
			{
				cp->value.string = (LPTSTR) GX_XSmalloc(GX_MAX_TEXT*sizeof(TCHAR));
				// QA: 31989 - #if Secure Code Cleanup.
				_tcsncpy(cp->value.string, cv->value.string, GX_MAX_TEXT - 1);
				cp->value.string[GX_MAX_TEXT - 1] = _T('\0');
			}
			cp->value_type = GX_VALUE_STRING;
		}
		break;
	default:
		cp->value_type = cv->type;  /* Error and N/A */
	}
}



/*
 * Recalc Options interface functions
 */


int  __cdecl _gx_set_recalc_mode(int si, int mode)
{
	assert(mode == GX_RECALC_AUTO || mode == GX_RECALC_MANUAL);
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	if (mode == GX_RECALC_AUTO || mode == GX_RECALC_MANUAL)
	{
		pContext->recalc_mode = mode;
		return 1;
	}
	else
		return 0;
}


int  __cdecl _gx_get_recalc_mode(int si)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	return pContext->recalc_mode;
}


int  __cdecl _gx_set_recalc_method(int si, int method)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	assert(method == GX_RECALC_AS_NEEDED || method == GX_RECALC_FOREGROUND);
	if (method == GX_RECALC_AS_NEEDED || method == GX_RECALC_FOREGROUND)
	{
		pContext->recalc_method = method;
		return 1;
	}
	else
		return 0;
}


int  __cdecl _gx_get_recalc_method(int si)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	return pContext->recalc_method;
}


int  __cdecl _gx_set_constraint_check(int si, int toggle)
{
	assert(toggle == 0 || toggle == 1);
	if (toggle == 0 || toggle == 1)
	{
		gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
		pContext->constraint_check = toggle;
		return 1;
	}
	else
		return 0;
}


int  __cdecl _gx_get_constraint_check(int si)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	return pContext->constraint_check;
}


int  __cdecl _gx_set_blanks_are_zeros(int si, int toggle)
{
	assert(toggle == 0 || toggle == 1);
	if (toggle == 0 || toggle == 1)
	{
		gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
		pContext->blanks_are_zeros = toggle;
		return 1;
	}
	else
		return 0;
}


int  __cdecl _gx_get_blanks_are_zeros(int si)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	return pContext->blanks_are_zeros;
}


int  __cdecl _gx_set_iteration_limit(int si, int limit)
{
	assert(limit >= 0 && limit <= GX_RECALC_MAX_ITER);
	if (limit >= 0 && limit <= GX_RECALC_MAX_ITER)
	{
		gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
		pContext->iteration_limit = limit;
		return 1;
	}
	else
		return 0;
}

int  __cdecl _gx_get_iteration_limit(int si)
{
	gxSheetContext *pContext = (gxSheetContext *) GXGetEngineState()->m_apSheetContext[si - 1];
	return pContext->iteration_limit;
}

LPCTSTR  __cdecl _gx_get_formatted_text(int si, gxCell * cp, gxCellProp *)
{
	_gx_get_context_ptr(si)->m_pSheetContext->GetCellText(cp, GXGetEngineState()->text_buf);

	if (cp->pStyle && cp->pStyle->GetIncludeFormat()
		&& cp->value_type == GX_VALUE_NUMERIC)
	{
		GXGetEngineState()->text_buf 
			= GXFormatText(*cp->pStyle, GXGetEngineState()->text_buf, GX_VT_NUMERIC);
	}

	return GXGetEngineState()->text_buf;
}
