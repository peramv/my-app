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
//
// ^FILE   : ACCOUNTDISTRIBUTIONPROCESSINCLUDES.h
// ^AUTHOR : Zijian Ying 
// ^DATE   : 04/22/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the acb dialog  CEdit
//
//******************************************************************************


#include <ifastdataimpl\dse_dstc0016_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0063_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0020_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0113_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0043_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0069_vwrepeat_record.hpp>

#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

extern IFASTBP_LINKAGE const I_CHAR *ACC_DISTRIBUTION_BUFFER;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACC_DISTRIBUTION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACC_DISTRIBUTION_SUB_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_MAILING_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ADDRESS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_DETAIL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_MASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId GROUP_FUND_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId LV_DistributionFromHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId LV_DistributionToHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId DistributionTransType;
}

//CP20030319const int ACC_DISTRIBUTION_LIST = 1;
//CP20030319const int ACC_DISTRIBUTION_SUB_LIST = 2;
//CP20030319const int MFACCOUNT_CBO = 3;
//CP20030319const int SHAREHOLDER_CBO = 4;
//CP20030319const int ACCOUNT_MAILING_LIST = 5;
//CP20030319const int ADDRESS_LIST = 6;
//CP20030319const int GROUP_FUND_LIST = 7;  
//CP20030319const int FUND_MASTER_LIST = 8;
//CP20030319const int FUND_LIST = 9;
//CP20030319const int FUND_DETAIL_LIST = 10;

const BFFieldId LIST_FILTER(200);
const BFFieldId BUTTON_DUMMY_FIELD(201);
const BFFieldId LISTKEY(300);
const BFFieldId TO_LISTKEY(301);
const BFFieldId SHAREHOLDER_NUMBER(500);
const BFFieldId PRIMARY_ACCOUNT_OWNER(600);

namespace ACCDISTRIBLIT
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR* const FUND_FROM_CODE;
   extern IFASTBP_LINKAGE const I_CHAR* const CLASS_FROM_CODE;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountDistributionProcessIncludes.h-arc  $
 * 
 *    Rev 1.6   Mar 21 2003 17:34:18   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:52:56   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   Aug 29 2002 12:51:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.3   22 May 2002 18:22:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   19 Mar 2002 13:14:44   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   Nov 01 2000 10:04:42   VASILEAD
 * Added Purchase service
 * 
 *    Rev 1.0   Feb 15 2000 10:58:54   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.11   Jan 25 2000 16:44:16   YINGZ
 * for release
 * 
 *    Rev 1.10   Jan 09 2000 16:42:10   PRAGERYA
 * Made compilable!
 * 
 *    Rev 1.9   Jan 07 2000 20:32:38   PRAGERYA
 * For Mihai
 * 
 *    Rev 1.8   Dec 30 1999 12:39:10   YINGBAOL
 * 
 *    Rev 1.7   Dec 03 1999 11:36:42   YINGBAOL
 * fix delete
 * 
 *    Rev 1.6   Nov 25 1999 12:03:10   YINGBAOL
 * check in for Me release
 * 
 *    Rev 1.5   Nov 12 1999 17:16:54   YINGBAOL
 * add fund detail list
 * 
 *    Rev 1.4   Oct 17 1999 12:08:40   POPESCUS
 * added a namespace for search
 * 
 *    Rev 1.3   Sep 23 1999 15:35:06   YINGZ
 * make it work for c1
 * 
 *    Rev 1.2   Sep 15 1999 17:00:00   YINGZ
 * add #include "ListViewHeading.hpp"
 * 
 *    Rev 1.1   Jul 08 1999 10:03:24   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

