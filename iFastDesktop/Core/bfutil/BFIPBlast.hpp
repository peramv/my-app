#pragma once

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

#include <iosfwd>
#include <dstring.hpp>
#include <bfutil\bfcritsec.hpp>
#include <map>

// class to write BFIPBlast files
class BFUTIL_LINKAGE BFIPBlast
{
private:
   BFIPBlast();
   ~BFIPBlast();


public:
   static BFIPBlast* getInstance();
   static void killInstance();

   int setFile( const char *pszFile );

   int writeBuffer( const DString &name, const DString &buffer );

private:
   static BFIPBlast *s_pInstance_;

   DStringA          fileName_;
   std::ofstream     *pFile_;

   BFCritSec         cs_;        // synchronize write access to the file

   int               iBuf_;      // index of buffer

   typedef std::multimap< DStringA, DStringA > TXNMAP;  // transaction_name, buffer_name
   typedef TXNMAP::iterator TXNMAP_ITER;

   TXNMAP mapTxn_;

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFIPBlast.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 17:41:16   PURDYECH
//New PVCS Database
//
//   Rev 1.1   22 Mar 2002 15:11:38   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.0   06 Sep 2001 20:54:18   PURDYECH
//Initial revision.
//
