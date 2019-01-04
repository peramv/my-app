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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : FinInstRegDetlList.cpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 14 June 2013
//
// ^CLASS    : FinInstRegDetlList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FinInstRegDetlList.hpp"
#include "FinInstRegDetl.hpp"
#include <ifastdataimpl\dse_dstc0450_vw.hpp>
#include <ifastdataimpl\dse_dstc0450_req.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest FIN_INST_REG_DETL_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME = I_( "FinInstRegDetlList" );
}

namespace CND
{
	extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
}


//******************************************************************************
FinInstRegDetlList::FinInstRegDetlList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	setObjectAsList( );
}


//******************************************************************************
FinInstRegDetlList::~FinInstRegDetlList( void )
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY FinInstRegDetlList::init(const DString &dstrComplyRule,
                                  const BFDataGroupId& idDataGroup,
                                  const DString &dstrAcctNum,
                                  const DString &dstrAcctDesignation,
                                  const DString &dstrBrokerCode,
                                  const DString &dstrInterCode,
                                  const DString &dstrTrack, 
                                  const DString &dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	DString mgmtCoIdOut;

	BFData requestData(ifds::DSTC0450_REQ); 

	std::vector<DString> vComplyRule;
	DSTCommonFunctions::tokenizeString(dstrComplyRule, vComplyRule);
	
	unsigned int complyIndex;
	for(complyIndex = 0; complyIndex < vComplyRule.size(); complyIndex++)
	{
		requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut ));
		requestData.setElementValue(ifds::Track, dstrTrack );
		requestData.setElementValue(ifds::Activity, dstrPageName );
		requestData.setElementValue(ifds::NextKey, NULL_STRING );
		requestData.setElementValue(ifds::Regulatory, vComplyRule[complyIndex].stripAll());

		// For new account, send account# 0 - backend will handle it.
		//requestData.setElementValue( ifds::AccountNum, getParent()->isNew()? I_("0"):dstrAcctNum);
		requestData.setElementValue(ifds::AccountNum, I_("0"));
		requestData.setElementValue(ifds::AcctDesignation, dstrAcctDesignation);
		requestData.setElementValue(ifds::BrokerCode, dstrBrokerCode);
		requestData.setElementValue(ifds::InterCode, dstrInterCode);

		ReceiveData(DSTC_REQUEST::FIN_INST_REG_DETL_INQUIRY, requestData, ifds::DSTC0450_VW, DSTCRequestor(getSecurity(), true));
	}
	return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
void FinInstRegDetlList::getFFIStartStopDate(const BFDataGroupId &idDataGroup, 
                                             const DString &dstrKeyFinInstRegDetlUUID,
                                             DString &startDate, 
                                             DString &stopDate)
{
   if (dstrKeyFinInstRegDetlUUID != NULL_STRING)
   {
      BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
      iter.begin();

      while (!iter.end())
      {
         DString dstrEffectiveDate, dstrStopDate, dstrFinInstRegDetlUUID;	
         iter.getObject()->getField(ifds::FinInstRegDetlUUID, dstrFinInstRegDetlUUID, idDataGroup);

         if (dstrKeyFinInstRegDetlUUID == dstrFinInstRegDetlUUID)
         {
            iter.getObject()->getField(ifds::EffectiveDate, startDate, idDataGroup, true);
            iter.getObject()->getField(ifds::StopDate, stopDate, idDataGroup, true);
         }

         ++iter;
      }
   }
}
