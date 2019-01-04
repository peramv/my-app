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
//    Copyright 2005 by DST IFDS.
//
//******************************************************************************

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace TRANS_REFUND_PARAM
{
   //account number
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   //transaction number
   extern IFASTBP_LINKAGE const I_CHAR * const TRANS_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ESTATE_ALLOC;
   extern IFASTBP_LINKAGE const I_CHAR * const COMMISSION_REBATE;
   extern IFASTBP_LINKAGE const I_CHAR * const REBOOK_EXIST;
	extern IFASTBP_LINKAGE const I_CHAR * const FUND_CODE;
	extern IFASTBP_LINKAGE const I_CHAR * const CLASS_CODE;
}


namespace REBOOK
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const SAMEACCOUNTTRANSTYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSNUM;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REFUND_PARAM;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRADES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CONFIRMATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REFUND;



