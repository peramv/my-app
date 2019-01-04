#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif   

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

#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

extern BPBASE_LINKAGE const I_CHAR *CMD_BPROC_CONFIRMATION;
extern BPBASE_LINKAGE const I_CHAR *CMD_BPROC_USER_SESSION;
extern BPBASE_LINKAGE const I_CHAR *CMD_BPROC_WORK_SESSION;

// Valid types for commands
const int GUI_TYPE              = 0x01000000;
const int DIALOG_TYPE           = 0x01010000;
const int BUSINESS_PROCESS_TYPE = 0x02000000;
const int SERVER_PROCESS_TYPE   = 0x03000000;


/**
 * This file contains enums and consts used for command processing.
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 11/19/98</dd></dl>
 * @version 0.1
 */

/**
 * Represents the different command return states.
 *
 * <pre>
 *@@ These are the valid return states:
 *@@   CMD_OK                 - Good return from modal process/dialog.
 *@@                          - Typically as a result of user pressing OK button.
 *@@   CMD_CANCEL             - Escape return from modal process/dialog.
 *@@                          - Typically as a result of user pressing Cancel button.
 *@@   CMD_MODELESS_INPROCESS - Return from modeless process/dialog indicating that
 *@@                          - it is in process.  This must be returned up the
 *@@                          - parent chain so the system can regain control and
 *@@                          - let the user work modelessly.  The modeless
 *@@                          - process/dialog will end only when the user performs
 *@@                          - an ending action.
 *@@   CMD_FAILURE            - The command failed to work correctly.
 *@@   CMD_NOT_FOUND          - The command was not found by the dispatcher.
 * </pre>
 */
enum E_COMMANDRETURN
{
   CMD_NO_RETURN,
   CMD_OK,
   CMD_CANCEL,
   CMD_MODELESS_INPROCESS,
   CMD_FAILURE,
   CMD_NOT_FOUND
};

/**
 * Represents the Global section to use.
 *
 * <pre>
 *@@ These are the valid sections:
 *@@   USER_GLOBAL     - These are globals for the user session.
 *@@   WORK_GLOBAL     - These are globals for the work session.
 * </pre>
 */
enum E_GLOBALTYPE
{
   USER_GLOBAL,
   WORK_GLOBAL
};

/**
 * Represents the possible modalities for a command.
 *
 * <pre>
 *@@ These are the valid modes:
 *@@   MODE_MODALONLY     - The command may only run modally.
 *@@   MODE_MODELESSONLY  - The command may only run modelessly.
 *@@   MODE_BOTH          - The command may run in either mode.
 * </pre>
 */
enum E_MODETYPE
{
   MODE_MODALONLY,
   MODE_MODELESSONLY,
   MODE_BOTH
};

/**
 * Represents the process type for a command.
 *
 * <pre>
 *@@ These are the valid process types:
 *@@   PROC_NEW       - The command involves creating something new (NASU).
 *@@   PROC_INQUIRY   - The command is in a read-only state.
 *@@   PROC_MAINT     - The command may perform maintenance (update) activities.
 * </pre>
 */
enum E_PROCESSTYPE
{
   PROC_NO_TYPE,
   PROC_NEW,                // NASU
   PROC_INQUIRY,            // Read-only
   PROC_MAINT,              // Updatable
   PROC_SUPPORT,            // No need to invoke confirmation
};

/**
 * Represents the search action when performing searches.
 *
 * <pre>
 *@@ These are the valid search actions:
 *@@   SEARCH_START      - Begin search.
 *@@   SEARCH_NEXT_BLOCK - Search for next block of records.
 * </pre>
 */
enum E_SEARCHACTION
{
   SEARCH_START,
   SEARCH_NEXT_BLOCK
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/CommandEnum.h-arc  $
 * 
 *    Rev 1.107   Nov 27 2002 15:04:32   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.106   27 Mar 2002 19:52:44   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.105   22 Mar 2002 15:08:14   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.104   Mar 06 2002 13:26:02   ULJAREVI
 * Added AgentCommissionProcess.
 * 
 *    Rev 1.103   Mar 05 2002 13:59:16   ULJAREVI
 * Added UnitholderOptionsProcess.
 * 
 *    Rev 1.102   21 Feb 2002 15:48:08   HSUCHIN
 * replaced interest accruals id with accrual
 * 
 *    Rev 1.101   Feb 12 2002 16:46:12   DINACORN
 * Removed ID-s for Unitholder Details ( GUI & Process ).
 * 
 *    Rev 1.100   Feb 01 2002 15:28:08   YINGBAOL
 * add Fee Param
 * 
 *    Rev 1.99   Jan 25 2002 11:56:50   FENGYONG
 * Add AccountSearch
 * 
 *    Rev 1.98   Jan 24 2002 14:29:18   ROSIORUC
 * Added Fast_Work_Unit
 * 
 *    Rev 1.97   Jan 10 2002 17:44:24   DINACORN
 * Added FAST_DEBIT_CARD ID-s.
 * 
 *    Rev 1.96   Jan 04 2002 10:29:18   OLTEANCR
 * added ClientUnitholder update
 * 
 *    Rev 1.95   Jan 02 2002 10:12:40   YINGBAOL
 * add AccountAllocation
 * 
 *    Rev 1.94   21 Dec 2001 13:59:18   MCNABBGL
 * removed CMDID_BPROC_ALLOCATIONS duplicity so that it fits into the compiler
 * 
 *    Rev 1.93   Dec 20 2001 18:28:04   FENGYONG
 * Add AccountAllocations
 * 
 *    Rev 1.92   Dec 19 2001 10:37:36   VADEANUM
 * Added support for GUI dealing.
 *
 *    Rev 1.91   Nov 30 2001 17:38:34   DINACORN
 * Added FAST_DETAILS_UNITHOLDER (GUI & PROCESS).
 *
 *    Rev 1.90   Nov 09 2001 15:47:52   ROSIORUC
 * Added ComplexDealing process
 *
 *    Rev 1.89   Oct 29 2001 18:22:32   DINACORN
 * Added GUI_FAST_DETAILS_AGENT.
 *
 *    Rev 1.88   Oct 23 2001 11:51:08   ULJAREVI
 * Added MandateMethodListProcess.
 *
 *    Rev 1.87   Oct 21 2001 14:21:20   OLTEANCR
 * added CMD/CMDID_VERIFY_SEARCH_AGENT,    CMD/CMDID_GUI_FAST_DETAILS
 *
 *    Rev 1.86   18 Oct 2001 11:23:56   SMITHDAV
 * Shutdown process additions.
 *
 *    Rev 1.85   Oct 17 2001 16:52:54   VADEANUM
 * FAST Agent and Client Details support.
 *
 *    Rev 1.84   Oct 15 2001 15:46:22   OLTEANCR
 * added VerifySearchDlg for FAST
 *
 *    Rev 1.83   Oct 11 2001 10:36:46   VADEANUM
 * Fast GUI search support.
 *
 *    Rev 1.82   20 Sep 2001 13:44:24   KOVACSRO
 * Added Esop Historical.
 *
 *    Rev 1.81   23 Aug 2001 11:23:26   HSUCHIN
 * Added Account Level Split Commission
 *
 *    Rev 1.80   Aug 23 2001 11:31:08   JANKAREN
 * Added As Pension Plan
 *
 *    Rev 1.79   Aug 14 2001 12:01:32   OLTEANCR
 * added FundList Process for FAST
 *
 *    Rev 1.78   Aug 14 2001 09:59:56   ZHANGCEL
 * Added defination for MatchTransfer
 *
 *    Rev 1.77   08 Aug 2001 11:03:54   PURDYECH
 * Added ClientInquiry Process for FAST
 *
 *    Rev 1.76   05 Aug 2001 15:25:56   HSUCHIN
 * added RSPContribution and RSPReceipts ids
 *
 *    Rev 1.75   31 Jul 2001 17:01:48   KOVACSRO
 * Added ESoPInfo.
 *
 *    Rev 1.74   26 Jul 2001 15:51:24   KOVACSRO
 * Added CMDID_BPROC_JTRADES   for efan.
 *
 *    Rev 1.73   Jul 16 2001 19:44:54   OLTEANCR
 * added  CMDID_GUI_CONTRACTINFO1
 *
 *    Rev 1.72   Jul 10 2001 09:50:52   ULJAREVI
 * Addde PrefixTypeListProcess, UKPostCodeSearchProcess support.
 *
 *    Rev 1.71   09 Jul 2001 15:25:02   SMITHDAV
 * Mgmt company refresh related changes.
 *
 *    Rev 1.70   Jun 27 2001 11:34:42   VADEANUM
 * Added BookTypeList, PriceTypeList, PriceBasisList support.
 *
 *    Rev 1.69   Jun 25 2001 18:21:52   VADEANUM
 * Added AnalysisCodeList support.
 *
 *    Rev 1.68   Jun 25 2001 16:13:20   VADEANUM
 * Added EventList support.
 *
 *    Rev 1.67   Jun 25 2001 11:39:52   VADEANUM
 * Added OriginId support.
 *
 *    Rev 1.66   Jun 12 2001 19:27:42   IVESPAUL
 * Re-implemented various RSF/RIF/Mandates functionality.
 *
 *    Rev 1.65   Jun 12 2001 15:26:46   ULJAREVI
 * Added MandateInstructionListProcess misc.
 *
 *    Rev 1.64   Jun 12 2001 11:24:28   MCNABBGL
 * session update changes
 *
 *    Rev 1.63   Jun 06 2001 18:16:14   MCNABBGL
 * session changes for fast code
 *
 *    Rev 1.62   28 May 2001 13:26:36   HSUCHIN
 * added SYSTEMATIC_INDEXING
 *
 *    Rev 1.61   May 16 2001 17:19:00   HERNANDO
 * Added Historical Systematic Index.
 *
 *    Rev 1.60   May 11 2001 16:27:36   HERNANDO
 * Sync-up 1.58.1.1
 *
 *    Rev 1.59   10 May 2001 16:54:40   SMITHDAV
 * Sync-up 1.58.1.1 & 1.58.2.0.
 *
 *    Rev 1.58   Mar 29 2001 13:52:50   ROSIORUC
 * Added UnitholderSystemOptions
 *
 *    Rev 1.57   Mar 27 2001 10:27:16   ROSIORUC
 * Added ClientSystemOptions
 *
 *    Rev 1.56   Mar 23 2001 10:56:16   ROSIORUC
 * Added RSFSystemOptions
 *
 *    Rev 1.55   Mar 23 2001 10:34:46   OLTEANCR
 * added CMDID_GUI_GUARANTEEINFO1
 *
 *    Rev 1.54   Mar 19 2001 11:43:10   YINGZ
 * take out trans banking
 *
 *    Rev 1.53   Mar 16 2001 15:01:30   VASILEAD
 * Added ACCOUNT_INQUIRY process
 *
 *    Rev 1.52   Mar 16 2001 14:10:30   ULJAREVI
 * Merged with new data broker changes.
 *
 *    Rev 1.51   Mar 12 2001 12:56:26   VASILEAD
 * Added TransactionSummary
 *
 *    Rev 1.50   Mar 12 2001 12:36:16   ULJAREVI
 * Mandates.
 *
 *    Rev 1.49   Mar 08 2001 15:29:40   ZHANGCEL
 * Added CMD_BPROC_BANKSEARCH AND CMD_GUI_BANK_SEARCH
 *
 *    Rev 1.48   Mar 06 2001 14:18:28   YINGZ
 * support splitcommission
 *
 *    Rev 1.47   Mar 04 2001 11:34:26   VASILEAD
 * Added  AccountHoldingsInquiryProcess
 *
 *    Rev 1.46   Feb 21 2001 16:06:38   BUZILAMI
 * changed BankAcct*.?pp => BankInstr*.?pp
 *
 *    Rev 1.45   Feb 12 2001 16:30:48   BUZILAMI
 * fix
 *
 *    Rev 1.44   Feb 12 2001 15:49:02   YINGZ
 * add apinasu
 *
 *    Rev 1.43   Feb 12 2001 12:54:12   BUZILAMI
 * Added New Banking
 *
 *    Rev 1.42   Jan 30 2001 12:07:40   OLTEANCR
 * added CMD_..AVAILABILITY & CMDID_ AVAILABILTIY
 *
 *    Rev 1.41   Jan 10 2001 14:36:34   VADEANUM
 * Added PIN Correspondence support.
 *
 *    Rev 1.40   Dec 28 2000 18:24:18   HUDAVID
 * Add CMD_BPROC_DEAL_DETAILS
 *
 *    Rev 1.39   Dec 14 2000 17:15:14   VADEANUM
 * Added Agent Locate support.
 *
 *    Rev 1.38   Dec 13 2000 16:18:58   VADEANUM
 * Added Transaction History support.
 *
 *    Rev 1.37   Dec 06 2000 10:33:30   VADEANUM
 * Added Account Search support.
 *
 *    Rev 1.36   Dec 05 2000 11:30:36   MCNABBGL
 * forgot CMDID definition for CMDID_BPROC_FAST_UNITHOLDER_VALUATION
 *
 *    Rev 1.35   Dec 05 2000 10:46:40   MCNABBGL
 * added CMD_BPROC_FAST_UNITHOLDER_VALUATION
 *
 *    Rev 1.34   04 Dec 2000 16:37:58   PURDYECH
 * Added FAST_CLIENT_VALIDATE and FAST_DEBIT_CARD_VALIDATE process constants.
 *
 *    Rev 1.33   Dec 04 2000 11:17:40   VASILEAD
 * Added FundToList
 *
 *    Rev 1.32   Nov 24 2000 09:38:06   MCNABBGL
 * added unittype and scheme
 *
 *    Rev 1.31   Nov 23 2000 17:31:40   VADEANUM
 * Added Fast Bank Search support.
 *
 *    Rev 1.30   Nov 21 2000 14:38:28   HUDAVID
 * Added ChangeHostMode command
 *
 *    Rev 1.29   Nov 21 2000 10:18:26   VASILEAD
 * Added AllFundInfo
 *
 *    Rev 1.28   Nov 14 2000 16:57:58   VADEANUM
 * Added Locate Unitholder environment.
 *
 *    Rev 1.27   Oct 23 2000 16:17:38   IVESPAUL
 * Added externs - seems like the thing to do.  Why?
 *
 *    Rev 1.26   23 Oct 2000 14:17:56   PURDYECH
 * Changed name of CMDID_BPROC_FAST_DEBIT_CARD to include _UPDATE.
 *
 *    Rev 1.25   23 Oct 2000 11:03:36   PURDYECH
 * Added DebitCard Update stuff
 *
 *    Rev 1.24   Oct 23 2000 10:44:54   IVESPAUL
 * Added Client and Unitholder environments.
 *
 *    Rev 1.23   17 Oct 2000 14:13:38   PURDYECH
 * Added AddressService support
 *
 *    Rev 1.22   Oct 16 2000 11:13:34   VASILEAD
 * Added SetDataServer command
 *
 *    Rev 1.21   Oct 02 2000 11:20:02   MCNABBGL
 * changes for predealing in emx
 *
 *    Rev 1.20   Sep 28 2000 14:57:42   MCNABBGL
 * Added Fast commands; cleaned up files
 *
 *    Rev 1.19   Sep 07 2000 12:00:12   FENGYONG
 * Add new process
 *
 *    Rev 1.18   Aug 10 2000 19:31:16   FENGYONG
 * Add JEntityListProcess
 *
 *    Rev 1.17   Aug 02 2000 14:03:04   VASILEAD
 * Added command for Maintenance process
 *
 *    Rev 1.16   Jul 20 2000 16:53:44   KOVACSRO
 * added RESP Beneficiary Relationship screen stuff
 *
 *    Rev 1.15   Jul 20 2000 15:18:28   VASILEAD
 * Added VerificationConf service, process and CBO
 *
 *    Rev 1.14   Jul 20 2000 10:09:54   KOVACSRO
 * added CMDID_BPROC_RESPBENREL
 *
 *    Rev 1.13   May 16 2000 16:34:30   PRAGERYA
 * Unitholder Process implemented
 *
 *    Rev 1.12   May 08 2000 17:07:00   YINGZ
 * add RedCodeByTaxTypeProcess support
 *
 *    Rev 1.11   May 08 2000 15:00:44   BUZILA
 * added FUNDCLASS process
 *
 *    Rev 1.10   Apr 24 2000 11:55:32   YINGZ
 * add
 *
 *    Rev 1.9   Apr 13 2000 14:36:02   POPESCUS
 * processes for Fast
 *
 *    Rev 1.8   Mar 24 2000 16:23:14   POPESCUS
 * added processes for Vision
 *
 *    Rev 1.7   Mar 20 2000 15:45:58   ZHANGCEL
 * Added MinMaxInfo Stuffs
 *
 *    Rev 1.6   Mar 09 2000 15:50:58   PETOLESC
 * Added TaxRates, RESPInfo, RESPTransactions.
 *
 *    Rev 1.5   Mar 09 2000 15:12:44   ZHANGCEL
 * Added GuaranteeInfo stuffs
 *
 *    Rev 1.4   Mar 02 2000 14:41:58   HSUCHIN
 * Contract Info added
 *
 *    Rev 1.3   Feb 29 2000 15:21:10   BUZILA
 * added Trading screen/process/CBO
 *
 *    Rev 1.2   Feb 28 2000 15:30:50   PRAGERYA
 * Check-in For Mihai
 *
 *    Rev 1.1   Feb 15 2000 18:54:58   MCNABBGL
 * changed comment format
 *
 *    Rev 1.0   Feb 15 2000 10:57:48   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.17   Jan 19 2000 11:05:02   WINNIE
 * add broker process and dlg
 *
 *    Rev 1.16   Dec 23 1999 14:41:24   POPESCUS
 * added a new type of process PROC_SUPPORT
 *
 *    Rev 1.15   Dec 16 1999 14:01:10   ZHANGCEL
 * Add Branch and SalesRep stuff
 *
 *    Rev 1.14   Dec 02 1999 10:06:54   DT24433
 * removed ConfirmSave stuff
 *
 *    Rev 1.13   Nov 26 1999 14:04:08   YINGZ
 * add bank dlg
 *
 *    Rev 1.12   Nov 24 1999 09:51:00   FENGYONG
 * Add JFundSrchProcess
 *
 *    Rev 1.11   Nov 23 1999 18:05:42   POPESCUS
 * NASU flow
 *
 *    Rev 1.10   Nov 22 1999 12:10:18   FENGYONG
 * Add BP for Vision Team
 *
 *    Rev 1.9   Nov 22 1999 11:35:20   HUANGSHA
 * Added SystematicFee process & gui
 *
 *    Rev 1.8   Oct 30 1999 15:08:50   HSUCHIN
 * Added Historical Account
 *
 *    Rev 1.7   Sep 27 1999 10:46:54   PRAGERYA
 * Allocations checked in for release; transaction allocations not debugged yet
 *
 *    Rev 1.6   Sep 20 1999 16:42:36   HSUCHIN
 * Free Unit handling
 *
 *    Rev 1.5   Sep 19 1999 13:38:42   PRAGERYA
 * Allocations handling enhanced
 *
 *    Rev 1.4   Jul 28 1999 13:16:06   POPESCUS
 * Added a new process for entity search
 *
 *    Rev 1.3   Jul 27 1999 16:03:34   BUZILA
 * Increment M2
 *
 *    Rev 1.2   Jul 23 1999 10:20:38   POPESCUS
 * Added a new process that will fill the dstc front end combos
 *
 *    Rev 1.1   Jul 08 1999 10:03:38   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */


