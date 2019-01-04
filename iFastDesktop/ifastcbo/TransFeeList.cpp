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
// ^FILE   : TransFeeList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : July 2004
//
// ^CLASS    : TransFeeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "transfeelist.hpp"

#include "acquisitionfee.hpp"
#include "adlfee.hpp"
#include "aggregatedfee.hpp"
#include "clawbackfee.hpp"
#include "conditionrate.hpp"
#include "dscfee.hpp"
#include "earlyredemptionfee.hpp"
#include "eventcommissiondeathfee.hpp"
#include "eventcommissionretirefee.hpp"
#include "exchangefee.hpp"
#include "exchangeoutfee.hpp"
#include "exchangeinfee.hpp"
#include "feesetuptraderuleslist.hpp"
#include "giadminfee.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "mvafee.hpp"
#include "nofee.hpp"
#include "shareholder.hpp"
#include "shorttermtrsffee.hpp"
#include "redemptionfee.hpp"
#include "transfee.hpp"
#include "tpafee.hpp"
#include "trade.hpp"
#include "trxnfee.hpp"
#include "withdrawalfee.hpp"
#include "xferinfee.hpp"
#include "xferoutfee.hpp"
#include "SpreadFee.hpp"

//fees inquiry
#include <ifastdataimpl\dse_dstc0298_req.hpp>
#include <ifastdataimpl\dse_dstc0298_vw.hpp>

//discount rate calculation
#include <ifastdataimpl\dse_dstc0311_req.hpp>
#include <ifastdataimpl\dse_dstc0311_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSACTION_FEES;
   extern CLASS_IMPORT const DSTCRequest DISCOUNT_RATE_CALCULATION;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("TransFeeList");
}

namespace CND
{  // Conditions used
}

namespace ifds
{
//field ids used
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFIntegerFieldId TransFeeCode;
   extern CLASS_IMPORT const BFDecimalFieldId DiscountRate;
   extern CLASS_IMPORT const BFDecimalFieldId ConditionRate;
//shareholder fields
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisCode;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
}

namespace FEES
{
   extern CLASS_EXPORT const I_CHAR * ACQUISITION                          = I_("1");
   extern CLASS_EXPORT const I_CHAR * DSC                                  = I_("3");
   extern CLASS_EXPORT const I_CHAR * EXCHANGE                             = I_("996");
   extern CLASS_EXPORT const I_CHAR * EXCHANGE_OUT                         = I_("44");
   extern CLASS_EXPORT const I_CHAR * EXCHANGE_IN                          = I_("49");
   extern CLASS_EXPORT const I_CHAR * CLAWBACK                             = I_("62");
   extern CLASS_EXPORT const I_CHAR * ADL                                  = I_("96");
   extern CLASS_EXPORT const I_CHAR * PURCHASE_CONDITION_RATE              = I_("110");
   extern CLASS_EXPORT const I_CHAR * REINVEST_PURCHASE_CONDITION_RATE     = I_("111");
   extern CLASS_EXPORT const I_CHAR * PURCHASE_TRXN                        = I_("112");
   extern CLASS_EXPORT const I_CHAR * PURCHASE_SPREAD_FEE                  = I_("122");
   extern CLASS_EXPORT const I_CHAR * REDEMPTION_SPREAD_FEE                = I_("123");
   extern CLASS_EXPORT const I_CHAR * REDEMPTION_TRXN                      = I_("113");
   extern CLASS_EXPORT const I_CHAR * AGGREGATED_EXTERNAL_CHARGE           = I_("114");
   extern CLASS_EXPORT const I_CHAR * AGGREGATED_COMMISSION                = I_("115");
   extern CLASS_EXPORT const I_CHAR * REBATE_AMOUNT                        = I_("116");
   extern CLASS_EXPORT const I_CHAR * MISC_COMMISSION                      = I_("117");
   extern CLASS_EXPORT const I_CHAR * DISCOUNT_RATE                        = I_("119");
   extern CLASS_EXPORT const I_CHAR * REDEMPTION_LIQUIDITY_FEE             = I_("127");
   extern CLASS_EXPORT const I_CHAR * WITHDRAWAL                           = I_("173");
   extern CLASS_EXPORT const I_CHAR * PURCHASE_TPA                         = I_("212");
   extern CLASS_EXPORT const I_CHAR * REDEMPTION_TPA                       = I_("213");
   extern CLASS_EXPORT const I_CHAR * EARLY_REDEMPTION                     = I_("340");
   extern CLASS_EXPORT const I_CHAR * SHORT_TERM_TRANSFER                  = I_("350");
   extern CLASS_EXPORT const I_CHAR * EVENT_COMMISSION_DEATH               = I_("601");
   extern CLASS_EXPORT const I_CHAR * EVENT_COMMISSION_RETIRE              = I_("602");
   extern CLASS_EXPORT const I_CHAR * MVA                                  = I_("700");
   extern CLASS_EXPORT const I_CHAR * GIADMIN                              = I_("701");
   extern CLASS_EXPORT const I_CHAR * REDEMPTION                           = I_("997");
   extern CLASS_EXPORT const I_CHAR * XFER_OUT                             = I_("998");
   extern CLASS_EXPORT const I_CHAR * XFER_IN                              = I_("999");
   extern CLASS_EXPORT const I_CHAR * NO_FEE                               = I_("10000");
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const REINVEST_PURCHASE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                             //  Field DD Id,      State Flags,      Group Flags 
   { ifds::TransType,   BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::TransNum,    BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
   { ifds::AccountNum,  BFCBO::NONE,      BFCBO::CALCULATED_FIELD }, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
void TransFeeList::buildKey (const DString &feeCode, const DString& fundCode, const DString& classCode, DString &strKey)
{
   DString feeCode_   (feeCode);
   DString fundCode_  (fundCode);
   DString classCode_ (classCode);
   fundCode_.strip();
   classCode_.strip();

   strKey = I_("FeeCode=") + feeCode_.strip() + I_(";");

   if(fundCode_ != NULL_STRING)
      strKey += I_("FundCode=") + fundCode_ + I_(";");

   if(classCode_ != NULL_STRING)
      strKey += I_("ClassCode=") + classCode_  + I_(";");
}

//******************************************************************************
TransFeeList::TransFeeList (BFAbstractCBO &parent) : MFCanBFCbo (parent),
_strKey (NULL_STRING),
_context (NULL),
_idDataGroup (BF::HOST),
_forcingRefresh(false)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
   registerMemberData( NUM_FIELDS,(const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,NULL);
}

//******************************************************************************
TransFeeList::~TransFeeList ()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY TransFeeList::initNew ( const DString &transNum,
                                 const DString &accountNum,
                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init"));

   setFieldNoValidate (ifds::TransNum, transNum, idDataGroup, false);
   setFieldNoValidate (ifds::AccountNum, accountNum, idDataGroup, false);
   _idDataGroup = idDataGroup;
   refresh (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeList::init ( const DString &transNum,
                              const DString &accountNum,
                              const BFDataGroupId &idDataGroup,
                              const DString &dstrTrack /*= I_("N")*/, 
                              const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));


   setFieldNoValidate (ifds::TransNum, transNum, BF::HOST, false);
   setFieldNoValidate (ifds::AccountNum, accountNum, BF::HOST, false);
   _idDataGroup = idDataGroup;
   
   BFData requestData (ifds::DSTC0298_REQ);
   DString mgmtCoIdOut;

   requestData.setElementValue (ifds::TransNum, transNum);
   requestData.setElementValue (ifds::AccountNum, accountNum);
   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName);
   refreshFeeCodes (idDataGroup);
   ReceiveData ( DSTC_REQUEST::TRANSACTION_FEES, 
                 requestData, 
                 ifds::DSTC0298_VW, 
                 DSTCRequestor(getSecurity(), false));
   refreshContext (idDataGroup, true); //restore value from trade
   calculateDiscountRate (idDataGroup); //because this has to be reflected on the screen use the caller's data group id
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeList::getTransFee ( const DString &feeCode,
                                     TransFee *&pTransFee,
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getTransFee"));

   pTransFee = NULL;

   DString strKey;
   DString fundCode;
   DString classCode;

   buildKey (feeCode, fundCode, classCode, strKey);
   BFObjIter iter ( *this, 
                    idDataGroup,
                    true,
                    BFObjIter::ITERTYPE::NON_DELETED);
   if (iter.positionByKey (strKey))
   {
      pTransFee = dynamic_cast <TransFee*> (iter.getObject());
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeList::getTransFeeRate ( const DString &feeCode, DString &feeRate, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTransFee"));

   feeRate = I_("");

   TransFee* pTransFee = NULL;
   getTransFee ( feeCode, pTransFee, idDataGroup);
   if(pTransFee != NULL)
   {
      pTransFee->getField(ifds::FeeRate, feeRate, BF::HOST);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeList::setTransFeeRate ( const DString &feeCode, const DString &feeRate, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setTransFee"));

   TransFee* pTransFee = NULL;
   getTransFee ( feeCode, pTransFee, idDataGroup);
   if(pTransFee != NULL && I_("") != feeRate)
   {
      pTransFee->setField(ifds::FeeRate, feeRate, BF::HOST, false);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeList::applyTransFeeRateToAllocation(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("applyTransFeeRateToAllocation"));

   TransFee* pTransFee = NULL;

   BFObjIter iter ( *this, 
                     idDataGroup, 
                     false, 
                     BFObjIter::ITERTYPE::NON_DELETED);

   iter.begin();
   while (!iter.end())
   {
      pTransFee = dynamic_cast <TransFee*> (iter.getObject());
      if(pTransFee)
      {
         pTransFee->applyTransFeeRateToAllocation(idDataGroup);
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeList::doCreateNewObject ( BFCBO *&pBase, 
                                           DString &strKey, 
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

//extract the fee code
   DString feeCode;
   DString::size_type pos = _strKey.find (I_("="));
   DString::size_type pos1 = _strKey.find (I_(";"));
   
   assert (pos != DString::npos); //should always happen
   
   if (pos != DString::npos)
   {
      feeCode = _strKey.substr (pos + 1);
   }

   pos = feeCode.find (I_(";"));
   if (pos != DString::npos)
   {
      feeCode = feeCode.substr (0, pos);
   }

      
   TransFee *pTransFee = makeFee (feeCode, idDataGroup);

   assert (pTransFee);
//pass the context down to the objects
   pTransFee->setContext (*_context);
   pTransFee->init (idDataGroup, true); //delay the init, until fee is applicable
   pBase = pTransFee;
   strKey = _strKey;
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY TransFeeList::doCreateObject ( const BFData &data, 
                                        BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doCreateObject"));

   DString feeCode = data.getElementValue (ifds::TransFeeCode);
   
   feeCode.strip().upperCase();

   TransFee *pTransFee = makeFee (feeCode, BF::HOST);

   assert (pTransFee);
//pass the context down to the objects
   if (_context)
   {
      pTransFee->setContext (*_context);
   }
   if(pTransFee->init (data) >= SEVERE_ERROR)
   {
      delete pTransFee;
      pTransFee = NULL;
   };
   pObjOut = pTransFee;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
inline void TransFeeList::setContext (const TransFeeContext &context)
{
   _context = const_cast <TransFeeContext*> (&context);
}

//******************************************************************************
SEVERITY TransFeeList::refresh (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("refresh"));
//refresh the set-up, based on the context the fee codes array can change   
//context should already be set here...
   assert (_context);

   refreshFeeCodes (idDataGroup);
   std::vector <DString> v_delta;

//extract the fees that do not apply any more
   BFObjIter iter_ ( *this, 
                     idDataGroup,
                     false,
                     BFObjIter::ITERTYPE::NON_DELETED);
   while (!iter_.end())
   {
      DString feeCode;

      iter_.getObject()->getField (ifds::TransFeeCode, feeCode, idDataGroup, false);
      //see if this code is within the fee codes list
      bool bExists = false;
      for (unsigned int i = 0; i < _feeCodes.size(); i++)
      {
         if (feeCode == _feeCodes [i])
         {
            bExists = true;
            break;
         }
      }
      if (!bExists)
      {
         v_delta.push_back (feeCode);
      }
      ++iter_;
   }
//delete what does not apply

   DString fundCode;
   DString classCode;

   for (unsigned int j = 0; j < v_delta.size(); j++)
   {
      BFObjIter iter ( *this, 
                       idDataGroup,
                       false,
                       BFObjIter::ITERTYPE::NON_DELETED);
      DString strKey;

      buildKey (v_delta [j], fundCode, classCode, strKey);
      if (iter.positionByKey (strKey))
      {
         deleteObject (strKey, idDataGroup); //this will also mark it for delete
      }
   }
   refreshContext (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeList::refreshContext ( const BFDataGroupId &idDataGroup, 
                                        bool bRestore /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("refreshContext"));
//context should already be set here...
   assert (_context);
//finally, refresh the list
   for (unsigned int k = 0; k < _feeCodes.size(); k++)
   {
      BFObjIter iter ( *this, 
                       idDataGroup,
                       true,
                       BFObjIter::ITERTYPE::NON_DELETED); //do not want to refresh the deleted objects
      TransFee *pTransFee = NULL;
      
      DString fundCode;
      DString classCode;
      
      buildKey (_feeCodes [k], fundCode, classCode, _strKey);

      bool bFound = iter.positionByKey (_strKey);
      
      if (bFound)
      {
         pTransFee = dynamic_cast <TransFee*> (iter.getObject());
         pTransFee->setContext (*_context); //set the new context
      }
      else
      {
         DString emptyKey; //forces a new item

         pTransFee = dynamic_cast <TransFee*> (getObject (emptyKey, idDataGroup));
      }
      if ( !pTransFee->isSystemApplicable (idDataGroup) || 
           !pTransFee->isContextApplicable (idDataGroup))
      {
		  if(bFound)
			  iter.deleteObject (); //this will  mark it for delete when object is found but may not have exact match for strykey
		  else
			  deleteObject (_strKey, idDataGroup); //this will also mark it for delete
      }
      else 
      {
         if (bFound) //do not reset newly created fees
         {
            if (!bRestore) //if call is to 'restore', then stick with what we have
            {
               if (pTransFee->hasContextChanged (idDataGroup))
               {
                  pTransFee->reInit (idDataGroup);
               }
               else
               {
   //values of the new context can be of interest for validations
                  pTransFee->validateAll (idDataGroup); 
               }
            }
         }
         else
         {
            pTransFee->reInit (idDataGroup); //no delay this time
            if (bRestore)
            {
               if (getParent()) //only if parent is not null..
               {
                  pTransFee->restore (*getParent(), idDataGroup);
               }
            }
         }
      }
   }
   calculateDiscountRate (idDataGroup);
   _forcingRefresh = false;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TransFeeList::getStrKey ( DString &strKey, 
                               const BFData *data)
{
   if (data) 
   {
      DString fundCode;
      DString classCode;
      buildKey (data->getElementValue (ifds::TransFeeCode), data->getElementValue (ifds::FundCode), data->getElementValue (ifds::ClassCode), strKey);
   }
   else
   {
      BFCBO::getStrKey (strKey, NULL);
   }
}

//******************************************************************************
TransFee *TransFeeList::makeFee ( const DString &feeCode,
                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("makeFee"));

   Trade *pTrade = dynamic_cast <Trade*>(getParent());
   TransFee *pTransFee = NULL;

   if (feeCode == FEES::ACQUISITION)
   {
      pTransFee = new AcquisitionFee (*this);
   }
   else if (feeCode == FEES::ADL)
   {
      pTransFee = new ADLFee (*this);
   }
   else if (feeCode == FEES::DSC)
   {
      pTransFee = new DSCFee (*this);
   }
   else if (feeCode == FEES::EXCHANGE)
   {
      pTransFee = new ExchangeFee (*this);
   }
   else if (feeCode == FEES::EXCHANGE_OUT)
   {
      pTransFee = new ExchangeOutFee (*this);
   }
   else if (feeCode == FEES::EXCHANGE_IN)
   {
      pTransFee = new ExchangeInFee (*this);
   }
   else if ( feeCode == FEES::PURCHASE_CONDITION_RATE ||
             feeCode == FEES::REINVEST_PURCHASE_CONDITION_RATE)
   {
      pTransFee = new ConditionRate (*this, feeCode);
   }
   else if ( feeCode == FEES::PURCHASE_TRXN ||
             feeCode == FEES::REDEMPTION_TRXN)
   {
      pTransFee = new TrxnFee (*this, feeCode);
   }
   else if (feeCode == FEES::WITHDRAWAL)
   {
      pTransFee = new WithdrawalFee (*this);
   }
   else if (feeCode == FEES::EARLY_REDEMPTION)
   {
      pTransFee = new EarlyRedemptionFee (*this);
   }
   else if (feeCode == FEES::REDEMPTION)
   {
      pTransFee = new RedemptionFee (*this);
   }
   else if (feeCode == FEES::SHORT_TERM_TRANSFER)
   {
      pTransFee = new ShortTermTrsfFee (*this);
   }
   else if (feeCode == FEES::MVA)
   {
      pTransFee = new MVAFee (*this);
   }
   else if (feeCode == FEES::GIADMIN)
   {
      pTransFee = new GIAdminFee (*this);
   }
   else if (feeCode == FEES::XFER_OUT)
   {
      pTransFee = new XferOutFee (*this);
   }
   else if (feeCode == FEES::XFER_IN)
   {
      pTransFee = new XferInFee (*this);
   }
   else if ( feeCode == FEES::AGGREGATED_EXTERNAL_CHARGE ||
             feeCode == FEES::AGGREGATED_COMMISSION ||
             feeCode == FEES::DISCOUNT_RATE ||
             feeCode == FEES::MISC_COMMISSION ||
             feeCode == FEES::REBATE_AMOUNT)
   {
      pTransFee = new AggregatedFee (*this, feeCode);
   }
   else if ( feeCode == FEES::PURCHASE_TPA || 
             feeCode == FEES::REDEMPTION_TPA)
   {
      pTransFee = new TPAFee (*this, feeCode);
   }
   else if (feeCode == FEES::CLAWBACK)
   {
      pTransFee = new ClawbackFee (*this);
   }
   else if (feeCode == FEES::EVENT_COMMISSION_DEATH)
   {
      pTransFee = new EventCommissionDeathFee (*this);
   }
   else if (feeCode == FEES::EVENT_COMMISSION_RETIRE)
   {
      pTransFee = new EventCommissionRetireFee (*this);
   }
   else if ( FEES::PURCHASE_SPREAD_FEE == feeCode || 
             FEES::REDEMPTION_SPREAD_FEE == feeCode || 
			 FEES::REDEMPTION_LIQUIDITY_FEE == feeCode)
   {
     pTransFee = new SpreadFee(*this, feeCode);
   }
   else if (!pTransFee)
   {
      pTransFee = new NoFee (*this); //to avoid crashes of non-handled fee codes
   }
   return pTransFee;
}

//******************************************************************************
void TransFeeList::onNotify ( E_EVENT_GROUP eEventCateg, 
                              E_EVENT eEventId, 
                              const DString &hint)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("onNotify"));
   if ( eEventCateg == FIELD_NOTIFICATIONS &&  //we only care about field notifications
        eEventId == E_EVENT_VALUE_CHANGE)      //we only care about value changes
   {
   //when we are notified we should refresh the context of our children
      assert (getParent());
      Trade *pTrade = dynamic_cast <Trade*> (getParent());
      
      if (pTrade && _context)  //already have the context set?
      {
         //save the current context
         TransFeeContext *oldContext = new TransFeeContext (*pTrade);

         *oldContext = *_context;
         _context = NULL; 
         //ask for the the new context
         if (pTrade->getTransFeeContext (_context, _idDataGroup) <= WARNING && _context)
         {
//refresh only if context changed, or we are hinted to force a refresh
            if (!(*_context == *oldContext) || hint == I_("ForceRefresh")) 
            {
               DString oldRedCode,
                  oldDepositType,
                  redCode,
                  depositType;

               oldContext->getField (ifds::RedCode, oldRedCode, _idDataGroup, false);
               oldContext->getField (ifds::DepositType, oldDepositType, _idDataGroup, false);
               _context->getField (ifds::RedCode, redCode, _idDataGroup, false);
               _context->getField (ifds::DepositType, depositType, _idDataGroup, false);
   //refresh this list first if red code or deposit type changed
               if ( redCode != oldRedCode ||
                    depositType != oldDepositType)
               {
                  //refresh the entire list and read the set-up defaults again, 
                  //this will reset the context for the items
                  refresh (_idDataGroup); 
               }
               else //refresh the context, only
               {
                  refreshContext (_idDataGroup);
               }
            }
         }
         delete oldContext; //get rid of the old context
         oldContext = NULL;
      }
   }
}

//******************************************************************************
SEVERITY TransFeeList::refreshFeeCodes (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("refreshFeeCodes"));

   DString accountNum,
      transType,
      redCode,
      depositType,
      indc;
   MFAccount *pMFAccount = NULL;

   getField (ifds::AccountNum, accountNum, idDataGroup, false);
   accountNum.stripLeading ('0').strip();
   _context->getField (ifds::TransType, transType, idDataGroup, false);
   _context->getField (ifds::RedCode, redCode, idDataGroup, false);
   _context->getField (ifds::DepositType, depositType, idDataGroup, false);
   if ( !accountNum.empty() &&
        getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
        pMFAccount)
   {
      DString shrNum;
      
      pMFAccount->getField (ifds::ShrNum, shrNum, idDataGroup);

      Shareholder *pShareholder = NULL;
      if ( getWorkSession ().getShareholder (idDataGroup, shrNum, pShareholder) <= WARNING &&
           pShareholder) 
      {
         DString taxJuris;

         pShareholder->getField (ifds::TaxJurisCode, taxJuris, idDataGroup);

         FeeSetupTradeRulesList *pFeeSetupTradeRulesList = NULL;

         if ( getMgmtCo().getFeeSetupTradeRulesList (pFeeSetupTradeRulesList) <= WARNING &&
              pFeeSetupTradeRulesList)
         {
//get the applicable fee codes, 
            pFeeSetupTradeRulesList->getFeeCodes ( transType, 
                                                   redCode, 
                                                   depositType, 
                                                   indc,  //??
                                                   taxJuris, 
                                                   _feeCodes);
         }
      }         
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransFeeList::calculateDiscountRate (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("calculateDiscountRate"));
   DString discountRate;
   
   assert (getParent());
   Trade *pTrade = dynamic_cast <Trade*> (getParent());

   if (pTrade)
   {         
      DString transType,
         acqFeeOption;

      pTrade->getField (ifds::TradesTransType, transType, idDataGroup, false);
      pTrade->getField (ifds::AcqFeeOption, acqFeeOption, idDataGroup, false);
//only for discount fee model calculate the discount 
      if (acqFeeOption == I_("1") && 
            ( transType == TRADETYPE::PURCHASE ||
              transType == TRADETYPE::REINVEST_PURCHASE))
      {
//find the acquisition fee rate
         TransFee *pAcqFee = NULL,
            *pCondionRate = NULL;

         if ( getTransFee (FEES::ACQUISITION, pAcqFee, idDataGroup) <= WARNING &&
              pAcqFee &&
              getTransFee ( transType == TRADETYPE::PURCHASE ? 
                              FEES::PURCHASE_CONDITION_RATE : 
                              FEES::REINVEST_PURCHASE_CONDITION_RATE,
                            pCondionRate, 
                            idDataGroup) <= WARNING &&
              pCondionRate)
         {
            DString conditionRate,
               acqFeeRate,
               fundCode,
               classCode,
			      mgmtCoIdOut;

            pCondionRate->getField (ifds::FeeRate, conditionRate, idDataGroup);
            //get the client condtion rate
            pAcqFee->getField (ifds::FeeRate, acqFeeRate, idDataGroup);
            pTrade->getField (ifds::FromFund, fundCode, idDataGroup);
            pTrade->getField (ifds::FromClass, classCode, idDataGroup);
            
            //call 311 to find the discount rate
            BFData requestData (ifds::DSTC0311_REQ);//311 request
            BFData receivedData(ifds::DSTC0311_VW);

            //set the request up
            requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
            requestData.setElementValue (ifds::TransType, transType);
            requestData.setElementValue (ifds::FundCode, fundCode);
            requestData.setElementValue (ifds::ClassCode, classCode);
            requestData.setElementValue (ifds::ConditionRate, conditionRate);
            requestData.setElementValue (ifds::AcqFee, acqFeeRate);
            //call the view
            if ( BFDataBroker::getInstance ()->
                  receive ( DSTC_REQUEST::DISCOUNT_RATE_CALCULATION, 
                              requestData, 
                              receivedData, 
                              DSTCRequestor (getSecurity ())) <= WARNING)
            {
               discountRate = receivedData.getElementValue (ifds::DiscountRate, 0x0003);
               discountRate.strip();
            }
         }
      }
   //set the value on trade 
      if (pTrade)
      {
         pTrade->setField (ifds::DiscountRate, discountRate, idDataGroup, true, true);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
void TransFeeList::setDataGroupForRefresh (const BFDataGroupId &idDataGroup)
{
   _idDataGroup = idDataGroup;
}

//******************************************************************************
void TransFeeList::doCommitDataGroup( const BFDataGroupId& idDataGroup )
{
   const BFDataGroupId& parentGroup = idDataGroup.getParent();
   setDataGroupForRefresh(parentGroup);
}

//******************************************************************************
void TransFeeList::changeFieldsForRebook()
{
    Trade *pTrade = dynamic_cast <Trade*> (getParent());
    if (pTrade)
    { 
      DString transNum;

      pTrade->getField (ifds::TransNum, transNum, BF::HOST, false);
      setFieldNoValidate (ifds::TransNum, transNum, BF::HOST, false);

      BFObjIter iter (*this, BF::HOST);
      
      while ( !iter.end() )
      {
         TransFee* pTransFee = dynamic_cast <TransFee*> (iter.getObject());
         
         if (pTransFee)
         {
            pTransFee->changeFieldsForRebook();
         }
         ++iter;
      }  
    }
    clearUpdatedFlags (BF::HOST); // the object should not be dirty 
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransFeeList.cpp-arc  $
// 
//    Rev 1.37   Aug 15 2012 18:14:04   dchatcha
// PETP0186479 FN11 - Event Commission on Transfer In
// 
//    Rev 1.36   Mar 08 2012 10:02:38   if991250
// GI Money Out
// 
//    Rev 1.35   Jan 27 2012 12:32:46   if991250
// fix deadlock on changing GI attributes for a pending purchase
// 
//    Rev 1.34   Dec 16 2011 11:19:12   popescu
// INA Commission Work
// 
//    Rev 1.33   Nov 27 2011 19:43:46   popescu
// INA Commission Work
// 
//    Rev 1.32   12 Aug 2009 15:33:04   popescu
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields
// 
//    Rev 1.31   Sep 12 2005 14:00:42   popescu
// Incident #399924 - refresh the fees list for rebooks, pending trades.
// 
//    Rev 1.30   Jul 08 2005 09:34:24   Yingbaol
// PET1235,FN01:transaction cancellation rebook
// 
//    Rev 1.29   Mar 03 2005 08:35:04   popescu
// PET 1117/56, only 'restore' if fee if not found
// 
//    Rev 1.28   Mar 03 2005 08:13:42   popescu
// PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
// 
//    Rev 1.27   Feb 17 2005 10:21:52   popescu
// PTS 243445, refresh of Discount Rate was not properly done for pending trades; made the view call with the proper datagroupid
// 
//    Rev 1.26   Feb 14 2005 17:30:24   popescu
// 240257, handling of fee code 116/Rebate Amount
// 
//    Rev 1.25   Feb 04 2005 11:54:10   popescu
// PET 1117/56, handling of two new fees 117/119
// 
//    Rev 1.24   Jan 29 2005 16:35:14   popescu
// PTS 10038434, handling of  two new fees (114 and 115) existing in pending trades, part of aggregated orders
// 
//    Rev 1.23   Jan 28 2005 06:59:02   aguilaam
// PTS 10038324, added XferOut fee to the makeFee method
// 
//    Rev 1.22   Jan 23 2005 13:57:48   popescu
// PTS 10037346, made exchange available for the user
// 
//    Rev 1.21   Jan 19 2005 16:41:16   popescu
// PTS 10038121, fixed display of acquisition fee for allocated trades
// 
//    Rev 1.20   Jan 13 2005 18:33:20   popescu
// PTS 10037865, refresh fee codes if for trades in pending mode
// 
//    Rev 1.19   Jan 12 2005 18:53:26   popescu
// PTS 10037339, allowed user to set Redemption Fee up
// 
//    Rev 1.18   Dec 14 2004 09:59:50   popescu
// PET 1117/06, refresh trans fee list in pending mode
// 
//    Rev 1.17   Dec 11 2004 11:48:06   popescu
// PET 1117/56 more fixes, pending trade mods
// 
//    Rev 1.16   Dec 10 2004 18:11:24   popescu
// PET 1117/06, more fixes
// 
//    Rev 1.15   Dec 09 2004 22:31:06   popescu
// PET 11717/06, fees and mod pending trades
// 
//    Rev 1.14   Dec 08 2004 22:08:30   popescu
// PET 1117/06, more fees
// 
//    Rev 1.13   Dec 07 2004 21:20:44   popescu
// PET 1117/06, pending trades/fees fixes, add-ons
// 
//    Rev 1.12   Dec 06 2004 16:59:38   popescu
// PET 1117/06, figured out the funny fix, put a proper fix in
// 
//    Rev 1.11   Dec 06 2004 16:51:34   popescu
// PET 1117/06, funny fix
// 
//    Rev 1.10   Dec 02 2004 20:59:42   popescu
// PET 1117/06, more fee fixes
// 
//    Rev 1.9   Dec 01 2004 15:45:18   popescu
// PET 1117/56 fees processing, calculate the discount rate
// 
//    Rev 1.8   Dec 01 2004 11:10:26   popescu
// PTS 10036050, fee cannot be percent for red code 16,17 bearer certificate
// 
//    Rev 1.7   Nov 29 2004 20:30:56   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.6   Nov 27 2004 21:19:28   popescu
// PET 1117/06, trades processing
// 
//    Rev 1.5   Nov 19 2004 10:04:40   popescu
// PET 1117.06, fees processing
// 
//    Rev 1.4   Nov 17 2004 16:15:58   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.3   Nov 15 2004 16:24:16   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.1   Nov 09 2004 16:51:14   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Nov 05 2004 21:30:26   popescu
// Initial revision.
// 
 */