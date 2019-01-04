#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif

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
// ^FILE   : BFUserSession.hpp
// ^AUTHOR : David Smith
// ^DATE   :
//
// ^CLASS    : BFUserSession
//
// ^CLASS DESCRIPTION :
//
//
//******************************************************************************

#include <srcprag.h>
#include <commonport.h>
#include <condition.hpp>
#include <bfcbo\bfsession.hpp>
#include <bfcbo\bfcbo.hpp>
#include <clientlocale.hpp>
#include <map>
#include <set>
#include <assert.h>

class BFGlobalSession;
class BFWorkSession;
class BFSecurity;
class BFHost;
class DString;

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

class BFBASE_LINKAGE BFUserSession : public BFSession, public BFCBO
{
public:
   virtual ~BFUserSession();

   virtual const BFSession &getSession() const; 
   virtual BFSession &getSession(); 

   virtual bool isSession() const;

   virtual const BFUserSession &getUserSession() const;
   virtual BFUserSession &getUserSession();

   virtual const BFGlobalSession &getGlobalSession() const;
   virtual BFGlobalSession &getGlobalSession();

   virtual const BFSecurity *getSecurity( const BFHost &host ) const;

   virtual const ClientLocale &getClientLocale() const;

   virtual bool isBFWorkSession() const;
   virtual bool isBFGlobalSession() const;
   virtual bool isBFUserSession() const;

   bool isLoggedOn( const BFHost &host ) const;
   SEVERITY logon( const BFHost &host, DString operatorId, DString password );
   SEVERITY logoff( const BFHost &host, DString &logoutMessage );
   SEVERITY changePassword( const BFHost &host, DString password, DString newPassword );

   const DString& getLanguage() const;

   void freeSession( BFSession *session );

protected:
//   BFUserSession(BFGlobalSession &globalSession);
   BFUserSession(BFGlobalSession &globalSession, long workDataSetId);

   void attachSession( BFSession *session );

   BFSecurity *getSecurity( const BFHost &host );
   void setLocale( const BFHost &host );
   void setClientLocale( const ClientLocale& rLocale );

   typedef std::set< BFSession * >  SESSION_SET;
#if _MSC_VER >= 1300
   typedef SESSION_SET::const_iterator SESSION_SET_CONST_ITERATOR;
#else
   typedef SESSION_SET::iterator SESSION_SET_CONST_ITERATOR;
#endif
   typedef SESSION_SET::iterator SESSION_SET_ITERATOR;
   const SESSION_SET& getSessionSet() const;

private:
   BFUserSession(); // not implemented
   BFUserSession( const BFUserSession& copy ); // not implemented

   BFGlobalSession &_globalSession;
   ClientLocale _clientLocale;
   DString _language;

   typedef std::map< DString, BFSecurity * >  SECURITY_MAP;
   typedef SECURITY_MAP::iterator SECURITY_MAP_ITERATOR;
#if _MSC_VER >= 1300
   typedef SECURITY_MAP::const_iterator SECURITY_MAP_CONST_ITERATOR;
#else
   typedef SECURITY_MAP::iterator SECURITY_MAP_CONST_ITERATOR;
#endif
   typedef SECURITY_MAP::value_type SECURITY_MAP_VALUE_TYPE;
   SECURITY_MAP _securityMap;

   SESSION_SET _sessionSet;

   friend BFGlobalSession;
   friend BFWorkSession;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/BFUserSession.hpp-arc  $
//
//   Rev 1.12   Nov 14 2004 16:23:02   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.11   Oct 22 2004 08:54:30   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.10   May 14 2004 13:24:34   SMITHDAV
//Add a temporary data area to the session objects. This replaces the InterProcessData globale areas.
//
//   Rev 1.9   May 10 2004 13:59:02   SMITHDAV
//Add a member function to return a const reference to the underlying child session set.
//
//   Rev 1.8   Oct 09 2002 17:40:10   PURDYECH
//New PVCS Database
//
//   Rev 1.7   Sep 17 2002 16:45:24   PURDYECH
//Added setClientLocale to allow the ClientLocale object to be updated by derived classes.
//
//   Rev 1.6   Aug 29 2002 12:51:16   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   22 May 2002 18:08:50   PURDYECH
//BFData Implementation
//
//   Rev 1.4   22 Mar 2002 15:11:46   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.3   08 Aug 2001 10:56:50   SMITHDAV
//Made extensive fixes to ClientLocale management.
//
//   Rev 1.2   Jun 18 2001 10:23:40   IVESPAUL
//AdminCompany objects now contain twin FastHost objects.
//
//   Rev 1.1   Jun 06 2001 18:16:14   MCNABBGL
//session changes for fast code
//
//   Rev 1.0   03 May 2001 14:44:50   SMITHDAV
//Initial revision.
 * 
 */
