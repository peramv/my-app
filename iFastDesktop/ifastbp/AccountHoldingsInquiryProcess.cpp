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
// ^FILE   : AccountHoldingsInquiryProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AccountHoldingsInquiryProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "accountholdingsinquiryprocess.hpp"
#include <ifastcbo\accountholdingsbycurrency.hpp>
#include <ifastcbo\accountdistributionlist.hpp>
#include <ifastcbo\acblist.hpp>
#include <ifastcbo\freeunitlist.hpp>
#include <ifastcbo\fundclassholdingslist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0020_req.hpp>
#include <ifastdataimpl\dse_dstc0020_vw.hpp>
#include <ifastdataimpl\dse_dstc0015_vw.hpp>
#include <ifastdataimpl\dse_dstc0016_vw.hpp>
#include <ifastdataimpl\dse_dstc0019_vw.hpp>
#include "accountholdingsinquiryprocessincludes.h"
#include <ifastcbo\fundclassholding.hpp>
#include <ifastcbo\mfaccountholdinglist.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNTHOLDINGSINQUIRY;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AccountHoldingsInquiryProcess > processCreator( CMD_BPROC_ACCOUNTHOLDINGSINQUIRY );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccountHoldingsInquiryProcess" );
   const I_CHAR * const AS_OF_DATE = I_( "AsofDate" );
}

namespace ACCTHOLDINGSLIT  //stands for account details literals
{
   const I_CHAR * const ACCOUNT_NUMBER_FIELD = I_( "TXAccountNum" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId TotBookValue;
   extern CLASS_IMPORT const BFDecimalFieldId TotMkTValue;
   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
   extern CLASS_IMPORT const BFDecimalFieldId TotPercentage;
   extern CLASS_IMPORT const BFDecimalFieldId TotTenPercFree;
   extern CLASS_IMPORT const BFTextFieldId FundName;
   extern CLASS_IMPORT const BFTextFieldId ElongName1;
   extern CLASS_IMPORT const BFTextFieldId FLongName;
   extern CLASS_IMPORT const BFDateFieldId AsofDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

AccountHoldingsInquiryProcess::AccountHoldingsInquiryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pMFAccountHoldingList( NULL )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MFACCOUNT_HOLDING_LIST,            true,  BF::NullContainerId,                             false, I_( "MFAccountHoldingList" ) );
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO,                     false, BF::NullContainerId,                             false, I_( "MFAccount" ) );
   addContainer( IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, true,  BF::NullContainerId,                             false, I_( "AccountHoldingsByCurrencyList" ) );
   addContainer( IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST,          true,  IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, false, I_( "FundClassHoldingsList" ) );
   addContainer( IFASTBP_PROC::ACCOUNT_DISTRIBUTION_LIST,         true,  BF::NullContainerId,                             false, I_( "AccountDistributionList" ) );

   addFieldDetails( ifds::InterCode,      IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::DateOfReg,      IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::EffectiveDate,  IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Slsrep,         IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::FirstEffective, IFASTBP_PROC::MFACCOUNT_CBO );   

   addFieldDetails( ifds::Currency,       IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::TotBookValue,   IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::TotMkTValue,    IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::TotTenPercFree, IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::TotPercentage,  IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AsofDate,       IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::AsAtDate,       IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::FundName,       IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST,          SUBCLASS_PROCESS );

   addFieldDetails( ifds::rxFundCode,     IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::rxClassCode,    IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::SettledUnits,   IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::UnsettledUnits, IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::FundNAV,        IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::SettledValue,   IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::UnsettledValue, IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::AdjustedCost,   IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::EligibleAmt,    IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::EligibleUnits,  IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::LeftAmt,        IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::LeftUnits,      IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::AmountType,     IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );   
   addFieldDetails( ifds::FundNumber,     IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::Percentage,     IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST,          SUBCLASS_PROCESS );

   addFieldDetails( ifds::FundCode,       IFASTBP_PROC::ACCOUNT_DISTRIBUTION_LIST );
   addFieldDetails( ifds::ClassCode,      IFASTBP_PROC::ACCOUNT_DISTRIBUTION_LIST );
   addFieldDetails( ifds::FundToCode,     IFASTBP_PROC::ACCOUNT_DISTRIBUTION_LIST );
   addFieldDetails( ifds::ClassToCode,    IFASTBP_PROC::ACCOUNT_DISTRIBUTION_LIST );

   addFieldDetails( ifds::Grp1Shares,     IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
   addFieldDetails( ifds::Grp2Shares,     IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
}

//******************************************************************************

AccountHoldingsInquiryProcess::~AccountHoldingsInquiryProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AccountHoldingsInquiryProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   DString _secondValue=NULL;

   try
   {
      getParameter( ACCTHOLDINGSLIT::ACCOUNT_NUMBER_FIELD, strAccountNumber );

      DString dstrTrack,dstrActivity;
      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");

      strAccountNumber.stripLeading().stripLeading( I_CHAR( '0' ) ).stripTrailing();
      if( strAccountNumber == I_("") )
      {
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_NO_DATA_AREA );
      }

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      sevRtn = dstcWorkSession->getMFAccount( getDataGroupId(), strAccountNumber, _pMFAccount,dstrTrack, 
                                              dstrActivity);
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount );
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

      FreeUnitList *_pFreeUnitList;
      sevRtn = _pMFAccount->getFreeUnitList( _pFreeUnitList, getDataGroupId() );
      if( WARNING >= sevRtn )
      {
         //setContainer( MFACCOUNT_HOLDING_LIST, _pMFAccountHoldingList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      ACBList *_pACBList;
      sevRtn = _pMFAccount->getACBList( _pACBList, getDataGroupId() );
      if( WARNING >= sevRtn )
      {
         //setContainer( MFACCOUNT_HOLDING_LIST, _pMFAccountHoldingList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      sevRtn = _pMFAccount->getAccountHoldingsByCurrencyList( _pAccountHoldingsByCurrencyList, getDataGroupId() );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, _pAccountHoldingsByCurrencyList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      sevRtn = _pMFAccount->getAccDistributionsList( _pAccDistributionsList, getDataGroupId() );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::ACCOUNT_DISTRIBUTION_LIST, _pAccDistributionsList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
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

E_COMMANDRETURN AccountHoldingsInquiryProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

void *AccountHoldingsInquiryProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   SEVERITY sevRtn1 = NO_CONDITION;

   try
   {
      if( IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST == idContainer )
      {
         {
            DString key = getCurrentListItemKey( this, IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST );
            if( key != NULL_STRING )
            {
               BFAbstractCBO *rpPtr = getCBOItem( IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, idDataGroup );
               AccountHoldingsByCurrency *pAccountHoldingsByCurrency = dynamic_cast < AccountHoldingsByCurrency* > ( rpPtr );
               pAccountHoldingsByCurrency->getFundClassHoldingsList( _pFundClassHoldingsList, idDataGroup );
               ptr = _pFundClassHoldingsList;
            }
         }
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

void AccountHoldingsInquiryProcess::doGetField(
                                              const GenericInterface *rpGICaller,
                                              const BFContainerId& idContainer,
                                              const BFFieldId& idField,
                                              const BFDataGroupId& idDataGroup,
                                              DString &strValueOut,
                                              bool bFormatted
                                              ) const
{  
   strValueOut = NULL_STRING;

   if( idField == ifds::Currency && idContainer == IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST )
   {
      AccountHoldingsInquiryProcess *rpNonConstThis = const_cast < AccountHoldingsInquiryProcess*> ( this );
      DString key = rpNonConstThis->getCurrentListItemKey( this, IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST );
      if( key != NULL_STRING )
      {
         BFAbstractCBO *rpPtr = rpNonConstThis->getCBOItem( IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, idDataGroup );
         AccountHoldingsByCurrency *pAccountHoldingsByCurrency = dynamic_cast < AccountHoldingsByCurrency* > ( rpPtr );
         pAccountHoldingsByCurrency->getCurrency( strValueOut );
      }
      else
         strValueOut = NULL_STRING;
   }

   if( ( idField == ifds::TotBookValue || idField == ifds::TotMkTValue || idField == ifds::TotTenPercFree || idField == ifds::TotPercentage ) && idContainer == IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST )
   {
      AccountHoldingsInquiryProcess *rpNonConstThis = const_cast < AccountHoldingsInquiryProcess*> ( this );
      DString key = rpNonConstThis->getCurrentListItemKey( this, IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST );
      if( key != NULL_STRING )
      {
         BFAbstractCBO *rpPtr = rpNonConstThis->getCBOItem( IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST, idDataGroup );
         AccountHoldingsByCurrency *pAccountHoldingsByCurrency = dynamic_cast < AccountHoldingsByCurrency* > ( rpPtr );
         if( idField == ifds::TotMkTValue )
            pAccountHoldingsByCurrency->getTotalMarketValue( strValueOut );
         else if( idField == ifds::TotBookValue )
            pAccountHoldingsByCurrency->getTotalBookValue( strValueOut );
         else if( idField == ifds::TotTenPercFree )
            pAccountHoldingsByCurrency->getTotalTenPercFree( strValueOut );
         else if( idField == ifds::TotPercentage )
            pAccountHoldingsByCurrency->getTotalPercentage( strValueOut );
      }
   }

   if( ( /*idField == DBR::Baycom ||*/ idField == ifds::Percentage || idField == ifds::FundName ) && idContainer == IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST )
   {
      AccountHoldingsInquiryProcess *rpNonConstThis = const_cast < AccountHoldingsInquiryProcess*> ( this );
      DString key = rpNonConstThis->getCurrentListItemKey( this, IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST );
      if( key != NULL_STRING )
      {
         BFAbstractCBO *rpPtr = rpNonConstThis->getCBOItem( IFASTBP_PROC::FUND_CLASS_HOLDINGS_LIST, idDataGroup );
         FundClassHolding *pFundClassHolding = dynamic_cast < FundClassHolding* > ( rpPtr );
         if( pFundClassHolding )
         {
            if( idField == ifds::Percentage )
            {
               pFundClassHolding->getPercOfTotal( strValueOut );
            }
            else if( idField == ifds::FundName )
            {
               DString strFundCode, strClassCode;
               pFundClassHolding->getField( ifds::rxFundCode, strFundCode, idDataGroup, false );
               pFundClassHolding->getField( ifds::rxClassCode, strClassCode, idDataGroup, false );
               DString dstLocaleStr = ClientLocaleContext::get().getLocale();

               FundMasterList *pFundMasterList;
               dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo().getFundMasterList( pFundMasterList );
               if( pFundMasterList )
                  if( dstLocaleStr != I_("frCA") )
                     pFundMasterList->getFundName( strFundCode, ifds::ElongName1, strValueOut);
                  else
                     pFundMasterList->getFundName( strFundCode, ifds::FLongName, strValueOut);
            }
         }
      }
   }
   if( idField == ifds::AsofDate && idContainer == IFASTBP_PROC::ACCOUNT_HOLDINGS_BY_CURRENCY_LIST )
   {
      DString AsofDate;
      if( dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::CurrBusDate, 
                                                                          AsofDate, 
                                                                          BF::HOST, 
                                                                          true ) <= WARNING )
      {
         strValueOut = AsofDate;
      }
   }
}


//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountHoldingsInquiryProcess.cpp-arc  $
// 
//    Rev 1.19   Nov 17 2004 15:18:44   popescu
// PET 1117/56, removed 'getField' method at the fund master list level, 
// 
//    Rev 1.18   Apr 02 2003 12:19:10   PURDYECH
// Code cleanup
// 
//    Rev 1.17   Mar 21 2003 17:34:20   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.16   Mar 07 2003 14:16:54   PURDYECH
// A couple of getFields had unintentionally incorrect parameter usage.
// 
//    Rev 1.15   Feb 11 2003 13:08:28   FENGYONG
// french fundname fix for fundcom
// 
//    Rev 1.14   Jan 02 2003 13:14:20   linmay
// Change BayCom to FundNumber
// 
//    Rev 1.13   Dec 12 2002 11:06:50   FENGYONG
// Add FirstEffective to mfaccountCBO, Add leftamt and amount type to fundholding
// 
//    Rev 1.12   Oct 09 2002 23:52:56   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.11   Aug 29 2002 16:42:30   SMITHDAV
// Condition split.
// 
//    Rev 1.10   Aug 29 2002 12:54:08   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.9   22 May 2002 18:23:46   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   27 Mar 2002 19:54:28   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.7   Mar 20 2002 10:46:20   FENGYONG
// Add Baycom
// 
//    Rev 1.6   Oct 30 2001 11:48:00   VASILEAD
// Added distribution information
// 
//    Rev 1.5   Jul 25 2001 14:07:18   YINGBAOL
// sync version 1.3.1.0
// 
//    Rev 1.4   03 May 2001 14:05:14   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.3   Mar 28 2001 14:46:32   VASILEAD
// Added unsettled values for the market value
// 
//    Rev 1.2   Mar 18 2001 18:18:02   VASILEAD
// Fixes for UAT release
// 
//    Rev 1.1   Mar 12 2001 12:58:38   VASILEAD
// Modified for FUNDcom release
 * 
//    Rev 1.1   Nov 25 1999 11:53:58   FENGYONG
// Changed with MFAccount 
 * 
 */


