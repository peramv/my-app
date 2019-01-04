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
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : ForeignContentWorksheetProcessIncludes.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : ForeignContentWorksheetProcessIncludes
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

// Inquiry View
//#include <ifastdataimpl\dse_dstc0_vw.hpp>
#include <ifastdataimpl\dse_dstc0294_vw.hpp>

namespace IFASTBP_PROC
{   
	extern IFASTBP_LINKAGE const BFContainerId FOREIGN_CONTENT_WORKSHEET;
	extern IFASTBP_LINKAGE const BFContainerId FOREIGN_CONTENT_TRADE;
}

namespace ifds
{
   //field ids used, not found in the above view   
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;   
	extern CLASS_IMPORT const BFTextFieldId    TradesTransType;   
	extern CLASS_IMPORT const BFDateFieldId    EffectiveDate;   
	extern CLASS_IMPORT const BFTextFieldId    FromFundNumber;   
	extern CLASS_IMPORT const BFTextFieldId    FromFund;   
	extern CLASS_IMPORT const BFTextFieldId    FromClass;   
	//extern CLASS_IMPORT const BFTextFieldId FromFundName;   
	extern CLASS_IMPORT const BFTextFieldId    ToFundNumber;   
	extern CLASS_IMPORT const BFTextFieldId    ToFund;   
	extern CLASS_IMPORT const BFTextFieldId    ToClass;   
	//extern CLASS_IMPORT const BFTextFieldId    ToFundName;   
	extern CLASS_IMPORT const BFDecimalFieldId Amount;   
	extern CLASS_IMPORT const BFTextFieldId    AmtType;  
	extern CLASS_IMPORT const BFTextFieldId    HypoTransType;  
	
	//extern CLASS_IMPORT const BFTextFieldId    OrderType;   
	//extern CLASS_IMPORT const BFTextFieldId ???;
   
	extern CLASS_IMPORT const BFTextFieldId FromFundName; 
	extern CLASS_IMPORT const BFTextFieldId ToFundName; 



}

namespace FOREIGN_CONTENT_WORKSHEET
{
   const I_CHAR * const ACCOUNT_NUMBER     = I_( "AccountNum" );   
	const I_CHAR * const SHAREHOLDER_NUMBER = I_( "ShareholderNum" ); 	
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ForeignContentWorksheetProcessincludes.h-arc  $
//
//   Rev 1.3   May 25 2004 10:46:34   YINGBAOL
//PET985:change view294
//
//   Rev 1.2   May 25 2004 10:07:44   YINGBAOL
//PET985: implement FundName
//
//   Rev 1.1   May 19 2004 17:41:56   YINGBAOL
//PET985: make hypo work
//
//   Rev 1.0   Apr 21 2004 15:39:24   VADEANUM
//Initial revision.
//
