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
// ^FILE   : AccountEntityXrefObject.hpp
// ^AUTHOR : Adrian + Serban
// ^DATE   : 
//
// ^CLASS    : AccountEntityXrefObject
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class EntityAddressMailingList;
class ErrMsgRulesList;
class RESPInfoUpdateValidationList; //QESI3FN03
class RESPInfoUpdateValidation; //QESI3FN03

struct _entityIDSeqOrder;

class IFASTCBO_LINKAGE AccountEntityXrefObject : public MFCanBFCbo
{
public:
   AccountEntityXrefObject( BFAbstractCBO &parent );
   virtual ~AccountEntityXrefObject();

   SEVERITY init( const DString& strKey, const BFData& data, bool flg_where_used,bool bRefresh =false, bool baseDelete = false );
   SEVERITY init( const BFDataGroupId& idDataGroup  ); //init for new objects

   const DString * getInitialStrKey();
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   void setInitialStrKey( const DString& strKey );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ); 
   void setFlagsUpdated( const BFDataGroupId& idDataGroup );
   bool isEntityEffective ( const DString& dstrDate, const BFDataGroupId& idDataGroup );

   SEVERITY getEntityMailingList( EntityAddressMailingList *&pEntityAddressMailingList, 
                                  const BFDataGroupId& idDataGroup, bool inquireDatabase = true ); 



   SEVERITY validateEntityTypeDofB( const BFDataGroupId& idDataGroup );
   bool acctOwnerAgeEligibleForTFSA(const BFDataGroupId& idDataGroup);

   void ModelOffer(AccountEntityXrefObject *Model, DString strSeqNum, const BFDataGroupId& idDataGroup);  // for entity copy
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

   void getField( const BFFieldId& idField, 
                  DString & strValue, 
                  const BFDataGroupId& idDataGroup, 
                  bool formattedReturn = false ) const;

   SEVERITY PopulateWhereUsedForAccount( const BFDataGroupId& idDataGroup,
                                         const DString& dstrTrack = I_("N"),
                                         const DString& dstrPageName = NULL_STRING );
   virtual SEVERITY setField( const BFFieldId& idField, const DString& dstrValue, const BFDataGroupId& idDataGroup, 
                              bool bFormatted = true, bool bSideEffect = false, bool  bCheckCurrentValue = true);
   SEVERITY getErrMsg( DString   dstrErrNum,       long lErrConditionId, 
                       long      lWarnConditionId, const BFDataGroupId& idDataGroup,   DString idiStr = NULL_STRING );

   void SetSpousalEntityNameSubSet( const BFDataGroupId& idDataGroup, DString SpousalNameSubSet, DString FSpouseEntity, bool setdefault = false );
   void setCountNum( int iCount )
   {
      _iCountNum = iCount;
   }

   SEVERITY setFieldSubSetForRESPEntity(const DString& strEntityType,
                                        const DString& strSubset,
                                        const BFDataGroupId& idDataGroup );
   SEVERITY setLetterRequired(const BFDataGroupId& idDataGroup);
   SEVERITY validateRESPBenefAlloc(const BFDataGroupId& idDataGroup );

   bool isLinkedToRESPBenef(const DString& strEntityId,const BFDataGroupId& idDataGroup);
   SEVERITY initSubstitutionsRelateCodeForRESP(const BFDataGroupId& idDataGroup);
   SEVERITY resetSubstitutionsRelateCodeForRESP(const BFDataGroupId& idDataGroup);
   SEVERITY refreshSelectableListForRESP(const DString& strEntityType,
                                         const BFDataGroupId& idDataGroup );
   SEVERITY validateDofBirthAgainstSINIdDateForRESPBenf(const BFDataGroupId& idDataGroup);
	//IN2780013 - SOC Loan Number and Loan Type
   SEVERITY validateDuplicatedLoanTypeForEscrow ( const BFDataGroupId& idDataGroup);
   bool isDuplicateLoanTypeForEscrow ( const AccountEntityXrefObject *pAEXToCheck,
                                       const BFDataGroupId& idDataGroup);
   SEVERITY validateEntityRegistrationAgentType(const DString& dstrTaxType, const BFDataGroupId& idDataGroup );
   SEVERITY updateAssociateEntity(const DString &subList, const BFDataGroupId &idDataGroup);
   SEVERITY validateAcctSAGESBalance(const BFDataGroupId &idDataGroup);
   SEVERITY validateAcctBCTESGBalance(const BFDataGroupId &idDataGroup);
   SEVERITY validateAcctGrantBalance(const BFDataGroupId &idDataGroup, const DString &dstrValidateType);
   SEVERITY updateVerifyStatFlag(const BFDataGroupId &idDataGroup);
   SEVERITY validateTaxJurisForRDSP( const BFDataGroupId& idDataGroup );
   SEVERITY validateRDSPBeneDateOfBirth (const DString& dstrDateOfBirth, const BFDataGroupId& idDataGroup);
   SEVERITY loadRDSPRelntoBeneSetSubstList(const BFDataGroupId& idDataGroup, const DString& dstrTaxType);

protected:
   virtual void doReset( const BFDataGroupId& idDataGroup );
   void doPopulateField( const BFFieldId& idField, DString & strValue, bool formattedReturn );
   void updateRegistrationAgentSubstitution(const BFDataGroupId& idDataGroup, const DString& dstrTaxType = I_(""));
   SEVERITY getRAEntityValidTaxType(const DString& dstrEntityId, 
                                    DString& dstrValidTaxType, 
                                    const BFDataGroupId& idDataGroup,
                                    const DString& dstrTrack,
                                    const DString& dstrPageName );
   SEVERITY validateEntityTypeAgainstElectResetEvent(const BFDataGroupId& idDataGroup);
   SEVERITY verifyStatusRelatedChanges (const BFFieldId &idFieldId, const BFDataGroupId &idDataGroup);

private:
   void initDefaultValues(const BFDataGroupId& idDataGroup, const DString& taxType);
   AccountEntityXrefObject( const AccountEntityXrefObject &rhs );
   AccountEntityXrefObject& operator=( const AccountEntityXrefObject &rhs );
   void setFundNumber( const BFFieldId& idField,const BFDataGroupId& idDataGroup);
   void setFundClassCode( const BFFieldId& idField,const BFDataGroupId& idDataGroup);
   void validateFundClass(const BFDataGroupId& idDataGroup, DString strEscrowFund = NULL_STRING, 
                          DString strEscrowClass = NULL_STRING);
   void validateReasonCode(const DString& dstrReason,const BFDataGroupId& idDataGroup);
   void validateAmountType(const DString& strValue,const BFDataGroupId& idDataGroup); 
   void validateEffectiveStopDate(const BFDataGroupId& idDataGroup);
   void validateAmountReason( const BFDataGroupId& idDataGroup );
   void getResponseData( BFData*& pResponse );
   void getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue) const;
   void validateFundNumber(const BFDataGroupId& idDataGroup);
   double getFundBalance (  bool& bFundValid, const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY validateAmtExcessBalance ( const DString& dstrAmt, const DString& dstrAmtType, const BFDataGroupId& idDataGroup );
   SEVERITY validateEscrowFundClass(const BFDataGroupId& idDataGroup);
   void getErrMsgValue( DString dstrErrNum, const BFDataGroupId& idDataGroup, DString& dstrErrValue );
   SEVERITY validateEntityIDForClearingPlatformEntity(const BFDataGroupId& idDataGroup);

   SEVERITY validateLangCodeForRESP(const DString& strValue,const BFDataGroupId& idDataGroup );

   SEVERITY validateIDForRESPEntity(const DString& strIDType,const BFDataGroupId& idDataGroup );
   SEVERITY buildEntitySSList(const DString& strEntityType, 
                              DString& strSelectableList, 
                              const BFDataGroupId& idDataGroup );
   SEVERITY validatePCGDelink(const DString& strValue,const BFDataGroupId&  idDataGroup );
   SEVERITY validateTaxJurisForRESP( const BFDataGroupId& idDataGroup );
   SEVERITY validatePCGList( const BFDataGroupId& idDataGroup );
   SEVERITY validateSINDuplicateForRESP( const BFDataGroupId& idDataGroup );
   SEVERITY validateClearingPlatform( const BFDataGroupId& idDataGroup );
   //QESI3FN03
   SEVERITY validateYearOfBirthForRESPBenf(const DString& strEntityDOfB, const BFDataGroupId& idDataGroup);
   SEVERITY validateDofBirthForRESPBenef(const DString& strEntityDOfB, const BFDataGroupId& idDataGroup);
   SEVERITY getEWIMsgforRESPBenfDofBirthUpdate( const BFDataGroupId &idDataGroup);
   SEVERITY doInitSINWithDofBirthForRESPBenf(const BFDataGroupId& idDataGroup);   
   // End - QESI3FN03
   //IN2780013 - SOC Loan Number and Loan Type
   SEVERITY validateLoanTypeLoanNumberForEscrow( const BFDataGroupId& idDataGroup ); 
   
   static bool sortByEntityID(const _entityIDSeqOrder& input1, 
                              const _entityIDSeqOrder& input2);
   int getEntityAge (const BFDataGroupId& idDataGroup);
   void setEscrowRelatedDate (const BFFieldId& idField, const BFDataGroupId& idDataGroup);
   SEVERITY getAccountHolderIDs(const BFDataGroupId& idDataGroup, DString& dstrNID, 
								DString &dstrPassport, DString& dstrCOINationalID,
								DString& dstrCOIPassport );
   SEVERITY validateAcctRegAgent(const BFDataGroupId& idDataGroup);
   SEVERITY AccountEntityXrefObject::setEntityAssociationSubstitutions(const BFDataGroupId& idDataGroup);
   SEVERITY initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew);

   DString objectKey;
   bool isAddCopy;
   BFData* _pResponseData;
   ErrMsgRulesList * _pErrMsgRulesList;
   int _iCountNum;
   DString  _dstrVerifyFilter;  
   bool     _bIsDirty;
   bool     _bVerificationEnabled;
   bool     _bInit;
   DString _paternalLastName;
};

/******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountEntityXrefObject.hpp-arc  $
 * 
 *    Rev 1.49   Aug 16 2012 10:52:08   wp040027
 * IN#3008167-P187485-CPF- Account Entity (RA) validation
 * 
 *    Rev 1.48   May 09 2012 16:17:38   if991250
 * CPF - IN 2945051 get the account tax type from Where used for axisting accounts
 * 
 *    Rev 1.47   May 02 2012 17:14:28   if991250
 * CPF - retrieve entity valid tax type from view 61
 * 
 *    Rev 1.46   Apr 27 2012 09:53:10   if991250
 * CPF - Account Setup & Settlement 
 * 
 *    Rev 1.45   Apr 16 2012 17:26:28   if991250
 * CPF Account Setup
 * 
 *    Rev 1.44   Feb 06 2012 04:32:20   panatcha
 * IN2780013 - SOC Loan Number and Loan Type
 * 
 *    Rev 1.43   Nov 22 2011 13:45:46   kitticha
 * P0188150 FN01 IN2740236 - There is no warning message after save entity maintenance without any TIN.
 * 
 *    Rev 1.42   Oct 28 2011 07:17:28   kitticha
 * PETP0188150 FN01 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.41   Feb 10 2011 12:59:22   dchatcha
 * P0165541FN12_IN2407181 : Error message'SIN Effective Date Cannot be Unknown', fix crashing after user change DOfB of existing RESP beneficiary to 12/31/9999.
 * 
 *    Rev 1.40   Nov 25 2010 11:28:52   kitticha
 * PET165541_FN03_QESI_Phase3_Non_Finance - revise.
 * 
 *    Rev 1.39   Nov 23 2010 08:37:00   kitticha
 * PET165541_FN03_QESI_Phase3_Non_Finance - revise
 * 
 *    Rev 1.38   Oct 29 2010 07:16:44   panatcha
 * PET165541_FN03_QESI_Phase3_Non_Finance
 * 
 *    Rev 1.37   Oct 08 2010 04:45:16   kitticha
 * PETP0172931_FN01_IN#2283060
 * 
 *    Rev 1.36   May 06 2010 23:35:46   popescu
 * RESP/QESI fixes
 * 
 *    Rev 1.35   Apr 06 2010 06:37:32   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, several fixes for issues found during VEW-DSK integration test.
 * 
 *    Rev 1.34   Apr 03 2010 02:23:58   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.33   Mar 31 2010 08:22:38   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.32   Mar 29 2010 07:13:32   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.31   Mar 26 2010 09:20:48   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.30   Mar 23 2010 13:49:42   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.29   Mar 12 2010 15:00:26   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.28   Jan 08 2009 06:01:02   daechach
 * IN 1545482 - R91-MT535/MT536-users should not be able to create Clearing platform entities.
 * 
 *    Rev 1.27   Jun 09 2008 07:27:24   daechach
 * Appended Revision Control Entries
 *
 */
