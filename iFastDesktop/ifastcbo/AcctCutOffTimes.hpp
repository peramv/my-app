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
// ^FILE     : AcctCutOffTimes.hpp
// ^CLASS    : AcctCutOffTimes
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class MsgActivityList;

class IFASTCBO_LINKAGE AcctCutOffTimes : public MFCanBFCbo
{
public:

	AcctCutOffTimes( BFAbstractCBO &parent, const DString& cutOffLevel);
	virtual ~AcctCutOffTimes();
	SEVERITY init( const BFData& data );
	SEVERITY init( const BFDataGroupId& idDataGroup );
	virtual void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);
	SEVERITY doValidateField( const BFFieldId& idField,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup );
    SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );


private:

	void initSubSets();
	void setRequiredFields (const BFDataGroupId& idDataGroup);

	SEVERITY setFundByFundNumber( const BFDataGroupId &idDataGroup, const DString &dstrFundNumber);
	SEVERITY setFundByFundClass( const BFDataGroupId &idDataGroup, const DString &dstrFundCode, const DString &dstrClassCode);

   	SEVERITY validateFundCode (const BFDataGroupId &idDataGroup, const DString &dstrFundCode);
	SEVERITY validateFundNumber(const BFDataGroupId& idDataGroup);
	SEVERITY validateClassCode (const BFDataGroupId &idDataGroup, const DString &dstrClassCode);

    DString dstrFundGroupList;
};

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCutOffTimes.hpp-arc  $
//
//   Rev 1.2   Jul 26 2006 14:53:22   jankovii
//PET 2192 FN02 - Dealings Sender Cut Off Time.
//
//   Rev 1.1   Jul 21 2006 14:07:12   jankovii
//PET 2192 FN02 - Dealings-Sender Cut-Off Time.
//
//   Rev 1.0   Jul 05 2005 17:16:58   hernando
//Initial revision.

