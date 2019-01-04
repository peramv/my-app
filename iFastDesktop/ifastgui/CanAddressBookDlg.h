#ifndef CANADDRESSBOOKDLG_H
#define CANADDRESSBOOKDLG_H
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
// ^FILE   : CanAddressBookDlg.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : September 3,2002
//
// ^CLASS    : CanAddressBookDlg
// ^SUBCLASS : CanMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\BaseAddressBookDlg.h>


class CanAddressBookDlg : public BaseAddressBookDlg
{
public:
	CanAddressBookDlg(UINT nIDD, CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~CanAddressBookDlg(){}
   enum
   {
      IDD = IDD_ADDRESSBOOK
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
protected:
   //{{AFX_VIRTUAL(AddressBookDlg)
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //}}AFX_VIRTUAL
// Implementation
   protected:
   // Generated message map functions
   //{{AFX_MSG(AddressBookDlg)

//	DECLARE_MESSAGE_MAP()

	virtual void OnSelRetMail();
   //}}AFX_MSG

   protected:

   virtual bool GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut);
   virtual void addControls();
   virtual void ShowShareHolder(bool bFreshList);  
   virtual void ShowEntity(); 
   virtual void LoadEntityAddress();
   virtual void LoadShareHolderAddress();
   virtual void SetAddressControlsReadOnly(bool bReadOnly);
   virtual bool doDisableControl(UINT nID, bool bIsNew);
   virtual void ControlUpdated( UINT controlID, const DString &strValue );
};

#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/CanAddressBookDlg.h-arc  $
//
//   Rev 1.6   Sep 29 2008 07:58:06   wongsakw
//PET5517 FN71 Unclaimed Property - Return Mail
//
//   Rev 1.5   Sep 22 2008 08:47:18   wongsakw
//PET5517 FN71 Unclaimed Property
//
//   Rev 1.4   Jul 30 2003 16:59:48   FENGYONG
//Add control update
//
//   Rev 1.3   Mar 21 2003 18:33:58   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Feb 06 2003 10:22:14   linmay
//modified constructor
//
//   Rev 1.1   Oct 09 2002 23:55:34   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.0   Sep 13 2002 15:51:14   YINGBAOL
//Initial revision.
 * 



  */