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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AddressDialog.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : 09/06/2002
//
// ^CLASS    : AdminDatesDialog
// ^SUBCLASS : BaseAddressBookDlg
//
// ^CLASS DESCRIPTION : the class  will dealing Japenese Address 
//
//******************************************************************************

#include <ifastgui\BaseAddressBookDlg.h>

class AddressBookDlg : public BaseAddressBookDlg
{
public:
   AddressBookDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~AddressBookDlg(){}
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


   //}}AFX_MSG

   protected:

   virtual bool GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut);
   virtual void addControls();
   virtual void ShowShareHolder(bool bFreshList);  
   virtual void ShowEntity(); 
   virtual void LoadEntityAddress();
   virtual void LoadShareHolderAddress();

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AddressBookDlg.h-arc  $
 * 
 *    Rev 1.24   Mar 21 2003 18:32:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.23   Oct 09 2002 23:55:28   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.22   Sep 13 2002 15:13:54   YINGBAOL
 * clean up address
 * 
 *    Rev 1.21   Aug 29 2002 12:57:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.20   Aug 23 2002 11:39:08   HSUCHIN
 * address enhancement for Name2
 * 
 *    Rev 1.19   Jul 09 2002 11:48:38   YINGBAOL
 * 1. refresh mailing 
 * 2. fix entity address
 * 
 *    Rev 1.18   22 May 2002 19:15:38   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.17   19 Mar 2002 13:44:26   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.16   27 Nov 2001 11:04:10   KOVACSRO
 * Changed doDisablePerrmCheckButtons.
 * 
 *    Rev 1.15   19 Apr 2001 17:12:18   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.14   Apr 12 2001 18:30:44   DINACORN
 * Add isDemoMode() method
 * 
 *    Rev 1.13   30 Mar 2001 17:43:18   KOVACSRO
 * Permission check stuff.
 * 
 *    Rev 1.12   Mar 22 2001 15:11:00   YINGBAOL
 * introduce user defined mask for number of copies
 * 
 *    Rev 1.11   Feb 16 2001 15:26:28   YINGBAOL
 * implement Save and Load stingery settings
 * 
 *    Rev 1.10   Dec 13 2000 14:35:50   KOVACSRO
 * 1. Modified DoListItemChanged, DoPreListItemChanged
 * 
 *    Rev 1.9   Oct 17 2000 14:22:54   YINGBAOL
 * fix create address and mailing procedure isuue
 * 
 *    Rev 1.8   Oct 05 2000 11:54:00   KOVACSRO
 * Added DoPrelistItemChanged();
 * 
 *    Rev 1.7   Sep 23 2000 11:27:54   YINGBAOL
 * fix issues in entity adress and so on
 * 
 *    Rev 1.6   Aug 11 2000 14:25:18   KOVACSRO
 * fixes
 * 
 *    Rev 1.5   Aug 02 2000 16:58:18   KOVACSRO
 * added Addtl reg. and disabled address for Acc.Des. 2 and 3, for AddrCode '01'
 * 
 *    Rev 1.4   Jul 17 2000 17:12:38   KOVACSRO
 * Added RegAddress not updatable for Acc. Des. = 2 OR 3
 * 
 *    Rev 1.3   Jul 04 2000 11:19:16   YINGZ
 * delete couple of unused functions
 * 
 *    Rev 1.2   Apr 03 2000 14:30:00   DT24433
 * use ShowAdminDates, removed unused headers
 * 
 *    Rev 1.1   Mar 08 2000 13:41:54   DT24433
 * added missing DBR identifier
 * 
 */

