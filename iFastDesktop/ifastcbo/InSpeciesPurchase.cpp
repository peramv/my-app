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
// ^FILE   : InSpeciesPurchase.cpp
// ^AUTHOR :   
// ^DATE   : July, 2009
//
// ^CLASS    : InSpeciesPurchase - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "InSpeciesPurchase.hpp"

namespace TRADETYPE
{
	extern CLASS_IMPORT I_CHAR * const INSPECIES_PURCHASE;
}

namespace
{
	//Trace literals
	const I_CHAR * const CLASSNAME = I_ ("InSpeciesPurchase");
}


//******************************************************************************
InSpeciesPurchase::InSpeciesPurchase (BFAbstractCBO &parent) : Purchase (parent), Trade (parent)
{
	TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}


//******************************************************************************
InSpeciesPurchase::~InSpeciesPurchase ()
{
	TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY InSpeciesPurchase::doInit (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

	setFieldNoValidate (ifds::TradesTransType, TRADETYPE::INSPECIES_PURCHASE, idDataGroup, false);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY InSpeciesPurchase::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME,  I_("preInitWithDefaultValues"));
	   
	Purchase::preInitWithDefaultValues (idDataGroup);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void InSpeciesPurchase::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   Purchase::doInitWithDefaultValues (idDataGroup);
}

//***************************************************************************************************
SEVERITY InSpeciesPurchase::doApplyRelatedChanges ( const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if (Purchase::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
	{
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

/* $Log::   
*/
