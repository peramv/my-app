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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE      : FinancialInstitution.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : October 2003
//
// ^CLASS     : FinancialInstitution
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class FinancialInstitutionList;

class IFASTCBO_LINKAGE FinancialInstitution : public MFCanBFCbo, private boost::noncopyable
{
public:
   //static methods
   /**
    * returns true if financial institution found
    * @param dstrCategory - the category of the financial institution (01 = BANK, 03 = INSTITUTION,..)
    * @param dstrType - the type of the financial institution (01 - ABA, 03 - Canadian, 07- Other)
    * @param nFIIdMaxLength - if financial institution found, it will return the max. length 
    *                      for the InstCode for this financial institution type (dstrType) and category (dstrCategory)
    * @param bIsAllDigits - if financial institution found, it will return if the InstCode should be all 
    *                      digits for this financial institution type (dstrType) and category (dstrCategory)
    * @param nAllFIIdMaxLength - if financial institution found it will return the maximum digits for all InstCode fields,
    *                      for this category (dstrCategory)
    */
   static bool getFICodeNumInfo (
      const DString &dstrCategory, 
      const DString &dstrType, 
      int   &nFIIdMaxLength, 
      bool  &bIsAllDigits, 
      int   &nAllFIIdMaxLength);
   /**
    * Calls the above method for the category FI_CATEGORY::BANK (01)
    */
   static bool getBankIdNumInfo (
      const DString &dstrBankIDType, 
      int   &nBankIdMaxLength, 
      bool  &bIsAllDigits, 
      int   &nAllBankIdMaxLength);
   /**
    * returns true if financial institution found
    * @param dstrCategory - the category of the financial institution (01 = BANK, 03 = INSTITUTION,..)
    * @param dstrType - the type of the financial institution (01 - ABA, 03 - Canadian,.. 07- Other,..)
    * @param nTransitMaxLength - if financial institution found, it will return the max. length 
    *                         for TransitNo for this financial institution type (dstrType) and category (dstrCategory)
    * @param bIsAllDigits - if financial institution found, it will return if the TransitNo should be all 
    *                      digits for this financial institution type (dstrType) and category (dstrCategory)
    * @param nAllTransitMaxLength - if financial institution it will return the maximum digits for all TransitNo fields,
    *                      for this category (dstrCategory)
    */
   static bool getFITransitNumInfo (
      const DString &dstrCategory, 
      const DString &dstrType, 
      int   &nTransitMaxLength, 
      bool  &bIsAllDigits, 
      int   &nAllTransitMaxLength);
   /**
    * Calls the above method for the category FI_CATEGORY::BANK (01)
    */
   static bool getBankTransitNumInfo (
      const DString &dstrType, 
      int   &nTransitMaxLength, 
      bool  &bIsAllDigits, 
      int   &nAllTransitMaxLength);
   /**
    * returns true if financial institution found
    * @param dstrCategory - the category of the financial institution (01 = BANK, 03 = INSTITUTION,..)
    * @param dstrType - the type of the financial institution (01 - ABA, 03 - Canadian,.. 07- Other,..)
    * @param nAccountMaxLength - if financial institution found, it will return the max. length 
    *                         for AcctNum for this financial institution type (dstrType) and category (dstrCategory)
    * @param bIsAllDigits - if financial institution found, it will return if the AcctNum should be all 
    *                      digits for this financial institution type (dstrType) and category (dstrCategory)
    * @param nAllTransitMaxLength - if financial institution it will return the maximum digits for all AcctNum fields,
    *                      for this category (dstrCategory)
    */
   static bool getFIAccNumInfo (
      const DString &dstrCategory, 
      const DString &dstrType, 
      int   &nAccountMaxLength, 
      bool  &bIsAllDigits, 
      int   &nAllAccountMaxLength);
   /**
    * Calls the above method for the category FI_CATEGORY::BANK (01)
    */
   static bool getBankAccNumInfo (
      const DString &dstrBankIDType, 
      int   &nAccountMaxLength, 
      bool  &bIsAllDigits, 
      int   &nAllAccountMaxLength);
   /**
    * Checks whether the code passed is valid
    * returns a SEVERITY
    * @param dstrCategory - the category of the financial institution (01, 02,...)
    * @param dstrType - the type of the financial institution (01 - ABA, 03 - Canadian,.. 07- Other,..)
    * @param dstrCode - the code of the financial institution
    */
   static SEVERITY validateFICode (
      const DString &dstrCategory,
      const DString &dstrType,
      const DString &dstrCode);
   /**
    * Checks whether the bank code passed is valid, calls the above method
    */
   static SEVERITY validateBankCode (DSTCWorkSession &workSession,
      const DString &dstrType,
      const DString &dstrCode);
   /**
    * Checks whether the transit num passed is valid
    * returns a SEVERITY
    * @param dstrCategory - the category of the financial institution (01, 02,...)
    * @param dstrType - the type of the financial institution (01 - ABA, 03 - Canadian,.. 07- Other,..)
    * @param dstrTransitNo - the transit number of a transit
    * @param idDataGroup - the data group
    */
   static SEVERITY validateFITransitNum (
      const DString &dstrCategory,
      const DString &dstrType, 
      const DString &dstrTransitNo);
   /**
    * Checks whether the bank transit num passed is valid, calls the above method
    */
   static SEVERITY validateBankTransitNum (DSTCWorkSession &workSession,
      const DString &dstrType, 
      const DString &dstrCode, 
      const DString &dstrTransitNo);
   /* Check bank id value has correct formatted. */
   static bool validatePreformatted(const DString &dstrType,
									const DString &dstrBankIdValue);
   /* Check bank acount num has correct formatted. */
   static bool validateAcctNbrformatted(const DString &dstrType,
										const DString &dstrCurrency,
										const DString &dstrBankAcctValue);
   /**
    * Checks whether the financial institution has transits
    */
   static bool hasTransits (
      const DString &dstrCategory, 
      const DString &dstrType);
   /**
    * Checks whether the category represent an institution
    */
   static bool institution (
      const DString &dstrCategory);
   /**
    * Checks whether the category represent a transit
    */
   static bool transit (
      const DString &dstrCategory);
   /**
    * Returns the parent category of the given one
    */
   static DString getParentCategory (const DString &category);
   //Constructor
   FinancialInstitution (BFAbstractCBO &parent);
   //Destructor
   virtual ~FinancialInstitution ();

   SEVERITY init (
      const DString &initCategory, 
      const DString &initType, 
      const BFDataGroupId& idDataGroup);
   SEVERITY init (const BFData &viewData);
protected:
   SEVERITY doValidateField (const BFFieldId& idField, 
      const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY doApplyRelatedChanges (const BFFieldId& idField, 
      const BFDataGroupId& idDataGroup);
   void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
private:
   SEVERITY commonInit (const BFDataGroupId &idDataGroup);
   SEVERITY assignInstCodeLabel (const BFDataGroupId &idDataGroup);
   DString _initCategory,
      _initType;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FinancialInstitution.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:40:50   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Oct 27 2003 19:48:38   popescu
//CIBC PET809, FN 13, added Transit Search by name
//
//   Rev 1.1   Oct 24 2003 17:19:36   popescu
//CIBC PET 809, FN 13
//
//   Rev 1.0   Oct 04 2003 16:08:42   popescu
//Initial revision.
 */