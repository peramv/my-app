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
//    Copyright 2013 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : FullEAPRedemption.cpp
// ^AUTHOR : 
// ^DATE   : Jan 2013
//
// ^CLASS    : FullEAPRedemption
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fulleapredemption.hpp"

#include "lsifcodeslist.hpp"
#include "mgmtco.hpp"
#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "supportedproductslist.hpp"
#include "trade.hpp"
#include "mfaccount.hpp"
#include "shareholder.hpp"

namespace
{
   // Trace literals
   const I_CHAR * CLASSNAME                     = I_("FullEAPRedemption");
   const I_CHAR * RESP_EARNINGS_TO_BENEFICIARY  = I_("61");
   const I_CHAR * AMOUNTTYPE_AMOUNT             = I_("D");
   const I_CHAR * GROSS_NET_NET                 = I_("N");
   const I_CHAR * GROSS_NET_GROSS               = I_("Y");
}

namespace ifds
{
//mgmtco fields
   extern CLASS_IMPORT const BFTextFieldId DSCOverride;
//fees fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFIntegerFieldId TransFeeCode;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId OverrideDSCAllow;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
   extern CLASS_IMPORT const BFTextFieldId DeathRedCode;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId FundRelnCode;
}

namespace CND
{  // Conditions used
   extern const long ERR_RESP_TRADE_NOT_ALLOW;
}

//namespace FEES
//{
//   extern const I_CHAR * EVENT_COMMISSION_DEATH;
//}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const FULL_EAP_REDEMPTION;
}

//******************************************************************************
FullEAPRedemption::FullEAPRedemption (BFAbstractCBO &parent) 
: Redemption (parent)
, Trade (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
FullEAPRedemption::~FullEAPRedemption()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY FullEAPRedemption::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

   setFieldNoValidate ( ifds::TradesTransType, TRADETYPE::FULL_EAP_REDEMPTION, idDataGroup, false);

   if (_bInitPending)
   {
      setFieldReadOnly( ifds::Amount, idDataGroup, true);
      setFieldReadOnly( ifds::AmtType, idDataGroup, true);
      setFieldReadOnly( ifds::GrossOrNet, idDataGroup, true);
      setFieldReadOnly( ifds::RedCode, idDataGroup, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FullEAPRedemption::doInit (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

   Redemption::doInit (data);

   if (_bInitPending)
   {
      setFieldReadOnly( ifds::Amount, BF::HOST, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FullEAPRedemption::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("preInitWithDefaultValues"));

   Redemption::preInitWithDefaultValues (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FullEAPRedemption::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   Redemption::doInitWithDefaultValues (idDataGroup);
   
   setFieldNoValidate ( ifds::TradesTransType, TRADETYPE::FULL_EAP_REDEMPTION, idDataGroup, false);
   setFieldNoValidate ( ifds::Amount, I_("0"), idDataGroup, false);
   setFieldNoValidate ( ifds::AmtType, AMOUNTTYPE_AMOUNT, idDataGroup, false);
   setFieldNoValidate ( ifds::GrossOrNet, GROSS_NET_GROSS, idDataGroup, false);

   setFieldReadOnly( ifds::TradesTransType, idDataGroup, true);
   
   setFieldNoValidate ( ifds::RedCode, 
                        RESP_EARNINGS_TO_BENEFICIARY, 
                        idDataGroup, 
                        false, 
                        false,  //force validation
                        true);  //notify         
   
   
   setFieldReadOnly( ifds::Amount, idDataGroup, true);
   setFieldReadOnly( ifds::AmtType, idDataGroup, true);
   setFieldReadOnly( ifds::GrossOrNet, idDataGroup, true);
}

//******************************************************************************
SEVERITY FullEAPRedemption::doValidateField (const BFFieldId &idField, 
                                             const DString &strValue, 
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   if( Redemption::doValidateField (idField, strValue, idDataGroup) <= WARNING )
   {
      if ( idField == ifds::AccountNum )
      {
         if( !isRESPTradeAccount(idDataGroup))
         {
            ADDCONDITIONFROMFILE (CND::ERR_RESP_TRADE_NOT_ALLOW);
         }
      }
      else if(idField == ifds::RedCode)
      {
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FullEAPRedemption::doValidateAll (const BFDataGroupId &idDataGroup, 
                                           long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   if( Redemption::doValidateAll (idDataGroup, lValidateGroup) <= WARNING )
   {
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FullEAPRedemption::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if( Redemption::doApplyRelatedChanges (idField, idDataGroup) <= WARNING )
   {
      if(idField == ifds::RedCode)
      {
         DString strRedCode;
         getField (ifds::RedCode, strRedCode, idDataGroup, false);
         
         if( strRedCode.strip().upperCase() == RESP_EARNINGS_TO_BENEFICIARY)
         {
            setFieldReadOnly( ifds::RedCode, idDataGroup, true);
         }
      }         
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool FullEAPRedemption::supportsAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
bool FullEAPRedemption::supportsFromAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
SEVERITY FullEAPRedemption::raiseFullRedemptionMessage( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,CLASSNAME, I_("raiseFullRedemptionMessage"));

   // don't raise warning message when amount is 0 and amount type is dollar

   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FullEAPRedemption.cpp-arc  $
// 
