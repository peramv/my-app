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
// ^FILE   : TransFeeRate.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : TransFeeRate
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "transfeerate.hpp"

#include "feeparamconfiglist.hpp"
#include "feesetuptraderuleslist.hpp"
#include "fundfeelist.hpp"
#include "mgmtco.hpp"
#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("TransFeeRate");
}

namespace CND
{  // Conditions used
   extern const long ERR_FEE_RATE_UNDER_MINIMUM;
   extern const long ERR_FEE_RATE_ABOVE_MAX;
   extern const long ERR_FEE_RATE_ABOVE_100_PERCENT;
   extern const long ERR_FEE_RATE_UNDER_0_PERCENT;
   extern const long ERR_FEE_MUST_BE_NUMERIC;
   extern const long ERR_NEGATIVE_FEE_NOT_ALLOW;
}

namespace ifds
{
//context fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
//fee fields
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
   extern CLASS_IMPORT const BFDecimalFieldId MinFee;
   extern CLASS_IMPORT const BFDecimalFieldId MaxFee;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                             //  Field DD Id,      State Flags,      Group Flags 
   { ifds::MinFee,           BFCBO::CALCULATED_FIELD,      0}, 
   { ifds::MaxFee,           BFCBO::CALCULATED_FIELD,      0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
TransFeeRate::TransFeeRate (BFAbstractCBO &parent, const DString &feeCode) : TransFee (parent, feeCode)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData (NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
}

//******************************************************************************
TransFeeRate::~TransFeeRate()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY TransFeeRate::init (const BFDataGroupId &idDataGroup /*=BF::HOST*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   TransFee::init (idDataGroup);
//   setFieldReadOnly (ifds::FeeRate, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeRate::init (const BFData &viewData)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   TransFee::init (viewData);
   setFeeMinMax (BF::HOST);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TransFeeRate::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
   if (canBeInitialized (idDataGroup))
   {
      TransFee::doInitWithDefaultValues (idDataGroup);
      setFeeMinMax (idDataGroup);
   }
}

//******************************************************************************
bool TransFeeRate::isChargeFee (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
SEVERITY TransFeeRate::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeDefault"));
   FundFeeList *pFundFeeList = NULL;
   DString rate (I_("0")),
      feeCurrency,feeRate;

   if ( getFeeParams (pFundFeeList, idDataGroup) <= WARNING &&
        pFundFeeList)
   {
      pFundFeeList->getField (ifds::Rate, rate, idDataGroup);
      pFundFeeList->getField (ifds::Currency, feeCurrency, idDataGroup);
	}

	getFormattedFee (idDataGroup, rate);
	Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

	if( (pTrade->isRebook() == true) && (pTrade->getOrigTradeFee().strip().upperCase() == I_("Y")))
	{
		getField(ifds::FeeRate, feeRate, idDataGroup);
		setFieldNoValidate (ifds::FeeRate, feeRate, idDataGroup, true, false, true, false);
	}
	else
	{
		setFieldNoValidate (ifds::FeeRate, rate, idDataGroup, true, false, true, false);
	}
	setFieldNoValidate (ifds::OrigFeeRate, rate, idDataGroup, true, false, true, false);
	setFieldNoValidate (ifds::Currency, feeCurrency, idDataGroup, false, false, true, false);
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeRate::setFeeMinMax (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeMinMax "));
   if (isFeeTypePercentage (idDataGroup) && !ignoreTypeForFeeRate () && !hasFeeParams (idDataGroup))
   {
      setFieldNoValidate (ifds::MinFee, I_("0"), idDataGroup, false, false, true, false);
      setFieldNoValidate (ifds::MaxFee, I_("100"), idDataGroup, false, false, true, false);
   }
   else //find the min max from fee param
   {
      FundFeeList *pFundFeeList = NULL;
      DString maxFee (I_("0")),
         minFee (I_("0"));

      if ( getFeeParams (pFundFeeList, idDataGroup) <= WARNING &&
           pFundFeeList)
      {
         pFundFeeList->getField (ifds::MinFee, minFee, idDataGroup);
         pFundFeeList->getField (ifds::MaxFee, maxFee, idDataGroup);
      }
      setField (ifds::MaxFee, maxFee, idDataGroup);
      setField (ifds::MinFee, minFee, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//some fees have max/min set by fee-params, even if the type is percentage 
//(and max/min is not 100/0)
//the base class should have the knowledge to apply the proper defaults 
//and validations for the fee rate, based on what this method returns 
//******************************************************************************
inline bool TransFeeRate::ignoreTypeForFeeRate ()
{
//default implemenation, ExchangeIn/Out fee will return true
   return false;
}

//******************************************************************************
SEVERITY TransFeeRate::doValidateField ( const BFFieldId &idField, 
                                         const DString &strValue, 
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   if (TransFee::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
      if (idField == ifds::FeeRate)
      {
         validateFeeRate (strValue, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeRate::doApplyRelatedChanges ( const BFFieldId &idField, 
                                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   if (TransFee::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
      if (idField == ifds::TradeFeeOption)
      {
         DString tradeFeeOption;

         getField (ifds::TradeFeeOption, tradeFeeOption, idDataGroup);
         if (tradeFeeOption == I_("3")) //suppress
         {
            DString rate (I_("0"));
            getFormattedFee (idDataGroup, rate);
            setFieldNoValidate ( ifds::FeeRate, rate, idDataGroup, true,
                                 false, true, true ); 
         }
         setFieldReadOnly (ifds::FeeRate, idDataGroup, tradeFeeOption == I_("3"));
      }
      else if (idField == ifds::FeeType) //if type changes, the min/max fields should change, too
      {
         setFeeMinMax (idDataGroup);
         //invalidate the fee rate
         setFieldValid (ifds::FeeRate, idDataGroup, false);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeRate::validateFeeRate ( const DString &strValue, 
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFeeRate"));

   if (isDecimal (strValue))
   {
      double dFeeRate = DSTCommonFunctions::convertToDouble (strValue);

      if (dFeeRate >= 0)
      {
         DString maxFee, 
            minFee;

         getField (ifds::MaxFee, maxFee, idDataGroup);
         getField (ifds::MinFee, minFee, idDataGroup);

         double dMaxFee = DSTCommonFunctions::convertToDouble (maxFee);
         double dMinFee = DSTCommonFunctions::convertToDouble (minFee);

         if (dFeeRate <= dMaxFee)
         {
            if (dFeeRate >= dMinFee)
            {
               ;//do nothing, fee in range
            }
            else
            {
               if (isFeeTypePercentage (idDataGroup) && !ignoreTypeForFeeRate()) //percentage
               {
                  DString idiStr,
                     feeName;

                  getField (ifds::TransFeeCode, feeName, idDataGroup, true);
                  addIDITagValue (idiStr, I_ ("name"), feeName);
                  DString dstrMinFee = DSTCommonFunctions::doubleToDString (ifds::MinFee, dMinFee);
				      DSTCommonFunctions::DisplayFormat(dstrMinFee, ifds::MinFee );
                  addIDITagValue (idiStr, I_ ("min"), dstrMinFee );
                  ADDCONDITIONFROMFILEIDI (CND::ERR_FEE_RATE_UNDER_0_PERCENT, idiStr);
               }
               else
               {
                  DString idiStr,
                     feeName;

                  getField (ifds::TransFeeCode, feeName, idDataGroup, true);
                  addIDITagValue (idiStr, I_ ("name"), feeName);
				  DString dstrMinFee = DSTCommonFunctions::doubleToDString (ifds::MinFee, dMinFee);
				  DSTCommonFunctions::DisplayFormat(dstrMinFee, ifds::MinFee );
                  addIDITagValue (idiStr, I_ ("min"), dstrMinFee );
                  ADDCONDITIONFROMFILEIDI (CND::ERR_FEE_RATE_UNDER_MINIMUM, idiStr);
               }
            }
         }
         else
         {
            if (isFeeTypePercentage (idDataGroup) && !ignoreTypeForFeeRate() && !hasFeeParams (idDataGroup)) //percentage
            {
               DString idiStr,
                  feeName;

               getField (ifds::TransFeeCode, feeName, idDataGroup, true);
               addIDITagValue (idiStr, I_ ("name"), feeName);
               ADDCONDITIONFROMFILEIDI (CND::ERR_FEE_RATE_ABOVE_100_PERCENT, idiStr);
            }
            else
            {
               DString idiStr,
                  feeName;

               getField (ifds::TransFeeCode, feeName, idDataGroup, true);
               addIDITagValue (idiStr, I_ ("name"), feeName);
			   DString dstrMaxFee = DSTCommonFunctions::doubleToDString (ifds::MaxFee, dMaxFee);
			   DSTCommonFunctions::DisplayFormat( dstrMaxFee, ifds::MaxFee );
               addIDITagValue (idiStr, I_ ("max"), dstrMaxFee );
               ADDCONDITIONFROMFILEIDI (CND::ERR_FEE_RATE_ABOVE_MAX, idiStr);
            }
         }
      }
      else
      {
          ADDCONDITIONFROMFILE (CND::ERR_NEGATIVE_FEE_NOT_ALLOW);
      }
   }
   else
   {
      ADDCONDITIONFROMFILE (CND::ERR_FEE_MUST_BE_NUMERIC);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool TransFeeRate::isFeeTypePercentage (const BFDataGroupId &idDataGroup) const
{
   DString feeType;

   getField (ifds::FeeType, feeType, idDataGroup);
   return feeType == I_("1"); //percentage
}

//******************************************************************************
void TransFeeRate::getField ( const BFFieldId &idField, 
                              DString &fieldValue, 
                              const BFDataGroupId &idDataGroup, 
                              bool formattedReturn) const
{
   if (idField == ifds::FeeRate && formattedReturn)
   {
      BFCBO::getField (idField, fieldValue, idDataGroup, false);
      getFormattedFee (idDataGroup, fieldValue);
   }
   else
   {
      BFCBO::getField (idField, fieldValue, idDataGroup, formattedReturn);
   }
}

//**********************************************************
void TransFeeRate::getFormattedFee ( const BFDataGroupId& idDataGroup, 
                                     DString &strValue) const
{
   if (!isFeeTypePercentage (idDataGroup))
   {
      DString feeCurrency;

      getField (ifds::Currency, feeCurrency, idDataGroup, false);
      CurrencyClass::getFormattedValue (getWorkSession (), strValue, feeCurrency);
   }
}

//******************************************************************************
SEVERITY TransFeeRate::setField ( const BFFieldId &idField, 
                                  const DString &dstrValue,
                                  const BFDataGroupId &idDataGroup, 
                                  bool bFormatted, 
                                  bool bSideEffect, 
                                  bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setField"));

   DString dstrLocalValue( dstrValue );

   if (idField == ifds::FeeRate )
   {               
      getFormattedFee (idDataGroup, dstrLocalValue);
   }
   
   BFCBO::setField( idField, dstrLocalValue, idDataGroup, bFormatted, bSideEffect, bCheckCurrentValue );
      
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransFeeRate.cpp-arc  $
// 
//    Rev 1.16   Nov 06 2009 14:51:44   popescu
// Incident 1899629 - Desktop missing validation of min & max in fee code - Fixed Desktop to read the min and max from the fee params set-up if the fee type is percentage and fee parameters exist.
// 
//    Rev 1.15   Nov 06 2009 14:27:38   popescu
// Incident 1899629 - Desktop missing validation of min & max in fee code - Fixed Desktop to read the min and max from the fee params set-up if the fee type is percentage and fee parameters exist.
// 
//    Rev 1.14   Jul 11 2005 17:24:44   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.13   Jun 20 2005 17:37:54   popescu
// Incident# 337811 -call 'getFormattedFee' method since it skips the fee type percent...
// 
//    Rev 1.12   Apr 09 2005 14:30:40   porteanm
// Incident 276992 - FeeRate not saved with the right precision.
// 
//    Rev 1.11   Apr 09 2005 14:13:42   porteanm
// Incident 276992 - FeeRate not saved with the right precision.
// 
//    Rev 1.10   Mar 31 2005 16:39:58   Fengyong
// incident #277963 - warning message "condition rate is zero"
// show up for api when there is no condition update.
// 
//    Rev 1.9   Mar 02 2005 08:33:08   popescu
// PET 1117/56 added virtual method meant to let the base class know whether to ignore the fee type or not when sets the min/max or validates the fee rate against min/max
// 
//    Rev 1.8   Jan 18 2005 19:42:26   popescu
// PTS 10038609, acquisition does not get refreshed if split comm changes to default
// 
//    Rev 1.7   Dec 08 2004 22:08:32   popescu
// PET 1117/06, more fees
// 
//    Rev 1.6   Nov 24 2004 21:36:38   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.5   Nov 19 2004 14:19:36   popescu
// PET 1117/06, fees processing
// 
//    Rev 1.4   Nov 17 2004 16:16:00   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.3   Nov 15 2004 16:24:18   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.1   Nov 09 2004 16:51:16   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Nov 05 2004 21:30:28   popescu
// Initial revision.
// 
 */