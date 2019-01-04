#pragma once
//******************************************************************************
//
// COPYRIGHT:
// 
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    AUTHOR : Amelia Aguila
//    DATE   : Janaury 2005
//
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^CLASS    : InvDetlDeductionProcessIncludes
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


// Inquiry View
#include <ifastdataimpl\dse_dstc0329_req.hpp>
#include <ifastdataimpl\dse_dstc0329_vw.hpp>
#include <ifastdataimpl\dse_dstc0329_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0022_vw.hpp>

namespace IFASTBP_PROC
{   
	extern IFASTBP_LINKAGE const BFContainerId TRANS_LIST;	
   extern IFASTBP_LINKAGE const BFContainerId INVENTORY_DETAIL_DEDUCTION_LIST;	
}

namespace INV_DETL_DEDUCT
{
   const I_CHAR * const ACCOUNT_NUMBER       = I_( "AccountNum" );   
	const I_CHAR * const SHAREHOLDER_NUMBER   = I_( "ShareholderNum" );   
	const I_CHAR * const TRANS_ID             = I_( "TransactionID" );   
  
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/InvDetlDeductionProcessIncludes.h-arc  $
//
//   Rev 1.1   Feb 17 2005 13:15:14   aguilaam
//PET1198_FN01: LSIF Reason Code enhancement. 
//
//   Rev 1.0   Jan 28 2005 14:34:28   aguilaam
//Initial revision.
//
