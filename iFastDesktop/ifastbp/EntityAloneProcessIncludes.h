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
//    Copyright 2005 by IFDS, Inc.
//
//******************************************************************************
//
// ^FILE   : EntityAloneProcessIncludes.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : 01/31/2005
//
// -----------------------------------------------------------------------------
//
// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

//name of the params used at transfering the search criteria to the business process

// Need to define list and search Id's to be used by a GUI object talking to the
// process.
#include <ifastdataimpl\dse_substitute_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_IDS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId WHEREUSED_LIST;
  
}


namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TaxJuris;
   extern CLASS_IMPORT const BFTextFieldId EUSDTaxOption;
   extern CLASS_IMPORT const BFTextFieldId UpdShrTaxJuris;
   extern CLASS_IMPORT const BFDateFieldId TaxJurisDeff;
   extern CLASS_IMPORT const BFTextFieldId IsNetworkSender;
}

namespace EntityAlone
{
   const BFFieldId AGE_YEARS(1000);
   const BFFieldId AGE_MONTHS(1001);
   const BFFieldId SALUTATION_EDIT(1002);
   const BFFieldId UPDATE_SHAREHOLDER(1003);
   const BFFieldId ACCOUNT_ENTITY(1004);




/*   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRESS_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_SHAREHOLDER;
   extern IFASTBP_LINKAGE const I_CHAR * const SETTLEMENT;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRESS_KEY;   
   extern const BFFieldId REG_ADDR_READ_ONLY;
   const BFFieldId SALUTATION_EDIT(14);
*/

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EntityAloneProcessIncludes.h-arc  $
//
//   Rev 1.1   Jul 21 2006 14:00:58   jankovii
//PET 2192 FN02 - Dealings-Sender Cut-Off Time.
//
//   Rev 1.0   Mar 01 2005 09:57:06   yingbaol
//Initial revision.
 * 


 */