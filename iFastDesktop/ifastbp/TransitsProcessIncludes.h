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
   extern CLASS_IMPORT const BFTextFieldId TransitsHeading;

   extern CLASS_IMPORT const BFTextFieldId BankIdType;
   extern CLASS_IMPORT const BFTextFieldId BankAddr;
   extern CLASS_IMPORT const BFTextFieldId InstCodeLabel;
}

const BFFieldId InstCateg(1);
const BFFieldId InstName(2);
const BFFieldId IsSupport(3);

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TRANSITS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FINANCIAL_INSTITUTION;
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
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransitsProcessIncludes.h-arc  $
//
//   Rev 1.1   Oct 27 2003 19:48:30   popescu
//CIBC PET809, FN 13, added Transit Search by name
//
//   Rev 1.0   Oct 04 2003 16:06:16   popescu
//Initial revision.
//
 * 
 */

