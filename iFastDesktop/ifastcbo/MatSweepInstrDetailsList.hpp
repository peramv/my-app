#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : MatSweepInstrDetailsList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MatSweepInstrDetailsList
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

class SettlementInstr;
class MatSweepInstrDetails;

class IFASTCBO_LINKAGE MatSweepInstrDetailsList : public MFCanBFCbo, private boost::noncopyable
{
public:

	MatSweepInstrDetailsList( BFAbstractCBO &parent );
	virtual ~MatSweepInstrDetailsList();

	SEVERITY init ( const DString& dstrAccountNum,
                   const DString& dstrFund,
                   const DString& dstrClass,                     
                   const DString& dstrInstrType,
                   const DString& dstrTransNum,
                   const DString& dstrEffectiveDate,
                   const DString& dstrInvestId,
                   const DString& dstrGBCD,
                   const DString& dstrTransSeq,
                   const DString& dstrTrack = I_("N"),
                   const DString& dstrPageName = NULL_STRING);

	SEVERITY checkDuplicate (const DString &dstrRollOverType, const BFDataGroupId &idDataGroup);
	SEVERITY validateCashSweepDetails (const BFDataGroupId& idDataGroup);
	SEVERITY validateMaturityInterstDetails (const BFDataGroupId& idDataGroup);
	SEVERITY validatePercent (const BFDataGroupId &idDataGroup);
	SEVERITY validateAmount (const BFDataGroupId &idDataGroup);

   SEVERITY clone ( MatSweepInstrDetailsList *pMatSweepInstrDetailsList, const BFDataGroupId& idDataGroup);

   SEVERITY resetRemainingFlag (const DString &dstrSplitType, const BFDataGroupId& idDataGroup);

   SEVERITY validateFundClassMinAmount (const DString &dstrCashSweepMinAmount, const BFDataGroupId& idDataGroup);
   SEVERITY validateInterestInstruction (const BFDataGroupId& idDataGroup);
	
protected:

	virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
    SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

	SEVERITY validateAllDetails (const BFDataGroupId& idDataGroup);
	SEVERITY validateRemainingFlag (const BFDataGroupId &idDataGroup);

	BFData m_requestData;
	DString m_accountLevel;
};

//*******************************************************************************
/* $Log::   
//    Rev 1.2   Dec 14 2011 16:55:42   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 **/