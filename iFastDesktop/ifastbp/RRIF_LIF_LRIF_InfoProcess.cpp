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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RRIF_LIF_LRIF_InfoProcess.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : Feb 07, 2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RRIF_LIF_LRIF_InfoProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\mfaccount.hpp>
#include "rrif_lif_lrif_infoprocess.hpp"
#include "rrif_lif_lrif_infoprocessincludes.h"
#include <ifastcbo\rrif_lif_lrif_infolist.hpp>
#include <ifastcbo\rrif_lif_lrif_info.hpp>
#include <ifastcbo\FromFundAllocList.hpp>
#include <ifastcbo\ToFundAllocList.hpp>
#include <ifastdataimpl\dse_dstc0129_req.hpp>
#include <ifastcbo\rrif_lif_lrif_paymentscalculation.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_RRIF_LIF_LRIF_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RRIF_LIF_LRIF_INFO;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RRIF_LIF_LRIF_InfoProcess > processCreator( CMD_BPROC_RRIF_LIF_LRIF_INFO );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RRIF_LIF_LRIF_InfoProcess" );
   const I_CHAR * const INITLISTS = I_( "initLists" );
   const I_CHAR * const PERFORMSEARCH = I_( "performSearch" );
   const I_CHAR * const RESETRRIRLIFLRIFALLOCLIST = I_( "resetRRIF_LIF_LRIF_AllocList" );
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long ERR_RRIF_INFO_NOT_APPLICABLE;
}
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_FIELD_INFO;
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_INFO;
}

namespace RRIF_LIF_LRIF
{
   const I_CHAR * const ACCOUNT_NUMBER_FIELD = I_( "AccountNum" );
   const I_CHAR * const SHAREHOLDER_FIELD    = I_( "ShareholderNum" );
   const I_CHAR * const LAST_NAME_FIELD      = I_( "LastName");
   const I_CHAR * const FIRST_NAME_FIELD     = I_( "FirstName");
   const I_CHAR * const RRIF_LIF_LRIF        = I_( "RIF");

}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
}

using namespace RRIF_LIF_LRIF;
//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319RRIF_LIF_LRIF_InfoProcess::RRIF_LIF_LRIF_InfoProcess():
RRIF_LIF_LRIF_InfoProcess::RRIF_LIF_LRIF_InfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL ), _pRRIF_LIF_LRIF_InfoList( 0 ), 
_pRRIF_LIF_LRIF_PaymentsCalculation( 0 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_("LIF_LRIF_InfoProcess") );

   addContainer( IFASTBP_PROC::MFACCOUNT_CBO,           false );
   addContainer( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, true, BF::NullContainerId,                   true, I_("RRIF_LIF_LRIF_INFO") );
   addContainer( IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,    true, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, true, I_("RRIF_FROM_ALLOC_LIST") );
   addContainer( IFASTBP_PROC::RRIF_TO_ALLOC_LIST,      true, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, true, I_("RRIF_TO_ALLOC_LIST") );

   // addContainer( RRIF_LIF_LRIF_CALCULATE, false, BF::NullContainerId,true );

   //addSubstituteList(DBR::Frequency);

   addFieldDetails( ifds::AccountNum,        IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::TaxType,           IFASTBP_PROC::MFACCOUNT_CBO );

   addFieldDetails( ifds::PensionJuris,      IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::MinWithAge,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::PlanType,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::RIFId,             IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::RecType,           IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::RecTypeDesc,       IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::SuppFedTax,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::SuppProvTax,       IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::FedRate,           IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::FedRatePUD,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::ProvRate,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::ProvRatePUD,       IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::RRIFAmount,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::GrossNetMethod,    IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::NetAmt,            IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::NowPlanValue,      IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::PYEPlanValue,      IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::CalcMandYr,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::CalcMaxYr,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::MandAmtPay,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::MandAmtYr,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::RIFPayType,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::PayTypeDesc,       IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::InstCode,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::InstName,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::TransitNo,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::BankAcctNum,       IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::BankType,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::PayOption,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::PayOptionDesc,     IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::MaxAmtYr,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::TaxOnMin,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::OverrideAmtYr,     IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::OverrideUnusedMax, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::PYUnusedMax,       IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::RIFSrcOfFund,      IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::RIFSrcOfFundDesc,  IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::January,           IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::February,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::March,             IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::April,             IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::May,               IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::June,              IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::July,              IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::August,            IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::September,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::October,           IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::November,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::December,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::EndOfMonth,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::LastProcessDate,   IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::AddrCode,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::GoodBad,           IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::EffectiveFrom,     IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::ModDate,           IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::StopDate,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::AddrLine1,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::AddrLine2,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::AddrLine3,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::AddrLine4,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::AddrLine5,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::PostalCode,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::IndexRate,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::Qualified,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::Username,          IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::BatchEffective,    IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::AccountTo,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::PreYrPercent,      IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::BatchName,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::RRIFBatchTrace,    IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::SpouseBirth,       IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::PayTerm,           IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::PayTermDesc,       IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::Factor,            IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::CansimRate,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::ModUser,           IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::ProcessDate,       IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::BatchTrace,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST ); //field from view 124
   addFieldDetails( ifds::rxBatchName,       IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST ); //field from view 124
   addFieldDetails( ifds::Frequency,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::MonthIndicator,    IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::DayOfWeek,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::DaysOfMonth,       IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::RRIFSrcOfFund,     IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );//P0186486_FN15_The Source of Funds
   addFieldDetails( ifds::RRIFSrcOfAcct,     IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );

   // gap 92
   addFieldDetails( ifds::RefTempInc,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::AdjLifeInc,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   // Locked In Product
   addFieldDetails( ifds::OrigPlanDeff,      IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails( ifds::OrigPlanDeffApplied,  IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   
   //addFieldDetails( ifds::RIFId, IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST );
   addFieldDetails( ifds::FundCode,          IFASTBP_PROC::RRIF_FROM_ALLOC_LIST );
   addFieldDetails( ifds::ClassCode,         IFASTBP_PROC::RRIF_FROM_ALLOC_LIST );
   addFieldDetails( ifds::AllocPercentage,   IFASTBP_PROC::RRIF_FROM_ALLOC_LIST );
   addFieldDetails( ifds::AllocAmount,       IFASTBP_PROC::RRIF_FROM_ALLOC_LIST );

   addFieldDetails( ifds::FundCode,          IFASTBP_PROC::RRIF_TO_ALLOC_LIST );
   addFieldDetails( ifds::ClassCode,         IFASTBP_PROC::RRIF_TO_ALLOC_LIST );
   addFieldDetails( ifds::AllocPercentage,   IFASTBP_PROC::RRIF_TO_ALLOC_LIST );
   addFieldDetails( ifds::AllocAmount,       IFASTBP_PROC::RRIF_TO_ALLOC_LIST );

/* taken out by yingbao----I do not see there is necessary
  addFieldDetails( DBR::NowPlanValue, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::PYEPlanValue, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::CalcMandYr, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::CalcMaxYr, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::PayTerm, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::Factor, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::MandAmtYrSysCalc, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::MaxAmtYrSysCalc, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::AcctValue, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::TotRedem, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::MandAmtPaySysCalc, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::AmountSysCalc, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::ProvRateSysCalc, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::FedRateSysCalc, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::NetAmountSysCalc, RRIF_LIF_LRIF_CALCULATE );
  addFieldDetails( DBR::CalcFedProvTax, RRIF_LIF_LRIF_CALCULATE );
*/
  
   addFieldDetails( RRIF_LIF_LRIF::ORG_KEY,  BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( RRIF_LIF_LRIF::DEST_KEY, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( RRIF_LIF_LRIF::IS_ORIGPLANDEFFAPPLIED,  BF::NullContainerId, SUBCLASS_PROCESS );
   
   //P0186486_FN03 - RRIF Annuities
   addFieldDetails( ifds::ExternalAssets,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   addFieldDetails(RRIF_LIF_LRIF::AreAllRRIFRecordsInactive, BF::NullContainerId, SUBCLASS_PROCESS); //added for CHG0041174
}

//******************************************************************************
RRIF_LIF_LRIF_InfoProcess::~RRIF_LIF_LRIF_InfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
/*
bool RRIF_LIF_LRIF_InfoProcess::doCancel( GenericInterface *rpGI )
{
  TRACE_METHOD( CLASSNAME, DOCANCEL );

  bool bRtn = false;
  return bRtn;
}
*/
//******************************************************************************
SEVERITY RRIF_LIF_LRIF_InfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   SEVERITY sevRtn  = SEVERE_ERROR;
   try
   {
      getParameter( ACCOUNT_NUMBER_FIELD, _strAccountNum );
      //getParameter( SHAREHOLDER_FIELD, _strShareholderNum );
      // getParameter( LAST_NAME_FIELD, _strLastName );
      // getParameter( FIRST_NAME_FIELD, _strFirstName );

      _strAccountNum.strip().stripLeading( I_CHAR( '0' ) );
      sevRtn = initLists( _strAccountNum );
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
   return(sevRtn);
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_InfoProcess::initLists( const DString& dstrAccountNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, INITLISTS );

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   MFAccount *pMFAccount;
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DString strAccount(dstrAccountNum);
   SEVERITY sevRtn = dstcWorkSession->getMFAccount( idDataGroup, dstrAccountNum, pMFAccount );
   if( NULL_STRING == _strShareholderNum )
   {
      pMFAccount->getField(ifds::ShrNum,_strShareholderNum,idDataGroup,false);
      _strShareholderNum.strip().stripLeading('0');
   }
   dstcWorkSession->getFirstSequenced01AccountholderEntityName( idDataGroup,strAccount, _strFirstName);


   _pRRIF_LIF_LRIF_PaymentsCalculation = new RRIF_LIF_LRIF_PaymentsCalculation( *dstcWorkSession );


   if( WARNING >= sevRtn )
   {
      bool bPermit = hasReadPermission(UAF::RIF_LIF_LRIF_INFO); 

      sevRtn = pMFAccount->getRRIF_LIF_LRIF_InfoList( _pRRIF_LIF_LRIF_InfoList, idDataGroup,true,bPermit );
      if( WARNING >= sevRtn && _pRRIF_LIF_LRIF_InfoList )
      {
         setContainer( IFASTBP_PROC::MFACCOUNT_CBO, pMFAccount );
         setContainer( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, _pRRIF_LIF_LRIF_InfoList );
      }
      else if( !_pRRIF_LIF_LRIF_InfoList )
      {
         ADDCONDITIONFROMFILE( CND::ERR_RRIF_INFO_NOT_APPLICABLE );
      }
   }
   return(sevRtn);
}
//******************************************************************************
bool RRIF_LIF_LRIF_InfoProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_RRIF_LIF_LRIF_INFO );
}

//******************************************************************************
E_COMMANDRETURN RRIF_LIF_LRIF_InfoProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );

   E_COMMANDRETURN rtn = CMD_FAILURE;
   try
   {
      if( isXMLAPIContext() )
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
      else
      {
         setParameter( ACCOUNT_NUMBER_FIELD, _strAccountNum );
         setParameter( SHAREHOLDER_FIELD, _strShareholderNum );
         //setParameter( LAST_NAME_FIELD, _strLastName );
         setParameter( FIRST_NAME_FIELD, _strFirstName );

         rtn = invokeCommand( this, CMD_GUI_RRIF_LIF_LRIF_INFO, getProcessType(), isModal(), &_rpChildGI );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************

bool RRIF_LIF_LRIF_InfoProcess::doOk( GenericInterface *rpGI )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOOK );
	if(_pRRIF_LIF_LRIF_InfoList->isUpdatedForDataGroup( getDataGroupId() ) )
	{
		MFAccount* pMFAccount  
         = dynamic_cast< MFAccount * >( getCBOItem( IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId() ) );
		if( pMFAccount )
		{
			pMFAccount->refreshMe(true);
		}
	}
   return(true);
}

//******************************************************************************

bool RRIF_LIF_LRIF_InfoProcess::doModelessSetFocus(
                                                  GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   SEVERITY severity = SEVERE_ERROR;
   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      DString dstrNewAccountNum;
      getParameter( ACCOUNT_NUM, dstrNewAccountNum );
      dstrNewAccountNum.strip().stripLeading( I_CHAR( '0' ) );

      DString dstrOldAccountNum;
      getField( rpGICaller, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrOldAccountNum );
      dstrOldAccountNum.strip().stripLeading( I_CHAR( '0' ) );

      if( dstrNewAccountNum != dstrOldAccountNum )
      {
         severity = initLists( dstrNewAccountNum );
         if( severity > WARNING )
            return(false);

         if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
            return(bRtn);// false
      }

      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
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

/*bool RRIF_LIF_LRIF_InfoProcess::doRefresh( GenericInterface *rpGICaller, 
                              const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   return true;
}*/

//******************************************************************************
void *RRIF_LIF_LRIF_InfoProcess::getPtrForContainer( const BFContainerId& idContainer, 
                                                     const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   // How do we handle init conditions??  (throw them?)
   try
   {
      if( IFASTBP_PROC::RRIF_FROM_ALLOC_LIST == idContainer )
      {
         {
            RRIF_LIF_LRIF_Info *pRRIF_LIF_LRIF_Info 
            = dynamic_cast< RRIF_LIF_LRIF_Info * >( getCBOItem( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, idDataGroup ) );
            FromFundAllocList *pAllocList = NULL;
            pRRIF_LIF_LRIF_Info->getFromFundAllocList( pAllocList, idDataGroup );
            ptr = pAllocList;
         }
      }
      else if(IFASTBP_PROC::RRIF_TO_ALLOC_LIST == idContainer )
      {
            RRIF_LIF_LRIF_Info *pRRIF_LIF_LRIF_Info 
            = dynamic_cast< RRIF_LIF_LRIF_Info * >( getCBOItem( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, idDataGroup ) );
            ToFundAllocList *pAllocList = NULL;
            pRRIF_LIF_LRIF_Info->getToFundAllocList( pAllocList, idDataGroup );
            ptr = pAllocList;		
		}
		else {
		
			assert(0); // should not run here
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
// If severity > warning, throw error ??
   return(ptr);
}

//******************************************************************************
bool RRIF_LIF_LRIF_InfoProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return( rpGICaller == NULL || _pRRIF_LIF_LRIF_InfoList == NULL ) ? 
   false : _pRRIF_LIF_LRIF_InfoList->doMoreRecordsExist();
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_InfoProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );

   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      DString strCallMode = I_("");
//CP20030319      switch( idSearch )
//CP20030319      {
//CP20030319         case RRIF_LIF_LRIF_INFO_LIST:
      if( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST == idSearch )
      {
         {
            sevRtn = _pRRIF_LIF_LRIF_InfoList->search( false );
         }
//CP20030319            break;
//CP20030319      }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}
//******************************************************************************
bool RRIF_LIF_LRIF_InfoProcess::doSend( GenericInterface* rpGICaller,const I_CHAR* szMessage )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSend") );
   bool valRtn = true;
   DString dstr( szMessage );

   if( dstr == I_( "CallView130" ) )
   {
      RRIF_LIF_LRIF_Info *pRRIF_LIF_LRIF_Info = dynamic_cast< RRIF_LIF_LRIF_Info * >( getCBOItem( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, getDataGroupId() ) );
      //   pRRIF_LIF_LRIF_Info->testIfCallingPaymentsCalculation( getReadOnlyGroupID ( rpGICaller ) );

      pRRIF_LIF_LRIF_Info->ForceToDoCalculation(getDataGroupId() );

   }
   else
   {
      valRtn = AbstractProcess::doSend( rpGICaller, szMessage );
   };
   return(valRtn);
}
//*******************************************************************************

SEVERITY RRIF_LIF_LRIF_InfoProcess::doValidateAll(
                                                 BFAbstractCBO *rpWSD,  const BFDataGroupId& idDataGroup   )
{

   return(_pRRIF_LIF_LRIF_InfoList->validateAll( idDataGroup ));


}
//*****************************************************************************************
SEVERITY RRIF_LIF_LRIF_InfoProcess::doSetField(
                                              const GenericInterface *rpGICaller,
                                              const BFContainerId& idContainer,
                                              const BFFieldId& idField,
                                              const BFDataGroupId& idDataGroup,
                                              const DString& strValue,
                                              bool bFormatted
                                              )
{  
   TRACE_METHOD( CLASSNAME, SETFIELD );

   if( BF::NullContainerId == idContainer && idField == RRIF_LIF_LRIF::ORG_KEY )
   {
      _dstrOrgKey = strValue;
   }
   else if( BF::NullContainerId == idContainer && idField == RRIF_LIF_LRIF::DEST_KEY )
   {
      _dstrDestKey = strValue;


      _pRRIF_LIF_LRIF_InfoList->AddCopy(_dstrOrgKey, _dstrDestKey, idDataGroup);
   }
   return(NO_CONDITION);

}

//******************************************************************************
void RRIF_LIF_LRIF_InfoProcess::doGetField ( const GenericInterface *rpGICaller,
                                             const BFContainerId &idContainer,
                                             const BFFieldId &idField,
                                             const BFDataGroupId &idDataGroup, 
                                             DString &strValueOut,
                                             bool bFormatted) const
{
	if (idContainer == BF::NullContainerId)
	{
		RRIF_LIF_LRIF_InfoProcess *rpNonConstThis = const_cast < RRIF_LIF_LRIF_InfoProcess*> ( this );
        BFAbstractCBO *rpPtr = rpNonConstThis->getCBOItem( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, idDataGroup );	 

		if(rpPtr)
		{
			if( idField == RRIF_LIF_LRIF::IS_ORIGPLANDEFFAPPLIED )
			{
			    rpPtr->getField(ifds::OrigPlanDeffApplied, strValueOut, idDataGroup, false);
			}
		}	
	}
   //chnages for CHG0041174 Starts
   if (idField == RRIF_LIF_LRIF::AreAllRRIFRecordsInactive)
   {
	   RRIF_LIF_LRIF_InfoList *pRRIF_LIF_LRIF_InfoList =  dynamic_cast < RRIF_LIF_LRIF_InfoList*> (( const_cast < RRIF_LIF_LRIF_InfoProcess *> ( this ) )->getCBOList (IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, idDataGroup));

		if(pRRIF_LIF_LRIF_InfoList)
		{
			strValueOut = pRRIF_LIF_LRIF_InfoList->areAllRRIFRecordsInactive (idDataGroup) ? I_("Y"): I_("N");
		}
   }
  //changes for CHG0041174 ends
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RRIF_LIF_LRIF_InfoProcess.cpp-arc  $
 * 
 *    Rev 1.47   Apr 20 2012 04:05:42   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.46   Feb 13 2012 04:18:18   panatcha
 * P0186486_FN03 - RRIF Annuities
 * 
 *    Rev 1.45   Oct 04 2010 06:23:40   kitticha
 * PET0168176 FN01 Locked In Product Changes.
 * 
 *    Rev 1.44   Jul 21 2010 08:31:42   kitticha
 * PET0168176 FN01 - Locked In Product.
 * 
 *    Rev 1.43   05 May 2008 15:04:08   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.42   24 Apr 2008 13:35:36   kovacsro
 * PET2255 FN47 - New Ontario LIF - added EligExtTrfGainLoss
 * 
 *    Rev 1.41   Jan 22 2008 15:42:46   yingz
 * fix incident 1110884 - bank infor display problem
 * 
 *    Rev 1.40   Nov 30 2007 18:31:14   daechach
 * PET5517 FN 97 - RRIF Net of Fees
 * 
 *    Rev 1.39   Aug 10 2007 17:06:56   smithdav
 * PET2360 FN76,91
 * 
 *    Rev 1.38   Sep 06 2006 11:23:24   porteanm
 * PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt.
 * 
 *    Rev 1.37   Mar 06 2006 10:27:16   popescu
 * Fixed linker warning
 * 
 *    Rev 1.36   Mar 03 2004 16:21:20   popescu
 * PTS 10027578, refresh the account information after updating the mailing address info and demographics info; changed the name of the refreshMe method, to be consistent with the shareholder object
 * 
 *    Rev 1.35   Sep 15 2003 14:17:28   YINGBAOL
 * PTS10020348 Refresh Default  Allocation
 * 
 *    Rev 1.34   Jun 09 2003 11:33:52   YINGBAOL
 * RRIF Allocation enhancement
 * 
 *    Rev 1.33   Mar 21 2003 17:47:30   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.32   Mar 09 2003 15:56:34   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.31   Jan 12 2003 16:38:56   YINGBAOL
 * RRIF Enhancement for Dynamic
 * 
 *    Rev 1.30   Oct 09 2002 23:53:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.29   Oct 08 2002 11:58:58   HSUCHIN
 * PTS 10010112 - condition frame fix
 * 
 *    Rev 1.28   Aug 29 2002 16:45:14   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.27   Aug 29 2002 12:54:38   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.26   Aug 06 2002 09:58:50   KOVACSRO
 * Release 48. Converted allocations.
 * 
 *    Rev 1.25   Jul 23 2002 10:19:56   FENGYONG
 * Add name for API
 * 
 *    Rev 1.24   Jun 03 2002 16:55:34   HSUCHIN
 * bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
 * 
 *    Rev 1.23   Jun 03 2002 16:42:26   FENGYONG
 * Add name for API
 * 
 *    Rev 1.22   22 May 2002 18:25:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.21   27 Mar 2002 19:55:38   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.20   Nov 14 2001 15:13:24   YINGBAOL
 * sync. up 18.1.1
 * 
 *    Rev 1.19   26 Oct 2001 11:07:38   SMITHDAV
 * hasPermission changes
 * 
 *    Rev 1.18   Oct 16 2001 11:42:16   YINGBAOL
 * fix title bar
 * 
 *    Rev 1.17   Jul 16 2001 17:17:06   ZHANGCEL
 * Fixed the crash which causes by    call "getBFWorkSession()"  in the constructor;
 * 
 *    Rev 1.16   15 May 2001 15:38:54   YINGZ
 * data group id clean up
 * 
 *    Rev 1.15   03 May 2001 14:05:38   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.14   Jan 08 2001 10:16:00   ZHANGCEL
 * Synchronized to C2/C3
 * 
 *    Rev 1.13   Dec 18 2000 17:39:36   WINNIE
 * No RRIF screen/ RRIF record  for external RRIF
 * 
 *    Rev 1.12   Nov 03 2000 11:31:44   YINGBAOL
 * BFBase change sync.
 * 
 *    Rev 1.11   Oct 17 2000 14:59:14   YINGBAOL
 * add addcopy function and fix other issues
 * 
 *    Rev 1.10   Oct 03 2000 13:32:28   YINGBAOL
 * add parent child relationship for RRIF_LRIF info and allocationlist
 * 
 *    Rev 1.9   Sep 28 2000 14:55:28   YINGBAOL
 * check permission and change validation logic
 * 
 *    Rev 1.8   Aug 30 2000 14:37:32   PETOLESC
 * Modified crossedits and logic to call view 130.
 * 
 *    Rev 1.7   Jul 18 2000 13:48:18   PETOLESC
 * Modified title bar for the RRIF dialog.
 * 
 *    Rev 1.6   Jun 28 2000 15:00:44   PETOLESC
 * Added Frequency field, changed logic for view 130 call sequence and a BIG bunch of other changes.
 * 
 *    Rev 1.5   Jun 09 2000 18:01:38   PETOLESC
 * Save work.
 * 
 *    Rev 1.4   May 19 2000 17:29:52   PETOLESC
 * save work
 * 
 *
 */
