///////////////////////////////////////////////////////////////////////////////
// gxparcop.cpp : implementation copy operator for CGXGridParam class
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

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"
#endif

#ifndef _GXDELAYR_H_
#include "grid\gxdelayr.h"
#endif

#include "grid\gxpriv.h"

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXPARAM")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// CGXAbstractGridParamCopyOperatorImp* m_pParamCopyOperatorImp

class CGXGridParamCopyOperatorImp: public CGXAbstractGridParamCopyOperatorImp
{
public:
	virtual void CopyObject(CGXProperties* pDest, const CGXProperties& p);
	virtual void CopyObject(CGXStylesMap* pDest, const CGXStylesMap& p);
	virtual void CopyObject(CGXGridParam* pDest, const CGXGridParam& p);
};


void AFXAPI CGXGridParam::ImplementCopyOperator()
{
	if (GXGetAppData()->m_pParamCopyOperatorImp == NULL)
	{
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pParamCopyOperatorImp = new CGXGridParamCopyOperatorImp);
		GXGetAppData()->m_pParamCopyOperatorImp = new CGXGridParamCopyOperatorImp;
	}
}

//


void CGXGridParamCopyOperatorImp::CopyObject(CGXGridParam* pDest, const CGXGridParam& p)
{
	ASSERT_VALID(pDest);

	if (&p == pDest)
		return;
	
	// cleanup owned objects
	if (pDest->m_bOwnStylesMap)
	{
		delete pDest->m_pStylesMap;
		pDest->m_pStylesMap = NULL;
	}

	if (pDest->m_bOwnData)
	{
		delete pDest->m_pData;
		pDest->m_pData = NULL;
	}

	if (pDest->m_bOwnProperties)
	{
		delete pDest->m_pProperties;
		pDest->m_pProperties = NULL;
	}

	if (pDest->m_bOwnPD)
	{
		delete pDest->m_pPD;
		pDest->m_pPD = NULL;
	}

	pDest->m_bThumbTrack = p.m_bThumbTrack;
	pDest->m_bNeedChangeTab = p.m_bNeedChangeTab;
	pDest->m_bReadOnly = p.m_bReadOnly;
	pDest->m_bUndoEnabled = p.m_bUndoEnabled;
	pDest->m_bNumberedRowHeaders = p.m_bNumberedRowHeaders;
	pDest->m_bNumberedColHeaders = p.m_bNumberedColHeaders;
	pDest->m_bReadOnly = p.m_bReadOnly;
	pDest->m_bNeedChangeTab = p.m_bNeedChangeTab;
	pDest->m_bAllowSelDragCols = p.m_bAllowSelDragCols;
	pDest->m_bAllowSelDragRows = p.m_bAllowSelDragRows;
	pDest->m_bOwnData = p.m_bOwnData;
	pDest->m_bOwnPD = p.m_bOwnPD;
	pDest->m_bOwnProperties = p.m_bOwnProperties;
	pDest->m_bOwnStylesMap = p.m_bOwnStylesMap;
	pDest->m_bEatFirstMouseClick = p.m_bEatFirstMouseClick;
	pDest->m_bTransparentBackground = p.m_bTransparentBackground;
	pDest->m_bLockReadOnly = p.m_bLockReadOnly;
	pDest->m_bSmartResize = p.m_bSmartResize;

	
	pDest->m_wAllowSelection = p.m_wAllowSelection;
	pDest->m_wAllowTrackRowHeight = p.m_wAllowTrackRowHeight;
	pDest->m_wAllowTrackColWidth = p.m_wAllowTrackColWidth;
	pDest->m_nFrozenRows = p.m_nFrozenRows;
	pDest->m_nFrozenCols = p.m_nFrozenCols;
	pDest->m_nDefaultWidth = p.m_nDefaultWidth;
	pDest->m_nDefaultHeight = p.m_nDefaultHeight;
	pDest->m_sSheetName = p.m_sSheetName;
	pDest->m_wActivateCell = p.m_wActivateCell;
	pDest->m_nHideCurrentCell = p.m_nHideCurrentCell;

	pDest->m_nMinTrackRowHeight = p.m_nMinTrackRowHeight;
	pDest->m_nMinTrackColWidth = p.m_nMinTrackColWidth;


	pDest->m_nDrawRowOrder = p.m_nDrawRowOrder;

	pDest->m_nHeaderRows = p.m_nHeaderRows;
	pDest->m_nHeaderCols = p.m_nHeaderCols;

	if (p.m_pStylesMap)
	{
		pDest->m_pStylesMap = new CGXStylesMap();
		*pDest->m_pStylesMap = *p.m_pStylesMap;
	}
	
	if (p.m_pData)
	{
		if (p.m_pData->IsKindOf(RUNTIME_CLASS(CGXFormulaSheet)))
			pDest->m_pData = new CGXFormulaSheet();
		else
			pDest->m_pData = new CGXData();

		*pDest->m_pData = *p.m_pData;
	}
	
	if (p.m_pProperties)
	{
		pDest->m_pProperties = new CGXProperties();
		*pDest->m_pProperties = *p.m_pProperties;
	}
	
	if (p.m_pPD)
	{
		pDest->m_pPD = new CGXPrintDevice();
		*pDest->m_pPD = *p.m_pPD;
	}

	pDest->m_SelRects = p.m_SelRects;
	pDest->m_CoveredCellsList = p.m_CoveredCellsList;
	pDest->UpdateCoveredCellsList();
	
	pDest->m_RowHeights = p.m_RowHeights;
	pDest->m_ColWidths = p.m_ColWidths;
	
	
	//copy the byte arrays for the hidden row and col flags
	pDest->m_abRowHidden.RemoveAll();
	pDest->m_abRowHidden.InsertAt(0, (CByteArray64 *) &p.m_abRowHidden);

	pDest->m_abColHidden.RemoveAll();
	pDest->m_abColHidden.InsertAt(0, (CByteArray64 *) &p.m_abColHidden);

	pDest->m_bScrollLikeExcel = p.m_bScrollLikeExcel;

	// ?? pDest->m_bSyncCurrentCell;
	// ?? pDest->m_bIsInit;

	pDest->m_nUndoFreezeFromCol = p.m_nUndoFreezeFromCol; 
	pDest->m_nUndoFreezeToCol = p.m_nUndoFreezeToCol;
	pDest->m_nUndoFreezeDestCol = p.m_nUndoFreezeDestCol;
	

	pDest->m_nSpecialMode = p.m_nSpecialMode;  
	
	
	pDest->m_bDrawWYSIWYG = p.m_bDrawWYSIWYG;

	pDest->m_nEnterKeyAction = p.m_nEnterKeyAction;
	pDest->m_dwUndoLimit = p.m_dwUndoLimit;
	
	pDest->m_bSortColsOnDblClk = p.m_bSortColsOnDblClk;
	pDest->m_bSortRowsOnDblClk = p.m_bSortRowsOnDblClk;
	pDest->m_bExcelLikeCurrentCell = p.m_bExcelLikeCurrentCell;
	pDest->m_bExcelLikeHeaders = p.m_bExcelLikeHeaders;
	pDest->m_bExcelLikeSelectionFrame = p.m_bExcelLikeSelectionFrame;
	pDest->m_bNewGridLineMode = p.m_bNewGridLineMode;


	pDest->m_wFloatCellsMode = p.m_wFloatCellsMode;

	// Floating and Merge Cells
	delete (CObject*) pDest->m_pDelayedDispFloatCells;
	pDest->m_pDelayedDispFloatCells = 0;
	delete (CObject*) pDest->m_pDispFloatCells;
	pDest->m_pDispFloatCells = 0;
	delete (CObject*) pDest->m_pDelayedMergeCells;
	pDest->m_pDelayedMergeCells = 0;
	delete (CObject*) pDest->m_pDelayedMergeCells;
	pDest->m_pDelayedMergeCells = 0;
	delete (CObject*) pDest->m_pHorzMergeCells;
	pDest->m_pHorzMergeCells = 0;
	delete (CObject*) pDest->m_pVertMergeCells;
	pDest->m_pVertMergeCells = 0;

	CGXAppData* pApp = GXGetAppData();
	CGXAbstractDelayedRangePoolImp* pDelayPool = (CGXAbstractDelayedRangePoolImp*) pApp->m_pDelayedRangePoolImp;
	CGXAbstractSpanCellPoolImp* pSpanPool = (CGXAbstractSpanCellPoolImp*) pApp->m_pSpanCellPoolImp;

	if (p.m_pDelayedDispFloatCells)
		pDest->m_pDelayedDispFloatCells = pDelayPool->CreateDelayedRangePool(*p.m_pDelayedDispFloatCells);

	if (p.m_pDispFloatCells)
		pDest->m_pDispFloatCells = pSpanPool->CreateSpanCellPool(*p.m_pDispFloatCells);

	pDest->m_wMergeCellsMode = p.m_wMergeCellsMode;

	if (pDelayPool && p.m_pDelayedMergeCells)
		pDest->m_pDelayedMergeCells = pDelayPool->CreateDelayedRangePool(*p.m_pDelayedMergeCells);
	
	if (pSpanPool && p.m_pHorzMergeCells)
		pDest->m_pHorzMergeCells = pSpanPool->CreateSpanCellPool(*p.m_pHorzMergeCells);

	if (pSpanPool && p.m_pVertMergeCells)
		pDest->m_pVertMergeCells = pSpanPool->CreateSpanCellPool(*p.m_pVertMergeCells);

	// etc.

	pDest->m_nGridLineStyle = p.m_nGridLineStyle;
	pDest->m_bDirectCopyPaste = p.m_bDirectCopyPaste;
	pDest->m_bDirectCutPaste = p.m_bDirectCutPaste;
	pDest->m_bDirectDragDrop = p.m_bDirectDragDrop;

	ASSERT_VALID(pDest);
}

void CGXGridParamCopyOperatorImp::CopyObject(CGXProperties* pDest, const CGXProperties& p)
{
	ASSERT(p.IsKindOf(RUNTIME_CLASS(CGXProperties)));
	ASSERT_VALID(&p);

	if (pDest == &p)
		return;

	pDest->Free();

	// attributes
	pDest->m_bDisplayVertLines      = p.m_bDisplayVertLines;
	pDest->m_bDisplayHorzLines      = p.m_bDisplayHorzLines;
	pDest->m_b3dButtons             = p.m_b3dButtons;
	pDest->m_bMarkRowHeader         = p.m_bMarkRowHeader;
	pDest->m_bMarkColHeader         = p.m_bMarkColHeader;
	pDest->m_bPrinting              = p.m_bPrinting;
	pDest->m_sSection               = p.m_sSection;
	pDest->m_nZoom                  = p.m_nZoom;

	// colors

	if (p.m_ColorNameArray.GetSize() > 0)
	{
		pDest->m_ColorNameArray.InsertAt(0, p.m_ColorNameArray.GetAt(0), p.m_ColorNameArray.GetSize());
		pDest->m_ColorArray.InsertAt(0, p.m_ColorArray.GetAt(0), p.m_ColorArray.GetSize());
		for (int i = 0; i < p.m_ColorNameArray.GetSize(); i++)
		{
			pDest->m_ColorArray.SetAt(i, p.m_ColorArray.GetAt(i));
			pDest->m_ColorNameArray.SetAt(i, p.m_ColorNameArray.GetAt(i));
		}
	}

	// user attributes
	if (p.m_UserPropertyInfoMap.GetCount() > 0)
	{
		WORD nID;
		CGXProperties::UserPropertyInfo* pSrcInfo;
		POSITION pos = p.m_UserPropertyInfoMap.GetStartPosition();
		while (pos)
		{
			p.m_UserPropertyInfoMap.GetNextAssoc(pos, nID, (void*&) pSrcInfo);
			pDest->m_UserPropertyInfoMap.SetAt(nID, new CGXProperties::UserPropertyInfo(*pSrcInfo));
		}
	}

	// print settings
	pDest->m_bCenterVertical   = p.m_bCenterVertical;
	pDest->m_bCenterHorizontal = p.m_bCenterHorizontal;
	pDest->m_bPrintVertLines   = p.m_bPrintVertLines;
	pDest->m_bPrintHorzLines   = p.m_bPrintHorzLines;
	pDest->m_bRowHeaders        = p.m_bRowHeaders;
	pDest->m_bColHeaders        = p.m_bColHeaders;
	pDest->m_nPageOrder        = p.m_nPageOrder;
	pDest->m_bPrintFrame       = p.m_bPrintFrame;
	pDest->m_bBlackWhite       = p.m_bBlackWhite;
	pDest->m_nTopMargin        = p.m_nTopMargin;
	pDest->m_nLeftMargin       = p.m_nLeftMargin;
	pDest->m_nBottomMargin     = p.m_nBottomMargin;
	pDest->m_nRightMargin      = p.m_nRightMargin;

	// Header&Footer
	pDest->m_nDistTop        = p.m_nDistTop;
	pDest->m_nDistBottom     = p.m_nDistBottom;
	pDest->m_nFirstPage      = p.m_nFirstPage;
	pDest->m_mapDataFooter   = p.m_mapDataFooter;
	pDest->m_mapDataHeader   = p.m_mapDataHeader;

	ASSERT_VALID(pDest);
}

void CGXGridParamCopyOperatorImp::CopyObject(CGXStylesMap* pDest, const CGXStylesMap& p)
{
	ASSERT(p.IsKindOf(RUNTIME_CLASS(CGXStylesMap)));
	ASSERT_VALID(&p);

	if (pDest == &p)
		return;

	pDest->Free();

	pDest->m_pStyleClass = p.m_pStyleClass;

	// Base Styles
	if (p.m_mwpIdInfo.GetCount() > 0)
	{
		// BaseStyleInfo
		WORD wStyleId;
		CGXStylesMap::BaseStyleInfo* pSrcInfo;
		POSITION pos = p.m_mwpIdInfo.GetStartPosition();
		while (pos)
		{
			p.m_mwpIdInfo.GetNextAssoc(pos, wStyleId, (void*&) pSrcInfo);
			pDest->m_mwpIdInfo.SetAt(wStyleId, new CGXStylesMap::BaseStyleInfo(*pSrcInfo));
		}

		// Names
		CString sName;
		void* vptr;

		pos = p.m_mswNameId.GetStartPosition();
		while (pos)
		{
			p.m_mswNameId.GetNextAssoc(pos, sName, vptr);
			pDest->m_mswNameId.SetAt(sName, vptr);
		}

		// Resource IDs
		pos = p.m_mpwResourceId.GetStartPosition();
		while (pos)
		{
			p.m_mpwResourceId.GetNextAssoc(pos, vptr, wStyleId);
			pDest->m_mpwResourceId.SetAt(vptr, wStyleId);
		}
	}

	pDest->m_nLastId = p.m_nLastId;

	// controls
	if (p.m_ControlNameMap.GetCount() > 0)
	{
		WORD nID;
		CString* pStrName;
		POSITION pos = p.m_ControlNameMap.GetStartPosition();
		while (pos)
		{
			p.m_ControlNameMap.GetNextAssoc(pos, nID, (void*&) pStrName);
			pDest->m_ControlNameMap.SetAt(nID, new CString(*pStrName));
		}
	}

	// user attributes
	if (p.m_UserAttrInfoMap.GetCount() > 0)
	{
		WORD w;
		CGXStylesMap::UserAttrInfo* pSrcInfo;
		POSITION pos = p.m_UserAttrInfoMap.GetStartPosition();
		while (pos)
		{
			p.m_UserAttrInfoMap.GetNextAssoc(pos, w, (void*&) pSrcInfo);
			pDest->m_UserAttrInfoMap.SetAt(w, new CGXStylesMap::UserAttrInfo(*pSrcInfo));
		}
	}

	pDest->m_sSection = p.m_sSection;

	pDest->m_wStyleStandard = pDest->GetBaseStyleId(GX_IDS_STYLE_STANDARD);
	pDest->m_wStyleColHeader = pDest->GetBaseStyleId(GX_IDS_STYLE_COLHEADER);
	pDest->m_wStyleRowHeader = pDest->GetBaseStyleId(GX_IDS_STYLE_ROWHEADER);

	ASSERT_VALID(pDest);
}

