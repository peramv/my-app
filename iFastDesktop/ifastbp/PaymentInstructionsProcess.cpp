//******************************************************************************
//
// COPYRIGHT:
//
//    Th* comput;
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : PaymentInstructionsProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : PaymentInstructionsProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "paymentinstructionsprocess.hpp"
#include "paymentinstructionsprocessincludes.h"
#include <ifastcbo\bankinstructionslist.hpp>
#include <ifastcbo\distributorbankinstructionslist.hpp>
#include <ifastcbo\distributorrepository.hpp>
#include <ifastcbo\paymentinstructions.hpp>
#include <ifastcbo\paymentinstructionslist.hpp>
#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_PAYMENT_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PAYMENT_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< PaymentInstructionsProcess > processCreator(CMD_BPROC_PAYMENT_INSTRUCTIONS);

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("PaymentInstructionsProcess");
   const I_CHAR * const YES = I_("Y");
   const I_CHAR * const NO = I_("N");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const PYIN;
}

namespace PAY_TO
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
}

namespace ifds
{
   //field ids used   
   extern CLASS_IMPORT const BFTextFieldId HasNegativeComm;  
	extern CLASS_IMPORT const BFTextFieldId ClientName;
}



//******************************************************************************
//              Public Methods
//******************************************************************************

PaymentInstructionsProcess::PaymentInstructionsProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand),
_rpChildGI(NULL),
_dstrBrokerCode(NULL_STRING),
_dstrBranchCode(NULL_STRING),
_dstrSlsRepCode(NULL_STRING),
_dstrPayToEntity(NULL_STRING),
_dstrPaymentFor(NULL_STRING),
_dstrSearchTypeMgmt(NULL_STRING),
_pPaymentInstructionsList(NULL),
_pBankInstructionsList(NULL),
_pDummyBankInstructionsList(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   //payment instructions list
   addContainer ( IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
                  true, 
                  BF::NullContainerId, 
                  true, 
                  I_("PaymentInstructionsList"));
   addFieldDetails (ifds::PayToEntity,    IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BrokerCode,     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BrokerName,     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BranchCode,     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BranchName,     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::SalesRepCode,   IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::SalesRepName,   IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::PaymentFor,     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::DirectTo,       IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::DirectToShrGrp, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::PayType,        IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::PayMethod,      IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::AccountNum,     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::CurrencyOption, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::Currency,       IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::ACHProcessor,   IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankChrgs,      IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::UseEntityAddress, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::AddrLine1,      IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::AddrLine2,      IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::AddrLine3,      IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::AddrLine4,      IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::AddrLine5,      IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::PostalCode,     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::CountryCode,    IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::ProcessDate,    IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::Username,       IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::ModDate,        IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::ModUser,        IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::PayInstructionsId, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
	addFieldDetails (ifds::CompanyCode,    IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
	addFieldDetails (ifds::ConsolType,     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
	addFieldDetails (ifds::PaymentIdMethod,IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
	addFieldDetails (ifds::EffectiveDate,  IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::StopDate,       IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::SuppressionReasonCode, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
   addFieldDetails ( EnableBanking, 
                     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST,
                     SUBCLASS_PROCESS);
   addFieldDetails ( ReloadBankList, 
                     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST,
                     SUBCLASS_PROCESS);   
   addFieldDetails ( OnlyBankListIsUpdated, 
                     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST,
                     SUBCLASS_PROCESS);   
   addFieldDetails ( RemoveBanks, 
                     IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST,
                     SUBCLASS_PROCESS);   
   addFieldDetails( ifds::HasNegativeComm, 
                    IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST,
                    SUBCLASS_PROCESS );
	addFieldDetails( ifds::ClientName, 
                    IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST,
                    SUBCLASS_PROCESS );
   addFieldDetails( HAS_NON_RECORDS, 
                    IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
                    SUBCLASS_PROCESS );


   //bank instructions list
   addContainer ( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                  true, 
                  IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
                  false, 
                  I_("BankInstructionsList"));
   addFieldDetails (ifds::BankIdValue, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::InstName, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAcctNum, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankIdType, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::AcctUseCode, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAcctCurrency, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::Status, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::EffectiveDate, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::StopDate, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::VerifyStat, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
}

//******************************************************************************
PaymentInstructionsProcess::~PaymentInstructionsProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;
   if (_pDummyBankInstructionsList)
   {
      delete _pDummyBankInstructionsList;
      _pDummyBankInstructionsList = NULL;
   }
}

//************************************************************************************
SEVERITY PaymentInstructionsProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      processParameters();
   }
   catch(ConditionException& ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN PaymentInstructionsProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, _dstrBrokerCode);
      setParameter(MFCAN_IP_PARAM::BRANCH_CODE, _dstrBranchCode);
      setParameter(MFCAN_IP_PARAM::SALES_REP_CODE, _dstrSlsRepCode);
		setParameter(MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, _dstrSearchTypeMgmt);
      setParameter(I_("PaymentFor"), _dstrPaymentFor);
      setParameter(I_("PayToEntity"), _dstrPayToEntity);
      rtn = invokeCommand ( this, 
                           CMD_GUI_PAYMENT_INSTRUCTIONS, 
                           PROC_NO_TYPE, 
                           isModal(), 
                           &_rpChildGI);
   }
   catch(ConditionException &ce)
   {
      assert(0);
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************
void PaymentInstructionsProcess::doGetField( const GenericInterface *rpGICaller,
                                             const BFContainerId& idContainer, 
                                             const BFFieldId& idField,
                                             const BFDataGroupId& idDataGroup, 
                                             DString &strValueOut,
                                             bool bFormatted) const
{
   strValueOut = NULL_STRING;
   if (idField == EnableBanking)
   {
      strValueOut = isBankingAllowed() ? I_("Y") : I_("N");
   }
   else if (idField == OnlyBankListIsUpdated)
   {
      strValueOut = _pBankInstructionsList && 
         _pBankInstructionsList->hasNonHostUpdates() &&
         _pPaymentInstructionsList && 
         !_pPaymentInstructionsList->hasNonHostUpdates() ?
         I_("Y") : I_("N");
   }
   else if (idField == RemoveBanks)
   {
      //get the current PaymentInstructions object
      PaymentInstructions *pPaymentInstructions = 
         dynamic_cast<PaymentInstructions*>(
         const_cast <PaymentInstructionsProcess*>(this)->
         getCBOItem(IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, idDataGroup));

      strValueOut = pPaymentInstructions && 
         pPaymentInstructions->isSuppressAllowed(idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == HAS_NON_RECORDS)
   {
      strValueOut = YES;
      BFObjIter iter(*_pPaymentInstructionsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
	  if( _dstrPaymentFor != NULL_STRING )
	  {
		  iter.setDataFilter( asString (ifds::PaymentFor.getId() ) + I_("=") + _dstrPaymentFor );
	  }
	  
      while( !iter.end() )
      {
         if( !iter.isDummy() )
         {
            strValueOut = NO;
            break;
         }
         ++iter;
      }      
   }   
   else if ( idField == ifds::HasNegativeComm )
   {
		//get the current PaymentInstructions object
      PaymentInstructions *pPaymentInstructions = 
         dynamic_cast<PaymentInstructions*>(
         const_cast <PaymentInstructionsProcess*>(this)->
         getCBOItem(IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, idDataGroup));

      strValueOut = pPaymentInstructions && 
		  pPaymentInstructions->hasAgencyNegCommission( idDataGroup )? 
         I_("Y") : I_("N");
   }
	else if (idField == ifds::ClientName)
   {
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption (ifds::ClientName, strValueOut, idDataGroup);     
   }
}

//******************************************************************************
SEVERITY PaymentInstructionsProcess::doSetField ( const GenericInterface *rpGICaller,
                                                  const BFContainerId& idContainer, 
                                                  const BFFieldId& idField,
                                                  const BFDataGroupId& idDataGroup, 
                                                  const DString& strValue,
                                                  bool bFormatted)
{  
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD);

   if (idField == ReloadBankList)
   {
      //reset the container, to pick up new items
      //do not care about the value, yet
      setContainer(IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, NULL);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructionsProcess::doValidateAll ( BFAbstractCBO *rpWSD,
                                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

   if (_pPaymentInstructionsList)
   {
      _pPaymentInstructionsList->validateAll(idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PaymentInstructionsProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
      if (processParameters() <= WARNING)
      {
         if (isValidModelessInterface(_rpChildGI))
         {  // Only if child still exists
            setContainer(IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, NULL);
            setParameter(MFCAN_IP_PARAM::BROKER_CODE, _dstrBrokerCode);
            setParameter(MFCAN_IP_PARAM::BRANCH_CODE, _dstrBranchCode);
            setParameter(MFCAN_IP_PARAM::SALES_REP_CODE, _dstrSlsRepCode);
				setParameter(MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, _dstrSearchTypeMgmt);
            setParameter(I_("PaymentFor"), _dstrPaymentFor);
            setParameter(I_("PayToEntity"), _dstrPayToEntity);
            bRtn = _rpChildGI->refresh(this, I_("ReloadParams"));
            bRtn = _rpChildGI->modelessSetFocus(rpGICaller);
         }
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return bRtn;
}

//******************************************************************************
bool PaymentInstructionsProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_PAYMENT_INSTRUCTIONS;
}

//******************************************************************************
SEVERITY PaymentInstructionsProcess::performSearch(GenericInterface *rpGI, 
   const BFContainerId &idSearch, E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));

   try
   {
      if (_pPaymentInstructionsList != NULL)
      {
         _pPaymentInstructionsList->getMore();
      }
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, 
         I_("performSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PaymentInstructionsProcess::doMoreRecordsExist ( GenericInterface *rpGICaller,
                                                      const BFContainerId &idSearch)
{
   return (rpGICaller == NULL || _pPaymentInstructionsList == NULL) ? false : 
      _pPaymentInstructionsList->doMoreRecordsExist();
}

//******************************************************************************
void *PaymentInstructionsProcess::getPtrForContainer ( const BFContainerId& idContainer,
                                                       const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   void *ptr = NULL;
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   DistributorRepository *pDistributorRepository = NULL;

   try
   {
      if ( pDSTCWorkSession->getDistributorRepository (pDistributorRepository) <= WARNING && 
           pDistributorRepository)
      {
         if (IFASTBP_PROC::BANK_INSTRUCTIONS_LIST == idContainer)
         {
            //the payment instructions list is not empty;
            //this hack is due to the fact that getCBOItem method, throws an
            //exception, instead of returning null
            if (isPaymentInstructionsListNotEmptyAfterFiltering ())
            {                  
               //get the current PaymentInstructions object
               PaymentInstructionsProcess *pPIP = 
                  dynamic_cast<PaymentInstructionsProcess*>(const_cast <PaymentInstructionsProcess*>(this));
               PaymentInstructions *pPI = 
                  dynamic_cast <PaymentInstructions*>(pPIP->getCBOItem (IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, idDataGroup));
               if (pPI && pPI->getBankInstructionsList (_pBankInstructionsList, idDataGroup) <= WARNING)
               {
                  ptr = _pBankInstructionsList;
               }
            }
            else
            {
               if (!_pDummyBankInstructionsList)
               {
                  _pDummyBankInstructionsList = 
                     new BankInstructionsList (*pDSTCWorkSession);
               }
               ptr = _pDummyBankInstructionsList;
            }
         }
         else if (IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST == idContainer)
         {
            if (pDistributorRepository->getPaymentInstructionsList( _dstrBrokerCode, 
                                                                    _dstrBranchCode, 
                                                                    _dstrSlsRepCode, 
                                                                    _dstrPaymentFor,
					                                                     _dstrSearchTypeMgmt,
                                                                    _pPaymentInstructionsList, idDataGroup) <= WARNING)
            {
               _pPaymentInstructionsList->setField ( ifds::PayToEntity, 
                                                     _dstrPayToEntity, 
                                                     idDataGroup, 
                                                     false, 
                                                     true);
               ptr = _pPaymentInstructionsList;
            }
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
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return ptr;
}

//******************************************************************************
SEVERITY PaymentInstructionsProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   _dstrBrokerCode = _dstrBranchCode = _dstrSlsRepCode = 
      _dstrPayToEntity = _dstrPaymentFor = _dstrSearchTypeMgmt = NULL_STRING;
   getParameter(MFCAN_IP_PARAM::BROKER_CODE, _dstrBrokerCode);
   _dstrBrokerCode.stripAll().upperCase();
   getParameter(MFCAN_IP_PARAM::BRANCH_CODE, _dstrBranchCode);
   _dstrBranchCode.stripAll().upperCase();
   getParameter(MFCAN_IP_PARAM::SALES_REP_CODE, _dstrSlsRepCode);
   _dstrSlsRepCode.stripAll().upperCase();
   getParameter(I_("PayToEntity"), _dstrPayToEntity);
   _dstrPayToEntity.stripAll().upperCase();
   //if 'All' the default should be broker
   if (_dstrPayToEntity == I_("ALL")) 
   {
      _dstrPayToEntity = PAY_TO::BROKER;
   }
   getParameter(I_("PaymentFor"), _dstrPaymentFor);
   _dstrPaymentFor.stripAll().upperCase();

	getParameter(MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, _dstrSearchTypeMgmt);
   _dstrSearchTypeMgmt.stripAll().upperCase();

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PaymentInstructionsProcess::isPaymentInstructionsListNotEmptyAfterFiltering()
{
   bool bNotEmpty = false;
   const BFDataGroupId& idDataGroup = getDataGroupId();
   BFObjIter iter(*_pPaymentInstructionsList, idDataGroup, false, 
      BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end())
   {
      PaymentInstructions *pPaymentInstructions = 
         dynamic_cast<PaymentInstructions*>(iter.getObject());

      if (pPaymentInstructions)
      {
         DString brokerCode, branchCode, salesRepCode, paymentFor;

         pPaymentInstructions->getField(ifds::BrokerCode, brokerCode, 
            idDataGroup, false);
         pPaymentInstructions->getField(ifds::BranchCode, branchCode, 
            idDataGroup, false);
         pPaymentInstructions->getField(ifds::SalesRepCode, salesRepCode, 
            idDataGroup, false);
         pPaymentInstructions->getField(ifds::PaymentFor, paymentFor, 
            idDataGroup, false);
         brokerCode.stripAll().upperCase();
         branchCode.stripAll().upperCase();
         salesRepCode.stripAll().upperCase();
         paymentFor.stripAll().upperCase();
         bNotEmpty |= 
            (_dstrBrokerCode == NULL_STRING || _dstrBrokerCode == brokerCode) &&
            (_dstrBranchCode == NULL_STRING || _dstrBranchCode == branchCode) &&
            (_dstrSlsRepCode == NULL_STRING || _dstrSlsRepCode == salesRepCode) &&
            (_dstrPaymentFor == NULL_STRING || _dstrPaymentFor == paymentFor);
         if (bNotEmpty)
         {
            break;
         }
      }
      ++iter;
   }
   return bNotEmpty;
}

//******************************************************************************
SEVERITY PaymentInstructionsProcess::getHistoricalParameters(
   const BFContainerId& idContainer, BFFieldId &recordIdField, DString& tableId, DString& dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   
   if (idContainer == IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST)
   {
      DString keyStringIDI, dstrPayInstructionsId, dstrBrokerCode;
      recordIdField = ifds::NullFieldId;
      tableId = AUDITTYPE::PYIN;
      getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, ifds::PayInstructionsId, dstrPayInstructionsId, false);
      getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, ifds::BrokerCode, dstrBrokerCode, false);
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode);
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::PAYINSTRUCT_ID, dstrPayInstructionsId);
      dstrKeys = keyStringIDI;
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PaymentInstructionsProcess::isBankingAllowed() const
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("isBankingAllowed"));

   const BFDataGroupId& idDataGroup = getDataGroupId();
   //get the current PaymentInstructions object
   PaymentInstructions *pPaymentInstructions = 
      dynamic_cast<PaymentInstructions*>(const_cast <PaymentInstructionsProcess*>(this)->
      getCBOItem(IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, idDataGroup));

   return pPaymentInstructions &&
      pPaymentInstructions->isBankingAllowed(idDataGroup);
}

//******************************************************************************
SEVERITY PaymentInstructionsProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                              HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PaymentInstructionsProcess.cpp-arc  $
// 
//    Rev 1.30   Nov 25 2009 14:28:24   jankovii
// PET0166583 FN01 Static Data Changes Banking 
// 
//    Rev 1.29   Aug 09 2007 14:01:12   jankovii
// PET 2388 FN01 - Swift Payment Method ID.
// 
//    Rev 1.28   Sep 10 2006 17:57:50   popescu
// STP 2192/12
// 
//    Rev 1.27   Sep 07 2006 21:37:30   popescu
// STP 2192/02
// 
//    Rev 1.26   Aug 28 2006 15:37:48   ZHANGCEL
// PET2212 FN10 -- Added new fields for Netting Bulking Redemption and Distribution Payment
// 
//    Rev 1.25   Jul 27 2006 17:57:14   ZHANGCEL
// PET2192 FN11 - Commission Payments to MgmtCo related changes
// 
//    Rev 1.24   May 31 2006 17:58:00   porteanm
// PET2132 FN03 - Edit check for Negative Commission.
// 
//    Rev 1.23   Jan 25 2006 10:19:18   AGUILAAM
// PET2016_FN05: AXA Office Trailer Fee Indicator
// 
//    Rev 1.22   Oct 19 2005 17:16:24   AGUILAAM
// PET1243_FN00: ABN AMRO Trailer Fee Processing
// 
//    Rev 1.21   Dec 23 2004 16:44:40   Fengyong
// PET1034745 - issue warning when there is no nscc payinstruction but have nscc paytoentity 
// 
//    Rev 1.20   Dec 09 2004 11:49:54   Fengyong
// PET1034745 - Add info box when no payment instruction record was added
// 
//    Rev 1.19   Mar 10 2004 13:18:02   HERNANDO
// PET965 FN11 - Added getHistoricalParameters.
// 
//    Rev 1.18   Feb 18 2004 18:00:48   popescu
// PTS 10027184; - moved the ownership of the payment instructions banking list at the payment instructions CBO level.
// - clean-up the work session every time user hits 'Search' on the Features Search Dialog
// - do not add payment instructions/ pay to entity records, when refreshing the respective CBO lists in DistributorRepository, always read them from back-end. Now, this is possible since the work session is cleaned-up all the time.
// - fixed crash that happens when a new record is added to the payment instructions bank list. The scenario to get this crash is: go to pay to entity screen, then click the 'instructions' button, modify an existing payment instructions record with bank information. Hit okay, commit the changes in the parent. Go back to the payment instructions (you will notice that the previous changes are not saved -  another issue that has been fixed with this ticket), and then click the Bank button. Add a new bank record. Desktop reports an internal error.
// - use new IFDSListCtrl, for the PayToEntity list and PaymentInstructions list.
// 
//    Rev 1.17   Sep 05 2003 10:10:20   popescu
// if the pay to entity param is 'ALL' then set it to Broker...
// synch-up for a fix in 52
// 
//    Rev 1.16   Sep 02 2003 17:58:50   popescu
// filtering should convert fields to uppercase
// 
//    Rev 1.15   Aug 19 2003 15:37:42   HERNANDO
// Uses Broker Code from List Item rather than class member.
// 
//    Rev 1.14   Aug 19 2003 10:42:30   HERNANDO
// Sync'd with 1.12.1.0.
// 
//    Rev 1.13   Aug 19 2003 10:24:14   HERNANDO
// Added keys to getHistoricalParameters.
// 
//    Rev 1.12   Aug 07 2003 12:46:36   popescu
// Removed a duplicate include
// 
//    Rev 1.11   Jul 31 2003 21:58:48   popescu
// Added support for PayType 'X' and support for Historical Info at the process level
// 
//    Rev 1.10   Jul 29 2003 14:19:20   popescu
// Fixes regarding the Discard/Cancel dialog
// 
//    Rev 1.9   Jul 26 2003 21:20:26   popescu
// worked on setting the caption of the payment instructions dialog
// 
//    Rev 1.8   Jul 26 2003 19:38:54   popescu
// the refresh of the banking list didn't work properly in some cases, 
// 
//    Rev 1.7   Jul 25 2003 14:26:00   popescu
// Fix crash in payment instructions dialog, as result of filtering the payment instructions list, cleared the address fields when the checque option is selected for the payment method
// 
//    Rev 1.6   Jul 23 2003 18:20:28   popescu
// Capitalized the parameters
// 
//    Rev 1.5   Jul 11 2003 13:46:38   popescu
// fixes related to the confirmation screen showing up even if there are no changes for the payment instructions screen, added validation for the Currency if BAAF is selected as the file processor
// 
//    Rev 1.4   Jul 10 2003 22:58:50   popescu
// latest changes to pay instruct, filtered correctly the screen, based on the input
// 
//    Rev 1.3   Jul 10 2003 22:19:56   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.2   Jul 09 2003 21:56:32   popescu
// Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
// 
//    Rev 1.1   Jul 02 2003 17:49:30   popescu
// work for payment instructions feature 
// 
//    Rev 1.0   Jul 01 2003 18:12:06   popescu
// Initial revision.
// 
 */
