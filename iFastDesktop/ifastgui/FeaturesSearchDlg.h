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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FeaturesSearchDlg.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/03
//
// ^CLASS    : FeaturesSearchDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <uibase\listctrl.h>
#include <uibase\combobase.h>
#include <uibase\dstdatetimectrl.h>

class FeaturesSearchDlg : public BaseMainDlg
{
public:
   // standard constructor
   FeaturesSearchDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(FeaturesSearchDlg)
   enum
   {
      IDD = IDD_FEATURES_SEARCH
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FeaturesSearchDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh(
      GenericInterface * /*rpGICaller*/, 
      const I_CHAR * /*szOriginalCommand*/ );
   virtual SEVERITY doInit();
   virtual void ControlUpdated(
      UINT controlID, 
      const DString &strValue);
   virtual void OnPostInitDialog();
   virtual bool PreCancel();

   // Generated message map functions
   //{{AFX_MSG(FeaturesSearchDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnAdd();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   void getBrokerFieldId (BFFieldId &brokerId);
   UINT getBrokerEditControlId();
private:
//methods
   LRESULT OpenBrokerListDlg(WPARAM, LPARAM);
   LRESULT OpenBranchListDlg(WPARAM, LPARAM);
   LRESULT OpenSlsRepListDlg(WPARAM, LPARAM);
   LRESULT OpenFundListDlg  (WPARAM, LPARAM);
   LRESULT OpenFeeModelDlg  (WPARAM, LPARAM);
   LRESULT OpenFndBrkrListDlg  (WPARAM, LPARAM);
   bool isBrokerSearchField();
   bool isBranchSearchField();
   bool isSlsRepSearchField();
   bool isFundCodeSearchField();
   bool isClassCodeSearchField();
   bool isFeeModelSearchField();
   bool isSponsorSearchField();
   bool isFndBrkrForAggregatedOrderSearchField();
   void SetDlgCaption();
   UINT getBranchEditControlId();
   UINT getSlsRepEditControlId();
   UINT getFeeModelEditControlId();
   UINT getAggFndBrkrEditControlId();
   bool discardUpdates();
   bool shouldSetTheCaller();
//properties
   CWnd* m_pWndItemInFocus;
   DString m_dstrBackgroundSearch;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FeaturesSearchDlg.h-arc  $
//
//   Rev 1.4   Jan 13 2011 05:59:42   wichian
//IN#2319580 - Add New fund broker button on Feature Search screen.
//
//   Rev 1.3   Mar 25 2009 07:23:20   kitticha
//IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search.
//
//   Rev 1.2   Aug 10 2004 11:28:14   FENGYONG
//PET 1117 FN5 - Client Condition Fee
//
//   Rev 1.1   Jan 28 2004 21:35:32   popescu
//PET 859, FN 23, modified resources (dialogs and menu item) and coded for the features search dialog
//
//   Rev 1.0   Oct 04 2003 16:10:36   popescu
//Initial revision.
//
//   Rev 1.5   Jul 29 2003 15:25:36   popescu
//Check if there are updates before cancelling the dialog/diasbled the update flag at the dialog level
//
//   Rev 1.4   Jul 10 2003 22:21:34   popescu
//check in for payment instruct, used mfcan_ip_param for some interporcess param passing
//
//   Rev 1.3   Jul 10 2003 12:53:32   popescu
//fixed compilation error
//
//   Rev 1.2   Jul 09 2003 21:57:38   popescu
//Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
//
//   Rev 1.1   Jul 01 2003 18:05:02   popescu
//Added the discard/cancel dialog if user clicks search again; changed the children processes to modeless, instead of modal
//
//   Rev 1.0   Jun 27 2003 18:18:10   popescu
//Initial revision.
//
 * 
 */
