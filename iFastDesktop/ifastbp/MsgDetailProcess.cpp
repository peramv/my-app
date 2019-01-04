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
// ^FILE   : MsgDetailProcess.cpp
// ^CLASS  : MsgDetailProcess
//
//******************************************************************************

#include "stdafx.h"
#include "MsgDetailProcess.hpp"
#include "MsgDetailProcessincludes.h"
#include <ifastcbo\MsgDetailList.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MSG_DETAIL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MSG_DETAIL;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MsgDetailProcess > processCreator( CMD_BPROC_MSG_DETAIL );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace 
{
   const I_CHAR * const CLASSNAME = I_( "MsgDetailProcess" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************
MsgDetailProcess::MsgDetailProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  m_rpChildGI( NULL  )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   addContainer( IFASTBP_PROC::MSG_DETAIL_LIST, true, BF::NullContainerId, true, I_("MsgDetailList") );
   addSubstituteList( ifds::MsgDetailHeading );

   addFieldDetails( ifds::MsgID, IFASTBP_PROC::MSG_DETAIL_LIST );
   addFieldDetails( ifds::MsgType, IFASTBP_PROC::MSG_DETAIL_LIST );
   addFieldDetails( ifds::MsgSegment, IFASTBP_PROC::MSG_DETAIL_LIST );
   addFieldDetails( ifds::MsgData, IFASTBP_PROC::MSG_DETAIL_LIST );
}

//******************************************************************************

MsgDetailProcess::~MsgDetailProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MsgDetailProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );

   // Get Parameters
   DString ActivityID;
   getParameter( MFCAN_IP_PARAM::ACTIVITY_ID, ActivityID );

   const BFDataGroupId& idDataGroup = getDataGroupId();

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   {
      try
      {
         MsgDetailList *pMsgDetailList = NULL;
         SEVERITY sevRtn = dstcWorkSession->getMsgDetailList( pMsgDetailList, idDataGroup, true, ActivityID );
         if( sevRtn <= WARNING && pMsgDetailList )
         {
            setContainer( IFASTBP_PROC::MSG_DETAIL_LIST, pMsgDetailList );      
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

bool MsgDetailProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_MSG_DETAIL );
}

//******************************************************************************

bool MsgDetailProcess::doModelessSetFocus( GenericInterface *rpGICaller )
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

E_COMMANDRETURN MsgDetailProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_MSG_DETAIL, getProcessType(), isModal(), &m_rpChildGI );
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

// ******************************************************************************
// Revision Control Entries
// ******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/MsgDetailProcess.cpp-arc  $
// 
//    Rev 1.0   Feb 21 2005 11:08:34   hernando
// Initial revision.
