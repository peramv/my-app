#include "stdafx.h"

#include <ifastdbrkr\ifastdbrkr.hpp>
#include ".\workeventagent.h"
#include "SonicWorkEventAgent.h"
#include "ActiveMQWorkEventAgent.h"

using namespace boost;

static DStringA createUUID()
{
    UUID uuid;
    UuidCreate ( &uuid );

    unsigned char * str;
    UuidToStringA ( &uuid, &str );

    DStringA s( ( char* ) str );
    RpcStringFreeA ( &str );

    return s;
}

static DStringA getComputerName()
{
   DWORD length = MAX_COMPUTERNAME_LENGTH + 1;
   char buffer[MAX_COMPUTERNAME_LENGTH + 1];

   if ( GetComputerNameA(buffer, &length) )
      return DStringA(buffer);
   else
      return DStringA("<Unknown>");
}

void WorkEventAgent::setUserId(const DString& dstrUserID) { userID_ = dstrUserID; }

DStringA WorkEventAgent::computerName_ = getComputerName();
DStringA WorkEventAgent::dtopID_ = createUUID();
DStringA WorkEventAgent::userID_ = NULL_STRING;

WorkEventAgent* WorkEventAgent::createInstance(DString dstrUserID, DString dstrTopic)
{
  switch (ifastdbrkr::getMessageService())
{
    case ifastdbrkr::MessageService::SonicMQ:
      return new SonicWorkEventAgent(dstrUserID, dstrTopic);

	case ifastdbrkr::MessageService::ActiveMQ:
      return new ActiveMQWorkEventAgent(dstrUserID, dstrTopic);

    default:
      assert(0);
}

  return nullptr;
}
const Json::Value WorkEventAgent::callService(const DSTCSecurity* pSecurity, Json::Value& request,
                                              const DString& dstrCompanyId)
{
  switch (ifastdbrkr::getMessageService())
{
    case ifastdbrkr::MessageService::SonicMQ:
      return SonicWorkEventAgent::callService(pSecurity, request, dstrCompanyId);
   
	case ifastdbrkr::MessageService::ActiveMQ:
      return ActiveMQWorkEventAgent::callService(pSecurity, request, dstrCompanyId);
   
    default:
      assert(0);
}

  return Json::Value();
   }
