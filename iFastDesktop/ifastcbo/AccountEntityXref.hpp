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
// ^FILE   : AccountEntityXref.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AccountEntityXref
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <ifastcbo\mfaccount.hpp>

class AccountEntityXrefObject;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

const DString strEmpty;
class IFASTCBO_LINKAGE AccountEntityXref : public MFCanBFCbo, private boost::noncopyable
{
public:
   AccountEntityXref( BFAbstractCBO &parent );
   virtual ~AccountEntityXref();

   SEVERITY init();
   SEVERITY PopulateAccountOwner( const BFDataGroupId& idDataGroup, 
                                  const DString &EntityId, 
                                  const DString &InputAcctNum = strEmpty, 
                                  const DString &InputShrNum = strEmpty, 
                                  const DString &NumEntry = strEmpty);

   SEVERITY PopulateWhereUsed( const DString &EntityId,
                               const DString &EntityType = NULL_STRING,
                               const DString &dstrTrack = I_("N"), 
                               const DString &dstrPageName = NULL_STRING,
                               const DString &retSameCIFAcct = I_("N"));

   SEVERITY PopulateEntitiesList( const BFDataGroupId& idDataGroup, 
                                  const DString& AccountNum,
                                  const DString& dstrTrack = I_("N"), 
                                  const DString& dstrPageName = NULL_STRING);

   SEVERITY UnlinkEntity( const DString& AccountNum, const DString& EntityId, const BFDataGroupId& idDataGroup );

   SEVERITY LinkEntity( const DString& AccountNum, 
                        const DString& EntityType, 
                        const DString& SeqNumber, 
                        const DString& EntityId, 
                        const BFDataGroupId& idDataGroup, 
                        AccountEntityXrefObject*& pAccountEntityXrefObject,
                        bool isCopyEntity = false );

   SEVERITY GetNextSeqNumber( const BFDataGroupId& idDataGroup, 
                              const DString& AccountNum, 
                              const DString& entityType, 
                              DString& seqNumber );

    SEVERITY GetEntitySeqNumber( const BFDataGroupId& idDataGroup,
		                         const DString& AccountNum, 
                                 const DString& EntityId,  
                                 DString& seqNumber );

   SEVERITY GetEntityIdForAccountOwnerSequence1( const DString& AccountNum, const BFDataGroupId& idDataGroup, DString &entityId );
   SEVERITY GetAcctOwnerEntityInfo( const DString& accountNum, const DString& seqNumber, const BFDataGroupId& idDataGroup, 
	                               DString& entityId, DString& firstName, DString& lastName );

   SEVERITY GetRESPEntityInfo(const DString& dstrAcctNum, 
                              const BFDataGroupId& idDataGroup, 
					          const DString& dstrEntityId,
							  DString& dstrRESPAllocPrcnt,
							  DString& dstrBenefDofBirth,
							  DString& dstrHRDCRelateCode,
							  DString& dstrTaxJuris,
							  DString& dstrEffectiveDate);

   SEVERITY validateDateOfBirth (const DString &accountNumber, const BFDataGroupId& idDataGroup);

   int GetNumberOfAccountHolders( const DString& AccountNum, const BFDataGroupId& idDataGroup );
   int GetNumberOfEntityByType( const DString& dstrAccountNum, const DString& dstrEntityType, const BFDataGroupId& idDataGroup );
   SEVERITY GetAccountEntityXrefObjectByType(const DString& dstrAccountNum, 
                                             const DString& dstrEntityType, 
                                             const int& index, 
                                             const BFDataGroupId& idDataGroup, 
                                             AccountEntityXrefObject*& pAccountEntityXrefObject);
   //build the key for us
   static void buildKey( DString &strKey, const DString& AccountNum, 
                         const DString& EntityType, const DString& SeqNumber, const DString& EntityId,
                         const DString& NewCount = NULL_STRING);
   static void buildPartialKeyForAccount( DString& partialKey, const DString& AccountNum );
   static void buildPartialKeyForEntityType( DString& partialKey, const DString& EntityType );
   static void buildPartialKeyForSequenceNumber( DString& partialKey, const DString& SequenceNumber );
   static void buildPartialKeyForEntityId( DString& partialKey, const DString& EntityId );
   static bool getValueForTag( const DString& strBuffer, const I_CHAR* szTag, DString &strValue );
   static void buildPartialKeyForRetrievingEntity( DString& strKey, const DString& AccountNum, 
                                                   const DString& EntityType, const DString& EntitySeq );
   static void buildPartialKeyForAcctEntityId( DString& strKey, const DString& AccountNum,
                                               const DString& EntityId );
   void setCurrentAccounNum( const DString& accountNum );
   bool getAvailablePercentForBenef( const DString& benefType, DString& percent, const BFDataGroupId& idDataGroup );
   bool IsDeleteAllowed(const DString&  strKey, const BFDataGroupId& idDataGroup,bool bAddCond = true );
   SEVERITY validateOneAccount( const DString& accountNum, const BFDataGroupId& idDataGroup );
   SEVERITY escrowAccount( const DString& strAcctNum, const DString& dstrTransType, const DString& dstrEntityType, 
                           const DString& dstrDate, const BFDataGroupId& idDataGroup, const DString& dstrInReason = NULL_STRING, const DString& dstrSeqNumber = NULL_STRING );
   SEVERITY escrowAccountFundClass( const DString& strAcctNum, const DString& strFund, const DString& strClass,
                                    const DString& dstrDate, const BFDataGroupId& idDataGroup ) ;
   void AddCopy(DString &orgKey, DString &destKey, const BFDataGroupId& idDataGroup);
   void getAcctOwnerEntities( ENTITIES_VECTOR & acctOwnerEntities, DString dstrAcctNum, const BFDataGroupId& idDataGroup );
   void getClearingPlatformEntities( ENTITIES_VECTOR & clearingPlatformEntities, DString dstrAcctNum, const BFDataGroupId& idDataGroup );
   void getRESPBeneficiaryEntities( ENTITIES_VECTOR & respBeneficiaryEntities, DString dstrAcctNum, const BFDataGroupId& idDataGroup );
   void getFormerSpouses( ENTITIES_VECTOR & formerSpouseEntities, DString dstrAcctNum, const BFDataGroupId& idDataGroup );
   void getBeneficiaries(  ACCTENTITYOBJ_VECTOR & vBenefEntities, DString dstrAcctNum, const BFDataGroupId& idDataGroup );
   void getAnnitants(  ACCTENTITYOBJ_VECTOR & vAnnitantEntities, DString dstrAcctNum, const BFDataGroupId& idDataGroup );
   void getAcctOwners(  ACCTENTITYOBJ_VECTOR & vAcctOwnerEntities, DString dstrAcctNum, const BFDataGroupId& idDataGroup );
   void getSpouse(  ACCTENTITYOBJ_VECTOR & vSpouseEntitiesVector, DString dstrAcctNum, bool bSpouse, const BFDataGroupId& idDataGroup );
   void cloneAcctEntityXrefFromModel( const DString& modelAccountNum, 
                                      const DString& newAccountNum, 
                                      const BFDataGroupId& idDataGroup );
   void SetChildrenSpousalNameSubSet( const BFDataGroupId& idDataGroup, bool setdefault = false );
   void setRESPSelectableFieldSubSet( const DString& entityType, 
                                      const DString& strDeletedKey,
                                      const BFDataGroupId& idDataGroup );

   SEVERITY getEntityMasterListAsOfDate (DString &entityAsOfDateList,
                                         const DString &entityType,
                                         const BFDataGroupId &idDataGroup,                                                                                                                  
                                         const DString &strAsOfDate = NULL_STRING,
                                         const bool &formatComma = false,
                                         const DString &accountNum = NULL_STRING);

   SEVERITY getEntityTaxJuris (const DString& dstrAcctNum, 
                               const BFDataGroupId& idDataGroup, 
						       const DString& dstrEntityId,
						       DString& dstrTaxJuris);

   bool IsSpouselinkedtoOwner (const DString &SpouseEntityId, const BFDataGroupId& idDataGroup);
   void setrefreshflag(bool relreshflag);
   bool getrefreshflag();
   DString getNextCount();
   DString getPrevCount();
   int  getCurrentCount();
   DString getStrCurrentCount();
   bool isRESPBeneficiaryDeleted (const DString& accountNum, const BFDataGroupId& idDataGroup);
   SEVERITY GetEntityIdForEntityType( const DString& accountNum, 
                                      const DString& entityType,
                                      const BFDataGroupId& idDataGroup, 
                                      DString& entityId );//Added for INC0033364
   SEVERITY GetEntityIdForEntityType( const DString& accountNum, 
                                      const DString& entityType,
                                      const DString& seqNumber, 
                                      const BFDataGroupId& idDataGroup, 
                                      DString& entityId );
   //P0186486_FN01 - IN2738162 Loan Number vs shareholder
   SEVERITY validateLoanNumberForNonEscrowAccount(const DString& accountNum, const BFDataGroupId& idDataGroup); 

   SEVERITY getAssociateEntitySubList(DString &subList, 
                                      const BFDataGroupId &idDataGroup,
                                      const DString &excludeEntityTypeFromSubList, 
                                      const DString &excludeSeqNumbeFromSubList);

   SEVERITY updateAssociateEntityForAllRelatedPartyEntities(const BFDataGroupId &idDataGroup,
                                                            const DString &excludeEntityTypeFromSubList, 
                                                            const DString &excludeSeqNumbeFromSubList);

   SEVERITY updateVerifyStatForDeletion( const BFDataGroupId &idDataGroup);

   void getRDSPBeneficiaryEntity( ENTITIES_VECTOR & rdspBeneficiaryEntity, DString dstrAcctNum, const BFDataGroupId& idDataGroup );

protected:
   virtual void doCommitDataGroup( const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );
   //support for refresh
   virtual SEVERITY doPreClearFields();
   virtual SEVERITY refresh( bool bNewObject = false );
   virtual bool canDeleteObject( const DString&  strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doDeleteObject ( const DString & strKey, const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed );
   
   SEVERITY validateAnnuitant (const DString &dstrAnnuitantSIN, const BFDataGroupId& idDataGroup);

private:
   SEVERITY AEXrefCreateObjectForEachRepeat( const BFData &data );
   void getStrKey( DString &strKey, const BFData *data );
   bool verifyDuplicityOfAcctOwnerEntities( const DString& entityId = NULL_STRING, const int current_index = -1 );
   SEVERITY escrowTitleRestrict( const DString& dstrReasonCode, const DString& dstrTransType, const BFDataGroupId& idDataGroup );
   SEVERITY escrowReason01To06 ( const DString& dstrEscrowFund, const DString& dstrTransType,const DString& dstrReasonCode, const BFDataGroupId& idDataGroup );
   SEVERITY escrowReason07To08 (const DString& dstrEscrowFund, const DString& dstrTransType, const BFDataGroupId& idDataGroup );
   SEVERITY escrowReason09 (const DString& dstrEscrowFund, const DString& dstrTransType, const BFDataGroupId& idDataGroup );
   SEVERITY escrowReason12To23 (const DString& dstrEscrowFund, const DString& dstrTransType, const BFDataGroupId& idDataGroup );
   void setupEscrowReasons( ) ;

   SEVERITY duplicateSINErrorWarning(const DString& strEntityID1,
                                     const DString& strEntityID2,
                                     const BFDataGroupId&  idDataGroup );

   DString _accountNum;
   DString _entityId;
   DString _entityType;
   DString _entitySeq;
   bool    _bEscrowBand;
   int     _iNewCount;
   DString currAccountNum; //used to validate only account-entity pairs that have one specific account

   typedef std::map< DString, int >     OBJ_USAGE_MAP;
   typedef OBJ_USAGE_MAP::iterator  OBJ_USAGE_MAP_ITER;
   typedef std::vector< DString > ENTITIES_VECTOR;

   OBJ_USAGE_MAP _entityMap;
   OBJ_USAGE_MAP _accountMap;
   ENTITIES_VECTOR acctOwnerEntities;

   bool flg_where_used;
   bool m_bRefresh;
   DString oldKey;

   typedef std::map < DString, long >  ESCROW_REASON_MAP;
   typedef ESCROW_REASON_MAP::iterator  ESCROW_REASON_MAP_ITER;
   typedef ESCROW_REASON_MAP::value_type  ESCROW_REASON_MAP_VALUE_TYPE;
   ESCROW_REASON_MAP _escrowReasonMap;
};

/******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountEntityXref.hpp-arc  $
 * 
 *    Rev 1.49   Mar 21 2012 12:10:16   jankovii
 * IN 2873391 - Cannot set up Joint RESP in iFAST
 * 
 *    Rev 1.48   Dec 01 2011 00:12:54   panatcha
 * IN2738162 Loan Number vs shareholder
 * 
 *    Rev 1.47   Jul 20 2011 17:54:58   dchatcha
 * P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
 * 
 *    Rev 1.46   Jan 10 2011 03:52:06   wutipong
 * IN2311277 - Unable to access FDP accounts in Desktop
 * 
 *    Rev 1.45   Sep 29 2010 11:37:16   jankovii
 * PET0175377 FN01 - AIP for Joint RESP Account
 * 
 *    Rev 1.44   May 06 2010 23:35:24   popescu
 * RESP/QESI fixes
 * 
 *    Rev 1.43   Apr 28 2010 13:07:36   jankovii
 * PET0165541 FN01 QESI RESP Trading
 * 
 *    Rev 1.42   Apr 23 2010 16:06:56   jankovii
 * PET0165541 FN01 QESI RESP Trading
 * 
 *    Rev 1.41   Apr 14 2010 02:06:48   kitticha
 * PET0165541-FN01 QESI RESP Trading.
 * 
 *    Rev 1.40   Mar 31 2010 08:28:22   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.39   Mar 26 2010 09:25:08   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.38   Mar 25 2010 13:56:28   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.37   Mar 22 2010 15:09:02   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.36   Mar 17 2010 06:33:10   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.35   Mar 12 2010 14:56:02   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.34   Mar 08 2010 13:16:46   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
 * 
 *    Rev 1.33   Feb 05 2009 15:56:58   jankovii
 * IN 1578637 - Project PBSA - Issue on Non Financial Update in Desktop - MMF#007
 * 
 *    Rev 1.32   Oct 28 2008 08:29:16   jankovii
 * PET 59888 FN03 AML KYC.
 * 
 *    Rev 1.31   06 Oct 2008 13:16:26   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.30   Jun 09 2008 06:25:44   daechach
 * Appended Revision Control Entries
 *
 */
