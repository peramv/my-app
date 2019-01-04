///////////////////////////////////////////////////////////////////////////////
// gxdtcal.cpp : Calendar control
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
// Multi-monitor support
#include <multimon.h>

#if _MFC_VER >= 0x0400   // only supported for MFC version 4.0 or greater

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXDTCAL_H_
#include "grid\gxdtcal.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


IMPLEMENT_SERIAL( CGXBCalendar, CWnd, GXDT_CAL_SCHEMA )
IMPLEMENT_SERIAL( CGXBPopupCalendar, CGXBCalendar, GXDT_CAL_SCHEMA )

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CGXBCalendar, CWnd)
	//{{AFX_MSG_MAP(CGXBCalendar)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CANCELMODE()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_SYSCOLORCHANGE()
	ON_BN_CLICKED(GX_IDB_NEXTYEAR, OnNextYear)
	ON_BN_CLICKED(GX_IDB_PREVYEAR, OnPrevYear)
	ON_BN_CLICKED(GX_IDB_NEXTMONTH, OnNextMonth)
	ON_BN_CLICKED(GX_IDB_PREVMONTH, OnPrevMonth)
	//}}AFX_MSG_MAP
	ON_MESSAGE( GXDT_OK, OnOK )
	ON_MESSAGE( GXDT_CANCEL, OnCancel )
END_MESSAGE_MAP()

		CGXBCalendar::CGXBCalendar( )
{
	m_bFullMonthNames = TRUE;
	m_bFullDayNames = FALSE;
	m_pSelectedDay = NULL;
	m_iPrePostDrawMode = GXDT_BDM_GXDT_DEFAULT_DIALOG_PPDRAW;
	m_iDrawMode = GXDT_BDM_GXDT_DEFAULT_DIALOG_DRAW; 
	m_iBehaMode = GXDT_BBM_GXDT_DEFAULT_DIALOG_BEHAVIOR;
	m_bCreated = FALSE;
#ifdef WIN32
	m_page = COleDateTime(1970,1,1,12,0,0);
#else // !WIN32
	m_page = CTime(1970,1,1,12,0,0);
#endif // WIN32
	m_pSelection = NULL;
	m_nBevelLines = GXDT_DP_DEFAULTBEVELLINES;
	m_bCapture = FALSE;
	
	InitFonts();

}

		CGXBCalendar::~CGXBCalendar( )
{
	// Must free all members of the CObList...PurgeDateList()
	PurgeDateList();
}

void CGXBCalendar::InitColors()
{
	m_clrText = GetSysColor( GXDT_DEFAULT_TEXT_COLOR );
 	m_clrGrayText = GetSysColor( GXDT_DEFAULT_GRAYTEXT_COLOR );
	m_clrLines = GetSysColor( GXDT_DEFAULT_LINES_COLOR );
	m_clrDayBarFace = GetSysColor( GXDT_DEFAULT_DAYBAR_BKGD_COLOR );
	m_clrDayBarText = GetSysColor( GXDT_DEFAULT_DAYBAR_FGD_COLOR );
	m_clrTitleFace = GetSysColor( GXDT_DEFAULT_TITLE_BKGD_COLOR );
	m_clrTitleText = GetSysColor( GXDT_DEFAULT_TITLE_FGD_COLOR );
}

int CGXBCalendar::GetFirstDayOfWeek() const
{
	return m_pnlDayBar.GetFirstDayOfWeek();
}

void CGXBCalendar::SetFirstDayOfWeek(int nNewFirstDay, BOOL bRedraw)
{
	m_pnlDayBar.SetFirstDayOfWeek(nNewFirstDay);

	// Recompute calendar and redraw
	if (m_bCreated) {
		SetUpDateBoxes();
		if ( bRedraw ) {
			Invalidate(FALSE);
			UpdateWindow();
		}
	}
}

BOOL	CGXBCalendar::Create( 	DWORD dwStyle, 
								CRect &rect, 
								CWnd *pParentWnd, 
								UINT nID,
								CCreateContext* pContext )
{

	ASSERT( !rect.IsRectEmpty());

	GXGetSysData()->UpdateSysColors();
	InitColors();

	m_pParent = pParentWnd;
	m_pNotifyWnd = pParentWnd;

#ifdef WIN32
	LPVOID lp = (LPVOID)pContext;
#else  /* WIN16 */
	char FAR *lp = (char FAR *)pContext;
#endif
		if(!CreateEx(0,
				  AfxRegisterWndClass(GetClassStyle(), ::LoadCursor(NULL, IDC_ARROW), GetSysColorBrush(COLOR_BTNFACE)), 				  
				  _T("CGXBCalendar"),
				  dwStyle | WS_CHILD | WS_CLIPCHILDREN,
				  rect.left,
				  rect.top,
				  rect.Width(),
				  rect.Height(),
				  pParentWnd->GetSafeHwnd(),
				  (HMENU)(SEC_DWORD) nID,
				  lp))

	{
		// Not a lot we can do.
		TRACE0("Failed to create CGXBCalendar\n");
		return FALSE;
	}
	
	BOOL bRetVal = TRUE; 
	// We'll first create 'em, then size 'em.  This allows us to have the
	// sizing code in only one place, rather than in Create and in Size...
 
	// After creating the *Calendar* window in the style requested by the
	// user, we'll change dwStyle to the right style for the rest of the Wnd's.
	dwStyle = WS_VISIBLE|WS_CHILD;
	
	// If we're in a "Size Rect To Font" mode, we'll want to adjust the rect.
	AdjustRectSizes( rect );
    
	for ( int i = 0 ; i < CGXBC_NUMDAYS ; i++ ) { 
		// Initially create all as PrePost.  They'll be corrected when they get
		// dates assigned.
		bRetVal &= m_day[i].Create( rect, this, nID, dwStyle, TRUE, FALSE,
							m_iPrePostDrawMode, m_iBehaMode, m_nBevelLines);
	}

	// Must not be able to select or highlight the day or title bars...
	long tmpBehaMode = m_iBehaMode & 
						~(GXDT_PBM_SELECTABLE|GXDT_PBM_HIGHLIGHTABLE);

	bRetVal &= m_pnlDayBar.Create( rect, this, dwStyle, nID, FALSE, FALSE,
						m_iDrawMode, 
						tmpBehaMode, m_nBevelLines  );

	bRetVal &= m_pnlTitle.Create( rect, this, dwStyle, nID, FALSE, FALSE,
						m_iDrawMode | GXDT_PDM_TEXTCENTERED,
						tmpBehaMode, m_nBevelLines  );
	
	// If the date/time has not been set i.e. m_page has it's initial value, then
	// reset it to the current date.
#ifdef WIN32
	// For COleDateTime m_dt==0 is the initial value.
	if ( m_page.m_dt == 0 ) {
		m_page = COleDateTime::GetCurrentTime();
#else // !WIN32
	// For CTime 1/1/70 is the self-initialized value.
	if ( m_page == CTime(1970,1,1,1,1,1) ) {
		m_page = CTime::GetCurrentTime();
#endif // WIN32
		NormalizeDate(m_page);
	}
	SetPage( m_page, FALSE );

	if (bRetVal == TRUE){
		SizeTitle();
		SizeDates();
		SizeDayBar();

 		// If we're in a "Size Font To Rect" mode, we'll want to adjust 
		// the font.
		AdjustFontSizes();

		// Set colors in the Title & Day bars, and in each dayBox.
		m_pnlTitle.SetTextColor(m_clrText);
		m_pnlTitle.SetGrayTextColor(m_clrGrayText);

		m_pnlDayBar.SetTextColor(m_clrText);
		m_pnlDayBar.SetGrayTextColor(m_clrGrayText);

		for ( int i = 0 ; i < CGXBC_NUMDAYS ; i++ ) { 
			m_day[i].SetTextColor(m_clrText);
			m_day[i].SetGrayTextColor(m_clrGrayText);
		}

	}
	m_bCreated = TRUE;

	UpdateWindow();
	SetFocus();
	
	return bRetVal;
}

void	CGXBCalendar::Serialize( CArchive &ar )
{
	// TODO: Implement serialization.
	ar; // unused
}

#ifdef WIN32
BOOL	CGXBCalendar::SetPage( const CTime        &newPage, BOOL bRedraw )
{
	COleDateTime t(newPage.GetTime());
	return SetPage(t, bRedraw);
}

BOOL	CGXBCalendar::SetPage( const COleDateTime &newPage, BOOL bRedraw )
#else
BOOL	CGXBCalendar::SetPage( const CTime        &newPage, BOOL bRedraw )
#endif
{
	// If we're not allowed	to change the page, and we're being asked to, then
	// complain and return false. Otherwise, change the page.
	if ( ( m_bCreated && (m_iBehaMode & GXDT_BBM_MONTH_FROZEN) )
		|| ( !IsDisplayableDate(newPage.GetYear(),
								newPage.GetMonth(),
								newPage.GetDay()) )) {
		MessageBeep( MB_ICONEXCLAMATION );
		return FALSE;
	} else {
		m_page = newPage;
		NormalizeDate(m_page);
		m_pnlTitle.SetPage(m_page);
		SetUpDateBoxes();
		if ( bRedraw ) {
			Invalidate(FALSE);
			UpdateWindow();
		}
		return TRUE;
	}	
}

CGXBDayBox *CGXBCalendar::GetSelectedDate( void )
{
	return m_pSelectedDay;
}

#ifdef WIN32
const COleDateTime& CGXBCalendar::GetSelectedDateValue( void )
#else
const CTime&        CGXBCalendar::GetSelectedDateValue( void )
#endif
{
	return m_pSelectedDay->GetDate();
}

UINT	CGXBCalendar::GetNumHighlightedDates( void )
{
	return (UINT)m_HltDateList.GetCount();
}

#ifdef WIN32
UINT	CGXBCalendar::GetAllHighlightedDates( COleDateTime *pDates, UINT nDates )
{
	// Fill the buffer at pDates with up to nDates CTimes representing 
	// highlighted dates.  Can call GetNumHighlightedDates() to find out
	// how large to make the buffer.
	ASSERT( pDates != NULL );

	POSITION p = m_HltDateList.GetHeadPosition();
    UINT i;
	for ( i = 0; i < nDates; i++ ){
		pDates[i] = *((COleDateTime *)(m_HltDateList.GetNext(p)));
		if ( p == NULL ) break;
	}
	return i;
}
#endif

UINT	CGXBCalendar::GetAllHighlightedDates( CTime *pDates, UINT nDates )
{
	// Fill the buffer at pDates with up to nDates CTimes representing 
	// highlighted dates.  Can call GetNumHighlightedDates() to find out
	// how large to make the buffer.
	ASSERT( pDates != NULL );

	POSITION p = m_HltDateList.GetHeadPosition();
	UINT i;
	for ( i = 0; i < nDates; i++ ){
		pDates[i] = *((CTime *)(m_HltDateList.GetNext(p)));
		if ( p == NULL ) break;
	}
	return i;
}

BOOL	CGXBCalendar::GetAutosizeFont( void )
{
	return (m_iBehaMode & GXDT_BBM_AUTOSIZE_FONT)?0:1;
}

BOOL	CGXBCalendar::GetAutosizeRect( void )
{
	return (m_iBehaMode & GXDT_BBM_AUTOSIZE_RECT)?0:1;
}

void	CGXBCalendar::SetAutosizeRect( BOOL bSet )
{
	if ( bSet ) {
		m_iBehaMode |= GXDT_BBM_AUTOSIZE_RECT;
	} else {
		m_iBehaMode &= ~GXDT_BBM_AUTOSIZE_RECT;
	}
}

void	CGXBCalendar::SetAutosizeFont( BOOL bSet )
{
	if ( bSet ) {
		m_iBehaMode |= GXDT_BBM_AUTOSIZE_FONT;
	} else {
		m_iBehaMode &= ~GXDT_BBM_AUTOSIZE_FONT;
	}
}

const CRect &CGXBCalendar::GetControlRect( void )
{
	static CRect rect;

	GetWindowRect(&rect);
	return rect;
}

CRect	CGXBCalendar::SetControlRect( CRect &newRect )
{
	// Set the control rect to the requested position & size.  If this is not
	// possible, return a NULL Rectangle.  Otherwise return the preceding 
	// control rect.  Perform geometric setup for the new calendar size.
	
	CRect tmp(0,0,0,0);

	if( m_hWnd != NULL ){
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement( &wndpl );
		tmp = wndpl.rcNormalPosition;
		wndpl.rcNormalPosition = newRect;
		SetWindowPlacement( &wndpl );
		SizeTitle();
		SizeDayBar();
		SizeDates();
		AdjustFontSizes();
	}
	
	return tmp;
}

BOOL	CGXBCalendar::GetSingleDate( void )
{
	return ((m_iBehaMode & GXDT_BBM_SINGLE_DATE)?1:0);
}

BOOL	CGXBCalendar::SetSingleDate( BOOL bTurnOn )
{
	BOOL bRetVal = !((m_iBehaMode & GXDT_BBM_SINGLE_DATE)==0L);
	if ( bTurnOn ) {
		m_iBehaMode |= GXDT_BBM_SINGLE_DATE;
	} else {
		m_iBehaMode &= ~GXDT_BBM_SINGLE_DATE;
	}
	return bRetVal;
}

BOOL	CGXBCalendar::GetMonthButtons( void )
{
	return ((m_iBehaMode & GXDT_BBM_MONTH_BUTTONS)?1:0);
}

BOOL	CGXBCalendar::SetMonthButtons( BOOL bTurnOn )
{
	BOOL bRetVal = !((m_iBehaMode & GXDT_BBM_MONTH_BUTTONS)==0L);
	if ( bTurnOn ) {
		m_iBehaMode |= GXDT_BBM_MONTH_BUTTONS;
	} else {
		m_iBehaMode &= ~GXDT_BBM_MONTH_BUTTONS;
	}
	return bRetVal;
}

BOOL	CGXBCalendar::GetYearButtons( void )
{
	return ((m_iBehaMode & GXDT_BBM_YEAR_BUTTONS)?1:0);
}

BOOL	CGXBCalendar::SetYearButtons( BOOL bTurnOn )
{
	BOOL bRetVal = !((m_iBehaMode & GXDT_BBM_YEAR_BUTTONS)==0L);
	if ( bTurnOn ) {
		m_iBehaMode |= GXDT_BBM_YEAR_BUTTONS;
	} else {
		m_iBehaMode &= ~GXDT_BBM_YEAR_BUTTONS;
	}
	return bRetVal;
}

BOOL	CGXBCalendar::GetKeyboardControl( void )
{
	return ((m_iBehaMode & GXDT_BBM_KEYBOARD_CONTROL)?1:0);
}

BOOL	CGXBCalendar::SetKeyboardControl( BOOL bTurnOn )
{
	// TODO: Document inability to execute keyboard control in non-popup.
	BOOL bRetVal = !((m_iBehaMode & GXDT_BBM_KEYBOARD_CONTROL));
	if ( bTurnOn ) {
		m_iBehaMode |= GXDT_BBM_KEYBOARD_CONTROL;
	} else {
		m_iBehaMode &= ~GXDT_BBM_KEYBOARD_CONTROL;
	}
	return bRetVal;
}

BOOL	CGXBCalendar::GetMonthFrozen( void )
{
	return ((m_iBehaMode & GXDT_BBM_MONTH_FROZEN)?1:0);
}

BOOL	CGXBCalendar::SetMonthFrozen( BOOL bMakeFrozen )
{
	BOOL bRetVal = ( m_iBehaMode & GXDT_BBM_MONTH_FROZEN )?1:0;
	if ( bMakeFrozen ) {
		m_iBehaMode |= GXDT_BBM_MONTH_FROZEN;
	} else {
		m_iBehaMode &= ~GXDT_BBM_MONTH_FROZEN;
	}
	return bRetVal;
}

BOOL	CGXBCalendar::GetAutoHide( void )
{
	return ((m_iBehaMode & GXDT_BBM_AUTO_HIDE)?1:0);
}

BOOL	CGXBCalendar::SetAutoHide( BOOL bHideAutomatically )
{
	BOOL bRetVal = ( m_iBehaMode & GXDT_BBM_AUTO_HIDE )?1:0;
	if ( bHideAutomatically ) {
		m_iBehaMode |= GXDT_BBM_AUTO_HIDE;
	} else {
		m_iBehaMode &= ~GXDT_BBM_AUTO_HIDE;
	}
	return bRetVal;
}

UINT	CGXBCalendar::GetAlignmentFlag( void )
{
	return (UINT)(( m_iDrawMode & 0x000F0000 ) >> 16);
}

UINT	CGXBCalendar::SetAlignmentFlag( UINT nNewFlag )
{
	BOOL bRetVal = (UINT)(( m_iDrawMode & 0x000F0000 ) >> 16);
	m_iDrawMode &= 0xFFF0FFFF;
	m_iDrawMode |= ( nNewFlag << 16 );
	return bRetVal;
}

COLORREF CGXBCalendar::SetTextColor( COLORREF newColor )
{
	COLORREF oldColor = m_clrText;
	m_clrText = newColor;

	return oldColor;
};

COLORREF CGXBCalendar::GetTextColor( void )
{
	return m_clrText;
}

void CGXBCalendar::OnPaint() 
{
	// TODO::BitBlt from a Memory DC...
	CPaintDC dc(this); // device context for painting

	CRect r = m_pnlTitle.GetContainerRect();
	CFont* pOldFont = dc.SelectObject(&m_TitleFont);
	if(dc.RectVisible(r))
		m_pnlTitle.OnDraw( &dc );

	r = m_pnlDayBar.GetContainerRect();
	if(dc.RectVisible(r))
	{
		dc.SelectObject(&m_DayFont);
		m_pnlDayBar.OnDraw( &dc );
	}

	PaintDates( &dc );

	dc.SelectObject(pOldFont);
}
  
void CGXBCalendar::SetUpDateBoxes( void )
{
	///////////////////////////////////////////////////////////////////////////
	// Find the date associated with ordinal 0 of the calendar.
#ifdef WIN32
	COleDateTime date(m_page);
	COleDateTimeSpan aDay(1,0,0,0);
#else
	CTime date(m_page);
	CTimeSpan aDay(1,0,0,0);
#endif
	m_phantomSelection = m_page;
	
	while ( date.GetDay() != 1 ) {
		date -= aDay;
	}

	while ( date.GetDayOfWeek() != m_pnlDayBar.GetFirstDayOfWeek() ) {
		date -= aDay;
	}

	///////////////////////////////////////////////////////////////////////////
	// Assign dates to m_day[] array.
	int nDay, nWeek;
	BOOL	bPartOfCurrentMonth = FALSE;

	// Iterate through all displayed days, setting states, draw modes, etc.
	for (int ordinal = 0 ; 	ordinal < CGXBC_NUMDAYS ; ordinal++ ){
  
		// Ensure that hours, minutes, seconds & timezones match.
		NormalizeDate(date);

		nDay = ordinal % 7;
		nWeek = ordinal / 7 ;

		// Following is a state machine to keep track of whether the date
		// associated with the current dayBox is part of the current month
		// of the calendar, or an "overflow" pre or post.
		if (date.GetDay()==1) bPartOfCurrentMonth = !bPartOfCurrentMonth;
		 
		m_day[ordinal].SetDate( date );

		// Make the distinction between PrePost & main-month days.
		if (bPartOfCurrentMonth) {
			m_day[ordinal].SetDrawMode(m_iDrawMode); 
			m_day[ordinal].SetPrePostState(FALSE);
		} else {
			m_day[ordinal].SetDrawMode(m_iPrePostDrawMode);
			m_day[ordinal].SetPrePostState(TRUE); 
		}

		// Set highlight state of the day.  
		if ( DateFoundInList( m_day[ordinal].GetDate() ) ){
			m_day[ordinal].SetHighlight(TRUE,FALSE);
		} else { 
			m_day[ordinal].SetHighlight( FALSE, FALSE );
		}
		
		// Set selected state of the day.
		if ( ( m_pSelection != NULL )
		  && (m_day[ordinal].GetDate() == m_selection )){
			m_phantomSelection = m_selection;
			m_day[ordinal].SetSelected( TRUE, FALSE );
		} else {
			m_day[ordinal].SetSelected( FALSE, FALSE );
		}
		
		date += aDay;
	}
}

void CGXBCalendar::SizeTitle( )
{

	// geo is geometry.  The GXDT_HD_LEFT & GXDT_VD_TOP constants, along with the 
	// GXDT_HD_TITLE & GXDT_VD_TITLE constants, define a proportional "budget" of
	// the total calendar rectangle to be allocated to the title bar.
	
	// First determine how much client area there is...
	CRect geo;
	GetClientRect(&geo);

	// Determine the total width & height budgets.
	double maxPixWide = double(geo.Width()-1);
	double maxPixHigh = double(geo.Height()-1);

	// Adjust height & width according to the title bar's budget.
	geo.BottomRight().x = geo.TopLeft().x + int(maxPixWide*GXDT_HD_TITLE);
	geo.BottomRight().y = geo.TopLeft().y + int(maxPixHigh*GXDT_VD_TITLE);

	// Adjust TLC offset for the title bar.
	geo.TopLeft().x = geo.TopLeft().x + int(maxPixWide*GXDT_HD_LEFT);
	geo.TopLeft().y = geo.TopLeft().y + int(maxPixHigh*GXDT_VD_TOP );

	// And tell the title bar how much space it gets.
	m_pnlTitle.SetContainerRect( geo );
}

void CGXBCalendar::SizeDayBar()
{
	// The day bar contains "Sunday  Monday  Tuesday  Wednesday  ...", etc

	// geo is geometry.  The GXDT_HD_LEFT & GXDT_VD_TITLE constants, along with the 
	// GXDT_HD_DAYBAR & GXDT_VD_WK_0 constants, define a proportional "budget" of
	// the total calendar rectangle to be allocated to the day bar.
	
	// First determine how much client area there is...
	CRect geo;
	GetClientRect(&geo);

	// Determine the total width & height budgets.
	double maxPixWide = double(geo.Width()-1);			 	
	double maxPixHigh = double(geo.Height()-1);

	// Adjust height & width according to the day bar's budget.
	geo.BottomRight().x = geo.TopLeft().x + int(maxPixWide*GXDT_HD_DAYBAR);
	geo.BottomRight().y = geo.TopLeft().y + int(maxPixHigh*GXDT_VD_WK_0);

	// Adjust TLC offset for the day bar.
	geo.TopLeft().x = geo.TopLeft().x + int(maxPixWide*GXDT_HD_LEFT);
	geo.TopLeft().y = geo.TopLeft().y + int(maxPixHigh*GXDT_VD_TITLE);

	// And tell the day bar how much space it gets.
	m_pnlDayBar.SetContainerRect(geo);
}

void CGXBCalendar::SizeDates( void )
{
	// The day boxes' sizing works the same as with the title- and day-bars.
	// The  GXDT_VD_WK_ARRAY and GXDT_HD_DAY_ARRAY array constants depict a
	// proportional	budget for the upper & lower boundaries (GXDT_VD_WK_ARRAY) and
	// the left & right boundaries (GXDT_HD_DAY_ARRAY) for each day box.  Once the
	// total calendar size is determined, this budget is applied to the total
	// to determine the actual screen coords of each day-box, and those coords
	// are used to create a CRect and size the day-boxes.

	// Determine the total geometry of the calendar..
	CRect geo;
	GetClientRect(&geo);

	// Determine the total width & height budgets.
	double MaxPixWide = double(geo.Width());
	double maxPixHigh = double(geo.Height());

	// An array depicting the vertical pixel-coordinates of the horizontal
	// week-demarcator lines.
	int weekLines[7];
	{
		double tmp[7] = GXDT_VD_WK_ARRAY;
		for ( int i = 0 ; i < 7 ; i++ ) {
			weekLines[i] = int(double(maxPixHigh)*tmp[i]);
		}
	}
		
	// An array depicting the horizontal pixel-coordinates of the vertical
	// day-demarcator lines.
	int dayLines[8];
	{
		double tmp[8] = GXDT_HD_DAY_ARRAY;
		for ( int i = 0 ; i < 8 ; i++ ) {
			dayLines[i] = int(double(MaxPixWide)*tmp[i]);
		}
	}

	// Set the container rects of each of the day-boxes, according to the
	// grid defined by dayLines[] and weekLines[]' coordinates.
	int nDay, nWeek;
	for (int ordinal = 0 ; 	ordinal < CGXBC_NUMDAYS ; ordinal++ ){
		nDay = ordinal % 7;
		nWeek = ordinal / 7 ;

		CRect myRect(	dayLines[nDay],			// Left
						weekLines[nWeek],		// Top
						dayLines[nDay+1]-1,		// Right
						weekLines[nWeek+1]-1);	// Bottom

		m_day[ordinal].SetContainerRect(myRect);
	}		

}

void CGXBCalendar::PaintDates( CDC *pDC )
{
	CFont* pOldFont = pDC->SelectObject(&m_DateFont);

	for ( int ordinal = 0; ordinal < CGXBC_NUMDAYS ; ordinal++ ) {
		CRect r = m_day[ordinal].GetContainerRect();
		if(pDC->RectVisible(r))
			m_day[ordinal].OnDraw( pDC );
	}

	pDC->SelectObject(pOldFont);
}

void CGXBCalendar::InitFonts( void ) {

	HGDIOBJ h = GetStockObject( SYSTEM_FONT );
	GetObject(h,sizeof(LOGFONT),&m_lfTitleFont );
	VERIFY(m_TitleFont.CreateFontIndirect(&m_lfTitleFont));
	GetObject(h,sizeof(LOGFONT),&m_lfDayFont );
	VERIFY(m_DayFont.CreateFontIndirect(&m_lfDayFont));
	GetObject(h,sizeof(LOGFONT),&m_lfDateFont );
	VERIFY(m_DateFont.CreateFontIndirect(&m_lfDateFont));

	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(m_lfTitleFont.lfFaceName,CGXBC_GXDT_DEFAULT_FONT);
	m_lfTitleFont.lfHeight *= 2;
	m_lfTitleFont.lfWidth  *= 2;
	m_lfTitleFont.lfQuality = DRAFT_QUALITY;
	m_lfTitleFont.lfOutPrecision = OUT_CHARACTER_PRECIS;
	m_lfTitleFont.lfPitchAndFamily = VARIABLE_PITCH;

	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(m_lfDayFont.lfFaceName,CGXBC_GXDT_DEFAULT_FONT);
	m_lfDayFont.lfQuality = DRAFT_QUALITY;
	m_lfDayFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;

	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(m_lfDateFont.lfFaceName,CGXBC_GXDT_DEFAULT_FONT);
	m_lfDateFont.lfQuality = DRAFT_QUALITY;
	m_lfDateFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
}

#ifdef WIN32
BOOL CGXBCalendar::SelectDate( CTime        date, BOOL bSet )
{
	COleDateTime t = date.GetTime();
	return SelectDate(t, bSet);
}

BOOL CGXBCalendar::SelectDate( COleDateTime date, BOOL bSet )
#else
BOOL CGXBCalendar::SelectDate( CTime        date, BOOL bSet )
#endif
{
	// If we don't do this, a date might not match that in a dateBox,
	// because of a mismatch in the hrs, mins, or CGXBs.
	NormalizeDate( date );

	// Update the pointer/instance pair to determine if a date is
	// being pointed at, and if so, then what date is it?
	if ( bSet ) {
		m_selection = m_phantomSelection = date;
		m_pSelection = &m_selection;
	} else {
		m_pSelection = NULL;
	}

	// Walk the calendar's current page, looking for the date in
	// question.  If we find it, either set or unset it, as appropriate.
	for ( int i = 0 ; i < CGXBC_NUMDAYS ; i++ ) {

		if ( m_day[i].GetDate() == date ) {
			m_day[i].SetSelected( bSet, TRUE );
			m_pSelectedDay = &m_day[i];

			// If the calendar has been created, then we can assume that
			// there is a notify window, and that the window wants to know
			// about the selection.  If the calendar has not been created,
			// then this is a pre-selection, and we will assume it is a part
			// of the setup stage, and the parent doesn't want to know about
			// it.  (There isn't an m_pNotifyWnd yet anyways, by default.)
			if ( m_bCreated ) {
				m_pNotifyWnd->PostMessage( GXDT_DATESELECTED, 
										bSet, 
										LPARAM(&(m_day[i])));
			}
		
			// If we're single-date only, we've done our one date, 
			// so send an OK, which will hide the calendar.
			if ( m_iBehaMode & GXDT_BBM_SINGLE_DATE ) {
				// If the calendar is single-date, then it makes no sense
				// for it to be pre-selected to a particular date, since 
				// that wiould cause it to disappear before appearing.
				ASSERT( m_bCreated );

				m_pNotifyWnd->PostMessage(	GXDT_OK, 
											bSet, 
											LPARAM(&(m_day[i])));
			}
		} else {
			// Not the newly selected date.  Unselect it if it was selected.
			if ( m_day[i].GetSelected() != FALSE ) {
				m_day[i].SetSelected( FALSE, TRUE );
			}
		}

	}
	if ( m_bCreated ) SetFocus();
	return TRUE;
}

#ifdef WIN32
BOOL CGXBCalendar::HighlightDate( CTime        &date, BOOL bSet )
{
	COleDateTime t = date.GetTime();
	return HighlightDate(t, bSet);
}

BOOL CGXBCalendar::HighlightDate( COleDateTime &date, BOOL bSet )
#else
BOOL CGXBCalendar::HighlightDate( CTime        &date, BOOL bSet )
#endif
{
	NormalizeDate( date );

	for ( int i = 0 ; i < CGXBC_NUMDAYS ; i++ ) {
		if ( m_day[i].GetDate() == date ) {
			m_day[i].SetHighlight( bSet, TRUE );
			m_pNotifyWnd->PostMessage( GXDT_HIGHLIGHTLISTCHANGED, 
									bSet, 
									LPARAM(&(m_day[i])));
		}
	}

	if ( bSet ) {
		AddDateToList( date );
	} else {
		RemoveDateFromList( date );
	}

	return TRUE;
}

#ifdef WIN32
BOOL CGXBCalendar::ToggleSelectDate( CTime        &date )
{
	COleDateTime t = date.GetTime();
	return ToggleSelectDate(t);
}

BOOL CGXBCalendar::ToggleSelectDate( COleDateTime &date )
#else
BOOL CGXBCalendar::ToggleSelectDate( CTime        &date )
#endif
{
	NormalizeDate( date );

	BOOL bDateSelected = FALSE;
	CGXBDayBox *pSelectedDate = NULL;
	for ( int i = 0 ; i < CGXBC_NUMDAYS ; i++ ) {
		if ( m_day[i].GetDate() == date ) {
			SelectDate(date,!m_day[i].GetSelected());
			bDateSelected = TRUE;
			i = CGXBC_NUMDAYS;
		}
	}
	if ( bDateSelected && ( m_iBehaMode & GXDT_BBM_SINGLE_DATE	) ) {
		OnOK(WPARAM(0),LPARAM(pSelectedDate));
	}

	return bDateSelected;
}

#ifdef WIN32
BOOL CGXBCalendar::ToggleHighlightDate( CTime        &date )
{
	COleDateTime t = date.GetTime();
	return ToggleHighlightDate(t);
}

BOOL CGXBCalendar::ToggleHighlightDate( COleDateTime &date )
#else
BOOL CGXBCalendar::ToggleHighlightDate( CTime        &date )
#endif
{
	NormalizeDate( date );

	BOOL bDateHighlighted = FALSE;
	for ( int i = 0 ; i < CGXBC_NUMDAYS ; i++ ) {
		if ( m_day[i].GetDate() == date ) {
			HighlightDate(date,!m_day[i].GetHighlight());
			bDateHighlighted = TRUE;
			i = CGXBC_NUMDAYS;
		}
	}

	return TRUE;
}

#ifdef WIN32
#define CTime COleDateTime

BOOL CGXBCalendar::AddDateToList( COleDateTime date )
#else
BOOL CGXBCalendar::AddDateToList( CTime        date )
#endif
{
	NormalizeDate( date );

	BOOL bRetval = TRUE;
	CTime *pTmp;
	if ( m_HltDateList.IsEmpty() ) {
		pTmp = new CTime(date);
		m_HltDateList.AddHead((CObject *)pTmp);
	} else {
		POSITION p = m_HltDateList.GetHeadPosition();
		while (  (p != NULL ) 
			  && ( *((CTime *)m_HltDateList.GetAt(p)) < date )){			
			m_HltDateList.GetNext(p);
		}

		// At this point, current > date, if date is not in the list,
		// current == date if date is in the list, or p == NULL if we're
		// at the end of the list...
		if ( p == NULL ) {
			pTmp = new CTime(date);
			m_HltDateList.AddTail((CObject *)pTmp);
		} else {
			pTmp = (CTime *)m_HltDateList.GetAt(p);
			if ( *pTmp > date ) {
				pTmp = new CTime(date);
				m_HltDateList.InsertBefore(p,(CObject *)pTmp);
			} else if ( *pTmp == date ) {
				bRetval = FALSE;
				// Nothing.  We don't want duplicates...
			} else {
				ASSERT( FALSE );
				// Elements in list out of order?
			}
		}
	}

	return bRetval;
}

#ifdef WIN32
BOOL CGXBCalendar::RemoveDateFromList( COleDateTime date )
#else
BOOL CGXBCalendar::RemoveDateFromList( CTime        date )
#endif
{
	NormalizeDate( date );

	BOOL bRetval = FALSE;
	CTime *pTmp;
	
	POSITION pos1, pos2;

	for( pos1 = m_HltDateList.GetHeadPosition(); ( pos2 = pos1 ) != NULL; ){
	    if( *((CTime *)m_HltDateList.GetNext( pos1 )) == date ) {
	        pTmp = (CTime *)m_HltDateList.GetAt( pos2 );
			m_HltDateList.RemoveAt( pos2 );
	        delete pTmp;
	    }
	}

	return bRetval;
}

#ifdef WIN32
BOOL CGXBCalendar::DateFoundInList( COleDateTime date )
#else
BOOL CGXBCalendar::DateFoundInList( CTime        date )
#endif
{
	NormalizeDate( date );

	BOOL bRetval = FALSE;
	CTime *pTmp;
	
	POSITION p = m_HltDateList.GetHeadPosition();
	while ( p != NULL ) {
		pTmp = (CTime *)m_HltDateList.GetNext(p);
		if ( *pTmp == date ) {
			p = NULL;  // Force exit from the loop.
			bRetval = TRUE;
		} else if ( *pTmp > date ) {
			p = NULL;  // Force exit from the loop.
			bRetval = FALSE;
		}
	}
	return bRetval;
}

#ifdef WIN32
#undef CTime
#endif

void CGXBCalendar::PurgeDateList( void )
{
	CTime *pTmp;
	POSITION p1, p2;
	
	p1 = m_HltDateList.GetHeadPosition();
	while ( (p2 = p1) != NULL ) {
		pTmp = (CTime *)m_HltDateList.GetNext(p1);
		m_HltDateList.RemoveAt(p2);
		delete pTmp;
	}
	ASSERT(m_HltDateList.IsEmpty()); 
	return;
}

#ifdef _DEBUG
void CGXBCalendar::DumpDateList( void )
{
	CTime *pTmp;
	POSITION p = m_HltDateList.GetHeadPosition();
	while ( p != NULL ) {
		pTmp = (CTime *)m_HltDateList.GetNext(p);
		TRACE3("%2d/%2d/%4d\n",
			pTmp->GetMonth(),
			pTmp->GetDay(),
			pTmp->GetYear());

	}
	return;
}
#endif

void CGXBCalendar::AdjustRectSizes( CRect &r, CDC *pDC /* = NULL */)
{
	BOOL bRelease = FALSE;

	if ( !( m_iBehaMode & GXDT_BBM_AUTOSIZE_RECT))	return;

	// Must pass in a pDC whenever resizing prior to or during creation.
	// Can use a NULL if *re*sizing rect or font, or both.
	if ( pDC == NULL ) {
		pDC = GetDC();
		bRelease = TRUE; // If we did the get, we must do the release too
	}

	
	m_day[0].SetBehaviorMode(m_iBehaMode);
	m_day[0].SetDrawMode(m_iPrePostDrawMode);
	m_day[0].SetBevelLines(m_nBevelLines);
	CSize dayBoxSize = m_day[0].RectSizeFromFont( pDC, this );

	CSize dayBarSize = m_pnlDayBar.RectSizeFromFont( pDC, this );
	CSize titleBarSize = m_pnlTitle.RectSizeFromFont( pDC, this );

	if (bRelease)
		ReleaseDC(pDC);

	dayBoxSize.cx *= 7;	// 7 days in a week.
	dayBoxSize.cy *= 6;	// 6 weeks shown on a calendar.

	CSize newSize;
	newSize.cx = max(max(dayBoxSize.cx,dayBarSize.cx),titleBarSize.cx);
	newSize.cy = dayBoxSize.cy + dayBarSize.cy + titleBarSize.cy;

	// TODO::Account for sizing alignments.
	// e.g. Centered on guesstimate rect, topLeft, etc...
	r.BottomRight() = r.TopLeft()+newSize;
}

void CGXBCalendar::AdjustFontSizes( CDC *pDC /* = NULL */ )
{
	BOOL bRelease = FALSE;

	if ( !( m_iBehaMode & GXDT_BBM_AUTOSIZE_FONT))	return;

	if ( pDC == NULL ) {
		pDC = GetDC();
		bRelease = TRUE; // If we GetDC, we must also ReleaseDC
	}

	LOGFONT lfTemp;
	HGDIOBJ h = GetStockObject( SYSTEM_FONT );
	GetObject(h,sizeof(LOGFONT),&lfTemp );

	// Adjust font sizes for the Day Boxes.
	m_lfDateFont.lfHeight=lfTemp.lfHeight;
	m_lfDateFont.lfWidth =lfTemp.lfWidth;

	m_lfDateFont = m_day[0].FontSizeFromRect( pDC, &m_lfDateFont );
	if(m_DateFont.m_hObject)
		m_DateFont.DeleteObject();
	VERIFY(m_DateFont.CreateFontIndirect(&m_lfDateFont));

	// Adjust font sizes for the Title Bar.
	m_lfTitleFont.lfHeight=lfTemp.lfHeight;
	m_lfTitleFont.lfWidth =lfTemp.lfWidth;
	m_lfTitleFont = m_pnlTitle.FontSizeFromRect( pDC, &m_lfTitleFont );
	if(m_TitleFont.m_hObject)
		m_TitleFont.DeleteObject();
	VERIFY(m_TitleFont.CreateFontIndirect(&m_lfTitleFont));

	// Adjust font sizes for the Day Bar.
	m_lfDayFont.lfHeight=lfTemp.lfHeight;
	m_lfDayFont.lfWidth =lfTemp.lfWidth;
	m_lfDayFont = m_pnlDayBar.FontSizeFromRect( pDC, &m_lfDayFont );
	if(m_DayFont.m_hObject)
		m_DayFont.DeleteObject();
	VERIFY(m_DayFont.CreateFontIndirect(&m_lfDayFont));

	if (bRelease)
		ReleaseDC(pDC);
}

void CGXBCalendar::OnSysColorChange()
{
	GXGetSysData()->UpdateSysColors();
	InitColors();

	CWnd::OnSysColorChange();
}

LRESULT CGXBCalendar::OnOK( WPARAM u, LPARAM l )
{
	m_pNotifyWnd->PostMessage( GXDT_OK, u, l );
	ShowWindow(SW_HIDE);
	return 0L;
}

LRESULT CGXBCalendar::OnCancel( WPARAM u, LPARAM l )
{
	m_pNotifyWnd->PostMessage( GXDT_CANCEL, u, l );
	ShowWindow(SW_HIDE);
	return 0L;
}

BOOL CGXBCalendar::SetBehaviorMode( long m )
{
	m_iBehaMode = m;
	return TRUE;
}

long CGXBCalendar::GetBehaviorMode( void )
{
	return m_iBehaMode;
}

BOOL CGXBCalendar::SetDrawMode( long m )
{
	m_iDrawMode = m;
	return TRUE;
}

long CGXBCalendar::GetDrawMode( void )
{
	return m_iDrawMode;
}

BOOL CGXBCalendar::SetPrePostDrawMode( long n )
{
	m_iPrePostDrawMode = n;
	return TRUE;
}

long CGXBCalendar::GetPrePostDrawMode( void )
{
	return m_iPrePostDrawMode;
}

#if (_MFC_VER >= 0x0800)  // Visual Studio 2005 (as of CTP August 2005)
LRESULT CGXBCalendar::OnNcHitTest(CPoint point) 
#else
UINT CGXBCalendar::OnNcHitTest(CPoint point) 
#endif
{
	// This disables the window's ability to resize itself...
#if (_MFC_VER >= 0x0800)  // Visual Studio 2005 (as of CTP August 2005)
	LRESULT i = CWnd::OnNcHitTest(point);

#else
	UINT i = CWnd::OnNcHitTest(point);
#endif 
 	if ( m_iBehaMode & GXDT_BBM_RESIZEABLE ) {
		// If it's okay to resize, be honest.
		return i;
	} else {
		// otherwise, lie about a border (resizability) hit...
		if ( i == HTBORDER ||  i == HTBOTTOM  || i == HTBOTTOMLEFT ||
			 i == HTBOTTOMRIGHT	|| i == HTTOPLEFT  || i == HTTOPRIGHT  ||
			 i == HTLEFT  || i == HTRIGHT  || i == HTTOP ) i = HTCLIENT;  
//#if (_MFC_VER >= 0x0800)  // Visual Studio 2005 (as of CTP August 2005)
//		return (LRESULT)i ;
//#else
		return i ;
//#endif 
	}
}

CWnd *CGXBCalendar::GetNotifyWnd( void )
{
	return 	m_pNotifyWnd;
}

void CGXBCalendar::SetNotifyWnd( CWnd *pWnd )
{
		m_pNotifyWnd = pWnd;
}

UINT CGXBCalendar::GetClassStyle( void )
{
	return CS_DBLCLKS;
}

void CGXBCalendar::OnDatePegged( void )
{
	MessageBeep(MB_ICONEXCLAMATION );
}

void CGXBCalendar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDblClk(nFlags, point);
	for ( int i = 0 ; i < CGXBC_NUMDAYS ; i++ ) {
		if ( m_day[i].HitTest(point) ){
			m_day[i].OnLButtonDblClk(nFlags, point);
		}
	}
}

void CGXBCalendar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);
	for ( int i = 0 ; i < CGXBC_NUMDAYS ; i++ ) {
		if ( m_day[i].HitTest(point) ){
			m_bDaySaved = FALSE;
			if(m_selection.GetYear() == m_page.GetYear() &&
			   m_selection.GetMonth() == m_page.GetMonth())
			{
				m_SaveSelectedDay = m_selection;
				m_bDaySaved       = TRUE;
			}

			m_day[i].OnLButtonDown(nFlags, point);

			if(m_day[i].GetSelected() && (m_iBehaMode & GXDT_BBM_LBUTTONTRACK) )
			{
				ASSERT(m_bCapture == FALSE);
				SetCapture();
				m_bCapture = TRUE;
			}

			break;
		}
	}
}

void CGXBCalendar::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);

	if(m_bCapture)
	{
		ReleaseCapture();
		m_bCapture = FALSE;
		for ( int i = 0 ; i < CGXBC_NUMDAYS ; i++ ) {
			if ( m_day[i].HitTest(point) ){
				m_day[i].OnLButtonDown(nFlags, point);
				
				if ( m_iBehaMode & GXDT_PBM_AUTOCLOSEABLE )
					OnOK(0, 0);

				return;
			}
		}

		// Not found return selection to previously selected date.
		CRect rect;
		GetClientRect(&rect);
		if(!rect.PtInRect(point))
		{
			if(m_bDaySaved)
				SelectDate(m_SaveSelectedDay, TRUE);
		}
		else
		{
			if ( m_iBehaMode & GXDT_PBM_AUTOCLOSEABLE )
				OnOK(0, 0);
		}
	}
}

void CGXBCalendar::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd::OnMouseMove(nFlags, point);

	if(m_bCapture)
	{
		for ( int i = 0 ; i < CGXBC_NUMDAYS ; i++ ) {
			if ( m_day[i].HitTest(point) ){
				if(!m_day[i].GetSelected())
					m_day[i].OnLButtonDown(nFlags, point);
				return;
			}
		}

		CRect rect;
		GetClientRect(&rect);
		if(!rect.PtInRect(point) && m_pSelectedDay->GetSelected())
			SelectDate(m_pSelectedDay->GetDate(), FALSE);
	}
}

void CGXBCalendar::OnCancelMode()
{
	CWnd::OnCancelMode();

	if(m_bCapture)
	{
		ReleaseCapture();
		m_bCapture = FALSE;

		if(m_bDaySaved)
			SelectDate(m_SaveSelectedDay, TRUE);
	}
}

void CGXBCalendar::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnRButtonDown(nFlags, point);
	for ( int i = 0 ; i < CGXBC_NUMDAYS ; i++ ) {
		if ( m_day[i].HitTest(point) ){
			m_day[i].OnRButtonDown(nFlags, point);
		}
	}
}

void CGXBCalendar::OnNextYear() { AdvanceYear(); }

void CGXBCalendar::OnPrevYear() { RetreatYear(); }

void CGXBCalendar::OnNextMonth(){ AdvanceMonth();}

void CGXBCalendar::OnPrevMonth(){ RetreatMonth();}

void CGXBCalendar::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// If we've no business being here, get out.
	if ( !(m_iBehaMode & GXDT_BBM_KEYBOARD_CONTROL) ) return;

	
	// Determine if the CONTROL key is pressed...
	int ks = GetKeyState( VK_CONTROL );
	ks >>= ((sizeof(int)*8)-1);
	BOOL bIsControl = ( ks != 0 );

	
 	switch(nChar) {
		case VK_RETURN:
			if ( m_pSelectedDay != NULL ) {
				OnOK(0,0L);
			} else {
				OnCancel(0,0L);
			}
			break;
		case VK_CANCEL:
		case VK_ESCAPE:
			OnCancel(0,0L);
			break;

		case VK_SPACE:
			ToggleSelectDate( m_phantomSelection );
			break;

		case VK_END:
			{
				// Put us past the end of this month, accounting for changing
				// year, if necessary.
#ifdef WIN32
				const COleDateTimeSpan ts4(4,0,0,0);
				const COleDateTimeSpan ts1(1,0,0,0);
				COleDateTime tmp(m_page.GetYear(),m_page.GetMonth(),28,12,0,0);
#else // !WIN32
				const CTimeSpan ts4(4,0,0,0);
				const CTimeSpan ts1(1,0,0,0);
				CTime tmp(m_page.GetYear(),m_page.GetMonth(),28,12,0,0);
#endif // WIN32
				tmp += ts4;	 // We're into the next month...

				// Back up until the month is same, therefore, end of month.
				while ( tmp.GetMonth() != m_page.GetMonth() ) tmp -= ts1;
				SelectDate(tmp,TRUE);
			}
			break;
		case VK_HOME:
#ifdef WIN32
			COleDateTime tmp(m_page.GetYear(),m_page.GetMonth(),1,12,0,0);
#else // !WIN32
			CTime tmp(m_page.GetYear(),m_page.GetMonth(),1,12,0,0);
#endif // WIN32
			SelectDate(tmp,TRUE);
			break;

	}

	// Control-key-dependent behavior...
	if ( ! bIsControl ) {
		switch(nChar) {
			case VK_NUMPAD4:
			case VK_LEFT:
				RetreatDay(TRUE);
				break;
			case VK_RIGHT:
			case VK_NUMPAD6:
				AdvanceDay(TRUE);
				break;
			case VK_NUMPAD8:
			case VK_UP:
				RetreatWeek(TRUE);
				break;
			case VK_NUMPAD2:
			case VK_DOWN:
				AdvanceWeek(TRUE);
				break;
			case VK_PRIOR:
				RetreatMonth(TRUE);
				break;
 			case VK_NEXT:
				AdvanceMonth(TRUE);
			default:
				// No default processing.
				break;
		}
	} else { // bIsControl
		switch(nChar) {
			case VK_NUMPAD4:
			case VK_LEFT:
				RetreatMonth(TRUE);
				break;
			case VK_NUMPAD6:
			case VK_RIGHT:
				AdvanceMonth(TRUE);
				break;
			case VK_NUMPAD8:
 			case VK_PRIOR:
			case VK_UP:
				RetreatYear(TRUE);
				break;
			case VK_NUMPAD2:
			case VK_NEXT:
			case VK_DOWN:
				AdvanceYear(TRUE);
				break;
			default:
 				// No default processing.
				break;
		}
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CGXBCalendar::AdvanceDay( BOOL bSelectionFollows /* = TRUE */)
{
	ASSERT( !(bSelectionFollows && (m_pSelectedDay == NULL))); 
	// You want selection to follow, but no day has been selected!

#ifdef WIN32
	COleDateTimeSpan ts = COleDateTimeSpan(1,0,0,0);
#else
	CTimeSpan ts = CTimeSpan(1,0,0,0);
#endif

	if (ts.GetStatus() == COleDateTimeSpan::valid) {
		if ( bSelectionFollows ) {
			return DeltaSelection( ts );
		} else {
			return DeltaPage( ts );
		}
	} else return FALSE;
}

BOOL CGXBCalendar::RetreatDay( BOOL bSelectionFollows /* = TRUE */)
{
	ASSERT( !(bSelectionFollows && (m_pSelectedDay == NULL))); 
	// You want selection to follow, but no day has been selected!

#ifdef WIN32
	COleDateTimeSpan ts = COleDateTimeSpan(-1,0,0,0);
#else
	CTimeSpan ts = CTimeSpan(-1,0,0,0);
#endif

	if (ts.GetStatus() == COleDateTimeSpan::valid) {
		if ( bSelectionFollows ) {
			return DeltaSelection( ts );
		} else {
			return DeltaPage( ts );
		}
	} else return FALSE;
}

BOOL CGXBCalendar::AdvanceWeek( BOOL bSelectionFollows /* = TRUE */)
{
	ASSERT( !(bSelectionFollows && (m_pSelectedDay == NULL))); 
	// You want selection to follow, but no day has been selected!

	SetFocus();

#ifdef WIN32
	COleDateTimeSpan ts = COleDateTimeSpan(7,0,0,0);
#else
	CTimeSpan        ts = CTimeSpan(7,0,0,0);
#endif

	if (ts.GetStatus() == COleDateTimeSpan::valid) {
		if ( bSelectionFollows ) {
			return DeltaSelection( ts );
		} else {
			return DeltaPage( ts );
		}
	} else return FALSE;
}

BOOL CGXBCalendar::RetreatWeek( BOOL bSelectionFollows /* = TRUE */)
{
	ASSERT( !(bSelectionFollows && (m_pSelectedDay == NULL))); 
	// You want selection to follow, but no day has been selected!

	SetFocus();

#ifdef WIN32
	COleDateTimeSpan ts = COleDateTimeSpan(-7,0,0,0);
#else
	CTimeSpan        ts = CTimeSpan(-7,0,0,0);
#endif

	if (ts.GetStatus() == COleDateTimeSpan::valid) {
		if ( bSelectionFollows ) {
			return DeltaSelection( ts );
		} else {
			return DeltaPage( ts );
		}
	} else return FALSE;
}

BOOL CGXBCalendar::AdvanceMonth( BOOL bSelectionFollows /* = TRUE */ )
{
	ASSERT( !(bSelectionFollows && (m_pSelectedDay == NULL))); 
	// You want selection to follow, but no day has been selected!

	// Two times, pre (before the advance) & post (after the advance).
#ifdef WIN32
	COleDateTime pre,post;
#else
	CTime pre,post;
#endif

	// Get the appropriate date to be delta'd
	if ( bSelectionFollows ) {
		pre = m_pSelectedDay->GetDate();
	} else {
		pre = m_page;
	}

	// "post" starts at the beginning of "pre's" month, and is then
	// advanced until it's at the first of the	next month.
	// We skip the 27 days following the beginning of "pre's" month,
	// to speed up the finding of the first of the next month..
#ifdef WIN32
	post = COleDateTime(pre.GetYear(),pre.GetMonth(),1,12,0,0);
	post += COleDateTimeSpan(27,0,0,0);
	while (post.GetDay() != 1 ) post += COleDateTimeSpan(1,0,0,0);

	SetFocus();

	// Get the timespan for the delta.
	COleDateTimeSpan ts = post - pre;
#else // !WIN32
	post = CTime(pre.GetYear(),pre.GetMonth(),1,12,0,0);
	post += CTimeSpan(27,0,0,0);
	while (post.GetDay() != 1 ) post += CTimeSpan(1,0,0,0);

	SetFocus();

	// Get the timespan for the delta.
	CTimeSpan ts = post - pre;
#endif // WIN32
	
	// Set the selection or the [page & selection] to this date.
	BOOL bRC = FALSE;

	if (ts.GetStatus() == COleDateTimeSpan::valid) {
		if ( bSelectionFollows ) {
			bRC=DeltaSelection( ts );
		} else {
			bRC=DeltaPage( ts );
		}
	} else bRC = FALSE;
	
	// In date/time control, if user hit enter to dismiss a popup,
	// the currently selected daybox would return its date in
	// response to a GetSelectedDateValue call, which is not inuitive
	// since this value is not displayed as "pressed" on a month/year
	// advance/retreat. Therefore, we are selecting this daybox on the 
	// advance such that the user gets a bit more of an inituitive response
	if(m_pSelectedDay)
		SelectDate(m_pSelectedDay->GetDate(),TRUE);

	return bRC;
}

BOOL CGXBCalendar::RetreatMonth( BOOL bSelectionFollows /* = TRUE */ )
{
	ASSERT( !(bSelectionFollows && (m_pSelectedDay == NULL))); 
	// You want selection to follow, but no day has been selected!

	// Two times, pre (before the retreat) & post (after the retreat).
#ifdef WIN32
	COleDateTime pre, post;
#else
	CTime pre, post;
#endif

	// Get the appropriate date to be delta'd
	if ( bSelectionFollows ) {
		pre = m_pSelectedDay->GetDate();
	} else {
		pre = m_page;
	}

	// "post" starts at the beginning of "pre's" month, and is then
	// backed up until it's at the first of the	preceding month.
	// We skip the 27 days preceding the beginning of "pre's" month,
	// to speed up the finding of the first of the preceding month..
#ifdef WIN32
	post = COleDateTime(pre.GetYear(),pre.GetMonth(),1,12,0,0);
	post -= COleDateTimeSpan(27,0,0,0);
	while (post.GetDay() != 1 ) post -= COleDateTimeSpan(1,0,0,0);

	SetFocus();

	// Get the timespan for the delta.
	COleDateTimeSpan ts = post - pre;
#else // !WIN32
	post = CTime(pre.GetYear(),pre.GetMonth(),1,12,0,0);
	post -= CTimeSpan(27,0,0,0);
	while (post.GetDay() != 1 ) post -= CTimeSpan(1,0,0,0);

	SetFocus();

	// Get the timespan for the delta.
	CTimeSpan ts = post - pre;
#endif // WIN32

	// Set the selection or the [page & selection] to this date.
	BOOL bRC = FALSE;
	if (ts.GetStatus() == COleDateTimeSpan::valid) {
		if ( bSelectionFollows ) {
			bRC=DeltaSelection( ts );
		} else {
			bRC=DeltaPage( ts );
		}
	} else bRC = FALSE;
	
	// In date/time control, if user hit enter to dismiss a popup,
	// the currently selected daybox would return its date in
	// response to a GetSelectedDateValue call, which is not inuitive
	// since this value is not displayed as "pressed" on a month/year
	// advance/retreat. Therefore, we are selecting this daybox on the 
	// advance such that the user gets a bit more of an inituitive response
	if(m_pSelectedDay)
		SelectDate(m_pSelectedDay->GetDate(),TRUE);

	return bRC;
}

BOOL CGXBCalendar::AdvanceYear( BOOL bSelectionFollows /* = TRUE */ )
{
	ASSERT( !(bSelectionFollows && (m_pSelectedDay == NULL))); 
	// You want selection to follow, but no day has been selected!

	// Two times, pre (before the advance) & post (after the advance).
#ifdef WIN32
	COleDateTime pre, post;
#else
	CTime pre, post;
#endif

	// Get the appropriate date to be delta'd
	if ( bSelectionFollows ) {
		pre = post = m_pSelectedDay->GetDate();
	} else {
		pre = post = m_page;
	}

	// If this advance would put us into an undisplayable date, don't do it.
	if ( !IsDisplayableDate( pre.GetYear(),12,31 ) ) {
		OnDatePegged();
		return FALSE;
	}
	
	// Unless we're at 2/29, mm/dd/yyyy can go to mm/dd/yyyy+1 
	if ( (pre.GetMonth() == 2) && (pre.GetDay() == 29) ) {
#ifdef WIN32
		post = COleDateTime(pre.GetYear()+1,2,28,0,0,0);
	} else {
		post = COleDateTime(pre.GetYear()+1,pre.GetMonth(),pre.GetDay(),12,0,0);
#else  // Win16
		post = CTime(pre.GetYear()+1,2,28,0,0,0);
	} else {
		post = CTime(pre.GetYear()+1,pre.GetMonth(),pre.GetDay(),12,0,0);
#endif // WIN32
	}

	SetFocus();

	// Get the timespan for the delta.
#ifdef WIN32
	COleDateTimeSpan ts = post - pre;
#else
	CTimeSpan        ts = post - pre;
#endif

	// Set the selection or the [page & selection] to this date.
	BOOL bRC = FALSE;

	if (ts.GetStatus() == COleDateTimeSpan::valid) {
		if ( bSelectionFollows ) {
			bRC=DeltaSelection( ts );
		} else {
			bRC=DeltaPage( ts );
		}
	} else bRC = FALSE;

	// In date/time control, if user hit enter to dismiss a popup,
	// the currently selected daybox would return its date in
	// response to a GetSelectedDateValue call, which is not inuitive
	// since this value is not displayed as "pressed" on a month/year
	// advance/retreat. Therefore, we are selecting this daybox on the 
	// advance such that the user gets a bit more of an inituitive response
	if(m_pSelectedDay)
		SelectDate(m_pSelectedDay->GetDate(),TRUE);

	return bRC;

	
}

BOOL CGXBCalendar::RetreatYear( BOOL bSelectionFollows /* = TRUE */ )
{
	ASSERT( !(bSelectionFollows && (m_pSelectedDay == NULL))); 
	// You want selection to follow, but no day has been selected!

	// Two times, pre (before the retreat) & post (after the retreat).
#ifdef WIN32
	COleDateTime pre, post;
#else
	CTime pre, post;
#endif

	// Get the appropriate date to be delta'd
	if ( bSelectionFollows ) {
		pre = post = m_pSelectedDay->GetDate();
	} else {
		pre = post = m_page;
	}

	// If this retreat would put us into an undisplayable date, don't do it.
	if ( !IsDisplayableDate( pre.GetYear()-1,12,31) ) {
		OnDatePegged();
		return FALSE;
	}

	// Unless we're at 2/29, mm/dd/yyyy can go to mm/dd/yyyy-1 
	if ( (pre.GetMonth() == 2) && (pre.GetDay() == 29) ) {
#ifdef WIN32
		post = COleDateTime(pre.GetYear()-1,2,28,0,0,0);
	} else {
		post = COleDateTime(pre.GetYear()-1,pre.GetMonth(),pre.GetDay(),12,0,0);
#else  // Win16
		post = CTime(pre.GetYear()-1,2,28,0,0,0);
	} else {
		post = CTime(pre.GetYear()-1,pre.GetMonth(),pre.GetDay(),12,0,0);
#endif // WIN32
	}
 
	SetFocus();

	// Get the timespan for the delta.
#ifdef WIN32
	COleDateTimeSpan ts = post - pre;
#else
	CTimeSpan        ts = post - pre;
#endif

	// Set the selection or the [page & selection] to this date.
	BOOL bRC = FALSE;
	if (ts.GetStatus() == COleDateTimeSpan::valid) {
		if ( bSelectionFollows ) {
			bRC=DeltaSelection( ts );
		} else {
			bRC=DeltaPage( ts );
		}
	} else bRC = FALSE;

	// In date/time control, if user hit enter to dismiss a popup,
	// the currently selected daybox would return its date in
	// response to a GetSelectedDateValue call, which is not inuitive
	// since this value is not displayed as "pressed" on a month/year
	// advance/retreat. Therefore, we are selecting this daybox on the 
	// advance such that the user gets a bit more of an inituitive response
	if(m_pSelectedDay)
		SelectDate(m_pSelectedDay->GetDate(),TRUE);

	return bRC;		
}

#ifdef WIN32
BOOL CGXBCalendar::DeltaPage( CTimeSpan        &ts )
{
	COleDateTimeSpan ots((long)ts.GetDays(), ts.GetHours(), ts.GetMinutes(), ts.GetSeconds());
	return DeltaPage(ots);
}

BOOL CGXBCalendar::DeltaPage( COleDateTimeSpan &ts )
#else
BOOL CGXBCalendar::DeltaPage( CTimeSpan        &ts )
#endif
{
	BOOL bRetVal = TRUE;
#ifdef WIN32
	COleDateTime t = m_page;
#else
	CTime        t = m_page;
#endif
	
	int days = int(ts.GetDays());  // Limitation: delta < 64K days, 16 bit..
	int yrs = days/365;		 
	days -= yrs*365;
	int months = days/28;	 // worst case...
	days -= months*28;
	if (!IsDisplayableDate( t.GetYear()+yrs, 
							t.GetMonth()+months, 
							t.GetDay()+days)) {
		OnDatePegged();
		bRetVal = FALSE;
	} else {
		t += ts;
		SetPage( t, TRUE );
	}
	return bRetVal;
}

#ifdef WIN32
BOOL CGXBCalendar::DeltaSelection( CTimeSpan        &ts )
{
	COleDateTimeSpan ots((long)ts.GetDays(), ts.GetHours(), ts.GetMinutes(), ts.GetSeconds());
	return DeltaSelection(ots);
}

BOOL CGXBCalendar::DeltaSelection( COleDateTimeSpan &ts )
#else
BOOL CGXBCalendar::DeltaSelection( CTimeSpan        &ts )
#endif
{
	if ( m_pSelectedDay == NULL ) {
		MessageBeep( MB_ICONEXCLAMATION );
		return FALSE;
	};

	BOOL bRetVal = TRUE;
#ifdef WIN32
	COleDateTime t1 = m_pSelectedDay->GetDate();
	COleDateTime t2;
#else
	CTime        t1 = m_pSelectedDay->GetDate();
	CTime        t2;
#endif

	int days = int(ts.GetDays());   // Assumption: delta < 64K days, 16 bit..
	int yrs = days/365;		 
	days -= yrs*365;
	int months = days/28; // worst case...
	days -= months*28;
	if (!IsDisplayableDate( t1.GetYear()+yrs, 
							t1.GetMonth()+months, 
							int(t1.GetDay())+days)) {
		OnDatePegged();
		bRetVal = FALSE;
	} else {  // It's a displayable date...
		t2 = t1 + ts;
 		if (  ( t1.GetMonth() != t2.GetMonth() ) 
			||( t1.GetYear()  != t2.GetYear()  )) {
				SetPage( t2, TRUE );
		}
		SelectDate( t2, TRUE );
	}
	return bRetVal;
}

BOOL CGXBCalendar::IsDisplayableDate( int year, int month, int day )
{
#ifdef WIN32
	day;	// unreferenced

	// COleDateTime Limit: 1 January 100 -- 31 December 9999

	return ( (year > 100) || (year == 100 && month > 1) ) 
			&& ( (year < 9999) || (year == 9999 && month <12) );

#else
	month += day/28;
	day   %= 28;
	year  += month/12;
	month %= 12;
	return (   (year >= 1400)
			&& (year <= 2400));
#endif
}

#ifdef WIN32
void CGXBCalendar::NormalizeDate( COleDateTime &date )
{
	static COleDateTimeSpan ts(1,0,0,0);
	date = COleDateTime(date.GetYear(),date.GetMonth(),date.GetDay(),12,0,0);
#else
void CGXBCalendar::NormalizeDate( CTime &date )
{
	static CTimeSpan        ts(1,0,0,0);
	date = CTime(date.GetYear(),date.GetMonth(),date.GetDay(),12,0,0);
#endif

	// And since the time is so helpful in accounting for time zone changes,
	// we've gotta remove the "help"...
	switch ( date.GetHour() ) {
		case 11: 
			date += ts;	break; 
		case 13:
			date -= ts;	break;
		case 12:
			break;
		default:
			ASSERT(FALSE);
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGXBPopupCalendar, CGXBCalendar)
	//{{AFX_MSG_MAP(CGXBPopupCalendar)
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CGXBPopupCalendar::CGXBPopupCalendar( )
{
	SetBehaviorMode(GXDT_BBM_GXDT_DEFAULT_POPUP_BEHAVIOR);
	SetDrawMode(GXDT_BDM_GXDT_DEFAULT_POPUP_DRAW);
	SetPrePostDrawMode(GXDT_BDM_GXDT_DEFAULT_POPUP_PPDRAW);
	m_bHideDoesOK = TRUE;
}
		
CGXBPopupCalendar::~CGXBPopupCalendar( )
{
	CWnd::DestroyWindow();
}
		
BOOL CGXBPopupCalendar::Create(DWORD dwStyle, 
		CRect& buttonRect, 
		CWnd* pParentWnd, 
		CCreateContext* pContext) 
{
	// We need to calculate where to place the popup, but first we have to
	// calculate it's size.  First, create an appropriately-sized rect.
	CRect r;
	SetAutosizeRect( TRUE );
	CDC* pDC = pParentWnd->GetDC();
	AdjustRectSizes( r, pDC );
	pParentWnd->ReleaseDC(pDC);

	// Next, move it to the origin.  We'll later move it from there.
	r.OffsetRect(-r.TopLeft());

	// Now adjust the rectangle to include the non-client space
	::AdjustWindowRectEx(&r, dwStyle | WS_POPUP, NULL, 0);
	r.OffsetRect(-r.left, -r.top);

	// Support info for placing the popup so it doesn't go off-screen.
	CRect rectWorkArea;

#ifdef WIN32
	// Multi-monitor support
	HMONITOR hMonitor = MonitorFromPoint(CPoint(buttonRect.left,buttonRect.top), MONITOR_DEFAULTTONEAREST);
	ASSERT(hMonitor != NULL);
	MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
	VERIFY(GetMonitorInfo(hMonitor, &monitorInfo));
	rectWorkArea = monitorInfo.rcWork;
#else 
	int cxScreen = ::GetSystemMetrics(SM_CXSCREEN);
	int cyScreen = ::GetSystemMetrics(SM_CYSCREEN);

	rectWorkArea.SetRect(0,0,cxScreen,cyScreen);
#endif

	CPoint offset;

	if(dwStyle & GXDT_PCS_ALIGNBOTTOMLEFT)
	{
		// Position below the supplied rectangle if possible, otherwise
		// above
		if((buttonRect.bottom + r.Height()) >= rectWorkArea.bottom)
			offset.y = buttonRect.top - r.Height();
		else
			offset.y = buttonRect.bottom;

		if((buttonRect.left + r.Width()) >= rectWorkArea.right)
			offset.x = buttonRect.right - r.Width();
		else
			offset.x = buttonRect.left;
	}
	else
	{
		// We'd like below and right, if possible.  If not, then above 
		// and/or left is the second choice.
		BOOL bAbove = ((buttonRect.bottom+r.Height()) >= rectWorkArea.bottom);
		BOOL bLeft  = ((buttonRect.right  +r.Width() ) >= rectWorkArea.right);

		// Compute an offset from the origin for the top left corner of the rect.
		offset.x = bLeft ?(buttonRect.left-r.Width()):buttonRect.right;
		offset.y = bAbove?(buttonRect.top-r.Height()):buttonRect.bottom;
	}

	// Apply the offset...
	r.OffsetRect(offset);

	// ...and create the popup.

	// SRSTUDIO-965 technique overrides SRSTUDIO-721
        // Ref: Override of CWnd::PreCreateWindow(CREATESTRUCT& cs) in VC++ 10.0 only 
        //      prevents popup calendar from crashing or not working without adding new resources to memory
	if(CGXBCalendar::Create(dwStyle|WS_POPUP, 
							r, 
							pParentWnd, 
							NULL) == TRUE)
	{
		// Successful creation.
		ASSERT(m_hWnd);
		SetFocus();
		return TRUE;
	} else {
		// Programmer info...
		TRACE0("Failed to create CGXBPopupCalendar\n");
		return FALSE;
	}
	pContext; // unused
}

UINT CGXBPopupCalendar::GetClassStyle( void )
{
	return CS_SAVEBITS | CS_DBLCLKS;
}

void CGXBPopupCalendar::Serialize( CArchive &ar )
{
	TRACE0("Implement serialization...\n");
	ar; //unused
}

#if _MSC_VER >= 1600
//@doc CGXBPopupCalendar
//@mfunc Overrides the VC++ 10.0 CWnd::PreCreateWindow() to prevent the popup calendar window from crashing or not working
//@rdesc BOOL 
//@xref <c CGXBPopupCalendar>
BOOL CGXBPopupCalendar::PreCreateWindow(CREATESTRUCT& cs)
{
	CWnd::PreCreateWindow( cs );
    cs.hMenu = NULL;
    return TRUE;
}
#endif

void CGXBPopupCalendar::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CGXBCalendar::OnActivate(nState, pWndOther, bMinimized);
	
	if ( nState == WA_INACTIVE ) {
		if ( m_bHideDoesOK && (GetSelectedDate() != NULL)) {
				OnOK(WPARAM(0),LPARAM(0));
		} else {
			OnCancel(WPARAM(0),LPARAM(0));
		}
	}
}

long CGXBPopupCalendar::SetHideMode( long okOrCancel )
{
	// Only two modes on hide : Either generate an "OK" or a "Cancel".
	ASSERT( ( okOrCancel == IDOK ) || ( okOrCancel == IDCANCEL ) );

	long retVal = m_bHideDoesOK?IDOK:IDCANCEL;
	m_bHideDoesOK = (okOrCancel == IDOK);
	return retVal;
}   




/////////////////////////////////////////////////////////////////////////////
// CGXBCalTitle

IMPLEMENT_SERIAL( CGXBCalTitle, CGXBPanel, GXDT_CALTITLE_SCHEMA )

CGXBCalTitle::CGXBCalTitle()
{
	m_bMonthButtons = TRUE;
	m_bYearButtons = TRUE;
	m_pParent = NULL;
}

CGXBCalTitle::~CGXBCalTitle()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGXBCalTitle message handlers

BOOL CGXBCalTitle::SetPage( const COleDateTime &date )
{
	CString strTitle;
	CString strMonth;

	VERIFY(CGXBLocale::GetMonthName(strMonth, 
		date.GetMonth(), m_iDrawMode & GXDT_BDM_FULL_MONTH_NAMES));

	strTitle.Format(_T("%s %d"), strMonth, date.GetYear());
	SetTextLabel( strTitle );

	return TRUE;
}

BOOL CGXBCalTitle::Create( 	CRect r,
							CWnd *pParent,
							DWORD dwStyle,
							UINT nID,
							BOOL bPressed, 
							BOOL bHighlighted, 
							long lDrawMode,
							long lBehaviorMode,
							UINT nBevelLines )
{

	BOOL bRetVal = 
		CGXBPanel::Create(	r, 
						pParent, 
						dwStyle, 
						nID, 
						bPressed, 
						bHighlighted,
						lDrawMode, 
						lBehaviorMode, 
						nBevelLines  );

	// If we created a window for the Title Bar to live in, then initialize
	// and create the month & year buttons, if requested.
	if ( bRetVal ) {
		ASSERT( pParent->IsKindOf( RUNTIME_CLASS(CGXBCalendar) ) );

		m_pParent = ((CGXBCalendar *)pParent);
		// ~WS_VISIBLE because we don't want to draw until we've sized the
		// whole title bar, and then the buttons.
#ifdef WIN32
		UINT btnStyle = WS_CHILD & ~WS_VISIBLE;
#else // !WIN32
		long btnStyle = WS_CHILD & ~WS_VISIBLE;
#endif // WIN32
		CRect rect(0,0,1,1);

		if ( lBehaviorMode & GXDT_BBM_MONTH_BUTTONS ) {
			bRetVal &= 
			m_btnPrevMonth.Create( _T("<"), btnStyle, rect, m_pParent, GX_IDB_PREVMONTH );
			bRetVal &= 
			m_btnNextMonth.Create( _T(">"), btnStyle, rect, m_pParent, GX_IDB_NEXTMONTH );
		}
		if ( lBehaviorMode & GXDT_BBM_YEAR_BUTTONS ) {
			bRetVal &= 
			m_btnPrevYear.Create( _T("<<"), btnStyle, rect, m_pParent, GX_IDB_PREVYEAR );
			bRetVal &= 
			m_btnNextYear.Create( _T(">>"), btnStyle, rect, m_pParent, GX_IDB_NEXTYEAR );
		}
	}

	return bRetVal;
}

CRect	CGXBCalTitle::SetContainerRect( CRect &rect )
{
	CRect r = CGXBPanel::SetContainerRect( rect );
	SizeButtons();
	return r;
}

void CGXBCalTitle::SizeButtons( void )
{
	UINT nInner, nOuter, nUpper, nLower;
	CRect r1 = GetContainerRect();
	CRect r;
	WINDOWPLACEMENT wp;
	wp.length = sizeof(WINDOWPLACEMENT);

	nUpper = r1.TopLeft().y     + (r1.Height()/5);
	nLower = r1.BottomRight().y - (r1.Height()/5);

 	// Size MONTH buttons.
	if ( m_iBehaviorMode & GXDT_BBM_MONTH_BUTTONS ) {
		if ( m_iBehaviorMode & GXDT_BBM_YEAR_BUTTONS ) {
			nInner = (r1.Width()*50)/200;
			nOuter = (r1.Width()*30)/200;
		}
		else {
			nInner = (r1.Width()*30)/200;
			nOuter = (r1.Width()*10)/200;
		}

		// Draw left-hand month button.
		r.SetRect(r1.TopLeft().x+nOuter,nUpper,r1.TopLeft().x+nInner,nLower);
		m_btnPrevMonth.GetWindowPlacement((WINDOWPLACEMENT FAR *) &wp );
		wp.rcNormalPosition = r;
		m_btnPrevMonth.SetWindowPlacement((WINDOWPLACEMENT FAR *) &wp );
		m_btnPrevMonth.ShowWindow(m_bMonthButtons?SW_SHOW:SW_HIDE);
		m_btnPrevMonth.EnableWindow(TRUE);

		// Draw right-hand month button.
		r.SetRect(r1.BottomRight().x-nInner,nUpper,r1.BottomRight().x-nOuter,nLower);
		m_btnNextMonth.GetWindowPlacement((WINDOWPLACEMENT FAR *) &wp );
		wp.rcNormalPosition = r;
		m_btnNextMonth.SetWindowPlacement((WINDOWPLACEMENT FAR *) &wp );
		m_btnNextMonth.ShowWindow(m_bMonthButtons?SW_SHOW:SW_HIDE);
		m_btnNextMonth.EnableWindow(TRUE);
	}

	// Size YEAR buttons.
   if ( m_iBehaviorMode & GXDT_BBM_YEAR_BUTTONS ) {
		nInner = (r1.Width()*30)/200;
		nOuter = (r1.Width()*10)/200;

		// Draw left-hand year button.
		r.SetRect(r1.TopLeft().x+nOuter,nUpper,r1.TopLeft().x+nInner,nLower);
		m_btnPrevYear.GetWindowPlacement( (WINDOWPLACEMENT FAR *)&wp );
		wp.rcNormalPosition = r;
		m_btnPrevYear.SetWindowPlacement( (WINDOWPLACEMENT FAR *)&wp );
		m_btnPrevYear.ShowWindow(m_bYearButtons?SW_SHOW:SW_HIDE);
		m_btnPrevYear.EnableWindow(TRUE);
 
 		// Draw right-hand year button.
		r.SetRect(r1.BottomRight().x-nInner,nUpper,r1.BottomRight().x-nOuter,nLower);
		m_btnNextYear.GetWindowPlacement( (WINDOWPLACEMENT FAR *)&wp );
		wp.rcNormalPosition = r;
		m_btnNextYear.SetWindowPlacement( (WINDOWPLACEMENT FAR *)&wp );
		m_btnNextYear.ShowWindow(m_bYearButtons?SW_SHOW:SW_HIDE);
		m_btnNextYear.EnableWindow(TRUE);


   }
}

BOOL CGXBCalTitle::OnDraw( CDC *pDC )
{
 	ASSERT( pDC != NULL );

	CGXBPanel::OnDraw( pDC );

	CFont *pFont = m_pParent->GetTitleFont();
	
	if ( m_iBehaviorMode & GXDT_BBM_YEAR_BUTTONS ) {
		m_btnPrevYear.SetFont( pFont, TRUE );
		m_btnNextYear.SetFont( pFont, TRUE );
		m_btnPrevYear.RedrawWindow ( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW );
		m_btnNextYear.RedrawWindow ( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW );
	}
	
	if ( m_iBehaviorMode & GXDT_BBM_MONTH_BUTTONS ) {
		m_btnPrevMonth.SetFont( pFont, TRUE );
		m_btnNextMonth.SetFont( pFont, TRUE );
		m_btnPrevMonth.RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW );
		m_btnNextMonth.RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW );
	}

	return TRUE;
}

void CGXBCalTitle::OnNextYear() 
{
	ASSERT( m_pParent != NULL );

	m_pParent->AdvanceYear();
}

void CGXBCalTitle::OnPrevYear() 
{
	ASSERT( m_pParent != NULL );

	m_pParent->RetreatYear();
}

void CGXBCalTitle::OnNextMonth() 
{
 	ASSERT( m_pParent != NULL );

	m_pParent->AdvanceMonth();
}

void CGXBCalTitle::OnPrevMonth() 
{
	ASSERT( m_pParent != NULL );

	m_pParent->RetreatMonth();
}

CSize CGXBCalTitle::RectSizeFromFont( CDC *pDC, CGXBCalendar* pWnd, LOGFONT *pLf )
{
	ASSERT_VALID(pWnd);

	CFont f, *pf;
	if ( pLf != NULL ) {
		f.CreateFontIndirect( pLf );
		pf = &f;
	} else {
		pf = pWnd->GetTitleFont();
	}
	CFont *pOldFont = pDC->SelectObject( pf );

	BOOL m_bFullMonthNames = (( m_iDrawMode & GXDT_BDM_FULL_MONTH_NAMES )!=FALSE);

	TCHAR *pszLabel = m_bFullMonthNames?_T("September, 2000"):_T("Sep, 2000");
	CSize s = pDC->GetTextExtent(pszLabel, (int)_tcsclen(pszLabel) );

	// If we have buttons, we want the title in the middle half+.
	// If we have no buttons, we want the title full-size. 
	if ( m_bYearButtons || m_bMonthButtons ) {
		// Returned rect will be large enough also to include buttons.
		s.cx = int(s.cx * 2.2);
		s.cy = int(s.cy * 1.2);
	} else {
		// Change factor for other than full-size rectangle.
		s.cx = int(s.cx * 1.2);
		s.cy = int(s.cy * 1.2);
	}
	
	pDC->SelectObject( pOldFont );

	return s;
}

LOGFONT	CGXBCalTitle::FontSizeFromRect( CDC *pDC, LOGFONT *pLf, CRect *pR)
{
	ASSERT( pDC != NULL );

	// We will use lf as a temp LOGFONT during the sizing.
	LOGFONT lf;
	if ( pLf == NULL ) {
#ifdef WIN32
		m_pParent->GetTitleFont()->GetLogFont(&lf);
#else // !WIN32
		GetLogFont(*(m_pParent->GetTitleFont()), &lf);
#endif // WIN32
	} else {
		lf = *pLf;
	}

	// We will use r as a temp CRect during the sizing.
	CRect r;
	if ( pR == NULL ) {	
		r = GetFaceRect();
	} else {
		r = *pR;
	}

	// Font-sizing algorithm will not converge if the sought-after size is
	// zero, so we anticipate & avoid the situation.
	if ( ( r.Height() == 0 ) || ( r.Width() == 0 ) ) {
		lf.lfHeight = lf.lfWidth = 0;
		return lf;
	}


	CSize sz;
	sz = RectSizeFromFont( pDC, m_pParent, &lf ) ;

	// We will iterate through coarse adjustments, greatly enlarging the font
	// and each time determining the resultant rectangle size until the rect
	// is too big, and then finely shrinking the font until the rectangle is 
	// once again small enough.

	while (	sz.cx < r.Width()  &&	sz.cy < r.Height() ) {
		lf.lfHeight *= 2; lf.lfWidth *= 2;			// Coarse adjust.
		sz = RectSizeFromFont( pDC, m_pParent, &lf );
	}

	while ( sz.cx > r.Width() || sz.cy > r.Height() ) {	// Fine Adjust.
		lf.lfHeight = min(int( lf.lfHeight * 0.95 ),lf.lfHeight-1);
		lf.lfWidth  = min(int( lf.lfWidth  * 0.95 ),lf.lfWidth-1);	 
		sz = RectSizeFromFont( pDC, m_pParent, &lf );
		if (lf.lfHeight < 2 || lf.lfWidth < 2 ) break; 
	}

	return lf;
}  


#endif // #if _MFC_VER >= 0x0400   
