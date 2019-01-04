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
// ^FILE   : ContractMaturityInstructionProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ContractMaturityInstructionProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "ContractMaturityInstructionsProcessIncludes.h"
#include "ContractMaturityInstructionProcess.hpp"
#include "ContractInfoProcess.hpp"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>

#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\WorksessionEntityList.hpp>
#include <ifastcbo\AddressList.hpp>
#include <ifastcbo\Shareholder.hpp>
#include <ifastcbo\ErrMsgRulesList.hpp>
#include <ifastcbo\MgmtCo.hpp>
#include <ifastcbo\ContractMaturityInstructionList.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_CONTRACT_MATURITY_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CONTRACT_MATURITY_INSTRUCTIONS;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ContractMaturityInstructionProcess > processCreator( CMD_BPROC_CONTRACT_MATURITY_INSTRUCTIONS);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME		= I_( "ContractMaturityInstructionProcess" );
   const I_CHAR * const PERFORMSEARCH	= I_( "performSearch" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId ContractType;
	extern CLASS_IMPORT const BFTextFieldId AmountType1;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
ContractMaturityInstructionProcess::ContractMaturityInstructionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_pContractMatInstrList (NULL)
, m_strAcctNum(NULL_STRING)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

    addContainer( IFASTBP_PROC::MFACCOUNT_CBO,					false,	BF::NullContainerId,	true);
	addContainer( IFASTBP_PROC::ADDRESS_LIST,					true,	BF::NullContainerId,	true,  I_("Address"));
	addContainer( IFASTBP_PROC::CONTRACTINFO_LIST,				true  );
	addContainer( IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, true,	BF::NullContainerId,	true, I_("ContractMatInstr"));

	addFieldDetails (ifds::AcctGroupName,		IFASTBP_PROC::MFACCOUNT_CBO);
	addFieldDetails (ifds::AccountNum,			IFASTBP_PROC::MFACCOUNT_CBO);
	addFieldDetails (ifds::BranchCode,			IFASTBP_PROC::MFACCOUNT_CBO);
	addFieldDetails (ifds::BranchName,			IFASTBP_PROC::MFACCOUNT_CBO);
	addFieldDetails (ifds::BrokerCode,			IFASTBP_PROC::MFACCOUNT_CBO);
	addFieldDetails (ifds::BrokerName,			IFASTBP_PROC::MFACCOUNT_CBO);

	addFieldDetails (ifds::AddrCode,			IFASTBP_PROC::ADDRESS_LIST);
	addFieldDetails (ifds::AddrLine1,			IFASTBP_PROC::ADDRESS_LIST);
	addFieldDetails (ifds::AddrLine2,			IFASTBP_PROC::ADDRESS_LIST);
	addFieldDetails (ifds::AddrLine3,			IFASTBP_PROC::ADDRESS_LIST);
	addFieldDetails (ifds::AddrLine4,			IFASTBP_PROC::ADDRESS_LIST);
	addFieldDetails (ifds::AddrLine5,			IFASTBP_PROC::ADDRESS_LIST);
	
	addFieldDetails (ifds::ContractTerm,		IFASTBP_PROC::CONTRACTINFO_LIST);
	addFieldDetails (ifds::LegalMaturityDate,	IFASTBP_PROC::CONTRACTINFO_LIST);
	addFieldDetails (ifds::CotAcctRid,			IFASTBP_PROC::CONTRACTINFO_LIST);
	addFieldDetails (ifds::CMPolicyYear,		IFASTBP_PROC::CONTRACTINFO_LIST);
	addFieldDetails (ifds::CMPolicyTerm,		IFASTBP_PROC::CONTRACTINFO_LIST);
	addFieldDetails (ifds::CMMaturityDate,		IFASTBP_PROC::CONTRACTINFO_LIST);

	addFieldDetails (ifds::ModUser,				IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::ModDate,				IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::ProcessDate,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::Username,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);

	addFieldDetails (ifds::ContractType,		IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::InstId,				IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::InstName,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::PolicyYear,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::PolicyTerm,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::MaturityDate,		IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::RedCode,				IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::PayType3,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::PUD1,				IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::Amount,				IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::AddrCode,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::ADCD,				IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::AddrLine1,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::AddrLine2,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::AddrLine3,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::AddrLine4,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::AddrLine5,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::SourceOfFunds,		IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::BankAcctName,		IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::BankIdNum,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::TransitNum,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::BankAcctNum,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails (ifds::AcctID,				IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails( ifds::BankAcctVer,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails( ifds::BankType,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails( ifds::BankContact,         IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
    addFieldDetails( ifds::BankCntry,           IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
    addFieldDetails( ifds::BankPstl,            IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
	addFieldDetails( ifds::BankAddr1,           IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
    addFieldDetails( ifds::BankAddr2,           IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
    addFieldDetails( ifds::BankAddr3,           IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
    addFieldDetails( ifds::BankAddr4,           IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
    addFieldDetails( ifds::BankAddr5,           IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS);
}

//******************************************************************************
ContractMaturityInstructionProcess::~ContractMaturityInstructionProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
bool ContractMaturityInstructionProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
  return m_pContractMatInstrList == NULL ? false : m_pContractMatInstrList->doMoreRecordsExist();
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY ContractMaturityInstructionProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

	try
	{
		getParameter (CONMATINS_PROC::ACCOUNT_NUM_VALUE,	m_strAcctNum);
		getParameter (CONMATINS_PROC::COT_REC_ID,			m_dstrCotAcctRid);
		getParameter (CONMATINS_PROC::CONTRACT_TYPE,		m_strContractType);
		getParameter (CONMATINS_PROC::CONTRACT_TYPE_ID,		m_strContractTypeId);
		getParameter (CONMATINS_PROC::POLICY_YEAR,			m_dstrPolicyYear);
		getParameter (CONMATINS_PROC::POLICY_TERM,			m_dstrPolicyTerm);
		getParameter (CONMATINS_PROC::MATURITY_DATE,		m_dstrMaturityDate);

		m_strAcctNum.strip();
		m_strContractType.strip();
		m_strContractTypeId.strip();
		m_dstrPolicyYear.strip();
		m_dstrPolicyTerm.strip();
		m_dstrMaturityDate.strip();
	}
	catch (ConditionException &ce)
	{
		SETCONDITIONFROMEXCEPTION (ce);
	}
	catch (...)
	{
		assert (0);
		THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
	}

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
void ContractMaturityInstructionProcess::doGetField (	const GenericInterface *rpGICaller,
														const BFContainerId& idContainer,
														const BFFieldId& idField,
														const BFDataGroupId& idDataGroup,
														DString &strValueOut,
														bool bFormatted ) const
{

}

//******************************************************************************
bool ContractMaturityInstructionProcess::doRefresh (
                               GenericInterface *rpGICaller, 
                               const I_CHAR *szOriginalCommand)
{
   TRACE_METHOD (CLASSNAME, DOREFRESH);

	setParameter (CONMATINS_PROC::ACCOUNT_NUM_VALUE,	m_strAcctNum);
	setParameter (CONMATINS_PROC::COT_REC_ID,			m_dstrCotAcctRid);
	setParameter (CONMATINS_PROC::CONTRACT_TYPE,		m_strContractType);
	setParameter (CONMATINS_PROC::CONTRACT_TYPE_ID,		m_strContractTypeId);
	setParameter (CONMATINS_PROC::POLICY_YEAR,			m_dstrPolicyYear);
	setParameter (CONMATINS_PROC::POLICY_TERM,			m_dstrPolicyTerm);
	setParameter (CONMATINS_PROC::MATURITY_DATE,		m_dstrMaturityDate);

   return _rpChildGI->refresh (this, NULL);
}

//******************************************************************************
E_COMMANDRETURN ContractMaturityInstructionProcess::doProcess()
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
		setParameter (CONMATINS_PROC::ACCOUNT_NUM_VALUE,	m_strAcctNum);
		setParameter (CONMATINS_PROC::COT_REC_ID,			m_dstrCotAcctRid);
		setParameter (CONMATINS_PROC::CONTRACT_TYPE,		m_strContractType);
		setParameter (CONMATINS_PROC::CONTRACT_TYPE_ID,		m_strContractTypeId);
		setParameter (CONMATINS_PROC::POLICY_YEAR,			m_dstrPolicyYear);
		setParameter (CONMATINS_PROC::POLICY_TERM,			m_dstrPolicyTerm);
		setParameter (CONMATINS_PROC::MATURITY_DATE,		m_dstrMaturityDate);

		rtn = invokeCommand( this, CMD_GUI_CONTRACT_MATURITY_INSTRUCTIONS, getProcessType(), isModal(), &_rpChildGI);
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

   return(rtn);
}

//******************************************************************************
bool ContractMaturityInstructionProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  
	// This is implemented to pass set focus on to child dialog.
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
	bool bRtn = false;

	try
	{
		DString dstrAcctNum;
		getParameter (CONMATINS_PROC::ACCOUNT_NUM_VALUE, dstrAcctNum);
		
		if( dstrAcctNum.stripLeading ('0').strip() != m_strAcctNum )
		{
			
			setContainer ( IFASTBP_PROC::ADDRESS_LIST,		NULL);
			setContainer ( IFASTBP_PROC::CONTRACTINFO_LIST, NULL);
			setContainer ( IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, NULL);
			doInit();
		}

		if(_rpChildGI)
		{
			if (isValidModelessInterface (_rpChildGI))
			{  
				// Only if child still exists
				bRtn = _rpChildGI->refresh (this, NULL);
				bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
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
		THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS, CND::BP_ERR_UNKNOWN_EXCEPTION);
	}

   return(bRtn);
}

//******************************************************************************
bool ContractMaturityInstructionProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_CONTRACT_MATURITY_INSTRUCTIONS);
}

//******************************************************************************
void* ContractMaturityInstructionProcess::getPtrForContainer(	const BFContainerId& idContainer, 
																const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
 
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   void *ptr = NULL;
   try
   {
		if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
		{
			if( dstcWorkSession->getMFAccount( getDataGroupId(), m_strAcctNum, m_pMFAccount ) <= WARNING && m_pMFAccount )
				ptr = m_pMFAccount;
		}
		else if (IFASTBP_PROC::CONTRACTINFO_LIST == idContainer)
		{
			MFAccount *pMFAccount = NULL;
			ContractMaturityInstructionProcess* pThis = const_cast<ContractMaturityInstructionProcess*>(this);
			pMFAccount = dynamic_cast<MFAccount*>( pThis->getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId()) );

			ContractInfoList* pContractInfoList = NULL;
			if( pMFAccount && pMFAccount->getContractInfoList( pContractInfoList, getDataGroupId(), true ) <= WARNING )
			{
				ptr = pContractInfoList;
			}
		}
		else if (IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS == idContainer)
		{
			MFAccount *pMFAccount = NULL;
			ContractMaturityInstructionProcess* pThis = const_cast<ContractMaturityInstructionProcess*>(this);
			pMFAccount = dynamic_cast<MFAccount*>( pThis->getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId()) );

			if( pMFAccount->getContractMaturityInfoList(	m_pContractMatInstrList,
															m_strAcctNum,
															m_dstrCotAcctRid,
															m_strContractType,
															m_strContractTypeId,
															idDataGroup) <= WARNING && m_pContractMatInstrList )
			{
				ptr = m_pContractMatInstrList;
			}
		}
		else if( IFASTBP_PROC::ADDRESS_LIST == idContainer )
		{
			m_pAddressList = NULL;

			MFAccount *pMFAccount = NULL;
			ContractMaturityInstructionProcess* pThis = const_cast<ContractMaturityInstructionProcess*>(this);
			pMFAccount = dynamic_cast<MFAccount*>( pThis->getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId()) );

			if( pMFAccount )
			{
				DString dstrShrNum = NULL_STRING;
				pMFAccount->getField(ifds::ShrNum, dstrShrNum, idDataGroup);
				if( !dstrShrNum.strip().empty() )
				{
					dstcWorkSession->getShareholder( idDataGroup, dstrShrNum, m_pShareholder );
				}
			}
			
			if( m_pShareholder )
				m_pShareholder->getAddressList( m_pAddressList, getDataGroupId() );

			if( m_pAddressList )
				ptr = m_pAddressList;
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
SEVERITY ContractMaturityInstructionProcess::doSetField (   const GenericInterface *rpGICaller,
															const BFContainerId &idContainer,
															const BFFieldId &idField,
															const BFDataGroupId &idDataGroup,
															const DString &strValue,
															bool bFormatted )
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION,  CLASSNAME, I_("doSetField"));

   if ( idContainer == BF::NullContainerId )
   {
    
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ContractMaturityInstructionProcess::doValidateAll (BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOVALIDATEALL);

   if(m_pContractMatInstrList)
		m_pContractMatInstrList->validateAll (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ContractMaturityInstructionProcess::performSearch (GenericInterface *rpGICaller, 
															const BFContainerId& idSearch, 
															E_SEARCHACTION eSearchAction)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );
	
	const BFDataGroupId& idDataGroup = getDataGroupId ();
	
	try
	{
		switch (eSearchAction)
		{
			case SEARCH_NEXT_BLOCK:
			{
				if (idSearch == IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS)
				{
					if (m_pContractMatInstrList)
						m_pContractMatInstrList->getMore();
				}
			}
			break;

			default:
				break;

		}//end of switch (eSearchAction)
	}//end of try
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ContractMaturityInstructionProcess.cpp-arc  $
// 
//    Rev 1.9   Mar 28 2012 17:53:30   wp040100
// P0186484 FN05 - Contract Maturity Instruction - Changed the the field in V431 from BankAcctVersion to BankAcctVer - Banking Screen Update Fix
// 
//    Rev 1.8   Mar 22 2012 18:38:12   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.7   Mar 16 2012 17:43:44   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.6   Mar 15 2012 19:33:36   wp040100
// IN 2874666 - P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.5   Mar 05 2012 20:37:06   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.4   Mar 02 2012 16:40:10   wp040100
// P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
// 
//    Rev 1.3   Feb 27 2012 20:20:46   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.2   Feb 23 2012 14:39:46   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.1   Feb 22 2012 15:57:54   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.0   Feb 21 2012 15:30:46   wp040100
// Initial revision.
// 
//
//
 * 
 * 
// 
*/
