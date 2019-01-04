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
// ^FILE   : ConditionRate.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : ConditionRate
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "conditionrate.hpp"

#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "trade.hpp"
#include "transfeelist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("ConditionRate");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFIntegerFieldId TransFeeCode;
}

namespace CND
{  // Conditions used
   extern const long WARN_CLIENT_CONDITION_RATE_IS_ZERO;
}

namespace FEES
{
   extern const I_CHAR * REINVEST_PURCHASE_CONDITION_RATE;
   extern const I_CHAR * PURCHASE_CONDITION_RATE;
   extern const I_CHAR * ACQUISITION;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const REINVEST_PURCHASE;
}

//******************************************************************************
ConditionRate::ConditionRate (BFAbstractCBO &parent, const DString &feeCode) : TransFeeRate (parent, feeCode)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
ConditionRate::~ConditionRate()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
void ConditionRate::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
   if (canBeInitialized (idDataGroup))
   {
      TransFeeRate::doInitWithDefaultValues (idDataGroup);
   }
}

//******************************************************************************
SEVERITY ConditionRate::setFeeProperties (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeProperties"));
   
   TransFeeRate::setFeeProperties (idDataGroup);
   
   DString feeType;

   getField (ifds::FeeType, feeType, idDataGroup);
   if (feeType == I_("2")) //scale
   {
      setField (ifds::TradeFeeOption, I_("1"), idDataGroup, false); //charge per system calculation
      setFieldReadOnly (ifds::FeeRate, idDataGroup, true);
      setFieldReadOnly (ifds::TradeFeeOption, idDataGroup, true);
      setFieldReadOnly (ifds::Currency, idDataGroup, true);
   }
   setFieldReadOnly (ifds::FeeType, idDataGroup, true);
   //if rate is zero, validation is triggered, so the user can be warned
   setFieldValid (ifds::FeeRate, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ConditionRate::setChargeOption (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setChargeOption"));
   setFieldNoValidate (ifds::ChargeOption, I_("0"), idDataGroup, false, false, true, false); //charge, always
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
inline bool ConditionRate::useFeeModelCode ()
{
   return true;
}

//******************************************************************************
bool ConditionRate::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
bool ConditionRate::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType,
		   feeCode;

	   getField (ifds::TransFeeCode, feeCode, idDataGroup, false);
	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   return (( transType == TRADETYPE::PURCHASE && 
	  		     feeCode == FEES::PURCHASE_CONDITION_RATE) ||
				 ( transType == TRADETYPE::REINVEST_PURCHASE && 
				 feeCode == FEES::REINVEST_PURCHASE_CONDITION_RATE)) &&
				 isApplicableForFeeModel (idDataGroup) &&
				 isApplicableForAcqFeeOption (idDataGroup);/* &&
														   hasFeeParams (idDataGroup); //use the fee model code*/
   }
   return false;
}

//******************************************************************************
bool ConditionRate::hasContextChanged (const BFDataGroupId &idDataGroup)
{
   return hasFeeParamsContextChanged (idDataGroup);
}

//******************************************************************************
bool ConditionRate::isApplicableForFeeModel (const BFDataGroupId &idDataGroup)
{
   DString feeModelCode,
      accountNum;

   getContext().getField (ifds::AccountNum, accountNum, idDataGroup, false);
   return getFeeModelCode (accountNum, feeModelCode, idDataGroup) <= WARNING &&
          !feeModelCode.empty();
}

//******************************************************************************
bool ConditionRate::isApplicableForAcqFeeOption (const BFDataGroupId &idDataGroup)
{
   DString acqFeeOption;
   
   getContext().getField (ifds::AcqFeeOption, acqFeeOption, idDataGroup, false);
   return acqFeeOption == I_("1"); //discount fee model
}

//******************************************************************************
SEVERITY ConditionRate::setFeeType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeType"));
   TransFeeRate::setFeeType (idDataGroup);

   if (!hasFeeParams (idDataGroup))
   {
      setFieldNoValidate ( ifds::FeeType, I_("1"), idDataGroup, false, 
                           false, true, false); //percentage
      setFieldNoValidate ( ifds::OrigFeeType, I_("1"), idDataGroup, false, 
                           false, true, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ConditionRate::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeDefault"));
   TransFeeRate::setFeeDefault (idDataGroup);
   calculateDiscountRate (idDataGroup);   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ConditionRate::doValidateField ( const BFFieldId &idField, 
                                          const DString &strValue, 
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   if (TransFeeRate::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
      if (idField == ifds::FeeRate)
      {
         double dec_fee_rate = DSTCommonFunctions::convertToDouble (strValue);

         if (dec_fee_rate == 0)
         {
            ADDCONDITIONFROMFILE (CND::WARN_CLIENT_CONDITION_RATE_IS_ZERO);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ConditionRate::doApplyRelatedChanges ( const BFFieldId &idField, 
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

         DString tradeFeeOption;

         getField (ifds::TradeFeeOption, tradeFeeOption, idDataGroup);
         if (tradeFeeOption == I_("3")) //suppress
         {
            calculateDiscountRate (idDataGroup);
         }
      }
      else if (idField == ifds::FeeRate)
      {
         calculateDiscountRate (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ConditionRate::calculateDiscountRate (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("calculateDiscountRate"));
   assert (getParent());
   TransFeeList *pTransFeeList = dynamic_cast <TransFeeList*> (getParent());
   
   if (pTransFeeList)
   {
      pTransFeeList->calculateDiscountRate (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ConditionRate.cpp-arc  $
// 
//    Rev 1.17   Mar 31 2005 16:38:00   Fengyong
// incident #277963 - warning message "condition rate is zero"
// show up for api when there is no condition update.
// 
//    Rev 1.16   Mar 02 2005 09:34:24   popescu
// Incident # 254204, client condition rate is displayed with a default value of zero, even if the set-up does not exist for it. user is warned if the value of the fee is left to zero
// 
//    Rev 1.15   Jan 14 2005 10:30:58   popescu
// PTS 10037865, charge option field should be 'Charge' and locked for Conditionrate and all other fees, but TrxnFee where user should be allowed to change its value.
// 
//    Rev 1.14   Jan 10 2005 10:38:26   popescu
// PTS 10037553, fixed fees properties in pending mode and trade reset of the trans type combo
// 
//    Rev 1.13   Dec 20 2004 14:19:10   popescu
// PTS 10037057, discount rate not updated when trade fee option changed to Override/Suppress
// 
//    Rev 1.12   Dec 15 2004 15:55:26   popescu
// PET 1117/06, fixes related to condition rates scale type/ acq fee option defaults
// 
//    Rev 1.11   Dec 11 2004 11:47:22   popescu
// PET 1117/56 more fixes, pending trade mods
// 
//    Rev 1.10   Dec 10 2004 20:18:12   winnie
// PET 1117 FN06 : set companyid when calling view 311 
// 
//    Rev 1.9   Dec 08 2004 22:08:12   popescu
// PET 1117/06, more fees
// 
//    Rev 1.8   Dec 02 2004 20:59:14   popescu
// PET 1117/06, more fee fixes
// 
//    Rev 1.7   Dec 01 2004 15:44:28   popescu
// PET 1117/56 fees processing, calculate the discount rate
// 
//    Rev 1.6   Nov 24 2004 21:35:34   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.5   Nov 19 2004 14:19:18   popescu
// PET 1117/06, fees processing
// 
//    Rev 1.4   Nov 17 2004 16:14:50   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.3   Nov 15 2004 16:22:22   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.1   Nov 09 2004 16:49:00   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Nov 06 2004 00:35:04   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 04 2004 11:03:16   popescu
// Initial revision.
// 
 */