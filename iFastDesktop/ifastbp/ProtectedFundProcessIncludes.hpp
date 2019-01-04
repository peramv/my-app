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
//    AUTHOR : Serban Popescu
//    DATE   : 01/08/2003
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0237_vw.hpp>
#include <ifastdataimpl\dse_dstc0237_req.hpp>
#include <ifastdataimpl\dse_dstc0237_vwrepeat_record.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId PROTECTED_FUND_LIST;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ProtectedFundsListHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;

}
// Need to define list and search Id's to be used by a GUI object talking to the
// process.
//CP20030319const int PROTECTED_FUND_LIST = 1;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ProtectedFundProcessIncludes.hpp-arc  $
//
//   Rev 1.3   Mar 21 2003 17:46:16   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Jan 20 2003 15:43:28   popescu
//Checked in for unit testing the ProtectedFundSetup feature
//
//   Rev 1.1   Jan 10 2003 10:05:58   popescu
//For revsions
//
//   Rev 1.0   Jan 10 2003 10:05:04   popescu
//Initial revision.
 * 
 */

