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
//    Copyright 2018 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundSuspensionValidation.hpp
// ^AUTHOR : 
// ^DATE   : 10 May 2018
//
// ^CLASS    : FundSuspensionValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :This class used to validate the suspened fund and will 
//						show warning/Error message to  user
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

class IFASTCBO_LINKAGE FundSuspensionValidation : public MFCanBFCbo, private boost::noncopyable
{

public:
	FundSuspensionValidation(BFAbstractCBO &parent);
	virtual ~FundSuspensionValidation();

	   SEVERITY init( const DString &strRunMode, 
                  const DString &strFromFundCode,
                  const DString &strFromClassCode, 
                  const DString &strTransType, 
                  const DString &strDealDate, 
                  const DString &strDealTime,
				  const DString &strFundToCode, 
				  const DString &strClassToCode,
				  const DString &strDepositType, 
				  const DString &strRedCode,
				  const DString &dstrTrack = I_("N"), 
				  const DString &dstrPageName = NULL_STRING
				  );  

	SEVERITY addConditions ();

protected:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Transfer.hpp-arc  $*/

//  Rev 1.0   May 10 2018 15:24:04   Amit k Mallick
//	Initial revision.