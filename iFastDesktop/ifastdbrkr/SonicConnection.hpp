#pragma once
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
// ^FILE   : SonicConnection.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : SonicConnection
// ^INHERITS FROM : BFRecordConnection         
//
// ^CLASS DESCRIPTION : 
//    
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>
#include <vector>
#include <bfconmgr\bfrecordconnection.hpp>

#include <progress/message/jclient/package.h>

// Import/Export resolution
#undef IFASTDBRKR_LINKAGE
#ifdef IFASTDBRKR_DLL
   #define IFASTDBRKR_LINKAGE CLASS_EXPORT
#else
   #define IFASTDBRKR_LINKAGE CLASS_IMPORT
#endif

class DSTCSecurity;

class IFASTDBRKR_LINKAGE SonicConnection : public BFRecordConnection
{
public:
   SonicConnection( const DStringA& hostId, 
                    const DStringA& connectionName, 
                    progress::message::jclient::QueueConnectionFactoryRef connFactory,
                    const DStringA &singleQueue,
                    const DStringA &multiQueue,
                    const DStringA &ldapQueue,
                    const DStringA &awdQueue,
                    int cMaxUses,
                    int iTimeout,
                    const DString& dstrCswAcl );
   virtual ~SonicConnection();

   virtual void putRequest( const DStringA& viewName, 
                            const DStringA& request, 
                            bool bCanRecycle, 
                            const BFData* pQuery, 
                            BFSecurity* pSecurity = NULL );

   void putRequestLDAP( const DStringA& request, bool bCanRecycle, DSTCSecurity* pDSTCSecurity );
   
   void putRequestAWD( const DStringA& request, 
                       bool bCanRecycle, 
                       const DString& companyid, 
                       DSTCSecurity* pDSTCSecurity );


   virtual const DStringA& getResponse();
   virtual const DStringA& getHostId() const;
   virtual const DStringA& getDescription() const;
   virtual bool isStale() const;
   void makeStale();

   virtual bool recycle();
   virtual void setRecycleRequired() {
      bRecycleRequired_ = true;
   }
   virtual bool isRecycleRequired() const {
      return(bRecycleRequired_);
   }
   void setTimeout( int iTimeout ) { iTimeout_ = iTimeout; }


public:
   struct Details {
      Details()
      : p_(NULL)
      , tQueue_(I_(""))
      , cUses_( 0 )
      , cRecycles_( 0 )
      , iTimeout_( 0 )
      {}
      SonicConnection* p_;
      DString tQueue_;
      int cUses_;
      int iTimeout_;
      int cRecycles_;
   };
   friend Details;
   typedef std::vector< SonicConnection::Details > DETAILS_VECTOR;
   typedef DETAILS_VECTOR::iterator DETAILS_VECTOR_ITER;
   static DETAILS_VECTOR getDetails();

private:
   static bool reuseConnection();
   void connect();
   void freeResponse();
   void disconnect();

   bool sendBuf( const DStringA& viewName,
                 const char *pRequestBuffer, 
                 int cRequestBuffer, 
                 bool bRecycleAllowed,
                 bool bRecycleOnReceive );
   bool recvBuf( const DStringA& viewName );
   bool connectionReset( int rcSock ) const;
   bool waitForData( int iTimeOut ) const;

   const DStringA idHost_;
   progress::message::jclient::QueueConnectionFactoryRef connFactory_;
   const DStringA singleQueue_; 
   const DStringA multiQueue_; 
   const DStringA ldapQueue_;
   const DStringA awdQueue_;
   const DStringA nameConnection_;
   const DStringA description_;

   bool connected_;
   bool bRecycleRequired_;

   int cMaxUses_;    // maximum number of transmissions which this socket should make
                     // before recycling
   int cUses_;       // number of times that this socket has been used to send/receive
   int iTimeout_;    // maximum number of seconds to wait for a response from the host
   int cRecycles_;

   DString dstrCswAcl_;

   progress::message::jclient::QueueConnectionRef getSingleConnection();
   static progress::message::jclient::QueueConnectionRef s_singleConnection_;

   progress::message::jclient::QueueConnectionRef connection_;
   progress::message::jclient::QueueSessionRef session_;
   progress::message::jclient::QueueSenderRef singleSender_;
   progress::message::jclient::QueueSenderRef multiSender_;
   progress::message::jclient::QueueSenderRef ldapSender_;
   progress::message::jclient::QueueSenderRef awdSender_;
   progress::message::jclient::QueueReceiverRef receiver_;
   progress::message::jclient::TemporaryQueueRef tempQueue_;

   void createResponse( const DStringA& viewName, const DStringA& persistHandle );
   
   void putRequest( QueueSenderRef sender, 
                    const DStringA& request, 
                    bool bCanRecycle, 
                    const DString& companyid, 
                    DSTCSecurity* pDSTCSecurity );
   
   DStringA dstrResponse_;

private:
   static jint s_deliveryMode_;
public:
   static jint getDefaultDeliveryMode();
   static jint setDefaultDeliveryMode(jint newValue);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/SonicConnection.hpp-arc  $
//
//   Rev 1.16   Dec 12 2010 17:33:30   purdyech
//IN2350361 - Performance enhancements
//
//   Rev 1.15   Oct 22 2009 04:46:18   purdyech
//Missed a merge
//
//   Rev 1.14   Oct 21 2009 10:59:06   purdyech
//LDAP Authorization support.   
//
//   Rev 1.13   Oct 14 2009 10:33:58   purdyech
//Single Connection
//
//   Rev 1.12   Aug 03 2009 23:12:52   purdyech
//LDAP Integration Pieces
//
//   Rev 1.11   Aug 02 2009 22:27:46   yingz
//LDAP change
//
//   Rev 1.10   Jun 05 2009 08:28:04   purdyech
//Fixed names of SonicSingle and SonicMulti queues in configuration.
//SonicErrorMessages are now handled appropriately.
//
//   Rev 1.9   May 01 2009 09:26:26   purdyech
//Add support to customize CswAcl property value
//
//   Rev 1.8   Mar 27 2009 10:08:56   purdyech
//Added more JMSProperties to ZTS request messages.
//
//   Rev 1.7   Mar 02 2009 08:21:12   purdyech
//ZTS Fixes to allow timeout to be dynamically reset.
//
//   Rev 1.6   Feb 27 2009 08:49:48   purdyech
//ZTS Fixes prior to User Experience Test
//
//   Rev 1.5   Feb 20 2009 14:56:48   purdyech
//ZTS Revision 6
//
//   Rev 1.4   Feb 06 2009 14:52:30   purdyech
//Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
//
//   Rev 1.3   Jan 27 2009 15:39:38   purdyech
//ZTS Support Upgrade
//
//   Rev 1.2   Aug 15 2008 08:33:12   purdyech
//Removed nextCorrid.  Class now uses a (guarded) static function so public definition is no longer needed.
//
//   Rev 1.1   Jun 19 2008 10:39:44   smithdav
//Make nextCorrid static.
//
//   Rev 1.0   Jun 17 2008 15:55:26   smithdav
//Initial revision.
// 
//
*/