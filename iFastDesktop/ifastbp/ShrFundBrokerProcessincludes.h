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
//    AUTHOR : Monica Vadeanu
//    DATE   : November 2004
//
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^CLASS    : ShrFundBrokerProcessIncludes
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
#include <ifastdataimpl\dse_dstc0327_vw.hpp>

namespace IFASTBP_PROC
{   
	extern IFASTBP_LINKAGE const BFContainerId SHR_FUND_BROKER_LIST;	
}

namespace ifds
{
   //field ids used, not found in the above view
   extern CLASS_IMPORT const BFTextFieldId ShrFndBrkExist;   	

	extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
	extern CLASS_IMPORT const BFTextFieldId FundName;	
	extern CLASS_IMPORT const BFTextFieldId FundBrokerName;
	
	extern CLASS_IMPORT const BFTextFieldId ModUser;	
	extern CLASS_IMPORT const BFDateFieldId ModDate;		
}

namespace SHR_FUND_BROKER
{
   const I_CHAR * const ACCOUNT_NUMBER     = I_( "AccountNum" );   
	const I_CHAR * const SHAREHOLDER_NUMBER = I_( "ShareholderNum" );   
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ShrFundBrokerProcessincludes.h-arc  $
//
//   Rev 1.2   Nov 28 2004 14:07:22   vadeanum
//PET1117 FN08 - Shareholder Fund Broker support 
//
//   Rev 1.1   Nov 11 2004 16:18:00   vadeanum
//PET1117 FN08 - Shareholder Fund Broker support.
//
//   Rev 1.0   Nov 04 2004 10:34:12   VADEANUM
//Initial revision.
//
