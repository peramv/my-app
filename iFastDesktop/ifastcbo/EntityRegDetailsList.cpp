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
// ^FILE   : EntityRegDetailsList.cpp
// ^AUTHOR :
// ^DATE   : 08 January 2014
//
// ^CLASS    : EntityRegDetailsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "EntityRegDetailsList.hpp"
#include "EntityRegDetails.hpp"
#include <ifastdataimpl\dse_dstc0456_vw.hpp>
#include <ifastdataimpl\dse_dstc0456_req.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest ENT_REG_DETAILS_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME = I_("EntityRegDetailsList");
}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId EntityId;
}

namespace CND
{
	/*extern const long ERR_DATA_NOT_FOUND;*/
	extern const long ERR_DATE_RANGE_OVERLAP;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
	//  Field DD Id,              State Flags,    Group Flags 
	{ifds::AccountNum,          BFCBO::NONE,    	0 }, 	
	{ifds::EntityId,            BFCBO::NONE,    	0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
EntityRegDetailsList::EntityRegDetailsList(BFAbstractCBO &parent)
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
	setObjectAsList( );
}


//******************************************************************************
EntityRegDetailsList::~EntityRegDetailsList( void )
{
	TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
void EntityRegDetailsList::initNew()
{     
}

//******************************************************************************
SEVERITY EntityRegDetailsList::init(const DString &dstrAccountNum,
									const DString &dstrEntityId,
									const DString &dstrTrack, 
									const DString &dstrPageName)                             
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	BFData requestData(ifds::DSTC0456_REQ);
	DString mgmtCoIdOut;

	requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
	requestData.setElementValue(ifds::Track, dstrTrack);
	requestData.setElementValue(ifds::Activity, dstrPageName);

	// For new account, send account# 0 - backend will handle it.
	requestData.setElementValue(ifds::AccountNum, getParent()->isNew()? I_("0"):dstrAccountNum);
	requestData.setElementValue(ifds::EntityId, dstrEntityId);

	ReceiveData(DSTC_REQUEST::ENT_REG_DETAILS_INQUIRY, requestData, ifds::DSTC0456_VW, DSTCRequestor(getSecurity(), true));

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY EntityRegDetailsList::init(const BFData& data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( data )" ) );

	attachDataObject( const_cast<BFData&>(data), false, true );

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY EntityRegDetailsList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

	pObjOut = new EntityRegDetails( *this );
	((EntityRegDetails*)(pObjOut))->init(const_cast<BFData&>(data));

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY EntityRegDetailsList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

	EntityRegDetails *pEntityRegDetails = new EntityRegDetails(*this);

	pEntityRegDetails->initNew(idDataGroup);
	pBase = pEntityRegDetails;

	return(GETCURRENTHIGHESTSEVERITY());
}



//******************************************************************************
SEVERITY EntityRegDetailsList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	validateOverlappingDateRanges(idDataGroup);

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void EntityRegDetailsList::getDefaultEntityId(DString &dstrDefaultEntityId,
											  const BFDataGroupId& idDataGroup)
{
	getField(ifds::EntityId, dstrDefaultEntityId, idDataGroup, false);
}

//******************************************************************************
void EntityRegDetailsList::setDefaultEntityId(DString &dstrDefaultEntityId,
											  const BFDataGroupId& idDataGroup)
{
	setFieldNoValidate(ifds::EntityId, dstrDefaultEntityId, idDataGroup, false);

	// Access from AllEntity or EntityId, only 1 Entity allowed.
	BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
	EntityRegDetails *pEntityRegDetails = NULL;

	iter.begin();
	while(!iter.end())
	{
		pEntityRegDetails = dynamic_cast< EntityRegDetails * >(iter.getObject());
		pEntityRegDetails->setDefaultEntityId(dstrDefaultEntityId, idDataGroup);
		++iter;
	}

}
//******************************************************************************
SEVERITY EntityRegDetailsList::validateOverlappingDateRanges(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateOverlappingDateRanges"));

	BFObjIter iter1(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
	BFObjIter iter2(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

	iter1.begin();

	while(!iter1.end())
	{
		DString entRegStartDate1, entRegStopDate1, 
				entRegEntityId1, entRegRegulation1,
			    entRegStartDate2, entRegStopDate2,
				entRegEntityId2, entRegRegulation2;				

		iter1.getObject()->getField(ifds::EffectiveDate, entRegStartDate1, idDataGroup);
		iter1.getObject()->getField(ifds::StopDate, entRegStopDate1, idDataGroup);
		iter1.getObject()->getField(ifds::EntityId, entRegEntityId1, idDataGroup);
		iter1.getObject()->getField(ifds::FATCACode, entRegRegulation1, idDataGroup);

		iter2.positionByKey(iter1.getStringKey()); 
		++iter2;

		while (!iter2.end())
		{
			iter2.getObject()->getField(ifds::EffectiveDate, entRegStartDate2, idDataGroup);
			iter2.getObject()->getField(ifds::StopDate, entRegStopDate2, idDataGroup);
			iter2.getObject()->getField(ifds::EntityId, entRegEntityId2, idDataGroup);
			iter2.getObject()->getField(ifds::FATCACode, entRegRegulation2, idDataGroup);

			if( (entRegEntityId1 == entRegEntityId2) && (entRegRegulation1 == entRegRegulation2) )
			{
				if (DSTCommonFunctions::dateRangesOverlap(entRegStartDate1, entRegStopDate1, entRegStartDate2, entRegStopDate2))
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
SEVERITY EntityRegDetailsList::doApplyRelatedChanges (const BFFieldId &idField, 
										const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if (idField == ifds::AccountNum)
	{
		setFieldUpdated (ifds::AccountNum, idDataGroup, false);
	}

	return(GETCURRENTHIGHESTSEVERITY());
}