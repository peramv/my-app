#ifndef PRODUCTVERSIONINFO_HPP
#define PRODUCTVERSIONINFO_HPP

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2001 by DST Systems, Inc.
 */

/**@pkg DICORE */    


#pragma message( "including "__FILE__ )

/**
 * This is a very low-level class that gets a DLL product version
 * string.
 */

#include "srcprag.h"

#ifndef STDINCLUDE_H
   #include "stdinclude.h"
#endif

#include "diport.h"

#ifndef MBCTYPE_H
#include <mbctype.h>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class DICORE_LINKAGE VersionInfo
{
public:

   VersionInfo( const char * const inFilename );
   virtual ~VersionInfo();

   const char * const getProductVersion () const
   {
      return productVersionInfo;
   }

   const char * const getFileVersion () const
   {
      return fileVersionInfo;
   }

private:
   VersionInfo();
   VersionInfo( const VersionInfo & );
   const VersionInfo & operator=( const VersionInfo & );

private:

   char * productVersionInfo;
   char * fileVersionInfo;
};

//**********************************************************************
//              Revision Control Entries
//**********************************************************************
//
// $Log:   Y:/VCS/DSTCProjects/3rdParty/infra/inc/win32/versioninfo.hpp-arc  $
//
//   Rev 1.0   Jul 05 2002 10:15:28   SMITHDAV
//Initial revision.
//
//   Rev 1.0   19 Mar 2001 15:14:26   DT14177
// 

#endif // PRODUCTVERSIONINFO_HPP
