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
// ^FILE   : ContractMaturityInstructionList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : ContractMaturityInstructionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class ContractMaturityInstruction;

class IFASTCBO_LINKAGE ContractMaturityInstructionList : public MFCanBFCbo, private boost::noncopyable
{
public:
   ContractMaturityInstructionList( BFAbstractCBO &parent );
   virtual ~ContractMaturityInstructionList();

	SEVERITY init	 (	const DString& dstrAccountNum,
						const DString& dstrContractType,
						const DString& dstrContractTypeId,
						const BFDataGroupId& idDataGroup );

	SEVERITY initNew (	const DString& dstrAccountNum, 
						const DString& dstrCotAcctRid );

	SEVERITY init	 (	const BFDataGroupId& idDataGroup );

	SEVERITY getMore();

	void setContractMatInstrAddFields (const DString& dstrAccountNum,		const DString& dstrCotAcctRid);
	void getContractMatInstrAddFields (		 DString& dstrAccountNum,			  DString& dstrCotAcctRid);
	void getCotAcctRid				  (		 DString& dstrCotAcctRid );

protected:
	SEVERITY doCreateNewObject  ( BFCBO *& pBase, DString &strKey,  
									  const BFDataGroupId& idDataGroup );

	SEVERITY doCreateObject			( const BFData& data, BFCBO*& pObjOut );

    SEVERITY doValidateAll			( const BFDataGroupId& idDataGroup,		long lValidateGroup );

	SEVERITY doApplyRelatedChanges	( const BFFieldId &idField, 
									  const BFDataGroupId &idDataGroup);

	SEVERITY doValidateField		( const BFFieldId &idField, 
									  const DString &strValue, 
									  const BFDataGroupId &idDataGroup);

private:
	BFData	m_requestData;

	DString m_dstrAccountNum,
			m_dstrCotAcctRid;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ContractMaturityInstructionList.hpp-arc  $
//
//   Rev 1.1   Mar 16 2012 17:45:24   wp040100
//P0186484 FN05 - Contract Maturity Instruction Changes
//
//   Rev 1.0   Feb 21 2012 15:34:40   wp040100
//Initial revision.
//
//
//
 * 
 * 
// 
*/
