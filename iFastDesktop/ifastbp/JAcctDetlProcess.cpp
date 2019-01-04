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
//******************************************************************************
//
// ^FILE   : JAcctDetlProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/09/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AcctDetlProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <bfproc\bpglobal.h>
#include "jacctdetlprocess.hpp"
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\demographics.hpp>
#include <bfcbo\bfobjiter.hpp>
#include <ifastdataimpl\dse_dstc0004_req.hpp>
#include <ifastdataimpl\dse_dstc0020_req.hpp>
#include <ifastdataimpl\dse_dstc0020_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_vw.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\translationlist.hpp>
#include <ifastcbo\fundsponsorslist.hpp>
#include <ifastcbo\accountdistributionlist.hpp>
#include <ifastcbo\currencyclass.hpp>
#include <ifastcbo\historicalmarketvaluelist.hpp>
#include "jacctdetlprocessincludes.h"
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastcbo\mfaccountlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCTDETL;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AcctDetlProcess > processCreator( CMD_BPROC_ACCTDETL );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AcctDetlProcess" );
   const I_CHAR * const AS_OF_DATE = I_( "AsofDate" );
}

namespace ACCTDETLIT  //stands for account details literals
{
   const I_CHAR * const ENTITY_ID_FIELD = I_( "EntityId" );
   const I_CHAR * const ACCOUNT_NUMBER_FIELD = I_( "TXAccountNum" );
   const I_CHAR * const SHAREHOLDER_NUM_FIELD = I_( "ShrNum" );
   const I_CHAR * const NUM_ENTRY_FIELD = I_( "NumEntry" );
   const I_CHAR * const LANGUAGE = I_( "language" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319AcctDetlProcess::AcctDetlProcess() : 
AcctDetlProcess::AcctDetlProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pMFAccountHoldingList( NULL ),
_pMFAccountList( NULL ),
_pFundMasterList( NULL ),
_pMFAccount( NULL ),
_pTranslationList( NULL ),
_pPendingTradeList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, true,  BF::NullContainerId, false, I_( "MFAccountHolding" ) );
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false,  BF::NullContainerId, false, I_( "MFAccount" )  );
   addContainer( IFASTBP_PROC::TRANSLATION_LIST, true,  BF::NullContainerId, false, I_( "Transaction" )  );
   addContainer( IFASTBP_PROC::FUNDMASTER_LIST, true );
   addContainer( IFASTBP_PROC::FUNDSPONSORS_LIST, true,  BF::NullContainerId, false, I_( "FundSponsors" )  );
   addContainer( IFASTBP_PROC::ACC_DISTRIBUTION_LIST, true,  BF::NullContainerId, false, I_( "Distribution" )  );
   addContainer( IFASTBP_PROC::PENDINGTRADE_LIST, true, BF::NullContainerId, false, I_("PendingTrade") );
   addContainer( IFASTBP_PROC::DEMOGRAPHICS_LIST, false, BF::NullContainerId, false, I_("Demographics") );

   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BeneficialOwner, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AltAccount, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctType, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctTypeDesc, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::TaxType, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::TaxTypeDesc, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::RecipientType, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::RecipientTypeDesc, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctDesignation, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctDesignationDesc, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::CurrencyName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::XrefNum, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BrokerCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BranchCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Slsrep, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::InterCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::InterAccount, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctStatus, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctStatusDesc, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::DateOfReg, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::RRSPFee, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::RRSPFeeDesc, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AMSCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::PensionJuris, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::PensionJurisDesc, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::StopPurchase, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::StopXferIn, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::StopXferOut, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::StopRed, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::FeeWaived, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::MarketMail, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Unseizable, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::RegCompleted, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::SupConf, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::SupEmpConf, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::InTrustFor, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Escrow, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctGroup, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctGroupName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BrokerName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BranchName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::SlsrepName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::SlsrepAltName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AccountBalance, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Username, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctMstrVer, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctMstrRid, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Employee, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AddAcctFlag, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::LastName, IFASTBP_PROC::MFACCOUNT_CBO, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FirstName, IFASTBP_PROC::MFACCOUNT_CBO, SUBCLASS_PROCESS );

   addFieldDetails( ifds::TotalValueAcctCurr, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AccountBalance, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::rxFundCode, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::rxClassCode, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::SettledUnits, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::SettledValue, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::UnsettledUnits, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::UnsettledValue, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::FundNAV, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::PYEUnits, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::PYEValue, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::AsAtDate, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::LastEvent, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::SettledValueAcctCurr, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::FundCurrency, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::TradedUnits, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::CombValueFundCurr, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::CombValueAcctCurr, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST,SUBCLASS_PROCESS );
   addFieldDetails( ifds::ExchRate, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::PendingTradesExist, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );

   addFieldDetails( ifds::DistributionPayType, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundGroupDesc, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundName, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundGroup, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, SUBCLASS_PROCESS  );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::DistributionPayType, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUNDMASTER_LIST );
   addFieldDetails( ifds::FundGroup, IFASTBP_PROC::FUNDMASTER_LIST );

   addFieldDetails( ifds::FundGroup, IFASTBP_PROC::FUNDSPONSORS_LIST );
   addFieldDetails( ifds::FundGroupDesc, IFASTBP_PROC::FUNDSPONSORS_LIST );

   addFieldDetails( ifds::rxFundCode, IFASTBP_PROC::PENDINGTRADE_LIST );
   addFieldDetails( ifds::rxClassCode, IFASTBP_PROC::PENDINGTRADE_LIST );

   addFieldDetails(ifds::FundCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundName, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::LangCode, IFASTBP_PROC::TRANSLATION_LIST );

   addFieldDetails(ifds::InvObjCode, IFASTBP_PROC::DEMOGRAPHICS_LIST );
   addFieldDetails(ifds::AdvisorCode, IFASTBP_PROC::DEMOGRAPHICS_LIST );
   
   addFieldDetails( ifds::Grp1Shares, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
   addFieldDetails( ifds::Grp2Shares, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST );
}

//******************************************************************************

AcctDetlProcess::~AcctDetlProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

//   delete _pMFAccountHoldingList;
   //delete _pMFAccountList;
//   delete _pMFAccount;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AcctDetlProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   DString _secondValue=NULL;

   try
   {
      DString EntityId=NULL, InputShrNum=NULL, NumEntry=NULL,shrNum = NULL_STRING;

      getParameter( ACCTDETLIT::ACCOUNT_NUMBER_FIELD, strAccountNumber );
      getParameter( ACCTDETLIT::ENTITY_ID_FIELD, EntityId );
      getParameter( ACCTDETLIT::SHAREHOLDER_NUM_FIELD, InputShrNum );
      getParameter( ACCTDETLIT::NUM_ENTRY_FIELD, NumEntry );
      getParameter( ACCTDETLIT::LANGUAGE, language );

      DString dstrTrack,dstrActivity;
      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");

      strAccountNumber.stripLeading().stripLeading( I_CHAR( '0' ) ).stripTrailing();
      if( strAccountNumber == I_("") && EntityId.stripAll() == I_("") )
      {
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_NO_DATA_AREA );
      }


      //_pMFAccount = new MFAccount;
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      sevRtn = dstcWorkSession->getMFAccount( getDataGroupId(), strAccountNumber, _pMFAccount, dstrTrack, dstrActivity);
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount );
         _pMFAccount->getField( ifds::ShrNum, shrNum, getDataGroupId() );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      } 

      sevRtn = _pMFAccount->getAccountHoldingList( _pMFAccountHoldingList, getDataGroupId() );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, _pMFAccountHoldingList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      sevRtn = _pMFAccount->getPendingTradesList( _pPendingTradeList, getDataGroupId(), 0 );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::PENDINGTRADE_LIST, _pPendingTradeList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }


      sevRtn = _pMFAccount->getAccDistributionsList(rpAccDistributionList, getDataGroupId() );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::ACC_DISTRIBUTION_LIST, rpAccDistributionList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      MgmtCo &mgmtCoOut = dstcWorkSession->getMgmtCo();

      sevRtn = mgmtCoOut.getTranslationList( _pTranslationList);
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::TRANSLATION_LIST, _pTranslationList );
      }

      sevRtn = mgmtCoOut.getFundMasterList( _pFundMasterList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDMASTER_LIST, _pFundMasterList );
      }

      sevRtn = mgmtCoOut.getFundSponsorsList( _pFundSponsorsList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDSPONSORS_LIST, _pFundSponsorsList );
      }
 
      sevRtn = _pMFAccount->getDemographicsList( _pDemographics, getDataGroupId() );
      if( _pDemographics != NULL && sevRtn <= WARNING )
      {
         setContainer( IFASTBP_PROC::DEMOGRAPHICS_LIST, _pDemographics );
      }
 
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

//******************************************************************************

E_COMMANDRETURN AcctDetlProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

void AcctDetlProcess::setCurrentListItem(
                                        const GenericInterface *rpGICaller,
                                        const BFContainerId& idList,
                                        const DString& strListItemKey
                                        )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM ); 
   AbstractProcess::setCurrentListItem( rpGICaller, idList, strListItemKey );
}

void AcctDetlProcess::doGetField( const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId& idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted ) const
{  
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   DString strEntityName, currency;
   DString acctnum  = strAccountNumber; 
   DString fundCode, classCode, strKey = NULL_STRING;
   AcctDetlProcess *rpNonConstThis = const_cast < AcctDetlProcess*> ( this );
   DString dstLocaleStr = ClientLocaleContext::get().getLocale();

   if( idField == ifds::FirstName || idField == ifds::LastName )
   {
      dstcWorkSession->getFirstSequenced01AccountholderEntityName( idDataGroup, acctnum, strEntityName);
      if( idField == ifds::LastName )
         strValueOut.assign( strEntityName, 0, strEntityName.find(';'));
      else if( idField == ifds::FirstName )
         strValueOut.assign(strEntityName, strEntityName.find(';') +1, strEntityName.length() + 1);
   }
   else if( idContainer == IFASTBP_PROC::MFACCOUNT_HOLDING_LIST )
   {
      rpNonConstThis->getField( rpGICaller, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, ifds::rxFundCode, fundCode, false );
      rpNonConstThis->getField( rpGICaller, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, ifds::rxClassCode, classCode, false );

      if( dstLocaleStr == I_("enUS") )     dstLocaleStr = I_("E");
      if( dstLocaleStr == I_("frCA") )     dstLocaleStr = I_("F");
   }

   if( idField == ifds::TotalValueAcctCurr )
   {
      _pMFAccountHoldingList->getField(ifds::TotalValueAcctCurr, strValueOut, idDataGroup, false);
      rpNonConstThis->getField( rpGICaller, IFASTBP_PROC::MFACCOUNT_CBO, ifds::Currency, currency, false );
      CurrencyClass::FormatValue( currency, strValueOut, strValueOut );
   }
   else if( idField == ifds::FundGroupDesc || idField == ifds::FundGroup )
   {
      DString FundGroup = NULL_STRING;
      BFObjIter bfIter( *_pFundMasterList, idDataGroup/*was ==> getDataGroupId()*/, false, BFObjIter::ITERTYPE::NON_DELETED );
      _pFundMasterList->buildKey( fundCode,strKey );
      bfIter.positionByKey( strKey );
      if( !bfIter.end() && bfIter.getObject() )
      {
         bfIter.getObject()->getField( ifds::FundGroup, strValueOut, idDataGroup, false );
      }
      if( strValueOut!= NULL_STRING && idField == ifds::FundGroupDesc )
      {
         BFObjIter iter1( *_pFundSponsorsList, idDataGroup/*was ==> getDataGroupId()*/, false, BFObjIter::ITERTYPE::NON_DELETED );
         _pFundSponsorsList->getStrKey(strKey, strValueOut);

         iter1.positionByKey( strKey );
         if( !iter1.end() && iter1.getObject() )
         {
            iter1.getObject()->getField( ifds::FundGroupDesc, strValueOut, idDataGroup, false );
         }
      }
   }
   else if( idField == ifds::FundName )
   {
      BFObjIter iter( *_pTranslationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      _pTranslationList->getStrKey( strKey, dstLocaleStr, fundCode );
      iter.positionByKey( strKey );
      if( !iter.end() && iter.getObject() )
      {
         iter.getObject()->getField( ifds::FundName, strValueOut, idDataGroup, false );
      }
   }
   else if( idField == ifds::CombValueAcctCurr )
   {
      DString dstrSrchFundCode, dstrSrchClassCode;

      BFObjIter holdingbfIter( *_pMFAccountHoldingList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

      //_pMFAccountHoldingList->getStrKey( strKey,fundCode,classCode );
      // holdingbfIter.positionByKey( strKey );

      // Iterate through MFAccountHoldingList and see if fund class passed is in list
      while(!holdingbfIter.end()) {

         holdingbfIter.getObject()->getField ( ifds::rxFundCode,  dstrSrchFundCode, idDataGroup );
         holdingbfIter.getObject()->getField ( ifds::rxClassCode, dstrSrchClassCode, idDataGroup );

         // If match found, return NO_CONDITION
         if( (fundCode == dstrSrchFundCode.strip()) && (classCode == dstrSrchClassCode.strip()) ) {
            break;
         }
      }
      if( !holdingbfIter.end() && holdingbfIter.getObject() )
      {
         holdingbfIter.getObject()->getField( ifds::CombValueAcctCurr, strValueOut, idDataGroup, false );
      }
      rpNonConstThis->getField( rpGICaller, IFASTBP_PROC::MFACCOUNT_CBO, ifds::Currency, currency, false );
      CurrencyClass::FormatValue( currency, strValueOut, strValueOut );
   }
}

const DString& AcctDetlProcess::getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   static DString key=NULL_STRING;

   try
   {
      if( idList == IFASTBP_PROC::MFACCOUNT_HOLDING_LIST )
      {
         sortFundByShortName( this, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, 
                              ifds::rxFundCode, ifds::rxClassCode, IFASTBP_PROC::TRANSLATION_LIST, language, &holdingfundNameSort);

         holdingiter=holdingfundNameSort.begin();
         if( holdingiter!=holdingfundNameSort.end() )
         {
            setCurrentListItem( rpGICaller, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, holdingiter->second );
            return(AbstractProcess::getCurrentListItemKey( rpGICaller, idList ));
         }
         else return(key);
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(AbstractProcess::getFirstListItemKey( rpGICaller, idList ));
}

//******************************************************************************

const DString& AcctDetlProcess::getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   static DString key = NULL_STRING;

   try
   {
      if( idList == IFASTBP_PROC::MFACCOUNT_HOLDING_LIST )
      {
         ++holdingiter;
         if( holdingiter!=holdingfundNameSort.end() )
         {
            setCurrentListItem( rpGICaller, IFASTBP_PROC::MFACCOUNT_HOLDING_LIST, holdingiter->second );
            return(AbstractProcess::getCurrentListItemKey( rpGICaller, idList ));
         }
         else return(key);
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(AbstractProcess::getNextListItemKey( rpGICaller, idList ));
}

void AcctDetlProcess::sortFundByShortName(GenericInterface *pGI, const BFContainerId& idContainer, 
                                          const BFFieldId& fundCode, const BFFieldId& classCode, const BFContainerId& idTranslationList, 
                                          DString &language, FUND_SORT* resultMap)
{
   resultMap->clear();
   DString tmp, fundcode, classcode;
   DString key = AbstractProcess::getFirstListItemKey( NULL, idContainer );

   if( key != NULL_STRING )
   {
      do
      {
         getField( NULL, idContainer, fundCode, fundcode );

         if( fundcode.strip() != NULL_STRING )
         {
            if( classCode.getId() != -1 )   //if we have a list of funds and not fund-code pairs
               pGI->getField( NULL, idContainer, classCode, classcode );
            else
               classcode = I_( "" );
            tmp = (language == I_("fr") )? I_("F  ") : I_("E  ");

            setCurrentListItem( NULL, idTranslationList, tmp+fundcode.strip().upperCase() );
            getField( NULL, idTranslationList, ifds::FundName, tmp );

            tmp+=classcode.strip(); // sort by fundname and class code since one fund can have more than one class
            (*resultMap)[tmp.strip()] = key;
         }
      }while( ( key = AbstractProcess::getNextListItemKey( NULL, idContainer ) ) != NULL_STRING );
   }
}
//******************************************************************************
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAcctDetlProcess.cpp-arc  $
 * 
 *    Rev 1.38   Jul 11 2003 16:10:56   FENGYONG
 * move KYC from sharholder to MFAccount
 * 
 *    Rev 1.37   Mar 21 2003 17:42:40   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.36   Mar 09 2003 15:55:46   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.35   Mar 07 2003 15:47:48   PURDYECH
 * Fixed up some DataGroupId problems in doGetField
 * 
 *    Rev 1.34   Mar 07 2003 11:56:16   PURDYECH
 * Documentation cleanup
 * 
 *    Rev 1.33   Dec 19 2002 13:26:02   sanchez
 * Modified  doGetField() Iterate throug account holdings list ot find the fund.  Don't use  positionByKey because the key uses a group code
 * 
 *    Rev 1.32   Oct 09 2002 23:53:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.31   Sep 30 2002 11:01:04   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.30   Aug 29 2002 16:45:00   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.29   Aug 29 2002 12:54:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.28   22 May 2002 18:24:30   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.27   27 Mar 2002 19:55:08   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.26   14 May 2001 13:58:14   YINGZ
 * code sync up
 * 
 *    Rev 1.25   May 08 2001 11:40:08   FENGYONG
 * sorting by fundname and add dogetfield
 * 
 *    Rev 1.24   03 May 2001 14:05:28   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.23   Mar 29 2001 12:11:08   FENGYONG
 * Add managementstyle and discretionary
 * 
 *    Rev 1.22   Feb 28 2001 15:43:26   YINGZ
 * change cbo names to meet xml output requirement
 * 
 *    Rev 1.21   Feb 13 2001 17:16:12   FENGYONG
 * Add pending tradelist for trading page
 * 
 *    Rev 1.20   Jan 31 2001 16:05:06   YINGBAOL
 * to prevent  track para from being empty 
 * 
 *    Rev 1.19   Jan 31 2001 15:29:00   FENGYONG
 * get TotalValueAcctCurr from CBO
 * 
 *    Rev 1.18   Jan 30 2001 14:22:32   FENGYONG
 * Add fields
 * 
 *    Rev 1.17   Jan 24 2001 09:55:28   YINGBAOL
 * view 20 change sync.
 * 
 *    Rev 1.16   Jan 23 2001 15:17:40   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.15   Dec 15 2000 16:53:50   FENGYONG
 * remove #3
 * 
 *    Rev 1.14   Dec 15 2000 16:44:20   YINGZ
 * add names for the container
 * 
 *    Rev 1.13   Dec 07 2000 15:44:54   YINGZ
 * name accout holding list
 * 
 *    Rev 1.12   Dec 01 2000 16:58:06   FENGYONG
 * Add acctdistribution list
 * 
 *    Rev 1.11   Nov 28 2000 14:43:48   FENGYONG
 * Add fundsponser
 * 
 *    Rev 1.10   Nov 17 2000 14:40:48   FENGYONG
 * change pname and request name for remove DE
 * 
 *    Rev 1.9   Sep 30 2000 13:08:16   YINGZ
 * add fundcurrency
 * 
 *    Rev 1.8   Aug 23 2000 12:29:08   FENGYONG
 * Add list
 * 
 *    Rev 1.7   Aug 22 2000 16:54:44   FENGYONG
 * Fix for french fundname and French desc
 * 
 *    Rev 1.6   Jul 27 2000 17:28:04   VASILEAD
 * Change the short fund name to long fund name
 * 
 *    Rev 1.5   Jul 05 2000 13:45:14   VASILEAD
 * Added ShortName from FundMasterList
 * 
 *    Rev 1.4   Jun 16 2000 10:35:50   VASILEAD
 * Reduced the number of transacions to be sent
 * 
 *    Rev 1.3   Apr 07 2000 15:23:26   FENGYONG
 * fix
 * 
 *    Rev 1.2   Mar 30 2000 15:46:12   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:52   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.12   Mar 13 2000 11:25:30   FENGYONG
// Fix bug
// 
//    Rev 1.11   Mar 10 2000 16:18:16   FENGYONG
// fix bug 
// 
//    Rev 1.10   Mar 07 2000 10:52:38   FENGYONG
// change fundlist
// 
//    Rev 1.9   Mar 06 2000 15:46:42   FENGYONG
// Add FirstName, LastName from #3 view
// 
//    Rev 1.8   Feb 01 2000 17:45:50   FENGYONG
// for AccountHolding List
// 
//    Rev 1.7   Feb 01 2000 16:01:40   FENGYONG
// Add error handler
// 
//    Rev 1.5   Jan 12 2000 16:50:20   FENGYONG
// change for AccountHolding list
// 
//    Rev 1.4   Jan 08 2000 14:33:00   POPESCUS
// added the datagroupid when quering for children lists
// 
//    Rev 1.3   Jan 06 2000 09:58:06   POPESCUS
// cleanup code and remove some unused methods
// 
//    Rev 1.2   Nov 30 1999 11:03:24   FENGYONG
// Modified to use AccountList
// 
//    Rev 1.1   Nov 25 1999 11:53:58   FENGYONG
// Changed with MFAccount 
 * 
 */


