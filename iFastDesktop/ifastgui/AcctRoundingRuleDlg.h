#ifndef ACCT_ROUNDING_RULE_DLG_H
#define ACCT_ROUNDING_RULE_DLG_H

#if _MSC_VER > 1000
   #pragma once
#endif

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
//    Copyright 2008 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AcctRoundingRuleDlg.h
// ^AUTHOR : 
// ^DATE   :
//
// ^CLASS    : AcctRoundingRuleDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
    #include <ifastgui\BaseMainDlg.h>
#endif

#include <ifastgui\ifasthistoricalinfo.hpp>

// AcctRoundingRuleDlg dialog

class AcctRoundingRuleDlg : public BaseMainDlg
{
public:
    AcctRoundingRuleDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
                        GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
    enum { IDD = IDD_ACCT_ROUNDING_RULE };

    //{{AFX_VIRTUAL(AcctSttlmntRuleDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support    
    //}}AFX_VIRTUAL

    //{{AFX_MSG(AcctSttlmntRuleDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnBtnAdd();
    afx_msg void OnBtnDelete();
    afx_msg void OnBtnReset();    
    afx_msg void OnBtnMore();
	afx_msg void OnBtnHistorical(); 
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

// Implementation
protected:
    void OnPostInitDialog();

    virtual SEVERITY doInit();
    virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                            const I_CHAR * /*szOriginalCommand*/
                            );

	virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut );
	void SetDlgCaption();	
	void DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem );

	LRESULT OpenFundClassListDlg( WPARAM, LPARAM );

private:

	void enableDisableControls();

};
#endif 

