///////////////////////////////////////////////////////////////////////////////
// gxcmd.cpp : implementation of command classes with undo information.
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

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCMD_H_
#include "grid\gxcmd.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCMD")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CGXCommand, CObject);
IMPLEMENT_DYNAMIC(CGXBlockCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXSetRowHeightCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXSetColWidthCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXHideRowsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXHideColsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXSetDefaultRowHeightCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXSetDefaultColWidthCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXMoveRowsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXMoveColsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXRemoveRowsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXRemoveColsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXInsertRowsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXInsertColsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXSetCoveredCellsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXSetStyleRangeCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXSetFrozenColsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXSetFrozenRowsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXMoveDataRowsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXMoveDataColsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXChangeStylesMapCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXChangePropertiesCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXChangeBaseStyleCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXMoveCellsCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXSetRangeNameCmd, CGXCommand);
IMPLEMENT_DYNAMIC(CGXDeleteRangeNameCmd, CGXCommand);

IMPLEMENT_COMMAND(CGXSetRowHeightCmd, GX_IDM_SETROWHEIGHT);
IMPLEMENT_COMMAND(CGXSetColWidthCmd, GX_IDM_SETCOLWIDTH);
IMPLEMENT_COMMAND(CGXHideColsCmd, GX_IDM_HIDECOLS);
IMPLEMENT_COMMAND(CGXHideRowsCmd, GX_IDM_HIDEROWS);
IMPLEMENT_COMMAND(CGXSetDefaultRowHeightCmd, GX_IDM_SETDEFAULTROWHEIGHT);
IMPLEMENT_COMMAND(CGXSetDefaultColWidthCmd, GX_IDM_SETDEFAULTCOLWIDTH);
IMPLEMENT_COMMAND(CGXMoveRowsCmd, GX_IDM_MOVEROWS);
IMPLEMENT_COMMAND(CGXMoveColsCmd, GX_IDM_MOVECOLS);
IMPLEMENT_COMMAND(CGXRemoveRowsCmd, GX_IDM_INSERTROWS);
IMPLEMENT_COMMAND(CGXRemoveColsCmd, GX_IDM_INSERTCOLS);
IMPLEMENT_COMMAND(CGXInsertRowsCmd, GX_IDM_REMOVEROWS);
IMPLEMENT_COMMAND(CGXInsertColsCmd, GX_IDM_REMOVECOLS);
IMPLEMENT_COMMAND(CGXSetCoveredCellsCmd, GX_IDM_SETCOVEREDCELLS);
IMPLEMENT_COMMAND(CGXSetStyleRangeCmd, GX_IDM_SETSTYLERANGE);
IMPLEMENT_COMMAND(CGXSetFrozenColsCmd, GX_IDM_SETFROZENCOLS);
IMPLEMENT_COMMAND(CGXSetFrozenRowsCmd, GX_IDM_SETFROZENROWS);
IMPLEMENT_COMMAND(CGXMoveDataRowsCmd, GX_IDM_SORTROWS);
IMPLEMENT_COMMAND(CGXMoveDataColsCmd, GX_IDM_SORTCOLS);
IMPLEMENT_COMMAND(CGXChangeStylesMapCmd, GX_IDM_CHANGESTYLESMAP);
IMPLEMENT_COMMAND(CGXChangePropertiesCmd, GX_IDM_CHANGEPROPERTIES);
IMPLEMENT_COMMAND(CGXMoveCellsCmd, GX_IDM_DRAGDROP_MOVE);
IMPLEMENT_COMMAND(CGXSetRangeNameCmd, GX_IDM_SETRANGENAME);
IMPLEMENT_COMMAND(CGXDeleteRangeNameCmd, GX_IDM_DELETERANGENAME);

// this file contains following methods:

// - Undo, Redo

// + several command classes with associated execute method

// Undo command factory 

//////////////////////////////////////////////////////////////
// CGXCommand

CGXCommand::CGXCommand()
	: m_ncRow(0), m_ncCol(0), m_bCCell(FALSE), m_pAdvUndo(NULL)
{
}

CGXCommand::~CGXCommand()
{
	delete m_pAdvUndo;
}

//////////////////////////////////////////////////////////////
// CGXBlockCmd

CGXBlockCmd::CGXBlockCmd(LPCTSTR s)
{
	if (s)
		m_sDesc = s;
	else
		m_sDesc = _T("Block");
}

CGXBlockCmd::~CGXBlockCmd()
{
	POSITION pos = m_CommandList.GetHeadPosition();
	CGXCommand* pCmd;
	while (pos)
	{
		pCmd = (CGXCommand*) m_CommandList.GetNext(pos);
		delete pCmd;
	}
	m_CommandList.RemoveAll();
}

BOOL CGXBlockCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	CGXLongOperation theOp;

	// Block: Status text
	{
		CString s;
		if (ctCmd == gxRedo)
			GXFormatString1(s, pGrid->m_pAppData->strmRedo, GetDescription());
		else if (ctCmd == gxUndo)
			GXFormatString1(s, pGrid->m_pAppData->strmUndo, GetDescription());
		else
			s = GetDescription();
		theOp.SetStatusText(s);
	}

	CGXBlockCmd* pBlockCmd = NULL;

	CObList* pList;

	if (ctCmd == gxRedo)
		pList = &pGrid->GetParam()->GetUndoList();
	else
		pList = &pGrid->GetParam()->GetRedoList();

	if (ctCmd == gxRedo || ctCmd == gxUndo)
		pList->AddHead(pBlockCmd = new CGXBlockCmd(GetDescription()));

	// Commands call AddComand to store undo/redo info
	// AddCommand will store all commands into pBlockCmd->m_CommandList

	pGrid->m_bBlockCmd = TRUE;
	pGrid->m_bCellUndone = FALSE;

	POSITION pos = m_CommandList.GetHeadPosition();

	BOOL bLock = FALSE;

	long nCount = (long)m_CommandList.GetCount();
	long nCmdDone = 0;

	if (nCount > 1)
	{
		bLock = pGrid->LockUpdate();
		theOp.SetLockedState();
	}

	BOOL b = TRUE;
	while (pos && b)
	{
		CGXCommand* pCmd = (CGXCommand*) m_CommandList.GetNext(pos);

		ASSERT_VALID(pCmd);
		ASSERT(pCmd->IsKindOf(RUNTIME_CLASS(CGXCommand)));

		b &= pGrid->ExecuteCommand(pCmd, pGrid, ctCmd);

		nCmdDone++;

		if (theOp.NeedMessages())
		{
			theOp.SetPercentDone((int) ((nCmdDone)*100/nCount));
			theOp.DoMessages();
		}
	}

	if (nCount > 1)
	{
		pGrid->LockUpdate(bLock);
		pGrid->Redraw();
	}

	if (pBlockCmd && !b)
	{
		delete pBlockCmd;
		pList->RemoveHead();
	}

	pGrid->m_bBlockCmd = FALSE;

	if (pGrid->m_bCellUndone)
		pGrid->OnCellUndone(pGrid->m_nLastRow, pGrid->m_nLastCol, pGrid->m_bLastSetEdit);

	return b;
}

LPCTSTR CGXBlockCmd::GetDescription() const
{
	return (LPCTSTR) m_sDesc;
}

//////////////////////////////////////////////////////////////
// CGXSetRowHeightCmd

CGXSetRowHeightCmd::CGXSetRowHeightCmd(ROWCOL nFromRow, ROWCOL nToRow, int* anHeightArray)
{
	ASSERT(anHeightArray != NULL);
	// ASSERTION-> anHeightArray must not be NULL ->END

	m_nFromRow = nFromRow;
	m_nToRow = nToRow;
	m_anHeightArray = anHeightArray;
}

CGXSetRowHeightCmd::~CGXSetRowHeightCmd()
{
	delete m_anHeightArray;
}

BOOL CGXSetRowHeightCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->SetRowHeight(m_nFromRow, m_nToRow, 0, m_anHeightArray, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXHideRowsCmd

CGXHideRowsCmd::CGXHideRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, BOOL* abHide)
{
	ASSERT(abHide != NULL);
	// ASSERTION-> abHide must not be NULL ->END

	m_nFromRow = nFromRow;
	m_nToRow = nToRow;
	m_abHide = abHide;
}

CGXHideRowsCmd::~CGXHideRowsCmd()
{
	delete m_abHide;
}

BOOL CGXHideRowsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->HideRows(m_nFromRow, m_nToRow, 0, m_abHide, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXSetDefaultRowHeightCmd

CGXSetDefaultRowHeightCmd::CGXSetDefaultRowHeightCmd(int nHeight)
{
	ASSERT(nHeight > 0);

	m_nHeight = nHeight;

}

BOOL CGXSetDefaultRowHeightCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->SetDefaultRowHeight(m_nHeight, GX_UPDATENOW, ctCmd);
}


//////////////////////////////////////////////////////////////
// CGXSetColWidthCmd

CGXSetColWidthCmd::CGXSetColWidthCmd(ROWCOL nFromCol, ROWCOL nToCol, int* anWidthArray)
{
	ASSERT(anWidthArray != NULL);
	// ASSERTION-> anWidthArray must not be NULL ->END

	m_nFromCol = nFromCol;
	m_nToCol = nToCol;
	m_anWidthArray = anWidthArray;

}

CGXSetColWidthCmd::~CGXSetColWidthCmd()
{
	delete m_anWidthArray;
}

BOOL CGXSetColWidthCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->SetColWidth(m_nFromCol, m_nToCol, 0, m_anWidthArray, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXHideColsCmd

CGXHideColsCmd::CGXHideColsCmd(ROWCOL nFromCol, ROWCOL nToCol, BOOL* abHide)
{
	ASSERT(abHide != NULL);
	// ASSERTION-> abHide must not be NULL ->END

	m_nFromCol = nFromCol;
	m_nToCol = nToCol;
	m_abHide = abHide;
}

CGXHideColsCmd::~CGXHideColsCmd()
{
	delete m_abHide;
}

BOOL CGXHideColsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->HideCols(m_nFromCol, m_nToCol, 0, m_abHide, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXSetDefaultColWidthCmd

CGXSetDefaultColWidthCmd::CGXSetDefaultColWidthCmd(int nWidth)
{
	ASSERT(nWidth > 0);

	m_nWidth = nWidth;

}

BOOL CGXSetDefaultColWidthCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->SetDefaultColWidth(m_nWidth, GX_UPDATENOW, ctCmd);
}


//////////////////////////////////////////////////////////////
// CGXMoveRowsCmd

CGXMoveRowsCmd::CGXMoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow)
{
	ASSERT(nToRow >= nFromRow && nDestRow != nFromRow);

	m_nFromRow = nFromRow;
	m_nToRow = nToRow;
	m_nDestRow = nDestRow;

}

BOOL CGXMoveRowsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->MoveRows(m_nFromRow, m_nToRow, m_nDestRow, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXMoveColsCmd

CGXMoveColsCmd::CGXMoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol)
{
	ASSERT(nToCol >= nFromCol && nDestCol != nFromCol);

	m_nFromCol = nFromCol;
	m_nToCol = nToCol;
	m_nDestCol = nDestCol;

}

BOOL CGXMoveColsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->MoveCols(m_nFromCol, m_nToCol, m_nDestCol, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXRemoveRowsCmd

CGXRemoveRowsCmd::CGXRemoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow)
{
	ASSERT(nToRow >= nFromRow);

	m_nFromRow = nFromRow;
	m_nToRow = nToRow;

}

BOOL CGXRemoveRowsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->RemoveRows(m_nFromRow, m_nToRow, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXRemoveColsCmd

CGXRemoveColsCmd::CGXRemoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol)
{
	ASSERT(nToCol >= nFromCol);

	m_nFromCol = nFromCol;
	m_nToCol = nToCol;

}

BOOL CGXRemoveColsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->RemoveCols(m_nFromCol, m_nToCol, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXInsertRowsCmd

CGXInsertRowsCmd::CGXInsertRowsCmd(ROWCOL nRow, ROWCOL nCount, int* anHeightArray, CObArray* pCellsArray, CObArray* pRowsArray, ROWCOL nColCount)
{
	m_nRow = nRow;
	m_nCount = nCount;
	m_pCellsArray = pCellsArray;
	m_pRowsArray = pRowsArray;
	m_nColCount = nColCount;
	m_anHeightArray = anHeightArray;
}

CGXInsertRowsCmd::~CGXInsertRowsCmd()
{
	DWORD dwSize = m_nCount*m_nColCount;

	if (m_pCellsArray)
	{
		if (dwSize < (DWORD) m_pCellsArray->GetSize())
		{
			CObList* pObList = (CObList*) m_pCellsArray->GetAt((int) dwSize);

			// Make sure this is a ObList
			if (pObList->IsKindOf(RUNTIME_CLASS(CObList)))
			{
				// Delete all objects - CObjects virtual destructor will let
				// the object cleanup itself 
				POSITION pos = pObList->GetHeadPosition();
				while (pos)			
					delete pObList->GetNext(pos);
				pObList->RemoveAll();
			}
		}

		for (int i = 0; i < m_pCellsArray->GetSize(); i++)
			delete m_pCellsArray->GetAt(i);
	}

	delete m_pCellsArray;

	if (m_pRowsArray)
		for (int i = 0; i < m_pRowsArray->GetSize(); i++)
			delete m_pRowsArray->GetAt(i);

	delete m_pRowsArray;

	delete m_anHeightArray;
}

BOOL CGXInsertRowsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->InsertRows(m_nRow, m_nCount, m_anHeightArray, m_pCellsArray, m_pRowsArray, m_nColCount, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXInsertColsCmd

CGXInsertColsCmd::CGXInsertColsCmd(ROWCOL nCol, ROWCOL nCount, int* anWidthArray, CObArray* pCellArray, CObArray* pColsArray, ROWCOL nRows)
{
	m_nCol = nCol;
	m_nCount = nCount;
	m_pCellsArray = pCellArray;
	m_pColsArray = pColsArray;
	m_nRowCount = nRows;
	m_anWidthArray = anWidthArray;

}

CGXInsertColsCmd::~CGXInsertColsCmd()
{
	DWORD dwSize = m_nCount*m_nRowCount;

	if (dwSize < (DWORD) m_pCellsArray->GetSize())
	{
		CObList* pObList = (CObList*) m_pCellsArray->GetAt((int) dwSize);

		// Make sure this is a ObList
		if (pObList->IsKindOf(RUNTIME_CLASS(CObList)))
		{
			// Delete all objects - CObjects virtual destructor will let
			// the object cleanup itself 
			POSITION pos = pObList->GetHeadPosition();
			while (pos)			
				delete pObList->GetNext(pos);
			pObList->RemoveAll();
		}
	}

	if (m_pCellsArray)
		for (int i = 0; i < m_pCellsArray->GetSize(); i++)
			delete m_pCellsArray->GetAt(i);

	delete m_pCellsArray;

	if (m_pColsArray)
		for (int i = 0; i < m_pColsArray->GetSize(); i++)
			delete m_pColsArray->GetAt(i);

	delete m_pColsArray;

	delete m_anWidthArray;
}

BOOL CGXInsertColsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->InsertCols(m_nCol, m_nCount, m_anWidthArray, m_pCellsArray, m_pColsArray, m_nRowCount, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXSetCoveredCellsCmd

CGXSetCoveredCellsCmd::CGXSetCoveredCellsCmd(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol)
{
	ASSERT(nToRow >= nRow && nToCol >= nCol);

	m_nRow = nRow;
	m_nCol = nCol;
	m_nToRow = nToRow;
	m_nToCol = nToCol;

}

BOOL CGXSetCoveredCellsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->SetCoveredCellsRowCol(m_nRow, m_nCol, m_nToRow, m_nToCol, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXSetStyleRangeCmd

CGXSetStyleRangeCmd::CGXSetStyleRangeCmd(const CGXRange& range, int nType, CObArray* pCellsArray)
{
	m_range = range;
	m_nType = nType;
	m_pCellsArray = pCellsArray;

}

CGXSetStyleRangeCmd::~CGXSetStyleRangeCmd()
{
	if (m_pCellsArray)
	{
		// Latest member in this array may contain advanced undo info (a CObList with CObjects)
		// that we need to clean up
		DWORD dwSize = m_range.GetWidth()*m_range.GetHeight();

		if (dwSize < (DWORD) m_pCellsArray->GetSize())
		{
			CObList* pObList = (CObList*) m_pCellsArray->GetAt((int) dwSize);

			// Make sure this is a ObList
			if (pObList->IsKindOf(RUNTIME_CLASS(CObList)))
			{
				// Delete all objects - CObjects virtual destructor will let
				// the object cleanup itself 
				POSITION pos = pObList->GetHeadPosition();
				while (pos)			
					delete pObList->GetNext(pos);
				pObList->RemoveAll();
			}
		}

		// Clean up all style objects
		for (int i = 0; i < m_pCellsArray->GetSize(); i++)
			delete m_pCellsArray->GetAt(i);
	}

	delete m_pCellsArray;
}

BOOL CGXSetStyleRangeCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->SetStyleRange(m_range, NULL, gxCopy, m_nType, m_pCellsArray, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXSetFrozenRowsCmd

CGXSetFrozenRowsCmd::CGXSetFrozenRowsCmd(ROWCOL nFrozenRows, ROWCOL nHeaderRows)
{
	m_nFrozenRows = nFrozenRows;
	m_nHeaderRows = nHeaderRows;
}

BOOL CGXSetFrozenRowsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->SetFrozenRows(m_nFrozenRows, m_nHeaderRows, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXSetFrozenColsCmd

CGXSetFrozenColsCmd::CGXSetFrozenColsCmd(ROWCOL nFrozenCols, ROWCOL nHeaderCols)
{
	m_nFrozenCols = nFrozenCols;
	m_nHeaderCols = nHeaderCols;
}

BOOL CGXSetFrozenColsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->SetFrozenCols(m_nFrozenCols, m_nHeaderCols, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXMoveDataRowsCmd

CGXMoveDataRowsCmd::CGXMoveDataRowsCmd(const CGXRange& rangeSort, CRowColArray* pawRowIndex)
{
	m_rangeSort = rangeSort;
	m_pawRowIndex = pawRowIndex;
}

CGXMoveDataRowsCmd::~CGXMoveDataRowsCmd()
{
	delete m_pawRowIndex;
}

BOOL CGXMoveDataRowsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->MoveDataRows(m_rangeSort, *m_pawRowIndex, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXMoveDataColsCmd

CGXMoveDataColsCmd::CGXMoveDataColsCmd(const CGXRange& rangeSort, CRowColArray* pawColIndex)
{
	m_rangeSort = rangeSort;
	m_pawColIndex = pawColIndex;
}

CGXMoveDataColsCmd::~CGXMoveDataColsCmd()
{
	delete m_pawColIndex;
}

BOOL CGXMoveDataColsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->MoveDataCols(m_rangeSort, *m_pawColIndex, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXChangeStylesMapCmd

CGXChangeStylesMapCmd::CGXChangeStylesMapCmd(const CGXStylesMap& stylesMap)
{
	m_pStylesMap = new CGXStylesMap(stylesMap);
}

CGXChangeStylesMapCmd::~CGXChangeStylesMapCmd()
{
		delete m_pStylesMap;
}

BOOL CGXChangeStylesMapCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->ChangeStylesMap(*m_pStylesMap, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXChangePropertiesCmd

CGXChangePropertiesCmd::CGXChangePropertiesCmd(const CGXProperties& Properties)
{
	m_pProperties = new CGXProperties(Properties);
}

CGXChangePropertiesCmd::~CGXChangePropertiesCmd()
{
		delete m_pProperties;
}

BOOL CGXChangePropertiesCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->ChangeProperties(*m_pProperties, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXChangeBaseStyleCmd

CGXChangeBaseStyleCmd::CGXChangeBaseStyleCmd(WORD wStyleId, const CGXStyle& style, const CString& sName)
{
	m_wStyleId = wStyleId;
	m_pBaseStyle = new CGXStyle(style);
	m_sName = sName;
}

CGXChangeBaseStyleCmd::~CGXChangeBaseStyleCmd()
{
		delete m_pBaseStyle;
}

BOOL CGXChangeBaseStyleCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->ChangeBaseStyle(m_wStyleId, *m_pBaseStyle, gxCopy, GX_UPDATENOW, ctCmd);
}

LPCTSTR CGXChangeBaseStyleCmd::GetDescription() const
{
	return m_sName;
}

//////////////////////////////////////////////////////////////
// CGXMoveCellsCmd

CGXMoveCellsCmd::CGXMoveCellsCmd(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo)
{
	m_rg = rg;
	m_nRow = nRow;
	m_nCol = nCol;
	m_pUndoInfo = pUndoInfo;
}

CGXMoveCellsCmd::~CGXMoveCellsCmd()
{
		delete m_pUndoInfo;
}

BOOL CGXMoveCellsCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	CGXRange rgDest(m_nRow, m_nCol, m_nRow+m_rg.GetHeight()-1, m_nCol+m_rg.GetWidth()-1);

	CObject* pInfo = m_pUndoInfo;
	m_pUndoInfo = NULL; 
	
	return pGrid->MoveCells(rgDest, m_rg.top, m_rg.left, pInfo, GX_UPDATENOW, ctCmd);
}

//////////////////////////////////////////////////////////////
// CGXSetRangeNameCmd

CGXSetRangeNameCmd::CGXSetRangeNameCmd(CString name, BOOL bOldRange, const CGXRange& oldRange)
{
	m_strName = name;
	m_bOldRange = bOldRange;
	m_oldRange = oldRange;
}

CGXSetRangeNameCmd::~CGXSetRangeNameCmd()
{
}

BOOL CGXSetRangeNameCmd::Execute(CGXGridCore* pGrid, GXCmdType ctType)
{
	if (m_bOldRange)
		return pGrid->SetRangeName(m_strName, m_oldRange, NULL, GX_UPDATENOW, ctType);
	else
		return pGrid->DeleteRangeName(m_strName, NULL, ctType);
}

//////////////////////////////////////////////////////////////
// CGXDeleteRangeNameCmd

CGXDeleteRangeNameCmd::CGXDeleteRangeNameCmd(CString name, const CGXRange& oldRange, CObject* pUndoInfo)
{
	m_strName = name;
	m_oldRange = oldRange;
	m_pUndoInfo = pUndoInfo;
}

CGXDeleteRangeNameCmd::~CGXDeleteRangeNameCmd()
{
		delete m_pUndoInfo;
}

BOOL CGXDeleteRangeNameCmd::Execute(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	return pGrid->SetRangeName(m_strName, m_oldRange, m_pUndoInfo, GX_UPDATENOW, ctCmd);
}


/////////////////////////////////////////////////////////////////////////////
// CGXCommandFactory 

CGXCommandFactory::CGXCommandFactory()
{
}

CGXCommand* CGXCommandFactory::CreateBlockCmd(LPCTSTR s)
{
	return new CGXBlockCmd(s);
}

CGXCommand* CGXCommandFactory::CreateSetRowHeightCmd(ROWCOL nFromRow, ROWCOL nToRow, int* anHeightArray)
{
	return new CGXSetRowHeightCmd(nFromRow, nToRow, anHeightArray);
}

CGXCommand* CGXCommandFactory::CreateHideRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, BOOL* abHide)
{
	return new CGXHideRowsCmd(nFromRow, nToRow, abHide);
}

CGXCommand* CGXCommandFactory::CreateSetDefaultRowHeightCmd(int nHeight)
{
	return new CGXSetDefaultRowHeightCmd(nHeight);
}

CGXCommand* CGXCommandFactory::CreateSetColWidthCmd(ROWCOL nFromCol, ROWCOL nToCol, int* anWidthArray)
{
	return new CGXSetColWidthCmd(nFromCol, nToCol, anWidthArray);
}

CGXCommand* CGXCommandFactory::CreateHideColsCmd(ROWCOL nFromCol, ROWCOL nToCol, BOOL* abHide)
{
	return new CGXHideColsCmd(nFromCol, nToCol, abHide);
}

CGXCommand* CGXCommandFactory::CreateSetDefaultColWidthCmd(int nWidth)
{
	return new CGXSetDefaultColWidthCmd(nWidth);
}

CGXCommand* CGXCommandFactory::CreateMoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow)
{
	return new CGXMoveRowsCmd(nFromRow, nToRow, nDestRow);
}

CGXCommand* CGXCommandFactory::CreateMoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol)
{
	return new CGXMoveColsCmd(nFromCol, nToCol, nDestCol);
}

CGXCommand* CGXCommandFactory::CreateRemoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow)
{
	return new CGXRemoveRowsCmd(nFromRow, nToRow);
}

CGXCommand* CGXCommandFactory::CreateRemoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol)
{
	return new CGXRemoveColsCmd(nFromCol, nToCol);
}

CGXCommand* CGXCommandFactory::CreateInsertRowsCmd(ROWCOL nRow, ROWCOL nCount, int* anHeightArray, CObArray* pCellsArray, CObArray* pRowsArray, ROWCOL nColCount)
{
	return new CGXInsertRowsCmd(nRow, nCount, anHeightArray, pCellsArray, pRowsArray, nColCount);
}

CGXCommand* CGXCommandFactory::CreateInsertColsCmd(ROWCOL nCol, ROWCOL nCount, int* anWidthArray, CObArray* pCellsArray, CObArray* pColsArray, ROWCOL nRowCount)
{
	return new CGXInsertColsCmd(nCol, nCount, anWidthArray, pCellsArray, pColsArray, nRowCount);
}

CGXCommand* CGXCommandFactory::CreateSetCoveredCellsCmd(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol)
{
	return new CGXSetCoveredCellsCmd(nRow, nCol, nToRow, nToCol);
}

CGXCommand* CGXCommandFactory::CreateSetStyleRangeCmd(const CGXRange& range, int nType, CObArray* pCellsArray)
{
	return new CGXSetStyleRangeCmd(range, nType, pCellsArray);
}

CGXCommand* CGXCommandFactory::CreateSetFrozenRowsCmd(ROWCOL nFrozenRows, ROWCOL nHeaderRows)
{
	return new CGXSetFrozenRowsCmd(nFrozenRows, nHeaderRows);
}

CGXCommand* CGXCommandFactory::CreateSetFrozenColsCmd(ROWCOL nFrozenCols, ROWCOL nHeaderCols)
{
	return new CGXSetFrozenColsCmd(nFrozenCols, nHeaderCols);
}

CGXCommand* CGXCommandFactory::CreateMoveDataRowsCmd(const CGXRange& rangeSort, CRowColArray* pawRowIndex)
{
	return new CGXMoveDataRowsCmd(rangeSort, pawRowIndex);
}

CGXCommand* CGXCommandFactory::CreateMoveDataColsCmd(const CGXRange& rangeSort, CRowColArray* pawColIndex)
{
	return new CGXMoveDataColsCmd(rangeSort, pawColIndex);
}

CGXCommand* CGXCommandFactory::CreateChangeStylesMapCmd(const CGXStylesMap& stylesMap)
{
	return new CGXChangeStylesMapCmd(stylesMap);
}

CGXCommand* CGXCommandFactory::CreateChangePropertiesCmd(const CGXProperties& Properties)
{
	return new CGXChangePropertiesCmd(Properties);
}

CGXCommand* CGXCommandFactory::CreateChangeBaseStyleCmd(WORD wStyleId, const CGXStyle& BaseStyle, const CString& sName)
{
	return new CGXChangeBaseStyleCmd(wStyleId, BaseStyle, sName);
}

CGXCommand* CGXCommandFactory::CreateMoveCellsCmd(const CGXRange& rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo)
{
	return new CGXMoveCellsCmd(rg, nRow, nCol, pUndoInfo);
}

CGXCommand* CGXCommandFactory::CreateSetRangeNameCmd(CString name, BOOL bOldRange, const CGXRange& oldRange)
{
	return new CGXSetRangeNameCmd(name, bOldRange, oldRange);
}

CGXCommand* CGXCommandFactory::CreateDeleteRangeNameCmd(CString name, const CGXRange& oldRange, CObject* pUndoInfo)
{
	return new CGXDeleteRangeNameCmd(name, oldRange, pUndoInfo);
}

BOOL CGXCommandFactory::SetAdvancedUndo(CGXGridCore* pGrid, BOOL bAdvUndo)
{
	CGXData* pData = pGrid->GetParam()->GetData();
	if (pData)
		return pData->SetAdvancedUndo(bAdvUndo);
	else
		return FALSE;
}

CObject* CGXCommandFactory::GetAdvancedUndoInfo(CGXGridCore* pGrid)
{
	CGXData* pData = pGrid->GetParam()->GetData();
	if (pData)
		return pData->GetAdvancedUndoInfo();
	else
		return NULL;
}

BOOL CGXCommandFactory::UndoAdvanced(CGXGridCore* pGrid, CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells)
{
	CGXData* pData = pGrid->GetParam()->GetData();
	if (pData && pAdvUndo)
		return pData->UndoAdvanced(pAdvUndo, bCreateUndoInfo, bOnlyToolCells);
	else
		return FALSE;
}

void CGXCommandFactory::CleanAdvancedUndo(CGXGridCore* pGrid)
{
	delete pGrid->GetAdvancedUndoInfo();
}

BOOL CGXCommandFactory::ExecuteCommand(CGXCommand* pCmd, CGXGridCore* pGrid, GXCmdType ctType)
{
	// Turn off cell locking (maybe the user
	// wants to undo the read-only state for cells)
	CGXGridParam* pParam = pGrid->GetParam();
	BOOL bLocked = pParam->IsLockReadOnly();
	pParam->SetLockReadOnly(FALSE);

	CGXData* pData = pParam->GetData();
	BOOL bRefresh = FALSE;
	if (pData && pCmd->m_pAdvUndo != NULL)
	{
		BOOL bOld = pGrid->SetAdvancedUndo(ctType != gxRollback);
		bRefresh = pGrid->UndoAdvanced(pCmd->m_pAdvUndo, TRUE, FALSE);
		pGrid->SetAdvancedUndo(bOld);
	}

	BOOL bDone = pCmd->Execute(pGrid, ctType);

	pParam->SetLockReadOnly(bLocked);

	return bDone;
}

void CGXCommandFactory::AddCommand(CGXGridCore* pGrid, CGXCommand* pCmd, GXCmdType ctCmd)
{
	ASSERT(ctCmd != gxRollback);

	CGXGridParam* pParam = pGrid->GetParam();

	if (ctCmd == gxDo)
		pParam->EmptyRedoList();

	// Check if there is undo info for matrix and tool worksheet functions
	// that overwrite other cells
	if (pCmd->m_pAdvUndo == NULL)
		pCmd->m_pAdvUndo = pGrid->GetAdvancedUndoInfo();

	CObList* pList;

	if (ctCmd == gxDo || ctCmd == gxRedo)
		pList = &pParam->GetUndoList();
	else
		pList = &pParam->GetRedoList();

	// Check if there is currently an transaction running
	if (pParam->m_nTrans > 0 || pGrid->m_bBlockCmd)
	{
		CGXBlockCmd* pBlockCmd = (CGXBlockCmd*) pList->GetHead();
		ASSERT(pBlockCmd->IsKindOf(RUNTIME_CLASS(CGXBlockCmd)));
		pList = &pBlockCmd->m_CommandList;
		// Commands will be added to transaction list
	}
	else if ((DWORD) pList->GetCount() > pParam->m_dwUndoLimit)
	{
		// remove last object if list gets too full
		delete pList->RemoveTail();
	}

	TRY
	{
		pCmd->m_bCCell = pGrid->GetCurrentCell(pCmd->m_ncRow, pCmd->m_ncCol);
		pList->AddHead(pCmd);
	}
	CATCH_ALL(e)
	{
		// delete command if it failed to add to be added to the objlist
			delete pCmd;
		GX_THROW_LAST
	}
	END_CATCH_ALL
}

void CGXCommandFactory::RemoveCommand(CGXGridCore* pGrid, GXCmdType ctCmd)
{
	ASSERT(ctCmd != gxRollback);

	CObList* pList;

	CGXGridParam* pParam = pGrid->GetParam();

	if (ctCmd == gxDo || ctCmd == gxRedo)
		pList = &pParam->GetUndoList();
	else
		pList = &pParam->GetRedoList();

	// Check if there is currently an transaction running
	if (pParam->m_nTrans > 0 || pGrid->m_bBlockCmd)
	{
		CGXBlockCmd* pBlockCmd = (CGXBlockCmd*) pList->GetHead();
		ASSERT(pBlockCmd->IsKindOf(RUNTIME_CLASS(CGXBlockCmd)));
		pList = &pBlockCmd->m_CommandList;
		// Commands will be added to transaction list
	}

	delete pList->RemoveHead();
}

BOOL CGXCommandFactory::Undo(CGXGridCore* pGrid)
{
	ROWCOL nRow, nCol;

	// Uncomment the following line if you want to be able
	// to undo changes in the current active cell. Otherwise
	// changes in current cell will simply be discarded and
	// no undo information generated.
	//
	// pGrid->TransferCurrentCell();

	// Cancel Edit Window
	if (pGrid->GetCurrentCell(&nRow, &nCol) && pGrid->IsActiveCurrentCell())
	{
		CGXControl* pControl = pGrid->GetControl(nRow, nCol);
		if (!pControl->OnCancelEditing())
			return FALSE;

		BOOL b = pControl->GetModify();
		pControl->Init(nRow, nCol);
		pControl->Refresh();
		pControl->OnCanceledEditing();

		// cell was modified
		if (b)
			return TRUE;

		// Fall trough!!! (cell was not modified)
	}

	CGXGridParam* pParam = pGrid->GetParam();

	CObList& undoList = pParam->GetUndoList();

	if (!undoList.IsEmpty())
	{
		CGXCommand* pCmd = (CGXCommand*) undoList.RemoveHead();

		ASSERT_VALID(pCmd);
		ASSERT(pCmd->IsKindOf(RUNTIME_CLASS(CGXCommand)));

		BOOL b = pGrid->ExecuteCommand(pCmd, pGrid, gxUndo);

		if (b)
			delete pCmd;
		else
			undoList.AddHead(pCmd);

		// Refresh formulas
		pGrid->RefreshViews();

		pGrid->UpdateScrollbars(FALSE);

		return b;
	}

	return FALSE;
}

BOOL CGXCommandFactory::Redo(CGXGridCore* pGrid)
{
	ROWCOL nRow, nCol;

	// Cancel Edit Window
	if (pGrid->GetCurrentCell(&nRow, &nCol) && pGrid->IsActiveCurrentCell())
	{
		if (!pGrid->TransferCurrentCell(FALSE, GX_INVALIDATE, FALSE))
			return FALSE;
	}

	CGXGridParam* pParam = pGrid->GetParam();

	CObList& redoList = pParam->GetRedoList();

	if (!redoList.IsEmpty())
	{
		CGXCommand* pCmd = (CGXCommand*) redoList.RemoveHead();

		ASSERT_VALID(pCmd);
		ASSERT(pCmd->IsKindOf(RUNTIME_CLASS(CGXCommand)));

		BOOL b = pGrid->ExecuteCommand(pCmd, pGrid, gxRedo);

		if (b)
		{
			if (pCmd->m_bCCell)
				pGrid->SetCurrentCell(pCmd->m_ncRow, pCmd->m_ncCol);

			delete pCmd;
		}
		else
			redoList.AddHead(pCmd);

		// Refresh formulas
		pGrid->RefreshViews();

		pGrid->UpdateScrollbars(FALSE);

		return b;
	}

	return FALSE;
}

void CGXCommandFactory::BeginTrans(CGXGridCore* pGrid, LPCTSTR s)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (pParam->m_nTrans == 0 && pParam->m_bUndoEnabled)
	{
		if (s)
			pGrid->m_sTransText = s;
		else
			pGrid->m_sTransText.Empty();

		CGXCommand* pCmd = new CGXBlockCmd(s);
		pCmd->m_bCCell = pGrid->GetCurrentCell(pCmd->m_ncRow, pCmd->m_ncCol);
		pParam->GetUndoList().AddHead(pCmd);

		pParam->m_nTrans++;
	}
	else if(pParam->m_bUndoEnabled)
		pParam->m_nTrans++;
}

void CGXCommandFactory::CommitTrans(CGXGridCore* pGrid)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (pParam->m_nTrans == 0 || !pParam->m_bUndoEnabled || --pParam->m_nTrans > 0)
		return;

	CObList& undoList = pParam->GetUndoList();

	CGXBlockCmd* pCmd = (CGXBlockCmd*) undoList.GetHead();
	ASSERT(pCmd->IsKindOf(RUNTIME_CLASS(CGXBlockCmd)));

	if (pCmd->m_CommandList.GetCount() == 0)
	{
		// there were no commands in the block
		delete pCmd;
		undoList.RemoveHead();
		return;
	}
	// Check for undo limit
	if ((DWORD) undoList.GetCount() > pParam->m_dwUndoLimit)
	{
		// remove last object if list gets too full
		delete undoList.RemoveTail();
	}
}

void CGXCommandFactory::Rollback(CGXGridCore* pGrid)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (pParam->m_nTrans == 0 || !pParam->m_bUndoEnabled || --pParam->m_nTrans > 0)
		return;

	pParam->m_nTrans = 0;

	CObList& undoList = pParam->GetUndoList();

	if (undoList.IsEmpty())
		return;

	CGXBlockCmd* pCmd = (CGXBlockCmd*) undoList.GetHead();
	ASSERT(pCmd->IsKindOf(RUNTIME_CLASS(CGXBlockCmd)));

	pCmd->Execute(pGrid, gxRollback);

	delete pCmd;
	undoList.RemoveHead();

	// if (pParam->m_bUndoEnabled)
	//  BlockCmd(gxRollback, _T("Restoring original state..."));

	// Refresh formulas
	pGrid->RefreshViews();
}

void CGXCommandFactory::OnCellUndone(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, BOOL bSetEdit)
{
	// called after undo

	if (pGrid->m_bBlockCmd)
	{
		pGrid->m_bLastSetEdit = bSetEdit;
		pGrid->m_nLastRow = nRow;
		pGrid->m_nLastCol = nCol;
		pGrid->m_bCellUndone = TRUE;
	}
	else if (bSetEdit && !pGrid->IsCurrentCell(nRow, nCol))
		// position active cell
		pGrid->SetCurrentCell(nRow, nCol);
	else
		// simple scroll cell in view
		pGrid->ScrollCellInView(nRow, nCol);

	pGrid->UpdateWindow();
}

BOOL CGXCommandFactory::CanUndo(CGXGridCore* pGrid, CCmdUI* pCmdUI)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (pParam == NULL)
	{
		if (pCmdUI)
			pCmdUI->Enable(FALSE);
		return FALSE;
	}

	ROWCOL nRow, nCol;
	BOOL bCurrent = FALSE;
	BOOL b  = FALSE;

	if (pGrid->IsActiveCurrentCell() && pGrid->GetCurrentCell(nRow, nCol))
		b = bCurrent = pGrid->GetControl(nRow, nCol)->GetModify();

	CObList& undoList = pParam->GetUndoList();

	b |= !undoList.IsEmpty();

	if (pCmdUI && pCmdUI->m_pMenu)
	{
		if (pGrid->m_sEditUndo.IsEmpty())
		{
			// Determine if I can display undo information in the menu

			// If you want to enable this feature, you have to change
			// the prompt for the menu item. This method searches
			// for the third entrie in the prompt (separated by '\n')
			// and replaces the %1 with the undo information text.
			//
			// Example:
			// MENUITEM "&Undo\tCtrl+Z",            ID_EDIT_UNDO
			// and in the stringtable:
			// ID_EDIT_UNDO  "Undo the last action\nUndo\n&Undo %1\tCtrl+Z"

			// determine prompt for the menu
			CString str;
			str.LoadString(pCmdUI->m_nID);
			TCHAR pszMenuText[255];

			// skip the first two entries

			// find first separator
			int n = str.Find(_T('\n'));
			if (n != -1)
			{
				str = str.Mid(n+1);

				// find second separator
				n = str.Find(_T('\n'));
			}

			// second separator found?
			if (n != -1)
			{
				str = str.Mid(n+1);
				pGrid->m_sEditUndo = str;
			}

			// if third parameter is not specified, try to use the menu text
			// (this is for compatibility with OG 1.0)
			else if (pCmdUI->m_pMenu->GetMenuString(pCmdUI->m_nID, pszMenuText, 255, MF_BYCOMMAND) > 0)
				pGrid->m_sEditUndo = pszMenuText;

			// if everything failed, use an hardcoded string
			else
				pGrid->m_sEditUndo = _T("Undo %1");
		}

		CString s;
		LPCTSTR pszCmd = _T("");
		if (bCurrent)
			pszCmd = pGrid->m_pAppData->strmUndoCurrentCell;
		else if (!undoList.IsEmpty())
			pszCmd = ((CGXCommand*) undoList.GetHead())->GetDescription();

		AfxFormatStrings(s, (LPCTSTR) pGrid->m_sEditUndo, &pszCmd, 1);
		pCmdUI->SetText(s);
	}

	if (pCmdUI)
		pCmdUI->Enable(b);
	return b;
}

BOOL CGXCommandFactory::CanRedo(CGXGridCore* pGrid, CCmdUI* pCmdUI)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (pParam == NULL)
	{
		if (pCmdUI)
			pCmdUI->Enable(FALSE);
		return FALSE;
	}

	CObList& redoList = pParam->GetRedoList();

	if (pCmdUI && pCmdUI->m_pMenu)
	{
		if (pGrid->m_sEditRedo.IsEmpty())
		{
			// Determine if I can display redo information in the menu

			// If you want to enable this feature, you have to change
			// the prompt for the menu item. This method searches
			// for the third entrie in the prompt (separated by '\n')
			// and replaces the %1 with the redo information text.
			//
			// Example:
			// MENUITEM "&Redo\tCtrl+A",            ID_EDIT_REDO
			// and in the stringtable:
			// ID_EDIT_REDO  "Redo the last action\nRedo\n&Redo %1\tCtrl+A"

			// determine prompt for the menu
			CString str;
			str.LoadString(pCmdUI->m_nID);
			TCHAR pszMenuText[255];

			// skip the first two entries

			// find first separator
			int n = str.Find(_T('\n'));
			if (n != -1)
			{
				str = str.Mid(n+1);

				// find second separator
				n = str.Find(_T('\n'));
			}

			// second separator found?
			if (n != -1)
			{
				str = str.Mid(n+1);
				pGrid->m_sEditRedo = str;
			}

			// if third parameter is not specified, try to use the menu text
			// (this is for compatibility with OG 1.0)
			else if (pCmdUI->m_pMenu->GetMenuString(pCmdUI->m_nID, pszMenuText, 255, MF_BYCOMMAND) > 0)
				pGrid->m_sEditRedo = pszMenuText;

			// if everything failed, use an hardcoded string
			else
				pGrid->m_sEditRedo = _T("Redo %1");
		}

		CString s;
		LPCTSTR pszCmd = _T("");
		if (!redoList.IsEmpty())
			pszCmd = ((CGXCommand*) redoList.GetHead())->GetDescription();

		AfxFormatStrings(s, (LPCTSTR) pGrid->m_sEditRedo, &pszCmd, 1);
		pCmdUI->SetText(s);
	}

	if (pCmdUI)
		pCmdUI->Enable(!redoList.IsEmpty());
	return !redoList.IsEmpty();
}

void CGXGridCore::ImplementUndoRedo()
{
	if (m_pUndoImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//AutoDeletePtr(m_pUndoImp = new CGXCommandFactory);
		m_pUndoImp = new CGXCommandFactory;
	}
}


BOOL CGXCommandFactory::CreateRemoveRowsUndoInfo(CGXGridCore* pGrid, ROWCOL& nFromRow, ROWCOL& nCount, ROWCOL& nColCount, CObArray*& pOldCellsArray, CObArray*& pOldRowsArray, CGXLongOperation& theOp)
{
	// Undo
	BOOL bNoUndo = FALSE;

	// Try, if Array fits in memory
	TRY
	{
		DWORD dwSize = 0;
		DWORD dwRows = 0;

		BOOL bCanceled = FALSE;

		if ((pGrid->GetParam()->m_nRemoveRowsFlags & GX_RMUNDO_BASESTYLES) > 0)
			dwRows = nCount;

		if ((pGrid->GetParam()->m_nRemoveRowsFlags & GX_RMUNDO_CELLSTYLES) > 0)
		{
			dwSize = nCount * nColCount;

			// Sorry ... too much!
			if (dwSize >= INT_MAX || nColCount > SHRT_MAX || nCount > SHRT_MAX)
			{
				if (AfxMessageBox(GX_IDS_CANNOTUNDO, MB_OKCANCEL) == IDCANCEL)
					return FALSE;
				bNoUndo = TRUE;
			}
			else
			{

				pOldCellsArray = new CObArray;
				pOldCellsArray->SetSize((int) dwSize);

				// Store styles in array, but allow user to abort
				for (ROWCOL r = 0; r < nCount; r++)
				{
					for (ROWCOL c = 0; c < nColCount; c++)
					{
						CGXStyle* pStyle;
						DWORD dwIndex;

						pStyle = pGrid->CreateStyle();
						dwIndex = r*nColCount+c;

						if (pGrid->GetStyleRowCol(nFromRow+r, c, *pStyle, gxCopy, pGrid->m_nExpressionValueType))
							pOldCellsArray->SetAt((int) dwIndex, pStyle);
						else
							pGrid->m_StyleBuffer.AddHead(pStyle);

						// check, if user pressed ESC to cancel
						if (theOp.NeedMessages())
						{
							theOp.SetPercentDone((int) (dwIndex * 100 / (dwSize+dwRows)));

							theOp.DoMessages(bCanceled);

							if (bCanceled)
								AfxThrowUserException();
						}
					}
				}
			}
		}

		if (!bNoUndo && (pGrid->GetParam()->m_nRemoveRowsFlags & GX_RMUNDO_BASESTYLES) > 0)
		{
			// Sorry ... too much!
			if (nCount > SHRT_MAX)
			{
				if (AfxMessageBox(GX_IDS_CANNOTUNDO, MB_OKCANCEL) == IDCANCEL)
					return FALSE;
				bNoUndo = TRUE;
			}
			else
			{
				pOldRowsArray = new CObArray;
				pOldRowsArray->SetSize((int) nCount);

				// Store styles in array, but allow user to abort
				for (ROWCOL r = 0; r < nCount; r++)
				{
					CGXStyle* pStyle;

					pStyle = pGrid->CreateStyle();

					if (pGrid->GetStyleRowCol(nFromRow+r, 0, *pStyle, gxCopy, -1))
						pOldRowsArray->SetAt((int) r, pStyle);
					else
						pGrid->m_StyleBuffer.AddHead(pStyle);

					// check, if user pressed ESC to cancel
					if (theOp.NeedMessages())
					{
						theOp.SetPercentDone((int) ((dwSize + r) * 100 / (dwSize+dwRows)));

						theOp.DoMessages(bCanceled);

						if (bCanceled)
							AfxThrowUserException();
					}
				}
			}
		}
	}
	CATCH(CMemoryException, e)
	{
		// clean up
		if (pOldCellsArray)
		{
			for (int i = 0; i < pOldCellsArray->GetSize(); i++)
				delete pOldCellsArray->GetAt(i);
		}
		delete pOldCellsArray;
		pOldCellsArray = NULL;

		if (pOldRowsArray)
		{
			for (int i = 0; i < pOldRowsArray->GetSize(); i++)
				delete pOldRowsArray->GetAt(i);
		}
		delete pOldRowsArray;
		pOldRowsArray = NULL;

		GX_THROW_LAST

		// shall I continue?
		if (AfxMessageBox(GX_IDS_CANNOTUNDO, MB_OKCANCEL) == IDCANCEL)
			return FALSE;
	}
	AND_CATCH(CUserException, e)
	{
		// clean up
		if (pOldCellsArray)
		{
			for (int i = 0; i < pOldCellsArray->GetSize(); i++)
				delete pOldCellsArray->GetAt(i);
		}
		delete pOldCellsArray;
		pOldCellsArray = NULL;

		if (pOldRowsArray)
		{
			for (int i = 0; i < pOldRowsArray->GetSize(); i++)
				delete pOldRowsArray->GetAt(i);
		}
		delete pOldRowsArray;
		pOldRowsArray = NULL;

		GX_THROW_LAST

		return FALSE;
	}
	END_CATCH

	return TRUE;
}


BOOL CGXCommandFactory::CreateRemoveColsUndoInfo(CGXGridCore* pGrid, ROWCOL& nFromCol, ROWCOL& nCount, ROWCOL& nRowCount, CObArray*& pOldCellsArray, CObArray*& pOldColsArray, CGXLongOperation& theOp)
{
	// Undo
	BOOL bNoUndo = FALSE;

	// Try, if Array fits in memory
	TRY
	{
		DWORD dwSize = 0;
		DWORD dwCols = 0;

		BOOL bCanceled = FALSE;

		if ((pGrid->GetParam()->m_nRemoveColsFlags & GX_RMUNDO_BASESTYLES) > 0)
			dwCols = nCount;

		if ((pGrid->GetParam()->m_nRemoveColsFlags & GX_RMUNDO_CELLSTYLES) > 0)
		{
			dwSize = nRowCount * nCount;

			// Sorry ... too much!
			if (dwSize >= INT_MAX || nRowCount > SHRT_MAX || nCount > SHRT_MAX)
			{
				if (AfxMessageBox(GX_IDS_CANNOTUNDO, MB_OKCANCEL) == IDCANCEL)
					return FALSE;
				bNoUndo = TRUE;
			}
			else
			{

				pOldCellsArray = new CObArray;
				pOldCellsArray->SetSize((int) dwSize);

				// Store styles in array, but allow user to abort
				for (ROWCOL r = 0; r < nRowCount; r++)
				{
					for (ROWCOL c = 0; c < nCount; c++)
					{
						CGXStyle* pStyle;
						DWORD dwIndex;

						pStyle = pGrid->CreateStyle();
						dwIndex = r*nCount+c;

						if (pGrid->GetStyleRowCol(r, nFromCol+c, *pStyle, gxCopy, pGrid->m_nExpressionValueType))
							pOldCellsArray->SetAt((int) dwIndex, pStyle);
						else
							pGrid->m_StyleBuffer.AddHead(pStyle);

						// check, if user pressed ESC to cancel
						if (theOp.NeedMessages())
						{
							theOp.SetPercentDone((int) (dwIndex * 100 / (dwSize + dwCols)));

							theOp.DoMessages(bCanceled);

							if (bCanceled)
								AfxThrowUserException();
						}

					}
				}
			}
		}

		if (!bNoUndo && (pGrid->GetParam()->m_nRemoveColsFlags & GX_RMUNDO_BASESTYLES) > 0)
		{
			// Sorry ... too much!
			if (nCount > SHRT_MAX)
			{
				if (AfxMessageBox(GX_IDS_CANNOTUNDO, MB_OKCANCEL) == IDCANCEL)
					return FALSE;
				bNoUndo = TRUE;
			}
			else
			{
				pOldColsArray = new CObArray;
				pOldColsArray->SetSize((int) nCount);

				// Store styles in array, but allow user to abort
				for (ROWCOL c = 0; c < nCount; c++)
				{
					CGXStyle* pStyle;

					pStyle = pGrid->CreateStyle();

					if (pGrid->GetStyleRowCol(0, nFromCol+c, *pStyle, gxCopy, -1))
						pOldColsArray->SetAt((int) c, pStyle);
					else
						pGrid->m_StyleBuffer.AddHead(pStyle);

					// check, if user pressed ESC to cancel
					if (theOp.NeedMessages())
					{
						theOp.SetPercentDone((int) ((c + dwSize) / (dwSize + nCount)));

						theOp.DoMessages(bCanceled);

						if (bCanceled)
							AfxThrowUserException();
					}
				}
			}
		}
	}
	CATCH(CMemoryException, e)
	{
		// clean up
		if (pOldCellsArray)
		{
			for (int i = 0; i < pOldCellsArray->GetSize(); i++)
				delete pOldCellsArray->GetAt(i);
		}
		delete pOldCellsArray;
		pOldCellsArray = NULL;

		if (pOldColsArray)
		{
			for (int i = 0; i < pOldColsArray->GetSize(); i++)
				delete pOldColsArray->GetAt(i);
		}
		delete pOldColsArray;
		pOldColsArray = NULL;

		GX_THROW_LAST

		// shall I continue?
		if (AfxMessageBox(GX_IDS_CANNOTUNDO, MB_OKCANCEL) == IDCANCEL)
			return FALSE;
	}
	AND_CATCH(CUserException, e)
	{
		// clean up
		if (pOldCellsArray)
		{
			for (int i = 0; i < pOldCellsArray->GetSize(); i++)
				delete pOldCellsArray->GetAt(i);
		}
		delete pOldCellsArray;
		pOldCellsArray = NULL;

		if (pOldColsArray)
		{
			for (int i = 0; i < pOldColsArray->GetSize(); i++)
				delete pOldColsArray->GetAt(i);
		}
		delete pOldColsArray;
		pOldColsArray = NULL;

		GX_THROW_LAST

		return FALSE;
	}
	END_CATCH

	return TRUE;
}
