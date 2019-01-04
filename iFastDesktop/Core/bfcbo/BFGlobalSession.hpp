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
// ^FILE   : BFGlobalSession.hpp
// ^AUTHOR : David Smith
// ^DATE   :
//
// ^CLASS    : BFGlobalSession
//
// ^CLASS DESCRIPTION :
//
//
//******************************************************************************

#include <srcprag.h>
#include <commonport.h>
#include <bfcbo\bfsession.hpp>
#include <bfcbo\bfcbo.hpp>

class BFUserSession;
class BFSecurity;
class BFHost;

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

class BFBASE_LINKAGE BFGlobalSession : public BFSession, public BFCBO
{
public:
   virtual ~BFGlobalSession() {};

   virtual const BFSession &getSession() const; 
   virtual BFSession &getSession(); 

   virtual bool isSession() const;

   virtual const BFUserSession &getUserSession() const;
   virtual BFUserSession &getUserSession();

   virtual const BFGlobalSession &getGlobalSession() const;
   virtual BFGlobalSession &getGlobalSession();

   virtual const BFSecurity *getSecurity(const BFHost &host) const;

   virtual const ClientLocale &getClientLocale() const;

   virtual bool isBFWorkSession() const;
   virtual bool isBFGlobalSession() const;
   virtual bool isBFUserSession() const;

protected:
//   BFGlobalSession(BFUserSession &userSession);
   BFGlobalSession(BFUserSession &userSession, long workDataSetId);

private:
   BFGlobalSession(); // not implemented
   BFGlobalSession(const BFGlobalSession& copy); // not implemented
   BFUserSession &_userSession;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/BFGlobalSession.hpp-arc  $
//
//   Rev 1.6   May 14 2004 13:24:20   SMITHDAV
//Add a temporary data area to the session objects. This replaces the InterProcessData globale areas.
//
//   Rev 1.5   Oct 09 2002 17:40:04   PURDYECH
//New PVCS Database
//
//   Rev 1.4   Aug 29 2002 12:51:14   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:08:48   PURDYECH
//BFData Implementation
//
//   Rev 1.2   22 Mar 2002 15:11:36   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.1   11 Jul 2001 12:20:44   SMITHDAV
//Fix Global Session cleanup problems.
//
//   Rev 1.0   03 May 2001 14:44:48   SMITHDAV
//Initial revision.
 * 
 */
