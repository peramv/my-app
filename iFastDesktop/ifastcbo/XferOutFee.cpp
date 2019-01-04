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
// ^FILE   : XferOutFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : XferOutFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "xferoutfee.hpp"

#include "funddetail.hpp"
#include "fundtolist.hpp"
#include "mfaccount.hpp"
#include "trade.hpp"
#include "tradefundalloc.hpp"
#include "tradefundalloclist.hpp"
#include "splitcommission.hpp"
#include "splitcommissionlist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("XferOutFee");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcqFeeDefault;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFIntegerFieldId TransFeeCode;
   //acount fields
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   //fund fields
   extern CLASS_IMPORT const BFTextFieldId ExchInFeeExist;
   extern CLASS_IMPORT const BFTextFieldId LoadType;
//fee fields
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
}

namespace CND
{  // Conditions used
}

namespace FEES
{
   //this fee deals with the IFee field value in trade
   extern const I_CHAR * XFER_OUT;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
	{ ifds::TradeInDate,                  BFCBO::NONE,             0}, 
};

//******************************************************************************
XferOutFee::XferOutFee (BFAbstractCBO &parent) : TransFeeRate (parent, FEES::XFER_OUT),
_acqFeeDefault (NULL_STRING),
_pFromSideSplitCommissionList (NULL),
_side (I_("To"))
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   getWorkSession ().getOption ( ifds::AcqFeeDefault,                               
                                 _acqFeeDefault, 
                                 BF::HOST,
                                 false);         
}

//******************************************************************************
XferOutFee::~XferOutFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
   if (_pFromSideSplitCommissionList) //do not need the pointer
   {
      delete _pFromSideSplitCommissionList;
      _pFromSideSplitCommissionList = NULL;
   }
}

//******************************************************************************
SEVERITY XferOutFee::restore ( BFCBO &rpParent, 
                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("restore"));
   DString feeRate,
      flatPercent;

   rpParent.getField (ifds::Fee, feeRate, idDataGroup);
   getFormattedFee (idDataGroup, feeRate);
   rpParent.getField (ifds::FlatPercent, flatPercent, idDataGroup);
   setFieldNoValidate ( ifds::FeeRate, feeRate, idDataGroup, false, 
                        false, false, false);
   if (flatPercent == Y) //flat
   {
      setFieldNoValidate ( ifds::FeeType, I_("0"), idDataGroup, false, 
                           false, false, false);
   }
   else if (flatPercent == N) //percent
   {
      setFieldNoValidate ( ifds::FeeType, I_("1"), idDataGroup, false, 
                           false, false, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool XferOutFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return !SplitCommission::isTypeZERO (getWorkSession ());
}

//******************************************************************************
bool XferOutFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   return (transType == TRADETYPE::EXCHANGE || transType == TRADETYPE::INTER_CLASS_SWITCH || transType == TRADETYPE::TRANSFER) &&
			  !isFeeWaivedForAccount (idDataGroup) &&
			  isApplicableForFund (idDataGroup) &&
			  isNotROAXferEnvironment (idDataGroup);
   }
   return false;
}

//******************************************************************************
bool XferOutFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
//fee needs to be refreshed if any of the 158 related fields changed
   return hasFieldContextChanged (ifds::FromFund, idDataGroup) ||
          hasFieldContextChanged (ifds::FromClass, idDataGroup) ||
          hasFieldContextChanged (ifds::ToFund, idDataGroup) ||
          hasFieldContextChanged (ifds::ToClass, idDataGroup) ||
          hasFieldContextChanged (ifds::AmtType, idDataGroup) ||
          hasFieldContextChanged (ifds::EffectiveDate, idDataGroup) ||
          hasFieldContextChanged (ifds::SettleCurrency, idDataGroup) ||
          hasFieldContextChanged (ifds::AccountTo, idDataGroup) ||
          hasFieldContextChanged (ifds::Broker, idDataGroup) ||
          hasFieldContextChanged (ifds::Branch, idDataGroup) ||
          hasFieldContextChanged (ifds::SlsrepCode, idDataGroup) ||
		  hasFieldContextChanged (ifds::TradeInDate, idDataGroup) ||
          hasFieldContextChanged (ifds::ROAAmount, idDataGroup);
}

//******************************************************************************
SEVERITY XferOutFee::doValidateField ( const BFFieldId &idField, 
                                       const DString &strValue, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   
   if (idField == ifds::FeeRate) //the maximum should be validated against the split commission list
   {
      assert (getParent() && getParent()->getParent());
      
      Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
      SplitCommissionList *pSplitCommissionList = NULL;

      if (_side == I_("To"))
      {
         if (pTrade)
         {
            pTrade->getSplitCommissionList (pSplitCommissionList, idDataGroup);
         }
      }
      else if (_side == I_("From"))
      {
         if (_pFromSideSplitCommissionList)
         {
            pSplitCommissionList = _pFromSideSplitCommissionList;
         }
      }
      if (pSplitCommissionList)
      {
         DString maxFee,
            feeRate,
            initialTotalRate;
      
         pSplitCommissionList->getField (ifds::Fee, maxFee, idDataGroup, false);
         pSplitCommissionList->getInitialTotalRate (initialTotalRate, idDataGroup);
         getField (ifds::FeeRate, feeRate, idDataGroup, false);
         double dMaxFee = DSTCommonFunctions::convertToDouble (maxFee),
                  dFee = DSTCommonFunctions::convertToDouble (feeRate),
                  dInitialTotalRate = DSTCommonFunctions::convertToDouble (initialTotalRate);
      
         SplitCommissionList::canFeeBeDiscounted ( pSplitCommissionList,
			                                       getWorkSession (), 
                                                   dFee, 
                                                   dInitialTotalRate, 
                                                   dMaxFee, 
                                                   idDataGroup);
      }
   }
   else
   {
      TransFeeRate::doValidateField (idField, strValue, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY XferOutFee::doApplyRelatedChanges ( const BFFieldId &idField, 
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   if (TransFeeRate::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
      if (idField == ifds::FeeRate)
      {
         assert (getParent() && getParent()->getParent());
         
         Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
         SplitCommissionList *pSplitCommissionList = NULL;

         if (_side == I_("To"))
         {
            if (pTrade)
            {
               pTrade->getSplitCommissionList (pSplitCommissionList, idDataGroup);
            }
         }
         else if (_side == I_("From"))
         {
            if (_pFromSideSplitCommissionList)
            {
               pSplitCommissionList = _pFromSideSplitCommissionList;
            }
         }
         if (pSplitCommissionList)
         {
            DString feeRate;

            getField (ifds::FeeRate, feeRate, idDataGroup, false);
//set the total rate to the split comm list
            DString totalRate;

            pSplitCommissionList->getSplitTotalRate (totalRate, idDataGroup);
            double dblTotalRate = DSTCommonFunctions::convertToDouble (totalRate);
            double dblFeeRate = DSTCommonFunctions::convertToDouble (feeRate);
            if (dblTotalRate != dblFeeRate)
            {
               pSplitCommissionList->setField ( ifds::Rate, 
                                                feeRate, 
                                                idDataGroup, 
                                                false, 
                                                true);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY XferOutFee::setFeeType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeType"));
   DString feeType (I_("1")); //percent

   setFieldReadOnly (ifds::FeeType, idDataGroup, true);
   setFieldNoValidate (ifds::FeeType, feeType, idDataGroup, false, false, true, false);
   setFieldNoValidate (ifds::OrigFeeType, feeType, idDataGroup, false, false, true, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY XferOutFee::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeDefault"));
//set the fee currency
   DString fromFund, 
      fromClass, 
      toFund, 
      toClass;

   getContext().getField (ifds::FromFund, fromFund, idDataGroup);
   getContext().getField (ifds::FromClass, fromClass, idDataGroup);
   getContext().getField (ifds::ToFund, toFund, idDataGroup);   
   getContext().getField (ifds::ToClass, toClass, idDataGroup);
   FundDetail *pToFundDetail = NULL,
      *pFromFundDetail = NULL;

   if ( !toFund.empty() && 
        !toClass.empty() &&
        getWorkSession().
           getFundDetail (toFund, toClass, idDataGroup, pToFundDetail) && 
        pToFundDetail &&
        !fromFund.empty() &&
        !fromClass.empty() &&
        getWorkSession().
           getFundDetail (fromFund, fromClass, idDataGroup, pFromFundDetail) && 
        pFromFundDetail)
   {
      DString toLoadType,
         fromLoadType;
      FundToList fundToList (*this);
      bool bIsNewMoney = fundToList.isBuySell (fromFund, fromClass, toFund, toClass),
         bReadOnly = true,
         bZeroFee = false;
      DString feeRate (I_("0"));

      pToFundDetail->getField (ifds::LoadType, toLoadType, idDataGroup, false);
      pFromFundDetail->getField (ifds::LoadType, fromLoadType, idDataGroup, false);
//the commission is applicable for not new money exchanges/transfers,
//or new money for BEL funds from side

      if (!bIsNewMoney)
      {
         if (fromLoadType != I_("BEL"))
         {
            bReadOnly = false;
         }
         else
         {
            bZeroFee = true;
         }
//get the split commission from trade....
         assert (getParent() && getParent()->getParent());
         
         Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

         if (pTrade && !bZeroFee)
         {
            SplitCommissionList *pSplitCommissionList = NULL;

            if ( pTrade->getSplitCommissionList (pSplitCommissionList, idDataGroup) <= WARNING &&
                 pSplitCommissionList)
            {
               pSplitCommissionList->getSplitTotalRate (feeRate, idDataGroup);
			    
			   DString dstrTaxTypeMaxFee = pSplitCommissionList->getTaxTypeMaxFee(idDataGroup);
			   if( !dstrTaxTypeMaxFee.empty() )
			   {
				   BigDecimal bdTotalRate(feeRate);
				   BigDecimal bdTaxTypeMaxFee(dstrTaxTypeMaxFee);

				   if( bdTaxTypeMaxFee < bdTotalRate)
				   {
					   feeRate = dstrTaxTypeMaxFee;
					   pSplitCommissionList->propagateTotalRate(feeRate,idDataGroup);	
				   }
			   }
            }
         }
      }
      else //new money, from side
      {
         DString transType,
            account, 
            accountTo,
            pud, 
            flatPrcnt,
            inPayType,
            iAmount,
            effectiveDate,
			tradeInDate,
            inGrossNet,
            brokerCode,
            branchCode,
            slsrepCode,
            exchRate,
            settleCurrency;

         if (hasContextChanged (idDataGroup) && _pFromSideSplitCommissionList) //do not need the pointer
         {
            delete _pFromSideSplitCommissionList;
            _pFromSideSplitCommissionList = NULL;
         }
         if (!_pFromSideSplitCommissionList)
         {
            _pFromSideSplitCommissionList = new SplitCommissionList (*this);
            getContext().getField (ifds::TransType, transType, idDataGroup, false);
            getContext().getField (ifds::AccountNum, account, idDataGroup, false);
            getContext().getField (ifds::AccountTo, accountTo, idDataGroup, false);
            getContext().getField (ifds::AmtType, pud, idDataGroup, false);
            getContext().getField (ifds::TradesPayType, inPayType, idDataGroup, false);
            getContext().getField (ifds::Amount, iAmount, idDataGroup, false);
            getContext().getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);
			getContext().getField (ifds::TradeInDate, tradeInDate, idDataGroup, false);
            getContext().getField (ifds::GrossOrNet, inGrossNet, idDataGroup, false);
            getContext().getField (ifds::Broker, brokerCode, idDataGroup, false);
            getContext().getField (ifds::Branch, branchCode, idDataGroup, false);
            getContext().getField (ifds::SlsrepCode, slsrepCode, idDataGroup, false);
            getContext().getField (ifds::SettleCurrency, settleCurrency, idDataGroup, false);
            getContext().getField (ifds::ExchRate, exchRate, idDataGroup, false);

            if (_pFromSideSplitCommissionList->init ( account, 
                                                      accountTo, 
                                                      fromFund, 
                                                      toFund, 
                                                      fromClass,
                                                      toClass, 
                                                      pud, 
                                                      I_("N"), 
                                                      inPayType, 
                                                      iAmount, 
                                                      transType, 
                                                      effectiveDate,
                                                      inGrossNet, 
                                                      brokerCode, 
                                                      branchCode, 
                                                      slsrepCode, 
                                                      settleCurrency,
                                                      I_("From"),
                                                      exchRate,
                                                      NULL_STRING,
													  NULL_STRING,
													  tradeInDate,
                                                      idDataGroup) > WARNING)
            {
               delete _pFromSideSplitCommissionList;
               _pFromSideSplitCommissionList = NULL;
            }
         }
         if (_pFromSideSplitCommissionList)
         {
            _pFromSideSplitCommissionList->getSplitTotalRate (feeRate, idDataGroup);
            _side = I_("From");
         }
      }
      setFieldReadOnly (ifds::FeeRate, idDataGroup, bReadOnly);
      setFieldReadOnly (ifds::TradeFeeOption, idDataGroup, bReadOnly); 
      getFormattedFee (idDataGroup, feeRate);
      if (_acqFeeDefault == Y)
      {
         setFieldNoValidate (ifds::FeeRate, feeRate, idDataGroup, false, false, true, false);
         setFieldNoValidate (ifds::OrigFeeRate, feeRate, idDataGroup, false, false, true, false);
      }

//set fee currency
      DString fundCurrency;

      pToFundDetail->getField (ifds::Currency, fundCurrency, idDataGroup, false);
      setField (ifds::Currency, fundCurrency, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY XferOutFee::setFeeMinMax (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeMinMax"));
//nothing to do here, min max are validated against split commission list
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool XferOutFee::isApplicableForFund (const BFDataGroupId &idDataGroup)
{
   bool bIsApplicable = false;
   DString fromFund, 
      fromClass, 
      toFund, 
      toClass;

   getContext().getField (ifds::FromFund, fromFund, idDataGroup);
   getContext().getField (ifds::FromClass, fromClass, idDataGroup);
   getContext().getField (ifds::ToFund, toFund, idDataGroup);   
   getContext().getField (ifds::ToClass, toClass, idDataGroup);
   FundDetail *pToFundDetail = NULL,
      *pFromFundDetail = NULL;

   return !toFund.empty() && 
          !toClass.empty() &&
           getWorkSession().getFundDetail (toFund, toClass, idDataGroup, pToFundDetail) && 
           pToFundDetail &&
           !fromFund.empty() &&
           !fromClass.empty() &&
           getWorkSession().getFundDetail (fromFund, fromClass, idDataGroup, pFromFundDetail) && 
           pFromFundDetail;
}

//******************************************************************************
SEVERITY XferOutFee::setFeeProperties (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeProperties"));
   TransFeeRate::setFeeProperties (idDataGroup);
   setFieldReadOnly (ifds::ChargeOption, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************
bool XferOutFee::isNotROAXferEnvironment (const BFDataGroupId &idDataGroup) 
{
    bool bRet = true;
    Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

    if (pTrade)
    {
      if (pTrade->isROAApplicable (idDataGroup))
      {
         DString roaAmount;
      
         getContext().getField (ifds::ROAAmount, roaAmount, idDataGroup);
         bRet = DSTCommonFunctions::convertToDouble (roaAmount) <= 0;
      }
    }
    return bRet;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/XferOutFee.cpp-arc  $
// 
//    Rev 1.16   Jul 31 2012 16:41:18   wp040027
// Sync up: IN# 3006862-CPF-Enable Fee in PAC/Corrected default Fee in PAC and Trade screen/Max Fee Validation
// 
//    Rev 1.15   Jul 26 2012 10:50:40   wp040027
// P0198518 - RDR Functionality
// 
//    Rev 1.14   Nov 27 2011 19:44:08   popescu
// INA Commission Work
// 
//    Rev 1.13   Mar 04 2011 12:10:46   jankovii
// PET181943 FN01 - XMLPhase 2
// 
//    Rev 1.12   Jul 07 2005 17:53:00   popescu
// Incident# 350901 - removed split commissions when not needed, do not call split commissions when trade is roa applicable, trans type is transfer and side of the splits is To
// 
//    Rev 1.11   Jul 04 2005 19:05:34   popescu
// Incident # 347073 - split commission is charged on the To side for environments where ROA is applicable.
// 
//    Rev 1.10   May 24 2005 15:57:46   yingbaol
// PET1203,FN01:fix splitcommission
// 
//    Rev 1.9   May 18 2005 09:03:46   yingbaol
// PET1203,FN01 Commission-Class A enhancement
// 
//    Rev 1.8   Mar 03 2005 08:14:00   popescu
// PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
// 
//    Rev 1.7   Feb 22 2005 14:05:02   popescu
// Incident #249310, validation of split commissions should be done against the initial total value, rather then 0 amount
// 
//    Rev 1.6   Jan 31 2005 10:05:38   popescu
// PTS 10038324, set charge option field to read only, there is no set-up for it.
// 
//    Rev 1.5   Jan 28 2005 11:08:02   popescu
// PTS 10038324, fees display issues
// 
//    Rev 1.4   Jan 28 2005 06:58:12   aguilaam
// PTS 10038324, fees display issues
// 
//    Rev 1.3   Jan 21 2005 16:55:50   popescu
// PTS 10038132, not show the fees if from fund/ and class are not entered
// 
//    Rev 1.2   Dec 08 2004 22:08:38   popescu
// PET 1117/06, more fees
// 
//    Rev 1.1   Nov 18 2004 13:44:58   YINGBAOL
// PET1117:  performance tunning 
// 
//    Rev 1.0   Nov 17 2004 15:56:08   popescu
// Initial revision.
// 
//    Rev 1.2   Nov 15 2004 16:22:30   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.0   Nov 10 2004 09:31:14   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 06 2004 00:35:04   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 04 2004 11:03:16   popescu
// Initial revision.
// 
 */