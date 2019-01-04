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
// ^FILE   : ContractInfoProcessIncludes.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/01/2000
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

#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0105_vw.hpp>
#include <ifastdataimpl\dse_dstc0105_req.hpp>
#include <ifastdataimpl\dse_dstc0087_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0133_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

// Need to define list and search ID's to be used by a GUI object talking to the
// process.

//CP20030319const int CONTRACTINFO_LIST = 1;
//CP20030319const int SHAREHOLDER_CBO   = 2;
//CP20030319const int MFACCOUNT_CBO     = 3;
//CP20030319const int MASTER_CONTRACT_LIST   = 4;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId CONTRACTINFO_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MASTER_CONTRACT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
}
namespace CONTRACT
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLD_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSID_EMPTY;
   // folowing parameters are used for DofBirth checking
   extern IFASTBP_LINKAGE const I_CHAR * const OWNER_ENTITYID;
   extern IFASTBP_LINKAGE const I_CHAR * const OWNER_NAME;
   extern IFASTBP_LINKAGE const I_CHAR * const SPOUSE_ENTITYID;
   extern IFASTBP_LINKAGE const I_CHAR * const SPOUSE_NAME;
   extern IFASTBP_LINKAGE const I_CHAR * const ASK_SPOUSE_DOFBIRTH;
   extern IFASTBP_LINKAGE const I_CHAR * const ASK_ENTITY_DOFBIRTH;
   extern IFASTBP_LINKAGE const I_CHAR * const NON_ANNUITANT_ENTITY;

   const BFFieldId ORG_KEY(1100);
   const BFFieldId DEST_KEY(1200);
   const BFFieldId CHECKDOFBIRTH(1300);
   const BFFieldId ISADDNEW(1400);
}

namespace ifds
{ 
   extern CLASS_IMPORT const BFTextFieldId GWOContract;
   extern CLASS_IMPORT const BFTextFieldId IsNewAcctContract;
   extern CLASS_IMPORT const BFTextFieldId IsDuringNASU;
}

namespace NASULIT //nasu literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const CREATING_ACCOUNT;
   extern IFASTBP_LINKAGE const I_CHAR * const CREATING_SHAREHOLDER;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ContractInfoProcessIncludes.h-arc  $
 * 
 *    Rev 1.18   Dec 27 2011 00:57:44   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.17   Apr 20 2006 16:16:08   porteanm
 * PET2102 FN02 - For 71 - Added isGWOContract and isNewAcctContract.
 * 
 *    Rev 1.16   Mar 20 2005 20:01:26   hernando
 * PET1024 FN02 - Added Include for Contract Master List.
 * 
 *    Rev 1.15   Mar 21 2003 17:38:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Oct 09 2002 23:53:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.13   Aug 29 2002 12:52:04   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.12   22 May 2002 18:21:28   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   19 Mar 2002 13:15:30   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.10   Nov 07 2001 14:40:40   ZHANGCEL
 * Added a new parameter: ASK_ENTITY_DOFBIRTH
 * 
 *    Rev 1.9   Jul 25 2001 16:15:14   OLTEANCR
 * unchanged
 * 
 *    Rev 1.8   Jul 17 2001 09:40:08   OLTEANCR
 * added logic for multicontracts
 * 
 *    Rev 1.7   May 11 2001 16:08:58   OLTEANCR
 * unchanged
 * 
 *    Rev 1.6   Sep 21 2000 14:44:10   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.5   May 12 2000 17:51:28   ZHANGCEL
 * Deal with DofBirth checking problems
 * 
 *    Rev 1.4   Apr 11 2000 11:29:14   ZHANGCEL
 * Added a parameter for DofBirth
 * 
 *    Rev 1.3   Mar 15 2000 10:04:26   ZHANGCEL
 * Bugs fixed
 * 
 *    Rev 1.2   Mar 07 2000 10:26:06   HSUCHIN
 * changed to use new infra
 * 
 *    Rev 1.1   Feb 15 2000 18:56:22   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:04   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.0   Feb 03 2000 13:23:44   ZHANGCEL
 * Initial revision.
 * 
 *
 */
