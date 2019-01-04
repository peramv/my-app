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
// ^FILE   : MatSweepInstr.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MatSweepInstr
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

#include <ifastdataimpl\dse_dstc0427_req.hpp> 
#include <ifastdataimpl\dse_dstc0427_vw.hpp> 
#include <ifastdataimpl\dse_dstc0427_vwrepeat_record.hpp> 

class MatSweepInstrDetailsList;
class FundLmtOverrideList;

class IFASTCBO_LINKAGE MatSweepInstr : public MFCanBFCbo
{
public:

	MatSweepInstr( BFAbstractCBO &parent );
	virtual ~MatSweepInstr();

	SEVERITY init (const BFData& data, 
		           const DString& matSwp, 
				   const DString& level);
	SEVERITY initNew (const DString& accountNum,
			         const DString& matSwp,
					 const DString& level,
                     const BFDataGroupId& idDataGroup );

	SEVERITY getMatSweepDetailsList ( MatSweepInstrDetailsList *&pMatSweepInstrDetailsList, 
									          const BFDataGroupId& idDataGroup);
   SEVERITY initClone ( MatSweepInstr* pClone, 
                        const BFDataGroupId& idDataGroup);
   bool isAccountLevel ()
   {
	   return m_Level == I_("Acct") ? true : false;
   }

	SEVERITY setMinimumAmount (const DString &dstrFundCode, 
							   const DString &dstrClassCode, 
							   const DString &dstrMinAmount,
							   const BFDataGroupId& idDataGroup);

	SEVERITY checkDuplicateActiveInstr (DString &dstrActiveInstrExists, const BFDataGroupId& idDataGroup);

	SEVERITY getFundLmtOverrideList (FundLmtOverrideList *&pFundLmtOverrideList,
                                     const DString& fundCode,
                                     const DString& classCode,
                                     const BFDataGroupId &idDataGroup);

	bool isRuleTypeEnabledForFundClass (const DString &dstrFundCode, 
									    const DString &dstrClassCode, 
									    const DString ruleType,
									    DString &dstrEWI,
									    const BFDataGroupId& idDataGroup);

protected:

	virtual SEVERITY doValidateField( const BFFieldId& idField, 
		                               const DString& strValue, 
									          const BFDataGroupId& idDataGroup );   
	virtual void doInitWithDefaultValues (const BFDataGroupId& idDataGroup);
	virtual SEVERITY doApplyRelatedChanges ( const BFFieldId& idField, 
                                            const BFDataGroupId& idDataGroup );

    SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

	SEVERITY commInit (const BFDataGroupId& idDataGroup);
	SEVERITY validateFundClass (const BFDataGroupId &idDataGroup);
	SEVERITY validateSelectedAmount (const BFDataGroupId &idDataGroup);
	SEVERITY validateInstructionType (const DString &dstrInstrType, const BFDataGroupId &idDataGroup);

	SEVERITY getTermsList (DString &dstrSimpleTermList, const BFDataGroupId &idDataGroup);

	SEVERITY setAllFeildsReadOnly (const BFDataGroupId &idDataGroup);
	SEVERITY setCashSweepBalFeildsReadOnly (const BFDataGroupId &idDataGroup);
	SEVERITY splitTypeRelatedChanges (const BFDataGroupId &idDataGroup);

private:

	DString m_matSwp;
	DString m_Level;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatSweepInstr.hpp-arc  $
//
//   Rev 1.11   Apr 22 2012 18:48:50   jankovii
//IN 2847670 & 2815937
//
//   Rev 1.10   Mar 28 2012 15:25:24   jankovii
//IN 2889383 - P0186477_FN05_Maturity Processing Dsktp issues_LIST 1_Seg_intrnl errr_min issues
//
//   Rev 1.9   Jan 31 2012 19:10:40   jankovii
//IN 2826242- Maturity/Interest Instruction on Trading Screen
//
//   Rev 1.8   Jan 26 2012 19:26:48   jankovii
//IN 2817696 - P0186477FN03-Cash Sweep Configuration Issues
//
//   Rev 1.7   Jan 20 2012 11:17:00   jankovii
//IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
//
//   Rev 1.6   Jan 11 2012 15:59:28   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.5   Dec 19 2011 20:30:44   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.4   Dec 19 2011 06:01:38   popescu
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.3   Dec 16 2011 15:55:20   jankovii
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
//
//   Rev 1.2   Dec 14 2011 16:55:34   popescu
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 * 
 */
