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
// ^FILE   : Purchase.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2004
//
// ^CLASS    : Purchase
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

class IFASTCBO_LINKAGE Purchase : virtual public Trade
{
public:
   Purchase (BFAbstractCBO &parent);
   virtual ~Purchase ();
//whether split commissions are allowed
   virtual bool isSplitCommissionAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isSettleLocAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isROAApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isEUSDApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isAssociationToOriginalContribAllowed (const BFDataGroupId &idDataGroup);
//multiple settle location
   virtual bool areMultipleSettleLocAllowed (const BFDataGroupId &idDataGroup);
//GIA- INA
   virtual bool isGIAAttribAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isMaturityInstrAllowed (const BFDataGroupId &idDataGroup);
   virtual bool areAllocationsAllowed (const BFDataGroupId &idDataGroup);
   virtual SEVERITY initPriceTypesList (const BFDataGroupId &idDataGroup);

protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFData &data);
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void populateFieldsWithDefaultValues (const BFDataGroupId &idDataGroup, const long &lMod);
   virtual void setFieldWithDefaultValue(const BFFieldId &idField,const BFDataGroupId &idDataGroup );

   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup );
   virtual SEVERITY transTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual void getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                          BFFieldId &classCodeFieldId) ;
   virtual void getPurchaseFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                                  BFFieldId &classCodeFieldId);
   SEVERITY getPurchaseFundField ( const BFFieldId &idField, 
                                   DString &strValue,
                                   const BFDataGroupId &idDataGroup);
   virtual void getAccountFieldId (BFFieldId &accountFieldId);
   virtual void getPurchaseAccountFieldId (BFFieldId &accountFieldId);
   SEVERITY getPurchaseAccountField ( const BFFieldId &idField, 
                                      DString &strValue,
                                      const BFDataGroupId &idDataGroup);
   SEVERITY getPurchaseAccount ( MFAccount *&pMFAccount, 
                                 const BFDataGroupId &idDataGroup);

//validation methods
   virtual SEVERITY validateNetOrdType (const BFDataGroupId &idDataGroup);
   virtual bool isACHApplicable (const BFDataGroupId &idDataGroup);
   virtual SEVERITY getDefaultBankInstructions ( BankInstructions *&pBankInstructions, 
                                                 const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountTrade ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
//fund validation
   virtual SEVERITY validateMasterActAMS (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundCode ( const DString &fundCode, 
                                       const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundClass ( const DString &fundCode, 
                                        const DString &classCode, 
                                        const DString &accountNum, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY fromFundClassRelatedChanges ( const DString &fundCode, 
                                                  const DString &classCode, 
                                                  const BFDataGroupId &idDataGroup);
   virtual SEVERITY getPurchaseRepInfoFields ( DString &broker, 
                                               DString &branch, 
                                               DString &agent, 
                                               const BFDataGroupId &idDataGroup);
//date validation
   virtual SEVERITY validateTradeDate ( const DString &tradeDate, 
                                        const BFDataGroupId &idDataGroup);
//deposit type, id validation
   virtual SEVERITY validateDepositType ( const DString &depositType,
                                          const BFDataGroupId &idDataGroup);
   SEVERITY validateDepositId ( const DString &depositId,
                                const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateCertRequired ( const DString &certRequired,
                                           const BFDataGroupId &idDataGroup);
   SEVERITY validateBorrowedFunds (const BFDataGroupId &idDataGroup);
   virtual bool isCashDateUpdatable ( FundMaster *pFundMaster,
                                      const BFDataGroupId &idDataGroup);
//amt type validation
   virtual SEVERITY validateAmtType ( const DString &amtType, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmount ( const DString &amount,  
                                     const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateAmtTypeGrossNet (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateMinFromFundAmount ( const DString &accountNum,
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
//currency
   virtual SEVERITY validateCurrency ( const DString &currency,
                                       const BFDataGroupId &idDataGroup);
   virtual SEVERITY filterSettleCurrencyForFund ( const DString &inCurrSubstList,
                                                  DString &currSubstList,
                                                  const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateSettleSource ( const DString &settleType,
                                           const BFDataGroupId &idDataGroup );
//PET 1023/01
   virtual void getROARelatedFields ( DString &amt,
                                      DString &amtType, 
                                      DString &currency,
                                      DString &exchRate, 
                                      const BFDataGroupId &idDataGroup);

   virtual void setDefaultPayType ( const DString dstrAccountNum, 
                                    DString &payType,
                                    const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFromSoftCapCheck (const BFDataGroupId &idDataGroup);
   bool isResidencyRequired( DString& strAccountNum, const BFDataGroupId &idDataGroup );
   SEVERITY getFormerSpouseList( DString& strFormerSpouses, const BFDataGroupId &idDataGroup );
   virtual SEVERITY validateClosedCountryForPendingTrades (const BFDataGroupId &idDataGroup);
   bool isCheckStartEndDate(){ return true;};
   virtual bool areRESPBenefAllocationsAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isRESPTransferAllowed (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateLinkedEntity(const DString& strValue, const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmtTypeRedCode (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmountRedCode (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateRESPTradeResidency(const DString &redcode, 
                                               const BFDataGroupId &idDataGroup);
   virtual SEVERITY validatePayInstrOption(const DString& strValue, const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateTradePayTypeFundClass( const BFDataGroupId &idDataGroup );
   virtual SEVERITY payTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY getDefaultFundClassPayType (const DString dstrAccountNum, 
                                                DString &payType,
                                                const DString dstrFundCode,
                                                const DString dstrClassCode,
                                                const BFDataGroupId &idDataGroup);
   SEVERITY giAttribRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY difFundRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundForERISAAccount ( const DString &fundCode, 
                                                  const DString &classCode, 
                                                  const BFDataGroupId &idDataGroup);
   SEVERITY validatePayStatus (const BFDataGroupId& idDataGroup);

   SEVERITY validateSEGTradeEntry(const DString &accountNum,
                                  const DString &fundCode,
                                  const DString &classCode,
                                  const DString &tradeDate,
                                  const DString &validationType,
                                  const DString &transType,
                                  const DString &transID,
                                  const BFDataGroupId &idDataGroup);
   virtual SEVERITY orderTypeRelatedChanges ( const BFDataGroupId &idDataGroup, 
                                               bool bValidateDate /* = true*/);
   //P0186486FN09 - Employee and Agent Account Gap#8A                              
   SEVERITY validateAccountType ( MFAccount *pMFAccount, 
                                 const BFDataGroupId &idDataGroup);
   SEVERITY validateEmployeeAgentPurchase( const DString &fundCode, const BFDataGroupId &idDataGroup);
   SEVERITY loadBusinessTypeSubslist( const BFDataGroupId &idDataGroup);//P0186486_FN15_The Source of Funds
   SEVERITY RightToCancelRelatedChanges (DString &dstrRTC,const BFDataGroupId& idDataGroup);  
   virtual SEVERITY RDRAdviceRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY validateAnnuitantGender (const BFDataGroupId &idDataGroup);
   virtual bool isExternalInstitutionTrackingEnable(const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateRDSPTrade (const BFDataGroupId &idDataGroup);
   virtual bool isRDSPTransferAllowed (const BFDataGroupId &idDataGroup);

private:
   SEVERITY validateAmtTypeSettleCurrency (const BFDataGroupId &idDataGroup);
   SEVERITY validateAmtTypePayType (const BFDataGroupId &idDataGroup);
//PET1117.FN6.R3
   SEVERITY acqFeeOptionDefault (const BFDataGroupId &idDataGroup);
   SEVERITY validateAcqFeeOption ( const DString &acqFeeOption, 
                                   const BFDataGroupId &idDataGroup);
//PET1117.FN56.R2.4.0
   SEVERITY readMinUnits ( const DString &transType,
                           const DString &fundCode,
                           const DString &classCode,
                           const DString &accountNum,
                           DString &minUnits, 
                           DString &errorSeverityLevel, 
                           const BFDataGroupId &idDataGroup);
   SEVERITY amsAccountRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY setSourceOfFundsChecked (const BFDataGroupId &idDataGroup);

	// if JumboPriceApplicable_149 is "Yes" and LoadType_56 is "FEL" and IncvActive_107 is "Yes"
	// and IncvBaseOn_107 is "6", return "true", otherwise, return "false"
	bool isJumboPriceApplicable ( const BFDataGroupId &idDataGroup);
   DString _defaultFeeModelOption;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Purchase.hpp-arc  $
//
//   Rev 1.82   Jul 26 2012 10:47:48   wp040027
//P0198518 - RDR Functionality
//
//   Rev 1.81   Jul 02 2012 19:05:42   wp040132
//P0199883_FN01_Cancellation Rights - Right To Cancel
//
//   Rev 1.80   May 16 2012 05:15:08   panatcha
//IN2929301 -  Agent and Employee
//
//   Rev 1.79   Apr 23 2012 15:51:46   wp040027
//Sync up: R12.3P0188394_Value date incorrect in ED & PW Non PF fund class
//
//   Rev 1.78   Apr 20 2012 03:44:12   panatcha
//P0186486_FN15_The Source of Funds
//
//   Rev 1.77   Apr 10 2012 05:04:56   panatcha
//P0186486FN09 - Employee and Agent Account Gap#8A
//
//   Rev 1.76   Mar 05 2012 12:11:10   dchatcha
//P0186484 FN05 - SEG Trade Processing.
//
//   Rev 1.75   Jan 25 2012 13:58:54   jankovii
//Sync up: IN 2820320 - Rel12.2 PET0186477 - DIF Trade Entry Screen Issues
//
//   Rev 1.74   Jan 20 2012 15:53:50   wp040027
//P0188394_Performance Fees - Order Entry
//
//   Rev 1.73   Nov 30 2011 17:56:46   dchatcha
//P0186477/FN03 - GIA - Purchase
//
//   Rev 1.72   Nov 27 2011 19:42:16   popescu
//INA Commission Work
//
//   Rev 1.71   Oct 19 2011 22:22:52   popescu
//P0186477/03 - GIA Trading Money In - prep work
//
//   Rev 1.70   Mar 11 2011 10:58:52   kitticha
//IN2450642 - Modify program to support fund-class hierarchy.
//
//   Rev 1.69   Feb 07 2011 18:30:16   dchatcha
//P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
//
//   Rev 1.68   Jan 31 2011 18:40:40   dchatcha
//P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
//
//   Rev 1.67   Apr 22 2010 07:29:00   kitticha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.66   Apr 21 2010 13:59:46   kitticha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.65   Apr 21 2010 01:21:04   popescu
//RESP-QESI Resp transfer screen
//
//   Rev 1.64   Apr 14 2010 23:58:08   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.63   Apr 14 2010 09:41:16   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.62   Mar 08 2010 13:19:06   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
//
//   Rev 1.61   27 Jul 2009 15:13:58   popescu
//Project Eiger - P0147738 FN36 - Adding a field to figure out when the multiple settle locations should show up
//
//   Rev 1.60   Jun 26 2009 06:25:06   kitticha
//IN#1738640 - R94 - Country Schedule - Cannot modify TX even when FundFrom and FundTo are same
//
//   Rev 1.59   06 Oct 2008 13:19:32   kovacsro
//PET142007  FN01 TFSA
//
//   Rev 1.58   01 Oct 2008 11:57:14   popescu
//Check in for incident 1419539	
//
//   Rev 1.57   23 Jul 2007 16:49:50   popescu
//PET 2360 - FN 20 - GAP 20 Soft cap functionality
//
//   Rev 1.56   May 04 2007 13:57:30   jankovii
//PET 2321 FN01 - MT54X Default Pay Type.
//
//   Rev 1.55   Oct 30 2006 17:03:52   jankovii
//PET 2185 FN04 - Trade restrictions.
//
//   Rev 1.54   Nov 29 2005 15:24:14   AGUILAAM
//PET_1228_FN02: EUSD Phase 2
//
//   Rev 1.53   Jul 15 2005 16:05:52   ZHANGCEL
//PET1203 FN04 -- Jumbo Pricing enhancement
//
//   Rev 1.52   Jun 01 2005 17:40:24   popescu
//PET 1203/05 - after code review minor changes - mainly formatting and changed getROAFields access to protected
//
//   Rev 1.51   May 18 2005 16:18:30   porteanm
//PET1203 FN05 - Class B NAV Share Lots - added doValidateAll().
//
//   Rev 1.50   May 18 2005 09:03:30   yingbaol
//PET1203,FN01 Commission-Class A enhancement
//
//   Rev 1.49   Apr 06 2005 19:17:40   popescu
//Incident #282933, missed req - raise a warning if user changes from acq fee option - model got changed 
//
//   Rev 1.48   Mar 10 2005 11:37:08   porteanm
//Incident 243157/243387 - SettleSource validation.
//
//   Rev 1.47   Dec 30 2004 12:41:16   popescu
//PTS 10037260, moved check whether fund sponsor fee model  exists at Trade CBO level, and called the validation for redemptions/purchases as well, missed req: PET1117.FN6.R3.7. 0
//
//   Rev 1.46   Dec 24 2004 14:04:06   popescu
//PTS 10037260, added missed validation against fund code; if fee model code exists at account/shareholder level and fund has fund sponsor then a fund sponsor fee model should be set-up
//
//   Rev 1.45   Dec 07 2004 01:37:40   popescu
//PET 1117/56 trades processing/modify trade
//
//   Rev 1.44   Dec 01 2004 15:44:46   popescu
//PET 1117/56 fees processing, calculate the discount rate
//
//   Rev 1.43   Nov 30 2004 20:10:00   popescu
//PET 1117/06
//
//   Rev 1.42   Nov 29 2004 20:30:26   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.41   Nov 24 2004 21:36:04   popescu
//PET 1117/06/56. trade processing, settle location
//
//   Rev 1.40   Nov 19 2004 14:17:20   popescu
//PET 1117/56 third party processing
//
//   Rev 1.39   Nov 14 2004 14:51:18   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.38   Nov 06 2004 00:42:14   popescu
//PET 1117/06, synch changes
//
//   Rev 1.6   Nov 04 2004 17:38:20   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.5   Nov 02 2004 19:19:30   popescu
//PET 1117/06 Trade processing...
//
//   Rev 1.4   Oct 28 2004 18:23:50   popescu
//PET 1117/06
//
//   Rev 1.3   Oct 27 2004 11:26:56   popescu
//PET 1117/06
//
//   Rev 1.2   Oct 22 2004 19:58:50   popescu
//PET 1117/06, work in progress...
//
//   Rev 1.1   Oct 21 2004 06:29:12   popescu
//PET 1117/06 - Trade processing work in progress..
//
//   Rev 1.0   Oct 01 2004 19:29:52   popescu
//Initial revision.
 * 
 *    Rev 1.206   Sep 15 2004 15:35:34   popescu
// 
*/