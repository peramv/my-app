// CanAddressBookF02Dlg.cpp : implementation file
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
// ^FILE   :CanAddressBookF02Dlg.cpp
// ^AUTHOR : Yingbao  Li, May Lin
// ^DATE   : Feb. 3, 2003
//
// ^CLASS    : CanAddressBookF02Dlg
// ^SUBCLASS : CanAddressBookDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include "stdafx.h"
#include "mfdstc.h"
#include "CanAddressBookF02Dlg.hpp"
#include "CanAddressBookDlg.h"
#include "BaseAddressBookDlg.h"

#include <ifastbp\addressprocessincludes.h>
#include <ifastbp\addressprocess.hpp>
#include <uibase\dstlistctrl.h>
#include <uibase\dsttabctrl.h>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0071_vw.hpp>
#include <ifastdataimpl\dse_dstc0072_req.hpp>
#include <ifastdataimpl\dse_dstc0113_vw.hpp>
#include <ifastbp\nasuprocessincludes.h>
#include <ifastcbo\dstcworksession.hpp>

#ifdef _DEBUG
   #undef THIS_FILE
static char THIS_FILE[]=__FILE__;
   #define new DEBUG_NEW
#endif

namespace
{  
   const I_CHAR *CLASSNAME                = I_( "CanAddressBookF02Dialog" );
   const I_CHAR *ADDRESS                  = I_("Address");
   const I_CHAR *SPACE_STRING             = I_( " " ); 
   const I_CHAR* const TAB_ADDR_INFO      = I_("Address Info");
   const I_CHAR* const TAB_RETMAIL_INFO   = I_("Return Mail Info");
   const I_CHAR *YES                      = I_( "Y" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ShareholderAddressHeadingVerifySet;
   extern CLASS_IMPORT const BFTextFieldId DskPCLookEnb;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDRESS_LOOKUP_BROWSER;

//**************************************************************************************
// Construction/Destruction
//**************************************************************************************

CanAddressBookF02Dlg::CanAddressBookF02Dlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: CanAddressBookDlg( CanAddressBookF02Dlg::IDD, pParent, pGIC, pGIParent, rCommand )

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//**************************************************************************************
void CanAddressBookF02Dlg::addControls()
{
   CanAddressBookDlg::addControls( );
   AddControl( CTRL_COMBO, IDC_CMB_SHR_PROVINCE, IFASTBP_PROC::ADDRESSES_LIST, 
               ifds::ProvinceCanadaUS, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ADDRESSES );
   AddControl( CTRL_EDIT, IDC_EDT_SHR_CITY, IFASTBP_PROC::ADDRESSES_LIST, 
               ifds::City,0 /*CTRLFLAG_FIELDS_FROM_SUB_LIST*/, IDC_LV_ADDRESSES );
   AddControl( CTRL_STATIC, IDC_STATIC_SHR_CITY);
   AddControl( CTRL_STATIC, IDC_STATIC_SHR_PROVINCE);
   AddControl( CTRL_STATIC,IDC_BTN_LOOKUP, CTRLFLAG_GUI_FIELD);
   AddControl( CTRL_CHECKBOX, IDC_CB_SKIP_VAL, IFASTBP_PROC::ADDRESSES_LIST, ifds::SkipValidate, CTRLFLAG_DEFAULT, IDC_LV_ADDRESSES);

   BaseAddressBookDlg::m_pMailInfoTabCtrl->registerControl(IDC_CMB_SHR_PROVINCE, TAB_ADDR_INFO);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->registerControl(IDC_EDT_SHR_CITY, TAB_ADDR_INFO);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->registerControl(IDC_STATIC_SHR_CITY, TAB_ADDR_INFO);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->registerControl(IDC_STATIC_SHR_PROVINCE, TAB_ADDR_INFO);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->registerControl(IDC_BTN_LOOKUP, TAB_ADDR_INFO);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->registerControl(IDC_CB_SKIP_VAL, TAB_ADDR_INFO);
}

//**************************************************************************************
void CanAddressBookF02Dlg::OnSelRetMail() 
{
    CanAddressBookDlg::OnSelRetMail();

    if (!IsShareholder() && m_strCurrentMailingPageName == I_("Return Mail Info"))
    {
        GetDlgItem(IDC_BTN_ENTITY_LOOKUP)->ShowWindow(SW_HIDE);
    }
}


//**************************************************************************************
void CanAddressBookF02Dlg::ShowShareHolder(bool bFreshList) 
{
   CanAddressBookDlg::ShowShareHolder(bFreshList);
   GetDlgItem (IDC_EDT_SHR_CITY)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_SHR_PROVINCE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHR_CITY)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHR_PROVINCE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_BTN_LOOKUP)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_BTN_ENTITY_LOOKUP)->ShowWindow (SW_HIDE);

   // when radio changed, skip validation should be visible depend on address code as well.
   DString dstrNominee,dstrAddrCode;

   getParent()->getField(this,ADDRLIT::REG_ADDR_READ_ONLY,dstrNominee,false);
   getParent()->getField(this,IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrCode,dstrAddrCode,false);

   dstrAddrCode.strip();

   bool bShow = dstrNominee == YES && I_("01") == dstrAddrCode ? false : true;

   GetDlgItem (IDC_CB_SKIP_VAL)->ShowWindow (SW_SHOW && bShow);
}

//**************************************************************************************
void CanAddressBookF02Dlg::ShowEntity() 
{

   CanAddressBookDlg::ShowEntity();
   GetDlgItem (IDC_EDT_SHR_CITY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_SHR_PROVINCE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_SHR_CITY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_SHR_PROVINCE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_BTN_LOOKUP)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CB_SKIP_VAL)->ShowWindow (SW_HIDE);
   
   DString dstrDskPCLookEnb;
   dynamic_cast<DSTCWorkSession*>(getBFWorkSession())->getOption(ifds::DskPCLookEnb, dstrDskPCLookEnb, getParent()->getDataGroupId(), false);

   GetDlgItem (IDC_BTN_ENTITY_LOOKUP)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_BTN_ENTITY_LOOKUP)->EnableWindow(dstrDskPCLookEnb.stripAll().upperCase() == YES);
}

//**************************************************************************************
bool CanAddressBookF02Dlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{
   DString str;  
   bool bRet = BaseAddressBookDlg::GetOverrideItemString(lSubstituteId,ColumnKey,strOut);

   if( lSubstituteId == ifds::ShareholderAddressHeadingVerifySet.getId() )
   {
      if( ColumnKey== ADDRESS )
      {
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
         bRet = true;
      }
   }

   return(bRet);
}

//***********************************************************************************************
void CanAddressBookF02Dlg::SetAddressControlsReadOnly(bool bReadOnly)
{
   BaseAddressBookDlg::SetAddressControlsReadOnly(bReadOnly);
   GetDlgItem( IDC_CMB_SHR_PROVINCE )->EnableWindow(!bReadOnly);  
   GetDlgItem( IDC_EDT_SHR_CITY )->EnableWindow(!bReadOnly);    
}

//**********************************************************************************************
bool CanAddressBookF02Dlg::doDisableControl(UINT nID, bool bIsNew)
{
   if( nID == IDC_CMB_SHR_PROVINCE || nID == IDC_EDT_SHR_CITY )
   {
      return disableControlForAddress01();
   }
   else return(CanAddressBookDlg::doDisableControl( nID,bIsNew ));
}

//**********************************************************************************************
const BFFieldId CanAddressBookF02Dlg::getAddressSubId()
{
   return ifds::ShareholderAddressF02;
}

//**************************************************************************************
void CanAddressBookF02Dlg::LoadShareHolderAddress()
{
   CanAddressBookDlg::LoadShareHolderAddress( );
   
   ConnectControl(IDC_EDT_SHR_CITY, true );  
   ConnectControl(IDC_CMB_SHR_PROVINCE, true);   
   ConnectControl(IDC_BTN_LOOKUP, true );
   ConnectControl(IDC_CB_SKIP_VAL, true );
}

//**************************************************************************************
void CanAddressBookF02Dlg::LoadEntityAddress()
{
   CanAddressBookDlg::LoadEntityAddress();

   ConnectControl(IDC_EDT_SHR_CITY,     false );  
   ConnectControl(IDC_CMB_SHR_PROVINCE, false ); 
   ConnectControl(IDC_CB_SKIP_VAL,      false );
}

//**************************************************************************************************************
void CanAddressBookF02Dlg::DoListItemChanged (UINT ListControlID, const DString &strKey, bool bIsNewItem , bool bIsDummyItem)
{
   CanAddressBookDlg::DoListItemChanged (ListControlID, strKey, bIsNewItem, bIsDummyItem);

   if(IsShareholder())
   {
   DString m_dstrPCLookupEnabled;
   getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST,      ifds::PCLookupEnabled, m_dstrPCLookupEnabled, false );

   GetDlgItem(IDC_BTN_LOOKUP)->EnableWindow( m_dstrPCLookupEnabled == I_("Y") ? TRUE : FALSE );

   DString dstrNominee,dstrAddrCode;

   getParent()->getField(this,ADDRLIT::REG_ADDR_READ_ONLY,dstrNominee,false);
   getParent()->getField(this,IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrCode,dstrAddrCode,false);

   dstrAddrCode.strip();

   bool bShow = dstrNominee == YES && I_("01") == dstrAddrCode ? false : true;

   m_pMailInfoTabCtrl->showTabControl(IDC_CB_SKIP_VAL, 0, bShow);

   if (bShow)
   {
      DString m_skipVal;
      getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST,      ifds::SkipValidate, m_skipVal, false );

      if ( m_skipVal == I_("1") )
      {
         ((CButton *) GetDlgItem (IDC_CB_SKIP_VAL))->SetCheck(1);
      }
      else
      {
         ((CButton *) GetDlgItem (IDC_CB_SKIP_VAL))->SetCheck(0);
      }
   }
   }
}

//******************************************************************************
void CanAddressBookF02Dlg::DoRefreshUncliamedRelatedFieldsForAddrCode01()
{
   // actually it would be only INVESCO to be able to refresh these fields..
   AddressProcess* pProcess = 
      dynamic_cast<AddressProcess*>(getParent());

   if ( pProcess )
   {
      pProcess->refreshUnclaimedFields( getParent()->getDataGroupId() );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/CanAddressBookF02Dlg.cpp-arc  $
// 
//    Rev 1.9   Jan 25 2010 23:00:10   dchatcha
// IN# 1983880 - Rel 97 Static Data - Status of Nom (01 Reg address) is set to Unverified.
// 
//    Rev 1.8   Jan 22 2010 09:08:42   dchatcha
// IN# 1982767 - REl 97 - Static Data - Display of Verified status.
// 
//    Rev 1.7   Dec 03 2009 03:48:24   dchatcha
// PET0166583 FN02 FN03 - Static Verification Phase 2.
// 
//    Rev 1.6   Aug 18 2009 12:09:48   jankovii
// IN 1794778 - Skip Vlaidation box misplaced on DK screeen
// 
//    Rev 1.5   Aug 18 2009 11:17:56   jankovii
// IN 1794778 - Skip Vlaidation box misplaced on DK screeen
// 
//    Rev 1.4   Sep 22 2008 08:47:32   wongsakw
// PET5517 FN71 Unclaimed Property
// 
//    Rev 1.3   May 30 2005 15:53:18   porteanm
// Incident 252121 - Don't load shareholder controls when in Entity mode.
// 
//    Rev 1.2   Mar 21 2003 18:34:00   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Feb 06 2003 10:23:22   linmay
// created 
// 
//    Rev 1.0   Feb 05 2003 13:08:58   linmay
// Initial Revision

  */
