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
// ^FILE     : AcctCutOffTimesDlg.h
// ^CLASS    : AcctCutOffTimesDlg
// ^SUBCLASS : BaseMainDlg
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
class AcctCutOffTimesDlg : public BaseMainDlg
{
public:
	AcctCutOffTimesDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
//{{AFX_DATA(AcctCutOffTimesDlg)
	enum
	{
		IDD = IDD_ACCT_CUT_OFF_TIMES
	};
//}}AFX_DATA

// ClassWizard generated virtual function overrides
//{{AFX_VIRTUAL(AcctCutOffTimesDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//}}AFX_VIRTUAL

protected:
	virtual bool doRefresh( GenericInterface *, const I_CHAR *);

	// Generated message map functions
	//{{AFX_MSG(AcctCutOffTimesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnReset();
	afx_msg void OnBtnAdmin();
	afx_msg void OnBtnMore();
	afx_msg void OnBtnHistorical();
	afx_msg void OnBtnSearch();
	afx_msg void OnBtnResetSearch();
	//}}AFX_MSG

	virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut );
	virtual void OnPostInitDialog();
	virtual bool GetDataForControl(UINT controlID, DString &strValueOut, bool bFormatted, int index ) const;
	virtual SEVERITY doInit();
	virtual bool doDisablePermCheckButton(UINT nID);

	void SetDlgCaption();
	LRESULT OpenBrokerListDlg(WPARAM, LPARAM);
	LRESULT OpenFundClassListDlg(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()

private:
	void getHeadingList(BFFieldId& idField);
	void setNetworkSenderCaption();
	void setBrokerCaption();
	void SetDisabledItems(bool isDisabled);

	DString	dstrEntityId;
	DString	dstrBrokerLevel;
	
	bool isAccountLevel;
	bool isNetworkSenderLevel;
	bool isBrokerLevel;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/AcctCutOffTimesDlg.h-arc  $
//
//   Rev 1.2   Nov 28 2011 10:22:22   popescu
//P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
//
//   Rev 1.1   Jul 21 2006 16:38:16   jankovii
//PET 2192 FN02 - Dealings - Sender Cut Off Time.
//
//   Rev 1.0   Jul 05 2005 17:41:26   hernando
//Initial revision.
