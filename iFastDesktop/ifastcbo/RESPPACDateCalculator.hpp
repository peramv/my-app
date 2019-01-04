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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPPACDateCalculator.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RESPPACDateCalculator
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RESPPACDateCalculator : public MFCanBFCbo, private boost::noncopyable
{
public:

	RESPPACDateCalculator (BFAbstractCBO &parent);
	
	virtual ~RESPPACDateCalculator();
	
	SEVERITY init(const DString &dstrAcctCommitMstrUUID,
					  const DString &dstrPACDeff,
					  const DString &dstrPACDrawDeff,
				     const DString &dstrTrack = I_("N"),
				     const DString &dstrPageName = NULL_STRING);

private:

};
///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPPACDateCalculator.hpp-arc  $
//
//   Rev 1.0   Jun 26 2012 17:32:38   if991250
//Initial revision.
//
*/