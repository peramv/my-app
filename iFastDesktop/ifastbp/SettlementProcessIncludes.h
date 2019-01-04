#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
//    Copyright 2002 by International Financial Data Services
//    AUTHOR : Yingbao Li
//    DATE   : May 24,2002
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId SETTLEMENT;
   extern IFASTBP_LINKAGE const BFContainerId SETTLEMENT_BANK_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SETTLEMENT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SETTLEMENT_TOTAL_LIST;
}
namespace SETTL_PROC
{

//CP20030319   const int SETTLEMENT_LIST = 1;
//CP20030319   const int SETTLEMENT_TOTAL_LIST = 2;
//CP20030319   const int SETTLEMENT_BANK_LIST = 3;
//CP20030319   const int SETTLEMENT = 4;
   const BFFieldId SETTLEMENT_FILTER(1000);
   const BFFieldId COPY_ADDRESS(1001);
   const BFFieldId TOTAL_COUNT(1002);
   const BFFieldId TOTAL_COUNT_SETTLE(1003);
   const BFFieldId CORRESPONDENT_INFO(1004);
   const BFFieldId ENTITY_NAME(1005);
   const BFFieldId SHR_NUM(1006);
   const BFFieldId PERMIT_INQ(1007);
   const BFFieldId PERMIT_UPDATE(1008);

}

namespace Settlement_Para
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCT_DETAIL;   
   extern IFASTBP_LINKAGE const I_CHAR * const TRANS_HISTORY;       
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_SCR;      
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_AWD;

   extern IFASTBP_LINKAGE const I_CHAR * const ALL_TRADE;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT;
   extern IFASTBP_LINKAGE const I_CHAR * const WIRE_ORDER;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCT_WIRENUMBER;

   extern IFASTBP_LINKAGE const I_CHAR * const TRADE_DATE;
   extern IFASTBP_LINKAGE const I_CHAR * const SETTLE_DATE;
   extern IFASTBP_LINKAGE const I_CHAR * const SETTLE_CURRENCY;
   extern IFASTBP_LINKAGE const I_CHAR * const BROKER;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANS_NUMBER;

   extern IFASTBP_LINKAGE const I_CHAR * const EXTERNAL_ID;

   extern IFASTBP_LINKAGE const I_CHAR * const NEXT_RECORD;
   extern IFASTBP_LINKAGE const I_CHAR * const EPA_BROKER;
   extern IFASTBP_LINKAGE const I_CHAR * const REGISTRATION_AGENT;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SettlementListHeadSet;
   extern CLASS_IMPORT const BFTextFieldId SettlementGridSet;
   extern CLASS_IMPORT const BFTextFieldId SettlementTotalHeading;
   extern CLASS_IMPORT const BFTextFieldId TradingAttributesHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId Settled;
   extern CLASS_IMPORT const BFDecimalFieldId PurchaseTotalSettle;
   extern CLASS_IMPORT const BFDecimalFieldId RedemptionTotalSettle;
   extern CLASS_IMPORT const BFDecimalFieldId NetTotalSettle;
   extern CLASS_IMPORT const BFDecimalFieldId CountTotalSettel;
   extern CLASS_IMPORT const BFTextFieldId SettleAll;
   extern CLASS_IMPORT const BFTextFieldId ShareholderAddress;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId CUSIP; 
   
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDCLASS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BROKER;



#include <ifastdataimpl\dse_dstc0200_vw.hpp>
#include <ifastdataimpl\dse_dstc0200_req.hpp>

#include <ifastdataimpl\dse_dstc0201_vw.hpp>
#include <ifastdataimpl\dse_dstc0201_req.hpp>
#include <ifastdataimpl\dse_dstc0206_req.hpp>
#include <ifastdataimpl\dse_dstc0206_vw.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>

namespace PAY_TO
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SettlementProcessIncludes.h-arc  $
//
//   Rev 1.18   Apr 27 2012 09:52:38   if991250
//CPF - Account Setup & Settlement 
//
//   Rev 1.17   Dec 09 2010 14:59:20   jankovii
//IN 2339013 - P0175778: Uptreaming QA testing
//
//   Rev 1.16   Dec 02 2010 00:02:32   dchatcha
//P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
//
//   Rev 1.15   Nov 25 2010 14:11:42   jankovii
//PET175778FN01 - Upstreaming Phase 2
//
//   Rev 1.14   Jul 05 2010 02:17:30   dchatcha
//IN# 1984105 - Settlement from Broker trade will bring out shareholder default bank.
//
//   Rev 1.13   Apr 25 2005 17:51:00   ZHANGCEL
//PET 1190 - FN06 -- Settltment by TransNum enhancement
//
//   Rev 1.12   Sep 07 2004 14:59:08   VADEANUM
//PET 1094 FN4 - Activest Bank File Interface.
//
//   Rev 1.11   Mar 21 2003 17:48:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.10   Oct 09 2002 23:53:36   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.9   Aug 29 2002 12:53:36   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.8   Aug 16 2002 13:53:36   YINGBAOL
//add permission check
//
//   Rev 1.7   Jun 21 2002 13:16:02   YINGBAOL
//support window title
//
//   Rev 1.6   Jun 16 2002 14:08:50   HSUCHIN
//added support for corresponding bank check
//
//   Rev 1.5   Jun 13 2002 15:52:16   YINGBAOL
//change view 200 and launch other screen
//
//   Rev 1.4   Jun 12 2002 17:05:42   YINGBAOL
//Add Count ID
//
//   Rev 1.3   Jun 11 2002 11:43:50   YINGBAOL
//more business rules added
//
//   Rev 1.2   Jun 06 2002 16:07:48   YINGBAOL
//save work
//
//   Rev 1.1   Jun 04 2002 10:53:04   YINGBAOL
//save work
//
//   Rev 1.0   May 30 2002 11:06:02   YINGBAOL
//Initial revision.
 * 
 *


 */

