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
//    Copyright by International Financial Data Services
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0348_vw.hpp>

namespace IFASTBP_PROC
{
	extern IFASTBP_LINKAGE const BFContainerId CUT_OFF_TIMES_LIST;
	extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId AcctLvlCutOffTimesHeading;
	extern CLASS_IMPORT const BFTextFieldId NetworkSenderLvlCutOffTimesHeading;
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId FundNumber;
	extern CLASS_IMPORT const BFTextFieldId ModUser;
	extern CLASS_IMPORT const BFDateFieldId ModDate;
	extern CLASS_IMPORT const BFTextFieldId BrokerContainerValid;
}

	
//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/AcctCutOffTimesProcessIncludes.h-arc  $
//
//   Rev 1.1   Jul 21 2006 14:01:38   jankovii
//PET 2192 FN02 - Dealings-Sender Cut-Off Time.
//
//   Rev 1.0   Jul 05 2005 17:39:58   hernando
//Initial revision.
