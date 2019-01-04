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
// ^FILE   : MsgProcess.cpp
// ^CLASS  : MsgProcess
//
//******************************************************************************

#include "stdafx.h"
#include "MsgProcess.hpp"
#include "MsgProcessIncludes.h"
#include <ifastcbo\MsgProcessCBOList.hpp>
#include <ifastcbo\MsgProcessCBO.hpp>
#include <ifastcbo\MsgActivityList.hpp>
#include <ifastcbo\MsgActivity.hpp>
#include <ifastcbo\MsgEventList.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MSG;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MSG;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MsgProcess > processCreator( CMD_BPROC_MSG );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace 
{
   const I_CHAR * const CLASSNAME = I_( "MsgProcess" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************
MsgProcess::MsgProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_rpChildGI( NULL  ), m_pMsgProcessList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MSG_PROCESS_LIST, true, BF::NullContainerId, true, I_("MsgProcessList") );
   addContainer( IFASTBP_PROC::MSG_ACTIVITY_LIST, true, IFASTBP_PROC::MSG_PROCESS_LIST, true, I_("MsgActivityList") );
   addContainer( IFASTBP_PROC::MSG_EVENT_LIST, true, IFASTBP_PROC::MSG_ACTIVITY_LIST, true, I_("MsgEventList") );

   addSubstituteList( ifds::MsgProcessHeading );
   addSubstituteList( ifds::MsgActivityHeading );
   addSubstituteList( ifds::MsgEventHeading );

   // Process List
   addFieldDetails( ifds::NetworkID, IFASTBP_PROC::MSG_PROCESS_LIST );
   addFieldDetails( ifds::ProcessID, IFASTBP_PROC::MSG_PROCESS_LIST );
   addFieldDetails( ifds::MsgProcessType, IFASTBP_PROC::MSG_PROCESS_LIST );
   addFieldDetails( ifds::MsgProcessStatus, IFASTBP_PROC::MSG_PROCESS_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::MSG_PROCESS_LIST);
   addFieldDetails( ifds::ProcessTime, IFASTBP_PROC::MSG_PROCESS_LIST);
   addFieldDetails( ifds::MsgProcessCategory, IFASTBP_PROC::MSG_PROCESS_LIST);
   addFieldDetails( ifds::FileName, IFASTBP_PROC::MSG_PROCESS_LIST);

   // Activity List
   addFieldDetails( ifds::ProcessID, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( ifds::ActivityID, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( ifds::ActivityType, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( ifds::SendRefNum, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( ifds::MsgDate, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( ifds::MsgTime, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( ifds::ProcessTime, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( ifds::FundBrokerCode, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( ifds::OmnibusID, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( ifds::TransNum, IFASTBP_PROC::MSG_ACTIVITY_LIST );
   addFieldDetails( OVERRIDE1, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( OVERRIDE2, BF::NullContainerId, SUBCLASS_PROCESS );

   // Event List
   addFieldDetails( ifds::EventCode, IFASTBP_PROC::MSG_EVENT_LIST );
   addFieldDetails( ifds::EventType, IFASTBP_PROC::MSG_EVENT_LIST );
   addFieldDetails( ifds::EventText, IFASTBP_PROC::MSG_EVENT_LIST );
}

//******************************************************************************

MsgProcess::~MsgProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MsgProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );

   const BFDataGroupId& idDataGroup = getDataGroupId();

   // Retrieve Parameters
   DString MsgProcessType, MsgProcessStatus, MsgProcessCategory, StartDate, EndDate;
   DString NetworkID, SendRefNum, TransNum, OmnibusID, ActivityID, EnvelopeID, MsgSearchType;
   getParameter( MFCAN_IP_PARAM::PROCESS_TYPE, MsgProcessType );
   getParameter( MFCAN_IP_PARAM::PROCESS_STATUS, MsgProcessStatus );
   getParameter( MFCAN_IP_PARAM::PROCESS_CATEGORY, MsgProcessCategory );
   getParameter( MFCAN_IP_PARAM::START_DATE, StartDate );
   getParameter( MFCAN_IP_PARAM::END_DATE, EndDate );
   getParameter( MFCAN_IP_PARAM::NETWORK_ID, NetworkID );
   getParameter( MFCAN_IP_PARAM::SENDER_REF_NUM, SendRefNum );
   getParameter( MFCAN_IP_PARAM::TRANS_NUM, TransNum );
   getParameter( MFCAN_IP_PARAM::AGGREGATEDORDER, OmnibusID );
   getParameter( MFCAN_IP_PARAM::ACTIVITY_ID, ActivityID );
   getParameter( MFCAN_IP_PARAM::ENVELOPE_ID, EnvelopeID );
   getParameter( MFCAN_IP_PARAM::SEARCH_TYPE, MsgSearchType );
   getParameter( I_("DisableTrade"), DisableTrade );
   getParameter( I_("DisableAggrOrder"), DisableAggrOrder );

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   {
      try
      {
         SEVERITY sevRtn = dstcWorkSession->getMsgProcessList( m_pMsgProcessList, idDataGroup, true,
                           EnvelopeID, TransNum, OmnibusID, ActivityID, SendRefNum, NetworkID, StartDate,
                           EndDate, MsgProcessType, MsgProcessCategory, MsgProcessStatus, MsgSearchType );
         if( sevRtn <= WARNING && m_pMsgProcessList )
         {
            setContainer( IFASTBP_PROC::MSG_PROCESS_LIST, m_pMsgProcessList );      
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

bool MsgProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_MSG );
}

//******************************************************************************

bool MsgProcess::doModelessSetFocus( GenericInterface *rpGICaller )
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

E_COMMANDRETURN MsgProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      // Set Parameters
      setParameter( I_("DisableTrade"), DisableTrade );
      setParameter( I_("DisableAggrOrder"), DisableAggrOrder );

      rtn = invokeCommand( this, CMD_GUI_MSG, getProcessType(), isModal(), &m_rpChildGI );
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

void* MsgProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {

      if( IFASTBP_PROC::MSG_ACTIVITY_LIST == idContainer )
      {
         {
            MsgProcessCBO *pMsgProcessCBO = dynamic_cast< MsgProcessCBO * >( getCBOItem(IFASTBP_PROC::MSG_PROCESS_LIST, idDataGroup ) );
            MsgActivityList* pMsgActivityList = NULL;
            if( pMsgProcessCBO->getMsgActivityList( pMsgActivityList, idDataGroup ) <= WARNING )
            {
               ptr = pMsgActivityList;
            }
         }
      }
      else if( IFASTBP_PROC::MSG_EVENT_LIST == idContainer )
      {
         {
            MsgActivity *pMsgActivity = dynamic_cast< MsgActivity * >( getCBOItem(IFASTBP_PROC::MSG_ACTIVITY_LIST, idDataGroup ) );
            MsgEventList* pMsgEventList = NULL;
            if( pMsgActivity->getMsgEventList( pMsgEventList, idDataGroup ) <= WARNING )
            {
               ptr = pMsgEventList;
            }
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

bool MsgProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) 
{
/*
   DString dstrMessage( szMessage );
   if( dstrMessage == I_("REFRESH") )
   {
      setContainer( IFASTBP_PROC::FUNDS_LIST, NULL );
      return( true );
   }
*/
   return(false);
}

//******************************************************************************

SEVERITY MsgProcess::performSearch( GenericInterface *rpGI, 
                                                    const BFContainerId& idSearch, 
                                                    E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ) );
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      if( m_pMsgProcessList )
      {
         sevRtn = m_pMsgProcessList->getMore();
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ), 
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return( sevRtn ); 
}

//******************************************************************************

bool MsgProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || m_pMsgProcessList == NULL ? false : 
          m_pMsgProcessList->doMoreRecordsExist());
}

//******************************************************************************

void MsgProcess::doGetField( const GenericInterface *rpGICaller,
                             const BFContainerId& idContainer,
                             const BFFieldId& idField,
                             const BFDataGroupId& idDataGroup,
                             DString &strValueOut,
                             bool bFormatted
                           ) const
{
   if( idField == OVERRIDE1 )
   {
      DString MsgProcessCategory, Type;
      const_cast<MsgProcess*>(this)->getField( rpGICaller, IFASTBP_PROC::MSG_PROCESS_LIST, ifds::MsgProcessCategory, MsgProcessCategory, false );
      Type = MsgProcessCategory.left( 1 );
      if( Type == I_("T") )
      {
         DString AccountNum;
         const_cast<MsgProcess*>(this)->getField( rpGICaller, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::AccountNum, AccountNum, false); 
         AccountNum.stripAll().stripLeading( I_CHAR('0') );
         strValueOut = AccountNum;
      }
      else if( Type == I_("A") )
      {
         DString FundBrokerCode;
         const_cast<MsgProcess*>(this)->getField( rpGICaller, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::FundBrokerCode, FundBrokerCode, false); 
         FundBrokerCode.stripAll();
         strValueOut = FundBrokerCode;
      }
      if( strValueOut.asInteger() == 0 )
      {
         strValueOut = NULL_STRING;
      }
   }
   else if( idField == OVERRIDE2 )
   {
      DString MsgProcessCategory, Type;
      const_cast<MsgProcess*>(this)->getField( rpGICaller, IFASTBP_PROC::MSG_PROCESS_LIST, ifds::MsgProcessCategory, MsgProcessCategory, false );
      Type = MsgProcessCategory.left( 1 );
      if( Type == I_("T") )
      {
         DString TransNum;
         const_cast<MsgProcess*>(this)->getField( rpGICaller, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::TransNum, TransNum, false); 
         TransNum.stripAll().stripLeading( I_CHAR('0') );
         strValueOut = TransNum;
      }
      else if( Type == I_("A") )
      {
         DString OmnibusID;
         const_cast<MsgProcess*>(this)->getField( rpGICaller, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::OmnibusID, OmnibusID, false); 
         OmnibusID.stripAll();
         strValueOut = OmnibusID;
      }
      if( strValueOut.asInteger() == 0 )
      {
         strValueOut = NULL_STRING;
      }
   }
}

// ******************************************************************************
// Revision Control Entries
// ******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/MsgProcess.cpp-arc  $
// 
//    Rev 1.2   Apr 21 2005 11:15:14   hernando
// Incident #278666 - Added OVERRIDE2 and revised OVERRIDE1.
// 
//    Rev 1.1   Feb 22 2005 14:48:38   hernando
// PET1117 FN66-68 - Added DisableTrade and DisableAggrOrder parameters.
// 
//    Rev 1.0   Feb 21 2005 11:09:06   hernando
// Initial revision.
