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
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : Trade.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2004
//
// ^CLASS    : Trade
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

//trade update view definition
#include <ifastdataimpl\dse_dstc0115_req.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

#define REVALIDATEFIELD(idField, idDataGroup) \
   if (GETCURRENTHIGHESTSEVERITY () <= WARNING) \
   { \
      revalidateField (idField, idDataGroup); \
      PROMOTECONDITIONS(); \
      CLEARCONDITIONSFRAMECURRENT(); \
   }

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

#define EXTRACT_VALUE_BY_DELIMITER(s, val, delimiter) \
      pos = s.find (delimiter); \
      val = s.substr (0, pos);

#define CHOP_STRING2(s, delimiter) \
         pos = s.find (delimiter); \
         pos = pos != DString::npos && pos + 1 <= s.length() ? pos + 1 : DString::npos; \
         if (pos != DString::npos) \
            s = s.substr (pos); \
         else \
            s = NULL_STRING;



//Forward declarations
class AccShrNumCheck;
class AccountEntityXref;
class Address;
class Agent;
class AmsMstrInfo;
class BankInstructions;
class BatchInfoList;
class Branch;
class Broker;
class DateValidation;
class DilutionAllocList;
class FundBroker;
class FundFeeList;
class FundMaster;
class FundSponsorFeeModelList;
class GIAInvAttribList;
class InvestmentHistoryList;
class MFAccount;
class MFAccountHoldingList;
class ProgressiveIntRateList;
class PSEEAPList;
class RedemptionValidation;
class RESPBeneficiaryAllocationList;
class RESPTransferList;
class RESPTradeValidationList;
class SegTrxValidation;
class SeqFundValidation;
class SplitCommissionList;
class TaxTypeRule;
class TradeBankInstructions;
class TradeBankInstructionsList;
class TradeFromFundAllocList;
class TradeAcctAllocList;
class TradeFundAlloc;
class TradeFundAllocList;
class TransFeeList;
class TransFeeContext;
class TradePayInstructList;
class TradeSettlementLocationsList;
class TradedUnitPosition;
class MatSweepInstrList;
class GIInvestmentDetailsList;
class EstateAllocationList;
class FundLmtOverrideList;
class TransactionList;
class ShareholderBankInstructionsList;
class ExternalInstitutionList;
class PendingTradeError;
class PendingTradeErrorList;
class RDSPTransfer;

class IFASTCBO_LINKAGE Trade : public MFCanBFCbo, private boost::noncopyable
{
friend class TradeFundAlloc;
friend class TradeFundAllocList;
public:
   Trade (BFAbstractCBO &parent);
   virtual ~Trade();
   SEVERITY init ( const BFDataGroupId &idDataGroup,
                   const DString &track = I_("N"),
                   const DString &pageName = NULL_STRING);
   SEVERITY init (const BFData &data);
   SEVERITY initRebook (const BFData &data);
   virtual SEVERITY initRefund (const BFData &data);
   virtual SEVERITY postInitRefund ( const BFDataGroupId &idDataGroup);
   SEVERITY postInitRebook ( const BFDataGroupId &idDataGroup,
                             bool bMultipleRebook);
   SEVERITY initRebookFromHistory(const BFData &data);
   bool isRebook();
   bool isRefund();
   DString getOrigTradeFee() const;
   //mod perm related changes
   void applyModPerm ( const DString &modPerm,
                       const BFDataGroupId &idDataGroup);
   SEVERITY refreshBatch ( const BFDataGroupId& idDataGroup,
                           const DString &track = I_("N"),
                           const DString &pageName = NULL_STRING);
   bool isValidDateLag (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setField ( const BFFieldId &idField, 
                               const DString &dstrValue,
                               const BFDataGroupId &idDataGroup, 
                               bool bFormatted = true, 
                               bool bSideEffect = false, 
                               bool bCheckCurrentValue = true);
   virtual void getField ( const BFFieldId &idField, 
                           DString &fieldValue, 
                           const BFDataGroupId &idDataGroup, 
                           bool formattedReturn = false) const;
//children of Trade, getters
   SEVERITY getAccountAllocationList ( TradeAcctAllocList *&pAccountAllocationList, 
                                       const BFDataGroupId &idDataGroup, 
                                       bool bCreate = true);
   SEVERITY getFromFundAllocationList ( TradeFromFundAllocList *&pTradeFromFundAllocList, 
                                        const BFDataGroupId &idDataGroup, 
                                        bool bCreate = true);
   SEVERITY getFundAllocationList ( TradeFundAllocList *&pFundAllocationList, 
                                    const BFDataGroupId& idDataGroup, 
                                    bool bCreate = true);
   SEVERITY getSplitCommissionList (SplitCommissionList *&pSplitCommissionList,
                                    const BFDataGroupId &idDataGroup,
                                    bool bCreate = true,
                                    bool bRefresh = false);
   SEVERITY getBankInstructionsList (TradeBankInstructionsList *&pTradeBankInstructionsList, 
                                     const BFDataGroupId &idDataGroup, 
                                     bool bCreate = false,
                                     BFAbstractCBO* pObjToCheck = NULL);
   SEVERITY getEstateAllocationList (EstateAllocationList *&pEstateAllocationList, 
                                     const BFDataGroupId &idDataGroup, 
                                     bool bCreate = true);
   SEVERITY getTransFeeList (TransFeeList *&pTransFeeList, 
                             const BFDataGroupId &idDataGroup,
                             bool bCreate = false);
   SEVERITY getTransFeeContext (TransFeeContext *&pTransFeeContext, 
                                const BFDataGroupId &idDataGroup);
   SEVERITY getBroker (Broker *&broker,
                       const BFDataGroupId &idDataGroup);
   SEVERITY getBranch (Branch *&branch,
                       const BFDataGroupId &idDataGroup);
   SEVERITY getAgent (Agent *&agent,
                      const BFDataGroupId &idDataGroup);
   SEVERITY getAccountHoldings ( MFAccountHoldingList *&pMFAccountHoldings,
                                 const BFDataGroupId &idDataGroup,
                                 const DString &fundCode = NULL_STRING,
                                 const DString &classCode = NULL_STRING);
   SEVERITY getAccountToHoldings ( MFAccountHoldingList *&pMFAccountToHoldings,
                                   const BFDataGroupId &idDataGroup,
                                   const DString &fundCode = NULL_STRING,
                                   const DString &classCode = NULL_STRING);
   SEVERITY getFundHoldingsForAccount ( const DString &accountNum,
                                        const DString &fundCode,
                                        const DString &classCode,
                                        MFAccountHoldingList *&pMFAccountHoldings,
                                        const BFDataGroupId &idDataGroup);
   SEVERITY getMFAccountHoldingList(const DString &accountNum,
                                        const DString &dstrFund,
                                        const DString &dstrClass,
                                        const DString &asOfDate,
                                        const DString &accBalMode,
                                        MFAccountHoldingList *&pMFAccountHoldingList,
                                        const BFDataGroupId &idDataGroup);
   SEVERITY getDefaultBankInstructions ( BFCBO *&pBase, 
                                         const BFDataGroupId &idDataGroup);
   SEVERITY getDilutionAllocList (DilutionAllocList *&pDilutionAllocList, 
                                  const BFDataGroupId &idDataGroup, 
                                  bool bCreate = true);
   SEVERITY getSettlementLocsList (TradeSettlementLocationsList *&pTradeSettlementLocationsList, 
                                   const BFDataGroupId &idDataGroup, 
                                   bool bCreate  = true);
   SEVERITY getRESPBenefAllocationList (RESPBeneficiaryAllocationList *&pRESPBeneficiaryAllocationList, 
                                        const BFDataGroupId &idDataGroup, 
                                        bool bCreate  = true);
   SEVERITY getRESPTransferList (RESPTransferList *&pRESPTransferList, 
                                 const BFDataGroupId &idDataGroup, 
                                 bool bCreate  = true);
   SEVERITY getMaturityInstrList (MatSweepInstrList *&pMaturityInstrList, 
                                  const BFDataGroupId &idDataGroup, 
                                  bool bCreate = true);
   SEVERITY getPSEData ( PSEEAPList *&pPSEEAPList, 
                         const BFDataGroupId &idDataGroup);
   SEVERITY getGIFundDefaults ( GIAInvAttribList *&pGIAInvAttribList, 
                                const BFDataGroupId &idDataGroup, bool doSideEffects = true);
   SEVERITY getTradePayInstructList (TradePayInstructList *&pTradePayInstructList, 
                                     const BFDataGroupId &idDataGroup, 
                                     bool bCreate = true,
                                     bool bDefault = false);
   SEVERITY getInvestmentHistoryList(InvestmentHistoryList *&pInvestmentHistoryList,
                                     const BFDataGroupId &idDataGroup,
                                     bool bForceRefresh = false);
   SEVERITY getProgressiveIntRateList(ProgressiveIntRateList *&pProgressiveIntRateList,
                                      const BFDataGroupId &idDataGroup,
                                      bool bForceRefresh = false);
   SEVERITY getProgressiveIntRateListForDisplay(ProgressiveIntRateList *&pProgressiveIntRateList,
                                                const BFDataGroupId &idDataGroup,
                                                bool bForceRefresh = true);
   SEVERITY getTradePayToEntity( DString &payToEntity,
                                 const BFDataGroupId &idDataGroup);
   SEVERITY validateDefaultSettleInstr( const DString &accountNum,
                                        const BFDataGroupId &idDataGroup);
   SEVERITY calculateEstimatedAllocAmount (DString &dstrCaclAmount, const BFDataGroupId &idDataGroup);

   SEVERITY getGIInvestmentDetails ( GIInvestmentDetailsList *&pGIInvestmentDetailsList, 
                                     const BFDataGroupId &idDataGroup, 
                                     bool bCreate = true);

   SEVERITY getGIInvestmentTotals ( GIInvestmentDetailsList *&pGIInvestmentDetailsList, 
                                        const BFDataGroupId &idDataGroup);
   
   SEVERITY getAdjustTransactionList( TransactionList* &pTransactionList, 
	                                  const BFDataGroupId& idDataGroup);
//whether dilution is allowed   or not
   virtual bool isDilutionAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isAccountCloningAllowed (const BFDataGroupId &idDataGroup);
   virtual bool areRESPBenefAllocationsAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isRESPTransferAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isAssociationWithBeneficiaryAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isAssociationToOriginalContribAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isPSEEAPAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isAIPAllowed (const BFDataGroupId &idDataGroup);
   //P0185010.FN02.R02.01 - Delivering EAP written notice and tax info return
   virtual bool isEAPAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isSEGPortfolio (const BFDataGroupId &idDataGroup);
   virtual bool isCASHSettleESGElig (const BFDataGroupId &idDataGroup);

//whether banking is allowed
   bool isBankingNeeded (const BFDataGroupId &idDataGroup, BFAbstractCBO* pObjToCheck = NULL);
//whether the shareholder address is needed
   virtual bool isShareholderAddressNeeded (const BFDataGroupId &idDataGroup);
//whether allocations are allowed or not
   virtual bool areAllocationsAllowed (const BFDataGroupId &idDataGroup);
//whether split commissions are allowed
   virtual bool isSplitCommissionAllowed (const BFDataGroupId &idDataGroup);
//whether tax rates are allowed
   virtual bool areTaxRatesAllowed (const BFDataGroupId &idDataGroup);
//whether settle locations are allowed
   virtual bool isSettleLocAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isGIAAttribAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isGIInvestmentListApplicable(const BFDataGroupId &idDataGroup);
   virtual bool isEstateAllocationListApplicable(const BFDataGroupId &idDataGroup);
   virtual bool isMaturityInstrAllowed (const BFDataGroupId &idDataGroup);
//due to the special nature of settle location, reset should be overridden
   SEVERITY resetSettleLoc ( const BFDataGroupId &idDataGroup, 
                             bool bFrom = true);
   SEVERITY resetPSE (const BFDataGroupId &idDataGroup);
   SEVERITY resetGIAAttrib (const BFDataGroupId &idDataGroup);
//multiple settle location
   virtual bool areMultipleSettleLocAllowed (const BFDataGroupId &idDataGroup);
//method looks at the fee trans list and copies the values over to the 
//old fee fields of 115, kept there so cycle will not break
   SEVERITY copyFeeValuesForCycleProcessing (const BFDataGroupId &idDataGroup);
//SP (Jan 2005), PTS 10037503
   SEVERITY makeDirty (const BFDataGroupId &idDataGroup);
//SP PET 1190/04, expose this method to public
    bool isBackdatedTrade (const BFDataGroupId &idDataGroup);
    virtual bool isSegTrade (const BFDataGroupId &idDataGroup);
//PET 1203/05
    virtual bool isROAApplicable (const BFDataGroupId &idDataGroup);
    bool isROATransType (const BFDataGroupId &idDataGroup);
    virtual bool isEUSDApplicable (const BFDataGroupId &idDataGroup);
    bool isFundInScope (const BFDataGroupId &idDataGroup);
    bool isFundLookedThru (const BFDataGroupId &idDataGroup);
    bool canFundBeAllocated (const DString& fundCode, const DString& classCode, const BFDataGroupId &idDataGroup);
    void checkBackdatedTrade (bool check = true);
//whether split payments are allowed or not
   virtual bool arePayInstructAllowed (const BFDataGroupId &idDataGroup);
   void setRebookForSameAcctTransType( bool bSameAcct = true ){ _bSameAccount = bSameAcct; };
   bool isRebookForSameAcctTransType(){return _bSameAccount;};
   void setInitialRebookTradeAmount( const DString& dstrInitialAmount ){ _strInitialRebookAmt = dstrInitialAmount;};
   DString getInitialRebookTradeAmount(){ return _strInitialRebookAmt;};
   SEVERITY getFundUnitPrecision(const DString& dstrFund, const DString& dstrClass, DString& precision );
   bool canUserModifyBatch (const DString &batchUser, const BFDataGroupId &idDataGroup);
   void initRebookBatch (const DString &rebookBatch, const BFDataGroupId &idDataGroup);
   bool IsInitPending() { return _bInitPending; }

   SEVERITY getExchRate (double &exchRate, 
                         const BFDataGroupId &idDataGroup, 
                         const DString &exactDate = I_("N"));
   SEVERITY isBaseCommissionApplicableAndGetSFACRate ( bool &baseCommApplicable,
                                                       DString &strSFACRate,
                                                       const BFDataGroupId &idDataGroup, 
                                                       const DString dstrAllocFundCode  = NULL_STRING, 
                                                       const DString dstrAllocClassCode = NULL_STRING);
   SEVERITY updateGuaranteesOverrideFlag(bool bFlag, const BFDataGroupId &idDataGroup);
   SEVERITY applyTransFeeRateToAllocation(const BFDataGroupId &idDataGroup);
   bool hasAllocations (const BFDataGroupId &idDataGroup);
   SEVERITY getExternalInstitutionList(ExternalInstitutionList*& pExternalInstitutionList, 
                                       const BFDataGroupId& idDataGroup);
   SEVERITY getPendingTradeErrorList( PendingTradeErrorList *&pPendingTradeErrorList, 
									  const BFDataGroupId& idDataGroup, 
									  bool bCreate);
   virtual bool setCashDateUpdatable( DString &tradeDate, const BFDataGroupId &idDataGroup );
   SEVERITY getAcctUnitsPrecision (	DString &unitsPrecisionAcct, const BFDataGroupId& idDataGroup);
   virtual bool isRDSPTransferAllowed (const BFDataGroupId &idDataGroup);
   SEVERITY getRDSPTransfer (RDSPTransfer *&pRDSPTransfer, const BFDataGroupId &idDataGroup, bool bCreate = true);   

protected:

//the place used to set the transaction type
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup) = 0;
//the place where derived classes should init fields for pending trades
   virtual SEVERITY doInit (const BFData &data);
//function to validate pending allocated trade added for INC0039323
   virtual SEVERITY validatePendingTradeAllocated(const BFDataGroupId &idDataGroup);
//things that should be done prior to doInitWithDefaultValues, should go in here
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
//based on the transaction type set in the previous method, reads various defaults
   virtual SEVERITY transTypeRelatedChanges (const BFDataGroupId &idDataGroup) = 0;
//each class should return the fund and class fields they are most interested in
   virtual void getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                          BFFieldId &classCodeFieldId) = 0;
   virtual void getAccountFieldId (BFFieldId &accountFieldId) = 0;
//base class' virtual methods
   virtual void doReset (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
   virtual SEVERITY doPreSetField ( const BFFieldId &idField, 
                                    DString &value, 
                                    const BFDataGroupId &idDataGroup, 
                                    bool bFormatted);
   virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void populateFieldsWithDefaultValues (const BFDataGroupId &idDataGroup, const long &lMod);
   virtual void setFieldWithDefaultValue(const BFFieldId &idField,const BFDataGroupId &idDataGroup );
//whether a trade is hypothetical or not
   virtual bool isHypo ();
//allocation helpers
   //each class should define whether or not they support allocation
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup) = 0;
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup) = 0;
   void setAllocField ( const BFFieldId &idFromField, 
                        const BFFieldId &idToField, 
                        const BFDataGroupId &idDataGroup);
   void setFromAllocField ( const BFFieldId &idFromField, 
                            const BFFieldId &idToField, 
                            const BFDataGroupId &idDataGroup);
   bool hasFromAllocations (const BFDataGroupId &idDataGroup);
  
   bool hasTradePayInstruct (const BFDataGroupId &idDataGroup);
//whether file processor applies for a type of trade
   virtual bool isACHApplicable (const BFDataGroupId &idDataGroup);
//virtual validation methods 
   virtual SEVERITY validateOrderType ( const DString &orderType, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY orderTypeRelatedChanges ( const BFDataGroupId &idDataGroup, 
                                              bool bValidateDate = true);
   virtual SEVERITY validateNetOrdType (const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateSegBackdates (const BFDataGroupId &idDataGroup);

//account validation
   virtual SEVERITY validateAccount ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountTrade ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountToTrade ( MFAccount *pMFAccountTo, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAccountTo ( MFAccount *pMFAccountTo, 
                                        const BFDataGroupId &idDataGroup);
//fund validation
   virtual SEVERITY validateFundCode ( const DString &fundCode, 
                                       const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundBalance ( const DString &accountNum,
                                          const DString &fundCode,
                                          const DString &classCode,
                                          const DString &amount,
                                          const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateTUP (const BFDataGroupId &idDataGroup);
   SEVERITY getTradedUnitPosition (TradedUnitPosition *&pTradedUnitPosition, const BFDataGroupId &idDataGroup);
   bool isTUPApplicable (const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateToFundCode ( const DString &fundCode, 
                                         const BFDataGroupId &idDataGroup);
   SEVERITY validateClassCode ( const DString &fundCode, 
                                const DString &classCode, 
                                const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateMasterActAMS (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundClass (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundClass ( const DString &fundCode, 
                                        const DString &classCode, 
                                        const DString &accountNum, 
                                        const BFDataGroupId &idDataGroup);
   SEVERITY validateToFundClass (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToFundClass ( const DString &fundCode, 
                                          const DString &classCode, 
                                          const DString &accountNum, 
                                          const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFromToFundClass ( const DString &fromCode,
                                              const DString &fromClass,
                                              const DString &toCode,
                                              const DString &toClass,
                                              const BFDataGroupId &idDataGroup);

   bool isFullExchgParentFndClsToParentFndCls(const BFDataGroupId &idDataGroup,
                                    const DString &fundFrom, 
                                    const DString &classFrom, 
                                    const DString &fundTo, 
                                    const DString &classTo);

//PET1117.FN6.R6
   SEVERITY setSettleCurrencyFromFund ( const DString &fundCode, 
                                        const DString &classCode, 
                                        const BFDataGroupId &idDataGroup);
//PET1117.FN6.R6
   virtual SEVERITY filterSettleCurrencyForFund ( const DString &inCurrSubstList, 
                                                  DString &currSubstList,
                                                  const BFDataGroupId &idDataGroup);
//PET1117.FN6.R6
   SEVERITY filterSettleCurrencyForFund ( const DString &fundCode,
                                          const DString &classCode,
                                          const DString &inCurrSubstList,
                                          DString &currSubstList,
                                          const BFDataGroupId &idDataGroup);  

   SEVERITY Trade::filterSettleCurrencybyTaxTypeRule(const DString &dstrinSubList,
													  const DString &dstrTaxTypeRuleCurrSet,
												       DString &stroutCurrencySet,
													   const BFDataGroupId &idDataGroup);
   SEVERITY canFundTrade ( const DString &broker,
                           const DString &branch,
                           const DString &agent,
                           const DString &transType,
                           const DString &accountNum,
                           const DString &fundCode,
                           const DString &classCode,
                           long lErrorId,
                           long lWarnId,
                           const BFDataGroupId &idDataGroup,
                           bool bCheckBrokerPermits = false);
   SEVERITY initBatch (const BFDataGroupId &idDataGroup);
   SEVERITY validateSettleLocations (const BFDataGroupId &idDataGroup);
   SEVERITY validateBeneficiaryAllocation (const BFDataGroupId &idDataGroup);
   SEVERITY getNumberOfUnits (double &dAvalUnits, const BFDataGroupId& idDataGroup);

   bool isFundSoftCapped (const DString &fundCode, 
                          const DString &classCode, 
                          const BFDataGroupId &idDataGroup);
   virtual SEVERITY setDefaultOrderType (const BFDataGroupId &idDataGroup);
   virtual bool isWireSupported (const BFDataGroupId &idDataGroup);
   virtual SEVERITY fromFundClassRelatedChanges ( const DString &fundCode, 
                                                  const DString &classCode, 
                                                  const BFDataGroupId &idDataGroup);
   virtual SEVERITY toFundClassRelatedChanges ( const DString &fundCode, 
                                                const DString &classCode, 
                                                const BFDataGroupId &idDataGroup);
   virtual SEVERITY amtTypeExtraRelatedChanges (const BFDataGroupId &idDataGroup);
//PET1117.FN6.R13
   SEVERITY validatePUEVCapableFund ( const DString &fundCode, 
                                      const DString &accountNum, 
                                      const BFDataGroupId &idDataGroup);
//PET1117.FN56.R2.5.0
   SEVERITY validateInvestroCapableFund ( const DString &fundCode, 
                                          const DString &accountNum, 
                                          const BFDataGroupId &idDataGroup);
//PET1117.FN56.R2.2.0 
   SEVERITY validateFundBrokerCode ( const DString &fundBroker,
                                     const BFDataGroupId &idDataGroup);
//PET1117.FN6.R3.7. 0
   SEVERITY validateFundSponsorFeeModelCode ( const DString &fundCode,
                                              const DString &accountNum,
                                              const BFDataGroupId &idDataGroup);
   SEVERITY getFundSponsorFeeModelList ( const DString &accountNum,
                                         const DString &fundCode,
                                         FundSponsorFeeModelList *&pFundSponsorFeeModelList,
                                         const BFDataGroupId &idDataGroup);
//PET1117.FN6/FN56
   SEVERITY thirdPartyFundRelatedChanges (const BFDataGroupId &idDataGroup);
//PET1117.FN.56.R2.3.0 
   SEVERITY aggregateOptionRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY refreshAllocations (const BFDataGroupId &idDataGroup);
   SEVERITY refreshSplitCommissions (const BFDataGroupId &idDataGroup);
//PET 2217/13
   SEVERITY refreshTradePayInstructions (const BFDataGroupId &idDataGroup);

   SEVERITY isFeeApplicable (const DString &dstrFee, bool &bFeeApplicable, const BFDataGroupId &idDataGroup);
//dates validation
   virtual SEVERITY validateTradeDate ( const DString& tradeDate, 
                                        const BFDataGroupId &idDataGroup);
   SEVERITY validateDepositDate ( const DString &depositDate, 
                                  const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateValueDate ( const DString &valueDate, 
                                        const BFDataGroupId &idDataGroup);
   SEVERITY validateDate ( const DString &validationType, 
                           const BFFieldId &idField, 
                           const DString &strValue, 
                           const BFDataGroupId &idDataGroup);
//cert rquired
   virtual SEVERITY validateCertRequired ( const DString &certRequired,
                                           const BFDataGroupId &idDataGroup);
   SEVERITY validateCertRequired ( const DString &fundCode,
                                   const DString &classCode,
                                   const DString &certRequired,
                                   const BFDataGroupId &idDataGroup);
//cash date
   void setCashDateUpdatable (const BFDataGroupId &idDataGroup);
   virtual bool isCashDateUpdatable ( FundMaster *pFundMaster,
                                      const BFDataGroupId &idDataGroup);
//gross net/amount/amt type
   virtual SEVERITY validateAmountAmtType (const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateAmount ( const DString &amount,  
                                     const BFDataGroupId& idDataGroup);
   void getFormattedAmount ( const BFDataGroupId &idDataGroup, 
                             DString &value) const;
   virtual SEVERITY validateAmtType ( const DString &amtType,
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmtTypeGrossNet (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateMinFromFundAmount ( const DString &account,
                                                const DString &fundCode,
                                                const DString &classCode,
                                                const DString &amtType,
                                                const DString &amount,
                                                const DString &broker,
                                                const DString &branch,
                                                const DString &slsrep,
                                                const DString &depositType, //in1419539
                                                const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateMinToFundAmount ( const DString &account,
                                              const DString &fundCode,
                                              const DString &classCode,
                                              const DString &amtType,
                                              const DString &amount,
                                              const DString &broker,
                                              const DString &branch,
                                              const DString &slsrep,
                                              const DString &depositType, //in1419539
                                              const BFDataGroupId &idDataGroup);
   SEVERITY validateAmountPrecision (const BFDataGroupId &idDataGroup);
   SEVERITY fundClassTradeMinimumAmtCheck ( const DString &transType,
                                            const DString &accountNum,
                                            const DString &fundCode, 
                                            const DString &classCode,
                                            const DString &amtType, 
                                            const DString &amount, 
                                            const DString &currency, 
                                            DString &initPurch, 
                                            const DString &broker,
                                            const DString &branch,
                                            const DString &slsrep,
                                            const DString &depositType, //in1419539
											const DString &tradeDate,
                                            const BFDataGroupId &idDataGroup,
                                            bool bFullExchPrntToPrnt = false,
                                            const DString &Indc = I_(""),
                                            const DString &adjForTransNum = I_(""),
											const DString &transNum = I_(""));
   virtual SEVERITY validateFromSoftCapCheck (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToSoftCapCheck (const BFDataGroupId &idDataGroup);
   SEVERITY fundClassSoftCapCheck ( const DString &transType,
                                    const DString &accountNum,
                                    const DString &fundCode, 
                                    const DString &classCode,
                                    const BFDataGroupId &idDataGroup);
//ams
   SEVERITY amsMinAmtCheck ( const DString &transType,
                             const DString &accountNum,
                             const DString &fundCode, 
                             const DString &classCode,
                             const DString &amtType, 
                             const DString &amount, 
                             const DString &currency,
                             const DString &broker,
                             const DString &branch,
                             const DString &slsrep,
                             const DString &depositType, //in1419539
                             bool bOverrideFundLevelCheck,
							 const DString &effectiveDate,
                             const BFDataGroupId &idDataGroup);
   bool isAMSLimitationCheckRequired ( const DString &accountNum, 
                                       const BFDataGroupId &idDataGroup);
   virtual SEVERITY amsFundClassTradeMinAmtCheck ( const DString &transType,
                                                   const DString &accountNum,
                                                   const DString &fundCode, 
                                                   const DString &classCode,
                                                   const DString &amtType, 
                                                   const DString &amount, 
                                                   const DString &currency, 
                                                   const DString &exchRate, 
                                                   const DString &effectiveDate, 
                                                   const DString &broker,
                                                   const DString &branch,
                                                   const DString &slsrep,
                                                   const DString &depositType, //in1419539
                                                   //ams   
                                                   const DString &amsCode,
                                                   AmsMstrInfo *pAMSMstrInfo,
                                                   const DString &taxJuris,
                                                   const DString &provResid,
                                                   const DString &accountType,
                                                   const DString &taxType,
                                                   const DString &acctDesign,
                                                   bool &bOverrideFundLevelCheck,
                                                   const BFDataGroupId &idDataGroup,
                                                   bool bFullExchPrntToPrnt);
   SEVERITY checkEntityOverride ( const DString &transType,
                                  const DString &fundCode,
                                  const DString &classCode,
                                  const DString &accountNum,
                                  bool &bOverride, 
                                  bool &bErrorSeverity, 
                                  const BFDataGroupId &idDataGroup);
   virtual bool isBrokerAllowed ( const DString &transType,
                                  const DString &accountNum,
                                  const DString &fundCode, 
                                  const DString &classCode,
                                  const BFDataGroupId &idDataGroup);
   virtual bool isAgentAllowed (const BFDataGroupId &idDataGroup);
//currency validation
   SEVERITY validateCurrencyTaxType ( const DString &accountNum, 
                                      const DString &currency, 
                                      const BFDataGroupId &idDataGroup);
//deposit type, id validation
   virtual SEVERITY validateDepositType ( const DString &depositType, 
                                          const BFDataGroupId &idDataGroup);
//redemption code
   virtual SEVERITY validateRedCode ( const DString &redCode, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY getAtCostTIKStatus ( const BFDataGroupId &idDataGroup, 
                                         const DString &dstrFundCodeIn, 
                                         const DString &dstrClassCodeIn,
                                         bool  blInAllocation,
                                         bool &blIsAtCostTIK);
   virtual bool isFullRedemption (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundCodeRedCodeAmount (const BFDataGroupId &idDataGroup);
//settle source
   virtual SEVERITY validateSettleSource ( const DString &settleSource,
                                           const BFDataGroupId &idDataGroup);

   SEVERITY commonValidateSettleSource( const DString &settleSource, 
                                        const BFDataGroupId &idDataGroup); 

//settle type
   virtual SEVERITY validateSettleType ( const DString &settleType,
                                         const BFDataGroupId &idDataGroup);
//pay type
   virtual SEVERITY payTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validatePayType ( const DString &payType,
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateCurrency ( const DString &currency,
                                       const BFDataGroupId &idDataGroup);
   virtual SEVERITY validatePayTypeBank (const BFDataGroupId &idDataGroup); //bank must be set up for EFT
//banking helpers
   virtual SEVERITY getDefaultBankInstructions ( BankInstructions *&pBankInstructions, 
                                                 const BFDataGroupId &idDataGroup);
   SEVERITY getShareholderBankInstructions ( BankInstructions *&pBankInstructions, 
                                             const DString &acctUsageCode,
                                             const BFDataGroupId &idDataGroup);
   SEVERITY getLastEFTBankInstructions ( BankInstructions *&pBankInstructions, 
                                         const BFDataGroupId &idDataGroup);
//STP project PET 2192 FN10/11 
   SEVERITY getPayEntityBankInstructions ( BankInstructions *&pBankInstructions, 
                                           const DString &acctUsageCode,
                                           const BFDataGroupId &idDataGroup);
   virtual void getDefaultPaymentFor ( DString &paymentFor, 
                                       const BFDataGroupId &idDataGroup);
//redemption code, deposit code
   SEVERITY loadDepRedCodeSubstList ( const DString &account, 
                                      const DString &codeType, 
                                      const BFDataGroupId &idDataGroup);
//settle location, clearing account
   SEVERITY setSettlementLocationSubstList ( const BFFieldId &idFieldCode,
                                             const DString &accountNum,
                                             const BFDataGroupId &idDataGroup);
   SEVERITY setSettlementCodeSubstList ( const BFFieldId &idFieldCode,
                                         const DString &accountNum,
                                         const BFDataGroupId& idDataGroup);
   SEVERITY setDefaultSettlementLocation ( const BFFieldId &idFieldCode,
                                           const DString &accountNum,
                                            const BFDataGroupId& idDataGroup);
   SEVERITY setDefaultAcctSettlementInstr ( const DString &accountNum,
                                            const BFDataGroupId& idDataGroup,
                                            bool bFrom = true);
   SEVERITY setAcctSettlementInstr ( const DString &settlementInstrCode,
                                     const DString &accountNum,
                                     const BFDataGroupId& idDataGroup,
                                     bool bFrom = true);
   SEVERITY setSettleLocationDescription ( const BFFieldId &idFieldCode, 
                                           const BFFieldId &idFieldDescription, 
                                           const BFDataGroupId &idDataGroup);
   SEVERITY clearingRelatedChanges ( const BFDataGroupId &idDataGroup,
                                     bool bFrom = true);
// ESG Settlement - PET 1334/01
   SEVERITY esgSettleRelatedChange (const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateESGSettle (const DString &strValue, const BFDataGroupId &idDataGroup);
   //bool isCASHSettleESGElig (const BFDataGroupId &idDataGroup);
   bool allowESGSettleForNominee (const BFDataGroupId &idDataGroup);
   bool allowESGSettleForIntermediary (const BFDataGroupId &idDataGroup);

   bool isHouseBroker (const BFDataGroupId &idDataGroup);
//returns the type of the trade object
   bool isPurchase (const BFDataGroupId &idDataGroup);
   bool isPurchaseLike (const BFDataGroupId &idDataGroup);
   bool isTransfer (const BFDataGroupId &idDataGroup);
   bool isExchange (const BFDataGroupId &idDataGroup);
   bool isExchangeLike (const BFDataGroupId &idDataGroup);
   bool isInterClassSwitch (const BFDataGroupId &idDataGroup);
   bool isRedemption (const BFDataGroupId &idDataGroup);
   bool isRedemptionLike (const BFDataGroupId &idDataGroup);
   bool isRollover (const BFDataGroupId &idDataGroup);
   bool isAllTransfer (const BFDataGroupId &idDataGroup);
   bool isMgmtFee (const BFDataGroupId &idDataGroup);
   bool isAdvisorFee (const BFDataGroupId &idDataGroup);
   bool isAdminFee (const BFDataGroupId &idDataGroup);
   bool isOneSideTrade (const BFDataGroupId &idDataGroup);
   bool isAutoWithdraw (const BFDataGroupId &idDataGroup);
   bool isManualDividend (const BFDataGroupId &idDataGroup);
   bool isManualMFRAdjustment(const BFDataGroupId &idDataGroup);
   bool isAllPurchase (const BFDataGroupId &idDataGroup);
//convenient methods
   SEVERITY getFundField ( const BFFieldId &idField, 
                           DString &strValue,
                           const BFDataGroupId &idDataGroup);
   SEVERITY getFundField ( const DString &fundCode, 
                           const DString &classCode, 
                           const BFFieldId &idField, 
                           DString &strValue);
   SEVERITY getAccountField ( const BFFieldId &idField, 
                              DString &value,
                              const BFDataGroupId &idDataGroup);
//returns the interest account for validations
   SEVERITY getAccount ( MFAccount *&pMFAccount, 
                         const BFDataGroupId &idDataGroup);

   SEVERITY getTradeDateValidation ( DateValidation *&pTrade_DateValidation, 
                                     const DString &validationType,
                                     const DString &tradeDate, 
                                     const DString &settleDate,
                                     const DString &depositDate,
                                     const DString &valueDate, 
                                     const DString &settleInDate,
									 const DString &tradeInDate,
                                     const BFDataGroupId &idDataGroup);
   SEVERITY getRedemptionValidation ( RedemptionValidation *&pRedemptionValidation,
                                      const BFDataGroupId &idDataGroup);
   SEVERITY getDefaultFundBrokerCode ( const DString &accountNum,
                                       const DString &fundCode,
                                       DString &defaultFundBrokerCode,
                                       DString &dstrFdBrokerDefaultLevel,
                                       const BFDataGroupId &idDataGroup);
   SEVERITY getFundBroker ( const DString &fundBrokerCode, 
                            FundBroker *&pFundBroker,
                            const BFDataGroupId &idDataGroup);
   int getYear (const DString &date);
// fund balance/nav price/unit price
   double getUnitPrice ( const DString &fundCode, 
                         const DString &classCode, 
                         const DString &fromDate, 
                         const DString &toDate, 
                         const BFDataGroupId &idDataGroup,
                         const DString tradeTransType = I_(""),  
                         const DString &prevDatePressed = I_("Y"), 
                         const DString &nextDatePressed = I_("N"));
   void getUnitPriceDetl (BigDecimal &dUnitValue,         
                          BigDecimal &dGAV,   
                          BigDecimal &dMultiPriceUsageID,
                          DString &dstrUnitId,
                          const DString &fundCode,
                          const DString &classCode, 
                          const DString &fromDate, 
                          const DString &toDate,
                          const BFDataGroupId &idDataGroup,
                          const DString &tradeTransType = I_(""),  
                          const DString &prevDatePressed = I_("Y"), 
                          const DString &nextDatePressed = I_("N"),
                          const DString &getTransType = I_(""),
                          const DString &GetNextAvailRate = I_("N"));
   double getFundBalance ( const DString &accountNum,
                           const DString &fundCode,
                           const DString &classCode,
                           const BFDataGroupId &idDataGroup);
   double getFundNAV ( const DString &accountNum,
                       const DString &fundCode,
                       const DString &classCode,
                       const BFDataGroupId &idDataGroup);
   bool canCloseAccount (const BFDataGroupId &idDataGroup);
   SEVERITY getTradeDefault ( const BFFieldId &genControlFieldId, 
                              DString &defValue, 
                              const BFDataGroupId &idDataGroup);
   bool isSameAccountOwner (const BFDataGroupId &idDataGroup);
   SEVERITY getFeeModelCode ( const DString &accountNum,
                              DString &feeModelCode, 
                              const BFDataGroupId &idDataGroup);
   SEVERITY getAccShrNumCheck ( const DString &accountNum,
                                AccShrNumCheck *&pAccShrNumCheck,
                                const BFDataGroupId &idDataGroup);
//PET1117.FN66,67,68 SWIFT?Investro/PartnerWorld
   SEVERITY loadNetworkIDValues (const BFDataGroupId &idDataGroup);
   SEVERITY getFundBrokerRoutingType ( const DString &accountNum,
                                       const DString &fundCode,
                                       DString &routingType,
                                       const BFDataGroupId &idDataGroup);
   SEVERITY validateAmtTypeForNetworkIDAndFundBroker ( const DString &account,
                                                       const DString &fundCode,
                                                       const BFDataGroupId &idDataGroup,
                                                       const DString &networkIds = NULL_STRING);

   SEVERITY validateAIPEntityTaxJuris (const DString &dstrAIPEntity, 
                                       const DString &dstrAccountNum,
                                       const BFDataGroupId &idDataGroup);

   SEVERITY validateAIPEntityAddress (const DString &dstrAIPEntity, 
                                      const DString &dstrAccountNum,
                                      const BFDataGroupId &idDataGroup);

   //P0185010.FN02.R02.01 - Delivering EAP written notice and tax info return
   SEVERITY validateEAPEntityAddress (const BFDataGroupId &idDataGroup);
                                      
   bool areAccountAndFundPUEVCapable (const BFDataGroupId &idDataGroup);
   SEVERITY setOtherConfirmTypeDefaultValues (const BFDataGroupId &idDataGroup);
   bool accountHasCategory( const DString &dstrCategory, const BFDataGroupId &idDataGroup);
//PET 1203/05 MFS commission class A
   virtual void roaAmountRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual void getROARelatedFields ( DString &amt, 
                                      DString &amtType, 
                                      DString &currency,
                                      DString &exchRate, 
                                      const BFDataGroupId &idDataGroup);
   SEVERITY clearROAAmount (const BFDataGroupId &idDataGroup);
//Incident #273734 - deals with the settle currency in a 
//non-multi currency environment for full redemptions and for closing accounts
   SEVERITY getAccountHoldingsCurrency (  DString &currency, 
                                          const BFDataGroupId &idDataGroup);
   SEVERITY setAccountHoldingsCurrency (const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateEUSDBackdates( const DString &dstrFund,
                                           const DString &dstrClass,
                                           const DString &dstrAccountNum,
                                           const BFDataGroupId &idDataGroup );

   SEVERITY getSegFundValidation ( SeqFundValidation *&pSeqFundValidation,
                                   const DString &fundCode, 
                                   const DString &classCode, 
                                   const DString &accountNum, 
                                   const DString &tradeDate,
                                   const BFDataGroupId &idDataGroup,
                                   const DString &dstrEventTransType,
                                   const DString &dstrTransType,
                                   const DString &toFundCode,
                                   const DString &toClassCode,
                                   const DString &toAccountNum);
   virtual bool isMCHSecRecIndApplicable (const BFDataGroupId &idDataGroup); 
   virtual void setDefaultPayType (const DString dstrAccountNum, DString &payType, const BFDataGroupId &idDataGroup);
   virtual void setClearingAccDefaultPayType (const DString dstrAccountNum, DString &payType,const BFDataGroupId &idDataGroup);
   bool isSegEnvironment (const BFDataGroupId &idDataGroup);
   SEVERITY setTradeDateToRespDate (const BFDataGroupId &idDataGroup);
   SEVERITY setDilutionRespDateInvalid (const BFDataGroupId &idDataGroup);
   SEVERITY setSettleLocsInstructionsInvalid( const BFDataGroupId &idDataGroup );
   SEVERITY setBeneficiaryAllocationsInvalid( const BFDataGroupId &idDataGroup);
   SEVERITY validateClosedCountry ( const DString &accountNum,
                                    const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateRESPContrDetlTaxYear(const DString& strValue, const BFDataGroupId &idDataGroup);
   virtual SEVERITY validatePayInstrOption(const DString& strValue, const BFDataGroupId &idDataGroup);
   SEVERITY get10PrcntAcAmt( DString &dstrAcAmt10Prcnt,
                             const DString &strAccountNum,
                             const DString &strRESPContrTaxYear,
                             const DString &strLinkedEntityId,
                             const BFDataGroupId &idDataGroup );
   virtual SEVERITY getDefaultFundClassPayType (const DString dstrAccountNum, 
                                                DString &payType,
                                                const DString dstrFundCode,
                                                const DString dstrClassCode,
                                                const BFDataGroupId &idDataGroup);
   SEVERITY getFeeParams ( const DString& feeCode,
                           const DString& fundCode,
                           const DString& classCode,
                           const DString& effectiveDate,
                           const DString& accountNum,
                           const DString& broker,
                           const DString& branch,
                           const DString& slsrepCode,
                           FundFeeList *&pFundFeeList, 
                           const BFDataGroupId &idDataGroup);
   SEVERITY forcedRateRelatedChanges(const BFDataGroupId& idDataGroup);
   SEVERITY investTypeRelatedChanges(const BFDataGroupId &idDataGroup);
   SEVERITY intCalcMthdRelatedChanges(const BFDataGroupId &idDataGroup);
   SEVERITY setCommRedRateSubstitutionSet(const BFDataGroupId &idDataGroup);
   bool isGIAFund (const DString &fundCode);
   bool isDIFFund (const DString &fundCode);
   bool isSEGFund (const DString &fundCode);
   SEVERITY validateFromSegTradeEntryCheck(const DString& accountNum,
                                           const DString& fundCode,
                                           const DString& classCode,
                                           const DString& tradeDate,
                                           const DString& transType,
                                           const DString& transId,
                                           const BFDataGroupId &idDataGroup);

   SEVERITY validateFromToSegTradeEntryCheck(const DString& accountNum,
                                             const DString& fundCode,
                                             const DString& classCode,
                                             const DString& accountTo,
                                             const DString& fundTo,
                                             const DString& classTo,
                                             const DString& tradeDate,
                                             const DString& transType,
                                             const DString& transId,
                                             const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAllSegTransfer(const BFDataGroupId &idDataGroup);
   //P0186486FN09 - Employee and Agent Account Gap#8A
   SEVERITY validateSlsRepIA(const BFDataGroupId &idDataGroup);
   void getFundCategory ( const DString& fundCode, DString& fundCategory);
   SEVERITY updateGuaranteeFeeOverride (const BFDataGroupId &idDataGroup);
   virtual bool isGuaranteeFeeOverrideAllowed (const BFDataGroupId &idDataGroup);
   void ValidateSourceOfAcct(const BFDataGroupId& idDataGroup);  //P0186486_FN15_The Source of Funds
   virtual SEVERITY loadDilution(const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateAnnuitantGender (const BFDataGroupId& idDataGroup);
   SEVERITY validateAnnuitantGender (const BFDataGroupId& idDataGroup, DString& dstrAccount);
   SEVERITY validateNMCRContract( MFAccount *pMFAccount, DString &fundCode, DString &classCode, DString &contractType, DString &contractVer, const BFDataGroupId &idDataGroup);
   bool hasNMCRContract( MFAccount *pMFAccount, DString &fundCode, DString &classCode, DString &dstrContractType, DString &dstrContractVer, const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateUnusualTrading(const BFDataGroupId &idDataGroup);
   SEVERITY getDefaultOrderRouting (bool &bAccountRuleAvailable, const BFDataGroupId &idDataGroup);
   bool isFundTRDTKT ( DString dstrFundCode, DString dstrClassCode,const BFDataGroupId &idDataGroup );
   SEVERITY orderRoutingRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY initPriceTypesList (const BFDataGroupId &idDataGroup);
   bool isRDSPTradeAccount (const BFDataGroupId &idDataGroup, DString& dstrAccountNum);
   virtual SEVERITY validateRDSPTrade (const BFDataGroupId &idDataGroup);
   SEVERITY validateRDSPTrade (const BFDataGroupId &idDataGroup, DString& dstrAccountNum);
   virtual SEVERITY validateSuspendedFund(const BFDataGroupId &idDataGroup);
   virtual SEVERITY refreshIntradayPricing(const BFDataGroupId &idDataGroup);
   bool isIntraDayPricingEnable(const BFDataGroupId& idDataGroup);
   virtual SEVERITY fromIntradayPricing(const BFDataGroupId &idDataGroup,DString dstrPriceCode,DString  dstrPriceCodeList);
   virtual SEVERITY hasWaiveGatingFund(const BFDataGroupId &idDataGroup);
   virtual SEVERITY setWaiveGatingDropdown(const BFDataGroupId &idDataGroup,DString WaiveGateFlag=I_(""));
   SEVERITY checkLiqRedFeeExist(const BFDataGroupId &idDataGroup,bool FromFlag=TRUE);

protected:
//exchange rate
   void setExchRate (const BFDataGroupId &idDataGroup);
   SEVERITY getExchRate ( const DString &fromCurrency, 
                          const DString &toCurrency, 
                          DString &asOfDate,
                          double &exchRate,
                          const BFDataGroupId &idDataGroup,
                          const DString &exactDate = I_("Y"));
   SEVERITY validateExchRate ( const DString &exchRate,
                               const BFDataGroupId &idDataGroup);


   SEVERITY refreshSettleDateByCurrencyChanges(const BFDataGroupId &idDataGroup);
   SEVERITY reCall135ForSettleDateOnly(const BFDataGroupId &idDataGroup);

   virtual bool isResidencyRequired ( DString& strAccountNum, 
                                      const BFDataGroupId &idDataGroup ){return false;};
   virtual SEVERITY getFormerSpouseList (DString& strFormerSpouses, const BFDataGroupId &idDataGroup);
   SEVERITY populateFormerSpouseList( const DString& strAccountNum, 
                                      DString& strFormerSpouses, 
                                      const BFDataGroupId &idDataGroup);
   virtual bool isCheckStartEndDate(){ return false;};
   virtual SEVERITY validateClosedCountryForPendingTrades (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateTradePayTypeFundClass( const BFDataGroupId &idDataGroup );
   virtual SEVERITY validateNegativeAmount ( const DString &amount, 
                                             const BFDataGroupId &idDataGroup);
   SEVERITY getShareholderAddressByAddrCode( const DString &addrCode,
                                             Address *&pAddress, 
                                             const BFDataGroupId &idDataGroup);
   SEVERITY validatePayMethod (const BFDataGroupId &idDataGroup);
   SEVERITY validatePayTypeCheque( const BFDataGroupId &idDataGroup );

   // RESP\QESI - Association to Beneficiary
   SEVERITY buildActiveRESPBenefList(DString &strActiveRESPBenefList, 
                                     DString &strFirstInListEntityId, 
                                     const BFDataGroupId &idDataGroup);
   SEVERITY getRESPBeneficiariesList( DString& strBenefList, 
                                      const DString& strAccountNum, 
                                      const BFDataGroupId &idDataGroup);
   bool isRESPTradeAccount (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmtTypeRedCode (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmountRedCode (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateLinkedEntity(const DString& strValue, const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateRESPTradeResidency(const DString &redcode, 
                                               const BFDataGroupId &idDataGroup);

   // RESP Trade validation view 405   
   SEVERITY getRESPTradeValidation (RESPTradeValidationList *&pRESPTradeValidationList, 
                                    const DString &accountNum,
                                    const DString &transType,
                                    const DString &fundCode,
                                    const DString &classCode,
                                    const DString &depType,
                                    const DString &redCode,
                                    const DString &tradeDate,
                                    const DString &settleDate,
                                    const DString &amountType,
                                    const DString &amount,
                                    const DString &grossOrNet,
                                    const DString &respBenefId,
                                    const DString &fee,
                                    const DString &flatPrcnt,
                                    const DString &ocRdmYear,
                                    const DString &respContrDetlTaxYear,
                                    const DString &assistedContrAmt,
                                    const BFDataGroupId &idDataGroup );
   
   SEVERITY getSegTrxValidation   ( const DString &strAccountNum,
                                    const DString &strFund,
                                    const DString &strClass,
                                    const DString &strAccountTo,
                                    const DString &strFundTo,
                                    const DString &strClassTo,
                                    const DString &strTransType,
                                    const DString &strRedCode,
                                    const DString &strTradeAmount,
                                    const DString &strDeff,
                                    const DString &strSettleDate,
                                    const DString &strPUD,
                                    const DString &strTransNum,
                                    const BFDataGroupId &idDataGroup );

   SEVERITY validateSegTrx(const BFDataGroupId &idDataGroup );
   SEVERITY validateSegExch(const BFDataGroupId &idDataGroup );
   virtual SEVERITY getAccountNumToPopulateRespBeneficiary (DString &accountNum, 
                                                            const BFDataGroupId &idDataGroup);

   SEVERITY updateNotinalDataWarning (const BFDataGroupId &idDataGroup);

   SEVERITY validateAIPEntity (const BFDataGroupId &idDataGroup);

   bool isTradeOnOrAfterPSEEAPEditDate (const BFDataGroupId &idDataGroup);
   SEVERITY setDefaultValueRESPAssistedContrAmt(const DString &dstrRESPContrDetlTaxYear,
                                                const DString &dstrLinkedEntityId,
                                                const BFDataGroupId &idDataGroup);
   SEVERITY updateGIMaturityDate(const BFDataGroupId &idDataGroup);                                                
//common interest protected members
   DString  _currentBusinessDate,
            _nextCycleDate,
            _todayDate,
            _multiCurrency;

   bool  _bInitPending,
         _bPtcForPending,
         _bShouldRefreshSplitCommissions; //boolean will allow split commission to refresh

   DString   batchOrderType;
   DString   defaultPayType;
   bool isNetworkRespReqApplicable();

   virtual SEVERITY validateMoneyMktFund(const BFDataGroupId &idDataGroup);
   SEVERITY editCheckOnMMF ( const DString &transType, bool bFullExchPrntToPrnt, const BFDataGroupId &idDataGroup);
   bool isMoneyMarketFund (const DString &fundCode);

   bool isValueDatePriorToTradeDate(const BFDataGroupId& idDataGroup);		
   void PaymentStatusRelatedChanges(const BFDataGroupId& idDataGroup);		
   SEVERITY loadPendTrdContrSubtList (const BFDataGroupId& idDataGroup);		
   SEVERITY loadPaymentStatusSubstList(const BFDataGroupId& idDataGroup);
   void PendTrdContractRelatedChanges (const BFDataGroupId& idDataGroup);
   SEVERITY enablePFCrystalisationFlag (const BFDataGroupId &idDataGroup);
   bool isFundERISAProhibited ( const DString &fundCode, 
                                const DString &classCode, 
                                const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundForERISAAccount ( const DString &fundCode,
                                                  const DString &classCode, 
                                                  const BFDataGroupId &idDataGroup);
   DString getRDRAdviceFlag(const DString &transType, const DString &account,const DString &fundCode,
								 const DString &classCode,const DString &tradeDate,const BFDataGroupId& idDataGroup);
   SEVERITY setRDRAdviceFlag(const DString &transType, const DString &account,const DString &fundCode,
								 const DString &classCode,const DString &tradeDate,const BFDataGroupId& idDataGroup);
   virtual SEVERITY RDRAdviceRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY buildPaymentRoutingSet(const BFDataGroupId &idDataGroup,DString &outdstrpymtLevelRoutingSet);
   virtual SEVERITY setPaymentRoutingSetDefault( const BFDataGroupId &idDataGroup);
   virtual SEVERITY setGIDIFTradePayType (const BFDataGroupId &idDataGroup);
   bool    bIsEventReceiptDateTimeAppl(const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateRedCodeDepTypeUCTrade( const BFDataGroupId &idDataGroup);
   virtual bool getContractTypeAndVersion (const BFDataGroupId &idDataGroup, const DString &dstrAccountNum, DString &dstrContractType, DString &dstrContractVer);
   virtual SEVERITY getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList,
											 const DString& dstrTransType,
											 const DString& dstrFundCode,
											 const DString& dstrClassCode,
											 const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateParentFundAgainstAmtType(const BFDataGroupId& idDataGroup);
   virtual SEVERITY getStopFlagSeverityFromFundLimitationRule(const DString &fundCode,
                                                              const DString &classCode,
                                                              const DString &limitationRule,
                                                              DString &dstrStopFlagSeverity,
                                                              const BFDataGroupId& idDataGroup);

   virtual bool isExternalInstitutionTrackingEnable(const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY deliveryNetworkRelatedChanges(const BFDataGroupId &idDataGroup); 
   DString getDivChqAddr(const BFDataGroupId &idDataGroup);
   SEVERITY Trade::getPurchasedUnits(DString& units, const BFDataGroupId& idDataGroup);

private:
//defaults
   void firstLineInInit (const BFDataGroupId &idDataGroup);
   SEVERITY initFeeFields (const BFDataGroupId &idDataGroup);
//helper method retrieves defaults for given trans type
protected:
   virtual   SEVERITY getTradeDefaults ( DString &payType, 
                                         DString &amtType, 
                                         DString &clearMethod,
                                         DString &fileProcessor,
                                         const BFDataGroupId &idDataGroup);
private:
   //helper for getAccountHoldings/getAccountToHoldings
   SEVERITY getHoldings ( const DString &accountNum,
                          MFAccountHoldingList *&pMFAccountToHoldings,
                          const BFDataGroupId &idDataGroup,
                          const DString &fundCode = NULL_STRING,
                          const DString &classCode = NULL_STRING);
   //retrieves a transaction number/batch from the back-end
   SEVERITY fetchTransNum ( const BFDataGroupId &idDataGroup,
                            const DString &track = I_("N"),
                            const DString &pageName = NULL_STRING);
//validation helpers
//account num
   SEVERITY validateAccountNum ( const DString &accountNum,
                                 const BFDataGroupId &idDataGroup);
   SEVERITY validateClearingAccount ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
   SEVERITY validateClearingMethod ( const DString &dstrClearingMethod,
                                     MFAccount *pMFAccount,
                                     const BFDataGroupId& idDataGroup,
                                     bool blFrom = true);
//broker, branch, sales rep
   SEVERITY checkIfBrokerEffective (const BFDataGroupId &idDataGroup);
   SEVERITY checkIfBranchEffective (const BFDataGroupId &idDataGroup);
   SEVERITY checkIfAgentEffective  (const BFDataGroupId &idDataGroup);
   SEVERITY validatePayTypeBroker (const BFDataGroupId &idDataGroup);
//wire/order, order number, gross/net
   SEVERITY validateWireOrderNum ( const DString &wireOrdNum,
                                   const BFDataGroupId &idDataGroup);
   SEVERITY wireOrderAllowed (const BFDataGroupId &idDataGroup);
   SEVERITY validateOrderSource ( const DString &orderSource,
                                  const BFDataGroupId &idDataGroup);
   SEVERITY validateGrossOrNet ( const DString &grossOrNet,
                                 const BFDataGroupId &idDataGroup);
   SEVERITY validateOrderSourceOrderType (const BFDataGroupId &idDataGroup);
   SEVERITY brokerRelatedChanges (DString& branchCode, const BFDataGroupId &idDataGroup);
   SEVERITY orderTypeBrokerRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY directOrderSettleDateRelatedChanges (const BFDataGroupId &idDataGroup);
//amount/amt type
   SEVERITY validateMinFromFundAmount (const BFDataGroupId &idDataGroup);
   SEVERITY validateMinToFundAmount (const BFDataGroupId &idDataGroup);
//pay type, file processor, settle currency, address code
   bool isFileProccessorApplicable (const BFDataGroupId &idDataGroup);
   SEVERITY fileProcessorRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY settleCurrencyRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY bankingRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY bankChrgsRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY addressRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY payMethodRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY payMethodPropertyChanges (const BFDataGroupId &idDataGroup);
   SEVERITY removeTradeBankInstructionsList (const BFDataGroupId &idDataGroup);
   SEVERITY clearBankFields (const BFDataGroupId &idDataGroup);
   SEVERITY validateAddressCode ( const DString &addressCode,
                                  const BFDataGroupId &idDataGroup);
//fund validation
   SEVERITY validateFromToFundClass (const BFDataGroupId &idDataGroup);   
protected:
   SEVERITY readStopFlag ( const DString &transType,
                           const DString &fundCode,
                           const DString &classCode,
                           const DString &accountNum,
                           bool &bStopFlag, 
                           bool &bErrorSeverity, 
                           const BFDataGroupId &idDataGroup);
private:
   SEVERITY validateBrokerFund ( const DString &broker,
                                 const DString &transType,
                                 const DString &accountNum,
                                 const DString &fundCode, 
                                 const DString &classCode, 
                                 DString &brokerPermits, 
                                 const BFDataGroupId &idDataGroup);
   SEVERITY validateAgentFund ( const DString &broker,
                                const DString &branch,
                                const DString &agent,
                                const DString &transType,
                                const DString &accountNum,
                                const DString &fundCode, 
                                const DString &classCode, 
                                const BFDataGroupId &idDataGroup);

//deal time, deal date, dates in general
   SEVERITY validateCashDate ( const DString &cashDate, 
                               const BFDataGroupId &idDataGroup);
   SEVERITY validateDealDate ( const DString &dealDate, 
                               const BFDataGroupId &idDataGroup);
   SEVERITY validateDealTime ( const DString &dealTime,
                               const BFDataGroupId &idDataGroup);
   SEVERITY validateSettleInDate ( const DString &settleInDate, 
                                   const BFDataGroupId &idDataGroup);
   SEVERITY validateTradeInDate ( const DString &dstrTradeInDate, 
                                       const BFDataGroupId &idDataGroup);
   SEVERITY validateAcctableTradeDate (const BFDataGroupId &idDataGroup);
   SEVERITY accountableBackdatedRelatedChanges (const BFDataGroupId &idDataGroup);

//helper for getting the ams master info, used in ams mstr validations
   SEVERITY getAMSMstrInfo ( AmsMstrInfo *&pAMSMstrInfo,
                             DString &amsCode,
                             const BFDataGroupId &idDataGroup);
//PET1117.FN66,67,68 SWIFT,Investro,PWLD
   SEVERITY validateParticipantID ( const DString &participantID,
                                    const BFDataGroupId &idDataGroup);
   SEVERITY validateSenderRefNum ( const DString &senderRefNum,
                                   const BFDataGroupId &idDataGroup);
   SEVERITY validateOtherConfirmType ( const DString &otherConfirmType,
                                       const BFDataGroupId &idDataGroup);
//PET 2251/01 - rel 74
   SEVERITY validateNetworkID  ( const DString &networkID,
                                 const BFDataGroupId &idDataGroup);
   SEVERITY validateAPIFundCurrency ( const DString &fundCurrency,
                                      const BFDataGroupId &idDataGroup);
   SEVERITY networkIDRelatedChanges (const BFDataGroupId &idDataGroup);   
   SEVERITY otherConfirmTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY setAccountabilityReasonCodeDefaultValues (const BFDataGroupId &idDataGroup);
   SEVERITY extTransNumRelatedChanges (const BFDataGroupId &idDataGroup);
//Incident # 261420
   int howManyActiveBankInstructions (const BFDataGroupId &idDataGroup);
//PET 1203/01, MFS commission class A
   void exchRateRelatedChanges (const BFDataGroupId &idDataGroup);
//PET 1295 / 01 - SSBG Trade Suppression Indicator
   SEVERITY setDefaultSuppressIndicators(   const BFFieldId &idFieldMCHDefault, 
                                          const BFFieldId &idFieldSecRecDefault,
                                          const BFDataGroupId &idDataGroup ) ;
   void setSuppressIndicatorsPerm (const BFDataGroupId &idDataGroup);
   
   void setSuppressIndicatorsSubstitutionSet (const BFDataGroupId &idDataGroup);

   void setDefaultMCHIndicator ( const BFFieldId &idFieldMCHDefault, 
                                 const BFDataGroupId &idDataGroup );
   void setDefaultSecRecIndicator ( const BFFieldId &idFieldSecRecDefault, 
                                    const BFDataGroupId &idDataGroup );
   void setNetworkIDSendRefNum ( const BFDataGroupId &idDataGroup, 
                                 bool bSetNetworkID = false);
   bool canIgnoreEUSDBackDateTrade ( const DString &dstrFund, 
                                     const DString &dstrClass, 
                                     const BFDataGroupId &idDataGroup);
   SEVERITY setUnitRoundMethodDefaultValue(const BFDataGroupId &idDataGroup);

//STP PET 2217/10/11/13
   SEVERITY setPayInstrOption (const BFDataGroupId &idDataGroup);
   SEVERITY setTradePayInstructField ( const BFFieldId &idFromField,
                                       const BFFieldId &idToField,  
                                       const BFDataGroupId &idDataGroup);
   SEVERITY setConsolidationType ( const DString &consolType, 
                                   const BFDataGroupId &idDataGroup);
   SEVERITY setRecptIssuedForRebook (const BFDataGroupId &idDataGroup);
   bool isAccountClosedCountry (const DString &accountNum,
                                const BFDataGroupId &idDataGroup);
   SEVERITY validateBankVerifyStatus (const BFDataGroupId &idDataGroup);
   SEVERITY initBeneficiaryListForRESP (const DString &taxType, 
                                        const BFDataGroupId &idDataGroup);
   SEVERITY validateRESPTrade (const BFDataGroupId &idDataGroup);
   SEVERITY displayRESPError (const DString &dstrWarnCode,
                             const DString &dstrWarnParam1,
                             const DString &dstrWarnParam2,
                             const BFDataGroupId &idDataGroup);
   SEVERITY initBeneficiarySubList (const BFDataGroupId &idDataGroup);
   SEVERITY initAccountHoldersSubList (const BFDataGroupId &idDataGroup);
   void setRESP10xAssistedContrAmt( const BFDataGroupId &idDataGroup );

   TransFeeContext *_pTransFeeContext;
   DString _strInitialRebookAmt;
   DString _strRDRAdviceFlag;
   bool  _bRebook, 
         _bBackDateCheck,
         //PET 2217/10/13
         _bAlreadySetPayTypeDefaults,
         _bDefaultPayInstructPayTypeIsNotEFTOrSystemCheque,
         _bSameAccount,
		 _bSetAmsParentFundClass;
	bool  _bRefund;

   DString _origTradeFee;

   BatchInfoList *_pBatchInfoList;

   DString _dstrDefaultSettleCurrencySet;
   
   SEVERITY ValidateFundAmtType( const BFDataGroupId &idDataGroup);
   SEVERITY readStopAmtTradeFlag ( const DString &transType,
									  const DString &fundCode,
									  const DString &classCode,
									  const DString &accountNum,
									  bool &bStopAmtTradeFlag, 
									  bool &bErrorSeverity, 
									  const BFDataGroupId &idDataGroup);

   SEVERITY setRespRequiredSubstList (const BFDataGroupId& idDataGroup);
   SEVERITY validateAMSTradeViaParentFundClass ( const BFDataGroupId &idDataGroup );
   virtual bool allowToFndClsBeParentAMS(const BFDataGroupId& idDataGroup);
   void ResetPendTrdContract (const BFDataGroupId& idDataGroup);		
   bool isPendTrdContrApplic (const BFDataGroupId& idDataGroup); 
   bool isAMSTradeViaParentFundClass (const BFDataGroupId &idDataGroup);
   protected:
   virtual SEVERITY getRegAgentBankInstructions ( BankInstructions *&pBankInstructions, 
                                                  const DString &bankAcctUseCode,
                                                  const BFDataGroupId &idDataGroup);
   void loadRDRAdviceSubstList(const BFDataGroupId& idDataGroup);
   SEVERITY addBlankToSubSet(const BFFieldId &idField ,const BFDataGroupId &idDataGroup, bool dstrUseNotApplicableAsDesc = false );  
   
   SEVERITY validateSettleTypeSettleNetworkXEdit(const BFDataGroupId& idDataGroup);
   SEVERITY validateSettleSourceSettleNetworkXEdit(const BFDataGroupId& idDataGroup);

public:
   virtual bool isG1G2ApplicableTrade(const BFDataGroupId &idDataGroup);

protected:
   SEVERITY doRegulatoryValidations(const BFDataGroupId &idDataGroup, const DString& dstrSide , const DString& dstrRegulation = NULL_STRING );
   SEVERITY doSIFRegulationSpecificValidations(const BFDataGroupId &idDataGroup, const DString& dstrSide );
   SEVERITY validatePSEInformation (const BFDataGroupId &idDataGroup, Frame *pFrame);
   SEVERITY validateCashDateMandatory (const BFDataGroupId &idDataGroup);
   bool isXferInDateActive (const BFDataGroupId &idDataGroup);

private:
   bool isTradeLevelOverrideRuleApplicable(const DString dstrTransType, const BFDataGroupId &idDataGroup);
   SEVERITY updateBranchCodeForRebook(const BFDataGroupId &idDataGroup);
   SEVERITY setAccountNumbersFromSystemLevel( bool bFrom, const BFDataGroupId& idDataGroup );
   SEVERITY setTransTypeListFromMiscInfo( const BFDataGroupId &idDataGroup);
   SEVERITY getDefaultBankingInstrFromAccount(BankInstructions *&pBankInstructions,ShareholderBankInstructionsList *&pBankingInstructionList, 
                                              const DString &dstrbankAcctUseCode, const BFDataGroupId &idDataGroup);
   SEVERITY getDefaultBankingInstrFromShareholder(BankInstructions *&pBankInstructions, ShareholderBankInstructionsList *&pBankingInstructionList, 
                                                  const DString &dstrbankAcctUseCode, const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Trade.hpp-arc  $
 * 
 *    Rev 1.410   Jul 26 2012 10:38:06   wp040027
 * P0198518 - RDR Functionality
 * 
 *    Rev 1.409   25 Jul 2012 17:50:14   if991250
 * P0186484 : Estate Allocation
 * 
 *    Rev 1.408   Jul 10 2012 18:25:42   wp040039
 * PETP0201166- SSBG- Fund Broker validation
 * 
 *    Rev 1.407   Apr 24 2012 21:24:18   wp040039
 * PETP0187485 - Trade Entry And Processing
 * 
 *    Rev 1.406   Apr 20 2012 03:09:32   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.405   Apr 17 2012 18:26:42   popescu
 * 2901148 - Gurantee Flag Override -synch-up from 12.3
 * 
 *    Rev 1.404   Apr 11 2012 12:40:12   dchatcha
 * Synch up : IN# 2901157 - Issue on SEG Trade Processing, revise allocation related logics, IN# 2914672 - P0186479 Issues on Guarantee Override field on Trade Entry screen
 * 
 *    Rev 1.403   Apr 10 2012 04:52:10   panatcha
 * P0186486FN09 - Employee and Agent Account Gap#8A
 * 
 *    Rev 1.402   Apr 09 2012 23:06:34   panatcha
 * P0186486FN09 - Employee and Agent Account Gap#8A
 * 
 *    Rev 1.401   Apr 06 2012 19:57:40   wutipong
 * IN2851692 Warning message fund currency
 * 
 *    Rev 1.400   Apr 06 2012 08:28:34   panatcha
 * P0186486FN09 - Employee and Agent Account Gap#8A
 * 
 *    Rev 1.399   Apr 04 2012 18:50:08   dchatcha
 * Synch up from few code change from R12.3
 * 
 *    Rev 1.398   Mar 08 2012 17:47:58   if991250
 * GI Money Out
 * 
 *    Rev 1.397   Mar 05 2012 12:21:24   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.396   Jan 25 2012 14:00:00   jankovii
 * Sync up: IN 2820320 - Rel12.2 PET0186477 - DIF Trade Entry Screen Issues
 * 
 *    Rev 1.395   Jan 24 2012 08:05:18   kitticha
 * Sync up R12.2 - P0186477 FN03 IN2801549 - Forced Rate issues.
 * 
 *    Rev 1.394   Jan 20 2012 15:46:28   wp040027
 * P0188394_Performance Fees - Order Entry
 * 
 *    Rev 1.393   Jan 16 2012 15:39:54   if991250
 * GI Investment Details
 * 
 *    Rev 1.392   Jan 06 2012 13:39:32   if991250
 * IA money out
 * 
 *    Rev 1.391   Dec 14 2011 15:44:22   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.390   Dec 08 2011 21:49:34   wp040032
 * P0183989 - Money Market Non Receipt
 * 
 *    Rev 1.389   Dec 07 2011 16:03:56   dchatcha
 * P0186477/FN03 - GIA - Purchase, rewrite logic on modify pending trade by using view 54 instead call to view 241
 * 
 *    Rev 1.388   Dec 03 2011 01:24:40   dchatcha
 * P0186477/FN03 - GIA - Purchase
 * 
 *    Rev 1.387   Dec 01 2011 19:01:28   dchatcha
 * P0186477/FN03 - GIA - Purchase, calling to view 423
 * 
 *    Rev 1.386   Nov 30 2011 18:01:20   dchatcha
 * P0186477/FN03 - GIA - Purchase, no need proxy fields and fix several issues found during test
 * 
 *    Rev 1.385   Nov 30 2011 00:09:46   dchatcha
 * P0186477/FN03 - GIA - Purchase
 * 
 *    Rev 1.384   Nov 28 2011 23:11:52   popescu
 * INA Commission Work
 * 
 *    Rev 1.383   Nov 27 2011 19:43:26   popescu
 * INA Commission Work
 * 
 *    Rev 1.382   Nov 11 2011 17:18:34   popescu
 * Seg-Non Seg co-mingling
 * 
 *    Rev 1.381   Oct 13 2011 06:49:14   popescu
 * GIA - Trade Entry - prep work
 * 
 *    Rev 1.380   Oct 06 2011 10:47:42   panatcha
 * P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
 * 
 *    Rev 1.379   Aug 03 2011 11:29:30   wp040027
 * P0186774 - Mutual Fund Order Processing
 * 
 *    Rev 1.378   Jul 20 2011 15:30:50   wp040027
 * PET P0186065 - Aggregated Amount Orders via Swift- Implementation of Rule 36 on Fund
 * 
 *    Rev 1.377   Apr 15 2011 14:59:34   jankovii
 * Sync up: IN 2495248 - Split Commission Issues on DSK
 * 
 *    Rev 1.376   Mar 11 2011 10:40:12   kitticha
 * IN2450642 - Modify program to support fund-class hierarchy.
 * 
 *    Rev 1.375   Mar 09 2011 10:38:36   jankovii
 * Sync up: PET181943 FN01 - XMLPhase 2
 * 
 *    Rev 1.374   Feb 18 2011 04:09:00   kitticha
 * PET0165541_FN12_IN2385316 - Default the assisted contribution amount for ED 78(same as PW Q1).
 * 
 *    Rev 1.373   Jan 31 2011 18:39:36   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.372   Oct 07 2010 11:34:46   jankovii
 * PET0175377 FN01 AIP for Joint RESP Account
 * 
 *    Rev 1.371   Sep 24 2010 14:33:58   jankovii
 * PET0175377 FN01 - AIP for Joint RESP Account
 * 
 *    Rev 1.370   Sep 22 2010 04:52:16   kitticha
 * PETP0173756 FN02 Don't Bust the Rules - few changes.
 * 
 *    Rev 1.369   Sep 21 2010 06:51:02   kitticha
 * PETP0173756 FN02 Don't Bust the Rules - few changes.
 * 
 *    Rev 1.368   Sep 17 2010 07:58:58   kitticha
 * PETP0173756 FN02 Don't Bust the Rules.
 * 
 *    Rev 1.367   Aug 20 2010 03:01:36   dchatcha
 * IN# 2209529 - User should not be able to add QESI Basic or QESI Increase for current year.
 * 
 *    Rev 1.366   Jul 21 2010 01:29:38   dchatcha
 * PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review, logic will be more simpler.
 * 
 *    Rev 1.365   Jun 24 2010 07:38:08   dchatcha
 * PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen.
 * 
 *    Rev 1.364   Jun 11 2010 06:52:38   kitticha
 * PETP0165541 FN02 IN#2123752 - PSE Fix. Remove previous rev logic.
 * 
 *    Rev 1.363   Jun 04 2010 03:56:22   kitticha
 * IN#2123752 - Additional logic and validation for PSE.
 * 
 *    Rev 1.362   May 27 2010 06:28:40   kitticha
 * PETP0165541 FN02 QESI Phase2.
 * 
 *    Rev 1.361   May 04 2010 10:16:30   jankovii
 * PET0165541 FN01 QESI RESP Trading.
 * 
 *    Rev 1.360   Apr 30 2010 15:32:08   popescu
 * RES-QESI Trading - PSE/EAP work
 * 
 *    Rev 1.359   Apr 29 2010 23:21:42   popescu
 * RES-QESI Trading - PSE/EAP work
 * 
 *    Rev 1.358   Apr 29 2010 10:52:32   kitticha
 * PET0165541 FN01 QESI RESP Trading.
 * 
 *    Rev 1.357   Apr 22 2010 07:43:38   kitticha
 * PET0165541 FN01 QESI RESP Trading.
 * 
 *    Rev 1.356   Apr 22 2010 03:54:54   dchatcha
 * PET0165541 FN01 QESI RESP Trading.
 * 
 *    Rev 1.355   Apr 21 2010 13:34:16   kitticha
 * PET0165541 FN01 QESI RESP Trading.
 * 
 *    Rev 1.354   Apr 21 2010 01:22:50   popescu
 * RESP-QESI Resp transfer screen
 * 
 *    Rev 1.353   Apr 20 2010 00:54:28   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - PSE/EAP   screen
 * 
 *    Rev 1.352   Apr 15 2010 00:00:32   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.351   Apr 13 2010 13:00:18   kitticha
 * PET0165541_FN01_QESI_Transaction.
 * 
 *    Rev 1.350   Apr 13 2010 11:51:10   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.349   Mar 27 2010 19:49:02   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.348   Mar 08 2010 13:20:26   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
 * 
 *    Rev 1.347   Dec 18 2009 10:41:08   jankovii
 * PET0166095 FN01 Validations on Money Out Transactions
 * 
 *    Rev 1.346   Dec 10 2009 23:19:20   dchatcha
 * PET0166583 FN02 FN03 - Static Verification Phase 2. Core review, move all of logic from Redemption object to Trade object.
 * 
 *    Rev 1.345   Nov 23 2009 16:18:34   jankovii
 * PET0166583 FN01 Static Data Changes_Banking information.
 * 
 *    Rev 1.344   Oct 26 2009 08:55:20   dchatcha
 * IN# 1874666 - Fix compile error.
 * 
 *    Rev 1.343   Oct 16 2009 11:59:30   popescu
 * IN# 1628727 - Configuration Issue with iFAST Desktop, Code review.
 * 
 *    Rev 1.342   Oct 02 2009 09:13:02   dchatcha
 * IN# 1628727 - Configuration Issue with iFAST Desktop, Code review.
 * 
 *    Rev 1.341   Sep 30 2009 06:52:36   dchatcha
 * IN# 1595165 - Rebooking functionality where contr rcpt was issued not working properly.
 * 
 *    Rev 1.340   17 Aug 2009 10:39:06   popescu
 * IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop - revised the code a little bit
 * 
 *    Rev 1.339   Aug 17 2009 08:28:40   dchatcha
 * IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop.
 * 
 *    Rev 1.338   Aug 14 2009 14:10:28   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.337   Aug 13 2009 15:57:58   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.336   Aug 11 2009 13:59:16   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.335   27 Jul 2009 15:15:22   popescu
 * Project Eiger - P0147738 FN36 - Adding a field to figure out when the multiple settle locations should show up
 * 
 *    Rev 1.334   Jul 16 2009 19:23:56   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Code Review.
 * 
 *    Rev 1.333   Jun 26 2009 06:33:58   kitticha
 * IN#1738640 - R94 - Country Schedule - Cannot modify TX even when FundFrom and FundTo are same
 * 
 *    Rev 1.332   15 Jun 2009 08:20:16   popescu
 * PET157837 FN02 - Country Schedule Daily Non Resident Schedule A - revised the code
 * 
 *    Rev 1.331   10 Jun 2009 18:35:24   popescu
 * PET157837 FN02 - Country Schedule Daily Non Resident Schedule A - revised the code
 * 
 *    Rev 1.330   Jun 09 2009 06:10:46   kitticha
 * PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
 * 
 *    Rev 1.329   May 27 2009 15:12:42   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.328   May 19 2009 14:24:36   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.327   Mar 11 2009 17:46:00   wutipong
 * IN1358908 AIG Unit Rounding Issue -- restrict user to enter decimal longer than fund unit precision to amount field, if amount type is Units.
 * 
 *    Rev 1.326   Jan 21 2009 12:02:58   jankovii
 * PET5517_FN94_Foreign Exchange Allocated Capital Gains
 * 
 *    Rev 1.325   06 Oct 2008 13:20:34   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.324   01 Oct 2008 12:07:06   popescu
 * Check in for code  1419539
 * 
 *    Rev 1.323   23 Jul 2008 11:28:02   kovacsro
 * PET0095436_FN01_Rounding (commented out code)
 * 
 *    Rev 1.322   17 Jul 2008 14:22:12   kovacsro
 * 1. fixed linkage error
 * 2. PET5517 FN60C Cancellation of Contribution Receipts - Rebooking
 * 
 *    Rev 1.321   Jul 04 2008 15:58:12   daechach
 * in# 1309030 - Realignment transfer entry issues.
 * 
 *    Rev 1.320   16 Jun 2008 16:39:18   popescu
 * Incident# 1315311 - param the Exact Date input field for view 134 that reads the exchange rates
 * 
 *    Rev 1.319   Jun 09 2008 08:20:40   daechach
 * IN # 1283327 - Trade created with invalid settlement date, Synched up from R85
 * 
 *    Rev 1.318   Apr 28 2008 17:31:34   wongsakw
 * Sync up : IN1235049 -- SSIIL iFAST UAT issue - Unsettled Units Redemption Validation fx issue
 * 
 *    Rev 1.317   15 Apr 2008 12:13:32   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.316   Jan 29 2008 17:37:28   wongsakw
 * Inc#1158727 -- Default PayType Transfer with expired sett details : move sett instr expiry check to trade date field.
 * 
 *    Rev 1.315   Nov 06 2007 10:47:08   jankovii
 * IN 1053528 & 1053527 - SSIIL iFAST UAT issue - Default Pay Type transfer clearing to non-clearing acct.
 * 
 *    Rev 1.314   Oct 30 2007 11:28:38   jankovii
 * IN 1053527 & 1053528 - SSIIL iFAST UAT issue - Default Pay Type transfer clearing to non-clearing acct.
 * 
 *    Rev 1.313   01 Aug 2007 15:59:26   popescu
 * Incident # 956780 - mgfeerebate should always be direct
 * 
 *    Rev 1.312   24 Jul 2007 20:13:46   popescu
 * GAP 20 -22 AIM
 * 
 *    Rev 1.311   23 Jul 2007 16:50:18   popescu
 * PET 2360 - FN 20 - GAP 20 Soft cap functionality
 * 
 *    Rev 1.310   May 04 2007 13:56:22   jankovii
 * PET 2321 FN01 - MT54X Default Pay Type.
 * 
 *    Rev 1.309   Mar 30 2007 14:08:34   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.307   Mar 26 2007 11:07:34   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.306   Mar 21 2007 13:26:08   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.305   Mar 14 2007 14:40:44   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.304   Nov 09 2006 00:08:24   popescu
 * PET 2281/Fn01 - cloning account - TA  synch-up from rel 73
 * 
 *    Rev 1.303   Nov 02 2006 11:21:20   popescu
 * PET 2251/01 - added RBCD to Network Order - and few checks
 * 
 *    Rev 1.302   Oct 30 2006 17:06:36   jankovii
 * PET 2185 FN04 - Trade restrictions.
 * 
 *    Rev 1.301   Oct 19 2006 15:35:04   popescu
 * Incident# 722294 - users will be able to override the trade payment instructions with system cheque
 * 
 *    Rev 1.300   Sep 30 2006 00:54:40   popescu
 * Incident 720294 - pay entity eff. dates
 * 
 *    Rev 1.299   Sep 15 2006 19:43:16   popescu
 * STP 2217/13 - fixes
 * 
 *    Rev 1.298   Sep 13 2006 19:11:28   popescu
 * STP 2192/FN 13
 * 
 *    Rev 1.297   Sep 05 2006 16:54:38   popescu
 * STP Project 2217/17
 * 
 *    Rev 1.296   Aug 29 2006 18:16:14   popescu
 * STP PET 2192 FN10/11 - bulking netting redemption
 * 
 *    Rev 1.295   Jul 07 2006 13:33:04   fengyong
 * Incident #659311 - Sync up - Add flag tell check backdate trade or not
 * 
 *    Rev 1.294   Jun 14 2006 16:19:54   popescu
 * PET 2102.FN02 Flex 
 * 
 *    Rev 1.293   Jun 14 2006 10:51:38   jankovii
 * PET2102 FN02 - Manulife Flex  Trade/Systematic Entry.
 * 
 *    Rev 1.292   May 25 2006 09:38:58   jankovii
 * PET 2102 FN02 - Manulife Flex Trade/Systematic Entry.
 * 
 *    Rev 1.291   Mar 31 2006 13:54:32   jankovii
 * PET 1334 - Alternative Product.
 * 
 *    Rev 1.290   Mar 24 2006 14:58:58   popescu
 * Incident# 564040 - CCB 2273 - Clear out the ExtTransNum for rebooks - view will assign it with M+transnum
 * 
 *    Rev 1.289   Mar 22 2006 16:23:32   jankovii
 * EUSD Backdated trade validation.
 * 
 *    Rev 1.288   Mar 13 2006 13:03:08   porteanm
 * Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
 * 
 *    Rev 1.287   Mar 10 2006 09:20:34   popescu
 * BPS Performance issue - cached view call 20 and passed params fund/class in as params - more work
 * 
 *    Rev 1.286   Mar 07 2006 17:18:34   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default, add set external transaction number
 * 
 *    Rev 1.285   Mar 06 2006 14:28:32   popescu
 * PET1334 - FN01 -- Added logic for ESGSettle enhancement - beautify during code review
 * 
 *    Rev 1.284   Mar 02 2006 10:37:50   AGUILAAM
 * IN 5569000 - sync-up from R68. MCHFileIndicator will default to exclude for 3rd party funds.
 * 
 *    Rev 1.283   Mar 01 2006 14:01:38   ZHANGCEL
 * PET1334 - FN01 -- Move function validateESGSettle to ATWithdraw and ManualDividend cbo.
 * 
 *    Rev 1.282   Feb 28 2006 17:24:42   ZHANGCEL
 * PET1334 - FN01 - Added new function isCashESGSettleElig()
 * 
 *    Rev 1.281   Feb 21 2006 17:06:34   popescu
 * Incident#547118 - DSK locks and sets to zero the amount field if AmtType selected is one of i) All Free Units (F), ii) Free/NonAge (T), iii) Matured & Free (Y), iv) Matured & ID (X) and v) Matured Units (M).......since these "Amt Type" options are referencing to ALL units and therefore is not a requirement to input a value in the "Amount" field. 
 * 
 *    Rev 1.280   Feb 21 2006 10:23:18   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.279   Feb 15 2006 11:01:36   AGUILAAM
 * IN 540739 - Sync-up from R68. If MCHSRActive, N/A is not a valid option
 * 
 *    Rev 1.278   Feb 15 2006 10:14:16   ZHANGCEL
 * PET 1334 - FN01 -- Add new functions for the ESG money movement 
 * 
 *    Rev 1.277   Jan 16 2006 12:17:02   popescu
 * PET 1295/01 - SSBG Trade Suppression Indicator
 * 
 *    Rev 1.276   Jan 12 2006 13:48:08   AGUILAAM
 * PET1295_FN01: Trade Suppress Indicator for MCH and SR Files - Trade Entry/Rebook/Trans History
 * 
 *    Rev 1.275   Nov 30 2005 13:51:26   AGUILAAM
 * PET 1228 FN 02 - EUSD Phase 2
 * 
 *    Rev 1.274   Nov 29 2005 15:24:20   AGUILAAM
 * PET_1228_FN02: EUSD Phase 2
 *  
 *    Rev 1.273   Nov 19 2005 15:52:26   popescu
 * BPS Performance issue - cached view call 20 and passed params fund/class in as params
 *
 *    Rev 1.272   Oct 04 2005 11:11:46   ZHANGCEL
 * PET1244 - FN01 - Pass EventTransType to determine whether the SegCapRules needs to involved
 * 
 *    Rev 1.271   Sep 28 2005 18:22:36   popescu
 * Incident # 406322 - bps performance improvement - cached view call 120 - account num validation,  and fixed 'reset' of trade (moved one line from Trade::firstLineInInit to doInit (idatagroup))
 * 
 *    Rev 1.270   Sep 27 2005 13:50:40   porteanm
 * Incident 395614 - SegFundValidation, super ugly implementation when is too late for a change of design.
 * 
 *    Rev 1.269   Aug 29 2005 10:36:34   popescu
 * Incident 390388 - wire order number should be blanked out for multiple rebooks
 * 
 *    Rev 1.268   Aug 17 2005 11:46:16   popescu
 * PET 1235/01 rebook and cancelation - cleaned the code, 
 * 
 *    Rev 1.267   Aug 12 2005 10:29:08   Yingbaol
 * Incident 377523 fix accoutable and reason code validation issue. 
 * 
 *    Rev 1.266   Aug 11 2005 10:34:14   popescu
 * PET 1235, reebook
 * 
 *    Rev 1.265   Jul 18 2005 12:45:58   popescu
 * Incident 358472 - cached fund broker at the trade level - previously the list was only queried for the first 25 records.
 * 
 *    Rev 1.264   Jul 08 2005 09:33:00   Yingbaol
 * PET1235,FN01:transaction cancellation rebook
 * 
 *    Rev 1.263   Jul 06 2005 16:30:34   porteanm
 * PET1171 EUSD 1B - Added validateEUSDBackDates().
 * 
 *    Rev 1.262   Jul 06 2005 12:34:22   AGUILAAM
 * PET_1235: dilution, part of Rebook/Cancellation; partial check-in
 * 
 *    Rev 1.261   Jun 30 2005 15:40:56   popescu
 * Incident # 346892 - fee should not be reset when modifying a split commission in pending mode. Clearing the ROAAmount should be done only if the field is available for business
 * 
 *    Rev 1.260   Jun 29 2005 11:57:32   popescu
 * Incident# 342270 - guard the refresh of split commissions with a boolean for fund related changes; save several view calls to 158
 * 
 *    Rev 1.259   Jun 22 2005 14:09:18   popescu
 * PET 1117/08 - renamed method activestRelatedChanges to thirdPartyFundRelatedChanges
 * 
 *    Rev 1.258   Jun 17 2005 19:28:36   popescu
 * Incident#273734 - settlement currency automatically assigned if all funds held by account are in the same currency. 
 * User stoped from placing a EFT Full Redemption (no fund, zero amount) if the account has non zero holding on funds with different currency.
 * 
 *    Rev 1.257   Jun 15 2005 15:45:26   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.256   Jun 10 2005 10:36:18   popescu
 * PET 1117/08 - cached the fund fee sponsor model list at the Trade level for better perfomance
 * 
 *    Rev 1.255   Jun 01 2005 17:40:40   popescu
 * PET 1203/05 - after code review minor changes - mainly formatting and changed getROAFields access to protected
 * 
 *    Rev 1.254   May 27 2005 11:31:20   popescu
 * PET 1117/08 - new method added to check if the trade broker is a house broker - uses the cached broker, rather then making a new view call - synch-up from release 62
 * 
 *    Rev 1.253   May 27 2005 11:13:22   yingbaol
 * PEt1203,FN01:Delete split commission when ROA amount is 0.0 for transfer
 * 
 *    Rev 1.252   May 24 2005 15:57:30   yingbaol
 * PET1203,FN01:fix splitcommission
 * 
 *    Rev 1.251   May 18 2005 09:03:38   yingbaol
 * PET1203,FN01 Commission-Class A enhancement
 * 
 *    Rev 1.250   May 11 2005 16:34:04   porteanm
 * PET1203 FN05 - Class B NAV Share Lots.
 *  
 *    Rev 1.249   Apr 11 2005 18:10:40   popescu
 * Incident# 285519, set the backdated reason to 17 and accountable to 04 if network id is partnerworld and trade is backdated, synch-up from release 60.0.1
 * 
 *    Rev 1.248   Apr 10 2005 16:09:42   popescu
 * Incident# 261420, allow multiple active bank accounts; raise warning at transaction level if shareholder has more then one active bank account
 * 
 *    Rev 1.247   Apr 07 2005 12:32:56   Fengyong
 * #275807 - Add ExtTransNum relatechange function
 * 
 *    Rev 1.246   Mar 29 2005 18:08:36   popescu
 * Incident# 273841, missed requirment, set the other confirm type to 1-Create PUEV note if fund and account are PUEV capable for an Investro network id.
 * 
 *    Rev 1.245   Mar 28 2005 10:23:10   popescu
 * Incident #270672 -- moved the set of LSIF Code to 'doApplyRelatedChanges' rather then 'doInitWithDefaultValues' - to avoid the call on 'Cancel(s)'
 * 
 *    Rev 1.244   Mar 24 2005 17:22:52   ZHANGCEL
 * Incident #270672 -- Move getHoldings from Private to Protected
 * 
 *    Rev 1.243   Mar 11 2005 07:55:56   popescu
 * PET 1190/04,    isBackdatedTrade made public. 
 * 
 *    Rev 1.242   Mar 10 2005 12:39:36   porteanm
 * Incident 243157/243387 - SettleSource validation.
 * 
 *    Rev 1.241   Feb 03 2005 12:12:06   popescu
 * PET 1117/66, user server context to override TrxnSettCurrRefresh flag. (flag should be 0, in such a case)
 * 
 *    Rev 1.240   Feb 01 2005 16:38:24   popescu
 * PET 1117/66/67/68, set default settlement currency from fund on fund currency related changes
 * 
 *    Rev 1.238   Jan 31 2005 12:58:34   popescu
 * PET 1117/66,67,68 swift/investro/pwld
 * 
 *    Rev 1.236   Jan 14 2005 11:07:34   popescu
 * PTS 10037724, changed the validation of deal date and compared the value of it with today's date, rather then current bussiness date.
 * 
 *    Rev 1.235   Jan 13 2005 11:47:34   popescu
 * PTS 10037724, exchange rate should not be set during pending trade midification, and deal date validation is triggered for new trades
 * 
 *    Rev 1.234   Jan 10 2005 10:38:48   popescu
 * PTS 10037553, fixed fees properties in pending mode and trade reset of the trans type combo
 * 
 *    Rev 1.233   Jan 06 2005 13:57:42   popescu
 * PTS 10037503, trade object set to be dirty immediate after being created
 * 
 *    Rev 1.232   Jan 04 2005 17:11:14   popescu
 * PTS 10037456, consider deposit 9 and 10 -bearer certificate when setting the default values for aggregate option
 * 
 *    Rev 1.231   Dec 31 2004 13:38:46   popescu
 * PTS 10037395, settlement currency should be set as required if for redemption the account closes or a full redemption is processed. Also, isFullNotCloseAcctRed method name to isFullRedemption
 * 
 *    Rev 1.230   Dec 30 2004 12:41:32   popescu
 * PTS 10037260, moved check whether fund sponsor fee model  exists at Trade CBO level, and called the validation for redemptions/purchases as well, missed req: PET1117.FN6.R3.7. 0
 * 
 *    Rev 1.229   Dec 29 2004 11:23:12   popescu
 * PTS 10037302, do not validate amount precision for amount type units
 * 
 *    Rev 1.228   Dec 14 2004 15:02:42   popescu
 * PET 1117/56, pay method/file proc related changes and fixes
 * 
 *    Rev 1.227   Dec 11 2004 11:47:54   popescu
 * PET 1117/56 more fixes, pending trade mods
 * 
 *    Rev 1.226   Dec 08 2004 17:50:14   popescu
 * PET 1117/56, modify an aggregated order's pending trades list
 * 
 *    Rev 1.225   Dec 07 2004 21:20:40   popescu
 * PET 1117/06, pending trades/fees fixes, add-ons
 * 
 *    Rev 1.224   Dec 07 2004 01:38:02   popescu
 * PET 1117/56 trades processing/modify trade
 * 
 *    Rev 1.223   Dec 01 2004 19:50:28   popescu
 * PET 1117/06, trades/fees processing, incorporate fees in trades transaction builder, and added method to copy fee values onto the trades fee fields for cycle processing
 * 
 *    Rev 1.222   Dec 01 2004 15:45:12   popescu
 * PET 1117/56 fees processing, calculate the discount rate
 * 
 *    Rev 1.221   Dec 01 2004 10:19:06   popescu
 * PET 1117/06, restored some of the missing pieces
 * 
 *    Rev 1.220   Nov 30 2004 20:10:18   popescu
 * PET 1117/06
 * 
 *    Rev 1.219   Nov 30 2004 08:43:28   popescu
 * PET 1117/06, more clearing/settle location related stuff
 * 
 *    Rev 1.218   Nov 29 2004 20:30:50   popescu
 * PET 1117/06/56 fees/trades processing
 * 
 *    Rev 1.217   Nov 27 2004 21:19:14   popescu
 * PET 1117/06, trades processing
 * 
 *    Rev 1.216   Nov 25 2004 11:44:20   popescu
 * PET 1117/06, settle locations
 * 
 *    Rev 1.215   Nov 24 2004 21:36:22   popescu
 * PET 1117/06/56. trade processing, settle location
 * 
 *    Rev 1.214   Nov 22 2004 13:09:36   popescu
 * PET 1117/56. fees processing
 * 
 *    Rev 1.213   Nov 19 2004 14:17:38   popescu
 * PET 1117/56 third party processing
 * 
 *    Rev 1.212   Nov 18 2004 14:00:22   popescu
 * PET 1117/56, validation for fund broker code
 * 
 *    Rev 1.211   Nov 14 2004 14:57:32   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.210   Nov 09 2004 16:50:54   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.209   Nov 08 2004 12:31:18   popescu
 * PET 1117/06 trade processing
 * 
 *    Rev 1.208   Nov 06 2004 00:42:48   popescu
 * PET 1117/06, synch changes
//
//   Rev 1.6   Nov 04 2004 17:41:46   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.5   Nov 02 2004 19:19:38   popescu
//PET 1117/06 Trade processing...
//
//   Rev 1.4   Oct 28 2004 18:23:58   popescu
//PET 1117/06
//
//   Rev 1.3   Oct 27 2004 11:27:04   popescu
//PET 1117/06
//
//   Rev 1.2   Oct 22 2004 19:58:56   popescu
//PET 1117/06, work in progress...
//
//   Rev 1.1   Oct 21 2004 06:29:26   popescu
//PET 1117/06 - Trade processing work in progress..
//
//   Rev 1.0   Oct 01 2004 19:30:02   popescu
//Initial revision.
 * 
 * 
// 
*/
