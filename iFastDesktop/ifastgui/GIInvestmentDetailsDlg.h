//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2011 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : GIInvestmentDetailsListDlg.h
// ^CLASS  : GIInvestmentDetailsListDlg
// ^SUBCLASS : BaseMainDlg
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif


class GIInvestmentDetailsDlg : public BaseMainDlg
{
public:

   GIInvestmentDetailsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   void DoListItemChanged( UINT listControlID, const DString &strKey, 
                           bool isNewItem, bool bIsDummyItem);

   //{{AFX_DATA(GIInvestmentDetailsListDlg)
   enum
   {
      IDD = IDD_GI_INVESTMENT_DETAILS
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(GIInvestmentDetailsListDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );
   // Generated message map functions
   //{{AFX_MSG(SettlementDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   virtual void OnPostInitDialog();
   virtual SEVERITY doInit ();
   virtual void OnCancel ();

   virtual void ControlUpdated( UINT controlID, const DString &strValue );

   // Generated message map functions
   //{{AFX_MSG(GIInvestmentDetailsListDlg)
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()

private:

   void SetDlgCaption ();
   DString	m_dstrAccountNum;
   DString  m_dstrCaller;
   bool m_ReadOnly;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/GIInvestmentDetailsDlg.h-arc  $
//
//   Rev 1.2   Mar 21 2012 16:29:06   if991250
//IN 2885623 - GI Money Out - Error handling
//
//   Rev 1.1   Feb 17 2012 10:38:32   if991250
//GI Invest
//
//   Rev 1.0   Jan 12 2012 10:26:08   jankovii
//Initial revision.
//
// Initial revision.
**/