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
// ^FILE   : DSTCAdvisorTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAdvisorTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcadvisortrxnbuilder.hpp"
#include "advisor.hpp"
#include "advisorlist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0191_req.hpp>
#include <ifastdataimpl\dse_dstc0191_vw.hpp>
#include <ifastdataimpl\dse_dstc0092_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SLSREP_LIST;
}
namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCAdvisorTrxnBuilder" );
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


const BFFieldId fieldsInAdvisor[]=
{
   ifds::BrokerCode,
   ifds::SlsrepCode,
   ifds::SlsRepEmail,
   ifds::SlsRepPhone,
};
static const int numfieldsInAdvisor = sizeof( fieldsInAdvisor ) / sizeof( BFFieldId );

//******************************************************************************

void DSTCAdvisorTrxnBuilder::fillingData( const BFAbstractCBO* pObj, BFData* data, const BFFieldId fieldIds[], int numFields )
{
   DString value;
   for( int i=0; i< numFields; ++i )
   {
      pObj->getField(fieldIds[i], value, BF::HOST, false);
      data->setElementValue( fieldIds[i], value, false, false );
   }
}

//******************************************************************************

SEVERITY DSTCAdvisorTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                    BFAbstractCBO* pBFBase, 
                                                    HostTransactionContainer* pTrxnContainer, 
                                                    BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "buildTransactions( DSTCWorkSession *, BFAbstractCBO *, HostTransactionContainer *, BF_OBJ_ACTIVITY )" ) );

   SEVERITY sevRtn = SEVERE_ERROR;

   AdvisorList* pAdvisorList = dynamic_cast<AdvisorList*>(pBFBase);
   if( pAdvisorList == NULL )
      return(GETCURRENTHIGHESTSEVERITY());


   DString strTrack, strPageName;
   pAdvisorList->getTrackActivity(strTrack,strPageName);

   //walk through the Advisor List
   BFObjIter iterAdvisorList(*pAdvisorList, BF::HOST);
   while( !iterAdvisorList.end() )
   {
      Advisor* pAdvisor = dynamic_cast<Advisor*>(iterAdvisorList.getObject());

      BF_OBJ_ACTIVITY ObjActivityAdvisor = iterAdvisorList.getKey().getActivity();

      if( pAdvisor && ( ObjActivityAdvisor == OBJ_ACTIVITY_ADDED    || 
                        ObjActivityAdvisor == OBJ_ACTIVITY_DELETED  || 
                        pAdvisor->hasTransactionUpdates()  ) )
      {
         DString dstTrnKey;

         DString dstSlsrep;

         pAdvisor->getField( ifds::Slsrep, dstSlsrep, BF::HOST, true );
         addIDITagValue(dstTrnKey, TRXNTAG::TRANSNUMTAG, dstSlsrep.stripLeading('0').strip());

         HostTransactionContainerIterator iterTrxnContainer( pTrxnContainer );//define an iterator on the HostTransactionContainer
         iterTrxnContainer.walkStrKey( dstTrnKey );                  // look for the trade record in the HostTransactionContainer
         iterTrxnContainer.walkTrxnGroup( NO_GROUP );                //the trxn hasn't been handled yet, no group and sub type set,
         iterTrxnContainer.walkTrxnSubType( 0 );

         iterTrxnContainer.begin();


         BFData *request = new BFData( ifds::DSTC0191_REQ );
         BFData *response = new BFData( ifds::DSTC0191_VW );

         DString tmp;
         pAdvisor->getField( ifds::BrokerCode, tmp, BF::HOST, true );
         request->setElementValue( ifds::BrokerCode, tmp );
         pAdvisor->getField( ifds::Slsrep, tmp, BF::HOST, true );
         request->setElementValue( ifds::SlsrepCode, tmp );
         pAdvisor->getField( ifds::Email, tmp, BF::HOST, true );
         request->setElementValue( ifds::SlsRepEmail, tmp );
         pAdvisor->getField( ifds::PhoneNumber, tmp, BF::HOST, true );
         request->setElementValue( ifds::SlsRepPhone, tmp );

         pAdvisor->getField( ifds::SlsRepCntry, tmp, BF::HOST, true );
         request->setElementValue( ifds::SlsRepCntry, tmp );
         pAdvisor->getField( ifds::SlsRepArea, tmp, BF::HOST, true );
         request->setElementValue( ifds::SlsRepArea, tmp );

         request->setElementValue( ifds::Track, strTrack );
         request->setElementValue( ifds::Activity, strPageName );
         DSTCWorkSession::setRunMode(request, ObjActivityAdvisor);

         DString mgmtCoId;
         workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
         request->setElementValue( ifds::CompanyId, mgmtCoId );

         DString dstrKeyTypes(NULL_STRING);
         //add the transaction to the container; the right side of the XchgData
         JData *jdata = new JData( DSTC_REQUEST::SLSREP_LIST, request, response );
         pTrxnContainer->addTransaction(dstTrnKey, jdata, 
                                        ObjActivityAdvisor, NOT_PERSISTENT, dstrKeyTypes);
      }

      ++iterAdvisorList;
   }  // while loop
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAdvisorTrxnBuilder.cpp-arc  $
// 
//    Rev 1.7   Nov 14 2004 14:31:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Mar 21 2003 18:04:02   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Oct 09 2002 23:54:16   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:55:20   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   22 May 2002 18:27:06   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   Feb 25 2002 18:55:18   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.1   Feb 14 2002 16:14:08   FENGYONG
// Add fields
// 
//    Rev 1.0   Jan 04 2002 10:09:22   FENGYONG
// Initial revision.
 * 
 * 
 */