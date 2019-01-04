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
// ^FILE   : Rollover.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2004
//
// ^CLASS    : Rollover2
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\redemption.hpp>
#include <ifastcbo\purchase.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class BankInstructions;
class FundMaster;
class AmsMstrInfo;

class IFASTCBO_LINKAGE Rollover : public Redemption, public Purchase
{
public:
   Rollover (BFAbstractCBO &parent);
   virtual ~Rollover ();
//whether tax rates are allowed
   virtual bool areTaxRatesAllowed (const BFDataGroupId &idDataGroup);
//whether split commissions are allowed
   virtual bool isSplitCommissionAllowed (const BFDataGroupId &idDataGroup);
//whether settle locations are allowed
   virtual bool isSettleLocAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isAccountCloningAllowed (const BFDataGroupId &idDataGroup);
//multiple settle location
   virtual bool areMultipleSettleLocAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isAssociationToOriginalContribAllowed (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFData &data);
   SEVERITY doValidateAll ( const BFDataGroupId& idDataGroup, 
                            long lValidateGroup);
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup);
   virtual SEVERITY transTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
   virtual SEVERITY getDefaultBankInstructions ( BankInstructions *&pBankInstructions, 
                                                 const BFDataGroupId &idDataGroup);
   virtual void getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                          BFFieldId &classCodeFieldId);
   virtual void getPurchaseFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                                  BFFieldId &classCodeFieldId);
   virtual void getAccountFieldId (BFFieldId &accountFieldId);
   virtual void getPurchaseAccountFieldId (BFFieldId &accountFieldId);
   virtual bool isACHApplicable (const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountTrade ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountToTrade ( MFAccount *pMFAccount, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAccountTo ( MFAccount *pMFAccount, 
                                        const BFDataGroupId &idDataGroup);
//fund validation
   virtual SEVERITY validateFundCode ( const DString &fundCode, 
                                       const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToFundCode ( const DString &fundCode, 
                                         const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateMasterActAMS (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundClass ( const DString &fundCode, 
                                        const DString &classCode, 
                                        const DString &accountNum, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToFundClass ( const DString &fundCode, 
                                          const DString &classCode, 
                                          const DString &accountNum, 
                                          const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFromToFundClass ( const DString &fromCode,
                                              const DString &fromClass,
                                              const DString &toCode,
                                              const DString &toClass,
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
   virtual SEVERITY fromFundClassRelatedChanges ( const DString &fundCode, 
                                                  const DString &classCode, 
                                                  const BFDataGroupId &idDataGroup);
   virtual SEVERITY toFundClassRelatedChanges ( const DString &fundCode, 
                                                const DString &classCode, 
                                                const BFDataGroupId &idDataGroup);
   virtual SEVERITY getPurchaseRepInfoFields ( DString &broker, 
                                               DString &branch, 
                                               DString &agent, 
                                               const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateTradeDate ( const DString &tradeDate, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmtTypeGrossNet (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmtType ( const DString &amtType, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmount ( const DString &amount,  
                                     const BFDataGroupId& idDataGroup);
   virtual bool isCashDateUpdatable ( FundMaster *pFundMaster,
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
   virtual SEVERITY filterSettleCurrencyForFund ( const DString &inCurrSubstList,
                                                  DString &currSubstList,
                                                  const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateCurrency ( const DString &currency,
                                       const BFDataGroupId &idDataGroup);
   virtual SEVERITY payTypeRelatedChanges (const BFDataGroupId &idDataGroup);
// validate Settle Source 
   virtual SEVERITY validateSettleSource ( const DString &settleSource,
                                           const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateEUSDBackdates( const DString &dstrFund,
	                                       const DString &dstrClass,
										   const DString &dstrAccountNum,
	                                       const BFDataGroupId &idDataGroup );

   virtual void setDefaultPayType ( const DString dstrAccountNum, 
	                                 DString &payType,
								            const BFDataGroupId &idDataGroup);

   SEVERITY getFormerSpouseList( DString& strFormerSpouses, 
	                              const BFDataGroupId &idDataGroup);

   virtual bool isRESPTransferAllowed (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateLinkedEntity(const DString& strValue, const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmtTypeRedCode (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmountRedCode (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateRESPTradeResidency(const DString &redcode, 
                                               const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateTradePayTypeFundClass( const BFDataGroupId &idDataGroup );
   virtual SEVERITY orderTypeRelatedChanges ( const BFDataGroupId &idDataGroup, 
                                               bool bValidateDate /* = true*/);
   virtual bool isExternalInstitutionTrackingEnable(const BFDataGroupId& idDataGroup);
   virtual SEVERITY initPriceTypesList(const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateRDSPTrade (const BFDataGroupId &idDataGroup);
   virtual bool isRDSPTransferAllowed (const BFDataGroupId &idDataGroup);

private:
   SEVERITY validateLSIFFund ( const DString &fundCode, 
                               const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Rollover.hpp-arc  $
//
//   Rev 1.31   Apr 20 2012 15:23:14   wp040027
//R12.3P0188394_Value date incorrect in ED & PW Non PF fund class
//
//   Rev 1.30   Feb 07 2011 18:32:02   dchatcha
//P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
//
//   Rev 1.29   Apr 22 2010 07:33:34   kitticha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.28   Apr 22 2010 05:29:12   kitticha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.27   Apr 21 2010 01:22:20   popescu
//RESP-QESI Resp transfer screen
//
//   Rev 1.26   Apr 14 2010 23:59:20   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.25   Apr 14 2010 09:44:06   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.24   Aug 11 2009 13:57:46   jankovii
//PET0164824 FN01 - Eiger iShares Orders and ETF Fields
//
//   Rev 1.23   27 Jul 2009 15:14:50   popescu
//Project Eiger - P0147738 FN36 - Adding a field to figure out when the multiple settle locations should show up
//
//   Rev 1.22   06 Oct 2008 13:19:48   kovacsro
//PET142007  FN01 TFSA
//
//   Rev 1.21   01 Oct 2008 12:00:56   popescu
//Check in for incident  1419539
//
//   Rev 1.20   May 04 2007 13:59:32   jankovii
//PET 2321 FN01 - MT54X Default Pay Type.
//
//   Rev 1.19   Nov 09 2006 00:08:16   popescu
//PET 2281/Fn01 - cloning account - TA  synch-up from rel 73
//
//   Rev 1.18   Oct 30 2006 17:05:40   jankovii
//PET 2185 FN04 - Trade restrictions.
//
//   Rev 1.17   Jul 07 2005 11:40:46   porteanm
//PET1171 EUSD 1B - Added validateEUSDBackDates().
//
//   Rev 1.16   Apr 06 2005 09:14:40   popescu
//Incident 243157/243387 - SettleSource validation.
//
//   Rev 1.15   Mar 10 2005 10:59:02   porteanm
//Incident 243157/243387 - SettleSource validation.
//
//   Rev 1.14   Dec 29 2004 11:22:20   popescu
//PTS 10037302, do not validate amount precision for amount type units
//
//   Rev 1.13   Dec 07 2004 01:37:50   popescu
//PET 1117/56 trades processing/modify trade
//
//   Rev 1.12   Dec 01 2004 15:45:00   popescu
//PET 1117/56 fees processing, calculate the discount rate
//
//   Rev 1.11   Nov 30 2004 20:10:08   popescu
//PET 1117/06
//
//   Rev 1.10   Nov 29 2004 20:30:40   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.9   Nov 24 2004 21:36:12   popescu
//PET 1117/06/56. trade processing, settle location
//
//   Rev 1.8   Nov 14 2004 14:52:30   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.7   Nov 06 2004 00:42:30   popescu
//PET 1117/06, synch changes
//
//   Rev 1.6   Nov 04 2004 17:41:42   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.5   Nov 02 2004 19:19:36   popescu
//PET 1117/06 Trade processing...
//
//   Rev 1.4   Oct 28 2004 18:23:54   popescu
//PET 1117/06
//
//   Rev 1.3   Oct 27 2004 11:27:00   popescu
//PET 1117/06
//
//   Rev 1.2   Oct 22 2004 19:58:54   popescu
//PET 1117/06, work in progress...
//
//   Rev 1.1   Oct 21 2004 06:29:20   popescu
//PET 1117/06 - Trade processing work in progress..
//
//   Rev 1.0   Oct 01 2004 19:29:58   popescu
//Initial revision.
 * 
 *    Rev 1.206   Sep 15 2004 15:35:34   popescu
// 
*/