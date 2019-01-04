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
//
// ^FILE   : DSTTimerListCtrl.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 01-02
//
// ^CLASS    : DSTTimerListCtrl
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//
//
//******************************************************************************

#include <uibase\dstlistctrl.h>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif


class WIN32UIBASE_LINKAGE DSTTimerListCtrl : public DSTListCtrl
{
// Construction
public:
   DSTTimerListCtrl( BaseDlg *rpParent,
                     const I_CHAR *dialogName,
                     UINT controlID,
                     UINT parentControlID,
                     UINT flags,
                     bool bShowSelAlways )
   : DSTListCtrl( rpParent,  dialogName, controlID, parentControlID, flags, bShowSelAlways)
   , m_nPreviousSelection( -1 )
   , m_bWaitCursor(false) 
   {}

// Attributes
public:

// Operations
public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DSTTimerListCtrl)
   //}}AFX_VIRTUAL

// Implementation
public:
//	virtual ~DSTTimerListCtrl();
   void doOk();

   // Generated message map functions
protected:
   //{{AFX_MSG(DSTTimerListCtrl)
   afx_msg void OnTimer(UINT nIDEvent);
   //}}AFX_MSG
   afx_msg BOOL OnDblclkItem(NMHDR* pNMHDR, LRESULT* pResult);

   DECLARE_MESSAGE_MAP()
   void newSelection(int iItem);

private:
   void startWaitCursor();
   void stopWaitCursor();
   int  m_nPreviousSelection;
   bool m_bWaitCursor;     
};

/////////////////////////////////////////////////////////////////////////////

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* 
 */
