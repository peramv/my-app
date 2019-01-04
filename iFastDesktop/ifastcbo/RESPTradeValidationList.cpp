//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : RESPTradeValidationList.cpp
// ^AUTHOR : 
// ^DATE   : Aprl, 2010
//
// ^CLASS    : RESPTradeValidationList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0405_vw.hpp>
#include <ifastdataimpl\dse_dstc0405_req.hpp>
#include <ifastdataimpl\dse_dstc0405_vwrepeat_record.hpp>

#include "RESPTradeValidation.hpp"
#include "RESPTradeValidationList.hpp"
#include "mfaccount.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESP_TRADE_VALIDATION_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "RESPTradeValidationList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

namespace CND
{
}

//******************************************************************************
RESPTradeValidationList::RESPTradeValidationList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList( );
}

//******************************************************************************
RESPTradeValidationList::~RESPTradeValidationList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************
SEVERITY RESPTradeValidationList::init(const DString& accountNum,
                                       const DString& transType,
                                       const DString& fundCode,
                                       const DString& classCode,
                                       const DString& depType,
                                       const DString& redCode,
                                       const DString& tradeDate,
                                       const DString& settleDate,
                                       const DString& amountType,
                                       const DString& amount,
                                       const DString& grossOrNet,
                                       const DString& respBenefId,
                                       const DString& fee,
                                       const DString& flatPrcnt,
                                       const DString& ocRdmYear,
                                       const DString& respContrDetlTaxYear,
                                       const DString& assistedContrAmt,
                                       const BFDataGroupId& idDataGroup,
                                       const DString& dstrTrack,
                                       const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;
   BFData requestData (ifds::DSTC0405_REQ);

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName);
   requestData.setElementValue (ifds::AccountNum, accountNum);
   requestData.setElementValue (ifds::TransType, transType);
   requestData.setElementValue (ifds::Fund, fundCode);
   requestData.setElementValue (ifds::Class, classCode);
   requestData.setElementValue (ifds::DepositType, depType);
   requestData.setElementValue (ifds::RedCode, redCode);
   requestData.setElementValue (ifds::TradeDate, tradeDate);
   requestData.setElementValue (ifds::SettleDate, settleDate);
   requestData.setElementValue (ifds::AmountType, amountType);
   requestData.setElementValue (ifds::Amount, amount);
   requestData.setElementValue (ifds::GrossOrNet, grossOrNet);
   requestData.setElementValue (ifds::RESPBenefId, respBenefId);
   requestData.setElementValue (ifds::Fee, fee);
   requestData.setElementValue (ifds::FlatPrcnt, flatPrcnt);
   requestData.setElementValue (ifds::OCRdmYear, ocRdmYear);
   requestData.setElementValue (ifds::RESPContrDetlTaxYear, respContrDetlTaxYear);
   requestData.setElementValue (ifds::AssistedContrAmt, assistedContrAmt);

   ReceiveData( DSTC_REQUEST::RESP_TRADE_VALIDATION_INQUIRY,
                requestData, 
                ifds::DSTC0405_VW, 
                DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTradeValidationList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new RESPTradeValidation( *this );
   ((RESPTradeValidation*) pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPTradeValidationList.cpp-arc  $
// 
//    Rev 1.2   May 27 2010 06:07:44   kitticha
// PETP0165541 FN02 QESI Phase2.
// 
//    Rev 1.1   Apr 22 2010 03:58:50   dchatcha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.0   Apr 21 2010 23:26:18   dchatcha
// Initial revision.
// 
*/
