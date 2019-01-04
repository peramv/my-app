
#ifndef ESTATEMENTDLG_H
#define ESTATEMENTDLG_H
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
// ^FILE   : EStatementDlg.h
// ^AUTHOR : Shaobo Huang
// ^DATE   : 
//
// ^CLASS    : EStatementDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : This is the code for the eStatement screen
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

class EStatementDlg : public BaseMainDlg
{
// Construction
public:
   EStatementDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   virtual ~EStatementDlg();

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
                         );
// Dialog Data
   //{{AFX_DATA(EStatementDlg)
   enum
   {
      IDD = IDD_ESTATEMENT
   };
   CButton m_btnStop;
   CButton m_btnHome;
   CButton m_btnForward;
   CButton m_btnBack;
   CWebBrowser m_browserCtrl;
   CAnimation  m_Animate;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(EStatementDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

   // Generated message map functions
   //{{AFX_MSG(EStatementDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnWebback();
   afx_msg void OnWebfwd();
   afx_msg void OnWebhome();
   afx_msg void OnWebstop();
   afx_msg void OnCommandStateChangeBushtml(long Command, BOOL Enable);
   afx_msg void OnDownloadBeginBushtml();
   afx_msg void OnDownloadCompleteBushtml();
   afx_msg void OnSize(UINT nType, int cx, int cy);
   DECLARE_EVENTSINK_MAP()
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   public:
   void SetHomeFocus();                                           // method to set focus on home key
   DString BuildRequestURL();

private:
   DString CalculateCZValue(DString& companyCode);

   HWND         m_hwndParent;       // Parent window handle
   CString      m_csFileDir;        // Path to data files
   struct ST_CTRL_SIZE
   {
      int   ctrlID;
      CRect ctrlRect;
   };
   ST_CTRL_SIZE* m_stCtrlSize[15];  //defined bigger to hold all child controls for simplicity
   int m_stCount;
};

#endif // ESTATEMENTDLG_H
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/EStatementDlg.h-arc  $
//
//   Rev 1.3   Mar 21 2003 18:36:20   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Oct 09 2002 23:55:40   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   13 Aug 2002 14:14:00   HUANGSHA
//Modification for requesting parameters
//
//   Rev 1.0   31 Jul 2002 09:44:12   HUANGSHA
//Initial revision.
 * 
 */
