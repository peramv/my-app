//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : SettlementProcess.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SettlementProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\addresslist.hpp>
#include <ifastcbo\bankinstructions.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\settlement.hpp>
#include "settlementprocess.hpp"
#include "settlementprocessincludes.h"
#include <ifastcbo\settlementtrade.hpp>
#include <ifastcbo\settlementtotallist.hpp>
#include <ifastcbo\settlementtradelist.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\mfaccount.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SETTLEMENT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SETTELEMENT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< SettlementProcess > processCreator( CMD_BPROC_SETTLEMENT );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace Settlement_Para
{
   const I_CHAR * const ACCOUNT_NUM          = I_( "AccountNum" );
   const I_CHAR * const ACCT_DETAIL          = I_( "Details" );
   const I_CHAR * const TRANS_HISTORY        = I_( "Transaction" );
   const I_CHAR * const FROM_SCR             = I_( "FromScr" );
   const I_CHAR * const ALL_TRADE            = I_( "AL" );
   const I_CHAR * const ACCOUNT              = I_( "AC" );
   const I_CHAR * const WIRE_ORDER           = I_( "WO" );
   const I_CHAR * const TRADE_DATE           = I_( "TD" );
   const I_CHAR * const SETTLE_DATE          = I_( "SD" );
   const I_CHAR * const SETTLE_CURRENCY      = I_( "CU" );
   const I_CHAR * const BROKER               = I_( "BR" );
   const I_CHAR * const FUND                 = I_( "FN" );
   const I_CHAR * const TRANS_NUMBER         = I_( "TN" );
   const I_CHAR * const ACCT_WIRENUMBER      = I_( "AW" );
   const I_CHAR * const DISPLAY_SETTLE_ONLY  = I_("DisplaySettleOnly");
   const I_CHAR * const DISPLAY_ALL          = I_("DisplayAll");
   const I_CHAR * const RESET_ITEM           = I_("Reset");
   const I_CHAR * const EXTERNAL_ID          = I_( "ET");
   const I_CHAR * const SETTLEALL            = I_("SettleAll");
   const I_CHAR * const FROM_AWD             = I_("FromAWD");
   const I_CHAR * const EPA_BROKER           = I_( "EP");
   const I_CHAR * const REGISTRATION_AGENT   = I_( "RA");

   //para for API
   const I_CHAR * const TRANSNUM             = I_("TransNum");
   const I_CHAR * const FUNDCODE             = I_("FundCode");
   const I_CHAR * const CLASSCODE            = I_("ClassCode");
   const I_CHAR * const TRANSTYPE            = I_("TransType");
   const I_CHAR * const SETTLEDATE           = I_("SettleDate");
   const I_CHAR * const TRADEDATE            = I_("TradeDate");
   const I_CHAR * const BROKERCODE           = I_("BrokerCode");
   const I_CHAR * const WIREORDNUM           = I_("WireOrdNum");
   const I_CHAR * const SINGLESEARCH         = I_( "TX" );
   const I_CHAR * const EXTERNALIDTYPE       = I_("ExternalIdType");
   const I_CHAR * const EXTERNALID           = I_("ExternalId");
}

namespace 
{
   const I_CHAR * const CLASSNAME      = I_( "SettlementProcess" );
   const I_CHAR * const YES            = I_("Y");
   const I_CHAR * const NO             = I_("N");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SettlePermCode;
   extern CLASS_IMPORT const BFTextFieldId PayInstructExists;
   extern CLASS_IMPORT const BFTextFieldId PayToEntity;
   extern CLASS_IMPORT const BFTextFieldId EPASettlementHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId FundIDList;
   extern CLASS_IMPORT const BFTextFieldId ExcludeStopSettle;
}
namespace FUND_ID_CODE
{
 const I_CHAR * const VALOREN	=	I_("Valoren");
 const I_CHAR * const TDCC		=	I_("TDCC");
 const I_CHAR * const CUSIP		=	I_("CUSIP");
}
//******************************************************************************
//              Public Methods
//******************************************************************************
//CP20030319SettlementProcess::SettlementProcess() : 
SettlementProcess::SettlementProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL ),_pSettlementTradeList(NULL)
, _pDummySettlementTradeList (NULL)
,_propSettlementListHeadSet  (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   addContainer( IFASTBP_PROC::SETTLEMENT_LIST,   true, BF::NullContainerId, true,I_("SettlementList") );
   addContainer( IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,   true,BF::NullContainerId,true,I_("SettlementTotal") );
   addContainer( IFASTBP_PROC::SETTLEMENT, false, BF::NullContainerId, true, I_("Settlement") );

   addSubstituteList(ifds::SettlementListHeadSet);
   // addSubstituteList(ifds::SettlementGridSet);
   addSubstituteList(ifds::SettlementTotalHeading );
   // addSubstituteList(ifds::TradingAttributesHeadingSet );
   addSubstituteList(ifds::EPASettlementHeadingSet);

   //SettlementSearch
   addFieldDetails( ifds::SearchType,           IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::WireOrdNum,           IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::TransNum,             IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::AccountNum,           IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::TransType,            IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::CompanyCode,          IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::BrokerCode,           IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::InterCode,            IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::FundCode,             IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::SettleCurrency,       IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::TradeDate,            IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::SettleDate,           IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::StartDate,            IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::EndDate,              IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::OverrideRepeats,      IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::VolSettleType,        IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::SettlePermCode,       IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::ExternalIdType,       IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::ExternalId,           IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::rxBatchName,          IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::RegAgentCode,         IFASTBP_PROC::SETTLEMENT );
   addFieldDetails( ifds::ExcludeStopSettle,    IFASTBP_PROC::SETTLEMENT);

   //Settlement List
   addFieldDetails( ifds::FundCode,             IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::ClassCode,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::CompanyCode,          IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::AccountNum,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::TransType,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::TransId,              IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::Indc,                 IFASTBP_PROC::SETTLEMENT_LIST );

   addFieldDetails( ifds::TradeDate,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::ValueDate,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::BrokerCode,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::BranchCode,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::SlsrepCode,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::SettleCurrency,       IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::GNSettle,             IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::TransDetlRid,         IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::Commission,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::AddrCode,             IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::Name1,                IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::Name2,                IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::AddrLine1,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::AddrLine2,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::AddrLine3,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::AddrLine4,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::AddrLine5,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::PostalCode,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::CountryCode,          IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::DistFee,              IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::Fee,                  IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::Units,                IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::AcctValue,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::Price,                IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::NetAmt,               IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::PayType,              IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::PayMethod,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::AltAccount,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::SettleDate,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::Commission2,          IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::OrderSource,          IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::SettleSource,         IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::SettleType,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::BankChrgs,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::DeliveryMethod,       IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::TransNum,             IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::Settled,              IFASTBP_PROC::SETTLEMENT_LIST );
   // addFieldDetails( ifds::GNSettle,				  SETTL_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::WireOrdNum,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::GrossAmt,             IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::SettledBy,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::SuppressCode,         IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::ACHProcessor,         IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::BatchName,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::ExchRate,             IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::ShrNum,               IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::ExpGNSettle,          IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::SettleAll,            IFASTBP_PROC::SETTLEMENT_LIST,SUBCLASS_PROCESS );
   addFieldDetails( SETTL_PROC::COPY_ADDRESS,   IFASTBP_PROC::SETTLEMENT_LIST,SUBCLASS_PROCESS );
   addFieldDetails( SETTL_PROC::PERMIT_INQ,     IFASTBP_PROC::SETTLEMENT,SUBCLASS_PROCESS );
   addFieldDetails( SETTL_PROC::PERMIT_UPDATE,  IFASTBP_PROC::SETTLEMENT,SUBCLASS_PROCESS );

   addFieldDetails( SETTL_PROC::SHR_NUM,        IFASTBP_PROC::SETTLEMENT_LIST,SUBCLASS_PROCESS );
   addFieldDetails( SETTL_PROC::ENTITY_NAME,    IFASTBP_PROC::SETTLEMENT_LIST,SUBCLASS_PROCESS );

   addFieldDetails( ifds::TradingAttributesHeadingSet, IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::SettlementGridSet,    IFASTBP_PROC::SETTLEMENT_LIST );

   addFieldDetails( ifds::PayInstructExists,    IFASTBP_PROC::SETTLEMENT_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::PayToEntity,          IFASTBP_PROC::SETTLEMENT_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::Currency,             IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( ifds::PurchaseTotal,        IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( ifds::RedemptTotal,         IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( ifds::ExchangeInTotal,      IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( ifds::ExchangeOutTotal,     IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( ifds::TransferInTotal,      IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( ifds::TransferOutTotal,     IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( ifds::NetTotal,             IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( ifds::CountTotal,           IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( ifds::CountTotalSettel,     IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );   
   addFieldDetails( ifds::PurchaseTotalSettle,  IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( ifds::RedemptionTotalSettle,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( ifds::NetTotalSettle,       IFASTBP_PROC::SETTLEMENT_TOTAL_LIST );
   addFieldDetails( SETTL_PROC::TOTAL_COUNT,    IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,SUBCLASS_PROCESS );
   addFieldDetails( SETTL_PROC::TOTAL_COUNT_SETTLE, IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,SUBCLASS_PROCESS );

   addFieldDetails( ifds::BankIdType,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::BankIdTypeCB,         IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::BankIdValueCB,        IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::BankIdValue,          IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::TransitNoCB,          IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::TransitNo,            IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::InstNameCB,           IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::InstName,             IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::BankAcctNum,          IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::BankAcctName,         IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::FundWKN,              IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::FundISIN,             IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::PymtRoutingMthd,		IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( SETTL_PROC::CORRESPONDENT_INFO,   IFASTBP_PROC::SETTLEMENT_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SettlementListHeadSet,     IFASTBP_PROC::SETTLEMENT_LIST, SUBCLASS_PROCESS );  
   addFieldDetails( ifds::Valoren,				 IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::TDCC,					 IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::CUSIP,				 IFASTBP_PROC::SETTLEMENT_LIST );
   addFieldDetails( ifds::PymtGen,                IFASTBP_PROC::SETTLEMENT_LIST);
   addFieldDetails( ifds::CashDate,             IFASTBP_PROC::SETTLEMENT_LIST );
}

//******************************************************************************
SettlementProcess::~SettlementProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _rpChildGI = NULL; 

   if (_pDummySettlementTradeList)
   {
	   delete _pDummySettlementTradeList;
	   _pDummySettlementTradeList = NULL;
   }
   if ( _propSettlementListHeadSet )
   {
      delete _propSettlementListHeadSet;
      _propSettlementListHeadSet = NULL;
   }
}

//******************************************************************************
SEVERITY SettlementProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );
   SEVERITY sevRtn=NO_CONDITION;

   getParameter( Settlement_Para::ACCOUNT_NUM, _dstrAccountNum );
   getParameter( Settlement_Para::FROM_SCR,  _dstrFromScr );

   Settlement* pSettlement = NULL;
   _dstrAccountNum.strip().stripLeading('0');
   const BFDataGroupId& idDataGroup = getDataGroupId();

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   sevRtn = dstcWorkSession->getSettlement(  pSettlement, idDataGroup   );
   if( sevRtn <= WARNING && pSettlement )
   {
      setContainer( IFASTBP_PROC::SETTLEMENT, pSettlement );

	  //Always default "Exclude Stop Settle" to YES.
	  pSettlement->setParameters(ifds::ExcludeStopSettle, YES, idDataGroup);
   }
   if( _dstrFromScr == Settlement_Para::ACCT_DETAIL || _dstrFromScr == Settlement_Para::TRANS_HISTORY ||
       _dstrFromScr == Settlement_Para::FROM_AWD)
   {
	    DString _dstrWireOrder;
	    DString dstrSearchType;

		if (_dstrFromScr == Settlement_Para::FROM_AWD)
		{
			 getParameter( Settlement_Para::WIREORDNUM,  _dstrWireOrder );	
			 if(_dstrWireOrder == NULL_STRING)
			 {
				 dstrSearchType = I_("AC");
				 pSettlement->setParameters(dstrSearchType,_dstrAccountNum, idDataGroup );
			 }
			 else
			 {
				 dstrSearchType = I_("AW");
				 pSettlement->setParameters(dstrSearchType,_dstrAccountNum, _dstrWireOrder, idDataGroup );
			 }
		}
		else
		{
			dstrSearchType = I_("AC");
	        pSettlement->setParameters(dstrSearchType,_dstrAccountNum, idDataGroup );
		}


      try
      {
         MFAccount* pMFAccount;
         dstcWorkSession->getMFAccount( idDataGroup,_dstrAccountNum,pMFAccount);
         pMFAccount->getField(ifds::ShrNum,_dstrShrNum, idDataGroup);
         _dstrShrNum.strip().stripLeading();
         dstcWorkSession->getFirstSequenced01AccountholderEntityName(idDataGroup,_dstrAccountNum,
                                                                     _dstrEntityName );             

      }
      catch( ConditionException &ce )
      {
         SETCONDITIONFROMEXCEPTION( ce );
      }
      catch( ... )
      {
         assert( 0 );
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                         CND::BP_ERR_UNKNOWN_EXCEPTION );
      }
   }

   //Added for API
   if( isXMLAPIContext() )	   
   {
	   _dstrFromScr.strip().upperCase();
	   if( _dstrFromScr == NULL_STRING )
	   {
		   _dstrFromScr = Settlement_Para::SINGLESEARCH;
	   }

	   pSettlement->setParameters(ifds::SearchType,_dstrFromScr, idDataGroup );

	   if( _dstrFromScr == Settlement_Para::EXTERNAL_ID )
	   {
		   DString _dstrExIdType, _dstrExId, _dstrSettleAll;

		   getParameter( Settlement_Para::EXTERNALIDTYPE,  _dstrExIdType );
		   getParameter( Settlement_Para::EXTERNALID,  _dstrExId );
		   getParameter( Settlement_Para::SETTLEALL,  _dstrSettleAll );

		   _dstrExIdType.stripAll();
		   _dstrExId.stripAll();
		   _dstrSettleAll.stripAll();
		   
		   pSettlement->setParameters(ifds::ExternalIdType,_dstrExIdType, idDataGroup );
		   pSettlement->setParameters(ifds::ExternalId,_dstrExId, idDataGroup );

		   performSearch(this, IFASTBP_PROC::SETTLEMENT_LIST, SEARCH_START);
		   if(_dstrSettleAll == YES)
		   {
			   if( _pSettlementTradeList )
				 _pSettlementTradeList->setSetAllFields( idDataGroup,_dstrSettleAll,false );
		   }
	   }
	   else if( _dstrFromScr == Settlement_Para::ALL_TRADE )
	   {		   
		   DString _dstrSettleAll;
		   getParameter( Settlement_Para::SETTLEALL,  _dstrSettleAll );
		   _dstrSettleAll.stripAll();

		   performSearch(this, IFASTBP_PROC::SETTLEMENT_LIST, SEARCH_START);
		   if(_dstrSettleAll == YES)
		   {
			   if( _pSettlementTradeList )
				 _pSettlementTradeList->setSetAllFields( idDataGroup,_dstrSettleAll,false );
		   }
	   }
	   if( _dstrFromScr == Settlement_Para::WIRE_ORDER )
	   {
		   DString _dstrWireOrder, _dstrSettleAll;

		   getParameter( Settlement_Para::WIREORDNUM,  _dstrWireOrder );		   
		   getParameter( Settlement_Para::SETTLEALL,  _dstrSettleAll );

		   _dstrWireOrder.stripAll();
		   _dstrSettleAll.stripAll();
		   
		   pSettlement->setParameters(ifds::WireOrdNum,_dstrWireOrder, idDataGroup );

		   performSearch(this, IFASTBP_PROC::SETTLEMENT_LIST, SEARCH_START);
		   if(_dstrSettleAll == YES)
		   {
			   if( _pSettlementTradeList )
				 _pSettlementTradeList->setSetAllFields( idDataGroup,_dstrSettleAll,false );
		   }
	   }
		if( _dstrFromScr == Settlement_Para::TRANS_NUMBER )
	   {
		   DString _dstrTransNum, _dstrSettleAll;

		   getParameter( Settlement_Para::TRANSNUM,  _dstrTransNum );		   
		   getParameter( Settlement_Para::SETTLEALL,  _dstrSettleAll );

		   _dstrTransNum.stripAll();
		   _dstrSettleAll.stripAll();
		   
		   pSettlement->setParameters(ifds::TransNum,_dstrTransNum, idDataGroup );

		   performSearch(this, IFASTBP_PROC::SETTLEMENT_LIST, SEARCH_START);
		   if(_dstrSettleAll == YES)
		   {
			   if( _pSettlementTradeList )
				 _pSettlementTradeList->setSetAllFields( idDataGroup,_dstrSettleAll,false );
		   }
	   }
	   else if(_dstrFromScr == Settlement_Para::SINGLESEARCH)
	   {
			DString dstrSearchType = _dstrFromScr;
			getParameter( Settlement_Para::TRANSNUM,  _dstrTransNum );
			getParameter( Settlement_Para::FUNDCODE,  _dstrFundCode );
			getParameter( Settlement_Para::CLASSCODE,  _dstrClassCode );
			getParameter( Settlement_Para::TRANSTYPE,  _dstrTransType );
			getParameter( Settlement_Para::SETTLEDATE,  _dstrSettleDate );
			getParameter( Settlement_Para::TRADEDATE,  _dstrTradeDate );
			getParameter( Settlement_Para::BROKERCODE,  _dstrBrokerCode );
			_dstrTransNum.strip().stripLeading('0');
			_dstrFundCode.strip();
			_dstrClassCode.strip();
			_dstrTransType.strip();
			_dstrBrokerCode.strip();
			pSettlement->setParameters(dstrSearchType,_dstrAccountNum, idDataGroup );			
			pSettlement->setParameters(ifds::TransNum,_dstrTransNum, idDataGroup, false );
			pSettlement->setParameters(ifds::FundCode,_dstrFundCode, idDataGroup, false );
			pSettlement->setParameters(ifds::ClassCode,_dstrClassCode, idDataGroup, false );
			pSettlement->setParameters(ifds::TransType,_dstrTransType, idDataGroup, false );
			pSettlement->setParameters(ifds::SettleDate,_dstrSettleDate, idDataGroup, false );
			pSettlement->setParameters(ifds::TradeDate,_dstrTradeDate, idDataGroup, false );
			pSettlement->setParameters(ifds::BrokerCode,_dstrBrokerCode, idDataGroup, false );
			performAPISearch(this, IFASTBP_PROC::SETTLEMENT_LIST, SEARCH_START);
	   }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
bool SettlementProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
	return( cmd.getKey() == CMD_GUI_SETTELEMENT );
}

//******************************************************************************
bool SettlementProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

   bool bRtn = false;
   try
   {
	  if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists         
         doInit();

         if( _rpChildGI->refresh( this, NULL ) )
		 {
             bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
		 }
      }
	  else
	  {
		  assert(0);
	  }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(bRtn);
}

//******************************************************************************
E_COMMANDRETURN SettlementProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {

      setParameter( Settlement_Para::ACCOUNT_NUM, _dstrAccountNum );
      setParameter( Settlement_Para::FROM_SCR,  _dstrFromScr );

	  if( !isXMLAPIContext() )
      {
		  rtn = invokeCommand( this, CMD_GUI_SETTELEMENT, getProcessType(), isModal(),
                           &_rpChildGI );
	  }
	  else
	  {
		  rtn = CMD_MODELESS_INPROCESS;
	  }
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}
//****************************************************************************************************

bool SettlementProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || _pSettlementTradeList == NULL ? false : 
          _pSettlementTradeList->doMoreRecordsExist());
}



//****************************************************************************************************
SEVERITY SettlementProcess::performSearch( GenericInterface *rpGI, 
                                           const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ) );
   SEVERITY sevRtn = SEVERE_ERROR;
   SEVERITY sevRtn1 = SEVERE_ERROR;
   try
   {
      Settlement* pSettlement;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      sevRtn = dstcWorkSession->getSettlement(  pSettlement, getDataGroupId()    );
      if( eSearchAction == SEARCH_START )
      {
         if( pSettlement && sevRtn <= WARNING )
         {
            sevRtn = pSettlement->validateAll( getDataGroupId()  );
         }
         if( sevRtn <= WARNING )
         {
            setContainer( IFASTBP_PROC::SETTLEMENT_LIST, NULL );
            sevRtn1 = pSettlement->getSettlementTradeList(  _pSettlementTradeList, getDataGroupId() );
            if( sevRtn1 <= WARNING && _pSettlementTradeList )
            {
               setContainer( IFASTBP_PROC::SETTLEMENT_LIST, _pSettlementTradeList );
               
               setContainer( IFASTBP_PROC::SETTLEMENT_TOTAL_LIST, NULL );
               SettlementTotalList* pSettlementTotalList;
               SEVERITY severity = pSettlement->getSettlementTotalList( pSettlementTotalList, getDataGroupId() );
               if( severity <= WARNING && pSettlementTotalList )
               {
                  setContainer( IFASTBP_PROC::SETTLEMENT_TOTAL_LIST, pSettlementTotalList );
               }
               sevRtn1 = (sevRtn1 > severity)? sevRtn1 : severity;
            }
         }
      }
      else if( eSearchAction == SEARCH_NEXT_BLOCK )
      {
         sevRtn1 = _pSettlementTradeList->getMore();
      }
      sevRtn = sevRtn1 > sevRtn? sevRtn1:sevRtn;
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ), 
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}

//******************************************************************************
void SettlementProcess::setCurrentListItem(
                                           const GenericInterface *rpGICaller,
                                           const BFContainerId &idList,
                                           const DString &strListItemKey
                                           )
{  
   TRACE_METHOD( CLASSNAME, I_( "setCurrentListItem" ) );
   BFDataGroupId idDataGroup = getDataGroupId();

   AbstractProcess::setCurrentListItem (rpGICaller, idList, strListItemKey);
   if (IFASTBP_PROC::SETTLEMENT_LIST == idList)
   {
//refresh the account number on the address list, get the shareholder      
      BFAbstractCBO *rpPtr = getCBOItem (IFASTBP_PROC::SETTLEMENT_LIST, 
         idDataGroup);
      if (rpPtr)
      {
         DSTCWorkSession * pDSTCWorkSession = 
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         DString shrNum;
         Shareholder *pShareholder = NULL;

         rpPtr->getField (ifds::ShrNum, shrNum, idDataGroup, false);        
         if (pDSTCWorkSession->getShareholder(idDataGroup, shrNum, pShareholder) <= WARNING &&
            pShareholder)
         {
            AddressList *pAddressList = NULL;
   
            if (pShareholder->getAddressList (pAddressList, idDataGroup) <= WARNING &&
               pAddressList)
            {
               DString accountNum;

               rpPtr->getField (ifds::AccountNum, accountNum, idDataGroup, false);
               //refresh the account num field on the address list
               pAddressList->setField (
                  ifds::AccountNum, 
                  accountNum, 
                  BF::HOST, //so everybody gets the value of the account number
                  false);
            }
         }
      }
   }
}

//****************************************************************************************************
SEVERITY SettlementProcess::performAPISearch( GenericInterface *rpGI, 
                                           const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ) );
   SEVERITY sevRtn = SEVERE_ERROR;
   SEVERITY sevRtn1 = SEVERE_ERROR;
   try
   {
      Settlement* pSettlement;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      sevRtn = dstcWorkSession->getSettlement(  pSettlement, getDataGroupId()    );
      if( eSearchAction == SEARCH_START )
      {

         if( pSettlement && sevRtn <= WARNING )
         {
            sevRtn = pSettlement->validateAll( getDataGroupId()  );
         }
         if( sevRtn <= WARNING )
         {
            setContainer( IFASTBP_PROC::SETTLEMENT_LIST, NULL );
            sevRtn1 = pSettlement->getSettlementTradeList(  _pSettlementTradeList, getDataGroupId() );
            if( sevRtn1 <=WARNING && _pSettlementTradeList )
            {
               setContainer( IFASTBP_PROC::SETTLEMENT_LIST, _pSettlementTradeList );

            }
            /*setContainer( IFASTBP_PROC::SETTLEMENT_TOTAL_LIST, NULL );
            SettlementTotalList* pSettlementTotalList;
            sevRtn = pSettlement->getSettlementTotalList(  pSettlementTotalList, getDataGroupId() );
            if( sevRtn1 <=WARNING && pSettlementTotalList )
            {
               setContainer( IFASTBP_PROC::SETTLEMENT_TOTAL_LIST, pSettlementTotalList );

            }*/

         }
      }
      else if( eSearchAction == SEARCH_NEXT_BLOCK )
      {

         sevRtn1 = _pSettlementTradeList->getMore();


      }
      sevRtn = sevRtn1 > sevRtn? sevRtn1:sevRtn;
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ), 
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}


//******************************************************************************
void *SettlementProcess::getPtrForContainer(const BFContainerId& idContainer,
                                            const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if (_pSettlementTradeList == NULL)
      {
         if (_pDummySettlementTradeList == NULL)
         {
            _pDummySettlementTradeList = new SettlementTradeList(*dstcWorkSession);
         }

         ptr = _pDummySettlementTradeList;
      }
   }
   catch ( ConditionException & )
   {
      throw;
   }
   catch ( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return (ptr);
}

//******************************************************************************
void SettlementProcess::doGetField( const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup,
                                    DString &strValueOut,
                                    bool bFormatted ) const
{
   if( idField == SETTL_PROC::SHR_NUM )
   {
      strValueOut = _dstrShrNum;
   }
   else if( idField == SETTL_PROC::ENTITY_NAME )
   {
      strValueOut = _dstrEntityName;
   }
   else if( idField == ifds::SettleAll )
   {
      if( _pSettlementTradeList )
         _pSettlementTradeList->getField(ifds::SettleAll,strValueOut,idDataGroup);
   }
   else if( idField == SETTL_PROC::TOTAL_COUNT || idField == SETTL_PROC::TOTAL_COUNT_SETTLE )
   {
      Settlement* pSettlement;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getSettlement(  pSettlement, getDataGroupId()    );
      if( pSettlement )
      {
         SettlementTotalList* pSettlementTotalList;
         pSettlement->getSettlementTotalList(  pSettlementTotalList, getDataGroupId(),false,false   );
         if( pSettlementTotalList )
            strValueOut = pSettlementTotalList->getCountNum(idField == SETTL_PROC::TOTAL_COUNT_SETTLE, getDataGroupId() );

      }
   }
   else if( idField == SETTL_PROC::CORRESPONDENT_INFO )
   {
      SettlementTrade* pSettlementTrade = dynamic_cast <SettlementTrade*> ( const_cast<SettlementProcess*>(this)->getCBOItem( idContainer, idDataGroup ) );
      (BankInstructions::isCorrBankInfoEntered ( pSettlementTrade, idDataGroup ))?strValueOut = YES:strValueOut = NO;
   }
   else if( idField == SETTL_PROC::PERMIT_INQ || idField == SETTL_PROC::PERMIT_UPDATE )
   {
      Settlement* pSettlement;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getSettlement(  pSettlement, getDataGroupId()    );
      if( pSettlement )
      {
         DString dstrSearchType;
         pSettlement->getField(ifds::SearchType,dstrSearchType,getDataGroupId(),false );
         dstrSearchType.strip();
         strValueOut = pSettlement->hasPermissionForSearchType(dstrSearchType,idField == SETTL_PROC::PERMIT_INQ )? YES:NO;
      }
   }
   else if ( idField == ifds::PayInstructExists || idField == ifds::PayToEntity )
   {
      DString transNum, transId, accountNum;

      SettlementProcess* pThis = 
         const_cast <SettlementProcess*> (this);

      pThis->getField( this, IFASTBP_PROC::SETTLEMENT_LIST, ifds::TransNum, transNum, false );
      pThis->getField( this, IFASTBP_PROC::SETTLEMENT_LIST, ifds::TransId, transId, false );
      pThis->getField( this, IFASTBP_PROC::SETTLEMENT_LIST, ifds::AccountNum, accountNum, false );

      MFAccount* pMFAccount;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( !accountNum.strip().upperCase().empty() && 
          !transNum.strip().upperCase().empty() && 
          !transId.strip().upperCase().empty() )
      {
         if( dstcWorkSession->getMFAccount( getDataGroupId(),accountNum,pMFAccount) <= WARNING && 
             pMFAccount )
         {
            TransactionList *pTransactionList = NULL;
            if( pMFAccount->getTransactionHistoryList(pTransactionList, 
                                                      NULL_STRING, //FundCode, 
                                                      NULL_STRING, //ClassCode, 
                                                      NULL_STRING, //NumEntry, 
                                                      NULL_STRING, //allFundsMode, 
                                                      transId,
                                                      getDataGroupId(), 
                                                      true, //inquireDatabase
                                                      NULL_STRING, //ExtTransNum
                                                      true, //receiveAll,
                                                      transNum ) <= WARNING && 
                                                      pTransactionList )
            {
               TransactionDetails* pTransactionDetails = NULL;

               BFObjIter iterTransactionsList(*pTransactionList, getDataGroupId());

               iterTransactionsList.begin();
               if ( !iterTransactionsList.end() ) // hopefully there would be only one record!
               {
                  pTransactionDetails = dynamic_cast<TransactionDetails*>(iterTransactionsList.getObject());
                  pTransactionDetails->getDetails( transId );

                  if ( idField == ifds::PayInstructExists )
                  {
                     pTransactionDetails->getField( idField, strValueOut, getDataGroupId(), false );
                  }
                  else
                  {
                     pTransactionDetails->getPayToEntity( strValueOut, getDataGroupId() );
                  }

                  strValueOut.strip();
               }
            }
         }
      }
   }
   else
   {
      assert(0);
   }
}
//**************************************************************************************
bool SettlementProcess::doOk(GenericInterface *rpGICaller)
{
   DString dstrAccountNum;
   bool bSettleMoreThanOne = false;
   if( _pSettlementTradeList )
   {
      bSettleMoreThanOne = _pSettlementTradeList->settleMoreThenOne( getDataGroupId(),dstrAccountNum ); 
   }
   DString dstrDisableRemark = bSettleMoreThanOne ? I_("Y"):I_("N");
   setParameter( MFCAN_IP_PARAM::DISABLE_REMARKS, dstrDisableRemark );
   if( !bSettleMoreThanOne ) //only settle one record, we pass LastActiveAccountNum
	{
      setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum );
		setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, NULL_STRING );
	}
	if( _pSettlementTradeList )
	{
      _pSettlementTradeList->clearUnsettleUpdatedFalg( getDataGroupId() );
	}	
   return(true);
}
//*****************************************************************************
SEVERITY  SettlementProcess:: doSetField(
                                        const GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer,
                                        const BFFieldId& idField,
                                        const BFDataGroupId& idDataGroup,
                                        const DString& strValue,
                                        bool bFormatted
                                        )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSetField" ) );

   if( idField == ifds::SettleAll )
   {
      if( _pSettlementTradeList )
         _pSettlementTradeList->setSetAllFields( idDataGroup,strValue,bFormatted );
   }
   else if( idField == SETTL_PROC::COPY_ADDRESS )
   {
      SettlementTrade* pSettlementTrade =  
      dynamic_cast<SettlementTrade*>( getCBOItem( idContainer, idDataGroup ) );
      if( pSettlementTrade ) pSettlementTrade->copyAddress( strValue, idDataGroup );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
bool SettlementProcess::doSend(
                              GenericInterface *rpGICaller,
                              const I_CHAR *szMessage
                              ) 
{
   DString dstrTag(szMessage);
   DString dstrFilter(NULL_STRING);
   if( dstrTag == Settlement_Para::DISPLAY_SETTLE_ONLY )
   {
      DString strSettle = asString( ifds::Settled.getId() );
      dstrFilter += strSettle;
      dstrFilter += I_( "=" );
      dstrFilter += I_("Y");
      setDataFilter( IFASTBP_PROC::SETTLEMENT_LIST, dstrFilter);
      return(true);
   }
   else if( dstrTag == Settlement_Para::DISPLAY_ALL )
   {
      clearDataFilter( IFASTBP_PROC::SETTLEMENT_LIST );
      return(true);
   }
	else if (dstrTag == Settlement_Para::RESET_ITEM )
	{
	   Settlement* pSettlement;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getSettlement(  pSettlement, getDataGroupId()    );
		SettlementTrade* pSettlementTrade =  
				dynamic_cast<SettlementTrade*>( getCBOItem( IFASTBP_PROC::SETTLEMENT_LIST, getDataGroupId() ) );

      if( pSettlement && pSettlementTrade )
      {
			pSettlement->UserChangeSettle(pSettlementTrade,ifds::Settled, getDataGroupId() );
		}
	}
   return(false);
}
/******************************************************************************
 Input: GenericInterface,ContainerID
 OutPut:None
 Return:BFProperties
 Functionality:Overide the getField Attributs for subclassed fields 
******************************************************************************/
const BFProperties *SettlementProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller,const BFContainerId &idContainer, 
															  const BFFieldId &idField, const BFDataGroupId &idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doGetFieldAttributes"));
   BFProperties  *pBFProperties = NULL;
   if (IFASTBP_PROC::SETTLEMENT_LIST == idContainer)
   {
	 if( idField == ifds::SettlementListHeadSet )
	 {
	   if(!_propSettlementListHeadSet)
	   {
		 const BFDataFieldProperties* pProps = BFDataFieldProperties::get (idField);
         _propSettlementListHeadSet			 = new BFProperties (pProps);
		 assert( _propSettlementListHeadSet );
		 DString dstrSubList (NULL_STRING), dstrNewSubList (NULL_STRING), dstrFundIDList(NULL_STRING);
		 pProps->getAllSubstituteValues (dstrSubList, ClientLocaleContext::get(), true );
		 DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	     if( dstcWorkSession && WARNING >= dstcWorkSession->getOption(ifds::FundIDList, dstrFundIDList, BF::HOST, false ))
		 {
		  if( MARKET_IDS::CANADA == DSTCommonFunctions::getMarket())
			_propSettlementListHeadSet->setAllSubstituteValues (dstrSubList);  //the fields are removed using DD for Canada
		  else
		   {
		   dstrNewSubList = dstrSubList;
		   DString dstrtempNewSubList = NULL_STRING; 
			if( DString::npos  == dstrFundIDList.find( FUND_ID_CODE::VALOREN ))
			{
				removeItemFromSubtList( dstrNewSubList , FUND_ID_CODE::VALOREN, dstrtempNewSubList );
				dstrNewSubList = dstrtempNewSubList; 
			}
			if( DString::npos  == dstrFundIDList.find( FUND_ID_CODE::TDCC ))
			{
				removeItemFromSubtList( dstrNewSubList , FUND_ID_CODE::TDCC, dstrtempNewSubList );
				dstrNewSubList = dstrtempNewSubList; 
			}
			if( DString::npos  == dstrFundIDList.find( FUND_ID_CODE::CUSIP ))
			{
				removeItemFromSubtList( dstrNewSubList , FUND_ID_CODE::CUSIP, dstrtempNewSubList );
				dstrNewSubList = dstrtempNewSubList; 
			}
		   _propSettlementListHeadSet->setAllSubstituteValues( dstrNewSubList ); 
		   }
		 }
	   }
	   else
	   {
		    pBFProperties = _propSettlementListHeadSet;
	   }
	 }
   }
 return pBFProperties;
}
/******************************************************************************
 Input: InSubList,Value to be removed
 OutPut:OutSubList
 Return:Void
 Functionality:Remove the value from the input ';' seprated sublist. 
******************************************************************************/
void  SettlementProcess::removeItemFromSubtList( const DString &dstrSubList, const DString &dstrIDValue, DString &dstrOutSubList )
{
    dstrOutSubList = NULL_STRING;
	I_CHAR *temp = const_cast<I_CHAR*> (dstrSubList.c_str ());
	do
	{
	 DString dstrSubListCode,dstrSubListDescr;   
     temp = parseIdiString (temp, dstrSubListCode, dstrSubListDescr );
	 if( dstrIDValue != dstrSubListCode  )
		dstrOutSubList += dstrSubListCode + I_("=") + dstrSubListDescr + I_(";");
	}while (temp && temp != NULL_STRING && *temp);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SettlementProcess.cpp-arc  $
// 
//    Rev 1.44   Apr 27 2012 09:52:26   if991250
// CPF - Account Setup & Settlement 
// 
//    Rev 1.43   Dec 09 2010 14:58:28   jankovii
// IN 2339013 - P0175778: Uptreaming QA testing
// 
//    Rev 1.42   Dec 01 2010 04:15:52   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.41   Nov 25 2010 14:10:44   jankovii
// PET175778FN01 - Upstreaming Phase 2
// 
//    Rev 1.40   Jul 05 2010 02:21:38   dchatcha
// IN# 1984105 - Settlement from Broker trade will bring out shareholder default bank.
// 
//    Rev 1.39   Aug 20 2009 12:05:28   jankovii
// IN 1803616 -  R94: "List not valid for list ID2120" received when resizing the settlements scn
// 
//    Rev 1.38   May 12 2009 13:48:24   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.37   07 Nov 2008 16:18:56   kovacsro
// IN#1466070 - Unable to SETTLE trades in Desktop via the 'SETTLEMENT' button
// 
//    Rev 1.36   Mar 30 2007 13:56:42   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.34   Mar 14 2007 14:48:40   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.33   Apr 25 2005 17:50:26   ZHANGCEL
// PET 1190 - FN06 -- Settltment by TransNum enhancement
// 
//    Rev 1.32   Feb 08 2005 11:38:38   Fengyong
// Temp check in for Settlement Trade API  - Dave 's needs
// 
//    Rev 1.31   Jan 25 2005 15:32:50   Fengyong
// PET10038244 - Settlement API default search type = single search.
// 
//    Rev 1.30   Dec 22 2004 16:00:48   Fengyong
// PET1094 FN4 - API implementation
// 
//    Rev 1.29   Dec 08 2004 15:48:14   hernando
// PET1117 FN06 - Added field details for FundISIN and FundWKN.
// 
//    Rev 1.28   Sep 07 2004 15:00:52   VADEANUM
// PET 1094 FN4 - Activest Bank Interface.
// 
//    Rev 1.27   May 26 2004 12:08:52   popescu
// PTS 10021623, broker address by tax type and reg adrress code
// 
//    Rev 1.26   Oct 30 2003 11:16:14   YINGBAOL
// PTS10023034
// 
//    Rev 1.25   Sep 03 2003 11:19:36   YINGBAOL
// calculating for settlenum after reset
// 
//    Rev 1.24   May 22 2003 14:11:42   popescu
// Replaced name 'BankInstr' with 'BankInstructions'; 
// simplified child lists getters for the Shareholder object
// 
//    Rev 1.23   Apr 07 2003 15:16:08   FENGYONG
// soem change for API
// 
//    Rev 1.22   Mar 21 2003 17:47:58   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.21   Oct 09 2002 23:53:36   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.20   Sep 30 2002 11:01:06   PURDYECH
// BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
// 
//    Rev 1.19   Sep 11 2002 09:51:46   KOVACSRO
// Added SettlePermCode
// 
//    Rev 1.18   Aug 29 2002 16:45:14   SMITHDAV
// Condition split.
// 
//    Rev 1.17   Aug 29 2002 12:54:40   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.16   Aug 16 2002 13:52:50   YINGBAOL
// add permission check
// 
//    Rev 1.15   Aug 08 2002 16:43:02   YINGBAOL
// fix totallist
// 
//    Rev 1.14   Jul 10 2002 16:26:14   YINGBAOL
// clear updated flag for settlement trade
// 
//    Rev 1.13   Jul 05 2002 13:41:32   YINGBAOL
// If there are more than one item settled, disable remarks in confirmation screen
// 
//    Rev 1.12   Jun 21 2002 13:15:28   YINGBAOL
// support window   Title
// 
//    Rev 1.11   Jun 16 2002 14:08:48   HSUCHIN
// added support for corresponding bank check
// 
//    Rev 1.10   Jun 15 2002 15:45:36   YINGBAOL
// change SettleMethod to SettleBy
// 
//    Rev 1.9   Jun 14 2002 16:26:02   YINGBAOL
// add ExpGNSettle
// 
//    Rev 1.8   Jun 14 2002 13:27:02   HSUCHIN
// added BankIdTypeCB
// 
//    Rev 1.7   Jun 13 2002 17:08:56   HSUCHIN
// fixed banking field container ids
// 
//    Rev 1.6   Jun 13 2002 15:51:46   YINGBAOL
// change view 200 and launch other screen
// 
//    Rev 1.5   Jun 12 2002 17:07:30   YINGBAOL
// add total count and other logic
// 
//    Rev 1.4   Jun 11 2002 11:44:58   YINGBAOL
// add copy address logic
// 
//    Rev 1.3   Jun 08 2002 13:03:48   HSUCHIN
// added bank fields to container
// 
//    Rev 1.2   Jun 06 2002 16:07:04   YINGBAOL
// save work
// 
//    Rev 1.1   Jun 04 2002 10:48:38   YINGBAOL
// save work
// 

 * 
 *
 */
