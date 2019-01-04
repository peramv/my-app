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
//    Copyright 2002, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : DSTCSettlementTrxnBuilder.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : June 3,2002
//
// ^CLASS    : DSTCBrokerAMSTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCBrokerAMSTrxnBuilder.hpp"
#include "BrokerAMSList.hpp"
#include "BrokerAMS.hpp"
#include "BrokerAMSsearch.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0251_req.hpp>
#include <ifastdataimpl\dse_dstc0251_vw.hpp>
#include <ifastdataimpl\dse_dstc0251_reqrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_BROKER_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCBrokerAMSTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
//   extern CLASS_IMPORT const BFTextFieldId rxAMSCode;
}

int DSTCBrokerAMSTrxnBuilder::buildIndex = 0;
//******************************************************************************
void DSTCBrokerAMSTrxnBuilder::buildTrxnKey( DString& strKey, BrokerAMSsearch* pBrokerAMSsearch )
{
   DString dstrBrokerCode;

   if(pBrokerAMSsearch){
	   pBrokerAMSsearch->getField( ifds::BrokerCode, dstrBrokerCode, BF::HOST, true );
	   dstrBrokerCode.strip();
	   addIDITagValue( strKey, TRXNTAG::AMSCODETAG, dstrBrokerCode );
   }
   addIDITagValue( strKey, TRXNTAG::AMSBROKERTAG, DString::asString( buildIndex++ ) );
}

//******************************************************************************
SEVERITY DSTCBrokerAMSTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                       BFAbstractCBO* pObj,
                                                       HostTransactionContainer* pTrCont, 
                                                       BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   SEVERITY severity = SEVERE_ERROR;
   bool first_time = true;
   BrokerAMSsearch* pBrokerAMSsearch = dynamic_cast< BrokerAMSsearch* >(pObj);

   if( pBrokerAMSsearch == NULL )
		 return(GETCURRENTHIGHESTSEVERITY());

   DString tmp;
   BrokerAMSList *pBrokerAMSlist;
   BFData* pDataReq = NULL;
   BFData* pDataRes = NULL;
   unsigned long cRepeats = 0;
   
   DString keyString;
   DSTCBrokerAMSTrxnBuilder::buildTrxnKey( keyString, pBrokerAMSsearch );

   severity = pBrokerAMSsearch->getBrokerAMSList( pBrokerAMSlist, BF::HOST, false, false );
   if( (pBrokerAMSlist != NULL) && (severity <= WARNING ) && pBrokerAMSlist->hasTransactionUpdates( ) )
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
		   pDataReq   = new BFData( ifds::DSTC0251_REQ );
		   pDataRes   = new BFData( ifds::DSTC0251_VW );

		   pBrokerAMSsearch->getField( ifds::BrokerCode, tmp, BF::HOST, true );
		   pDataReq->setElementValue( ifds::BrokerCode, tmp );

		   pDataReq->setElementValue( ifds::Track, I_("N") );
		   pDataReq->setElementValue( ifds::Activity, I_("") );

		   DString mgmtCoId;
		   workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
		   pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

		   DString dstrKeyTypes(NULL_STRING);
		   //add the transaction to the container;
		   JData *jdata = new JData( DSTC_REQUEST::AMS_BROKER_UPDATE, pDataReq, pDataRes );
		   pTrCont->addTransaction( keyString, jdata, objActivity, NOT_PERSISTENT, dstrKeyTypes );
	   }
	   else
	   {
		   pDataReq = (*iterTrxnContList)->getRequestDataObject();
	   }

	   //walk through BrokerAMSList
       BFObjIter bfIter( *pBrokerAMSlist, BF::HOST );
	   bfIter.begin();
       while( !bfIter.end() )
       {
          BrokerAMS* pBrokerAMS = dynamic_cast< BrokerAMS* >( bfIter.getObject() );
          BF_OBJ_ACTIVITY lObjActivity = bfIter.getKey().getActivity();	

		  if( bfIter.hasTransactionUpdates(false)  )
		  {			   
               //create a repeat for the request and filled in
               BFData repeat( ifds::DSTC0251_REQRepeat_Record );
               //fill in the request update, only the part for which the BrokerAMS is responsible
               pBrokerAMS->getData( repeat, BF::HOST );

               //set the RunMode field to the EntityUpdate trxn
               DSTCWorkSession::setRunMode( &repeat, lObjActivity );
               //add the repeat to the retrieved request
               pDataReq->addRepeat( repeat );
               //cRepeats = pDataReq->getRepeatCount();
               //pDataReq->setElementValue( ifds::RepeatCount, DString::asString( cRepeats ), false, false );
			   cRepeats ++;
          }
		  ++bfIter;		  
       }//end while
	   if(cRepeats > 0)
			pDataReq->setElementValue( ifds::RepeatCount, DString::asString( cRepeats ), false, false );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCBrokerAMSTrxnBuilder.cpp-arc  $
// 
//    Rev 1.4   Nov 14 2004 14:31:46   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Mar 21 2003 18:04:38   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Mar 14 2003 15:34:02   FENGYONG
// fix
// 
//    Rev 1.1   Mar 07 2003 16:46:04   FENGYONG
// groupid fix
// 
//    Rev 1.0   Mar 03 2003 16:34:04   FENGYONG
// Initial revision.
* 
*/