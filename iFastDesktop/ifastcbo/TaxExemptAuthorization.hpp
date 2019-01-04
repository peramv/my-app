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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TaxExemptAuthorization.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 13/07/2004
//
// ^CLASS    : TaxExemptAuthorization
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <srcprag.h>

class BFData;

class MgmtCoOptions;
class MFAccount;
class TaxExemptAuthorizationList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TaxExemptAuthorization : public MFCanBFCbo, private boost::noncopyable
{
public:
   TaxExemptAuthorization (BFAbstractCBO &parent);
   virtual ~TaxExemptAuthorization();
   SEVERITY init (const BFData &data); 
   SEVERITY initNew (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId& idDataGroup);

   /* This is a method used to init Status substitution set. The rule is:
    * There is four substitution set for status:
    * 1. StatusDeath -- Corresponding to StatusDeathSet which only has one item, 
    *    that is "03" -- "Death"
    * 2. StatusActive -- Corresponding to StatusActiveSet which only has one item,
    *    that is "01" -- "Active"
    * 3. StatusActiveDeath -- Corresponding to StatusActiveDeathSet which has two items,
    *    they are "01" and "03"
    * 4. StatusBlank -- Corresponding to StatusBlankSet which has no item in the set list.
    */

   SEVERITY doValidateField( const BFFieldId& idField,
                             const DString& strValue,
                             const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId &idDataGroup);
   void createTaxExemptAuthorizationList (DString &strCodesList, const BFDataGroupId& idDataGroup);

protected:
   virtual void doReset (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
private:
   /** EU Savings Directive **/
   SEVERITY setAcctOwnerEntityList (const BFDataGroupId &idDataGroup);

   SEVERITY commonInit(const BFDataGroupId &idDataGroup);
   SEVERITY relatedChangesForEUSD (const BFDataGroupId& idDataGroup);
	
	double getExemptAmtRemain (const BFDataGroupId& idDataGroup);
	void getDefaultStopDate (DString& dstrInDate, DString& dstrOutDate);
	
   // private member functions
   SEVERITY validateExemptAmtOrig (const DString& strValue, const BFDataGroupId& idDataGroup);
	SEVERITY validateFundCode (const BFDataGroupId &idDataGroup, const DString &dstrFundCode);
	SEVERITY validateClassCode (const BFDataGroupId &idDataGroup, const DString &dstrClassCode);
	SEVERITY validateFundNumber (const BFDataGroupId& idDataGroup);
	SEVERITY validateFundWKN (const BFDataGroupId &idDataGroup, const DString &dstrFundWKN);
	SEVERITY validateFundISIN (const BFDataGroupId &idDataGroup, const DString &dstrFundISIN);
   SEVERITY validateTaxExType (const DString& strValue, const BFDataGroupId& idDataGroup);
	SEVERITY validateJurisFromShrInfo (const BFDataGroupId& idDataGroup);

	SEVERITY setFundByFundNumber(const BFDataGroupId &idDataGroup, const DString &dstrFundNumber);
	SEVERITY setFundByFundClass (const BFDataGroupId &idDataGroup, const DString &dstrFundCode, const DString &dstrClassCode);
	SEVERITY setFundByWKN (const BFDataGroupId &idDataGroup, const DString &dstrFundWKN);
	SEVERITY setFundByISIN (const BFDataGroupId &idDataGroup, const DString &dstrFundISIN);

	// private member data
   DString _eusdParticip,
      _backupWithholdingTax;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxExemptAuthorization.hpp-arc  $
//
//   Rev 1.11   Aug 17 2012 16:42:16   wp040133
//ESS_P01999461_FN01_Distribution Enhancement
//Tax Exempt Authorization Change redesign work.
//Impl code review
//
//   Rev 1.10   Aug 16 2012 19:15:56   wp040133
//ESS_P01999461_FN01_Distribution Enhancement
//Tax Exempt Authorization Change redesign work..Added a new function doApplyRelatedChangesforIDExemptType() to handle the related changes for IDexempt type
//
//   Rev 1.9   Feb 13 2012 18:09:02   wp040100
//P0194640 FN02 - Non-Resident Withholding Tax - Jurisdiction validation changes
//
//   Rev 1.8   Feb 07 2012 22:25:32   wp040100
//P0194640 FN02 - Non-Resident Withholding Tax
//
//   Rev 1.7   Oct 21 2011 09:50:22   kitticha
//PETP0188150 FN01 - Irish Withholding Tax Functionality.
//
//   Rev 1.6   Nov 15 2006 16:57:04   popescu
//Incident# 750524 - track the receipt of W9 forms
//
//   Rev 1.5   Jan 04 2006 16:19:20   jankovii
//Incident #510701- EUSD Exempt Authorization wrong error message
//
//   Rev 1.4   Nov 28 2005 09:44:38   jankovii
//PET1228_FN02_ EU Savings Directive Phase Two
//
//   Rev 1.3   Mar 04 2005 16:33:12   georgeet
//PET1171 FN01 - EU Savings Directive Tax Exemption.  Modified the existing screen to include four new fields with appropriate business logic.
//
//   Rev 1.2   Nov 14 2004 14:56:52   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Sep 20 2004 10:40:06   ZHANGCEL
//PET1082-FNrlc --  New Quebec withholding tax enhancement
//
//   Rev 1.0   Aug 06 2004 17:46:10   ZHANGCEL
//Initial revision.
 * 
 */