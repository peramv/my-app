///////////////////////////////////////////////////////////////////////////////
// gxengine.cpp : Objective Grid interface to the formula engine
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
#define _RW_IMPL

#include "stdafx.h"

#include "grid\gxsinc.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXENGINE_H_
#include "grid\gxengine.h"
#endif

#if _MFC_VER >= 0x0300
#ifndef _WINNLS_
#include "winnls.h"
#endif
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXENGINE")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CGXFormulaSheet, CGXData, 0 /* schema number*/ )

// CGXGridCore methods that will establish link dependencies to Formula Engine

void CGXGridCore::EnableFormulaEngine()
{
	// if called before CGXGridCore::OnGridInitialUpdate, CGXGridCore
	// will create a CGXFormulaSheet instead of CGXData

	ASSERT(!m_bInitDone);
	// ASSERTION-> Please place the call to this function
	// before calling Initialize or CGXGridView::OnInitialUpdate.
	// ->END

	ASSERT(!GXGetAppData()->m_bLocaleNumbersEnabled);
	//ASSERTION: LocaleNumbers not supported in formula engine

	GXGetAppData()->m_bFormulaEnabled = TRUE;

	m_pDefaultDataClass = RUNTIME_CLASS(CGXFormulaSheet);
	m_nExpressionValueType = GX_VALUE_EXPRESSION;

	ImplementRangeName();
	CGXDrawingAndFormatting::ImplementNumberFormatting();
}

// shortcut to get a pointer to sheet context

CGXFormulaSheet* CGXGridCore::GetSheetContext()
{
	CGXGridParam* pParam = GetParam();

	if (pParam && pParam->GetData() && pParam->GetData()->IsKindOf(RUNTIME_CLASS(CGXFormulaSheet)))
		return (CGXFormulaSheet*) pParam->GetData();

	return NULL;
}


//////////////////////////////////////////////////////////////////
// struct GX_ENGINE_STATE


GX_ENGINE_STATE* __cdecl GXGetEngineState()
{
	CGXAppData* pAppData = GXGetAppData();
	if (pAppData->m_pEngineState == NULL)
		pAppData->m_pEngineState = new GX_ENGINE_STATE;

	return (GX_ENGINE_STATE*) pAppData->m_pEngineState;
}

GX_ENGINE_STATE::GX_ENGINE_STATE()
{
	print_lotus = 0;
	print_lc = 0;
	print_at_sign = 0;

	expr_err_flag = 0;
	error_reason = 0;
	error_position = 0;

	xs_error_silence = 0;
	xs_error_status = 0;
	xs_error_code = 0;
	last_severity = -1; /* initialize to impossible code */
	doing_insert_or_delete = 0;

	m_pWorksheetFunctions = NULL;

	iso_escape = 0;
}

GX_ENGINE_STATE::~GX_ENGINE_STATE()
{
	delete m_pWorksheetFunctions;
}

void GX_ENGINE_STATE::SetWorksheetFunctionClass(CGXWorksheetFunctions* pClassObject)
{
	if (m_pWorksheetFunctions)
		delete m_pWorksheetFunctions;

	m_pWorksheetFunctions = pClassObject;
}

void __cdecl _gx_restore_cells(int si, gxCell* cp)
{
	gxCell* next_cell;

	while (cp != NULL)
	{
		next_cell = cp->next;
		_gx_destroy_cell(si, _gx_find_cell(si, cp->row, cp->col));
		_gx_insert_cell(si, cp);
		// TRACE(_T("_gx_insert_cell(%d,%d)\n"), cp->row, cp->col);
		GX_CELL_SET_FLAG(cp, GX_UPDATED);
		cp = next_cell;
	}
}

//////////////////////////////////////////////////////////////////
// CGXUndoEngineCellsInfo
// holds undo info moving cells (cut/paste, ole dnd)

class CGXUndoEngineCellsInfo: public CObject
{
	GRID_DECLARE_DYNAMIC(CGXUndoEngineCellsInfo);

public:
	CGXUndoEngineCellsInfo()
		{ m_pCells = m_pToolCells = NULL; m_pDeletedRangeName = NULL; }

	~CGXUndoEngineCellsInfo()
	{     
		gxCell* next_cell = NULL;
		for (gxCell* cp = m_pCells; cp != NULL; cp = next_cell)
		{
			next_cell = cp->next;
			_gx_free_cell(cp);
		}
		m_pCells = NULL; 

		if (m_pDeletedRangeName)
		{   
			GX_XSfree((m_pDeletedRangeName)->name);   /* free the name */
			GX_XSfree(m_pDeletedRangeName);   /* free the struct */
		}
	}

	gxCell* m_pCells;
	gxCell* m_pToolCells;
	gxRange m_undo_dst; // may not be initialized
	BOOL m_bClearDest;
	gxRangeName *m_pDeletedRangeName;
};

// move ranges in one step - CGXGridCore expects CGXFormulaSheet
// to create efficient undo info and store it in pUndoInfo

IMPLEMENT_DYNAMIC(CGXUndoEngineCellsInfo, CObject);

//////////////////////////////////////////////////////////////////
// class CGXFormulaSheet

CGXFormulaSheet::CGXFormulaSheet()
{
	m_nSheetContext = _gx_new_sheet_context();
	m_bAdvancedUndoInfo = FALSE;
	gxSheetContext* pContext = _gx_get_context_ptr(m_nSheetContext);
	pContext->m_pSheetContext = this;
	m_pAdvUndoInfo = NULL;
	m_bsConstraint = 0;
}

CGXFormulaSheet::~CGXFormulaSheet()
{
	delete m_pAdvUndoInfo;
	_gx_free_sheet_context(m_nSheetContext);
}

void CGXFormulaSheet::InitParam(CGXGridParam* pParam)
{
	pParam->m_bDirectCopyPaste = TRUE;
	pParam->m_bDirectCutPaste = TRUE;
	pParam->m_bDirectDragDrop = TRUE;
	pParam->m_nDisplayExpression = GX_EXPR_DISPLAYACTIVE;
}

// Value Interface
BOOL CGXFormulaSheet::SetFormulaRowCol(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszFormula)
{
	// TRACE(_T("SetFormulaRowCol '%s'\n"), pszFormula);

	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);
	int c = GetEngineCol(nCol);

	if (*pszFormula != _T('='))
	{
		TRACE(_T("Error in CGXFormulaSheet::SetFormulaRowCol - wrong formula\n"));
		TRACE(_T("formula does not start with equal sign '%s'\n"), pszFormula);
		return FALSE;
	}

	int status = _gx_cell_put_formula(si, r, c, pszFormula, NULL, NULL);

	if (status)
	{
		// correct formula
		gxCell *cp = _gx_find_cell(si, r, c);

		BOOL bOld = SetPreserveCells(m_bAdvancedUndoInfo);

		if (cp->cell_type == GX_FORMULA_CELL)
		{
			int mask = _gx_freeze_list_order(si, GX_ALL_LISTS);
			_gx_evaluate_cell(si, cp);
			_gx_unfreeze_list_order(si, mask);
		}

		// Some worksheet function (especially tools and matrix operations)
		// require advanced undo info
		CheckAdvancedUndo(TRUE, FALSE);

		SetPreserveCells(bOld);

		// operation successfull...
		return TRUE;
	}
	else
	{
		TCHAR line[512];
		wsprintf(line, _T("ERROR: %s (Pos %d)"), _gx_xs_error_msg(_gx_get_error_reason()), _gx_get_error_position());

		wsprintf(_gx_get_context_ptr(si)->szErrorText, _T("Cell %s%d: %s"),
//			_gx_col_to_text(c - _gx_get_col_shift()), r - _gx_get_row_shift(),
			_gx_col_to_text(c), r,
			line);
		TRACE(_T("%s\n"), _gx_get_context_ptr(si)->szErrorText);
		_gx_get_context_ptr(m_nSheetContext)->first_error = 0;

		// operation failed...
		return FALSE;
	}
}

// Some worksheet function (especially tools and matrix operations)
// require advanced undo info
void CGXFormulaSheet::CheckAdvancedUndo(BOOL bClearDest, BOOL bToolCells)
{
	int si = m_nSheetContext;
	gxSheetContext* pContext = _gx_get_context_ptr(m_nSheetContext);

	if (bToolCells)
	{
		BOOL bOld = SetPreserveCells(m_bAdvancedUndoInfo);

		int nOld = _gx_get_recalc_method(si);
		_gx_set_recalc_method(si, GX_RECALC_FOREGROUND);
		_gx_recalc(si);
		_gx_set_recalc_method(si, nOld);

		SetPreserveCells(bOld);
	}

	if (pContext->preserve_list)
	{
		if (m_pAdvUndoInfo == NULL)
			m_pAdvUndoInfo = new CGXUndoEngineCellsInfo;

		gxCell* tail_cell = NULL;
		if (bToolCells)
		{
			tail_cell = m_pAdvUndoInfo->m_pToolCells;
			m_pAdvUndoInfo->m_pToolCells = pContext->preserve_list;
		}
		else
		{
			tail_cell = m_pAdvUndoInfo->m_pCells;
			m_pAdvUndoInfo->m_pCells = pContext->preserve_list;
		}

		// Append existing undo cells
		if (tail_cell)
		{
			gxCell* cp = NULL;
			for (cp = pContext->preserve_list; cp->next != NULL; cp = cp->next)
				NULL;

			cp->next = tail_cell;
		}

		m_pAdvUndoInfo->m_undo_dst = pContext->undo_dst;
		m_pAdvUndoInfo->m_bClearDest = pContext->is_undo_init && bClearDest;
		pContext->preserve_list = NULL;
		pContext->is_undo_init = 0;
	}
}

CObject* CGXFormulaSheet::GetAdvancedUndoInfo()
{
	CObject* pAdvUndo = m_pAdvUndoInfo;
	m_pAdvUndoInfo = NULL;

	return pAdvUndo;
}

BOOL CGXFormulaSheet::UndoAdvanced(CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells)
{
	// TRACE(_T("UndoAdvancedList\n"));

	if (pAdvUndo == NULL || !pAdvUndo->IsKindOf(RUNTIME_CLASS(CGXUndoEngineCellsInfo)))
		return FALSE;

	CGXUndoEngineCellsInfo* pInfo = (CGXUndoEngineCellsInfo*) pAdvUndo;

	int si = m_nSheetContext;
	gxSheetContext* pContext = _gx_get_context_ptr(si);
	// int nOld = pContext->keep_empties;
	// pContext->keep_empties = TRUE;
	
	int mask = _gx_freeze_list_order(m_nSheetContext, GX_ALL_LISTS);

	pContext->do_preserve = bCreateUndoInfo;
	pContext->preserve_list = NULL;

	if (pInfo->m_bClearDest)	 // SetStyleRange really needs this
		_gx_clear_range(si, pInfo->m_undo_dst);

	_gx_restore_cells(si, pInfo->m_pToolCells);
	pInfo->m_pToolCells = NULL;

	if (!bOnlyToolCells)
	{
		_gx_restore_cells(si, pInfo->m_pCells);
		pInfo->m_pCells = NULL;
	}

	_gx_add_recalc_range(si, &pInfo->m_undo_dst);

	if (bCreateUndoInfo)
	{
		if (bOnlyToolCells)
			pInfo->m_pToolCells = pContext->preserve_list;
		else
			pInfo->m_pCells = pContext->preserve_list;
		pInfo->m_bClearDest = FALSE;
		pContext->preserve_list = NULL;
	}

	pContext->do_preserve = FALSE;

	_gx_unfreeze_list_order(m_nSheetContext, mask);

	return TRUE;
}

BOOL CGXFormulaSheet::SetAdvancedUndo(BOOL b)
{
	BOOL bOld = m_bAdvancedUndoInfo;

	m_bAdvancedUndoInfo = b;

	return bOld;
}

BOOL CGXFormulaSheet::SetPreserveCells(BOOL b)
{
	gxSheetContext* pContext = _gx_get_context_ptr(m_nSheetContext);
	
	BOOL bOld = pContext->do_preserve;

	pContext->do_preserve = b;

	return bOld;
}

int CGXFormulaSheet::GetEngineRow(ROWCOL nRow)
{
	return (int) max(GX_MIN_ROW, ((int) nRow - 1 + GX_MIN_ROW));
}

int CGXFormulaSheet::GetEngineCol(ROWCOL nCol)
{
	return (int) max(GX_MIN_COL, ((int) nCol - 1 + GX_MIN_COL));
}

ROWCOL CGXFormulaSheet::GetGridRow(int nEngineRow)
{
	return (ROWCOL) (nEngineRow + 1 - GX_MIN_ROW);
}

ROWCOL CGXFormulaSheet::GetGridCol(int nEngineCol)
{
	return (ROWCOL) (nEngineCol + 1 - GX_MIN_COL);
}

BOOL CGXFormulaSheet::SetTextRowCol(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszText)
{
	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);
	int c = GetEngineCol(nCol);

	int status = _gx_cell_put_label(si, r, c, pszText, NULL);

	if (*pszText == _T('\0'))
	{
		// mark cell as empty
		gxCell* cp = _gx_find_cell(si, r, c);

		gxCellValue cv;
		cv.type = GX_VALUE_NONE;

		_gx_set_cell_value(cp, &cv);
	}

	return status != 0;
}

BOOL CGXFormulaSheet::SetNumberRowCol(ROWCOL nRow, ROWCOL nCol, double number)
{
	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);
	int c = GetEngineCol(nCol);

	int status = _gx_cell_put_number(si, r, c, number, NULL);

	return status != 0;
}


BOOL CGXFormulaSheet::SetFormatRowCol(ROWCOL nRow, ROWCOL nCol, unsigned format, unsigned places)
{
	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);
	int c = GetEngineCol(nCol);

	CGXStyle* pTStyle = Grid()->CreateStyle();

	pTStyle->SetFormat(format);
	pTStyle->SetPlaces(places);

	gxCell *cp = _gx_find_cell(si, r, c);

	if (cp == NULL)				   
	{
		_gx_cell_put_label(si, r, c, _T(""), NULL);
		cp = _gx_find_cell(si, r, c);
	}

	if (cp)
	{
		if (cp->pStyle)
		{
			cp->pStyle->ChangeStyle(*pTStyle, gxOverride);
			Grid()->RecycleStyle(pTStyle);
		}
		else
			cp->pStyle = pTStyle;
	}

	return TRUE;
}

unsigned CGXFormulaSheet::GetFormatRowCol(ROWCOL nRow, ROWCOL nCol, unsigned* pPlaces)
{
	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);
	int c = GetEngineCol(nCol);

	gxCell *cp = _gx_find_cell(si, r, c);

	if (cp && cp->pStyle && cp->pStyle->GetIncludeFormat())
	{
		if (pPlaces)
			*pPlaces = cp->pStyle->GetPlaces();

		return cp->pStyle->GetFormat();
	}

	return GX_FMT_DEFAULT;
}

BOOL CGXFormulaSheet::SetExpressionRowCol(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszInput)
	// parse text, set formula/text/number, apply format (if date)
{
	int status = 0;
	double d;
	unsigned nFormat, nValFormat;
	unsigned nValPlaces;
	
	if (*pszInput == _T('\0'))
		status = SetTextRowCol(nRow, nCol, pszInput);

	else if (GXDeval(pszInput, &d, &nValFormat, &nValPlaces))
	{
		status = SetNumberRowCol(nRow, nCol, d);

		nFormat = GetFormatRowCol(nRow, nCol);

		if (GX_IS_DATE_FORMAT(nFormat) || GX_IS_TIME_FORMAT(nFormat))
			SetFormatRowCol(nRow, nCol, GX_FMT_GEN, 15);
	}
	else if (_tcsicmp(pszInput, _T("#N/A")) == 0)
	{
		status = SetFormulaRowCol(nRow, nCol, _T("=NA()"));
	}
	else
	{
#if _MFC_VER >= 0x0300
		COleDateTime dt;
#endif
		switch (pszInput[0])
		{
		case _T('='):
			status = SetFormulaRowCol(nRow, nCol, pszInput);
			break;

		case _T('\''):
			status = SetTextRowCol(nRow, nCol, pszInput+1);
			break;
				
		default:
#if _MFC_VER >= 0x0300
			if (dt.ParseDateTime(pszInput))
			{
				status = SetNumberRowCol(nRow, nCol, (double) dt);

				if (status && !GX_IS_DATE_FORMAT(GetFormatRowCol(nRow, nCol)))
				{
					int idate = (int) (double) dt;

					unsigned fmt;

					// only date ?
					if ((double) dt == (double) idate)
						fmt = GX_FMT_DATE;

					// only time  ?
					else if (idate == 0)
						fmt = GX_FMT_TIME;

					// both date and time
					else
						fmt = GX_FMT_DATETIME;

					SetFormatRowCol(nRow, nCol, fmt, 0);
				}
			}
			else
#else
			TIMESTAMP_STRUCT tm;
			if (GXParseDateTime(&tm, pszInput))
			{                                
				double dt = 0.0;
				_gx_encode_time(&dt, (int) tm.hour, (int) tm.minute, (int) tm.second);
				
				long gdate = _gx_encode_date(0, (int) tm.year, (int) tm.month, (int) tm.day);
				if (gdate != 30105)
					dt += gdate;
				
				status = SetNumberRowCol(nRow, nCol, (double) dt);

				if (status && !GX_IS_DATE_FORMAT(GetFormatRowCol(nRow, nCol)))
				{
					int idate = (int) (double) dt;

					unsigned fmt;

					// only date ?
					if ((double) dt == (double) idate)
						fmt = GX_FMT_DATE;

					// only time  ?
					else if (idate == 0)
						fmt = GX_FMT_TIME;

					// both date and time
					else
						fmt = GX_FMT_DATETIME;

					SetFormatRowCol(nRow, nCol, fmt, 0);
				}
			}
			else

#endif
				status = SetTextRowCol(nRow, nCol, pszInput);
		}
	}

	return status != 0;
}


int CGXFormulaSheet::GetNumberRowCol(ROWCOL nRow, ROWCOL nCol, double& number)
	// formula will be evaluated if needed
	// d will be 0 for text cells 
	// returns errcode (ok, error, constraint, cycle, N/A)
{
	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);
	int c = GetEngineCol(nCol);
	
	gxCell *cp = _gx_find_cell(si, r, c);

	if (cp && cp->cell_type == GX_FORMULA_CELL && !GX_CELL_TEST_FLAG(cp, GX_VISITED))
	{
		int mask = _gx_freeze_list_order(si, GX_ALL_LISTS);
		_gx_back_calc(si, cp);	/* make sure the value is current */
		_gx_unfreeze_list_order(si, mask);
	}

	if (cp && GX_CELL_CONTAINS_NUMBER(cp))
		number = cp->value.number;
	else
		number = 0.0;

	return 0;	// ok, error, constraint, ...
}


int CGXFormulaSheet::GetCellText(gxCell* cp, CString& sText)
{
	int si = m_nSheetContext;

	if (cp == NULL)
	{
		sText.Empty();
		return 0;
	}

	if (cp->cell_type == GX_FORMULA_CELL && !GX_CELL_TEST_FLAG(cp, GX_VISITED))
	{
		int mask = _gx_freeze_list_order(si, GX_ALL_LISTS);
		_gx_back_calc(si, cp);	/* make sure the value is current */
		_gx_unfreeze_list_order(si, mask);
	}

	if (GX_CELL_TEST_FLAG(cp, GX_CYCLE) && _gx_get_iteration_limit(si) == 0)
	{
		sText = _T("Cycle!");
	}
	else
	{
		switch (cp->value_type)
		{
		case GX_VALUE_NONE:
			sText.Empty();
			break;

		case GX_VALUE_NUMERIC:
			sText.Format(_T("%.14g"), cp->value.number); 
			break;

		case GX_VALUE_STRING:
			sText = cp->value.string;
			break;

		case GX_VALUE_SHORT_STRING:
			_gx_xs_short_strcpy(sText.GetBuffer(10), cp->value.short_string, TRUE);
			sText.ReleaseBuffer();
			break;

		case GX_VALUE_NA:
			sText = _T("#N/A"); // NOTE: NA is not supported in OG 6.0. 
			break;

		case GX_VALUE_ERROR:
			sText = _T("Error!");
			break;

		default:
			sText = _T("Value?");
			break;
		}
	}

	return 0;
}

int CGXFormulaSheet::GetTextRowCol(ROWCOL nRow, ROWCOL nCol, CString& sText)
	// formula will be evaluated if needed
	// numeric cells will be converted to string 
	// returns errcode (ok, error, constraint, cycle, N/A)
{
	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);
	int c = GetEngineCol(nCol);
	
	gxCell *cp = _gx_find_cell(si, r, c);

	return GetCellText(cp, sText);
}

int CGXFormulaSheet::GetExpression(gxCell* cp, CString& sText) // , BOOL bMarkText)
{
	int si = m_nSheetContext;

	if (cp == NULL)
	{
		sText.Empty();
		return 0;
	}

	if (cp->cell_type == GX_FORMULA_CELL
		|| cp->cell_type == GX_CONSTANT_FORMULA_CELL)
	{
		_gx_expr_print(si, cp->formula, sText.GetBuffer(GX_MAX_TEXT));
		sText.ReleaseBuffer();

		return 0;
	}
	else
	{
		switch (cp->value_type)
		{
		case GX_VALUE_NONE:
			sText.Empty();
			break;

		case GX_VALUE_NUMERIC:
			sText.Format(_T("%.14g"), cp->value.number); 

			// Date values should be displayed as date
			if (cp->pStyle && cp->pStyle->GetIncludeFormat()
				&& (GX_IS_DATE_FORMAT(cp->pStyle->GetFormat())
					|| GX_IS_TIME_FORMAT(cp->pStyle->GetFormat())))
				sText = GXFormatText(*cp->pStyle, sText, GX_VT_NUMERIC);

			break;

		case GX_VALUE_STRING:
			// Add a ' so that value will be recognized as text when
			// SetExpressionRowCol will be called
			sText = _T('\'');
			sText += cp->value.string;
			break;

		case GX_VALUE_SHORT_STRING:
			// Add a ' so that value will be recognized as text when
			// SetExpressionRowCol will be called
			{
				TCHAR shortstring[10];
				sText = _T('\'');
				_gx_xs_short_strcpy(shortstring, cp->value.short_string, TRUE);
				sText += shortstring;
				break;
			}

		case GX_VALUE_NA:
			sText = _T("#N/A");// NOTE: NA is not supported in OG 6.0.
			break;

		case GX_VALUE_ERROR:
			sText = _T("Error!");
			break;

		default:
			sText = _T("Value?");
			break;
		}
	}

	return 0;
}

int CGXFormulaSheet::GetExpressionRowCol(ROWCOL nRow, ROWCOL nCol, CString& sText)
	// stores formula as string in sText if formula cell
	// otherwise cell value will be stored in sText
	// returns errcode (ok, error, constraint, cycle, N/A)
{
	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);
	int c = GetEngineCol(nCol);
	
	gxCell *cp = _gx_find_cell(si, r, c);

	return GetExpression(cp, sText);
}


// Common settings for Formula Engine:
void CGXFormulaSheet::SetIterationLimit(int nLimit)	// 0 - no iteration
{
	_gx_set_iteration_limit(m_nSheetContext, nLimit);
}

int CGXFormulaSheet::GetIterationLimit() const
{
	return _gx_get_iteration_limit(m_nSheetContext);
}

void CGXFormulaSheet::SetBlanksAreZeros(BOOL bToggle)
{
	_gx_set_blanks_are_zeros(m_nSheetContext, bToggle);
}

BOOL CGXFormulaSheet::GetBlanksAreZeros() const
{
	return _gx_get_blanks_are_zeros(m_nSheetContext);
}

void CGXFormulaSheet::SetRecalcMode(int nMode)	// automatic/manual
{
	_gx_set_recalc_mode(m_nSheetContext, nMode);
}

int CGXFormulaSheet::GetRecalcMode() const
{
	return _gx_get_recalc_mode(m_nSheetContext);
}

void CGXFormulaSheet::SetRecalcMethod(int nMethod) // foreground / as needed
{
	_gx_set_recalc_method(m_nSheetContext, nMethod);
}

int CGXFormulaSheet::GetRecalcMethod() const
{
	return _gx_get_recalc_method(m_nSheetContext);
}

void CGXFormulaSheet::SetConstraintCheck(BOOL bToggle)	
{
	// Add base style for constraint check
	if (Grid() && Grid()->GetParam() && Grid()->GetParam()->GetStylesMap())
		RegisterBaseStyles(Grid()->GetParam()->GetStylesMap());

	_gx_set_constraint_check(m_nSheetContext, bToggle);
}

BOOL CGXFormulaSheet::EvaluateExpression(CString& sResult, LPCTSTR pszFormula)
{
	CGXFormula fm;
	
	ResetError();

	if (!_gx_parse_formula(m_nSheetContext, pszFormula, fm.pfm))
	{
		GetError(sResult);
		return FALSE;
	}

	BOOL b = EvaluateExpression(sResult, fm);

	return b;
}


BOOL CGXFormulaSheet::EvaluateExpression(CString& sResult, CGXFormula& fm)
{
	gxCell cp;
	memset(&cp, 0, sizeof(gxCell));
	cp.formula = fm.pfm;
	_gx_evaluate_cell(m_nSheetContext, &cp);

	GetCellText(&cp, sResult);

	return cp.value_type != GX_VALUE_ERROR;
}

BOOL CGXFormulaSheet::ParseExpression(LPCTSTR pszFormula, CGXFormula& fm)
{
	return _gx_parse_formula(m_nSheetContext, pszFormula, fm.pfm);
}

BOOL CGXFormulaSheet::GetConstraintCheck() const
{
	return _gx_get_constraint_check(m_nSheetContext);
}

// Base Styles

void CGXFormulaSheet::RegisterBaseStyles(CGXStylesMap* pStyMap)
{
	m_bsConstraint = pStyMap->RegisterStyle(GX_IDS_STYLE_CONSTRAINTVIOL, CGXStyle().SetInterior(RGB(255,0,0)), TRUE);
}

// CGXStyle* colstyles, rowstyles, tablestyle will 
// be inherited from CGXData

// overrides
void CGXFormulaSheet::DeleteContents()
{
	CGXData::DeleteContents();

	ResetSheet();
}

void CGXFormulaSheet::ResetSheet()
{
	int si = m_nSheetContext;
	gxSheetContext* pContext = _gx_get_context_ptr(si);

	// reinit data
	_gx_clear_recalc_rangelist(si);
	delete[] pContext->row_cell_count;
	delete[] pContext->col_cell_count;
	_gx_free_cell_block_list(&pContext->constant_list);
	_gx_free_cell_block_list(&pContext->recalc_list);
	_gx_free_cell_block_list(&pContext->empty_list);
	_gx_free_range_name_list(si);

	pContext->row_cell_count = NULL;
	pContext->col_cell_count = NULL;
	pContext->highwater_rowcount = 0;
	pContext->highwater_colcount = 0;
}

void CGXFormulaSheet::Serialize(CArchive& ar)
{
	static const WORD wVersion = 1;
	WORD wActualVersion = wVersion;

	ASSERT_VALID( this );

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
			TRACE0( "Incompatible format while reading CGXFormulaSheet" );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXFormulaSheet object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	CGXData::Serialize(ar);

	int si = m_nSheetContext;

	gxSheetContext* pContext = _gx_get_context_ptr(si);

	int mask = _gx_freeze_list_order(si, GX_ALL_LISTS);

	if (!ar.IsStoring())
	{
		// reinit data
		ResetSheet();

		// General settings
		WORD w;
		ar >> w;
		SetIterationLimit((int) w);

		ar >> w;
		SetBlanksAreZeros((BOOL) w);

		ar >> w;
		SetRecalcMode((int) w);	

		ar >> w;
		SetRecalcMethod((int) w);

		ar >> w;
		//SetConstraintCheck((BOOL) w);	
		_gx_set_constraint_check(m_nSheetContext, w);

		// Named ranges
		CStringArray namedRanges;
		namedRanges.Serialize(ar);
		SetRangeNameArray(namedRanges);

		// Load Cells
		gxCell* cp;
		CString s, sExpr;
		BYTE b;
		DWORD dw;

		ar >> b;
		while (b)
		{
			ar >> b;
			gxCellBlockList* gxlist;
			switch (b)
			{
			case GX_EMPTY_CELL:
				gxlist = &pContext->empty_list;
				break;
			case GX_FORMULA_CELL:
				gxlist = &pContext->recalc_list;
				break;
			default:
				gxlist = &pContext->constant_list;
				break;
			}
			
			cp = _gx_new_cell(gxlist);

			cp->cell_type = (unsigned) b;
			ar >> b; cp->value_type = (unsigned) b;
			ar >> b; cp->flags = (unsigned) b;
			ar >> dw; cp->row = (gxRowCol) dw;
			ar >> dw; cp->col = (gxRowCol) dw;
			ar >> cp->pStyle;

			

			BOOL bParseError = FALSE;
			if (cp->cell_type == GX_FORMULA_CELL
				|| cp->cell_type == GX_CONSTANT_FORMULA_CELL)
			{
				ar >> sExpr;
				TRACE1("The formula %s\n", sExpr);
				if (sExpr.GetLength() >= GX_MAX_TEXT)
					sExpr = sExpr.Left(GX_MAX_TEXT-1);
				cp->formula = (gxFormula *) GX_XSmalloc (sizeof(gxFormula));
				bParseError = _gx_parse_formula(si, sExpr, cp->formula) == 0;
				// ASSERT(_ttol(((LPCTSTR) sExpr)+1) == 0);
			}

			if (cp->cell_type != GX_EMPTY_CELL)
			{
				switch (cp->value_type)
				{
				case GX_VALUE_NUMERIC:
					{
						double d;
						ar >> d;
						if (!bParseError)
							cp->value.number = d;
					}
					break;

				case GX_VALUE_STRING:
				case GX_VALUE_SHORT_STRING:
					{
						gxCellValue cv;
						cv.type = GX_VALUE_STRING;
						ar >> s;
						if (s.GetLength() >= GX_MAX_TEXT)
							s = s.Left(GX_MAX_TEXT-1);
						if (!bParseError)
						{
							cv.value.string = (LPTSTR) (LPCTSTR) s;
							_gx_set_cell_value(cp, &cv);
						}
					}
					break;

				case GX_VALUE_ERROR:
					{
						WORD w;
						ar >> w;
						if (!bParseError)
							cp->value.err.code = w;
					}
					break;
				}
			}

			if (bParseError)
			{
				// error in formula - convert it to a label cell
				// with formula as text value
				gxRowCol r = cp->row;
				gxRowCol c = cp->col;
				CGXStyle* pStyle = cp->pStyle;
				cp->value_type = GX_VALUE_NUMERIC;
				_gx_free_cell(cp);

				cp = _gx_new_cell(&pContext->constant_list);

				cp->cell_type = GX_LABEL_CELL;
				cp->value_type = GX_VALUE_NUMERIC;
				cp->row = r;
				cp->col = c;
				cp->pStyle = pStyle;

				gxCellValue cv;
				cv.type = GX_VALUE_STRING;
				cv.value.string = (LPTSTR) (LPCTSTR) sExpr;
				_gx_set_cell_value(cp, &cv);
			}

			gxCell* dp = _gx_find_cell(si, cp->row, cp->col);
			if (dp)
			{
				if (cp->cell_type != GX_EMPTY_CELL)
				{
					_gx_destroy_cell(si, dp);
					_gx_insert_cell(si, cp);
				}
			}
			else
				_gx_insert_cell(si, cp);

			// b will be 0 if no more cells
			ar >> b;
		}
	}
	else
	{
		// General settings
		WORD w;

		w = (WORD) GetIterationLimit();
		ar << w;
		
		w = (WORD) GetBlanksAreZeros();
		ar << w;

		w = (WORD) GetRecalcMode();	
		ar << w;

		w = (WORD) GetRecalcMethod();
		ar << w;

		w = (WORD) GetConstraintCheck();	
		ar << w;

		// Named ranges
		CStringArray namedRanges;
		GetRangeNameArray(namedRanges);
		namedRanges.Serialize(ar);

		gxScanBuf scan;
		gxCell* cp;
		CString s;

		// Store Cells
		for (int i = 0; i <= 2; i++)
		{
			switch (i)
			{
			case 0:
				_gx_init_cell_list_scan(&pContext->constant_list, &scan);
				break;
			case 1:
				_gx_init_cell_list_scan(&pContext->recalc_list, &scan);
				break;
			case 2:
				_gx_init_cell_list_scan(&pContext->empty_list, &scan);
				break;
			}

			while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
			{
				if (!cp->inserted)
					continue;

				// Fix for serialization problem:
				// Problem: In some cases, without the if stmt. below, when a GX_FORMULA_CELL was never visited and it's 
				// value type is say X then the value type is stored as X(Reference 1). But, subsequently
				// the cell would get _gx_back_calced(Reference 2) which might cause the value type to be set
				// as GX_VALUE_ERROR and later store (Reference 3) the error code instead of a value of type X.
				// Fix: Including the line below prior to <Reference 1> automatically fixes the problem.
				if (cp->cell_type == GX_FORMULA_CELL && !GX_CELL_TEST_FLAG(cp, GX_VISITED))
						_gx_back_calc(si, cp);

				ar << (BYTE) 1;
				ar << (BYTE) cp->cell_type;
				ar << (BYTE) cp->value_type;	// Reference 1
				ar << (BYTE) cp->flags;
				ar << (DWORD) cp->row;
				ar << (DWORD) cp->col;
				ar << cp->pStyle;

				switch (cp->cell_type)
				{
				case GX_EMPTY_CELL:
					continue;
				case GX_FORMULA_CELL:
					if (!GX_CELL_TEST_FLAG(cp, GX_VISITED))
						_gx_back_calc(si, cp);
				case GX_CONSTANT_FORMULA_CELL:
					if (cp->formula)
						GetExpression(cp, s);
					else
						s.Empty();
					ar << s;
					// TRACE(_T("%s\n"), s);
					break;
				}

				switch (cp->value_type)
				{
				case GX_VALUE_NUMERIC:
					ar << cp->value.number;
					break;
				case GX_VALUE_STRING:
					s = cp->value.string;
					ar << s;
					break;
				case GX_VALUE_SHORT_STRING:
					_gx_xs_short_strcpy(s.GetBuffer(10), cp->value.short_string, TRUE);	
					s.ReleaseBuffer();
					ar << s;
					break;
				case GX_VALUE_ERROR:
					ar << (WORD) cp->value.err.code;
					break;
				}
			}
		}

		// mark end of cells
		ar << (BYTE) 0;
	}

	_gx_unfreeze_list_order(si, mask);
}

const CGXData& CGXFormulaSheet::operator=(const CGXData& pData)
{
	if (&pData == this)
		return *this;

	ResetSheet();

	const CGXFormulaSheet& p = (CGXFormulaSheet&) pData;

	if (!p.IsKindOf(RUNTIME_CLASS(CGXFormulaSheet)))
	{
		// p is a CGXData object. Convert all CGXData cell entries
		// to cells in formula engine.

		CGXData::operator=(p);

		int si = m_nSheetContext;

		BOOL bHeader = FALSE;
		int nMaxRow = 1;

		for (int nRow = 1; nRow < m_apapCellStyle.GetSize(); nRow++)
		{
			CGXStylePtrArray* apCols = m_apapCellStyle[nRow];

			bHeader = FALSE;

			// Nothing to do if row is empty
			if (apCols != NULL)
			{

				// Build a new column array
				for (int n = 0; n < apCols->GetSize(); n++)
				{
					CGXStyle* pStyle = apCols->GetAt(n);

					if (pStyle == NULL)
						continue;

					if (n == 0)
					{
						bHeader = TRUE;
						nMaxRow = nRow;
						continue;
					}

					apCols->SetAt(n, NULL);

					int r = GetEngineRow((ROWCOL) nRow);
					int c = GetEngineCol((ROWCOL) n);
		
					gxCell *cp = _gx_find_cell(si, r, c);

					BOOL bFindAgain = FALSE;
					BOOL bDone = FALSE;
					BOOL bValueOnly = (pStyle->GetStyleBits() == 0x400 || pStyle->GetStyleBits() == 0);

					if (pStyle->GetIncludeValue())
					{
						LPCTSTR pszValue = _T("");
						
						if (pStyle->GetIncludeValue())
							pszValue = pStyle->GetValueRef();

						// Numeric values will always end up beeing numeric
						// even if nType == GX_VALUE_EXPRESSION
						if (*pszValue)
							bDone = bFindAgain = SetExpressionRowCol(nRow, n, pszValue);
						else 
							bDone = bFindAgain = SetTextRowCol(nRow, n, pszValue);
					}

					if (bValueOnly)
					{
						delete pStyle;
						continue;
					}

					// make sure we have an appended style object
					if (bFindAgain || cp == NULL)
						cp = _gx_find_cell(si, r, c);

					if (cp == NULL)
					{
						int status = _gx_cell_put_label(si, r, c, _T(""), NULL);

						if (status)
						{
							// mark cell as empty
							cp = _gx_find_cell(si, r, c);

							gxCellValue cv;
							cv.type = GX_VALUE_NONE;

							_gx_set_cell_value(cp, &cv);
						}
						// something went wrong
						else
							continue;
					}

					assert(cp != NULL);

					// copy style pointer 
					delete cp->pStyle;
					cp->pStyle = pStyle;
				}

				if (bHeader)
					apCols->SetSize(1);
				else
				{
					delete apCols;
					m_apapCellStyle.SetAt(nRow, NULL);
				}
			}
		}

		m_apapCellStyle.SetSize(nMaxRow+1);

		return *this;
	}
	else
	{
		int mask = _gx_freeze_list_order(m_nSheetContext, GX_ALL_LISTS);

		// Duplicate all cells
		gxScanBuf scan;
		gxCell* cp;
		CString s;
		gxRange src;
		src.c0 = GX_MIN_COL;
		src.c1 = GX_MAX_COL;
		src.r0 = GX_MIN_ROW;
		src.r1 = GX_MAX_ROW;

		int si1 = m_nSheetContext;
		int si2 = p.m_nSheetContext;
		gxSheetContext* pContext1 = _gx_get_context_ptr(si1);
		gxSheetContext* pContext2 = _gx_get_context_ptr(si2);

		// Store Cells
		_gx_init_cell_list_scan(&pContext2->empty_list, &scan);
		while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
		{
			gxCell* dp = _gx_copy_cell_to_list(&pContext1->empty_list, cp);
			if (dp->pStyle)
				dp->pStyle = cp->pStyle->Clone();
		}

		_gx_init_cell_list_scan(&pContext2->constant_list, &scan);
		while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
		{
			gxCell* dp = _gx_copy_cell_to_list(&pContext1->constant_list, cp);
			if (dp->pStyle)
				dp->pStyle = cp->pStyle->Clone();
		}

		_gx_init_cell_list_scan(&pContext2->recalc_list, &scan);
		while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
		{
			gxCell* dp = _gx_copy_cell_to_list(&pContext1->recalc_list, cp);
			if (dp->pStyle)
				dp->pStyle = cp->pStyle->Clone();
		}

		// attributes like _gx_recalc option, constraint check etc.)
		SetIterationLimit(p.GetIterationLimit());
		SetBlanksAreZeros(p.GetBlanksAreZeros());
		SetRecalcMode(p.GetRecalcMode());	
		SetRecalcMethod(p.GetRecalcMethod());
		SetConstraintCheck(p.GetConstraintCheck());	

		CStringArray namedRanges;
		p.GetRangeNameArray(namedRanges);
		SetRangeNameArray(namedRanges);

		_gx_unfreeze_list_order(m_nSheetContext, mask);

		return CGXData::operator=(p);
	}
}

// Inserting Colums or Rows
BOOL CGXFormulaSheet::StoreInsertRows(ROWCOL nRow, ROWCOL nCount)
{
	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);

	_gx_insert_rows(si, r, (int) nCount);

	// check tool cells
	CheckAdvancedUndo(FALSE, TRUE);

	return CGXData::StoreInsertRows(nRow, nCount);
}

BOOL CGXFormulaSheet::StoreInsertCols(ROWCOL nCol, ROWCOL nCount)
{
	int si = m_nSheetContext;
	int c = GetEngineCol(nCol);

	_gx_insert_columns(si, c, (int) nCount);

	// check tool cells
	CheckAdvancedUndo(FALSE, TRUE);

	return CGXData::StoreInsertCols(nCol, nCount);
}

// Removing Colums or Rows
BOOL CGXFormulaSheet::StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow)
{
	int si = m_nSheetContext;
	int r = GetEngineRow(nFromRow);
	int n = (int) (nToRow-nFromRow+1);

	_gx_delete_rows(si, r, n);

	// Check for cell references
	CheckAdvancedUndo(FALSE, FALSE);

	// check tool cells
	CheckAdvancedUndo(FALSE, TRUE);

	return CGXData::StoreRemoveRows(nFromRow, nToRow);
}

BOOL CGXFormulaSheet::StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol)
{
	int si = m_nSheetContext;
	int c = GetEngineCol(nFromCol);
	int n = (int) (nToCol-nFromCol+1);

	_gx_delete_cols(si, c, n);

	// Check for cell references
	CheckAdvancedUndo(FALSE, FALSE);

	// check tool cells
	CheckAdvancedUndo(FALSE, TRUE);

	return CGXData::StoreRemoveCols(nFromCol, nToCol);
}

// Moving Colums or Rows
BOOL CGXFormulaSheet::StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow)
{
	int si = m_nSheetContext;
	int rfrom = GetEngineRow(nFromRow);
	int rto = GetEngineRow(nToRow);
	int rdest = GetEngineRow(nDestRow);

	_gx_reorder_range(si, TRUE, rfrom, rto, rdest);

	// check cell references
	CheckAdvancedUndo(TRUE, FALSE);

	// check tool cells
	CheckAdvancedUndo(FALSE, TRUE);

	return CGXData::StoreMoveRows(nFromRow, nToRow, nDestRow);
}

BOOL CGXFormulaSheet::StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol)
{
	int si = m_nSheetContext;
	int cfrom = GetEngineCol(nFromCol);
	int cto = GetEngineCol(nToCol);
	int cdest = GetEngineCol(nDestCol);

	_gx_reorder_range(si, FALSE, cfrom, cto, cdest);

	// check cell references
	CheckAdvancedUndo(TRUE, FALSE);

	// check tool cells
	CheckAdvancedUndo(FALSE, TRUE);

	return CGXData::StoreMoveCols(nFromCol, nToCol, nDestCol);
}

// copy ranges in one step - CGXGridCore creates undo info

BOOL CGXFormulaSheet::StoreCopyCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol)
{
	gxRange src;
	src.c0 = GetEngineCol(rg.left);
	src.c1 = GetEngineCol(rg.right);
	src.r0 = GetEngineRow(rg.top);
	src.r1 = GetEngineRow(rg.bottom);

	int si = m_nSheetContext;
	int r = GetEngineRow(max(1, nRow));
	int c = GetEngineCol(max(1, nCol));

	// TRACE(_T("StoreCopyCells()\n"));

	_gx_copy_range(si, src, r, c, 1);
	
	gxRange dst;
	dst = _gx_figure_move_dest(&src, r, c);
	_gx_add_recalc_range(si, &dst);

	// check tool cells
	CheckAdvancedUndo(TRUE, TRUE);

	return TRUE;
}

BOOL CGXFormulaSheet::StoreMoveCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject*& pUndoInfo, BOOL bCreateUndoInfo, int ctCmd)
{
	gxRange src;
	src.c0 = GetEngineCol(rg.left);
	src.c1 = GetEngineCol(rg.right);
	src.r0 = GetEngineRow(rg.top);
	src.r1 = GetEngineRow(rg.bottom);

	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);
	int c = GetEngineCol(nCol);

	// TRACE(_T("StoreMoveCells()\n"));

	gxRange dst;
	dst = _gx_figure_move_dest(&src, r, c);

	gxSheetContext* pContext = _gx_get_context_ptr(si);
	pContext->do_preserve = bCreateUndoInfo;
	pContext->preserve_list = NULL;

	CGXUndoEngineCellsInfo* pInfo = NULL;
	if (pUndoInfo && pUndoInfo->IsKindOf(RUNTIME_CLASS(CGXUndoEngineCellsInfo)))
		pInfo = (CGXUndoEngineCellsInfo*) pUndoInfo;

	if (pInfo)
	{
		_gx_restore_cells(si, pInfo->m_pToolCells);
		pInfo->m_pToolCells = NULL;
	}

	_gx_move_range(si, src, r, c, 0);

	if (pInfo)
	{
		_gx_restore_cells(si, pInfo->m_pCells);
		pInfo->m_pCells = NULL;
	}

	if (bCreateUndoInfo)
	{
		if (pUndoInfo == NULL)
			pUndoInfo = pInfo = new CGXUndoEngineCellsInfo;

		pInfo->m_pCells = pContext->preserve_list;
		pContext->preserve_list = NULL;
	}

	pContext->do_preserve = bCreateUndoInfo && (ctCmd == gxDo || ctCmd == gxRedo);

	// BOOL bOld = SetPreserveCells(m_bAdvancedUndoInfo);
	// TRACE(_T("MoveCells - Recalc\n"));

	_gx_add_recalc_range(si, &dst);
	int nOld = _gx_get_recalc_method(si);
	_gx_set_recalc_method(si, GX_RECALC_FOREGROUND);
	_gx_recalc(si);
	_gx_set_recalc_method(si, nOld);

	if (bCreateUndoInfo)
	{
		pInfo->m_pToolCells = pContext->preserve_list;
		pContext->preserve_list = NULL;
	}

	pContext->do_preserve = FALSE;

	// TRACE(_T("MoveCells - Return\n"));
	return TRUE;
}

// gxCell data
BOOL CGXFormulaSheet::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType)
{
	if (nType >= 0 && nRow > 0 && nCol > 0)
	{
		int si = m_nSheetContext;
		int r = GetEngineRow(nRow);
		int c = GetEngineCol(nCol);
		
		gxCell *cp = _gx_find_cell(si, r, c);

		BOOL bFindAgain = FALSE;
		BOOL bDone = FALSE;
		BOOL bValueOnly = pStyle && (pStyle->GetStyleBits() == 0x400 || pStyle->GetStyleBits() == 0);

		switch (mt)
		{
		case gxRemove:
			if (cp)
				_gx_destroy_cell(si, cp);
			return TRUE;

		case gxExclude:
			if (cp == NULL)
				return TRUE;

			else if (pStyle->GetIncludeValue() && cp->pStyle == NULL)
			{
				_gx_destroy_cell(si, cp);
				return TRUE;
			}
			
			if (pStyle->GetIncludeValue())
			{
				gxCellValue cv;
				cv.type = GX_VALUE_NONE;

				_gx_set_cell_value(cp, &cv);
			}

			bDone = TRUE;

			break;

		case gxCopy:
			if (pStyle->GetStyleBits() == 0)
			{
				if (cp) 
					_gx_destroy_cell(si, cp);
				return TRUE;
			}
			else if (bValueOnly && cp && cp->pStyle)
			{
				delete cp->pStyle;
				cp->pStyle = NULL;
				bDone = TRUE;
			}

		default:
			if (pStyle->GetIncludeValue())
			{
				LPCTSTR pszValue = _T("");
				
				if (pStyle->GetIncludeValue())
					pszValue = pStyle->GetValueRef();

				// Numeric values will always end up beeing numeric
				// even if nType == GX_VALUE_EXPRESSION
				if (pStyle->GetValueType() == GX_VT_NUMERIC)
					bDone = bFindAgain = SetNumberRowCol(nRow, nCol, _gxttof(pszValue));
				else 
				{
					if (*pszValue && nType == GX_VALUE_EXPRESSION)
						bDone = bFindAgain = SetExpressionRowCol(nRow, nCol, pszValue);
					else 
						bDone = bFindAgain = SetTextRowCol(nRow, nCol, pszValue);
				}
			}
		}

		if (bValueOnly)
			return bDone;

		// make sure we have an appended style object
		if (bFindAgain || cp == NULL)
			cp = _gx_find_cell(si, r, c);

		if (cp == NULL)
		{
			int status = _gx_cell_put_label(si, r, c, _T(""), NULL);

			if (status)
			{
				// mark cell as empty
				cp = _gx_find_cell(si, r, c);

				gxCellValue cv;
				cv.type = GX_VALUE_NONE;

				_gx_set_cell_value(cp, &cv);
			}
			// something went wrong
			else
				return FALSE;
		}

		assert(cp != NULL);

		// if no style opject is appended to cell and the style is to be reset then we are done, too
		if (cp->pStyle == NULL)
			// if only value is to be modifed then we are done
			cp->pStyle = pStyle->Clone();
		else
			cp->pStyle->ChangeStyle(*pStyle, mt);

		return TRUE;
	}
	else

		return CGXData::StoreStyleRowCol(nRow, nCol, pStyle, mt, nType);
}

BOOL CGXFormulaSheet::GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType)
{
	if (nType >= 0 && nRow > 0 && nCol > 0)
	{
		int si = m_nSheetContext;
		int r = GetEngineRow(nRow);
		int c = GetEngineCol(nCol);
		
		gxCell *cp = _gx_find_cell(si, r, c);

		if (cp == NULL)
			return FALSE;

		if (cp->pStyle)
			style.ChangeStyle(*cp->pStyle, mt);

		CString sText;
		if (nType == GX_VALUE_EXPRESSION)
		{
			GetExpression(cp, sText);

			style.SetValue(sText);
			style.SetValueType(GX_VT_EXPRESSION);
		}
		else
		{
			GetCellText(cp, sText);		// formula will be reevaluated if needed
			style.SetValue(sText);

			switch (cp->value_type)
			{
			case GX_VALUE_NUMERIC:
				style.SetValueType(GX_VT_NUMERIC);
				break;

			case GX_VALUE_NONE:
			case GX_VALUE_STRING:
			case GX_VALUE_SHORT_STRING:
			case GX_VALUE_NA:
				style.SetValueType(GX_VT_STRING);
				break;

			case GX_VALUE_ERROR:
			default:
				style.SetValueType(GX_VT_ERROR);
				break;
			}
		}

		if (GetConstraintCheck() && GX_CELL_TEST_FLAG(cp, GX_CONSTRAINT_VIOL))
		{
			CGXGridCore* pGrid = Grid();
			CGXStylesMap* pStyMap = NULL;
			
			if (pGrid && pGrid->GetParam())
				pStyMap = pGrid->GetParam()->GetStylesMap();

			if (pStyMap)
			{
				if (m_bsConstraint == 0)
					m_bsConstraint = pStyMap->GetBaseStyleId(GX_IDS_STYLE_CONSTRAINTVIOL);

				if (m_bsConstraint == 0)
					RegisterBaseStyles(pStyMap);

				if (m_bsConstraint != 0)
				{
					CGXStyle* pConstraintStyle;
					if (pStyMap->LookupStyle(m_bsConstraint, pConstraintStyle))
						style.ChangeStyle(*pConstraintStyle, gxOverride);

					GX_CELL_SET_FLAG(cp, GX_UPDATED);  // force redrawing this cell
				}
			}
		}

		return TRUE;
	}
	else
		return CGXData::GetStyleRowCol(nRow, nCol, style, mt, nType);
}

static void __cdecl _gx_insert_cells(int si, gxCell* cp)
{
	gxCell* next_cell;

	int mask = _gx_freeze_list_order(si, GX_ALL_LISTS);

	while (cp != NULL)
	{
		next_cell = cp->next;
		// _gx_destroy_cell(si, _gx_find_cell(si, cp->row, cp->col));
		_gx_insert_cell(si, cp);
		// TRACE(_T("_gx_insert_cell(%d,%d)\n"), cp->row, cp->col);
		// GX_CELL_SET_FLAG(cp, GX_UPDATED);
		cp = next_cell;
	}

	_gx_unfreeze_list_order(si, mask);
}


// Sorting (rearranging) rows and columns
BOOL CGXFormulaSheet::StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& anRowIndex)
{
	// anRowIndex contains a reference from the new row id to the previous row id.
	// We have to rearrange anRowIndex so that we have a reference from the previous
	// row id to the new row id. Then we can loop through all cells and change cp->row.

	CRowColArray anOldRowIndex;
	anOldRowIndex.SetSize(sortRange.GetHeight());

	for (int n = 0; n < anRowIndex.GetSize(); n++)
		anOldRowIndex[anRowIndex[n]] = n;

	// NOTE: cp->row = anOldRowIndex[cp->row-sortRange.top]+sortRange.top;

	gxCell *cp;
	int si = m_nSheetContext;
	gxSheetContext *context = _gx_get_context_ptr(si);
	gxScanBuf scan;
	gxCell* constant_list = NULL;
	gxCell* recalc_list = NULL;

	unsigned nRow1 = GetEngineRow(sortRange.top);
	unsigned nRow2 = GetEngineRow(sortRange.bottom);

	_gx_init_cell_list_scan(&context->constant_list, &scan);
	while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
	{
		if (!cp->inserted)
			continue;

		if (cp->row >= nRow1 && cp->row <= nRow2
			&& (sortRange.IsRows() 
				|| GetGridCol(cp->col) >= sortRange.left 
					&& GetGridCol(cp->col) <= sortRange.right))
		{
			_gx_remove_cell(si, cp);
			cp->row = anOldRowIndex[cp->row-nRow1]+nRow1;
			cp->next = constant_list;
			constant_list = cp;
		}
	}

	/* We must scan the entire recalc_list and update all formulas which
	 * reference any cell being moved to point to the cell's new location. */

	int update = 0;
	gxExprNode *ep;
	_gx_init_cell_list_scan(&context->recalc_list, &scan);
	while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
	{
		if (!cp->inserted)
			continue;

		update = 0;
		// TCHAR buf[512];
		// _gx_expr_print(si, cp->formula, buf);
		// TRACE(_T("%d,%d: %s"), cp->row, cp->col, buf);

		if (cp->row >= nRow1 && cp->row <= nRow2
			&& (sortRange.IsRows() 
				|| GetGridCol(cp->col) >= sortRange.left 
					&& GetGridCol(cp->col) <= sortRange.right))
		{
			_gx_remove_cell(si, cp);
			cp->row = anOldRowIndex[cp->row-nRow1]+nRow1;
			cp->next = recalc_list;
			recalc_list = cp;
		}

		for (int i = 0; i < cp->formula->expr_size; i++)
		{
			ep = cp->formula->expression + i;
			if ((ep->node_type == GX_CELL_NODE) || (ep->node_type == GX_RANGE_NODE))
			{
				if (ep->value.range.r0 >= nRow1 && ep->value.range.r0 <= nRow2
					&& ep->value.range.r1 == ep->value.range.r0
					&& (sortRange.IsRows() 
						|| GetGridCol(ep->value.range.c0) >= sortRange.left 
							&& GetGridCol(ep->value.range.c1) <= sortRange.right))
				{
					ep->value.range.r0 = ep->value.range.r1
						= anOldRowIndex[ep->value.range.r0-nRow1]+nRow1;

					update = 1;
				}
			}
		}

		if (update)
			GX_CELL_SET_FLAG(cp, GX_NEEDS_RECALC);  // so we know it is up
	}

	_gx_insert_cells(si, constant_list);
	_gx_insert_cells(si, recalc_list);

	return CGXData::StoreMoveDataRows(sortRange, anRowIndex);
}

BOOL CGXFormulaSheet::StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& anColIndex)
{
	// anRowIndex contains a reference from the new row id to the previous row id.
	// We have to rearrange anRowIndex so that we have a reference from the previous
	// row id to the new row id. Then we can loop through all cells and change cp->row.

	CRowColArray anOldColIndex;
	anOldColIndex.SetSize(sortRange.GetWidth());

	for (int n = 0; n < anColIndex.GetSize(); n++)
		anOldColIndex[anColIndex[n]] = n;

	// NOTE: cp->col = anOldColIndex[cp->col-sortRange.left]+sortRange.left;

	gxCell *cp;
	int si = m_nSheetContext;
	gxSheetContext *context = _gx_get_context_ptr(si);
	gxScanBuf scan;
	gxCell* constant_list = NULL;
	gxCell* recalc_list = NULL;

	unsigned nCol1 = GetEngineCol(sortRange.left);
	unsigned nCol2 = GetEngineCol(sortRange.right);

	_gx_init_cell_list_scan(&context->constant_list, &scan);
	while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
	{
		if (!cp->inserted)
			continue;

		if (cp->col >= nCol1 && cp->col <= nCol2
			&& (sortRange.IsCols() 
				|| GetGridRow(cp->row) >= sortRange.top  
					&& GetGridRow(cp->row) <= sortRange.bottom))
		{
			_gx_remove_cell(si, cp);
			cp->col = anOldColIndex[cp->col-nCol1]+nCol1;
			cp->next = constant_list;
			constant_list = cp;
		}
	}

	/* We must scan the entire recalc_list and update all formulas which
	 * reference any cell being moved to point to the cell's new location. */

	int update = 0;
	gxExprNode *ep;
	_gx_init_cell_list_scan(&context->recalc_list, &scan);
	while ((cp = _gx_do_cell_list_scan(&scan)) != NULL)
	{
		if (!cp->inserted)
			continue;

		update = 0;
		// TCHAR buf[512];
		// _gx_expr_print(si, cp->formula, buf);
		// TRACE(_T("%d,%d: %s"), cp->row, cp->col, buf);

		if (cp->col >= nCol1 && cp->col <= nCol2
			&& (sortRange.IsCols() 
				|| GetGridRow(cp->row) >= sortRange.top 
					&& GetGridRow(cp->row) <= sortRange.bottom))
		{
			_gx_remove_cell(si, cp);
			cp->col = anOldColIndex[cp->col-nCol1]+nCol1;
			cp->next = recalc_list;
			recalc_list = cp;
		}

		for (int i = 0; i < cp->formula->expr_size; i++)
		{
			ep = cp->formula->expression + i;
			if ((ep->node_type == GX_CELL_NODE) || (ep->node_type == GX_RANGE_NODE))
			{
				if (ep->value.range.c0 >= nCol1 && ep->value.range.c0 <= nCol2
					&& ep->value.range.c1 == ep->value.range.c0
					&& (sortRange.IsCols() 
						|| GetGridRow(ep->value.range.r0) >= sortRange.top 
							&& GetGridRow(ep->value.range.r1) <= sortRange.bottom))
				{
					ep->value.range.c0 = ep->value.range.c1
						= anOldColIndex[ep->value.range.c0-nCol1]+nCol1;

					update = 1;
				}
			}
		}

		if (update)
			GX_CELL_SET_FLAG(cp, GX_NEEDS_RECALC);  // so we know it is up
	}

	_gx_insert_cells(si, constant_list);
	_gx_insert_cells(si, recalc_list);

	return CGXData::StoreMoveDataCols(sortRange, anColIndex);
}

// Update
BOOL CGXFormulaSheet::GetUpdateFlag(ROWCOL nRow, ROWCOL nCol)  
{
	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);
	int c = GetEngineCol(nCol);
	
	if (!GX_VALID_ROW(r) || !GX_VALID_COL(c))
		return FALSE;

	gxCell *cp = _gx_find_cell(si, r, c);

	// Is this cell marked as updated?
	return (cp && cp->cell_type == GX_FORMULA_CELL 
		&& (!GX_CELL_TEST_FLAG(cp, GX_VISITED) || GX_CELL_TEST_FLAG(cp, GX_UPDATED)))
		|| (cp && cp->cell_type != GX_FORMULA_CELL && GX_CELL_TEST_FLAG(cp, GX_UPDATED))
		;
}

void CGXFormulaSheet::SetUpdateFlag(ROWCOL nRow, ROWCOL nCol, BOOL bToggle)  
	// set update flag (TRUE if cell shall be updated next time CGXGridCore::RefreshView is called)
{
	int si = m_nSheetContext;
	int r = GetEngineRow(nRow);
	int c = GetEngineCol(nCol);

	if (!GX_VALID_ROW(r) || !GX_VALID_COL(c))
		return;
	
	gxCell *cp = _gx_find_cell(si, r, c);

	if (cp)
	{
		//TRACE("SetUpdate %d/%d = %d\n", nRow, nCol, bToggle);
		if (bToggle)
			GX_CELL_SET_FLAG(cp, GX_UPDATED);
		else
			GX_CELL_CLEAR_FLAG(cp, GX_UPDATED);
	}
}

void CGXFormulaSheet::AddRecalcRange(const CGXRange& range)
{
	int si = m_nSheetContext;

	CGXRange r = range;
	r.ExpandRange(1, 1, GetRowCount(), GetColCount());

	gxRange rg;
	rg.r0 = GetEngineRow(max(1, r.top));
	rg.r1 = GetEngineRow(max(1, r.bottom));
	rg.c0 = GetEngineCol(max(1, r.left));
	rg.c1 = GetEngineCol(max(1, r.right));
	_gx_add_recalc_range(si, &rg);

	// _gx_reset_first_error(si);
}

void CGXFormulaSheet::Recalc(BOOL bForceRecalc)
{
	int mask = _gx_freeze_list_order(m_nSheetContext, GX_ALL_LISTS);

	if (bForceRecalc)
		_gx_force_recalc(m_nSheetContext);
	else
		_gx_recalc(m_nSheetContext);

	_gx_unfreeze_list_order(m_nSheetContext, mask);
}

void CGXFormulaSheet::ResetError()
{
	_gx_reset_first_error(m_nSheetContext);
}

BOOL CGXFormulaSheet::GetError(CString& strError)
{
	if (!_gx_get_context_ptr(m_nSheetContext)->first_error)
	{
		strError = _gx_get_context_ptr(m_nSheetContext)->szErrorText;
		return TRUE;
	}

	return FALSE;
}

BOOL CGXFormulaSheet::SetRangeName(LPCTSTR name, const CGXRange& rg, CObject* pUndoInfo)
{
	int si = m_nSheetContext;
	gxRange range;
	memset(&range, 0, sizeof(gxRange));
	range.r0 = GetEngineRow(rg.top);
	range.r1 = GetEngineRow(rg.bottom);
	range.c0 = GetEngineCol(rg.left);
	range.c1 = GetEngineCol(rg.right);
    if (rg.GetWidth() == 1 && rg.GetHeight() == 1)
		range.cell_only = 1;
	CGXUndoEngineCellsInfo* pInfo = NULL;
	if (pUndoInfo && pUndoInfo->IsKindOf(RUNTIME_CLASS(CGXUndoEngineCellsInfo)))
		pInfo = (CGXUndoEngineCellsInfo*) pUndoInfo;

	if (pInfo && pInfo->m_pDeletedRangeName)
	{
		_gx_range_name_undelete(si, pInfo->m_pDeletedRangeName);
		pInfo->m_pDeletedRangeName = NULL;
	}
	else
	{
		_gx_range_name_set(si, name, &range);
		_gx_force_recalc(si);
	}

	if (pInfo)
	{
		_gx_restore_cells(si, pInfo->m_pCells);
		pInfo->m_pCells = NULL;
	}

	return TRUE;
}

BOOL CGXFormulaSheet::GetRangeName(LPCTSTR name, CGXRange& rg)
{
	int si = m_nSheetContext;
	gxRange range;
	memset(&range, 0, sizeof(gxRange));

	if (_gx_range_name_lookup(si, name, &range))
	{
		rg.SetCells(GetGridRow(range.r0), GetGridCol(range.c0),
			GetGridRow(range.r1), GetGridCol(range.c1));

		return TRUE;
	}

	return FALSE;
}

BOOL CGXFormulaSheet::DeleteRangeName(LPCTSTR name, CObject*& pUndoInfo, BOOL bCreateUndoInfo)
{
	int si = m_nSheetContext;

	gxSheetContext* pContext = _gx_get_context_ptr(si);
	pContext->do_preserve = bCreateUndoInfo;
	pContext->preserve_list = NULL;

	int n = _gx_range_name_delete(si, name);

	pContext->do_preserve = FALSE;

	CGXUndoEngineCellsInfo* pInfo = NULL;
	if (pUndoInfo && pUndoInfo->IsKindOf(RUNTIME_CLASS(CGXUndoEngineCellsInfo)))
		pInfo = (CGXUndoEngineCellsInfo*) pUndoInfo;

	if (bCreateUndoInfo)
	{
		if (pUndoInfo == NULL)
			pUndoInfo = pInfo = new CGXUndoEngineCellsInfo;

		pInfo->m_pCells = pContext->preserve_list;
		pInfo->m_pDeletedRangeName = pContext->deleted_range_name;
		pContext->deleted_range_name = NULL;
		pContext->preserve_list = NULL;
	}

	return n != 0;
}

BOOL CGXFormulaSheet::GetRangeNameArray(CStringArray& strarray) const
{
	int si = m_nSheetContext;
	gxRangeName **rnpp;

	TCHAR s[256];

	strarray.RemoveAll();
	for (rnpp = &_gx_get_context_ptr(si)->range_name_list;
		 (*rnpp) != NULL; rnpp = &((*rnpp)->next))
	{
		wsprintf(s, _T("%s=%s"), (*rnpp)->name, _gx_range_to_text(&(*rnpp)->range));
		strarray.SetAtGrow(strarray.GetSize(), s);
	}

	return TRUE;
}

void CGXFormulaSheet::SetRangeNameArray(CStringArray& namedRanges)
{
	// Add Range Names
	for (int i = 0; i < namedRanges.GetSize(); i++)
	{
		CString s = namedRanges[i];
		int n = s.Find(_T('='));

		CGXRange range;
		if (n > 0)
		{
			CString strName = s.Left(n);
			CString strRange = s.Mid(n+1);
			if (TextToRange(strRange, range))
				SetRangeName(strName, range);
		}
	}
}

BOOL CGXFormulaSheet::TextToRange(LPCTSTR strRange, CGXRange& rg)
{
	gxRange range;

	if (_gx_text_to_range(strRange, &range))
	{
		rg.top = CGXFormulaSheet::GetGridRow(range.r0);
		rg.bottom = CGXFormulaSheet::GetGridRow(range.r1);
		rg.left = CGXFormulaSheet::GetGridCol(range.c0);
		rg.right = CGXFormulaSheet::GetGridCol(range.c1);
		rg.m_bValid = TRUE;
		return TRUE;
	}

	return FALSE;
}

LPCTSTR CGXFormulaSheet::RangeToText(const CGXRange& rg, LPTSTR buffer, int nSize, BOOL bForceRange)
{
	gxRange range;
	memset(&range, 0, sizeof(gxRange));
	range.r0 = GetEngineRow(rg.top);
	range.r1 = GetEngineRow(rg.bottom);
	range.c0 = GetEngineCol(rg.left);
	range.c1 = GetEngineCol(rg.right);

	if (!bForceRange && rg.GetWidth() == 1 && rg.GetHeight() == 1)
		range.cell_only = 1;

	if (nSize == -1)
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(buffer, _gx_range_to_text(&range));
	}else
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_tcsncpy(buffer, _gx_range_to_text(&range), nSize);
		buffer[nSize-1] = 0;
	}

	return buffer;
}

/*void CGXFormulaSheet::SetTreeShifts(int nFirstRow, int nFirstCol)
{
	_gx_set_shifts(nFirstRow, nFirstCol);
}*/
////////////////////////////////////////////////////////////////////////////

CGXFormula::CGXFormula()
{
	pfm = (gxFormula*) malloc(sizeof(gxFormula));
}

CGXFormula::~CGXFormula()
{
	_gx_free_formula(pfm);
}
