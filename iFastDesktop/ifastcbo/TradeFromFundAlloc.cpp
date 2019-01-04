//*****************************************************************************
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
//*****************************************************************************
//
//    ^FILE   : TradeFromFundAlloc.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : August, 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : TradeFromFundAlloc
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "fundalloc.hpp"
#include "funddetail.hpp"
#include "mfaccount.hpp"
#include "mfaccountholdinglist.hpp"
#include "pendingtradedetails.hpp"
#include "transactiondetails.hpp"
#include "trade.hpp"
#include "tradefromfundalloc.hpp"
#include "tradeacctalloc.hpp"
#include "tradeacctalloclist.hpp"
#include "tradefromfundalloc.hpp"
#include "tradefromfundalloclist.hpp"
#include "tradefundalloc.hpp"
#include "tradefundalloclist.hpp"
#include <ifastdataimpl\dse_dstc0060_vwrepeat_record.hpp>

namespace 
{
   const I_CHAR * CLASSNAME = I_("TradeFromFundAlloc");
   const I_CHAR * HOLDINGS_LIST = I_("HoldingsList");
}

namespace ifds
{
   //field ids used
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId FromClass;
   extern CLASS_IMPORT const BFTextFieldId FromFund;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeAlloc;
   extern CLASS_IMPORT const BFTextFieldId AmtType;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId AllowFullTransfer;
   extern CLASS_IMPORT const BFTextFieldId FullTransfer;
   extern CLASS_IMPORT const BFTextFieldId RecordType;
   extern CLASS_IMPORT const BFDecimalFieldId SettledUnits;
   extern CLASS_IMPORT const BFDecimalFieldId SettledValue;
   extern CLASS_IMPORT const BFDecimalFieldId UnsettledUnits;
   extern CLASS_IMPORT const BFDecimalFieldId UnsettledValue;
   extern CLASS_IMPORT const BFDecimalFieldId FundNAV;
   extern CLASS_IMPORT const BFDecimalFieldId EstimatedAllocAmount;
   extern CLASS_IMPORT const BFNumericFieldId AccountTo;
   extern CLASS_IMPORT const BFNumericFieldId TransFeeRID;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                              // Field DD Id,         State Flags,         Group Flags 
   {ifds::FullTransfer,            BFCBO::NONE,     0}, 
   {ifds::AllowFullTransfer,       BFCBO::NONE,     0}, 
   {ifds::EstimatedAllocAmount,    BFCBO::NONE,     0}, 
   {ifds::TransFeeRID,             BFCBO::NONE,     0}, 
};

namespace CND
{
   extern const long ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL;
   extern const long ERR_TRANSFER_NOT_ALLOWED;
}


static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
TradeFromFundAlloc::TradeFromFundAlloc(BFAbstractCBO &parent) 
: FundAlloc(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);
}

//******************************************************************************
TradeFromFundAlloc::~TradeFromFundAlloc()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::initNew(const BFDataGroupId& idDataGroup,
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   setObjectNew();
   commonInit(idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initExisting"));

   attachDataObject(const_cast< BFData & >(data), false, true); 
   //because FromFundNumber doesn't come from the host
   setFundNumber (BF::HOST);
   setAllocFields (BF::HOST);
   clearUpdatedFlags (BF::HOST);
   commonInit(BF::HOST);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::commonInit(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   setFieldAllSubstituteValues(ifds::AllocAmtType, idDataGroup, 
      ifds::AmountTypeAlloc);

   DString parentAllowFullTransfer;

   //copy from parent
   getParent()->getField (ifds::AllowFullTransfer, parentAllowFullTransfer, 
      idDataGroup, false);
   if (parentAllowFullTransfer == NULL_STRING)
   {
      parentAllowFullTransfer = I_("N");
   }
   setFieldNoValidate (ifds::AllowFullTransfer, parentAllowFullTransfer, 
      idDataGroup, false, true, true, false);
   setFieldNoValidate (ifds::FullTransfer, I_("N"), idDataGroup, 
      false, true, true, true);
   setFieldNoValidate (ifds::EstimatedAllocAmount, I_("0"), 
      idDataGroup, false, true, true);
   //this will always be the from side
   setFieldNoValidate (ifds::RecordType, I_("FROM"), idDataGroup, 
      false, true, true, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TradeFromFundAlloc::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{
   FundAlloc::doInitWithDefaultValues (idDataGroup);
   if (dynamic_cast<TransactionDetails*>(getParent()->getParent()))
   {
      setFieldNoValidate(ifds::AllocAmtType, I_("D"), idDataGroup, 
         false, true, true, false);
   }
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::doApplyRelatedChanges(const BFFieldId &idField, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, 
      I_("doApplyRelatedChanges"));

   if (FundAlloc::doApplyRelatedChanges(idField, idDataGroup) <= WARNING)
   {
      //apply changes to specific fields related to this object
      if (idField == ifds::FullTransfer)
      {
         fullTransferChanges (idDataGroup);
      }
      else if (idField == ifds::AllowFullTransfer)
      {
         DString allowFullTransfer;
         
         getField(ifds::AllowFullTransfer, 
            allowFullTransfer, idDataGroup, false);
         if (allowFullTransfer == I_("N"))
         {
            setFieldNoValidate(ifds::FullTransfer, I_("N"), 
               idDataGroup, false, true, true, false); //do not apply changes
         }
         fullTransferChanges (idDataGroup);
      }
      else if (idField == ifds::EffectiveDate || 
         idField == ifds::AccountNum)
      {
         //remove the holdings list
         BFObjIter iter (*this, idDataGroup);

         iter.positionByKey(HOLDINGS_LIST);
         if (!iter.end())
         {
            iter.removeObjectFromMap (true);
         }
         //calculates the estimated amount, if it is required
         calculateEstimatedAllocAmount(idDataGroup);
      }
      else if (idField == ifds::FundClass)
      {
         //get the MFAccount object

         DString accountNum;
         MFAccount *pMFAccount;

         getField(ifds::AccountNum, accountNum, idDataGroup, false);
         if (getWorkSession().getMFAccount(idDataGroup, accountNum, 
            pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING 
            && pMFAccount)
         {
            DString fundCode, classCode, transType, tradeDate;

            getField (ifds::FundCode, fundCode, idDataGroup, false);
            getField (ifds::ClassCode, classCode, idDataGroup, false);
            getField (ifds::TransType, transType, idDataGroup, false);
            getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
            if (pMFAccount->canTradeFundClass(fundCode, classCode, 
               transType, tradeDate, idDataGroup) <= WARNING)
            {
               //calculates the estimated amount, if it is required
               //calculateEstimatedAllocAmount (idDataGroup);
               fullTransferChanges (idDataGroup);
            }
//set the from fund and class for the purpose of correctly displaying the amounts fields
            TradeFromFundAllocList *pTradeFromFundAllocList = 
               dynamic_cast<TradeFromFundAllocList *>(getParent());
            Trade *pTrade = dynamic_cast<Trade*>(getTopLevelCBO());

            if (pTrade && pTradeFromFundAllocList)
            {
               //get the right side of the transaction, and set the from fund/class on it
               TradeAcctAllocList *pAccountAllocationList = NULL;

               if (pTrade->getAccountAllocationList (pAccountAllocationList, 
                  idDataGroup, true) <= WARNING && 
                  pAccountAllocationList)
               {
                  pAccountAllocationList->setField (ifds::FromFund, 
                     fundCode, idDataGroup, false);
                  pAccountAllocationList->setField (ifds::FromClass, 
                     classCode, idDataGroup, false);
               }
            }
         }
      }
      else if (idField == ifds::AllocAmount ||
         idField == ifds::AllocAmtType)
      {
         //calculates the estimated amount, if it is required
         calculateEstimatedAllocAmount (idDataGroup);
      }
      else if (idField == ifds::EstimatedAllocAmount)
      {
         DString allowFullTransfer;
         
         getField(ifds::AllowFullTransfer, allowFullTransfer, 
            idDataGroup, false);

         if (allowFullTransfer == I_("Y"))
         {
            TradeFromFundAllocList *pTradeFromFundAllocList = 
               dynamic_cast<TradeFromFundAllocList *>(getParent());
            Trade *pTrade = dynamic_cast<Trade*>(getTopLevelCBO());

            if (pTrade && pTradeFromFundAllocList)
            {
               DString totalAmount;
            
               pTradeFromFundAllocList->getEstimatedTotalAmount (totalAmount, 
                  idDataGroup, false);
               //get the right side of the transaction, and set the amount on it
               TradeAcctAllocList *pAccountAllocationList = NULL;

               if (pTrade->getAccountAllocationList (pAccountAllocationList, 
                  idDataGroup, true) <= WARNING && 
                  pAccountAllocationList)
               {
                  pAccountAllocationList->setField (ifds::Amount, 
                     totalAmount, idDataGroup, true);
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::doValidateField(const BFFieldId &idField, 
   const DString &strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
   if (FundAlloc::doValidateField(idField, strValue, idDataGroup) > WARNING)
   {
      //remove some of the conditions that are not to be raised here, 
      //when full transfer is allowed
      DString allowFullTransfer;

      getField (ifds::AllowFullTransfer, 
         allowFullTransfer, idDataGroup, false);
      
      if (allowFullTransfer == I_("Y"))
      {
         if (idField == ifds::AllocAmount)
         {
            clearAllocCondition ( MYFRAME(),
               CND::ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::copyDataFromParent(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("copyDataFromParent"));
   BFCBO* pBFCBO = getTopLevelCBO();
   DString strTemp;

   if (dynamic_cast<Trade*>(pBFCBO))
   {
      pBFCBO->getField (ifds::AccountNum, strTemp, idDataGroup, false);
      setFieldNoValidate (ifds::AccountNum, strTemp, idDataGroup, false, false);
      pBFCBO->getField (ifds::TransSeq, strTemp, idDataGroup, false);
      setFieldNoValidate (ifds::TransSeq, strTemp, idDataGroup, false, false);
      pBFCBO->getField (ifds::FromFund, strTemp, idDataGroup, false);
      setFieldNoValidate (ifds::FundCode, strTemp, idDataGroup, false, false);
      pBFCBO->getField (ifds::FromClass, strTemp, idDataGroup, false);
      setFieldNoValidate (ifds::ClassCode, strTemp, idDataGroup, false, false);
   }
   else /*if (dynamic_cast<PendingTradeDetails*>(pBFCBO))*/
   {
      pBFCBO->getField (ifds::AccountNum, strTemp, idDataGroup, false);
      setFieldNoValidate (ifds::AccountNum, strTemp, idDataGroup, false, false);
      pBFCBO->getField (ifds::rxFundCode, strTemp, idDataGroup, false);
      setFieldNoValidate(ifds::FundCode, strTemp, idDataGroup, false, false);
      pBFCBO->getField (ifds::rxClassCode, strTemp, idDataGroup, false);
      setFieldNoValidate(ifds::ClassCode, strTemp, BF::HOST, false, false);
      pBFCBO->getField (ifds::SettleCurrency, strTemp, BF::HOST, false);
      setFieldNoValidate(ifds::SettleCurrency, strTemp, BF::HOST, false, false);
   }
   setFundNumber(idDataGroup);

   DString allowFullTransfer;

   getField (ifds::AllowFullTransfer, allowFullTransfer, idDataGroup, false);   
   if (allowFullTransfer == I_("N"))
   {
      setField (ifds::AllocPercentage, I_("100"), idDataGroup, false);
   }
   else if (dynamic_cast<Trade*>(pBFCBO))
   {
      DString fullTransfer;
      BFCBO* parent = getParent();

      if (parent)
      {
         BFObjIter iter (*parent, idDataGroup);

         pBFCBO->getField (ifds::FullTransfer, fullTransfer, idDataGroup, false);
         if (iter.getNumberOfItemsInList() <= 1 && fullTransfer == I_("Y"))
         {
            setFieldNoValidate (ifds::FullTransfer, I_("Y"), idDataGroup, 
               false, true, true, true);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::getFundNAV (double &dFundNAV, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getNAV "));

   //get the current bussiness date and effective date
   DString currBusDate, effectiveDate,
         fundCode, classCode;

   getField(ifds::FundCode, fundCode, idDataGroup, false);
   getField(ifds::ClassCode, classCode, idDataGroup, false);
   dFundNAV = 0.0;

   //get NAV from the account holdings
   MFAccountHoldingList* pHoldingList = NULL;

   if (getHoldings (pHoldingList, idDataGroup) <= WARNING && pHoldingList)
   {
      BFObjIter iter(*pHoldingList, idDataGroup, true, 
         BFObjIter::ITERTYPE::NON_DELETED);
      //walk the list, match the fund and class, 
      //and retrive the number of units

      BFData matchCriteria;

      matchCriteria.setElementValue(ifds::rxFundCode, fundCode, true);
      matchCriteria.setElementValue(ifds::rxClassCode, classCode, true);
      iter.positionOnNextMatch(matchCriteria, idDataGroup);
      if (!iter.end())
      {
         DString fundNAV;
         
         iter.getObject()->getField(ifds::FundNAV, fundNAV, idDataGroup, false);
         dFundNAV = DSTCommonFunctions::convertToDouble(fundNAV);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::getNumberOfUnits (double &dAvalUnits, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getNumberOfUnits"));
   
   MFAccountHoldingList* pHoldingList = NULL;

   dAvalUnits = 0.0;
   if (getHoldings (pHoldingList, idDataGroup) <= WARNING && pHoldingList)
   {
      BFObjIter iter(*pHoldingList, idDataGroup, true, 
         BFObjIter::ITERTYPE::NON_DELETED);
      //walk the list, match the fund and class, 
      //and retrive the number of units
      DString fundCode, classCode;

      getField(ifds::FundCode, fundCode, idDataGroup, false);
      getField(ifds::ClassCode, classCode, idDataGroup, false);

      BFData matchCriteria;

      matchCriteria.setElementValue(ifds::rxFundCode, fundCode, true);
      matchCriteria.setElementValue(ifds::rxClassCode, classCode, true);
      iter.positionOnNextMatch(matchCriteria, idDataGroup);
      if (!iter.end())
      {
         DString units;
         //get the settled and unsettled units
         iter.getObject()->getField(ifds::SettledUnits, units, idDataGroup, false);
         dAvalUnits += DSTCommonFunctions::convertToDouble(units);
         iter.getObject()->getField(ifds::UnsettledUnits, units, idDataGroup, false);
         dAvalUnits += DSTCommonFunctions::convertToDouble(units);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::getNumberOfUnits (DString &dstrAvalUnits, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getNumberOfUnits"));
   
   double dAvalUnits = 0.0;
   if (getNumberOfUnits (dAvalUnits, idDataGroup) <= WARNING)
   {
      dstrAvalUnits = DSTCommonFunctions::doubleToDString(ifds::AllocAmount, 
         dAvalUnits);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::getBalance(double &dBalance, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBalance"));
   
   MFAccountHoldingList* pHoldingList = NULL;

   dBalance = 0.0;
   if (getHoldings (pHoldingList, idDataGroup) <= WARNING && pHoldingList)
   {
      BFObjIter iter(*pHoldingList, idDataGroup, true, 
         BFObjIter::ITERTYPE::NON_DELETED);
      //walk the list, match the fund and class, 
      //and retrive the balance
      DString fundCode, classCode;

      getField(ifds::FundCode, fundCode, idDataGroup, false);
      getField(ifds::ClassCode, classCode, idDataGroup, false);

      BFData matchCriteria;

      matchCriteria.setElementValue(ifds::rxFundCode, fundCode, true);
      matchCriteria.setElementValue(ifds::rxClassCode, classCode, true);
      iter.positionOnNextMatch(matchCriteria, idDataGroup);
      if (!iter.end())
      {
         DString balance;
         //get the settled and unsettled balance
         iter.getObject()->getField(ifds::SettledValue, balance, idDataGroup, false);
         dBalance += DSTCommonFunctions::convertToDouble(balance);
         iter.getObject()->getField(ifds::UnsettledValue, balance, idDataGroup, false);
         dBalance += DSTCommonFunctions::convertToDouble(balance);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::getBalance(DString &dstrBalance, 
   const BFDataGroupId& idDataGroup)
{   
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBalance"));
   double dblBalance = 0.0;

   if (getBalance (dblBalance, idDataGroup) <= WARNING)
   {
      dstrBalance = DSTCommonFunctions::doubleToDString(ifds::AllocAmount, dblBalance);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::getHoldings(MFAccountHoldingList *&pHoldingList, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getHoldings"));
   pHoldingList = dynamic_cast<MFAccountHoldingList*>(
      getObject(HOLDINGS_LIST, idDataGroup));

   if (!pHoldingList)
   {
      DString accountNum, effectiveDate;

      getField(ifds::AccountNum, accountNum, idDataGroup);
      getField(ifds::EffectiveDate, effectiveDate, idDataGroup);
      pHoldingList = new MFAccountHoldingList(*this);
      if (pHoldingList->init (accountNum, effectiveDate, NULL_STRING, NULL_STRING) <= WARNING)
      {
         setObject (pHoldingList, HOLDINGS_LIST,OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pHoldingList;
         pHoldingList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::calculateEstimatedAllocAmount(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("calculateEstimatedAllocAmount"));

   DString allowFullTransfer;

   getField (ifds::AllowFullTransfer, allowFullTransfer, idDataGroup, false);
   if (allowFullTransfer == I_("Y"))
   {
      DString amtType, estimatedAllocAmount;

      getField (ifds::AllocAmtType, amtType, idDataGroup, false);
      getField (ifds::AllocAmount, estimatedAllocAmount, idDataGroup, false);
   
      double dAmount = DSTCommonFunctions::convertToDouble (estimatedAllocAmount),
         dFundNAV = 0.0;

      if (amtType == I_("D")) //dollar amount
      {
         //do nothing...
      }
      else if (amtType == I_("U")) //units
      {
         if (getFundNAV (dFundNAV, idDataGroup) <= WARNING)
         {
            //multiply the units stored in the AllocAmount field 
            //with the price per unit
            estimatedAllocAmount = 
               DSTCommonFunctions::doubleToDString(ifds::AllocAmount, 
               dAmount * dFundNAV);
         }
      }
      else if (amtType == I_("P")) //percentage
      {
         double dAvalUnits = 0.0;

         //find the number of available units and find the NAV, of this fund 
         //then multiple by the number of units and percentage, 
         //and this is the estimated amount
         if (getNumberOfUnits (dAvalUnits, idDataGroup) <= WARNING && 
            getFundNAV (dFundNAV, idDataGroup) <= WARNING)
         {
            estimatedAllocAmount = DSTCommonFunctions::doubleToDString(
               ifds::AllocAmount, dAmount / 100 * dAvalUnits * dFundNAV);
         }
      }
      setFieldNoValidate (ifds::EstimatedAllocAmount, 
         estimatedAllocAmount, idDataGroup, false, true, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAlloc::fullTransferChanges (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("fullTransferChanges"));

   DString allowFullTransfer, fullTransfer, allocAmtType;

   getField (ifds::AllowFullTransfer, allowFullTransfer, idDataGroup, false);   
   getField (ifds::FullTransfer, fullTransfer, idDataGroup, false);
   getParent()->getField (ifds::AllocAmtType, 
      allocAmtType, idDataGroup, false);   
   if (allowFullTransfer == I_("Y"))
   {
      setFieldReadOnly (ifds::AllocPercentage, idDataGroup, true);
      setFieldNoValidate (ifds::AllocPercentage, I_("0.0"), idDataGroup, 
         false, true, true);
      if (fullTransfer == I_("Y"))
      {
   
         DString amtType, allocAmount;

         getField(ifds::AllocAmtType, amtType, idDataGroup, false);
         if (amtType == I_("D")) //dollars
         {
            //get the full balance of the fund
            getBalance (allocAmount, idDataGroup);
         }
         else if (amtType == I_("U")) //units
         {
            //get the number of units of the fund
            getNumberOfUnits (allocAmount, idDataGroup);
         }
         else if (amtType == I_("P"))
         {
            allocAmount = I_("100");
         }
         setFieldNoValidate (ifds::AllocAmount, allocAmount, idDataGroup, 
            false, true, true, false);
         setFieldReadOnly (ifds::AllocAmount, idDataGroup, true);
         setFieldReadOnly (ifds::AllocAmtType, idDataGroup, true);
      }
      else 
      {
         //do not know whay we have to do this here,...
         setFieldAllSubstituteValues(ifds::AllocAmtType, idDataGroup, 
            ifds::AmountTypeAlloc);
         setFieldReadOnly (ifds::AllocAmount, idDataGroup, false);
         setFieldReadOnly (ifds::AllocAmtType, idDataGroup, false);
      }
      calculateEstimatedAllocAmount (idDataGroup);
   }
   else
   {
      if (fullTransfer == I_("N"))
      {
         setFieldAllSubstituteValues (ifds::AllocAmtType, idDataGroup, 
            ifds::AmountTypeAlloc);
         setFieldReadOnly (ifds::AllocAmount, idDataGroup, false);
         setFieldReadOnly (ifds::AllocPercentage, idDataGroup, false);
         if (dynamic_cast<Trade*> (getParent()->getParent()))
         {
            //copy from parent
            setFieldNoValidate (ifds::AllocAmtType, allocAmtType, idDataGroup, 
               false, true, true, false);
         }
         setFieldReadOnly (ifds::AllocAmtType, idDataGroup, true);
         setFieldNoValidate (ifds::EstimatedAllocAmount, I_("0"), 
            idDataGroup, false, true, true);
      }
      else
      {
         assert (0);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TradeFromFundAlloc::clearAllocCondition (Frame *pFrame, int conditionCode)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("clearCondition"));

   int count = pFrame->getCount();
   for (int i = 0; i < count; i++)
   {
      Condition *c = pFrame->getCondition(i);
      int condCode = c->getCode();

      if(condCode == conditionCode)
      {
         pFrame->clearCondition(i);
         break;
      }
   }         
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeFromFundAlloc.cpp-arc  $
// 
//    Rev 1.11   Oct 13 2005 18:20:10   popescu
// BPS Performance issue - cached view call 20 and passed params fund/class in as params
// 
//    Rev 1.10   Nov 14 2004 14:57:52   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Feb 17 2004 17:17:14   popescu
// PTS 10023292, Multiple Fund Transfers, Units vs Amounts display; made sure that both sides of the transfer/exchange are looking at the same fund, in order to display the amount values
// 
//    Rev 1.8   Jan 19 2004 17:43:28   popescu
// PTS 10026204, 
// Preserve the state of the Full Transfer flag
// 
//    Rev 1.7   Jan 05 2004 16:32:50   popescu
// PTS 10025748, in case of a 'Full Transfer' of the From Side Multi Fund Allocation, set the amount of transaction to the To side. Before it was wrongly set to zero.
// 
//    Rev 1.6   Nov 04 2003 11:40:10   popescu
// PTS 10023203, Transaction History allocation issues for multi fund allocation, desktop not sending a request for FROM records
// 
//    Rev 1.5   Oct 28 2003 12:40:06   popescu
// PTS 10023292, display issues of decimal fields
// 
//    Rev 1.4   Sep 12 2003 10:44:10   popescu
// PET809, FN02 CIBC multi fund transfer
// Moved the cross objects validation between FromFundList and ToFundList from the process layer to the CBO layer, and since the Trade object owns both lists, the most logical place to put the validation seemed to be doValidateAll method of the Trade object
// 
//    Rev 1.3   Sep 08 2003 17:11:10   popescu
// PET 809_FN_02, fixes after performing integrated unit testing with the view team
// 
//    Rev 1.2   Sep 05 2003 18:29:28   popescu
// PET809_FN02, fixex
// 
//    Rev 1.1   Sep 01 2003 21:32:38   popescu
// PET 809, FN 02 CIBC Multi Fund Transfer
// 
//    Rev 1.0   Aug 13 2003 20:12:26   popescu
// Initial revision.
 */