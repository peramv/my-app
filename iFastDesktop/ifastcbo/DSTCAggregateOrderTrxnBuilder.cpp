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
// ^FILE   : DSTCAggregateOrderTrxnBuilder.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : Dec 9, 2004
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAggregateOrderTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstctradestrxnbuilder.hpp"
#include "AggregatedOrder.hpp"
#include "AggregatedOrderlist.hpp"
#include "DSTCAggregateOrderTrxnBuilder.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0324_req.hpp>
#include <ifastdataimpl\dse_dstc0324_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AGGREGATED_ORDER_LIST_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCAggregateOrderTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId OmnibusID;
}


//******************************************************************************
void DSTCAggregateOrderTrxnBuilder::fillingData ( BFCBO* pObj, 
                                          BFData* data, 
                                          FieldPair fields[], 
                                          int numFields 
                                        ) 
{
   DString value;
   /*
   for (int i = 0; i < numFields; ++i)
   {
      pObj->getField (fields[i]._objFieldId, value, BF::HOST, false);
      data->setElementValue (fields[i]._viewFieldId, value, false, false);
   }*/
}

//******************************************************************************
SEVERITY DSTCAggregateOrderTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                   BFAbstractCBO* pBFCBO, 
                                                   HostTransactionContainer* pTrxnContainer, 
                                                   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   SEVERITY sevRtn = SEVERE_ERROR;

   AggregatedOrderList* pAggregatedOrderList = dynamic_cast<AggregatedOrderList*>(pBFCBO);
   if( pAggregatedOrderList == NULL )
      return(GETCURRENTHIGHESTSEVERITY());


   DString strTrack, 
      strPageName;

   pAggregatedOrderList->getTrackActivity (strTrack, strPageName);

   //walk through the Aggregated Order List
   //if no list do not go and get one from the database
   BFObjIter iterAggregatedOrderList(*pAggregatedOrderList, BF::HOST);
   while( !iterAggregatedOrderList.end() )
   {
      AggregatedOrder* pAggregatedOrder = dynamic_cast<AggregatedOrder*>(iterAggregatedOrderList.getObject());

      BF_OBJ_ACTIVITY ObjActivityAggregatedOrder = iterAggregatedOrderList.getKey().getActivity();

      if( pAggregatedOrder && pAggregatedOrder->hasTransactionUpdates())
      {
        
         DString dstOmnibusID;

         pAggregatedOrder->getField( ifds::OmnibusID, dstOmnibusID, BF::HOST, true );
         addIDITagValue(dstOmnibusID, TRXNTAG::TRANSNUMTAG, dstOmnibusID.stripLeading('0').strip());

         HostTransactionContainerIterator iterTrxnContainer( pTrxnContainer );//define an iterator on the HostTransactionContainer
         iterTrxnContainer.walkStrKey( dstOmnibusID );                  // look for the AggregatedOrder record in the HostTransactionContainer
         iterTrxnContainer.walkTrxnGroup( NO_GROUP );                //the trxn hasn't been handled yet, no group and sub type set,
         iterTrxnContainer.walkTrxnSubType( 0 );

         iterTrxnContainer.begin();


         BFData *request = new BFData( ifds::DSTC0324_REQ );
         BFData *response = new BFData( ifds::DSTC0324_VW );

         pAggregatedOrder->getData(*request, BF::HOST);

         request->setElementValue( ifds::Track, strTrack );
         request->setElementValue( ifds::Activity, strPageName );
         DSTCWorkSession::setRunMode(request, ObjActivityAggregatedOrder);

         DString mgmtCoId;
         workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
         request->setElementValue( ifds::CompanyId, mgmtCoId );

         DString dstrKeyTypes(NULL_STRING);
         //add the transaction to the container; the right side of the XchgData
         JData *jdata = new JData( DSTC_REQUEST::AGGREGATED_ORDER_LIST_UPDATE, request, response );
         pTrxnContainer->addTransaction( dstOmnibusID, jdata, 
                                         ObjActivityAggregatedOrder, NOT_PERSISTENT, dstrKeyTypes);

      }
      ++iterAggregatedOrderList;
   }  // while loop
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAggregateOrderTrxnBuilder.cpp-arc  $
// 
//    Rev 1.2   Jun 08 2006 14:57:06   ZHANGCEL
// Incident 638029 -- Fix the issue that only the last record can be  submit.
// 
//    Rev 1.1   Dec 09 2004 18:42:38   popescu
// PET 1117/56 fixed trxn builder issue
// 
//    Rev 1.0   Dec 09 2004 14:43:50   zhangcel
// Initial revision.
 
 */