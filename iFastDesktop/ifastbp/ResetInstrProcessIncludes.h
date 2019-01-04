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
#include <ifastdataimpl\dse_dstc0243_vwrepeat_record.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_HOLDINGS;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
   extern IFASTBP_LINKAGE const BFContainerId PROT_FUND_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RESET_INSTR_CRITERIA;
   extern IFASTBP_LINKAGE const BFContainerId RESET_INSTR_LIST;
}
namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId ResetInstrUsing;
   extern CLASS_IMPORT const BFTextFieldId ResetInstrHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId ElongName1;
}

namespace RESET_INSTR
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );  
   const I_CHAR * const FUNDCLASS = I_( "FundClass" );     
//CP20030319   const int RESET_INSTR_LIST = 1;   
//CP20030319   const int ACCOUNT_HOLDINGS = 2;
//CP20030319   const int MFACCOUNT = 3;
   const BFFieldId FUNDDESC(4);
//CP20030319   const int PROT_FUND_LIST = 5;   
//CP20030319   const int RESET_INSTR_CRITERIA = 6;
   const BFFieldId updated(7);
   const I_CHAR * const PARENT = I_( "Parent" );  
   const I_CHAR * const CONTRACT_DETAIL = I_( "Contract_Detail" );
   const BFFieldId ORIKEY (8);
   const BFFieldId DESTKEY (9);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ResetInstrProcessIncludes.h-arc  $
//
//   Rev 1.3   Mar 21 2003 17:47:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Jan 27 2003 07:29:26   HSUCHIN
//clean up and added ORIKEY/DESTKEY
//
//   Rev 1.1   Jan 26 2003 16:01:38   HSUCHIN
//added headingset
//
//   Rev 1.0   Jan 24 2003 16:10:42   HSUCHIN
//Initial Revision
 */
