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
// ^FILE     : UserDefMatDlg.h
// ^CLASS    : UserDefMatDlg
// ^SUBCLASS : BaseMainDlg
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
class UserDefMatDlg : public BaseMainDlg
{
public:

   UserDefMatDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //{{AFX_DATA(UserDefMatDlg)
   enum
   {
      IDD = IDD_USER_DEF_MAT
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(UserDefMatDlg)
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

   virtual bool doRefresh( GenericInterface *, const I_CHAR *);
   virtual SEVERITY doInit();

   // Generated message map functions
   //{{AFX_MSG(UserDefMatDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnReset();

   //}}AFX_MSG

   virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut );
   virtual void OnPostInitDialog();
   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual bool GetDataForControl(UINT controlID, DString &strValueOut, bool bFormatted, int index ) const;
   virtual void DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem , bool bIsDummyItem);

   DECLARE_MESSAGE_MAP()

private:

   DString m_dstrAccountNumber;
   DString m_dstrShareholderNumber;
   DString m_dstrIsContract;
   DString m_dstrSegTransExist;
	DString m_dstrModPerm;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/UserDefMatDlg.h-arc  $
//
//   Rev 1.1   Feb 14 2006 14:15:06   zhengcon
//Incident #528284 - add one field ModPerm for updatable permission of User Defined Maturity Date of converted account
//
//   Rev 1.0   Mar 21 2005 11:40:34   hernando
//Initial revision.
//
//   Rev 1.0   Feb 21 2005 09:59:38   hernando
//Initial revision.
