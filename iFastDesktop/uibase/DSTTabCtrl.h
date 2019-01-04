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
//    Copyright 2002 by DST Systems, Inc.
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
class WIN32UIBASE_LINKAGE DSTTabCtrl : public CTabCtrl
{
// Construction
public:
   DSTTabCtrl(
             BaseDlg *rpParent,
             const I_CHAR *dialogName,
             UINT controlID, 
             UINT parentControlID,
             UINT flags
             );

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DSTTabCtrl)
   //}}AFX_VIRTUAL

// Implementation
   virtual ~DSTTabCtrl();
   /**
      * @param rpBD - a pointer to the parent dialog.
      * @param tabCtrlName - the name of the tab control
      */
   void Init(BaseDlg *rpBD, const I_CHAR *tabCtrlName);  
   /**
      * Calling this method will : refresh the error signs on all the pages,
      * hide the registered controls with all the other pages, show the registered 
      * controls for the specified page name, select the specified page (if not
      * already selected)
      * @param pageName - Specifies the name of the selected page (if empty
      * the first page is selected)
      */
   void Load(const DString &pageName = NULL_STRING);
   /**
      * Calling this method will : refresh the error signs on all the pages,
      * hide the registered controls with all the other pages, show the registered 
      * controls for the specified page name, select the specified page (if not
      * already selected)
      * @param stringID - Specifies the string ID of the selected page name(if zero
      * the first page is selected)
      */
   void Load(UINT stringID);
   /**
      * refreshes the error signs on all the pages
      */
   void RefreshAllIcons();
   /**
      * Adds a new tab to the control
      * @param tabName - Specifies the name of the new page. Page names have to be unique
      * @param iPos - Specifies the zero based position of the new page. If -1 inserts page last
      * @returns true if page has been successfuly added, false if not
      */ 
   bool AddTab(const DString & tabName, int iPos = -1);
   /**
      * Adds a new tab to the control
      * @param tabStringId - Specifies the string ID of the new page name.
      * @param iPos - Specifies the zero based position of the new page. If -1 inserts page last
      * @returns true if page has been successfuly added, false if not
      */ 
   bool AddTab(UINT tabStringId, int iPos = -1);
   /**
      * Removes a tab(page) from the control
      * @param tabName - Specifies the name of the page to be removed (has to be a name used
      * in AddTab
      * @returns true if page has been successfuly removed, false if not
      */   
   bool RemoveTab(const DString &tabName);
   /**
      * Removes a tab(page) from the control
      * @param tabStringId - Specifies the string ID of the page name to be removed (has to be 
      * a string ID used in AddTab
      * @returns true if page has been successfuly removed, false if not
      */   
   bool RemoveTab(UINT tabStringId);
   /**
      * Selects a tab(page) from the control
      * @param tabName - Specifies the name of the page to be selected (has to be a name used
      * in AddTab
      * @returns true if page has been successfuly selected, false if not
      */   
   bool SelectTab(const DString &tabName, bool force = false);
   /**
      * Selects a tab(page) from the control
      * @param tabStringId - Specifies the string ID of the page name to be selected (has to be 
      * a string ID used in AddTab
      * @returns true if page has been successfuly selected, false if not
      */   
   bool SelectTab (UINT tabStringId, bool force = false);
   /**
      * Checks whether a tab(page) exists
      * @param tabStringId - specifies the string ID of the page name to be selected (has to be 
      * a string ID used in AddTab
      * @returns true if page exists, false if not
      */   
   bool HasTab (UINT tabStringId);
   /**
      * Checks whether a tab(page) exists
      * @param tabName - Specifies the name of the page to be checked (has to be a name used
      * in AddTab
      * @returns true if page exists, false if not
      */   
   bool HasTab(const DString &tabName);
   UINT GetControlID() {return(m_controlID);}
   /**
      * links a base control with a tab (page)
      * @param controlID - ID of control to be registered
      * @param tabName - Specifies the name of the page 
      * @returns true if the control has been successfuly registered, false if not
      */ 
   bool registerControl(UINT controlID, const DString& tabName);
   /**
      * links a base control with a tab (page)
      * @param controlID - ID of control to be registered
      * @param stringID - Specifies the string ID of the page name
      * @returns true if the control has been successfuly registered, false if not
      */ 
   bool registerControl(UINT controlID, UINT stringID);
   /**
      * un-links a base control from a tab (page)
      * @param controlID - ID of control to be removed
      * @param tabName - Specifies the name of the page 
      * @returns true if the control has been successfuly un-linked, false if not
      */   
   bool removeControlFromPage(UINT controlID, const DString& tabName);
   /**
      * un-links a base control from a tab (page)
      * @param controlID - ID of control to be removed
      * @param stringID - Specifies the string ID of the page name
      * @returns true if the control has been successfuly un-linked, false if not
      */   
   bool removeControlFromPage(UINT controlID, UINT stringID);
   /**
      * links a DST list control with a tab (page)
      * @param controlID - ID of the list control to be registered
      * @param tabName - Specifies the name of the page 
      * @returns true if the list control has been successfuly registered, false if not
      */ 
   bool registerListControl(UINT controlID, const DString& tabName);
   /**
      * links a DST list control with a tab (page)
      * @param controlID - ID of the list control to be registered
      * @param stringID - Specifies the string ID of the page name
      * @returns true if the list control has been successfuly registered, false if not
      */ 
   bool registerListControl(UINT controlID, UINT stringID);
   /**
      * un-links a DST list control from a tab (page)
      * @param controlID - ID of the list control to be removed
      * @param tabName - Specifies the name of the page 
      * @returns true if the list control has been successfuly un-linked, false if not
      */   
   bool removeListControlFromPage(UINT controlID, const DString& tabName);
   /**
      * un-links a DST list control from a tab (page)
      * @param controlID - ID of the list control to be removed
      * @param stringID - Specifies the string ID of the page name
      * @returns true if the list control has been successfuly un-linked, false if not
      */   
   bool removeListControlFromPage(UINT controlID, UINT stringID);
   /**
      * links a DST grid window with a tab (page)
      * @param controlID - ID of the grid window to be registered
      * @param tabName - Specifies the name of the page 
      * @returns true if the grid window has been successfuly registered, false if not
      */ 
   bool registerGridWnd(UINT controlID, const DString& tabName);
   /**
      * links a DST grid window with a tab (page)
      * @param controlID - ID of the grid window to be registered
      * @param stringID - Specifies the string ID of the page name
      * @returns true if the grid window has been successfuly registered, false if not
      */ 
   bool registerGridWnd(UINT controlID, UINT stringID);
   /**
      * un-links a grid window from a tab (page)
      * @param controlID - ID of the grid window to be removed
      * @param tabName - Specifies the name of the page 
      * @returns true if the grid window has been successfuly un-linked, false if not
      */   
   bool removeGridWndFromPage(UINT controlID, const DString& tabName);
   /**
      * un-links a grid window from a tab (page)
      * @param controlID - ID of the grid window to be removed
      * @param stringID - Specifies the string ID of the page name
      * @returns true if the grid window has been successfuly un-linked, false if not
      */   
   bool removeGridWndFromPage(UINT controlID, UINT stringID);

   /**
      * un-allow display/hide control dynamically
      * @param controlID - ID  of the MFC control
      * @param stringID - Specifies the string ID of the page name
      * @param bShow - true: display the control, false: hide the control     
      */
   void showTabControl( UINT controlID,UINT stringID, bool bShow = true );


   // Generated message map functions
protected:
   //{{AFX_MSG(DSTTabCtrl)
   // NOTE - the ClassWizard will add and remove member functions here.
   afx_msg void OnSelChanging(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()

   private:
   DString m_strDialogName;
   UINT m_parentControlID;
   UINT m_flags;
   DString m_strTabName;
   BaseDlg *m_rpParentDialog;
   CImageList *m_icons;
   UINT m_controlID;


   struct CTRL_PROP
   {
      DString strKey;//to keep the current selection key (not used for base controls)
      SEVERITY sev;//to keep the severity for disconnected controls
      bool bConnected;//to keep track if the control is connected/disconnected
      bool bShow;    //display control based on the flag
   };

   typedef std::map< UINT, CTRL_PROP > REG_CONTROLS;
   typedef REG_CONTROLS::iterator REG_CONTROLS_ITER;

   typedef std::map< UINT, CTRL_PROP> REG_LIST_CONTROLS;
   typedef REG_LIST_CONTROLS::iterator REG_LIST_CONTROLS_ITER;

   typedef std::map< UINT, CTRL_PROP> REG_GRIDS;
   typedef REG_GRIDS::iterator REG_GRIDS_ITER;

   struct PAGE_PROP
   {
      DString pageName;//tab (page) name
      REG_CONTROLS regControls;//registered base controls
      REG_LIST_CONTROLS regListControls;//registered list controls
      REG_GRIDS regGrids;//registered grids
   };

   typedef std::map < DString, PAGE_PROP *, std::less <DString> > PAGE;
   typedef std::map < DString, PAGE_PROP *, std::less <DString> >::iterator PAGE_ITER;

   PAGE m_pages;
   /**
      * links a base control with a tab (page)
      * @param controlID - ID of control to be registered
      * @param nPage - Specifies the page's position in the tab control (zero based) 
      * @returns true if the control has been successfuly registered, false if not
      */ 
   bool registerControlWithPage(UINT controlID, UINT nPage);
   /**
      * un-links a base control from a tab (page)
      * @param controlID - ID of the control to be removed
      * @param nPage - Specifies the page's position in the tab control (zero based) 
      * @returns true if the control has been successfuly un-linked, false if not
      */   
   bool removeControlFromPageNo(UINT controlID, UINT nPage);
   /**
      * links a list control with a tab (page)
      * @param controlID - ID of the list control to be registered
      * @param nPage - Specifies the page's position in the tab control (zero based) 
      * @returns true if the list control has been successfuly registered, false if not
      */ 
   bool registerListControlWithPage(UINT controlID, UINT nPage);
   /**
      * un-links a list control from a tab (page)
      * @param controlID - ID of the list control to be removed
      * @param nPage - Specifies the page's position in the tab control (zero based) 
      * @returns true if the list control has been successfuly un-linked, false if not
      */
   bool removeListControlFromPageNo(UINT controlID, UINT nPage);
   /**
      * links a grid window with a tab (page)
      * @param controlID - ID of the grid window to be registered
      * @param nPage - Specifies the page's position in the tab control (zero based) 
      * @returns true if the grid window has been successfuly registered, false if not
      */ 
   bool registerGridWndWithPage(UINT controlID, UINT nPage);
   /**
      * un-links a grid window from a tab (page)
      * @param controlID - ID of the grid window to be removed
      * @param nPage - Specifies the page's position in the tab control (zero based) 
      * @returns true if the grid window has been successfuly un-linked, false if not
      */
   bool removeGridWndFromPageNo(UINT controlID, UINT nPage);
   /**
      * @param tabName - Specifies the name of the page 
      * @returns the page's position if name was found, else -1
      */
   int getPagePos (const DString& tabName);
   /**
      * @param nPageNum - position of the tab(zero based)
      * @returns a pointer to the PAGE_PROP of the specified tab
      */
   PAGE_PROP * getPageProp (UINT nPageNum);
   /**
      * @param strPageName - the page name
      * @returns a pointer to the PAGE_PROP of the specified tab
      */
   PAGE_PROP * getPageProp (const DString &strPageName) {return m_pages [strPageName];};
   /**
      * @returns the name of the nPage tab or NULL_STRING for an invalid nPage
      */
   DString getPageName(UINT nPage);
   /**
      * show/hide all the registered controls with the specified page 
      * (base controls, list controls, grid windows)
      * @param nPage - Specifies the page's position in the tab control (zero based) 
      * @param bShow - true for show, false for hide
      */
   void showRegisteredControls(UINT nPage, bool bShow = true);
   /**
      * refreshes the error sign for the specified page
      * @param nPage - Specifies the page's position in the tab control (zero based) 
      */
   void refreshIcon(UINT nPage);
   /**
      * draws the severity icon on the tab
      * @param nPage - Specifies the page's position in the tab control (zero based) 
      * @param sevMax - Specifies the maximum severity for all the registered controls
      * for this page
      */
   void showIcon(UINT nPage, SEVERITY sevMax);
   /**
      * calls BaseDlg::isDisconnectRequired; if yes, it disconnects the registered control
      * and keeps some info about it (severity, selection key...)
      * @param nPage - Specifies the page's position in the tab control (zero based) 
      */ 
   void disconnectControls(const DString &strPageName);
   /**
      * calls BaseDlg::isConnectRequired; if yes, it connects the registered control
      * @param nPage - Specifies the page's position in the tab control (zero based) 
      */ 
   void connectControls(const DString &strPageName);
   /**
      * helper method to be used while the selection changes
      */ 
   bool onSelChanging();
   /**
      * helper method to be used after the selection changed
      */ 
   void onSelChanged();
};

/////////////////////////////////////////////////////////////////////////////
