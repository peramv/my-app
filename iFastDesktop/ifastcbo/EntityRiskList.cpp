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
// ^FILE   : EntityRiskList.cpp
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : EntityRiskList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "EntityRiskList.hpp"
#include "EntityRisk.hpp"
#include "Entity.hpp"

#include <ifastdataimpl\dse_dstc0477_vw.hpp>
#include <ifastdataimpl\dse_dstc0477_req.hpp>

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest ENTITY_RISK_INQUIRY;
}

namespace
{
    const I_CHAR * const CLASSNAME = I_("EntityRiskList");
}

namespace ifds
{
    extern CLASS_IMPORT const BFNumericFieldId EntityId;
    extern CLASS_IMPORT const BFTextFieldId HighestRiskLevel;
    extern CLASS_IMPORT const BFTextFieldId RiskLevelRanking;
    extern CLASS_IMPORT const BFTextFieldId HighRiskLevels;
}

namespace CND
{
    extern const long ERR_DUPLICATE_RECORD;
}

int EntityRiskList::nextUUID = 1;

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
    //  Field DD Id,              State Flags,    Group Flags 
    {ifds::EntityId,            BFCBO::REQUIRED,    	0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
EntityRiskList::EntityRiskList(BFAbstractCBO &parent)
    : MFCanBFCbo( parent )
{
    TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

    registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
    setObjectAsList();
}


//******************************************************************************
EntityRiskList::~EntityRiskList(void)
{
    TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
void EntityRiskList::initNew(const DString &dstrEntityId, const BFDataGroupId& idDataGroup)
{
    setFieldNoValidate(ifds::EntityId, dstrEntityId, idDataGroup, false, true);
}

//******************************************************************************
SEVERITY EntityRiskList::init(const DString &dstrEntityId,
                              const DString &dstrTrack, 
                              const DString &dstrPageName)                             
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

    BFData requestData(ifds::DSTC0477_REQ);
    DString mgmtCoIdOut;

    requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
    requestData.setElementValue(ifds::Track, dstrTrack);
    requestData.setElementValue(ifds::Activity, dstrPageName);
    requestData.setElementValue(ifds::EntityId, dstrEntityId);

    ReceiveData(DSTC_REQUEST::ENTITY_RISK_INQUIRY, requestData, ifds::DSTC0477_VW, DSTCRequestor(getSecurity(), true));

    return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY EntityRiskList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

    pObjOut = new EntityRisk( *this );
    ((EntityRisk*)(pObjOut))->init(const_cast<BFData&>(data));

    return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY EntityRiskList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

    EntityRisk *pEntityRisk = new EntityRisk(*this);

    pEntityRisk->initNew(idDataGroup);
    pBase = pEntityRisk;

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY EntityRiskList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

    return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY EntityRiskList::doApplyRelatedChanges (const BFFieldId &idField, 
                                                const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));



    return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
void EntityRiskList::setAllRiskReadOnly(bool isReadonly, const BFDataGroupId &idDataGroup)
{
    BFObjIter iterRisk(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

    while (!iterRisk.end())
    {
        dynamic_cast<EntityRisk*>(iterRisk.getObject())->setAllFieldReadOnly(isReadonly, idDataGroup);

        ++iterRisk;
    }
}