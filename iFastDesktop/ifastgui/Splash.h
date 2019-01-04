
#ifndef SPLASH_H
#define SPLASH_H

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
//    Copyright 1997-1998 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : Splash.h
// ^AUTHOR : Terry Erickson
// ^DATE   : 4/17/98
//
// ^CLASS  : CSplashWnd
// ^PARENT : CWnd
//
// ^CLASS DESCRIPTION : Displays a splash screen at start up
//
// -----------------------------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// -----------------------------------------------------------------------------
//
// ^METHOD      : CSplashWnd
//
// ^DESCRIPTION : constructor
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : ~CSplashWnd
//
// ^DESCRIPTION : destructor
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : ShowSplashScreen
//
// ^DESCRIPTION : Static method to display splash screen
//
// ^PARAMETERS  :
//    ^^ CWnd *pParentWnd - Pointer to parent window or NULL
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : PostNcDestroy
//
// ^DESCRIPTION : Called by the framework after the window is destroyed
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// -----------------------------------------------------------------------------
//
// ^METHOD      : Create
//
// ^DESCRIPTION : Creates the window
//
// ^PARAMETERS  :
//    ^^ CWnd *pParentWnd - Pointer to parent window or NULL
//
// ^RETURNS     :
//    ^^ BOOL - Returns True if successful creation
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : HideSplashScreen
//
// ^DESCRIPTION : Destroys the splash screen window
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

class CSplashWnd : public CWnd
{
public:

   CSplashWnd();
   ~CSplashWnd();
   static void ShowSplashScreen( CWnd* pParentWnd = NULL );
   virtual void PostNcDestroy();

   CBitmap m_bitmap;

protected:

   static CSplashWnd* c_pSplashWnd;

   BOOL Create( CWnd* pParentWnd = NULL );
   void HideSplashScreen();

   // Generated message map functions
   //{{AFX_MSG(CSplashWnd)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnPaint();
   afx_msg void OnTimer(UINT nIDEvent);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastgui/Splash.h-arc  $
 * 
 *    Rev 1.2   Oct 09 2002 23:56:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.1   19 Mar 2002 13:44:56   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.0   Feb 15 2000 11:01:26   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:54   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
