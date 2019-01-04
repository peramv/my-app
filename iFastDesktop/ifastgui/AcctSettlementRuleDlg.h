#ifndef ACCT_LVL_STTLMNT_RULE_DLG_H
#define ACCT_LVL_STTLMNT_RULE_DLG_H

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
// ^FILE   : AcctLvlSttlmntRuleDlg.h
// ^AUTHOR : Chatchai Daecha
// ^DATE   : Febuary 2008
//
// ^CLASS    : AcctLvlSttlmntRuleDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
    #include <ifastgui\BaseMainDlg.h>
#endif

// AcctLvlSttlmntRuleDlg dialog

class AcctLvlSttlmntRuleDlg : public BaseMainDlg
{
public:
    AcctLvlSttlmntRuleDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
                          GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
    enum { IDD = IDD_ACCT_CONTRL };

    //{{AFX_VIRTUAL(AcctLvlSttlmntRuleDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

    //{{AFX_MSG(AcctLvlSttlmntRuleDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnBtnAdd();
    afx_msg void OnBtnDelete();
    afx_msg void OnBtnReset();
    afx_msg void OnBtnAdmin();
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
    LRESULT OpenFundClassListDlg( WPARAM, LPARAM );


private:

};
#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AcctSettlementRuleDlg.h-arc  $ */
//
//   Rev 1.1   Apr 16 2008 18:34:14   daechach
//PET2385 FN02&07 - Modified code regarding code review.
