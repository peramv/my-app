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
//******************************************************************************
//
// ^FILE   : DataDictionaryConstants.cpp
// ^AUTHOR : Jerry Leenerts, modified by Yakov Prager July 12, 1999
// ^DATE   : 2/11/99
//
// ----------------------------------------------------------
//
// ^CODING COMMENTS  :
//
//    NOTE: This file will ultimately be created from the DataDictionary as part
//     of the build process
//
//    This file contains the constant character string declarations for
//    the data set and field names.
//
//    The names are defined in the namespace DD to keep them out of the
//    global name space, to avoid conflicts with duplicate names.
//
//    The names are defined as const char * so they won't be stored in the  data
//    segment (which gets backed up by the swap file). Using const with any type
//    that has a constructor (i.e. string) won't ensure this. #define not only 
//    doesn't do this, it also doesn't provide type checking.
//
//    Any variables added to this file will need to be added to DataDictionary.h
//    as well, as extern definitions.
//
//
//******************************************************************************

// This file needs to be part of a lower layer where it will be shared by 
// Infrastructure on up.
#include "stdafx.h"
#include "configurationconstants.h"

// Macro to assist creating exportable tags for tags where the tag and the value 
// are the same.
#ifdef DST_UNICODE
   #define CONFIGURATION_CONSTANTS_TAG( tag ) \
      const wchar_t * const tag = L#tag
#else
   #define CONFIGURATION_CONSTANTS_TAG( tag ) \
      const char * const tag = #tag
#endif

// Keep groupings in alphabetical order

namespace CONFIGURATION_CONSTANTS
{
   // Common used for view processing
   CONFIGURATION_CONSTANTS_TAG( Repeat_Record );

   // Config manager tags
   CONFIGURATION_CONSTANTS_TAG( CBO );
   CONFIGURATION_CONSTANTS_TAG( DataPath );
   CONFIGURATION_CONSTANTS_TAG( MFDSTC );
   CONFIGURATION_CONSTANTS_TAG( Path );
   CONFIGURATION_CONSTANTS_TAG( SysloadPath );
   CONFIGURATION_CONSTANTS_TAG( FYIfile );
   CONFIGURATION_CONSTANTS_TAG( Csi );
   CONFIGURATION_CONSTANTS_TAG( Configfile );

   // Field used for logon
   CONFIGURATION_CONSTANTS_TAG( NewPassword );
   CONFIGURATION_CONSTANTS_TAG( Password );
   CONFIGURATION_CONSTANTS_TAG( UserID );

   // Session tags
   CONFIGURATION_CONSTANTS_TAG( HLLAPI_BATC );

   // Fields that are non-host specific (used to pass data between classes)
   CONFIGURATION_CONSTANTS_TAG( DSTC_MANAGEMENTCOMPANIES );
   CONFIGURATION_CONSTANTS_TAG( RTSHost );
   CONFIGURATION_CONSTANTS_TAG( RTSHostIP );
   CONFIGURATION_CONSTANTS_TAG( RTSHostPort );
   CONFIGURATION_CONSTANTS_TAG( VMHostName );
   CONFIGURATION_CONSTANTS_TAG( Type );
   CONFIGURATION_CONSTANTS_TAG( Param );
   CONFIGURATION_CONSTANTS_TAG( Host );

   CONFIGURATION_CONSTANTS_TAG( SMQBrokerURLs );
   CONFIGURATION_CONSTANTS_TAG( SMQSingleQueue );
   CONFIGURATION_CONSTANTS_TAG( SMQMultiQueue );
   CONFIGURATION_CONSTANTS_TAG( SMQWorkEventTopicPrefix );
   CONFIGURATION_CONSTANTS_TAG( SMQWorkEventReplyTopic );
   CONFIGURATION_CONSTANTS_TAG( SMQWorkAgentKeepAliveTopic );
   CONFIGURATION_CONSTANTS_TAG( SMQUser );
   CONFIGURATION_CONSTANTS_TAG( SMQPassword );
   CONFIGURATION_CONSTANTS_TAG( SMQWaitTimeout );

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ConfigurationConstants.cpp-arc  $
 * 
 *    Rev 1.10   Jun 05 2009 08:46:44   purdyech
 * Fixed names of SonicSingle and SonicMulti queues in configuration.
 * SonicErrorMessages are now handled appropriately.
 * 
 *    Rev 1.9   Feb 17 2009 07:10:10   purdyech
 * Added SMQWaitTimeout for ZTS
 * 
 *    Rev 1.8   Feb 06 2009 14:55:48   purdyech
 * Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
 * 
 *    Rev 1.7   Jun 17 2008 16:00:52   smithdav
 * Add SonicConnection support
 * 
 *    Rev 1.6   Jun 08 2006 14:07:48   fengyong
 * Add guiconfig
 * 
 *    Rev 1.5   Nov 24 2003 16:02:08   HSUCHIN
 * PTS 10020087 - Add Host constant
 * 
 *    Rev 1.4   Oct 09 2002 23:55:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   Sep 20 2002 15:23:26   SMITHDAV
 * Changes to support multiple Csi configurations for mutliple instances of desktops.
 * 
 *    Rev 1.2   Jul 05 2002 10:33:36   PURDYECH
 * include file cleanup
 * 
 *    Rev 1.1   Feb 12 2001 15:22:16   HSUCHIN
 * added three new constants to access info from registry 
 * 
 *    Rev 1.0   Feb 15 2000 10:59:50   SMITHDAV
 * Initial revision.
// 
//    Rev 1.2   Aug 10 1999 11:19:38   BUZILA
// added support for configuring FYI screen's start page
// 
//    Rev 1.1   Jul 12 1999 17:28:14   PRAGERYA
// 
//    Rev 1.0   Jul 12 1999 11:45:00   PRAGERYA
// Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:02:00   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
