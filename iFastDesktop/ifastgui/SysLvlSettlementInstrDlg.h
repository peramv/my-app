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
// ^FILE   : SysLvlSettlementInstrDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SysLvlSettlementInstrDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\ifasthistoricalinfo.hpp>

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
class SysLvlSettlementInstrDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   SysLvlSettlementInstrDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //{{AFX_DATA(SysLvlSettlementInstrDlg)
   enum
   {
      IDD = IDD_SETTLEMENT_INSTRUCTION_SYSLVL
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SysLvlSettlementInstrDlg)
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

   // Generated message map functions
   //{{AFX_MSG(SysLvlSettlementInstrDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDel();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnHistorical();
   //}}AFX_MSG

   virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut );
   virtual void OnPostInitDialog();
	virtual bool doDisablePermCheckButton(UINT nID);
   void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);
   virtual void ControlUpdated( UINT controlID, const DString &strValue );

   DECLARE_MESSAGE_MAP()

private:

   void EnableControls( );
   void ClearEnableChildControls( );
   void checkPermissionForInqUpdate();

   bool m_bIsEntryNew;
};

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/SysLvlSettlementInstrDlg.h-arc  $
//
//   Rev 1.0   Oct 13 2004 15:38:02   VADEANUM
//Initial revision.
//
//   Rev 1.0   Nov 24 2003 16:52:10   HERNANDO
//Initial revision.
