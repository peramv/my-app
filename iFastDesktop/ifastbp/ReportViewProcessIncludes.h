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
}
namespace REPORT_VIEW
{
   const I_CHAR * const REPORTNAME = I_( "ReportName" );   
   const I_CHAR * const REPORTPATH = I_( "ReportPath" );
   const I_CHAR * const REPORTDATA = I_( "ReportData" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Description;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ReportViewProcessIncludes.h-arc  $
//
//   Rev 1.3   Mar 21 2003 17:46:56   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Dec 10 2002 13:34:58   HSUCHIN
//added dogetfield
//
//   Rev 1.1   Dec 10 2002 10:59:24   HSUCHIN
//added report data
//
//   Rev 1.0   Dec 08 2002 22:10:56   HSUCHIN
//Initial Revision
 */
