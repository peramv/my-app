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
// ^FILE   : GIAInvAttribListDlg.h
// ^CLASS  : GIAInvAttribListDlg
// ^SUBCLASS : BaseMainDlg
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif


class GIAInvAttribDlg : public BaseMainDlg
{
public:

   GIAInvAttribDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   //{{AFX_DATA(GIAInvAttribListDlg)
   enum
   {
      IDD = IDD_GIA_INVEST_ATTRIBS
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(GIAInvAttribListDlg)
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
   //{{AFX_MSG(GIAInvAttribListDlg)
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()

private:

   void SetDlgCaption ();
   DString	m_dstrAccountNum,
      m_dstrCaller;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/GIAInvAttribDlg.h-arc  $
//
//   Rev 1.2   Dec 03 2011 01:30:54   dchatcha
//P0186477/FN03 - GIA - Purchase
//
//   Rev 1.1   Nov 27 2011 19:44:24   popescu
//INA Commission Work
//
// Initial revision.
**/