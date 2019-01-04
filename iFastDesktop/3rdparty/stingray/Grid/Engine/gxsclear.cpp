///////////////////////////////////////////////////////////////////////////////
// gxsclear.cpp: empty range of cells
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

extern void __cdecl _gx_preserve_raw(int si, gxCell * cp);


int  __cdecl _gx_clear_range(int si, gxRange dst)
{
	gxCell *cp,
		  *next_cell,
		  *remove_list = NULL;
	gxSheetContext *context = _gx_get_context_ptr(si);
	gxScanBuf scan;
	gxRange dst2;

	dst2 = dst;
	if (!_gx_limit_to_extent(si, &dst2))
		return 0;

	GX_MARK_MODIFIED(si);

	int mask = _gx_freeze_list_order(si, GX_ALL_LISTS);

	_gx_init_range_scan(si, dst2, &scan, GX_CONSTANT_LIST | GX_RECALC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
	{
		_gx_check_tool_neighborhood(si, cp);

		_gx_remove_cell(si, cp);
		if (context->keep_empties)
		{
			gxCell* ip = _gx_insert_empty_cell(si, cp->row, cp->col, NULL);
			GX_CELL_SET_FLAG(ip, GX_UPDATED);
		}
		if (context->do_preserve)
			_gx_preserve_raw(si, cp);
		else
		{
			cp->next = remove_list;
			remove_list = cp;
		}
	}

	for (cp = remove_list; cp != NULL; cp = next_cell)
	{
		next_cell = cp->next;
		_gx_free_cell(cp);
	}

	_gx_add_recalc_range(si, &dst);
	// _gx_recalc(si);

	_gx_unfreeze_list_order(si, mask);

	return 1;
}
