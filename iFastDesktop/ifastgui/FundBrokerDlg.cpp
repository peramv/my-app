//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial  Ltd.
//
//******************************************************************************
//    
// ^FILE   : FundBrokerDlg.h
// ^AUTHOR : 
// ^DATE   : 07/26/04
//
// ^CLASS    : FundBrokerDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"

#include <uibase\DSTEdit.h>  
#include <uibase\dsttabctrl.h> 
#include "FundBrokerDlg.h"
#include <ifastbp\FundBrokerProcessInclude.h>
#include <ifastbp\FundBrokerProcess.hpp>
#include <uibase\DSTListCtrl.h>
#include <uibase\ifdslistctrl.h>
#include <uibase\DSTComboBox.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastbp\featuressearchprocessincludes.h>
#include <ifastbp\fillsearchcriteriaprocessincludes.h>
#include <ifastbp\searchprocess.hpp>
#include <ifastbp\searchprocessincludes.h>
#include <ifastdataimpl\dse_dstc0326_vw.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FUND_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_BROKER_SETTLEMENT_INSTR;
#define	MAX_LIMIT_50	50
#define	MAX_LIMIT_35	35
#define MAX_ZIP_CODE    10



#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FundBrokerDlg > dlgCreator( CMD_GUI_FUND_BROKER );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME							= I_( "FundBrokerDlg" );
   const I_CHAR * const YES									= I_( "Y" );
   const I_CHAR * const NO										= I_( "N" );

   const I_CHAR* const  LV_FUNDBROKER						= I_( "Fund Broker List" );
   const I_CHAR* const  LV_FEE_PARAM						= I_( "Fee Param List" );   
   const I_CHAR* const  LV_ENTITY_IDS_LIST				= I_( "Entity IDS List" );
   const I_CHAR* const  PERCENT								= I_( "Percent" );
   const I_CHAR * const FLAT									= I_( "0" );
   const I_CHAR * const PERCENTAGE							= I_( "1" );
   const I_CHAR * const FEE_CODE_MANAGEMENT_FEE			= I_("18");
   const I_CHAR * const FEE_CPDE_MANAGEMENT_REBATE		= I_("95");
   const I_CHAR * const FEE_CODE_MANAGEMENT_DISCOUNT	= I_("180");


   const I_CHAR * const NUMBERS = I_("0123456789.");
	const I_CHAR * const	NOT_APPLY  =  I_("NA");
   const I_CHAR * const CHARACTERS = I_("0123456789 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@.");
   const I_CHAR * const PHONENUMBERS = I_("0123456789-\\(\\)");
   const I_CHAR * const INVESTRO = I_( "02" );
   const I_CHAR * const FAX = I_( "01" );   
   const CString RemoveList[] =
   {_T("Driver's  License"),_T("Passport"),_T("Birth Certificate"),_T("Tax ID Number"),
		_T("CIF"),_T("Member License #"),_T("PCG Business Number"),
		_T("Record of Landing or Permanent Residence"),_T("Provincial Health Card"),
		_T("Quebec Enterprise Number (NEQ)"),_T("\0")};

}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const FUND_BROKER_MAINTENANCE;
}
namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId FeeParamListHeaderSet;
   extern CLASS_IMPORT const BFTextFieldId EntityIDSHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId FundBrokerListSet;   
   extern CLASS_IMPORT const BFTextFieldId ShareholderAddressF02;
   
   extern CLASS_IMPORT const BFTextFieldId ChargeOption;
   extern CLASS_IMPORT const BFTextFieldId FeeModelOption;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFTextFieldId ParamFeeType;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId CommGroup;
   extern CLASS_IMPORT const BFTextFieldId IdValue;
   extern CLASS_IMPORT const BFTextFieldId IdType;
   extern CLASS_IMPORT const BFDateFieldId IdDate;
   extern CLASS_IMPORT const BFTextFieldId BusinessPhone;
   extern CLASS_IMPORT const BFTextFieldId BusinessExt;
   extern CLASS_IMPORT const BFTextFieldId BusinessFax;
   extern CLASS_IMPORT const BFTextFieldId Email;
   extern CLASS_IMPORT const BFTextFieldId Contact; 
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   
   extern CLASS_IMPORT const BFTextFieldId LanguageCode;
   extern CLASS_IMPORT const BFTextFieldId LastName;
   extern CLASS_IMPORT const BFTextFieldId SetFundToInvestr;
   extern CLASS_IMPORT const BFTextFieldId Changed;
   extern CLASS_IMPORT const BFNumericFieldId FundBrokerOffsetTime;
   extern CLASS_IMPORT const BFTextFieldId FundBrokerRegAddr;
   extern CLASS_IMPORT const BFTextFieldId CountryOfIssue;
}
namespace ENTITY_IDS_VALUE
{
    const I_CHAR * const NATIONAL_ID			   = I_("05");
	const I_CHAR * const DRIVERS_LICENSE		   = I_("01");
	const I_CHAR * const BIRTH_CERTIFICATE		   = I_("03");
	const I_CHAR * const PASSPORT				   = I_("02");
	const I_CHAR * const FAST					   = I_("30");
	const I_CHAR * const iFAST_SICAV			   = I_("31");
	const I_CHAR * const iFAST_OEIC				   = I_("32");
}

class LVFundBrokerData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVFundBrokerData() {}
   DString FundBrokerCode_;
   DString Name_;
   DString EffectiveDate_;
   DString PUEVCapable_;
   DString RoutingType_;
   DString PriceType_;
   DString StopDate_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundBrokerCode, FundBrokerCode_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Name, Name_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EffectiveDate, EffectiveDate_ );      
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::StopDate, StopDate_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::PUEVCapable, PUEVCapable_ );      
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::RoutingType, RoutingType_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::PriceType, PriceType_ );      
   }
};

class LVFundBrokerAdapter : public IFDSListCtrlAdapter< LVFundBrokerData >
{
public:
   // required overrides
   virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2 )
   {
      int result = 0;

      const BFFieldId* pFieldId = pCtrl->getColumnField( iSortColumn - 1 );
      if( 1 == iSortColumn ) {
         // Condition indicator column.  Sort on image index
         result = ( IFDSListBase::getColumnLVItem( lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem( lParam2, iSortColumn - 1)->iImage );
      } else if( NULL == pFieldId ) {
         return( 0 );
      } else if( *pFieldId == ifds::FundBrokerCode ) {
         result = i_strcmp( pData1->FundBrokerCode_.c_str(), pData2->FundBrokerCode_.c_str() );
      } else if( *pFieldId == ifds::Name ) {
         result = i_strcmp( pData1->Name_.c_str(), pData2->Name_.c_str() );
      } else if( *pFieldId == ifds::EffectiveDate ) {
         result = i_strcmp( pData1->EffectiveDate_.c_str(), pData2->EffectiveDate_.c_str() );
      } else if( *pFieldId == ifds::StopDate ) {
         result = i_strcmp( pData1->StopDate_.c_str(), pData2->StopDate_.c_str() );
      } else if( *pFieldId == ifds::PUEVCapable ) {
         result = i_strcmp( pData1->PUEVCapable_.c_str(), pData2->PUEVCapable_.c_str() );
      } else if( *pFieldId == ifds::RoutingType ) {
         result = i_strcmp( pData1->RoutingType_.c_str(), pData2->RoutingType_.c_str() );
      } else if( *pFieldId == ifds::PriceType ) {
         result = i_strcmp( pData1->PriceType_.c_str(), pData2->PriceType_.c_str() );
      }

      return( bAscending ? result : -result );
   }

   virtual LRESULT onGetDispInfo( IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo )
   {
      if( pDispInfo->item.mask & LVIF_TEXT )
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField( pDispInfo->item.iSubItem );

         if( NULL == pFieldId ) {
            pDispInfo->item.pszText = I_( "" );
         } else if( *pFieldId == ifds::FundBrokerCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundBrokerCode_.c_str();
         } else if( *pFieldId == ifds::Name ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->Name_.c_str();
         } else if( *pFieldId == ifds::EffectiveDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->EffectiveDate_.c_str();
         } else if( *pFieldId == ifds::StopDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->StopDate_.c_str();
         } else if( *pFieldId == ifds::PUEVCapable ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->PUEVCapable_.c_str();
         } else if( *pFieldId == ifds::RoutingType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->RoutingType_.c_str();
         } else if( *pFieldId == ifds::PriceType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->PriceType_.c_str();
         }
         return( 1 );
      }
      return( 0 );
   }
};

//******************************************************************************

FundBrokerDlg::FundBrokerDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FundBrokerDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, F4Clicked(false)
, m_nameupdateflag(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(FundBrokerDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
FundBrokerDlg::~FundBrokerDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void FundBrokerDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(FundBrokerDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FundBrokerDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FundBrokerDlg)
ON_BN_CLICKED(IDC_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_MORE_FEE, OnBtnFeeParamMore)
ON_BN_CLICKED(IDC_ADD_FEE, OnBtnAddFeeParam)
ON_BN_CLICKED(IDC_BTN_DEL_FEE, OnBtnDelFeeParam)
ON_BN_CLICKED(IDC__ADMIN, OnBtnAdmDates)
ON_MESSAGE(UM_OPENENTITYSEARCHDLG, OpenEntitySearchDlg)
ON_BN_CLICKED(IDC_ADD_FUND_BROKER, OnBtnAddFundBroker)
ON_BN_CLICKED(IDC_BTN_DEL_FUNDBROKER, OnBtnDelFundBroker)
ON_BN_CLICKED(IDC_BTN_MORE_FUNDBROKER, OnBtnMoreFundBroker)
ON_BN_CLICKED(IDC_ADD_ID, OnBtnAddID)
ON_BN_CLICKED(IDC_BTN_DEL_ID, OnBtnDelID)
ON_BN_CLICKED(IDC_RD_CONTACT1, OnBtnContact1)
ON_BN_CLICKED(IDC_RD_CONTACT2, OnBtnContact2)
ON_BN_CLICKED(IDC_SETTLELOC, OnBtnSettleLoc)
ON_EN_KILLFOCUS(IDC_EDT_FB_NAME, OnKillfocusLastName)
ON_EN_KILLFOCUS(IDC_EDT_CT_LAST_NAME, OnKillfocusCTLastName)
//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FundBrokerDlg message handlers


//******************************************************************************
void FundBrokerDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );

   SetUserAccesFunctionCode(UAF::FUND_BROKER_MAINTENANCE);
   addBtnAddForPermissionCheck(IDC_ADD_FUND_BROKER, IDC_LIST_FUND_BROKER);
   addBtnDeleteForPermissionCheck(IDC_BTN_DEL_FUNDBROKER, IDC_LIST_FUND_BROKER);
	addBtnAddForPermissionCheck(IDC_ADD_FEE, IDC_LIST_FEE_PARAM);
	addBtnAddForPermissionCheck(IDC_ADD_ID, IDC_LV_ENTITY_IDS); 

    addControls();

	doRefresh(this, NULL);
    GetDlgItem(IDC_BTN_MORE_FUNDBROKER)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::FUND_BROKER_LIST ) );
    GetDlgItem(IDC_BTN_MORE_FEE)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::FEE_PARAM_LIST ) );
    ShowTabCtrl	  (IDC_TAB_FUNDBRKRID,true);
    LoadTabControl (IDC_TAB_FUNDBRKRID);
	DString dstrIDtype = NULL_STRING;
	getParent()->getField( this, ifds::IdType, dstrIDtype,false );
	if(dstrIDtype == ENTITY_IDS_VALUE::BIRTH_CERTIFICATE || dstrIDtype == ENTITY_IDS_VALUE::DRIVERS_LICENSE || 
		dstrIDtype == ENTITY_IDS_VALUE::PASSPORT ||dstrIDtype == ENTITY_IDS_VALUE::NATIONAL_ID )
	{
		GetDlgItem(IDC_CMB_COUNTRY_OF_ISSUE)->ShowWindow(SW_SHOW);	 
		GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_CMB_COUNTRY_OF_ISSUE)->ShowWindow(SW_HIDE);	 
		GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_HIDE);
	}

}

//******************************************************************************
SEVERITY FundBrokerDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;
   
   sevRtn = NO_CONDITION;
   return(sevRtn);
}
//******************************************************************************
void FundBrokerDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );

   IFDSListCtrl* pFundBrokerListCtrl = 
      new IFDSAdaptedListCtrl< LVFundBrokerAdapter >(this, CLASSNAME, 
      IDC_LIST_FUND_BROKER, 0, 0, true, true);

   AddIFDSListControl(pFundBrokerListCtrl, LV_FUNDBROKER, IFASTBP_PROC::FUND_BROKER_LIST, ifds::FundBrokerListSet);

//   AddListControl( CLASSNAME,IDC_LIST_FUND_BROKER,     LV_FUNDBROKER,     ifds::FundBrokerListSet,           IFASTBP_PROC::FUND_BROKER_LIST);
   AddListControl( CLASSNAME,IDC_LIST_FEE_PARAM,     LV_FEE_PARAM,     ifds::FeeParamListHeaderSet,           IFASTBP_PROC::FEE_PARAM_LIST, 
                   IDC_LIST_FUND_BROKER, true);//, LISTFLAG_NOT_AUTO_ADD );
   AddListControl( CLASSNAME,IDC_LV_ENTITY_IDS,     LV_ENTITY_IDS_LIST,     ifds::EntityIDSHeadingSet,           IFASTBP_PROC::ENTITY_IDS_LIST, 
                   IDC_LIST_FUND_BROKER, true);//, LISTFLAG_NOT_AUTO_ADD );   
   
   
   AddControl( CTRL_EDIT,    IDC_EDT_FUNDBROKER_CODE,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::FundBrokerCode,0,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_EDIT,    IDC_EDT_FB_NAME,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::Name,0,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_EDIT,    IDC_EDT_OFFSETTIME,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::FundBrokerOffsetTime,0,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_DATE,   IDC_DTP_EFFECTIVE,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::EffectiveDate,0,IDC_LIST_FUND_BROKER);   
   AddControl( CTRL_DATE,   IDC_DTP_STOPDATE,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::StopDate,0,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_COMBO,  IDC_CMB_PVEU_CAPABLE,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::PUEVCapable,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_COMBO,  IDC_CMB_ROUTING_TYPE,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::RoutingType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_COMBO,  IDC_CMB_PRICE_TYPE,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::PriceType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_EDIT,    IDC_EDT_FB_LAST_NAME2,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::Remarks1,0,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_EDIT, IDC_FUNDBROKER_ADDRESS, IFASTBP_PROC::FUND_BROKER_LIST, 
		         ifds::ShareholderAddressF02,CTRLFLAG_FIELDS_FROM_SUB_LIST, IDC_LIST_FUND_BROKER );
   AddControl( CTRL_COMBO,    IDC_CMB_COUNTRY,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::Country,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_EDIT,    IDC_EDT_POSTCODE,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::PostalCode,0,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_COMBO,    IDC_CMB_CLEARING_METHOD,   IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::FrClearingMethod,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FUND_BROKER);

   
   AddControl( CTRL_COMBO,  IDC_CMB_ID_TYPE,   IFASTBP_PROC::ENTITY_IDS_LIST, 
               ifds::IdType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LV_ENTITY_IDS);   
   AddControl( CTRL_EDIT, IDC_EDT_ID_VALUE, IFASTBP_PROC::ENTITY_IDS_LIST, 
		ifds::IdValue,0, IDC_LV_ENTITY_IDS );   
   AddControl( CTRL_DATE,   IDC_DTP_ID_DATE,   IFASTBP_PROC::ENTITY_IDS_LIST, 
               ifds::IdDate,0,IDC_LV_ENTITY_IDS);
   AddControl( CTRL_COMBO,    IDC_CMB_COUNTRY_OF_ISSUE,  IFASTBP_PROC::ENTITY_IDS_LIST, 
			   ifds::CountryOfIssue,CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ENTITY_IDS );
   
   AddControl( CTRL_COMBO,  IDC_CMB_FEE_CODE,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::FeeCode,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FEE_PARAM);
   AddControl( CTRL_COMBO,  IDC_CMB_FEE_TYPE1,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::ParamFeeType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FEE_PARAM);
   AddControl( CTRL_EDIT, IDC_EDT_VALUE1, IFASTBP_PROC::FEE_PARAM_LIST, 
		         ifds::Rate,0, IDC_LIST_FEE_PARAM );
   AddControl( CTRL_DATE,   IDC_DTP_FEE_EFFECTIVE,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::EffectiveDate,0,IDC_LIST_FEE_PARAM);
   AddControl( CTRL_DATE,   IDC_DTP_FEE_STOPDATE,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::StopDate,0,IDC_LIST_FEE_PARAM);

   AddControl( CTRL_EDIT, IDC_EDT_CT_FIRST_NAME, BF::NullContainerId, 
		ifds::FirstName,0, IDC_LIST_FUND_BROKER );   
   AddControl( CTRL_EDIT, IDC_EDT_CT_LAST_NAME, BF::NullContainerId, 
		ifds::LastName,0, IDC_LIST_FUND_BROKER );   
   AddControl( CTRL_COMBO,  IDC_CMB_LANGUAGE,   BF::NullContainerId, 
               ifds::LanguageCode,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FUND_BROKER);    
   AddControl( CTRL_EDIT, IDC_EDT_CT_PHONE, BF::NullContainerId, 
		ifds::BusinessPhone,0, IDC_LIST_FUND_BROKER );
   AddControl( CTRL_EDIT, IDC_EDT_CT_FAX, BF::NullContainerId, 
		ifds::BusinessFax,0, IDC_LIST_FUND_BROKER );
   AddControl( CTRL_EDIT, IDC_EDT_CT_EMAIL, BF::NullContainerId, 
		ifds::Email,0, IDC_LIST_FUND_BROKER );
   AddControl( CTRL_EDIT, IDC_EDT_CT_EXT, BF::NullContainerId, 
		ifds::BusinessExt,0, IDC_LIST_FUND_BROKER ); 
   
   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RD_CONTACT1 ) );
   pRadioButton->SetCheck( 1 );

   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_POSTCODE ) )->SetAllowedChars( CHARACTERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_CT_PHONE ) )->SetAllowedChars( PHONENUMBERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_CT_FAX ) )->SetAllowedChars( PHONENUMBERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_CT_EMAIL ) )->SetAllowedChars( CHARACTERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_CT_EXT ) )->SetAllowedChars( PHONENUMBERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_VALUE1 ) )->SetAllowedChars( NUMBERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_OFFSETTIME ))->SetMaxCharNum( 5 );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_OFFSETTIME ))->setInputAllowedDecimal();
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_OFFSETTIME ))->SetAllowedChars(I_("-0123456789"));
   


   AddControl (CTRL_STATIC,		IDC_STATIC_TYPE,	CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,		IDC_STATIC_DATE,	CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,		IDC_STATIC_VALUE,	CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,     IDC_STATIC_CNTRY_OF_ISSUE,  CTRLFLAG_GUI_FIELD);
   
   AddControl (CTRL_STATIC,		IDC_STATIC_BROKERGROUP, CTRLFLAG_GUI_FIELD);
   
    
   AddControl( CTRL_EDIT, IDC_EDT_DEALER_CODE,IFASTBP_PROC::FUND_BROKER_LIST, 
		       ifds::FbDealer,0, IDC_LIST_FUND_BROKER );
   AddControl( CTRL_EDIT,    IDC_EDT_BRANCH_CODE, IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::FbBranch,0,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_EDIT, IDC_EDT_AGENT_CODE,IFASTBP_PROC::FUND_BROKER_LIST, 
		        ifds::FbAgent,0, IDC_LIST_FUND_BROKER );
   AddControl (CTRL_STATIC, IDC_STATIC_BRANCH_CODE, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STATIC_DEALER_CODE, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STATIC_AGENT_CODE, CTRLFLAG_GUI_FIELD);   
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_DEALER_CODE ) )->SetMaxCharNum(MAX_LIMIT_50);
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_BRANCH_CODE ) )->SetMaxCharNum(MAX_LIMIT_35);
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_AGENT_CODE) )->SetMaxCharNum(MAX_LIMIT_50); 
   AddControl( CTRL_EDIT, IDC_EDT_ACCOUNT_SRV, IFASTBP_PROC::FUND_BROKER_LIST, 
		       ifds::AcctServicer,0, IDC_LIST_FUND_BROKER );
   AddControl( CTRL_EDIT,    IDC_EDT_REG_NAME, IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::RegName,0,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_EDIT, IDC_EDT_ACCOUNT_DESIGNATION, IFASTBP_PROC::FUND_BROKER_LIST, 
		       ifds::FbAcctDesig,0, IDC_LIST_FUND_BROKER );  
   AddControl( CTRL_EDIT, IDC_EDT_REG_ACCOUNT,IFASTBP_PROC::FUND_BROKER_LIST, 
		       ifds::RegAcct,0, IDC_LIST_FUND_BROKER );
   AddControl( CTRL_EDIT,    IDC_EDT_PORTFOLIO_CODE, IFASTBP_PROC::FUND_BROKER_LIST, 
              ifds::FbPortfolio,0,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_COMBO,    IDC_CMB_SETTLEMENT_TYPE,IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::FbSettleType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FUND_BROKER);    
   
   AddControl (CTRL_STATIC, IDC_STATIC_ACCOUNT_SRV, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STATIC_REG_NAME, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STATIC_ACCOUNT_DESIGNATION, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STATIC_REG_ACCOUNT, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STATIC_PORTFOLIO_CODE, CTRLFLAG_GUI_FIELD);              
   AddControl (CTRL_STATIC, IDC_STATIC_SETTLEMENT_TYPE, CTRLFLAG_GUI_FIELD);

   
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_ACCOUNT_SRV ) )->SetMaxCharNum(MAX_LIMIT_35);
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_REG_NAME ) )->SetMaxCharNum(MAX_LIMIT_50);
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_ACCOUNT_DESIGNATION ) )->SetMaxCharNum(MAX_LIMIT_50);
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_REG_ACCOUNT) )->SetMaxCharNum(MAX_LIMIT_50);
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_PORTFOLIO_CODE ) )->SetMaxCharNum(MAX_LIMIT_50); 
   AddControl (CTRL_STATIC,		IDC_STATIC_FIRST_NAME,	CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,		IDC_STATIC_LAST_NAME,	CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,		IDC_STATIC_LANGUAGE,	CTRLFLAG_GUI_FIELD);     
   AddControl (CTRL_STATIC,		IDC_STATIC_PHONE,		CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,		IDC_STATIC_FAX,			CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,		IDC_STATIC_EMAIL,		CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,		IDC_STATIC_EXT,			CTRLFLAG_GUI_FIELD);     
   AddControl (CTRL_CHECKBOX,	IDC_RD_CONTACT1,	    CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_CHECKBOX,	IDC_RD_CONTACT2,	    CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD);

   //Address Page and Reg Address Page    
   AddControl( CTRL_EDIT, IDC_FUNDBROKER_REG_ADDRESS,IFASTBP_PROC::FUND_BROKER_LIST, 
		       ifds::FundBrokerRegAddr,CTRLFLAG_FIELDS_FROM_SUB_LIST, IDC_LIST_FUND_BROKER );
   AddControl( CTRL_EDIT,    IDC_EDT_REG_POSTCODE,IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::RegPostalCode,0,IDC_LIST_FUND_BROKER);
   AddControl( CTRL_COMBO,    IDC_CMB_REG_COUNTRY,IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::RegCountry,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FUND_BROKER);
   AddControl (CTRL_STATIC, IDC_STATIC_SHR_POST, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STATIC_ENTITY_COUNTRY, CTRLFLAG_GUI_FIELD);
 
   AddControl (CTRL_STATIC, IDC_STATIC_LINK_TRANSFER_AGENT, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STATIC_LINK_FUND_COMPANY, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STATIC_LINK_FUND_BROKER_TYPE, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STATIC_LINK_CLIENT_GROUP, CTRLFLAG_GUI_FIELD);

   AddControl( CTRL_EDIT, IDC_EDT_LINK_TRANSFER_AGENT,IFASTBP_PROC::FUND_BROKER_LIST, ifds::FbTagent, 0, IDC_LIST_FUND_BROKER );	// Transfer Agent
   AddControl( CTRL_EDIT, IDC_EDT_LINK_FUND_COMPANY,IFASTBP_PROC::FUND_BROKER_LIST, ifds::FbFndCmpny, 0, IDC_LIST_FUND_BROKER );	// Fund Company
   AddControl( CTRL_EDIT, IDC_EDT_LINK_FUND_BROKER_TYPE,IFASTBP_PROC::FUND_BROKER_LIST, ifds::FbType, 0, IDC_LIST_FUND_BROKER );	// Fund Broker Type
   AddControl( CTRL_EDIT, IDC_EDT_LINK_CLIENT_GROUP,IFASTBP_PROC::FUND_BROKER_LIST, ifds::FbClientGrp, 0, IDC_LIST_FUND_BROKER );	// Underlying Client/Client Group

   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_LINK_TRANSFER_AGENT ) )->SetMaxCharNum( 60 );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_LINK_FUND_COMPANY ) )->SetMaxCharNum( 60 );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_LINK_FUND_BROKER_TYPE ) )->SetMaxCharNum( 60 );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_LINK_CLIENT_GROUP ) )->SetMaxCharNum( 60 );

   CString cstrInfo;
   cstrInfo.LoadString(TXT_FUNDBRKRID_PAGE);    
   DSTTabCtrl* pTabCtrl  = NULL;
   pTabCtrl =	AddTabControl(CLASSNAME,IDC_TAB_FUNDBRKRID, cstrInfo);
	 if (pTabCtrl)     
	  {  
	    pTabCtrl->SetMinTabWidth (50);
		pTabCtrl->AddTab (TXT_FUNDBRKRID_PAGE);
		pTabCtrl->AddTab (TXT_LINKINFO_PAGE);
		pTabCtrl->AddTab (TXT_BBR_PAGE);
		pTabCtrl->AddTab (TXT_ACCOUNTINFO_PAGE);
		pTabCtrl->AddTab (TXT_CONTACT_INFO);
		pTabCtrl->AddTab (TXT_ADDRESS_PAGE);
		pTabCtrl->AddTab (TXT_REG_ADDRESS_PAGE);

		pTabCtrl->registerListControl( IDC_LV_ENTITY_IDS, TXT_FUNDBRKRID_PAGE);
		pTabCtrl->registerControl ( IDC_STATIC_TYPE, TXT_FUNDBRKRID_PAGE);
		pTabCtrl->registerControl ( IDC_STATIC_VALUE, TXT_FUNDBRKRID_PAGE);
		pTabCtrl->registerControl ( IDC_STATIC_CNTRY_OF_ISSUE,TXT_FUNDBRKRID_PAGE);
		pTabCtrl->registerControl ( IDC_STATIC_DATE,TXT_FUNDBRKRID_PAGE);	
		pTabCtrl->registerControl ( IDC_CMB_ID_TYPE  , TXT_FUNDBRKRID_PAGE);
		pTabCtrl->registerControl ( IDC_EDT_ID_VALUE , TXT_FUNDBRKRID_PAGE);
		pTabCtrl->registerControl ( IDC_CMB_COUNTRY_OF_ISSUE, TXT_FUNDBRKRID_PAGE);
		pTabCtrl->registerControl ( IDC_DTP_ID_DATE ,TXT_FUNDBRKRID_PAGE);
		//Link Info-TAB
		pTabCtrl->registerControl ( IDC_STATIC_LINK_TRANSFER_AGENT, TXT_LINKINFO_PAGE);		// Transfer Agent
		pTabCtrl->registerControl ( IDC_STATIC_LINK_FUND_COMPANY, TXT_LINKINFO_PAGE);		// Fund Company
		pTabCtrl->registerControl ( IDC_STATIC_LINK_FUND_BROKER_TYPE, TXT_LINKINFO_PAGE);	// Fund Broker Type
		pTabCtrl->registerControl ( IDC_STATIC_LINK_CLIENT_GROUP, TXT_LINKINFO_PAGE);	    // Underlying Client/Client Group
		pTabCtrl->registerControl ( IDC_EDT_LINK_TRANSFER_AGENT, TXT_LINKINFO_PAGE);
		pTabCtrl->registerControl ( IDC_EDT_LINK_FUND_COMPANY, TXT_LINKINFO_PAGE);
		pTabCtrl->registerControl ( IDC_EDT_LINK_FUND_BROKER_TYPE, TXT_LINKINFO_PAGE);
		pTabCtrl->registerControl ( IDC_EDT_LINK_CLIENT_GROUP, TXT_LINKINFO_PAGE);
		//BRR-TAB
		pTabCtrl->registerControl ( IDC_STATIC_BRANCH_CODE, TXT_BBR_PAGE);
		pTabCtrl->registerControl ( IDC_STATIC_DEALER_CODE, TXT_BBR_PAGE);
		pTabCtrl->registerControl ( IDC_STATIC_AGENT_CODE, TXT_BBR_PAGE);
		pTabCtrl->registerControl ( IDC_EDT_BRANCH_CODE , TXT_BBR_PAGE);
		pTabCtrl->registerControl ( IDC_EDT_DEALER_CODE, TXT_BBR_PAGE);
		pTabCtrl->registerControl ( IDC_EDT_AGENT_CODE , TXT_BBR_PAGE);
		//ACCOUNTINFO-TAB
		pTabCtrl->registerControl ( IDC_STATIC_ACCOUNT_SRV, TXT_ACCOUNTINFO_PAGE);
		pTabCtrl->registerControl ( IDC_STATIC_REG_NAME, TXT_ACCOUNTINFO_PAGE);
		pTabCtrl->registerControl ( IDC_STATIC_ACCOUNT_DESIGNATION, TXT_ACCOUNTINFO_PAGE);
		pTabCtrl->registerControl ( IDC_STATIC_REG_ACCOUNT, TXT_ACCOUNTINFO_PAGE);
		pTabCtrl->registerControl ( IDC_STATIC_PORTFOLIO_CODE, TXT_ACCOUNTINFO_PAGE);
		pTabCtrl->registerControl ( IDC_STATIC_SETTLEMENT_TYPE,TXT_ACCOUNTINFO_PAGE);		  

		pTabCtrl->registerControl ( IDC_EDT_ACCOUNT_SRV , TXT_ACCOUNTINFO_PAGE);
		pTabCtrl->registerControl ( IDC_EDT_ACCOUNT_DESIGNATION, TXT_ACCOUNTINFO_PAGE);
		pTabCtrl->registerControl ( IDC_EDT_REG_NAME , TXT_ACCOUNTINFO_PAGE);
		pTabCtrl->registerControl ( IDC_EDT_REG_ACCOUNT ,TXT_ACCOUNTINFO_PAGE);
		pTabCtrl->registerControl ( IDC_EDT_PORTFOLIO_CODE ,TXT_ACCOUNTINFO_PAGE);
		pTabCtrl->registerControl ( IDC_CMB_SETTLEMENT_TYPE, TXT_ACCOUNTINFO_PAGE); 
	  	//CONTACTINFO -TAB
		pTabCtrl->registerControl ( IDC_STATIC_FIRST_NAME,	TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_STATIC_LAST_NAME,	TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_STATIC_LANGUAGE,	TXT_CONTACT_INFO);	
		pTabCtrl->registerControl ( IDC_STATIC_PHONE  ,		TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_STATIC_FAX	,		TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_STATIC_EMAIL,		TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_STATIC_EXT,			TXT_CONTACT_INFO); 

		pTabCtrl->registerControl ( IDC_RD_CONTACT1,		TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_RD_CONTACT2,		TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_EDT_CT_FIRST_NAME,	TXT_CONTACT_INFO);	
		pTabCtrl->registerControl ( IDC_EDT_CT_LAST_NAME,	TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_EDT_CT_PHONE,		TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_EDT_CT_FAX,			TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_EDT_CT_EMAIL,		TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_EDT_CT_EXT,			TXT_CONTACT_INFO);
		pTabCtrl->registerControl ( IDC_CMB_LANGUAGE,		TXT_CONTACT_INFO);
		//address tab
		pTabCtrl->registerControl (IDC_FUNDBROKER_ADDRESS, TXT_ADDRESS_PAGE);
		pTabCtrl->registerControl (IDC_STATIC_SHR_POST, TXT_ADDRESS_PAGE);
		pTabCtrl->registerControl (IDC_EDT_POSTCODE, TXT_ADDRESS_PAGE);
		pTabCtrl->registerControl (IDC_STATIC_ENTITY_COUNTRY, TXT_ADDRESS_PAGE);	
		pTabCtrl->registerControl (IDC_CMB_COUNTRY, TXT_ADDRESS_PAGE); 		    
		//registered address 
		pTabCtrl->registerControl (IDC_STATIC_SHR_POST, TXT_REG_ADDRESS_PAGE);
		pTabCtrl->registerControl (IDC_STATIC_ENTITY_COUNTRY, TXT_REG_ADDRESS_PAGE);	
		pTabCtrl->registerControl (IDC_FUNDBROKER_REG_ADDRESS, TXT_REG_ADDRESS_PAGE);
		pTabCtrl->registerControl (IDC_EDT_REG_POSTCODE, TXT_REG_ADDRESS_PAGE);      
		pTabCtrl->registerControl (IDC_CMB_REG_COUNTRY, TXT_REG_ADDRESS_PAGE);
	  }           
   
   //FAX Template
   AddControl( CTRL_COMBO,    IDC_CMB_FAX_TEMPLATE , IFASTBP_PROC::FUND_BROKER_LIST, 
               ifds::FbTemplate,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FUND_BROKER);
   GetDlgItem(IDC_CMB_FAX_TEMPLATE)->EnableWindow(FALSE);    
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_REG_POSTCODE ) )->SetAllowedChars( CHARACTERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_REG_POSTCODE ) )->SetMaxCharNum  ( MAX_ZIP_CODE);
   dynamic_cast<DSTEdit*>(GetControl( IDC_FUNDBROKER_REG_ADDRESS ) )->SetMaxCharNum  ( 200 );

  

  ConnectControlsToData ();
}

//******************************************************************************
bool FundBrokerDlg::doDisablePermCheckButton(UINT nID)

{
   TRACE_METHOD( CLASSNAME, I_( "doDisablePermCheckButtons" ));
   bool bEnableFlag = false;

   if( nID == IDC_BTN_DEL_FUNDBROKER )
   {      
      DString dstrNewItem;
      getParent()->getField ( this, IFASTBP_PROC::FUND_BROKER_LIST, FUNDBROKER::NEWITEM, dstrNewItem, false );            
      bEnableFlag = dstrNewItem.strip() != YES;
   }

   return(bEnableFlag);
}

//*********************************************************************************
void FundBrokerDlg::ControlUpdated(
                                UINT controlID,
                                const DString &strValue
                                )
{
   switch( controlID )
   {
      case IDC_EDT_FB_NAME:
         m_nameupdateflag = true;
         break;
      case IDC_EDT_CT_LAST_NAME:
         if( strValue == NULL_STRING )
         {
            LoadControl ( IDC_EDT_CT_FIRST_NAME );   
            LoadControl ( IDC_CMB_LANGUAGE );
            LoadControl ( IDC_EDT_CT_PHONE );
            LoadControl ( IDC_EDT_CT_FAX );
            LoadControl ( IDC_EDT_CT_EMAIL );
            LoadControl ( IDC_EDT_CT_EXT );         
         }
         break;
	  case IDC_CMB_ROUTING_TYPE:
		  {
			  DString dstrNewItem, dstrChanged;			  
			  getParent()->getField ( this, IFASTBP_PROC::FUND_BROKER_LIST, FUNDBROKER::NEWITEM, dstrNewItem, false );
			  getParent()->getField ( this, IFASTBP_PROC::FUND_BROKER_LIST, ifds::Changed, dstrChanged, false );
			  if( dstrNewItem == NO && dstrChanged == YES && strValue == INVESTRO )
			  {
				CString cstrYESNOWARN;
				cstrYESNOWARN.LoadString(TXT_UPDATE_FUND_TO_INVESTRO_CAPABLE);
				if( AfxMessageBox(cstrYESNOWARN,MB_YESNO ) == IDYES )//TXT_UPDATE_FUND_TO_INVESTRO_CAPABLE
				{					
					getParent()->setField(this, IFASTBP_PROC::FUND_BROKER_LIST, ifds::SetFundToInvestr, YES);
				}
				getParent()->setField(this, IFASTBP_PROC::FUND_BROKER_LIST, ifds::Changed, NO);
			  }                       
			  GetDlgItem(IDC_CMB_FAX_TEMPLATE)->EnableWindow( strValue == FAX );
			  LoadControl(IDC_CMB_FAX_TEMPLATE );  			
		  }
		 break;	
		case IDC_CMB_ID_TYPE:
			{
			 CString strItemText;
			 RemoveFromCombo(IDC_CMB_ID_TYPE, RemoveList);
			 if (strValue == ENTITY_IDS_VALUE::BIRTH_CERTIFICATE || strValue == ENTITY_IDS_VALUE::DRIVERS_LICENSE || 
				 strValue == ENTITY_IDS_VALUE::PASSPORT || strValue == ENTITY_IDS_VALUE::NATIONAL_ID)
			 {
				 GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_SHOW);
				 GetDlgItem (IDC_CMB_COUNTRY_OF_ISSUE )->ShowWindow(SW_SHOW);
				 
			 }
			 else
			 {
				 GetDlgItem (IDC_CMB_COUNTRY_OF_ISSUE ) ->ShowWindow(SW_HIDE);
				 GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_HIDE);
			 }
			 if (strValue == ENTITY_IDS_VALUE::FAST || ENTITY_IDS_VALUE::iFAST_OEIC||ENTITY_IDS_VALUE::iFAST_SICAV)
			 {
				 ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum(20);
			 }

			}
         break;    
      default:
         break;    
   }
}

//******************************************************************************
void FundBrokerDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

      	CString cstrDlgCaption;
		cstrDlgCaption.LoadString(TXT_FUND_BROKER_SYS_LVL);
      	
	   	SetWindowText( cstrDlgCaption );
}

//******************************************************************************

bool FundBrokerDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   SetDlgCaption();
   LoadListControl( IDC_LIST_FUND_BROKER );

   return(true);
}

//********************************************************************************
void FundBrokerDlg::OnKillfocusLastName()
{   
   if(!F4Clicked && m_nameupdateflag)
   {      
      uNameCtrlID = IDC_EDT_FB_NAME;
      PostMessage (UM_OPENENTITYSEARCHDLG);   
   }
   m_nameupdateflag = false;
}

//********************************************************************************
void FundBrokerDlg::OnKillfocusCTLastName()
{   
/*
   if(!F4Clicked)
   {   
      uNameCtrlID = IDC_EDT_CT_LAST_NAME;
      PostMessage (UM_OPENENTITYSEARCHDLG);   
   }
*/
}
//******************************************************************************

BOOL FundBrokerDlg::PreTranslateMessage( MSG* pMsg ) 
{

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_FB_NAME ) )
      {
         F4Clicked = true;
         PostMessage (UM_OPENENTITYSEARCHDLG);
         uNameCtrlID = IDC_EDT_FB_NAME;
         GetDlgItem( IDC_FUNDBROKER_ADDRESS )->SetFocus();         
      }
/*
      else if( GetFocus() == GetDlgItem( IDC_EDT_CT_LAST_NAME ) )
      {
         F4Clicked = true;
         PostMessage (UM_OPENENTITYSEARCHDLG);
         uNameCtrlID = IDC_EDT_CT_LAST_NAME; 
         GetDlgItem( IDC_EDT_CT_PHONE )->SetFocus();
      }

      else if( GetFocus() == GetDlgItem( IDC_EDT_CT_FIRST_NAME ) )
      {
         F4Clicked = true;
         PostMessage (UM_OPENENTITYSEARCHDLG);
         uNameCtrlID = IDC_EDT_CT_FIRST_NAME;
         GetDlgItem( IDC_EDT_CT_PHONE )->SetFocus();
      }
*/
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************
LRESULT FundBrokerDlg::OpenEntitySearchDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenSlsRepListDlg"));
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   eRtn = OpenEntitySearchDlg();
   return eRtn;
}

//******************************************************************
E_COMMANDRETURN FundBrokerDlg::OpenEntitySearchDlg()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenSlsRepListDlg"));
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {     
      CString lastname;
      DString dstrLastName, isNameUpdate = YES, exactsearch = NO;
      GetDlgItem( uNameCtrlID )->GetWindowText( lastname );
      dstrLastName = lastname;      

      if(!F4Clicked) //lost focus
      {         
         if( uNameCtrlID == IDC_EDT_FB_NAME ) 
         {
            getParent()->getField(this,IFASTBP_PROC::FUND_BROKER_LIST,FUNDBROKER::ISNAMEUPDATE, isNameUpdate,false );            
         }
         else 
         {
            isNameUpdate = NO;
         }
         exactsearch = YES;
      }

      F4Clicked = false;

      if( isNameUpdate == YES && dstrLastName != NULL_STRING )
      {
         
         setParameter( SRCHLIT::SEARCH_CRITERIA_CODE, SEARCHCRITERIA::ENTITY_SEARCH );
         setParameter( SRCHLIT::SEARCH_USING_CODE, SEARCHENTITYUSING::NAME );
         setParameter( SRCHLIT::FIRST_VALUE, NULL_STRING );
         setParameter( SRCHLIT::SECOND_VALUE, dstrLastName );
         setParameter( SRCHLIT::BACKGROUND_SEARCH, YES);
         setParameter( SRCHLIT::ALLENTITY, YES);         
         setParameter( SRCHLIT::EXACTSEARCH, exactsearch); 

         eRtn = invokeCommand( getParent(), CMD_BPROC_SEARCH, PROC_NO_TYPE, true, NULL );
         
         DString entityId;		
         switch (eRtn)
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
            {
               getParameter( I_( "EntityId" ), entityId );                     
               if( uNameCtrlID == IDC_EDT_FB_NAME )
               {
                  getParent()->setField(this, IFASTBP_PROC::FUND_BROKER_LIST, ifds::EntityId, entityId);                  
               }
/*
               else if ( uNameCtrlID == IDC_EDT_CT_LAST_NAME )
               {
                  CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RD_CONTACT1 ) );
                  if( pRadioButton->GetCheck() )
                  {
                     getParent()->setField(this, IFASTBP_PROC::FUND_BROKER_LIST, ifds::Contact1EntityID, entityId);
                  }
                  else
                  {
                     getParent()->setField(this, IFASTBP_PROC::FUND_BROKER_LIST, ifds::Contact2EntityID, entityId);
                  }                  
               }
*/
			   const DString* dstrKey = &(getParent()->getCurrentListItemKey(this,IFASTBP_PROC::FUND_BROKER_LIST ) );				
               LoadListControl( IDC_LIST_FUND_BROKER, dstrKey );
            }
            case CMD_CANCEL:
               break;
            default:
               if( uNameCtrlID == IDC_EDT_FB_NAME && uNameCtrlID == IDC_EDT_CT_LAST_NAME 
                  && uNameCtrlID == IDC_EDT_CT_FIRST_NAME )
               {
                  // Display error
                  // ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
                  // Clear condition, create new entity in Process by set name.
               }
               break;
         }
      }
      m_nameupdateflag = false;
   }
   catch(ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch(...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }

   return(eRtn);
}

//******************************************************************************
void FundBrokerDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnReset" ) );
   ResetListItem ( IDC_LIST_FUND_BROKER );
}
//*********************************************************************************
void FundBrokerDlg::OnBtnAddFeeParam()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddFeeParam" ) );
   AddToListControl( IDC_LIST_FEE_PARAM );   
}
//********************************************************************************
void FundBrokerDlg::OnBtnDelFeeParam()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelFeeParam" ) );
   DeleteFromListControl( IDC_LIST_FEE_PARAM );
}
//**********************************************************************************
void FundBrokerDlg::OnBtnFeeParamMore()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnFeeParamMore" ) );
   CWaitCursor wait;
   static int cursel;
   cursel = GetList( IDC_LIST_FEE_PARAM )->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);  
   const DString *crtKey = &getParent()->getCurrentListItemKey( this,IFASTBP_PROC::FEE_PARAM_LIST );
   if( getParent()->performSearch( this, IFASTBP_PROC::FEE_PARAM_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LIST_FEE_PARAM );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LIST_FEE_PARAM )->SetSelection( crtKey );
      }
   }
   GetDlgItem(IDC_BTN_MORE_FEE)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::FEE_PARAM_LIST ) );
   GetList( IDC_LIST_FEE_PARAM )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);   

}


//**********************************************************************************
void FundBrokerDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::FUND_BROKER_LIST );
}

//************************************************************************************
void FundBrokerDlg::DoListItemChanged(
                                   UINT listControlID,
                                   const DString &strKey, 
                                   bool bIsNewItem ,
                                   bool bIsDummyItem
                                   )
{


   if( listControlID == IDC_LIST_FUND_BROKER)
   {
      // Historical
      m_nameupdateflag = false;
	  GetDlgItem(IDC_BTN_MORE_FEE)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::FEE_PARAM_LIST ) );
   }

}

//******************************************************************************

void FundBrokerDlg::InitControl(
                         UINT controlID
                         )
{

/*	switch(controlID)
	{

		default:

		break;
	}
*/
}

//*********************************************************************************
bool FundBrokerDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
   bool bRet = true;  

   return(bRet);
}

//**********************************************************************************
void FundBrokerDlg::EnableControls(bool bEnable )
{
//  GetDlgItem(IDC_BTN_DETAIL)->EnableWindow(bEnable);
}

//*********************************************************************************
void FundBrokerDlg::OnBtnAddFundBroker()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddFundBroker" ) );
   AddToListControl( IDC_LIST_FUND_BROKER );
}

//*********************************************************************************
void FundBrokerDlg::OnBtnDelFundBroker()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelFundBroker" ) );
   DeleteFromListControl( IDC_LIST_FUND_BROKER );
}
//*********************************************************************************
void FundBrokerDlg::OnBtnMoreFundBroker()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnMoreFundBroker" ) );
   CWaitCursor wait;
   static int cursel;
   cursel = GetList( IDC_LIST_FUND_BROKER )->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);  
   const DString *crtKey = &getParent()->getCurrentListItemKey( this,IFASTBP_PROC::FUND_BROKER_LIST );
   if( getParent()->performSearch( this, IFASTBP_PROC::FUND_BROKER_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LIST_FUND_BROKER );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LIST_FUND_BROKER )->SetSelection( crtKey );
      }
   }
   GetDlgItem(IDC_BTN_MORE_FUNDBROKER)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::FUND_BROKER_LIST ) );
   GetList( IDC_LIST_FUND_BROKER )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);
}
//*********************************************************************************
void FundBrokerDlg::OnBtnAddID()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddID" ) );
   AddToListControl( IDC_LV_ENTITY_IDS );
}
//*********************************************************************************
void FundBrokerDlg::OnBtnDelID()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelID" ) );
   DeleteFromListControl( IDC_LV_ENTITY_IDS );
}

//*********************************************************************************
void FundBrokerDlg::OnBtnContact1()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnContact1" ) );
   getParent()->setField(this, IFASTBP_PROC::FUND_BROKER_LIST, 
                     ifds::Contact, I_("1"));

   LoadControl ( IDC_EDT_CT_FIRST_NAME );
   LoadControl ( IDC_EDT_CT_LAST_NAME );
   LoadControl ( IDC_CMB_LANGUAGE );
   LoadControl ( IDC_EDT_CT_PHONE );
   LoadControl ( IDC_EDT_CT_FAX );
   LoadControl ( IDC_EDT_CT_EMAIL );
   LoadControl ( IDC_EDT_CT_EXT );
}
//*********************************************************************************
void FundBrokerDlg::OnBtnContact2()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnContact2" ) );
   getParent()->setField(this, IFASTBP_PROC::FUND_BROKER_LIST, 
                     ifds::Contact, I_("2"));

   LoadControl ( IDC_EDT_CT_FIRST_NAME );
   LoadControl ( IDC_EDT_CT_LAST_NAME );
   LoadControl ( IDC_CMB_LANGUAGE );
   LoadControl ( IDC_EDT_CT_PHONE );
   LoadControl ( IDC_EDT_CT_FAX );
   LoadControl ( IDC_EDT_CT_EMAIL );
   LoadControl ( IDC_EDT_CT_EXT );
}

//*********************************************************************************
void FundBrokerDlg::OnBtnSettleLoc()
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSettleLoc"));
	
	DString dstrFundBrokerCode;

	getParent()->getField ( this, IFASTBP_PROC::FUND_BROKER_LIST, ifds::FundBrokerCode, dstrFundBrokerCode, false );            
    setParameter( I_("FundBrokerCode"), dstrFundBrokerCode );

	E_COMMANDRETURN eRtn = 
		invokeCommand( getParent(), CMD_BPROC_FUND_BROKER_SETTLEMENT_INSTR, PROC_SUPPORT, true, NULL );
	    
	switch (eRtn)
	{
		case CMD_OK:
		case CMD_MODELESS_INPROCESS:
		{
			break;
		}
		case CMD_CANCEL:
			break;
		default:
		{
			// Display error                  
			ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
			break;
		}
	}
}

//******************************************************************************
//              FundBrokerDlg::tabSelectionChanged
//  Function :called when the tab slection is changed
//  Input    :tabControl ID,PageName of the TAB
//  Output   :Void
//  Return   :void
//******************************************************************************
    
void FundBrokerDlg::tabSelectionChanged( UINT tabControlID, const DString& strPageName )
{

   CString cstrPageAddress, cstrPageRegAdd,cstrAddressText,cstrZipText,cstrCountryText, 
		   cstrBrokerIDInfoPage,cstrBBRPage,cstrAccountInfoPage,cstrContactInfoPage,cstrLinkInfoPage;
   cstrPageAddress.LoadString( TXT_ADDRESS_PAGE );    
   cstrPageRegAdd.LoadString( TXT_REG_ADDRESS_PAGE );
   cstrBrokerIDInfoPage.LoadString(TXT_FUNDBRKRID_PAGE);
   cstrLinkInfoPage.LoadString(TXT_LINKINFO_PAGE);
   cstrBBRPage.LoadString(TXT_BBR_PAGE);
   cstrAccountInfoPage.LoadString(TXT_ACCOUNTINFO_PAGE);
   cstrContactInfoPage.LoadString(TXT_CONTACT_INFO);
   if( strPageName.c_str() == cstrPageAddress )
   {
	  
	   cstrZipText.LoadString(TXT_STC_ZIPCODE);
	   cstrCountryText.LoadString(TXT_STC_COUNTRY);
	   GetDlgItem( IDC_STATIC_SHR_POST )->SetWindowText( cstrZipText ); 
	   GetDlgItem( IDC_STATIC_ENTITY_COUNTRY )->SetWindowText( cstrCountryText );
	   GetDlgItem( IDC_ADD_ID )->ShowWindow(SW_HIDE);
	   GetDlgItem( IDC_BTN_DEL_ID )->ShowWindow(SW_HIDE); 
	  

   }
   if( strPageName.c_str() == cstrPageRegAdd )
   {
	    
		cstrZipText.LoadString(TXT_STC_REG_ZIPCODE);
		cstrCountryText.LoadString(TXT_STC_REG_COUNTRY);
	    GetDlgItem( IDC_STATIC_SHR_POST )->SetWindowText( cstrZipText );
		GetDlgItem( IDC_STATIC_ENTITY_COUNTRY )->SetWindowText( cstrCountryText );
		GetDlgItem( IDC_ADD_ID )->ShowWindow(SW_HIDE);
		GetDlgItem( IDC_BTN_DEL_ID )->ShowWindow(SW_HIDE); 
		
   }
   if( strPageName.c_str() ==  cstrBrokerIDInfoPage)
   {
	  GetDlgItem( IDC_ADD_ID )->ShowWindow(SW_SHOW);
	  GetDlgItem( IDC_BTN_DEL_ID )->ShowWindow(SW_SHOW); 		  	 
   }
   if( strPageName.c_str() == cstrLinkInfoPage)
   {
	  GetDlgItem( IDC_ADD_ID )->ShowWindow(SW_HIDE);
	  GetDlgItem( IDC_BTN_DEL_ID )->ShowWindow(SW_HIDE); 
   }
   if( strPageName.c_str() ==   cstrBBRPage)
   {
	  GetDlgItem( IDC_ADD_ID )->ShowWindow(SW_HIDE);
	  GetDlgItem( IDC_BTN_DEL_ID )->ShowWindow(SW_HIDE); 
   }
   if( strPageName.c_str() ==   cstrAccountInfoPage)
   {
	   GetDlgItem( IDC_ADD_ID )->ShowWindow(SW_HIDE);
	   GetDlgItem( IDC_BTN_DEL_ID )->ShowWindow(SW_HIDE); 
   }
   if( strPageName.c_str() ==   cstrContactInfoPage)
   {
	   GetDlgItem( IDC_ADD_ID )->ShowWindow(SW_HIDE);
	   GetDlgItem( IDC_BTN_DEL_ID )->ShowWindow(SW_HIDE); 
   }
   
}
//******************************************************************************
//              FundBrokerDlg::RemoveFromCombo
//  Function :Removes the input test from the combo box
//  Input    :ComboBox ID,An rray of text to be removed
//  Output   :Void
//  Return   :void
//******************************************************************************
void FundBrokerDlg::RemoveFromCombo(UINT CtrlID,const CString* strItemText)
{
		 int index = 0,i= 0;
	     CComboBox *pIDComboBox = static_cast < CComboBox* > ( GetDlgItem( CtrlID));
		 while(strItemText[i].Compare(_T("\0")))
		 {
			pIDComboBox->DeleteString(pIDComboBox->FindStringExact(index,strItemText[i]));
			i++;
		 }
		 LoadControl ( CtrlID );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/*  
 * 
 */





