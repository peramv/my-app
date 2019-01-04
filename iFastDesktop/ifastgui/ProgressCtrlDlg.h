#ifndef PROGRESSCTRLDLG_H
#define PROGRESSCTRLDLG_H
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
// ^FILE   : ProgressCtrlDlg.h
// ^AUTHOR : Serban Popescu
// ^DATE   : July 2008
//
// ^CLASS    : ProgressCtrlDlg
//
// ^CLASS DESCRIPTION : This is the code for the ProgressCtrlDlg screen
//
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#include <configmanager.hpp>

class ProgressCtrlDlg : public BaseMainDlg
{
public:
   ProgressCtrlDlg (CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/)
   {  // Nothing to refresh here
      return true;
   }

// Dialog Data
   //{{AFX_DATA(ProgressCtrlDlg)
   enum
   {
      IDD = IDD_PROGRESS_DLG
   };
   CProgressCtrl m_ProgressCtrl;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ProgressCtrlDlg)

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

private:
   // Generated message map functions
   //{{AFX_MSG(ProgressCtrlDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnTimer (UINT nIDEvent);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   UINT m_dataLoadTimer;
   int pos;
template <class _X> 
   SEVERITY checkAsyncRetrieve_X ( _X *&pXMember);

};

#endif // ProgressCtrlDlg_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ProgressCtrlDlg.h-arc  $
//
//   Rev 1.2   24 Jul 2008 12:01:28   popescu
//Incident - 1190617 - set all the data init calls to be asynch
//
//   Rev 1.1   18 Jul 2008 13:53:46   popescu
//Incident - 1190617 - added a WM_CLOSE message that will automatically close the dialog
//
//   Rev 1.0   17 Jul 2008 15:11:52   popescu
//Initial revision.
 * 
 *
 */
