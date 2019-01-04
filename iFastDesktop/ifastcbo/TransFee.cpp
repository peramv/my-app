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
// ^FILE   : TransFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : July 2004
//
// ^CLASS    : TransFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "transfee.hpp"

#include "feeparamconfiglist.hpp"
#include "feesetuptraderuleslist.hpp"
#include "fundfeelist.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "mfaccount.hpp"
#include "shareholder.hpp"
#include "mgmtco.hpp"
#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("TransFee");
   const I_CHAR *  PURCHASE   = I_("ED");
}

namespace CND
{  // Conditions used
   extern long const ERR_FEE_TYPE_SCALE_NOT_SUPPORTED;
   extern long const ERR_FEE_TYPE_TIER_NOT_SUPPORTED;
   extern long const ERR_FEE_CANNOT_BE_OVERRIDDEN;
   extern CLASS_IMPORT const long ERR_FEE_PARAMS_NOT_AVAILABLE;
}

namespace ifds
{
//context fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
//fee fields
   extern CLASS_IMPORT const BFIntegerFieldId TransFeeCode;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
//fee param config list fields
   extern CLASS_IMPORT const BFTextFieldId Status;
   extern CLASS_IMPORT const BFTextFieldId ChargeOptionList;
   extern CLASS_IMPORT const BFTextFieldId TradeFeeTypeList;
   extern CLASS_IMPORT const BFTextFieldId FeeTypeList;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
//account fields
   extern CLASS_IMPORT const BFTextFieldId FeeWaived;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
//fund group
   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId DisableFee4Alloc;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const ONE_SIDE_TRADE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
    //  Field DD Id,      State Flags,      Group Flags 
   { ifds::RecordType,       BFCBO::NONE,      0}, 
   { ifds::TransFeeCode,     BFCBO::NONE,      0}, 
   { ifds::FeeType,          BFCBO::NONE,      0}, 
   { ifds::OrigFeeType,      BFCBO::NONE,      0}, 
   { ifds::Currency,         BFCBO::NONE,      0}, 
   { ifds::ChargeOption,     BFCBO::NONE,      0}, 
   { ifds::TradeFeeOption,   BFCBO::NONE,      0}, 
   { ifds::FeeRate,          BFCBO::NONE,      0}, 
   { ifds::OrigFeeRate,      BFCBO::NONE,      0}, 
   { ifds::TransFeeRID,      BFCBO::NONE,      0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

namespace FEES
{
   extern const I_CHAR * AGGREGATED_EXTERNAL_CHARGE;
   extern const I_CHAR * AGGREGATED_COMMISSION;
   extern const I_CHAR * MISC_COMMISSION;
   extern const I_CHAR * DISCOUNT_RATE;
}


//******************************************************************************
TransFee::TransFee (BFAbstractCBO &parent, const DString &feeCode) : MFCanBFCbo (parent),
_feeCode (feeCode),
_oldContext (NULL),
_context (NULL),
_bDelayInit (false)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   registerMemberData ( NUM_FIELDS,(const CLASS_FIELD_INFO *)&classFieldInfo,
                        0,NULL);
   _context = new TransFeeContext (*this);
}

//******************************************************************************
TransFee::~TransFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
   if (_oldContext)
   {
      delete _oldContext;
      _oldContext = NULL;
   }
   if (_context)
   {
      delete _context;
      _context = NULL;
   }
}

//******************************************************************************
SEVERITY TransFee::init (const BFDataGroupId &idDataGroup, bool bDelayInit /*= false*/ )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   _bDelayInit = bDelayInit;
   setFieldNoValidate (ifds::TransFeeCode, _feeCode, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFee::reInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("reInit"));
   _bDelayInit = false; //no delay this time
   initWithDefaultValues (idDataGroup);
   DString feeCode = get_FeeCode();
   if(I_("112") == feeCode || I_("113") == feeCode || I_("122") == feeCode || I_("123") == feeCode || I_("127") == feeCode)
      setFieldNoValidate(ifds::TransFeeCode, feeCode, BF::HOST, false, true,false, false);
   *_oldContext = *_context;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFee::init (const BFData &viewData)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&>(viewData), false, true);
   _feeCode = viewData.getElementValue (ifds::TransFeeCode);
   _feeCode.strip();
//this is a fee!!!
   setFieldNoValidate (ifds::RecordType, I_("Fee"), BF::HOST, false);
   getFeeParamConfigDefaults (BF::HOST);
   setFieldReadOnly (ifds::TransFeeCode, BF::HOST, true);
   setFieldReadOnly (ifds::Currency, BF::HOST, true);
   setFeeProperties (BF::HOST);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFee::restore ( BFCBO &rpParent, 
                             const BFDataGroupId &idDataGroup)
{
//default implementation
   return NO_CONDITION;
}

//******************************************************************************
void TransFee::setContext (const TransFeeContext &context)
{
//save the current context
   bool bSave = !_oldContext;
   if (!_oldContext)
   {
      _oldContext = new TransFeeContext (*this);
   }
   else
   {
      bSave = !(*_context == context); //only if there is a change
   }
   if (bSave)
   {
      *_oldContext = *_context;
//store the new one
      *_context = context;
   }
}

//******************************************************************************
inline TransFeeContext &TransFee::getContext()
{
   return *_context;
}

//******************************************************************************
inline bool TransFee::canBeInitialized (const BFDataGroupId &idDataGroup)
{
   return isSystemApplicable (idDataGroup) &&  //only if fee is system applicable
          !_bDelayInit;                        //and the init is not delayed
}

//******************************************************************************
void TransFee::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
	if (canBeInitialized (idDataGroup))
	{
//this is a fee!!!
		setFieldNoValidate (ifds::RecordType, I_("Fee"), idDataGroup, false);
		getFeeParamConfigDefaults (idDataGroup);
//per system default
//do a set field no validate so validation will not be triggered,
//this is useful if somehow the set-up of view 253 is wrong
		setFieldNoValidate (ifds::TradeFeeOption, I_("0"), idDataGroup, false, true); 
		setFieldReadOnly (ifds::TransFeeCode, idDataGroup, true);
		setFieldReadOnly (ifds::Currency, idDataGroup, true);
		setFeeType (idDataGroup);
		setFeeDefault (idDataGroup);
		setChargeOption (idDataGroup);
		setFeeProperties (idDataGroup);
		setNonDummyFlag();
	}
}

//******************************************************************************
void TransFee::doReset (const BFDataGroupId &idDataGroup)
{
   if (!isNew())
   {
      initWithDefaultValues (idDataGroup);
   }
}

//******************************************************************************
inline SEVERITY TransFee::setFeeProperties (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeProperties"));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFee::setFeeType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeType"));
   FundFeeList *pFundFeeList = NULL;
   DString feeType (I_("0")); //flat

   if ( getFeeParams (pFundFeeList, idDataGroup) <= WARNING &&
        pFundFeeList)
   {
      pFundFeeList->getField (ifds::FeeType, feeType, idDataGroup);
   }
   setFieldNoValidate (ifds::FeeType, feeType, idDataGroup, false, false, true, false);
   setFieldNoValidate (ifds::OrigFeeType, feeType, idDataGroup, false, false, true, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFee::setChargeOption (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setChargeOption"));
   FundFeeList *pFundFeeList = NULL;
   DString chargeOption (I_("0"));

   if ( getFeeParams (pFundFeeList, idDataGroup) <= WARNING &&
        pFundFeeList)
   {
      pFundFeeList->getField (ifds::ChargeOption, chargeOption, idDataGroup);
      chargeOption.strip();
      if (chargeOption.empty())//if no fee params set-up, should default it to '0'
      {
         chargeOption = I_("0");
      }
   }
   setField (ifds::ChargeOption, chargeOption, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TransFee::applyModPerm ( const DString &modPerm,
                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("applyModPerm"));
//first make sure that the properties are set with the right data group id
   setFeeProperties (idDataGroup); 
   if ( modPerm == I_("0") ||
        modPerm == I_("4"))
   {
      for (int i = 0; i < NUM_FIELDS; i++)
      {
         BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];     
         const BFFieldId &fieldId = fieldInfo.getFieldId();

         setFieldReadOnly (fieldId, idDataGroup, true);
      }
   }
}

//******************************************************************************
SEVERITY TransFee::doValidateField ( const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   if (idField == ifds::TradeFeeOption)
   {
      validateTradeFeeOption (strValue, idDataGroup);
   }
   else if (idField == ifds::FeeType)
   {
      validateFeeType (strValue, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFee::doApplyRelatedChanges ( const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   if (idField == ifds::TradeFeeOption)
   {
      DString tradeFeeOption;

      getField (ifds::TradeFeeOption, tradeFeeOption, idDataGroup, false);
      if (tradeFeeOption == I_("0")) //charge as per system default
      {
//restore defaults
         setFeeDefault (idDataGroup);
      }
	  //P0178201FN01_WaiveDSCforClosedFund
	  else if (tradeFeeOption == I_("4")) 
	  {
		DString feeRate(I_("0"));

		setFieldNoValidate ( ifds::FeeRate, feeRate, idDataGroup, false, 
                           false,
                           true, //notify
                           false); //no related changes
	  }
	  //End - P0178201FN01_WaiveDSCforClosedFund
   }
   else if (idField == ifds::FeeType)
   {
      setFieldNoValidate ( ifds::TradeFeeOption, I_("2"), idDataGroup, false, //override
                           true,
                           true, //notify
                           false); //no related changes
   }
   else if (idField == ifds::FeeRate)
   {
      DString origFeeRate,
         feeRate,
         tradeFeeOption (I_("2")); //override
      
      getField (ifds::OrigFeeRate, origFeeRate, idDataGroup, false);
      getField (ifds::FeeRate, feeRate, idDataGroup, false);
      double dec_origFeeRate = DSTCommonFunctions::convertToDouble (origFeeRate),
         dec_feeRate = DSTCommonFunctions::convertToDouble (feeRate);
      if (// isChargeFee (idDataGroup) && 
           dec_feeRate == 0 ) //No
      {
         tradeFeeOption = I_("3"); //suppress
      }
      else if (dec_origFeeRate == dec_feeRate)
      {
         tradeFeeOption = I_("0"); //charge as per default
      }
      setFieldNoValidate ( ifds::TradeFeeOption, tradeFeeOption, idDataGroup, false, 
                           true,
                           true, //notify
                           false); //no related changes
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFee::getFeeParamConfigDefaults (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFeeParamConfigDefaults"));

   FeeParamConfigList *pFeeParamConfigList = NULL;
   bool bChargeOptionDefaultsRead = false,
      bChargeTradeFeeOptionDefaultsRead = false,
      bChargeFeeTypeOptionDefaultsRead = false;

   if ( getMgmtCo().getFeeParamConfigList (pFeeParamConfigList) <= WARNING &&
        pFeeParamConfigList)
   {
//perform an extra check if the fee code is found in fee param configuration
      DString feeCode;
      
      getField (ifds::TransFeeCode, feeCode, idDataGroup, false);

      BFObjIter bfIter (*pFeeParamConfigList, BF::HOST);

//since there are two records in view 253 for fee codes 114/115,
//then choose the one at fndbroker level
      if ( feeCode == FEES::AGGREGATED_COMMISSION ||
           feeCode == FEES::AGGREGATED_EXTERNAL_CHARGE)
      {
         DString strKey;

         pFeeParamConfigList->buildKeyForFundBrokerLevel (feeCode, strKey);
         bfIter.positionByKey (strKey);
      }
      while (!bfIter.end())
      {
         DString feeCode_;

         bfIter.getObject()->getField (ifds::FeeCode, feeCode_, idDataGroup);
         feeCode_.stripLeading ('0').strip();
         if (feeCode == feeCode_)
         {
            DString chargeOptionList,
               tradeFeeTypeList,
               feeTypeList;
			
            bfIter.getObject()->getField (ifds::ChargeOptionList, chargeOptionList, idDataGroup, false);
            bfIter.getObject()->getField (ifds::TradeFeeTypeList, tradeFeeTypeList, idDataGroup, false);
            bfIter.getObject()->getField (ifds::FeeTypeList, feeTypeList, idDataGroup, false);
            bChargeOptionDefaultsRead = 
               loadSubstitutionList (ifds::ChargeOption, idDataGroup, chargeOptionList);
            bChargeTradeFeeOptionDefaultsRead = 
               loadSubstitutionList (ifds::TradeFeeOption, idDataGroup, tradeFeeTypeList);
            bChargeFeeTypeOptionDefaultsRead = 
               loadSubstitutionList (ifds::FeeType, idDataGroup, feeTypeList);
            break;
         }
         ++bfIter;
      }
   }
//no defaults or the readings went wrong, ask the individual fee objects to provide the defaults
   if ( !bChargeOptionDefaultsRead ||
        !bChargeTradeFeeOptionDefaultsRead ||
        !bChargeFeeTypeOptionDefaultsRead)
   {
      getFeeConfigDefaults ( bChargeOptionDefaultsRead,
                             bChargeTradeFeeOptionDefaultsRead,
                             bChargeFeeTypeOptionDefaultsRead,
                             idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
inline void TransFee::getFeeConfigDefaults ( bool bChargeOptionDefaultsRead,
                                             bool bChargeTradeFeeOptionDefaultsRead,
                                             bool bChargeFeeTypeOptionDefaultsRead,
                                             const BFDataGroupId &idDataGroup)
{
   //usually a trans fee should have determined its defaults configs by now
   //special cases (i.e. ADLFee) override this method
   return;
}

//******************************************************************************
inline bool TransFee::useToSide ()
{
   //default implementation (ExchageIn Fee returns true)
   return false;
}

//******************************************************************************
inline bool TransFee::useFeeModelCode ()
{
   //default implementation (ConditionRate/TrxnFee return true)
   return false;
}

//******************************************************************************
SEVERITY TransFee::getFeeParams ( FundFeeList *&pFundFeeList, 
                                  const BFDataGroupId &idDataGroup)
{
   DString fundCode,
      classCode;

   if (useToSide())
   {
      getContext().getField (ifds::ToFund, fundCode, idDataGroup);
      getContext().getField (ifds::ToClass, classCode, idDataGroup);
   }
   else
   {
      getContext().getField (ifds::FromFund, fundCode, idDataGroup);
      getContext().getField (ifds::FromClass, classCode, idDataGroup);
   }
   return getFeeParams ( fundCode,
                         classCode,
                         pFundFeeList,
                         idDataGroup);
}

//******************************************************************************
SEVERITY TransFee::getFeeParams ( const DString &fundCode,
                                  const DString &classCode,
                                  FundFeeList *&pFundFeeList, 
                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFeeParams"));
   DString feeCode, 
      effectiveDate, 
      accountNum,
      broker, 
      branch, 
      slsrepCode, 
      stopDate,
      feeModelCode,
      commGroup;

   getField (ifds::TransFeeCode, feeCode, idDataGroup);
   getContext().getField (ifds::EffectiveDate, effectiveDate, idDataGroup);
   getContext().getField (ifds::AccountNum, accountNum, idDataGroup);
   getContext().getField (ifds::Broker, broker, idDataGroup);
   getContext().getField (ifds::Branch, branch, idDataGroup);
   getContext().getField (ifds::SlsrepCode, slsrepCode, idDataGroup);
   stopDate = effectiveDate;
   if (useFeeModelCode()) //find out the fee model code
   {
//look at the account, for the fee model code
      if ( getFeeModelCode (accountNum, feeModelCode, idDataGroup) <= WARNING &&
           !feeModelCode.empty())
      {
//now, find out the fund sponsor and assigned it to comm group
         if (!fundCode.empty())
         {
            FundMasterList *pFundMasterList = NULL;
            FundMaster *pFundMaster = NULL;
            if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
                 pFundMasterList &&
                 pFundMasterList->getFundMaster ( fundCode, 
                                                  idDataGroup, 
                                                  pFundMaster) &&
                  pFundMaster)
            {
               DString fundSponsor;

               pFundMaster->getField (ifds::FundGroup, fundSponsor, idDataGroup, false);
               commGroup = fundSponsor;
            }
         }
      }
   }
   feeCode.stripLeading ('0').strip();
   if (!feeCode.empty())
   {
      DString strKey = 
         I_("FundFeeList_FeeCode=") + feeCode +
         I_(";FundCode=") + fundCode +
         I_(";ClassCode=") + classCode +
         I_(";CommGroup=") + commGroup +
         I_(";EffectiveDate=") + effectiveDate +
         I_(";AccountNum=") + accountNum +
         I_(";Broker=") + broker +
         I_(";Branch=") + branch +
         I_(";SlsrepCode=") + slsrepCode +
         I_(";StopDate=") + stopDate +
         I_(";FeeModelCode=") + feeModelCode;

      pFundFeeList = 
         dynamic_cast<FundFeeList*> (getObject (strKey, idDataGroup));

      if (!pFundFeeList)
      {
         pFundFeeList = new FundFeeList (*this);
         if ( pFundFeeList->init ( feeCode, 
                                   fundCode,
                                   classCode,
                                   commGroup,
                                   effectiveDate,
                                   accountNum,
                                   I_("FindRecord"),
                                   NULL_STRING, 
                                   NULL_STRING, 
                                   NULL_STRING,
                                   NULL_STRING,
                                   stopDate, 
                                   broker, 
                                   NULL_STRING, 
                                   branch, 
                                   slsrepCode,
                                   NULL_STRING,
                                   feeModelCode) <= WARNING)
         {
            setObject ( pFundFeeList, 
                        strKey, 
                        OBJ_ACTIVITY_NONE, 
                        idDataGroup);
         }
         else
         {
            int count = CONDITIONCOUNT();
            Condition *c = NULL;
            for (int i = 0; i < count; i++)
            {
               c = GETCONDITION( i );
               int condCode = c->getCode();
               //do not want to promote this condition
               if (condCode == CND::ERR_FEE_PARAMS_NOT_AVAILABLE) 
               {
                  CLEARCONDITION (i);
                  break;
               }
            }         
            delete pFundFeeList;
            pFundFeeList = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool TransFee::hasFeeParams (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("hasFeeParams"));

   FundFeeList *pFundFeeList = NULL;

   return getFeeParams ( pFundFeeList, 
                         idDataGroup) <= WARNING && pFundFeeList;
}

//******************************************************************************
bool TransFee::hasFeeParams ( const DString &fundCode,
                              const DString &classCode,
                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("hasFeeParams"));

   FundFeeList *pFundFeeList = NULL;

   return getFeeParams ( fundCode, 
                         classCode, 
                         pFundFeeList, 
                         idDataGroup) <= WARNING && pFundFeeList;
}

//******************************************************************************
bool TransFee::hasFieldContextChanged ( const BFFieldId &idField,
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("hasContextChanged"));
   DString oldValue,
      value;
   bool retVal = false;

   if (_oldContext)
   {
      _oldContext->getField (idField, oldValue, idDataGroup);
   }
   if (_context)
   {
      _context->getField (idField, value, idDataGroup);
   }
   retVal = oldValue != value;
   return retVal;
}

//******************************************************************************
bool TransFee::hasFeeParamsContextChanged (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("hasFeeParamsContextChanged"));
   
   bool bFundContextChanged = false;

   if (useToSide())
   {
      bFundContextChanged = 
         hasFieldContextChanged (ifds::ToFund, idDataGroup) ||
         hasFieldContextChanged (ifds::ToClass, idDataGroup);
   }
   else
   {
      bFundContextChanged = 
         hasFieldContextChanged (ifds::FromFund, idDataGroup) ||
         hasFieldContextChanged (ifds::FromClass, idDataGroup);
   }
   return bFundContextChanged ||
          hasFieldContextChanged (ifds::EffectiveDate, idDataGroup) ||
          hasFieldContextChanged (ifds::AccountNum, idDataGroup) ||
          hasFieldContextChanged (ifds::Broker, idDataGroup) ||
          hasFieldContextChanged (ifds::Branch, idDataGroup) ||
          hasFieldContextChanged (ifds::SlsrepCode, idDataGroup);
}

//******************************************************************************
SEVERITY TransFee::validateTradeFeeOption ( const DString &strValue, 
                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateTradeFeeOption")
                         );
   if (strValue == I_("2")) //override
   {
      FeeSetupTradeRulesList *pFeeSetupTradeRulesList = NULL;

      if ( getMgmtCo().getFeeSetupTradeRulesList (pFeeSetupTradeRulesList) <= WARNING &&
           pFeeSetupTradeRulesList
         )
      {
         DString feeCode,
            transType;

         getField (ifds::TransFeeCode, feeCode, idDataGroup, false);
         getContext().getField (ifds::TransType, transType, idDataGroup, false);
         if (!pFeeSetupTradeRulesList->canFeeBeOverridden (feeCode, transType))
         {
            ADDCONDITIONFROMFILE (CND::ERR_FEE_CANNOT_BE_OVERRIDDEN);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFee::validateFeeType ( const DString &strValue, 
                                     const BFDataGroupId &idDataGroup
                                   )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFeeType")
                         );
   //get the default fee type, if it is scale or tier, do not raise the error
   DString defaultFeeType;

   FundFeeList *pFundFeeList = NULL;
   if ( getFeeParams (pFundFeeList, idDataGroup) <= WARNING &&
        pFundFeeList)
   {
      
      pFundFeeList->getField (ifds::FeeType, defaultFeeType, idDataGroup);
   }
//raise the error only if default doesn't exist or fee type is different then default
   if (defaultFeeType.empty() || defaultFeeType != strValue)
   {
      if (strValue == I_("2")) //scale
      {
         ADDCONDITIONFROMFILE (CND::ERR_FEE_TYPE_SCALE_NOT_SUPPORTED);
      }
      else if (strValue == I_("3")) //tier
      {
         ADDCONDITIONFROMFILE (CND::ERR_FEE_TYPE_TIER_NOT_SUPPORTED);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool TransFee::isFeeWaivedForAccount (const BFDataGroupId &idDataGroup)
{
   bool bIsFeeWaived = true;

   DString transType,
      accountNum;
   
   getContext().getField (ifds::TransType, transType, idDataGroup);
   if (DSTCommonFunctions::codeInList (transType, TRADETYPE::ONE_SIDE_TRADE))
   {
      getContext().getField (ifds::AccountNum, accountNum, idDataGroup);
   }
   else //two side trade
   {
      getContext().getField (ifds::AccountTo, accountNum, idDataGroup);
   }

   MFAccount *pMFAccount = NULL;

   if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
        pMFAccount)
   {
      DString feeWaived;
      
      pMFAccount->getField (ifds::FeeWaived, feeWaived, idDataGroup, false);
      bIsFeeWaived = feeWaived == I_("Y");
   }
   return bIsFeeWaived;
}

//******************************************************************************
DString TransFee::charge2Rate (const DString &charge)
{
   DString rate;

   if (charge == I_("N"))
   {
      rate = I_("0");
   }
   else if (charge == I_("Y"))
   {
      rate = I_("1");
   }
   return rate;
}

//******************************************************************************
SEVERITY TransFee::getFeeModelCode ( const DString &accountNum,
                                     DString &feeModelCode,
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFeeModelCode"));

   MFAccount *pMFAccount = NULL;

   if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
        pMFAccount)
   {
      pMFAccount->getField (ifds::FeeModelCode, feeModelCode, idDataGroup);
      if (feeModelCode.empty())
      {
   //get the fee model code from shareholder
         DString shrNum;
         Shareholder *pShareholder = NULL;

         pMFAccount->getField (ifds::ShrNum, shrNum, idDataGroup);
         //get the shareholder
         if ( getWorkSession ().getShareholder ( idDataGroup, 
                                                 shrNum, 
                                                 pShareholder) <= WARNING && 
              pShareholder)
         {
            pShareholder->getField (ifds::FeeModelCode, feeModelCode, idDataGroup);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
//*******************************************************************************
void TransFee::changeFieldsForRebook()
{
   //clear recordID
   setFieldNoValidate (ifds::TransFeeRID, NULL_STRING, BF::HOST, false);
   clearUpdatedFlags( BF::HOST ); // the object should not be dirty 
}

SEVERITY TransFee::applyTransFeeRateToAllocation(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("applyTransFeeRateToAllocation"));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool TransFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
	DString dstrRedCode, dstrTransType,DepositType;
	getContext().getField (ifds::RedCode, dstrRedCode, idDataGroup);
	getContext().getField (ifds::TransType, dstrTransType, idDataGroup);

	/* 
		Currently, only B1 is not charged any fees for transfer.
		Redemption is not applied this logic as BA's confirmation.
	*/
	if (dstrRedCode == I_("B1") && dstrTransType == I_("TR"))
		return false;
	
	return true;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransFee.cpp-arc  $
// 
//    Rev 1.41   Nov 29 2010 02:31:12   panatcha
// P0178201FN01_WaiveDSCforClosedFund - Remove setting the fee rate to read-only
// 
//    Rev 1.40   Nov 26 2010 09:07:36   panatcha
// P0178201FN01_WaiveDSCforClosedFund
// 
//    Rev 1.39   Oct 27 2009 14:18:48   jankovii
// IN 1889151 - System level Fee 112 with future stop date not display in DSK
// 
//    Rev 1.38   Sep 29 2009 14:50:58   popescu
// Incident 1847231 - Default value of Option and Rate of Fee Type 112, 212, 113 and 213
// 
//    Rev 1.37   Apr 24 2008 14:04:14   jankovii
// PET5347 FN08 - Commission override.
// 
//    Rev 1.36   Jul 15 2005 09:20:52   Yingbaol
// PET1235,FN01: Add Record ID ro field info
// 
//    Rev 1.35   Jul 08 2005 09:34:16   Yingbaol
// PET1235,FN01:transaction cancellation rebook
// 
//    Rev 1.34   Jun 20 2005 17:03:32   popescu
// Incident# 337811 - reversed the fee type/default settings, since defaulting is based on the type
// 
//    Rev 1.33   Apr 10 2005 17:56:38   popescu
// Incident 276992 - no need to override setField in this class
// 
//    Rev 1.32   Apr 09 2005 14:09:58   porteanm
// Incident 276992 - FeeRate not saved with the right precision.
// 
//    Rev 1.31   Mar 03 2005 08:56:32   popescu
// PET 1117/56, for fee type 'Charge' if user chooses to waive the fee, (set it to N), then set the trade fee option to 'Supress'
// 
//    Rev 1.30   Mar 03 2005 08:13:34   popescu
// PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
// 
//    Rev 1.29   Mar 02 2005 08:39:42   popescu
// PET 1117/56, apply 'useToSide' to 'hasFeeParamsContextChanged' method
// 
//    Rev 1.28   Mar 02 2005 08:31:12   popescu
// PET 1117/56, added virtual method meant to let the base class know which side (from or to) should be used when fee params are called
// 
//    Rev 1.27   Feb 28 2005 11:27:46   popescu
// PET 1117/56 for fees that have fee params, and the value of ChargeOption is empty, set it to '0'
// 
//    Rev 1.26   Feb 23 2005 10:56:40   popescu
// PET 1117/56, always set the object as non-dummy, so it will get saved even if the fee gets its data from default values.
// 
//    Rev 1.25   Feb 14 2005 17:30:20   popescu
// 240257, handling of fee code 116/Rebate Amount
// 
//    Rev 1.24   Feb 04 2005 11:54:06   popescu
// PET 1117/56, handling of two new fees 117/119
// 
//    Rev 1.23   Feb 03 2005 17:43:36   popescu
// PTS 10038591, fee model code was incorrectly read from the shareholder
// 
//    Rev 1.22   Jan 31 2005 18:19:46   popescu
// PET 1117/06/56, set the acq fee related fields to read only if shareholder has a fee model. Also, set option '1' for TradeFeeOption (Charge per system calculated)
// 
//    Rev 1.21   Jan 31 2005 12:33:06   popescu
// PTS 10038434, fix the fees read only properties based on the mod perm value of a pending trade 
// 
//    Rev 1.20   Jan 29 2005 16:35:08   popescu
// PTS 10038434, handling of  two new fees (114 and 115) existing in pending trades, part of aggregated orders
// 
//    Rev 1.19   Jan 29 2005 12:36:26   winnie
// PTS 10038434 : Restore the statement to filter the valid TradeFeeOption substitution list based on the set up in Fee Parmeters
// 
//    Rev 1.18   Jan 23 2005 15:22:14   popescu
// PTS 10037685, read the charge option defaults and fee type defaults from view 253
// 
//    Rev 1.17   Jan 18 2005 19:42:20   popescu
// PTS 10038609, acquisition does not get refreshed if split comm changes to default
// 
//    Rev 1.16   Jan 14 2005 10:31:02   popescu
// PTS 10037865, charge option field should be 'Charge' and locked for Conditionrate and all other fees, but TrxnFee where user should be allowed to change its value.
// 
//    Rev 1.15   Jan 12 2005 14:42:42   popescu
// PTS 10037788, fee charge option default value fix
// 
//    Rev 1.14   Jan 10 2005 10:38:52   popescu
// PTS 10037553, fixed fees properties in pending mode and trade reset of the trans type combo
// 
//    Rev 1.13   Jan 04 2005 16:15:00   popescu
// PTS 10037245, enable acq fee default for user input if trade is allocated and DisableFee4Alloc is turned off
// 
//    Rev 1.12   Dec 15 2004 15:55:32   popescu
// PET 1117/06, fixes related to condition rates scale type/ acq fee option defaults
// 
//    Rev 1.11   Dec 09 2004 22:31:06   popescu
// PET 11717/06, fees and mod pending trades
// 
//    Rev 1.10   Dec 09 2004 12:37:48   popescu
// PET 1117/56, more fees work /pending trade
// 
//    Rev 1.9   Dec 08 2004 22:08:26   popescu
// PET 1117/06, more fees
// 
//    Rev 1.8   Dec 02 2004 20:59:40   popescu
// PET 1117/06, more fee fixes
// 
//    Rev 1.7   Dec 01 2004 19:50:30   popescu
// PET 1117/06, trades/fees processing, incorporate fees in trades transaction builder, and added method to copy fee values onto the trades fee fields for cycle processing
// 
//    Rev 1.6   Dec 01 2004 15:45:16   popescu
// PET 1117/56 fees processing, calculate the discount rate
// 
//    Rev 1.5   Nov 24 2004 21:36:28   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.4   Nov 17 2004 16:15:46   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.3   Nov 15 2004 16:23:34   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.1   Nov 09 2004 16:50:56   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Nov 05 2004 21:30:14   popescu
// Initial revision.
// 
 */