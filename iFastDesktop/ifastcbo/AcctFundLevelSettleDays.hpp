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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctFundLevelSettleDays.hpp
// ^AUTHOR : 
// ^DATE   : February 2017
//
// ^CLASS    : AcctFundLevelSettleDays
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

class IFASTCBO_LINKAGE AcctFundLevelSettleDays : public MFCanBFCbo, private boost::noncopyable
{

public:
	AcctFundLevelSettleDays(BFAbstractCBO &parent);
	virtual ~AcctFundLevelSettleDays();

	static void buildKey( DString &strKey,
						  const DString &dstrAccountNum,
						  const DString &dstrFundCode,
						  const DString &dstrClassCode,
						  const DString &dstrTransType,
						  const DString &dstrSettleDays,
						  const DString &dstrStartDate );

	SEVERITY init( const DString &dstrAccountNum, 
				   const DString &dstrfundCode, 
				   const DString &dstrClassCode, 
				   const DString &dstrTransType, 
				   const DString &dstrSettleDays, 
				   const DString &dstrStartDate,
				   const DString &dstrTrack = I_("N"), 
				   const DString &dstrPageName = NULL_STRING);

	SEVERITY addConditions ();

protected:

private:
	DString _fundCode, _classCode;
	BFData *requestData;

};