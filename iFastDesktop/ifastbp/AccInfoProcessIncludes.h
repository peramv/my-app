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
//    Copyright 1999 by DST Systems, Inc.
//    AUTHOR : Mihai Virgil Buzila
//    DATE   : 06/04/99
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0090_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vwrepeat_record.hpp>

//include the data sets
#include <ifastdataimpl\dse_substitute_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
}
namespace ACCINFOPROC
{
   // Trace literals
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const MODEL_ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_ID;

   const BFFieldId ACCOUNT_NUMBER_FIELD(101);
   const BFFieldId CREATING_ACCOUNT_FIELD(102);
   const BFFieldId GRP_CODE_LEVEL_FIELD(103);
   const BFFieldId ACCOUNT_INFO_CHANGED(104);  
   const BFFieldId REP_BY_BRANCH_FIELD(105); 
   const BFFieldId TITLE_FIELD(106);

   // Need to define list and search Id's to be used by a GUI object talking to the
   // process.
//CP20030319   const int MFACCOUNT_CBO = 1;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccInfoProcessIncludes.h-arc  $
 * 
 *    Rev 1.12   Jul 10 2003 22:19:10   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.11   Mar 21 2003 17:33:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:52:56   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:51:24   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:22:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   19 Mar 2002 13:14:42   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.6   Sep 23 2000 15:29:32   DINACORN
 * Create dummy fields in ACCINFOPROC
 * 
 *    Rev 1.5   Sep 01 2000 14:38:20   YINGBAOL
 * add AccountInfo Changed
 * 
 *    Rev 1.4   Aug 23 2000 11:49:16   DINACORN
 * Added GRP_CODE_LEVEL_FIELD
 * 
 *    Rev 1.3   Aug 16 2000 10:35:26   DINACORN
 * Added addFieldDetails() for Group
 * 
 *    Rev 1.2   Feb 15 2000 18:56:08   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.1   Feb 15 2000 12:50:14   POPESCUS
/* 
 *    Rev 1.0   Feb 15 2000 10:58:54   SMITHDAV
 * Initial revision.
// 
//    Rev 1.21   Jan 12 2000 09:03:18   POPESCUS
// changes related to cloning an account and fixing some validation, adding subst sets
// 
//    Rev 1.20   Jan 11 2000 08:41:42   POPESCUS
// fixes and validation
// 
//    Rev 1.19   Jan 06 2000 09:58:38   POPESCUS
// cleanup code and remove some unused methods
// 
//    Rev 1.18   Dec 24 1999 10:29:54   VASILEAD
// Fixed NASU flow
// 
//    Rev 1.17   Dec 23 1999 11:29:10   POPESCUS
// NASU process and the new confirmation model
// 
//    Rev 1.16   Dec 21 1999 14:15:00   POPESCUS
// cleanup the code, validations and misc
// 
//    Rev 1.15   Dec 14 1999 09:50:36   ZHANGCEL
// Add parameter for TaxType
// 
//    Rev 1.14   Dec 03 1999 18:21:36   ZHANGCEL
// Debug
// 
//    Rev 1.13   Dec 01 1999 11:24:12   ZHANGCEL
// Modify for default Broker Branch and SalesRep
// 
//    Rev 1.12   Nov 30 1999 13:58:40   ZHANGCEL
// New AccountInfo implementation
// 
//    Rev 1.11   Nov 29 1999 10:11:06   ZHANGCEL
// Add two new subclass
// 
//    Rev 1.10   Nov 25 1999 14:08:58   POPESCUS
// get the account number for mfcommonbm and cleanup
// 
//    Rev 1.9   Nov 25 1999 10:19:54   ZHANGCEL
// change brokerList value
// 
//    Rev 1.8   Nov 24 1999 10:06:06   POPESCUS
// again NASU
// 
//    Rev 1.7   Nov 23 1999 18:05:42   POPESCUS
// NASU flow
// 
//    Rev 1.6   Nov 15 1999 11:59:28   PRAGERYA
// Further additions for Incr2
// 
//    Rev 1.5   Aug 26 1999 16:10:40   PRAGERYA
// Implementing Search for Shareholder and Account Info
// 
//    Rev 1.4   Aug 11 1999 12:34:10   PRAGERYA
// Enhancing implementation
// 
//    Rev 1.3   Aug 08 1999 19:33:24   PRAGERYA
// All in!
// 
//    Rev 1.2   Aug 04 1999 09:37:22   PRAGERYA
// Implementing process
// 
//    Rev 1.1   Jul 27 1999 16:03:30   BUZILA
// Increment M2
// 
//    Rev 1.0   Jul 22 1999 17:22:50   BUZILA
// Initial revision.
*/ 

