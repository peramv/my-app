#pragma once
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
//
//******************************************************************************
//
// ^FILE   : MFAccount.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MFAccount
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#define EXTRACT_VALUE(s, val) \
      pos = s.find (I_(",")); \
      val = s.substr (0, pos);

#define CHOP_STRING(s) \
         pos = s.find (I_(",")); \
         pos = pos != DString::npos && pos + 1 <= s.length() ? pos + 1 : DString::npos; \
         if (pos != DString::npos) \
            s = s.substr (pos); \
         else \
            s = NULL_STRING;

class AbstractAllocList;
class ACBList;
class AccountCommitment;
class AccountContractList;
class AccountDistributionList;
class AccountEntityXref;
class AccountEntityXrefObject;
class AcctGuaranteeGuardOptList;
class AccountHoldingsByCurrencyList;
class AccountReviewList;
class AccountTradesList;
class AcctCategoryList;
class AcctControlRecordList;
class AcctSplitCommList;
class AgentList;
class AmsFundAllocList;
class AMSCodeList;
class AsPensionPlan;
class BranchList;
class BrokerList;
class CertificateList;
class COANavig;
class ContractInfoList;
class DefAcctAllocList;
class ErrMsgRulesList;
class ESoPInfo;
class Entity;
class FeeParamList;
class FreeUnitList;
class FundDetailList;
class GroupFundList;
class GroupList;
class HypoRedCriteria;
class IntermediaryList;
class MatchTransferList;
class MasterContractList;
class MFAccountHoldingList;
class PendingTradeList;
class PensionInfo;
class RESPInfo;
class RESPTransactionsList;
class RRIF_LIF_LRIF_InfoList;
class RSPContributionList;
class Shareholder;
class SystematicList;
class TaxTypeRule;
class TradeMinAmtCheck;
class TransactionList;
class AcctMailingOverrideList;
class Demographics;
class AMSMstrList;
class DirectTradingList;
class FundMgmtSettlementInstrList;
class InventorySummaryList;
class TaxExemptAuthorizationList;
class ContractMaturityInstructionList;
class AcctSettlementInstrList;
class UserDefMatList;
class Broker;
class AcctCutOffTimesList;
class AMSAcctLvlList;
class DefFundAllocList;
class AcctLvlSttlmntRuleList;
class RegDocumentList;
class TradeAuthorization;
class InvestorAuthorizationList;
class InvestorAuthorization;
class RESPBeneficiaryAllocationList;
class RESPTransferList;
class RESPTransactionTypesList;
class RESPBeneficiaryList;
class RESPTradeSearchCriteria;
class RESPInfoUpdateValidationList;
class FeeModelList;
class ProdPortfolioFundList;
class ProdPortfolioInfoList;
class ProdPortfolioPlanInfoList;
class MatSweepInstrList;
class AcctOwnershipAllocationList;
class AcctRegDetailsList;
class EntityRegDetailsList;
class EntityRegJurisDetailsList;
class FinInstRegDetlList;
class AWDHistoryWorkList;
class AlertMessageList;
class RegPlanTransferList;
class AcctRoundingRuleList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

typedef std::vector< AccountEntityXrefObject * > ACCTENTITYOBJ_VECTOR;
typedef std::vector< DString > ENTITIES_VECTOR;
typedef std::vector< DString > ENTITY_ID_LIST;

namespace ACCOUNT_GROUPING
{
   extern IFASTCBO_LINKAGE const long ACCOUNT_INFO;
   extern IFASTCBO_LINKAGE const long ACCOUNT_RESP_INFO;
   extern IFASTCBO_LINKAGE const long VALUE_VARIATION;
}

class IFASTCBO_LINKAGE MFAccount : public MFCanBFCbo, private boost::noncopyable
{
public:
//flags used for grouping

   MFAccount( BFAbstractCBO &parent );
   virtual ~MFAccount();

   enum AT_ACCOUNT
   {
      ACCOUNT_NOT_EFFECT = 1, 
      SALES_REP_NOT_EFFECT,
      ACCOUNT__SALES_REP_OK
   };

   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& accountNum, const DString& shrNum );
   SEVERITY init( const BFData& refData );
   SEVERITY init( const DString& strAccNum, const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);

   SEVERITY getAccountHoldingList( MFAccountHoldingList *&pMFAccountHoldingList, 
                                   const BFDataGroupId& idDataGroup, bool inquireDatabase = true );
   SEVERITY getAcctMailingOverrideList( AcctMailingOverrideList*& pAcctMailingOverrideList, 
                                           const BFDataGroupId& idDataGroup, bool inquireDatabase = true );
   SEVERITY getACBList( ACBList *&pACBList, 
                        const BFDataGroupId& idDataGroup, 
                        const DString& strFund = NULL_STRING,
                        const DString& strClass = NULL_STRING,
                        bool inquireDatabase = true );
   SEVERITY getFreeUnitList( FreeUnitList *&pFreeUnitList, 
                             const BFDataGroupId& idDataGroup, bool inquireDatabase = true );

   SEVERITY getFreeUnitList(FreeUnitList *&pFreeUnitList, 
                            const BFDataGroupId& idDataGroup,
                            const DString& AcctLvlDSCFund,
                            const DString& AllFundMode,
                            const DString& AllFundGroupMode,
                            bool inquireDatabase = true);

   SEVERITY getFreeUnitListBy(FreeUnitList *&pFreeUnitList, 
                              const BFDataGroupId& idDataGroup,
                              const DString& FundCode,
							  const DString& ClassCode,
                              const DString& FundGroup,
                              bool inquireDatabase = true);

   SEVERITY getAccountHoldingsByCurrencyList( AccountHoldingsByCurrencyList *&pAccountHoldingsByCurrencyList , 
                                              const BFDataGroupId& idDataGroup, bool inquireDatabase = true );
   //bStartEmptyList should be always false if allFundsMode is true
   SEVERITY getTransactionsList( TransactionList *&pTransactionsList, 
                                 const BFDataGroupId& idDataGroup, bool allFundsMode = false, 
                                 bool inquireDatabase = true, bool bStartEmptyList = false );
   SEVERITY getPendingTradesList( PendingTradeList *&pPendingTradesList, 
                                  const BFDataGroupId& idDataGroup, int nNumEntry = -1,
                                  DString ExtTransNum = NULL_STRING,bool bRefresh = false );
   bool IsTransactionPending( const DString& ExtTransNum );
   SEVERITY getSystematicList( SystematicList *&pSystematicList, 
                               const BFDataGroupId& idDataGroup, 
                               bool inquireDatabase = true,
                               const DString &payType = NULL_STRING,
                               const DString &amount = NULL_STRING,
                               const DString &amountType= NULL_STRING );
   SEVERITY getDirectTradingList( DirectTradingList *&pDirectTradingList, 
                               const BFDataGroupId& idDataGroup, bool inquireDatabase = true );    
   SEVERITY getAccDistributionsList(AccountDistributionList *&pAccDistributionList,
      const BFDataGroupId& idDataGroup, bool inquireDatabase = true, bool bCreate = true );
   SEVERITY getRRIF_LIF_LRIF_InfoList(RRIF_LIF_LRIF_InfoList *&pRRIF_LIF_LRIF_InfoList, 
      const BFDataGroupId& idDataGroup, bool inquireDatabase = true,bool bPermit = true );
   SEVERITY getRESPInfo( RESPInfo *&pRESPInfo, const BFDataGroupId& idDataGroup, bool inquireDatabase = true );
   SEVERITY getRESPTransactionsList( RESPTransactionsList *&pRESPTransactionsList,
                                     const DString& dstrHistoryPending,
                                     const BFDataGroupId& idDataGroup);
   SEVERITY getRESPTransactionsList( RESPTransactionsList *&pRESPTransactionsList, 
                                     const DString& dstrHistoryPending,
                                     const DString& dstrTransId,
                                     const DString& dstrRESPBenefId,
                                     const DString& dstrRESPBenefName,
                                     const DString& dstrFromDate,
                                     const DString& dstrToDate,
                                     const DString& dstrTransTypeDesc,
                                     const DString& dstrTfrStat,
                                     const DString& dstrRepHRDC,
                                     const BFDataGroupId& idDataGroup, 
                                     bool inquireDatabase = true );

   SEVERITY getRESPTransactionTypesList (RESPTransactionTypesList *&pRESPTransactionTypesList,
                                         const DString &dstrTransId,
                                         const DString& dstrHistoryPending,
                                         const BFDataGroupId& idDataGroup,
                                         bool inquireDatabase = true );

   SEVERITY getRESPBeneficiaryList (RESPBeneficiaryList *&pRESPBeneficiaryList,
                                    const BFDataGroupId& idDataGroup,
                                    bool inquireDatabase = true);

   SEVERITY getMatSweepInstrList (MatSweepInstrList *&pMatSweepInstrList,
                                  const DString& instructionType,
                                  const DString& dstrLevel,
                                  const DString& dstrFund,
                                  const DString& dstrClass,
                                  const DString& dstrTransNum,
                                  const DString& dstrTransId,
                                  const DString& dstrIntInvestId,
                                  const DString& dstrPrincipalAmount,
                                  const DString& dstrAccuredAmount,
                                  const BFDataGroupId& idDataGroup,
                                  bool inquireDatabase = true);

   SEVERITY removeMatSweepInstrList ();

   SEVERITY removeRegDocumentList(const DString& dstrEntityId,
                                 const BFDataGroupId& idDataGroup);

   SEVERITY getRESPTradeSearchCriteria (RESPTradeSearchCriteria *&pRESPTradeSearchCriteria, 
                                       const DString &dstrTransId,
                                       const DString &dstrTradeDate,
                                       const DString &dstrHistoryPending,
                                       const BFDataGroupId& idDataGroup);

   SEVERITY getContractInfoList( ContractInfoList*& pContractInfoList, 
                                 const BFDataGroupId& idDataGroup, 
                                 bool inquireDatabase = true );
   
   SEVERITY getRegPlanTransferList( RegPlanTransferList*& pRegPlanTransferList, const BFDataGroupId& idDataGroup, bool inquireDatabase = true);

   SEVERITY getCertificateList( CertificateList *&pCertificateList, 
                                const BFDataGroupId& idDataGroup, 
                                bool inquireDatabase = true );
   SEVERITY getESoPInfo( ESoPInfo *&pESoPInfo, const BFDataGroupId& idDataGroup, bool bCreate = true);
   SEVERITY getRSPContributionList( RSPContributionList *&pRSPContributionList, const BFDataGroupId& idDataGroup, bool inquireDatabase = true);
   SEVERITY getTransactionHistoryList ( TransactionList *&pTransactionList, 
                                        const DString& dstrFundCode, const DString& dstrClassCode, 
                                        const DString& dstrNumEntry, const DString& allFundsMode, 
                                        const DString& strReqTransid,
                                        const BFDataGroupId& idDataGroup, bool inquireDatabase = true,
                                        DString ExtTransNum = NULL_STRING, bool receiveAll = false,
                                        DString TransNum = NULL_STRING,
                                        const DString& strWireOrder = NULL_STRING);
   SEVERITY getProdPortfolioPlanInfoList (ProdPortfolioPlanInfoList*& pProdPortfolioPlanInfoList,
                                          const DString& prodPortfolioUUID,
                                          const BFDataGroupId& idDataGroup);
   SEVERITY getProdPortfolioInfoList (ProdPortfolioInfoList*& pProdPortfolioPlanInfoList,
                                      const BFDataGroupId& idDataGroup,
                                      bool bViewCall = false);
   void getLastActiveTransactionHistoryList ( TransactionList *&pTransactionList, const BFDataGroupId& idDataGroup );

   void parseName (const DString &originalName, DString &newName);

   SEVERITY doesFundHaveCertificateUnits (const DString &fundCode, const DString &classCode, const BFDataGroupId& idDataGroup, bool &bFoundCertificate);

   SEVERITY getMatchTransferList ( MatchTransferList *&pMatchTransferList,
                                   DString& dstrTransId, const BFDataGroupId& idDataGroup,
                                   bool inquireDatabase = true );
   SEVERITY getAsPensionPlan( AsPensionPlan *&pAsPensionPlan, const BFDataGroupId& idDataGroup, bool inquireDatabase = true );
   SEVERITY getAcctSplitCommList( AcctSplitCommList *&pAcctSplitCommList, const BFDataGroupId& idDataGroup, bool inquireDatabase = true);
   SEVERITY getHypoRedCriteria( HypoRedCriteria *&pHypoRedCriteria, const BFDataGroupId& idDataGroup);
   SEVERITY getAccountCommitment( AccountCommitment *&pAccountCommitment, const BFDataGroupId& idDataGroup, bool createNew = false);

   SEVERITY getAcctSettlementRuleList( AcctLvlSttlmntRuleList *&pAcctSettlementRuleList, 
                                       const BFDataGroupId& idDataGroup,
                                       bool inquireDatabase = true );
   SEVERITY isNonRegNonResident(DString &dstrNonRegNonResident, const BFDataGroupId &idDataGroup);

   bool isSettlementRuleExist( const BFDataGroupId& idDataGroup );
   bool changeTaxType(const DString& taxType, const BFDataGroupId& idDataGroup ); 
   bool isAccountAttachedAMSC(const BFDataGroupId& idDataGroup);


   virtual void getField( const BFFieldId& idField, DString &strFieldValue, 
                          const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
   SEVERITY cloneFromModel( const DString& modelAccount, const BFDataGroupId& idDataGroup );
   SEVERITY rollbackClone( const BFDataGroupId& idDataGroup );

   // Move fundClassTradeMinimum to trade
   /*SEVERITY fundClassTradeMinimum ( const DString&  strFundCode, const DString&  strClassCode, const DString&  strTransType,
                                    const DString&  strAmountType, const DString&  strAmount, const DString&  strEffectiveDate, 
                                    const DString&  strSettleCurrency, DString &strInitial, const BFDataGroupId& idDataGroup);*/
   double fundClassBalance ( const DString &fundCode, 
                             const DString &classCode, 
                             bool &recordFound, 
                             const BFFieldId &idField, 
                             const BFDataGroupId &idDataGroup, 
                             const DString &asOfDate = NULL_STRING);
   bool pendingOfFundExist (const DString fundCode, const DString classCode, const DString transtype, const BFDataGroupId& idDataGroup);
   bool pendingOfFundExist (const DString& fundCode, const DString& classCode, const BFDataGroupId& idDataGroup);
   SEVERITY canTradeFundClass ( const DString& fundCode, const DString& classCode, const DString& transType, 
                                const DString& tradeDate, const BFDataGroupId& idDataGroup );
   /*SEVERITY lockedInFundClass ( const DString& acctNum, const DString& fundCode, const DString& classCode, 
                              const DString& tradeDate, const BFDataGroupId& idDataGroup );*/
   SEVERITY lockedInFundClass ( const DString& fundCode, const DString& classCode, 
                                const DString& tradeDate, const BFDataGroupId& idDataGroup );
   SEVERITY fundClassInGroup(const DString& fundCode, const DString& classCode,  
                             const DString& tradeDate, const BFDataGroupId& idDataGroup);
   bool isAccountModel( const DString& entityId, const BFDataGroupId& idDataGroup );
   bool isAcctDTAEligible( const BFDataGroupId& idDataGroup );
   int  CheckEffectiveForAT(DString strEffective,const BFDataGroupId& idDataGroup);
   bool isATAllowed( const BFDataGroupId& idDataGroup );
   SEVERITY loadIntermCodeSubstitutionList( const BFDataGroupId& idDataGroup );
   SEVERITY getTaxTypeRule ( TaxTypeRule *&taxTypeRule, const BFDataGroupId& idDataGroup);
   SEVERITY getLIPRateExist(DString &strLIPRateExist, const BFDataGroupId& idDataGroup);
   SEVERITY groupContributMax ( const BFDataGroupId& idDataGroup, DString &strOut );
   SEVERITY groupLockedIn ( const BFDataGroupId& idDataGroup, DString &strOut );
   SEVERITY getErrMsg( DString dstrErrNum, long lErrConditionId, 
                       long lWarnConditionId, const BFDataGroupId& idDataGroup, DString idiStr = NULL_STRING );
   bool isJoint( const BFDataGroupId& idDataGroup );
   //gets the this pointer
   virtual BFAbstractCBO *getTopLevelAncestor();
   void getInitialAccountNumber( DString &initAccountNum );
   void  setAccountDesignation(const BFDataGroupId& idDataGroup);
   void  setIntermAccountReadOnly();

   SEVERITY validateMoneyInTFSA(const BFDataGroupId& idDataGroup);
   SEVERITY canPurchase ( const DString& dstrTradeDate, const BFDataGroupId& idDataGroup );
   SEVERITY escrowPurchase ( const DString&  dstrTradeDate, const BFDataGroupId& idDataGroup ) ;

   SEVERITY canRedeem ( const DString& dstrTradeDate, const BFDataGroupId& idDataGroup );
   SEVERITY escrowRedeem ( const DString&  dstrTradeDate, const BFDataGroupId& idDataGroup ) ;

   SEVERITY canTrfExchIn ( const DString& dstrTradeDate, const BFDataGroupId& idDataGroup );
   SEVERITY canTrfExchOut ( const DString& dstrTradeDate, const BFDataGroupId& idDataGroup );
   SEVERITY exchEscrow ( const DString&  dstrTradeDate, const BFDataGroupId& idDataGroup );
   SEVERITY addrEscrow ( const BFDataGroupId& idDataGroup );
   SEVERITY canTrade( const DString& TransType, const BFFieldId& idField, const DString& dstrTradeDate, const BFDataGroupId& idDataGroup );
   SEVERITY canTrade( const DString& TransType, const DString& dstrTradeDate, const BFDataGroupId& idDataGroup );
   bool accountActive ( const DString& dstrDate, const BFDataGroupId& idDataGroup );
   SEVERITY trferEscrow ( const DString&  dstrTradeDate, const BFDataGroupId& idDataGroup );
   SEVERITY canRedeemFundClass ( const DString& fundCode, const DString& classCode, 
                                 const DString& tradeDate, const BFDataGroupId& idDataGroup );

   SEVERITY canExchOutFundClass ( const DString& fundCode, const DString& classCode, 
                                  const DString& tradeDate, const BFDataGroupId& idDataGroup );

   SEVERITY canContributeFundClass ( const DString& fundCode, const DString& classCode, 
                                     const DString& transType,
                                     const DString& tradeDate, const BFDataGroupId& idDataGroup );
   SEVERITY canContributeProtectedFund ( const DString fundCode,
                                         const DString classCode, 
                                         const BFDataGroupId& idDataGroup );

   SEVERITY purchaseGICAllow ( DString &dstrFund, const BFDataGroupId& idDataGroup);
   SEVERITY AMSFundAllow ( const DString &dstrFund, const DString &dstrClass, const BFDataGroupId& idDataGroup);
   SEVERITY getAccountReviewList( AccountReviewList *&, const BFDataGroupId& idDataGroup, bool = true);
   SEVERITY getAccountTradesList(AccountTradesList *&pAccountTradesList, const BFDataGroupId& idDataGroup);
   SEVERITY getUserDefMatList( UserDefMatList *&, const BFDataGroupId& idDataGroup, bool = true, const DString& LegalMaturityDate = NULL_STRING, const DString& ContractType = NULL_STRING );
   void getBeneficiaries(  ACCTENTITYOBJ_VECTOR & vBenefEntities, const BFDataGroupId& idDataGroup );
   void getAcctOwnerEntities(  ENTITIES_VECTOR & acctOwnerEntities, const BFDataGroupId& idDataGroup );
   void getAnnitants(  ACCTENTITYOBJ_VECTOR & vAnnitantEntities, const BFDataGroupId& idDataGroup );
   void getAcctOwners(  ACCTENTITYOBJ_VECTOR & vAcctOwnerEntities, const BFDataGroupId& idDataGroup );
   void getSpouseEntity(  ACCTENTITYOBJ_VECTOR & vSpouseEntitiesVertor, bool bSpouse, Entity *&pEntity, const BFDataGroupId& idDataGroup );
   bool isSpousalBeneficiary (const DString &dstrEntityIdIn, const BFDataGroupId &idDataGroup);
   bool isChildBeneficiary (const DString &dstrEntityIdIn, const BFDataGroupId &idDataGroup);
   bool isBeneficiary (const DString &dstrEntityIdIn, const BFDataGroupId &idDataGroup);
   void GetEntityIdForAcctOwnerSeq1( const BFDataGroupId& idDataGroup, DString& entityId );
   //void GetEntityInfoForAcctOwner( const BFDataGroupId& idDataGroup, const DString& seqNumber, 
      //                             DString& entityIds, DString& firstName, DString& lastName );
   bool pendingRedemptionExist( const DString& dstrfundCode, const DString& dstrclassCode, 
                                const BFDataGroupId& idDataGroup );

   bool isSettleRedeptionAllowed(const BFDataGroupId& idDataGroup  );

   /* move logic to trade
   SEVERITY getTradeMinAmtCheck(const DString&  strAccountNum,const DString&  strFundCode, 
                                const DString&  strClassCode, const DString&  strTransType, const DString&  strAmountType, 
                                const DString&  strAmount, const DString&  strEffectiveDate, const DString&  strSettleCurrency,
                                TradeMinAmtCheck*& pTradeMinAmtCheck, const BFDataGroupId& idDataGroup);*/
   SEVERITY checkSpouseValidSINExists( bool &bSINExists, const BFDataGroupId& idDataGroup );
   SEVERITY checkSpouseTransfereeValidSINExists( bool &bSINExists, const BFDataGroupId& idDataGroup );


   SEVERITY getDofBirthofOwnerSeq01( DString& dstrDofBirth, const BFDataGroupId& idDataGroup );
   SEVERITY getSINAcctOwnerSeq01( DString& dstrSIN, const BFDataGroupId& idDataGroup );

   int getAgeofOwnerSeq01( const BFDataGroupId& idDataGroup );
   SEVERITY getGroupFundListFromGroup( DString dstrGroupCode, DString dstrFundCode, const BFDataGroupId& idDataGroup, GroupFundList *& pGroupFundList ); 
   SEVERITY getFundListFromGroupAndPortfolio( ProdPortfolioFundList *&pProdPortfolioFundList,
                                              const DString& dstrGroupCode,
                                              const DString& dstrProdPortfolioUUID, 
                                              const BFDataGroupId& idDataGroup);
   SEVERITY getMasterContractListByPortfolio( MasterContractList *&pMasterContractList,
                                              const BFDataGroupId& idDataGroup);
   static SEVERITY validateAccountNum(const DString& strAccountNum, DSTCWorkSession &parent);
   SEVERITY getFeeParamList(FeeParamList *&pFeeParamList,const BFDataGroupId& idDataGroup,bool inquireDatabase = true);
   SEVERITY refreshDataObject();
   SEVERITY getDofDeathofOwnerSeq01( DString& dstrDofDeath, const BFDataGroupId& idDataGroup );
   SEVERITY getDofDeathofEntityType( const DString& dstrEntityType, DString& dstrDofDeath, const BFDataGroupId& idDataGroup );//Modified for INC0033364
   SEVERITY getPensionInfo( PensionInfo *&pPensionInfo, const BFDataGroupId& idDataGroup, bool inquireDatabase = true);
   SEVERITY validateTaxTypeAcctType( const BFDataGroupId& idDataGroup );
   void getAcctName(DString &dstrAcctName, const BFDataGroupId& idDataGroup, bool kanji=true);
   SEVERITY getAMSFundAllocList(const DString& dstrAMSType, const DString &dstrEffectiveDate, AmsFundAllocList* &pAmsFundAllocList, const BFDataGroupId& idDataGroup, bool bCreate=true);
   //this method will return a 100% default account allocation list
   SEVERITY getAMSAcctAllocList(AbstractAllocList* &pAmsAcctAllocList, const BFDataGroupId& idDataGroup, bool bCreate=true);
   SEVERITY getAccountContractList( AccountContractList*& pAccountContractList, 
                                    DString dstrAccountNum, DString dstrFundCode,
                                    DString dstrClassCode, const BFDataGroupId& idDataGroup );
   SEVERITY getAcctCategoryList(AcctCategoryList* &pAcctCategoryList, const BFDataGroupId& idDataGroup, bool bCreate=true,  bool bRefresh = false);
   SEVERITY getRegDocumentsList( RegDocumentList* &pRegDocumentList, 
                                 const DString& dstrEntityId,
                                 const BFDataGroupId& idDataGroup,	
                                 bool bCreate = true,
								 bool bAcctRegDocListForDeadEntity = false);

   SEVERITY getRegDocumentsList( RegDocumentList* &pRegDocumentList, 
                                 const DString& dstrEntityId,
                                 const DString& dstrComplyRule,
                                 const DString& dstrRegStandard,
                                 const BFDataGroupId& idDataGroup,	
                                 bool bCreate = true,
								 bool bAcctRegDocListForDeadEntity = false);

  bool isRegDocumentsOutStanding( const DString& dstrEntityId,
                                  const DString& dstrComplyRule,                                  
                                  const BFDataGroupId& idDataGroup,	
                                  bool bCreate = true,
								  bool bAcctRegDocListForDeadEntity = false); 

  SEVERITY getBrokerFundAllow(const DString& dstrFundCode, 
                              const DString& dstrClassCode,
                              BrokerList *&pBrokerList,
                              const BFDataGroupId& idDataGroup);

  SEVERITY getAgentFundAllow(const DString& dstrFundCode,
                             const DString& dstrClassCode,
                             AgentList *&pAgentList,
                             const BFDataGroupId& idDataGroup);
  
   SEVERITY validateToFundClassAgainstFundEligible(const DString& dstrFundCode,
                                                   const DString& dstrClassCode,
                                                   const BFDataGroupId &idDataGroup);

   SEVERITY getTradeAuthorization (TradeAuthorization *&pTradeAuthorization,
                                   const DString &recordType,
                                   const DString &transNum,
                                   const DString &transId,
                                   const DString &authorization,
                                   const BFDataGroupId &idDataGroup);
   SEVERITY getTradeAuthorization (TradeAuthorization *&pTradeAuthorization,
                                   const BFDataGroupId &idDataGroup);
   SEVERITY getFundMgmtSettlementInstrList( FundMgmtSettlementInstrList *&pFundMgmtSettlementInstrList, 
                                            const BFDataGroupId& idDataGroup, 
                                            bool binquireDatabase = true );

   SEVERITY getSettlementInstrList( AcctSettlementInstrList *& pAcctSettlementInstrList, 
                                    const BFDataGroupId& idDataGroup,
                                    bool bInquireDatabase = true );

   SEVERITY getInventorySummaryList( InventorySummaryList*& pInventorySummaryList, 
                                     DString dstrAccountNum, DString dstrFundCode,
                                     DString dstrClassCode, DString dstrActiveOnly,
                                     const BFDataGroupId& idDataGroup );
   SEVERITY getTaxExemptAuthorizationList( TaxExemptAuthorizationList*& pTaxExemptAuthorizationList, 
                                           DString dstrAccountNum, const BFDataGroupId& idDataGroup, bool inquireDatabase = true );

   SEVERITY getContractMaturityInfoList( ContractMaturityInstructionList *&pContractMaturityInstructionList,
                                         const DString& dstrAccountNum, DString& dstrCotAcctRid,
                                         const DString& dstrContractType, const DString& dstrContractTypeId,
                                         const BFDataGroupId& idDataGroup, bool inquireDatabase = true  );

   SEVERITY getRESPBenefAllocationList ( RESPBeneficiaryAllocationList *&pRESPBeneficiaryAllocationList, 
                                         const BFDataGroupId &idDataGroup,
                                         const DString &transId,
                                         const DString &tradeType = I_("Pend"));
   SEVERITY getRESPTransferList ( RESPTransferList *&pRESPTransferList, 
                                  const BFDataGroupId &idDataGroup,
                                  const DString &accountNumTo,
                                  const DString &transId,
                                  const DString &transType,
                                  const DString &tradeDate,
                                  const DString &depositType,
                                  const DString &redCode, 
                                  const DString &amount,
                                  const DString &tradeType = I_("Pend"));
   bool isCategoryExist( const BFDataGroupId& idDataGroup, const DString& dstrCategoryType );
   bool isAMSRBOnly(const BFDataGroupId& idDataGroup);
   bool isAMSAnOption(const BFDataGroupId& idDataGroup);

   SEVERITY getEntitySubstList (const BFDataGroupId &idDataGroup, DString &entitySubstList, bool isDeathClaim);
   SEVERITY getFullEntityName (const BFDataGroupId &idDataGroup, const DString &dstrEntityId, DString &dstrFullEntityName);
   SEVERITY getDeadEntities (const BFDataGroupId &idDataGroup, 
                             DString &entitySubstList);

   SEVERITY getEntitySubstSet(const BFDataGroupId &idDataGroup, 
                              DString &entitySubstSet, 
                              const DString& dstrEntityType = I_(""),
                              const bool& isAppendEntityType = true);

   SEVERITY getFinInstRegDetlList(FinInstRegDetlList *&pFinInstRegDetlList,
                                 const DString &dstrComplyRule, 
                                 const BFDataGroupId& idDataGroup, 
                                 bool bCreate = true,
                                 const DString& dstrTrack = I_("N"),
                                 const DString& dstrPageName  = NULL_STRING);

   SEVERITY getAcctRoundingRuleList( AcctRoundingRuleList *&pAcctRoundingRuleList, 
                                     const BFDataGroupId& idDataGroup,
                                     bool bCreate = true);

   bool hasAcctRoundingRule(const BFDataGroupId& idDataGroup);


   //******************************************************************************
   // This method will set/unset the default values for WRAP Account.
   // When the bSetDefault paramter is true, the field MgmtFeePayOption is set to 
   // 3, which is broker (default).  The field AMSROCode is set only when the 
   // system option ClientAMSType is RO.  The value set for AMSROCode depends on the
   // system level setup.  When the bSetDefault parameter is false, the MgmtFeePayOption
   // field is reset to 0 (N/A) and the AMSROCode is set to NULL_STRING when the
   // system option ClinetAMSType is RO.
   // @param   bool bSetDefault - True, set the fields to defaults for WRAP account.
   //                             false, undo the defaults for WRAP account.
   //          const BFDataGroupId& idDataGroup - current data group id.
   //******************************************************************************
   void setWRAPAcctDefaults ( bool bSetDefault, const BFDataGroupId& idDataGroup );
   void setAlertViewedFlag(const bool bFlag);
   bool getAlertViewedFlag();
   bool doesTaxJurisdictionLimitationListExist(const BFDataGroupId& idDataGroup);
   bool isRRIFAccount(const BFDataGroupId& idDataGroup);
   SEVERITY getDemographicsList(Demographics *&pDemographics,
      const BFDataGroupId& idDataGroup, bool inquireDatabase = true);
   SEVERITY getAMSMstrList( AMSMstrList*& pAMSMstrList, const BFDataGroupId& idDataGroup,
                            const DString& dstrInquryDate);

   bool isAMSAccount ( const BFDataGroupId& idDataGroup );
   //AMSMstrList* getAMSMstrList( const DString& dstrDate, const BFDataGroupId& idDataGroup );
   SEVERITY canPAC( const DString& dstrDate, const BFDataGroupId& idDataGroup );
   SEVERITY minPAC( const DString& dstrDate, const DString& dstrAmount,
                    bool& bOverrideFundLevel, const BFDataGroupId& idDataGroup );
   SEVERITY canSWP( const DString& dstrDate, const BFDataGroupId& idDataGroup );
   SEVERITY minSWP( const DString& dstrDate, const DString& dstrAmount,
                    bool& bOverrideFundLevel, const BFDataGroupId& idDataGroup );
   SEVERITY canATIn( const DString& dstrDate, const BFDataGroupId& idDataGroup );
   SEVERITY canATOut( const DString& dstrDate, const BFDataGroupId& idDataGroup );
   bool isHouseBroker ( const BFDataGroupId& idDataGroup );
   virtual SEVERITY setField( const BFFieldId &fieldId,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true);
   void refreshMe (bool bRefresh);
   bool isClearingAcount( const BFDataGroupId& idDataGroup );
   bool hasSettlementLocation( const BFDataGroupId& idDataGroup );
   void checkNetworkControlind( const BFDataGroupId& idDataGroup );
   bool isBrokerNSCCCompliant( const DString& brokerCode, const BFDataGroupId& idDataGroup );
   bool isBrokerFileTypeD( const BFDataGroupId& idDataGroup );

   SEVERITY validatePendingTradesForAMSEligibleFunds( const BFDataGroupId &idDataGroup );
   SEVERITY validateUnsettledUnitsForAMSEligibleFunds( const BFDataGroupId &idDataGroup );
   SEVERITY validateAMSForInstitutionalCode ( const BFDataGroupId &idDataGroup );
   /*SEVERITY validateAMSForEscrow (const BFDataGroupId& idDataGroup);*/
   SEVERITY validateAMSforCertificates (const BFDataGroupId& idDataGroup,
      DefFundAllocList* &pFundAllocList);
   SEVERITY validateAMSForStopPurchaseRedeem (const BFDataGroupId& idDataGroup);
   ///////////////////////////////////
   /*
   SEVERITY setAMSRebalanceReadOnlyFlag( const BFDataGroupId &idDataGroup, bool bReadOnly = true );
   */

   SEVERITY getAMSAcctLvlList( const BFDataGroupId &idDataGroup, AMSAcctLvlList *&pAMSAcctLvlList, bool bCreate=true );                                                             

   SEVERITY getAccountHoldingsAsOfDate( const DString &dstrAsOfDate,
                                        MFAccountHoldingList *&pMFAccountHoldingList,
                                        const BFDataGroupId &idDataGroup,
                                        const DString &fundCode = NULL_STRING,
                                        const DString &classCode = NULL_STRING);
   SEVERITY isBrokerBranchRepActive( const DString& dstrEffectiveDate, 
                                     const BFDataGroupId& idDataGroup) ;
   SEVERITY isBrkBrRepActiveAsOf( const DString& dstrAsOfDate,
                                  const DString& dstrEffectiveDate,
                                  const DString& dstrStopDate) ;
   SEVERITY getBroker( Broker *&pBroker, const DString& dstrBrokerCode,
                       const BFDataGroupId &idDataGroup );
   bool checkIfClrFirmRelated (const DString& dstrBrokerCode, const BFDataGroupId &idDataGroup,
                               const DString& dstrClearingFirmBroker, const DString& dstrRelationType = NULL_STRING );
   SEVERITY getInvestorAuthorizationList ( InvestorAuthorizationList *&pInvestorAuthorizationList, 
                                           const BFDataGroupId &idDataGroup);

   SEVERITY getInvestorAuthorization( InvestorAuthorization *&pInvestorAuthorization, 
                                      const BFDataGroupId& idDataGroup );

   SEVERITY validateBrokerForNSCC( const DString& brokerCode,	const BFDataGroupId& idDataGroup );
   SEVERITY validateClrFirmAgtFirmTPA( const BFDataGroupId& idDataGroup );
   SEVERITY validateAgtFirmClrFirm( const BFDataGroupId& idDataGroup );
   SEVERITY validateTPAClrFirm( const BFDataGroupId& idDataGroup );
   SEVERITY validateAgentTPA( const BFDataGroupId& idDataGroup );
   SEVERITY validateClearingFirm( const BFDataGroupId& idDataGroup );
   int validateAffluent( const BFDataGroupId& idDataGroup );
   SEVERITY checkIfNSCCComplant( const DString& dstrBrokerCode, const BFDataGroupId& idDataGroup );
   SEVERITY checkIfBrokerEffective (const DString& brokerCode, const BFDataGroupId &idDataGroup);
   SEVERITY setParticipantID (const DString& dstrClearingFirm, const BFDataGroupId &idDataGroup );
   void checkNSCCBroker( const BFDataGroupId& idDataGroup );
   SEVERITY getAcctCutOffTimesList( AcctCutOffTimesList*& pAcctCutOffTimesList, const BFDataGroupId& idDataGroup, bool inquireDatabase = true );
   bool negativeBalanceAllowed( const BFDataGroupId& idDataGroup, const DString& fundCode, const DString& classCode);
   bool checkPWConsolType( const BFDataGroupId& idDataGroup );
   bool checkIDConsolType( const BFDataGroupId& idDataGroup );
   bool checkEDConsolType( const BFDataGroupId& idDataGroup );
   SEVERITY getPayToEntity (DString &payToEntity, const BFDataGroupId &idDataGroup);
   SEVERITY getPayToEntityForRedemption( DString &payToEntity,
                                         const BFDataGroupId &idDataGroup);

   SEVERITY validateAMSRBForEscrow( const BFDataGroupId& idDataGroup );
   SEVERITY validateAMSRBForSWP( const BFDataGroupId& idDataGroup );
   SEVERITY validateAMSRBForGICFund( const BFDataGroupId& idDataGroup );
   SEVERITY validateAMSRBForPendingPAC( const BFDataGroupId& idDataGroup );
   SEVERITY validateAMSRBForFundCurrency( const BFDataGroupId& idDataGroup );

   SEVERITY getDefaultConsolType ( DString &dstrConsolTransType, 
                                   DString &dstrConsolidation, 
                                   DString &dstrConsolDefault,
                                   const BFDataGroupId &idDataGroup);
   SEVERITY getMstrActAttrbValue(const DString &dstrMstrActAttrbName, DString &dstrMstrActAttrbValue, const BFDataGroupId &idDataGroup);
   SEVERITY getTaxTypeSchedule( DString &dstrTaxTypeSchedule, const BFDataGroupId& idDataGroup );
   SEVERITY isTaxTypeScheduleApplicable( bool &bApplicable, const DString& dstrTaxType, 
      const DString& dstrPensionJuris, const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup );
   SEVERITY getGrandfatheredDate( DString& dstrGrandFatheredDate, const BFDataGroupId& idDataGroup, 
      const DString& dstrTaxType, const DString& dstrTaxTypeSchedule, const DString& dstrPensionJuris, bool blFormatted = false );
   SEVERITY isLIFGainLossEligible( const BFDataGroupId& idDataGroup, DString& strEligible );

   SEVERITY getAcctGuaranteeGuardOptList ( AcctGuaranteeGuardOptList *&pAcctGuaranteeGuardOptList, 
                                           const BFDataGroupId &idDataGroup,
                                           bool inquireDatabase = true );

   SEVERITY getRESPInfoUpdateValidationList (RESPInfoUpdateValidationList *&pRESPInfoUpdateValidationList, 
                                             const DString &dstrTransID, /*TransId*/
                                             const DString &dstrNewTaxJuris, /*NewTaxJuris*/
                                             const DString &dstrNewSibling, /*NewSibling*/
                                             const DString &dstrValidateType, /*ValidationType*/
                                             const DString &dstrBenefIdList, /*BenefIdList*/
                                             const BFDataGroupId &idDataGroup);

   SEVERITY validateAcctCatEPA(const DString& dstrBrokerCode,
                               const DString& dstrAcctDesignation,
                               const DString& dstrAcctType,
                               const DString& dstrAcctTaxType,
                               const BFDataGroupId &idDataGroup);

   SEVERITY getDefaultPaymentTypeInfo( const DString &strTradeType,
                                       const DString &strFundCode,
                                       const DString &strClassCode,
                                       DString &strPaymentType,
                                       const BFDataGroupId& idDataGroup );

   SEVERITY getAcctControlRecordList( AcctControlRecordList *&pAcctControlRecordList,
                                      const DString &strRuleType,
                                      const DString &strFundCode,
                                      const DString &strClassCode,
                                      const DString &strEffectiveDate,
                                      const DString &strStopDate,
									  const DString &strInquiryType,
                                      const BFDataGroupId &idDataGroup);

   SEVERITY getBenefDeathSettlementDate(const DString& strLinkEntityID,
                                        DString& strDeathSettleDate,
                                        const BFDataGroupId& idDataGroup );
   bool canSetupTaxExemptProvincial(const BFDataGroupId& idDataGroup);
   bool isIWTNonTaxable (const BFDataGroupId& idDataGroup);
   bool hasGIAHolding (const BFDataGroupId& idDataGroup);
   bool hasSegFundsWithinPortfolio (const BFDataGroupId& idDataGroup);
   bool isCommitmentApplicable (const BFDataGroupId& idDataGroup);
   bool validateSubOrgType( const BFDataGroupId& idDataGroup );
   bool isERISAAccount ( const BFDataGroupId& idDataGroup );

   SEVERITY getAlertMessageList(const DString &dstrFromScreen, 
                                AlertMessageList *&pAlertMessageList, 
                                const BFDataGroupId& idDataGroup);
   void discardAlertMessageList();

   bool isAlertMessageExists(const DString &dstrFromScreen, const BFDataGroupId& idDataGroup);
   bool isRemarkAlertExists(const DString &dstrFromScreen, const BFDataGroupId& idDataGroup);

   SEVERITY getIDOfSequenced01OfEntityObject( const DString& idType, 
                                              const DString& entityType, 
                                              DString& idValue, 
                                              const BFDataGroupId& idDataGroup);

   SEVERITY validateIASlsRepForEmployeeAgent(const BFDataGroupId &idDataGroup);

   SEVERITY loadSettleCurrencySubstitutionList( const BFDataGroupId& idDataGroup);
   bool bIsTaxTypeRelatedtoRegAgent (const BFDataGroupId  &idDataGroup); 

   SEVERITY refreshShareholder(const BFDataGroupId& idDataGroup);
   SEVERITY validationStopAdjustmentDate(const DString& strValue,const BFDataGroupId& idDataGroup);
   SEVERITY getAgeOfSequenced01OfEntityObject( const DString& entityType, 
                                               DString& ageInYear,
                                               DString& ageInMnth,
                                               const BFDataGroupId& idDataGroup);
                                               
   SEVERITY getAcctOwnershipAllocationList(AcctOwnershipAllocationList *&pAcctOwnershipAllocationList,
                                           const BFDataGroupId& idDataGroup);
                                           
   DString getMgmtFeePayOptOvdSetup(const BFDataGroupId& idDataGroup);
   bool hasAcctOwnershipAllocationRecord(const BFDataGroupId& idDataGroup);
   unsigned int getNumOfEmbededACBList(const BFDataGroupId& idDataGroup );
   SEVERITY getEmbededACBListBySeq( unsigned int iNumSeq,
                                    ACBList *&pACBList, 
                                    const BFDataGroupId& idDataGroup, 
                                    DString& strFund,
                                    DString& strClass );
   
   SEVERITY checkIdForAccOwner(const DString &dstrCheckIDType,bool &bIDExists,const BFDataGroupId& idDataGroup);
   SEVERITY displayEnvXrefWarningOnUpdate(const BFDataGroupId& idDataGroup,bool &bDisplyWarnSICAV ,bool &bDisplyWarnOEIC );
   SEVERITY getAnnuitantYoungerAge( DString &dstrAnnuitantYoungerAge, const BFDataGroupId& idDataGroup);
   bool hasBlankAnnuitantGender(const BFDataGroupId& idDataGroup);
   bool isSingle( const BFDataGroupId& idDataGroup );

   SEVERITY getAcctRegDetailsList(AcctRegDetailsList *&pAcctRegDetailsList, const BFDataGroupId &idDataGroup, const DString &dstrComplyRule = I_("FA"));
   SEVERITY getEntityRegDetailsList(EntityRegDetailsList *&pEntityRegDetailsList,   
									const DString &dstrEntityId,
								    const BFDataGroupId &idDataGroup, 
									bool inquireDatabase = true);
   SEVERITY getEntityRegJurisDetailsList(EntityRegJurisDetailsList *&pEntityRegJurisDetailsList,   
										 const DString &dstrEntityId,
										 const BFDataGroupId &idDataGroup, 
										 bool inquireDatabase = true);
   SEVERITY getAccountLvlEntityRegJurisDetailsList(EntityRegJurisDetailsList *&pEntityRegJurisDetailsList,   
						   						   const DString &dstrAccountNum,
												   const DString &dstrEntityId,
												   const DString &dstrFATCACode,
												   const BFDataGroupId &idDataGroup);
   bool hasAMSTrades(const BFDataGroupId& idDataGroup);
   
   void setAWDHistroyWorkList(AWDHistoryWorkList *awdWorkList) {
      _pAwdWorkList=awdWorkList;
   }

   AWDHistoryWorkList *getAWDHistoryList() {
      return _pAwdWorkList;
   }
   bool isAccountOmnibus(DString& dstrAccountNum, const BFDataGroupId &idDataGroup); 
   bool accountHasTradeAfterDate(DString& dstrFund, DString& dstrClass, 
								 DString& dstrDate, const BFDataGroupId &idDataGroup);

   bool hasTransTypePendingTrades( const DString &dstrTransType,
								   const DString &dstrAccountNum,
								   const DString &dstrFundCode,
								   const DString &dstrClassCode,
								   const BFDataGroupId &idDataGroup);

   bool hasTransTypeProccessedTrades( const DString &dstrTransType,
									  const DString &dstrAccountNum,
									  const DString &dstrFundCode,
									  const DString &dstrClassCode,
									  const BFDataGroupId &idDataGroup);

   SEVERITY getDefaultOrderRoutingInfo( DString &dstrAcctOrderRouting,
										const DString &tradeDate,
                                        const BFDataGroupId& idDataGroup ) ;

   bool isRDSPAccount ( const BFDataGroupId& idDataGroup );

protected:

   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, 
                                     const BFDataGroupId& idDataGroup );
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual void doPopulateField (const BFFieldId &idField, DString &strValue, bool formattedReturn);
   //support for refresh
   virtual SEVERITY doPreClearFields();
   virtual SEVERITY reInit( );
   virtual bool needsRefresh (const BFDataGroupId  &idDataGroup) const; 

   SEVERITY loadNetworkIDValues (const BFDataGroupId &idDataGroup);
   SEVERITY validateBrokerIA(const BFDataGroupId &idDataGroup);
   SEVERITY validateBranchIA(const BFDataGroupId &idDataGroup);
   SEVERITY validateSlsRepIA(const BFDataGroupId &idDataGroup);

   SEVERITY validateSiblingOnly(const BFDataGroupId &idDataGroup);
   SEVERITY validateRESPTaxType(const DString &taxType, const BFDataGroupId& idDataGroup);

   SEVERITY getFeeModelInfo (FeeModelList *&pFeeModelList, 
                             const DString &dstrFeeModelCode,
                             const BFDataGroupId& idDataGroup);
                             
   SEVERITY GetEntityIdForEntityTypeSeq1( const DString& entityType, 
                                          const BFDataGroupId& idDataGroup, 
                                          DString& entityId );                             

   SEVERITY validatePortfolioField(const BFDataGroupId& idDataGroup );

   SEVERITY validateBlockTransfer( const DString& brokerCode, 
                                   const DString& branchCode,
                                   const DString& slsRep, 
                                   const BFDataGroupId& idDataGroup );
   SEVERITY validateSalesrepFund( const DString& dstrBroker,
                                  const DString& dstrBranch,
                                  const DString& dstrSlsRep,
                                  const DString& dstrFund, 
                                  const DString& dstrClass, 
                                  const BFDataGroupId& idDataGroup );

   SEVERITY validateServiceOnlySlsRep(const BFDataGroupId &idDataGroup);

   void initializeSubstitutionList( const BFFieldId& idField, 
                                    const DString &dstrGroupCode, 
                                    const BFDataGroupId& idDataGroup);
   void addBlankToSubSet(const BFFieldId &idField ,const BFDataGroupId &idDataGroup, bool dstrUseNotApplicableAsDesc = false );

private:
   //validation helpers
   SEVERITY checkBroker( const DString& brokerCode, const BFDataGroupId& idDataGroup, bool condition_returned );
   SEVERITY checkBranches( const DString& branchCode, const BFDataGroupId& idDataGroup, bool condition_returned );
   SEVERITY checkAgents( const DString& slsRepCode, const BFDataGroupId& idDataGroup, bool condition_returned, bool &bNewAgent );
   SEVERITY checkTheAccountNumber( const DString& accountNum, const BFDataGroupId& idDataGroup, 
                                   bool &found );
   SEVERITY checkForReadOnly( const BFDataGroupId& idDataGroup );   
   SEVERITY initFieldsAndSubst( const BFDataGroupId& idDataGroup );
   SEVERITY initFieldsNotInInquiry( const BFDataGroupId& idDataGroup );
   SEVERITY validateLifLiraLRif ( const DString& taxType, Shareholder *&pshareholder, const BFDataGroupId& idDataGroup );
   SEVERITY validateRESP ( const DString& taxType, const BFDataGroupId& idDataGroup );
   SEVERITY loadGroupSubstitutionList( const BFDataGroupId& idDataGroup );
   SEVERITY loadAcctTypeSubstitutionList( const BFDataGroupId& idDataGroup );
   SEVERITY loadTaxTypeSubstitutionList( const BFDataGroupId& idDataGroup );
   SEVERITY getGroupList ( GroupList *&pGroupList);
   DString  getGrpCodeLevel ( const BFDataGroupId& idDataGroup );
   SEVERITY getAccountEntityXref ( AccountEntityXref *&pAccountEntityXref, const BFDataGroupId& idDataGroup );
   SEVERITY getShareholder ( Shareholder *&pShareholder, const BFDataGroupId& idDataGroup );
   SEVERITY validateTaxType( const DString &taxType, const BFDataGroupId& idDataGroup);
   SEVERITY validateTaxTypePensionJuris( const BFDataGroupId& idDataGroup );
   SEVERITY validateAltAcct( const DString& dstrAltAcctNum, const BFDataGroupId& idDataGroup );
   SEVERITY initDefaultAddress01 (const BFDataGroupId &idDataGroup);
   SEVERITY refreshDefaultAddress01 (const BFDataGroupId &idDataGroup);
   SEVERITY checkDefaultMailingInfo(const BFDataGroupId& idDataGroup);
   SEVERITY validateMgmtFeePayOption( const BFDataGroupId& idDataGroup );
   SEVERITY validateBusinessNo( const BFDataGroupId& idDataGroup );
   SEVERITY validateAccountTaxTypeAccountDesTaxJurisProvRes(const BFDataGroupId& idDataGroup);
   SEVERITY checkAMSRestriction( const DString& dstrDate, const DString& dstrTransType, const BFDataGroupId& idDataGroup, bool& bFundOverride, const DString& dstrAmount, bool bCheckGrandFather = false );
   SEVERITY validateClearingID( const BFDataGroupId& idDataGroup );
   SEVERITY validateLengthForBrokerBranchSalsRep(const DString& dstrType,
                                                 const DString& strValue,
                                                 const BFDataGroupId& idDataGroup);
   SEVERITY validateModelCode( const BFDataGroupId& idDataGroup );
   SEVERITY validateBrokerChangeForDocList( const BFDataGroupId& idDataGroup );
   SEVERITY validateBrokerChangeForTrailerFee (const DString& dstrNewBrokerCode, 
                                               const BFDataGroupId& idDataGroup );

   void getResponseData(BFData*& pResponse);

   void setRecipientType ( const BFDataGroupId& idDataGroup, bool assign = true );

   bool ZeroBalance( const BFDataGroupId& idDataGroup );
   bool slsRepByBranch ( const BFDataGroupId& idDataGroup );
   bool getFundDetailList ( );
   bool isSINMatching ( const DString& entityId1, 
                        const DString& entityId2, 
                        const BFDataGroupId &idDataGroup);
   bool isPortfolioRequired (const BFDataGroupId &idDataGroup);
   /////////////////void setAMSTypeSubstitutionList(const BFDataGroupId& idDataGroup);
   SEVERITY flipReadOnlyForTaxTypeSchedule( const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup );
   SEVERITY updateTaxTypeSchedule( const DString& dstrTaxType, const DString& dstrTaxTypeSchedule, 
                                   const DString& dstrPensionJuris, const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup );
   SEVERITY validateTaxTypeTaxTypeSchedWithJurisEffDate( const BFDataGroupId& idDataGroup );
   SEVERITY validateBrokerNI31103STMT(DString& brokerCode, const BFDataGroupId &idDataGroup);
   SEVERITY getLatestAmendmentYearOfOwnerSeq01( DString& dstrLatestAmendYear, const BFDataGroupId& idDataGroup );
   SEVERITY setFieldFromModelAcct(const BFFieldId& idField, const BFDataGroupId& idDataGroup, MFAccount *pMFAccountModel, bool readOnly, bool validateNow = false);
   SEVERITY validateAcctCustodian(const BFDataGroupId& idDataGroup);

public:
   void setDefaultAggregationType ( const DString dstrAggrType,const BFDataGroupId& idDataGroup );
   SEVERITY getAccountLevelCOA(COANavig*& pCOANavig, const DString& dstrAcctNum,const BFDataGroupId& idDataGroup, bool bForceRefresh = false) ;

   DString _brokerName;
   DString _branchName;
   DString _branchCode;
   DString _agentName;
   DString _agentAltName;
   DString _agentType;
   DString _reinitAccountNum;
   //this saves the initial account number, that came in when creating a new account
   DString _initAccountNum;
   DString _initEffectiveDate;
   DString _grpCodeLevel;
   GroupList* _pGroupList;
   DString _GroupName;
   AccountEntityXref* _pAcctEntityXref;
   Shareholder* _pShareholder;
   IntermediaryList* _pIntermediaryList;
   DString _salesRepByBranch;
   DString _strLIPRateExist;
   ErrMsgRulesList* _pErrMsgRulesList;
   FundDetailList *_pFundDetailList;
   ACCTENTITYOBJ_VECTOR vBenefAcctEntVectot;
   BFData* _pResponseData;
   DString _dstrHouseBroker;
   bool   _bRefresh;
   bool _bStopReasonChanged;
   bool _alertViewed;
   DString _dstrRegStandard;
   DString _recipientTypeSubstList;
   DString _dstrTAKey;
   DString _serviceAgentUpdated;

   AWDHistoryWorkList *_pAwdWorkList;
   COANavig *_pCOANavig;
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MFAccount.hpp-arc  $
 * 
 * History:
 * 04-Mar-2014	Supareuk Sukjaitham P0221545 FN01 DFT0030180 T54906
 *              - Added a new function getMgmtFeePayOptOvdSetup
 *              - Recheck with the new task T54906
 *
 *    Rev 1.250   Jul 24 2012 19:01:38   dchatcha
 * P0179630 FN01 FATCA Project - Acct Ownership Allocation
 * 
 *    Rev 1.249   Jul 23 2012 12:31:16   wutipong
 * PETP0179630_FN01 FATCA Account Entity Document Tracking
 * 
 *    Rev 1.248   Jul 12 2012 10:29:16   dchatcha
 * Synh up : IN# 2994672 - Block Service Unit Transfers, simplified logic that let account cbo update b\b\s
 * 
 *    Rev 1.247   Jul 09 2012 19:29:52   dchatcha
 * Synch up : IN# 2994672 - Block Service Unit Transfers.
 * 
 *    Rev 1.246   Jun 05 2012 11:38:06   dchatcha
 * IN#2969458- Bypass  the editing for age difference if the new "Guarantees Override" flag set as "Yes"
 * 
 *    Rev 1.245   May 18 2012 15:20:08   dchatcha
 * P0186479 FN10 -Gap 14G - Block Service Unit Transfers, revise code.
 * 
 *    Rev 1.244   May 16 2012 05:03:46   panatcha
 * P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
 * 
 *    Rev 1.243   May 14 2012 15:39:48   dchatcha
 * P0186479 FN10 -Gap 14G - Block Service Unit Transfers.
 * 
 *    Rev 1.242   May 04 2012 11:44:28   wp040039
 * PETP0187485 - Trade Entry And Processing
 * 
 *    Rev 1.241   Apr 25 2012 10:00:32   if991250
 * added dummy bIsTaxTypeRelatedtoRegAgent to fix compilation issue
 * 
 *    Rev 1.240   Apr 25 2012 09:56:46   if991250
 * added loadSettleCurrencySubstitutionList
 * 
 *    Rev 1.239   Apr 12 2012 10:37:20   dchatcha
 * Synch up: IN# 2918245 - Portfolio keep display error after update on any field on account information screen.
 * 
 *    Rev 1.238   Apr 09 2012 23:36:24   panatcha
 * P0186486FN09 - Employee and Agent Account Gap#8A
 * 
 *    Rev 1.237   Mar 30 2012 11:30:54   jankovii
 * IN 2898233 - R12.3-P0186477-Enable manual tax calculation of money out transactions for NR
 * 
 *    Rev 1.236   Mar 16 2012 17:46:18   wp040100
 * P0186484 FN05 - Contract Maturity Instruction Changes
 * 
 *    Rev 1.235   Mar 08 2012 12:36:50   jankovii
 * Sync up: IN 2859411 - P0186477_FN02_Interest Instruction-Err displayed on split type 'Amount' instrctn
 * 
 *    Rev 1.234   Mar 05 2012 12:26:06   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.233   Mar 02 2012 12:54:22   if991250
 * Account Commitment in NASU
 * 
 *    Rev 1.232   Feb 28 2012 14:03:22   if991250
 * do not send create acct commit if not applicable
 * 
 *    Rev 1.231   Feb 24 2012 16:06:46   popescu
 * NASU - Added commitment.
 * 
 *    Rev 1.230   Feb 21 2012 17:23:02   if991250
 * added function to remove the maturity instructions list
 * 
 *    Rev 1.229   Feb 21 2012 15:46:16   wp040100
 * P0186484 FN05 - Contract Maturity Instruction Changes
 * 
 *    Rev 1.228   Feb 17 2012 10:04:44   popescu
 * refresh portfolio - temporary backed the code out.
 * 
 *    Rev 1.227   Feb 16 2012 16:08:54   if991250
 * added Account Commitment
 * 
 *    Rev 1.226   Feb 13 2012 22:57:18   dchatcha
 * Synch up: IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.225   Feb 03 2012 15:16:54   jankovii
 * Sync up: IN 2826242- Maturity/Interest Instruction on Trading Screen
 * 
 *    Rev 1.224   Feb 01 2012 16:34:12   dchatcha
 * Synch up: IN# 2799812 - Contract Screen Issues, refresh portfolio list during NASU.
 * 
 *    Rev 1.223   Jan 23 2012 12:08:22   jankovii
 * Sync up: IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
 * 
 *    Rev 1.222   Jan 16 2012 13:51:12   wp040027
 * P0188394_Performance Fees - ERISA Functionality
 * 
 *    Rev 1.221   Dec 27 2011 00:43:32   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.220   Dec 19 2011 23:32:32   popescu
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.219   Dec 14 2011 18:10:44   dchatcha
 * P0186477/FN03 - GIA - Purchase, validate trade fund\class against portfolio.
 * 
 *    Rev 1.218   Dec 12 2011 12:00:14   wp040100
 * P0186477/FN03 - GIA - Investment History Changes
 * 
 *    Rev 1.217   Dec 08 2011 14:19:16   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.216   Nov 27 2011 22:29:46   popescu
 * 2740236 - TIN Validation
 * 
 *    Rev 1.215   Oct 28 2011 04:41:56   kitticha
 * PETP0188150 FN01 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.214   Oct 21 2011 09:34:44   kitticha
 * PETP0188150 FN01 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.213   Oct 04 2011 18:20:10   dchatcha
 * P0186477 FN01 - GIA Enhancements, display validate portfolio fields based on environment functionality(UAF).
 * 
 *    Rev 1.212   Sep 30 2011 10:07:28   popescu
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.211   Jul 20 2011 18:00:46   dchatcha
 * P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
 * 
 *    Rev 1.210   Jul 07 2011 18:58:36   dchatcha
 * P0181953 FN01 - TFSA Amendment.
 * 
 *    Rev 1.209   Mar 11 2011 11:24:42   kitticha
 * IN2450642 - Modify program to support fund-class hierarchy.
 * 
 *    Rev 1.208   Jan 31 2011 18:53:58   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.207   Jan 11 2011 10:43:14   jankovii
 * IN 2350361 - iFast performance issue
 * 
 *    Rev 1.206   Dec 09 2010 15:05:02   jankovii
 * IN 2339013 - P0175778: Uptreaming QA testing
 * 
 *    Rev 1.205   Dec 01 2010 06:17:48   dchatcha
 * P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
 * 
 *    Rev 1.204   Nov 24 2010 02:59:52   kitticha
 * PET165541_FN03_QESI_Phase3_Non_Finance - revise.
 * 
 *    Rev 1.203   Nov 23 2010 14:26:30   jankovii
 * PET175778F N01 - Upstreaming Phase 2
 * 
 *    Rev 1.202   Sep 17 2010 07:56:30   kitticha
 * PETP0173756 FN02 Don't Bust the Rules.
 * 
 *    Rev 1.201   Sep 15 2010 13:44:02   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.200   Aug 11 2010 19:40:26   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.199   Aug 06 2010 14:03:56   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.198   May 13 2010 03:49:04   dchatcha
 * RESP QESI Synch-up 1.194.1.3
 * 
 *    Rev 1.197   Apr 26 2010 04:07:12   dchatcha
 * RESP QESI Synch-up 1.194.1.2
 * 
 *    Rev 1.196   Apr 19 2010 08:00:00   popescu
 * RQESI Synch-up 1.194.1.1
 * 
 *    Rev 1.195   Apr 06 2010 12:36:22   kitticha
 * PET0169756_FN01_N131-103 Statement and Confirm.
 * 
 *    Rev 1.194   Apr 06 2010 06:32:32   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, take out method that set sibling only valid flag, no longer use.
 * 
 *    Rev 1.193   Mar 31 2010 00:24:50   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - bene allocation updates
 * 
 *    Rev 1.192   Mar 26 2010 09:18:22   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.191   Mar 12 2010 14:52:22   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.190   Jan 22 2010 02:21:24   dchatcha
 * IN# 1976746 - Pay Instruction button enabled with Pay type X and error displayed.
 * 
 *    Rev 1.189   Oct 26 2009 16:29:38   jankovii
 * PET157825 FN08 FN11 FN14 AMS Gaps
 * 
 *    Rev 1.188   22 Jul 2009 18:09:18   popescu
 * PET156681 FN14 H36 Investor Authorization - clean-up various fixes.
 * 
 *    Rev 1.187   Jul 22 2009 08:26:46   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Code review. 
 * 
 *    Rev 1.186   Jul 09 2009 15:05:26   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.185   29 Jun 2009 16:10:28   popescu
 * PET 156681 - FN 14 - Investor Authorization
 * 
 *    Rev 1.184   Apr 01 2009 09:38:20   jankovii
 * IN 1642475 - Character not compatible - IFast desktop / Base
 * 
 *    Rev 1.183   Mar 02 2009 09:59:56   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.182   Jan 12 2009 11:12:44   jankovii
 * IN 1549377 Estate and Death of Notification acct category can only be added by the system
 * 
 *    Rev 1.181   24 Dec 2008 11:39:32   popescu
 * Incident 1531239 - Recipient Type 6 and 7 cannot be modified in Desktop
 * 
 *    Rev 1.180   24 Dec 2008 11:37:22   popescu
 * Incident 1531161 - Recipient Type 6 &7 should not be set up on Registered accounts
 * 
 *    Rev 1.179   Nov 28 2008 14:39:04   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.178   03 Nov 2008 17:32:48   popescu
 * KYC/AML - Joint accounts feature - after System Integrated Testing
 * 
 *    Rev 1.177   31 Oct 2008 16:18:54   popescu
 * KYC/AML - joint accounts feature
 * 
 *    Rev 1.176   Oct 28 2008 08:33:10   jankovii
 * PET 59888 FN03 AML KYC.
 * 
 *    Rev 1.175   Aug 29 2008 14:34:16   jankovii
 * IN 1388930.
 * 
 *    Rev 1.174   Aug 28 2008 14:25:36   jankovii
 * IN 1388930 - NASU flow does not update document list unless at least one document.
 * 
 *    Rev 1.173   Jul 29 2008 17:39:18   daechach
 * in#1327144 - New ON LIF with effective date of Dec 31, 2007, synched up from R87.
 * 
 *    Rev 1.172   Jul 25 2008 14:27:40   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.171   23 May 2008 10:05:36   popescu
 * Incident 1253513 - The issue has been solved by checking if the SIN number of the "account from" beneficiary matches the SIN number of the "account to" account owner.
 * This is done only in environments where the entity ids of the above are different. This occurs if the generic control CSSStopSINMatch is turned on.
 * 
 *    Rev 1.170   05 May 2008 14:51:08   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.169   01 May 2008 13:57:46   kovacsro
 * PET2255 FN47 - New Ontario LIF - finalized
 * 
 *    Rev 1.168   15 Apr 2008 12:09:42   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.167   Mar 11 2008 20:14:42   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.166   10 Jan 2008 14:34:10   kovacsro
 * IN#1147561 made getDefaultConsolType() public 
 * 
 *    Rev 1.165   Nov 06 2007 18:31:02   smithdav
 * IN1024380 -  Change AMS certificates edit to check at the fund level instead of the account level.
 * 
 *    Rev 1.164   26 Oct 2007 16:32:06   kovacsro
 * IN# 1039915 - added validation for Affluent field
 * 
 *    Rev 1.163   Oct 24 2007 19:10:14   smithdav
 * IN1024380 - AMSAcctLevel active Certificates edit.
 * 
 *    Rev 1.162   20 Sep 2007 10:55:34   popescu
 * Incident 1002765 - fixed the validation for institutional code AMS
 * 
 *    Rev 1.161   Aug 03 2007 09:35:04   smithdav
 * PET 2360 FN02
 * 
 *    Rev 1.160   Jul 18 2007 09:36:14   smithdav
 * PET2360 FN02
 * 
 *    Rev 1.159   Jul 11 2007 16:21:00   smithdav
 * PET 2360 FN02 - AMS - Interim changes
 * 
 *    Rev 1.158   Jun 27 2007 14:57:46   porteanm
 * PET 2360 FN02 - AMS.
 * 
 *    Rev 1.157   Jun 22 2007 14:22:22   porteanm
 * PET 2360 FN02 - AMS - work in progress.
 * 
 *    Rev 1.156   Feb 15 2007 14:37:28   popescu
 * Incident# 819881 - MFS slowness with the distribution screen
 *  - release 76 and above, synch-up
 * 
 *    Rev 1.155   Jan 24 2007 16:50:00   ZHANGCEL
 * PET2306 FN02 -- Add logic for ConsolTypeID and ConsolTypePW
 * 
 *    Rev 1.154   Oct 13 2006 17:42:56   fengyong
 * Add transnum search
 * 
 *    Rev 1.153   Sep 21 2006 18:36:50   ZHANGCEL
 * PET2212 FN10 - Add a function to deal with ConsolType issue
 * 
 *    Rev 1.152   Feb 21 2006 10:20:16   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.151   Nov 19 2005 15:52:08   popescu
 * BPS Performance issue - cached view call 20 and passed params fund/class in as params
 * 
 *    Rev 1.150   Sep 20 2005 12:51:34   fengyong
 * Incident 402113 - In Transaction history screen:
 * All fund mode and select fund combo box, do not need check transId.
 * 
 *    Rev 1.149   Sep 20 2005 12:15:20   AGUILAAM
 * PET1250_FN09_Custody Client Accounts and Negative Balances; also fixed Refresh functionality for Settlements.
 * 
 *    Rev 1.148   Jul 20 2005 14:01:36   Yingbaol
 * PET1235,FN01: fix refresh pending trade
 * 
 *    Rev 1.147   Jul 07 2005 15:58:56   ZHANGCEL
 * PET1141-FN05 -- Added another parameter in setParticipantID()
 * 
 *    Rev 1.146   Jul 06 2005 15:23:04   hernando
 * PET1250 FN01 - Added getAcctCutOffTimesList.
 * 
 *    Rev 1.145   Jul 06 2005 10:59:22   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.144   May 16 2005 09:39:38   AGUILAAM
 * IN 299732 - inactive broker/branch/rep not allowed for systematics
 * 
 *    Rev 1.143   Apr 21 2005 17:31:50   hernando
 * Incident #278666 - Added TransNum to Pending Trade List and Transaction History List get fns.  Added IsTransactionPending fn.  Synchronized with 1.139.1.0-1.139.1.1
 * 
 *    Rev 1.142   Apr 14 2005 10:07:08   hernando
 * PET1024 FN02 - Added parameter, Contract Type.
 * 
 *    Rev 1.141   Apr 12 2005 10:28:58   porteanm
 * PET1190 FN14 - Wire order redemption against unsettled units.
 * 
 *    Rev 1.140   Mar 20 2005 15:03:46   hernando
 * PET1024 FN02 - Added getUserDefMatList.
 * 
 *    Rev 1.139   Mar 13 2005 17:28:50   winnie
 * Restore the previous version. 
 * 
 *    Rev 1.138   Mar 11 2005 14:28:18   smithdav
 * Fixed bug in Group::getGroupFundListByFund function where BPS threads clashed the function call concurrently.
 *
 *    Rev 1.137   Feb 17 2005 13:23:28   yingbaol
 * magic #237768: sync. up version 1.135.1.0 GetFundFroupBy FundCode
 * 
 *    Rev 1.136   Feb 04 2005 14:59:40   porteanm
 * PTS 10033798 - "Should this Account be rebalanced in the next cycle" support.
 * 
 *    Rev 1.135   Dec 21 2004 16:05:08   popescu
 * PTS 10037131, removed 'deletePendingTradesList' method at the account level; it is dangerous to have such a public method; dealt with removing the list when necessary after trade is being modified, in trades process
 * 
 *    Rev 1.134   Dec 07 2004 15:50:40   popescu
 * Fix cross-edit validation, acctype/taxtype
 * 
 *    Rev 1.133   Nov 14 2004 14:50:04   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.132   Oct 13 2004 13:52:40   VADEANUM
 * PET 1117 FN21 - Settlement Instruction support.
 * 
 *    Rev 1.131   Sep 22 2004 09:12:44   WINNIE
 * PET1082 FN02 Tax Exemption : add new parameter to indicate if getting data from database is required or not. When transaction builder invoke this method, it does not require getting data from the database.
 * 
 *    Rev 1.130   Aug 11 2004 18:37:42   FENGYONG
 * Temp check in  PET 117 FN5  for other enhancement compiling
 * 
 *    Rev 1.129   Aug 11 2004 12:04:50   AGUILAAM
 * PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
 * 
 *    Rev 1.128   Aug 06 2004 17:33:18   ZHANGCEL
 * PET 1082 FNrlc - Add a new function -- getTaxExemptAuthorizationList()
 * 
 *    Rev 1.127   Jul 23 2004 10:00:48   YINGBAOL
 * PET1117: Add isSettleRedeptionAllowed method.
 * 
 *    Rev 1.126   May 26 2004 11:01:42   YINGBAOL
 * PTS10027992:add limit for BrokerCode,BranchCode and SalsRepCode based on the ifast setting.
 * 
 *    Rev 1.125   May 25 2004 22:39:06   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.124   May 25 2004 20:32:26   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.123   May 20 2004 14:17:04   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.122   May 11 2004 15:28:16   HERNANDO
 * PET1046 FN01 - Added ActiveOnly to getInventorySummaryList.
 * 
 *    Rev 1.121   Apr 12 2004 16:15:14   VADEANUM
 * PET1005 FN11 - AMS Gaps.
 * 
 *    Rev 1.120   Apr 05 2004 17:29:42   FENGYONG
 * PET944 FN01, release 56.1 NSCC Broker Matrix
 * 
 *    Rev 1.119   Mar 03 2004 16:21:24   popescu
 * PTS 10027578, refresh the account information after updating the mailing address info and demographics info; changed the name of the refreshMe method, to be consistent with the shareholder object
 * 
 *    Rev 1.118   Feb 25 2004 14:27:50   ZHANGCEL
 * PET1001-FN01: Added a function to get InventorySummaryList
 * 
 *    Rev 1.117   Feb 18 2004 15:37:26   YINGBAOL
 * PTS10027208:Add validation for clearing ID 
 * 
 *    Rev 1.116   Nov 25 2003 11:19:56   VADEANUM
 * PET859 FN1 - Settlement Location at Trade Level support - added isClearingAccount() and hasSettlementLocation().
 * 
 *    Rev 1.115   Nov 20 2003 18:12:18   HERNANDO
 * PET859 FN1 - Added getSettlementLocationAcctLvlList.
 * 
 *    Rev 1.114   Nov 20 2003 09:13:02   linmay
 * added validatePendingPAC( ) for PTS #10024070
 * 
 *    Rev 1.113   Nov 05 2003 15:39:20   HSUCHIN
 * sync up 1.111.1.0
 * 
 *    Rev 1.112   Oct 16 2003 12:21:24   FENGYONG
 * PET809 FN08 Direct Trading enhancement
 * 
 *    Rev 1.111   Sep 15 2003 14:20:24   YINGBAOL
 * add refresh me and needsrefresh methods
 * 
 *    Rev 1.110   Sep 12 2003 13:49:34   FENGYONG
 * override set field function
 * 
 *    Rev 1.109   Aug 21 2003 17:21:16   HSUCHIN
 * change getAMSFundAllocation to take in effective date
 * 
 *    Rev 1.108   Aug 21 2003 11:53:26   YINGBAOL
 * add validateAMSRRIF
 * 
 *    Rev 1.107   Aug 19 2003 09:08:24   HSUCHIN
 * added isHouseBroker method and house broker validation
 * 
 *    Rev 1.106   Aug 15 2003 15:26:42   HSUCHIN
 * added AMS Restriction support canPAC, minPAC etc.
 * 
 *    Rev 1.105   Aug 13 2003 10:19:26   YINGBAOL
 * sync. version 1.104.1.0 to 1.104.1.15.
 * 
 * 
 *    Rev 1.104   Mar 05 2003 11:54:36   HSUCHIN
 * PTS 10014446 - fixed broker/branch/salesrep validation to check effective/stop date.
 * 
 *    Rev 1.103   Feb 06 2003 15:04:10   HSUCHIN
 * added method setWRAPAcctDefaults to set/unset defaults for WRAP accounts
 * 
 *    Rev 1.102   Feb 06 2003 10:44:50   WINNIE
 * New method canContributeProtecedFund to validate if account owner is valid for buying or transfer into protected fund
 * 
 *    Rev 1.101   Jan 29 2003 13:47:10   sanchez
 * new function prtotypes   bool isAMSOnly    (const BFDataGroupId& idDataGroup);
 *    bool isAMSAnOption(const BFDataGroupId& idDataGroup);
 * 
 *    Rev 1.100   Jan 25 2003 17:04:16   KOVACSRO
 * Added isCategoryExist( );
 * 
 *    Rev 1.99   Jan 23 2003 16:29:30   KOVACSRO
 * Added getAcctCategoryList
 * 
 *    Rev 1.98   Jan 21 2003 19:07:14   WINNIE
 * Add edit check for redemption for Group level locked-in for employer or employee
 * 
 *    Rev 1.97   Jan 21 2003 18:37:22   WINNIE
 * remove method fundclasstradeMinimum. Method to be build in Trade.cpp instead. Correction of account contract key build
 * 
 *    Rev 1.96   Jan 20 2003 15:18:48   HSUCHIN
 * added getAccountContractList
 * 
 *    Rev 1.95   Jan 09 2003 10:18:12   sanchez
 * new DefineSEVERITY setAMSTypeSubstitutionList()
 * 
 *    Rev 1.94   Nov 26 2002 14:55:58   HERNANDO
 * Changed getAMSAcctAllocList signature.
 * 
 *    Rev 1.93   Nov 25 2002 16:02:30   KOVACSRO
 * Added  getAMSFundAllocList(AmsFundAllocList and getAMSAcctAllocList;
 * 
 *    Rev 1.92   Oct 29 2002 10:52:18   KOVACSRO
 * added getHypoRedCriteria.
 * 
 *    Rev 1.91   Oct 09 2002 23:54:46   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.90   Sep 04 2002 17:09:34   KOVACSRO
 * Added getAcctName()
 * 
 *    Rev 1.89   Aug 29 2002 12:53:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.88   Aug 02 2002 14:40:10   KOVACSRO
 * added a couple of methods to check default address and mailing info.
 * 
 *    Rev 1.87   Jul 06 2002 19:13:18   WINNIE
 * change method name to reflect purpose
 * 
 *    Rev 1.86   Jul 02 2002 11:13:08   WINNIE
 * Tax legislation enhancement for marriage break down redemption and transfer with red code 29 and 30
 * 
 *    Rev 1.85   Jun 27 2002 17:03:42   ZHANGCEL
 * Added a new function: validateTaxTypePensionJuris() for the TaxType and PensionJuris combination checking
 * 
 *    Rev 1.84   Jun 19 2002 15:52:26   ZHANGCEL
 * PTS 10008491: Added a function - checkForDuplicateAltAcct() for the duplicate alternate account checking
 * 
 *    Rev 1.83   13 Jun 2002 14:40:42   YINGZ
 * add reqtransid to support settlement
 * 
 *    Rev 1.82   Jun 05 2002 17:45:08   ZHANGCEL
 * PTS 10008253: added a cross edit for TaxType and AcctType to avoid invalid TaxType and AcctType combination being accepted.
 * 
 *    Rev 1.81   31 May 2002 13:25:14   HERNANDO
 * Account Review - Added getAccountReviewList fn.
 * 
 *    Rev 1.80   May 30 2002 16:43:10   HSUCHIN
 * added method to getPensionInfo
 * 
 *    Rev 1.79   22 May 2002 18:20:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.78   19 Mar 2002 13:17:56   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.77   Mar 12 2002 16:01:42   JANKAREN
 * Added getDofDeathofOwnerSeq01()
 * 
 *    Rev 1.76   05 Mar 2002 16:24:28   KOVACSRO
 * Added refreshDataObject(), which is a partial refresh for MFAccount.
 * 
 *    Rev 1.75   Feb 25 2002 19:14:40   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.74   25 Feb 2002 12:14:56   WINNIE
 * remove parameter since fundInGroup no longer include checking of stop flag; Purchase, Redemption and Transfer class will call the stopflag checking directly
 * 
 *    Rev 1.73   Feb 11 2002 12:09:02   YINGBAOL
 * add getFeeParamList
 * 
 *    Rev 1.72   08 Feb 2002 16:55:18   KOVACSRO
 * Added validateAccountNum static method.
 * 
 *    Rev 1.71   Feb 06 2002 17:32:20   ZHANGCEL
 * Change the function validateLifLiraLRif()
 * 
 *    Rev 1.70   Dec 03 2001 15:36:20   ZHANGCEL
 * Added a new function: getGroupFundFromGroup()
 * 
 *    Rev 1.69   Nov 28 2001 12:31:08   JANKAREN
 * Added getDofBirthofOwnerSeq01, getAgeofOwnerSeq01 and validateAMSCode
 * 
 *    Rev 1.68   20 Nov 2001 16:40:40   KOVACSRO
 * Added bStartEmptyList param to getTransactionList().
 * 
 *    Rev 1.67   14 Nov 2001 09:38:44   KOVACSRO
 * synchup to 1.65.1.0
 * 
 *    Rev 1.66   15 Oct 2001 12:09:32   KOVACSRO
 * 1. Added bCreate param for getAcctDistributionList.
 * 2.Added doPopulateField().
 * 
 *    Rev 1.65   02 Oct 2001 11:42:26   KOVACSRO
 * Removed getEsopHistoricalList()
 * 
 *    Rev 1.64   26 Sep 2001 14:05:34   WINNIE
 * title restriction enhancement
 * 
 *    Rev 1.63   25 Sep 2001 14:46:38   WINNIE
 * new method to getEsoPHistoricalList
 * 
 *    Rev 1.62   17 Sep 2001 13:34:48   WINNIE
 * title restriction enhancement
 * 
 *    Rev 1.61   23 Aug 2001 14:45:18   HSUCHIN
 * added getAcctSplitCommList
 * 
 *    Rev 1.60   Aug 23 2001 12:44:44   JANKAREN
 * Added getAsPensionPlan()
 * 
 *    Rev 1.59   Aug 16 2001 13:26:10   ZHANGCEL
 * Added a new function: getMatchTransferList()
 * 
 *    Rev 1.58   08 Aug 2001 14:21:46   HSUCHIN
 * added two functions getTransactionHistoryList and getLastActiveTransactionHistoryList
 * 
 *    Rev 1.57   05 Aug 2001 16:14:46   HSUCHIN
 * added getRSPcontributionList function
 * 
 *    Rev 1.56   31 Jul 2001 17:02:50   KOVACSRO
 * Added getESoPInfo.
 * 
 *    Rev 1.55   27 Jul 2001 14:01:22   KOVACSRO
 * changed fundClassTradeMin().
 * 
 *    Rev 1.54   Jul 04 2001 16:13:10   JANKAREN
 * trade bug fix
 * 
 *    Rev 1.53   May 18 2001 12:54:24   JANKAREN
 * Sync up SSB(1.49.1.2)
 * 
 *    Rev 1.52   11 May 2001 11:51:28   HSUCHIN
 * Sync up with SSB (1.49.1.1)
 * 
 *    Rev 1.51   May 08 2001 16:34:54   FENGYONG
 * Add transtype for Pending of fundexist
 * 
 *    Rev 1.50   03 May 2001 14:04:32   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.49   30 Mar 2001 17:09:20   BUZILAMI
 * Systematic bank changes
 * 
 *    Rev 1.47   19 Mar 2001 12:00:38   BUZILAMI
 * fixed a refresh problem
 * 
 *    Rev 1.46   Mar 13 2001 11:09:06   YINGZ
 * add functions getAccountHoldingsByCurrencyList etc
 * 
 *    Rev 1.45   Mar 01 2001 14:22:26   ZHANGCEL
 * Added a new function: getEntityIdForAcctOwnerSeq1()
 * 
 *    Rev 1.44   Feb 19 2001 15:17:06   ZHANGCEL
 * Adde new functions: getAcctOwnerEntities(), getBeneficiaries(), getAnnitants() , getAcctOwners(), isSpousalBemeficiary(), isChildBeneficiary() and isBeneficiary()
 * 
 *    Rev 1.43   Feb 12 2001 16:56:22   KOVACSRO
 * Added getAccountPendinTrades().
 * 
 *    Rev 1.42   Jan 24 2001 12:49:02   KOVACSRO
 * Changed getPendingTradeList().
 * 
 *    Rev 1.41   Jan 22 2001 11:19:48   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.40   Jan 17 2001 10:20:14   KOVACSRO
 * Modified getPendingTrades(), Added deletePendingTrades() and a member var.
 * 
 *    Rev 1.39   Jan 10 2001 18:03:20   WINNIE
 * add PurchaseGICAllow and AMSFundAllow method
 * 
 *    Rev 1.38   Dec 20 2000 16:18:18   WINNIE
 * add funddetaillist pointer; remove two parameter for FundClassTradeMinimum
 * 
 *    Rev 1.37   Dec 05 2000 17:14:06   DINACORN
 * Synchronization to C2/C3: Add validateTaxType() and getErrMsg() methods; Add "Revision Control Entries" at the end of file.
* 
*/
