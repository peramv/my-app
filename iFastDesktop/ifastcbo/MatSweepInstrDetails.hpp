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
//    Copyright 2004, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : MatSweepInstrDetails.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MatSweepInstrDetails
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

#define EXTRACT_VALUE(s, val) \
      pos = s.find (I_(",")); \
      val = s.substr (0, pos);

#define CHOP_STRING(s) \
         pos = s.find (I_(",")); \
         pos = pos != DString::npos && pos + 1 <= s.length() ? pos + 1 : DString::npos; \
         if (pos != DString::npos) \
            s = s.substr (pos); \
         else \
            s = NULL_STRING;

class GIAInvAttribList;
class FundLmtOverrideList;
class MatSweepInstrBankList;

class IFASTCBO_LINKAGE MatSweepInstrDetails : public MFCanBFCbo
{
public:

	MatSweepInstrDetails( BFAbstractCBO &parent );
	virtual ~MatSweepInstrDetails();

	SEVERITY init(const BFData& data );
	SEVERITY init(const BFDataGroupId& idDataGroup );
	SEVERITY initNew(const BFDataGroupId& idDataGroup );

	SEVERITY isDIFFund (const DString& dstrFund, bool &bIsDIFFund, const BFDataGroupId& idDataGroup);
	SEVERITY isGIAFund (const DString& dstrFund, bool &bIsGIAFund, const BFDataGroupId& idDataGroup);
	SEVERITY isSEGFund (const DString& dstrFund, bool &bIsSEGFund, const BFDataGroupId& idDataGroup);

	SEVERITY initClone (const MatSweepInstrDetails* pClone, const BFDataGroupId& idDataGroup);

	SEVERITY resetRemainingFlag (const DString &dstrSplitType, const BFDataGroupId& idDataGroup);

	
	SEVERITY getFundClassMinAmount (const DString &dstrFundCode, 
							       const DString &dstrClassCode, 
							       DString &dstrMinCashSweepAmount,
								   DString &dstrEWI,
							       const BFDataGroupId& idDataGroup);
   SEVERITY getBankInstructionsList(MatSweepInstrBankList *&pMatSweepInstrBankList, 
      const BFDataGroupId& idDataGroup, bool bCreate = true);

protected:

	virtual SEVERITY doValidateField( const BFFieldId& idField, 
		                              const DString& strValue, 
									  const BFDataGroupId& idDataGroup );   
	virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
    SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

	virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
	
	SEVERITY validateFundClass (const BFDataGroupId &idDataGroup);
	SEVERITY validateAssociatedNum (const DString &dstrAcctountNum, const BFDataGroupId& idDataGroup);
	SEVERITY validateRolloverType (const DString &dstrRollOverType, const BFDataGroupId& idDataGroup);
	SEVERITY validatePercent (const DString &dstrPercent, const BFDataGroupId &idDataGroup);
	SEVERITY validateAddressCode (const DString &dstrAddressCode, const BFDataGroupId &idDataGroup);
	SEVERITY validateMaturityBank (const BFDataGroupId &idDataGroup);
	SEVERITY validateRolloverForInstrType(const BFDataGroupId &idDataGroup);

	SEVERITY setCASHDIFSEGFieldsReadOnly (const BFDataGroupId &idDataGroup, bool bInit = false);
	SEVERITY setGIAFieldsReadOnly (const BFDataGroupId &idDataGroup, bool bInit = false);
	SEVERITY setBusinessTypeFieldsReadOnly (const BFDataGroupId &idDataGroup);
	SEVERITY setRollOverFieldsReadOnly (const BFDataGroupId &idDataGroup);
	SEVERITY setRemainingFlagFieldsReadOnly (const BFDataGroupId &idDataGroup);

	SEVERITY redirectRelatedChanges (const DString &dstrRolloverType, const BFDataGroupId &idDataGroup);
	SEVERITY reinvestRelatedChanges (const DString &dstrRolloverType, const BFDataGroupId &idDataGroup);
	SEVERITY cashRelatedChanges (const DString &dstrRolloverType, const BFDataGroupId &idDataGroup);
	SEVERITY payTypeRelatedChanges (const DString &dstrPayType, const BFDataGroupId &idDataGroup);
	SEVERITY fundClassRelatedChanges (const BFDataGroupId &idDataGroup);
	SEVERITY bankAddressRelatedChanges (const DString &dstrPayType, const BFDataGroupId& idDataGroup);
	SEVERITY remainingFlagRelatedChanges (const BFDataGroupId& idDataGroup);
	SEVERITY currencyRelatedChanges (const BFDataGroupId& idDataGroup);
	SEVERITY fileProcessorRelateChanges (const BFDataGroupId& idDataGroup);
	SEVERITY intCalcMthdRelatedChanges(const BFDataGroupId &idDataGroup, bool bInit = false);
	SEVERITY intAdditionalAmtRelatedChanges(const BFDataGroupId &idDataGroup, bool bInit = false);

	SEVERITY cashSweepDefaults (const BFDataGroupId& idDataGroup);


	SEVERITY commInit (const BFDataGroupId& idDataGroup);

	SEVERITY setAllFeildsReadOnly (const BFDataGroupId &idDataGroup);

	SEVERITY setGIFundFields (const BFDataGroupId &idDataGroup);


	SEVERITY getGIFundDefaults ( GIAInvAttribList *&pGIAInvAttribList,
								 const DString &fundCode,
								 const DString &classCode,
								 const DString &effectiveDate,
                         const BFDataGroupId &idDataGroup,
                         bool doSideEffects = true);

	SEVERITY getFundCurrency (const DString &dstrFundCode, 
							  const DString &dstrClassCode, 
							  DString &dstrCurrency,
							  const BFDataGroupId& idDataGroup);

	SEVERITY getFundLmtOverrideList (FundLmtOverrideList *&pFundLmtOverrideList,
                                     const DString& fundCode,
                                     const DString& classCode,
                                     const BFDataGroupId &idDataGroup);



	SEVERITY setFundClassMinAmount (const BFDataGroupId& idDataGroup);
   SEVERITY businessTypeRelatedChanges (const BFDataGroupId &idDataGroup);//P0186486_FN15_The Source of Funds
   SEVERITY loadBusinessTypeSubslist( const BFDataGroupId &idDataGroup);
   void ValidateRefNum(const BFDataGroupId& idDataGroup);
   SEVERITY setCommReductionEditable(const BFDataGroupId& idDataGroup);

private:
	DString m_multiCurrency;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatSweepInstrDetails.hpp-arc  $
//
//   Rev 1.17   Aug 03 2012 20:11:16   wp040240
//IN3014673 - P0181067 Added Error condition to avoid cash instructions  to registered client accounts
//
//   Rev 1.16   May 04 2012 11:52:12   panatcha
//P0186486_FN15_The Source of Funds
//
//   Rev 1.15   Apr 05 2012 14:14:46   jankovii
//IN 2904085 - Automatin Instructions - For reinvestment, the destination fileds s/s pre-popula
//
//   Rev 1.14   Mar 21 2012 13:23:38   jankovii
//IN 2889348 - Maturity Processing _ Desktop Issues_List 1_EFT issues
//
//   Rev 1.13   Feb 09 2012 13:12:36   jankovii
//IN 2835682 - P0186477FN03 -Database error when accessing Maturity/ Interest Screen
//
//   Rev 1.12   Feb 01 2012 15:06:10   if991250
//retrieve the bank list
//
//   Rev 1.11   Jan 31 2012 19:14:06   jankovii
//IN 2826242- Maturity/Interest Instruction on Trading Screen
//
//   Rev 1.10   Jan 26 2012 19:35:34   jankovii
//IN 2817696 - P0186477FN03-Cash Sweep Configuration Issues
//
//   Rev 1.9   Jan 20 2012 11:15:20   jankovii
//IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
//
//   Rev 1.8   Jan 13 2012 11:10:26   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions - clone
//
//   Rev 1.7   Jan 11 2012 16:01:30   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.6   Jan 06 2012 12:22:14   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.5   Dec 21 2011 15:31:24   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.4   Dec 19 2011 20:32:14   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.3   Dec 16 2011 15:59:30   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.4   Dec 16 2011 15:54:18   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.3   Dec 15 2011 10:24:44   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.2   Dec 14 2011 16:55:42   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 * 
 */