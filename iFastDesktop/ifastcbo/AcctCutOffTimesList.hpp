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
//    Copyright 2005, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : AcctCutOffTimesList.hpp
// ^CLASS  : AcctCutOffTimesList
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AcctCutOffTimesList : public MFCanBFCbo
{
public:

	AcctCutOffTimesList( BFAbstractCBO &parent );
	virtual ~AcctCutOffTimesList();

	SEVERITY init( const DString& AccountNum,
					const DString& EntityId = NULL_STRING,
					const DString& BrokerCode = NULL_STRING,
					const DString& dstrTrack = I_("N"),
					const DString& dstrPageName = NULL_STRING );
	SEVERITY init();
	SEVERITY getMore();
	DString getCutOffLevel();
	DString getBrokerCode();

protected:

	virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
	virtual SEVERITY doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup );
	SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

	BFData	m_requestData;
	DString	dstrCutOffLevel;
	DString	dstrBrokerCode;
};


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCutOffTimesList.hpp-arc  $
//
//   Rev 1.2   Jul 21 2006 14:08:16   jankovii
//PET 2192 FN02 - Dealings-Sender Cut-Off Time.
//
//   Rev 1.1   Jul 25 2005 15:52:54   hernando
//PET1250 FN01 - Added init() as a stub for new accounts.
//
//   Rev 1.0   Jul 05 2005 17:17:14   hernando
//Initial revision.
