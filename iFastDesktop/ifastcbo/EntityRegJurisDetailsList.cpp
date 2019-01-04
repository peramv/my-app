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
// ^FILE   : EntityRegJurisDetailsList.cpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 14 June 2013
//
// ^CLASS    : EntityRegJurisDetailsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "EntityRegJurisDetailsList.hpp"
#include "EntityRegJurisDetails.hpp"
#include <ifastdataimpl\dse_dstc0458_vw.hpp>
#include <ifastdataimpl\dse_dstc0458_req.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest ENT_REG_JURIS_DETAILS_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME = I_("EntityRegJurisDetailsList");
}

namespace ifds
{

}

namespace CND
{
	//extern const long ERR_DATA_NOT_FOUND;
	extern const long ERR_DATE_RANGE_OVERLAP;
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
	//  Field DD Id,              State Flags,    Group Flags 
	{ifds::AccountNum,          BFCBO::NONE,    	0 },	
	{ifds::EntityId,            BFCBO::NONE,    	0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
EntityRegJurisDetailsList::EntityRegJurisDetailsList(BFAbstractCBO &parent)
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
	setObjectAsList( );
}


//******************************************************************************
EntityRegJurisDetailsList::~EntityRegJurisDetailsList( void )
{
	TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
void EntityRegJurisDetailsList::initNew()
{     
}

//******************************************************************************
SEVERITY EntityRegJurisDetailsList::init(const DString &dstrAccountNum,										 
										 const DString &dstrEntityId,
										 const DString &dstrTrack, 
										 const DString &dstrPageName)                             
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	BFData requestData(ifds::DSTC0458_REQ);
	DString mgmtCoIdOut;

	requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
	requestData.setElementValue(ifds::Track, dstrTrack);
	requestData.setElementValue(ifds::Activity, dstrPageName);

	// For new account, send account# 0 - backend will handle it.
	requestData.setElementValue(ifds::AccountNum, getParent()->isNew()? I_("0"):dstrAccountNum);
	requestData.setElementValue(ifds::EntityId, dstrEntityId);

	ReceiveData(DSTC_REQUEST::ENT_REG_JURIS_DETAILS_INQUIRY, requestData, ifds::DSTC0458_VW, DSTCRequestor(getSecurity(), true));

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY EntityRegJurisDetailsList::init(const BFData& data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( data )" ) );

	attachDataObject( const_cast<BFData&>(data), false, true );

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY EntityRegJurisDetailsList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

	pObjOut = new EntityRegJurisDetails( *this );
	((EntityRegJurisDetails*)(pObjOut))->init(const_cast<BFData&>(data));

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY EntityRegJurisDetailsList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

	EntityRegJurisDetails *pEntityRegJurisDetails = new EntityRegJurisDetails(*this);

	pEntityRegJurisDetails->initNew(idDataGroup);
	pBase = pEntityRegJurisDetails;

	return(GETCURRENTHIGHESTSEVERITY());
}



//******************************************************************************
SEVERITY EntityRegJurisDetailsList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	validateOverlappingDateRanges(idDataGroup);

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void EntityRegJurisDetailsList::getDefaultEntityId(DString &dstrDefaultEntityId,
											  const BFDataGroupId& idDataGroup)
{
	getField(ifds::EntityId, dstrDefaultEntityId, idDataGroup, false);
}

//******************************************************************************
void EntityRegJurisDetailsList::setDefaultEntityId(DString &dstrDefaultEntityId,
											  const BFDataGroupId& idDataGroup)
{
	setFieldNoValidate(ifds::EntityId, dstrDefaultEntityId, idDataGroup, false);
	
	// Access from AllEntity or EntityId, only 1 Entity allowed.
	BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
	EntityRegJurisDetails *pEntityRegJurisDetails = NULL;

	iter.begin();
	while(!iter.end())
	{
		pEntityRegJurisDetails = dynamic_cast< EntityRegJurisDetails * >(iter.getObject());
		pEntityRegJurisDetails->setDefaultEntityId(dstrDefaultEntityId, idDataGroup);
		++iter;
	}
}

//******************************************************************************
SEVERITY EntityRegJurisDetailsList::validateOverlappingDateRanges(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateOverlappingDateRanges"));

	BFObjIter iter1(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
	BFObjIter iter2(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

	iter1.begin();

	while(!iter1.end())
	{
		DString entRegJurStartDate1, entRegJurStopDate1, 
				entRegJurEntityId1, entRegJurRegulation1, entRegJurTaxJuris1,
			    entRegJurStartDate2, entJurRegStopDate2,
				entRegJurEntityId2, entRegJurRegulation2, entRegJurTaxJuris2;				

		iter1.getObject()->getField(ifds::TaxPayerStartDate, entRegJurStartDate1, idDataGroup);
		iter1.getObject()->getField(ifds::TaxPayerStopDate, entRegJurStopDate1, idDataGroup);
		iter1.getObject()->getField(ifds::EntityId, entRegJurEntityId1, idDataGroup);
		iter1.getObject()->getField(ifds::FATCACode, entRegJurRegulation1, idDataGroup);
		iter1.getObject()->getField(ifds::TaxJuris, entRegJurTaxJuris1, idDataGroup);

		iter2.positionByKey(iter1.getStringKey()); 
		++iter2;

		while (!iter2.end())
		{
			iter2.getObject()->getField(ifds::TaxPayerStartDate, entRegJurStartDate2, idDataGroup);
			iter2.getObject()->getField(ifds::TaxPayerStopDate, entJurRegStopDate2, idDataGroup);
			iter2.getObject()->getField(ifds::EntityId, entRegJurEntityId2, idDataGroup);
			iter2.getObject()->getField(ifds::FATCACode, entRegJurRegulation2, idDataGroup);
			iter2.getObject()->getField(ifds::TaxJuris, entRegJurTaxJuris2, idDataGroup);

			if( (entRegJurEntityId1 == entRegJurEntityId2) && (entRegJurRegulation1 == entRegJurRegulation2) &&
				 (entRegJurTaxJuris1 == entRegJurTaxJuris2) )
			{
				if (DSTCommonFunctions::dateRangesOverlap(entRegJurStartDate1, entRegJurStopDate1, entRegJurStartDate2, entJurRegStopDate2))
				{
					ADDCONDITIONFROMFILE(CND::ERR_DATE_RANGE_OVERLAP);
				}
			}

			++iter2;
		}

		++iter1;
	}
	return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************
SEVERITY EntityRegJurisDetailsList::doApplyRelatedChanges (const BFFieldId &idField, 
										const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if (idField == ifds::AccountNum)
	{
		setFieldUpdated (ifds::AccountNum, idDataGroup, false);
	}

	return(GETCURRENTHIGHESTSEVERITY());
}
