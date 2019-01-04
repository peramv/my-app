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
// ^FILE   : AccountAllocationsProcess.cpp
// ^AUTHOR : 
// ^DATE   : 09/18/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AccountAllocationsProcess
//    This class manages the allocations information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\defacctalloclist.hpp>
#include <ifastcbo\defacctalloc.hpp>
#include <ifastcbo\deffundalloclist.hpp>
#include <ifastcbo\deffundalloc.hpp>
#include <ifastcbo\shralloctypelist.hpp>
#include <ifastcbo\shralloctype.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include "accountallocationsprocess.hpp"
#include "accountallocationsprocessincludes.h"
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\shareholder.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNTALLOCATIONS;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AccountAllocationsProcess > processCreator( CMD_BPROC_ACCOUNTALLOCATIONS );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME   = I_( "AccountAllocationsProcess" );
   const I_CHAR * const YES         = I_( "Y" );
   const I_CHAR * const NO          = I_( "N" );

}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long BP_ERR_INVALID_DATE_FORMAT;
   extern const long ERR_NO_VALID_SHAREHOLDER_OR_ACCOUNT;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId Name;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;

}

//******************************************************************************
//              Public Methods
//******************************************************************************

AccountAllocationsProcess::AccountAllocationsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pShrAllocationsList( 0 )
, _rpChildGI( 0 )
, _pAcctAllocationsList(0)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MFACCOUNT_CBO,         false );
   addContainer( IFASTBP_PROC::SHAREHOLDER_CBO,       false );

   addContainer( IFASTBP_PROC::SHR_ALLOCATIONS_LIST,  true, BF::NullContainerId, true, I_("ShareholderAllocation") );
   addContainer( IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, true, BF::NullContainerId, true, I_("AccountAllocation") );
   addContainer( IFASTBP_PROC::FUND_ALLOCATIONS_LIST, true, BF::NullContainerId, true, I_("FundAllocation") ); 

   addContainer( IFASTBP_PROC::MFACCOUNT_LIST,        true );

   addFieldDetails( ifds::TransType,        IFASTBP_PROC::SHR_ALLOCATIONS_LIST );
   addFieldDetails( ifds::EffectiveDate,    IFASTBP_PROC::SHR_ALLOCATIONS_LIST );
   //The following field should not be here, but is necessary due to 
   //the "flat" design of view 58
   addFieldDetails( ifds::Level,            IFASTBP_PROC::SHR_ALLOCATIONS_LIST );
   //The following field should not be here, but is required by the wrong 
   //design of the host
   addFieldDetails( ifds::AllocPercentage,  IFASTBP_PROC::SHR_ALLOCATIONS_LIST );

   addFieldDetails( ifds::AllocPercentage,  IFASTBP_PROC::ACCT_ALLOCATIONS_LIST );
   addFieldDetails( ifds::AccountNum,       IFASTBP_PROC::ACCT_ALLOCATIONS_LIST );
   //The following three fields should not be here, but are necessary due to 
   //the "flat" design of view 58
   addFieldDetails( ifds::Level,            IFASTBP_PROC::ACCT_ALLOCATIONS_LIST );
   addFieldDetails( ifds::TransType,        IFASTBP_PROC::ACCT_ALLOCATIONS_LIST );
   addFieldDetails( ifds::EffectiveDate,    IFASTBP_PROC::ACCT_ALLOCATIONS_LIST );

   addFieldDetails( ifds::ToFundNumber,     IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::FundCode,         IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::ClassCode,        IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::AllocPercentage,  IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   //The following four fields should not be here, but are necessary due to 
   //the "flat" design of view 58
   addFieldDetails( ifds::Level,            IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::TransType,        IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::EffectiveDate,    IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::AccountNum,       IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::SplitComm,        IFASTBP_PROC::FUND_ALLOCATIONS_LIST );

   //Account
   addFieldDetails( ifds::AccountNum,       IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::TaxType,          IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Currency,         IFASTBP_PROC::MFACCOUNT_CBO );

   //Shareholder
   addFieldDetails( ifds::ShrNum,           IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::GroupCode,        IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::Name1,            IFASTBP_PROC::SHAREHOLDER_CBO );

   addFieldDetails( ifds::AllocTaxType,     BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctTotalPercent, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundTotalPercent, BF::NullContainerId, SUBCLASS_PROCESS );

}

//******************************************************************************

AccountAllocationsProcess::~AccountAllocationsProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AccountAllocationsProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( ACCOUNTALLOCATIONSPROC::ACCOUNT_NUM, _dstrAccountNum );
      getParameter( ACCOUNTALLOCATIONSPROC::TRANSTYPE, _dstrTransType );
      getParameter( ACCOUNTALLOCATIONSPROC::EFFECTIVEDATE, _dstrEffectiveDate );

      _dstrAccountNum.stripAll();
      if( _dstrAccountNum == NULL_STRING )
         THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::ERR_NO_VALID_SHAREHOLDER_OR_ACCOUNT);

      if( _dstrTransType == NULL_STRING ) _dstrTransType = I_("RO");
      if( _dstrEffectiveDate !=NULL_STRING )
      {
         if( !BFDate::isValidDate( _dstrEffectiveDate, BFDate::DF_DISPLAY ) )  // is this date in valid display format (display format as defined in registry)
         {
            THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_INVALID_DATE_FORMAT );
         }

         DString tmp;
         DSTCommonFunctions::UnformatDate( _dstrEffectiveDate, tmp );
         _dstrEffectiveDate = tmp;
      }

      setContainers( getDataGroupId() );
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

SEVERITY AccountAllocationsProcess::setContainers(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "setContainers" ) );

   SEVERITY sevRtn = SEVERE_ERROR;

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( _dstrEffectiveDate == NULL_STRING )
   {
      dstcWorkSession->getMgmtCoOptions()->getField(ifds::CurrBusDate, _dstrEffectiveDate, getDataGroupId( ), false );
   }

   sevRtn = dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, _pMFAccount, I_("N"), NULL_STRING, true, true );
   if( sevRtn > WARNING )
      return(sevRtn);
   setContainer( IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount );

   _pMFAccount->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
   dstrShareholderNum.strip().stripLeading( I_CHAR( '0' ) );
   sevRtn = dstcWorkSession->getShareholder( idDataGroup, dstrShareholderNum, _pShareholder );
   if( sevRtn > WARNING )
      return(sevRtn);
   setContainer( IFASTBP_PROC::SHAREHOLDER_CBO, _pShareholder );

   sevRtn = _pShareholder->getAllocationList(_pShrAllocationsList, idDataGroup );
   setContainer( IFASTBP_PROC::FUND_ALLOCATIONS_LIST, NULL );
   setContainer( IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, NULL );
   setContainer( IFASTBP_PROC::SHR_ALLOCATIONS_LIST, NULL );
   sevRtn = filterContainer(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY AccountAllocationsProcess::filterContainer(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "setContainers" ) );

   SEVERITY sevRtn = SEVERE_ERROR;
   bool haveshareallc = false, haveaccountallc = false;

   assert( _pShrAllocationsList );
   ShrAllocType *pShrAllocation = NULL;
   DefAcctAlloc *pAcctAllocation = NULL;
   DefFundAlloc *pFundAllocation = NULL;
   DString transtype, effectivedate,accountnum;

   BFObjIter bfIter(*_pShrAllocationsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !bfIter.end() )
   {
      pShrAllocation= dynamic_cast < ShrAllocType* > ( bfIter.getObject() );
      assert( pShrAllocation );

      pShrAllocation->getField( ifds::EffectiveDate, effectivedate, idDataGroup, false);
      pShrAllocation->getField( ifds::TransType, transtype, idDataGroup, false );
	  pShrAllocation->getAccountAllocationList( _pAcctAllocationsList, idDataGroup );
      if( effectivedate == _dstrEffectiveDate && transtype == _dstrTransType )
      {
         haveshareallc = true;         
         BFObjIter bfIter1(*_pAcctAllocationsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
         while( !bfIter1.end() )
         {
            pAcctAllocation= dynamic_cast < DefAcctAlloc* > ( bfIter1.getObject() );
            pAcctAllocation->getField( ifds::AccountNum, accountnum, idDataGroup, true );
			pAcctAllocation->getFundAllocationList( _pFundAllocationsList, idDataGroup );
            if( accountnum.stripAll() == _dstrAccountNum )
            {
               haveaccountallc = true;               
               setContainer( IFASTBP_PROC::FUND_ALLOCATIONS_LIST, _pFundAllocationsList );
               break;
            }
			else
			{
				//_pFundAllocationsList->clearAllocations(idDataGroup);
				//bfIter1.deleteObject();
			}
            ++bfIter1;
         }
         break;
      }
	  else
	  {
		  //_pAcctAllocationsList->clearAllocations(idDataGroup);
		  //bfIter.deleteObject();
	  }
      ++bfIter;
   }  

   DString dstrKeyAlloc = _dstrTransType + _dstrAccountNum + _dstrEffectiveDate;
   if( haveshareallc == false )
   {
      if( _pShrAllocationsList->addNewAllocation(dstrKeyAlloc, idDataGroup, false)<=WARNING )
      {
         pShrAllocation = dynamic_cast<ShrAllocType*>(_pShrAllocationsList->getObject(dstrKeyAlloc, idDataGroup));
         assert(pShrAllocation);
         pShrAllocation->setField(ifds::EffectiveDate,_dstrEffectiveDate,idDataGroup, false);
         pShrAllocation->setField(ifds::TransType,_dstrTransType,idDataGroup, false);
         pShrAllocation->getAccountAllocationList(_pAcctAllocationsList, idDataGroup, true);
      }
      assert(_pAcctAllocationsList);
      dstrKeyAlloc = _dstrAccountNum;
      if( _pAcctAllocationsList->addNewAllocation(dstrKeyAlloc, idDataGroup, false, false, false)<=WARNING )
      {
         pAcctAllocation = dynamic_cast<DefAcctAlloc*>(_pAcctAllocationsList->getObject(dstrKeyAlloc, idDataGroup));
         assert(pAcctAllocation);
         pAcctAllocation->setField(ifds::EffectiveDate,_dstrEffectiveDate,idDataGroup, false);
         pAcctAllocation->setField(ifds::TransType,_dstrTransType,idDataGroup, false);
         pAcctAllocation->setField(ifds::AllocPercentage,I_("100"),idDataGroup, false);
         pAcctAllocation->setField(ifds::AccountNum,_dstrAccountNum,idDataGroup, false);
         pAcctAllocation->getFundAllocationList(_pFundAllocationsList, idDataGroup, true, false);
         assert(_pFundAllocationsList);
      }
   }

   setContainer( IFASTBP_PROC::FUND_ALLOCATIONS_LIST, _pFundAllocationsList );
   setContainer( IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, _pAcctAllocationsList );
   setContainer( IFASTBP_PROC::SHR_ALLOCATIONS_LIST, _pShrAllocationsList );

   DString temp = asString( ifds::TransType.getId() );
   DString dstrFilter;
   dstrFilter = temp + I_( "=" ) + _dstrTransType + I_(";");
   temp = asString( ifds::AccountNum.getId() );
   dstrFilter = dstrFilter + temp + I_( "=" ) + _dstrAccountNum + I_(";");
   setDataFilter( IFASTBP_PROC::SHR_ALLOCATIONS_LIST, dstrFilter);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN AccountAllocationsProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = CMD_MODELESS_INPROCESS;
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

void *AccountAllocationsProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
	  if( IFASTBP_PROC::FUND_ALLOCATIONS_LIST == idContainer )
      {
         {
            ptr = _pFundAllocationsList;                  
         }
      }
	  if( IFASTBP_PROC::ACCT_ALLOCATIONS_LIST == idContainer )
      {
         {
            ptr = _pAcctAllocationsList;                  
         }
      }
	  if( IFASTBP_PROC::SHR_ALLOCATIONS_LIST == idContainer )
      {
         {
            ptr = _pShrAllocationsList;                  
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
// If severity > warning, throw error ??
   return(ptr);
}

//******************************************************************************

bool AccountAllocationsProcess::doOk( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOOK );
/*
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   // 1. define a map, keyed by AccountNum; the value indicates the existence of
   //    default allocations for the key AccountNum
   std::map< DString, DString > mapAcctAlloc;

   // 2. fill in the map, setting all values to NO for now
   //Initialize the Map
   const DString *pAcctKey = &(getFirstListItemKey( rpGICaller, IFASTBP_PROC::MFACCOUNT_LIST));
   while( *pAcctKey != NULL_STRING )
   {
      DString dstrAccountNum;
      getField(rpGICaller, IFASTBP_PROC::MFACCOUNT_LIST, ifds::AccountNum, dstrAccountNum, false );
      dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
      mapAcctAlloc[ dstrAccountNum ] = NO;

      pAcctKey = &(getNextListItemKey(rpGICaller, IFASTBP_PROC::MFACCOUNT_LIST));
   }

   // 3. memorize the current iter positions in the default allocation lists, 
   //    to restore them  later
   const DString& dstrCurrShrAllocKey = getCurrentListItemKey( rpGICaller, IFASTBP_PROC::SHR_ALLOCATIONS_LIST );
   const DString& dstrCurrAcctAllocKey = getCurrentListItemKey( rpGICaller, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST );

   // 4. iterate through the acct level default allocations and set the value
   //    in the map to YES for every met AccountNum.
   const DString *pShrLevelKey = &(getFirstListItemKey(rpGICaller, IFASTBP_PROC::SHR_ALLOCATIONS_LIST));
   while( *pShrLevelKey != NULL_STRING )
   {
      const DString *pAcctLevelKey = &(getFirstListItemKey(rpGICaller, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST));
      while( *pAcctLevelKey != NULL_STRING )
      {
         DString dstrCurrAccountNum;
         getField( rpGICaller, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::AccountNum, dstrCurrAccountNum, false );
         dstrCurrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
         if( dstrCurrAccountNum != NULL_STRING )
            mapAcctAlloc[ dstrCurrAccountNum ] = YES;

         pAcctLevelKey = &(getNextListItemKey(rpGICaller, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST));
      }
      pShrLevelKey = &(getNextListItemKey(rpGICaller, IFASTBP_PROC::SHR_ALLOCATIONS_LIST));
   }

   // 5. restore the initial iter positions in the lists
   setCurrentListItem( rpGICaller, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, dstrCurrShrAllocKey );
   setCurrentListItem( rpGICaller, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, dstrCurrAcctAllocKey );

   // 6. set AcctAlloc field in the accounts, according to the value in the map
   std::map< DString, DString >::iterator iter = mapAcctAlloc.begin();  
   while( iter != mapAcctAlloc.end() )
   {
      MFAccount *pMFAccount;
      dstcWorkSession->getMFAccount(getDataGroupId(), (*iter).first, pMFAccount);
      if( pMFAccount )
         pMFAccount->setField( ifds::AcctAlloc, (*iter).second, getDataGroupId(), false );

      ++iter;
   }
*/   return(true);
}

//******************************************************************************

SEVERITY AccountAllocationsProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOVALIDATEALL );

   _pShrAllocationsList->validateAll( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AccountAllocationsProcess::deleteItemFromList(const GenericInterface *rpGICaller, const BFContainerId& idList) 
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("deleteItemFromList") );

    AbstractProcess::deleteItemFromList(rpGICaller, idList);
    return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
//              Private Methods
//******************************************************************************


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountAllocationsProcess.cpp-arc  $
// 
//    Rev 1.21   Apr 14 2004 10:33:26   FENGYONG
// PTS 10028971 API allocation specific type deleting
// 
//    Rev 1.19   Sep 12 2003 13:55:24   FENGYONG
// fix for API frank russel
// 
//    Rev 1.18   Apr 02 2003 12:19:04   PURDYECH
// Code cleanup
// 
//    Rev 1.17   Mar 21 2003 17:33:58   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.16   Dec 12 2002 13:48:14   FENGYONG
// change MFCANBP to BPBASE
// 
//    Rev 1.15   Dec 12 2002 11:45:14   FENGYONG
// Accountnumber and date validation,
// 
//    Rev 1.14   Oct 09 2002 23:52:56   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.13   Sep 04 2002 15:45:48   PURDYECH
// Condition, comment and formatting cleanup
// 
//    Rev 1.12   Aug 29 2002 16:42:30   SMITHDAV
// Condition split.
// 
//    Rev 1.11   Aug 29 2002 12:54:08   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.10   Jul 31 2002 16:02:00   FENGYONG
// percentage changed to allocpercentage.
// 
//    Rev 1.9   Jul 31 2002 15:16:24   KOVACSRO
// allocation fixes.
// 
//    Rev 1.8   Jun 03 2002 16:55:14   HSUCHIN
// bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
// 
//    Rev 1.7   22 May 2002 18:23:44   PURDYECH
// BFData Implementation
// 
//    Rev 1.6   22 Apr 2002 10:07:50   KOVACSRO
// Rel.47 : new design for Allocations.
// 
//    Rev 1.5   27 Mar 2002 19:54:26   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.4   21 Mar 2002 15:40:38   SMITHDAV
// Trim accountNum parameter.
// 
//    Rev 1.3   Feb 07 2002 16:51:18   FENGYONG
// Add dateformat checking
// 
//    Rev 1.2   Jan 17 2002 14:56:28   FENGYONG
// change CBO reference name
// 
//    Rev 1.1   Jan 08 2002 15:23:00   FENGYONG
// remove delete old fundallocation records
// 
//    Rev 1.0   Dec 20 2001 18:19:10   FENGYONG
// Initial revision.
 *
 */
