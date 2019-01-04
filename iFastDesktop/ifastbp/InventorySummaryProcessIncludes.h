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
#include <ifastdataimpl\dse_dstc0287_vw.hpp>
#include <ifastdataimpl\dse_dstc0287_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0292_vw.hpp>
#include <ifastdataimpl\dse_dstc0292_vwrepeat_record.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId INVENTORY_SUMMARY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId INVENTORY_DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_HOLDINGS;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
   extern IFASTBP_LINKAGE const BFContainerId FUND_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_MASTER_LIST;
}
namespace ifds
{   
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId InventorySummHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId InventoryDetailsHeading;
   extern CLASS_IMPORT const BFTextFieldId ElongName1;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFNumericFieldId TransId;
}

namespace INV_SUMMARY
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );  
   const I_CHAR * const FUNDCLASS = I_( "FundClass" ); 
	const I_CHAR * const FUND_CODE = I_( "FundCode" );
	const I_CHAR * const CLASS_CODE = I_( "ClassCode" );   
   const I_CHAR * const ACTIVEONLY = I_( "ActiveOnly" );
//CP20030319   const int ACCOUNT_HOLDINGS = 2;
//CP20030319   const int MFACCOUNT = 3;
   const BFFieldId FUNDDESC(5);
//CP20030319   const int PROT_FUND_LIST = 6;
   const BFFieldId SEARCHFUNDDESC(7);
   const BFFieldId TOTALCBFREEUNITS(8);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/InventorySummaryProcessIncludes.h-arc  $
//
//   Rev 1.1   May 19 2004 17:45:24   HERNANDO
//PET1046 FN01 - Added LSIF/Inventory Details support.
//
//   Rev 1.0   Feb 24 2004 10:29:10   ZHANGCEL
//Initial revision.

 */
