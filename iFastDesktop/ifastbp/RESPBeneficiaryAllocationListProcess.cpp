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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RESPBeneficiaryAllocationListProcess.cpp
// ^AUTHOR : 
// ^DATE   : July, 2009
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RESPBeneficiaryAllocationListProcess
//    This class manages the RESP Beneficiary Allocation List information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "accdetailsprocess.hpp"
#include "accdetailsprocessincludes.h"
#include "respbeneficiaryallocationlistprocessincludes.h"
#include "respbeneficiaryallocationlistprocess.hpp"
#include "respinfoprocessincludes.h"
#include <bfproc\genericinterface.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include <ifastcbo\errmsgruleslist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\respbeneficiaryallocationlist.hpp>
#include <ifastcbo\resptransactionsdetails.hpp>
#include <ifastcbo\resptransactionslist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>



extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_BENEF_ALLOCATION_LIST;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_RESP_BENEF_ALLOCATION_LIST;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACC_DETAILS;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RESPBeneficiaryAllocationListProcess > processCreator(CMD_BPROC_RESP_BENEF_ALLOCATION_LIST);


namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "RESPBeneficiaryAllocationListProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
RESPBeneficiaryAllocationListProcess::RESPBeneficiaryAllocationListProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_Caller (NULL_STRING)
, m_TradeListKey (NULL_STRING)
, m_RESPTransListKey (NULL_STRING)
, m_AccountNum (NULL_STRING)
, m_DecimalDigits (NULL_STRING)
, m_HistoryPending (NULL_STRING)
, m_disableScreen (NULL_STRING)
, m_HRDCPending (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer ( IFASTBP_PROC::TRADE, false, BF::NullContainerId, false, I_("Trade"));
   addContainer ( IFASTBP_PROC::TRANSACTION, false, BF::NullContainerId, false, I_("Transaction"));
   addContainer ( IFASTBP_PROC::PENDING_TRANSACTION, false, BF::NullContainerId, false, I_("PendingTransaction"));
   addContainer ( IFASTBP_PROC::RESP_TRANSACTION, false);
   addContainer ( IFASTBP_PROC::RESP_BENEF_ALLOC_LIST, true, BF::NullContainerId, true, I_("RESPBenefAllocationList"));

   addFieldDetails( ifds::RESPBenefId,       IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::RESPAllocAmt,      IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::RESPAllocPrcnt,    IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::BenefDofB,         IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::HRDCRelateCode,    IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::TaxJuris,          IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::RESPContrDetlVer,  IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::PendGrantExists,   IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::ProcGrantExists,   IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::EffectiveDate,     IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::TransId,           IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::GrantTransNumList, IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::ReAllocated,       IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);
   addFieldDetails( ifds::HRDCReported,       IFASTBP_PROC::RESP_BENEF_ALLOC_LIST); //P0185010.FN03.R03.00 - RESP Beneficiary Re-Allocations
   addFieldDetails( ifds::AllowManualDelete,    IFASTBP_PROC::RESP_BENEF_ALLOC_LIST);

   addFieldDetails( ifds::TradesTransType,   IFASTBP_PROC::TRADE);
   addFieldDetails( ifds::GrossOrNet,        IFASTBP_PROC::TRADE);
   addFieldDetails( ifds::Amount,            IFASTBP_PROC::TRADE);
   addFieldDetails( ifds::DepositType,       IFASTBP_PROC::TRADE);
   addFieldDetails( ifds::AmtType,           IFASTBP_PROC::TRADE);

   addFieldDetails( ifds::TransType,         IFASTBP_PROC::TRANSACTION);
   addFieldDetails( ifds::GrossOrNet,        IFASTBP_PROC::TRANSACTION);
   addFieldDetails( ifds::GrossAmt,          IFASTBP_PROC::TRANSACTION);
   addFieldDetails( ifds::DepositType,       IFASTBP_PROC::TRANSACTION);
   addFieldDetails( ifds::AmtType,           IFASTBP_PROC::TRANSACTION);

   addFieldDetails( ifds::TransType,         IFASTBP_PROC::PENDING_TRANSACTION);
   addFieldDetails( ifds::GrossNetMethod,    IFASTBP_PROC::PENDING_TRANSACTION);
   addFieldDetails( ifds::Amount,            IFASTBP_PROC::PENDING_TRANSACTION);
   addFieldDetails( ifds::DepositType,       IFASTBP_PROC::PENDING_TRANSACTION);
   addFieldDetails( ifds::AmountType,        IFASTBP_PROC::PENDING_TRANSACTION);
   //read the caller in ctor to determine the commit parent
   getParameter (CALLER, m_Caller);
}

//******************************************************************************
RESPBeneficiaryAllocationListProcess::~RESPBeneficiaryAllocationListProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY RESPBeneficiaryAllocationListProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   getParameter (ACCOUNT_NUM, m_AccountNum);
   getParameter (TRADE_LIST_KEY, m_TradeListKey);
   getParameter (RESP_TRANS_LIST_KEY, m_RESPTransListKey);
   getParameter (DECIMAL_DIGITS, m_DecimalDigits);
   getParameter (HISTORY_PENDING_FIELD, m_HistoryPending);
   getParameter (I_("DisableScreen"), m_disableScreen);
   getParameter (TRANSID, m_TransId);
   getParameter (HRDCPending, m_HRDCPending);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPBeneficiaryAllocationListProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_RESP_BENEF_ALLOCATION_LIST);
}

//******************************************************************************
bool RESPBeneficiaryAllocationListProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  
   // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;

   try
   {
      getParameter (CALLER, m_Caller);
      getParameter (ACCOUNT_NUM, m_AccountNum);
      getParameter (TRADE_LIST_KEY, m_TradeListKey);
      getParameter (RESP_TRANS_LIST_KEY, m_RESPTransListKey);
      getParameter (DECIMAL_DIGITS, m_DecimalDigits);
      getParameter (HISTORY_PENDING_FIELD, m_HistoryPending);
      getParameter (I_("DisableScreen"), m_disableScreen);
	  getParameter (HRDCPending, m_HRDCPending);

      setContainer (IFASTBP_PROC::RESP_BENEF_ALLOC_LIST, NULL);

      if (isValidModelessInterface (_rpChildGI))
      {  // Only if child still exists
         bRtn = _rpChildGI->refresh (this, NULL);
      }
      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(bRtn);
}

//******************************************************************************
E_COMMANDRETURN RESPBeneficiaryAllocationListProcess::doProcess()
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   setParameter (CALLER, m_Caller);
   setParameter (DECIMAL_DIGITS, m_DecimalDigits);
   setParameter (HISTORY_PENDING_FIELD, m_HistoryPending);
   setParameter (ACCOUNT_NUM, m_AccountNum);
   setParameter (I_("DisableScreen"), m_disableScreen);
   setParameter (TRANSID, m_TransId);
   setParameter (HRDCPending, m_HRDCPending);

   try
   {
      rtn = invokeCommand( this, CMD_GUI_RESP_BENEF_ALLOCATION_LIST, getProcessType(), isModal(),
         &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
void *RESPBeneficiaryAllocationListProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                                const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::TRADE == idContainer)
      {
         if (m_Caller == I_("TradeEntry"))
         {
            WorksessionTradesList *pTradesList (NULL);

            if( pDSTCWorkSession->getTradesList (pTradesList, idDataGroup) <= WARNING && 
               pTradesList)
            {
               BFObjIter iter (*pTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

               iter.positionByKey (m_TradeListKey);
               if (!iter.end())
               {
                  ptr = dynamic_cast <Trade*>(iter.getObject());
               }
            }
         }
      }
      else if (IFASTBP_PROC::TRANSACTION == idContainer)
      {
         if (m_Caller == I_("RESPTransactionsDlg") && m_HistoryPending == RESPINFONAMES::HISTORY)
         {
            RESPTransactionsDetails *pRESPTransactionsDetails = 
               dynamic_cast <RESPTransactionsDetails*> (getCBOItem (IFASTBP_PROC::RESP_TRANSACTION, idDataGroup));

            if (pRESPTransactionsDetails)
            {
               TransactionDetails *pTransactionDetails = NULL;

               if ( pRESPTransactionsDetails->getTransactionDetails (pTransactionDetails, idDataGroup) &&
                    pTransactionDetails)
               {
                  ptr = pTransactionDetails;
               }
            }
         }
      }
      else if (IFASTBP_PROC::PENDING_TRANSACTION == idContainer)
      {
         if (m_Caller == I_("RESPTransactionsDlg") && m_HistoryPending == RESPINFONAMES::PENDING)
         {
            RESPTransactionsDetails *pRESPTransactionsDetails = 
               dynamic_cast <RESPTransactionsDetails*> (getCBOItem (IFASTBP_PROC::RESP_TRANSACTION, idDataGroup));

            if (pRESPTransactionsDetails)
            {
               PendingTradeDetails *pPendingTradeDetails = NULL;

               if ( pRESPTransactionsDetails->getPendingTransactionDetails (pPendingTradeDetails, idDataGroup) &&
                    pPendingTradeDetails)
               {
                  ptr = pPendingTradeDetails;
               }
            }
         }
      }
      else if (IFASTBP_PROC::RESP_TRANSACTION == idContainer)
      {
         MFAccount *pMFAccount (NULL);

         if ( pDSTCWorkSession ->getMFAccount (idDataGroup, m_AccountNum, pMFAccount) <= WARNING &&
            pMFAccount)
         {
            RESPTransactionsList *pRESPTransactionsList (NULL);

            if (pMFAccount->getRESPTransactionsList (pRESPTransactionsList, m_HistoryPending, getDataGroupId ()) <= WARNING &&
               pRESPTransactionsList)
            {
               BFObjIter iter ( *pRESPTransactionsList,idDataGroup, 
                  false, BFObjIter::ITERTYPE::NON_DELETED);

               iter.positionByKey (m_RESPTransListKey);

               if (!iter.end ())
               {
                  ptr = dynamic_cast <RESPTransactionsDetails *>(iter.getObject());
               }
            }
         }
      }
      else if (IFASTBP_PROC::RESP_BENEF_ALLOC_LIST == idContainer)
      {
         if (m_Caller == I_("TradeEntry"))
         {
            Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

            if (pTrade)
            {
               RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList = NULL;

               if (pTrade->getRESPBenefAllocationList  (pRESPBeneficiaryAllocationList, idDataGroup) <= WARNING &&
                  pRESPBeneficiaryAllocationList)
               {
                  ptr = pRESPBeneficiaryAllocationList;
               }
            }
         }
         else if (m_Caller == I_("RESPTransactionsDlg"))
         {
            RESPTransactionsDetails *pRESPTransactionsDetails = 
               dynamic_cast <RESPTransactionsDetails*> (getCBOItem (IFASTBP_PROC::RESP_TRANSACTION, idDataGroup));

            if (pRESPTransactionsDetails != NULL)
            {
               RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList = NULL;

               DString tradeType = m_HistoryPending == RESPINFONAMES::HISTORY ? I_("Proc") : I_("Pend");
               if ( pRESPTransactionsDetails->getRESPBenefAllocationList  (pRESPBeneficiaryAllocationList, idDataGroup, tradeType) <= WARNING &&
                  pRESPBeneficiaryAllocationList)
               {
                  ptr = pRESPBeneficiaryAllocationList;
               }
            }
         }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(ptr);
}
//******************************************************************************
bool RESPBeneficiaryAllocationListProcess::doOk (GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );

   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocationListProcess::doValidateAll ( BFAbstractCBO *rpWSD, 
                                                               const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, DOVALIDATEALL);

   RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList = 
      dynamic_cast <RESPBeneficiaryAllocationList *> (getCBOList (IFASTBP_PROC::RESP_BENEF_ALLOC_LIST, idDataGroup));

   if (pRESPBeneficiaryAllocationList)
   {
	   pRESPBeneficiaryAllocationList->setField(ifds::HRDCPending, m_HRDCPending, idDataGroup, false);
	   pRESPBeneficiaryAllocationList->validateAll (idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPBeneficiaryAllocationListProcess::setCommitDataGroupAsHost()
{
   return m_Caller == I_("RESPTransactionsDlg");
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RESPBeneficiaryAllocationListProcess.cpp-arc  $
// 
//    Rev 1.16   Oct 06 2011 10:21:32   panatcha
// P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
// 
//    Rev 1.15   Nov 10 2010 04:02:50   dchatcha
// PET0165541 FN03 - QESI Phase3 - Removed not necessary pieces of code.
// 
//    Rev 1.14   Oct 29 2010 06:27:02   kitticha
// PET0165541 FN03 - QESI Phase3.
// 
//    Rev 1.13   Oct 27 2010 10:22:14   jankovii
// IN 2305655 - FN03 QESI - RESP Beneficiary Allocation History Button
// 
//    Rev 1.12   Sep 15 2010 13:52:18   jankovii
// PET165541 FN03 SOC14 & SOC6
// 
//    Rev 1.11   Aug 06 2010 13:55:44   jankovii
// PET165541 FN03 SOC14 & SOC6
// 
//    Rev 1.10   Jun 21 2010 17:19:40   popescu
// Incident 2162449 - REL Pre99 Bene Alloc button grayed out on RESP Transaction History Screen
// 
//    Rev 1.9   Jun 09 2010 15:30:48   jankovii
// IN 2143804 - QESI - #165541 - RESP TRansaction History
// 
//    Rev 1.8   May 13 2010 01:31:14   popescu
// RESP-QESI fixes
// 
//    Rev 1.7   Apr 23 2010 18:50:34   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading - fixed RESP Transfer fixed session 115 
// 
//    Rev 1.6   Mar 31 2010 00:54:00   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading - bene allocation updates
// 
//    Rev 1.5   Mar 31 2010 00:24:04   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading - bene allocation updates
// 
//    Rev 1.4   Mar 30 2010 16:31:26   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.3   Mar 29 2010 23:05:50   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.15   Mar 29 2010 10:49:40   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
*/