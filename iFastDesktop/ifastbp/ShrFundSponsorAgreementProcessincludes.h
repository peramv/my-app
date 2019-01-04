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
//    DATE   : June 2004
//
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^CLASS    : ShrFundSponsorAgreementProcessIncludes
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
#include <ifastdataimpl\dse_dstc0299_vw.hpp>

namespace IFASTBP_PROC
{   
	extern IFASTBP_LINKAGE const BFContainerId SHR_FUND_SPONSOR_AGREEMENT_LIST;	
}

namespace ifds
{
   //field ids used, not found in the above view
   extern CLASS_IMPORT const BFTextFieldId ShrFndSpAgrExists;   
}

namespace SHR_FUND_SPONSOR_AGREEMENT
{
   const I_CHAR * const ACCOUNT_NUMBER     = I_( "AccountNum" );   
	const I_CHAR * const SHAREHOLDER_NUMBER = I_( "ShareholderNum" );   
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ShrFundSponsorAgreementProcessincludes.h-arc  $
//
//   Rev 1.1   Jul 27 2004 15:46:50   VADEANUM
//PET1117 FN01 - Shareholder Static Data - first working version.
//
//   Rev 1.0   Jul 26 2004 10:30:44   VADEANUM
//Initial revision.
//
