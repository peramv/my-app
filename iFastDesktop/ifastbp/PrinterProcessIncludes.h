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
   extern IFASTBP_LINKAGE const BFContainerId PRINTER_LIST;
}
namespace PRINTER
{
//CP20030319   const int PRINTER_LIST = 1;
   const I_CHAR * const NAME = I_( "PrinterName" );   
   const I_CHAR * const COMPANY = I_( "CompanyId" );   
   const I_CHAR * const LOCAL = I_( "LocalPrinter" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId PrinterName;
   extern CLASS_IMPORT const BFTextFieldId Description;
   extern CLASS_IMPORT const BFTextFieldId PrinterHeadingSet;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PrinterProcessIncludes.h-arc  $
//
//   Rev 1.1   Mar 21 2003 17:46:06   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Dec 08 2002 22:10:46   HSUCHIN
//Initial Revision
 */
