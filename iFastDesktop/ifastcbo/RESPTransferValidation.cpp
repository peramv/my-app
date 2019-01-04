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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPTransferValidation.cpp
// ^AUTHOR : Unknown
// ^DATE   : March, 2010
//
// ^CLASS    : RESPTransferValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "RESPTransferValidation.hpp"
#include "RESPTransfer.hpp"
#include <ifastdataimpl\dse_dstc0407_req.hpp>
#include <ifastdataimpl\dse_dstc0407_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESP_TRANSFER_UPDATE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId EligDateforCLB;
   extern CLASS_IMPORT const BFNumericFieldId HistNonTrustYear;
   extern CLASS_IMPORT const BFTextFieldId TotTransfINDC;
   extern CLASS_IMPORT const BFDecimalFieldId QESIPaid;   
}

namespace CND
{  
   extern const long ERR_RESP_PLAN_LIMIT_EXCEEDED;
   extern const long WARN_RESP_PLAN_LIMIT_EXCEEDED;
   extern const long ERR_RESP_YEAR_LIMIT_EXCEEDED;
   extern const long WARN_RESP_YEAR_LIMIT_EXCEEDED;
   extern const long ERR_RESP_BENEF_OVER21;
   extern const long WARN_RESP_BENEF_OVER21;
   extern const long ERR_RESP_BENEF_OVER31;
   extern const long WARN_RESP_BENEF_OVER31;
   extern const long ERR_LIFETIME_CONTRIB_LIMITS_NOT_SETUP;
   extern const long WARN_LIFETIME_CONTRIB_LIMITS_NOT_SETUP;
   extern const long ERR_ANNUAL_CONTRIB_LIMITS_NOT_SETUP;
   extern const long WARN_ANNUAL_CONTRIB_LIMITS_NOT_SETUP;
   extern const long ERR_GRANT_AMOUNT_NOT_APPLICABLE;
   extern const long WARN_GRANT_AMOUNT_NOT_APPLICABLE;
   extern const long ERR_BENEF_NOT_ELIGIBLE_FOR_CLB;
   extern const long WARN_BENEF_NOT_ELIGIBLE_FOR_CLB;
   extern const long ERR_BALANCE_LESS_THEN_TRANS_AMOUNT;
   extern const long WARN_BALANCE_LESS_THEN_TRANS_AMOUNT;
   extern const long ERR_BALANCE_LESS_THEN_ENTERED_TRANS_AMOUNT;
   extern const long WARN_BALANCE_LESS_THEN_ENTERED_TRANS_AMOUNT;
   extern const long ERR_CLB_AMOUNT_CANNOT_BE_TRANSFERED;
   extern const long WARN_CLB_AMOUNT_CANNOT_BE_TRANSFERED;
   extern const long ERR_MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR;
   extern const long WARN_MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR;
   extern const long ERR_NON_TRUSTEE_UPDATE_HIST_INFO_REQ;
   extern const long WARN_NON_TRUSTEE_UPDATE_HIST_INFO_REQ;
   //P0185010.FN02.R01.02 - new field CESG Grant paid
   extern const long ERR_CESG_LIMIT_EXCEEDED;
   extern const long WARN_CESG_LIMIT_EXCEEDED;
   extern const long ERR_QESI_LIMIT_EXCEEDED;
   extern const long WARN_QESI_LIMIT_EXCEEDED;
   extern const long ERR_CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE;
   extern const long WARN_CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE;
   extern const long ERR_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG;
   extern const long WARN_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG;
   extern const long ERR_AMOUNT_EXCEEDS_BCTESG_BALANCE;
   extern const long WARN_AMOUNT_EXCEEDS_BCTESG_BALANCE;
   extern const long ERR_TRANSFER_IN_WITH_BCTESG_CANNOT_BE_PROCESSED_BEFORE_DEFF;
   extern const long WARN_TRANSFER_IN_WITH_BCTESG_CANNOT_BE_PROCESSED_BEFORE_DEFF;
   extern const long ERR_TRADE_WILL_CREATE_NEGATIVE_NOTIONAL_BALANCE_UC_AC_YTD;
   extern const long WARN_TRADE_WILL_CREATE_NEGATIVE_NOTIONAL_BALANCE_UC_AC_YTD;
   extern const long ERR_NOTIONALS_MANUAL_OVERRIDE_RECOMMENDED_FOR_MULTIPLE_TRANSFERS;
   extern const long WARN_NOTIONALS_MANUAL_OVERRIDE_RECOMMENDED_FOR_MULTIPLE_TRANSFERS;
   extern const long ERR_NOTIONALS_MANUAL_OVERRIDE_MAY_BE_REQUIRED;
   extern const long WARN_NOTIONALS_MANUAL_OVERRIDE_MAY_BE_REQUIRED;
}

namespace
{
   const I_CHAR * const CLASSNAME                                       = I_ ("RESPTransferValidation");
   const I_CHAR * const VALIDATION                                      = I_ ("V");  
   const I_CHAR * const RESP_PLAN_LIMIT_EXCEEDED                        = I_("216");
   const I_CHAR * const RESP_YEAR_LIMIT_EXCEEDED                        = I_("217");
   const I_CHAR * const BENEFICIARY_IS_OVER_21                          = I_("726");
   const I_CHAR * const BENEFICIARY_IS_OVER_31                          = I_("999");
   const I_CHAR * const LIFETIME_CONTRIB_LIMITS_NOT_SETUP               = I_("1045");
   const I_CHAR * const ANNUAL_CONTRIB_LIMITS_NOT_SETUP                 = I_("1046");
   const I_CHAR * const GRANT_AMOUNT_NOT_APPLICABLE                     = I_("716"); 
   const I_CHAR * const BENEF_NOT_ELIGIBLE_FOR_CLB                      = I_("718"); 
   const I_CHAR * const BALANCE_LESS_THEN_TRANS_AMOUNT                  = I_("1080");
   const I_CHAR * const BALANCE_LESS_THEN_ENTERED_TRANS_AMOUNT          = I_("1081"); 
   const I_CHAR * const CLB_AMOUNT_CANNOT_BE_TRANSFERED                 = I_("719");
   const I_CHAR * const LIFETIME_LIMIT                                  = I_("LIFETIMELIMIT");
   const I_CHAR * const ANNUAL_LIMIT                                    = I_("ANNUALLIMIT");
   const I_CHAR * const TO_DATE                                         = I_("TODATE");
   const I_CHAR * const BENEF_NAME                                      = I_("BENNAME");
   const I_CHAR * const ELIGDATE                                        = I_("ELIGDATE");
   const I_CHAR * const MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR  = I_("1091");
   const I_CHAR * const NON_TRUSTEE_UPDATE_HIST_INFO_REQ                = I_("1119");
   //P0185010.FN02.R01.02 - new field CESG Grant paid 
   //const I_CHAR * const CESG_LIMIT_EXCEEDED                             = I_("1136");
   const I_CHAR * const WARNPARM14                                      = I_("WARNPARM14");
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const CESG_LIMIT_EXCEEDED;
   extern CLASS_IMPORT I_CHAR * const QESI_LIMIT_EXCEEDED;
   extern CLASS_IMPORT I_CHAR * const CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG;
   extern CLASS_IMPORT I_CHAR * const AMOUNT_EXCEEDS_BCTESG_BALANCE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN_WITH_BCTESG_CANNOT_BE_PROCESSED_BEFORE_DEFF;
   extern CLASS_IMPORT I_CHAR * const BALANCE_LESS_THEN_ENTERED_TRANS_AMOUNT;
   extern CLASS_IMPORT I_CHAR * const TRADE_WILL_CREATE_NEGATIVE_NOTIONAL_BALANCE_UC_AC_YTD;
   extern CLASS_IMPORT I_CHAR * const NOTIONALS_MANUAL_OVERRIDE_RECOMMENDED_FOR_MULTIPLE_TRANSFERS;
   extern CLASS_IMPORT I_CHAR * const NOTIONALS_MANUAL_OVERRIDE_MAY_BE_REQUIRED;
}

//******************************************************************************
RESPTransferValidation::RESPTransferValidation (BFAbstractCBO &parent)
: MFCanBFCbo (parent),
m_BenefName (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   setObjectAsList ();
}

//******************************************************************************
RESPTransferValidation::~RESPTransferValidation ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY RESPTransferValidation::init (const DString &strCallType,
                                       const DString &strTradeType,
                                       const DString &strTransId,
                                       const DString &strTransType,
                                       const DString &strDepositType,
                                       const DString &strRedCode,
                                       const DString &strAccountNum,
                                       const DString &strAccountTo,
                                       const DString &strTradeDate,
                                       const DString &strAmount,
                                       const DString &strRESPBenefName,
                                       const DString &strNEQ1,
                                       const DString &strNEQ2,
									   const DString &strAcctLvlOverride,
                                       //const DString &strEligibleTrfx,
                                       //const DString &strHistNonTrustYear,
                                       //const DString &strTotTransfINDC,
                                       const RESPTransfer *pRESPTransfer,
                                       const BFDataGroupId &idDataGroup,
                                       bool ignoreDataNotFound /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));

   m_BenefName = strRESPBenefName;

   BFData queryData  (ifds::DSTC0407_REQ);
   BFData repeatData  (ifds::DSTC0407_REQRepeat_Record);
   DString mgmtCoIdOut;

   // non repeating data
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::CallType, strCallType); 
   queryData.setElementValue (ifds::TradeType, strTradeType); 
   queryData.setElementValue (ifds::TransId, strTransId); 

   queryData.setElementValue (ifds::TransType, strTransType); 
   queryData.setElementValue (ifds::DepositType, strDepositType); 
   queryData.setElementValue (ifds::RedCode, strRedCode); 
   queryData.setElementValue (ifds::AccountNum, strAccountNum); 
   queryData.setElementValue (ifds::AccountTo, strAccountTo); 
   queryData.setElementValue (ifds::EffectiveDate, strTradeDate); 
   queryData.setElementValue (ifds::Amount, strAmount); 
   queryData.setElementValue (ifds::NEQ1, strNEQ1); 
   queryData.setElementValue (ifds::NEQ2, strNEQ2);
   queryData.setElementValue (ifds::AcctLvlOverride, strAcctLvlOverride);

   DString strRecordLevel;
   DString strRESPBenefIDFrom;
   DString strRESPTrfAllocEntityTypeFrom;
   DString strRESPTrfEntityTypeSeqFrom;
   DString strRESPBenefIDTo;
   DString strRESPTrfAllocEntityTypeTo;
   DString strRESPTrfEntityTypeSeqTo;
   DString strYTDContr;
   DString strTDContr;
   DString strGrantAmount;
   DString strAdditionalGrant;
   DString strCLBAmount;
   DString strPGrantAmount;
   DString strTDRedContrib;
   DString strTDRedEarning;
   DString strRedCESG;
   DString strRedCLB;
   DString strRedPGrant;
   DString strUCAmt;
   DString strACAmt;
   DString strPre98ContribAmt;
   DString strPre98RedContribAmt;
   DString strTransferPercent;
   DString strQESIUCAmount;
   DString strQESIACAmount;
   DString strQESIYTDContribution;
   DString strQESIBasicGrant;
   DString strQESIIncreaseAmt;
   DString strPre98QESIContrib;
   DString strPre2007QESIContrib;
   DString strRESPExtTrDetlUUID;
   DString strRESPExtTrDetlVer;
   DString strRESPContrDetlUUID;
   DString strRESPContrDetlVer;
   DString strHistNonTrustYear; 
   DString strTotTransfINDC;
   DString strEligibleTrfx;
   DString strCESGPaid;
   DString strQESIPaid;
   DString strSAGESGrant;
   DString strSAGESUCAmount;
   DString strSAGESACAmount;
   DString strBCTESGGrant;
   DString strUCRedAmt;
   DString strACRedAmt;
   DString strSAGESRedUCAmt;
   DString strSAGESRedACAmt;
   DString strQESIRedUCAmt;
   DString strQESIRedACAmt;
   DString strQESIRedYTDContrib;
   DString strPre2007QESIRedContrib;
   DString strRedAdditionalGrant;
   DString strRedSAGES;
   DString strQESIRedBasic;
   DString strQESIRedIncrease;
   DString strRedBCTESG;

   // get grant data:

   if (pRESPTransfer)
   {
      pRESPTransfer->getField (ifds::RecordLevel, strRecordLevel, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPBenefIDFrom, strRESPBenefIDFrom, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPTrfAllocEntityTypeFrom, strRESPTrfAllocEntityTypeFrom, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPTrfEntityTypeSeqFrom, strRESPTrfEntityTypeSeqFrom, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPBenefIDTo, strRESPBenefIDTo, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPTrfAllocEntityTypeTo, strRESPTrfAllocEntityTypeTo, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPTrfEntityTypeSeqTo, strRESPTrfEntityTypeSeqTo, idDataGroup, false);
      pRESPTransfer->getField (ifds::YTDContr, strYTDContr, idDataGroup, false);
      pRESPTransfer->getField (ifds::TDContr, strTDContr, idDataGroup, false);
      pRESPTransfer->getField (ifds::GrantAmount, strGrantAmount, idDataGroup, false);
      pRESPTransfer->getField (ifds::AdditionalGrant, strAdditionalGrant, idDataGroup, false);
      pRESPTransfer->getField (ifds::CLBAmount, strCLBAmount, idDataGroup, false);
      pRESPTransfer->getField (ifds::PGrantAmount, strPGrantAmount, idDataGroup, false);
      pRESPTransfer->getField (ifds::TDRedContrib, strTDRedContrib, idDataGroup, false);
      pRESPTransfer->getField (ifds::TDRedEarning, strTDRedEarning, idDataGroup, false);
      pRESPTransfer->getField (ifds::RedCESG, strRedCESG, idDataGroup, false);
      pRESPTransfer->getField (ifds::RedCLB, strRedCLB, idDataGroup, false);
      pRESPTransfer->getField (ifds::RedPGrant, strRedPGrant, idDataGroup, false);
      pRESPTransfer->getField (ifds::UCAmt, strUCAmt, idDataGroup, false);
      pRESPTransfer->getField (ifds::ACAmt, strACAmt, idDataGroup, false);
      pRESPTransfer->getField (ifds::Pre98ContribAmt, strPre98ContribAmt, idDataGroup, false);
      pRESPTransfer->getField (ifds::Pre98RedContribAmt, strPre98RedContribAmt, idDataGroup, false);
      pRESPTransfer->getField (ifds::TransferPercent, strTransferPercent, idDataGroup, false);
      pRESPTransfer->getField (ifds::QESIUCAmount, strQESIUCAmount, idDataGroup, false);
      pRESPTransfer->getField (ifds::QESIACAmount, strQESIACAmount, idDataGroup, false);
      pRESPTransfer->getField (ifds::QESIYTDContribution, strQESIYTDContribution, idDataGroup, false);
      pRESPTransfer->getField (ifds::QESIBasicGrant, strQESIBasicGrant, idDataGroup, false);
      pRESPTransfer->getField (ifds::QESIIncreaseAmt, strQESIIncreaseAmt, idDataGroup, false);
      pRESPTransfer->getField (ifds::Pre98QESIContrib, strPre98QESIContrib, idDataGroup, false);
      pRESPTransfer->getField (ifds::Pre2007QESIContrib, strPre2007QESIContrib, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPExtTrDetlUUID, strRESPExtTrDetlUUID, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPExtTrDetlVer, strRESPExtTrDetlVer, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPContrDetlUUID, strRESPContrDetlUUID, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPContrDetlVer, strRESPContrDetlVer, idDataGroup, false);
      pRESPTransfer->getField (ifds::HistNonTrustYear, strHistNonTrustYear, idDataGroup, false);
      pRESPTransfer->getField (ifds::TotTransfINDC, strTotTransfINDC, idDataGroup, false);
      pRESPTransfer->getField (ifds::EligibleTransfer, strEligibleTrfx, idDataGroup, false);
      pRESPTransfer->getField (ifds::CESGPaid, strCESGPaid, idDataGroup, false); //P0185010.FN02.R01.02 - CESG Grant paid
	  pRESPTransfer->getField (ifds::QESIPaid, strQESIPaid, idDataGroup, false);
	  pRESPTransfer->getField (ifds::SAGESGrant, strSAGESGrant, idDataGroup, false);
	  pRESPTransfer->getField (ifds::SAGESUCAmount, strSAGESUCAmount, idDataGroup, false);
	  pRESPTransfer->getField (ifds::SAGESACAmount, strSAGESACAmount, idDataGroup, false);
	  pRESPTransfer->getField (ifds::BCTESGGrant, strBCTESGGrant, idDataGroup, false);
	  pRESPTransfer->getField (ifds::UCRedAmt, strUCRedAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::ACRedAmt, strACRedAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::SAGESRedUCAmt, strSAGESRedUCAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::SAGESRedACAmt, strSAGESRedACAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::QESIRedUCAmt, strQESIRedUCAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::QESIRedACAmt, strQESIRedACAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::QESIRedYTDContrib, strQESIRedYTDContrib, idDataGroup, false);
	  pRESPTransfer->getField (ifds::Pre2007QESIRedContrib, strPre2007QESIRedContrib, idDataGroup, false);
	  pRESPTransfer->getField (ifds::RedAdditionalGrant, strRedAdditionalGrant, idDataGroup, false);
	  pRESPTransfer->getField (ifds::RedSAGES, strRedSAGES, idDataGroup, false);
	  pRESPTransfer->getField (ifds::QESIRedBasic, strQESIRedBasic, idDataGroup, false);
	  pRESPTransfer->getField (ifds::QESIRedIncrease, strQESIRedIncrease, idDataGroup, false);
	  pRESPTransfer->getField (ifds::RedBCTESG, strRedBCTESG, idDataGroup, false);
   }

   // repeating data
   repeatData.setElementValue (ifds::RecordLevel, strRecordLevel);
   repeatData.setElementValue (ifds::RESPBenefIDFrom, strRESPBenefIDFrom);
   repeatData.setElementValue (ifds::RESPTrfAllocEntityTypeFrom, strRESPTrfAllocEntityTypeFrom);
   repeatData.setElementValue (ifds::RESPTrfEntityTypeSeqFrom, strRESPTrfEntityTypeSeqFrom);
   repeatData.setElementValue (ifds::RESPBenefIDTo, strRESPBenefIDTo);
   repeatData.setElementValue (ifds::RESPTrfAllocEntityTypeTo, strRESPTrfAllocEntityTypeTo);
   repeatData.setElementValue (ifds::RESPTrfEntityTypeSeqTo, strRESPTrfEntityTypeSeqTo);
   repeatData.setElementValue (ifds::YTDContr, strYTDContr);
   repeatData.setElementValue (ifds::TDContr, strTDContr);
   repeatData.setElementValue (ifds::GrantAmount, strGrantAmount);
   repeatData.setElementValue (ifds::AdditionalGrant, strAdditionalGrant);
   repeatData.setElementValue (ifds::CLBAmount, strCLBAmount);
   repeatData.setElementValue (ifds::PGrantAmount, strPGrantAmount);
   repeatData.setElementValue (ifds::TDRedContrib, strTDRedContrib);
   repeatData.setElementValue (ifds::TDRedEarning, strTDRedEarning);
   repeatData.setElementValue (ifds::RedCESG, strRedCESG);
   repeatData.setElementValue (ifds::RedCLB, strRedCLB);
   repeatData.setElementValue (ifds::RedPGrant, strRedPGrant);
   repeatData.setElementValue (ifds::UCAmt, strUCAmt);
   repeatData.setElementValue (ifds::ACAmt, strACAmt);
   repeatData.setElementValue (ifds::Pre98ContribAmt, strPre98ContribAmt);
   repeatData.setElementValue (ifds::Pre98RedContribAmt, strPre98RedContribAmt);
   repeatData.setElementValue (ifds::TransferPercent, strTransferPercent);
   repeatData.setElementValue (ifds::QESIUCAmount, strQESIUCAmount);
   repeatData.setElementValue (ifds::QESIACAmount, strQESIACAmount);
   repeatData.setElementValue (ifds::QESIYTDContribution, strQESIYTDContribution);
   repeatData.setElementValue (ifds::QESIBasicGrant, strQESIBasicGrant);
   repeatData.setElementValue (ifds::QESIIncreaseAmt, strQESIIncreaseAmt);
   repeatData.setElementValue (ifds::Pre98QESIContrib, strPre98QESIContrib);
   repeatData.setElementValue (ifds::Pre2007QESIContrib, strPre2007QESIContrib);
   repeatData.setElementValue (ifds::RESPExtTrDetlUUID, strRESPExtTrDetlUUID);
   repeatData.setElementValue (ifds::RESPExtTrDetlVer, strRESPExtTrDetlVer);
   repeatData.setElementValue (ifds::RESPContrDetlUUID, strRESPContrDetlUUID);
   repeatData.setElementValue (ifds::EligibleTransfer, strEligibleTrfx);
   repeatData.setElementValue (ifds::HistNonTrustYear, strHistNonTrustYear);
   repeatData.setElementValue (ifds::TotTransfINDC, strTotTransfINDC); 
   repeatData.setElementValue (ifds::CESGPaid, strCESGPaid);  //P0185010.FN02.R01.02 - CESG Grant paid
   repeatData.setElementValue (ifds::QESIPaid, strQESIPaid);
   repeatData.setElementValue (ifds::SAGESGrant, strSAGESGrant);
   repeatData.setElementValue (ifds::SAGESUCAmount, strSAGESUCAmount);
   repeatData.setElementValue (ifds::SAGESACAmount, strSAGESACAmount);
   repeatData.setElementValue (ifds::BCTESGGrant, strBCTESGGrant);
   repeatData.setElementValue (ifds::UCRedAmt, strUCRedAmt);
   repeatData.setElementValue (ifds::ACRedAmt, strACRedAmt);
   repeatData.setElementValue (ifds::SAGESRedUCAmt, strSAGESRedUCAmt);
   repeatData.setElementValue (ifds::SAGESRedACAmt, strSAGESRedACAmt);
   repeatData.setElementValue (ifds::QESIRedUCAmt, strQESIRedUCAmt);
   repeatData.setElementValue (ifds::QESIRedACAmt, strQESIRedACAmt);
   repeatData.setElementValue (ifds::QESIRedYTDContrib, strQESIRedYTDContrib);
   repeatData.setElementValue (ifds::Pre2007QESIRedContrib, strPre2007QESIRedContrib);
   repeatData.setElementValue (ifds::RedAdditionalGrant, strRedAdditionalGrant);
   repeatData.setElementValue (ifds::RedSAGES, strRedSAGES);
   repeatData.setElementValue (ifds::QESIRedBasic, strQESIRedBasic);
   repeatData.setElementValue (ifds::QESIRedIncrease, strQESIRedIncrease);
   repeatData.setElementValue (ifds::RedBCTESG, strRedBCTESG);

   repeatData.setElementValue (ifds::RunMode, I_("M"));

   queryData.setElementValue( ifds::RepeatCount, I_("1"), false, false);
   queryData.addRepeat (repeatData);

   ReceiveData  (DSTC_REQUEST::RESP_TRANSFER_UPDATE, queryData, ifds::DSTC0407_VW,
      DSTCRequestor (getSecurity (), true, ignoreDataNotFound));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY RESPTransferValidation::validateBeneficiary (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("validateBeneficiary"));

   DString warnCode1, warnCode2, warnCode3, 
      warnCode4, warnCode5, warnCode6,
      warnCode7, warnCode8, warnCode9, 
      warnCode10, warnCode11, warnCode12, 
      warnCode13,
      warnCode14; //P0185010.FN02.R01.02 - new field CESG Grant paid
   DString warnCode15, warnCode16, warnCode17;

   DString param1, param2;
   DString param51, param52;
   DString param61, param62;
   DString param14;//P0185010.FN02.R01.02 - new field CESG Grant paid
   DString param17;

   getField (ifds::WarnCode1, warnCode1, idDataGroup, false);
   getField (ifds::WarnCode2, warnCode2, idDataGroup, false);
   getField (ifds::WarnCode3, warnCode3, idDataGroup, false);
   getField (ifds::WarnCode4, warnCode4, idDataGroup, false);
   getField (ifds::WarnCode5, warnCode5, idDataGroup, false);
   getField (ifds::WarnCode6, warnCode6, idDataGroup, false);
   getField (ifds::WarnCode7, warnCode7, idDataGroup, false);
   getField (ifds::WarnCode8, warnCode8, idDataGroup, false);
   getField (ifds::WarnCode9, warnCode9, idDataGroup, false);
   getField (ifds::WarnCode10, warnCode10, idDataGroup, false);
   getField (ifds::WarnCode11, warnCode11, idDataGroup, false);
   getField (ifds::WarnCode12, warnCode12, idDataGroup, false);
   getField (ifds::WarnCode13, warnCode13, idDataGroup, false);
   getField (ifds::WarnCode14, warnCode14, idDataGroup, false); //P0185010.FN02.R01.02 - new field CESG Grant paid
   getField (ifds::WarnCode15, warnCode15, idDataGroup, false);
   getField (ifds::WarnCode16, warnCode16, idDataGroup, false);
   getField (ifds::WarnCode17, warnCode17, idDataGroup, false);

   getField (ifds::WarnParam51, param51, idDataGroup, false);
   getField (ifds::WarnParam52, param52, idDataGroup, false);
   getField (ifds::WarnParam61, param61, idDataGroup, false);
   getField (ifds::WarnParam62, param62, idDataGroup, false);
   getField (ifds::WarnParam14, param14, idDataGroup, false);//P0185010.FN02.R01.02 - new field CESG Grant paid
   getField (ifds::WarnParam17, param17, idDataGroup, false);

   if (!warnCode1.empty ())
   {
      displayErrorMessage (warnCode1, param1, param2, idDataGroup);
   }

   if (!warnCode2.empty ())
   {
      displayErrorMessage (warnCode2, param1, param2, idDataGroup);
   }

   if (!warnCode3.empty ())
   {
      displayErrorMessage (warnCode3, param1, param2, idDataGroup);
   }

   if (!warnCode4.empty ())
   {
      displayErrorMessage (warnCode4, param1, param2, idDataGroup);
   }

   if (!warnCode5.empty ())
   {
      displayErrorMessage (warnCode5, param51, param52, idDataGroup);
   }

   if (!warnCode6.empty ())
   {
      displayErrorMessage (warnCode6, param61, param62, idDataGroup);
   }

   if (!warnCode7.empty ())
   {
      displayErrorMessage (warnCode7, param1, param2, idDataGroup);
   }

   if (!warnCode8.empty ())
   {
      displayErrorMessage (warnCode8, param1, param2, idDataGroup);
   }

   if (!warnCode9.empty ())
   {
      displayErrorMessage (warnCode9, param1, param2, idDataGroup);
   }

   if (!warnCode10.empty ())
   {
      displayErrorMessage (warnCode10, param1, param2, idDataGroup);
   }

   if (!warnCode11.empty ())
   {
      displayErrorMessage (warnCode11, param1, param2, idDataGroup);
   }

   if (!warnCode12.empty ())
   {
      displayErrorMessage (warnCode12, param1, param2, idDataGroup);
   }
   
   if (!warnCode13.empty ())
   {
      displayErrorMessage (warnCode13, param1, param2, idDataGroup);
   }
   //P0185010.FN02.R01.02 - new field CESG Grant paid
   if (!warnCode14.empty ())
   {
      displayErrorMessage (warnCode14, param14, param2, idDataGroup);
   }
   
   if (!warnCode15.empty ())
   {
      displayErrorMessage (warnCode15, param1, param2, idDataGroup);
   }

   if (!warnCode16.empty ())
   {
      displayErrorMessage (warnCode16, param1, param2, idDataGroup);
   }

   if (!warnCode17.strip().upperCase().empty ())
   {
      displayErrorMessage (warnCode17, param17, param2, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY RESPTransferValidation::displayErrorMessage (const DString &errorNumber,
                                                      const DString &param1,
                                                      const DString &param2,
                                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("displayErrorMessage"));

   if (errorNumber == RESP_PLAN_LIMIT_EXCEEDED)
   {
      DString idiStr1 = NULL_STRING;

      addIDITagValue (idiStr1, BENEF_NAME, m_BenefName);
      addIDITagValue (idiStr1, LIFETIME_LIMIT, param1);
      addIDITagValue (idiStr1, TO_DATE, param2);

      getErrMsg (RESP_PLAN_LIMIT_EXCEEDED,
                 CND::ERR_RESP_PLAN_LIMIT_EXCEEDED,
                 CND::WARN_RESP_PLAN_LIMIT_EXCEEDED,
                 idDataGroup, idiStr1);
   }
   else if (errorNumber == RESP_YEAR_LIMIT_EXCEEDED)
   {
      DString idiStr2 = NULL_STRING;

      addIDITagValue (idiStr2, BENEF_NAME, m_BenefName);
      addIDITagValue (idiStr2, ANNUAL_LIMIT, param1);
      addIDITagValue (idiStr2, TO_DATE, param2);

      getErrMsg (RESP_YEAR_LIMIT_EXCEEDED,
                 CND::ERR_RESP_YEAR_LIMIT_EXCEEDED,
                 CND::WARN_RESP_YEAR_LIMIT_EXCEEDED,
                 idDataGroup, idiStr2);
   }
   else if (errorNumber == BENEFICIARY_IS_OVER_21)
   {
      DString idiStr = NULL_STRING;

      addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

      getErrMsg (BENEFICIARY_IS_OVER_21,
                 CND::ERR_RESP_BENEF_OVER21,
                 CND::WARN_RESP_BENEF_OVER21,
                 idDataGroup, idiStr);
   }
   else if (errorNumber == BENEFICIARY_IS_OVER_31)
   {
      DString idiStr = NULL_STRING;

      addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

      getErrMsg (BENEFICIARY_IS_OVER_31,
                 CND::ERR_RESP_BENEF_OVER31,
                 CND::WARN_RESP_BENEF_OVER31,
                 idDataGroup, idiStr);
   }
   else if (errorNumber == LIFETIME_CONTRIB_LIMITS_NOT_SETUP)
   {
      DString idiStr = NULL_STRING;

      addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

      getErrMsg (LIFETIME_CONTRIB_LIMITS_NOT_SETUP,
                 CND::ERR_LIFETIME_CONTRIB_LIMITS_NOT_SETUP,
                 CND::WARN_LIFETIME_CONTRIB_LIMITS_NOT_SETUP,
                 idDataGroup, idiStr);
   }
   else if (errorNumber == ANNUAL_CONTRIB_LIMITS_NOT_SETUP)
   {
      DString idiStr = NULL_STRING;

      addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

      getErrMsg (ANNUAL_CONTRIB_LIMITS_NOT_SETUP,
                 CND::ERR_ANNUAL_CONTRIB_LIMITS_NOT_SETUP,
                 CND::WARN_ANNUAL_CONTRIB_LIMITS_NOT_SETUP,
                 idDataGroup, idiStr);
   }
   else if (errorNumber == GRANT_AMOUNT_NOT_APPLICABLE)
   {
      //DString idiStr = NULL_STRING;

      //addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

      getErrMsg (GRANT_AMOUNT_NOT_APPLICABLE,
                 CND::ERR_GRANT_AMOUNT_NOT_APPLICABLE,
                 CND::WARN_GRANT_AMOUNT_NOT_APPLICABLE,
                 idDataGroup/*, idiStr*/);
   }
   else if (errorNumber == BENEF_NOT_ELIGIBLE_FOR_CLB)
   {
      DString idiStr = NULL_STRING;
      DString dstrEligDateforCLB;

      getWorkSession ().getOption ( ifds::EligDateforCLB, dstrEligDateforCLB, BF::HOST, true );
      dstrEligDateforCLB.strip();

      addIDITagValue (idiStr, ELIGDATE, dstrEligDateforCLB);
      addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

      getErrMsg (BENEF_NOT_ELIGIBLE_FOR_CLB,
                 CND::ERR_BENEF_NOT_ELIGIBLE_FOR_CLB,
                 CND::WARN_BENEF_NOT_ELIGIBLE_FOR_CLB,
                 idDataGroup, idiStr);
   }
   else if (errorNumber == CLB_AMOUNT_CANNOT_BE_TRANSFERED)
   {
      getErrMsg (CLB_AMOUNT_CANNOT_BE_TRANSFERED, 
                 CND::ERR_CLB_AMOUNT_CANNOT_BE_TRANSFERED, 
                 CND::WARN_CLB_AMOUNT_CANNOT_BE_TRANSFERED, 
                 idDataGroup);
   }
   else if (errorNumber == BALANCE_LESS_THEN_TRANS_AMOUNT)
   {
      DString idiStr = NULL_STRING;

      addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

      getErrMsg (BALANCE_LESS_THEN_TRANS_AMOUNT,
                 CND::ERR_BALANCE_LESS_THEN_TRANS_AMOUNT,
                 CND::WARN_BALANCE_LESS_THEN_TRANS_AMOUNT,
                 idDataGroup, idiStr);
   }
   else if(errorNumber == MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR) //1091
   {
      DString idiStr = NULL_STRING;

      addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

      getErrMsg (MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR,
                 CND::ERR_MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR,
                 CND::WARN_MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR,
                 idDataGroup, idiStr);
   }
   else if(errorNumber == NON_TRUSTEE_UPDATE_HIST_INFO_REQ)//1119
   {
      DString idiStr = NULL_STRING;

      addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

      getErrMsg (NON_TRUSTEE_UPDATE_HIST_INFO_REQ,
                 CND::ERR_NON_TRUSTEE_UPDATE_HIST_INFO_REQ,
                 CND::WARN_NON_TRUSTEE_UPDATE_HIST_INFO_REQ,
                 idDataGroup, idiStr);
   }
   //P0185010.FN02.R01.02 - new field CESG Grant paid
   else if(errorNumber == IFASTERR::CESG_LIMIT_EXCEEDED)//1136
   {
      DString idiStr = NULL_STRING;

      addIDITagValue (idiStr, WARNPARM14, param1);

      getErrMsg (errorNumber,
                 CND::ERR_CESG_LIMIT_EXCEEDED,
                 CND::WARN_CESG_LIMIT_EXCEEDED,
                 idDataGroup, 
                 idiStr);
   }
   else if(errorNumber == IFASTERR::QESI_LIMIT_EXCEEDED)//1287
   {
      DString idiStr = NULL_STRING;

      addIDITagValue (idiStr, I_("LIMIT_VALUE"), param1);

      getErrMsg (errorNumber,
                 CND::ERR_QESI_LIMIT_EXCEEDED,
                 CND::WARN_QESI_LIMIT_EXCEEDED,
                 idDataGroup, 
                 idiStr);
   }
   else if(errorNumber ==  IFASTERR::BALANCE_LESS_THEN_ENTERED_TRANS_AMOUNT) // 1081
   {
      getErrMsg(errorNumber,
                CND::ERR_BALANCE_LESS_THEN_ENTERED_TRANS_AMOUNT,
                CND::WARN_BALANCE_LESS_THEN_ENTERED_TRANS_AMOUNT,
                idDataGroup);
   }
   else if(errorNumber ==  IFASTERR::CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE) // 1701 
   {
      getErrMsg(errorNumber,
                CND::ERR_CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE,
                CND::WARN_CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE,
                idDataGroup);
   }
   else if(errorNumber ==  IFASTERR::ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG) // 1710 
   {
      getErrMsg(errorNumber,
                CND::ERR_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG,
                CND::WARN_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG,
                idDataGroup);
   }
   else if(errorNumber ==  IFASTERR::AMOUNT_EXCEEDS_BCTESG_BALANCE) // 1711 
   {
      getErrMsg(errorNumber,
                CND::ERR_AMOUNT_EXCEEDS_BCTESG_BALANCE,
                CND::WARN_AMOUNT_EXCEEDS_BCTESG_BALANCE,
                idDataGroup);
   }
   else if(errorNumber ==  IFASTERR::TRANSFER_IN_WITH_BCTESG_CANNOT_BE_PROCESSED_BEFORE_DEFF) // 1712 
   {
      getErrMsg(errorNumber,
                CND::ERR_TRANSFER_IN_WITH_BCTESG_CANNOT_BE_PROCESSED_BEFORE_DEFF,
                CND::WARN_TRANSFER_IN_WITH_BCTESG_CANNOT_BE_PROCESSED_BEFORE_DEFF,
                idDataGroup);
   }
   else if(errorNumber ==  IFASTERR::TRADE_WILL_CREATE_NEGATIVE_NOTIONAL_BALANCE_UC_AC_YTD) // 1952 
   {
	   getErrMsg(errorNumber,
				 CND::ERR_TRADE_WILL_CREATE_NEGATIVE_NOTIONAL_BALANCE_UC_AC_YTD,
				 CND::WARN_TRADE_WILL_CREATE_NEGATIVE_NOTIONAL_BALANCE_UC_AC_YTD,
				 idDataGroup);
   }
   else if(errorNumber == IFASTERR::NOTIONALS_MANUAL_OVERRIDE_RECOMMENDED_FOR_MULTIPLE_TRANSFERS) // 1967 
   {
	   getErrMsg(errorNumber,
				 CND::ERR_NOTIONALS_MANUAL_OVERRIDE_RECOMMENDED_FOR_MULTIPLE_TRANSFERS,
				 CND::WARN_NOTIONALS_MANUAL_OVERRIDE_RECOMMENDED_FOR_MULTIPLE_TRANSFERS,
				 idDataGroup);
   }
   else if(errorNumber == IFASTERR::NOTIONALS_MANUAL_OVERRIDE_MAY_BE_REQUIRED) // 1968 
   {
	   getErrMsg(errorNumber,
				 CND::ERR_NOTIONALS_MANUAL_OVERRIDE_MAY_BE_REQUIRED,
				 CND::WARN_NOTIONALS_MANUAL_OVERRIDE_MAY_BE_REQUIRED,
				 idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************
void RESPTransferValidation::buildKey (const DString &_dstrRESPBenefId,
                                       const DString &_dstrTradeDate, 
                                       const DString &_dstrAmount, 
                                       const DString &_dstrNEQ1,
                                       const DString &_dstrNEQ2,
                                       //const DString &_dstrEligibleTrfx,
                                       //const DString &_dstrHistNonTrustYear,
                                       //const DString &_dstrTotTransfINDC,
                                       const RESPTransfer *pRESPTransfer,
                                       const BFDataGroupId &idDataGroup,
                                       DString &strKey)
{
   DString dstrRESPBenefId (_dstrRESPBenefId),
      dstrTradeDate (_dstrTradeDate), 
      dstrAmount (_dstrAmount), 
      dstrNEQ1 (_dstrNEQ1),
      dstrNEQ2 (_dstrNEQ2);
      //dstrNEQ2 (_dstrNEQ2),
      //dstrEligibleTrfx (_dstrEligibleTrfx),
      //dstrHistNonTrustYear (_dstrHistNonTrustYear),
      //dstrTotTransfINDC (_dstrTotTransfINDC);

   dstrRESPBenefId.strip ();
   dstrTradeDate.strip();
   dstrAmount.strip();
   dstrNEQ1.strip();
   dstrNEQ2.strip();

   DString strRecordLevel;
   DString strYTDContr;
   DString strTDContr;
   DString strGrantAmount;
   DString strAdditionalGrant;
   DString strCLBAmount;
   DString strPGrantAmount;
   DString strTDRedContrib;
   DString strTDRedEarning;
   DString strRedCESG;
   DString strRedCLB;
   DString strRedPGrant;
   DString strUCAmt;
   DString strACAmt;
   DString strPre98ContribAmt;
   DString strPre98RedContribAmt;
   DString strTransferPercent;
   DString strQESIUCAmount;
   DString strQESIACAmount;
   DString strQESIYTDContribution;
   DString strQESIBasicGrant;
   DString strQESIIncreaseAmt;
   DString strPre98QESIContrib;
   DString strPre2007QESIContrib;
   DString strRESPExtTrDetlUUID;
   DString strRESPExtTrDetlVer;
   DString strRESPContrDetlUUID;
   DString strRESPContrDetlVer;
   DString strHistNonTrustYear; 
   DString strTotTransfINDC;
   DString strEligibleTransfer;
   DString strCESGPaid;
   DString strQESIPaid;
   DString strSAGESGrant;
   DString strSAGESUCAmount;
   DString strSAGESACAmount;
   DString strBCTESGGrant;
   DString strUCRedAmt;
   DString strACRedAmt;
   DString strSAGESRedUCAmt;
   DString strSAGESRedACAmt;
   DString strQESIRedUCAmt;
   DString strQESIRedACAmt;
   DString strQESIRedYTDContrib;
   DString strPre2007QESIRedContrib;
   DString strRedAdditionalGrant;
   DString strRedSAGES;
   DString strQESIRedBasic;
   DString strQESIRedIncrease;
   DString strRedBCTESG;

   // get grant data:

   if (pRESPTransfer)
   {
      pRESPTransfer->getField (ifds::RecordLevel, strRecordLevel, idDataGroup, false);
      pRESPTransfer->getField (ifds::YTDContr, strYTDContr, idDataGroup, false);
      pRESPTransfer->getField (ifds::TDContr, strTDContr, idDataGroup, false);
      pRESPTransfer->getField (ifds::GrantAmount, strGrantAmount, idDataGroup, false);
      pRESPTransfer->getField (ifds::AdditionalGrant, strAdditionalGrant, idDataGroup, false);
      pRESPTransfer->getField (ifds::CLBAmount, strCLBAmount, idDataGroup, false);
      pRESPTransfer->getField (ifds::PGrantAmount, strPGrantAmount, idDataGroup, false);
      pRESPTransfer->getField (ifds::TDRedContrib, strTDRedContrib, idDataGroup, false);
      pRESPTransfer->getField (ifds::TDRedEarning, strTDRedEarning, idDataGroup, false);
      pRESPTransfer->getField (ifds::RedCESG, strRedCESG, idDataGroup, false);
      pRESPTransfer->getField (ifds::RedCLB, strRedCLB, idDataGroup, false);
      pRESPTransfer->getField (ifds::RedPGrant, strRedPGrant, idDataGroup, false);
      pRESPTransfer->getField (ifds::UCAmt, strUCAmt, idDataGroup, false);
      pRESPTransfer->getField (ifds::ACAmt, strACAmt, idDataGroup, false);
      pRESPTransfer->getField (ifds::Pre98ContribAmt, strPre98ContribAmt, idDataGroup, false);
      pRESPTransfer->getField (ifds::Pre98RedContribAmt, strPre98RedContribAmt, idDataGroup, false);
      pRESPTransfer->getField (ifds::TransferPercent, strTransferPercent, idDataGroup, false);
      pRESPTransfer->getField (ifds::QESIUCAmount, strQESIUCAmount, idDataGroup, false);
      pRESPTransfer->getField (ifds::QESIACAmount, strQESIACAmount, idDataGroup, false);
      pRESPTransfer->getField (ifds::QESIYTDContribution, strQESIYTDContribution, idDataGroup, false);
      pRESPTransfer->getField (ifds::QESIBasicGrant, strQESIBasicGrant, idDataGroup, false);
      pRESPTransfer->getField (ifds::QESIIncreaseAmt, strQESIIncreaseAmt, idDataGroup, false);
      pRESPTransfer->getField (ifds::Pre98QESIContrib, strPre98QESIContrib, idDataGroup, false);
      pRESPTransfer->getField (ifds::Pre2007QESIContrib, strPre2007QESIContrib, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPExtTrDetlUUID, strRESPExtTrDetlUUID, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPExtTrDetlVer, strRESPExtTrDetlVer, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPContrDetlUUID, strRESPContrDetlUUID, idDataGroup, false);
      pRESPTransfer->getField (ifds::RESPContrDetlVer, strRESPContrDetlVer, idDataGroup, false);
      pRESPTransfer->getField (ifds::HistNonTrustYear, strHistNonTrustYear, idDataGroup, false);
      pRESPTransfer->getField (ifds::TotTransfINDC, strTotTransfINDC, idDataGroup, false);
      pRESPTransfer->getField (ifds::EligibleTransfer, strEligibleTransfer, idDataGroup, false);
      pRESPTransfer->getField (ifds::CESGPaid, strCESGPaid, idDataGroup, false); //P0185010.FN02.R01.02 - CESG Grant paid
	  pRESPTransfer->getField (ifds::QESIPaid, strQESIPaid, idDataGroup, false);
	  pRESPTransfer->getField (ifds::SAGESGrant, strSAGESGrant, idDataGroup, false);
	  pRESPTransfer->getField (ifds::SAGESUCAmount, strSAGESUCAmount, idDataGroup, false);
	  pRESPTransfer->getField (ifds::SAGESACAmount, strSAGESACAmount, idDataGroup, false);
	  pRESPTransfer->getField (ifds::BCTESGGrant, strBCTESGGrant, idDataGroup, false);
	  pRESPTransfer->getField (ifds::UCRedAmt, strUCRedAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::ACRedAmt, strACRedAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::SAGESRedUCAmt, strSAGESRedUCAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::SAGESRedACAmt, strSAGESRedACAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::QESIRedUCAmt, strQESIRedUCAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::QESIRedACAmt, strQESIRedACAmt, idDataGroup, false);
	  pRESPTransfer->getField (ifds::QESIRedYTDContrib, strQESIRedYTDContrib, idDataGroup, false);
	  pRESPTransfer->getField (ifds::Pre2007QESIRedContrib, strPre2007QESIRedContrib, idDataGroup, false);
	  pRESPTransfer->getField (ifds::RedAdditionalGrant, strRedAdditionalGrant, idDataGroup, false);
	  pRESPTransfer->getField (ifds::RedSAGES, strRedSAGES, idDataGroup, false);
	  pRESPTransfer->getField (ifds::QESIRedBasic, strQESIRedBasic, idDataGroup, false);
	  pRESPTransfer->getField (ifds::QESIRedIncrease, strQESIRedIncrease, idDataGroup, false);
	  pRESPTransfer->getField (ifds::RedBCTESG, strRedBCTESG, idDataGroup, false);
   }

   strKey = DString (I_("RESPTransferValidation_")) + 
      I_("BenefId=") + dstrRESPBenefId + I_(";") +
      I_("TradeDate=") + dstrTradeDate + I_(";") +
      I_("Amount=") + dstrAmount + I_(";") +
      I_("RecordLevel=") + strRecordLevel + I_(";") +
      I_("YTDContr=") + strYTDContr + I_(";") +
      I_("TDContr=") + strTDContr + I_(";") +
      I_("GrantAmount=") +  strGrantAmount+ I_(";") +
      I_("AdditionalGrant=") + strAdditionalGrant + I_(";") +
      I_("CLBAmount=") + strCLBAmount + I_(";") +
      I_("PGrantAmount=") + strPGrantAmount + I_(";") +
      I_("TDRedContrib=") + strTDRedContrib + I_(";") +
      I_("TDRedEarning=") + strTDRedEarning + I_(";") +
      I_("RedCESG=") + strRedCESG + I_(";") +
      I_("RedCLB=") + strRedCLB + I_(";") +
      I_("RedPGrant=") + strRedPGrant + I_(";") +
      I_("UCAmt=") + strUCAmt + I_(";") +
      I_("ACAmt=") + strACAmt + I_(";") +
      I_("Pre98ContribAmt=") + strPre98ContribAmt + I_(";") +
      I_("Pre98RedContribAmt=") + strPre98RedContribAmt + I_(";") +
      I_("TransferPercent=") + strTransferPercent + I_(";") +
      I_("QESIUCAmount=") + strQESIUCAmount + I_(";") +
      I_("QESIACAmount=") + strQESIACAmount + I_(";") +
      I_("QESIYTDContribution=") + strQESIYTDContribution + I_(";") +
      I_("QESIBasicGrant=") + strQESIBasicGrant + I_(";") +
      I_("QESIIncreaseAmt=") + strQESIIncreaseAmt + I_(";") +
      I_("Pre98QESIContrib=") + strPre98QESIContrib + I_(";") +
      I_("Pre2007QESIContrib=") + strPre2007QESIContrib + I_(";") +
      I_("strRESPExtTrDetlUUID=") + strRESPExtTrDetlUUID + I_(";") +
      I_("RESPExtTrDetlVer=") + strRESPExtTrDetlVer + I_(";") +
      I_("RESPContrDetlUUID=") + strRESPContrDetlUUID + I_(";") +
      I_("RESPContrDetlVer=") + strRESPContrDetlVer + I_(";") +
      I_("HistNonTrustYear=") + strHistNonTrustYear +I_(";") + 
      I_("EligibleTransfer=") + strEligibleTransfer + I_(";") +
      I_("NEQ1=") + dstrNEQ1 + I_(";") +
      I_("NEQ2=") + dstrNEQ2 + I_(";") +
      I_("TotTransfINDC=") + strTotTransfINDC + I_(";") + 
      I_("CESGPaid=") + strCESGPaid + I_(";") +
	  I_("QESIPaid=") + strQESIPaid + I_(";") +
	  I_("SAGESGrant=") + strSAGESGrant + I_(";") +
	  I_("SAGESUCAmount=") + strSAGESUCAmount + I_(";") +
	  I_("SAGESACAmount=") + strSAGESACAmount + I_(";") +
      I_("BCTESGGrant=") + strBCTESGGrant + I_(";") +
	  I_("UCRedAmt=") + strUCRedAmt + I_(";") +
	  I_("ACRedAmt=") + strACRedAmt + I_(";") +
	  I_("SAGESRedUCAmt=") + strSAGESRedUCAmt + I_(";") +
	  I_("SAGESRedACAmt=") + strSAGESRedACAmt + I_(";") +
	  I_("QESIRedUCAmt=") + strQESIRedUCAmt + I_(";") +
	  I_("QESIRedACAmt=") + strQESIRedACAmt + I_(";") +
	  I_("QESIRedYTDContrib=") + strQESIRedYTDContrib + I_(";") +
	  I_("Pre2007QESIRedContrib=") + strPre2007QESIRedContrib + I_(";") +
	  I_("RedAdditionalGrant=") + strRedAdditionalGrant + I_(";") +
	  I_("RedSAGES=") + strRedSAGES + I_(";") +
	  I_("QESIRedBasic=") + strQESIRedBasic + I_(";") +
	  I_("QESIRedIncrease=") + strQESIRedIncrease + I_(";") +
	  I_("RedBCTESG=") + strRedBCTESG + I_(";");
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPTransferValidation.cpp-arc  $
// 
//    Rev 1.4   Oct 06 2011 10:32:28   panatcha
// P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
// 
//    Rev 1.3   Jul 14 2011 08:09:04   panatcha
// DRAFT - IN2584478, IN5285248, IN2591262
// 
//    Rev 1.2   Jun 28 2011 10:34:10   panatcha
// P0184541_FN01_InvescoQESItrans
// 
