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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DSTCBulkCancelTrxnBuilder.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : November 2005
//
// ^CLASS    : DSTCBulkCancelTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCBulkCancelTrxnBuilder.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0337_vw.hpp>
#include <ifastdataimpl\dse_dstc0355_req.hpp>
#include <ifastdataimpl\dse_dstc0355_vw.hpp>
#include <ifastdataimpl\dse_dstc0355_reqrepeat_record.hpp>

#include "bulkcancel.hpp"
#include "BulkCancellist.hpp"
#include "DilutionAllocList.hpp"
#include "DilutionAlloc.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BULK_CANCEL_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCBulkCancelTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId ModPermission;
}

int DSTCBulkCancelTrxnBuilder::buildIndex = 0;
//******************************************************************************
void DSTCBulkCancelTrxnBuilder::buildTrxnKey( DString& strKey, BulkCancel* pBulkCancel )
{  	
	DString dstrTradeDate, dstrFund, dstrClass;
	pBulkCancel->getField( ifds::TradeDate, dstrTradeDate, BF::HOST, true );
	pBulkCancel->getField( ifds::Fund,      dstrFund,      BF::HOST, true );
	pBulkCancel->getField( ifds::Class,     dstrClass,     BF::HOST, true );
    
	dstrTradeDate.strip();
	dstrFund.strip();
	dstrClass.strip();

    //build the key    
	if( dstrTradeDate != NULL_STRING )
         addIDITagValue( strKey, TRXNTAG::BULKCANCELTAG, dstrTradeDate );
	if( dstrFund != NULL_STRING )
         addIDITagValue( strKey, TRXNTAG::BULKCANCELTAG, dstrFund );
	if( dstrClass != NULL_STRING )
         addIDITagValue( strKey, TRXNTAG::BULKCANCELTAG, dstrClass );
}

//******************************************************************************
SEVERITY DSTCBulkCancelTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
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
    addIDITagValue( keyString, TRXNTAG::BULKCANCELTAG, DString::asString( buildIndex++ ) );

	BulkCancel* pBulkCancel = NULL;
	BulkCancellist* pBulkCancelList = dynamic_cast< BulkCancellist* >(pObj);
	BFObjIter iter (*pBulkCancelList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);               
	if (!iter.end ())
	{
		pBulkCancel = dynamic_cast <BulkCancel*> (iter.getObject());
	}
	if( pBulkCancel && pBulkCancel->hasTransactionUpdates() )
	{
		//define an iterator on the HostTransactionContainer
		HostTransactionContainerIterator iterTrxnContList( pTrCont );
		//set filter to look for BulkCancellation fixed area
		iterTrxnContList.walkStrKey( keyString );
		//the trxn hasn't been handled yet, no group and sub type set,
		iterTrxnContList.walkTrxnGroup( NO_GROUP );
		iterTrxnContList.walkTrxnSubType( 0 );
		iterTrxnContList.begin();

		if( iterTrxnContList.end() )
		// Fixed Area either does not exists, so create a new one
		{
			pDataReq   = new BFData( ifds::DSTC0355_REQ );
			pDataRes   = new BFData( ifds::DSTC0355_VW );

			pBulkCancel->getData( *pDataReq, BF::HOST );

			pDataReq->setElementValue( ifds::Track, I_("N") );
			pDataReq->setElementValue( ifds::Activity, I_("") );

			DString mgmtCoId;
			workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
			pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
			
			DString dstrRunMode, dstrModPerm;
			pBulkCancel->getField(ifds::ModPermission, dstrModPerm, BF::HOST);			
			if( dstrModPerm == NULL_STRING ) 
				dstrRunMode = I_("A");			
			else
			{
				dstrRunMode = I_("M");
				DString dstrTradeAdjustID;
				pBulkCancel->getField( ifds::TradeAdjustID, dstrTradeAdjustID, BF::HOST );
				pDataReq->setElementValue( ifds::TradeAdjustID, dstrTradeAdjustID );
			}
			pDataReq->setElementValue( ifds::RunMode, dstrRunMode );

			DString dstrKeyTypes;
			DSTCBulkCancelTrxnBuilder::buildTrxnKey( dstrKeyTypes, pBulkCancel );
			//add the transaction to the container;
			JData *jdata = new JData( DSTC_REQUEST::BULK_CANCEL_UPDATE, pDataReq, pDataRes );
			pTrCont->addTransaction( keyString, jdata, objActivity, NOT_PERSISTENT, dstrKeyTypes );
		}


		DilutionAllocList * pDilutionList = NULL;
		pBulkCancel->getDilutionAllocList( BF::HOST, pDilutionList );

		if( pDilutionList )
		{
			BFObjIter bfIter( *pDilutionList, BF::HOST );
			bfIter.begin();
			while( !bfIter.end() )
			{
				DilutionAlloc* pDilution = dynamic_cast< DilutionAlloc* >( bfIter.getObject() );
				BF_OBJ_ACTIVITY lObjActivity = bfIter.getKey().getActivity();	

				if( lObjActivity == OBJ_ACTIVITY_ADDED || lObjActivity == OBJ_ACTIVITY_DELETED
							|| pDilution->hasTransactionUpdates() )
				{	
						//create a repeat for the request and filled in
						BFData repeat( ifds::DSTC0355_REQRepeat_Record );
						//fill in the request update, only the part for which the Dilution is responsible
						pDilution->getData( repeat, BF::HOST );
						
						//set the RunMode field to the Update trxn
						//////////DSTCWorkSession::setRunMode( &repeat, lObjActivity );                            
						if( lObjActivity == OBJ_ACTIVITY_NONE )
						{
							repeat.setElementValue( ifds::DilRunMode, RUNMODE::MODIFIED );
						}
						else if( lObjActivity == OBJ_ACTIVITY_ADDED )
						{
							repeat.setElementValue( ifds::DilRunMode, RUNMODE::ADDED );
						}
						else if( lObjActivity == OBJ_ACTIVITY_DELETED )
						{
							repeat.setElementValue( ifds::DilRunMode, RUNMODE::DELETED );
						} 						

			            
						//add the repeat to the retrieved request
						pDataReq->addRepeat( repeat );
						//cRepeats = pDataReq->getRepeatCount();
						//pDataReq->setElementValue( ifds::RepeatCount, DString::asString( cRepeats ), false, false );
						cRepeats ++;
				}

				++bfIter;
		       
			}//end while
		}
	
		if(cRepeats > 0)
			pDataReq->setElementValue( ifds::RepeatCount, DString::asString( cRepeats ), false, false );
	}	 	
   
    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCBulkCancelTrxnBuilder.cpp-arc  $
// 
//    Rev 1.5   Dec 29 2005 13:12:02   porteanm
// Incident 501804 - Allow multiple Bulk Cancellation Instructions for the same Trade Date/Fund/Class. View fixed previously missing TradeAdjustID.
// 
//    Rev 1.4   Nov 23 2005 17:57:02   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.3   Nov 23 2005 17:12:52   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.2   Nov 10 2005 13:23:56   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.1   Nov 06 2005 15:09:56   porteanm
// PET 1286 FN01 - Bulk Cancellation - work in progress.
// 
//    Rev 1.0   Nov 05 2005 15:08:08   porteanm
// Initial revision.
// 
*/