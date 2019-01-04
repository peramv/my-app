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
// ^FILE   :  DSTCHost.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif

#ifndef DSTCHOST_HPP
   #include "DSTCHost.hpp"
#endif

#ifndef DSTCSECURITY_HPP
   #include "DSTCSecurity.hpp"
#endif

DSTCHost *DSTCHost::_primaryHost = NULL;
DSTCHost *DSTCHost::_backupHost = NULL;

DSTCHost::DSTCHost(const DString &id)
: _id(id)
{
}

DSTCHost::~DSTCHost()
{
}

const DString &
DSTCHost::getId() const
{
   return(_id);
}

BFSecurity *
DSTCHost::createSecurity() const
{
   return(new DSTCSecurity(this));
}

void
DSTCHost::setPrimaryHost(const DString &id)
{
   delete _primaryHost;
   _primaryHost = NULL;
   _primaryHost = new DSTCHost(id);
}

void
DSTCHost::setBackupHost(const DString &id)
{
   delete _backupHost;
   _backupHost = NULL;
   _backupHost = new DSTCHost(id);
}

const DSTCHost &
DSTCHost::getPrimaryHost()
{
   if( NULL == _primaryHost )
   {
      assert(0);
      throw;
   }

   return(*_primaryHost);
}

const DSTCHost &
DSTCHost::getBackupHost()
{
   if( NULL == _backupHost )
   {
      assert(0);
      throw;
   }

   return(*_backupHost);
}

