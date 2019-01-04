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
#include <ifastdataimpl\dse_dstc0145_req.hpp>
#include <ifastdataimpl\dse_dstc0145_vw.hpp>

//CP20030319const int VERIFICATIONCONF_CBO = 1;

const I_CHAR *VERIFICATIONCONF_INPUT = I_("VERIFICATIONCONF_INPUT");

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId VERIFICATIONCONF_CBO;
}
namespace VERIFICATIONCONFLT  //stands for verification confirmation literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const TRACKSHR;
   extern IFASTBP_LINKAGE const I_CHAR * const SHRNUM_TRACKSHR;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCTDESIGNATION_TRACKSHR;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCTTYPE_TRACKSHR;
   extern IFASTBP_LINKAGE const I_CHAR * const GROUPCODE_TRACKSHR;
   extern IFASTBP_LINKAGE const I_CHAR * const RESPROVCODE_TRACKSHR;
   extern IFASTBP_LINKAGE const I_CHAR * const TAXJURISCODE_TRACKSHR;
   extern IFASTBP_LINKAGE const I_CHAR * const TAXTYPE_TRACKSHR;
   extern IFASTBP_LINKAGE const I_CHAR * const INSTCODE_TRACKSHR;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSITNO_TRACKSHR;
   extern IFASTBP_LINKAGE const I_CHAR * const BANKACCTNUM_TRACKSHR;

   extern IFASTBP_LINKAGE const I_CHAR * const TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const SHRNUM_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNTNUM_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDITIONALINFO_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const ALTACCOUNT_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const BENOWNER_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const BRANCHCODE_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const BRANCHNAME_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const BROKERCODE_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const BROKERNAME_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const CURRENCY_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const EMPLOYEE_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const INTRUSTFOR_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const ITFDETAILS_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const MARKETMAIL_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const SALESREPCODE_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const SALESREPNAME_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const STOPPUR_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const STOPRED_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const STOPXFERIN_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const STOPXFEROUT_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const SUPCONF_TRACKACT;
   extern IFASTBP_LINKAGE const I_CHAR * const UNSEIZABLE_TRACKACT;

   extern IFASTBP_LINKAGE const I_CHAR * const TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNTNUM_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITYID_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const AUTHORIZEDTOTRADE_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const BUSEXT_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const BUSPHONE_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const DOFBIRTH_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const EMAIL_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITYTYPE_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const FIRSTNAME_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const GENDER_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const HOMEFAX_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const HOMEPHONE_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const LANG_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const LASTNAME_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const SALUTATION_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const SIN_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const BENIRREVOCABLE_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const BENPERCENTAGE_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const BENRELATECODE_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const JOINTDISPCODE_TRACKENT;
   extern IFASTBP_LINKAGE const I_CHAR * const JOINTTYPE_TRACKENT;

   extern IFASTBP_LINKAGE const I_CHAR * const TRACKADD;
   extern IFASTBP_LINKAGE const I_CHAR * const SHRNUM_TRACKADD;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRCODE_TRACKADD;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRLINE1_TRACKADD;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRLINE2_TRACKADD;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRLINE3_TRACKADD;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRLINE4_TRACKADD;
   extern IFASTBP_LINKAGE const I_CHAR * const COUNTRYCODE_TRACKADD;
   extern IFASTBP_LINKAGE const I_CHAR * const EXCEPTIONMAIL_TRACKADD;
   extern IFASTBP_LINKAGE const I_CHAR * const EXCEPTIONDETAILS_TRACKADD;
   extern IFASTBP_LINKAGE const I_CHAR * const POSTALCODE_TRACKADD;

   extern IFASTBP_LINKAGE const I_CHAR * const TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNTNUM_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSID_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDITIONALINFO_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const AMOUNT_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const AMOUNTTYPE_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const CHEQUEADDR_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const CLASSFROMCODE_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const CLASSFROMNAME_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const CLASSTOCODE_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const CLASSTONAME_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const EXCHRATE_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const FEE_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const FLATPERCENT_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDFROMCODE_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDFROMNAME_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDTOCODE_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDTONAME_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const PAYTYPE_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const SETTLECURRENCY_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const SETTLEINFUNDCURR_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSTYPE_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const DIVTOSAMEFUND_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const DIVTOFUNDLIST_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const DIVTOCLASSLIST_TRACKTXN;
   extern IFASTBP_LINKAGE const I_CHAR * const DIVTOPERCENTLIST_TRACKTXN;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/VerificationConfProcessIncludes.h-arc  $
//
//   Rev 1.8   Mar 21 2003 17:50:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Mar 11 2003 13:50:02   PURDYECH
//Fixes to help the DataGroupId source code converters work more smoothly.
//
//   Rev 1.6   Oct 09 2002 23:53:44   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   22 May 2002 18:18:24   PURDYECH
//BFData Implementation
//
//   Rev 1.4   19 Mar 2002 13:20:14   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.3   Nov 24 2000 14:53:18   HSUCHIN
//added constant for RIP Processing
//
//   Rev 1.2   Aug 08 2000 13:44:00   YINGZ
//add VerificationStringProcessor
//
//   Rev 1.1   Aug 03 2000 14:41:52   VASILEAD
//Added tracking support to VerifConf
//
//   Rev 1.0   Jul 26 2000 09:37:34   VASILEAD
//Initial revision.
 * 
 *    Rev 1.2   Mar 24 2000 12:22:50   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.1   Feb 29 2000 15:29:42   FENGYONG
// Add CurrentDate
// 
//    Rev 1.0   Nov 24 1999 09:27:48   FENGYONG
// Initial revision.
 * 
 *
 */

