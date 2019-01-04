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
// ^FILE   : ContactInfo.hpp
// ^AUTHOR : Chin Hsu
// ^DATE   : 29/02/2000
//
// ^CLASS    : ContactInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <srcprag.h>

class BFData;

class MasterContractList;
class MgmtCoOptions;
class TaxTypeRuleList;
class EntityIdsList;   
class ContractInfoList;
class MFAccount;
class MFAccountHoldingList;
class AgentList;
class CotLegalAge;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ContractInfo : public MFCanBFCbo, private boost::noncopyable
{  
public:
   ContractInfo( BFAbstractCBO &parent );
   virtual ~ContractInfo();
   SEVERITY init( const BFData& data ); 

   void init2( ContractInfoList *pContractInfoList, const BFDataGroupId& idDataGroup);

   void SetFieldProperties( const BFDataGroupId& idDataGroup, bool bReadOnly = true);

   virtual void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);

   SEVERITY getAcctCreationDate(DString& strValue, const BFDataGroupId& idDataGroup, bool bFormatted);
   SEVERITY getMasterMinTermAndMinMaxAge( DString& dstrMinTerm, DString& dstrMinAge, 
                                          DString& dstrMaxAge, const BFDataGroupId& idDataGroup );

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
   SEVERITY initStatusSubst( const BFDataGroupId& idDataGroup );

   /* This is a method used to copy a new record when user hit the AddCopy button
    * @param Mode -- Original record
    *
    */
   void ModelOffer(ContractInfo *Model, const BFDataGroupId& idDataGroup);

   SEVERITY doValidateField( const BFFieldId& idField,
                             const DString& strValue,
                             const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY loadContractTypeSubstitutionList( const BFDataGroupId& idDataGroup );
   void createContractTypesList( DString &strCodesList, const BFDataGroupId& idDataGroup );
   bool isGWOContract( const BFDataGroupId& idDataGroup );
   bool isNewContract( const BFDataGroupId& idDataGroup );
   SEVERITY getMasterContract(BFAbstractCBO*& _pMasterContract, const BFDataGroupId& idDataGroup);
   bool CompareTwinContracts(const ContractInfo* pCompareTo, const BFDataGroupId& idDataGroup);
   SEVERITY updateContractMatBasedOnSubst(const BFDataGroupId& idDataGroup, bool hasLinkedContractWithIssueDate = false);
   SEVERITY getContractTypeAndVersion ( DString &dstrContractType, DString &dstrContractVer, const BFDataGroupId &idDataGroup );
   SEVERITY getNMCRContract ( DString &dstrNMCRContract, const BFDataGroupId &idDataGroup );
   bool isSingleLifeNMCR (const BFDataGroupId& idDataGroup);
   bool isElectedSingleLifeNMCR (const BFDataGroupId& idDataGroup);
   bool hasSingleLifeNMCRMaster (const BFDataGroupId& idDataGroup);
   bool validateAnnuitantGender (const BFDataGroupId& idDataGroup, DString &dstrGender);

protected:
   SEVERITY ValidateTaxTypeAndTaxJurisdiction( const BFDataGroupId& idDataGroup );
   // private member functions
   bool ValidateLegalMaturityDate( const DString& LegalMaturityDate, const BFDataGroupId& idDataGroup );
   SEVERITY ValidateEffectiveDate( const DString& EffectiveDateContract, const BFDataGroupId& idDataGroup );
   SEVERITY ValidateStopDate( const DString& StopDate, const BFDataGroupId& idDataGroup );
   SEVERITY ValidateStatus( const DString& Status, const BFDataGroupId& idDataGroup);
   SEVERITY ValidateContractTerm( const DString& ContractTerm, const BFDataGroupId& idDataGroup );
   SEVERITY ValidateProvince( const DString& Province, const BFDataGroupId& idDataGroup );
//   SEVERITY ValidateMaturityType( const DString& MaturityType );
   //SEVERITY ValidateUserMaturityDate( const DString& UserMaturityDate, const BFDataGroupId& idDataGroup );
   SEVERITY ValidateContractType( const DString& valContractType, const BFDataGroupId& idDataGroup);
   SEVERITY ValidateContractEffectiveDate( const BFDataGroupId& idDataGroup );
	SEVERITY loadProvinceSubstitutionList( const BFDataGroupId& idDataGroup );

	bool getDofBirth( const BFDataGroupId& idDataGroup, DString &dstrDofBirth );
	virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	SEVERITY ValidateOldestLegalDate( DString &dsDofBirth, const BFDataGroupId& idDataGroup );
   SEVERITY initCMDBasedON(const BFDataGroupId& idDataGroup);
   SEVERITY loadAgeBasedOnSubstitutionList( const BFDataGroupId& idDataGroup );
   SEVERITY defaultReadonlyFields( const BFDataGroupId& idDataGroup );
   SEVERITY contractMaturityDateRelatedChanges(const BFDataGroupId& idDataGroup);
   SEVERITY getMasterContractList(MasterContractList*& _pMasterContractList, const BFDataGroupId& idDataGroup);
   SEVERITY contractTypeRelatedChanges(const BFDataGroupId& idDataGroup);
   SEVERITY cdStartDateRelatedChanges(const BFDataGroupId& idDataGroup);

   SEVERITY ValidateUserDefinedMaturityDateBetweenMinMaxAge(const BFDataGroupId& idDataGroup );
   SEVERITY ValidateUserDefinedMaturityDateGreaterThanMinTerm(const BFDataGroupId& idDataGroup );
   SEVERITY ValidateUserDefinedMaturityDateLessThanMaturityDate(const BFDataGroupId& idDataGroup );

private:
//   DString getDescription( const DString& strCode, const DString& strAllSubstList );
   SEVERITY getAgentList( const BFDataGroupId& idDataGroup, AgentList *&pAgentList);
   SEVERITY getCotLegalAge( CotLegalAge *&pCotLegalAge, const BFDataGroupId& idDataGroup, bool inquireDatabase = true );
   /*
   * This function will be only called by CheckDofBirth. The reason is that the program
   * does BailMaturityDate and LegalMaturityDate calculation only when the DofBirth is valid. 
   */
   void SetDefaultValues( DString &DofBirth, const BFDataGroupId& idDataGroup);
   void setLegalAge( const BFDataGroupId& idDataGroup );

   void addYearToDate( DString& dstrInDate, DString& dstrOutDate, int numYear );

   /* Perform the function only when the program get valid DofBirth
    * @param dsDofBirth - a parameter that get from Entity and is not a NULL_STRING
    * returns - Using dsDofBirth to calculate OldestLegalDate and check it. If it is in 
    *           the past, returns false, otherwise returns true.
    */
//   bool CheckOldestLegalDate( DString &dsDofBirth, const BFDataGroupId& idDataGroup, bool &bWrongTaxType );

   /* This is a method used to calculate BailMaturityDate and LeaglMaturityDate
    * @param dstrDofBirth - a parameter that passed from ContractProcess. It
    *        is a field of EntityIds(DSTC0051_VW.hpp). Actually it is the birth day of
    *        an Annuitant ( EntityType_50 = '05' with EntityTypeSeq=1) or an Owner
             ( EntityType_50='01' with EntityTypeSeq=1)
    * @param iInputAge - When bIsBailOutAge is true, it should be BailOutAge#-87,
    *        otherwise, it should be CriticalAge#-87
    * @param bIsBailOutAge - When BailMaturityDate is going to be calculated,
    *        it should be true.
    *        When LeaglMaturityDate is going to be calculated, it should be false.
    * @dstrOutDate - The result of calculation.
    * @returns - if dstrDofBirth == NULL_STRING or year=0, returns false, 
    *        Otherwise, returns true.
    */
   bool CalcBailOrLeaglDate(DString& dstrDofBirth, int iInputAge,
                            bool bIsBailOutAge, DString& dstrOutDate);

   // private member data
   ContractInfoList     *_pList;
   MgmtCoOptions        *_pMgmtCoOptions;
   TaxTypeRuleList      *_pTaxTypeRuleList;
   MasterContractList   *_pMasterContractList;
   MFAccount            *_pMFAccount;
   MFAccountHoldingList *_pAccountHoldingList;
   DString              _dstrAcctNum;
   DString              _dstrLegalMaturityDate;
   bool bDefaultValuesAlreadySet;
   bool _bMultiContract;

   DString _dstr12319999;
   bool _bGuaranteeCalcByRules;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ContractInfo.hpp-arc  $
 * 
 *    Rev 1.41   May 25 2012 19:13:26   if991250
 * IN#2938847 Contract Information - User defined Maturity Date validation
 * 
 *    Rev 1.40   Apr 20 2012 13:30:56   if991250
 * IN 2921758 filtering the CMD based on function of MinAge
 * 
 *    Rev 1.39   Apr 10 2012 16:20:18   if991250
 * IN 2900207 Contract Information
 * 
 *    Rev 1.38   Mar 27 2012 16:50:42   if991250
 * IN 2858958 - Contract info
 * 
 *    Rev 1.37   Mar 15 2012 16:27:56   jankovii
 * IN 2845942 - Closing Period Term
 * 
 *    Rev 1.36   Feb 15 2012 17:35:16   dchatcha
 * IN# 2848252 - P0186484 FN02 Seg Desktop - Contract Info Screen issues for non-IA
 * 
 *    Rev 1.35   Jan 21 2012 08:56:36   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.34   Jan 17 2012 17:43:18   dchatcha
 * IN# 2799812 - Contract Screen issues. Fix crashing during load contract infromation screen. 
 * 
 *    Rev 1.33   Jan 16 2012 21:58:22   dchatcha
 * IN# 2799812 - Contract Screen issues, build error.
 * 
 *    Rev 1.32   Jan 16 2012 20:08:30   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.31   Dec 27 2011 00:53:32   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 */
