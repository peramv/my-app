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
// ^FILE   : InSpeciesRedemption.cpp
// ^AUTHOR :  
// ^DATE   : July, 2009
//
// ^CLASS    : InSpeciesRedemption - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "InSpeciesRedemption.hpp"

namespace TRADETYPE
{
	extern CLASS_IMPORT I_CHAR * const INSPECIES_REDEMPTION;
}

namespace
{
	//Trace literals
	const I_CHAR * const CLASSNAME = I_ ("InSpeciesRedemption");
}


//******************************************************************************
InSpeciesRedemption::InSpeciesRedemption (BFAbstractCBO &parent) : Redemption (parent), Trade (parent)
{
	TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}


//******************************************************************************
InSpeciesRedemption::~InSpeciesRedemption ()
{
	TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY InSpeciesRedemption::doInit (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

	setFieldNoValidate (ifds::TradesTransType, TRADETYPE::INSPECIES_REDEMPTION, idDataGroup, false);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY InSpeciesRedemption::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME,  I_("preInitWithDefaultValues"));
	   
	Redemption::preInitWithDefaultValues (idDataGroup);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void InSpeciesRedemption::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   Redemption::doInitWithDefaultValues (idDataGroup);
}

//***************************************************************************************************
SEVERITY InSpeciesRedemption::doApplyRelatedChanges ( const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if (Redemption::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
	{
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

/* $Log::   
*/
