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
// ^FILE   : HypoRedProcess.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/29/2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : HypoRedProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "hyporedprocess.hpp"
#include "hyporedprocessincludes.h"

#include <ifastcbo\hyporedacctholdingslist.hpp>
#include <ifastcbo\hyporedcriteria.hpp>
#include <ifastcbo\hyporeddetaillist.hpp>
#include <ifastcbo\hyporedsummary.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\funddetail.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\mgmtco.hpp>


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_HYPO_RED;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACC_DETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HYPO_RED;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< HypoRedProcess > processCreator( CMD_BPROC_HYPO_RED );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "HypoRedProcess" );


   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
   const I_CHAR * const YES_STRING     = I_( "Yes" );
   const I_CHAR * const NO_STRING      = I_( "No" );
   const double dSmallValue            = .0000000001;

}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId FeePercent;
   extern CLASS_IMPORT const BFDecimalFieldId TotCBAmount; 
   extern CLASS_IMPORT const BFTextFieldId	  LoadType;
   
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319HypoRedProcess::HypoRedProcess() : 
HypoRedProcess::HypoRedProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL ),
_strAccountNum(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   //add containers
   addContainer( IFASTBP_PROC::MFACCOUNT,     false, BF::NullContainerId,                      false, I_("MFAccount") );
   addContainer( IFASTBP_PROC::CRITERIA,      false, IFASTBP_PROC::MFACCOUNT,    true,  I_("HypoRedCriteria") );
   addContainer( IFASTBP_PROC::HOLDINGS_LIST, true,  IFASTBP_PROC::CRITERIA,     true,  I_("HypoRedAcctHoldings") );
   addContainer( IFASTBP_PROC::SUMMARY_LIST,  true,  IFASTBP_PROC::CRITERIA,     false, I_("HypoRedSummaryList") );
   addContainer( IFASTBP_PROC::DETAILS_LIST,  true,  IFASTBP_PROC::SUMMARY_LIST, false, I_("HypoRedDetailsList") );
   addContainer( IFASTBP_PROC::TOTAL_LIST,    true,  IFASTBP_PROC::SUMMARY_LIST, false, I_("HypoRedTotalList") );
   addContainer( IFASTBP_PROC::ERRORS_LIST,   true,  IFASTBP_PROC::CRITERIA,     false, I_("HypoRedErrorList") );

   //set data filters for SUMMARY_LIST : filter out those records which have an error on it
   DString strErrDescrField = asString( ifds::ErrorDesc.getId() );
   DString dstrFilter = strErrDescrField;
   dstrFilter += I_( "=" );
   dstrFilter += NULL_STRING;
   setDataFilter( IFASTBP_PROC::SUMMARY_LIST, dstrFilter);
   //set data filters for ERRORS_LIST : filter out those records which have NO error on it
   dstrFilter = strErrDescrField;
   dstrFilter += I_( "!=" );
   dstrFilter += NULL_STRING;
   setDataFilter( IFASTBP_PROC::ERRORS_LIST, dstrFilter);
   //set data filters for HOLDINGS_LIST : filter those records which have zero settled units
   dstrFilter = asString( ifds::SettledUnits.getId() );;
   dstrFilter += I_( "!=" );
   dstrFilter += I_("0");
   setDataFilter( IFASTBP_PROC::HOLDINGS_LIST, dstrFilter);

   //MFACCOUNT fields
   addFieldDetails( ifds::ShrNum,              IFASTBP_PROC::MFACCOUNT );
   addFieldDetails( ifds::AccountNum,          IFASTBP_PROC::MFACCOUNT );

   //CRITERIA fields
   addFieldDetails( ifds::TradeDate,           IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FullRed,             IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::RedCode,             IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::GrossOrNet,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::AmtType,             IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::AcctLvlDSC,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::isLSIF,              IFASTBP_PROC::CRITERIA ); 

   //HOLDINGS_LIST fields
   addFieldDetails( ifds::rxFundCode,          IFASTBP_PROC::HOLDINGS_LIST );
   addFieldDetails( ifds::rxClassCode,         IFASTBP_PROC::HOLDINGS_LIST );
	addFieldDetails( ifds::FundNumber,          IFASTBP_PROC::HOLDINGS_LIST );	
   addFieldDetails( ifds::FundName,            IFASTBP_PROC::HOLDINGS_LIST );
   addFieldDetails( ifds::FundCurrency,        IFASTBP_PROC::HOLDINGS_LIST );
   addFieldDetails( ifds::SettledUnits,        IFASTBP_PROC::HOLDINGS_LIST );
   addFieldDetails( ifds::SettledValue,        IFASTBP_PROC::HOLDINGS_LIST );
   addFieldDetails( ifds::Amount,              IFASTBP_PROC::HOLDINGS_LIST );

   //SUMMARY_LIST fields
   addFieldDetails( ifds::FundCode,            IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::ClassCode,           IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::Baycom,              IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::FundCurrency,        IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::Amount,              IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::Units,               IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::FreeAmount,          IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::FreeUnits,           IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::ApplicableAmt,       IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::ApplicableUnits,     IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::DSC,                 IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::Fee,                 IFASTBP_PROC::SUMMARY_LIST );   
   addFieldDetails( ifds::FedTax,              IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::ProvTax,             IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::ErrorDesc,           IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::ErrorCode,           IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::FedClawback,             IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::ProvClawback,            IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::AdditionalProvClawback,  IFASTBP_PROC::SUMMARY_LIST );
   addFieldDetails( ifds::TotCBAmount,		   IFASTBP_PROC::SUMMARY_LIST );

   //DETAILS_LIST fields
   addFieldDetails( ifds::FundCode,            IFASTBP_PROC::DETAILS_LIST );
   addFieldDetails( ifds::ClassCode,           IFASTBP_PROC::DETAILS_LIST );
   addFieldDetails( ifds::Baycom,              IFASTBP_PROC::DETAILS_LIST );
   addFieldDetails( ifds::FundCurrency,        IFASTBP_PROC::DETAILS_LIST );
   addFieldDetails( ifds::Amount,              IFASTBP_PROC::DETAILS_LIST );
   addFieldDetails( ifds::Units,               IFASTBP_PROC::DETAILS_LIST );
   addFieldDetails( ifds::FeePercent,          IFASTBP_PROC::DETAILS_LIST );
   addFieldDetails( ifds::DSC,                 IFASTBP_PROC::DETAILS_LIST );
   addFieldDetails( ifds::FedClawback,             IFASTBP_PROC::DETAILS_LIST );
   addFieldDetails( ifds::ProvClawback,            IFASTBP_PROC::DETAILS_LIST );
   addFieldDetails( ifds::AdditionalProvClawback,  IFASTBP_PROC::DETAILS_LIST );
   addFieldDetails( ifds::TotCBAmount,		   IFASTBP_PROC::DETAILS_LIST );


   //TOTAL_LIST fields
   addFieldDetails( ifds::Currency,            IFASTBP_PROC::TOTAL_LIST );
   addFieldDetails( ifds::GrossAmt,            IFASTBP_PROC::TOTAL_LIST );
   addFieldDetails( ifds::DSC,                 IFASTBP_PROC::TOTAL_LIST );
   addFieldDetails( ifds::Fee,                 IFASTBP_PROC::TOTAL_LIST );   
   addFieldDetails( ifds::FedTax,              IFASTBP_PROC::TOTAL_LIST );
   addFieldDetails( ifds::ProvTax,             IFASTBP_PROC::TOTAL_LIST );  
   addFieldDetails( ifds::NetAmt,              IFASTBP_PROC::TOTAL_LIST );
   addFieldDetails( ifds::FedClawback,             IFASTBP_PROC::TOTAL_LIST );
   addFieldDetails( ifds::ProvClawback,            IFASTBP_PROC::TOTAL_LIST );
   addFieldDetails( ifds::AdditionalProvClawback,  IFASTBP_PROC::TOTAL_LIST );
   addFieldDetails( ifds::TotCBAmount,		   IFASTBP_PROC::TOTAL_LIST );

   //ERRORS_LIST fields
   addFieldDetails( ifds::FundCode,            IFASTBP_PROC::ERRORS_LIST );
   addFieldDetails( ifds::ClassCode,           IFASTBP_PROC::ERRORS_LIST );
   addFieldDetails( ifds::ErrorCode,           IFASTBP_PROC::ERRORS_LIST );
   addFieldDetails( ifds::ErrorDesc,           IFASTBP_PROC::ERRORS_LIST );

   //dummy fields
   addFieldDetails( ifds::ValidHypoRed,        BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::ValidHypoCriteria,   BF::NullContainerId, SUBCLASS_PROCESS);

}

//******************************************************************************

HypoRedProcess::~HypoRedProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY HypoRedProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      getParameter( HYPO_RED::ACCOUNT_NUMBER, _strAccountNum );
      if( _strAccountNum.strip().stripLeading( '0' ).empty() )
      {
         assert(0);
         return(SEVERE_ERROR);
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      //assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN HypoRedProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   setParameter( HYPO_RED::ACCOUNT_NUMBER, _strAccountNum );
   try
   {

      rtn = invokeCommand( this, CMD_GUI_HYPO_RED, getProcessType(),
                           isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      //assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      //assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************

void *HypoRedProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;

   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case HYPO_RED::MFACCOUNT:
      if( IFASTBP_PROC::MFACCOUNT == idContainer )
      {
         {
            MFAccount *pMFAccount;
            DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            if( dstcWorkSession->getMFAccount(idDataGroup, _strAccountNum, pMFAccount ) <= WARNING )
               ptr = pMFAccount;
         }
//CP20030319            break;

//CP20030319			case HYPO_RED::CRITERIA:
      }
      else if( IFASTBP_PROC::CRITERIA == idContainer )
      {
         {
            MFAccount *pMFAccount = dynamic_cast<MFAccount *>
                                    (getCBOItem(IFASTBP_PROC::MFACCOUNT, idDataGroup));

            if( pMFAccount )
            {
               HypoRedCriteria* pHypoRedCriteria = NULL;
               if( pMFAccount->getHypoRedCriteria(pHypoRedCriteria, idDataGroup)<=WARNING )
                  ptr = pHypoRedCriteria;
            }
         }
//CP20030319            break;

//CP20030319			case HYPO_RED::HOLDINGS_LIST:
      }
      else if( IFASTBP_PROC::HOLDINGS_LIST == idContainer )
      {
         {
            HypoRedAcctHoldingsList* pHypoRedAcctHoldingsList = NULL;
            HypoRedCriteria* pHypoRedCriteria = dynamic_cast<HypoRedCriteria*>
                                                (getCBOItem(IFASTBP_PROC::CRITERIA, idDataGroup));
            if( pHypoRedCriteria->getHypoRedAcctHoldingsList(pHypoRedAcctHoldingsList, idDataGroup)<=WARNING )
               ptr = pHypoRedAcctHoldingsList;

         }
//CP20030319            break;

//CP20030319			case HYPO_RED::SUMMARY_LIST:
//CP20030319			case HYPO_RED::ERRORS_LIST://same as summary list
      }
      else if( IFASTBP_PROC::SUMMARY_LIST == idContainer
               || IFASTBP_PROC::ERRORS_LIST == idContainer )
      {
         {
            HypoRedSummaryList* pHypoRedSummaryList = NULL;
            HypoRedCriteria* pHypoRedCriteria = dynamic_cast<HypoRedCriteria*>
                                                (getCBOItem(IFASTBP_PROC::CRITERIA, idDataGroup));
            if( pHypoRedCriteria->getHypoRedSummaryList(pHypoRedSummaryList, idDataGroup)<=WARNING )
               ptr = pHypoRedSummaryList;

         }
//CP20030319            break;

//CP20030319			case HYPO_RED::DETAILS_LIST:
      }
      else if( IFASTBP_PROC::DETAILS_LIST == idContainer )
      {
         {
            HypoRedDetailList* pHypoRedDetailList = NULL;
            if( getNumberOfItemsInList(this, IFASTBP_PROC::SUMMARY_LIST) )
            {
               HypoRedSummary* pHypoRedSummary = dynamic_cast<HypoRedSummary*>
                                                 (getCBOItem(IFASTBP_PROC::SUMMARY_LIST, idDataGroup));
               if( pHypoRedSummary->getHypoRedDetailList(pHypoRedDetailList, idDataGroup)<=WARNING )
                  ptr = pHypoRedDetailList;
            }
         }
//CP20030319            break;

//CP20030319			case HYPO_RED::TOTAL_LIST:
      }
      else if( IFASTBP_PROC::TOTAL_LIST == idContainer )
      {
         {
            HypoRedCurrencyList *pHypoRedCurrencyList = NULL;
            HypoRedCriteria* pHypoRedCriteria = dynamic_cast<HypoRedCriteria*>
                                                (getCBOItem(IFASTBP_PROC::CRITERIA, idDataGroup));
            if( pHypoRedCriteria->getCurrencyList(pHypoRedCurrencyList, idDataGroup)<=WARNING )
               ptr = pHypoRedCurrencyList;
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

bool HypoRedProcess::doModelessChildComplete( const Command &cmd )
{
// End when GUI ends   
   return( cmd.getKey() == CMD_GUI_HYPO_RED );
}
//******************************************************************************

bool HypoRedProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  
   bool bRtn = true;
   DString strAccNum;
   bool bRefresh = false;
   getParameter( HYPO_RED::ACCOUNT_NUMBER, strAccNum );
   strAccNum.strip().stripLeading( '0' );

   if( rpGICaller->getCommand().getKey() == CMD_BPROC_ACC_DETAILS && strAccNum != _strAccountNum )
   {  //reset the containers
      _strAccountNum = strAccNum;
      setContainer( IFASTBP_PROC::MFACCOUNT, NULL );
      bRefresh = true;
   }
   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      if( bRefresh )
         bRtn = _rpChildGI->refresh( this, HYPO_RED::TXT_ACCT_NUM_CHANGED );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}
//******************************************************************************
SEVERITY HypoRedProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll") );
   //nothing to do
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY HypoRedProcess::ok2( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("ok2") );
   //there is nothing to be committed to the host; reset the whole thing here
   reset(rpGICaller, IFASTBP_PROC::CRITERIA);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void HypoRedProcess::doGetField(
                               const GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId& fieldID,
                               const BFDataGroupId& idDataGroup,
                               DString &strValueOut,
                               bool bFormatted
                               ) const
{
   if( fieldID == ifds::ValidHypoRed )
   {
      strValueOut = NO;
      if( !_strAccountNum.empty() )
      {
         MFAccount *pAcct;
         if( dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount(
                                                                              idDataGroup, _strAccountNum, pAcct, I_("N"), NULL_STRING, false) <= WARNING
             && pAcct )//don't create
         {
            HypoRedCriteria *pHypoRedCriteria = NULL;
            if( pAcct->getHypoRedCriteria(pHypoRedCriteria, idDataGroup)<=WARNING && pHypoRedCriteria )
            {
               HypoRedAcctHoldingsList* pHypoRedAcctHoldingsList = NULL;
               if( pHypoRedCriteria->getHypoRedAcctHoldingsList(
                                                               pHypoRedAcctHoldingsList, idDataGroup, false ) <= WARNING && pHypoRedAcctHoldingsList )
               {
                  if( pHypoRedAcctHoldingsList->isValidForInquiry(idDataGroup) )
                     strValueOut = YES;
               }
            }
         }
      }
   }
   else if( fieldID == ifds::ValidHypoCriteria )
   {
      strValueOut = NO;
      if( !_strAccountNum.empty() )
      {
         MFAccount *pAcct;
         if( dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount(
                                                                              idDataGroup, _strAccountNum, pAcct, I_("N"), NULL_STRING, false) <= WARNING
             && pAcct )//don't create
         {
            HypoRedCriteria *pHypoRedCriteria = NULL;
            if( pAcct->getHypoRedCriteria(pHypoRedCriteria, idDataGroup)<=WARNING && pHypoRedCriteria )
            {
               if( pHypoRedCriteria->isValidForInquiry(idDataGroup) )
                  strValueOut = YES;
            }
         }
      }
   }
   else
      assert(0);

   if( bFormatted )
   {
      if( strValueOut == YES )
         strValueOut = YES_STRING;
      else if( strValueOut == NO )
         strValueOut = NO_STRING;
   }
}

//******************************************************************************
SEVERITY HypoRedProcess::doSetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& fieldID,
                                   const BFDataGroupId& idDataGroup,
                                   const DString& strValue,
                                   bool bFormatted
                                   )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );
   assert(0);
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
bool HypoRedProcess::hasChargeBackFund()
{
	const BFDataGroupId& idDataGroup = getDataGroupId();
	HypoRedAcctHoldingsList* pHypoRedAcctHoldingsList = NULL;
	HypoRedCriteria* pHypoRedCriteria = dynamic_cast<HypoRedCriteria*>(getCBOItem(IFASTBP_PROC::CRITERIA, idDataGroup));

	bool bChargeBackFundSelected = false;
	if (pHypoRedCriteria->getHypoRedAcctHoldingsList(pHypoRedAcctHoldingsList, idDataGroup) <= WARNING && pHypoRedAcctHoldingsList)
	{
		BFObjIter iter(*pHypoRedAcctHoldingsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		while ( !iter.end() ) 
		{
			DString dstrAmount, dstrFundCode, dstrClassCode;
			BFAbstractCBO *pHolding = iter.getObject();
			pHolding->getField(ifds::Amount, dstrAmount, idDataGroup, false);
			double dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);
			if( dAmount > dSmallValue )//greater than zero
			{
				pHolding->getField(ifds::rxFundCode, dstrFundCode, idDataGroup, false);
				pHolding->getField(ifds::rxClassCode, dstrClassCode, idDataGroup, false);

				FundDetail *pFundDetail = NULL;
				FundDetailList *pFundDetailList = NULL;
				DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
				dstcWorkSession->getMgmtCo().getFundDetailList( pFundDetailList );
				assert(pFundDetailList);
				if (pFundDetailList->getFundDetail( dstrFundCode.strip().upperCase(), dstrClassCode.strip().upperCase(), idDataGroup, pFundDetail ) )
				{
					DString loadType;
					pFundDetail->getField( ifds::LoadType, loadType, idDataGroup );
					bChargeBackFundSelected = (loadType.upperCase().strip() == I_("CB"));
					if (bChargeBackFundSelected)
						break;
				}
			}
			++iter;
		}
	}

	return (bChargeBackFundSelected);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HypoRedProcess.cpp-arc  $
// 
//    Rev 1.7   Jun 14 2007 10:55:00   porteanm
// PET 2363 - Cleanup
// 
//    Rev 1.6   Jun 14 2007 10:49:12   porteanm
// PET 2363 FN?? - GAP 5  - for BKK.
// 
//    Rev 1.5   May 10 2004 13:42:42   AGUILAAM
// PET985_FN01-1: LSIF HypoCalc enhancement - added clawback fields
// 
//    Rev 1.4   Apr 04 2003 16:38:30   VADEANUM
// Fix.
// 
//    Rev 1.3   Apr 04 2003 16:02:34   VADEANUM
// Merged with 1.1.1.0 - Fixed Fund Num in Holdings List.
// 
//    Rev 1.2   Mar 21 2003 17:41:28   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Nov 22 2002 16:54:56   KOVACSRO
// Added implementation.
// 
//    Rev 1.0   Oct 29 2002 10:53:52   KOVACSRO
// Initial Revision
// 

  */