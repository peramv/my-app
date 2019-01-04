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
// ^FILE   : HybridPurchase.cpp
// ^AUTHOR :    
// ^DATE   : July, 2009
//
// ^CLASS    : HybridPurchase - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "hybridpurchase.hpp"

namespace
{
	//Trace literals
	const I_CHAR * const CLASSNAME = I_ ("HybridPurchase");
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const HYBRID_PURCHASE;
}

//******************************************************************************
HybridPurchase::HybridPurchase (BFAbstractCBO &parent) : Purchase (parent), Trade (parent)
{
	TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}


//******************************************************************************
HybridPurchase::~HybridPurchase ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY HybridPurchase::doInit (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

	setFieldNoValidate ( ifds::TradesTransType, TRADETYPE::HYBRID_PURCHASE, idDataGroup, false);
   
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY HybridPurchase::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("preInitWithDefaultValues"));
	
	//base class call   
	Purchase::preInitWithDefaultValues (idDataGroup);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void HybridPurchase::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInitWithDefaultValues"));
	
	//call base class
	Purchase::doInitWithDefaultValues (idDataGroup);
}

//***************************************************************************************************
SEVERITY HybridPurchase::doInit (const BFData &data)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

	Purchase::doInit (data);

	return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY HybridPurchase::doApplyRelatedChanges ( const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if (Purchase::doApplyRelatedChanges (idField, idDataGroup)  <= WARNING)
	{
	}
	
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY HybridPurchase::doValidateField ( const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
   
   if (Purchase::doValidateField (idField, strValue, idDataGroup)  <= WARNING)
   {
   }
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY HybridPurchase::doValidateAll ( const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doValidateAll"));

	Purchase::doValidateAll( idDataGroup, true );
	
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
/* $Log::
*/
