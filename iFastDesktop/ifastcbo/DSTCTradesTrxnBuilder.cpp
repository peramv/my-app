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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCTradesTrxnBuilder.cpp
// ^AUTHOR : Shaobo Huang
// ^DATE   : March 21, 2000
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCTradesTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dilutionalloc.hpp"
#include "dilutionalloclist.hpp"
#include "dstctradestrxnbuilder.hpp"
#include "giinvestmentdetails.hpp"
#include "giinvestmentdetailslist.hpp"
#include "tradeacctalloc.hpp"
#include "tradeacctalloclist.hpp"
#include "tradefromfundalloc.hpp"
#include "tradefromfundalloclist.hpp"
#include "transfeelist.hpp"
#include "transfee.hpp"
#include "accountdistributionlist.hpp"
#include "mfaccount.hpp"
#include "trade.hpp"
#include "tradepayinstructlist.hpp"
#include "tradepayinstruct.hpp"
#include "worksessiontradeslist.hpp"
#include "tradefundalloc.hpp"
#include "tradefundalloclist.hpp"
#include "splitcommission.hpp"
#include "splitcommissionlist.hpp"
#include "mgmtco.hpp"
#include "TradeSettlementLocationsList.hpp"
#include "TradeSettlementLocations.hpp"
#include "dstcmatsweepinstrtrxnbuilder.hpp"
#include "RESPBeneficiaryAllocationList.hpp"
#include "RESPBeneficiaryAllocation.hpp"
#include "RESPTransferList.hpp"
#include "RESPTransfer.hpp"
#include "estateallocationlist.hpp"
#include "estateallocation.hpp"
#include "funddetail.hpp"
#include "DSTCPendingTradeErrorTrxnBuilder.hpp"

#include <ifastdataimpl\dse_dstc0115_req.hpp>
#include <ifastdataimpl\dse_dstc0115_vw.hpp>
#include <ifastdataimpl\dse_dstc0339_vw.hpp>
#include <ifastdataimpl\dse_dstc0397_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADES_LIST;
}
namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCTradesTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId PayToEntity;
   extern CLASS_IMPORT const BFTextFieldId BenefRecType;
   extern CLASS_IMPORT const BFDecimalFieldId ForcedRateAmt;
   extern CLASS_IMPORT const BFTextFieldId AWDFieldFlag;   
}
namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE;
}

struct FieldPair
{
   FieldPair( const BFFieldId& objFieldId, const BFFieldId& viewFieldId )
   : _objFieldId( objFieldId )
   , _viewFieldId( viewFieldId )
   {
   }

   BFFieldId _objFieldId;
   BFFieldId _viewFieldId;
};

struct FieldPair fieldsInAcctAlloc[] = 
{
   FieldPair( ifds::AccountNum,       ifds::AccountNum ),
   FieldPair( ifds::AllocPercentage,  ifds::AcctPrcnt ),
   FieldPair( ifds::AllocAmount,      ifds::AcctLvlAmount ),
   FieldPair( ifds::DistribDetlVer,   ifds::AcctLvlVer ),
   FieldPair( ifds::DistribDetlRid,   ifds::AcctLvlRid )
};
static const int numFieldsInAcctAlloc = sizeof( fieldsInAcctAlloc ) / sizeof( FieldPair );

struct FieldPair fieldsInFundAlloc[] = 
{
   FieldPair( ifds::FundCode,        ifds::FundCode ),
   FieldPair( ifds::ClassCode,       ifds::ClassCode ),
   FieldPair( ifds::AllocPercentage, ifds::AllocPercentage ),
   FieldPair( ifds::AllocAmount,     ifds::AllocAmount ),
   FieldPair( ifds::DistribDetlVer,  ifds::DistribDetlVer ),
   FieldPair( ifds::DistribDetlRid,  ifds::DistribDetlRid ),
   FieldPair( ifds::RecordType,      ifds::RecordType ),
   FieldPair( ifds::AllocAmtType,    ifds::AllocAmtType ),
   FieldPair( ifds::AccountNum,      ifds::AccountNum ),
   FieldPair( ifds::FeeType,         ifds::FeeType),
   FieldPair( ifds::FeeRate,         ifds::FeeRate),

};
static const int numFieldsInFundAlloc = sizeof( fieldsInFundAlloc ) / sizeof( FieldPair );

struct FieldPair fieldsInSplitComm[] = 
{
   FieldPair( ifds::CommLevel,      ifds::CommLevel ),
   FieldPair( ifds::CommRate,       ifds::CommRate ),
   FieldPair( ifds::TradesPayType,  ifds::TradesPayType ),
   FieldPair( ifds::Fixed,          ifds::Fixed ),
   FieldPair( ifds::GrossOrNet,     ifds::GrossOrNet ),
   FieldPair( ifds::CommPrcnt,      ifds::CommPrcnt ),
   FieldPair( ifds::BrokerCode,     ifds::BrokerCode ),
   FieldPair( ifds::BranchCode,     ifds::BranchCode ),
   FieldPair( ifds::SlsrepCode,     ifds::SlsrepCode ),
   FieldPair( ifds::SplitCommRid,   ifds::SplitCommRid ),
   FieldPair( ifds::RenunAmount,    ifds::RenunAmount ),
};
static const int numFieldsInSplitComm = sizeof( fieldsInSplitComm ) / sizeof( FieldPair );

struct FieldPair fieldsInFromAlloc[] = 
{
   FieldPair (ifds::AllocPercentage,  ifds::AcctPrcnt),
};

static const int numFieldsInFromAlloc = sizeof( fieldsInFromAlloc ) / sizeof( FieldPair );

struct FieldPair fieldsInTransFee [] = 
{
   FieldPair (ifds::RecordType,    ifds::RecordType),
   FieldPair (ifds::TransFeeCode,  ifds::TransFeeCode),
   FieldPair (ifds::FeeType,       ifds::FeeType),
   FieldPair (ifds::FeeRate,       ifds::FeeRate),
   FieldPair (ifds::Currency,      ifds::Currency),
   FieldPair (ifds::ChargeOption,  ifds::ChargeOption),
   FieldPair (ifds::TradeFeeOption,ifds::TradeFeeOption),
   FieldPair (ifds::OrigFeeType,   ifds::OrigFeeType),
   FieldPair (ifds::OrigFeeRate,   ifds::OrigFeeRate),
   FieldPair (ifds::TransFeeRID,   ifds::TransFeeRID),
   FieldPair (ifds::FundCode,      ifds::FundCode),
   FieldPair (ifds::ClassCode,     ifds::ClassCode),

};

static const int numFieldsInTransFee = sizeof( fieldsInTransFee ) / sizeof( FieldPair );

struct FieldPair fieldsInMultiSettleLocations [] = 
{
   FieldPair (ifds::RecordType,        ifds::RecordType),
   FieldPair (ifds::SettleLocCode,     ifds::SettleLocCode),
   FieldPair (ifds::TransClrSettlAmt,  ifds::TransClrSettlAmt),
   FieldPair (ifds::ForAccount,        ifds::ForAccount),
   FieldPair (ifds::TransClrSettlUUID, ifds::TransClrSettlUUID),
   FieldPair (ifds::InFavourOf,        ifds::InFavourOf),
   FieldPair (ifds::DeliveryTo,        ifds::DeliveryTo)
};

static const int numFieldsInMultiSettlemLocations = sizeof( fieldsInMultiSettleLocations ) / sizeof( FieldPair );

struct FieldPair fieldsInEntityAllocations [] = 
{
   FieldPair (ifds::RecordType,           ifds::RecordType),
   FieldPair (ifds::AllocEntityType,      ifds::AllocEntityType),
   FieldPair (ifds::AllocEntityTypeSeq,   ifds::AllocEntityTypeSeq),
   FieldPair (ifds::RESPBenefId,          ifds::RESPBenefId),
   FieldPair (ifds::RESPAllocAmt,         ifds::RESPAllocAmt),
   FieldPair (ifds::RESPAllocPrcnt,       ifds::RESPAllocPrcnt),
};

static const int numFieldsInEntityAllocations = sizeof( fieldsInEntityAllocations ) / sizeof( FieldPair );

struct FieldPair fieldsInRESPTransfer [] = 
{
   FieldPair (ifds::RecordType,                 ifds::RecordType),
   FieldPair (ifds::FromPlanNum,                ifds::FromPlanNum),
   FieldPair (ifds::FromContractId,             ifds::FromContractId),
   FieldPair (ifds::ToPlanNum,                  ifds::ToPlanNum),
   FieldPair (ifds::ToContractId,               ifds::ToContractId),
   FieldPair (ifds::InceptionDate,              ifds::InceptionDate),
   FieldPair (ifds::TerminationDate,            ifds::TerminationDate),
   FieldPair (ifds::NEQ1,                       ifds::NEQ1),
   FieldPair (ifds::NEQ2,                       ifds::NEQ2),
   FieldPair (ifds::RESPLetter,                 ifds::RESPLetter),
   FieldPair (ifds::RESPTransStat,              ifds::RESPTransStat),
   FieldPair (ifds::AcctLvlOverride,            ifds::AcctLvlOverride),
   FieldPair (ifds::RecordLevel,                ifds::RecordLevel),
   FieldPair (ifds::RESPTrfAllocEntityTypeFrom, ifds::RESPTrfAllocEntityTypeFrom),
   FieldPair (ifds::RESPTrfEntityTypeSeqFrom,   ifds::RESPTrfEntityTypeSeqFrom),
   FieldPair (ifds::RESPBenefIDFrom,            ifds::RESPBenefIDFrom),
   FieldPair (ifds::RESPTrfAllocEntityTypeTo,   ifds::RESPTrfAllocEntityTypeTo),
   FieldPair (ifds::RESPTrfEntityTypeSeqTo,     ifds::RESPTrfEntityTypeSeqTo),
   FieldPair (ifds::RESPBenefIDTo,              ifds::RESPBenefIDTo),
   FieldPair (ifds::YTDContr,                   ifds::YTDContr),
   FieldPair (ifds::TDContr,                    ifds::TDContr),
   FieldPair (ifds::GrantAmount,                ifds::GrantAmount),
   FieldPair (ifds::AdditionalGrant,            ifds::AdditionalGrant),
   FieldPair (ifds::CLBAmount,                  ifds::CLBAmount),
   FieldPair (ifds::PGrantAmount,               ifds::PGrantAmount),
   FieldPair (ifds::TDRedContrib,               ifds::TDRedContrib),
   FieldPair (ifds::TDRedEarning,               ifds::TDRedEarning),
   FieldPair (ifds::RedCESG,                    ifds::RedCESG),
   FieldPair (ifds::RedCLB,                     ifds::RedCLB),
   FieldPair (ifds::RedPGrant,                  ifds::RedPGrant),
   FieldPair (ifds::UCAmt,                      ifds::UCAmt),
   FieldPair (ifds::ACAmt,                      ifds::ACAmt),
   FieldPair (ifds::Pre98ContribAmt,            ifds::Pre98ContribAmt),
   FieldPair (ifds::Pre98RedContribAmt,         ifds::Pre98RedContribAmt),
   FieldPair (ifds::TransferPercent,            ifds::TransferPercent),
   FieldPair (ifds::QESIUCAmount,               ifds::QESIUCAmount),
   FieldPair (ifds::QESIACAmount,               ifds::QESIACAmount),
   FieldPair (ifds::QESIYTDContribution,        ifds::QESIYTDContribution),
   FieldPair (ifds::QESIBasicGrant,             ifds::QESIBasicGrant),
   FieldPair (ifds::QESIIncreaseAmt,            ifds::QESIIncreaseAmt),
   FieldPair (ifds::Pre98QESIContrib,           ifds::Pre98QESIContrib),
   FieldPair (ifds::Pre2007QESIContrib,         ifds::Pre2007QESIContrib),
   FieldPair (ifds::RESPExtTrDetlUUID,          ifds::RESPExtTrDetlUUID),
   FieldPair (ifds::RESPExtTrDetlVer,           ifds::RESPExtTrDetlVer),
   FieldPair (ifds::RESPContrDetlUUID,          ifds::RESPContrDetlUUID),
   FieldPair (ifds::RESPContrDetlVer,           ifds::RESPContrDetlVer),
   FieldPair (ifds::EligibleTransfer,           ifds::EligibleTransfer),
   FieldPair (ifds::HistNonTrustYear,           ifds::HistNonTrustYear),
   FieldPair (ifds::TotTransfINDC,              ifds::TotTransfINDC),
   FieldPair (ifds::CESGPaid,                   ifds::CESGPaid), //P0185010.FN02.R01.02 - CESG Grant paid
   FieldPair (ifds::QESIPaid,                   ifds::QESIPaid),
   FieldPair (ifds::IsResidualCESG,             ifds::IsResidualCESG),
   FieldPair (ifds::SAGESGrant,					ifds::SAGESGrant),
   FieldPair (ifds::SAGESUCAmount,				ifds::SAGESUCAmount),
   FieldPair (ifds::SAGESACAmount,				ifds::SAGESACAmount),
   FieldPair (ifds::BCTESGGrant,				ifds::BCTESGGrant),
   FieldPair (ifds::UCRedAmt,					ifds::UCRedAmt),
   FieldPair (ifds::ACRedAmt,					ifds::ACRedAmt),
   FieldPair (ifds::SAGESRedUCAmt,				ifds::SAGESRedUCAmt),
   FieldPair (ifds::SAGESRedACAmt,				ifds::SAGESRedACAmt),
   FieldPair (ifds::QESIRedUCAmt,				ifds::QESIRedUCAmt),
   FieldPair (ifds::QESIRedACAmt,				ifds::QESIRedACAmt),
   FieldPair (ifds::QESIRedYTDContrib,			ifds::QESIRedYTDContrib),
   FieldPair (ifds::Pre2007QESIRedContrib,		ifds::Pre2007QESIRedContrib),
   FieldPair (ifds::RedAdditionalGrant,			ifds::RedAdditionalGrant),
   FieldPair (ifds::RedSAGES,					ifds::RedSAGES),
   FieldPair (ifds::QESIRedBasic,				ifds::QESIRedBasic),
   FieldPair (ifds::QESIRedIncrease,			ifds::QESIRedIncrease),
   FieldPair (ifds::RedBCTESG,					ifds::RedBCTESG),
};

static const int numFieldsInRESPTransfer = sizeof( fieldsInRESPTransfer ) / sizeof( FieldPair );

struct FieldPair fieldsInDilutionAlloc [] = 
{
   FieldPair( ifds::RecordType,           ifds::RecordType ),
   FieldPair( ifds::Accountable,          ifds::AccCode ),
   FieldPair( ifds::BackDatedReason,      ifds::ReasonCode ),
   FieldPair( ifds::RespDate,             ifds::RespDate ),
   FieldPair( ifds::AllocPercent,         ifds::RspPrcnt ),
   FieldPair( ifds::DilVersion,           ifds::DilVersion ),
   FieldPair( ifds::SplitAccCodeRID,      ifds::SplitAccCodeRID ),
   FieldPair( ifds::BillingToEntityType,  ifds::BillingToEntityType ),
   FieldPair( ifds::BillingToEntity,      ifds::BillingToEntity ),
   FieldPair( ifds::AssociatedAcctNum,    ifds::AssociatedAcctNum ),
   FieldPair( ifds::ExSysDilPymtNSM,      ifds::ExSysDilPymtNSM ),
   FieldPair( ifds::DilutionNSM,		  ifds::DilutionNSM ),
};

static const int numFieldsInDilutionAlloc = sizeof( fieldsInDilutionAlloc ) / sizeof( FieldPair );

struct FieldPair fieldsInPayInstructAlloc [] = 
{
   FieldPair( ifds::RecordType,        ifds::RecordType ),
   FieldPair( ifds::UseEntityAddress,  ifds::TPIUsePayEntAddr ),
   FieldPair( ifds::AddrLine1,         ifds::TPIAddress1 ),
   FieldPair( ifds::AddrLine2,         ifds::TPIAddress2 ),
   FieldPair( ifds::AddrLine3,         ifds::TPIAddress3 ),
   FieldPair( ifds::AddrLine4,         ifds::TPIAddress4 ),
   FieldPair( ifds::AddrLine5,         ifds::TPIAddress5 ),
   FieldPair( ifds::CountryCode,       ifds::TPIAddrCntry ),
   FieldPair( ifds::PostalCode,        ifds::TPIAddrPSTL ),
   FieldPair( ifds::PayToEntity,       ifds::TPIPayEntity ),
   FieldPair( ifds::PaymentFor,        ifds::TPIPaymentFor ),
   FieldPair( ifds::PayType,           ifds::TPIPayType ),
   FieldPair( ifds::PayMethod,         ifds::TPIPayMethod ),
   FieldPair( ifds::ACHProcessor,      ifds::TPIACHProcessor ),
   FieldPair( ifds::BankCharge,        ifds::TPIBankCharge ),
//   FieldPair( ifds::CurrencyOption,		ifds::TPICurrOption ),
   FieldPair( ifds::Currency,          ifds::TPIPayCurrency ),
   FieldPair( ifds::DirectTo,          ifds::TPIDirectTo ),
   FieldPair( ifds::AccountNum,        ifds::TPIReinvAccount ),
   FieldPair( ifds::ConsolType,        ifds::TPIConsolType ),
   //FieldPair( ifds::CompanyCode,		ifds::TPICompanyCode),
   //FieldPair( ifds:::TOShGroup,		ifds::TPITOShGroup),
   FieldPair( ifds::AllocPercent,      ifds::TPIPercentage ),
   FieldPair( ifds::TPIVersion,        ifds::RecTypeVersion ),
   FieldPair( ifds::TPITrdPayInstrID,  ifds::RecTypRecid ),   
   FieldPair( ifds::PayInstructionsId, ifds::TPIPayInstructID ),   
   
};

static const int numFieldsInPayInstructAlloc = sizeof( fieldsInPayInstructAlloc ) / sizeof( FieldPair );

struct FieldPair fieldsInGIInvestDetails [] = 
{
   FieldPair( ifds::RecordType,        ifds::RecordType ),

//   FieldPair( ifds::SelInvRunMode,     ifds::SelInvRunMode),
   FieldPair( ifds::InvHisInvestId,    ifds::InvHisInvestId),
   FieldPair( ifds::InvSummId,         ifds::InvSummId),
   FieldPair( ifds::SelInvAmtType,     ifds::SelInvAmtType),
   FieldPair( ifds::SelInvAmount,      ifds::SelInvAmount),
  
};

static const int numfieldsInGIInvestDetails = sizeof( fieldsInGIInvestDetails ) / sizeof( FieldPair );

struct FieldPair fieldsInEstateAllocation [] = 
{
   //extern __declspec(dllimport) const BFNumericFieldId BenefEntityID;
   //extern __declspec(dllimport) const BFTextFieldId BenefAddrCode;
   //extern __declspec(dllimport) const BFTextFieldId BenefAddrLevel;
   //extern __declspec(dllimport) const BFDecimalFieldId BenefPrcnt;
   //extern __declspec(dllimport) const BFDecimalFieldId BenefAmount;
   //extern __declspec(dllimport) const BFDecimalFieldId BenefUnits;
   //extern __declspec(dllimport) const BFTextFieldId BenefName;

   //extern __declspec(dllimport) const BFTextFieldId BenefRunMode;

   //extern __declspec(dllimport) const BFTextFieldId    BenefAddrCode;
   //extern __declspec(dllimport) const BFTextFieldId    BenefAddrLevel;
   //extern __declspec(dllimport) const BFDecimalFieldId BenefPrcnt;
   //extern __declspec(dllimport) const BFDecimalFieldId BenefAmount;
   //extern __declspec(dllimport) const BFDecimalFieldId BenefUnits;
   //extern __declspec(dllimport) const BFNumericFieldId BenefEntityID;

   FieldPair( ifds::BenefAddrCode,     ifds::BenefAddrCode),
   FieldPair( ifds::BenefAddrLevel,    ifds::BenefAddrLevel),
   FieldPair( ifds::BenefPrcnt,        ifds::BenefPrcnt),
   FieldPair( ifds::BenefAmount,       ifds::BenefAmount),
   FieldPair( ifds::BenefUnits,        ifds::BenefUnits),
   FieldPair( ifds::BenefEntityID,     ifds::BenefEntityID),
  
};

static const int numfieldsInEstateAllocation = sizeof( fieldsInEstateAllocation ) / sizeof( FieldPair );

//******************************************************************************
void DSTCTradesTrxnBuilder::fillingData ( BFCBO* pObj, 
                                          BFData* data, 
                                          FieldPair fields[], 
                                          int numFields) 
{
   DString value;
   
   for (int i = 0; i < numFields; ++i)
   {
      pObj->getField (fields[i]._objFieldId, value, BF::HOST, false);
      data->setElementValue (fields[i]._viewFieldId, value, false, false);
   }
}

//******************************************************************************
SEVERITY DSTCTradesTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                   BFAbstractCBO* pBFCBO, 
                                                   HostTransactionContainer* pTrxnContainer, 
                                                   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   SEVERITY sevRtn = SEVERE_ERROR;

   WorksessionTradesList* pTradesList = dynamic_cast<WorksessionTradesList*>(pBFCBO);
   if( pTradesList == NULL )
      return(GETCURRENTHIGHESTSEVERITY());


   DString strTrack, 
      strPageName;

   pTradesList->getTrackActivity (strTrack, strPageName);

   //walk through the Trades List
   //if no list do not go and get one from the database
   BFObjIter iterTradesList(*pTradesList, BF::HOST);
   while( !iterTradesList.end() )
   {
      Trade* pTrade = dynamic_cast<Trade*>(iterTradesList.getObject());
      //We have to do some hack here because base does not supported
      //
      BF_OBJ_ACTIVITY ObjActivityTrade =  iterTradesList.getKey().getActivity();
      if (pTrade && changeObjectActivity (pTrade,ObjActivityTrade ) )
      {
         ++iterTradesList;
         continue;
      }
      if (pTrade && ( ObjActivityTrade == OBJ_ACTIVITY_ADDED    || 
                      ObjActivityTrade == OBJ_ACTIVITY_DELETED  || 
                      pTrade->hasTransactionUpdates()))
      {
         DString dstTrnKey;

         DString dstTransNum;

         pTrade->getField( ifds::TransNum, dstTransNum, BF::HOST, true );
         addIDITagValue(dstTrnKey, TRXNTAG::TRANSNUMTAG, dstTransNum.stripLeading('0').strip());

         HostTransactionContainerIterator iterTrxnContainer( pTrxnContainer );//define an iterator on the HostTransactionContainer
         iterTrxnContainer.walkStrKey( dstTrnKey );                  // look for the trade record in the HostTransactionContainer
         iterTrxnContainer.walkTrxnGroup( NO_GROUP );                //the trxn hasn't been handled yet, no group and sub type set,
         iterTrxnContainer.walkTrxnSubType( 0 );

         iterTrxnContainer.begin();


         BFData *request = new BFData( ifds::DSTC0115_REQ );
         BFData *response = new BFData( ifds::DSTC0115_VW );

         pTrade->getData(*request, BF::HOST);

         request->setElementValue( ifds::Track, strTrack );
         request->setElementValue( ifds::Activity, strPageName );
         DSTCWorkSession::setRunMode(request, ObjActivityTrade);

         DString mgmtCoId;
         workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
         request->setElementValue( ifds::CompanyId, mgmtCoId );

         DString dstrKeyTypes(NULL_STRING);
         //add the transaction to the container; the right side of the XchgData
         JData *jdata = new JData( DSTC_REQUEST::TRADES_LIST, request, response );
         pTrxnContainer->addTransaction( dstTrnKey, jdata, 
                                         ObjActivityTrade, NOT_PERSISTENT, dstrKeyTypes);
         
         //IntRate should be original amount in the case of ForcedRate
         DString dstrForcedRate, dstrForcedRateAmt;
         pTrade->getField(ifds::ForcedRate, dstrForcedRate, BF::HOST);
         if(dstrForcedRate == I_("2"))
         {
            pTrade->getField(ifds::ForcedRateAmt, dstrForcedRateAmt, BF::HOST);
            request->setElementValue(ifds::IntRate, dstrForcedRateAmt);
         }

         // build account allocation, fund allocation and split commission
         TradeAcctAllocList *pAccountAllocationList;
         TradeAcctAlloc* pAccountAllocation;
         TradeFundAllocList* pFundAllocationList;
         TradeFundAlloc* pFundAllocation;
         SplitCommissionList* pSplitCommissionList = NULL;
         SplitCommission* pSplitCommission = NULL;
         
         DString strActivity, 
            tmp, 
            strAcctDistribDetlRid, 
            strFundDistribDetlRid;
	    DString dstrAWDFieldFlag, dstrExtTransNum, dstrTransNum, dstrNetWorkID;
		workSession.getOption (ifds::AWDFieldFlag, dstrAWDFieldFlag, BF::HOST,  false);
		pTrade->getField (ifds::ExtTransNum, dstrExtTransNum, BF::HOST, false);
		pTrade->getField (ifds::TransNum, dstrTransNum, BF::HOST, false);
		pTrade->getField (ifds::NetworkID, dstrNetWorkID,BF::HOST, false);

		if(dstrAWDFieldFlag == I_("Y")&& dstrNetWorkID == I_("AWD") && 
		   !(dstrExtTransNum.stripAll().empty()))
		{
		dstrExtTransNum = dstrExtTransNum +I_("-")+ dstrTransNum;
		request->setElementValue(ifds::ExtTransNum ,dstrExtTransNum);
		}
		//Assign the EventReciept Date and time only during the trans builder
		//to have consistent display of warning in case of dealdatetime empty
		DString dstrEventReceiptTime,dstrEventReceiptDate;
		pTrade->getField(ifds::EventReceiptTime, dstrEventReceiptTime, BF::HOST, false);
		pTrade->getField(ifds::EventReceiptDate, dstrEventReceiptDate, BF::HOST, false);
		//if date is empty for whatever reason,time should also be empty
		if(dstrEventReceiptDate.stripAll().empty())
		{
			request->setElementValue( ifds::EventReceiptTime, NULL_STRING);
		}
		//remove the mask and send the time to the view 
		else if(!dstrEventReceiptTime.stripAll().empty())
		{
			removeMaskFromString(dstrEventReceiptTime,I_("##:##:##"));
			request->setElementValue( ifds::EventReceiptTime, dstrEventReceiptTime);
		}
         //don't create one here, if not already created
         pTrade->getAccountAllocationList (pAccountAllocationList, BF::HOST, false);
         int count = 0;

         if (pAccountAllocationList)
         {
            BFObjIter iterAccountAllocList(*pAccountAllocationList, BF::HOST);
            
            while (!iterAccountAllocList.end())
            {
               pAccountAllocation = dynamic_cast<TradeAcctAlloc*>(iterAccountAllocList.getObject());
               assert(pAccountAllocation);
               
               BF_OBJ_ACTIVITY acctAllocActivity = iterAccountAllocList.getKey().getActivity();
               if( changeObjectActivity( pTrade,acctAllocActivity ) )
               {
                  ++iterAccountAllocList;
                  continue;
               };
               pAccountAllocation->getField (ifds::DistribDetlRid, strAcctDistribDetlRid, BF::HOST, false);
//due to the current design for view 115, if DistribDetlRid == I_("0") and
//1.fundAllocActivity == OBJ_ACTIVITY_NONE, we should change it to OBJ_ACTIVITY_ADDED
//2.fundAllocActivity == OBJ_ACTIVITY_DELETED, we should skip this record, but not the split commissions, if any
               if (acctAllocActivity == OBJ_ACTIVITY_NONE && strAcctDistribDetlRid == I_("0"))
               {
                   acctAllocActivity = OBJ_ACTIVITY_ADDED;
               }
               //don't create one here, if not already created
               pAccountAllocation->getFundAllocationList (pFundAllocationList, BF::HOST, false); 

               bool _bAccountLvl = true;

               if( pFundAllocationList )
               {
                  BFObjIter iterFundAllocList(*pFundAllocationList, BF::HOST);
                  int numFundAllocList = iterFundAllocList.getNumberOfItemsInList();
                  
                  while (!iterFundAllocList.end ())
                  {
                     bool _bFundLvl = true;

                     pFundAllocation = dynamic_cast<TradeFundAlloc*>(iterFundAllocList.getObject());

                     // We should not be comparing the version number, but the record id.                  
                     pFundAllocation->getField( ifds::DistribDetlRid, strFundDistribDetlRid, BF::HOST, false );

                     BF_OBJ_ACTIVITY fundAllocActivity = iterFundAllocList.getKey().getActivity();
                     if( changeObjectActivity( pTrade,fundAllocActivity ) )
                     {
                        ++iterFundAllocList;
                        continue;
                     };

//due to the current design for view 115, if DistribDetlRid == I_("0") and
//1.fundAllocActivity == OBJ_ACTIVITY_NONE, we should change it to OBJ_ACTIVITY_ADDED
//2.fundAllocActivity == OBJ_ACTIVITY_DELETED, we should skip this fund allocation, but not its split commissions!
                     if (fundAllocActivity == OBJ_ACTIVITY_NONE && strFundDistribDetlRid == I_("0"))
                     {
                         fundAllocActivity = OBJ_ACTIVITY_ADDED;
                     }
                     pFundAllocation->getSplitCommissionList (pSplitCommissionList, BF::HOST);
                     bool bSplitCreated (false);
                     if (pSplitCommissionList)
                     {
                        bool deleted = false;
                        
                        BFObjIter iterSplitCommissionList(*pSplitCommissionList, BF::HOST);
//only send one repeat for a deleted fund allocation (if the fund allocation is saved in the database)
                        while (!deleted  && !iterSplitCommissionList.end())
                        {
                          //YB
                          //this is hack, because base does not support to change Object activity
                          //I really hesitate to change it.
                          //Let's cross our hand to pray it will work......

                           BF_OBJ_ACTIVITY splitActivity = iterFundAllocList.getKey().getActivity();
                           if( changeObjectActivity( pTrade,splitActivity ) )
                           {
                              ++iterSplitCommissionList;
                              continue;
                           };
                           deleted = fundAllocActivity == OBJ_ACTIVITY_DELETED && strFundDistribDetlRid != I_("0");
                           
                           pSplitCommission = dynamic_cast<SplitCommission*>(iterSplitCommissionList.getObject());
                           if (pSplitCommission)
                           {
                              BFData dataRepeat (ifds::DSTC0115_REQRepeat_Record);

                              fillingData (pSplitCommission, &dataRepeat, fieldsInSplitComm, numFieldsInSplitComm);

                              bool bSplitCommDeleted = acctAllocActivity == OBJ_ACTIVITY_DELETED || 
                                                       fundAllocActivity == OBJ_ACTIVITY_DELETED;

//If there is a multiple fund allocation, the split commission run mode flag should take the fund
//allocation flag when the fund allocation run mode is added.  This handles the case where a single fund
//allocation was changed to a multiple fund allocation where the split commission run mode flag remained
//a modified mode due to default split commissions.

                              if (fundAllocActivity == OBJ_ACTIVITY_ADDED && numFundAllocList > 1)
                              {
                                 dataRepeat.setElementValue (ifds::CommRunMode, RUNMODE::ADDED);
                              }
                              else
                              {
                                 dataRepeat.setElementValue (
                                    ifds::CommRunMode, 
                                    bSplitCommDeleted ? RUNMODE::DELETED : 
                                    DSTCWorkSession::getRunMode ( iterSplitCommissionList.getKey().getActivity(), 
                                                                  pSplitCommission->hasTransactionUpdates ()
                                                                ) 
                                                            );
                              }
                              fillingData (pFundAllocation, &dataRepeat, fieldsInFundAlloc, numFieldsInFundAlloc);

                              if (_bFundLvl && !(strFundDistribDetlRid == I_("0") && 
                                                fundAllocActivity == OBJ_ACTIVITY_DELETED))
                              {
                                 tmp = DSTCWorkSession::getRunMode ( fundAllocActivity, 
                                                                     pFundAllocation->hasTransactionUpdates ()
                                                                   );
                                 _bFundLvl = false;
                              }
                              else
                              {
                                 tmp = RUNMODE::UNCHANGED;
                              }
                              dataRepeat.setElementValue (ifds::AllocRunMode, tmp);
                              fillingData (pAccountAllocation, &dataRepeat, fieldsInAcctAlloc, numFieldsInAcctAlloc);

                              if ( _bAccountLvl && 
                                   !(strAcctDistribDetlRid == I_("0") && acctAllocActivity == OBJ_ACTIVITY_DELETED)
                                 )
                              {
                                 tmp = DSTCWorkSession::getRunMode ( acctAllocActivity, 
                                                                     pAccountAllocation->hasTransactionUpdates ()
                                                                   ); 
                                 _bAccountLvl = false;
                              }
                              else
                              {
                                 tmp = RUNMODE::UNCHANGED;
                              }
                              dataRepeat.setElementValue( ifds::AcctLvlRunMode, tmp );
                              dataRepeat.setElementValue (ifds::DilRunMode, RUNMODE::UNCHANGED);
                              request->addRepeat(dataRepeat);
                              bSplitCreated = true;
                              ++ count; 
                           }
                           ++iterSplitCommissionList;
                        }
                     }
                     if( !bSplitCreated ) // temp fix until split comm is ready
                     {
                        if( (strFundDistribDetlRid == I_("0") && fundAllocActivity==OBJ_ACTIVITY_DELETED) ||
                            (strAcctDistribDetlRid == I_("0") && acctAllocActivity==OBJ_ACTIVITY_DELETED) )
                        {
                           ++iterFundAllocList;
                           continue;
                        }

                        // when there is no split commission
                        BFData dataRepeat (ifds::DSTC0115_REQRepeat_Record);

                        dataRepeat.setElementValue (ifds::CommRunMode, RUNMODE::UNCHANGED);
                        dataRepeat.setElementValue (ifds::DilRunMode, RUNMODE::UNCHANGED);

                        fillingData (pFundAllocation, &dataRepeat, fieldsInFundAlloc, numFieldsInFundAlloc);

                        if( _bFundLvl)
                        {
                           tmp = DSTCWorkSession::getRunMode( fundAllocActivity, 
                                                              pFundAllocation->hasTransactionUpdates( )); 
                           _bFundLvl = false;
                        }
                        else
                        {
                           tmp = RUNMODE::UNCHANGED;
                        }

                        dataRepeat.setElementValue (ifds::AllocRunMode, tmp);

                        fillingData (pAccountAllocation, &dataRepeat, fieldsInAcctAlloc, numFieldsInAcctAlloc);

                        if (_bAccountLvl)
                        {
                           tmp = ( DSTCWorkSession::getRunMode( acctAllocActivity, 
                                                                pAccountAllocation->hasTransactionUpdates( )) );
                           _bAccountLvl = false;
                        }
                        else
                        {
                           tmp = RUNMODE::UNCHANGED;
                        }
                        dataRepeat.setElementValue( ifds::AcctLvlRunMode, tmp );
                        request->addRepeat(dataRepeat);
                        ++ count; 
                     }

                     //DString transType;
                     //pTrade->getField(ifds::TradesTransType, transType, BF::HOST, false);
                     //DString dstrFundCode;
                     //DString dstrClassCode;
                     //
                     ////BFFieldId fundFieldId (ifds::NullFieldId);
                     ////BFFieldId classFieldId (ifds::NullFieldId);
                     ////pTrade->getFundAndClassFieldIds(fundFieldId, classFieldId);
                     ////pTrade->getField(fundFieldId,  dstrFundCode,  BF::HOST, false);
                     ////pTrade->getField(classFieldId, dstrClassCode, BF::HOST, false);

                     //if(DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE))
                     //{
                     //   pTrade->getField(ifds::FromFund,  dstrFundCode,  BF::HOST, false);
                     //   pTrade->getField(ifds::FromClass, dstrClassCode, BF::HOST, false);
                     //}
                     //else if(DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE))
                     //{
                     //   pTrade->getField(ifds::ToFund,  dstrFundCode,  BF::HOST, false);
                     //   pTrade->getField(ifds::ToClass, dstrClassCode, BF::HOST, false);
                     //}

                     //bool needTransFee = pFundAllocation->hasPurchExchgFrontEndLoadCommission(BF::HOST) && 
                     //   dstrFundCode.stripAll()  == NULL_STRING && 
                     //   dstrClassCode.stripAll() == NULL_STRING;
                     //if(needTransFee)
                     //{
                     //   BFData transFeeDataRepeat(ifds::DSTC0115_REQRepeat_Record);

                     //   transFeeDataRepeat.setElementValue (ifds::CommRunMode, RUNMODE::UNCHANGED);
                     //   transFeeDataRepeat.setElementValue (ifds::AcctLvlRunMode, RUNMODE::UNCHANGED);
                     //   transFeeDataRepeat.setElementValue (ifds::DilRunMode, RUNMODE::UNCHANGED);

                     //   
                     //   fillingData(pFundAllocation, &transFeeDataRepeat, fieldsInTransFee, numFieldsInTransFee);               
                     //   

                     //   DString dstrTransFeeRID;
                     //   transFeeDataRepeat.setElementValue (ifds::RecordType, I_("Fee"));
                     //   

                     //   if(DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE))
                     //   {
                     //      transFeeDataRepeat.setElementValue (ifds::TransFeeCode, I_("1"));
                     //   }
                     //   else if(DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE))
                     //   {
                     //      transFeeDataRepeat.setElementValue (ifds::TransFeeCode, I_("999"));
                     //   }
                     //   transFeeDataRepeat.setElementValue (ifds::ChargeOption,    I_("0"));
                     //   transFeeDataRepeat.setElementValue (ifds::TradeFeeOption,  I_("2"));
                     //   transFeeDataRepeat.setElementValue (ifds::OrigFeeType,     I_("1"));
                     //   transFeeDataRepeat.setElementValue (ifds::OrigFeeRate,     I_("0"));


                     //   FundDetail *pFundDetail = NULL;
                     //   pFundAllocation->getField(ifds::FundCode,  dstrFundCode,  BF::HOST);
                     //   pFundAllocation->getField(ifds::ClassCode, dstrClassCode, BF::HOST);
                     //   if (!dstrFundCode.stripAll().empty() && !dstrClassCode.stripAll().empty() &&
                     //      workSession.getFundDetail (dstrFundCode, dstrClassCode, BF::HOST, pFundDetail) && pFundDetail)
                     //   { 
                     //      DString dstrFeeCurrency; 
                     //      pFundDetail->getField(ifds::Currency, dstrFeeCurrency, BF::HOST, false);
                     //      transFeeDataRepeat.setElementValue(ifds::Currency, dstrFeeCurrency.stripAll());
                     //   } 

                     //   pFundAllocation->getField(ifds::TransFeeRID, dstrTransFeeRID, BF::HOST, false);
                     //   BF_OBJ_ACTIVITY transFeeActivity = iterFundAllocList.getKey().getActivity();
                     //   if (transFeeActivity == OBJ_ACTIVITY_NONE && dstrTransFeeRID == I_("0"))
                     //   {
                     //      transFeeActivity  = OBJ_ACTIVITY_ADDED;
                     //   }
                     //   transFeeDataRepeat.setElementValue(ifds::AllocRunMode, 
                     //           DSTCWorkSession::getRunMode(transFeeActivity, pFundAllocation->hasTransactionUpdates ()));
                     //   request->addRepeat(transFeeDataRepeat);
                     //   ++count;
                     //}
                     ++iterFundAllocList;
                  }
               }
               ++iterAccountAllocList;
            }
         }

         //we did not touch from side allocation for rebook
         //it won't supported 
         //check the from fund allocations
         TradeFromFundAllocList *pTradeFromFundAllocList = NULL;

         if ( pTrade->getFromFundAllocationList (pTradeFromFundAllocList, BF::HOST, false) &&
              pTradeFromFundAllocList)
         {
            BFObjIter iterFromFundAlloc (*pTradeFromFundAllocList, BF::HOST, false);
            
            while (!iterFromFundAlloc.end())
            {
               TradeFromFundAlloc *pTradeFromFundAlloc = 
                     dynamic_cast<TradeFromFundAlloc*>(iterFromFundAlloc.getObject());

               // when there is no split commission
               BFData dataRepeat (ifds::DSTC0115_REQRepeat_Record);

               dataRepeat.setElementValue (ifds::CommRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::DilRunMode, RUNMODE::UNCHANGED);
               fillingData (pTradeFromFundAlloc, &dataRepeat, fieldsInFundAlloc, numFieldsInFundAlloc);
               fillingData (pTradeFromFundAllocList, &dataRepeat, fieldsInFromAlloc, numFieldsInFromAlloc);
               
               pFundAllocation->getField (ifds::DistribDetlRid, strFundDistribDetlRid, BF::HOST, false);

               BF_OBJ_ACTIVITY fundAllocActivity = iterFromFundAlloc.getKey().getActivity();

               if (fundAllocActivity == OBJ_ACTIVITY_NONE && strFundDistribDetlRid == I_("0"))
               {
                  fundAllocActivity = OBJ_ACTIVITY_ADDED;
               }
               dataRepeat.setElementValue ( ifds::AllocRunMode, 
                                            DSTCWorkSession::getRunMode ( fundAllocActivity, 
                                                                          pFundAllocation->hasTransactionUpdates ()));
               dataRepeat.setElementValue (ifds::AcctLvlRunMode, tmp);               
               request->addRepeat(dataRepeat);
               ++count;
               ++iterFromFundAlloc;
            }
         }
//trans fees processing
         TransFeeList *pTransFeeList = NULL;

         //do not create it in here if it doesn't exist
         pTrade->getTransFeeList (pTransFeeList, BF::HOST, false);
         if (pTransFeeList)
         {
            BFObjIter iterTransFees (*pTransFeeList, BF::HOST, false);

            while (!iterTransFees.end())
            {
               DString transFeeId;
               TransFee *pTransFee = dynamic_cast<TransFee*> (iterTransFees.getObject());

               BF_OBJ_ACTIVITY transFeeActivity = iterTransFees.getKey().getActivity();
               if( changeObjectActivity(pTrade,transFeeActivity ) )
               {               
                  ++iterTransFees;
               };

               BFData dataRepeat (ifds::DSTC0115_REQRepeat_Record);

               // when there is no split commission, no acct level allocation
               dataRepeat.setElementValue (ifds::CommRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::AcctLvlRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::DilRunMode, RUNMODE::UNCHANGED);

               fillingData (pTransFee, &dataRepeat, fieldsInTransFee, numFieldsInTransFee);               
               pTransFee->getField (ifds::TransFeeRID, transFeeId, BF::HOST, false);

               //BF_OBJ_ACTIVITY transFeeActivity = iterTransFees.getKey().getActivity();

               if (transFeeActivity == OBJ_ACTIVITY_NONE && transFeeId == I_("0"))
               {
                  transFeeActivity  = OBJ_ACTIVITY_ADDED;
               }
               dataRepeat.setElementValue ( ifds::AllocRunMode, 
                                            DSTCWorkSession::getRunMode ( transFeeActivity, 
                                                                          pTransFee->hasTransactionUpdates ()));
               request->addRepeat (dataRepeat);
               ++count;
               ++iterTransFees;
            }
         }

         DilutionAllocList *pDilutionAllocList = NULL;

         pTrade->getDilutionAllocList (pDilutionAllocList, BF::HOST, false);

         if (pDilutionAllocList)
         {
            BFObjIter iterDilution (*pDilutionAllocList, BF::HOST, false);
			DString  dstrMatchingKey;

            while (!iterDilution.end())
            {
               DilutionAlloc *pDilution = dynamic_cast<DilutionAlloc*> (iterDilution.getObject()); 

               DString splitAccCodeRID;

               BFData dataRepeat (ifds::DSTC0115_REQRepeat_Record);

               // when there is no dilution
               dataRepeat.setElementValue (ifds::AllocRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::AcctLvlRunMode, RUNMODE::UNCHANGED);
               fillingData (pDilution, &dataRepeat, fieldsInDilutionAlloc, numFieldsInDilutionAlloc);   
			   
               pDilution->getField (ifds::SplitAccCodeRID, splitAccCodeRID, BF::HOST, false);

               BF_OBJ_ACTIVITY dilutionActivity = iterDilution.getKey().getActivity();

               if (dilutionActivity == OBJ_ACTIVITY_NONE && splitAccCodeRID == I_("0"))
               {
                  dilutionActivity  = OBJ_ACTIVITY_ADDED;
               }
               dataRepeat.setElementValue ( ifds::DilRunMode, 
                                            DSTCWorkSession::getRunMode ( dilutionActivity, 
                                                                          pDilution->hasTransactionUpdates ()));
               request->addRepeat (dataRepeat);
               ++count;
               ++iterDilution;
            }
			pDilutionAllocList->getField(ifds::MatchingKey, dstrMatchingKey, BF::HOST);
			request->setElementValue (ifds::MatchingKey, dstrMatchingKey);
         }


         TradePayInstructList *pTradePayInstructList = NULL;

         pTrade->getTradePayInstructList (pTradePayInstructList, BF::HOST, false);

         if (pTradePayInstructList)
         {
            BFObjIter iterPayInstruct (*pTradePayInstructList, BF::HOST, false);

            while (!iterPayInstruct.end())
            {
               TradePayInstruct *pTradePayInstruct = dynamic_cast<TradePayInstruct*> (iterPayInstruct.getObject()); 

               DString tpiRID;

               BFData dataRepeat (ifds::DSTC0115_REQRepeat_Record);

               // when there is no pay instruct
               dataRepeat.setElementValue (ifds::AllocRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::AcctLvlRunMode, RUNMODE::UNCHANGED);
               pTradePayInstruct->getField (ifds::TPITrdPayInstrID, tpiRID, BF::HOST);
               fillingData (pTradePayInstruct, &dataRepeat, fieldsInPayInstructAlloc, numFieldsInPayInstructAlloc);               

               BF_OBJ_ACTIVITY tradePayInstructActivity = iterPayInstruct.getKey().getActivity();

               tpiRID.stripLeading ('0');
               if (tradePayInstructActivity == OBJ_ACTIVITY_NONE && tpiRID.empty())
               {
                  tradePayInstructActivity  = OBJ_ACTIVITY_ADDED;
               }

               dataRepeat.setElementValue ( ifds::RecTypRunMode, 
                                            DSTCWorkSession::getRunMode ( tradePayInstructActivity,
                                                                          pTradePayInstruct->hasTransactionUpdates ()));
               request->addRepeat (dataRepeat);
               ++count;
               ++iterPayInstruct;
            }
         }

         //settlement locations.
         TradeSettlementLocationsList *pTradeSettlementLocationsList = NULL;

         //do not create it in here if it doesn't exist
         pTrade->getSettlementLocsList (pTradeSettlementLocationsList, BF::HOST, false);

         if (pTradeSettlementLocationsList)
         {
            BFObjIter iterSettleLocs (*pTradeSettlementLocationsList, BF::HOST, false);

            while (!iterSettleLocs.end())
            {
               DString settleLocId;
               TradeSettlementLocations *pTradeSettlementLocations = dynamic_cast<TradeSettlementLocations*> (iterSettleLocs.getObject());

               BF_OBJ_ACTIVITY settleLocsActivity = iterSettleLocs.getKey().getActivity();

               if( changeObjectActivity(pTrade,settleLocsActivity ) )
               {
                  ++iterSettleLocs;
               };

               BFData dataRepeat (ifds::DSTC0115_REQRepeat_Record);

               dataRepeat.setElementValue (ifds::CommRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::AcctLvlRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::DilRunMode, RUNMODE::UNCHANGED);

               fillingData (pTradeSettlementLocations, &dataRepeat, fieldsInMultiSettleLocations, numFieldsInMultiSettlemLocations);               
               pTradeSettlementLocations->getField (ifds::TransClrSettlUUID, settleLocId, BF::HOST, false);


               if (settleLocsActivity == OBJ_ACTIVITY_NONE && settleLocId == I_("0"))
               {
                  settleLocsActivity  = OBJ_ACTIVITY_ADDED;
               }

               dataRepeat.setElementValue ( ifds::AllocRunMode, 
                                            DSTCWorkSession::getRunMode ( settleLocsActivity, 
                                            pTradeSettlementLocations->hasTransactionUpdates ()));

               request->addRepeat (dataRepeat);
               ++count;
               ++iterSettleLocs;
            }
         }

         // entity aka resp allocaitons

         RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList = NULL;

         //do not create it in here if it doesn't exist
         pTrade->getRESPBenefAllocationList (pRESPBeneficiaryAllocationList, BF::HOST, false);

         if (pRESPBeneficiaryAllocationList)
         {
            BFObjIter iterAllocList (*pRESPBeneficiaryAllocationList, BF::HOST, false);

            while (!iterAllocList.end())
            {
               RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation = dynamic_cast<RESPBeneficiaryAllocation*> (iterAllocList.getObject());

               BF_OBJ_ACTIVITY allocListActivity = iterAllocList.getKey().getActivity();

               if( changeObjectActivity(pTrade,allocListActivity ) )
               {
                  ++iterAllocList;
               };

               BFData dataRepeat (ifds::DSTC0115_REQRepeat_Record);

               dataRepeat.setElementValue (ifds::AllocRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::CommRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::AcctLvlRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::DilRunMode, RUNMODE::UNCHANGED);


               fillingData (pRESPBeneficiaryAllocation, &dataRepeat, fieldsInEntityAllocations, numFieldsInEntityAllocations);               
               //pTradeSettlementLocations->getField (ifds::TransClrSettlUUID, settleLocId, BF::HOST, false);


               // uncomment whne uuis gets available
               //if (allocListActivity == OBJ_ACTIVITY_NONE /*&& settleLocId == I_("0")*/)
               //{
               //   allocListActivity  = OBJ_ACTIVITY_ADDED;
               //}

               dataRepeat.setElementValue ( ifds::EntityAllocRunMode, 
                                            DSTCWorkSession::getRunMode ( allocListActivity, 
                                            pRESPBeneficiaryAllocation->hasTransactionUpdates ()));

               request->addRepeat (dataRepeat);
               ++count;
               ++iterAllocList;
            }
         }

         //
         // RESP Transfer data:

         RESPTransferList *pRESPTransferList = NULL;

         //do not create it in here if it doesn't exist
         pTrade->getRESPTransferList (pRESPTransferList, BF::HOST, false);

         if (pRESPTransferList)
         {
            BFObjIter iterRESPTransferList (*pRESPTransferList, BF::HOST, false);

            while (!iterRESPTransferList.end())
            {
               RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*> (iterRESPTransferList.getObject());

               BF_OBJ_ACTIVITY transferActivity = iterRESPTransferList.getKey().getActivity();

               if( changeObjectActivity(pTrade,transferActivity ) )
               {               
                  ++iterRESPTransferList;
               };

               BFData dataRepeat (ifds::DSTC0115_REQRepeat_Record);

               dataRepeat.setElementValue (ifds::AllocRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::CommRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::AcctLvlRunMode, RUNMODE::UNCHANGED);
               dataRepeat.setElementValue (ifds::DilRunMode, RUNMODE::UNCHANGED);


               fillingData (pRESPTransfer, &dataRepeat, fieldsInRESPTransfer, numFieldsInRESPTransfer);
               //pTradeSettlementLocations->getField (ifds::TransClrSettlUUID, settleLocId, BF::HOST, false);


               // uncomment whne uuis gets available
               //if (allocListActivity == OBJ_ACTIVITY_NONE /*&& settleLocId == I_("0")*/)
               //{
               //   allocListActivity  = OBJ_ACTIVITY_ADDED;
               //}

               dataRepeat.setElementValue ( ifds::RESPTrfAllocRunMode, 
                                            DSTCWorkSession::getRunMode ( transferActivity, 
                                            pRESPTransfer->hasTransactionUpdates ()));

               request->addRepeat (dataRepeat);
               ++count;
               ++iterRESPTransferList;
            }
         }

         GIInvestmentDetailsList *pGIInvestmentDetailsList;
         pTrade->getGIInvestmentDetails(pGIInvestmentDetailsList, BF::HOST, false);
         
         DString dstrRedemOrder;
         pTrade->getField(ifds::RedemOrder, dstrRedemOrder, BF::HOST, false);

         if(pGIInvestmentDetailsList && dstrRedemOrder != I_("FM"))
         {
            BFObjIter iterGIInvestmentDetails (*pGIInvestmentDetailsList, BF::HOST, false); 

            while (!iterGIInvestmentDetails.end())
            {
               GIInvestmentDetails *pGIInvestmentDetails = dynamic_cast<GIInvestmentDetails*> (iterGIInvestmentDetails.getObject()); 

               DString tpiRID;
               
               DString amount;
               pGIInvestmentDetails->getField(ifds::SelInvAmount, amount, BF::HOST);
               
               if(amount != I_("") && amount != I_("0"))
               {

                  BFData dataRepeat (ifds::DSTC0115_REQRepeat_Record);
                  
                  dataRepeat.setElementValue (ifds::SelInvRunMode, RUNMODE::ADDED);

                  fillingData (pGIInvestmentDetails, &dataRepeat, fieldsInGIInvestDetails, numfieldsInGIInvestDetails);               
                  dataRepeat.setElementValue (ifds::RecordType, I_("SelInvAlloc"));
                  dataRepeat.setElementValue (ifds::AllocRunMode, RUNMODE::UNCHANGED);
                  dataRepeat.setElementValue (ifds::AcctLvlRunMode, RUNMODE::UNCHANGED);

                  request->addRepeat (dataRepeat);
                  ++count;
               }
               ++iterGIInvestmentDetails;
            }
         }

         EstateAllocationList *pEstateAllocationList;
         pTrade->getEstateAllocationList(pEstateAllocationList, BF::HOST, false);

         if(pEstateAllocationList)
         {
            BFObjIter iterEstateAllocationList(*pEstateAllocationList, BF::HOST, false);

            while (!iterEstateAllocationList.end())
            {
               EstateAllocation *pEstateAllocation = dynamic_cast<EstateAllocation*> (iterEstateAllocationList.getObject()); 

               DString tpiRID;
               
               DString amount;
               pEstateAllocation->getField(ifds::SelInvAmount, amount, BF::HOST);
               
//               if(amount != I_("") && amount != I_("0"))
               {
                  BFData dataRepeat (ifds::DSTC0115_REQRepeat_Record);
                  DString dstrBenefRecType;
                  pEstateAllocation->getField(ifds::BenefRecType, dstrBenefRecType, BF::HOST);
                  if(dstrBenefRecType == I_("T"))
                  {
                     dataRepeat.setElementValue (ifds::SelInvRunMode, RUNMODE::MODIFIED);
                     dataRepeat.setElementValue (ifds::BenefRunMode, RUNMODE::MODIFIED);
                  }
                  else if(dstrBenefRecType == I_("D"))
                  {
                     dataRepeat.setElementValue (ifds::SelInvRunMode, RUNMODE::ADDED);
                     dataRepeat.setElementValue (ifds::BenefRunMode, RUNMODE::ADDED);
                  }

                  fillingData (pEstateAllocation, &dataRepeat, fieldsInEstateAllocation, numfieldsInEstateAllocation);               
                  dataRepeat.setElementValue (ifds::RecordType, I_("EstateAlloc"));
                  dataRepeat.setElementValue (ifds::AllocRunMode, RUNMODE::UNCHANGED);
                  dataRepeat.setElementValue (ifds::AcctLvlRunMode, RUNMODE::UNCHANGED);

                  request->addRepeat (dataRepeat);
                  ++count;
               }
               ++iterEstateAllocationList;
            }
         }

         request->setElementValue(ifds::RepeatCount, DString::asString (count), false, false);
	    
      }

      //maturity instructions...
      DSTCMatSweepInstrTrxnBuilder::buildTransactions (workSession, pTrade, pTrxnContainer, objActivity) ;

	  //pending trade error...
      DSTCPendingTradeErrorTrxnBuilder::buildTransactions (workSession, pTrade, pTrxnContainer, objActivity) ;

      ++iterTradesList;
   }  // while loop
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************************
bool DSTCTradesTrxnBuilder::changeObjectActivity(Trade* pTrade,BF_OBJ_ACTIVITY& ObjActivity )
{
   bool bSkipBuilder = false;
   if ((pTrade->isRebook() || pTrade->isRefund()) && ObjActivity == OBJ_ACTIVITY_DELETED ) //skip builder in this case
   {
      bSkipBuilder = true;
   }
   else if ((pTrade->isRebook() || pTrade->isRefund()) && ObjActivity == OBJ_ACTIVITY_NONE )    // change it to added
   {
      ObjActivity = OBJ_ACTIVITY_ADDED;
   }
   return bSkipBuilder;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCTradesTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.70   09 Aug 2012 17:26:40   if991250
 * Estate Allocation - Send Modify for existing records
 * 
 *    Rev 1.69   26 Jul 2012 17:21:04   if991250
 * Added Estate Allocation
 * 
 *    Rev 1.68   Mar 09 2012 17:41:04   if991250
 * GIInvestmentDetails
 * 
 *    Rev 1.67   Mar 09 2012 10:51:14   if991250
 * fix for the RepeatCount
 * 
 *    Rev 1.66   Mar 08 2012 11:17:10   if991250
 * update for GI Investments
 * 
 *    Rev 1.65   Mar 08 2012 09:57:30   if991250
 * GI Money Out
 * 
 *    Rev 1.64   Jan 18 2012 16:16:56   jankovii
 * IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
 * 
 *    Rev 1.63   Oct 06 2011 10:39:20   panatcha
 * P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
 * 
 *    Rev 1.62   Jul 15 2011 12:11:26   jankovii
 * P0184541_FN01_InvescoQESItrans - revesed code that was handling 25+ records.
 * 
 *    Rev 1.61   Jun 28 2011 10:26:18   panatcha
 * P0184541_FN01_InvescoQESItrans
 * 
 *    Rev 1.60   Jun 24 2010 07:42:54   dchatcha
 * PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen.
 * 
 *    Rev 1.59   Jun 08 2010 10:52:00   jankovii
 * IN 2124688 - PETP0165541 -  Dep Code 17 - Account Level Override.
 * 
 *    Rev 1.58   Apr 30 2010 16:39:44   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.57   Apr 23 2010 16:09:00   jankovii
 * PET0165541 FN01 QESI RESP Trading
 * 
 *    Rev 1.56   Apr 20 2010 16:11:28   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.55   Mar 25 2010 13:57:38   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.54   Aug 11 2009 13:51:32   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.53   Aug 30 2007 15:24:20   jankovii
 * PET 2360 FN11 - Dilution.
 * 
 *    Rev 1.52   Sep 21 2006 01:50:36   popescu
 * STP PET 2217/13
 * 
 *    Rev 1.51   Sep 18 2006 00:25:18   popescu
 * STP Pet 2217/13
 * 
 *    Rev 1.50   Oct 05 2005 15:32:56   porteanm
 * Incident 420984 - Replaced 339.Repeat.Version with 339.Repeat.DilVersion.
 * 
 *    Rev 1.49   Jul 11 2005 20:14:20   AGUILAAM
 * PET1235_FN01: dilution, part of Rebook/Cancellation
 * 
 *    Rev 1.48   Jul 11 2005 11:06:42   AGUILAAM
 * PET1235: dilution, part of rebook/cancellation
 * 
 *    Rev 1.47   Jul 08 2005 09:28:22   Yingbaol
 * PET1235,FN01: transaction cancellation rebook
 * 
 *    Rev 1.46   Feb 17 2005 17:05:02   aguilaam
 * incident # 239846 - pass and display RenunAmount (checked in for Serban)
 * 
 *    Rev 1.45   Dec 07 2004 01:37:30   popescu
 * PET 1117/56 trades processing/modify trade
 * 
 *    Rev 1.44   Dec 01 2004 19:50:18   popescu
 * PET 1117/06, trades/fees processing, incorporate fees in trades transaction builder, and added method to copy fee values onto the trades fee fields for cycle processing
 * 
 *    Rev 1.43   Nov 14 2004 14:33:54   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.42   Jan 13 2004 16:06:44   popescu
 * PET 910, System Integration Testing, Rel_55.0.0.2
 * Fix involved allows back dated trades when modifying a pending trade; issue occurred due to a previous fix where the WorkSessionTradesList is now retrieved using an 'idDataGroup' not equal with BF::HOST.
 * 
 *    Rev 1.41   Sep 08 2003 17:10:56   popescu
 * PET 809_FN_02, fixes after performing integrated unit testing with the view team
 * 
 *    Rev 1.40   Sep 01 2003 21:32:20   popescu
 * PET 809, FN 02 CIBC Multi Fund Transfer
 * 
 *    Rev 1.39   Mar 21 2003 18:07:18   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.38   Oct 09 2002 23:54:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.37   Sep 17 2002 17:48:22   WINNIE
 * Sync up fixes for 10009490
 * 
 *    Rev 1.36   Sep 12 2002 15:23:18   HSUCHIN
 * sync up with 1.34.1.0
 * 
 *    Rev 1.35   Aug 29 2002 12:55:38   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.34   24 May 2002 15:44:30   KOVACSRO
 * new allocation design changes.
 * 
 *    Rev 1.33   22 May 2002 18:28:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.32   08 May 2002 15:15:08   KOVACSRO
 * Field name changes.
 * 
 *    Rev 1.31   29 Apr 2002 16:22:28   KOVACSRO
 * new Trade allocations.
 * 
 *    Rev 1.30   08 Mar 2002 11:35:44   KOVACSRO
 * same for FundAllocationList : we don't want to create objects in transaction builder (if already created it's a different story)
 * 
 *    Rev 1.29   07 Mar 2002 12:11:12   KOVACSRO
 * If account allocations haven't already been created, don't create them here.
 * 
 *    Rev 1.28   Feb 25 2002 18:55:38   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.27   13 Feb 2002 11:25:50   HSUCHIN
 * bug fix for split commission, added a new field splitcommrid.
 * 
 *    Rev 1.26   24 Jan 2002 15:58:50   HSUCHIN
 * potential bug fix.   The DistribDetlRid is not compared rather than the DistribDetlVer
 * 
 *    Rev 1.25   29 Nov 2001 16:44:36   HSUCHIN
 * bug fix for builder when modifying a trade from single to multiple fund
 * 
 *    Rev 1.24   09 Nov 2001 10:05:28   HSUCHIN
 * bug fix, split commission is now initialized to null
 * 
 *    Rev 1.23   05 Nov 2001 10:46:08   HSUCHIN
 * bug fix for Split Commission building.  The DistribDetlVer is not set in the case of a single fund, hence cannot be used to determine the state of the Fund Allocation.
 * 
 *    Rev 1.22   Oct 25 2001 17:53:50   ZHANGCEL
 * Fixed the bug of Rel43-QA Requset 438
 * 
 */