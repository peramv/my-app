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
//    Copyright 1997 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : Address.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : October, 99
//
// ^CLASS    : Address
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class AccountMailingList;
class MgmtCoOptions;
class AddressList;
class NomineeInterAddr;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE Address : public MFCanBFCbo
{
public :
   static SEVERITY buildAddressLine1 (
      DSTCWorkSession &rpDSTCWorkSession,
      const DString &accontNum,
      DString& adressLine1, 
      const BFDataGroupId &idDataGroup);
public:
   Address (BFAbstractCBO &parent);
   virtual ~Address();

   SEVERITY init (
            const DString &shrNum, 
            const BFDataGroupId &idDataGroup);
   SEVERITY init (
            const DString &shrNum, 
            const BFData &data, 
            const BFData &kanaData);
   SEVERITY init (
            const DString &shrNum, 
            const BFData& data);
   void setObjectUpdated (
            const BFDataGroupId &idDataGroup);
   SEVERITY refreshFields( const BFFieldId fieldsArray[], 
                           int numFields, 
                           const BFDataGroupId& idDataGroup );
   SEVERITY getFormattedAddress(DString& dstrAddress, const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doValidateField (
            const BFFieldId &idField, 
            const DString &strValue, 
            const BFDataGroupId &idDataGroup);
   virtual SEVERITY doPreSetField (
            const BFFieldId &idField, 
            DString &strValue, 
            const BFDataGroupId &idDataGroup, 
            bool bFormatted);
   virtual SEVERITY doApplyRelatedChanges (
            const BFFieldId &idField, 
            const BFDataGroupId &idDataGroup);
   virtual SEVERITY doPreValidateAll (
            const BFDataGroupId& idDataGroup);
   virtual void doInitWithDefaultValues (
            const BFDataGroupId& idDataGroup);
   virtual SEVERITY doValidateAll( const BFDataGroupId &idDataGroup, 
                                  long lValidateGroup);

   SEVERITY verifyStatusRelatedChanges (const BFFieldId &idFieldId, 
                                        const BFDataGroupId &idDataGroup);

private:   
   SEVERITY commonInit (
            const DString &shrNum,
            const BFDataGroupId &idDataGroup);
   SEVERITY getAccountDesignation (
            DString &strAcctDes, 
            const BFDataGroupId& idDataGroup);
   bool isClient (
            const BFDataGroupId &idDataGroup);
   bool isNominee (
            const BFDataGroupId &idDataGroup);
   bool isIntermediary (
            const BFDataGroupId &idDataGroup);
   SEVERITY getNomineeInterAddress (
            NomineeInterAddr *&pNomineeInterAddr,
            const BFDataGroupId &idDataGroup);
   bool refreshNomineeInterAddress(
            const BFDataGroupId &idDataGroup);

//validation routines
   SEVERITY validateRegAddressCode (
            const BFDataGroupId &idDataGroup);
   SEVERITY validateEffectiveStopDate (
            const DString &strValue, 
            const BFDataGroupId& idDataGroup);
   SEVERITY validateCountryCode (
            const DString &strValue, 
            const BFDataGroupId &idDataGroup);
   bool validatePostalCode (
         const DString &strValue, 
         const BFDataGroupId &idDataGroup, 
         bool bAddCondition = true);
   SEVERITY validateRetMailFlag (
         const DString &strValue, 
         const BFDataGroupId& idDataGroup);
   void validateAddrLine (
         const BFFieldId &idField,
         DString strLine,
         const BFDataGroupId &idDataGroup);
   void validateAddrKanaLine (
         const BFFieldId &idField, 
         DString strLine,
         const BFDataGroupId& idDataGroup);
   SEVERITY validateCountryProvinceUSA(const BFDataGroupId& idDataGroup);
//helper methods
   void setFieldsReadOnly (
            const BFDataGroupId &idDataGroup, 
            bool bReadOnly);
   bool isDigit( const I_CHAR val );
   bool isValidFirstDigit( const I_CHAR val );
   bool isValidThirdFifthDigit( const I_CHAR val );
   int getAddressLines (
            const BFFieldId &idField, 
            DString strLine,
            const BFDataGroupId &idDataGroup,
            bool bKana = false);

   bool IsAddrCodeDuplicated(const DString& strAddrCode, const BFDataGroupId& idDataGroup);
   void RefreshMailingReturnField(const DString& strAddrCode, const BFDataGroupId& idDataGroup);
   bool IsAddrCodeFirstTimeSetup(const DString& strAddrCode, const BFDataGroupId& idDataGroup);
   bool isValidPostalCodeValue(I_CHAR* code,I_CHAR* cVal);
   void getCountryCodeByPost(DString& countryCode, const DString& strPostCode);

   void addAdrressEmptyCondition(DString strLine);
   void setPostalCodeFieldValue(DString &strValue, const BFDataGroupId& idDataGroup);
   bool determineCountryCode(DString &strCountry, const DString& strPostalCode, const BFDataGroupId& idDataGroup);
   SEVERITY setReturnedMailFields( const BFDataGroupId& idDataGroup );
   bool isRegisterAddressUpdateable(const BFDataGroupId& idDataGroup);

   SEVERITY setProvinceSubstSet(const BFDataGroupId& idDataGroup);

   bool checkUpdatePermissionForRetmailRelated( const BFDataGroupId & idDataGroup  );
   SEVERITY doResidencyCheck( const DString& dstrAddrCode, const DString& dstrCountryCode, const BFDataGroupId& idDataGroup );
   SEVERITY doCountryCodeRelatedChanges( const BFDataGroupId& idDataGroup);
   SEVERITY initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew);

   bool isBeneficiaryOwnerAddr (const BFDataGroupId &idDataGroup);
   SEVERITY updateMailingInfoByRetmailForAddrCode(const BFDataGroupId &idDataGroup);


private:   
   bool     _blRetMail;
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Address.hpp-arc  $
 * 
 *    Rev 1.36   Jan 25 2010 10:49:56   dchatcha
 * IN# 1983880 - Rel 97 Static Data - Status of Nom (01 Reg address) is set to Unverified.
 * 
 *    Rev 1.35   Dec 03 2009 03:04:12   dchatcha
 * PET0166583 FN02 FN03 - Static Verification Phase 2.
 * 
 *    Rev 1.34   Jun 09 2009 05:29:34   kitticha
 * PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
 * 
 *    Rev 1.33   29 Oct 2008 13:28:28   kovacsro
 * PET5517 FN71 Unclaimed property - added  doCountryCodeRelatedChanges
 * 
 *    Rev 1.32   29 Oct 2008 13:06:34   kovacsro
 * IN#1461514 - TFSA- chg addr to Non-Res with active pac
 * 
 *    Rev 1.31   Sep 22 2008 08:45:58   wongsakw
 * PET5517 FN71 Unclaimed Property
 * 
 *    Rev 1.30   06 Nov 2007 13:46:08   kovacsro
 * IN#1057338 - province CanadaUS substitution set read from view 252 now, rather than the DD
 * 
 *    Rev 1.29   Jul 28 2006 10:42:54   fengyong
 * Incident #672869 - Ret mail flag refresh
 * 
 *    Rev 1.28   Nov 08 2004 11:31:18   PURDYECH
 * PET910 - Correct parameters for Address::isValidFirstDigit(), Address::isValidPostalCodeValue(), and Address::isValidThirdFifthDigit().
 * 
 *    Rev 1.27   Oct 04 2004 14:28:38   YINGBAOL
 * PET1145 Fn01: Sync. up version 1.23.1.0
 * 
 *    Rev 1.26   Jun 01 2004 12:06:50   popescu
 * PTS 10026900, constructed the correct line 1 of the address for Nominee/Intermediary accounts
 * 
 *    Rev 1.25   May 25 2004 20:32:10   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.24   May 20 2004 14:16:54   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 */
