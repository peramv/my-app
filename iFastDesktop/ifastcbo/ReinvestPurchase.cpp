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
// ^FILE   : ReinvestPurchase.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : September, 2004
//
// ^CLASS    : ReinvestPurchase - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "reinvestpurchase.hpp"

#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "reinvestpurchaseschedule.hpp"

namespace ifds
{
//management company options
//attributes grid
//fund fields
//subst sets
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REINVEST_PURCHASE;
}

namespace ifds
{
//cross-edits
   extern CLASS_IMPORT const BFTextFieldId FromFundTradeDate;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_ ("ReinvestPurchase");
}

namespace CND
{
   extern const long ERR_FUND_NOT_WITHIN_REINVEST_PURCHASE_SCHEDULE;
}

namespace UAF
{
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
    //Field DD Id,              State Flags,      Group Flags 
   {ifds::FromFundTradeDate,      BFCBO::IMMEDIATE_VALIDATION, 0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
ReinvestPurchase::ReinvestPurchase (BFAbstractCBO &parent) : Purchase (parent), Trade (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
	registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);    
	
   addCrossEdit (ifds::FromFundTradeDate, ifds::EffectiveDate); 
   addCrossEdit (ifds::FromFundTradeDate, ifds::FromFund); 
}


//******************************************************************************
ReinvestPurchase::~ReinvestPurchase ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY ReinvestPurchase::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));

   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::REINVEST_PURCHASE, 
                        idDataGroup, 
                        false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool ReinvestPurchase::supportsAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
SEVERITY ReinvestPurchase::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues"));
   Purchase::preInitWithDefaultValues (idDataGroup);

   setFieldReadOnly (ifds::DepositType, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void ReinvestPurchase::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   Purchase::doInitWithDefaultValues (idDataGroup);
   setFieldNoValidate ( ifds::DepositType, I_("24"), idDataGroup, false,
                        false, //valid
                        true);  //notify
}

//******************************************************************************
SEVERITY ReinvestPurchase::doValidateField ( const BFFieldId &idField, 
                                             const DString &strValue, 
                                             const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   if (Purchase::doValidateField (idField, strValue, idDataGroup))
   {
      if (idField == ifds::FromFundTradeDate)
      {
         validateReinvestPurchaseSchedule (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY ReinvestPurchase::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                   const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   if (Purchase::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//***********************************************************************************
SEVERITY ReinvestPurchase::validateReinvestPurchaseSchedule (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateReinvestPurchaseSchedule "));

   DString fundCode,
      tradeDate;

   getField (ifds::FromFund, fundCode, idDataGroup, false);
   getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);

   if (!fundCode.empty() && !tradeDate.empty())
   {
      FundMasterList *pFundMasterList;
      FundMaster *pFundMaster = NULL;

      if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
           pFundMasterList &&
           pFundMasterList->getFundMaster (fundCode, idDataGroup, pFundMaster) &&
           pFundMaster)
      {
         ReinvestPurchaseSchedule *pReinvestPurchaseSchedule = NULL;

         if ( pFundMaster->getReinvestPurchaseSchedule ( pReinvestPurchaseSchedule, 
                                                         idDataGroup) <= WARNING &&
              pReinvestPurchaseSchedule)
         {
            if (!pReinvestPurchaseSchedule->
                  isDateWithinReinvestmentSchedule ( tradeDate, 
                                                     idDataGroup)
               )
            {
               DString idiStr,
                  tradeDateDescr;

               getField (ifds::EffectiveDate, tradeDateDescr, idDataGroup, true);
               addIDITagValue (idiStr, I_("FUND"), fundCode);
               addIDITagValue (idiStr, I_("DATE"), tradeDateDescr);
               ADDCONDITIONFROMFILEIDI (CND::ERR_FUND_NOT_WITHIN_REINVEST_PURCHASE_SCHEDULE, idiStr);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
inline SEVERITY ReinvestPurchase::validateDepositType ( const DString &depositType,
                                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateDepositType")
                          );
//skip depo type validation
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReinvestPurchase.cpp-arc  $
// 
//    Rev 1.8   Nov 16 2006 11:11:58   popescu
// PET 2252. FN01 - mgmt fee rebate
// 
//    Rev 1.7   Dec 24 2004 09:55:40   popescu
// PTS 10037200, modify button for reinvest purchase is not actvie
// 
//    Rev 1.6   Dec 07 2004 01:37:46   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.5   Dec 03 2004 10:46:08   popescu
// PET 1117/06, fees processing
// 
//    Rev 1.4   Nov 29 2004 20:30:36   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.3   Nov 14 2004 14:51:44   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Nov 06 2004 00:42:24   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.1   Nov 04 2004 17:38:24   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Oct 29 2004 20:27:28   popescu
// Initial revision.
// 
//    Rev 1.0   Oct 01 2004 19:30:04   popescu
// Initial revision.
 * 
 *    Rev 1.566   Sep 21 2004 16:02:32   popescu
  * Initial revision.
// 
// 
*/
