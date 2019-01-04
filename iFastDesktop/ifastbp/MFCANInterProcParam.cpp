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
//    Copyright 2000 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : MFCANInterProcParam.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/21/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MFCANInterProcParam
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "mfcaninterprocparam.hpp"

namespace MFCAN_IP_PARAM
{
   //used all over the place
   const I_CHAR * const ACCOUNT_NUM                = I_("AccountNum");
   const I_CHAR * const SHR_NUM                    = I_("ShrNum");   
   //fund and class
   const I_CHAR * const FUND_CODE                  = I_("FundCode");
   const I_CHAR * const CLASS_CODE                 = I_("ClassCode");
   const I_CHAR * const FUND_GROUP                 = I_("FundGroup");
   const I_CHAR * const FUND_NUMBER                = I_("FundNumber");
   const I_CHAR * const FUND_ISIN                  = I_("FundISIN");
   const I_CHAR * const FUND_WKN                   = I_("FundWKN");
   const I_CHAR * const FUND_LFC                   = I_("FundLFC");
   const I_CHAR * const CUSIP                      = I_("CUSIP");
   //broker, branch, salsrep
   const I_CHAR * const BROKER_CODE                = I_("BrokerCode");
   const I_CHAR * const BRANCH_CODE                = I_("BranchCode");
   const I_CHAR * const SALES_REP_CODE             = I_("SalesRepCode");
   //to pass in a caller id (since same process can be called from different places)
   const I_CHAR * const CALLER                     = I_("Caller");
   //used in bank instruction process
   const I_CHAR * const BANK_TYPE                  = I_("BankType");
   //generally used to pass in the key of a main list
   const I_CHAR * const LIST_KEY                   = I_("ListKey");
   //generally used to pass in the key of a sub-list
   const I_CHAR * const SUB_LIST_KEY               = I_("SubListKey");
   //generally used to pass in the key of the selection in a list
   const I_CHAR * const SELECTION_KEY              = I_("SelectionKey");
   //for historical search dialog
   const I_CHAR * const TABLEID                    = I_("TableId");
   const I_CHAR * const RECID                      = I_("RecId");
   const I_CHAR * const KEYS                       = I_("Keys");
   //for (broker) search dialog
   const I_CHAR * const SEARCH_TYPE                = I_("SearchType");
   const I_CHAR * const SEARCH_CRITERIA            = I_("SearchCriteria");
   const I_CHAR * const SEARCH_USING               = I_("SearchUsing");
   const I_CHAR * const BACKGROUND_SEARCH          = I_("BackgroundSearch");
    //for trade
   const I_CHAR * const TRANS_TYPE                 = I_("TransType");
   const I_CHAR * const TRANS_NUM                  = I_("TransNum");
   const I_CHAR * const TRADE_DATE                 = I_("TradeDate");

   const I_CHAR * const TRADE_BANK_SELECTION       = I_("TradeBankSelection");
   const I_CHAR * const TRADE                      = I_("Trade");
   const I_CHAR * const TRANS_ID                   = I_("TransId");
   const I_CHAR * const PENDING_RID                = I_("PendingRid");
   const I_CHAR * const TRANS_PENDING              = I_("TransPending");
   const I_CHAR * const DISABLE_REMARKS            = I_("DisableRemarks");
   const I_CHAR * const ID_VALUE                   = I_("IdValue");

   const I_CHAR * const PAC_SWP_ID                 = I_("PACSWPId");
   const I_CHAR * const PAYENTITY_ID               = I_("PayEntityId");
   const I_CHAR * const PAYINSTRUCT_ID             = I_("PayInstructId");

   const I_CHAR * const EFFECTIVE_DATE             = I_("EffectiveDate");
   const I_CHAR * const ADDRESS_CODE               = I_("AddressCode");
   const I_CHAR * const ENTITY_ID                  = I_("EntityId");
   const I_CHAR * const ENTITY_TYPE                = I_("EntityType");
   const I_CHAR * const SEQNUMBER                  = I_("SeqNumber");
   const I_CHAR * const ADDRESS_ID                 = I_("AddressId");
   const I_CHAR * const ENTITY_CODE                = I_("EntityCode");
   const I_CHAR * const ACCT_USE_CODE              = I_("AcctUseCode");
   const I_CHAR * const CURRENCY                   = I_("Currency");
   const I_CHAR * const DOCUMENT_TYPE              = I_("DocumentType");
   const I_CHAR * const DELIVERY_OPTION            = I_("DeliveryOption");
   const I_CHAR * const FROM_REMARKS               = I_("FromRemarks");
   const I_CHAR * const FEE_MODEL_CODE             = I_("FeeModelCode");
   const I_CHAR * const FUNDSPONSOR                = I_("FundSponsor");
   const I_CHAR * const AGGREGATEDORDER            = I_("AggregatedOrders");
   const I_CHAR * const REGAGENT					      = I_("RegAgent");

   const I_CHAR * const ACTIVITY_ID                = I_("ActivityID");
   const I_CHAR * const SENDER_REF_NUM             = I_("SenderRefNum");
   const I_CHAR * const NETWORK_ID                 = I_("NetworkID");
   const I_CHAR * const START_DATE                 = I_("StartDate");
   const I_CHAR * const END_DATE                   = I_("EndDate");
   const I_CHAR * const PROCESS_TYPE               = I_("ProcessType");
   const I_CHAR * const PROCESS_CATEGORY           = I_("ProcessCategory");
   const I_CHAR * const PROCESS_STATUS             = I_("ProcessStatus");
   const I_CHAR * const ENVELOPE_ID                = I_("EnvelopeID");

    //  for EntityAddressSearch
    //const I_CHAR * const SEARCH_TYPE              = I_("SearchType");
   const I_CHAR * const ADDRSS_ID                  = I_("AddrId");
   const I_CHAR * const ADDRESS_LINE1              = I_("AddrLine1");
   const I_CHAR * const ADDRESS_LINE2              = I_("AddrLine2");
   const I_CHAR * const ADDRESS_LINE3              = I_("AddrLine3");
   const I_CHAR * const CITY                       = I_("City");
   const I_CHAR * const PROVICE                    = I_("Province");
   const I_CHAR * const COUNTRY                    = I_("Country");
   const I_CHAR * const POST_CODE                  = I_("PostalCode");
   const I_CHAR * const MATURITY_DATE              = I_("MaturityDate");
   const I_CHAR * const SEG_TRANS_EXIST            = I_("SegTransExist");
   const I_CHAR * const CONTRACT_TYPE              = I_("ContractType");
   const I_CHAR * const EXTERNAL_TRANS_NUM         = I_("ExtTransNum");
   const I_CHAR * const MOD_PERM                   = I_("ModPerm");
   const I_CHAR * const SEARCH_TYPE_MGMT           = I_("SearchTypeMgmt");
   const I_CHAR * const SPONSOR_GROUP              = I_("SponsorGroup");
   const I_CHAR * const SPONSORDESC                = I_("SponsorDesc");
   const I_CHAR * const RULE_TYPE                  = I_("RuleType");
   const I_CHAR * const DISTRIB_LEVEL              = I_("DistributionLevel");
   const I_CHAR * const DISTRIB_LEVEL_PARAM        = I_("DistribLevelParam");
   const I_CHAR * const DIRCT_DEPST_APPLIC         = I_("DirectDepositApplicable");
   const I_CHAR * const DISTRIB_GBCD               = I_("DistribGBCD");
   const I_CHAR * const VERIFY_STAT                = I_("VerifyStat");

   const I_CHAR * const MAT_INSTR_TYPE             = I_("MatInstrType");
   const I_CHAR * const MAT_INSTR_LEVEL            = I_("MatInstrLevel");
   const I_CHAR * const MAT_INSTR_KEY              = I_("MatInstrKey");
   const I_CHAR * const MAT_INSTR_DETL_KEY         = I_("MatInstrDetlKey");
   const I_CHAR * const INVEST_ID                  = I_("InvHisInvestId" );
   const I_CHAR * const RESET                      = I_("Reset" );
   const I_CHAR * const INV_PRINCIPAL				   = I_( "PrincipalAmount" );
   const I_CHAR * const INV_ACCRUED		            = I_( "AccruedAmount " );
   const I_CHAR * const CON_MAT_INSTR_KEY			   = I_("ConMatInstrKey");
   const I_CHAR * const CON_MAT_INSTR_COTACCTRID	= I_("ConAcctRID");
   const I_CHAR * const CON_MAT_INSTR_TYPE			= I_("ConMatType");
   const I_CHAR * const CON_MAT_INSTR_TYPEID		   = I_("ConMatTypeID");


   const I_CHAR * const FEE_TYPE		               = I_("FeeType");
   const I_CHAR * const HOLDING_COMP_CODE          = I_("HoldingCompCode");
   const I_CHAR * const HOLDING_COMP_NAME          = I_("HoldingCompName");
} 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MFCANInterProcParam.cpp-arc  $
 * 
 *    Rev 1.54   Apr 04 2012 11:29:54   wp040039
 * PETP0187485-Registration Agent  Banking
 * 
 *    Rev 1.53   Mar 02 2012 16:39:48   wp040100
 * P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
 * 
 *    Rev 1.52   Mar 02 2012 15:01:40   jankovii
 * IN 2859411 - P0186477_FN02_Interest Instruction-Err displayed on split type 'Amount' instrctn
 * 
 *    Rev 1.51   Feb 21 2012 16:58:10   if991250
 * Added Reset
 * 
 *    Rev 1.50   Feb 21 2012 13:10:18   if991250
 * Trade Mat Sweep Instr Banks
 * 
 *    Rev 1.49   Feb 02 2012 15:07:12   if991250
 * Maturity/Interest Instructions banking
 * 
 *    Rev 1.48   Jan 31 2012 14:54:00   if991250
 * Added params for Maturity Instructions
 * 
 *    Rev 1.47   Jan 13 2010 09:10:20   dchatcha
 * IN# 1971377 - R97_Static Data_File Processor&Bank are blank after deleting distribution option.
 * 
 *    Rev 1.46   Jul 09 2009 14:20:06   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.45   Jan 07 2009 06:58:50   daechach
 * PETP0155543 FN01 - Account Level Distribution Instructions.
 * 
 *    Rev 1.44   Mar 11 2008 19:26:40   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.43   Nov 02 2006 11:44:00   ZHANGCEL
 * PET2217 FN26 - Add a new parameter for Bank Instruction title display
 * 
 *    Rev 1.42   Nov 01 2006 11:17:56   ZHANGCEL
 * PET2217 FN26 -- Add a new paramer to pop up FundSponsor list with <F4>
 * 
 *    Rev 1.41   Jul 27 2006 17:55:12   ZHANGCEL
 * PET2192 FN11 -- Add a new Parameter for SearchTypeMgmt
 * 
 *    Rev 1.40   Feb 14 2006 14:08:50   zhengcon
 * Incident #528284 - add one field ModPerm for updatable permission of User Defined Maturity Date of converted account
 * 
 *    Rev 1.39   Apr 21 2005 11:13:02   hernando
 * Incident #278666 - Added External Trans Num.
 * 
 *    Rev 1.38   Apr 13 2005 15:19:10   hernando
 * PET1024 FN02 - Added Contract Type.
 * 
 *    Rev 1.37   Mar 21 2005 11:34:42   hernando
 * PET1024 FN02 - Added SEG_TRANS_EXIST.
 * 
 *    Rev 1.36   Mar 20 2005 19:39:42   hernando
 * PET1024 FN02 - Added MATURITY_DATE.
 * 
 *    Rev 1.35   Mar 08 2005 13:52:42   ZHANGCEL
 * PET1171 FN01 -- Added parameter for EntityAddressSearch issue
 * 
 *    Rev 1.34   Feb 16 2005 11:25:52   hernando
 * PET1117 FN66-68 - Added additional parameters to support Messages.
 * 
 *    Rev 1.33   Nov 26 2004 14:45:52   zhangcel
 * PET1117/FN8 -- Aggregated Order related changes
 * 
 *    Rev 1.32   Oct 27 2004 12:04:54   popescu
 * PET 1117/06, Trade processing, 
 * 
 *    Rev 1.31   Aug 10 2004 11:13:38   FENGYONG
 * PET117 FN5 - Client Condition Fee
 * 
 *    Rev 1.30   May 27 2004 17:19:40   HERNANDO
 * PET1017 FN01- Remarks-Confirmation change.   Allow Confirmation to view the Added Remark and allow copying it to the AWD object.
 * 
 *    Rev 1.29   Mar 02 2004 16:18:24   HERNANDO
 * PET965 FN11 - Added DELIVERY_OPTION, DOCUMENT_TYPE.
 * 
 *    Rev 1.28   Feb 22 2004 13:58:34   HERNANDO
 * PET965 FN11 - Added EFFECTIVE_DATE, ADDRESS_CODE, ENTITY_ID, ENTITY_TYPE, SEQNUMBER, ADDRESS_ID, ENTITY_CODE, ACCT_USE_CODE, and CURRENCY.
 * 
 *    Rev 1.27   Sep 01 2003 21:21:10   popescu
 * PET 809 FN 02, CIBC Multi fund enhancement
 * 
 *    Rev 1.26   Aug 18 2003 16:04:20   HERNANDO
 * Added PAYENTITY_ID and PAYINSTRUCT_ID.
 * 
 *    Rev 1.25   Aug 14 2003 15:43:52   popescu
 * Added new process ids for multi-fund gui and bp layer. Changed the id of the allocation process and dialog from *_ALLOCATIONS to *SIMPLE_ALLOCATION; introduced a new process(AllocationSplitProcess) with the Id *_ALLOCATIONS only at the bp level, that will decide which allocation screen should be invoked
 * 
 *    Rev 1.24   Aug 07 2003 18:35:46   popescu
 * added new param that will help set the UI selection on the desired bank
 * 
 *    Rev 1.23   Jul 09 2003 21:56:28   popescu
 * Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
 * 
 *    Rev 1.22   Jun 30 2003 16:56:26   popescu
 * added historical info search to the Broker Features search;
 * moved some param names to the mfcaniterprocparam namespace
 * 
 *    Rev 1.21   Jun 27 2003 18:12:52   popescu
 * Pay To Entity feature, dialog, process and CBO
 * 
 *    Rev 1.20   Jun 01 2003 17:07:32   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.19   May 31 2003 11:54:36   popescu
 * RRIF bank work
 * 
 *    Rev 1.18   May 26 2003 11:28:34   popescu
 * Parameters clean-up
 * 
 *    Rev 1.17   May 23 2003 10:04:06   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.16   Oct 09 2002 23:53:28   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Jun 18 2002 15:45:42   HSUCHIN
 * added shareholder num
 * 
 *    Rev 1.14   Jun 08 2002 13:12:24   HSUCHIN
 * added settlement options
 * 
 *    Rev 1.13   24 May 2002 15:21:00   KOVACSRO
 * Fund and Client bank.
 * 
 *    Rev 1.12   22 May 2002 18:24:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   Sep 25 2001 10:40:56   YINGBAOL
 * add RIF bank Type
 * 
 *    Rev 1.10   20 Jun 2001 16:44:48   YINGZ
 * add saving plan
 * 
 *    Rev 1.9   12 Apr 2001 15:27:40   BUZILAMI
 * Trading Bank Changes
 * 
 *    Rev 1.8   Apr 09 2001 15:13:38   YINGBAOL
 * add tradedate
 * 
 *    Rev 1.7   30 Mar 2001 17:09:24   BUZILAMI
 * Systematic bank changes
 * 
 *    Rev 1.6   07 Mar 2001 15:41:58   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 * 
 *    Rev 1.5   Feb 21 2001 10:39:28   BUZILAMI
 * Bank Acct changes
 * 
 *    Rev 1.4   15 Dec 2000 12:43:44   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.3   Apr 28 2000 18:20:04   BUZILA
 * M3
 * 
 *    Rev 1.2   Apr 03 2000 08:56:24   BUZILA
 * Trade changes
 * 
 *    Rev 1.1   Mar 24 2000 12:22:56   POPESCUS
 * Make things happen for Vision
 * 
 *    Rev 1.0   Mar 22 2000 13:06:56   BUZILA
 * Initial revision.
 *
 */
