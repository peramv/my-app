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
// ^FILE   : AcctCutOffTimesProcess.cpp
// ^CLASS  : AcctCutOffTimesProcess
//
//******************************************************************************

#include "stdafx.h"
#include "AcctCutOffTimesProcess.hpp"
#include "AcctCutOffTimesProcessIncludes.h"
#include <ifastcbo\AcctCutOffTimesList.hpp>
#include <ifastcbo\AcctCutOffTimes.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\MFAccount.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\entity.hpp>
#include "confirmationprocessincludes.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCT_LVL_CUT_OFF_TIMES;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator<AcctCutOffTimesProcess> processCreator(CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES);

namespace CND
{
	extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace 
{
	const I_CHAR * const CLASSNAME = I_("AcctCutOffTimesProcess");
	const I_CHAR * const PERFORMSEARCH = I_("performSearch");
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId CutOffLevel;
	extern CLASS_IMPORT const BFTextFieldId BrokerCode;
}

namespace AUDITTYPE
{
	extern CLASS_IMPORT I_CHAR * const CUTOFF;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AcctCutOffTimesProcess::AcctCutOffTimesProcess(GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand)
, m_rpChildGI(NULL), m_pCutOffTimesList(NULL), m_dstrAccountNumber(NULL_STRING)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

	addContainer(IFASTBP_PROC::CUT_OFF_TIMES_LIST, true, BF::NullContainerId, true, I_("AcctCutOffTimesProcessList"));
	addContainer(IFASTBP_PROC::MFACCOUNT, false, BF::NullContainerId, false, I_("MFAccount"));
	
	// Process List
	addFieldDetails(ifds::CutOffTime, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
	addFieldDetails(ifds::CutOffTimeType, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
	addFieldDetails(ifds::FundGroup, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
	addFieldDetails(ifds::TimeZoneCode, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
	addFieldDetails(ifds::FundCode, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
	addFieldDetails(ifds::FundNumber, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
	addFieldDetails(ifds::ClassCode, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
	addFieldDetails(ifds::CutOffDays, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
	addFieldDetails(ifds::CutOffLevel, IFASTBP_PROC::CUT_OFF_TIMES_LIST);

	// Admin/Date fields
	addFieldDetails(ifds::ModDate, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
	addFieldDetails(ifds::ModUser, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
	addFieldDetails(ifds::ProcessDate, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
	addFieldDetails(ifds::Username, IFASTBP_PROC::CUT_OFF_TIMES_LIST);

	// For the Caption
	addFieldDetails(ifds::AccountNum, IFASTBP_PROC::MFACCOUNT);

	// For Broker Code
	addFieldDetails(ifds::BrokerCode, BF::NullContainerId, SUBCLASS_PROCESS); 
	addFieldDetails(ifds::BrokerContainerValid, BF::NullContainerId, SUBCLASS_PROCESS); 

	// For Historical
	addFieldDetails(ifds::RecId, IFASTBP_PROC::CUT_OFF_TIMES_LIST);
}

//******************************************************************************

AcctCutOffTimesProcess::~AcctCutOffTimesProcess()
{
	TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************

SEVERITY AcctCutOffTimesProcess::doInit()
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doInit"));
	
	// Get Parameter
	getParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNumber);
	getParameter(I_("EntityId"), m_dstrEntityId);
	getParameter(I_("BrokerLevel"), m_dstrBrokerLevel);

	const BFDataGroupId& idDataGroup = getDataGroupId();
	
	DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	{
		try
		{
			if(m_dstrAccountNumber != NULL_STRING && !m_dstrAccountNumber.empty())
			{
				MFAccount *pMFAccount;
				if(dstcWorkSession->getMFAccount(idDataGroup, m_dstrAccountNumber, pMFAccount) <= WARNING && NULL != pMFAccount)
				{
					if(pMFAccount->getAcctCutOffTimesList(m_pCutOffTimesList, idDataGroup) <= WARNING && NULL != m_pCutOffTimesList)
					{
						setContainer(IFASTBP_PROC::CUT_OFF_TIMES_LIST, m_pCutOffTimesList);      
					}
				}
			}
			else if(m_dstrEntityId != NULL_STRING && !m_dstrEntityId.empty())
			{
				Entity *pEntity = NULL;
				if(dstcWorkSession->getEntity(idDataGroup, m_dstrEntityId, pEntity) && NULL != pEntity)
				{
					if(pEntity->getNetworkSenderCutOffTimesList (m_pCutOffTimesList, idDataGroup) <= WARNING && m_pCutOffTimesList != NULL)
					{	
						setContainer(IFASTBP_PROC::CUT_OFF_TIMES_LIST, m_pCutOffTimesList);      
					}
				}
			}
		}
		catch(ConditionException &ce)
		{
			SETCONDITIONFROMEXCEPTION(ce);
		}
		catch(...)
		{
			assert(0);
			THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,CND::BP_ERR_UNKNOWN_EXCEPTION);
		}
	}
	
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool AcctCutOffTimesProcess::doModelessChildComplete(const Command &cmd)
{
	return(cmd.getKey() == CMD_GUI_ACCT_LVL_CUT_OFF_TIMES);
}

//******************************************************************************

bool AcctCutOffTimesProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus"));
	
	bool bRtn = false;
	
	try
	{
		assert(m_rpChildGI);
		if(isValidModelessInterface(m_rpChildGI))
		{
			bRtn = m_rpChildGI->refresh(this, NULL);
			bRtn = m_rpChildGI->modelessSetFocus(rpGICaller);
		}
	}
	catch(ConditionException &ce)
	{
		SETCONDITIONFROMEXCEPTION(ce);
	}
	catch(...)
	{
		assert(0);
		THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS, CND::BP_ERR_UNKNOWN_EXCEPTION);
	}
	
	return(bRtn);
}

//******************************************************************************

E_COMMANDRETURN AcctCutOffTimesProcess::doProcess()
{
	MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
	E_COMMANDRETURN rtn = CMD_FAILURE;
	
	try
	{
		setParameter(I_("EntityId"), m_dstrEntityId);
		setParameter(I_("BrokerLevel"), m_dstrBrokerLevel);

		rtn = invokeCommand(this, CMD_GUI_ACCT_LVL_CUT_OFF_TIMES, getProcessType(), isModal(), &m_rpChildGI);
	}
	catch(ConditionException &ce)
	{
		assert(0);
		SETCONDITIONFROMEXCEPTION(ce);
	}
	catch(...)
	{
		assert(0);
		THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION);
	}

	return(rtn);
}

//******************************************************************************

void* AcctCutOffTimesProcess::getPtrForContainer(const BFContainerId& idContainer, const BFDataGroupId& idDataGroup)
{
	void *ptr = NULL;
	DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	try
	{

		if(IFASTBP_PROC::MFACCOUNT == idContainer)
		{
			{
				MFAccount *pMFAccount = NULL;
				if(dstcWorkSession->getMFAccount(getDataGroupId(), m_dstrAccountNumber, pMFAccount) 
					<= WARNING && pMFAccount)
					ptr = pMFAccount;
			}
		}
		else if(IFASTBP_PROC::CUT_OFF_TIMES_LIST == idContainer)
		{
			//AcctCutOffTimesList *pBrokerCutOff = NULL;
			if(dstcWorkSession->getBrokerCutOff(m_dstrBrokerCode, m_pCutOffTimesList, BF::HOST) <= WARNING && m_pCutOffTimesList)
			{
				ptr = m_pCutOffTimesList;
			}
		}
	}
	catch(ConditionException &)
	{
		throw;
	}
	catch(...)
	{
		assert(0);
		THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
	}
	return(ptr);
}

//******************************************************************************

bool AcctCutOffTimesProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) 
{
	DString dstrMessage (szMessage);
	if (dstrMessage == I_("RESET_SEARCH"))
	{
		getCBOList(IFASTBP_PROC::CUT_OFF_TIMES_LIST, getDataGroupId())->clearUpdatedFlags(getDataGroupId(), true);
		setContainer(IFASTBP_PROC::CUT_OFF_TIMES_LIST, NULL);
	}

	return(false);
}

//******************************************************************************

bool AcctCutOffTimesProcess::doMoreRecordsExist(GenericInterface *rpGICaller, const BFContainerId& idSearch)
{
	return(rpGICaller == NULL || m_pCutOffTimesList == NULL ? false : 
          m_pCutOffTimesList->doMoreRecordsExist());
}

//******************************************************************************

void AcctCutOffTimesProcess::doGetField(const GenericInterface *rpGICaller,
                             const BFContainerId& idContainer,
                             const BFFieldId& idField,
                             const BFDataGroupId& idDataGroup,
                             DString &strValueOut,
                             bool bFormatted) const
{
	if(idContainer == BF::NullContainerId)
	{
		if(idField == ifds::BrokerCode)
		{
			strValueOut = m_dstrBrokerCode;
		}
		else if (idField == ifds::BrokerContainerValid)
		{
			strValueOut = ((const_cast<AcctCutOffTimesProcess*>(this))->isContainerValid(IFASTBP_PROC::CUT_OFF_TIMES_LIST) && m_dstrBrokerLevel == I_("Y")) ? I_("Y"):I_("N");
		}
	}
}

//******************************************************************************

SEVERITY AcctCutOffTimesProcess::doSetField (const GenericInterface *rpGICaller,
										 const BFContainerId& idContainer,
										 const BFFieldId& idField,
										 const BFDataGroupId& idDataGroup, 
										 const DString& strValue,
										 bool bFormatted)
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD);
	if(idContainer == BF::NullContainerId)
	{
		if(idField == ifds::BrokerCode)
		{
			setContainer(IFASTBP_PROC::CUT_OFF_TIMES_LIST, NULL);
			m_dstrBrokerCode = strValue;
		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

bool AcctCutOffTimesProcess::doOk(GenericInterface *rpGICaller)
{
	if(m_dstrBrokerLevel == I_("Y"))
	{
		setParameter(CONFPROC::PARM_CALLED_FROM, I_("BrokerCutOff"));
	}

	MFAccount *pMFAccount = NULL;   
	const BFDataGroupId& idDataGroup = getDataGroupId();
	DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	
	if(m_dstrAccountNumber != NULL_STRING && !m_dstrAccountNumber.empty())
	{
		if(dstcWorkSession->getMFAccount(idDataGroup, m_dstrAccountNumber, pMFAccount) <= WARNING)
		{
			AcctCutOffTimesList *pAcctCutOffTimesList = NULL;
			if(pMFAccount->getAcctCutOffTimesList(pAcctCutOffTimesList, idDataGroup) <= WARNING)
			{
				if(pAcctCutOffTimesList && pAcctCutOffTimesList->isUpdatedForDataGroup(getDataGroupId()))
					pMFAccount->refreshMe(true);
			}
		}
	}

	return(true);
}
//******************************************************************************
SEVERITY AcctCutOffTimesProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH);
	SEVERITY sevRtn = SEVERE_ERROR;

	try
	{
		if(m_pCutOffTimesList != NULL)
		{
			sevRtn = m_pCutOffTimesList->getMore();
			setContainer(IFASTBP_PROC::CUT_OFF_TIMES_LIST, NULL);
			setContainer(IFASTBP_PROC::CUT_OFF_TIMES_LIST, m_pCutOffTimesList);
		}
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION(ce);
	}
	catch(...)
	{
		assert(0);
		THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION);
	}
	return(sevRtn); 
}

//******************************************************************************

SEVERITY AcctCutOffTimesProcess::getHistoricalParameters(const BFContainerId &idContainer, BFFieldId &recordIdField, DString &tableId, DString &dstrKeys) 
{

	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   
	if(idContainer == IFASTBP_PROC::CUT_OFF_TIMES_LIST)
	{
		recordIdField = ifds::RecId;
		tableId = AUDITTYPE::CUTOFF;
		dstrKeys = NULL_STRING;
	}
	else 
	{
		assert(0);
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY AcctCutOffTimesProcess::getHistoricalParameters(const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical)
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

	return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/AcctCutOffTimesProcess.cpp-arc  $
// 
//    Rev 1.2   Jul 25 2006 15:57:46   jankovii
// PET 2192 FN02 - Dealings Sender Cut Off Time.
// 
//    Rev 1.1   Jul 21 2006 14:04:52   jankovii
// PET 2192 FN02 - Dealings-Sender Cut-Off Time.
// 
//    Rev 1.0   Jul 05 2005 17:39:42   hernando
// Initial revision.
