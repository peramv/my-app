#define IFASTCBO_DLL

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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : SplitCommissionList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : February  26, 2001
//
// ^CLASS    : SplitCommissionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "splitcommission.hpp"
#include "splitcommissionlist.hpp"

#include "broker.hpp"
#include "brokerlist.hpp"
#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "fundtolist.hpp"
#include "mgmtco.hpp"
#include "trade.hpp"
#include "tradefundalloc.hpp"
#include "tradingfeerules.hpp"
#include "transactiondetails.hpp"
#include "ifastcbo\mfaccount.hpp"
#include "taxtyperule.hpp"
#include "taxtyperulelist.hpp"
#include "fundlmtoverridelist.hpp"
#include "fundlmtoverride.hpp"
#include "trademinamtcheck.hpp"
namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME			   = I_ ("SplitCommissionList");
   const I_CHAR * const NOT_NEGOTIABLE		   = I_ ("0");
   const I_CHAR * const ALLOWS_DISCOUNT		= I_ ("1");
   const I_CHAR * const FULLY_NEGOTIABLE	   = I_ ("2");
   const I_CHAR * const FLAT				      = I_ ("0");
   const I_CHAR * const PERCENT				   = I_ ("1");
   const I_CHAR * const RULE_TYPE_NON_SHARING_DISCOUNT = I_("52");
   //just to initialize the default total rate and check against this value
   //totals cannot be less then zero
   const double INIT_MAX_RATE = -1.0;
   const I_CHAR * const RDR_ADVICE_PROVIDED   = I_ ("02");
}


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SPLIT_COMMISSION_LIST;
   extern CLASS_IMPORT const DSTCRequest DEF_SPLIT_COMMISSION_LIST;
}

namespace CND
{
   extern const long ERR_IDENTICAL_SPLIT_COM;
   extern const long ERR_TOTAL_SPLIT_COMMISION_RATE_EXCEEDS_FEE_DEFAULT;
   extern const long ERR_SPLIT_COMMISSION_ONLY_DISCOUNTS_ALLOWED;
   extern const long ERR_PERCENTAGE_NOT_EQUAL_100;
   extern const long ERR_COMMISSION_IS_NOT_NEGOTIABLE;
   extern const long ERR_WARN_SPLICCOMAMOUNT_IS_GREATER;
   extern const long ERR_TOTAL_SPLIT_COMMISION_RATE_EXCEEDS_FEE_MAX;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId SlsrepCode;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;
   extern CLASS_IMPORT const BFDecimalFieldId FeePercent;
   extern CLASS_IMPORT const BFDecimalFieldId FeeOverrideType;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId MaxFeeAppl;
   extern CLASS_IMPORT const BFDecimalFieldId MinInitAmt;
   extern CLASS_IMPORT const BFDecimalFieldId BrkOverideAmt;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
   extern CLASS_IMPORT const BFDecimalFieldId MaxFee;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT_2;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN_2;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
}

//these fields are needed to get the default fee value by calling view 197
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//   Field DD Id,        State Flags,       Group Flags 
   {ifds::Account,        BFCBO::NONE, 0}, 
   {ifds::BrokerCode,     BFCBO::NONE, 0}, 
   {ifds::BranchCode,     BFCBO::NONE, 0}, 
   {ifds::SlsrepCode,     BFCBO::NONE, 0}, 
   {ifds::Fund,           BFCBO::NONE, 0}, 
   {ifds::Class,          BFCBO::NONE, 0}, 
   {ifds::EffectiveDate,  BFCBO::NONE, 0}, 
   {ifds::TransType,      BFCBO::NONE, 0},
   {ifds::Amount,         BFCBO::NONE, 0},
   {ifds::Rate,           BFCBO::NONE, 0},
   {ifds::FeeType,        BFCBO::NONE, 0},
   {ifds::MaxFeeRate,     BFCBO::CALCULATED_FIELD, 0},
   {ifds::CommEntType,    BFCBO::NONE, 0},
   {ifds::CommRate,       BFCBO::NONE, 0},
   {ifds::RDRAdvice,      BFCBO::NONE, 0},
   { ifds::TradeInDate,   BFCBO::NONE, 0},

};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
bool SplitCommissionList::commissionNotNegotiable (const DString &feeOverrideType)
{
   return feeOverrideType == NULL_STRING || feeOverrideType == NOT_NEGOTIABLE;
}

//******************************************************************************
bool SplitCommissionList::commissionAllowsDiscount (const DString &feeOverrideType)
{
   return feeOverrideType == ALLOWS_DISCOUNT;
}

//******************************************************************************
bool SplitCommissionList::commissionFullyNegotiable (const DString &feeOverrideType)
{
   return feeOverrideType == FULLY_NEGOTIABLE;
}

//******************************************************************************
SEVERITY SplitCommissionList::canFeeBeDiscounted ( SplitCommissionList *pSplitCommissionList,
												               DSTCWorkSession &rpDSTCWorkSession, 
                                                   const double &dFee,
                                                   const double &dInitialTotalRate,
                                                   const double &dMaxRate,
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("canFeeBeDiscounted"));
   
   DString feeOverrideType;
   
   if (pSplitCommissionList)
   {
      DString dstrFeeType;

      pSplitCommissionList->getField (ifds::FeeType, dstrFeeType, idDataGroup, false);

      if (dstrFeeType == FLAT)
      {
         return GETCURRENTHIGHESTSEVERITY ();
      }
   }
   if( bIsTaxLevelOverride4MaxFeeNotAllowed(pSplitCommissionList,rpDSTCWorkSession,idDataGroup))
   {
	   DString dstrMaxFeeRate;
	   pSplitCommissionList->getField (ifds::MaxFeeRate, dstrMaxFeeRate, idDataGroup, false);
	   if( !dstrMaxFeeRate.empty() )
	   {
		   double maxFeeRate = DSTCommonFunctions::convertToDouble (dstrMaxFeeRate);

		   if( maxFeeRate > INIT_MAX_RATE && (dFee - maxFeeRate) > .0000000001 )
		   {
			   DString strIDI,maxTotal; 
			   maxTotal = DSTCommonFunctions::doubleToDString (ifds::CommAmount, maxFeeRate);
			   DSTCommonFunctions::DisplayFormat( maxTotal, ifds::CommAmount );
			   addIDITagValue (strIDI, I_ ("MAX"), maxTotal);
			   ADDCONDITIONFROMFILEIDI (CND::ERR_TOTAL_SPLIT_COMMISION_RATE_EXCEEDS_FEE_MAX, strIDI);
			   return GETCURRENTHIGHESTSEVERITY ();
		   }
	   }
   }
   rpDSTCWorkSession.getOption (ifds::FeeOverrideType, feeOverrideType, BF::HOST, false);
   //when commision is not negotiable the renunciation can't be different then zero
   if (commissionNotNegotiable (feeOverrideType) && 
      fabs (dFee - dInitialTotalRate) > .0000000001)
   {
      //Need to add proper condition.
      ADDCONDITIONFROMFILE (CND::ERR_COMMISSION_IS_NOT_NEGOTIABLE);
      return GETCURRENTHIGHESTSEVERITY ();
   }
   //tells to ignore renunciation only if a discount is allowed
   if (commissionAllowsDiscount (feeOverrideType) && 
      dMaxRate == INIT_MAX_RATE &&
      dFee - dInitialTotalRate > .0000000001) 
   {
      //only discounts are allowed
      ADDCONDITIONFROMFILE (CND::ERR_SPLIT_COMMISSION_ONLY_DISCOUNTS_ALLOWED);
      return GETCURRENTHIGHESTSEVERITY ();
   }
   //if only discounts are allowed, but the total exceeds the default value of the fee
   //if exists
   if (commissionAllowsDiscount (feeOverrideType) && 
      dMaxRate > INIT_MAX_RATE && 
      dFee - dMaxRate > .0000000001)
   {
      DString strIDI, 
         defaultTotal;

      defaultTotal = DSTCommonFunctions::doubleToDString (ifds::CommAmount, dMaxRate);
      DSTCommonFunctions::DisplayFormat( defaultTotal, ifds::CommAmount );
      addIDITagValue (strIDI, I_ ("DEFAULT"), defaultTotal);
      ADDCONDITIONFROMFILEIDI (CND::ERR_TOTAL_SPLIT_COMMISION_RATE_EXCEEDS_FEE_DEFAULT, strIDI);
      return GETCURRENTHIGHESTSEVERITY ();
   }
   

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
DString SplitCommissionList::calculateBaseCommission (const DString &feeDefaultRate_,
                                                      const DString &sfacRate_)
{
   DString baseCommission (NULL_STRING),
      sfacRate(sfacRate_),
      feeDefaultRate(feeDefaultRate_);

   sfacRate.stripLeading('0');
   feeDefaultRate.stripLeading('0');
   if (!sfacRate.empty() && !feeDefaultRate.empty())
   {
      BigDecimal bdFee = DSTCommonFunctions::convertToBigDecimal (feeDefaultRate);
      if(bdFee == DSTCommonFunctions::convertToBigDecimal (I_("0")))
      {
         baseCommission = feeDefaultRate_;
      }
      else
      {
         BigDecimal bdSFACRate = DSTCommonFunctions::convertToBigDecimal (sfacRate);
         BigDecimal bd1 = DSTCommonFunctions::convertToBigDecimal (I_("1"));
         BigDecimal bd100 = DSTCommonFunctions::convertToBigDecimal (I_("100"));
         BigDecimal bdBaseComm = bdFee / (bd1 + bdSFACRate/bd100);
         baseCommission = bdBaseComm.asDString ();
      }
   }
   return baseCommission;
}

//******************************************************************************
SplitCommissionList::SplitCommissionList (BFAbstractCBO &parent): 
MFCanBFCbo (parent),
_maxRate (INIT_MAX_RATE),
_initialTotalRate (0.0),
_callDefault (false),
_hasSplits (false),
_bSkipCal (false)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   setObjectAsList ();
   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
}

//******************************************************************************
SplitCommissionList::~SplitCommissionList (void)
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY SplitCommissionList::init ( const DString& dstrTransNum,
                                     const DString& dstrTransSeq, 
                                     const DString& dstrTransType,
                                     const DString& dstrAccountNum, 
                                     const DString& dstrFund, 
                                     const DString& dstrClass,
                                     const DString& dstrBrokerCode, 
                                     const DString& dstrBranchCode,
                                     const DString& dstrSlsRepCode, 
                                     const DString& dstrEffectiveDate,
                                     const DString& transId,
                                     const DString& rdrAdvice,
                                     const BFDataGroupId& idDataGroup /*=BF::HOST*/,
                                     const DString& dstrTrack /*=I_ ("N")*/, 
                                     const DString& dstrPageName /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));   

   BFData reqData (ifds::DSTC0151_REQ);//151 request
   DString mgmtCoIdOut;
   
   setFieldNoValidate (ifds::FeeType, PERCENT, idDataGroup);
   setFieldNoValidate (ifds::Account, dstrAccountNum, idDataGroup);
   setFieldNoValidate (ifds::Fund, dstrFund, idDataGroup);
   setFieldNoValidate (ifds::Class, dstrClass, idDataGroup);
   setFieldNoValidate (ifds::TransType, dstrTransType, idDataGroup);
   setFieldNoValidate (ifds::BrokerCode, dstrBrokerCode, idDataGroup);
   setFieldNoValidate (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
   setFieldNoValidate (ifds::RDRAdvice, rdrAdvice, idDataGroup);

   reqData.setElementValue (ifds::TransNum, dstrTransNum);
   reqData.setElementValue (ifds::TransType, dstrTransType);
   reqData.setElementValue (ifds::TransSeq, dstrTransSeq);
   reqData.setElementValue (ifds::TransId, transId);
   reqData.setElementValue (ifds::AccountNum, dstrAccountNum);
   reqData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   reqData.setElementValue (ifds::Track, dstrTrack);
   reqData.setElementValue (ifds::Activity, dstrPageName);   
   DString transType (dstrTransType);

   if (dstrTransType == TRADETYPE::AUTO_TRANSFER)
   {
      transType = TRADETYPE::TRANSFER_IN;
   }
   commonInit ( reqData, 
                transType, 
                dstrAccountNum, 
                dstrFund, 
                dstrClass, 
                dstrBrokerCode,
                dstrBranchCode, 
                dstrSlsRepCode, 
                dstrEffectiveDate,
				NULL_STRING,
                rdrAdvice,
                idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY SplitCommissionList::init ( const DString& dstrAccount,
                                     const DString& dstrAccountTo,
                                     const DString& dstrFund,
                                     const DString& dstrFundTo,
                                     const DString& dstrClass,
                                     const DString& dstrClassTo,
                                     const DString& dstrPUD,
                                     const DString& dstrFlatPrcnt,
                                     const DString& dstrInPayType,
                                     const DString& dstrIAmount,
                                     const DString& dstrInTransType,
                                     const DString& dstrEffectiveDate,
                                     const DString& dstrInGrossNet,
                                     const DString& dstrBrokerCode,
                                     const DString& dstrBranchCode,
                                     const DString& dstrSlsRepCode,
                                     const DString& dstrSettleCurrency,
                                     const DString& dstrInRecordType,
                                     const DString& exchRate,
                                     const DString& investTerm,
									 const DString& rdrAdvice,
									 const DString& dstrTradeInDate,
                                     const BFDataGroupId& idDataGroup /*=BF::HOST*/,
                                     const DString& dstrTrack /*=I_ ("N")*/,
                                     const DString& dstrPageName /*=NULL_STRING*/) 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));

   BFData reqData (ifds::DSTC0158_REQ);
   DString mgmtCoIdOut;
   DString dstrTransType (dstrInTransType),
           dstrRecordType (dstrInRecordType);
   
   DString dstrFeeType = dstrFlatPrcnt == I_("N") ? PERCENT : FLAT; 

   _callDefault = true;
   _dstrAmount = dstrIAmount;

   setFieldNoValidate (ifds::Account, dstrAccount, idDataGroup);
   setFieldNoValidate (ifds::BrokerCode, dstrBrokerCode, idDataGroup);
   setFieldNoValidate (ifds::BranchCode, dstrBranchCode, idDataGroup);
   setFieldNoValidate (ifds::SlsrepCode, dstrSlsRepCode, idDataGroup);
   setFieldNoValidate (ifds::Fund, dstrFund, idDataGroup);
   setFieldNoValidate (ifds::Class, dstrClass, idDataGroup);
   setFieldNoValidate (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
   setFieldNoValidate (ifds::FeeType, dstrFeeType, idDataGroup);
   setFieldNoValidate (ifds::RDRAdvice, rdrAdvice, idDataGroup);
   setFieldNoValidate (ifds::TradeInDate, dstrTradeInDate, idDataGroup);
   //modify the transaction type to support the back-end
   if (dstrTransType == TRADETYPE::PAC) //for PAC
   {
      dstrTransType = TRADETYPE::PURCHASE;
   }
   else if (dstrTransType == TRADETYPE::SWP) //for SWP
   {
      dstrTransType = I_ ("AW");
   }
   else if ( dstrTransType == TRADETYPE::AUTO_TRANSFER  || //for automatic transfer
             dstrTransType == TRADETYPE::TRANSFER_IN    || 
             dstrTransType == TRADETYPE::TRANSFER_IN_2  || 
             dstrTransType == TRADETYPE::TRANSFER_OUT   ||
             dstrTransType == TRADETYPE::TRANSFER_OUT_2 ||
             dstrTransType == TRADETYPE::EXCHANGE ||
             dstrTransType == TRADETYPE::INTER_CLASS_SWITCH) 
   {
      dstrTransType = TRADETYPE::TRANSFER;
   } 
   else if (dstrTransType == TRADETYPE::PURCHASE)
   {
      dstrTransType = I_ ("DD");
   }
   setFieldNoValidate (ifds::TransType, dstrTransType, idDataGroup);
   //we have to figure the value of record type if it is null string
   if (dstrRecordType == NULL_STRING)
   {
      dstrRecordType = I_("From"); //by default
      //the general case the record type should be 'From'
      if (dstrTransType == TRADETYPE::TRANSFER)
      {
			FundToList  fundToList (*this);
			DString fromFund (dstrFund),
			   fromClass (dstrClass),
			   toFund (dstrFundTo),
			   toClass (dstrClassTo);
//new money, look at split commission of the to side of the trade
			if ( fundToList.isBuySell (fromFund, fromClass, toFund, toClass) ||
              isROAApplicable (idDataGroup))
			{
				dstrRecordType = I_("To");
			}
      }
   }
   if ( dstrTransType == TRADETYPE::TRANSFER &&
        dstrRecordType == I_("From"))
   {
      TradeFundAlloc *pTradeFundAlloc = dynamic_cast <TradeFundAlloc *> (getParent());

      if (pTradeFundAlloc)
      {
         BFCBO *pTopLevelCBO = pTradeFundAlloc->getTopLevelCBO();
         Trade *pTrade = dynamic_cast <Trade*> (pTopLevelCBO);

         if (pTrade && pTrade->isROAApplicable (idDataGroup))
         {
            //no need for splits in this case, cycle will assign the right commissions
            //Incident# 350901 - MFS project PET 1203/05
            return GETCURRENTHIGHESTSEVERITY (); 
         }
      }
   }
   reqData.setElementValue (ifds::Account, dstrAccount);
   reqData.setElementValue (ifds::AccountTo, dstrAccountTo);
   reqData.setElementValue (ifds::Fund, dstrFund);
   reqData.setElementValue (ifds::FundTo, dstrFundTo);
   reqData.setElementValue (ifds::Class, dstrClass);
   reqData.setElementValue (ifds::ClassTo, dstrClassTo);
   reqData.setElementValue (ifds::PUD, dstrPUD);
   reqData.setElementValue (ifds::FlatPrcnt, dstrFlatPrcnt);
   reqData.setElementValue (ifds::InPayType, dstrInPayType);
   reqData.setElementValue (ifds::IAmount, dstrIAmount);
   reqData.setElementValue (ifds::InTransType, dstrTransType);
   reqData.setElementValue (ifds::EffectiveDate, dstrEffectiveDate, false, false);
   reqData.setElementValue (ifds::InGrossNet, dstrInGrossNet);
   reqData.setElementValue (ifds::InBrokerCode, dstrBrokerCode);
   reqData.setElementValue (ifds::InBranchCode, dstrBranchCode);
   reqData.setElementValue (ifds::InSlsRepCode, dstrSlsRepCode);
   reqData.setElementValue (ifds::SettleCurrency, dstrSettleCurrency);
   reqData.setElementValue (ifds::RecordType, dstrRecordType);
   reqData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   reqData.setElementValue (ifds::Track, dstrTrack);
   reqData.setElementValue (ifds::Activity, dstrPageName);
   reqData.setElementValue (ifds::ExchRate, exchRate);
   reqData.setElementValue (ifds::InvestTerm, investTerm);
   reqData.setElementValue (ifds::TradeInDate, dstrTradeInDate, false, false);
   commonInit ( reqData, 
                dstrTransType, 
                dstrAccount, 
                dstrFund, 
                dstrClass, 
                dstrBrokerCode,
                dstrBranchCode, 
                dstrSlsRepCode, 
                dstrEffectiveDate,
				dstrTradeInDate,
				rdrAdvice,
                idDataGroup);
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY SplitCommissionList::commonInit ( BFData& reqData,   
                                           const DString& dstrTransType,
                                           const DString& dstrAccountNum, 
                                           const DString& dstrFund, 
                                           const DString& dstrClass,
                                           const DString& dstrBrokerCode, 
                                           const DString& dstrBranchCode,
                                           const DString& dstrSlsRepCode, 
                                           const DString& dstrEffectiveDate,
										   const DString& dstrTradeInDate,
										   const DString& dstrRDRAdvice,
										   const BFDataGroupId& idDataGroup /*=BF::HOST*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("commonInit"));
   SEVERITY severity = NO_CONDITION;

   if (_callDefault)
   {
      BFData* receivedData = new BFData (ifds::DSTC0158_VW);
   
      if ( (severity = BFDataBroker::getInstance ()->
            receive ( DSTC_REQUEST::DEF_SPLIT_COMMISSION_LIST, 
                      reqData, 
                      *receivedData, 
                      DSTCRequestor (getSecurity (), 
                      true ))) <= WARNING)
	  {
		  //attach this object to the list, the base should delete it
		  attachDataObject (*receivedData, true);
		  
		  if(dstrRDRAdvice != RDR_ADVICE_PROVIDED)
		  {
			  int repeats = receivedData->getRepeatCount ();

			  _hasSplits = repeats > 0;
			  for (int i = 0; i < repeats; i++)
			  {
				  const BFData& repeatData = receivedData->getRepeat (i);
				  BFData *p151BFData = new BFData (ifds::DSTC0151_VWRepeat_Record);
				  SplitCommission *pSplitCommission = new SplitCommission (*this);
				  //copy 158 over to 151
				  //fields named differently are:
				  p151BFData->setElementValue (ifds::GrossOrNet,
					  repeatData.getElementValue (ifds::GrossNet), false, false);
				  //init the object and copy all the fields that have the same name
				  pSplitCommission->init (*p151BFData);
				  pSplitCommission->setData (repeatData, BF::HOST);
				  pSplitCommission->setAllFieldsValid (BF::HOST);
				  //we do not need validation for the copied fields
				  CLEARCONDITIONS ();
				  //find the key for this object               
				  DString dstrKey (NULL_STRING);

				  getStrKey (dstrKey, &repeatData);
				  setObject (pSplitCommission, dstrKey, OBJ_ACTIVITY_ADDED, idDataGroup);
				  pSplitCommission->setField (ifds::Default, I_ ("Y"), BF::HOST, false);
			  }
		  }
		  else
		  {
			  DString dstrRate;
			  receivedData->getElementValue(ifds::Fee, dstrRate);
			  addRDRAdviceProvidedCommission( dstrRate, idDataGroup /*=BF::HOST*/);
		  }
	  }
      else
      {
         delete receivedData;
      }
   }
   else
   {
      severity = ReceiveData ( DSTC_REQUEST::SPLIT_COMMISSION_LIST, 
                               reqData, 
                               ifds::DSTC0151_VW, 
                               DSTCRequestor (getSecurity (), 
                               false));
   }
   if (severity <= WARNING)
   {
      DString acctNum = dstrAccountNum,
            fundCode = dstrFund,
            classCode = dstrClass;

      //for transfers use the TO parameters
      if (dstrTransType == TRADETYPE::TRANSFER && _callDefault) 
      {
         acctNum = reqData.getElementValue (ifds::AccountTo);
         fundCode = reqData.getElementValue (ifds::FundTo);
         classCode = reqData.getElementValue (ifds::ClassTo);
      }
      //get the default fee rate, it comes in the fixed section of view 151 and 158
      DString feeDefaultRate;
      
      getField (ifds::Fee, feeDefaultRate, idDataGroup, false);
      _maxRate = DSTCommonFunctions::convertToDouble (feeDefaultRate);
      _initialTotalRate = 0.0;
      getSplitTotalRate (_initialTotalRate, idDataGroup);
      if (_hasSplits && _callDefault)
      {
         bool baseCommApplicable (false);
         DString sfacRate (NULL_STRING);

         TradeFundAlloc *pTradeFundAlloc = dynamic_cast <TradeFundAlloc *> (getParent());

	      if (pTradeFundAlloc)
	      {
		      BFCBO *pTopLevelCBO = pTradeFundAlloc->getTopLevelCBO();
            
		      Trade *pTrade = dynamic_cast <Trade*> (pTopLevelCBO);

            if ( pTradeFundAlloc &&
                 pTradeFundAlloc->isBaseCommissionApplicableAndGetSFACRate (baseCommApplicable, sfacRate, idDataGroup) <= WARNING &&
                 baseCommApplicable)
            {
               sfacRate.stripLeading('0');
               feeDefaultRate.stripLeading('0');
               if (!sfacRate.empty() && !feeDefaultRate.empty())
               {
                  _initialTotalRate = DSTCommonFunctions::convertToDouble (calculateBaseCommission (feeDefaultRate, sfacRate));
               }
            }
            else if (pTrade)
            {
               FundMasterList *pFundMasterList (NULL);

               if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
                    pFundMasterList)
               {
                  if (pFundMasterList->isGIAFund (fundCode))
                  {
                     DString commRedRate;

                     pTrade->getField (ifds::CommRedRate, commRedRate, idDataGroup, false);
                     commRedRate.stripLeading ('0');
                     if (!commRedRate.empty())
                     {
                        DString initialTotalRate;
                        
                        getSplitTotalRate (initialTotalRate, idDataGroup);
                        BigDecimal bdCommRedRate = DSTCommonFunctions::convertToBigDecimal (commRedRate);
                        BigDecimal bdInitialTotalRate = DSTCommonFunctions::convertToBigDecimal (initialTotalRate);
                        BigDecimal bdReducedRate (bdInitialTotalRate);
                        BigDecimal bd1 = DSTCommonFunctions::convertToBigDecimal (I_("1"));
                        BigDecimal bd100 = DSTCommonFunctions::convertToBigDecimal (I_("100"));

                        bdReducedRate = bdInitialTotalRate * (bd1 - bdCommRedRate/bd100);
                        _initialTotalRate = DSTCommonFunctions::convertToDouble (bdReducedRate.asDString ());
                     }
                  }
               }
            }
         }
      }	  
	  //calculate the amount field
      double dblTotalSplitAmount = 0.0;
      
      getSplitTotalAmount (dblTotalSplitAmount, idDataGroup);

      double dblAmount = _initialTotalRate != 0.0 ? dblTotalSplitAmount * 100 / _initialTotalRate : 0;
      DString dstrAmount = DSTCommonFunctions::doubleToDString (ifds::CommAmount, dblAmount);

      setFieldNoValidate (ifds::Amount, dstrAmount, BF::HOST);

      //end calculating the total amount, 
      //this will be used in recalculating the comm amounts, 
      //if the comm rates change
      //set the rate field
      setFieldNoValidate ( ifds::Rate, 
                           DSTCommonFunctions::doubleToDString (ifds::Rate, _initialTotalRate),
                           idDataGroup, 
                           false, 
                           true, 
                           false,
                           false);
      calculateFieldsBasedOnCommissionType (idDataGroup);
   }
   bool advReadOnly = dstrRDRAdvice == RDR_ADVICE_PROVIDED;

   BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end ())
   {
	   SplitCommission *pSplitCommission = dynamic_cast<SplitCommission *> (iter.getObject ());

	   if (pSplitCommission != NULL)
	   {
		   pSplitCommission->setFieldReadOnly(ifds::CommEntType,idDataGroup, advReadOnly);
		   pSplitCommission->setFieldReadOnly(ifds::CommRate,idDataGroup, advReadOnly);
	   }		
	   ++iter;
   }


   clearUpdatedFlags (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY SplitCommissionList::initDefaultFlatFeeData (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("initDefaultFlatFeeData"));

	BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

	while (!iter.end ())
	{
		SplitCommission *pSplitCommission = dynamic_cast<SplitCommission *> (iter.getObject ());

		if (pSplitCommission != NULL)
		{
			pSplitCommission->setField (ifds::CommPrcnt, I_("0"), idDataGroup, true, true);
			pSplitCommission->setField (ifds::CommAmount, I_("0"), idDataGroup, true, true);
			pSplitCommission->setField (ifds::CommRate, I_("0"), idDataGroup, true, true);
		}		
		++iter;
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY SplitCommissionList::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doApplyRelatedChanges"));
   if (idField == ifds::Amount && idDataGroup != BF::HOST && !shouldSkipCalculatingRatesAmounts (idDataGroup))
   {
      //recalculate the comm ammounts if the total amount of the allocation to which
      //this split commission belongs has changed
      BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
      DString dstrAmount;
      double dblAmount = 0.0;

      getField (ifds::Amount, dstrAmount, idDataGroup);
      dblAmount = DSTCommonFunctions::convertToDouble (dstrAmount);
      while (!iter.end ())
      {
         SplitCommission *pSplitCommission = 
            dynamic_cast<SplitCommission *> (iter.getObject ());

         if (pSplitCommission)
         {         
            DString dstrCommRate;
            double dblCommRate = 0.0;

            pSplitCommission->getField (ifds::CommRate, dstrCommRate, idDataGroup);
            dblCommRate = DSTCommonFunctions::convertToDouble (dstrCommRate); 

            //recalculate the new comm amount based on the comm percentage and the new total
            double dblCommAmount = dblCommRate * dblAmount / 100;
            DString dstrCommAmount = DSTCommonFunctions::doubleToDString (ifds::CommAmount, dblCommAmount);
         
            pSplitCommission->setField (ifds::CommAmount, dstrCommAmount, idDataGroup);
         }
         ++iter;
      }
   }
   else if (idField == ifds::FeeType)
   {
	  setFieldUpdated (ifds::FeeType, idDataGroup, false);
	  setValidFlag (ifds::FeeType, idDataGroup, true);	

   }
   else if (idField == ifds::Rate && idDataGroup != BF::HOST)
   {
      applyRateRelatedChanges (idDataGroup);
/*
   if (SplitCommission::isTypeTWO (getWorkSession()))
      {
         calculateFieldsBasedOnCommissionType (idDataGroup);
      }
	  else if (SplitCommission::isTypeONE (getWorkSession()))
	  {
         //if there's only one commission record, make sure that the commission percentage is 100%
		 BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
		 if( iter.getNumberOfItemsInList() == 1 )
		 {
			 iter.getObject()->setField( ifds::CommPrcnt, I_("100.00"), idDataGroup, false );
		 }
	  }

     bool bNonSharingDiscount = false;
     isNonSharingDiscount(bNonSharingDiscount, idDataGroup);
     
     if(bNonSharingDiscount)
     {
         calculateNonSharingSplitCommission(idDataGroup);
     }
     else
     {
      //propagate the total rate onto the splits
         BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

         while (!iter.end ())
         {
            SplitCommission *pSplitCommission = 
               dynamic_cast<SplitCommission *> (iter.getObject ());

            if (pSplitCommission)
            {
               if (SplitCommission::isTypeONE (getWorkSession()))
               {

                  //based on the existing percentages recalculate the each rate
                  DString rate,
                     commPrcnt,
                     commRate;

                  getField (ifds::Rate, rate, idDataGroup, false);
                  double dblRate = DSTCommonFunctions::convertToDouble (rate);
                  double dblCommRate = 0.0, 
                     dblCommPrcnt = 0.0;

                  pSplitCommission->getField (ifds::CommPrcnt, commPrcnt, idDataGroup);
                  dblCommPrcnt = DSTCommonFunctions::convertToDouble (commPrcnt);
                  dblCommRate = dblCommPrcnt * dblRate / 100;
                  commRate = DSTCommonFunctions::doubleToDString (ifds::CommRate, dblCommRate);
                  _bSkipCal = true;
                  pSplitCommission->setField (ifds::CommRate, commRate, idDataGroup, true, true);
                  _bSkipCal = false;
               }
               //in any case recalculate the amount
               pSplitCommission->calculateTheCommissionAmount (idDataGroup);
            }
            ++iter;
         }
      }
*/   
   }
   else if(idField == ifds::RDRAdvice)
   {
       DString dstrRDRAdvice;
	   getField (ifds::RDRAdvice, dstrRDRAdvice, idDataGroup);

	   bool advReadOnly = dstrRDRAdvice == RDR_ADVICE_PROVIDED; 
 
	   BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

	   while (!iter.end ())
	   {
		   SplitCommission *pSplitCommission = dynamic_cast<SplitCommission *> (iter.getObject ());

		   if (pSplitCommission != NULL)
		   {
			   pSplitCommission->setFieldReadOnly(ifds::CommEntType,idDataGroup, advReadOnly);
			   pSplitCommission->setFieldReadOnly(ifds::CommRate,idDataGroup, advReadOnly);
		   }		
		   ++iter;
	   }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY SplitCommissionList::applyRateRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("applyRateRelatedChanges"));


   if (SplitCommission::isTypeTWO (getWorkSession()))
   {
      calculateFieldsBasedOnCommissionType (idDataGroup);
   }
   else if (SplitCommission::isTypeONE (getWorkSession()))
   {
      //if there's only one commission record, make sure that the commission percentage is 100%
      BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
      if( iter.getNumberOfItemsInList() == 1 )
      {
         iter.getObject()->setField( ifds::CommPrcnt, I_("100.00"), idDataGroup, false );
      }
   }

   bool bNonSharingDiscount = false;
   isNonSharingDiscount(bNonSharingDiscount, idDataGroup);

   if(bNonSharingDiscount)
   {
      calculateNonSharingSplitCommission(idDataGroup);
   }
   else
   {
      //propagate the total rate onto the splits
      BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

      while (!iter.end ())
      {
         SplitCommission *pSplitCommission = 
            dynamic_cast<SplitCommission *> (iter.getObject ());

         if (pSplitCommission)
         {
            if (SplitCommission::isTypeONE (getWorkSession()))
            {

               //based on the existing percentages recalculate the each rate
               DString rate,
                  commPrcnt,
                  commRate;

               getField (ifds::Rate, rate, idDataGroup, false);
               double dblRate = DSTCommonFunctions::convertToDouble (rate);
               double dblCommRate = 0.0, 
                  dblCommPrcnt = 0.0;

               pSplitCommission->getField (ifds::CommPrcnt, commPrcnt, idDataGroup);
               dblCommPrcnt = DSTCommonFunctions::convertToDouble (commPrcnt);
               dblCommRate = dblCommPrcnt * dblRate / 100;
               commRate = DSTCommonFunctions::doubleToDString (ifds::CommRate, dblCommRate);
               _bSkipCal = true;
               pSplitCommission->setField (ifds::CommRate, commRate, idDataGroup, true, true);
               _bSkipCal = false;
            }
            //in any case recalculate the amount
            pSplitCommission->calculateTheCommissionAmount (idDataGroup);
         }
         ++iter;
      }
   }


   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
SEVERITY SplitCommissionList::calculateNonSharingSplitCommission(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("calculateNonSharingSplitCommission"));

   SplitCommission* pBrokerSplitCommission = NULL;
   SplitCommission* pBranchSplitCommission = NULL;
   SplitCommission* pSlsRepSplitCommission = NULL;
   SplitCommission* pMgmtCoSplitCommission = NULL;

   DString dstrRate;
   getField(ifds::Rate, dstrRate, idDataGroup, false);
   BigDecimal bdRate(dstrRate);
   BigDecimal bdRateRemaining(bdRate);

   BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end ())
   {
      SplitCommission *pSplitCommission = dynamic_cast<SplitCommission *> (iter.getObject ());

      if (pSplitCommission)
      {
         DString dstrBrokerCode;
         DString dstrBranchCode;
         DString dstrSlsrepCode;

         pSplitCommission->getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
         pSplitCommission->getField(ifds::BranchCode, dstrBranchCode, idDataGroup, false);
         pSplitCommission->getField(ifds::SlsrepCode, dstrSlsrepCode, idDataGroup, false);

         if(dstrSlsrepCode != I_(""))
         {
            pSlsRepSplitCommission = pSplitCommission;
         }
         else if(dstrBranchCode != I_(""))
         {
            pBranchSplitCommission = pSplitCommission;
         }
         else if(dstrBrokerCode != I_(""))
         {
            pBrokerSplitCommission = pSplitCommission;
         }
         else
         {
            pMgmtCoSplitCommission = pSplitCommission;
         }

      }
      ++iter;
   }

   if(pMgmtCoSplitCommission)
   {
      calculateSharedDiscount(pMgmtCoSplitCommission, bdRate, bdRateRemaining, idDataGroup, pSlsRepSplitCommission || pBranchSplitCommission || pBrokerSplitCommission ? false : true );
   }

   if(pSlsRepSplitCommission)
   {
      calculateSharedDiscount(pSlsRepSplitCommission, bdRate, bdRateRemaining, idDataGroup, pBranchSplitCommission || pBrokerSplitCommission ? false : true );
   }
   
   if(pBranchSplitCommission)
   {
      calculateSharedDiscount(pBranchSplitCommission, bdRate, bdRateRemaining, idDataGroup, pBrokerSplitCommission ? false : true);
   }

   if(pBrokerSplitCommission)
   {
      calculateSharedDiscount(pBrokerSplitCommission, bdRate, bdRateRemaining, idDataGroup, true);
   }

   //if(pMgmtCoSplitCommission && bdRateRemaining > BIGDEC_ZERO)
   //{
   //   DString dstrCurrentCommAmount;
   //   pMgmtCoSplitCommission->getField(ifds::CommAmount, dstrCurrentCommAmount, idDataGroup, false);
   //   BigDecimal bdCurrentAmount(dstrCurrentCommAmount);
   //   BigDecimal bdCurrentRate = bdCurrentAmount / bdRate;

   //   if(bdCurrentAmount < bdRateRemaining)
   //   {  
   //      bdRateRemaining -= bdCurrentAmount;
   //   }  
   //   else if(bdRateRemaining >= BIGDEC_ZERO)
   //   {
   //      bdCurrentAmount = bdRateRemaining;
   //      bdRateRemaining = BIGDEC_ZERO;
   //      bdCurrentRate = bdCurrentAmount / bdRate;
   //   }
   //   
   //   pMgmtCoSplitCommission->setField(ifds::CommAmount, bdCurrentAmount.asDString(), idDataGroup, false);
   //   pMgmtCoSplitCommission->setField(ifds::CommRate, bdCurrentRate.asDString(), idDataGroup, false);
   //}

   return GETCURRENTHIGHESTSEVERITY ();
};

SEVERITY SplitCommissionList::calculateSharedDiscount(SplitCommission* pCurrentSplitCommission, 
                                                      const BigDecimal& bdRate, BigDecimal& bdRateRemaining, 
                                                      const BFDataGroupId& idDataGroup,
                                                      bool useRemainingCommission)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("calculateSharedDiscount"));

   DString dstrCurrentCommAmount;
   pCurrentSplitCommission->getField(ifds::CommAmount, dstrCurrentCommAmount, idDataGroup, false);
   DString dstrCurrentCommRate;
   pCurrentSplitCommission->getField(ifds::CommRate, dstrCurrentCommRate, idDataGroup, false);
   BigDecimal bdCurrentCommRate(dstrCurrentCommRate);
   BigDecimal bdCurrentAmount(dstrCurrentCommAmount);
//   BigDecimal bdCurrentRate = bdCurrentCommRate/ bdRate;

   if(useRemainingCommission)
   {
      bdCurrentCommRate = bdRateRemaining;
   }
   if(bdCurrentCommRate < bdRateRemaining)
   {  
      bdRateRemaining -= bdCurrentCommRate;
   }  
   else if(bdRateRemaining >= BIGDEC_ZERO)
   {
      bdCurrentCommRate = bdRateRemaining;
      bdRateRemaining = BIGDEC_ZERO;
      //bdCurrentRate = bdCurrentCommRate / bdRate;
   }
   
   pCurrentSplitCommission->setField(ifds::CommRate, bdCurrentCommRate.asDString(), idDataGroup, false);

   return GETCURRENTHIGHESTSEVERITY ();
}

SEVERITY SplitCommissionList::isNonSharingDiscount(bool& isNonSharingDiscount, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("isNonSharingDiscount"));
   
   isNonSharingDiscount = false;
   DString dstrAccountNum;
   DString dstrFundCode;
   DString dstrClassCode;
   DString dstrTransType;
   DString dstrBrokerCode;
   DString dstrEffectiveDate;
   DString dstrAmtType  = I_("D");
   DString dstrAmt      = I_("0");

   getField (ifds::Account,   dstrAccountNum,idDataGroup, false);
   getField (ifds::Fund,      dstrFundCode,  idDataGroup, false);
   getField (ifds::Class,     dstrClassCode, idDataGroup, false);
   getField (ifds::TransType, dstrTransType, idDataGroup, false);

   getField (ifds::BrokerCode, dstrBrokerCode,   idDataGroup, false);
   getField (ifds::EffectiveDate,  dstrEffectiveDate,   idDataGroup, false);
   
   
   
   DString dstrNonSharingDiscountApplicable;
   if( getNonSharingDiscountApplicable( dstrNonSharingDiscountApplicable,
			dstrTransType,
			dstrFundCode,
			dstrClassCode,
			dstrBrokerCode,
			dstrEffectiveDate,
			dstrAccountNum,
			dstrAmtType,
			dstrAmt,
			idDataGroup) <= WARNING)
     {
        dstrNonSharingDiscountApplicable.stripAll(); 
        if(dstrNonSharingDiscountApplicable != I_("0"))
            isNonSharingDiscount = true;
     }
   
   


   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY SplitCommissionList::doDeleteObject ( const DString &strKey, 
                                               const BFDataGroupId& idDataGroup, 
                                               bool bIsObjectDestroyed) 
{ 
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doDeleteObject"));
   //should recalculate the commission percentages
   //this requires special handling, since the iterator has not been set, yet as 'OBJ_ACTIVITY_DELETED'
   //for the object with the key 'strKey'

   //walk the list to recalculate the split commission rate total,
   //skip the previously deleted objects
   BFObjIter iter1 (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   double dblTotalRate = 0.0;

   while (!iter1.end ())
   {
      SplitCommission *pSplitCommission = 
         dynamic_cast<SplitCommission *> (iter1.getObject ());

      if (pSplitCommission && iter1.getStringKey () != strKey)
      {
         //get the comm amount
         double dblCommRate = 0.0;
         DString dstrCommRate;

         pSplitCommission->getField (ifds::CommRate, dstrCommRate, idDataGroup);
         dblCommRate = DSTCommonFunctions::convertToDouble (dstrCommRate);
         dblTotalRate += dblCommRate;
      }
      ++iter1;
   }
   //now, calculate the percentages
   BFObjIter iter2 (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter2.end ())
   {
      SplitCommission *pSplitCommission = 
         dynamic_cast<SplitCommission *> (iter2.getObject ());

      if (pSplitCommission && iter2.getStringKey () != strKey)
      {
         DString dstrCommRate, dstrCommPrcnt;
         double dblCommRate = 0.0, dblCommPrcnt = 0.0;

         pSplitCommission->getField (ifds::CommRate, dstrCommRate, idDataGroup);
         dblCommRate = DSTCommonFunctions::convertToDouble (dstrCommRate);
         dblCommPrcnt = dblTotalRate != 0 ? dblCommRate * 100 / dblTotalRate : 0.0;
         //use ifds::Amount for conversion because it has four decimals, for better precision
         dstrCommPrcnt = DSTCommonFunctions::doubleToDString (ifds::Amount, dblCommPrcnt);
         pSplitCommission->setField (ifds::CommPrcnt, dstrCommPrcnt, idDataGroup, true, true);
      }
      ++iter2;
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY SplitCommissionList::doCreateObject ( const BFData& data, 
                                               BFCBO*& pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doCreateObject"));

   SplitCommission * pSplitCommission = new SplitCommission (*this);

   pSplitCommission->init (data);
   pSplitCommission->setField (ifds::Default, I_ ("N"), BF::HOST, false);
   pObjOut = pSplitCommission;
//at least one repeat exists, by calling 151...
   _hasSplits = true;
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY SplitCommissionList::doCreateNewObject ( BFCBO*& pBase, 
                                                  DString& strKey, 
                                                  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doCreateNewObject"));

   SplitCommission* pSplitCommission = new SplitCommission (*this);   

   pSplitCommission->initNew (idDataGroup);
   pBase = pSplitCommission;
//at least one repeat exists, by adding a new record
   _hasSplits = true;
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY SplitCommissionList::validateTotalSplitAmount (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("validateTotalSplitAmount"));

	DString dstrTotalSplitAmount;
	DString dstrAmount;
	double  dTotalSplitAmount;
	double  dAmount;
	double  dExchRate;

    getTotal (ifds::CommRate, dstrTotalSplitAmount, idDataGroup);

	TradeFundAlloc *pTradeFundAlloc = dynamic_cast <TradeFundAlloc *> (getParent());

	if (pTradeFundAlloc)
	{
		BFCBO *pTopLevelCBO = pTradeFundAlloc->getTopLevelCBO();
      
		Trade *pTrade = dynamic_cast <Trade*> (pTopLevelCBO);

		if (pTrade)
		{    
			pTrade->calculateEstimatedAllocAmount (dstrAmount, idDataGroup);
			pTrade->getExchRate (dExchRate, idDataGroup);
		}

		dTotalSplitAmount = DSTCommonFunctions::convertToDouble (dstrTotalSplitAmount);
		dAmount = DSTCommonFunctions::convertToDouble (dstrAmount) * dExchRate;

		if ( dTotalSplitAmount > dAmount)
		{
			DString idiStr;

			DString dstrSplitAmount = DSTCommonFunctions::doubleToDString (ifds::CommRate, dTotalSplitAmount);
			DString dstrAmount = DSTCommonFunctions::doubleToDString (ifds::Amount, dAmount);
			addIDITagValue (idiStr, I_("AMOUNT"), dstrAmount);
			addIDITagValue (idiStr, I_("SPLITAMOUNT"), dstrSplitAmount);
        
			ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_SPLICCOMAMOUNT_IS_GREATER, idiStr);
		}
	}

    return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY SplitCommissionList::doValidateAll ( const BFDataGroupId &idDataGroup, 
                                              long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doValidateAll"));

   DString dstrFeeType;

   getField (ifds::FeeType, dstrFeeType, idDataGroup, false);
   
   if (dstrFeeType == FLAT)
   {
       validateTotalSplitAmount (idDataGroup);
	   return GETCURRENTHIGHESTSEVERITY ();
   }

   //get the split commsion default
   //for now do a view call, later this should be changed
   DString dstrSplitTotalRate (NULL_STRING);
   
   getSplitTotalRate (dstrSplitTotalRate, idDataGroup);
   BFObjIter iter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   
   if ( iter.getNumberOfItemsInList () > 0 && //only apply validations if the list does not have deleted objects
        SplitCommissionList::canFeeBeDiscounted (this,
		                                           getWorkSession(), 
                                                 DSTCommonFunctions::convertToDouble (dstrSplitTotalRate),
                                                 _initialTotalRate,
                                                 _maxRate,
                                                 idDataGroup) <= WARNING)
       
   {
      std::set< DString > dupSplitComm;

      // 1. iterate through the list
      DString dstr;
      while (!iter.end ())
      {
         // 1-1. Verify that all fund-class pairs are unique
         DString dstrCommEntType;
         iter.getObject ()->getField (ifds::CommEntType, dstrCommEntType, idDataGroup);
         dstrCommEntType.strip ().upperCase ();

         DString dstrBrokerCode;
         iter.getObject ()->getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup); 
         dstrBrokerCode.strip ().upperCase ();

         DString dstrBranchCode;
         iter.getObject ()->getField (ifds::BranchCode, dstrBranchCode, idDataGroup); 
         dstrBranchCode.strip ().upperCase ();

         DString dstrSlsrepCode;
         iter.getObject ()->getField (ifds::SlsrepCode, dstrSlsrepCode, idDataGroup); 
         dstrSlsrepCode.strip ().upperCase ();


         dstr = dstrCommEntType + dstrBrokerCode + dstrBranchCode + dstrSlsrepCode;
         if (!dupSplitComm.insert (dstr).second)
         {
            ADDCONDITIONFROMFILE (CND::ERR_IDENTICAL_SPLIT_COM);
            return (GETCURRENTHIGHESTSEVERITY ());
         }
         ++iter;
      }   
      if (_hasSplits)
      {
         double dblSplitTotalPercent = 0.0,
            dblSplitTotalAmount = 0.0;

         getSplitTotalPercent (dblSplitTotalPercent, idDataGroup);
         getSplitTotalAmount (dblSplitTotalAmount, idDataGroup);
         //if the Commission Type is 2, use the percentage to calculate splits.
         //total percentage must be exactly 100.0%
         if (SplitCommission::isTypeTWO (getWorkSession ()) == true)
         {
            if (fabs (dblSplitTotalAmount - 0.0) > .0000000001 && 
               fabs (dblSplitTotalPercent - 100.0) > .0000000001)
            {
               ADDCONDITIONFROMFILE (CND::ERR_PERCENTAGE_NOT_EQUAL_100);
            }
         } //else, don't care about percentage.
         
         //If need to check wheather total split amount is greater than 0 or not, uncomment this block
         /* 
         else
         {
            if (fabs (dblSplitTotalAmount - 0.0) < .0000000001)
            {
               ADDCONDITIONFROMFILE (CND::ERR_PERCENTAGE_NOT_EQUAL_100);
            }
         }
         */
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool SplitCommissionList::hasSplits()
{
   return _hasSplits;
}

//******************************************************************************
void SplitCommissionList::getRenunciationAmount ( double &dblRenunciationAmount, 
                                                  const BFDataGroupId& idDataGroup)
{
   DString dstrRenunciationAmount;

   getRenunciationAmount (dstrRenunciationAmount, idDataGroup);
   dblRenunciationAmount = DSTCommonFunctions::convertToDouble (dstrRenunciationAmount);
}

//******************************************************************************
void SplitCommissionList::getRenunciationAmount ( DString &dstrRenunciationAmount, 
                                                  const BFDataGroupId& idDataGroup)
{   
   double dblSplitTotalRate = 0.0;

   getSplitTotalRate (dblSplitTotalRate, idDataGroup);
   dstrRenunciationAmount = 
      DSTCommonFunctions::doubleToDString ( ifds::CommRate, 
                                            _maxRate - dblSplitTotalRate);

   //CurrencyClass::getFormattedValue (getWorkSession (), dstrRenunciationAmount);
   BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end ())
   {
      iter.getObject ()->setField (ifds::RenunAmount, dstrRenunciationAmount, idDataGroup);
      ++iter;
   }
}

//******************************************************************************
void SplitCommissionList::getSplitTotalAmount ( double &dblSplitTotalAmount, 
                                                const BFDataGroupId& idDataGroup)
{
   DString dstrSplitTotalAmount;
   
   getSplitTotalAmount (dstrSplitTotalAmount, idDataGroup);
   dblSplitTotalAmount = DSTCommonFunctions::convertToDouble (dstrSplitTotalAmount);
}

//******************************************************************************
void SplitCommissionList::getSplitTotalAmount ( DString &dstrSplitTotalAmount, 
                                                const BFDataGroupId& idDataGroup)
{
   getTotal (ifds::CommAmount, dstrSplitTotalAmount, idDataGroup);
   CurrencyClass::getFormattedValue (getWorkSession (), dstrSplitTotalAmount);
}

//******************************************************************************
void SplitCommissionList::getSplitTotalPercent ( double &dblSplitTotalPercent, 
                                                 const BFDataGroupId& idDataGroup)
{
   DString dstrSplitTotalPercent;
   
   getSplitTotalPercent (dstrSplitTotalPercent, idDataGroup);
   dblSplitTotalPercent = DSTCommonFunctions::convertToDouble (dstrSplitTotalPercent);
}

//******************************************************************************
void SplitCommissionList::getSplitTotalPercent (DString &dstrSplitTotalPercent, 
                                                const BFDataGroupId& idDataGroup)
{
   getTotal (ifds::CommPrcnt, dstrSplitTotalPercent, idDataGroup);
}

//******************************************************************************
void SplitCommissionList::getSplitTotalRate ( double &dblSplitTotalRate, 
                                              const BFDataGroupId& idDataGroup)
{
   DString dstrSplitTotalRate;
   
   getSplitTotalRate (dstrSplitTotalRate, idDataGroup);
   dblSplitTotalRate = DSTCommonFunctions::convertToDouble (dstrSplitTotalRate);
}

//******************************************************************************
void SplitCommissionList::getSplitTotalRate ( DString &dstrSplitTotalRate, 
                                              const BFDataGroupId& idDataGroup)
{
   getTotal (ifds::CommRate, dstrSplitTotalRate, idDataGroup);
}

//******************************************************************************
void SplitCommissionList::getInitialTotalRate ( DString &dstrInitialTotalRate, 
                                                const BFDataGroupId& idDataGroup)
{
   dstrInitialTotalRate = DSTCommonFunctions::doubleToDString (ifds::Rate, _initialTotalRate);
}

//helper method to calculate totals for various fields
//******************************************************************************
void SplitCommissionList::getTotal (const BFFieldId& idField, 
                                    DString &dstrTotal, 
                                    const BFDataGroupId& idDataGroup)
{
   BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   DString dstr;
   double dtotal = 0.0;

   while (!iter.end ())
   {
      iter.getObject ()->getField (idField, dstr, idDataGroup);
      dtotal += DSTCommonFunctions::convertToDouble (dstr);
      ++iter;
   }
   dstrTotal = DSTCommonFunctions::doubleToDString (idField, dtotal);
}

//******************************************************************************
void SplitCommissionList::deleteSplitCommList (const BFDataGroupId& idDataGroup)
{
   BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   while (!iter.end ())
   {
      iter.deleteObject ();
   }
}
//******************************************************************************
bool SplitCommissionList::hasCBOObject ()
{
   BFObjIter iter (*this, BF::HOST, 0, BFObjIter::ITERTYPE::NON_DELETED);
   return (!iter.end ()); 
}

//******************************************************************************
void SplitCommissionList::calculateFieldsBasedOnCommissionType (const BFDataGroupId &idDataGroup)
{
   BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   DString strRate;
   double dblRate = 0.0;

   if (SplitCommission::isTypeTWO (getWorkSession ()))
   {
      getField (ifds::Rate, strRate, idDataGroup, false);
   }
   else if (SplitCommission::isTypeONE (getWorkSession()))
   {
      getSplitTotalRate (strRate, idDataGroup);
   }
   dblRate = DSTCommonFunctions::convertToDouble (strRate);
   
   double dblCumulRate = 0;

   while (!iter.end ())
   {
      SplitCommission *pSplitCommission = 
         dynamic_cast<SplitCommission *> (iter.getObject ());

      if (pSplitCommission)
      {
         if (SplitCommission::isTypeTWO (getWorkSession ()))
         {
            //for commission type two we have the percentage, 
            //and we need to calculate the rate
            DString dstrCommRate, dstrCommPrcnt;
            double dblCommRate = 0.0, dblCommPrcnt = 0.0;

            pSplitCommission->getField (ifds::CommPrcnt, dstrCommPrcnt, idDataGroup);
            dblCommPrcnt = DSTCommonFunctions::convertToDouble (dstrCommPrcnt); 
            dblCommRate = dblCommPrcnt * dblRate / 100;

            dstrCommRate = DSTCommonFunctions::doubleToDString (ifds::CommRate, dblCommRate);
            double dblRoundedCommRate  = DSTCommonFunctions::convertToDouble (dstrCommRate);
            if(dblRoundedCommRate + dblCumulRate > dblRate)
            {
               dblCommRate = dblRate - dblCumulRate;
               dstrCommRate = DSTCommonFunctions::doubleToDString (ifds::CommRate, dblCommRate);
               dblRoundedCommRate  = DSTCommonFunctions::convertToDouble (dstrCommRate);
            }
            pSplitCommission->setField (ifds::CommRate, dstrCommRate, idDataGroup, true, true);
            dblCumulRate += dblRoundedCommRate;
         }
         else if (SplitCommission::isTypeONE (getWorkSession()) && !_bSkipCal)
         {
            //for commission type one we have the rate and the amount,
            //and we need to calculate the percentage 
            DString dstrCommRate, dstrCommPrcnt;
            double dblCommRate = 0.0, dblCommPrcnt = 0.0;

            pSplitCommission->getField (ifds::CommRate, dstrCommRate, idDataGroup);
            dblCommRate = DSTCommonFunctions::convertToDouble (dstrCommRate);
            dblCommPrcnt = dblRate != 0 ? dblCommRate * 100 / dblRate : 0.0;
            //use ifds::Amount for conversion because it has four decimals, for better precision
            dstrCommPrcnt = DSTCommonFunctions::doubleToDString (ifds::Amount, dblCommPrcnt);
            pSplitCommission->setFieldNoValidate (ifds::CommPrcnt, dstrCommPrcnt, idDataGroup, true, true);
         }
      }
      ++iter;
   }
}

//******************************************************************************
bool SplitCommissionList::shouldSkipCalculatingRatesAmounts (const BFDataGroupId& idDataGroup)
{
   bool bSkip = false;

   TradeFundAlloc *pTradeFundAlloc = dynamic_cast <TradeFundAlloc *> (getParent());

   if (pTradeFundAlloc)
   {
      BFCBO *pTopLevelCBO = pTradeFundAlloc->getTopLevelCBO();

      bSkip = !!dynamic_cast <TransactionDetails*> (pTopLevelCBO);
   }    
   return bSkip;
}


//**********************************************************************************
bool SplitCommissionList::isROAApplicable (const BFDataGroupId &idDataGroup) 
{
   bool bRet = false;
   TradeFundAlloc *pTradeFundAlloc = dynamic_cast <TradeFundAlloc *> (getParent());

   if (pTradeFundAlloc)
   {
      BFCBO *pTopLevelCBO = pTradeFundAlloc->getTopLevelCBO();
      Trade *pTrade = dynamic_cast <Trade*> (pTopLevelCBO);

      if (pTrade && pTrade->isROAApplicable (idDataGroup))
      {
         DString roaAmount;
         
         pTrade->getField (ifds::ROAAmount, roaAmount, idDataGroup);
         double dAmt = DSTCommonFunctions::convertToDouble (roaAmount);
         bRet = dAmt > 0;
      }
   }   
   return bRet;
}

//*******************************************************************************
void SplitCommissionList::changeFieldsForRebook()
{
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      SplitCommission* pSplitCommission = dynamic_cast<SplitCommission*>( iter.getObject() );
      pSplitCommission->changeFieldsForRebook();   
      ++iter;
   }
}

///*******************************************************************************
//Input:SplitCommissionList &SplitCommissionList,DSTCWorkSession &rpDSTCWorkSession,.
//OutPut:None
//Return:bool
//Functionality:This function checks limitation on TaxTypeLevel,
//              if the Fees can overide the MAX_FEE
//*******************************************************************************/
bool SplitCommissionList::bIsTaxLevelOverride4MaxFeeNotAllowed(SplitCommissionList *pSplitCommissionList,
															   DSTCWorkSession &rpDSTCWorkSession,
															   const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("bIsTaxLevelOverride4MaxFeeAllowed"));
	DString dstrAccountNum;
	MFAccount *pMFAccount = NULL;
	bool bOverideNotAllowed = false;
	pSplitCommissionList->getField (ifds::Account, dstrAccountNum, idDataGroup, false);
	if (rpDSTCWorkSession.getMFAccount ( idDataGroup, 
                                        dstrAccountNum, 
                                       pMFAccount) <= WARNING && 
									   pMFAccount)
									   //&& pMFAccount->bIsTaxTypeRelatedtoRegAgent(idDataGroup))
	{
		DString dstrAccTaxType;
		pMFAccount->getField(ifds::TaxType, dstrAccTaxType, idDataGroup, false );	
        TaxTypeRuleList *ptaxTypeRuleList=NULL;
		if( rpDSTCWorkSession.getMgmtCo().getTaxTypeRuleList( ptaxTypeRuleList )<=WARNING && ptaxTypeRuleList )
		{
		 //create iterator on ptaxTypeRuleList and find the tax type of the account allows Taxlevel override			
         BFObjIter iterList(*ptaxTypeRuleList, BF::HOST, false );
		 //ptaxTypeRuleList->getStrKey( strTaxType);
		 while( !iterList.end() )
		 {
			 DString dstrTaxType;
			 TaxTypeRule *pTaxTypeRule = dynamic_cast<TaxTypeRule*>(iterList.getObject());
			 pTaxTypeRule->getField( ifds::TaxType, dstrTaxType, BF::HOST );
			 if(dstrTaxType == dstrAccTaxType)
			 {   
				 DString dstrMaxFeeAppl;
				 pTaxTypeRule->getField(ifds::MaxFeeAppl,dstrMaxFeeAppl,BF::HOST);
				 if( I_("Y") == dstrMaxFeeAppl )
					 bOverideNotAllowed =true;
				 break;
			 }
		   ++iterList;
       }
		}
	}
   		return bOverideNotAllowed;
}


//******************************************************************************shashi
SEVERITY SplitCommissionList::getNonSharingDiscountApplicable(DString& dstrNonSharingDiscountApplicable,
												DString dstrTransType,
												DString dstrFundCode,
												DString dstrClassCode,
												DString dstrBrokerCode,
												DString dstrEffectiveDate,
												DString dstrAccountNum,
												DString dstrAmountType,
												DString dstrAmount,
												const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAcqFeeMax"));

   DString dstrTaxType; 
   DString dstrFundCurrency;

   MFAccount *pMFAccount=NULL;
   if (getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
									   pMFAccount)
   {
		pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
   }
   
   CurrencyClass::getFundCurrency( getWorkSession(), dstrFundCode, dstrClassCode, dstrFundCurrency);

   dstrFundCurrency.strip().upperCase();
   dstrTaxType.strip().upperCase();
   
   DString dtrTransType    = I_("ED");
//   DString dstrAmountType  = I_("D");
   dstrAmount      = I_("0"); 
   DString dstrExchRate    = I_("1");
   DString dstrBranchCode  = I_("");
   DString dstrSalesRepCode = I_("");
   DString dstrAMSCode     = I_("");
   DString dstrAMSType     = I_("");
   DString dstrDepositType = I_("");
   DString dstrOrderType   = I_("");

   TradeMinAmtCheck tradeMinAmtCheck(*this);
   SEVERITY sevRtn = tradeMinAmtCheck.init(dstrAccountNum, 
                                 dstrFundCode, 
                                 dstrClassCode, 
                                 dstrTransType, 
                                 dstrAmountType, 
                                 dstrAmount, 
                                 dstrEffectiveDate, 
                                 dstrFundCurrency, 
                                 dstrExchRate,
                                 dstrBrokerCode, 
                                 dstrBranchCode,
								         dstrSalesRepCode,
                                 dstrAMSCode, 
                                 dstrAMSType,
                                 dstrDepositType,
								         dstrOrderType);
      
      
     if( sevRtn <= WARNING )
          tradeMinAmtCheck.getField(ifds::BrkOverideAmt, dstrNonSharingDiscountApplicable, idDataGroup, false);

   return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************************
DString SplitCommissionList::getTaxTypeMaxFee(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, 
		I_("getTaxTypeMaxFee"));
	
	DString dstrAccountNum,
		    dstrMaxFee = NULL_STRING;
	getField (ifds::Account, dstrAccountNum, idDataGroup, false);
	
	MFAccount *pMFAccount=NULL;
    if (getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
									   pMFAccount)
    {
		DString dstrAccTaxType;
		pMFAccount->getField(ifds::TaxType, dstrAccTaxType, idDataGroup, false );	
    
		TaxTypeRuleList *ptaxTypeRuleList=NULL;
		if( getWorkSession().getMgmtCo().getTaxTypeRuleList( ptaxTypeRuleList )<=WARNING && ptaxTypeRuleList )
		{
			BFObjIter iterList(*ptaxTypeRuleList, BF::HOST, false );
			while( !iterList.end() )
		    {
				DString dstrTaxType;
				TaxTypeRule *pTaxTypeRule = dynamic_cast<TaxTypeRule*>(iterList.getObject());
				pTaxTypeRule->getField( ifds::TaxType, dstrTaxType, idDataGroup );
				if(dstrTaxType == dstrAccTaxType)
				{  
					DString dstrMaxFeeAppl;
				    pTaxTypeRule->getField(ifds::MaxFeeAppl,dstrMaxFeeAppl,idDataGroup);
				    if( I_("Y") == dstrMaxFeeAppl )
					{
						pTaxTypeRule->getField(ifds::MaxFee,dstrMaxFee,idDataGroup);
						break;
					}
				}
				++iterList;
		    }
		}
	}
   	return dstrMaxFee;
}
//******************************************************************************
SEVERITY SplitCommissionList::propagateTotalRate(DString &dstrTotalRate, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("propagateTotalRate"));
	
	setFieldNoValidate (ifds::Rate, dstrTotalRate, idDataGroup,true,true,false,false);
	
	BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

	while (!iter.end ())
	{
		//propagate the total rate onto the splits
		SplitCommission *pSplitCommission = 
			dynamic_cast<SplitCommission *> (iter.getObject ());

		if (pSplitCommission)
		{
			if (SplitCommission::isTypeONE (getWorkSession()))
			{
				//based on the existing percentages recalculate the each rate
				DString rate,
					commPrcnt,
					commRate;

				getField (ifds::Rate, rate, idDataGroup, false);
				double dblRate = DSTCommonFunctions::convertToDouble (rate);
				double dblCommRate = 0.0, 
					dblCommPrcnt = 0.0;

				pSplitCommission->getField (ifds::CommPrcnt, commPrcnt, idDataGroup);
				dblCommPrcnt = DSTCommonFunctions::convertToDouble (commPrcnt);
				dblCommRate = dblCommPrcnt * dblRate / 100;
				commRate = DSTCommonFunctions::doubleToDString (ifds::CommRate, dblCommRate);
				_bSkipCal = true;
				pSplitCommission->setField (ifds::CommRate, commRate, idDataGroup, true, true);
				_bSkipCal = false;
			}
			//in any case recalculate the amount
			pSplitCommission->calculateTheCommissionAmount (idDataGroup);
		}
		++iter;
	}
	return(GETCURRENTHIGHESTSEVERITY());
}
//********************************************************************************
SEVERITY SplitCommissionList::changeToRDRAdviceProvided( const BFDataGroupId& idDataGroup /*=BF::HOST*/)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("commonInit"));
    SEVERITY severity = NO_CONDITION;

	DString dstrRate;
	getSplitTotalRate (dstrRate, idDataGroup);   
	
	BFObjIter bfIter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

	bfIter.begin();
	while (!bfIter.end())
	{            
		bfIter.deleteObject ();
	}
	
	addRDRAdviceProvidedCommission( dstrRate, idDataGroup /*=BF::HOST*/);
	
	return GETCURRENTHIGHESTSEVERITY ();
}
//**************************************************************************************************
SEVERITY SplitCommissionList::addRDRAdviceProvidedCommission( const DString& dstrRate, const BFDataGroupId& idDataGroup /*=BF::HOST*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("addRDRAdviceProvidedCommission"));
   SEVERITY severity = NO_CONDITION;

	BFObjectKey objKey (NULL_STRING, idDataGroup);

	BFCBO * pBFCBO = getNewListItem (objKey);

	pBFCBO->setField (ifds::CommPrcnt, I_("100"), idDataGroup, false);
	pBFCBO->setField (ifds::CommRate, dstrRate, idDataGroup, false);
	pBFCBO->setField (ifds::CommEntType, I_("CNTX"), idDataGroup, false);

	DString dstrRDRAdvice;
	getField(ifds::RDRAdvice,dstrRDRAdvice,idDataGroup);

	pBFCBO->setFieldReadOnly(ifds::CommEntType,idDataGroup,dstrRDRAdvice == RDR_ADVICE_PROVIDED);
	pBFCBO->setFieldReadOnly(ifds::CommRate,idDataGroup,dstrRDRAdvice == RDR_ADVICE_PROVIDED);

	return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SplitCommissionList.cpp-arc  $
// 
//    Rev 1.102   Jul 31 2012 16:46:32   wp040027
// Sync up: IN# 3006862-CPF-Enable Fee in PAC/Corrected default Fee in PAC and Trade screen/Max Fee Validation
// 
//    Rev 1.101   Jul 30 2012 09:06:16   wp040027
// P0198518 - RDR Functionality - Review Comment incorporated
// 
//    Rev 1.100   Jul 26 2012 10:39:24   wp040027
// P0198518 - RDR Functionality
// 
//    Rev 1.99   Jul 03 2012 21:34:54   popescu
// incident 2827213 - comm reduction fix..
// 
//    Rev 1.98   Jun 08 2012 12:19:02   wp040027
// IN 2956475 - Split Commission environment max fee not working
// 
//    Rev 1.97   Jun 04 2012 09:29:08   if991250
// CPF: PAC
// 
//    Rev 1.96   May 18 2012 14:03:18   if991250
// CPF: P0187485_FN01_Discount Non-Sharing Enhancement
// 
//    Rev 1.95   May 18 2012 13:39:26   if991250
// CPF: P0187485_FN01_Discount Non-Sharing Enhancement
// 
//    Rev 1.94   Apr 24 2012 21:16:32   wp040039
// PETP0187485 - Trade Entry And Processing
// 
//    Rev 1.93   Feb 09 2012 19:34:14   popescu
// 2821238 - Base Commission should be calculated on Overriding the default Acquisition Fee
// 
//    Rev 1.92   Jan 30 2012 18:34:22   popescu
// incident 2827213 - comm reduction fix..
// 
//    Rev 1.91   Jan 27 2012 15:56:50   popescu
// Incident 2821238 - corrected the comm reduction calculation
// 
//    Rev 1.90   Dec 16 2011 11:19:02   popescu
// INA Commission Work
// 
//    Rev 1.89   Dec 13 2011 08:53:30   popescu
// P0186477/FN03 - INA Commission Work
// 
//    Rev 1.88   Dec 01 2011 16:35:52   popescu
// INA Commission Work
// 
//    Rev 1.87   Nov 28 2011 23:07:56   popescu
// INA Commission Work
// 
//    Rev 1.86   Nov 27 2011 19:42:42   popescu
// INA Commission Work
// 
//    Rev 1.85   Nov 23 2011 09:23:46   popescu
// INA Base Commission
// 
//    Rev 1.84   Apr 15 2011 14:36:00   jankovii
// IN 2495248 - Split Commission Issues on DSK
// 
//    Rev 1.83   Mar 25 2011 14:49:04   jankovii
// IN 2475801 - Invalid split commission calculation
// 
//    Rev 1.82   Mar 04 2011 12:16:04   jankovii
// PET181943 FN01 - XMLPhase 2
// 
//    Rev 1.81   02 Jan 2009 14:43:34   kovacsro
// IN#1384231- OUTSTANDING COMMISSION - MFS Sicav (set the split rate whenever the fee rate is set by the user - this was failing because CommPrcnt was zero for a brand new SplitCommission object)
// 
//    Rev 1.80   Jan 29 2008 13:17:26   daechach
// IN#1134569 - Cancel of Transfer out Trade not Allowed.
// 
//    Rev 1.79   Nov 02 2007 14:47:44   smithdav
// Only do 100% edit for type 2 entry mode.
// 
//    Rev 1.78   Jul 11 2005 17:24:22   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.77   Jul 08 2005 09:31:56   Yingbaol
// PET1235,FN01:transaction cancellation rebook
// 
//    Rev 1.76   Jul 07 2005 17:52:24   popescu
// Incident# 350901 - removed split commissions when not needed, do not call split commissions when trade is roa applicable, trans type is transfer and side of the splits is To
// 
//    Rev 1.75   Jul 04 2005 19:04:52   popescu
// Incident # 347073 - split commission is charged on the To side for environments where ROA is applicable.
// 
//    Rev 1.74   Jun 30 2005 12:39:14   popescu
// Incident # 338532 - fixed nbr of decimals on the split commission screen for amounts and percentages  - amount fields are formatted to 2 decimals, percentages to 4
// 
//    Rev 1.73   Jun 15 2005 18:41:26   popescu
// Incident # 333141- correctly displayed the split commission amount value for processed transactions
// 
//    Rev 1.72   May 18 2005 09:03:34   yingbaol
// PET1203,FN01 Commission-Class A enhancement
// 
//    Rev 1.71   Mar 30 2005 14:37:38   popescu
// Incident# 275373, added an extra parameter to view 151 (TransId), split commission trans history/pending trades inquiry
// 
//    Rev 1.70   Feb 22 2005 14:04:52   popescu
// Incident #249310, validation of split commissions should be done against the initial total value, rather then 0 amount
// 
//    Rev 1.69   Feb 21 2005 14:46:46   popescu
// Incident #244407, fixed the split commission getotalrate method. It should always calculate the rate, based on the 'CommRate' field. Should not care if there are splits or not.
// 
//    Rev 1.68   Feb 17 2005 17:05:08   aguilaam
// incident # 239846 - pass and display RenunAmount (checked in for Serban)
// 
//    Rev 1.67   Jan 20 2005 19:54:32   popescu
// PET 1117/06, fixed split comm calc issue for comm environment type 1
// 
//    Rev 1.66   Jan 19 2005 14:20:58   popescu
// PTS 10038083, enabled acquisition fee for split comm type 2 (manulife env.) and calculate the splits if total rate changes
// 
//    Rev 1.65   Dec 02 2004 18:23:02   popescu
// PET 1117/06/56, trades processing/fees processing
// 
//    Rev 1.64   Nov 18 2004 13:28:26   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.63   Nov 17 2004 16:15:30   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.62   Nov 14 2004 14:56:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.61   Mar 17 2004 10:54:32   popescu
// PTS 10028239, do not raise the 100% percent allocation error if the total split rate is zero, and use 4 decimals precision to calculate the comm percentages
// 
//    Rev 1.60   Jan 29 2004 09:43:02   popescu
// PST 10026625, for pending trades display the split commission rates comming from back-end (view 151) instead of re-calculating them based on the default total split rate
// 
//    Rev 1.59   Jan 22 2004 18:35:36   popescu
// PTS 10026412, SplitCommission percentage validation should not be executed if the list is empty, without splits
// 
//    Rev 1.58   Jan 21 2004 18:12:04   popescu
// PTS 10026237,
// For allocated purchases the acquisition fee should be zero and split commissions default values are displayed as they are returned by view 158.
// Also, if no repeated record is returned by 158 set the IFee to the Fee field value of the fixed section of view 158 and follow the same validation rules, as if split commissions would exist.
// 
//    Rev 1.57   Dec 16 2003 12:42:28   popescu
// PTS 10024124
// 
//    Rev 1.56   Dec 15 2003 16:37:40   AGUILAAM
// PTS 10024124
// 
//    Rev 1.55   Dec 15 2003 11:55:02   popescu
// PTS 10023645, disable split commission button if 158 returns data not found, for various reasons
// 
//    Rev 1.54   Dec 12 2003 13:25:32   AGUILAAM
// PTS 10024124, split comm, re-work
// 
//    Rev 1.53   Dec 10 2003 12:19:24   popescu
// PTS 10024124, spcomm re-work
// 
//    Rev 1.52   Dec 08 2003 15:28:24   popescu
// PTS 10023645, split commission re-work
// 
//    Rev 1.51   Oct 22 2003 09:47:10   popescu
// PTS 10022763, the comm amount failed to be calculated when discounting the fee at the trade level
// 
//    Rev 1.50   Sep 10 2003 17:45:16   popescu
// Put a quick hack in for commission type 2, that will set the percentage to 100 in case it comes 0 from the view side and the total rate of the split is not zero. The assumption made is that there is only one element in the split commission list.
// 
//    Rev 1.49   Aug 20 2003 15:17:24   popescu
// PTS 10020298
// 
//    Rev 1.48   Aug 20 2003 13:24:48   popescu
// PTS 10018618 fix; the code provided will not however, remain, it should be changed by getting the right fee code from the back-end
// 
//    Rev 1.47   Aug 20 2003 12:14:40   popescu
// PTS 10018366, fixed percentage calculation for commission type one, and split comm list removed if fund change
// 
//    Rev 1.46   Aug 20 2003 11:27:18   popescu
// PTS 10018403
// The split commission percentage calculation was using a wrong total rate it should be using the initial total rate of the split
// 
//    Rev 1.45   Aug 19 2003 09:02:06   popescu
// PTS 10020327
// Added a new field, Rate, used to update the total value of the split rate 
// 
//    Rev 1.44   May 30 2003 19:19:54   popescu
// PTS 10017741
// 
//    Rev 1.43   May 13 2003 19:36:40   popescu
// PTS 10016228 & 10016241
// 
//    Rev 1.42   May 13 2003 17:07:10   popescu
// Split commission re-work, part II
// 
//    Rev 1.41   May 13 2003 10:06:12   popescu
// Split commission re-work
// 
//    Rev 1.40   May 07 2003 11:02:20   popescu
// fixed PTS 10016875
// 
//    Rev 1.39   May 05 2003 17:13:40   HERNANDO
// PTS 10016753 - Do not display Error for FromClass on the Trade Dialog as per Yingbao's suggestion.
// 
//    Rev 1.38   Apr 29 2003 17:05:48   popescu
// PTS 10016204
// 
//    Rev 1.37   Apr 25 2003 16:33:16   popescu
// PTS Work:10016245,
// 
//    Rev 1.36   Apr 21 2003 09:30:02   popescu
// PTS 10016188, correctly calculate the split total in doValidateAll
// 
//    Rev 1.35   Apr 14 2003 16:27:32   popescu
// PTS 10011081- split commision amount is being calculated by the view side
// 
//    Rev 1.34   Apr 05 2003 16:11:02   popescu
// Moved setting the Fee field inTrade & Systematic into the SplitCommisionProcess
// 
//    Rev 1.33   Apr 04 2003 15:59:04   popescu
// split commsion work for Systematic
// 
//    Rev 1.32   Apr 04 2003 10:18:44   popescu
// split commsion work
// 
//    Rev 1.31   Mar 21 2003 18:25:10   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.30   Dec 17 2002 14:06:30   YINGBAOL
// promot "Data not found"
// 
//    Rev 1.29   Oct 09 2002 23:55:02   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.28   Aug 29 2002 12:56:42   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.27   Jun 03 2002 11:09:24   HSUCHIN
// sync up with 1.24.1.1
// 
//    Rev 1.26   22 May 2002 18:29:54   PURDYECH
// BFData Implementation
// 
//    Rev 1.25   29 Apr 2002 16:31:52   KOVACSRO
// new trade allocations.
// 
//    Rev 1.24   16 Nov 2001 16:34:06   HSUCHIN
// added missing logic for default split for commission type 2
// 
//    Rev 1.23   07 Nov 2001 15:43:52   HSUCHIN
// code cleanup and added support for commission type 2.  New functions setSplitRateTotal, reCalculateCommRate/CommPrcnt and getFELFee.
// 
//    Rev 1.22   14 Oct 2001 15:23:06   HSUCHIN
// renunciation check re-enable for all commission types
// 
//    Rev 1.21   26 Sep 2001 11:46:46   HSUCHIN
// diable renunciation check if split commission level is 1
// 
//    Rev 1.20   13 Sep 2001 17:52:26   HSUCHIN
// added logic to set the CommPrcnt fields for some cases where the view returing does not have them set.
// 
//    Rev 1.19   18 Jul 2001 16:06:00   HSUCHIN
// bug fix for default split commission
// 
//    Rev 1.18   09 May 2001 10:27:36   HSUCHIN
// Session management restructuring
// 
//    Rev 1.17   08 May 2001 14:07:02   HSUCHIN
// use the correct condition for validation
// 
//    Rev 1.16   May 07 2001 16:04:40   WINNIE
// fix compile error
// 
//    Rev 1.15   07 May 2001 14:03:58   HSUCHIN
// added duplicate check to validateall
// 
//    Rev 1.14   May 07 2001 13:52:34   YINGBAOL
// add hasCBOObject method
// 
//    Rev 1.13   02 May 2001 13:01:48   HSUCHIN
// removed donotifyresponse
// 
//    Rev 1.12   May 02 2001 10:13:44   YINGBAOL
// use sync receive data instead of  Asyncreceivedata
// 
//    Rev 1.11   27 Apr 2001 13:37:06   HSUCHIN
// added function deleteSplitCommList
// 
//    Rev 1.10   16 Apr 2001 14:50:52   HSUCHIN
// Changed validate condition message
// 
//    Rev 1.9   14 Apr 2001 10:35:16   HSUCHIN
// changed init for Default SplitCommission to not use Async.   added function reCalculateCommAmount 
// 
//    Rev 1.8   01 Apr 2001 12:57:46   HSUCHIN
// check in for winnie
// 
//    Rev 1.7   01 Apr 2001 09:49:58   HSUCHIN
// added Default Split Commission init
// 
//    Rev 1.6   Mar 23 2001 15:58:06   HERNANDO
// Initialize 'total' to prevent strange Renunciation total amounts.
// 
//    Rev 1.5   Mar 19 2001 15:03:52   HSUCHIN
// additional processing and validation
// 
//    Rev 1.4   Mar 18 2001 11:52:06   HSUCHIN
// additioanl features and support
// 
//    Rev 1.3   Mar 13 2001 09:21:18   HSUCHIN
// checked in for Zijian
// 
//    Rev 1.2   Mar 08 2001 15:32:50   YINGZ
// make it work
// 
//    Rev 1.1   Feb 27 2001 15:49:22   YINGZ
// for robert
 * 
 */

