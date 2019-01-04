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
//    Copyright 2002 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   :CanAddressBookDlg.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : Sept. 3, 2002
//
// ^CLASS    : CanAddressBookDlg
// ^SUBCLASS : BaseAddressBookDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include "stdafx.h"
#include "mfdstc.h"
#include "CanAddressBookDlg.h"
#include "BaseAddressBookDlg.h"

#include <ifastbp\addressprocessincludes.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dsttabctrl.h>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0071_vw.hpp>
#include <ifastdataimpl\dse_dstc0072_req.hpp>
#include <ifastdataimpl\dse_dstc0113_vw.hpp>
#include <ifastbp\nasuprocessincludes.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>

#ifdef _DEBUG
   #undef THIS_FILE
static char THIS_FILE[]=__FILE__;
   #define new DEBUG_NEW
#endif

namespace
{  
   const I_CHAR *CLASSNAME                = I_( "CanAddressBookDialog" );
   const I_CHAR *ADDRESS                  = I_("Address");
   const I_CHAR *SPACE_STRING             = I_( " " ); 
   const I_CHAR* const TAB_ADDR_INFO      = I_("Address Info");
   const I_CHAR* const TAB_RETMAIL_INFO   = I_("Return Mail Info");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ShareholderAddressHeadingVerifySet;
}

//-------------------------------------------------------------------
// Construction/Destruction
//--------------------------------------------------------------------

CanAddressBookDlg::CanAddressBookDlg( UINT nIDD,CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseAddressBookDlg( nIDD, pParent, pGIC, pGIParent, rCommand )

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//**************************************************************************************
void CanAddressBookDlg::addControls()
{
   BaseAddressBookDlg::addControls( );

   AddControl( CTRL_COMBO, IDC_CMB_SHR_COUNTRY, IFASTBP_PROC::ADDRESSES_LIST, 
               ifds::CountryCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ADDRESSES );
   AddControl( CTRL_COMBO, IDC_CMB_CONFIRM, IFASTBP_PROC::ADDRESSES_LIST, 
               ifds::Confirm, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ADDRESSES );
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA ) 
   {
      AddControl( CTRL_COMBO, IDC_CMB_RET_MAIL, IFASTBP_PROC::ADDRESSES_LIST, 
                  ifds::RetMailFlag, CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                  IDC_LV_ADDRESSES );
      AddControl( CTRL_DATE, IDC_DTP_RET_DATE, IFASTBP_PROC::ADDRESSES_LIST, 
                  ifds::RetMailDate, CTRLFLAG_DEFAULT, IDC_LV_ADDRESSES );

      AddControl( CTRL_STATIC, IDC_STATIC_RET_MAIL);
      AddControl( CTRL_STATIC, IDC_STATIC_RET_DATE);

	  // Entity Return Mail 
      AddControl( CTRL_COMBO, IDC_CMB_ENTITY_RET_MAIL, IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
                  ifds::RetMailFlag, CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                  IDC_LV_ADDRESSES );
      AddControl( CTRL_DATE, IDC_DTP_ENTITY_RET_DATE, IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
                  ifds::RetMailDate, CTRLFLAG_DEFAULT, IDC_LV_ADDRESSES );

      AddControl( CTRL_STATIC, IDC_STATIC_ENTITY_RET_MAIL);
      AddControl( CTRL_STATIC, IDC_STATIC_ENTITY_RET_DATE);

      AddControl( CTRL_STATIC,IDC_STATIC_CONFIRM);
      AddControl( CTRL_STATIC,IDC_STATIC_SHR_POST);

      DString dstrAddrFormat;
      DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      pdstcWorkSession->getOption( ifds::ShrAddressFormat,dstrAddrFormat, getParent()->getDataGroupId(), false );

      AddControl (CTRL_STATIC,IDC_STATIC_SHR_COUNTRY);


      m_pMailInfoTabCtrl->registerControl(IDC_CMB_RET_MAIL, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_DTP_RET_DATE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_RET_MAIL, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_RET_DATE, TAB_RETMAIL_INFO);

      m_pMailInfoTabCtrl->registerControl(IDC_CMB_ENTITY_RET_MAIL, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_DTP_ENTITY_RET_DATE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_ENTITY_RET_MAIL, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_ENTITY_RET_DATE, TAB_RETMAIL_INFO);

      m_pMailInfoTabCtrl->registerControl(IDC_EDT_POST_CODE, TAB_ADDR_INFO);

      m_pMailInfoTabCtrl->registerControl(IDC_CMB_CONFIRM, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_CONFIRM, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_SHR_POST, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_CMB_SHR_COUNTRY, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_SHR_COUNTRY, TAB_ADDR_INFO);

      ConnectControl(IDC_DTP_RET_DATE,true);
      ConnectControl(IDC_CMB_RET_MAIL,true);
      ConnectControl(IDC_CMB_UNCLAIM_REASON_CODE, true);
      ConnectControl(IDC_CMB_UNCLAIM_STAGE, true);
      ConnectControl(IDC_DTP_UNCLAIM_GOVT_STMT_DATE, true);
      ConnectControl(IDC_DTP_UNCLAIM_REMITTANCE_DATE, true);
      ConnectControl(IDC_EDT_UNCLAIM_COMMENT, true);
      ConnectControl(IDC_DTP_UNCLAIM_STAMP_DATE, true);
      ConnectControl(IDC_CMB_UNCLAIM_STAGE_ASSIGN, true);

      ConnectControl(IDC_CMB_ENTITY_RET_MAIL,true);
	  ConnectControl(IDC_DTP_ENTITY_RET_DATE,true);
	  ConnectControl(IDC_CMB_ENTITY_UNCLAIM_REASON_CODE,true);
	  ConnectControl(IDC_EDT_ENTITY_UNCLAIM_COMMENT,true);
   }
}
//**************************************************************************************
void CanAddressBookDlg::LoadShareHolderAddress()
{
   BaseAddressBookDlg::LoadShareHolderAddress( );
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA )
   {
      ConnectControl(IDC_CMB_RET_MAIL, true );
      ConnectControl(IDC_DTP_RET_DATE, true );
      ConnectControl(IDC_CMB_UNCLAIM_REASON_CODE, true);
      ConnectControl(IDC_CMB_UNCLAIM_STAGE, true);
      ConnectControl(IDC_DTP_UNCLAIM_GOVT_STMT_DATE, true);
      ConnectControl(IDC_DTP_UNCLAIM_REMITTANCE_DATE, true);
      ConnectControl(IDC_EDT_UNCLAIM_COMMENT, true);
      ConnectControl(IDC_DTP_UNCLAIM_STAMP_DATE, true);
      ConnectControl(IDC_CMB_UNCLAIM_STAGE_ASSIGN, true);

      ConnectControl(IDC_CMB_ENTITY_RET_MAIL,false);
	  ConnectControl(IDC_DTP_ENTITY_RET_DATE,false);
	  ConnectControl(IDC_CMB_ENTITY_UNCLAIM_REASON_CODE,false);
	  ConnectControl(IDC_EDT_ENTITY_UNCLAIM_COMMENT,false);
   }

   ConnectControl(IDC_CMB_SHR_COUNTRY, true );  
   ConnectControl(IDC_CMB_CONFIRM,true);   
   ConnectControl(IDC_CMB_CODE,true); 

   ConnectControl( IDC_DTP_ENTITY_ADDRESS_EFFECTIVE, false );
   ConnectControl( IDC_EDT_ENTITY_ADDRESS_CODE,      false );
   ConnectControl( IDC_ENTITY_ADDRESS,               false );
   ConnectControl( IDC_EDT_CITY,                     false );
   ConnectControl( IDC_EDT_ENTITY_ADDRESS_ID,        false );	   
   //////////////IF ACCOUNT IS NOT BLANK//////////////////////////////
   ConnectControl( IDC_CMB_ENTITY_HOLD_MAIL,         false );
   
   ConnectControl( IDC_EDT_ENTITY_POST,              false );
   ConnectControl( IDC_CMB_ENTITY_COUNTRY,           false );
   ConnectControl( IDC_CMB_PROVINCE,                 false );   
   ConnectControl( IDC_EDT_ENTITY_PROVINCE,          false );   	
   ConnectControl( IDC_EDT_ENTITY_ADDR_NAME,         false ); 
}

//---------------------------------------------------------------------------------------
void CanAddressBookDlg::LoadEntityAddress()
{
   BaseAddressBookDlg::LoadEntityAddress( );
   DString strMarket = DSTCommonFunctions::getMarket(); 	
   if( strMarket == MARKET_IDS::CANADA )
   {
      ConnectControl(IDC_CMB_RET_MAIL,false);
      ConnectControl(IDC_DTP_RET_DATE,false);

	  ConnectControl( IDC_CMB_ENTITY_RET_MAIL,            true );
      ConnectControl( IDC_DTP_ENTITY_RET_DATE,            true );
      ConnectControl( IDC_CMB_ENTITY_UNCLAIM_REASON_CODE, true );
      ConnectControl( IDC_EDT_ENTITY_UNCLAIM_COMMENT,     true ); 
   }

   ConnectControl(IDC_CMB_SHR_COUNTRY, false );  
   ConnectControl(IDC_CMB_CONFIRM,     false);
   ConnectControl(IDC_CMB_CODE,        false);
    
   ConnectControl(IDC_DTP_ENTITY_ADDRESS_EFFECTIVE, true );
   ConnectControl(IDC_EDT_ENTITY_ADDRESS_CODE,      true );
   ConnectControl(IDC_ENTITY_ADDRESS,               true );
   ConnectControl(IDC_EDT_CITY,                     true );
   ConnectControl(IDC_EDT_ENTITY_ADDRESS_ID,        true );	   
   //////////////IF ACCOUNT IS NOT BLANK//////////////////////////////
   ConnectControl(IDC_CMB_ENTITY_HOLD_MAIL,         true );

   ConnectControl(IDC_EDT_ENTITY_POST,              true);
   ConnectControl(IDC_CMB_ENTITY_COUNTRY,           true);
   ConnectControl(IDC_CMB_PROVINCE,                 true);   
   ConnectControl(IDC_EDT_ENTITY_ADDR_NAME,         true);
}

//-----------------------------------------------------------------------------------
void CanAddressBookDlg::ShowShareHolder(bool bFreshList) 
{
   BaseAddressBookDlg::ShowShareHolder(bFreshList);
   GetDlgItem (IDC_EDT_POST_CODE)->ShowWindow (SW_SHOW);
   DString dstrAddrFormat;
   DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pdstcWorkSession->getOption( ifds::ShrAddressFormat,dstrAddrFormat, getParent()->getDataGroupId(), false );

   GetDlgItem (IDC_STATIC_CONFIRM)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_CONFIRM)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHR_POST)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_ENTITY_POST)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_PROVINCE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_COUNTRY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_ENTITY_COUNTRY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_SHR_COUNTRY)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHR_COUNTRY)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_EDT_CITY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_PROVINCE)->ShowWindow (SW_HIDE);

   /*DString strMarket = DSTCommonFunctions::getMarket();
	if( strMarket == MARKET_IDS::CANADA ) 
	{
	  GetDlgItem (IDC_STATIC_RET_MAIL)->ShowWindow (SW_SHOW);
	  GetDlgItem (IDC_CMB_RET_MAIL)->ShowWindow (SW_SHOW);
	  GetDlgItem (IDC_STATIC_RET_DATE)->ShowWindow (SW_SHOW);
	  GetDlgItem (IDC_DTP_RET_DATE)->ShowWindow (SW_SHOW);       
	} 
	
	else
	{
		GetDlgItem (IDC_STATIC_RET_MAIL)->ShowWindow (SW_HIDE);
	    GetDlgItem (IDC_CMB_RET_MAIL)->ShowWindow (SW_HIDE);
	    GetDlgItem (IDC_STATIC_RET_DATE)->ShowWindow (SW_HIDE);
	    GetDlgItem (IDC_DTP_RET_DATE)->ShowWindow (SW_HIDE);  
	}
	*/
}

//---------------------------------------------------------
void CanAddressBookDlg::ShowEntity() 
{
   BaseAddressBookDlg::ShowEntity();
   GetDlgItem (IDC_EDT_POST_CODE)->ShowWindow (SW_HIDE);

   DString dstrAddrFormat;
   DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pdstcWorkSession->getOption( ifds::ShrAddressFormat,dstrAddrFormat, getParent()->getDataGroupId(), false );

   GetDlgItem (IDC_STATIC_CONFIRM)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_CONFIRM)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_SHR_POST)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_POST)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_ENTITY_PROVINCE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_ENTITY_COUNTRY)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_ENTITY_COUNTRY)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHR_COUNTRY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_SHR_COUNTRY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_EDT_CITY)->ShowWindow (SW_SHOW);
//   GetDlgItem (IDC_CMB_PROVINCE)->ShowWindow (SW_SHOW);    
   doSwitchProvinceControl();

   GetDlgItem(IDC_CMB_CODE)->ShowWindow(SW_SHOW);


}
//*************************************************************
bool CanAddressBookDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
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
         strOut += str+SPACE_STRING;
         strOut += strPostalCode;
         bRet = true;
      }
   }

   return(bRet);
}

//***********************************************************************************************
void CanAddressBookDlg::SetAddressControlsReadOnly(bool bReadOnly)
{
   BaseAddressBookDlg::SetAddressControlsReadOnly(bReadOnly);
   GetDlgItem( IDC_CMB_CONFIRM )->EnableWindow(!bReadOnly);  
   GetDlgItem( IDC_CMB_SHR_COUNTRY )->EnableWindow(!bReadOnly);    
}

//**********************************************************************************************
bool CanAddressBookDlg::doDisableControl(UINT nID, bool bIsNew)
{
   if( nID == IDC_CMB_CONFIRM || nID == IDC_CMB_SHR_COUNTRY )
   {
      return(disableControlForAddress01());	  
   }
   else return(BaseAddressBookDlg::doDisableControl( nID,bIsNew ));
}

//********************************************************************************
void CanAddressBookDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   BaseAddressBookDlg::ControlUpdated( controlID, strValue );
   switch (controlID)
   {
      case IDC_SHAREHOLDER_ADDRESS:
      case IDC_EDT_CITY:
      case IDC_CMB_SHR_PROVINCE:
      case IDC_EDT_SHR_CITY:
      case IDC_CMB_SHR_COUNTRY:
      case IDC_EDT_REG_ADDR_CODE:
      case IDC_EDT_POST_CODE:
      {
         DString strMarket = DSTCommonFunctions::getMarket();
         if( strMarket == MARKET_IDS::CANADA ) {
            LoadControl( IDC_CMB_RET_MAIL );
         }
         break;
      }
      case IDC_CMB_RET_MAIL:
      {
         if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA ) 
         {
            LoadControl( IDC_DTP_RET_DATE );
            LoadControl( IDC_CMB_UNCLAIM_REASON_CODE );

            LoadControl( IDC_CMB_UNCLAIM_STAGE );
            LoadControl( IDC_DTP_UNCLAIM_GOVT_STMT_DATE );
            LoadControl( IDC_DTP_UNCLAIM_REMITTANCE_DATE );
            LoadControl( IDC_EDT_UNCLAIM_COMMENT );
         }
      }
         break;
      case IDC_CMB_ENTITY_RET_MAIL:
      {
         if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA ) 
         {
			OnSelRetMail();
            LoadControl( IDC_DTP_ENTITY_RET_DATE );
            LoadControl( IDC_CMB_ENTITY_UNCLAIM_REASON_CODE );
            LoadControl( IDC_EDT_ENTITY_UNCLAIM_COMMENT );
         }		  
	  }
		break;
      case IDC_CMB_UNCLAIM_STAGE:
      {
         LoadControl( IDC_DTP_UNCLAIM_STAMP_DATE);
         LoadControl( IDC_CMB_UNCLAIM_STAGE_ASSIGN);
      }
         break;
   }
}
/*
void CanAddressBookDlg::HideReturnMail()
{
   BaseAddressBookDlg::HideReturnMail();
 
   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA ) 
   {
      
      BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STATIC_RET_MAIL,1,false);
		BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_CMB_RET_MAIL,1,false);
		BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STATIC_RET_DATE,1,false);
		BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_DTP_RET_DATE,1,false);
      
   }
}*/

/*
void CanAddressBookDlg::ShowReturnMail()
{
   BaseAddressBookDlg::ShowReturnMail();
   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA ) 
   {

		/*GetDlgItem (IDC_STATIC_RET_MAIL)->ShowWindow (SW_SHOW);
		GetDlgItem (IDC_CMB_RET_MAIL)->ShowWindow (SW_SHOW);
		GetDlgItem (IDC_STATIC_RET_DATE)->ShowWindow (SW_SHOW);
		GetDlgItem (IDC_DTP_RET_DATE)->ShowWindow (SW_SHOW);
		BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STATIC_RET_MAIL,1,true);
		BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_CMB_RET_MAIL,1,true);
		BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STATIC_RET_DATE,1,true);
		BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_DTP_RET_DATE,1,true);
      
		OnSelRetMail( );
   }
}
*/

//******************************************************************************
void CanAddressBookDlg::OnSelRetMail( )
{
   if( DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA ) 
      return;
   DString dstrRetMailFlag;

   //int showFlag = (dstrRetMailFlag==I_("Y"))?SW_SHOW:SW_HIDE;
   bool bShrShow = false;
   bool bEntityShow = false;
   bool bShowEntityAddress = false;

   if( IsShareholder() )
   {
      getParent()->getField(this, IFASTBP_PROC::ADDRESSES_LIST, ifds::RetMailFlag,dstrRetMailFlag,false);
      bShrShow = true;
	  bEntityShow = false;
	  bShowEntityAddress = false;
   }	
   else 
   {
      getParent()->getField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::RetMailFlag,dstrRetMailFlag,false);
      bShrShow = false;
	  bEntityShow = true; 
	  bShowEntityAddress = true;
   }

   bool isShow = (dstrRetMailFlag==I_("Y"));

   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_REASON_CODE,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_CMB_UNCLAIM_REASON_CODE,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_STAGE,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_CMB_UNCLAIM_STAGE,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_GOVT_STMT_DATE,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_DTP_UNCLAIM_GOVT_STMT_DATE,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_REMITTANCE_DATE,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_DTP_UNCLAIM_REMITTANCE_DATE,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_COMMENT,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_EDT_UNCLAIM_COMMENT,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_STAMP_DATE,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_DTP_UNCLAIM_STAMP_DATE,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_STAGE_ASSIGN,1,isShow && bShrShow);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_CMB_UNCLAIM_STAGE_ASSIGN,1,isShow && bShrShow);

   // Entity Return mail 
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STATIC_ENTITY_RET_MAIL,1, bEntityShow && (m_strCurrentMailingPageName == TAB_RETMAIL_INFO));
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_CMB_ENTITY_RET_MAIL,1, bEntityShow && (m_strCurrentMailingPageName == TAB_RETMAIL_INFO));
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STATIC_ENTITY_RET_DATE,1, bEntityShow && (m_strCurrentMailingPageName == TAB_RETMAIL_INFO));
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_DTP_ENTITY_RET_DATE,1, bEntityShow && (m_strCurrentMailingPageName == TAB_RETMAIL_INFO));

   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_ENTITY_UNCLAIM_REASON_CODE,1,isShow && bEntityShow && (m_strCurrentMailingPageName == TAB_RETMAIL_INFO));
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_CMB_ENTITY_UNCLAIM_REASON_CODE,1,isShow && bEntityShow && (m_strCurrentMailingPageName == TAB_RETMAIL_INFO));
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_ENTITY_UNCLAIM_COMMENT,1,isShow && bEntityShow && (m_strCurrentMailingPageName == TAB_RETMAIL_INFO));
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_EDT_ENTITY_UNCLAIM_COMMENT,1,isShow && bEntityShow && (m_strCurrentMailingPageName == TAB_RETMAIL_INFO));
	

   if (m_strCurrentMailingPageName == TAB_RETMAIL_INFO)
   {	   
	   //    Entity Address: If return mail info is displayed, hide address controls
	   GetDlgItem (IDC_TXT_ENTITY_ADDRESS_EFFECTIVE)->ShowWindow (false);
	   GetDlgItem (IDC_DTP_ENTITY_ADDRESS_EFFECTIVE)->ShowWindow (false);
	   GetDlgItem (IDC_EDT_ENTITY_ADDRESS_CODE)->ShowWindow (false);
	   GetDlgItem (IDC_STATIC_ENTITY_ADDRESS)->ShowWindow (false);
	   GetDlgItem (IDC_ENTITY_ADDRESS)->ShowWindow (false);

	   GetDlgItem (IDC_STATIC_CITY)->ShowWindow (false);
	   GetDlgItem (IDC_EDT_CITY)->ShowWindow (false);
	   GetDlgItem (IDC_STATIC_ADDRESS_ID)->ShowWindow (false);
	   GetDlgItem (IDC_EDT_ENTITY_ADDRESS_ID)->ShowWindow (false);
	   GetDlgItem (IDC_STATIC_ENTITY_POST)->ShowWindow (false);

	   GetDlgItem (IDC_EDT_ENTITY_POST)->ShowWindow (false);
	   GetDlgItem (IDC_STATIC_ENTITY_COUNTRY)->ShowWindow (false);
	   GetDlgItem (IDC_CMB_ENTITY_COUNTRY)->ShowWindow (false);
	   GetDlgItem (IDC_STATIC_ENTITY_PROVINCE)->ShowWindow (false);
	   GetDlgItem (IDC_CMB_PROVINCE)->ShowWindow (false);           

	   GetDlgItem (IDC_EDT_ENTITY_PROVINCE)->ShowWindow (false);     
	   GetDlgItem (IDC_TXT_ENTITY_ADDR_NAME)->ShowWindow (false);
	   GetDlgItem (IDC_EDT_ENTITY_ADDR_NAME)->ShowWindow (false);

       GetDlgItem (IDC_CMB_ENTITY_HOLD_MAIL)->ShowWindow (false);
       GetDlgItem (IDC_STATIC_ENTITY_HOLD_MAIL)->ShowWindow (false);
   } 

   OnSelAddressCode(); //fills the address mailing list grid
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/CanAddressBookDlg.cpp-arc  $
// 
//    Rev 1.20   Jan 22 2010 09:07:46   dchatcha
// IN# 1982767 - REl 97 - Static Data - Display of Verified status.
// 
//    Rev 1.19   Dec 03 2009 03:50:00   dchatcha
// PET0166583 FN02 FN03 - Static Verification Phase 2.
// 
//    Rev 1.18   Aug 18 2009 11:19:16   jankovii
// IN 1794778 - Skip Vlaidation box misplaced on DK screeen
// 
//    Rev 1.17   Aug 07 2009 09:27:06   jankovii
// IN 1789793 - R95 Stability-Desktop - Cannot create account.
// 
//    Rev 1.16   20 Jul 2009 16:04:32   walkerro
// PET 156681 FN03 - fixed bug regarding Lookup button not registered correctly.
// 
//    Rev 1.15   17 Jul 2009 14:08:30   walkerro
// PET156681 FN03 - Postal Code Lookup on address screen
// 
//    Rev 1.14   02 Mar 2009 13:53:04   popescu
// Incident 1569397 - fixed display issue on the mailing planel, reduce flickering.
// 
//    Rev 1.13   Nov 06 2008 02:41:26   daechach
// PET5517 FN71 Unclaimed Property Phase 2
// 
//    Rev 1.12   Sep 29 2008 07:57:54   wongsakw
// PET5517 FN71 Unclaimed Property - Return Mail
// 
//    Rev 1.11   Sep 22 2008 08:47:06   wongsakw
// PET5517 FN71 Unclaimed Property
// 
//    Rev 1.10   Mar 16 2005 10:05:00   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.9   Mar 08 2005 10:19:40   porteanm
// PET 1171 FN01 - EUSD Entity Address Update - work in progress.
// 
//    Rev 1.8   Mar 03 2005 12:51:50   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.7   Feb 25 2005 13:17:08   porteanm
// PET 1171 FN01 - EUSD Entity Address Search.
// 
//    Rev 1.6   Sep 27 2003 17:21:46   HSUCHIN
// PTS 10022295 - bug fix with Lux market resources not having CIBC enhancement controls.
// 
//    Rev 1.5   Jul 30 2003 16:59:44   FENGYONG
// Add control update
// 
//    Rev 1.4   Jul 30 2003 11:27:20   FENGYONG
// CIBC enhancement PET809_FN46
// 
//    Rev 1.3   Mar 21 2003 18:33:56   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Feb 06 2003 10:21:28   linmay
// modified constructor
// 
//    Rev 1.1   Oct 09 2002 23:55:34   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.0   Sep 13 2002 15:51:12   YINGBAOL
// Initial revision.

 


  */

