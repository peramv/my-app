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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AlertMessagesProcess.cpp
// ^AUTHOR : 
// ^DATE   : 04 April 2016
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AlertMessagesProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "AlertMessagesProcess.hpp"
#include "AlertMessagesProcessIncludes.h"
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\MFAccountList.hpp>
#include <ifastcbo\Shareholder.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ALERT_MESSAGES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ALERT_MESSAGES;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator<AlertMessagesProcess> processCreator(CMD_BPROC_ALERT_MESSAGES);

namespace 
{
	const I_CHAR * const CLASSNAME = I_("AlertMessagesProcess");
}

namespace CND
{
    extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{   
    extern CLASS_IMPORT const BFTextFieldId AlertCode;
    extern CLASS_IMPORT const BFTextFieldId AlertSource;
    extern CLASS_IMPORT const BFNumericFieldId AccountNum;
    extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

namespace ALERT_MSG_PARAM
{
    extern CLASS_EXPORT I_CHAR * const ACCOUNT_NUM = I_("AccountNum");
    extern CLASS_EXPORT I_CHAR * const FROM_SCREEN = I_("FromScreen");
    extern CLASS_EXPORT I_CHAR * const SHAREHOLDER_NUM = I_("ShareNum");
}

namespace ALERT_MSG_OPENED_FROM
{
    extern CLASS_EXPORT I_CHAR * const TRADE          = I_("Trade");
    extern CLASS_EXPORT I_CHAR * const ACCT_DETL      = I_("AccountDetails");
}


//****************************************************************
AlertMessagesProcess::AlertMessagesProcess(GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand),
  _rpChildGI(NULL)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

    addContainer(IFASTBP_PROC::MFACCOUNT_CBO, false );
	addContainer(IFASTBP_PROC::ALERT_MESSAGE_LIST, true, IFASTBP_PROC::MFACCOUNT_CBO);

    addFieldDetails(ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO);
    addFieldDetails(ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO);

	addFieldDetails(ifds::AlertCode, IFASTBP_PROC::ALERT_MESSAGE_LIST);
    addFieldDetails(ifds::AlertSource, IFASTBP_PROC::ALERT_MESSAGE_LIST);
}


//****************************************************************
AlertMessagesProcess::~AlertMessagesProcess()
{
	TRACE_DESTRUCTOR(CLASSNAME)
}


//****************************************************************
SEVERITY AlertMessagesProcess::doInit()
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
	SEVERITY sevRtn = SEVERE_ERROR;

	try
	{
        getParent()->getParameter(ALERT_MSG_PARAM::ACCOUNT_NUM, _accountNum);
        getParent()->getParameter(ALERT_MSG_PARAM::FROM_SCREEN, _fromScreen);
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
	}
	return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************************
E_COMMANDRETURN AlertMessagesProcess::doProcess()
{  
	MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
	E_COMMANDRETURN rtn = CMD_FAILURE;

	try
	{
		if( isXMLAPIContext() )
		{
			rtn = CMD_MODELESS_INPROCESS;
		}
		else
		{
			//getParent()->setParameter(ACCOUNT_NUMBER, _dstrAccountNum);
			rtn = invokeCommand(this, CMD_GUI_ALERT_MESSAGES, getProcessType(), isModal(), &_rpChildGI);
		}
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return(rtn);
}


//****************************************************************
bool AlertMessagesProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
	SEVERITY sevRtn = SEVERE_ERROR;

	bool bRtn = false;
	try
	{
		assert(_rpChildGI && isValidModelessInterface(_rpChildGI));

		if (isValidModelessInterface(_rpChildGI))
		{  
			setContainer(IFASTBP_PROC::ALERT_MESSAGE_LIST, NULL);

			bRtn = _rpChildGI->refresh(this, NULL);
			bRtn = _rpChildGI->modelessSetFocus(rpGICaller);
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

	return(bRtn);
}


//****************************************************************
bool AlertMessagesProcess::doModelessChildComplete( const Command &cmd )
{
	return cmd.getKey() == CMD_GUI_ALERT_MESSAGES;
}


//****************************************************************
bool AlertMessagesProcess::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
	TRACE_METHOD(CLASSNAME, DOREFRESH);
	//setParameter(ACCOUNT_NUMBER, _dstrAccountNum );

	return _rpChildGI->refresh(this, NULL);
}


//****************************************************************
void AlertMessagesProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
	//setParameter(ACCOUNT_NUMBER, _dstrAccountNum);
}


////****************************************************************
bool AlertMessagesProcess::doOk(GenericInterface *rpGICaller)
{
   SEVERITY sevReturn = NO_CONDITION;

   return sevReturn == NO_CONDITION;
}

//****************************************************************
void *AlertMessagesProcess::getPtrForContainer(const BFContainerId& idContainer,
											const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));

	void *ptr = NULL;
	SEVERITY sevRtn = SEVERE_ERROR;

	DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	try
	{  
        if (idContainer == IFASTBP_PROC::MFACCOUNT_CBO)
        {
            MFAccount *pMFAccount = NULL;
            DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

            if (dstcWorkSession->getMFAccount(getDataGroupId(), _accountNum, pMFAccount) <= WARNING && pMFAccount)
            {
                ptr = pMFAccount;
            }
        }
        else if (idContainer == IFASTBP_PROC::ALERT_MESSAGE_LIST)
		{
            
            AlertMessageList *pAlertMessageList = NULL;
            MFAccount *pMFAccount = NULL;

            pMFAccount = dynamic_cast<MFAccount*>(getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId()));

            if (pMFAccount->getAlertMessageList(_fromScreen, pAlertMessageList, getDataGroupId()) <= WARNING && pAlertMessageList)
			{
				ptr = pAlertMessageList;
			}
		}
	}
	catch (ConditionException &)
	{
		throw;
	}
	catch (...)
	{
		assert(0);
		THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
			CND::BP_ERR_UNKNOWN_EXCEPTION);
	}

	return ptr;
}