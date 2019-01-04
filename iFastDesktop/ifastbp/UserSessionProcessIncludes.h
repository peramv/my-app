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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.
#include <ifastdataimpl\dse_dstc0001_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

const BFFieldId USERID( 1 );
const BFFieldId PASSWORD( 2 );
const BFFieldId NEWPASSWORD( 3 );
const BFFieldId SYSTMGMTS( 4 );
const BFFieldId LANGUAGE( 5 );
//CP20030319const int MGMT_COMPANIES_LIST = 6;
const BFFieldId MGMTCONAME( 7 );
const BFFieldId AWDPROFILE ( 8 );
const BFFieldId CURRENT_COMPANY_NDX( 9 );
const BFFieldId SESSIONID ( 10 );
const BFFieldId ACCESSALLSLSREP( 11 );
const BFFieldId CLIENTID( 12 );
const BFFieldId CHANGE_AWDPROFILE ( 13 );
const BFFieldId CHANGE_MGT_COMPANY ( 14 );
const BFFieldId CLIENTNAME( 15 );
const BFFieldId XMLCONFIGFILE( 16 );


#define STARTSESSION I_( "STARTSESSION" )

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MGMT_COMPANIES_LIST;
}
namespace USERSESSION
{
   extern IFASTBP_LINKAGE const I_CHAR * const NEWSESSION;
   extern IFASTBP_LINKAGE const I_CHAR * const YES;
   extern IFASTBP_LINKAGE const I_CHAR * const NO;

}

// Need to define list and search ID's to be used by a GUI object talking to the
// process.


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/UserSessionProcessIncludes.h-arc  $
 * 
 *    Rev 1.13   Sep 19 2011 14:48:16   dchatcha
 * Usability Improvement on iFAST/Desktop
 * 
 *    Rev 1.12   Dec 22 2009 06:14:00   dchatcha
 * IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
 * 
 *    Rev 1.11   May 08 2004 13:28:18   YINGBAOL
 * PTS10029514:AWD Container disappears when Mgmt Co changed
 * 
 *    Rev 1.10   Mar 21 2003 17:49:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Mar 07 2003 11:59:44   PURDYECH
 * Change MGMT_COMPANIES_LIST from a BFFieldId to a const int.  The symbol is used as a idContainer, not a field.
 * 
 *    Rev 1.8   Oct 09 2002 23:53:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:54:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   22 May 2002 18:18:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:20:14   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   Sep 20 2001 10:56:00   HUANGSHA
 * Added the CLIENTID
 * 
 *    Rev 1.3   Jul 26 2000 11:45:48   VASILEAD
 * Added AccessAllSlsRep field in logon transaction
 * 
 *    Rev 1.2   Jul 25 2000 11:52:38   YINGZ
 * take out logon off for the existing user
 * 
 *    Rev 1.1   Feb 15 2000 18:57:06   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:28   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.3   Dec 13 1999 14:15:38   DT24433
 * added constant
 * 
 *    Rev 1.2   13 Dec 1999 09:33:08   HSUCHIN
 * added USERSESSION namespace
 * 
 *    Rev 1.1   Jul 08 1999 10:04:04   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
