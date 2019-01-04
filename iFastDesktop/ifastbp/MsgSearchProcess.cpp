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
//    Copyright 2005 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : MsgSearchProcess.cpp
// ^CLASS  : MsgSearchProcess
//
//******************************************************************************

#include "stdafx.h"
#include "MsgSearchProcess.hpp"
#include "MsgSearchProcessincludes.h"
#include <bfproc\genericinterfacecontainer.hpp>
#include <ifastcbo\MsgSearchCriteria.hpp>
#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MSG;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MSG_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MSG_SEARCH;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MsgSearchProcess > processCreator(CMD_BPROC_MSG_SEARCH);

namespace 
{
   const I_CHAR * const CLASSNAME = I_("MsgSearchProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

MsgSearchProcess::MsgSearchProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand),  
_rpChildGI(NULL), 
_pMsgSearchCriteria (NULL),
_searchType (NULL_STRING),
_backgroundSearch (I_("N"))
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   addContainer(IFASTBP_PROC::SEARCH_CRITERIA_FILLER, false, BF::NullContainerId, true);

   addFieldDetails(ifds::MsgSearchType, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::MsgProcessType, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::MsgProcessStatus, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::MsgProcessCategory, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::StartDate, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::EndDate, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::NetworkID, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SendRefNum, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::TransNum, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::OmnibusID, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::ActivityID, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchUsing, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
}

//******************************************************************************

MsgSearchProcess::~MsgSearchProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;
   if (_pMsgSearchCriteria)
   {
      delete _pMsgSearchCriteria;
      _pMsgSearchCriteria = NULL;
   }
}

//************************************************************************************

SEVERITY MsgSearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      getParameter (MFCAN_IP_PARAM::SEARCH_TYPE, _searchType);
      if( _searchType.empty() )
      {
         _searchType = MSG_SEARCH_TYPE::ACTIVITYID;   // Used for default
      }
      _pMsgSearchCriteria = new MsgSearchCriteria( *pDSTCWorkSession );
      if( _pMsgSearchCriteria->init( _searchType, BF::HOST ) <= WARNING )
      {
         setContainer( IFASTBP_PROC::SEARCH_CRITERIA_FILLER, _pMsgSearchCriteria );
      }
   }
   catch (ConditionException& ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

E_COMMANDRETURN MsgSearchProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_MSG_SEARCH, PROC_NO_TYPE, isModal(), &_rpChildGI );
   }
   catch(ConditionException &ce)
   {
      assert(0);
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************

bool MsgSearchProcess::doModelessChildComplete(const Command &cmd)
{
   return( cmd.getKey() == CMD_GUI_MSG_SEARCH );
}

//******************************************************************************

SEVERITY MsgSearchProcess::performSearch (GenericInterface *rpGI, 
   const BFContainerId &idSearch, E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));

   try
   {
      const BFDataGroupId &idDataGroup = getDataGroupId();
      E_COMMANDRETURN rtn = CMD_FAILURE;

      if( eSearchAction == SEARCH_START )
      {
         if( _pMsgSearchCriteria->validateAll( idDataGroup ) <= WARNING )
         {
            DString MsgProcessType, StartDate, EndDate, MsgProcessStatus;
            DString NetworkID, SendRefNum, TransNum, OmnibusID, ActivityID;
            DString MsgProcessCategory, MsgSearchType;

            getField( this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::MsgSearchType, MsgSearchType, false );
            getField( this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::MsgProcessType, MsgProcessType, false );
            getField( this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::StartDate, StartDate, false );
            getField( this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::EndDate, EndDate, false );
            getField( this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::MsgProcessStatus, MsgProcessStatus, false );
            getField( this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::NetworkID, NetworkID, false );
            getField( this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::SendRefNum, SendRefNum, false );
            getField( this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::TransNum, TransNum, false );
            getField( this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::OmnibusID, OmnibusID, false );
            getField( this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::ActivityID, ActivityID, false );
            getField( this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::MsgProcessCategory, MsgProcessCategory, false );

            setParameter( MFCAN_IP_PARAM::SEARCH_TYPE, MsgSearchType );

            if( MsgSearchType == MSG_SEARCH_TYPE::PROCESSTYPE )
            {
               setParameter( MFCAN_IP_PARAM::PROCESS_TYPE, MsgProcessType );
               setParameter( MFCAN_IP_PARAM::START_DATE, StartDate );
               setParameter( MFCAN_IP_PARAM::END_DATE, EndDate );
               setParameter( MFCAN_IP_PARAM::PROCESS_STATUS, MsgProcessStatus );
               setParameter( MFCAN_IP_PARAM::NETWORK_ID, NetworkID );
            }
            else if( MsgSearchType == MSG_SEARCH_TYPE::NETWORKID )
            {
               setParameter( MFCAN_IP_PARAM::START_DATE, StartDate );
               setParameter( MFCAN_IP_PARAM::END_DATE, EndDate );
               setParameter( MFCAN_IP_PARAM::NETWORK_ID, NetworkID );
            }
            else if( MsgSearchType == MSG_SEARCH_TYPE::SENDERREFNUM )
            {
               setParameter( MFCAN_IP_PARAM::SENDER_REF_NUM, SendRefNum );
               setParameter( MFCAN_IP_PARAM::NETWORK_ID, NetworkID );
            }
            else if( MsgSearchType == MSG_SEARCH_TYPE::TRANSNUMBER )
            {
               setParameter( MFCAN_IP_PARAM::TRANS_NUM, TransNum );
            }
            else if( MsgSearchType == MSG_SEARCH_TYPE::AGGRORDNUM )
            {
               setParameter( MFCAN_IP_PARAM::AGGREGATEDORDER, OmnibusID );
            }
            else if( MsgSearchType == MSG_SEARCH_TYPE::ACTIVITYID )
            {
               setParameter( MFCAN_IP_PARAM::ACTIVITY_ID, ActivityID );
            }
            else if( MsgSearchType == MSG_SEARCH_TYPE::PROCESSCATEGORY )
            {
               setParameter( MFCAN_IP_PARAM::PROCESS_CATEGORY, MsgProcessCategory );
               setParameter( MFCAN_IP_PARAM::START_DATE, StartDate );
               setParameter( MFCAN_IP_PARAM::END_DATE, EndDate );
               setParameter( MFCAN_IP_PARAM::PROCESS_STATUS, MsgProcessStatus );
               setParameter( MFCAN_IP_PARAM::NETWORK_ID, NetworkID );
            }
            rtn = invokeCommand(this, CMD_BPROC_MSG, getProcessType(), true /*Modal*/, NULL);
            if( rtn == CMD_OK )
            {
               rpGI->send( this, I_("CLOSE") );
            }
         }
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, 
         I_("performSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/MsgSearchProcess.cpp-arc  $
// 
//    Rev 1.1   Feb 24 2005 16:27:58   hernando
// PET1117 FN66-68 - Changed default Search Type.  Handle the Close button from the Msg Search Dialog.
// 
//    Rev 1.0   Feb 21 2005 11:09:18   hernando
// Initial revision.
