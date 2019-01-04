///////////////////////////////////////////////////////////////////////////////
// gxdtbase.cpp : Date Time control
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
// Authors: Daniel Jebaraj, Stefan Hoenig
//
// Portions of this code were copied from Objective Toolkit.

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#if _MFC_VER >= 0x0400   // only supported for MFC version 4.0 or greater

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXDTCAL_H_
#include "grid\gxdtcal.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

//FOUNDATION_GLOBAL_FUNC_API(HWND) RWGetSafeHwnd();

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

IMPLEMENT_DYNAMIC(CGXBDTListGadget, CGXBDTGadget)
IMPLEMENT_DYNAMIC(CGXBDTSpinGadget, CGXBDTGadget)
IMPLEMENT_DYNAMIC(CGXBDTButtonGadget, CGXBDTGadget)
IMPLEMENT_DYNAMIC(CGXBDTStaticGadget, CGXBDTGadget)
IMPLEMENT_DYNAMIC(CGXBDTNumericGadget, CGXBDTGadget)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#include <math.h>

// Useful macro for determining the number of elements in an array
#define dimensionof(a) (sizeof(a)/sizeof(a[0]))

TCHAR* gx_str_replace(const TCHAR* pszInput, const TCHAR* pszOld, const TCHAR* pszNew)
{
	// calculate the lengths
	DWORD dwInputLen = (DWORD)_tcslen(pszInput);
	DWORD dwOldLen = (DWORD)_tcslen(pszOld);
	DWORD dwNewLen = (DWORD)_tcslen(pszNew);

	DWORD dwLen = dwInputLen + dwNewLen - dwOldLen + 1;
	
	if(dwInputLen == 0 || dwLen == 0)
		return NULL; // error
		
	TCHAR* pszRet = new TCHAR[dwLen];
	
	if(pszRet == NULL)
		return NULL; 
	
	TCHAR* pszPos =(TCHAR*)_tcsstr(pszInput, pszOld);
	
	if(pszPos == NULL)
	{
		if(pszRet)
			delete [] pszRet;
		return NULL; // substring not found
	}
		
	TCHAR* _pszRet = pszRet;
	
	DWORD dwSize = (DWORD)(pszPos-pszInput);
	memcpy(pszRet, pszInput, dwSize*sizeof(TCHAR)); 
	pszRet+=dwSize;

	dwSize = dwNewLen;
	memcpy(pszRet, pszNew, dwNewLen*sizeof(TCHAR)); 
	pszRet+=dwSize;
	
	dwSize = dwInputLen - ( (DWORD)(pszPos - pszInput) + dwOldLen);
	memcpy(pszRet, pszPos + dwOldLen, dwSize*sizeof(TCHAR)); 
	pszRet+=dwSize;
	
	*pszRet = _T('\0');

	return _pszRet;
}

// In fast data entry mode, use tab to move between fields.

// Timers values, in milli-seconds, used for firing spin events
//static const int nInitialTimer = 500;		// We wait 500ms before going into
//static const int nNormalTimer  = 100;		// firing spin events every 100ms.


// Minimum and maximum values of COleDateTime
static const COleDateTime minDateTime = DATE(-657434L);	// About year 100
static const COleDateTime maxDateTime = DATE(2958465L);	// About year 9999

/////////////////////////////////////////////////////////////////////////////
// CGXBDateTimeCtrl window
//

IMPLEMENT_DYNAMIC(CGXBDateTimeCtrl, CWnd)

BEGIN_MESSAGE_MAP(CGXBDateTimeCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_GETDLGCODE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_SIZE()
	ON_WM_ENABLE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_CANCELMODE()
	ON_MESSAGE(WM_SETTINGCHANGE, OnSettingChange)
	ON_WM_SYSKEYDOWN()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_WM_DESTROY()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_MESSAGE(GXDT_OK, OnCalendarOK)
	ON_MESSAGE(GXDT_CANCEL, OnCalendarCancel)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGXBDateTimeCtrl - construction
//
CGXBDateTimeCtrl::CGXBDateTimeCtrl()
{
	m_nCurGadget     =
	m_nXOrigin       =
	m_nFixed         =
	m_nRightOffset   =
	m_nState         =
	m_nNoEdit        = 0;
	m_bFastInput     = TRUE;
	m_formatType     = ShortDate;
	m_validMode      = NoValidation;
	m_hFont          = NULL;
	m_pCapture       = NULL;
	m_pPopupCalendar = NULL;
	m_datetime       = COleDateTime::GetCurrentTime();		// Default to now
	m_datetimeMin    = minDateTime;
	m_datetimeMax    = maxDateTime;
	m_nBkDisabled    = COLOR_BTNFACE;
	m_nCalBmp        = GX_IDB_DOWNARROW;
	m_bHourPM		 = FALSE;

	
	ASSERT(m_datetime.GetStatus()    == COleDateTime::valid &&
		   m_datetimeMin.GetStatus() == COleDateTime::valid &&
		   m_datetimeMax.GetStatus() == COleDateTime::valid);

	// ADDED for OG
	m_clrText = GXGetSysData()->clrText;
	m_clrWindow = GXGetSysData()->clrWindow;

	// Handles the spinner timing, in msecs.
	// To slow spinner, after call to OnInitialUpdate, try 
	//  ((CGXDateTimeCtrl*)GetRegisteredControl(GX_IDS_CTRL_DATETIME))
	//                                            ->m_nNormalTimer = 200;
	m_nInitialTimer = 500;
	m_nNormalTimer  = 100;	

}

CGXBDateTimeCtrl::~CGXBDateTimeCtrl()
{
	// Reset any state
	Tidy();

	// ... then destroy all the gadgets.
	for(int i=0; i<m_gadgets.GetSize(); i++)
		delete m_gadgets[i];

	m_gadgets.RemoveAll();
}

BOOL CGXBDateTimeCtrl::CreateEx(DWORD dwExStyle, DWORD dwStyle, const RECT& rect, 
							   CWnd* pParentWnd, UINT nID, 
							   CCreateContext* pContext)
{
	// First we attempt to create the window
	if(!CWnd::CreateEx(dwExStyle,
					   AfxRegisterWndClass(0, GXGetSysData()->hcurArrow),
					   NULL,
					   dwStyle | WS_CHILD,
					   rect.left,
					   rect.top,
					   rect.right - rect.left,
					   rect.bottom - rect.top,
					   pParentWnd->GetSafeHwnd(),
					   (HMENU)(SEC_DWORD)nID,
					   (LPVOID) pContext))
	{
		// Failed to create the window
		ASSERT(0);
		return FALSE;
	}
	
	ASSERT_VALID(this);

	// Get the font to use with this control, we initially base this on our
	// parents font.
	CFont* pFont = pParentWnd->GetFont();
	if(pFont)
		m_hFont = *pFont;
	else
		m_hFont = (HFONT) ::GetStockObject(SYSTEM_FONT);

	// If we are to have a calendar control, then we create a fixed (right
	// aligned) button gadget for this now.
	m_nFixed = 0;
	if(dwStyle & GXDT_DTS_CALENDAR)
	{
		CGXBDTButtonGadget* pGadget = new CGXBDTButtonGadget;
		
		pGadget->SetStyle(pGadget->GetStyle() | CGXBDTGadget::IsFixed);
		
		/* $$
		pGadget->Initialise(this, MAKEINTRESOURCE(GX_IDB_DOWNARROW), 
							GXDT_DTID_CALDROPDOWN);
		*/
		pGadget->Initialise(this, MAKEINTRESOURCE(m_nCalBmp), 
							GXDT_DTID_CALDROPDOWN);
		
		m_gadgets.Add(pGadget);
		
		m_nFixed++;
	}
	
	// If we are to have a spinner control, thenm we create the fixed (right
	// aligned) spinner gadget now.
	if(dwStyle & GXDT_DTS_UPDOWN)
	{
		CGXBDTSpinGadget* pGadget = new CGXBDTSpinGadget;
		
		pGadget->SetStyle(pGadget->GetStyle() | CGXBDTGadget::IsFixed);
		pGadget->Initialise(this, GXDT_DTID_SPINNER);
		
		m_gadgets.Add(pGadget);
		
		m_nFixed++;
	}
	
	// Reset the index of the gadget with focus (to skip past any fixed 
	// gadgets)
	m_nCurGadget = m_nFixed;

	// Parse the set date/time string to build the gadget array (m_gadgets)
	ParseDateTimeFormat();

	// Now layout these gadgets within the window.
	LayoutGadgets();

	return TRUE;
}

BOOL CGXBDateTimeCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
							 UINT nID, CCreateContext* pContext)
{
	return CreateEx(0, dwStyle, rect, pParentWnd, nID, pContext);
}

void CGXBDateTimeCtrl::OnCreatePopupCalendar() 
{ 
	m_pPopupCalendar = new CGXBPopupCalendar; 
}

/////////////////////////////////////////////////////////////////////////////
// CGXBDateTimeCtrl - operations
//

//---------------------------------------------------------------------------
// InvalidateGadget
//
// This function is responsible for forcing a re-paint of the given gadget.
//
void CGXBDateTimeCtrl::InvalidateGadget(CGXBDTGadget* pGadget, 
									   BOOL bImmediateRedraw /* = FALSE */)
{
	// Get the window rectangle of the gadget (relative to our client)
	CRect r = pGadget->GetRect();

	// If our window is offset, then adjust the gadget rectangle accordingly
	if(!(pGadget->GetStyle() & CGXBDTGadget::IsFixed))
		r.OffsetRect(-m_nXOrigin, 0);

	// ... now force the re-paint
	InvalidateRect(r);

	if(bImmediateRedraw)
		UpdateWindow();
}

void CGXBDateTimeCtrl::InvalidateGadget(int nIndex, 
									   BOOL bImmediateRedraw /* = FALSE */)
{
	InvalidateGadget(m_gadgets[nIndex], bImmediateRedraw);
}

//---------------------------------------------------------------------------
// GadgetFromPoint
//
// Returns the index of the gadget at the given point
//
int CGXBDateTimeCtrl::GadgetFromPoint(CPoint point)
{
	// First we compare against the fixed gadgets.
	int i;
	for(i=0; i<m_nFixed ; i++)
	{
		// We ignore CGXBDTStaticGadgets.
		if(m_gadgets[i]->GetStyle() & 
		   (CGXBDTGadget::WantFocus | CGXBDTGadget::WantMouse))
		{
			if(m_gadgets[i]->GetRect().PtInRect(point))
				return i;
		}
	}

	// Now offset the origin as appropriate and check against the scrollable
	// gadgets
	point.x += m_nXOrigin;
	for(; i<m_gadgets.GetSize(); i++)
	{
		if((m_gadgets[i]->GetStyle() & 
			(CGXBDTGadget::WantFocus | CGXBDTGadget::WantMouse)) &&
		   point.x <= m_gadgets[i]->GetRect().right)
			return i;
	}

	// Not found a match yet, so return the gadget closest to the given point.
	for(i=(int)m_gadgets.GetSize()-1; 
		i > m_nFixed && !(m_gadgets[i]->GetStyle() & 
		(CGXBDTGadget::WantFocus | CGXBDTGadget::WantMouse)); i--);

	return i;
}

//---------------------------------------------------------------------------
// BringIntoView
//
// This function will ensure that the given gadget is in view. If it is not
// fully in view then the origin for the moveable gadgets will be offset so
// that the gadget is visible.
//
void CGXBDateTimeCtrl::BringIntoView(CGXBDTGadget* pGadget)
{
	// Get the visible portion of the client rectangle
	CRect clientRect;
	GetClientRect(&clientRect);		 
	if (clientRect.IsRectEmpty())
		return;

	clientRect.DeflateRect(1, 0);			// 1 pixel space between gadgets
											// and borders
	clientRect.right -= m_nRightOffset;		// Remove any fixed gadgets
	clientRect.OffsetRect(m_nXOrigin, 0);	// Adjust for any adjustment of
											// the origin


	const CRect& r = pGadget->GetRect();
	CRect intersect;
	intersect.IntersectRect(clientRect, r);
	if(r != intersect)
	{
		// Part of the gadget is outside the viewable area, bring it inside
		if(r.left < clientRect.left)
			// We'll bring it in from the left
			m_nXOrigin = r.left;
		else if(r.right > clientRect.right)
		{
			// Part of the right hand edge is missing, see what we can do about
			// this.
			int nDiff = r.right - clientRect.right;
			clientRect.OffsetRect(nDiff, 0);
			if(r.left < clientRect.left)
				// It's too big for the client area, so just ensure that it is
				// left aligned
				m_nXOrigin = r.left;
			else
				// Align the right hand edge
				m_nXOrigin += nDiff;
		}

		InvalidateRect(NULL, FALSE);
	}
}

void CGXBDateTimeCtrl::BringIntoView(int nIndex)
{
	BringIntoView(m_gadgets[nIndex]);
}

//---------------------------------------------------------------------------
// SetFormat
//
// Sets the current format to one of the locale dependant formats
//
void CGXBDateTimeCtrl::SetFormat(FormatType format)
{
	// Wrong function for Custom format
	ASSERT(format != Custom);

	m_strCustomFormat.Empty();
	m_formatType = format;

	// Rebuild the gadget array
	ResetGadgets();
}

//---------------------------------------------------------------------------
// SetFormat
//
// Sets the current format to the given customized string
//
void CGXBDateTimeCtrl::SetFormat(LPCTSTR lpszFormat)
{
	m_strCustomFormat = lpszFormat;
	m_formatType      = Custom;

	// Rebuild the gadget array
	ResetGadgets();
}

//---------------------------------------------------------------------------
// GetFormat
//
// Returns the current format mode
//
void CGXBDateTimeCtrl::GetFormat(FormatType& format) const
{
	format = m_formatType;
}

//---------------------------------------------------------------------------
// GetFormat
//
// Returns the current format string.
//
void CGXBDateTimeCtrl::GetFormat(CString& format) const
{
	if(m_formatType == Custom)
		// It is a custom format string
		format = m_strCustomFormat;
	else
	{
		// It is a locale dependant one. Extract and return.
		LCID lcid = GetUserDefaultLCID();
		LCTYPE lcType = 0;
		switch(m_formatType)
		{
		case Time:      lcType = LOCALE_STIMEFORMAT; break;
		case DateTime: //same as ShortDate
		case ShortDate: lcType = LOCALE_SSHORTDATE;  break;
		case LongDate:  lcType = LOCALE_SLONGDATE;   break;
		}

		GetLocaleInfo(lcid, lcType, format.GetBuffer(256), 256);
		format.ReleaseBuffer();
		if( m_formatType == DateTime )
		{
			CString s;
			GetLocaleInfo(lcid, LOCALE_STIMEFORMAT, s.GetBuffer(256), 256);
			s.ReleaseBuffer();
			format += _T(" ") + s;
		}
	}
}

//---------------------------------------------------------------------------
// SizeToContent
//
// Sets the size of the control to the exact size of it's contents.
//
void CGXBDateTimeCtrl::SizeToContent()
{
	if(!m_hWnd || !m_gadgets.GetSize())
		return;

	// Calculate size of borders.
	CRect rect;
	rect.SetRectEmpty();
	AdjustWindowRectEx(&rect, GetStyle(), FALSE, GetExStyle());

	// Align at 0, 0
	rect.OffsetRect(-rect.left, -rect.top);

	// Add in size of fixed gadgets
	rect.right += m_nRightOffset;

	// Add in size of moveable gadgets
	for(int i=m_nFixed; i<m_gadgets.GetSize(); i++)
		rect.right +=m_gadgets[i]->GetRect().Width();
	rect.right += 3;

	if(m_gadgets.GetSize() > m_nFixed)
	{
		// If we have moveable gadgets, then height is set to the height
		// of the first moveable gadget (all moveable gadgets should be
		// same height).
		rect.bottom += m_gadgets[m_nFixed]->GetRect().Height();
		rect.bottom += 2;
	}
	else if(m_nFixed)
		// If we only have fixed gadgets, then height is set to that of the
		// first fixed gadget (all fixed gadgets are same height).
		rect.bottom += m_gadgets[0]->GetRect().Height();

	// Now set the new size of the control
	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), 
				 SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
}


//---------------------------------------------------------------------------
// EnableFastInput
//
// Enables fast input mode. In this mode we automatically advance to the 
// next gadget when a numeric gadget has received it's maximum number of
// digits (such as a user entering 02 to a 2 digit month field).
//
void CGXBDateTimeCtrl::EnableFastEntry(BOOL bEnable /* = TRUE */)
{
	m_bFastInput = bEnable;
}

//---------------------------------------------------------------------------
// IsFastInputEnabled
//
// Returns TRUE if fast input is currently enabled.
//
BOOL CGXBDateTimeCtrl::IsFastEntryEnabled() const
{
	return m_bFastInput;
}

// Tells if the current gadget the right most or left most gadget that 
// wants the focus

BOOL CGXBDateTimeCtrl::IsFocusOnRightMostGadget() const
{
	int nGadget = m_nCurGadget + 1;
	while(nGadget < m_gadgets.GetSize())
	{
		if(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantFocus)
		{
			// Can move to the right
			return FALSE;
		}

		nGadget++;
	}
	return TRUE;
}

BOOL CGXBDateTimeCtrl::IsFocusOnLeftMostGadget() const
{
	int nGadget = m_nCurGadget - 1;
	while(nGadget >= 0)
	{
		if(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantFocus)
		{
			// Can move to the left
			return FALSE;
		}

		nGadget--;
	}
	return TRUE;
}

//---------------------------------------------------------------------------
// SetModified
//
// Sets the date and time modification state.
//
void CGXBDateTimeCtrl::SetModified(BOOL bModified)
{
	if(bModified)
		m_nState |= DateModified|TimeModified;
	else
		m_nState &= ~(DateModified|TimeModified);
}

void CGXBDateTimeCtrl::SetModified(BOOL bDate, BOOL bTime)
{
	if(bDate)
		m_nState |= DateModified;
	else
		m_nState &= ~DateModified;

	if(bTime)
		m_nState |= TimeModified;
	else
		m_nState &= ~TimeModified;
}

//---------------------------------------------------------------------------
// IsModified
//
// Returns the current modification state
//
BOOL CGXBDateTimeCtrl::IsModified() const
{
	return (m_nState & (TimeModified|DateModified)) ? TRUE : FALSE;
}

void CGXBDateTimeCtrl::IsModified(BOOL& bDate, BOOL& bTime) const
{
	bDate = (m_nState & DateModified) ? TRUE : FALSE;
	bTime = (m_nState & TimeModified) ? TRUE : FALSE;
}

//---------------------------------------------------------------------------
// IsEditting
//
// Returns TRUE if a numeric gadget is in the middle of being editted.
//
BOOL CGXBDateTimeCtrl::IsEditing() const
{
	return (m_nState & Editing) ? TRUE : FALSE;
}

//---------------------------------------------------------------------------
// SetDateTime
//
// Sets the current date and time.
//
BOOL CGXBDateTimeCtrl::SetDateTime(const COleDateTime& datetime)
{
	ASSERT(datetime.GetStatus() == COleDateTime::valid);
	if(datetime.GetStatus() != COleDateTime::valid)
		// New date/time is invalid!
		return FALSE;

	// Update gadgets with the new date/time value.

	if(m_hWnd != NULL)
		UpdateGadgets(datetime);
	else
		m_datetime = datetime;

	return TRUE;
}

//---------------------------------------------------------------------------
// SetDate
//
// Sets the current date (only)
//
BOOL CGXBDateTimeCtrl::SetDate(const COleDateTime& date)
{
	ASSERT(date.GetStatus() == COleDateTime::valid);
	if(date.GetStatus() != COleDateTime::valid)
		// New date is invalid.
		return FALSE;

	// Add new date to current time.
	COleDateTime temp;
	if(temp.SetDateTime(date.GetYear(),
					date.GetMonth(),
					date.GetDay(),
					m_datetime.GetHour(),
					m_datetime.GetMinute(),
					m_datetime.GetSecond()))
		return FALSE;

	// Update gadgets with the new date.
	if(m_hWnd != NULL)
		UpdateGadgets(temp);
	else
		m_datetime = temp;

	return TRUE;
}

//---------------------------------------------------------------------------
// SetTime
//
// Sets the current time (only)
//
BOOL CGXBDateTimeCtrl::SetTime(const COleDateTime& time)
{
	ASSERT(time.GetStatus() == COleDateTime::valid);
	if(time.GetStatus() != COleDateTime::valid)
		// New time is invalid
		return FALSE;
	
	// Add new time to current date
	COleDateTime temp;
	if(temp.SetDateTime(m_datetime.GetYear(),
						m_datetime.GetMonth(),
						m_datetime.GetDay(),
						time.GetHour(),
						time.GetMinute(),
						time.GetSecond()))
		return FALSE;

	// Update gadgets with the new time
	if(m_hWnd != NULL)
		UpdateGadgets(temp);
	else
		m_datetime = temp;

	return TRUE;
}

//---------------------------------------------------------------------------
// GetDateTime
//
// Returns the current date and time.
//
const COleDateTime& CGXBDateTimeCtrl::GetDateTime() const
{
	return m_datetime;
}

//---------------------------------------------------------------------------
// SetMinMax
//
// Sets the minimum and maximum date and time (and validation mode to be
// applied.
//
BOOL CGXBDateTimeCtrl::SetMinMax(const COleDateTime& minDateTime, 
								const COleDateTime& maxDateTime,
								ValidationMode mode /* = DateTime */)
{
	ASSERT(minDateTime.GetStatus() == COleDateTime::valid && 
		   maxDateTime.GetStatus() == COleDateTime::valid);
	ASSERT(minDateTime <= maxDateTime);

	if(minDateTime.GetStatus() != COleDateTime::valid || 
	   maxDateTime.GetStatus() != COleDateTime::valid || 
	   minDateTime > maxDateTime)
	   // Invalid range supplied
		return FALSE;

	struct tm tmMin, tmMax;
	if(!GXBGetTmFromOleDate(minDateTime, tmMin) || 
	   !GXBGetTmFromOleDate(maxDateTime, tmMax))
		return FALSE;

	switch(mode)
	{
	case TimeValidation:
		// Time validation only. Set the min/max values using a base year
		VERIFY(!m_datetimeMin.SetDateTime(1899, 12, 30, tmMin.tm_hour, 
										  tmMin.tm_min, tmMin.tm_sec));
		VERIFY(!m_datetimeMax.SetDateTime(1899, 12, 30, tmMax.tm_hour, 
										  tmMax.tm_min, tmMax.tm_sec));
		if(m_datetimeMin.GetStatus() != COleDateTime::valid || 
		   m_datetimeMax.GetStatus() != COleDateTime::valid)
			return FALSE;

		break;

	case DateValidation:
		// Date validation only. Set the min/max values using a time of
		// midnight.
		VERIFY(!m_datetimeMin.SetDateTime(tmMin.tm_year, tmMin.tm_mon, 
										  tmMin.tm_mday, 0, 0, 0));
		VERIFY(!m_datetimeMax.SetDateTime(tmMax.tm_year, tmMax.tm_mon, 
										  tmMax.tm_mday, 0, 0, 0));
		if(m_datetimeMin.GetStatus() != COleDateTime::valid || 
		   m_datetimeMax.GetStatus() != COleDateTime::valid)
			return FALSE;

		break;

	case DateTimeValidation:
	default:
		// Both date and time validation. 
		m_datetimeMin = minDateTime;
		m_datetimeMax = maxDateTime;
		break;
	}

	m_validMode       = mode;

	// Bring date into line with new ranges
	COleDateTime temp = m_datetime;
	if(!Validate(temp, -1))
	{
		ASSERT(0);
		return FALSE;
	}

	// and updates gadgets with new date (if necessary)
	if(m_hWnd != NULL)
		UpdateGadgets(temp);

	return TRUE;
}

//---------------------------------------------------------------------------
// GetMinMax
//
// Returns the current validation method and ranges.
//
CGXBDateTimeCtrl::ValidationMode 
		CGXBDateTimeCtrl::GetMinMax(COleDateTime& minDateTime, 
								   COleDateTime& maxDateTime) const
{
	minDateTime = m_datetimeMin;
	maxDateTime = m_datetimeMax;

	return m_validMode;
}

//---------------------------------------------------------------------------
// Validate
//
// Validates that the current date/time is valid.
//
BOOL CGXBDateTimeCtrl::Validate(const COleDateTime& datetime) const
{
	if(datetime.GetStatus() != COleDateTime::valid)
		return FALSE;

	struct tm tmNew;
	if(!GXBGetTmFromOleDate(datetime, tmNew))
	{
		ASSERT(0);
		return FALSE;
	}

	// Build a date/time value to compare against the ranges.
	COleDateTime temp;
	switch(m_validMode)
	{
	case TimeValidation:
		// Time validation uses a default year
		if(temp.SetDateTime(1899, 12, 30, tmNew.tm_hour, tmNew.tm_min,
							tmNew.tm_sec))
		{
			ASSERT(0);
			return FALSE;
		}
		break;

	case DateValidation:
		// Date validation uses a time of minute
		if(temp.SetDateTime(tmNew.tm_year, tmNew.tm_mon, tmNew.tm_mday, 
							0, 0, 0))
		{
			ASSERT(0);
			return FALSE;
		}
		break;

	case DateTimeValidation:
		temp = datetime;
		break;

	case NoValidation:
		// No validation required.
		return TRUE;

	default:
		ASSERT(0);
		return FALSE;
	}

//  changed to check to second accuracy...
//	if(temp < m_datetimeMin || temp > m_datetimeMax)
//		// Date and/or time does not fall within required range.
//		return FALSE;

	COleDateTimeSpan tSpan;
	if(temp < m_datetimeMin)
	{
		tSpan = m_datetimeMin - temp;
		if (((int)tSpan.GetTotalSeconds()) != 0 )	
			  return FALSE;	// invalid
	}
	else if(temp > m_datetimeMax)
	{
		tSpan = temp - m_datetimeMax;
		if (((int)tSpan.GetTotalSeconds()) != 0 )
			  return FALSE;	// invalid
	}

	return TRUE;
}

//---------------------------------------------------------------------------
// GetNoEdit
//
// Returns a bit setting define which field are edittable
//
int CGXBDateTimeCtrl::GetNoEdit() const
{
	return m_nNoEdit;
}

//---------------------------------------------------------------------------
// SetNoEdit
//
// Sets which fields are edittable
//
void CGXBDateTimeCtrl::SetNoEdit(int nNoEdit)
{
	m_nNoEdit = nNoEdit;

	// Re-build the gadget array so that the gagdets correctly reflect the
	// no edit status.
	if(m_hWnd)
		ResetGadgets();
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDateTimeCtrl overrideables
//

//---------------------------------------------------------------------------
// OnChanging
//
// This function is called just before a commit of a new date/time is
// performed. You override this if you want to perform any last minute
// validation.
//
BOOL CGXBDateTimeCtrl::OnChanging(const COleDateTime& /* newDateTime */)
{
	// Return FALSE if you want to abort the change
	return TRUE;
}

//---------------------------------------------------------------------------
// OnChanged
//
// This function is called after a new date/time has been commited. The 
// default implementation notifies the parent window with a GXDT_DTN_CHANGED
// notification.
//
void CGXBDateTimeCtrl::OnChanged()
{
	if(GetExStyle() & WS_EX_NOPARENTNOTIFY)
		return;

	GetParent()->SendMessage(WM_COMMAND,
							 (WPARAM) MAKELONG(GetDlgCtrlID(), GXDT_DTN_CHANGED),
							 (LPARAM) m_hWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDateTimeCtrl implementation
//

//---------------------------------------------------------------------------
// LayoutGadgets
//
// Lay's out the gadgets within the client area.
//
void CGXBDateTimeCtrl::LayoutGadgets()
{
	m_nRightOffset = 0;

	// Get DC used for calculating gadget size
	CWindowDC dc(this);
	HFONT hFontOld = (HFONT) dc.SelectObject((HGDIOBJ) m_hFont);

	CRect clientRect;
	GetClientRect(&clientRect);

	// Point holding the position of the next gadget.
	CPoint pt(1, 1);

	// Now we loop through the gadgets sequentially, setting their position.
	for(int i=0; i<m_gadgets.GetSize(); i++)
	{
		CGXBDTGadget& gadget = *m_gadgets[i];

		// Get the size of the gadget.
		gadget.CalcSize(dc);
		CRect r = gadget.GetRect();

		if(gadget.GetRect().bottom == -1)
		{
			// Gadget has no height, so set it to the height of the client
			// rectangle.
			r.OffsetRect(pt);
			r.top    = clientRect.top;
			r.bottom = clientRect.bottom;
		}
		else
			// Move the gadget so that it is left aligned with the previous
			// gadget
			r.OffsetRect(pt);

		if(gadget.GetStyle() & CGXBDTGadget::IsFixed)
		{
			// Fixed gadgets are right aligned.
			clientRect.right -= r.Width();
			r.OffsetRect(clientRect.right - r.left, 0);

			// Increase the amount of space reserved for fixed gadgets
			m_nRightOffset += r.Width();
		}
		else
			pt.x += r.Width();

		gadget.SetRect(r);
	}

	if (hFontOld)
		dc.SelectObject((HGDIOBJ) hFontOld);
}

//---------------------------------------------------------------------------
// Draw
//
// Controls drawing of gadgets to the client area.
//
void CGXBDateTimeCtrl::Draw(CDC& dc)
{
	// Get the current clipping rectangle.
	CRect r;
	dc.GetClipBox(&r);

	// Start by filling the background of the area to be drawn.
	// $$ dc.FillSolidRect(r, m_clrWindow);
	// Commented this out so that we can fill in the actual color stored in the style
	// 7/20/98
	// dc.FillSolidRect(r, m_cBkColor);

	HFONT hFontOld = (HFONT) dc.SelectObject((HGDIOBJ) m_hFont);

	// First we draw the fixed gadgets and remove them from the cliping region
	int i;
	for(i=0; i<m_nFixed; i++)
	{
		const CRect& r = m_gadgets[i]->GetRect();

		if(dc.RectVisible(&r))
		{
			m_gadgets[i]->Draw(dc);

			CRgn clipRgn;
			clipRgn.CreateRectRgn(r.left, r.top, r.right, r.bottom);
			dc.SelectClipRgn(&clipRgn, RGN_XOR);
		}
	}
	
	// Adjust the origin for the current moveable gadgets.
	dc.SetViewportOrg(-m_nXOrigin, 0);

	// and draw the moveable gadgets.
	for(; i<m_gadgets.GetSize(); i++)
	{
		// Added by OG
		dc.SetBkMode(TRANSPARENT);
		dc.SetBkColor(m_clrWindow);
		dc.SetTextColor(m_clrText);

		if(dc.RectVisible(&m_gadgets[i]->GetRect()))
			m_gadgets[i]->Draw(dc);
	}

	dc.SetViewportOrg(0, 0);
	dc.SelectObject((HGDIOBJ) hFontOld);
}


//---------------------------------------------------------------------------
// AdvanceGadget
//
// Moves the currently selected gadget forward to the next gadget that will
// accept focus
//
void CGXBDateTimeCtrl::AdvanceGadget()
{
	int nGadget = m_nCurGadget + 1;
	while(nGadget < m_gadgets.GetSize())
	{
		if(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantFocus)
		{
			// Found a gadget to enable ...
			m_gadgets[m_nCurGadget]->Enable(FALSE);
			m_gadgets[m_nCurGadget = nGadget]->Enable(TRUE);
			BringIntoView(m_nCurGadget);
			break;
		}

		nGadget++;
	}
}

//---------------------------------------------------------------------------
// RetreatGadget
//
// Moves the currently selected gadget backwards to the previous gadgets that
// will accept focus.
//
void CGXBDateTimeCtrl::RetreatGadget()
{
	int nGadget = m_nCurGadget - 1;
	while(nGadget >= 0)
	{
		if(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantFocus)
		{
			// Found a gadget to enable ...
			m_gadgets[m_nCurGadget]->Enable(FALSE);
			m_gadgets[m_nCurGadget = nGadget]->Enable(TRUE);
			BringIntoView(m_nCurGadget);
			break;
		}

		nGadget--;
	}
}

//---------------------------------------------------------------------------
// SpinnerEvent
//
// Handles events from the spinner gadget, by relaying them to the enabled
// gadget.
//
BOOL CGXBDateTimeCtrl::SpinnerEvent(UINT uNotifyCode, int /* nID */, 
								   LPARAM lParam)
{
	if(m_nCurGadget == 0)
         m_nCurGadget = 1;
	m_gadgets[m_nCurGadget]->Enable(TRUE);
	if(m_nCurGadget >= m_gadgets.GetSize())
		return FALSE;

	return OnNotify(uNotifyCode, m_gadgets[m_nCurGadget]->GetID(), lParam);
}

//---------------------------------------------------------------------------
// PopupCalendar
//
// Handles notifications from the calendar popup button gadget. This will
// cause the popup calendar to be displayed.
//
BOOL CGXBDateTimeCtrl::PopupCalendar(UINT /* uNotifyCode */, int /* nID */, 
									LPARAM /* lParam */)
{
	ASSERT(!m_pPopupCalendar);

	if(m_nCurGadget < m_gadgets.GetSize())
		// Reset the currently enabled gadget
		m_gadgets[m_nCurGadget]->OnCancelMode();

//	CGXGridCombo::SetComboBoxDropDown(TRUE);
	GXGetAppData()->m_bDiscardNcActivate = TRUE;

	// Now create and initialise and popup calendar object
// $$	m_pPopupCalendar = new CGXBPopupCalendar;
	OnCreatePopupCalendar();
	ASSERT_VALID(m_pPopupCalendar);

	m_pPopupCalendar->SetHideMode(IDCANCEL);		// cancel on hide

	m_pPopupCalendar->SetBehaviorMode(m_pPopupCalendar->GetBehaviorMode() | 
									  GXDT_PBM_PPSELECTABLE |
									  GXDT_BBM_LBUTTONTRACK);
	m_pPopupCalendar->SetPrePostDrawMode(m_pPopupCalendar->GetPrePostDrawMode() |
									     GXDT_PDM_PREPOSTGRAYED | 
										 GXDT_PDM_BEVELPRESSED);
	m_pPopupCalendar->SetPage(m_datetime, FALSE);
	m_pPopupCalendar->SelectDate(m_datetime, TRUE);

	CRect r;
	GetWindowRect(&r);

	if(!m_pPopupCalendar->Create(WS_VISIBLE | WS_POPUP | WS_THICKFRAME |
								 GXDT_PCS_ALIGNBOTTOMLEFT, 
								 r, 
								 this)) 
	{
		TRACE0("Failed to create CGXBPopupCalendar\n");
		delete m_pPopupCalendar;
		m_pPopupCalendar = NULL;
	}

//	CGXGridCombo::SetComboBoxDropDown(FALSE);
	GXGetAppData()->m_bDiscardNcActivate = FALSE;

	return TRUE;
}

//---------------------------------------------------------------------------
// UpdateGadgets
//
// Updates the gadgets defined in nFlags with the current date/time.
//
void CGXBDateTimeCtrl::UpdateGadgets(UINT nFlags /* = GXDT_DTID_ALL */)
{
	int nTemp = 0;
	struct tm tmTemp;
	
	if(!GXBGetTmFromOleDate(m_datetime, tmTemp))
	{
		ASSERT(0);
		return;
	}

	// Loop through the gadgets, updating as appropriate.
	for(int i=0; i<m_gadgets.GetSize(); i++)
	{
		if(m_gadgets[i]->GetID() != -1 && (m_gadgets[i]->GetID() & nFlags))
		{
			// Update this gadget, first format it's value ...
			switch(m_gadgets[i]->GetID())
			{
			case GXDT_DTID_12HOUR:
				nTemp = tmTemp.tm_hour;
				if(nTemp == 0)
					nTemp = 12;			// 12 am
				else if(nTemp >= 13 && nTemp <= 23)
					nTemp -= 12;		// pm
				break;

			case GXDT_DTID_24HOUR:
				nTemp = tmTemp.tm_hour;;
				break;

			case GXDT_DTID_MINUTE:
				nTemp = tmTemp.tm_min;
				break;

			case GXDT_DTID_SECOND:
				nTemp = tmTemp.tm_sec;
				break;

			case GXDT_DTID_AMPM:
				
				if(tmTemp.tm_hour >= 12)
					nTemp = m_bHourPM = TRUE;
				else
					nTemp = m_bHourPM = 0;
				break;

			case GXDT_DTID_DAYNO:
				nTemp = tmTemp.tm_mday;
				break;

			case GXDT_DTID_DAYNAME:
				nTemp = tmTemp.tm_wday - 1;
				break;

			case GXDT_DTID_MONTHNO:
				nTemp = tmTemp.tm_mon;
				break;

			case GXDT_DTID_MONTHNAME:
				nTemp = tmTemp.tm_mon - 1;
				break;

			case GXDT_DTID_YEAR2:
				nTemp = tmTemp.tm_year % 100;
				break;

			case GXDT_DTID_YEAR4:
				nTemp = tmTemp.tm_year;
				break;
			}

			m_gadgets[i]->SetValue(nTemp);
			InvalidateGadget(i);
		}
	}
}

//---------------------------------------------------------------------------
// UpdateGadgets
//
// Sets the new date/time, and updates those gadgets which will be affected
// by the change.
//
void CGXBDateTimeCtrl::UpdateGadgets(const COleDateTime& datetime)
{
	UINT nUpdate = 0;
	struct tm tmNew, tmCur;

	if(!GXBGetTmFromOleDate(datetime, tmNew) || !GXBGetTmFromOleDate(m_datetime, tmCur))
	{
		ASSERT(0);
		return;
	}

	// Determine which gadgets need to be reset.
	if(tmCur.tm_hour != tmNew.tm_hour)
		nUpdate |= GXDT_DTID_12HOUR | GXDT_DTID_24HOUR | GXDT_DTID_AMPM;
	if(tmCur.tm_min  != tmNew.tm_min)
		nUpdate |= GXDT_DTID_MINUTE;
	if(tmCur.tm_sec  != tmNew.tm_sec)
		nUpdate |= GXDT_DTID_SECOND;
	if(tmCur.tm_wday != tmNew.tm_wday)
		nUpdate |= GXDT_DTID_DAYNAME;
	if(tmCur.tm_mday != tmNew.tm_mday)
		nUpdate |= GXDT_DTID_DAYNO;
	if(tmCur.tm_mon  != tmNew.tm_mon)
		nUpdate |= GXDT_DTID_MONTHNAME | GXDT_DTID_MONTHNO;
	if(tmCur.tm_year != tmNew.tm_year)
		nUpdate |= GXDT_DTID_YEAR2 | GXDT_DTID_YEAR4;

	// And force those gadgets to be reset and redrawn.
	m_datetime = datetime;
	UpdateGadgets(nUpdate);
}

//---------------------------------------------------------------------------
// Validate
//
// Validates the given date/time value. If it is out of range, then various
// fields can be adjusted to bring it into line depending on the value of
// nPos:
//         Year  Month  Day  Hours Minutes Seconds
//    -1    X      X     X     X      X       X  
//	   5           X     X     X      X       X
//     4                 X     X      X       X
//     3                       X      X       X
//     2                              X       X
//     1                                      X
//
BOOL CGXBDateTimeCtrl::Validate(COleDateTime& datetime, int nPos) const
{
	struct tm tmNew, tmBase;

	if(datetime.GetStatus() != COleDateTime::valid)
		return FALSE;

	if(!GXBGetTmFromOleDate(datetime, tmNew))
	{
		return FALSE;
	}

	// Set value to compare against
	COleDateTime temp;
	switch(m_validMode)
	{
	case TimeValidation:
		// We are validating time only, so use a default date
		if(temp.SetDateTime(1899, 12, 30, tmNew.tm_hour, tmNew.tm_min, 
							tmNew.tm_sec))
		{
			ASSERT(0);
			return FALSE;
		}
		break;

	case DateValidation:
		// We are validating date ony, so use a time of midnight
		if(temp.SetDateTime(tmNew.tm_year, tmNew.tm_mon, tmNew.tm_mday, 
							0, 0, 0))
		{
			ASSERT(0);
			return FALSE;
		}
		break;

	case DateTimeValidation:
		temp = datetime;
		break;

	case NoValidation:
		// No validation required.
		return TRUE;

	default:
		ASSERT(0);
		return FALSE;
	}

	COleDateTime base;

// changed to check to second accuracy...
// 	if(temp < m_datetimeMin)
// 		base = m_datetimeMin;
// 	else if(temp > m_datetimeMax)
//		base = m_datetimeMax;
// 	else
//		// Date/Time is valid
// 		return TRUE;
	
	COleDateTimeSpan tSpan;
	if(temp < m_datetimeMin)
	{
		tSpan = m_datetimeMin - temp;
		if ( ((int)tSpan.GetTotalSeconds()) == 0 )	
			return TRUE;	//valid
		base = m_datetimeMin;
	}
	else if(temp > m_datetimeMax)
	{
		tSpan = temp - m_datetimeMax;
		if ( ((int)tSpan.GetTotalSeconds()) == 0 )
			return TRUE;	// Date/Time is valid
		base = m_datetimeMax;
	}
	else
		// Date/Time is valid
		return TRUE;

	// Date/Time is invalid. base is the date we need to adjust towards.
	
	if(nPos == 0)
		// No adjustments allowed:
		return FALSE;

	if(!GXBGetTmFromOleDate(base, tmBase))
	{
		ASSERT(0);
		return FALSE;
	}

	// Check that we can perform the adjustments (this ensures that when
	// we adjust the date/time that it will actual be within the valid
	// ranges).
	switch(nPos)
	{
	case  1: if(tmBase.tm_min  != tmNew.tm_min)  return FALSE;
	case  2: if(tmBase.tm_hour != tmNew.tm_hour) return FALSE;
	case  3: if(tmBase.tm_mday != tmNew.tm_mday) return FALSE;
	case  4: if(tmBase.tm_mon  != tmNew.tm_mon)  return FALSE;
	case  5: if(tmBase.tm_year != tmNew.tm_year) return FALSE;
	case -1: break;
	}

	// And adjust towards the minimum date/time
	switch(nPos)
	{
	case -1: tmNew.tm_year = tmBase.tm_year;
	case  5: tmNew.tm_mon  = tmBase.tm_mon;
	case  4: tmNew.tm_mday = tmBase.tm_mday;
	case  3: tmNew.tm_hour = tmBase.tm_hour;
	case  2: tmNew.tm_min  = tmBase.tm_min;
	case  1: tmNew.tm_sec  = tmBase.tm_sec;
	}

	// Set the new date/time
	datetime.SetDateTime(tmNew.tm_year, tmNew.tm_mon, tmNew.tm_mday, 
						 tmNew.tm_hour, tmNew.tm_min, tmNew.tm_sec);
	
	// and validate it (just in case!)
	return Validate(datetime);
}

//---------------------------------------------------------------------------
// OnNotify
//
// Handles notifications from gadgets.
//
BOOL CGXBDateTimeCtrl::OnNotify(UINT uNotifyCode, int nID, LPARAM lParam)
{
	if(uNotifyCode == GXDT_GN_EDIT)
	{
		// Editting notification from numeric gadget. Set Editing flag
		// accordingly
		if(lParam)
			m_nState |= Editing;
		else
			m_nState &= ~Editing;

		return TRUE;
	}

	if(uNotifyCode == GXDT_GN_NUMERIC_DONE)
	{
		if(m_bFastInput)
		{
			// With fast input enabled, when a value has been completely entered
			// into a numeric gadget we advance forward to the next gadget.
			AdvanceGadget();
			return TRUE;
		}
	}
	// Table mapping gadget IDs to functions to handle notification from
	// that gadget.
	struct 
	{
		int  nID;
		BOOL (CGXBDateTimeCtrl::*fn)(UINT, int, LPARAM);
	}
    static const LookupTable[] =
       {
          { GXDT_DTID_12HOUR,      &CGXBDateTimeCtrl::ChangeHour    },
          { GXDT_DTID_24HOUR,      &CGXBDateTimeCtrl::ChangeHour    },
          { GXDT_DTID_MINUTE,      &CGXBDateTimeCtrl::ChangeMinute  },
          { GXDT_DTID_SECOND,      &CGXBDateTimeCtrl::ChangeSecond  },
          { GXDT_DTID_AMPM,        &CGXBDateTimeCtrl::ChangeAmPm    },
          { GXDT_DTID_DAYNO,       &CGXBDateTimeCtrl::ChangeDay     },
          { GXDT_DTID_DAYNAME,     &CGXBDateTimeCtrl::ChangeDay     },
          { GXDT_DTID_MONTHNO,     &CGXBDateTimeCtrl::ChangeMonth   },
          { GXDT_DTID_MONTHNAME,   &CGXBDateTimeCtrl::ChangeMonth   },
          { GXDT_DTID_YEAR2,       &CGXBDateTimeCtrl::ChangeYear    },
          { GXDT_DTID_YEAR4,       &CGXBDateTimeCtrl::ChangeYear    },
          { GXDT_DTID_CALDROPDOWN, &CGXBDateTimeCtrl::PopupCalendar },
          { GXDT_DTID_SPINNER,     &CGXBDateTimeCtrl::SpinnerEvent  }
       };

	// Find the appropriate handling function and ask it to handle the 
	// notification.
	for(int i=0; i<dimensionof(LookupTable); i++)
	{
		if(LookupTable[i].nID == nID)
			return (this->*LookupTable[i].fn)(uNotifyCode, nID, lParam);
	}

	// Unrecognised gadget?
	ASSERT(0);

	return FALSE;
}

//---------------------------------------------------------------------------
// CaptureMouse
//
// Sets mouse capture for the given gadget.
//
void CGXBDateTimeCtrl::CaptureMouse(CGXBDTGadget* pGadget, BOOL bSet)
{
	if(bSet)			// Setting capture
	{
		// Only one gadget can have capture at a time
		ASSERT(m_pCapture == NULL);

		m_pCapture = pGadget;
		SetCapture();
	}
	else				// Releasing capture
	{
		// Ensure that somebody has capture
		ASSERT(m_pCapture);
		ASSERT_VALID(m_pCapture);

		ReleaseCapture();
		m_pCapture = NULL;
	}
}

//---------------------------------------------------------------------------
// ResetGadgets
//
// Removes all moveable gadgets from the gadget array, before rebuilding them
//
void CGXBDateTimeCtrl::ResetGadgets()
{
	if(m_hWnd)
	{
		// Reset state information first
		Tidy();

		// Remove moveable gadgets
		while(m_gadgets.GetSize() > m_nFixed)
		{
			delete m_gadgets[m_nFixed];
			m_gadgets.RemoveAt(m_nFixed);
		}

		// and then rebuild them
		ParseDateTimeFormat();
		LayoutGadgets();
		Invalidate(FALSE);
	}
}

//---------------------------------------------------------------------------
// Tidy
//
// Resets the current state.
//
void CGXBDateTimeCtrl::Tidy()
{
	if(m_pCapture)
		CaptureMouse(NULL, FALSE);

	if(m_pPopupCalendar)
	{
		delete m_pPopupCalendar;
		m_pPopupCalendar = NULL;
	}
	
	m_nCurGadget = 0;
	m_nXOrigin   = 0;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDateTimeCtrl message handlers
//
void CGXBDateTimeCtrl::OnPaint() 
{
	// Determine background color
	m_cBkColor = IsWindowEnabled() ? GXGetSysData()->clrWindow : 
									 ::GetSysColor(m_nBkDisabled);

	CPaintDC paintDC(this); // device context for painting

	CRect clientRect;
	GetClientRect(&clientRect);

	// Attempt to create an off-screen DC to draw to.
	CDC memDC;
	CBitmap bmp;
	if(memDC.CreateCompatibleDC(&paintDC) == FALSE ||
	   bmp.CreateCompatibleBitmap(&paintDC, clientRect.Width(), 
								  clientRect.Height()) == FALSE)
	{
		// Failed to create the off-screen DC, so just draw to the screen.
		Draw(paintDC);
	}
	else
	{
		CBitmap* pOldBmp = memDC.SelectObject(&bmp);

		CRect clipRect;
		paintDC.GetClipBox(clipRect);

		// Set the clipping region for the off-screen DC
		CRgn clipRgn;
		clipRgn.CreateRectRgn(clipRect.left, clipRect.top, clipRect.right, clipRect.bottom);
		memDC.SelectClipRgn(&clipRgn);
		
		// Included next line to copy over the current bg color to the memdc...
		memDC.BitBlt(clipRect.left, clipRect.top, clipRect.Width(), clipRect.Height(), 
					   &paintDC, clipRect.left, clipRect.top, SRCCOPY);
		

		// and draw to the off-screen DC
		Draw(memDC);

		// Copy the results to the screen DC. 
		paintDC.BitBlt(clipRect.left, clipRect.top, clipRect.Width(), clipRect.Height(), 
					   &memDC, clipRect.left, clipRect.top, SRCCOPY);

		memDC.SelectObject(pOldBmp);
	}
}

void CGXBDateTimeCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);

	if(m_gadgets.GetSize() == 0)
		return;

	if(::GetKeyState(VK_TAB) & 0x8000)
	{
		// We are gaining focus and the tab key is down. The chances are the 
		// user has tabbed into this field. Since we are in fast edit mode
		// we will either move to the first or last gadget in the control
		// (depending on whether this is a forward or back tab).
		int nGadget;

		m_gadgets[m_nCurGadget]->Enable(FALSE);

		if(::GetKeyState(VK_SHIFT) & 0x8000)
		{
			// Find last gadget
			for(nGadget = (int)m_gadgets.GetSize() - 1;
				nGadget >= m_nFixed && 
					!(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantFocus);
				nGadget--);
		}
		else
		{
			// Find first gadget
			for(nGadget = m_nFixed;
				nGadget < m_gadgets.GetSize() &&
					!(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantFocus);
				nGadget++);
		}

		if(nGadget >= m_nFixed && nGadget < m_gadgets.GetSize())
		{
			m_gadgets[m_nCurGadget = nGadget]->Enable(TRUE);
			BringIntoView(m_nCurGadget);
		}
	}
	else

		// We are gaining focus, enable the current gadget.
		m_gadgets[m_nCurGadget]->Enable(TRUE);
}

void CGXBDateTimeCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);

	// We are losing focusm disable the current gadget.
	if(m_gadgets.GetSize())
		m_gadgets[m_nCurGadget]->Enable(FALSE);
}

void CGXBDateTimeCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// Pass WM_CHAR events through to the currently enabled gadget.
	if(!m_gadgets.GetSize())
	{
		CWnd::OnChar(nChar, nRepCnt, nFlags);
		return;
	}

	
	if(nChar == _T('\t'))
		// In fast editmode we process tabs in OnKeyDown ... don't want it
		// here though, so discard it.
		return;

	// Look at the adjacent static gadget. If it matches, then advance to the
	// next gadget. This allows easy advance to the next field when entering a
	// date.
	if((m_nCurGadget + 1) < m_gadgets.GetSize())
	{
		// Look at 
		CGXBDTStaticGadget* pGadget = (CGXBDTStaticGadget*) m_gadgets[m_nCurGadget + 1];
		if(pGadget->IsKindOf(RUNTIME_CLASS(CGXBDTStaticGadget)))
		{
			// Get the caption of the static gadget, removing leading and 
			// trailing spaces before performing a comparison.
			CString temp = pGadget->GetCaption();
			temp.TrimLeft();
			temp.TrimRight();

			if((temp.GetLength() == 0 && TCHAR(nChar) == _T(' ')) ||
			   (temp.GetLength() == 1 && TCHAR(nChar) == temp[0]))
			{
				// We have a match ... so advance.
				AdvanceGadget();
				return;
			}
		}
	}
	
	m_gadgets[m_nCurGadget]->OnChar(nChar);
}

void CGXBDateTimeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(!m_gadgets.GetSize())
	{
		CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}

	if(nChar == VK_LEFT)
	{
		// Left arrow causes us to enable the gadget prior to the currently
		// enabled gadgets.
		int nGadget = m_nCurGadget - 1;
		while(nGadget >= 0)
		{
			if(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantFocus)
			{
				// Found a gadget to enable ...
				m_gadgets[m_nCurGadget]->Enable(FALSE);
				m_gadgets[m_nCurGadget = nGadget]->Enable(TRUE);
				BringIntoView(m_nCurGadget);
				break;
			}

			nGadget--;
		}
	}
	else if(nChar == VK_RIGHT)
	{
		// Right arrow causes us to enable the gadget next to the currently
		// enabled gadgets.
		int nGadget = m_nCurGadget + 1;
		while(nGadget < m_gadgets.GetSize())
		{
			if(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantFocus)
			{
				// Found a gadget to enable ...
				m_gadgets[m_nCurGadget]->Enable(FALSE);
				m_gadgets[m_nCurGadget = nGadget]->Enable(TRUE);
				BringIntoView(m_nCurGadget);
				break;
			}

			nGadget++;
		}
	}
	else if(nChar == VK_F4)
	{
		// F4 is an accelerator for the popup calendar
		if(GetStyle() & GXDT_DTS_CALENDAR)
			PopupCalendar(0, 0, 0);
	}
	else if(nChar == VK_TAB)
	{
		// In fast edit mode, tab will move me to the next gadget. 
		BOOL bShift     = (GetKeyState(VK_SHIFT) & 0x8000) ? TRUE : FALSE;
		if(bShift)				// Shift + tab
			RetreatGadget();
		else					// tab
			AdvanceGadget();
	}
	else
		// Pass remaining WM_KEYDOWN message through to currently enabled
		// gadget.
		m_gadgets[m_nCurGadget]->OnKeyDown(nChar);
}

void CGXBDateTimeCtrl::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(m_gadgets.GetSize() && nChar == VK_DOWN)
	{
		// ALT + Down arrow is an accelerator for the calendar
		if(GetStyle() & GXDT_DTS_CALENDAR)
			PopupCalendar(0, 0, 0);
	}
	else
		CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

UINT CGXBDateTimeCtrl::OnGetDlgCode() 
{
	return DLGC_WANTCHARS|DLGC_WANTARROWS|DLGC_WANTTAB;
}

void CGXBDateTimeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_gadgets.GetSize())
	{
		CWnd::OnLButtonDown(nFlags, point);
		return;
	}

	// Find gadget button press occured over.
	int nGadget = GadgetFromPoint(point);

	if(GetFocus() != this)
	{
		// We don't currently have focus, so get it ...
		if(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantFocus)
			BringIntoView(m_nCurGadget = nGadget);

		SetFocus();
	}
	else if(nGadget != m_nCurGadget && 
		    (m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantFocus))
	{
		// Enable the gadget clicked on.
		m_gadgets[m_nCurGadget]->Enable(FALSE);
		m_gadgets[m_nCurGadget = nGadget]->Enable(TRUE);

		BringIntoView(nGadget);
	}

	// If the gadget hit wants the WM_LBUTTONDOWN, then pass it on.
	if(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantMouse)
	{
		if(!(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::IsFixed))
			point.x += m_nXOrigin;

		m_gadgets[nGadget]->OnLButtonDown(nFlags, point);
	}
}

void CGXBDateTimeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// Pass the WM_MOUSEMOVE message through to gadget with capture
	if(m_pCapture)
	{
		ASSERT_VALID(m_pCapture);
		
		if(!(m_pCapture->GetStyle() & CGXBDTGadget::IsFixed))
			point.x += m_nXOrigin;

		m_pCapture->OnLButtonUp(nFlags, point);
	}
	else
		CWnd::OnLButtonUp(nFlags, point);
}

void CGXBDateTimeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Pass the WM_MOUSEMOVE message through to gadget with capture
	if(m_pCapture)
	{
		ASSERT_VALID(m_pCapture);
		
		if(!(m_pCapture->GetStyle() & CGXBDTGadget::IsFixed))
			point.x += m_nXOrigin;

		m_pCapture->OnMouseMove(nFlags, point);
	}
	else
		CWnd::OnMouseMove(nFlags, point);
}

void CGXBDateTimeCtrl::OnCancelMode() 
{
	// Pass the WM_CANCELMODE message through to gadget with capture
	if(m_pCapture)
	{
		ASSERT_VALID(m_pCapture);

		m_pCapture->OnCancelMode();
	}
	else
		CWnd::OnCancelMode();
}

LRESULT CGXBDateTimeCtrl::OnCalendarOK(WPARAM /* wParam */, LPARAM /* lParam */) 
{
	// The calendar has been dismissed with a new date for us.
	if(m_pPopupCalendar)
	{
		// Extract the new date from the calendar
		COleDateTime newDate = m_pPopupCalendar->GetSelectedDateValue();
		if(newDate.GetStatus() == COleDateTime::valid)
		{
			// CGXBPopupCalendar doesn't preserve date and time, so need to 
			// combine them
			if(!newDate.SetDateTime(newDate.GetYear(),
									newDate.GetMonth(),
									newDate.GetDay(),
									m_datetime.GetHour(),
									m_datetime.GetMinute(),
									m_datetime.GetSecond()))
			{
				if(Validate(newDate) && 
				   OnChanging(newDate))
				{
					// Set the new date ...
					m_nState  |= DateModified;
					UpdateGadgets(newDate);
					OnChanged();
				}
			}
		}

		delete m_pPopupCalendar;
		m_pPopupCalendar = NULL;
	}

	return 0L;
}

LRESULT CGXBDateTimeCtrl::OnCalendarCancel(WPARAM /* wParam */, LPARAM /* lParam */) 
{
	// The calendar has been cancelled.
	delete m_pPopupCalendar;
	m_pPopupCalendar = NULL;

	return 0L;
}

void CGXBDateTimeCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	// Re-layout the gadgets for the new layout.
	LayoutGadgets();
	Invalidate(FALSE);
}

void CGXBDateTimeCtrl::OnSysColorChange() 
{
	// Update all saved color information
	GXGetSysData()->UpdateSysColors();

	for(int i=0; i<m_gadgets.GetSize(); i++)
		m_gadgets[i]->OnSysColorChange();

	CWnd::OnSysColorChange();
}

LRESULT CGXBDateTimeCtrl::OnSettingChange(WPARAM /* wParam */, LPARAM /* lParam */) 
{
	// Could be a change to date/time format or to regional settings.
	// Rebuild my gadget list just in case.
	ResetGadgets();

	return 0;
}

LRESULT CGXBDateTimeCtrl::OnSetFont(WPARAM wParam, LPARAM /* lParam */)
{
	m_hFont = (HFONT) wParam;

	// Re-layout the gadgets for the new font.
	LayoutGadgets();

	// We ignore the redraw flag in lParam and always redraw
	Invalidate(FALSE);

	return 0L;
}

void CGXBDateTimeCtrl::OnDestroy() 
{
	Tidy();

	CWnd::OnDestroy();
}

void CGXBDateTimeCtrl::OnEnable(BOOL /* bEnable */)
{
	Invalidate(FALSE);
}
void CGXBDateTimeCtrl::OnNcCalcSize(BOOL bCalcValidRects, 
								   NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	if(GXGetSysData()->bWin4 || !(GetExStyle() & WS_EX_CLIENTEDGE))
		CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
	else if(bCalcValidRects && lpncsp)
		// We implement the WS_EX_CLIENTEDGE style for Win3 systems.
		InflateRect(&lpncsp->rgrc[0], -2, -2);
}

void CGXBDateTimeCtrl::OnNcPaint() 
{
	if(GXGetSysData()->bWin4 || !(GetExStyle() & WS_EX_CLIENTEDGE))
		CWnd::OnNcPaint();
	else
	{
		// We implement the WS_EX_CLIENTEDGE style for Win3 systems.
		CWindowDC dc(this);

		CRect r;
		GetWindowRect(&r);

		CWnd* pParentWnd = GetParent();
		if(pParentWnd)
			pParentWnd->ScreenToClient(&r);

		r.OffsetRect(-r.left, -r.top);

		dc.Draw3dRect(r, GXGetSysData()->clrBtnShadow, GXGetSysData()->clrBtnHilite);
		r.DeflateRect(1, 1);
		dc.Draw3dRect(r, GXGetSysData()->clrWindowFrame, GXGetSysData()->clrBtnFace);
	}
}


/////////////////////////////////////////////////////////////////////////////
// GXBGetTmFromOleDate
//
// Function to convert a DATE (base for COleDateTime) to a tm structure.
//
BOOL AFXAPI GXBGetTmFromOleDate(DATE dtSrc, struct tm& tmDest)
{
	// Half a second, expressed in days
	static const DATE HALF_SECOND = (1.0/172800.0);

	// One-based array of days in year at month start
	static int rgMonthDays[13] =
		{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

	// The legal range does not actually span year 0 to 9999.
	if (dtSrc > maxDateTime || dtSrc < minDateTime) // about year 100 to about 9999
		return FALSE;

	long nDays;             // Number of days since Dec. 30, 1899
	long nDaysAbsolute;     // Number of days since 1/1/0
	long nSecsInDay;        // Time in seconds since midnight
	long nMinutesInDay;     // Minutes in day

	long n400Years;         // Number of 400 year increments since 1/1/0
	long n400Century;       // Century within 400 year block (0,1,2 or 3)
	long n4Years;           // Number of 4 year increments since 1/1/0
	long n4Day;             // Day within 4 year block
							//  (0 is 1/1/yr1, 1460 is 12/31/yr4)
	long n4Yr;              // Year within 4 year block (0,1,2 or 3)
	BOOL bLeap4 = TRUE;     // TRUE if 4 year block includes leap year

	double dblDate = dtSrc; // tempory serial date

	// If a valid date, then this conversion should not overflow
	nDays = (long)dblDate;

	// Round to the second
	dblDate += ((dtSrc > 0.0) ? HALF_SECOND : -HALF_SECOND);

	nDaysAbsolute = (long)dblDate + 693959L; // Add days from 1/1/0 to 12/30/1899

	dblDate = fabs(dblDate);
	nSecsInDay = (long)((dblDate - floor(dblDate)) * 86400.);

	// Calculate the day of week (sun=1, mon=2...)
	//   -1 because 1/1/0 is Sat.  +1 because we want 1-based
	tmDest.tm_wday = (int)((nDaysAbsolute - 1) % 7L) + 1;

	// Leap years every 4 yrs except centuries not multiples of 400.
	n400Years = (long)(nDaysAbsolute / 146097L);

	// Set nDaysAbsolute to day within 400-year block
	nDaysAbsolute %= 146097L;

	// -1 because first century has extra day
	n400Century = (long)((nDaysAbsolute - 1) / 36524L);

	// Non-leap century
	if (n400Century != 0)
	{
		// Set nDaysAbsolute to day within century
		nDaysAbsolute = (nDaysAbsolute - 1) % 36524L;

		// +1 because 1st 4 year increment has 1460 days
		n4Years = (long)((nDaysAbsolute + 1) / 1461L);

		if (n4Years != 0)
			n4Day = (long)((nDaysAbsolute + 1) % 1461L);
		else
		{
			bLeap4 = FALSE;
			n4Day = (long)nDaysAbsolute;
		}
	}
	else
	{
		// Leap century - not special case!
		n4Years = (long)(nDaysAbsolute / 1461L);
		n4Day = (long)(nDaysAbsolute % 1461L);
	}

	if (bLeap4)
	{
		// -1 because first year has 366 days
		n4Yr = (n4Day - 1) / 365;

		if (n4Yr != 0)
			n4Day = (n4Day - 1) % 365;
	}
	else
	{
		n4Yr = n4Day / 365;
		n4Day %= 365;
	}

	// n4Day is now 0-based day of year. Save 1-based day of year, year number
	tmDest.tm_yday = (int)n4Day + 1;
	tmDest.tm_year = n400Years * 400 + n400Century * 100 + n4Years * 4 + n4Yr;

	// Handle leap year: before, on, and after Feb. 29.
	if (n4Yr == 0 && bLeap4)
	{
		// Leap Year
		if (n4Day == 59)
		{
			/* Feb. 29 */
			tmDest.tm_mon = 2;
			tmDest.tm_mday = 29;
			goto DoTime;
		}

		// Pretend it's not a leap year for month/day comp.
		if (n4Day >= 60)
			--n4Day;
	}

	// Make n4DaY a 1-based day of non-leap year and compute
	//  month/day for everything but Feb. 29.
	++n4Day;

	// Month number always >= n/32, so save some loop time */
	for (tmDest.tm_mon = (n4Day >> 5) + 1;
		n4Day > rgMonthDays[tmDest.tm_mon]; tmDest.tm_mon++);

	tmDest.tm_mday = (int)(n4Day - rgMonthDays[tmDest.tm_mon-1]);

DoTime:
	if (nSecsInDay == 0)
		tmDest.tm_hour = tmDest.tm_min = tmDest.tm_sec = 0;
	else
	{
		tmDest.tm_sec = (int)nSecsInDay % 60L;
		nMinutesInDay = nSecsInDay / 60L;
		tmDest.tm_min = (int)nMinutesInDay % 60;
		tmDest.tm_hour = (int)nMinutesInDay / 60;
	}

	return TRUE;
}

// Useful macro for determining the number of elements in an array
#define dimensionof(a) (sizeof(a)/sizeof(a[0]))

// Date/Time format characters
static const TCHAR cHours12 = _T('h');				// Hours (12 hour clock)
static const TCHAR cHours24 = _T('H');				// Hours (24 hour clock)
static const TCHAR cMinutes = _T('m');				// Minutes
static const TCHAR cSeconds = _T('s');				// Seconds
static const TCHAR cAmPm    = _T('t');				// AM/PM designator
static const TCHAR cDay     = _T('d');				// Day of week/month
static const TCHAR cMonth   = _T('M');				// Month
static const TCHAR cYear    = _T('y');				// Year
static const TCHAR cEra     = _T('g');				// Era

// List of type codes for Am/Pm strings
static const LCTYPE AmPmIds[2] = 
{
	LOCALE_S1159,									// Am 
	LOCALE_S2359									// Pm
};

//-----------------------------------------------------------------------------
//  ParseDateTimeFormat
//
//  Parses the date/time format string returned by GetFormat and builds the
//  gadget array (m_gadgets) for each of the date/time component fields
//
void CGXBDateTimeCtrl::ParseDateTimeFormat()
{
	// Table mapping date/time format characters onto correct function for
	// parsing that format.
	struct 
	{
		TCHAR c;
		void (CGXBDateTimeCtrl::*fn)(LPCTSTR&, LPCTSTR&, UINT);
		UINT  u;
		BOOL bDate;
	}
    static const DTFormatTable[] =
       {
          { cHours12,  &CGXBDateTimeCtrl::ParseHours,      FALSE , 0 },
          { cHours24,  &CGXBDateTimeCtrl::ParseHours,      TRUE  , 0 },
          { cMinutes,  &CGXBDateTimeCtrl::ParseMinutes,    0     , 0 },
          { cSeconds,  &CGXBDateTimeCtrl::ParseSeconds,    0     , 0 },
          { cAmPm,     &CGXBDateTimeCtrl::ParseAmPm,       0     , 0 },
          { cDay,      &CGXBDateTimeCtrl::ParseDay,        0     , TRUE },
          { cMonth,    &CGXBDateTimeCtrl::ParseMonth,      0     , TRUE },
          { cYear,     &CGXBDateTimeCtrl::ParseYear,       0     , TRUE },
          { cEra,      &CGXBDateTimeCtrl::ParseEra,        0     , TRUE },
          { _T('\''),  &CGXBDateTimeCtrl::ParseQuotedText, 0     , 0 },
          { _T('"'),   &CGXBDateTimeCtrl::ParseQuotedText, 0     , 0 }
       };

	// Get the current date/time format string
	CString temp;
	GetFormat(temp);

	m_bDateTokens = FALSE;

	// We loop down the date/time format string. For each character we 
	// recognise, we call a function for parsing that format string. This
	// function will add any text not recognised since the last recognised
	// character as a static gadget, before adding a gadget to handle the
	// recognised date/time component.
	LPCTSTR lpsz = temp;
	LPCTSTR lpszStart = lpsz;
	while(*lpsz)
	{
		// Lookup to see if we know about this character
		for(int i=0; i<dimensionof(DTFormatTable); i++)
		{
			if(DTFormatTable[i].c == *lpsz)
			{
				// We know about it, so call it's parsing function.
				(this->*DTFormatTable[i].fn)(lpszStart, lpsz, 
											 DTFormatTable[i].u);

				m_bDateTokens |= DTFormatTable[i].bDate;

				break;
			}
		}

		lpsz = _tcsinc(lpsz);				// Move forward to next character
	}
	
	// Flush any text not since the last handled sequence.
	FlushStatic(lpszStart, lpsz);

	// Update all new gadgets with the current date/time values
	UpdateGadgets();
}

//-----------------------------------------------------------------------------
//  ParseHours
//
//  Parses the hour fields 'h' and 'H'.
//
//    Formats:   h  hours (12 hour clock) with no lead zero
//              hh  hours (12 hour clock) with lead zero
//               H  hours (24 hour clock) with no lead zero
//              HH  hours (24 hour clock) with lead zero
//
void CGXBDateTimeCtrl::ParseHours(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
								 UINT uParam)
{
	// Add any unrecognised text as static gadget
	FlushStatic(lpszStart, lpsz);

	// Create numeric gadget for handling hours
	CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;

	if(uParam)
	{
		// 24 hour clock
		BOOL bLeadZero = CheckLeadZero(lpsz, cHours24);
		pGadget->Initialise(this, 0, 23, 0, bLeadZero, GXDT_DTID_24HOUR);
	}
	else
	{
		// 12 hour clock
		BOOL bLeadZero = CheckLeadZero(lpsz, cHours12);
		pGadget->Initialise(this, 1, 12, 0, bLeadZero, GXDT_DTID_12HOUR);
	}
	
	if(m_nNoEdit & FixedHour)
	{
		// The user is not allowed to change the hour, so ensure this field
		// can't receive focus
		pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
	}

	m_gadgets.Add(pGadget);

	// Skip past this field
	lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseMinutes
//
//  Parses the minutes field 'm'.
//
//    Formats:   m  minutes with no lead zero
//              mm  minutes with lead zero
//
void CGXBDateTimeCtrl::ParseMinutes(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
								   UINT /* uParam */)
{
	// Add any unrecognised text as static gadget
	FlushStatic(lpszStart, lpsz);

	// Create numeric gadget for handling minutes
	BOOL bLeadZero = CheckLeadZero(lpsz, cMinutes);
	CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;
	pGadget->Initialise(this, 0, 59, 0, bLeadZero, GXDT_DTID_MINUTE);

	if(m_nNoEdit & FixedMinute)
	{
		// The user is not allowed to change the minutes, so ensure this field
		// can't receive focus
		pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
	}

	m_gadgets.Add(pGadget);

	// Skip past this field
	lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseSeconds
//
//  Parses the seconds field 's'.
//
//    Formats:   s  seconds with no lead zero
//              ss  seconds with lead zero
//
void CGXBDateTimeCtrl::ParseSeconds(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
								   UINT /* uParam */)
{
	// Add any unrecognised text as static gadget
	FlushStatic(lpszStart, lpsz);

	// Create numeric gadget for seconds minutes
	BOOL bLeadZero = CheckLeadZero(lpsz, cSeconds);
	CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;
	pGadget->Initialise(this, 0, 59, 0, bLeadZero, GXDT_DTID_SECOND);

	if(m_nNoEdit & FixedSecond)
	{
		// The user is not allowed to change the seconds, so ensure this field
		// can't receive focus
		pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
	}

	m_gadgets.Add(pGadget);

	// Skip past this field
	lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseAmPm
//
//  Parses the am/pm field 't'.
//
//    Formats:   t  One digit Am/Pm designator
//              tt  Complete Am/Pm designator
//
void CGXBDateTimeCtrl::ParseAmPm(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
								UINT /* uParam */)
{
	// Add any unrecognised text as static gadget
	FlushStatic(lpszStart, lpsz);

	// TRUE if we are dealing with abbreviated form
	BOOL bAbbreviated = !CheckLeadZero(lpsz, cAmPm);

	// Build a list of the Am/Pm designators (all 2 of them!)
	TCHAR buf[256];
	LCID lcid = GetUserDefaultLCID();

	CStringArray list;
	for(int i=0; i<dimensionof(AmPmIds); i++)
	{
		GetLocaleInfo(lcid, AmPmIds[i], buf, sizeof(buf));
		if(bAbbreviated)
		{
			LPTSTR ptr = _tcsinc(buf);
			if(ptr)
				*ptr = TCHAR(NULL);
		}

		list.Add(buf);
	}

	// Now create and initialise a list gadget for this field
	CGXBDTListGadget* pGadget = new CGXBDTListGadget;
	pGadget->Initialise(this, list, 0, GXDT_DTID_AMPM);

	if(m_nNoEdit & FixedHour)
	{
		// The user is not allowed to change the hours, so ensure this field
		// can't receive focus.
		pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
	}

	m_gadgets.Add(pGadget);

	// Skip past this field
	lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseDay
//
//  Parses the day and day of week fields 'd'.
//
//    Formats:   d  day of month with no leading zero
//              dd  day of month with leading zero
//             ddd  abbreviated day of week
//            dddd  full day of week
//
void CGXBDateTimeCtrl::ParseDay(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
							   UINT /* uParam */)
{
	// Add any unrecognised text as static gadget
	FlushStatic(lpszStart, lpsz);

	// Determine format required
	BOOL bNumeric = TRUE;
	BOOL bLong    = TRUE;
	if(!CheckLeadZero(lpsz, cDay))
		bLong = FALSE;
	else if(CheckLeadZero(lpsz, cDay))
	{
		bNumeric = FALSE;
		if(!CheckLeadZero(lpsz, cDay))
			bLong = FALSE;
	}

	// We now have:  bLong  bNumeric
	//               FALSE   TRUE        d (day of month with no leading zero)
	//               TRUE    TRUE       dd (day of month with leading zero)
	//               FALSE   FALSE     ddd (abbreviated day of week)
	//               TRUE    FALSE    dddd (full day of week)

	if(bNumeric)
	{
		// Create and initialise numeric gadget for day of month
		CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;
		pGadget->Initialise(this, 1, 31, 0, bLong, GXDT_DTID_DAYNO);

		if(m_nNoEdit & FixedDay)
		{
			// The user is not allowed to change the day, so ensure this field
			// can't receive focus
			pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
		}

		m_gadgets.Add(pGadget);
	}
	else
	{
		// We need to build a list of the locale day's of week names
		CStringArray list;
		CString strDay;

		for(int i=1; i<=7; i++)
		{
			VERIFY(CGXBLocale::GetDayName(strDay, i, bLong));
			list.Add(strDay);		
		}

		// Create and initialise a list gadget (with these day names)
		CGXBDTListGadget* pGadget = new CGXBDTListGadget;
		pGadget->Initialise(this, list, 0, GXDT_DTID_DAYNAME);

		if(m_nNoEdit & FixedDay)
		{
			// The user is not allowed to change the day, so ensure this field
			// can't receive focus
			pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
		}

		m_gadgets.Add(pGadget);
	}

	// Skip past this field
	lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseMonth
//
//  Parses the month field 'M'.
//
//    Formats:   M  Month as digit with no leading zero
//              MM  Month as digit with leading zero
//             MMM  Abbreviated month name
//            MMMM  Full month name
//
void CGXBDateTimeCtrl::ParseMonth(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
								 UINT /* uParam */)
{
	// Add any unrecognised text as static gadget
	FlushStatic(lpszStart, lpsz);

	// Determine format required
	BOOL bNumeric = TRUE;
	BOOL bLong    = TRUE;
	if(!CheckLeadZero(lpsz, cMonth))
		bLong = FALSE;
	else if(CheckLeadZero(lpsz, cMonth))
	{
		bNumeric = FALSE;
		if(!CheckLeadZero(lpsz, cMonth))
			bLong = FALSE;
	}

	// We now have:  bLong  bNumeric
	//               FALSE   TRUE       M (Month as digit with no leading zero)
	//               TRUE    TRUE      MM (Month as digit with leading zero)
	//               FALSE   FALSE    MMM (abbreviated month name)
	//               TRUE    FALSE   MMMM (full month name)

	if(bNumeric)
	{
		// Create and initialise numeric gadget for month digit
		CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;
		pGadget->Initialise(this, 1, 12, 0, bLong, GXDT_DTID_MONTHNO);

		if(m_nNoEdit & FixedMonth)
		{
			// The user is not allowed to change the month, so ensure this 
			// field can't receive focus
			pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
		}

		m_gadgets.Add(pGadget);
	}
	else
	{
		// We need to build a list of the locale month names
		CStringArray list;
		CString strMonth;

		for(int i=1; i<=12; i++)
		{
			VERIFY(CGXBLocale::GetMonthName(strMonth, i, bLong));
			list.Add(strMonth);		
		}

		// Create and initialise a list gadget (with these month names)
		CGXBDTListGadget* pGadget = new CGXBDTListGadget;
		pGadget->Initialise(this, list, 0, GXDT_DTID_MONTHNAME);

		if(m_nNoEdit & FixedMonth)
		{
			// The user is not allowed to change the month, so ensure this 
			// field can't receive focus
			pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
		}

		m_gadgets.Add(pGadget);
	}

	// Skip past this field
	lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseYear
//
//  Parses the year field 'y'.
//
//    Formats:   y  Year as 2 digits with no lead zero for year less than 10
//              yy  Year as 2 digits with lead zero for year less than 10
//             yyy  Year as 4 digits
//            yyyy  Year as 4 digits (same as yyy)
//
void CGXBDateTimeCtrl::ParseYear(LPCTSTR& lpszStart, LPCTSTR& lpsz, 
								UINT /* uParam */)
{
	// Add any unrecognised text as static gadget
	FlushStatic(lpszStart, lpsz);

	BOOL b2Digit   = TRUE;
	BOOL bLeadZero = TRUE;
	if(!CheckLeadZero(lpsz, cYear))
		// 2 digit, no lead zero
		bLeadZero = FALSE;
	else if(CheckLeadZero(lpsz, cYear))
	{
		// 4 digit
		b2Digit   = FALSE;

		// Case of yyy and yyyy are same
		CheckLeadZero(lpsz, cYear);
	}
	// else	2 digit lead zero

	// We now have:  b2Digit  bLeadZero
	//                TRUE     FALSE       y (2 digit with no lead zero)
	//                TRUE     TRUE       yy (2 digit with lead zero)
	//                FALSE    ?        yyyy (4 digit)

	// Create and initialise numeric gadget for year field
	CGXBDTNumericGadget* pGadget = new CGXBDTNumericGadget;
	if(b2Digit)
		pGadget->Initialise(this, 0, 99, 0, bLeadZero, GXDT_DTID_YEAR2);
	else
		pGadget->Initialise(this, 0, 9999, 0, FALSE, GXDT_DTID_YEAR4);

	if(m_nNoEdit & FixedYear)
	{
		// The user is not allowed to change the year, so ensure this 
		// field can't receive focus
		pGadget->SetStyle(pGadget->GetStyle() & (~CGXBDTGadget::WantFocus));
	}

	m_gadgets.Add(pGadget);

	// Skip past this field
	lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseEra
//
//  Parses the era field 'g' (note we don't currently support era's).
//
//    Formats:  gg  Period/era string
//
void CGXBDateTimeCtrl::ParseEra(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT /* uParam */)
{
	// We currently don't handle era's ... so just ignore

	// Add any unrecognised text as static gadget
	FlushStatic(lpszStart, lpsz);

	// Call CheckLeadZero to handle the case of 'gg' as well as 'g'.
	CheckLeadZero(lpsz, cEra);

	// Skip past this field
	lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  ParseQuotedText
//
//  Parses quoted text and emits it through transparently to the gadget list.
//
void CGXBDateTimeCtrl::ParseQuotedText(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT /* uParam */)
{
	// Add any unrecognised text as static gadget
	FlushStatic(lpszStart, lpsz);

	// Find the end of the quoted text
	TCHAR cQuote = *lpsz;

	lpszStart = lpsz = _tcsinc(lpsz);
	
	while(*lpsz && *lpsz != cQuote)
		lpsz = _tcsinc(lpsz);

	// and add this string as a static string
	FlushStatic(lpszStart, lpsz);

	// Move past the last quote
	lpszStart = _tcsinc(lpsz);
}

//-----------------------------------------------------------------------------
//  FlushStatic
//
//  Copies any text not recognised into a static gadget.
//
void CGXBDateTimeCtrl::FlushStatic(LPCTSTR lpszStart, LPCTSTR lpszEnd)
{
	if(lpszStart == lpszEnd)
		// Nothing to flush
		return;

	// Make a copy of the string starting at the start of the static string
	LPTSTR lpszCopy = _tcsdup(lpszStart);
	if(!lpszCopy)
		return;

	// Place a NULL so as to mark the end of "this" static string
	lpszCopy[lpszEnd-lpszStart] = NULL;

	// Now create the static string
	CGXBDTStaticGadget* pGadget = new CGXBDTStaticGadget;
	pGadget->Initialise(this, lpszCopy);
	m_gadgets.Add(pGadget);

	// Remember to free the _tcsdup buffer.
	free(lpszCopy);
}

//-----------------------------------------------------------------------------
//  CheckLeadZero
//
//  Returns TRUE if the given char appears in the next position in the given
//  buffer.
//
BOOL CGXBDateTimeCtrl::CheckLeadZero(LPCTSTR& lpsz, TCHAR c) const
{
	BOOL bLeadZero = FALSE;

	// Move to next character
	LPCTSTR lpszNext = _tcsinc(lpsz);
	if(*lpszNext == c)
	{
		// We have a match, so must return TRUE. Note we also advance to point
		// at this new character.
		bLeadZero = TRUE;
		lpsz      = lpszNext;
	}

	return bLeadZero;
}





// Notes:
//   
//   These functions take the following parameters:
//
//     nID          ID of the gadget
//     lParam       depends on uNotifyCode
//     uNotifyCode  GXDT_GN_SPINUP    Increment by the amount defined in lParam
//                  GXDT_GN_SPINDOWN  Decrement by the amount defined in lParam
//                  GXDT_GN_INCREMENT Increment by one (lParam undefined)
//                  GXDT_GN_DECREMENT Decrement by one (lParam undefined)
//                  GXDT_GN_MINIMUM   Move to the minimum value (lParam undefined)
//                  GXDT_GN_MAXIMUM   Move to the maximum value (lParam undefined)
//                  GXDT_GN_VALIDATE  Validate the value defined in lParam
//                  GXDT_GN_MODIFY    Validate and commit the value defined in lParam
//
//   For all of these notify codes, the function returns TRUE if successful,
//   otherwise FALSE.
//


//---------------------------------------------------------------------------
//  ChangeHour
//
//  Changes the value of hour depending on uNotifyCode
//
BOOL CGXBDateTimeCtrl::ChangeHour(UINT uNotifyCode, int nID, LPARAM lParam)
{
	COleDateTime temp;
	struct tm    tmTemp;
	int          nValidationType = 2;
	int          nInc            = 1;
	int			 nLParam		 = int(lParam);

	// Extract the current date/time into the tm structure tmTemp
	if(!GXBGetTmFromOleDate(m_datetime, tmTemp))
	{
		ASSERT(0);
		return FALSE;
	}
	
	switch(uNotifyCode)
	{
	case GXDT_GN_SPINUP:
		// A spin event, decode the increment (note the maximum of 2)
		//nInc = min(2, lParam);
		nInc = min(2, nLParam);

		// Fall through ...

	case GXDT_GN_INCREMENT:
		/*$$
		// Increment the hour wrapping as necessary
		tmTemp.tm_hour += nInc;
		if(tmTemp.tm_hour > 23)
			tmTemp.tm_hour = 0;
		break;*/

		// Increment the hour wrapping as necessary
		if(tmTemp.tm_hour == -1)
			tmTemp.tm_hour = COleDateTime::GetCurrentTime().GetHour();
		else
		{
			tmTemp.tm_hour += nInc;
			if(tmTemp.tm_hour > 23)
				tmTemp.tm_hour = 0;
		}
		break;

	case GXDT_GN_SPINDOWN:
		// A spin event, decode the decrement (note the maximum of 2)
//		nInc = min(2, lParam);
		nInc = min(2, nLParam);

		// Fall through ...

	case GXDT_GN_DECREMENT:
/* $$	
		// Decrement the hour wrapping as necessary.
		tmTemp.tm_hour -= nInc;
		if(tmTemp.tm_hour < 0)
			tmTemp.tm_hour = 23;
		break;
*/
		// Decrement the hour wrapping as necessary.
		if(tmTemp.tm_hour == -1)
			tmTemp.tm_hour = COleDateTime::GetCurrentTime().GetHour();
		else
		{
			tmTemp.tm_hour -= nInc;
			if(tmTemp.tm_hour < 0)
				tmTemp.tm_hour = 23;
		}
		break;


	case GXDT_GN_MINIMUM:
		// Move to the minimum hour
		tmTemp.tm_hour  = 0;
		nValidationType = 3;
		break;

	case GXDT_GN_MAXIMUM:
		// Move to the maximum hour
		tmTemp.tm_hour  = 23;
		nValidationType = 3;
		break;

	case GXDT_GN_VALIDATE:
	case GXDT_GN_MODIFY:
		// Validate/modify a new value
		if(nID == GXDT_DTID_12HOUR)
		{
/*$$
			// 12 hour clock requires work to bring it into 24 hour format
			if(!(lParam >= 1 && lParam <= 12))
				return FALSE;

			// Need to modify it back into 24 hour clock format
			if(tmTemp.tm_hour >= 12)					// pm
			{
				if(lParam != 12)				// Exclude 12pm which is midday
					lParam += 12;
			}
			else if(lParam == 12)
				// 12 am is midnight
				lParam = 0;
*/
			// 12 hour clock requires work to bring it into 24 hour format
			//if(!(lParam >= 1 && lParam <= 12))
			if(!(nLParam >= 1 && nLParam <= 12))
				return FALSE;

			// Convert 12-hour (1-12) to 24 hour (0-23)
			if(IsHourPM())
				//lParam+=12;
				nLParam+=12;
			//if(lParam>23) 
			if(nLParam>23) 
				//lParam=0;
				nLParam=0;
		}
		//else if(!(lParam >= 0 && lParam <= 23))
		else if(!(nLParam >= 0 && nLParam <= 23))
			return FALSE;

		//tmTemp.tm_hour = int(lParam);
		tmTemp.tm_hour = nLParam;

		break;
	}

	// Validate the new time
	temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, tmTemp.tm_mday, 
					 tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec);
	if(!Validate(temp, nValidationType))
		return FALSE;						// Failure ...

	if(uNotifyCode == GXDT_GN_VALIDATE)
		// We are only validating, so nothing further to do.
		return TRUE;

	// You override on changing to perform additional validation
	if(!OnChanging(temp))
		return FALSE;

	// Update gadgets to show new hour
	UpdateGadgets(temp);
	m_nState |= DateModified;

	// Inform parent we have changed
	OnChanged();

	UpdateWindow();

	return TRUE;
}

//---------------------------------------------------------------------------
//  ChangeMinute
//
//  Changes the value of minute depending on uNotifyCode
//
BOOL CGXBDateTimeCtrl::ChangeMinute(UINT uNotifyCode, int /* nID */, LPARAM lParam)
{
	COleDateTime temp;
	struct tm    tmTemp;
	int          nValidationType = 1;
	int          nInc            = 1;
	int			 nLParam		 = int(lParam);

	// Extract the current date/time into the tm structure tmTemp
	if(!GXBGetTmFromOleDate(m_datetime, tmTemp))
	{
		ASSERT(0);
		return FALSE;
	}

	switch(uNotifyCode)
	{
	case GXDT_GN_SPINUP:
		// A spin event, decode the increment (note the maximum of 2)
		//nInc = min(2, lParam);
		nInc = min(2, nLParam);

		// Fall through ...

	case GXDT_GN_INCREMENT:
/* $$		
		// Increment the minute wrapping as necessary
		tmTemp.tm_min += nInc;
		if(tmTemp.tm_min > 59)
			tmTemp.tm_min = 0;
		break;
*/
		// Increment the minute wrapping as necessary
		if(tmTemp.tm_min == -1)
			tmTemp.tm_min = COleDateTime::GetCurrentTime().GetMinute();
		else
		{
			tmTemp.tm_min += nInc;
			if(tmTemp.tm_min > 59)
				tmTemp.tm_min = 0;
		}
		break;

	case GXDT_GN_SPINDOWN:
		// A spin event, decode the decrement (note the maximum of 2)
		//nInc = min(2, lParam);
		nInc = min(2, nLParam);

		// Fall through ...

	case GXDT_GN_DECREMENT:
/* $$		
		// Decrement the minute wrapping as necessary
		tmTemp.tm_min -= nInc;
		if(tmTemp.tm_min < 0)
			tmTemp.tm_min = 59;
		break;
*/
		// Decrement the minute wrapping as necessary
		if(tmTemp.tm_min == -1)
			tmTemp.tm_min = COleDateTime::GetCurrentTime().GetMinute();
		else
		{
			tmTemp.tm_min -= nInc;
			if(tmTemp.tm_min < 0)
				tmTemp.tm_min = 59;
		}
		break;

	case GXDT_GN_MINIMUM:
		// Move to the lowest valid minute
		tmTemp.tm_min   = 0;
		nValidationType = 2;
		break;

	case GXDT_GN_MAXIMUM:
		// Move to the highest valid minute
		tmTemp.tm_min   = 59;
		nValidationType = 2;
		break;

	case GXDT_GN_VALIDATE:
	case GXDT_GN_MODIFY:
		// Validate/modify the minute field to the new value
		//if(!(lParam >= 0 && lParam <= 59))
		if(!(nLParam >= 0 && nLParam <= 59))
			return FALSE;

		//tmTemp.tm_min = int(lParam);
		tmTemp.tm_min = nLParam;
		break;
	}

	// Validate the new time
	temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, tmTemp.tm_mday, 
					 tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec);
	if(!Validate(temp, nValidationType))
		return FALSE;							// Failure ...

	if(uNotifyCode == GXDT_GN_VALIDATE)
		// We are only validating, so nothing further to do.
		return TRUE;

	// You override on changing to perform additional validation
	if(!OnChanging(temp))
		return FALSE;

	// Update gadgets to show new minute
	UpdateGadgets(temp);
	m_nState |= DateModified;

	// Inform parent that we have changed
	OnChanged();

	UpdateWindow();

	return TRUE;
}

//---------------------------------------------------------------------------
//  ChangeSecond
//
//  Changes the value of seconds depending on uNotifyCode
//
BOOL CGXBDateTimeCtrl::ChangeSecond(UINT uNotifyCode, int /* nID */, LPARAM lParam)
{
	COleDateTime temp;
	struct tm    tmTemp;
	int          nValidationType = 0;
	int          nInc            = 1;
	int			 nLParam		 = int(lParam);

	// Extract the current date/time into the tm structure tmTemp
	if(!GXBGetTmFromOleDate(m_datetime, tmTemp))
	{
		ASSERT(0);
		return FALSE;
	}

	switch(uNotifyCode)
	{
	case GXDT_GN_SPINUP:
		// A spin event, decode the increment (note the maximum of 2)
		//nInc = min(2, lParam);
		nInc = min(2, nLParam);

		// Fall through ...

	case GXDT_GN_INCREMENT:
/*
		// Increment the seconds wrapping as necessary
		tmTemp.tm_sec += nInc;
		if(tmTemp.tm_sec > 59)
			tmTemp.tm_sec = 0;
		break;
*/
		// Increment the seconds wrapping as necessary
		if(tmTemp.tm_sec == -1)
			tmTemp.tm_sec = COleDateTime::GetCurrentTime().GetSecond();
		else
		{
			tmTemp.tm_sec += nInc;
			if(tmTemp.tm_sec > 59)
				tmTemp.tm_sec = 0;
		}
		break;

	case GXDT_GN_SPINDOWN:
		// A spin event, decode the decrement (note the maximum of 2)
		//nInc = min(2, lParam);
		nInc = min(2, nLParam);

		// Fall through ...

	case GXDT_GN_DECREMENT:
/* $$
		// Decrement the seconds wrapping as necessary
		tmTemp.tm_sec -= nInc;
		if(tmTemp.tm_sec < 0)
			tmTemp.tm_sec = 59;
		break;
*/
		// Decrement the seconds wrapping as necessary
		if(tmTemp.tm_sec == -1)
			tmTemp.tm_sec = COleDateTime::GetCurrentTime().GetSecond();
		else
		{
			tmTemp.tm_sec -= nInc;
			if(tmTemp.tm_sec < 0)
				tmTemp.tm_sec = 59;
		}
		break;

	case GXDT_GN_MINIMUM:
		// Set seconds to it's lowest possible value
		tmTemp.tm_sec   = 0;
		nValidationType = 1;
		break;

	case GXDT_GN_MAXIMUM:
		// Set seconds to it's highest possible value
		tmTemp.tm_sec   = 59;
		nValidationType = 1;
		break;

	case GXDT_GN_VALIDATE:
	case GXDT_GN_MODIFY:
		// Validate/modify the seconds to the specified value
		//if(!(lParam >= 0 && lParam <= 59))
		if(!(nLParam >= 0 && nLParam <= 59))
			return FALSE;

		//tmTemp.tm_sec = int(lParam);
		tmTemp.tm_sec = nLParam;
		break;
	}

	// Validate the new time
	temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, tmTemp.tm_mday, 
					 tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec);
	if(!Validate(temp, nValidationType))
		return FALSE;						// Failure ...

	if(uNotifyCode == GXDT_GN_VALIDATE)
		// We are only validating, so nothing further to do.
		return TRUE;

	// You override on changing to perform additional validation
	if(!OnChanging(temp))
		return FALSE;

	// Update gadgets to show new second
	UpdateGadgets(temp);
	m_nState |= DateModified;

	// Inform parent that we have changed
	OnChanged();

	UpdateWindow();

	return TRUE;
}

//---------------------------------------------------------------------------
//  ChangeAmPm
//
//  Changes the value of Am/Pm depending on uNotifyCode
//
BOOL CGXBDateTimeCtrl::ChangeAmPm(UINT uNotifyCode, int /* nID */, LPARAM lParam)
{
	COleDateTime temp;
	struct tm    tmTemp;
	int          nValidationType = 2;

	// Extract the current date/time into the tm structure tmTemp
	if(!GXBGetTmFromOleDate(m_datetime, tmTemp))
	{
		ASSERT(0);
		return FALSE;
	}

	switch(uNotifyCode)
	{
	case GXDT_GN_SPINDOWN:
	case GXDT_GN_SPINUP:
	case GXDT_GN_INCREMENT:
	case GXDT_GN_DECREMENT:
		// As we only have two possible values, both spin and inc/dec events
		// cause us to toggle am/pm
/* $$
		if(tmTemp.tm_hour < 12)
			tmTemp.tm_hour += 12;
		else
			tmTemp.tm_hour -= 12;

		break;
*/
		if(tmTemp.tm_hour == -1)
			tmTemp.tm_hour = 0;
		else if(tmTemp.tm_hour < 12)
			tmTemp.tm_hour += 12;
		else
			tmTemp.tm_hour -= 12;

		break;


	case GXDT_GN_MINIMUM:
/* $$
		// Move to am
		if(tmTemp.tm_hour < 12)
			return TRUE;				// Already at Am so nothing to do

		tmTemp.tm_hour -= 12;
		break;
*/
		// Move to am
		if(tmTemp.tm_hour == -1)
			tmTemp.tm_hour = 0;
		else if(tmTemp.tm_hour < 12)
			return TRUE;				// Already at Am so nothing to do
		else
			tmTemp.tm_hour -= 12;
		break;

	case GXDT_GN_MAXIMUM:
/* $$
		// Move to pm
		if(tmTemp.tm_hour >= 12)
			return TRUE;				// Already at Pm so nothing to do

		tmTemp.tm_hour += 12;
		break;
*/
		// Move to pm
		if(tmTemp.tm_hour == -1)
			tmTemp.tm_hour = 23;
		else if(tmTemp.tm_hour >= 12)
			return TRUE;				// Already at Pm so nothing to do
		else
			tmTemp.tm_hour += 12;
		break;

	case GXDT_GN_VALIDATE:
	case GXDT_GN_MODIFY:
		// Validate/Modify a new am/pm value
		if(lParam == 1 && tmTemp.tm_hour < 12)
			tmTemp.tm_hour += 12;
		else if(lParam == 0 && tmTemp.tm_hour >= 12)
			tmTemp.tm_hour -= 12;

		break;
	}

	// Set the am/pm internal storage
	if(tmTemp.tm_hour>11) m_bHourPM=TRUE;
	else				  m_bHourPM=FALSE;

	// Validate the new time
	temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, tmTemp.tm_mday, 
					 tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec);
	if(!Validate(temp, nValidationType))
		return FALSE;						// Failure ...

	if(uNotifyCode == GXDT_GN_VALIDATE)
		// We are only validating, so nothing further to do
		return TRUE;

	// You override on changing to perform additional validation
	if(!OnChanging(temp))
		return FALSE;

	// Update gadgets to show new am/pm value (and possible change in hours)
	UpdateGadgets(temp);
	m_nState |= DateModified;

	// Inform parent that we have changed.
	OnChanged();

	UpdateWindow();

	return TRUE;
}

//---------------------------------------------------------------------------
//  ChangeDay
//
//  Changes the value of day depending on uNotifyCode
//
BOOL CGXBDateTimeCtrl::ChangeDay(UINT uNotifyCode, int nID, LPARAM lParam)
{
	COleDateTime temp;
	struct tm    tmTemp;
	int          nValidationType = 3;
	int          nInc            = 1;
	int			 nLParam         = int(lParam);

	// Extract the current date/time into the tm structure tmTemp
	if(!GXBGetTmFromOleDate(m_datetime, tmTemp))
	{
		ASSERT(0);
		return FALSE;
	}

	switch(uNotifyCode)
	{
	case GXDT_GN_SPINUP:
		// A spin event, decod the decrement (note the maximum of 2)
		//nInc = min(2, lParam);
		nInc = min(2, nLParam);

		// Fall through ...

	case GXDT_GN_INCREMENT:

		// Increment the day, wrapping as necessary
		tmTemp.tm_mday += nInc;
		if(temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, tmTemp.tm_mday, 
							tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec))
			// Have exceeded bounds on month ... wrap back to day 1
			tmTemp.tm_mday = 1;

		break;

	case GXDT_GN_SPINDOWN:
		// A spin event, decode the decrement (note the maximum of 2)
		//nInc = min(2, lParam);
		nInc = min(2, nLParam);
		
		// Fall through ...

	case GXDT_GN_DECREMENT:
	
		// Decrement the day, wrapping as necessary
		tmTemp.tm_mday -= nInc;
		if(tmTemp.tm_mday < 1)
			tmTemp.tm_mday = 31;

		break;

	case GXDT_GN_MINIMUM:
		// Move to the first valid day of this month or week
		if(nID == GXDT_DTID_DAYNAME)
		{
			// Reduce by required number of days to get to first day of
			// week
			int nDiff = tmTemp.tm_wday - 1;
			temp  = m_datetime;
			temp -= COleDateTimeSpan(nDiff, 0, 0, 0);
			if(temp.GetStatus() != COleDateTime::valid)
				return FALSE;

			// Extract new date information
			GXBGetTmFromOleDate(temp, tmTemp);
		}
		else
			// Move to first day of month
			tmTemp.tm_mday  = 1;
		
		nValidationType = 4;
		break;

	case GXDT_GN_MAXIMUM:
		// Move to the last valid day of this month or week

		if(nID == GXDT_DTID_DAYNAME)
		{
			// Increase by the required number of days to reach each of week
			int nDiff = 7 - tmTemp.tm_wday;
			temp  = m_datetime;
			temp += COleDateTimeSpan(nDiff, 0, 0, 0);
			if(temp.GetStatus() != COleDateTime::valid)
				return FALSE;

			GXBGetTmFromOleDate(temp, tmTemp);
		}
		else
			// Move to end of month (Validate will take care of wrapping this
			// to a valid value)
			tmTemp.tm_mday  = 31;

		nValidationType = 4;
		break;

	case GXDT_GN_VALIDATE:
	case GXDT_GN_MODIFY:

		// Validate/modify the given day of month or week
		if(nID == GXDT_DTID_DAYNAME)
		{
			// Day of week, convert to day of month.
			temp = m_datetime;
			//lParam++;
			nLParam++;
			int nDayOfWeek = tmTemp.tm_wday;
			//int nInc = (nDayOfWeek < lParam) ? 1 : -1;
			int nInc = (nDayOfWeek < nLParam) ? 1 : -1;
			COleDateTimeSpan oneDay(1, 0, 0, 0);

			//for(; lParam != nDayOfWeek; nDayOfWeek += nInc)
			for(; nLParam != nDayOfWeek; nDayOfWeek += nInc)
			{
				if(nInc > 0)
					temp += oneDay;
				else
					temp -= oneDay;
			}

			if(temp.GetStatus() != COleDateTime::valid)
				return FALSE;

			GXBGetTmFromOleDate(temp, tmTemp);
		}
		else if(!temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, int(lParam),
								  tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec))
			// Day of month (valid)
			//tmTemp.tm_mday = int(lParam);
			tmTemp.tm_mday = int(nLParam);
		else
			// Exceeds bounds, so is invalid!
			return FALSE;

		break;
	}

	// Validate the new date
	if(temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, tmTemp.tm_mday, 
						tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec))
	{
		// Invalid, check to see if it is the day which is out of range
		while(tmTemp.tm_mday > 28)
		{
			// Attempt to bring the day back into range
			tmTemp.tm_mday--;
			if(!temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, tmTemp.tm_mday, 
								 tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec))
				break;
		}

		if(temp.GetStatus() != COleDateTime::valid)
			// Could not bring it back into range, so give up.
			return FALSE;
	}

	// Validate the new date
	if(!Validate(temp, nValidationType))
		return FALSE;						// Failure ...

	if(uNotifyCode == GXDT_GN_VALIDATE)
		// We are only validating, so nothing further to do.
		return TRUE;

	// You override OnChanging to perform additional validation
	if(!OnChanging(temp))
		return FALSE;

	// Updates gadgets to show new day of month/week
	UpdateGadgets(temp);
	m_nState |= DateModified;

	// Inform parent we have changed.
	OnChanged();

	UpdateWindow();

	return TRUE;
}

//---------------------------------------------------------------------------
//  ChangeMonth
//
//  Changes the value of month depending on uNotifyCode
//
BOOL CGXBDateTimeCtrl::ChangeMonth(UINT uNotifyCode, int nID, LPARAM lParam)
{
	COleDateTime temp;
	struct tm    tmTemp;
	int          nValidationType = 4;

	// Extract the current date/time into the tm structure tmTemp
	if(!GXBGetTmFromOleDate(m_datetime, tmTemp))
	{
		ASSERT(0);
		return FALSE;
	}

	switch(uNotifyCode)
	{
	case GXDT_GN_SPINUP:
	case GXDT_GN_INCREMENT:

		// Increment the month (by 1) wrapping as necessary
		// $$ Included this if
		if(tmTemp.tm_mon == -1)
			tmTemp.tm_mon = COleDateTime::GetCurrentTime().GetMonth();
		else if(tmTemp.tm_mon == 12)
			tmTemp.tm_mon = 1;
		else
			tmTemp.tm_mon++;

		break;

		
	case GXDT_GN_SPINDOWN:
	case GXDT_GN_DECREMENT:
		
		// Decrement the month (by 1) wrapping as necessary
		// $$ Included this if
		if(tmTemp.tm_mon == -1)
			tmTemp.tm_mon = COleDateTime::GetCurrentTime().GetMonth();
		else if(tmTemp.tm_mon == 1)
			tmTemp.tm_mon = 12;
		else
			tmTemp.tm_mon--;

		break;

	case GXDT_GN_MINIMUM:
		// Move to lowest valid month
		tmTemp.tm_mon   = 1;
		nValidationType = 5;
		break;

	case GXDT_GN_MAXIMUM:
		// Move to highest valid month
		tmTemp.tm_mon   = 12;
		nValidationType = 5;
		break;

	case GXDT_GN_VALIDATE:
	case GXDT_GN_MODIFY:
		// Validate/modify month
		if(nID == GXDT_DTID_MONTHNAME)
			// Bring month name index to valid month value
			lParam++;
		else if(!(lParam >= 1 && lParam <= 12))
			return FALSE;

		tmTemp.tm_mon = int(lParam);
		break;
	}

	// Validate the new date
	if(temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, tmTemp.tm_mday, 
						tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec))
	{
		// Invalid, check to see if it is the day which is out of range
		while(tmTemp.tm_mday > 28)
		{
			// Try and bring the day back into range.
			tmTemp.tm_mday--;
			if(!temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, tmTemp.tm_mday, 
								 tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec))
				break;
		}

		if(temp.GetStatus() != COleDateTime::valid)
			// Unable to bring it back into range, so failure.
			return FALSE;
	}

	if(!Validate(temp, nValidationType))
		// Not a valid date ....
		return FALSE;

	if(uNotifyCode == GXDT_GN_VALIDATE)
		// We are only validating, so nothing further to do.
		return TRUE;

	// You override OnChanging to perform additional validation
	if(!OnChanging(temp))
		return FALSE;

	// Update gadgets to show new hour
	UpdateGadgets(temp);
	m_nState |= DateModified;

	// Inform parent we have changed
	OnChanged();

	UpdateWindow();

	return TRUE;
}

//---------------------------------------------------------------------------
//  ChangeYear
//
//  Changes the value of year depending on uNotifyCode.
//
BOOL CGXBDateTimeCtrl::ChangeYear(UINT uNotifyCode, int nID, LPARAM lParam)
{
	COleDateTime temp;
	struct tm    tmTemp;
	int          nValidationType = 5;
	int          nInc            = 1;

	// Extract the current date/time into the tm structure tmTemp
	if(!GXBGetTmFromOleDate(m_datetime, tmTemp))
	{
		ASSERT(0);
		return FALSE;
	}

	switch(uNotifyCode)
	{
	case GXDT_GN_SPINUP:
		// A spin event, decode the increment
		nInc = int(lParam);

		// Fall through ...

	case GXDT_GN_INCREMENT:
		// Increment the year.
		// $$ inlcuded this if
		if(tmTemp.tm_year == -1)
			tmTemp.tm_year = COleDateTime::GetCurrentTime().GetYear();
		else
		{
			tmTemp.tm_year += nInc;
			tmTemp.tm_year = min(tmTemp.tm_year, 9999);
		}
		break;

	case GXDT_GN_SPINDOWN:
		// A spin event, decode the decrement
		nInc = int(lParam);

		// Fall through ...

	case GXDT_GN_DECREMENT:
		// Decrement the year.
		// $$ inlcuded this if
		if(tmTemp.tm_year == -1)
			tmTemp.tm_year = COleDateTime::GetCurrentTime().GetYear();
		else
		{
			tmTemp.tm_year -= nInc;
			tmTemp.tm_year = max(tmTemp.tm_year, 100);
		}
		break;

	case GXDT_GN_MINIMUM:
		// Move to the lowest possible year
		tmTemp.tm_year  = m_datetimeMin.GetYear();
		break;

	case GXDT_GN_MAXIMUM:
		// Move to the highest possible year
		tmTemp.tm_year  = m_datetimeMax.GetYear();
		break;

	case GXDT_GN_VALIDATE:
	case GXDT_GN_MODIFY:
		// Validate/Modify a new year
		if(nID == GXDT_DTID_YEAR2)
		{

			// Pre-Y2K fix implementation (for backward compatibility)
			if (GetStyle() & GXDT_DTS_Y2K_NOFIX) 
			{
				if(tmTemp.tm_year == -1)
				{
					// What is the right thing to do with the century?
					// We'll use the current century...
					SYSTEMTIME st;
					GetSystemTime(&st);
					lParam += ((int)st.wYear/100) * 100;
				}
				else
				{
					// Add stored century to 2 digit years.
					lParam += (tmTemp.tm_year/100) * 100;
				}
			}

			// else, determine century, accounting for year 2000+
			else 
			{				
				lParam += GetCentury((int)lParam);
			}
		}

		tmTemp.tm_year = int(lParam);
		break;
	}

	// Validate the new date
	if(temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, tmTemp.tm_mday, 
						tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec))
	{
		// Invalid, check to see if it is the day which is out of range
		while(tmTemp.tm_mday > 28)
		{
			// Attempt to bring the day back into range.
			tmTemp.tm_mday--;
			if(!temp.SetDateTime(tmTemp.tm_year, tmTemp.tm_mon, tmTemp.tm_mday, 
								 tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec))
				break;
		}

		if(temp.GetStatus() != COleDateTime::valid)
			// Could not bring it back into range.
			return FALSE;
	}

	if(!Validate(temp, nValidationType))
		// New date is invalid ...
		return FALSE;

	if(uNotifyCode == GXDT_GN_VALIDATE)
		// We are only validating, so nothing further to do.
		return TRUE;

	// You override OnChanging to perform additional validation
	if(!OnChanging(temp))
		return FALSE;

	// Update gadgets to show new year.
	UpdateGadgets(temp);
	m_nState |= DateModified;

	// Inform parent we have changed.
	OnChanged();

	UpdateWindow();

	return TRUE;
}

//---------------------------------------------------------------------------
//  GetCentury
//
// Inferencing rule: The control uses COleDateTime's inferencing rule, which as of now
// (in OLEAUT32.DLL version 2.20.4049; 1999)
// uses 1930 as the pivot year, meaning 2 digit years < 30 are interpreted as belonging to the 21st century
// while 2 digit years >= 30 are interpreted as belonging to the 20th century.
// This behavior will hence change if Microsoft modifies this "sliding window" behavior in a later version of oleaut32.dll.
//
// Override this method for application specific date contexts.
//
int CGXBDateTimeCtrl::GetCentury(int n2DigitYear)
{
	COleDateTime dt;
	CString strDate;
	CString str2DigitYear;
	str2DigitYear.Format(_T("%d"), n2DigitYear);
	
	// First determine the locale setting by formatting a dummy date into a string
	dt.SetDate(1999, 1, 1);		
	strDate = dt.Format();

	TCHAR* str2DigitYDate = NULL;

	str2DigitYDate = gx_str_replace(strDate, _T("1999"), str2DigitYear);
	if(str2DigitYDate == NULL)
		str2DigitYDate = gx_str_replace(strDate, _T("99"), str2DigitYear);
	ASSERT(str2DigitYDate != NULL);
			// ASSERTION -> This logic assumes the short date representation in the current locale
			// has either yy(2 digit year) or yyyy (4 digit year).
			// If not override this function and modify the logic.

	dt.ParseDateTime(str2DigitYDate);
	if(str2DigitYDate)
		delete [] str2DigitYDate;

	ASSERT(dt.GetStatus() == COleDateTime::valid);
		// See the above ASSERTION description.

	// Return the century.
	return dt.GetYear()-n2DigitYear;
}


// We maintain a list mapping outstanding timers to gadget controls
CMapWordToOb CGXBDTGadget::m_timers;


/////////////////////////////////////////////////////////////////////////////
// CGXBDTGadget - construction
//
IMPLEMENT_DYNAMIC(CGXBDTGadget, CObject)

CGXBDTGadget::CGXBDTGadget()
{
	m_pCtrl    = NULL;
	m_bEnabled = FALSE;
	m_nID      = -1;
	m_nValue   = 0;
	m_style    = WantFocus;
}

CGXBDTGadget::~CGXBDTGadget()
{
	// Just in case
	StopTimer();
}

//---------------------------------------------------------------------------
// Initialise
//
// Initialises the gadget
//
BOOL CGXBDTGadget::Initialise(CGXBDateTimeCtrl* pCtrl, int nID /* = -1 */)
{
	m_pCtrl = pCtrl;
	m_nID   = nID;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDTGadget - operations
//

//---------------------------------------------------------------------------
// GetStyle
//
// Returns the current gadget style
//
int CGXBDTGadget::GetStyle() const
{
	return m_style;
}

//---------------------------------------------------------------------------
// SetStyle
//
// Sets the current gadget style
//
void CGXBDTGadget::SetStyle(int style)
{
	m_style = style;
}

//---------------------------------------------------------------------------
// SetValue
//
// Sets the current gadget value
//
void CGXBDTGadget::SetValue(int nNewValue)
{
	m_nValue = nNewValue;
}

//---------------------------------------------------------------------------
// GetValue
//
// Returns the current gadget value
//
int CGXBDTGadget::GetValue() const
{
	return m_nValue;
}

//---------------------------------------------------------------------------
// GetID
//
// Returns the gadget ID
//
int CGXBDTGadget::GetID() const
{
	return m_nID;
}

//---------------------------------------------------------------------------
// GetRect
//
// Returns the gadget's rectangle (this is relative to the CGXBDateTimeCtrl's
// client).
//
const CRect& CGXBDTGadget::GetRect() const
{
	return m_rect;
}

//---------------------------------------------------------------------------
// SetRect
//
// Sets the gadget's rectangle (this is relative to the CGXBDateTimeCtrl's
// client).
//
void CGXBDTGadget::SetRect(const RECT& rect)
{
	m_rect = rect;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDTGadget - overrideables
//

//---------------------------------------------------------------------------
// Enable
//
// Enable/Disable the gadget. This is effectively giving focus to the gadget
// - only one gadget can be enabled at any one time.
//
BOOL CGXBDTGadget::Enable(BOOL bEnable)
{
	if(!(m_style & WantFocus))
		// We're don't want focus
		return FALSE;

	if(bEnable != m_bEnabled)
	{
		// Change of enabled state
		m_bEnabled = bEnable;
		Invalidate();
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDTGadget - implementation
//

//---------------------------------------------------------------------------
// Notify
//
// Passes a notify event onto our parent CGXBDateTimeCtrl.
//
BOOL CGXBDTGadget::Notify(UINT uNotifyCode, int nID, LPARAM lParam /* = 0L */)
{
	return m_pCtrl->OnNotify(uNotifyCode, nID, lParam);
}

//---------------------------------------------------------------------------
// Invalidate
//
// Tells our parent CGXBDateTimeCtrl that we want to be invalidated
//
void CGXBDTGadget::Invalidate(BOOL bImmediateRedraw /* = FALSE */)
{
	m_pCtrl->InvalidateGadget(this, bImmediateRedraw);
}

//---------------------------------------------------------------------------
// SetCapture
//
// Tells our parent CGXBDateTimeCtrl that we require mouse capture
//
void CGXBDTGadget::CaptureMouse(BOOL bSet)
{
	m_pCtrl->CaptureMouse(this, bSet);
}

COLORREF CGXBDTGadget::GetBkColor() const
{
	return m_pCtrl->m_cBkColor; 
}
//---------------------------------------------------------------------------
// StartTimer
//
// Sets a repetative timer event for this Gadget. This is implemented by
// setting a timer with a callback function. We then maintain a mapping list
// of outstanding timer IDs to gadgets.
//
// Note that each gadget object can only ever have one timer outstanding.
//
void CGXBDTGadget::StartTimer(UINT uElapse /* ms */)
{
	TIMERPROC lpfnTimerProc = 
		(TIMERPROC) MakeProcInstance((FARPROC) TimerProc, 
									 AfxGetInstanceHandle());

	WORD wID = (WORD)::SetTimer(NULL, 1, uElapse, lpfnTimerProc);
	if(wID > 0)
		// Timer set successfully, so add it to the list of timers
		m_timers.SetAt(wID, this);
}

//---------------------------------------------------------------------------
// StopTimer
//
// Terminates any timer associated with the current gadget.
//
void CGXBDTGadget::StopTimer()
{
	// Look up this timer in our mapping table
	POSITION pos = m_timers.GetStartPosition();
	while(pos != NULL)
	{
		WORD wID;
		CGXBDTGadget* pGadget;
		m_timers.GetNextAssoc(pos, wID, (CObject*&) pGadget);
		if(pGadget == this)
		{
			KillTimer(NULL, wID);
			VERIFY(m_timers.RemoveKey(wID));
			return;
		}
	}
}

//---------------------------------------------------------------------------
// TimerProc
//
// Timer callback function. Passes the event onto the associated gadget
//
void CALLBACK AFX_EXPORT CGXBDTGadget::TimerProc(HWND /* hWnd */, UINT /* nMsg */, 
											UINT nIDEvent, DWORD /* dwTime */)
{
	CGXBDTGadget* pGadget;
	if(m_timers.Lookup(WORD(nIDEvent), (CObject*&) pGadget))
		pGadget->OnTimer();
}





CGXBDTSpinGadget::CGXBDTSpinGadget()
{
	m_style  = WantMouse;
	m_nState = 0;
	m_nTimer = 0;
}

CGXBDTSpinGadget::~CGXBDTSpinGadget()
{
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDTSpinGadget - overrideables
//

//---------------------------------------------------------------------------
//  CalcSize
//
//  Sets m_rect to the required size of the spin button.
//
void CGXBDTSpinGadget::CalcSize(CDC& /* dc */)
{
	m_rect.SetRectEmpty();

	m_rect.right  = 16;
	m_rect.bottom = -1;			// CGXBDateTimeCtrl will set our height to
								// the height of it's client rectangle
}

//---------------------------------------------------------------------------
//  Draw
//
//  Draws the spin button component (bound by m_rect)
//
void CGXBDTSpinGadget::Draw(CDC& dc)
{
	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive()) 
		// Note: If we use dc.GetWindow()->m_hWnd we do not get a valid window
		// handle. Instead we use AfxGetMainWnd()->GetSafeHwnd().
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"SPIN");	
	
	dc.FillSolidRect(m_rect, GXGetSysData()->clrBtnFace);

	// Select pens/brushes for drawing arrows
	HGDIOBJ hOldPen   = dc.SelectObject(::GetStockObject(BLACK_PEN));
	HGDIOBJ hOldBrush = dc.SelectObject(::GetStockObject(BLACK_BRUSH));

	// Split the button into two parts (spin up button/spin down button)
	int nHeight = m_rect.Height()/2;

	// Draw the spin up button
	CRect r = m_rect;
	r.bottom = r.top + nHeight;

	if (lhTheme)
	{
		int iState = UPS_NORMAL;
		if (m_nState & SpinUp) iState = UPS_PRESSED;	

		RWDrawThemeBackground (lhTheme, dc.GetSafeHdc(), SPNP_UP, iState, &r, 0 );			
	}
	else
	{
		DrawPart(dc, r, FALSE, m_nState & SpinUp);
	}

	// Draw the spin down button
	r = m_rect;
	r.top = r.bottom - nHeight;

	if (lhTheme)
	{
		int iState = UPS_NORMAL;		
		if (m_nState & SpinDown) iState = UPS_PRESSED;				

		RWDrawThemeBackground (lhTheme, dc.GetSafeHdc(), SPNP_DOWN, iState, &r, 0 );			
	}
	else
	{
		DrawPart(dc, r, TRUE, m_nState & SpinDown);
	}


	dc.SelectObject(hOldBrush);
	dc.SelectObject(hOldPen);

	if (lhTheme) RWCloseThemeData (lhTheme);
}

//---------------------------------------------------------------------------
//  OnLButtonDown
//
//  Handles WM_LBUTTONDOWN messages for this gadget
//
void CGXBDTSpinGadget::OnLButtonDown(UINT /* nFlags */, CPoint point)
{
	// Determine which button the hit occured over
	int nHit = CheckHit(point);
	ASSERT(nHit != -1);
	if(nHit == -1)
		// Didn't hit on either button
		return;

	// As soon as one of the spin buttons have been pressed we fire a spin
	// event to the CGXBDateTimeCtrl to force it to increment the current field
	if(nHit == 0)					// Spin up
	{
		m_nState &= ~(CaptureDown|SpinDown);
		m_nState |= (CaptureUp|SpinUp);

		Notify(GXDT_GN_SPINUP, m_nID, 1);
	}
	else							// Spin down
	{
		m_nState &= ~(CaptureUp|SpinUp);
		m_nState |= (CaptureDown|SpinDown);

		Notify(GXDT_GN_SPINDOWN, m_nID, 1);
	}

	// Force redraw to show pressed state
	Invalidate();

	// We need to capture mouse to detect when button is released
	CaptureMouse(TRUE);

	// We wait for a 500ms timer to expire before we perform next spin event
	// (then every 100ms).
	StartTimer(GetInitialTimerValue());

	m_nState |= (TimerRunning | InitialTimer);
	m_nTimer = 0;
}

//---------------------------------------------------------------------------
//  OnLButtonUp
//
//  Handle WM_LBUTTONUP messages for this gadget. 
//
void CGXBDTSpinGadget::OnLButtonUp(UINT /* nFlags */, CPoint /* point */)
{
	if(!(m_nState & (CaptureDown|CaptureUp)))
		// We're not tracking a button press so ignore.
		return;

	// We have now finished capture
	CaptureMouse(FALSE);

	// Redraw with button released (if it is currently pressed).
	if(m_nState & (SpinDown|SpinUp))
		Invalidate();

	m_nState &= ~(SpinDown|SpinUp|CaptureDown|CaptureUp);

	// Kill the timer if it was running
	if(m_nState & TimerRunning)
	{
		StopTimer();
		m_nState &= ~(TimerRunning | InitialTimer);
	}
}

//---------------------------------------------------------------------------
//  OnMouseMove
//
//  Handles WM_MOUSEMOVE messages.
//
void CGXBDTSpinGadget::OnMouseMove(UINT /* nFlags */, CPoint point)
{
	int nHit = CheckHit(point);
	if(m_nState & CaptureDown)
	{
		// We are tracking a press of the SpinDown button. see if the movement
		// will cause the button to toggle state
		if((nHit == 1 && !(m_nState & SpinDown)) ||
		   (nHit != 1 && (m_nState & SpinDown)))
		{
			m_nState ^= SpinDown;
			Invalidate();
		}
	}
	else if(m_nState & CaptureUp)
	{
		// We are tracking a press of the SpinUp button. see if the movement
		// will cause the button to toggle state
		if((nHit == 0 && !(m_nState & SpinUp)) ||
		   (nHit != 0 && (m_nState & SpinUp)))
		{
			m_nState ^= SpinUp;
			Invalidate();
		}
	}
	else
		// Not currently tracking anything, so ignore
		return;

	if(m_nState & (SpinUp|SpinDown))
	{
		if(!(m_nState & TimerRunning))
		{
			// A button has changed state to being down, we need setup a timer
			StartTimer(GetNormalTimerValue());
			m_nState |= TimerRunning;
			m_nState &= ~InitialTimer;
			m_nTimer = 0;
		}
	}
	else if(m_nState & InitialTimer)
	{
		//do nothing...
	}
	else if(m_nState & TimerRunning)
	{
		// We have no button down at the moment, so kill the spin timer.
		StopTimer();
		m_nState &= ~(TimerRunning | InitialTimer);
	}
}

//---------------------------------------------------------------------------
//  OnCancelMode
//
//  Handles the WM_CANCELMODE message - causes a reset of any state
//
void CGXBDTSpinGadget::OnCancelMode()
{
	if(!(m_nState & (CaptureDown|CaptureUp)))
		// Not currently tracking a button press, so ignore
		return;

	CaptureMouse(FALSE);

	if(m_nState & (SpinDown|SpinUp))
		Invalidate();

	m_nState &= ~(SpinDown|SpinUp|CaptureDown|CaptureUp);

	if(m_nState & TimerRunning)
	{
		StopTimer();
		m_nState &= ~(TimerRunning | InitialTimer);
	}
}

//---------------------------------------------------------------------------
//  OnTimer
//
//  Handles spin timer events. We have a 500ms timer (state flag InitialTimer)
//  initially, and there after 100ms timer events. Every event causes a spin
//  event to be passed onto the CGXBDateTimeCtrl.
//
void CGXBDTSpinGadget::OnTimer()
{
	ASSERT(m_nState & (SpinUp|SpinDown));

	if(m_nState & InitialTimer)
	{
		// Need to reset the 500ms timer to 1ms.
		StopTimer();
		StartTimer(GetNormalTimerValue());
		m_nState ^= InitialTimer;
	}

	// We have a form of acceleration. After 2 seconds we proceed to increments
	// of 2, and after 5 seconds we move to increments of 5.
	m_nTimer++;
	int nInc = 1;
	if(m_nTimer > 50)		// 5 seconds
		nInc = 5;
	else if(m_nTimer > 20)	// 2 seconds
		nInc = 2;

	// Pass on the spin event to the CGXBDateTimeCtrl.
	if(m_nState & SpinUp)
		Notify(GXDT_GN_SPINUP, m_nID, LPARAM(nInc));
	else
		Notify(GXDT_GN_SPINDOWN, m_nID, LPARAM(nInc));
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDTSpinGadget - implementation
//

//---------------------------------------------------------------------------
//  DrawPart
//
//  Draws either the spin down or spin up button.
//
void CGXBDTSpinGadget::DrawPart(CDC& dc, CRect& r, BOOL bInvert, BOOL bDown)
{
	// Draw the button borders.
	if(bDown)
	{
		// Button is currently pressed
		dc.Draw3dRect(r, GXGetSysData()->clrBtnShadow, GXGetSysData()->clrBtnHilite);
		r.DeflateRect(1, 1);
		dc.Draw3dRect(r, GXGetSysData()->clrWindowFrame, GXGetSysData()->clrBtnFace);
		r.DeflateRect(1, 1);
	}
	else
	{
		// Button is currently raised
		dc.Draw3dRect(r, GXGetSysData()->clrBtnFace, GXGetSysData()->clrWindowFrame);
		r.DeflateRect(1, 1);
		dc.Draw3dRect(r, GXGetSysData()->clrBtnHilite, GXGetSysData()->clrBtnShadow);
		r.DeflateRect(1, 1);
	}

	// Calculate the arrow dimensions. Note if bInvert is specificied, then
	// the arrow will be drawn upside down.
	int nArrowHeight = min(4, (r.Height()/4) + 1);
	int nArrowWidth  = nArrowHeight*2 - 1;
	int nLeft        = (r.Width() - nArrowWidth)/2 + r.left;
	int nTop         = bInvert ? (r.bottom - (r.Height() - nArrowHeight)/2 - 1)
							   : (r.top    + (r.Height() - nArrowHeight)/2);

	if(bDown)
		// Button is down, so offset arrow to give impression of movement
		nLeft++, nTop++;

	if(nArrowHeight > 1)
	{
		// Draw the arrow
		CPoint pts[3];
		pts[0].x = nLeft + (nArrowWidth-1)/2;
		pts[0].y = nTop;
		pts[1].x = nLeft + nArrowWidth - 1;
		pts[1].y = bInvert ? (nTop - nArrowHeight + 1) 
						   : (nTop + nArrowHeight - 1);
		pts[2].x = nLeft;
		pts[2].y = pts[1].y;

		dc.SetPolyFillMode(WINDING);
		dc.Polygon(pts, 3);
	}
	else
		// Face is too small to show arrow, so we just draw a single pixel
		dc.SetPixel(nLeft, nTop, RGB(0, 0, 0));
}

//---------------------------------------------------------------------------
// helper methods GetInitialTimerValue & GetNormalTimerValue
//
// Used to retrieve the timing info from parent CGXBDateTimeCtrl
// The info in set in the parent to give the user access for resetting 
// these values.
int CGXBDTSpinGadget::GetInitialTimerValue()
{
	return m_pCtrl->m_nInitialTimer;
}

int CGXBDTSpinGadget::GetNormalTimerValue()
{
	return m_pCtrl->m_nNormalTimer;
}

//---------------------------------------------------------------------------
//  CheckHit
//
//  Returns  0 if the given point is a hit on the Spin up button,
//           1 if it is a hit on the Spin down button,
//          -1 if it is a miss.
//
int CGXBDTSpinGadget::CheckHit(CPoint point) const
{
	if(!m_rect.PtInRect(point))
		return -1;

	int nHeight = m_rect.Height()/2;
	if(point.y <= (m_rect.top + nHeight))
		return 0;
	else
		return 1;
}

int _gxnMatchTimer = 2000;				// Timer to wait before reseting pattern
									// match state (in milli-seconds)

/////////////////////////////////////////////////////////////////////////////
// CGXBDTListGadget - construction
//
CGXBDTListGadget::CGXBDTListGadget()
{
	m_bTimerRunning = FALSE;

	memset(m_cBuf, 0, sizeof(m_cBuf));
}

CGXBDTListGadget::~CGXBDTListGadget()
{
}

//---------------------------------------------------------------------------
// Initialise
//
// Initialises the list gadget (defining string list and initial index)
//
BOOL CGXBDTListGadget::Initialise(CGXBDateTimeCtrl* pCtrl, 
								const CStringArray& list, int nValue, int nID)
{
	if(!CGXBDTGadget::Initialise(pCtrl, nID))
		return FALSE;

	m_nValue = nValue;
	m_list.Copy(list);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDTListGadget - overrideables
//

//---------------------------------------------------------------------------
// CalcSize
//
// Sets m_rect to the required size of the list gadget. This is the size of
// the longest string.
//
void CGXBDTListGadget::CalcSize(CDC& dc)
{
	m_rect.SetRectEmpty();

	// Determine the dimensions of the longest string.
	for(int i=0; i<m_list.GetSize(); i++)
	{
		CRect rect;
		rect.SetRectEmpty();
		dc.DrawText(m_list[i], -1, rect, DT_EXTERNALLEADING | DT_CALCRECT | 
					DT_SINGLELINE | DT_TOP | DT_LEFT | DT_NOPREFIX);

		if(rect.right > m_rect.right)
			m_rect.right = rect.right;
		if(rect.bottom > m_rect.bottom)
			m_rect.bottom = rect.bottom;
	}
}

//---------------------------------------------------------------------------
// Draw
//
// Draws the list component - the string at the current index centered within
// m_rect.
//
void CGXBDTListGadget::Draw(CDC& dc)
{

	// If we are enabled, then we highlight the current string
	if(m_bEnabled)
	{
		dc.SetTextColor(GXGetSysData()->clrHighlightText);
		dc.SetBkColor(GXGetSysData()->clrHighlight);
		dc.SetBkMode(OPAQUE);
	}

	// Draw the current string
	dc.DrawText(m_list[m_nValue], -1, m_rect, DT_SINGLELINE | DT_TOP | 
		        DT_CENTER | DT_NOPREFIX | DT_EXTERNALLEADING);


}

//---------------------------------------------------------------------------
// Enable
//
// Enables (sets focus) to this list gadget
//
BOOL CGXBDTListGadget::Enable(BOOL bEnable)
{
	if(m_bTimerRunning)
	{
		// We are loosing focus for some reason, so we want to kill the 
		// pattern matching timer.
		StopTimer();
		m_bTimerRunning = FALSE;
		m_strPat.Empty();
	}

	return CGXBDTGadget::Enable(bEnable);
}

//---------------------------------------------------------------------------
// OnKeyDown
//
// Handles WM_KEYDOWN messages which we are enabled.
//
void CGXBDTListGadget::OnKeyDown(UINT nChar)
{
	switch(nChar)
	{
	case VK_ADD:
	case VK_UP:
		// An increment, clear any current state before telling our parent
		// CGXBDateTimeCtrl that we need to be incremented.
		if(m_bTimerRunning)
		{
			StopTimer();
			m_bTimerRunning = FALSE;
		}

		// Perform an increment
		Notify(GXDT_GN_INCREMENT, m_nID);
		break;

	case VK_DOWN:
	case VK_SUBTRACT:
		// A decrement, clear any current state before telling our parent
		// CGXBDateTimeCtrl that we need to be decremented.
		if(m_bTimerRunning)
		{
			StopTimer();
			m_bTimerRunning = FALSE;
		}

		// Perform a decrement
		Notify(GXDT_GN_DECREMENT, m_nID);
		break;

	case VK_HOME:
		// Home causes us to move to the start of our valid range. We clear
		// any state before asking our parent CGXBDateTimeCtrl to move us to
		// our minimum value
		if(m_bTimerRunning)
		{
			StopTimer();
			m_bTimerRunning = FALSE;
		}

		// Move to start of range
		Notify(GXDT_GN_MINIMUM, m_nID);
		break;

	case VK_END:
		// End causes us to move to the end of our valid range. We clear
		// any state before asking our parent CGXBDateTimeCtrl to move us to
		// our maximum value
		if(m_bTimerRunning)
		{
			StopTimer();
			m_bTimerRunning = FALSE;
		}

		// Move to end of range
		Notify(GXDT_GN_MAXIMUM, m_nID);
		break;
	}
}

//---------------------------------------------------------------------------
// OnChar
//
// Handles WM_CHAR messages while we are enabled.
// 
// Characters entered cause a search to be performed from the current position.
// If a match is found we add this character to the a pattern string and start
// a timer. Any further characters entered within this timer are added to this 
// string before performing any further lookups.
//
//    e.g. If the current month is January
//             User enters 'J'  matches with June 
//             User enters 'u'  matches with June
//			   User enters 'l'  matches with July
//         Timer now expires
//             User enters 'J' matches back round to January.
//
void CGXBDTListGadget::OnChar(UINT nChar)
{
	// Handle MBCS chars by buffering up lead bytes. We wait for subsequent 
	// byte before processing.
	int i;
	for(i=0; m_cBuf[i]; i++);
	m_cBuf[i] = TCHAR(nChar);
	if(_istlead(m_cBuf[i]))
		return;

	// Add new char to pattern
	CString pat = m_cBuf;

	int nLen    = (int)_tcslen(m_strPat);
	if(nLen == 0)
	{
		// No saved pattern, so just match first initial after current position
		// in list
		int nIndex = FindMatch(pat, m_nValue+1);
		if(nIndex == -1)
			// No match for this initial
			MessageBeep((UINT) -1);
		else
		{
			// We have a match, we have already moved to the new index. Need to
			// save the current pattern and start the timer.
			Invalidate(TRUE);
			m_strPat = pat;
			StartTimer(_gxnMatchTimer);
			m_bTimerRunning = TRUE;
		}
	}
	else if((nLen == 1 || 
			(nLen == 2 && _istlead(m_strPat[0]))) && 
			m_strPat.CompareNoCase(pat) == 0)
	{
		// We have one character in the stored pattern (which this input
		// matches to). Therefore move to the next string starting with
		// this character.
		int nIndex = FindMatch(m_strPat, m_nValue + 1);

		// We should always have a match (if no others, then matches to the
		// current index).
		ASSERT(nIndex != -1);

		// Restart the timer.
		Invalidate(TRUE);
		StopTimer();
		StartTimer(_gxnMatchTimer);
		m_bTimerRunning = TRUE;
	}
	else
	{
		// Another character to add to the pattern. Find the first matching
		// string
		m_strPat += m_cBuf;
		int nIndex = FindMatch(m_strPat, m_nValue);
		if(nIndex == -1)
		{
			// We have no match, so reset state.
			StopTimer();
			MessageBeep((UINT) -1);
			m_strPat.Empty();
		}
		else
		{
			// We have a match, so restart the timer.
			StopTimer();
			Invalidate(TRUE);
			StartTimer(_gxnMatchTimer);
		}
	}

	m_cBuf[0] = m_cBuf[1] = TCHAR(NULL);
}

//---------------------------------------------------------------------------
// OnTimer
//
// Handles WM_TIMER messages - these cause our current pattern matching state
// to be reset.
//
void CGXBDTListGadget::OnTimer()
{
	StopTimer();
	m_bTimerRunning = FALSE;
	m_strPat.Empty();
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDTListGadget - implementation
//

//---------------------------------------------------------------------------
// FindMatch
//
// Finds a match for the given pattern from the given current position. Returns
// the index of the matching entry (or -1).
//
int CGXBDTListGadget::FindMatch(LPCTSTR lpszPat, int nCurPos)
{
	// $$
	// Ensure not negative
	nCurPos = max(0, nCurPos);

	int nLen = (int)_tcslen(lpszPat);

	if(nCurPos >= m_list.GetSize())
		// Check for wrap around
		nCurPos = 0;
	int i;
	for(i=nCurPos;; )
	{
		if(_tcsnicmp(m_list[i], lpszPat, nLen) == 0)
		{
			// We have found a matching pattern. Tell our parent 
			// CGXBDateTimeCtrl that we want to move to this entry. If we're not
			// we continue trying to find a valid entry.
			if(Notify(GXDT_GN_VALIDATE, m_nID, LPARAM(i)))
				// It's valid.
				break;
		}

		// Move to next entry.
		i++;
		if(i >= m_list.GetSize())
			// We have wrapped around
			i = 0;

		if(i==nCurPos)
			// We have checked all entries ... abort
			return -1;
	}

	// Tell our parent CGXBDateTimeCtrl to change our value.
	Notify(GXDT_GN_MODIFY, m_nID, LPARAM(i));

	return i;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDTNumericGadget - construction
//
CGXBDTNumericGadget::CGXBDTNumericGadget()
{
	m_nMin      =
	m_nMax      =
	m_nWidth    =
	m_nCurDigit = 0;
	m_bLeadZero = FALSE;
}

CGXBDTNumericGadget::~CGXBDTNumericGadget()
{
}

//---------------------------------------------------------------------------
// Initialise
//
// Initialises this numeric gadget.
//
BOOL CGXBDTNumericGadget::Initialise(CGXBDateTimeCtrl* pCtrl, int nMin, int nMax, 
									int nValue, BOOL bLeadZero, 
									int nID /* = -1 */)
{
	if(!CGXBDTGadget::Initialise(pCtrl, nID))
		return FALSE;

	m_nMin      = nMin;				// Minimum value
	m_nMax      = nMax;				// Maximum value
	m_nValue    = nValue;			// Current value
	m_bLeadZero = bLeadZero;		// TRUE if should be displayed with lead 0

	// Calculate maximum width required
	m_nWidth    = nMax < 10 ? 1 : (nMax < 100 ? 2 : (nMax < 1000 ? 3 : 4));

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDTNumericGadget - overrideables
//

//---------------------------------------------------------------------------
// CalcSize
//
// Sets m_rect to the maximum displayable size of the numeric gadget.
//
void CGXBDTNumericGadget::CalcSize(CDC& dc)
{
	m_rect.SetRectEmpty();
	dc.DrawText(_T("00000"), m_nWidth, m_rect, DT_EXTERNALLEADING | 
		        DT_CALCRECT | DT_SINGLELINE | DT_TOP | DT_LEFT | DT_NOPREFIX);
}

//---------------------------------------------------------------------------
// Draw
//
// Draws the numeric gadet.
//
void CGXBDTNumericGadget::Draw(CDC& dc)
{
	// We normally use the current value, unless we are being editted and
	// have a half complete number (in which case we use m_nNewValue).
	int nValue = m_nCurDigit ? m_nNewValue : m_nValue;

	// Build the display string
	TCHAR buf[20];
	if(m_bLeadZero)					// with lead zero
	{
		TCHAR buf2[20];

		// QA: 31989 - #if Secure Code Cleanup.
		_stprintf(buf2, _T("%%0%dd"), m_nWidth);
		_stprintf(buf, buf2, nValue);		
	}else							// without lead zero
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_stprintf(buf, _T("%d"), nValue);
	}

	// If we are enabled (have focus) then we are highlighted
	if(m_bEnabled)
	{
		dc.SetTextColor(GXGetSysData()->clrHighlightText);
		dc.SetBkColor(GXGetSysData()->clrHighlight);
		dc.SetBkMode(OPAQUE);
	}
	// $$
	else
	{
		dc.SetTextColor(GXGetSysData()->clrText);
		dc.SetBkColor(GetBkColor());
	}
	// and draw the value
	dc.DrawText(buf, -1, m_rect, DT_SINGLELINE | DT_TOP | DT_CENTER |
		        DT_NOPREFIX | DT_EXTERNALLEADING);
}

//---------------------------------------------------------------------------
// Enable
//
// Enables (sets focus to) this gadget
//
BOOL CGXBDTNumericGadget::Enable(BOOL bEnable)
{
	if(m_nCurDigit)
		// We are currently being editted. Validate what we have so far,
		// and update if necessary.
		Validate();

	return CGXBDTGadget::Enable(bEnable);
}

//---------------------------------------------------------------------------
// OnKeyDown
//
// Handles WM_KEYDOWN messages while we are enabled.
//
void CGXBDTNumericGadget::OnKeyDown(UINT nChar)
{
	if(!((nChar >= _T('0') && nChar <= _T('9')) || 
	   (nChar >= VK_NUMPAD0 && nChar <= VK_NUMPAD9)))
	{
		// The digits will be handled in OnChar
		if(m_nCurDigit && !Validate())
			return;
	}

	switch(nChar)
	{
	case VK_ADD:
	case VK_UP:
		// Increment the current value (clearing any edit state first)
		if(m_nCurDigit && !Validate())
			break;

		// Perform an increment
		Notify(GXDT_GN_INCREMENT, m_nID);
		break;

	case VK_DOWN:
	case VK_SUBTRACT:
		// Decrement the current value (clearing any edit state first)
		if(m_nCurDigit && !Validate())
			break;

		// Perform a decrement
		Notify(GXDT_GN_DECREMENT, m_nID);
		break;

	case VK_HOME:
		// Move to our minimum value (clearing any edit state first)
		if(m_nCurDigit && !Validate())
			break;

		// Move to start of range
		Notify(GXDT_GN_MINIMUM, m_nID);
		break;

	case VK_END:
		// Move to our maximum value (clearing any edit state first)
		if(m_nCurDigit && !Validate())
			break;

		// Move to end of range
		Notify(GXDT_GN_MAXIMUM, m_nID);
		break;
	}
}

//---------------------------------------------------------------------------
// OnChar
//
// Handles WM_CHAR message while we are enabled.
//
void CGXBDTNumericGadget::OnChar(UINT nChar)
{
	if(nChar >= _T('0') && nChar <= _T('9'))
	{
		// We have a digit ...

		if(m_nCurDigit == 0)
		{
			// This is the first character entered, we go into edit mode.
			Notify(GXDT_GN_EDIT, m_nID, TRUE);
			m_nNewValue = 0;
		}
		else if(m_nNewValue == 0 && m_nCurDigit && nChar == _T('0'))
			// Another zero entered, value will remain zero, so nothing to do
			return;
		else
			// We will add the new digit to the number. First need to offset
			// the number by a power of 10 to allow for this new digit.
			m_nNewValue *= 10;

		// Add in the new digit
		m_nNewValue += nChar - _T('0');
		m_nCurDigit++;

		// We have receached our maximum number of characters, so validate and
		// commit what we have now.
		if(m_nCurDigit == m_nWidth)
		{
			if(Validate())
				Notify(GXDT_GN_NUMERIC_DONE, m_nID);
		}

		Invalidate(TRUE);
	}
	else if(m_nCurDigit)
	{
		// We are in edit mode, and have received an invalid character. This
		// aborts the edit mode.
		MessageBeep((UINT) -1);
		m_nCurDigit = 0;
		Invalidate();
		Notify(GXDT_GN_EDIT, m_nID, FALSE);
	}
}

//---------------------------------------------------------------------------
// OnCancelMode
//
// Handles the WM_CANCELMODE message while we are enabled.
//
void CGXBDTNumericGadget::OnCancelMode()
{
	if(m_nCurDigit)
		// We are in edit mode ... validate and commit what we have so far
		// (as a way of reseting edit mode)
		Validate();
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDTNumericGadget - implementation
//

//---------------------------------------------------------------------------
// Validate
//
// Validates and commits an edit
//
BOOL CGXBDTNumericGadget::Validate()
{
	BOOL bRes   = FALSE;

	// Reset edit mode
	m_nCurDigit = 0;

	// Ask our parent CGXBDateTimeCtrl to validate the new value
	if(Notify(GXDT_GN_VALIDATE, m_nID, LPARAM(m_nNewValue)))
	{
		// It is valid, so ask our parent CGXBDateTimeCtrl to commit the change.
		bRes     = TRUE;
		m_nValue = m_nNewValue;
		Notify(GXDT_GN_MODIFY, m_nID, LPARAM(m_nValue));
	}
	else
	{
		// It's invalid....
		MessageBeep((UINT) -1);
		Invalidate();
	}

	// We are leaving edit mode.
	Notify(GXDT_GN_EDIT, m_nID, FALSE);

	return bRes;
}




/////////////////////////////////////////////////////////////////////////////
// CGXBDTButtonGadget - construction
//


CGXBDTButtonGadget::CGXBDTButtonGadget()
{
	m_style  = WantMouse;
	m_nState = 0;
}

CGXBDTButtonGadget::~CGXBDTButtonGadget()
{
}

//---------------------------------------------------------------------------
// Initialise
//
// Initialises the button and defines the bitmap to display on the face.
//
BOOL CGXBDTButtonGadget::Initialise(CGXBDateTimeCtrl* pCtrl, LPCTSTR lpszBmpName,
								   int nID /* = -1 */)
{
	if(!CGXBDTGadget::Initialise(pCtrl, nID))
		return FALSE;

	// Load the bitmap
	if(!GXLoadSysColorBitmap(m_bmp, lpszBmpName))
		return FALSE;

	// Store the bitmap resource ID (we will need to reload the bitmap if
	// the system color scheme is changed).
	m_lpszBmpName = lpszBmpName;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDTButtonGadget - overrideables
//

//---------------------------------------------------------------------------
// CalcSize
//
// Sets m_rect to the required size of the button.
//
void CGXBDTButtonGadget::CalcSize(CDC& /* dc */)
{
	m_rect.SetRectEmpty();

	m_rect.right  = 16;
	m_rect.bottom = -1;
}

//---------------------------------------------------------------------------
// Draw
//
// Draws the button component (bound by m_rect)
//
void CGXBDTButtonGadget::Draw(CDC& dc)
{
	HTHEME lhTheme = NULL;
	if(RWIsAppThemed() && RWIsThemeActive())
		// Note: If we use dc.GetWindow()->m_hWnd we do not get a valid window
		// handle. Instead we use AfxGetMainWnd()->GetSafeHwnd().
		lhTheme = RWOpenThemeData(RWGetSafeHwnd(), L"BUTTON");	
	
	CRect r = m_rect;

	if (lhTheme)
	{
		int iState = PBS_NORMAL;
		if (m_nState & Down) iState = UPS_PRESSED;	

		RWDrawThemeBackground (lhTheme, dc.GetSafeHdc(), BP_PUSHBUTTON, iState, &r, 0 );			
		r.DeflateRect(2, 2);
	}
	else
	{
		// Draw the button borders
		if(m_nState & Down)				// Button is currently pressed
		{
			dc.Draw3dRect(r, GXGetSysData()->clrBtnShadow, GXGetSysData()->clrBtnShadow);
			r.DeflateRect(1, 1);
			dc.Draw3dRect(r, GXGetSysData()->clrBtnFace, GXGetSysData()->clrBtnFace);
			r.DeflateRect(1, 1);
		}
		else							// Button is currently raised
		{
			dc.Draw3dRect(r, GXGetSysData()->clrBtnFace, GXGetSysData()->clrWindowFrame);
			r.DeflateRect(1, 1);
			dc.Draw3dRect(r, GXGetSysData()->clrBtnHilite, GXGetSysData()->clrBtnShadow);
			r.DeflateRect(1, 1);
		}

		// Fill the face of the button (prior to loading bitmap)
		dc.FillSolidRect(r, GXGetSysData()->clrBtnFace);
	}

	// Now draw the bitmap centered on the face
	CDC memDC;
	if(memDC.CreateCompatibleDC(&dc))
	{
		BITMAP bm;
		VERIFY(m_bmp.GetObject(sizeof(bm), &bm) == sizeof(bm));

		int nLeft = (r.Width() - bm.bmWidth)/2 + r.left;
		int nTop  = (r.Height() - bm.bmHeight)/2 + r.top;

		if(m_nState & Down)
			// The button is currently pressed, so offset bitmap to give
			// impression of movement.
			nLeft++, nTop++;

		CBitmap *pOldBmp = memDC.SelectObject(&m_bmp);
		dc.BitBlt(nLeft, nTop, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBmp);
	}

	if (lhTheme) RWCloseThemeData (lhTheme);
}

//---------------------------------------------------------------------------
// OnLButtonDown
//
// Handles WM_LBUTTONDOWN messages (the button becomes pressed)
//
void CGXBDTButtonGadget::OnLButtonDown(UINT /* nFlags */, CPoint /* point */)
{
	// Draw the button is a depressed state and set capture so I can tell
	// when the button has been released
	m_nState |= Down | Capture;
	Invalidate();
	CaptureMouse(TRUE);
}

//---------------------------------------------------------------------------
// OnLButtonUp
//
// Handles WM_LBUTTONUP messages (normally when a button is currently
// pressed)
//
void CGXBDTButtonGadget::OnLButtonUp(UINT /* nFlags */, CPoint point)
{
	if(!(m_nState & Capture))
		// The button is not currently pressed, so nothing to do.
		return;

	CaptureMouse(FALSE);
	m_nState ^= Capture;

	if(m_rect.PtInRect(point))
		// The mouse was released while over the button, so inform the 
		// CGXBDateTimeCtrl of the button click.
		Notify(GXDT_GN_DROPDOWN, m_nID);

	if(m_nState & Down)
	{
		// Redraw the button in it's raised (up) state
		m_nState ^= Down;
		Invalidate();
	}
}

//---------------------------------------------------------------------------
// OnMouseMove
//
// Handles WM_MOUSEMOVE messages (normally when a button is currently
// pressed)
//
void CGXBDTButtonGadget::OnMouseMove(UINT /* nFlags */, CPoint point)
{
	if(!(m_nState & Capture))
		// The button is not currently pressed, so nothing to do.
		return;

	// We want to look for changes for state - this happens when the mouse
	// is either dragged into or out of the button.
	BOOL bHit = m_rect.PtInRect(point);
	if(((m_nState & Down) && !bHit) || (!(m_nState & Down) && bHit))
	{
		// Toggle button state and redraw.
		m_nState ^= Down;
		Invalidate();
	}
}

//---------------------------------------------------------------------------
// OnCancelMode
//
// Handles WM_CANCELMODE message (normally when a button is currently
// pressed)
//
void CGXBDTButtonGadget::OnCancelMode()
{
	if(!(m_nState & Capture))
		// The button is not currently pressed, so nothing to do.
		return;

	// Release capture, and return the button to an raised (up) state
	CaptureMouse(FALSE);
	m_nState ^= Capture;

	if(m_nState & Down)
	{
		m_nState ^= Down;
		Invalidate();
	}
}

//---------------------------------------------------------------------------
// OnSysColorChange
//
// Handles WM_SYSCOLORCHANGE message. We want to reload the bitmap to reflect
// the new color scheme.
//
void CGXBDTButtonGadget::OnSysColorChange()
{
	if(m_bmp.m_hObject)
	{
		m_bmp.DeleteObject();

		GXLoadSysColorBitmap(m_bmp, m_lpszBmpName);
	}
}



CGXBDTStaticGadget::CGXBDTStaticGadget()
{
	m_style = 0;
}

CGXBDTStaticGadget::~CGXBDTStaticGadget()
{
}

//---------------------------------------------------------------------------
// Initialise
//
// Initialises the gadget
//
BOOL CGXBDTStaticGadget::Initialise(CGXBDateTimeCtrl* pCtrl, LPCTSTR lpszCaption,
								   int nID /* = -1 */)
{
	if(!CGXBDTGadget::Initialise(pCtrl, nID))
		return FALSE;

	m_strCaption = lpszCaption;

	return TRUE;
}

// GetCaption
//
// Returns my caption
//
CString CGXBDTStaticGadget::GetCaption() const
{
	return m_strCaption;
}

/////////////////////////////////////////////////////////////////////////////
// CGXBDTStaticGadget - overrideables
//

//---------------------------------------------------------------------------
// CalcSize
//
// Sets m_rect to the dimensions of the caption.
//
void CGXBDTStaticGadget::CalcSize(CDC& dc)
{
	m_rect.SetRectEmpty();
	dc.DrawText(m_strCaption, -1, m_rect, DT_EXTERNALLEADING | DT_CALCRECT |
		        DT_SINGLELINE | DT_TOP | DT_LEFT | DT_NOPREFIX);
} 

//---------------------------------------------------------------------------
// Draw
//
// Draws the caption, clipped to m_rect
//
void CGXBDTStaticGadget::Draw(CDC& dc)
{
	dc.DrawText(m_strCaption, -1, m_rect, DT_SINGLELINE | DT_TOP | DT_LEFT |
		        DT_NOPREFIX | DT_EXTERNALLEADING);
} 

#endif // #if _MFC_VER >= 0x0400   
