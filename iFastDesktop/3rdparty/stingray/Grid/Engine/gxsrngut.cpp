///////////////////////////////////////////////////////////////////////////////
// gxsrngn.cpp: Range Utilities
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

static int base26_convert(TCHAR c)
{  /* converts a base-26 digit a-z or A-Z */
	if (c >= _T('a') && c <= _T('z'))
		return (c - _T('a'));
	if (c >= _T('A') && c <= _T('Z'))
		return (c - _T('A'));
	return (-1);
}

/*static int nShiftCol = 0, nShiftRow = 0;
void __cdecl _gx_set_shifts(int nRow1, int nCol1)
{
	nShiftRow = nRow1 - 1;
	nShiftCol = nCol1 - 1;
}

int __cdecl _gx_get_row_shift(){return nShiftRow;} 

int __cdecl _gx_get_col_shift(){return nShiftCol;} */

LPCTSTR  __cdecl _gx_col_to_text(unsigned int col)
{
	// static TCHAR alpha[4],
	register LPTSTR t = GXGetEngineState()->_gx_col_to_text_alpha;

	if (col <= GX_MAX_COL)
	{
		// Column header in format A, B, ..., AA, ..., AAA, ... ZZZZZ
		TCHAR s[10];
		int n;
		for (n = 0; n < 9; n++)
		{
			s[n] = (TCHAR) ((col%26) + _T('A'));	
			if ((col = col/26) == 0)
				break;
			col--;	// Changed to fix the col-text transulation bug.
		}

		// reverse string
		int i;
		for (i = 0; i < n+1; i++)
			t[i] = s[n-i];
		t[i] = 0;

//		if (n > 0)	// Changed to fix the col-text transulation bug
//			t[0]--;

		return (GXGetEngineState()->_gx_col_to_text_alpha);
	}
	else
		return NULL;
}


LPCTSTR  __cdecl _gx_rc_to_text(int r, int c)
{
	// QA: 31989 - #if Secure Code Cleanup.
	_stprintf(GXGetEngineState()->_gx_rc_to_text_id, _T("%s%d"), _gx_col_to_text(c), r);
	return (GXGetEngineState()->_gx_rc_to_text_id);
}

// Convert text to col. number.
// Example: AXZ = 1 * 26^2 + 24 * 26^1 + 26 * 26^0	= 1326

int  __cdecl _gx_text_to_col(LPCTSTR name)
{
	int c;
	c = base26_convert(*name++);
	while (c != -1 && _istalpha(*name))
	{
		if (c > 25)
			c = c * 26;
		else
			c = (c + 1) * 26;
		c += (base26_convert(*name++) + 1);	// Changed to fix the col-text transulation bug.
	}
	if (c > GX_MAX_COL || _istalpha(*name))
		c = -1;
	if(c > 25) c--;		// Changed to fix the col-text transulation bug.
	return (c);
}

int  __cdecl _gx_text_to_rc(LPCTSTR name, int *row, int *col)
/*
  convert ASCII cell name to row, col
*/
{
	int r,
		c;
	LPCTSTR n = name;
	if (*n == _T('$'))
		n++;
	c = _gx_text_to_col(n);
	if (!GX_VALID_COL(c))
		return 0;
	while (_istalpha(*(++n)));
	if (*n == _T('$'))
		n++;
	r = _ttoi(n);
	if (!GX_VALID_ROW(r))
		return 0;
	*row = r;
	*col = c;
	return 1;
}

int  __cdecl _gx_text_to_range(LPCTSTR name, gxRange * range)
{
	gxRange tmp_rng;
	int r_temp,
		c_temp;
	tmp_rng.abs_r0 = tmp_rng.abs_r1 = tmp_rng.abs_c0 = tmp_rng.abs_c1 = 0;
	if (*name == _T('$'))
	{
		tmp_rng.abs_c0 = 1; /* absolute column */
		name++;
	}
	c_temp = _gx_text_to_col(name);
	if (!GX_VALID_COL(c_temp))
		return 0;
	tmp_rng.c0 = c_temp;
	while (_istalpha(*(++name)));
	if (*name == _T('$'))
	{
		tmp_rng.abs_r0 = 1; /* absolute row */
		name++;
	}
	r_temp = _ttoi(name);
	if (!GX_VALID_ROW(r_temp))
		return 0;
	tmp_rng.r0 = r_temp;
	while (_istdigit(*(++name)));
	if (*name == _T('\0'))
	{
		tmp_rng.cell_only = 1;
		tmp_rng.r1 = tmp_rng.r0;
		tmp_rng.c1 = tmp_rng.c0;
	}
	else
	{
		tmp_rng.cell_only = 0;
		if (*name == _T('.') || *name == _T(':'))
			name++;
		else
			return 0;   /* must have at least one '.' here */
		if (*name == _T('.'))
			name++;
		if (*name == _T('$'))
		{
			tmp_rng.abs_c1 = 1; /* absolute column */
			name++;
		}
		c_temp = _gx_text_to_col(name);
		if (!GX_VALID_COL(c_temp))
			return 0;
		tmp_rng.c1 = c_temp;
		while (_istalpha(*(++name)));
		if (*name == _T('$'))
		{
			tmp_rng.abs_r1 = 1; /* absolute row */
			name++;
		}
		r_temp = _ttoi(name);
		if (!GX_VALID_ROW(r_temp))
			return 0;
		tmp_rng.r1 = r_temp;
		while (_istdigit(*(++name)));
	}
	if (*name != _T('\0'))
		return 0;   /* leftover characters at the end! */
	if (!GX_BOUNDS_CHECK(tmp_rng.r0, tmp_rng.c0) ||
		!GX_BOUNDS_CHECK(tmp_rng.r1, tmp_rng.c1))
		return 0;
	else
	{
		_gx_sort_range(&tmp_rng);
/*		if(tmp_rng.r0 >= 1 && tmp_rng.c0 >= 0)
		{
			tmp_rng.r0 += nShiftRow;
			tmp_rng.r1 += nShiftRow;
		        tmp_rng.c0 += nShiftCol;
			tmp_rng.c1 += nShiftCol;
		} */
		*range = tmp_rng;
		return 1;
	}
}

int  __cdecl _gx_si_text_to_range(int si, LPCTSTR name, gxRange * range)
{
	int status;

	status = _gx_text_to_range(name, range);
	if (!status)
		status = (_gx_range_name_lookup(si, name, range) != NULL);
	return status;
}

LPCTSTR  __cdecl _gx_range_to_text(gxRange * range)
{
	LPTSTR text = GXGetEngineState()->_gx_range_to_text_buf;
	TCHAR cell[12];
	if (!GX_BOUNDS_CHECK(range->r0, range->c0))
		return NULL;
	if (!range->cell_only && !GX_BOUNDS_CHECK(range->r1, range->c1))
		return NULL;
	
	switch ((range->abs_r0 << 1) | range->abs_c0)
	{
	case 0: /* relative row and col */
		// QA: 31989 - #if Secure Code Cleanup.
//		_stprintf(cell, _T("%s%d"), _gx_col_to_text(range->c0 - nShiftCol), range->r0 - nShiftRow );
		_stprintf(cell, _T("%s%d"), _gx_col_to_text(range->c0), range->r0);
		break;
	case 1: /* relative row, absolute col */
		// QA: 31989 - #if Secure Code Cleanup.
//		_stprintf(cell, _T("$%s%d"), _gx_col_to_text(range->c0 - nShiftCol), range->r0 - nShiftRow);
		_stprintf(cell, _T("$%s%d"), _gx_col_to_text(range->c0), range->r0);
		break;
	case 2: /* absolute row, relative col */
		// QA: 31989 - #if Secure Code Cleanup.
//		_stprintf(cell, _T("%s$%d"), _gx_col_to_text(range->c0 - nShiftCol), range->r0 - nShiftRow);
		_stprintf(cell, _T("%s$%d"), _gx_col_to_text(range->c0), range->r0);
		break;
	case 3: /* absolute row and col */
		// QA: 31989 - #if Secure Code Cleanup.
//		_stprintf(cell, _T("$%s$%d"), _gx_col_to_text(range->c0 - nShiftCol), range->r0 - nShiftRow);
		_stprintf(cell, _T("$%s$%d"), _gx_col_to_text(range->c0), range->r0);
		break;
	}

	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(text, cell);

	if (!range->cell_only)
	{   /* This is a range, not just a cell */
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscat(text, _T(".."));
		switch ((range->abs_r1 << 1) | range->abs_c1)
		{
		case 0: /* relative row and col */
			// QA: 31989 - #if Secure Code Cleanup.
//			_stprintf(cell, _T("%s%d"), _gx_col_to_text(range->c1 - nShiftCol), range->r1 - nShiftRow);
			_stprintf(cell, _T("%s%d"), _gx_col_to_text(range->c1), range->r1);
			break;
		case 1: /* relative row, absolute col */
			// QA: 31989 - #if Secure Code Cleanup.
//			_stprintf(cell, _T("$%s%d"), _gx_col_to_text(range->c1 - nShiftCol), range->r1 - nShiftRow);
			_stprintf(cell, _T("$%s%d"), _gx_col_to_text(range->c1), range->r1);
			break;
		case 2: /* absolute row, relative col */
			// QA: 31989 - #if Secure Code Cleanup.
//			_stprintf(cell, _T("%s$%d"), _gx_col_to_text(range->c1 - nShiftCol), range->r1 - nShiftRow);
			_stprintf(cell, _T("%s$%d"), _gx_col_to_text(range->c1), range->r1);
			break;
		case 3: /* absolute row and col */
			// QA: 31989 - #if Secure Code Cleanup.
//			_stprintf(cell, _T("$%s$%d"), _gx_col_to_text(range->c1 - nShiftCol), range->r1 - nShiftRow);
			_stprintf(cell, _T("$%s$%d"), _gx_col_to_text(range->c1), range->r1);
			break;
		}
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscat(text, cell);
	}
	return (text);
}

int  __cdecl _gx_sort_range(gxRange * range)
{
	int temp;
	if (!GX_BOUNDS_CHECK(range->r0, range->c0))
		return 0;
	if (!range->cell_only && !GX_BOUNDS_CHECK(range->r1, range->c1))
		return 0;
	if (range->cell_only)
	{
		range->r1 = range->r0;
		range->c1 = range->c0;
		range->abs_r1 = range->abs_r0;
		range->abs_c1 = range->abs_c0;
	}
	else
	{
		if (range->r1 < range->r0)
		{
			temp = range->r0;
			range->r0 = range->r1;
			range->r1 = temp;
			temp = range->abs_r0;
			range->abs_r0 = range->abs_r1;
			range->abs_r1 = temp;
		}
		if (range->c1 < range->c0)
		{
			temp = range->c0;
			range->c0 = range->c1;
			range->c1 = temp;
			temp = range->abs_c0;
			range->abs_c0 = range->abs_c1;
			range->abs_c1 = temp;
		}
	}
	return 1;
}


int  __cdecl _gx_intersect(gxRange * rp0, gxRange * rp1)
{  /* determine if two ranges _gx_intersect */
	assert(GX_IS_SORTED(*rp0));
	assert(GX_IS_SORTED(*rp1));
	if (rp0->c1 < rp1->c0)
		return 0;
	if (rp1->c1 < rp0->c0)
		return 0;
	if (rp0->r1 < rp1->r0)
		return 0;
	if (rp1->r1 < rp0->r0)
		return 0;
	return 1;
}


int  __cdecl _gx_intersection(gxRange * rp1, gxRange * rp2, gxRange * result)
{
	if (!_gx_intersect(rp1, rp2))
		return 0;
	result->r0 = GX_MAX(rp1->r0, rp2->r0);
	result->c0 = GX_MAX(rp1->c0, rp2->c0);
	result->r1 = GX_MIN(rp1->r1, rp2->r1);
	result->c1 = GX_MIN(rp1->c1, rp2->c1);
	return 1;
}

int  __cdecl _gx_same_range(gxRange * rp0, gxRange * rp1)
{
	if (rp0->r0 == rp1->r0 && rp0->r1 == rp1->r1 &&
		rp0->c0 == rp1->c0 && rp0->c1 == rp1->c1)
		return 1;
	else
		return 0;
}


gxRange  __cdecl _gx_make_range(int r0, int c0, int r1, int c1, int abs_mask)
{
	gxRange newrange;

	if (abs_mask & GX_CELL_ONLY)
		return _gx_make_cell(r0, c0, abs_mask); /* version 2 compatible */

	newrange.r0 = GX_VALID_ROW(r0) ? r0 : 0;
	newrange.c0 = GX_VALID_COL(c0) ? c0 : 0;
	newrange.r1 = GX_VALID_ROW(r1) ? r1 : 0;
	newrange.c1 = GX_VALID_COL(c1) ? c1 : 0;

	newrange.abs_r0 = abs_mask & GX_ABS_R0 ? 1 : 0;
	newrange.abs_c0 = abs_mask & GX_ABS_C0 ? 1 : 0;
	newrange.abs_r1 = abs_mask & GX_ABS_R1 ? 1 : 0;
	newrange.abs_c1 = abs_mask & GX_ABS_C1 ? 1 : 0;

	newrange.cell_only = 0;

	_gx_sort_range(&newrange);

	return newrange;
}


gxRange  __cdecl _gx_make_cell(int r, int c, int abs_mask)
{
	gxRange newrange;

	newrange.r0 = newrange.r1 = GX_VALID_ROW(r) ? r : 0;
	newrange.c0 = newrange.c1 = GX_VALID_COL(c) ? c : 0;

	newrange.abs_r0 = newrange.abs_r1 = abs_mask & GX_ABS_R0 ? 1 : 0;
	newrange.abs_c0 = newrange.abs_c1 = abs_mask & GX_ABS_C0 ? 1 : 0;

	newrange.cell_only = 1;

	return newrange;
}


void  __cdecl _gx_purify_range(gxRange * range)
{
	range->abs_r0 = range->abs_r1 = range->abs_c0 = range->abs_c1 = 0;
	range->cell_only = 0;
	_gx_sort_range(range);
}

void  __cdecl _gx_init_range(gxRange * range)
{
	range->abs_r0 = range->abs_r1 = range->abs_c0 = range->abs_c1 = 0;
	range->cell_only = 0;

	range->r0 = 0; range->r1 = 0; range->c0 = 0; range->c1 = 0;
}
