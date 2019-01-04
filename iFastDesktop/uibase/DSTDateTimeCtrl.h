#pragma once


#include "afxdtctl.h"


#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000
// DSTDateTimeCtrl.h : header file
//

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// DSTDateTimeCtrl window

class WIN32UIBASE_LINKAGE DSTDateTimeCtrl : public CDateTimeCtrl
{
// Construction
public:
   DSTDateTimeCtrl();

// Attributes
public:

// Operations
   public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DSTDateTimeCtrl)
   public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void PreSubclassWindow();
   //}}AFX_VIRTUAL

// Implementation
public:
   void GetDateInHostFormat( CString &strOut);
   virtual ~DSTDateTimeCtrl();

   // Generated message map functions
protected:
   //{{AFX_MSG(DSTDateTimeCtrl)
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

