//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//******************************************************************************
//
// ^FILE   : TaxExemptAuthorizationDlg.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : Feb 10, 2004
//
// ^CLASS    : TaxExemptAuthorizationDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <bfproc\AbstractProcess.hpp>
#include "TaxExemptAuthorizationDlg.h"
#include <ifastcbo\DSTCommonFunction.hpp>

#include <uibase\DSTListCtrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <uibase\DSTComboBox.h>
#include <uibase\dstbutton.h>
#include <ifastbp\TaxExemptAuthorizationProcessIncludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_TAX_EXEMPT_AUTHORIZATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TaxExemptAuthorizationDlg > dlgCreator( CMD_GUI_TAX_EXEMPT_AUTHORIZATION );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME							= I_( "TaxExemptAuthorizationDlg" );
   const I_CHAR * const LV_TAX_EXEMPT_AUTHORIZATION_LIST    = I_( "TaxExemptAuthorizationList" );  
   const I_CHAR * const YES									= I_( "Y" );
   const I_CHAR * const NO									= I_( "N" );         
   const I_CHAR * const FUNDCODE							= I_( "FundCode" );         
   const I_CHAR * const CLASSCODE							= I_( "ClassCode" );         
   const I_CHAR * const FUNDNAME							= I_( "FundName" );         
   const I_CHAR * const FUNDWKN								= I_( "FundWKN" );         
   const I_CHAR * const FUNDISIN							= I_( "FundISIN" );   
   const I_CHAR * const NR301_NO							= I_( "NRNO" ); 
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId TaxExemptAuthorizationHeading;
	extern CLASS_IMPORT const BFTextFieldId TaxExemptAuthorizationHeading1;
	extern CLASS_IMPORT const BFTextFieldId TaxExemptAuthorizationHeading2;
	extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
	extern CLASS_IMPORT const BFTextFieldId FundCode;
	extern CLASS_IMPORT const BFTextFieldId ClassCode;
	extern CLASS_IMPORT const BFTextFieldId FundName;
	extern CLASS_IMPORT const BFTextFieldId FundWKN;
	extern CLASS_IMPORT const BFTextFieldId FundISIN;
	extern CLASS_IMPORT const BFTextFieldId ExemptLevelList;
   extern CLASS_IMPORT const BFTextFieldId BackWithholdTax;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const TAX_EXEMPT_AUTHORIZATION;
}
namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

class LVTaxExemptAuthorizationData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVTaxExemptAuthorizationData() {}

   DString m_dstrTaxExType, m_dstrTaxJuris, m_dstrEffectiveDate, m_dstrStopDate;
   DString m_dstrExemptAmtOrig, m_dstrExemptAmtRemain, m_dstrEntityId;
   DString m_dstrFundCode, m_dstrClassCode, m_dstrFundISIN, m_dstrFundWKN, m_dstrExemptionScope;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {

      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EntityId, m_dstrEntityId );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TaxExType, m_dstrTaxExType );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TaxJurisCode, m_dstrTaxJuris );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EffectiveDate, m_dstrEffectiveDate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::StopDate, m_dstrStopDate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ExemptAmtOrig, m_dstrExemptAmtOrig );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ExemptAmtRemain, m_dstrExemptAmtRemain );
	   pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundCode, m_dstrFundCode );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ClassCode, m_dstrClassCode );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundISIN,  m_dstrFundISIN);
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundWKN, m_dstrFundWKN );
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ExemptionScope, m_dstrExemptionScope );
   }
};

class LVTaxExemptAuthorizationAdapter : public IFDSListCtrlAdapter< LVTaxExemptAuthorizationData >
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
      } else if( *pFieldId == ifds::TaxExType ) {
         result = i_strcmp( pData1->m_dstrTaxExType.c_str(), pData2->m_dstrTaxExType.c_str() );
	  } else if( *pFieldId == ifds::FundCode ) {
         result = i_strcmp( pData1->m_dstrFundCode.c_str(), pData2->m_dstrFundCode.c_str() );
	  } else if( *pFieldId == ifds::ClassCode ) {
         result = i_strcmp( pData1->m_dstrClassCode.c_str(), pData2->m_dstrClassCode.c_str() );
   	  } else if( *pFieldId == ifds::FundISIN ) {
         result = i_strcmp( pData1->m_dstrFundISIN.c_str(), pData2->m_dstrFundISIN.c_str() );
	  } else if( *pFieldId == ifds::FundWKN ) {
         result = i_strcmp( pData1->m_dstrFundWKN.c_str(), pData2->m_dstrFundWKN.c_str() );
      } else if( *pFieldId == ifds::TaxJurisCode ) {
         result = i_strcmp( pData1->m_dstrTaxJuris.c_str(), pData2->m_dstrTaxJuris.c_str() );
      } else if( *pFieldId == ifds::EffectiveDate ) {
			if ( DSTCommonFunctions::CompareDates( pData1->m_dstrEffectiveDate.c_str(), pData2->m_dstrEffectiveDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = 1;
			else if ( DSTCommonFunctions::CompareDates( pData2->m_dstrEffectiveDate.c_str(), pData1->m_dstrEffectiveDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = -1;
			// for equal, result will be 0         
      } else if( *pFieldId == ifds::StopDate ) {
         result = i_strcmp( pData1->m_dstrStopDate.c_str(), pData2->m_dstrStopDate.c_str() );
      } else if( *pFieldId == ifds::ExemptAmtOrig ) {
			double dblExemptAmtOrig1 = DSTCommonFunctions::convertToDouble ( pData1->m_dstrExemptAmtOrig.c_str() );
			double dblExemptAmtOrig2 = DSTCommonFunctions::convertToDouble ( pData2->m_dstrExemptAmtOrig.c_str() );         			
			if ( dblExemptAmtOrig1 > dblExemptAmtOrig2 )
				result = 1;
			else if ( dblExemptAmtOrig1 < dblExemptAmtOrig2 )
				result = -1;
			// for equal result will be 0;
      } else if( *pFieldId == ifds::ExemptAmtRemain ) {
			double dblExemptAmtRemain1 = DSTCommonFunctions::convertToDouble ( pData1->m_dstrExemptAmtRemain.c_str() );
			double dblExemptAmtRemain2 = DSTCommonFunctions::convertToDouble ( pData2->m_dstrExemptAmtRemain.c_str() ); 
         if ( dblExemptAmtRemain1 > dblExemptAmtRemain2 )
				result = 1;
			else if ( dblExemptAmtRemain1 < dblExemptAmtRemain2 )
				result = -1;
      }	else if( *pFieldId == ifds::ExemptionScope ) {
         result = i_strcmp( pData1->m_dstrExemptionScope.c_str(), pData2->m_dstrExemptionScope.c_str() );
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
         } else if( *pFieldId == ifds::TaxExType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTaxExType.c_str();
         } else if( *pFieldId == ifds::TaxJurisCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTaxJuris.c_str();
         } else if( *pFieldId == ifds::EffectiveDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrEffectiveDate.c_str();
         } else if( *pFieldId == ifds::StopDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrStopDate.c_str();
         } else if( *pFieldId == ifds::ExemptAmtOrig ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrExemptAmtOrig.c_str();
         } else if( *pFieldId == ifds::ExemptAmtRemain ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrExemptAmtRemain.c_str();
         } 
         else if( *pFieldId == ifds::EntityId ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrEntityId.c_str();
         } 
		 else if( *pFieldId == ifds::FundCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFundCode.c_str();
         }
		 else if( *pFieldId == ifds::ClassCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrClassCode.c_str();
         } 
		 else if( *pFieldId == ifds::FundWKN ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFundWKN.c_str();
         } 
		 else if( *pFieldId == ifds::FundISIN ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFundISIN.c_str();
         } 
		 else if( *pFieldId == ifds::ExemptionScope ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrExemptionScope.c_str();
         } 
		 
         return( 1 );
      }
      return( 0 );
   }
};

//******************************************************************************
// Constructor
//******************************************************************************
TaxExemptAuthorizationDlg::TaxExemptAuthorizationDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( TaxExemptAuthorizationDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   dstrMarket = DSTCommonFunctions::getMarket();
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   //{{AFX_DATA_INIT( TaxExemptAuthorizationDlg )
   //}}AFX_DATA_INIT
   
}

//******************************************************************************
// Destructor
//******************************************************************************
TaxExemptAuthorizationDlg::~TaxExemptAuthorizationDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void TaxExemptAuthorizationDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( TaxExemptAuthorizationDlg ) 
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( TaxExemptAuthorizationDlg, BaseMainDlg )
//{{AFX_MSG_MAP( TaxExemptAuthorizationDlg )
ON_BN_CLICKED(IDC_BTN_ADMIN_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************
void TaxExemptAuthorizationDlg::OnPostInitDialog()
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
	SetUserAccesFunctionCode (UAF::TAX_EXEMPT_AUTHORIZATION);
	addBtnAddForPermissionCheck (IDC_BTN_ADD, IDC_LV_TAX_EXEMPT_LIST);
   addBtnDeleteForPermissionCheck (IDC_BTN_DELETE, IDC_LV_TAX_EXEMPT_LIST);
   addControls ();
//   DisplayDeregistration();
   
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY TaxExemptAuthorizationDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   return ( NO_CONDITION );
}

//******************************************************************************
// This method sets up the custom controls to the correct data set.
//******************************************************************************
void TaxExemptAuthorizationDlg::addControls( )
{

   IFDSListCtrl* pCtrl = 
      new IFDSAdaptedListCtrl< LVTaxExemptAuthorizationAdapter >
         ( this, CLASSNAME, 
			  IDC_LV_TAX_EXEMPT_LIST,
			  0, 			
			  /*LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE*/
			  0, true, true );

   BFFieldId taxExemptAuthorizationHeading;
   getHeadingList (taxExemptAuthorizationHeading);

   AddIFDSListControl( pCtrl, 
                       LV_TAX_EXEMPT_AUTHORIZATION_LIST,
                       IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST,
                       taxExemptAuthorizationHeading );

	if ( NULL != pCtrl )		
		pCtrl->SortOnColumn( 1 );

   //if ( dstrMarket == MARKET_IDS::CANADA ) {
   AddControl( CTRL_STATIC, IDC_DEREGISTATION, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::DeregAmtYrToDate, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );
   //}
	AddControl( CTRL_COMBO, 
					IDC_TAX_EXEMPT_TYPE, 
					IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, 
					ifds::TaxExType, 
					CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
					(UINT)IDC_LV_TAX_EXEMPT_LIST );
   AddControl( CTRL_COMBO, 
					IDC_TAX_JURIS, 
					IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, 
					ifds::TaxJurisCode, 
					CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
					(UINT)IDC_LV_TAX_EXEMPT_LIST );
   AddControl( CTRL_DATE, IDC_DTP_START_DATE, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::EffectiveDate, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );
   AddControl( CTRL_DATE, IDC_DTP_STOP_DATE, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::StopDate, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );
   AddControl( CTRL_EDIT, IDC_EXE_AMOUNT, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::ExemptAmtOrig, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );
   AddControl( CTRL_EDIT, IDC_EDT_CERT_NUM, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::CertNumber, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );
   AddControl( CTRL_EDIT, IDC_REMAIN_EXE_AMOUNT, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::ExemptAmtRemain, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );
   
   AddControl( CTRL_COMBO, 
					IDC_CMB_ACCOUNT_OWNER, 
					IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, 
					ifds::EntityId, 
					CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
					(UINT)IDC_LV_TAX_EXEMPT_LIST );
   AddControl( CTRL_COMBO, 
					IDC_CMB_EXEMPT_SCOPE, 
					IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, 
					ifds::ExemptionScope, 
					CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
					(UINT)IDC_LV_TAX_EXEMPT_LIST );
   AddControl( CTRL_COMBO, 
					IDC_CMB_REASON_CODE, 
					IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, 
					ifds::ExemptionReasonCode, 
					CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
					(UINT)IDC_LV_TAX_EXEMPT_LIST );
   						
   AddControl( CTRL_EDIT, IDC_EDT_FUND_NUMBER, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::FundNumber, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );
   AddControl( CTRL_EDIT, IDC_EDT_FUND_CODE, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::FundCode, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );
   AddControl( CTRL_STATIC, IDC_STC_FUND_NAME, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::FundName, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );
   AddControl( CTRL_EDIT, IDC_EDT_CLASS_CODE, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::ClassCode, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );

   if (dstrMarket == MARKET_IDS::LUXEMBOURG)
   {
		AddControl( CTRL_EDIT, IDC_EDT_WKN, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::FundWKN, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );
		AddControl( CTRL_EDIT, IDC_EDT_ISIN, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::FundISIN, CTRLFLAG_DEFAULT, IDC_LV_TAX_EXEMPT_LIST );
   }

   doRefresh(this, NULL_STRING);
	//EnableDisableDeleteButton();
	
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool TaxExemptAuthorizationDlg::doRefresh( GenericInterface * rpGICaller, 
                                           const I_CHAR * szOriginalCommand)
{
   DString dstrShrNum, 
      dstrAccountNum, 
      dstrEntityName;

   getParent()->getField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShrNum, dstrShrNum);
   getParent()->getField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum);  
   SetAccount (dstrAccountNum );   
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),dstrAccountNum,dstrEntityName );
   SetShrAcctCaption (dstrShrNum, dstrAccountNum, dstrEntityName);
   
   LoadListControl ( IDC_LV_TAX_EXEMPT_LIST );
   GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST));		//

   return(true);
}
//******************************************************************************
void TaxExemptAuthorizationDlg::OnBtnAdd()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAdd" ) );
   AddToListControl( IDC_LV_TAX_EXEMPT_LIST );
   GetList( IDC_LV_TAX_EXEMPT_LIST )->SetFocus();
}
//********************************************************************************
void TaxExemptAuthorizationDlg::OnBtnDelete()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelete" ) );
   DeleteFromListControl( IDC_LV_TAX_EXEMPT_LIST );
   GetList( IDC_LV_TAX_EXEMPT_LIST )->SetFocus();
}

//**********************************************************************************
void TaxExemptAuthorizationDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );
}

//******************************************************************************
void TaxExemptAuthorizationDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnReset" ) );
   ResetListItem( IDC_LV_TAX_EXEMPT_LIST );
   GetList( IDC_LV_TAX_EXEMPT_LIST )->SetFocus(); 

   LoadListControl ( IDC_LV_TAX_EXEMPT_LIST );
 } 

//*************************************************************************
void TaxExemptAuthorizationDlg::ControlUpdated( UINT controlID, 
															 const DString &strValue )
{   
   switch( controlID )
   {		
	   	case IDC_TAX_EXEMPT_TYPE:
			{
				ExemptTypeControlUpdated();
			}
			break;

		case IDC_EXE_AMOUNT:
			{							
				LoadControl( IDC_REMAIN_EXE_AMOUNT );
			}
			break;	

		case IDC_EDT_FUND_NUMBER:
			{
				LoadControl (IDC_EDT_FUND_CODE);
				LoadControl (IDC_EDT_CLASS_CODE);
				LoadControl (IDC_STC_FUND_NAME);
				
				if (dstrMarket == MARKET_IDS::LUXEMBOURG)
				{
					LoadControl (IDC_EDT_WKN);
					LoadControl (IDC_EDT_ISIN);
				}
			}
			break;

		case IDC_EDT_FUND_CODE:
		case IDC_EDT_CLASS_CODE:
			{
				LoadControl (IDC_EDT_FUND_NUMBER);
				LoadControl (IDC_STC_FUND_NAME);
				
				if (dstrMarket == MARKET_IDS::LUXEMBOURG)
				{
					LoadControl (IDC_EDT_WKN);
					LoadControl (IDC_EDT_ISIN);
				}
			}
			break;

		case IDC_EDT_WKN:
			LoadControl (IDC_EDT_FUND_NUMBER);
			LoadControl (IDC_EDT_CLASS_CODE);
			LoadControl (IDC_EDT_FUND_CODE);
			LoadControl (IDC_STC_FUND_NAME);
			LoadControl (IDC_EDT_ISIN);
			break;

		case IDC_EDT_ISIN:
			LoadControl (IDC_EDT_FUND_NUMBER);
			LoadControl (IDC_EDT_CLASS_CODE);
			LoadControl (IDC_EDT_FUND_CODE);
			LoadControl (IDC_STC_FUND_NAME);
			LoadControl (IDC_EDT_WKN);
			break;

		default:
			break;
	}
}

//******************************************************************************

void TaxExemptAuthorizationDlg::DoListItemChanged( UINT listControlID,
                                             const DString &strKey,
                                             bool bIsNewItem,
                                             bool bIsDummyItem )
{
   if( listControlID == IDC_LV_TAX_EXEMPT_LIST )
   {
      EnableDisableDeleteButton();
   }
}

//******************************************************************************

void TaxExemptAuthorizationDlg::EnableDisableDeleteButton()
{
	DString dstrExemptAmountUsed;
	getParent()->getField(this, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::ExemptAmountUsed, dstrExemptAmountUsed);   
    double dec_ExemptAmountUsed = DSTCommonFunctions::convertToDouble( dstrExemptAmountUsed );

	GetDlgItem( IDC_BTN_DELETE )->EnableWindow( dec_ExemptAmountUsed == 0 );
}

//******************************************************************************
void TaxExemptAuthorizationDlg::ExemptTypeControlUpdated()
{
	DString dstrExemptLevelList;
	DString dstrEUSDParticip,
      backupWithholdingTax;

	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	dstWorkSession->getOption (ifds::ExemptLevelList, dstrExemptLevelList, getParent()->getDataGroupId(), false);
	dstWorkSession->getOption (ifds::EUSDParticip, dstrEUSDParticip, getParent()->getDataGroupId(), false);
   dstWorkSession->getOption (ifds::BackWithholdTax, backupWithholdingTax, getParent()->getDataGroupId(), false);
	
   DString dstrTaxExType;
   getParent()->getField(this,IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::TaxExType, dstrTaxExType, false);

   if(dstrTaxExType == I_("NR") ||
	   dstrTaxExType == I_("INTR"))
   {
	   dstrExemptLevelList = I_("01");
   }
   else if(dstrTaxExType == I_("W8") ||
	   dstrTaxExType == I_("W9"))
   {
	   dstrExemptLevelList = I_("02");
   }
	bool	bShowAccountFields = true;
	bool	bShowFundFields = true;
	bool	bShowWKNISINFields = true;
	bool	bShowOtherFields = true;

	if (dstrExemptLevelList.pos (I_("03"))>= 0 )
	{
		bShowAccountFields = true;
		bShowFundFields = true;
		bShowWKNISINFields = dstrMarket == MARKET_IDS::LUXEMBOURG ? true : false;
	}
	else if (dstrExemptLevelList. pos (I_("04")) >= 0)
	{
		bShowFundFields = true;		
		bShowAccountFields = false;		
	}
	else if (dstrExemptLevelList. pos (I_("02")) >= 0)
	{
		bShowAccountFields = true;
		bShowFundFields = false;
		bShowWKNISINFields = false;
	}
	else // it has to be 01 then
	{
		bShowAccountFields = false;
		bShowFundFields = false;
		bShowWKNISINFields = false;
		bShowOtherFields = false;
	}
	
	// Account
	GetControl(IDC_CMB_ACCOUNT_OWNER)->Show(bShowAccountFields);
	GetControl(IDC_EDT_CERT_NUM)->Show(true);
	GetDlgItem(IDC_STC_ACCOUNT)->ShowWindow(bShowAccountFields);
	GetDlgItem(IDC_STATIC_CERT_NUM)->ShowWindow(true);

	// Fund
	GetDlgItem(IDC_STC_FUND)->ShowWindow(bShowFundFields);
	GetDlgItem(IDC_STC_CLASS_CODE)->ShowWindow(bShowFundFields);
	GetDlgItem(IDC_STC_FUND_NAME)->ShowWindow(bShowFundFields);
	GetControl(IDC_EDT_FUND_NUMBER)->Show(bShowFundFields);
	GetControl(IDC_EDT_FUND_CODE)->Show(bShowFundFields);
	GetControl(IDC_EDT_CLASS_CODE)->Show(bShowFundFields);

	// WKN & ISIN
	if (dstrMarket == MARKET_IDS::LUXEMBOURG)
	{
      GetDlgItem(IDC_STC_WKN)->ShowWindow(bShowWKNISINFields);
		GetDlgItem(IDC_STC_ISIN)->ShowWindow(bShowWKNISINFields);
		GetControl(IDC_EDT_WKN)->Show(bShowWKNISINFields);
		GetControl(IDC_EDT_ISIN)->Show(bShowWKNISINFields);
	}

	if(dstrTaxExType == NR301_NO){
		GetDlgItem(IDC_TAX_JURIS)->EnableWindow(false);
		GetDlgItem(IDC_CMB_EXEMPT_SCOPE)->EnableWindow(false);
	}
	else{
		GetDlgItem(IDC_TAX_JURIS)->EnableWindow(true);
		GetDlgItem(IDC_CMB_EXEMPT_SCOPE)->EnableWindow(true);
	}
}

//******************************************************************************
void TaxExemptAuthorizationDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel = GetList (IDC_LV_TAX_EXEMPT_LIST)->GetNextItem (-1, LVIS_SELECTED | LVNI_FOCUSED);
   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );

   if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_TAX_EXEMPT_LIST );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_TAX_EXEMPT_LIST )->SetSelection( crtKey );
      }
   }
   SetMessageStatusBar(NULL_STRING); 
   GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST));		//
   GetList (IDC_LV_TAX_EXEMPT_LIST)->SetSelection (cursel, true, true);
}

//******************************************************************************

BOOL TaxExemptAuthorizationDlg::PreTranslateMessage( MSG* pMsg ) 
{
	if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
	{
		if( GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) ||
			GetFocus() == GetDlgItem( IDC_EDT_CLASS_CODE ) ||
			GetFocus() == GetDlgItem( IDC_EDT_FUND_CODE ))
		{
			PostMessage( UM_OPENFUNDCLASSLISTDLG );
		}
		else if (dstrMarket == MARKET_IDS::LUXEMBOURG && 
			    (GetFocus() == GetDlgItem( IDC_EDT_WKN) ||
				GetFocus() == GetDlgItem( IDC_EDT_ISIN )))
		{
			PostMessage( UM_OPENFUNDCLASSLISTDLG );
		}
	}

	return BaseMainDlg::PreTranslateMessage (pMsg);
}

//******************************************************************************
LRESULT TaxExemptAuthorizationDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundListDlg" ) );

	E_COMMANDRETURN eRtn = CMD_CANCEL;
	CWaitCursor wait;

	try
	{
		if( GetFocus () == GetDlgItem( IDC_EDT_FUND_CODE ) ) 
		{
			DString dstrFundCode;

			GetControlText( IDC_EDT_FUND_CODE, dstrFundCode);
			setParameter (FUNDCODE, dstrFundCode);
		} 
		else if( GetFocus () == GetDlgItem( IDC_EDT_CLASS_CODE ) )
		{
			DString dstrClassCode;

			GetControlText (IDC_EDT_CLASS_CODE, dstrClassCode);
			setParameter (CLASSCODE, dstrClassCode);
		}
		else if( GetFocus () == GetDlgItem( IDC_EDT_WKN ) )
		{
			DString dstrWKN;

			GetControlText (IDC_EDT_WKN, dstrWKN);
			setParameter (CLASSCODE, dstrWKN);
		}
		else if( GetFocus () == GetDlgItem( IDC_EDT_ISIN ) )
		{
			DString dstrISIN;

			GetControlText (IDC_EDT_ISIN, dstrISIN);
			setParameter (CLASSCODE, dstrISIN);
		}
      
		//invoke the fund class dialog and process
		SetMessageStatusBar (TXT_LOAD_FUND_INFO);
		eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );

		switch (eRtn)
		{
			case CMD_OK:
			case CMD_MODELESS_INPROCESS:
            {
				DString dstrFundName, dstrFundCode, dstrClassCode, dstrFundISIN, dstrFundWKN;

				getParameter (FUNDNAME, dstrFundName);
				getParent()->setField ( this, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::FundName, dstrFundName);
				getParameter (FUNDCODE, dstrFundCode);
				getParent()->setField ( this, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::FundCode, dstrFundCode);
				getParameter (CLASSCODE, dstrClassCode);
				getParent()->setField ( this, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::ClassCode, dstrClassCode);

				LoadControl( IDC_EDT_FUND_CODE );
				LoadControl( IDC_EDT_CLASS_CODE );
				LoadControl( IDC_STC_FUND_NAME );

				if (dstrMarket == MARKET_IDS::LUXEMBOURG)
				{
					getParameter (FUNDWKN, dstrFundWKN);
					getParent()->setField ( this, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::FundWKN, dstrFundWKN);
					getParameter (FUNDISIN, dstrFundISIN);
					getParent()->setField ( this, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, ifds::FundISIN, dstrFundISIN);

					LoadControl( IDC_EDT_WKN );
					LoadControl( IDC_EDT_ISIN );
				}

				break;
			}
			case CMD_CANCEL:
				break;
			default:
				// Display error
				ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
				SetMessageStatusBar (NULL_STRING);
				break;
		}
		SetMessageStatusBar (NULL_STRING);
	}
	catch( ConditionException &ce )
	{
		ConditionMessageBox( ce );
	}
	catch (...)
	{
		DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
	}
	
	return eRtn;
}
void TaxExemptAuthorizationDlg::getHeadingList (BFFieldId& idField)
{
	DString dstrExemptLevelList;
   	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

	dstWorkSession->getOption(ifds::ExemptLevelList, dstrExemptLevelList, getParent()->getDataGroupId(), false);
	
	if (dstrExemptLevelList.pos (I_("03"))>= 0 )
		idField = ifds::TaxExemptAuthorizationHeading2;
	else if (dstrExemptLevelList. pos (I_("02")) >= 0)
		idField = ifds::TaxExemptAuthorizationHeading1;
	else // list is "01"
		idField = ifds::TaxExemptAuthorizationHeading;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TaxExemptAuthorizationDlg.cpp-arc  $
// 
//    Rev 1.8   Aug 01 2012 07:18:06   panatcha
// IN2956851 - disable control related to NR301exempt type
// 
//    Rev 1.7   Nov 15 2006 16:57:10   popescu
// Incident# 750524 - track the receipt of W9 forms
// 
//    Rev 1.6   Dec 09 2005 16:16:44   jankovii
// PET1228_FN02_EU Savings Directive Phase Two.
// 
//    Rev 1.5   Nov 28 2005 09:58:54   jankovii
// PET1228_FN02_ EU Savings Directive Phase Two
// 
//    Rev 1.4   Sep 15 2005 15:15:30   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   Aug 22 2005 10:54:08   ZHANGCEL
// PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
// 
//    Rev 1.2   Mar 04 2005 16:43:14   georgeet
// PET1171 FN01 - EU Savings Directive Tax Exemption.  Modified the existing screen to include four new fields with appropriate business logic.
// 
//    Rev 1.1   Sep 20 2004 10:48:10   ZHANGCEL
// PET1082_FNrlc: New Quebuc withholding tax enhancement
// 
//    Rev 1.0   Aug 06 2004 17:53:38   ZHANGCEL
// Initial revision.
*/


