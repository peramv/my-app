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
// ^FILE   : TradeFundAlloc.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/04/02
//
// ^CLASS    : TradeFundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Trade, PendingTradeDetails and TransactionDetails fund allocation
//
//******************************************************************************
#include "stdafx.h"
#include "tradefundalloc.hpp"

#include "acctalloc.hpp"
#include "acqfeeinquiry.hpp"
#include "broker.hpp"
#include "funddetail.hpp"
#include "fundfeelist.hpp"
#include "fundmasterlist.hpp"
#include "fundtolist.hpp"
#include "mfaccount.hpp"
#include "mgmtcooptions.hpp"
#include "segtradeentryvalidation.hpp"
#include "seqfundvalidation.hpp"
#include "splitcommission.hpp"
#include "pendingtradedetails.hpp"
#include "splitcommissionlist.hpp"
#include "trade.hpp"
#include "tradeacctalloclist.hpp"
#include "transactiondetails.hpp"
#include "tradefundalloclist.hpp"
#include "tradefromfundalloc.hpp"
#include "tradefromfundalloclist.hpp"
#include "transfer.hpp"
#include "transfeelist.hpp"
#include <ifastdataimpl\dse_dstc0022_vw.hpp>
#include <ifastdataimpl\dse_dstc0054_vw.hpp>
#include <ifastdataimpl\dse_dstc0115_vw.hpp>
#include <ifastdataimpl\dse_dstc0115_req.hpp>
#include "mgmtco.hpp"
#include "errmsgruleslist.hpp"
#include "mfaccountholdinglist.hpp"
#include "acquisitionfee.hpp"
#include "xferinfee.hpp"

namespace
{
   const I_CHAR * const CLASSNAME                  = I_("TradeFundAlloc");
   const I_CHAR * const NO                         = I_("N");
   const I_CHAR * const YES                        = I_("Y");
   const I_CHAR * const OMNIBUS_ACCT               = I_("6");            // Omnibus account type
   const I_CHAR * const AMOUNT                     = I_("D");            // amount type
   const I_CHAR * const ACQFEE_INQUIRY_LIST        = I_("AcqFeeInquiryList");
   const I_CHAR * const FRONTENDLOAD               = I_("FEL");
   const double dSmallValue                        = .0000000001;
   const I_CHAR * const UNITS                      = I_("U");            // amount type
   const I_CHAR * HOLDINGS_LIST                    = I_("HoldingsList");

   const I_CHAR * const COMMISSION_TYPE_ZERO = I_ ("0");
   const I_CHAR * const COMMISSION_TYPE_ONE  = I_ ("1");
   const I_CHAR * const COMMISSION_TYPE_TWO  = I_ ("2");   
   const I_CHAR *  FEES_NOT_ALLOWED	         = I_("0,2,3");
}

namespace TRADETYPE
{
    extern CLASS_IMPORT I_CHAR * const PURCHASE;
    extern CLASS_IMPORT I_CHAR * const REDEMPTION;
    extern CLASS_IMPORT I_CHAR * const TRANSFER;
    extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
    extern CLASS_IMPORT I_CHAR * const TRANSFER_IN_2;
    extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
    extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT_2;
    extern CLASS_IMPORT I_CHAR * const EXCHANGE;
    extern CLASS_IMPORT I_CHAR * const EXCHANGE_IN;
    extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
    extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER;
    extern CLASS_IMPORT I_CHAR * const ONE_SIDE_TRADE;
    extern CLASS_IMPORT I_CHAR * const MGMT_FEE ;
    extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
    extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
}

namespace FEES
{
   extern CLASS_IMPORT const I_CHAR * ACQUISITION;
   extern CLASS_IMPORT const I_CHAR * EXCHANGE_IN;
   extern CLASS_IMPORT const I_CHAR * XFER_IN;

}
namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const CONTRACT_TYPE_AND_VERSION_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const TRADE_NOT_ALLOWED_TO_CANCEL;
   extern CLASS_IMPORT I_CHAR * const BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE;
   extern CLASS_IMPORT I_CHAR * const BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA;
   extern CLASS_IMPORT I_CHAR * const LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE;
}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_VALUE_CANNOT_BE_ZERO;
   extern const long ERR_ALLOCATION_NOT_ALLOWED;
   extern const long ERR_CONTRACT_TYPE_AND_VERSION_REQUIRED;
   extern const long WARN_CONTRACT_TYPE_AND_VERSION_REQUIRED;
   extern const long ERR_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT;
   extern const long WARN_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT;
   extern const long ERR_TRADE_NOT_ALLOWED_TO_CANCEL;
   extern const long WARN_TRADE_NOT_ALLOWED_TO_CANCEL;
   extern const long ERR_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE;
   extern const long WARN_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE;
   extern const long ERR_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA;
   extern const long WARN_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA;
   extern const long ERR_SEG_VALIDATION_BACKDATED_NOT_ALLOWED;
   extern const long ERR_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE;
   extern const long WARN_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE;
   extern const long ERR_FEETYPE_NOT_SUPPORTED;
   extern const long WARN_FEETYPE_NOT_SUPPORTED;
} 

namespace ifds
{  
//   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;
   extern CLASS_IMPORT const BFTextFieldId SplitComm;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId rxTransType;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId CurrencyName;
   extern CLASS_IMPORT const BFTextFieldId AcctTradeType;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId MinToFundAmount;
   extern CLASS_IMPORT const BFTextFieldId FromCurrency;
   extern CLASS_IMPORT const BFTextFieldId Initial;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercent;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFDecimalFieldId AcqFee;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId LoadType;
   extern CLASS_IMPORT const BFNumericFieldId TransNum;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId Broker;
   extern CLASS_IMPORT const BFTextFieldId Branch;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
   extern CLASS_IMPORT const BFTextFieldId SysCurrency;
   extern CLASS_IMPORT const BFTextFieldId DefltRedCodeFlag;
   extern CLASS_IMPORT const BFTextFieldId FullRedem;
   extern CLASS_IMPORT const BFDecimalFieldId SettledUnits;
   extern CLASS_IMPORT const BFDecimalFieldId SettledValue;
   extern CLASS_IMPORT const BFTextFieldId AllocAtCost;
   extern CLASS_IMPORT const BFTextFieldId GuaranteeCalcByRules;
   extern CLASS_IMPORT const BFTextFieldId FundClassTradeDate;
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
   extern CLASS_IMPORT const BFTextFieldId WarnValue1;
   extern CLASS_IMPORT const BFTextFieldId WarnValue2;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
   extern CLASS_IMPORT const BFTextFieldId CombinedLoadType; 
   extern CLASS_IMPORT const BFTextFieldId AcqFeeDefault;
   extern CLASS_IMPORT const BFTextFieldId AcqFeeDefault;
   extern CLASS_IMPORT const BFTextFieldId DisableFee4Alloc;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
   extern CLASS_IMPORT const BFNumericFieldId TransFeeRID;
   extern CLASS_IMPORT const BFTextFieldId FundServBroker;
   extern CLASS_IMPORT const BFTextFieldId SoftCapCheck;
}
 
namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE;
}


//******************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
// Field DD Id,               State Flags,                  Group Flags

   //cross edits 
   {ifds::MinToFundAmount,          BFCBO::NONE,                  0}, 
   {ifds::AllocPercent,             BFCBO::IMMEDIATE_VALIDATION,  0}, 
   {ifds::AllocAtCost,              BFCBO::IMMEDIATE_VALIDATION,  0},   
   {ifds::TransSeq,                 BFCBO::NONE,                  0}, 
   {ifds::TransId,                  BFCBO::NONE,                  0}, 
   {ifds::DistribDetlVer,           BFCBO::NONE,                  0}, 
   {ifds::DistribDetlRid,           BFCBO::NONE,                  0}, 
   {ifds::FeeType,                  BFCBO::NONE,                  0}, 
   {ifds::FeeRate,                  BFCBO::NONE,                  0}, 
   {ifds::TransFeeRID,              BFCBO::NONE,                  0}, 
   {ifds::SoftCapCheck,             BFCBO::IMMEDIATE_VALIDATION,  0}, 

};

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                  State Flags,      Group Flags
   //SegFundValidation CBO is also kept in Trade. When Trade creates a 100% FundAllocation
   //it will also set the  SegFundValidation for it by making a clone of its own - so the view
   //call is made only once, even though we have two disctinct SegFundValidation CBOs
   { I_("SplitCommissionList"),      BFCBO::NONE,        0},
   { I_("AcqFeeInquiry"),            BFCBO::NONE,        0},

};

static const int NUM_OBJECTS = sizeof(classObjectInfo) / sizeof(BFCBO::CLASS_OBJECT_INFO);

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
TradeFundAlloc::TradeFundAlloc(BFAbstractCBO &parent) : FundAlloc(parent), _bInitialSplitComm (false)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData(NUM_FIELDS,  (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo);

   addCrossEdit (ifds::MinToFundAmount, ifds::AccountNum);
   addCrossEdit (ifds::MinToFundAmount, ifds::FundCode);
   addCrossEdit (ifds::MinToFundAmount, ifds::ClassCode);
   addCrossEdit (ifds::MinToFundAmount, ifds::AllocAmtType);
   addCrossEdit (ifds::MinToFundAmount, ifds::AllocAmount);
   addCrossEdit (ifds::MinToFundAmount, ifds::EffectiveDate);

   addCrossEdit (ifds::AllocPercent, ifds::FundCode);
   addCrossEdit (ifds::AllocPercent, ifds::ClassCode);	
   addCrossEdit (ifds::AllocPercent, ifds::AllocAmount);   

   addCrossEdit (ifds::AllocAtCost, ifds::FundCode);
   addCrossEdit (ifds::AllocAtCost, ifds::ClassCode);
   addCrossEdit (ifds::AllocAtCost, ifds::AllocPercentage);
   addCrossEdit (ifds::AllocAtCost, ifds::AllocAmount); 
       
   addCrossEdit(ifds::SoftCapCheck, ifds::FundCode);
   addCrossEdit(ifds::SoftCapCheck, ifds::ClassCode);
}

//******************************************************************************
TradeFundAlloc::~TradeFundAlloc(void)
{
   TRACE_DESTRUCTOR(CLASSNAME);
}
//******************************************************************************
SEVERITY TradeFundAlloc::initNew ( const BFDataGroupId& idDataGroup,
                                   const DString &dstrTrack, 
                                   const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   setObjectNew();
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TradeFundAlloc::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
   FundAlloc::doInitWithDefaultValues (idDataGroup);

   DString newSubst = removeItemFromAllSubtList (ifds::FeeType, I_("2"), idDataGroup); //Scale
   newSubst = removeItemFromSubtList (newSubst, I_("3")); //Tier
   newSubst = removeItemFromSubtList (newSubst, I_("4")); //Tier By Threshold
   setFieldAllSubstituteValues(ifds::FeeType, idDataGroup, newSubst);

   DString dstrAcqFeeDefault;
   getWorkSession().getOption (ifds::AcqFeeDefault, dstrAcqFeeDefault, BF::HOST, false);
   DString dstrDisableFee4Alloc;
   getWorkSession().getOption (ifds::DisableFee4Alloc, dstrDisableFee4Alloc, BF::HOST, false);

   dstrDisableFee4Alloc = I_("Y"); //forcing the allocation level rate to be read only
   
   setFieldReadOnly(ifds::FeeType, idDataGroup, dstrDisableFee4Alloc == I_("Y"));  
   setFieldReadOnly(ifds::FeeRate, idDataGroup, dstrDisableFee4Alloc == I_("Y"));

   setAmountField (idDataGroup); 
   setFieldNoValidate (ifds::RecordType, I_("TO"), idDataGroup, false, true, false, false);
   setFieldNoValidate (ifds::FeeType, I_("1"), idDataGroup, false, true, false, false);

} 

//******************************************************************************
SEVERITY TradeFundAlloc::updateCommissionDefault(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("updateCommissionDefault"));

   DString commissionType;

   getWorkSession().getOption (ifds::CommissionType, commissionType, BF::HOST, false);

   if(commissionType == COMMISSION_TYPE_ZERO)
   {

   }
   else 
   {

   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::initExisting (const BFData &data) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initExisting"));
 
   attachDataObject(const_cast< BFData & >(data), false, true); 
   setFundNumber (BF::HOST);//because ToFundNumber doesn't come from the host
   setAllocFields (BF::HOST);

   DString newSubst = removeItemFromAllSubtList (ifds::FeeType, I_("2"), BF::HOST); //Scale
   newSubst = removeItemFromSubtList (newSubst, I_("3")); //Tier
   newSubst = removeItemFromSubtList (newSubst, I_("4")); //Tier By Threshold
   setFieldAllSubstituteValues(ifds::FeeType, BF::HOST, newSubst);

   DString dstrAcqFeeDefault;
   getWorkSession().getOption (ifds::AcqFeeDefault, dstrAcqFeeDefault, BF::HOST, false);

   DString dstrDisableFee4Alloc;
   getWorkSession().getOption (ifds::DisableFee4Alloc, dstrDisableFee4Alloc, BF::HOST, false);

   dstrDisableFee4Alloc = I_("Y"); //forcing the allocation level rate to be read only

   setFieldReadOnly(ifds::FeeType, BF::HOST, dstrDisableFee4Alloc == I_("Y"));
   setFieldReadOnly(ifds::FeeRate, BF::HOST, dstrDisableFee4Alloc == I_("Y"));

   DString dstrSplitComm;

   getField(ifds::SplitComm, dstrSplitComm, BF::HOST, false);
   _bInitialSplitComm = (dstrSplitComm == YES);
   //setFieldNoValidate(ifds::Default, NO, BF::HOST);
   setFieldNoValidate(ifds::RecordType, I_("TO"), BF::HOST, false, true, false, false);
   setAmountField (BF::HOST);
   clearUpdatedFlags(BF::HOST);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeFundAlloc::getSplitCommissionList ( SplitCommissionList *&rpSplitCommissionList, 
                                                  const BFDataGroupId &idDataGroup, 
                                                  bool bCreate /*= true*/,
                                                  bool bGetDefault /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getSplitCommissionList")); 
   DString splitComm;

   getField (ifds::SplitComm, splitComm, idDataGroup);
   bCreate = bCreate && splitComm == Y;

   rpSplitCommissionList = 
         dynamic_cast <SplitCommissionList *> (getObject (I_("SplitCommissionList"), idDataGroup));
  
   if (bCreate)
   {
      if ( rpSplitCommissionList || //exists
           !_bInitialSplitComm)     //transaction doesn't have splits initially (from pending/history)
      {
         //completely remove the list
         if ( rpSplitCommissionList &&  //exists
              !_bInitialSplitComm &&    //doesn't exist initially (from pending/history)
              bGetDefault)               //force a refresh, 
                                                    //or split comm did not exist before 
                                                    //(now the set of data changed, so try again to get split comms)
         {
            BFObjIter iter (*this, idDataGroup);

            iter.positionByKey (I_("SplitCommissionList"));
            if (!iter.end())
            {
               iter.removeObjectFromMap (true);
               rpSplitCommissionList = NULL;
            }
         }
         if (rpSplitCommissionList && _bInitialSplitComm && bGetDefault)
         {
//list exists due to a prior call to 151, and now needs to be refreshed 
//send deletes to back-end;
            rpSplitCommissionList->deleteSplitCommList (idDataGroup);
//no more initial splits, the one read by 151 are gone
            _bInitialSplitComm = false;
         }
//call 158
         if (!rpSplitCommissionList || (_bInitialSplitComm && bGetDefault))
         {
            Trade *pTrade = dynamic_cast<Trade*> (getTopLevelCBO());

            assert (pTrade);
            DString accountNum, accountTo, fund, fundTo, classCode, classTo,exchRate,
               PUD, flatPrcnt, inPayType, iAmount, inTransType, effectiveDate,tradeInDate,dstrAmount,
               inGrossNet, brokerCode, branchCode, slsRepCode, settleCurrency;

            getTopLevelAllocList()->getField (ifds::TransType, inTransType, idDataGroup, false);
            getField (ifds::AllocAmount, iAmount, idDataGroup, false);
            if ( inTransType == TRADETYPE::TRANSFER || 
                 inTransType == TRADETYPE::EXCHANGE ||
                 inTransType == TRADETYPE::INTER_CLASS_SWITCH)
            {
               pTrade->getField (ifds::FromFund, fund, idDataGroup, false); 
               pTrade->getField (ifds::FromClass, classCode, idDataGroup, false);
               getField (ifds::FundCode, fundTo, idDataGroup, false);       
               getField (ifds::ClassCode, classTo, idDataGroup, false);
            } 
            else 
            {
               getField (ifds::FundCode, fund, idDataGroup, false); 
               getField (ifds::ClassCode, classCode, idDataGroup, false);
               pTrade->getField (ifds::ToFund, fundTo, idDataGroup, false);
               pTrade->getField (ifds::ToClass, classTo, idDataGroup, false); 
            }

            if (pTrade && !fund.empty() && !classCode.empty()) //do not bother to call 158 if fund and class empty
            {
               pTrade->getField (ifds::AccountNum, accountNum, idDataGroup, false);
               pTrade->getField (ifds::AccountTo, accountTo, idDataGroup, false);
               //pTrade->getField (ifds::AmtType, PUD, idDataGroup, false);
               pTrade->getField (ifds::FlatPercent, flatPrcnt, idDataGroup, false);
               pTrade->getField (ifds::TradesPayType, inPayType, idDataGroup, false);
               
               pTrade->getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);
			   pTrade->getField (ifds::TradeInDate, tradeInDate, idDataGroup, false);
               pTrade->getField (ifds::GrossOrNet, inGrossNet, idDataGroup, false);
               pTrade->getField (ifds::Broker, brokerCode, idDataGroup, false);
               pTrade->getField (ifds::Branch, branchCode, idDataGroup, false);
               pTrade->getField (ifds::SlsrepCode, slsRepCode, idDataGroup, false);

               DString roaAmount;
               pTrade->getROARelatedFields (roaAmount, PUD, settleCurrency, exchRate, idDataGroup);

              
			   DString rdrAdvice;              
               pTrade->getField (ifds::RDRAdvice, rdrAdvice, idDataGroup, false);

			   DString investTerm;
               
               pTrade->getField (ifds::InvestTerm, investTerm, idDataGroup, false);

               if (PUD != I_("D"))
               {
                  pTrade->calculateEstimatedAllocAmount (iAmount, idDataGroup);	
               }

               // what is this roa about ??? ivanka
               double dRoa = DSTCommonFunctions::convertToDouble(roaAmount);
               dstrAmount = dRoa == 0.0 ? iAmount: roaAmount;

               if (!rpSplitCommissionList) //it is possible that we only need a refresh
               {
                  rpSplitCommissionList = new SplitCommissionList(*this);
               }
//call the default split commission view
               if ( rpSplitCommissionList->init ( accountNum, 
                                                  accountTo, 
                                                  fund,
                                                  fundTo, 
                                                  classCode, 
                                                  classTo, 
                                                  PUD, 
                                                  flatPrcnt,//I_("N"), //flatprcnt
                                                  inPayType,
                                                  dstrAmount, 
                                                  inTransType, 
                                                  effectiveDate, 
                                                  inGrossNet, 
                                                  brokerCode,
                                                  branchCode, 
                                                  slsRepCode, 
                                                  settleCurrency, 
                                                  NULL_STRING, //let the list itself decide the value of the record type
                                                  exchRate,
                                                  investTerm,
												  rdrAdvice,
												  tradeInDate,
                                                  idDataGroup) <= WARNING)
               {
                  setObject ( rpSplitCommissionList, 
                              I_("SplitCommissionList"), 
                              OBJ_ACTIVITY_NONE, 
                              idDataGroup);
                  if (!rpSplitCommissionList->hasSplits())
                  {
                     setField (ifds::SplitComm, NO, idDataGroup, false);
                  }
                  //
                  //override the amount return from view
                  //Incident 340683
                  //
                  rpSplitCommissionList->setField (ifds::Amount, iAmount, idDataGroup, true);
               }
            }
            else
            {
               delete rpSplitCommissionList;
               rpSplitCommissionList = NULL;
            }
         }
      }
      else //call 151
      {
         fetchSplitCommisionListUsingParentCBO (rpSplitCommissionList, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::fetchSplitCommisionListUsingParentCBO ( SplitCommissionList *&rpSplitCommissionList, 
                                           const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initSplitCommisionList"));

   DString dstrTransNum, 
           dstrTransSeq, 
           dstrAccountNum, 
           dstrTransType, 
           dstrFund, 
           dstrClass, 
           dstrBrokerCode, 
           dstrBranchCode, 
           dstrSalesRepCode, 
           dstrEffectiveDate,
           dstrTransId,
		   dstrRDRAdvice;
   BFCBO *pParentCBO = getTopLevelCBO();

   //get the common fields
   getTopLevelAllocList()->getField (ifds::TransType, dstrTransType, idDataGroup, false);
   getTopLevelAllocList()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   getField (ifds::TransSeq, dstrTransSeq, idDataGroup, true);
   // should get the Fund and Class from TradeFundAlloc object since the 
   //Trade/Pending Trade may have a blank fund/class if the trade is an allocation trade
   getField(ifds::FundCode, dstrFund, idDataGroup, true);
   getField(ifds::ClassCode, dstrClass, idDataGroup, true);
   // If the split has never been downloaded.
   if(!rpSplitCommissionList && dynamic_cast<Trade*>(pParentCBO))
   {
      Trade* pTrade = dynamic_cast<Trade*>(pParentCBO);

      pTrade->getField (ifds::TransNum, dstrTransNum, idDataGroup, true);
	  pTrade->getField (ifds::Broker, dstrBrokerCode, idDataGroup, true);          
	  pTrade->getField (ifds::Branch, dstrBranchCode, idDataGroup, true);
      pTrade->getField (ifds::SlsrepCode, dstrSalesRepCode, idDataGroup, true);
      pTrade->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, true);
	  pTrade->getField (ifds::RDRAdvice, dstrRDRAdvice, idDataGroup, false);
      if (pTrade->isRebook())
      {
         //check if this is an 100 % allocated trade, if yes get the trans id from the trade object
         //get the parent list
         BFCBO *pParentList = getParent();
         assert (pParentList);

         BFObjIter iter ( *pParentList, 
                           idDataGroup, 
                           false, 
                           BFObjIter::ITERTYPE::NON_DELETED);
         iter.begin();
         int iAllocNum = iter.getNumberOfItemsInList();
         if (iAllocNum > 1)
         {
            getField (ifds::TransId, dstrTransId, idDataGroup, true);
         }
         else
         {
            // IN 402898 - sync up from rel64; use new field "SplitCommRebookTransID from view 54 to get splits, if it exists
            pTrade->getField (ifds::SplitCommRebookTransID, dstrTransId, idDataGroup, true);
         }
      } 
      rpSplitCommissionList = new SplitCommissionList (*this);
   } 
   else if (!rpSplitCommissionList && dynamic_cast<PendingTradeDetails*>(pParentCBO))
   {
      PendingTradeDetails* pPendingTradeDetails = dynamic_cast<PendingTradeDetails*>(pParentCBO);
      
      pPendingTradeDetails->getField (ifds::TransNum, dstrTransNum, idDataGroup, true);
      pPendingTradeDetails->getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup, true);
      pPendingTradeDetails->getField (ifds::BranchCode, dstrBranchCode, idDataGroup, true);
      pPendingTradeDetails->getField (ifds::SlsrepCode, dstrSalesRepCode, idDataGroup, true);
      pPendingTradeDetails->getField (ifds::TradeDate, dstrEffectiveDate, idDataGroup, true);
      rpSplitCommissionList = new SplitCommissionList (*this);
   } 
   else if (!rpSplitCommissionList && dynamic_cast<TransactionDetails*>(pParentCBO))
   {
      TransactionDetails* pTransactionDetails = dynamic_cast<TransactionDetails*>(pParentCBO);

      pTransactionDetails->getField (ifds::TransNum, dstrTransNum, idDataGroup, true);
      pTransactionDetails->getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup, true);
      pTransactionDetails->getField (ifds::BranchCode, dstrBranchCode, idDataGroup, true);
      pTransactionDetails->getField (ifds::SalesRepCode, dstrSalesRepCode, idDataGroup, true);
      pTransactionDetails->getField (ifds::TradeDate, dstrEffectiveDate, idDataGroup, true);
	  pTransactionDetails->getField (ifds::TransId, dstrTransId, idDataGroup, true);//Change done for REQ0061274
      //getField (ifds::TransId, dstrTransId, idDataGroup, true);
      rpSplitCommissionList = new SplitCommissionList (*this);
   }
   //calls view 151
   if (rpSplitCommissionList->init ( dstrTransNum, 
                                     dstrTransSeq, 
                                     dstrTransType, 
                                     dstrAccountNum,
                                     dstrFund, 
                                     dstrClass, 
                                     dstrBrokerCode, 
                                     dstrBranchCode, 
                                     dstrSalesRepCode, 
                                     dstrEffectiveDate,
                                     dstrTransId,
									 dstrRDRAdvice) <= WARNING)
   {
      setObject (rpSplitCommissionList, I_("SplitCommissionList"), OBJ_ACTIVITY_NONE, idDataGroup); 
      getMaxFeeRate(rpSplitCommissionList,idDataGroup);
   }
   else
   {
      delete rpSplitCommissionList;
      rpSplitCommissionList = NULL;
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//****************************************************************************************************************
SEVERITY TradeFundAlloc::getMaxFeeRate(SplitCommissionList *&rpSplitCommissionList,const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMaxFeeRate"));

	BFCBO *pParentCBO = getTopLevelCBO();
	Trade* pTrade = dynamic_cast<Trade*>(pParentCBO);
//	assert (pTrade);

	DString accountNum, accountTo, fund, fundTo, classCode, classTo,exchRate,
		PUD, flatPrcnt, inPayType, iAmount, inTransType, effectiveDate,dstrAmount,tradeInDate,
		inGrossNet, brokerCode, branchCode, slsRepCode, settleCurrency;

	getField (ifds::FundCode, fund, idDataGroup, false); 
	getField (ifds::ClassCode, classCode, idDataGroup, false);

	if (pTrade && !fund.empty() && !classCode.empty()) //do not bother to call 158 if fund and class empty
	{
		pTrade->getField (ifds::AccountNum, accountNum, idDataGroup, false);
		pTrade->getField (ifds::AccountTo, accountTo, idDataGroup, false);
		pTrade->getField (ifds::ToFund, fundTo, idDataGroup, false);
		pTrade->getField (ifds::ToClass, classTo, idDataGroup, false); 
		pTrade->getField (ifds::FlatPercent, flatPrcnt, idDataGroup, false);
		pTrade->getField (ifds::TradesPayType, inPayType, idDataGroup, false);
		getTopLevelAllocList()->getField (ifds::TransType, inTransType, idDataGroup, false);
		getField (ifds::AllocAmount, iAmount, idDataGroup, false);
		if ( inTransType == TRADETYPE::TRANSFER || 
			 inTransType == TRADETYPE::EXCHANGE ||
             inTransType == TRADETYPE::INTER_CLASS_SWITCH)
		{
			pTrade->getField (ifds::FromFund, fund, idDataGroup, false); 
			pTrade->getField (ifds::FromClass, classCode, idDataGroup, false);
			getField (ifds::FundCode, fundTo, idDataGroup, false); 
			getField (ifds::ClassCode, classTo, idDataGroup, false);
		}
		pTrade->getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);
		pTrade->getField (ifds::TradeInDate, tradeInDate, idDataGroup, false);
		pTrade->getField (ifds::GrossOrNet, inGrossNet, idDataGroup, false);
		pTrade->getField (ifds::Broker, brokerCode, idDataGroup, false);
		pTrade->getField (ifds::Branch, branchCode, idDataGroup, false);
		pTrade->getField (ifds::SlsrepCode, slsRepCode, idDataGroup, false);

		DString roaAmount;
		pTrade->getROARelatedFields (roaAmount, PUD, settleCurrency, exchRate, idDataGroup);

		DString investTerm;
		pTrade->getField (ifds::InvestTerm, investTerm, idDataGroup, false);

		if (PUD != I_("D"))
		{
			pTrade->calculateEstimatedAllocAmount (iAmount, idDataGroup);	
		}

		double dRoa = DSTCommonFunctions::convertToDouble(roaAmount);
		dstrAmount = dRoa == 0.0 ? iAmount: roaAmount;

		//call the default split commission view
		SplitCommissionList lpSplitCommissionList(*this);
		if (lpSplitCommissionList.init( accountNum,
										accountTo,
										fund,
										fundTo,
										classCode,
										classTo,
										PUD,
										flatPrcnt,
										inPayType,
										iAmount,
										inTransType,
										effectiveDate,
										inGrossNet, 
										brokerCode,
										branchCode,
										slsRepCode,
										settleCurrency,
										NULL_STRING, //record type 
										I_("0.0"), // exchange rate for systematic should be zero,
										NULL_STRING,NULL_STRING,tradeInDate,idDataGroup) <= WARNING)
		{
			DString maxFeeRate;
			lpSplitCommissionList.getField(ifds::MaxFeeRate, maxFeeRate, idDataGroup, false);
			rpSplitCommissionList->setField(ifds::MaxFeeRate, maxFeeRate, idDataGroup);
		}
	}
	return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY TradeFundAlloc::doApplyRelatedChanges ( const BFFieldId& idField, 
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
   if (FundAlloc::doApplyRelatedChanges(idField, idDataGroup) <= WARNING)
   {
      if ( idField == ifds::FundCode || 
           idField == ifds::ClassCode)
      {
         Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO());

         DString dstrFundCode;
         DString dstrClassCode;

         getField (ifds::FundCode, dstrFundCode, idDataGroup, false);       
         getField (ifds::ClassCode, dstrClassCode, idDataGroup, false);

         if(pTrade && !pTrade->_bInitPending && dstrFundCode.stripAll() != NULL_STRING && dstrClassCode.stripAll() != NULL_STRING)
         {//force refresh 
            SplitCommissionList *pSplitCommissionList = NULL;
            getSplitCommissionList (pSplitCommissionList, idDataGroup, true, true);
         }
         refreshSplitCommFlag (idDataGroup);
//         if (!pTrade || !pTrade->IsInitPending()) //avoid infinite recursive calls for trades that don't have alloc
         {         
            calculateAquisitionFeeCommission(idDataGroup);
         }
      }
      else if (idField == ifds::AllocAmount) 
      {
         //When the amount changes we should check to see if the fund/class allocation is allowed.
         //This is used to check trades with default allocation/ams allocations
         setFieldValid (ifds::MinToFundAmount, idDataGroup, false);
         //
         //incident  338408 
         //
         Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO());

         if (pTrade) 
         {
            DString dstrROAAmount;

            pTrade->getField (ifds::ROAAmount, dstrROAAmount, idDataGroup, false );			
            if ( !pTrade->_bInitPending //&& //should not refresh if we are in copy pending...
                  //pTrade->isROAApplicable (idDataGroup) &&  
                  //DSTCommonFunctions::convertToDouble (dstrROAAmount) == 0.0
                  ) 
            {               
               SplitCommissionList *pSplitCommissionList = NULL;

               if ( getSplitCommissionList (pSplitCommissionList, idDataGroup, true, true) <= WARNING &&
                    pSplitCommissionList)
               {
                  //notify the trans fee list of the change
                  TransFeeList *pTransFeeList = NULL;
                  DString strKey = I_("TransFeeList");

                  pTransFeeList = dynamic_cast <TransFeeList *> (pTrade->getObject (strKey, idDataGroup));
                  if ( //pTrade->getTransFeeList (pTransFeeList, idDataGroup, false) <= WARNING &&
                       pTransFeeList)
                  {
                     pTransFeeList->setForcingRefresh(true);
                     pTransFeeList->onNotify (FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_("ForceRefresh"));
                  }
               }
            }
         }
         setFieldValid(ifds::FundClass, idDataGroup, false);
         setFieldValid(ifds::SoftCapCheck, idDataGroup, false);
         calculateAquisitionFeeCommission(idDataGroup);
         setAmountField (idDataGroup);
      }
      else if ( ifds::EffectiveDate == idField )
      {
         setFieldValid (ifds::FundClass,  idDataGroup, false);
         setFieldValid (ifds::SoftCapCheck,  idDataGroup, false);
      }
      else if ( ifds::FeeRate == idField )
      {
         DString feeRate;
         getField(idField, feeRate, idDataGroup);
         DString origFeeRate(feeRate);

         DString dstrCommissionType;
         getWorkSession().getOption (ifds::CommissionType,   dstrCommissionType,   BF::HOST, false);         
         if(dstrCommissionType.stripAll() != I_("0") && hasPurchExchgFrontEndLoadCommission(idDataGroup))
         {
            DString dstrSFACRate (NULL_STRING);
            bool baseCommApplicable = false;
            assert (getParent() && getParent()->getParent());
//            Trade *pTrade = dynamic_cast <Trade*> (getTopLevelCBO());
            DString dstrFundCode;
            DString dstrClassCode;
            getField(ifds::FundCode,  dstrFundCode, idDataGroup, false);
            getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

            if (isBaseCommissionApplicableAndGetSFACRate (baseCommApplicable, dstrSFACRate, idDataGroup, dstrFundCode, dstrClassCode) <= WARNING 
               && baseCommApplicable)
            {
               DString baseCommission = SplitCommissionList::calculateBaseCommission (feeRate, dstrSFACRate);

               if (!baseCommission.empty()) 
               {
                  feeRate = baseCommission;
               }
            }
            SplitCommissionList *pSplitCommissionList = NULL;
   
            if ( getSplitCommissionList (pSplitCommissionList, idDataGroup, true, false) <= WARNING && 
               pSplitCommissionList) 
            { 
               pSplitCommissionList->setField(ifds::Rate, feeRate, idDataGroup);	
               if(idDataGroup == BF::HOST) //doApplyRelated changes does nothing for BF::HOST
                  pSplitCommissionList->applyRateRelatedChanges (idDataGroup);
            }
         }
         
         //Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO());
         //if (pTrade && !pTrade->IsInitPending()) //avoid infinite recursive calls for trades that don't have alloc
         //   updateTransFeeAcqFeeRate(origFeeRate, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY TradeFundAlloc::calculateAquisitionFeeCommission(const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("calculateAquisitionFeeCommission"));
   bool bIsApplicable = false;

   DString dstrFundCode;
   DString dstrClassCode;

   getField(ifds::FundCode, dstrFundCode, idDataGroup);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup);
   
   bIsApplicable = hasPurchExchgFrontEndLoadCommission(idDataGroup);

   if(bIsApplicable && idDataGroup != BF::HOST)
   {

      Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO());
      TransFeeList* pTransFeeList = NULL;

      if(pTrade && pTrade->getTransFeeList(pTransFeeList, idDataGroup, false) && pTransFeeList)
      {
         TransFee* pAcquisitionFee = NULL;

         DString dstrCommissionType;
         getWorkSession().getOption (ifds::CommissionType,   dstrCommissionType,   BF::HOST, false);         
         DString dstrTransType;
         getTopLevelAllocList()->getField (ifds::TransType, dstrTransType, idDataGroup, false);

         if(DSTCommonFunctions::codeInList (dstrTransType, TRADETYPE::PURCHASE_LIKE))
         {
            pTransFeeList->getTransFee(FEES::ACQUISITION, pAcquisitionFee, idDataGroup);
         } 
         else if(DSTCommonFunctions::codeInList (dstrTransType, TRADETYPE::EXCHANGE_LIKE))
         {
            if(dstrCommissionType.stripAll() != I_("0"))
            {
               pTransFeeList->getTransFee(FEES::XFER_IN, pAcquisitionFee, idDataGroup);
            }
            else
            {
               pTransFeeList->getTransFee(FEES::EXCHANGE_IN, pAcquisitionFee, idDataGroup);
            }
         }

         if(pAcquisitionFee)
         {
            DString dstrFeeRate;
            DString dstrFeeType;
            pAcquisitionFee->getField(ifds::FeeRate, dstrFeeRate, idDataGroup, false);
            pAcquisitionFee->getField(ifds::FeeType, dstrFeeType, idDataGroup, false);
            setFieldNoValidate(ifds::FeeRate, dstrFeeRate, idDataGroup, false); 
            setFieldNoValidate(ifds::FeeType, dstrFeeType, idDataGroup, false); 
         }
         else if(dstrCommissionType != I_("0"))
         {
            setFieldNoValidate(ifds::FeeRate, I_("0"), idDataGroup, false);   
            setFieldNoValidate(ifds::FeeType, I_("1"), idDataGroup, false); 
         }
      };


   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::getAcqFeeDefault (AcqFeeInquiry *&pAcqFeeInquiry, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAcqFeeDefault"));
   
   Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO()); 
   if (SplitCommission::isTypeZERO (getWorkSession()) && pTrade)
   {
      DString transType;
      DString accountNum;
      DString fromFund;
      DString fromClass;
      DString toFund;
      DString toClass;
      DString fundCode;
      DString classCode;
		DString toAccountNum;
	   DString toAcctTaxType;
	  DString tradeInDate;
   
      pTrade->getField (ifds::TransType,  transType, idDataGroup);
      pTrade->getField (ifds::FromFund,   fromFund, idDataGroup);
      pTrade->getField (ifds::FromClass,  fromClass, idDataGroup);
      pTrade->getField (ifds::AccountNum, accountNum, idDataGroup);
      
		if (pTrade->isPurchaseLike(idDataGroup))
      {
         fundCode = fromFund;
         classCode = fromClass;	
      }
      else if ( pTrade->isExchangeLike(idDataGroup))
      {
         pTrade->getField (ifds::AccountTo, toAccountNum, idDataGroup);
         pTrade->getField (ifds::ToFund, toFund, idDataGroup); 
         pTrade->getField (ifds::ToClass, toClass, idDataGroup);
		 pTrade->getField (ifds::TradeInDate, tradeInDate, idDataGroup);
         fundCode = toFund;
         classCode = toClass;

			if (toAccountNum != accountNum)
			{
				MFAccount *pMFAccountTo = NULL;

				if ( !toAccountNum.empty() &&
						getWorkSession().getMFAccount (idDataGroup, toAccountNum, pMFAccountTo) <= WARNING && 
						pMFAccountTo)
				{
					pMFAccountTo->getField (ifds::TaxType, toAcctTaxType, idDataGroup);
				}
			}
      }

      MFAccount *pMFAccount = NULL;

      if (!accountNum.empty() && !fromFund.empty() && !fromClass.empty() && 
          getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && 
          pMFAccount)
      {
         FundDetail *pFundDetail = NULL;
      
         if (getWorkSession().getFundDetail (fundCode, classCode, idDataGroup, pFundDetail) && pFundDetail)
         {
            DString fundCurrency;
            DString settleCurrency;
            DString tradeDate;
            DString amount;
            DString amtType;
            DString taxType;
            DString brokerCode;
         
            pFundDetail->getField (ifds::Currency, fundCurrency, idDataGroup, false);
            pTrade->getField (ifds::SettleCurrency, settleCurrency, idDataGroup, false);
            if (settleCurrency.empty())
            {
               settleCurrency = fundCurrency;
            }
            pMFAccount->getField (ifds::TaxType, taxType, idDataGroup); 
            taxType.strip().upperCase();
            pMFAccount->getField(ifds::BrokerCode, brokerCode, idDataGroup, false);
            pTrade->getField(ifds::EffectiveDate,  tradeDate,  idDataGroup, false);
            pTrade->getField(ifds::Amount,         amount,     idDataGroup, false);
            pTrade->getField(ifds::AmtType,        amtType,    idDataGroup, false);
         
            double dec_amount = DSTCommonFunctions::convertToDouble (amount);
            if (dec_amount != 0 || pTrade->isExchangeLike(idDataGroup))
            {
               DString strKey =  
                  I_("AcqFeeInquiry_TransType") + transType +
                  I_(";FundCode=") + fromFund +
                  I_(";ClassCode=") + fromClass +
                  I_(";EffectiveDate=") + tradeDate +
                  I_(";AccountNum=") + accountNum +
                  I_(";BrokerCode=") + brokerCode +
                  I_(";ToFund=") + toFund +
                  I_(";ToClass=") + toClass +
                  I_(";TaxType=") + taxType +
                  I_(";Amount=") + amount +
                  I_(";AmtType=") + amtType +
                  I_(";Currency=") + settleCurrency +
				      I_(";ToAcctTaxType=") + toAcctTaxType+
				      I_(";AcctNumbr=")  +accountNum +
				  I_(";TradeInDate=") + tradeInDate;
   
               pAcqFeeInquiry = dynamic_cast <AcqFeeInquiry*> (getObject (strKey, idDataGroup));

               if (!pAcqFeeInquiry)
               {
                  pAcqFeeInquiry = new AcqFeeInquiry (*this);
                  pAcqFeeInquiry->setFundCurrency (fundCurrency);
                  if (pAcqFeeInquiry->init(taxType, transType, tradeDate, amount, amtType, fromFund, 
                                           fromClass, settleCurrency, brokerCode, toFund, toClass,
														 I_("N"),  // flatpercent default 
														 I_("N"),  // track default
														 NULL_STRING ,  // activity default
														 toAcctTaxType, accountNum, tradeInDate) <= WARNING)
                  {
                     setObject (pAcqFeeInquiry, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
                  }
                  else
                  {
                     delete pAcqFeeInquiry;
                     pAcqFeeInquiry = NULL;
                  }
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::doValidateField ( const BFFieldId &idField, 
                                           const DString &strValue, 
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
   if (FundAlloc::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
      if (idField == ifds::FundCode)
      {
         validateFundCode (strValue, idDataGroup);
      }
      else if (idField == ifds::ClassCode)
      {
         validateClassCode (strValue, idDataGroup);
      }
      else if (idField == ifds::FundClass)
      {
         validateFundClass (idDataGroup);
      }
      else if (idField == ifds::SoftCapCheck)
      {
         validateSoftCapCheck (idDataGroup);
      }
      else if (idField == ifds::AllocAmount)
      {
         validateAmount (strValue, idDataGroup);
      }
      else if (idField == ifds::MinToFundAmount)
      {
         validateCrossAmount (idDataGroup);
      }
      else if (idField == ifds::AllocAtCost)	
      {
         validateFundClassPercent (idDataGroup);
         validateFundAllocation (idDataGroup);
      }
      else if (idField == ifds::FeeType)
      { 
         if (DSTCommonFunctions::codeInList (strValue, FEES_NOT_ALLOWED) && 
            !SplitCommission::isTypeZERO (getWorkSession()))
         {
            getErrMsg (I_("1113"), CND::ERR_FEETYPE_NOT_SUPPORTED, CND::WARN_FEETYPE_NOT_SUPPORTED, idDataGroup);
         }

         SplitCommissionList *pSplitCommissionList = NULL;
         if ( getSplitCommissionList (pSplitCommissionList, idDataGroup) <= WARNING &&
            pSplitCommissionList)
         {
            pSplitCommissionList->setField (ifds::FeeType, strValue, idDataGroup, false, true);
         }

      }

   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::validateFundCode ( const DString &strValue, 
                                            const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundCode"));
//validation for blank fund and isFundExist in FundMasterList is already done by FundAlloc superclass

	DString fundCode (strValue);
 	DString classCode;

	getField (ifds::ClassCode, classCode, idDataGroup);

	//cash fund code is invalid for default fund allocations
	if (fundCode.strip().upperCase() == I_("CASH"))
	{
		ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_CLASS_CODES);
	}
	else
	{
		//call trade method
		Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO());

		if (pTrade)
		{
			if (!classCode.empty ())
			{
				if (!pTrade->canFundBeAllocated (fundCode, classCode, idDataGroup) && pTrade->hasAllocations (idDataGroup))
					ADDCONDITIONFROMFILE (CND::ERR_ALLOCATION_NOT_ALLOWED);
			}

			pTrade->validateFundCode (strValue, idDataGroup);
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::validateClassCode ( const DString &strValue, 
                                             const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateClassCode"));

//validation for blank class code is done by FundAlloc
	DString fundCode;

	getField (ifds::FundCode, fundCode, idDataGroup);
//call trade method
	Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO());

	if (pTrade && !fundCode.empty())
	{
		if (pTrade->canFundBeAllocated (fundCode, strValue, idDataGroup) || !pTrade->hasAllocations (idDataGroup))
			pTrade->validateClassCode (fundCode, strValue, idDataGroup);
		else
			ADDCONDITIONFROMFILE (CND::ERR_ALLOCATION_NOT_ALLOWED);
	}
	
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::validateFundClass (const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundClass"));
   DString classCode, 
      fundCode;

   getField (ifds::FundCode, fundCode, idDataGroup, false);
   fundCode.strip().upperCase();
   getField (ifds::ClassCode, classCode, idDataGroup, false);
   classCode.strip().upperCase();

   Trade* pTrade = 
      dynamic_cast<Trade*> (getTopLevelCBO());
   
   if (pTrade)
   {
      DString transType,
         accountNum;

      getTopLevelAllocList()->getField (ifds::TransType, transType, idDataGroup, false);
      if (transType == TRADETYPE::TRANSFER || 
          transType == TRADETYPE::EXCHANGE || 
          transType == TRADETYPE::INTER_CLASS_SWITCH)
      {
         pTrade->getField (ifds::AccountTo, accountNum, idDataGroup, false);
         if (pTrade->validateToFundClass (fundCode, classCode, accountNum, idDataGroup) <= WARNING)
         {
            DString fromFund, fromClass, tradeDate;

            getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);

            pTrade->getField (ifds::FromFund, fromFund, idDataGroup, false);
            pTrade->getField (ifds::FromClass, fromClass, idDataGroup, false);
            //do not call validation if not necessary - Incident 374150
            if (!fromFund.empty() && !fromClass.empty())
            {
//call trade method
               pTrade->validateFromToFundClass (fromFund, fromClass, fundCode, classCode, idDataGroup);
               if (transType == TRADETYPE::EXCHANGE ||
                   transType == TRADETYPE::INTER_CLASS_SWITCH)
               {
				  DString transId;
			      
      			  getField (ifds::TransId, transId, idDataGroup,false);
				  pTrade->validateFromToSegTradeEntryCheck(accountNum,
                                          fundCode,
                                          classCode,
                                          accountNum,
                                          fundCode,
                                          classCode,
                                          tradeDate,
                                          transType,
                                          transId,
                                          idDataGroup);

               }
            }
         }
      }
      else
      {
         pTrade->getField (ifds::AccountNum, accountNum, idDataGroup, false);
//call trade method
         pTrade->validateFundClass (fundCode, classCode, accountNum, idDataGroup);
      }
      if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
         FundDetail *pFundDetail = NULL;

         if ( getWorkSession ().getFundDetail  ( fundCode, 
                                                 classCode, 
                                                 idDataGroup, 
                                                 pFundDetail) && 
               pFundDetail)
         {
            DString fundCurrency;

            pFundDetail->getField(ifds::Currency, fundCurrency, idDataGroup, false);
//call trade method
            pTrade->validateCurrencyTaxType (accountNum, fundCurrency, idDataGroup);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::validateSoftCapCheck (const BFDataGroupId &idDataGroup) 
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateSoftCapCheck"));

    DString classCode, fundCode;

    getField (ifds::FundCode, fundCode, idDataGroup, false);
    fundCode.strip().upperCase();
    getField (ifds::ClassCode, classCode, idDataGroup, false);
    classCode.strip().upperCase();

    Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO());

    if (pTrade)
    {
        DString transType, accountNum;

        getTopLevelAllocList()->getField (ifds::TransType, transType, idDataGroup, false);

        if (transType == TRADETYPE::TRANSFER || 
            transType == TRADETYPE::EXCHANGE || 
            transType == TRADETYPE::INTER_CLASS_SWITCH)
        {
            pTrade->getField (ifds::AccountTo, accountNum, idDataGroup, false);
            DString fromFund, fromClass, tradeDate;

            getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
            pTrade->getField (ifds::FromFund, fromFund, idDataGroup, false);
            pTrade->getField (ifds::FromClass, fromClass, idDataGroup, false);

            if (!fromFund.empty() && !fromClass.empty())
            {
                if (transType == TRADETYPE::EXCHANGE ||
                    transType == TRADETYPE::INTER_CLASS_SWITCH)
                {
                    pTrade->fundClassSoftCapCheck (TRADETYPE::EXCHANGE_IN, accountNum, fundCode, classCode, idDataGroup); 
                }
                else if (transType == TRADETYPE::TRANSFER &&     //Twitch - different from/to account and different fund/class.
                        (fromFund != fundCode || fromClass != classCode))
                {
                    //AccountTo - Transfer In
                    getWorkSession().fundClassSoftCappedCheck(accountNum, fundCode, classCode, I_("DD"), tradeDate, idDataGroup);
                }
            }

        }
        else
        {
            pTrade->getField (ifds::AccountNum, accountNum, idDataGroup, false);

            if (transType == TRADETYPE::PURCHASE)
            {
                pTrade->fundClassSoftCapCheck (TRADETYPE::PURCHASE, accountNum, fundCode, classCode, idDataGroup); 
            }
        }
    }

   return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************
SEVERITY TradeFundAlloc::validateCrossAmount (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateCrossAmount"));
   Trade *pTrade = dynamic_cast <Trade*> (getTopLevelCBO());
   
   if (pTrade)
   {
      DString accountNum,
         transType,
         amount,
         amtType,
         classCode, 
         fundCode,
		   broker,
		   branch,
		   slsrep,
         depositType; //in1419539

      getField (ifds::AllocAmount, amount, idDataGroup, false);
      pTrade->getField (ifds::AmtType, amtType, idDataGroup, false);
      pTrade->getField (ifds::DepositType, depositType, idDataGroup); //in1419539
      getTopLevelAllocList()->getField(ifds::TransType, transType,idDataGroup, false);
      getParentAcctAlloc()->getField (ifds::AccountNum, accountNum, idDataGroup, false);

      MFAccount *pMFAccount = NULL;

      if (getWorkSession().getMFAccount (idDataGroup, accountNum,pMFAccount) <= WARNING && pMFAccount)
      {
         pMFAccount->getField (ifds::BrokerCode, broker, idDataGroup); 
         pMFAccount->getField (ifds::BranchCode, branch, idDataGroup);
         pMFAccount->getField (ifds::Slsrep, slsrep, idDataGroup);
      }

      getField (ifds::FundCode, fundCode, idDataGroup, false);
      fundCode.strip().upperCase();
      getField (ifds::ClassCode, classCode, idDataGroup, false);
      classCode.strip().upperCase();
      if (transType == TRADETYPE::TRANSFER || 
          transType == TRADETYPE::EXCHANGE ||
          transType == TRADETYPE::INTER_CLASS_SWITCH)
      {
//call trade method
         pTrade->validateMinToFundAmount (accountNum,    
                                          fundCode, 
                                          classCode, 
                                          amtType, 
                                          amount, 
			                                 broker, 
                                          branch, 
                                          slsrep, 
                                          depositType, //in1419539
                                          idDataGroup);
      }
      else
      {
//call trade method
         pTrade->validateMinFromFundAmount ( accountNum, 
                                             fundCode, 
                                             classCode, 
                                             amtType, 
                                             amount, 
			                                    broker, 
                                             branch, 
                                             slsrep, 
                                             depositType, //in1419539
                                             idDataGroup);
//only redemptions should answer to this call
         pTrade->validateFundBalance (accountNum, fundCode, classCode, amount, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::validateFundAllocation (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundAllocation"));

	Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO());
	DString fundCode, classCode;

    getField (ifds::FundCode, fundCode, idDataGroup, false);
    getField (ifds::ClassCode, classCode, idDataGroup, false);

	if (pTrade && !fundCode.empty() && !classCode.empty ())
	{
		bool bCanBeAllocated = pTrade->canFundBeAllocated (fundCode, classCode, idDataGroup);
		
		if (bCanBeAllocated || !pTrade->hasAllocations (idDataGroup))
		{
			DString percent;
			getField (ifds::AllocPercentage, percent, idDataGroup, false);
			double dPercent = DSTCommonFunctions::convertToDouble(percent);

			bool bPercent = dPercent == 0 || dPercent == 100 ?  true : false;

			if (!bPercent && !bCanBeAllocated)
			{
				ADDCONDITIONFROMFILE (CND::ERR_ALLOCATION_NOT_ALLOWED);
			}
		}
		else
		{
			ADDCONDITIONFROMFILE (CND::ERR_ALLOCATION_NOT_ALLOWED);
		}
	}

   return GETCURRENTHIGHESTSEVERITY();

}
//******************************************************************************
SEVERITY TradeFundAlloc::validateFundClassPercent (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateFundClassPercent" ));   

   Trade *pTrade = dynamic_cast <Trade*> (getTopLevelCBO());

   if (pTrade)
   {
//check for AtCost allocation, only if generic control DefltRedCodeFlag is set to Yes
      DString defltRedCodeFlag;

      getWorkSession().getOption (ifds::DefltRedCodeFlag, defltRedCodeFlag, BF::HOST, false);
      if (defltRedCodeFlag.strip() == Y)
      {
         //if it is single fund allocations it is OK    
         DString classCode, 
            fundCode,
            percent;

         getField (ifds::FundCode, fundCode, idDataGroup, false);
         getField (ifds::ClassCode, classCode, idDataGroup, false);
         getField (ifds::AllocPercentage, percent, idDataGroup, false);

         double dAllocPercentage = DSTCommonFunctions::convertToDouble(percent);
         
         if (fabs (dAllocPercentage - 100) > dSmallValue && !fundCode.empty() && !classCode.empty())
         {
            bool blIsAtCostTIK = false;

            //transfers/exchanges will answer this call
            pTrade->getAtCostTIKStatus( idDataGroup, 
                                        fundCode, 
                                        classCode,
                                        true , // we have an allocation
                                        /* false, we don't need the return value (if it is At Cost or not)*/	
                                        blIsAtCostTIK);
         }
      }
   }
     return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::validateAmount( const DString &strValue, 
                                         const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmount"));
   Trade *pTrade = dynamic_cast<Trade*> (getTopLevelCBO());
   DString classCode, 
      fundCode;
   
   getField (ifds::FundCode, fundCode, idDataGroup, false);
   getField (ifds::ClassCode, classCode, idDataGroup, false);

   if (pTrade && !fundCode.empty() && !classCode.empty())
   {
      pTrade->validateAmount (strValue, idDataGroup);
//allocations should not care whether amount is zero for purchases,
//impeeds setting default allocations (PTS 10037326)
/*    
	  int count = CONDITIONCOUNT();
      Condition *c = NULL;
      for (int i = 0; i < count; i++)
      {
         c = GETCONDITION( i );
         int condCode = c->getCode();
         //do not want to promote this condition
         if (condCode == CND::ERR_VALUE_CANNOT_BE_ZERO) 
         {
            CLEARCONDITION( i );
            break;
         }
      }
*/
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::doValidateAll (const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"))
//deal with settle currency in trade if environment is non-multi currency
   //read management company options VERY OFTEN used
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeFundAlloc::initDefault (BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initDefault"))

   FundAlloc::initDefault(pDefaultAlloc, idDataGroup);

   DString dstrFundCode, dstrClassCode, dstrTransType;

   getField(ifds::FundCode, dstrFundCode, BF::HOST, false);
   getField(ifds::ClassCode, dstrClassCode, BF::HOST, false);
   getField(ifds::TransType, dstrTransType, BF::HOST, false);

   FundDetail *pFundDetail = NULL;
   bool bSplitCommActive = false;
   if((!dstrFundCode.empty()) && (!dstrClassCode.empty()) &&
       (getFundDetail(dstrFundCode, dstrClassCode, pFundDetail)<=WARNING) && pFundDetail)
   {
      bSplitCommActive = pFundDetail->splitCommActive(getWorkSession(), dstrTransType.strip(), BF::HOST);
   }

   setField(ifds::SplitComm, bSplitCommActive ? YES : NO, BF::HOST, false);
//   setFieldNoValidate(ifds::Default, YES, BF::HOST, false); //default split commission
   setFieldNoValidate(ifds::RecordType, I_("TO"), BF::HOST, false, true, false, false);

   setAmountField( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeFundAlloc::copyDataFromParent(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
   //this method should be only called when the parent is a trade or a pending trade details
   BFCBO* pBFCBO = getTopLevelCBO();
   DString strTemp, strTransType;

   //init with 0 the trans seq
   setFieldNoValidate(ifds::TransSeq, I_("0"), BF::HOST, false, false);
   getTopLevelAllocList()->getField(ifds::TransType, strTransType, idDataGroup, false);
   if ((dynamic_cast<Trade*> (pBFCBO)))
   {
      getParentAcctAlloc()->getField(ifds::AccountNum, strTemp, idDataGroup, false);
      setFieldNoValidate(ifds::AccountNum, strTemp, idDataGroup, false, false);

      pBFCBO->getField(ifds::TransSeq, strTemp, idDataGroup, false);
      if (strTemp != NULL_STRING)
      {
         setFieldNoValidate(ifds::TransSeq, strTemp, idDataGroup, false, false);
      }
      if (strTransType.strip() == TRADETYPE::TRANSFER || 
          strTransType == TRADETYPE::EXCHANGE ||
          strTransType == TRADETYPE::INTER_CLASS_SWITCH)
      {
         pBFCBO->getField (ifds::ToFund, strTemp, idDataGroup, false);
         setFieldNoValidate(ifds::FundCode, strTemp, idDataGroup, false, false);

         pBFCBO->getField (ifds::ToClass, strTemp, idDataGroup, false);
         setFieldNoValidate(ifds::ClassCode, strTemp, idDataGroup, false, false);
      }
      if (DSTCommonFunctions::codeInList (strTransType.strip(), TRADETYPE::ONE_SIDE_TRADE))
      {
         pBFCBO->getField (ifds::FromFund, strTemp, idDataGroup, false);
         setFieldNoValidate(ifds::FundCode, strTemp, idDataGroup, false, false);

         pBFCBO->getField (ifds::FromClass, strTemp, idDataGroup, false);
         setFieldNoValidate(ifds::ClassCode, strTemp, idDataGroup, false, false);
      }
   }
   else if (dynamic_cast<PendingTradeDetails*> (pBFCBO))
   {
      getParentAcctAlloc()->getField(ifds::AccountNum, strTemp, idDataGroup, false);
      setFieldNoValidate(ifds::AccountNum, strTemp, idDataGroup, false, false);

      if(strTransType.strip() == TRADETYPE::TRANSFER || 
         strTransType == TRADETYPE::EXCHANGE ||
         strTransType == TRADETYPE::INTER_CLASS_SWITCH ||
         strTransType == TRADETYPE::AUTO_TRANSFER)
      {
         pBFCBO->getField (ifds::FundTo, strTemp, idDataGroup, false);
         setFieldNoValidate(ifds::FundCode, strTemp, idDataGroup, false, false);

         pBFCBO->getField (ifds::ClassToCode, strTemp, idDataGroup, false);
         setFieldNoValidate(ifds::ClassCode, strTemp, idDataGroup, false, false);
      }
     	else if (DSTCommonFunctions::codeInList (strTransType.strip(), TRADETYPE::ONE_SIDE_TRADE))
      {
         pBFCBO->getField (ifds::rxFundCode, strTemp, idDataGroup, false);
         setFieldNoValidate(ifds::FundCode, strTemp, idDataGroup, false, false);

         pBFCBO->getField (ifds::rxClassCode, strTemp, idDataGroup, false);
         setFieldNoValidate(ifds::ClassCode, strTemp, BF::HOST, false, false);
      }
      pBFCBO->getField (ifds::SettleCurrency, strTemp, BF::HOST, false);
      setFieldNoValidate(ifds::SettleCurrency, strTemp, BF::HOST, false, false);
      
      DString transSeq;
      
      pBFCBO->getField(ifds::TransSeq, transSeq, idDataGroup, false);
      setFieldNoValidate(ifds::TransSeq, transSeq, BF::HOST, false );
   }
   else if(dynamic_cast<TransactionDetails*> (pBFCBO))
   {
      getParentAcctAlloc()->getField(ifds::AccountNum, strTemp, idDataGroup, false);
      setFieldNoValidate(ifds::AccountNum, strTemp, idDataGroup, false, false);

      if(strTransType.strip() == TRADETYPE::TRANSFER || 
         strTransType == TRADETYPE::EXCHANGE ||
         strTransType == TRADETYPE::INTER_CLASS_SWITCH)
         //||
         //strTransType.strip() == TRADETYPE::TRANSFER_OUT   ||
         //strTransType.strip() == TRADETYPE::TRANSFER_OUT_2 ||
         //strTransType.strip() == TRADETYPE::EXCHANGE_OUT)
      {
         pBFCBO->getField (ifds::TfrFund, strTemp, idDataGroup, false);
         setFieldNoValidate(ifds::FundCode, strTemp, idDataGroup, false, false);

         pBFCBO->getField (ifds::TfrClass, strTemp, idDataGroup, false);
         setFieldNoValidate(ifds::ClassCode, strTemp, idDataGroup, false, false);
      }
      else
      {
         pBFCBO->getField (ifds::rxFundCode, strTemp, BF::HOST, false);
         setFieldNoValidate(ifds::FundCode, strTemp, BF::HOST, false, false);

         pBFCBO->getField (ifds::rxClassCode, strTemp, BF::HOST, false);
         setFieldNoValidate(ifds::ClassCode, strTemp, BF::HOST, false, false);
      }
      //set the transaction sequence
      pBFCBO->getField(ifds::TransSeq, strTemp, idDataGroup, false);
      setFieldNoValidate(ifds::TransSeq, strTemp, idDataGroup, false, false);
      pBFCBO->getField (ifds::SettleCurrency, strTemp, BF::HOST, false);
      setFieldNoValidate(ifds::SettleCurrency, strTemp, BF::HOST, false, false);
      pBFCBO->getField(ifds::TransId, strTemp, idDataGroup, false);
      setFieldNoValidate(ifds::TransId, strTemp, idDataGroup, false, false);
   }
   else
      assert(0);

   //set the fund number
   setFundNumber(idDataGroup);

   //split commissions :
   //1. if it is an existent allocation and it has a split commission already created, we should not go for a default one
   //2. either if it is an existent or new allocation for which there is no split comm. record saved in the database,
   //2.a. we should set the SplitComm field to YES, if split comm is active (allowed) and go for the default one
   //2.b. we should set the SplitComm field to NO, if split comm is NOT active (allowed) and we shouldn't go for the default one
   if (!(dynamic_cast<Trade*> (pBFCBO)))
   {
      pBFCBO->getField (ifds::SplitComm, strTemp, idDataGroup, false);
      setFieldNoValidate(ifds::SplitComm, strTemp, idDataGroup, false, false);
   }
   else
   {
      getField (ifds::SplitComm, strTemp, idDataGroup, false);
   }
   if (!isNew() && strTemp == YES)//only for existing allocation with split commission
   {
      _bInitialSplitComm = true;
//      setFieldNoValidate(ifds::Default, NO, idDataGroup, false, false);
   }
   else if(splitCommActive (idDataGroup))//both for new or existing allocation that doesn't have a persistent split comm., but split comm is allowed
   {
      //the split commission is already saved in the database in case of a TransactionHistory
      //represented by the TransactionDetails object, this allocation should have the 
      //_bInitialSplitComm set to true and should not look for the Default split
      if (dynamic_cast<TransactionDetails*> (pBFCBO))
      {
//         setFieldNoValidate(ifds::Default, NO, idDataGroup, false);
         _bInitialSplitComm = true;
      }
      else
      {
//         setFieldNoValidate(ifds::Default, YES, idDataGroup, false);  
      }
      setFieldNoValidate(ifds::SplitComm, YES, idDataGroup, false,true,true);
   }
   else//both for new or existing allocation that doesn't have a persistent split comm., and split comm is NOT allowed
   {
      //still if there was split commission in history, although right now the fund doe not allow split commision
      //we should display it, so
      if (dynamic_cast<TransactionDetails*> (pBFCBO))
      {
         _bInitialSplitComm = true;
         setFieldNoValidate(ifds::SplitComm, YES, idDataGroup, false,true,true);  
      } else
      {      
         setFieldNoValidate(ifds::SplitComm, NO, idDataGroup, false,true,true);  
      }
//      setFieldNoValidate(ifds::Default, NO, idDataGroup, false);  
   }

   //it only makes sense to copy data from the parent for a 100% allocation
   setField(ifds::AllocPercentage, I_("100"), idDataGroup, false);//this will also set the amount field

   setAmountField( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool TradeFundAlloc::splitCommActive (const BFDataGroupId& idDataGroup)  
{
   bool bSplitCommActive = false;
   Trade *pTrade = dynamic_cast<Trade *>(getTopLevelCBO());

   if (pTrade)
   {
//      if (pTrade->isSplitCommissionAllowed (idDataGroup))
      {
         bool bAlreadySet = false;
         FundDetail *pFundDetail = NULL,
            *pFromFundDetail = NULL;
         DString fundCode, 
            classCode, 
            transType,
            loadType,
            fromLoadType;

         getField (ifds::FundCode, fundCode, idDataGroup);
         getField (ifds::ClassCode, classCode, idDataGroup);
         fundCode.strip().upperCase();
         classCode.strip().upperCase();
         getTopLevelAllocList()->getField (ifds::TransType, transType, idDataGroup, false);

         if (getWorkSession().getFundDetail (fundCode, classCode, 
            idDataGroup, pFundDetail) && pFundDetail)
         {  
            pFundDetail->getField (ifds::LoadType, loadType, 
               idDataGroup, false);
            if (transType == TRADETYPE::TRANSFER ||
                transType == TRADETYPE::EXCHANGE ||
                transType == TRADETYPE::INTER_CLASS_SWITCH)
            {
               DString fromFund, fromClass;

               pTrade->getField (ifds::FromFund, fromFund, idDataGroup, false);
               pTrade->getField (ifds::FromClass, fromClass, idDataGroup, false);

               if (getWorkSession().getFundDetail (fromFund, fromClass, 
                  idDataGroup, pFromFundDetail) && pFromFundDetail)
               {            
                  pFromFundDetail->getField (ifds::LoadType, fromLoadType, 
                     idDataGroup, false);
                  FundToList  fundToList( *this );
                  //not new money, look at split commission of the from side of the trade
                  if ( !fundToList.isBuySell (fromFund, fromClass, 
                     fundCode, classCode))
                  {
                     bSplitCommActive = pFromFundDetail->splitCommActive (
                        getWorkSession(), transType, idDataGroup);
                     bAlreadySet = true;
                  }

               }
            }
            if (!bAlreadySet)
            {
               bSplitCommActive = pFundDetail->splitCommActive (
                  getWorkSession(), transType, idDataGroup);
               if (!bSplitCommActive && 
                   (transType == TRADETYPE::TRANSFER || transType == TRADETYPE::EXCHANGE || transType == TRADETYPE::INTER_CLASS_SWITCH) && 
                   (fromLoadType == I_("BEL") || loadType == I_("BEL")))
               {
                  bSplitCommActive = pFromFundDetail->splitCommActive (
                        getWorkSession(), transType, idDataGroup);
               }
            }
         }
      }
   }
   return bSplitCommActive;
}

//******************************************************************************
SEVERITY TradeFundAlloc::setAmountField( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAmountField" ) );   

   bool blDisableAmount = false;
   DString dstrTransType;
   getTopLevelAllocList()->getField(ifds::TransType, dstrTransType, idDataGroup, false);
   if ( I_( "PW" ) == dstrTransType || I_( "AF" ) == dstrTransType)
   {
      BFCBO *pParentCBO = getTopLevelCBO();
      if ( NULL != pParentCBO )
      {
         Trade* pTrade = dynamic_cast<Trade*>(pParentCBO);
         if ( NULL != pTrade )
         {
            if ( pTrade->isFullRedemption ( idDataGroup ) )
            {
               blDisableAmount = true;
            }
         }
      }
   }

   setFieldReadOnly( ifds::AllocAmount, idDataGroup, blDisableAmount );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeFundAlloc::refreshSplitCommFlag (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "refreshSplitCommFlag" ) );

   if (splitCommActive (idDataGroup))
   {
      setFieldNoValidate (ifds::SplitComm, Y, idDataGroup, false, true, true);  
//no more initial split commission, get the default split
      _bInitialSplitComm = false;
   }
   else
   {
      setFieldNoValidate (ifds::SplitComm, N, idDataGroup, false, true, true);  
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeFundAlloc::validateFundClassAccNumDate (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClassAccNumDate" ) );
   //ask derived class if seg fund validation is required
   if (!isSegFundValidationReq())
      return(GETCURRENTHIGHESTSEVERITY());

   DString dstrFundTo;
   getField( ifds::FundCode,      dstrFundTo,      idDataGroup, false );

   // if SegClient and CotClient do the SegFundValidation
   if( isSegCotClient() )
   {
      DString dstrTransType, dstrEventTransType; 
      getTopLevelAllocList()->getField (ifds::TransType, dstrTransType, idDataGroup, false);

      if ( dstrTransType == TRADETYPE::TRANSFER || 
           dstrTransType == TRADETYPE::EXCHANGE ||
           dstrTransType == TRADETYPE::INTER_CLASS_SWITCH)
      {
         DString dstrClassTo, dstrAccountTo, dstrEffectiveDate;
         getField( ifds::FundCode,      dstrFundTo,      idDataGroup, false );
         getField( ifds::ClassCode,     dstrClassTo,       idDataGroup, false );
         getField( ifds::AccountNum,    dstrAccountTo,     idDataGroup, false );
         getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
         if ( dstrTransType == TRADETYPE::TRANSFER )
            dstrEventTransType = I_("07");
         else 
            dstrEventTransType = I_("08");

         SeqFundValidation *pToSeqFundValidation = NULL;	
         Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO());

         /* As of incident #682515 From and To funds are required for validation. Commented 
            out code bellow is now obsolete.

         if ( NULL != pTrade &&
         pTrade->getSegFundValidation( pToSeqFundValidation, 
                                       dstrFundTo, 
                                       dstrClassTo, 
                                       dstrAccountTo, 
                                       dstrEffectiveDate, 
                                       idDataGroup, 
                                       dstrEventTransType,
                                       dstrTransType,
                                       NULL_STRING,
                                       NULL_STRING,
                                       NULL_STRING) <= WARNING &&
            NULL != pToSeqFundValidation )
         {
            pToSeqFundValidation->canTradeFundClass( idDataGroup );
            pToSeqFundValidation->addSegFundValidationWarnings( idDataGroup );
         }
         */
      }
      FundMasterList *pFundMasterList (NULL);
      bool isSegFund = false;

      if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
           pFundMasterList)
      {
         isSegFund = pFundMasterList->isSegregatedFund(dstrFundTo);
      }

      if(isSegFund)
      {
         SeqFundValidation *pSeqFundValidation = NULL;
         if( getSeqFundValidation( pSeqFundValidation, idDataGroup ) <= WARNING && pSeqFundValidation )
         {
            pSeqFundValidation->canTradeFundClass( idDataGroup );
            pSeqFundValidation->addSegFundValidationWarnings( idDataGroup );

         }
      }
   }

   DString dstrGuaranteeCalcByRules;
   getWorkSession().getOption (ifds::GuaranteeCalcByRules, 
                               dstrGuaranteeCalcByRules, 
                               idDataGroup, 
                               false);

   if( dstrGuaranteeCalcByRules.strip().upperCase() == I_("Y") )
   {
      DString dstrTransType; 
      getTopLevelAllocList()->getField (ifds::TransType, dstrTransType, idDataGroup, false);

      BFCBO *pParentCBO = getTopLevelCBO();
      Trade* pTrade = dynamic_cast<Trade*>(pParentCBO);

      DString fromFund, fromClass, effectiveDate,
              toFund, toClass, accountTo, accountNum, transID;
      pTrade->getField (ifds::FromFund, fromFund, idDataGroup, false);
      pTrade->getField (ifds::FromClass, fromClass, idDataGroup, false);
      pTrade->getField( ifds::EffectiveDate, effectiveDate, idDataGroup, false );
      pTrade->getField( ifds::TransId, transID, idDataGroup, false );
      pTrade->getField( ifds::AccountNum, accountNum, idDataGroup, false );

      if ( dstrTransType == TRADETYPE::TRANSFER || 
           dstrTransType == TRADETYPE::EXCHANGE ||
           dstrTransType == TRADETYPE::INTER_CLASS_SWITCH)
      {
         getField( ifds::FundCode, toFund, idDataGroup, false );
         getField( ifds::ClassCode, toClass, idDataGroup, false );
         pTrade->getField( ifds::AccountTo, accountTo, idDataGroup, false );
      }
      else
      {
         getField( ifds::FundCode, fromFund, idDataGroup, false );
         getField( ifds::ClassCode, fromClass, idDataGroup, false );
      }

      FundMasterList *pFundMasterList (NULL);
      if( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
           pFundMasterList && 
           ( pFundMasterList->isSegregatedFund(fromFund) || pFundMasterList->isSegregatedFund (toFund)))
      {
         SEGTradeEntryValidation validationObj(*this);

         if( validationObj.init(accountNum,
                              fromFund,
                              fromClass,
                              accountTo, // account to
                              toFund, // fund to
                              toClass, // class to
                              effectiveDate,
                              I_("TradeDate"),
                              dstrTransType,
                              transID) <= WARNING )
         {
            DString strErrorCode;
            validationObj.getField(ifds::WarnCode, strErrorCode, idDataGroup, false);
            strErrorCode.strip().upperCase();

            switch( strErrorCode.asInteger())
            {
               case 1214:
               {
                  DString strIDI,
                     strDateFormat,
                     strWarnValue1,
                     strWarnValue2;
                  validationObj.getField(ifds::WarnValue1, strWarnValue1, idDataGroup, false);
                  validationObj.getField(ifds::WarnValue2, strWarnValue2, idDataGroup, false);
                  strWarnValue2.lowerCase();
                  DSTCommonFunctions::FormatDateByString (strWarnValue1, strWarnValue2);
                  addIDITagValue( strIDI, I_( "TRADE_DATE" ), strWarnValue1 );
                  getErrMsg ( IFASTERR::TRADE_NOT_ALLOWED_TO_CANCEL,
                              CND::ERR_TRADE_NOT_ALLOWED_TO_CANCEL, 
                              CND::WARN_TRADE_NOT_ALLOWED_TO_CANCEL, 
                              idDataGroup,
                              strIDI);
               }
                  break;
               case 1215:
               {
                  getErrMsg ( IFASTERR::BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE,
                              CND::ERR_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE, 
                              CND::WARN_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE, 
                              idDataGroup);
               }
                  break;
               case 1216:
               {
                  getErrMsg ( IFASTERR::BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA,
                              CND::ERR_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA, 
                              CND::WARN_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA, 
                              idDataGroup);
               }
                  break;
               case 1229:
               {
                  getErrMsg ( IFASTERR::LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE,
                              CND::ERR_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE, 
                              CND::WARN_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE, 
                              idDataGroup);
               }
               default:
                  break;
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeFundAlloc::getSeqFundValidation( SeqFundValidation *&pSeqFundValidation,
                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSeqFundValidation" ) );

   //check cbobase to see if we've already built it
   //if it is already built, check if the parameters are changed
   //if not built create and store with base
   //if built but parameter(s) changed, reInit with the new ones
   pSeqFundValidation = NULL;
   DString strAccountNum, strFundCode, strClassCode, strEffectiveDate;
   getField( ifds::FundCode,     strFundCode,      idDataGroup, false );
   getField( ifds::ClassCode,    strClassCode,     idDataGroup, false );
   getField( ifds::AccountNum,   strAccountNum,    idDataGroup, false );
   getField( ifds::EffectiveDate,strEffectiveDate, idDataGroup, false );

   if( strAccountNum.strip().empty() || 
      strFundCode.strip().upperCase().empty() || 
      strClassCode.strip().upperCase().empty() || 
      strEffectiveDate.strip().empty() )
      return(GETCURRENTHIGHESTSEVERITY()); 	

   DString dstrFromAccount, dstrFromFund, dstrFromClass, 
          dstrToAccount, dstrToFund, dstrToClass;

   DString dstrTransType, dstrEventTransType;
   getTopLevelAllocList()->getField (ifds::TransType, dstrTransType, idDataGroup, false);
   if ( dstrTransType == TRADETYPE::TRANSFER || 
        dstrTransType == TRADETYPE::EXCHANGE ||
        dstrTransType == TRADETYPE::INTER_CLASS_SWITCH)
   {
      Trade* pTrade = dynamic_cast<Trade*>(getTopLevelCBO());
      if ( NULL != pTrade )
      {
         pTrade->getField (ifds::AccountNum, dstrFromAccount, idDataGroup, false); 
         pTrade->getField (ifds::FromFund,   dstrFromFund,    idDataGroup, false); 
         pTrade->getField (ifds::FromClass,  dstrFromClass,   idDataGroup, false);

         dstrToAccount = strAccountNum;
         dstrToFund    = strFundCode;
         dstrToClass   = strClassCode;

         if ( dstrTransType == TRADETYPE::TRANSFER )
            dstrEventTransType = I_("07");
         else 
            dstrEventTransType = I_("08");
         //dstrEventTransType = NULL_STRING;  // Exchange/Transfer should not have FromFund side SegFundRules validation
      }
   }
   else
   {
      dstrFromAccount = strAccountNum;
      dstrFromFund    = strFundCode;
      dstrFromClass   = strClassCode;
      if( dstrTransType == TRADETYPE::PURCHASE )
         dstrEventTransType = I_("05");
      else
         dstrEventTransType = NULL_STRING; // other transtype should not have FromFund side SegFundRules validation
   }        

   DString dstrKey = I_("SeqFundValidation_AccountNum=") + dstrFromAccount 
                   + I_(";FundCode=")     + dstrFromFund 
                   + I_(";ClassCode=")    + dstrFromClass 
                   + I_(";TradeDate=")    + strEffectiveDate
                   + I_(";FundCodeTo=")   + dstrToAccount
                   + I_(";ClassCodeTo=")  + dstrToFund 
                   + I_(";AccountNumTo=") + dstrToClass
                   + I_(";EventTransType=")    + dstrEventTransType;
   
   pSeqFundValidation = 
      dynamic_cast<SeqFundValidation *> (BFCBO::getObject (dstrKey, idDataGroup));
   
   if( pSeqFundValidation )
   {
      DString dstrGuaranteesOverride = NULL_STRING;

      if( dstrTransType == TRADETYPE::TRANSFER )
      {
         Trade* pTrade = dynamic_cast<Trade*>(getTopLevelCBO());

         if (pTrade)
         {
            pTrade->getField( ifds::GuaranteesOverride, dstrGuaranteesOverride, idDataGroup, false );
            dstrGuaranteesOverride.strip().upperCase();
         }
      }

      dstrGuaranteesOverride.strip().upperCase();
      pSeqFundValidation->setField( ifds::GuaranteesOverride,dstrGuaranteesOverride,BF::HOST,false,false,false);

      if( pSeqFundValidation->isChanged( dstrFromFund, 
                                         dstrFromClass, 
                                         dstrFromAccount, 
                                         strEffectiveDate, 
                                         dstrEventTransType,
                                         dstrToFund, 
                                         dstrToClass, 
                                         dstrToAccount ) )
         pSeqFundValidation->reInit(dstrFromFund, 
                                    dstrFromClass, 
                                    dstrFromAccount, 
                                    strEffectiveDate,
                                    dstrEventTransType,
                                    dstrToFund, 
                                    dstrToClass, 
                                    dstrToAccount,
                                    dstrTransType
                                    );
   }
   else
   {
      pSeqFundValidation = new SeqFundValidation ( *this );

      DString dstrGuaranteesOverride;
      Trade* pTrade = dynamic_cast<Trade*>(getTopLevelCBO());
      if(pTrade)
      {
         pTrade->getField( ifds::GuaranteesOverride, dstrGuaranteesOverride, idDataGroup, false );
      }

      dstrGuaranteesOverride.strip().upperCase();
      pSeqFundValidation->setField( ifds::GuaranteesOverride,dstrGuaranteesOverride,BF::HOST,false,false,false);

      if( pSeqFundValidation->init( dstrFromFund, 
                                    dstrFromClass, 
                                    dstrFromAccount, 
                                    strEffectiveDate, 
                                    dstrEventTransType,
                                    dstrToFund, 
                                    dstrToClass, 
                                    dstrToAccount,
                                    dstrTransType
                                    ) <= WARNING )
      {
         setObject( pSeqFundValidation, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup ); 
      }
      else
      {
         delete pSeqFundValidation;
         pSeqFundValidation = NULL;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
void TradeFundAlloc::changeFieldsForRebook()
{
   setFieldNoValidate( ifds::DistribDetlVer, NULL_STRING, BF::HOST, false,true,false,false ); // no related changes
   setFieldNoValidate( ifds::DistribDetlRid, NULL_STRING, BF::HOST, false,true,false,false ); // no related changes

   SplitCommissionList* pSplitCommissionList = NULL;

   getSplitCommissionList ( pSplitCommissionList, BF::HOST,false );
   if( pSplitCommissionList )
   {
      pSplitCommissionList->changeFieldsForRebook();   
   }
   clearUpdatedFlags( BF::HOST ); // the object should not be dirty 
}

//******************************************************************************
bool TradeFundAlloc::hasPurchExchgFrontEndLoadCommission(const BFDataGroupId& idDataGroup)
{
   bool retVal = false;
   retVal = isFELFundClass(idDataGroup);
   //DString dstrFundCode;
   //DString dstrClassCode;
   //getField( ifds::FundCode,  dstrFundCode,  idDataGroup);
   //getField( ifds::ClassCode, dstrClassCode, idDataGroup);

   //FundDetail *pFundDetail = NULL;
   //if (!dstrFundCode.stripAll().empty() && !dstrClassCode.stripAll().empty() &&
   //      getWorkSession().getFundDetail (dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) && pFundDetail)
   //{
   //   DString dstrLoadType;
   //   pFundDetail->getField(ifds::LoadType, dstrLoadType, idDataGroup, false);
   //   if(dstrLoadType == FRONTENDLOAD)
   //      retVal = true;
   //}

   if(retVal)
   {
      Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO()); 
      BFCBO *pCBO = getTopLevelCBO(); 
      DString dstrTransType;
      if(pCBO)
      {
         if(dynamic_cast<Trade*>(pCBO)) //trade object
         {
            pCBO->getField(ifds::TradesTransType, dstrTransType, idDataGroup, false);
         }
         else //Pending trade or trans hist
         {
            pCBO->getField(ifds::TransType, dstrTransType, idDataGroup, false);
         }

         if(!DSTCommonFunctions::codeInList (dstrTransType, TRADETYPE::PURCHASE_LIKE)&&
            !(DSTCommonFunctions::codeInList (dstrTransType, TRADETYPE::EXCHANGE_LIKE) 
            && !SplitCommission::isTypeZERO (getWorkSession()) 
            )
            )
         {
            retVal = false;
         }
      }
   }
   
   return retVal;
};

//******************************************************************************
bool TradeFundAlloc::isFELFundClass(const BFDataGroupId& idDataGroup)
{
   bool retVal = false;
   DString dstrFundCode;
   DString dstrClassCode;
   getField( ifds::FundCode,  dstrFundCode,  idDataGroup);
   getField( ifds::ClassCode, dstrClassCode, idDataGroup);

   FundDetail *pFundDetail = NULL;
   if (!dstrFundCode.stripAll().empty() && !dstrClassCode.stripAll().empty() &&
         getWorkSession().getFundDetail (dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) && pFundDetail)
   {
      DString dstrLoadType;
      pFundDetail->getField(ifds::LoadType, dstrLoadType, idDataGroup, false);
      if(dstrLoadType == FRONTENDLOAD)
         retVal = true;
   }

   return retVal;
};

//******************************************************************************
SEVERITY TradeFundAlloc::setFeeRate(const DString& dstrFeeRate, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFeeRate" ) );

   setFieldNoValidate(ifds::FeeRate, dstrFeeRate, idDataGroup, false, true, false, false);

   return(GETCURRENTHIGHESTSEVERITY());
};

//******************************************************************************
SEVERITY TradeFundAlloc::updateTransFeeAcqFeeRate(const DString& dstrFeeRate, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFeeRate" ) );
   Trade* pTrade = dynamic_cast<Trade*> (getTopLevelCBO()); 
   if(pTrade)
   {
      DString transType;
      pTrade->getField(ifds::TradesTransType, transType, idDataGroup, false);
      TransFeeList *pTransFeeList = NULL;
      
      if (pTrade->getTransFeeList (pTransFeeList, idDataGroup, false) <= WARNING && pTransFeeList)
      {
         TransFee *pTransFee = NULL;

         if(DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE))
         {
            pTransFeeList->getTransFee(FEES::ACQUISITION, pTransFee, idDataGroup);
            AcquisitionFee* pAquisitionFee = dynamic_cast<AcquisitionFee*>(pTransFee);
            if(pAquisitionFee)
            {
               pAquisitionFee->setFeeRate(dstrFeeRate, idDataGroup);
            }
         }
         else if(DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE))
         {
            pTransFeeList->getTransFee(FEES::XFER_IN, pTransFee, idDataGroup);
            XferInFee* pXferInFee = dynamic_cast<XferInFee*>(pTransFee);
            if(pXferInFee)
            {
               pXferInFee->setFeeRate(dstrFeeRate, idDataGroup);
            }
         }   
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
};


//******************************************************************************
SEVERITY TradeFundAlloc::isBaseCommissionApplicableAndGetSFACRate ( bool &baseCommApplicable,
                                                           DString &strSFACRate,                                                 
                                                           const BFDataGroupId &idDataGroup, 
                                                           const DString dstrAllocFundCode, 
                                                           const DString dstrAllocClassCode )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isBaseCommissionApplicableAndGetSFACRate"));

   baseCommApplicable = false;
   strSFACRate = NULL_STRING;
   
   Trade *pTrade = dynamic_cast<Trade*> (getTopLevelCBO());

   if (pTrade && SplitCommission::isTypeTWO (getWorkSession()))
   {
      DString dstrBrokerCode;
      DString dstrFund;
      DString dstrClass;

      pTrade->getField (ifds::Broker, dstrBrokerCode, idDataGroup, false);
      
      getField (ifds::FundCode,  dstrFund, idDataGroup, false);
      getField (ifds::ClassCode, dstrClass, idDataGroup, false);
      Broker *pBroker (NULL); 

      if ( pTrade->getBroker (pBroker, idDataGroup) <= WARNING && pBroker)
      {
         DString fundServBroker;

         pBroker->getField (ifds::FundServBroker, fundServBroker, idDataGroup);
         if (fundServBroker == I_("N"))
         {
            FundDetail *pFundDetail = NULL;

            if (!dstrFund.empty() &&
                !dstrClass.empty() &&
                getWorkSession().getFundDetail (dstrFund, dstrClass, idDataGroup, pFundDetail) && 
                pFundDetail)
            {
               DString loadType;

               pFundDetail->getField (ifds::LoadType, loadType, idDataGroup, false);
               if (loadType == I_("FEL"))
               {
                  FundFeeList *pFundFeeList = NULL;

                  DString dstrEffectiveDate;
                  DString dstrAccountNum;
                  DString dstrBranchCode;
                  DString dstrSlsRepCode;

                  pTrade->getField (ifds::Branch, dstrBranchCode, idDataGroup, false);
                  pTrade->getField (ifds::SlsrepCode, dstrSlsRepCode, idDataGroup, false);
                  pTrade->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
                  pTrade->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
                  if ( pTrade->getFeeParams (I_("69"), //SFAC
                        dstrFund, dstrClass, dstrEffectiveDate, dstrAccountNum, dstrBrokerCode, 
                        dstrBranchCode, dstrSlsRepCode, pFundFeeList, idDataGroup) <= WARNING 
                        && pFundFeeList)
                  {
                     pFundFeeList->getField (ifds::Rate, strSFACRate, idDataGroup);
                     baseCommApplicable = true;
                  }
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeFundAlloc.cpp-arc  $
// 
//    Rev 1.117   Jul 31 2012 16:42:10   wp040027
// Sync up: IN# 3006862-CPF-Enable Fee in PAC/Corrected default Fee in PAC and Trade screen/Max Fee Validation
// 
//    Rev 1.116   Jul 30 2012 09:09:10   wp040027
// P0198518 - RDR Functionality - Review Comment incorporated
// 
//    Rev 1.115   Jul 26 2012 10:49:38   wp040027
// P0198518 - RDR Functionality
// 
//    Rev 1.114   Jul 06 2012 17:04:06   if991250
// IN2984281 Split commission refresh for GI Attrib changes
// 
//    Rev 1.113   Apr 16 2012 23:22:16   popescu
// 2901148 - Gurantee Flag Override
// 
//    Rev 1.112   Apr 11 2012 17:34:10   dchatcha
// IN# 2914672 - P0186479 Issues on Guarantee Override field on Trade Entry screen
// 
//    Rev 1.111   Apr 11 2012 12:21:26   dchatcha
// IN# 2914672 - P0186479 Issues on Guarantee Override field on Trade Entry screen
// 
//    Rev 1.110   Apr 11 2012 11:43:16   dchatcha
// IN# 2901157 - Issue on SEG Trade Processing, revise allocation related logics.
// 
//    Rev 1.109   Jan 26 2012 14:34:38   if991250
// P0186477- GIA trading Screen Issue - Seg fund validation needs to be executed only if the fund category is segregated ('S').
// 
//    Rev 1.108   Nov 27 2011 19:43:38   popescu
// INA Commission Work
// 
//    Rev 1.107   Mar 04 2011 12:14:30   jankovii
// PET181943 FN01 - XMLPhase 2
// 
//    Rev 1.106   May 05 2010 16:59:06   popescu
// RESP / QESI Gap validation on bene alloc was triggered for transfers..
// 
//    Rev 1.105   Sep 16 2009 15:45:42   jankovii
// IN 1821187 - iFast/Desktop - Amount field is grade out in Allocation screen - Redemptions
// 
//    Rev 1.104   Jun 18 2009 02:56:04   kitticha
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
// 
//    Rev 1.103   01 Oct 2008 12:10:06   popescu
// Check in for incident 1419539
// 
//    Rev 1.102   Jan 29 2008 13:19:42   daechach
// IN#1134569 - Cancel of Transfer out Trade not Allowed.
// 
//    Rev 1.101   24 Jul 2007 20:13:50   popescu
// GAP 20 -22 AIM
// 
//    Rev 1.100   Dec 07 2006 11:56:00   jankovii
// Incident #682515 - Age restriction to purchase or switch to GSIP fund not working.
// 
//    Rev 1.99   Oct 30 2006 17:07:02   jankovii
// PET 2185 FN04 - Trade restrictions.
// 
//    Rev 1.98   Jun 14 2006 10:51:16   jankovii
// PET2102 FN02 - Manulife Flex  Trade/Systematic Entry.
// 
//    Rev 1.97   May 25 2006 09:38:24   jankovii
// PET 2102 FN02 - Manulife Flex Trade/Systematic Entry.
// 
//    Rev 1.96   Apr 11 2006 09:23:42   jankovii
// PET 1334 Alternative Product.
// 
//    Rev 1.95   Apr 06 2006 10:49:52   jankovii
// PET 1334 Alternative Product. Allow allocation if it is only one ond 100%.
// 
//    Rev 1.94   Mar 31 2006 13:53:32   jankovii
// PET 1334 - Alternative Product.
// 
//    Rev 1.93   Oct 04 2005 11:15:54   ZHANGCEL
// PET1244 - FN01 - Specify EventTransType to determine whether the SegCapRules needs to be involved
// 
//    Rev 1.92   Sep 28 2005 11:17:26   ZHANGCEL
// PET1244 FN01 -- Seg Fund Evolution enhancement
// 
//    Rev 1.91   Sep 27 2005 13:58:26   porteanm
// Incident 395614 - SegFundValidation, super ugly implementation when is too late for a change of design.
// 
//    Rev 1.90   Sep 26 2005 10:05:02   AGUILAAM
// IN 402898 - sync up from rel64; use SplitCommRebookTransID from view 54 to get splitcomm
// 
//    Rev 1.89   Sep 23 2005 18:26:22   ZHANGCEL
// PET1244 FN01 -- Seg Func Evolution enhancement
// 
//    Rev 1.88   Aug 25 2005 12:14:02   porteanm
// Incident 387964 - 0 Amount check, added back conditions.
// 
//    Rev 1.87   Aug 18 2005 14:37:14   porteanm
// incident 383289 - Trigger FundClass validation after Effective Date has been changed.
// 
//    Rev 1.86   Aug 09 2005 10:44:16   popescu
// Incident # 374150 - do not call validation if not necessary - for TR/EX
// 
//    Rev 1.85   Jul 15 2005 09:20:48   Yingbaol
// PET1235,FN01: Add Record ID ro field info
// 
//    Rev 1.84   Jul 08 2005 09:33:22   Yingbaol
// PET1235,FN01:transaction cancellation rebook
// 
//    Rev 1.83   Jun 28 2005 17:46:34   popescu
// Incident# 345035 - split commission refreshed if amount changes only if trade is not pending copying mode.
// 
//    Rev 1.82   Jun 27 2005 12:03:22   popescu
// Incindent 338408: force refreshes on split commission if user changes amount/roa value
// 
//    Rev 1.81   Jun 24 2005 10:38:24   Yingbaol
// Incindent338408: check ROAAmount before refreshing splitcommission.
// 
//    Rev 1.80   Jun 23 2005 17:48:42   Yingbaol
// Incident 338408, refresh split commission when amount is changed on trading.
// 
//    Rev 1.79   Jun 23 2005 17:03:56   Yingbaol
// Incident240683,Fix SplitCommission amount.
// 
//    Rev 1.78   Jun 15 2005 15:50:32   porteanm
// PET1024 FN40 - Guarantee Adjustments.
// 
//    Rev 1.77   Jun 01 2005 17:46:44   popescu
// PET 1203/05 - changed to dynamic_cast and check if pointer is null
// 
//    Rev 1.76   May 18 2005 09:03:40   yingbaol
// PET1203,FN01 Commission-Class A enhancement
// 
//    Rev 1.75   Apr 22 2005 17:28:20   aguilaam
// IN 290231, 275393, 290196 : set account number for call to view 60 and 151
// 
//    Rev 1.74   Mar 30 2005 14:57:16   popescu
// Incident# 275373, added an extra parameter to view 151 (TransId), split commission trans history/pending trades inquiry
// 
//    Rev 1.73   Mar 24 2005 10:40:32   popescu
// Incident # 260181, split commissions not applicable for ED's with deposittypes 9,10,18
// 
//    Rev 1.72   Feb 22 2005 17:37:34   popescu
// Incident# 247079, move the code to dovalidateall
// 
//    Rev 1.71   Feb 22 2005 10:37:16   popescu
// Incident# 247079, set the trade settle currency to alloc currency in a non-multi currency environment if one of the alloc funds change.
// 
//    Rev 1.70   Jan 21 2005 17:40:12   popescu
// PTS 10038130, split comm didn't show up due to a reversed condition
// 
//    Rev 1.69   Jan 18 2005 19:42:14   popescu
// PTS 10038609, acquisition does not get refreshed if split comm changes to default
// 
//    Rev 1.68   Jan 12 2005 17:18:24   popescu
// PTS 10037811, fixed pending trade issue with split commissions, also cleaned-up the fel/acq fee methods
// 
//    Rev 1.67   Dec 31 2004 13:38:48   popescu
// PTS 10037395, settlement currency should be set as required if for redemption the account closes or a full redemption is processed. Also, isFullNotCloseAcctRed method name to isFullRedemption
// 
//    Rev 1.66   Dec 29 2004 18:42:02   popescu
// PTS 10037326, allocations should not trigger amount is zero error if booking a purchase. Also, fixed allocations list selection.
// 
//    Rev 1.65   Dec 29 2004 15:43:36   popescu
// PTS 10037311, fund allocation should check the fund balance only for redemptions, since XR/TR's deal with the right side of the trade;
// 
//    Rev 1.64   Dec 02 2004 18:23:22   popescu
// PET 1117/06/56, trades processing/fees processing
// 
//    Rev 1.63   Dec 01 2004 10:19:10   popescu
// PET 1117/06, restored some of the missing pieces
// 
//    Rev 1.62   Nov 29 2004 20:30:54   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.61   Nov 27 2004 21:19:16   popescu
// PET 1117/06, trades processing
// 
//    Rev 1.60   Nov 18 2004 13:28:36   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.59   Nov 14 2004 14:57:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.58   Nov 06 2004 00:43:14   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.57   Sep 08 2004 18:15:54   ZHANGCEL
// 1.Code clean up to group transtypes together 
// 2.PET1094-FN8 -- AdminFee related changes
// 
//    Rev 1.56   May 13 2004 21:07:02   popescu
// PET 985, FN 01, LSIF Trade entry
// 
//    Rev 1.55   May 13 2004 10:45:56   AGUILAAM
// PTS 10029479 - purchase/PAC on US funds not allowed for RRSP accounts, applies to both single-fund and allocated transactions
// 
//    Rev 1.54   May 10 2004 20:28:46   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.53   Mar 25 2004 10:57:06   ZHANGCEL
// PTS 10028465: Fine tuneing for the previous fix
// 
//    Rev 1.52   Mar 24 2004 16:59:40   ZHANGCEL
// PTS 10028465: Rewrite code in TradeFundAlloc::getNumberOfUnits because the old code does not work properly
// 
//    Rev 1.51   Mar 23 2004 14:25:22   VADEANUM
// PTS 10027993 - TIK error message for Allocations.
// 
//    Rev 1.50   Feb 27 2004 11:08:10   AGUILAAM
// PET965_FN02: Added trade amount validation against account holdings (return error or warning)
// 
//    Rev 1.49   Jan 21 2004 18:12:20   popescu
// PTS 10026237,
// For allocated purchases the acquisition fee should be zero and split commissions default values are displayed as they are returned by view 158.
// Also, if no repeated record is returned by 158 set the IFee to the Fee field value of the fixed section of view 158 and follow the same validation rules, as if split commissions would exist.
// 
//    Rev 1.48   Dec 16 2003 12:42:38   popescu
// PTS 10024124
// 
//    Rev 1.47   Dec 15 2003 16:37:58   AGUILAAM
// PTS 10024124
// 
//    Rev 1.46   Dec 15 2003 13:35:04   popescu
// removed an erroneous if statement
// 
//    Rev 1.45   Dec 15 2003 11:55:10   popescu
// PTS 10023645, disable split commission button if 158 returns data not found, for various reasons
// 
//    Rev 1.44   Dec 12 2003 13:25:36   AGUILAAM
// PTS 10024124, split comm, re-work
// 
//    Rev 1.43   Dec 08 2003 15:28:46   popescu
// PTS 10023645, split commission re-work
// 
//    Rev 1.42   Nov 14 2003 10:39:22   ZHANGCEL
// PTS ticket 10023920: The last paremeter  blIsAtCostTIK of function getAtCostTIKStatus() should pass by reference instead of pass by value
// 
//    Rev 1.41   Oct 14 2003 10:38:26   VADEANUM
// PTS 10021935 - Allocation screen Percent Total is 200 - added 
// setAmountField as Read Only or not...
// 
//    Rev 1.40   Oct 03 2003 16:12:20   FENGYONG
// PTS 10020517, duplicate error message 
// 
//    Rev 1.39   Oct 03 2003 11:28:40   popescu
// PTS 10018428 & 10017258 removed the assignement of the InterestRate field of the TransSeq from Trade CBO, and added the correct assigmenent of the TransSeq field to the allocation object based on the Pending trade object
// 
//    Rev 1.38   Oct 03 2003 10:22:04   HSUCHIN
// PTS 10022324 - bug fix with AMS limitation check during cycle.  Record Type was not set hence AMS code not properly set to distrib-detl record.
// 
//    Rev 1.37   Sep 26 2003 17:28:34   VADEANUM
// PTS 10021901 & 10021935 - WHTax - Allocations - Work in progress.
// 
//    Rev 1.36   Sep 08 2003 17:11:14   popescu
// PET 809_FN_02, fixes after performing integrated unit testing with the view team
// 
//    Rev 1.35   Sep 05 2003 10:18:58   popescu
// synch-up for 52 fix. PTS 10018366
// 
//    Rev 1.34   Sep 03 2003 14:25:46   HSUCHIN
// Bug fix to allocations where default allocations/ams allocation did not validate fund/class for stop flags
// 
//    Rev 1.33   Sep 01 2003 21:32:42   popescu
// PET 809, FN 02 CIBC Multi Fund Transfer
// 
//    Rev 1.32   Aug 25 2003 18:39:54   WINNIE
// Non close account full redemption code enhancement : If full redemption is indicated, set the percentage to 100% (for processing purpose) and set the allocpercentage to read only. Same logic applies to new object recreation. Modify doInitwithdefaultValue to invoke this the new method
// 
//    Rev 1.31   Aug 19 2003 11:50:44   popescu
// PTS 10018428 and PTS 10018433
// although explanations have been provided and action items have been added for the view team, further testing for these two tickets revealed an issue related to setting the transaction sequence for an allocated transaction details. The sequence has been correctly set to the TradeFundAlloc object
// 
//    Rev 1.30   Aug 18 2003 19:39:06   popescu
// PTS 10020184, synch-up with 51 and fix PTS
// 
//    Rev 1.29   Jun 18 2003 12:22:06   popescu
// minor comp error
// 
//    Rev 1.28   Jun 17 2003 11:02:48   VADEANUM
// PTS 10017735 - replaced Transfer::isSpecialExchOrTIK() with Transfer::getAtCostTIKStatus().
// 
//    Rev 1.27   Jun 16 2003 20:36:06   popescu
// minor
// 
//    Rev 1.26   Jun 16 2003 20:12:20   popescu
// minor change
// 
//    Rev 1.25   Jun 16 2003 18:38:32   WINNIE
// Ticket 10018432 : Get default rate failed due to fund and class from trade are blank for allocation trade. Get fund and class from the TradeFundAlloc object instead
// 
//    Rev 1.24   Jun 02 2003 18:20:04   popescu
// removed setSplitRate total since is not used anymore. The amount on a split commission should be set by using the Amount field of the SplitCommission list
// 
//    Rev 1.23   May 30 2003 19:20:10   popescu
// PTS 10017741
// 
//    Rev 1.22   May 16 2003 17:18:32   popescu
// now the transaction details object asks trade fund alloc for its plit commission
// 
//    Rev 1.21   May 15 2003 15:03:40   popescu
// fixes for a crash in PendingTrades, split comm
// 
//    Rev 1.20   May 13 2003 19:38:14   popescu
// PTS 10016228 & 10016241
// 
//    Rev 1.19   May 13 2003 10:07:16   popescu
// Split commission re-work
// 
//    Rev 1.18   Apr 29 2003 17:14:44   popescu
// PTS 10016204
// 
//    Rev 1.17   Apr 22 2003 14:51:26   FENGYONG
// fix stripAll(',') for multilanguage and 
// change 100.00 to 100
// 
//    Rev 1.16   Apr 14 2003 16:27:40   popescu
// PTS 10011081- split commision amount is being calculated by the view side
// 
//    Rev 1.15   Mar 21 2003 18:27:06   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.14   Dec 17 2002 13:50:22   YINGBAOL
// Put some comment line back for PTS 10011929
// 
//    Rev 1.13   Nov 29 2002 10:34:10   KOVACSRO
// rxTransType changes
// 
//    Rev 1.12   Oct 09 2002 23:55:10   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.11   Oct 09 2002 15:00:54   HSUCHIN
// sync up with 1.5.1.1
// 
//    Rev 1.10   Sep 16 2002 14:25:58   HSUCHIN
// sync up with 1.5.1.0
// 
//    Rev 1.9   Aug 29 2002 12:56:54   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.8   Aug 20 2002 16:55:22   KOVACSRO
// If DefRedCodeFlag is turned off, don't check for At Cost.
// 
//    Rev 1.7   Aug 19 2002 17:08:46   KOVACSRO
// Added validation for At Cost exchange or TIK
// 
//    Rev 1.6   Aug 13 2002 17:09:46   HSUCHIN
// change calling method to trade splitCommAllow to prevent infinite loop.
// 
//    Rev 1.5   Jul 02 2002 11:59:16   KOVACSRO
// Using SysCurrency rather than SettleCurrency to issue the 'Foreign Currency' warning message.
// 
//    Rev 1.4   Jun 27 2002 17:21:26   KOVACSRO
// AllocAmtType versus AmountType.
// 
//    Rev 1.3   24 May 2002 15:49:42   KOVACSRO
// some fixes.
// 
//    Rev 1.2   22 May 2002 18:30:06   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   08 May 2002 17:11:32   KOVACSRO
// More implementation.
// 
//    Rev 1.1   08 May 2002 17:05:36   KOVACSRO
// More implementation.
// 
//    Rev 1.1   08 May 2002 17:04:22   KOVACSRO
// More implementation.
// 
//    Rev 1.0   29 Apr 2002 16:57:48   KOVACSRO
// Initial revision.
 * 
 * 
 */