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
//    Copyright 2008 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCAcctSettlementRuleTrxnBuilder.cpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : Febuary 2008
//
// ^CLASS    : DSTCAcctSettlementRuleTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "DSTCAcctSettlementRuleTrxnBuilder.hpp"
#include "AcctSettlementRule.hpp"
#include "AcctSettlementRuleList.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0387_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0387_req.hpp>
#include <ifastdataimpl\dse_dstc0387_vw.hpp>


namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest ACCT_CONTROL_MAINTENANCE;
}

namespace
{
    const I_CHAR* CLASSNAME          = I_( "DSTCAcctSettlementRuleTrxnBuilder" );
    const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
    extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
    extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

namespace KEYTYPES
{
    extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
void DSTCAcctSettlementRuleTrxnBuilder::buildTrxnKey( DString& strKey, MFAccount *pMFAccount, 
                                                      AcctLvlSttlmntRuleList* pAcctLvlSttlmntRuleList )
{
    DString dstrAccountNum;
    DString dstrRuletype;
    DString dstrFundcode;
    DString dstrClasscode;
    DString dstrEffdate;
    DString dstrStopdate;

    pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
    dstrAccountNum.stripLeading( '0' );
    dstrAccountNum.strip();

    //build the key
    addIDITagValue( strKey, TRXNTAG::ACCTSETTLEMENTRULETAG, dstrAccountNum );
}

//******************************************************************************
SEVERITY DSTCAcctSettlementRuleTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj, 
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
    SEVERITY severity = SEVERE_ERROR;
    MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);

    if( pMFAccount != NULL )
    {
        DString dstrAccountNum, dstTrnKey, dstKeyTypes;
        pMFAccount->getField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
        addIDITagValue( dstTrnKey, I_("AcctLevelSettlementRuleList"), dstrAccountNum.stripLeading('0').strip() );
        addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );

        HostTransactionContainerIterator iterTrxnContList( pTrCont );
        //set filter to look for Entity fixed area
        iterTrxnContList.walkStrKey( dstTrnKey );
        iterTrxnContList.walkTrxnGroup( NO_GROUP );
        iterTrxnContList.walkTrxnSubType( 0 );

        AcctLvlSttlmntRuleList* pAcctLvlSttlmntRuleList = NULL;

        //if no list do not go and get one from the database
        severity = pMFAccount->getAcctSettlementRuleList( pAcctLvlSttlmntRuleList, BF::HOST, false );

        if( pAcctLvlSttlmntRuleList != NULL && severity <= WARNING )
        {
            BFData *pDataReq = NULL;
            BFData *pDataRes = NULL;

            BFObjIter iterAcctLvlSttlmntRuleList( *pAcctLvlSttlmntRuleList, BF::HOST );
            AcctLvlSttlmntRule* pAcctLvlSttlmntRule = NULL;

            iterAcctLvlSttlmntRuleList.begin();
            while( !iterAcctLvlSttlmntRuleList.end() )
            {
                pAcctLvlSttlmntRule = 
                    dynamic_cast<AcctLvlSttlmntRule*>(iterAcctLvlSttlmntRuleList.getObject());

                if( iterAcctLvlSttlmntRuleList.hasTransactionUpdates( ) )
                {
                    iterTrxnContList.begin();
                    if( iterTrxnContList.end() )
                    {
                        pDataReq = new BFData( ifds::DSTC0387_REQ );
                        pDataRes = new BFData( ifds::DSTC0387_VW );

                        DString strTrack, strActivity;
                        pAcctLvlSttlmntRuleList->getTrackActivity(strTrack,strActivity);          
                        pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                        pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                        DString mgmtCoId;
                        workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                        pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
                        pDataReq->setElementValue( ifds::AccountNum, dstrAccountNum );

                        JData *jdata = new JData( DSTC_REQUEST::ACCT_CONTROL_MAINTENANCE, pDataReq, pDataRes );
                        pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
                    }
                    else
                        pDataRes = (*iterTrxnContList)->getRequestDataObject();

                    //create a repeat for the request and filled it in
                    BFData lDataRepeat( ifds::DSTC0387_REQRepeat_Record );

                    //fill in the request update, only the part for which the Settlement Rule is responsible
                    pAcctLvlSttlmntRule->getData( lDataRepeat, BF::HOST );

                    //set the RunMode field
                    DSTCWorkSession::setRunMode( &lDataRepeat, iterAcctLvlSttlmntRuleList.getKey().getActivity() );

                    //add the lDataRepeat to the request
                    pDataReq->addRepeat( lDataRepeat );
                    DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
                    pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );
                }
                ++iterAcctLvlSttlmntRuleList;
            }
        }
    }

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctSettlementRuleTrxnBuilder.cpp-arc  $ */
// 
//    Rev 1.2   Apr 16 2008 18:51:12   daechach
// PET2385 FN02&07 - Modified code regarding code review.
