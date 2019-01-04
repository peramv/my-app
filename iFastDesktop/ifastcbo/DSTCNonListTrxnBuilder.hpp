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
// ^FILE   : DSTCNonListTrxnBuilder.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Aug, 2014
//
// ^CLASS    : DSTCNonListTrxnBuilder..Template calss for the Transcation Builder
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
      const BFDataId &viewId) :
   _trxnKey (trxnKey),
   _dstcRequest (dstcRequest),
   _requestId (requestId),
   _viewId (viewId)
   {};
   _trxnInfo (
      const DString &trxnKey,
      const DSTCRequest &dstcRequest,
      const BFDataId &requestId, 
      const BFDataId &viewId,
	  const std::vector<BFFieldId> &fields) :
   _trxnKey (trxnKey),
   _dstcRequest (dstcRequest),
   _requestId (requestId),
   _viewId (viewId),
	_fields (fields)
   {};
   const DString _trxnKey;
   const DSTCRequest &_dstcRequest;
   const BFDataId &_requestId;
   const BFDataId &_viewId;
   const std::vector<BFFieldId> _fields;

} TRXNINFO;

template <class T>
   class DSTCNonListTrxnBuilder
   {
   public:
      DSTCNonListTrxnBuilder () {};
      virtual ~DSTCNonListTrxnBuilder () {};
      SEVERITY buildTransactions ( DSTCWorkSession &workSession,
                                   HostTransactionContainer *pTrCont, 
                                   BFCBO *pObj, 
                                   const TRXNINFO &trxninfo,
                                   const DString &dstrTag = NULL_STRING, //pass in the tag in  case of list of updates and the update happens in a non-repeat view for the list
                                   BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE,                                   
                                   const DString &dstrKeyTypes = NULL_STRING,
                                   TRXN_TYPE TxnType =  NOT_PERSISTENT,
                                   bool binclSubObj = true,
                                   bool bIsDefaultFields = true  );
   private:
   };

const BFFieldId fieldDefaults[] = {
 ifds::Track,
 ifds::Activity,
 ifds::CompanyId,
 ifds::Track, 
 ifds::SessionId,
 ifds::User_Id,
 ifds::LanguageCode,
};
static const int NUM_DEFAULT_FIELDS = sizeof( fieldDefaults ) / sizeof( BFFieldId );

//******************************************************************************
template <class T>
SEVERITY DSTCNonListTrxnBuilder<T>::buildTransactions ( DSTCWorkSession &workSession,
                                                        HostTransactionContainer *pTrCont, 
                                                        BFCBO *pObj, 
                                                        const TRXNINFO &trxninfo,
                                                        const DString &dstrTag ,/* NULL_STRING */
                                                        BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/,
                                                        const DString &dstrKeyTypes /*=NULL_STRING*/,
                                                        TRXN_TYPE TxnType,/*NOT_PERSISTENT*/
                                                        bool binclSubObj,/*true*/
                                                        bool bIsDefaultFields /*true*/
                                                        ) 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("buildTransactions"));

   DString _dstrTrxnKey (trxninfo._trxnKey);
   DString _dstrNewTrxnKey = NULL_STRING;
   DString _dstrtag( dstrTag );
   HostTransactionContainerIterator iterTrxnContList (pTrCont);
   //set filter to look for the update fixed area
   addIDITagValue( _dstrNewTrxnKey, _dstrTrxnKey, _dstrtag.stripAll() );
   iterTrxnContList.walkStrKey (_dstrNewTrxnKey);
   iterTrxnContList.walkTrxnGroup (NO_GROUP);
   iterTrxnContList.walkTrxnSubType (0);
   T t = dynamic_cast<T> ( pObj );
   bool bUpdated = false;
   bUpdated = t->hasTransactionUpdates(binclSubObj);
   if ( t && bUpdated)
   {
        BFData *pDataReq = NULL;
        BFData *pDataRes = NULL;       
        iterTrxnContList.begin ();
        //fill in the fixed area, 
        //didn't find the request in the trxn container
        if (iterTrxnContList.end ())
        {
            DString strTrack, strActivity, mgmtCoId;
            //populate the fixed session
            pDataReq = new BFData (trxninfo._requestId);
            pDataRes = new BFData (trxninfo._viewId);
            pObj->getData(*pDataReq, BF::HOST);
            assert( pDataReq );
            if(!pDataReq)
               return GETCURRENTHIGHESTSEVERITY ();   
            pObj->getTrackActivity (strTrack, strActivity);
            pDataReq->setElementValue (ifds::Track, strTrack, false, false);
            pDataReq->setElementValue (ifds::Activity, strActivity, false, false);
            //continue to fill in the request update, 
            workSession.getMgmtCo ().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
            pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);  
            JData *jdata = new JData (trxninfo._dstcRequest, pDataReq, pDataRes);
            pTrCont->addTransaction ( _dstrNewTrxnKey,
                                      jdata, 
                                      objActivity, 
                                      TxnType, 
                                      dstrKeyTypes);
            if( bIsDefaultFields )
            {
               unsigned long cNumFields = pDataReq->getFieldCount();
               for( unsigned long indexField = 0;  indexField < cNumFields;  ++indexField )
               {
                  const BFDataField& pDF = pDataReq->getElementByIndex( indexField );
                  const BFFieldId& idField = pDF.getId();
                  bool isInDefault = false;
                  for( unsigned int defaultField =0 ; defaultField < NUM_DEFAULT_FIELDS ; ++defaultField)
                  {                     
                     if( idField.getId() ==  fieldDefaults[defaultField].getId() )
                     { 
                        isInDefault = true;
                        break;
                     }
                  }
                  if(!isInDefault)
                  {
                     DString value;
	                 pObj->getField (idField , value, BF::HOST); 
                     pDataReq->setElementValue (idField , value); 
                  }
               }
            }
            else // a specific field vector is passed to the template..use this...
            {
                for (unsigned int i = 0; i < trxninfo._fields.size(); i++)
                {
	                DString value;
	                pObj->getField (trxninfo._fields[i], value, BF::HOST);
	                pDataReq->setElementValue (trxninfo._fields[i], value);
					
                }
            }
         }
         else
         {
            pDataReq = (*iterTrxnContList)->getRequestDataObject ();					
         }
    }
   return GETCURRENTHIGHESTSEVERITY ();
};


///******************************************************************************
//              Revision Control Entries
///******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCNonListTrxnBuilder.hpp-arc  $*/