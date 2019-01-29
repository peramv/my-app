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
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : DSTCTransCancelTrxnBuilder.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Feb 28,2005
//
// ^CLASS    : DSTCTransCancelTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCTransCancelTrxnBuilder.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0338_req.hpp>
#include <ifastdataimpl\dse_dstc0338_vw.hpp>
#include <ifastdataimpl\dse_dstc0338_reqrepeat_record.hpp>

#include "DilutionAllocList.hpp"
#include "DilutionAlloc.hpp"
#include "TransCancellist.hpp"
#include "TransCancel.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANS_CANCEL_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCTransCancelTrxnBuilder" );
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

int DSTCTransCancelTrxnBuilder::buildIndex = 0;
//******************************************************************************
void DSTCTransCancelTrxnBuilder::buildTrxnKey( DString& strKey, TransCancel* pTransCancel )
{  
	DString transNum;
	pTransCancel->getField( ifds::TransNum, transNum, BF::HOST, true );
    transNum.strip();
    //build the key
    addIDITagValue( strKey, TRXNTAG::TRANSNUMTAG, transNum );
}

//******************************************************************************
SEVERITY DSTCTransCancelTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
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
    addIDITagValue( keyString, TRXNTAG::FUNDBROKERTAG, DString::asString( buildIndex++ ) );

	TransCancel* pTransCancel = NULL;
	TransCancellist* pTransCancelList = dynamic_cast< TransCancellist* >(pObj);
	BFObjIter iter (*pTransCancelList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);               
	if (!iter.end ())
	{
		pTransCancel = dynamic_cast <TransCancel*> (iter.getObject());
	}
	if( pTransCancel && pTransCancel->hasTransactionUpdates(true) )
	{
		//define an iterator on the HostTransactionContainer
		HostTransactionContainerIterator iterTrxnContList( pTrCont );
		//set filter to look for BrokerAMS fixed area
		iterTrxnContList.walkStrKey( keyString );
		//the trxn hasn't been handled yet, no group and sub type set,
		iterTrxnContList.walkTrxnGroup( NO_GROUP );
		iterTrxnContList.walkTrxnSubType( 0 );
		iterTrxnContList.begin();

		if( iterTrxnContList.end() )
		// Fixed Area either does not exists, so create a new one
		{
			pDataReq   = new BFData( ifds::DSTC0338_REQ );
			pDataRes   = new BFData( ifds::DSTC0338_VW );

			pTransCancel->getData( *pDataReq, BF::HOST );

			pDataReq->setElementValue( ifds::Track, I_("N") );
			pDataReq->setElementValue( ifds::Activity, I_("") );

			DString mgmtCoId;
			workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
			pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
			
			DString dstrRunMode, dstrModPerm, dstrTranStatus;
			pTransCancel->getField(ifds::ModPermission, dstrModPerm, BF::HOST);
			pTransCancel->getField(ifds::TranStatus, dstrTranStatus, BF::HOST);
			if( dstrModPerm == NULL_STRING ) dstrRunMode = I_("A");
			else if( dstrTranStatus == I_("03")) dstrRunMode = I_("D");
			else dstrRunMode = I_("M");
			pDataReq->setElementValue( ifds::RunMode, dstrRunMode );

			DString dstrKeyTypes;
			DSTCTransCancelTrxnBuilder::buildTrxnKey( dstrKeyTypes, pTransCancel );
			//add the transaction to the container;
			JData *jdata = new JData( DSTC_REQUEST::TRANS_CANCEL_UPDATE, pDataReq, pDataRes );
			pTrCont->addTransaction( keyString, jdata, objActivity, NOT_PERSISTENT, dstrKeyTypes );
		}
		
		DString dstrEventReceiptTime,dstrEventReceiptDate; 
		pTransCancel->getField(ifds::EventReceiptTime, dstrEventReceiptTime, BF::HOST);
		pTransCancel->getField(ifds::EventReceiptDate, dstrEventReceiptDate, BF::HOST);
		//if date is empty for what ever reason,time should also be empty
		if(dstrEventReceiptDate.stripAll().empty())
		{
			pDataReq->setElementValue( ifds::EventReceiptTime, NULL_STRING);
		}
		//remove the mask and send the time to the view
		else if(!dstrEventReceiptTime.stripAll().empty())
		{
			removeMaskFromString(dstrEventReceiptTime,I_("##:##:##"));
			pDataReq->setElementValue( ifds::EventReceiptTime, dstrEventReceiptTime);
		}

		DilutionAllocList * pDilutionList = NULL;
		pTransCancel->getDilutionAllocList( BF::HOST, pDilutionList );

		if( pDilutionList )
		{
         DString  dstrSettleNetwork, dstcDilutionLinkNum, dstrMatchingKey;
         pDilutionList->getField(ifds::SettleNetwork, dstrSettleNetwork, BF::HOST, false);
         pDataReq->setElementValue(ifds::SettleNetwork, dstrSettleNetwork);
		 pDilutionList->getField(ifds::DilutionLinkNum, dstcDilutionLinkNum, BF::HOST, false);
         pDataReq->setElementValue(ifds::DilutionLinkNum, dstcDilutionLinkNum);

		 pDilutionList->getField(ifds::MatchingKey, dstrMatchingKey, BF::HOST, false);
         pDataReq->setElementValue(ifds::MatchingKey, dstrMatchingKey);

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
						BFData repeat( ifds::DSTC0338_REQRepeat_Record );
						//fill in the request update, only the part for which the BrokerAMS is responsible
						pDilution->getData( repeat, BF::HOST );
						//set the RunMode field to the Update trxn
						DSTCWorkSession::setRunMode( &repeat, lObjActivity );            
			            
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCTransCancelTrxnBuilder.cpp-arc  $
// 
//    Rev 1.3   Nov 02 2007 11:28:26   jankovii
// IN #1057653 - trade cancellation using split dilution.
// 
//    Rev 1.2   Mar 16 2005 15:35:06   Fengyong
// PET1190 FN05 - change view 337 to repeatable
// 
//    Rev 1.1   Mar 07 2005 13:44:10   Fengyong
// PET1190FN04 - TransCancellist Add RunMode
// 
//    Rev 1.0   Mar 03 2005 18:33:16   Fengyong
// Initial revision.
// 
*/