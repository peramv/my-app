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
//    Copyright 2010, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : ContractMaturityInstruction.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : ContractMaturityInstruction
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

class ContractMaturityInstructionList;
class ContractMatInstrBankList;

class IFASTCBO_LINKAGE ContractMaturityInstruction : public MFCanBFCbo
{
public:
	ContractMaturityInstruction( BFAbstractCBO &parent );
	virtual ~ContractMaturityInstruction();

	SEVERITY init	 ( const BFData& data );
	SEVERITY initNew ( const BFDataGroupId& idDataGroup);

	SEVERITY init( const BFDataGroupId& idDataGroup, const DString& dstrTrack = I_("N"),
                   const DString& dstrPageName = NULL_STRING );

	SEVERITY loadRedCodeSubstList(  const BFDataGroupId& idDataGroup );
  SEVERITY loadFileProcessor(const BFDataGroupId& idDataGroup);

	SEVERITY doValidateField( const BFFieldId& idField,
							  const DString& strValue,
							  const BFDataGroupId& idDataGroup );

	SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
									 const BFDataGroupId &idDataGroup );

	/*
	SEVERITY loadRedCodeSubstList(	const DString &account,	const DString &codeType,
									const BFDataGroupId &idDataGroup )
	*/

	SEVERITY init(const DString& dstrAccountNum);

	SEVERITY getBankInstructionsList( ContractMatInstrBankList *&pContractMatInstrBankList, 
									  const BFDataGroupId& idDataGroup, bool bCreate = true);

//protected:
	void doInitWithDefaultValues (  const BFDataGroupId& idDataGroup );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ContractMaturityInstruction.hpp-arc  $
//
//   Rev 1.5   Mar 13 2012 12:05:08   wp040100
//P0186484 FN05 - Contract Maturity Instructions Validation for PayType - EFT
//
//   Rev 1.4   Mar 05 2012 20:36:18   wp040100
//P0186484 FN05 - Contract Maturity Instruction Changes
//
//   Rev 1.3   Mar 02 2012 16:38:02   wp040100
//P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
//
//   Rev 1.2   Feb 23 2012 14:39:12   wp040100
//P0186484 FN05 - Contract Maturity Instruction Changes
//
//   Rev 1.1   Feb 21 2012 15:53:42   wp040100
//P0186484 FN05 - Contract Maturity Instruction Changes.
//
//   Rev 1.0   Feb 21 2012 15:32:32   wp040100
//Initial revision.
//
//
//
 * 
 * 
// 
*/
