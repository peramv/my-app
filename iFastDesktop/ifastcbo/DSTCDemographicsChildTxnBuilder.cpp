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
//    Copyright 2014 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : DSTCDemographicsChildTxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCDemographicsChildTxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "dstcdemographicschildtxnbuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "demographics.hpp"
#include "demographicschild.hpp"
#include "demographicschildlist.hpp"
#include "entity.hpp"
#include "mfaccount.hpp"

#include <ifastdataimpl\dse_dstc0466_req.hpp>
#include <ifastdataimpl\dse_dstc0466_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0466_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DEMOGRAPHICS_CHILD_LIST_UPDATE; 
}

namespace
{
   const I_CHAR* CLASSNAME          = I_("DSTCDemographicsChildTxnBuilder");
   const I_CHAR* BUILDTRANSACTIONS  = I_("buildTransactions");
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
   extern CLASS_IMPORT I_CHAR * const ENTITYID;
}

//******************************************************************************
SEVERITY DSTCDemographicsChildTxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                             BFAbstractCBO *pObj, 
                                                             HostTransactionContainer *pTrCont, 
                                                             BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   DemographicsChildList *pDemographicsChildList = NULL;
   Demographics *pDemographics = dynamic_cast<Demographics*>(pObj);
   MFAccount *pMFAccount = dynamic_cast<MFAccount*>(pObj->getParent());
   Entity *pEntity = dynamic_cast<Entity*>(pObj->getParent());

   if (pDemographics)
   {
      DString strAccountNum = I_("0"),strEntityId = I_("0");
      if (pMFAccount && !pEntity)
      {
         pMFAccount->getField (ifds::AccountNum, strAccountNum, BF::HOST,false);
         strAccountNum.strip().upperCase();
      }
      else if (!pMFAccount && pEntity)
      {
         pEntity->getField (ifds::EntityId, strEntityId, BF::HOST,false);
         strEntityId.strip().upperCase();
      }

      pDemographics->getDemographicsChildList(pDemographicsChildList,BF::HOST);

      if( NULL != pDemographicsChildList && pDemographicsChildList->hasTransactionUpdates( ))
      {
         BFData* request = new BFData( ifds::DSTC0466_REQ );
         BFData* response = new BFData( ifds::DSTC0466_VW );
         DString strTrack, strAvtivity, strKey, keyTypes;
         pDemographicsChildList->getTrackActivity(strTrack,strAvtivity);;

         request->setElementValue( ifds::Track, strTrack, false, false );
         request->setElementValue( ifds::Activity, strAvtivity, false, false );

         pDemographicsChildList->getData( *request, BF::HOST );

         addIDITagValue( strKey, 
                         TRXNTAG::DEMOGRAPHICS_CHILD_TAG, 
                         (pMFAccount != NULL)? strAccountNum:strEntityId);

         DString mgmtCoId;
         workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
         request->setElementValue( ifds::CompanyId, mgmtCoId );

         request->setElementValue( ifds::AccountNum, strAccountNum, false, false );
         request->setElementValue( ifds::EntityId, strEntityId, false, false );

         if (pMFAccount != NULL)
         {
            addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, strAccountNum );
         }
         else
         {
            addIDITagValue( keyTypes, KEYTYPES::ENTITYID, strEntityId );
         }

         JData *jdata = new JData( DSTC_REQUEST::DEMOGRAPHICS_CHILD_LIST_UPDATE, request, response );
         pTrCont->addTransaction( strKey, jdata, objActivity, NOT_PERSISTENT, keyTypes );

         BFObjIter iterDemographicsChildList (*pDemographicsChildList, BF::HOST);

         iterDemographicsChildList.begin ();
         while (!iterDemographicsChildList.end ())
         {
            DemographicsChild *pDemographicsChild = dynamic_cast<DemographicsChild*> (iterDemographicsChildList.getObject ());

            BFData repeat (ifds::DSTC0466_REQRepeat_Record);

            //fill in the request update,
            pDemographicsChild->getData (repeat, BF::HOST);
            request->addRepeat (repeat);

            ++iterDemographicsChildList;
         }

         DString dstRepeats = DString::asString (request->getRepeatCount ());
         request->setElementValue (ifds::RepeatCount, dstRepeats);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
//              Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCDemographicsChildTxnBuilder.cpp-arc  $
// 
