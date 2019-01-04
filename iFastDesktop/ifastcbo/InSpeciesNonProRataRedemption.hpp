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
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : InSpeciesNonProRataRedemption.hpp
// ^AUTHOR :  Robbins Kuriakose
// ^DATE   : July, 2012
//
// ^CLASS    : InSpeciesNonProRataReedemption
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "InSpeciesRedemption.hpp"

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTCBO_LINKAGE InSpeciesNonProRataRedemption : public InSpeciesRedemption
{
public:
	InSpeciesNonProRataRedemption (BFAbstractCBO &parent);
	virtual ~InSpeciesNonProRataRedemption();

protected:
	virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);

private:
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/InSpeciesNonProRataRedemption.hpp-arc  $
//
//   Rev 1.0   Jul 19 2012 20:02:10   wp040133
//Initial revision.
// 