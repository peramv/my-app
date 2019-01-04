#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial, Inc.
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0239_vwrepeat_record.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_CONTRACT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_HOLDINGS;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
   extern IFASTBP_LINKAGE const BFContainerId PROT_FUND_LIST;
}
namespace ifds
{   
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId ContractHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId ElongName1;
   extern CLASS_IMPORT const BFTextFieldId ResetExist;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

namespace ACC_CONTRACT
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );  
   const I_CHAR * const FUNDCLASS = I_( "FundClass" );  
//CP20030319   const int ACCOUNT_CONTRACT_LIST = 1;   
//CP20030319   const int ACCOUNT_HOLDINGS = 2;
//CP20030319   const int MFACCOUNT = 3;
   const BFFieldId RESET(4);
   const BFFieldId FUNDDESC(5);
//CP20030319   const int PROT_FUND_LIST = 6;
   const BFFieldId SEARCHFUNDDESC(7);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountContractProcessIncludes.h-arc  $
//
//   Rev 1.2   Mar 21 2003 17:34:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Jan 21 2003 13:44:12   HSUCHIN
//add more ids
//
//   Rev 1.0   Jan 20 2003 17:20:20   HSUCHIN
//Initial Revision
 */
