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
//    DATE   : 21/07/99
//
//******************************************************************************


//include the data sets
#include <ifastdataimpl\dse_substitute_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//name of the substitute list fields
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FILLER;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SearchCriteria;   
   extern CLASS_IMPORT const BFTextFieldId SearchUsing;   

   extern CLASS_IMPORT const BFTextFieldId SearchAccountUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchChequeUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchCertificateUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchSystematicsUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchBankingUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchEntityUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchAddressUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchCOAUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchDistributionsUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchAllocationsUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchShareholderUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchAccountInfoUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchLabels;
   extern CLASS_IMPORT const BFTextFieldId SearchTradeUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchAMSUsing;   
   extern CLASS_IMPORT const BFTextFieldId SearchAllEntityUsing;   
   extern CLASS_IMPORT const BFTextFieldId SearchAccountRegulatoryUsing;
}

namespace SEARCHCRITERIA
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const CHEQUE_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const CERTIFICATE_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const SYSTEMATICS_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const BANKING_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const ENTITY_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const ADDRESS_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const COA_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const DISTRIBUTIONS_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const ALLOCATIONS_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const SHAREHOLDER_INFO_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_INFO_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const TRADE_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const AMSGLOBAL_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const ALLENTITY_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_REGULATORY_SEARCH;

   extern IFASTBP_LINKAGE const BFFieldId CURRENT_USING_LIST;
   extern IFASTBP_LINKAGE const BFFieldId LABEL1;
   extern IFASTBP_LINKAGE const BFFieldId LABEL2;
   extern IFASTBP_LINKAGE const BFFieldId LABEL3;
}

namespace SEARCHACCOUNTUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const NAME;
   extern IFASTBP_LINKAGE const I_CHAR* const TELEPHONE;
   extern IFASTBP_LINKAGE const I_CHAR* const SOCIAL_INSURANCE_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const CREDIT_CARD;
   extern IFASTBP_LINKAGE const I_CHAR* const DRIVER_LICENSE;
   extern IFASTBP_LINKAGE const I_CHAR* const PASSPORT;
   extern IFASTBP_LINKAGE const I_CHAR* const BIRTH_CERTIFICATE;
   extern IFASTBP_LINKAGE const I_CHAR* const NATIONAL_ID;
   extern IFASTBP_LINKAGE const I_CHAR* const SOCIAL_SECURITY_INSURANCE_CARD;
   extern IFASTBP_LINKAGE const I_CHAR* const SHAREHOLDER_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const ALT_ACCOUNT_AND_BROKER_CODE;
   extern IFASTBP_LINKAGE const I_CHAR* const BROKER_CODE;
   extern IFASTBP_LINKAGE const I_CHAR* const ID_OTHER;
   extern IFASTBP_LINKAGE const I_CHAR* const BIRTH_NAME;
   extern IFASTBP_LINKAGE const I_CHAR* const INTERMEDIARY_CODE;
   extern IFASTBP_LINKAGE const I_CHAR* const OTHER_REFERENCE_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const BUSINESSNO;
   extern IFASTBP_LINKAGE const I_CHAR* const CIF;
   extern IFASTBP_LINKAGE const I_CHAR* const ACCESS_ID;
   extern IFASTBP_LINKAGE const I_CHAR* const CLEARING_ID; //MT535/MT536
   extern IFASTBP_LINKAGE const I_CHAR* const HOUSEHOLD; 
   extern IFASTBP_LINKAGE const I_CHAR* const REGISTRATION_AGENT;
   extern IFASTBP_LINKAGE const I_CHAR* const CPFB_NUMBER;
}  

namespace SEARCHCHEQUEUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const CHEQUE_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const BROKER;
}

namespace SEARCHCERTIFICATEUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const CERTIFICATE_NUMBER_AND_FUND_CODE;
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
}

namespace SEARCHSYSTEMATICSUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
}

namespace SEARCHBANKINGUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const BROKER_CODE;
   extern IFASTBP_LINKAGE const I_CHAR* const BRANCH_CODE;
   extern IFASTBP_LINKAGE const I_CHAR* const REP_CODE;
   extern IFASTBP_LINKAGE const I_CHAR* const NEW_ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const CLIENT;
   extern IFASTBP_LINKAGE const I_CHAR* const FUND;
   extern IFASTBP_LINKAGE const I_CHAR* const FUND_CLASS;
   extern IFASTBP_LINKAGE const I_CHAR* const FUND_GROUP;
   extern IFASTBP_LINKAGE const I_CHAR* const FUND_SPONSOR;
   extern IFASTBP_LINKAGE const I_CHAR* const REG_AGENT;
}

namespace SEARCHENTITYUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ENTITY_ID;
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const NAME;
   extern IFASTBP_LINKAGE const I_CHAR* const SOCIAL_SECURITY_INSURANCE_CARD;
   extern IFASTBP_LINKAGE const I_CHAR* const PASSPORT;
   extern IFASTBP_LINKAGE const I_CHAR* const DRIVER_LICENSE;
   extern IFASTBP_LINKAGE const I_CHAR* const SOCIAL_INSURANCE_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const CREDIT_CARD;
   extern IFASTBP_LINKAGE const I_CHAR* const BIRTH_CERTIFICATE;
   extern IFASTBP_LINKAGE const I_CHAR* const NATIONAL_ID;
   extern IFASTBP_LINKAGE const I_CHAR* const CPFB_ACCT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_MANAGER_UNIQUE_ID;
}

namespace SEARCHALLENTITYUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ENTITY_ID;
   extern IFASTBP_LINKAGE const I_CHAR* const NAME;
   extern IFASTBP_LINKAGE const I_CHAR* const SOCIAL_SECURITY_INSURANCE_CARD;
   extern IFASTBP_LINKAGE const I_CHAR* const PASSPORT;
   extern IFASTBP_LINKAGE const I_CHAR* const DRIVER_LICENSE;
   extern IFASTBP_LINKAGE const I_CHAR* const SOCIAL_INSURANCE_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const CREDIT_CARD;
   extern IFASTBP_LINKAGE const I_CHAR* const BIRTH_CERTIFICATE;
   extern IFASTBP_LINKAGE const I_CHAR* const NATIONAL_ID;
   extern IFASTBP_LINKAGE const I_CHAR* const WHEREUSE;
   extern IFASTBP_LINKAGE const I_CHAR* const REG_AGENT;
}

namespace SEARCHADDRESSUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const SHAREHOLDER_NUMBER;
}

namespace SEARCHCOAUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
}

namespace SEARCHDISTRIBUTIONSUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
}

namespace SEARCHALLOCATIONSUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
}

namespace SEARCHSHAREHOLDERUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const SHAREHOLDER_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
}

namespace SEARCHACCOUNTINFOUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
}

namespace SEARCHTRADEUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const SHAREHOLDER_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const ACOUNT_BROKER;
}

namespace SEARCHGLOBALUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const REBALANCING;
   extern IFASTBP_LINKAGE const I_CHAR* const REPORT;
}

namespace SEARCHFEEMODELUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ALLFEEMODEL;
   extern IFASTBP_LINKAGE const I_CHAR* const FEEMODELCODE;
   extern IFASTBP_LINKAGE const I_CHAR* const FUNDSPONSORCODE;
}

namespace SEARCHACCOUNTREGULATORYUSING
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR* const OTHER_REFERENCE_NUMBER;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FillSearchCriteriaProcessIncludes.h-arc  $
 * 
 *    Rev 1.28   May 01 2012 09:25:12   if991250
 * CPF - validating that the Registration agent has the appropriate tax type for the CPF account
 * 
 *    Rev 1.27   Apr 16 2012 17:25:44   if991250
 * CPF Account Setup
 * 
 *    Rev 1.26   Apr 04 2012 20:50:14   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.25   Apr 04 2012 11:19:56   wp040039
 * PETP0187485-Registration Agent  Banking
 * 
 *    Rev 1.24   Oct 27 2011 07:28:04   popescu
 * P0188902 - DYN Household Project - added new search criteria to look for accounts based on a household
 * 
 *    Rev 1.23   Dec 15 2008 02:28:30   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.22   Sep 08 2008 15:55:10   jankovii
 * PET 5517 FN71 - Stale Cheque.
 * 
 *    Rev 1.21   12 Jul 2007 18:41:14   popescu
 * GAP 6 - CIF - added two new search types on the main screen - by CIF and by AccessID
 * 
 */
