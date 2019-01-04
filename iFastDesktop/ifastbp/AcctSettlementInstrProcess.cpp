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
// ^FILE   : AcctSettlementInstrProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AcctSettlementInstrProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "mfcaninterprocparam.hpp"
#include "AcctSettlementInstrProcess.hpp"
#include "AcctSettlementInstrProcessincludes.h"

#include <ifastdataimpl\dse_dstcglob_vw.hpp>


#include <ifastcbo\ErrMsgRulesList.hpp>
#include <ifastcbo\acctsettlementinstr.hpp>
#include <ifastcbo\acctsettlementinstrlist.hpp>
#include <ifastcbo\fundmgmtsettlementinstr.hpp>
#include <ifastcbo\fundmgmtsettlementinstrlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AcctSettlementInstrProcess > processCreator( CMD_BPROC_SETTLEMENT_INSTRUCTIONS_ACCTLVL );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long BP_ERR_CLIENT_SETTLE_INSTR_MANDATORY;
   extern const long BP_WRN_NO_CLIENT_SETTLE_INSTR;
}

namespace 
{
   const I_CHAR * const CLASSNAME = I_( "AcctSettlementInstrProcess" );
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const FUND_MGMT_CLIENT_SETTLEMENT_INSTR_REQUIRED;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AcctSettlementInstrProcess::AcctSettlementInstrProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: SettlementInstrProcess( pGIC, pGIParent, rCommand ),
m_rpChildGI( NULL  ), 
m_pFndMgmtSettlementInstructiondList( NULL ),
m_pSettlementInstructiondList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	
	addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, true, I_("Account") );

   // Account - for Title, when called for Account
   addFieldDetails( ifds::ShrNum,     IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO );		
}

//******************************************************************************
AcctSettlementInstrProcess::~AcctSettlementInstrProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   m_rpChildGI = NULL;
}

//******************************************************************************
SEVERITY AcctSettlementInstrProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );

   SettlementInstrProcess::doInit();
   getParameter(I_("AccountNum"), m_dstrAccountNumber );
   const BFDataGroupId& idDataGroup = getDataGroupId();

   {
      try
      {
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

         MFAccount *pMFAccount;
         if( dstcWorkSession->getMFAccount( idDataGroup, m_dstrAccountNumber, pMFAccount ) <= WARNING &&
				 NULL != pMFAccount )
         {
            if ( pMFAccount->getFundMgmtSettlementInstrList( m_pFndMgmtSettlementInstructiondList, 
					                                              idDataGroup ) <= WARNING &&
					  NULL != m_pFndMgmtSettlementInstructiondList )
            {
               setContainer( IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST, m_pFndMgmtSettlementInstructiondList );      
            }

			   if ( pMFAccount->getSettlementInstrList( m_pSettlementInstructiondList, idDataGroup ) <= WARNING &&
					NULL != m_pSettlementInstructiondList )
			   {
				   setContainer( IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, m_pSettlementInstructiondList );      
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

//******************************************************************************
//              Protected Methods
//******************************************************************************
bool AcctSettlementInstrProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_SETTLEMENT_INSTRUCTIONS_ACCTLVL );
}

//******************************************************************************
E_COMMANDRETURN AcctSettlementInstrProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_SETTLEMENT_INSTRUCTIONS_ACCTLVL, getProcessType(), isModal(), &m_rpChildGI );
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
void* AcctSettlementInstrProcess::getPtrForContainer( const BFContainerId& idContainer, 
																					 const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {
      if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
      {
         MFAccount *pMFAccount;
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
}

//******************************************************************************
bool AcctSettlementInstrProcess::doOk(GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   // Update Account Details Option.
   MFAccount *pMFAccount = NULL;
   DString dstrSettlementLocationFlag = I_( "N" );
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( NULL != dstcWorkSession &&
       dstcWorkSession->getMFAccount( idDataGroup, m_dstrAccountNumber, pMFAccount ) <= WARNING &&
       NULL != pMFAccount )
   {

		FundMgmtSettlementInstrList *pFundMgmtSettlementInstrList = NULL;
		if( pMFAccount->getFundMgmtSettlementInstrList( pFundMgmtSettlementInstrList, idDataGroup ) <= WARNING &&
          NULL != pFundMgmtSettlementInstrList )
		{
			BFObjIter iter( *pFundMgmtSettlementInstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			while( !iter.end() )
			{
				if( !iter.isDummy() )
				{
					dstrSettlementLocationFlag = I_( "Y" );
					break;
				}
				++iter;
			}
      }
      pMFAccount->setField( ifds::SettleLocExist, dstrSettlementLocationFlag, idDataGroup, false );

      bool bAcctSettlementInstrExists = false;

      if ( dstrSettlementLocationFlag == I_( "Y" ) )
      {			
         AcctSettlementInstrList *pAcctSettlementInstrList = NULL;

         if (pMFAccount->getSettlementInstrList( pAcctSettlementInstrList, idDataGroup) <= WARNING &&
             NULL != pAcctSettlementInstrList )
			{
   			BFObjIter iter( *pAcctSettlementInstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	   		while( !iter.end() )
		   	{
			   	if( !iter.isDummy() )
				   {
					   bAcctSettlementInstrExists = true;
					   break;
				   }
				   ++iter;
            }
			}
		}

      if ( dstrSettlementLocationFlag == I_( "Y" ) && !bAcctSettlementInstrExists) 
      {
         ErrMsgRulesList *pErrMsgRulesList = NULL;
         if ( dstcWorkSession->getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
              NULL != pErrMsgRulesList )
         {
            DString dstrErrValue;
            pErrMsgRulesList->getEWIValue( I_( "429" ), idDataGroup, dstrErrValue );
            dstrErrValue.strip().upperCase();
            if ( I_( "E" ) == dstrErrValue )
            {
               ADDCONDITIONFROMFILE( CND::BP_ERR_CLIENT_SETTLE_INSTR_MANDATORY );
               //PROMOTECONDITIONS();
            }
            //else if ( I_( "W" ) == dstrErrValue )
            //{
            //  ADDCONDITIONFROMFILE( CND::BP_WRN_NO_CLIENT_SETTLE_INSTR );
            //}
         }
      }     
   }
   return (GETCURRENTHIGHESTSEVERITY() <= WARNING );
}

//******************************************************************************
SEVERITY AcctSettlementInstrProcess::doValidateAll( BFAbstractCBO *rpWSD,
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
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/AcctSettlementInstrProcess.cpp-arc  $
// 
//    Rev 1.5   Dec 10 2004 10:12:20   vadeanum
// PET1117_FN21: settlement instructions - cleanup.
// 
//    Rev 1.4   Dec 09 2004 15:33:50   vadeanum
// PET1117_FN21: settlement instructions - added doValidateAll().
// 
//    Rev 1.3   Dec 01 2004 20:35:16   vadeanum
// PET1117_FN21: settlement instructions - the error message should pop up only when there a fundmgmt level instr.
// 
//    Rev 1.2   Nov 26 2004 10:00:06   aguilaam
// PET1117-FN21: settlement instructions 
// 
//    Rev 1.1   Nov 19 2004 17:31:40   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.0   Oct 13 2004 15:22:18   VADEANUM
// Initial revision.
//
