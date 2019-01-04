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
//    AUTHOR : Serban Popescu
//    DATE   : October 2003
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0100_vw.hpp>
#include <ifastdataimpl\dse_dstc0100_req.hpp>


namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FinancialInstitutionsHeading;

   extern CLASS_IMPORT const BFTextFieldId BankIdType;
   extern CLASS_IMPORT const BFTextFieldId BankAddr;
   extern CLASS_IMPORT const BFTextFieldId InstCodeLabel;
}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FINANCIAL_INSTITUTION_LIST;
}

namespace FI_CATEGORY
{
   extern CLASS_IMPORT I_CHAR * const BANK;
   extern CLASS_IMPORT I_CHAR * const BANK_TRANSIT;
   extern CLASS_IMPORT I_CHAR * const INSTITUTION;
   extern CLASS_IMPORT I_CHAR * const INSTITUTION_TRANSIT;
   extern CLASS_IMPORT I_CHAR * const OTHER;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FinancialInstitutionProcessIncludes.h-arc  $
//
//   Rev 1.1   Oct 24 2003 17:18:40   popescu
//CIBC PET 809, FN 13
//
//   Rev 1.0   Oct 04 2003 16:06:08   popescu
//Initial revision.
//
 * 
 */

