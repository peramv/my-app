#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//    AUTHOR : Mihai Virgil Buzila
//    DATE   : 16/04/99
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0088_vw.hpp>
#include <ifastdataimpl\dse_dstc0088_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId GROUP_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
}
namespace SHRPROC
{
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const GROUP_CODE;

   const BFFieldId CREATING_SHAREHOLDER(1);
   const BFFieldId SHAREHOLDER_NUM_FIELD(2);

   // Need to define list and search Id's to be used by a GUI object talking to the
   // process.
//CP20030319   const int SHAREHOLDER_CBO = 1;
//CP20030319   const int MFACCOUNT_CBO = 2;
//CP20030319   const int GROUP_LIST = 3;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ShareholderProcessIncludes.h-arc  $
 * 
 *    Rev 1.8   Feb 07 2012 18:09:28   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.7   Mar 21 2003 17:48:12   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:53:38   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Aug 29 2002 12:53:40   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 18:20:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:18:30   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Oct 11 2000 11:55:10   VASILEAD
 * Added server updates support
 * 
 *    Rev 1.1   Feb 15 2000 18:56:48   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:22   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.14   Jan 17 2000 14:00:16   POPESCUS
 * support for refresh and misc
 * 
 *    Rev 1.13   Nov 29 1999 11:26:50   POPESCUS
 * Fixes in NASU flow
 * 
 *    Rev 1.12   Nov 25 1999 17:08:58   POPESCUS
 * 
 *    Rev 1.11   Nov 23 1999 18:05:46   POPESCUS
 * NASU flow
 * 
 *    Rev 1.10   Nov 08 1999 15:50:38   ZHANGCEL
 * add mgmtco_cbo
 * 
 *    Rev 1.9   Oct 26 1999 10:29:34   ZHANGCEL
 * MFACCOUNT_CBO and GROUP_LIST added
 * 
 *    Rev 1.8   Aug 26 1999 16:10:44   PRAGERYA
 * Implementing Search for Shareholder and Account Info
 * 
 *    Rev 1.7   Aug 08 1999 19:33:30   PRAGERYA
 * All in!
 * 
 *    Rev 1.6   Jul 30 1999 17:24:34   PRAGERYA
 * Coded to the level of Incr1
 * 
 *    Rev 1.5   Jul 27 1999 14:07:28   BUZILA
 * fix
 * 
 *    Rev 1.4   Jul 23 1999 15:33:34   SMITHDAV
 * m21
 * 
 *    Rev 1.1   Jul 08 1999 10:03:58   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

