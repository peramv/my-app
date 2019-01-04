
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
// ^FILE   : AMSDeltaAllocDlg.h
// ^AUTHOR : Thanisorn S.
// ^DATE   : Jan. 10,2018
//
// ^CLASS    : AMSDeltaAllocDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the AMS Delta screen.
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

class AMSDeltaAllocDlg : public BaseMainDlg
{
public:

   AMSDeltaAllocDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   enum
   {
      IDD = IDD_AMS_DELTA_ALLOC
   };

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:

   virtual bool doRefresh(GenericInterface * /*rpGICaller*/, 
                          const I_CHAR * /*szOriginalCommand*/
                         );
   virtual SEVERITY doInit();
   virtual BOOL OnInitDialog();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   afx_msg void OnBtnAdmDates();
   
   virtual void OnPostInitDialog();
   virtual void DoListItemChanged(UINT listControlID,
                                  const DString &strKey,
                                  bool bIsNewItem ,
                                  bool bIsDummyItem
                                 );
   virtual void ControlUpdated(UINT controlID,const DString &strValue);

private:
   bool addControls();
   void DisableControls();

   UINT m_uiDialogItem;

   DString _dstrAmsCode;
   DString _dstrAccountNum;
};