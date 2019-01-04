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
// ^FILE   : ActiveMQConnectionFactory.hpp
// ^AUTHOR : David B. Smith
// ^DATE   : January 2000
//
// ^CLASS    : ActiveMQConnectionFactory
// ^INHERITS FROM : BFConnectionFactory
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include <win32\platform.h>
#include <bfconmgr\BFConnectionFactory.hpp>
#include <dstring.hpp>
#include <memory>

#undef MIN_PRIORITY
#undef MAX_PRIORITY

class BFConnection;

namespace cms
{
class ConnectionFactory;
class Connection;
}

// Import/Export resolution
#undef IFASTDBRKR_LINKAGE
#ifdef IFASTDBRKR_DLL
#define IFASTDBRKR_LINKAGE CLASS_EXPORT
#else
#define IFASTDBRKR_LINKAGE CLASS_IMPORT
#endif

class IFASTDBRKR_LINKAGE ActiveMQConnectionFactory : public BFConnectionFactory
{
 public:
  ActiveMQConnectionFactory(const DString& brokerURLs, const DString& singleQueue,
                            const DString& multiQueue, const DString& ldapQueue,
                            const DString& awdQueue, const DString& user, const DString& password,
                            int cMaxUses, int iTimeout, int iTimeToLive,
                            const DString& dstrCswAcl = DString(I_("cswacl")));
  ~ActiveMQConnectionFactory();

  const DString& getCswAcl() const { return dstrCswAcl_; }

  virtual BFConnection* createConnection(const DStringA& hostId);
  virtual void destroyConnection(BFConnection* connection);

  inline int getTimeout() const { return iTimeout_; }
  void setTimeout(int iTimeout);
  inline int getTimeToLive() const { return iTimeToLive_; }
  void setTimeToLive(int iTimeToLive);
  inline const DString& getBrokerURLs() const { return brokerURLs_; }
  inline const DString& getSingleQueue() const { return singleQueue_; }
  inline const DString& getMultiQueue() const { return multiQueue_; }
  inline const DString& getLDAPQueue() const { return ldapQueue_; }
  inline const DString& getAwdQueue() const { return awdQueue_; }
  inline const DString& getUser() const { return user_; }
  inline const DString& getPassword() const { return password_; }
  inline int getMaxUses() const { return cMaxUses_; }

  std::shared_ptr<cms::Connection> getSingleConnection();

 private:
  DString brokerURLs_;
  DString singleQueue_;
  DString multiQueue_;
  DString ldapQueue_;
  DString awdQueue_;
  DString user_;
  DString password_;
  int cMaxUses_;
  int iTimeout_;
  int iTimeToLive_;

  DString dstrCswAcl_;

  std::shared_ptr<cms::ConnectionFactory> connFactory_;
  std::shared_ptr<cms::Connection> s_singleConnection_;

  static bool reuseConnection();

public:
  static cms::ConnectionFactory* createCMSConnectionFactory(const DString& brokerURLs,
                                                            const DString& user = I_(""),
                                                            const DString& password = I_(""));

};
