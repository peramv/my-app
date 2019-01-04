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
// ^FILE   : MatSweepInstrDetailProcess.cpp
// ^CLASS  : MatSweepInstrDetailProcess
//
//******************************************************************************

#include "stdafx.h"
#include "MatSweepInstrDetailProcess.hpp"
#include "MatSweepInstrDetailProcessincludes.h"

#include <ifastcbo\MatSweepInstrList.hpp>
#include <ifastcbo\MatSweepInstr.hpp>
#include <ifastcbo\MatSweepInstrDetails.hpp>
#include <ifastcbo\MatSweepInstrDetailsList.hpp>

#include <ifastcbo\trade.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MATSWP_INSTR_DETLS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MATSWP_INSTR_DETLS;

#include <bfproc\concreteprocesscreator.hpp>

static ConcreteProcessCreator< MatSweepInstrDetailProcess > processCreator( CMD_BPROC_MATSWP_INSTR_DETLS );

namespace 
{
   const I_CHAR *CLASSNAME			= I_("MatSweepInstrDetailProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace TRADE_VALIDATION_GROUP
{
   extern CLASS_IMPORT const long MATSWEEP_ATTRIB_DETAIL;
}


//******************************************************************************
//              Public Methods
//******************************************************************************
MatSweepInstrDetailProcess::MatSweepInstrDetailProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ) 
, _rpChildGI( NULL )
, m_Caller (NULL_STRING)
, m_strInstrType (NULL_STRING)
, m_MatSweepInstrListKey (NULL_STRING)
, m_MatSweepInstrDetailListKey (NULL_STRING)
, m_accountNum (NULL_STRING)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	addContainer (IFASTBP_PROC::TRADE, false, BF::NullContainerId, true, I_("Trade"));
	addContainer (IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, false,  BF::NullContainerId, true, I_("MatSweepInstruction"));

	addFieldDetails( ifds::DistribDetlUUID,	IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::IntInvestId,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::RolloverType,    IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::AccountTo,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::FundTo,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::ClassTo,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::RemainingFleg,   IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::Currency,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::Percentage,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::PayType,         IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::PayTypeDesc,     IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::CommReduction,   IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::IntInvestType,	IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::FELAmt,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::IntInvestTerm,   IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::IntCalcMthd,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::ForcedRate,      IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::ForcedRateAmt,	IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::IntCredFreq,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BusinessType,    IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::RefNum,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::AddlAmt,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	
	// bank fields:
	addFieldDetails( ifds::BankAcctId,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAcctUse,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankIdType,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankIdValue,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankTransitNo,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankSwiftCode,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankRefNumber,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::InstName,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAddr1,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAddr2,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAddr3,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAddr4,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAddr5,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankPostal,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankCountry,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAcctType,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAcctTypeDesc,	IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAcctCurrency,	IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAcctCurrDesc,	IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankEffectiveDate,	IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankStopDate,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::PayMethod,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::ACHProcessor,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankContact,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankCorrespondent,	IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::AddrCode,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
    addFieldDetails( ifds::BankId1,				IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAcctNum,			IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAcctName,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::IntInvestUUID,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);	
	addFieldDetails( ifds::DistribDetlVersion,	IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::BankAcctVersion,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);
	addFieldDetails( ifds::IntInvestVer,		IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL);

}

//******************************************************************************
MatSweepInstrDetailProcess::~MatSweepInstrDetailProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY MatSweepInstrDetailProcess::doInit()
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   getParameter (CALLER, m_Caller);
   getParameter (ACCOUNT_NUM, m_accountNum);
   getParameter (LIST_KEY_INV, m_MatSweepInstrListKey);
   getParameter (LIST_KEY_DETL, m_MatSweepInstrDetailListKey);
   getParameter (INSTR_TYPE, m_strInstrType );

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool MatSweepInstrDetailProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_MATSWP_INSTR_DETLS);
}

//******************************************************************************
E_COMMANDRETURN MatSweepInstrDetailProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (CALLER, m_Caller);   
      setParameter (ACCOUNT_NUM, m_accountNum);  
	  setParameter (INSTR_TYPE, m_strInstrType );

      rtn = invokeCommand( this, CMD_GUI_MATSWP_INSTR_DETLS, PROC_NO_TYPE, isModal(), &_rpChildGI );
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
void *MatSweepInstrDetailProcess::getPtrForContainer( const BFContainerId& idContainer,
                                               const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   
	void *ptr = NULL;
	DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	try
	{
		if (IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL == idContainer)
		{
		  //
			MFAccount *pMFAccount = NULL;
		    MatSweepInstrList *pMatSweepInstrList = NULL;

			if (m_Caller == COA)
			{
					
				if (pDSTCWorkSession->getMFAccount (idDataGroup, m_accountNum, pMFAccount) <= WARNING && pMFAccount)
				{
					if ( pMFAccount->getMatSweepInstrList (pMatSweepInstrList,
                                                           m_strInstrType,
                                                           idDataGroup) <= WARNING && pMatSweepInstrList )
					{
						BFObjIter iter (*pMatSweepInstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

						iter.positionByKey (m_MatSweepInstrListKey);
						
						if (!iter.end())
						{
							MatSweepInstr *pMatSweepInstr = dynamic_cast <MatSweepInstr*>(iter.getObject());

							if (pMatSweepInstr)
							{
								MatSweepInstrDetailsList *pMatSweepInstrDetailsList = NULL;

								if (pMatSweepInstr->getMatSweepDetailsList (pMatSweepInstrDetailsList, idDataGroup) <= WARNING &&
									 pMatSweepInstrDetailsList)
								{

									BFObjIter iter1 (*pMatSweepInstrDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
						
									iter1.positionByKey (m_MatSweepInstrDetailListKey);
									
									if (!iter1.end())
									{
										ptr = dynamic_cast <MatSweepInstrDetails*>(iter1.getObject());
									}
								}                                     
							}	
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
bool MatSweepInstrDetailProcess::doOk (GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );

   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

//*****************************************************************************
SEVERITY MatSweepInstrDetailProcess::doValidateAll ( BFAbstractCBO *rpWSD, 
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
bool MatSweepInstrDetailProcess::doSend ( GenericInterface *rpGICaller,
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