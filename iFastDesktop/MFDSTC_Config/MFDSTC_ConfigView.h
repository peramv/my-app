// MFDSTC_ConfigView.h : interface of the CMFDSTC_ConfigView class
//


#pragma once
#include "ConfigSheet.h"

class CMFDSTC_ConfigView : public CFormView
{
protected: // create from serialization only
	CMFDSTC_ConfigView();
	DECLARE_DYNCREATE(CMFDSTC_ConfigView)

public:
	enum{ IDD = IDD_MFDSTC_CONFIG_FORM };

// Attributes
public:
	CMFDSTC_ConfigDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMFDSTC_ConfigView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
   CConfigSheet* pConfigSheet_;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
   virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
   bool isUpdated(void);
   afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
   afx_msg void OnFileSave();
   afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
   afx_msg void OnFileSaveAs();
   afx_msg void OnUpdateLoadRegistry(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in MFDSTC_ConfigView.cpp
inline CMFDSTC_ConfigDoc* CMFDSTC_ConfigView::GetDocument() const
   { return reinterpret_cast<CMFDSTC_ConfigDoc*>(m_pDocument); }
#endif

