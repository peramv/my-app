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

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0137_vw.hpp>
#include <ifastdataimpl\dse_dstc0137_vwrepeat_record.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId HYPOTHETICALRED;
   extern IFASTBP_LINKAGE const BFContainerId HYPOTHETICALRED_DETAIL_LIST;
}
namespace HYPOTHETICALREDINFOLIT  
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNTNUM;  
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const CLASSCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const TRADEDATE;
   extern IFASTBP_LINKAGE const I_CHAR * const GROSSORNET;
   extern IFASTBP_LINKAGE const I_CHAR * const AMOUNTTYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const FULLREDEM;
   extern IFASTBP_LINKAGE const I_CHAR * const REDCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const AMOUNT;
   extern IFASTBP_LINKAGE const I_CHAR * const BAYCOM;
   /*
    extern IFASTBP_LINKAGE const I_CHAR * const SESSIONID;
    extern IFASTBP_LINKAGE const I_CHAR * const USER_ID;
    extern IFASTBP_LINKAGE const I_CHAR * const LANGUAGECODE;
    extern IFASTBP_LINKAGE const I_CHAR * const COMPANYID;
   */

}


