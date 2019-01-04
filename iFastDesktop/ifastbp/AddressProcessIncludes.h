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
//
// ^FILE   : AddressProcessIncludes.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : 11/05/1999
//
// -----------------------------------------------------------------------------
//
// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

//name of the params used at transfering the search criteria to the business process

// Need to define list and search Id's to be used by a GUI object talking to the
// process.
#include <ifastdataimpl\dse_substitute_vw.hpp>
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
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_MAILING_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ADDRESSES_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_ADDRESS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_MAILING_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_ADDRESS;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_ADDRESS_INFO;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACCT_MAILING_OVERRIDE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId PROVINCE_LIST;	   
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Salutation;
   extern CLASS_IMPORT const BFTextFieldId CountryName;
   extern CLASS_IMPORT const BFTextFieldId kShareholderAddress;
   extern CLASS_IMPORT const BFTextFieldId ShareholderAddress;
   extern CLASS_IMPORT const BFTextFieldId ShareholderAddressF02;
   extern CLASS_IMPORT const BFTextFieldId EntityAddress;
   extern CLASS_IMPORT const BFTextFieldId Name12;
   extern CLASS_IMPORT const BFTextFieldId Yes_NO;
   extern CLASS_IMPORT const BFTextFieldId OPDeliveryOption;
   extern CLASS_IMPORT const BFTextFieldId OPDeliveryMethods; 
   extern CLASS_IMPORT const BFTextFieldId CnsntToWaive;
   extern CLASS_IMPORT const BFTextFieldId ShrAddressFormat;
   extern CLASS_IMPORT const BFTextFieldId PCLookupEnabled;
   

}

//CP20030319const int ADDRESSES_LIST        =  1;
//CP20030319const int ENTITY_LIST         =  2;  
//CP20030319const int ENTITY_ADDRESS_LIST     =  3;
//CP20030319const int ACCOUNT_MAILING_LIST    = 4;
//const int ACCOUNT_ADDRESS_INFO_LIST	=	4;
//CP20030319const int SHAREHOLDER_ADDRESS_INFO  = 5;
//CP20030319const int SHAREHOLDER_ADDRESS     = 6;
//const int ACCOUNT_ADDRESS_INFO		=	7;
//CP20030319const int SHAREHOLDER_LIST        =  8;
//CP20030319const int ENTITY_MAILING_LIST     =  9;

namespace ADDRLIT
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_ENTITY;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_TYPE;   	
   extern IFASTBP_LINKAGE const I_CHAR * const SEQ_NUMBER;   	
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRESS_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_SHAREHOLDER;
   extern IFASTBP_LINKAGE const I_CHAR * const SETTLEMENT;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRESS_KEY;   
   extern const BFFieldId REG_ADDR_READ_ONLY;   
   const BFFieldId SALUTATION_EDIT(14);
   const BFFieldId CREATE_MAIL_OVERRIDE(15);

}
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BROKER_ADDRESS;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AddressProcessIncludes.h-arc  $
 * 
 *    Rev 1.21   17 Jul 2009 14:06:36   walkerro
 * PET156681 FN03 - Postal Code lookup on address screen
 * 
 *    Rev 1.20   Sep 29 2005 10:55:30   yingbaol
 * PET1277,FN09: Add Mailing Option Overide for NASU Flow
 * 
 *    Rev 1.19   Mar 14 2005 17:20:08   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.18   Mar 11 2005 15:01:16   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update - work in progress.
 * 
 *    Rev 1.17   Feb 25 2005 13:19:38   porteanm
 * PET 1171 FN01 - EUSD Entity Address Search.
 * 
 *    Rev 1.16   Oct 14 2003 13:09:12   HERNANDO
 * PET893 FN08 - Salutation enhancement.
 * 
 *    Rev 1.15   Apr 03 2003 15:44:06   YINGBAOL
 * add Broker_Address_Process
 * 
 *    Rev 1.14   Apr 01 2003 16:52:38   FENGYONG
 * Add AcctMailingOverride list
 * 
 *    Rev 1.13   Mar 21 2003 17:35:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Feb 06 2003 10:19:40   linmay
 * added new fields for shareholderaddressfo2
 * 
 *    Rev 1.11   Oct 09 2002 23:53:00   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Oct 08 2002 11:48:16   YINGBAOL
 * take off those fields which is part of view 113 and 114
 * 
 *    Rev 1.9   Sep 23 2002 15:22:58   YINGBAOL
 * add fields
 * 
 *    Rev 1.8   Sep 13 2002 15:54:04   YINGBAOL
 * release 49
 * 
 *    Rev 1.7   Aug 29 2002 17:07:28   SMITHDAV
 * ClientLocale and Field interface changes.
 * 
 *    Rev 1.6   Aug 27 2002 10:08:14   HSUCHIN
 * sync up with 1.5.1.0
 * 
 *    Rev 1.5   Jun 11 2002 11:43:30   YINGBAOL
 * lauch address list dialoge for settlement
 * 
 *    Rev 1.4   22 May 2002 18:21:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:15:00   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Jul 17 2000 17:00:54   KOVACSRO
 * Added some new BR
 * 
 *    Rev 1.1   Feb 15 2000 18:56:12   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:56   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Jan 25 2000 18:05:22   YINGBAOL
 * fix
 * 
 *    Rev 1.9   Dec 02 1999 17:56:58   POPESCUS
 * Fixed crashes in search
 * 
 *    Rev 1.8   Nov 30 1999 15:25:04   YINGBAOL
 * add NASU
 * 
 *    Rev 1.7   Nov 24 1999 14:14:04   YINGBAOL
 * check in sync
 * 
 *    Rev 1.6   Nov 18 1999 16:14:18   YINGBAOL
 * split view 43 sync
 * 
 *    Rev 1.5   Nov 02 1999 15:55:08   YINGBAOL
 * add Shareholderlist
 * 
 *    Rev 1.4   Oct 29 1999 09:39:54   YINGBAOL
 * new list and CBO support
 * 
 *    Rev 1.3   Aug 25 1999 14:25:04   YINGBAOL
 * No change.
 * 
 *    Rev 1.2   Aug 18 1999 11:51:12   YINGBAOL
 * modify  for inc2
 * 
 *    Rev 1.1   Jul 08 1999 10:03:26   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

