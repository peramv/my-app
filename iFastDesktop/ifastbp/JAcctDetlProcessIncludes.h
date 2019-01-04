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

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

#include <ifastdataimpl\dse_dstc0020_vwrepeat_record.hpp>

#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0016_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0003_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0136_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0148_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0053_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0011_vw.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int MFACCOUNT_HOLDING_LIST = 1;
//CP20030319const int MFACCOUNT_CBO = 2;
//CP20030319const int TRANSLATION_LIST = 3;
//CP20030319const int FUNDMASTER_LIST = 4;
//CP20030319const int FUNDSPONSORS_LIST = 5;
//CP20030319const int ACC_DISTRIBUTION_LIST = 6;
//CP20030319const int PENDINGTRADE_LIST = 7;
//CP20030319const int DEMOGRAPHICS_LIST = 8;
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACC_DISTRIBUTION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId DEMOGRAPHICS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDMASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDSPONSORS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_HOLDING_LIST;
   extern IFASTBP_LINKAGE const BFContainerId PENDINGTRADE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANSLATION_LIST;
}
namespace ACCTDETLIT  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_ID_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_NUM_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const NUM_ENTRY_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const LANGUAGE;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAcctDetlProcessIncludes.h-arc  $
 * 
 *    Rev 1.15   Mar 21 2003 17:42:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Oct 09 2002 23:53:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.13   22 May 2002 18:20:46   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   19 Mar 2002 13:17:38   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.11   May 08 2001 10:35:00   FENGYONG
 * Add variable
 * 
 *    Rev 1.10   Mar 29 2001 12:13:28   FENGYONG
 * Add managementstyle
 * 
 *    Rev 1.9   Feb 13 2001 17:16:34   FENGYONG
 * Add pending tradelist for trading page
 * 
 *    Rev 1.8   Dec 15 2000 16:54:16   FENGYONG
 * remove #3
 * 
 *    Rev 1.7   Dec 01 2000 16:57:54   FENGYONG
 * Add acctdistribution list
 * 
 *    Rev 1.6   Nov 28 2000 14:44:18   FENGYONG
 * Add fundsponser
 * 
 *    Rev 1.5   Aug 22 2000 16:57:24   FENGYONG
 * Fix French fundname and French Desc
 * 
 *    Rev 1.4   Jul 05 2000 13:44:58   VASILEAD
 * Added ShortName from FundMasterList
 * 
 *    Rev 1.3   Mar 24 2000 16:23:14   POPESCUS
 * added processes for Vision
 * 
 *    Rev 1.2   Mar 24 2000 12:22:46   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.2   Mar 06 2000 15:50:36   FENGYONG
// Add #3 view
// 
//    Rev 1.1   Nov 30 1999 11:00:58   FENGYONG
// Modified to use AccountList
// 
//    Rev 1.0   Nov 22 1999 11:23:02   FENGYONG
// Initial revision.
 * 
 *
 */

