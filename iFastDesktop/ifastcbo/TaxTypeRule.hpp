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
// ^FILE   : TaxTypeRule.hpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : May 18,2000
//
// ^CLASS    : TaxTypeRule
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class RedCodeByTaxTypeList;
class TaxJurisLimitList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TaxTypeRule : public MFCanBFCbo, private boost::noncopyable
{
public:

   TaxTypeRule( BFAbstractCBO &parent );
   virtual ~TaxTypeRule();
   SEVERITY init( const BFDataGroupId& idDataGroup );
   SEVERITY init( const BFData &viewData );

   bool validTransfer( const DString& dstrTaxTypeIn, const BFDataGroupId& idDataGroup );
   void getDepTypeList( RedCodeByTaxTypeList *&pDepTypeList, const BFDataGroupId& idDataGroup );
   void getRedCodeList( RedCodeByTaxTypeList *&pRedCodeList, const BFDataGroupId& idDataGroup );   
   bool validAcctType( const DString& accountType, const BFDataGroupId& idDataGroup );
   bool validAcctDesignation ( const DString& dstrAcctDesignation, const BFDataGroupId& idDataGroup );
   bool isValidDepCode(const DString& dstrDepCode );
   bool isValidRedCode(const DString& dstrRedCode );

   bool doesTaxJurisdictionLimitationListExist(const BFDataGroupId& idDataGroup);
   bool isValidAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );
   bool isValidMinimumAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );
   bool isValidMaximumAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );
   bool isValidPensionJurisdiction( const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );
   bool getAgeCalcBasedOn(int& ageCalcBasedOn, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );

//******************************************************************************
// Method to return the value of the idField requested based on the jurisdiction
// passed in from the TaxJurisLimitList CBO.
// @param   const BFFieldId& idField - Field Id request
//          const DString& dstrJurisdiction - Jurisdiction used.
//          const BFDataGroupId& idDataGroup - datagroup id.
// @return  DString - value of field Id based on the Jurisdiction.
//******************************************************************************
   DString getJurisLimitField( const BFFieldId& idField, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup, bool blFormatted = false );

   /**
    * This method returns a bool indicating whether the age (dstrAge) passed in
    * is a valid Minimum withdraw age.  The age (dstrAge) has to be greater than
    * the minimum withdraw age store in the TaxJurisLimitList CBO based on the
    * 
    * @param dstrAge Age to check
    * @param dstrJurisdiction
    *                Jurisidiction to check in
    * @param idDataGroup
    *                Datagroup id
    * 
    * @return true if dstrAge is greater than min withdraw age for the jurisdiction.
    *         false otherwise
    */
   bool isValidMinimumAgeForWithdrawl( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );

   bool isCarryForwardUnusedMaxApplic( const DString& dstrJurisdiction, 
								       const BFDataGroupId& idDataGroup );
   bool canUseSpousesAge( const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );
   SEVERITY isTaxTypeSchedule01Exist( bool &bApplicable, const DString& dstrPensionJuris, 
	   const BFDataGroupId& idDataGroup );
   bool getCheckEligibleAge(const BFDataGroupId& idDataGroup);

private:
   mutable BFCritSec csDepTypeList_;
   mutable BFCritSec csRedCodeList_;
   mutable BFCritSec csTaxJurisLimitList_;

   TaxJurisLimitList *m_pTaxJurisLimitList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxTypeRule.hpp-arc  $
// 
//    Rev 1.30   Feb 20 2009 14:34:20   jankovii
// IN  1557042 - Accountholder less than 55 but no warning on Desktop and a/c created
// 
//    Rev 1.29   Nov 28 2008 13:45:38   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.28   06 Oct 2008 13:20:06   kovacsro
// PET142007  FN01 TFSA
// 
//    Rev 1.27   12 Sep 2008 15:41:20   kovacsro
// PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
// 
//    Rev 1.26   01 May 2008 13:57:56   kovacsro
// PET2255 FN47 - New Ontario LIF - finalized
// 
//    Rev 1.25   Aug 10 2007 17:07:16   smithdav
// PET2360 FN76,91
// 
//    Rev 1.24   Sep 07 2006 16:53:22   porteanm
// PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt. 
// 
//    Rev 1.23   Nov 14 2004 14:57:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.22   Feb 20 2004 09:23:44   PURDYECH
// PET 910 - Previous checkin was of incorrect file.
// 
//    Rev 1.21   Feb 19 2004 14:15:06   PURDYECH
// Fixed some multithreading issues.
// 
//    Rev 1.20   Mar 21 2003 18:26:18   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.19   Oct 09 2002 23:55:06   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.18   Aug 29 2002 12:53:50   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.17   Jul 09 2002 10:23:06   HSUCHIN
// added getJurisLimitField and isValidMinimumAgeForWithdrawl to get Field values from TaxJurisLimitList based on jurisdiction and check for valid min age for withdrawl based on jurisdiction.
// 
//    Rev 1.16   08 Jun 2002 18:22:08   HERNANDO
// Added functions to validate Tax Jurisdiction and Age.
// 
//    Rev 1.15   22 May 2002 18:19:16   PURDYECH
// BFData Implementation
// 
//    Rev 1.14   19 Mar 2002 13:18:54   PURDYECH
// Use #pragma once as include guard
// Remove compile time "including..." message
// 
//    Rev 1.13   25 Feb 2002 11:58:04   KOVACSRO
// Added isValidDepCode and isValidRedCode  methods.
// 
//    Rev 1.12   11 May 2001 10:34:16   HSUCHIN
// Sync up with SSB (1.10.1.0)
// 
//    Rev 1.11   03 May 2001 14:05:02   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.10   Feb 19 2001 15:25:32   ZHANGCEL
// Changed the parameter name in validTransfer().
// 
//    Rev 1.9   Nov 30 2000 10:58:54   WINNIE
// new method to validate against acct designation
// 
//    Rev 1.8   Nov 17 2000 13:26:50   WINNIE
// uncomment out methods
// 
//    Rev 1.7   Nov 16 2000 10:48:54   DINACORN
// Create the substitution lists for RedCode and DepositType which get the description from DataDictionary, not from view
// 
//    Rev 1.6   Nov 02 2000 14:11:30   VASILEAD
// Added workSeesionId parameter for Mgmtco based CBOs
// 
//    Rev 1.5   Oct 18 2000 15:34:42   DINACORN
// Added getAcctTypeSubstList and getAccountTypeDescription methods
// 
//    Rev 1.4   Aug 08 2000 14:21:00   WINNIE
// Add business rule to validate account type based on the tax type of the account
// 
//    Rev 1.3   May 29 2000 14:45:58   BUZILA
// pDepositTypeList and pRedemptionCodeList taken out 
// 
//    Rev 1.2   May 25 2000 15:35:06   WINNIE
// add getsessionId
// 
//    Rev 1.1   May 24 2000 16:51:06   WINNIE
// Add method to get valid redemption code and deposit type
// 
//    Rev 1.0   May 18 2000 16:43:32   WINNIE
// Initial revision.
*/