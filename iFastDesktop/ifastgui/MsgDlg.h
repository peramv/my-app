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
// ^FILE     : MsgDlg.h
// ^CLASS    : MsgDlg
// ^SUBCLASS : BaseMainDlg
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
class MsgDlg : public BaseMainDlg
{
public:

   MsgDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //{{AFX_DATA(MsgDlg)
   enum
   {
      IDD = IDD_MSG
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(MsgDlg)
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

   virtual bool doRefresh( GenericInterface *, const I_CHAR *);

   // Generated message map functions
   //{{AFX_MSG(MsgDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnDetail();
   afx_msg void OnBtnTrade();
   afx_msg void OnBtnAggrOrder();

   //}}AFX_MSG

   virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut );
   virtual void OnPostInitDialog();
//	virtual bool doDisablePermCheckButton(UINT nID);
   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual bool GetDataForControl(UINT controlID, DString &strValueOut, bool bFormatted, int index ) const;
   virtual void DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem , bool bIsDummyItem);
   virtual SEVERITY doInit();

   DECLARE_MESSAGE_MAP()

private:

   DString DisableAggrOrder;
   DString DisableTrade;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/MsgDlg.h-arc  $
//
//   Rev 1.1   Apr 19 2005 13:38:04   hernando
//Incident #292495 - Added doInit.
//
//   Rev 1.0   Feb 21 2005 09:59:38   hernando
//Initial revision.
