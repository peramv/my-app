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

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

//name of the params used at transfering the search criteria to the business process
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0023_req.hpp>
#include <ifastdataimpl\dse_dstc0023_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0063_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FI_FUND_DETAIL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FI_FUND_INFO_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FI_FUND_MASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FI_PROC_GEN_LIST;
   extern IFASTBP_LINKAGE const BFContainerId UNIT_FACTORS_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundInfoSet;
}

#define FUND_CODE_VALUE			    I_( "FundCodeValue" )
#define CLASS_CODE_VALUE	     	 I_( "ClassCodeValue" )
#define FROM_DATE_VALUE			    I_( "FromDateValue" )
#define TO_DATE_VALUE			    I_( "ToDateValue" )
#define PREV_DATE_PRESSED_VALUE   I_( "PrevDatePressedValue" )
#define NEXT_DATE_PRESSED_VALUE   I_( "NextDatePressedValue" )
#define NEXT_KEY_VALUE            I_( "NextKeyValue" )

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/UnitFactorProcessIncludes.h-arc  $
//
//   Rev 1.0   Sep 09 2004 10:40:58   HERNANDO
//Initial revision.
 */
