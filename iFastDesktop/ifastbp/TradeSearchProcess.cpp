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
// ^FILE   : TradeSearchProcess.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 02/21/2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TradeSearchProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\tradesearchcriteria.hpp>
#include "tradesearchprocess.hpp"
#include "tradesearchprocessincludes.h"
#include <ifastcbo\transactionlist.hpp>

//#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\dstcworksession.hpp>



extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRADE_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRADE_SEARCH;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TradeSearchProcess > processCreator( CMD_BPROC_TRADE_SEARCH );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME             = I_( "TradeSearchProcess" );
   const I_CHAR * const PERFORMSEARCH  = I_( "performSearch" );   


   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
   const I_CHAR * const YES_STRING     = I_( "Yes" );
   const I_CHAR * const NO_STRING      = I_( "No" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId FeePercent;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundISIN; 
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundName; 
   extern CLASS_IMPORT const BFTextFieldId BulkCancelAllowed;
   extern CLASS_IMPORT const BFTextFieldId TradesSearchTransType;
   extern CLASS_IMPORT const BFTextFieldId CUSIP;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319TradeSearchProcess::TradeSearchProcess() : 
TradeSearchProcess::TradeSearchProcess (GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess( pGIC, pGIParent, rCommand)
, _rpChildGI( NULL ),
_pPendingList(NULL),
_pTransactionList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   //add containers
   addContainer( IFASTBP_PROC::CRITERIA, 
      false, BF::NullContainerId, true, I_("Criteria") );
   addContainer( IFASTBP_PROC::PENDING_LIST, 
      true, IFASTBP_PROC::CRITERIA, false, I_("PendingList") );
   addContainer( IFASTBP_PROC::TRANSACTION_LIST, 
      true,  IFASTBP_PROC::CRITERIA, false, I_("TransactionList") );

   //CRITERIA fields
   addFieldDetails( ifds::Pending,             IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SearchType,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::TransNum,            IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::WireOrdNum,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::NetworkID,           IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ExtTransNum,         IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SendRefNum,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::PartRefNum,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::MasterRefNum,        IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FromDate,            IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ToDate,              IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::AccountNum,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ExternalIdType,      IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ExternalId,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::AltAccount,          IFASTBP_PROC::CRITERIA );

   addFieldDetails( ifds::TradeDate,           IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FundCode,            IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ClassCode,		   IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FundNumber,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FundName,            IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FundWKN,             IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FundISIN,            IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::BulkCancelAllowed,   IFASTBP_PROC::CRITERIA );  
   addFieldDetails( ifds::NSCCControlNumber,   IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::TradesSearchTransType, IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::TDCC,					IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::Valoren,				IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::CUSIP,				IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SearchUserID,		    IFASTBP_PROC::CRITERIA );

   //PENDING_LIST fields
   addFieldDetails( ifds::rxAcctNum,           IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::rxFundCode,          IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::rxClassCode,         IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TradeDate,           IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransType,           IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransNum,            IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Amount,              IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AmountType,          IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::MsgExists,           IFASTBP_PROC::PENDING_LIST );

   //TRANSACTION_LIST fields
   addFieldDetails( ifds::AccountNum,          IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::rxFundCode,          IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::rxClassCode,         IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::TradeDate,           IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::TransType,           IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::TransNum,            IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::Units,               IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::GrossAmt,            IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::TransId,             IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::MsgExists,           IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::Cancelled,           IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::TradesSearchTransType, IFASTBP_PROC::TRANSACTION_LIST );


   //dummy fields
   //addFieldDetails( ifds::ValidTradeSearch,        BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::ValidTradeCriteria,   BF::NullContainerId, SUBCLASS_PROCESS);

}

//******************************************************************************

TradeSearchProcess::~TradeSearchProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY TradeSearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN TradeSearchProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   try
   {
      rtn = invokeCommand( this, CMD_GUI_TRADE_SEARCH, getProcessType(),
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
void *TradeSearchProcess::getPtrForContainer (const BFContainerId& idContainer, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;
   DSTCWorkSession* dstcWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::CRITERIA == idContainer)
      {
         TradeSearchCriteria* pTradeSearchCriteria = NULL;

         if (dstcWorkSession->getTradeSearchCriteria (pTradeSearchCriteria) <= WARNING)
         {
            ptr = pTradeSearchCriteria;
         }
      }
      else if( IFASTBP_PROC::PENDING_LIST == idContainer )
      {
         TradeSearchCriteria* pTradeSearchCriteria = dynamic_cast<TradeSearchCriteria*>(
            getCBOItem (IFASTBP_PROC::CRITERIA, idDataGroup));

         _pPendingList = NULL;
         if (pTradeSearchCriteria->getPendingList (_pPendingList, idDataGroup) <= WARNING)
         {
            ptr = _pPendingList;
         }
      }
      else if( IFASTBP_PROC::TRANSACTION_LIST == idContainer )
      {
         TradeSearchCriteria* pTradeSearchCriteria = dynamic_cast<TradeSearchCriteria*>(
            getCBOItem (IFASTBP_PROC::CRITERIA, idDataGroup));

         _pTransactionList = NULL;
         if (pTradeSearchCriteria->getTransactionList (_pTransactionList, idDataGroup) <= WARNING)
         {
            ptr = _pTransactionList;
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
//******************************************************************************

SEVERITY TradeSearchProcess::ok2( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("ok2") );
   //there is nothing to be committed to the host; reset the whole thing here
   reset(rpGICaller, IFASTBP_PROC::CRITERIA);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void TradeSearchProcess::doGetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& fieldID,
                                   const BFDataGroupId& idDataGroup,
                                   DString &strValueOut,
                                   bool bFormatted
                                   ) const
{
   if( fieldID == ifds::ValidTradeCriteria )
   {
      strValueOut = NO;
      TradeSearchCriteria* pSearchCrt = NULL;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( dstcWorkSession->getTradeSearchCriteria(pSearchCrt)<=WARNING )
         if( pSearchCrt->isValidForInquiry(idDataGroup) )
            strValueOut = YES;
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
SEVERITY TradeSearchProcess::doSetField(
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

SEVERITY TradeSearchProcess::performSearch (
   GenericInterface *rpGICaller, 
   const BFContainerId& idSearch, 
   E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );

   const BFDataGroupId& idDataGroup = getDataGroupId ();
   try
   {
      switch (eSearchAction)
      {
         case SEARCH_START:
            {
               if (idSearch == IFASTBP_PROC::PENDING_LIST)
                  _pPendingList = NULL;
               else if (idSearch == IFASTBP_PROC::TRANSACTION_LIST)
                  _pTransactionList = NULL;
               setContainer (idSearch, NULL);
            }
            break;
         case SEARCH_NEXT_BLOCK:
            {
               if (idSearch == IFASTBP_PROC::PENDING_LIST)
               {
                  if (_pPendingList)
                     _pPendingList->getMore ();
               }
               else if (idSearch == IFASTBP_PROC::TRANSACTION_LIST)
               {
                  if (_pTransactionList)
                     _pTransactionList->getMore();
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
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool TradeSearchProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                             const BFContainerId& idSearch )
{
   if (!rpGICaller)
      return(false);

   if (IFASTBP_PROC::PENDING_LIST == idSearch)
   {
      return _pPendingList == NULL ? false : _pPendingList->doMoreRecordsExist();
   }
   else if (IFASTBP_PROC::TRANSACTION_LIST == idSearch)
   {
      return _pTransactionList == NULL ? false : _pTransactionList->doMoreRecordsExist();
   }
   return false;
}

//******************************************************************************
bool TradeSearchProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_TRADE_SEARCH );
}

//******************************************************************************
bool TradeSearchProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false; 
   
   if( isValidModelessInterface( _rpChildGI ) )
   {  // Only if child still exists
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }

   return(bRtn);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradeSearchProcess.cpp-arc  $
// 
//    Rev 1.14   Jan 16 2012 14:44:24   wp040027
// P0188394_Performance Fees - Trade Search
// 
//    Rev 1.13   Mar 02 2006 16:26:24   jankovii
// PET 2072 FN01- NSCC Control Number.
// 
//    Rev 1.12   Dec 19 2005 12:49:14   porteanm
// Incident 492760 - Added new column "Cancelled" to the Trade Search results for processed transactions.
// 
//    Rev 1.11   Nov 10 2005 15:20:04   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.10   Nov 10 2005 13:23:16   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.9   Nov 04 2005 10:43:48   ZHANGCEL
// PET 1286  FN01 -- Add Fields Detail for TradeDate related search
// 
//    Rev 1.8   May 27 2005 17:30:30   ZHANGCEL
// Fix the crash when search using is AltAccountNum
// 
//    Rev 1.7   Feb 22 2005 14:49:36   hernando
// PET1117 FN66-68 - Added Field Details for MsgExists.
// 
//    Rev 1.6   Sep 07 2004 15:39:54   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.5   May 11 2004 11:01:00   ZHANGCEL
// PET1046_FN02 -- Trade Search by account enhancement
// 
//    Rev 1.4   Apr 26 2004 13:09:26   popescu
// PET 1046, FN02, Trade search by account, code clean-up, removed old comments
// 
//    Rev 1.3   Apr 08 2003 15:43:26   HERNANDO
// PTS 10015695 - Defined if blocks to fix More functionality.
// 
//    Rev 1.2   Mar 21 2003 17:49:08   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Mar 04 2003 17:07:06   KOVACSRO
// Amount changed into GrossAmt for transactions
// 
//    Rev 1.0   Mar 03 2003 09:52:16   KOVACSRO
// Initial revision.


  */