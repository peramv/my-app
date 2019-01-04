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
// ^FILE   : RESPTransactionsProcess.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 01/20/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RESPTransactionsProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "resptransactionsprocess.hpp"
#include "resptransactionsprocessincludes.h"
#include <ifastcbo\resptransactionslist.hpp>
#include <ifastcbo\respinfo.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\resptradesearchcriteria.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_RESPTRANSACTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESPTRANSACTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_BENEF_ALLOCATION_LIST;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RESPTransactionsProcess > processCreator( CMD_BPROC_RESPTRANSACTIONS );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "RESPTransactionsProcess" );
}

namespace RESPTRANSACTIONSNAMES
{
   const I_CHAR * const ACCOUNT_NUMBER_FIELD  = I_( "AccountNum" );
   const I_CHAR * const HISTORY_PENDING_FIELD = I_( "HistoryPending" );
   const I_CHAR * const SHAREHOLDER_FIELD     = I_( "ShareholderNum" );
   const I_CHAR * const LAST_NAME_FIELD       = I_( "LastName");
   const I_CHAR * const FIRST_NAME_FIELD      = I_( "FirstName");
   const I_CHAR * const TRANS_HIST            = I_( "TransHist" );
   const I_CHAR * const CALLER                = I_( "Caller" );
   const I_CHAR * const TRADE_DATE            = I_( "TradeDate" );

   const I_CHAR * const TRANSACTIONS_PENDING  = I_( "Pending" );
   const I_CHAR * const HISTORY               = I_( "H" );
   const I_CHAR * const PENDING               = I_( "P" );
   const I_CHAR * const YES                   = I_( "Y" );
   const I_CHAR * const NO                    = I_( "N" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId HistNonTrustYear;
}

using namespace RESPTRANSACTIONSNAMES;

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319RESPTransactionsProcess::RESPTransactionsProcess() : 
RESPTransactionsProcess::RESPTransactionsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ),
_rpChildGI( NULL ),
_pRESPTransactionsList (NULL),
_strAccountNum (NULL_STRING), 
_strHistoryPending (NULL_STRING),
_strTransId (NULL_STRING),
_strTradeDate (NULL_STRING),
_strCaller (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

//   addSubstituteList( DBR::RESPTransactionHeadingSet );

   addContainer( IFASTBP_PROC::RESP_CRITERIA, false, BF::NullContainerId, true, I_("RESPCriteria") );
   //addContainer (IFASTBP_PROC::RESPTRANSACTIONS_LIST, true, BF::NullContainerId, false);
   addContainer (IFASTBP_PROC::RESPTRANSACTIONS_LIST, true, IFASTBP_PROC::RESP_CRITERIA, false);

   addFieldDetails( ifds::BeneName, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::DepositType, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::DepositTypeDesc, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::RedCode, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::RedCodeDesc, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::TransId, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::GrossAmt, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::HRDCTransId, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::SettleDate, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::ACAmt, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::TerminateDate, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::GrantAmount, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::LifeContr, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::GrantTransCode, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::GrantTransLabel, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::GrantTransId, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::RedLifeContr, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::UCAmt, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::UCReason, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::UCReasonDesc, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::OldContractId, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::OldPlanId, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::RESPLetter, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::HRDCReported, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::RESPTransStat, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::GrantRepayable, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::GrantRepayablePurch, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::YTDContr, IFASTBP_PROC::RESPTRANSACTIONS_LIST );

   addFieldDetails( ifds::TransType, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::AmountType, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::Cancelled, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::Reversal, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::HRDCPending, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::GrossNet, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::TradeGrossAmt, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::TransNum, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::AddlCESGRsnCode, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::AddlCESGRsnDesc, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::NeedRepHRDC, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::CESGInDetlErrorDesc, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::OCRdmYear, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::CESGAmount, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::Tainted, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::GratRepayReasonAll, IFASTBP_PROC::RESPTRANSACTIONS_LIST );

   addFieldDetails( ifds::RESPContrDetlTaxYear, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::PurAdd, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::PurCLB, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::PurQESI, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::AddtlQESI, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::PurPGrant, IFASTBP_PROC::RESPTRANSACTIONS_LIST );

   addFieldDetails( ifds::RedIncome, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::RedCLB, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::RedCESG, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::RedPGrant, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::RedQESI, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::AccountTo, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::AIPAcctName, IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails ( ifds::HistNonTrustYear,IFASTBP_PROC::RESPTRANSACTIONS_LIST);
   addFieldDetails ( ifds::IsResidualCESG,IFASTBP_PROC::RESPTRANSACTIONS_LIST);

   // SAGES fields
   addFieldDetails( ifds::SAGESPurAmt,    IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::SAGESRedAmt,    IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::SAGESTransID,    IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::SAGESTransOrigCode,    IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::SAGESUCDesc,    IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::SAGESRejDesc,    IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::SAGESReported,    IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::SAGESUCAmt,     IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   addFieldDetails( ifds::SAGESACAmt,     IFASTBP_PROC::RESPTRANSACTIONS_LIST );

   //BCTESG
   addFieldDetails( ifds::BCTESGGrant,    IFASTBP_PROC::RESPTRANSACTIONS_LIST );
   
   // search fields:
   addFieldDetails( ifds::RESPBenefId,    IFASTBP_PROC::RESP_CRITERIA );
   addFieldDetails( ifds::FromDate,       IFASTBP_PROC::RESP_CRITERIA );
   addFieldDetails( ifds::ToDate,         IFASTBP_PROC::RESP_CRITERIA );
   addFieldDetails( ifds::TfrStat,        IFASTBP_PROC::RESP_CRITERIA );
   addFieldDetails( ifds::TransTypeDesc,  IFASTBP_PROC::RESP_CRITERIA );
   addFieldDetails( ifds::RepHRDC,        IFASTBP_PROC::RESP_CRITERIA );
   addFieldDetails( ifds::HistoryPending, IFASTBP_PROC::RESP_CRITERIA );

}

//******************************************************************************
RESPTransactionsProcess::~RESPTransactionsProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool RESPTransactionsProcess::doCancel( GenericInterface *rpGI )
{
   TRACE_METHOD( CLASSNAME, DOCANCEL );
   bool bRtn = true;
   return bRtn;
}

//******************************************************************************
SEVERITY RESPTransactionsProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      getParent()->getParameter( ACCOUNT_NUMBER_FIELD, _strAccountNum );
      getParent()->getParameter( HISTORY_PENDING_FIELD, _strHistoryPending );
      getParent()->getParameter( I_("TransId"), _strTransId );
      getParent()->getParameter( CALLER, _strCaller );
      getParent()->getParameter( TRADE_DATE, _strTradeDate );
      removeTransactionList (this, RESPTRANSACTIONSNAMES::HISTORY);
      removeTransactionList (this, RESPTRANSACTIONSNAMES::PENDING);
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPTransactionsProcess::doOk (GenericInterface *rpGI)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOOK );

   return true;
}

//******************************************************************************
E_COMMANDRETURN RESPTransactionsProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( ACCOUNT_NUMBER_FIELD, _strAccountNum );
      setParameter( HISTORY_PENDING_FIELD, _strHistoryPending );
      setParameter( CALLER, _strCaller );

      rtn = invokeCommand( this, CMD_GUI_RESPTRANSACTIONS, PROC_NO_TYPE, isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
bool RESPTransactionsProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.

   bool bRtn = false;
   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

//******************************************************************************
bool RESPTransactionsProcess::doRefresh( GenericInterface *rpGICaller,
                                         const I_CHAR *szOriginalCommand )
{
   const DString resp_TransListKey = getCurrentListItemKey (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST);

   removeTransactionList (rpGICaller, _strHistoryPending);
   setParameter (I_("RESP_TransListKey"), resp_TransListKey);

   return AbstractProcess::doRefresh (rpGICaller, szOriginalCommand);
}

//******************************************************************************
bool RESPTransactionsProcess::doModelessChildComplete( const Command &cmd )
{
   return cmd.getKey() == CMD_GUI_RESPTRANSACTIONS;
}

//******************************************************************************
bool RESPTransactionsProcess::doMoreRecordsExist( GenericInterface *rpGICaller, 
                                                  const BFContainerId& idContainer)
{
   return _pRESPTransactionsList && _pRESPTransactionsList->doMoreRecordsExist();
}

//******************************************************************************
SEVERITY RESPTransactionsProcess::performSearch ( GenericInterface *rpGI, 
                                                  const BFContainerId& idSearch, 
                                                  E_SEARCHACTION searchAction )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));

   try
   {
      if (SEARCH_NEXT_BLOCK == searchAction)
      {
         if (_pRESPTransactionsList)
         {
            _pRESPTransactionsList->getMore();
            //setContainer (IFASTBP_PROC::RESPTRANSACTIONS_LIST, NULL);
         }
      }
      else if (SEARCH_START == searchAction)
      {
         setContainer (IFASTBP_PROC::RESPTRANSACTIONS_LIST, NULL);
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch ( ... )
   {
      throw EXCEPTIONFROMFILE (CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void *RESPTransactionsProcess::getPtrForContainer ( const BFContainerId& idContainer,
                                                    const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::RESP_CRITERIA == idContainer)
      {
         RESPTradeSearchCriteria* pRESPTradeSearchCriteria = NULL;
         MFAccount* pMFAccount (NULL);

         if ( pDSTCWorkSession->getMFAccount (idDataGroup, _strAccountNum, pMFAccount) <= WARNING &&
              pMFAccount)
         {
            if ( pMFAccount->getRESPTradeSearchCriteria (pRESPTradeSearchCriteria, 
                                                         _strTransId,
                                                         _strTradeDate,
                                                         _strHistoryPending,
                                                         idDataGroup) <= WARNING && pRESPTradeSearchCriteria )
            {
               ptr = pRESPTradeSearchCriteria;
            }
         }
      }
      else if (IFASTBP_PROC::RESPTRANSACTIONS_LIST == idContainer)
      {
         // call this from RESPCriteria:
         RESPTradeSearchCriteria* pRESPTradeSearchCriteria = dynamic_cast<RESPTradeSearchCriteria*>(
            getCBOItem (IFASTBP_PROC::RESP_CRITERIA, idDataGroup));

         _pRESPTransactionsList = NULL;
         if (pRESPTradeSearchCriteria->getRESPTransactionsList (_pRESPTransactionsList,
                                                                _strAccountNum,
                                                                _strHistoryPending, 
                                                                _strTransId, 
                                                                idDataGroup) <= WARNING)
         {
            ptr = _pRESPTransactionsList;
         }
      }
   }
   catch (ConditionException &)
   {
      throw;
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return ptr;
}

//******************************************************************************
void RESPTransactionsProcess::doPostOk ( GenericInterface *rpGICaller,
                                         bool bSuccessFlag)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));
}

//******************************************************************************
SEVERITY RESPTransactionsProcess::removeTransactionList (GenericInterface *rpGICaller, 
                                                         const DString& historyPending)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("removeTransactionList"));

   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   MFAccount* pMFAccount(NULL);
   if ( pDSTCWorkSession->getMFAccount (getDataGroupId(), _strAccountNum, pMFAccount) <= WARNING &&
         pMFAccount)
   {
      BFObjIter iter (*pMFAccount, getDataGroupId());

      iter.positionByKey (I_("RESPTransactionsList") + historyPending);
      if (!iter.end ())
      {
         iter.removeObjectFromMap (true);
      }
   }
   setContainer (IFASTBP_PROC::RESPTRANSACTIONS_LIST, NULL);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RESPTransactionsProcess.cpp-arc  $
 * 
 *    Rev 1.30   Jun 28 2011 09:52:28   panatcha
 * P0184541_FN01_InvescoQESItrans
 * 
 *    Rev 1.29   Nov 10 2010 04:10:56   dchatcha
 * PET0165541 FN03 - QESI Phase3 - Removed not necessary pieces of code and synch up code change from R101.
 * 
 *    Rev 1.28   Oct 29 2010 06:28:40   kitticha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.27   Sep 24 2010 14:25:54   jankovii
 * PET0175377 FN01 - AIP for Joint RESP Account
 * 
 *    Rev 1.26   Sep 15 2010 13:49:34   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.25   Aug 16 2010 15:52:08   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.24   Aug 11 2010 19:43:58   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.23   Aug 09 2010 16:12:56   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.22   Aug 06 2010 14:00:08   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.21   Jun 09 2010 15:10:22   jankovii
 * IN 2131626 - PETP0165541 -  Mapping Issues on the RESP Trans History Screen.
 * 
 *    Rev 1.20   Jun 08 2010 11:28:58   jankovii
 * IN 2141202 - PET0165541-"To Beneficiary" fileld  display issue on Pending view.
 * 
 *    Rev 1.19   May 13 2010 01:31:24   popescu
 * RESP-QESI fixes
 * 
 *    Rev 1.18   May 12 2010 06:10:16   popescu
 * RESP/QESI - fixed description of Grant Repayment Reason 
 * 
 *    Rev 1.17   May 11 2010 08:19:00   popescu
 * QESI - RESP Fixes
 * 
 *    Rev 1.16   May 03 2010 19:40:26   popescu
 * PET165541_FN01_QESI - RESP Gap - small fixes
 * 
 *    Rev 1.15   Apr 09 2010 14:43:54   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - RESP Trading History Dialog - fixed refresh issue when updating allocations
 * 
 *    Rev 1.14   Apr 01 2010 16:23:32   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - RESP Trading History Dialog
 * 
 *    Rev 1.13   Apr 01 2010 00:46:54   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - RESP Trading History Dialog
 * 
 *    Rev 1.12   Mar 31 2010 15:16:42   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.11   25 Nov 2008 16:39:10   popescu
 * Incident  1496411 - fixed the more button in the RESP screen
 * 
 *    Rev 1.10   Jul 25 2008 18:34:52   daechach
 * in#1089944 - iFast/Desktop RESP Transaction History Screen
 * 
 *    Rev 1.9   Mar 21 2003 17:47:24   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:53:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 16:45:12   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.6   22 May 2002 18:25:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   27 Mar 2002 19:55:38   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.4   Jun 07 2001 11:11:50   YINGBAOL
 * fix refresh issue
 * 
 *    Rev 1.3   03 May 2001 14:05:38   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   15 Dec 2000 12:43:48   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.1   Mar 22 2000 09:02:46   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.3   Mar 02 2000 12:00:06   PETOLESC
// Corrected qa issues.
// 
//    Rev 1.2   Feb 16 2000 10:06:48   PETOLESC
// Included the list in MFAccount.
// 
//    Rev 1.1   Feb 07 2000 11:02:20   PETOLESC
// Minor corrections and code cleaning.
 * 
 *
 */
