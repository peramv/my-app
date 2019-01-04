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
// ^FILE   : JBrokerListProcess.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 18/02/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BrokerListProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <time.h>
#include "jbrokerlistprocess.hpp"
#include <ifastdataimpl\dse_dstc0090_req.hpp>
#include "jbrokerlistprocessincludes.h"
#include <ifastcbo\jbrokerlist.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_JBROKERLIST;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< BrokerListProcess > processCreator( CMD_BPROC_JBROKERLIST );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "BrokerListProcess" );
   const I_CHAR *pBROKERCODE = I_( "BrokerCode" );
   const I_CHAR *pBROKERNAME = I_( "BrokerName" );
   const I_CHAR *pREQUESTTYPE = I_( "RequestType" );
   const I_CHAR *BROKERLIST = I_( "BrokerList" );
}

namespace BROKERLISTLIT  //stands for account details literals
{
   const I_CHAR * const BROKERCODE = I_( "BrokerCode" );  
   const I_CHAR * const BROKERNAME = I_( "BrokerName" );  
   const I_CHAR * const REQUESTTYPE= I_( "RequestType" ); 
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319BrokerListProcess::BrokerListProcess() : 
BrokerListProcess::BrokerListProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pJBrokerList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::BROKER_LIST, true, BF::NullContainerId,true,BROKERLIST   );

   addFieldDetails( ifds::BrokerCode, IFASTBP_PROC::BROKER_LIST );
   addFieldDetails( ifds::BrokerName, IFASTBP_PROC::BROKER_LIST );
   addFieldDetails( ifds::BrokerType, IFASTBP_PROC::BROKER_LIST );
   addFieldDetails( ifds::BrokerTypeDesc, IFASTBP_PROC::BROKER_LIST );
   addFieldDetails( ifds::AddrLine1, IFASTBP_PROC::BROKER_LIST );
   addFieldDetails( ifds::AddrLine2, IFASTBP_PROC::BROKER_LIST );
   addFieldDetails( ifds::AddrLine3, IFASTBP_PROC::BROKER_LIST );
   addFieldDetails( ifds::AddrLine4, IFASTBP_PROC::BROKER_LIST );
   addFieldDetails( ifds::AddrLine5, IFASTBP_PROC::BROKER_LIST );
   addFieldDetails( ifds::AddrCntryCode, IFASTBP_PROC::BROKER_LIST );
   addFieldDetails( ifds::PhoneNumber, IFASTBP_PROC::BROKER_LIST );
}

//******************************************************************************

BrokerListProcess::~BrokerListProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pJBrokerList;
   _rpChildGI = NULL;
}

bool BrokerListProcess::doGetData(
                                 GenericInterface * ,
                                 BFData * 
                                 ) const
{
   _pJBrokerList->getMore();
   BrokerListProcess * _pAbsPr = const_cast < BrokerListProcess * >(this);
   _pAbsPr->setContainer( IFASTBP_PROC::BROKER_LIST, NULL );
   _pAbsPr->setContainer( IFASTBP_PROC::BROKER_LIST, _pJBrokerList );
   return(true);
}

bool BrokerListProcess::doMoreRecordsExist(
                                          GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer 
                                          )
{
   return( _pJBrokerList->doMoreRecordsExist() );
}



//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY BrokerListProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   DString _BrokerCode,_BrokerName,_RequestType;
   try
   {
      getParameter( pBROKERCODE, _BrokerCode );
      getParameter( pBROKERNAME, _BrokerName );
      getParameter( pREQUESTTYPE, _RequestType );
      if( _BrokerCode==I_("") ) _RequestType = I_("l");
      else _RequestType = I_("s");

      _pJBrokerList = new JBrokerList( *getBFWorkSession() );

      sevRtn = _pJBrokerList->init( _BrokerCode, _BrokerName, _RequestType);

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::BROKER_LIST, _pJBrokerList );
      }

   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

//******************************************************************************

E_COMMANDRETURN BrokerListProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JBrokerListProcess.cpp-arc  $
 * 
 *    Rev 1.13   Mar 21 2003 17:43:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Mar 07 2003 11:56:32   PURDYECH
 * Documentation cleanup
 * 
 *    Rev 1.11   Oct 09 2002 23:53:24   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 16:45:02   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.9   Aug 29 2002 12:54:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:24:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   27 Mar 2002 19:55:12   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.6   03 May 2001 14:05:30   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Mar 26 2001 21:59:52   YINGBAOL
 * xml support
 * 
 *    Rev 1.4   Jan 23 2001 15:17:44   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.3   15 Dec 2000 12:43:36   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.2   Mar 30 2000 15:47:04   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:54   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.2   Mar 10 2000 09:56:58   FENGYONG
// For Nextkey
// 
//    Rev 1.1   Mar 08 2000 14:50:34   FENGYONG
// Add Fileds
// 
//    Rev 1.0   Feb 25 2000 16:17:38   FENGYONG
// Initial revision.
// 
//    Rev 1.0   Nov 24 1999 09:21:36   FENGYONG
// Initial revision.
 * 
 */


