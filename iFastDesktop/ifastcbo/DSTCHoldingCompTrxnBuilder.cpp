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
//    Copyright 2005, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : DSTCHoldingCompTrxnBuilder.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : March 6, 2005
//
// ^CLASS    : DSTCHoldingCompTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCHoldingCompTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0331_req.hpp>
#include <ifastdataimpl\dse_dstc0331_vw.hpp>
#include <ifastdataimpl\dse_dstc0331_reqrepeat_record.hpp>
#include "holdingcomp.hpp"
#include "holdingcomplist.hpp"
#include "Entity.hpp"



namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest WHEREUSE_LIST_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCHoldingCompTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
//   extern CLASS_IMPORT const BFTextFieldId rxCompCode;
//   extern CLASS_IMPORT const BFNumericFieldId Settled;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ENTITYID;
}


//******************************************************************************
void DSTCHoldingCompTrxnBuilder::buildTrxnKey( DString& strKey, Entity* pEntity )
{
   addIDITagValue( strKey, TRXNTAG::WHEREUSEDTAG, TRXNTAG::WHEREUSEDTAG );
   DString entityId;
   pEntity->getEntityId( entityId );
   entityId.stripLeading( '0' );
   entityId.strip();
   addIDITagValue( strKey, TRXNTAG::ENTITYIDTAG, entityId );
}
//******************************************************************************

/*
SEVERITY DSTCHoldingCompTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                       BFAbstractCBO* pObj,
                                                       HostTransactionContainer* pTrCont, 
                                                       BF_OBJ_ACTIVITY objActivity // OBJ_ACTIVITY_NONE
                                                       )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

	SEVERITY severity = SEVERE_ERROR;

   HoldingCompList* pHoldingCompList = NULL;
   workSession.getHoldingCompList(pHoldingCompList, BF::HOST, I_(""),  I_(""), I_(""), I_(""), false);

	//DString entityId;
	//entity->getEntityId( entityId );
	//entityId.stripLeading( '0' );
	//entityId.strip();

	if(pHoldingCompList != NULL )
	{
      BFObjIter iterHoldingComp( *pHoldingCompList, BF::HOST, true );
   
      while(!iterHoldingComp.end())
      {

         HoldingComp* pHoldingComp = dynamic_cast<HoldingComp*>(iterHoldingComp.getObject());

         BFData* request = new BFData( ifds::DSTC0331_REQ );
         
         BFData dataRepeat (ifds::DSTC0331_REQRepeat_Record);         

         BFData* response = new BFData( ifds::DSTC0331_VW );
         DString strTrack;
         DString strActivity;
         pHoldingComp->getTrackActivity(strTrack, strActivity);;

         request->setElementValue( ifds::Track, strTrack, false, false );
         request->setElementValue( ifds::Activity, strActivity, false, false );

         pHoldingComp->getData( dataRepeat, BF::HOST );

         const BFObjectKey& iterKey = iterHoldingComp.getKey();
         
         DSTCWorkSession::setRunMode( &dataRepeat, iterKey.getActivity() );

         request->addRepeat(dataRepeat);
		   request->setElementValue( ifds::RepeatCount, I_("1"), false, false );

         //std::vector<BFFieldId> holdingCompFields;

		   //holdingCompFields.push_back(ifds::WhereUse);
		   //holdingCompFields.push_back(ifds::WhereUseCode);
		   //holdingCompFields.push_back(ifds::EntityType);
		   //holdingCompFields.push_back(ifds::RecId);
		   //holdingCompFields.push_back(ifds::Version);
		   //holdingCompFields.push_back(ifds::EffectiveDate);
		   //holdingCompFields.push_back(ifds::StopDate);
		   //holdingCompFields.push_back(ifds::HoldingCompName);
		   //holdingCompFields.push_back(ifds::CompUsage);
		   //holdingCompFields.push_back(ifds::AggregationMethod);
		   //holdingCompFields.push_back(ifds::LangCode);


         DString strKey = I_("HoldingCompList");
         DString entityId;
         pHoldingComp->getField(ifds::EntityId, entityId, BF::HOST, false);
         entityId.stripLeading( '0' );
         entityId.strip();
         strKey += entityId;
//         addIDITagValue( strKey, TRXNTAG::ENTITYIDTAG, entityId );

         DString keyTypes;   
			addIDITagValue( keyTypes, KEYTYPES::ENTITYID, entityId );

         DString mgmtCoId;
         workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
         request->setElementValue(ifds::CompanyId, mgmtCoId);

         JData *jdata = new JData( DSTC_REQUEST::WHEREUSE_LIST_UPDATE, request, response );
         pTrCont->addTransaction( strKey, jdata, objActivity, NOT_PERSISTENT, keyTypes );

      
         ++iterHoldingComp;
      }

	}
	
  return(GETCURRENTHIGHESTSEVERITY());
}
*/


SEVERITY DSTCHoldingCompTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                       BFAbstractCBO* pObj,
                                                       HostTransactionContainer* pTrCont, 
                                                       BF_OBJ_ACTIVITY objActivity // OBJ_ACTIVITY_NONE
                                                      )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

	SEVERITY severity = SEVERE_ERROR;

   HoldingCompList* pHoldingCompList = NULL;
   workSession.getHoldingCompList(pHoldingCompList, BF::HOST, I_(""),  I_(""), I_(""), I_(""), false);

	//DString entityId;
	//entity->getEntityId( entityId );
	//entityId.stripLeading( '0' );
	//entityId.strip();

	if(pHoldingCompList != NULL )
	{
		DString keyTypes;   
		//addIDITagValue( keyTypes, KEYTYPES::ENTITYID, entityId );

		DSTCListTrxnBuilder<HoldingComp*> HoldingCompListTrxnBuilder;
		DString key = I_("HoldingCompList");// + entityId;

      std::vector<BFFieldId> holdingCompFields;

		holdingCompFields.push_back(ifds::WhereUse);
		holdingCompFields.push_back(ifds::WhereUseCode);
		holdingCompFields.push_back(ifds::EntityType);
		holdingCompFields.push_back(ifds::RecId);
		holdingCompFields.push_back(ifds::Version);
		holdingCompFields.push_back(ifds::EffectiveDate);
		holdingCompFields.push_back(ifds::StopDate);
		holdingCompFields.push_back(ifds::HoldingCompName);
		holdingCompFields.push_back(ifds::CompUsage);
		holdingCompFields.push_back(ifds::AggregationMethod);
		holdingCompFields.push_back(ifds::LangCode);


		TRXNINFO HoldingCompTrxnInfo(key,
				DSTC_REQUEST::WHEREUSE_LIST_UPDATE,
				ifds::DSTC0331_REQ,
				ifds::DSTC0331_REQRepeat_Record,
				ifds::DSTC0331_VW,
            holdingCompFields);





		HoldingCompListTrxnBuilder.buildTransactions(workSession, 
		 											pTrCont, 
													pHoldingCompList, 
  													HoldingCompTrxnInfo,
													objActivity,
													keyTypes ); 
	}
	
  return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCHoldingCompTrxnBuilder.cpp-arc  $
// 
//    Rev 1.4   Dec 02 2005 09:18:08   jankovii
// Incident #468333 - it was not possible to add 2 entites in All entites where use option.
// 
//    Rev 1.3   Nov 30 2005 09:34:52   popescu
// Incindent# 463650 - a dummy where used record was erroneous sent to back-end
// 
//    Rev 1.2   Nov 08 2005 16:18:50   jankovii
// PET1228 - replaced existing code with DSTCListTrxnBuilder support.
// 
//    Rev 1.1   May 03 2005 14:52:44   yingbaol
// Incident302278, desktop should not send dummy record to back end
// 
//    Rev 1.0   Mar 06 2005 15:37:30   yingbaol
// Initial revision.
//


* 
*/