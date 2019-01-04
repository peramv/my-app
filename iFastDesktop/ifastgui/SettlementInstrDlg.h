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
//    Copyright 2004 by International Financial Data Service
//
//******************************************************************************
//
// ^FILE   : SettlementInstrDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SettlementInstrDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <ifastgui\ifasthistoricalinfo.hpp>

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
class SettlementInstrDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
	SettlementInstrDlg( CWnd* pParent, 
						     GenericInterfaceContainer* pGIC, 
							  GenericInterface* pGIParent, 
							  const Command& rCommand );

	//{{AFX_DATA(SettlementInstrDlg)
	enum
	{
      IDD = IDD_SETTLEMENT_INSTRUCTIONS
	};
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SettlementInstrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	virtual bool doRefresh( GenericInterface *, const I_CHAR *);

	// Generated message map functions
	//{{AFX_MSG(SettlementInstrDlg)
	virtual BOOL OnInitDialog();   
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();   
	afx_msg void OnBtnReset();
	afx_msg void OnBtnHistorical();
	afx_msg void OnBtnAdmDates();
	afx_msg void OnBtnAddSettlInstr();
	afx_msg void OnBtnDelSettlInstr();
	afx_msg void OnBtnResetSettlInstr();	
	afx_msg void OnBtnHistoricalSettlInstr();
	afx_msg void OnBtnAdmDatesSettlInstr();	
	//}}AFX_MSG

   virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut );
   virtual void OnPostInitDialog();	
   virtual void ControlUpdated( UINT controlID, const DString &strValue );   
   void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);

   DECLARE_MESSAGE_MAP()

public:	

private:
		
  /**
   * Will be overriden at Account or Fund Broker level
   */
	virtual void setSettlementInstructionsControls();	
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/SettlementInstrDlg.h-arc  $
//
//   Rev 1.1   Nov 19 2004 17:33:34   aguilaam
//PET117_FN21: settlement instructions enhancement (temporary check-in for build)
//
//   Rev 1.0   Oct 13 2004 15:40:26   VADEANUM
//Initial revision.
//
