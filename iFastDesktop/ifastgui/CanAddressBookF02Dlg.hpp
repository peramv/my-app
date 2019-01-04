#ifndef CANADDRESSBOOKF02DLG_H
#define CANADDRESSBOOKF02DLG_H
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
//    Copyright 2002 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : CanAddressBookF02Dlg.h
// ^AUTHOR : Yingbao  Li, May Lin
// ^DATE   : Feb. 03,2003
//
// ^CLASS    : CanAddressBookF02Dlg
// ^SUBCLASS : CanAddressBookDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\CanAddressBookDlg.h>


class CanAddressBookF02Dlg : public CanAddressBookDlg
{
public:
   CanAddressBookF02Dlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~CanAddressBookF02Dlg(){}
   enum
   {
      IDD = IDD_CAN_ADDRESSBOOK_F02
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
protected:
   //{{AFX_VIRTUAL(CanAddressBookF02Dlg)
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //}}AFX_VIRTUAL
// Implementation
   protected:
   // Generated message map functions
   //{{AFX_MSG(CanAddressBookF02Dlg)

//	DECLARE_MESSAGE_MAP()


   //}}AFX_MSG

   protected:

   virtual bool GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut);
   virtual void addControls();
   virtual void ShowShareHolder(bool bFreshList);  
   virtual void ShowEntity(); 
   virtual void SetAddressControlsReadOnly(bool bReadOnly);
   virtual bool doDisableControl(UINT nID, bool bIsNew);
   virtual const BFFieldId getAddressSubId();

   virtual void LoadEntityAddress();
   virtual void LoadShareHolderAddress();
   virtual void DoListItemChanged (UINT listControlID, const DString &strKey, bool bIsNewItem , bool bIsDummyItem);

   virtual void DoRefreshUncliamedRelatedFieldsForAddrCode01( void );
   virtual void OnSelRetMail();
};

#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/CanAddressBookF02Dlg.hpp-arc  $
//
//   Rev 1.6   Jan 25 2010 22:59:06   dchatcha
//IN# 1983880 - Rel 97 Static Data - Status of Nom (01 Reg address) is set to Unverified.
//
//   Rev 1.5   Aug 18 2009 11:18:40   jankovii
//IN 1794778 - Skip Vlaidation box misplaced on DK screeen
//
//   Rev 1.4   May 30 2005 15:51:12   porteanm
//Incident 252121 - Don't load shareholder controls when in Entity mode.
//
//   Rev 1.3   Mar 21 2003 18:34:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Feb 06 2003 13:42:36   YINGBAOL
//make getAddressSubId() virtual 
//
//   Rev 1.1   Feb 06 2003 10:23:38   linmay
//created
//
//   Rev 1.0   Feb 05 2003 13:39:10   linmay
//Initial Revision

  */