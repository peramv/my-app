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
// Author: Stefan Hoenig
//

// gxstydlg.h : header file
//

#ifndef _GXSTYDLG_H_
#define _GXSTYDLG_H_

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"
#endif

#ifndef _GXWND_H_
#include "grid\gxwnd.h"
#endif

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

// classes defined in this header file

class CGXStylesDialog;
class CGXStyleSheet;
class CGXFontPage;
class CGXColorPage;
class CGXBorderPage;
class CGXAlignmentPage;
class CGXMergeCellPage;
class CGXFloatCellPage;
class CGXControlPage;
class CGXUserAttributPage;
class CGXBasedOnPage;
class CGXFormatPage;
class CGXGridParam;

/////////////////////////////////////////////////////////////////////////////
// CGXStylesDialog dialog

class CGXStylesDialog : public CDialog
{
	DECLARE_DYNAMIC(CGXStylesDialog)

// Construction
public:
	CGXStylesDialog(CWnd* pParent = NULL);   // standard constructor

	void SetStylesMap(CGXStylesMap& stylesmap);
	const CGXStylesMap& GetStylesMap();
	void SetParam(CGXGridParam* pParam);

protected:
// Dialog Data
	//{{AFX_DATA(CGXStylesDialog)
	enum { IDD = IDD_GXSTYLESDLG };
	CComboBox   m_cbStyles;
	CButton m_btnRemoveStyle;
	CButton m_btnChangeStyle;
	CButton m_btnAddStyle;
	BOOL    m_bSaveDefault;
	CString m_sStyle;
	//}}AFX_DATA

	CGXStylesMap m_StylesMap;
	CGXGridParam* m_pParam;

// Overrides
	virtual CGXStyleSheet* CreateStyleSheet();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXStylesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGXStylesDialog)
	afx_msg void OnBtnAddStyle();
	afx_msg void OnBtnChangeStyle();
	afx_msg void OnBtnLoadDefStyles();
	afx_msg void OnBtnRemoveStyle();
	afx_msg void OnSelchangeStyleNames();
	afx_msg void OnEditchangeStyleName();
	afx_msg void OnDblclkStyleNames();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXStyleSheet

class CGXStyleSheet : public CGXPropertySheet
{
	DECLARE_DYNAMIC(CGXStyleSheet)

// Construction
public:
	CGXStyleSheet(UINT nIDCaption, CGXStylesMap& stylesMap, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CGXStyleSheet(LPCTSTR pszCaption, CGXStylesMap& stylesMap, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CGXStyleSheet(UINT nIDCaption, CGXGridParam* pParam, CGXStylesMap* pStylesMap = NULL, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CGXStyleSheet(LPCTSTR pszCaption, CGXGridParam* pParam, CGXStylesMap* pStylesMap = NULL, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

	virtual void CreatePages();

// Attributes
protected:
	void Init();

	CGXStyle*       m_pStyle;
	CGXStyle*       m_pDefaultStyle;
	CGXStylesMap*   m_pStylesMap;
	CGXGridParam*   m_pParam;

	CGXFontPage*        m_pFontPage;
	CGXColorPage*       m_pColorPage;
	CGXBorderPage*      m_pBorderPage;
	CGXAlignmentPage*   m_pAlignmentPage;
	CGXMergeCellPage*  m_pMergeCellPage;
	CGXFloatCellPage*  m_pFloatCellPage;
	CGXControlPage*     m_pControlPage;
	CGXUserAttributPage* m_pUserAttributPage;
	CGXBasedOnPage*     m_pBasedOnPage;
	CGXFormatPage*		m_pFormatPage;

protected:
	// Overridable factory methods for creating the pages.
	virtual CGXFontPage* CreateFontPage();
	virtual CGXColorPage* CreateColorPage();
	virtual CGXBorderPage* CreateBorderPage();
	virtual CGXAlignmentPage* CreateAlignmentPage();
	virtual CGXMergeCellPage* CreateMergeCellPage();
	virtual CGXFloatCellPage* CreateFloatCellPage();
	virtual CGXControlPage* CreateControlPage();
	virtual CGXUserAttributPage* CreateUserAttributPage();
	virtual CGXBasedOnPage* CreateBasedOnPage();
	virtual CGXFormatPage* CreateFormatPage();

public:
	virtual void UpdateData(BOOL bSaveAndValidate);

	void SetStyle(const CGXStyle& style);
	void SetDefaultStyle(const CGXStyle& style);
	void SetStylesMap(const CGXStylesMap& stylesMap);
	const CGXStyle& GetStyle() const;
	const CGXStyle& GetDefaultStyle() const;
	const CGXStylesMap& GetStylesMap() const;

// Operations
public:

	//{{AFX_VIRTUAL(CGXStyleSheet)
	virtual SEC_INT DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXStyleSheet();

protected:
	//{{AFX_MSG(CGXStyleSheet)
	afx_msg void OnOK();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGXFontPage dialog

// CGXTextColorComboBox control

class CGXTextColorComboBox : public CComboBox
{
// Construction
public:
	CGXTextColorComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXTextColorComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXTextColorComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXTextColorComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// CGXFontSample control

class CGXFontSample : public CWnd
{
public:
	CGXFontSample();

// attributes
	COLORREF m_rgbTextColor;
	CFont* m_pFont;
	int m_nOrientation;

	void SetTextColor(COLORREF rgbColor);
	COLORREF GetTextColor() const;

	void SetSampleFont(CFont* pFont, BOOL nOrientation = 0);
	CFont* GetSampleFont();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXFontSample)
	//}}AFX_VIRTUAL

#if _MFC_VER < 0x0300
	// for deriving from a standard control
	virtual WNDPROC* GetSuperWndProcAddr();
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGXFontSample)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXFontFaceNameBox window

class CGXFontFaceNameBox : public CComboBox
{
// Construction
public:
	CGXFontFaceNameBox();

	// Attributes
public:
	CBitmap m_bmTTFont;
	COLORREF m_rgbWindowText;
	COLORREF m_rgbWindow;
	COLORREF m_rgbHilight;
	COLORREF m_rgbHilightText;

// Operations
public:
	void InitSysColors();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXFontFaceNameBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXFontFaceNameBox();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// Generated message map functions
protected:
	//{{AFX_MSG(CGXFontFaceNameBox)
	afx_msg void OnSysColorChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

class CGXFontPage : public CGXPropertyPage
{
	DECLARE_DYNCREATE(CGXFontPage)

// Construction
public:
	CGXFontPage(const CGXFont* pFont = NULL);
	virtual ~CGXFontPage();

#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
	#undef IDD_GXFONTPAGE
	#define IDD_GXFONTPAGE IDD_GXFONTTAB
#endif
// Dialog Data
	//{{AFX_DATA(CGXFontPage)
	enum { IDD = IDD_GXFONTPAGE };
	CComboBox	m_cbOrientation;
	CButton m_btnStrikeout;
	CButton m_btnUnderline;
	CComboBox   m_cbSize;
	CComboBox   m_cbOutline;
	//}}AFX_DATA

	CGXTextColorComboBox m_cbTextColor;
	CGXFontSample m_wndSample;
	CGXFontFaceNameBox m_cbFaceName;

	CGXFont     m_font;
	CGXFont     m_fontParent;
	CString     m_sParentName;

	CFont       fontSample;

	COLORREF    m_rgbText;
	BOOL        m_bIncludeText;

	void SetParentFont(const CGXFont* pFontParent, LPCTSTR szParentName = NULL);
	const CGXFont& GetFont() const;
	void SetFont(const CGXFont* pFont);
	void SetIncludeTextColor(BOOL b);
	BOOL GetIncludeTextColor();
	void SetTextColor(COLORREF rgbColor);
	COLORREF GetTextColor();

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXFontPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bUpdate;

	// Generated message map functions
	//{{AFX_MSG(CGXFontPage)
	afx_msg void OnSelchangeFaceName();
	afx_msg void OnSelchangeOutline();
	afx_msg void OnSelchangeSize();
	afx_msg void OnKillfocusSize();
	afx_msg void OnSelchangeOrientation();
	afx_msg void OnKillfocusOrientation();
	afx_msg void OnKillfocusOutline();
	afx_msg void OnKillfocusFacename();
	afx_msg void OnUnderlineClicked();
	afx_msg void OnStrikeoutClicked();
	virtual BOOL OnInitDialog();
	afx_msg void OnCloseupGxcbtextcolor();
	afx_msg void OnEditchangeGxcbtextcolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXColorPage dialog

// CGXColorButtonBox control

class CGXColorButtonBox : public CWnd
{
	DECLARE_REGISTER()

// Construction
public:
	CGXColorButtonBox();

// Attributes
public:
	int GetCurSel() const;
	void SetCurSel(int nIndex);

	int m_nCurSel;
	BOOL m_bDefaultButton;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXColorButtonBox)
	//}}AFX_VIRTUAL

#if _MFC_VER < 0x0300
	// for deriving from a standard control
	virtual WNDPROC* GetSuperWndProcAddr();
#endif

// Implementation
public:
	virtual ~CGXColorButtonBox();
	CRect GetButtonRect(int nIndex) const;
	BOOL HitTest(const CPoint& pt, int& retVal) const;
	void DrawColorButton(CDC* pDC, int nIndex) const;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXColorButtonBox)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// CGXColorSample control

class CGXColorSample : public CWnd
{
	DECLARE_REGISTER()

public:
	CGXColorSample();

// Attributes
	CGXBrush    m_brInterior;
	int         m_n3dFrame;

	void SetBrush(CBrush* pBrush);
	CBrush* GetBrush() const;

	void SetInterior(const CGXBrush& logbrush);
	const CGXBrush& GetInteriorRef() const;

	int Get3dFrame() const;
	void Set3dFrame(int n);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXColorSample)
	//}}AFX_VIRTUAL

#if _MFC_VER < 0x0300
	// for deriving from a standard control
	virtual WNDPROC* GetSuperWndProcAddr();
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGXColorSample)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// CGXPatternComboBox control

class CGXPatternComboBox : public CComboBox
{
// Construction
public:
	CGXPatternComboBox();

// Attributes
public:
	COLORREF m_rgbText,
			 m_rgbBack;

	COLORREF GetTextColor() const;
	void SetTextColor(COLORREF rgbColor);

	COLORREF GetBackColor() const;
	void SetBackColor(COLORREF rgbColor);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXPatternComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXPatternComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXPatternComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


// CGXColorPage dialog

class CGXColorPage : public CGXPropertyPage
{
	DECLARE_DYNCREATE(CGXColorPage)

// Construction
public:
	CGXColorPage();
	virtual ~CGXColorPage();

	// Parent Style
//  void SetParentColor(CGXBrush brParent, COLORREF rgbBack, LPCTSTR szParentName = NULL);

	// Interior
	BOOL GetIncludeInterior() const;
	void SetIncludeInterior(BOOL b);
	const CGXBrush& GetInterior() const;
	void SetInterior(const CGXBrush& brush);

	// 3d Frame
	int Get3dFrame() const;
	void Set3dFrame(int n);

protected:
// Dialog Data
#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
	#undef IDD_GXCOLORPAGE
	#define IDD_GXCOLORPAGE IDD_GXCOLORTAB
#endif
	//{{AFX_DATA(CGXColorPage)
	enum { IDD = IDD_GXCOLORPAGE };
	CStatic m_textBaseStyle;
	int     m_n3dFrame;
	//}}AFX_DATA

	CGXColorButtonBox   m_wndBackColor;
	CGXColorButtonBox   m_wndTextColor;
	CGXColorSample      m_wndColorSample;

	CGXColorButtonBox& BackColorWnd();
	CGXColorButtonBox& TextColorWnd();
	CGXColorSample& ColorSampleWnd();

	CGXPatternComboBox m_cbPatterns;

	CGXBrush    m_logbrushParent;
	BOOL        m_bIncludeInterior;
	CGXBrush    m_logbrushInterior;
	CBrush      m_brSample;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXColorPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXColorPage)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnChangedColor(WPARAM wParam, LPARAM lParam);
	afx_msg void OnGxbtn3dradioClicked();
	afx_msg void OnSelchangeGxcombopattern();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXBorderPage Propertypage

// CGXBorderTypeButton control

class CGXBorderTypeButton : public CButton
{
// Construction
public:
	CGXBorderTypeButton();
	void SetLogPen(const LOGPEN& logpen);
	const LOGPEN& GetLogPen();
	void EnableCheckBox(BOOL b);
	void SetColor(COLORREF rgbColor);
	void SetActive(BOOL b);

	void SetInclude(BOOL b);
	BOOL GetInclude();

// Attributes
protected:
	LOGPEN m_logpen;
	BOOL m_bCheckBox;
	int m_bInclude;

	CPen m_pen;
	BOOL m_bActive;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBorderTypeButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXBorderTypeButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXBorderTypeButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// CGXColorComboBox control

class CGXColorComboBox : public CComboBox
{
// Construction
public:
	CGXColorComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXColorComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXColorComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXColorComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CGXBorderPage : public CGXPropertyPage
{
	DECLARE_DYNCREATE(CGXBorderPage)

// Public interface
public:
	CGXBorderPage();
	virtual ~CGXBorderPage();

	BOOL GetIncludeBorders(int nBorder);
	void SetIncludeBorders(int nBorder, BOOL b);

	void SetBorders(int nBorder, const LOGPEN& pen);
	const LOGPEN& GetBorders(int nBorder);

	void EnableRangeButton(BOOL bVisible);

#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
	#undef IDD_GXBORDERSPAGE
	#define IDD_GXBORDERSPAGE IDD_GXBORDERSTAB
#endif
// Implementation
protected:
	//{{AFX_DATA(CGXBorderPage)
	enum { IDD = IDD_GXBORDERSPAGE };
	//}}AFX_DATA

	CGXBorderTypeButton m_btnType[8];
	CGXBorderTypeButton m_btnBorder[5];
	CGXColorComboBox m_lboxColors;

	UINT m_nCurType;
	BOOL m_bRange;
	UINT m_nCurBorder;

	//{{AFX_VIRTUAL(CGXBorderPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGXBorderPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokCombocolor();
	afx_msg void OnCloseupCombocolor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXAlignmentPage dialog

class CGXAlignmentPage : public CGXPropertyPage
{
	DECLARE_DYNCREATE(CGXAlignmentPage)

// Construction
public:
	CGXAlignmentPage();
	virtual ~CGXAlignmentPage();

// Dialog Data
#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
	#undef IDD_GXALIGNPAGE
	#define IDD_GXALIGNPAGE IDD_GXALIGNTAB
#endif
	//{{AFX_DATA(CGXAlignmentPage)
	enum { IDD = IDD_GXALIGNPAGE };
	int     m_nAllowEnter;
	int     m_nWrapText;
	int     m_nHorzAlign;
	int     m_nVertAlign;
	int     m_nAutoSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXAlignmentPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXAlignmentPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXMergeCellPage dialog

class CGXMergeCellPage : public CGXPropertyPage
{
	DECLARE_DYNCREATE(CGXMergeCellPage)

// Construction
public:
	CGXMergeCellPage();
	virtual ~CGXMergeCellPage();

// Dialog Data
#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
	#undef IDD_GXMERGEPAGE
	#define IDD_GXMERGEPAGE IDD_GXMERGETAB
#endif
	//{{AFX_DATA(CGXMergeCellPage)
	enum { IDD = IDD_GXMERGEPAGE };
	int     m_nMergeCell;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXMergeCellPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXMergeCellPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXFloatCellPage dialog

class CGXFloatCellPage : public CGXPropertyPage
{
	DECLARE_DYNCREATE(CGXFloatCellPage)

// Construction
public:
	CGXFloatCellPage();
	virtual ~CGXFloatCellPage();

// Dialog Data
#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
	#undef IDD_GXFLOATPAGE
	#define IDD_GXFLOATPAGE IDD_GXFLOATTAB
#endif
	//{{AFX_DATA(CGXFloatCellPage)
	enum { IDD = IDD_GXFLOATPAGE };
	int     m_nFloatCell;
	int     m_nFloodCell;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXFloatCellPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXFloatCellPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXControlPage dialog

class CGXControlPage : public CGXPropertyPage
{
	DECLARE_DYNCREATE(CGXControlPage)

// Construction
public:
	CGXControlPage();
	virtual ~CGXControlPage();

// Dialog Data
#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
	#undef IDD_GXCONTROLPAGE
	#define IDD_GXCONTROLPAGE IDD_GXCONTROLTAB
#endif
	//{{AFX_DATA(CGXControlPage)
	enum { IDD = IDD_GXCONTROLPAGE };
	CComboBox   m_cbControlName;
	CEdit   m_editValue;
	CButton m_checkValue;
	int     m_nReadOnly;
	CString m_sChoices;
	int     m_nValue;
	CString m_sValue;
	CString m_sMaxLength;
	int     m_nTriState;
	int     m_nEnabled;
	//}}AFX_DATA

	// int      m_nVertScrollbar;

	// Control
	WORD m_nControl;       // UINT_MAX indicates that no control is specified

	const CMapWordToPtr* m_pControlNameMap;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXControlPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXControlPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnGxcheckValue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXUserAttributPage dialog

class CGXUserAttributPageGrid : public CGXGridWnd
{
	DECLARE_REGISTER()

public:
	// Attributes
	CString m_sNameTitle,
			m_sValueTitle;

public:
	// Overridables
	virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);
	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType);
	virtual void OnInitialUpdate();
	virtual void OnModifyCell(ROWCOL nRow, ROWCOL nCol);
	virtual void OnClickedButtonRowCol(ROWCOL nRow, ROWCOL nCol);
};

class CGXUserAttributPage : public CGXPropertyPage
{
	DECLARE_DYNCREATE(CGXUserAttributPage)

// Construction
public:
	CGXUserAttributPage();
	virtual ~CGXUserAttributPage();

// Dialog Data
#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
	#undef IDD_GXUSERATTRPAGE
	#define IDD_GXUSERATTRPAGE IDD_GXUSERATTRTAB
#endif
	//{{AFX_DATA(CGXUserAttributPage)
	enum { IDD = IDD_GXUSERATTRPAGE };
	//}}AFX_DATA

	CGXUserAttributPageGrid m_userGrid;
	CStringArray m_arrayContent;
	CByteArray  m_arrayInclude;
	CWordArray  m_arrayID;
	const CMapWordToPtr* m_pUserAttrInfoMap;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXUserAttributPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXUserAttributPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXBasedOnPage dialog

class CGXBasedOnPage : public CGXPropertyPage
{
	DECLARE_DYNCREATE(CGXBasedOnPage)

// Construction
public:
	CGXBasedOnPage();
	virtual ~CGXBasedOnPage();

// Dialog Data
#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
	#undef IDD_GXSPECIALPAGE
	#define IDD_GXSPECIALPAGE IDD_GXSPECIALTAB
#endif
	//{{AFX_DATA(CGXBasedOnPage)
	enum { IDD = IDD_GXSPECIALPAGE };
	CComboBox   m_cbBasedOn;
	CString     m_sBasedOn;
	//}}AFX_DATA

	CStringList m_BasedOnStringList;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGXBasedOnPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGXBasedOnPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGXFormatPage dialog

class CGXFormatPage : public CGXPropertyPage
{
	DECLARE_DYNCREATE(CGXFormatPage)

// Construction
public:
	CGXFormatPage();	// standard constructor
	virtual ~CGXFormatPage();

// Dialog Data
#if _MFC_VER < 0x0300 && defined(USE_TABDLG)
	#undef IDD_GXFORMATPAGE
	#define IDD_GXFORMATPAGE IDD_GXFORMATTAB
#endif
	int		m_nFormat;
	//{{AFX_DATA(CGXFormatPage)
	enum { IDD = IDD_GXFORMATPAGE };
	CComboBox	m_cbFormat;
	CString	m_strPlaces;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CGXFormatPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXSTYDLG_H_
