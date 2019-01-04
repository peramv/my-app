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
// ^FILE   : ctimerlistctrl.h
// ^AUTHOR : Steve Bergee
// ^DATE   : 09-97
//
// ^CLASS    : CTimerListCtrl
// ^SUBCLASS : ListViewControl
//
// ^CLASS DESCRIPTION : 
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
// ----------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
//******************************************************************************

#include <uibase\listctrl.h>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimerListCtrl window

class WIN32UIBASE_LINKAGE CTimerListCtrl : public ListViewControl
{
// Construction
public:
   CTimerListCtrl( bool bShowSelAlways = true )
   : ListViewControl( bShowSelAlways ),
   ListIdentifier( -1 ),
   ChangeCounter( 0 ),
   CurrentSelection( -1 ) {}

// Attributes
public:

// Operations
   public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CTimerListCtrl)
   //}}AFX_VIRTUAL

// Implementation
   public:
//	virtual ~CTimerListCtrl();

   // Generated message map functions
   protected:
   //{{AFX_MSG(CTimerListCtrl)
   afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnTimer(UINT nIDEvent);
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
   private:
   USHORT  ChangeCounter;
   ULONG   ListIdentifier;
   int   CurrentSelection;
};

/////////////////////////////////////////////////////////////////////////////

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/CTimerListCtrl.h-arc  $
 * 
 *    Rev 1.3   Oct 09 2002 17:42:38   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   19 Mar 2002 13:36:02   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   16 Jan 2002 09:41:08   KOVACSRO
 * We don't need ListID in constructor (if we need a ListID, it should be in an Init method)
 * 
 *    Rev 1.0   Feb 15 2000 11:00:56   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:04:54   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
