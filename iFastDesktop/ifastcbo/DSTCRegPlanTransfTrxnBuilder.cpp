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
// ^FILE   : DSTCRegPlanTransfTrxnBuilder.cpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : Nov 2016
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCRegPlanTransfTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "ifasthosttransactioncontainer.hpp"

#include "regplantransferlist.hpp"
#include "regplantransfer.hpp"
#include "regplantransferalloclist.hpp"
#include "regplantransferalloc.hpp"
#include "acbrecord.hpp"
#include "dstcregplantransftrxnbuilder.hpp"
#include "dstcworksession.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"

#include <ifastdataimpl\dse_dstc0474_req.hpp>
#include <ifastdataimpl\dse_dstc0474_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REG_PLAN_TRANSF_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCRegPlanTransfTrxnBuilder" );
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
   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
}

//******************************************************************************
void DSTCRegPlanTransfTrxnBuilder::buildTrxnKey ( DString& dstrKey, BFAbstractCBO *pObj) 
{
	DString dstrRegTransferMstrUUID;
	
	pObj->getField( ifds::RegTransferMstrUUID, dstrRegTransferMstrUUID, BF::HOST);
	addIDITagValue(dstrKey, I_("RegTransferMstrUUID"), dstrRegTransferMstrUUID);
}

//******************************************************************************
SEVERITY DSTCRegPlanTransfTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                BFAbstractCBO *pObj, 
                                                HostTransactionContainer *pTrCont, 
                                                BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);
   SEVERITY severity = SEVERE_ERROR;

   if (pMFaccount)
   {
      DString dstAccountNum, dstTrnKey, dstKeyTypes;

      pMFaccount->getField (ifds::AccountNum, dstAccountNum, BF::HOST, true);

      addIDITagValue (dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum);
      
      RegPlanTransferList* pRegPlanTransferList = NULL;

      severity = pMFaccount->getRegPlanTransferList( pRegPlanTransferList, BF::HOST, false );
      if ( severity <= WARNING && pRegPlanTransferList)
      {
         BFObjIter iterRegPlanTransferList( *pRegPlanTransferList, BF::HOST );

         while( !iterRegPlanTransferList.end() )
         {
            RegPlanTransfer* pRegPlanTransfer = dynamic_cast<RegPlanTransfer*>( iterRegPlanTransferList.getObject() );

            BF_OBJ_ACTIVITY listObjActivity = iterRegPlanTransferList.getKey().getActivity();

            if( pRegPlanTransfer != NULL && (listObjActivity == OBJ_ACTIVITY_ADDED || pRegPlanTransfer->hasTransactionUpdates( ) || listObjActivity == OBJ_ACTIVITY_DELETED ) )
            {
               DString strKey;
               //**  Data* req;
               BFData *request = new BFData( ifds::DSTC0474_REQ );
               BFData *response = new BFData( ifds::DSTC0474_VW );
               DString strTrack, strActivity;
               pRegPlanTransferList->getTrackActivity(strTrack,strActivity);                    
               request->setElementValue( ifds::Track, strTrack, false, false );
               request->setElementValue( ifds::Activity, strActivity, false, false );

               DString mgmtCoId;
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               request->setElementValue( ifds::CompanyId, mgmtCoId );

               DString dstrAmountTypeAlloc;
               pRegPlanTransfer->getField(ifds::AmountTypeAlloc, dstrAmountTypeAlloc, BF::HOST, false);

               int count = 0;

               DSTCRegPlanTransfTrxnBuilder::buildTrxnKey( strKey, pRegPlanTransfer);


               //define an iterator on the HostTransactionContainer
               HostTransactionContainerIterator iterTrxnContList( pTrCont );

               // get the key for this systematic
               // look for the systematic record in the HostTransactionContainer
               iterTrxnContList.walkStrKey( strKey );
               //the trxn hasn't been handled yet, no group and sub type set,
               iterTrxnContList.walkTrxnGroup( NO_GROUP );
               iterTrxnContList.walkTrxnSubType( 0 );
               iterTrxnContList.begin();


               pRegPlanTransfer->getData( *request, BF::HOST ); 
               request->setElementValue( ifds::AccountNum, dstAccountNum, false, false );

               if(listObjActivity == OBJ_ACTIVITY_ADDED)
                  request->setElementValue( ifds::RegTransferMstrUUID, I_("0"));

               DSTCWorkSession::setRunMode( request, listObjActivity );
               DString keyTypes;

               addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum );

               JData *jdata = new JData( DSTC_REQUEST::REG_PLAN_TRANSF_UPDATE, request, response );
               pTrCont->addTransaction( strKey, jdata, listObjActivity, NOT_PERSISTENT, keyTypes );

               // get allocation data
               RegPlanTransferAllocList* pAllocList = NULL;
               SEVERITY sevRtn1 = pRegPlanTransfer->getRegPlanTransferAllocList(BF::HOST, pAllocList );

               severity = std::max( severity, sevRtn1 );

               if( pAllocList != NULL && severity <= WARNING )  //if available allocation list
               {
                  DString dstrVer,dstrRid;

                  BFObjIter iteralloc( *pAllocList, BF::HOST );

                  int iAcctAllocNum = 0;
                  int nDeletedItems = 0;
                  iteralloc.begin();
                  while( !iteralloc.end() )
                  {
                     iAcctAllocNum++;
                     if( iteralloc.getKey().getActivity() == OBJ_ACTIVITY_DELETED ) 
                        ++nDeletedItems;
                     
                     ++iteralloc;
                  }

                  int nEffectedItems = iAcctAllocNum - nDeletedItems;

                  //check if there is any allocation attached to the allocation list
                  iteralloc.begin();
                  
                  while( !iteralloc.end())
                  {
                     BF_OBJ_ACTIVITY allocObjActivity = iteralloc.getKey().getActivity();
                     RegPlanTransferAlloc* pRegPlanTransferAlloc = dynamic_cast<RegPlanTransferAlloc*>( iteralloc.getObject() );

                     if(allocObjActivity== OBJ_ACTIVITY_ADDED || pRegPlanTransferAlloc->hasTransactionUpdates( ) || allocObjActivity == OBJ_ACTIVITY_DELETED)
                     {
                        DString dstrRegTransferAllocUUID;
                        pRegPlanTransferAlloc->getField( ifds::RegTransferAllocUUID, dstrRegTransferAllocUUID, BF::HOST, false );

                        //Let's ignore the 100% deleted Allocations
                        if( listObjActivity == OBJ_ACTIVITY_DELETED && dstrRegTransferAllocUUID == I_("0") )
                        {
                           ++iteralloc;
                           continue;
                        }

                        DString dstrAllocRunMode = iAcctAllocNum >1 && ( dstrRegTransferAllocUUID == I_("0") || dstrRegTransferAllocUUID == NULL_STRING)? 
                                 RUNMODE::ADDED : 
                                 DSTCWorkSession::getRunMode( iteralloc.getKey().getActivity(), pRegPlanTransferAlloc->hasTransactionUpdates( ) ); 

                        // if record is updated or if setAsDefault is turned on, sent transaction 
                        if( pRegPlanTransferAlloc != NULL )
                        {
                           BFData dataRepeat(ifds::DSTC0474_REQRepeat_Record);

                           dataRepeat.setElementValue( ifds::AllocRunMode, dstrAllocRunMode);
                           pRegPlanTransferAlloc->getData(dataRepeat, BF::HOST);

                           DString dstrAllocAmount;
                           if(dstrAmountTypeAlloc == I_("P"))
                           {
                              pRegPlanTransferAlloc->getField(ifds::Percentage, dstrAllocAmount, BF::HOST, false);
                              dataRepeat.setElementValue( ifds::AllocAmount, dstrAllocAmount);
                           }
                           else if(dstrAmountTypeAlloc == I_("D"))
                           {
                              pRegPlanTransferAlloc->getField(ifds::Amount, dstrAllocAmount, BF::HOST, false);
                              dataRepeat.setElementValue( ifds::AllocAmount, dstrAllocAmount);
                           }
                           request->addRepeat(dataRepeat);
                           ++ count; 
                        }
                     }                          
                     ++iteralloc;
                  } //while allocation list has more than one item    
                  unsigned long rptCount = request->getRepeatCount();
                  request->setElementValue( ifds::RepeatCount, DString::asString( rptCount ), false, false );

               }  // if available allocation list
            }  //pRegPlanTransfer has changes
            ++iterRegPlanTransferList;      
         } // more iterRegPlanTransferList
      } // pRegPlanTransferList exists
   }

   return GETCURRENTHIGHESTSEVERITY();
}

