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
// ^FILE   : ifastdbrkr.hpp
// ^AUTHOR : Chris Purdye
// ^DATE   : Apri 2010
//
//******************************************************************************

#include <srcprag.h>
#include <win32\platform.h>
#include <DString.hpp>

// Import/Export resolution
#undef IFASTDBRKR_LINKAGE
#ifdef IFASTDBRKR_DLL
#define IFASTDBRKR_LINKAGE CLASS_EXPORT
#else
#define IFASTDBRKR_LINKAGE CLASS_IMPORT
#endif

namespace ifastdbrkr
{
IFASTDBRKR_LINKAGE enum class MessageService { SonicMQ, ActiveMQ };
struct MessageServiceConfig
{
  DString brokerURLs;
  DString singleQueue;
  DString multiQueue;
  DString ldapQueue;
  DString awdQueue;
  DString user;
  DString password;
  int iTimeout;
  int iTimeToLive;
  int iMaxConnections;
};
IFASTDBRKR_LINKAGE MessageService getMessageService();
IFASTDBRKR_LINKAGE void setMessageService(MessageService ms);
IFASTDBRKR_LINKAGE MessageService cycleMessageService();

IFASTDBRKR_LINKAGE void initialize();
IFASTDBRKR_LINKAGE void shutdown();

IFASTDBRKR_LINKAGE void initializeActiveMQ();
IFASTDBRKR_LINKAGE void shutdownActiveMQ();

IFASTDBRKR_LINKAGE const DStringA& getBatchSize(const DStringA& view);
IFASTDBRKR_LINKAGE bool getBatchSize(DStringA& view, DStringA& size);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/ifastdbrkr.hpp-arc  $
//
//   Rev 1.0   May 03 2010 04:53:48   purdyech
//Initial revision.
//
*/
