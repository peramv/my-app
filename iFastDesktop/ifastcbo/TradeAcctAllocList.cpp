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
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : TradeAcctAllocList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/04/02
//
// ^CLASS    : TradeAcctAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Trade, PendingTradeDetails and TransactionDetails account allocation list
//
//******************************************************************************
#include "stdafx.h"
#include "amsmstrlist.hpp"
#include "defacctalloclist.hpp"
#include "mfaccount.hpp"
#include "pendingtradedetails.hpp"
#include "transactiondetails.hpp"
#include "trade.hpp"
#include "tradeacctalloc.hpp"
#include "tradeacctalloclist.hpp"
#include "tradefundalloclist.hpp"
#include <ifastdataimpl\dse_dstc0060_vw.hpp>
#include <ifastdataimpl\dse_dstc0060_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME  = I_("TradeAcctAllocList");

}

namespace CND
{
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId TradesTransType;
   extern CLASS_IMPORT const BFTextFieldId AmtType;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFTextFieldId FromFund;
   extern CLASS_IMPORT const BFTextFieldId FromClass;
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFNumericFieldId AccountTo;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFTextFieldId DefaultAlloc;
   extern CLASS_IMPORT const BFTextFieldId FundAlloc;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PT_ALLOCATIONS;
}
namespace 
{
   const I_CHAR * const UNITS    = I_("U");       // amount type
   const I_CHAR * const RB_TYPE  = I_("RB");
   const I_CHAR * const YES      = I_("Y");
   const I_CHAR * const NO       = I_("N");

}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const ALL_FUND_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT_2;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE;  
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const ONE_SIDE_TRADE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,      Group Flags 
   {ifds::Amount,          BFCBO::NONE,             0}, 
   {ifds::EffectiveDate,   BFCBO::NONE,             0}, 
   {ifds::TransNum,        BFCBO::NONE,             0}, 
   
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
TradeAcctAllocList::TradeAcctAllocList(BFAbstractCBO &parent) 
: AcctAllocList(parent), _pView60Data(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   setObjectAsList();
}

//******************************************************************************
TradeAcctAllocList::~TradeAcctAllocList(void)
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pView60Data)
   {
      delete _pView60Data;
      _pView60Data = NULL;
   }
}

//******************************************************************************
SEVERITY TradeAcctAllocList::initNew(const BFDataGroupId& idDataGroup, bool bGetDefault, 
   const DString& dstrTrack, const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   _dstrTrack = dstrTrack;
   _dstrActivity = dstrPageName;

   AcctAllocList::initNew(idDataGroup, bGetDefault, dstrTrack, dstrPageName);
   
   DString str;
   BFCBO *pTrade = getTopLevelCBO();

   setFieldFromCBO(pTrade, ifds::TradesTransType, ifds::TransType, idDataGroup, str);
   if (str.strip() == TRADETYPE::TRANSFER)
   {
      setFieldFromCBO (pTrade, ifds::AccountTo, ifds::AccountNum, idDataGroup, str);
   }
   else
   {
      setFieldFromCBO (pTrade, ifds::AccountNum, ifds::AccountNum, idDataGroup, str);
   }
   setFieldFromCBO (pTrade, ifds::AmtType, ifds::AllocAmtType, idDataGroup, str);

   if (bGetDefault)
   {
      TradeAcctAlloc *pTradeAccAlloc = NULL;

      initDefaultAllocationList (pTradeAccAlloc, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeAcctAllocList::initExisting(const DString& dstrTrack,
   const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initExisting"));

   _dstrTrack = dstrTrack;
   _dstrActivity = dstrPageName;
   DString dstrKey, mgmtCoIdOut, strAccountNum, strTransNum, strTradeDate, strTransCode, str;

   //if the allocation belongs to a PendingTrade or TransactionDetails, the AccountNum field has been already set in
   //if the allocation belongs to a trade	we always need AccountNum from Trade to call view 60 but
   //we need to keep AccountTo from Trade if it is a Transfer and AccountNum for every other trans type
   BFCBO* pCBO = getTopLevelCBO();
   Trade* pTrade = dynamic_cast<Trade*>(pCBO);
   if(pTrade)
   {
      pCBO->getField(ifds::AccountNum, strAccountNum, BF::HOST, false);
      pCBO->getField(ifds::TradesTransType, str, BF::HOST, false);
      if(str.strip() == TRADETYPE::TRANSFER  || 
         str == TRADETYPE::ALL_FUND_TRANSFER || 
         str == TRADETYPE::TRANSFER_OUT_2    ||
         str == TRADETYPE::TRANSFER_OUT)
      {
         setFieldFromCBO(pCBO, ifds::AccountTo, ifds::AccountNum, BF::HOST, str);
      }
      else
      {
         setFieldFromCBO(pCBO, ifds::AccountNum, ifds::AccountNum, BF::HOST, str);
      }
   }
   else if (pCBO)//PendingTrade or TransactionDetails
   {
      getField(ifds::AccountNum, strAccountNum, BF::HOST, false);
      if (strAccountNum.empty())
      {
         pCBO->getField(ifds::AccountNum, strAccountNum, BF::HOST, false);
         setFieldFromCBO(pCBO, ifds::AccountNum, ifds::AccountNum, BF::HOST, str);
      }
   }
   setListFields (BF::HOST);
   setFieldFromCBO (pCBO, ifds::TransNum, ifds::TransNum, BF::HOST, strTransNum);
   getField(ifds::EffectiveDate, strTradeDate, BF::HOST, true);
   assert (!strAccountNum.strip().empty());
   assert (!strTransNum.strip().empty());
   assert (!strTradeDate.strip().empty());
   _pView60Data = new BFData(ifds::DSTC0060_VW);
   
   BFData requestData(ifds::DSTC0060_REQ);
   
   requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
   requestData.setElementValue(ifds::AccountNum, strAccountNum );
   requestData.setElementValue(ifds::TransNum, strTransNum); 
   requestData.setElementValue(ifds::TradeDate, strTradeDate);
   requestData.setElementValue(ifds::RecordType, I_("TO"));
   requestData.setElementValue(ifds::NextKey, NULL_STRING);   
   requestData.setElementValue(ifds::Track, dstrTrack);
   requestData.setElementValue(ifds::Activity, dstrPageName);

   if(BFDataBroker::getInstance()->receive(DSTC_REQUEST::PT_ALLOCATIONS, 
      requestData, *_pView60Data, DSTCRequestor(getSecurity(), true)) > WARNING)
   {
      delete _pView60Data;
      _pView60Data = NULL;
      return GETCURRENTHIGHESTSEVERITY();
   }

   std::set< DString > accountNum;
   int cRepeats = _pView60Data->getRepeatCount();

   if (0 != cRepeats)
   {
      for (int i = 0; i < cRepeats; i++)
      {
         const BFData &data = _pView60Data->getRepeat(i);
         DString dstrAccountNum = data.getElementValue(ifds::AccountNum);

         dstrAccountNum.strip().stripLeading('0');
         if (accountNum.insert(dstrAccountNum).second)
         {
            TradeAcctAlloc *accountAllocation = new TradeAcctAlloc(*this);
            DString dstrKey;
            
            getStrKey(dstrKey, &data);
            assert(!dstrKey.empty());
            setObject(accountAllocation, dstrKey, OBJ_ACTIVITY_NONE, BF::HOST);
            accountAllocation->initExisting(data);
         }
      }
   }
   else
   {
      //either we called initExisting() when Allocation field for this transaction was NO
      //or the view returned 'No data found' when the Allocation field in view 54 or 22 is actually YES
      //they both should never happen
      //assert(0);
      
      //this looks like a hack, do not add it yet (SP)
      //if (initNew(BF::HOST, false) <= WARNING)//don't pick up the default allocations here
      DString accountNum_;

      getField (ifds::AccountNum, accountNum_, BF::HOST);
      addExistingAllocation(accountNum_, BF::HOST);      
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeAcctAllocList::addNewAllocation (const DString& strKey, 
   const BFDataGroupId& idDataGroup, bool bGetDefault, bool bCopyParent,
   bool bAddChildren)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("addNewAllocation"));
   assert(!(bGetDefault & bCopyParent));//can't be both true
   BFObjectKey objKey(strKey, idDataGroup);
   DString strKeyCopy(strKey);
   if(!strKeyCopy.strip().empty())
      m_strKeyForNewItem = strKey;
   TradeAcctAlloc * pNewTradeAcctAlloc = dynamic_cast<TradeAcctAlloc*>(getNewListItem(objKey));
   m_strKeyForNewItem = NULL_STRING;

   //the key is the AccountNum
   DString strAccountNum(strKey),strAmount(NULL_STRING) ;
   if(strAccountNum.strip().stripLeading('0') != NULL_STRING)
      pNewTradeAcctAlloc->setField(ifds::AccountNum, strAccountNum, idDataGroup, false);

   if(bCopyParent)
   {
      pNewTradeAcctAlloc->copyDataFromParent(idDataGroup);
   }
   if(bAddChildren)
   {
      assert(pNewTradeAcctAlloc);
      TradeFundAllocList *pFundAllocList;
      pNewTradeAcctAlloc->getFundAllocationList(pFundAllocList, idDataGroup, true, bGetDefault);//this will set the amount, too
      //if there is no allocation in the list, we have to add the 100% alloc
      BFObjIter iter(*pFundAllocList, idDataGroup);
      int nNbrOfAlloc = iter.getNumberOfItemsInList();
      if(nNbrOfAlloc == 0)//no default alloc; have to copy parent data
         pFundAllocList->addNewAllocation(NULL_STRING, idDataGroup, false, true, bAddChildren);//this will set the amount, too
   }
   //set the amount, if it hasn't already been picked up
   if(!bCopyParent && !bAddChildren)
   {
      getTopLevelCBO()->getField(ifds::Amount, strAmount, idDataGroup, false);
      setField(ifds::Amount, strAmount, idDataGroup, false);
   }
   clearUpdatedFlags( idDataGroup, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeAcctAllocList::addExistingAllocation(const DString& strKey, 
   const BFDataGroupId& idDataGroup, bool bAddChildren)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("addExistingAllocation"));

   BFObjectKey objKey(strKey, idDataGroup);
   TradeAcctAlloc * pNewTradeAcctAlloc;
   getKey(objKey, NULL, true);
   objKey.setActivity(OBJ_ACTIVITY_NONE);
   pNewTradeAcctAlloc = new TradeAcctAlloc(*this);
   setObject(objKey, pNewTradeAcctAlloc);

   //the key is the AccountNum
   DString strAccountNum(strKey),strAmount(NULL_STRING) ;
   if(strAccountNum.strip().stripLeading('0') != NULL_STRING)
      pNewTradeAcctAlloc->setField(ifds::AccountNum, strAccountNum, idDataGroup, false);

   pNewTradeAcctAlloc->initWithDefaultValues(idDataGroup);
   pNewTradeAcctAlloc->copyDataFromParent(idDataGroup);

   if(bAddChildren)
   {
      assert(pNewTradeAcctAlloc);
      TradeFundAllocList *pFundAllocList;
      pNewTradeAcctAlloc->getFundAllocationList(pFundAllocList, idDataGroup, true, false);//this will set the amount, too
      //if there is no allocation in the list, we have to add the 100% alloc
      BFObjIter iter(*pFundAllocList, idDataGroup);
      int nNbrOfAlloc = iter.getNumberOfItemsInList();
      if(nNbrOfAlloc == 0)//no default alloc; have to copy parent data
         pFundAllocList->addExistingAllocation(NULL_STRING, idDataGroup, bAddChildren);//this will set the amount, too
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeAcctAllocList::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   AcctAllocList::doApplyRelatedChanges(idField, idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeAcctAllocList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	// Do validation only if there is any object in the map
   BFObjIter iterTradeAcctAllocList( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	iterTradeAcctAllocList.begin();
	int iCount = iterTradeAcctAllocList.getNumberOfItemsInList();
   if ( iCount > 0 )	
	{
		AcctAllocList::doValidateAll(idDataGroup, lValidateGroup);
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeAcctAllocList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   TradeAcctAlloc *pAllocation = new TradeAcctAlloc(*this);
   pAllocation->initNew(idDataGroup);
   pBase = pAllocation;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TradeAcctAllocList::getStrKey(DString &strKey, const BFData *data)
{
   TRACE_METHOD(CLASSNAME, I_("getStrKey"));

   if(!data)
   {
      BFCBO::getStrKey(strKey, data);
   }
   else
   {
      data->getElementValue(ifds::AccountNum, strKey);
      strKey.strip().stripLeading('0');
   }
}

//******************************************************************************
void TradeAcctAllocList::getStrKeyForNewItem(DString & strKey)
{
   if(strKey.strip().empty())
   {
      BFCBO::getStrKeyForNewItem(strKey);
   }
   else
   {
      strKey.stripLeading('0');
   }
}

//******************************************************************************
SEVERITY TradeAcctAllocList::setListFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setListFields"));

   BFCBO *pParent = NULL;
   pParent = getParent();
   assert(pParent);
   DString str;

   if (dynamic_cast<Trade*>(pParent))
   {
      setFieldFromCBO(pParent, ifds::TradesTransType, ifds::TransType, idDataGroup, str);
      setFieldFromCBO(pParent, ifds::FromFund, ifds::FromFund, idDataGroup, str);
      setFieldFromCBO(pParent, ifds::FromClass, ifds::FromClass, idDataGroup, str);
      setFieldFromCBO(pParent, ifds::EffectiveDate, ifds::EffectiveDate, idDataGroup, str);
   }
   else if ( dynamic_cast<PendingTradeDetails*>(pParent) ||
             dynamic_cast<TransactionDetails*>(pParent)
           )
   {
      setFieldFromCBO(pParent, ifds::TransType, ifds::TransType, idDataGroup, str);
      setFieldFromCBO(pParent, ifds::rxFundCode, ifds::FromFund, idDataGroup, str);
      setFieldFromCBO(pParent, ifds::rxClassCode, ifds::FromClass, idDataGroup, str);
      setFieldFromCBO(pParent, ifds::TradeDate, ifds::EffectiveDate, idDataGroup, str);
   } 
   setFieldFromCBO(pParent, ifds::Amount, ifds::Amount, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::AmtType, ifds::AllocAmtType, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::SettleCurrency, ifds::Currency, idDataGroup, str);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void TradeAcctAllocList::getFormattedAmount(const BFDataGroupId& idDataGroup, 
   DString &dstrValue)
{
   DString strTransType, strAmountType;

   getField(ifds::AllocAmtType, strAmountType, idDataGroup, false);
   getField(ifds::TransType, strTransType, idDataGroup, false);

   if(strAmountType.strip().upperCase() != UNITS)
   {
      //if(strTransType.strip() == TRADETYPE::MGMT_FEE || strTransType == TRADETYPE::PURCHASE || strTransType == TRADETYPE::REDEMPTION)
      if (DSTCommonFunctions::codeInList (strTransType, TRADETYPE::ONE_SIDE_TRADE ))
         formatAmtUsingCurrency(idDataGroup, dstrValue);
      else //if(strTransType.strip() == TRADETYPE::EXCHANGE || strTransType == TRADETYPE::TRANSFER || strTransType == TRADETYPE::ALL_FUND_TRANSFER)
         formatAmtUsingFromFund(idDataGroup, dstrValue);
   }
   else//units
   {
      formatAmtUsingFromFund(idDataGroup, dstrValue);
   }  
}

//******************************************************************************
SEVERITY TradeAcctAllocList::getDefaultAllocList(AbstractAllocList*& pDefaultAllocationList, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDefaultAllocList"));
   //rule : if AMSCode in the account 
   //a) has a valid value - get AMSType, DefaultAlloc and FundAlloc fields 
   //from the corresponding AMSMstr record
   //a1)if AMSType == RB
   //a11) if  DefaultAlloc == Y, get RB type shareholder default allocations
   //a12 else if FundAlloc == Y, get AMS allocations from MFAccount
   //a2,b) any other case - get default allocations for the specified trans type

   pDefaultAllocationList = NULL;
   DString strAccountNum, strAMSCode(NULL_STRING);
   getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
   MFAccount* pMFAccount = NULL;
   if(getWorkSession().getMFAccount(idDataGroup, strAccountNum, pMFAccount) > WARNING || !pMFAccount)
      return(GETCURRENTHIGHESTSEVERITY());

   pMFAccount->getField(ifds::AMSCode, strAMSCode, idDataGroup, false);
   if (!strAMSCode.strip().empty())
   {
      DString strDefaultAlloc, strFundAlloc;
      AMSMstrList objAMSMstrList(*this);
      if (objAMSMstrList.init2(RB_TYPE, strAMSCode, true)>WARNING)
         return(GETCURRENTHIGHESTSEVERITY());

	  DString dstrEffectiveDate = NULL;
   	  getWorkSession().getDateInHostFormat(dstrEffectiveDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   

      objAMSMstrList.getFieldByAMSCode(RB_TYPE,strAMSCode,dstrEffectiveDate, ifds::DefaultAlloc, 
         strDefaultAlloc, idDataGroup, false);
      if (strDefaultAlloc == YES)
      {
         getRebalDefAllocList(pDefaultAllocationList, idDataGroup);
         return(GETCURRENTHIGHESTSEVERITY());
      }
      else if (strDefaultAlloc == NO)
      {
         objAMSMstrList.getFieldByAMSCode(RB_TYPE,strAMSCode,dstrEffectiveDate, ifds::FundAlloc, 
            strFundAlloc, idDataGroup, false);
         if (strFundAlloc == YES)
         {
            getAMSDefAllocList(pDefaultAllocationList, idDataGroup);
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
   }
   getShrDefAllocList(pDefaultAllocationList, idDataGroup);   
   
   return GETCURRENTHIGHESTSEVERITY();
}
//*****************************************************************************
void  TradeAcctAllocList::changeFieldsForRebook()
{
   BFObjIter iter ( *this, 
                     BF::HOST                      
                     );
   while( !iter.end() )
   {
      TradeAcctAlloc* pTradeAcctAlloc = dynamic_cast<TradeAcctAlloc* >( iter.getObject() );
      pTradeAcctAlloc->changeFieldsForRebook();
      ++iter;   
   }
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeAcctAllocList.cpp-arc  $
// 
//    Rev 1.28   Jan 29 2008 13:18:28   daechach
// IN#1134569 - Cancel of Transfer out Trade not Allowed.
// 
//    Rev 1.27   Jul 08 2005 09:33:12   Yingbaol
// PET1235,FN01:transaction cancellation rebook
// 
//    Rev 1.26   Apr 22 2005 17:28:40   aguilaam
// IN 290231, 275393, 290196 : set account number for call to view 60 and 151
// 
//    Rev 1.25   Mar 28 2005 16:01:50   yingbaol
// incident 23776: fix discard window pops up even though there is nothing updated
// 
//    Rev 1.24   Dec 16 2004 12:15:32   popescu
// PET 1117/06/56, fixed allocations issues for transfers in pending mode, also set of a settle curr if DefSettleCurr-83 is N
// 
//    Rev 1.23   Nov 22 2004 13:09:38   popescu
// PET 1117/56. fees processing
// 
//    Rev 1.22   Nov 14 2004 14:57:40   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.21   Sep 02 2004 15:01:10   WINNIE
// PET 1094 FN08 : New Fee Type implementation and clean up code to use isPurchaseLike and iRedemptionLike
// 
//    Rev 1.20   Oct 21 2003 13:45:54   VADEANUM
// PTS 10023082 - Error message doesn't allow to modify redemption - doValidateAll() only there is an object in the map.
// 
//    Rev 1.19   Sep 01 2003 21:32:38   popescu
// PET 809, FN 02 CIBC Multi Fund Transfer
// 
//    Rev 1.18   Jul 23 2003 11:07:28   linmay
// sync with getamsmstrlist
// 
//    Rev 1.17   Jun 18 2003 11:21:10   popescu
// PTS 100017258
// 
//    Rev 1.16   May 30 2003 19:20:04   popescu
// PTS 10017741
// 
//    Rev 1.15   May 15 2003 15:03:28   popescu
// fixes for a crash in PendingTrades, split comm
// 
//    Rev 1.14   Apr 21 2003 09:48:42   YINGBAOL
// change getFieldByAMSCode sync.
// 
//    Rev 1.13   Mar 21 2003 18:26:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.12   Jan 16 2003 17:05:28   KOVACSRO
// Fix for previous implementation : if view 179 fails, just return.
// 
//    Rev 1.11   Jan 15 2003 17:35:50   KOVACSRO
// The rules for picking up default allocations have changed.
// 
//    Rev 1.10   Nov 29 2002 10:52:58   KOVACSRO
// Added support for different kind of default allocations.
// 
//    Rev 1.9   Oct 09 2002 23:55:10   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 12:56:52   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.7   Aug 01 2002 11:35:08   KOVACSRO
// format amount fix.
// 
//    Rev 1.6   Jul 31 2002 14:58:54   KOVACSRO
// Added getStrKeyForNewItem
// 
//    Rev 1.5   Jun 27 2002 17:21:06   KOVACSRO
// AllocAmtType versus AmountType.
// 
//    Rev 1.4   24 May 2002 15:48:56   KOVACSRO
// some fixes.
// 
//    Rev 1.3   22 May 2002 18:30:04   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   10 May 2002 13:38:28   KOVACSRO
// A bug fixed for the account number.
// 
//    Rev 1.1   08 May 2002 17:02:06   KOVACSRO
// More implementation.
// 
//    Rev 1.0   29 Apr 2002 16:57:48   KOVACSRO
// Initial revision.
 * 
 * 
 */