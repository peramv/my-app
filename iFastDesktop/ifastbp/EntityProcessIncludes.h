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

//******************************************************************************
//
// ^FILE   : EntityProcess.cpp
// ^AUTHOR : Ady & Serban
// ^DATE   : 22/04/1999
//
// -----------------------------------------------------------------------------


#include <ifastdataimpl\dse_substitute_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId BACKGROUND_IDS_SEARCH;
   extern IFASTBP_LINKAGE const BFContainerId BACKGROUND_ON_BTN_SEARCH;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_IDS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RISK_LIST;
}
namespace SEARCH_PARAM
{
   const I_CHAR * const FIRST_NAME           = I_( "FirstName" );
   const I_CHAR * const LAST_NAME            = I_( "LastName" );
   const I_CHAR * const BIRTH_LAST_NAME      = I_( "BirthLastName" );
   const I_CHAR * const BIRTH_FIRST_NAME     = I_( "BirthFirstName" );
   const I_CHAR * const HOME_PHONE           = I_( "HomePhone" );
   const I_CHAR * const BUSINESS_PHONE       = I_( "BusinessPhone" );
   const I_CHAR * const ID_TYPE              = I_( "IdType" );
   const I_CHAR * const ID_VALUE             = I_( "IdValue" );
}

namespace ENTPROC
{

   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const CURRENT_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const MODEL_ACCOUNT_NUM;

   const BFFieldId ACCOUNT_NUMBER_FIELD(1);
   const BFFieldId PROC_CREATING_ACCOUNT(2);
   const BFFieldId PROC_CREATING_SHAREHOLDER(3);
   const BFFieldId SELECTION_KEY(4);
   const BFFieldId HAS_NON_DUMMY_RECORDS(5);
   const BFFieldId ACCOUNT_TYPE_FIELD(6);
   const BFFieldId PERCENT_AVAILABLE(7);
   const BFFieldId AGE_YEARS(9);
   const BFFieldId AGE_MONTHS(10);
   const BFFieldId SHR_NUM(11);
   const BFFieldId NEW_ITEM(12);
   const BFFieldId NEW_ACCOUNT(13);
   const BFFieldId SALUTATION_EDIT(14);
   const BFFieldId ACCOUNT_TYPE(15);
   const BFFieldId UPDATE_SHAREHOLDER(16);  
   const BFFieldId IS_RESPBENE_DELETED (17);  
   const BFFieldId LETTER_REQUIRED (18);  
   const BFFieldId RISK_DEFF_DATE_APPL(19);
   const BFFieldId ACCOUNT_TAX_TYPE(20);

   const BFFieldId ORG_KEY(1100);
   const BFFieldId DEST_KEY(1200);
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId EntityListViewHeading;
   extern CLASS_IMPORT const BFTextFieldId EntityIDSHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId DuplicateSINcheck;
   extern CLASS_IMPORT const BFTextFieldId CSSStopSINMatch;
   extern CLASS_IMPORT const BFTextFieldId FrFundNumber;
   extern CLASS_IMPORT const BFTextFieldId CountryCode;
   extern CLASS_IMPORT const BFTextFieldId OwnerSpouseName;
   extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
   extern CLASS_IMPORT const BFTextFieldId UpdShrTaxJuris;
   extern CLASS_IMPORT const BFTextFieldId BeneficiaryTitleDisplay;
   extern CLASS_IMPORT const BFTextFieldId AssigneeScreen;
   extern CLASS_IMPORT const BFTextFieldId NAME_LENGTH;
}

namespace IDS
{
   extern CLASS_IMPORT const I_CHAR * const CIF;
   extern CLASS_IMPORT const I_CHAR * const ACCESS_ID;
   extern CLASS_IMPORT const I_CHAR * const CLEARING_PLATFORM; //MT535/MT536
   extern CLASS_IMPORT const I_CHAR * const PASSPORT;
   extern CLASS_IMPORT const I_CHAR * const BIRTH_CERTIFICATE;
   extern CLASS_IMPORT const I_CHAR * const DRIVERS_LICENSE;
   extern CLASS_IMPORT const I_CHAR * const BUSINESS_NUMBER;
   extern CLASS_IMPORT const I_CHAR * const NATIONAL_ID;
   extern CLASS_IMPORT const I_CHAR * const TRUST_ACCOUNT_NUMBER;
   extern CLASS_IMPORT const I_CHAR * const BIC_CODE;
   extern CLASS_IMPORT const I_CHAR * const TAX_ID_NUMBER;
   extern CLASS_IMPORT const I_CHAR * const EMPLOYER_NUMBER;
   extern CLASS_IMPORT const I_CHAR * const TAX_FILE_NUMBER;        
   extern CLASS_IMPORT const I_CHAR * const AUSTRALIAN_BUSINESS_NUMBER;
   extern CLASS_IMPORT const I_CHAR * const AEOI;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EntityProcessIncludes.h-arc  $
 * 
 *    Rev 1.30   Jul 17 2012 19:19:46   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts, build error...
 * 
 *    Rev 1.29   Jul 13 2012 12:34:52   dchatcha
 * P0179630 FN01 FATCA Project - Entity level
 * 
 *    Rev 1.28   Jul 13 2012 12:32:20   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts, build error...
 * 
 *    Rev 1.27   Apr 05 2012 10:48:36   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.26   Feb 06 2012 02:59:12   panatcha
 * IN2780013 - SOC Loan Number and Loan Type
 * 
 *    Rev 1.25   Oct 13 2011 18:51:46   popescu
 * PETP0186486 FN01 - RRSP Loan Program - fixed a linkage warning
 * 
 *    Rev 1.24   Sep 02 2011 13:11:10   kitticha
 * PETP0186486 FN01 - RRSP Loan Program.
 * 
 *    Rev 1.23   May 06 2010 23:34:42   popescu
 * RESP/QESI fixes
 * 
 *    Rev 1.22   23 Jan 2009 16:32:06   popescu
 * Incident 	1548019 - reset button on entitymaintenance dlg, BIC Code can be valid/invalid for entitytype 58
 * 
 *    Rev 1.21   Dec 15 2008 02:21:50   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.20   17 Jul 2007 15:18:54   popescu
 * GAP 6 CIF - AIM
 * 
 *    Rev 1.19   27 Jun 2007 16:47:26   popescu
 * Incident# 929895 - enable search button and create a new entity if this is used.
 * 
 *    Rev 1.18   Mar 04 2005 17:12:46   yingbaol
 * PET1171,FN01:EUSD add Tax Jurisdiction
 * 
 *    Rev 1.17   Feb 28 2004 16:05:56   HERNANDO
 * PET965 FN11 - Additional historical enhancement.  Added Account Type.
 * 
 *    Rev 1.16   Oct 14 2003 11:32:28   HERNANDO
 * PET893 FN08 - Salutation Enhancement.
 * 
 *    Rev 1.15   Mar 21 2003 17:39:00   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Oct 09 2002 23:53:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.13   Aug 29 2002 12:52:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.12   22 May 2002 18:21:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   19 Mar 2002 13:16:56   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.10   Sep 12 2001 10:49:08   ZHANGCEL
 * Added a new parameter: MODEL_ACCOUNT_NUM
 * 
 *    Rev 1.9   Jul 29 2001 15:04:46   YINGBAOL
 * take out entity_do_reset
 * 
 *    Rev 1.8   18 May 2001 12:43:28   HSUCHIN
 * removed REPOSITORY_LIST (not used)
 * 
 *    Rev 1.7   Dec 20 2000 10:01:26   ZHANGCEL
 * Added two paremeters for CopyEntity requirement
 * 
 *    Rev 1.6   Nov 13 2000 10:15:18   KOVACSRO
 * Added DuplicateSINcheck.
 * 
 *    Rev 1.5   Sep 26 2000 11:15:18   OLTEANCR
 *  .
 * 
 *    Rev 1.4   Jul 28 2000 16:08:16   YINGBAOL
 * add new item logic
 * 
 *    Rev 1.3   Jul 26 2000 11:14:26   YINGBAOL
 * first version for C2
 * 
 *    Rev 1.2   Mar 09 2000 14:30:52   VASILEAD
 * Updated Entity screen for C2
 * 
 *    Rev 1.1   Feb 15 2000 18:56:26   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:06   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.16   Jan 23 2000 16:44:48   VASILEAD
 * Reset functionality
 * 
 *    Rev 1.15   Jan 13 2000 17:39:40   VASILEAD
 * Added support for catching errors
 * 
 *    Rev 1.14   Jan 12 2000 11:39:02   VASILEAD
 * Fixed compilation error 
 * 
 *    Rev 1.13   Jan 10 2000 16:15:06   VASILEAD
 * Added Joint information in Entity screen
 * 
 *    Rev 1.12   Jan 09 2000 14:58:30   VASILEAD
 * Corrected entity screen in the NASU
 * 
 *    Rev 1.11   Dec 21 1999 10:42:14   VASILEAD
 * Added Entity list iteration based on the string keys and not on the ObjectKey, added background search support
 * 
 *    Rev 1.10   Dec 15 1999 10:44:14   VASILEAD
 * Implemented background search for Entity screen
 * 
 *    Rev 1.9   Dec 07 1999 12:22:08   VASILEAD
 * Fixes in Entity
 * 
 *    Rev 1.8   Nov 25 1999 15:54:18   VASILEAD
 * Added new conditions
 * 
 *    Rev 1.7   Nov 23 1999 18:05:44   POPESCUS
 * NASU flow
 * 
 *    Rev 1.6   Nov 22 1999 14:35:08   BUZILA
 * added EntityIDSHeadingSet..
 * 
 *    Rev 1.5   Aug 27 1999 15:07:08   YINGZ
 * ?
 * 
 *    Rev 1.4   Aug 12 1999 14:21:08   DT24433
 * changed GEN_PROC_LIST to non-zero value
 * 
 *    Rev 1.3   Jul 28 1999 12:04:36   BUZILA
 * added to EntityProcess the getField(...) method 
 * 
 *    Rev 1.2   Jul 27 1999 15:03:20   BUZILA
 * First M2 revision
 * 
 *    Rev 1.1   Jul 08 1999 10:03:42   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
