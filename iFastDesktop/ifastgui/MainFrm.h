
#ifndef MAINFRM_H
#define MAINFRM_H

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
// ^FILE   : MainFrm.h
// ^AUTHOR :
// ^DATE   : 11-96
//
// ^CLASS    : CMainFrame
// ^SUBCLASS : CFrameWnd
//
// ^CLASS DESCRIPTION :
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
// ^METHOD : CMainFrame::noAWD()
//
// ^DESCRIPTION : We don't have AWD.  Remove Forms and EnCorr pull downs
//
// ^PARAMETERS  :
//      none
//
// ^RETURNS     :
//      void
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
// ----------------------------------------------------------
//
// ^METHOD      : setCallTrackerActive
//
// ^DESCRIPTION : Adds or removes CallTracker from the menu
//
// ^PARAMETERS  :
//   ^^ BOOL active - whether to add or remove the menu item
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
//*****************************************************************************
#ifndef INCLUDED_VECTOR
   #define INCLUDED_VECTOR
   #include <vector>
#endif

class DSTCUserSession;

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
   CMainFrame();
   DECLARE_DYNCREATE(CMainFrame)

// Attributes
   public:
   enum MenuType
   {
      Undefined,
      TA2000,
		AwdComments,
      Forms,
      EnCorr,
      System,
      AwdCsd,
      AwdHistory
   };


// Operations
public:
   void setAwdActive( BOOL active );
   void setCallTrackerActive( BOOL active );
   void setLiteratureActive( BOOL active );
   void resetDynamicMenuList();
   void setMgmCo( const DSTCUserSession *dstUserSession );
   void CheckMenuItem(DString item);


   MenuType CMainFrame::findDynamicMenuItem( UINT nID, DString &strID );
// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CMainFrame)
public:
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   //}}AFX_VIRTUAL

// Implementation
public:
   void ChangeMenu();
   virtual ~CMainFrame();
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
   //{{AFX_MSG(CMainFrame)
   afx_msg void OnAbout();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   private:
   void set (BOOL active, UINT nMenuID, const I_CHAR *pcchMenu);
   void appendSubMenu( CMenu *pMenu,
                       const I_CHAR *pcchMenu,
                       const I_CHAR *pcchItem,
                       const I_CHAR *pcchKey,
                       UINT nMenuID,
                       MenuType mt );
   void appendDynamicMenuItem( CMenu *pMenu,
                               MenuType mt,
                               const DString &strName,
                               const DString &strID );
   int findPosition( CMenu *pMenu, const CString &cstrItem );
   void deleteMenuItem( CMenu *pMenu, const CString &cstrItem );
private:
   struct DynamicMenuItem
   {
      MenuType mt;
      UINT     id;
      DString   strName;
      DString   strID;
   };

   typedef std::vector<DynamicMenuItem> ItemVector;

   ItemVector m_ivList;
   UINT       m_nNextMenuID;
public:
	afx_msg void OnClose();
};

#endif   // MAINFRM_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MainFrm.h-arc  $
 * 
 *    Rev 1.10   26 Sep 2007 17:02:02   kovacsro
 * IN#1015356 - added OnClose
 * 
 *    Rev 1.9   Dec 22 2004 16:56:20   zhangcel
 * PTS 10031333 -- Added a new function onCreate()
 * 
 *    Rev 1.8   May 06 2004 16:14:36   VADEANUM
 * PET 1017 - AWD Comments - added AWDComments.
 * 
 *    Rev 1.7   Oct 09 2002 23:55:46   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   19 Mar 2002 13:44:44   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.5   Nov 26 2001 15:01:28   HERNANDO
 * Removed OnHelp and m_shellExecuteInfo.
 * 
 *    Rev 1.4   Nov 19 2001 16:56:10   HERNANDO
 * Added m_shellExecuteInfo.
 * 
 *    Rev 1.3   03 May 2001 14:07:38   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Oct 19 2000 18:17:20   HERNANDO
 * Added AwdHistory menu type.
 * 
 *    Rev 1.1   Feb 15 2000 18:59:32   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:18   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   15 Dec 1999 11:11:24   HSUCHIN
 * added dynamic menu for change of management company
 * 
 *    Rev 1.1   Jul 08 1999 10:05:28   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
