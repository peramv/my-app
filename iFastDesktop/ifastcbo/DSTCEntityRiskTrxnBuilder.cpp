//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use orsuch information
//    may result in civil liabilities. disclosure of 
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCEntityRiskTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCEntityRiskTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCEntityRiskTrxnBuilder.hpp"

#include "EntityRisk.hpp"
#include "EntityRiskList.hpp"
#include "Entity.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0478_req.hpp>
#include <ifastdataimpl\dse_dstc0478_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0478_vw.hpp>

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest ENTITY_RISK_UPDATE;
}
namespace
{
    const I_CHAR* CLASSNAME         = I_("DSTCEntityRiskTrxnBuilder");
}

namespace CND
{
    extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
    extern CLASS_IMPORT I_CHAR * const ENTITYID;
}

//******************************************************************************
void DSTCEntityRiskTrxnBuilder::buildTrxnKey(DString& dstrKey,  
                                             const DString &entityId) 
{
    addIDITagValue(dstrKey, TRXNTAG::ENTITYRISKTAG, I_("EntityRiskList"));
    addIDITagValue(dstrKey, TRXNTAG::ENTITYIDTAG, entityId);
}

//******************************************************************************
SEVERITY DSTCEntityRiskTrxnBuilder::buildTransactions(DSTCWorkSession &workSession,
                                                      BFAbstractCBO* pObj,
                                                      HostTransactionContainer* pTrCont, 
                                                      BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
    SEVERITY severity = SEVERE_ERROR;
    Entity* pEntity = dynamic_cast<Entity*>(pObj);
    EntityRiskList *pEntityRiskList = NULL;

    if (pEntity &&
        pEntity->getEntityRiskList(pEntityRiskList, BF::HOST) <= WARNING && pEntityRiskList)
    {
        DString dstrEntityId, dstTrnKey;
        BFObjIter iterEntityRisk(*pEntityRiskList, BF::HOST);
        TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_ENTITY_RISK : UPDATE_ENTITY_RISK;

        pEntity->getEntityId(dstrEntityId);
        dstrEntityId.stripLeading('0');
        dstrEntityId.strip();

        if (pEntityRiskList->hasTransactionUpdates())
        {
            DString dstKeyTypes;
            BFData *pDataReq = NULL;
            BFData *pDataRes = NULL;
            int count = 0;

            BFObjIter iterEntityRisk(*pEntityRiskList, BF::HOST);


            DSTCEntityRiskTrxnBuilder::buildTrxnKey(dstTrnKey, dstrEntityId);

            HostTransactionContainerIterator iterTrxnContList(pTrCont);

            iterTrxnContList.walkStrKey(dstTrnKey);
            iterTrxnContList.walkTrxnGroup(NO_GROUP);
            iterTrxnContList.walkTrxnSubType(0);

            iterTrxnContList.begin();

            //fill in the fixed area
            if (iterTrxnContList.end())
            {

                pDataReq = new BFData(ifds::DSTC0478_REQ);
                pDataRes = new BFData(ifds::DSTC0478_VW);

                DString strTrack, strActivity;

                pEntityRiskList->getTrackActivity(strTrack,strActivity);         
                pDataReq->setElementValue(ifds::Track, strTrack, false, false);
                pDataReq->setElementValue(ifds::Activity, strActivity, false, false);

                //fill in the request update
                DString mgmtCoId;
                workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

                pDataReq->setElementValue(ifds::CompanyId, mgmtCoId);
                pDataReq->setElementValue(ifds::EntityId, dstrEntityId);

                addIDITagValue(dstKeyTypes, I_("OBJECT"), I_("EntityRiskList"));
                addIDITagValue( dstKeyTypes, KEYTYPES::ENTITYID, dstrEntityId );
            }
            else
                pDataRes = (*iterTrxnContList)->getRequestDataObject();

            iterEntityRisk.begin();
            while (!iterEntityRisk.end())
            {
                if (iterEntityRisk.hasTransactionUpdates())
                {
                    count++;

                    EntityRisk *pEntityRisk = NULL;
                    pEntityRisk = dynamic_cast<EntityRisk*>(iterEntityRisk.getObject());			

                    //create a repeat for the request and fill it in
                    BFData repeat(ifds::DSTC0478_REQRepeat_Record);

                    //fill in the request update
                    pEntityRisk->getData(repeat, BF::HOST);

                    //set the RunMode field 
                    DSTCWorkSession::setRunMode(&repeat, iterEntityRisk.getKey().getActivity());

                    //add the lDataRepeat to the request
                    pDataReq->addRepeat(repeat);
                    DString dstRepeats = DString::asString(pDataReq->getRepeatCount());
                    pDataReq->setElementValue(ifds::RepeatCount, DString::asString(count), false, false);
                }

                ++iterEntityRisk;
            }

            JData *jdata = new JData(DSTC_REQUEST::ENTITY_RISK_UPDATE, pDataReq, pDataRes);
            pTrCont->addTransaction(dstTrnKey, jdata, objActivity, trxnType, dstKeyTypes);
        } 
    }

    return GETCURRENTHIGHESTSEVERITY();
}