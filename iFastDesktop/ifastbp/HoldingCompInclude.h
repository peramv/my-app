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
//    Copyright 2002 by Internantional Financial.
//
//******************************************************************************

//#include <dataimpl\dse_dstc0305_vw.hpp>
#include <dataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FEE_MODEL_LIST;
}
namespace HOLDINGCOMP  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_SCR;
}

namespace ifds
{
/*
   extern CLASS_IMPORT const BFTextFieldId FeeParamListSet;
   extern CLASS_IMPORT const BFTextFieldId FeeScaleListSet;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId GSTExempt;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
*/
}

