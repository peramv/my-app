#pragma once
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
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : BankInstructions.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 2/9/01
//
// ^CLASS    : BankInstructions
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class RRIFBankInstructions;
class SystematicBankInstructions;
class DistributionBankInstructions;
class AccountDistribution;
class SettlementTradeBankInstructions;
class TradeBankInstructions;
class MatSweepInstrBank;
class AcctCommitBank;
class ContractMatInstrBank;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

extern const BFFieldId fieldsInCorresBank[];
extern const BFFieldId fieldsInBeneficialBank[];
extern const int numFieldsInCorresBank;
extern const int numFieldsInBeneficialBank;

struct IARecordPeriod;

class IFASTCBO_LINKAGE BankInstructions : public MFCanBFCbo, private boost::noncopyable
{
public:
   static bool isCorrBankInfoEmpty ( BFCBO *pCBO, 
                                     const BFDataGroupId &idDataGroup);
   static bool isCorrBankInfoEntered ( BFCBO *pCBO, 
                                       const BFDataGroupId &idDataGroup);

   //X-structors
   BankInstructions (BFAbstractCBO &parent);
   ~BankInstructions ();

//init methods
   SEVERITY init ( const BFData &data, 
                   const DString &dstrBankType,
                   bool bBaseDelete = false);
   SEVERITY initNew ( const DString &dstrBankType, 
                      const BFDataGroupId &idDataGroup);
//cloning methods use to clone this banking object into a
//not on host banking object
   SEVERITY cloneInto ( DistributionBankInstructions *&pBankInstructions, 
                        BFAbstractCBO* pParent, 
                        const BFDataGroupId &idDataGroup);
   SEVERITY cloneInto ( RRIFBankInstructions *&pBankInstructions, 
                        BFAbstractCBO* pParent, 
                        const BFDataGroupId &idDataGroup);
   SEVERITY cloneInto ( SystematicBankInstructions *&pBankInstructions, 
                        BFAbstractCBO* pParent, 
                        const BFDataGroupId &idDataGroup);
   SEVERITY cloneInto ( SettlementTradeBankInstructions *&pBankInstructions, 
                        BFAbstractCBO* pParent, 
                        const BFDataGroupId &idDataGroup);
   SEVERITY cloneInto ( TradeBankInstructions *&pBankInstructions, 
                        BFAbstractCBO* pParent, 
                        const BFDataGroupId &idDataGroup);
   SEVERITY cloneInto ( MatSweepInstrBank *&pBankInstructions, 
                        BFAbstractCBO* pParent, 
                        const BFDataGroupId &idDataGroup);
   SEVERITY cloneInto ( AcctCommitBank *&pBankInstructions, 
                        BFAbstractCBO* pParent, 
                        const BFDataGroupId &idDataGroup);
   SEVERITY cloneInto ( ContractMatInstrBank *&pBankInstructions, 
                        BFAbstractCBO* pParent, 
                        const BFDataGroupId &idDataGroup);
   
   virtual SEVERITY setField  ( const BFFieldId &fieldId,
                                const DString &strValue,
                                const BFDataGroupId &idDataGroup, 
                                bool lFormatted = true,
                                bool lSideEffect = false,
                                bool bCheckCurrentValue = true);

   void setFieldsDistribBankReadOnly ( const BFDataGroupId &idDataGroup = BF::HOST, 
                                       bool bReadOnly = true);
   virtual bool isBankingUpdatedByUser(const BFDataGroupId &idDataGroup);
protected:
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doReset (const BFDataGroupId &idDataGroup);
   virtual SEVERITY preInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY postInit (const BFDataGroupId &idDataGroup);
   //validation methods
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);

//file processor
   SEVERITY fileProcessorRelatedChanges (const BFDataGroupId &idDataGroup);
//currency
   SEVERITY currencyRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY getBankInfo ( const BFFieldId fields[], 
                          const BFDataGroupId &idDataGroup);
   SEVERITY eftRedemptionRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY eftPurchaseRelatedChanges (const BFDataGroupId &idDataGroup);
   void setFieldsReadOnly ( const BFFieldId fieldsArray[], 
                            int numFields, 
                            const BFDataGroupId &idDataGroup = BF::HOST, 
                            bool bReadOnly = true);

   SEVERITY validateBankAcctUseCodeCurrType(const BFDataGroupId &idDataGroup);
   SEVERITY validateAcctUseCodeForInvestorAuthorizationInfo(const BFDataGroupId &idDataGroup);
   SEVERITY validateBankForIA( const BFDataGroupId &idDataGroup );
   SEVERITY verifyStatusRelatedChanges (const BFFieldId &idFieldId, const BFDataGroupId &idDataGroup);
   SEVERITY validateStopDateEffDate(const BFDataGroupId &idDataGroup);

   bool _bGetsCloned; //indicate if the object is in the process of being cloned

private:
   //clones this object, using as type and parent the given ones
   template <class _X>
      SEVERITY cloneInto_X ( _X *&pBankInstructions, 
                             BFAbstractCBO* pParent, 
                             const BFDataGroupId &idDataGroup);
   SEVERITY commonInit ( const DString &dstrBankType,
                         const BFDataGroupId &idDataGroup);
   //correspondent bank info
   bool isCorrBankInfoApplicable  (const BFDataGroupId &idDataGroup);
   void setReadOnlyAndClearCorrBank ( bool readonly, 
                                      const BFDataGroupId &idDataGroup);

   void setBankInfoReadOnly ( const BFFieldId fieldIds[], 
                              const BFDataGroupId &idDataGroup = BF::HOST, 
                              bool bReadOnly = true);
//method to check if file processor and currency are allowed to be loaded dynamically
   SEVERITY getTransTypeFor207Call ( DString &transType, 
                                     DString &achControl,
                                     const BFDataGroupId &idDataGroup);
   DString getBankingEntity(const DString& strBankType);

   SEVERITY validateCountryCode ( const DString &countryCode,
                                  const BFDataGroupId &idDataGroup);

   SEVERITY initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew);


//misc
   bool isTradeBank (const BFDataGroupId &idDataGroup);
   bool isShareholderBank (const BFDataGroupId &idDataGroup);  
   bool isAccountBank (const BFDataGroupId &idDataGroup);
   bool isDistributorBank (const BFDataGroupId &idDataGroup);
   bool isFundBank (const BFDataGroupId &idDataGroup);
   bool isDistributionBank (const BFDataGroupId &idDataGroup);
   bool isSystematicBank (const BFDataGroupId &idDataGroup);
   bool isRRIFBank (const BFDataGroupId &idDataGroup);
   bool isSettlementBank (const BFDataGroupId &idDataGroup);
   bool isClientBank (const BFDataGroupId &idDataGroup);
   bool isDirectTradingBank (const BFDataGroupId &idDataGroup);
   bool isBankTransitNumRequired (const DString &bankType);
   bool isPendingTradeBank (const BFDataGroupId &idDataGroup);
   bool isTransactionBank (const BFDataGroupId &idDataGroup);
   bool isFundGroupBank (const BFDataGroupId &idDataGroup);
   bool isFundSponsorBank (const BFDataGroupId &idDataGroup);
   bool isNonStaticDataBank (const BFDataGroupId &idDataGroup);
   bool isRegAgentBank( const BFDataGroupId &idDataGroup);
   bool isMaturityBank (const BFDataGroupId &idDataGroup);
   bool isAcctCommitBank (const BFDataGroupId &idDataGroup);
   bool bIsRedirect2RegAgentInst(const BFDataGroupId &idDataGroup);
   static bool sortByEffectiveDate(const IARecordPeriod& input1, 
                                   const IARecordPeriod& input2);
   DString  _dstrVerifyStatus;
   bool     _bIsDirty;
   bool     _bCanVerify;
   bool     _bVerificationEnabled;
   bool     _bInit;
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructions.hpp-arc  $
 * 
 *    Rev 1.61   Apr 24 2012 20:54:18   wp040039
 * PETP0187485 - Trade Entry And Processing
 * 
 *    Rev 1.60   Apr 03 2012 20:08:58   wp040039
 * PETP0187485-Registartion Agent  Banking
 * 
 *    Rev 1.59   Mar 02 2012 16:38:56   wp040100
 * P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
 * 
 *    Rev 1.58   Feb 24 2012 18:40:44   if991250
 * Account Commitment
 * 
 *    Rev 1.57   Feb 02 2012 15:05:20   if991250
 * Maturity/Interest Instructions banking
 * 
 *    Rev 1.56   Feb 18 2011 09:43:34   kitticha
 * PET0179308_FN01_IN2431866 - Remove the DSK logic to make the Correspondent & Originator required.
 * 
 *    Rev 1.55   Jan 31 2011 18:07:32   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.54   Mar 08 2010 12:14:52   popescu
 * Incident 2039534 - fixed the issue where unverified banking instruction are not copied with the proper value of the verify status field. they get reset to verified, if they are un-verified
 * 
 *    Rev 1.53   Jan 13 2010 09:25:12   dchatcha
 * IN# 1971377 - R97_Static Data_File Processor&Bank are blank after deleting distribution option.
 * 
 *    Rev 1.52   Jan 12 2010 15:35:14   jankovii
 * IN 1964321 & 1964324 - Static data issues.
 * 
 *    Rev 1.51   Nov 17 2009 15:22:02   jankovii
 * PET0166583 FN01 Static Data Changes Banking 
 * 
 *    Rev 1.50   Oct 26 2009 09:54:38   dchatcha
 * IN# 1872743 - PET156681-FN14 Inactive Banking a/c warning message.
 * 
 *    Rev 1.49   Jul 16 2009 19:11:32   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Integration issues.
 * 
 *    Rev 1.48   Jul 09 2009 14:58:56   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.47   09 Mar 2009 11:12:32   kovacsro
 * IN#1609264 - PET155543R92 Bank name not display in acct level distrib instruction
 * 
 *    Rev 1.46   Feb 20 2008 09:50:54   jankovii
 * PET 2385 FN06 Bank Details upload.
 * 
 *    Rev 1.45   Oct 18 2006 15:53:26   popescu
 * PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
 * 
 *    Rev 1.44   Sep 10 2006 17:58:30   popescu
 * STP 2192/12
 * 
 *    Rev 1.43   Jul 31 2006 15:28:16   ZHANGCEL
 * PET2192 FN11 -- MgmtCo Banking related changes
 * 
 *    Rev 1.42   Jan 18 2005 12:53:54   popescu
 * PTS 10037935, added new rej-error code to control whether bank information country code is mandatory or not
 * 
 *    Rev 1.41   Nov 04 2004 17:37:10   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.40   Sep 21 2004 13:33:42   HERNANDO
 * PET1094 FN06 - Absatzmeldung Files enhancement.  Added isFundGroupBank.
 * 
 *    Rev 1.39   Sep 15 2004 16:22:56   popescu
 * PET 1094/06, file processor is not applicable for fund sponsor banking
 * 
 *    Rev 1.38   Apr 05 2004 16:25:46   popescu
 * PTS 10028532, reset button doesn' work properly
 * 
 *    Rev 1.37   Feb 17 2004 10:36:08   popescu
 * PET965.FN1 SSB Profile restriction, re-added the banking files to avoid branching
 * 
 *    Rev 1.36   Feb 17 2004 10:31:20   popescu
 * PTS 10027188, copy the value of the file processor field into trading screen, and trade banking screen, when modifying a pending trade; removed the substitution list of the BankInstrType, since the combo is being loaded anyhow in the dialog. This field is not  updatable. Assign the correct transaction type to the bankinstructions4trxn object and set all the fields to read only in postInit
 * 
 *    Rev 1.35   Feb 11 2004 18:45:22   popescu
 * PTS 10026899, reloaded currency set for Suppress pay type in Payment Instructions, loaded banking currency dynamically based on the file processor value if not empty
 * 
 *    Rev 1.34   Jan 30 2004 15:04:44   popescu
 * PTS 10026408, 
 * Removed hard coding of the file processor for banking, for broker/branch/slsrep, systematic,distribution,trade,shareholder.
 * Set the value of the file processor to NULL_STRING if there are no values from the back-end, 
 * For banking and distributions set the file processor NOT required if there are no values at the back-end
 * 
 *    Rev 1.33   Dec 29 2003 18:35:36   popescu
 * PTS 10025597, cleared the TransitNum if the bank id type changes and the bank id type doesn't support transits
 * 
 *    Rev 1.32   Nov 19 2003 18:14:10   popescu
 * Field TransitNo should be set as required. Fixed a broken code while working on PET 809, FN 17
 * 
 *    Rev 1.31   Oct 06 2003 12:43:00   popescu
 * Added banking support for DirectTrading enhancement
 * 
 *    Rev 1.30   Oct 04 2003 15:57:12   popescu
 * CIBC PET 809, FN 13;
 * also cleaned-up BankSearch and BankList objects,
 * replaced with FinancialInstitutionList
 * 
 *    Rev 1.29   Sep 25 2003 17:19:56   popescu
 * PTS 10022248, the BAFF option for File processor has been made available for Client level banking, as well
 * 
 *    Rev 1.28   Aug 02 2003 11:39:34   popescu
 * more banking
 * 
 *    Rev 1.27   Jul 31 2003 17:09:38   popescu
 * few fixes and fund/class search
 * 
 *    Rev 1.26   Jul 31 2003 13:50:54   popescu
 * PTS 10020265, added more bank fields to the RRIF object so they can be copied over to the update view 129, in case new bank mstr needs to be created
 * 
 *    Rev 1.25   Jul 30 2003 11:35:00   popescu
 * Correspondent banking is enabled for Distribution banking, AcctUsage EFT, and moved some acct usage codes under the namespace AcctUseCode
 * 
 *    Rev 1.24   Jul 29 2003 10:41:02   popescu
 * Fixed PTS 10002134
 * 
 *    Rev 1.23   Jun 25 2003 12:19:06   FENGYONG
 * PET821_FN17.1.1
 * 
 *    Rev 1.22   Jun 18 2003 17:45:00   popescu
 * RRIF Banking Enhancement , business rules, bug fixes 
 * 
 *    Rev 1.21   Jun 05 2003 10:42:18   popescu
 * business rules work for banking
 * 
 *    Rev 1.20   Jun 03 2003 20:58:40   popescu
 * Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
 * 
 *    Rev 1.19   Jun 01 2003 17:19:44   popescu
 * Removed obsolete code
 * 
 *    Rev 1.18   Jun 01 2003 17:07:38   popescu
 * Systematic  &Distribution banking work
 * 
 *    Rev 1.17   May 31 2003 20:29:14   popescu
 * RRIF work part ||
 * 
 *    Rev 1.16   May 31 2003 11:54:46   popescu
 * RRIF bank work
 * 
 *    Rev 1.15   May 27 2003 13:14:04   popescu
 * RRIF Banking work
 * 
 *    Rev 1.14   May 23 2003 10:04:14   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.13   May 22 2003 14:11:58   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
//
//   Rev 1.36   Mar 21 2003 18:00:14   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.35   Oct 09 2002 23:54:04   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.34   Sep 09 2002 12:13:20   KOVACSRO
//Sync-up for PTS10009768
//
//   Rev 1.33   Aug 29 2002 12:51:52   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.32   Jul 19 2002 10:07:28   KOVACSRO
//Added clearCorrBankFields ()
//
//   Rev 1.31   Jul 05 2002 11:50:48   KOVACSRO
//Dynamically loading AcctUse subst. list.
//
//   Rev 1.30   Jun 28 2002 13:45:18   KOVACSRO
//moved payMethodRelatedChanges to protected.
//
//   Rev 1.29   Jun 21 2002 17:38:42   KOVACSRO
//Added isCorrBankInfoAplicable
//
//   Rev 1.28   Jun 20 2002 13:34:58   KOVACSRO
//Added isMultiCurrency
//
//   Rev 1.27   Jun 17 2002 17:27:36   KOVACSRO
//name change.
//
//   Rev 1.26   Jun 16 2002 16:58:28   KOVACSRO
//Added setBankAcctName.
//
//   Rev 1.25   Jun 16 2002 12:53:44   HSUCHIN
//added some new functions and renamed setFieldFlag to setBankAcctTypeRequired
//
//   Rev 1.24   Jun 14 2002 17:32:18   KOVACSRO
//new TradeBankInstructions class changes.
//
//   Rev 1.23   Jun 14 2002 14:02:46   HSUCHIN
//added function setFieldsReadOnly
//
//   Rev 1.22   Jun 13 2002 17:36:30   HSUCHIN
//added extra parameter to init
//
//   Rev 1.21   Jun 13 2002 17:25:34   KOVACSRO
//PendingTrade modifications
//
//   Rev 1.20   Jun 12 2002 17:41:18   KOVACSRO
//Added distribution and systematic bank types
//
//   Rev 1.19   Jun 11 2002 12:24:04   HSUCHIN
//added new init for settlement
//
//   Rev 1.18   Jun 07 2002 17:33:30   KOVACSRO
//International Wire modifications.
//
//   Rev 1.17   22 May 2002 22:22:22   PURDYECH
//BFData Implementation
//
//   Rev 1.16   22 May 2002 18:21:44   PURDYECH
//BFData Implementation
//
//   Rev 1.15   Mar 26 2002 16:18:36   ZHANGCEL
//added a overitted function: getField ()
//
//   Rev 1.14   19 Mar 2002 13:15:12   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.13   Feb 25 2002 18:53:58   PURDYECH
//Phase 1 of BFData Rollout - Base Component Compatibility
//
//   Rev 1.12   02 Oct 2001 10:58:10   WINNIE
//bug fix for bank validation
//
//   Rev 1.11   05 Aug 2001 14:36:46   YINGZ
//fix reset problem
//
//   Rev 1.10   17 Jul 2001 10:14:52   YINGZ
//implement ACHProcessor
//
//   Rev 1.9   Jul 04 2001 10:45:08   ZHANGCEL
//Sync up to 1.4.1.7
//
//   Rev 1.8   May 16 2001 13:43:46   WINNIE
//sycn up with 1.4.1.4 : Clean up the initization and set readonly fields
//
//   Rev 1.7   10 May 2001 12:14:16   KOVACSRO
//sync up.
//
//   Rev 1.6   09 May 2001 14:29:10   HSUCHIN
//Sync up with SSB
//
//   Rev 1.5   03 May 2001 14:03:48   SMITHDAV
//Session management restructuring.
//
//   Rev 1.4   Apr 04 2001 14:33:02   WINNIE
//get bank name and validation
//
//   Rev 1.3   Apr 03 2001 14:30:08   WINNIE
//disable corresponding bank fields
//
//   Rev 1.2   Apr 01 2001 16:20:42   WINNIE
//default value and validation
//
//   Rev 1.1   30 Mar 2001 17:12:00   BUZILAMI
//Systematic bank changes
//
//   Rev 1.0   Feb 21 2001 16:01:18   BUZILAMI
//Initial revision.
//
 * 
*/