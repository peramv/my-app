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
//    Copyright 2002 by Internantional Financial.
//
//******************************************************************************

//#include <ifastdataimpl\dse_dstc0305_vw.hpp>
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
   extern IFASTBP_LINKAGE const BFContainerId FUNDSPONSOR_FEE_MODEL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDSPONSOR_FEE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FEE_SCALE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_LIST;
}
namespace FUNDSPONSORFEEMODEL  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_SCR;
   extern IFASTBP_LINKAGE const I_CHAR * const FEE_MODEL_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCHTYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_SPONSOR_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const SYSTEM;
   extern IFASTBP_LINKAGE const I_CHAR * const ALL;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNTNUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNTSCR;

   const BFFieldId FeeModelExists (10001);
}

namespace ifds
{
/*
   extern CLASS_IMPORT const BFTextFieldId FeeParamListSet;
   extern CLASS_IMPORT const BFTextFieldId FeeScaleListSet;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId GSTExempt;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
*/
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundSponsorFeeModelProcessInclude.h-arc  $
//
//   Rev 1.3   Jul 13 2005 17:38:02   popescu
//Incident 352435 - improved performance on the fund sponsor fee model screen - get rid of the wacky keys
//
//   Rev 1.2   Jan 21 2005 17:33:12   Fengyong
//PET10037902 - show all the records after click more button
//
//   Rev 1.1   Aug 10 2004 11:12:12   FENGYONG
//PET117 FN5 - Client Condition Fee
//
//   Rev 1.0   Aug 09 2004 10:04:34   FENGYONG
//Initial revision.
//
 * 
 */