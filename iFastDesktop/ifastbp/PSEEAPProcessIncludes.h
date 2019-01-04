#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************

//******************************************************************************
//
// ^FILE   : PSEEAPProcessIncludes.h.cpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0115_Req.hpp> 

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
	extern IFASTBP_LINKAGE const BFContainerId PSE_EAP_LIST;
	extern IFASTBP_LINKAGE const BFContainerId TRADE;
}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

namespace
{
   const I_CHAR * const CALLER = I_("Caller");
   const I_CHAR * const ACCOUNT_NUM = I_("AccountNum");
   const I_CHAR * const TRADE_LIST_KEY = I_("TradeListKey");
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PSEEAPProcessIncludes.h-arc  $
//
//   Rev 1.0   Apr 20 2010 00:59:50   popescu
//Initial revision.
//
 * 
*/