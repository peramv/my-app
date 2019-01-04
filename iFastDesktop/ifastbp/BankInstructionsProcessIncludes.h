#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : BankInstrProcessIncludes.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 02/09/2001
//
//******************************************************************************

//bank instructions
#include <ifastdataimpl\dse_dstc0052_vw.hpp>
//for rrif
#include <ifastdataimpl\dse_dstc0067_vw.hpp>
#include <ifastcbo\bankinstructions.hpp>
#include <ifastcbo\bankinstructionslist.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace 
{
   const I_CHAR *const CLONE = I_("Clone");
}

//name of the substitute list fields
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId BANK_INSTRUCTIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RRIF_LIF_LRIF;
   extern IFASTBP_LINKAGE const BFContainerId SYSTEMATIC;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_DISTRIBUTION;
   extern IFASTBP_LINKAGE const BFContainerId SETTLEMENT;
   extern IFASTBP_LINKAGE const BFContainerId PENDING_DETAILS;
   extern IFASTBP_LINKAGE const BFContainerId TRANSACTION_DETAILS;
   extern IFASTBP_LINKAGE const BFContainerId TRADE;
   extern IFASTBP_LINKAGE const BFContainerId MAT_SWEEP_INSTRUCTION_DETL;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_COMMITMENT;
   extern IFASTBP_LINKAGE const BFContainerId CONTRACT_MATURITY_INSTRUCTIONS;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CloneBankInstructions;
   extern CLASS_IMPORT const BFTextFieldId CallerName;
   extern CLASS_IMPORT const BFTextFieldId TradesTransType;
   extern CLASS_IMPORT const BFTextFieldId PayToEntity;
   extern CLASS_IMPORT const BFTextFieldId InstAddress;
   extern CLASS_IMPORT const BFTextFieldId BankAddr;
   extern CLASS_IMPORT const BFTextFieldId BankAddrCB;
   extern CLASS_IMPORT const BFTextFieldId Status;
   extern CLASS_IMPORT const BFTextFieldId TemplateNumber;
   extern CLASS_IMPORT const BFTextFieldId PayMethod;
   extern CLASS_IMPORT const BFTextFieldId OBIInstructions;
   extern CLASS_IMPORT const BFTextFieldId InstAddressCB;
   extern CLASS_IMPORT const BFTextFieldId BankInstrType;
   extern CLASS_IMPORT const BFTextFieldId Name;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId TradesTransType;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId SalesRepCode;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId BankingInstr;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId PayReason;
   extern CLASS_IMPORT const BFTextFieldId IsRRIFAccount;
   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId FundSponsor;

   //gui fields for substitution lists
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboBroker;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboDefault;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboDefaultNoRRIF;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboBranch;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboSlsRep;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboTransaction;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboPendingTransaction;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboMaturityInterest;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboTrade;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboAdminFee;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboClient;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboFund;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboFundClass;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboSettlement;
   extern CLASS_IMPORT const BFTextFieldId BankOptionsFieldsHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId BankInstrHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId BankOptionsHeadingSet;   
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboDirectTrading;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboFundGroup;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboFundSponsor;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboTradeBroker;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboTradeBranch;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboTradeSlsrep;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboContMatInstr;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
   extern CLASS_IMPORT I_CHAR * const FUND;
   extern CLASS_IMPORT I_CHAR * const CLIENT;
   extern CLASS_IMPORT I_CHAR * const TRADE;
   extern CLASS_IMPORT I_CHAR * const PENDING_TRADE;
   extern CLASS_IMPORT I_CHAR * const PENDING;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS;
   extern CLASS_IMPORT I_CHAR * const SYSTEMATIC;
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
   extern CLASS_IMPORT I_CHAR * const TRANSACTION;
   extern CLASS_IMPORT I_CHAR * const RRIF;
   extern CLASS_IMPORT I_CHAR * const SETTLEMENT;
   extern CLASS_IMPORT I_CHAR * const DIRECT_TRADING;
   extern CLASS_IMPORT I_CHAR * const FUND_GROUP;
   extern CLASS_IMPORT I_CHAR * const FUND_SPONSOR;
   extern CLASS_IMPORT I_CHAR * const MATURITY_INSTRUCTIONS;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_COMMITMENT;
   extern CLASS_IMPORT I_CHAR * const CONTRACTMAT_INSTRUCTIONS;
   extern CLASS_IMPORT I_CHAR * const REG_AGENT;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT;
}

namespace AcctUseCode
{
   extern CLASS_IMPORT const I_CHAR * const DIRECT_TRADING;
}

namespace FI_CATEGORY
{
   extern CLASS_IMPORT I_CHAR * const BANK;
   extern CLASS_IMPORT I_CHAR * const BANK_TRANSIT;
   extern CLASS_IMPORT I_CHAR * const INSTITUTION;
   extern CLASS_IMPORT I_CHAR * const INSTITUTION_TRANSIT;
   extern CLASS_IMPORT I_CHAR * const OTHER;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
}

namespace PAY_TO
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
}

namespace BANKINGLEVEL
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER_LEVEL;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_LEVEL ;
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER_AND_ACCOUNT_LEVEL;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BankInstructionsProcessIncludes.h-arc  $
 * 
 *    Rev 1.27   Apr 04 2012 11:13:32   wp040039
 * PETP0187485-Registration Agent  Banking
 * 
 *    Rev 1.26   Mar 02 2012 16:40:32   wp040100
 * P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
 * 
 *    Rev 1.25   Feb 24 2012 18:16:24   if991250
 * ACCOUNT_COMMITMENT
 * 
 *    Rev 1.24   Feb 02 2012 15:07:02   if991250
 * Maturity/Interest Instructions banking
 * 
 *    Rev 1.23   Oct 18 2006 15:53:10   popescu
 * PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
 * 
 *    Rev 1.22   Sep 07 2006 21:37:28   popescu
 * STP 2192/02
 * 
 *    Rev 1.21   Nov 04 2004 17:36:34   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.20   Sep 21 2004 13:21:00   HERNANDO
 * PET1094 FN06 - Absatcmeldung Files enhancement.
 * 
 *    Rev 1.19   Oct 19 2003 18:35:02   popescu
 * CIBC PET 809, FN 13
 * 
 *    Rev 1.18   Oct 19 2003 16:43:20   popescu
 * CIBC, PET809, FN 13 banking work
 * 
 *    Rev 1.17   Oct 06 2003 12:42:50   popescu
 * Added banking support for DirectTrading enhancement
 * 
 *    Rev 1.16   Jul 31 2003 22:02:50   popescu
 * Fund/Class search changes....
 * 
 *    Rev 1.15   Jun 10 2003 16:10:46   popescu
 * Changed the SettlementTrade bank instructions files to match new design for bank instructions that are not on host
 * 
 *    Rev 1.14   Jun 10 2003 11:51:14   popescu
 * work for Fubd/Class banking search
 * 
 *    Rev 1.13   Jun 01 2003 17:07:30   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.12   May 31 2003 20:29:10   popescu
 * RRIF work part ||
 * 
 *    Rev 1.11   May 31 2003 11:54:34   popescu
 * RRIF bank work
 * 
 *    Rev 1.10   May 27 2003 13:13:56   popescu
 * RRIF Banking work
 * 
 *    Rev 1.9   May 22 2003 14:11:26   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
//
//   Rev 1.7   Mar 21 2003 17:36:32   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:53:04   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   22 May 2002 18:21:38   PURDYECH
//BFData Implementation
//
//   Rev 1.4   19 Mar 2002 13:15:14   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.3   20 Mar 2001 16:00:04   BUZILAMI
//address changes
//
//   Rev 1.2   07 Mar 2001 15:41:54   BUZILAMI
//Broker, Branch, SlsRep Bank Instructions changes
//
//   Rev 1.1   Feb 22 2001 15:24:36   BUZILAMI
//added search for bank using Broker, Branch and sales Rep
//
//   Rev 1.0   Feb 21 2001 16:01:20   BUZILAMI
//Initial revision.
//
 * 
 *
 */
