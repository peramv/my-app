#pragma once





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
// ^FILE   : DSTCHost.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : DSTCHost
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include <win32\platform.h>
///#endif

#include <DString.hpp>
///#endif

#include <bfdbrkr\BFHost.hpp>
///#endif

// Import/Export resolution
#undef IFASTDBRKR_LINKAGE
#ifdef IFASTDBRKR_DLL
   #define IFASTDBRKR_LINKAGE CLASS_EXPORT
#else
   #define IFASTDBRKR_LINKAGE CLASS_IMPORT
#endif

class IFASTDBRKR_LINKAGE DSTCHost : public BFHost
{
public:
   DSTCHost(const DString &id);
   virtual ~DSTCHost();

   virtual const DString &getId() const;
   virtual BFSecurity *createSecurity() const;

   static void setPrimaryHost(const DString &id);
   static void setBackupHost(const DString &id);
   static const DSTCHost &getPrimaryHost();
   static const DSTCHost &getBackupHost();

private:
   DSTCHost(); // not implemented

   const DString  _id;

   static DSTCHost *_primaryHost;
   static DSTCHost *_backupHost;
};


///#endif // 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCHost.hpp-arc  $
//
//   Rev 1.5   Nov 14 2004 15:00:02   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Oct 09 2002 23:55:22   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   22 May 2002 18:21:22   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:15:36   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   03 May 2001 14:04:02   SMITHDAV
//Session management restructuring.
//
//   Rev 1.0   23 Oct 2000 20:34:34   SMITHDAV
//Initial revision.
*/