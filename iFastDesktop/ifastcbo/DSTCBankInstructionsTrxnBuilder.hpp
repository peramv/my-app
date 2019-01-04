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
//    Copyright 2001 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCBankInstructionsTrxnBuilder.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : March 2001
//
// ^CLASS    : DSTCBankInstructionsTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : Handle banking instruction for shareholder defaults, systematic banking
//
//
//******************************************************************************

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declaration
class DistributorRepository;
class FundBankInstructionsListRepository;
class ShareholderBankInstructionsList;
class FundBankInstructionsList;
class ClientBankInstructionsList;
class HostTransactionContainer;
class Shareholder;
class DirectTradingBankInstructionsList;
class AgentBankInstructionsListRepository;

class DSTCBankInstructionsTrxnBuilder
{
public:
   static SEVERITY buildTransactions(DSTCWorkSession &workSession, 
      BFAbstractCBO* pBFBase, HostTransactionContainer* pTrCont,
      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE);

   static void buildTrxnKey(DString& strKey, Shareholder *pShareholder);
   static const void  buildTrxnKeyForBankingInstr ( DString &strKey, const DString& dstrBankEntityType,
                                                    const Shareholder* pShareholder);
   static void buildTrxnKey(DString& strKey, 
      ClientBankInstructionsList* pClientBankInstructionsList);
   static void buildTrxnKey(DString &strKey, 
      FundBankInstructionsList *pFundBankInstructionsList);
   static SEVERITY buildDefaultShareholderTransactions(
      DSTCWorkSession &workSession, 
      Shareholder *pShareholder, 
      HostTransactionContainer *pTrCont);
   static SEVERITY buildDirectTradingTransactions(
      DSTCWorkSession &workSession, 
      Shareholder *pShareholder, 
      HostTransactionContainer *pTrCont);
   static SEVERITY buildDistributorTransactions(DSTCWorkSession &workSession, 
      DistributorRepository *pDistributorRepository, 
      HostTransactionContainer *pTrCont);
   static SEVERITY buildClientTransactions(DSTCWorkSession &workSession, 
      ClientBankInstructionsList *pBankList, HostTransactionContainer *pTrCont);
   static SEVERITY buildFundTransactions(DSTCWorkSession &workSession, 
      FundBankInstructionsListRepository *pBankList, HostTransactionContainer *pTrCont);
   static SEVERITY buildFundGroupTransactions(DSTCWorkSession &workSession, 
      FundBankInstructionsListRepository *pBankList, HostTransactionContainer *pTrCont);
   static SEVERITY DSTCBankInstructionsTrxnBuilder::buildFundSponsorTransactions (
      DSTCWorkSession &workSession, 
      FundBankInstructionsListRepository *pFundBankInstructionsListRepository, 
      HostTransactionContainer *pTrCont);
   static SEVERITY DSTCBankInstructionsTrxnBuilder::buildRegAgentTransactions (
	  DSTCWorkSession &workSession, 
	  AgentBankInstructionsListRepository *pAgentBankInstructionsListRepository, 
	  HostTransactionContainer *pTrCont);
private:
   static SEVERITY buildShareholderTransactions(
      DSTCWorkSession &workSession, 
      Shareholder *pShareholder, 
      ShareholderBankInstructionsList *pShareholderBankInstructionsList, 
      HostTransactionContainer *pTrCont);
   static SEVERITY buildDirectTradingTransactions(
      DSTCWorkSession &workSession, 
      Shareholder *pShareholder, 
      DirectTradingBankInstructionsList *pDirectTradingBankInstructionsList, 
      HostTransactionContainer *pTrCont);
  static SEVERITY buildShareholderBankTransactions (
      DSTCWorkSession &workSession, 
      Shareholder *pShareholder, 
      ShareholderBankInstructionsList *pShareholderBankInstructionsList, 
      HostTransactionContainer *pTrCont);
  static  SEVERITY buildAccountBankTransactions (
      DSTCWorkSession &workSession, 
      Shareholder *pShareholder, 
      ShareholderBankInstructionsList *pShareholderBankInstructionsList, 
      HostTransactionContainer *pTrCont);
   //objects of this class gets never created. Class used only for his static methods
   DSTCBankInstructionsTrxnBuilder()
   {};
   ~DSTCBankInstructionsTrxnBuilder()
   {};
};

