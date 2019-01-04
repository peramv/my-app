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
// ^FILE   : EstateAllocationListDlg.h
// ^CLASS  : EstateAllocationListDlg
// ^SUBCLASS : BaseMainDlg
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif


class EstateAllocationDlg : public BaseMainDlg
{
public:

   EstateAllocationDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   void DoListItemChanged( UINT listControlID, const DString &strKey, 
                           bool isNewItem, bool bIsDummyItem);
   void EstateAllocationDlg::OnBtnAddress();

   //{{AFX_DATA(EstateAllocationListDlg)
   enum
   {
      IDD = IDD_ESTATE_ALLOCATION
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(EstateAllocationListDlg)
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
   //{{AFX_MSG(EstateAllocationListDlg)
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
/* $Log:   Y:/VCS/BF iFAST/ifastgui/EstateAllocationDlg.h-arc  $
//
//   Rev 1.0   25 Jul 2012 15:28:28   if991250
//Initial revision.
//
**/