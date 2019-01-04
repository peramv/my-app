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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

// Disable warning C4018: xxxx : signed/unsigned mismatch to clean up warnings 
//  that the standard template library generates.
// Disable warning C4005 - macro redefinition
// Disable warning C4097 - typedef-name 'x' used as synonym for class-name 'b'...
// Disable warning C4146 - unary minus operator applied to unsigned type...
// Disable warning C4251 - needs to have dll-interface to be used by clients of...
// Disable warning C4663 - C++ language change: to explicitly specialize class
//  template 'x' use...
// Disable warning C4786 - identifier was truncated to '255' characters in the
//  debug information
// These should be cleared periodically to check that our code is not generating
//  these warnings
#pragma warning( disable : 4018 4097 4146 4251 4663 4786 4503 4275 )

#include <commonport.h>
#include <bfproc\bpsessiontags.h>
#include <conditionmanager.hpp>

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif


namespace CND
{
   extern BPBASE_LINKAGE const I_CHAR *BPBASE_CONDITION;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/BPGlobal.h-arc  $
 * 
 *    Rev 1.7   May 14 2004 13:09:26   SMITHDAV
 * Add 4275 to the warning disable list.
 * 
 *    Rev 1.6   Oct 09 2002 17:40:52   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.5   Aug 29 2002 12:51:16   PURDYECH
 * ClientLocale and Field corrections
 * 
 *    Rev 1.4   22 Mar 2002 15:11:48   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.3   Mar 01 2000 12:52:18   DT24433
 * added initial pragma
 * 
 *    Rev 1.2   Feb 29 2000 15:19:50   BUZILA
 * added pragma warning disable 4503
 * 
 *    Rev 1.1   Feb 15 2000 18:54:58   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:46   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Jul 20 1999 11:23:04   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:03:30   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

