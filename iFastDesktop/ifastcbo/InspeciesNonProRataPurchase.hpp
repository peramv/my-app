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
// ^FILE   : InSpeciesPurchase.hpp
// ^AUTHOR : 
// ^DATE   : July, 2009
//
// ^CLASS    : InSpeciesPurchase
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "InSpeciesPurchase.hpp"

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTCBO_LINKAGE InSpeciesNonProRataPurchase : public InSpeciesPurchase
{
public:
	InSpeciesNonProRataPurchase (BFAbstractCBO &parent);
	virtual ~InSpeciesNonProRataPurchase();

protected:
	virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);


private:
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/InspeciesNonProRataPurchase.hpp-arc  $
//
//   Rev 1.0   Jul 19 2012 19:56:44   wp040133
//Initial revision.
// 