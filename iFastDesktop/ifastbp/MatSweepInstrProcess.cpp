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
//    Copyright 2011 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : MatSweepInstrProcess.cpp
// ^CLASS  : MatSweepInstrProcess
//
//******************************************************************************

#include "stdafx.h"
#include "MatSweepInstrProcess.hpp"
#include "MatSweepInstrProcessincludes.h"

#include <ifastcbo\MatSweepInstrList.hpp>
#include <ifastcbo\MatSweepInstr.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MATSWP_INSTR;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MATSWP_INSTR;

#include <bfproc\concreteprocesscreator.hpp>

static ConcreteProcessCreator< MatSweepInstrProcess > processCreator( CMD_BPROC_MATSWP_INSTR );

namespace 
{
   const I_CHAR *CLASSNAME			= I_("MatSweepInstrProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace TRADE_VALIDATION_GROUP
{
   extern CLASS_IMPORT const long MATSWEEP_ATTRIB;
}


//******************************************************************************
//              Public Methods
//******************************************************************************
MatSweepInstrProcess::MatSweepInstrProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ) 
, _rpChildGI( NULL )
, m_Caller (NULL_STRING)
, m_strInstrType (NULL_STRING)
, m_MatSweepInstrListKey (NULL_STRING)
, m_accountNum (NULL_STRING)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	addContainer (IFASTBP_PROC::TRADE, false, BF::NullContainerId, true, I_("Trade"));
	addContainer (IFASTBP_PROC::MAT_SWEEP_INSTRUCTION, false,  BF::NullContainerId, true, I_("MatSweepInstruction"));

	addFieldDetails( ifds::MatSwpInstructionType,	IFASTBP_PROC::MAT_SWEEP_INSTRUCTION);
	addFieldDetails( ifds::AccountNum,				IFASTBP_PROC::MAT_SWEEP_INSTRUCTION);
	addFieldDetails( ifds::Fund,					IFASTBP_PROC::MAT_SWEEP_INSTRUCTION);
	addFieldDetails( ifds::Class,					IFASTBP_PROC::MAT_SWEEP_INSTRUCTION);
	addFieldDetails( ifds::SplitType,				IFASTBP_PROC::MAT_SWEEP_INSTRUCTION);
	addFieldDetails( ifds::EffectiveDate,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION);
	addFieldDetails( ifds::TransNum,				IFASTBP_PROC::MAT_SWEEP_INSTRUCTION);
	addFieldDetails( ifds::CashSweepBal,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION);
	addFieldDetails( ifds::SelectedAmt,				IFASTBP_PROC::MAT_SWEEP_INSTRUCTION);
	addFieldDetails( ifds::IntInvestId,				IFASTBP_PROC::MAT_SWEEP_INSTRUCTION);
	addFieldDetails( ifds::GBCD,					IFASTBP_PROC::MAT_SWEEP_INSTRUCTION);
}

//******************************************************************************
MatSweepInstrProcess::~MatSweepInstrProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY MatSweepInstrProcess::doInit()
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   getParameter (CALLER, m_Caller);
   getParameter (ACCOUNT_NUM, m_accountNum);
   getParameter (LIST_KEY_INV, m_MatSweepInstrListKey);
   getParameter (INSTR_TYPE, m_strInstrType );

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool MatSweepInstrProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_MATSWP_INSTR);
}

//******************************************************************************
E_COMMANDRETURN MatSweepInstrProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (CALLER, m_Caller);   
      setParameter (ACCOUNT_NUM, m_accountNum);  
	  setParameter (INSTR_TYPE, m_strInstrType );

      rtn = invokeCommand( this, CMD_GUI_MATSWP_INSTR, PROC_NO_TYPE, isModal(), &_rpChildGI );
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
void *MatSweepInstrProcess::getPtrForContainer( const BFContainerId& idContainer,
                                               const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   
	void *ptr = NULL;
	DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	try
	{
		if (IFASTBP_PROC::MAT_SWEEP_INSTRUCTION == idContainer)
		{
         MFAccount *pMFAccount = NULL;
         MatSweepInstrList *pMatSweepInstrList = NULL;

         if (m_Caller == COA)
         {
         		
	         if (pDSTCWorkSession->getMFAccount (idDataGroup, m_accountNum, pMFAccount) <= WARNING && pMFAccount)
	         {
		         if ( pMFAccount->getMatSweepInstrList (pMatSweepInstrList,
                                                      m_strInstrType,
                                                      idDataGroup) <= WARNING && pMatSweepInstrList)
		         {
			         BFObjIter iter (*pMatSweepInstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

			         iter.positionByKey (m_MatSweepInstrListKey);
         			
			         if (!iter.end())
			         {
				         ptr = dynamic_cast <MatSweepInstr*>(iter.getObject());
			         }
		         }

	         }
         }
			/*else if (m_Caller == I_("TradeEntry"))
			{
				WorksessionTradesList *pTradesList (NULL);

				if( pDSTCWorkSession->getTradesList (pTradesList, idDataGroup) <= WARNING && 
					pTradesList)
				{
					BFObjIter iter (*pTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

					iter.positionByKey (m_MatSweepInstrListKey);
					if (!iter.end())
					{
						ptr = dynamic_cast <Trade*>(iter.getObject());
					}
				}
			}*/
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
   
	return ptr;  
}

//******************************************************************************
bool MatSweepInstrProcess::doOk (GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );

   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

//*****************************************************************************
SEVERITY MatSweepInstrProcess::doValidateAll ( BFAbstractCBO *rpWSD, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOVALIDATEALL);
   
   if (m_Caller == I_("TradeEntry"))
   {
//      Trade *pTrade = 
//         dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));
//
//      if (pTrade)
//      {
////validate only the GI attrib group
//         pTrade->validateAll (idDataGroup, TRADE_VALIDATION_GROUP::MATSWEEP_ATTRIB);
//      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool MatSweepInstrProcess::doSend ( GenericInterface *rpGICaller,
                                   const I_CHAR  *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSEND);

   DString message (szMessage);
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   Trade *pTrade = 
      dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));
   
   //reset settle location values, only for new trades
   if (m_Caller == I_("TradeEntry") && pTrade)
   {
      if (message == I_("Cancel")) 
      {
         pTrade->resetGIAAttrib (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/*
*/