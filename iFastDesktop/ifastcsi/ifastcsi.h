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
//    Copyright 2000 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : ifastcsi.h
// ^AUTHOR : 
// ^DATE   : 
// ^CLASS    : ifastcsi
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : interface for the DstcCsi class.
//
//******************************************************************************


#if !defined(_DSTCCSI_H__INCLUDED_)
   #define _DSTCCSI_H__INCLUDED_

   #include <ifastcsi\CsiException.h>
   #include <ifastcsi\xplatform.h>
   #include <string>

namespace DcCsiProcesses
{
   static const char *MASTER_MENU                  = "MasterMenu";
   static const char *ACCOUNT_INFORMATION          = "AccountInformation";
   static const char *AUTOMATIC_TRANSFER_INFO      = "AutomaticTransferInfo";
   static const char *BASIC_SHARE_HOLDER           = "BasicShareholder";
   static const char *HISTORICAL_ACCOUNT_INFO      = "HistoricalAccountInfo";
   static const char *BANK_INFORMATION_MENU        = "BankInformationMenu";
   static const char *BANK_INFORMATION             = "BankInformation";
   static const char *PAC_INFORMATION              = "PACInformation";
   static const char *SWP_INFORMATION              = "SWPInformation";
   static const char *PAC_ALLOCATION               = "PACAllocation";
   static const char *SWP_ALLOCATION               = "SWPAllocation";
   static const char *ALLOCATIONS                  = "Allocations";
   static const char *TRANSACTION                  = "Transaction";
   static const char *SHAREHOLDER_REMARKS          = "ShareholderRemarks";
   static const char *DEMOGRAPHIC_INFO             = "DemographicInfo";
   static const char *TRANSACTION_PROCESSING_MENU  = "TransactionProcessingMenu";
   static const char *SETTLEMENTS                  = "Settelements";
   static const char *ORDERS_PROCESSED             = "OrdersProcessed";
   static const char *ADDRESS_INFORMATION          = "AddressInformation";
   static const char *ADDRESS_ASSIGNMENTS          = "AddressAssignments";
   static const char *ACCOUNT_ENTITY_RELATIONSHIP  = "AccountEntityRelationship";
   static const char *BRANCH_INFORMATION           = "BranchInformation";
   static const char *BROKER_INFORMATION           = "BrokerInformation";
   static const char *SALES_REP_INFORMATION        = "SalesRepInformation";
   static const char *WHERE_USED                   = "WhereUsed";
   static const char *ENTITY_MAINTAINANCE          = "EntityMaintainance";
   static const char *NEW_SHAREHOLDER              = "NewShareholder";
   static const char *FUNDVALUE_TRADE_OR_FUND      = "FundValueByTradeOrByFund"; 
   static const char *ADD_DISTRIBUTION_INFO        = "AddDistributionInfo";
   static const char *DISTRIBUTION_INFO            = "DistributionInfo";
   static const char *CERTIFICATE_INFO             = "CertificateInfo";
   static const char *DISTRIBUTION_ADD             = "DistributionAdd";
   static const char *CHOOSE_MANAGE_COMP           = "ChooseManageCompany";
   static const char *ALLOCATION_PENDING_TRADE     = "AllocationPendingTrade";
   static const char *LOCKED_IN_INFORMATION        = "LockedInformation";
   static const char *RESP_INFORMATION             = "RespInformation";
   static const char *RESP_TRANS_INFORMATION       = "RespTransInformation";
   static const char *GUARANTEE_TRANSACTION        = "GuaranteeTransaction";
   static const char *CONTRACT_INFORMATION         = "ContractInformation";
   static const char *LIF_INFO_PROCESS             = "LIFInformation";
   static const char *RRIF_INFO_PROCESS            = "RRIFInformation";
   static const char *LRIF_INFO_PROCESS            = "LRIFInformation";
   static const char *HYPO_REDEMPTION_PROCESS      = "HypoRedemptionInfo";
   static const char *LIF_ALLOCATION_PROCESS       = "LIFAllocation";
   static const char *RRIF_ALLOCATION_PROCESS      = "RRIFAllocation";
   static const char *LRIF_ALLOCATION_PROCESS      = "LRIFAllocation";
   static const char *TAX_RATE_INFORMATION         = "TaxRateInformation";
   static const char *PATCH_ORDER_ENTRY_INFO       = "PatchOrderEntryInformation";
   static const char *AMS_GLOBAL_ALLOCATION        = "AsmGlobalAllocation";
   static const char *REDEMPTION_DETAIL            = "RedemptionDetail";
	static const char *YTD_CONTRIBUTION             = "YTDContribution";
}

namespace DcCsiParameters
{
   static const char *USER_ID             = "UserId";
   static const char *PASSWORD            = "Password";
   static const char *CHANGE_PASSWORD     = "Change Password";
   static const char *ACCOUNT_NUMBER      = "AccountNumber";
   static const char *ENTITY_NAME         = "EntityName";
   static const char *BIRTH_NAME          = "BirthName";
   static const char *SIN_NUMBER          = "SinNumber";
   static const char *BANK_ACCOUNT_NUMBER = "BankAccountNumber";
   static const char *FUND                = "Fund";
   static const char *CLASS               = "Class";
   static const char *START_DATE          = "StartDate";
   static const char *STOP_DATE           = "StopDate";
   static const char *BROKER_NUMBER       = "BrokerNumber";
   static const char *BRANCH_NUMBER       = "BranchNumber";
   static const char *SALES_REP_NUMBER    = "SalesRepNumber";
   static const char *ENTITY_ID           = "EntityId";
}

class CsiSession;

class D_LINKAGE DstcCsi  
{
public:
   DstcCsi() {};
   static void RegisterProcesses();
   static void RegisterScreens();

private:
   static void D_CALLBACK MasterMenu();
   static void D_CALLBACK AccountInformation();
   static void D_CALLBACK AutomaticTransferInfo();
   static void D_CALLBACK BasicShareholder();
   static void D_CALLBACK HistoricalAccountInfo();
   static void D_CALLBACK BankInformationMenu();
   static void D_CALLBACK BankInformation();
   static void D_CALLBACK PACInformation();
   static void D_CALLBACK SWPInformation();
   static void D_CALLBACK PACAllocation();
   static void D_CALLBACK SWPAllocation();
   static void D_CALLBACK Allocations();
   static void D_CALLBACK Transaction();
   static void D_CALLBACK ShareholderRemarks();
   static void D_CALLBACK DemographicInfo();
   static void D_CALLBACK TransactionProcessingMenu();
   static void D_CALLBACK Settlements();
   static void D_CALLBACK OrdersProcessed();
   static void D_CALLBACK AddressInformation();
   static void D_CALLBACK AddressAssignments();
   static void D_CALLBACK AccountEntityRelationship();
   static void D_CALLBACK BrokerInformationMenu();
   static void D_CALLBACK BrokerInformation();
   static void D_CALLBACK BranchInformation();
   static void D_CALLBACK SalesRepInformation();
   static void D_CALLBACK WhereUsed();
   static void D_CALLBACK NewShareholder();
   static void D_CALLBACK FundValueByTradeOrByFund();
   static void D_CALLBACK EntityMaintainance();
   static void D_CALLBACK AddDistributionInfo();
   static void D_CALLBACK DistributionInfo();
   static void D_CALLBACK CertificateInfo();
   static void D_CALLBACK DistributionAdd();
   static void D_CALLBACK EntityRelationship();
   static void D_CALLBACK ChooseManageComp();
   static void D_CALLBACK LockedInformation();
   static void D_CALLBACK RespInformation();
   static void D_CALLBACK RespTransInformation();
   static void D_CALLBACK GuaranteeTransaction();
   static void D_CALLBACK ContractInformation();
   static void D_CALLBACK LIFInformation();
   static void D_CALLBACK RRIFInformation();
   static void D_CALLBACK LRIFInformation();
   static void D_CALLBACK LIFAllocation();
   static void D_CALLBACK RRIFAllocation();
   static void D_CALLBACK LRIFAllocation();
   static void D_CALLBACK HypoRedemptionInfo();
   static void D_CALLBACK PatchOrderEntryInformation();
   static void D_CALLBACK TaxRateInformation();
   static void D_CALLBACK AmsGlobalAllocation();
   static void D_CALLBACK RedemptionDetail();
	static void D_CALLBACK YTDContribution();

   static void logon();
   static void D_CALLBACK preset();
   static void D_CALLBACK reset();
};

class DstcCsiTimeout : public CsiException
{
public:
   DstcCsiTimeout(const std::string &target)
   : _target(target){}

   virtual const std::string getMessage() {return("Timeout occurred on " + _target);}
private:
   std::string _target;
};

class DstcCsiLogonCancelled : public CsiException
{
public:
   DstcCsiLogonCancelled() {}
   virtual const std::string getMessage() {return("Logon cancelled by user");}
};

#endif // !defined(_DSTCCSI_H__INCLUDED_)

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcsi/ifastcsi.h-arc  $
 * 
 *    Rev 1.8   May 26 2004 15:19:20   VADEANUM
 * PTS 10028913 - YTD support.
 * 
 *    Rev 1.7   Oct 09 2002 23:55:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Jan 29 2002 10:57:46   JANKAREN
 * Added Redemption Detail
 * 
 *    Rev 1.5   Nov 28 2001 09:58:14   YINGBAOL
 * added AMS Global Allocation
 * 
 *    Rev 1.4   May 05 2000 10:29:02   YINGBAOL
 * add patch order information
 * 
 *    Rev 1.3   Apr 17 2000 17:13:26   YINGBAOL
 * added redemption
 * 
 *    Rev 1.2   Apr 03 2000 15:49:30   YINGBAOL
 * add RIF LIF Allocation
 * 
 *    Rev 1.1   Mar 07 2000 09:42:00   YINGBAOL
 * Change Synchronize
 * 
 * 
 *
 */