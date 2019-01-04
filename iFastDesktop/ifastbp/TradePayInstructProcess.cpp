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
//    Copyright 1997 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TradePayInstructProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2006
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TradePayInstructProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "tradepayinstructprocess.hpp"
#include "tradepayinstructprocessincludes.h"
#include "mfcaninterprocparam.hpp"

#include <ifastcbo\lighttrade.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\pendingtradebankinstructionslist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\tradepayinstruct.hpp>
#include <ifastcbo\tradepayinstructlist.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\transactiondetailsbankinstructionslist.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRADE_PAYMENT_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRADE_PAYMENT_INSTRUCTIONS;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TradePayInstructProcess > processCreator (CMD_BPROC_TRADE_PAYMENT_INSTRUCTIONS);

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "TradePayInstructProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
}

namespace MFCAN_IP_PARAM
{
   extern const I_CHAR * const CALLER;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
TradePayInstructProcess::TradePayInstructProcess ( GenericInterfaceContainer* pGIC, 
                                                   GenericInterface* pGIParent, 
                                                   const Command& rCommand ) : 
AbstractProcess (pGIC, pGIParent, rCommand),
_rpChildGI (NULL),
_pTradePayInstructList (NULL),
_pDummyTrade (NULL),
_pMFAccount (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   
   addContainer ( IFASTBP_PROC::TRADE, 
                  false,  //non-repeatable
                  BF::NullContainerId,
                  false,  //non-updatable
                  I_("Trade"));
   addContainer ( BANK, 
                  false,  //non-repeatable
                  BF::NullContainerId,
                  false,  //non-updatable
                  I_("Bank"));
   addContainer ( IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
                  true, 
                  IFASTBP_PROC::TRADE, 
                  true, 
                  I_("TradePayInstructList"));
   //the pending trade container
   addContainer ( IFASTBP_PROC::PENDING_DETAILS, 
                  false, //non-repeatable
                  BF::NullContainerId,
                  false,  //non-updatable
                  I_("PendingDetails"));
   //the transaction history container
   addContainer ( IFASTBP_PROC::TRANSACTION_DETAILS, 
                  false,  //non-repeatable
                  BF::NullContainerId,
                  false,  //non-updatable
                  I_("TransactionDetails"));
	
   addFieldDetails ( ifds::AllocPercent,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::PaymentFor,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::PayType,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::PayMethod,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::ConsolType,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::ACHProcessor,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::AddrLine1, 
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::AddrLine2, 
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::AddrLine3, 
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::AddrLine4, 
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::AddrLine5, 
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);   
   addFieldDetails ( ifds::PostalCode,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::CountryCode,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::UseEntityAddress,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::Currency,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::ProcessDate,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::Username,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::ModDate, 
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::ModUser,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);

   addFieldDetails ( ifds::InstName,
                     BANK);
   addFieldDetails ( ifds::BankIdValue,
                     BANK);
   addFieldDetails ( ifds::BankAcctName,
                     BANK);
   addFieldDetails ( ifds::BankAcctNum,
                     BANK);
   addFieldDetails ( ifds::Broker,
                     IFASTBP_PROC::TRADE);
   addFieldDetails ( ifds::Branch,
                     IFASTBP_PROC::TRADE);
   addFieldDetails ( ifds::SlsrepCode,
                     IFASTBP_PROC::TRADE);
   addFieldDetails ( ifds::AccountNum,
                     IFASTBP_PROC::TRADE);
   addFieldDetails ( EnableBanking,
                     IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, SUBCLASS_PROCESS);
}

//******************************************************************************
TradePayInstructProcess::~TradePayInstructProcess()
{
   TRACE_DESTRUCTOR (CLASSNAME);
   if ((_caller == I_("Transaction") || _caller == I_("PendingTransaction")) && _pTradePayInstructList)
   {
      delete _pTradePayInstructList;
      _pTradePayInstructList = NULL;
   }
   if (_pDummyTrade)
   {
      delete _pDummyTrade;
      _pDummyTrade = NULL;
   }
   _rpChildGI = NULL;
}

//******************************************************************************
void TradePayInstructProcess::doGetField( const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId& idField,
                                          const BFDataGroupId& idDataGroup,
                                          DString &strValueOut,
                                          bool bFormatted ) const
{  
   strValueOut = NULL_STRING;
   
   if (idField == EnableBanking)
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();
      //get the current PaymentInstructions object
      TradePayInstruct *pTradePayInstruct = 
         dynamic_cast<TradePayInstruct*>
         (const_cast <TradePayInstructProcess*>(this)->
         getCBOItem(IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, idDataGroup));

      strValueOut = pTradePayInstruct && pTradePayInstruct->isBankingAllowed (idDataGroup) ? I_("Y") : I_("N");
   }
}

//******************************************************************************
SEVERITY TradePayInstructProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
      BFDataGroupId idDataGroup = getDataGroupId();

      getParameter (MFCAN_IP_PARAM::CALLER, _caller);
      getParameter (MFCAN_IP_PARAM::TRANS_NUM, _transNum);
      getParameter (MFCAN_IP_PARAM::LIST_KEY, _listKey);
      getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);
      if (!_accountNum.empty ())
      {
//retrieve the mf account pointer
         if ( pDSTCWorkSession->getMFAccount ( idDataGroup, 
                                               _accountNum, 
                                               _pMFAccount, 
                                               I_ ("N"), 
                                               NULL_STRING, 
                                               true, 
                                               true) <= WARNING && 
              _pMFAccount)
         {
            ;//perhaps do something in the future...if exists...
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE (CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN TradePayInstructProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (MFCAN_IP_PARAM::CALLER, _caller);
      setParameter (MFCAN_IP_PARAM::TRANS_NUM, _transNum);
      setParameter (MFCAN_IP_PARAM::LIST_KEY, _listKey);
      rtn = invokeCommand ( this, 
                            CMD_GUI_TRADE_PAYMENT_INSTRUCTIONS, 
                            PROC_NO_TYPE, 
                            isModal(), 
                            &_rpChildGI);
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE (CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
SEVERITY TradePayInstructProcess::doSetField ( const GenericInterface *rpGICaller,
                                               const BFContainerId& idContainer,
                                               const BFFieldId& idField,
                                               const BFDataGroupId& idDataGroup,
                                               const DString& strValue,
                                               bool bFormatted)
{  
   return NO_CONDITION;
}

//******************************************************************************
void *TradePayInstructProcess::getPtrForContainer ( const BFContainerId& idContainer, 
                                                    const BFDataGroupId& idDataGroup)
{
   void *ptr = NULL;
   
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   assert (pDSTCWorkSession);

   if (pDSTCWorkSession)
   {
      try
      {
         if (idContainer == IFASTBP_PROC::TRADE)
         {
            if (_caller == I_("TradeEntry"))
            {
               if (!_listKey.empty())
               {
                  WorksessionTradesList *pTradesList = NULL;

                  if ( pDSTCWorkSession->getTradesList (pTradesList, getDataGroupId()) <= WARNING && 
                       pTradesList)
                  {
	                  BFObjIter iter ( *pTradesList, 
                                       getDataGroupId(), 
                                       false, 
                                       BFObjIter::ITERTYPE::NON_DELETED);
                  	
	                  iter.positionByKey (_listKey);
	                  if (!iter.end())
	                  {
		                  Trade* pTrade = dynamic_cast <Trade*>(iter.getObject());

                        if (pTrade)
                        {
                           ptr = pTrade;
                        }
                     }
                  }
               }
            }
            else 
            {
               if (!_pDummyTrade)
               {
                  _pDummyTrade = new LightTrade (*pDSTCWorkSession);
               }
               ptr = _pDummyTrade;
            }
         }
         else if (IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST == idContainer)
         {
            if (_caller == I_("TradeEntry"))
            {
               Trade *pTrade = 
                  dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADE, 
                                                      idDataGroup));
               if ( pTrade &&
                    pTrade->getTradePayInstructList (_pTradePayInstructList, getDataGroupId()) <= WARNING &&
                    _pTradePayInstructList)
               {
                  ptr = _pTradePayInstructList;
               }
            }
            else if (_caller == I_("Transaction") || _caller == I_("PendingTransaction"))
            {
               if (_pTradePayInstructList)
               {
                  delete _pTradePayInstructList;
                  _pTradePayInstructList = NULL;
               }
               _pTradePayInstructList = new TradePayInstructList (*pDSTCWorkSession);
               if (_pTradePayInstructList->init (NULL_STRING, _transNum, getDataGroupId (), true) <= WARNING)
               {
                  ptr = _pTradePayInstructList;
               }
            }
         }
         else if (idContainer == BANK)
         {
            if (_caller == I_("TradeEntry"))
            {
               Trade *pTrade = 
                  dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADE, 
                                                      idDataGroup));
               ptr = pTrade;
            }
            else if (_caller == I_("Transaction"))
            {
               TransactionDetails *rpTransactionDetails = 
                  dynamic_cast<TransactionDetails*> ( getCBOItem ( IFASTBP_PROC::TRANSACTION_DETAILS, 
                                                                  idDataGroup));

               if (rpTransactionDetails)
               {
                  TransactionDetailsBankInstructionsList 
                     *pTransactionDetailsBankInstructionsList = NULL;

                  if ( rpTransactionDetails->
                           getBankInstructionsList ( pTransactionDetailsBankInstructionsList, 
                                                     idDataGroup) <= WARNING &&
                       pTransactionDetailsBankInstructionsList)
                  {
                     BFObjIter iter ( *pTransactionDetailsBankInstructionsList, 
                                       idDataGroup, 
                                       false, 
                                       BFObjIter::ITERTYPE::NON_DELETED);
                     if (!iter.end())
                     {
                        ptr = iter.getObject();
                     }
                  }
               }
            }
            else if (_caller == I_("PendingTransaction"))
            {
               PendingTradeDetails *rpPendingTradeDetails = 
                  dynamic_cast <PendingTradeDetails*> (getCBOItem (IFASTBP_PROC::PENDING_DETAILS, idDataGroup));

               if (rpPendingTradeDetails)
               {
                  PendingTradeBankInstructionsList 
                     *pPendingTradeBankInstructionsList = NULL;

                  if ( rpPendingTradeDetails->
                        getBankInstructionsList ( pPendingTradeBankInstructionsList, 
                                                  idDataGroup) <= WARNING &&
                       pPendingTradeBankInstructionsList)
                  {
                     BFObjIter iter ( *pPendingTradeBankInstructionsList, 
                                       idDataGroup, 
                                       false, 
                                       BFObjIter::ITERTYPE::NON_DELETED);
                     if (!iter.end())
                     {
                        ptr = iter.getObject();
                     }
                  }
               }
            }
         }
         else if (IFASTBP_PROC::PENDING_DETAILS == idContainer)
         {
            //get the associated pending trades list
            PendingTradeList *pPendingTradeList = NULL;
            
            if ( _pMFAccount && 
                 _pMFAccount->getPendingTradesList ( pPendingTradeList, 
                                                     idDataGroup) <= WARNING && 
                  pPendingTradeList &&
                  !_listKey.empty())
            {
               BFObjIter iter ( *pPendingTradeList, 
                                idDataGroup, 
                                false, 
                                BFObjIter::ITERTYPE::NON_DELETED);

               iter.positionByKey (_listKey);
               if (!iter.end ())
               {
                  ptr = iter.getObject();
               }
            }
         }
         else if (IFASTBP_PROC::TRANSACTION_DETAILS == idContainer)
         {
            //get the associated pending trades list
            TransactionList *pTransactionList = NULL;
            
            if (_pMFAccount)
            {
               _pMFAccount->getLastActiveTransactionHistoryList ( pTransactionList, 
                                                                  idDataGroup);
               if ( pTransactionList &&
                    !_listKey.empty())
               {
                  BFObjIter iter ( *pTransactionList, 
                                   idDataGroup, 
                                   false, 
                                   BFObjIter::ITERTYPE::NON_DELETED);

                  iter.positionByKey (_listKey);
                  if (!iter.end ())
                  {
                     ptr = iter.getObject();
                  }
               }
            }
         }
      }
      catch (ConditionException &)
      {
         throw;
      }
      catch( ... )
      {
         assert( 0 );
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                         CND::BP_ERR_UNKNOWN_EXCEPTION );
      }
   }
   return ptr;
}

//*****************************************************************************
bool TradePayInstructProcess::doOk (GenericInterface *rpGICaller)
{
   return true;
}

//******************************************************************************
void TradePayInstructProcess::doPostOk ( GenericInterface *rpGICaller, 
                                         bool bSuccessFlag)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));

	if (bSuccessFlag)
   {
      DString payType,
		      payMethod,
            fileProcessor;

      if (_caller == I_("TradeEntry")) 
      {
         //check if only one record, set parameter pay type and paty method
         //if >=2 records, then set accountable and BackDatedReason parameters to be empty.	   
         BFObjIter iter (*_pTradePayInstructList, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED);	   
         int numOfItem = iter.getNumberOfItemsInList();
         
         if (numOfItem == 1)
         {
            iter.getObject()->getField (ifds::PayType, payType, getDataGroupId ());
            iter.getObject()->getField (ifds::PayMethod, payMethod, getDataGroupId ());
            iter.getObject()->getField (ifds::ACHProcessor, fileProcessor, getDataGroupId ());
         }
      }
      setParameter (I_("PayType"), payType);
      setParameter (I_("PayMethod"), payMethod);
      setParameter (I_("ACHProcessor"), fileProcessor);
   }
}

//**********************************************************************
SEVERITY TradePayInstructProcess::doValidateAll( BFAbstractCBO *rpWSD, 
                                                 const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

   if (_pTradePayInstructList)
   {
		_pTradePayInstructList->validateAll (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool TradePayInstructProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return (cmd.getKey() == CMD_GUI_TRADE_PAYMENT_INSTRUCTIONS);
}

//******************************************************************************
bool TradePayInstructProcess::doModelessSetFocus (GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   
   bool bRtn = false; 

   if (isValidModelessInterface (_rpChildGI))
   {  
      getParameter (MFCAN_IP_PARAM::CALLER, _caller);
      getParameter (MFCAN_IP_PARAM::TRANS_NUM, _transNum);
      getParameter (MFCAN_IP_PARAM::LIST_KEY, _listKey);
      getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);
      // Only if child still exists
      if (isValidModelessInterface (_rpChildGI))
      {
         bRtn = _rpChildGI->refresh (this, I_("ReloadParams"));
         bRtn = _rpChildGI->modelessSetFocus (rpGICaller);
      }
   }
   return bRtn;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradePayInstructProcess.cpp-arc  $
// 
//    Rev 1.5   Sep 22 2006 00:46:40   popescu
// STP 2217/13
// 
//    Rev 1.4   Sep 21 2006 01:50:08   popescu
// STP PET 2217/13
// 
//    Rev 1.3   Sep 15 2006 19:43:06   popescu
// STP 2217/13 - fixes
// 
//    Rev 1.2   Sep 10 2006 17:57:56   popescu
// STP 2192/12
// 
//    Rev 1.1   Sep 07 2006 21:37:32   popescu
// STP 2192/02
// 
//    Rev 1.0   Aug 29 2006 18:25:50   popescu
// Initial revision.
// 
 */
