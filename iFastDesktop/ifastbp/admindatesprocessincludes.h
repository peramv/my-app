#pragma once
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
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

//******************************************************************************
//
// ^FILE   : AdminDatesProcess.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 06/05/1999
//
// -----------------------------------------------------------------------------


// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by entity here

// Temporarily, defining fields to use

const BFFieldId MOD_DATE(1);
const BFFieldId MOD_USER(2);
const BFFieldId PROCESS_DATE(3);
const BFFieldId PROCESS_USER(4);
const BFFieldId PROCESS_TIME(5);


// Need to define list and search ID's to be used by a GUI object talking to the
// process.


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/admindatesprocessincludes.h-arc  $
 * 
 *    Rev 1.6   Feb 19 2005 18:18:20   hernando
 * PET1117 FN66-68 - Added alternate display; added Process Time.
 * 
 *    Rev 1.5   Mar 21 2003 17:35:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Aug 29 2002 12:51:42   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.3   22 May 2002 18:21:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   19 Mar 2002 13:15:02   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   Feb 15 2000 18:56:12   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:56   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:03:28   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
namespace IFASTBP_PROC
{
}
