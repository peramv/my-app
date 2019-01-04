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
//
//******************************************************************************
//
// ^FILE   :  BFDataBroker.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <SrcPrag.h>
#include "BFDataBroker.hpp"
#include <base.h>
#include <conditionmanager.hpp>
#include <configmanager.hpp>
#include <BaseDBSecurity.hpp>
#include "BFRequest.hpp"
#include "BFRequestor.hpp"
#include "FileRequestor.hpp"
#include "SysLoadRequestor.hpp"


namespace
{
   const I_CHAR *CLASSNAME             = I_( "BFDataBroker" );
   const I_CHAR *const GETINSTANCE     = I_( "getInstance" );

   const I_CHAR *const STUB_MODE       = I_( "STUB_MODE" );
   const I_CHAR *const DATA_BROKER     = I_( "DataBroker" );
   const I_CHAR *const DATA_PATH       = I_( "DataPath" );
   const I_CHAR *const PATH            = I_( "Path" );
   const I_CHAR *const SYS_LOAD_PATH   = I_( "SysloadPath" );
   const I_CHAR *const DEMO_MODE       = I_( "DemoMode" );
   const I_CHAR *const PROTO_DATA_PATH = I_( "ProtoDataPath" );
   const I_CHAR *const RECEIVE         = I_( "receive" );
}

namespace CND
{
   extern const I_CHAR *BFDBRKR_CONDITION;
}

//initialize the static members
BFDataBroker *BFDataBroker::_pInstance = NULL;

//******************************************************************************
BFDataBroker::BFDataBroker()
: _sysLoadFileRequestor(NULL)
, _requestCount(0)
, _conditionCount(0)
, _informationCount(0)
, _warningCount(0)
, _severeErrorCount(0)//
, _criticalErrorCount(0)
, _stubFilesPath( I_( "" ) )
, _stubMode(OFF)
{
   ConfigManager* theMgr = ConfigManager::getManager( DATA_BROKER );
   Configuration theConfig = theMgr->retrieveConfig( DATA_PATH );

   DStringA sysLoadPath = theConfig.getValueAsString( SYS_LOAD_PATH );
   _sysLoadFileRequestor = new FileRequestor(sysLoadPath);

   I_CHAR *rpEnv = NULL;
   rpEnv = i_getenv( STUB_MODE );    // Can return NULL pointer if no variable
   if( rpEnv )
   {
      if( !i_strcmp( rpEnv, I_("OFFLINE") ) )
      {
         _stubMode = OFFLINE;
      }
      else if( !i_strcmp( rpEnv, I_("COLLECT") ) )
      {
         _stubMode = COLLECT;
      }
      if( !i_strcmp( rpEnv, I_("OFFLINE") ) || !i_strcmp( rpEnv, I_("COLLECT") ) )
      {
         theConfig = theMgr->retrieveConfig( DEMO_MODE );
         _stubFilesPath = theConfig.getValueAsString( PROTO_DATA_PATH );
      }
   }
}

//******************************************************************************
BFDataBroker::~BFDataBroker()
{

   delete _sysLoadFileRequestor;

}

//******************************************************************************
BFDataBroker *
BFDataBroker::getInstance( void )
{
   TRACE_METHOD( CLASSNAME, GETINSTANCE );

   if( !BFDataBroker::_pInstance )
   {
      BFDataBroker::_pInstance = new BFDataBroker();
      if( !BFDataBroker::_pInstance )
      {
         THROWFROMBASE( CND::BFDBRKR_CONDITION, GETINSTANCE, BASE_ALLOC_FAIL );
         return(NULL);
      }
   }
   return(BFDataBroker::_pInstance);
}

//******************************************************************************
void 
BFDataBroker::killInstance()
{
   if( BFDataBroker::_pInstance )
   {
      delete BFDataBroker::_pInstance;
      BFDataBroker::_pInstance = NULL;
   }
}



//******************************************************************************
SEVERITY 
BFDataBroker::receive( const BFRequest &request, BFData &queryData, BFData &receivedData, BFRequestor &requestor, bool *outMoreAvailable /*= NULL*/ )
{
   SEVERITY sev;

   // working off-line? -- receive data from stub file
   if( OFFLINE ==_stubMode )
   {
      FileRequestor stubFileRequestor( _stubFilesPath, false, true );
      sev = stubFileRequestor.receive( request, queryData, receivedData, outMoreAvailable );
      requestor.setRequestTime( stubFileRequestor.getRequestTime() );     
      incrementRequestStats(sev);
      return( sev );
   }
   else if( COLLECT == _stubMode )
   {
      FileRequestor stubFileRequestor( _stubFilesPath, false, false );
      if( stubFileRequestor.fileExists(request, queryData ) )
      {
         sev = stubFileRequestor.receive( request, queryData, receivedData, outMoreAvailable );
         requestor.setRequestTime( stubFileRequestor.getRequestTime() );     
      }
      else
      {
         sev = requestor.receive( request, queryData, receivedData, outMoreAvailable );
         stubFileRequestor.store(request, receivedData );
      }
      incrementRequestStats(sev);
      return(sev);
   }

   // sysLoad request type? -- create a sysload requestor and use it to receive data
   if( request.isSysLoadRequest() )
   {
      SysLoadRequestor sysLoadRequestor(*_sysLoadFileRequestor, requestor);
      return(sysLoadRequestor.receive( request, queryData, receivedData, outMoreAvailable ));
   }

   // recieve data from specified requestor
   {
      sev = requestor.receive( request, queryData, receivedData, outMoreAvailable );
      incrementRequestStats(sev);
      return(sev);
   }
}

//******************************************************************************
void 
BFDataBroker::incrementRequestStats(SEVERITY severity)
{
   _requestCount++;

   BFGuard g( csCount_ );
   switch( severity )
   {
      case NO_CONDITION:
         break;
      case INFORMATIONAL:
         _conditionCount++;
         _informationCount++;
         break;
      case WARNING:
         _conditionCount++;
         _warningCount++;
         break;
      case SEVERE_ERROR:
         _conditionCount++;
         _severeErrorCount++;
         break;
      case CRITICAL_ERROR:
         _conditionCount++;
         _criticalErrorCount++;
         break;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfdbrkr/BFDataBroker.cpp-arc  $
//
//   Rev 1.13   Aug 12 2003 10:07:58   PURDYECH
//Added new logging method (bf::log::...)
// 
//    Rev 1.12   Oct 09 2002 17:40:36   PURDYECH
// New PVCS Database
// 
//    Rev 1.11   Aug 29 2002 12:49:26   PURDYECH
// ClientLocale and Field corrections
// 
//    Rev 1.10   Jul 05 2002 08:53:04   PURDYECH
// Cleaned up code.
// 
//    Rev 1.9   22 May 2002 17:56:08   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   22 Mar 2002 15:17:08   PURDYECH
// BFData integration
// 
//    Rev 1.7   25 Sep 2001 13:22:46   PURDYECH
// Stub File Fixes.
// 
//    Rev 1.6   18 Sep 2001 15:20:46   PURDYECH
// Get STUB_DATA working again.
// 
//    Rev 1.5   Jun 12 2001 15:05:58   DINACORN
// Sync. up with SSB (1.2.1.2)
 *
 */
