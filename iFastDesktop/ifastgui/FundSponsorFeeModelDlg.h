#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial Ltd.
//
//******************************************************************************
//
// ^FILE   : FundSponsorFeeModelDlg.h
// ^AUTHOR : 
// ^DATE   : 07/26/04
//
// ^CLASS    : FundSponsorFeeModelDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>


#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// FundSponsorFeeModelDlg dialog

class FundSponsorFeeModelDlg : public BaseMainDlg
{
// Construction
public:
   FundSponsorFeeModelDlg ( CWnd* pParent, 
                            GenericInterfaceContainer* pGIC, 
                            GenericInterface* pGIParent, 
                            const Command& rCommand);
   ~FundSponsorFeeModelDlg();

// Dialog Data
   //{{AFX_DATA(FundSponsorFeeModelDlg)
   enum
   {
      IDD = IDD_FEE_MODEL_FUND_SPONSOR
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FundSponsorFeeModelDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(FundSponsorFeeModelDlg)
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAddFeeParam();
   afx_msg void OnBtnDelFeeParam();
   afx_msg void OnBtnFeeParamMore();
   afx_msg void OnBtnAddFundSponsor();
   afx_msg void OnBtnDelFundSponsor();
   afx_msg void OnBtnFundSponsorMore();
   afx_msg void OnBtnAddScale();
   afx_msg void OnBtnDelScale();
   afx_msg void OnBtnAdmDates(); 
   afx_msg void OnRbAccount();
   afx_msg void OnRbShareholder();
   afx_msg void OnSelSearchAccount();
   afx_msg void OnSelchangeCmbAccountNum();   
   afx_msg void OnKillfocusSearchModelCode();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   /**
    * Required implementation for the refresh method.  No refresh activity is
    * performed for this class.
    * @param rpGICaller - A reference pointer to the calling object.
    * @param szOriginalCommand - A string literal representing the original
    * command issuing the refresh (which may provide a hint on whether this
    * object needs to check for refresh).
    * @returns true if successful, call getErrors for errors if false
    */
   bool doRefresh ( GenericInterface * /*rpGICaller*/, 
                    const I_CHAR *); /*szOriginalCommand*/
   /**
     * This method is invoked by the base architecture after OnInitDialog has 
     * completed.  This should be implemented for time intensive setup so that
     * the screen can display quickly and then do this processing.
     */
   void OnPostInitDialog();


   /**
     * This method is optional - override if subclass needs to implement.
     * The override should perform any initialization 
     * required, including getting parameters from InterProcessData (they get
     * cleared after this call).
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   SEVERITY doInit();


   virtual void ControlUpdated ( UINT controlID,
                                 const DString &strValue);
   bool ListViewControlFilter ( long lSubstituteId, const DString *);
   bool GetOverrideItemString (long lSubstituteId, const DString &ColumnKey, DString &strOut);

private:
   UINT  uFeeModelCtrlID; 
   
   LRESULT OpenFeeModelDlg  (WPARAM, LPARAM);   
   bool ListFilterRelateChange (UINT nID);
   void SetDlgCaption();
   void addControls( );
   void DispSearchTypeRelated();
   void displayModelOptionRelateControls();
   void displayFeeParamTypeRelatedControls();
   void ShowScaleRelateControls( bool bShow );
   void ShowFeeRelateControls( bool bShow );
   void SearchModelCodeRelateChange();
   DString m_dstrFundSponsorCode;
   DString m_dstrFeeModelCode;
   DString m_dstrSearchType;
   DString m_AcctNum;
   DString m_ShrNum;
   DString m_fromScr;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FundSponsorFeeModelDlg.h-arc  $
//
//   Rev 1.8   Jul 13 2005 17:38:58   popescu
//Incident 352435 - improved performance on the fund sponsor fee model screen - get rid of the wacky keys
//
//   Rev 1.7   Nov 02 2004 11:21:58   FENGYONG
//PTS10035397 - Add dummy record for the filter result
//
//   Rev 1.6   Sep 29 2004 11:12:12   FENGYONG
//PET1117FN5 - chnage after ESS walkthrough
//
//   Rev 1.5   Sep 27 2004 14:07:46   FENGYONG
//fix after code review
//
//   Rev 1.4   Sep 24 2004 18:51:22   FENGYONG
//Add function dodisable...
//
//   Rev 1.3   Sep 02 2004 12:33:00   FENGYONG
//PET1117 FN5 - Client Fee
//
//   Rev 1.2   Aug 11 2004 18:42:50   FENGYONG
//Temp PET 1117 FN5 check in for second coder use
//
//   Rev 1.1   Aug 10 2004 11:28:48   FENGYONG
//PET 1117 FN5 - Client Condition Fee
//
//   Rev 1.0   Aug 09 2004 09:56:42   FENGYONG
//Initial Revision
//
//   Rev 1.7   Apr 04 2003 16:05:32   PURDYECH
//Sync 1.6.2.0 back to trunk
//
//   Rev 1.6.2.0   Mar 21 2003 18:36:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6.1.0   Mar 05 2003 11:31:22   PURDYECH
//Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
//
//   Rev 1.6   Feb 20 2003 09:28:06   YINGBAOL
//add doDisableControl and doDisablePermCheckButton
//
//   Rev 1.5   Jan 29 2003 16:22:26   popescu
//Added the historical button for FeeParamSysDlg and FundSponsorFeeModelDlg
//
//   Rev 1.4   Jan 22 2003 17:49:22   YINGBAOL
//clean some unused code
//
//   Rev 1.3   Jan 03 2003 19:39:30   YINGBAOL
//add logic for commission Group
//
//   Rev 1.2   Oct 09 2002 23:55:40   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   Feb 22 2002 14:17:28   YINGBAOL
//add more function
//
*/
