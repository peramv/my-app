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
//    Copyright 2000 by DST Systems, Inc.
//    AUTHOR : Mihai Virgil Buzila
//    DATE   : 03 Feb 2000
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

//include the data sets
#include <ifastdataimpl\dse_dstc0115_req.hpp>
#include <ifastdataimpl\dse_dstc0421_vw.hpp>
#include <ifastdataimpl\dse_dstc0421_req.hpp>
#include <ifastdataimpl\dse_dstc0298_vw.hpp>
#include "mfcaninterprocparam.hpp"

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

const BFContainerId ACCOUNT (11);
const BFContainerId ACCOUNT_TO (21);
const BFContainerId SHAREHOLDER (31);
const BFContainerId SHAREHOLDER_TO (41);
const BFContainerId ADDRESS (51);
const BFContainerId ADDRESS_TO (61);
const BFContainerId ACCOUNT_CATEGORY_LIST (71);
const BFContainerId ACCOUNT_CATEGORY_LIST_TO (81);
const BFContainerId SHAREHOLDER_ADDRESS (91);
const BFContainerId BROKER (101);
const BFContainerId BRANCH (111);
const BFContainerId AGENT (121);
const BFContainerId ACCOUNT_HOLDINGS (131);
const BFContainerId ACCOUNT_HOLDINGS_TO (141);
const BFContainerId TRANS_FEE_LIST (151);
const BFContainerId PENDING_TRADES_LIST (161);
const BFContainerId PENDING_TRADE (171);
const BFContainerId AGGREGATED_ORDER (181);
const BFContainerId DILUTION_LIST (191);
const BFContainerId TRADE_PAY_INSTRUCT_LIST (201);
const BFContainerId TRADE_MULTI_SETTLEMENT_LOC_LIST (211);
const BFContainerId RESP_BENEF_ALLOC_LIST (212);
const BFContainerId RESP_TRANSFER_LIST (213);
const BFContainerId GIA_ATTRIB_LIST (214);
const BFContainerId MAT_SWEEP_INSTRUCTIONS_LIST (215);
const BFContainerId RDSP_TRANSFER (216);

//search account ids
const BFContainerId SEARCH_ALT_ACCOUNT (1001);
const BFContainerId SEARCH_ALT_ACCOUNT_FROM (1011);
const BFContainerId SEARCH_ALT_ACCOUNT_TO (1021);
const BFContainerId SEARCH_X_REF_NUM (1031);
const BFContainerId SEARCH_X_REF_NUM_FROM (1041);
const BFContainerId SEARCH_X_REF_NUM_TO (1051);

const BFFieldId IsAccountSetAndValid (10001, I_("IsAccountSetAndValid"));
const BFFieldId IsBankingNeeded (10011, I_("IsBankingNeeded"));
const BFFieldId IsShareholderAddressNeeded (10021, I_("IsShareholderAddressNeeded"));
const BFFieldId ShouldAskForRep (10031, I_("ShouldAskForRep"));
const BFFieldId IsCancelHitOnVerifySearch (10041, I_("IsCancelHitOnVerifySearch"));
const BFFieldId AreAllocationsAllowed (10051, I_("AreAllocationsAllowed"));
const BFFieldId IsSplitCommissionAllowed (10061, I_("IsSplitCommissionAllowed"));
const BFFieldId AreTaxRatesAllowed (10071, I_("AreTaxRatesAllowed"));
const BFFieldId IsChargeFee (10081, I_("IsChargeFee"));
const BFFieldId IsSettleLocAllowed (10091, I_("IsSettleLocAllowed"));
const BFFieldId IsClearingAccount (10101, I_("IsClearingAccount"));
const BFFieldId Reset (10111, I_("Reset"));
const BFFieldId IsDilutionAllowed (10112, I_("IsDilutionAllowed"));
const BFFieldId IsRebook (10113, I_("IsRebook"));
const BFFieldId IsEUSDApplicable (10114, I_("IsEUSDApplicable"));
const BFFieldId IsFundInScope (10115, I_("FundIsInScope"));
const BFFieldId IsFundLookedThru (10116, I_("FundIsLookedThru"));
const BFFieldId ArePayInstructAllowed (10117, I_("AreSplitPaymentsAllowed"));
const BFFieldId IsAccountCloningAllowed (10118, I_("IsAccountCloningAllowed"));
const BFFieldId ClonedAcountNum (10119, I_("ClonedAcountNum"));
const BFFieldId AmountDecimalDigit(10120, I_("AmountDecimalDegit"));
const BFFieldId AreMultipleSettleLocAllowed (10121, I_("AreMultipleSettleLocAllowed"));
const BFFieldId AreRESPBenefAllocationsAllowed (10122, I_("AreRESPBenefAllocationsAllowed"));
const BFFieldId RefreshRESPBenefAllocation (10123, I_("RefreshRESPBenefAllocation"));
const BFFieldId IsRESPTransferAllowed (10124, I_("IsRESPTransferAllowed"));
const BFFieldId IsPSEEAPAllowed (10125, I_("IsPSEEAPAllowed"));
const BFFieldId RefreshRESPTransfers (10126, I_("RefreshRESPTransfers"));
const BFFieldId IsAssociationToOriginalContribAllowed (10127, I_("IsAssociationToOriginalContribAllowed"));
const BFFieldId AcqFeeType (10128, I_("AcqFeeType"));
const BFFieldId IsGIAAttribAllowed (10129, I_("IsGIAAttribAllowed"));
const BFFieldId IsMaturityInstrAllowed (10130, I_("isMaturityInstrAllowed"));
const BFFieldId IsGIInvestmentListApplicable(10131, I_("IsGIInvestmentListApplicable"));
const BFFieldId IsEstateAllocationListApplicable(10132, I_("IsEstateAllocationListApplicable"));
const BFFieldId isCASHSettleESGElig(10133, I_("isCASHSettleESGElig"));
const BFFieldId isG1G2Applicable(10134, I_("isG1G2Applicable"));
const BFFieldId IsRefund (10135, I_("IsRefund"));
const BFFieldId IsRDSPTransferAllowed (10136, I_("IsRDSPTransferAllowed"));
const BFFieldId RefreshRDSPTransfers (10137, I_("RefreshRDSPTransfers"));


namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const HYBRID_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const INSPECIES_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const HYBRID_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const INSPECIES_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const REFUND_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const REFUND_REDEMPTION_INDC;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const ONE_SIDE_TRADE;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE;
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE;
   extern CLASS_IMPORT I_CHAR * const DIVIDEND;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
   extern CLASS_IMPORT I_CHAR * const INSP_NON_PRO_RATA_PURCHASE;  
   extern CLASS_IMPORT I_CHAR * const INSP_NON_PRO_RATA_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const POST_ADJUSTMENT_LIST;
   extern CLASS_IMPORT I_CHAR * const CROSS_SYSTEM_TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const CROSS_SYSTEM_TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE_2;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const SYSTEM_CHEQUE;
   extern CLASS_IMPORT I_CHAR * const EFT;
} 

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const TRADE;
}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TRADES_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACCT_ALLOCATION;
   extern IFASTBP_LINKAGE const BFContainerId FUND_ALLOCATION;
   extern IFASTBP_LINKAGE const BFContainerId SPLIT_COMMISSION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId GI_INVESTMENT_DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ESTATE_ALLOCATION;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER; 
}

namespace ifds
{
//list view controls headings
   extern CLASS_IMPORT const BFTextFieldId TradingHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId Trading_AllocationHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId SplitCommissionDetailsHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId DilutionHeadSet;
   extern CLASS_IMPORT const BFTextFieldId TradePayInstructHeadSet;
   extern CLASS_IMPORT const BFTextFieldId TradeSettleLocationsListHeading;
   extern CLASS_IMPORT const BFTextFieldId RESPBenefAllocHeading;
   extern CLASS_IMPORT const BFTextFieldId RESPTransferHeading;
//grid sets
   extern CLASS_IMPORT const BFTextFieldId TradeAttributesHeading;
   extern CLASS_IMPORT const BFTextFieldId TradeAttributesFields;
   extern CLASS_IMPORT const BFTextFieldId TradeFeesHeading;
   extern CLASS_IMPORT const BFTextFieldId TradeFeesFields;
//fields sets
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonCommon;
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonQESI;
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonRDSP;
//fields   
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
//fund number related fields
   extern CLASS_IMPORT const BFTextFieldId Baycom;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FromCurrency;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
   extern CLASS_IMPORT const BFTextFieldId FundToISIN;
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundToWKN;
   extern CLASS_IMPORT const BFTextFieldId FundLFC;
   extern CLASS_IMPORT const BFTextFieldId FundToLFC;
   extern CLASS_IMPORT const BFTextFieldId FundCurrency;
//broker/branch/sales rep related fields
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
//remarks fields
   extern CLASS_IMPORT const BFTextFieldId Remarks;
   extern CLASS_IMPORT const BFTextFieldId RemarksLine;
//address related fields
   extern CLASS_IMPORT const BFTextFieldId TradeAddress;
   extern CLASS_IMPORT const BFTextFieldId Name;
	extern CLASS_IMPORT const BFTextFieldId Name1;
	extern CLASS_IMPORT const BFTextFieldId Name2;
   extern CLASS_IMPORT const BFTextFieldId AddrLine1;
   extern CLASS_IMPORT const BFTextFieldId AddrLine2;
   extern CLASS_IMPORT const BFTextFieldId AddrLine3;
   extern CLASS_IMPORT const BFTextFieldId AddrLine4;
   extern CLASS_IMPORT const BFTextFieldId AddrLine5;
   extern CLASS_IMPORT const BFTextFieldId PostalCode;
   extern CLASS_IMPORT const BFTextFieldId CountryCode;
//account caution related fields
   extern CLASS_IMPORT const BFNumericFieldId rxAcctNum;
   extern CLASS_IMPORT const BFTextFieldId PendingTrade;
   extern CLASS_IMPORT const BFTextFieldId Remarks;
   extern CLASS_IMPORT const BFTextFieldId Certificates;
   extern CLASS_IMPORT const BFTextFieldId StopPurchase;
   extern CLASS_IMPORT const BFTextFieldId StopRed;
   extern CLASS_IMPORT const BFTextFieldId StopRedSettle;
   extern CLASS_IMPORT const BFTextFieldId StopXferOut;
   extern CLASS_IMPORT const BFTextFieldId StopXferIn;
   extern CLASS_IMPORT const BFTextFieldId UnsettledTrn;
   extern CLASS_IMPORT const BFTextFieldId HighestEntityRisk;
   extern CLASS_IMPORT const BFTextFieldId DTAType;
   extern CLASS_IMPORT const BFTextFieldId AcctCategory;   
   extern CLASS_IMPORT const BFTextFieldId ExistAssignee;
   extern CLASS_IMPORT const BFTextFieldId ApplyPST;
   extern CLASS_IMPORT const BFTextFieldId GSTExempt;
//shareholder number field
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
//account search fields
   extern CLASS_IMPORT const BFTextFieldId AltAccount;
   extern CLASS_IMPORT const BFTextFieldId XrefNum;
//account balance fields
   extern CLASS_IMPORT const BFDecimalFieldId AccountBalance;
   extern CLASS_IMPORT const BFDecimalFieldId SettledUnits;
   extern CLASS_IMPORT const BFDecimalFieldId SettledValue;
//display only fields in trade's attribute's grid
   extern CLASS_IMPORT const BFTextFieldId InitPurch;
   extern CLASS_IMPORT const BFTextFieldId CreateRep;
//allocations fields
   extern CLASS_IMPORT const BFDecimalFieldId AllocAmount;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
//split commission fields
   extern CLASS_IMPORT const BFTextFieldId CommEntTypeDesc;
   extern CLASS_IMPORT const BFTextFieldId CommEntName;
   extern CLASS_IMPORT const BFDecimalFieldId CommPrcnt;
   extern CLASS_IMPORT const BFDecimalFieldId CommAmount;
   extern CLASS_IMPORT const BFDecimalFieldId CommRate;
//fees fields
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
   extern CLASS_IMPORT const BFTextFieldId TrxnFee;
//purchase total
   extern CLASS_IMPORT const BFDecimalFieldId PurchaseTotal;
//mod perm
   extern CLASS_IMPORT const BFTextFieldId TransModPerm;
//API fields
   extern CLASS_IMPORT const BFTextFieldId ParticipantID;
   extern CLASS_IMPORT const BFTextFieldId FundIDType;
   extern CLASS_IMPORT const BFTextFieldId FundIDValue;
   extern CLASS_IMPORT const BFTextFieldId FieldAssignment;
//mgtm co options
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
//dilution allocation list fields
	extern CLASS_IMPORT const BFDecimalFieldId AllocPercent;
	extern CLASS_IMPORT const BFTextFieldId BackDatedReason;
	extern CLASS_IMPORT const BFDateFieldId RespDate;
	extern CLASS_IMPORT const BFTextFieldId Accountable;
	extern CLASS_IMPORT const BFTextFieldId ESGSettle;
//value date
   extern CLASS_IMPORT const BFTextFieldId ValueDateOverriden;
//amount field
   extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
//resp transfer fields
   extern CLASS_IMPORT const BFDateFieldId BenefEffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId Relation;
   extern CLASS_IMPORT const BFTextFieldId GrantRequest;
   extern CLASS_IMPORT const BFDateFieldId TaintEndDate;

//GI Investment
   extern CLASS_IMPORT const BFTextFieldId GIInvestmentDetailsHeading;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId CUSIP;
   extern CLASS_IMPORT const BFTextFieldId ToValoren;
   extern CLASS_IMPORT const BFTextFieldId ToTDCC;
   extern CLASS_IMPORT const BFTextFieldId ToCUSIP;
   extern CLASS_IMPORT const BFTextFieldId SourceOfTrade;
   extern CLASS_IMPORT const BFTextFieldId ChannelOfTrade;
   extern CLASS_IMPORT const BFTextFieldId Platform;
   extern CLASS_IMPORT const BFNumericFieldId CrossSysAcctNum;
   extern CLASS_IMPORT const BFDecimalFieldId Grp1Shares;
   extern CLASS_IMPORT const BFDecimalFieldId Grp2Shares;
   extern CLASS_IMPORT const BFTextFieldId    AggregationType;
   extern CLASS_IMPORT const BFTextFieldId    SourceofFundsChecked;
}

namespace MFCAN_IP_PARAM
{
   //account number
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   //shareholder number
   extern IFASTBP_LINKAGE const I_CHAR * const SHR_NUM;
//fund params
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const CLASS_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_ISIN;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_WKN;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_LFC;
   extern IFASTBP_LINKAGE const I_CHAR * const CUSIP;
}

namespace FEES
{
   extern CLASS_IMPORT const I_CHAR * ACQUISITION;
   extern CLASS_IMPORT const I_CHAR * EXCHANGE;
   extern CLASS_IMPORT const I_CHAR * REDEMPTION;
   extern CLASS_IMPORT const I_CHAR * XFER_OUT;
   extern CLASS_IMPORT const I_CHAR * REDEMPTION_TRXN;
   extern CLASS_IMPORT const I_CHAR * PURCHASE_TRXN;
   extern CLASS_IMPORT const I_CHAR * PURCHASE_SPREAD_FEE;
   extern CLASS_IMPORT const I_CHAR * REDEMPTION_SPREAD_FEE;
   extern CLASS_IMPORT const I_CHAR * REDEMPTION_LIQUIDITY_FEE;
}

namespace RRIF_LIF_LRIF
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const LAST_NAME_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const FIRST_NAME_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const RRIF_LIF_LRIF;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradesProcessIncludes.h-arc  $
 * 
 *    Rev 1.92   Jul 27 2012 08:16:36   wp040132
 * P0199891 _FN01_Arrow_FAST_File
 * 
 *    Rev 1.91   25 Jul 2012 17:47:12   if991250
 * P0186484 : Estate Allocation
 * 
 *    Rev 1.90   Apr 11 2012 11:05:58   dchatcha
 * IN# 2901157 - Issue on SEG Trade Processing, revise allocation related logics.
 * 
 *    Rev 1.89   Mar 29 2012 23:16:16   dchatcha
 * IN#2901157 - Issues on SEG Trade Processing
 * 
 *    Rev 1.88   Mar 08 2012 09:57:18   if991250
 * GI Money Out
 * 
 *    Rev 1.87   Jan 06 2012 13:38:28   if991250
 * IA money out
 * 
 *    Rev 1.86   Nov 01 2011 15:35:48   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.85   Oct 27 2011 17:24:04   popescu
 * GIA Trading prep-work
 * 
 *    Rev 1.84   Oct 18 2011 00:44:52   popescu
 * GIA Trading prep-work
 * 
 *    Rev 1.83   Mar 03 2011 16:07:18   jankovii
 * PET181943 FN01 - XMLPhase 2
 * 
 *    Rev 1.82   Jun 11 2010 06:14:48   kitticha
 * PETP0165541 FN02 IN#2123752 - PSE Fix. Remove previous rev fields.
 * 
 *    Rev 1.81   Jun 04 2010 03:28:28   kitticha
 * IN#2123752 - Additional logic and validation for PSE.
 * 
 *    Rev 1.80   May 06 2010 23:35:04   popescu
 * RESP/QESI fixes
 * 
 *    Rev 1.79   Apr 21 2010 01:20:38   popescu
 * RESP-QESI Resp transfer screen
 * 
 *    Rev 1.78   Apr 20 2010 10:08:02   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading PSE/EAP
 * 
 *    Rev 1.77   Apr 20 2010 09:41:56   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.76   Apr 14 2010 23:56:32   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.75   Apr 14 2010 09:51:50   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.74   Mar 23 2010 10:06:42   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.73   Mar 08 2010 13:11:56   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
 * 
 *    Rev 1.72   Dec 02 2009 14:56:34   popescu
 * Prepare the terrain for incident 1780456, which will go in release 98 
 * 
 *    Rev 1.71   Aug 11 2009 13:46:18   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 *  
 *    Rev 1.70   27 Jul 2009 15:13:32   popescu
 * Project Eiger - P0147738 FN36 - Adding a field to figure out when the multiple settle locations should show up
 *
 *    Rev 1.69   Mar 18 2009 03:49:14   wutipong
 * IN#1358908 - AIG unit rounding issue -- more fix
 * 
 *    Rev 1.68   Sep 06 2007 17:19:06   popescu
 * GAP 18 - added manual management fee rebate to manual dividend screen
 * 
 *    Rev 1.67   Nov 10 2006 18:07:40   popescu
 * PET 2281/FN 01
 * 
 *    Rev 1.66   Nov 08 2006 16:49:20   popescu
 * PET 2281/FN 01 - Copy account functionality -TA
 * 
 *    Rev 1.65   Sep 07 2006 21:37:52   popescu
 * STP 2192/02
 * 
 *    Rev 1.64   Aug 29 2006 18:22:04   popescu
 * STP PET 2192 FN10/11 - bulking netting redemption
 * 
 *    Rev 1.62   Feb 20 2006 13:04:46   ZHANGCEL
 * PET 1334 - FN1 -- Added new function for the ESG Settlement enhancement
 * 
 *    Rev 1.61   Feb 07 2006 11:29:46   AGUILAAM
 * IN 534395 - fixed rebook for management fee (AF91) where multiple trades are linked to one transnum; match exact trade with fund/class.
 * 
 *    Rev 1.60   Nov 29 2005 15:23:28   AGUILAAM
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.59   Nov 10 2005 11:03:10   popescu
 * Incident# 450556 - if rebook and AWD enabled ExtTransNum has to be updated
 * 
 *    Rev 1.58   Jul 07 2005 12:17:34   AGUILAAM
 * PET1235 : dilution, part of Rebook/Cancellation
 * 
 *    Rev 1.57   Jun 13 2005 18:44:58   popescu
 * Incident # 317213 - fixed trade entry crash  for allocated orders with composed of funds with and/or without split commissions.
 * 
 *    Rev 1.56   May 30 2005 23:16:06   popescu
 * Incident # 301110 - reversed the old fix; updated the effective date on the trade entry screen for new trades only if user changes the default value of it. Otherwise is up to view 127 to determine the correct date.
 * 
 *    Rev 1.55   May 27 2005 10:47:14   popescu
 * Incident # 319459 - added DIVIDEND to the trade type namespace
 * 
 *    Rev 1.54   Mar 31 2005 12:14:04   popescu
 * Incident# 260162, used Name1 and Name2 to build the correct  name for address 02, ... 
 * 
 *    Rev 1.53   Feb 18 2005 16:57:54   popescu
 * Incident #237786, fixed refresh data flickering issue, synch-up from Release 59.0.4
 * 
 *    Rev 1.52   Feb 01 2005 11:45:00   popescu
 * PET 1117/66/67/68, API validations for SWIFT/Investro/Pwld
 * 
 *    Rev 1.51   Jan 29 2005 19:27:48   popescu
 * PET 1117. 66. added fields API
 * 
 *    Rev 1.50   Jan 23 2005 13:56:18   popescu
 * PTS 10037346, made exchange available for the user
 * 
 *    Rev 1.49   Jan 21 2005 15:30:18   popescu
 * PET 1117/06, API pending trade mods
 * 
 *    Rev 1.48   Jan 13 2005 17:36:40   popescu
 * PET 1117/06, API further changes
 * 
 *    Rev 1.47   Dec 08 2004 17:49:56   popescu
 * PET 1117/56, modify an aggregated order's pending trades list
 * 
 *    Rev 1.46   Dec 07 2004 02:45:06   popescu
 * PET 1117/56, verify search won't pop-up if alt acct/other ref # search returns one match
 * 
 *    Rev 1.45   Dec 07 2004 01:37:20   popescu
 * PET 1117/56 trades processing/modify trade
 * 
 *    Rev 1.44   Nov 30 2004 07:53:32   popescu
 * PET 1117/06, made purchase total and OnBtnHistory active once again
 * 
 *    Rev 1.43   Nov 24 2004 21:35:20   popescu
 * PET 1117/06/56. trade processing, settle location
 * 
 *    Rev 1.42   Nov 22 2004 13:08:48   popescu
 * PET 1117/56. fees processing
 * 
 *    Rev 1.41   Nov 17 2004 15:19:04   popescu
 * PET 1117/56, removed 'getField' method at the fund master list level, 
 * 
 *    Rev 1.40   Nov 07 2004 14:06:28   popescu
 * PET 1117/06, synch changes
//
//   Rev 1.3   Nov 04 2004 17:36:58   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.2   Oct 01 2004 19:25:34   popescu
//PET 1117/06, SSB Germany Trade processing
//
//   Rev 1.1   Sep 23 2004 16:00:56   popescu
//PET 1117/06 - Trade processing work in progress...
//
//   Rev 1.0   Aug 13 2004 18:56:04   popescu
//Initial revision.
 * 
// 
*/

