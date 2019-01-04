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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : Systematic.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : Systematic
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

class SysAllocationList;
class SystematicList;
class MgmtCoOptions;
class SystematicList;
class GroupFundList;
class CurrencyList;
class FundMasterList;
class FundDetailList;
class GroupList;
class MFAccount;
class Shareholder;
class AcqFeeInquiry;
class AutoTransAllocationList;
class AutoAcctTransAllocationList;
class SeqFundValidation;
class SysIndexList;
class AccountEntityXref;
class ErrMsgRulesList;
class SystematicBankInstructionsList;
class FundLmtOverrideList;
class GMWBValidation;
class SEGFundValidationRules;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

static bool s_bDisableStopDate = false;

class IFASTCBO_LINKAGE Systematic : public MFCanBFCbo, private boost::noncopyable
{
public:
   Systematic( BFAbstractCBO &parent );
   virtual ~Systematic();

   SEVERITY init( const BFDataGroupId& idDataGroup, 
                  const BFData& viewData, 
                  const BFData *sysAllocData,  
				  const BFData* pAtAllocData, 
				  const DString& strKey,
				  const DString &strPayType = NULL_STRING,
				  const DString &strAmount = NULL_STRING,
				  const DString &strAmountType = NULL_STRING);
   SEVERITY initAtAcctAlloc( const BFDataGroupId& idDataGroup, const BFData* pAtAllocData, const DString& strKey);
   SEVERITY initNew( const BFDataGroupId& idDataGroup,
	                 const DString &strPayType = NULL_STRING,
					 const DString &strAmount = NULL_STRING,
					 const DString &strAmountType = NULL_STRING);
   void init2( const BFDataGroupId& idDataGroup, SystematicList *pList );

   SEVERITY getSysAllocationList( SysAllocationList *&pSysAllocationList );
   SEVERITY getAtAcctAllocationList( AutoAcctTransAllocationList *&pAtAcctAllocationList );
   SEVERITY getAcqFeeInquiry( AcqFeeInquiry *&pAcqFeeInquiry, const BFDataGroupId& idDataGroup );

   void SetFieldProperties( const BFDataGroupId& idDataGroup, bool bIsNewItem = true );

   SEVERITY requestAcqFeeInquiry(const BFDataGroupId& idDataGroup);
   void calculateDefaultAcqFee(const BFDataGroupId& idDataGroup);
   DString& getFeeDisableFlag() { return(_dstrFeeDisableFlag);}
   DString& getFeeUpdateFlag()  { return(_dstrFeeUpdateFlag);}
   DString& getDefaultAcqFee()  { return(_dstrDefaultAcqFee);}
   void setConfirmedFee(const BFDataGroupId& idDataGroup, const DString& dstrFee) {_dstrFee = dstrFee;}
   void getParameter(DString& strAcct,DString& strFund,DString& strClass,DString& strAmount );
   bool validateEffecFundClass(const DString& dstrFund, const DString& dstrClass, const BFDataGroupId& idDataGroup);
   DString getTransactionTypeValue(const BFDataGroupId& idDataGroup);

   bool isNewObject(){return(_bNewFlag == true);};
   void setObjectAsNew(bool bFlag = false){_bNewFlag = bFlag;};
   void ModelOffer( Systematic * Model, const BFDataGroupId& idDataGroup );
   bool isSWPPortfolioPayoutPlan(const BFDataGroupId& idDataGroup);
   bool isSWPCustomPayoutPlan(const BFDataGroupId& idDataGroup);
   bool allSWPCustomPayoutFndCls(const BFDataGroupId& idDataGroup);
   void setFieldsPropSWPPortfolioPayout(const BFDataGroupId &idDataGroup);

   void getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue) const;
   void getFormattedFee(const BFDataGroupId& idDataGroup, DString &dstrValue) const;
   bool findTransType(const BFDataGroupId& idDataGroup, const DString& transType); // return true if transtype is transType

   double getCurrExchangeRate(const DString& dstrFromCurrency, const DString& dstrToCurrency, const DString& dstrDate);

   void ValidateAmountLimit(double dstrAmount, const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup);
   void ValidateAmountInitPur(double dstrAmount, const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup);
   SEVERITY validateFundCode( const DString& dstrfundCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateClassCode( const DString& dstrfundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateGMWB (const DString &fundCode, const DString &classCode, const BFDataGroupId& idDataGroup);
   SEVERITY getGMWBValidationObject(GMWBValidation*& pGMWBValidation, const DString &fundCode, const DString &classCode, const BFDataGroupId& idDataGroup);

   SEVERITY getSEGFundValidationRules (SEGFundValidationRules  *&pSEGFundValidationRules,
                                       const DString& fundCode, 
                                       const DString& classCode, 
                                       const DString& acctNum,
                                       const DString& effDate,
                                       const BFDataGroupId& idDataGroup);

	SEVERITY getSeqFundValidation(SeqFundValidation *&pSeqFundValidation, 
                                 const BFDataGroupId& idDataGroup,
                                 const DString& fundCode, 
                                 const DString& classCode, 
                                 const DString& acctNum,
                                 const DString& effDate);

   void ValidateSegFund( DString dstrFundCode, 
                         DString dstrClassCode, 
                         DString dstrEffectiveDate,
                         const BFDataGroupId& idDataGroup );

   void getValidListAmountTypeByFund(const DString& fundCode, 
                                     const DString& classCode, 
                                     DString &listAmtType,
                                     const BFDataGroupId& idDataGroup);

   SEVERITY SegCapValidation ( const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

   virtual void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);
/**
    * virtual function. Should be overwritten in order to do special processing in setField before the actual value is 
    * filled in into the CBO
    * @param idField      - the identifier of the field to be set
    * @param strValue      - the value to be set
    * @param idDataGroup  - the identifier of the data group with which the field should be set
    * @param bFormatted    - strValue is formatted or not
   */
   SEVERITY doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField,const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual void getField( const BFFieldId& idField, DString& strFieldValue, 
                          const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
   virtual SEVERITY setField( const BFFieldId& idField, const DString& dstrValue, const BFDataGroupId& idDataGroup, 
                              bool bFormatted = true, bool bSideEffect = false, bool  bCheckCurrentValue = true);

   void setupDefaultAllocationList( const BFDataGroupId& idDataGroup, const DString& dstrAmount = I_("0"), bool bDummyAllocations = false ); 
   void processSplitCommOption( const BFDataGroupId& idDataGroup ); 

   SEVERITY getSystematicIndexList(const BFDataGroupId& idDataGroup, SysIndexList *& pSysIndexList );
   virtual void doReset          ( const BFDataGroupId& idDataGroup );
   void lockFrequency ( const BFDataGroupId& idDataGroup, bool bLock );
   SEVERITY CheckAmountTypeForPACSWPMultiAllocation(const BFDataGroupId& idDataGroup );
   void updateAmountTypeRelatedFields(const BFDataGroupId& idDataGroup);
   DString getFeatureSplitComm();   
  	bool validBrokerFund( const DString& FromToFund, const DString& dstrFund, const DString& dstrClass, const BFDataGroupId& idDataGroup );
   bool validSalesrepFund( const DString& FromToFund, const DString& dstrFund, const DString& dstrClass, const BFDataGroupId& idDataGroup );
   SEVERITY stopFlagCheck( const DString dstrFundCode,
                                   const DString dstrClassCode, 
                                   const DString dstrTransType,
                                   const BFDataGroupId& idDataGroup );

   SEVERITY getErrMsg( DString   dstrErrNum,       long lErrConditionId, 
                       long      lWarnConditionId, const BFDataGroupId& idDataGroup,   DString idiStr = NULL_STRING );
   void getErrMsgValue( DString dstrErrNum, const BFDataGroupId& idDataGroup, DString& dstrErrValue );
   SEVERITY getBankInstructionsList(SystematicBankInstructionsList *&pSystematicBankInstructionsList, 
      const BFDataGroupId& idDataGroup, bool bCreate = true);
	bool isSWPGoodAtDate( const BFDataGroupId& idDataGroup,const DString& dstrDate );
   
   bool isCappedFund ( const DString& dstrFundCode, const BFDataGroupId& idDataGroup );
   SEVERITY ValidateCappedAmt ( const DString& dstrOriAmount, const DString& dstrAmount, const BFDataGroupId& idDataGroup);
   SEVERITY validateFromSoftCapCheck (const BFDataGroupId &idDataGroup);
   SEVERITY validateToSoftCapCheck (const BFDataGroupId &idDataGroup);
   SEVERITY validateFundClassPayout(const BFDataGroupId &idDataGroup);
   bool isFundSoftCapped (const DString &fundCode, 
                          const DString &classCode, 
                          const BFDataGroupId &idDataGroup);

  /**
   * Determines if Withholding Tax is applicable based on 
   * Tax Type of Account and Trans Type (should be registered
   * and SWP)
   * 
   * @param idDataGroup
   * @return 
   */
   bool isWHTaxApplicable( const BFDataGroupId &idDataGroup );
   bool isFieldsDisabledBaseOnRuleType( const DString& ruleType, 
                                        const BFDataGroupId &idDataGroup,
                                        bool &bDisableStopDate = s_bDisableStopDate);
  /**
   * Returns Yes if
   * Pay Type is PAC EFT and at least one bankfileprocdetl record exists
   * for PAC (149.ACHPAC = Yes) OR
   * Pay Type is SWP EFT and at least one bankfileprocdetl record exists
   * for SWP (149.ACHSWP = Yes)
   * 
   * @param idDataGroup
   * @return 
   */
	bool isFileProcessorApplicable( const BFDataGroupId &idDataGroup );

	SEVERITY setFieldValidFlag( const BFFieldId &fieldId, 
		                        const BFDataGroupId &idDataGroup, 
								bool bValid = false );
  //ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues) 
	bool isSystematicListDummy(const BFDataGroupId& idDataGroup); 
	void setAllFieldsValid( const BFDataGroupId &idDataGroup, bool bValid = false );
   bool hasNonAMSFunds(const BFDataGroupId& idDataGroup);

protected:


   SEVERITY getSystematicDefault ( const BFFieldId &genControlFieldId, 
                                   DString &defValue, 
                                   const BFDataGroupId &idDataGroup
                                 );
   SEVERITY doRegulatoryValidations(const BFDataGroupId &idDataGroup, const DString& dstrSide , const DString& dstrRegulation = NULL_STRING );
   SEVERITY doSIFRegulationSpecificValidations(const BFDataGroupId &idDataGroup, const DString& dstrSide );

   private:
   SEVERITY setAmountField( const BFFieldId& idField, const DString& dstrValue,
                            const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect);
   SEVERITY setAllocListAmount(BFCBO* pAllocListBFCBO, double dTotalAmount, const BFDataGroupId& idDataGroup);

   SEVERITY setFundField( const BFFieldId& idField, const DString& dstrValue,
                          const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect);
   void setFundClassCode( const BFFieldId& idField,const BFDataGroupId& idDataGroup);
   void setFundNumber( const BFFieldId& idField,const BFDataGroupId& idDataGroup);
   void setFrequencySubstitution(const BFDataGroupId& idDataGroup);

   bool PayTypeIsEFT( const BFDataGroupId& idDataGroup );
   bool setDisableAcqFee(const BFDataGroupId& idDataGroup);
   bool initDisableAcqFee(const BFDataGroupId& idDataGroup);
   SEVERITY addBlankToSubSet(const BFFieldId &idField ,const BFDataGroupId &idDataGroup, bool dstrUseNotApplicableAsDesc = false );
   void populateFieldsWithDefaultValues (const BFDataGroupId &idDataGroup, const long& lMod);
   void setFieldWithDefaultValue(const BFFieldId &idField,const BFDataGroupId &idDataGroup );

   SEVERITY calculateAmount (const DString &dstrAmountType, const BFDataGroupId& idDataGroup);

   SystematicList *           _pList;
   SysAllocationList *        _pSysAllocationList;
   MgmtCoOptions *            _pMgmtCoOption;  
   GroupFundList *            _pGroupFundList;
   CurrencyList *             _pCurrencyList;
   FundMasterList*            _pFundMasterList;
   FundDetailList*            _pFundDetailList;
   GroupList*                 _pGroupList;
   MFAccount*                 _pMFAccount;
   Shareholder*          _pShareholder;
   AcqFeeInquiry*             _pAcqFeeInquiry;
   AutoTransAllocationList*  _pAtAllocationList;
   AutoAcctTransAllocationList*  _pAtAcctAllocationList;
   AccountEntityXref*      _pAcctEntityXref;
   DString                    _dstrFeeUpdateFlag;
   DString                    _dstrFeeDisableFlag;
   DString                    _dstrDefaultAcqFee;
   bool                _bNewFlag;
   DString                    _dstrmultiCurrency;
   DString             _AcctFeeWaived;
   DString m_strSegClient, m_strCotClient;
   ErrMsgRulesList* _pErrMsgRulesList;
   /**
    *  Remember the last request parameters for AcqFeeInquiry
    */
   DString                    _dstrFee;
	DString							_dstrFlatPercent;
   DString                    _dstrTaxType;
   DString                    _dstrTransType;
   DString                    _dstrEffectiveDate;
   DString                    _dstrAmount;
   DString                    _dstrAmountType;
   DString                    _dstrFundCode;
   DString                    _dstrClassCode;
   DString                    _dstrFundToCode;
   DString                    _dstrClassToCode;
   DString                    _dstrCurrency;
   DString                    _dstrBrokerCode;
   DString             _featureBankLayout;
   DString             _featureSplitComm;
   DString             _dstrSysCurrency;
   DString			   _dstrPayType;
   DString			   _dstrAwdAmount;
   DString			   _dstrAwdAmountType;


   void ValidateEffectiveDate( const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup );
   void ValidateDate( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   void ValidateBankAcctType(const DString& BankAcctType);
   void ValidateBankAcctNum(const DString& BankAcctNum);
   void ValidateTransType(const DString& dstrTransType, const BFDataGroupId& idDataGroup);
   void ValidateBankAccount(const DString& dstrValue, const BFDataGroupId& idDataGroup);

   void ValidateBankInformation(const BFDataGroupId& idDataGroup);

   void ValidateBrokerCode(const DString& BrokerCode, const BFDataGroupId& idDataGroup);
   void ValidateBranchCode(const DString& BranchCode, const BFDataGroupId& idDataGroup);
   void ValidateSalesRepCode(const DString& SalesRepCode, const BFDataGroupId& idDataGroup);

   void ValidatePayType(const DString& PayType, const BFDataGroupId& idDataGroup, const DString& dstrFundCode = NULL_STRING);
   void ValidateFundClass(const BFDataGroupId& idDataGroup);
   void ValidateAmount(const DString& Amount, const BFDataGroupId& idDataGroup);
   void ValidateAmountType(const DString& AmountType, const BFDataGroupId& idDataGroup);
   void ValidateGrossOrNet(const DString& GrossOrNet, const BFDataGroupId& idDataGroup);
   void ValidateSrcOfFund(const DString& SrcOfFund, const BFDataGroupId& idDataGroup);
   void ValidateFee(const DString& Fee, const BFDataGroupId& idDataGroup);
   void ValidateFeePercent(const DString& FeePercent, const BFDataGroupId& idDataGroup);
   SEVERITY validateCurrency (const DString &currency, const BFDataGroupId &idDataGroup);
   void ValidateAdminFeeCurr(const DString& AdminFeeCurr, const BFDataGroupId& idDataGroup);
   void ValidateAdminFee(const DString& dstrAdminFee, const BFDataGroupId& idDataGroup);
   void ValidateFundToClassToAccountTo( const BFDataGroupId& idDataGroup );
   SEVERITY validateATAccountTaxType( const DString& ToAcctNum, const BFDataGroupId& idDataGroup );
   void ValidateFundToCode(DString& strFundTo, const BFDataGroupId& idDataGroup );
   SEVERITY validateAccountTo( const DString& toAcctNum, const BFDataGroupId& idDataGroup );
   bool getFundCurrency(DString& dstrCurrency, const BFDataGroupId& idDataGroup);
   void validateFundClassTransferAllowed(const BFDataGroupId& idDataGroup);
   void validateAmountTypeCrossEdit(const BFDataGroupId& idDataGroup);
   void setATAllocation(const BFDataGroupId& idDataGroup);

   void ValidateAddrCode(const DString& strValue, const BFDataGroupId& idDataGroup);
   bool clearStatusFundToClassToAccountTo(const BFDataGroupId& idDataGroup );

   void ValidateMonthlyIndicator(const DString& strValue, const BFDataGroupId& idDataGroup);
   void ValidateAllocation(const BFDataGroupId& idDataGroup);

   void ValidateInitialAmt(const DString& strInitialAmt, const BFDataGroupId& idDataGroup);
   bool VUBFeeTypeIsPercentage(const BFDataGroupId& idDataGroup) const;
   void getVUBExpectedAmt(DString& strVUBExpectedAmt, const BFDataGroupId& idDataGroup) const;
   void setVUBFee(const DString& strVUBFee, const BFDataGroupId& idDataGroup);
   void getVUBFee(DString& strVUBFee, const BFDataGroupId& idDataGroup) const;
   void getFraction(DString& strFraction, DString& strNumerator, DString& strDenominator) const;
   double getContribution(const BFDataGroupId& idDataGroup) const;
   bool isValidFraction(const DString& strIn) const;
   void setFieldStatus( const BFDataGroupId& idDataGroup, bool isSavingPlan );

   SEVERITY InitFieldsNotInInquiry(const BFDataGroupId& idDataGroup);
   SEVERITY getMFAccount( const DString& AcctNum, const BFDataGroupId& idDataGroup, MFAccount *&pAcctOut );
   SEVERITY getSegCotClient();
   
   bool binit;
   DString _strRDRAdviceFlag;
   void parsingCombinedField(const DString& dstrValueIn, 
                             DString& dstrField1, DString& dstrField2, 
                             const DString& dstrSep) const;
   void setExchInFee(const BFDataGroupId& idDataGroup);
   SEVERITY setExchOutFee(const BFDataGroupId& idDataGroup);

   SEVERITY setDefaultExchInFee( DString dstrFundCode, DString dstrClassCode, const BFDataGroupId& idDataGroup );
   SEVERITY setMonths(const BFDataGroupId& idDataGroup);
   SEVERITY setMonthIndicatorFromMonthFields(const BFDataGroupId& idDataGroup);
   SEVERITY setDefaultMonthlyIndicator(const BFDataGroupId& idDataGroup);
   bool isAnnualy(const DString& strMonthIndicator);
   bool isSemiAnnualy(const DString& strMonthIndicator);
   bool isQuarterly(const DString& strMonthIndicator);
   int getNoOfYes(const DString& strMonthIndicator);
   void setFieldsToReadonlyWhenForBadRecord(const BFDataGroupId& idDataGroup);
   SEVERITY validateBELFee(const DString& dstrBELFee, const BFDataGroupId& idDataGroup);
   SEVERITY validateExchInFee(const BFDataGroupId& idDataGroup);
   SEVERITY validateExchOutFee(const BFDataGroupId& idDataGroup);
   void setAmtTypeSubList( const BFDataGroupId& idDataGroup );
   void  setDefaultAcquisitionFee( const BFDataGroupId& idDataGroup );
   SEVERITY getAccountEntityXref ( AccountEntityXref *&pAccountEntityXref, const BFDataGroupId& idDataGroup );
   void checkNextProcDate( const DString& EffectiveDate, const DString& StopDate, const BFDataGroupId& idDataGroup );
	SEVERITY validateTransType(const BFDataGroupId& idDataGroup);
/*   SEVERITY stopFlagOverride(const DString dstrAcctNum, 
                             const DString dstrTransType, 
                             const DString dstrFundCode,
                             const DString dstrClassCode,
                             bool &bStopFlag, bool &bErrorSeverity, const BFDataGroupId& idDataGroup);*/
   SEVERITY minAmountOverride( const DString& dstrTransType, 
                               const DString& dstrFundCode,
                               const DString& dstrClassCode,
                               DString &dMinAmt, bool &bErrorSeverity, const BFDataGroupId& idDataGroup);

   SEVERITY cappedDateRule ( const BFDataGroupId& idDataGroup );
   SEVERITY cappedFundRule ( const DString& dstrFundCode, const BFDataGroupId& idDataGroup);
   SEVERITY readStopFlag ( const DString &transType,
                           const DString &fundCode,
                           const DString &classCode,
                           const DString &accountNum,
                           bool &bStopFlag, 
                           bool &bErrorSeverity, 
                           const BFDataGroupId& idDataGroup);

   SEVERITY getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList,
                                     const DString& transType,
                                     const DString& fundCode,
                                     const DString& classCode,   
                                     const BFDataGroupId &idDataGroup);
   SEVERITY disableFieldsBaseOnRuleType(const DString& ruleType, const BFDataGroupId &idDataGroup);
   void ValidateSourceOfBankAcct(const BFDataGroupId& idDataGroup);
   void loadRDRAdviceSubstList(const BFDataGroupId& idDataGroup);
   DString getRDRAdviceFlag(const BFDataGroupId& idDataGroup);
   SEVERITY RDRAdviceRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY validateRDRAdviceForAmt (const DString& dstrAmount, const BFDataGroupId &idDataGroup);
   bool		bIsEventReceiptDateTimeAppl(const BFDataGroupId &idDataGroup);
private:


  /**
   * If isFileProcApplicable, then the grid will show the 
   * Payment Method and File Processor fields, otherwise hide them.
   * 
   * @param idDataGroup
   * @return 
   */
	SEVERITY systematicPayTypeRelatedChangesForFileProcessor( const BFDataGroupId &idDataGroup );

  /**
   * When Payment Method changes, the corresponding
   * File Processor/Settle Currency lists need to be reloaded.
   * 
   * @param idDataGroup
   * @return 
   */
	SEVERITY payMethodRelatedChanges( const BFDataGroupId &idDataGroup );

  /**
   * Sets File Processor field list values and properties.
   * 
   * @param idDataGroup
   * @return 
   */
	SEVERITY setFileProcessor( const BFDataGroupId &idDataGroup );

  /**
   * Sets Pay Method field list values and properties.
   * 
   * @param idDataGroup
   * @return 
   */
	SEVERITY setPayMethod( const BFDataGroupId &idDataGroup );

  /**
   * Sets Settle Currency field list values and properties.
   * 
   * @param idDataGroup
   * @return 
   */
	SEVERITY setSettleCurrency( const BFDataGroupId &idDataGroup );
	
  /**
   * If Withholding Tax is applicable, then the 4 WHTax fields
   * should be shown in the grid, otherwise they should be hidden.
   * 
   * @param idDataGroup
   * @return 
   */
  SEVERITY transTypeWHTaxRelatedChanges( const BFDataGroupId &idDataGroup );
	
  /**
   * If Override Tax = Percent, then percentage should be between 0 and 100.
   * If Override Tax = Amount, then amount should be positive.
   * 
   * @param dstrTaxPUDOverride
   * @param dstrTaxRate
   * @param idDataGroup
   * @return 
   */
  SEVERITY validateTaxPUDOverride( const DString &dstrTaxPUDOverride, 
		                              const DString &dstrTaxRate, 
												const BFDataGroupId &idDataGroup );
	  
  /**
   * If Tax Override = Amount, then Amount should not exceed
   * Trade Amount (when Trade Amount Type is Amount).
   * 
   * @param dstrTaxPUDOverride
   * @param dstrTaxRate
   * @param idDataGroup
   * @return 
   */
  SEVERITY validateTaxAmountPUDOverride( const DString &dstrTaxPUDOverride, 
										 const DString &dstrTaxRate, 
										 const BFDataGroupId &idDataGroup );

  SEVERITY validateResidency( const DString &dstrAccountNumber, const BFDataGroupId &idDataGroup );
  SEVERITY validateMoneyInDates( const DString &dstrAccountNumber, const DString &dstrEffectiveDate,
	                             const BFDataGroupId &idDataGroup );

  SEVERITY validateAccountClosedCountry ( const DString &strTransType,
                                          const BFDataGroupId &idDataGroup );
  SEVERITY validateFromToFundClassAcctTo (const BFDataGroupId &idDataGroup);
  SEVERITY payTypeRelatedChanges( const BFDataGroupId &idDataGroup);//P0186486_FN15_The Source of Funds
  DString _dstrHostCurrencyList;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Systematic.hpp-arc  $
 * 
 *    Rev 1.100   Jul 26 2012 10:44:20   wp040027
 * P0198518 - RDR Functionality
 * 
 *    Rev 1.99   Jun 27 2012 12:31:44   if991250
 * IN2981340 : RRIF
 * 
 *    Rev 1.98   May 28 2012 10:39:04   if991250
 * CPF - Account Entity + Systematics
 * 
 *    Rev 1.97   May 11 2012 14:05:08   jankovii
 * P0186481 FN07 - GWA LWA Payment Options for SWP RRIF
 * 
 *    Rev 1.96   Apr 30 2012 15:41:58   popescu
 * 2902002 - P0186480FN02 - Diploma DSK Validation
 * 
 *    Rev 1.95   Apr 20 2012 03:59:52   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.94   Jan 11 2012 15:22:00   dchatcha
 * IN# 2796443 - Validation rule for Allocated Auto Transfer.
 * 
 *    Rev 1.93   Feb 27 2011 21:12:06   panatcha
 * ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues)
 * 
 *    Rev 1.92   Nov 24 2010 12:02:24   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.91   Jun 09 2009 06:06:18   kitticha
 * PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
 * 
 *    Rev 1.90   08 Oct 2008 14:54:42   kovacsro
 * PET142007  FN01 TFSA - added date validation for money in transaction
 * 
 *    Rev 1.89   07 Oct 2008 11:08:52   kovacsro
 * PET142007  FN01 TFSA - sending AccountTo for AT rather than FromAccountNum
 * 
 *    Rev 1.88   24 Jul 2007 20:13:32   popescu
 * GAP 20 -22 AIM
 * 
 *    Rev 1.87   Oct 04 2005 13:50:30   AGUILAAM
 * IN 418142 (R65) - If fee is defined by user as "flat" and default feetype is "percent", fee will be converted to amount or dollar value; display corresponding message right away
 * 
 *    Rev 1.86   Sep 28 2005 16:24:02   ZHANGCEL
 * PET1244 - FN01 - Seg Fund Evolution enhancement
 * 
 *    Rev 1.85   Mar 17 2005 14:37:04   porteanm
 * Incident 262660 - PAC Eff Date validation for single fund and alloc.
 * 
 *    Rev 1.84   Jan 04 2005 11:24:36   yingbaol
 * PTS10036915: implement display hide stingray control at dialog layor.
 * 
 *    Rev 1.83   Dec 16 2004 12:51:28   popescu
 * PTS 10036278, read the defaults for systematic pay type from generic controls
 * 
 *    Rev 1.82   Nov 14 2004 14:56:42   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.81   Oct 27 2004 10:32:44   VADEANUM
 * PET 1010 FN02 CCB 1383 - WHTax for Registered Accts on SWPs.
 * 
 *    Rev 1.80   Sep 13 2004 12:43:40   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.79   Sep 07 2004 15:06:08   VADEANUM
 * PET 1094 FN4 - Activest Bank File Processor.
 * 
 *    Rev 1.78   Jun 25 2004 16:38:40   popescu
 * PST 10031525, fund limitation override issues
 * 
 *    Rev 1.77   May 13 2004 10:45:54   AGUILAAM
 * PTS 10029479 - purchase/PAC on US funds not allowed for RRSP accounts, applies to both single-fund and allocated transactions
 * 
 *    Rev 1.76   Apr 23 2004 18:16:26   WINNIE
 * Ticket 10021181 : new cappedfundrule method for capped fund logic 
 * 
 *    Rev 1.75   Oct 03 2003 19:19:30   popescu
 * CIBC PET 809, FN13, removed references to BankSearch and BankList objects
 * 
 *    Rev 1.74   Sep 04 2003 17:28:54   HSUCHIN
 * PTS 10021181 - sync up from 1.70.1.0
 * 
 *    Rev 1.73   Aug 25 2003 15:42:52   HSUCHIN
 * fixed bug with systematic updating for AMS accounts when nothing has changed.
 * 
 *    Rev 1.72   Aug 15 2003 15:32:00   HSUCHIN
 * added AMS Restriction enhancement.   
 * 
 *    Rev 1.71   Aug 11 2003 11:56:10   YINGBAOL
 * add method isSWPGoodAtDate;
 * 
 *    Rev 1.70   Jun 01 2003 17:08:04   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.69   May 27 2003 10:34:36   popescu
 * sync-up with 1.222.1 and removed the checkBank method who 's not being called by anyone
 * 
 *    Rev 1.68   Apr 12 2003 13:45:22   FENGYONG
 * Add fundction get error num value
 * 
 *    Rev 1.67   Apr 10 2003 09:33:36   FENGYONG
 * tempery checkin for initial purchase amount validation
 * 
 *    Rev 1.66   Mar 25 2003 13:16:22   popescu
 * Synch-up back to trunc
 * 
 *    Rev 1.65   Mar 21 2003 18:25:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.64   Feb 06 2003 18:22:52   HSUCHIN
 * added capped fund validation support for amount and stop date.  3 new methods initCapped, ValidateCappedAmt and isCappedFund.
 * 
 *    Rev 1.63   Jan 30 2003 19:05:14   WINNIE
 * Call by reference for input parameters of getStopFlag, override and minimum amount 
 * 
 *    Rev 1.62   Jan 21 2003 18:34:34   WINNIE
 * Systematic minimum edit check on amount : allow warning or error message based on the set up at fund limitation override
 * 
 *    Rev 1.61   Jan 12 2003 16:00:46   WINNIE
 * New logic for stop flag checking at funddetail level, it now allow user to issue error or warning based on the set up in the database; It allow allow override based on the tax type, account type, acct designation, tax juris and prov of resident value of the MFaccount and Shareholder; New logic for fund/class validation against salesrep
 * 
 *    Rev 1.60   Jan 05 2003 11:53:40   HSUCHIN
 * sync up with rel 49.1 (1.58)
 * 
 *    Rev 1.59   Dec 06 2002 09:32:24   YINGBAOL
 * PRIF Enhancement
 * 
 *    Rev 1.58   Oct 09 2002 23:55:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.57   Aug 29 2002 12:53:46   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.56   Jul 25 2002 14:21:20   ZHANGCEL
 * PTS 10008129: Added logic for NextProcessDate checking
 * 
 *    Rev 1.55   Jul 17 2002 17:41:56   ZHANGCEL
 * PTS 10008737: Added logic for the broker allow fund checking
 * 
 *    Rev 1.54   Jun 05 2002 09:40:34   HSUCHIN
 * sync up with 1.49.1.0
 * 
 *    Rev 1.53   Jun 03 2002 16:55:14   HSUCHIN
 * bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
 * 
 *    Rev 1.52   24 May 2002 15:04:04   KOVACSRO
 * doPresetField changes.
 * 
 *    Rev 1.51   22 May 2002 22:22:26   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.50   22 May 2002 18:19:50   PURDYECH
 * BFData Implementation
 */
