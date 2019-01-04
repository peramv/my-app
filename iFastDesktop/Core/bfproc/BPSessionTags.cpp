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
// ^FILE   : BPSessionTags.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 3 Mar 1999
//
// ----------------------------------------------------------
//
// ^CODING COMMENTS  :
//    This file contains the constant character string declarations for
//    the interacting with Session.
//
//    These names are used only by the DSTCCanadaMF application but appear
//    in the Session.ini file.  They are appended here into the namespace
//    "SessionTags"
//
//    The names are defined as const char * so they will be stored with the
//    EXE, and not the run-time data segment (which gets backed up by the
//    swap file). Using const with any type that has a constructor (i.e. string)
//    won't ensure this. #define not only doesn't do this, is also doesn't
//    provide type checking.
//
//    Any variables added to this file will need to be added to BPSessionTags.h
//    as well, as extern definitions.
//
//******************************************************************************

#include "BPGlobal.h"
#include "BPSessionTags.h"

// Macro to assist creating exportable tags for tags where the tag and the value 
// are the same.
#ifdef DST_UNICODE
   #define STTAG( tag ) \
      CLASS_EXPORT const wchar_t * tag = L#tag
#else
   #define STTAG( tag ) \
      CLASS_EXPORT const char *tag = #tag
#endif

namespace SessionTags
{
   // Tags
   STTAG( CallerExtension );
   STTAG( CallerName );
   STTAG( CallerPhoneNumber );
   STTAG( CallerRelationship );
   STTAG( OperatorExtension );
   STTAG( SecondaryExt );
   STTAG( SecondaryPhone );
   STTAG( USERSESSIONID );
   STTAG( WORKSESSIONID );
   STTAG( CallTime );
   STTAG( PhoneAreaCode );
   STTAG( SecondaryAreaCode );
   STTAG( System );

   // Maint Events
   STTAG( ADDRESS_CHANGE );

   // Financial Events
   STTAG( EXCHANGE );

   //TODO These need to be moved to a ConfigTags file
   STTAG( DSTCMFOptions );
   STTAG( Session );             // Config value ??
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/BPSessionTags.cpp-arc  $
 * 
 *    Rev 1.2   Jan 06 2003 16:43:20   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.1   Oct 09 2002 17:40:52   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.0   Feb 15 2000 10:57:34   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:01:52   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

