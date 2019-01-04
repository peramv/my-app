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
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : FundBrokerSettlementInstrProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundBrokerSettlementInstrProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "mfcaninterprocparam.hpp"
#include "FundBrokerSettlementInstrProcess.hpp"
#include "FundBrokerSettlementInstrProcessIncludes.h"

#include <ifastdataimpl\dse_dstcglob_vw.hpp>

#include <ifastcbo\fundmgmtsettlementinstr.hpp>
#include <ifastcbo\fundmgmtsettlementinstrlist.hpp>
#include <ifastcbo\fundbroker.hpp>
#include <ifastcbo\fundbrokerlist.hpp>
#include <ifastcbo\fundbrokersettlementinstr.hpp>
#include <ifastcbo\fundbrokersettlementinstrlist.hpp>

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FundBrokerSettlementInstrProcess > processCreator( CMD_BPROC_FUND_BROKER_SETTLEMENT_INSTR );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace 
{
   const I_CHAR * const CLASSNAME = I_( "FundBrokerSettlementInstrProcess" );
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const ATSET;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
FundBrokerSettlementInstrProcess::FundBrokerSettlementInstrProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: SettlementInstrProcess( pGIC, pGIParent, rCommand )
,  m_rpChildGI( NULL  ), 
m_pFndMgmtSettlementInstructiondList( NULL ),
m_pSettlementInstructiondList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	
	addContainer( IFASTBP_PROC::FUND_BROKER_LIST, false, BF::NullContainerId, true, I_("FundBrokerList") );   
	addFieldDetails( ifds::FundBrokerCode, IFASTBP_PROC::FUND_BROKER_LIST );
}

//******************************************************************************
FundBrokerSettlementInstrProcess::~FundBrokerSettlementInstrProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   m_rpChildGI = NULL;
} 


//******************************************************************************
SEVERITY FundBrokerSettlementInstrProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );

   SettlementInstrProcess::doInit();
   getParameter(I_("FundBrokerCode"), m_dstrFundBrokerCode );
   const BFDataGroupId& idDataGroup = getDataGroupId();

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   {
      try
      {
         FundBrokerList *pFundBrokerList = NULL;
         FundBroker *pFundBroker = NULL;
         if( NULL != dstcWorkSession &&
             dstcWorkSession->getFundBrokerList( pFundBrokerList, idDataGroup, false, I_( "" ), I_("") ) <= WARNING &&
				 NULL != pFundBrokerList )
         {
            //setContainer (IFASTBP_PROC::FUND_BROKER_LIST, pFundBrokerList);
            if (pFundBrokerList->getFundBroker ( m_dstrFundBrokerCode, idDataGroup, pFundBroker) <= WARNING &&
                pFundBroker)
            {
               setContainer (IFASTBP_PROC::FUND_BROKER_LIST, pFundBroker);
               
               if ( pFundBroker->getFndMgmtSettlementInstrList( m_pFndMgmtSettlementInstructiondList, 
					                                                idDataGroup ) <= WARNING &&
					   NULL != m_pFndMgmtSettlementInstructiondList )
               {
                  setContainer( IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST, m_pFndMgmtSettlementInstructiondList );      
               }

				   if ( pFundBroker->getSettlementInstrList( m_pSettlementInstructiondList, idDataGroup ) <= WARNING &&
					   NULL != m_pSettlementInstructiondList )
				   {
					   setContainer( IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, m_pSettlementInstructiondList );      
				   }
            }
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

/*
//******************************************************************************
void* FundBrokerSettlementInstrProcess::getPtrForContainer( const BFContainerId& idContainer, 
																					 const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {
      if( IFASTBP_PROC::FUND_BROKER_LIST == idContainer )
      {
         FundBrokerList *pFundBrokerList;
         FundBroker *pFundBroker;
         if( NULL != dstcWorkSession &&
             dstcWorkSession->getFundBrokerList( pFundBrokerList, idDataGroup, false, m_dstrFundBrokerCode, I_("") ) <= WARNING &&
				 NULL != pFundBrokerList )
         {
            if ( pFundBroker->getFndMgmtSettlementInstrList( m_pFndMgmtSettlementInstructiondList, 
					                                              idDataGroup ) <= WARNING &&
					  NULL != m_pFndMgmtSettlementInstructiondList )
            {
               setContainer( IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST, m_pFndMgmtSettlementInstructiondList );      
            }
         

            pFundBroker *pFundBroker;
         if( dstcWorkSession->getMFAccount( idDataGroup, m_dstrAccountNumber, pMFAccount ) <= WARNING )
         {
            ptr = pMFAccount;

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
   return(ptr);
}*/

//******************************************************************************
//              Protected Methods
//******************************************************************************
bool FundBrokerSettlementInstrProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_FUND_BROKER_SETTLEMENT_INSTR );
}

//******************************************************************************
E_COMMANDRETURN FundBrokerSettlementInstrProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {        
      rtn = invokeCommand( this, CMD_GUI_FUND_BROKER_SETTLEMENT_INSTR, getProcessType(), isModal(), &m_rpChildGI );
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
SEVERITY FundBrokerSettlementInstrProcess::doValidateAll( BFAbstractCBO *rpWSD,
                                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));
	
   if( NULL != m_pFndMgmtSettlementInstructiondList )
   {
      m_pFndMgmtSettlementInstructiondList->validateAll( idDataGroup );
   }

   if( NULL != m_pSettlementInstructiondList )
   {
      m_pSettlementInstructiondList->validateAll( idDataGroup );
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool FundBrokerSettlementInstrProcess::doOk(GenericInterface *rpGICaller)
{
 
   return( true );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundBrokerSettlementInstrProcess.cpp-arc  $
// 
//    Rev 1.4   Dec 10 2004 17:23:08   vadeanum
// PET117_FN21: settlement instructions enhancement.
// 
*/
