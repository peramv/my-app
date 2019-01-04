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
//    DATE   : 16/04/99
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

//name of the params used at transfering the search criteria to the business process


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0064_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>

// Need to define list and search Id's to be used by a GUI object talking to the
// process.

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId COA_MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId COA_PROC_GEN_LIST;
   extern IFASTBP_LINKAGE const BFContainerId COA_SHAREHOLDER_CBO;
}
namespace COALIT
{
   extern const I_CHAR* const ACCOUNT_NUM;
}
namespace COAPROC
{

   // Need to define list and search Id's to be used by a GUI object talking to the
   // process.
//CP20030319   const int COA_PROC_GEN_LIST  =   0;
//CP20030319   const int COA_SHAREHOLDER_CBO  =   2;
//CP20030319   const int COA_MFACCOUNT_CBO  =   3;

   const BFFieldId inNASU(102);
   const BFFieldId lYes(103);
   const BFFieldId lChange(104);
   const BFFieldId lView(105);
   const BFFieldId lYes_no(106);
   const BFFieldId AMSOption(107);
   const BFFieldId RespExists(108);
   const BFFieldId AcctOwnershipRecordExist (109);
   const BFFieldId MgmtFeePayOptionDefault (110);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/COAProcessIncludes.h-arc  $
 * 
 * History: 
 * 07-Mar-2014 Supareuk Sukjaitham P0221545 FN01 DFT0030180 T54906
 *             - Added a new field MgmtFeePayOptionDefault
 *             - Recheck with the new task T54906
 *
 *    Rev 1.12   Jul 24 2012 19:08:26   dchatcha
 * P0179630 FN01 FATCA Project - Acct Ownership Allocation
 * 
 *    Rev 1.11   Mar 21 2003 17:38:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Mar 11 2003 14:11:42   HSUCHIN
 * fixed COA dlg crash for RESP accounts
 * 
 *    Rev 1.9   Jan 29 2003 13:43:28   sanchez
 * added new field AMSOption to the COAPROC namespace
 * 
 *    Rev 1.8   Oct 09 2002 23:53:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:52:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   07 Jun 2002 17:00:48   HERNANDO
 * Added #include "dse_dstc0149_vw.hpp".
 * 
 *    Rev 1.5   22 May 2002 18:21:36   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:15:26   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Feb 16 2001 15:29:38   YINGBAOL
 * put some hardcode strings into DD
 * 
 *    Rev 1.2   Sep 20 2000 14:21:16   ZHANGCEL
 * Debug
 * 
 *    Rev 1.1   Feb 15 2000 18:56:20   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.9   Jan 22 2000 15:18:58   BUZILA
 * fixes
 * 
 *    Rev 1.8   Dec 24 1999 15:37:02   BUZILA
 * we don't need anymore COAlist
 * 
 *    Rev 1.7   Dec 22 1999 18:01:48   BUZILA
 * changes due to COA flags movament
 * 
 *    Rev 1.6   Nov 25 1999 15:12:52   BUZILA
 * fixes
 * 
 *    Rev 1.5   Nov 20 1999 19:39:18   BUZILA
 * fixes
 * 
 *    Rev 1.4   Oct 17 1999 12:12:16   POPESCUS
 * namespaces fixes
 * 
 *    Rev 1.3   Aug 05 1999 11:52:52   BUZILA
 * 1
 * 
 *    Rev 1.2   Jul 27 1999 16:03:34   BUZILA
 * Increment M2
 * 
 *    Rev 1.1   Jul 08 1999 10:03:36   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

