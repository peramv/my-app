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
// ^FILE   : AcctTransProcess.cpp
// ^AUTHOR :  Yongmei Feng
// ^DATE   : 03/11/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AcctTransProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "jaccttransprocess.hpp"
#include "fillsearchcriteriaprocessincludes.h"
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include "jaccttransprocessincludes.h"
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\translationlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "etrackheader.h"
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0022_vw.hpp>
#include <ifastdataimpl\dse_dstc0017_vw.hpp>
#include <ifastdataimpl\dse_dstc0136_vw.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_TRANS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AcctTransProcess > processCreator( CMD_BPROC_ACCT_TRANS );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "AcctTransProcess" );

   const I_CHAR *Y = I_( "Y" );
   const I_CHAR *N = I_( "N" );

   const I_CHAR *pALLFUND = I_( "AllFundMode" );
   const I_CHAR *pACCOUNTNUM = I_( "AccountNum" );
   const I_CHAR *pSHAREHOLDERNUM = I_( "ShareholderNum" );
   const I_CHAR *pFUNDCODE = I_( "FundCode" );
   const I_CHAR *pCLASSCODE = I_( "ClassCode" );
   const I_CHAR *pNUMENTRY = I_( "NumEntry" );
   const I_CHAR *pFROMDATE = I_( "FromDate" );
   const I_CHAR *pTODATE = I_( "ToDate" );
   const I_CHAR *pNEXTKEY = I_( "NextKey" );
   const I_CHAR *pUSEDATEFLAG = I_( "UseDateFlag" );
   const I_CHAR *ACCT_TRANS = I_( "accttrans" );
   const I_CHAR *TRANS_DTL = I_( "transdtl1" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

namespace ACCTTRANSLIT //entity search literals
{
   const I_CHAR * const ACCOUNT_NUM = I_( "TXAccountNum" ); 
   const I_CHAR * const FUND_CODE = I_( "TXFundCode" ); 
   const I_CHAR * const CLASS_CODE = I_( "TXClassCode" ); 
   const I_CHAR * const NUM_ENTRY = I_( "NumEntry" ); 
   const I_CHAR * const ALL_FUND_MODE = I_( "AllFundMode" );  
   const I_CHAR * const SHAREHOLDER_NUM = I_( "SrchShrNum" ); 
   const I_CHAR * const TRANSID = I_( "TXTransId" );
   const I_CHAR * const TRANS_DESC = I_( "TransDesc" );
   const I_CHAR * const OVERRIDE_REPEATS = I_( "OverrideRepeats" ); 
}


namespace ETRACK
{
   const I_CHAR * const TRACK = I_("ETRACK");
   const I_CHAR * const ACTIVITY = I_("ACTIVITY");  
   const I_CHAR * const YES_TRACK = I_("Y");    
   const I_CHAR * const NO_TRACK = I_("N");  


}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ElongName1;
   extern CLASS_IMPORT const BFTextFieldId ElongName2;
   extern CLASS_IMPORT const BFTextFieldId ToBrokerCode;
   extern CLASS_IMPORT const BFTextFieldId ToSlsRepCode;
   extern CLASS_IMPORT const BFTextFieldId FLongName;
}

//****************************************************
// TransactionHistory(view 17) and TransactionDetail(view 22) are used  
//to track user's activity 
//

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319AcctTransProcess::AcctTransProcess() : 
AcctTransProcess::AcctTransProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pTransHistoryList( NULL ),
_pTransDetails( NULL ),
_pFundDetailList( NULL ),
_pTranslationList( NULL ),
_pmgmtcooptions( NULL ),
_pMFAccount( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::TRANS_LIST, true, BF::NullContainerId, false, I_( "TransactionList" ) );
   addContainer( IFASTBP_PROC::TRANS_DETAILS, false, BF::NullContainerId, false, I_( "TransactionDetails" ) );
   addContainer( IFASTBP_PROC::FUNDSRCH_LIST, true );
   addContainer( IFASTBP_PROC::DEDUCTION_LIST, true, BF::NullContainerId, false, I_( "DeductionList" ) );
   addContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, false );
   addContainer( IFASTBP_PROC::TRANSLATION_LIST, true );
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false );

   addFieldDetails( ifds::CurrBusDate, IFASTBP_PROC::MGMTCOOPTIONS_LIST );
// from list vw 17
   addFieldDetails( ifds::TransId, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TransType, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TransTypeDesc, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TransNum, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TradeDate, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleDate, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Settled, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::GrossAmt, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::NetAmt, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::UnitPrice, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Units, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::UnitBalance, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::rxFundCode, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::rxClassCode, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Cancelled, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Reversal, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::PayType2, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::PayTypeDesc, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OrderBatch, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OrderTrace, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OrderUser, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CancelBatch, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CancelTrace, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CancelUser, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleBatch, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleTrace, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleUser, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::VerifiedBy, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TfrAcct, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TfrFund, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TfrClass, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleCurrency, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Amount, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::FundName, IFASTBP_PROC::TRANS_LIST, SUBCLASS_PROCESS );

// from cbo vw22
   addFieldDetails( ifds::rxFundCode, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::rxClassCode, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::TransNum, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::GrossAmt, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::TradeDate, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::UnitPrice, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SettleDate, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Units, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::UnitBalance, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Settled, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::NetAmt, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::TransType, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Cancelled, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::OrderType, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::WireOrdNum, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::BrokerCode, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::BranchCode, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SalesRepCode, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::TfrAcct, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::TfrFund, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::TfrClass, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::GrossOrNet, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::DepositType, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::DepositTypeDesc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::RedCode, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::RedCodeDesc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::RvCode, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::RvCodeDesc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::PartFull, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::PrevUnitBal, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Commission, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::HoldBackAmt, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::HoldBackRate, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::OverrideDSCDesc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::OverrideAmt, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SharesElig, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::PartnerShip, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::ProvSales, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::DepositDate, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::CashDate, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::DealDate, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::DealTime, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SetGrossAmt, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SetNetAmt, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SettleCurrency, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::ExchRate, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::ConfIssued, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::RecptIssued, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SrcOfFund, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SrcOfFundDesc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SrcOfAccount, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::OrderSource, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::OrderSrcDesc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SettleSource, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SettleSrcDesc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SettleType, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SettleTypeDesc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SettledBy, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SettledByDesc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::ChqSupCode, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::ChqSupCodeDesc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::ConfirmReq, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::CertRequired, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::OnStmt, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::RoundFlag, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SeqNum, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Accountable, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::AcctableDesc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::BrokerName, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::BranchName, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SlsrepName, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::SlsrepAltName, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Remarks1, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Remarks2, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Remarks3, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Allocation, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Initial, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::GroupCode, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::FeePercent, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::PostUnsettled, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Indc, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::ExpSetlGN, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::DepositId, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::BackDatedReason, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::FASOrigTransNum, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::FASSourceNumber, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Reversal, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::Baycom, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::BayComTo, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::ToBrokerCode, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::ToSlsRepCode, IFASTBP_PROC::TRANS_DETAILS );
   addFieldDetails( ifds::FundName, IFASTBP_PROC::TRANS_DETAILS, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ElongName2, IFASTBP_PROC::TRANS_DETAILS, SUBCLASS_PROCESS );

   addFieldDetails( ifds::LastName, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FirstName, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::NextKey, BF::NullContainerId, SUBCLASS_PROCESS );
   //for view 3
/*   addFieldDetails( DBR::AccountNum, ENTITY_LIST );
   addFieldDetails( DBR::ShrNum, ENTITY_LIST );
   addFieldDetails( DBR::LastName, ENTITY_LIST );
   addFieldDetails( DBR::FirstName, ENTITY_LIST );
   addFieldDetails( DBR::SIN, ENTITY_LIST );
   addFieldDetails( DBR::BirthDate, ENTITY_LIST );
   addFieldDetails( DBR::TaxType, ENTITY_LIST );
   addFieldDetails( DBR::TaxTypeDesc, ENTITY_LIST );
   addFieldDetails( DBR::HomePhone, ENTITY_LIST );
   addFieldDetails( DBR::EntityId, ENTITY_LIST );
   addFieldDetails( DBR::Address1, ENTITY_LIST );
   addFieldDetails( DBR::Address2, ENTITY_LIST );
   addFieldDetails( DBR::Address3, ENTITY_LIST );
   addFieldDetails( DBR::Address4, ENTITY_LIST );
   addFieldDetails( DBR::Address5, ENTITY_LIST );
   addFieldDetails( DBR::PostalCode, ENTITY_LIST );
   addFieldDetails( DBR::IdType1, ENTITY_LIST );
   addFieldDetails( DBR::IdValue1, ENTITY_LIST );
   addFieldDetails( DBR::IdType2, ENTITY_LIST );
   addFieldDetails( DBR::IdValue2, ENTITY_LIST );
   addFieldDetails( DBR::IdType3, ENTITY_LIST );
   addFieldDetails( DBR::IdValue3, ENTITY_LIST );
   addFieldDetails( DBR::IdType4, ENTITY_LIST );
   addFieldDetails( DBR::IdValue4, ENTITY_LIST );
   addFieldDetails( DBR::IdType5, ENTITY_LIST );
   addFieldDetails( DBR::IdValue5, ENTITY_LIST );
   addFieldDetails( DBR::IdType6, ENTITY_LIST );
   addFieldDetails( DBR::IdValue6, ENTITY_LIST );
   addFieldDetails( DBR::IdType7, ENTITY_LIST );
   addFieldDetails( DBR::IdValue7, ENTITY_LIST );
   addFieldDetails( DBR::IdType8, ENTITY_LIST );
   addFieldDetails( DBR::IdValue8, ENTITY_LIST );
   addFieldDetails( DBR::IdType9, ENTITY_LIST );
   addFieldDetails( DBR::IdValue9, ENTITY_LIST );
   addFieldDetails( DBR::IdType10, ENTITY_LIST );
   addFieldDetails( DBR::IdValue10, ENTITY_LIST );
   addFieldDetails( DBR::BirthLastName, ENTITY_LIST );
   addFieldDetails( DBR::BirthFirstName, ENTITY_LIST );
   addFieldDetails( DBR::MultipleReln, ENTITY_LIST );
   addFieldDetails( DBR::Addr11Line1, ENTITY_LIST );
   addFieldDetails( DBR::Addr11Line2, ENTITY_LIST );
   addFieldDetails( DBR::Addr11Line3, ENTITY_LIST );
   addFieldDetails( DBR::Addr11Line4, ENTITY_LIST );
   addFieldDetails( DBR::Addr11Line5, ENTITY_LIST );
   addFieldDetails( DBR::PostalCode11, ENTITY_LIST );
*/
   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::FUNDSRCH_LIST );

   addFieldDetails(ifds::DeductCode, IFASTBP_PROC::DEDUCTION_LIST );
   addFieldDetails(ifds::DeductDesc, IFASTBP_PROC::DEDUCTION_LIST );
   addFieldDetails(ifds::DeductAmt, IFASTBP_PROC::DEDUCTION_LIST );

   addFieldDetails(ifds::FundCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundName, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::LangCode, IFASTBP_PROC::TRANSLATION_LIST );

   addFieldDetails(ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails(ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO );
}

//******************************************************************************

AcctTransProcess::~AcctTransProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pTransHistoryList;
   delete _pTransDetails;
   delete _pMFAccount;
   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool AcctTransProcess::doGetData(
                                GenericInterface * ,
                                BFData * 
                                ) const
{
   _pTransHistoryList->getMore();
   AcctTransProcess * _pAbsPr = const_cast < AcctTransProcess * >(this);
   _pAbsPr->setContainer( IFASTBP_PROC::TRANS_LIST, NULL );
   _pAbsPr->setContainer( IFASTBP_PROC::TRANS_LIST, _pTransHistoryList );
   return(true);
}

//******************************************************************************

SEVERITY AcctTransProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   DString _secondValue;
   try
   {
      DString ShareholderNum,FundCode,ClassCode,
      NumEntry,AllFundMode,FromDate,ToDate,UseDateFlag, transId, transDesc, overrideRepeats;
      DString dstrTrack,dstrActivity,dstrNextKey;
      getParameter( ACCTTRANSLIT::ACCOUNT_NUM, AccountNum );
      getParameter( ACCTTRANSLIT::FUND_CODE, FundCode );
      getParameter( ACCTTRANSLIT::CLASS_CODE, ClassCode );
      getParameter( ACCTTRANSLIT::NUM_ENTRY, NumEntry );
      getParameter( ACCTTRANSLIT::ALL_FUND_MODE, AllFundMode );
      getParameter( ACCTTRANSLIT::SHAREHOLDER_NUM, ShareholderNum);
      getParameter( pFROMDATE, FromDate);
      getParameter( pTODATE, ToDate);
      getParameter( pNEXTKEY, dstrNextKey);
      getParameter( pUSEDATEFLAG, UseDateFlag);
      getParameter( ACCTTRANSLIT::TRANSID, transId );
      getParameter( ACCTTRANSLIT::TRANS_DESC, transDesc );
      getParameter( ACCTTRANSLIT::OVERRIDE_REPEATS, overrideRepeats );

      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");

      AccountNum.stripAll();
      FundCode.stripAll().upperCase();
      ClassCode.stripAll().upperCase();
      NumEntry.stripAll();
      AllFundMode.stripAll();
      ShareholderNum.stripAll();

      if( AccountNum==I_("") && transDesc == ACCT_TRANS )
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_NO_DATA_AREA );
      if( ( AllFundMode == Y ) || (FundCode == NULL_STRING && ClassCode == NULL_STRING) )
      {
         AllFundMode = Y;
      }
      else
      {
         AllFundMode = N;
      }

      if( FromDate != NULL_STRING && ToDate != NULL_STRING )
      {
         UseDateFlag = Y;
      }
      else
      {
         UseDateFlag = N;
      }

      if( AccountNum != NULL_STRING )
      {
         _pMFAccount = new MFAccount( *getBFWorkSession() );
         sevRtn = _pMFAccount->init( AccountNum );
         if( WARNING >= sevRtn )
         {
            setContainer( IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount );
         }
         else
         {
            return(GETCURRENTHIGHESTSEVERITY());
         } 

      }
      transId.strip();
      if( transDesc == ACCT_TRANS )
      {
         _pTransHistoryList = new TransactionList( *getBFWorkSession() );

         sevRtn = _pTransHistoryList->init( AccountNum,
                                            FundCode, ClassCode, NumEntry, AllFundMode, UseDateFlag, FromDate, ToDate, 
                                            dstrTrack,dstrActivity,dstrNextKey );
         if( WARNING >= sevRtn )
         {
            setContainer( IFASTBP_PROC::TRANS_LIST, _pTransHistoryList );
         }
         else
         {
            return(GETCURRENTHIGHESTSEVERITY());
         }

         MgmtCo &mgmtCoOut = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo();

         sevRtn = mgmtCoOut.getFundDetailList( _pFundDetailList );
         if( WARNING >= sevRtn )
         {
            setContainer( IFASTBP_PROC::FUNDSRCH_LIST, _pFundDetailList );
         }

         sevRtn = mgmtCoOut.getMgmtCoOptions( _pmgmtcooptions );

         if( WARNING >= sevRtn )
         {
            setContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, _pmgmtcooptions );
         }

      }
      else if( transDesc == TRANS_DTL )
      {
         _pTransDetails = new TransactionDetails( *getBFWorkSession() );

         sevRtn = _pTransDetails->getDetails( transId, dstrTrack, dstrActivity );
         if( WARNING >= sevRtn )
         {
            setContainer( IFASTBP_PROC::TRANS_DETAILS, _pTransDetails );
         }
         else
         {
            return(GETCURRENTHIGHESTSEVERITY());
         }

         setContainer( IFASTBP_PROC::DEDUCTION_LIST, _pTransDetails->getDeductionList() );

      }
      else
         assert( 0 );

      MgmtCo &mgmtCoOut = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo();
      sevRtn = mgmtCoOut.getTranslationList( _pTranslationList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::TRANSLATION_LIST, _pTranslationList );
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

bool AcctTransProcess::doMoreRecordsExist(
                                         GenericInterface *rpGICaller,
                                         const BFContainerId& idContainer 
                                         )
{
   return( _pTransHistoryList->doMoreRecordsExist() );
}

//******************************************************************************

E_COMMANDRETURN AcctTransProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;

   return(rtn);
}

//******************************************************************************

bool AcctTransProcess::doRefresh( GenericInterface *rpGICaller, 
                                  const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   return(true);
}

void AcctTransProcess::doGetField(
                                 const GenericInterface *rpGICaller,
                                 const BFContainerId& idContainer,
                                 const BFFieldId& idField,
                                 const BFDataGroupId& idDataGroup,
                                 DString &strValueOut,
                                 bool bFormatted
                                 ) const
{  
   DString strEntityName;
   DString acctnum  = AccountNum; 

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( idField == ifds::FirstName || idField == ifds::LastName )
   {
      dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), acctnum, strEntityName);
      if( idField == ifds::LastName )
         strValueOut.assign( strEntityName, 0, strEntityName.find(';'));
      else if( idField == ifds::FirstName )
         strValueOut.assign(strEntityName, strEntityName.find(';') +1, strEntityName.length() + 1);
   }
   else if( idField == ifds::FundName && ( idContainer == IFASTBP_PROC::TRANS_LIST || idContainer == IFASTBP_PROC::TRANS_DETAILS ) )
   {
      AcctTransProcess *rpNonConstThis = const_cast < AcctTransProcess*> ( this );
      DString strFundCode, strClassCode;
      rpNonConstThis->getField( this, idContainer, ifds::rxFundCode, strFundCode, true );
      rpNonConstThis->getField( this, idContainer, ifds::rxClassCode, strClassCode, true );
      DString dstLocaleStr = ClientLocaleContext::get().getLocale();
	  FundMasterList *pFundMasterList;
      dstcWorkSession->getMgmtCo().getFundMasterList( pFundMasterList );
      if( pFundMasterList )
      {
		 if(dstLocaleStr != I_("frCA"))
			pFundMasterList->getFundName( strFundCode, ifds::ElongName1, strValueOut);
		 else
		    pFundMasterList->getFundName( strFundCode, ifds::FLongName, strValueOut);         
      }
   }
   else if( idField == ifds::ElongName2 && idContainer == IFASTBP_PROC::TRANS_DETAILS )
   {
      AcctTransProcess *rpNonConstThis = const_cast < AcctTransProcess*> ( this );
      DString strFundCode, strClassCode;
      rpNonConstThis->getField( this, idContainer, ifds::TfrFund, strFundCode, true );
      rpNonConstThis->getField( this, idContainer, ifds::TfrClass, strClassCode, true );
      FundMasterList *pFundMasterList;
      dstcWorkSession->getMgmtCo().getFundMasterList( pFundMasterList );
      if( pFundMasterList )
      {
         pFundMasterList->getFundName( strFundCode, ifds::ElongName1, strValueOut);
      }
   }
   else if( idField == ifds::NextKey )
   {
//CP20030309      _pTransHistoryList->getField(ifds::NextKey, strValueOut, TRANS_LIST, false);
      _pTransHistoryList->getField(ifds::NextKey, strValueOut, idDataGroup, false);
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAcctTransProcess.cpp-arc  $
 * 
 *    Rev 1.39   Nov 17 2004 15:18:52   popescu
 * PET 1117/56, removed 'getField' method at the fund master list level, 
 * 
 *    Rev 1.38   Mar 21 2003 17:42:48   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.37   Mar 09 2003 15:55:52   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.36   Feb 12 2003 12:51:24   FENGYONG
 * pts ticket: 10013444
 * 
 *    Rev 1.35   Dec 12 2002 11:29:26   FENGYONG
 * Add ToBrokerCode and ToSlsRepCode
 * 
 *    Rev 1.34   Oct 09 2002 23:53:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.33   Oct 08 2002 16:57:28   FENGYONG
 * add settled field
 * 
 *    Rev 1.32   Aug 29 2002 16:45:00   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.31   Aug 29 2002 12:54:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.30   22 May 2002 18:24:30   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.29   Apr 26 2002 10:42:16   FENGYONG
 * Add Baycom
 * 
 *    Rev 1.28   27 Mar 2002 19:55:08   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.27   Mar 20 2002 10:45:32   FENGYONG
 * Add BayCom
 * 
 *    Rev 1.26   Nov 13 2001 12:47:04   VASILEAD
 * Added fund name info for funds transfer
 * 
 *    Rev 1.25   Nov 02 2001 11:14:38   FENGYONG
 * Add nextkey as a parameter
 * 
 *    Rev 1.24   Sep 26 2001 14:48:10   VASILEAD
 * Added Reversal field to the interface
 * 
 *    Rev 1.23   03 May 2001 14:05:28   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.22   Mar 18 2001 18:18:10   VASILEAD
 * Fixes for UAT release
 * 
 *    Rev 1.21   Mar 12 2001 12:58:40   VASILEAD
 * Modified for FUNDcom release
 * 
 *    Rev 1.20   Feb 28 2001 11:24:02   VASILEAD
 * Added string descriptions for containers
 * 
 *    Rev 1.19   Jan 31 2001 16:05:08   YINGBAOL
 * to prevent  track para from being empty 
 * 
 *    Rev 1.18   Jan 23 2001 15:17:42   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.17   Jan 17 2001 12:08:08   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.16   Jan 04 2001 10:38:42   VASILEAD
 * More DSC bug fixes
 * 
 *    Rev 1.15   15 Dec 2000 12:43:34   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.14   Dec 14 2000 15:53:26   FENGYONG
 * remove #3
 * 
 *    Rev 1.13   Dec 13 2000 10:57:48   FENGYONG
 * Add filed PayType2 and change #17 and #54 DataSet  from PayType to PayType2
 * 
 *    Rev 1.12   Nov 17 2000 14:40:50   FENGYONG
 * change pname and request name for remove DE
 * 
 *    Rev 1.11   Sep 26 2000 11:03:30   VASILEAD
 * Took out memory leak
 * 
 *    Rev 1.10   Sep 08 2000 16:16:50   FENGYONG
 * Taxtype
 * 
 *    Rev 1.9   Sep 07 2000 12:04:34   FENGYONG
 * fix memery leak
 * 
 *    Rev 1.8   Aug 22 2000 16:54:48   FENGYONG
 * Fix for french fundname and French desc
 * 
 *    Rev 1.7   Aug 01 2000 15:45:58   YINGZ
 * add currency field
 * 
 *    Rev 1.6   Jul 05 2000 13:45:12   VASILEAD
 * Added ShortName from TranslationList
 * 
 *    Rev 1.5   Jun 28 2000 12:01:42   VASILEAD
 * Adapted to the new views
 * 
 *    Rev 1.4   Jun 16 2000 10:35:52   VASILEAD
 * Reduced the number of transacions to be sent
 * 
 *    Rev 1.3   May 16 2000 14:32:18   YINGZ
 * support usedateflag
 * 
 *    Rev 1.2   Mar 30 2000 15:46:24   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:52   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.12   Mar 13 2000 11:25:46   FENGYONG
// Fix bug
// 
//    Rev 1.11   Mar 10 2000 16:18:32   FENGYONG
// fix bug
// 
//    Rev 1.10   Mar 10 2000 09:56:14   FENGYONG
// For Nextkey
// 
//    Rev 1.9   Mar 06 2000 15:48:28   FENGYONG
// Add FundName & TfrFundName
// 
//    Rev 1.8   Mar 01 2000 16:10:48   FENGYONG
// Add CurrentDate
// 
//    Rev 1.7   Feb 29 2000 15:26:50   FENGYONG
// Add fields
// 
//    Rev 1.6   Feb 01 2000 16:01:54   FENGYONG
// add error handler
// 
//    Rev 1.5   Jan 19 2000 13:59:54   FENGYONG
// For nextkey
// 
//    Rev 1.4   Jan 12 2000 16:50:40   FENGYONG
// add getItem
// 
//    Rev 1.3   Dec 16 1999 11:49:24   DT24433
// removed doOk/doCancel, unused headers
// 
//    Rev 1.2   Dec 15 1999 10:09:22   FENGYONG
// Add calculation for grossamt
// 
//    Rev 1.1   Nov 30 1999 11:03:34   FENGYONG
// Modified to adapt multipages
 *
 */
