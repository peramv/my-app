#pragma once


//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <uibase\BaseControl.hpp>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE DSTButton : public CButton, public BaseControl
{
// Construction
public:
   DSTButton( BaseDlg *rpParent, UINT controlID );

// Attributes
public:

// Operations
   public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DSTButton)
   //}}AFX_VIRTUAL

// Implementation
   public:
   virtual ~DSTButton();

   // Generated message map functions
protected:
   //{{AFX_MSG(DSTButton)
   // NOTE - the ClassWizard will add and remove member functions here.
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
   virtual void DoGetText(
                         DString &strValueOut,
                         int index=0
                         ) const;
   virtual void DoInit();
   virtual bool DoSetText(
                         const DString &strValueIn,
                         int index=0
                         );
   bool doSetCtrlReadOnly(bool bReadOnly);

};

/////////////////////////////////////////////////////////////////////////////

