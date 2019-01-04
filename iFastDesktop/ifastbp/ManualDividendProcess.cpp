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
//    Copyright 2003 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : ManualDividendProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ManualDividendProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "ManualDividendProcess.hpp"
#include "ManualDividendProcessincludes.h"
#include <ifastcbo\ManualDividendList.hpp>
#include <ifastcbo\ManualDividend.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mfaccount.hpp>
#include "mfcaninterprocparam.hpp"
#include "confirmationprocessincludes.h"
//--- Testing
#include <ifastcbo\trade.hpp>
#include <dataimpl\ifast_fieldids.hpp>


#include <dataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MANUAL_DIVIDEND;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MANUAL_DIVIDEND;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ManualDividendProcess > processCreator( CMD_BPROC_MANUAL_DIVIDEND );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace 
{
   const I_CHAR * const CLASSNAME = I_( "ManualDividendProcess" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************
ManualDividendProcess::ManualDividendProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_rpChildGI( NULL  ), m_pManualDividendList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MANUAL_DIVIDEND_LIST, true, BF::NullContainerId, true, I_("ManualDividendList") );

   addSubstituteList( ifds::ManualDividendHeading );

   // Transaction List
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::FromFund, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::FromClass, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::FromFundNumber, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::ToFund, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::ToClass, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::ToFundNumber, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::AmtType, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::Amount, IFASTBP_PROC::MANUAL_DIVIDEND_LIST);
   addFieldDetails( ifds::TradesPayType, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::SuppressCode, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::AddrCode, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::AddrLine1, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::AddrLine2, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::AddrLine3, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::AddrLine4, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::AddrLine5, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::TransNum, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::Batch, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::SettleDate, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::Remarks1, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::Remarks2, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::Remarks3, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::OrderType, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::SettleCurrency, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::Accountable, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );
   addFieldDetails( ifds::BackDatedReason, IFASTBP_PROC::MANUAL_DIVIDEND_LIST );

   // Subclass Process Field
   addFieldDetails( ifds::ShareholderAddress, IFASTBP_PROC::MANUAL_DIVIDEND_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ShrNum, BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************

ManualDividendProcess::~ManualDividendProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY ManualDividendProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );

   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   {
      try
      {
         if (dstcWorkSession->getManualDividendList( m_pManualDividendList, 
            idDataGroup, true) <= WARNING && m_pManualDividendList)
         {
            setContainer (IFASTBP_PROC::MANUAL_DIVIDEND_LIST, m_pManualDividendList);
         }
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
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool ManualDividendProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_MANUAL_DIVIDEND );
}

//******************************************************************************

bool ManualDividendProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

   bool bRtn = false;
   try
   {
      assert( m_rpChildGI );
      if( isValidModelessInterface( m_rpChildGI ) )
      {
         bRtn = m_rpChildGI->refresh( this, NULL );
         bRtn = m_rpChildGI->modelessSetFocus( rpGICaller );
      }
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

   return( bRtn );
}

//******************************************************************************

E_COMMANDRETURN ManualDividendProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_MANUAL_DIVIDEND, getProcessType(), isModal(), &m_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return( rtn );
}

//******************************************************************************

void* ManualDividendProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {
/*
      if( IFASTBP_PROC::MANUAL_DIVIDEND_LIST == idContainer )
      {
         {
            MktIndexValues *pMktIndexValues = dynamic_cast< MktIndexValues * >( getCBOItem(IFASTBP_PROC::MANUAL_DIVIDEND_LIST, idDataGroup ) );
            MktIndexFundsList* pMktIndexFundsList = NULL;
            if( pMktIndexValues->getMktIndexFundsList( pMktIndexFundsList, idDataGroup ) <= WARNING )
            {
               ptr = pMktIndexFundsList;
            }
         }
      }
      else
      {
      }
*/
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
   return(ptr);
}

//******************************************************************************

bool ManualDividendProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) 
{
   return(false);
}

//******************************************************************************

bool ManualDividendProcess::doOk(GenericInterface *rpGICaller)
{
   setParameter( CONFPROC::PARM_CALLED_FROM, I_("ManualDividend") );
   return( true );
}

//******************************************************************************

void ManualDividendProcess::doGetField(    const GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer,
                                           const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup,
                                           DString &dstrValueOut,
                                           bool bFormatted
                                           ) const
{
   dstrValueOut = NULL_STRING;
   if( idField == ifds::ShareholderAddress )
   {
      ManualDividend *pManualDividend = dynamic_cast< ManualDividend * >( const_cast< ManualDividendProcess * >( this )->getCBOItem( IFASTBP_PROC::MANUAL_DIVIDEND_LIST, idDataGroup ) );
      if( pManualDividend )
      {
         //pManualDividend->getAddress( dstrValueOut, idDataGroup );
      }
   }
   else if( idField == ifds::ShrNum )
   {
      MFAccount *pMFAccount = NULL;
      ManualDividend *pManualDividend = dynamic_cast< ManualDividend * >( const_cast< ManualDividendProcess * >( this )->getCBOItem( IFASTBP_PROC::MANUAL_DIVIDEND_LIST, idDataGroup ) );
      if( pManualDividend )
      {
         DString dstrAccountNum;
         pManualDividend->getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );
         DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         pDSTCWorkSession->getMFAccount( idDataGroup, dstrAccountNum, pMFAccount );
         pMFAccount->getField( idField, dstrValueOut, idDataGroup, false );
      }
   }
}

// ******************************************************************************
// Revision Control Entries
// ******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ManualDividendProcess.cpp-arc  $
// 
//    Rev 1.2   May 27 2005 10:10:30   popescu
// Incident # 319459 - fixed the Manual Dividend reset issue - also used WorkSessionTradesList for manual dividends; use the TradesProcess instead of ManualDividendProcess
// 
//    Rev 1.1   May 28 2003 10:52:00   popescu
// Part of the cleaning of DSTCWorksession, not finalized yet, more to come....
// 
//    Rev 1.0   May 22 2003 17:01:06   HERNANDO
// Initial revision.
 */
