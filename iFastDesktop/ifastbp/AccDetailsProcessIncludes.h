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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by entity here

// Defining fields to use

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0017_vw.hpp>
#include <ifastdataimpl\dse_dstc0020_vw.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0049_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_vw.hpp>
#include <ifastdataimpl\dse_dstc0064_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>

#include <ifastdataimpl\dse_listviewheading.hpp>

#include <bfproc\bfcontainerid.hpp>


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ADDRESS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_IDS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDS_DETAILS_EX_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDS_DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId PENDING_TRADES_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_ADDRESS;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
   extern IFASTBP_LINKAGE const BFContainerId TRANSACTIONS_LIST;
}
namespace ACCDETLIT  //stands for account details literals
{
   const BFFieldId ACCOUNT_NUMBER_CODE(101);
   const BFFieldId ENTITY_ID_NUMBER(102);
   const BFFieldId PHONE_NUMBER(103);
   //fields for checking the permissions for displaying attributes
   const BFFieldId ACB_ATTR(104);
   const BFFieldId ADDRESS_BOOK_ATTR(105);
   const BFFieldId ENTITY_ATTR(106);
   const BFFieldId INTEREST_ACCRUED_ATTR(107);
   const BFFieldId CHEQUE_ATTR(108);
   const BFFieldId HIST_MKT_VALUE_ATTR(109);
   const BFFieldId DEMOGRAPHICS_ATTR(110);
   const BFFieldId DISTRIBUTION_ATTR(111);
   const BFFieldId AMOUNT_UNITS(112);
   const BFFieldId AMOUNT_DOLLARS(113);
   const BFFieldId ALT_ACCOUNT_NUMBER_CODE(114);
   const BFFieldId BROKER_CODE(115);
   const BFFieldId FUND_CURRENCY(116);
   const BFFieldId NEW_ACCOUNT_NUMBER(117);
   const BFFieldId INITIAL_ENTITY_ID(118);
   const BFFieldId RIF_LIF_LRIF_INFO(119);
   const BFFieldId RIF_LIF_LRIF_ALLOC_INFO(120);
   const BFFieldId CONTRACT_ATTR(121);
   const BFFieldId GUARANTEE_ATTR(122);
   const BFFieldId RESPINFO_ATTR(123);
   const BFFieldId RESP_TRANSACTIONS_ATTR(124);
   const BFFieldId YTD_CONTRIBUTION_ATTR(125);
   const BFFieldId AS_PENSION_ATTR(126);
   const BFFieldId ACCT_SPLIT_COMM(127);
   //other fields
   const BFFieldId FULL_TRANS_LIST(128);

   const BFFieldId FEE_PARAMETER_ATTR(129);
   const BFFieldId HYPOTHETICAL_REDEMPTION_ATTR(130);
   const BFFieldId ACCOUNTREVIEW(131);
   const BFFieldId PENSION_INFO_ATTR(132);
   const BFFieldId ESTATEMENT_ATTR(133);
   const BFFieldId AMS_OPTION(134);
   const BFFieldId ACCT_SETTLE_LOC(135);
   const BFFieldId ACCTCATEGORY_DESC(136);
   const BFFieldId FEEMODEL_ATTR(137);
   const BFFieldId HAS_FOF(138);
   const BFFieldId ACCT_SETTLE_RULE(139);
   const BFFieldId ACCT_TRAILER_FEE (140);
   const BFFieldId REFRESH_PORTFOLIO (141);
   const BFFieldId HAS_ACCT_OWNERSHIP_RECORD (142);

   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_ID_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const PHONE_NUM_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const ALT_ACCOUNT_NUM_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const BROKER_CODE_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const REFRESH_PENDING_TRADES;
}

namespace ENTSRCHLIT //entity search literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_CODE;
}

namespace SEARCHACCOUNTUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const CIF;
   extern IFASTBP_LINKAGE const I_CHAR* const HOUSEHOLD;
}  

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CategMargin;
   extern CLASS_IMPORT const BFTextFieldId CategLoan;
   extern CLASS_IMPORT const BFTextFieldId CategChqPriv;
   extern CLASS_IMPORT const BFTextFieldId CategWrap;

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccDetailsProcessIncludes.h-arc  $
 * 
 *    Rev 1.33   Jul 24 2012 19:07:28   dchatcha
 * P0179630 FN01 FATCA Project - Acct Ownership Allocation
 * 
 *    Rev 1.32   Feb 08 2012 20:31:30   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.31   Oct 27 2011 07:54:42   popescu
 * P0188902 - DYN Household Project - added new search criteria to look for accounts based on a household
 * 
 *    Rev 1.30   Nov 10 2010 03:59:00   dchatcha
 * PET0165541 FN03 - QESI Phase3 - Removed not necessary pieces of code.
 * 
 *    Rev 1.29   Oct 29 2010 09:46:38   kitticha
 * PET0165541 FN03 - QESI Phase3 - Fixed the duplicate fieldid.
 * 
 *    Rev 1.28   Oct 29 2010 06:18:50   kitticha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.27   Sep 30 2010 10:02:36   jankovii
 * PET168727 FN22 - Trailer Fee Setup
 * 
 *    Rev 1.26   Mar 11 2008 19:06:46   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.25   Sep 21 2007 17:58:52   smithdav
 * PET 2360 FN02 - Launch Global AMS screen from AcctDetails for FOF funds.
 * 
 *    Rev 1.24   22 Aug 2007 13:37:22   popescu
 * GAP 6 - search by CIF should return all the entities linked by CIF
 * 
 *    Rev 1.23   Aug 11 2004 18:40:10   FENGYONG
 * PET 1117 FN05 Syncup after get files resource 
 * 
 *    Rev 1.22   Aug 11 2004 11:59:46   AGUILAAM
 * PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
 * 
 *    Rev 1.21   Nov 27 2003 10:40:32   HERNANDO
 * PET892 FN1 - Added Settlement Location.
 * 
 *    Rev 1.20   Mar 21 2003 17:33:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.19   Jan 26 2003 15:25:44   KOVACSRO
 * Added account category fields.
 * 
 *    Rev 1.18   Nov 06 2002 14:17:04   HERNANDO
 * Added AMS_OPTION.
 * 
 *    Rev 1.17   Oct 09 2002 23:52:56   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.16   11 Sep 2002 10:26:48   HUANGSHA
 * added permission of eStatement
 * 
 *    Rev 1.15   Aug 29 2002 12:51:24   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   07 Jun 2002 18:44:50   HERNANDO
 * Added #include "dse_dstc0149_vw.hpp"
 * 
 *    Rev 1.13   Jun 02 2002 17:50:54   HSUCHIN
 * added pension info
 * 
 *    Rev 1.12   31 May 2002 13:30:04   HERNANDO
 * Added Account Review.
 * 
 *    Rev 1.11   22 May 2002 18:22:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.10   19 Mar 2002 13:14:40   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.9   26 Feb 2002 16:51:44   HSUCHIN
 * added hypothetical redemption
 * 
 *    Rev 1.8   Feb 19 2002 14:15:32   YINGBAOL
 * add FeeParameter Attribute
 * 
 *    Rev 1.7   19 Nov 2001 11:09:26   KOVACSRO
 * added FULL_TRANS_LIST field.
 * 
 *    Rev 1.6   13 Sep 2001 10:18:38   HSUCHIN
 * added AcctSplitComm
 * 
 *    Rev 1.5   Aug 23 2001 12:33:30   JANKAREN
 * Added As Pension Plan
 * 
 *    Rev 1.4   18 Aug 2001 09:27:54   HSUCHIN
 * added YTD stuff
 * 
 *    Rev 1.3   Jan 17 2001 10:17:42   KOVACSRO
 * Added a parameter REFRESH_PENDING_TRADES.
 * 
 *    Rev 1.2   Jul 19 2000 10:47:22   WINNIE
 * Filter Contract, RESP, Gurantee Attribute on account defail screen according to the taxtype, system features and permission
 * 
 *    Rev 1.1   Mar 20 2000 10:19:18   YINGBAOL
 * RIF_LIF and RIF_LIF_ALLOC added
 * 
 *    Rev 1.0   Feb 15 2000 10:58:54   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.12   Jan 28 2000 15:08:08   VASILEAD
 * Fixed diplaying Kana addresses
 * 
 *    Rev 1.11   Jan 12 2000 09:03:14   POPESCUS
 * changes related to cloning an account and fixing some validation, adding subst sets
 * 
 *    Rev 1.10   Dec 29 1999 18:11:34   BUZILA
 * changed COA flags
 * 
 *    Rev 1.9   Dec 24 1999 10:29:54   VASILEAD
 * Fixed NASU flow
 * 
 *    Rev 1.8   Dec 23 1999 11:29:10   POPESCUS
 * NASU process and the new confirmation model
 * 
 *    Rev 1.7   Nov 30 1999 18:24:52   POPESCUS
 * changes related to the NASU flow
 * 
 *    Rev 1.6   Nov 02 1999 10:28:44   YINGBAOL
 * 
 *    Rev 1.5   Oct 24 1999 16:26:54   VASILEAD
 * Sync up with M2
 * 
 *    Rev 1.4   Oct 05 1999 09:47:44   HUANGSHA
 * Set focus on the selected entity on detail screen if search for the AltAccount + BrokerCode
 * 
 *    Rev 1.3   Sep 03 1999 14:34:14   YINGZ
 * add listview header
 * 
 *    Rev 1.2   Jul 14 1999 16:42:52   VASILEAD
 * Add AMOUNT_UNITS and AMOUNT_DOLLARS
 * 
 *    Rev 1.1   Jul 08 1999 10:03:24   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
