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
//    Copyright 2001 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCAcctSplitCommTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : Aug 29, 2001
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAcctSplitCommTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  : 
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "acctsplitcomm.hpp"
#include "acctsplitcommlist.hpp"
#include "acctsplitcommrep.hpp"
#include "acctsplitcommreplist.hpp"
#include "dstcacctsplitcommtrxnbuilder.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0176_req.hpp>
#include <ifastdataimpl\dse_dstc0176_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0176_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCOUNT_SPLITCOMM_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCAcctSplitCommTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
   const I_CHAR* YES = I_( "Y" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

const BFFieldId fieldsInAcctSplitComm[]=
{
   ifds::CommLevel,
   ifds::GrossOrNet,
   ifds::TradesPayType,
   ifds::CommPrcnt,
   ifds::EffectiveDate,
   ifds::StopDate,
   ifds::AgencyCode,
   ifds::BranchCode,
   ifds::AgentCode,
   ifds::SplCommRid,
   ifds::Active,
};
static const int numFieldsInAcctSplitComm = sizeof( fieldsInAcctSplitComm ) / sizeof( BFFieldId );

int DSTCAcctSplitCommTrxnBuilder::buildIndex = 0;

//******************************************************************************
void DSTCAcctSplitCommTrxnBuilder::buildTrxnKey( DString& dstStrKey, MFAccount* mfAccount )
{
   DString dstrAccountNum;

   mfAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
   dstrAccountNum.stripLeading( '0' );
   dstrAccountNum.strip();
   //build the key
   addIDITagValue( dstStrKey, TRXNTAG::ACCTTAG, dstrAccountNum );
   addIDITagValue( dstStrKey, TRXNTAG::ACCTSPLITCOMMTAG, DString::asString( buildIndex++ ) );
}

//******************************************************************************
SEVERITY DSTCAcctSplitCommTrxnBuilder::buildTransactions( DSTCWorkSession &workSession, 
                                                          BFAbstractCBO* pObj, 
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);

   if( pMFAccount != NULL )
   {
      AcctSplitCommList *pAcctSplitCommList = NULL;
      AcctSplitComm *pAcctSplitComm = NULL;
      AcctSplitCommRepList *pAcctSplitCommRepList = NULL;
      AcctSplitCommRep *pAcctSplitCommRep = NULL;
      SEVERITY severity = SEVERE_ERROR;
      int count = 0;

      //do not retrieve list from database.
      severity = pMFAccount->getAcctSplitCommList ( pAcctSplitCommList, BF::HOST, false);

      if( severity <= WARNING && pAcctSplitCommList )
      {
         DString dstrTrack,dstrActivity, dstrAccountNum, dstrMgmtCo, dstrStrKey, dstrKeyTypes;

         buildTrxnKey( dstrStrKey, pMFAccount );
         BFData* pRequest = new BFData( ifds::DSTC0176_REQ );
         BFData* pResponse = new BFData( ifds::DSTC0176_VW );
         pMFAccount->getField ( ifds::AccountNum, dstrAccountNum, BF::HOST );
         pAcctSplitCommList->getTrackActivity( dstrTrack,dstrActivity );                         
         workSession.getMgmtCo().getField(ifds::CompanyId, dstrMgmtCo, BF::HOST);
         pRequest->setElementValue( ifds::CompanyId, dstrMgmtCo );
         pRequest->setElementValue( ifds::Track, dstrTrack, false, false );
         pRequest->setElementValue( ifds::Activity, dstrActivity, false, false );         
         pRequest->setElementValue( ifds::AccountNum, dstrAccountNum, false, false );

         addIDITagValue( dstrKeyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );

         JData *jdata = new JData( DSTC_REQUEST::ACCOUNT_SPLITCOMM_UPDATE, pRequest, pResponse );
         pTrCont->addTransaction( dstrStrKey, jdata, objActivity, UPDATE_ACCOUNT, dstrKeyTypes );

         BFObjIter iterAcctSplitCommList ( *pAcctSplitCommList, BF::HOST, false, BFObjIter::ITERTYPE::ALL );
         while( !iterAcctSplitCommList.end() )
         {
            pAcctSplitComm = dynamic_cast <AcctSplitComm*> ( iterAcctSplitCommList.getObject() );
            if( pAcctSplitComm->getAcctSplitCommRepList ( pAcctSplitCommRepList, BF::HOST ) <= WARNING && 
                pAcctSplitCommRepList )
            {
               BFObjIter iterAcctSplitCommRepList ( *pAcctSplitCommRepList, BF::HOST, false, BFObjIter::ITERTYPE::ALL );               
               while( !iterAcctSplitCommRepList.end() )//&& iterAcctSplitCommRepList.hasTransactionUpdates( false ) )
               {
                  pAcctSplitCommRep = dynamic_cast <AcctSplitCommRep*> ( iterAcctSplitCommRepList.getObject() );
                  if( pAcctSplitCommRep )
                  {
                     if( pAcctSplitCommRep->hasTransactionUpdates ( false ) || 
                         iterAcctSplitCommRepList.getKey().getActivity() == OBJ_ACTIVITY_DELETED || 
                         iterAcctSplitCommRepList.getKey().getActivity() == OBJ_ACTIVITY_ADDED )
                     {
                        BFData dataRepeat(ifds::DSTC0176_REQRepeat_Record);                  
                        fillingData( pAcctSplitCommRep, &dataRepeat, fieldsInAcctSplitComm, numFieldsInAcctSplitComm );
                        DSTCWorkSession::setRunMode( &dataRepeat, iterAcctSplitCommRepList.getKey().getActivity() );
                        pRequest->addRepeat( dataRepeat );                     
                        ++count;
                     }
                  }
                  ++iterAcctSplitCommRepList;
               }
            }
            ++iterAcctSplitCommList;
         }
         pRequest->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void DSTCAcctSplitCommTrxnBuilder::fillingData( BFCBO* pObj, BFData* data, const BFFieldId fieldIds[], int numFields )
{
   DString value;
   for( int i=0; i< numFields; ++i )
   {
      pObj->getField(fieldIds[i], value, BF::HOST, false);
      data->setElementValue( fieldIds[i], value, false, false );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctSplitCommTrxnBuilder.cpp-arc  $ 
// 
//    Rev 1.10   Nov 14 2004 14:31:22   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Mar 21 2003 18:03:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Oct 09 2002 23:54:14   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.7   Aug 29 2002 12:55:20   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   Aug 12 2002 16:25:06   HSUCHIN
// another one, hopefully last.
// 
//    Rev 1.5   Aug 12 2002 16:16:30   HSUCHIN
// bug fix for not finding deleted records.
// 
//    Rev 1.4   Aug 12 2002 16:02:00   HSUCHIN
// bug fix for builder where modifications were registered properly.
// 
//    Rev 1.3   22 May 2002 18:27:00   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   Feb 25 2002 18:55:16   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.1   13 Sep 2001 10:23:48   HSUCHIN
// fix so that builder will only send updated records and leave out the non updated records
// 
//    Rev 1.0   30 Aug 2001 16:38:00   HSUCHIN
// Initial revision.
*/