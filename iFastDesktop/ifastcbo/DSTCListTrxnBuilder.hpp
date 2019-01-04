#pragma once 

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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCListTrxnBuilder.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : July, 2003
//
// ^CLASS    : DSTCListTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include "mgmtco.hpp"
//Forward declaration

typedef struct _trxnInfo
{
   _trxnInfo (
      const DString &trxnKey,
      const DSTCRequest &dstcRequest,
      const BFDataId &requestId, 
      const BFDataId &requestRepeatId,
      const BFDataId &viewId) :
   _trxnKey (trxnKey),
   _dstcRequest (dstcRequest),
   _requestId (requestId),
   _requestRepeatId (requestRepeatId),
   _viewId (viewId)
   {};
   _trxnInfo (
      const DString &trxnKey,
      const DSTCRequest &dstcRequest,
      const BFDataId &requestId, 
      const BFDataId &requestRepeatId,
      const BFDataId &viewId,
		const std::vector<BFFieldId> &fields) :
   _trxnKey (trxnKey),
   _dstcRequest (dstcRequest),
   _requestId (requestId),
   _requestRepeatId (requestRepeatId),
   _viewId (viewId),
	_fields (fields)
   {};
   const DString _trxnKey;
   const DSTCRequest &_dstcRequest;
   const BFDataId &_requestId;
   const BFDataId &_requestRepeatId;
   const BFDataId &_viewId;
	const std::vector<BFFieldId> _fields;

} TRXNINFO;

template <class T>
   class DSTCListTrxnBuilder
   {
   public:
      DSTCListTrxnBuilder () {};
      virtual ~DSTCListTrxnBuilder () {};
      SEVERITY buildTransactions ( DSTCWorkSession &workSession,
                                   HostTransactionContainer *pTrCont, 
                                   BFCBO *pList, 
                                   const TRXNINFO &trxninfo,
                                   BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE,
                                   const DString &dstrKeyTypes = NULL_STRING,
								   bool bCheckListUpdates = false );
   private:
   };

//******************************************************************************
template <class T>
SEVERITY DSTCListTrxnBuilder<T>::buildTransactions ( DSTCWorkSession &workSession,
                                                     HostTransactionContainer *pTrCont, 
                                                     BFCBO *pList, 
                                                     const TRXNINFO &trxninfo,
                                                     BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/,
                                                     const DString &dstrKeyTypes /*=NULL_STRING*/,
													 bool bCheckListUpdates /* = false */)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("buildTransactions"));

   DString _dstrTrxnKey (trxninfo._trxnKey);
   HostTransactionContainerIterator iterTrxnContList (pTrCont);
   BFData adds;


   //set filter to look for the update fixed area
   iterTrxnContList.walkStrKey (_dstrTrxnKey);
   iterTrxnContList.walkTrxnGroup (NO_GROUP);
   iterTrxnContList.walkTrxnSubType (0);

   if (pList)
   {
      BFObjIter iterList (*pList, BF::HOST);
      BFData *pDataReq = NULL;
      BFData *pDataRes = NULL;           

	  bool bListUpdate = false;

	  if (bCheckListUpdates)
	  {
		bListUpdate = pList->hasTransactionUpdates(false);
	  }

      iterList.begin ();
      while (!iterList.end ())
      {
         T t = dynamic_cast<T> (iterList.getObject ());

         if (t && (iterList.hasTransactionUpdates () || bListUpdate))
         {
            iterTrxnContList.begin ();
            //fill in the fixed area, 
            //didn't find the request in the trxn container
            if (iterTrxnContList.end ())
            {
               DString strTrack, strActivity, mgmtCoId;

               //populate the fixed session
               pDataReq = new BFData (trxninfo._requestId);
               pDataRes = new BFData (trxninfo._viewId);
               pList->getTrackActivity (strTrack, strActivity);
               pDataReq->setElementValue (ifds::Track, strTrack, false, false);
               pDataReq->setElementValue (ifds::Activity, strActivity, false, false);
               //continue to fill in the request update, 
               workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
               pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);
   
               JData *jdata = new JData (trxninfo._dstcRequest, pDataReq, pDataRes);

               pTrCont->addTransaction ( _dstrTrxnKey, 
                                         jdata, 
                                         objActivity, 
                                         NOT_PERSISTENT, 
                                         dstrKeyTypes);

					for (unsigned int i = 0; i < trxninfo._fields.size(); i++)
					{
						DString value;

						pList->getField (trxninfo._fields[i], value, BF::HOST);
						pDataReq->setElementValue (trxninfo._fields[i], value);
					}
            }
            else
            {
               pDataReq = (*iterTrxnContList)->getRequestDataObject ();					
            }
            //create a repeat for the request and filled it in
            BFData repeat (trxninfo._requestRepeatId);
   
            //fill in the request update,
            t->getData (repeat, BF::HOST);
            //set the RunMode field to the trxn
            DSTCWorkSession::setRunMode (&repeat, iterList.getKey ().getActivity ());

            DString runMode (RUNMODE::UNCHANGED);
            try
            {
               runMode = repeat.getElementValue (ifds::RunMode);
            }
            catch (BFDataFieldNotFoundException)
            {
            }
            //check whether this is an 'Add' repeat, if yes, save it for later use
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
   return GETCURRENTHIGHESTSEVERITY ();
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCListTrxnBuilder.hpp-arc  $
//
//   Rev 1.11   Aug 16 2010 10:45:06   jankovii
//IN 2200497 - AFT System fee model setup error - configuration issue.
//
//   Rev 1.10   Jul 12 2010 15:00:42   jankovii
//IN 2182601 - QESI - PET165541 FN01 - Infomation complete field.
//
//   Rev 1.9   31 Oct 2008 16:18:18   popescu
//KYC/AML - joint accounts feature
//
//   Rev 1.8   Dec 10 2004 18:24:48   popescu
//PET 1117/06 Added key types as parameter
//
//   Rev 1.7   Dec 10 2004 15:28:48   popescu
//PET 1117/06 Added object activity as parameter
//
//   Rev 1.6   Nov 15 2004 14:49:14   popescu
//PET 1117/06, .NET synch changes
//
//   Rev 1.5   Nov 14 2004 14:32:48   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Jul 27 2004 15:25:48   VADEANUM
//PET1117 FN01 - Added constructor to pass a vector of fields for the fix part.
//
//   Rev 1.3   Feb 25 2004 15:36:46   popescu
//PTS 10027513, the delete updates should be going before add updates, in case a record has been deleted on Desktop and then re-added.  Back-end checks whether the newly added record is not duplicate. This assures that the record is deleted first and re-added.
//
//   Rev 1.2   Aug 07 2003 13:39:44   popescu
//the transaction key was in TRXINFO was set as reference to DString, changed it to a DString
//
//   Rev 1.1   Jul 26 2003 19:33:54   popescu
//changed the name of the iterator that walks the list
//
//   Rev 1.0   Jul 08 2003 13:39:02   popescu
//Initial revision.
 */