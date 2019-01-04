#include "stdafx.h"
#include "persistentusersession.hpp"
#include <ifastcbo\dstcusersession.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>
#include <ifastcbo\dstcglobalsession.hpp>
#include <bfutil\bfguard.hpp>
#include <ifastdbrkr\dstchost.hpp>
#include <bf/log/log.hpp>

PersistentUserSession* PersistentUserSession::s_instance = NULL;
BFCritSec PersistentUserSession::s_cs;

DSTCUserSession* PersistentUserSession::getInstance( const DString& userid,
                                                     const DString& password )
{
   BFGuard g( s_cs );
   if( NULL == s_instance )
   {
      try
      {
         s_instance = new PersistentUserSession( userid, password );
      }
      catch( PersistentUserSessionException& )
      {
         delete s_instance;
         s_instance = NULL;
         return( NULL );
      }
   }
   return( s_instance->_instance );
}


DSTCUserSession* PersistentUserSession::getInstance()
{
   {
      BFGuard g( s_cs );
      if( NULL != s_instance )
      {
         return( s_instance->_instance );
      }
   }

   return( NULL );
}

void PersistentUserSession::killInstance()
{
   BFGuard g( s_cs );
   delete s_instance;
   s_instance = NULL;
}

PersistentUserSession::PersistentUserSession( const DString& userid,
                                              const DString& password )
: _instance( NULL )
{
   MAKEFRAMECONSTRUCTOR2( CND::IFASTBP_CONDITION, I_( "PersistentUserSession" ), I_( "PersistentUserSession" ) );

   bf::log::LogStream ls( bf::log::cbo );
   ls << bf::log::information << I_( "Creating persistent user session for " ) << userid << bf::log::endlf;

   // create a user session which will be the one and only persistent user session
   _instance = new DSTCUserSession();

   // logon using the special admin account
   SEVERITY sev = _instance->logon( DSTCHost::getPrimaryHost(), userid, password );
   if( sev <= WARNING )
   {
      // if we logged on Ok then retrieve all MgmtCo information.
      const DSTCUserSession* pUS = _instance;
      const DSTCSecurity* pSecurity = dynamic_cast< const DSTCSecurity* >(pUS->getSecurity( DSTCHost::getPrimaryHost() ) );
      int cMgmtCo = pSecurity->getNumberOfCompanies();
      int iMgmtCo;

      DString dstrCompanyId;
      DString dstrCompanyName;

      for( iMgmtCo = 0; iMgmtCo < cMgmtCo; ++iMgmtCo )
      {
         pSecurity->getCompanyInfo( iMgmtCo, dstrCompanyId, dstrCompanyName );
         dynamic_cast< DSTCGlobalSession&>(_instance->getGlobalSession()).refreshMgmtCo( dstrCompanyId );
      }
   }
   else
   {
      // failure to logon ...log the error 
      ls << bf::log::severe << I_( "Failed to create persistent user session for " ) << userid << bf::log::endlf;

      PROMOTECONDITIONS();
      Frame *frame = MYFRAME();
      frame->packConditions();
      int count = frame->getCount(  );
      for( int i = 0; i < count; i++ )
      {
         Condition *cnd = frame->getCondition( i );
         cnd->prepareMessage( ClientLocaleContext::get() );
         ls << bf::log::severe << I_( "Error creating persitent user session for " ) 
                               << userid 
                               << I_( ": [" )
                               << cnd->getComponentName() 
                               << I_( " - " )
                               << cnd->getCode() 
                               << I_( "] " )
                               << cnd->getMessage()
                               << bf::log::endlf;
      }
      ls.flush();

      
      // ... throw an exception
      throw PersistentUserSessionException();
   }
}

PersistentUserSession::~PersistentUserSession()
{
   delete _instance;
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/persistentusersession.cpp-arc  $
// 
//    Rev 1.4   Sep 16 2005 11:42:24   popescu
// Incident# 393028 - With this fix the logon errors are trapped and the persistent user session is not created. Hence, the BPServer exits gracefully.
// 
//    Rev 1.3   Oct 09 2002 23:53:32   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Aug 29 2002 12:54:36   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.1   30 Jul 2001 15:15:02   SMITHDAV
// Allow the Mgmt Co refresh loop to continue for subsequent Mgmt Co's after a error occurs in one.
// 
//    Rev 1.0   17 Jul 2001 11:40:02   PURDYECH
// Initial revision.
// 
//    Rev 1.3   16 Jul 2001 15:30:44   SMITHDAV
// Added error handling on refresh.
// 
//    Rev 1.2   09 Jul 2001 15:25:14   SMITHDAV
// Mgmt company refresh related changes.
// 
//    Rev 1.1   03 Jul 2001 16:53:40   PURDYECH
// Infrastructure Release 1.9 Fixes.
// 
//    Rev 1.0   Jun 26 2001 16:09:44   PURDYECH
// Initial revision.
//
