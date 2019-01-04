#ifndef MGMTDETAILSDLG_H
#define MGMTDETAILSDLG_H
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
// ^FILE   : MgmtDetailsDlg.h
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ^CLASS    : MgmtDetailsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************
#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

//{{AFX_INCLUDES()
#include <ifastgui\webbrowser.h>
#include <ifastgui\animation.h>
//}}AFX_INCLUDES

class MgmtDetailsDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   MgmtDetailsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(MgmtDetailsDlg)
   enum
   {
      IDD = IDD_MANAGEMENTDETAILS
   };
   CButton m_btnWebStop;
   CButton m_btnWebHome;
   CButton m_btnWebFwd;
   CButton m_btnWebBack;
   CString m_txtFundCode;
   CWebBrowser m_wbrowMgmtDetail;
   CAnimation  m_Animate;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(MgmtDetailsDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit();
   /**
     * Required implementation for the refresh method.  No refresh activity is
     * performed for this class.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh( GenericInterface * rpGICaller, 
                           const I_CHAR * szOriginalCommand );
   // Generated message map functions
   //{{AFX_MSG(MgmtDetailsDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnWebhome();
   afx_msg void OnWebstop();
   afx_msg void OnWebback();
   afx_msg void OnWebfwd();
   afx_msg void OnCommandStateChangeMgmtDetailsHtml(long Command, BOOL Enable);
   afx_msg void OnDownloadBeginMgmtDetailsHtml();
   afx_msg void OnDownloadCompleteMgmtDetailsHtml();
   DECLARE_EVENTSINK_MAP()
   //}}AFX_MSG
   virtual void OnPostInitDialog();
   void fillInitialValues();

   DECLARE_MESSAGE_MAP()

   private:
   CString m_FileName;
   CString m_csFileDir;        // Path to data files
};

#endif // MgmtDetailsDlg_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MgmtDetailsDlg.h-arc  $
 * 
 *    Rev 1.3   Mar 21 2003 18:39:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.2   Oct 09 2002 23:55:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.1   Feb 15 2000 18:59:36   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:20   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.4   Feb 02 2000 14:55:08   DT24433
 * removed ok/cancel
 * 
 *    Rev 1.3   Jul 20 1999 16:58:50   BUZILA
 * Added animation control to Mgmt details
 * 
 *    Rev 1.2   Jul 15 1999 16:39:30   BUZILA
 * Fixing Mgmt Detail
 * 
 *    Rev 1.1   Jul 08 1999 10:05:38   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
