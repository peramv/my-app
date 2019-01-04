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
//#include "DSTC0006_VW.hpp"
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0055_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId TRANSACTION_BANK_INSTRUCTION_CBO;
}
// Temporarily, defining fields to use

//const int ACCT_USE_DESC_ = 1;
/*const int INST_CODE_ = 1;
const int INST_NAME_ = 2;
const int SWIFT_CODE_ = 3;
const int REF_NUMBER_ = 4;
const int TRANSIT_NO_ = 5;
const int BANK_ACCT_NUM_ = 6;
const int BANK_ACCT_NAME_ = 7;
const int BANK_ACCT_TYPE_ = 8;
const int BANK_ACCT_TYPE_DESC_ = 9;
const int CURRENCY_NAME_ = 10;
const int PAY_REASON_1_ = 11;
const int PAY_REASON_2_ = 12;
//const int EFFECTIVE_FROM_ = 14;
//const int STOP_DATE_ = 15;
const int TRANS_ID_ = 13;
const int ACCOUNT_NUM_ = 14;*/

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//const int SHAREHOLDER_BANK_INSTRUCTIONS_LIST = 1;
//const int SYSTEMATIC_LIST = 2;
//CP20030319const int TRANSACTION_BANK_INSTRUCTION_CBO = 1;
//CP20030319const int MFACCOUNT_CBO = 2;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransactionBankInstructionProcessIncludes.h-arc  $
 * 
 *    Rev 1.5   Mar 21 2003 17:49:30   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:53:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   22 May 2002 18:19:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   19 Mar 2002 13:19:00   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   Feb 15 2000 18:56:52   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:26   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:04:00   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
