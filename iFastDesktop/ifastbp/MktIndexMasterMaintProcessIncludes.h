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
   extern IFASTBP_LINKAGE const BFContainerId FUNDS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId INDICES_LIST;
}
namespace INDEX_MASTER
{
//CP20030319   const int INDICES_LIST = 1;
//CP20030319   const int FUNDS_LIST = 2;
   const BFFieldId FUNDDESC( 1000 );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId IndexMasterHeading;
   extern CLASS_IMPORT const BFTextFieldId IndexFundsHeading;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId ElongName1;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDCLASS;

#include <ifastdataimpl\dse_dstc0240_vw.hpp>
#include <ifastdataimpl\dse_dstc0240_req.hpp>
#include <ifastdataimpl\dse_dstc0241_vw.hpp>
#include <ifastdataimpl\dse_dstc0241_req.hpp>

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MktIndexMasterMaintProcessIncludes.h-arc  $
//
//   Rev 1.2   Mar 21 2003 17:45:28   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Feb 07 2003 14:14:28   HERNANDO
//Added Fund Description.
//
//   Rev 1.0   Jan 23 2003 10:29:06   HERNANDO
//Initial Revision
 */

