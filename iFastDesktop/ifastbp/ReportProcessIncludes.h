#pragma once
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//******************************************************************************

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId REPORT_COMMON_INFO;
   extern IFASTBP_LINKAGE const BFContainerId REPORT_CRITERIA_LIST;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ReportName;
   extern CLASS_IMPORT const BFTextFieldId ReportMode;
   extern CLASS_IMPORT const BFTextFieldId ReportType;
   extern CLASS_IMPORT const BFTextFieldId ScheduleJob;
   extern CLASS_IMPORT const BFDateFieldId RunOnDate;
   extern CLASS_IMPORT const BFTextFieldId RunOnTime;
   extern CLASS_IMPORT const BFTextFieldId TimeZone;
   extern CLASS_IMPORT const BFTextFieldId CriteriaType;
   extern CLASS_IMPORT const BFTextFieldId IncludeExclude;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId GroupCode;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFDateFieldId StartDate;   
   extern CLASS_IMPORT const BFTextFieldId InclPending;
	extern CLASS_IMPORT const BFDateFieldId LiveRunDate;
	extern CLASS_IMPORT const BFTextFieldId UnsettleWithAMSFund;
	extern CLASS_IMPORT const BFTextFieldId PendingWithAMSFund;
   extern CLASS_IMPORT const BFTextFieldId Description;
   extern CLASS_IMPORT const BFTextFieldId ReportCriteriaHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId CriteriaValue;
   extern CLASS_IMPORT const BFTextFieldId RecordType;
   extern CLASS_IMPORT const BFTextFieldId GlobalLevelRebal;
   extern CLASS_IMPORT const BFTextFieldId AccountLevelRebal;
}

namespace REPORT 
{
//CP20030319   const int REPORT_COMMON_INFO = 1;
//CP20030319   const int REPORT_CRITERIA_LIST = 2;
}

namespace CRITERIA_VAL
{
	const BFFieldId AMSCode (10001, I_("AMSCode"));
	const BFFieldId AccountNum (10002, I_("AccountNum"));
	const BFFieldId EffectiveDate (10003, I_("StartDate"));
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ReportProcessIncludes.h-arc  $
//
//   Rev 1.3   Apr 09 2004 10:06:28   VADEANUM
//PET1005 FN11 - AMS Gaps.
//
//   Rev 1.2   Mar 21 2003 17:46:40   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 29 2002 13:11:48   HSUCHIN
//clean up
//
//   Rev 1.0   Nov 27 2002 11:57:46   HSUCHIN
//Initial Revision
 */
