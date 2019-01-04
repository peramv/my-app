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
//    Copyright 2002 by Internantial Financial
//
//
//******************************************************************************
//
// ^FILE   : DSTCSavingsDirectiveTrxnBuilder.cpp
// ^AUTHOR : Amelia Aguila
// ^DATE   : 15 Nov 2005
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCSavingsDirectiveTrxnBuilder.hpp"

#include "savingsdirective.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0358_req.hpp>
#include <ifastdataimpl\dse_dstc0358_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SAVINGS_DIRECTIVE_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCSavingsDirectiveTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId CompanyId;
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

int DSTCSavingsDirectiveTrxnBuilder::buildIndex = 0;

//******************************************************************************
void DSTCSavingsDirectiveTrxnBuilder::buildTrxnKey( DString& strKey, SavingsDirective* pSavingsDirective )
{  
	DString transId, tisType, tis, costType, cost, eusdOverrideVer;
	pSavingsDirective->getField( ifds::TransId, transId, BF::HOST, true );
   transId.strip();
	pSavingsDirective->getField( ifds::TISType, tisType, BF::HOST, true );
	pSavingsDirective->getField( ifds::TIS, tis, BF::HOST, true );
	pSavingsDirective->getField( ifds::CostType, costType, BF::HOST, true );
	pSavingsDirective->getField( ifds::Cost, cost, BF::HOST, true );
	pSavingsDirective->getField( ifds::EUSDOverrideVersion, eusdOverrideVer, BF::HOST, true );

    //build the key
    addIDITagValue( strKey, TRXNTAG::SAVDIRECTIVETAG, transId );
}

//******************************************************************************
SEVERITY DSTCSavingsDirectiveTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                       BFAbstractCBO* pObj,
                                                       HostTransactionContainer* pTrCont, 
                                                       BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

    SEVERITY severity = SEVERE_ERROR;
    bool first_time = true;    

    DString tmp;
    BFData* pDataReq = NULL;
    BFData* pDataRes = NULL;
    unsigned long cRepeats = 0;   

    DString keyString;
    addIDITagValue( keyString, TRXNTAG::SAVDIRECTIVETAG, DString::asString( buildIndex++ ) );

	SavingsDirective* pSavingsDirective = dynamic_cast <SavingsDirective* > (pObj);
	
	if (pSavingsDirective && pSavingsDirective->hasTransactionUpdates())
	{
		//define an iterator on the HostTransactionContainer
		HostTransactionContainerIterator iterTrxnContList( pTrCont );
		iterTrxnContList.walkStrKey( keyString );
		//the trxn hasn't been handled yet, no group and sub type set,
		iterTrxnContList.walkTrxnGroup( NO_GROUP );
		iterTrxnContList.walkTrxnSubType( 0 );
		iterTrxnContList.begin();

		if( iterTrxnContList.end() )
		// Fixed Area either does not exists, so create a new one
		{
			pDataReq   = new BFData( ifds::DSTC0358_REQ );
			pDataRes   = new BFData( ifds::DSTC0358_VW );

			pSavingsDirective->getData( *pDataReq, BF::HOST );

			pDataReq->setElementValue( ifds::Track, I_("N") );
			pDataReq->setElementValue( ifds::Activity, I_("") );

			DString mgmtCoId;
			workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
			pDataReq->setElementValue( ifds::CompanyCode, mgmtCoId );
			
			DString dstrKeyTypes;
			DSTCSavingsDirectiveTrxnBuilder::buildTrxnKey( dstrKeyTypes, pSavingsDirective );
			//add the transaction to the container;
			JData *jdata = new JData( DSTC_REQUEST::SAVINGS_DIRECTIVE_UPDATE, pDataReq, pDataRes );
			pTrCont->addTransaction( keyString, jdata, objActivity, NOT_PERSISTENT, dstrKeyTypes );
		}
	}
	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCSavingsDirectiveTrxnBuilder.cpp-arc  $
// 
//    Rev 1.0   Nov 29 2005 16:59:24   AGUILAAM
// Initial revision.
// 
*/