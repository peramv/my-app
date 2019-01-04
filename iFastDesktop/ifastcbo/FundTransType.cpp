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
//    Copyright 2002 by International Finanical Data Services Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundTransType.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : January 9, 2003
// ^CLASS    : FundTransType
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundtranstype.hpp"
#include "fundlmtoverride.hpp"
#include "fundlmtoverridelist.hpp"
#include "Trade.hpp"
#include "MFAccount.hpp"
#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0236_vw.hpp>

#define EXTRACT_VALUE(s, val) \
      pos = s.find (I_(",")); \
      val = s.substr (0, pos);

#define CHOP_STRING(s) \
         pos = s.find (I_(",")); \
         pos = pos != DString::npos && pos + 1 <= s.length() ? pos + 1 : DString::npos; \
         if (pos != DString::npos) \
            s = s.substr (pos); \
         else \
            s = NULL_STRING;

namespace
{
   const I_CHAR * const CLASSNAME     =     I_("FundTransType");
   const I_CHAR * const YES           =     I_("Y");
   const I_CHAR * const NO            =     I_("N");
   const I_CHAR * const EWI_ERROR     =     I_ ("E");
   const I_CHAR * const EWI_WARNING   =     I_ ("W");

}

namespace RULE_TYPE
{
   /***** Possible Limitmation Code (misc-info group code 'FY')
   Code   Description
   ----------------------------------
   01     Min. Init. Purchase
   02     Min. Subseq. Purchase
   03     Stop Purchase
   04     Stop Redemption
   05     Stop Transfer In
   06     Stop Transfer Out
   07     P.A.C. Minimum
   08     Stop P.A.C.
   09     Stop S.W.P.
   10     Stop Auto Transfer In
   11     Stop Auto Transfer Out
   15     Min. Units Purchase
   20     Broker Elig. Override-Redemption/Transfer Out
   21     Broker Elig. Override-Trf In Kind
   36     Stop Amonut Trade
   43     Bankruptcy
   38	  Rollover Ignore acct stop Transfer In
   39	  Rollover Ignore acct stop Transfer Out
   *******/
   extern const I_CHAR * const MIN_INIT_PUR_AMT;
   extern const I_CHAR * const MIN_SUB_SEQ_PUR; 
   extern const I_CHAR * const STOP_PUR;
   extern const I_CHAR * const STOP_RED;
   extern const I_CHAR * const STOP_TRFER_IN;
   extern const I_CHAR * const STOP_TRFER_OUT;
   extern const I_CHAR * const PAC_MIN_AMT;
   extern const I_CHAR * const STOP_PAC;
   extern const I_CHAR * const STOP_SWP;
   extern const I_CHAR * const STOP_ATI;
   extern const I_CHAR * const STOP_ATO;
   extern const I_CHAR * const MIN_UNIT_PUR;
   extern const I_CHAR * const BRK_PW_TRFOUT;
   extern const I_CHAR * const BRK_TRFIN_KIND;
   extern const I_CHAR * const STOP_AMT_TRADE; 
   extern const I_CHAR * const BANKRUPTCY;
   extern const I_CHAR * const SKIP_ACCT_STOP_FOR_ROLLOVER_EXCHANGE_IN;
   extern const I_CHAR * const SKIP_ACCT_STOP_FOR_ROLLOVER_EXCHANGE_OUT;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId OverrideExists;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId StopOverrideRule;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_IN;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE; 
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE_IN;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE_OUT;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH_IN;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH_OUT;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//   Field DD Id,        State Flags,       Group Flags 
   {ifds::TransType,       BFCBO::NONE, 0}, 
   {ifds::OverrideExists,  BFCBO::NONE, 0}, 
   {ifds::FundCode,        BFCBO::NONE, 0}, 
   {ifds::ClassCode,       BFCBO::NONE, 0},
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);


//****************************************************************************
FundTransType::FundTransType (BFAbstractCBO &parent) : MFCanBFCbo(parent),
_stopCode (NULL_STRING),
_initMinCode (NULL_STRING),
_subseqMinCode (NULL_STRING),
_unitMinCode (NULL_STRING),
_stopAmtTradeCode (NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
   registerMemberData ( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                        0, NULL);
}

//****************************************************************************
FundTransType::~FundTransType()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}     

//****************************************************************************
SEVERITY FundTransType::init ( const DString &transType, 
                               const DString &fundCode, 
                               const DString &classCode, 
                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init"));

   setFieldNoValidate (ifds::TransType, transType, BF::HOST, false); 
   setFieldNoValidate (ifds::OverrideExists, YES, BF::HOST, false); 
   setFieldNoValidate (ifds::FundCode, fundCode, BF::HOST, false); 
   setFieldNoValidate (ifds::ClassCode, classCode, BF::HOST, false); 
   setLimitationCode (BF::HOST);
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY FundTransType::getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList, 
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFundLmtOverrideList"));
   pFundLmtOverrideList = NULL;
   
   DString transType,
      overrideExists,
      fundCode,
      classCode;

   getField (ifds::TransType, transType, idDataGroup);
   getField (ifds::OverrideExists, overrideExists, idDataGroup);
   getField (ifds::FundCode, fundCode, idDataGroup);
   getField (ifds::ClassCode, classCode, idDataGroup);

   //check cbobase to see if we've already built it
   //if not built, create and store with base
   DString strTag = I_("FundLmtOverrideList");
   pFundLmtOverrideList = 
      dynamic_cast<FundLmtOverrideList *>(BFCBO::getObject(strTag, idDataGroup));

// since override is initialize as 'Yes', 
//if override is Yes but no list exist, then this list is never initialized
   if (!pFundLmtOverrideList && overrideExists.strip().upperCase() == YES)
   {
      pFundLmtOverrideList = new FundLmtOverrideList (*this);
      if (pFundLmtOverrideList->init (fundCode, classCode, transType) <= WARNING)
      {
         setObject (pFundLmtOverrideList, strTag, OBJ_ACTIVITY_NONE, idDataGroup); 
         pFundLmtOverrideList->getField (ifds::OverrideExists, overrideExists, idDataGroup);
         setFieldNoValidate (ifds::OverrideExists, overrideExists, idDataGroup, false); 
      }
      else
      {
         delete pFundLmtOverrideList;
         pFundLmtOverrideList = NULL;
         setFieldNoValidate (ifds::OverrideExists, NO, idDataGroup, false); 
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Different code represents different limitation setttings. 
// Need the code to get the right record
void FundTransType::setLimitationCode (const BFDataGroupId& idDataGroup)
{
   DString transType;
   getField(ifds::TransType, transType, idDataGroup);
   if (DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE))
   {
      _stopCode = RULE_TYPE::STOP_PUR;
      _initMinCode = RULE_TYPE::MIN_INIT_PUR_AMT;
      _subseqMinCode = RULE_TYPE::MIN_SUB_SEQ_PUR;
      _unitMinCode = RULE_TYPE::MIN_UNIT_PUR;
      _stopAmtTradeCode = RULE_TYPE::STOP_AMT_TRADE;

      _stopCode += I_(",");
      _stopCode += RULE_TYPE::BANKRUPTCY;
   }
   else if (DSTCommonFunctions::codeInList (transType, TRADETYPE::REDEMPTION_LIKE))
   {
      _stopCode = RULE_TYPE::STOP_RED;
      _entityOverride = RULE_TYPE::BRK_PW_TRFOUT;
      _stopAmtTradeCode = RULE_TYPE::STOP_AMT_TRADE; 

      _stopCode += I_(",");
      _stopCode += RULE_TYPE::BANKRUPTCY;
   }
   else if (transType == TRADETYPE::TRANSFER_IN)
   {
      _stopCode = RULE_TYPE::STOP_TRFER_IN;
      _entityOverride = RULE_TYPE::BRK_TRFIN_KIND;
      _stopAmtTradeCode = RULE_TYPE::STOP_AMT_TRADE;

      _stopCode += I_(",");
      _stopCode += RULE_TYPE::BANKRUPTCY;
   }   
   else if (transType == TRADETYPE::TRANSFER_OUT)
   {
      _stopCode = RULE_TYPE::STOP_TRFER_OUT;
      _entityOverride = RULE_TYPE::BRK_PW_TRFOUT;
      _stopAmtTradeCode = RULE_TYPE::STOP_AMT_TRADE;

      _stopCode += I_(",");
      _stopCode += RULE_TYPE::BANKRUPTCY;
   }
   else if (transType == TRADETYPE::EXCHANGE_IN || transType == TRADETYPE::INTER_CLASS_SWITCH_IN)
   {
      _stopCode = RULE_TYPE::STOP_TRFER_IN;
      _stopAmtTradeCode = RULE_TYPE::STOP_AMT_TRADE;

      _stopCode += I_(",");
      _stopCode += RULE_TYPE::BANKRUPTCY;
   }
   else if (transType == TRADETYPE::EXCHANGE_OUT || transType == TRADETYPE::INTER_CLASS_SWITCH_OUT)
   {
      _stopCode = RULE_TYPE::STOP_TRFER_OUT;
      _stopAmtTradeCode = RULE_TYPE::STOP_AMT_TRADE;

      _stopCode += I_(",");
      _stopCode += RULE_TYPE::BANKRUPTCY;
   }
   else if (transType == TRADETYPE::PAC)
   {
      _stopCode = RULE_TYPE::STOP_PAC;
      _initMinCode = RULE_TYPE::PAC_MIN_AMT;   
      _subseqMinCode = RULE_TYPE::PAC_MIN_AMT;

      _stopCode += I_(",");
      _stopCode += RULE_TYPE::BANKRUPTCY;
   }
   else if (transType == TRADETYPE::SWP)
   {
      _stopCode = RULE_TYPE::STOP_SWP;

      _stopCode += I_(",");
      _stopCode += RULE_TYPE::BANKRUPTCY;
   }
   else if (transType == TRADETYPE::AUTO_TRANSFER_IN)
   {
      _stopCode = RULE_TYPE::STOP_ATI;

      _stopCode += I_(",");
      _stopCode += RULE_TYPE::BANKRUPTCY;
   }
   else if (transType == TRADETYPE::AUTO_TRANSFER_OUT)
   {
      _stopCode = RULE_TYPE::STOP_ATO;

      _stopCode += I_(",");
      _stopCode += RULE_TYPE::BANKRUPTCY;
   }
   else if (transType == TRADETYPE::ROLLOVER_EXCHANGE_IN)
   {
	  _stopCode = RULE_TYPE::SKIP_ACCT_STOP_FOR_ROLLOVER_EXCHANGE_IN;
      _stopCode += I_(",");
   }
   else if (transType == TRADETYPE::ROLLOVER_EXCHANGE_OUT)
   {
	  _stopCode = RULE_TYPE::SKIP_ACCT_STOP_FOR_ROLLOVER_EXCHANGE_OUT;
      _stopCode += I_(",");
   }
}

//******************************************************************************
SEVERITY FundTransType::getStopFlag ( const DSTCWorkSession &workSession,
                                      const DString &accountNum, 
                                      DString &stopFlag,
                                      DString &stopSeverityCode,
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getStopFlag"));
   DString fundCode, 
      classCode;
   FundDetail *pFundDetail = NULL;

//initialize, just in case, 
   stopFlag = NO;
   stopSeverityCode = I_("I");
//fund detail is the 'grandparent' of this object
//look for stop flag at the FundDetail level,
//based on the transaction type   
   assert (getParent() && getParent()->getParent());
   
   BFFieldId stopFieldId = ifds::NullFieldId;
   DString transType;

   getField(ifds::TransType, transType, idDataGroup);
    if (DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE))
    {
        stopFieldId = ifds::StopPurchase;
    }
    else if (DSTCommonFunctions::codeInList (transType, TRADETYPE::REDEMPTION_LIKE))
    {
        stopFieldId = ifds::StopRed;
    }
    else if (transType == TRADETYPE::EXCHANGE_IN ||
             transType == TRADETYPE::INTER_CLASS_SWITCH_IN ||
             transType == TRADETYPE::TRANSFER_IN)
    {
        stopFieldId = ifds::StopXferIn;
    }
    else if (transType == TRADETYPE::EXCHANGE_OUT ||
             transType == TRADETYPE::INTER_CLASS_SWITCH_OUT ||
             transType == TRADETYPE::TRANSFER_OUT)
    {
        stopFieldId = ifds::StopXferOut;
    }
    else if (transType == TRADETYPE::PAC)
    {
        stopFieldId = ifds::StopPAC;
    }
    else if (transType == TRADETYPE::SWP)
    {
        stopFieldId = ifds::StopSWP;
    }
    else if (transType == TRADETYPE::AUTO_TRANSFER_IN)
    {
        stopFieldId = ifds::StopSysGenTrnfrIn;
    }   
    else if (transType == TRADETYPE::AUTO_TRANSFER_OUT)
    {
        stopFieldId = ifds::StopSysGenTrfrOut;
    }
    if (stopFieldId != ifds::NullFieldId)
    {
//get the stop flag from FundDetail
        getParent()->getParent()->getField ( stopFieldId, 
                                            stopFlag, 
                                            idDataGroup, 
                                            false);
        stopFlag.strip().upperCase();
        if (stopFlag == YES)
        {
            stopSeverityCode = I_("E");
        }
    }
 

    FundLmtOverrideList *pFundLmtOverrideList= NULL;

    if ( getFundLmtOverrideList ( pFundLmtOverrideList, 
                                    idDataGroup) <= WARNING &&
            pFundLmtOverrideList)
    {
        DString strStopCodeList(_stopCode);
        do
        {
            DString::size_type pos = 0;
            DString stopCode_;

            EXTRACT_VALUE(strStopCodeList, stopCode_);
            FundLmtOverride *pFundLmtOverride = NULL;

            if ( pFundLmtOverrideList->getFundLmtOverride ( workSession,
                                                            accountNum, 
                                                            //send the stop code, which matches the 'rule type'
                                                            stopCode_, 
                                                            pFundLmtOverride, 
                                                            idDataGroup) <= WARNING && 
            pFundLmtOverride)
            {
            pFundLmtOverride->getField (ifds::StopFlag, stopFlag, idDataGroup, false);
            stopFlag.strip().upperCase();
            pFundLmtOverride->getField (ifds::StopFlagSeverityCode, stopSeverityCode, idDataGroup, false);
            stopSeverityCode.strip().upperCase();
            }      
            CHOP_STRING (strStopCodeList);
        }
        while (strStopCodeList != NULL_STRING);
    }
 return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundTransType::getMinAmount ( const DSTCWorkSession &workSession,
                                       const DString &accountNum, 
                                       DString &minAmount,
                                       DString &minSeverityCode,
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getMinAmount"));

   DString fundCode, 
      classCode;
   FundDetail *pFundDetail = NULL;

//initialize, just in case, 
   minAmount = I_("0");
   minSeverityCode = I_("I");
//fund detail is the 'grandparent' of this object
//look for min amount value at the FundDetail level,
//based on the transaction type   
   assert (getParent() && getParent()->getParent());
   
   BFFieldId minFieldId = ifds::NullFieldId;
   DString transType;

   getField(ifds::TransType, transType, idDataGroup);
   if (DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE))
   {
      minFieldId = ifds::MinInitPurAmt;
   }
   else if (DSTCommonFunctions::codeInList (transType, TRADETYPE::REDEMPTION_LIKE))
   {
      minFieldId = ifds::MinInitRedAmt;
   }
   else if (transType == TRADETYPE::PAC)
   {
      minFieldId = ifds::MinPAC;
   }
   else if (transType == TRADETYPE::SWP)
   {
      minFieldId = ifds::MinSWP;
   }

   if (minFieldId != ifds::NullFieldId)
   {
   //get the min amount value from FundDetail
      getParent()->getParent()->getField ( minFieldId, 
                                           minAmount, 
                                           idDataGroup, 
                                           false);
      minAmount.strip();
      if (minAmount != I_("0")) //a non zero-amount
      {
         minSeverityCode = I_("W");
      }
   }

   FundLmtOverrideList *pFundLmtOverrideList= NULL;

   if ( getFundLmtOverrideList ( pFundLmtOverrideList, 
                                 idDataGroup) <= WARNING &&
        pFundLmtOverrideList)
   {
      FundLmtOverride *pFundLmtOverride = NULL;
      
      if ( pFundLmtOverrideList->getFundLmtOverride ( workSession,
                                                      accountNum, 
                                                      //send the initial min code, which matches the 'rule type'
                                                      _initMinCode, 
                                                      pFundLmtOverride, 
                                                      idDataGroup) <= WARNING && 
           pFundLmtOverride)
      {
         pFundLmtOverride->getField (ifds::MinInitAmt, minAmount, idDataGroup, false);
         pFundLmtOverride->getField (ifds::MinInitAmtSeverityCode, minSeverityCode, idDataGroup, false);
         minSeverityCode.strip().upperCase();
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundTransType::getSubseqMinAmount ( const DSTCWorkSession &workSession,
                                             const DString &accountNum, 
                                             DString &subseqMinAmount,
                                             DString &subseqMinSeverityCode,
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getSubseqAmount"));

   DString fundCode, 
      classCode;
   FundDetail *pFundDetail = NULL;

//initialize, just in case, 
   subseqMinAmount = I_("0");
   subseqMinSeverityCode = I_("I");
//fund detail is the 'grandparent' of this object
//look for subseq amount value at the FundDetail level,
//based on the transaction type   
   assert (getParent() && getParent()->getParent());
   
   BFFieldId subseqMinFieldId = ifds::NullFieldId;
   DString transType;

   getField (ifds::TransType, transType, idDataGroup);
   if (DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE))
   {
      subseqMinFieldId = ifds::MinSubPurAmt;
   }
   else if (DSTCommonFunctions::codeInList (transType, TRADETYPE::REDEMPTION_LIKE))
   {
      subseqMinFieldId = ifds::MinSubRedAmt;
   }
   else if (transType == TRADETYPE::PAC)
   {
      subseqMinFieldId = ifds::MinPAC;
   }
   else if (transType == TRADETYPE::SWP)
   {
      subseqMinFieldId = ifds::MinSWP;
   }
   if (subseqMinFieldId != ifds::NullFieldId)
   {
   //get the subseq min amount value from FundDetail
      getParent()->getParent()->getField ( subseqMinFieldId, 
                                           subseqMinAmount, 
                                           idDataGroup, 
                                           false);
      subseqMinAmount.strip();
      if (subseqMinAmount != I_("0")) //a non zero-amount
      {
         subseqMinSeverityCode = I_("W");
      }
   }

   FundLmtOverrideList *pFundLmtOverrideList= NULL;

   if ( getFundLmtOverrideList ( pFundLmtOverrideList, 
                                 idDataGroup) <= WARNING &&
        pFundLmtOverrideList)
   {
      FundLmtOverride *pFundLmtOverride = NULL;
      
      if ( pFundLmtOverrideList->getFundLmtOverride ( workSession,
                                                      accountNum, 
                                                      //send the subseq min code, which matches the 'rule type'
                                                      _subseqMinCode, 
                                                      pFundLmtOverride, 
                                                      idDataGroup) <= WARNING && 
           pFundLmtOverride)
      {
         pFundLmtOverride->getField (ifds::MinSubSeqAmt, subseqMinAmount, idDataGroup, false);
         pFundLmtOverride->getField (ifds::MinSubSeqAmtSeverityCode, subseqMinSeverityCode, idDataGroup, false);
         subseqMinSeverityCode.strip().upperCase();
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundTransType::getMinUnits ( const DSTCWorkSession &workSession,
                                      const DString &accountNum, 
                                      DString &minUnits,
                                      DString &minSeverityCode,
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getMinUnits"));

//initialize, just in case, 
   minUnits = I_("0");
   minSeverityCode = I_("I");
   FundLmtOverrideList *pFundLmtOverrideList= NULL;

   if ( getFundLmtOverrideList ( pFundLmtOverrideList, 
                                 idDataGroup) <= WARNING &&
        pFundLmtOverrideList)
   {
      FundLmtOverride *pFundLmtOverride = NULL;
      
      if ( pFundLmtOverrideList->getFundLmtOverride ( workSession,
                                                      accountNum, 
                                                      //send the initial unit min code, which matches the 'rule type'
                                                      _unitMinCode, 
                                                      pFundLmtOverride, 
                                                      idDataGroup) <= WARNING && 
           pFundLmtOverride)
      {
         pFundLmtOverride->getField (ifds::MinSubSeqAmt, minUnits, idDataGroup, false);
         pFundLmtOverride->getField (ifds::MinSubSeqAmtSeverityCode, minSeverityCode, idDataGroup, false);
         minSeverityCode.strip().upperCase();
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY FundTransType::getEntityOverride ( const DSTCWorkSession &workSession,
                                            const DString &accountNum, 
                                            DString &entityOverride,
                                            DString &overrideSeverityCode,
                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getEntityOverride"));

//initialize, just in case, 
   entityOverride = N;
   overrideSeverityCode = I_("I");
   FundLmtOverrideList *pFundLmtOverrideList= NULL;

   if ( getFundLmtOverrideList ( pFundLmtOverrideList, 
                                 idDataGroup) <= WARNING &&
        pFundLmtOverrideList)
   {
      FundLmtOverride *pFundLmtOverride = NULL;
      
      if ( pFundLmtOverrideList->getFundLmtOverride ( workSession,
                                                      accountNum, 
                                                      //send the initial unit min code, which matches the 'rule type'
                                                      _entityOverride, 
                                                      pFundLmtOverride, 
                                                      idDataGroup) <= WARNING && 
           pFundLmtOverride)
      {
         pFundLmtOverride->getField (ifds::StopFlag, entityOverride, idDataGroup, false);
         pFundLmtOverride->getField (ifds::StopFlagSeverityCode, overrideSeverityCode, idDataGroup, false);
         overrideSeverityCode.upperCase();
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY FundTransType::getStopAmtTradeFlag ( const DSTCWorkSession &workSession,
                                      const DString &accountNum, 
                                      DString &stopFlag,
                                      DString &stopSeverityCode,
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getStopAmtTradeFlag"));

   FundLmtOverrideList *pFundLmtOverrideList= NULL;

   if ( getFundLmtOverrideList ( pFundLmtOverrideList, 
                                 idDataGroup) <= WARNING &&
         pFundLmtOverrideList)
   {
      FundLmtOverride *pFundLmtOverride = NULL;
      
      if ( pFundLmtOverrideList->getFundLmtOverride ( workSession,
                                                      accountNum, 
                                                      //send the stop code, which matches the 'rule type'
                                                      _stopAmtTradeCode, 
                                                      pFundLmtOverride, 
                                                      idDataGroup) <= WARNING && 
           pFundLmtOverride)
      {
         pFundLmtOverride->getField (ifds::StopFlag, stopFlag, idDataGroup, false);
         stopFlag.strip().upperCase();
         pFundLmtOverride->getField (ifds::StopFlagSeverityCode, stopSeverityCode, idDataGroup, false);
         stopSeverityCode.strip().upperCase();
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundTransType.cpp-arc  $
// 
//    Rev 1.26   Jan 16 2012 16:22:04   dchatcha
// IN# 2796443 - Validation rule for Allocated Auto Transfer, back-end take stop flag to be considered.
// 
//    Rev 1.25   Jan 10 2012 20:59:20   dchatcha
// IN# 2796443 - Validation rule for Allocated Auto Transfer, forgot checking for redemption....
// 
//    Rev 1.24   Jan 09 2012 18:43:24   dchatcha
// IN# 2796443 - Validation rule for Allocated Auto Transfer
// 
//    Rev 1.23   Dec 26 2011 21:03:06   dchatcha
// IN# 2783697 - Description changes for table 0999 and Escrow
// 
//    Rev 1.22   Jul 20 2011 15:25:58   wp040027
// PET P0186065 - Aggregated Amount Orders via Swift- Implementation of Rule 36 on Fund
// 
//    Rev 1.21   24 Jul 2007 20:13:06   popescu
// GAP 20 -22 AIM
// 
//    Rev 1.20   Jan 13 2005 13:22:44   popescu
// PTS 10037380, read the min units puchase override rule value (rule type = 15)  from fields MinSubSeqAmt ;
// 
//    Rev 1.19   Nov 14 2004 14:43:22   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.18   Nov 04 2004 17:37:48   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.17   Sep 08 2004 18:10:14   ZHANGCEL
// PET1094-FN8 -- AdminFee related changes
// 
//    Rev 1.16   Aug 17 2004 17:29:48   popescu
// PTS 10033134, convert the severity codes for the override limits records to uppercase
// 
//    Rev 1.15   Aug 16 2004 15:17:56   popescu
// PTS 10033134, changed the default value for stop purchases/redemption, error level from W to E.
// 
//    Rev 1.14   Jul 08 2004 16:13:08   popescu
// PTS 10032006, check the trade minimum amount for to side funds, for rollovers transaction type
// 
//    Rev 1.13   Jun 25 2004 19:05:18   popescu
// PTS 10031525, Fund limitation overrides issue
// 
//    Rev 1.12   Jun 25 2004 16:38:24   popescu
// PST 10031525, fund limitation override issues
// 
//    Rev 1.11   Apr 21 2003 14:59:06   popescu
// added new trans type names
// 
//    Rev 1.10   Apr 04 2003 10:18:32   popescu
// split commsion work
// 
//    Rev 1.9   Mar 21 2003 19:50:00   PURDYECH
// Sync 1.5.1.0 back to trunk
// 
//    Rev 1.8   Mar 21 2003 13:09:38   WINNIE
// assign classcode to avoid error in view call
// 
//    Rev 1.7   Mar 20 2003 11:25:34   popescu
// Early redemption fee and short term transfer fee work
// 
//    Rev 1.6   Mar 19 2003 14:44:22   popescu
// Exchange Out fee automatic transfer, and Trad
// 
//    Rev 1.5.1.0   Mar 21 2003 18:12:18   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Mar 18 2003 21:10:28   popescu
// Exchange out fee work
// 
//    Rev 1.4   Mar 11 2003 10:31:26   popescu
// Synch-up with Pre51
// 
//    Rev 1.3.1.0   Mar 08 2003 12:48:56   WINNIE
// Bug fix : existing logic does not match corresponding limitation code to the corresponding limitation setting, it is likely to get the wrong record if there are multiple limitation under same fund/class but for different transtype and different limitation code.
// 
//    Rev 1.3   Feb 03 2003 14:38:52   WINNIE
// do not override default value
// 
//    Rev 1.2   Jan 30 2003 19:05:02   WINNIE
// Call by reference for input parameters of getStopFlag, override and minimum amount 
// 
//    Rev 1.1   Jan 21 2003 18:32:34   WINNIE
// add method getMinAmountFlag for systematic minimum edit check; add register data in contractor to correct field assignment; pass fund and class for invoking fund limitation override CBO
// 
//    Rev 1.0   Jan 12 2003 16:05:40   WINNIE
// Initial revision.
// 
*/