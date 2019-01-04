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
// ^FILE   : EntityIds.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : November, 1999
//
// ^CLASS    : EntityIds
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class DSTCWorkSession;

class IFASTCBO_LINKAGE EntityIds : public MFCanBFCbo, private boost::noncopyable
{
//static validation methods
public:
   static SEVERITY validateSIN (DSTCWorkSession &rpDSTCWorkSession,
                                const DString &sin,
                                const DString& strEntityTypeFmt,
                                const BFDataGroupId &idDataGroup,
                                bool bIsSINRequired = false, 
                                bool bIgnoreWarnings = false);
   static SEVERITY validateSIN (DSTCWorkSession &rpDSTCWorkSession, 
                                const DString &taxType,
                                const DString &entityType, 
                                const DString &sin,
                                const DString &entityId,
                                const BFDataGroupId &idDataGroup);
   static bool isSINExcepted (DSTCWorkSession &rpDSTCWorkSession, 
                              const DString &sin,
                              const BFDataGroupId &idDataGroup);

   SEVERITY validateBICCode ( DSTCWorkSession &rpDSTCWorkSession,
                              const DString &dstrBicCode,
                              const DString &dstrEntityId,
                              const BFDataGroupId &idDataGroup);
   SEVERITY validateNEQ (DSTCWorkSession &rpDSTCWorkSession,
                         const DString &dstrNEQ,
                         const DString &dstrEntityId,
                         const BFDataGroupId &idDataGroup);
   SEVERITY validateTrustAccountNum (DSTCWorkSession &rpDSTCWorkSession,
                                     const DString &dstrTrustAccountNum,
                                     const DString &dstrEntityId,
                                     const BFDataGroupId &idDataGroup);
   SEVERITY checkForDuplicateBICCode ( const DString &bicCodeValue,
                                       const BFDataGroupId &idDataGroup);
   SEVERITY checkForDuplicateNEQ (const DString &neqValue,const BFDataGroupId &idDataGroup);

   SEVERITY setBICCodeProperties (const BFDataGroupId& idDataGroup);
   SEVERITY setEntityType (const BFDataGroupId& idDataGroup);

   static SEVERITY validateIDTypeValueEntity( DSTCWorkSession &rpDSTCWorkSession, 
                                              const DString &entityType,
                                              const DString &entityID,
                                              const DString &taxType,
                                              const DString &idType,
                                              const DString &idValue,
                                              const BFDataGroupId &idDataGroup );

   static SEVERITY validateIDType (DSTCWorkSession &rpDSTCWorkSession, 
                                   const DString &idType,
                                   const DString &idValue, 
                                   const BFDataGroupId &idDataGroup, 
                                   bool bIsIDTypeRequired, 
                                   bool bIgnoreWarnings );

   static SEVERITY ValidateHKID_NRIC(DSTCWorkSession &rpDSTCWorkSession,
                                     const DString &dstrCode,
                                     const DString &dstrEntityId,
                                     const BFDataGroupId &idDataGroup);

   SEVERITY validatePCGAgainstSystem(const DString &strObjIDValue,
                                     const BFDataGroupId &idDataGroup);
   //MT53X
   void initializeClearingPlatformIDList(const BFDataGroupId& idDataGroup, bool bReadOnly = false);
   //QESI3FN03
   void doInitIdDate (const DString& dstrEntityType, 
                      const DString& dstrIDType, 
                      const DString& dstrValue, 
                      const BFDataGroupId &idDataGroup);
   //CHG0037322
   void initSinIdDateForTFSATaxType (const BFDataGroupId& idDataGroup);

  //SEVERITY validateSINForRESPBenef( const BFDataGroupId& idDataGroup);
  // end- QESI3FN03
public:
   EntityIds (BFAbstractCBO &parent);
   virtual ~EntityIds ();
   SEVERITY init ( const BFData &data, 
                   const DString &entityId,
                   const DString &entityType);
   SEVERITY init ( const BFDataGroupId &idDataGroup, 
                   const DString &entityId,
                   const DString &entityType);

   // visible for entity cbo
   SEVERITY isTrustNumberValid (const BFDataGroupId &idDataGroup);
   SEVERITY validationEntitySearchID (const BFDataGroupId &idDataGroup);

protected:
   SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, 
                           long lValidateGroup);
   SEVERITY doValidateField (const BFFieldId &idField, 
                             const DString &strValue, 
                             const BFDataGroupId &idDataGroup);
   SEVERITY doApplyRelatedChanges (const BFFieldId &idField, 
                                   const BFDataGroupId &idDataGroup);
   void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   SEVERITY validIdType (const BFDataGroupId &idDataGroup);
   bool isNetworkSenderEntity ( const BFDataGroupId &idDataGroup, 
                                const DString &strEntityNum);
   bool isNEQEntity (const BFDataGroupId &idDataGroup, 
                     const DString& strEntityNum);
   SEVERITY validateAdditionalAcctNumber (const BFDataGroupId &idDataGroup);
   SEVERITY validateIDValueForIDTypeOnSystem( const DString &IDType, 
                                              const DString &IDValue, 
                                              const BFDataGroupId& idDataGroup );

   SEVERITY initalizeXrEnvRefIDTypes (const BFDataGroupId &idDataGroup);
   SEVERITY validateGIINFormat(const BFDataGroupId &idDataGroup);
   SEVERITY validateTransmitterNumberFormat(const BFDataGroupId &idDataGroup);
   SEVERITY initStatusForGIIN(const BFDataGroupId &idDataGroup);
   SEVERITY validateForOverlappingOfRecords(const DString& strValue,const BFDataGroupId &idDataGroup);
   SEVERITY validateTaxIDEmployerIDForFATCA(const DString& againstedIDType,const BFDataGroupId &idDataGroup);
   SEVERITY verifyStatusRelatedChanges (const BFFieldId &idFieldId, const BFDataGroupId &idDataGroup);

private:
   static DString getEntityTypeDescription ( DSTCWorkSession &rpDSTCWorkSession,
                                             const DString &entityType,
                                             const BFDataGroupId &idDataGroup);
   static bool isSINRequired ( DSTCWorkSession &rpDSTCWorkSession, 
                               const DString &taxType,
                               const DString &entityType, 
                               const BFDataGroupId &idDataGroup,
                               bool &bCheckedErrMsgList,
                               DString &strErrValue = DString (I_("W")));

   static bool isIDTypeRequired( DSTCWorkSession &rpDSTCWorkSession, 
                                 const DString &taxType,
                                 const DString &entityType,
                                 const DString &idType,
                                 const BFDataGroupId &idDataGroup,
                                 DString &strErrValue = DString (I_("W")) );

   static SEVERITY validateSINOnSystem (DSTCWorkSession &rpDSTCWorkSession, 
                                        const DString &entityId,
                                        const DString &sin,
                                        const BFDataGroupId &idDataGroup);

   SEVERITY isTrustNumberValid (DSTCWorkSession &rpDSTCWorkSession,
                                const DString& strTrustNum,
                                const BFDataGroupId &idDataGroup);

   void setAllFieldsReadOnly (const BFDataGroupId &idDataGroup);
   SEVERITY setSINToParentEntity (const BFDataGroupId &idDataGroup);
   SEVERITY checkForDuplicateSIN (const DString &sin, 
                                  const BFDataGroupId &idDataGroup);
   SEVERITY nonSINRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY validateSINDuplicateForRESP(const DString &sin, 
                                        const BFDataGroupId &idDataGroup);
   //MT53X
   void initializeSubstitutionList( const BFFieldId& idField, 
                                    const DString &dstrGroupCode, 
                                    const BFDataGroupId& idDataGroup);

   SEVERITY getEWIMsgforRESPBenfSINUpdate(const BFDataGroupId &idDataGroup);
   bool CheckForDuplicateID( const DString &idType ,const BFDataGroupId& idDataGroup) ;
   SEVERITY validateAcctRegAgent(const BFDataGroupId& idDataGroup );
   SEVERITY validateTaxFileNum(const BFDataGroupId& idDataGroup );
   SEVERITY validateAusBusinessNum(const BFDataGroupId& idDataGroup );
   SEVERITY initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew);
 
   DString  _market;
   DString  _dstrVerifyFilter;
   bool     _bIsDirty;
   bool     _bVerificationEnabled;
   bool     _bInit;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityIds.hpp-arc  $
 * 
 *    Rev 1.45   Aug 16 2012 10:53:40   wp040027
 * IN#3008167-P187485-CPF- Account Entity (RA) validation
 * 
 *    Rev 1.44   Jul 23 2012 17:05:12   dchatcha
 * P0179630 FN01 FATCA Project - Entity level
 * 
 *    Rev 1.43   Jul 12 2012 19:01:00   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
 * 
 *    Rev 1.42   Apr 04 2012 21:28:52   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.41   Nov 25 2010 08:13:30   kitticha
 * PET165541_FN03_QESI_Phase3_Non_Finance - revise.
 * 
 *    Rev 1.40   Nov 23 2010 08:48:46   kitticha
 * PET165541_FN03_QESI_Phase3_Non_Finance - revise
 * 
 *    Rev 1.39   Oct 29 2010 07:19:10   panatcha
 * PET165541_FN03_QESI_Phase3_Non_Finance
 * 
 *    Rev 1.38   Aug 16 2010 06:26:00   panatcha
 * P0172931_FN01_MT53X_Entity Creation
 * 
 *    Rev 1.37   Apr 30 2010 11:10:48   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.36   Apr 07 2010 09:35:06   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.35   Mar 29 2010 07:03:40   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.34   Mar 12 2010 14:59:08   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.33   Oct 01 2009 11:34:08   dchatcha
 * P0163546 FN01 TA Automate Fund Transfer, Code review.
 * 
 *    Rev 1.32   Sep 28 2009 07:58:08   dchatcha
 * P0163546 FN01 TA Automate Fund Transfer.
 * 
 *    Rev 1.31   23 Jan 2009 16:32:34   popescu
 * Incident 	1548019 - reset button on entitymaintenance dlg, BIC Code can be valid/invalid for entitytype 58
 * 
 *    Rev 1.30   16 Jan 2009 17:23:12   popescu
 * Incident 1544134 - various fixes
 * 
 *    Rev 1.29   Dec 15 2008 01:47:30   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.28   06 Jul 2007 14:43:18   popescu
 * PET 2363 GAP 6 CIF
 * 
 *    Rev 1.27   Nov 20 2006 13:52:06   jankovii
 * PET 2287 FN01 - Grupo Mundial Trade Aggregation.
 * 
 *    Rev 1.26   Nov 06 2006 10:05:32   jankovii
 * Incident #737656: Bic code validation.
 * 
 *    Rev 1.25   Jul 26 2006 13:43:16   jankovii
 * PET 2192 FN02 - Dealings Sender Cut Off Time.
 * 
 *    Rev 1.24   Jul 24 2006 11:44:34   jankovii
 * PET 2192 FN02 Dealings Sender Cut Off Time.
 * 
 *    Rev 1.23   Mar 01 2005 11:52:16   yingbaol
 * PET1137,FN01: EU saving entity update
 * 
 *    Rev 1.22   Nov 14 2004 14:36:40   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.21   Nov 04 2004 11:01:04   FENGYONG
 * PET1117 FN54 - Fund broker static temp check in for 59 build
 * 
 *    Rev 1.20   Jan 12 2004 18:48:08   popescu
 * PTS 10024062, fixed fail on joint account duplicate SIN; (sin values part of the exception list should be checked as duplicates)
 * 
 *    Rev 1.19   Nov 25 2003 12:17:54   popescu
 * PTS 10024062, before checking for a duplicate SIN see whether SIN is part of the exception list
 * 
 *    Rev 1.18   Nov 17 2003 14:33:10   popescu
 * PTS 10023438, SIN RESP validation, do not to add warnings if ErrorValue from err msg rule list return 'I'
 * 
 *    Rev 1.17   Nov 08 2003 21:46:12   popescu
 * PTS 10023438, performance issues fixes, do not call PopulateWhereUsed anymore, data is in memory
 * 
 *    Rev 1.16   Nov 06 2003 09:41:08   popescu
 * PTS 10023703, fixed error message for non-sin type of id's.
 * 
 *    Rev 1.15   Nov 05 2003 18:05:20   popescu
 * PTS 10023703, Erroneous warning 'Account owner SIN missing' pops-up, although the SIN number is correctly retrieved by Desktop from back-end,
 * 
 *    Rev 1.14   Nov 05 2003 14:25:56   popescu
 * PTS 10023438, SIN should be required and valid if acct is RESP or family RESP and  entity is acct owner or beneficiary
 * 
 *    Rev 1.13   Oct 30 2003 17:26:20   popescu
 * PTS 10023438, RESP SIN legislative requirement
 * 
 *    Rev 1.12   Oct 30 2003 16:30:34   popescu
 * PTS 10023438, RESP SIN legislative requirement
 * 
 * 
 */