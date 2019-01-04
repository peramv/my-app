///////////////////////////////////////////////////////////////////////////////
// gxdtbox.cpp : Calender control
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

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

IMPLEMENT_SERIAL( CGXBPanel, CObject, (DWORD)GXDT_PANEL_SCHEMA )
 
#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDTBOX")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CGXBPanel::CGXBPanel( )
{
	m_bCreated = FALSE;
	m_sLabel = _T("");
	
	m_nBevelLines = 3;
	m_nHighlightLines = 2;
	m_bSelected = FALSE;
	m_bHighlighted = FALSE;
	
	m_iDrawMode = GXDT_PDM_GXDT_DEFAULT_DIALOG_DRAW ;
	
	m_clrOutline = RGB(000,000,000); /* Black */
	m_clrHighlight = RGB(255,000,000);	/* Red */
	m_bNeedMetrics = TRUE;
}

CGXBPanel::~CGXBPanel( )
{
}

BOOL CGXBPanel::Create(CRect r,
					   CWnd *pParent,
					   DWORD dwStyle,
					   UINT nID,
					   BOOL bSelected, 
					   BOOL bHighlighted, 
					   long iDrawMode,
					   long iBehaviorMode,
					   UINT nBevelLines )
{
	ASSERT( !m_bCreated );
	
	BOOL bRetVal = TRUE;
	m_rOuterRect = r;
	m_pParent = pParent;
	m_bSelected = bSelected;
	m_bHighlighted = bHighlighted;
	m_iDrawMode = iDrawMode;
	m_iBehaviorMode = iBehaviorMode;
	m_nBevelLines = nBevelLines;
	m_bCreated = TRUE;
	
	// Based upon our current size, determine the starting & ending diagonal
	// indices for the outline, bevel, face, label, and highlighting.
	GetMetrics();
	
	return bRetVal;
	nID; //unused
	dwStyle; //unused
};

BOOL CGXBPanel::OnDraw(CDC *pDC)
{
	ASSERT( pDC != NULL );
	ASSERT( m_bCreated );
	
	if (m_bNeedMetrics) 
		GetMetrics();

	BOOL bRetVal = TRUE;
	
	// Set Text and background colors, and the font.
	COLORREF oldBkgdColor = pDC->SetBkColor( GXGetSysData()->clrBtnFace );
	COLORREF oldTextColor = pDC->SetTextColor( m_clrText );

	HTHEME	lhTheme = NULL;
	HRESULT	hr = 0;

	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"BUTTON");

	if( lhTheme )
	{
		int iState = PBS_NORMAL/*PBS_HOT*/;

		if( m_bSelected )
			iState = PBS_PRESSED;

		if( !(m_iBehaviorMode & GXDT_PBM_SELECTABLE) )
			iState = PBS_DISABLED;

		hr = RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), BP_PUSHBUTTON, iState, &m_rOuterRect, 0 );

		pDC->SetBkMode( TRANSPARENT );
	}
	else
	{
		// Draw the component parts of a proper CGXBPanel.
		bRetVal = OnDrawOutline( pDC );
		bRetVal     &= OnDrawBevel( pDC );
	}

	bRetVal     &= OnDrawFace( pDC );
	bRetVal     &= OnDrawLabel( pDC );
	bRetVal		&= OnDrawHighlight( pDC );
	
	// Put things back the way they were.
	pDC->SetBkColor( oldBkgdColor );
	pDC->SetTextColor( oldTextColor );

	if( lhTheme )
		RWCloseThemeData( lhTheme );

	return bRetVal;
}

BOOL CGXBPanel::OnDrawOutline(CDC *pDC)
{
	ASSERT( pDC != NULL );
	ASSERT( m_bCreated );
	
	DrawBevelLines( pDC,
		m_clrOutline, 
		m_clrOutline, 
		m_iStartOutline,
		m_iStartBevel);
	return TRUE;
}

BOOL CGXBPanel::OnDrawBevel(CDC *pDC)
{
	ASSERT( pDC != NULL );
	ASSERT( m_bCreated );
	
	COLORREF tl = m_bSelected?GXGetSysData()->clrBtnShadow:GXGetSysData()->clrBtnHilite;
	COLORREF br = m_bSelected?GXGetSysData()->clrBtnHilite:GXGetSysData()->clrBtnShadow;
	DrawBevelLines( pDC, tl, br, m_iStartBevel, m_iStartHighlight );
	return TRUE;
}

BOOL CGXBPanel::OnDrawHighlight(CDC *pDC)
{
	ASSERT( pDC != NULL );
	ASSERT( m_bCreated );
	
	DrawBevelLines( pDC,
		m_clrHighlight, 
		m_clrHighlight, 
		m_iStartHighlight, 
		m_iStartFace ); 
	return TRUE;
}

BOOL CGXBPanel::OnDrawFace(CDC *pDC)
{
	ASSERT( pDC != NULL );
	ASSERT( m_bCreated );
	
	CRect rect = GetFaceRect();
	
	// ExtTextOut() doesn't include bottom & right pixel lines...
	rect.BottomRight().Offset(1,1);

	if( !RWIsAppThemed() || !RWIsThemeActive() )
	pDC->ExtTextOut(0,0,ETO_OPAQUE,rect,NULL,0,NULL);
	
	return TRUE;
}

BOOL CGXBPanel::OnDrawLabel(CDC *pDC)
{
	ASSERT( pDC != NULL );
	ASSERT( m_bCreated );
	
	int xLoc, yLoc;
	TEXTMETRIC tm;
	pDC->GetTextMetrics( &tm );
	CRect theRect = GetFaceRect();
	
	UINT iAlign;
	if ( m_iDrawMode & GXDT_PDM_TEXTCENTERED ) {
		iAlign = TA_CENTER | TA_BASELINE;
		xLoc = theRect.TopLeft().x + theRect.Width()/2;
		yLoc = theRect.TopLeft().y + theRect.Height()/2 + tm.tmAscent/2	;
	} else {
		iAlign = TA_LEFT | TA_TOP ;
		xLoc = theRect.TopLeft().x + theRect.Width()/10;
		yLoc = theRect.TopLeft().y + theRect.Height()/10;
	}
	
	UINT oldAlign = pDC->SetTextAlign( iAlign );
	
	// Text out to box.
	if( RWIsAppThemed() && RWIsThemeActive() )
		pDC->ExtTextOut(xLoc,
						yLoc,
						0,
						theRect,
						m_sLabel.GetBuffer(0),
						m_sLabel.GetLength(),
						NULL);
	else
		pDC->ExtTextOut(xLoc,
			yLoc,
			ETO_OPAQUE,
			theRect,
			m_sLabel.GetBuffer(0),
			m_sLabel.GetLength(),
			NULL);
	
	// Restore things.
	pDC->SetTextAlign( oldAlign );
	return TRUE;
}

CRect CGXBPanel::SetContainerRect(CRect &rect)
{
	ASSERT( m_bCreated );
	
	CRect tmp = m_rOuterRect;
	m_rOuterRect = rect;
	
	m_bNeedMetrics = TRUE;
	
	return tmp;
}

CRect CGXBPanel::GetContainerRect(void)
{
	ASSERT( m_bCreated );
	
	return m_rOuterRect;
}

CRect CGXBPanel::GetFaceRect( void)
{
	ASSERT( m_bCreated );
	
	CRect tmp = m_rOuterRect;
	tmp.TopLeft().x += m_iStartFace;
	tmp.TopLeft().y += m_iStartFace;
	tmp.BottomRight().x -= m_iStartFace;
	tmp.BottomRight().y -= m_iStartFace;
	
	if ( ( tmp.Height() < 0 ) || ( tmp.Width() < 0 ) ) {
		tmp.SetRect(0,0,0,0);
	}
	
	return tmp;		
}

CString	CGXBPanel::SetTextLabel(CString &theLabel)
{
	CString tmp = m_sLabel;
	m_sLabel = theLabel;
	return tmp;
}

CString	CGXBPanel::SetTextLabel(TCHAR *pTheLabel)
{
	CString tmp = m_sLabel;
	m_sLabel = pTheLabel;
	return tmp;
}

CString	CGXBPanel::GetTextLabel()
{
	return m_sLabel;
}

long CGXBPanel::SetDrawMode(long nMode)
{
	long tmp = m_iDrawMode;
	m_iDrawMode = nMode;
	m_bNeedMetrics = TRUE;
	
	return tmp;
}

long CGXBPanel::GetDrawMode()
{
	return m_iDrawMode;
}

long CGXBPanel::SetBehaviorMode(long iBehaviorMode)
{
	long tmp = m_iBehaviorMode;
	m_iBehaviorMode = iBehaviorMode;
	m_bNeedMetrics = TRUE;
	
	return tmp;
}

UINT CGXBPanel::SetBevelLines(UINT nLines)
{
	UINT tmp = m_nBevelLines;
	m_nBevelLines = nLines;
	m_bNeedMetrics = TRUE;
	
	return tmp;
}

UINT CGXBPanel::GetBevelLines()
{
	return m_nBevelLines;
}

UINT CGXBPanel::SetHighlightLines(UINT nLines)
{
	UINT tmp = m_nHighlightLines;
	m_nHighlightLines = nLines;
	m_bNeedMetrics = TRUE;
	
	return tmp;
}

UINT CGXBPanel::GetHighlightLines()
{
	return m_nHighlightLines;
}

BOOL CGXBPanel::SetSelected(BOOL bNewState, BOOL bRedraw)
{
	// We will set this panel to "Selected" if bNewState is TRUE, and to
	// "Unselected" if bNewState is FALSE.  We will redraw the panel if
	// requested by the state of bRedraw.
	BOOL bRetVal = TRUE;
	if ( m_iBehaviorMode & GXDT_PBM_SELECTABLE ) {
		m_bSelected = bNewState;
	} else {
		bRetVal = FALSE;
	}
	
	m_bNeedMetrics = TRUE;
	
	if ( bRedraw && m_bCreated ) {
		CRect r = m_rOuterRect;
		r.InflateRect(1, 1);
		m_pParent->InvalidateRect(r, FALSE);
		m_pParent->UpdateWindow();
	}
	
	return bRetVal;
}

BOOL CGXBPanel::GetSelected()
{
	return m_bSelected;
}

BOOL CGXBPanel::SetHighlight(BOOL bNewState, BOOL bRedraw)
{
	// We will set this panel to "Highlighted" if bNewState is TRUE, and to
	// "Unhighlighted" if bNewState is FALSE.  We will redraw the panel if
	// requested by the state of bRedraw.
	BOOL bRetVal = TRUE;
	if ( m_iBehaviorMode & GXDT_PBM_HIGHLIGHTABLE ) {
		m_bHighlighted = bNewState;
	} else {
		m_bHighlighted = FALSE;
		bRetVal = FALSE;
	}
	
	m_bNeedMetrics = TRUE;
	
	if ( bRedraw && m_bCreated ) {
		CRect r = m_rOuterRect;
		r.InflateRect(1, 1);
		m_pParent->InvalidateRect(r, FALSE);
		m_pParent->UpdateWindow();
	}
	
	return bRetVal;
}

BOOL CGXBPanel::GetHighlight()
{
	return m_bHighlighted;
}

COLORREF CGXBPanel::SetTextColor(COLORREF &clr)
{
	COLORREF tmp = m_clrText;
	m_clrText = clr;
	return tmp;
}

void CGXBPanel::SetGrayTextColor(COLORREF &clr)
{
	m_clrGrayText = clr;
}

COLORREF CGXBPanel::GetGrayTextColor()
{
	return m_clrGrayText;
}

BOOL CGXBPanel::HitTest(const CPoint &pt)
{
	return m_rOuterRect.PtInRect( pt );
}

void CGXBPanel::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	MessageBeep(MB_ICONASTERISK );
	nChar; //unused
	nRepCnt; // unused
	nFlags; // unused
}

void CGXBPanel::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if ( m_iBehaviorMode & GXDT_PBM_AUTOCLOSEABLE ) {
		m_pParent->PostMessage( GXDT_OK );
	}
	nFlags; //unused
	point; //unused
}

void CGXBPanel::OnLButtonDown(UINT nFlags, CPoint point) 
{
	MessageBeep(MB_ICONASTERISK );
	nFlags; //unused
	point; //unused
}

void CGXBPanel::OnRButtonDown(UINT nFlags, CPoint point) 
{
	MessageBeep(MB_ICONASTERISK );
	nFlags; // unused
	point; //unused
}

void CGXBPanel::DrawBevelLines(CDC *pDC, 
							   COLORREF &clrTopLeft,
							   COLORREF &clrBottomRight,
							   UINT nStartOffset,
							   UINT nEndOffset)
{
	ASSERT( pDC != NULL );
	ASSERT( nStartOffset <= nEndOffset );
	
	// if we're not being asked to draw something, skip it!
	if ( nStartOffset == nEndOffset ) return ;
	
	COLORREF oldBkCol = pDC->GetBkColor();
	
	CRect r(m_rOuterRect.left   + nStartOffset,
		m_rOuterRect.top    + nStartOffset,
		m_rOuterRect.right  - nStartOffset + 1,
		m_rOuterRect.bottom - nStartOffset + 1);
	
	for(UINT i=nStartOffset; i<=nEndOffset; i++)
	{
		GXDraw3dRect1(pDC, r, clrTopLeft, clrBottomRight);
		r.InflateRect(-1, -1);
	}
	
	pDC->SetBkColor(oldBkCol);
}

void CGXBPanel::TextCenteredInRect(CDC *pDC,
								   CRect &theRect, 
								   CString& strText)
{
	ASSERT( pDC != NULL );
	
	if ( strText.IsEmpty() || theRect.IsRectEmpty() ) return;
	
	// Install our alignment & colors, while saving the old ones.
	UINT oldAlign = pDC->SetTextAlign( TA_CENTER | TA_BASELINE );
	COLORREF oldBkgdColor = pDC->SetBkColor( GXGetSysData()->clrBtnFace );
	COLORREF oldTextColor = pDC->SetTextColor( m_clrText );
	
	// Determine the text location & alignment
	TEXTMETRIC tm;
	pDC->GetTextMetrics( &tm );
	int xLoc = theRect.TopLeft().x + theRect.Width()/2;
	int yLoc = theRect.TopLeft().y + theRect.Height()/2 + tm.tmAscent/2	;
	
	// Text out to box.
	if( RWIsAppThemed() && RWIsThemeActive() )
		pDC->ExtTextOut(xLoc,yLoc,0,theRect,strText,NULL);
	else
		pDC->ExtTextOut(xLoc,yLoc,ETO_OPAQUE,theRect,strText,NULL);
	
	// Restore things.
	pDC->SetTextAlign( oldAlign );
	pDC->SetBkColor( oldBkgdColor );
	pDC->SetTextColor( oldTextColor );
}

void CGXBPanel::GetMetrics()
{
	// Set the values of each of m_iStartOutline, m_iStartBevel,
	// and m_iStartHighlight.  These determine the thickness of each feature
	// of a panel.  Note that if there is no outline, then m_iStartOutline
	// and m_iStartBevel will be equal, otherwise, they will differ by the
	// number of pixels' width attributable to the outline.
	//
	// The numbers represent a number of pixels along the diagonal.  See
	// the Draw... functions for an example of how this is done.
	m_iStartOutline = 0;
	if ( m_bSelected ) {
		if ( m_iDrawMode & GXDT_PDM_OUTLINEPRESSED ) {
			m_iStartBevel = m_iStartOutline + 1;
		} else {
			m_iStartBevel = m_iStartOutline;
		}
	} else {
		if ( m_iDrawMode & GXDT_PDM_OUTLINERELEASED ) {
			m_iStartBevel = m_iStartOutline + 1;
		} else {
			m_iStartBevel = m_iStartOutline;
		}
	}
	
	if ( m_bSelected ) {
		if ( m_iDrawMode & GXDT_PDM_BEVELPRESSED ) {
			m_iStartHighlight = m_iStartBevel + m_nBevelLines;
		} else {
			m_iStartHighlight = m_iStartBevel;
		}
	} else {
		if ( m_iDrawMode & GXDT_PDM_BEVELRELEASED ) {
			m_iStartHighlight = m_iStartBevel + m_nBevelLines;
		} else {
			m_iStartHighlight = m_iStartBevel;
		}
	}
	
	if ( m_bHighlighted ) {
		if ( m_bSelected ) {
			if (m_iDrawMode & GXDT_PDM_HIGHLIGHTPRESSED) {
				m_iStartFace = m_iStartHighlight + m_nBevelLines;
			} else {
				m_iStartFace = m_iStartHighlight;
				
			}
		} else {
			if (m_iDrawMode & GXDT_PDM_HIGHLIGHTRELEASED) {
				m_iStartFace = m_iStartHighlight + m_nBevelLines;
			} else {
				m_iStartFace = m_iStartHighlight;
			}
		}
	} else {
		m_iStartFace = m_iStartHighlight;
	}
	
	m_bNeedMetrics = FALSE;
}


#ifndef WIN32
int CGXBPanel::GetLogFont(CFont &theFont, LOGFONT* pLogFont)
{   
	ASSERT(theFont.m_hObject != NULL);
	return ::GetObject(theFont.m_hObject, sizeof(LOGFONT), pLogFont);
}
#endif // WIN32



IMPLEMENT_SERIAL( CGXBDayBox, CGXBPanel, GXDT_DAY_SCHEMA )


CGXBDayBox::CGXBDayBox( )
{
	m_ordinal = 0xCDCD;
#ifndef WIN32
	// CTime claims to be 1900-based, but calls mktime, 
	// which is 1970-based!
	m_today = CTime(1970,1,1,1,1,1);
#endif // !WIN32
	
	// If we try to do something date-oriented before this is true, we assert.
	m_bDateInitted = FALSE;
	
}

CGXBDayBox::~CGXBDayBox( )
{
	
}

BOOL CGXBDayBox::Create(CRect rect,
						CGXBCalendar *pParent,
						UINT nID,
						DWORD dwStyle,
						BOOL bSelected,
						BOOL bHighlighted,
						long iDrawMode,
						long iBehaviorMode,
						UINT nBevelLines )
{
	CGXBPanel::Create(rect, 
		(CWnd *)pParent,
		// TODO: PCB: Find out why/how the following two were swapped!  
		dwStyle, 
		nID, 
		bSelected, 
		bHighlighted,
		iDrawMode,
		iBehaviorMode,
		nBevelLines );
	
	return TRUE;
};

#ifdef WIN32
COleDateTime CGXBDayBox::SetDate( COleDateTime date )
#else
CTime        CGXBDayBox::SetDate( CTime        date )
#endif
{
	// Assert that the date for this dayBox has been normalized...
	ASSERT(date.GetHour() == 12 );
	
	// Do not try to set the selected date for a calendar
	// through the m_pSelectedDay()->SetDay(foo);  Do this
	// with CGXBCalendar::SelectDate(foo); This will change
	// the selection pointer to the correct CGXBDayBox, too.
#ifdef WIN32
	COleDateTime tmp = m_today;
#else
	CTime        tmp = m_today;
#endif
	m_today = date;
	m_bDateInitted = TRUE;
	
#if (0)
	TRACE("Initializing %02d/%02d/%04d\n",
		m_today.GetMonth(),m_today.GetDay(),m_today.GetYear());
#endif //(0)
	
	return tmp;
}


// TODO: Provide Dump() implementation for each class.

#ifdef WIN32
const COleDateTime &CGXBDayBox::GetDate( void )
#else
const CTime        &CGXBDayBox::GetDate( void )
#endif
{
	ASSERT( m_bDateInitted );
	
	return m_today;
};

BOOL	CGXBDayBox::GetPrePostState( void )
{
	// A "PrePost" date is one which is on a particular page of the calendar,
	// but belongs to the preceding or following month.  PrePost dates are by
	// default grayed and not selectable or highlightable, although	clicking 
	// one will by default cause the calendar's page to change, and then   
	// highlight the *date* that was clicked upon.
	return m_bPrePost;
};

BOOL	CGXBDayBox::SetPrePostState( BOOL bToWhat )
{
	BOOL bTmp = m_bPrePost;
	m_bPrePost = bToWhat;
	if ( m_bPrePost ) {
		if ( m_iBehaviorMode & GXDT_PBM_PPSELECTABLE )
			m_iBehaviorMode &= ~GXDT_PBM_HIGHLIGHTABLE;
		else
			m_iBehaviorMode &= ~(GXDT_PBM_SELECTABLE | GXDT_PBM_HIGHLIGHTABLE);
	} else {
		m_iBehaviorMode |= (GXDT_PBM_SELECTABLE | GXDT_PBM_HIGHLIGHTABLE);
	}
	return bTmp;
};

BOOL	CGXBDayBox::OnDrawLabel( CDC *pDC )
{
	///////////////////////////////////////////////////////////////////////////
	// Put the date text into the box
	
	// TODO: Make this key off of the settings
	UINT oldAlign = pDC->SetTextAlign( TA_LEFT | TA_TOP );
	
	// Set the text color
	COLORREF oldText;
	if ( m_bPrePost && (m_iDrawMode & GXDT_PDM_PREPOSTGRAYED )){
		oldText = pDC->SetTextColor(m_clrGrayText);
	} else {
		oldText = pDC->SetTextColor(m_clrText);
	}
	
	// Determine the text
	TCHAR dt[20];
	// QA: 31989 - #if Secure Code Cleanup.
	_itot(m_today.GetDay(), dt, 10);
	int nLen = (int)_tcsclen(dt);
	
	// Determine where we'll actually put the text.
	CRect geo = GetFaceRect();
	int xLoc, yLoc;
	if ( m_iDrawMode & GXDT_PDM_TEXTCENTERED ) {
		// Determine the text extent for label placement.
		CSize sz = pDC->GetTextExtent(dt, nLen);
		
		xLoc = geo.TopLeft().x + geo.Width()/2 - sz.cx/2;
		yLoc = geo.TopLeft().y + geo.Height()/2 - sz.cy/2;
	} else {
		xLoc = geo.TopLeft().x + geo.Width()/10;
		yLoc = geo.TopLeft().y + geo.Height()/10;
	}
	
	// Text out to box.
	if( RWIsAppThemed() && RWIsThemeActive() )
		pDC->ExtTextOut( xLoc, yLoc, 0, geo, dt, nLen, NULL );
	else
		pDC->ExtTextOut( xLoc, yLoc, ETO_OPAQUE, geo, dt, nLen, NULL );
	
	// Restore things.
	pDC->SetTextAlign( oldAlign );
	pDC->SetTextColor(oldText);
	
	return TRUE;
}


void CGXBDayBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// We're going to select the currently clicked-upon date.  If this
	// box is pre-post, we will first change the page, then select the 
	// desired date.
#ifdef WIN32
	COleDateTime tmpToday = m_today;
#else
	CTime        tmpToday = m_today;
#endif
	
	if ( m_bPrePost && !(m_iBehaviorMode & GXDT_PBM_PPSELECTABLE) ) {
		if (((CGXBCalendar *)m_pParent)->SetPage(tmpToday, TRUE) == FALSE) {
			return;
		}
	}
	
	if(m_iBehaviorMode & GXDT_BBM_LBUTTONTRACK)
		((CGXBCalendar *)m_pParent)->SelectDate( tmpToday, TRUE );
	else
		((CGXBCalendar *)m_pParent)->ToggleSelectDate( tmpToday );
	
	point;
	nFlags;
}


void CGXBDayBox::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// We're going to highlight the currently clicked-upon date.  If this
	// box is pre-post, we will first change the page, then highlight the 
	// desired date.
#ifdef WIN32
	COleDateTime tmpToday = m_today;
#else
	CTime        tmpToday = m_today;
#endif
	
	if ( m_bPrePost ) {
		if (((CGXBCalendar *)m_pParent)->SetPage(tmpToday, TRUE) == FALSE) {
			return;
		}
	}
	
	((CGXBCalendar *)m_pParent)->ToggleHighlightDate( tmpToday );
	point;
	nFlags;
}


CSize CGXBDayBox::RectSizeFromFont( CDC *pDC, CGXBCalendar* pWnd, LOGFONT *pLf )
{
	ASSERT_VALID(pWnd);
	
	CFont f, *pf;
	if ( pLf != NULL ) {
		VERIFY(f.CreateFontIndirect( pLf ));  // GOOBER
		pf = &f;
	} else {
		pf = pWnd->GetDateFont();
	}
	CFont *pOldFont = pDC->SelectObject( pf );
	
	// "88" is the size of the largest date that could appear.
	CSize s = pDC->GetTextExtent(_T("88"),2 );
	
	CSize szSave = s;
	
	// Want the rect larger than the label, anyways...
	s.cx = int( s.cx * 1.25 );
	s.cy = int( s.cy * 1.25 );
	
	if ( !(m_iDrawMode & GXDT_PDM_TEXTCENTERED) ) {
		// If the label's top-left corner, we want the rect 4x large.
		s.cx = int( s.cx * 1.5 );
		s.cy = int( s.cy * 1.5 );
	}
	
	CSize szBorder = GetBorderSize();
	s.cx = max(s.cx, szSave.cx + szBorder.cx);
	s.cy = max(s.cy, szSave.cy + szBorder.cy);
	
	pDC->SelectObject( pOldFont );
	
	return s;
}

CSize CGXBDayBox::GetBorderSize()
{
	UINT nSize;
	BOOL bSaveSelected  = m_bSelected;
	BOOL bSaveHighlight = m_bHighlighted;
	
	m_bSelected    = TRUE;
	m_bHighlighted = TRUE;
	
	BOOL bSave = SetPrePostState(TRUE);
	m_bNeedMetrics = TRUE;
	GetMetrics();
	nSize = m_iStartFace - m_iStartOutline;
	
	SetPrePostState(FALSE);
	m_bNeedMetrics = TRUE;
	GetMetrics();
	nSize = max(nSize, m_iStartFace - m_iStartOutline);
	
	SetPrePostState(bSave);
	m_bNeedMetrics = TRUE;
	m_bSelected    = bSaveSelected;
	m_bHighlighted = bSaveHighlight;
	
	return CSize(nSize, nSize);
}

LOGFONT CGXBDayBox::FontSizeFromRect(CDC *pDC, LOGFONT *pLf, CRect *pR )
{
	LOGFONT lf;
	if ( pLf == NULL ) {
#ifdef WIN32
		((CGXBCalendar*) m_pParent)->GetDateFont()->GetLogFont(&lf);
#else // !WIN32
		GetLogFont(*(((CGXBCalendar*) m_pParent)->GetDateFont()), &lf);
#endif
	} else {
		lf = *pLf;
	}
	
	CRect r;
	if ( pR == NULL ) {	
		r = GetContainerRect();
	} else {
		r = *pR;
	}
	
	if ( r.IsRectNull() ) {
		lf.lfHeight = lf.lfWidth = 0;
		return lf;
	}
	
	// We will iterate through coarse adjustments, greatly enlarging the font
	// and each time determining the resultant rectangle size until the rect
	// is too big, and then finely shrinking the font until the rectangle is 
	// once again small enough.
	CSize sz;
	sz = RectSizeFromFont( pDC, (CGXBCalendar*) m_pParent, &lf ) ;
	
	// Iterate through larger & larger fonts with a large delta.
	while (	(sz.cx < r.Width()) && (sz.cy < r.Height()) ) {
		lf.lfHeight *= 2; lf.lfWidth *= 2;			// Coarse adjust.
		sz = RectSizeFromFont( pDC, (CGXBCalendar*) m_pParent, &lf ) ;
		//TRACE("Coarse: A font %dx%d yields a rect %dx%d.\n",lf.lfHeight,lf.lfWidth,sz.cy,sz.cx );
	}
	
	// Iterate through smaller & smaller fonts with a small delta.
	while ( sz.cx > r.Width() || sz.cy > r.Height() ) {	// Fine Adjust.
		lf.lfHeight = min(int( lf.lfHeight * 0.9 ),lf.lfHeight-1);
		lf.lfWidth  = min(int( lf.lfWidth  * 0.9 ),lf.lfWidth-1);	 
		sz = RectSizeFromFont( pDC, (CGXBCalendar*) m_pParent, &lf ) ;
		//TRACE("Fine: A font %dx%d yields a rect %dx%d.\n",lf.lfHeight,lf.lfWidth,sz.cy,sz.cx );
		if ( (lf.lfHeight < 1) || (lf.lfWidth < 1) ) break;
		
	}
	
	return lf;
}

void CGXBDayBox::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// Double click should select *and* double click, but the first
	// of the (double) clicks may have deselected the dayBox.
	
	if ( !m_bSelected ) OnLButtonDown( nFlags, point );
	
	CGXBPanel::OnLButtonDblClk(nFlags, point);
}  



/////////////////////////////////////////////////////////////////////////////
// CGXBDayBar

// TODO: Implement Serial in DayBar.

CGXBDayBar::CGXBDayBar()
{
	m_nFirstDayOfWeek = 1; // Default to Sunday
}

CGXBDayBar::~CGXBDayBar()
{
}

void CGXBDayBar::SetFirstDayOfWeek(int nFirstDay)
{
	m_nFirstDayOfWeek = nFirstDay;
}

int CGXBDayBar::GetFirstDayOfWeek() const
{
	return m_nFirstDayOfWeek;
}

/////////////////////////////////////////////////////////////////////////////
// CGXBDayBar message handlers
BOOL	CGXBDayBar::OnDrawLabel( CDC *pDC )
{
	ASSERT( pDC != NULL );
	
	// Determine how much room we have for text.
	CRect geo = GetFaceRect();
	int maxPixWide = geo.Width()-1;
	
	// Create the font for the Day Name labels.
	CFont *pTmpFont = pDC->SelectObject( ((CGXBCalendar*) m_pParent)->GetDayBarFont() );
	
	// hdDay[] holds the horizontal geometries of the day name "cells" in the
	// Calendar.  ( GXDT_HD_DAY_ARRAY comes from the Calendar.h file).
	double hdDay[] = GXDT_HD_DAY_ARRAY;
	
	// Print the day labels.
	CRect tmpRect;
	int index;
	tmpRect.TopLeft().y = geo.TopLeft().y;
	tmpRect.BottomRight().y = geo.BottomRight().y;
	
	CString strDay;
	
	for ( int day = 1 ; day <= 7 ; day++ ) 
	{
		index = (day + m_nFirstDayOfWeek - 2) % 7;
		
		tmpRect.TopLeft().x = geo.TopLeft().x + int(hdDay[day-1]*maxPixWide);
		tmpRect.BottomRight().x = geo.TopLeft().x + int(hdDay[day]*maxPixWide);
		
		VERIFY(CGXBLocale::GetDayName(strDay, index + 1, m_iDrawMode & GXDT_BDM_FULL_DAY_NAMES));
		TextCenteredInRect(pDC, tmpRect, strDay);
	}
	
	// Restore the old font.
	pDC->SelectObject( pTmpFont );
	
	return TRUE;
}

CSize CGXBDayBar::RectSizeFromFont( CDC *pDC, CGXBCalendar* pWnd, LOGFONT *pLf )
{
	ASSERT( pDC != NULL );
	ASSERT_VALID(pWnd);
	
	CFont f, *pf;
	if ( pLf != NULL ) {
		f.CreateFontIndirect( pLf );
		pf = &f;
	} else {
		pf = pWnd->GetDayBarFont();
	}
	CFont *pOldFont = pDC->SelectObject( pf );
	
	CString strDay;
	CSize s;
	
	// "Wed" is the size of the largest date that could appear.
	VERIFY(CGXBLocale::GetDayName(strDay, 4, m_iDrawMode & GXDT_BDM_FULL_DAY_NAMES));
	s = pDC->GetTextExtent(strDay);
	
	// Put things back the way we found 'em.
	pDC->SelectObject( pOldFont );
	
	
	// We want room for seven labels across the bar.
	s.cx *= 7;
	
	return s;
}

LOGFONT CGXBDayBar::FontSizeFromRect( CDC *pDC, LOGFONT *pLf, CRect *pR )
{
	ASSERT( pDC != NULL );
	
	// We will use lf as a temp LOGFONT during the sizing.
	LOGFONT lf;
	if ( pLf == NULL ) {
#ifdef WIN32
		((CGXBCalendar*) m_pParent)->GetDayBarFont()->GetLogFont(&lf);
#else
		GetLogFont(*(((CGXBCalendar*) m_pParent)->GetDayBarFont()), &lf);
#endif
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
	
	// Font-sizing algorithm will
	//	not converge, if the sought-after size is
	// zero, so we anticipate & avoid the situation.
	if ( ( r.Height() == 0 ) || ( r.Width() == 0 ) ) {
		lf.lfHeight = lf.lfWidth = 0;
		return lf;
	}
	
	// We will iterate through coarse adjustments, greatly enlarging the font
	// and each time determining the resultant rectangle size until the rect
	// is too big, and then finely shrinking the font until the rectangle is 
	// once again small enough.
	
	CSize sz = RectSizeFromFont( pDC, (CGXBCalendar*) m_pParent, &lf );
	while (	sz.cx < r.Width() && sz.cy < r.Height() ) {	// Coarse adjust.
		lf.lfHeight *= 2; lf.lfWidth *= 2;			
		sz = RectSizeFromFont( pDC, (CGXBCalendar*) m_pParent, &lf );
	}
	
	while ( sz.cx > r.Width() || sz.cy > r.Height() ) { // Fine Adjust.  
		lf.lfHeight = min(int( lf.lfHeight * 0.9 ),lf.lfHeight-1);
		lf.lfWidth  = min(int( lf.lfWidth  * 0.9 ),lf.lfWidth-1);	 
		sz = RectSizeFromFont( pDC, (CGXBCalendar*) m_pParent, &lf );
		if ( sz.cx < 3 || sz.cy < 3 ) break; 
	}
	
	return lf;
}         



const int CGXBLocale::DaysPerWeek = 7;
const int CGXBLocale::MonthsPerYear = 12;

#ifdef WIN32
// List of type codes for day name (in both abbreviated and full form)
const LCTYPE CGXBLocale::DayNameIds[7][2] = 
{
	LOCALE_SABBREVDAYNAME7, LOCALE_SDAYNAME7,		// Sunday
		LOCALE_SABBREVDAYNAME1, LOCALE_SDAYNAME1,		// Monday
		LOCALE_SABBREVDAYNAME2, LOCALE_SDAYNAME2,		// Tuesday
		LOCALE_SABBREVDAYNAME3, LOCALE_SDAYNAME3,		// Wednesday
		LOCALE_SABBREVDAYNAME4, LOCALE_SDAYNAME4,		// Thursday
		LOCALE_SABBREVDAYNAME5, LOCALE_SDAYNAME5,		// Friday
		LOCALE_SABBREVDAYNAME6, LOCALE_SDAYNAME6		// Saturday
};

// List of type codes for month names (in both abbreviated and full form)
const LCTYPE CGXBLocale::MonthNameIds[12][2] = 
{
	LOCALE_SABBREVMONTHNAME1,  LOCALE_SMONTHNAME1,	// January
		LOCALE_SABBREVMONTHNAME2,  LOCALE_SMONTHNAME2,	// Febuary
		LOCALE_SABBREVMONTHNAME3,  LOCALE_SMONTHNAME3,	// March
		LOCALE_SABBREVMONTHNAME4,  LOCALE_SMONTHNAME4,	// April
		LOCALE_SABBREVMONTHNAME5,  LOCALE_SMONTHNAME5,	// May
		LOCALE_SABBREVMONTHNAME6,  LOCALE_SMONTHNAME6,	// June
		LOCALE_SABBREVMONTHNAME7,  LOCALE_SMONTHNAME7,	// July
		LOCALE_SABBREVMONTHNAME8,  LOCALE_SMONTHNAME8,	// August
		LOCALE_SABBREVMONTHNAME9,  LOCALE_SMONTHNAME9,	// September
		LOCALE_SABBREVMONTHNAME10, LOCALE_SMONTHNAME10,	// October
		LOCALE_SABBREVMONTHNAME11, LOCALE_SMONTHNAME11,	// November
		LOCALE_SABBREVMONTHNAME12, LOCALE_SMONTHNAME12,	// December
};

LCID CGXBLocale::m_lcid = GetUserDefaultLCID();

#else // WIN32

TCHAR *CGXBLocale::dayAbbr[] = {_T(""),_T("Sun"),_T("Mon"),_T("Tue"),
_T("Wed"),_T("Thu"),_T("Fri"),_T("Sat")};
TCHAR *CGXBLocale::dayFull[] = {_T(""), _T("Sunday"), _T("Monday"), _T("Tuesday"),
_T("Wednesday"), _T("Thursday"), _T("Friday"),
_T("Saturday") };

TCHAR *CGXBLocale::monthAbbr[] = {
	_T(""),_T("Jan"),_T("Feb"), _T("March"),
		_T("April"),_T("May"),_T("June"),
		_T("July"),_T("Aug"),_T("Sep"),
		_T("Oct"),_T("Nov"),_T("Dec")
};

TCHAR *CGXBLocale::monthFull[] = {
	_T(""),_T("January"),_T("February"),_T("March"),
		_T("April"),_T("May"),_T("June"),
		_T("July"),_T("August"),_T("September"),
		_T("October"),_T("November"),_T("December")
};
#endif

BOOL AFXAPI CGXBLocale::GetDayName(CString& strDay, int nDay, BOOL bFullName)
{
	TCHAR szDay[256];
	
	ASSERT(nDay >= 1 && nDay <= DaysPerWeek);
	
	if (GetLocaleInfo(m_lcid, DayNameIds[nDay-1][bFullName ? 1 : 0], szDay, sizeof(szDay)) == 0)
	{
		TRACE(_T("CGXBLocale::GetDayName failed.\n"));
		return FALSE;
	}
	
	strDay = szDay;
	
	return TRUE;
}

BOOL AFXAPI CGXBLocale::GetMonthName(CString& strMonth, int nMonth, BOOL bFullName)
{
	TCHAR szMonth[256];
	
	ASSERT(nMonth >= 1 && nMonth <= MonthsPerYear);
	
	if (GetLocaleInfo(m_lcid, MonthNameIds[nMonth-1][bFullName ? 1 : 0], szMonth, sizeof(szMonth)) == 0)
	{
		TRACE(_T("CGXBLocale::GetDayName failed.\n"));
		return FALSE;
	}
	
	strMonth = szMonth;
	
	return TRUE;
}


#endif // #if _MFC_VER >= 0x0400   
