
#ifndef BROKERLISTDLG_H
#define BROKERLISTDLG_H
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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : BrokerListDlg.h
// ^AUTHOR : Winnie Shiu
// ^DATE   : January 17, 2000
//
// ^CLASS    : BrokerListDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Remarks dialog
//
//
//
// -----------------------------------------------------------------------------

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

class BrokerListDlg : public BaseMainDlg
{
// Construction
public:
   BrokerListDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   void SetDlgCaption(DString &strDlgCaption);

// Dialog Data
   //{{AFX_DATA(BrokerListDlg)
   enum
   {
      IDD = IDD_BROKER_LIST
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(BrokerListDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(BrokerListDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnDblclkLvBroker(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnMore();
   //}}AFX_MSG
   void OnPostInitDialog();
   virtual SEVERITY doInit();
   virtual bool doRefresh(GenericInterface * rpGICaller, 
      const I_CHAR *szOriginalCommand);
   virtual bool GetDataForControl(UINT controlID,
      DString &strValueOut, bool bFormatted, int index) const;
   virtual bool SetDataFromControl(UINT controlID,
      const DString &strValue, bool bFormatted, SEVERITY &sevRtn, int index);
   virtual void ControlUpdated(
      UINT controlID, const DString &strValue);
   DECLARE_MESSAGE_MAP()
private:
   DString m_dstrCaller;
   DString m_strSearchUsing;
};

#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BrokerListDlg.h-arc  $
 * 
 *    Rev 1.8   Apr 06 2009 04:11:28   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. - additional code changes for More button
 * 
 *    Rev 1.7   Mar 25 2009 07:21:06   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search.
 * 
 *    Rev 1.6   Jul 10 2003 22:21:36   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.5   Mar 21 2003 18:33:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:55:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   19 Mar 2002 13:44:32   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.2   Mar 06 2000 16:41:48   DT24433
 * cosmetic
 * 
 *    Rev 1.1   Feb 25 2000 11:21:42   POPESCUS
 * fixes
// 
//    Rev 1.2   Jan 24 2000 18:11:34   POPESCUS
// some fixes
// 
//    Rev 1.1   Jan 22 2000 15:42:12   WINNIE
// To get search work

*/