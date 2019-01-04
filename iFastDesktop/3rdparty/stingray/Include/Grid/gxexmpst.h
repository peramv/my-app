///////////////////////////////////////////////////////////////////////////////
// gxexmpst.h
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


#ifndef _GX_EX__MP_SET_H__
#define _GX_EX__MP_SET_H__

#include "grid\gxexhdr.h"
#include "grid\gxexman.h"
#include "grid\gxexhnd.h"
#include "grid\gxextbl.h"
#include "grid\gxexmap.h"
#include <StingrayExportDefs.h>

typedef CGXExcelMap<CGXExcelHandler> CGXHandlerMap;
typedef CGXExcelMap<CGXExcelTable>	CGXTableMap;

typedef CGXExcelMapImpl<CGXExcelHandler> CGXHandlerMapImpl;
typedef CGXExcelMapImpl<CGXExcelTable>	CGXTableMapImpl;

GRID_API CGXHandlerMap* GXExGetHandlerMap();
GRID_API CGXTableMap* GXExGetTableMap();

class CGXExMapHolder
{
public:
	// construction
	GRID_API CGXExMapHolder();
	GRID_API ~CGXExMapHolder();

	// access
	GRID_API void SetHandlerMap(CGXHandlerMap* pHandlerMap);
	GRID_API void SetTableMap(CGXTableMap* pTableMap);

	GRID_API CGXHandlerMap* GetHandlerMap() const;
	GRID_API CGXTableMap*  GetTableMap() const;

protected:
	// data
	CGXHandlerMap*	m_pHandlerMap;
	CGXTableMap*	m_pTableMap;
};

#endif
