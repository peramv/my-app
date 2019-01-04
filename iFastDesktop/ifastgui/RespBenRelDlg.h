
#ifndef RESPBENRELDLG_H
#define RESPBENRELDLG_H

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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RespBenRelDlg.h
// ^AUTHOR : Robert Kovacs
// ^DATE   : 11/05/1999
//
// ^CLASS    : RespBenRelDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
/*#ifndef LISTCTRL_H
#include <uibase\listctrl.h>
#endif*/
#ifndef COMBOBASE_H
   #include <uibase\combobase.h>
#endif



/////////////////////////////////////////////////////////////////////////////
// RespBenRelDlg dialog

class RespBenRelDlg : public BaseMainDlg
{
// Construction
public:
   RespBenRelDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(RespBenRelDlg)
   enum
   {
      IDD = IDD_RESP_BEN_REL
   };
   CButton m_BtnRemove;
   CButton m_BtnJoin;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(RespBenRelDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(RespBenRelDlg)
   afx_msg void OnSelchangeCmbRespBen();
   afx_msg void OnBtnJoin();
   afx_msg void OnBtnRemove();
   afx_msg void OnBtnReset();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   BOOL OnInitDialog();
   void OnPostInitDialog();
   virtual SEVERITY doInit();
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );
   //void DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem , bool bIsDummyItem);


private:

   DString m_strNASUFlag;
   DString _strAccountNum;
   DString _strCurrentRespBenKey;
   DString _strInitialRespName;//RESP ben. initially selected in the combo
   void FillRespBenCombo();
   void FillLVToJoin();
   void FillLVJoined();
   void setTitle();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESPBENRELDLG_H__2AC2F0B3_5D72_11D4_BEC0_00C04F58DD3B__INCLUDED_)
