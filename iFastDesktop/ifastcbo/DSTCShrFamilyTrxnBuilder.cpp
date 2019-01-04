//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use orsuch information
//    may result in civil liabilities. disclosure of 
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCShrFamilyTrxnBuilder.cpp
// ^AUTHOR : Claudio Sanchez
// ^DATE   : January 10, 2003
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCSHAREHOLDERREMARKSTRXNBUILDER
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcshrfamilytrxnbuilder.hpp"

#include "shrfamily.hpp"
#include "shrfamilylist.hpp"
#include "shareholder.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0234_req.hpp>
#include <ifastdataimpl\dse_dstc0234_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0234_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SHR_FAMILY_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME         = I_( "DSTCShhrFamilyTrxnBuilder" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const SHRNUM;
}

//******************************************************************************
SEVERITY DSTCShhrFamilyTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   Shareholder* pShareholder = dynamic_cast<Shareholder*>(pObj);

   ShrFamilyList  *pFamilyList   = NULL;


   if( pShareholder != NULL )
   {
      // Enter here with a valid shareholder pointer and get shareholder field
      DString dstShrNum, dstTrnKey, dstKeyTypes;
      pShareholder->getField( ifds::ShrNum, dstShrNum, BF::HOST, true );
      addIDITagValue( dstTrnKey,   TRXNTAG::SHRFAMILYTAG, dstShrNum.stripLeading('0').strip() );
      addIDITagValue( dstKeyTypes, KEYTYPES::SHRNUM, dstShrNum );

      HostTransactionContainerIterator iterTrxnContList( pTrCont );

      //set filter to look for Entity fixed area
      iterTrxnContList.walkStrKey( dstTrnKey );
      iterTrxnContList.walkTrxnGroup( NO_GROUP );
      iterTrxnContList.walkTrxnSubType( 0 );

      if (pShareholder->getShrFamilyList(pFamilyList, BF::HOST, false) <= WARNING && pFamilyList)
      {
         BFData *pDataReq = NULL;
         BFData *pDataRes = NULL;

         //define an iterator on the remarksList
         BFObjIter iter( *pFamilyList, BF::HOST );
         ShrFamily* pFamily = NULL;

         iter.begin();
         while( !iter.end() )
         {
      
            //in case of a list the obj_activity is known only by the list,
            //so ask the key about it
            pFamily = dynamic_cast<ShrFamily*>( iter.getObject() );

            if( iter.hasTransactionUpdates() )
            {
               iterTrxnContList.begin();

               //fill in the fixed area
               if( iterTrxnContList.end() )
               {
                  pDataReq = new BFData( ifds::DSTC0234_REQ );
                  pDataRes = new BFData( ifds::DSTC0234_VW );

                  DString strTrack, strActivity;

                  pFamilyList->getTrackActivity(strTrack,strActivity);         
                  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                  //fill in the request update, only the part for which the Remarks is responsible
                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
                  pDataReq->setElementValue( ifds::ShrNum, dstShrNum );

                  JData *jdata = new JData( DSTC_REQUEST::SHR_FAMILY_UPDATE, pDataReq, pDataRes );
                  pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
               }
               else
                  pDataReq = (*iterTrxnContList)->getRequestDataObject();


               //create a repeat for the request and filled it in
               BFData repeat( ifds::DSTC0234_REQRepeat_Record);
               

               //fill in the request update, only the part for which the Remarks is responsible
               pFamily->getData( repeat, BF::HOST );

               //set the RunMode field to the ShareholderRemarksUpdate trxn
               DSTCWorkSession::setRunMode( &repeat, iter.getKey().getActivity() );

               //add the lDataRepeat to the request
               pDataReq->addRepeat( repeat );
               DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
               pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );
            }
            //move to the next remark
            ++iter;
         } //meaning we have at least one remark
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCShrFamilyTrxnBuilder.cpp-arc  $
// 
//    Rev 1.7   Nov 14 2004 14:33:40   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Mar 21 2003 18:07:02   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Jan 20 2003 14:02:26   popescu
// change the assignement of the request pointer when the trxn is found in the container
// 
//    Rev 1.4   Jan 15 2003 12:39:36   sanchez
// changed:
// #include <ifastdataimpl\dse_dstc0234_vew.hpp>
// to:
// #include <ifastdataimpl\dse_dstc0234_vw.hpp>
// 
// Uncomment line:
// pDataRes = new BFData( ifds::DSTC0234_VW )
// 
//    Rev 1.3   Jan 14 2003 17:38:18   sanchez
// Change for data request
// added
// Revision Control Entries
 */