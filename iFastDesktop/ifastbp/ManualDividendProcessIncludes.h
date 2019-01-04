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
//    Copyright 2003 by International Financial Data Services
//    AUTHOR : 
//    DATE   : 
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MANUAL_DIVIDEND_LIST;
}

/*
namespace MANUAL_DIVIDEND
{
   const BFFieldId SHAREHOLDERADDRESS( 1000 );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId IndexValuesHeading;
   extern CLASS_IMPORT const BFTextFieldId IndexFundsHeading;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId ElongName1;
}

const BFFieldId PERCENTAGE_CHANGED(100);
*/
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDCLASS;
/*
#include <dataimpl\dse_dstc0241_vw.hpp>
#include <dataimpl\dse_dstc0241_req.hpp>
#include <dataimpl\dse_dstc0247_vw.hpp>
#include <dataimpl\dse_dstc0247_req.hpp>
#include <dataimpl\dse_dstc0248_vw.hpp>
#include <dataimpl\dse_dstc0248_req.hpp>
*/
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ManualDividendProcessIncludes.h-arc  $
//
//   Rev 1.0   May 22 2003 17:01:18   HERNANDO
//Initial revision.
 */

