#ifndef ACCOUNTDETAILSDLG_H
#define ACCOUNTDETAILSDLG_H

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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AccountDetailsDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : AccountDetailsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

#ifndef BASEACCOUNTDETAILSDLG_H
   #include <ifastgui\BaseAccountDetailsDlg.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// AccountDetailsDlg dialog

class AccountDetailsDlg : public BaseAccountDetailsDlg
{
// Construction
public:
   AccountDetailsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(AccountDetailsDlg)
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AccountDetailsDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual void BtnAdminDates();
   virtual void RbPendingTrades();
   virtual void RbTransHistory();
   virtual void SetfocusLvEntitiesIds(NMHDR* pNMHDR, LRESULT* pResult);
   virtual void SetfocusLvHistoryTrades(NMHDR* pNMHDR, LRESULT* pResult);
   virtual void SetfocusLbOptions();
   virtual void SetfocusLbCautions();
   virtual void SetfocusLbAttrib();
   virtual void SetfocusLvFunds(NMHDR* pNMHDR, LRESULT* pResult);
   virtual void SetfocusLvEntities(NMHDR* pNMHDR, LRESULT* pResult);
   virtual void fillShrAddressList();
   virtual void ItemchangedLvAccounts(int index);
   virtual void SetfocusLvAccounts(NMHDR* pNMHDR, LRESULT* pResult);
   virtual void fillAddressSelectList();

   // Generated message map functions
   //{{AFX_MSG(AccountDetailsDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccountDetailsDlg.h-arc  $
 * 
 *    Rev 1.4   Mar 21 2003 18:30:40   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.3   Oct 09 2002 23:55:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   04 Feb 2002 15:22:44   KOVACSRO
 * Changed the parameter for ItemchangedLvAccounts
 * 
 *    Rev 1.1   10 Aug 2001 14:24:50   HSUCHIN
 * added pvcs log entries and beautify source
*/