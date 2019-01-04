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
// ^FILE   : RedemptionFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Jan 2005
//
// ^CLASS    : RedemptionFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "redemptionfee.hpp"

#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "trade.hpp"
#include "splitcommission.hpp"
#include "splitcommissionlist.hpp"

#include <ifastdataimpl\dse_dstc0121_vw.hpp>

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("RedemptionFee");
}

namespace ifds
{
//management co options
//fee fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId LoadType;
}

namespace CND
{  // Conditions used
}

namespace FEES
{
   extern const I_CHAR * REDEMPTION;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
}

//******************************************************************************
RedemptionFee::RedemptionFee (BFAbstractCBO &parent) : AcquisitionFee (parent, FEES::REDEMPTION)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
RedemptionFee::~RedemptionFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
void RedemptionFee::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
   AcquisitionFee::doInitWithDefaultValues (idDataGroup);
}

//******************************************************************************
bool RedemptionFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return SplitCommission::isTypeZERO (getWorkSession ());
}

//******************************************************************************
bool RedemptionFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   return transType == TRADETYPE::REDEMPTION &&
		      !isFeeWaivedForAccount (idDataGroup);   
   }
   return false;
}

//******************************************************************************
bool RedemptionFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
   return hasFieldContextChanged (ifds::Amount, idDataGroup);
}

//******************************************************************************
SEVERITY RedemptionFee::setFeeMinMax (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeMinMax "));
   DString maxFee;

   if (isFeeTypePercentage (idDataGroup))
   {
      maxFee = I_("100");
      setField (ifds::MinFee, I_("0"), idDataGroup, false);
   }
   else
   {
      getContext().getField (ifds::Amount, maxFee, idDataGroup);
   }
   setField (ifds::MaxFee, maxFee, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RedemptionFee::setFeeProperties (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeProperties"));
   TransFeeRate::setFeeProperties (idDataGroup);
   setFieldReadOnly (ifds::ChargeOption, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RedemptionFee::getFeeConfigDefaults ( bool bChargeOptionDefaultsRead,
                                           bool bChargeTradeFeeOptionDefaultsRead,
                                           bool bChargeFeeTypeOptionDefaultsRead,
                                           const BFDataGroupId &idDataGroup)
{
   if (!bChargeOptionDefaultsRead)
   {
      loadSubstitutionList (ifds::ChargeOption, idDataGroup, I_("0")); //charge
   }
   if (!bChargeTradeFeeOptionDefaultsRead)
   {
      loadSubstitutionList (ifds::TradeFeeOption, idDataGroup, I_("0,2")); //charge as default/override/suppress
   }
   if (!bChargeFeeTypeOptionDefaultsRead)
   {
      loadSubstitutionList (ifds::FeeType, idDataGroup, I_("0,1")); //percent
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RedemptionFee.cpp-arc  $
// 
//    Rev 1.7   Apr 15 2005 10:23:14   popescu
// Incident #285556 - fee only should change if Amount changes
// 
//    Rev 1.6   Apr 11 2005 16:10:34   popescu
// Incident #285556 - user is able to charge any flat fee amount for full redemptions. Also, for partial redemption validation is meant to stop the user charge a fee that is more then the redemption amount.
// 
//    Rev 1.5   Mar 01 2005 15:54:54   winnie
// PET 1117 FN56 : Redemption Fee is not fund depandent. Should only refresh the fee for split commission client. It should applies to allocation trade as well.
// 
//    Rev 1.4   Feb 28 2005 11:29:14   popescu
// PET 1117/56, set the correct min/max values based on the fee types
// 
//    Rev 1.3   Jan 31 2005 10:09:34   popescu
// PTS 10038434, set the charge option field to read only, the fee is not driven by set-up
// 
//    Rev 1.2   Jan 12 2005 20:00:04   popescu
// PTS 10037339, fixed min/max for percentage type fee and do not allow redemption fee for an AFT environment
// 
//    Rev 1.1   Jan 12 2005 18:51:56   popescu
// PTS 10037339, allowed user to set Redemption Fee up
// 
//    Rev 1.0   Jan 12 2005 17:30:10   popescu
// Initial revision.
// 

 */