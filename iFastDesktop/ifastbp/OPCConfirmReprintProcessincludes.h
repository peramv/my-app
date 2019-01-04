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
// ^CLASS    : OPCConfirmReprintProcessIncludes
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
//#include <dataimpl\dse_dstc0345_vw.hpp>

namespace IFASTBP_PROC
{   
	extern IFASTBP_LINKAGE const BFContainerId OPC_CONFIRM_REPRINT;	
	extern IFASTBP_LINKAGE const BFContainerId OPC_ONLINE_CONFIRM_REPRINT;	
}

namespace ifds
{
   //field ids used, not found in the above view
   //extern CLASS_IMPORT const BFTextFieldId ;   
}

namespace OPC_CONFIRM_REPRINT
{
   const I_CHAR * const TRANSID = I_( "TransId" );   
   const I_CHAR * const FUND    = I_( "Fund" );   
   const I_CHAR * const CLASS   = I_( "Class" );   
}

namespace OPC_ONLINE_CONFIRM_REPRINT
{
   const I_CHAR * const TRANSID = I_( "TransId" );   
   const I_CHAR * const FUND    = I_( "Fund" );   
   const I_CHAR * const CLASS   = I_( "Class" );   
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/OPCConfirmReprintProcessincludes.h-arc  $
//
//   Rev 1.1   May 06 2005 12:35:34   porteanm
//PET OPC Confirm Reprint - Added PCOnlineConfirmReport for Release 63.
//
//   Rev 1.0   May 05 2005 13:54:30   porteanm
//Initial revision.
//

