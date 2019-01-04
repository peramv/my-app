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
//    Copyright 2002 by DST Systems, Inc.
//
//******************************************************************************

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0217_vw.hpp>
#include <ifastdataimpl\dse_dstc0217_req.hpp>
#include <ifastdataimpl\dse_dstc0217_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0020_vwrepeat_record.hpp>


namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId CRITERIA;
   extern IFASTBP_LINKAGE const BFContainerId DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ERRORS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId HOLDINGS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
   extern IFASTBP_LINKAGE const BFContainerId SUMMARY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TOTAL_LIST;
}
namespace HYPO_RED
{
   const I_CHAR * const ACCOUNT_NUMBER       = I_( "AccountNum" );
   const I_CHAR * const TXT_ACCT_NUM_CHANGED = I_( "AccountNumChanged" );


	//container IDs
//CP20030319   const int MFACCOUNT      =  1;
//CP20030319   const int CRITERIA       =  2;
//CP20030319   const int HOLDINGS_LIST  =  3;
//CP20030319   const int SUMMARY_LIST   =  4;
//CP20030319   const int DETAILS_LIST   =  5;
//CP20030319   const int TOTAL_LIST     =  6;
//CP20030319   const int ERRORS_LIST    =  7;

}


namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FundName;
	extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFDecimalFieldId GrossAmt;
   extern CLASS_IMPORT const BFDecimalFieldId NetAmt;
   extern CLASS_IMPORT const BFNumericFieldId ErrorCode;
   extern CLASS_IMPORT const BFTextFieldId ErrorDesc;
   extern CLASS_IMPORT const BFTextFieldId ValidHypoRed;
   extern CLASS_IMPORT const BFTextFieldId ValidHypoCriteria;
   extern CLASS_IMPORT const BFTextFieldId isLSIF;
}

