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
// ^FILE   : BFWorkSession.cpp
// ^AUTHOR : David Smith
// ^DATE   : 
//
//******************************************************************************
#include "bfworksession.hpp"
#include "bfusersession.hpp"

//******************************************************************************
BFWorkSession::BFWorkSession(BFUserSession &userSession, long workDataSetId)
: BFSession( workDataSetId )
, BFCBO()
, _userSession( userSession )
, _hostTransactionContainer()
, _clientLocale( userSession.getClientLocale() )
, _hadTrxnError(false)
, _endSession(false)

{
   EXECHISTI( I_( "BFWorkSession( BFUserSession &, long )" ) );
   ClientLocaleContext::set(_clientLocale);
}

//******************************************************************************
const BFSession &
BFWorkSession::getSession() const
{
   return(*this);
}

//******************************************************************************
BFSession &
BFWorkSession::getSession()
{
   return(*this);
}

//******************************************************************************
bool 
BFWorkSession::isSession() const
{
   return(true);
}

//******************************************************************************
const BFUserSession &
BFWorkSession::getUserSession() const
{
   return(_userSession);
}

//******************************************************************************
const BFGlobalSession &
BFWorkSession::getGlobalSession() const
{
   return(_userSession.getGlobalSession());
}

//******************************************************************************
BFUserSession &
BFWorkSession::getUserSession()
{
   return(_userSession);
}

//******************************************************************************
BFGlobalSession &
BFWorkSession::getGlobalSession()
{
   return(_userSession.getGlobalSession());
}

//******************************************************************************
const BFSecurity *
BFWorkSession::getSecurity(const BFHost &host) const
{
   return(_userSession.getSecurity(host));
}

//******************************************************************************
const ClientLocale &
BFWorkSession::getClientLocale() const
{
   return(_clientLocale);
}

void 
BFWorkSession::setClient( const DString &client )
{
   _clientLocale.setClient( client );
   ClientLocaleContext::set(_clientLocale);
}

//******************************************************************************
bool
BFWorkSession::isBFWorkSession() const 
{
   return(true);
}

//******************************************************************************
bool
BFWorkSession::isBFGlobalSession() const 
{
   return(false);
}

//******************************************************************************
bool
BFWorkSession::isBFUserSession() const 
{
   return(false);
}

//******************************************************************************
HostTransactionContainer& 
BFWorkSession::getHostTransactionContainer()
{
   return(_hostTransactionContainer);
}
//******************************************************************************
void 
BFWorkSession::cleanupWorkSession()
{
   eraseObjectContainer();
   _hostTransactionContainer.clearContainer();
}

//******************************************************************************
void 
BFWorkSession::clearUncommitedTransactions()
{
   _hostTransactionContainer.clearUncommitedTransactions();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfcbo/BFWorkSession.cpp-arc  $
//
//   Rev 1.9   Feb 20 2009 14:48:04   purdyech
//ZTS Revision 6
//
//   Rev 1.8   May 14 2004 13:24:36   SMITHDAV
//Add a temporary data area to the session objects. This replaces the InterProcessData globale areas.
//
//   Rev 1.7   May 10 2004 15:09:02   SMITHDAV
//Move work-session level "global data" to the BFWorksession from InterProcessData.
// 
//    Rev 1.6   Oct 09 2002 17:40:12   PURDYECH
// New PVCS Database
// 
//    Rev 1.5   Aug 29 2002 12:51:08   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   22 May 2002 17:54:28   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   Aug 16 2001 17:24:44   HUANGSHA
// Temp bug fix
// 
//    Rev 1.2   08 Aug 2001 10:56:48   SMITHDAV
// Made extensive fixes to ClientLocale management.
// 
//    Rev 1.1   03 Jul 2001 16:22:30   SMITHDAV
// Add revision constants.
// 
//    Rev 1.0   03 May 2001 14:37:58   SMITHDAV
// Initial revision.
 * 
 */
