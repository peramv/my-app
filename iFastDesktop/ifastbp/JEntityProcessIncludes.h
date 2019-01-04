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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ACBProcessIncludes.h
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int ENTITY_LIST = 1;

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0051_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_LIST;
}
namespace ENTITYLIT //entity search literals
{

   extern IFASTBP_LINKAGE const I_CHAR * const pACCOUNTNUM ;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JEntityProcessIncludes.h-arc  $
//
//   Rev 1.5   Sep 28 2004 10:31:36   YINGBAOL
//PET1145 FN01 Entity update
//
//   Rev 1.4   Mar 21 2003 17:43:46   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:53:24   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   22 May 2002 18:20:32   PURDYECH
//BFData Implementation
//
//   Rev 1.1   19 Mar 2002 13:17:48   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   Aug 10 2000 18:08:40   FENGYONG
//Initial revision.
 * 
 *
 */

