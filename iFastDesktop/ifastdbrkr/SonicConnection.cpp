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
// ^FILE   :  SonicConnection.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  April 2000
//
// ----------------------------------------------------------
#include <srcprag.h>
#include "SonicConnection.hpp"
#include <conditionmanager.hpp>
#include <bf/log/log.hpp>
#include <bfdata/bfdata.hpp>
#include <bfutil/bfhrtimer.hpp>
#include <bfdbrkr/bfviewtimelog.hpp>
//#include "base64.h"
#include <vector>
#include <map>
#include <sstream>
#include <configmanager.hpp>
#include <ifastdbrkr/dstcsecurity.hpp>
#include <ifastdbrkr/SonicFrameworkError.hpp>
#include <ifastdbrkr/ifastdbrkr.hpp>

namespace ifds {
   const DString& getAppVersion();
}

#include <assert.h>

using namespace java::lang;
using namespace progress::message::jclient;

namespace
{
   extern const I_CHAR *CLASSNAME = I_( "SonicConnection" );
}


DString asDString( StringRef s ) {
   WStringRef wStr = s->toWide();
   std::wstring w;
   w.append( (const I_CHAR*)wStr, wStr->length() );
   return( DString(w) );
}

DStringA asDStringA( StringRef s ) {
   AStringRef aStr = s->toAscii();
   std::string a;
   a.append( (const char*)aStr, aStr->length() );
   return( DStringA(a) );
}

static const char* getDelimiter() {
   static unsigned char szDelim[2] = {0x00, 0x00};
      szDelim[0] = 0xfe;
   
   return( (const char*)szDelim );
}


namespace CND
{
   extern const I_CHAR *IFASTDBRKR_CONDITION;
//   extern const long ERR_SMQ_SOCKET_INITIALIZATION_FAILED;
   extern const long ERR_SMQ_CONNECT_FAILED;
   extern const long ERR_SMQ_MESSAGE_SEND_FAILED;
   extern const long ERR_SMQ_MESSAGE_RECEIVE_FAILED;
   extern const long ERR_SMQ_UNKNOWN_MESSAGE_TYPE;
   extern const long ERR_SMQ_SONICMQ_ERROR;
   extern const long ERR_INVALID_PERSIST_REQUEST;
   extern const long ERR_VIEW_TIMEOUT;
}

static DString LogJMSException( unsigned long l, JMSExceptionRef e ) {
   bf::log::LogStream ls( bf::log::databroker );
   ls << bf::log::information;
   StringRef strCode = e->getErrorCode();
   DString dstrCode = DString( asDStringA(strCode) );
   int eType = e->getType();
   StringRef s = e->toString();
   DString msg = DString( asDStringA( s ) );
   ls << I_("JMSException detected at line ") << l << I_(".  Type=" ) << eType << I_(", Code=") << dstrCode.c_str() << I_(", msg=") << msg.c_str() << bf::log::endlf;
   return( msg );
}

static StringRef getLocalHost() {
   char szHostName[256];
   gethostname( szHostName, sizeof(szHostName)/sizeof(szHostName[0]) );
   return( createString( szHostName ) );
}

static StringRef getLocalIP() {
   WSADATA wsaData;
   struct hostent *pHostEnt; 
   struct sockaddr_in tmpSockAddr; //placeholder for the ip address

   // Not needed if it is already taken care by some other part of the application
   WSAStartup(MAKEWORD(2,0),&wsaData); 

//   char hostname[25];
//   strcpy(hostname,"Test Computer Name")
   //This will retrieve the ip details and put it into pHostEnt structure
   char szHostName[256];
   gethostname(szHostName, sizeof(szHostName)/sizeof(szHostName[0]));
   pHostEnt = gethostbyname(szHostName);

   if ( NULL == pHostEnt ) {
      return( createString("") );
   }

   memcpy(&tmpSockAddr.sin_addr,pHostEnt->h_addr,pHostEnt->h_length);

   char szIP[17];
   strcpy(szIP,inet_ntoa(tmpSockAddr.sin_addr));
   StringRef s = createString(szIP);
   return( s );
}

static DStringA getNextPersistHandle() {
   static BFCritSec cs;
   BFGuard g(cs);
   static long s_PersistRequestId = 0;
   char szBuf[16];
   sprintf( szBuf, "%05d0000000000", ++s_PersistRequestId );
   return( DStringA(szBuf) );
}

static StringRef s_JMS_SonicMQ_preserveUndelivered = createString("JMS_SonicMQ_preserveUndelivered");
static StringRef s_JMS_SonicMQ_notifyUndelivered   = createString("JMS_SonicMQ_notifyUndelivered");
static StringRef s_IFAST_ORIGIN_USER               = createString("IFAST_ORIGIN_USER");
static StringRef s_IFAST_ORIGIN_COMPUTER           = createString("IFAST_ORIGIN_COMPUTER");
static StringRef s_IFAST_ORIGIN_IP                 = createString("IFAST_ORIGIN_IP");
static StringRef s_IFAST_SLOT_NAME                 = createString("IFAST_SLOT_NAME");
static StringRef s_IFAST_ZTS_REPLYTO               = createString("IFAST_ZTS_REPLYTO");
static StringRef s_IFAST_SESSION_ID                = createString("IFAST_SESSION_TOKEN");
static StringRef s_IFAST_COMPANY_ID                = createString("IFAST_ZTS_COMPANY_ID");
static StringRef s_IFAST_USER_ID                   = createString("IFAST_ZTS_USER_ID");
static StringRef s_IFAST_VIEW_NAME                 = createString("IFAST_ZTS_VIEW_NAME");
static StringRef s_IFAST_VERSION                   = createString("IFAST_VERSION");
static StringRef s_IFAST_TRACK_ID                  = createString("IFAST_TRACK_ID");
static StringRef s_IFAST_NUM_BATCH                 = createString("IFAST_NUM_BATCH");
//static StringRef s_IFAST_SESSION_TOKEN             = createString("IFAST_SESSION_TOKEN");
static StringRef s_IFAST_ORIGIN_APPLICATION        = createString("IFAST_ORIGIN_APPLICATION");

static StringRef s_OriginUser       = createString( getenv("USERNAME") );
static StringRef s_OriginComputer   = getLocalHost();
static StringRef s_OriginIP         = getLocalIP();
static StringRef s_OriginApplication= createString("DTOP");

static StringRef s_OEInvocationTime = createString("IFAST_METRIC_OE_INVOCATION");
static StringRef s_ViewTime         = createString("IFAST_ZTS_VIEWTIME");
static StringRef s_PreViewTime      = createString("IFAST_ZTS_PREVIEWTIME");
static StringRef s_PostViewTime     = createString("IFAST_ZTS_POSTVIEWTIME");
static StringRef s_ESB_In           = createString("IFAST_TS_ENTRY");
static StringRef s_ESB_Out          = createString("IFAST_TS_EXIT");

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SessionId;
   extern CLASS_IMPORT const BFTextFieldId User_Id;
   extern CLASS_IMPORT const BFTextFieldId LanguageCode;
   extern CLASS_IMPORT const BFTextFieldId CompanyId;
}

class ConnectionLogInfo {
public:
   ConnectionLogInfo( const DStringA& viewName ) 
   : viewName_( viewName )
   , msgId_("")
   , sendTime_( 0 )
   , receiveTime_(0)
   , unitOfWorkTime_(0)
   , networkTime_(0)
   , oeInvocationTime_(0)
   , preViewTime_(0)
   , viewTime_(0)
   , postViewTime_(0) 
   {
      GetSystemTime(&timeStamp_);
   }

   void setMsgId( const DStringA& msgId ) {
      msgId_ = msgId;
   }
   const DStringA& getMsgid() const {
      return msgId_;
   }

   void setSendTime( unsigned long v ) {
      sendTime_ = v;
   }
   unsigned long getSendTime() const {
      return sendTime_;
   }

   void setReceiveTime( unsigned long v ) {
      receiveTime_ = v;
   }
   unsigned long getReceiveTime() const {
      return receiveTime_;
   }

   void setUnitOfWorkTime( unsigned long v ) {
      unitOfWorkTime_ = v;
   }
   unsigned long getUnitOfWorkTime() const {
      return unitOfWorkTime_;
   }

   void setNetworkTime( unsigned long v ) {
      networkTime_ = v;
   }
   unsigned long getNetworkTime() const {
      return networkTime_;
   }

   unsigned long getOEInvocationTime() const {
      return oeInvocationTime_;
   }
   
   void setOEInvocationTime( unsigned long v ) {
      oeInvocationTime_ = v;
   }

   void setPreViewTime( unsigned long v ) {
      preViewTime_ = v;
   }
   unsigned long getPreViewTime() const {
      return preViewTime_;
   }

   void setViewTime( unsigned long v ) {
      viewTime_ = v;
   }
   unsigned long getViewTime() const {
      return viewTime_;
   }

   void setPostViewTime( unsigned long v ) {
      postViewTime_ = v;
   }
   unsigned long getPostViewTime() const {
      return postViewTime_;
   }

   void log() {
      BFViewTimeLog::getInstance().log( viewName_, msgId_, sendTime_, receiveTime_, unitOfWorkTime_, networkTime_, oeInvocationTime_, viewTime_, preViewTime_, postViewTime_ );
   }

   void log( const char* pszNote ) {
      BFViewTimeLog::getInstance().log( viewName_, msgId_, sendTime_, receiveTime_, unitOfWorkTime_, networkTime_, oeInvocationTime_, viewTime_, preViewTime_, postViewTime_, pszNote );
   }


private:
   const DStringA    viewName_;
   DStringA          msgId_;
   unsigned long     sendTime_;
   unsigned long     receiveTime_;
   unsigned long     unitOfWorkTime_;
   unsigned long     networkTime_;
   unsigned long     oeInvocationTime_;
   unsigned long     viewTime_;
   unsigned long     preViewTime_;
   unsigned long     postViewTime_;
   SYSTEMTIME        timeStamp_;    //
};

static long getNextCorrID() {
   static BFCritSec s_CorrID;
   static long nextCorrID = 0;
   BFGuard g(s_CorrID);
   return(++nextCorrID);
}

typedef std::vector<DStringA> REQUEST_VECTOR;
typedef REQUEST_VECTOR::iterator REQUEST_VECTOR_ITER;
typedef std::map< DStringA, REQUEST_VECTOR* > MAP_PERSIST_REQUESTS;
typedef MAP_PERSIST_REQUESTS::iterator MAP_PERSIST_REQUESTS_ITER;

MAP_PERSIST_REQUESTS s_mapPersistentRequests;

void deletePersistentRequests( const DStringA& key ) {
   MAP_PERSIST_REQUESTS_ITER it = s_mapPersistentRequests.find( key );
   if ( it != s_mapPersistentRequests.end() ) {
      REQUEST_VECTOR* p = (*it).second;
      delete p;
      s_mapPersistentRequests.erase(it);
   }
}

typedef std::set< SonicConnection* > CONNECTION_SET;
typedef CONNECTION_SET::iterator CONNECTION_SET_ITER;
static CONNECTION_SET s_setConnections;
static BFCritSec s_csSet;

SonicConnection::DETAILS_VECTOR SonicConnection::getDetails() {
   DETAILS_VECTOR v;
   CONNECTION_SET_ITER i;
   for ( i = s_setConnections.begin();
       i != s_setConnections.end();
       ++i ) {
      SonicConnection* p = *i;
      SonicConnection::Details s;
      s.p_ = p;
      s.cUses_ = p->cUses_;
      s.iTimeout_ = p->iTimeout_;
      s.cRecycles_ = p->cRecycles_;
      progress::message::jclient::TemporaryQueueRef t = p->tempQueue_;
      StringRef tq = t->getQueueName();
      s.tQueue_ = DStringA(tq->toAscii());
      v.push_back( s );
   }

   return v;
}

// Keep a simple map of the existing connections

static void addConnection( SonicConnection* p ) {
   BFGuard g(s_csSet);
   s_setConnections.insert( p );
}

static void removeConnection( SonicConnection* p ) {
   CONNECTION_SET_ITER i = s_setConnections.find(p);
   if ( i != s_setConnections.end() ) {
      s_setConnections.erase( p );
   }
}

bool SonicConnection::reuseConnection() {
   return( GetConfigValueAsBool( I_("RTSHost"), I_("UseSingleSonicConnection") ) );
}

progress::message::jclient::QueueConnectionRef SonicConnection::s_singleConnection_ = null;
progress::message::jclient::QueueConnectionRef SonicConnection::getSingleConnection() {
   if ( s_singleConnection_ != null ) {
      return( s_singleConnection_ );
   }
   static BFCritSec cs;
   BFGuard g(cs);
   if ( s_singleConnection_ == null ) {
      s_singleConnection_ = connFactory_->createQueueConnection();
      s_singleConnection_->start();
   }
   return( s_singleConnection_ );
}


jint SonicConnection::s_deliveryMode_ = DeliveryMode_NON_PERSISTENT_ASYNC;

static BFCritSec s_csDeliveryMode;
jint SonicConnection::getDefaultDeliveryMode() {
   BFGuard g(s_csDeliveryMode);
   return( s_deliveryMode_ );
}

jint SonicConnection::setDefaultDeliveryMode(jint newValue) {
   BFGuard g(s_csDeliveryMode);
   jint oldValue = s_deliveryMode_;
   s_deliveryMode_ = newValue;
   return( oldValue );
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SonicConnection::SonicConnection( const DStringA& hostId, 
                                  const DStringA& connectionName, 
                                  QueueConnectionFactoryRef connFactory,
                                  const DStringA& singleQueue,
                                  const DStringA& multiQueue,
                                  const DStringA& ldapQueue,
                                  const DStringA& awdQueue,
                                  int cMaxUses,
                                  int iTimeout,
                                  const DString& dstrCswAcl )
: idHost_(hostId)
, connFactory_(connFactory)
, singleQueue_(singleQueue)
, multiQueue_(multiQueue)
, ldapQueue_( ldapQueue )
, awdQueue_( awdQueue )
, nameConnection_(connectionName)
, description_(hostId + ":" + connectionName)
, bRecycleRequired_(false)
, cMaxUses_(cMaxUses)
, cUses_(0)
, cRecycles_(0)
, iTimeout_( 0 == iTimeout ? 60 : iTimeout )
, connection_(null)
, session_(null)
, singleSender_(null)
, multiSender_(null)
, ldapSender_(null)
, awdSender_(null)
, receiver_(null)
, tempQueue_(null)
, dstrCswAcl_( dstrCswAcl ) {
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING )
}

SonicConnection::~SonicConnection() {
   removeConnection( this );
   try {
      disconnect();
   }
   catch ( ... ) {
   }
}



//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void SonicConnection::connect() {
   bf::log::LogStream ls( bf::log::databroker );
   ls << bf::log::information;
   BFHRTimer tConnect;

   try {
      try {
         if ( !reuseConnection() ) {
            connection_ = connFactory_->createQueueConnection();
            connection_->start();
            session_ = connection_->createQueueSession(jfalse, Session_AUTO_ACKNOWLEDGE);
         }
         else {
            session_ = getSingleConnection()->createQueueSession(jfalse, Session_AUTO_ACKNOWLEDGE);
         }
         singleSender_ = session_->createSender(createQueue(createString(singleQueue_.c_str())));
         multiSender_ = null;
         ldapSender_ = null;
         awdSender_ = null;
         tempQueue_ = session_->createTemporaryQueue();
         receiver_ = session_->createReceiver( tempQueue_ );


      }
      catch (ConditionException) {
         throw;
      }
      catch ( progress::message::jclient::JMSExceptionRef e ) {
         DString idi;
         addIDITagValue( idi, I_("ERROR"), LogJMSException( __LINE__, e ) );
         THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("connect"), CND::ERR_SMQ_SONICMQ_ERROR, idi );
      }
      catch (...) {
         THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("connect"), CND::ERR_SMQ_MESSAGE_SEND_FAILED );
      }
   }
   catch ( ... ) {
      ls << bf::log::information << I_( "SonicConnection::connect -- failed creating job" ) << bf::log::endl;
      if ( tempQueue_ != null ) {
         try {
            tempQueue_->_delete();
         }
         catch (...) {
         }
         tempQueue_=null; 
      }
      if ( session_ != null ) {
         try {
            session_->close();
         }
         catch (...) {
         }
         session_=null; 
      }
      if ( !reuseConnection() && connection_ != null ) {
         try {
            connection_->close();
         }
         catch (...) {
         }
         connection_=null; 
      }
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_( "connect" ), CND::ERR_SMQ_CONNECT_FAILED );
   }

   cUses_ = 0;
}

//******************************************************************************
void SonicConnection::disconnect() {
   bf::log::LogStream ls( bf::log::databroker );
   ls << bf::log::information;
   BFHRTimer tClose;

   if ( tempQueue_ != null ) {
      try {
         tempQueue_->_delete();
      }
      catch (...) {
      }
      tempQueue_=null; 
   }
   if ( session_ != null ) {
      try {
         session_->close();
      }
      catch (...) {
      }
      session_=null; 
   }
   if ( !reuseConnection() ) {
      if ( connection_ != null ) {
         try {
            connection_->close();
         }
         catch (...) {
         }
         connection_=null; 
      }
   }

   // free the response buffer
   freeResponse();

   cUses_ = -1;
}

bool SonicConnection::recycle() {
   try {
      bf::log::LogStream ls( bf::log::databroker );
      ls << bf::log::information;

      ++cRecycles_;
      disconnect();
      connect();
      bRecycleRequired_ = false;
   }
   catch ( ConditionException& ) {
   }
   return( 1 == (session_ != null) );
}

const DStringA NullPersistHandle("000000000000000");

void SonicConnection::createResponse( const DStringA& viewName, const DStringA& persistHandle ) {
   // B0007300073000020000x000000000000001FY
   // ^    ^    ^    ^    ^    ^    ^    ^
   dstrResponse_ = "B";
   dstrResponse_ += viewName.substr(7);
   dstrResponse_ += viewName.substr(7);
   dstrResponse_ += "00002";
   dstrResponse_ += persistHandle;
   dstrResponse_ += "00001";

      dstrResponse_ += getDelimiter();
  
   dstrResponse_ += "FY";
}

void SonicConnection::putRequestLDAP( const DStringA& request, bool bCanRecycle, DSTCSecurity* pDSTCSecurity ) {

   // does this need to be recycled?
   if ( -1 != cMaxUses_ && ++cUses_ > cMaxUses_ ) {
      recycle();
   }
   try {
      if ( ldapSender_ == null ) {
         ldapSender_ = session_->createSender(createQueue(createString(ldapQueue_.c_str())));
      }
   }
   catch (ConditionException) {
      throw;
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      setRecycleRequired();
      DString idi;
      addIDITagValue( idi, I_("ERROR"), LogJMSException( __LINE__, e ) );
      THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequestLDAP"), CND::ERR_SMQ_SONICMQ_ERROR, idi );
   }
   catch (...) {
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequestLDAP"), CND::ERR_SMQ_MESSAGE_SEND_FAILED );
   }
   putRequest( ldapSender_, request, bCanRecycle, null, pDSTCSecurity );
}


void SonicConnection::putRequestAWD( const DStringA& request, 
                                     bool bCanRecycle, 
                                     const DString& companyId, 
                                     DSTCSecurity* pDSTCSecurity ) {


   if ( session_ == null ) {
      connect();
      addConnection(this);
   }

   // does this need to be recycled?
   if ( -1 != cMaxUses_ && ++cUses_ > cMaxUses_ ) {
      recycle();
   }
   try {
      if ( awdSender_ == null ) {
         awdSender_ = session_->createSender(createQueue(createString(awdQueue_.c_str())));
      }
   }
   catch (ConditionException) {
      throw;
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      setRecycleRequired();
      DString idi;
      addIDITagValue( idi, I_("ERROR"), LogJMSException( __LINE__, e ) );
      THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequestAWD"), CND::ERR_SMQ_SONICMQ_ERROR, idi );
   }
   catch (...) {
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequestAWD"), CND::ERR_SMQ_MESSAGE_SEND_FAILED );
   }
   putRequest( awdSender_, request, bCanRecycle, companyId, pDSTCSecurity );
}


void SonicConnection::putRequest( progress::message::jclient::QueueSenderRef sender, 
                                  const DStringA& request, 
                                  bool bCanRecycle, 
                                  const DString& companyId,
                                  DSTCSecurity* pDSTCSecurity ) {

   bf::log::LogStream ls( bf::log::databroker );
   ls << bf::log::information;
   ls << I_("SonicConnection::putRequest  Request to send LDAP/AWD") << bf::log::endlf;
   bf::log::LogStream lsTrace( bf::log::databroker );
   lsTrace << bf::log::ltrace;

   freeResponse();
   dstrResponse_ = "";

   TextMessageRef reqMessage;
   try {
      reqMessage = session_->createTextMessage();
   }
   catch (ConditionException) {
      throw;
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      setRecycleRequired();
      DString idi;
      addIDITagValue( idi, I_("ERROR"), LogJMSException( __LINE__, e ) );
      THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"), CND::ERR_SMQ_SONICMQ_ERROR, idi );
   }
   catch (...) {
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"), CND::ERR_SMQ_MESSAGE_SEND_FAILED );
   }

   // Logging out the content of the messages would violate compliance rules.  
   //   CP 20101203
   //lsTrace << DString(request) << bf::log::endlf;

   StringRef reqText = createString( request.c_str() ); 

   reqMessage->setText( reqText);
   reqMessage->setBooleanProperty( s_JMS_SonicMQ_preserveUndelivered, jfalse);
   reqMessage->setBooleanProperty( s_JMS_SonicMQ_notifyUndelivered, jfalse);
   reqMessage->setStringProperty( s_IFAST_ZTS_REPLYTO, tempQueue_->getQueueName() );
   reqMessage->setStringProperty( s_IFAST_ORIGIN_USER, s_OriginUser );
   reqMessage->setStringProperty( s_IFAST_ORIGIN_COMPUTER, s_OriginComputer );
   reqMessage->setStringProperty( s_IFAST_ORIGIN_IP, s_OriginIP );
   reqMessage->setStringProperty( s_IFAST_VERSION, createString( ifds::getAppVersion().c_str() ) );
   reqMessage->setStringProperty( s_IFAST_ORIGIN_APPLICATION, s_OriginApplication);

   if ( companyId != NULL_STRING ) {
      reqMessage->setStringProperty(s_IFAST_SLOT_NAME, createString(companyId.c_str()));
      reqMessage->setStringProperty(s_IFAST_COMPANY_ID, createString(companyId.c_str()));
   }

   if ( NULL != pDSTCSecurity ) {
      DString sessionId = I_("");
      sessionId = pDSTCSecurity->getSessionId();
      sessionId.stripTrailing();
      reqMessage->setStringProperty(s_IFAST_SESSION_ID, createString(sessionId.c_str()));
   }

   QueueReceiverRef receiver = null;
   try {
      StringRef corrID = Long::toHexString(getNextCorrID());
      reqMessage->setJMSReplyTo( tempQueue_ );

      reqMessage->setJMSCorrelationID(corrID);

      BFHRTimer tSend,tUOW;
      sender->send( reqMessage, getDefaultDeliveryMode(), 4, iTimeout_*1000 );
      ++cUses_;

      StringRef msgId = reqMessage->getJMSMessageID();
	  WStringRef msgWide = msgId->toWide();
      DString dstrMsgId = (const I_CHAR*)msgWide;
//      cli.setMsgId( dstrMsgId );
      //cli.setSendTime( tSend.elapsed() );
      ls << I_("Message ") << dstrMsgId << I_(" sent for view LDAP/AWD.") << bf::log::endlf;

      BFHRTimer tCreateRecv;
      lsTrace << I_("Receiver created in ") << tCreateRecv.elapsed() << I_(" ms.") << bf::log::endl;

      BFHRTimer tRecv;
      try {
         lsTrace << I_("SonicConnection::putRequest().  About to receive for ") << dstrMsgId << bf::log::endlf;
         tRecv.reset();
         MessageRef respMessage = null;
         unsigned long timeout = iTimeout_ * 1000;
         while ( 1 ) {
            respMessage = (iTimeout_ == 0L) ? receiver_->receive()
                          : receiver_->receive( iTimeout_*1000 );
            if ( respMessage != null ) {
               StringRef respCorrID = respMessage->getJMSCorrelationID();
               if ( !respCorrID->equals(corrID) ) {
                  continue;
               }
               // reset SessionID from IFAST_SESSION_ID property
               if ( respMessage->propertyExists( s_IFAST_SESSION_ID ) ) {
                  DString sessionId = asDString(respMessage->getStringProperty( s_IFAST_SESSION_ID ));
                  ls << I_("New Session ID: ") << sessionId << bf::log::endlf;
                  pDSTCSecurity->setSessionId( sessionId );
               }
            }
            break;
         }
         lsTrace << I_("SonicConnection::putRequest().  Received ") << dstrMsgId << bf::log::endlf;
         if ( respMessage!= null && respMessage->instanceof(TextMessage::type()) ) {
            TextMessageRef textMsg = TextMessageRef::cast(respMessage);
            StringRef msgText = textMsg->getText();
            AStringRef aStr = msgText->toAscii();
            std::string rStr;
            rStr.append( (const char*)aStr, aStr->length() );
            if ( rStr.length() == 0  ) {
               // It's XML ... it's an error!  
//                  ls << I_("TextMessage ") << dstrTrackId << I_(" [") << aStr->length() << I_("] ") << DString(DStringA(rStr.c_str())) << bf::log::endlf;
               SonicFrameworkError sfwe( rStr, getDelimiter() );
               dstrResponse_ = sfwe.getErrorMessage();
               dstrResponse_ += getDelimiter();
               dstrResponse_ += "F";
//                  dstrResponse_ += DStringA(dstrTrackId);
            }
            else {
               std::string rStrDecoded = rStr;
               // Logging out the content of the messages would violate compliance rules.  
               //   CP 20101203
               //lsTrace << I_("TextMessage ") << I_(" [") << rStrDecoded.length() << I_("] ") << DString(DStringA(rStrDecoded.c_str())) << bf::log::endlf;
               lsTrace << I_("TextMessage ") << I_(" [") << rStrDecoded.length() << I_("] ") << bf::log::endlf;
               dstrResponse_ = rStrDecoded;
            }
         }
      }
      catch (ConditionException) {
         // cli.log("ConditionException");
         throw;
      }
      catch ( progress::message::jclient::JMSExceptionRef e ) {
         setRecycleRequired();
         DString idi;
         addIDITagValue( idi, I_("ERROR"), LogJMSException( __LINE__, e ) );
         THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"), CND::ERR_SMQ_SONICMQ_ERROR, idi );
      }
      catch (...) {
         THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"), CND::ERR_SMQ_MESSAGE_SEND_FAILED );
      }
   }
   catch (ConditionException) {
      throw;
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      setRecycleRequired();
      DString idi;
      addIDITagValue( idi, I_("ERROR"), LogJMSException( __LINE__, e ) );
      THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"), CND::ERR_SMQ_SONICMQ_ERROR, idi );
   }
   catch (...) {
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"), CND::ERR_SMQ_MESSAGE_SEND_FAILED );
   }

}

//******************************************************************************
void SonicConnection::putRequest( const DStringA& oViewName, 
                                  const DStringA& request,
                                  bool bCanRecycle,
                                  const BFData* pQuery,
                                  BFSecurity* pSecurity ) {
   bf::log::LogStream ls( bf::log::databroker );
   ls << bf::log::information;
   ls << I_("SonicConnection::putRequest  Request to send ") << DString(oViewName) << bf::log::endlf;
   bf::log::LogStream lsTrace( bf::log::databroker );
//   lsTrace << bf::log::ltrace;

   DStringA viewName(oViewName);
   DSTCSecurity* pDSTCSecurity = NULL;
   if ( NULL != pSecurity ) {
      try {
         pDSTCSecurity = dynamic_cast<DSTCSecurity*>(pSecurity);
      }
      catch (const std::bad_cast& e) {
         ls << I_("Security object is not DSTCSecurity: ") << DString(DStringA(e.what())) << bf::log::endl;
      }
   }

   if ( session_ == null ) {
      connect();
      addConnection(this);
   }


   if ( viewName == "LDAP" ) {
      putRequestLDAP( request, bCanRecycle, pDSTCSecurity );
      return;
   }

   if ( viewName == "AWD" ) {
      putRequestAWD( request, bCanRecycle, NULL_STRING, pDSTCSecurity );
      return;
   }

   int retryCount=0;
   bool retry=false;
   do {
   retry=false;
   progress::message::jclient::QueueSenderRef* pSender = &singleSender_;

   if ( viewName == "CFXTRAN00073" ) {
      DStringA persistRequest;
      DStringA persistHandle = getNextPersistHandle();
      REQUEST_VECTOR* pRV = NULL;
      pRV = new REQUEST_VECTOR;
      s_mapPersistentRequests[ persistHandle ] = pRV;
      persistRequest = request.substr( 0,27 );
      persistRequest += persistHandle;
      persistRequest += request.substr(42);
      pRV->push_back( persistRequest );
      createResponse( viewName, persistHandle );
      return;
   }
   DStringA persistHandle = "";
   persistHandle = request.substr( 27,15 );
   if ( persistHandle != NullPersistHandle ) {
      REQUEST_VECTOR* pRV = NULL;
      MAP_PERSIST_REQUESTS_ITER it = s_mapPersistentRequests.find( persistHandle );
      if ( it == s_mapPersistentRequests.end() ) {
         THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_( "putRequest" ), CND::ERR_INVALID_PERSIST_REQUEST );
      }
      else {
         pRV = (*it).second;
      }
      pRV->push_back( request );
      if ( viewName != "CFXTRAN00074" && viewName != "CFXTRAN10074" ) {
         // if not commit or rollback then create a response and return
         createResponse( viewName,persistHandle );
         ++cUses_;
         return;
      }
   }

   ConnectionLogInfo cli( viewName );

   // does this need to be recycled?
   if ( -1 != cMaxUses_ && ++cUses_ > cMaxUses_ ) {
      recycle();
   }
   freeResponse();
   dstrResponse_ = "";

   TextMessageRef reqMessage;
   try {
      reqMessage = session_->createTextMessage();
   }
   catch (ConditionException) {
      throw;
   }
   catch ( progress::message::jclient::JMSExceptionRef e ) {
      setRecycleRequired();
      DString idi;
      addIDITagValue( idi, I_("ERROR"), LogJMSException( __LINE__, e ) );
      THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"), CND::ERR_SMQ_SONICMQ_ERROR, idi );
   }
   catch (...) {
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"), CND::ERR_SMQ_MESSAGE_SEND_FAILED );
   }
   if ( viewName != "CFXTRAN00074" &&
        viewName != "CFXTRAN10074" ) {
      DStringA reqLog = request;
      if ( viewName == "CFLOGON00001" ) {
         // don't log password for Logon View.  Password is field 2.  
         // Find delim character
         char chDelim = reqLog.at(48);
         size_t begin = 50;
         begin = reqLog.find_first_of( chDelim, begin );
         if ( std::string::npos != begin ) {
            begin += 2; // go past delimiter and unknown flag
            size_t end = reqLog.find_first_of( chDelim, begin );
            reqLog.replace( begin, end - begin, "**********" );
         }
      }
      else if ( viewName == "CFXTRAN00039" ) {
         //must replace fields 4 and 5 with stars
         char chDelim = reqLog.at(48);
         size_t begin = 0;
         int iField = 1;
         for ( int iField = 1; iField < 6 && std::string::npos != begin; ++iField ) {
            begin = reqLog.find_first_of( chDelim, ++begin );
            if ( std::string::npos != begin ) {
               if ( 4 == iField || 5 == iField ) {
                  begin += 2; // go past delimiter and unknown flag
                  size_t end = reqLog.find_first_of( chDelim, begin );
                  reqLog.replace( begin, end - begin, "**********" );
               }
            }
         }
      }
      // Logging out the content of the messages would violate compliance rules.  
      //   CP 20101203
      //lsTrace << DString(reqLog) << bf::log::endlf;
      reqMessage->setText(createString( (const unsigned char *)request.c_str(), "UTF-8" ) );
   }
   else {
      if ( viewName == "CFXTRAN10074" ) {
         // rollback!
         deletePersistentRequests( persistHandle );
         createResponse( "CFXTRAN00074", persistHandle );
         ls << I_("Rollback for ") << DString(persistHandle) << bf::log::endlf;
         ++cUses_;
         return;
      }
      // must be a commit!  
      std::stringstream s;
      s << "<?xml version=\"1.0\"?>"
      << "<SuperView xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      << "<Nasu>";
      MAP_PERSIST_REQUESTS_ITER it = s_mapPersistentRequests.find( persistHandle );
      if ( it != s_mapPersistentRequests.end() ) {
         REQUEST_VECTOR* p = (*it).second;
         int cSeq = 1;
         for ( REQUEST_VECTOR_ITER vit = p->begin(); vit != p->end(); ++vit,++cSeq ) {
            const DStringA& r = *vit;

            // Logging out the content of the messages would violate compliance rules.  
            //   CP 20101203
            //lsTrace << DString(r) << bf::log::endlf;
            std::string str = r.c_str();
            // XML escape str
            size_t begin = 0;
            while ( std::string::npos != ( begin = str.find_first_of( "&", begin ) ) ) {
               str.replace( begin++, 1, "&amp;" );
            }
            begin = 0;
            while ( std::string::npos != ( begin = str.find_first_of( "<", begin ) ) ) {
               str.replace( begin++, 1, "&lt;" );
            }
            begin = 0;
            while ( std::string::npos != ( begin = str.find_first_of( ">", begin ) ) ) {
               str.replace( begin++, 1, "&gt;" );
            }
            s << "<Views>";
            s << "<Seq>" << cSeq << "</Seq>";
            s << "<RawData>" << str << "</RawData>";
            s << "</Views>";
         }
      }
      s << "</Nasu>" << "</SuperView>";
      long len = s.str().length();
      const std::string& myStr = s.str();
      const char* pszReq = myStr.c_str();
      DString dx = DStringA(pszReq);
      lsTrace << I_("[") << len << I_(" bytes] " ) << dx << bf::log::endlf;
      reqMessage->setText( createString( (const unsigned char *)pszReq , "UTF-8" ));

      if ( multiSender_ == null ) {
         multiSender_ = session_->createSender(createQueue(createString(multiQueue_.c_str())));
      }
      pSender = &multiSender_;
      deletePersistentRequests( persistHandle );
   }

   reqMessage->setBooleanProperty( s_JMS_SonicMQ_preserveUndelivered, jfalse);
   reqMessage->setBooleanProperty( s_JMS_SonicMQ_notifyUndelivered, jfalse);
   reqMessage->setStringProperty( s_IFAST_ZTS_REPLYTO, tempQueue_->getQueueName() );
   reqMessage->setStringProperty( s_IFAST_ORIGIN_USER, s_OriginUser );
   reqMessage->setStringProperty( s_IFAST_ORIGIN_COMPUTER, s_OriginComputer );
   reqMessage->setStringProperty( s_IFAST_ORIGIN_IP, s_OriginIP );
   reqMessage->setStringProperty( s_IFAST_VERSION, createString(ifds::getAppVersion().c_str() ) );
   reqMessage->setStringProperty( s_IFAST_VIEW_NAME, createString( viewName.c_str() ) );
   reqMessage->setStringProperty( s_IFAST_ORIGIN_APPLICATION, s_OriginApplication);

   DStringA strBatch = ifastdbrkr::getBatchSize(viewName);
   if( strBatch.size() > 0 ) {
      reqMessage->setStringProperty( s_IFAST_NUM_BATCH, createString(strBatch.c_str()) );
   }

   DString companyId = dstrCswAcl_;
   if ( viewName != "CFLOGON00001" &&
        viewName != "CFLOGOFF00002" &&
        viewName != "CFXTRAN00039" ) {
      if ( pQuery->exists( ifds::CompanyId ) ) {
         companyId = pQuery->getElementValue( ifds::CompanyId );
         companyId.stripTrailing();
      }
   }
   reqMessage->setStringProperty(s_IFAST_SLOT_NAME, createString(companyId.c_str()));
   reqMessage->setStringProperty(s_IFAST_COMPANY_ID, createString(companyId.c_str()));
   DString sessionId = I_("");
   if ( NULL != pDSTCSecurity ) {
      sessionId = pDSTCSecurity->getSessionId();
      sessionId.stripTrailing();
   }
   reqMessage->setStringProperty(s_IFAST_SESSION_ID, createString(sessionId.c_str()));
//   reqMessage->setStringProperty(s_IFAST_SESSION_TOKEN, createString(sessionId.c_str()));

   DString userId;
   if ( pQuery->exists( ifds::User_Id ) ) {
      userId = pQuery->getElementValue( ifds::User_Id );
      userId.stripTrailing();
   }
   reqMessage->setStringProperty(s_IFAST_USER_ID, createString(userId.c_str()));
   QueueReceiverRef receiver = null;

   try {
      StringRef corrID = Long::toHexString(getNextCorrID());
      reqMessage->setJMSReplyTo( tempQueue_ );

      reqMessage->setJMSCorrelationID(corrID);

      BFHRTimer tSend,tUOW;
      (*pSender)->send( reqMessage, getDefaultDeliveryMode(), 4, iTimeout_*1000 );
      ++cUses_;

      StringRef msgId = reqMessage->getJMSMessageID();
	  WStringRef msgWide = msgId->toWide();
      DString dstrMsgId = (const I_CHAR*)msgWide;
      cli.setMsgId( dstrMsgId );
      cli.setSendTime( tSend.elapsed() );
      ls << I_("Message ") << dstrMsgId << I_(" sent for view ") << viewName << I_(".") << bf::log::endlf;

      BFHRTimer tCreateRecv;
      lsTrace << I_("Receiver created in ") << tCreateRecv.elapsed() << I_(" ms.") << bf::log::endl;

      BFHRTimer tRecv;
      try {
         lsTrace << I_("SonicConnection::putRequest().  About to receive for ") << dstrMsgId << bf::log::endlf;
         tRecv.reset();
         MessageRef respMessage = null;
         unsigned long timeout = iTimeout_ * 1000;
         while ( 1 ) {
            respMessage = (iTimeout_ == 0L) ? receiver_->receive()
                          : receiver_->receive( iTimeout_*1000 );
            if ( respMessage != null ) {
               StringRef respCorrID = respMessage->getJMSCorrelationID();
               if ( !respCorrID->equals(corrID) ) {
                  continue;
               }
               if ( respMessage->propertyExists( s_IFAST_SESSION_ID ) ) {
                  DString sessionId = asDString(respMessage->getStringProperty( s_IFAST_SESSION_ID ));
                  ls << I_("New Session ID: ") << sessionId << bf::log::endlf;
                  if ( NULL != pDSTCSecurity ) {
                     pDSTCSecurity->setSessionId( sessionId );
                  }
               }
            }
            break;
         }
         lsTrace << I_("SonicConnection::putRequest().  Received ") << dstrMsgId << bf::log::endlf;
         if ( respMessage!= null ) {
            DString dstrTrackId;
            tRecv.stop();
            tUOW.stop();
            cli.setReceiveTime( tRecv.elapsed() );
            cli.setUnitOfWorkTime( tUOW.elapsed() );

            lsTrace << I_("SonicConnection::putRequest, UOW for ") << dstrMsgId << I_(" was ") << tUOW.elapsed() << I_("ms.") << bf::log::endlf;

            if ( respMessage->propertyExists( s_OEInvocationTime ) ) {
               cli.setOEInvocationTime( respMessage->getLongProperty( s_OEInvocationTime ) / 1000000 );
            }
            // determine value of "VIEWTIME" parameter
            if ( respMessage->propertyExists( s_ViewTime ) ) {
               cli.setViewTime( respMessage->getIntProperty( s_ViewTime ) );
            }
            if ( respMessage->propertyExists( s_PreViewTime ) ) {
               cli.setPreViewTime( respMessage->getIntProperty( s_PreViewTime ) );
            }
            if ( respMessage->propertyExists( s_PostViewTime ) ) {
               cli.setPostViewTime( respMessage->getIntProperty( s_PostViewTime ) );
            }
            if ( respMessage->propertyExists( s_ESB_In ) &&
                 respMessage->propertyExists( s_ESB_Out ) ) {
               long esb_in_ms  = static_cast<long>(respMessage->getLongProperty(s_ESB_In));
               long esb_out_ms = static_cast<long>(respMessage->getLongProperty(s_ESB_Out));
               cli.setNetworkTime( esb_out_ms - esb_in_ms );
            }

            if ( respMessage->propertyExists( s_IFAST_TRACK_ID ) ) {
               dstrTrackId = asDString(respMessage->getStringProperty( s_IFAST_TRACK_ID ));
            }

            if ( respMessage->instanceof(BytesMessage::type()) ) {
               BytesMessageRef bytesMsg = BytesMessageRef::cast(respMessage);
               jbyteArrayRef msgBytes = createjbyteArray(bytesMsg->getBodySize());
               bytesMsg->readBytes(msgBytes);
               std::string str;
               str.append( (char*)msgBytes->getArray(), msgBytes->getLength());
               // Logging out the content of the messages would violate compliance rules.  
               //   CP 20101203
               //lsTrace << I_("BytesMessage ") << dstrTrackId << I_(" [") << str.length() << I_("] ") << DString(DStringA(str.c_str())) << bf::log::endlf;
               lsTrace << I_("BytesMessage ") << dstrTrackId << I_(" [") << str.length() << I_("] ") << bf::log::endlf;
               dstrResponse_ = str;
            }
            else if ( respMessage->instanceof(TextMessage::type()) ) {
               TextMessageRef textMsg = TextMessageRef::cast(respMessage);
               StringRef msgText = textMsg->getText();
               AStringRef aStr = msgText->toAscii();
               std::string rStr;
               rStr.append( (const char*)aStr, aStr->length() );
               if ( rStr.length() == 0 || I_('<') == rStr.at(0) ) {
                  // It's XML ... it's an error!  
                  ls << I_("TextMessage ") << dstrTrackId << I_(" [") << aStr->length() << I_("] ") << DString(DStringA(rStr.c_str())) << bf::log::endlf;
                  SonicFrameworkError sfwe( rStr, getDelimiter() );
                  dstrResponse_ = sfwe.getErrorMessage();
                  dstrResponse_ += getDelimiter();
                  dstrResponse_ += "F";
                  dstrResponse_ += DStringA(dstrTrackId);
               }
               else {
                  std::string rStrDecoded = rStr;
                  // Logging out the content of the messages would violate compliance rules.  
                  //   CP 20101203
                  //lsTrace << I_("TextMessage ") << dstrTrackId << I_(" [") << rStrDecoded.length() << I_("] ") << DString(DStringA(rStrDecoded.c_str())) << bf::log::endlf;
                  lsTrace << I_("TextMessage ") << dstrTrackId << I_(" [") << rStrDecoded.length() << I_("] ") << bf::log::endlf;
                  dstrResponse_ = rStrDecoded;
               }
            }
            else {
               ls << I_("Response to ") << dstrTrackId << I_(" received, but it's not of type TextMessage or ByteMessage");
               // It's a funny type like Multi-part or XML.
               // Fortunately, we can treat if like a Text message and get the underlying error out of the message
               TextMessageRef textMsg = TextMessageRef::cast(respMessage);
               StringRef msgText = textMsg->getText();
               AStringRef aStr = msgText->toAscii();
               std::string rStr;
               rStr.append( (const char*)aStr, aStr->length() );
               if ( 0 == rStr.length() || I_('<') == rStr.at(0) ) {
                  // It's XML ... it's an error!
                  SonicFrameworkError sfwe( rStr, getDelimiter() );
                  dstrResponse_ = sfwe.getErrorMessage();
                  dstrResponse_ += getDelimiter();
                  dstrResponse_ += "F";
                  dstrResponse_ += DStringA(dstrTrackId);
               }
               else {
                  // It's not XML so throw an error to the framework.
                  cli.log( "Unknown Message Received" );
                  THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_( "putRequest" ), CND::ERR_SMQ_UNKNOWN_MESSAGE_TYPE );
               }
            }
         }
         else {
            cli.log( "View Timeout" );
            DString strIdi;
            addIDITagValue( strIdi, I_("VIEWNAME"), DString(viewName) );
            DString timeout;
            timeout.convertIntToString(iTimeout_);
            addIDITagValue( strIdi, I_("TIMEOUT"), timeout);

            THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, 
                               CLASSNAME, 
                               I_( "putRequest" ), 
                               CND::ERR_VIEW_TIMEOUT,
                               strIdi );
         }
      }
      catch (ConditionException) {
         cli.setReceiveTime( tRecv.elapsed() );
         cli.log( "ConditionException" );
         throw;
      }
      catch ( JMSExceptionRef e ) {
         setRecycleRequired();
         DString idi;
         addIDITagValue( idi, I_("ERROR"), LogJMSException( __LINE__, e ) );
         THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_( "putRequest" ), CND::ERR_SMQ_SONICMQ_ERROR, idi );

      }
      catch (...) {
         cli.setReceiveTime( tRecv.elapsed() );
         cli.log( "Generic Exception" );
         THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_( "putRequest" ), CND::ERR_SMQ_MESSAGE_RECEIVE_FAILED );
      }
   }
   catch (ConditionException) {
      cli.log("ConditionException");
      throw;
   }
   catch ( JMSExceptionRef e ) {
      if (retryCount == 0 ) {
		  recycle();
		  ++retryCount;
		  retry=true;
	  } else {
         setRecycleRequired();
         DString idi;
         addIDITagValue( idi, I_("ERROR"), LogJMSException( __LINE__, e ) );
        THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"), CND::ERR_SMQ_SONICMQ_ERROR, idi );
	  }
   }
   catch (...) {
      cli.log("catch all");
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"), CND::ERR_SMQ_MESSAGE_SEND_FAILED );
   }
   cli.log();

   } while(retry);

}

//******************************************************************************
void SonicConnection::freeResponse() {
}

const DStringA &
SonicConnection::getHostId() const {
   return(idHost_);
}

const DStringA &
SonicConnection::getDescription() const {
   return(description_);
}

#pragma warning(push)
#pragma warning(disable: 4800)
bool 
SonicConnection::isStale() const {
   return( static_cast<bool>( session_ == null ) );
}
#pragma warning(pop)

void SonicConnection::makeStale() {
   recycle();
}

const DStringA &
SonicConnection::getResponse() {
   return( dstrResponse_ );
}


