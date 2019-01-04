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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : MinMaxInfoProcessIncludes.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/14/2000
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

#include <ifastdataimpl\dse_dstc0109_vw.hpp>
#include <ifastdataimpl\dse_dstc0109_req.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
// Need to define list and search ID's to be used by a GUI object talking to the
// process.

//CP20030319const int MINMAXINFO_CBO = 1;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MINMAXINFO_CBO;
}
namespace MINMAX
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const AS_OF_DATE;
   extern IFASTBP_LINKAGE const I_CHAR * const TAX_TYPE;

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MinMaxInfoProcessIncludes.h-arc  $
 * 
 *    Rev 1.4   Mar 21 2003 17:45:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.3   Oct 09 2002 23:53:30   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   22 May 2002 18:20:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.1   19 Mar 2002 13:18:02   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.0   Mar 20 2000 15:48:42   ZHANGCEL
 * Initial revision.
// 
//    Rev 1.1   Feb 29 2000 15:29:48   ZHANGCEL
// Added two new parameters
 * 
 *
 */

