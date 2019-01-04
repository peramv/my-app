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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : RedemptionValidation.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 04/25/2003
//
// ^CLASS    : RedemptionValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "redemptionvalidation.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0143_req.hpp>
#include <ifastdataimpl\dse_dstc0143_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REDEMPTION_VALIDATION;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "RedemptionValidation" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const EFFECTIVEDATE = I_( "EffectiveDate" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId LSIFCode;
   extern CLASS_IMPORT const BFDecimalFieldId LSIFUnitsAvail;
}

namespace  CND
{
   
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,														State Flags, Group Flags 
	{ ifds::CurrLIPSetup,		BFCBO::NONE, 0 },
	{ ifds::MaxPensionEarning,	BFCBO::NONE, 0 },
	{ ifds::AmountOver,         BFCBO::NONE, 0 },
	{ ifds::UnitHeld,			BFCBO::NONE, 0 },
	{ ifds::FeeDfnExist,		BFCBO::NONE, 0 },
	{ ifds::MaxRedFee,			BFCBO::NONE, 0 },
	{ ifds::LLPValMsg,			BFCBO::NONE, 0 },
	{ ifds::TransExist,			BFCBO::NONE, 0 },
	{ ifds::MinWithAgeErr1,		BFCBO::NONE, 0 }, 
	{ ifds::MinWithAgeErr2,		BFCBO::NONE, 0 },
	{ ifds::PenInfoErr,			BFCBO::NONE, 0 },
	{ ifds::TaxTypeRulErr,		BFCBO::NONE, 0 }, 
	{ ifds::AmtSysCalc,			BFCBO::NONE, 0 },
	{ ifds::RRIFDetlErr,		BFCBO::NONE, 0 }, 
	{ ifds::LowRemainBal,		BFCBO::NONE, 0 },
	{ ifds::RemAmtPayFirst,		BFCBO::NONE, 0 },
	{ ifds::AmntOverMax,		BFCBO::NONE, 0 },
	{ ifds::EurCurrMstr,		BFCBO::NONE, 0 },
	{ ifds::LSIFUnitsAvail,     BFCBO::NONE, 0 },
	{ ifds::AmtOverMin,		    BFCBO::NONE, 0 },

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,    State Flags,         Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
RedemptionValidation::RedemptionValidation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS,
                       (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//****************************************************************************
RedemptionValidation::~RedemptionValidation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************
SEVERITY RedemptionValidation::init( 
      const DString &transType,
      const DString &accountNum,
      const DString &effectiveDate,    
      const DString &fundCode,
      const DString &classCode,        
      const DString &amount,
      const DString &amountType,       
      const DString &redCode,
      const DString &settleDate,       
      const DString &settleCurrency,
      const DString &lsifCode,
	  const DString &grossNet,
	   const DString &taxable /*= I_("N")*/,
	   const DString &dstrTrack /*= I_("N")*/,
	   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   
   BFData queryData(ifds::DSTC0143_REQ);
   BFData *receivedData = new BFData(ifds::DSTC0143_VW);
	DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::TransType,      transType );
   queryData.setElementValue( ifds::AccountNum,     accountNum );
   queryData.setElementValue( ifds::EffectiveDate,  effectiveDate, false, false );
	queryData.setElementValue( ifds::FundCode,       fundCode );
	queryData.setElementValue( ifds::ClassCode,      classCode );
	queryData.setElementValue( ifds::Amount,         amount );
	queryData.setElementValue( ifds::AmountType,     amountType );
	queryData.setElementValue( ifds::RedCode,        redCode );
	queryData.setElementValue( ifds::SettleDate,     settleDate );
	queryData.setElementValue( ifds::SettleCurrency, settleCurrency );
   queryData.setElementValue( ifds::LSIFCode,       lsifCode );
   queryData.setElementValue( ifds::GrossOrNet,       grossNet );
   queryData.setElementValue( ifds::Taxable,        taxable );
   queryData.setElementValue( ifds::Track,          dstrTrack );
   queryData.setElementValue( ifds::Activity,       dstrPageName );
   ReceiveData (DSTC_REQUEST::REDEMPTION_VALIDATION, queryData, 
      *receivedData, DSTCRequestor (getSecurity()));
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void RedemptionValidation::buildKey (
      const DString &_transType,
      const DString &_accountNum,
      const DString &_effectiveDate,    
      const DString &_fundCode,
      const DString &_classCode,        
      const DString &_amount,
      const DString &_amountType,       
      const DString &_redCode,
      const DString &_settleDate,       
      const DString &_settleCurrency,
      const DString &_lsifCode,
  	  const DString &_grossNet,
      DString &strKey)
{
   DString transType (_transType),
      accountNum (_accountNum),
      effectiveDate (_effectiveDate), 
      fundCode (_fundCode),
      classCode (_classCode),
      amount (_amount),
      amountType (_amountType),       
      redCode (_redCode),
      settleDate (_settleDate),       
      settleCurrency (_settleCurrency),
      lsifCode (_lsifCode),
	  grossNet (_grossNet);

   transType.strip().upperCase();
   accountNum.strip();
   effectiveDate.strip();
   fundCode.strip().upperCase();
   classCode.strip().upperCase();
   amount.strip();
   amountType.strip().upperCase();
   redCode.strip().upperCase();
   settleDate.strip();
   settleCurrency.strip();
   lsifCode.strip().upperCase();
   grossNet.strip().upperCase();

   strKey = DString (I_("RedemptionValidation_")) + 
      I_("TransType=") + transType + I_(";") +
      I_("AccountNum=") + accountNum + I_(";") +
      I_("EffectiveDate=") + effectiveDate + I_(";") +
      I_("FundCode=") + fundCode + I_(";") +
      I_("ClassCode=") + classCode + I_(";") +
      I_("Amount=") + amount + I_(";") +
      I_("AmountType=") + amountType + I_(";") +
      I_("RedemptionCode=") + redCode + I_(";") +
      I_("SettleDate=") + settleDate + I_(";") +
      I_("SettleCurrency=") + settleCurrency + I_(";") +
      I_("LSIFCode=") + lsifCode + I_(";") +
	  I_("GrossNet=") + grossNet + I_(";");
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RedemptionValidation.cpp-arc  $
// 
//    Rev 1.6   Apr 17 2009 10:48:06   jankovii
// PET 157825 FN04 Manual RRIF Redemption.
// 
//    Rev 1.5   Nov 14 2004 14:51:42   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   May 17 2004 19:04:20   popescu
// PET 985, FN01, LSIF Trade entry field name changes
// 
//    Rev 1.3   May 13 2004 21:06:40   popescu
// PET 985, FN 01, LSIF Trade entry
// 
//    Rev 1.2   Sep 19 2003 11:16:58   VADEANUM
// PTS 10021736 - Withholding Tax Default Rates.
// 
//    Rev 1.1   Aug 15 2003 14:28:50   FENGYONG
// add field taxable
// 
//    Rev 1.0   May 02 2003 18:20:02   ZHANGCEL
// Initial revision.
 
*/


