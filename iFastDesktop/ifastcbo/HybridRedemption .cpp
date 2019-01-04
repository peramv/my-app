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
// ^FILE   : HybridRedemption.cpp
// ^AUTHOR :    
// ^DATE   : July, 2009
//
// ^CLASS    : HybridRedemption - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "hybridRedemption.hpp"

namespace
{
	//Trace literals
	const I_CHAR * const CLASSNAME = I_ ("HybridRedemption");
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const HYBRID_REDEMPTION;
}

//******************************************************************************
HybridRedemption::HybridRedemption (BFAbstractCBO &parent) : Redemption (parent), Trade (parent)
{
	TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}


//******************************************************************************
HybridRedemption::~HybridRedemption ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY HybridRedemption::doInit (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

	setFieldNoValidate ( ifds::TradesTransType, TRADETYPE::HYBRID_REDEMPTION, idDataGroup, false);
   
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY HybridRedemption::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("preInitWithDefaultValues"));
	
	//base class call   
	Redemption::preInitWithDefaultValues (idDataGroup);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void HybridRedemption::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInitWithDefaultValues"));
	
	//call base class
	Redemption::doInitWithDefaultValues (idDataGroup);
}

//***************************************************************************************************
SEVERITY HybridRedemption::doInit (const BFData &data)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

	Redemption::doInit (data);

	return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY HybridRedemption::doApplyRelatedChanges ( const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if (Redemption::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
	{
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY HybridRedemption::doValidateField ( const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
   
   if (Redemption::doValidateField (idField, strValue, idDataGroup)  <= WARNING)
   {
   }
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY HybridRedemption::doValidateAll ( const BFDataGroupId& idDataGroup, 
                                   long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doValidateAll"));

	Redemption::doValidateAll( idDataGroup, true );
	
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
/* $Log::
*/
