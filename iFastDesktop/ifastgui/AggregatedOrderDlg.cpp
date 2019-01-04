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
// ^FILE   : AggregatedOrderDlg.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : Nov 4, 2004
//
// ^CLASS    : AggregatedOrderDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include <bfproc\AbstractProcess.hpp>
#include "AggregatedOrderDlg.h"
#include <ifastcbo\DSTCommonFunction.hpp>
#include <uibase\DSTListCtrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <uibase\DSTComboBox.h>
#include <uibase\dstbutton.h>
#include <uibase\dstedit.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\AggregatedOrderProcessInclude.h>
#include <uibase\dsttabctrl.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_AGGREGATED_ORDER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRADES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MSG;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AggregatedOrderDlg > dlgCreator( CMD_GUI_AGGREGATED_ORDER );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
	const I_CHAR * const CLASSNAME							= I_( "AggregatedOrderDlg" );
	const I_CHAR * const ONBTNREFRESH  						= I_( "OnBtnRefresh" );
	const I_CHAR * const LV_AGGREGATE_ORDER_LIST			= I_( "AggregatedOrderList" ); 
	const I_CHAR * const LV_PENDING_TRADE_LIST			= I_( "PendingTradeList");
	const I_CHAR * const YES								   = I_( "Y" );
   const I_CHAR * const NO									   = I_( "N" ); 
	const I_CHAR * const AGGREGATED							= I_( "01" );
	const I_CHAR * const ORDER_SENT							= I_( "02" );
	const I_CHAR * const DONOT_SEND							= I_( "03" );
	const I_CHAR * const PRICE_LOADED						= I_( "04" );
	const I_CHAR * const PRICE_POSTED						= I_( "05" );
   const int      MAX_CHAR_COUNT_DEFAULT              = 50;
   const UINT     NO_CONTROL                          =  0x00000;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AggregatedOrderListHeading;
   extern CLASS_IMPORT const BFTextFieldId AggrOrderPendingTradeListHeading;
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
   extern CLASS_IMPORT const BFIntegerFieldId NumberOfTrade;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFIntegerFieldId LossCount;
	extern CLASS_IMPORT const BFTextFieldId Recalculate;
	extern CLASS_IMPORT const BFTextFieldId Currency; 
	extern CLASS_IMPORT const BFTextFieldId AggrOrdRefreshed;
	extern CLASS_IMPORT const BFTextFieldId AllowEnableOk;
	extern CLASS_IMPORT const BFNumericFieldId WarnMsgCode;
}
namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const AGGREGATED_ORDER_INFORMATION;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace MFCAN_IP_PARAM
{
   extern IFASTBP_LINKAGE const I_CHAR * const LIST_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const CALLER;
}

typedef struct 
{
   public: E_CONTROLTYPE eType;
           UINT controlID;
           const BFContainerId idContainer;
           const BFFieldId idField;
           UINT flags;
           UINT controlGroupID;

}CONTROL_FIELD_MAPPING;

const CONTROL_FIELD_MAPPING controlFieldMapping[] = 
{
    //controlType  ControlID        ContainerID                         FieldID          Flag                                               controlGroupID
    { CTRL_COMBO, IDC_CMB_STATUS, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OrdStatus, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST,  (UINT)IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_COMBO, IDC_CMB_PRICE_TYPE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::AggrPriceType, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_COMBO, IDC_CMB_STTL_LOCATION, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::SettleLocationCode, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_COMBO, IDC_CMB_CLEAN_METHOD, IFASTBP_PROC::AGGREGATED_ORDER_LIST, 	ifds::ClrSettlMethod, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_COMBO, IDC_CMB_STTL_INST_CODE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::SettlInstrCode, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT,  IDC_EDT_PRICE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::Price, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_COMM_RATE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::Commission, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_CALCULATE_NAV, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::NAV, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_DATE, IDC_DTP_BRK_STTLDATE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::BrkSettlDate, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_DATE, IDC_DTP_TRADE_DATE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::TradeDate, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_ORIG_AMTTYPE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::AmountType, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_ORIG_AMOUNT, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::Amount, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_EXT_AMOUNT, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::ExternCharge, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_CAL_OFFER_PRICE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OfferPrice, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_ROUT_REF_NO, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::RoutingRef, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_STTL_AMTTYPE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::BrkSettlPUD, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_STTL_AMOUNT, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::BrkSettlAmtUnits, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_REBATE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::RebateRate, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_BENEFIT, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::AFTBenefit, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
	{ CTRL_EDIT, IDC_EDT_STTL_ACCT, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::SettleAccountNum, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
	{ CTRL_EDIT, IDC_EDT_DELIVERY_TO, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::DeliveryTo, CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE, IDC_LV_AGGREGATE_ORDER_LIST },
	{ CTRL_EDIT, IDC_EDT_FOR_ACCT, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::ForAccount, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
	{ CTRL_EDIT, IDC_EDT_IN_FAVOR_OF, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::InFavourOf, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
	{ CTRL_EDIT, IDC_EDT_REMARKS, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::RemarksAggr, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
	{ CTRL_COMBO, IDC_CMB_SEC_REC_FILE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::SecRecFileIndicator,	CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_AGGREGATE_ORDER_LIST },
	{ CTRL_STATIC, IDC_TXT_PROCESS_DATE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::ProcessDate, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
	{ CTRL_STATIC, IDC_TXT_PROCESS_TIME, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::ProcessTime, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
	{ CTRL_BUTTON, IDC_BTN_REFRESH, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::LossCount, 0, 0 },
	{ CTRL_BUTTON, IDC_BTN_RESET, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::Recalculate, 0, 0 },
	{ CTRL_STATIC, IDC_TXT_FUND_CURRENCY, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::Currency, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_STATIC, IDC_TXT_AGGR_DATE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::AggrDate, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
	{ CTRL_STATIC, IDC_TXT_AGGR_TIME, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::AggrTime, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    //{ CTRL_STATIC, IDC_TXT_INT_SETL_ACC, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::InFavourOf, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    //{ CTRL_STATIC, IDC_TXT_NUMBER_OF_TRADE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_PREF_CASH_MSG_TYPE, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::CashMsgType, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_BENFICIARY, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::Beneficiary, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_RECEIVING_BANK, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::ReceivingBank, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_SPECIAL_INST, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::SpecialInstructions, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_INTERMEDIARY_BANK, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::IntermediaryBank, CTRLFLAG_DEFAULT, IDC_LV_AGGREGATE_ORDER_LIST },
    { CTRL_EDIT, IDC_EDT_INT_SETL_ACC, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::InternalSettlementAccount, CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE, IDC_LV_AGGREGATE_ORDER_LIST }, 

};

int  numScreenControls = sizeof(controlFieldMapping)/sizeof( CONTROL_FIELD_MAPPING );

typedef struct 
{
   public: const UINT	STATIC_LABEL ;
           const UINT   EDIT_CONTROL ;

}TAB_CONTROL_FIELD_MAPPING;

const TAB_CONTROL_FIELD_MAPPING aggregateOrderDetailsTabControls[] = //IDD_AGGREGATE_HELPER_01 DIALOGEX Details 
{  
    // LABEL                   // EDIT CONTROL
    { IDC_STATIC_GEN_3 ,       IDC_CMB_STATUS          } ,           
    { IDC_STATIC_GEN_4 ,       IDC_CMB_PRICE_TYPE      } ,
    { IDC_STATIC_GEN_5 ,       IDC_EDT_PRICE           } ,
    { IDC_STATIC_GEN_6 ,       IDC_DTP_TRADE_DATE      } ,
    { IDC_STATIC_GEN_14 ,      IDC_EDT_COMM_RATE       } ,
    { IDC_STATIC_GEN_16 ,      IDC_EDT_REBATE          } ,
    { IDC_STATIC_GEN_15 ,      IDC_EDT_EXT_AMOUNT      } ,
    { IDC_TXT_SEC_REC_FILE ,   IDC_CMB_SEC_REC_FILE    } ,
    { IDC_STATIC_GEN_31 ,      IDC_EDT_REMARKS         } ,
    { IDC_STATIC_GEN_17 ,      IDC_EDT_CALCULATE_NAV   } ,
    { IDC_STATIC_GEN_18 ,      IDC_EDT_CAL_OFFER_PRICE } ,
    { IDC_STATIC_GEN_21 ,      IDC_TXT_FUND_CURRENCY   } ,
    { IDC_STATIC_GEN_19 ,      IDC_EDT_BENEFIT         } ,
    { IDC_STATIC_GEN_7 ,       NO_CONTROL              } , //use NO_CONTROL if there is no control associated
                                                              // eg:Group-box does not have any edit control associated with it
    { IDC_STATIC_GEN_8 ,       IDC_DTP_BRK_STTLDATE    } ,
    { IDC_STATIC_GEN_13 ,      IDC_EDT_STTL_AMOUNT     } ,
    { IDC_STATIC_GEN_9,        IDC_EDT_ROUT_REF_NO     } ,
    { IDC_STATIC_GEN_10,       IDC_EDT_ORIG_AMTTYPE    } ,
    { IDC_STATIC_GEN_11,       IDC_EDT_STTL_AMTTYPE    } ,             
    { IDC_STATIC_GEN_12,       IDC_EDT_ORIG_AMOUNT     } ,
};

int  numAggregateOrderDetailsTabControls = sizeof(aggregateOrderDetailsTabControls)/sizeof( TAB_CONTROL_FIELD_MAPPING ); 

const TAB_CONTROL_FIELD_MAPPING aggregateOrderSummaryTabControls[] = //IDD_AGGREGATE_HELPER_02 DIALOGEX Summary 
{  
     // LABEL                      // EDIT CONTROL
    { IDC_STATIC_GEN_26   ,        NO_CONTROL              } ,
    { IDC_TXT_NUMBER_OF_TRADE,     NO_CONTROL              } ,//Static edit controls should be registered as GUIField if they are not connected to the fields 
                                                              // { IDC_STATIC_GEN_26   , IDC_TXT_NUMBER_OF_TRADE } 
    { IDC_STATIC_GEN_28   ,        IDC_TXT_PROCESS_DATE    } ,
    { IDC_STATIC_GEN_30   ,        IDC_TXT_PROCESS_TIME    } ,
    { IDC_STATIC_AGGR_DATE ,       IDC_TXT_AGGR_DATE       } ,
    { IDC_STATIC_AGGR_TIME ,       IDC_TXT_AGGR_TIME       } ,
};
int numAggregateOrderSummaryTabControls = sizeof(aggregateOrderSummaryTabControls)/sizeof( TAB_CONTROL_FIELD_MAPPING ); 

const TAB_CONTROL_FIELD_MAPPING aggregateOrderSettlementTabControls[] = //IDD_AGGREGATE_HELPER_03 DIALOGEX Settlement 
{  
    { IDC_STATIC_GEN_20 ,             IDC_CMB_STTL_LOCATION      } ,
    { IDC_STATIC_GEN_24 ,             IDC_CMB_STTL_INST_CODE     } ,
    { IDC_STATIC_GEN_23 ,             IDC_CMB_CLEAN_METHOD       } ,    
    { IDC_STATIC_GEN_25 ,             IDC_EDT_DELIVERY_TO        } ,
    { IDC_STATIC_GEN_27 ,             IDC_EDT_FOR_ACCT           } ,
    { IDC_STATIC_GEN_29 ,             IDC_EDT_IN_FAVOR_OF        } ,
    { IDC_STATIC_GEN_22,              IDC_EDT_STTL_ACCT          } ,
    { IDC_STC_LBL_INTERMEDIARY_BANK , IDC_EDT_INTERMEDIARY_BANK  } ,
    { IDC_STC_LBL_PREF_CASH_MSG_TYPE ,IDC_EDT_PREF_CASH_MSG_TYPE } ,
    { IDC_STC_LBL_RECEIVING_BANK ,    IDC_EDT_RECEIVING_BANK     } ,
    { IDC_STC_LBL_BENFICIARY ,        IDC_EDT_BENFICIARY         } ,
    { IDC_STC_LBL_SPECIAL_INST ,      IDC_EDT_SPECIAL_INST       } ,
    { IDC_STC_LBL_INT_SETL_ACC,       IDC_EDT_INT_SETL_ACC       } ,    
};
int numAggregateOrderSettlementTabControls = sizeof(aggregateOrderSettlementTabControls) /sizeof( TAB_CONTROL_FIELD_MAPPING ); 

class LVAggregatedOrderData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVAggregatedOrderData() {}

   DString m_dstrOmnibusId, m_dstrBrokerName, m_dstrFundCode, m_dstrClassCode;
   DString m_dstrWKN, m_dstrISIN,m_dstrFundName, m_dstrTransType, m_dstrTradeDate, m_dstrAggregateOption;
	DString m_dstrOrdStatus, m_dstrGroupCode, m_dstrRoutingType;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {

      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::OmnibusID, m_dstrOmnibusId );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::BrokerName, m_dstrBrokerName );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundCode, m_dstrFundCode );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ClassCode, m_dstrClassCode );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundWKN, m_dstrWKN );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundISIN, m_dstrISIN );
		pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundName, m_dstrFundName );
	   pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TransType, m_dstrTransType );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TradeDate, m_dstrTradeDate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::AggregateOption, m_dstrAggregateOption);
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::OrdStatus, m_dstrOrdStatus );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GroupCode, m_dstrGroupCode );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::RoutingType, m_dstrRoutingType );
   }
};

class LVAggregatedOrderAdapter : public IFDSListCtrlAdapter< LVAggregatedOrderData >
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
      } else if( *pFieldId == ifds::OmnibusID ) {
			// Aggregated Order Reference # column, should be sorted as integer
			int iInvSummId1 = pData1->m_dstrOmnibusId.asInteger();
         int iInvSummId2 = pData2->m_dstrOmnibusId.asInteger();
         if ( iInvSummId1 > iInvSummId2 )
				result = 1;
			else if ( iInvSummId1 < iInvSummId2 )
				result = -1;
         //result = i_strcmp( pData1->m_dstrOmnibusId.c_str(), pData2->m_dstrOmnibusId.c_str() );
      } else if( *pFieldId == ifds::BrokerName ) {
         result = i_strcmp( pData1->m_dstrBrokerName.c_str(), pData2->m_dstrBrokerName.c_str() );
		 } else if( *pFieldId == ifds::FundCode ) {
         result = i_strcmp( pData1->m_dstrFundCode.c_str(), pData2->m_dstrFundCode.c_str() );
      } else if( *pFieldId == ifds::ClassCode ) {
         result = i_strcmp( pData1->m_dstrClassCode.c_str(), pData2->m_dstrClassCode.c_str() );
		 } else if( *pFieldId == ifds::FundWKN ) {
         result = i_strcmp( pData1->m_dstrWKN.c_str(), pData2->m_dstrWKN.c_str() );
      } else if( *pFieldId == ifds::FundISIN ) {
         result = i_strcmp( pData1->m_dstrISIN.c_str(), pData2->m_dstrISIN.c_str() );
		} else if( *pFieldId == ifds::FundName) {
         result = i_strcmp( pData1->m_dstrFundName.c_str(), pData2->m_dstrFundName.c_str() );
		} else if( *pFieldId == ifds::TransType ) {
         result = i_strcmp( pData1->m_dstrTransType.c_str(), pData2->m_dstrTransType.c_str() );
      } else if( *pFieldId == ifds::TradeDate ) {
			if ( DSTCommonFunctions::CompareDates( pData1->m_dstrTradeDate.c_str(), pData2->m_dstrTradeDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = -1;
			else if ( DSTCommonFunctions::CompareDates( pData2->m_dstrTradeDate.c_str(), pData1->m_dstrTradeDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = 1;
		} else if( *pFieldId == ifds::AggregateOption ) {
         result = i_strcmp( pData1->m_dstrAggregateOption.c_str(), pData2->m_dstrAggregateOption.c_str() );
		} else if( *pFieldId == ifds::TransType ) {
         result = i_strcmp( pData1->m_dstrTransType.c_str(), pData2->m_dstrTransType.c_str() );
		} else if( *pFieldId == ifds::OrdStatus ) {
         result = i_strcmp( pData1->m_dstrOrdStatus.c_str(), pData2->m_dstrOrdStatus.c_str() );
		} else if( *pFieldId == ifds::GroupCode ) {
         result = i_strcmp( pData1->m_dstrGroupCode.c_str(), pData2->m_dstrGroupCode.c_str() );
		} else if( *pFieldId == ifds::RoutingType ) {
         result = i_strcmp( pData1->m_dstrRoutingType.c_str(), pData2->m_dstrRoutingType.c_str() );
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
         } else if( *pFieldId == ifds::OmnibusID ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrOmnibusId.c_str();
         } else if( *pFieldId == ifds::BrokerName ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrBrokerName.c_str();
         } else if( *pFieldId == ifds::FundCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFundCode.c_str();
         } else if( *pFieldId == ifds::ClassCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrClassCode.c_str();
         } else if( *pFieldId == ifds::FundWKN ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrWKN.c_str();
         } else if( *pFieldId == ifds::FundISIN ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrISIN.c_str();
			} else if( *pFieldId == ifds::FundName ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFundName.c_str();
			} else if( *pFieldId == ifds::TransType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTransType.c_str();
         } else if( *pFieldId == ifds::TradeDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTradeDate.c_str();
         } else if( *pFieldId == ifds::AggregateOption ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrAggregateOption.c_str();
         } else if( *pFieldId == ifds::OrdStatus ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrOrdStatus.c_str();
         } else if( *pFieldId == ifds::GroupCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrGroupCode.c_str();
         } else if( *pFieldId == ifds::RoutingType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrRoutingType.c_str();
         } 

         return( 1 );
      }
      return( 0 );
   }
};

//******************************************************************************
// Constructor
//******************************************************************************
AggregatedOrderDlg::AggregatedOrderDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( AggregatedOrderDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
DisableMsg( NULL_STRING ),
isFromMessage(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   //{{AFX_DATA_INIT( AggregatedOrderDlg )
	m_StrNumberOfTrade = I_("");
   //}}AFX_DATA_INIT

   
}

//******************************************************************************
// Destructor
//******************************************************************************
AggregatedOrderDlg::~AggregatedOrderDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void AggregatedOrderDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( AggregatedOrderDlg ) 
	 DDX_Text(pDX, IDC_TXT_NUMBER_OF_TRADE,  m_StrNumberOfTrade);
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( AggregatedOrderDlg, BaseMainDlg )
//{{AFX_MSG_MAP( AggregatedOrderDlg )
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
ON_BN_CLICKED(IDC_BTN_TRADE_MODIFY, OnBtnTradeModify)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_MESSAGE, OnBtnMessage)
ON_BN_CLICKED(IDC_BTN_AGGR_HIST, OnBtnHistorical)
ON_BN_CLICKED(IDC_BTN_MORE_PND_TRD, OnBtnMorePendingTrade)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************

BOOL AggregatedOrderDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
//******************************************************************************
void AggregatedOrderDlg::OnPostInitDialog()
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   addControls( );
   InitialButtons();

   // Enable/Disable Msg Button
   GetDlgItem( IDC_BTN_MESSAGE )->EnableWindow( DisableMsg.empty() );
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY AggregatedOrderDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   // Get Parameters
   getParameter( I_("DisableMsg"), DisableMsg );
	if (!DisableMsg.empty())
	{
		getParameter(AGGREGATE::AGGR_ORDER_NUMBER, _dstrAggrOrderNum);
		isFromMessage = true;
	}

   return ( NO_CONDITION );
}

//******************************************************************************
// This method sets up the custom controls to the correct data set.
//******************************************************************************
void AggregatedOrderDlg::addControls( )
{

   IFDSListCtrl* pCtrl = 
      new IFDSAdaptedListCtrl< LVAggregatedOrderAdapter >
         ( this, CLASSNAME, 
			  IDC_LV_AGGREGATE_ORDER_LIST,
			  0, /*LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE*/0, true, true );
  
   AddIFDSListControl( pCtrl, 
                       LV_AGGREGATE_ORDER_LIST, 
                       IFASTBP_PROC::AGGREGATED_ORDER_LIST,
                       ifds::AggregatedOrderListHeading );
	

	AddListControl( CLASSNAME, 
                   IDC_LV_PENDING_TRADE_LIST,
                   LV_PENDING_TRADE_LIST,
                   ifds::AggrOrderPendingTradeListHeading,
						 IFASTBP_PROC::PENDING_TRADE, IDC_LV_AGGREGATE_ORDER_LIST, true, LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE );


	if ( NULL != pCtrl )		
		pCtrl->SortOnColumn( 1 );
  
   for( int i = 0 ; i < numScreenControls ; i++ )
   {
     AddControl( controlFieldMapping[i].eType ,
                 controlFieldMapping[i].controlID,
                 controlFieldMapping[i].idContainer,
                 controlFieldMapping[i].idField,
                 controlFieldMapping[i].flags,
                 (UINT)controlFieldMapping[i].controlGroupID );
   }
	( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_PRICE ) ) )->SetAllowedChars(I_(".0123456789"));
	( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_COMM_RATE ) ) )->SetAllowedChars(I_(".0123456789"));
	( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ORIG_AMOUNT ) ) )->SetAllowedChars(I_(".0123456789"));
	( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_EXT_AMOUNT ) ) )->SetAllowedChars(I_(".0123456789"));
	( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_STTL_AMOUNT ) ) )->SetAllowedChars(I_(".0123456789"));
	( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_REBATE ) ) )->SetAllowedChars(I_(".0123456789"));
    ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_PREF_CASH_MSG_TYPE ) ) )->SetMaxCharNum(25);
   // ( dynamic_cast < DSTEdit* > ( GetControl( IDC_TXT_INT_SETL_ACC ) ) )->SetMaxCharNum(25); //MAX_CHAR_COUNT_DEFAULT
    ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BENFICIARY ) ) )->SetMaxCharNum( MAX_CHAR_COUNT_DEFAULT );
    ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_RECEIVING_BANK ) ) )->SetMaxCharNum( MAX_CHAR_COUNT_DEFAULT );
    ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_SPECIAL_INST ) ) )->SetMaxCharNum( MAX_CHAR_COUNT_DEFAULT );
    ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_INTERMEDIARY_BANK ) ) )->SetMaxCharNum( MAX_CHAR_COUNT_DEFAULT );

    //TAB Control related activities.
    registerTabControls();    
    ShowTabCtrl (IDC_TAB_AGGREGATE_INFO, true);
    LoadTabControl (IDC_TAB_AGGREGATE_INFO);

	doRefresh(this, NULL_STRING);
	
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool AggregatedOrderDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
   int iItemNumber = 0;
   iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
   if( iItemNumber != 0 )
   {
      DString dstrAggrOrderNum, dstrStatus;
      getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OmnibusID, dstrAggrOrderNum, false );
      setParameter( AGGREGATE::AGGR_ORDER_NUMBER, dstrAggrOrderNum );
      getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OrdStatus, dstrStatus, false );
      StatusRelatedChanges( dstrStatus );
      GetDlgItem( IDC_BTN_REFRESH )->EnableWindow( dstrStatus == PRICE_LOADED );

      DString aggregateOrderKey;

      aggregateOrderKey = getParent ()-> getCurrentListItemKey (this, IFASTBP_PROC::AGGREGATED_ORDER_LIST);

      LoadListControl (IDC_LV_AGGREGATE_ORDER_LIST, &aggregateOrderKey);
      LoadListControl (IDC_LV_PENDING_TRADE_LIST);
      int iNumOfItem = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::PENDING_TRADE );
      DString str;
      convertIntToString( iNumOfItem, str );
      m_StrNumberOfTrade = str.c_str();

      GetDlgItem(IDC_TXT_NUMBER_OF_TRADE)->SetWindowText( m_StrNumberOfTrade );

      ConnectControlsToData ();  
      //LoadControls(); 
      ShowTabCtrl (IDC_TAB_AGGREGATE_INFO, true);
      LoadTabControl (IDC_TAB_AGGREGATE_INFO);
      EnableUpdateingControls( false );
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST ) );
      GetDlgItem( IDC_BTN_MORE_PND_TRD )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::PENDING_TRADE ) );
//    GetDlgItem( IDOK )->EnableWindow( true );
   }
   else
   {
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( false );
      GetDlgItem( IDC_BTN_MORE_PND_TRD )->EnableWindow( false );
      GetDlgItem( IDC_BTN_RESET )->EnableWindow( false );
      GetDlgItem( IDC_BTN_TRADE_MODIFY )->EnableWindow( false );
   }

   return(true);
}

//**********************************************************************************
void AggregatedOrderDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::AGGREGATED_ORDER_LIST );
}

//******************************************************************************
void AggregatedOrderDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnReset" ) );
	const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
   ResetListItem( IDC_LV_AGGREGATE_ORDER_LIST);
	LoadListControl ( IDC_LV_AGGREGATE_ORDER_LIST);
	if( *crtKey != NULL_STRING )
   {
       GetList( IDC_LV_AGGREGATE_ORDER_LIST)->SetSelection( crtKey );
   }
   //GetList( IDC_LV_AGGREGATE_ORDER_LIST)->SetFocus();
}

//*************************************************************************
void AggregatedOrderDlg::ControlUpdated( UINT controlID, 
															 const DString &strValue )
{   
   switch( controlID )
   {		
		case IDC_CMB_STATUS:
			{							
				StatusRelatedChanges(strValue);
				LoadControl( IDC_EDT_ORIG_AMOUNT );
				LoadControl( IDC_EDT_STTL_AMOUNT );
			}
			break;					
		case IDC_CMB_STTL_INST_CODE:
			//LoadControl( IDC_EDT_DELIVERY_TO );
			//LoadControl( IDC_EDT_FOR_ACCT );
			//LoadControl( IDC_EDT_IN_FAVOR_OF );
			break;
		case IDC_DTP_BRK_STTLDATE:
		case IDC_CMB_PRICE_TYPE:
		case IDC_EDT_PRICE:
		case IDC_EDT_COMM_RATE:
		case IDC_EDT_EXT_AMOUNT:
		case IDC_EDT_REBATE:
		case IDC_EDT_ORIG_AMOUNT:
			{
				LoadControl( IDC_EDT_STTL_AMOUNT );
			}
		case IDC_EDT_STTL_AMOUNT:
			{		
				GetDlgItem( IDC_BTN_REFRESH )->EnableWindow (true);
				GetDlgItem( IDOK )->EnableWindow( false );
			}
			break;
		case IDC_BTN_REFRESH:
			{
            //GetDlgItem (IDC_BTN_TRADE_MODIFY)->EnableWindow (true);
            break;
			}
		case IDC_DTP_TRADE_DATE:
         {
				//GetDlgItem (IDC_BTN_TRADE_MODIFY)->EnableWindow (true);
            break;
         }
		default:
			break;
	}
}

//******************************************************************************

void AggregatedOrderDlg::DoListItemChanged( UINT listControlID,
                                             const DString &strKey,
                                             bool bIsNewItem,
                                             bool bIsDummyItem )
{
	DString dstrStatus, dstrAggrOrderNum, dstrWKN, dstrISIN;
   if( listControlID == IDC_LV_AGGREGATE_ORDER_LIST)
   {
		const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
		getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OrdStatus, dstrStatus, false );
      StatusRelatedChanges( dstrStatus );
		//GetDlgItem( IDC_BTN_REFRESH )->EnableWindow( dstrStatus == PRICE_LOADED );
		

		DString dstRecalculate;
		getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::Recalculate, dstRecalculate, false );
		GetDlgItem( IDC_BTN_REFRESH )->EnableWindow( dstRecalculate == YES ); 
		//GetDlgItem( IDOK )->EnableWindow(dstAggrOrdRefreshed == YES );

		DString dstAggrOrdRefreshed;
		getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::AggrOrdRefreshed, dstAggrOrdRefreshed, false );
		GetDlgItem( IDC_BTN_RESET )->EnableWindow( dstAggrOrdRefreshed == NO ); 

		getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OmnibusID, dstrAggrOrderNum, false );
		setParameter( AGGREGATE::AGGR_ORDER_NUMBER, dstrAggrOrderNum );
 		
		DString str;
		int iNumOfItem = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::PENDING_TRADE );
		convertIntToString( iNumOfItem, str );
		m_StrNumberOfTrade = str.c_str();
		GetDlgItem(IDC_TXT_NUMBER_OF_TRADE)->SetWindowText( m_StrNumberOfTrade );
		if(iNumOfItem > 0 )
			LoadListControl ( IDC_LV_PENDING_TRADE_LIST );

      GetDlgItem( IDC_BTN_MORE_PND_TRD )->EnableWindow( 
         getParent()->doMoreRecordsExist( this, IFASTBP_PROC::PENDING_TRADE ) );

	}
	else if( listControlID == IDC_LV_PENDING_TRADE_LIST)
	{
		getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OmnibusID, dstrAggrOrderNum, false );
		setParameter( AGGREGATE::AGGR_ORDER_NUMBER, dstrAggrOrderNum );
	}
}

//******************************************************************************
void AggregatedOrderDlg::OnBtnMore  ( )
{
   TRACE_METHOD( CLASSNAME, ONBTNMORE );

   CWaitCursor wait; 
   SetMessageStatusBar( TXT_LOAD_AGGREGATED_ORDER );

   static int cursel;

   cursel = GetList( IDC_LV_AGGREGATE_ORDER_LIST)->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST );

	DString dstrAggrOrderNum;
	getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OmnibusID, dstrAggrOrderNum, false );
	setParameter( AGGREGATE::AGGR_ORDER_NUMBER, dstrAggrOrderNum );

   if( getParent()->performSearch( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {

      LoadListControl( IDC_LV_AGGREGATE_ORDER_LIST);
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_AGGREGATE_ORDER_LIST)->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST ) );
   GetDlgItem( IDC_BTN_MORE_PND_TRD )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::PENDING_TRADE ) );

   GetList( IDC_LV_AGGREGATE_ORDER_LIST)->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************
void AggregatedOrderDlg::OnBtnMorePendingTrade ()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMorePendingTrade") );

   int curPndTrdSel = GetList(IDC_LV_PENDING_TRADE_LIST)->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::PENDING_TRADE );

   if( getParent()->performSearch( this, IFASTBP_PROC::PENDING_TRADE, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      int iNumOfItem = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::PENDING_TRADE );
      DString str;
      convertIntToString( iNumOfItem, str );
      m_StrNumberOfTrade = str.c_str();

      GetDlgItem(IDC_TXT_NUMBER_OF_TRADE)->SetWindowText( m_StrNumberOfTrade );

      LoadListControl( IDC_LV_PENDING_TRADE_LIST);

      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_PENDING_TRADE_LIST)->SetSelection( crtKey );
      }
   }

   GetDlgItem( IDC_BTN_MORE_PND_TRD )->EnableWindow( 
      getParent()->doMoreRecordsExist( this, IFASTBP_PROC::PENDING_TRADE ) );

}

//******************************************************************************

void AggregatedOrderDlg::OnBtnRefresh  ( )
{
   TRACE_METHOD( CLASSNAME, ONBTNREFRESH );
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNREFRESH );
	
	DString dstrAggrOrderNum, dstrRecalculate, dstrAllowEnableOk, dstrWarnMsgCode;
	getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OmnibusID, dstrAggrOrderNum, false );
	setParameter( AGGREGATE::AGGR_ORDER_NUMBER, dstrAggrOrderNum );

	bool bRet = getParent()->send( this,I_( "CallView324" ) );
	SEVERITY sevRte =  GETCURRENTHIGHESTSEVERITY();
	//if ( getParent()->send( this,I_( "CallView324" ) ) == false )
	
	// Incident #288887 -- If wive 324 returns WarnMsgCode is not 0, display the warning message
	getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::WarnMsgCode, dstrWarnMsgCode, false );
	
	int iWarnMsgCode = dstrWarnMsgCode.asInteger();
	if ( iWarnMsgCode == 578 )
	{
		AfxMessageBox( TXT_WARNING_EXCEEDED_LIMIT );
	}
	else if ( iWarnMsgCode == 655 )
	{
		AfxMessageBox( TXT_WARNING_LOSS_SITUATION );
	}
	if ( bRet == false )
	{
		ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY() );
	}

	if ( bRet == true || ( bRet == false && sevRte == WARNING ) )
	{
		LoadListControl( IDC_LV_PENDING_TRADE_LIST );
		GetDlgItem( IDC_BTN_REFRESH )->EnableWindow( false );
		getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::AllowEnableOk, dstrAllowEnableOk, false );
		GetDlgItem( IDOK )->EnableWindow( dstrAllowEnableOk == YES );
//      GetDlgItem (IDC_BTN_TRADE_MODIFY)->EnableWindow (true);
      GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);
		GetDlgItem(IDCANCEL)->EnableWindow(false);
	}
}

//******************************************************************************

void AggregatedOrderDlg::StatusRelatedChanges( const DString str )
{
	DString dstrAllowEnableOk;

	getParent()->getField (this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::AllowEnableOk, dstrAllowEnableOk, false);
	GetDlgItem (IDOK)->EnableWindow (dstrAllowEnableOk == YES);
   GetDlgItem (IDC_BTN_REFRESH)->EnableWindow (false);
	if (str == AGGREGATED)
	{
		GetDlgItem (IDC_BTN_TRADE_MODIFY )->EnableWindow (false);
	}
   else if (str == ORDER_SENT || str == DONOT_SEND)
	{      
		GetDlgItem (IDC_BTN_TRADE_MODIFY)->EnableWindow (false);
	}
	else if (str == PRICE_LOADED)
	{
		DString dstrAggrOrderNum;

      getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OmnibusID, dstrAggrOrderNum, false);
		setParameter (AGGREGATE::AGGR_ORDER_NUMBER, dstrAggrOrderNum);
      GetDlgItem (IDC_BTN_TRADE_MODIFY)->EnableWindow (true);
	  GetDlgItem( IDC_BTN_REFRESH )->EnableWindow (true);
	  GetDlgItem( IDOK )->EnableWindow( false );
   }
	else if (str == PRICE_POSTED)
	{
		GetDlgItem (IDC_BTN_TRADE_MODIFY)->EnableWindow (false);
	}
	DString dstrAmountType,dstrStatus;
	getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OrdStatus, dstrStatus, false );
    getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::AmountType, dstrAmountType, false);
	  
	EnableControl( IDC_EDT_ORIG_AMOUNT, (dstrAmountType==I_("D") && dstrStatus==PRICE_LOADED));
}

//******************************************************************************
void AggregatedOrderDlg::EnableUpdateingControls( bool bFlag )
{
	 EnableControl( IDC_EDT_ORIG_AMTTYPE, bFlag );
	 //EnableControl( IDC_EDT_ORIG_AMOUNT, bFlag );
    EnableControl( IDC_EDT_ROUT_REF_NO, bFlag );
	 EnableControl( IDC_EDT_STTL_AMTTYPE, bFlag );
    EnableControl( IDC_EDT_BENEFIT, bFlag );
	 EnableControl( IDC_EDT_CAL_OFFER_PRICE, bFlag );
    EnableControl( IDC_EDT_CALCULATE_NAV, bFlag );
	 //EnableControl( IDC_EDT_STTL_ACCT, bFlag ); 
}

//******************************************************************************
bool AggregatedOrderDlg::hasLossTrade()
{
	 //return( getParent()->CheckPendingTrade() );
	return false;
}

//******************************************************************************
void AggregatedOrderDlg::OnBtnTradeModify() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, 
                          CLASSNAME, 
                          I_("OnBtnTradeModify()"));
   CWaitCursor wait;
   DString aggregateOrderKey,
      tradeDate;

   aggregateOrderKey = getParent ()-> getCurrentListItemKey (this,IFASTBP_PROC::AGGREGATED_ORDER_LIST);
   getParent()->getField (this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::TradeDate, tradeDate, false);
   try
   {
      SetMessageStatusBar (TXT_LOAD_TRADES);
      setParameter (MFCAN_IP_PARAM::CALLER, I_("ModifyPendingTradesWithLoss"));
      setParameter (MFCAN_IP_PARAM::LIST_KEY, aggregateOrderKey);
      setParameter (MFCAN_IP_PARAM::TRADE_DATE, tradeDate);
		switch ( invokeCommand ( getParent(), 
                               CMD_BPROC_TRADES,
                               PROC_NO_TYPE, 
                               isModal(),
                               NULL))
      {
         case CMD_MODELESS_INPROCESS:
         case CMD_OK:
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch ( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   SetMessageStatusBar (NULL_STRING);
	getParent()->send(this, I_("ModifyTrade"));
   GetDlgItem(IDCANCEL)->EnableWindow(false);
}

//******************************************************************************
void AggregatedOrderDlg::InitialButtons()
{
   GetDlgItem( IDC_BTN_REFRESH )->EnableWindow( false );
   GetDlgItem( IDC_BTN_MESSAGE )->EnableWindow( TRUE );
}

//******************************************************************************

void AggregatedOrderDlg::OnBtnMessage()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnMessage" ) );

	GetDlgItem(IDC_BTN_MESSAGE)->SetFocus();
	CWaitCursor wait;

   // Set OmnibusID (Aggregate Order Number)
   DString OmnibusID;
   getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OmnibusID, OmnibusID, false );
   setParameter( MFCAN_IP_PARAM::AGGREGATEDORDER, OmnibusID );

   // Disable Trade Button
   setParameter( I_("DisableAggrOrder"), I_("DisableAggrOrder") );

   // Set Message Type
   setParameter( MFCAN_IP_PARAM::SEARCH_TYPE, I_("AggrOrdRefNum") );

   try
   {
      bool bModal = true;
      E_COMMANDRETURN eRtn = CMD_OK;
      SetMessageStatusBar( IDS_LOADING_MSG );
      eRtn = invokeCommand( getParent(), CMD_BPROC_MSG, PROC_NO_TYPE, bModal, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   SetMessageStatusBar( NULL_STRING );
}

//*********************************************************************************
bool AggregatedOrderDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
	if (!isFromMessage)
   {
		return true;
   }
	else
	{
		bool bRet = false;

      if (lSubstituteId == ifds::AggregatedOrderListHeading.getId())
		{
			DString dstrOmnibusID;
			
         getParent()->getField( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST, ifds::OmnibusID, dstrOmnibusID, false);	  
			if (dstrOmnibusID == _dstrAggrOrderNum)
         {
				bRet = true;
         }
		}
      else
      {
         bRet = true;
      }
		return bRet;
	}
}

//******************************************************************************
void AggregatedOrderDlg::OnBtnHistorical() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical") );   
   CWaitCursor wait;   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::AGGREGATED_ORDER_LIST);
}

//******************************************************************************
void AggregatedOrderDlg::registerTabControls () 
{
   TRACE_METHOD( CLASSNAME, I_("registerTabControls") );

   DSTTabCtrl* pTabCtrl = AddTabControl(CLASSNAME, IDC_TAB_AGGREGATE_INFO, I_("AggregateOrderTab"));
   assert (pTabCtrl);
   if (pTabCtrl)
   {
     pTabCtrl->SetMinTabWidth (50);
     pTabCtrl->AddTab(TXT_TAB_AGGR_DETAILS);     
     pTabCtrl->AddTab(TXT_TAB_AGGR_SETTLEMENT_INFO);
     pTabCtrl->AddTab(TXT_TAB_AGGR_SUMMARY);

     //Details tab 
     for(unsigned int i=0; i<numAggregateOrderDetailsTabControls; i++)
      {
        //Register the static controls
         if( NO_CONTROL != aggregateOrderDetailsTabControls[i].STATIC_LABEL )
         {
            AddControl(CTRL_STATIC, aggregateOrderDetailsTabControls[i].STATIC_LABEL, CTRLFLAG_GUI_FIELD );
            pTabCtrl->registerControl(aggregateOrderDetailsTabControls[i].STATIC_LABEL, TXT_TAB_AGGR_DETAILS ); 
         }
        // Register the edit controls
         if( NO_CONTROL != aggregateOrderDetailsTabControls[i].EDIT_CONTROL )
             pTabCtrl->registerControl(aggregateOrderDetailsTabControls[i].EDIT_CONTROL, TXT_TAB_AGGR_DETAILS ); 
      }

     //Summary tab
     for(unsigned int i=0; i<numAggregateOrderSummaryTabControls; i++)
      {
        //Register the static controls
         if( NO_CONTROL != aggregateOrderSummaryTabControls[i].STATIC_LABEL )
         {
            AddControl(CTRL_STATIC, aggregateOrderSummaryTabControls[i].STATIC_LABEL, CTRLFLAG_GUI_FIELD);
            pTabCtrl->registerControl(aggregateOrderSummaryTabControls[i].STATIC_LABEL, TXT_TAB_AGGR_SUMMARY ); 
         }
        // Register the edit controls
         if( NO_CONTROL != aggregateOrderSummaryTabControls[i].EDIT_CONTROL )
             pTabCtrl->registerControl(aggregateOrderSummaryTabControls[i].EDIT_CONTROL, TXT_TAB_AGGR_SUMMARY );          
      }

    //Settlement tab
     for(unsigned int i=0; i<numAggregateOrderSettlementTabControls; i++)
      {
         //Register the static controls
         if( NO_CONTROL != aggregateOrderSettlementTabControls[i].STATIC_LABEL )
         {
            AddControl(CTRL_STATIC, aggregateOrderSettlementTabControls[i].STATIC_LABEL, CTRLFLAG_GUI_FIELD );
            pTabCtrl->registerControl(aggregateOrderSettlementTabControls[i].STATIC_LABEL, TXT_TAB_AGGR_SETTLEMENT_INFO ); 
         }
       // Register the edit controls
       if( NO_CONTROL != aggregateOrderSettlementTabControls[i].EDIT_CONTROL )
           pTabCtrl->registerControl(aggregateOrderSettlementTabControls[i].EDIT_CONTROL, TXT_TAB_AGGR_SETTLEMENT_INFO ); 
      }

   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AggregatedOrderDlg.cpp-arc  $
// 
//    Rev 1.48   Jul 27 2011 10:59:30   wp040027
// PET P0186065 - Aggregated Amount Orders via Swift- Enable 'Orig Amt' field to allow user to enter broker confirmed amount
// 
//    Rev 1.47   Mar 05 2009 00:57:48   dchatcha
// IN 1395049 - Not returning all the pending trades, introduced 'More' button for pending trade part of Aggregated order screen.
// 
//    Rev 1.46   Jan 12 2006 15:40:40   zhengcon
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Aggregate Order
// 
//    Rev 1.45   Oct 05 2005 10:37:24   AGUILAAM
// PET1286_FN02_Verification of Aggregated Order Fund Price
// 
//    Rev 1.44   Sep 22 2005 19:18:06   popescu
// Incident #410678 - The list of trades part of an aggregated order are properly displayed, if user inquires for aggregated order, going through Desktop > Menu > Interface> Message 
// 
//    Rev 1.43   Sep 15 2005 15:10:20   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.42   Aug 18 2005 16:48:38   fengyong
// Incident 379172 - call view 324 calculate settleAmt/Units
// 
//    Rev 1.41   Jul 28 2005 14:26:54   ZHANGCEL
// Incident #361305 -- Fix issue of the fund cureency displaying 
// 
//    Rev 1.40   Jun 16 2005 20:18:36   popescu
// Incident# 328435 - enable trade modify button in any circumstances for an aggregated order with status price loaded
// 
//    Rev 1.39   May 30 2005 22:19:58   popescu
// Incident #301175 - subsequent fix - enable trade modify buttomn when an error on the underlying trades of an aggregated order occurs when user modifies the trade date
// 
//    Rev 1.38   May 27 2005 17:31:40   Fengyong
// #Incident 317930 - Sync up, refresh after back from modify pending trade
// 
//    Rev 1.37   May 27 2005 15:47:36   ZHANGCEL
// Incident #297240 --Add logic to filter the list to fix the problem launching AggregatedOrderDlg from Message screen
// 
//    Rev 1.36   May 12 2005 17:10:10   popescu
// Incident# 301175 - enable the TradeModify button if there are errors on pending trades
// 
//    Rev 1.35   May 09 2005 16:00:26   Fengyong
// #Incident 288887 - new issue about internal error when changing item.
// 
//    Rev 1.34   May 04 2005 16:59:26   hernando
// Incident 303637 - Added parameter, DisableMsg.
// 
//    Rev 1.33   Apr 27 2005 11:29:30   ZHANGCEL
// Incident #288887 -- Bug fix for the warning return from view324 issue
// 
//    Rev 1.32   Apr 18 2005 10:34:16   popescu
// Incident #285862, fixed validation issue with the trade date on the aggregated order screen
// 
//    Rev 1.31   Apr 08 2005 16:26:06   ZHANGCEL
// Incident #280871 -- Solve the sort problem 
// 
//    Rev 1.30   Apr 07 2005 17:20:28   ZHANGCEL
// Incident # 280871 -- The order of Aggr.Ref. # is sorted by integer instead of text
// 
//    Rev 1.29   Mar 10 2005 10:00:58   popescu
// PET 11190/04, added the TradeDate as control to the dialog
// 
//    Rev 1.28   Mar 09 2005 11:55:12   hernando
// PET1117 FN66-68 - Added MsgButton to Aggregate Order Dialog.
// 
//    Rev 1.27   Mar 07 2005 11:09:40   ZHANGCEL
// Incident #258348 -- Refresh button should be disable when change variance severty from ERROR to WARNING
// 
//    Rev 1.26   Mar 03 2005 16:13:06   ZHANGCEL
// Incident #248320 -- After <Modify Trade> force to submit changes to backend and disable <Cancel> botton
// 
//    Rev 1.23   Feb 08 2005 18:36:32   zhangcel
// PTS 10038581 (Magic order #18337 ) -- Fix <OK>, <Cancel>,<Reset> button issue.
// 
//    Rev 1.22   Jan 31 2005 18:18:34   zhangcel
// PTS ticket 10038394 -- <Ok> button related changes
// 
//    Rev 1.21   Jan 28 2005 15:35:38   zhangcel
// PTS Ticket 10038394 -- Added logic to restrict numeric value
// 
//    Rev 1.20   Jan 28 2005 13:51:40   zhangcel
// PTS ticket 10038243 -- Make <Ok> botton to be disable when <Refresh> button is enable.
// 
//    Rev 1.19   Jan 27 2005 13:30:58   zhangcel
// PTS ticket 10038328 -- Show error message "Amount exceed variance limit" when user hip <Refresh> button
// 
//    Rev 1.18   Jan 24 2005 15:26:28   zhangcel
// PET ticket 10038135 -- Fix the crash issue regarding more, reset button
// 
//    Rev 1.17   Jan 24 2005 11:25:18   zhangcel
// PET ticket 10038135 -- Fix the more button and reset button issue
// 
//    Rev 1.16   Jan 14 2005 15:10:38   zhangcel
// PET1117-FN08 -- Fix currency display issue
// 
//    Rev 1.15   Dec 22 2004 17:12:40   zhangcel
// PET1117 - FN 08 -- Added logic to refresh Pending Trade list when user click ModifyTrade button
// 
//    Rev 1.14   Dec 17 2004 12:38:52   zhangcel
// PET 1117 FN 08 -- Add logic for the Amount Decimal issue
// 
//    Rev 1.13   Dec 15 2004 19:00:02   zhangcel
// PET 1117 FN 08 -- Bug fix for logic releated with  the Refresh button and Reset
// 
//    Rev 1.12   Dec 10 2004 16:50:12   zhangcel
// PET 1117 FN 08 -- Bug fix for displaying Number of Trades
// 
//    Rev 1.11   Dec 10 2004 14:55:34   zhangcel
// PET1117 -FN8  -- Bug fix for Pending list
// 
//    Rev 1.10   Dec 10 2004 13:56:20   zhangcel
// PET1117 FN8 -- Refresh PendingTrade list issue
// 
//    Rev 1.9   Dec 09 2004 22:31:08   popescu
// PET 11717/06, fees and mod pending trades
// 
//    Rev 1.8   Dec 09 2004 17:59:32   zhangcel
// PET1117 - FN 08 -- More logic for the OnBtnRefresh
// 
//    Rev 1.5   Dec 08 2004 17:50:20   popescu
// PET 1117/56, modify an aggregated order's pending trades list
// 
//    Rev 1.4   Dec 08 2004 12:45:48   zhangcel
// PET1117-FN08 More code for the enhancement
// 
//    Rev 1.3   Dec 07 2004 09:57:28   zhangcel
// PET1117 - FN8 -- more code populated
// 
//    Rev 1.2   Dec 06 2004 11:41:58   zhangcel
// PET1117 FN8 -- More code for the enhancement
// 
//    Rev 1.1   Dec 03 2004 17:09:50   zhangcel
// PET 1117 FN 08 -- More logic implemented
// 
//    Rev 1.0   Nov 26 2004 14:53:08   zhangcel
// Initial revision.
// 
*/


