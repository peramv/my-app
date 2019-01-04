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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AggregatedFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Jan 2005
//
// ^CLASS    : AggregatedFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "aggregatedfee.hpp"

#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("AggregatedFee");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

namespace CND
{  // Conditions used
}

namespace FEES
{
   extern const I_CHAR * AGGREGATED_EXTERNAL_CHARGE;
   extern const I_CHAR * AGGREGATED_COMMISSION;
   extern const I_CHAR * MISC_COMMISSION;
   extern const I_CHAR * DISCOUNT_RATE;
   extern const I_CHAR * REBATE_AMOUNT;
}

//******************************************************************************
AggregatedFee::AggregatedFee (BFAbstractCBO &parent, const DString &feeCode) : TransFeeRate (parent, feeCode)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
AggregatedFee::~AggregatedFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
void AggregatedFee::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
//this fee should not be initialized
   if (canBeInitialized (idDataGroup))
   {
      assert (0);
   }
}

//******************************************************************************
void AggregatedFee::doReset (const BFDataGroupId &idDataGroup)
{
//nothing to do...
}


//******************************************************************************
SEVERITY AggregatedFee::setFeeProperties (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeProperties"));
   TransFeeRate::setFeeProperties (idDataGroup);
//everything is read only
   setFieldReadOnly (ifds::FeeRate, idDataGroup, true);
   setFieldReadOnly (ifds::FeeType, idDataGroup, true);
   setFieldReadOnly (ifds::TradeFeeOption, idDataGroup, true);
   //do a set field no validate so validation will not be triggered,
   //this is useful if somehow the set-up of view 253 is wrong
   setFieldNoValidate ( ifds::TradeFeeOption, I_("1"), idDataGroup, false,  //charge per system calculation
                        true, //valid
                        true, //side effect
                        false);  //no related changes
   setFieldReadOnly (ifds::Currency, idDataGroup, true);
   setFieldReadOnly (ifds::ChargeOption, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AggregatedFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
//allways applies 
   return true;
}

//******************************************************************************
bool AggregatedFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   //only applies for pending trades, that are part of an aggregated order
	   assert (getParent() && getParent()->getParent());
	   Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

	   return !pTrade->isNew();
   }
   return false;
}

//******************************************************************************
bool AggregatedFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
   return false; //should not be refreshed
}

//******************************************************************************
SEVERITY AggregatedFee::setFeeDefault (const BFDataGroupId &idDataGroup)
{
//no defaults this method should not be called   
   assert (0);
   return NO_CONDITION;
}

//******************************************************************************
SEVERITY AggregatedFee::setFeeMinMax (const BFDataGroupId &idDataGroup)
{
//nothing to be done here...   
   return NO_CONDITION;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AggregatedFee.cpp-arc  $
// 
//    Rev 1.3   Feb 14 2005 18:39:50   popescu
// 240257, do not apply related changes when setting the trade fee option to '1'
// 
//    Rev 1.2   Feb 14 2005 17:30:16   popescu
// 240257, handling of fee code 116/Rebate Amount
// 
//    Rev 1.1   Feb 04 2005 11:53:58   popescu
// PET 1117/56, handling of two new fees 117/119
// 
//    Rev 1.0   Jan 29 2005 16:39:28   popescu
// Initial revision.
// 
// 
 */