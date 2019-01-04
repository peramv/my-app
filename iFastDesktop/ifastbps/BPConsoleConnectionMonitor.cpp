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
// ^FILE   :  BPConsoleConnectionMonitor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  December 2000
//
// ----------------------------------------------------------
#include "stdafx.h"

#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif
#ifndef BPCONSOLECONNECTIONMONITOR_HPP
   #include "BPConsoleConnectionMonitor.hpp"
#endif
#ifndef BPCONSOLEHOSTCONNECTIONMONITOR_HPP
   #include "BPConsoleHostConnectionMonitor.hpp"
#endif
#ifndef BFHOSTCONNECTIONMANAGER_HPP
   #include <bfconmgr\BFHostConnectionManager.hpp>
#endif

BPConsoleConnectionMonitor::BPConsoleConnectionMonitor(const int refreshRate)
:  BFAbstractConnectionMonitor(refreshRate)
{
}

BPConsoleConnectionMonitor::~BPConsoleConnectionMonitor()
{
}

BFHostConnectionMonitor *
BPConsoleConnectionMonitor::createHostConnectionMonitor(const BFHostConnectionManager *hostConnectionManager)
{
   return(new BPConsoleHostConnectionMonitor(hostConnectionManager));
}
