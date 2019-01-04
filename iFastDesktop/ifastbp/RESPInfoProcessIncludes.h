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
// ^FILE   : RESPInfoProcessIncludes.h
// ^AUTHOR : Dan Petolescu
// ^DATE   : 01/05/2000
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

#include <ifastdataimpl\dse_dstc0066_vw.hpp>
#include <ifastdataimpl\dse_dstc0066_req.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId RESPINFO_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RESPINFOBENEFICIARY_LIST;
}
namespace RESPINFONAMES
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const LAST_NAME_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const FIRST_NAME_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const HISTORY_PENDING_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const HISTORY;
   extern IFASTBP_LINKAGE const I_CHAR * const PENDING;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RESPInfoProcessIncludes.h-arc  $
 * 
 *    Rev 1.7   Mar 29 2010 23:06:56   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.6   Mar 21 2003 17:47:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:53:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   22 May 2002 18:20:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:18:14   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Mar 22 2000 09:02:30   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.2   Mar 08 2000 10:50:30   PETOLESC
// Modified the title bar as requested by qa.
// 
//    Rev 1.1   Feb 16 2000 10:22:44   PETOLESC
// Added the list to MFAccount.
// 
//    Rev 1.0   Jan 17 2000 14:46:28   PETOLESC
// Initial revision.
 * 
 *
 */

