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
//******************************************************************************
//
// ^FILE   : DataDictionaryConstants.h
// ^AUTHOR : Jerry Leenerts, modified by Yakov Prager July 12, 1999
// ^DATE   : 2/11/99
//
// ----------------------------------------------------------
//
// ^CODING COMMENTS  :
//    This file contains the external constant character string definitions for
//    data set and field names. The names match the associated string literal.
//
//  These will probably be split out into multiple files to reduce dependencies.
//
//******************************************************************************

// Import/Export resolution

// Macro to assist creating tags
#define CONFIGURATION_CONSTANTS_EXTERN( tag ) \
   extern const I_CHAR * const tag

// Keep groupings in alphabetical order
namespace CONFIGURATION_CONSTANTS
{
   // Common used for view processing
   CONFIGURATION_CONSTANTS_EXTERN( Repeat_Record );

   // Config manager tags
   CONFIGURATION_CONSTANTS_EXTERN( CBO );
   CONFIGURATION_CONSTANTS_EXTERN( DataPath );
   CONFIGURATION_CONSTANTS_EXTERN( MFDSTC );
   CONFIGURATION_CONSTANTS_EXTERN( Path );
   CONFIGURATION_CONSTANTS_EXTERN( SysloadPath );
   CONFIGURATION_CONSTANTS_EXTERN( FYIfile );
   CONFIGURATION_CONSTANTS_EXTERN( Csi );
   CONFIGURATION_CONSTANTS_EXTERN( Configfile );

   // Tags used for logon
   CONFIGURATION_CONSTANTS_EXTERN( NewPassword );
   CONFIGURATION_CONSTANTS_EXTERN( Password );
   CONFIGURATION_CONSTANTS_EXTERN( UserID );

   // Session tags
   CONFIGURATION_CONSTANTS_EXTERN( HLLAPI_BATC );

   // Fields that are non-host specific (used to pass data between classes)
   CONFIGURATION_CONSTANTS_EXTERN( DSTC_MANAGEMENTCOMPANIES );
   CONFIGURATION_CONSTANTS_EXTERN( RTSHost );
   CONFIGURATION_CONSTANTS_EXTERN( RTSHostIP );
   CONFIGURATION_CONSTANTS_EXTERN( RTSHostPort );
   CONFIGURATION_CONSTANTS_EXTERN( VMHostName );
   CONFIGURATION_CONSTANTS_EXTERN( Type );
   CONFIGURATION_CONSTANTS_EXTERN( Param );
   CONFIGURATION_CONSTANTS_EXTERN( Host );

   CONFIGURATION_CONSTANTS_EXTERN( SMQBrokerURLs );
   CONFIGURATION_CONSTANTS_EXTERN( SMQSingleQueue );
   CONFIGURATION_CONSTANTS_EXTERN( SMQMultiQueue );
   CONFIGURATION_CONSTANTS_EXTERN( SMQWorkEventTopicPrefix );
   CONFIGURATION_CONSTANTS_EXTERN( SMQWorkEventReplyTopic );
   CONFIGURATION_CONSTANTS_EXTERN( SMQWorkAgentKeepAliveTopic );
   CONFIGURATION_CONSTANTS_EXTERN( SMQUser );
   CONFIGURATION_CONSTANTS_EXTERN( SMQPassword );
   CONFIGURATION_CONSTANTS_EXTERN( SMQWaitTimeout );

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ConfigurationConstants.h-arc  $
 * 
 *    Rev 1.12   Jun 05 2009 08:48:04   purdyech
 * Fixed names of SonicSingle and SonicMulti queues in configuration.
 * SonicErrorMessages are now handled appropriately.
 * 
 *    Rev 1.11   Feb 17 2009 07:11:30   purdyech
 * Added SMQWaitTimeout for ZTS
 * 
 *    Rev 1.10   Feb 06 2009 14:55:40   purdyech
 * Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
 * 
 *    Rev 1.9   Jun 17 2008 16:00:56   smithdav
 * Add SonicConnection support
 * 
 *    Rev 1.8   Jun 08 2006 14:07:58   fengyong
 * Add guiconfig
 * 
 *    Rev 1.7   Nov 24 2003 16:02:12   HSUCHIN
 * PTS 10020087 - Add Host constant
 * 
 *    Rev 1.6   Oct 09 2002 23:55:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Sep 20 2002 15:23:28   SMITHDAV
 * Changes to support multiple Csi configurations for mutliple instances of desktops.
 * 
 *    Rev 1.4   Jul 05 2002 08:49:10   PURDYECH
 * Removed #pragma message
 * 
 *    Rev 1.3   22 Mar 2002 15:11:50   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.2   Feb 12 2001 15:22:20   HSUCHIN
 * added three new constants to access info from registry 
 * 
 *    Rev 1.1   Feb 15 2000 18:55:00   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:48   SMITHDAV
 * Initial revision.
// 
//    Rev 1.2   Aug 10 1999 11:19:36   BUZILA
// added support for configuring FYI screen's start page
// 
//    Rev 1.1   Jul 12 1999 17:29:02   PRAGERYA
// SysLoad implementation
// 
//    Rev 1.0   Jul 12 1999 11:47:20   PRAGERYA
// Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:03:40   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
