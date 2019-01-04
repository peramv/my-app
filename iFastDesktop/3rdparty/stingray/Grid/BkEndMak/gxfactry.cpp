// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Objective Grid
// gxfactry.cpp : Generated Factory class for configuration gxstndrd
//
//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////
//
// Author: Stefan Hoenig
//

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifndef _GXCRTF_H_
#include "grid\gxcrtf.h"
#endif

#ifndef _GXDTCRL_H
#include "grid\gxdtctrl.h"
#endif

#ifndef _GXCURCTL_H_
#include "grid\gxcurctl.h"
#endif

#ifndef _GXTWND_H_
#include "grid\gxtwnd.h"
#endif

#ifndef _GXWND_H_
#include "grid\gxwnd.h"
#endif

#include "grid\gxcvrcel.h"

#include "grid\gxdelayr.h"



#ifndef _GXFCTRY_H_
#include "grid\gxfctry.h"
#endif


#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXFACTRY")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

void AFXAPI GXInit(UINT uiMfcVersion, LPCTSTR pszLang, LPCTSTR pszPath)
{
	GXInit(uiMfcVersion, new CGXControlFactory, pszLang, pszPath);
}

void CGXControlFactory::InitializeGridComponents(CGXGridCore* pGrid)
{
	// InitializeGridComponents is called from CGXGridCore ctor.
	// No window has been created for the grid. m_pGridWnd is NULL.
	// Don't use the pGrid->m_pGridWnd!
	pGrid;

	// General grid components - enable them in the control
	// factory so that all grids in your application behave
	// similar. You can enable/disable the behavior for individual
	// grid with CGXGridParam settings (e.g. EnableMoveRows, 
	// EnableSelection etc).

	pGrid->ImplementFindReplace();			// Find and Replace 
	pGrid->ImplementHideCells();			// Hiding rows and columns
	pGrid->ImplementAutoScroll();			// AutoScrolling, SpeedScrolling
	pGrid->ImplementResizeToFit();			// Resize Cells to fit size
	pGrid->ImplementUpdateHint();			// Update Hint mechanism
	pGrid->ImplementUndoRedo();			// Undo and Redo 
	pGrid->ImplementGridSort();			// Sorting rows or columns
	pGrid->ImplementOldDrawing();			// Old drawing (for backward compatibility)
	pGrid->ImplementCoveredCells();			// Covered Cells
	pGrid->ImplementMergeCells();			// Merge Cells
	pGrid->ImplementFloatCells();			// Floating Cells
	pGrid->ImplementPrinting();			// Printing
	pGrid->ImplementUserSelectRange();		// Select cell ranges with mouse or keyboard
	pGrid->ImplementExcelLikeFrame();		// Excel-like Selection Frame
	pGrid->ImplementUserDragSelectRange();	// Drag selected rows or columns with mouse
	pGrid->ImplementUserResizeCells();		// Resize rows or columns with mouse
	pGrid->ImplementOptimizedUpdate();		// Optimized update for inserting, moving and removing rows and columms
	pGrid->ImplementMarkEditHeader();		// Outline row and column header of current cell
	pGrid->ImplementFreezeMenuHelper();		// FreezeRows, UnfreezeRows (and ..Cols) methods
	pGrid->ImplementDirectCopyMoveCells();	// Direct copying, moving of cells within one grid
	pGrid->ImplementTextDataExchange();	// CSV text file and clipboard data exchange
	pGrid->ImplementStyleDataExchange();	// CGXStyle binary file and clipboard data exchange
	pGrid->ImplementCutPaste();			// Cut, Copy and Paste methods
	pGrid->ImplementClearCells();			// ClearCells method
 pGrid->ImplementExcelLikeFill();		// Excel like auto fill
}

void CGXControlFactory::InitializeApplicationComponents()
{
	// General application wide components - other components
	// rely on some of these application wide components, e.g.
	// 
					
	CGXPrintDevice::ImplementPrintDevice();	// Store printer settings in document
	CGXStyle::ImplementCompareSubset();		// CGXStyle and CGXFont's IsSubSet method
	CGXStyle::ImplementSerialize();			// CGXStyle, CGXFont, CGXBrush and CGXPen's Serialize method
	CGXStyle::ImplementSerializeOG5Compatible();	// OG 5 Backward compatibility for deserializing CGXStyle class
	CGXStyle::ImplementProfile();			// CGXStyle - read and write profile
	CGXGridParam::ImplementSerialize();		// Serialize parameter and related subobjects
	CGXGridParam::ImplementCopyOperator();	// Copy parameter object with all its subobjects
	CGXDrawingAndFormatting::ImplementDrawRotatedText();	// Draw rotated text in cells
	CGXDrawingAndFormatting::ImplementNumberFormatting();	// Number formatting with GXStyle::SetFormat
#if _MFC_VER >= 0x0400
	GXImplementOleDateTime();				// Date & Time parsing with COleDateTime routines
#endif
	GXImplementNoOleDateTime();				// Date & Time parsing without using COleDateTime routines
	CGXData::ImplementSortMoveData();		// Rearrange rows and columns in CGXData (when sorting the grid)
	CGXData::ImplementCopyMoveCells();		// Direct copying and moving cells within grid in CGXData
	CGXLongOperation::ImplementLongOperation(); // Wait cursor, ESC key and status messages
	CGXCoveredCellPool::ImplementCoveredCellPool();	// Covered cells pool data structure
	CGXSpanCellPool::ImplementSpanCellPool();	// Float&Merge cells pool data structure
	CGXDelayedRangePool::ImplementDelayedRangePool();	// Lazy Evaluation data structure for float&merge cells
}

void CGXControlFactory::RegisterAllControls(CGXStylesMap* pStylesMap)
{
	pStylesMap;

	// Basic cell types
	pStylesMap->AddControl(GX_IDS_CTRL_EDIT);
	pStylesMap->AddControl(GX_IDS_CTRL_HEADER);
	pStylesMap->AddControl(GX_IDS_CTRL_TEXTFIT);
	pStylesMap->AddControl(GX_IDS_CTRL_COMBOBOX);
	pStylesMap->AddControl(GX_IDS_CTRL_ONEBASED);
	pStylesMap->AddControl(GX_IDS_CTRL_ZEROBASED);
	pStylesMap->AddControl(GX_IDS_CTRL_ONEBASED_EX);
	pStylesMap->AddControl(GX_IDS_CTRL_ZEROBASED_EX);
	pStylesMap->AddControl(GX_IDS_CTRL_CBS_DROPDOWN);
	pStylesMap->AddControl(GX_IDS_CTRL_CBS_DROPDOWNLIST);
	pStylesMap->AddControl(GX_IDS_CTRL_LISTBOX);
	pStylesMap->AddControl(GX_IDS_CTRL_STATIC);
	pStylesMap->AddControl(GX_IDS_CTRL_PUSHBTN);
	pStylesMap->AddControl(GX_IDS_CTRL_RADIOBTN);
	pStylesMap->AddControl(GX_IDS_CTRL_RADIOBTN3D);
	pStylesMap->AddControl(GX_IDS_CTRL_CHECKBOX);
	pStylesMap->AddControl(GX_IDS_CTRL_CHECKBOX3D);
	pStylesMap->AddControl(GX_IDS_CTRL_CHECKBOXEX);
	pStylesMap->AddControl(GX_IDS_CTRL_CHECKBOX3DEX);
	pStylesMap->AddControl(GX_IDS_CTRL_RADIOBTNEX);
	pStylesMap->AddControl(GX_IDS_CTRL_RADIOBTN3DEX);

	// Advanced
	pStylesMap->AddControl(GX_IDS_CTRL_MASKEDIT);
	pStylesMap->AddControl(GX_IDS_CTRL_PROGRESS);
	pStylesMap->AddControl(GX_IDS_CTRL_PASSWORD);
	pStylesMap->AddControl(GX_IDS_CTRL_CBS_TABBED_DROPDOWN);
	pStylesMap->AddControl(GX_IDS_CTRL_CBS_TABBED_DROPDOWNLIST);
	pStylesMap->AddControl(GX_IDS_CTRL_TABBED_COMBOBOX);
#if _MFC_VER >= 0x0400
	pStylesMap->AddControl(GX_IDS_CTRL_RICHEDIT);
	pStylesMap->AddControl(GX_IDS_CTRL_CHECKLIST_COMBOBOX);
#endif

	// Edit Misc
	pStylesMap->AddControl(GX_IDS_CTRL_SPINEDIT);
	pStylesMap->AddControl(GX_IDS_CTRL_HOTSPOT);
	pStylesMap->AddControl(GX_IDS_CTRL_SCROLLEDIT);
	
	// Date&Time
#if _MFC_VER >= 0x0400
	pStylesMap->AddControl(GX_IDS_CTRL_DATETIME);
	pStylesMap->AddControl(GX_IDS_CTRL_DATETIMENOCAL);
#endif

	// Currency
#if _MFC_VER >= 0x0400
	pStylesMap->AddControl(GX_IDS_CTRL_CURRENCY);
#endif



}

CGXControl* CGXControlFactory::CreateControl(UINT nID, CGXGridCore* pGrid)
{
	CGXControl* pControl = NULL;

	class Friend_CGXDateTimeCtrl : public CGXDateTimeCtrl
	{
		friend class CGXControlFactory;
	};

	BOOL bWin32s = FALSE;
#if _MFC_VER >= 0x0400
	bWin32s = GXGetAppData()->bWin31;
#endif

	// create control on demand
	switch (nID)
	{
	case 0:
	default:
		GX_TRACEONCE(_T("Warning: Couldn't create cell type Id %u %s\n"), nID, (LPCTSTR) CGXResourceString(nID));
		//NULL;
		// Fall through

	case GX_IDS_CTRL_EDIT:
		// default edit box
		pControl = new CGXEditControl(pGrid, GX_IDS_CTRL_EDIT);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_STATIC:
		// use static cell as default if cell type is unknown
		pControl = new CGXStatic(pGrid);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_HEADER:
		// default headers
		pControl = new CGXHeader(pGrid);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_TEXTFIT:
		// Comboboxes
		// combobox only allows text input which fits the choice list
		pControl = new CGXComboBox(pGrid, GX_IDS_CTRL_TEXTFIT, GX_IDS_CTRL_TEXTFIT, GXCOMBO_TEXTFIT);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_COMBOBOX:
		// combobox allows user to input any text
		pControl = new CGXComboBox(pGrid, GX_IDS_CTRL_COMBOBOX, GX_IDS_CTRL_COMBOBOX, GXCOMBO_NOTEXTFIT);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_ONEBASED:
		// combobox uses an integer as cell value
		pControl = new CGXComboBox(pGrid, GX_IDS_CTRL_ONEBASED, GX_IDS_CTRL_ONEBASED, GXCOMBO_ONEBASED);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_ZEROBASED:
		// combobox uses an integer as cell value
		pControl = new CGXComboBox(pGrid, GX_IDS_CTRL_ZEROBASED, GX_IDS_CTRL_ZEROBASED, GXCOMBO_ZEROBASED);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_ONEBASED_EX:
			// use an integer as value and display choice as cell text
		pControl = new CGXComboBox(pGrid, GX_IDS_CTRL_ONEBASED_EX, GX_IDS_CTRL_ONEBASED_EX,
			GXCOMBO_ONEBASED|GXCOMBO_DISPLAYCHOICE);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_ZEROBASED_EX:
			// use an zero-based integer as value and display choice as cell text
		pControl = new CGXComboBox(pGrid, GX_IDS_CTRL_ZEROBASED_EX, GX_IDS_CTRL_ZEROBASED_EX,
			GXCOMBO_ZEROBASED|GXCOMBO_DISPLAYCHOICE);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_CBS_DROPDOWN:
		{
			// CComboBox adapter with CBS_DROPDOWN style
			CGXComboBoxWnd* pWnd = new CGXComboBoxWnd(pGrid);
			// Comment: Added CBS_AUTOHSCROLL flag
			pWnd->Create(WS_VSCROLL | CBS_DROPDOWN | CBS_AUTOHSCROLL, GX_IDS_CTRL_CBS_DROPDOWN);
			pWnd->m_bFillWithChoiceList = TRUE;
			pWnd->m_bWantArrowKeys = FALSE;
			pControl = pWnd;
		}
		break;

	case GX_IDS_CTRL_CBS_DROPDOWNLIST:
		{
			// CComboBox adapter with CBS_DROPDOWNLIST style
			CGXComboBoxWnd* pWnd = new CGXComboBoxWnd(pGrid);
			pWnd->Create(WS_VSCROLL | CBS_DROPDOWNLIST, GX_IDS_CTRL_CBS_DROPDOWNLIST);
			pWnd->m_bFillWithChoiceList = TRUE;
			pWnd->m_bWantArrowKeys = FALSE;
			pControl = pWnd;
		}
		break;

	case GX_IDS_CTRL_SPINEDIT:
		// Textcontrol with Spinbuttons
		pControl = new CGXSpinEdit(pGrid, GX_IDS_CTRL_SPINEDIT);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_HOTSPOT:
		// Textcontrol with hotspot button
		pControl = new CGXHotSpotEdit(pGrid, GX_IDS_CTRL_HOTSPOT);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_SCROLLEDIT:
		// Textcontrol with Vertical scrollbars
		pControl = new CGXVScrollEdit(pGrid, GX_IDS_CTRL_SCROLLEDIT);
		break;

	case GX_IDS_CTRL_LISTBOX:
		// Listbox
		pControl = new CGXListBox(pGrid, GX_IDS_CTRL_LISTBOX);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_PUSHBTN:
		// Push Button
		pControl = new CGXPushbutton(pGrid);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_RADIOBTN:
		// Radio Buttons
		pControl = new CGXRadioButton(pGrid, FALSE /* normal Look */);
		break;

	case GX_IDS_CTRL_RADIOBTN3D:
		pControl = new CGXRadioButton(pGrid, TRUE /* 3d-Look */);
		break;

 case GX_IDS_CTRL_RADIOBTNEX:
		// Radio Buttons
		pControl = new CGXRadioButtonEx(pGrid, FALSE /* normal Look */);
		break;

case GX_IDS_CTRL_RADIOBTN3DEX:
		pControl = new CGXRadioButtonEx(pGrid, TRUE /* 3d-Look */);
		break;

	case GX_IDS_CTRL_CHECKBOX:
		// Check Boxes
		pControl = new CGXCheckBox(pGrid, FALSE /* normal Look */);
		break;

	case GX_IDS_CTRL_CHECKBOX3D:
		pControl = new CGXCheckBox(pGrid, TRUE /* 3d-Look */);
		break;

	case GX_IDS_CTRL_CHECKBOXEX:
		// Check Boxes
		pControl = new CGXCheckBoxEx(pGrid, FALSE /* normal Look */);
		break;

	case GX_IDS_CTRL_CHECKBOX3DEX:
		pControl = new CGXCheckBoxEx(pGrid, TRUE /* 3d-Look */);
		break;

	case GX_IDS_CTRL_MASKEDIT:
		{
			CGXMaskControl* pEditCtrl = new CGXMaskControl(pGrid, GX_IDS_CTRL_MASKEDIT);
			pEditCtrl->CreateControl();
			pControl = pEditCtrl;
		((CGXStatic*)pControl)->ImplementCellTips();
		}
		break;

	case GX_IDS_CTRL_RICHEDIT:
#if _MFC_VER >= 0x0400
		{
			CGXRichEditCtrl* pWnd = new CGXRichEditCtrl(pGrid);
			pWnd->CreateControl(ES_MULTILINE, GX_IDS_CTRL_RICHEDIT);
			pControl = pWnd;
		}
#endif
		break;

	case GX_IDS_CTRL_PROGRESS:
		pControl = new CGXProgressCtrl(pGrid);
		break;

	case GX_IDS_CTRL_PASSWORD:
		pControl = new CGXPasswordControl(pGrid, GX_IDS_CTRL_PASSWORD);
		((CGXStatic*)pControl)->ImplementCellTips();
		break;

	case GX_IDS_CTRL_CBS_TABBED_DROPDOWN:
		// register dropdown list
		if (!bWin32s)
		{
			CGXTabbedComboBoxWnd* pWnd = new CGXTabbedComboBoxWnd(pGrid);
			pWnd->CreateControl(CBS_DROPDOWN, GX_IDS_CTRL_CBS_TABBED_DROPDOWN);
			pControl = pWnd;
			break;
		}
		// Win32s - FALL THROUGH (use CGXTabbedComboBox instead)

	case GX_IDS_CTRL_CBS_TABBED_DROPDOWNLIST:
		// register dropdown list
		if (!bWin32s)
		{
			CGXTabbedComboBoxWnd* pWnd = new CGXTabbedComboBoxWnd(pGrid);
			pWnd->CreateControl(CBS_DROPDOWNLIST, GX_IDS_CTRL_CBS_TABBED_DROPDOWNLIST);
			pWnd->m_bDropDownOnClick = TRUE;
			pControl = pWnd;
			break;
		}
		// Win32s - FALL THROUGH (use CGXTabbedComboBox instead)

	case GX_IDS_CTRL_TABBED_COMBOBOX:
		// register dropdown list
		{
			CGXTabbedComboBox* pWnd = new CGXTabbedComboBox(pGrid, GX_IDS_CTRL_TABBED_COMBOBOX, GX_IDS_CTRL_TABBED_COMBOBOX);
			pControl = pWnd;
		((CGXStatic*)pControl)->ImplementCellTips();
		}
		break;

#if _MFC_VER >= 0x0400
	case GX_IDS_CTRL_CHECKLIST_COMBOBOX:
		// register dropdown check list
		{
			CGXCheckListComboBox* pWnd = new CGXCheckListComboBox(pGrid);
			pControl = pWnd;
		((CGXStatic*)pControl)->ImplementCellTips();
		}
		break;

	case GX_IDS_CTRL_DATETIME:
		{
			//CGXDateTimeCtrl* pDateTime = new CGXDateTimeCtrl(pGrid, GX_IDS_CTRL_DATETIME);
			// QA 31461
                    Friend_CGXDateTimeCtrl* pDateTime = (Friend_CGXDateTimeCtrl*)(new CGXDateTimeCtrl(pGrid, GX_IDS_CTRL_DATETIME));
			pDateTime->CreateControl(WS_CHILD|GXDT_DTS_UPDOWN|GXDT_DTS_CALENDAR, CRect(0,0,0,0));
			// If you don't want spin buttons remove the GXDT_DTS_UPDOWN flag above!
			pDateTime->m_bInactiveDrawButton = FALSE;
			pDateTime->m_bInactiveDrawSpin = FALSE;
                    // QA 31461
			pDateTime->m_bDateValueAsNumber = TRUE; // set this TRUE if values should be stored
				                                 // as number and not as date string. This is especially very essential if you
				                                 // need support for differnt languages, e.g. if a document gets serialized with
				                                 // an english computer and reloaded on a german computer.
			pControl = pDateTime;
		((CGXStatic*)pControl)->ImplementCellTips();
		}
		break;

	case GX_IDS_CTRL_DATETIMENOCAL:
		{
			//CGXDateTimeCtrl* pDateTimeNoCal = new CGXDateTimeCtrl(pGrid, GX_IDS_CTRL_DATETIMENOCAL);
			// QA 31461
            Friend_CGXDateTimeCtrl* pDateTimeNoCal = (Friend_CGXDateTimeCtrl*)(new CGXDateTimeCtrl(pGrid, GX_IDS_CTRL_DATETIMENOCAL));
			pDateTimeNoCal->CreateControl(WS_CHILD|GXDT_DTS_UPDOWN, CRect(0,0,0,0));
			pDateTimeNoCal->m_bInactiveDrawSpin = FALSE;
			pDateTimeNoCal->m_bInactiveDrawButton = FALSE;
                    // QA 31461
			pDateTimeNoCal->m_bDateValueAsNumber = TRUE; // set this TRUE if values should be stored
				                                      // as number and not as date string. This is especially very essential if you
				                                      // need support for differnt languages, e.g. if a document gets serialized with
				                                      // an english computer and reloaded on a german computer.
			pControl = pDateTimeNoCal;
		((CGXStatic*)pControl)->ImplementCellTips();
		}
		break;

		case GX_IDS_CTRL_CURRENCY:
			{
				CGXCurrencyEdit* pCurrency = new CGXCurrencyEdit(pGrid, GX_IDS_CTRL_CURRENCY);
				pCurrency->CreateControl(WS_CHILD);
				pControl = pCurrency;
		((CGXStatic*)pControl)->ImplementCellTips();
			}
			break;
#endif
	}

	return pControl;
}


void CGXControlFactory::RegisterAllUserAttributes(CGXStylesMap* pStylesMap)
{
	pStylesMap;

	CGXControl::AddUserAttributes(pStylesMap);
	CGXComboBox::AddUserAttributes(pStylesMap);

	CGXSpinEdit::AddUserAttributes(pStylesMap);
	CGXCheckBox::AddUserAttributes(pStylesMap);
 CGXRadioButtonEx::AddUserAttributes(pStylesMap);
	CGXMaskControl::AddUserAttributes(pStylesMap);
	CGXProgressCtrl::AddUserAttributes(pStylesMap);
	CGXTabbedComboBox::AddUserAttributes(pStylesMap);
	CGXTabbedComboBoxWnd::AddUserAttributes(pStylesMap);
#if _MFC_VER >= 0x0400
	CGXDateTimeCtrl::AddUserAttributes(pStylesMap);
	CGXCurrencyEdit::AddUserAttributes(pStylesMap);
#endif

	// Tooltips
#if _MFC_VER >= 0x0400
	pStylesMap->AddUserAttribute(GX_IDS_UA_TOOLTIPTEXT,
		CGXStyle().SetWrapText(TRUE).SetAutoSize(TRUE));
#endif

#if _MFC_VER >= 0x0400
		// for the ellipses
		CString strChoice;
		strChoice.LoadString(GX_IDS_CHOICE_ELLIPSE);

		pStylesMap->AddUserAttribute(GX_IDS_UA_ELLIPSISTYPE,
			CGXStyle().SetControl(GX_IDS_CTRL_CBS_DROPDOWNLIST).SetChoiceList(strChoice));
#endif
}

void CGXControlFactory::RegisterWndClasses(HINSTANCE hInstance)
{
	hInstance;

	CGXGridWnd::RegisterClass(hInstance);

	// Tab Window
	CGXTabBeam::RegisterClass(hInstance);
	CGXTabWnd::RegisterClass(hInstance);
}

void CGXControlFactory::UnregisterWndClasses(HINSTANCE hInstance)
{
	hInstance;

	CGXGridWnd::UnregisterClass(hInstance);

	// Tab Window
	CGXTabBeam::UnregisterClass(hInstance);
	CGXTabWnd::UnregisterClass(hInstance);
}

