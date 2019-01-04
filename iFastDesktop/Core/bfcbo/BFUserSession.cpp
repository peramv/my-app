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
// ^FILE   : BFUserSession.cpp
// ^AUTHOR : David Smith
// ^DATE   : 
//
//******************************************************************************
#include "bfusersession.hpp"
#include "bfglobalsession.hpp"
#include "bfworksession.hpp"
#include <conditionmanager.hpp>
#include <bfdbrkr\bfhost.hpp>
#include <bfdbrkr\bfsecurity.hpp>
#include <bfutil\clientlocalecontext.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME       = I_( "BFUserSession" );
   const I_CHAR * const LOGON           = I_( "logon" );
   const I_CHAR * const LOGOFF          = I_( "logoff" );
   const I_CHAR * const CHANGE_PASSWORD = I_( "changePassword" );
}

namespace CND
{  // Conditions used
   extern const I_CHAR *BFBASE_CONDITION;
}

//******************************************************************************
BFUserSession::BFUserSession(BFGlobalSession &globalSession, long workDataSetId)
: BFSession(workDataSetId)
, BFCBO()
, _globalSession( globalSession )
, _securityMap()
, _clientLocale( ClientLocaleContext::get() )
, _language(NULL_STRING)
{
}

//******************************************************************************
BFUserSession::~BFUserSession()
{

   SESSION_SET_ITERATOR sessionIterator = _sessionSet.begin();
   while( _sessionSet.end() != sessionIterator )
   {
      delete (*sessionIterator);
      _sessionSet.erase( sessionIterator );
      sessionIterator = _sessionSet.begin();
   }

   SECURITY_MAP_ITERATOR securityIterator = _securityMap.begin();
   while( _securityMap.end() != securityIterator )
   {
      delete (*securityIterator).second;
      _securityMap.erase( securityIterator );
      securityIterator = _securityMap.begin();
   }

}

//******************************************************************************
const BFSession &
BFUserSession::getSession() const
{
   return(*this);
}

//******************************************************************************
BFSession &
BFUserSession::getSession()
{
   return(*this);
}

//******************************************************************************
bool 
BFUserSession::isSession() const
{
   return(true);
}

//******************************************************************************
const BFUserSession &
BFUserSession::getUserSession() const
{
   return(*this);
}

//******************************************************************************
const BFGlobalSession &
BFUserSession::getGlobalSession() const
{
   return(_globalSession);
}

//******************************************************************************
BFUserSession &
BFUserSession::getUserSession()
{
   return(*this);
}

//******************************************************************************
BFGlobalSession &
BFUserSession::getGlobalSession()
{
   return(_globalSession);
}

//******************************************************************************
const BFSecurity *
BFUserSession::getSecurity(const BFHost &host) const
{
   EXECHISTI( I_( "getSecurity( const BFHost & )" ) );

   SECURITY_MAP_CONST_ITERATOR iterator = _securityMap.find( host.getId() );

   if( _securityMap.end() != iterator )
   {
      return(*iterator).second;
   }

   assert(0);
   // TODO: throw something
   throw;
}

//******************************************************************************
BFSecurity *
BFUserSession::getSecurity(const BFHost &host)
{
   EXECHISTI( I_( "getSecurity( const BFHost & )" ) );
   
   SECURITY_MAP_ITERATOR iterator = _securityMap.find( host.getId() );

   if( _securityMap.end() != iterator )
   {
      return(*iterator).second;
   }

   BFSecurity *security = host.createSecurity();
   _securityMap.insert( SECURITY_MAP_VALUE_TYPE( host.getId(), security ) );

   return(security);
}

//******************************************************************************
void BFUserSession::setClientLocale( const ClientLocale& rLocale )
{
   _clientLocale = rLocale;
   cleanBFPropertyRepository();
   ClientLocaleContext::set( _clientLocale );
}

//******************************************************************************
void 
BFUserSession::setLocale( const BFHost &host )
{
   SECURITY_MAP_ITERATOR iterator = _securityMap.find( host.getId() );

   if( _securityMap.end() != iterator )
   {
      _language = (*iterator).second->getLanguage();
      _clientLocale.setLocale( (*iterator).second->getLocale() );
      ClientLocaleContext::set(_clientLocale);
   }
   // leave unchanged if we are not logged on to the given host.
}

//******************************************************************************
const ClientLocale &
BFUserSession::getClientLocale() const
{
   return(_clientLocale);
}

//******************************************************************************
bool
BFUserSession::isBFWorkSession() const 
{
   return(false);
}

//******************************************************************************
bool
BFUserSession::isBFGlobalSession() const 
{
   return(false);
}

//******************************************************************************
bool
BFUserSession::isBFUserSession() const 
{
   return(true);
}

//******************************************************************************
bool 
BFUserSession::isLoggedOn( const BFHost &host ) const
{

   SECURITY_MAP_CONST_ITERATOR iterator = _securityMap.find( host.getId() );

   if( _securityMap.end() != iterator && ((*iterator).second)->isLoggedOn() )
   {
      return(true);
   }

   return(false);
}

//******************************************************************************
SEVERITY 
BFUserSession::logon( const BFHost &host, DString operatorId, DString password )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION, CLASSNAME, LOGON );

   BFSecurity *security = getSecurity(host);

   if( security->isLoggedOn() )
   {
      return(NO_CONDITION);
   }

   if( security->logon( operatorId, password ) <= WARNING )
   {
      // _language and _clientLocale are update on first logon only...
      if( NULL_STRING == _language )
      {
         _language = security->getLanguage();
         _clientLocale.setLocale( security->getLocale() );
         ClientLocaleContext::set(_clientLocale);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
SEVERITY 
BFUserSession::logoff( const BFHost &host, DString &logoutMessage )
{

   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION, CLASSNAME, LOGOFF );

   BFSecurity *security = getSecurity(host);

   if( !security->isLoggedOn() )
   {
      return(NO_CONDITION);
   }

   security->logoff( logoutMessage );

   return(GETCURRENTHIGHESTSEVERITY( ));

}

//******************************************************************************
SEVERITY 
BFUserSession::changePassword( const BFHost &host, DString password, DString newPassword )
{

   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION, CLASSNAME, CHANGE_PASSWORD );

   BFSecurity *security = getSecurity(host);

   security->changePassword( password, newPassword );

   return(GETCURRENTHIGHESTSEVERITY( ));

}

//******************************************************************************
const DString& 
BFUserSession::getLanguage() const
{
   return(_language);
}

//******************************************************************************
void 
BFUserSession::freeSession(BFSession *session)
{
   SESSION_SET_ITERATOR iterator = _sessionSet.find(session);
   if( _sessionSet.end() != iterator )
   {
      _sessionSet.erase( iterator );
      delete session;
   }

}

//******************************************************************************
void 
BFUserSession::attachSession(BFSession *session)
{
   if( NULL == session || &session->getUserSession() != this )
   {
      assert(0);
      throw;
   }
   _sessionSet.insert(session);

}

//******************************************************************************
const BFUserSession::SESSION_SET& 
BFUserSession::getSessionSet() const
{
   return _sessionSet;

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfcbo/BFUserSession.cpp-arc  $
//
//   Rev 1.17   May 29 2012 11:27:06   if991250
//support for cleaning the BFPropertyRepository on language change
//
//   Rev 1.16   Feb 20 2009 14:48:00   purdyech
//ZTS Revision 6
//
//   Rev 1.15   Oct 22 2004 08:54:28   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.14   May 14 2004 13:24:32   SMITHDAV
//Add a temporary data area to the session objects. This replaces the InterProcessData globale areas.
//
//   Rev 1.13   May 10 2004 13:59:12   SMITHDAV
//Add a member function to return a const reference to the underlying child session set.
// 
//    Rev 1.12   Oct 09 2002 17:40:10   PURDYECH
// New PVCS Database
// 
//    Rev 1.11   Sep 17 2002 16:45:24   PURDYECH
// Added setClientLocale to allow the ClientLocale object to be updated by derived classes.
// 
//    Rev 1.10   Aug 29 2002 12:51:08   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.9   Jun 10 2002 09:31:10   PURDYECH
// Changed initialization of ClientLocale to use ClientLocale::getDefaultClientLocale().
// 
//    Rev 1.8   22 May 2002 17:54:26   PURDYECH
// BFData Implementation
// 
//    Rev 1.7   Aug 16 2001 17:24:42   HUANGSHA
// Temp bug fix
// 
//    Rev 1.6   08 Aug 2001 10:57:14   SMITHDAV
// Made extensive fixes to ClientLocale management.
// 
//    Rev 1.5   Jul 20 2001 16:46:16   HUANGSHA
// fix the setLanguage(..)
// 
//    Rev 1.4   03 Jul 2001 16:22:30   SMITHDAV
// Add revision constants.
// 
//    Rev 1.3   Jun 18 2001 10:22:34   IVESPAUL
// AdminCompany objects now contain twin FastHost objects.
// 
//    Rev 1.2   Jun 13 2001 11:50:56   PURDYECH
// Fixed memory leaks in session deletion logic.
// 
//    Rev 1.1   Jun 06 2001 18:16:16   MCNABBGL
// session changes for fast code
// 
//    Rev 1.0   03 May 2001 14:37:58   SMITHDAV
// Initial revision.
 * 
 */
