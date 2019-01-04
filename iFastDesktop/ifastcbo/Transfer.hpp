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
// ^FILE   : Transfer.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2004
//
// ^CLASS    : Transfer
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\trade.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class AmsMstrInfo;

class IFASTCBO_LINKAGE Transfer : public Trade
{
public:
   Transfer (BFAbstractCBO &parent);
   virtual ~Transfer();
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup);
   virtual bool isSettleLocAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isROAApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isEUSDApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isAccountCloningAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isPSEEAPAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isGIInvestmentListApplicable(const BFDataGroupId &idDataGroup);
   virtual bool isMaturityInstrAllowed (const BFDataGroupId &idDataGroup);
   
protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFData &data);
   virtual SEVERITY transTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual void getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                          BFFieldId &classCodeFieldId);
   virtual void getAccountFieldId (BFFieldId &accountFieldId);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup );
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup); 
//validation methods
   virtual SEVERITY validateOrderType ( const DString &orderType, 
                                        const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateSegBackdates (const BFDataGroupId& idDataGroup);

//account validation
   virtual SEVERITY canAccountTrade ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountToTrade ( MFAccount *pMFAccountTo, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAccountTo ( MFAccount *pMFAccount, 
                                        const BFDataGroupId &idDataGroup);

//fund validation
   virtual SEVERITY validateFundCode ( const DString &fundCode, 
                                       const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundClass (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundClass ( const DString &fundCode, 
                                        const DString &classCode, 
                                        const DString &accountNum, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToFundCode ( const DString &fundCode, 
                                         const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToFundClass ( const DString &fundCode, 
                                          const DString &classCode, 
                                          const DString &accountNum, 
                                          const BFDataGroupId &idDataGroup); 
   SEVERITY validateToSoftCapCheck (const BFDataGroupId &idDataGroup);
   SEVERITY moreValidateToFundClass ( const DString &fundCode,
                                      const DString &classCode,
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFromToFundClass ( const DString &fromFund,
                                              const DString &fromClass,
                                              const DString &toFund,
                                              const DString &toClass,
                                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY fromFundClassRelatedChanges ( const DString &fundCode, 
                                                  const DString &classCode, 
                                                  const BFDataGroupId &idDataGroup);
   virtual SEVERITY toFundClassRelatedChanges ( const DString &fundCode, 
                                                const DString &classCode, 
                                                const BFDataGroupId &idDataGroup);
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

   virtual SEVERITY validateAmtType ( const DString &amtType,
                                      const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateGrossTransfer (const DString &redCode, const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateAmountAmtType (const BFDataGroupId& idDataGroup);
   virtual bool isBrokerAllowed ( const DString &transType,
                                  const DString &accountNum,
                                  const DString &fundCode, 
                                  const DString &classCode,
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

   virtual bool isEscrowTaxTypeRIFTransferApplicable (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateRedCodeExclCodes ( const DString &redCode,
                                               const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateRedCode ( const DString &redCode, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundCodeRedCodeAmount (const BFDataGroupId &idDataGroup);
   SEVERITY validateAccountToRedCode (const BFDataGroupId& idDataGroup);
   SEVERITY validateIfAllocatedAtCostTIKAllowed (const BFDataGroupId &idDataGroup);
   virtual SEVERITY getAtCostTIKStatus ( const BFDataGroupId& idDataGroup, 
                                         const DString& dstrFundCodeIn, 
                                         const DString& dstrClassCodeIn,
                                         bool  blInAllocation,
                                         bool &blIsAtCostTIK);

   SEVERITY validate27RedCodeTIK ( const DString &redCode, 
                                   const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateTIKRedCodes ( const DString &redCode,
                                          const BFDataGroupId& idDataGroup);

   virtual SEVERITY validateFundBalance ( const DString &accountNum,
                                          const DString &fundCode,
                                          const DString &classCode,
                                          const DString &amount,
                                          const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateCurrency ( const DString &currency,
                                       const BFDataGroupId &idDataGroup);

   SEVERITY validateProtectedFundAllowedTransfers (const BFDataGroupId &idDataGroup);
   SEVERITY validateEscrowTaxTypeRIFTransfer (const BFDataGroupId &idDataGroup);
   SEVERITY validateTransferToLIRA (const BFDataGroupId &idDataGroup);
   SEVERITY validateTransferToLRSP (const BFDataGroupId &idDataGroup);
   int getEscrowFundClassState (const BFDataGroupId &idDataGroup);

//deposit type
   virtual SEVERITY validateDepositType ( const DString &depositType,
                                          const BFDataGroupId &idDataGroup);
//settle type
   virtual SEVERITY validateSettleType ( const DString &settleType,
                                         const BFDataGroupId &idDataGroup);
   virtual bool isSplitCommissionAllowed (const BFDataGroupId &idDataGroup);
//PET 1203/05 MFS commission class A
   virtual void roaAmountRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual void getROARelatedFields ( DString &amt, 
                                      DString &amtType, 
                                      DString &currency,
                                      DString &exchRate, 
                                      const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateSettleSource ( const DString &settleSource,
                                           const BFDataGroupId &idDataGroup);

   virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);


   virtual bool isWireSupported (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setDefaultOrderType (const BFDataGroupId &idDataGroup);
   bool isResidencyRequired( DString& strAccountNum, const BFDataGroupId &idDataGroup );
   SEVERITY getFormerSpouseList( DString& strFormerSpouses, const BFDataGroupId &idDataGroup );
   bool isCheckStartEndDate(){ return true;};
   bool isEstateTransfer (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateClosedCountryForPendingTrades (const BFDataGroupId &idDataGroup);
   SEVERITY validateFundToWithSegValidation(const BFDataGroupId &idDataGroup) ;
   virtual SEVERITY validateMasterActAMS(const BFDataGroupId &idDataGroup);
   virtual bool areRESPBenefAllocationsAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isRESPTransferAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isAIPAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isEAPAllowed (const BFDataGroupId &idDataGroup);//P0185010.FN02.R02.01 - Delivering EAP written notice and tax info return
   virtual bool isGuaranteeFeeOverrideAllowed(const BFDataGroupId &idDataGroup);   

   virtual SEVERITY getAccountNumToPopulateRespBeneficiary (DString &accountNum, 
                                                            const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateRESPtoRESPTransfer(const DString& strDepType,
                                                const DString& strRedCode, 
                                                const DString& strTaxTypeFrom, 
                                                const DString& strTaxTypeTo, 
                                                const BFDataGroupId& idDataGroup);

   virtual bool areTaxRatesAllowed(const BFDataGroupId& idDataGroup);
   virtual SEVERITY withholdingTaxRelatedChanges(const BFDataGroupId &idDataGroup);

   SEVERITY validateMoneyMktFund (const BFDataGroupId &idDataGroup);

   virtual SEVERITY validatePerfFeeFromToClassesWithFund ( const BFDataGroupId &idDataGroup);
   virtual SEVERITY validatePerfFeeFXRate ( const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundForERISAAccount ( const DString &fundCode, 
                                                  const DString &classCode, 
                                                  const BFDataGroupId &idDataGroup);
   virtual SEVERITY PFCrystalisationRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY validateGuaranteesOverride(const DString& strValue,const BFDataGroupId &idDataGroup);
   SEVERITY validateAcctFromToXEdit(const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAllSegTransfer(const BFDataGroupId &idDataGroup);
   virtual SEVERITY RDRAdviceRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateRedCodeDepTypeUCTrade(const BFDataGroupId &idDataGroup);
   virtual bool allowToFndClsBeParentAMS(const BFDataGroupId& idDataGroup);
   bool bskipAllowableTransferValidation(const BFDataGroupId &idDataGroup);
   SEVERITY validateAnnuitantGender (const BFDataGroupId &idDataGroup);
   bool getContractTypeAndVersion ( const BFDataGroupId &idDataGroup,
									const DString &dstrAccountNum,	
									DString &contractType, 
									DString &contractVer);

   void setSettleCurrencyToFund(const DString &toFund, const DString &toClass, const BFDataGroupId &idDataGroup);

	virtual bool setCashDateUpdatable(DString &tradeDate, const BFDataGroupId &idDataGroup );

	SEVERITY validateCashDateToFundMandatory (const BFDataGroupId &idDataGroup);

	virtual SEVERITY validateUnusualTrading(const BFDataGroupId &idDataGroup);
	virtual SEVERITY initPriceTypesList (const BFDataGroupId &idDataGroup);
	virtual SEVERITY validateSuspendedFund(const BFDataGroupId &idDataGroup);
	virtual SEVERITY validateRDSPTrade (const BFDataGroupId &idDataGroup);
	virtual SEVERITY refreshIntradayPricing(const BFDataGroupId &idDataGroup);
	virtual SEVERITY toIntradayPricing(const BFDataGroupId &idDataGroup,DString dstrPriceCode,DString  dstrPriceCodeList);
	virtual SEVERITY hasWaiveGatingFund(const BFDataGroupId &idDataGroup);
	virtual bool isRDSPTransferAllowed (const BFDataGroupId &idDataGroup);
	
private:
   SEVERITY validateGICFund ( const DString &fundCode, 
                              const BFDataGroupId &idDataGroup);
   SEVERITY isTransferInKind ( const DString &dstrFromFund, 
                               const DString &dstrFromClass, 
                               const DString &dstrToFund, 
                               const DString &dstrToClass, 
                               const BFDataGroupId& idDataGroup,
                               bool &blValidTransfer);

   SEVERITY validateFromToFundForRealignClearingMethod (const BFDataGroupId &idDataGroup);
   SEVERITY validateFromToClassForRealignClearingMethod (const BFDataGroupId &idDataGroup);

   bool isValidBeneficiary ( const DString &dstrAcctNumFr, 
                             const DString &dstrAcctNumTo, 
                             const BFDataGroupId &idDataGroup);

   bool isValidTransBeneficiary ( const DString &dstrAcctNumFr, 
                                  const DString &dstrAcctNumTo, 
                                  const DString &SpouseOrChild, 
                                  const BFDataGroupId &idDataGroup);

   SEVERITY amsAccountRelatedChanges (const BFDataGroupId &idDataGroup);

   bool isRealignmentTransfer(const BFDataGroupId& idDataGroup);
   bool isParticipantTransfer(const BFDataGroupId& idDataGroup);
   bool isAClearingSameFundTransfer ( bool bCheckBothAccounts, 
                                      const BFDataGroupId &idDataGroup);

   bool areFromToSideClearingAcct(const BFDataGroupId& idDataGroup);
   SEVERITY validateClearingForRealignmntTr( const BFDataGroupId &idDataGroup );
   SEVERITY validateRedCodeDepTypeRESPTrade( const BFDataGroupId &idDataGroup );
   SEVERITY validateGuaranteesOverrideAcctFromTo(const BFDataGroupId &idDataGroup);

   bool bValidateAll, 
	   _blTaxable; 

   SEVERITY validateNMCRContractTypeAndVersion ( const BFDataGroupId &idDataGroup );
   SEVERITY validateAgeAndGender ( const BFDataGroupId &idDataGroup );
   SEVERITY validateAnnuitantAgeForToAcct(const BFDataGroupId &idDataGroup);
   SEVERITY validateAnnuitantSINsForFromToAcct(const BFDataGroupId &idDataGroup);
   SEVERITY validateTwitchAgaintAMS(const BFDataGroupId &idDataGroup);
   SEVERITY tradeInDateRelatedChanges (const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Transfer.hpp-arc  $
//
//   Rev 1.129   Jul 26 2012 10:45:34   wp040027
//P0198518 - RDR Functionality
//
//   Rev 1.128   Jun 05 2012 11:40:34   dchatcha
//IN#2969458- Bypass  the editing for age difference if the new "Guarantees Override" flag set as "Yes"
//
//   Rev 1.127   Apr 16 2012 23:21:04   popescu
//2901148 - Gurantee Flag Override
//
//   Rev 1.126   Apr 03 2012 09:59:02   dchatcha
//IN#2901157 - Issue on SEG Trade Processing
//
//   Rev 1.125   Mar 16 2012 13:46:06   dchatcha
//P0186484 FN05 - SEG Trade Processing, new validations.
//
//   Rev 1.124   Mar 15 2012 18:01:32   if991250
//IN 2879297: Money Out
//
//   Rev 1.123   Mar 13 2012 17:40:16   if991250
//IN 2879297: Money Out
//
//   Rev 1.122   Mar 05 2012 12:17:02   dchatcha
//P0186484 FN05 - SEG Trade Processing.
//
//   Rev 1.121   Jan 20 2012 15:49:26   wp040027
//P0188394_Performance Fees - Order Entry
//
//   Rev 1.120   Dec 08 2011 21:53:52   wp040032
//P0183989 - Money Market Non Receipt
//
//   Rev 1.119   Oct 21 2011 10:11:36   kitticha
//PETP0188150 FN01 - Irish Withholding Tax Functionality.
//
//   Rev 1.118   Oct 06 2011 10:44:30   panatcha
//P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
//
//   Rev 1.117   Jul 22 2011 18:29:28   dchatcha
//P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting. code review.
//
//   Rev 1.116   Jul 20 2011 21:19:40   dchatcha
//P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
//
//   Rev 1.115   Sep 24 2010 14:31:54   jankovii
//PET0175377 FN01 - AIP for Joint RESP Account
//
//   Rev 1.114   Aug 02 2010 07:53:54   dchatcha
//IN# 2196483 - QESI phase 1 - PET165541 - cannot process exchanges.
//
//   Rev 1.113   Apr 29 2010 10:50:00   kitticha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.112   Apr 22 2010 10:29:58   kitticha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.111   Apr 21 2010 14:07:58   kitticha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.110   Apr 20 2010 00:55:00   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading - PSE/EAP   screen
//
//   Rev 1.109   Apr 14 2010 09:45:44   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.108   Mar 08 2010 13:21:36   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
//
//   Rev 1.107   Oct 26 2009 18:12:24   wutipong
//#1412263 - code refactor as per Zijian's suggestion
//
//   Rev 1.106   Jun 26 2009 06:26:58   kitticha
//IN#1738640 - R94 - Country Schedule - Cannot modify TX even when FundFrom and FundTo are same
//
//   Rev 1.105   10 Jun 2009 18:35:34   popescu
//PET157837 FN02 - Country Schedule Daily Non Resident Schedule A - revised the code
//
//   Rev 1.104   Jun 09 2009 06:23:32   kitticha
//PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
//
//   Rev 1.103   Apr 17 2009 10:43:28   jankovii
//PET 157825 FN04 Manual RRIF Redemption
//
//   Rev 1.102   Dec 02 2008 14:58:00   jankovii
//PET 142196 FN01 Federal Restricted LIF and LIRA.
//
//   Rev 1.101   24 Oct 2008 11:58:44   popescu
//Incident 1309030 - re-coded the realignment transfer logic 
//
//   Rev 1.100   06 Oct 2008 13:20:50   kovacsro
//PET142007  FN01 TFSA
//
//   Rev 1.99   01 Oct 2008 12:14:34   popescu
//Check in for incident 1419539
//
//   Rev 1.98   Jul 28 2008 18:25:22   daechach
//in# 1309030 - Realignment transfer entry issues. Code review.
//
//   Rev 1.97   Jul 04 2008 15:53:24   daechach
//in# 1309030 - Realignment transfer entry issues.
//
//   Rev 1.96   May 09 2008 11:49:38   wongsakw
//PET5815 FN02 Realignment Transfer
//
//   Rev 1.95   10 Oct 2007 14:37:54   popescu
//IN  1005517,1020252 - LRSP logic
//
//   Rev 1.94   01 Aug 2007 15:59:32   popescu
//Incident # 956780 - mgfeerebate should always be direct
//
//   Rev 1.93   24 Jul 2007 20:14:04   popescu
//GAP 20 -22 AIM
//
//   Rev 1.92   May 09 2007 16:20:24   jankovii
//MT54X PET2321 FN03 -Participant Transfer.
//
//   Rev 1.91   Mar 30 2007 14:09:42   jankovii
//PET 2292 FN01 - Switch Settlement.
//
//   Rev 1.89   Mar 26 2007 11:06:20   jankovii
//PET 2292 FN01 - Switch Settlement.
//
//   Rev 1.88   Mar 14 2007 14:38:24   jankovii
//PET 2292 FN01 - Switch Settlement.
//
//   Rev 1.87   Nov 09 2006 00:08:30   popescu
//PET 2281/Fn01 - cloning account - TA  synch-up from rel 73
//
//   Rev 1.86   Oct 30 2006 17:08:30   jankovii
//PET 2185 FN04 - Trade restrictions.
//
//   Rev 1.85   Sep 05 2006 19:05:48   popescu
//Incident# 693254 - settlement source field opened for TR/XR
//
//   Rev 1.84   May 25 2006 09:35:52   jankovii
//PET 2102 FN02 - Manulife Flex Trade/Systematic Entry.
//
//   Rev 1.83   Nov 29 2005 15:24:24   AGUILAAM
//PET_1228_FN02: EUSD Phase 2
//
//   Rev 1.82   Sep 27 2005 13:54:54   porteanm
//Incident 395614 - SegFundValidation, super ugly implementation when is too late for a change of design.
//
//   Rev 1.81   Jun 30 2005 15:41:54   popescu
//Incident # 346892 - fee should not be reset when modifying a split commission in pending mode. Clearing the ROAAmount should be done only if the field is available for business
//
//   Rev 1.80   Jun 01 2005 17:40:48   popescu
//PET 1203/05 - after code review minor changes - mainly formatting and changed getROAFields access to protected
//
//   Rev 1.79   May 27 2005 11:13:44   yingbaol
//PEt1203,FN01:Delete split commission when ROA amount is 0.0 for transfer
//
//   Rev 1.78   May 18 2005 09:03:46   yingbaol
//PET1203,FN01 Commission-Class A enhancement
//
//   Rev 1.77   Dec 29 2004 11:22:40   popescu
//PTS 10037302, do not validate amount precision for amount type units
//
//   Rev 1.76   Dec 07 2004 01:38:06   popescu
//PET 1117/56 trades processing/modify trade
//
//   Rev 1.75   Nov 30 2004 20:10:38   popescu
//PET 1117/06
//
//   Rev 1.74   Nov 29 2004 20:31:02   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.73   Nov 26 2004 17:52:24   popescu
//PTS 10033507, synch-up rel 58/58.1 branch 1.190.2.0
//
//   Rev 1.72   Nov 25 2004 14:59:24   popescu
//PET 1117/06, settle locations
//
//   Rev 1.71   Nov 24 2004 21:36:42   popescu
//PET 1117/06/56. trade processing, settle location
//
//   Rev 1.70   Nov 14 2004 14:58:46   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.69   Nov 06 2004 00:43:24   popescu
//PET 1117/06, synch changes
//
//   Rev 1.6   Nov 04 2004 17:41:52   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.5   Nov 02 2004 19:19:42   popescu
//PET 1117/06 Trade processing...
//
//   Rev 1.4   Oct 28 2004 18:24:00   popescu
//PET 1117/06
//
//   Rev 1.3   Oct 27 2004 11:27:08   popescu
//PET 1117/06
//
//   Rev 1.2   Oct 22 2004 19:59:00   popescu
//PET 1117/06, work in progress...
//
//   Rev 1.1   Oct 21 2004 06:29:32   popescu
//PET 1117/06 - Trade processing work in progress..
//
//   Rev 1.0   Oct 01 2004 19:30:06   popescu
//Initial revision.
 * 
 *    Rev 1.206   Sep 15 2004 15:35:34   popescu
// 
*/