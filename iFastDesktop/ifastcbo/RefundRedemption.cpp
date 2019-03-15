//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : RefundRedemption.cpp
// ^AUTHOR :  
// ^DATE   : 
//
// ^CLASS    : RefundRedemption - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "RefundRedemption.hpp"
#include "transfeelist.hpp"
#include "tradeacctalloclist.hpp"
#include <ifastdataimpl\dse_dstc0127_req.hpp>
#include <ifastdataimpl\dse_dstc0127_vw.hpp>
#include <ifastdataimpl\dse_dstc0344_vw.hpp>
#include "TradeFundAllocList.hpp"

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
	extern CLASS_IMPORT I_CHAR * const REFUND_REDEMPTION;
	extern CLASS_IMPORT I_CHAR * const REFUND_REDEMPTION_INDC;
}

namespace
{
	//Trace literals
	const I_CHAR * const CLASSNAME = I_ ("RefundRedemption");
   extern CLASS_IMPORT const int AUTO_BATCHING;
}

namespace DATE_VALIDATION
{
   extern CLASS_IMPORT const I_CHAR * const INPUT_SETTLE_DATE; 
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DealDateTime;
   extern CLASS_IMPORT const BFTextFieldId AutoBatch;
   extern CLASS_IMPORT const BFTextFieldId TransModPerm;
   extern CLASS_IMPORT const BFTextFieldId AcctableTradeDate;
   extern CLASS_IMPORT const BFTextFieldId FromHistoryTrade;
   extern CLASS_IMPORT const BFTextFieldId Indc;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundLFC;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANS_NUM;
}
//******************************************************************************
RefundRedemption::RefundRedemption (BFAbstractCBO &parent) : Redemption (parent), Trade (parent)
{
	TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}


//******************************************************************************
RefundRedemption::~RefundRedemption ()
{
	TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY RefundRedemption::doInit (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

	setFieldNoValidate (ifds::TradesTransType, TRADETYPE::REFUND_REDEMPTION, idDataGroup, false);
   
//   setFieldReadOnly (ifds::EffectiveDate, BF::HOST, true);
   setFieldReadOnly (ifds::AmtType, BF::HOST, true);
   setFieldReadOnly (ifds::FromFund, BF::HOST, true);
   setFieldReadOnly (ifds::FromClass, BF::HOST, true);
   setFieldReadOnly (ifds::FromFundNumber, BF::HOST, true);
   setFieldReadOnly (ifds::FundISIN, BF::HOST, true);

   setFieldReadOnly (ifds::FundWKN, BF::HOST, true);
   setFieldReadOnly (ifds::FundLFC, BF::HOST, true);
   setFieldReadOnly (ifds::FundISIN, BF::HOST, true);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY RefundRedemption::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME,  I_("preInitWithDefaultValues"));
	   
	Redemption::preInitWithDefaultValues (idDataGroup);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void RefundRedemption::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   Redemption::doInitWithDefaultValues (idDataGroup);
}

//***************************************************************************************************
SEVERITY RefundRedemption::doApplyRelatedChanges ( const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if (Redemption::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
	{
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

SEVERITY RefundRedemption::validateMinFromFundAmount ( const DString &accountNum,
                                                 const DString &fundCode,
                                                 const DString &classCode,
                                                 const DString &amtType,
                                                 const DString &amount,
                                                 const DString &broker,
                                                 const DString &branch,
                                                 const DString &slsrep,
                                                 const DString &depositType, //in1419539
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateMinFromFundAmount"));
   DString currency,
      initPurch,tradeDate;

   getField (ifds::SettleCurrency, currency, idDataGroup);
   getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);

   bool bOverrideFundLevelCheck = false;
//first check ams
   amsMinAmtCheck ( TRADETYPE::REDEMPTION,
                    accountNum,
                    fundCode, 
                    classCode,
                    amtType, 
                    amount, 
                    currency, 
                    broker,
                    branch,
                    slsrep,
                    depositType, //in1419539
                    bOverrideFundLevelCheck,
					tradeDate,
                    idDataGroup);

   if (!bOverrideFundLevelCheck && GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
      
      DString oldTransNum;
      DString transNum;
      getField (ifds::AdjTransNum, oldTransNum, BF::HOST, false);
	  getField (ifds::TransNum, transNum, BF::HOST, false);

      fundClassTradeMinimumAmtCheck ( TRADETYPE::REDEMPTION,
                                      accountNum,
                                      fundCode,
                                      classCode,
                                      amtType,
                                      amount,
                                      currency,
                                      initPurch,
                                      broker,
                                      branch,
                                      slsrep,
                                      depositType, //in1419539
									  tradeDate,
                                      idDataGroup,
                                      false,
                                      TRADETYPE::REFUND_REDEMPTION_INDC,
                                      oldTransNum,
									  transNum);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

/* $Log::   
*/
