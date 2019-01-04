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
//    Copyright 2003 by International Financial Data Services
//    AUTHOR : 
//    DATE   : 
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId SETTLEMENT_LOCATIONS_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SettleLocationSysLvlHeading;
}


#include <dataimpl\dse_dstc0267_vw.hpp>
#include <dataimpl\dse_dstc0267_req.hpp>
#include <dataimpl\dse_dstc0268_vw.hpp>
#include <dataimpl\dse_dstc0268_req.hpp>

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/SettleLocationSysLvlProcessIncludes.h-arc  $
//
//   Rev 1.1   Nov 24 2003 18:17:54   HERNANDO
//Next revision.
//
//   Rev 1.0   Nov 20 2003 11:31:34   HERNANDO
//Initial revision.
//

