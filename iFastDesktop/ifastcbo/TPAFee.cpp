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
// ^FILE   : TPAFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : August 2009
//
// ^CLASS    : TPAFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "tpafee.hpp"

#include "mgmtco.hpp"
#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("TPAFee");
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
   extern const I_CHAR * PURCHASE_TPA;
   extern const I_CHAR * REDEMPTION_TPA;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE;
}

//******************************************************************************
TPAFee::TPAFee (BFAbstractCBO &parent, const DString &feeCode) : TransFeeRate (parent, feeCode)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
TPAFee::~TPAFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
void TPAFee::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
   if (canBeInitialized (idDataGroup))
   {
      TransFeeRate::doInitWithDefaultValues (idDataGroup);
      setFieldNoValidate (ifds::TradeFeeOption, I_("1"), idDataGroup, false, true);//charge per system calculation
   }
}

//******************************************************************************
bool TPAFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
bool TPAFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType,
		   feeCode;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   getField (ifds::TransFeeCode, feeCode, idDataGroup, false);
	   return (( DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE) &&
		      feeCode == FEES::PURCHASE_TPA) ||
			  ( DSTCommonFunctions::codeInList (transType, TRADETYPE::REDEMPTION_LIKE) &&
			  feeCode == FEES::REDEMPTION_TPA)) &&
			  hasFeeParams (idDataGroup);
   }
   return false;
}

//******************************************************************************
bool TPAFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
   return hasFeeParamsContextChanged (idDataGroup);
}

//******************************************************************************
SEVERITY TPAFee::setFeeType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeType"));
   TransFeeRate::setFeeType (idDataGroup);
   setFieldReadOnly (ifds::FeeType, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TPAFee::setFeeProperties (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeProperties"));
   
   TransFeeRate::setFeeProperties (idDataGroup);   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TPAFee::doApplyRelatedChanges ( const BFFieldId &idField, 
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   if (TransFeeRate::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
      if (idField == ifds::TradeFeeOption)
      {
//always read only
         setFieldReadOnly (ifds::FeeType, idDataGroup, true);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TPAFee.cpp-arc  $
// 
//    Rev 1.1   Sep 29 2009 14:51:08   popescu
// Incident 1847231 - Default value of Option and Rate of Fee Type 112, 212, 113 and 213
// 
//    Rev 1.0   12 Aug 2009 15:36:58   popescu
// Initial revision.
// 
// 
 */