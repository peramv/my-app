#pragma once

#include <bfutil\bfcritsec.hpp>

class DSTCUserSession;

class PersistentUserSessionException
{
};

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE PersistentUserSession  
{
public:
   static DSTCUserSession* getInstance();
   static DSTCUserSession* getInstance( const DString& userid,
                                        const DString& password );
   static void killInstance();

protected:
   PersistentUserSession( const DString& userid, const DString& password );
   ~PersistentUserSession();

   DSTCUserSession* _instance;

   static PersistentUserSession* s_instance;
   static BFCritSec s_cs;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   D:/scc/ifds/ifast/archives/ifastbp/persistentusersession.hpp-arc  $
//
//   Rev 1.3   Oct 09 2002 23:53:32   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   22 May 2002 18:20:18   PURDYECH
//BFData Implementation
//
//   Rev 1.1   19 Mar 2002 13:18:04   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   17 Jul 2001 11:40:20   PURDYECH
//Initial revision.
//
