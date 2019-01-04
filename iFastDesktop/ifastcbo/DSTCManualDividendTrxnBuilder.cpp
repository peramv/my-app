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
//    Copyright 2003 by IFDS, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCManualDividendTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCManualDividendTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCManualDividendTrxnBuilder.hpp"
#include "mfaccount.hpp"
#include "ManualDividend.hpp"
#include "ManualDividendList.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0115_req.hpp>
#include <ifastdataimpl\dse_dstc0115_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADES_LIST; // View 115
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCManualDividendTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
}

//******************************************************************************

SEVERITY DSTCManualDividendTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                   BFAbstractCBO* pBFCBO, 
                                                   HostTransactionContainer* pTrxnContainer, 
                                                   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   SEVERITY sevRtn = SEVERE_ERROR;

   ManualDividendList* pManualDividendList = dynamic_cast<ManualDividendList*>(pBFCBO);
   if( pManualDividendList == NULL )
      return(GETCURRENTHIGHESTSEVERITY());

   BFObjIter iterManualDividendList(*pManualDividendList, BF::HOST);
   while( !iterManualDividendList.end() )
   {
      ManualDividend* pManualDividend = dynamic_cast<ManualDividend*>(iterManualDividendList.getObject());

      BF_OBJ_ACTIVITY ObjActivityTrade = iterManualDividendList.getKey().getActivity();

      if( pManualDividend && 
          ( ObjActivityTrade == OBJ_ACTIVITY_ADDED   || 
            ObjActivityTrade == OBJ_ACTIVITY_DELETED || 
            pManualDividend->hasTransactionUpdates() ) 
        )
      {
         DString dstTrnKey;
         DString dstTransNum;

         pManualDividend->getField( ifds::TransNum, dstTransNum, BF::HOST, true );
         addIDITagValue(dstTrnKey, TRXNTAG::TRANSNUMTAG, dstTransNum.stripLeading('0').strip());

         HostTransactionContainerIterator iterTrxnContainer( pTrxnContainer );
         iterTrxnContainer.walkStrKey( dstTrnKey );
         iterTrxnContainer.walkTrxnGroup( NO_GROUP );
         iterTrxnContainer.walkTrxnSubType( 0 );

         iterTrxnContainer.begin();

         BFData *request = new BFData( ifds::DSTC0115_REQ );
         BFData *response = new BFData( ifds::DSTC0115_VW );

         pManualDividend->getData(*request, BF::HOST);

         DString dstrTrack, dstrActivity;
         pManualDividendList->getTrackActivity( dstrTrack, dstrActivity );
         request->setElementValue( ifds::Track, dstrTrack, false, false );
         request->setElementValue( ifds::Activity, dstrActivity, false, false );

         DSTCWorkSession::setRunMode( request, ObjActivityTrade );

         DString mgmtCoId;
         workSession.getMgmtCo().getField( ifds::CompanyId, mgmtCoId, BF::HOST );
         request->setElementValue( ifds::CompanyId, mgmtCoId );

         DString dstrKeyTypes( NULL_STRING );
         JData *jdata = new JData( DSTC_REQUEST::TRADES_LIST, request, response );
         pTrxnContainer->addTransaction(dstTrnKey, jdata, 
                                        ObjActivityTrade, NOT_PERSISTENT, dstrKeyTypes);

         request->setElementValue( ifds::RepeatCount, DString::asString( 0 ), false, false );
      }

      ++iterManualDividendList;
   }
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCManualDividendTrxnBuilder.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:32:50   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   May 22 2003 17:04:56   HERNANDO
// Initial revision.
 */