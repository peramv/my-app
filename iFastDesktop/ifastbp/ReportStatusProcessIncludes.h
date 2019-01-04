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
   extern IFASTBP_LINKAGE const BFContainerId REPORT_PARAM_LIST;
   extern IFASTBP_LINKAGE const BFContainerId REPORT_STATUS_CRITERIA;
   extern IFASTBP_LINKAGE const BFContainerId REPORT_STATUS_LIST;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompanyId;   
   extern CLASS_IMPORT const BFIntegerFieldId SchedJobId;
   extern CLASS_IMPORT const BFTextFieldId ReportName;
   extern CLASS_IMPORT const BFDateFieldId StartDate;
   extern CLASS_IMPORT const BFDateFieldId EndDate;
   extern CLASS_IMPORT const BFTextFieldId StartTime;
   extern CLASS_IMPORT const BFTimeFieldId FinalTime;
   extern CLASS_IMPORT const BFTextFieldId CriteriaType;
   extern CLASS_IMPORT const BFTextFieldId CriteriaValue;   
   extern CLASS_IMPORT const BFTextFieldId IncludeExclude;
   extern CLASS_IMPORT const BFTextFieldId JobStatus;
   extern CLASS_IMPORT const BFTextFieldId ReportStatusHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId ReportStatusParamHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId OutputFileName;
   extern CLASS_IMPORT const BFTextFieldId OutputFilePath;
   extern CLASS_IMPORT const BFTextFieldId PrinterName;
}

namespace REPORT_STATUS
{
//CP20030319   const int REPORT_STATUS_CRITERIA = 1;
//CP20030319   const int REPORT_STATUS_LIST = 2;
//CP20030319   const int REPORT_PARAM_LIST = 3;   
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ReportStatusProcessIncludes.h-arc  $
//
//   Rev 1.3   Feb 21 2006 12:03:08   popescu
//Incindent# 544677 - correctly updates the Begin and End time of a work object.
//
//   Rev 1.2   Mar 21 2003 17:46:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Dec 08 2002 22:12:42   HSUCHIN
//added support for printer process and report view
//
//   Rev 1.0   Nov 29 2002 13:52:50   HSUCHIN
//Initial Revision
 */
