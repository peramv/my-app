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
// ^FILE   : BankInstructionsProcess.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 02/09/2001
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BankInstructionsProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "bankinstructionsprocess.hpp"
#include "bankinstructionsprocessincludes.h"

#include <ifastcbo\accountdistribution.hpp>
#include <ifastcbo\accountdistributionlist.hpp>
#include <ifastcbo\acctcommitbanklist.hpp>
#include <ifastcbo\acctcommitbank.hpp>
#include <ifastcbo\accountcommitment.hpp>
#include <ifastcbo\agentlist.hpp>
#include <ifastcbo\brokerlist.hpp>
#include <ifastcbo\broker.hpp>
#include <ifastcbo\branchlist.hpp>
#include <ifastcbo\clientbankinstructionslist.hpp>
#include <ifastcbo\directtradingbankinstructionslist.hpp>
#include <ifastcbo\distributorbankinstructionslist.hpp>
#include <ifastcbo\distributorrepository.hpp>
#include <ifastcbo\distributionbankinstructions.hpp>
#include <ifastcbo\distributionbankinstructionslist.hpp>
#include <ifastcbo\fundbankinstructionslist.hpp>
#include <ifastcbo\fundbankinstructionslistrepository.hpp>
#include <ifastcbo\agentbankinstructionslistrepository.hpp>
#include <ifastcbo\fundgroupbankinstructionslist.hpp>
#include <ifastcbo\fundsponsorbankinstructionslist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\fundgroupsublist.hpp>
#include <ifastcbo\fundsponsorslist.hpp>
#include <ifastcbo\matsweepinstrbank.hpp>
#include <ifastcbo\matsweepinstrbanklist.hpp>
#include <ifastcbo\matsweepinstrdetails.hpp>
#include <ifastcbo\matsweepinstrdetailslist.hpp>
#include <ifastcbo\matsweepinstrlist.hpp>
#include <ifastcbo\matsweepinstr.hpp>
#include <ifastcbo\ContractMaturityInstruction.hpp>
#include <ifastcbo\ContractMaturityInstructionList.hpp>
#include <ifastcbo\ContractMatInstrBank.hpp>
#include <ifastcbo\ContractMatInstrBankList.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\rrifbankinstructions.hpp>
#include <ifastcbo\rrifbankinstructionslist.hpp>
#include <ifastcbo\rrif_lif_lrif_info.hpp>
#include <ifastcbo\rrif_lif_lrif_infolist.hpp>
#include <ifastcbo\shareholderbankinstructionslist.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\settlement.hpp>
#include <ifastcbo\settlementtrade.hpp>
#include <ifastcbo\settlementtradelist.hpp>
#include <ifastcbo\settlementtradebankinstructions.hpp>
#include <ifastcbo\settlementtradebankinstructionslist.hpp>
#include <ifastcbo\systematicbankinstructions.hpp>
#include <ifastcbo\systematicbankinstructionsList.hpp>
#include <ifastcbo\systematic.hpp>
#include <ifastcbo\systematiclist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\tradebankinstructions.hpp>
#include <ifastcbo\tradebankinstructionslist.hpp>
#include <ifastcbo\tradepayinstructlist.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>
#include "mfcaninterprocparam.hpp"


#define INCLUDED_ASSERT_H
#include <assert.h>
extern IFASTBP_LINKAGE const I_CHAR *CMD_GUI_BANK_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR *CMD_BPROC_BANK_INSTRUCTIONS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< BankInstructionsProcess > processCreator (CMD_BPROC_BANK_INSTRUCTIONS);

namespace
{
   const I_CHAR *const CLASSNAME             = I_("BankInstructionsProcess");
   const I_CHAR *const USER_ACCESS_CODE      = I_("UserAccessCode");
   const I_CHAR *const DISTRIB_LEVEL         = I_("02");
   const I_CHAR *const DISTRIB_CATEGORY      = I_("2");
   const I_CHAR *const UNVERIFIED            = I_("02");
   const I_CHAR * const SET_FROM_GUI         = I_("SetFromGUI");

}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace CND
{
   extern const long BP_ERR_BROKER_OR_BRANCH_EMPTY;
   extern const long BP_ERR_BROKER_OR_BRANCH_OR_SLSREP_EMPTY;
   extern const long BP_ERR_FUND_EMPTY;
   extern const long BP_ERR_INVALID_FUND;
   extern const long BP_ERR_BROKER_EMPTY;
   extern const long BP_ERR_CLASS_EMPTY;
   extern const long BP_ERR_INVALID_FUND_AND_CLASS;
   extern const long BP_ERR_INVALID_FUND_GROUP;
   extern const long BP_ERR_EMPTY_FUND_GROUP;
   extern const long BP_ERR_INVALID_FUND_SPONSOR;
   extern const long BP_ERR_EMPTY_FUND_SPONSOR;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFDecimalFieldId BankDetlRid; 
   extern CLASS_IMPORT const BFTextFieldId FundGroupDesc;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId PayInstructExists;
   extern CLASS_IMPORT const BFTextFieldId RegAgent;
   extern CLASS_IMPORT const BFTextFieldId PayInstrOption;   
   extern CLASS_IMPORT const BFTextFieldId DefaultBankingLevel;  
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const BKACCT;
   extern CLASS_IMPORT I_CHAR * const SHADISBK;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
BankInstructionsProcess::BankInstructionsProcess (GenericInterfaceContainer *pGIC, 
   GenericInterface *pGIParent, const Command& rCommand)
: AbstractProcess (pGIC, pGIParent, rCommand),
_rpChildGI (NULL),
_pShareholder (NULL),
_pMFAccount (NULL),
_bankInstrType (NULL_STRING),
_accountNum (NULL_STRING),
_shrNum (NULL_STRING),     
_callerListKey (NULL_STRING),
_callerSubListKey (NULL_STRING),
_fundCode (NULL_STRING),
_classCode (NULL_STRING),
_fundGroup (NULL_STRING),
_fundSponsor (NULL_STRING),
_brokerCode (NULL_STRING),
_branchCode (NULL_STRING), 
_salesRepCode (NULL_STRING),
_caller (NULL_STRING),
_systematicListKey (NULL_STRING),
_rrifListKey (NULL_STRING),
_distributionListKey (NULL_STRING),
_matSweepInstrListKey(NULL_STRING),
_acctCommitListKey(NULL_STRING),
_conMatInstrListKey(NULL_STRING),
_conConMatListKey(NULL_STRING),
_dstrCotAcctRid(NULL_STRING),
_dstrContractType(NULL_STRING),
_dstrContractTypeId(NULL_STRING),
_settlementListKey (NULL_STRING),
_tradeListKey (NULL_STRING),
_bankInstructionsListSelectionKey (NULL_STRING),
_distribGBCD (NULL_STRING),
_distribVerifyStat (NULL_STRING),
_payInstructExists (NULL_STRING),
_matSweepInstrType(NULL_STRING),
_matSweepInstrLevel(NULL_STRING),
_matSweepInstrKey(NULL_STRING),
_matSweepInstrDetailsKey(NULL_STRING),
_PrincipalAmount (NULL_STRING),
_AccuredAmount (NULL_STRING),
_payToEntity (NULL_STRING),
_propBankOptionsFieldsHeadingSet (NULL),
_pDummyRRIFBankInstructionsList (NULL),
_pDummySystematicBankInstructionsList (NULL),
_pDummyMatSweepInstrBankList(NULL),
_pDummyContractMatInstrBankList(NULL),
_pDummyAcctCommitBankList(NULL),
_pDummyDistributionBankInstructionsList (NULL),
_pDummySettlementTradeBankInstructionsList (NULL),
_TransNum(NULL),
_TransId(NULL),
_IntInvestId(NULL),
_RegAgent(NULL)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);

   //the RRIF container
   addContainer (IFASTBP_PROC::RRIF_LIF_LRIF, false);
   //the systematic container
   addContainer (IFASTBP_PROC::SYSTEMATIC, false);
   //the account distribution container
   addContainer (IFASTBP_PROC::ACCOUNT_DISTRIBUTION, false);
   //the settlement trade container
   addContainer (IFASTBP_PROC::SETTLEMENT, false);
   //the pending trade container
   addContainer (IFASTBP_PROC::PENDING_DETAILS, false);
   //the transaction history container
   addContainer (IFASTBP_PROC::TRANSACTION_DETAILS, false);
   //the trades list container
   addContainer (IFASTBP_PROC::TRADE, false);
   //the maturity sweep instructions container
   addContainer (IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, false);
   //the account commitment container
   addContainer (IFASTBP_PROC::ACCOUNT_COMMITMENT, false);
   //the contract maturity instructions container
   addContainer (IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, false);
   //the bank instructions list container
   addContainer ( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, true, 
                  BF::NullContainerId, 
                  true, I_("Bank_Instructions"));
   //fields for the bank instructions container
   addFieldDetails ( ifds::BankInstrType, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::TradesTransType, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::PayToEntity, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::BankOptionsHeadingSet, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails ( ifds::BankOptionsFieldsHeadingSet, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::ShrNum, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::Name, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::AccountNum, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::BrokerCode, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::BranchCode, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::SalesRepCode, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::FundCode, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::CloneBankInstructions, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::CallerName, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::IsRRIFAccount, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::SettleCurrency, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::FundGroup, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::FundSponsor, 
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::PayInstructExists,
                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                     SUBCLASS_PROCESS);
   addFieldDetails ( ifds::RegAgent,    
					 IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
					 SUBCLASS_PROCESS);
   addFieldDetails (ifds::PayInstrOption,    
					 IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
					 SUBCLASS_PROCESS);

   addFieldDetails (ifds::TransType, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankIdType, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankIdValue, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::TransitNo, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::InstAddress, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankIdTypeCB, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankIdValueCB, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::TransitNoCB, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::InstNameCB, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::InstAddressCB, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::InstCode, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::SwiftCode, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::RefNumber, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAcctNum, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAcctName, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAcctType, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAcctCurrency, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::EffectiveDate, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::StopDate, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::PayReason1, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::PayReason2, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::AcctUseCode, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::InstName, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAcctVer, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAcctRid, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::Status, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::TemplateNumber, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::ACHProcessor, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::PayMethod, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankPostal, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankCountry, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankContact, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankPostalCB, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankCountryCB, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankContactCB, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::FFC, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::OBIInstructions, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::ModUser, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::ModDate, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::ProcessDate, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::Username, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAddr1, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAddr2, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAddr3, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAddr4, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAddr5, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAddrCB1, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAddrCB2, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAddrCB3, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAddrCB4, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::BankAddrCB5, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::rxShrNumber, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::VerifyStat, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::AcctID, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::TradeExists, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
   addFieldDetails (ifds::rxAcctNum, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);   
   addFieldDetails (ifds::rxBankingEntity, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST); 

   addFieldDetails (ifds::SettleCurrency, IFASTBP_PROC::SETTLEMENT);

   addFieldDetails (ifds::FundCode, IFASTBP_PROC::ACCOUNT_DISTRIBUTION);
   addFieldDetails (ifds::ClassCode, IFASTBP_PROC::ACCOUNT_DISTRIBUTION);
   addFieldDetails (ifds::BankDetlRid, IFASTBP_PROC::ACCOUNT_DISTRIBUTION);
   addFieldDetails (ifds::EffectiveDate, IFASTBP_PROC::ACCOUNT_DISTRIBUTION);
}

//******************************************************************************
BankInstructionsProcess::~BankInstructionsProcess ()
{
   TRACE_DESTRUCTOR (CLASSNAME);

   if (!_propBankOptionsFieldsHeadingSet)
   {
      delete _propBankOptionsFieldsHeadingSet;
      _propBankOptionsFieldsHeadingSet = NULL;
   }
   if (_pDummyRRIFBankInstructionsList)
   {
      delete _pDummyRRIFBankInstructionsList;
      _pDummyRRIFBankInstructionsList = NULL;
   }
   if (_pDummySystematicBankInstructionsList)
   {
      delete _pDummySystematicBankInstructionsList;
      _pDummySystematicBankInstructionsList = NULL;
   }
   if (_pDummyMatSweepInstrBankList)
   {
      delete _pDummyMatSweepInstrBankList;
      _pDummyMatSweepInstrBankList = NULL;
   }

   if(_pDummyContractMatInstrBankList)
   {
      delete _pDummyContractMatInstrBankList;
      _pDummyContractMatInstrBankList = NULL;
   }
   
   if(_pDummyAcctCommitBankList)
   {
      delete _pDummyAcctCommitBankList;
      _pDummyAcctCommitBankList = NULL;
   }

   if (_pDummyDistributionBankInstructionsList)
   {
      delete _pDummyDistributionBankInstructionsList;
      _pDummyDistributionBankInstructionsList = NULL;
   }
   if (_pDummySettlementTradeBankInstructionsList)
   {
      delete _pDummySettlementTradeBankInstructionsList;
      _pDummySettlementTradeBankInstructionsList = NULL;
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY BankInstructionsProcess::doInit ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   getParameter (USER_ACCESS_CODE, m_strUserAccessCode);
   if (processParameters () <= WARNING)
   {
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
      BFDataGroupId idDataGroup = getDataGroupId();
   //we have to process bank inquiries that can return data not found
      if (_bankInstrType == BANKTYPE::PENDING_TRADE)
      {
         PendingTradeDetails *rpPendingTradeDetails = 
            dynamic_cast <PendingTradeDetails*> (getCBOItem ( IFASTBP_PROC::PENDING_DETAILS, idDataGroup));

         if (rpPendingTradeDetails)
         {
            PendingTradeBankInstructionsList 
               *pPendingTradeBankInstructionsList = NULL;

            if ( rpPendingTradeDetails->
                  getBankInstructionsList ( pPendingTradeBankInstructionsList, 
                                             idDataGroup) <= WARNING &&
               pPendingTradeBankInstructionsList)
            {
               setContainer ( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                              pPendingTradeBankInstructionsList);
            }
         }
      }
      else if (_bankInstrType == BANKTYPE::TRANSACTION)
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
               setContainer ( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                              pTransactionDetailsBankInstructionsList);
            }
         }
      }
      else if (_bankInstrType == BANKTYPE::FUND_GROUP)
      {
         FundBankInstructionsListRepository 
            *pFundBankInstructionsListRepository = NULL;
      
         if ( pDSTCWorkSession->
               getFundBankInstructionsListRepository (pFundBankInstructionsListRepository) <= WARNING && 
            pFundBankInstructionsListRepository)
         {
            FundGroupBankInstructionsList 
                  *pFundGroupBankInstructionsList = NULL;

            if ( pFundBankInstructionsListRepository->
                     getFundGroupBankInstructionsList ( _fundGroup, 
                                                      pFundGroupBankInstructionsList, 
                                                      idDataGroup) <= WARNING && 
               pFundGroupBankInstructionsList)
            {  
               setContainer ( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                              pFundGroupBankInstructionsList);
            }
         }
      }
      else if (_bankInstrType == BANKTYPE::FUND_SPONSOR)
      {
         FundBankInstructionsListRepository 
            *pFundBankInstructionsListRepository = NULL;
      
         if ( pDSTCWorkSession->
               getFundBankInstructionsListRepository (pFundBankInstructionsListRepository) <= WARNING && 
            pFundBankInstructionsListRepository)
         {
            FundSponsorBankInstructionsList 
                  *pFundSponsorBankInstructionsList = NULL;

            if ( pFundBankInstructionsListRepository->
                     getFundSponsorBankInstructionsList ( _fundSponsor, 
                                                         pFundSponsorBankInstructionsList, 
                                                         idDataGroup) <= WARNING && 
               pFundSponsorBankInstructionsList)
            {  
               setContainer ( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                              pFundSponsorBankInstructionsList);
            }
         }
      }
	  else if (_bankInstrType == BANKTYPE::REG_AGENT)
	  {	 
		  AgentBankInstructionsListRepository 
			  *pAgentBankInstructionsListRepository = NULL;

		  if ( pDSTCWorkSession->
			  getAgentBankInstructionsListRepository (pAgentBankInstructionsListRepository) <= WARNING && 
			  pAgentBankInstructionsListRepository)
		  {
			  RegAgentBankInstructionsList 
				  *pRegAgentBankInstructionsList = NULL;

			  if ( pAgentBankInstructionsListRepository->
				  getRegAgentBankInstructionsList ( _RegAgent, 
				  pRegAgentBankInstructionsList, 
				  idDataGroup) <= WARNING && 
				  pRegAgentBankInstructionsList)
			  {  
				  setContainer ( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
					  pRegAgentBankInstructionsList);
			  }
		  }
	  }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool BankInstructionsProcess::doOk (GenericInterface *rpGI)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOOK);

   const BFDataGroupId& idDataGroup = getDataGroupId ();
   DSTCWorkSession *dstcWorkSession = 
      dynamic_cast <DSTCWorkSession*> (getBFWorkSession ());

   if (BANKTYPE::SHAREHOLDER == _bankInstrType || 
       BANKTYPE::ACCOUNT == _bankInstrType )
   {
      DString dstBankFlag = I_("N");

      if (_pShareholder)
      {
         ShareholderBankInstructionsList 
            *pShareholderBankInstructionsList = NULL;

         if ( _pShareholder->getShareholderBankInstructionsList ( pShareholderBankInstructionsList, 
                                                                  idDataGroup) <= WARNING)
         {
            BFObjIter iter ( *pShareholderBankInstructionsList, 
                             idDataGroup, 
                             false, 
                             BFObjIter::ITERTYPE::NON_DELETED);

            while (!iter.end ())
            {
               if (!iter.isDummy ())
               {
                  dstBankFlag = I_ ("Y");
                  break;
               }
               ++iter;
            }
            _pShareholder->setField ( ifds::BankingInstr, 
                                      dstBankFlag, 
                                      idDataGroup, 
                                      false);
         }
      }
   } 
   //check whether we are in the RRIF/Systematic/Distribution/Settlement/Trade
   //screen so we can copy the banking information fields over to the 
   //RRIF/Systematic/Distribution/SettlementTrade/Trade  objects
   else if ( ( _bankInstrType == BANKTYPE::RRIF ||
               _bankInstrType == BANKTYPE::SYSTEMATIC ||
               _bankInstrType == BANKTYPE::DISTRIBUTION ||
               _bankInstrType == BANKTYPE::SETTLEMENT ||
               _bankInstrType == BANKTYPE::TRADE ||
               _bankInstrType == BANKTYPE::MATURITY_INSTRUCTIONS ||
               _bankInstrType == BANKTYPE::ACCOUNT_COMMITMENT ||
			   _bankInstrType == BANKTYPE::CONTRACTMAT_INSTRUCTIONS ) &&
             _caller == _bankInstrType) 
   {      
      //get the current BanknigInstructions object
      BankInstructionsEx *pBankInstructionsEx = 
         dynamic_cast <BankInstructionsEx*> ( getCBOItem ( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                                           idDataGroup));
	  BankInstructions *pBankInstructions = dynamic_cast<BankInstructions*>(pBankInstructionsEx);
	  //copy only if user has done any updates.
	  if (pBankInstructionsEx && pBankInstructions->isBankingUpdatedByUser(idDataGroup))
      {
         pBankInstructionsEx->copyToSpecificCBO (idDataGroup);
      }
   } 
   return true;
}

//******************************************************************************
E_COMMANDRETURN BankInstructionsProcess::doProcess ()
{  
   MAKEFRAME2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if (!isXMLAPIContext ())
      {
         setParameter (USER_ACCESS_CODE, m_strUserAccessCode);
         setParameter ( MFCAN_IP_PARAM::SELECTION_KEY, 
                        _bankInstructionsListSelectionKey);
         setParameter ( MFCAN_IP_PARAM::SPONSORDESC, _fundSponsorDesc);
         rtn = invokeCommand ( this, 
                               CMD_GUI_BANK_INSTRUCTIONS, 
                               getProcessType (), 
                               isModal (), 
                               &_rpChildGI);
      }
      else 
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
   }
   catch (ConditionException &ce)
   {
      assert (0);
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************
bool BankInstructionsProcess::doCancel (GenericInterface *rpGICaller)
{
   removedClonedBankLists();
   return true;
}

//******************************************************************************
bool BankInstructionsProcess::doSend ( GenericInterface  *rpGICaller,
                                       const I_CHAR  *szMessage)
{
   DString message (szMessage);
   bool bReturn = false;
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast <DSTCWorkSession*> (getBFWorkSession ());

   if (message == CLONE)
   {
    if (BANKTYPE::SHAREHOLDER == _bankInstrType || 
       BANKTYPE::ACCOUNT == _bankInstrType )
      {
         //validate first the default banking, 
         //and then a valid record is cloned
         ShareholderBankInstructionsList
            *pShareholderBankInstructionsList = NULL;

         if ( _pShareholder && 
              _pShareholder->getShareholderBankInstructionsList ( pShareholderBankInstructionsList, 
                                                                  idDataGroup) <= WARNING &&
              pShareholderBankInstructionsList)
         {
            bReturn = pShareholderBankInstructionsList->validateAll (idDataGroup) <= WARNING;
         }
         if (bReturn)
         {
            if (_caller == BANKTYPE::RRIF)
            {
               RRIF_LIF_LRIF_Info *pRRIF_LIF_LRIF_Info = NULL;
               RRIFBankInstructionsList *pRRIFBankInstructionsList = NULL;
               RRIFBankInstructions *pRRIFBankInstructions = NULL;

               bReturn = cloneAndAttach ( pRRIF_LIF_LRIF_Info, 
                                          pRRIFBankInstructionsList, 
                                          pRRIFBankInstructions, 
                                          IFASTBP_PROC::RRIF_LIF_LRIF, 
                                          _rrifListKey) <= WARNING;
            }
            else if (_caller == BANKTYPE::SYSTEMATIC)
            {
               Systematic *pSystematic = NULL;
               SystematicBankInstructionsList *pSystematicBankInstructionsList = NULL;
               SystematicBankInstructions *pSystematicBankInstructions = NULL;

               bReturn = cloneAndAttach ( pSystematic, 
                                          pSystematicBankInstructionsList, 
                                          pSystematicBankInstructions, 
                                          IFASTBP_PROC::SYSTEMATIC, 
                                          _systematicListKey) <= WARNING;
            }
            else if (_caller == BANKTYPE::DISTRIBUTION)
            {
               AccountDistribution *pAccountDistribution = NULL;
               DistributionBankInstructionsList *pDistributionBankInstructionsList = NULL;
               DistributionBankInstructions *pDistributionBankInstructions = NULL;

               bReturn = cloneAndAttach ( pAccountDistribution, 
                                          pDistributionBankInstructionsList, 
                                          pDistributionBankInstructions, 
                                          IFASTBP_PROC::ACCOUNT_DISTRIBUTION, 
                                          _distributionListKey) <= WARNING;
            }
            else if (_caller == BANKTYPE::MATURITY_INSTRUCTIONS)
            {
               MatSweepInstrDetails *pMatSweepInstrDetails = NULL;
               MatSweepInstrBankList *pMatSweepInstrBankList = NULL;
               MatSweepInstrBank *pMatSweepInstrBank = NULL;

               bReturn = cloneAndAttach ( pMatSweepInstrDetails, 
                                          pMatSweepInstrBankList, 
                                          pMatSweepInstrBank, 
                                          IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, 
                                          _matSweepInstrListKey) <= WARNING;
            }
			else if (_caller == BANKTYPE::CONTRACTMAT_INSTRUCTIONS)
            {
               ContractMaturityInstruction *pContractMaturityInstruction = NULL;
               ContractMatInstrBankList *pContractMatInstrBankList = NULL;
               ContractMatInstrBank *pContractMatInstrBank = NULL;

               bReturn = cloneAndAttach ( pContractMaturityInstruction, 
                                          pContractMatInstrBankList, 
                                          pContractMatInstrBank, 
                                          IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, 
                                          _conMatInstrListKey) <= WARNING;
            }
            else if (_caller == BANKTYPE::ACCOUNT_COMMITMENT)
            {
               AccountCommitment *pAccountCommitment = NULL;
               AcctCommitBankList *pAcctCommitBankList = NULL;
               AcctCommitBank *pAcctCommitBank = NULL;

               bReturn = cloneAndAttach ( pAccountCommitment, 
                                          pAcctCommitBankList, 
                                          pAcctCommitBank, 
                                          IFASTBP_PROC::ACCOUNT_COMMITMENT, 
                                          _acctCommitListKey) <= WARNING;
            }
            else if (_caller == BANKTYPE::SETTLEMENT)
            {
               SettlementTrade *rpSettlementTrade = NULL;
               SettlementTradeBankInstructionsList *pSettlementTradeBankInstructionsList = NULL;
               SettlementTradeBankInstructions *pSettlementTradeBankInstructions = NULL;

               bReturn = cloneAndAttach ( rpSettlementTrade, 
                                          pSettlementTradeBankInstructionsList, 
                                          pSettlementTradeBankInstructions, 
                                          IFASTBP_PROC::SETTLEMENT, 
                                          _settlementListKey) <= WARNING;
            }
            else if (_caller == BANKTYPE::TRADE)
            {
               Trade *rpTrade = NULL;
               TradeBankInstructionsList *pTradeBankInstructionsList = NULL;
               TradeBankInstructions *pTradeBankInstructions = NULL;

               bReturn = cloneAndAttach ( rpTrade, 
                                          pTradeBankInstructionsList, 
                                          pTradeBankInstructions, 
                                          IFASTBP_PROC::TRADE, 
                                          _tradeListKey) <= WARNING;
            }
         }
      } 
      else if ( _bankInstrType == BANKTYPE::CLIENT ||
                _bankInstrType == BANKTYPE::BROKER ||
                _bankInstrType == BANKTYPE::BRANCH ||
                _bankInstrType == BANKTYPE::SALESREP)
      {
         //validate first the client banking, 
         //and then a valid record is cloned
         if (_bankInstrType == BANKTYPE::CLIENT)
         {
            ClientBankInstructionsList 
               *pClientBankInstructionsList = NULL;

            if ( pDSTCWorkSession->getClientBankInstructionsList ( pClientBankInstructionsList, 
                                                                   idDataGroup) <= WARNING &&
                 pClientBankInstructionsList)
            {
               bReturn = pClientBankInstructionsList->validateAll (idDataGroup) <= WARNING;
            }
         }
         //validate first the distributor banking, 
         //and then a valid record is cloned
         else if ( _bankInstrType == BANKTYPE::BROKER ||
                   _bankInstrType == BANKTYPE::BRANCH ||
                   _bankInstrType == BANKTYPE::SALESREP)
         {
            DistributorRepository *pDistributorRepository = NULL;

            if ( pDSTCWorkSession->getDistributorRepository (pDistributorRepository) <= WARNING &&
                 pDistributorRepository)
            {
               DistributorBankInstructionsList *pDistributorBankInstructionsList = NULL;
   
               if ( pDistributorRepository->
                      getDistributorBankInstructionsList ( _brokerCode, 
                                                           _branchCode, 
                                                           _salesRepCode,
                                                           pDistributorBankInstructionsList, 
                                                           idDataGroup) <= WARNING &&
                    pDistributorBankInstructionsList)
               {
                  bReturn = pDistributorBankInstructionsList->validateAll (idDataGroup) <= WARNING;
               }
            }
         }
         if (bReturn)
         {
            if (_caller == BANKTYPE::TRADE)
            {
               Trade *rpTrade = NULL;
               TradeBankInstructionsList *pTradeBankInstructionsList = NULL;
               TradeBankInstructions *pTradeBankInstructions = NULL;

               bReturn = cloneAndAttach ( rpTrade, 
                                          pTradeBankInstructionsList, 
                                          pTradeBankInstructions, 
                                          IFASTBP_PROC::TRADE, 
                                          _tradeListKey) <= WARNING;
            }
            else if (_caller == BANKTYPE::SETTLEMENT)
            {
               SettlementTrade *rpSettlementTrade = NULL;
               SettlementTradeBankInstructionsList *pSettlementTradeBankInstructionsList = NULL;
               SettlementTradeBankInstructions *pSettlementTradeBankInstructions = NULL;

               bReturn = cloneAndAttach ( rpSettlementTrade, 
                                          pSettlementTradeBankInstructionsList, 
                                          pSettlementTradeBankInstructions, 
                                          IFASTBP_PROC::SETTLEMENT, 
                                          _settlementListKey) <= WARNING;
            }
         }
      }
   }
   return bReturn;
}

//******************************************************************************
void BankInstructionsProcess::setCurrentListItem ( const GenericInterface *rpGICaller, 
                                                   const BFContainerId& idList,
                                                   const DString &strListItemKey)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           SETCURRENTLISTITEM);

   if (IFASTBP_PROC::BANK_INSTRUCTIONS_LIST == idList)
   {
      if (_bankInstrType == BANKTYPE::RRIF)
      {
         _rrifListKey = strListItemKey;
      }
      else if (_bankInstrType == BANKTYPE::SYSTEMATIC)
      {
         _systematicListKey = strListItemKey;
      }
      else if (_bankInstrType == BANKTYPE::DISTRIBUTION)
      {
         _distributionListKey = strListItemKey;
      }      
      else if (_bankInstrType == BANKTYPE::SETTLEMENT)
      {
         _settlementListKey = strListItemKey;
      }
      else if (_bankInstrType == BANKTYPE::TRADE)
      {
         _tradeListKey = strListItemKey;
      }
      else if(_bankInstrType == BANKTYPE::MATURITY_INSTRUCTIONS)
      {
         _matSweepInstrListKey = strListItemKey;
      }
      else if(_bankInstrType == BANKTYPE::ACCOUNT_COMMITMENT)
      {
         _acctCommitListKey = strListItemKey;
      }
	  else if(_bankInstrType == BANKTYPE::CONTRACTMAT_INSTRUCTIONS)
	  {
		_conMatInstrListKey = strListItemKey;
	  }
   } 
   AbstractProcess::setCurrentListItem ( rpGICaller, 
                                         idList, 
                                         strListItemKey);
}

//******************************************************************************
bool BankInstructionsProcess::doModelessSetFocus (GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert (_rpChildGI && isValidModelessInterface (_rpChildGI));

      // get bank type
      if (processParameters () <= WARNING)
      {
//also reset all containers,
         setContainer (IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, NULL);
         setContainer (IFASTBP_PROC::RRIF_LIF_LRIF, NULL);
         setContainer (IFASTBP_PROC::SYSTEMATIC, NULL);
         setContainer (IFASTBP_PROC::ACCOUNT_DISTRIBUTION, NULL);
         setContainer (IFASTBP_PROC::SETTLEMENT, NULL);
         setContainer (IFASTBP_PROC::TRADE, NULL);
         if (isValidModelessInterface (_rpChildGI))
         {  // Only if child still exists
            bRtn = _rpChildGI->refresh (this, NULL);
            bRtn = _rpChildGI->modelessSetFocus (rpGICaller);
         }
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 ( CND::BPBASE_CONDITION, 
                       CLASSNAME, DOMODELESSSETFOCUS,
                       CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return bRtn;
}

//******************************************************************************
bool BankInstructionsProcess::doModelessChildComplete (const Command &cmd)
{
   // End when GUI ends
   return (cmd.getKey () == CMD_GUI_BANK_INSTRUCTIONS);
}

//******************************************************************************
void BankInstructionsProcess::doGetField ( const GenericInterface *rpGICaller,
                                           const BFContainerId &idContainer, 
                                           const BFFieldId &idField,
                                           const BFDataGroupId &idDataGroup, 
                                           DString &strValueOut,
                                           bool bFormatted) const
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELD);

   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   BankInstructionsProcess* pBp = ( const_cast<BankInstructionsProcess* >(this) );

   strValueOut = NULL_STRING;
   //this field is used to enable/disable the To button
   if (idField == ifds::CloneBankInstructions) 
   {
      if ( _caller == BANKTYPE::SETTLEMENT )
      {
         if( _bankInstrType == BANKTYPE::SHAREHOLDER || _bankInstrType == BANKTYPE::ACCOUNT )
         {
            DString settleCurrency, bankAcctCurrency;
            BankInstructionsProcess* pBp = ( const_cast<BankInstructionsProcess* >(this) );

            pBp->getField ( rpGICaller, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                           ifds::BankAcctCurrency, bankAcctCurrency, false);

            pBp->getField ( rpGICaller, IFASTBP_PROC::SETTLEMENT,
                           ifds::SettleCurrency, settleCurrency, false);

            bankAcctCurrency.strip().upperCase();
            settleCurrency.strip().upperCase();
            strValueOut = settleCurrency == bankAcctCurrency ? I_("Y") : I_("N");
         }
         else if( _bankInstrType == BANKTYPE::BROKER ||
                  _bankInstrType == BANKTYPE::BRANCH || 
                  _bankInstrType == BANKTYPE::SALESREP )
         {
            // allow broker\barnch\slsrep bank in case that there is 
            // pay instruction for them
            strValueOut = I_("Y");
         }
      }
      else 
      {
         strValueOut = 
            ( (_bankInstrType == BANKTYPE::SHAREHOLDER || _bankInstrType == BANKTYPE::ACCOUNT ) &&
              ( _caller == BANKTYPE::RRIF || 
                _caller == BANKTYPE::SYSTEMATIC ||
                _caller == BANKTYPE::DISTRIBUTION ||
                _caller == BANKTYPE::TRADE   ||
                _caller == BANKTYPE::MATURITY_INSTRUCTIONS ||
                _caller == BANKTYPE::ACCOUNT_COMMITMENT	   ||
				_caller == BANKTYPE::CONTRACTMAT_INSTRUCTIONS ))  ||
                
            ( (_bankInstrType == BANKTYPE::CLIENT || 
               _bankInstrType == BANKTYPE::BROKER ||
               _bankInstrType == BANKTYPE::BRANCH ||
               _bankInstrType == BANKTYPE::SALESREP) &&
              _caller == BANKTYPE::TRADE) ? I_ ("Y") : I_ ("N");
      }
   }
   //caller name is mainly used for the caption of the To button
   else if (idField == ifds::CallerName)
   {
      strValueOut = _caller;
   }
   else if (idField == ifds::IsRRIFAccount)
   {
      strValueOut = I_ ("N");
      if (_pMFAccount && _pMFAccount->isRRIFAccount (getDataGroupId ()))
      {
         strValueOut = I_ ("Y");
      } 
   }
   else if (idField == ifds::AccountNum)
   {
      strValueOut = _accountNum;
   }
   else if (idField == ifds::ShrNum)
   {
      strValueOut = _shrNum;
   }
   else if (idField == ifds::Name)
   {
      pDSTCWorkSession->
         getFirstSequenced01AccountholderEntityName ( getDataGroupId (), 
                                                      DString (_accountNum), 
                                                      strValueOut);
   }
   else if (idField == ifds::BankInstrType)
   {
     if( BANKLEVEL::ACCOUNT == _bankInstrType ||  BANKLEVEL::SHAREHOLDER == _bankInstrType )
     {
          DString dstrDefaultBankingLevel;
          DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
          if(pDSTCWorkSession)
             pDSTCWorkSession->getOption (ifds::DefaultBankingLevel, dstrDefaultBankingLevel, getParent()->getDataGroupId(), false);

          strValueOut = BANKENTITY::ACCOUNT == dstrDefaultBankingLevel ? I_("Account") : _bankInstrType ;
     }
     else
     {
          strValueOut = _bankInstrType;
     }
   }
   else if (idField == ifds::BrokerCode)
   {
      if (_caller == BANKTYPE::TRADE)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (pBp->getCBOItem ( IFASTBP_PROC::TRADE, 
                                                     idDataGroup));
         if (pTrade)
         {
            pTrade->getField (ifds::Broker, strValueOut, idDataGroup, false);
         }
      }
      else
      {
         strValueOut = _brokerCode;
      }
   }
   else if (idField == ifds::BranchCode)
   {
      if (_caller == BANKTYPE::TRADE)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (pBp->getCBOItem ( IFASTBP_PROC::TRADE, 
                                                     idDataGroup));
         if (pTrade)
         {
            pTrade->getField (ifds::Branch, strValueOut, idDataGroup, false);
         }
      }
      else
      {
         strValueOut = _branchCode;
      }
   }
   else if (idField == ifds::SalesRepCode)
   {
      if (_caller == BANKTYPE::TRADE)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (pBp->getCBOItem ( IFASTBP_PROC::TRADE, 
                                                     idDataGroup));
         if (pTrade)
         {
            pTrade->getField (ifds::SlsrepCode, strValueOut, idDataGroup, false);
         }
      }
      else
      {
         strValueOut = _salesRepCode;
      }
   }
   else if ( idField == ifds::TradesTransType )
   {
      if (_caller == BANKTYPE::TRADE)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (pBp->getCBOItem ( IFASTBP_PROC::TRADE, 
                                                     idDataGroup));
         if (pTrade)
         {
            pTrade->getField (idField, strValueOut, idDataGroup, false);
         }
      }
      strValueOut.strip ();
   }
   else if(ifds::PayInstrOption == idField)
   {
	   if(BANKTYPE::TRADE == _caller)
	   {
		   Trade *pTrade = 
			   dynamic_cast <Trade*> (pBp->getCBOItem ( IFASTBP_PROC::TRADE, 
			   idDataGroup));
		   if (pTrade)
		   {
			   pTrade->getField (idField, strValueOut, idDataGroup, false);
		   }
	   }
	   strValueOut.strip ();
   }
   else if ( idField == ifds::PayToEntity )
   {
      if (_caller == BANKTYPE::TRADE)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (pBp->getCBOItem ( IFASTBP_PROC::TRADE, 
                                                     idDataGroup));
         if (pTrade)
         {
            if (pTrade->arePayInstructAllowed (idDataGroup))
            {
               pTrade->getTradePayToEntity (strValueOut, idDataGroup);
            }
         }
      }
      else if ( _caller == BANKTYPE::SETTLEMENT )
      {
         strValueOut = _payToEntity;
      }

      strValueOut.strip ();
   }
   else if ( idField == ifds::PayInstructExists )
   {
      if ( _caller == BANKTYPE::SETTLEMENT )
      {
         strValueOut = _payInstructExists;
      }

      strValueOut.strip ();
   }
   else if (idField == ifds::FundCode)
   {
      strValueOut = _fundCode;
   }
   else if (idField == ifds::FundGroup)
   {
      strValueOut = _fundGroup;
   }
   else if (idField == ifds::FundSponsor)
   {
      strValueOut = _fundSponsor;
   }
   else if (idField == ifds::RegAgent)
   {
	   strValueOut = _RegAgent;
   }
}

//******************************************************************************
SEVERITY BankInstructionsProcess::doSetField ( const GenericInterface *rpGICaller,
                                               const BFContainerId &idContainer, 
                                               const BFFieldId &idField,
                                               const BFDataGroupId &idDataGroup, 
                                               const DString &strValue,
                                               bool bFormatted)
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD);

   if (idField == ifds::BankInstrType)
   {
      _bankInstrType = strValue;

      //read broker, branch and slsrep if caller is TRADE and pay to entity is not empty
      //if ( (_caller == BANKTYPE::TRADE || _caller == BANKTYPE::SETTLEMENT ) &&
      if ( _caller == BANKTYPE::TRADE &&
          (_bankInstrType == BANKTYPE::BRANCH ||
           _bankInstrType == BANKTYPE::BROKER ||
           _bankInstrType == BANKTYPE::SALESREP))
      {
         DString payToEntity;

         getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::PayToEntity, payToEntity, false);
         if (payToEntity == PAY_TO::BROKER)
         {
            getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BrokerCode, _brokerCode, false);
            _brokerCode.strip ().upperCase ();
            _branchCode = NULL_STRING;
            _salesRepCode = NULL_STRING;
         }
         else if (payToEntity == PAY_TO::BRANCH)
         {
            getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BrokerCode, _brokerCode, false);
            getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BranchCode, _branchCode, false);
            _brokerCode.strip ().upperCase ();
            _branchCode.strip ().upperCase ();
            _salesRepCode = NULL_STRING;
         }
         else if (payToEntity == PAY_TO::SALESREP)
         {
            getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BrokerCode, _brokerCode, false);
            getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BranchCode, _branchCode, false);
            getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::SalesRepCode, _salesRepCode, false);
            _brokerCode.strip ().upperCase ();
            _branchCode.strip ().upperCase ();
            _salesRepCode.strip ().upperCase ();
         }
      }
//reset the container, to pick up new items
      setContainer (IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, NULL);
      if (getNumberOfItemsInList (this, idContainer) > 0)
      {
         BFAbstractCBO *rpPtr = getCBOItem (idContainer, idDataGroup);
         DString dstrGUIOnly;
         getParameter( SET_FROM_GUI, dstrGUIOnly);
         if (rpPtr && I_("Y") != dstrGUIOnly)
         {
            rpPtr->setField ( ifds::BankInstrType, 
                              strValue, 
                              idDataGroup, 
                              bFormatted, 
                              false);
         }
      }
      if(_pShareholder )
         _pShareholder->setCurrentBankingSel( strValue );
   }
   return NO_CONDITION;
}

//******************************************************************************
const BFProperties *BankInstructionsProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                                    const BFContainerId &idContainer, 
                                                                    const BFFieldId &idField, 
                                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           DOGETFIELDATTRIBUTES);
   BFProperties  *pBFProperties = NULL;

   if (idField == ifds::BankOptionsFieldsHeadingSet)
   {
      if (!_propBankOptionsFieldsHeadingSet)
      {
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get (idField);
         _propBankOptionsFieldsHeadingSet = new BFProperties (pProps);
         if ( _bankInstrType == BANKTYPE::FUND || 
              _bankInstrType == BANKTYPE::CLIENT ||
              _bankInstrType == BANKTYPE::FUND_GROUP ||
              _bankInstrType == BANKTYPE::FUND_CLASS ||
              _bankInstrType == BANKTYPE::FUND_SPONSOR)
//DO NOT EXCLUDE file processor for Sharholder banking because API needs to set-up the default value!!!!!
         {
//remove the file processor field from the grid substitution list 'BankOptionsFieldsHeadingSet'
	         DString substList,
               newsubList (NULL_STRING),
               tmp (I_("ACHProcessor"));

            _propBankOptionsFieldsHeadingSet->getAllSubstituteValues (substList);

            int nPos = substList.find (tmp + I_("="));

            if (nPos != DString::npos)
	         {
	           newsubList = substList.left(nPos);
	           tmp = substList.right(substList.length() - nPos);
	           int rnPos = tmp.find(';');
	           if (rnPos != DString::npos)
	           {
                  newsubList += tmp.right (tmp.length() - rnPos - 1);
	           }
               _propBankOptionsFieldsHeadingSet->setAllSubstituteValues (newsubList);
	         }
         }
      }
      pBFProperties = _propBankOptionsFieldsHeadingSet;
   }
   return pBFProperties;
}

//******************************************************************************
void *BankInstructionsProcess::getPtrForContainer ( const BFContainerId &idContainer,
                                                    const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("getPtrForContainer"));
   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast <DSTCWorkSession*> (getBFWorkSession ());

   bool bDistribVerificationEnabled = false;
   pDSTCWorkSession->isVerificationEnabled ( idDataGroup, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             bDistribVerificationEnabled);

   try
   {
      if (IFASTBP_PROC::BANK_INSTRUCTIONS_LIST == idContainer)
       {
         if ( BANKTYPE::SHAREHOLDER == _bankInstrType || 
              BANKTYPE::ACCOUNT == _bankInstrType )
          {
                ShareholderBankInstructionsList 
                   *pShareholderBankInstructionsList = NULL;

                if (_pShareholder)
                {
                   if (_pShareholder->
                         getShareholderBankInstructionsList ( pShareholderBankInstructionsList, 
                                                              idDataGroup,  true,_accountNum ) <= WARNING && 
                         pShareholderBankInstructionsList)
                   {
                      pShareholderBankInstructionsList->setField ( ifds::AccountNum, 
                                                                   _accountNum, 
                                                                   idDataGroup, 
                                                                   false);
				      pShareholderBankInstructionsList-> setFieldUpdated( ifds::AccountNum,idDataGroup,false);
                      ptr = pShareholderBankInstructionsList;
                   }

                }
          }
          else if (_bankInstrType == BANKTYPE::DIRECT_TRADING)
          {
            DirectTradingBankInstructionsList 
               *pDirectTradingBankInstructionsList = NULL;

            if (_pShareholder)
            {
               if (_pShareholder->
                     getDirectTradingBankInstructionsList ( pDirectTradingBankInstructionsList, 
                                                            idDataGroup) <= WARNING && 
                     pDirectTradingBankInstructionsList)
               {
                  pDirectTradingBankInstructionsList->
                        setField ( ifds::AccountNum, 
                                   _accountNum, 
                                   idDataGroup, 
                                   false);
                  ptr = pDirectTradingBankInstructionsList;
               }
            }
         }
         else if (_bankInstrType == BANKTYPE::TRADE)
         {
            WorksessionTradesList *pTradesList = NULL;

            if ( pDSTCWorkSession->getTradesList ( pTradesList, 
                                                   idDataGroup) <= WARNING &&
                 pTradesList)
            {
               Trade *pTrade = NULL;
   
               pTrade = dynamic_cast <Trade*> 
                     ( pTradesList->getObject ( _callerListKey, 
                                                idDataGroup) );
               if (pTrade)
               {
                  BFAbstractCBO * pTradePayInstruct (NULL);
                  
                  if (!_callerSubListKey.empty () && 
                      pTrade->arePayInstructAllowed (idDataGroup))
                  {
                     TradePayInstructList *pTradePayInstructList = NULL;

                     if ( pTrade->
                           getTradePayInstructList (pTradePayInstructList, idDataGroup, false) <= WARNING && 
                           pTradePayInstructList)
                     {
                        BFObjIter iter ( *pTradePayInstructList, 
                                          idDataGroup, 
                                          false, 
                                          BFObjIter::ITERTYPE::NON_DELETED);

                        if (!_callerSubListKey.empty())
                        {
                           //use the sub-list key
                           iter.positionByKey (_callerSubListKey);
                           if (!iter.end ())
                           {
                              pTradePayInstruct = iter.getObject ();
                           }
                        }
                     }
                  }     

                  TradeBankInstructionsList *pTradeBankInstructionsList = NULL;

                  if ( pTrade->getBankInstructionsList ( pTradeBankInstructionsList, 
                                                         idDataGroup,
                                                         false,
                                                         pTradePayInstruct) <= WARNING &&
                       pTradeBankInstructionsList)
                  {
                     ptr = pTradeBankInstructionsList;
                  }
               }
            }
         }
         else if (_bankInstrType == BANKTYPE::DISTRIBUTION)
         {
            AccountDistribution *rpAccountDistribution = 
               dynamic_cast<AccountDistribution*> ( getCBOItem ( IFASTBP_PROC::ACCOUNT_DISTRIBUTION, 
                                                                 idDataGroup));

            if (rpAccountDistribution)
            {
               DistributionBankInstructionsList
                  *pDistributionBankInstructionsList = NULL;

               if ( rpAccountDistribution->
                      getBankInstructionsList ( pDistributionBankInstructionsList, 
                                                idDataGroup) <= WARNING &&
                    pDistributionBankInstructionsList)
               {
                  ptr = pDistributionBankInstructionsList;

                  if ( bDistribVerificationEnabled )
                  {
                     BFObjIter iterDistribBankList (*pDistributionBankInstructionsList, idDataGroup, false, 
                                                     BFObjIter::ITERTYPE::NON_DELETED);

                     if (!iterDistribBankList.end ())
                     {
                        BankInstructions *pBankInstructions = 
                              dynamic_cast<BankInstructions*> ( iterDistribBankList.getObject() );
                        if ( pBankInstructions && 
                            _distribGBCD == I_("N") && 
                            _distribVerifyStat == UNVERIFIED )
                        {
                           pBankInstructions->setFieldsDistribBankReadOnly( idDataGroup, true );
                        }
                     }
                  }
               }
            } 
            else 
            {
               //see RRIF' comments....
               if (buildDummyDistributionBankInstructionsList () <= WARNING)
               {
                  ptr = _pDummyDistributionBankInstructionsList;
               }
            }
         }
         else if (_bankInstrType == BANKTYPE::SYSTEMATIC)
         {
            Systematic *rpSystematicPtr = 
                  dynamic_cast<Systematic*> ( getCBOItem ( IFASTBP_PROC::SYSTEMATIC, 
                                                           idDataGroup));

            if (rpSystematicPtr)
            {
               SystematicBankInstructionsList 
                     *pSystematicBankInstructionsList = NULL;

               if ( rpSystematicPtr->getBankInstructionsList ( pSystematicBankInstructionsList, 
                                                               idDataGroup) <= WARNING)
               {
                  ptr = pSystematicBankInstructionsList;
               }
            } 
            else 
            {
               //see RRIF' comments....
               if (buildDummySystematicBankInstructionsList () <= WARNING)
               {
                  ptr = _pDummySystematicBankInstructionsList;
               }
            }
         }
         else if (_bankInstrType == BANKTYPE::MATURITY_INSTRUCTIONS)
         {
            MatSweepInstrDetails *rpMatSweepInstrDetailsPtr = 
               dynamic_cast<MatSweepInstrDetails*> ( getCBOItem ( IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, 
                                                           idDataGroup));

            if (rpMatSweepInstrDetailsPtr)
            {
               MatSweepInstrBankList *pMatSweepInstrBankList = NULL;

               if ( rpMatSweepInstrDetailsPtr->getBankInstructionsList ( pMatSweepInstrBankList, idDataGroup) <= WARNING)
               {
                  ptr = pMatSweepInstrBankList;
               }
            } 
            else 
            {
               //see RRIF' comments....
               if (buildDummyMatSweepInstrBankList() <= WARNING)
               {
                  ptr = _pDummyMatSweepInstrBankList;
               }
            }
         }
         else if (_bankInstrType == BANKTYPE::ACCOUNT_COMMITMENT)
         {
            if(_pMFAccount)
            {
               AccountCommitment* pAccountCommitment;
               _pMFAccount->getAccountCommitment(pAccountCommitment, idDataGroup);
               if(pAccountCommitment != NULL)
               {
                  AcctCommitBankList *pAcctCommitBankList = NULL;

                  if ( pAccountCommitment->getBankInstructionsList( pAcctCommitBankList, idDataGroup) <= WARNING)
                  {
                     ptr = pAcctCommitBankList;
                  }
               } 
               else 
               {
                  //see RRIF' comments....
                  if (buildDummyAcctCommitBankList() <= WARNING)
                  {
                     ptr = _pDummyAcctCommitBankList;
                  }
               }
            }
         }
		 else if (_bankInstrType == BANKTYPE::CONTRACTMAT_INSTRUCTIONS)
         {
			ContractMaturityInstructionList* pContractMaturityInstructionList = NULL;
			if ( _pMFAccount && 
				_pMFAccount->getContractMaturityInfoList ( pContractMaturityInstructionList, 
				_accountNum, _dstrCotAcctRid, _dstrContractType, _dstrContractTypeId,  idDataGroup, false) <= WARNING && 
				pContractMaturityInstructionList )
			{
				BFObjIter iter ( *pContractMaturityInstructionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

				iter.positionByKey (_conConMatListKey);
				if (!iter.end ())
				{
					ContractMatInstrBankList *pContractMatInstrBankList = NULL;

					ContractMaturityInstruction *rpContractMaturityInstructionPtr = dynamic_cast<ContractMaturityInstruction*>( iter.getObject() );
					if (   rpContractMaturityInstructionPtr 
						&& rpContractMaturityInstructionPtr->getBankInstructionsList (pContractMatInstrBankList, idDataGroup) <= WARNING
						&& pContractMatInstrBankList )
					{
						ptr = pContractMatInstrBankList;
					}
					else if ( buildDummyContractMatInstrBankList() <= WARNING ) //see RRIF' comments....
					{
						ptr = _pDummyContractMatInstrBankList;
					}
				}
				else 
				{
					//see RRIF' comments....
					if ( buildDummyContractMatInstrBankList() <= WARNING )
					{
						ptr = _pDummyContractMatInstrBankList;
					}
				}

			}//-- if ( _pMFAccount &&

         }
         else if (_bankInstrType == BANKTYPE::SETTLEMENT)
         {
            SettlementTrade *rpSettlementTrade = 
                  dynamic_cast<SettlementTrade*> ( getCBOItem ( IFASTBP_PROC::SETTLEMENT, 
                                                                idDataGroup));

            if (rpSettlementTrade)
            {
               SettlementTradeBankInstructionsList 
                  *pSettlementTradeBankInstructionsList = NULL;

               if ( rpSettlementTrade->
                      getBankInstructionsList ( pSettlementTradeBankInstructionsList, 
                                                idDataGroup) <= WARNING &&
                    pSettlementTradeBankInstructionsList)
               {
                  ptr = pSettlementTradeBankInstructionsList;
               }
            } 
            else 
            {
               //see RRIF' comments...
               if (buildDummySettlementTradeBankInstructionsList () <= WARNING)
               {
                  ptr = _pDummySettlementTradeBankInstructionsList;
               }
            }
         }
         else if (_bankInstrType == BANKTYPE::RRIF)
         {
            RRIF_LIF_LRIF_Info *rpRRIFPtr = 
                  dynamic_cast<RRIF_LIF_LRIF_Info*> ( getCBOItem ( IFASTBP_PROC::RRIF_LIF_LRIF, 
                                                                   idDataGroup));

            if (rpRRIFPtr)
            {
               RRIFBankInstructionsList *pRRIFBankInstructionsList = NULL;

               if ( rpRRIFPtr->
                      getBankInstructionsList ( pRRIFBankInstructionsList, 
                                                idDataGroup) <= WARNING &&
                    pRRIFBankInstructionsList)
               {
                  ptr = pRRIFBankInstructionsList;
               }
            } 
            else 
            {
               //create this dummy pointer in case we are asked for RRIF bank instructions 
               //list, and there is no RRIF object to hang the list off;
               //the dialog will just disable all the controls, so we can display it
               //properly. In this case we cannot add/delete anything to/from 
               //the list, because the list is not created with a proper parent, 
               //which is suppose to be RRIFInfo object,
               //also this dummy list is used for display purposes,
               //in case there are any banks hangig off the RRIF objects
               if (buildDummyRRIFBankInstructionsList () <= WARNING)
               {
                  ptr = _pDummyRRIFBankInstructionsList;
               }
            }
         }
         else if ( _bankInstrType == BANKTYPE::BROKER ||
                   _bankInstrType == BANKTYPE::BRANCH ||
                   _bankInstrType == BANKTYPE::SALESREP)
         {
            DistributorRepository *pDistributorRepository = NULL;

            if ( pDSTCWorkSession->getDistributorRepository (pDistributorRepository) <= WARNING &&
                 pDistributorRepository)
            {
               DistributorBankInstructionsList *pDistributorBankInstructionsList = NULL;
   
               if ( pDistributorRepository->
                      getDistributorBankInstructionsList ( _brokerCode, 
                                                           _branchCode, 
                                                           _salesRepCode,
                                                           pDistributorBankInstructionsList, 
                                                           idDataGroup) <= WARNING &&
                    pDistributorBankInstructionsList)
               {
                  ptr = pDistributorBankInstructionsList;
               }
            }
         }
         else if (_bankInstrType == BANKTYPE::CLIENT)
         {
            ClientBankInstructionsList 
               *pClientBankInstructionsList = NULL;

            if ( pDSTCWorkSession->
                   getClientBankInstructionsList ( pClientBankInstructionsList, 
                                                   idDataGroup) <= WARNING &&
                 pClientBankInstructionsList)
            {
               ptr = pClientBankInstructionsList;
            }
         }
         else if (_bankInstrType == BANKTYPE::FUND)
         {
            FundBankInstructionsListRepository 
               *pFundBankInstructionsListRepository = NULL;

            if ( pDSTCWorkSession->
                   getFundBankInstructionsListRepository (pFundBankInstructionsListRepository) <= WARNING &&
                 pFundBankInstructionsListRepository)
            {
               FundBankInstructionsList
                  *pFundBankInstructionsList = NULL;
   
               if ( pFundBankInstructionsListRepository->
                      getFundBankInstructionsList ( _fundCode,  
                                                   pFundBankInstructionsList, 
                                                   idDataGroup) <= WARNING &&
                    pFundBankInstructionsList
                  )
               {
                  ptr = pFundBankInstructionsList;
               }
            }
         }
         else if (_bankInstrType == BANKTYPE::FUND_CLASS)
         {
            FundBankInstructionsListRepository 
               *pFundBankInstructionsListRepository = NULL;

            if ( pDSTCWorkSession->
                   getFundBankInstructionsListRepository (pFundBankInstructionsListRepository) <= WARNING &&
                 pFundBankInstructionsListRepository)
            {
               FundBankInstructionsList
                  *pFundBankInstructionsList = NULL;
   
               if ( pFundBankInstructionsListRepository-> 
                      getFundBankInstructionsList ( _fundCode, 
                                                    _classCode,
                                                    pFundBankInstructionsList, 
                                                    idDataGroup) <= WARNING &&
                    pFundBankInstructionsList)
               {
                  ptr = pFundBankInstructionsList;
               }
            }
         }
      } 
      else if (IFASTBP_PROC::RRIF_LIF_LRIF == idContainer)
      { //we should look at the account and get the RRIF list
         RRIF_LIF_LRIF_InfoList *pRRIF_LIF_LRIF_InfoList = NULL;

         if ( _pMFAccount && 
              _pMFAccount->getRRIF_LIF_LRIF_InfoList ( pRRIF_LIF_LRIF_InfoList, 
                                                       idDataGroup) <= WARNING && 
              pRRIF_LIF_LRIF_InfoList && 
              !_callerListKey.empty())
         {
            BFObjIter iter ( *pRRIF_LIF_LRIF_InfoList, 
                             idDataGroup, 
                             false, 
                             BFObjIter::ITERTYPE::NON_DELETED);
            
            iter.positionByKey (_callerListKey);
            if (!iter.end ())
            {
               ptr = iter.getObject ();
            }
         }
      }
      else if (IFASTBP_PROC::SYSTEMATIC == idContainer)
      { //we should look at the account and get the Systematic list
         SystematicList *pSystematicList = NULL;

         if ( _pMFAccount && 
              _pMFAccount->getSystematicList ( pSystematicList, 
                                               idDataGroup) <= WARNING && 
              pSystematicList && 
              !_callerListKey.empty())
         {
            BFObjIter iter ( *pSystematicList, 
                             idDataGroup, 
                             false, 
                             BFObjIter::ITERTYPE::NON_DELETED);
            
            iter.positionByKey (_callerListKey);
            if (!iter.end ())
            {
               ptr = iter.getObject ();
            }
         }
      } 
      else if (IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL == idContainer)
      { //we should look at the account and get the Systematic list
         MatSweepInstrList* pMatSweepInstrList = NULL;
         if(_matSweepInstrLevel == I_("Acct") || _matSweepInstrLevel == I_("Proc") )
         {
            if ( _pMFAccount && 
               _pMFAccount->getMatSweepInstrList(pMatSweepInstrList, _matSweepInstrType, _matSweepInstrLevel, 
               _fundCode, 
               _classCode, _TransNum, _TransId, _IntInvestId, _PrincipalAmount, _AccuredAmount, idDataGroup, false) <= WARNING && 
               pMatSweepInstrList && !_matSweepInstrKey.empty())

            {
               BFObjIter iter ( *pMatSweepInstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
               
               iter.positionByKey (_matSweepInstrKey);
               if (!iter.end ())
               {
                  MatSweepInstr* pMatSweepInstr = (MatSweepInstr*)iter.getObject();
                  if(pMatSweepInstr)
                  {
				         MatSweepInstrDetailsList *pMatSweepInstrDetailsList = NULL;

				         if ( pMatSweepInstr->getMatSweepDetailsList (pMatSweepInstrDetailsList, idDataGroup) <= WARNING &&
					         pMatSweepInstrDetailsList)
				         {
                        BFObjIter detailIter( *pMatSweepInstrDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
                        detailIter.positionByKey (_matSweepInstrDetailsKey);
                        
                        if(!detailIter.end())
                        {
                           ptr= detailIter.getObject();
                        }
				         }                                     
                  }
               }
            }
         }
         else if(_matSweepInstrLevel == I_("Trade") )
         {
				MatSweepInstrList *pMatSweepInstrList = NULL;
            Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

				if ( pTrade &&
                 pTrade->getMaturityInstrList (pMatSweepInstrList, idDataGroup) <= WARNING && 
                 pMatSweepInstrList)
				{
               BFObjIter iter ( *pMatSweepInstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
               
               iter.positionByKey (_matSweepInstrKey);
               if (!iter.end ())
               {
                  MatSweepInstr* pMatSweepInstr = (MatSweepInstr*)iter.getObject();
                  if(pMatSweepInstr)
                  {
				         MatSweepInstrDetailsList *pMatSweepInstrDetailsList = NULL;

				         if ( pMatSweepInstr->getMatSweepDetailsList (pMatSweepInstrDetailsList, idDataGroup) <= WARNING &&
					         pMatSweepInstrDetailsList)
				         {
                        BFObjIter detailIter( *pMatSweepInstrDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
                        detailIter.positionByKey (_matSweepInstrDetailsKey);
                        
                        if(!detailIter.end())
                        {
                           ptr= detailIter.getObject();
                        }
				         }                                     
                  }
               }
//					ptr = pMatSweepInstrList;
				}
         }
      } 
      else if (IFASTBP_PROC::ACCOUNT_COMMITMENT == idContainer)
      {
         ptr = NULL;
         if(_pMFAccount)
         {
            AccountCommitment* pAccountCommitment;
            _pMFAccount->getAccountCommitment(pAccountCommitment, idDataGroup);
            if(pAccountCommitment != NULL)
            {
               ptr = pAccountCommitment;
            }
         }
      }
	  else if (IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS == idContainer)
      {
		ptr = NULL;
		ContractMaturityInstructionList* pContractMaturityInstructionList = NULL;
        if ( _pMFAccount && 
             _pMFAccount->getContractMaturityInfoList ( pContractMaturityInstructionList, 
			 _accountNum, _dstrCotAcctRid, _dstrContractType, _dstrContractTypeId,  idDataGroup, false) <= WARNING && 
             pContractMaturityInstructionList && !_conMatInstrListKey.empty() )
        {
            BFObjIter iter ( *pContractMaturityInstructionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

            iter.positionByKey (_conConMatListKey);
            if (!iter.end ())
            {                
				ptr = iter.getObject();
            }
        }//-- if ( _pMFAccount &&
      }
      else if (IFASTBP_PROC::ACCOUNT_DISTRIBUTION == idContainer)
      {
         AccountDistributionList *pAccountDistributionList = NULL;
         
         //get the account distribution list from MfAccount
         if ( _pMFAccount && 
              _pMFAccount->getAccDistributionsList ( pAccountDistributionList, 
                                                     idDataGroup) <= WARNING && 
              pAccountDistributionList && 
              !_callerListKey.empty())
         {
            BFObjIter iter ( *pAccountDistributionList, 
                             idDataGroup, 
                             false, 
                             BFObjIter::ITERTYPE::NON_DELETED);

            iter.positionByKey (_callerListKey);
            if (!iter.end ())
            {
               AccountDistribution *pAccountDistribution = 
                  dynamic_cast<AccountDistribution*> (iter.getObject ());

               if (pAccountDistribution)
               {
                  //get the 'SplitList'
                  AccountDistributionList *pSplitList = NULL;

                  if ( pAccountDistribution->
                         getSplitList ( pSplitList,
                                        idDataGroup) <= WARNING &&
                       pSplitList)
                  {
                     //this is the sub-list for the account distribution
                     BFObjIter iter ( *pSplitList, 
                                      idDataGroup, 
                                      false, 
                                      BFObjIter::ITERTYPE::NON_DELETED);

                     if (!_callerSubListKey.empty())
                     {
                        //use the sub-list key
                        iter.positionByKey (_callerSubListKey);
                        if (!iter.end ())
                        {
                           ptr = iter.getObject ();
                        }
                     }
                  }
               }
            }
         }
      }
      else if (IFASTBP_PROC::SETTLEMENT == idContainer)
      {  //get a pointer to the Settlement object
         Settlement *pSettlement = NULL;

         if ( pDSTCWorkSession->
                getSettlement ( pSettlement, 
                                idDataGroup, 
                                false) <= WARNING && 
              pSettlement)
         {
            SettlementTradeList *pSettlementTradeList = NULL;

            if ( pSettlement->
                   getSettlementTradeList ( pSettlementTradeList, 
                                            idDataGroup, 
                                            false, 
                                            false) <= WARNING && 
                 pSettlementTradeList && 
                 !_callerListKey.empty())
            {            
               BFObjIter iter ( *pSettlementTradeList, 
                                idDataGroup, 
                                false, 
                                BFObjIter::ITERTYPE::NON_DELETED);
            
               iter.positionByKey (_callerListKey);
               if (!iter.end ())
               {
                  ptr = iter.getObject ();
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
              !_callerListKey.empty())
         {
            BFObjIter iter ( *pPendingTradeList, 
                             idDataGroup, 
                             false, 
                             BFObjIter::ITERTYPE::NON_DELETED);

            iter.positionByKey (_callerListKey);
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
                 !_callerListKey.empty())
            {
               BFObjIter iter ( *pTransactionList, 
                                idDataGroup, 
                                false, 
                                BFObjIter::ITERTYPE::NON_DELETED);

               iter.positionByKey (_callerListKey);
               if (!iter.end ())
               {
                  ptr = iter.getObject();
               }
            }
         }
      }
      else if (IFASTBP_PROC::TRADE == idContainer)
      {
         WorksessionTradesList *pTradesList = NULL;

         if ( pDSTCWorkSession->getTradesList ( pTradesList, idDataGroup) <= WARNING && pTradesList 
              && !_callerListKey.empty())
         {
            BFObjIter iter ( *pTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

            iter.positionByKey (_callerListKey);
            if (!iter.end ())
            {
               ptr = iter.getObject();
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
      assert (0);
      THROWFROMFILE2 ( CND::BPBASE_CONDITION, 
                       CLASSNAME, DOINIT,
                       CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return (ptr);
}

//******************************************************************************
SEVERITY BankInstructionsProcess::doValidateAll ( BFAbstractCBO *rpWSD,
                                                  const BFDataGroupId& idDataGroup
                                                )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateAll"));
   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());

   //see about this....!
   if ( _bankInstrType == BANKTYPE::BROKER ||
        _bankInstrType == BANKTYPE::BRANCH ||
        _bankInstrType == BANKTYPE::SALESREP ||
        _bankInstrType == BANKTYPE::CLIENT ||
        _bankInstrType == BANKTYPE::FUND ||
        _bankInstrType == BANKTYPE::FUND_CLASS ||
        _bankInstrType == BANKTYPE::FUND_GROUP ||
        _bankInstrType == BANKTYPE::FUND_SPONSOR||
		_bankInstrType == BANKTYPE::REG_AGENT)
   {
      return rpWSD->validateAll (idDataGroup);
   }

   bool shouldValidateShareholder = 
      _bankInstrType == BANKTYPE::SHAREHOLDER ||  
      _bankInstrType == BANKTYPE::ACCOUNT ||   
      _bankInstrType == BANKTYPE::RRIF ||
      _bankInstrType == BANKTYPE::SYSTEMATIC ||
      _bankInstrType == BANKTYPE::DISTRIBUTION ||
      _bankInstrType == BANKTYPE::SETTLEMENT;
   
   if (shouldValidateShareholder)
   {
      //should validate the shareholder banks in case something
      //got changed
      ShareholderBankInstructionsList
         *pShareholderBankInstructionsList = NULL;

      if ( _pShareholder && 
           _pShareholder->getShareholderBankInstructionsList ( pShareholderBankInstructionsList, 
                                                               idDataGroup) <= WARNING &&
           pShareholderBankInstructionsList)
      {
         pShareholderBankInstructionsList->validateAll (idDataGroup);
      }
   }
   if (_bankInstrType == BANKTYPE::DIRECT_TRADING)
   {
      DirectTradingBankInstructionsList 
        *pDirectTradingBankInstructionsList = NULL;

      if (_pShareholder)
      {
         if ( _pShareholder->getDirectTradingBankInstructionsList ( pDirectTradingBankInstructionsList, 
                                                                    idDataGroup) <= WARNING && 
               pDirectTradingBankInstructionsList)
         {
            pDirectTradingBankInstructionsList->validateAll (idDataGroup);
         }
      }
   }
   if ( _bankInstrType == BANKTYPE::RRIF ||
        _bankInstrType == BANKTYPE::SYSTEMATIC ||
        _bankInstrType == BANKTYPE::DISTRIBUTION ||
        _bankInstrType == BANKTYPE::SETTLEMENT ||
        _bankInstrType == BANKTYPE::SETTLEMENT ||
        _bankInstrType == BANKTYPE::TRADE ||
		_bankInstrType == BANKTYPE::CONTRACTMAT_INSTRUCTIONS )
   {
      //should validate the 'only item' of the non host lists
      BFAbstractCBO *pBankInstructionsList = getCBOItem ( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                                          idDataGroup);

      if (pBankInstructionsList)
      {
         pBankInstructionsList->validateAll (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void BankInstructionsProcess::doPostOk ( GenericInterface* rpGICaller, 
                                         bool bSuccessFlag)
{
   if (bSuccessFlag)
   {
      removedClonedBankLists ();
   }
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
SEVERITY BankInstructionsProcess::processParameters ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_ ("processParameters"));

   DSTCWorkSession *pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   const BFDataGroupId& idDataGroup = getDataGroupId ();

   _bankInstrType = 
   _shrNum = 
   _accountNum = 
   _brokerCode = 
   _branchCode = 
   _salesRepCode = 
   _fundCode = 
   _callerListKey = 
   _bankInstructionsListSelectionKey =
   _callerSubListKey = 
   _caller = 
   _fundSponsorDesc = 
   _payInstructExists =
   _payToEntity = NULL_STRING;
   _matSweepInstrType = NULL_STRING;
   _matSweepInstrLevel = NULL_STRING;
   _matSweepInstrKey = NULL_STRING;
   _matSweepInstrDetailsKey = NULL_STRING;
   _conConMatListKey = NULL_STRING;

   getParameter (MFCAN_IP_PARAM::SELECTION_KEY, _bankInstructionsListSelectionKey);
   //get the account param, if any
   getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);
   //get the caller main list key, if any
   getParameter (MFCAN_IP_PARAM::LIST_KEY, _callerListKey);
   _callerListKey.strip ();
   //get the caller sub-list key, if any (used from AccDistribution)
   getParameter (MFCAN_IP_PARAM::SUB_LIST_KEY, _callerSubListKey);
   _callerSubListKey.strip ();
   //get the type of the bank
   getParameter (MFCAN_IP_PARAM::BANK_TYPE, _bankInstrType);
   _caller = _bankInstrType;

   getParameter ( MFCAN_IP_PARAM::DISTRIB_GBCD,_distribGBCD );
   getParameter ( MFCAN_IP_PARAM::VERIFY_STAT, _distribVerifyStat );

   getParameter ( I_("PayInstructExists"), _payInstructExists );
   getParameter ( I_("PayToEntity"), _payToEntity );

   if (_bankInstrType == BANKTYPE::BROKER)
   {
      getParameter (MFCAN_IP_PARAM::BROKER_CODE, _brokerCode);
      _brokerCode.strip ().upperCase ();
//check whether the broker exists
      if (!_brokerCode.empty ())
      {
         BrokerList brokerList (*pDSTCWorkSession);

         if(brokerList.init2 ( _brokerCode, 
                            NULL_STRING, 
                            I_ ("L"), 
                            NULL_STRING, 
                            NULL_STRING) <= WARNING)
         {
            //the broker exists, check if it is effective or not.
            Broker *broker;
            if( brokerList.getBroker(_brokerCode, broker) <= WARNING && broker != NULL)
            {
               DString dstrCurrBusDate;
               
               pDSTCWorkSession->getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
               broker->checkEffective(dstrCurrBusDate, idDataGroup);
            }
         }
         
      }
      else 
      {
         ADDCONDITIONFROMFILE (CND::BP_ERR_BROKER_EMPTY);
      }
   }
   else if (_bankInstrType == BANKTYPE::BRANCH)
   {
      getParameter (MFCAN_IP_PARAM::BROKER_CODE, _brokerCode);
      getParameter (MFCAN_IP_PARAM::BRANCH_CODE, _branchCode);
      _brokerCode.strip ().upperCase ();
      _branchCode.strip ().upperCase ();
//check whether the broker, branch exists
      if ( !_brokerCode.empty () && 
           !_branchCode.empty ())
      {
         BranchList branchList (*pDSTCWorkSession);

         branchList.init ( _brokerCode, 
                           _branchCode);
      }
      else 
      {
         ADDCONDITIONFROMFILE (CND::BP_ERR_BROKER_OR_BRANCH_EMPTY);
      }
   }
   else if (_bankInstrType == BANKTYPE::SALESREP)
   {
      getParameter (MFCAN_IP_PARAM::BROKER_CODE, _brokerCode);
      getParameter (MFCAN_IP_PARAM::BRANCH_CODE, _branchCode);
      getParameter (MFCAN_IP_PARAM::SALES_REP_CODE, _salesRepCode);
      _brokerCode.strip ().upperCase ();
      _branchCode.strip ().upperCase ();
      _salesRepCode.strip ().upperCase ();
//check whether the broker, branch, sales rep exists
      if ( !_brokerCode.empty () && 
           !_branchCode.empty () &&
           !_salesRepCode.empty ())
      {
         AgentList agentList (*pDSTCWorkSession);

         agentList.init ( _brokerCode, 
                          _branchCode, 
                          _salesRepCode);
      }
      else 
      {
         ADDCONDITIONFROMFILE (CND::BP_ERR_BROKER_OR_BRANCH_OR_SLSREP_EMPTY);
      }
   }
   else if ( _bankInstrType == BANKTYPE::FUND ||
             _bankInstrType == BANKTYPE::FUND_CLASS)
   {
      getParameter (MFCAN_IP_PARAM::FUND_CODE, _fundCode);
      _fundCode.strip ().upperCase ();
      if (!_fundCode.empty ())
      {
         FundMasterList *pFundMasterList = NULL;
         
         if ( pDSTCWorkSession->getMgmtCo ().
                  getFundMasterList (pFundMasterList) <= WARNING && 
              pFundMasterList
           )
         {
            if (!pFundMasterList->IsFundExist (_fundCode, idDataGroup))
            {
               ADDCONDITIONFROMFILE (CND::BP_ERR_INVALID_FUND);
            }
            else if (_bankInstrType == BANKTYPE::FUND_CLASS)
            {
               getParameter (MFCAN_IP_PARAM::CLASS_CODE, _classCode);
               _classCode.strip ().upperCase ();
               if (!_classCode.empty ())
               {
                  FundDetail *pFundDetail = NULL;

                  if ( !pDSTCWorkSession->getFundDetail ( _fundCode, 
                                                          _classCode, 
                                                          idDataGroup, 
                                                          pFundDetail) || 
                       !pFundDetail)
                  {
                     DString strIDI;

                     addIDITagValue (strIDI, I_ ("FUND"), _fundCode);
                     addIDITagValue (strIDI, I_ ("CLASS"), _classCode);
                     ADDCONDITIONFROMFILEIDI (CND::BP_ERR_INVALID_FUND_AND_CLASS, strIDI);
                  }
               }
               else
               {
                  ADDCONDITIONFROMFILE (CND::BP_ERR_CLASS_EMPTY);
               }
            }
         }
      }
      else
      {
         ADDCONDITIONFROMFILE (CND::BP_ERR_FUND_EMPTY);
      }
   }
   else if (_bankInstrType == BANKTYPE::FUND_GROUP)
   {   
      getParameter( MFCAN_IP_PARAM::FUND_GROUP, _fundGroup);
      _fundGroup.strip ().upperCase();
      if (!_fundGroup.empty())
      {   
         FundGroupSubList* pFundGroupSubList = NULL;

         if ( pDSTCWorkSession->getMgmtCo().getFundGroupSubList ( pFundGroupSubList, 
                                                                  I_("BANK")) <= WARNING &&  
              pFundGroupSubList)
         {
	         if (!pFundGroupSubList->doesFundGroupExist (_fundGroup ))
            {   
               ADDCONDITIONFROMFILE (CND::BP_ERR_INVALID_FUND_GROUP); 
            }
         }
      }
      else 
      {
         ADDCONDITIONFROMFILE (CND::BP_ERR_EMPTY_FUND_GROUP);
      }
   }
   else if (_bankInstrType == BANKTYPE::FUND_SPONSOR)
   {   
      getParameter (MFCAN_IP_PARAM::FUNDSPONSOR, _fundSponsor);
      _fundSponsor.strip ().upperCase();
      if (!_fundSponsor.empty())
      {
         FundSponsorsList* pFundSponsorsList = NULL;

         if ( pDSTCWorkSession->getMgmtCo().getFundSponsorsList (pFundSponsorsList) <= WARNING &&  
               pFundSponsorsList)
         {
            BFAbstractCBO *pFundSponsor (NULL);

            if (pFundSponsorsList->getFundSponsor (_fundSponsor, pFundSponsor) <= WARNING)
            {   
               if (!pFundSponsor)
               {
                  //ADDCONDITIONFROMFILE (CND::BP_ERR_INVALID_FUND_SPONSOR); 
               }
               else
               {
                  pFundSponsor->getField( ifds::FundGroupDesc, _fundSponsorDesc, idDataGroup );
               }
            }
         }
      }
      else 
      {
         //ADDCONDITIONFROMFILE (CND::BP_ERR_EMPTY_FUND_SPONSOR);
      }
   }
   else if (_bankInstrType == BANKTYPE::SETTLEMENT )
   {
      DString strPayInstructExists = _payInstructExists;
      DString strPayToEntity = _payToEntity;

      strPayInstructExists.strip().upperCase();
      strPayToEntity.strip().upperCase();

      if ( !strPayInstructExists.empty() )
      {
         if ( strPayToEntity == PAY_TO::BROKER)
         {
            getParameter (MFCAN_IP_PARAM::BROKER_CODE, _brokerCode);
            _brokerCode.strip ().upperCase ();
         }
         else if (strPayToEntity == PAY_TO::BRANCH)
         {
            getParameter (MFCAN_IP_PARAM::BROKER_CODE, _brokerCode);
            getParameter (MFCAN_IP_PARAM::BRANCH_CODE, _branchCode);
            _brokerCode.strip ().upperCase ();
            _branchCode.strip ().upperCase ();
         }
         else if (strPayToEntity == PAY_TO::SALESREP)
         {
            getParameter (MFCAN_IP_PARAM::BROKER_CODE, _brokerCode);
            getParameter (MFCAN_IP_PARAM::BRANCH_CODE, _branchCode);
            getParameter (MFCAN_IP_PARAM::SALES_REP_CODE, _salesRepCode);
            _brokerCode.strip ().upperCase ();
            _branchCode.strip ().upperCase ();
            _salesRepCode.strip ().upperCase ();
         }
      }
   }
   else if (_bankInstrType == BANKTYPE::MATURITY_INSTRUCTIONS)
   {
      getParameter (MFCAN_IP_PARAM::MAT_INSTR_TYPE,      _matSweepInstrType);
      getParameter (MFCAN_IP_PARAM::MAT_INSTR_LEVEL,     _matSweepInstrLevel);
      getParameter (MFCAN_IP_PARAM::MAT_INSTR_KEY,       _matSweepInstrKey);
      getParameter (MFCAN_IP_PARAM::MAT_INSTR_DETL_KEY,  _matSweepInstrDetailsKey);
	  getParameter (MFCAN_IP_PARAM::INV_PRINCIPAL,  _PrincipalAmount);
	  getParameter (MFCAN_IP_PARAM::INV_ACCRUED, _AccuredAmount);

      //_matSweepInstrLevel.strip().upperCase();
      _matSweepInstrType.strip().upperCase();
      _matSweepInstrKey.strip().upperCase();
      _matSweepInstrDetailsKey.strip().upperCase();

      getParameter(MFCAN_IP_PARAM::FUND_CODE,   _fundCode);
      getParameter(MFCAN_IP_PARAM::CLASS_CODE,  _classCode);
      getParameter(MFCAN_IP_PARAM::TRANS_NUM,   _TransNum);
      getParameter(MFCAN_IP_PARAM::TRANS_ID,    _TransId);
      getParameter(MFCAN_IP_PARAM::INVEST_ID,   _IntInvestId);
      _fundCode.strip().upperCase();
      _classCode.strip().upperCase();
      _TransNum.strip().upperCase();
      _TransId.strip().upperCase();
      _IntInvestId.strip().upperCase();
   }
   else if (_bankInstrType == BANKTYPE::REG_AGENT)
   {	
	   getParameter (MFCAN_IP_PARAM::REGAGENT, _RegAgent);
	   _RegAgent.strip().upperCase();
   }

   else if ( _bankInstrType == BANKTYPE::CONTRACTMAT_INSTRUCTIONS )
   {
		getParameter (MFCAN_IP_PARAM::CON_MAT_INSTR_KEY,		_conConMatListKey);

		getParameter (MFCAN_IP_PARAM::CON_MAT_INSTR_COTACCTRID,	_dstrCotAcctRid);
		getParameter (MFCAN_IP_PARAM::CON_MAT_INSTR_TYPE,		_dstrContractType);
		getParameter (MFCAN_IP_PARAM::CON_MAT_INSTR_TYPEID,		_dstrContractTypeId);
		
		_conConMatListKey.strip();
		_dstrCotAcctRid.strip();
		_dstrContractType.strip();
		_dstrContractTypeId.strip();
   }
   //if no error do some other processing
   if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
//some common processing
//to retrive the shareholder number, the account object,
//and the shareholder object
      if (_accountNum != NULL_STRING)
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
            _pMFAccount->getField (ifds::ShrNum, _shrNum, idDataGroup);
            _shrNum.strip ().stripLeading (I_CHAR ('0'));
//retrieve the shareholder pointer
            pDSTCWorkSession->getShareholder ( idDataGroup, 
                                               _shrNum, 
                                               _pShareholder);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void BankInstructionsProcess::removedClonedBankLists ()
{
   //blow the non-host lists so, we'll be forced to recreate them,
   //from the instances of the parent objects
   const BFDataGroupId &idDataGroup = getDataGroupId ();

   if (_caller == BANKTYPE::RRIF)
   {
      removeBankInstructionsList ( IFASTBP_PROC::RRIF_LIF_LRIF, 
                                   I_("RRIF_LIF_LRIF_BankInstructionsList"));
   } 
   else if (_caller == BANKTYPE::SYSTEMATIC)
   {
      removeBankInstructionsList ( IFASTBP_PROC::SYSTEMATIC, 
                                   I_("Systematic_BankInstructionsList"));
      
   }
   else if (_caller == BANKTYPE::DISTRIBUTION)
   {
      removeBankInstructionsList ( IFASTBP_PROC::ACCOUNT_DISTRIBUTION, 
                                   I_("Distribution_BankInstructionsList"));
   }
   else if (_caller == BANKTYPE::MATURITY_INSTRUCTIONS)
   {
      removeBankInstructionsList ( IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, 
                                   I_("MatSweepInstrBankList"));
   }
   else if (_caller == BANKTYPE::ACCOUNT_COMMITMENT)
   {
      removeBankInstructionsList ( IFASTBP_PROC::ACCOUNT_COMMITMENT, 
                                   I_("AcctCommitBankList"));
   }
   else if (_caller == BANKTYPE::CONTRACTMAT_INSTRUCTIONS)
   {
      removeBankInstructionsList ( IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, 
                                   I_("ContractMatInstrBankList"));
   }
   else if (_caller == BANKTYPE::SETTLEMENT)
   {
      //removeBankInstructionsList ( IFASTBP_PROC::SETTLEMENT, 
      //                             I_("SettlementTrade_BankInstructionsList"));
   }
   else if (_caller == BANKTYPE::TRADE)
   {
	
      //removeBankInstructionsList ( IFASTBP_PROC::SETTLEMENT, 
      //                             I_("Trade_BankInstructionsList"));
   }
}

//******************************************************************************
void BankInstructionsProcess::removeBankInstructionsList ( const BFContainerId& idContainer, 
                                                           const I_CHAR *icharKey)
{
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   BFAbstractCBO *pCBOItem = getCBOItem ( idContainer, 
                                          idDataGroup);

   if (pCBOItem)
   {
      BFObjIter iter (*pCBOItem, idDataGroup);

      iter.positionByKey (icharKey);
      if (!iter.end ())
      {
         iter.removeObjectFromMap (true);
      }
   }
}

//******************************************************************************
//_X - the type of the object that holds the banking instructions list (i.e. RRIF info object)
//_Y - the type of the banking instructions list (i.e. RRIFBankInstructionsList)
//_Z - the type of the banking instruction object (i.e. RRIFBankInstructions)
template <class _X, class _Y, class _Z>
   SEVERITY BankInstructionsProcess::cloneAndAttach ( const _X*, 
                                                      const _Y*, 
                                                      const _Z*, 
                                                      const BFContainerId &idContainer, 
                                                      const DString &keyToBeRemoved)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTBP_CONDITION, 
                           CLASSNAME, 
                           I_("cloneAndAttach"));

   const BFDataGroupId &idDataGroup = getDataGroupId ();         
   //get the current _X object
   _X *_pX = dynamic_cast<_X*> ( getCBOItem ( idContainer, 
                                              idDataGroup));

   if (_pX)
   {
      _Y *pBankInstructionsList = NULL;

      //get the bank instructions list that receives the clone
      //get the _Y banking instructions from the _X object
      if ( _pX->getBankInstructionsList ( pBankInstructionsList, 
                                          idDataGroup) <= WARNING && 
           pBankInstructionsList
         )
      {
//since we have the parent list, we can start the cloning process

         //get the current banking instructions item
         BankInstructions *pBankInstructions = 
               dynamic_cast<BankInstructions*> ( getCBOItem ( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                                              idDataGroup));
         //we have one, clone it
         if (pBankInstructions)
         {
            _Z *pBankInstructionsClone = NULL;

            if ( pBankInstructions->cloneInto ( pBankInstructionsClone, 
                                                pBankInstructionsList, 
                                                idDataGroup) <= WARNING && 
                 pBankInstructionsClone)
            {
//delete the current banking instructions object from list _Y and
//attach the clone _Z to the list
               BFObjIter iter ( *pBankInstructionsList, 
                                idDataGroup, 
                                true,
                                BFObjIter::ITERTYPE::NON_DELETED
                              );

               iter.positionByKey (keyToBeRemoved);
               if (!iter.end ())
               {
                  iter.removeObjectFromMap (true);
               }

//get the new key
               DString newKey;

               pBankInstructionsList->getStrKey (newKey);
               //set the object on the list
               pBankInstructionsList->setObject ( pBankInstructionsClone, 
                                                  newKey, 
                                                  OBJ_ACTIVITY_NONE, 
                                                  idDataGroup, 
                                                  OBJ_TYPE_NONE);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructionsProcess::buildDummySystematicBankInstructionsList ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTBP_CONDITION, 
                           CLASSNAME, 
                           I_("buildDummySystematicBankInstructionsList"));

   SystematicBankInstructions *pSystematicBankInstructions = NULL;
   Systematic *pSystematic = NULL;

   return buildDummyBankInstructionsList ( _pDummySystematicBankInstructionsList,
                                           pSystematicBankInstructions, 
                                           pSystematic);
}

//******************************************************************************
SEVERITY BankInstructionsProcess::buildDummyMatSweepInstrBankList()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTBP_CONDITION, 
                           CLASSNAME, 
                           I_("buildDummyMatSweepInstrBankList"));

   MatSweepInstrBankList *pMatSweepInstrBankList = NULL;
   MatSweepInstrDetails *pMatSweepInstrDetails = NULL;

   return buildDummyBankInstructionsList ( _pDummyMatSweepInstrBankList,
                                           pMatSweepInstrBankList, 
                                           pMatSweepInstrDetails);
}

//******************************************************************************
SEVERITY BankInstructionsProcess::buildDummyAcctCommitBankList()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTBP_CONDITION, 
                           CLASSNAME, 
                           I_("buildDummyAcctCommitBankList"));

   AcctCommitBankList *pAcctCommitBankList = NULL;
   AccountCommitment *pAccountCommitment = NULL;

   return buildDummyBankInstructionsList ( _pDummyAcctCommitBankList,
                                           pAcctCommitBankList, 
                                           pAccountCommitment);
}
//******************************************************************************
SEVERITY BankInstructionsProcess::buildDummyContractMatInstrBankList()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTBP_CONDITION, 
                           CLASSNAME, 
                           I_("buildDummyContractMatInstrBankList") );

   ContractMaturityInstruction *pContractMaturityInstruction = NULL;
   ContractMatInstrBankList *pContractMatInstrBankList = NULL;

   return buildDummyBankInstructionsList ( _pDummyContractMatInstrBankList,
                                           pContractMatInstrBankList,
                                           pContractMaturityInstruction );
}

//******************************************************************************
SEVERITY BankInstructionsProcess::buildDummyDistributionBankInstructionsList ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTBP_CONDITION, 
                           CLASSNAME, 
                           I_("buildDummyDistributionBankInstructionsList"));

   DistributionBankInstructions *pDistributionBankInstructions = NULL;
   AccountDistribution *pAccountDistribution = NULL;

   return buildDummyBankInstructionsList ( _pDummyDistributionBankInstructionsList,
                                           pDistributionBankInstructions, 
                                           pAccountDistribution);
}

//******************************************************************************
SEVERITY BankInstructionsProcess::buildDummyRRIFBankInstructionsList ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTBP_CONDITION, 
                           CLASSNAME, 
                           I_("buildDummyRRIFBankInstructionsList"));

   RRIFBankInstructions *pRRIFBankInstructions = NULL;
   RRIF_LIF_LRIF_Info *pRRIF_LIF_LRIF_Info = NULL;

   return buildDummyBankInstructionsList ( _pDummyRRIFBankInstructionsList,
                                           pRRIFBankInstructions, 
                                           pRRIF_LIF_LRIF_Info);
}

//******************************************************************************
SEVERITY BankInstructionsProcess::buildDummySettlementTradeBankInstructionsList ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTBP_CONDITION, 
                           CLASSNAME, 
                           I_("buildDummySettlementTradeBankInstructionsList"));

   SettlementTradeBankInstructions *pSettlementTradeBankInstructions = NULL;
   SettlementTrade *pSettlementTrade = NULL;

   return buildDummyBankInstructionsList ( _pDummySettlementTradeBankInstructionsList,
                                           pSettlementTradeBankInstructions, 
                                           pSettlementTrade);
}

//******************************************************************************
//_X - the type of the banking instructions list (i.e. RRIFBankInstructionsList), that we
//want ot build
//_Y - the type of the banking instruction object (i.e. RRIFBankInstructions)
//_Z - the type of the object that holds the banking instructions list (i.e. RRIF info object)
//******************************************************************************
template <class _X, class _Y, class _Z>
SEVERITY BankInstructionsProcess::buildDummyBankInstructionsList ( _X *&ptrBankListOut, 
                                                                   const _Y *ptrBankObject, 
                                                                   const _Z *ptrObject)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_ ("buildDummyBankInstructionsList"));
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   //blow the pointer out if is not null and rebuild the list
   _X *pBankListOut = dynamic_cast<_X*> (ptrBankListOut);

   if (pBankListOut)
   {
      delete pBankListOut;
      pBankListOut = NULL;
   }
   pBankListOut = new _X (*pDSTCWorkSession);
   //build the list only if we have an account available
   if (_pMFAccount)
   {
      //the list that contains the objects 
      //that might have banks hung off
      BFAbstractCBO *pParentList = NULL;

      if (_bankInstrType == BANKTYPE::RRIF)
      {
         RRIF_LIF_LRIF_InfoList *pRRIF_LIF_LRIF_InfoList = NULL;

         if (_pMFAccount->getRRIF_LIF_LRIF_InfoList (pRRIF_LIF_LRIF_InfoList, 
            idDataGroup) <= WARNING && pRRIF_LIF_LRIF_InfoList)
         {
            pParentList = pRRIF_LIF_LRIF_InfoList;
         }
      }
      else if (_bankInstrType == BANKTYPE::DISTRIBUTION)
      {
         AccountDistributionList *pAccDistributionList = NULL;

         if (_pMFAccount->getAccDistributionsList (pAccDistributionList, 
            idDataGroup) <= WARNING && pAccDistributionList)
         {
            AccountDistribution *pAccountDistribution = NULL;

            //set-up an iterator to get the account distributions that have
            //bank lists attached, at the split (allocation) level
            BFObjIter iterAccDistributionList (*pAccDistributionList, 
               idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

            while (!iterAccDistributionList.end ())
            {
               AccountDistribution *pAccountDistribution = 
                  dynamic_cast<AccountDistribution*> (iterAccDistributionList.getObject ());

               if (pAccountDistribution)
               {
                  AccountDistributionList *pSplitList = NULL;
                  
                  if (pAccountDistribution->getSplitList (pSplitList, 
                     idDataGroup) <= WARNING && pSplitList)
                  {
                     BFObjIter iterSplitList (*pSplitList, 
                        idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

                     while (!iterSplitList.end ())
                     {
                        AccountDistribution *pSplitAccountDistribution = 
                           dynamic_cast<AccountDistribution*> (iterSplitList.getObject ());

                        //build the parent list
                        if (!pParentList) //create it if NULL
                        {
                           //concatenate the split lists in it
                           pParentList = 
                              new AccountDistributionList (*pDSTCWorkSession);
                        }

                        DString dstrKey;
                        
                        (dynamic_cast<AccountDistributionList*>
                           (pParentList))->getStrKeyForNewItem (dstrKey);
                        //set the object, and tell 
                        //the list not to delete the objects
                        (dynamic_cast<AccountDistributionList*>
                           (pParentList))->setObject (pSplitAccountDistribution, dstrKey, 
                           OBJ_ACTIVITY_NONE, idDataGroup, OBJ_TYPE_NONE,
                           BFCBO::OBJ_DELETE::NO_DELETE_ON_DTOR);
                        ++iterSplitList;
                     }
                  }
               }
               ++iterAccDistributionList;
            }
         }
      }
      else if (_bankInstrType == BANKTYPE::SYSTEMATIC)
      {
         SystematicList *pSystematicList = NULL;

         if (_pMFAccount->getSystematicList (pSystematicList, 
            idDataGroup) <= WARNING && pSystematicList)
         {
            pParentList = pSystematicList;
         }
      }
      else if (_bankInstrType == BANKTYPE::SETTLEMENT)
      {
         Settlement *pSettlement = NULL;

         if (pDSTCWorkSession->getSettlement (pSettlement, idDataGroup, 
            false) <= WARNING && pSettlement)
         {
            SettlementTradeList *pSettlementTradeList = NULL;

            if (pSettlement->getSettlementTradeList (pSettlementTradeList, 
               idDataGroup, false, false) <= WARNING && pSettlementTradeList)
            {
               pParentList = pSettlementTradeList;
            }
         }
      }
      if (pParentList)
      {
         BFObjIter iterParentList (*pParentList, idDataGroup, false, 
            BFObjIter::ITERTYPE::NON_DELETED);

         while (!iterParentList.end ())
         {
            _Z *pObject = dynamic_cast<_Z*> (iterParentList.getObject ());

            if (pObject)
            {
               _X *pBankList = NULL;

               //do not create the bank list in here,
               //call this with false
               if (pObject->getBankInstructionsList (pBankList, idDataGroup) <= WARNING && 
                  pBankList)
               {
                  //get the first item of the list, it is always only one
                  BFObjIter iterBankList (*pBankList, idDataGroup, false, 
                     BFObjIter::ITERTYPE::NON_DELETED);

                  while (!iterBankList.end ())
                  {
                     _Y *pBankObject = dynamic_cast<_Y*> (iterBankList.getObject ());
                     
                     if (pBankObject) //set it on the previously created bank list 
                     {
                        //ask the bank list for the string key
                        DString dstrKey;
                        
                        pBankListOut->getStrKey (dstrKey);
                        //set the object, and tell 
                        //the list not to delete the objects
                        pBankListOut->setObject ( pBankObject, 
                                                  dstrKey, 
                                                  OBJ_ACTIVITY_NONE, 
                                                  idDataGroup, 
                                                  OBJ_TYPE_NONE,
                                                  BFCBO::OBJ_DELETE::NO_DELETE_ON_DTOR);
                     }
                     ++iterBankList;
                  }
               }
            }
            ++iterParentList;
         }
      }
      if (_bankInstrType == BANKTYPE::DISTRIBUTION)
      {
         delete pParentList;
         pParentList = NULL;
      }
   }
   ptrBankListOut = pBankListOut;
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructionsProcess::getHistoricalParameters ( const BFContainerId &idContainer, 
                                                            BFFieldId &recordIdField, 
                                                            DString &tableId, 
                                                            DString &dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           GETHISTORICALPARAMETERS);

   DString dstrAcctUseCode, 
      dstrCurrency, 
      dstrEntityCode, 
      keyStringIDI;
   if (idContainer == IFASTBP_PROC::BANK_INSTRUCTIONS_LIST)
   {
      recordIdField = ifds::BankAcctRid;
      if ( _bankInstrType == BANKTYPE::BROKER ||
           _bankInstrType == BANKTYPE::BRANCH ||
           _bankInstrType == BANKTYPE::SALESREP ||
           _bankInstrType == BANKTYPE::FUND ||
           _bankInstrType == BANKTYPE::FUND_GROUP ||
           _bankInstrType == BANKTYPE::FUND_SPONSOR ||
           _bankInstrType == BANKTYPE::SHAREHOLDER ||
           _bankInstrType == BANKTYPE::CLIENT ||
           _bankInstrType == BANKTYPE::TRADE ||
		   _bankInstrType == BANKTYPE::FUND_CLASS ||
		   _bankInstrType == BANKTYPE::SETTLEMENT ||
		   _bankInstrType == BANKTYPE::DISTRIBUTION ||
		   _bankInstrType == BANKTYPE::SYSTEMATIC ||
		   _bankInstrType == BANKTYPE::RRIF ||
		   _bankInstrType == BANKTYPE::DIRECT_TRADING||
		   _bankInstrType == BANKTYPE::REG_AGENT )
      {
         tableId = AUDITTYPE::BKACCT;
         dstrKeys = NULL_STRING;
      }
   }
   else if (idContainer == IFASTBP_PROC::ACCOUNT_DISTRIBUTION)
   {
      recordIdField = ifds::BankDetlRid;
      tableId = AUDITTYPE::SHADISBK;
// Account Number, From Fund, From Class, Effective Date
      DString dstrAccountNum, 
         dstrEffectiveDate, 
         dstrFundCode, 
         dstrClassCode;

      getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::AccountNum, dstrAccountNum, false);
      getField (this, IFASTBP_PROC::ACCOUNT_DISTRIBUTION, ifds::FundCode, dstrFundCode, false);
      getField (this, IFASTBP_PROC::ACCOUNT_DISTRIBUTION, ifds::ClassCode, dstrClassCode, false);
      getField (this, IFASTBP_PROC::ACCOUNT_DISTRIBUTION, ifds::EffectiveDate, dstrEffectiveDate, false);
      addIDITagValue (keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum);
      addIDITagValue (keyStringIDI, MFCAN_IP_PARAM::FUND_CODE, dstrFundCode);
      addIDITagValue (keyStringIDI, MFCAN_IP_PARAM::CLASS_CODE, dstrClassCode);
      addIDITagValue (keyStringIDI, MFCAN_IP_PARAM::EFFECTIVE_DATE, dstrEffectiveDate);
      dstrKeys = keyStringIDI;
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructionsProcess::getHistoricalParameters ( const BFContainerId &idContainer, 
                                                            HISTORICAL_VECTOR &vectorHistorical)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool BankInstructionsProcess::hasBankingInstr(const DString& dstrxAcctNumber) const
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("hasBankingInstr"));


  bool bHasAccount = false;
  assert(_pShareholder);
  assert(hasProcessRun());
  if(_pShareholder) 
     bHasAccount = _pShareholder->hasBankingInstr(BF::HOST,const_cast<DString&>(dstrxAcctNumber));
  return bHasAccount;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/**$Log:   Y:/VCS/BF iFAST/ifastbp/BankInstructionsProcess.cpp-arc  $
 * 
 *    Rev 1.105   May 04 2012 18:18:44   wp040100
 * IN 2915591 - Code Merge - Enabled validations for Bank Account Number and Back Account Holder Name
 * 
 *    Rev 1.104   Apr 24 2012 21:32:16   wp040039
 * PETP0187485 - Trade Entry And Processing
 * 
 *    Rev 1.103   Apr 04 2012 11:07:42   wp040039
 * PETP0187485-Registration Agent  Banking
 * 
 *    Rev 1.102   Mar 16 2012 17:43:10   wp040100
 * P0186484 FN05 - Contract Maturity Instruction Changes
 * 
 *    Rev 1.101   Mar 08 2012 12:34:18   jankovii
 * Sync up: IN 2859411 - P0186477_FN02_Interest Instruction-Err displayed on split type 'Amount' instrctn
 * 
 *    Rev 1.100   Mar 02 2012 16:41:20   wp040100
 * P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
 * 
 *    Rev 1.99   Feb 24 2012 18:39:40   if991250
 * Account Commitment
 * 
 *    Rev 1.98   Feb 21 2012 13:08:46   if991250
 * Trade Mat Sweep Instr Banks
 * 
 *    Rev 1.97   Feb 16 2012 17:30:32   if991250
 * fix compile error
 * 
 *    Rev 1.96   Feb 16 2012 17:27:04   if991250
 * added back check for _callerListKey.empty()
 * 
 *    Rev 1.95   Feb 16 2012 17:06:38   if991250
 * Trade MatSweep Bank
 * 
 *    Rev 1.94   Feb 02 2012 15:06:40   if991250
 * Maturity/Interest Instructions banking
 * 
 *    Rev 1.93   Nov 01 2010 09:07:48   wutipong
 * IN#2307118 - All slots in INSUAT1 return inactive message.
 * 
 *    Rev 1.92   Jul 05 2010 02:23:40   dchatcha
 * IN# 1984105 - Settlement from Broker trade will bring out shareholder default bank.
 * 
 *    Rev 1.91   Mar 31 2010 12:30:22   wutipong
 * IN2032885 Duplicate error messages recieved in Desktop
 * 
 *    Rev 1.90   Jan 13 2010 09:14:10   dchatcha
 * IN# 1971377 - R97_Static Data_File Processor&Bank are blank after deleting distribution option.
 * 
 *    Rev 1.89   Jan 11 2010 11:16:06   jankovii
 * IN 1973318 - No data in Historical Information screen for Fund Class level banking
 * 
 *    Rev 1.88   Nov 26 2009 13:20:14   jankovii
 * PET0166583 FN01 Static Data Changes Banking 
 * 
 *    Rev 1.87   Nov 17 2009 15:11:32   jankovii
 * PET0166583 FN01 Static Data Changes Banking 
 * 
 *    Rev 1.86   Dec 12 2006 12:22:34   popescu
 * Incident# 777131 - fixed the access violation error on trade pay instruct dialog when user switches from system check to eft and clicks on bank btn
 * 
 *    Rev 1.85   Nov 02 2006 11:45:10   ZHANGCEL
 * PET2217 FN26 - Add a new parameter for Bank Instruction title display
 * 
 *    Rev 1.84   Oct 18 2006 15:52:56   popescu
 * PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
 * 
 *    Rev 1.83   Sep 15 2006 19:42:56   popescu
 * STP 2217/13 - fixes
 * 
 *    Rev 1.82   Sep 10 2006 17:57:28   popescu
 * STP 2192/12
 * 
 *    Rev 1.81   Sep 07 2006 21:37:16   popescu
 * STP 2192/02
 * 
 *    Rev 1.80   Jul 31 2006 15:25:44   ZHANGCEL
 * PET2192 FN11 -- MgmtCo Banking related changes
 * 
 *    Rev 1.79   Dec 17 2004 11:28:30   popescu
 * PTS 10036680, restored file processor at shareholder level banking, for API use, and removed copying the file processor for SettlementTrade banking if bank is cloned. This is a synch-up from release 58.
 * 
 *    Rev 1.78   Nov 07 2004 14:05:50   popescu
 * PET 1117/06, synch changes
 * 
 *    Rev 1.77   Nov 04 2004 17:36:18   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.76   Sep 27 2004 18:01:50   HERNANDO
 * PTS10034084 - Replaced Bank Instruction Audit IDs with BKACCT.  (58.1 and up)
 * 
 *    Rev 1.75   Sep 23 2004 15:59:22   popescu
 * PET1094 FN06 - Absatzmeldung Files enhancement.
 * 
 *    Rev 1.74   Sep 23 2004 10:09:14   popescu
 * PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
 * 
 *    Rev 1.73   Sep 21 2004 14:30:46   ZHANGCEL
 * PET1094 - FN8 -- Roll back the code of ver1.71
 * 
 *    Rev 1.72   Sep 21 2004 13:25:58   HERNANDO
 * PET1094 FN06 - Absatzmeldung Files enhancement.
 * 
 *    Rev 1.71   Sep 08 2004 17:37:14   ZHANGCEL
 * PET1094-FN8 -- AdminFee related change
 * 
 *    Rev 1.70   Apr 27 2004 16:02:00   popescu
 * PTS 10029582, 10029578 similar issue, the validation should be done prior to remove the cloned bank lists
 * 
 *    Rev 1.69   Apr 01 2004 10:51:00   popescu
 * PTS 10028751,  synch-up from version 1.60.1.3, release 55.1.1
 * 
 *    Rev 1.68   Mar 12 2004 13:29:42   popescu
 * PTS 10027880, synch-up release 55.1.0.0, ver 1.60.1.2
 * 
 *    Rev 1.67   Mar 10 2004 13:13:38   HERNANDO
 * PET965 FN11 - Added getHistoricalParameters.
 * 
 *    Rev 1.66   Mar 09 2004 16:33:02   popescu
 * PET 965, FN 11, confirmation doesn't show -up anymore after switching to distribution/systematic banking, view mode from shareholder banking
 * 
 *    Rev 1.65   Mar 02 2004 16:35:30   HERNANDO
 * PET965 FN11 - Changed Distribution Banking.
 * 
 *    Rev 1.64   Mar 02 2004 11:17:46   YINGBAOL
 * PET965: SSB profile restriction: centrolize permission check at process layer.
 * 
 *    Rev 1.63   Feb 28 2004 16:11:40   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.62   Feb 11 2004 15:43:30   popescu
 * PET965.FN1 SSB Profile restriction, added a new method to remove cloned bank lists
  *
  *   Rev 1.61   Feb 09 2004 10:13:32   FENGYONG
  *PET965.FN1 SSB Profile restriction
  *
  *   Rev 1.60   Jan 13 2004 13:45:40   popescu
  *PET 910, System Integration Testing, Rel_55.0.0.2
  *Transaction Banking returns Data Not Found, if no data available
  *
  *   Rev 1.59   Oct 23 2003 17:48:58   FENGYONG
  *PET809 FN08 Direct trading enhancement
  *
  *   Rev 1.58   Oct 19 2003 18:34:54   popescu
  *CIBC PET 809, FN 13
  *
  *   Rev 1.57   Oct 19 2003 16:43:10   popescu
  *CIBC, PET809, FN 13 banking work
  *
  *   Rev 1.56   Oct 06 2003 12:42:38   popescu
  *Added banking support for DirectTrading enhancement
  *
  *   Rev 1.55   Oct 04 2003 15:54:48   popescu
  *CIBC PET 809, FN 13;
  *also cleaned-up BankSearch and BankList objects,
  *replaced with FinancialInstitutionList
  *
  *   Rev 1.54   Aug 07 2003 18:35:34   popescu
  *added new param that will help set the UI selection on the desired bank
  *
  *   Rev 1.53   Aug 07 2003 15:06:10   popescu
  *few changes for settlement banking
  *
  *   Rev 1.52   Jul 31 2003 19:27:50   popescu
  *validate the default banking record first before clonning it
  *
  *   Rev 1.51   Jun 25 2003 16:27:18   popescu
  *refresh improvements
  *
  *   Rev 1.50   Jun 18 2003 17:44:52   popescu
  *RRIF Banking Enhancement , business rules, bug fixes 
  *
  *   Rev 1.49   Jun 12 2003 15:39:14   popescu
  *restore cleaning the keys filter 
  *
  *   Rev 1.48   Jun 10 2003 16:10:40   popescu
  *Changed the SettlementTrade bank instructions files to match new design for bank instructions that are not on host
  *
  *   Rev 1.47   Jun 10 2003 11:51:10   popescu
  *work for Fubd/Class banking search
  *
  *   Rev 1.46   Jun 09 2003 17:39:42   popescu
  *Added support for fund and class search, still stopped at the Gui level, because it shouldn't be functional yet; do not know the id for the bank entity when seraching for bank using fund and class
  *
  *   Rev 1.45   Jun 03 2003 20:58:30   popescu
  *Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
  *
  *   Rev 1.44   Jun 01 2003 17:07:24   popescu
  *Systematic & Distribution banking work
  *
  *   Rev 1.43   May 31 2003 20:29:02   popescu
  *RRIF work part ||
  *
  *   Rev 1.42   May 31 2003 11:54:22   popescu
  *RRIF bank work
  *
  *   Rev 1.41   May 27 2003 18:29:00   popescu
  *due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
  *
  *   Rev 1.40   May 27 2003 13:13:52   popescu
  *RRIF Banking work
  *
  *   Rev 1.39   May 23 2003 10:03:54   popescu
  *Part of bank instructions cleaning up process, moved the bank types into the ifastids project
  *
  *   Rev 1.38   May 22 2003 14:11:24   popescu
  *Replaced name 'BankInstr' with 'BankInstructions'; 
  *simplified child lists getters for the Shareholder object
// 
//    Rev 1.49   Apr 02 2003 16:39:42   linmay
// clean for security
// 
//    Rev 1.48   Mar 21 2003 17:36:26   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.47   Nov 29 2002 15:46:24   ZHANGCEL
// Synced up to 1.46
// 
//    Rev 1.46   Oct 09 2002 23:53:04   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.45   Oct 08 2002 11:48:00   HSUCHIN
// PTS 10010112 - condition frame fix
// 
//    Rev 1.44   Sep 11 2002 09:51:16   KOVACSRO
// Added m_strUserAccessCode
// 
//    Rev 1.43   Sep 04 2002 15:45:44   PURDYECH
// Condition, comment and formatting cleanup
// 
//    Rev 1.42   Aug 29 2002 16:42:36   SMITHDAV
// Condition split.
// 
//    Rev 1.41   Aug 29 2002 12:54:14   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.40   Jul 10 2002 16:43:32   FENGYONG
// make API work
// 
//    Rev 1.39   Jul 05 2002 11:53:30   KOVACSRO
// setting BankIsType field.
// 
//    Rev 1.38   Jul 05 2002 08:56:12   PURDYECH
// Fixed include files
// Removed commented-out code.
// 
//    Rev 1.37   Jun 18 2002 16:41:22   HSUCHIN
// added shareholdernum and accountnum parameter passing for settlement
// 
//    Rev 1.36   Jun 16 2002 13:07:00   HSUCHIN
// added settlementtradebank to validate all
// 
//    Rev 1.35   Jun 13 2002 17:14:26   HSUCHIN
// added settlement copy on doOk
// 
//    Rev 1.34   Jun 11 2002 21:27:00   HSUCHIN
// added support for settlement
// 
//    Rev 1.33   Jun 07 2002 17:40:32   KOVACSRO
// passing a trade pointer rather than several strings
// 
//    Rev 1.32   03 Jun 2002 15:17:40   KOVACSRO
// Added PayMethod
// 
//    Rev 1.31   24 May 2002 15:18:52   KOVACSRO
// Fund and Client bank.
// 
//    Rev 1.30   22 May 2002 18:23:52   PURDYECH
// BFData Implementation
// 
//    Rev 1.29   27 Mar 2002 19:54:34   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.28   Jul 04 2001 11:19:34   ZHANGCEL
// Sync up with 1.24.1.1
// 
//    Rev 1.28   Jun 26 2001 10:43:12   ZHANGCEL
// Sync up to 1.24.1.1
// 
//    Rev 1.27   13 Jun 2001 11:00:30   KOVACSRO
// Added TradesTransType field.
// 
//    Rev 1.26   15 May 2001 15:38:28   YINGZ
// data group id clean up
// 
//    Rev 1.25   11 May 2001 16:33:36   YINGZ
// code sync up
// 
//    Rev 1.24   30 Apr 2001 10:48:12   BUZILAMI
// fix Trade bank init
// 
//    Rev 1.23   Apr 28 2001 20:05:12   WINNIE
// fix banking update in trade
// 
//    Rev 1.22   27 Apr 2001 14:47:20   BUZILAMI
// Commit fix
// 
//    Rev 1.21   26 Apr 2001 13:22:24   BUZILAMI
// commit fix
// 
//    Rev 1.20   26 Apr 2001 10:33:42   BUZILAMI
// fix
// 
//    Rev 1.19   Apr 18 2001 15:28:24   WINNIE
// set deault value for bank
// 
//    Rev 1.18   16 Apr 2001 14:58:26   BUZILAMI
// initialization of custom trade bank
// 
//    Rev 1.17   16 Apr 2001 14:27:38   BUZILAMI
// FIX
// 
//    Rev 1.16   12 Apr 2001 15:27:38   BUZILAMI
// Trading Bank Changes
// 
//    Rev 1.15   10 Apr 2001 16:12:32   BUZILAMI
// distrib bank changes
// 
//    Rev 1.14   Apr 10 2001 10:50:10   YINGBAOL
// fix
// 
//    Rev 1.13   Apr 09 2001 15:49:18   YINGZ
// fix coa problem
// 
//    Rev 1.12   Apr 09 2001 15:13:18   YINGBAOL
// distiguish pendingTrade and Transaction History
// 
//    Rev 1.11   06 Apr 2001 18:58:10   BUZILAMI
// fix
// 
//    Rev 1.10   06 Apr 2001 15:50:56   BUZILAMI
// fix
// 
//    Rev 1.9   Apr 06 2001 13:07:06   YINGBAOL
// samll fix
// 
//    Rev 1.8   Apr 03 2001 15:22:50   YINGBAOL
// add BankTransactionList and it's logic
// 
//    Rev 1.7   30 Mar 2001 17:09:22   BUZILAMI
// Systematic bank changes
// 
//    Rev 1.6   27 Mar 2001 17:03:16   BUZILAMI
// fixes
// 
//    Rev 1.5   27 Mar 2001 11:48:12   BUZILAMI
// modeless set focus fix
// 
//    Rev 1.4   20 Mar 2001 16:00:08   BUZILAMI
// address changes
// 
//    Rev 1.3   16 Mar 2001 16:33:44   BUZILAMI
// added some fields
// 
//    Rev 1.2   07 Mar 2001 15:41:56   BUZILAMI
// Broker, Branch, SlsRep Bank Instructions changes
// 
//    Rev 1.1   Feb 22 2001 15:24:36   BUZILAMI
// added search for bank using Broker, Branch and sales Rep
// 
//    Rev 1.0   Feb 21 2001 16:03:52   BUZILAMI
// Initial revision.
// 
  *
 *
 */

