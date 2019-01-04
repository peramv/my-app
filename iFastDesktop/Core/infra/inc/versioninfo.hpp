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

   VersionInfo( DString & inFilename );
   virtual ~VersionInfo();

   DString getProductVersion() const
   {
      return productVersionInfo;
   }

   DString getFileVersion() const
   {
      return fileVersionInfo;
   }

   static DString & getVersionString( DString & inFileName,
                                      DString & msgOut );

private:
   VersionInfo();
   VersionInfo( const VersionInfo & );
   const VersionInfo & operator=( const VersionInfo & );

private:

   DString productVersionInfo;
   DString fileVersionInfo;
};

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/inc/versioninfo.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:18   kovacsro
//Initial revision.
//
//   Rev 1.2   23 Jan 2002 13:40:38   dt14177
//fixed memory leak and Unicode compile
//problem
//
//   Rev 1.1   22 Jan 2002 16:18:24   dt14177
//added getVersionString()
//
//   Rev 1.0   19 Mar 2001 15:14:26   DT14177
// 

#endif // PRODUCTVERSIONINFO_HPP
