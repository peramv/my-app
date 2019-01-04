
#ifndef BUSINFODLG_H
#define BUSINFODLG_H
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
// ^FILE   : BusInfoDlg.h
// ^AUTHOR : Paul Lyons
// ^DATE   : 06-97
//
// ^CLASS    : BusInfoDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : This is the code for the FYI screen
//
//******************************************************************************

//{{AFX_INCLUDES()
#include <ifastgui\webbrowser.h>
#include <ifastgui\animation.h>
//}}AFX_INCLUDES

#ifndef BASEMAINDLG_H
   #include <ifastgui\basemaindlg.h>
#endif


#define CSC_NAVIGATEFORWARD 1
#define CSC_NAVIGATEBACK    2 

class BusInfoDlg : public BaseMainDlg
{
// Construction
public:
   BusInfoDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   virtual ~BusInfoDlg();

   /**
     * Required implementation for the refresh method.  No refresh activity is
     * performed for this class.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/
                         )
   {  // Nothing to refresh here
      return(true);
   }
// Dialog Data
   //{{AFX_DATA(BusInfoDlg)
   enum
   {
      IDD = IDD_BUSINFO
   };
   CButton m_BtnStop;
   CButton m_BtnHome;
   CButton m_BtnForward;
   CButton m_BtnBack;
   CListBox  m_BUSLISTBOX;
   CWebBrowser m_BusHTML;
   CAnimation  m_Animate;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(BusInfoDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

   // Generated message map functions
   //{{AFX_MSG(BusInfoDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnWebback();
   afx_msg void OnWebfwd();
   afx_msg void OnWebhome();
   afx_msg void OnWebstop();
   afx_msg void OnCommandStateChangeBushtml(long Command, BOOL Enable);
   afx_msg void OnDownloadBeginBushtml();
   afx_msg void OnDownloadCompleteBushtml();
   DECLARE_EVENTSINK_MAP()
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   public:
   void SetHomeFocus();                                           // method to set focus on home key
   void GetHomeNameFromRegistry(CString& strHomeName);
private:
   CString      m_BusList[40];      // Array holding HTML filenames for listbox
   HWND         m_hwndParent;       // Parent window handle
   CString      m_csFileDir;        // Path to data files
};

#endif // BUSINFODLG_H
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BusInfoDlg.h-arc  $
 * 
 *    Rev 1.5   Mar 21 2003 18:33:48   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:55:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   19 Mar 2002 13:44:32   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.2   Oct 12 2000 15:10:22   HUANGSHA
 * Fix when go back to home page, it should reretrive the registry again
 * 
 *    Rev 1.1   Feb 15 2000 18:59:14   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:10   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.3   Aug 10 1999 11:42:44   BUZILA
 * -member
 * 
 *    Rev 1.2   Aug 10 1999 11:19:38   BUZILA
 * added support for configuring FYI screen's start page
 * 
 *    Rev 1.1   Jul 08 1999 10:04:44   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
