#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

extern IFASTBP_LINKAGE const I_CHAR *NASU_BUFFER;

namespace IFASTBP_PROC
{
}
namespace NASULIT //nasu literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const CREATING_ACCOUNT;
   extern IFASTBP_LINKAGE const I_CHAR * const CREATING_SHAREHOLDER;
   extern IFASTBP_LINKAGE const I_CHAR * const TRXNS_ERROR;
   extern IFASTBP_LINKAGE const I_CHAR * const PARM_CALLED_FROM;
   extern IFASTBP_LINKAGE const I_CHAR * const COMMANDRETURN;
   extern IFASTBP_LINKAGE const I_CHAR * const COMMANDCANCEL;
   extern IFASTBP_LINKAGE const I_CHAR * const COMMANDOK;
   extern IFASTBP_LINKAGE const I_CHAR * const CanCelAfterAccountInfo;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/NASUProcessIncludes.h-arc  $
 * 
 *    Rev 1.8   Mar 21 2003 17:45:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:53:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Jul 26 2002 15:28:34   YINGBAOL
 * fix PTS10009161
 * 
 *    Rev 1.5   22 May 2002 18:20:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:18:04   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   21 Nov 2001 10:08:14   HSUCHIN
 * added COMMANDRETURN, COMMANDOK, COMMANDCANCEL.
*/