// AddressBookDlg.cpp : implementation file
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
// ^FILE   :AddressBookDlg.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 11/05/1999
//
// ^CLASS    : AddressBookDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include "stdafx.h"
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include "mfdstc.h"
#include "addressbookdlg.h"
#include <ifastbp\addressprocessincludes.h>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <uibase\dstedit.h>
#include <uibase\dstcfuncs.h>
#include <uibase\dstlistctrl.h>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0071_vw.hpp>
#include <ifastdataimpl\dse_dstc0072_req.hpp>
#include <ifastdataimpl\dse_dstc0113_vw.hpp>
#include <ifastbp\nasuprocessincludes.h>
#include <configmanager.hpp>
#include "CanAddressBookDlg.h"
#include "CanAddressBookF02Dlg.hpp"


extern CLASS_IMPORT const I_CHAR* CMD_GUI_ADDRESSES;
#include <bfproc\concretedialogcreator.hpp>

struct addressDialogCreator
{
   GenericInterface* operator()( GenericInterfaceContainer* pGIC, 
                                 GenericInterface* pGIParent,
                                 const Command& rCommand ) const { 
      DString strMarket = DSTCommonFunctions::getMarket();
      if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
      {
         DString dstrAddrForm;
         pGIParent->getField(NULL,ifds::ShrAddressFormat,dstrAddrForm,false);
         dstrAddrForm.strip();
         if( strMarket == MARKET_IDS::LUXEMBOURG ) dstrAddrForm = I_("01");
         if( dstrAddrForm == I_("02") ) 
            return ( new CanAddressBookF02Dlg( NULL, pGIC, pGIParent, rCommand ) );
         else 
            return ( new CanAddressBookDlg( CanAddressBookDlg::IDD, NULL, pGIC, pGIParent, rCommand ) );			 
      }
      else if( strMarket == MARKET_IDS::JAPAN )
      {
         return( new AddressBookDlg( NULL, pGIC, pGIParent, rCommand ) );
      }
      return( NULL );
   }
};

static ConcreteDialogCreator< AddressBookDlg, addressDialogCreator > dlgCreator( CMD_GUI_ADDRESSES );

#ifdef _DEBUG
   #undef THIS_FILE
static char THIS_FILE[]=__FILE__;
   #define new DEBUG_NEW
#endif

namespace
{  
   const I_CHAR *CLASSNAME             = I_( "AddressBookDialog" );
   const I_CHAR *LV_ADDRESS_LIST       = I_( "AddressList" );
   const I_CHAR *LV_ADDRESS_MAIL_LIST  = I_( "AddressMailList" );
   const I_CHAR *SPACE_STRING          = I_( " " ); 
   const I_CHAR *EMPTY_STRING          = I_( "" );
   const I_CHAR *ADDRESS               = I_("Address");
   const I_CHAR *ADDRESSCODE           = I_("AddrCode");
   const I_CHAR *ADDRESSCODEDESC       = I_("AddrCodeDesc");
   const I_CHAR *ADDRESSLINE           = I_( "AddressLine" );
   const I_CHAR *TYPE                  = I_( "Type" );
   const I_CHAR *HOLD                  = I_( "Hold");
   const I_CHAR *SERVEAGENT            = I_( "Service Agent" );
   const I_CHAR *COPIES                = I_( "Number Copies" );
   const I_CHAR *Y_STRING              = I_( "Y" );
   const I_CHAR *GRID_WINDOW           = I_( "GridWindow" ) ;

   const I_CHAR *GridWindow            = I_( "AddressBookDialog" ) ;

   const I_CHAR *SERVICEAGENT          = I_( "ServiceAgent" ) ;
   const I_CHAR *NUMBERCOPIES          = I_( "NumberCopies" ) ;
   const I_CHAR *WORKSTATION           = I_( "WORKSTATION" );
   const I_CHAR *DEFAULTWORKSTATION    = I_("DefaultWorkstation");
   const    int   DISPLAYCODEALL       = 0;
   const    int   DISPLAYCODESELECT    = 1;

   const I_CHAR *const STUB_MODE = I_( "STUB_MODE" );
   const I_CHAR *const OFFLINE   = I_( "OFFLINE" );
}

namespace ADDRLIT
{
   const BFFieldId REG_ADDR_READ_ONLY(101);
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ShareholderAddressHeadingVerifySet;
}

//-------------------------------------------------------------------
// Construction/Destruction
//--------------------------------------------------------------------

AddressBookDlg::AddressBookDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseAddressBookDlg( AddressBookDlg::IDD, pParent, pGIC, pGIParent, rCommand )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//**************************************************************************************
void AddressBookDlg::addControls()
{
   BaseAddressBookDlg::addControls( );
   AddControl( CTRL_EDIT, IDC_EDT_ENTITY_NAME, IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::AddrDesc, CTRLFLAG_NOT_UPDATABLE, IDC_LV_ADDRESSES );
   AddControl( CTRL_COMBO, IDC_CMB_ENTITY_ADDRESS_CODE, IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::AddrCode, CTRLFLAG_NOT_UPDATABLE, IDC_LV_ADDRESSES );
   AddControl( CTRL_EDIT, IDC_SHAREHOLDER_KANA, IFASTBP_PROC::ADDRESSES_LIST, 
               ifds::kShareholderAddress,CTRLFLAG_FIELDS_FROM_SUB_LIST, IDC_LV_ADDRESSES );
   AddControl( CTRL_COMBO, IDC_CMB_PREFECTURE, IFASTBP_PROC::ADDRESSES_LIST, 
               ifds::CountryCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ADDRESSES );
   AddControl( CTRL_EDIT, IDC_EDT_CITY, IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::City, CTRLFLAG_NOT_UPDATABLE, IDC_LV_ADDRESSES );
   AddControl( CTRL_EDIT, IDC_EDT_PROVINCE, IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::ProvinceName, CTRLFLAG_NOT_UPDATABLE, IDC_LV_ADDRESSES );

   AddControl( CTRL_EDIT, IDC_TXT_ROLE, IFASTBP_PROC::ENTITY_LIST, 
               ifds::EntityType, CTRLFLAG_NOT_UPDATABLE, IDC_LV_ADDRESSES );


   //Kanji & Kana converting
   DSTEdit* pKanjiEdit = dynamic_cast<DSTEdit*>(GetDlgItem(IDC_SHAREHOLDER_ADDRESS));
   DSTEdit* pKanaEdit  = dynamic_cast<DSTEdit*>(GetDlgItem(IDC_SHAREHOLDER_KANA));
   pKanjiEdit->SetKanaEdit(pKanaEdit);

   AddControl( CTRL_COMBO, IDC_CMB_CONFIRM, IFASTBP_PROC::ADDRESSES_LIST, 
               ifds::Confirm, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ADDRESSES );

}
//**************************************************************************************
void AddressBookDlg::LoadShareHolderAddress()
{
   BaseAddressBookDlg::LoadShareHolderAddress( );
   ConnectControl(IDC_EDT_ENTITY_NAME,false);
   ConnectControl(IDC_CMB_ENTITY_ADDRESS_CODE,false);
   ConnectControl(IDC_SHAREHOLDER_KANA,true);
   ConnectControl(IDC_CMB_PREFECTURE,true);
   ConnectControl(IDC_EDT_CITY,false);
   ConnectControl(IDC_EDT_PROVINCE,false);
}
//---------------------------------------------------------------------------------------
void AddressBookDlg::LoadEntityAddress()
{

   BaseAddressBookDlg::LoadEntityAddress( );
   ConnectControl(IDC_CMB_CODE,false);
   ConnectControl(IDC_EDT_ENTITY_NAME,true);
   ConnectControl(IDC_CMB_ENTITY_ADDRESS_CODE,true);
   ConnectControl(IDC_SHAREHOLDER_KANA,false);
   ConnectControl(IDC_CMB_PREFECTURE,false);
   ConnectControl(IDC_EDT_CITY,true);
   ConnectControl(IDC_EDT_PROVINCE,true);
}
//-----------------------------------------------------------------------------------
void AddressBookDlg::ShowShareHolder(bool bFreshList) 
{

   BaseAddressBookDlg::ShowShareHolder(bFreshList);
   GetDlgItem (IDC_STATIC_ENTITY_NAME)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_EDT_ENTITY_NAME)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_ADDRESS_CODE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_ENTITY_ADDRESS_CODE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_PREFECTURE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_PREFECTURE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_SHAREHOLDER_KANA)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_KANA)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_ENTITY_COUNTRY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_ENTITY_COUNTRY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_EDT_PROVINCE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_PROVINCE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_EDT_CITY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_EDT_PROVINCE)->ShowWindow (SW_HIDE);

}

//---------------------------------------------------------
void AddressBookDlg::ShowEntity() 
{

   BaseAddressBookDlg::ShowEntity();
   GetDlgItem (IDC_STATIC_ENTITY_NAME)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_EDT_ENTITY_NAME)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_ENTITY_ADDRESS_CODE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_ENTITY_ADDRESS_CODE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_PREFECTURE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_PREFECTURE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_SHAREHOLDER_KANA)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_KANA)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_PROVINCE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_ENTITY_COUNTRY)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_ENTITY_COUNTRY)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_EDT_PROVINCE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_EDT_CITY)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_BTN_CHANGE)->ShowWindow (SW_SHOW);
   GetDlgItem(IDC_CMB_CODE)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_BTN_ADD)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_BTN_DELETE)->ShowWindow (SW_HIDE);

}
//*************************************************************
bool AddressBookDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{
   DString str;  
   bool bRet = BaseAddressBookDlg::GetOverrideItemString(lSubstituteId,ColumnKey,strOut);

   if( lSubstituteId == ifds::ShareholderAddressHeadingVerifySet.getId() )
   {
      if( ColumnKey== ADDRESS )
      {
         DString strPostalCode;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::PostalCode, strPostalCode );
         strPostalCode.strip();
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrLine1, str );
         str.strip();
         strOut = str+SPACE_STRING ;//reset the old value
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrLine2, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrLine3, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrLine4, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrLine5, str );
         str.strip();
         strPostalCode += SPACE_STRING;
         strOut = strPostalCode + strOut;
         bRet = true;
      }
   }

   return(bRet);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AddressBookDlg.cpp-arc  $
 * 
 *    Rev 1.56   Jan 22 2010 09:05:44   dchatcha
 * IN# 1982767 - REl 97 - Static Data - Display of Verified status.
 * 
 *    Rev 1.55   Dec 03 2009 03:51:44   dchatcha
 * PET0166583 FN02 FN03 - Static Verification Phase 2.
 * 
 *    Rev 1.54   Apr 21 2003 14:35:42   YINGBAOL
 * For Market Lux, we don't support Address format "02"
 * 
 *    Rev 1.53   Mar 21 2003 18:31:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.52   Feb 07 2003 16:31:18   HSUCHIN
 * bug fix for dialog creation based on system option
 * 
 *    Rev 1.51   Feb 06 2003 13:41:10   YINGBAOL
 * change address dialoge creator
 * 
 *    Rev 1.50   Oct 09 2002 23:55:28   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.49   Sep 13 2002 15:13:52   YINGBAOL
 * clean up address
 * 
 *    Rev 1.48   Aug 29 2002 20:09:24   SMITHDAV
 * CellProperties fixes
 * 
 *    Rev 1.47   Aug 29 2002 12:57:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.46   Aug 23 2002 11:39:06   HSUCHIN
 * address enhancement for Name2
 * 
 *    Rev 1.45   Aug 13 2002 10:32:16   YINGBAOL
 * roll back name2 from address list to shareholder
 * 
 *    Rev 1.44   Aug 06 2002 10:11:02   KOVACSRO
 * only add a new address if not already added.
 * 
 *    Rev 1.43   Jul 29 2002 16:28:48   YINGBAOL
 * get Name from address instead of shareholder
 * 
 *    Rev 1.42   Jul 09 2002 11:49:10   YINGBAOL
 * 1. refresh mailing
 * 2. fix entity address
 * 
 *    Rev 1.41   Jul 05 2002 11:57:56   HERNANDO
 * PTS 10008165 - Changed Adr Code to Combo-box w/Drop-down list.
 * 
 *    Rev 1.40   Jul 05 2002 10:40:32   PURDYECH
 * Include file cleanup.
 * 
 *    Rev 1.39   22 May 2002 19:15:36   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.38   01 Apr 2002 16:23:08   HSUCHIN
 * PTS 10007114 - dialog enhancement, The salutation combo box now has blank as an option.
 * 
 *    Rev 1.37   27 Mar 2002 20:00:52   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.36   Jan 28 2002 11:27:20   YINGBAOL
 * HLLAPI Change
 * 
 *    Rev 1.35   27 Nov 2001 11:05:10   KOVACSRO
 * Changed doDisablePerrmCheckButtons.
 * 
 *    Rev 1.34   05 Nov 2001 15:46:34   KOVACSRO
 * hasPermission() changes
 * 
 *    Rev 1.33   Jul 20 2001 11:12:04   YINGBAOL
 * always show selection on the list control
 * 
 *    Rev 1.32   19 Apr 2001 17:11:42   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.31   Apr 12 2001 18:29:42   DINACORN
 * Disable some controls in Demo mode
 * 
 *    Rev 1.30   Apr 02 2001 11:19:32   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.29   30 Mar 2001 17:42:36   KOVACSRO
 * Permission check stuff.
 * 
 *    Rev 1.28   27 Mar 2001 16:43:36   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.27   Mar 22 2001 15:11:04   YINGBAOL
 * introduce user defined mask for number of copies
 * 
 *    Rev 1.26   01 Mar 2001 16:37:16   KOVACSRO
 * Modifications for permission check.
 * 
 *    Rev 1.25   Feb 16 2001 15:26:32   YINGBAOL
 * implement Save and Load stingery settings
 * 
 *    Rev 1.24   Feb 12 2001 16:20:32   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.23   Feb 05 2001 10:35:28   YINGBAOL
 * fix crash for M3 
 * 
 *    Rev 1.22   Dec 13 2000 14:34:54   KOVACSRO
 * 1. Modified DoListItemChanged, DoPrelistItemChanged
 * 2.Added Dummy Item logic for perm. check.
 * 
 *    Rev 1.21   Dec 05 2000 17:17:34   KOVACSRO
 * Added new item permission logic.
 * 
 *    Rev 1.20   Dec 01 2000 14:39:58   KOVACSRO
 * Added permission check.
 * 
 *    Rev 1.19   Oct 24 2000 11:38:58   KOVACSRO
 * set the max. length for postal code field, other minor changes.
 * 
 *    Rev 1.18   Oct 20 2000 13:34:48   YINGBAOL
 * adjust stingery width
 * 
 *    Rev 1.17   Oct 17 2000 14:22:58   YINGBAOL
 * fix create address and mailing procedure isuue
 * 
 *    Rev 1.16   Oct 05 2000 11:56:36   KOVACSRO
 * Disabled 'Delete' button for Registration Address when it is read only;
 * 
 *    Rev 1.15   Oct 05 2000 11:06:08   KOVACSRO
 * Moved PostalCode at the end of the address for non Japanesse.
 * 
 *    Rev 1.14   Sep 29 2000 13:29:16   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.13   Sep 23 2000 11:27:50   YINGBAOL
 * fix issues in entity adress and so on
 * 
 *    Rev 1.12   Aug 22 2000 12:01:40   YINGBAOL
 * check NasuFlag
 * 
 *    Rev 1.11   Aug 21 2000 15:27:40   YINGBAOL
 * add second record for Account des. 2,or 3
 * 
 *    Rev 1.10   Aug 11 2000 14:24:56   KOVACSRO
 * fixes
 * 
 *    Rev 1.9   Aug 02 2000 16:57:54   KOVACSRO
 * added Addtl reg. and disabled address for Acc.Des. 2 and 3, for AddrCode '01'
 * 
 *    Rev 1.8   Jul 19 2000 10:17:46   YINGBAOL
 * fix crash for entity address
 * 
 *    Rev 1.7   Jul 18 2000 10:51:02   KOVACSRO
 * Disabled Entity RB
 * 
 *    Rev 1.6   Jul 17 2000 17:11:48   KOVACSRO
 * Added RegAddress not updatable for Acc. Des. = 2 OR 3
 * 
 *    Rev 1.5   Jul 11 2000 13:54:50   YINGBAOL
 * add country for Shareholder
 * 
 *    Rev 1.4   Jul 04 2000 11:19:14   YINGZ
 * delete couple of unused functions
 * 
 *    Rev 1.3   Jun 02 2000 14:06:32   BUZILA
 * disabling AdminDates button inside NASU
 * 
 *    Rev 1.2   Apr 03 2000 14:28:48   DT24433
 * use ShowAdminDates, removed unused headers
 * 
 *    Rev 1.1   Mar 15 2000 10:25:30   VASILEAD
 * Updates for C2
 * 
 *    Rev 1.0   Feb 15 2000 11:01:04   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.48   Feb 09 2000 10:51:20   YINGBAOL
 * fix
 * 
 *    Rev 1.47   Jan 30 2000 17:17:48   YINGBAOL
 * fix
 * 
 *    Rev 1.46   Jan 29 2000 15:40:56   YINGBAOL
 * fix
 * 
 *    Rev 1.45   Jan 28 2000 14:44:42   YINGBAOL
 * check in for release
 * 
 *    Rev 1.44   Jan 26 2000 18:15:26   YINGBAOL
 * fix
 * 
 *    Rev 1.43   Jan 25 2000 18:05:00   YINGBAOL
 * fix
 * 
 *    Rev 1.42   Jan 24 2000 11:57:48   YINGBAOL
 * fix
 * 
 *    Rev 1.41   Jan 21 2000 10:36:44   YINGBAOL
 * added error process
 * 
 *    Rev 1.40   Jan 17 2000 15:22:02   YINGBAOL
 * hllapi change sync
 * 
 *    Rev 1.39   Jan 14 2000 15:29:48   YINGBAOL
 * modify resource sync.
 * 
 *    Rev 1.38   Jan 07 2000 17:14:06   YINGBAOL
 * modify window caption
 * 
 *    Rev 1.37   Jan 06 2000 17:11:38   HUANGSHA
 * kanji-kana for address
 * 
 *    Rev 1.36   Jan 06 2000 16:54:14   YINGBAOL
 * change set focus
 * 
 *    Rev 1.35   Dec 30 1999 15:38:32   YINGBAOL
 * ?
 * 
 *    Rev 1.34   Dec 30 1999 14:17:06   YINGBAOL
 * fix NFCAddrMailing
 * 
 *    Rev 1.33   Dec 30 1999 10:31:48   YINGBAOL
 * added NFCAddr Field
 * 
 *    Rev 1.32   Dec 23 1999 16:44:08   BUZILA
 * warning taken out
 * 
 *    Rev 1.31   Dec 22 1999 10:16:38   YINGBAOL
 * check in for release
 * 
 *    Rev 1.30   Dec 21 1999 10:15:32   YINGBAOL
 * added validation
 * 
 *    Rev 1.29   Dec 17 1999 14:15:10   YINGBAOL
 * change address code
 * 
 *    Rev 1.28   Dec 13 1999 10:41:16   YINGBAOL
 * 

  */
