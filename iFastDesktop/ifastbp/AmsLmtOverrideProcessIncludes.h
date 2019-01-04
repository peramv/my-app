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
//    Copyright 2002 by International Financial Data Services
//    AUTHOR : Yingbao Li
//    DATE   : May 24,2002
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
   extern IFASTBP_LINKAGE const BFContainerId AMS_LMT_OVERRIDE_LIST;
}
namespace AMS_LMT_OVERRIDE_PROC
{

	const BFFieldId updated(1000);
}

namespace AMS_LMT_Para
{
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_CODE;
 //  extern IFASTBP_LINKAGE const I_CHAR * const AMS_TYPE; 
 //  extern IFASTBP_LINKAGE const I_CHAR * const AMS_EFFECTIVE_DATE; 
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_REC_ID; 
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_SCR; 



}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AmsLmtOverrideHeading;
   extern CLASS_IMPORT const BFTextFieldId AMSType;


}



#include <ifastdataimpl\dse_dstc0262_req.hpp>
#include <ifastdataimpl\dse_dstc0262_vw.hpp>
#include <ifastdataimpl\dse_dstc0261_req.hpp>


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AmsLmtOverrideProcessIncludes.h-arc  $
//
//   Rev 1.3   Aug 13 2003 16:22:54   linmay
//added From_Scr as a parameter
//
//   Rev 1.2   Aug 08 2003 09:36:10   linmay
//fix bug
//
//   Rev 1.1   Aug 05 2003 11:29:16   linmay
//fix bug
//
//   Rev 1.0   Jul 23 2003 09:25:00   linmay
//Initial Revision
//
//



 */

