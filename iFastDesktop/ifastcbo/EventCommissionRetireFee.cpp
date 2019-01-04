//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2012 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : EventCommissionRetireFee.cpp
// ^AUTHOR : 
// ^DATE   : Aug 2012
//
// ^CLASS    : EventCommissionRetireFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "eventcommissionretirefee.hpp"

#include "eventcommissioninq.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "lsifcodeslist.hpp"
#include "trade.hpp"
#include "transfeelist.hpp"
#include "supportedproductslist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("EventCommissionRetireFee");
}

namespace ifds
{
//fees fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFIntegerFieldId TransFeeCode;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;

//fund fields
   extern CLASS_IMPORT const BFTextFieldId SuppressAdmin;
   extern CLASS_IMPORT const BFTextFieldId EventComm;
}

namespace CND
{  // Conditions used
}

namespace FEES
{
   extern const I_CHAR * EVENT_COMMISSION_RETIRE;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
}

//******************************************************************************
EventCommissionRetireFee::EventCommissionRetireFee (BFAbstractCBO &parent, const DString &feeCode) 
: TransFeeCharge (parent, feeCode)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
EventCommissionRetireFee::EventCommissionRetireFee (BFAbstractCBO &parent) 
: TransFeeCharge (parent, FEES::EVENT_COMMISSION_RETIRE)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
EventCommissionRetireFee::~EventCommissionRetireFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
bool EventCommissionRetireFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
bool EventCommissionRetireFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString fundCode,
		       classCode,
			   transType;

	   getContext().getField (ifds::FromFund, fundCode, idDataGroup);
	   getContext().getField (ifds::FromClass, classCode, idDataGroup);
	   getContext().getField (ifds::TransType, transType, idDataGroup, false);

	   return hasFeeParams (fundCode, classCode, idDataGroup) && 
		      transType == TRADETYPE::TRANSFER &&
		      isEventCommissionRetireApplicable (idDataGroup);
   }
   return false;
}

//******************************************************************************
bool EventCommissionRetireFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
//fee needs to be refreshed if any of these parameters change
   return hasFieldContextChanged (ifds::AccountTo, idDataGroup) ||
          hasFieldContextChanged (ifds::FromFund, idDataGroup) ||
          hasFieldContextChanged (ifds::FromClass, idDataGroup) ||
          hasFieldContextChanged (ifds::ToFund, idDataGroup) ||
          hasFieldContextChanged (ifds::ToClass, idDataGroup);
}

//******************************************************************************
bool EventCommissionRetireFee::isEventCommissionRetireApplicable (const BFDataGroupId &idDataGroup)
{
   bool bIsApplicable = false;
   DString accountNum,
      accountNumTo,
      redCode;

   getContext().getField (ifds::AccountNum, accountNum, idDataGroup);
   getContext().getField (ifds::AccountTo, accountNumTo, idDataGroup);
   accountNum.strip().upperCase();
   accountNumTo.strip().upperCase();
   if (!accountNum.empty() && !accountNumTo.empty() && 
        accountNum != I_("0") && accountNumTo != I_("0"))
   {
      EventCommissionInq eventCommissionInq(*this);
      if (eventCommissionInq.init (accountNum, accountNumTo, redCode, idDataGroup) <= WARNING)
      {
         DString eventComm;
         eventCommissionInq.getField (ifds::EventComm, eventComm, idDataGroup, false);
         eventComm.strip().upperCase();
         bIsApplicable = eventComm == I_("RETIREROLLCOMM");
      }
   }

   return bIsApplicable;
}

//******************************************************************************
SEVERITY EventCommissionRetireFee::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFeeDefaults"));
   DString chargeFee = I_("Y");
   DString tradeFeeOption = I_("0");
   
   setFieldNoValidate ( ifds::TradeFeeOption, tradeFeeOption, idDataGroup, false, false, true, false);
   setFieldNoValidate ( ifds::FeeCharge, chargeFee, idDataGroup, false, false, true, false);
   setFieldNoValidate ( ifds::FeeRate, charge2Rate (chargeFee), idDataGroup, false, false, true, false);
   setFieldNoValidate (ifds::FeeType, I_("1"), idDataGroup, false, false, true, false); //percent
   setFieldNoValidate (ifds::OrigFeeType, I_("1"), idDataGroup, false, false, true, false);
   setFieldNoValidate ( ifds::OrigFeeRate, charge2Rate (chargeFee), idDataGroup, false, false, true, false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/EventCommissionRetireFee.cpp-arc  $
// 
//    Rev 1.0   Aug 15 2012 14:59:46   dchatcha
// Initial revision.
// 
