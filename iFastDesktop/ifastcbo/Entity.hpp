#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1

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
// ^FILE   : Entity.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : Entity
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//

#include <ifastcbo\MFCanCbo.hpp>
#include <boost\utility.hpp>

//Forward declaration
class EntityIdsList;
class AddressEntityList;
class ErrMsgRulesList;
class AcctCutOffTimesList;
class RegDocumentList;
class Demographics;
class WhereUsedList;
class EntityRegDetailsList;
class EntityRegJurisDetailsList;
class EntityRiskList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE Entity : public MFCanBFCbo, private boost::noncopyable
{
public:
   static bool bUsedByEntityAlone;
   Entity (BFAbstractCBO &parent);
   virtual ~Entity ();

   BFAbstractCBO *getTopLevelAncestor ();
   SEVERITY init (const BFData &data);
   SEVERITY init (const DString &strEntityNum);
   SEVERITY init (const DString &entityId, 
                  const BFDataGroupId &idDataGroup);
   SEVERITY getEntityIdsList (EntityIdsList *&pEntityIdsList, 
                              const BFDataGroupId &idDataGroup, 
                              bool inquireDatabase = true);
   SEVERITY getAddressEntityList ( AddressEntityList *&pAddressEntityList, 
                                   const BFDataGroupId &idDataGroup, 
                                   bool inquireDatabase = true);
   SEVERITY getWhereUsedList ( WhereUsedList*& pWhereUsedList, 
                               const BFDataGroupId& idDataGroup, 
                               bool inquireDatabase = true,
                               bool bCreate = true);
   void getEntityId (DString &entityId) const;
   void setFlagsUpdated (const BFDataGroupId &idDataGroup);
   int getEntityAge (const int&basedOn, 
                     const BFDataGroupId &idDataGroup);
   bool getEntityAge ( DString &strYears, 
                       DString &strMths, 
                       const BFDataGroupId &idDataGroup);
   SEVERITY getErrMsg  (DString dstrErrNum, 
                        long lErrConditionId, 
                        long lWarnConditionId, 
                        const BFDataGroupId &idDataGroup, 
                        DString idiStr = NULL_STRING);
   SEVERITY validateNationality (const DString &dstrNationality, 
                                 const BFDataGroupId &idDataGroup);
   SEVERITY validateDateOfBirth (const DString &dstrDateOfBirth, 
                                 const BFDataGroupId &idDataGroup);
   SEVERITY validateOccupation (const DString &dstrOccupationCode, 
                                const BFDataGroupId &idDataGroup);
   SEVERITY getNetworkSenderCutOffTimesList ( AcctCutOffTimesList*& pAcctCutOffTimesList, 
                                              const BFDataGroupId& idDataGroup, 
                                              bool inquireDatabase = true );
   SEVERITY getEntityRiskList(EntityRiskList*& pEntityRiskList, 
                              const BFDataGroupId &idDataGroup, 
                              bool inquireDatabase = true);

   SEVERITY getDemographicsList( Demographics*& pDemographics, 
                                 const BFDataGroupId& idDataGroup, 
                                 bool inquireDatabase = true );

   bool shouldUpdateShareholder(const  BFDataGroupId& idDataGroup );
   bool isAccountRelated( const BFDataGroupId& idDataGroup );
   bool isNetworkSenderEntity (const BFDataGroupId& idDataGroup);
   bool isFundSponsorEntity (const BFDataGroupId& idDataGroup);
   bool isNEQEntity (const BFDataGroupId& idDataGroup);
   bool isDead (const BFDataGroupId& idDataGroup);
   DString getTheRegulatoryStandardComplyRule (const BFDataGroupId& idDataGroup);
   SEVERITY initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew);
   bool hasIDSByType (const DString &strIDCheck, const BFDataGroupId& idDataGroup);

   void saveShareNum (const DString& shrNum)
   {
      _shrNum = shrNum;
   }
   SEVERITY initEUSDRelatedFields (const BFDataGroupId &idDataGroup);
   SEVERITY validateBICCode (const BFDataGroupId& idDataGroup); 
   void setFundSponsorMandatoryFields (const BFDataGroupId& idDataGroup);
   DString getEntityType () {
      return _entityType;
   }
   void setEntityType (const DString& entityType) {
      _entityType = entityType;
   }

   //P0186486_FN01 - IN2738162 Loan Number vs shareholder
   void validateLoanTypeLoanNumberForNotAllowedEntity(const BFDataGroupId& idDataGroup);
   void validateMandatedIDforCPFTaxTypes(const BFDataGroupId& idDataGroup);
   SEVERITY getActOwnerNationalIdAndPassport(DString& dstrNationalID,
                                             DString& dstrPassport,
                                             DString& dstrCOINationalID,
                                             DString& dstrCOIPassport,
                                             const BFDataGroupId& idDataGroup);
   SEVERITY validateAcctRegAgent(DString& dstrAccountNum,
                                 DString& dstrTaxType,
                                 DString& dstrEntityId,
                                 DString& dstrNationalID,
                                 DString& dstrCOINationalID,
                                 DString& dstrPassport,
                                 DString& dstrCOIPassport,
                                 const BFDataGroupId& idDataGroup);
   SEVERITY responseIDRemoved(const BFDataGroupId &idDataGroup);
   void refreshMe (bool bRefresh);
   bool needsRefresh ();
   SEVERITY getGender ( DString &dstrGender, const BFDataGroupId &idDataGroup ); 
   SEVERITY validateGenderForElectedSingleLifeNMCR (const DString &dstrGender, const BFDataGroupId& idDataGroup);
   SEVERITY validateRisk(const BFDataGroupId &idDataGroup); 
   SEVERITY validateGenderAgainstElectResetEvent (const DString &dstrGender, const BFDataGroupId& idDataGroup);
   SEVERITY getEntityRegDetailsList(EntityRegDetailsList *&pEntityRegDetailsList,   
                                    const BFDataGroupId &idDataGroup,
                                    const DString &accountNum = NULL_STRING);
   SEVERITY getEntityRegJurisDetailsList(EntityRegJurisDetailsList *&pEntityRegJurisDetailsList,   
                                         const BFDataGroupId &idDataGroup,
                                         const DString &accountNum = NULL_STRING);
   void setEmployeeClassWithoutValidation(const DString &empClass, const BFDataGroupId &idDataGroup);
   SEVERITY validateEmployeeClassForFATCA(const BFDataGroupId &idDataGroup, const DString &dstrEntityType);
   bool isAccountHolderRiskApplicable( const BFDataGroupId &idDataGroup);
   SEVERITY validationForCRM (const BFDataGroupId &idDataGroup);
   SEVERITY validateTaxJurisForRDSP (const BFDataGroupId& idDataGroup);
   SEVERITY validateRDSPEntity (const BFDataGroupId& idDataGroup);
   SEVERITY validationForEmailPhone (const BFDataGroupId &idDataGroup);

protected:
   virtual SEVERITY doValidateField (const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup);
//support for refresh
   virtual SEVERITY doPreClearFields ();
   virtual SEVERITY reInit ();
   SEVERITY validateBirthAndDeathDate (const BFDataGroupId &idDataGroup);
   void doPopulateField (const BFFieldId &idField, DString  &strValue, bool formattedReturn);
   SEVERITY doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId &idDataGroup);
   SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);

   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   bool checkForDuplicateBICCode (DString bicCode, const BFDataGroupId& idDataGroup);

   SEVERITY doesNEQExists (const BFDataGroupId &idDataGroup);
   SEVERITY validateEmployeeClass (const DString &strValue, const BFDataGroupId &idDataGroup);
   SEVERITY validateTaxJuris (const DString &strValue, const BFDataGroupId &idDataGroup);
   SEVERITY verifyStatusRelatedChanges (const BFFieldId &idFieldId, const BFDataGroupId &idDataGroup);

private:
   SEVERITY setSINToEntity (const BFDataGroupId &idDataGroup);
   void initializeSubstitutionList (const BFFieldId &idField, 
                                    const DString &dstrGroupCode, 
                                    const BFDataGroupId &idDataGroup);
   void getResponseData (BFData *&pResponse);
   void setAllSubstituteValuesBasedonMicInfo (const DString& groupCode,       
                                              const BFFieldId& idField,
                                              const BFDataGroupId& idDataGroup);
   void setAllFieldsReadOnlyforAccountRelated (const BFDataGroupId& idDataGroup);
   bool isPayAgentRelated (const BFDataGroupId& idDataGroup);
   bool isFundBrokerOnly (const BFDataGroupId& idDataGroup);
   void setAllSubstituteValuesForTaxOption(const BFDataGroupId& idDataGroup);
   bool isFieldChanged (const BFFieldId& idField, const BFDataGroupId& idDataGroup);
   SEVERITY validateMandatoryId (const BFDataGroupId& idDataGroup);
   SEVERITY validateAreaOrPhoneNumber (const DString &number, 
                                       const BFDataGroupId& idDataGroup, 
                                       bool isAreaCodeNumber = false) ;
   SEVERITY validateAreaOrPhoneNumber (const BFDataGroupId& idDataGroup);
   SEVERITY validateEntityType (const BFDataGroupId& idDataGroup);
   SEVERITY validateDeathClaimDocStatus (const BFDataGroupId& idDataGroup);
   SEVERITY validateTaxJurisForRESP (const BFDataGroupId& idDataGroup);
   SEVERITY validateTaxJurisEffDateForRESP (const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateGenderForRESP (const DString &strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateTFSAEntity(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateDeceasedAnnuitantTFSA(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateLoanTypeLoanNumber( const BFDataGroupId& idDataGroup );
   SEVERITY validateTIN (const BFDataGroupId& idDataGroup);
   SEVERITY validateRESPAcctHolder(const BFDataGroupId& idDataGroup);
   SEVERITY validatePaternalMaternalNames (const BFDataGroupId& idDataGroup);
   void getAccountNum(DString& accountNum, const BFDataGroupId& idDataGroup);

   DString _entityId, 
           _entityType;
// Please don't use _shrNum
// it only has right value when a new entity is created and it is account related.
   DString _shrNum;
   BFData* _pResponseData;
   ErrMsgRulesList* _pErrMsgRulesList;
   bool   _bRefresh, m_bPaternalMaternal;
   bool     _bIsDirty;
   bool _bVerificationEnabled;
   bool     _bInit;
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Entity.hpp-arc  $
 * 
 *    Rev 1.65   Aug 16 2012 10:52:56   wp040027
 * IN#3008167-P187485-CPF- Account Entity (RA) validation
 * 
 *    Rev 1.64   Jul 12 2012 19:03:32   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
 * 
 *    Rev 1.63   May 28 2012 10:38:28   if991250
 * CPF - Account Entity + Systematics
 * 
 *    Rev 1.62   Apr 04 2012 23:10:06   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.61   Dec 19 2011 04:33:38   panatcha
 * IN2766093 - IWT TIN Warning Message
 * 
 *    Rev 1.60   Nov 30 2011 04:35:50   panatcha
 * IN2738162 Loan Number vs shareholder
 * 
 *    Rev 1.59   Nov 27 2011 22:29:38   popescu
 * 2740236 - TIN Validation
 * 
 *    Rev 1.58   Nov 09 2011 01:54:36   kitticha
 * PETP0186486 FN01 IN2707425 - RRSP Loan Issues - Modify validation for RRSP Loan when delete.
 * 
 *    Rev 1.57   Nov 08 2011 08:12:12   kitticha
 * PETP0186486 FN01 IN2707425 - RRSP Loan Issues.
 * 
 *    Rev 1.56   Oct 13 2011 18:52:18   popescu
 * PETP0186486 FN01 - RRSP Loan Program - fixed a linkage warning
 * 
 *    Rev 1.55   Sep 02 2011 13:05:58   kitticha
 * PETP0186486 FN01 - RRSP Loan Program.
 * 
 *    Rev 1.54   Jul 07 2011 19:00:14   dchatcha
 * P0181953 FN01 - TFSA Amendment.
 * 
 *    Rev 1.53   May 06 2010 23:36:06   popescu
 * RESP/QESI fixes
 * 
 *    Rev 1.52   Apr 30 2010 11:08:42   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.51   Apr 07 2010 09:36:16   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.50   Apr 06 2010 06:28:42   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, move validation logic from account entity cross reference to entity.
 * 
 *    Rev 1.49   Mar 23 2010 13:40:48   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.48   Mar 12 2010 14:57:24   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.47   23 Jan 2009 16:32:20   popescu
 * Incident 	1548019 - reset button on entitymaintenance dlg, BIC Code can be valid/invalid for entitytype 58
 * 
 *    Rev 1.46   16 Jan 2009 17:23:06   popescu
 * Incident 1544134 - various fixes
 * 
 *    Rev 1.45   Jan 08 2009 05:58:04   daechach
 * IN 1545482 - R91-MT535/MT536-users should not be able to create Clearing platform entities.
 * 
 *    Rev 1.44   Dec 15 2008 01:42:54   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.43   Nov 28 2008 14:32:18   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.42   31 Oct 2008 16:18:38   popescu
 * KYC/AML - joint accounts feature
 * 
 *    Rev 1.41   Oct 28 2008 08:32:20   jankovii
 * PET 59888 FN03 AML KYC.
 * 
 *    Rev 1.40   Sep 12 2008 06:47:36   daechach
 * PET0128026 - KYC Phase 2
 * 
*/
