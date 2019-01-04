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
// ^FILE   :  BFConnectionManager.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  March 2000
//
// ----------------------------------------------------------
#include <srcprag.h>
#include "SonicConnectionFactory.hpp"
#include "SonicConnection.hpp"
#include <bf/log/log.hpp>
#include <configmanager.hpp>

namespace
{
   const I_CHAR *CLASSNAME = I_( "SonicConnectionFactory" );
}

namespace ifds {
   const DString& getAppVersion();
}

SonicConnectionFactory::SonicConnectionFactory( const DString& brokerURLs, 
                                                const DString& singleQueue,
                                                const DString& multiQueue,
                                                const DString& ldapQueue,
                                                const DString& awdQueue,
                                                const DString& user, 
                                                const DString& password,
                                                int cMaxUses,
                                                int iTimeout,
                                                const DString& dstrCswAcl )
: brokerURLs_(brokerURLs)
, singleQueue_(singleQueue)
, multiQueue_(multiQueue)
, ldapQueue_( ldapQueue )
, awdQueue_( awdQueue )
, cMaxUses_( cMaxUses )
, user_( user )
, password_( password )
, iTimeout_( iTimeout )
, connFactory_( null )
, dstrCswAcl_( dstrCswAcl )
{
   if( dstrCswAcl_ == I_("") ) {
      dstrCswAcl_ = I_("cswacl");
   }

   if( GetConfigValueAsBool(I_("RTSHost"), I_("UseSingleSonicConnection") ) ) {
      I_CHAR szConnID[512] = {0};

      const I_CHAR* pszUser = i_getenv(I_("USERNAME"));

      char szHostName[256];
      gethostname( szHostName, sizeof(szHostName)/sizeof(szHostName[0]) );
      DString dstrHostName = DStringA(szHostName);

      DWORD dwProcessId = GetCurrentProcessId();
 
      // Get AppVersion, but convert all non-alpha, non-digits, and non-dots to
      // underscore.  This prevents invalid characters from showing up in the 
      // connection name
      int cb = ifds::getAppVersion().length();
      I_CHAR* pszVer = new I_CHAR[cb + 1];
      i_strcpy(pszVer, ifds::getAppVersion().c_str());
      for( int i = 0; i < cb; ++i ) {
         if( !i_isalnum(pszVer[i]) && I_('.') != pszVer[i]) {
            pszVer[i] = I_('_');
         }
      }

      
      i_sprintf(szConnID, I_("mfdstc_%s_%s_%06d_%s"),
                pszUser,               // LAN username
                dstrHostName.c_str(),  // ComputerName
                dwProcessId,           // PID
                pszVer );     
      
      delete[] pszVer;

      connFactory_ = createQueueConnectionFactory( null,
                                                   createString(szConnID),
                                                   createString(user_.c_str()), 
                                                   createString(password.c_str()) );
   }
   else {
      connFactory_ = createQueueConnectionFactory( null, 
                                                   createString(user_.c_str()), 
                                                   createString(password.c_str()) );
   }
   connFactory_->setFaultTolerant(jtrue);
   connFactory_->setConnectionURLs( createString(brokerURLs_.c_str()) );
}

SonicConnectionFactory::~SonicConnectionFactory()
{
}

BFConnection *
SonicConnectionFactory::createConnection(const DStringA &hostId)
{
   bf::log::LogStream ls( bf::log::databroker );
   ls << bf::log::information;
   ls << I_("Creating new SonicConnection") << bf::log::endlf;
   return( new SonicConnection( hostId, 
                                "SonicConnection", 
                                connFactory_, 
                                singleQueue_,
                                multiQueue_,
                                ldapQueue_,
                                awdQueue_,
                                cMaxUses_, 
                                iTimeout_,
                                dstrCswAcl_ ) );
}

void
SonicConnectionFactory::destroyConnection(BFConnection *connection)
{
   if( NULL == connection )
      return;

   bf::log::LogStream ls( bf::log::databroker );
   ls << bf::log::information;
   ls << I_("Destroying SonicConnection") << bf::log::endlf;

   SonicConnection *smqConnection = dynamic_cast<SonicConnection *> (connection);
   delete smqConnection;
}

void SonicConnectionFactory::setTimeout( int iTimeout )
{
   iTimeout_ = iTimeout;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/SonicConnectionFactory.cpp-arc  $
// 
//    Rev 1.8   May 03 2010 04:50:30   purdyech
// IN2107238 - Support for named single connection to SonicMQ
// 
//    Rev 1.7   Jan 06 2010 13:58:32   purdyech
// Store SMQ password to allow SMQTest to be used from AboutSonicPropPage
// 
//    Rev 1.6   Aug 03 2009 23:14:02   purdyech
// LDAP Integration Pieces
// 
//    Rev 1.5   Jun 05 2009 08:29:24   purdyech
// Fixed names of SonicSingle and SonicMulti queues in configuration.
// SonicErrorMessages are now handled appropriately.
// 
//    Rev 1.4   May 25 2009 08:53:38   purdyech
// Set CswAcl to default of 'cswacl' if not specified.
// 
//    Rev 1.3   May 01 2009 09:26:40   purdyech
// Add support to customize CswAcl property value
// 
//    Rev 1.2   Feb 27 2009 08:49:52   purdyech
// ZTS Fixes prior to User Experience Test
// 
//    Rev 1.1   Feb 06 2009 14:52:56   purdyech
// Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
// 
//    Rev 1.0   Jun 17 2008 15:55:28   smithdav
// Initial revision.
// 
// 
//
*/