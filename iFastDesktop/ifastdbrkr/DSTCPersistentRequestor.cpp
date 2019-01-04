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
// ^FILE   :  DSTCRequestor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <srcprag.h>
#include "dstcpersistentrequestor.hpp"
#include "dstcrequestbuffer.hpp"
#include "dstcresponsebuffer.hpp"
#include "dstcsecurity.hpp"
#include <conditionmanager.hpp>
#include "dstcrequest.hpp"
#include <bfdbrkr\bfdatabroker.hpp>
#include <ifastdataimpl\dse_dstc0074_req.hpp>
#include <ifastdataimpl\dse_dstc0074_vw.hpp>
#include <ifastdataimpl\dse_dstc0073_req.hpp>
#include <ifastdataimpl\dse_dstc0073_vw.hpp>
#include <assert.h>

namespace 
{
   const I_CHAR *const CLASSNAME = I_( "DSTCPersistentRequestor" );
   const I_CHAR *const RECEIVE   = I_( "receive" );
   const I_CHAR *const STUB_MODE = I_( "STUB_MODE" );
}

namespace CND
{
   extern const I_CHAR *IFASTDBRKR_CONDITION;
   extern const long ERR_PERSISTENCE_START_REQUEST_FAILED;
}

namespace DSTC_REQUEST
{
   extern CLASS_EXPORT const DSTCRequest PERSISTENCE_START;
   extern CLASS_EXPORT const DSTCRequest PERSISTENCE_COMMIT;
   extern CLASS_EXPORT const DSTCRequest PERSISTENCE_ROLLBACK;
}

//******************************************************************************
DSTCPersistentRequestor::DSTCPersistentRequestor( const DSTCSecurity *security, const DString &mgmtCoId, const DString &ppType )
: DSTCRequestor(security, true, true),
_persistMode( START_PERSIST ),
_persistHandle(),
_mgmtCoId(mgmtCoId),
_stale(false),
_commitParams (NULL)
{
   // send start call
   BFData persistStartRequest( ifds::DSTC0073_REQ );
   BFData persistStartResponse( ifds::DSTC0073_VW );

   persistStartRequest.setElementValue( ifds::CompanyId, _mgmtCoId );
   persistStartRequest.setElementValue( ifds::Track, I_("N") );
   persistStartRequest.setElementValue( ifds::Activity, NULL_STRING );
   persistStartRequest.setElementValue( ifds::PPType, ppType );


//###temporary fix for demo mode: begin ->
   SEVERITY severity;
   I_CHAR *rpEnv = NULL;
   rpEnv = i_getenv( STUB_MODE );    // Can return NULL pointer if no variable
   if( rpEnv && !i_strcmp( rpEnv, I_("OFFLINE") ) )
   {
      severity = BFDataBroker::getInstance()->receive( DSTC_REQUEST::PERSISTENCE_START, 
                                                       persistStartRequest, 
                                                       persistStartResponse,
                                                       *this );
   }
   else
   {
      severity = receive( DSTC_REQUEST::PERSISTENCE_START, 
                          persistStartRequest, 
                          persistStartResponse );
   }
//temporary fix for demo mode: <- end

   if( WARNING < severity )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("DSTCRequestor"), CND::ERR_PERSISTENCE_START_REQUEST_FAILED);

   DString updateStatus = persistStartResponse.getElementValue( ifds::UpdateStatus );
   if( I_("Y") != updateStatus.strip() )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("DSTCRequestor"), CND::ERR_PERSISTENCE_START_REQUEST_FAILED);

   _persistMode = IN_PERSIST;
}

//******************************************************************************
DSTCPersistentRequestor::~DSTCPersistentRequestor()
{
   if( !_stale )
      rollback();
}

//******************************************************************************
void DSTCPersistentRequestor::setCommitParams (BFData &commitParams)
{
   _commitParams = &commitParams;
}

//******************************************************************************
SEVERITY 
DSTCPersistentRequestor::commit(BFData& persistStopResponse)
{
   assert(!_stale);
   _persistMode = END_PERSIST;

   // send end call

   BFData persistStopRequest( ifds::DSTC0074_REQ );

   persistStopRequest.setElementValue( ifds::CompanyId, _mgmtCoId );
   persistStopRequest.setElementValue( ifds::Track, I_("N") );
   persistStopRequest.setElementValue( ifds::Activity, NULL_STRING );
   persistStopRequest.setElementValue( ifds::CommitFlag, I_("Y") );
   if (_commitParams)
   {
      persistStopRequest.setElementValue( ifds::BusinessArea, 
                                          _commitParams->getElementValue (ifds::BusinessArea).stripAll ());
      persistStopRequest.setElementValue( ifds::WorkType, 
                                          _commitParams->getElementValue (ifds::WorkType).stripAll ());
      persistStopRequest.setElementValue( ifds::AWDObjectId, 
                                          _commitParams->getElementValue (ifds::AWDObjectId).stripAll ());
      persistStopRequest.setElementValue( ifds::AWDCrda, 
                                          _commitParams->getElementValue (ifds::AWDCrda).stripAll ());
   }

//###temporary fix for demo mode: begin ->
   SEVERITY severity;
   I_CHAR *rpEnv = NULL;
   rpEnv = i_getenv( STUB_MODE );    // Can return NULL pointer if no variable
   if( rpEnv && !i_strcmp( rpEnv, I_("OFFLINE") ) )
   {
      severity = BFDataBroker::getInstance()->receive( DSTC_REQUEST::PERSISTENCE_COMMIT, 
                                                       persistStopRequest, 
                                                       persistStopResponse,
                                                       *this );
   }
   else
   {
      severity = receive( DSTC_REQUEST::PERSISTENCE_COMMIT, 
                          persistStopRequest, 
                          persistStopResponse );
   }
//temporary fix for demo mode: <- end

   _stale = true;

   return(severity);

}

//******************************************************************************
SEVERITY 
DSTCPersistentRequestor::rollback()
{
   assert(!_stale);
   _persistMode = END_PERSIST;

   // send end call

   BFData persistStopRequest( ifds::DSTC0074_REQ );
   BFData persistStopResponse( ifds::DSTC0074_VW );

   persistStopRequest.setElementValue( ifds::CompanyId, _mgmtCoId );
   persistStopRequest.setElementValue( ifds::Track, I_("N") );
   persistStopRequest.setElementValue( ifds::Activity, NULL_STRING );

   persistStopRequest.setElementValue( ifds::CommitFlag, I_("N") );

//###temporary fix for demo mode: begin ->
   SEVERITY severity;
   I_CHAR *rpEnv = NULL;
   rpEnv = i_getenv( STUB_MODE );    // Can return NULL pointer if no variable
   if( rpEnv && !i_strcmp( rpEnv, I_("OFFLINE") ) )
   {
      severity = BFDataBroker::getInstance()->receive( DSTC_REQUEST::PERSISTENCE_ROLLBACK, 
                                                       persistStopRequest, 
                                                       persistStopResponse,
                                                       *this );
   }
   else
   {
      severity = receive( DSTC_REQUEST::PERSISTENCE_ROLLBACK, 
                          persistStopRequest, 
                          persistStopResponse );
   }
//temporary fix for demo mode: <- end

   _stale = true;

   return(severity);

}

//******************************************************************************
BFRequestor *
DSTCPersistentRequestor::clone() const
{
   assert(0);
   return(NULL); 
}

//******************************************************************************
BFWriteBuffer *
DSTCPersistentRequestor::createRequestBuffer(const BFRequest &request) const
{
   assert(!_stale);
   return(new DSTCRequestBuffer(request, _persistMode, _persistHandle));
}

//******************************************************************************
SEVERITY 
DSTCPersistentRequestor::receiveBuffer( const BFRequest &request, 
                                        const BFWriteBuffer *queryBuffer, 
                                        BFReadBuffer **receivedBuffer,
                                        const BFData* pQuery )
{

   assert(!_stale);

   SEVERITY severity = DSTCRequestor::receiveBuffer( request, queryBuffer, receivedBuffer, pQuery );

   if( WARNING >= severity && START_PERSIST == _persistMode )
   {
      DSTCResponseBuffer *dstcResponseBuffer = dynamic_cast<DSTCResponseBuffer *>(*receivedBuffer);
      _persistHandle = dstcResponseBuffer->getPersistHandle();
   }

   return(severity);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCPersistentRequestor.cpp-arc  $
// 
//    Rev 1.17   Mar 27 2009 10:19:08   purdyech
// Added more JMSProperties to ZTS request messages.
// 
//    Rev 1.16   Feb 06 2009 14:53:14   purdyech
// Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
// 
//    Rev 1.15   15 Nov 2007 17:45:10   popescu
// PET 5636/01 Internal audit tracking
// 
//    Rev 1.14   Oct 09 2002 23:55:22   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.13   Aug 29 2002 12:51:18   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.12   Jun 14 2002 16:50:00   VASILEAD
// Added ppType param to the class constructor
// 
//    Rev 1.11   22 May 2002 18:12:56   PURDYECH
// BFData Implementation
// 
//    Rev 1.10   Jun 13 2001 13:48:12   DINACORN
// Sync. up with SSB (1.7.1.0)
// 
//    Rev 1.9   12 Jun 2001 13:49:08   SMITHDAV
// Fix bug -- set mgmtCoId for start and end persist views.
// 
//    Rev 1.8   03 May 2001 14:03:32   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.7   16 Feb 2001 14:55:38   SMITHDAV
// Fixed Substitution values. ??Some testing required??
// 
//    Rev 1.6   Jan 25 2001 15:49:40   YINGBAOL
// track rollback
// 
//    Rev 1.5   Jan 25 2001 13:55:04   YINGBAOL
// add etrack
// 
//    Rev 1.4   18 Jan 2001 11:55:54   SMITHDAV
// Moved PersistMode enum from DSTCRequestBuffer scope to global scope and into file DSTCPersistentRequestor.hpp so that it can be accessed outside of the DstcDbrkr lib.
// 
//    Rev 1.3   Jan 16 2001 13:47:04   OLTEANCR
// modified destructor
// 
//    Rev 1.2   06 Nov 2000 14:53:06   SMITHDAV
// Add exception handling for new data broker system.
// 
//    Rev 1.1   30 Oct 2000 11:22:44   SMITHDAV
// Add support for getting more records.
// 
//    Rev 1.0   23 Oct 2000 20:31:24   SMITHDAV
// Initial revision.
 */

