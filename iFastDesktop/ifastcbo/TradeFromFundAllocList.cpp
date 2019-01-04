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
// ^FILE   : TradeFromFundAllocList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2003
//
// ^CLASS    : TradeFromFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "funddetail.hpp"
#include "trade.hpp"
#include "tradeacctalloclist.hpp"
#include "tradefromfundalloc.hpp"
#include "tradefromfundalloclist.hpp"
#include "pendingtradedetails.hpp"
#include "transactiondetails.hpp"
#include <ifastdataimpl\dse_dstc0060_req.hpp>
#include <ifastdataimpl\dse_dstc0060_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PT_ALLOCATIONS;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("TradeFromFundAllocList");
}


namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId AllowFullTransfer;
   extern CLASS_IMPORT const BFTextFieldId FullTransfer;
   extern CLASS_IMPORT const BFTextFieldId AmtType;
   extern CLASS_IMPORT const BFDecimalFieldId EstimatedAllocAmount;
   extern CLASS_IMPORT const BFTextFieldId FromClass;
   extern CLASS_IMPORT const BFTextFieldId FromFund;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                              //  Field DD Id,        State Flags,   Group Flags 
   {ifds::AccountNum,        BFCBO::NONE,   0}, 
   {ifds::Amount,            BFCBO::NONE,   0},
   {ifds::AllowFullTransfer, BFCBO::NONE,   0},
   {ifds::AllocPercentage,   BFCBO::NONE,   0},
   {ifds::AllocAmtType,      BFCBO::NONE,   0},
};

namespace CND
{
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
   extern const long ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL;
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
TradeFromFundAllocList::TradeFromFundAllocList(BFAbstractCBO &parent) : 
   FundAllocList(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
}

//******************************************************************************
TradeFromFundAllocList::~TradeFromFundAllocList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY TradeFromFundAllocList::initNew (
   const BFDataGroupId &idDataGroup, 
   const DString& dstrTrack /*= I_("N")*/,
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   FundAllocList::initNew(idDataGroup, false, dstrTrack, dstrPageName);

   commonInit (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAllocList::initExisting(const DString &dstrTrack,
   const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initExisting"));

   BFCBO* pCBO = getTopLevelCBO();
   DString accountNum, 
      transNum, 
      tradeDate, 
      mgmtCoIdOut;
   
   setListFields(BF::HOST);
   pCBO->getField(ifds::AccountNum, accountNum, BF::HOST, true);
   pCBO->getField(ifds::TransNum, transNum, BF::HOST, true);
   if (dynamic_cast<TransactionDetails*>(pCBO))
   {
      pCBO->getField(ifds::TradeDate, tradeDate, BF::HOST, true);
   }
   else
   {
      pCBO->getField(ifds::EffectiveDate, tradeDate, BF::HOST, true);
   }

   assert (!accountNum.strip().empty());
   assert (!transNum.strip().empty());
   assert (!tradeDate.strip().empty());
   
   BFData requestData(ifds::DSTC0060_REQ);
   
   requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
   requestData.setElementValue(ifds::AccountNum, accountNum);
   requestData.setElementValue(ifds::TransNum, transNum); 
   requestData.setElementValue(ifds::TradeDate, tradeDate);
   requestData.setElementValue(ifds::RecordType, I_("FROM"));
   requestData.setElementValue(ifds::NextKey, NULL_STRING);   
   requestData.setElementValue(ifds::Track, dstrTrack);
   requestData.setElementValue(ifds::Activity, dstrPageName);
   //call the back-end
   if (ReceiveData(DSTC_REQUEST::PT_ALLOCATIONS, requestData, 
      ifds::DSTC0060_VW, DSTCRequestor(getSecurity(), true, true)) > WARNING)
   {
      DString fromFund, fromClass;

      if (dynamic_cast<Trade*>(pCBO))
      {
         pCBO->getField (ifds::FromFund, fromFund, BF::HOST, false);
         pCBO->getField (ifds::FromClass, fromClass, BF::HOST, false);
      }
      else
      {
         pCBO->getField (ifds::rxFundCode, fromFund, BF::HOST, false);
         pCBO->getField (ifds::rxClassCode, fromClass, BF::HOST, false);
      }
      if (fromFund.stripAll() != NULL_STRING && 
         fromFund.stripAll() != NULL_STRING)
      {
         //add a fake record, if the codition is data not found 
         int count = CONDITIONCOUNT();
         Condition *c = NULL;

         for (int i = 0; i < count; i++)
         {
            c = GETCONDITION(i);
            int condCode = c->getCode();
            if (condCode == CND::ERR_DATA_NOT_FOUND)
            {
               CLEARCONDITION(i)
               //add the fake record
               addNewAllocation(NULL_STRING, BF::HOST, false, true, false);
            }
         }
      }
   }
   commonInit(BF::HOST);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAllocList::commonInit(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   BFCBO* pCBO = getTopLevelCBO();

   if (idDataGroup != BF::HOST)
   {
      DString fromFund, 
         fromClass;
      Trade *pTrade = dynamic_cast<Trade*>(pCBO);

      if (pTrade)
      {
         pTrade->getField (ifds::FromFund, fromFund, 
            idDataGroup, false);
         pTrade->getField (ifds::FromClass, fromClass, 
            idDataGroup, false);
         if (fromFund != NULL_STRING && fromClass != NULL_STRING)
         {
            TradeAcctAllocList *pAccountAllocationList = NULL;

            if (pTrade->getAccountAllocationList (pAccountAllocationList, 
               idDataGroup, true) <= WARNING && 
               pAccountAllocationList)
            {
               pAccountAllocationList->setField (ifds::FromFund, 
                  fromFund, idDataGroup, false);
               pAccountAllocationList->setField (ifds::FromClass, 
                  fromClass, idDataGroup, false);
            }
         }
      }
   }
   setAllowFullTransfer(idDataGroup);
   //total percentage at the 'account alloc level'
   setField (ifds::AllocPercentage, I_("100"), 
      idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAllocList::doCreateNewObject(BFCBO *&pBase, 
   DString &strKey, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   TradeFromFundAlloc *pTradeFromFundAlloc = new TradeFromFundAlloc(*this);
   
   pTradeFromFundAlloc->initNew(idDataGroup);
   pBase = pTradeFromFundAlloc;
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY TradeFromFundAllocList::doCreateObject(const BFData &data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   TradeFromFundAlloc *pTradeFromFundAlloc = new TradeFromFundAlloc(*this);

   pTradeFromFundAlloc->initExisting(data);
   pObjOut = pTradeFromFundAlloc;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAllocList::doDeleteObject (const DString &strKey, 
      const BFDataGroupId &idDataGroup, bool bIsObjectDestroyed)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doDeleteObject"));
   DString allowFullTransfer;
   
   getField (ifds::AllowFullTransfer, allowFullTransfer, 
      idDataGroup, false);

   if (allowFullTransfer == I_("Y"))
   {
      Trade *pTrade = dynamic_cast<Trade*>(getTopLevelCBO());

      if (pTrade)
      {
         DString totalAmount;
      
         //skip the key that it's being deleted
         getEstimatedTotalAmount (totalAmount, idDataGroup, false, strKey);
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
   return GETCURRENTHIGHESTSEVERITY();
}


//********************************************************************
SEVERITY TradeFromFundAllocList::doValidateAll(const BFDataGroupId& idDataGroup, 
   long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   if (FundAllocList::doValidateAll(idDataGroup, lValidateGroup) > WARNING)
   {
      //remove some of the conditions that are not to be raised here, 
      //when full transfer is allowed
      DString allowFullTransfer;

      getField (ifds::AllowFullTransfer, allowFullTransfer, idDataGroup, false);
      
      if (allowFullTransfer == I_("Y"))
      {
         clearAllocCondition (MYFRAME(), CND::ERR_SUM_OF_PERCENTAGES_NOT_100);
         clearAllocCondition (MYFRAME(), CND::ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL);
      }
   }
   //for non multicurrency env., 
   //issue an error if not all the currencies are the same
   if (!isMultiCurrency())
   {
      validateMulticurrency(idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY TradeFromFundAllocList::addNewAllocation(const DString& strKey, 
   const BFDataGroupId& idDataGroup, bool bGetDefault,
   bool bCopyParent, bool bAddChildren)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("addNewAllocation"));

   BFObjectKey objKey(strKey, idDataGroup);

   TradeFromFundAlloc *pTradeFromFundAlloc = 
      dynamic_cast<TradeFromFundAlloc *>(getNewListItem(objKey));
   
   if (bCopyParent)
   {
      pTradeFromFundAlloc->copyDataFromParent(idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAllocList::doApplyRelatedChanges(const BFFieldId& idField, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
   if (FundAllocList::doApplyRelatedChanges(idField, idDataGroup) <= WARNING)
   {
      if (idField == ifds::Amount)
      {
         setAllowFullTransfer(idDataGroup);
      }
      else if (idField == ifds::AllowFullTransfer)
      {
         DString allowFullTransfer;

         getField(ifds::AllowFullTransfer, 
            allowFullTransfer, idDataGroup, false);

         BFObjIter iter(*this, idDataGroup, false, 
            BFObjIter::ITERTYPE::NON_DELETED);

         while (!iter.end())
         {
            iter.getObject()->setField(ifds::AllowFullTransfer, 
               allowFullTransfer, idDataGroup, false, true, true);
            ++iter;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeFromFundAllocList::getEstimatedTotalAmount (DString &totalEstimatedAmount, 
   const BFDataGroupId& idDataGroup, bool bFormatted, const DString &skipKey /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEstimatedTotalAmount"));
   
   double dTotal = 0.0;
   BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end())
   {
      if (iter.getStringKey() != skipKey)
      {
         DString estimatedAllocAmount;
         double dEstimatedAllocAmount;

         iter.getObject()->getField (ifds::EstimatedAllocAmount, estimatedAllocAmount,
            idDataGroup, false);
         dEstimatedAllocAmount = 
            DSTCommonFunctions::convertToDouble (estimatedAllocAmount);
         dTotal += dEstimatedAllocAmount;
      }
      ++iter;
   }
   totalEstimatedAmount = DSTCommonFunctions::doubleToDString(
      ifds::EstimatedAllocAmount, dTotal);
   if (bFormatted)
   {
      getFormattedAmount (idDataGroup, totalEstimatedAmount);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFromFundAllocList::setAllowFullTransfer (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAllowFullTransfer"));

   BFCBO* pBFCBO = getTopLevelCBO();

   if (dynamic_cast<Trade*>(pBFCBO))
   {
      DString amount, amtType;

      pBFCBO->getField (ifds::Amount, amount, idDataGroup, false);
      pBFCBO->getField (ifds::AmtType, amtType, idDataGroup, false);

      double dAmount = DSTCommonFunctions::convertToDouble (amount);
      bool bAllow = dAmount <= 0.0 && amtType == I_("D");

      setFieldNoValidate(ifds::AllowFullTransfer, 
         bAllow ? I_("Y") : I_("N"), idDataGroup, false, true, true, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TradeFromFundAllocList::getFormattedAmount (
   const BFDataGroupId &idDataGroup, 
   DString &dstrValue)
{
   DString unitsPrecision, 
      fundCode, 
      classCode, 
      amountType;

   getField (ifds::AllocAmtType, amountType, idDataGroup, false);

//format the amount based on one fund in the list
   BFObjIter iter (*this, idDataGroup);

   if (!iter.end())
   {
      iter.getObject()->getField (ifds::FundCode, fundCode, idDataGroup, false);
      fundCode.strip().upperCase();
      iter.getObject()->getField (ifds::ClassCode, classCode, idDataGroup, false);
      classCode.strip().upperCase();
   }
   
   FundDetail *pFundDetail = NULL;

   if (getFundDetail (fundCode, classCode, pFundDetail) <= WARNING && pFundDetail)
   {
      if (amountType.strip() != I_("U"))
      {
         DString currency;
         
         pFundDetail->getField (ifds::Currency, currency, BF::HOST, false);
         CurrencyClass::getFormattedValue (getWorkSession(), dstrValue, currency, amountType);
      }
      else
      {
         int iUnitsPrecision = 0;

         pFundDetail->getField (ifds::UnitsPrecision, unitsPrecision, BF::HOST, false);
         iUnitsPrecision = unitsPrecision.asInteger(); 
         const BFFieldId &fieldId = ifds::USDollar;
         DSTCommonFunctions::formattedField (fieldId, iUnitsPrecision, dstrValue); 
      }
   }
}

//******************************************************************************
void TradeFromFundAllocList::clearAllocCondition (Frame *pFrame, int conditionCode)
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeFromFundAllocList.cpp-arc  $
// 
//    Rev 1.10   Nov 14 2004 14:57:54   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Feb 24 2004 16:31:14   popescu
// PTS 10023292 wrong parameter sent to CurrencyClass::getFormattedValue method
// 
//    Rev 1.8   Feb 17 2004 17:17:20   popescu
// PTS 10023292, Multiple Fund Transfers, Units vs Amounts display; made sure that both sides of the transfer/exchange are looking at the same fund, in order to display the amount values
// 
//    Rev 1.7   Jan 19 2004 17:43:30   popescu
// PTS 10026204, 
// Preserve the state of the Full Transfer flag
// 
//    Rev 1.6   Jan 05 2004 16:32:56   popescu
// PTS 10025748, in case of a 'Full Transfer' of the From Side Multi Fund Allocation, set the amount of transaction to the To side. Before it was wrongly set to zero.
// 
//    Rev 1.5   Nov 04 2003 11:40:18   popescu
// PTS 10023203, Transaction History allocation issues for multi fund allocation, desktop not sending a request for FROM records
// 
//    Rev 1.4   Oct 28 2003 12:40:12   popescu
// PTS 10023292, display issues of decimal fields
// 
//    Rev 1.3   Sep 08 2003 17:11:12   popescu
// PET 809_FN_02, fixes after performing integrated unit testing with the view team
// 
//    Rev 1.2   Sep 01 2003 21:32:40   popescu
// PET 809, FN 02 CIBC Multi Fund Transfer
// 
//    Rev 1.1   Aug 15 2003 11:31:40   popescu
// fixed comp error
// 
//    Rev 1.0   Aug 13 2003 20:12:42   popescu
// Initial revision.
 */