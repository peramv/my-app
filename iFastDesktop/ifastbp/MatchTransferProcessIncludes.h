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
// ^FILE   : MatchTransferProcessInclude.h
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/04/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Matching Transfer Record dialog
//
//******************************************************************************


#include <ifastdataimpl\dse_listviewheading.hpp>

#include <ifastdataimpl\dse_dstc0022_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_vwrepeat_record.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

// Need to define list and search ID's to be used by a GUI object talking to the
// process.

//CP20030319const int MATCHTRANSFER_CBO = 1;
//CP20030319const int FUNDMASTER_LIST  = 2;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FUNDMASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MATCHTRANSFER_CBO;
}
namespace MATCHTRANSFER
{
   const I_CHAR *ACCOUNTNUM = I_( "AccountNum" );
   const I_CHAR *TRANSID = I_( "TransId" );
   const I_CHAR *SHAREHOLDERNUM = I_( "ShareholderNum" );
   const I_CHAR *ENTITYID = I_( "EntityId" );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MatchTransferProcessIncludes.h-arc  $
//
//   Rev 1.5   Mar 21 2003 17:44:50   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:53:28   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   22 May 2002 18:20:22   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:17:56   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Sep 10 2001 16:54:02   ZHANGCEL
//Added a new parameter
//
//   Rev 1.0   Aug 16 2001 13:32:46   ZHANGCEL
//Initial revision.
 * 
 */

