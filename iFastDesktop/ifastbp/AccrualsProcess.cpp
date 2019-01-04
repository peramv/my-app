//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial.
//
//******************************************************************************
//
// ^FILE   : AccrualsProcess.cpp
// ^AUTHOR : 
// ^DATE   : Jan 09, 2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AccrualsProcess
//    This class manages the remarks information. <-- Really???
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\accrualslist.hpp>
#include "accrualsprocess.hpp"
#include "accrualsprocessincludes.h"
#include <ifastcbo\accrualssearchcriteria.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastcbo\mgmtco.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCRUALS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCRUALS;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AccrualsProcess > processCreator( CMD_BPROC_ACCRUALS );

//******************************************************************************
// MF - Management Fee
// MFR - Management Fee Rebate
//******************************************************************************

namespace
{
   // Trace literals
   const I_CHAR * const ACCOUNT_NUM             = I_( "AccountNum" );
   const I_CHAR * const CLASS_CODE              = I_( "ClassCode" );
   const I_CHAR * const CLASSNAME               = I_( "AccrualsProcess" );
   const I_CHAR * const END_DATE                = I_( "EndDate" );   
   const I_CHAR * const FUND_CODE               = I_( "FundCode" );
   const I_CHAR * const INC_UNSETTLED           = I_( "InclUnsettled ");
   const I_CHAR * const INTEREST_ACCRUAL_TYPE   = I_( "01" );
   const I_CHAR * const MF_ACCRUAL_TYPE         = I_( "02" );
   const I_CHAR * const MF_REBATE_ACCRUAL_TYPE  = I_( "03" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const PERFORMSEARCH           = I_( "performSearch" );   
   const I_CHAR * const START_DATE              = I_( "StartDate" );     
   const I_CHAR * const SUMMARY                 = I_( "S" );   
   const I_CHAR * const YES                     = I_( "Y" );      
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AccrualSummary;
   extern CLASS_IMPORT const BFDecimalFieldId Accum;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFDecimalFieldId AmtPaid;
   extern CLASS_IMPORT const BFDecimalFieldId DailyAmount;
   extern CLASS_IMPORT const BFTextFieldId Description;
   extern CLASS_IMPORT const BFDecimalFieldId EligUnits;
   extern CLASS_IMPORT const BFDateFieldId EndDate;
   extern CLASS_IMPORT const BFDecimalFieldId GSTAmt;
   extern CLASS_IMPORT const BFDecimalFieldId NRTaxAmt;
   extern CLASS_IMPORT const BFDecimalFieldId Paid;
   extern CLASS_IMPORT const BFDecimalFieldId PaidInclude;
   extern CLASS_IMPORT const BFDateFieldId StartDate;
}

//******************************************************************************
// Constructor - Container and field details are initialized here.
//******************************************************************************

AccrualsProcess::AccrualsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pInterestAccrualDetailsList( NULL ),
_pInterestAccrualSummaryList( NULL ),
_pMFAccrualsList ( NULL ),
_pMFRAccrualsList ( NULL ),
_pMFAccrualsSummaryList ( NULL ),
_pMFRAccrualsSummaryList ( NULL ),
_pInterestSearchCriteria ( NULL ),
_pMFSearchCriteria ( NULL ),
_pMFRSearchCriteria ( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //readonly
   addContainer( IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST,  true,  BF::NullContainerId, false ); 
   addContainer( IFASTBP_PROC::MF_ACCRUAL_LIST,                true,  BF::NullContainerId, false );  
   addContainer( IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST,         true,  BF::NullContainerId, false );
   addContainer( IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST,  true,  BF::NullContainerId, false ); 
   addContainer( IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST,        true,  BF::NullContainerId, false );  
   addContainer( IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST, true,  BF::NullContainerId, false );

   addContainer( IFASTBP_PROC::MFACCOUNT_CBO,                  false, BF::NullContainerId, false );

   // The search criteria needs to be updatable
   addContainer( IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO,   false, BF::NullContainerId, true );
   addContainer( IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO,         false, BF::NullContainerId, true );
   addContainer( IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO,  false, BF::NullContainerId, true );

   // Substitution List
   addSubstituteList(ifds::AccrualType);

   // Interest Search Criteria

   addFieldDetails( ifds::FundNumber,     IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO );   
   addFieldDetails( ifds::FundCode,       IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::ClassCode,      IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::StartDate,      IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::EndDate,        IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::InclUnsettled,  IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::AccrualSummary, IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO );   

   // MF Search Criteria

   addFieldDetails( ifds::FundNumber,     IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO );   
   addFieldDetails( ifds::FundCode,       IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::ClassCode,      IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::StartDate,      IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::EndDate,        IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::InclUnsettled,  IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::AccrualSummary, IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO );   

   // MFR Search Criteria

   addFieldDetails( ifds::FundNumber,     IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO );   
   addFieldDetails( ifds::FundCode,       IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::ClassCode,      IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::StartDate,      IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::EndDate,        IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::InclUnsettled,  IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO );
   addFieldDetails( ifds::AccrualSummary, IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO );   


   // Interest Accruals - Details
   addFieldDetails( ifds::RecType,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST );
   addFieldDetails( ifds::rxFundCode,     IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST );
   addFieldDetails( ifds::rxClassCode,    IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST );
   addFieldDetails( ifds::AsofDate,       IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST );
   addFieldDetails( ifds::EligibleUnits,  IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST );
   addFieldDetails( ifds::IntRate,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST );
   addFieldDetails( ifds::IntValue,       IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST );
   addFieldDetails( ifds::IntPaid,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST );
   addFieldDetails( ifds::AccumTotal,     IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST );
   addFieldDetails( TOTALS_FIELD1,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD2,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD3,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD4,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD5,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD6,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD7,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD8,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD9,        IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST,  SUBCLASS_PROCESS );

   // Interest Accruals - Summary
   addFieldDetails( ifds::RecType,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::rxFundCode,     IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::rxClassCode,    IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::AsofDate,       IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::EligibleUnits,  IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::IntRate,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::IntValue,       IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::IntPaid,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::AccumTotal,     IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( TOTALS_FIELD1,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD2,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD3,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD4,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD5,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD6,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD7,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD8,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD9,        IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST,  SUBCLASS_PROCESS );


   // MF Accruals Details
   addFieldDetails( ifds::RecType,        IFASTBP_PROC::MF_ACCRUAL_LIST );
   addFieldDetails( ifds::rxFundCode,     IFASTBP_PROC::MF_ACCRUAL_LIST );
   addFieldDetails( ifds::rxClassCode,    IFASTBP_PROC::MF_ACCRUAL_LIST );
   addFieldDetails( ifds::AsofDate,       IFASTBP_PROC::MF_ACCRUAL_LIST );
   addFieldDetails( ifds::EligUnits,      IFASTBP_PROC::MF_ACCRUAL_LIST );
   addFieldDetails( ifds::Amount,         IFASTBP_PROC::MF_ACCRUAL_LIST );
   addFieldDetails( ifds::GSTAmt,         IFASTBP_PROC::MF_ACCRUAL_LIST );
   addFieldDetails( ifds::AmtPaid,        IFASTBP_PROC::MF_ACCRUAL_LIST );
   addFieldDetails( ifds::AccumTotal,     IFASTBP_PROC::MF_ACCRUAL_LIST );
   addFieldDetails( ifds::NRTaxAmt,       IFASTBP_PROC::MF_ACCRUAL_LIST );
   addFieldDetails( ifds::PaidInclude,    IFASTBP_PROC::MF_ACCRUAL_LIST );
   addFieldDetails( TOTALS_FIELD1,        IFASTBP_PROC::MF_ACCRUAL_LIST,                SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD2,        IFASTBP_PROC::MF_ACCRUAL_LIST,                SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD3,        IFASTBP_PROC::MF_ACCRUAL_LIST,                SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD4,        IFASTBP_PROC::MF_ACCRUAL_LIST,                SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD5,        IFASTBP_PROC::MF_ACCRUAL_LIST,                SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD6,        IFASTBP_PROC::MF_ACCRUAL_LIST,                SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD7,        IFASTBP_PROC::MF_ACCRUAL_LIST,                SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD8,        IFASTBP_PROC::MF_ACCRUAL_LIST,                SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD9,        IFASTBP_PROC::MF_ACCRUAL_LIST,                SUBCLASS_PROCESS );


   // MF Accruals Summary
   addFieldDetails( ifds::RecType,        IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::rxFundCode,     IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::rxClassCode,    IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::AsofDate,       IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::EligUnits,      IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::Amount,         IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::GSTAmt,         IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::AmtPaid,        IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::AccumTotal,     IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::NRTaxAmt,       IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::PaidInclude,    IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( TOTALS_FIELD1,        IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST,        SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD2,        IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST,        SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD3,        IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST,        SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD4,        IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST,        SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD5,        IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST,        SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD6,        IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST,        SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD7,        IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST,        SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD8,        IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST,        SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD9,        IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST,        SUBCLASS_PROCESS );

   // MFR Accruals Details
   addFieldDetails( ifds::RecType,        IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );
   addFieldDetails( ifds::rxFundCode,     IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );
   addFieldDetails( ifds::rxClassCode,    IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );
   addFieldDetails( ifds::AsofDate,       IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );
   addFieldDetails( ifds::EligUnits,      IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );
   addFieldDetails( ifds::Amount,         IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );
   addFieldDetails( ifds::GSTAmt,         IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );
   addFieldDetails( ifds::AmtPaid,        IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );
   addFieldDetails( ifds::AccumTotal,     IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );
   addFieldDetails( ifds::NRTaxAmt,       IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );
   addFieldDetails( ifds::PaidInclude,    IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );
   addFieldDetails( TOTALS_FIELD1,        IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST,         SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD2,        IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST,         SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD3,        IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST,         SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD4,        IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST,         SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD5,        IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST,         SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD6,        IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST,         SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD7,        IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST,         SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD8,        IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST,         SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD9,        IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST,         SUBCLASS_PROCESS );

   // MFR Accruals Summary
   addFieldDetails( ifds::RecType,        IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::rxFundCode,     IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::rxClassCode,    IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::AsofDate,       IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::EligUnits,      IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::Amount,         IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::GSTAmt,         IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::AmtPaid,        IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::AccumTotal,     IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::NRTaxAmt,       IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( ifds::PaidInclude,    IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );
   addFieldDetails( TOTALS_FIELD1,        IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD2,        IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD3,        IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD4,        IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD5,        IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD6,        IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD7,        IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD8,        IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( TOTALS_FIELD9,        IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST, SUBCLASS_PROCESS );

   // General Account information.
   addFieldDetails( ifds::AccountNum,     IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::ShrNum,         IFASTBP_PROC::MFACCOUNT_CBO);   
}

//******************************************************************************
// Destructor - Since accruals are not held in the repository, we need to delete
// the cbos when we are finish with them.
//******************************************************************************

AccrualsProcess::~AccrualsProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( _pInterestAccrualDetailsList )
   {
      delete _pInterestAccrualDetailsList;
      _pInterestAccrualDetailsList = NULL;
   }

   if( _pMFAccrualsList )
   {
      delete _pMFAccrualsList;
      _pMFAccrualsList = NULL;
   }

   if( _pMFRAccrualsList )
   {
      delete _pMFRAccrualsList;
      _pMFRAccrualsList = NULL;
   }

   if( _pInterestSearchCriteria )
   {
      delete _pInterestSearchCriteria;
      _pInterestSearchCriteria = NULL;
   }
   if( _pMFSearchCriteria )
   {
      delete _pMFSearchCriteria;
      _pMFSearchCriteria = NULL;
   }

   if( _pMFRSearchCriteria )
   {
      delete _pMFRSearchCriteria;
      _pMFRSearchCriteria = NULL;
   }

   if( _pInterestAccrualSummaryList )
   {
      delete _pInterestAccrualSummaryList;
      _pInterestAccrualSummaryList = NULL;
   }

   if( _pMFAccrualsSummaryList )
   {
      delete _pMFAccrualsSummaryList;
      _pMFAccrualsSummaryList = NULL;
   }

   if( _pMFRAccrualsSummaryList )
   {
      delete _pMFRAccrualsSummaryList;
      _pMFRAccrualsSummaryList = NULL;
   }
}

//******************************************************************************
// Function which get the container pointer on demand.
// @param   const BFContainerId& idContainer - Id to the container.
//          const BFDataGroupId& idDataGroup - group id.
// @returns void.
//******************************************************************************

void *AccrualsProcess::getPtrForContainer( const BFContainerId& idContainer,
                                           const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   try
   {
      // RSP Contribution List
      if( IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO == idContainer )
      {
         {            
            _pInterestSearchCriteria = dynamic_cast< AccrualsSearchCriteria * >( getCBOItem( IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO, idDataGroup ) );
            if( _pInterestSearchCriteria )
               ptr = _pInterestSearchCriteria;
         }
      }
      else if( IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO == idContainer )
      {
         {
            _pMFSearchCriteria = dynamic_cast< AccrualsSearchCriteria * >( getCBOItem( IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO, idDataGroup ) );
            if( _pMFSearchCriteria )
               ptr = _pMFSearchCriteria;
         }
      }
      else if( IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO == idContainer )
      {
         {
            _pMFRSearchCriteria = dynamic_cast< AccrualsSearchCriteria * >( getCBOItem( IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO, idDataGroup ) );
            if( _pMFRSearchCriteria )
               ptr = _pMFRSearchCriteria;
         }
      }
      else if( IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST == idContainer )
      {
         ptr = _pInterestAccrualDetailsList;
      }
      else if( IFASTBP_PROC::MF_ACCRUAL_LIST == idContainer )
      {
         ptr = _pMFAccrualsList;
      }
      else if( IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST == idContainer )
      {
         ptr = _pMFRAccrualsList;
      }
      else if( IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST == idContainer )
      {
         ptr = _pInterestAccrualSummaryList;
      }
      else if( IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST == idContainer )
      {
         ptr = _pMFAccrualsSummaryList;
      }
      else if( IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST == idContainer )
      {
         ptr = _pMFRAccrualsSummaryList;
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      //Show we throw?
   }
   return(ptr);
}

//******************************************************************************
// Override for field which are defined in the Constructor as SUBCLASS_PROCESS.
// The following fields are processed.
// TOTAL_FIELD1
// TOTAL_FIELD2
// TOTAL_FIELD3
// TOTAL_FIELD4
// TOTAL_FIELD5
// TOTAL_FIELD6
// TOTAL_FIELD7
// @param   const GenericInterface *rpGICaller - pointer to parent object.
//          const BFContainerId& idContainer - container id.
//          const BFFieldId& idField - field requested.
//          const BFDataGroupId& idDataGroup - group id.
//          DString &strValueOut - Field value returned.
//          bool bFormatted - boolean indicating value to be formatted or not.
// @returns void.
//******************************************************************************

void AccrualsProcess::doGetField( const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId& idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOGETFIELD );
   AccrualsList *ptr;
   if( IFASTBP_PROC::MF_ACCRUAL_LIST == idContainer )
   {
      ptr = _pMFAccrualsList;
   }
   else if( IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST == idContainer )
   {
      ptr = _pMFRAccrualsList;
   }
   else if( IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST == idContainer )
   {
      ptr = _pMFAccrualsSummaryList;
   }
   else if( IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST == idContainer )
   {
      ptr = _pMFRAccrualsSummaryList;
   }
   else if( IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST == idContainer )
   {
      ptr = _pInterestAccrualDetailsList;
   }
   else if( IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST == idContainer )
   {
      ptr=_pInterestAccrualSummaryList;
   }
   else
   {
      assert (0);
   }

   if( ptr == NULL )
   {
      strValueOut == NULL_STRING;
      return;
   }

   if( ( idContainer == IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST ) ||
       ( idContainer == IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST ) )
   {
      if( idField == TOTALS_FIELD1 )
      {
         strValueOut = ptr->getTotalEarned();
      }
      else if( idField == TOTALS_FIELD2 )
      {
         strValueOut = ptr->getTotalPaid();
      }
      else if( idField == TOTALS_FIELD3 )
      {
         strValueOut = ptr->getTotalAccumTotal();
      }
      else
      {
         strValueOut == NULL_STRING;
      }         
   }
   else
   {
      if( idField == TOTALS_FIELD1 )
      {
         strValueOut = ptr->getTotalEarned();
      }
      else if( idField == TOTALS_FIELD2 )
      {
         strValueOut = ptr->getTotalPaid();
      }
      else if( idField == TOTALS_FIELD3 )
      {
         strValueOut = ptr->getTotalAccumTotal();
      }
      else if( idField == TOTALS_FIELD4 )
      {
         _pMFAccount->getField ( ifds::GSTExempt, strValueOut, idDataGroup, true );
      }
      else if( idField == TOTALS_FIELD5 )
      {
         strValueOut = ptr->getTotalGSTPaid();
      }
      else if( idField == TOTALS_FIELD6 )
      {
         strValueOut = ptr->getTotalNRTaxPaid();
      }
      else if( idField == TOTALS_FIELD7 )
      {
         _pMFAccount->getField ( ifds::ApplyPST, strValueOut, idDataGroup, true );
      }
      else if( idField == TOTALS_FIELD8 )
      {
         strValueOut = ptr->getTotalGSTOutstanding ();
      }
      else if( idField == TOTALS_FIELD9 )
      {
         strValueOut = ptr->getTotalNRTaxOutstanding ();
      }
      else
      {
         strValueOut == NULL_STRING;
      }
   } 
}

//******************************************************************************
// Initializes all the search criteria cbos and accrual list cbos.
// @returns SEVERITY.
//******************************************************************************

SEVERITY AccrualsProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( ACCOUNT_NUM, _dstrAccountNum );     
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      sevRtn = pDSTCWorkSession->getMFAccount( getDataGroupId(), _dstrAccountNum, _pMFAccount );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount );
      }
      _pInterestSearchCriteria = new AccrualsSearchCriteria ( *getBFWorkSession() );
      _pInterestSearchCriteria->init ( _dstrAccountNum, INTEREST_ACCRUAL_TYPE, BF::HOST );
      setContainer ( IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO, _pInterestSearchCriteria );
      _pMFSearchCriteria = new AccrualsSearchCriteria ( *getBFWorkSession() );
      _pMFSearchCriteria->init ( _dstrAccountNum, MF_ACCRUAL_TYPE, BF::HOST );
      setContainer ( IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO, _pMFSearchCriteria );
      _pMFRSearchCriteria = new AccrualsSearchCriteria ( *getBFWorkSession() );
      _pMFRSearchCriteria->init ( _dstrAccountNum, MF_REBATE_ACCRUAL_TYPE, BF::HOST );
      setContainer ( IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO, _pMFRSearchCriteria );
      setContainer( IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST, 0 );
      setContainer( IFASTBP_PROC::MF_ACCRUAL_LIST, 0 );
      setContainer( IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST, 0 );
      setContainer( IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST, 0 );
      setContainer( IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST, 0 );
      setContainer( IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST, 0 );
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
// Function which tells the generic interface container that the modeless child
// has been destroyed.
// @param   const Command &cmd - cmd indicating the child is destroyed.
// @returns bool - true when successful.
//******************************************************************************

bool AccrualsProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE );

   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ACCRUALS );
}


//******************************************************************************
// Functions which brings the Accrual dialog to focus and top of the window 
// stack.  It also notifies Accruals to refresh in case account information 
// has changed.
// @param   GenericInterface *rpGICaller - pointer to parent object.
// @return bool - true when successful, false otherwise.
//******************************************************************************

bool AccrualsProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
         DString dstrNewAccountNum;
         getParameter( ACCOUNT_NUM, dstrNewAccountNum );
         if( dstrNewAccountNum != _dstrAccountNum )
         {
            if( _pInterestAccrualDetailsList )
            {
               delete _pInterestAccrualDetailsList;
               _pInterestAccrualDetailsList = NULL;
            }

            if( _pMFAccrualsList )
            {
               delete _pMFAccrualsList;
               _pMFAccrualsList = NULL;
            }

            if( _pMFRAccrualsList )
            {
               delete _pMFRAccrualsList;
               _pMFRAccrualsList = NULL;
            }

            if( _pInterestSearchCriteria )
            {
               delete _pInterestSearchCriteria;
               _pInterestSearchCriteria = NULL;
            }
            if( _pMFSearchCriteria )
            {
               delete _pMFSearchCriteria;
               _pMFSearchCriteria = NULL;
            }

            if( _pMFRSearchCriteria )
            {
               delete _pMFRSearchCriteria;
               _pMFRSearchCriteria = NULL;
            }

            if( _pInterestAccrualSummaryList )
            {
               delete _pInterestAccrualSummaryList;
               _pInterestAccrualSummaryList = NULL;
            }

            if( _pMFAccrualsSummaryList )
            {
               delete _pMFAccrualsSummaryList;
               _pMFAccrualsSummaryList = NULL;
            }

            if( _pMFRAccrualsSummaryList )
            {
               delete _pMFRAccrualsSummaryList;
               _pMFRAccrualsSummaryList = NULL;
            }

            doInit();
         }
         bRtn = _rpChildGI->refresh( this, NULL );
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
      }
      return(bRtn);
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
   return(false);
}

//******************************************************************************
// This functions starts the Accruals Dialog
// @returns E_COMMANDRETURN.
//******************************************************************************

E_COMMANDRETURN AccrualsProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_ACCRUALS, getProcessType(),
                           isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
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

//******************************************************************************
// This function is called by the accruals dialog to initiate a new search.
// @param   GenericInterface *rpGICaller - pointer to parent object.
//          const BFContainerId& idSearch - Type of search is requested.
//          E_SEARCHACTION eSearchAction - SEARCH_START (new search)
//                                         SEARCH_NEXT_BLOCK ( get More )
//******************************************************************************

SEVERITY AccrualsProcess::performSearch( GenericInterface *rpGICaller, 
                                         const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;
   const BFDataGroupId& idDataGroup = getDataGroupId ();
   try
   {
      switch( eSearchAction )
      {
         case SEARCH_START:
            {
               if( IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST == idSearch
                   || IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST == idSearch )
               {
                  {
                     sevRtn = _pInterestSearchCriteria->validateAll (idDataGroup );
                     if( sevRtn > WARNING )
                        return(sevRtn);

                     if( idSearch == IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST )
                     {
                        if( _pInterestAccrualDetailsList != NULL )
                        {
                           delete _pInterestAccrualDetailsList;
                           _pInterestAccrualDetailsList = NULL;
                        }
                        _pInterestAccrualDetailsList = new AccrualsList ( *getBFWorkSession() );
                        sevRtn = _pInterestAccrualDetailsList->init ( _pInterestSearchCriteria, idDataGroup );                           
                     }
                     else
                     {
                        if( _pInterestAccrualSummaryList != NULL )
                        {
                           delete _pInterestAccrualSummaryList;
                           _pInterestAccrualSummaryList = NULL;
                        }
                        _pInterestAccrualSummaryList = new AccrualsList ( *getBFWorkSession() );
                        sevRtn = _pInterestAccrualSummaryList->init( _pInterestSearchCriteria, idDataGroup );
                     }
                  }
               }
               else if( IFASTBP_PROC::MF_ACCRUAL_LIST == idSearch
                        || IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST == idSearch )
               {
                  {
                     sevRtn = _pMFSearchCriteria->validateAll (idDataGroup );
                     if( sevRtn > WARNING )
                        return(sevRtn);
                     if( idSearch == IFASTBP_PROC::MF_ACCRUAL_LIST )
                     {
                        if( _pMFAccrualsList != NULL )
                        {
                           delete _pMFAccrualsList;
                           _pMFAccrualsList = NULL;
                        }
                        _pMFAccrualsList = new AccrualsList ( *getBFWorkSession() );
                        sevRtn = _pMFAccrualsList->init ( _pMFSearchCriteria, idDataGroup );
                     }
                     else
                     {
                        if( _pMFAccrualsSummaryList != NULL )
                        {
                           delete _pMFAccrualsSummaryList;
                           _pMFAccrualsSummaryList = NULL;
                        }
                        _pMFAccrualsSummaryList = new AccrualsList ( *getBFWorkSession() );
                        sevRtn = _pMFAccrualsSummaryList->init( _pMFSearchCriteria, idDataGroup );
                     }
                  }
               }
               else if( IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST == idSearch
                        || IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST == idSearch )
               {
                  {
                     sevRtn = _pMFRSearchCriteria->validateAll (idDataGroup );
                     if( sevRtn > WARNING )
                        return(sevRtn);
                     if( idSearch == IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST )
                     {
                        if( _pMFRAccrualsList != NULL )
                        {
                           delete _pMFRAccrualsList;
                           _pMFRAccrualsList = NULL;
                        }
                        _pMFRAccrualsList = new AccrualsList ( *getBFWorkSession() );
                        sevRtn = _pMFRAccrualsList->init ( _pMFRSearchCriteria, idDataGroup );
                     }
                     else
                     {
                        if( _pMFRAccrualsSummaryList != NULL )
                        {
                           delete _pMFRAccrualsSummaryList;
                           _pMFRAccrualsSummaryList = NULL;
                        }
                        _pMFRAccrualsSummaryList = new AccrualsList ( *getBFWorkSession() );
                        sevRtn = _pMFRAccrualsSummaryList->init( _pMFRSearchCriteria, idDataGroup );
                     }
                  }

               }
               else
               {
               }
            }
            break;
         case SEARCH_NEXT_BLOCK:
            {
               if( IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST == idSearch )
               {
                  {
                     sevRtn = _pInterestAccrualDetailsList->getMore ();
                  }
               }
               else if( IFASTBP_PROC::MF_ACCRUAL_LIST == idSearch )
               {
                  {
                     sevRtn = _pMFAccrualsList->getMore ();
                  }
               }
               else if( IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST == idSearch )
               {
                  {
                     sevRtn = _pMFRAccrualsList->getMore ();
                  }
               }
            }
            break;
         default:
            break;
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
// Function called by accruals dialog which returns true/false depending on
// whether there exist more data in the database.
// @param   GenericInterface *rpGICaller - pointer to parent object.
//          in idSearch - Type of search is requested.
// @returns bool - true if there are more data
//                 false otherwise.
//******************************************************************************

bool AccrualsProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   if( rpGICaller == NULL )
      return(false);

   if( IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST == idSearch )
   {
      {
         return( _pInterestAccrualDetailsList == NULL ) ? false : _pInterestAccrualDetailsList->doMoreRecordsExist();
      }
   }
   else if( IFASTBP_PROC::MF_ACCRUAL_LIST == idSearch )
   {
      {
         return( _pMFAccrualsList == NULL ) ? false : _pMFAccrualsList->doMoreRecordsExist();
      }
   }
   else if( IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST == idSearch )
   {
      {
         return( _pMFRAccrualsList == NULL ) ? false : _pMFRAccrualsList->doMoreRecordsExist();
      }
   }
   else if( IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST == idSearch )
   {
      {
         return( _pInterestAccrualSummaryList == NULL ) ? false : _pInterestAccrualSummaryList->doMoreRecordsExist();
      }
   }
   else if( IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST == idSearch )
   {
      {
         return( _pMFAccrualsSummaryList == NULL ) ? false : _pMFAccrualsSummaryList->doMoreRecordsExist();
      }
   }
   else if( IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST == idSearch )
   {
      {
         return( _pMFRAccrualsSummaryList == NULL ) ? false : _pMFRAccrualsSummaryList->doMoreRecordsExist();
      }
   }
   // shouldn't get here.
   return(false);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccrualsProcess.cpp-arc  $
// 
//    Rev 1.16   Apr 02 2003 12:19:20   PURDYECH
// Code cleanup
// 
//    Rev 1.15   Mar 21 2003 17:34:52   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.14   Mar 06 2003 10:24:00   PURDYECH
// Fixed up comments so that auto-conversion for datagroups will proceed properly.
// 
//    Rev 1.13   Oct 09 2002 23:53:00   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.12   Aug 29 2002 16:42:32   SMITHDAV
// Condition split.
// 
//    Rev 1.11   Aug 29 2002 12:54:10   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.10   22 May 2002 22:22:56   PURDYECH
// BFData Implementation
// 
//    Rev 1.9   16 Apr 2002 14:48:58   HSUCHIN
// changed impl to get totals from AccrualList CBO
// 
//    Rev 1.8   04 Apr 2002 13:48:56   HSUCHIN
// reworked the way the total fields were calculated and retrieved.
// 
//    Rev 1.7   27 Mar 2002 19:54:30   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.6   20 Mar 2002 16:43:54   HSUCHIN
// added support for Daily NR Tax
// 
//    Rev 1.5   12 Mar 2002 10:27:34   HSUCHIN
// added support for summary containers for accruals
// 
//    Rev 1.4   07 Mar 2002 16:35:44   HSUCHIN
// added support for new fields
// 
//    Rev 1.3   06 Mar 2002 17:14:34   HSUCHIN
// force validation before search and return highest severity.
// 
//    Rev 1.2   27 Feb 2002 16:09:38   HSUCHIN
// bug fix and memory leak clean up
// 
//    Rev 1.1   26 Feb 2002 16:52:38   HSUCHIN
// view changes fixes and completion of MF/MFR
// 
//    Rev 1.0   21 Feb 2002 16:01:46   HSUCHIN
// Initial revision.
 */
