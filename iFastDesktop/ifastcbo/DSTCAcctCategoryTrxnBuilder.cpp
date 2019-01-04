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
// ^AUTHOR : Robert Kovacs
// ^DATE   : January 21, 2003
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCShrFamilyTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcacctcategorytrxnbuilder.hpp"

#include "acctcategory.hpp"
#include "acctcategorylist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0246_req.hpp>
#include <ifastdataimpl\dse_dstc0246_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0246_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_CATEGORY_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME         = I_( "DSTCAcctCategoryTrxnBuilder" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
SEVERITY DSTCAcctCategoryTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);

   AcctCategoryList  *pAcctCategoryList  = NULL;


   if( pMFaccount )
   {
      DString dstAccountNum, dstTrnKey, dstKeyTypes;
      pMFaccount->getField( ifds::AccountNum, dstAccountNum, BF::HOST, true );
      addIDITagValue( dstTrnKey,   TRXNTAG::ACCTCATEGORYTAG, dstAccountNum.stripLeading('0').strip() );
      addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum );

      HostTransactionContainerIterator iterTrxnContList( pTrCont );

      iterTrxnContList.walkStrKey( dstTrnKey );
      iterTrxnContList.walkTrxnGroup( NO_GROUP );
      iterTrxnContList.walkTrxnSubType( 0 );

      if (pMFaccount->getAcctCategoryList(pAcctCategoryList, BF::HOST, false) <= WARNING && pAcctCategoryList)
      {
         BFData *pDataReq = NULL;
         BFData *pDataRes = NULL;

         BFObjIter iter( *pAcctCategoryList, BF::HOST );
         AcctCategory* pAcctCategory = NULL;

         iter.begin();
         while( !iter.end() )
         {
            pAcctCategory = dynamic_cast<AcctCategory*>( iter.getObject() );

            if( iter.hasTransactionUpdates() )
            {
               iterTrxnContList.begin();

               //fill in the fixed area
               if( iterTrxnContList.end() )
               {
                  pDataReq = new BFData( ifds::DSTC0246_REQ );
                  pDataRes = new BFData( ifds::DSTC0246_VW );

                  DString strTrack, strActivity;

                  pAcctCategoryList->getTrackActivity(strTrack,strActivity);         
                  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                  //fill in the request update
                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
                  pDataReq->setElementValue( ifds::AccountNum, dstAccountNum );

                  JData *jdata = new JData( DSTC_REQUEST::ACCT_CATEGORY_UPDATE, pDataReq, pDataRes );
                  pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
               }
               else
                  pDataRes = (*iterTrxnContList)->getRequestDataObject();


               //create a repeat for the request and fill it in
               BFData repeat( ifds::DSTC0246_REQRepeat_Record);
               
               //fill in the request update
               pAcctCategory->getData( repeat, BF::HOST );

               //set the RunMode field 
               DSTCWorkSession::setRunMode( &repeat, iter.getKey().getActivity() );

               //add the lDataRepeat to the request
               pDataReq->addRepeat( repeat );
               DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
               pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );
            }
            //move to the next AcctCategory
            ++iter;
         } //meaning we have at least one AcctCategory
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctCategoryTrxnBuilder.cpp-arc  $
// 
//    Rev 1.4   01 May 2007 13:55:34   popescu
// Incident: ? (got raised by Lux - C.Rigot) account# is invalid for acct cut off times trxn sent, and acct category
// 
//    Rev 1.3   Nov 14 2004 14:31:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Apr 04 2003 13:56:56   YINGBAOL
// fix Transtype
// 
//    Rev 1.1   Mar 21 2003 18:03:38   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.0   Jan 21 2003 14:26:26   KOVACSRO
// Initial revision.

 */