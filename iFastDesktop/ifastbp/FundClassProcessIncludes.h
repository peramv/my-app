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

#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0063_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//CP20030319const int FUNDDETAIL_LIST = 1;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FUNDDETAIL_LIST;
}
namespace 
{
   const I_CHAR *CODE_USING_FUND_NAME      = I_( "0" );
   const I_CHAR *CODE_USING_FUND_NUMBER    = I_( "1" );
   const I_CHAR *CODE_USING_FUND_CODE      = I_( "2" );
   const I_CHAR *CODE_USING_FUND_CLASS     = I_( "3" );

   const I_CHAR *CODE_FOR_FUND         = I_( "0" );
   const I_CHAR *CODE_FOR_ALL_FUNDS        = I_( "1" );

   const I_CHAR *PARM_FUND_CODE          = I_( "FundCode" );
   const I_CHAR *PARM_FUND_CLASS         = I_( "FundClass" );
   const I_CHAR *PARM_FUND_NUMBER        = I_( "FundNumber" );

   const I_CHAR *PARM_SEARCHFOR          = I_( "SEARCHFOR" );
   const I_CHAR *PARM_SEARCHUSING        = I_( "SEARCHUSING" );
   const I_CHAR *PARM_SEARCHVALUE        = I_( "SEARCHVALUE" );
   const I_CHAR *PARM_SEARCHITEMFOUND      = I_( "SEARCHITEMFOUND" );
   const I_CHAR *PARM_SEARCHNAMELANGUAGE   = I_( "SEARCHNAMELANGUAGE" );
   const I_CHAR *PARM_DEF_LANGUAGE_MAIN    = I_( "MAIN" );
   const I_CHAR *PARM_DEF_LANGUAGE_ALTERNATE = I_( "ALTERNATE" );
   const I_CHAR *PARM_DEF_LANGUAGE_BOTH    = I_( "BOTH" );
}

namespace FUNDCLASSLIST
{
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const CLASS_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const SHR_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ONLY_ESOP_ELIGIBLE;
   extern IFASTBP_LINKAGE const I_CHAR * const MANAGEMENTFEE;
   extern IFASTBP_LINKAGE const I_CHAR * const MANAGEMENTFEE_REBATE;
}

namespace FUNDCLASS
{
   const BFFieldId USE_GROUPFUNDLIST(1000);
   const BFFieldId IS_IN_GROUPFUNDLIST(1001);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/*
*/


