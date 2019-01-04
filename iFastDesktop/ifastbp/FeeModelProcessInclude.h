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

//#include <ifastdataimpl\dse_dstc0305_vw.hpp>
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
   extern IFASTBP_LINKAGE const BFContainerId FEE_MODEL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FEE_MODEL_SEARCH;
}

namespace MFCAN_IP_PARAM
{
   extern IFASTBP_LINKAGE const I_CHAR * const FEE_MODEL_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const HOLDING_COMP_CODE;
}
namespace FEEMODEL  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_SCR;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SrcHoldingCompCode;
   extern CLASS_IMPORT const BFTextFieldId SrcHoldingCompName;
   extern CLASS_IMPORT const BFTextFieldId SrcFeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId SrcFeeModelDesc;
   extern CLASS_IMPORT const BFDateFieldId AsofDate;
   extern CLASS_IMPORT const BFTextFieldId SearchAll;

   extern CLASS_IMPORT const BFTextFieldId HoldingCompCode;
   extern CLASS_IMPORT const BFTextFieldId HoldingCompName;
   extern CLASS_IMPORT const BFTextFieldId Program;
   extern CLASS_IMPORT const BFTextFieldId CalcCurrency;
   extern CLASS_IMPORT const BFTextFieldId EligibleFundBy;
   extern CLASS_IMPORT const BFTextFieldId FeeModelFundGroup;
   extern CLASS_IMPORT const BFTextFieldId ModelAggregationMethod;
   extern CLASS_IMPORT const BFTextFieldId ScheduleFreqID;
   extern CLASS_IMPORT const BFTextFieldId CalcRateType;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFNumericFieldId FeeModelRecid;
   extern CLASS_IMPORT const BFTextFieldId SchedSetupFreqAppl;

   extern CLASS_IMPORT const BFTextFieldId CalcRateTypeList;
   extern CLASS_IMPORT const BFTextFieldId HoldingEntityAppl;
   extern CLASS_IMPORT const BFTextFieldId CalcCurrencyAppl;
   extern CLASS_IMPORT const BFTextFieldId FundGroupType;
   extern CLASS_IMPORT const BFTextFieldId FundGrpTypeList;
   extern CLASS_IMPORT const BFTextFieldId AggregationMethodList;
   extern CLASS_IMPORT const BFTextFieldId FeeModelOptionList;



}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FeeModelProcessInclude.h-arc  $
//
//   Rev 1.1   Aug 10 2004 11:11:50   FENGYONG
//PET117 FN5 - Client Condition Fee
//
//   Rev 1.0   Aug 09 2004 10:01:24   FENGYONG
//Initial revision.
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