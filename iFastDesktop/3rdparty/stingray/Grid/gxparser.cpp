///////////////////////////////////////////////////////////////////////////////
// gxparser.cpp : implementation of Serialization for CGXGridParam class
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


class CGXGridDocSerializeImp: public CGXAbstractGridDocSerializeImp
{
public:
	virtual void Serialize(CGXGridParam* pParam, CArchive& ar);
	virtual void Serialize(CGXProperties* pProp, CArchive& ar);
	virtual void Serialize(CGXStylePtrArray* pArray, CArchive& ar);
	virtual void Serialize(CGXStylePtrArrayPtrArray* pArray, CArchive& ar);
	virtual void Serialize(CGXData* pData, CArchive& ar);
	virtual void Serialize(CGXStylesMap* pStyMap, CArchive& ar);
};

void AFXAPI CGXGridParam::ImplementSerialize()
{
	if (GXGetAppData()->m_pDocSerializeImp == NULL)
	{
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pDocSerializeImp = new CGXGridDocSerializeImp);
		GXGetAppData()->m_pDocSerializeImp = new CGXGridDocSerializeImp;
	}

	CGXStyle::ImplementSerialize();
	CGXSpanCellPool::ImplementSpanCellPool();
	CGXDelayedRangePool::ImplementDelayedRangePool();
}

inline void AFXAPI GXArchiveBool(CArchive& ar, BOOL& b)
{
	if (ar.IsStoring())
		ar << (BYTE) b;
	else
	{
		BYTE i;
		ar >> i;
		b = i;
	}
}

void CGXGridDocSerializeImp::Serialize(CGXGridParam* pParam, CArchive& ar)
{
	static const WORD wVersion = 11; // 8.1.1
	WORD wActualVersion = wVersion;

	ASSERT_VALID(pParam);

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion > wVersion )
		{
#ifdef _DEBUG
			TRACE0( "Incompatible format while reading CGXGridParam" );
			TRACE2("in %s at line %d\n", __FILE__, __LINE__);
			ASSERT(0);
			// ASSERTION-> Wrong version detected while reading object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	if (!ar.IsStoring())
	{
		// cleanup owned objects
		if (pParam->m_bOwnStylesMap)
		{
			delete pParam->m_pStylesMap;
			pParam->m_pStylesMap = NULL;
		}

		if (pParam->m_bOwnData)
		{
			delete pParam->m_pData;
			pParam->m_pData = NULL;
		}

		if (pParam->m_bOwnProperties)
		{
			delete pParam->m_pProperties;
			pParam->m_pProperties = NULL;
		}

		if (pParam->m_bOwnPD)
		{
			delete pParam->m_pPD;
			pParam->m_pPD = NULL;
		}
	}

	GXArchiveBool(ar, pParam->m_bThumbTrack);
	GXArchiveBool(ar, pParam->m_bNeedChangeTab);
	GXArchiveBool(ar, pParam->m_bReadOnly);
	GXArchiveBool(ar, pParam->m_bUndoEnabled);
	GXArchiveBool(ar, pParam->m_bNumberedRowHeaders);
	GXArchiveBool(ar, pParam->m_bNumberedColHeaders);
	GXArchiveBool(ar, pParam->m_bReadOnly);
	GXArchiveBool(ar, pParam->m_bNeedChangeTab);
	GXArchiveBool(ar, pParam->m_bAllowSelDragCols);
	GXArchiveBool(ar, pParam->m_bAllowSelDragRows);
	GXArchiveBool(ar, pParam->m_bOwnData);
	GXArchiveBool(ar, pParam->m_bOwnPD);
	GXArchiveBool(ar, pParam->m_bOwnProperties);
	GXArchiveBool(ar, pParam->m_bOwnStylesMap);
	GXArchiveBool(ar, pParam->m_bEatFirstMouseClick);
	GXArchiveBool(ar, pParam->m_bTransparentBackground);
	GXArchiveBool(ar, pParam->m_bLockReadOnly);
	GXArchiveBool(ar, pParam->m_bSmartResize);

	if (ar.IsStoring())
	{
		ar << pParam->m_wAllowSelection;
		ar << pParam->m_wAllowTrackRowHeight;
		ar << pParam->m_wAllowTrackColWidth;
		ar << pParam->m_nFrozenRows;
		ar << pParam->m_nFrozenCols;
		ar << pParam->m_nDefaultWidth;
		ar << pParam->m_nDefaultHeight;
		ar << pParam->m_sSheetName;
		ar << pParam->m_wActivateCell;
		ar << pParam->m_nHideCurrentCell;

		ar << (WORD) pParam->m_nMinTrackRowHeight;
		ar << (WORD) pParam->m_nMinTrackColWidth;


		ar << pParam->m_nDrawRowOrder;

		ar << pParam->m_nHeaderRows;
		ar << pParam->m_nHeaderCols;

		// This is a bit dirty, but style-objects need access to the styles-map
		// and CArchive::pParam->m_pDocument is not needed for serializing the following objects
		CDocument* pOldDoc = ar.m_pDocument;
		ar.m_pDocument = (CDocument*) pParam->GetStylesMap();

		// CGXStyle::Serialize needs the styles-map because BaseStyleIds must
		// be serailized with its names. (These names are maintained in styles-map).

		if (pParam->m_bOwnStylesMap)
			ar << pParam->m_pStylesMap;
		if (pParam->m_bOwnData)
			ar << pParam->m_pData;
		if (pParam->m_bOwnProperties)
			ar << pParam->m_pProperties;

		// reset document ptr
		ar.m_pDocument = pOldDoc;

		if (pParam->m_bOwnPD)
			ar << pParam->m_pPD;
	}
	else
	{
		WORD w;

		ar >> pParam->m_wAllowSelection;
		ar >> pParam->m_wAllowTrackRowHeight;
		ar >> pParam->m_wAllowTrackColWidth;
		ar >> pParam->m_nFrozenRows;
		ar >> pParam->m_nFrozenCols;
		ar >> pParam->m_nDefaultWidth;
		ar >> pParam->m_nDefaultHeight;
		ar >> pParam->m_sSheetName;
		ar >> pParam->m_wActivateCell;
		ar >> pParam->m_nHideCurrentCell;

		ar >> w; pParam->m_nMinTrackRowHeight = (int) w;
		ar >> w; pParam->m_nMinTrackColWidth = (int) w;

		ar >> pParam->m_nDrawRowOrder;

		ar >> pParam->m_nHeaderRows;
		ar >> pParam->m_nHeaderCols;

		if (pParam->m_bOwnStylesMap)
			ar >> pParam->m_pStylesMap;

		// This is a bit dirty, but style-objects need access to the styles-map
		// and CArchive::pParam->m_pDocument is not needed for serializing the following objects
		CDocument* pOldDoc = ar.m_pDocument;
		ar.m_pDocument = (CDocument*) pParam->GetStylesMap();

		if (pParam->m_bOwnData)
			ar >> pParam->m_pData;

		if (pParam->m_bOwnProperties)
			ar >> pParam->m_pProperties;

		// reset document ptr
		ar.m_pDocument = pOldDoc;

		if (pParam->m_bOwnPD)
			ar >> pParam->m_pPD;
	}

	pParam->m_SelRects.Serialize(ar);
	pParam->m_CoveredCellsList.Serialize(ar);

	if (!ar.IsStoring())
	{
		pParam->UpdateCoveredCellsList();
	}

	pParam->m_RowHeights.Serialize(ar);
	pParam->m_ColWidths.Serialize(ar);
	pParam->m_abRowHidden.Serialize(ar);
	pParam->m_abColHidden.Serialize(ar);

	if (wActualVersion >= 2)
		GXArchiveBool(ar, pParam->m_bScrollLikeExcel);

	if (wActualVersion >= 3)
	{
		GXArchiveBool(ar, pParam->m_bSyncCurrentCell);
		GXArchiveBool(ar, pParam->m_bIsInit);

		if (ar.IsStoring())
		{
			ar << pParam->m_nUndoFreezeFromCol;   // additional information
			ar << pParam->m_nUndoFreezeToCol;     // for "Unfreeze" columns
			ar << pParam->m_nUndoFreezeDestCol;
		}
		else
		{
			ar >> pParam->m_nUndoFreezeFromCol;   // additional information
			ar >> pParam->m_nUndoFreezeToCol;     // for "Unfreeze" columns
			ar >> pParam->m_nUndoFreezeDestCol;
		}
	}

	if (wActualVersion >= 4)
	{
		if (ar.IsStoring())
		{
			ar << pParam->m_nSpecialMode;   // special mode
		}
		else
		{
			ar >> pParam->m_nSpecialMode;   // special mode
		}
	}

	if (wActualVersion >= 5)
	{
		GXArchiveBool(ar, pParam->m_bDrawWYSIWYG);

		if (ar.IsStoring())
		{
			ar << pParam->m_nEnterKeyAction;
			ar << pParam->m_dwUndoLimit;
		}
		else
		{
			ar >> pParam->m_nEnterKeyAction;
			ar >> pParam->m_dwUndoLimit;
		}
	}

	if (wActualVersion >= 6)
	{
		GXArchiveBool(ar, pParam->m_bSortColsOnDblClk);
		GXArchiveBool(ar, pParam->m_bSortRowsOnDblClk);
		GXArchiveBool(ar, pParam->m_bExcelLikeCurrentCell);
		GXArchiveBool(ar, pParam->m_bExcelLikeSelectionFrame);
		GXArchiveBool(ar, pParam->m_bNewGridLineMode);

		if (ar.IsStoring())
		{
			ar << pParam->m_wFloatCellsMode;
			ar << pParam->m_pDelayedDispFloatCells;
			ar << pParam->m_pDispFloatCells;

			ar << pParam->m_wMergeCellsMode;
			ar << pParam->m_pDelayedMergeCells;
			ar << pParam->m_pHorzMergeCells;
			ar << pParam->m_pVertMergeCells;
			ar << pParam->m_nGridLineStyle;
		}
		else
		{
			ar >> pParam->m_wFloatCellsMode;
			ar >> pParam->m_pDelayedDispFloatCells;
			ar >> pParam->m_pDispFloatCells;

			ar >> pParam->m_wMergeCellsMode;
			ar >> pParam->m_pDelayedMergeCells;
			ar >> pParam->m_pHorzMergeCells;
			ar >> pParam->m_pVertMergeCells;
			ar >> pParam->m_nGridLineStyle;

			if (wActualVersion < 7)
			{
				// this info is incompatible with OG 5.0
				// Therefore I force recalculating this info 
				// (see OG 5.0 - PRB001: Merge cells (and covered cells) don't MERGE from col 0 to col n or row 0 to row n)
				if (pParam->m_pDelayedDispFloatCells)
				{
					pParam->m_pDelayedDispFloatCells->MakeEmpty();
					pParam->m_pDelayedDispFloatCells->DelayRange(CGXRange(0, 0, GX_MAXROWCOL, GX_MAXROWCOL));
					pParam->m_pDispFloatCells->MakeEmpty();
				}

				if (pParam->m_pDelayedMergeCells)
				{
					pParam->m_pDelayedMergeCells->MakeEmpty();
					pParam->m_pDelayedMergeCells->DelayRange(CGXRange(0, 0, GX_MAXROWCOL, GX_MAXROWCOL));
					pParam->m_pHorzMergeCells->MakeEmpty();
					pParam->m_pVertMergeCells->MakeEmpty();
				}
			}
		}
	}

	if (wActualVersion >= 8)
	{
		GXArchiveBool(ar, pParam->m_bDirectCopyPaste);
		GXArchiveBool(ar, pParam->m_bDirectCutPaste);
		GXArchiveBool(ar, pParam->m_bDirectDragDrop);
	}

	if (wActualVersion >= 9)
	{
		if (ar.IsStoring())
			ar << pParam->m_nDisplayExpression;
		else
			ar >> pParam->m_nDisplayExpression;
	}

	if (wActualVersion >= 10)
	{
		GXArchiveBool(ar, pParam->m_bExcelLikeHeaders);
	}

	if (wActualVersion >= 11)
	{
		GXArchiveBool(ar, pParam->m_bSortAscending);

		if (ar.IsStoring())
		{
			ar << pParam->m_nLastSortedCol;
			ar << pParam->m_nLastSortedRow;
		}
		else
		{
			ar >> pParam->m_nLastSortedCol;
			ar >> pParam->m_nLastSortedRow;
		}
	}

	ASSERT_VALID(pParam);
}


void CGXGridDocSerializeImp::Serialize(CGXProperties* pProp, CArchive& ar)
{
	// Version 4 from version 7.02
	static const WORD wVersion = 4;
	WORD wActualVersion = wVersion;

	ASSERT_VALID(pProp);

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion > wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0("Incompatible format while reading CGXProperties" );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXProperties object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	// Colors
	pProp->m_ColorArray.Serialize(ar);

	CStringArray array;
	array.Serialize(ar);

	if (!ar.IsStoring())
		pProp->m_ColorArray.SetSize(pProp->m_ColorNameArray.GetSize());

	GXArchiveBool(ar, pProp->m_bDisplayVertLines);
	GXArchiveBool(ar, pProp->m_bDisplayHorzLines);
	GXArchiveBool(ar, pProp->m_b3dButtons);
	GXArchiveBool(ar, pProp->m_bMarkRowHeader);
	GXArchiveBool(ar, pProp->m_bMarkColHeader);

	if (ar.IsStoring())
	{
		ar << pProp->m_sSection;
		ar << (LONG) pProp->m_nZoom;

		// user properties
		if (pProp->m_UserPropertyInfoMap.GetCount() > 0)
		{
			WORD nID;
			CGXProperties::UserPropertyInfo* pInfo;
			POSITION pos = pProp->m_UserPropertyInfoMap.GetStartPosition();
			while (pos)
			{
				pProp->m_UserPropertyInfoMap.GetNextAssoc(pos, nID, (void*&) pInfo);
				ar << (DWORD) pInfo->nID;
				ar << pInfo->sName;
				ar << pInfo->pStyle;
			}
		}
		ar << (DWORD) 0;

		// Print Settings
		ar << pProp->m_bPrintVertLines;
		ar << pProp->m_bPrintHorzLines;
		ar << pProp->m_nPageOrder;
		ar << pProp->m_bBlackWhite;
		ar << pProp->m_bRowHeaders;
		ar << pProp->m_bCenterVertical;
		ar << pProp->m_bCenterHorizontal;
		ar << pProp->m_nTopMargin;
		ar << pProp->m_nLeftMargin;
		ar << pProp->m_nRightMargin;
		ar << pProp->m_nBottomMargin;
		ar << pProp->m_bPrintFrame;

		// Header&Footer
		ar << pProp->m_nDistTop;
		ar << pProp->m_nDistBottom;
		ar << pProp->m_nFirstPage;
		ar << pProp->m_gxnPropTextHeadline;
		ar << pProp->m_gxnPropTextFootnote;
		
		pProp->m_awColBreaks.Serialize(ar);
		pProp->m_awRowBreaks.Serialize(ar);
	}
	else
	{
		LONG l;
		ar >> pProp->m_sSection;
		ar >> l; pProp->m_nZoom = (int) l;

		// user properties
		DWORD dw;
		ar >> dw;
		if (dw)
		{
			CString s;
			CGXProperties::UserPropertyInfo* pInfo;
			while (dw > 0)
			{
				WORD nID = (WORD) dw;
				ar >> s;
				if (!pProp->m_UserPropertyInfoMap.Lookup(nID, (void*&) pInfo))
				{
					pInfo = new CGXProperties::UserPropertyInfo;
					pInfo->nID = nID;
					pInfo->sName = s;
				}
				else
					delete pInfo->pStyle;
				ar >> pInfo->pStyle;
				pProp->m_UserPropertyInfoMap.SetAt(pInfo->nID, pInfo);

				ar >> dw;
			}
		}

		// Print Settings
		ar >> pProp->m_bPrintVertLines;
		ar >> pProp->m_bPrintHorzLines;
		ar >> pProp->m_nPageOrder;
		ar >> pProp->m_bBlackWhite;
		ar >> pProp->m_bRowHeaders;
		ar >> pProp->m_bCenterVertical;
		ar >> pProp->m_bCenterHorizontal;
		ar >> pProp->m_nTopMargin;
		ar >> pProp->m_nLeftMargin;
		ar >> pProp->m_nRightMargin;
		ar >> pProp->m_nBottomMargin;
		ar >> pProp->m_bPrintFrame;

		// Header&Footer
		ar >> pProp->m_nDistTop;
		ar >> pProp->m_nDistBottom;
		ar >> pProp->m_nFirstPage;
		ar >> pProp->m_gxnPropTextHeadline;
		ar >> pProp->m_gxnPropTextFootnote;

		if(wActualVersion >= 3)
		{
			pProp->m_awColBreaks.Serialize(ar);
			pProp->m_awRowBreaks.Serialize(ar);
		}

		ASSERT_VALID(pProp);
	}

	pProp->m_mapDataFooter.Serialize(ar);
	pProp->m_mapDataHeader.Serialize(ar);

	// Do not do this for version 3.
	if (wActualVersion == 2 || wActualVersion >= 4)
	{
		if (ar.IsStoring())
			ar << pProp->m_bColHeaders;
		else
			ar >> pProp->m_bColHeaders;
	}
}

void CGXGridDocSerializeImp::Serialize(CGXStylePtrArray* pArray, CArchive& ar)
{
	// Serializes only existing elements,
	// e.g.  1 xxx 2 xxx 3 xxx 7 xxx 22 xxx DWORD_MAX,
	// where xxx is a CGXStyle object and DWORD_MAX identifies the end of serialization

	static const WORD wVersion = 1;
	WORD wActualVersion = wVersion;

	ASSERT_VALID(pArray);

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion != wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0( "Incompatible format while reading CGXStylePtrArray" );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXStylePtrArray object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	const DWORD dwTerm = 0xFFFFFFFF;

	if (ar.IsStoring())
	{
		// storing

		DWORD dwSize = (DWORD) pArray->GetSize();
		ar << dwSize;
		for (int index = 0; index <= pArray->GetUpperBound(); index++)
		{
			CGXStyle* pStyle = pArray->GetAt(index);
			if (pStyle)
			{
				ar << (DWORD) index;
				ar << pStyle;
			}
		}
		ar << dwTerm;
	}
	else
	{
		// loading

		pArray->DeleteAll();

		DWORD dwSize;
		ar >> dwSize;

		pArray->SetSize((int) dwSize);

		DWORD dwIndex;
		ar >> dwIndex;

		while (dwIndex != dwTerm)
		{
			CGXStyle* pStyle;
			pStyle = NULL;
			ar >> pStyle;

			pArray->SetAt((int) dwIndex, pStyle);

			// Next id
			ar >> dwIndex;
		}
	}
}

void CGXGridDocSerializeImp::Serialize(CGXStylePtrArrayPtrArray* pArray, CArchive& ar)
{
	// Serializes only existing elements,
	// e.g.  1 xxx 2 xxx 3 xxx 7 xxx 22 xxx DWORD_MAX,
	// where xxx is a CGXStylePtrArray object and DWORD_MAX identifies the end of serialization

	static const WORD wVersion = 1;
	WORD wActualVersion = wVersion;

	ASSERT_VALID(pArray);

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion != wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0( "Incompatible format while reading CGXStylePtrArrayPtrArray " );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXStylePtrArrayPtrArray object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	const DWORD dwTerm = 0xFFFFFFFF;

	if (ar.IsStoring())
	{
		// storing

		DWORD dwSize = (DWORD) pArray->GetSize();
		ar << dwSize;
		for (int index = 0; index <= pArray->GetUpperBound(); index++)
		{
			CGXStylePtrArray* pStylePtrArray = pArray->GetAt(index);
			if (pStylePtrArray)
			{
				ar << (DWORD) index;
				pStylePtrArray->Serialize(ar);
			}
		}
		ar << dwTerm;
	}
	else
	{
		// loading

		pArray->DeleteAll();

		DWORD dwSize;
		ar >> dwSize;

		pArray->SetSize((int) dwSize);

		DWORD dwIndex;
		ar >> dwIndex;

		while (dwIndex != dwTerm)
		{
			CGXStylePtrArray* pStylePtrArray = new CGXStylePtrArray;
			pStylePtrArray->Serialize(ar);

			pArray->SetAt((int) dwIndex, pStylePtrArray);

			// Next id
			ar >> dwIndex;
		}
	}
}

void CGXGridDocSerializeImp::Serialize(CGXData* pData, CArchive& ar)
{
	static const WORD wVersion = 1;
	WORD wActualVersion = wVersion;

	ASSERT_VALID(pData);

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion != wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0( "Incompatible format while reading CGXData" );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXData object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	if (ar.IsStoring())
	{
		ar << pData->m_nRows,
		ar << pData->m_nCols;
	}
	else
	{
		ar >> pData->m_nRows,
		ar >> pData->m_nCols;
	}

	pData->m_apapCellStyle.Serialize(ar);
	pData->m_apRowBaseStyle.Serialize(ar);
	pData->m_apColBaseStyle.Serialize(ar);
}

void CGXGridDocSerializeImp::Serialize(CGXStylesMap* pStyMap, CArchive& ar)
{
	static const WORD wVersion = 2;
	WORD wActualVersion = wVersion;

	ASSERT_VALID(pStyMap);

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion > wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0("Incompatible format while reading CGXStylesMap" );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXStylesMap object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	if (ar.IsStoring())
	{
		ASSERT_VALID(pStyMap);

		ar << pStyMap->m_sSection;

		// Control names
		ar << (WORD) pStyMap->m_ControlNameMap.GetCount();
		POSITION pos;
		for (pos = pStyMap->m_ControlNameMap.GetStartPosition(); pos; )
		{
			WORD w;
			CString* pStrName;
			pStyMap->m_ControlNameMap.GetNextAssoc(pos, w, (void*&) pStrName);
			ar << (DWORD) w; // DWORD - backward compatible
			ar << *pStrName;
		}

		// Base Styles
		ar << (WORD) pStyMap->m_mswNameId.GetCount();

		CString sName;
		pos = pStyMap->m_mswNameId.GetStartPosition();
		void* vptr;
		while (pos)
		{
			WORD wStyleId;
			pStyMap->m_mswNameId.GetNextAssoc(pos, sName, vptr);
			wStyleId = (WORD) (SEC_LONG) vptr;
			ar << wStyleId;
			ar << sName;
		}

		ar << (WORD) pStyMap->m_mwpIdInfo.GetCount();

		if (pStyMap->m_mwpIdInfo.GetCount() > 0)
		{
			// BaseStyleInfo
			WORD wStyleId;
			CGXStylesMap::BaseStyleInfo* pSrcInfo;
			POSITION pos = pStyMap->m_mwpIdInfo.GetStartPosition();
			while (pos)
			{
				pStyMap->m_mwpIdInfo.GetNextAssoc(pos, wStyleId, (void*&) pSrcInfo);
				ar << wStyleId;
				ar << (DWORD) pSrcInfo->nResourceID;
				ar << pSrcInfo->sName;
				ar << (BYTE) pSrcInfo->bSystem;
				pSrcInfo->pStyle->Serialize(ar, pStyMap);
			}
		}

		ar << pStyMap->m_nLastId;

		// Version 2

		if (wActualVersion > 1)
		{
			ar << (WORD) pStyMap->m_UserAttrInfoMap.GetCount();

			if (pStyMap->m_UserAttrInfoMap.GetCount() > 0)
			{
				// BaseStyleInfo
				WORD nId;
				CGXStylesMap::UserAttrInfo* pSrcInfo;
				POSITION pos = pStyMap->m_UserAttrInfoMap.GetStartPosition();
				while (pos)
				{
					pStyMap->m_UserAttrInfoMap.GetNextAssoc(pos, nId, (void*&) pSrcInfo);
					ar << (DWORD) nId;
					pSrcInfo->pStyle->Serialize(ar, pStyMap);
				}
			}
		}
	}
	else
	{
		pStyMap->FreeStylesMap();
		pStyMap->FreeControlMap();

		ar >> pStyMap->m_sSection;

		WORD wCount;

		// Control names
		ar >> wCount;
		WORD n;
		for (n = 0; n < wCount; n++)
		{
			DWORD dw;
			WORD wId;
			CString sName;
			ar >> dw;	// DOWRD id - backward compatible
			wId = (WORD) dw;     
			ar >> sName;    // Name

			pStyMap->m_ControlNameMap.SetAt(wId, new CString(sName));
		}

		ar >> wCount;

		for (n = 0; n < wCount; n++)
		{
			WORD wStyleId;
			CString sName;
			ar >> wStyleId;     // id
			ar >> sName;    // Name
		}

		ar >> wCount;

		for (n = 0; n < wCount; n++)
		{
			CGXStylesMap::BaseStyleInfo* pInfo = new CGXStylesMap::BaseStyleInfo;
			WORD wStyleId;
			BYTE b;
			DWORD dw;
			ar >> wStyleId; pInfo->nID = wStyleId;  // id
			ar >> dw; pInfo->nResourceID = (UINT) dw;
			ar >> pInfo->sName; // sName
			ar >> b;    pInfo->bSystem = (BOOL) b;  // bSystem
			pInfo->pStyle = (CGXStyle*) pStyMap->m_pStyleClass->CreateObject();
			pInfo->pStyle->Serialize(ar, pStyMap);
			if (dw > 0)
			{
				if (!pInfo->sName.LoadString(pInfo->nResourceID))
				{
					// resource string not found 
					pInfo->sName.Format(_T("STYLE%u"), pInfo->nResourceID);
				}
				
				pStyMap->m_mpwResourceId.SetAt((void*) (SEC_DWORD) pInfo->nResourceID, wStyleId);
			}
			pStyMap->m_mswNameId.SetAt(pInfo->sName, (void*) (SEC_DWORD) wStyleId);
			pStyMap->m_mwpIdInfo.SetAt(wStyleId, pInfo);
		}

		ar >> pStyMap->m_nLastId;

		// Version 2

		if (wActualVersion > 1)
		{
			ar >> wCount;

			for (n = 0; n < wCount; n++)
			{
				CGXStylesMap::UserAttrInfo* pInfo = new CGXStylesMap::UserAttrInfo;
				DWORD nId;
				ar >> nId; pInfo->nID = (WORD) nId;  // id
				if (!pInfo->sName.LoadString(pInfo->nID))
				{
					// resource string not found 
					pInfo->sName.Format(_T("UA%u"), nId);
				}
				pInfo->pStyle = (CGXStyle*) pStyMap->m_pStyleClass->CreateObject();
				pInfo->pStyle->Serialize(ar, pStyMap);
				pStyMap->m_UserAttrInfoMap.SetAt((WORD) nId, pInfo);
			}
		}

		pStyMap->m_wStyleStandard = pStyMap->GetBaseStyleId(GX_IDS_STYLE_STANDARD);
		pStyMap->m_wStyleColHeader = pStyMap->GetBaseStyleId(GX_IDS_STYLE_COLHEADER);
		pStyMap->m_wStyleRowHeader = pStyMap->GetBaseStyleId(GX_IDS_STYLE_ROWHEADER);

		ASSERT_VALID(pStyMap);
	}
}

