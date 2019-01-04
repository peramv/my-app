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
// ^FILE   : Command.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 12/14/1998
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : Command
//    This class handles the information about a command
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "bpglobal.h"
#include "command.hpp"
#include <idistring.hpp>
#include <assert.h>
#include "commandtraits.hpp"

BPBASE_LINKAGE const I_CHAR *CMD_BPROC_CONFIRMATION                  = I_( "BPROC_CONFIRMATION" );
BPBASE_LINKAGE const I_CHAR *CMD_BPROC_WORK_SESSION                  = I_( "BPROC_WORK_SESSION" );
BPBASE_LINKAGE const I_CHAR *CMD_BPROC_USER_SESSION                  = I_( "BPROC_USER_SESSION" );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME       = I_( "Command" );
   const I_CHAR * const COPYCONSTRUCTOR = I_( "(Command &)" );
   const I_CHAR * const INIT            = I_( "init" );
   // Literals
   const I_CHAR * const CMD             = I_( "CMD" );

}

namespace CND
{  // Conditions used
   extern const long BP_ERR_MUST_RUN_MODAL;
   extern const long BP_ERR_MUST_RUN_MODELESS;
   extern const long BP_ERR_COMMAND_NOT_FOUND;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

SEVERITY Command::init(
                      const I_CHAR *szCommand,
                      E_PROCESSTYPE type,
                      bool bModal
                      )
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, INIT );  // Needs to change
   int i = 0;   
   const CommandTraits* pTraits = CommandTraitsMap::getInstance().get( DString( szCommand ) );

   if (NULL != pTraits)
   {
      *this = *pTraits;
      _bModal = bModal;      
      _eProcessType = type;
      _strName = szCommand;
      if( bModal && !canRunModal() )
      {  // Temporary - go to two step construction and return condition
         DString strIDI;
         addIDITagValue( strIDI, CMD, _strName );
         ADDCONDITIONFROMFILE( CND::BP_ERR_MUST_RUN_MODELESS );
      }
      else if( !bModal && !canRunModeless() )
      {
         DString strIDI;
         addIDITagValue( strIDI, CMD, _strName );
         ADDCONDITIONFROMFILE( CND::BP_ERR_MUST_RUN_MODAL );
      }
      return(GETHIGHESTSEVERITY());
   }


   assert( 0 );  // Command not found
   ADDCONDITIONFROMFILE( CND::BP_ERR_COMMAND_NOT_FOUND );
   return(GETHIGHESTSEVERITY());
}

//******************************************************************************

Command::Command( ) 
: _bModal( false )
, _commandType( 0 )
, _eProcessType( PROC_NO_TYPE )
, _id( 0 )
, _maxPerUserSession( 1 )
, _maxPerWorkSession( 1 )
, _windowHeight( -1 )
, _windowWidth( -1 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

Command::Command( const Command &cmd ) 
: _bModal( cmd._bModal )
, _commandType( cmd._commandType )
, _eAllowedModes( cmd._eAllowedModes )
, _eProcessType( cmd._eProcessType )
, _id( cmd._id )
, _maxPerUserSession( cmd._maxPerUserSession )
, _maxPerWorkSession( cmd._maxPerWorkSession )
, _strKey( cmd._strKey )
, _strName( cmd._strName )
, _webPageName (cmd._webPageName)
, _windowHeight( cmd._windowHeight )
, _windowWidth( cmd._windowWidth )
{
   TRACE_CONSTRUCTOR( CLASSNAME, COPYCONSTRUCTOR );
}

//******************************************************************************
Command::Command( const CommandTraits& traits )
: _bModal( false )
, _commandType( traits.getType() )
, _eAllowedModes( traits.getModes() )
, _eProcessType( PROC_NO_TYPE )
, _id( -1 )
, _maxPerUserSession( traits.getMaxPerUserSession() )
, _maxPerWorkSession( traits.getMaxPerWorkSession() )
, _strName( traits.getName() )
, _webPageName( traits.getWebPageName() )
, _windowHeight( traits.getWindowHeight() )
, _windowWidth( traits.getWindowWidth() )
{
}

//******************************************************************************

Command::~Command()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

bool Command::canRunModal() const
{
   return( _eAllowedModes != MODE_MODELESSONLY );
}

//******************************************************************************

bool Command::canRunModeless() const
{
   return( _eAllowedModes != MODE_MODALONLY );
}

//******************************************************************************

bool Command::isCommandTypeOf( int type ) const
{  // Currently, we allow 2 levels in the type hierarchy.  If the type passed in
   //  has a value for these levels in descending order we check against the
   //  command's type to see if we have a match.  We stop whenever the level
   //  of the type passed in no longer has a value - but at least the first
   //  level must have a value.
   int mask = 0xFF000000;

   if( (type & mask) != (_commandType  & mask) )
   {  // Didn't match first level
      return(false);
   }

   mask = 0x00FF0000;
   if( type & mask )
   {  // Check second level
      if( (type & mask) != (_commandType  & mask) )
      {  // Didn't match second level
         return(false);
      }
   }

   return(true);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfproc/Command.cpp-arc  $
//
//   Rev 1.116   06 Dec 2007 15:19:40   popescu
//Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
//
//   Rev 1.115   Jun 08 2006 13:41:06   FENGYONG
//Add webmapping for broswer launcher enhancement
 * 
 *    Rev 1.114   Jan 06 2003 16:43:22   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.113   Oct 09 2002 17:40:52   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.112   Aug 29 2002 13:47:16   PURDYECH
 * Base Condition split out
 * 
 *    Rev 1.111   27 Mar 2002 20:49:50   PURDYECH
 * Process/Dialog Factory overhaul.
 * 
 *    Rev 1.110.2.0   27 Mar 2002 19:47:20   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.110   Mar 06 2002 13:25:10   ULJAREVI
 * Added AgentCommissionProcess.
 * 
 *    Rev 1.109   Mar 05 2002 14:02:02   ULJAREVI
 * Added UnitholderOptionsProcess.
 * 
 *    Rev 1.108   21 Feb 2002 15:47:40   HSUCHIN
 * replaced Interest accruals id with accruals
 * 
 *    Rev 1.107   Feb 12 2002 16:37:04   DINACORN
 * Removed ID-s for Unitholder Details ( GUI & Process ).
 * 
 *    Rev 1.106   Feb 01 2002 15:27:34   YINGBAOL
 * add FeeParam
 * 
 *    Rev 1.105   Jan 25 2002 11:56:30   FENGYONG
 * Add AccountSearch
 * 
 *    Rev 1.104   Jan 24 2002 14:27:06   ROSIORUC
 * Added FAST_WORK_UNIT
 * 
 *    Rev 1.103   Jan 10 2002 17:44:30   DINACORN
 * Added FAST_DEBIT_CARD ID-s.
 * 
 *    Rev 1.102   Jan 07 2002 15:43:04   FENGYONG
 * change process name for api
 * 
 *    Rev 1.101   Jan 04 2002 10:37:12   FENGYONG
 * change process name for api slsrepupdate
 * 
 *    Rev 1.100   Jan 04 2002 10:29:52   OLTEANCR
 * added ClientUnitholder update
 * 
 *    Rev 1.99   Dec 20 2001 18:27:00   FENGYONG
 * Add AccountAllocations
 * 
 *    Rev 1.98   Dec 19 2001 10:37:56   VADEANUM
 * Added support for GUI dealing.
 *
 *    Rev 1.97   Nov 30 2001 17:38:38   DINACORN
 * Added FAST_DETAILS_UNITHOLDER (GUI & PROCESS).
 *
 *    Rev 1.96   Nov 09 2001 15:47:28   ROSIORUC
 * Added ComplexDealing process
 *
 *    Rev 1.95   Oct 29 2001 18:21:54   DINACORN
 * Added GUI_FAST_DETAILS_AGENT.
 *
 *    Rev 1.94   Oct 25 2001 11:12:58   VADEANUM
 * Fast Agent Search must be MODALONLY.
 *
 *    Rev 1.93   Oct 23 2001 12:03:08   ULJAREVI
 * Added MandateMethodListProcess.
/*
 *    Rev 1.92   Oct 21 2001 14:21:50   OLTEANCR
 * added CMD/CMDID_VERIFY_SEARCH_AGENT,    CMD/CMDID_GUI_FAST_DETAILS
 *
 *    Rev 1.91   18 Oct 2001 11:23:32   SMITHDAV
 * Shutdown process additions.
 *
 *    Rev 1.90   Oct 17 2001 16:52:06   VADEANUM
 * FAST Agent and Client Details support.
 *
 *    Rev 1.89   Oct 15 2001 15:45:50   OLTEANCR
 * added VerifySearchDlg for FAST
 *
 *    Rev 1.88   Oct 11 2001 10:36:14   VADEANUM
 * Fast GUI search support.
 *
 *    Rev 1.87   20 Sep 2001 13:43:48   KOVACSRO
 * Added Esop Historical.
 *
 *    Rev 1.86   23 Aug 2001 11:23:54   HSUCHIN
 * Added Account Level Split Commission
 *
 *    Rev 1.85   Aug 23 2001 11:00:58   JANKAREN
 * Added As Pension Plan
 *
 *    Rev 1.84   Aug 14 2001 12:00:38   OLTEANCR
 * added FundList Process for FAST
 *
 *    Rev 1.83   Aug 14 2001 10:19:06   ZHANGCEL
 * Added defination for MatchTransfer
 *
 *    Rev 1.82   08 Aug 2001 11:03:40   PURDYECH
 * Added ClientInquiry Process for FAST
 *
 *    Rev 1.81   05 Aug 2001 15:25:56   HSUCHIN
 * added RSPContribution and RSPReceipts ids
 *
 *    Rev 1.80   31 Jul 2001 17:01:20   KOVACSRO
 * Added ESoPInfo.
 *
 *    Rev 1.79   26 Jul 2001 15:50:30   KOVACSRO
 * Added JTRADES for efan.
 *
 *    Rev 1.78   23 Jul 2001 16:51:22   KOVACSRO
 * Change StatusReport back to AvailabilityProcess.
 *
 *    Rev 1.77   Jul 16 2001 19:36:10   OLTEANCR
 * added contractinfo1
 *
 *    Rev 1.76   Jul 10 2001 09:50:16   ULJAREVI
 * Added PrefixTypeListProcess, UKPostCodeSearchProcess support.
 *
 *    Rev 1.75   09 Jul 2001 15:25:02   SMITHDAV
 * Mgmt company refresh related changes.
 *
 *    Rev 1.74   Jun 27 2001 11:35:28   VADEANUM
 * Added BookTypeList, PriceTypeList, PriceBasisList support.
 *
 *    Rev 1.73   Jun 25 2001 18:20:42   VADEANUM
 * Added AnalysisCodeList support.
 *
 *    Rev 1.72   Jun 25 2001 16:14:24   VADEANUM
 * Added EventList support.
 *
 *    Rev 1.71   Jun 25 2001 11:38:36   VADEANUM
 * Added OriginId support.
 *
 *    Rev 1.70   Jun 12 2001 19:27:36   IVESPAUL
 * Re-implemented various RSF/RIF/Mandates functionality.
 *
 *    Rev 1.69   Jun 12 2001 15:24:34   ULJAREVI
 * Added MandateInstructionListProcess misc.
 *
 *    Rev 1.68   Jun 12 2001 11:23:24   MCNABBGL
 * session update changes
 *
 *    Rev 1.67   Jun 06 2001 18:13:16   MCNABBGL
 * session changes for fast code
 *
 *    Rev 1.66   28 May 2001 13:26:18   HSUCHIN
 * added SYSTEMATIC_INDEXING
 *
 *    Rev 1.65   May 16 2001 17:17:28   HERNANDO
 * Add Historical Systematic Index.
 *
 *    Rev 1.64   10 May 2001 13:34:32   SMITHDAV
 * Sync-up 1.63.1.0 & 1.63.2.0.
 *
 *    Rev 1.63   Mar 29 2001 13:48:40   ROSIORUC
 * Added UnitholderSystemOptions tags
 *
 *    Rev 1.62   Mar 27 2001 10:32:44   ROSIORUC
 * Added ClientSystemOptions
 *
 *    Rev 1.61   Mar 23 2001 11:01:22   ROSIORUC
 * added RSFSystemOptions
 *
 *    Rev 1.60   Mar 23 2001 10:33:10   OLTEANCR
 * added CMD_GUI_GUARANTEEINFO1
 *
 *    Rev 1.59   Mar 19 2001 11:41:32   YINGZ
 * take out trans banking
 *
 *    Rev 1.58   Mar 16 2001 15:01:54   VASILEAD
 * Added ACCOUNT_INQUIRY process
 *
 *    Rev 1.57   Mar 16 2001 14:08:22   ULJAREVI
 * Merged with new data broker changes.
 *
 *    Rev 1.56   Mar 12 2001 12:56:22   VASILEAD
 * Added TransactionSummary
 *
 *    Rev 1.55   Mar 12 2001 12:34:18   ULJAREVI
 * Address Mandates.
 *
 *    Rev 1.54   Mar 08 2001 15:29:12   ZHANGCEL
 * Added CMD_BPROC_BANKSEARCH AND CMD_GUI_BANK_SEARCH
 *
 *    Rev 1.53   Mar 06 2001 14:18:14   YINGZ
 * support splitcommission
 *
 *    Rev 1.52   Mar 04 2001 11:33:52   VASILEAD
 * Added  AccountHoldingsInquiryProcess
 *
 *    Rev 1.51   Mar 01 2001 14:21:02   YINGZ
 * set some process names for xml api
 *
 *    Rev 1.50   Feb 21 2001 16:06:10   BUZILAMI
 * changed BankAcct*.?pp => BankInstr*.?pp
 *
 *    Rev 1.49   Feb 12 2001 15:48:46   YINGZ
 * add apinasu
 *
 *    Rev 1.48   Feb 12 2001 12:54:10   BUZILAMI
 * Added New Banking
 *
 *    Rev 1.47   Feb 06 2001 14:00:00   YINGZ
 * rename AddressProcess
 *
 *    Rev 1.46   Jan 30 2001 12:06:08   OLTEANCR
 * added CMD_.. AVAILABILITY & CMDID_...AVAILABILTY
 *
 *    Rev 1.45   Jan 30 2001 10:40:34   YINGZ
 * change the processname
 *
 *    Rev 1.44   Jan 22 2001 16:26:54   YINGZ
 * make distributionb work and change process names
 *
 *    Rev 1.43   Jan 10 2001 14:35:22   VADEANUM
 * Added PIN Correspondence support.
 *
 *    Rev 1.42   Jan 02 2001 15:05:52   MCNABBGL
 * deal details changes
 *
 *    Rev 1.41   Dec 28 2000 18:22:56   HUDAVID
 * Added CMD_BPROC_DEAL_DETAILS
 *
 *    Rev 1.40   Dec 20 2000 13:33:08   YINGZ
 * add CMD_BPROC_REDEMPTION and CMD_BPROC_EXCHANGE which all trigger CMDID_BPROC_TRADES. this is for xml
 *
 *    Rev 1.39   Dec 14 2000 17:16:10   VADEANUM
 * Added Agent Locate support.
 *
 *    Rev 1.38   Dec 13 2000 16:19:20   VADEANUM
 * Added Transaction History support.
 *
 *    Rev 1.37   Dec 06 2000 10:37:52   VADEANUM
 * Added Account Search support.
 *
 *    Rev 1.36   Dec 05 2000 10:46:42   MCNABBGL
 * added CMD_BPROC_FAST_UNITHOLDER_VALUATION
 *
 *    Rev 1.35   04 Dec 2000 16:38:40   PURDYECH
 * Added FAST_CLIENT_VALIDATE and FAST_DEBIT_CARD_VALIDATE process constants.
 *
 *    Rev 1.34   Dec 04 2000 11:17:26   VASILEAD
 * Added FundToList
 *
 *    Rev 1.33   Nov 24 2000 09:37:44   MCNABBGL
 * added scheme and unittype
 *
 *    Rev 1.32   Nov 23 2000 17:34:36   VADEANUM
 * Added Fast Bank Search support.
 *
 *    Rev 1.31   Nov 21 2000 14:38:32   HUDAVID
 * Added ChangeHostMode command
 *
 *    Rev 1.30   Nov 21 2000 10:18:24   VASILEAD
 * Added AllFundInfo
 *
 *    Rev 1.29   Nov 20 2000 10:40:24   FENGYONG
 * change commandtype
 *
 *    Rev 1.28   Nov 14 2000 16:55:06   VADEANUM
 * Added Locate Unitholder environment.
 *
 *    Rev 1.27   Nov 08 2000 10:37:10   DT24433
 * made BPROC_ACCTDETL and BPROC_TRADES string definitions more user friendly for XML.
 *
 *    Rev 1.26   23 Oct 2000 11:03:22   PURDYECH
 * Added DebitCard Update stuff
 *
 *    Rev 1.25   Oct 23 2000 10:45:20   IVESPAUL
 * Added Client and Unitholder environments.
 *
 *    Rev 1.24   17 Oct 2000 14:13:34   PURDYECH
 * Added AddressService support
 *
 *    Rev 1.23   Oct 16 2000 11:13:20   VASILEAD
 * Added SetDataServer command
 *
 *    Rev 1.22   Oct 02 2000 11:19:34   MCNABBGL
 * changes for predeal
 *
 *    Rev 1.21   Sep 28 2000 14:57:40   MCNABBGL
 * Added Fast commands; cleaned up files
 *
 *    Rev 1.20   Sep 19 2000 15:20:38   VASILEAD
 * Cleanup services, UserSeesionProcess and security object
 *
 *    Rev 1.18   Aug 10 2000 19:31:00   FENGYONG
 * Add JEntityListProcess
 *
 *    Rev 1.17   Aug 03 2000 10:53:36   IVESPAUL
 * Dealing changes,  server, process, cbo and databroker.
 *
 *    Rev 1.16   Aug 02 2000 14:02:52   VASILEAD
 * Added command for Maintenance process
 *
 *    Rev 1.15   Jul 20 2000 16:55:24   KOVACSRO
 * added RESP Beneficiary Relationship screen stuff
 *
 *    Rev 1.14   Jul 20 2000 15:18:28   VASILEAD
 * Added VerificationConf service, process and CBO
 *
 *    Rev 1.13   Jul 20 2000 09:45:32   KOVACSRO
 * added CMD_BPROC_RESPBENREL
 *
 *    Rev 1.12   May 16 2000 16:34:18   PRAGERYA
 * Unitholder Process implemented
 *
 *    Rev 1.11   May 08 2000 17:06:48   YINGZ
 * add RedCodeByTaxTypeProcess support
 *
 *    Rev 1.10   May 08 2000 15:00:42   BUZILA
 * added FUNDCLASS process
 *
 *    Rev 1.9   Apr 24 2000 11:56:12   YINGZ
 * add CMDID_BPROC_JFUNDINDIV etc
 *
 *    Rev 1.8   Apr 13 2000 14:36:02   POPESCUS
 * processes for Fast
 *
 *    Rev 1.7   Mar 24 2000 16:23:14   POPESCUS
 * added processes for Vision
 *
 *    Rev 1.6   Mar 20 2000 15:40:54   ZHANGCEL
 * Added MinMaxInfo stuffs
 *
 *    Rev 1.5   Mar 09 2000 15:50:58   PETOLESC
 * Added TaxRates, RESPInfo, RESPTransactions.
 *
 *    Rev 1.4   Mar 09 2000 15:11:42   ZHANGCEL
 * Added GuaranteeInfo stuffs
 *
 *    Rev 1.3   Mar 02 2000 14:41:58   HSUCHIN
 * Contract Info added
 *
 *    Rev 1.2   Feb 29 2000 15:21:08   BUZILA
 * added Trading screen/process/CBO
 *
 *    Rev 1.1   Feb 28 2000 15:30:50   PRAGERYA
 * Check-in For Mihai
 *
 *    Rev 1.0   Feb 15 2000 10:57:34   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.19   Jan 22 2000 15:42:14   WINNIE
 * To get search work
 *
 *    Rev 1.18   Jan 19 2000 11:09:22   WINNIE
 * add broker screen
 *
 *    Rev 1.17   Dec 16 1999 14:01:30   ZHANGCEL
 * Add Branch and SalesRep stuff
 *
 *    Rev 1.16   Dec 02 1999 10:04:58   DT24433
 * removed ConfirmSave stuff
 *
 *    Rev 1.15   Nov 26 1999 14:04:40   YINGZ
 * add bank dlg
 *
 *    Rev 1.14   Nov 24 1999 09:49:50   FENGYONG
 * Add JFundSrchprocess
 *
 *    Rev 1.13   Nov 23 1999 18:05:36   POPESCUS
 * NASU flow
 *
 *    Rev 1.12   Nov 22 1999 12:11:02   FENGYONG
 * Add BP for Vision Team
 *
 *    Rev 1.11   Nov 22 1999 11:35:02   HUANGSHA
 * Added SystematicFee process & gui
 *
 *    Rev 1.10   Oct 30 1999 15:08:46   HSUCHIN
 * Added Historical Account
 *
 *    Rev 1.9   Sep 27 1999 10:45:18   PRAGERYA
 * Allocations checked in for release; transaction allocations not debugged yet
 *
 *    Rev 1.8   Sep 24 1999 10:09:38   PRAGERYA
 * "Milestone" check in
 *
 *    Rev 1.7   Sep 20 1999 16:42:20   HSUCHIN
 * Free Unit handling
 *
 *    Rev 1.6   Sep 19 1999 13:36:10   PRAGERYA
 * Allocations handling enhanced
 *
 *    Rev 1.5   Jul 28 1999 13:16:04   POPESCUS
 * Added a new process for entity search
 *
 *    Rev 1.4   Jul 27 1999 16:01:46   BUZILA
 * Increment M2
 *
 *    Rev 1.3   Jul 23 1999 10:22:28   POPESCUS
 * Added a new Process that will fill in the dstc front end combos
 *
 *    Rev 1.2   Jul 20 1999 11:14:00   VASILEAD
 * New conditions update
 *
 *    Rev 1.1   Jul 08 1999 10:01:58   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
