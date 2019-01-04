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
// ^FILE   : RESPTransfer.hpp
// ^AUTHOR : 
// ^DATE   : February, 2010
//
// ^CLASS    : RESPTransfer
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

class RESPTransferValidation;
class EntityIdsList;

class IFASTCBO_LINKAGE RESPTransfer : public MFCanBFCbo, private boost::noncopyable
{
public:
   friend class RESPTransferList;

   RESPTransfer (BFAbstractCBO &parent);
   virtual ~RESPTransfer();

   SEVERITY init ( const BFData& data, 
      const BFDataGroupId &idDataGroup,
      bool bSetFieldsReadOnly = false,
	  bool bSetNotionals = false);
   SEVERITY initNew (const BFDataGroupId& idDataGroup, 
                     bool bSetFieldsReadOnly = false);
   SEVERITY getTransferValidation (RESPTransferValidation *&pRESPTransferValidation,
                                   const BFDataGroupId &idDataGroup);
   SEVERITY setGrantsReadOnly (bool bReadOnly, const BFDataGroupId& idDataGroup);
   SEVERITY validateFromToBeneficiary (const BFDataGroupId &idDataGroup);
   bool isRESPRelatedFieldsUpdated(const BFDataGroupId &idDataGroup);


   SEVERITY loadNotionalYearList(const BFDataGroupId &idDataGroup);
   SEVERITY clearFieldsForNonTrusteeTxfrGrants (const BFDataGroupId& idDataGroup);
   SEVERITY resetFieldsForNonTrusteeTxfrGrants ( const BFDataGroupId& idDataGroup);
   SEVERITY initNonTrusteeTxfrFields(const BFDataGroupId& idDataGroup);
   virtual void getStrKey( DString &strKey, const BFData *data = NULL );
   SEVERITY initClone (const BFData& data, const BFDataGroupId &idDataGroup );
   bool isSAGESRelatedFieldsUpdated(const BFDataGroupId &idDataGroup);

protected:
   virtual void doInitWithDefaultValues (const BFDataGroupId& idDataGroup);
   virtual SEVERITY doValidateField (const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
   virtual SEVERITY doApplyRelatedChanges (const BFFieldId& idField, const BFDataGroupId& idDataGroup);
   virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);	
   virtual SEVERITY doTransferPercentChanges (const BFDataGroupId& idDataGroup);

   SEVERITY validateBeneficiary (const DString &dstrBenefId, const BFDataGroupId &idDataGroup, bool bFromAccount = true);
   SEVERITY validateBeneficiary (const BFDataGroupId &idDataGroup);
   SEVERITY validateCLBGrant (const BFDataGroupId &idDataGroup);
   SEVERITY validateTransferPercent (const DString &dstrTransferPercent, const BFDataGroupId &idDataGroup);
   SEVERITY validateFromToSIN (const BFDataGroupId &idDataGroup);
   SEVERITY getSIN (DString &dstrSIN, EntityIdsList *&pEntityIdsList, const BFDataGroupId &idDataGroup);
   SEVERITY isSameSIN (const BFDataGroupId &idDataGroup, bool &bSameSIN);
   SEVERITY doCLBAmountChanges (const BFDataGroupId& idDataGroup, bool bSetValue = true);
   SEVERITY setAccountLevelGrantsReadOnly (const BFDataGroupId& idDataGroup);
   SEVERITY doNEQ1RelatedChanges(const BFDataGroupId& idDataGroup);
   SEVERITY doTotTransfINDCRelatedChanges(const BFDataGroupId& idDataGroup);
   SEVERITY doEligibleTransferRelatedChanges(const BFDataGroupId& idDataGroup);
   SEVERITY getEffectiveYear(DString& strEffectiveYear,const BFDataGroupId& idDataGroup);
   bool isInHistoricalRESPPeriod(const BFDataGroupId& idDataGroup);
   SEVERITY checkHistoricalTrade(const BFDataGroupId& idDataGroup);
   SEVERITY validateQESITotTxfr (const BFDataGroupId& idDataGroup);
   SEVERITY validateSAGESUpdate(const BFFieldId &idField, const BFDataGroupId& idDataGroup);
   SEVERITY validateSAGESACAmount (const BFDataGroupId &idDataGroup);
   SEVERITY validateTransferInNotionals (const BFDataGroupId &idDataGroup);
   SEVERITY validateTransferInNotionalAmt (const BFDataGroupId &idDataGroup, const BFFieldId &idField);
   SEVERITY validateTransferInNotionalAmt (const BFDataGroupId &idDataGroup, const BFFieldId &idField, const DString &dstrTradeType);
   SEVERITY doCalcQESIPre2007Amt (const BFDataGroupId& idDataGroup);
   SEVERITY setBeneficiaryCLBAmounts (const BFDataGroupId &idDataGroup, bool bSetValue = true);

private:
   static unsigned int getCurrentCounter() { return RESPTransfer::si_Counter; }
   static void incCurrentCounter() { RESPTransfer::si_Counter++; }
   SEVERITY setResidualCESGRelatedFields (const BFDataGroupId& idDataGroup);
   SEVERITY doCalcAsstUnAsstAmt (const BFDataGroupId& idDataGroup);
   SEVERITY doCalcSAGESAsstUnAsstAmt (const BFDataGroupId& idDataGroup);
   SEVERITY setFederalFieldsReadOnly (const BFDataGroupId& idDataGroup);
   BigDecimal getUCAmtLTDForBenef(const BFDataGroupId &idDataGroup);
   SEVERITY getRESPTransferNotional (RESPTransfer *& pRESPTransfer, const BFDataGroupId &idDataGroup);
   SEVERITY setNotionalBalanceFields (const BFDataGroupId& idDataGroup, bool bSetNotionals = false);
   SEVERITY doCalcNotionalBalanceAmt (const BFDataGroupId& idDataGroup, const BFFieldId &idFieldPur, const BFFieldId &idFieldRed, bool bTransferIn = false);
   SEVERITY doCalcPurRedNotionalAmt (const BFDataGroupId& idDataGroup, const BFFieldId &idFieldPur, const BFFieldId &idFieldRed, bool bTransferIn = false);
   SEVERITY doCalcQESIAsstUnAsstAmt (const BFDataGroupId& idDataGroup);

private:

   SEVERITY commonInit (bool bSetFieldsReadOnly, bool bSetNotionals, const BFDataGroupId& idDataGroup);
   bool m_bChoosingBenef;
   bool m_bTransferPrcntApplicable;
   DString m_dstrTradeYear;
   bool m_bIsNonTrustee;
   bool m_bInitNewLoaded;
   bool m_bReset;
   bool m_bFirstLoad;
   bool m_bIsNonTrusteeLoaded;
   bool m_bHistTxfr;
   bool m_bTradeYearApplicable;
   bool m_bNonTrusteeHistTxfr;
   bool m_bInitExisting;
   
   static unsigned int si_Counter;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
//
// $Log::   Y:/VCS/BF iFAST/ifastcbo/RESPTransfer.hpp-arc  $
//
//   Rev 1.19   Jul 29 2011 07:41:06   panatcha
//fix IN5285248 and IN2591262
//
//   Rev 1.18   Jul 25 2011 07:13:40   panatcha
//P0184541_FN01_InvescoQESItrans incidents
//
//   Rev 1.17   Jul 14 2011 08:12:16   panatcha
//DRAFT - IN2584478, IN5285248, IN2591262 
//
//   Rev 1.16   Jun 30 2011 00:28:20   panatcha
//P0184541_FN01_InvescoQESItrans
//
//   Rev 1.15   Jun 28 2011 10:31:24   panatcha
//P0184541_FN01_InvescoQESItrans
//
//   Rev 1.14   Oct 29 2010 05:29:54   kitticha
//PET0165541 FN03 - QESI Phase3.
//
//   Rev 1.13   Aug 13 2010 12:08:44   jankovii
//Sync up: IN 2200243 - Invesco Trimark Parent Cycle CY1287 {27 JULY 2010}
//
//   Rev 1.12   Jul 21 2010 01:33:50   dchatcha
//PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review, logic will be more simpler.
//
//   Rev 1.11   Jun 24 2010 07:44:12   dchatcha
//PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen.
// 
