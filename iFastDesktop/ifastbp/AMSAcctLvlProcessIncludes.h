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

#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0204_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0380_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId AMS_MASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId GLOBAL_DEFINED_AMS;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId ROOT_USER_DEFINED_AMS;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
   extern IFASTBP_LINKAGE const BFContainerId USER_DEFINED_AMS;
   extern IFASTBP_LINKAGE const BFContainerId AMS_ACCOUNT_LEVEL_LIST;
}
namespace AMSACCTLVLLITERALS
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const NAME;
   extern IFASTBP_LINKAGE const I_CHAR * const AMSCODE_USER_DEFINED;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AMSAcctLevelHeading;
}

const BFFieldId TOTAL_PERCENTAGE(100);
const BFFieldId CHANGE_OCCURED(101);
const BFFieldId REBALANCE(102);
const BFFieldId AMSCODE_DESCRIPTION(103);
const BFFieldId THRESHOLD_PERCENTAGE( 104 );
const BFFieldId COMMON_CURRENCY( 105 );
const BFFieldId IsFundLimitedByBankuptcy (106);//IN2818924 - DSK_AMS Validation for CDIC

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AMSAcctLvlProcessIncludes.h-arc  $
//
//   Rev 1.7   Jan 31 2012 07:44:46   panatcha
//IN2818924 - DSK_AMS Validation for CDIC
//
//   Rev 1.6   Jul 11 2007 16:20:28   smithdav
//PET 2360 FN02 - AMS - Interim changes
//
//   Rev 1.5   Jun 22 2007 14:17:06   porteanm
//PET 2360 FN02 - AMS - work in progress.
//
//   Rev 1.4   Apr 02 2003 11:58:46   HERNANDO
//Sync'd with 1.2.1.0
//
//   Rev 1.3   Mar 21 2003 17:35:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Mar 18 2003 17:23:18   HERNANDO
//[updated] Dev-level revision for AMS.
//
//   Rev 1.1   Jan 08 2003 16:38:16   sanchez
//Rebalancing Target Mix
//
//   Rev 1.0   Nov 28 2002 18:35:38   HERNANDO
//Initial revision.
 * 
 */
