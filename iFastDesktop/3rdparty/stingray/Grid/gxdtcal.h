// This is a part of the Objective Grid C++ Library.
// Copyright © 1999-2004 Quovadx, Inc.  All Rights Reserved.
// 
// 
// This computer software is owned by Quovadx, Inc. and is protected by 
// U.S. copyright laws and other laws and by international treaties. This 
// computer software is furnished by Quovadx, Inc. pursuant to a written 
// license agreement and may be used, copied, transmitted, and stored 
// only in accordance with the terms of such license agreement and with 
// the inclusion of the above copyright notice.  This computer software or 
// any other copies thereof may not be provided or otherwise made available 
// to any other person.
// 
// U.S. Government Restricted Rights.  This computer software: 
//      (a) was developed at private expense and is in all respects the 
//          proprietary information of Quovadx, Inc.; 
//      (b) was not developed with government funds; 
//      (c) is a trade secret of Quovadx, Inc. for all purposes of the 
//          Freedom of Information Act; and 
//      (d) is a commercial item and thus, pursuant to Section 12.212 
//          of the Federal Acquisition Regulations (FAR) and DFAR 
//          Supplement Section 227.7202, Government’s use, duplication or 
//          disclosure of the computer software is subject to the restrictions 
//          set forth by Quovadx, Inc.
//
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Authors: Daniel Jebaraj, Stefan Hoenig
//
// Portions of this code were copied from Objective Toolkit.

// gxdtcal.h : Declarations for the Calendar Control
// 

#ifndef _GXDTCAL_H_
#define _GXDTCAL_H_

#if _MFC_VER >= 0x0400   // only supported for MFC version 4.0 or greater

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// header file

class CGXBCalendar;

#define GXDT_PANEL_SCHEMA					0x0100
#define GXDT_DAY_SCHEMA						0x0100
#define GXDT_CAL_SCHEMA						0x0100

#define GXDT_PANEL_DEBUG						FALSE
//	Drawing mode components.
#define GXDT_PDM_FILLIN						0x0001L
#define GXDT_PDM_BEVELPRESSED					0x0002L
#define GXDT_PDM_BEVELRELEASED				0x0004L
#define GXDT_PDM_OUTLINEPRESSED				0x0008L
#define GXDT_PDM_OUTLINERELEASED				0x0010L
#define GXDT_PDM_HIGHLIGHTPRESSED				0x0020L
#define GXDT_PDM_HIGHLIGHTRELEASED			0x0040L
#define GXDT_PDM_TEXTCENTERED					0x0080L
#define GXDT_PDM_PREPOSTGRAYED				0x0100L

// Behavior mode components
#define GXDT_PBM_TEXTSCALEABLEHEIGHT			0x1000L
#define GXDT_PBM_TEXTSCALEABLEWIDTH			0x2000L
#define GXDT_PBM_SELECTABLE					0x4000L
#define GXDT_PBM_HIGHLIGHTABLE				0x8000L
#define GXDT_PBM_AUTOCLOSEABLE				0x0100L
#define GXDT_PBM_PPSELECTABLE					0x0200L


#define GXDT_PDM_DRAW1 \
			GXDT_PDM_FILLIN | GXDT_PDM_BEVELPRESSED | \
			GXDT_PDM_BEVELRELEASED | GXDT_PDM_OUTLINEPRESSED | \
			GXDT_PDM_OUTLINERELEASED | GXDT_PDM_HIGHLIGHTPRESSED | \
			GXDT_PDM_HIGHLIGHTRELEASED | \
			GXDT_PDM_PREPOSTGRAYED

#define GXDT_PDM_DRAW2 GXDT_PDM_FILLIN | GXDT_PDM_BEVELPRESSED | \
			GXDT_PDM_HIGHLIGHTPRESSED | GXDT_PDM_HIGHLIGHTRELEASED | \
			GXDT_PDM_PREPOSTGRAYED

#define GXDT_PDM_DRAW3 GXDT_PDM_FILLIN | GXDT_PDM_BEVELPRESSED | \
			GXDT_PDM_TEXTCENTERED 

#define GXDT_PDM_GXDT_DEFAULT_VIEW_DRAW GXDT_PDM_DRAW1
#define GXDT_PDM_GXDT_DEFAULT_DIALOG_DRAW GXDT_PDM_DRAW1
#define GXDT_PDM_GXDT_DEFAULT_POPUP_DRAW GXDT_PDM_DRAW3

#define GXDT_PDM_GXDT_DEFAULT_VIEW_PPDRAW GXDT_PDM_FILLIN | GXDT_PDM_PREPOSTGRAYED
#define GXDT_PDM_GXDT_DEFAULT_DIALOG_PPDRAW GXDT_PDM_FILLIN | GXDT_PDM_PREPOSTGRAYED
#define GXDT_PDM_GXDT_DEFAULT_POPUP_PPDRAW GXDT_PDM_FILLIN | GXDT_PDM_PREPOSTGRAYED | \
			GXDT_PDM_TEXTCENTERED

#define GXDT_PBM_GXDT_DEFAULT_VIEW_BEHAVIOR \
			GXDT_PBM_SELECTABLE|GXDT_PBM_HIGHLIGHTABLE
#define GXDT_PBM_GXDT_DEFAULT_DIALOG_BEHAVIOR \
			GXDT_PBM_SELECTABLE | GXDT_PBM_HIGHLIGHTABLE
#define GXDT_PBM_GXDT_DEFAULT_POPUP_BEHAVIOR \
			GXDT_PBM_SELECTABLE

#define GXDT_DP_DEFAULTBEVELLINES		  		2



class CGXBPanel	: public CObject
{
	DECLARE_SERIAL( CGXBPanel ) 
// Construction
public:
	BOOL HitTest( const CPoint &pt );
	CGXBPanel( );
	BOOL	Create( CRect r, 
					CWnd *pParent,
					DWORD dwStyle,
					UINT nID,
					BOOL bSelected = FALSE, 
					BOOL bHighlighted = FALSE, 
					long nDrawMode = GXDT_PDM_GXDT_DEFAULT_DIALOG_DRAW,
					long nBehaviorMode = GXDT_PBM_GXDT_DEFAULT_DIALOG_BEHAVIOR,
					UINT nBevelLines = GXDT_DP_DEFAULTBEVELLINES);

// Attributes
public:
	COLORREF GetGrayTextColor( void );
	void SetGrayTextColor( COLORREF &clr );
	COLORREF SetTextColor( COLORREF &clr );
	CRect SetContainerRect( CRect &rect );
	CRect GetContainerRect( void );
	CRect GetFaceRect( void );
	CString SetTextLabel( CString &theLabel );
	CString SetTextLabel( TCHAR *pszText );
	CString GetTextLabel( void );
	long SetDrawMode( long nMode );
	long GetDrawMode( void );
	UINT SetBevelLines( UINT nLines );
	UINT GetBevelLines( void );
	UINT SetHighlightLines( UINT nLines );
	UINT GetHighlightLines( void );
	BOOL SetSelected( BOOL bSelected, BOOL bRedraw = TRUE );
	BOOL GetSelected( void );
	BOOL SetHighlight( BOOL bHighlight, BOOL bRedraw = TRUE );
	BOOL GetHighlight( void );
	long SetBehaviorMode(long iBehaviorMode);

// Operations
public:
protected:
	void GetMetrics( void );

// Overrides
public:
	virtual BOOL OnDrawHighlight( CDC *pDC );
	virtual BOOL OnDraw( CDC *pDC );
	virtual BOOL OnDrawBevel( CDC *pDC );
	virtual BOOL OnDrawOutline( CDC *pDC );
	virtual BOOL OnDrawFace( CDC *pDC );
	virtual BOOL OnDrawLabel( CDC *pDC );

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBPanel)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXBPanel( );

	void OnLButtonDblClk(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point); 
	void OnRButtonDown(UINT nFlags, CPoint point); 
	void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	COLORREF m_clrGrayText;
	void	TextCenteredInRect( CDC *pDC, CRect &theRect, CString& strText);
	void	DrawBevelLines(	CDC *pDC, 
							COLORREF &topLeft, 
							COLORREF &bottomRight,
							UINT nStartOfOffset,
							UINT nEndOfOffset );
	void	DrawRect(CDC *pDC, 
					 CRect theRect,
					 COLORREF theLineColor);
	
	CWnd *m_pParent;
 	long m_iBehaviorMode;
	long m_iDrawMode;
	CString	m_sLabel;
	CRect m_rOuterRect;
	UINT m_nBevelLines;
	UINT m_nHighlightLines;
	BOOL m_bSelected;
	BOOL m_bHighlighted;
	COLORREF m_clrOutline;
	COLORREF m_clrHighlight;
	COLORREF m_clrText;

protected:
	BOOL m_bNeedMetrics;
	BOOL m_bCreated;
	UINT m_iStartOutline;
	UINT m_iStartBevel;
	UINT m_iStartHighlight;
	UINT m_iStartFace;
};



/////////////////////////////////////////////////////////////////////////////
// CGXBDayBox:
// See CGXBDayBox.cpp for the implementation of this class
//

class CGXBDayBox	: public CGXBPanel
{
	DECLARE_SERIAL( CGXBDayBox ) 
// Construction
public:
	CGXBDayBox( );
	BOOL Create( CRect rect,
				 CGXBCalendar *pParent,
				 UINT nID,
 				 DWORD dwStyle = WS_CHILD|WS_VISIBLE,
				 BOOL bSelected = FALSE,
				 BOOL bHighlighted = FALSE,
				 long iDrawMode = GXDT_PDM_GXDT_DEFAULT_DIALOG_DRAW,
				 long iBehaviorMode = GXDT_PBM_GXDT_DEFAULT_DIALOG_BEHAVIOR,
				 UINT nBevelLines = GXDT_DP_DEFAULTBEVELLINES );
		
// Attributes
public:
#ifdef WIN32
	COleDateTime SetDate( COleDateTime newDate );
	const COleDateTime &GetDate( void );
#else
	CTime SetDate( CTime newDate );
	const CTime &GetDate( void );
#endif
	
	BOOL SetPrePostState( BOOL bToWhat );
	BOOL GetPrePostState( void );

// Operations
public:

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBDayBox)
	//}}AFX_VIRTUAL
 	virtual BOOL OnDrawLabel( CDC *pDC  );

// Implementation
public:
	virtual ~CGXBDayBox( );
	CSize GetBorderSize();
	CSize RectSizeFromFont( CDC *pDC, CGXBCalendar* pWnd, LOGFONT *pLf = NULL );
	LOGFONT	FontSizeFromRect( CDC *pDC, 
							 LOGFONT *pLf = NULL, 
							 CRect *pR = NULL );
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnLButtonDblClk(UINT nFlags, CPoint point);


protected:
	UINT m_ordinal;
#ifdef WIN32
	COleDateTime m_today;
#else
	CTime        m_today;
#endif
	BOOL m_bPrePost;
	BOOL m_bDateInitted;

};


/////////////////////////////////////////////////////////////////////////////
// CGXBDayBar window

class CGXBDayBar : public CGXBPanel
{
// Construction
public:
	CGXBDayBar();

// Attributes
public:

// Operations
public:
	CSize RectSizeFromFont( CDC *pDC, CGXBCalendar* pWnd, LOGFONT *pLf = NULL );
	LOGFONT	FontSizeFromRect( CDC *pDC, 
							  LOGFONT *pLf = NULL, 
							  CRect *pR = NULL );

	virtual BOOL OnDrawLabel( CDC *pDC );
	void SetFirstDayOfWeek(int nFirstDay);
	int GetFirstDayOfWeek() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBDayBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXBDayBar();

	int m_nFirstDayOfWeek;
};


#define GXDT_CALTITLE_SCHEMA 0x0100


class CGXBCalTitle : public CGXBPanel
{
	DECLARE_SERIAL( CGXBCalTitle ) 
// Construction
public:
	CGXBCalTitle();
	BOOL Create( CRect r,
		     CWnd *pParent,
		     DWORD dwStyle,
		     UINT nID,
		     BOOL bPressed, 
		     BOOL bHighlighted, 
		     long iDrawMode,
		     long iBehaviorMode,
		     UINT nBevelLines );
 
// Attributes
public:
	virtual CRect SetContainerRect( CRect &rect );

// Operations
public:
#ifdef WIN32
	virtual BOOL SetPage( const COleDateTime &date );
#else
	virtual BOOL SetPage( const CTime        &date );
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBCalTitle)
	//}}AFX_VIRTUAL
	virtual BOOL OnDraw( CDC *pDC );

// Implementation
public:
	virtual ~CGXBCalTitle();
	CSize RectSizeFromFont( CDC *pDC, CGXBCalendar* pWnd, LOGFONT *pLf = NULL );
	LOGFONT FontSizeFromRect( CDC *pDC, 
							  LOGFONT *pLf = NULL,
							  CRect *pR = NULL );

protected:
	void SizeButtons( void );
	CGXBCalendar *m_pParent;

	CButton	m_btnPrevYear;
	CButton	m_btnPrevMonth;
	CButton	m_btnNextMonth;
	CButton	m_btnNextYear;

	BOOL m_bYearButtons;
	BOOL m_bMonthButtons;

	void OnNextYear();
	void OnPrevYear();
	void OnNextMonth();
	void OnPrevMonth();
};


/////////////////////////////////////////////////////////////////////////////
// CGXBLocale 
//
//   This class aids in internationalization.
//


class CGXBLocale
{
// Construction
public:
	CGXBLocale();

// Attributes
public:

	static const int DaysPerWeek;
	static const int MonthsPerYear;

protected:

#ifdef WIN32	//or WIN64
	static LCID m_lcid;
	static const LCTYPE DayNameIds[7][2];
	static const LCTYPE MonthNameIds[12][2];
#else // WIN32
	static TCHAR *dayAbbr[];
	static TCHAR *dayFull[];
	static TCHAR *monthAbbr[];
	static TCHAR *monthFull[];
#endif


// Operations
public:

	static BOOL AFXAPI GetDayName(CString& strDay, int nDay, BOOL bFullName = TRUE);
	static BOOL AFXAPI GetMonthName(CString& strMonth, int nMonth, BOOL bFullName = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBDayBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXBLocale();

};

class CGXBCalendar;


// Behavior options. High 16 bits describe overall calendar modes,
// low 16 bits describe component behavior modes.
#define GXDT_BBM_AUTOSIZE_FONT				0x00010000L
#define GXDT_BBM_AUTOSIZE_RECT				0x00020000L 
#define GXDT_BBM_SINGLE_DATE				0x00040000L
#define GXDT_BBM_MONTH_BUTTONS				0x00080000L
#define GXDT_BBM_YEAR_BUTTONS				0x00100000L
#define GXDT_BBM_KEYBOARD_CONTROL			0x00200000L
#define GXDT_BBM_MONTH_FROZEN				0x00400000L
#define GXDT_BBM_AUTO_HIDE					GXDT_PBM_AUTOCLOSEABLE
#define GXDT_BBM_LBUTTONTRACK				0x01000000L

// Not yet implemented.
#define GXDT_BBM_RESIZEABLE				0x00800000L

// Draw options. High 16 bits describe overall calendar modes,
// low 16 bits describe component behavior modes.
#define GXDT_BDM_FULL_MONTH_NAMES			0x10000000L
#define GXDT_BDM_FULL_DAY_NAMES			0x20000000L
  
// Styles for CGXBPopupCalendar
#define GXDT_PCS_ALIGNBOTTOMLEFT			0x0001		// Align calendar at bottom
													// left of supplied rect.

/*
// Calendar-control-to-parent messages.
#define GXDT_DATESELECTED				(WM_USER+1)
#define GXDT_HIGHLIGHTLISTCHANGED		(WM_USER+2)
#define GXDT_OK							(WM_USER+3)
#define GXDT_CANCEL						(WM_USER+4)
// moved to gxmsg.h
*/

// Defaults
#define GXDT_DEFAULT_DAY_BKGD_COLOR			COLOR_WINDOW	
#define GXDT_DEFAULT_DAY_PRE_POST_BKGD_COLOR	COLOR_BTNSHADOW			
#define GXDT_DEFAULT_DAYBAR_BKGD_COLOR		COLOR_BTNFACE
#define GXDT_DEFAULT_DAYBAR_FGD_COLOR		COLOR_BTNTEXT
#define GXDT_DEFAULT_TITLE_BKGD_COLOR		COLOR_ACTIVECAPTION
#define GXDT_DEFAULT_TITLE_FGD_COLOR			COLOR_CAPTIONTEXT
#define GXDT_DEFAULT_LINES_COLOR				COLOR_BTNTEXT
#define GXDT_DEFAULT_SELECTED_COLOR			COLOR_BKGD
#define GXDT_DEFAULT_HIGHLIGHTED_COLOR		COLOR_HIGHLIGHT
#define GXDT_DEFAULT_TEXT_COLOR				COLOR_WINDOWTEXT
#define GXDT_DEFAULT_GRAYTEXT_COLOR			COLOR_GRAYTEXT

#define GXDT_BBM_GXDT_DEFAULT_VIEW_BEHAVIOR \
			GXDT_PBM_GXDT_DEFAULT_VIEW_BEHAVIOR | GXDT_BBM_AUTOSIZE_FONT | \
			GXDT_BBM_YEAR_BUTTONS |GXDT_BBM_MONTH_BUTTONS | GXDT_BBM_KEYBOARD_CONTROL 

#define GXDT_BBM_GXDT_DEFAULT_DIALOG_BEHAVIOR GXDT_PBM_GXDT_DEFAULT_DIALOG_BEHAVIOR | \
		GXDT_BBM_AUTOSIZE_FONT | GXDT_BBM_YEAR_BUTTONS | GXDT_BBM_MONTH_BUTTONS | \
		GXDT_BBM_KEYBOARD_CONTROL 
									  
#define GXDT_BBM_GXDT_DEFAULT_POPUP_BEHAVIOR GXDT_PBM_GXDT_DEFAULT_DIALOG_BEHAVIOR | \
			GXDT_BBM_AUTOSIZE_FONT | GXDT_BBM_YEAR_BUTTONS | GXDT_BBM_MONTH_BUTTONS | \
			GXDT_BBM_KEYBOARD_CONTROL | GXDT_BBM_AUTO_HIDE

#define GXDT_BDM_GXDT_DEFAULT_VIEW_DRAW GXDT_PDM_GXDT_DEFAULT_VIEW_DRAW | \
			GXDT_BDM_FULL_MONTH_NAMES | GXDT_BDM_FULL_DAY_NAMES
#define GXDT_BDM_GXDT_DEFAULT_DIALOG_DRAW GXDT_PDM_GXDT_DEFAULT_DIALOG_DRAW | \
			GXDT_BDM_FULL_MONTH_NAMES
#define GXDT_BDM_GXDT_DEFAULT_POPUP_DRAW GXDT_PDM_GXDT_DEFAULT_POPUP_DRAW

#define GXDT_BDM_GXDT_DEFAULT_VIEW_PPDRAW GXDT_PDM_GXDT_DEFAULT_VIEW_PPDRAW
#define GXDT_BDM_GXDT_DEFAULT_DIALOG_PPDRAW GXDT_PDM_GXDT_DEFAULT_DIALOG_PPDRAW
#define GXDT_BDM_GXDT_DEFAULT_POPUP_PPDRAW GXDT_PDM_GXDT_DEFAULT_POPUP_PPDRAW



#define CGXBC_NUMDAYS					42				 //7 days x 6 wks. 
#define CGXBC_GXDT_DEFAULT_FONT				_T("Arial")

// Geometry of the Calendar
#define GXDT_VD_TOP							0.000
#define GXDT_VD_TITLE						0.175
#define	GXDT_VD_WK_0							0.250
#define GXDT_VD_WK_ARRAY						{ 0.250,0.375,0.500,0.625,\
												0.750,0.875,1.000}

#define GXDT_HD_LEFT							0.000
#define GXDT_HD_TITLE						1.000
#define GXDT_HD_DAYBAR						1.000
#define GXDT_HD_DAY_ARRAY					{0.000, 0.143, 0.286, 0.429,\
										 0.572, 0.715, 0.858, 1.000}


/////////////////////////////////////////////////////////////////////////////
// CGXBCalendar:
// See Calendar.cpp for the implementation of this class
//
class CGXBDayBox;
class CGXBDayBar;
class CGXBCalTitle;

class CGXBCalendar : public CWnd
{
	DECLARE_SERIAL( CGXBCalendar ) 
// Implementation

	//{{AFX_MSG(CGXBCalendar)
	afx_msg void OnPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNextYear(); 
	afx_msg void OnPrevYear(); 
	afx_msg void OnNextMonth();
	afx_msg void OnPrevMonth();
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	afx_msg LRESULT OnOK(WPARAM u, LPARAM l);
	afx_msg LRESULT OnCancel(WPARAM u, LPARAM l);
	DECLARE_MESSAGE_MAP()

// Construction
public:
	CGXBCalendar( );
	virtual BOOL Create(	DWORD dwStyle, 
							CRect &Rect, 
							CWnd *pWndParent, 
							UINT nID,
							CCreateContext* pContext = NULL );


// Attributes
public:
	long GetPrePostDrawMode( void );
	BOOL SetPrePostDrawMode( long l );
	long GetBehaviorMode( void );
	BOOL SetBehaviorMode( long m );
	BOOL FAR SetDrawMode( long m );
	long GetDrawMode( void );
#ifdef WIN32	//or WIN64
	BOOL SetPage( const COleDateTime &calendarPage, BOOL bRedraw = FALSE );
	const COleDateTime& GetSelectedDateValue( void );
	UINT GetAllHighlightedDates( COleDateTime *pDates, UINT nDates );
#else
	const CTime& GetSelectedDateValue( void );
#endif
	UINT GetAllHighlightedDates( CTime *pDates, UINT nDates );
	BOOL SetPage( const CTime &calendarPage, BOOL bRedraw = FALSE );
	BOOL MarkDate( const CTime &date, BOOL bSelectIt );
	CGXBDayBox *GetSelectedDate( void );
	UINT GetNumHighlightedDates( void );
	BOOL GetAutosizeFont( void );
	BOOL GetAutosizeRect( void );
	void SetAutosizeRect( BOOL bSet );
	void SetAutosizeFont( BOOL bSet );
	const CRect	&GetControlRect( void );
	CRect SetControlRect( CRect &newRect );
	BOOL GetSingleDate( void );
	BOOL SetSingleDate( BOOL bTurnOn );
	BOOL GetMonthButtons( void );
	BOOL SetMonthButtons( BOOL bTurnOn );
	BOOL GetYearButtons( void );
	BOOL SetYearButtons( BOOL bTurnOn );
	BOOL GetKeyboardControl( void );
	BOOL SetKeyboardControl( BOOL bTurnOn );
	BOOL GetMonthFrozen( void );
	BOOL SetMonthFrozen( BOOL bMakeFrozen );
	BOOL GetAutoHide( void );
	BOOL SetAutoHide( BOOL bHideAutomatically );
	UINT GetAlignmentFlag( void );
	UINT SetAlignmentFlag( UINT lNewFlag );
	CWnd *GetNotifyWnd( void );
	void SetNotifyWnd( CWnd *pWnd );
	COLORREF SetTextColor( COLORREF newColor );
	COLORREF GetTextColor( void );
	void SetFirstDayOfWeek(int nNewFirstDay, BOOL bRedraw = FALSE);
	int GetFirstDayOfWeek() const;


// Operations
public:
	virtual BOOL AdvanceDay( BOOL bSelectionFollows = TRUE );
	virtual BOOL RetreatDay(  BOOL bSelectionFollows = TRUE );
	virtual BOOL AdvanceWeek( BOOL bSelectionFollows = TRUE );
	virtual BOOL RetreatWeek(  BOOL bSelectionFollows = TRUE );
	virtual BOOL AdvanceMonth( BOOL bSelectionFollows = FALSE );
	virtual BOOL RetreatMonth(  BOOL bSelectionFollows = FALSE );
	virtual BOOL AdvanceYear(  BOOL bSelectionFollows = FALSE );
	virtual BOOL RetreatYear(  BOOL bSelectionFollows = FALSE );
#ifdef WIN32	//or WIN64
	virtual BOOL DeltaSelection( COleDateTimeSpan &ts );
	virtual BOOL DeltaPage( COleDateTimeSpan &ts );
	virtual	BOOL HighlightDate( COleDateTime &date, BOOL bSet );
	virtual	BOOL SelectDate( COleDateTime date, BOOL bSet );
	virtual	BOOL ToggleSelectDate( COleDateTime &date );
	virtual	BOOL ToggleHighlightDate( COleDateTime &date );
#endif
	virtual BOOL DeltaSelection( CTimeSpan &ts );
	virtual BOOL DeltaPage( CTimeSpan &ts );
	virtual	BOOL HighlightDate( CTime &date, BOOL bSet );
	virtual	BOOL SelectDate( CTime date, BOOL bSet );
	virtual	BOOL ToggleSelectDate( CTime &date );
	virtual	BOOL ToggleHighlightDate( CTime &date );
	void Serialize( CArchive &ar );

protected:
	void PurgeDateList( void );
	virtual BOOL IsDisplayableDate( int year, int month, int day );


// Overrideables
public:
	virtual void InitColors();

// Implementation
public:
	virtual	~CGXBCalendar( );
	void TextCenteredInRect( CDC *pDC, 
							 CRect theRect, 
							 COLORREF clrFgnd, 
							 COLORREF clrBkgd,
							 CString& strText);

	CGXBDayBar m_pnlDayBar;
	CGXBCalTitle m_pnlTitle;

protected:
#ifdef WIN32	//or WIN64
	void NormalizeDate( COleDateTime &date );
	BOOL DateFoundInList( COleDateTime date );
	BOOL RemoveDateFromList( COleDateTime date );
	BOOL AddDateToList( COleDateTime date );
#else
	void NormalizeDate( CTime &date );
	BOOL DateFoundInList( CTime date );
	BOOL RemoveDateFromList( CTime date );
	BOOL AddDateToList( CTime date );
#endif
	virtual void OnDatePegged( void );
	UINT m_nBevelLines;
	virtual UINT GetClassStyle( void );
	CWnd *m_pNotifyWnd;
	void AdjustFontSizes( CDC *pDC = NULL );
	void AdjustRectSizes( CRect &r, CDC *pDC = NULL );
	CWnd *m_pParent;
	void SizeTitle( void );
	void SizeDayBar( void );
	void SizeDates( void );
	void InitFonts( void );
	void SetUpDateBoxes( void );
	void PaintDates( CDC *pDC );
	enum deltaDate { negYear, negMonth, negDay, Day, Month, Year };

protected:
	BOOL m_bCreated;
#ifdef _DEBUG
	void DumpDateList( void );
#endif

#ifdef WIN32	//or WIN64
	COleDateTime m_page;
	COleDateTime m_selection;
	COleDateTime *m_pSelection;
	COleDateTime m_phantomSelection;
#else
	CTime        m_page;
	CTime        m_selection;
	CTime        *m_pSelection;
	CTime        m_phantomSelection;
#endif

	CGXBDayBox m_day[CGXBC_NUMDAYS];
	CGXBDayBox *m_pSelectedDay;

	UINT	m_nOpMode;
	UINT	m_nAlignment;

	BOOL	m_bFullMonthNames;
	BOOL	m_bFullDayNames;

	BOOL	m_bCapture;
	BOOL    m_bDaySaved;
#ifdef WIN32	//WIN64
	COleDateTime m_SaveSelectedDay;
#else
	CTime        m_SaveSelectedDay;
#endif

	CObList m_HltDateList;

	LOGFONT	m_lfTitleFont;
	LOGFONT	m_lfDayFont;
	LOGFONT	m_lfDateFont;
	CFont   m_TitleFont;
	CFont	m_DayFont;
	CFont   m_DateFont;

public:
	CFont* GetTitleFont() { return &m_TitleFont; }
	CFont* GetDayBarFont() { return &m_DayFont; }
	CFont* GetDateFont() { return &m_DateFont; }

protected:
	COLORREF m_clrText;
	COLORREF m_clrLines;
	COLORREF m_clrDayBarText;
	COLORREF m_clrDayBarFace;
	COLORREF m_clrTitleText;
	COLORREF m_clrTitleFace;
	COLORREF m_clrGrayText;

	long m_iPrePostDrawMode;
	long m_iDrawMode;
	long m_iPrePostBehaMode;
	long m_iBehaMode;
};


/////////////////////////////////////////////////////////////////////////////
// CGXBPopupCalendar window

class CGXBPopupCalendar : public CGXBCalendar
{

	DECLARE_SERIAL(CGXBPopupCalendar);
	
	//{{AFX_MSG(CGXBPopupCalendar)
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Construction
public:
	CGXBPopupCalendar( );
	virtual BOOL Create(DWORD dwStyle, 
						CRect &buttonRect, 
						CWnd *pParentWnd, 
						CCreateContext *pContext = NULL);

// Attributes
public:
	long SetHideMode( long okOrCancel ); // IDOK or IDCANCEL
	virtual UINT GetClassStyle( void );

// Operations
public:
	void Serialize( CArchive &ar );


// Overridables
public:

// Implementation
public:
	virtual ~CGXBPopupCalendar( );

protected:
	BOOL m_bHideDoesOK;
};

// CGXBDateTimeCtrl styles
#define GXDT_DTS_CALENDAR		0x0001L
#define GXDT_DTS_UPDOWN			0x0002L
#define GXDT_DTS_Y2K_NOFIX		0x0010L		// overrides Y2K fix (backward compatibility)
#define GXDT_DTS_Y2K_CONTEXT	0x0020L     // base Y2K reference year on current date in control


// CGXBDateTimeCtrl notifications
#define GXDT_DTN_CHANGED		0x0100

// CGXBDateTimeCtrl Gadget IDs (bit settings)
#define GXDT_DTID_12HOUR		0x0001
#define GXDT_DTID_24HOUR		0x0002
#define GXDT_DTID_MINUTE		0x0004
#define GXDT_DTID_SECOND		0x0008
#define GXDT_DTID_AMPM		0x0010
#define GXDT_DTID_DAYNO		0x0020
#define GXDT_DTID_DAYNAME		0x0040
#define GXDT_DTID_MONTHNO		0x0080
#define GXDT_DTID_MONTHNAME	0x0100
#define GXDT_DTID_YEAR2		0x0200
#define GXDT_DTID_YEAR4		0x0400
#define GXDT_DTID_CALDROPDOWN	0x4000
#define GXDT_DTID_SPINNER		0x8000
#define GXDT_DTID_ALL			0xffff


// Forward references
class CGXBPopupCalendar;


// Gadget notifications
#define GXDT_GN_INCREMENT		0x0001
#define GXDT_GN_DECREMENT		0x0002
#define GXDT_GN_SPINUP		0x0003
#define GXDT_GN_SPINDOWN		0x0004
#define GXDT_GN_DROPDOWN		0x0005
#define GXDT_GN_VALIDATE		0x0006
#define GXDT_GN_MODIFY		0x0007
#define GXDT_GN_MINIMUM		0x0008
#define GXDT_GN_MAXIMUM		0x0009
#define GXDT_GN_EDIT			0x000a
#define GXDT_GN_NUMERIC_DONE	0x000b

// Forward references
class CGXBDateTimeCtrl;


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//  class CGXBDTGadget 
//  
//  Abstract base class for the gadget components used by CGXBDateTimeCtrl
//
class CGXBDTGadget : public CObject
{

DECLARE_DYNAMIC(CGXBDTGadget)
// Construction
public:
	CGXBDTGadget();

	// Initialises the gadget.
	BOOL Initialise(CGXBDateTimeCtrl* pCtrl, int nID = -1);

// Attributes
public:
	enum	// Style flags (for m_style and GetStyle/SetStyle)
	{
		WantFocus = 0x0001,		// Gadget accepts focus (i.e. can be enabled)
		WantMouse = 0x0002,		// Gadget wants mouse clicks
		IsFixed   = 0x0004		// Gadget is not moveable (fixed to right edge
	};							// of control)

// Operations
public:
	// Set/Get the style flags for this gadget.
	int  GetStyle() const;
	void SetStyle(int style);

	// Set/Get the current value of the gadget
	void SetValue(int nNewValue);
	int  GetValue() const;

	// Returns the gadget's ID;
	int GetID() const;

	// Set/Get the gadget's rectangle (relative to CGXBDateTimeCtrl's client)
	const CRect& GetRect() const;
	void SetRect(const RECT& rect);

// Overrideables
public:
	// Function to calculate the required size of the gadget
	virtual void CalcSize(CDC& dc) = 0;

	// Function to draw the gadget
	virtual void Draw(CDC& dc) = 0;

	// Function to enable (give focus to) the gadget (returns FALSE if fails)
	virtual BOOL Enable(BOOL bEnable);

	// Handlers for WM_KEYDOWN/WM_CHAR messages while gadget is enabled
	virtual void OnKeyDown(UINT /* nChar */) {}
	virtual void OnChar(UINT /* nChar */) {}

	// Handler for mouse messages while gadget is enabled (only if
	// style has WantMouse flag).
	virtual void OnLButtonDown(UINT /* nFlags */, CPoint /* point */) {}
	virtual void OnLButtonUp(UINT /* nFlags */, CPoint /* point */) {}
	virtual void OnMouseMove(UINT /* nFlags */, CPoint /* point */) {}
	virtual void OnCancelMode() {}

	// Handles timer events requested by this gadget
	virtual void OnTimer() {}

	// Handler for the WM_SYSCOLORCHANGE message (each gadget receives it)
	virtual void OnSysColorChange() {}

// Implementation
public:
	virtual ~CGXBDTGadget();

protected:
	// Passes notify events to parent
	BOOL Notify(UINT uNotifyCode, int nID, LPARAM lParam = 0L);

	// Invalidates this gadget.
	void Invalidate(BOOL bImmediateRedraw = FALSE);

	// Returns the background color to use
	COLORREF GetBkColor() const;
		
	// Set capture to this gadget
	void CaptureMouse(BOOL bSet);

	// Functions for manipulating timer events
	void StartTimer(UINT uElapse /* ms */);
	void StopTimer();

	// Callback function used for timer events.
	static void CALLBACK EXPORT TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, 
										  DWORD dwTime);

// Implementation - data members
protected:
	CRect               m_rect;			// Gadget window rect (relative to
										// CGXBDateTimeCtrl's client)
	BOOL                m_bEnabled;		// TRUE if we are enabled (have focus)
	int                 m_style;		// Holds style flags
	int                 m_nID;			// This gadgets ID
	int                 m_nValue;		// This gadgets current value
	CGXBDateTimeCtrl*    m_pCtrl;		// Parent CGXBDateTimeCtrl
	static CMapWordToOb m_timers;		// Maps current timers onto gadgets
};


/////////////////////////////////////////////////////////////////////////////
//  class CGXBDTStaticGadget
//  
//  Class implementing a non-editable text gadget for CGXBDateTimeCtrl
//
class CGXBDTStaticGadget : public CGXBDTGadget
{
DECLARE_DYNAMIC(CGXBDTStaticGadget)
// Construction
public:
	CGXBDTStaticGadget();

	// Initialises the static gadget (and define the caption)
	BOOL Initialise(CGXBDateTimeCtrl* pCtrl, LPCTSTR lpszCaption, 
					int nID = -1);

// Attributes
public:

// Operations
public:
	// Function to return the caption
	CString GetCaption() const;

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	virtual void Draw(CDC& dc);

// Implementation
public:
	virtual ~CGXBDTStaticGadget();

// Implementation - data members
protected:
	CString m_strCaption;				// Text of caption
};


/////////////////////////////////////////////////////////////////////////////
//  class CGXBDTNumericGadget
//  
//  Class implementing an editable numeric gadte for CGXBDateTimeCtrl
//
class CGXBDTNumericGadget : public CGXBDTGadget
{
DECLARE_DYNAMIC(CGXBDTNumericGadget)
// Construction
public:
	CGXBDTNumericGadget();

	// Initialise the numeric gadget.
	BOOL Initialise(CGXBDateTimeCtrl* pCtrl, int nMin, int nMax, int nValue, 
					BOOL bLeadZero, int nID = -1);

// Attributes
public:

// Operations
public:

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	virtual void Draw(CDC& dc);
	
	// Function to enable (give focus to) the gadget (returns FALSE if fails)
	virtual BOOL Enable(BOOL bEnable);

	// Handlers for WM_KEYDOWN and WM_CHAR when gadget is enabled
	virtual void OnKeyDown(UINT nChar);
	virtual void OnChar(UINT nChar);

	// Handler for WM_CANCELMODE
	virtual void OnCancelMode();

// Implementation
public:
	virtual ~CGXBDTNumericGadget();

protected:
	// Validate's keyboard entry of new date
	BOOL Validate();

// Implementation - data members
protected:
	int  m_nMin;				// Minimum value
	int  m_nMax;				// Maximum value
	int  m_nWidth;				// Maximum no. of chars. allowed
	int  m_nNewValue;			// New value (used during keyboard entry)
	int  m_nCurDigit;			// Current digit being editted
	BOOL m_bLeadZero;			// TRUE if value is to be displayed with
								// leading zero
};


/////////////////////////////////////////////////////////////////////////////
//  class CGXBDTListGadget
//  
//  Class implementing a text gadget with a defined list of possible strings
//
class CGXBDTListGadget : public CGXBDTGadget
{
DECLARE_DYNAMIC(CGXBDTListGadget)
// Construction
public:
	CGXBDTListGadget();

	// Initialise the list gadget
	BOOL Initialise(CGXBDateTimeCtrl* pCtrl, const CStringArray& list, 
					int nValue, int nID = -1);

// Attributes
public:

// Operations
public:

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	virtual void Draw(CDC& dc);
	
	// Function to enable (give focus to) the gadget (returns FALSE if fails)
	virtual BOOL Enable(BOOL bEnable);

	// Handlers for WM_KEYDOWN and WM_CHAR when gadget is enabled
	virtual void OnKeyDown(UINT nChar);
	virtual void OnChar(UINT nChar);

	// Handler for timer events
	virtual void OnTimer();

// Implementation
public:
	virtual ~CGXBDTListGadget();

protected:
	int FindMatch(LPCTSTR lpszPat, int nCurPos);

// Implementation - data members
protected:
	CStringArray m_list;				// List of possible string
	TCHAR        m_cBuf[3];				// Used during entry of Multi-Byte
										// character
	CString      m_strPat;				// Holds string entered so far 
										// (during partial match)
	BOOL         m_bTimerRunning;		// TRUE when we have a timer enabled
};


/////////////////////////////////////////////////////////////////////////////
//  class CGXBDTButtonGadget
//  
//  Class implementing a simple push button gadget for CGXBDateTimeCtrl
//
class CGXBDTButtonGadget : public CGXBDTGadget
{
DECLARE_DYNAMIC(CGXBDTButtonGadget)
// Construction
public:
	CGXBDTButtonGadget();

	BOOL Initialise(CGXBDateTimeCtrl* pCtrl, LPCTSTR lpszBmpName, 
					int nID = -1);

// Attributes
public:
	enum				// State flags (see m_nState)
	{
		Capture = 0x0001,			// We currently have capture (tracking
									// button press)
		Down    = 0x0002			// The button is currently pressed
	};

// Operations
public:

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	virtual void Draw(CDC& dc);

	// Handlers for mouse messages while we are enabled
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnCancelMode();

	// Handler for WM_SYSCOLORCHANGE
	virtual void OnSysColorChange();

// Implementation
public:
	virtual ~CGXBDTButtonGadget();

// Implementation - data members
protected:
	int     m_nState;				// State information
	CBitmap m_bmp;					// Bitmap displayed on button
	LPCTSTR m_lpszBmpName;			// Resource ID of bitmap
};


/////////////////////////////////////////////////////////////////////////////
//  class CGXBDTSpinGadget
//  
//  Class implementing a spin button gadget for use with CGXBDateTimeCtrl
//
class CGXBDTSpinGadget : public CGXBDTGadget
{
	DECLARE_DYNAMIC(CGXBDTSpinGadget)
// Construction
public:
	CGXBDTSpinGadget();

// Attributes
public:
	enum							// State flags (see m_nState)
	{	
		SpinUp       = 0x0001,		// The spin up button is currently pressed
		SpinDown     = 0x0002,		// The spin down button is currently pressed
		CaptureUp    = 0x0004,		// We are tracking press of spin up btn
		CaptureDown  = 0x0008,		// We are tracking press of spin down btn
		TimerRunning = 0x0010,		// We have a timer running
		InitialTimer = 0x0020		// The timer has been initialised (first
	};								// tick = 500ms, subsequent ticks = 100ms).

// Operations
public:

// Overrideables
protected:
	// Function to calculate the required size of the gadget
	virtual void CalcSize(CDC& dc);

	// Function to draw the gadget
	virtual void Draw(CDC& dc);

	// Handlers for mouse messages while we are enabled
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnCancelMode();

	// Handler for timer events
	virtual void OnTimer();

// Implementation
public:
	virtual ~CGXBDTSpinGadget();

protected:
	// Draws either up or down spin button
	void DrawPart(CDC& dc, CRect& r, BOOL bInvert, BOOL bDown);

	// Returns 0 if point is on spin up button, 1 if on spin down, else -1
	int  CheckHit(CPoint point) const;

// Implementation - data members
protected:
	int      m_nState;					// Holds state information
	SEC_UINT m_nTimer;					// Timer tick count

//used to specify timing for spinner
protected:
	virtual int GetInitialTimerValue();
	virtual int GetNormalTimerValue();

};


/////////////////////////////////////////////////////////////////////////////
// CGXBDateTimeCtrl window
//    
class CGXBDateTimeCtrl : public CWnd
{
	DECLARE_DYNAMIC(CGXBDateTimeCtrl)

// Construction
public:
	CGXBDateTimeCtrl();

	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, 
				CCreateContext* pContext = NULL);
	BOOL CreateEx(DWORD dwExStyle, DWORD dwStyle, const RECT& rect, 
				  CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

// Attributes
public:
	// Control format type as used by Get/SetFormat.
	enum FormatType
	{
		Time,							// Locale time format
		ShortDate,						// Locale short date format 
		LongDate,						// Locale long date format
		Custom,							// A user supplied date/time format 
		DateTime						// Locale short date + locale time
	};									

	// The validation types as used by Get/SetMinMax
	enum ValidationMode
	{
		NoValidation,					// No validation is required
		TimeValidation,					// Validation of time fields only
		DateValidation,					// Validation of date fields only
		DateTimeValidation				// Validation of date & time fields
	};

	// Definitions of non-editable fields as used by Get/SetNoEdit
	enum NoEdit
	{
		FixedYear   = 0x0001,			// The year is non-editable
		FixedMonth  = 0x0002,			// The month is non-editable
		FixedDay    = 0x0004,			// The day is non-editable
		FixedHour   = 0x0008,			// The hour is non-editable
		FixedMinute = 0x0010,			// The minute is non-editable
		FixedSecond = 0x0020			// The second is non-editable
	};

// Operations
public:
	// Forcing a given gadget to be redrawn
	void InvalidateGadget(CGXBDTGadget* pGadget, BOOL bImmediateRedraw = FALSE);
	void InvalidateGadget(int nIndex, BOOL bImmediateRedraw = FALSE);

	// Return the index of the gadget at the given point
	int  GadgetFromPoint(CPoint point);

	// Bring a given gadget into the displayable portion of the window
	void BringIntoView(CGXBDTGadget* pGadget);
	void BringIntoView(int nIndex);

	// Set/Get the current date/time format
	void SetFormat(FormatType format);
	void SetFormat(LPCTSTR lpszFormat);
	void GetFormat(FormatType& format) const;
	void GetFormat(CString& format) const;

	// Functions for enabling fast input. With fast input enabled, when a 
	// numeric field has received a valid input (it's maximum number of
	// digits), it advances input focus to the next field.
	// virtual so that CGXDateTimeCtrl can supply the UA value instead
	void EnableFastEntry(BOOL bEnable = TRUE);
	virtual BOOL IsFastEntryEnabled() const;

	// Tells if the current gadget the right most or left most gadget that 
	// wants the focus

	BOOL IsFocusOnRightMostGadget() const;
	BOOL IsFocusOnLeftMostGadget() const;


	// Force the control to re-size to fit it's contents exactly
	void SizeToContent();

	// Set/Determine the current modified state.
	void SetModified(BOOL bModified);
	void SetModified(BOOL bDate, BOOL bTime);
	BOOL IsModified() const;
	void IsModified(BOOL& bDate, BOOL& bTime) const;

	// Returns TRUE if the user is currently in the middle of editting one
	// of the numeric fields
	BOOL IsEditing() const;

	// Set/Get the current date and time
	BOOL SetDateTime(const COleDateTime& datetime);
	BOOL SetDate(const COleDateTime& date);
	BOOL SetTime(const COleDateTime& time);
	const COleDateTime& GetDateTime() const;

	// Set/Get the current validation mode and the ranges being validated
	// to.
	BOOL SetMinMax(const COleDateTime& minDateTime, 
				   const COleDateTime& maxDateTime, 
				   ValidationMode mode = DateTimeValidation);
	ValidationMode GetMinMax(COleDateTime& minDateTime, 
							 COleDateTime& maxDateTime) const;

	// Validates the given date/time to the current ranges
	BOOL Validate(const COleDateTime& datetime) const;

	// Set/Get the edittable fields.
	int  GetNoEdit() const;
	void SetNoEdit(int nNoEdit);

	// AM/PM indicator
	BOOL IsHourPM();
// Overrides
	// Function called just before a commit of a new date/time is applied.
	// Return FALSE to abandon the commit.
	virtual BOOL OnChanging(const COleDateTime& newDateTime);

	// Function called after the date/time has been modified. The default
	// implementation passes a GXDT_DTN_CHANGED notification to the parent.
	virtual void OnChanged();

// Implementation
public:
	virtual ~CGXBDateTimeCtrl();

protected:
	// Function responsible for parsing the date/time format string and 
	// building the m_gadgets component list.
	void ParseDateTimeFormat();

	// Functions used by ParseDateTimeFormat for parsing individual components
	// of the date/time string
	void ParseHours(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	void ParseMinutes(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	void ParseSeconds(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	void ParseAmPm(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	void ParseDay(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	void ParseMonth(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	void ParseYear(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	void ParseEra(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	void ParseQuotedText(LPCTSTR& lpszStart, LPCTSTR& lpsz, UINT uParam);
	BOOL CheckLeadZero(LPCTSTR& lpsz, TCHAR c) const;
	void FlushStatic(LPCTSTR lpszStart, LPCTSTR lpszEnd);

	// Functions used for changing the value of a speicific field 
	BOOL ChangeHour(UINT uNotifyCode, int nID, LPARAM lParam);
	BOOL ChangeMinute(UINT uNotifyCode, int nID, LPARAM lParam);
	BOOL ChangeSecond(UINT uNotifyCode, int nID, LPARAM lParam);
	BOOL ChangeAmPm(UINT uNotifyCode, int nID, LPARAM lParam);
	BOOL ChangeDay(UINT uNotifyCode, int nID, LPARAM lParam);
	BOOL ChangeMonth(UINT uNotifyCode, int nID, LPARAM lParam);
	BOOL ChangeYear(UINT uNotifyCode, int nID, LPARAM lParam);
	virtual int GetCentury(int n2DigitYear);	// Modified sig. in OG7.02

	// Functions for moving forward/backwards a gadget
	void AdvanceGadget();
	void RetreatGadget();

	// Function used to layout the gadgets within the controls client
	virtual void LayoutGadgets();

	// Function used for controlling the drawing of the gadgets.
	virtual void Draw(CDC& dc);

	// Handler for spinner events
	BOOL SpinnerEvent(UINT uNotifyCode, int nID, LPARAM lParam);

	// Handler for creating the popup calendar
	virtual BOOL PopupCalendar(UINT uNotifyCode, int nID, LPARAM lParam);

	// Override this to hook in a SECPopupCalendar derived object.
	virtual void OnCreatePopupCalendar();

	// Functions for updating the specified gadgets with new values and
	// for forcing them to be redisplayed
	void UpdateGadgets(const COleDateTime& datetime);
	void UpdateGadgets(UINT nFlags = GXDT_DTID_ALL);

	// Performs validation of a new date (and can correct certain
	// fields to make it valid)
	virtual BOOL Validate(COleDateTime& datetime, int nPos) const;

	// Handles notify events from gadgets
	virtual BOOL OnNotify(UINT uNotifyCode, int nID, LPARAM lParam);

	// Handles requests from gadgets to capture the mouse.
	void CaptureMouse(CGXBDTGadget* pGadget, BOOL bSet);

	// Functions for causing the gadget display to be re-built.
	void ResetGadgets();
	void Tidy();

protected:
// Implementation - data members
	enum								// Internal state flags
	{
		DateModified = 0x0001,			// The date has been modified
		TimeModified = 0x0002,			// The time has been modified
		Editing      = 0x0004			// A numeric field is currently being
	};									// editted.

	int               m_nState;			// Holds state information (see flags)
	int               m_nNoEdit;		// Holds non-editable fields (see NoEdit)
	BOOL			  m_bFastInput;		// TRUE if fast input enabled
	COleDateTime      m_datetime;		// Current date/time
	COleDateTime      m_datetimeMin;	// Minimum date/time
	COleDateTime      m_datetimeMax;	// Maximum date/time
	ValidationMode    m_validMode;		// Validation mode (see ValidationMode)
	FormatType        m_formatType;		// Date/Time format type (see FormatType)
	CString           m_strCustomFormat;// Holds custom date/time format string
	HFONT             m_hFont;			// Font used by control
	int               m_nCurGadget;		// Current gadget (gadget with focus)
	int               m_nXOrigin;		// Current offset (scrolled percentage)
										// of window.
	int               m_nRightOffset;	// Amount of space on right reserved for
										// fixed gadgets
	int               m_nFixed;			// No. of fixed gadgets.
	CGXBDTGadget*      m_pCapture;		// Ptr to gadget which has mouse capture
	CGXBPopupCalendar* m_pPopupCalendar;	// Handle of popup calendar 
										// (normally NULL)

	BOOL			  m_bHourPM;		// AM/PM toggle
	COLORREF          m_cBkColor;		// Current background color

public:
	int               m_nBkDisabled;	// System background color when disabled
	UINT              m_nCalBmp;		// ID of bmp to display on cal. drop down
										// button.

	BOOL              m_bDateTokens;	// OG: ParseDateTime will set this TRUE if it finds date tokens

protected:

	// CGXBDTGadgetArray would normally be implemented as a template 
	// (CTypedPtrArray). Since templates are not implemented by some Unix
	// compilers, we copy what the template would have done.
	class CGXBDTGadgetArray : public CObArray
	{
	public:
		// Accessing elements
		CGXBDTGadget* GetAt(int nIndex) const;
		CGXBDTGadget*& ElementAt(int nIndex);
		void SetAt(int nIndex, CGXBDTGadget* ptr);

		// Potentially growing the array
		void SetAtGrow(int nIndex, CGXBDTGadget* newElement);
		int Add(CGXBDTGadget* newElement);
		int Append(const CGXBDTGadgetArray& src);
		void Copy(const CGXBDTGadgetArray& src);

		// Operations that move elements around
		void InsertAt(int nIndex, CGXBDTGadget* newElement, int nCount = 1);
		void InsertAt(int nStartIndex, CGXBDTGadgetArray* pNewArray);

		// overloaded operator helpers
		CGXBDTGadget* operator[](int nIndex) const;
		CGXBDTGadget*& operator[](int nIndex);
	};

	// m_gadgets is an array of all the gadget components.
	CGXBDTGadgetArray m_gadgets;

	// Implementation - message map and entries
	DECLARE_MESSAGE_MAP()

	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSysColorChange();
	afx_msg void OnCancelMode();
	afx_msg LRESULT OnSettingChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg LRESULT OnCalendarOK(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCalendarCancel(WPARAM wParam, LPARAM lParam);

	// A very dear friend of mine ...
	friend class CGXBDTGadget;

public:
	// Added for OG
	COLORREF m_clrText;
	COLORREF m_clrWindow;

	// Handles the spinner timing, initially set to 500 & 100 msecs.
	// To slow spinner, after call to OnInitialUpdate, try 
	//  ((CGXDateTimeCtrl*)GetRegisteredControl(GX_IDS_CTRL_DATETIME))->m_nNormalTimer = 200;
	int m_nInitialTimer;
	int m_nNormalTimer;	
};


/////////////////////////////////////////////////////////////////////////////
// Function for converting a DATE (base type of COleDateTime) to a tm structure
extern BOOL AFXAPI GXBGetTmFromOleDate(DATE dtSrc, struct tm& tmDest);


/////////////////////////////////////////////////////////////////////////////

#define ON_GXDT_DTN_CHANGED(id, memberFxn) \
		ON_CONTROL(GXDT_DTN_CHANGED, id, memberFxn)


/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "grid\gxdtcal.inl"
#endif


//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//
#endif // #if _MFC_VER >= 0x0400   

#endif // _GXDTCAL_H_

