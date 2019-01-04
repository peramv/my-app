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
// ^CLASS    : ConfirmReprintProcessIncludes
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
#include <ifastdataimpl\dse_dstc0345_vw.hpp>

namespace IFASTBP_PROC
{   
	extern IFASTBP_LINKAGE const BFContainerId CONFIRM_REPRINT;		
	extern IFASTBP_LINKAGE const BFContainerId OPC_CONFIRM_REPRINT;		
}

namespace ifds
{
   //field ids used, not found in the above view
   extern CLASS_IMPORT const BFTextFieldId OPCConfirmReprint;   
}

namespace CONFIRM_REPRINT
{
   const I_CHAR * const ACCOUNTNUM = I_( "AccountNum" );   
   const I_CHAR * const TRANSID    = I_( "TransId" );   
   const I_CHAR * const FUND       = I_( "Fund" );   
   const I_CHAR * const CLASS      = I_( "Class" );   
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ConfirmReprintProcessincludes.h-arc  $
//
//   Rev 1.1   May 25 2005 14:58:08   porteanm
//PET OPC Confirm Reprint.
//
//   Rev 1.0   May 24 2005 12:46:02   porteanm
//Initial revision.
//


