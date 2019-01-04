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
// ^FILE   : LightTrade.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : September, 2004
//
// ^CLASS    : LightTrade - Object merely defines a dummy trade
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "lighttrade.hpp"

namespace ifds
{
//attributes grid
   extern CLASS_IMPORT const BFTextFieldId TradeAttributesFields;
   extern CLASS_IMPORT const BFTextFieldId PurchaseAttributes;
   extern CLASS_IMPORT const BFTextFieldId RedemptionAttributes;
   extern CLASS_IMPORT const BFTextFieldId TransferAttributes;
   extern CLASS_IMPORT const BFTextFieldId ManualTradesTransType;
   extern CLASS_IMPORT const BFTextFieldId CIApplicable;
   extern CLASS_IMPORT const BFTextFieldId SIApplicable;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
   extern CLASS_IMPORT I_CHAR * const DIVIDEND;
   extern CLASS_IMPORT I_CHAR * const MANUAL_DIVIDEND_ADJ;
   extern CLASS_IMPORT I_CHAR * const CAPITAL_GAIN_INCOME_ADJ;
   extern CLASS_IMPORT I_CHAR * const SUPPLEMENTARY_INCOME_ADJ;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const TRADING_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const TRADING_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRADING_REDEMPTION;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_ ("LightTrade");
}

//******************************************************************************
LightTrade::LightTrade (BFAbstractCBO &parent, bool bManualTrades /*=false*/) : Trade (parent),
_bManualTrades (bManualTrades)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
}


//******************************************************************************
LightTrade::~LightTrade ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY LightTrade::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
//get default data dictionary value
   DString transType;
   BFProperties *pBFPropertiesTradesTransType = NULL;

   if (_bManualTrades)
   {
       pBFPropertiesTradesTransType = 
           getFieldProperties (ifds::ManualTradesTransType, idDataGroup);

       DString dstrCIApplicable, dstrSIApplicable, newTradesTransTypeSubList;
       getWorkSession().getOption(ifds::CIApplicable, dstrCIApplicable, idDataGroup, false);
       getWorkSession().getOption(ifds::SIApplicable, dstrSIApplicable, idDataGroup, false);

       if (pBFPropertiesTradesTransType)
       {
           pBFPropertiesTradesTransType->getAllSubstituteValues(newTradesTransTypeSubList);

           if (dstrCIApplicable.stripAll().upperCase() != I_("Y"))
           {
               newTradesTransTypeSubList = removeItemFromSubtList(newTradesTransTypeSubList, TRADETYPE::CAPITAL_GAIN_INCOME_ADJ);
           }

           if (dstrSIApplicable.stripAll().upperCase() != I_("Y"))
           {
               newTradesTransTypeSubList = removeItemFromSubtList(newTradesTransTypeSubList, TRADETYPE::SUPPLEMENTARY_INCOME_ADJ);
           }

           setFieldAllSubstituteValues(ifds::TradesTransType, idDataGroup, newTradesTransTypeSubList);
       }
   }
   else
   {
       pBFPropertiesTradesTransType = 
           getFieldProperties (ifds::TradesTransType, idDataGroup);
   }

   if (pBFPropertiesTradesTransType)
   {
      //get the default data dictionary value
      pBFPropertiesTradesTransType->getDefaultValue (transType);

      if (_bManualTrades && DSTCommonFunctions::getMarket () == MARKET_IDS::CANADA)
      {
          transType = TRADETYPE::MANUAL_DIVIDEND_ADJ;
      }

      if ( (transType == TRADETYPE::PURCHASE || transType == TRADETYPE::DIVIDEND || transType == TRADETYPE::MANUAL_DIVIDEND_ADJ) &&
           getWorkSession ().hasCreatePermission (UAF::TRADING_PURCHASE))
      {
         ; //use purchase
      }
      else if (getWorkSession ().hasCreatePermission (UAF::TRADING_REDEMPTION))
      {
         transType = TRADETYPE::REDEMPTION;
      }
      else if (getWorkSession ().hasCreatePermission (UAF::TRADING_EXCHANGE))
      {
         transType = TRADETYPE::EXCHANGE;
      }
      else
      {
         assert (0); //nothing can be created?
      }
      setFieldNoValidate ( ifds::TradesTransType, 
                           transType, 
                           idDataGroup, 
                           false);
   }
//attributes grid,set this as default, just to show something on the screen
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool LightTrade::supportsAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
bool LightTrade::supportsFromAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
void LightTrade::getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                           BFFieldId &classCodeFieldId)
{
   fundCodeFieldId  = ifds::NullFieldId;
   classCodeFieldId = ifds::NullFieldId;
}


//******************************************************************************
void LightTrade::getAccountFieldId (BFFieldId &accountFieldId)
{
   accountFieldId = ifds::AccountNum;
}


//******************************************************************************
inline bool LightTrade::isHypo ()
{
//a dummy trade is a hypothetical trade
   return true;
}

//******************************************************************************
inline bool LightTrade::areTaxRatesAllowed (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
inline bool LightTrade::isDilutionAllowed (const BFDataGroupId &idDataGroup)
{
	return false;
}

//******************************************************************************
void LightTrade::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   setFieldNoValidate (ifds::TradesPayType, NULL_STRING, idDataGroup, false);
   setFieldNoValidate (ifds::RedCode, NULL_STRING, idDataGroup, false);
   setFieldNoValidate (ifds::DepositType, NULL_STRING, idDataGroup, false);
   setFieldNoValidate (ifds::ExchRate, NULL_STRING, idDataGroup, false);
//open-up account to for the user
//   setFieldReadOnly (ifds::AccountTo, idDataGroup, false);
   return;
}

//******************************************************************************
SEVERITY LightTrade::doApplyRelatedChanges ( const BFFieldId &idField, 
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   if (idField == ifds::TradesTransType)
   {
      Trade::doApplyRelatedChanges (idField, idDataGroup);
   }
//ignore all other related changes applied for this object   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY LightTrade::transTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("transTypeRelatedChanges"));
   if (isPurchaseLike (idDataGroup))
   {
      setFieldAllSubstituteValues ( ifds::TradeAttributesFields, 
                                    idDataGroup, 
                                    ifds::PurchaseAttributes);
   }
   else if (isRedemptionLike (idDataGroup))
   {
      setFieldAllSubstituteValues ( ifds::TradeAttributesFields, 
                                    idDataGroup, 
                                    ifds::RedemptionAttributes);
   }
   else if ( isExchangeLike (idDataGroup) ||
             isRollover(idDataGroup))
   {
      setFieldAllSubstituteValues ( ifds::TradeAttributesFields, 
                                    idDataGroup, 
                                    ifds::TransferAttributes);
   }
//nothing to do in here
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY LightTrade::canAccountTrade ( MFAccount *pMFAccount, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canAccountTrade"));
//nothing to do in here
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY LightTrade::validateAccount ( MFAccount *pMFAccount, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAccount"));
//nothing to do in here
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/LightTrade.cpp-arc  $
// 
//    Rev 1.9   Sep 06 2007 17:19:30   popescu
// GAP 18 - added manual management fee rebate to manual dividend screen
// 
//    Rev 1.8   Jul 07 2005 12:17:54   AGUILAAM
// PET1235 : dilution, part of Rebook/Cancellation
// 
//    Rev 1.7   May 30 2005 15:11:32   popescu
// Incident #315485 - if user does not have permission to place certain types of transactions the choices will not be available on the trade entry screen
// 
//    Rev 1.6   Apr 18 2005 15:41:58   porteanm
// Incident 290447 - undid changes for RESP account validation for new trades.
// 
//    Rev 1.5   Apr 15 2005 16:48:54   porteanm
// Incident 290447 - RESP account validation for new trades.
// 
//    Rev 1.4   Nov 29 2004 20:30:16   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.3   Nov 14 2004 14:49:06   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Nov 06 2004 00:41:38   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.1   Nov 04 2004 17:38:02   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Oct 01 2004 19:30:30   popescu
// Initial revision.
 * 
 *    Rev 1.566   Sep 21 2004 16:02:32   popescu
  * Initial revision.
// 
// 
*/
