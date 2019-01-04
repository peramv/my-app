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
// ^FILE   : GMWBValidation.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : GMWBValidation
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

class IFASTCBO_LINKAGE GMWBValidation : public MFCanBFCbo, private boost::noncopyable
{
public:

	static void buildKey (const DString &accountNum,
						  const DString &validateType,
						  const DString &transNum,
						  const DString &fundCode,
						  const DString &classCode,
						  const DString &effectiveDate,
						  const DString &stopDate,
						  const DString &payOption,
						  const DString &recId,
						  const DString &runMode,
						  DString &strKey);

	SEVERITY validateGMWB (const DString &fundCode, const DString &classCode, const BFDataGroupId& idDataGroup);

public:

	GMWBValidation (BFAbstractCBO &parent);
	
	virtual ~GMWBValidation();
	
	SEVERITY init(const DString &accountNum,
				  const DString &validateType,
				  const DString &transNum,
				  const DString &fundCode,
				  const DString &classCode,
				  const DString &effectiveDate,
				  const DString &stopDate,
				  const DString &payOption,
				  const DString &recId,
				  const DString &runMode,
				  const DString &dstrTrack = I_("N"),
				  const DString &dstrPageName = NULL_STRING);

private:

};
///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GMWBValidation.hpp-arc  $
//
//   Rev 1.1   May 14 2012 15:38:22   jankovii
//P0186481 FN07-GWA LWA Payment Options for SWP RRIF v4.
//
//   Rev 1.0   May 11 2012 13:17:10   jankovii
//Initial revision.

*/