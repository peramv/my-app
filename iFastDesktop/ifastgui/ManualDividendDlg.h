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
//    Copyright 2003 by International Financial Data Service
//
//******************************************************************************
//
// ^FILE   : ManualDividendDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : ManualDividendDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
class ManualDividendDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   ManualDividendDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //{{AFX_DATA(ManualDividendDlg)
   enum
   {
      IDD = IDD_MANUALDIVIDEND
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ManualDividendDlg)
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL PreTranslateMessage(MSG* pMsg);

   //}}AFX_VIRTUAL

protected:

   virtual bool doRefresh( GenericInterface *, const I_CHAR *);
   virtual bool doSend ( GenericInterface *rpGICaller, 
                         const I_CHAR *szMessage);
   virtual void OnPostInitDialog();
   virtual void ControlUpdated ( UINT controlID, 
                                 const DString &strValue);

   virtual void DoListItemChanged (UINT listControlID,
                                   const DString &strKey, 
                                   bool bIsNewItem, 
                                   bool bIsDummyItem);

   afx_msg void OnEnKillfocusEdtAccount();
   afx_msg void OnEnKillfocusEdtNumUnitEligDividends();
   afx_msg void OnEnKillfocusEdtNumUnitDividends();
   afx_msg void OnEnKillfocusEdtAmount();

   // Generated message map functions
   //{{AFX_MSG(ManualDividendDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDel();
   afx_msg void OnBtnBank();
   afx_msg void OnBtnDilutions();
   //}}AFX_MSG
   virtual bool PreOk();
   DECLARE_MESSAGE_MAP()

private:

   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
   LRESULT OpenSelectAddressDlg( WPARAM, LPARAM );
   LRESULT OpenIdnAccountsDlg( WPARAM, LPARAM );
   void EnableControls( );
   void ClearEnableChildControls();
   void DisplayPayTypeRelated (const DString &dstrPayType);
   void DisplayToFundCodeRelated (const DString &dstrToFund);

   void RoundByNumDigit(const DString& inValue, 
                        DString& roundedValue, 
                        int& iNumDigit);

   void ConvertToStringWithNumDigit(const double& dInValue, 
                                    DString& roundedValue, 
                                    int& iNumDigit);
                                    
   void UpdateAmountTypeDollar(void);
   void UpdateAmountTypeUnit(void);
   void MakeMaskWithNumDigit(DString& strOutMask, int& iNumDigit);
   void DisplayBankControls(BOOL bShow);
   void UpdateControlsByTranstype(DString &transType);
   void ClearControlValues();

private:
   bool m_bFundNumberSupported;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ManualDividendDlg.h-arc  $
//
//   Rev 1.5   Aug 17 2009 08:22:34   dchatcha
//IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop.
//
//   Rev 1.4   Nov 22 2005 09:34:44   zhengcon
//Incident #458410 -- fixed the cursor flashing problem
//
//   Rev 1.3   May 27 2005 10:10:44   popescu
//Incident # 319459 - fixed the Manual Dividend reset issue - also used WorkSessionTradesList for manual dividends; use the TradesProcess instead of ManualDividendProcess
//
//   Rev 1.2   Jan 19 2004 09:32:54   HERNANDO
//PTS10025436 - Added PreOk to display a message before validation/Confirmation as requested.
//
//   Rev 1.1   Jun 26 2003 16:22:54   HERNANDO
//PTS 10018774 - Added DisplayToFundCodeRelated.
//
//   Rev 1.0   May 22 2003 17:03:52   HERNANDO
//Initial revision.
*/