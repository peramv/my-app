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
// ^FILE   : Redemption.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2004
//
// ^CLASS    : Redemption
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
class BankInstructions;
class AmsMstrInfo;
class InvestorAuthorization;

class IFASTCBO_LINKAGE Redemption : virtual public Trade
{
public:
   Redemption (BFAbstractCBO &parent);
   virtual ~Redemption();
//whether tax rates are allowed
   virtual bool areTaxRatesAllowed (const BFDataGroupId &idDataGroup);
//whether split commissions are allowed
   virtual bool isSplitCommissionAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isSettleLocAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isShareholderAddressNeeded (const BFDataGroupId &idDataGroup);
   virtual bool isAssociationToOriginalContribAllowed (const BFDataGroupId &idDataGroup);
//whether pay instructions are allowed or not
   virtual bool arePayInstructAllowed (const BFDataGroupId &idDataGroup);
//multiple settle location
   virtual bool areMultipleSettleLocAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isPSEEAPAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isAssociationWithBeneficiaryAllowed (const BFDataGroupId &idDataGroup);
   SEVERITY validateEstateAllocationPresent(const BFDataGroupId &idDataGroup);
   SEVERITY validateXRedCode(const BFDataGroupId &idDataGroup);
   SEVERITY setDefaultForRedCode (const BFDataGroupId &idDataGroup);
   virtual SEVERITY initPriceTypesList (const BFDataGroupId &idDataGroup);
   virtual SEVERITY hasWaiveGatingFund(const BFDataGroupId &idDataGroup);

protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFData &data);
   virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup);
   virtual SEVERITY transTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup );
   virtual void getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                          BFFieldId &classCodeFieldId);
   virtual void getAccountFieldId (BFFieldId &accountFieldId);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
//validation methods
   virtual SEVERITY validateAccount ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
//pay type
   virtual SEVERITY payTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validatePayType ( const DString &payType,
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateMasterActAMS (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundCode ( const DString &fundCode, 
                                       const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundClass ( const DString &fundCode, 
                                        const DString &classCode, 
                                        const DString &accountNum, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateOrderType ( const DString &orderType, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY orderTypeRelatedChanges ( const BFDataGroupId &idDataGroup, 
                                              bool bValidateDate = true);
   virtual SEVERITY fromFundClassRelatedChanges ( const DString &fundCode, 
                                                  const DString &classCode, 
                                                  const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateSettleSource ( const DString &settleType,
                                           const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateValueDate ( const DString &valueDate, 
                                        const BFDataGroupId &idDataGroup);
   virtual bool isACHApplicable (const BFDataGroupId &idDataGroup);
   virtual SEVERITY getDefaultBankInstructions ( BankInstructions *&pBankInstructions, 
                                                 const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountTrade ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmtType ( const DString &amtType, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmtTypeGrossNet (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmountAmtType (const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateAmount ( const DString &amount,  
                                     const BFDataGroupId& idDataGroup);
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
   virtual bool isBrokerAllowed ( const DString &transType,
                                  const DString &accountNum,
                                  const DString &fundCode, 
                                  const DString &classCode,
                                  const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateRedCode ( const DString &redCode, 
                                      const BFDataGroupId &idDataGroup);

   SEVERITY validateLifTransferRedCode( const DString &redCode, 
                                        const BFDataGroupId &idDataGroup);

   virtual bool isFullRedemption (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundCodeRedCodeAmount (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmountGrossNet (const BFDataGroupId &idDataGroup); 
   virtual SEVERITY validateFundBalance ( const DString &accountNum,
                                          const DString &fundCode,
                                          const DString &classCode,
                                          const DString &amount,
                                          const BFDataGroupId &idDataGroup);
   virtual SEVERITY withholdingTaxRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY filterSettleCurrencyForFund ( const DString &inCurrSubstList,
                                                  DString &currSubstList,
                                                  const BFDataGroupId &idDataGroup);

   virtual void getDefaultPaymentFor ( DString &paymentFor, 
                                       const BFDataGroupId &idDataGroup);
   virtual void setDefaultPayType ( const DString dstrAccountNum, 
                                    DString &payType,
                                    const BFDataGroupId &idDataGroup);

   virtual SEVERITY getMaturedUnits( const BFDataGroupId &idDataGroup );
   SEVERITY getFormerSpouseList( DString& strFormerSpouses, const BFDataGroupId &idDataGroup );
   SEVERITY validateRedCodeAgainstWDFeeDefault( const BFDataGroupId &idDataGroup );

   SEVERITY validateFundSubCatIAFundIndicator(const DString& strFundCode,
                                              const DString& strClassCode, 
                                              const BFDataGroupId &idDataGroup );
   SEVERITY getActiveInvestorAuthorization( InvestorAuthorization *&pInvestorAuthorization ,
                                            const DString& strTradeDate,
                                            const BFDataGroupId &idDataGroup );
   virtual SEVERITY validateTradePayTypeFundClass( const BFDataGroupId &idDataGroup );
   virtual bool isRESPTransferAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isAIPAllowed (const BFDataGroupId &idDataGroup);
   //P0185010.FN02.R02.01 - Delivering EAP written notice and tax info return
   virtual bool isEAPAllowed (const BFDataGroupId &idDataGroup);
   //--
   virtual SEVERITY validateLinkedEntity(const DString& strValue, const BFDataGroupId &idDataGroup);
   SEVERITY validateTainted(const DString& strValue, const BFDataGroupId &idDataGroup);

   SEVERITY validateMoneyMktFund (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateSrcOfFund(const DString& strValue, const BFDataGroupId &idDataGroup);
   SEVERITY loadBusinessTypeSubslist( const BFDataGroupId &idDataGroup);
   virtual SEVERITY setGIDIFTradePayType (const BFDataGroupId &idDataGroup);
   virtual SEVERITY raiseFullRedemptionMessage( const BFDataGroupId &idDataGroup);
   virtual bool isExternalInstitutionTrackingEnable(const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateRDSPTrade (const BFDataGroupId &idDataGroup);
   virtual bool isRDSPTransferAllowed (const BFDataGroupId &idDataGroup);
   SEVERITY getGrossNetType( const BFDataGroupId &idDataGroup );

private:
   SEVERITY validateTaxRatePUD ( const DString &dstrTax, 
                                 const BFDataGroupId& idDataGroup);
   SEVERITY validateFedProvTaxRatePUD (const BFDataGroupId& idDataGroup);
   SEVERITY validateSuppressCode (const BFDataGroupId& idDataGroup);
   SEVERITY validateStopSettleRedemption ( const DString &orderType,
                                           const BFDataGroupId &idDataGroup);
   SEVERITY getDefaultTaxAmount ( double dblDefaultTaxRate,
                                  double dblDefaultFedTaxRate,
                                  double dblDefaultProvTaxRate,
                                  const BFDataGroupId& idDataGroup,
                                  double &dblDefaultTaxAmt);
   SEVERITY removeAllocationsIfAccountCanBeClosed (const BFDataGroupId& idDataGroup);
   SEVERITY redCodeRelatedChanges (const BFDataGroupId& idDataGroup);
   SEVERITY validateRESPReportHRDC (const DString &strValue, 
                                    const BFDataGroupId &idDataGroup);
   SEVERITY validateGrantRepaymentReason (const DString &strValue, 
                                          const BFDataGroupId &idDataGroup);
   SEVERITY validateOverContrbRedmYear (const DString &strValue, 
                                        const BFDataGroupId &idDataGroup);
   SEVERITY respRedcodeRelatedChange(const BFDataGroupId &idDataGroup);
   SEVERITY recalculateEstateAllocation(const BFDataGroupId &idDataGroup);
   SEVERITY validateRedCodeUnclaimedProperty(const BFDataGroupId &idDataGroup);

   bool _blTaxable;
   DString _dstrEAPEarningCodes; //IN2689391 - PET0185010_FN01: CESG Paid is tracked at the EAP level
//GI-INA
   virtual bool isGIInvestmentListApplicable(const BFDataGroupId &idDataGroup);
   virtual bool isEstateAllocationListApplicable(const BFDataGroupId &idDataGroup);
   bool bIsRegAgentPayInstOption(const BFDataGroupId &idDataGroup);
   bool bIsTaxTypeRelatedtoRegAgent(const BFDataGroupId &idDataGroup);
   bool isAllFundsFullMoneyOutIndc (const BFDataGroupId& idDataGroup);
   bool fullMoneyOutRelatedChanges (const BFDataGroupId& idDataGroup);

   SEVERITY rdspRedcodeRelatedChange(const BFDataGroupId &idDataGroup);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Redemption.hpp-arc  $
//
//   Rev 1.117   10 Aug 2012 13:07:36   if991250
//Estate Allocation
//
//   Rev 1.116   25 Jul 2012 17:49:42   if991250
//P0186484 : Estate Allocation
//
//   Rev 1.115   May 07 2012 07:34:32   popescu
//PETP0187485 - Trade Entry And Processing
//
//
//   Rev 1.114   Apr 24 2012 21:14:36   wp040039
//PETP0187485 - Trade Entry And Processing
//
//   Rev 1.113   Apr 20 2012 03:39:42   panatcha
//P0186486_FN15_The Source of Funds
//
//   Rev 1.112   Mar 05 2012 11:44:28   dchatcha
//P0186484 FN05 - SEG Trade Processing.
//
//   Rev 1.111   Jan 06 2012 13:38:54   if991250
//IA money out
//
//   Rev 1.110   Dec 08 2011 21:48:16   wp040032
//P0183989 - Money Market Non Receipt
//
//   Rev 1.109   Oct 13 2011 06:18:20   panatcha
//IN2689391 - PET0185010_FN01: CESG Paid is tracked at the EAP level
//
//   Rev 1.108   Oct 07 2011 01:19:08   kitticha
//PETP0183105 FN02 - Unclaimed Property Alberta.
//
//   Rev 1.107   Oct 06 2011 10:45:24   panatcha
//P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
//
//   Rev 1.106   Apr 07 2011 16:10:02   wp040027
//.
//
//   Rev 1.105   Feb 18 2011 04:48:12   kitticha
//PET0165541_FN12_IN2385316 - Default the assisted contribution amount for ED 78(same as PW Q1).
//
//   Rev 1.104   Oct 29 2010 05:05:56   kitticha
//PET0165541 FN03 - QESI Phase3.
//
//   Rev 1.103   Sep 24 2010 14:28:26   jankovii
//PET0175377 FN01 - AIP for Joint RESP Account
//
//   Rev 1.102   Apr 30 2010 08:07:04   kitticha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.101   Apr 26 2010 13:34:12   kitticha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.100   Apr 23 2010 22:22:08   popescu
//PET0165541 FN01 QESI RESP Trading - restore ordertype logic.
//
//   Rev 1.99   Apr 22 2010 07:53:58   dchatcha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.98   Apr 22 2010 04:02:42   dchatcha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.97   Apr 21 2010 13:54:24   kitticha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.96   Apr 20 2010 00:53:56   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading - PSE/EAP   screen
//
//   Rev 1.95   Apr 14 2010 23:58:48   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.94   Apr 14 2010 09:42:46   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.93   Dec 10 2009 23:21:56   dchatcha
//PET0166583 FN02 FN03 - Static Verification Phase 2. Core review, move all of logic from Redemption object to Trade object.
//
//   Rev 1.92   Dec 03 2009 02:59:52   dchatcha
//PET0166583 FN02 FN03 - Static Verification Phase 2.
//
//   Rev 1.91   Aug 11 2009 13:55:58   jankovii
//PET0164824 FN01 - Eiger iShares Orders and ETF Fields
//
//   Rev 1.90   Jul 30 2009 18:35:38   dchatcha
//Synch up: IN#1611516 - New edit at desktop trade level to prevent enter redemption, if there is improper default fee setup.
//
//   Rev 1.89   27 Jul 2009 15:14:28   popescu
//Project Eiger - P0147738 FN36 - Adding a field to figure out when the multiple settle locations should show up
//
//   Rev 1.88   Jul 16 2009 19:30:28   dchatcha
//PET156681 FN14 H36 Investor Authorization, Code Review.
//
//   Rev 1.87   Jul 09 2009 15:02:54   dchatcha
//PET156681 FN14 H36 Investor Authorization.
//
//   Rev 1.86   06 Oct 2008 13:19:42   kovacsro
//PET142007  FN01 TFSA
//
//   Rev 1.85   01 Oct 2008 11:59:10   popescu
//Check in for incident 1419539
//
//   Rev 1.84   Sep 05 2007 09:42:52   smithdav
//IN 980102
//
//   Rev 1.83   24 Jul 2007 20:13:26   popescu
//GAP 20 -22 AIM
//
//   Rev 1.82   May 04 2007 13:58:38   jankovii
//PET 2321 FN01 - MT54X Default Pay Type.
//
//   Rev 1.81   Oct 30 2006 17:04:46   jankovii
//PET 2185 FN04 - Trade restrictions.
//
//   Rev 1.80   Sep 07 2006 21:38:08   popescu
//STP 2192/02
//
//   Rev 1.79   Aug 29 2006 18:15:56   popescu
//STP PET 2192 FN10/11 - bulking netting redemption
//
//   Rev 1.78   Jun 09 2006 14:44:24   popescu
//Incident# 640084 - Added edit check where user cannot place a redemption if redemption code is 02 - Close Account and amount type is all free units.
//
//   Rev 1.77   Dec 31 2004 13:38:30   popescu
//PTS 10037395, settlement currency should be set as required if for redemption the account closes or a full redemption is processed. Also, isFullNotCloseAcctRed method name to isFullRedemption
//
//   Rev 1.76   Dec 29 2004 11:22:14   popescu
//PTS 10037302, do not validate amount precision for amount type units
//
//   Rev 1.75   Dec 07 2004 21:20:30   popescu
//PET 1117/06, pending trades/fees fixes, add-ons
//
//   Rev 1.74   Dec 07 2004 01:37:44   popescu
//PET 1117/56 trades processing/modify trade
//
//   Rev 1.73   Dec 01 2004 15:44:54   popescu
//PET 1117/56 fees processing, calculate the discount rate
//
//   Rev 1.72   Nov 29 2004 20:30:30   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.71   Nov 27 2004 21:19:06   popescu
//PET 1117/06, trades processing
//
//   Rev 1.70   Nov 25 2004 14:59:08   popescu
//PET 1117/06, settle locations
//
//   Rev 1.69   Nov 24 2004 21:36:08   popescu
//PET 1117/06/56. trade processing, settle location
//
//   Rev 1.68   Nov 19 2004 14:17:26   popescu
//PET 1117/56 third party processing
//
//   Rev 1.67   Nov 14 2004 14:51:36   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.66   Nov 06 2004 00:42:20   popescu
//PET 1117/06, synch changes
//
//   Rev 1.6   Nov 04 2004 17:38:24   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.5   Nov 02 2004 19:19:32   popescu
//PET 1117/06 Trade processing...
//
//   Rev 1.4   Oct 28 2004 18:23:52   popescu
//PET 1117/06
//
//   Rev 1.3   Oct 27 2004 11:26:58   popescu
//PET 1117/06
//
//   Rev 1.2   Oct 22 2004 19:58:52   popescu
//PET 1117/06, work in progress...
//
//   Rev 1.1   Oct 21 2004 06:29:16   popescu
//PET 1117/06 - Trade processing work in progress..
//
//   Rev 1.0   Oct 01 2004 19:29:56   popescu
//Initial revision.
 * 
 *    Rev 1.206   Sep 15 2004 15:35:34   popescu
// 
*/