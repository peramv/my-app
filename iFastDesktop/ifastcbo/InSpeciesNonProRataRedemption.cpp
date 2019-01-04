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
//
//******************************************************************************
//
// ^FILE   : InspeciesNonProRataRedemption.cpp
// ^AUTHOR : Robbins Kuriakose 
// ^DATE   : July, 2012
//
// ^CLASS    : InspeciesNonProRataRedemption
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "InspeciesNonProRataRedemption.hpp"

namespace TRADETYPE
{
	extern CLASS_IMPORT I_CHAR * const INSP_NON_PRO_RATA_REDEMPTION;
}

namespace
{
	//Trace literals
	const I_CHAR * const CLASSNAME = I_ ("InSpeciesNonProRataRedemption");
}


//******************************************************************************
InSpeciesNonProRataRedemption::InSpeciesNonProRataRedemption (BFAbstractCBO &parent) : InSpeciesRedemption (parent), Trade (parent)
{
	TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}


//******************************************************************************
InSpeciesNonProRataRedemption::~InSpeciesNonProRataRedemption ()
{
	TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY InSpeciesNonProRataRedemption::doInit (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

	setFieldNoValidate (ifds::TradesTransType, TRADETYPE::INSP_NON_PRO_RATA_REDEMPTION, idDataGroup, false);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/InSpeciesNonProRataRedemption.cpp-arc  $
// 
//    Rev 1.0   Jul 19 2012 20:00:56   wp040133
// Initial revision.
// 
