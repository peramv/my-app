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
// ^FILE   : WorksessionTradesList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September 2004
//
// ^CLASS    : WorksessionTradesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "worksessiontradeslist.hpp"

#include "adminfee.hpp"
#include "atwithdraw.hpp"
#include "alltransfer.hpp"
#include "cusiprollover.hpp"
#include "exchange.hpp"
#include "duplicatetradecheck.hpp"
#include "fulleapredemption.hpp"
#include "hybridpurchase.hpp"
#include "hybridredemption.hpp"
#include "inspeciesnonproratapurchase.hpp"
#include "inspeciesnonprorataredemption.hpp"
#include "inspeciespurchase.hpp"
#include "inspeciesredemption.hpp"
#include "lighttrade.hpp"
#include "manualdividend.hpp"
#include "mgmtfee.hpp"
#include "mgmtfeerebate.hpp"
#include "manualmgmtfeerebate.hpp"
#include "manualforeigncapgainallocAdjustment.hpp"
#include "purchase.hpp"
#include "redemption.hpp"
#include "reinvestpurchase.hpp"
#include "rollover.hpp"
#include "pendingtradedetails.hpp"
#include "transactionDetails.hpp"
#include "transfer.hpp"
#include "tradefundalloclist.hpp"
#include "RolloverExchange.hpp"
#include "ForeignCapGainAllocationAdjustment.hpp"
#include "SupplementaryIncomeAdjustment.hpp"
#include "MgmtFeeRebateAdjustment.hpp"
#include "CapitalGainIncomeAdjustment.hpp"
#include "ManualDividendAdjustment.hpp"
#include "AdvisorFee.hpp"
#include "CrossSysTransferIn.hpp"
#include "CrossSysTransferOut.hpp"
#include "InterClassSwitch.hpp"
#include "RefundRedemption.hpp"
#include "errmsgruleslist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

//active batch
#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("WorksessionTradesList");
   const I_CHAR * const AMOUNT = I_ ("D");//Dollars

   const int AUTO_BATCHING = 2;
}

namespace CND
{
   extern const long WARN_BATCH_NAME_HAS_BEEN_CHANGED;
   extern const long ERR_DUPLICATE_TRADE;//this is warning
   extern const long WARN_DUPLICATE_TRADE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId PurchaseTotal;
   extern CLASS_IMPORT const BFTextFieldId ChkDuplicationTrade;
//pending trades fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundTo;
   extern CLASS_IMPORT const BFTextFieldId ClassToCode;
   extern CLASS_IMPORT const BFTextFieldId PayType2;
   extern CLASS_IMPORT const BFTextFieldId AmountType;
   extern CLASS_IMPORT const BFTextFieldId Baycom;
   extern CLASS_IMPORT const BFTextFieldId BayComTo;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId TransModPerm;
   extern CLASS_IMPORT const BFTextFieldId PayInstructExists;
   extern CLASS_IMPORT const BFDecimalFieldId InvHisInvestId;
   extern CLASS_IMPORT const BFNumericFieldId PendingRid;
   extern CLASS_IMPORT const BFNumericFieldId rxAcctNum;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;

   extern CLASS_IMPORT const BFTextFieldId FieldAssignment;
   extern CLASS_IMPORT const BFNumericFieldId SplitCommRebookTransID;
   extern CLASS_IMPORT const BFTextFieldId RcptStatus;
   extern CLASS_IMPORT const BFTextFieldId GrossNetMethod;
   extern CLASS_IMPORT const BFIntegerFieldId AutoBatch;
   extern CLASS_IMPORT const BFTextFieldId BatchUser;
   extern CLASS_IMPORT const BFTextFieldId Broker;
   extern CLASS_IMPORT const BFTextFieldId Branch;
   extern CLASS_IMPORT const BFTextFieldId FromHistoryTrade;
   extern CLASS_IMPORT const BFTextFieldId SalesRepCode;
   extern CLASS_IMPORT const BFTextFieldId SlsrepCode;
   extern CLASS_IMPORT const BFDecimalFieldId GrossAmt;
   extern CLASS_IMPORT const BFDecimalFieldId NetAmt;
   extern CLASS_IMPORT const BFDecimalFieldId ForcedRateAmt;
   extern CLASS_IMPORT const BFTextFieldId AWDFieldFlag;
   extern CLASS_IMPORT const BFTextFieldId Indc;
   extern CLASS_IMPORT const BFTextFieldId DupliRuleFieldList ;
   extern CLASS_IMPORT const BFTextFieldId Allocation;//INC0039323
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACTIVE_BATCH;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//    Field DD Id,            State Flags,         Group Flags
   { ifds::PurchaseTotal,    BFCBO::NONE, BFCBO::CALCULATED_FIELD},
   { ifds::TradesTransType,  BFCBO::NONE, BFCBO::CALCULATED_FIELD},
   { ifds::AccountNum,       BFCBO::NONE, BFCBO::CALCULATED_FIELD},
   { ifds::TransModPerm,     BFCBO::NONE, BFCBO::CALCULATED_FIELD},
   { ifds::TradesPayType,    BFCBO::NONE, BFCBO::CALCULATED_FIELD},
   { ifds::Amount,           BFCBO::NONE, BFCBO::CALCULATED_FIELD},
   { ifds::AmtType,          BFCBO::NONE, BFCBO::CALCULATED_FIELD},
   { ifds::EffectiveDate,    BFCBO::NONE, BFCBO::CALCULATED_FIELD},
   { ifds::FieldAssignment,  BFCBO::NONE, BFCBO::CALCULATED_FIELD},
   { ifds::WireOrdNum,       BFCBO::NONE, BFCBO::CALCULATED_FIELD},
   { ifds::OrderType,        BFCBO::NONE, BFCBO::CALCULATED_FIELD},
   { ifds::Indc,             BFCBO::NONE, BFCBO::CALCULATED_FIELD},
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

struct DuplicateTrade
{
	BFFieldId configurableField;
	const I_CHAR* fieldValue;

};
const struct DuplicateTrade duplicateTradeList [] =
{
	ifds::AccountNum,       I_(";AccountNum="),
	ifds::FromFund,         I_(";FundCode="),
	ifds::FromClass,        I_(";ClassCode="),
	ifds::Amount,           I_(";Amount="),
	ifds::AmtType,          I_(";AmountType="),
	ifds::TradesTransType,  I_(";TransType="),
	ifds::Indc,             I_(";Indc="),
	ifds::EffectiveDate,    I_(";EffectiveDate="),
	ifds::SettleCurrency,   I_(";SettleCurrency="),
	ifds::SettleDate,       I_(";SettleDate="),
	ifds::ToFund,           I_(";ToFund="),
	ifds::ToClass,          I_(";ToClass="),
	ifds::AccountTo,        I_(";AccountTo="),
};

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
   extern CLASS_IMPORT I_CHAR * const ALL_FUND_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE_REBATE;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const REINVEST_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const DIVIDEND;
   extern CLASS_IMPORT I_CHAR * const AUTO_WITHDRAW;
   extern CLASS_IMPORT I_CHAR * const MANUAL_MGMT_FEE_REBATE;
   extern CLASS_IMPORT I_CHAR * const FOREIGN_CAP_GAIN_ALLOC_ADJUSTMENT;
   extern CLASS_IMPORT I_CHAR * const HYBRID_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const HYBRID_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const INSPECIES_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const INSPECIES_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const REFUND_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const CUSIP_ROLLOVER;
   extern CLASS_IMPORT I_CHAR * const INSP_NON_PRO_RATA_PURCHASE;  
   extern CLASS_IMPORT I_CHAR * const INSP_NON_PRO_RATA_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const FULL_EAP_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const MANUAL_DIVIDEND_ADJ;    
   extern CLASS_IMPORT I_CHAR * const CAPITAL_GAIN_INCOME_ADJ; 
   extern CLASS_IMPORT I_CHAR * const SUPPLEMENTARY_INCOME_ADJ;  
   extern CLASS_IMPORT I_CHAR * const FOREIGN_CAPGAIN_ALLOCATION_ADJ;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE_REBATE_ADJ;
   extern CLASS_IMPORT I_CHAR * const ADVISOR_FEE;
   extern CLASS_IMPORT I_CHAR * const CROSS_SYSTEM_TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const CROSS_SYSTEM_TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
}
namespace IFASTERR
{
	 extern CLASS_IMPORT I_CHAR * const DUPLICATE_ALREADY_EXIST;
}

//******************************************************************************
void WorksessionTradesList::buildKey ( const DString &accountNum,
                                       const DString &transNum,
                                       DString &strKey)
{
   DString _accountNum (accountNum),
      _transNum (transNum);

   _accountNum.strip().stripLeading ('0');
   _transNum.strip().stripLeading ('0');
   strKey = I_("Account=") + _accountNum + 
            I_(";TransNum=") + _transNum;
}


//******************************************************************************
WorksessionTradesList::WorksessionTradesList (BFAbstractCBO &parent) 
: MFCanBFCbo (parent),
_bRebook (false),
_bIsARollover (false),
_bManualTrades (false),
_bFromHistory (false),
_batchName (NULL_STRING),
m_bDuplicateTrade (false),
_pErrMsgRulesList (NULL)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO*)&classFieldInfo, 0, NULL);
   setObjectAsList ();
}

//******************************************************************************
WorksessionTradesList::~WorksessionTradesList()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY WorksessionTradesList::init ( const BFDataGroupId &idDataGroup, 
                                       const DString &track, 
                                       const DString &pageName)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init"));
   _track = track;
   _pageName = pageName;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY WorksessionTradesList::fromPending2Trade ( PendingTradeDetails *pPendingTrade,
                                                    const BFDataGroupId &idDataGroup,
                                                    bool bReqRefresh,
                                                    DString &strNewKey,
                                                    bool bSameAccount /*= false*/,
                                                    bool bRebook /*=false*/,
                                                    bool bMultipleRebook /*= false*/,
                                                    bool bIsARollover /*= false*/,
                                                    const DString &rebookBatch /* = NULL_STRING*/,
                                                    bool bRefund /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("fromPending2Trade"));
   assert (pPendingTrade);
   _bRebook = bRebook;
   _bRefund = bRefund;
   _bIsARollover = bIsARollover;

   DString batchUser, strINDC;

   BFData *data = new BFData (ifds::DSTC0115_REQ);
//fill the 115 data object with the pending trades values
   if (pPendingTrade->getData (*data, idDataGroup) <= WARNING)
   {
      fromPending2Trade (pPendingTrade, data, idDataGroup);

      BFCBO *bfcbo = NULL;
      Trade *pTrade = NULL;
      DString transModPerm, strAmount;

      pPendingTrade->getField (ifds::TransModPerm, transModPerm, idDataGroup, false);
      pPendingTrade->getField (ifds::BatchUser, batchUser, idDataGroup, false);
      pPendingTrade->getField (ifds::Indc, strINDC, idDataGroup, false);
      //save permission mode
      setField (ifds::TransModPerm, transModPerm, BF::HOST, false);
      setField (ifds::Indc, strINDC, BF::HOST, false);

      pPendingTrade->getField (ifds::Amount, strAmount, idDataGroup, false);
      doCreateObject (*data, bfcbo);
      //reset permission mode
      setField (ifds::TransModPerm, NULL_STRING, BF::HOST, false);
      if (bfcbo)
      {
         BFObjectKey objKey;
         DString strRcptStatus, strGrossNetMethod, strGrossOrNet, strForcedRateAmt, strAllocation;

         getKey (objKey, data);
         setObject (objKey, bfcbo);
         bfcbo->setField (ifds::RqdRefresh, bReqRefresh ? I_("Y") : I_("N"), idDataGroup, false);
         pTrade = dynamic_cast<Trade*>(bfcbo);
         assert(pTrade);

         pTrade->setRebookForSameAcctTransType(bSameAccount);
         pPendingTrade->getField (ifds::RcptStatus, strRcptStatus, idDataGroup, false);
         pTrade->setField( ifds::RcptStatus, strRcptStatus, idDataGroup, false);
         pPendingTrade->getField (ifds::GrossNetMethod, strGrossNetMethod, idDataGroup, false);
         strGrossOrNet = strGrossNetMethod.strip() == I_("02") && !_bRefund ? "N" : "Y";
         pTrade->setField( ifds::GrossOrNet, strGrossOrNet, idDataGroup, false);
         pPendingTrade->getField(ifds::ForcedRateAmt, strForcedRateAmt, idDataGroup, false);
         pTrade->setField(ifds::ForcedRateAmt, strForcedRateAmt, idDataGroup, false);
		 pPendingTrade->getField(ifds::Allocation, strAllocation, idDataGroup, false);//INC0039323
         pTrade->setField(ifds::Allocation, strAllocation, idDataGroup, false);//INC0039323
         if (!rebookBatch.empty ())
            pTrade->initRebookBatch (rebookBatch, idDataGroup);

         pTrade->canUserModifyBatch (batchUser, BF::HOST);
         if( bSameAccount )
         {
             pTrade->setInitialRebookTradeAmount(strAmount);
         }
// clear this for idDataGroup
         pTrade->clearUpdatedFlags (idDataGroup);
         pTrade->setAllFieldsValid (idDataGroup);
         strNewKey = objKey.getStringKey ();
         if (_bRebook)
         {
            pTrade->postInitRebook (idDataGroup, bMultipleRebook);
            //because of the nature of rebook, is part of a flow, the trade should always be dirty
            //to trigger validation
            pTrade->makeDirty (idDataGroup);
         }
         if (_bRefund)
         {
            pTrade->postInitRefund (idDataGroup);
            //because of the nature of refund, is part of a flow, the trade should always be dirty
            //to trigger validation
            pTrade->makeDirty (idDataGroup);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY WorksessionTradesList::fromHistory2Trade ( TransactionDetails *pHistoryTrade,
                                                    const BFDataGroupId &idDataGroup,
                                                    bool bReqRefresh,
                                                    DString &strNewKey,
                                                    bool bSameAccount /*= false*/,
                                                    bool bRebook /*=false*/,
                                                    bool bMultipleRebook /*= false*/,
                                                    bool bIsARollover /*= false*/,
                                                    const DString &rebookBatch /* = NULL_STRING*/,
                                                    bool bRefund /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("fromHistory2Trade"));

   assert (pHistoryTrade);
   _bRebook = bRebook;
   _bIsARollover = bIsARollover;

   DString batchUser,
      strINDC;

   BFData *data = new BFData (ifds::DSTC0115_REQ);
   //fill the 115 data object with the history trades values
   if (pHistoryTrade->getData (*data, idDataGroup) <= WARNING)
   {
      _bFromHistory = true;
      fromHistory2Trade (pHistoryTrade, data, idDataGroup);

      BFCBO *bfcbo = NULL;
      Trade *pTrade = NULL;
      DString transModPerm, strAmount;

      pHistoryTrade->getField (ifds::TransModPerm, transModPerm, idDataGroup, false);
      pHistoryTrade->getField (ifds::BatchUser, batchUser, idDataGroup, false);
      pHistoryTrade->getField (ifds::Indc, strINDC, idDataGroup, false);
      //save permission mode
      setField (ifds::TransModPerm, transModPerm, BF::HOST, false);
      setField (ifds::Indc, strINDC, BF::HOST, false);

      data->getElementValue (ifds::Amount, strAmount );
      doCreateObject (*data, bfcbo);
      //reset permission mode
      setField (ifds::TransModPerm, NULL_STRING, BF::HOST, false);
      if (bfcbo)
      {
         BFObjectKey objKey;
         DString strRcptStatus, strGrossNetMethod, strGrossOrNet;

         getKey (objKey, data);
         setObject (objKey, bfcbo);
         bfcbo->setField (ifds::RqdRefresh, bReqRefresh ? I_("Y") : I_("N"), idDataGroup, false);
         pTrade = dynamic_cast<Trade*>(bfcbo);
         assert(pTrade);

         pTrade->setRebookForSameAcctTransType(bSameAccount);
         pHistoryTrade->getField (ifds::RcptStatus, strRcptStatus, idDataGroup, false);
         pTrade->setField( ifds::RcptStatus, strRcptStatus, idDataGroup, false);
         pTrade->setField( ifds::FromHistoryTrade, I_("Y"), idDataGroup, false);

         if (!rebookBatch.empty ())
            pTrade->initRebookBatch (rebookBatch, idDataGroup);

         pTrade->canUserModifyBatch (batchUser, BF::HOST);
         if( bSameAccount )
         {
             pTrade->setInitialRebookTradeAmount(strAmount);
         }
// clear this for idDataGroup
         pTrade->clearUpdatedFlags (idDataGroup);
         pTrade->setAllFieldsValid (idDataGroup);
         strNewKey = objKey.getStringKey ();
         if (_bRebook)
         {
            pTrade->postInitRebook (idDataGroup, bMultipleRebook);
            //because of the nature of rebook, is part of a flow, the trade should always be dirty
            //to trigger validation
            pTrade->makeDirty (idDataGroup);
         }
         if (bRefund)
         {
            pTrade->postInitRefund (idDataGroup);
            //because of the nature of rebook, is part of a flow, the trade should always be dirty
            //to trigger validation
            pTrade->makeDirty (idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
inline void WorksessionTradesList::setManualTrades (bool bManualTrades)
{
   _bManualTrades = bManualTrades;
}

//******************************************************************************
SEVERITY WorksessionTradesList::doCreateObject ( const BFData &data, 
                                                 BFCBO* &pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doCreateObject"));
   DString transType = data.getElementValue (ifds::TradesTransType),
      transModPerm, strINDC;

   transType.strip();
   getField (ifds::TransModPerm, transModPerm, BF::HOST, false);
   getField (ifds::Indc, strINDC, BF::HOST, false);
//rollover is a special transaction composed of a PW an a ED
//the transtype read from the back-end should be changed to 'LR'
   if (_bIsARollover && _bRebook)
   {
      transType = TRADETYPE::ROLLOVER;
   }

   if(_bRefund)
   {
      transType = TRADETYPE::REFUND_REDEMPTION;
   }

   if(transType.strip().upperCase() == TRADETYPE::REDEMPTION && 
      strINDC.strip().upperCase() == I_("96"))
   {
      transType = TRADETYPE::FULL_EAP_REDEMPTION;
   }

   Trade *pTrade = makeTrade (transType, BF::HOST);
   if (pTrade)
   {
      if (_bRebook ) //rebook
      {
         if( _bFromHistory )
         {
            pTrade->initRebookFromHistory(data);
         }
         else
         {
            pTrade->initRebook (data);
         }
      }
      else if (_bRefund ) //rebook
      {
         pTrade->initRefund(data);
      }
      else //pending
      {
         if (pTrade->init (data) <= WARNING)
         {
            pTrade->applyModPerm (transModPerm, BF::HOST);
         }
      }
   }
   pObjOut = pTrade;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY WorksessionTradesList::doCreateNewObject ( BFCBO* &pBase, 
                                                    DString &strKey, 
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doCreateNewObject"));

   DString transType;
   getField (ifds::TradesTransType, transType, idDataGroup, false);

   Trade *pTrade = makeTrade (transType, idDataGroup);

   if (pTrade->init (idDataGroup, _track, _pageName) <= WARNING)
   {
      DString accountNum,
         effectiveDate;

      getField ( ifds::AccountNum, 
                 accountNum, 
                 idDataGroup, 
                 false);
      getField ( ifds::EffectiveDate, 
                 effectiveDate, 
                 idDataGroup, 
                 false);
      accountNum.stripLeading ('0');
      if (!accountNum.empty())
      {         
         SEVERITY sev = NO_CONDITION;

         if(!bfutil::isServerContext())
         {
            if (!effectiveDate.empty())
            {
               sev = pTrade->setField ( ifds::EffectiveDate, 
                                    effectiveDate, 
                                    idDataGroup, 
                                    false, 
                                    true, 
                                    true);
            }
         }
         if (sev <= WARNING)
         {
            pTrade->setObjectNew();
            if ( pTrade->setField ( ifds::AccountNum, 
                                    accountNum, 
                                    idDataGroup, 
                                    false, 
                                    true, 
                                    true) <= WARNING)
            {
               DString transNum;

               pTrade->getField ( ifds::TransNum, 
                                  transNum, 
                                  idDataGroup, 
                                  false);

               BFData data;

               data.setElementValue (ifds::AccountNum, accountNum, true);
               data.setElementValue (ifds::TransNum, transNum, true);
               getStrKey (strKey, &data);
            }
         }
      }

      DString fieldAssignment;
      
      getField (ifds::FieldAssignment, fieldAssignment, idDataGroup, false);
      pTrade->setField (ifds::FieldAssignment, fieldAssignment, idDataGroup, false, true, true);

      if (fieldAssignment == I_("API"))
      {
         DString payType;

         getField (ifds::TradesPayType, payType, idDataGroup, false);
         payType.strip();
         pTrade->setField ( ifds::TradesPayType, payType, idDataGroup, false, 
                            true, 
                            true);
      }
      if (fieldAssignment == I_("FromAWD"))
      {
         DString amount, 
                 amtType,
				 orderType,
				 wireOrderNum;

         getField (ifds::Amount, amount, idDataGroup, false);
         getField (ifds::AmtType, amtType, idDataGroup, false);
         getField (ifds::OrderType, orderType, idDataGroup, false);
         getField (ifds::WireOrdNum, wireOrderNum, idDataGroup, false);
         if (!amount.empty())
         {
            pTrade->setField (ifds::Amount, amount, idDataGroup, false, true, true);
         }
         if (!amtType.empty())
         {
            pTrade->setField (ifds::AmtType, amtType, idDataGroup, false, true, true);
         }
		 if (!orderType.empty())
         {
            pTrade->setField (ifds::OrderType, orderType, idDataGroup, false, true, true);
         }
		 if (!wireOrderNum.empty())
         {
            pTrade->setField (ifds::WireOrdNum, wireOrderNum, idDataGroup, false, true, true);
         }
      }
   }
//reset the account num field and trans type on the list...
   setField (ifds::FieldAssignment, NULL_STRING, idDataGroup, false);
   setField (ifds::AccountNum, NULL_STRING, idDataGroup, false);
   setField (ifds::TradesTransType, NULL_STRING, idDataGroup, false);
   setField (ifds::EffectiveDate, NULL_STRING, idDataGroup, false);
   setField (ifds::Amount, NULL_STRING, idDataGroup, false);
   setField (ifds::AmtType, NULL_STRING, idDataGroup, false);
   pBase = pTrade;
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
void WorksessionTradesList::getStrKey ( DString &strKey, 
                                        const BFData *data /*= NULL*/)
{
   if (data)
   {
      DString accountNum,
         transNum,
         genKey;

      BFCBO::getStrKey (genKey, NULL);
      accountNum = data->getElementValue (ifds::AccountNum);
      transNum = data->getElementValue (ifds::TransNum);
      buildKey (accountNum, transNum, strKey);
//this will preserve the order in which the elements were added
      strKey = I_("Key=") + genKey + I_(";") + strKey; 
   }
   else
   {
      BFCBO::getStrKey (strKey);
   }
}

//*********************************************************************************
void WorksessionTradesList::getStrKeyForNewItem (DString &strKey)
{
   DString genKey;

   BFCBO::getStrKey (genKey, NULL);
//this will preserve the order in which the elements were added
   strKey = I_("Key=") + genKey; 
}

//******************************************************************************
Trade *WorksessionTradesList::makeTrade ( const DString &transType,
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("makeTrade"));

   Trade *pTrade = NULL;

   const_cast <DString&>(transType).upperCase();
   if (transType == TRADETYPE::ADMIN_FEE)
   {
      pTrade = new AdminFee (*this);
   }
   else if (transType == TRADETYPE::ALL_FUND_TRANSFER)
   {
      pTrade = new AllTransfer (*this);
   }
   else if (transType == TRADETYPE::EXCHANGE)
   {
      pTrade = new Exchange (*this);
   }
   else if (transType == TRADETYPE::MGMT_FEE)
   {
      pTrade = new MgmtFee (*this);
   }
   else if (transType == TRADETYPE::MGMT_FEE_REBATE)
   {
      pTrade = new MgmtFeeRebate (*this);
   }
   else if (transType == TRADETYPE::FOREIGN_CAP_GAIN_ALLOC_ADJUSTMENT)
   {
      pTrade = new ManualForeignCapGainAllocAdjustment (*this);
   }
   else if (transType == TRADETYPE::MANUAL_MGMT_FEE_REBATE)
   {
      pTrade = new ManualMgmtFeeRebate (*this);
   }
   else if (transType == TRADETYPE::PURCHASE)
   {
      pTrade = new Purchase (*this);
   }
   else if (transType == TRADETYPE::HYBRID_PURCHASE)
   {
      pTrade = new HybridPurchase (*this);
   }
   else if (transType == TRADETYPE::INSPECIES_PURCHASE)
   {
      pTrade = new InSpeciesPurchase (*this);
   }
   else if (transType == TRADETYPE::REDEMPTION)
   {
      pTrade = new Redemption (*this);
   }
    else if (transType == TRADETYPE::HYBRID_REDEMPTION)
   {
      pTrade = new HybridRedemption (*this);
   } 
   else if (transType == TRADETYPE::INSPECIES_REDEMPTION)
   {
      pTrade = new InSpeciesRedemption (*this);
   }
   else if (transType == TRADETYPE::REFUND_REDEMPTION)
   {
      pTrade = new RefundRedemption (*this);
   }
   else if (transType == TRADETYPE::REINVEST_PURCHASE)
   {
      pTrade = new ReinvestPurchase (*this);
   }
   else if (transType == TRADETYPE::ROLLOVER)
   {
      pTrade = new Rollover (*this);
   }
   else if (transType == TRADETYPE::CUSIP_ROLLOVER)
   {
      pTrade = new CusipRollover (*this);
   }
   else if (transType == TRADETYPE::TRANSFER)
   {
      pTrade = new Transfer (*this);
   }
   else if (transType == TRADETYPE::DIVIDEND)
   {
      pTrade = new ManualDividend (*this);
   }
   else if( transType == TRADETYPE::AUTO_WITHDRAW )
   {
      pTrade = new ATWithdraw (*this);   
   }
   else if( transType == TRADETYPE::INSP_NON_PRO_RATA_PURCHASE )  
   {
      pTrade = new InSpeciesNonProRataPurchase (*this);   
   }
   else if( transType == TRADETYPE::INSP_NON_PRO_RATA_REDEMPTION )
   {
      pTrade = new InSpeciesNonProRataRedemption (*this);     
   }
   else if( transType == TRADETYPE::FULL_EAP_REDEMPTION )
   {
      pTrade = new FullEAPRedemption (*this);
   }
   else if( transType == TRADETYPE::ROLLOVER_EXCHANGE )
   {
      pTrade = new RolloverExchange (*this);
   }
   else if (transType == TRADETYPE::MANUAL_DIVIDEND_ADJ)
   {
       pTrade = new ManualDividendAdjustment(*this);
   }
   else if (transType == TRADETYPE::CAPITAL_GAIN_INCOME_ADJ)
   {
       pTrade = new CapitalGainIncomeAdjustment(*this);
   }
   else if (transType == TRADETYPE::SUPPLEMENTARY_INCOME_ADJ)
   {
       pTrade = new SupplementaryIncomeAdjustment(*this);
   }
   else if (transType == TRADETYPE::FOREIGN_CAPGAIN_ALLOCATION_ADJ)
   {
       pTrade = new ForeignCapGainAllocationAdjustment(*this);
   }
   else if (transType == TRADETYPE::MGMT_FEE_REBATE_ADJ)
   {
       pTrade = new MgmtFeeRebateAdjustment(*this);
   }
   else if (transType == TRADETYPE::ADVISOR_FEE)
   {
       pTrade = new AdvisorFee(*this);
   }
   else if (transType == TRADETYPE::CROSS_SYSTEM_TRANSFER_IN)
   {
       pTrade = new CrossSysTransferIn(*this);
   }
   else if (transType == TRADETYPE::CROSS_SYSTEM_TRANSFER_OUT)
   {
       pTrade = new CrossSysTransferOut(*this);
   }
   else if (transType == TRADETYPE::INTER_CLASS_SWITCH)
   {
       pTrade = new InterClassSwitch(*this);
   }
   else if (transType.empty())
   {
      pTrade = new LightTrade (*this, _bManualTrades);
   }
   else //unknown trade type
   {
      assert (0);
   }
   return pTrade;
}

//*********************************************************************************
SEVERITY WorksessionTradesList::checkDuplicate ( Trade *pTrade, 
                                                 const BFDataGroupId &idDataGroup)
                                                
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("checkDuplicate"));

   bool bDuplicateTrade = false;
   m_bDuplicateTrade = false; // member variable used in PendingTradeErrorTrxn builder
   DString chkDuplicationTrade;

   getWorkSession ().getOption ( ifds::ChkDuplicationTrade, 
                                 chkDuplicationTrade, 
                                 idDataGroup, 
                                 false); 

   DString dupliRuleFieldList;
   getWorkSession ().getOption ( ifds::DupliRuleFieldList,  dupliRuleFieldList, idDataGroup, false); 

   dupliRuleFieldList.upperCase();
   int index = dupliRuleFieldList.length();

   DString dupliRuleMask[13] ;
   for (int i=0; i<index; ++i)
   {
	   dupliRuleMask[i] = dupliRuleFieldList.substr(0, 1);
	   dupliRuleFieldList.erase(0, 1);
   }

   if (chkDuplicationTrade == I_("Y"))
   {
      DString accountNum, 
         fundCode, 
         classCode;

      pTrade->getField (ifds::AccountNum, accountNum, idDataGroup);
      pTrade->getField (ifds::FromFund, fundCode, idDataGroup);
      pTrade->getField (ifds::FromClass, classCode, idDataGroup);

	  DString strKey;
	  accountNum.stripLeading ('0');
      if (!accountNum.empty())
      {
   //check the trading list
         BFObjIter iter ( *this, 
                        idDataGroup);
         iter.begin();
         while (!iter.end ())
         {
            Trade *pTrade_ = dynamic_cast <Trade*> (iter.getObject ());
      //want to skip the current trade from the list
            if (pTrade_ && pTrade_ != pTrade)
            {
			   DString tradeValue, tradeValue_ ;
			   bool bConfigurablefield = false ;
			   for (int i = 0; i< index; ++i )
			   {
				   if (dupliRuleMask[i] == I_ ("Y") )
				   {
						pTrade->getField (duplicateTradeList [i].configurableField, tradeValue, idDataGroup);
						pTrade_->getField (duplicateTradeList [i].configurableField, tradeValue_, idDataGroup);
						 if (tradeValue == tradeValue_ )
						 {
							 bConfigurablefield = true;
						 }
						 else 
						 {
							 bConfigurablefield = false;
							 break;	
						 }
				   }

			   }

               if ( bConfigurablefield )
               {
      //we have duplicate, check allocations if necessary
                  bDuplicateTrade = true;

                  //if allocated trade?
                  if ( fundCode.empty() && 
                     classCode.empty())
                  {
                     bDuplicateTrade = false; //no duplicate if fund/class empty, until we check allocations
      
                     std::set <DString> duplicateAlloc;
                     TradeFundAllocList *pFundAllocationList = NULL;
                     TradeFundAllocList *pFundAllocationList_ = NULL;

                     if ( pTrade->getFundAllocationList ( pFundAllocationList, 
                                                         idDataGroup) <= WARNING &&
                        pFundAllocationList &&
                        pTrade_->getFundAllocationList ( pFundAllocationList_, 
                                                         idDataGroup) <= WARNING &&
                        pFundAllocationList_)
                     {
                        BFObjIter iterAlloc (*pFundAllocationList, idDataGroup);
                     
                        while (!iterAlloc.end())
                        {
                           if (iterAlloc.getObject())
                           {
                              DString fundCode,
                                 classCode,
                                 percentage;
                           
                              iterAlloc.getObject()->getField (ifds::FundCode, fundCode, idDataGroup);
                              iterAlloc.getObject()->getField (ifds::ClassCode, classCode, idDataGroup);
                              iterAlloc.getObject()->getField (ifds::AllocPercentage, percentage, idDataGroup);
                              duplicateAlloc.insert (fundCode.strip() + classCode.strip() + percentage.strip());
                           }
                           ++iterAlloc;
                        }

                        BFObjIter iterAlloc_ ( *pFundAllocationList_, idDataGroup);
                        while (iterAlloc_.end())
                        {
                           if (iterAlloc_.getObject())
                           {
                              DString fundCode_,
                                 classCode_,
                                 percentage_;

                              iterAlloc_.getObject()->getField (ifds::FundCode, fundCode_, idDataGroup);
                              iterAlloc_.getObject()->getField (ifds::ClassCode, classCode_, idDataGroup);
                              iterAlloc_.getObject()->getField (ifds::AllocPercentage, percentage_, idDataGroup);
                              std::set <DString>::iterator iterDuplicateAlloc;
                              if (duplicateAlloc.find ( fundCode_.strip() + 
                                                      classCode_.strip() + 
                                                      percentage_.strip()) == duplicateAlloc.end() //found the end of the set?
                                 )
                              {
                                 bDuplicateTrade = false;//no duplicate alloc, it's over
                                 break;
                              }
                           }
                           ++iterAlloc_;
                        }
                     }
                  }
               }
               if (bDuplicateTrade)
               {
                  break; //if duplicate found
               }
            }
            ++iter;
         }
      //if not found in the memory, call the view to check the pending trades
         if (!bDuplicateTrade)
         {
            if (!fundCode.empty() && !classCode.empty())
            {
               DuplicateTradeCheck *pDuplicateTradeCheck = NULL;      
			   DString recId,transNum, indc,transType, amount, 
				   amountType, effectiveDate, settleCurrency,settleDate, toFundCode,toClassCode,toAccount;

			   pTrade->getField (ifds::Amount, amount, idDataGroup, true);
			   pTrade->getField (ifds::AmtType, amountType, idDataGroup);
			   pTrade->getField (ifds::EffectiveDate, effectiveDate, idDataGroup);
			   pTrade->getField (ifds::InterDetlRid, recId, idDataGroup);
			   pTrade->getField (ifds::TransNum, transNum, idDataGroup);
			   pTrade->getField (ifds::Indc, indc, idDataGroup);
			   pTrade->getField (ifds::SettleCurrency, settleCurrency, idDataGroup);
			   pTrade->getField (ifds::SettleDate, settleDate, idDataGroup);
			   pTrade->getField (ifds::ToFund, toFundCode, idDataGroup);
			   pTrade->getField (ifds::ToClass, toClassCode, idDataGroup);
			   pTrade->getField (ifds::AccountTo, toAccount, idDataGroup);
			   pTrade->getField (ifds::TradesTransType, transType, idDataGroup);

			   DString strKey,tradeValue;
			   strKey= I_("DuplicateTradeCheck_TransNum=") + transNum;
			   for (int i=0; i<index; ++i)
			   {
				   if (dupliRuleMask[i] == I_ ("Y") )
				   {
						strKey.append(duplicateTradeList[i].fieldValue);
						pTrade->getField (duplicateTradeList [i].configurableField, tradeValue, idDataGroup);
						strKey.append(tradeValue);
				   }
			   }

               pDuplicateTradeCheck = 
                     dynamic_cast<DuplicateTradeCheck*> (getObject (strKey, idDataGroup));
               if (!pDuplicateTradeCheck) //not found, try a lesser combination
               {
                  BFObjIter iterTransNum ( *this, 
                                          idDataGroup, 
                                          true, //match substrings
                                          BFObjIter::ITERTYPE::NON_DELETED
                                       );
                  if (iterTransNum.positionByKey (I_("DuplicateTradeCheck_TransNum=") + transNum))
                  {
                     iterTransNum.removeObjectFromMap (true);//so we not end-up with whole bunch of duplicate trade check objects
                  }
               }
               if (!pDuplicateTradeCheck)
               {
                  pDuplicateTradeCheck = new DuplicateTradeCheck (*this);
                  if ( pDuplicateTradeCheck->init ( accountNum, 
                                                   fundCode, 
                                                   classCode, 
                                                   transType, 
                                                   amountType, 
                                                   amount, 
                                                   effectiveDate,
												   indc,
												   settleCurrency,
												   settleDate,
												   toFundCode,
												   toClassCode,
												   toAccount,
												   recId) <= WARNING
                     )
                  {
                     setObject (pDuplicateTradeCheck, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
                  }
                  else
                  {
                     delete pDuplicateTradeCheck;
                     pDuplicateTradeCheck = NULL;
                  }

               }
               if (pDuplicateTradeCheck)
               {
                  bDuplicateTrade = pDuplicateTradeCheck->isDuplicate ();
               }
            }
         }
      }
      if (bDuplicateTrade)
      {
		  getErrMsg ( IFASTERR::DUPLICATE_ALREADY_EXIST, 
			  CND::ERR_DUPLICATE_TRADE, 
			  CND::WARN_DUPLICATE_TRADE, 
			  BF::HOST);

		  m_bDuplicateTrade = true; 		  
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//***************************************************************************************************
SEVERITY WorksessionTradesList::getErrMsgValue( DString dstrErrNum,       
								  const BFDataGroupId& idDataGroup, 
								  DString& dstrErrValue 
								)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getErrMsgValue" ) );

   if( _pErrMsgRulesList == NULL )
   {
      SEVERITY sevRtn = getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }

   if( _pErrMsgRulesList )
   {	   
      _pErrMsgRulesList->getEWIValue( dstrErrNum, idDataGroup, dstrErrValue);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//***************************************************************************************************
SEVERITY WorksessionTradesList::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                        const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
//fields on this list should not be updatable
   setFieldUpdated (idField, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY WorksessionTradesList::doValidateAll ( const BFDataGroupId &idDataGroup, 
                                                long lValidateGroup)
{   
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateAll"));

   DString batchName,
           mgmtCoIdOut,
           autoBatch;

   getWorkSession().getOption( ifds::AutoBatch, autoBatch, idDataGroup, false );

   if (autoBatch.asInteger () ==  AUTO_BATCHING)
      return GETCURRENTHIGHESTSEVERITY();	

   BFData queryData(ifds::DSTC0124_REQ);
   BFData *response = new BFData(ifds::DSTC0124_VW);

   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));  
   queryData.setElementValue (ifds::Track, I_("N"));
   queryData.setElementValue (ifds::Activity, NULL_STRING);

   if (BFDataBroker::getInstance()->
         receive ( DSTC_REQUEST::ACTIVE_BATCH, 
                   queryData, 
                   *response, 
                   DSTCRequestor(getSecurity())) <= WARNING
      )
   {
      response->getElementValue (ifds::rxBatchName, batchName);
      batchName.strip();
      delete response;
   }

   BFObjIter iter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   bool bBatchChanged = false;
   
   while (!iter.end())
   {
      if (iter.getObject()->isNew() && !iter.isDummy())
      {
         DString _batchName;

         iter.getObject()->getField (ifds::BatchName, _batchName, idDataGroup, false);
         _batchName.strip();
         if (_batchName != batchName)
         {
            iter.getObject()->setField (ifds::BatchName, batchName, idDataGroup, false, true);
            bBatchChanged = true;
            break;
         }
      }
      ++iter;
   }
   if (bBatchChanged)
   {
      ADDCONDITIONFROMFILE (CND::WARN_BATCH_NAME_HAS_BEEN_CHANGED);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void WorksessionTradesList::getField ( const BFFieldId &idField, 
                                       DString &fieldValue, 
                                       const BFDataGroupId &idDataGroup, 
                                       bool formattedReturn) const
{
   if (idField == ifds::PurchaseTotal)
   {
      fieldValue = const_cast <WorksessionTradesList*>(this)->calculatePurchaseTotal (idDataGroup);
   }
   else
   {
      BFCBO::getField (idField, fieldValue, idDataGroup, formattedReturn);
   }
}

//******************************************************************************
DString WorksessionTradesList::calculatePurchaseTotal (const BFDataGroupId &idDataGroup)
{
   //iterate through TRADES_LIST and calculate the total amount
   //if one entry is not 'Purchase' or the 'AmountType' is not Dollar, 
   //or if we have more currency types, the sum will be zero
   double totalPurchase = 0.0;
   BFObjIter iterTrades ( *this, 
                          idDataGroup, 
                          true, 
                          BFObjIter::ITERTYPE::NON_DELETED, 
                          false, 
                          true);
   DString firstSettleCurrency;
   bool bFirstTrade = false,
      bNotFirstTradeAnyMore = false;
   
   while (!iterTrades.end())
   {
      Trade *pTrade = dynamic_cast <Trade*> (iterTrades.getObject());
      
      if (pTrade)
      {
         DString amount, 
            transType, 
            amtType, 
            settleCurrency;

         pTrade->getField (ifds::Amount, amount, idDataGroup);
         pTrade->getField (ifds::TradesTransType, transType, idDataGroup);
         pTrade->getField (ifds::AmtType, amtType, idDataGroup);
         pTrade->getField (ifds::SettleCurrency, settleCurrency, idDataGroup);
         if (!bFirstTrade && !bNotFirstTradeAnyMore)
         {
//save the first value for settle currency, then check the other if they are the same
            bFirstTrade = true;
            firstSettleCurrency = settleCurrency;
         }
//if not the first trade, but the second, third, etc... trade,
//check if the other currencies are the same
         if (!bFirstTrade && bNotFirstTradeAnyMore)
         {
            if (settleCurrency != firstSettleCurrency)
            {
               totalPurchase = 0.0;
               break;
            }
         }
         if ( transType == TRADETYPE::PURCHASE &&
              amtType == I_("D"))
         {
            double dec_amount = DSTCommonFunctions::convertToDouble (amount);
            totalPurchase += dec_amount;
         }
         else
         {
            totalPurchase = 0.0;
            break;
         }
         if (bFirstTrade) 
         {
            bFirstTrade = false; //reset the first trade flag
            bNotFirstTradeAnyMore = true; //not anymore first trade
         }
      } //pTrade
      ++iterTrades;
   }
   return DSTCommonFunctions::doubleToDString (ifds::PurchaseTotal, totalPurchase);
}

//******************************************************************************
SEVERITY WorksessionTradesList::fromPending2Trade ( PendingTradeDetails *pPendingTrade, 
                                                    BFData *data,
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("fromPending2Trade"));
   //copy fields that do not match
   struct pending2trade_mapping
   {
      BFFieldId _pending;
      BFFieldId _trade;
   } 
   a_pending2trade_mapping [] = 
   {
      {ifds::rxAcctNum,             ifds::AccountNum},
      {ifds::TradeDate,             ifds::EffectiveDate},
      {ifds::TransType,             ifds::TradesTransType},
      {ifds::PayType2,              ifds::TradesPayType},
      {ifds::rxFundCode,            ifds::FromFund},
      {ifds::rxClassCode,           ifds::FromClass},
      {ifds::FundTo,                ifds::ToFund},
      {ifds::ClassToCode,           ifds::ToClass},
      {ifds::AmountType,            ifds::AmtType},
      {ifds::PendingRid,            ifds::InterDetlRid},
      {ifds::SplitCommRebookTransID,ifds::SplitCommRebookTransID},
      {ifds::BatchTrace,            ifds::Trace},
      {ifds::PayInstructExists,     ifds::PayInstructExists},
      {ifds::InvHisInvestId,        ifds::InvHisInvestId},
   };

   int num_fields = sizeof (a_pending2trade_mapping) / sizeof (pending2trade_mapping);

   for (int i = 0; i < num_fields; i++)
   {
      DString str;
      bool appendFlag = a_pending2trade_mapping [i]._trade == ifds::SplitCommRebookTransID || 
                        a_pending2trade_mapping [i]._trade == ifds::PayInstructExists || 
						a_pending2trade_mapping [i]._trade == ifds::InvHisInvestId ;

      pPendingTrade->getField (a_pending2trade_mapping [i]._pending, str, idDataGroup, false);
      data->setElementValue (a_pending2trade_mapping [i]._trade, str, appendFlag);
   }
   //remove the transnumber and display only the AWD object ID always..
   //the transNumber will be appended by the DSTCTradeTransBuilder always..
   DString dstrAWDFieldFlag, dstrExtTransNum, dstrTransNum, dstrNetWorkID;
   getWorkSession ().getOption (ifds::AWDFieldFlag, dstrAWDFieldFlag, BF::HOST,  false);
   data->getElementValue (ifds::ExtTransNum, dstrExtTransNum);
   data->getElementValue (ifds::NetworkID,   dstrNetWorkID);
   dstrNetWorkID.strip();
   if(dstrAWDFieldFlag == I_("Y") && dstrNetWorkID == I_("AWD"))
   {
   int iPos =  dstrExtTransNum.find_last_of(I_("-"));
   if(iPos != DString::npos )
	  dstrExtTransNum = dstrExtTransNum.left(iPos);
   data->setElementValue(ifds::ExtTransNum, dstrExtTransNum );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY WorksessionTradesList::fromHistory2Trade ( TransactionDetails *pHistoryTrade, 
                                                    BFData *data,
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("fromHistory2Trade"));

   struct history2trade_mapping
   {
      BFFieldId _history;
      BFFieldId _trade;
   } 
   a_history2trade_mapping [] = 
   {
      {ifds::AccountNum,            ifds::AccountNum},
      {ifds::TradeDate,             ifds::EffectiveDate},
      {ifds::TransType,             ifds::TradesTransType},
      {ifds::PayType2,              ifds::TradesPayType},
      {ifds::rxFundCode,            ifds::FromFund},
      {ifds::rxClassCode,           ifds::FromClass},
      {ifds::BrokerCode,            ifds::Broker},
      {ifds::BranchCode,            ifds::Branch},
      {ifds::SalesRepCode,          ifds::SlsrepCode},
   };

   int num_fields = sizeof (a_history2trade_mapping) / sizeof (history2trade_mapping);

   for (int i = 0; i < num_fields; i++)
   {
      DString str;
      bool appendFlag = a_history2trade_mapping [i]._trade == ifds::SplitCommRebookTransID || 
                        a_history2trade_mapping [i]._trade == ifds::PayInstructExists || 
						a_history2trade_mapping [i]._trade == ifds::InvHisInvestId;

      pHistoryTrade->getField (a_history2trade_mapping [i]._history, str, idDataGroup, false);
      data->setElementValue (a_history2trade_mapping [i]._trade, str, appendFlag);
   }

   DString strGrossOrNet;
   pHistoryTrade->getField( ifds::GrossOrNet, strGrossOrNet, idDataGroup, false );

   DString strAmount;
   if(strGrossOrNet == I_("Y"))
   {
      pHistoryTrade->getField( ifds::GrossAmt, strAmount, idDataGroup, false );
   }
   else
   {
      pHistoryTrade->getField( ifds::NetAmt, strAmount, idDataGroup, false );
   }
   data->setElementValue (ifds::GrossOrNet, strGrossOrNet);
   data->setElementValue (ifds::Amount, strAmount );
   //remove the transnumber and display only the AWD object ID always..
   //the transNumber will be appended by the DSTCTradeTransBuilder always..
   DString dstrAWDFieldFlag, dstrExtTransNum, dstrTransNum, dstrNetWorkID;
   getWorkSession ().getOption (ifds::AWDFieldFlag, dstrAWDFieldFlag, BF::HOST,  false);
   data->getElementValue (ifds::ExtTransNum, dstrExtTransNum);
   data->getElementValue (ifds::NetworkID,   dstrNetWorkID);
   if(dstrAWDFieldFlag == I_("Y") && dstrNetWorkID == I_("AWD"))
   {
   int iPos =  dstrExtTransNum.find_last_of(I_("-"));
   if(iPos != DString::npos )
	  dstrExtTransNum = dstrExtTransNum.left(iPos);
   data->setElementValue(ifds::ExtTransNum, dstrExtTransNum );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool WorksessionTradesList::isTradeAdded ( const DString &tradeKey,
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isTradeAdded"));
   bool bIsTradeAdded = false;
   BFObjIter iter ( *this, idDataGroup);

   if (iter.positionByKey (tradeKey))
   {
      DString accountNum, 
         accountNum_,
         transNum,
         transNum_,
         strKey;

      iter.getObject ()->getField (ifds::AccountNum, accountNum, idDataGroup);
      accountNum.stripLeading ('0').strip();
      if (_bRebook && iter.getKey().getActivity() == OBJ_ACTIVITY_NONE)
      {  
         iter.getObject ()->getField (ifds::AdjTransNum, transNum, idDataGroup);
      }
      else
      {
         iter.getObject ()->getField (ifds::TransNum, transNum, idDataGroup);
      } 
      transNum.stripLeading ('0').strip();
//decompose the given key
      I_CHAR *temp = const_cast<I_CHAR*> (tradeKey.c_str ());

      do
      {
         DString keyElement,
            keyValue;

         temp = parseIdiString (temp, keyElement, keyValue);
         if (keyElement == I_("TransNum"))
         {
            transNum_ = keyValue;
         }
         else if (keyElement == I_("Account"))
         {
            accountNum_ = keyValue;
         }
      } while (temp && temp != NULL_STRING && *temp);   
      bIsTradeAdded = accountNum == accountNum_ && transNum == transNum_;
   }
   return bIsTradeAdded;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/WorksessionTradesList.cpp-arc  $
// 
//    Rev 1.81   Jul 27 2012 08:28:00   wp040132
// P0199891 _FN01_Arrow_FAST_File
// 
//    Rev 1.80   Feb 01 2012 13:36:26   jankovii
// IN 2826242- Maturity/Interest Instruction on Trading Screen
// 
//    Rev 1.79   Nov 22 2010 13:23:34   jankovii
// PET175778 FN01 - Upstreaming Phase 2
// 
//    Rev 1.78   Jan 29 2010 14:14:38   popescu
//  ESG20 PET166183 FN03 CUSIP Rollover
// 
//    Rev 1.77   Sep 30 2009 06:51:56   dchatcha
// IN# 1595165 - Rebooking functionality where contr rcpt was issued not working properly.
// 
//    Rev 1.76   Sep 21 2009 16:23:52   popescu
// Incident 1845648 please add support for launching the trading screen if mapping for pruchase and redeem work types exists in the AWD Ini file.
// 
//    Rev 1.75   Sep 21 2009 16:10:58   popescu
// Incident 1845648 please add support for launching the trading screen if mapping for pruchase and redeem work types exists in the AWD Ini file.
// 
//    Rev 1.74   Aug 11 2009 14:00:02   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields
// 
//    Rev 1.73   May 27 2009 15:12:16   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.72   May 20 2009 11:03:14   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.71   May 19 2009 14:26:20   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.70   Jan 21 2009 11:54:50   jankovii
// PET5517_FN94_Foreign Exchange Allocated Capital Gains
// 
//    Rev 1.69   04 Nov 2008 13:28:50   kovacsro
// IN#1467118 - Related to in 1259584, modifying pending NET trades issue
// 
//    Rev 1.68   03 Sep 2008 09:04:36   kovacsro
// IN#1375331 - RcptStatus
// 
//    Rev 1.67   17 Jul 2008 14:24:36   kovacsro
// PET5517 FN60C Cancellation of Contribution Receipts - Rebooking
// 
//    Rev 1.66   17 Jul 2008 10:58:38   kovacsro
// PET5517 FN60C Cancellation of Contribution Receipts - Rebooking
// 
//    Rev 1.65   15 May 2008 16:34:22   kovacsro
// IN#1172388 - refresh BatchName on the screen, when it changes
// 
//    Rev 1.64   Sep 06 2007 17:21:10   popescu
// GAP 18 - added manual management fee rebate to manual dividend screen
// 
//    Rev 1.63   Nov 16 2006 11:12:10   popescu
// PET 2252. FN01 - mgmt fee rebate
// 
//    Rev 1.62   Sep 30 2006 00:55:02   popescu
// Incident 720294 - pay entity eff. dates
// 
//    Rev 1.61   Jul 26 2006 15:44:32   fengyong
// Incident #472462 - reject API trade.
// 
//    Rev 1.60   Jan 03 2006 16:35:14   popescu
// checked if account num is empty before calling a duplicate check - to fix a faulty view call in case RTS cramps
// 
//    Rev 1.59   Nov 08 2005 14:37:34   popescu
// Incident# 449242 - mapped the trace number from a pending trade to a trade
// 
//    Rev 1.58   Sep 22 2005 20:17:52   AGUILAAM
// IN 402898 - SplitCommRebookTransID to be used for rebook of single trades; fix for rebook button
// 
//    Rev 1.57   Sep 08 2005 13:35:22   popescu
// Incident#398878 - set the rebooked trade dirty 
// 
//    Rev 1.56   Sep 08 2005 12:59:24   popescu
// Incident# 398841 - activated rebook for rollovers
// 
//    Rev 1.55   Aug 29 2005 10:42:52   popescu
// Incident 390388 - wire order number should be blanked out for multiple rebooks
// 
//    Rev 1.54   Aug 17 2005 11:46:22   popescu
// PET 1235/01 rebook and cancelation - cleaned the code, 
// 
//    Rev 1.53   Aug 12 2005 10:29:18   Yingbaol
// Incident 377523 fix accoutable and reason code validation issue. 
// 
//    Rev 1.52   Aug 11 2005 10:26:34   popescu
// PET 1235 - Reeebok, few changes
// 
//    Rev 1.51   Jul 29 2005 14:34:38   Yingbaol
// PET1235,FN01: fix some issue for exchange
// 
//    Rev 1.50   Jul 15 2005 09:21:42   Yingbaol
// PET1235,FN01: don't check modify permission from view 54.
// 
//    Rev 1.49   Jul 09 2005 13:03:24   Yingbaol
// PET1235,FN01: add automatic withdraw
// 
//    Rev 1.48   Jul 08 2005 09:34:32   Yingbaol
// PET1235,FN01:transaction cancellation rebook
// 
//    Rev 1.47   May 30 2005 22:38:52   popescu
// Incident# 317930 - backed out fix
// 
//    Rev 1.46   May 27 2005 17:20:38   Fengyong
// #Incident 317930 - Sync up, Add function InitExist
// 
//    Rev 1.45   May 27 2005 10:44:10   popescu
// Incident # 319459 - fixed the Manual Dividend reset issue - also used WorkSessionTradesList for manual dividends; 
// 
//    Rev 1.44   Apr 22 2005 16:47:14   popescu
// Incident 290447 - fix 62 comp issue
// 
//    Rev 1.43   Apr 20 2005 18:00:06   popescu
// Incident 290447 - syncup - RESP account validation for new trades - check in for 62
// 
//    Rev 1.42   Apr 20 2005 17:59:22   popescu
// Incident 290447 - backed code out
// 
//    Rev 1.41   Apr 20 2005 10:47:36   porteanm
// Incident #278545, open-up effective date field on trade entry screen
// 
//    Rev 1.40   Apr 18 2005 15:45:02   porteanm
// Incident 290447 - RESP account validation for new trades.
// 
//    Rev 1.39   Apr 07 2005 17:40:06   popescu
// Incident #278545, open-up effective date field on trade entry screen
// 
//    Rev 1.38   Apr 07 2005 12:31:38   popescu
// Incident #278545, open-up effective date field on trade entry screen
// 
//    Rev 1.37   Apr 06 2005 11:23:54   popescu
// Incident # 280371, baycom/WKN/ISIN numbers should be picked-up from to fund/class when modifying a pending trade
// 
//    Rev 1.36   Mar 11 2005 14:32:08   popescu
// Incident # 262042, fix the pay type default for API/PW and AF's
// 
//    Rev 1.35   Mar 08 2005 08:13:16   popescu
// Incident # 260166, fixed appearance of PurchaseTotal field
// 
//    Rev 1.34   Feb 28 2005 10:56:12   Fengyong
// 253158 - dirty code fix for api trade, add tradspaytype as a parameter from process level.
// 
//    Rev 1.33   Jan 11 2005 18:53:24   popescu
// PTS 10037725, user should not be able to enter a trade with an erroneous account num
// 
//    Rev 1.32   Jan 07 2005 19:05:12   popescu
// PTS 10037553, fixed issues with modifying pending trades 
// 
//    Rev 1.31   Jan 06 2005 13:57:48   popescu
// PTS 10037503, trade object set to be dirty immediate after being created
// 
//    Rev 1.30   Dec 16 2004 19:06:36   popescu
// PET 1117/06, fixes for the case were account nums are invalid, or becomming invalid due to a change in Trade's context. Also, fixes for the order of keys when adding new trade
// 
//    Rev 1.29   Dec 09 2004 22:31:08   popescu
// PET 11717/06, fees and mod pending trades
// 
//    Rev 1.28   Dec 08 2004 17:50:16   popescu
// PET 1117/56, modify an aggregated order's pending trades list
// 
//    Rev 1.27   Dec 07 2004 21:20:46   popescu
// PET 1117/06, pending trades/fees fixes, add-ons
// 
//    Rev 1.26   Dec 07 2004 01:38:08   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.25   Nov 30 2004 20:10:40   popescu
// PET 1117/06
// 
//    Rev 1.24   Nov 30 2004 07:53:34   popescu
// PET 1117/06, made purchase total and OnBtnHistory active once again
// 
//    Rev 1.23   Nov 22 2004 13:09:50   popescu
// PET 1117/56. fees processing
// 
//    Rev 1.22   Nov 15 2004 14:57:54   popescu
// PET 1117/06, synch .NET changes
// 
//    Rev 1.20   Nov 06 2004 00:43:26   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.5   Nov 04 2004 17:41:52   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.4   Nov 02 2004 19:19:42   popescu
// PET 1117/06 Trade processing...
// 
//    Rev 1.3   Oct 28 2004 18:24:02   popescu
// PET 1117/06
// 
//    Rev 1.2   Oct 27 2004 11:27:10   popescu
// PET 1117/06
// 
//    Rev 1.1   Oct 21 2004 06:29:36   popescu
// PET 1117/06 - Trade processing work in progress..
// 
//    Rev 1.0   Oct 01 2004 19:30:08   popescu
// Initial revision.
// 
//    Rev 1.19   Jul 22 2004 13:45:32   HERNANDO
// PTS 10032389 - Recovered doPreSetField.
// 
//    Rev 1.18   May 17 2004 18:10:46   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.17   May 14 2004 17:38:04   popescu
// PET 905, fn 01, LSIF trade entry
// 
//    Rev 1.16   Jan 13 2004 16:06:54   popescu
// PET 910, System Integration Testing, Rel_55.0.0.2
// Fix involved allows back dated trades when modifying a pending trade; issue occurred due to a previous fix where the WorksessionTradesList is now retrieved using an 'idDataGroup' not equal with BF::HOST.
// 
//    Rev 1.15   Oct 27 2003 15:25:08   HSUCHIN
// added revision control. no change
 * 
 */