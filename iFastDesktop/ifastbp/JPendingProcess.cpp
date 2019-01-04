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
// ^FILE   : JPendingProcess.cpp
// ^AUTHOR :  Yongmei Feng
// ^DATE   : 09/05/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : JPendingProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "jpendingprocess.hpp"
#include <ifastcbo\acqfeeinquiry.hpp>
#include <ifastcbo\currencyclass.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\addresslist.hpp>
#include "jpendingprocessincludes.h"
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_JPENDING;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< JPendingProcess > processCreator( CMD_BPROC_JPENDING );

namespace
{
   const I_CHAR *CLASSNAME = I_( "JPendingProcess" );
}

namespace PENDINGLIT
{
   // Trace literals
   extern const I_CHAR * const pACCOUNTNUM         = I_( "AccountNum" );
   extern const I_CHAR * const pSHAREHOLDERNUM     = I_( "ShareholderNum" );
   extern const I_CHAR * const pFUNDCODE           = I_( "FundCode" );
   extern const I_CHAR * const pCLASSCODE          = I_( "ClassCode" );
   extern const I_CHAR * const pNUMENTRY           = I_( "NumEntry" );
   extern const I_CHAR * const pTRANSTYPE          = I_( "TransType" );
   extern const I_CHAR * const pTRANSNUM           = I_( "TransNum" );
   extern const I_CHAR * const pTRADEDATE          = I_( "TradeDate" );
   extern const I_CHAR * const pBROKERCODE         = I_( "BrokerCode" );
   extern const I_CHAR * const pBRANCHCODE         = I_( "BranchCode" );
   extern const I_CHAR * const pSLSREPCODE         = I_( "SlsRepCode" );
   extern const I_CHAR * const pPENDINGDETAILSONLY = I_( "PendingDetailsOnly" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ElongName1;
   extern CLASS_IMPORT const BFTextFieldId ElongName2;
   extern CLASS_IMPORT const BFTextFieldId ToBrokerCode;
   extern CLASS_IMPORT const BFTextFieldId ToSlsRepCode;
   extern CLASS_IMPORT const BFTextFieldId FLongName;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319JPendingProcess::JPendingProcess() : 
JPendingProcess::JPendingProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pPendingTradeList( NULL),
_pTranslationList( NULL ),
_pmgmtcooptions( NULL ),
_pFundDetailList( NULL ),
_pAddressList(NULL),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::FUND_DETAIL_LIST, true );
   addContainer( IFASTBP_PROC::TRANSLATION_LIST, true );
   addContainer( IFASTBP_PROC::PENDING_LIST, true, BF::NullContainerId, false, I_( "PendingList" ) );
   addContainer( IFASTBP_PROC::PENDING_DETAILS, false, BF::NullContainerId, false, I_( "PendingDetails" ) );
   addContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, false );
   addContainer( IFASTBP_PROC::ADDR_LIST, true );
   addContainer( IFASTBP_PROC::ACQFEEINQUIRY_CBO, false );

   addFieldDetails( ifds::CurrBusDate, IFASTBP_PROC::MGMTCOOPTIONS_LIST );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUND_DETAIL_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::FUND_DETAIL_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::FUND_DETAIL_LIST );
   addFieldDetails( ifds::LoadType, IFASTBP_PROC::FUND_DETAIL_LIST );

   addFieldDetails(ifds::LangCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundName, IFASTBP_PROC::TRANSLATION_LIST );

   // list, vw 53
   addFieldDetails( ifds::rxFundCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::rxClassCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TradeDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransType, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransTypeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransNum, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AccountTo, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AcctToName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FundTo, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ClassToCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Amount, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AmountType, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AmountTypeDesc, IFASTBP_PROC::PENDING_LIST );
   //addFieldDetails( ifds::GrossOrNet, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::GrossNetMethod, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OrderType, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::WireOrdNum, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BatchUser, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BatchName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BatchTrace, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::GoodBad, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleCurrency, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::rxAcctNum, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FundName, IFASTBP_PROC::PENDING_LIST, SUBCLASS_PROCESS );
   // cbo, vw 54
   addFieldDetails( ifds::Broker, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Branch, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SlsrepCode, IFASTBP_PROC::PENDING_LIST );
//	addFieldDetails( DBR::SettleCurrency, PENDING_LIST );
   addFieldDetails( ifds::SettleCurrName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExchRate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Fee, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FlatPercent, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FeeCurrency, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BELFee, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AdminFeeAmt, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OverrideDSC, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OverrideDSCDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OverrideAmt, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OverrideTax, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FedRate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransRatePUDFed, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ProvRate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransRatePUDProv, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ProvSales, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ProvSalesName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DepositType, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DepositTypeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RedCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RedCodeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Payment, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PayType2, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PayTypeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AddrCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AddrLine, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SuppressCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ChqSupCodeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OrderSource, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OrderSrcDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleSource, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleSrcDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SrcOfFund, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SrcOfFundDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SrcOfAccount, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleType, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleTypeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExpGNSettle, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettledBy, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettledByDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RoundFlag, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RoundFlagDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CreditFreq, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CreditFreqDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExtraCommission, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CertRequired, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CertIssued, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ConfirmRequired, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OnStmt, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RecptIssued, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExclMFCSSettle, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::GuaranteeDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::MaturityDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::InterestRate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BrokerName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BranchName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SlsrepName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SlsrepAltName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DepId, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Remarks1, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Remarks2, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Remarks3, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RejCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RejCodeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Accountable, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AcctableDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DepositDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TimeStamp, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PendingRid, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::InitPurch, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BackDatedReason, IFASTBP_PROC::PENDING_LIST );

   addFieldDetails( ifds::BrokerCode, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::SlsrepCode, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::Fee, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::BELFee, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::TransType, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::AccountTo, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::FundTo, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::WireOrdNum, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::rxFundCode, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::rxClassCode, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::Amount, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::AmountType, IFASTBP_PROC::PENDING_DETAILS );
   //addFieldDetails( ifds::GrossOrNet, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::GrossNetMethod, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Baycom, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::BayComTo, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::ToBrokerCode, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::ToSlsRepCode, IFASTBP_PROC::PENDING_DETAILS );
   addFieldDetails( ifds::FundName, IFASTBP_PROC::PENDING_DETAILS, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ElongName2, IFASTBP_PROC::PENDING_DETAILS, SUBCLASS_PROCESS );


   addFieldDetails( ifds::LastName, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FirstName, BF::NullContainerId, SUBCLASS_PROCESS );

   addFieldDetails( ifds::AddrCode,      IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::AddrCodeDesc,    IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::Name1,       IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::Name2,       IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::AddrLine1,     IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::AddrLine2,     IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::AddrLine3,     IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::AddrLine4,     IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::AddrLine5,     IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::PostalCode,    IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::CountryCode,   IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::City,        IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::CountryName,   IFASTBP_PROC::ADDR_LIST );
   addFieldDetails( ifds::AddrStatus,   IFASTBP_PROC::ADDR_LIST );

   addFieldDetails( ifds::MaxFee, IFASTBP_PROC::ACQFEEINQUIRY_CBO, SUBCLASS_PROCESS );
   addFieldDetails( ifds::MaxFeeType, IFASTBP_PROC::ACQFEEINQUIRY_CBO, SUBCLASS_PROCESS );

}

//******************************************************************************

JPendingProcess::~JPendingProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   delete _pPendingTradeList;
   _pPendingTradeList = NULL;
   if( _pAddressList ) delete _pAddressList;
   _pAddressList = NULL;

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool JPendingProcess::doGetData(
                               GenericInterface * ,
                               BFData * 
                               ) const
{
   _pPendingTradeList->getMore();
   return(true);
}

//******************************************************************************

SEVERITY JPendingProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( PENDINGLIT::pACCOUNTNUM, _AccountNum );
      getParameter( PENDINGLIT::pFUNDCODE, _FundCode );
      getParameter( PENDINGLIT::pCLASSCODE, _ClassCode );
      getParameter( PENDINGLIT::pNUMENTRY, _NumEntry );
      getParameter( PENDINGLIT::pSHAREHOLDERNUM, _ShareholderNum);
      getParameter( PENDINGLIT::pTRANSTYPE, _TransType);
      getParameter( PENDINGLIT::pTRANSNUM, _TransNum);
      getParameter( PENDINGLIT::pTRADEDATE, _TradeDate);
      getParameter( PENDINGLIT::pBROKERCODE, _BrokerCode);
      getParameter( PENDINGLIT::pBRANCHCODE, _BranchCode);
      getParameter( PENDINGLIT::pSLSREPCODE, _SlsRepCode);
      getParameter( PENDINGLIT::pPENDINGDETAILSONLY, _pPendingDetailsOnly );

      DString dstrTrack,dstrActivity;
      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");
      _AccountNum.stripAll();
      _BrokerCode.stripAll();
      _BranchCode.stripAll();
      _SlsRepCode.stripAll();
      _FundCode.stripAll().upperCase();
      _ClassCode.stripAll().upperCase();
      _NumEntry.stripAll();

      _ShareholderNum.stripAll();
      _TransNum.stripAll().stripLeading( '0' );
      _TransType.stripAll();
      _TradeDate.stripAll();

      MgmtCo &mgmtCoOut = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo();

      _pFundDetailList = NULL;
      sevRtn = mgmtCoOut.getFundDetailList( _pFundDetailList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUND_DETAIL_LIST, _pFundDetailList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      sevRtn = mgmtCoOut.getTranslationList( _pTranslationList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::TRANSLATION_LIST, _pTranslationList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      sevRtn = mgmtCoOut.getMgmtCoOptions( _pmgmtcooptions );

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, _pmgmtcooptions );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      if( _pPendingDetailsOnly == I_( "Y" ) )
      {
         PendingTradeDetails *pPendingTradeDetails = new PendingTradeDetails( *getBFWorkSession() );
         sevRtn = pPendingTradeDetails->getDetails( _AccountNum, _FundCode, _ClassCode, _TransType, _TransNum, _TradeDate );
         if( WARNING >= sevRtn )
         {
            setContainer( IFASTBP_PROC::PENDING_DETAILS, pPendingTradeDetails );
         }
         else
         {
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
      else
      {
         _pPendingTradeList = new PendingTradeList( *getBFWorkSession() );
         sevRtn = _pPendingTradeList->init( _AccountNum, _BrokerCode, _BranchCode,
                                            _SlsRepCode,_NumEntry,dstrTrack,dstrActivity );
         if( WARNING >= sevRtn )
         {
            setContainer( IFASTBP_PROC::PENDING_LIST, _pPendingTradeList );
         }
         else
         {
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }


   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool JPendingProcess::doMoreRecordsExist(
                                        GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer 
                                        )
{
   return( _pPendingTradeList->doMoreRecordsExist() );
}

//******************************************************************************

E_COMMANDRETURN JPendingProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************

void JPendingProcess::setCurrentListItem(
                                        const GenericInterface *rpGICaller,
                                        const BFContainerId& idList,
                                        const DString& strListItemKey
                                        )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM ); 
   AbstractProcess::setCurrentListItem( rpGICaller, idList, strListItemKey );
   DString _shrnum,_secondValue;
   SEVERITY sevRtn = SEVERE_ERROR;

   if( idList == IFASTBP_PROC::PENDING_LIST )
   {


      BFObjIter bfIter( *_pPendingTradeList, getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );
      bfIter.getObject()->getField(ifds::ShrNum,_shrnum,BF::HOST);
      _shrnum.stripAll().stripLeading('0');

      _pPendingTradeList->getItem( strListItemKey, BF::HOST );

      if( _pAddressList )
      {
         delete _pAddressList; _pAddressList = NULL;
      }
      _pAddressList = new AddressList( *getBFWorkSession() );
      sevRtn = _pAddressList->init( _shrnum, true);
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::ADDR_LIST, _pAddressList );
      }

      bfIter.getObject()->getField(ifds::rxAcctNum,_acctnum,BF::HOST);
      _acctnum.stripAll().stripLeading('0');
   }
}

void JPendingProcess::doGetField(
                                const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                DString &strValueOut,
                                bool bFormatted
                                ) const
{  
   DString strEntityName;
   DString acctnum  = _acctnum; 

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( idField == ifds::FirstName || idField == ifds::LastName )
   {
      dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), acctnum, strEntityName );
      if( idField == ifds::LastName )
         strValueOut.assign( strEntityName, 0, strEntityName.find(';'));
      else if( idField == ifds::FirstName )
         strValueOut.assign(strEntityName, strEntityName.find(';') +1, strEntityName.length() + 1);
   }

   JPendingProcess *rpNonConstThis = const_cast < JPendingProcess*> ( this );

   if( idContainer == IFASTBP_PROC::ACQFEEINQUIRY_CBO && ( idField == ifds::MaxFee || idField == ifds::MaxFeeType ) )
   {
      DString fundCode, classCode;
      rpNonConstThis->getField( rpGICaller, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, fundCode, false );
      rpNonConstThis->getField( rpGICaller, IFASTBP_PROC::PENDING_LIST, ifds::rxClassCode, classCode, false );

      AcqFeeInquiry *pAcqFeeInquiry = new AcqFeeInquiry( *dstcWorkSession );
      pAcqFeeInquiry->init( NULL, NULL, NULL, NULL, NULL, fundCode, classCode, NULL, NULL, NULL, NULL );
      pAcqFeeInquiry->getField( idField, strValueOut, idDataGroup, bFormatted );

      if( idField == ifds::MaxFeeType && strValueOut == NULL_STRING )
         strValueOut = I_( "0" );

      if( idField == ifds::MaxFee )
      {
         DString dstrCurrency, maxFeeType;

         pAcqFeeInquiry->getField( ifds::MaxFeeType, maxFeeType, idDataGroup, bFormatted );

         if( maxFeeType == I_( "0" ) ) // Flat
         {
            if( fundCode.strip() != NULL_STRING && classCode.strip() != NULL_STRING )
               CurrencyClass::getFundCurrency( *dstcWorkSession, fundCode, classCode, dstrCurrency );

            CurrencyClass::getFormattedValue( *dstcWorkSession, strValueOut, dstrCurrency );
         }
      }
      delete pAcqFeeInquiry; pAcqFeeInquiry = NULL;
   }
   else if( idField == ifds::FundName && ( idContainer == IFASTBP_PROC::PENDING_LIST || idContainer == IFASTBP_PROC::PENDING_DETAILS ) )
   {
      JPendingProcess *rpNonConstThis = const_cast < JPendingProcess*> ( this );
      DString strFundCode, strClassCode;
      rpNonConstThis->getField( this, idContainer, ifds::rxFundCode, strFundCode, true );
      rpNonConstThis->getField( this, idContainer, ifds::rxClassCode, strClassCode, true );
      DString dstLocaleStr = ClientLocaleContext::get().getLocale();
      FundMasterList *pFundMasterList;
      dstcWorkSession->getMgmtCo().getFundMasterList( pFundMasterList );
      if( pFundMasterList )
      {
         if( dstLocaleStr != I_("frCA") )
            pFundMasterList->getFundName (strFundCode, ifds::ElongName1, strValueOut);
         else
            pFundMasterList->getFundName( strFundCode, ifds::FLongName, strValueOut);     
      }
   }
   else if( idField == ifds::ElongName2 && idContainer == IFASTBP_PROC::PENDING_DETAILS )
   {
      JPendingProcess *rpNonConstThis = const_cast < JPendingProcess*> ( this );
      DString strFundCode, strClassCode;
      rpNonConstThis->getField( this, idContainer, ifds::FundTo, strFundCode, true );
      FundMasterList *pFundMasterList;
      dstcWorkSession->getMgmtCo().getFundMasterList( pFundMasterList );
      if( pFundMasterList )
      {
         pFundMasterList->getFundName( strFundCode, ifds::ElongName1, strValueOut);
      }
   }
}

void *JPendingProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   SEVERITY sevRtn1 = NO_CONDITION;

   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case PENDING_DETAILS:
      if( IFASTBP_PROC::PENDING_DETAILS == idContainer )
      {
         {
            BFObjIter bfIter(*_pPendingTradeList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
            while( !bfIter.end() )
            {
               PendingTradeDetails *pPendingTradeDetails = dynamic_cast < PendingTradeDetails* > ( bfIter.getObject() );
               DString strTransNum;
               pPendingTradeDetails->getField( ifds::TransNum, strTransNum, idDataGroup, true );
               if( strTransNum.stripLeading( '0' ) == _TransNum )
               {
                  DString strFund, strClass, strTransType, strTradeDate;

                  pPendingTradeDetails->getField( ifds::rxFundCode, strFund, idDataGroup, true );
                  pPendingTradeDetails->getField( ifds::rxClassCode, strClass, idDataGroup, true );
                  pPendingTradeDetails->getField( ifds::TransType, strTransType, idDataGroup, false );
                  pPendingTradeDetails->getField( ifds::TradeDate, strTradeDate, idDataGroup, true );

                  pPendingTradeDetails->getDetails( _AccountNum, strFund, strClass, strTransType, strTransNum, strTradeDate );
                  ptr = pPendingTradeDetails;
                  break;
               }
            }
         }
//CP20030319            break;
//CP20030319      }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JPendingProcess.cpp-arc  $
 // 
 //    Rev 1.33   Aug 29 2008 09:53:52   daechach
 // in#1355618 - recode fix for 1259584 Gross\net
 // 
 //    Rev 1.32   Dec 13 2004 14:16:42   popescu
 // PET 1117/56, ChqSupCode-->SuppressCode, view 54
 // 
 //    Rev 1.31   Dec 07 2004 21:20:12   popescu
 // PET 1117/06, pending trades/fees fixes, add-ons
 // 
 //    Rev 1.30   Nov 22 2004 13:08:40   popescu
 // PET 1117/56. fees processing
 // 
 //    Rev 1.29   Nov 17 2004 15:18:54   popescu
 // PET 1117/56, removed 'getField' method at the fund master list level, 
 // 
 //    Rev 1.28   Mar 21 2003 17:44:12   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.27   Feb 12 2003 12:51:04   FENGYONG
 // pts ticket: 10013444
 // 
 //    Rev 1.26   Dec 11 2002 13:35:24   FENGYONG
 // Add fields toBrokerCode and toSlsRepCode
 // 
 //    Rev 1.25   Oct 30 2002 10:30:52   YINGBAOL
 // change field name according to Yongmei's requirement
 // 
 //    Rev 1.24   Oct 09 2002 23:53:26   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.23   Aug 29 2002 16:45:04   SMITHDAV
 // Condition split.
 // 
 //    Rev 1.22   Aug 29 2002 12:54:30   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.21   22 May 2002 18:24:36   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.20   Apr 26 2002 10:42:42   FENGYONG
 // Add BaycomTo
 // 
 //    Rev 1.19   27 Mar 2002 19:55:16   PURDYECH
 // Process/WindowFactory overhaul
 // 
 //    Rev 1.18   Mar 20 2002 10:46:00   FENGYONG
 // Add BayCom
 // 
 //    Rev 1.17   Nov 13 2001 12:24:44   VASILEAD
 // Added fund name info to funds transfer
 // 
 //    Rev 1.16   03 May 2001 14:05:32   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.15   Apr 04 2001 14:16:32   FENGYONG
 // clear memery after used
 // 
 //    Rev 1.14   Mar 18 2001 18:18:12   VASILEAD
 // Fixes for UAT release
 // 
 //    Rev 1.13   Mar 12 2001 12:58:44   VASILEAD
 // Modified for FUNDcom release
 // 
 //    Rev 1.12   Jan 31 2001 16:05:30   YINGBAOL
 // to prevent  track para from being empty 
 // 
 //    Rev 1.11   Jan 25 2001 13:58:14   YINGBAOL
 // track pending trade list
 // 
 //    Rev 1.10   Jan 23 2001 15:17:48   YINGBAOL
 // add eTrack
 // 
 //    Rev 1.9   Jan 17 2001 12:08:10   VASILEAD
 // Added workSessionId param for MgmtCo::getMgmtCoOptions()
 // 
 //    Rev 1.8   Jan 02 2001 11:52:42   VASILEAD
 // Fixed DSC Override bug
 // 
 //    Rev 1.7   15 Dec 2000 12:43:42   PURDYECH
 // Use precompiled header stdafx.h.
 // Removed unnecessary header files.
 // 
 //    Rev 1.6   Dec 14 2000 15:53:36   FENGYONG
 // remove #3
 // 
 //    Rev 1.5   Dec 13 2000 10:57:52   FENGYONG
 // Add filed PayType2 and change #17 and #54 DataSet  from PayType to PayType2
 // 
 //    Rev 1.4   Oct 04 2000 13:49:54   FENGYONG
 // Add EntityList to get firstname and lastname
 // 
 //    Rev 1.3   Sep 16 2000 13:54:00   FENGYONG
 // Add fields
 // 
 //    Rev 1.2   Sep 14 2000 16:16:08   YINGZ
 // add new field
 // 
 //    Rev 1.1   Sep 13 2000 16:54:36   FENGYONG
 // Add brokercode, branchcode,slsrep
 // 
 //    Rev 1.0   Sep 07 2000 11:56:14   FENGYONG
 // Initial revision.
 *
 */
