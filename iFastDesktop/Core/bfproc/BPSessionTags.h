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
//
// ^FILE   : BPSessionTags.h
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 3 Mar 1999
//
// ----------------------------------------------------------
//
// ^CODING COMMENTS  :
//    This file contains the external constant character string definitions for
//    tags passed to Session which appear in the Session.ini file.
//
//******************************************************************************

#include <sessiontags.h>

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

// Macro to assist creating extern tags
#define STEXTERN( tag ) \
   extern BPBASE_LINKAGE const I_CHAR *tag

namespace SessionTags
{
   // Tags
   STEXTERN( CallerExtension );
   STEXTERN( CallerName );
   STEXTERN( CallerPhoneNumber );
   STEXTERN( CallerRelationship );
   STEXTERN( OperatorExtension );
   STEXTERN( DSTCMFOptions );
   STEXTERN( SecondaryExt );
   STEXTERN( SecondaryPhone );
   STEXTERN( Session );
   STEXTERN( USERSESSIONID );
   STEXTERN( WORKSESSIONID );
   STEXTERN( CallTime );
   STEXTERN( PhoneAreaCode );
   STEXTERN( SecondaryAreaCode );
   STEXTERN( System );

   // Maint Events
   STEXTERN( ADDRESS_CHANGE ); 

   // Financial Events
   STEXTERN( EXCHANGE );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfproc/BPSessionTags.h-arc  $
 * 
 *    Rev 1.3   Oct 09 2002 17:40:52   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   22 Mar 2002 15:11:48   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.1   Feb 15 2000 18:54:58   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:46   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:03:32   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
