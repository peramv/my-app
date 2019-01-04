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
// ^FILE   : CotLegalAge.cpp
// ^AUTHOR :  
// ^DATE   : 
//
// ^CLASS    : CotLegalAge 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "CotLegalAge.hpp"
#include <ifastdataimpl\dse_dstc0367_req.hpp>
#include <ifastdataimpl\dse_dstc0367_vw.hpp>

namespace
{
	const I_CHAR * const CLASSNAME		= I_ ("CotLegalAge");
}

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest COT_LEGAL_AGE;
}


//******************************************************************************
CotLegalAge::CotLegalAge( BFAbstractCBO &parent ) : MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}
//******************************************************************************
CotLegalAge::~CotLegalAge ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY CotLegalAge::init (const DString& dstrContractType, const DString& dstrTaxType, 
							   const DString& dstrProvReg, const DString& dstrEffectiveDate,
							   const DString& dstrTrack, const DString& dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
	BFData	queryData(ifds::DSTC0367_REQ);
	DString mgmtCoIdOut;

	queryData.setElementValue (ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	queryData.setElementValue (ifds::Track, dstrTrack );
    queryData.setElementValue (ifds::Activity, dstrPageName );
	queryData.setElementValue (ifds::ContractType, dstrContractType);
	queryData.setElementValue (ifds::TaxType, dstrTaxType); 
	queryData.setElementValue (ifds::ProvReg, dstrProvReg); 
	queryData.setElementValue (ifds::EffectiveDate, dstrEffectiveDate, false, false);
	
	ReceiveData (DSTC_REQUEST::COT_LEGAL_AGE, queryData, ifds::DSTC0367_VW, DSTCRequestor(getSecurity(), true));

	return GETCURRENTHIGHESTSEVERITY ();
}
