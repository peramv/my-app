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

#include <ifastdataimpl\dse_dstc0194_vw.hpp>
#include <ifastdataimpl\dse_dstc0195_vw.hpp>
#include <ifastdataimpl\dse_dstc0196_vw.hpp>
#include <ifastdataimpl\dse_dstc0197_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>
#include <ifastdataimpl\dse_dstc0229_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FEE_PARAM_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FEE_SCALE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_COMM_GROUP_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACOUNT;
}
namespace FEEPARAM  //stands for account details literals
{
//CP20030319   const int FEE_PARAM_LIST   = 1L;
//CP20030319   const int FEE_SCALE_LIST      = 2L;
//CP20030319   const int MFACOUNT        = 3L;
//CP20030319	const int FUND_COMM_GROUP_LIST  =4L;


   const BFFieldId PRIMARY_ACCOUNT_OWNER(100L);
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FeeParamListSet;
   extern CLASS_IMPORT const BFTextFieldId FeeScaleListSet;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId GSTExempt;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;


}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FeeParamProcessInclude.h-arc  $
//
//   Rev 1.10   Mar 21 2003 17:39:42   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.9   Jan 29 2003 16:22:14   popescu
//Added the historical button for FeeParamSysDlg and FeeParamDlg
//
//   Rev 1.8   Jan 03 2003 19:46:16   YINGBAOL
//add  FUND_COMM_GROUP_LIST 
//
//   Rev 1.7   Jan 03 2003 16:28:04   linmay
//added dstc_vw0229
//
//   Rev 1.6   Nov 18 2002 10:55:36   PURDYECH
//BFObjectKey changes.
//
//   Rev 1.5   Oct 09 2002 23:53:14   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:52:24   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:21:12   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:17:02   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Feb 22 2002 14:20:40   YINGBAOL
//more function added
 * 
 */