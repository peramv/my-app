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
// ^FILE   : BFGlobalSession.cpp
// ^AUTHOR : David Smith
// ^DATE   : 
//
//******************************************************************************
#include "bfglobalsession.hpp"
#include "bfusersession.hpp"

//******************************************************************************
BFGlobalSession::BFGlobalSession(BFUserSession &userSession, long workDataSetId) 
: BFSession(workDataSetId)
, BFCBO()
, _userSession( userSession )
{
}

//******************************************************************************
const BFSession &
BFGlobalSession::getSession() const
{
   return(*this);
}

//******************************************************************************
BFSession &
BFGlobalSession::getSession()
{
   return(*this);
}

//******************************************************************************
const BFUserSession &
BFGlobalSession::getUserSession() const
{
   return(_userSession);
}

//******************************************************************************
bool 
BFGlobalSession::isSession() const
{
   return(true);
}

//******************************************************************************
const BFGlobalSession &
BFGlobalSession::getGlobalSession() const
{
   return(*this);
}

//******************************************************************************
BFUserSession &
BFGlobalSession::getUserSession()
{
   return(_userSession);
}

//******************************************************************************
BFGlobalSession &
BFGlobalSession::getGlobalSession()
{
   return(*this);
}

//******************************************************************************
const BFSecurity *
BFGlobalSession::getSecurity(const BFHost &host) const
{
   return(_userSession.getSecurity(host));
}

//******************************************************************************
const ClientLocale &
BFGlobalSession::getClientLocale() const
{
   return(_userSession.getClientLocale());
}

//******************************************************************************
bool
BFGlobalSession::isBFWorkSession() const 
{
   return(false);
}

//******************************************************************************
bool
BFGlobalSession::isBFGlobalSession() const 
{
   return(true);
}

//******************************************************************************
bool
BFGlobalSession::isBFUserSession() const 
{
   return(false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/BFGlobalSession.cpp-arc  $
//
//   Rev 1.5   May 14 2004 13:24:38   SMITHDAV
//Add a temporary data area to the session objects. This replaces the InterProcessData globale areas.
// 
//    Rev 1.4   Oct 09 2002 17:40:04   PURDYECH
// New PVCS Database
// 
//    Rev 1.3   Aug 29 2002 12:51:06   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.2   22 May 2002 17:54:18   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   03 Jul 2001 16:22:18   SMITHDAV
// Add revision constants.
// 
//    Rev 1.0   03 May 2001 14:37:56   SMITHDAV
// Initial revision.
 * 
 */
