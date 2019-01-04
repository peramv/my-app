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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TaxRatesProcessIncludes.h
// ^AUTHOR : Dan Petolescu
// ^DATE   : 12/13/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0112_vw.hpp>
#include <ifastdataimpl\dse_dstc0112_req.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TAXRATES_LIST;
}
// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int TAXRATES_LIST = 1;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TaxRatesProcessIncludes.h-arc  $
 * 
 *    Rev 1.5   Mar 21 2003 17:49:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:53:40   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   22 May 2002 18:19:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   19 Mar 2002 13:18:52   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   Feb 15 2000 18:56:52   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:24   SMITHDAV
 * Initial revision.
// 
//    Rev 1.0   Dec 29 1999 17:25:14   PETOLESC
// Initial revision.
 * 
 *
 */
