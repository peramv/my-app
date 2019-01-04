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
// ^FILE   : ExchangeFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Jan 2005
//
// ^CLASS    : ExchangeFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "exchangefee.hpp"

#include "splitcommission.hpp"

#include <ifastdataimpl\dse_dstc0121_vw.hpp>

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("ExchangeFee");
}

namespace ifds
{
//fee fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

namespace CND
{  // Conditions used
}

namespace FEES
{
   extern const I_CHAR * EXCHANGE;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE;
}

//******************************************************************************
ExchangeFee::ExchangeFee (BFAbstractCBO &parent) : AcquisitionFee (parent, FEES::EXCHANGE)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
ExchangeFee::~ExchangeFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
void ExchangeFee::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
   AcquisitionFee::doInitWithDefaultValues (idDataGroup);
}

//******************************************************************************
bool ExchangeFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return SplitCommission::isTypeZERO (getWorkSession ());
}

//******************************************************************************
SEVERITY ExchangeFee::setFeeProperties (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeProperties"));
   TransFeeRate::setFeeProperties (idDataGroup);
   setFieldReadOnly (ifds::ChargeOption, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ExchangeFee.cpp-arc  $
// 
//    Rev 1.1   Jan 31 2005 10:09:24   popescu
// PTS 10038434, set the charge option field to read only, the fee is not driven by set-up
// 
//    Rev 1.0   Jan 24 2005 10:26:04   popescu
// Initial revision.
// 
 */