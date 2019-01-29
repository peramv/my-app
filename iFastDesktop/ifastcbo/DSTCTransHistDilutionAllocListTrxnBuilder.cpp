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
//******************************************************************************
//
// ^FILE   : DSTCTransHistDilutionAllocListTrxnBuilder.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : December, 2005
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCTransHistDilutionAllocListTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "DSTCTransHistDilutionAllocListTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "DilutionAlloc.hpp"
#include "DilutionAlloclist.hpp"

#include <ifastdataimpl\dse_dstc0357_req.hpp>
#include <ifastdataimpl\dse_dstc0357_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0357_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANS_HIST_DILUTION_ALLOC_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_("DSTCTransHistDilutionAllocListTrxnBuilder");
   const I_CHAR* BUILDTRANSACTIONS = I_("buildTransactions");
}

extern BF_OBJ_TYPE OBJ_TYPE_TRANS_HIST_DILUTION_ALLOC_LIST;


//******************************************************************************
void DSTCTransHistDilutionAllocListTrxnBuilder::buildTrxnKey (DString& dstrKey) 
{
}

//******************************************************************************
SEVERITY DSTCTransHistDilutionAllocListTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
																	   BFAbstractCBO *pObj, 
																	   HostTransactionContainer *pTrCont, 
																	   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   DString dstrTransId;

   DilutionAllocList *pList = dynamic_cast<DilutionAllocList*>(pObj);   
   if ( NULL != pList )
   {
		BFObjIter iterList (*pList, BF::HOST);
		iterList.begin ();
		while (!iterList.end ())
		{
			DilutionAlloc *pDilutionAlloc = dynamic_cast <DilutionAlloc*>(iterList.getObject() );

			if( NULL != pDilutionAlloc)
			{
				pDilutionAlloc->getField( ifds::TransId, dstrTransId, BF::HOST );
				dstrTransId.stripAll();
				break;
			}
			++iterList;
		}   
		
		DString _dstrTrxnKey( I_("DilutionAllocList") + dstrTransId );
		HostTransactionContainerIterator iterTrxnContList (pTrCont);
		BFData adds;
		   
		//set filter to look for the update fixed area
		iterTrxnContList.walkStrKey (_dstrTrxnKey);
		iterTrxnContList.walkTrxnGroup (NO_GROUP);
		iterTrxnContList.walkTrxnSubType (0);
	   
		BFData *pDataReq = NULL;
		BFData *pDataRes = NULL;           

		
		if(pList->hasTransactionUpdates())
		{
			DString strTrack, strActivity, mgmtCoId;

			//populate the fixed session
			pDataReq = new BFData (ifds::DSTC0357_REQ);
			pDataRes = new BFData (ifds::DSTC0357_VW);
			pList->getTrackActivity (strTrack, strActivity);
			pDataReq->setElementValue (ifds::Track, strTrack, false, false);
			pDataReq->setElementValue (ifds::Activity, strActivity, false, false);
			//continue to fill in the request update, 
			workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
			pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);

			pDataReq->setElementValue( ifds::TransId, dstrTransId );
		   
			DString dstrSettleNetwork, dstrDilutionLinkNum, dstrMatchingKey;
			pList->getField(ifds::SettleNetwork, dstrSettleNetwork, BF::HOST);
			pList->getField(ifds::DilutionLinkNum, dstrDilutionLinkNum, BF::HOST);
			pDataReq->setElementValue( ifds::SettleNetwork, dstrSettleNetwork );
			pDataReq->setElementValue( ifds::DilutionLinkNum, dstrDilutionLinkNum );

			pList->getField(ifds::MatchingKey, dstrMatchingKey, BF::HOST);
			pDataReq->setElementValue (ifds::MatchingKey, dstrMatchingKey);

			JData *jdata = new JData (DSTC_REQUEST::TRANS_HIST_DILUTION_ALLOC_UPDATE, pDataReq, pDataRes);

			pTrCont->addTransaction ( _dstrTrxnKey, 
										jdata, 
										objActivity, 
										NOT_PERSISTENT, 
										I_( "" ) );	
		}

		iterList.begin ();
		while (!iterList.end ())
		{
			DilutionAlloc *pDilutionAlloc = dynamic_cast <DilutionAlloc*>(iterList.getObject() );

			if( NULL != pDilutionAlloc&& iterList.hasTransactionUpdates() )
			{
				iterTrxnContList.begin ();
				//fill in the fixed area, 
				//didn't find the request in the trxn container
				if (!iterTrxnContList.end ())
				{
					pDataReq = (*iterTrxnContList)->getRequestDataObject ();					
				}
				//create a repeat for the request and fill it in
				BFData repeat (ifds::DSTC0357_REQRepeat_Record);
	   
				//fill in the request update,
				pDilutionAlloc->getData (repeat, BF::HOST);
				//set the RunMode field to the trxn
				DSTCWorkSession::setRunMode (&repeat, iterList.getKey ().getActivity ());

				//check whether this is an 'Add' repeat, if yes, save it for later use
				DString runMode = repeat.getElementValue (ifds::RunMode);

				runMode.stripAll();
				if (runMode == RUNMODE::ADDED)
				{
					adds.addRepeat (repeat);
				}
				else
				{
					//add the repeat to the request
					pDataReq->addRepeat (repeat);
				}
			}
			++iterList;
		}
		if (pDataReq != NULL && pDataRes != NULL)
		{
			int noOfAdds = adds.getRepeatCount ();

			if (noOfAdds > 0) //add the previously saved adds
			{
				for (int i = 0; i < noOfAdds; i++)
				{
				pDataReq->addRepeat (adds.getRepeat (i));
				}
			}

			DString dstRepeats = DString::asString (pDataReq->getRepeatCount ());

			pDataReq->setElementValue (ifds::RepeatCount, dstRepeats);
		}
   }	


   /*
   DString dstrTransId;
   BFObjIter iter( *pDilutionAllocList, 
				   BF::HOST );
   iter.begin();
   while (!iter.end ())
   {
         DilutionAlloc *pDilutionAlloc = dynamic_cast <DilutionAlloc*> (iter.getObject ());
         if( NULL != pDilutionAlloc )
		 {
			 pDilutionAlloc->getField( ifds::TransId, dstrTransId, BF::HOST );
			 dstrTransId.stripAll();
			 break;
		 }
		 ++iter;
   }
	   
   std::vector<BFFieldId> fields;

   fields.push_back(ifds::TransId );
   DSTCListTrxnBuilder<DilutionAlloc*> DilutionAllocListTrxnBuilder;
               
   TRXNINFO DilutionAllocListTrxnInfo( I_("DilutionAllocList") + dstrTransId, 																		
  									   DSTC_REQUEST::TRANS_HIST_DILUTION_ALLOC_UPDATE,
									   ifds::DSTC0357_REQ,
									   ifds::DSTC0357_REQRepeat_Record,
									   ifds::DSTC0357_VW,
									   fields);

   DilutionAllocListTrxnBuilder.buildTransactions( workSession, 
			  				 					   pTrCont, 
												   pDilutionAllocList, 
  												   DilutionAllocListTrxnInfo,
                                                   objActivity,
                                                   I_( "" ) ); 
   */

			         
   return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCTransHistDilutionAllocListTrxnBuilder.cpp-arc  $
// 
//    Rev 1.1   Dec 14 2005 11:15:20   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.0   Dec 13 2005 19:19:06   porteanm
// Initial revision.
//
//
