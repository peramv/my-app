//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2006 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : PaymentInstrValidation.cpp
//    ^AUTHOR : Celia Zhang
//    ^DATE   : October, 2006
//    Copyright 2004 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : PaymentInstrValidation
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"

#include "PaymentInstrValidation.hpp"

#include <ifastdataimpl\dse_dstc0376_req.hpp>
#include <ifastdataimpl\dse_dstc0376_vw.hpp>

// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("PaymentInstrValidation");
}


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PAYMENT_INSTR_VALIDATION;
}

//******************************************************************************
PaymentInstrValidation::PaymentInstrValidation(BFAbstractCBO &parent) 
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);   
}

//******************************************************************************
PaymentInstrValidation::~PaymentInstrValidation()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY PaymentInstrValidation::init( const DString &dstrBrokerCode,
							    const DString &dstrBranchCode,
								 const DString &dstrSalesRepCode,
								 const DString &dstrPaymentFor,
								 const DString &dstrEffectiveDate,
								 const DString &dstrStopDate )
								
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   
   _pRequestData = new BFData(ifds::DSTC0376_REQ);

   DString dstrMgmtCoIdOut;

   _pRequestData->setElementValue(ifds::BrokerCode,      dstrBrokerCode );      
   _pRequestData->setElementValue(ifds::BranchCode,		dstrBranchCode );      
   _pRequestData->setElementValue(ifds::SalesRepCode,    dstrSalesRepCode );      
   _pRequestData->setElementValue(ifds::PaymentFor,		dstrPaymentFor );      
   _pRequestData->setElementValue(ifds::EffectiveDate,   dstrEffectiveDate ); 
	_pRequestData->setElementValue(ifds::StopDate,			dstrStopDate ); 
   _pRequestData->setElementValue(ifds::CompanyId,       getMgmtCoId( dstrMgmtCoIdOut ) );
   _pRequestData->setElementValue(ifds::Track,           I_( "N" ) );   

   ReceiveData( DSTC_REQUEST::PAYMENT_INSTR_VALIDATION, 
	            *_pRequestData, 
                ifds::DSTC0376_VW, 
				DSTCRequestor( getSecurity(), 
				true, true, true ) );   

   return GETCURRENTHIGHESTSEVERITY();            
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
// 


