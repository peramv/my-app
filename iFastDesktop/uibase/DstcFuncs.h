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
//
// ^FILE   : DstcFuncs.h
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 6/18/97
//
// ^DESCRIPTION : This file contains general helper functions.
//
//******************************************************************************

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

DString WIN32UIBASE_LINKAGE &stripComplete( DString &str );

/** 
  * This method sets the date from a string in host format into a COleDateTime
  * object.
  * @param dateOut - COleDateTime to hold the converted string
  * @param strHost - DString (which will have trailing spaces stripped) of date in
  * host format to convert
  * @returns an int with 0 being the set worked
  */
int WIN32UIBASE_LINKAGE setOleDateFromHost( COleDateTime &dateOut, DString &strHost, DString Type = I_("D") );





//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DstcFuncs.h-arc  $
 * 
 *    Rev 1.6   Jul 06 2005 13:57:58   hernando
 * PET1250 FN01 - Added support for time.
 * 
 *    Rev 1.5   Nov 27 2002 15:05:38   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.4   Oct 09 2002 17:42:40   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.3   Sep 20 2002 15:19:24   SMITHDAV
 * Remove unused function.
 * 
 *    Rev 1.2   19 Mar 2002 13:36:18   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   Feb 15 2000 18:58:52   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:00:58   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.3   Dec 21 1999 14:37:06   YINGBAOL
 * 
 *    Rev 1.2   Sep 01 1999 11:53:16   DT24433
 * added setOleDateFromHost
 * 
 *    Rev 1.1   Jul 08 1999 10:05:00   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
