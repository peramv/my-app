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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPTransferList.hpp
// ^AUTHOR : 
// ^DATE   : February, 2010
//
// ^CLASS    : RESPTransferList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class RESPTransfer;

class IFASTCBO_LINKAGE RESPTransferList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   RESPTransferList (BFAbstractCBO &parent);
   virtual ~RESPTransferList ();

   // Initialize function
   SEVERITY initNew ( const DString &accountNum,
                      const DString &accountNumTo,
                      const DString &transType,
                      const DString &tradeDate,
                      const DString &depositType,
                      const DString &redCode,
                      const DString &amount,
                      const BFDataGroupId &idDataGroup,
                      bool bSetFieldsReadOnly = false,
                      const DString &dstrTrack = I_("N"),
                      const DString &dstrPageName = NULL_STRING);
   SEVERITY init ( const DString &accountNum,
                   const DString &accountNumTo,
                   const DString &transId,
                   const DString &transType,
                   const DString &tradeDate,
                   const DString &depositType,
                   const DString &redCode, 
                   const DString &amount,
                   const DString &tradeType = I_("Pend"),
                   bool bSetFieldsReadOnly = false,
                   const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING);

   SEVERITY readDefaultNotionals ( const DString &benefIdFrom,
                                   const DString &benefIdTo,
                                   const DString &benefIdSeqTo,
                                   const DString &transferPercent,
                                   const BFDataGroupId &idDataGroup,
                                   bool bAcctTransferPercent = false,
                                   bool bTransferPercentUpdate = false);

   SEVERITY restoreNotionals ( const DString &benefIdFrom,
                               const DString &benefIdTo,
                               const DString &benefIdSeqTo,
                               const DString &transferPercent,
                               const BFDataGroupId &idDataGroup,                               
                               bool bAcctLevel,							   
							   DString &strKey);  

   SEVERITY checkDuplicate ( const RESPTransfer *pRESPTransferToCheck, 
                             const BFDataGroupId &idDataGroup);
                             
   SEVERITY checkDuplicate ( const BFDataGroupId &idDataGroup); 
                                                      
   SEVERITY totalGrants (const BFDataGroupId &idDataGroup);
   SEVERITY getBeneficiaryMasterList ( DString &beneficiaryList, 
                                       const DString &accountNum,
                                       const BFDataGroupId &idDataGroup,
                                       bool bFromAccount = true);
   SEVERITY getRESPEntityInfo (const DString dstrEntityId, 
                               const BFDataGroupId &idDataGroup, 
                               const DString& dstrAccountNum,
                               DString& dstrEffectiveDate);

   SEVERITY getRESPEntityInfo(const DString dstrEntityId, 
                              const BFDataGroupId &idDataGroup, 
                              const DString& dstrAccountNum,
                              DString& dstrEffectiveDate,
                              DString& dstrRESPAllocPrcnt,
                              DString& dstrTaxJuris,
                              DString& dstrHRDCRelateCode,
                              DString& dstrBenefDofBirth);

   SEVERITY getEntitySeqNumber (const DString dstrEntityId, 
                                const DString dstrAccountNum,
                                const BFDataGroupId &idDataGroup, 
                                DString& dstrSeqNumber);

   SEVERITY validateBeneficiaryEffectiveDate ( const DString &dstrTradeDate, 
                                               const BFDataGroupId &idDataGroup);

   SEVERITY setAccountCLBGrant (const BFDataGroupId &idDataGroup, bool bSetValue = true);
   SEVERITY validateAccountCLBGrant (const BFDataGroupId &idDataGroup);

   bool isInternalTransfer (const BFDataGroupId &idDataGroup);
   bool isPurchaseLikeTransfer (const BFDataGroupId &idDataGroup);
   bool isNonRespToResp (const BFDataGroupId &idDataGroup);
   bool initTransferPercent (const BFDataGroupId &idDataGroup);
   bool isAcctLevelOverrideApplicable (const BFDataGroupId &idDataGroup);
   bool isRESPRelatedFieldsUpdated (const BFDataGroupId &idDataGroup);
   bool isNonTrustee(const BFDataGroupId &idDataGroup);
   bool isInHistoricalRESPPeriod(const BFDataGroupId& idDataGroup);
   bool isInHistoricalRESPPeriod(const DString& strYear,const BFDataGroupId& idDataGroup);
   bool isNonTrusteeContrib(const BFDataGroupId &idDataGroup); //IN2672499 - RESP Transfer Information error message
   
   bool isAnyRESPBenefQCResident(const BFDataGroupId &idDataGroup);
   void getTradeYear (DString &dstrTradeYear,const BFDataGroupId &idDataGroup);
   SEVERITY	getMore();
   SEVERITY isTotTransfINDCApplicable(const BFDataGroupId &idDataGroup);
   bool isListOfNonTrusteeTrfx ( const BFDataGroupId &idDataGroup );
   SEVERITY getUpdatedRecord(RESPTransferList *&pList, const BFDataGroupId &idDataGroup );
   SEVERITY checkExistingBenf ( const RESPTransfer *pRESPTransferToCheck,const BFDataGroupId &idDataGroup);
   bool checkBenefExists ( const RESPTransfer *pRESPTransferToCheck,
                                            const BFDataGroupId &idDataGroup);
   SEVERITY validateContribYear (const RESPTransfer *pRESPTransferToCheck,
                                                   const BFDataGroupId &idDataGroup);
   SEVERITY doDefaultWithBenefCurrTradeYear( const  RESPTransfer *pRESPTransferToCheck,
                                             DString &strEligibleTransfer,
                                             DString &strTotTransfINDC,
                                             const BFDataGroupId &idDataGroup);
   bool isAnyBenefCurrTradeYear(const BFDataGroupId &idDataGroup);
   bool setAnyBenefCurrTradeYear(const BFDataGroupId &idDataGroup);
   bool isAnyHistricalTxfr(const BFDataGroupId &idDataGroup);
   bool checkContribution ( const RESPTransfer *pRESPTransferToCheck,
                                          const BFDataGroupId &idDataGroup,
                                          bool bCheckCurrYearTrade /*false*/);
   SEVERITY populateRequestData ( BFData &requestData,
                                  const BFDataGroupId &idDataGroup); 
   bool isExternalTransferOut (const BFDataGroupId &idDataGroup);
   bool isManualOverrideApplicable (const BFDataGroupId &idDataGroup);
   SEVERITY setAccountCLBAmounts (const BFDataGroupId &idDataGroup);
                                     
protected:

   virtual SEVERITY doCreateObject (const BFData &data, BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject (BFCBO *&pBase, DString &strKey,  const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);
   virtual SEVERITY doApplyRelatedChanges (const BFFieldId& idField, const BFDataGroupId& idDataGroup);
   virtual SEVERITY doValidateField (const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
   virtual SEVERITY doAcctLevelOverrideChanges (const BFDataGroupId& idDataGroup);

   SEVERITY doInceptionDateChanges (const BFDataGroupId& idDataGroup);
   SEVERITY validateNumberOfBeneficiaries (const BFDataGroupId &idDataGroup);
   SEVERITY validateInceptionDate (const DString &dstrInceptionDate, const BFDataGroupId &idDataGroup);
   SEVERITY validateTerminationDate (const DString &dstrTerminationDate, const BFDataGroupId &idDataGroup);
   SEVERITY validatePlansAndContracts (const BFDataGroupId &idDataGroup);
   SEVERITY validateLeterAndStatus (const BFDataGroupId &idDataGroup);
   SEVERITY validateAccountNotinalData (const BFDataGroupId &idDataGroup);
   SEVERITY validateFromToBeneficiary (const BFDataGroupId &idDataGroup);
   SEVERITY validateQESITotTxfr (const BFDataGroupId& idDataGroup);
   SEVERITY validateContribYear (const BFDataGroupId &idDataGroup);
   SEVERITY validateAccountLTDAmt (const BFDataGroupId &idDataGroup);
   SEVERITY validateAccountQESIPreFeb2007Amt (const BFDataGroupId &idDataGroup);
   SEVERITY validateTransferUpdate ( const BFDataGroupId &idDataGroup );

   SEVERITY commonInit (const BFDataGroupId &idDataGroup);
   SEVERITY setFieldsReadOnly (const BFDataGroupId &idDataGroup);
   SEVERITY grantTotal (const BFFieldId &idField,
                        const BFDataGroupId &idDataGroup,
                        DString &dstrGrantTotal);
   SEVERITY displayRespToRespWarning (const BFDataGroupId &idDataGroup);

   void initNEQs (const DString &depositType, const DString &redCode, const BFDataGroupId &idDataGroup);
   void initDates (const DString &depositType, const DString &redCode, const BFDataGroupId &idDataGroup);
   void initLetterAndStatus (const DString &tradeType, const DString &depositType, const DString &redCode, const DString &transType, const BFDataGroupId &idDataGroup);

   void initFromPlanInfo (const DString &depositType, const DString &redCode, const DString &transType, const BFDataGroupId &idDataGroup);
   void initToPlanInfo (const DString &depositType, const DString &redCode, const DString &transType, const BFDataGroupId &idDataGroup);
   void setOnlyUpdatedFlag(bool bOnlyUpdated);
   void clearConditionBeforeSubmission (Frame *pFrame, int conditionCode);

   SEVERITY setInNonTrusteeTxfrPeriod(const BFDataGroupId& idDataGroup);
   SEVERITY  doTransfINDCApplicable(bool bFlag,const BFDataGroupId& idDataGroup);
   SEVERITY doNEQ1RelatedChanges(const BFDataGroupId& idDataGroup);
   SEVERITY doRESPTransStatRelatedChanges(const BFDataGroupId& idDataGroup);   
   SEVERITY validateBeneficiaries (const BFDataGroupId &idDataGroup);

private:
   SEVERITY validateRESPInfoUpdate ( const BFDataGroupId &idDataGroup );
   SEVERITY buildDataObject(RESPTransferList* pList,const BFDataGroupId& idDataGroup);

   int getYear (const DString &date);

   bool  _bSetFieldsReadOnly;
   bool _bOnlyUpdated;
   bool _bNonTrusteeContrib; //IN2672499 - RESP Transfer Information error message

   DString m_FromBeneficiaryList,
      m_ToBeneficiaryList;
   DString _dstrTrack,
      _dstrPageName;
   BFData* _pRequestData;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log::   Y:/VCS/BF iFAST/ifastcbo/RESPTransferList.hpp-arc  $
//
//   Rev 1.26   Oct 05 2011 00:57:22   panatcha
//IN2672499 - RESP Transfer Information error message
//
//   Rev 1.25   Jul 29 2011 07:42:58   panatcha
//fix IN5285248 and IN2591262
//
//   Rev 1.24   Jul 25 2011 07:16:02   panatcha
//P0184541_FN01_InvescoQESItrans incidents
//
//   Rev 1.23   Jul 14 2011 08:14:24   panatcha
//DRAFT - IN2584478, IN5285248, IN2591262 
//
//   Rev 1.22   Jun 28 2011 10:33:28   panatcha
//P0184541_FN01_InvescoQESItrans
//
//   Rev 1.21   Oct 29 2010 05:34:10   kitticha
//PET0165541 FN03 - QESI Phase3.
//
//   Rev 1.20   Sep 03 2010 05:32:28   dchatcha
//IN# 2231991 - No warning message when changing the Transfer%
//
//   Rev 1.19   Aug 13 2010 12:10:34   jankovii
//Sync up: IN 2200243 - Invesco Trimark Parent Cycle CY1287 {27 JULY 2010}
//
//   Rev 1.18   Jul 21 2010 22:38:12   dchatcha
//PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review, remove no longer required pieces.
//
//   Rev 1.17   Jul 21 2010 01:31:06   dchatcha
//PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review, logic will be more simpler.
//
//   Rev 1.16   Jun 29 2010 02:59:52   dchatcha
//PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review.
//
//   Rev 1.15   Jun 24 2010 07:45:38   dchatcha
//PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen.
// 
