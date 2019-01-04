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
// ^FILE   : MatSweepInstrList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MatSweepInstrList
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

class MatSweepInstr;

class IFASTCBO_LINKAGE MatSweepInstrList : public MFCanBFCbo, private boost::noncopyable
{
public:

	MatSweepInstrList( BFAbstractCBO &parent );
	virtual ~MatSweepInstrList();

	SEVERITY init ( const DString& dstrAccountNum,
                    const DString& dstrInstructionType,
                    const DString& dstrFund,
                    const DString& dstrClass,
                    const DString& dstrTransNum,
					const DString& dstrTransId,
					const DString& dstrIntInvestId,
				    const DString& dstrLevel,
					const DString& dstrAmount,
					const DString& dstrAccuredAmount,
                    const BFDataGroupId& idDataGroup,
                    const DString& dstrTrack = I_("N"),
                   const DString& dstrPageName = NULL_STRING );
   SEVERITY clone ( const DString& objectKey, 
                    const BFDataGroupId& idDataGroup);

   SEVERITY checkDuplicate (const MatSweepInstr *pMatSweepInstrToCheck, 
							const BFDataGroupId &idDataGroup);
   SEVERITY checkActiveDuplicate (const MatSweepInstr *pMatSweepInstrToCheck, 
							      DString &dstrHasDuplicate,
							      const BFDataGroupId &idDataGroup);

   SEVERITY validateMaturityInterestInstr (const MatSweepInstr *pMatSweepInstrToCheck, const BFDataGroupId &idDataGroup);
   SEVERITY setTransId (const DString &dstrTransId, const BFDataGroupId &idDataGroup);

protected:

   virtual SEVERITY doCreateObject (const BFData& data, BFCBO*& pObjOut);
   virtual SEVERITY doCreateNewObject (BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup);
   SEVERITY doValidateAll (const BFDataGroupId& idDataGroup, long lValidateGroup);

	BFData m_requestData;

	DString m_dstrMatSwp;
	DString m_dstrLevel;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatSweepInstrList.hpp-arc  $
//
//   Rev 1.11   Mar 28 2012 15:27:20   jankovii
//IN 2889383 - P0186477_FN05_Maturity Processing Dsktp issues_LIST 1_Seg_intrnl errr_min issues
//
//   Rev 1.10   Mar 07 2012 14:18:58   jankovii
//IN 2873354 - P0186477FN03- Deleting Instruction on Processed Investments
//
//   Rev 1.9   Mar 05 2012 11:21:48   jankovii
//IN 2859411 - P0186477_FN02_Interest Instruction-Err displayed on split type 'Amount' instrctn
//
//   Rev 1.8   Jan 31 2012 19:12:18   jankovii
//IN 2826242- Maturity/Interest Instruction on Trading Screen
//
//   Rev 1.7   Jan 20 2012 09:47:00   jankovii
//IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
//
//   Rev 1.6   Jan 11 2012 16:00:26   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.5   Jan 06 2012 12:28:46   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.4   Dec 19 2011 20:33:48   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.3   Dec 16 2011 15:50:20   popescu
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.2   Dec 14 2011 16:55:18   popescu
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 * 
 */
