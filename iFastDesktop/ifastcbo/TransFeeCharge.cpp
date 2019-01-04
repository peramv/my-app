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
// ^FILE   : TransFeeCharge.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : TransFeeCharge
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "transfeecharge.hpp"

#include "feeparamconfiglist.hpp"
#include "feesetuptraderuleslist.hpp"
#include "mgmtco.hpp"
#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("TransFeeCharge");
}

namespace CND
{  // Conditions used
}

namespace ifds
{
//context fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
//fee fields
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                             //  Field DD Id,      State Flags,      Group Flags 
   { ifds::FeeCharge,        BFCBO::NONE,                  0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
TransFeeCharge::TransFeeCharge (BFAbstractCBO &parent, const DString &feeCode) : TransFee (parent, feeCode)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData (NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);

}

//******************************************************************************
TransFeeCharge::~TransFeeCharge()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY TransFeeCharge::init (const BFDataGroupId &idDataGroup /*=BF::HOST*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   TransFee::init (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeCharge::init (const BFData &viewData)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   TransFee::init (viewData);
   DString feeRate = viewData.getElementValue (ifds::FeeRate);

   feeRate.strip();

   double d_rate = DSTCommonFunctions::convertToDouble (feeRate);

   if (d_rate == 0)
   {
      setFieldNoValidate (ifds::FeeCharge, N, BF::HOST, false, false, true, false);
   }
   else if (d_rate == 1)
   {
      setFieldNoValidate (ifds::FeeCharge, Y, BF::HOST, false, false, true, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool TransFeeCharge::isChargeFee (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
SEVERITY TransFeeCharge::doValidateField ( const BFFieldId &idField, 
                                           const DString &strValue, 
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   if (TransFee::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
      if (idField == ifds::FeeCharge)
      {
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeCharge::doApplyRelatedChanges ( const BFFieldId &idField, 
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
            setFieldNoValidate ( ifds::FeeCharge, N, idDataGroup, false,
                                 false,
                                 false, //do not notify
                                 false);  //no related changes
            //to keep charge/rate synchronized
            setFieldNoValidate ( ifds::FeeRate, charge2Rate(DString (N)), idDataGroup, false,
                                 false,
                                 false, //do not notify
                                 false);  //no related changes
         }
         setFieldReadOnly (ifds::FeeCharge, idDataGroup, tradeFeeOption == I_("3"));
      }
      else if (idField == ifds::FeeCharge)
      {
         DString feeCharge;

         getField (ifds::FeeCharge, feeCharge, idDataGroup);
         setFieldNoValidate ( ifds::FeeRate, charge2Rate(feeCharge), idDataGroup, false,
                              false,
                              false, //do not notify
                              true); //related changes
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TransFeeCharge::getFeeConfigDefaults ( bool bChargeOptionDefaultsRead,
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
      loadSubstitutionList (ifds::TradeFeeOption, idDataGroup, I_("0,2,3")); //charge as default/override/suppress
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransFeeCharge.cpp-arc  $
// 
//    Rev 1.7   Feb 22 2005 17:54:14   popescu
// PET 1117/56, change chargeoption initialization, to '0' from '1' (1 no longer means 'Charge')
// 
//    Rev 1.6   Jan 18 2005 19:42:22   popescu
// PTS 10038609, acquisition does not get refreshed if split comm changes to default
// 
//    Rev 1.5   Dec 09 2004 12:37:52   popescu
// PET 1117/56, more fees work /pending trade
// 
//    Rev 1.4   Dec 08 2004 22:08:28   popescu
// PET 1117/06, more fees
// 
//    Rev 1.3   Nov 17 2004 16:15:52   popescu
// No change.
// 
//    Rev 1.2   Nov 15 2004 16:23:38   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.0   Nov 05 2004 21:30:22   popescu
// Initial revision.
// 
 */