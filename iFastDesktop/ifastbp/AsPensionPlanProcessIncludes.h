#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : AsPensionPlanProcessIncludes.cpp
// ^AUTHOR : Karen Jan
// ^DATE   : July 25, 2001
//
//******************************************************************************
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0171_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ASPENSIONPLAN;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId EntityName;
}
namespace ASPENSIONPLANLIT  //stands for As Pension Plan literals
{

   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_NUM;


   //container ID
//CP20030319   const int ASPENSIONPLAN        = 1;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AsPensionPlanProcessIncludes.h-arc  $
//
//   Rev 1.5   Mar 21 2003 17:36:12   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:53:02   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   22 May 2002 18:21:46   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:15:08   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   04 Jan 2002 17:24:02   KOVACSRO
//Added EntityName field
//
//   Rev 1.0   Aug 23 2001 13:08:08   JANKAREN
//Initial revision.
//
 * 
 *
 */
