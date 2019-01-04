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

#include <ifastdataimpl\dse_dstc0197_vw.hpp>
#include <ifastdataimpl\dse_dstc0229_vw.hpp>
#include <ifastdataimpl\dse_dstc0230_req.hpp>
#include <ifastdataimpl\dse_dstc0230_vw.hpp>
#include <ifastdataimpl\dse_dstc0231_req.hpp>
#include <ifastdataimpl\dse_dstc0232_vw.hpp>
#include <ifastdataimpl\dse_dstc0231_vw.hpp>

#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FEE_PARAM_SEARCH;
   extern IFASTBP_LINKAGE const BFContainerId FEE_PARAM_SYSTEM_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FEE_PARAM_SYSTEM_SCALE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_COMM_GROUP_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FEE_PARAM_SYSTEM_THRESHOLD_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FEE_PARAM_SYSTEM_SCALE_THR_LIST;
}
namespace FEEPARAMSYS  //stands for system level fee details literals
{
//CP20030319	const int FEE_PARAM_SYSTEM_LIST				= 1L;
//CP20030319	const int FEE_PARAM_SYSTEM_SCALE_LIST		= 2L;
//CP20030319	const int FUND_COMM_GROUP_LIST				= 3L;
//CP20030319	const int FEE_PARAM_SEARCH						= 4L;
	const BFFieldId CLEAR_SEARCH_CRITERIA(1000);
	const BFFieldId HAS_OBJECT_UPDATE(1001);
	const BFFieldId RELOAD_OBJECT(1002);
	const BFFieldId IS_THE_SAME_BUSINESS_DATE(1003);
	const BFFieldId GET_DEFAULT_BRANCH_CODE(1004);
    const BFFieldId ALLOW_NEG_RATE(1005);
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FeeScaleListSet;
   extern CLASS_IMPORT const BFTextFieldId FeeParamSysHeading;
   extern CLASS_IMPORT const BFTextFieldId FeeScaleSysHeading;
   extern CLASS_IMPORT const BFTextFieldId SysFeeGridSet;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId TradingAttributesHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId RepByBranch;
   extern CLASS_IMPORT const BFTextFieldId FeeScaleSysInvestTermHeading;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId SearchAll;
   extern CLASS_IMPORT const BFDateFieldId AsofDate;

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FeeParamSysProcessInclude.hpp-arc  $
//
//   Rev 1.12   Dec 13 2011 08:53:22   popescu
//P0186477/FN03 - INA Commission Work
//
//   Rev 1.11   Jun 11 2003 15:41:06   linmay
//fix bug for Borker level fee setup
//
//   Rev 1.10   Jun 04 2003 11:30:26   linmay
//PTS Ticket: #10017810
//
//   Rev 1.9   Mar 21 2003 17:39:50   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.8   Mar 10 2003 15:06:18   linmay
//added field repbybranch
//
//   Rev 1.7   Jan 31 2003 09:33:38   linmay
//added new BFFieldId RELOAD_OBJECT;
//
//   Rev 1.6   Jan 21 2003 13:47:04   linmay
//added FromFunderNumber
//
//   Rev 1.5   Jan 18 2003 17:20:54   YINGBAOL
//add HAS_OBJECT_UPDATE
//
//   Rev 1.4   Jan 17 2003 18:06:22   linmay
//added feescalesysheadingset
//
//   Rev 1.3   Jan 17 2003 14:12:54   YINGBAOL
//add FEE_PARAM_SEARCH
//
//   Rev 1.2   Jan 15 2003 11:52:56   linmay
//added log comment
// 
*/