//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2012 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : DSTCACBTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : Sept 2012
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCACBTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "ifasthosttransactioncontainer.hpp"

#include "acblist.hpp"
#include "acbrecord.hpp"
#include "dstcacbtrxnbuilder.hpp"
#include "dstcworksession.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"

#include <ifastdataimpl\dse_dstc0447_req.hpp>
#include <ifastdataimpl\dse_dstc0447_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACB_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCACBTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId IsNewOrUpdate;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFDateFieldId ACBPlugDate;
}

//******************************************************************************
void DSTCACBTrxnBuilder::buildTrxnKey ( DString& dstrKey, BFAbstractCBO *pObj) 
{

}

//******************************************************************************
SEVERITY DSTCACBTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                BFAbstractCBO *pObj, 
                                                HostTransactionContainer *pTrCont, 
                                                BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);

   if (pMFaccount)
   {
      DString dstAccountNum, 
         dstTrnKey, 
         dstKeyTypes;

      pMFaccount->getField (ifds::AccountNum, dstAccountNum, BF::HOST, true);

      addIDITagValue (dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum);

      ACBList *pACBList = NULL;
      unsigned int iNumOfEmbededACBList = pMFaccount->getNumOfEmbededACBList(BF::HOST);
      for( unsigned int i = 0; i < iNumOfEmbededACBList; i++)
      {
         DString acbFund,acbClass;
         if(pMFaccount->getEmbededACBListBySeq(i, pACBList, BF::HOST, acbFund, acbClass) && 
            pACBList && !acbFund.strip().upperCase().empty() && !acbClass.strip().upperCase().empty() &&
            (pACBList->isUpdated(true) || pACBList->hasTransactionUpdates(true)))
         {
            if (pMFaccount->getACBList(pACBList, BF::HOST, acbFund, acbClass, false ) <= WARNING && 
                pACBList)
            {
               bool bIsChildUpdate = pACBList->isUpdated(true) || 
                                     pACBList->hasTransactionUpdates(true);

               BFObjIter iterACBList (*pACBList, BF::HOST);

               DString dstAccountNum, dstTrnKey, dstKeyTypes;
               pMFaccount->getField( ifds::AccountNum, dstAccountNum, BF::HOST, true );
               addIDITagValue( dstTrnKey, I_("ACBPlug"), dstAccountNum.stripLeading('0').strip() );
               addIDITagValue( dstTrnKey, I_("Fund"), acbFund.strip().upperCase() );
               addIDITagValue( dstTrnKey, I_("Class"), acbClass.strip().upperCase() );
               addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum );

               HostTransactionContainerIterator iterTrxnContList( pTrCont );

               iterTrxnContList.walkStrKey( dstTrnKey );
               iterTrxnContList.walkTrxnGroup( NO_GROUP );
               iterTrxnContList.walkTrxnSubType( 0 );
               
               BFData *pDataReq = NULL;
               BFData *pDataRes = NULL;
               
               iterACBList.begin();
               
               if (!iterACBList.end())
               {
                  iterTrxnContList.begin();

                  if( iterTrxnContList.end() )
                  {
                     pDataReq = new BFData( ifds::DSTC0447_REQ );
                     pDataRes = new BFData( ifds::DSTC0447_VW );

                     DString strTrack, strActivity;

                     pACBList->getTrackActivity(strTrack, strActivity);
                     pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                     pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                     DString mgmtCoId, acbPlugAmt;
                     workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

                     pACBList->getField (ifds::ACBPlugAmt, acbPlugAmt, BF::HOST, false);
                     pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);
                     pDataReq->setElementValue (ifds::AccountNum, dstAccountNum);
                     pDataReq->setElementValue (ifds::rxFundCode, acbFund.strip().upperCase());
                     pDataReq->setElementValue (ifds::rxClassCode, acbClass.strip().upperCase());
                     pDataReq->setElementValue (ifds::ACBPlugAmt, acbPlugAmt);

                     JData *jdata = new JData( DSTC_REQUEST::ACB_UPDATE, pDataReq, pDataRes );
                     pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
                  }
                  else
                  {
                     pDataRes = (*iterTrxnContList)->getRequestDataObject();
                  }
               }
               else
               {
                  // only ACB plug date has valid date, then allow calling to view 447 when
                  // there is no ACB record before
                  DString mgmtCoId, acbPlugAmt, acbPlugDate;
                  pACBList->getField (ifds::ACBPlugDate, acbPlugDate, BF::HOST, false);
                  
                  acbPlugDate.strip().upperCase();
                  if( !acbPlugDate.empty() )
                  {
                     pDataReq = new BFData( ifds::DSTC0447_REQ );
                     pDataRes = new BFData( ifds::DSTC0447_VW );

                     DString strTrack, strActivity;

                     pACBList->getTrackActivity(strTrack, strActivity);
                     pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                     pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                     workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

                     pACBList->getField (ifds::ACBPlugAmt, acbPlugAmt, BF::HOST, false);
                     pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);
                     pDataReq->setElementValue (ifds::AccountNum, dstAccountNum);
                     pDataReq->setElementValue (ifds::rxFundCode, acbFund.strip().upperCase());
                     pDataReq->setElementValue (ifds::rxClassCode, acbClass.strip().upperCase());
                     pDataReq->setElementValue (ifds::ACBPlugAmt, acbPlugAmt);

                     JData *jdata = new JData( DSTC_REQUEST::ACB_UPDATE, pDataReq, pDataRes );
                     pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
                  }
               }
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCACBTrxnBuilder.cpp-arc  $
// 