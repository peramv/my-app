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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountDistribution.hpp
// ^AUTHOR : Zijian Ying + Yingbao for M2
// ^DATE   : 10/21/99
//
// ^CLASS    : AccountDistribution
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <ifastcbo\accountdistributionlist.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

#define BANK_GROUP	1

class FundMasterList;
class FundDetailList;
class MgmtCoOptions;
class BankList;
class AddressList;
class DistributionBankInstructionsList;
class TradePayInstructList;
class BankInstructions;

class FundClassDistribOptionsList;

class IFASTCBO_LINKAGE AccountDistribution : public MFCanBFCbo, private boost::noncopyable
{
public:
   AccountDistribution( BFAbstractCBO &parent );
   virtual ~AccountDistribution();  

   SEVERITY  init( const BFDataGroupId& idDataGroup, 
                   const DString& dstrAccountNum, 
                   const DString& dstrShareholderNum,
                   DISTRIBUTION_LEVEL level,
                   BFData *data = NULL,
                   BFData *distributionData = NULL );

   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

   void SetListPointer(FundDetailList* pFundDetailList, FundMasterList* pFundMasterList);
   SEVERITY getSplitList( AccountDistributionList *&pSplitList, const BFDataGroupId& idDataGroup = BF::HOST );
   virtual SEVERITY doApplyRelatedChanges(const BFFieldId& ieldId, const BFDataGroupId& idDataGroup  );
   void CopyInfoToFundClassLevel(BFAbstractCBO *pParentDistribution, const BFDataGroupId& idDataGroup);
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY getBankInstructionsList ( DistributionBankInstructionsList *&pDistributionBankInstructionsList, 
                                      const BFDataGroupId &idDataGroup, 
                                      bool bCreate = true);
   SEVERITY setPayTypeSubstSet ( const BFDataGroupId &idDataGroup, 
                                 const DString &dstrTransType = NULL_STRING, 
                                 const DString &dstrFundCode = NULL_STRING, 
                                 const DString &dstrClassCode = NULL_STRING);
   SEVERITY getPayInstructList (TradePayInstructList *&pTradePayInstructList, 
                                const BFDataGroupId &idDataGroup);
   bool isAllFundsMode( const BFDataGroupId &idDataGroup );
   SEVERITY validateAllFundsDistrib( const BFDataGroupId &idDataGroup );

   SEVERITY verifyStatusRelatedChangesFromChild(const BFFieldId &idFieldId,
                                                      bool isDirty,
                                                const BFDataGroupId &idDataGroup);
   SEVERITY verifyStatusChangesFromDeletion(const BFDataGroupId& idDataGroup);
   SEVERITY validateDeletedChildDistrib( const BFDataGroupId& idDataGroup );
   double getIDUnitPrice ( const BFDataGroupId &idDataGroup);  
   void setLastIDRate(const BFDataGroupId& idDataGroup);   

private:
   void ValidateCurrency(const DString& Currency, const BFDataGroupId& idDataGroup);
   void GetFundCurrency(DString& Currency, const BFDataGroupId& idDataGroup) const;
   bool DistributionPayTypeIsSysCheck( const BFDataGroupId& idDataGroup );

   //implement business rules here
   bool IsRightPayType( const DString& strValue, const BFDataGroupId& idDataGroup ) const;
   bool IsFundToCodeCash( const BFDataGroupId& idDataGroup ) const;
   bool IsRightFundClassTo( const DString& dstrFundCode, 
                            const DString& dstrClassCode, const BFDataGroupId& idDataGroup ) const;
   bool IsValidFundClass( const DString& dstrFundCode, 
                          const DString& dstrClassCode, const BFDataGroupId& idDataGroup ) const;
   bool IsValidFund( const DString& dstrFundCode, const BFDataGroupId& idDataGroup ) const;
   void ValidateBankAcctType( const DString& BankAcctType);
   void ValidateBankAcctNum( const DString& BankAcctNum, const BFDataGroupId& idDataGroup );
   void ValidateTransNo( const DString& TransNo, const BFDataGroupId& idDataGroup );
   void ValidateDistributePercentage( const DString& strValue, const BFDataGroupId& idDataGroup );
   void ValidateBankIdValue ( const DString& dstrBankIdValue, const BFDataGroupId& idDataGroup );

   SEVERITY ValidateFundCode( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY ValidateClassCode( const BFFieldId& idField, const DString& strValue, 
                           const BFDataGroupId& idDataGroup );
   SEVERITY validatePayType( const DString& dstrValue,const BFDataGroupId& idDataGroup );

   SEVERITY validateFromFundClass( const BFDataGroupId &idDataGroup );
   SEVERITY validateToFundClass( const BFDataGroupId &idDataGroup );
   SEVERITY validateToSoftCapCheck(const BFDataGroupId &idDataGroup);
   SEVERITY getFundClassDistribOptionsList(const DString& dstrDistributionType, 
                                           const DString& dstrFundCode, 
                                           const DString& dstrClassCode,
                                           const BFDataGroupId &idDataGroup,
                                           FundClassDistribOptionsList*& pFundClassDistribOptionsList );

   // the following two functions are for C2 fund number stuffs
   SEVERITY setFundClassCode( const BFFieldId& idField,const BFDataGroupId& idDataGroup);
   void setFundNumber( const BFFieldId& idField,const BFDataGroupId& idDataGroup);

   SEVERITY getFundMastList( FundMasterList *&pFundMastList) const;//view 63
   SEVERITY getFundDetailList( FundDetailList *&pFundDetailList) const;//view 56
   SEVERITY validateCash(const BFDataGroupId& idDataGroup);
   SEVERITY isToFundClassAllowed( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY canTradeFundClass( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY allFundsRelatedChanges(const BFDataGroupId&  idDataGroup);
   bool isConsolIDGCOn();

   SEVERITY verifyStatusRelatedChanges (const BFFieldId &idFieldId, 
                                        const BFDataGroupId &idDataGroup);

   SEVERITY ValidateAddrCode( const DString& strValue, 
                              const BFDataGroupId& idDataGroup );
   void getDivChqAddr(DString& strAddrCode, const BFDataGroupId& idDataGroup );

   SEVERITY removeDistributionBankInstructionsList (const BFDataGroupId &idDataGroup);

   AccountDistributionList *_pSplitList;
   DString _dstrAccountNum;
   DString _dstrShareholderNum;
   DISTRIBUTION_LEVEL _level;
   DString dstrBankingFormat;
   MgmtCoOptions *pMgmtCoOptions;
   AddressList *_pAddressList;

protected:
   void SetRequiredField(const BFDataGroupId& idDataGroup);
   SEVERITY setPayTypeDefault(const BFDataGroupId &idDataGroup );
   SEVERITY getTradeDefault ( const BFFieldId &genControlDefaultFieldId, DString &defaultValue, const BFDataGroupId &idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId &idDataGroup, 
                                   long lValidateGroup);
   SEVERITY initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew, bool bReset = false);
   void SetReadOnlyFields( const BFDataGroupId& idDataGroup );
   virtual void doReset( const BFDataGroupId& idDataGroup );
   SEVERITY validatePayEntityBank( const BFDataGroupId& idDataGroup );
   SEVERITY getEntityBankInstruction(BankInstructions *&pBankInstructions,
                                     const DString& payToEntity,
                                     const BFDataGroupId& idDataGroup);
   double AccountDistribution::getUnitPrice ( const DString &fundCode, 
											  const DString &classCode, 
											  const DString &fromDate, 
											  const DString &toDate, 
											  const BFDataGroupId &idDataGroup,
											  const DString tradeTransType, 
											  const DString &prevDatePressed, 
											  const DString &nextDatePressed);    

   BFData *_distributionData;
   FundMasterList *_pFundMasterList;
   FundDetailList *_pFundDetailList;

   MFAccount *_pMFAccount;
   DString strCurrencySubstList,
      _currentBusinessDate;

private:
   bool isBankingAllowed (const BFDataGroupId &idDataGroup);
   bool isEFTCheckAllowed (const BFDataGroupId &idDataGroup) const;
   bool isNSCCCompliant(const BFDataGroupId &idDataGroup, const DString& dstrFundCode = NULL_STRING, const DString& dstrClassCode = NULL_STRING);
   SEVERITY payMethodRelatedChanges(const BFDataGroupId& idDataGroup);
   SEVERITY setCurrencySubstSet (const BFDataGroupId &idDataGroup);
   SEVERITY setPayMethodSubstSet (const BFDataGroupId &idDataGroup);
   SEVERITY fileProcessorRelatedChanges (const BFDataGroupId &idDataGroup, bool forceLoad = false);
   bool hasPayInstructionsForDistribution (const BFDataGroupId &idDataGroup);   
   SEVERITY validateAcctDistribOpt( const DString& dstrValue, const BFDataGroupId &idDataGroup );
   SEVERITY validateAcctDistribCurrencyOpt( const DString& dstrValue, const BFDataGroupId &idDataGroup );
   SEVERITY acctDistribOptRelChanges( const BFDataGroupId &idDataGroup );
   SEVERITY acctDistribCurrencyOptRelChanges( const BFDataGroupId &idDataGroup );
   SEVERITY acctLvlDistrInit( const DString& strAcctDistribOpt, const DString& strAcctDistribCurrOpt, const BFDataGroupId &idDataGroup );
   SEVERITY clearBankingFields( const BFDataGroupId &idDataGroup );
   SEVERITY validateAcctDistribPayType( const BFDataGroupId &idDataGroup );

   DString  _dstrVerifyStatus;
   bool     _bIsDirty;
   bool     _bCanVerify;
   bool     _bVerificationEnabled;
   bool     _bInit;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountDistribution.hpp-arc  $
 * 
 *    Rev 1.57   May 04 2012 10:51:28   if991250
 * CPF - Account Distribution
 * 
 *    Rev 1.56   Mar 03 2010 14:42:30   popescu
 * Incident 2033491 - User is able to select Verified or Unverified when hitting RESET - issue fixed for banking/address and distribution
 * 
 *    Rev 1.55   Feb 08 2010 22:10:30   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one.
 * 
 *    Rev 1.54   Feb 06 2010 17:20:30   dchatcha
 * Restored 1.52
 * 
 *    Rev 1.53   Feb 03 2010 19:04:08   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one.
 * 
 *    Rev 1.52   Jan 15 2010 20:09:22   dchatcha
 * IN# 1975225 - DSK Error when setup Distribution with Broker's unverified bank info.
 * 
 *    Rev 1.51   Jan 11 2010 08:24:18   dchatcha
 * IN# 1964348 - R97_Static Data_Second User cannot verify after making change but reset/cancel.
 * 
 *    Rev 1.50   Jan 11 2010 05:18:04   dchatcha
 * IN# 1964329 - R97_Static Data_Only 01 Address will be verified as static data.
 * 
 *    Rev 1.49   Dec 23 2009 01:41:44   dchatcha
 * IN# 1953647 - R97 Cannot delete distribution option.
 * 
 *    Rev 1.48   Dec 03 2009 03:20:12   dchatcha
 * PET0166583 FN02 FN03 - Static Verification Phase 2.
 * 
 *    Rev 1.47   14 Aug 2009 10:46:06   sibuhatm
 * The BAFF issue is resolved in Account Distribution screen. The Austria and Germany will not display in File processor drop down.
 * 
 * IN1796298 - Unable to select BAFF at dividend screen in Produciton.
 * 
 *    Rev 1.46   23 Feb 2009 15:33:24   kovacsro
 * P0155543_FN01_ Account Level Distribution 
 * 
 *    Rev 1.43   10 Jan 2008 14:35:36   kovacsro
 * IN#1147561 added isConsolidIDGCOn()
 * 
 *    Rev 1.42   24 Dec 2007 09:52:30   kovacsro
 * PET2400FN01R2.0 - added validation when account level bulking is not turned on
 * 
 *    Rev 1.41   21 Dec 2007 14:43:20   kovacsro
 * PET2400FN01 - account level distribution instruction
 * 
 *    Rev 1.40   24 Jul 2007 20:12:50   popescu
 * GAP 20 -22 AIM
 * 
 *    Rev 1.39   Jun 14 2007 12:16:02   porteanm
 * PET 2360 FN48 - GAPS 48 - Cleanup.
 * 
 *    Rev 1.38   Jun 14 2007 12:12:18   porteanm
 * PET 2360 FN48 - GAPS 48 - for BKK.
 * 
 *    Rev 1.37   Feb 14 2007 11:14:02   popescu
 * Incident# 819881 - MFS slowness with the distribution screen
 * 
 *    Rev 1.36   Oct 03 2006 22:25:48   popescu
 * Incident #722094 - raise warn msgs if payment instr missing for either pw or id
 * 
 *    Rev 1.35   Sep 21 2006 17:03:14   popescu
 * STP 2217/13 Acct distribution redirect to broker payment type
 * 
 *    Rev 1.34   Mar 21 2006 16:04:32   ZHANGCEL
 * PET 2132 -- Payment is defaulted to N and no other paytype is allowed for NSCC-Compliant.
 * 
 *    Rev 1.33   Dec 15 2004 16:07:30   Fengyong
 * PTS10036277 - set pay type default value for cash distribution.
 * 
 *    Rev 1.32   Nov 14 2004 14:24:26   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.31   Apr 05 2004 17:29:18   FENGYONG
 * PET944 FN01, release 56.1 NSCC Broker Matrix
 * 
 *    Rev 1.30   Jan 30 2004 15:04:38   popescu
 * PTS 10026408, 
 * Removed hard coding of the file processor for banking, for broker/branch/slsrep, systematic,distribution,trade,shareholder.
 * Set the value of the file processor to NULL_STRING if there are no values from the back-end, 
 * For banking and distributions set the file processor NOT required if there are no values at the back-end
 * 
 *    Rev 1.29   Jan 28 2004 23:03:32   popescu
 * PTS 10026408, in distribution file processor is only required when pay type is 'E' - EFT,
 * BankInstructionsEx.cpp added a stripAll for the copied values
 * 
 *    Rev 1.28   Jan 27 2004 20:04:00   popescu
 * PTS 10026408, CITIBNK is not listed in Drop-down list for File Processor in setting up bank information, by Account - Income Distribution
 * 
 *    Rev 1.27   Oct 04 2003 15:57:06   popescu
 * CIBC PET 809, FN 13;
 * also cleaned-up BankSearch and BankList objects,
 * replaced with FinancialInstitutionList
 * 
 *    Rev 1.26   Aug 07 2003 13:22:10   FENGYONG
 * currency combo fix
 * 
 *    Rev 1.25   Jun 19 2003 17:21:52   FENGYONG
 * PET821_FN17
 * 
 *    Rev 1.24   Jun 01 2003 17:07:34   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.23   Mar 21 2003 17:54:00   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.22   Feb 26 2003 17:18:36   HSUCHIN
 * PTS - 10013814 - bug fix to fundnumber not populating fund/class code and account/fund/class trading check.
 * 
 *    Rev 1.21   Jan 03 2003 18:04:54   WINNIE
 * change to severity to ensure error being promoted properly
 * 
 *    Rev 1.20   Jan 03 2003 10:04:24   WINNIE
 * validation for allowable transfer when reinvest to a different fund
 * 
 *    Rev 1.19   Oct 09 2002 23:53:50   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.18   Aug 29 2002 12:51:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.17   22 May 2002 18:22:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.16   18 Apr 2002 15:27:26   HSUCHIN
 * Added support for Management Fee Rebate Distribution
*/