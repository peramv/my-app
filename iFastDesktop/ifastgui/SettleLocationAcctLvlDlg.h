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
// ^FILE   : SettleLocationAcctLvlDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SettleLocationAcctLvlDlg
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
class SettleLocationAcctLvlDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   SettleLocationAcctLvlDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //{{AFX_DATA(SettleLocationAcctLvlDlg)
   enum
   {
      IDD = IDD_SETTLEMENT_LOCATION_ACCTLVL
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SettleLocationAcctLvlDlg)
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

   virtual bool doRefresh( GenericInterface *, const I_CHAR *);

   // Generated message map functions
   //{{AFX_MSG(SettleLocationAcctLvlDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDel();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnHistorical();
   //}}AFX_MSG

   virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut );
   virtual void OnPostInitDialog();
	virtual bool doDisablePermCheckButton(UINT nID);
   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual bool GetDataForControl(UINT controlID, DString &strValueOut, bool bFormatted, int index ) const;
   void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);

   DECLARE_MESSAGE_MAP()

public:

		virtual bool filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag);

private:

   void EnableControls( );
   void ClearEnableChildControls( );
   void checkPermissionForInqUpdate();
};

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/SettleLocationAcctLvlDlg.h-arc  $
//
//   Rev 1.1   Feb 27 2004 15:59:52   HERNANDO
//PET965 FN11 - Added DoListItemChanged.
//
//   Rev 1.0   Nov 24 2003 17:59:26   HERNANDO
//Initial revision.
