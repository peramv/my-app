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
// ^FILE   : ActiveMQConnection.hpp
// ^AUTHOR : David B. Smith
// ^DATE   : January 2000
//
// ^CLASS    : ActiveMQConnection
// ^INHERITS FROM : BFRecordConnection
//
// ^CLASS DESCRIPTION :
//
//
//******************************************************************************
#include <win32\platform.h>
#include <bfconmgr\bfrecordconnection.hpp>
#include <dstring.hpp>
#include <vector>
#include <memory>

#undef MIN_PRIORITY
#undef MAX_PRIORITY

// Import/Export resolution
#undef IFASTDBRKR_LINKAGE
#ifdef IFASTDBRKR_DLL
#define IFASTDBRKR_LINKAGE CLASS_EXPORT
#else
#define IFASTDBRKR_LINKAGE CLASS_IMPORT
#endif

class DSTCSecurity;

namespace cms
{
class Connection;
class ConnectionFactory;
class Session;
class MessageProducer;
class MessageConsumer;
class TemporaryQueue;
};

class IFASTDBRKR_LINKAGE ActiveMQConnection : public BFRecordConnection
{
 public:
  ActiveMQConnection(const DStringA& hostId, const DStringA& connectionName,
                     std::shared_ptr<cms::ConnectionFactory> connFactory,
                     const DStringA& singleQueue, const DStringA& multiQueue,
                     const DStringA& ldapQueue, const DStringA& awdQueue, int cMaxUses,
                     int iTimeout, int iTimeToLive,const DString& dstrCswAcl);

  ActiveMQConnection(const DStringA& hostId, const DStringA& connectionName,
                     std::shared_ptr<cms::Connection> connection,
                     const DStringA& singleQueue, const DStringA& multiQueue,
                     const DStringA& ldapQueue, const DStringA& awdQueue, int cMaxUses,
                     int iTimeout, int iTimeToLive, const DString& dstrCswAcl);

  virtual ~ActiveMQConnection();

  virtual void putRequest(const DStringA& viewName, const DStringA& request, bool bCanRecycle,
                          const BFData* pQuery, BFSecurity* pSecurity = nullptr);

  void putRequestLDAP(const DStringA& request, bool bCanRecycle, DSTCSecurity* pDSTCSecurity);

  void putRequestAWD(const DStringA& request, bool bCanRecycle, const DString& companyid,
                     DSTCSecurity* pDSTCSecurity);

  virtual const DStringA& getResponse();
  virtual const DStringA& getHostId() const;
  virtual const DStringA& getDescription() const;
  virtual bool isStale() const;
  void makeStale();

  virtual bool recycle();
  virtual void setRecycleRequired() { bRecycleRequired_ = true; }
  virtual bool isRecycleRequired() const { return (bRecycleRequired_); }
  void setTimeout(int iTimeout) { iTimeout_ = iTimeout; }
  void setTimeToLive(int iTimeToLive) { iTimeToLive_ = iTimeToLive; }

 public:
  struct Details
  {
    Details() : p_(nullptr), tQueue_(I_("")), cUses_(0), cRecycles_(0), iTimeout_(0), iTimeToLive_(0) {}
    ActiveMQConnection* p_;
    DString tQueue_;
    int cUses_;
    int iTimeout_;
	int iTimeToLive_;
    int cRecycles_;
  };
  friend Details;
  typedef std::vector<ActiveMQConnection::Details> DETAILS_VECTOR;
  typedef DETAILS_VECTOR::iterator DETAILS_VECTOR_ITER;
  static DETAILS_VECTOR getDetails();

 private:
  void connect();
  void freeResponse();
  void disconnect();

  bool sendBuf(const DStringA& viewName, const char* pRequestBuffer, int cRequestBuffer,
               bool bRecycleAllowed, bool bRecycleOnReceive);
  bool recvBuf(const DStringA& viewName);
  bool connectionReset(int rcSock) const;
  bool waitForData(int iTimeOut) const;

  const DStringA idHost_;
  std::shared_ptr<cms::ConnectionFactory> connFactory_;
  std::shared_ptr<cms::Connection> singleConnection_;
  const DStringA singleQueue_;
  const DStringA multiQueue_;
  const DStringA ldapQueue_;
  const DStringA awdQueue_;
  const DStringA nameConnection_;
  const DStringA description_;

  bool connected_;
  bool bRecycleRequired_;

  int cMaxUses_;  // maximum number of transmissions which this socket should make
                  // before recycling
  int cUses_;     // number of times that this socket has been used to send/receive
  int iTimeout_;  // maximum number of seconds to wait for a response from the host
  int iTimeToLive_;
  int cRecycles_;

  DString dstrCswAcl_;

  std::unique_ptr<cms::Connection> connection_;
  std::unique_ptr<cms::Session> session_;
  std::unique_ptr<cms::MessageProducer> singleSender_;
  std::unique_ptr<cms::MessageProducer> multiSender_;
  std::unique_ptr<cms::MessageProducer> ldapSender_;
  std::unique_ptr<cms::MessageProducer> awdSender_;
  std::unique_ptr<cms::MessageConsumer> receiver_;
  std::unique_ptr<cms::TemporaryQueue> tempQueue_;

  void createResponse(const DStringA& viewName, const DStringA& persistHandle);

  void putRequest(cms::MessageProducer* sender, const DStringA& request, bool bCanRecycle,
                  const DString& companyid, DSTCSecurity* pDSTCSecurity);

  DStringA dstrResponse_;

 private:
  static int s_deliveryMode_;

 public:
  static int getDefaultDeliveryMode();
  static int setDefaultDeliveryMode(int newValue);
};
