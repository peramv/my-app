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
//    Copyright 2004 by IFDS.
//
//******************************************************************************
//
// ^FILE   : BrokerRemarkProcess.cpp
// ^AUTHOR : Yingbao   Li
// ^DATE   : Sept. 10, 2004
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BrokerRemarkProcess
//    This class manages the Broker information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "BrokerRemarkProcess.hpp"
#include "BrokerRemarkProcessincludes.h"
#include <ifastcbo\BrokerRemarkList.hpp>
#include <ifastcbo\RemarkContainer.hpp>





extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BROKER_REMARK;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< BrokerRemarkProcess > processCreator(CMD_BPROC_BROKER_REMARK);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("BrokerRemarkProcess");
   const I_CHAR * const PERFORMSEARCH = I_("performSearch");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long ERR_BROKER_LIST_EMPTY;
   extern const long ERR_BROKER_NAME_EMPTY;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

BrokerRemarkProcess::BrokerRemarkProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand), 
_rpChildGI(0) 

{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   addContainer(IFASTBP_PROC::BROKER_REMARK_LIST, true,BF::NullContainerId,true,I_("BrokerRemarkList"));
   addContainer(IFASTBP_PROC::BRANCH_REMARK_LIST, true,BF::NullContainerId,true,I_("BranchRemarkList"));
   addContainer(IFASTBP_PROC::AGENT_REMARK_LIST,  true,BF::NullContainerId,true,I_("AgentRemarkList"));  	
	addFieldDetails(ifds::BrokerCode,		IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::BranchCode,		IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::AgentCode,			IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::EffectiveDate,	IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::Remark1,			IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::Remark2,			IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::Remark3,			IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::Remark4,			IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::Remark5,			IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::Remark6,			IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::Remark7,			IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::Remark8,			IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::Remark9,			IFASTBP_PROC::BROKER_REMARK_LIST);
   addFieldDetails(ifds::Remark10,			IFASTBP_PROC::BROKER_REMARK_LIST);
	addFieldDetails(ifds::BrokerCode,		IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::BranchCode,		IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::AgentCode,			IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::EffectiveDate,	IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::Remark1,			IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::Remark2,			IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::Remark3,			IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::Remark4,			IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::Remark5,			IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::Remark6,			IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::Remark7,			IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::Remark8,			IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::Remark9,			IFASTBP_PROC::BRANCH_REMARK_LIST);
   addFieldDetails(ifds::Remark10,			IFASTBP_PROC::BRANCH_REMARK_LIST);
	addFieldDetails(ifds::BrokerCode,		IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::BranchCode,		IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::AgentCode,			IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::EffectiveDate,	IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::Remark1,			IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::Remark2,			IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::Remark3,			IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::Remark4,			IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::Remark5,			IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::Remark6,			IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::Remark7,			IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::Remark8,			IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::Remark9,			IFASTBP_PROC::AGENT_REMARK_LIST);
   addFieldDetails(ifds::Remark10,			IFASTBP_PROC::AGENT_REMARK_LIST);

}

//******************************************************************************
BrokerRemarkProcess::~BrokerRemarkProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);



}

//******************************************************************************
SEVERITY BrokerRemarkProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);
	DString brokeCode,branchCode,agentCode,asdate;
   getParameter(I_("BrokerCode"), brokeCode);
   getParameter(I_("BranchCode"), branchCode);
   getParameter(I_("AgentCode"),  agentCode);
   getParameter(I_("AsDate"), asdate);
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	if(dstcWorkSession)
	{
		RemarkContainer* pRemarkContainer = NULL;
		dstcWorkSession->getRemarkContainer(pRemarkContainer,
			brokeCode,branchCode,agentCode,asdate,getDataGroupId() );
		if(pRemarkContainer)
		{
			   BrokerRemarkList* pRemarklist = NULL;
				pRemarkContainer->getBrokerRemarkList(pRemarklist,getDataGroupId(),0 );
				setContainer( IFASTBP_PROC::BROKER_REMARK_LIST, pRemarklist );
				pRemarklist = NULL;
				pRemarkContainer->getBrokerRemarkList(pRemarklist,getDataGroupId(),1 );
				setContainer( IFASTBP_PROC::BRANCH_REMARK_LIST, pRemarklist );
				if( agentCode.strip() != NULL_STRING )
				{
					pRemarklist = NULL;
					pRemarkContainer->getBrokerRemarkList(pRemarklist,getDataGroupId(),2 );
					setContainer( IFASTBP_PROC::AGENT_REMARK_LIST, pRemarklist );
				}				
		}	
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool BrokerRemarkProcess::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{
   return false;
}

//******************************************************************************
E_COMMANDRETURN BrokerRemarkProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_MODELESS_INPROCESS;

   return rtn;
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrokerRemarkProcess.cpp-arc  $
// 
//    Rev 1.1   Oct 04 2004 10:17:36   YINGBAOL
// PET1145: FN1  BranchCode can be blank for SalesRep 
// 
//    Rev 1.0   Sep 24 2004 14:49:34   YINGBAOL
// Initial revision.
 * 
  
*/ 
