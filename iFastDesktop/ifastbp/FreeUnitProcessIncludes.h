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

//This needs to changed when Free Units view file is avaliable

#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0019_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int FREEUNIT_LIST = 1;
//CP20030319const int MFACCOUNT_CBO = 2;
const BFFieldId LIST_FILTER(3);
const BFFieldId FUND_CURRENCY(4);
const BFFieldId DSC_FEE_LEVEL( 101808 );

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FREEUNIT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId FREEAMOUNT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FREEUNIT_ACCT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FREEAMOUNT_ACCT_LIST;
}

namespace FREEUNITINFOLIT
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNTNUM;  
   extern IFASTBP_LINKAGE const I_CHAR * const ALLFUNDMODE;
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const CLASSCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const PRCNTHOLDING_LVL;
}

namespace PERCENT_FREE_LVL
{
   extern IFASTBP_LINKAGE const I_CHAR * const NOT_HOLDING;  
   extern IFASTBP_LINKAGE const I_CHAR * const ONLY_FUND_GROUP;  
   extern IFASTBP_LINKAGE const I_CHAR * const ONLY_FUND;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_AND_FNDGRP;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FreeAmountHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId FreeAmountAcctLevelHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId FreeUnitAcctLevelHeadingSet;
}