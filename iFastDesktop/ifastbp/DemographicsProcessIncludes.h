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

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0011_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>

// Temporarily, defining fields to use

/*//const int SHAREHOLDER_NUM_ = 1;
const int BIRTH_DATE_ = 1;
const int GENDER_ = 2;
const int MARITAL_CODE_ = 3;
const int MARITAL_DESC_ = 4;
const int EMPLOYER_ = 5;
const int EMPLOYED_YRS_ = 6;
const int INDUSTRY_CODE_ = 7;
const int INDUSTRY_DESC_ = 8;
const int OCCUPATIONAL_CODE_ = 9;
const int OCCUPATIONAL_DESC_ = 10;
const int ANNUAL_INCOME_CODE_ = 11;
const int ANNUAL_INCOME_DESC_ = 12;
const int NET_WORTH_CODE_ = 13;
const int NET_WORTH_DESC_ = 14;
const int INV_OBJ_CODE_ = 15;
const int INV_OBJ_DESC_ = 16;
const int INV_KNOWLEDGE_CODE_ = 17;
const int INV_KNOWLEDGE_DESC_ = 18;
const int INV_HORIZON_CODE_ = 19;
const int INV_HORIZON_DESC_ = 20;
const int RISK_TOLERANCE_CODE_ = 21;
const int RISK_TOLERANCE_DESC_ = 22;
const int OTHER_INVESTMENTS_ = 23;
const int ADVISOR_CODE_ = 24;
const int ADVISOR_DESC_ = 25;
const int WITNESS_NAME_ = 26;
const int WITNESS_ADDR_1_ = 27;
const int WITNESS_ADDR_2_ = 28;
const int EFFECTIVE_DATE_ = 29;
const int PROCESS_DATE_ = 30;
const int PERSONAL_SEC_CODE_ = 31;
const int VERSION_NUM_ = 32;
const int ACCOUNT_NUM_ = 33;*/

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int DEMOGRAPHICS_CBO       = 1;
//CP20030319const int MFACCOUNT_CBO          = 2;
const BFFieldId PRIMARY_ACCOUNT_OWNER(500);

const BFFieldId ENTITY_LAST_NAME( 1001 );
const BFFieldId ENTITY_FIRST_NAME( 1002 );
const BFFieldId DEMO_ENTITY_ID( 12001 );

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId DEMOGRAPHICS_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId REGULATORY_STANDARD_LIST;
}

namespace 
{
   const I_CHAR * const DEMOGRAPHICS_TITLE = I_("DemographicsTitle");
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DemographicsProcessIncludes.h-arc  $
 * 
 *    Rev 1.9   Sep 12 2008 06:54:20   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.8   Jul 16 2008 16:01:04   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.7   Mar 21 2003 17:38:30   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:53:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Aug 29 2002 12:52:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 18:21:18   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:15:32   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Jul 20 2000 16:53:44   HUANGSHA
 * Fixed the Crash problem lauched from NASU
 * 
 *    Rev 1.1   Feb 15 2000 18:56:24   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:04   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Nov 11 1999 09:48:48   ZHANGCEL
 * add a paremeter
 * 
 *    Rev 1.1   Jul 08 1999 10:03:42   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
