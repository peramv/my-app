
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
//    Copyright 2002 by International Financial Data Service
//
//******************************************************************************
//
// ^FILE   : AmsLmtOverrideDlg.h
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov. 12,2002
//
// ^CLASS    : AmsLmtOverrideDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

class AMSHypoAllocDlg : public BaseMainDlg
{
public:

   AMSHypoAllocDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   enum
   {
      IDD = IDD_AMS_HYPOCALC_ALLOC
   };

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:

   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/
						 );
  
   virtual SEVERITY doInit();
   virtual BOOL PreTranslateMessage(MSG* pMsg);
 
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDel();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   virtual void OnPostInitDialog();
   virtual void DoListItemChanged(
                           UINT listControlID,
                           const DString &strKey,
                           bool bIsNewItem ,
                           bool bIsDummyItem
                           );
   virtual bool doDisablePermCheckButton(UINT nID);

	virtual void ControlUpdated(UINT controlID, const DString &strValue);

private:
	bool addControls();
    void EnableControls( );
	LRESULT OpenFundClassListDlg( WPARAM, LPARAM );

	UINT    m_uiDialogItem;
    DString _dstrAmsCode;
    DString _dstrAmsType;
    DString _dstrEffectiveDate;
	DString _dstrFromScr; 

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AMSHypoAllocDlg.h-arc  $
//   Rev 1.0   Jul 24 2017 Thanisorn S.
//Initial Revision
//
*/