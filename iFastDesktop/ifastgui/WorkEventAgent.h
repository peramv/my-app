#pragma once

class DSTCSecurity;

namespace Json
{
   class Value;
}

class WorkEventAgent
{
public:

  virtual ~WorkEventAgent() {}

  virtual const Json::Value& getOutFields(const DSTCSecurity* pSecurity,
                                          const DString& companyid) = 0;

  static const Json::Value callService(const DSTCSecurity* pSecurity, Json::Value& request,
                                       const DString& companyid);
   static void setUserId(const DString &dstrUserID);
  static WorkEventAgent* createInstance(DString dstrUserID, DString dstrTopic);

protected:
  static DStringA getComputerName() { return computerName_; }
  static DStringA getUserId() { return userID_; }
  static DStringA getDtopId() { return dtopID_; }

private:
   static DStringA userID_;
   static DStringA dtopID_;
   static DStringA computerName_;
};
