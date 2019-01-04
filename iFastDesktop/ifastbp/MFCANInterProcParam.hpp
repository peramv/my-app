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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : MFCANInterProcParam.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/21/2000
//
// ----------------------------------------------------------
//
// ^CLASS    : MFCANInterProcParam
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace MFCAN_IP_PARAM
{
   //account number
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   //shareholder number
   extern IFASTBP_LINKAGE const I_CHAR * const SHR_NUM;
   //broker, banch, salesrep
   extern IFASTBP_LINKAGE const I_CHAR * const BROKER_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const BRANCH_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const SALES_REP_CODE;
   //fund and class
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const CLASS_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_GROUP;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_ISIN;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_WKN;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_LFC;
   extern IFASTBP_LINKAGE const I_CHAR * const CUSIP;
   //used in processes that need to determine from where are they called
   extern IFASTBP_LINKAGE const I_CHAR * const CALLER;
   extern IFASTBP_LINKAGE const I_CHAR * const BANK_TYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const LIST_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const SUB_LIST_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const SELECTION_KEY;
   //for the historical info search dialog and process
   extern IFASTBP_LINKAGE const I_CHAR * const TABLEID;
   extern IFASTBP_LINKAGE const I_CHAR * const RECID;
   extern IFASTBP_LINKAGE const I_CHAR * const KEYS;
   //for search
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_TYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_CRITERIA;
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_USING;
   extern IFASTBP_LINKAGE const I_CHAR * const BACKGROUND_SEARCH;
   //trade
   extern IFASTBP_LINKAGE const I_CHAR * const TRANS_TYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANS_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const TRADE_DATE;


   //to be checked.....
   extern IFASTBP_LINKAGE const I_CHAR * const TRADE_BANK_SELECTION;
   extern IFASTBP_LINKAGE const I_CHAR * const TRADE;


   extern IFASTBP_LINKAGE const I_CHAR * const TRANS_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const PENDING_RID;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANS_PENDING;
   extern IFASTBP_LINKAGE const I_CHAR * const DISABLE_REMARKS;
   extern IFASTBP_LINKAGE const I_CHAR * const ID_VALUE;

   extern IFASTBP_LINKAGE const I_CHAR * const PAC_SWP_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const PAYENTITY_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const PAYINSTRUCT_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRESS_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const EFFECTIVE_DATE;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRESS_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_TYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const SEQNUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRESS_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCT_USE_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const CURRENCY;
   extern IFASTBP_LINKAGE const I_CHAR * const DOCUMENT_TYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const DELIVERY_OPTION;
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_REMARKS;
   extern IFASTBP_LINKAGE const I_CHAR * const FEE_MODEL_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDSPONSOR;
   extern IFASTBP_LINKAGE const I_CHAR * const AGGREGATEDORDER;
   extern IFASTBP_LINKAGE const I_CHAR * const REGAGENT;

   extern IFASTBP_LINKAGE const I_CHAR * const ACTIVITY_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const SENDER_REF_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const NETWORK_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const START_DATE;
   extern IFASTBP_LINKAGE const I_CHAR * const END_DATE;
   extern IFASTBP_LINKAGE const I_CHAR * const PROCESS_TYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const PROCESS_CATEGORY;
   extern IFASTBP_LINKAGE const I_CHAR * const PROCESS_STATUS;
   extern IFASTBP_LINKAGE const I_CHAR * const ENVELOPE_ID;

   // for EntityAddressSearch
   //extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_TYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRSS_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRESS_LINE1;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRESS_LINE2;
   extern IFASTBP_LINKAGE const I_CHAR * const ADDRESS_LINE3;
   extern IFASTBP_LINKAGE const I_CHAR * const CITY;
   extern IFASTBP_LINKAGE const I_CHAR * const PROVICE;
   extern IFASTBP_LINKAGE const I_CHAR * const COUNTRY;
   extern IFASTBP_LINKAGE const I_CHAR * const POST_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const MATURITY_DATE;
   extern IFASTBP_LINKAGE const I_CHAR * const SEG_TRANS_EXIST;
   extern IFASTBP_LINKAGE const I_CHAR * const CONTRACT_TYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const EXTERNAL_TRANS_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const MOD_PERM;
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_TYPE_MGMT;
   extern IFASTBP_LINKAGE const I_CHAR * const SPONSOR_GROUP;
   extern IFASTBP_LINKAGE const I_CHAR * const SPONSORDESC;

   // bank
   extern IFASTBP_LINKAGE const I_CHAR * const DISTRIB_LEVEL; 
   extern IFASTBP_LINKAGE const I_CHAR * const DISTRIB_LEVEL_PARAM;
   extern IFASTBP_LINKAGE const I_CHAR * const DIRCT_DEPST_APPLIC;
   // static dataverification for account distrib
   extern IFASTBP_LINKAGE const I_CHAR * const DISTRIB_GBCD;
   extern IFASTBP_LINKAGE const I_CHAR * const VERIFY_STAT;

   extern IFASTBP_LINKAGE const I_CHAR * const MAT_INSTR_TYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const MAT_INSTR_LEVEL;
   extern IFASTBP_LINKAGE const I_CHAR * const MAT_INSTR_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const MAT_INSTR_DETL_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const INVEST_ID;
	extern IFASTBP_LINKAGE const I_CHAR * const RESET;
	extern IFASTBP_LINKAGE const I_CHAR * const INV_PRINCIPAL;
   extern IFASTBP_LINKAGE const I_CHAR * const INV_ACCRUED;
   extern IFASTBP_LINKAGE const I_CHAR * const CON_MAT_INSTR_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const CON_MAT_INSTR_COTACCTRID;
   extern IFASTBP_LINKAGE const I_CHAR * const CON_MAT_INSTR_TYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const CON_MAT_INSTR_TYPEID;
   extern IFASTBP_LINKAGE const I_CHAR * const FEE_TYPE;

   extern IFASTBP_LINKAGE const I_CHAR * const HOLDING_COMP_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const HOLDING_COMP_NAME;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MFCANInterProcParam.hpp-arc  $
 * 
 *    Rev 1.50   Apr 04 2012 11:31:46   wp040039
 * PETP0187485-Registration Agent  Banking
 * 
 *    Rev 1.49   Mar 02 2012 16:39:30   wp040100
 * P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
 * 
 *    Rev 1.48   Mar 02 2012 15:01:18   jankovii
 * IN 2859411 - P0186477_FN02_Interest Instruction-Err displayed on split type 'Amount' instrctn
 * 
 *    Rev 1.47   Feb 21 2012 16:57:54   if991250
 * Added Reset
 * 
 *    Rev 1.46   Feb 21 2012 13:10:32   if991250
 * Trade Mat Sweep Instr Banks
 * 
 *    Rev 1.45   Feb 02 2012 15:07:22   if991250
 * Maturity/Interest Instructions banking
 * 
 *    Rev 1.44   Jan 31 2012 14:54:16   if991250
 * Added params for Maturity Instructions
 * 
 *    Rev 1.43   Jan 13 2010 09:08:00   dchatcha
 * IN# 1971377 - R97_Static Data_File Processor&Bank are blank after deleting distribution option.
 * 
 *    Rev 1.42   Jul 09 2009 14:17:42   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.41   Jan 07 2009 06:57:42   daechach
 * PETP0155543 FN01 - Account Level Distribution Instructions.
 * 
 *    Rev 1.40   Nov 02 2006 11:44:24   ZHANGCEL
 * PET2217 FN26 - Add a new parameter for Bank Instruction title display
 * 
 *    Rev 1.39   Nov 01 2006 11:18:22   ZHANGCEL
 * PET2217 FN26 -- Add a new parament to pop up FundSponsor list with <F4>
 * 
 *    Rev 1.38   Jul 27 2006 17:56:02   ZHANGCEL
 * PET2192 FN11 - Add a new parament for SearchTypeMgmt
 * 
 *    Rev 1.37   Feb 14 2006 14:09:40   zhengcon
 * Incident #528284 - add one field ModPerm for updatable permission of User Defined Maturity Date of converted account
 * 
 *    Rev 1.36   Apr 21 2005 11:13:38   hernando
 * Incident #278666 - Added External Trans Num.
 * 
 *    Rev 1.35   Apr 13 2005 15:19:32   hernando
 * PET1024 FN02 - Added Contract Type.
 * 
 *    Rev 1.34   Mar 21 2005 11:34:56   hernando
 * PET1024 FN02 - Added SEG_TRANS_EXIST.
 * 
 *    Rev 1.33   Mar 20 2005 19:39:24   hernando
 * PET1024 FN02 - Added MATURITY_DATE.
 * 
 *    Rev 1.32   Mar 08 2005 13:53:02   ZHANGCEL
 * PET1171 FN01 -- Added parameter for EntityAddressSearch issue
 * 
 *    Rev 1.31   Feb 16 2005 11:26:16   hernando
 * PET1117 FN66-68 - Added additional parameters to support Messages.
 * 
 *    Rev 1.30   Nov 26 2004 14:46:10   zhangcel
 * PET1117/FN8 -- Aggregated Order related changes
 * 
 *    Rev 1.29   Oct 27 2004 12:04:56   popescu
 * PET 1117/06, Trade processing, 
 * 
 *    Rev 1.28   Aug 10 2004 11:13:40   FENGYONG
 * PET117 FN5 - Client Condition Fee
 * 
 *    Rev 1.27   May 27 2004 17:19:58   HERNANDO
 * PET1017 FN01- Remarks-Confirmation change.   Allow Confirmation to view the Added Remark and allow copying it to the AWD object.
 * 
 *    Rev 1.26   Mar 02 2004 16:18:36   HERNANDO
 * PET965 FN11 - Added DELIVERY_OPTION, DOCUMENT_TYPE.
 * 
 *    Rev 1.25   Feb 22 2004 13:58:20   HERNANDO
 * PET965 FN11 - Added EFFECTIVE_DATE, ADDRESS_CODE, ENTITY_ID, ENTITY_TYPE, SEQNUMBER, ADDRESS_ID, ENTITY_CODE, ACCT_USE_CODE, and CURRENCY.
 * 
 *    Rev 1.24   Sep 01 2003 21:21:10   popescu
 * PET 809 FN 02, CIBC Multi fund enhancement
 * 
 *    Rev 1.23   Aug 18 2003 16:04:06   HERNANDO
 * Added PAYENTITY_ID and PAYINSTRUCT_ID.
 * 
 *    Rev 1.22   Aug 14 2003 15:44:02   popescu
 * Added new process ids for multi-fund gui and bp layer. Changed the id of the allocation process and dialog from *_ALLOCATIONS to *SIMPLE_ALLOCATION; introduced a new process(AllocationSplitProcess) with the Id *_ALLOCATIONS only at the bp level, that will decide which allocation screen should be invoked
 * 
 *    Rev 1.21   Aug 07 2003 18:35:44   popescu
 * added new param that will help set the UI selection on the desired bank
 * 
 *    Rev 1.20   Jul 09 2003 21:56:32   popescu
 * Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
 * 
 *    Rev 1.19   Jun 30 2003 16:56:26   popescu
 * added historical info search to the Broker Features search;
 * moved some param names to the mfcaniterprocparam namespace
 * 
 *    Rev 1.18   Jun 01 2003 17:07:32   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.17   May 31 2003 11:54:36   popescu
 * RRIF bank work
 * 
 *    Rev 1.16   May 26 2003 11:28:38   popescu
 * Parameters clean-up
 * 
 *    Rev 1.15   May 23 2003 10:04:08   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.14   Oct 09 2002 23:53:30   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.13   Jun 18 2002 15:45:12   HSUCHIN
 * added shareholder number
 * 
 *    Rev 1.12   Jun 08 2002 13:12:24   HSUCHIN
 * added settlement options
 * 
 *    Rev 1.11   24 May 2002 15:17:28   KOVACSRO
 * Fund and Client bank.
 * 
 *    Rev 1.10   22 May 2002 18:20:24   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   19 Mar 2002 13:17:58   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.8   Sep 25 2001 10:43:56   YINGBAOL
 * add BankType RRIF
 * 
 *    Rev 1.7   20 Jun 2001 16:44:32   YINGZ
 * add saving plan
 * 
 *    Rev 1.6   11 May 2001 16:33:08   YINGZ
 * code sync
 * 
 *    Rev 1.5   30 Mar 2001 17:09:20   BUZILAMI
 * Systematic bank changes
 * 
 *    Rev 1.4   07 Mar 2001 15:41:56   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 * 
 *    Rev 1.3   Feb 21 2001 10:39:26   BUZILAMI
 * Bank Acct changes
 * 
 *    Rev 1.2   Apr 28 2000 18:19:56   BUZILA
 * M3
 * 
 *    Rev 1.1   Apr 03 2000 08:56:24   BUZILA
 * Trade changes
 * 
 *    Rev 1.0   Mar 22 2000 13:07:38   BUZILA
 * Initial revision.
 * 
*/
