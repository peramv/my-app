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
// ^FILE   : DSTCDemographicsTrxnBuilder.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : October 1999
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCDemographicsTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  : Create the transaction and put it into the container
//
//******************************************************************************
#include "stdafx.h"

#include "ifasthosttransactioncontainer.hpp"
#include "dstcdemographicstrxnbuilder.hpp"
#include "dstcdemographicschildtxnbuilder.hpp"
#include "dstcmfshareholdertrxnbuilder.hpp"

#include "shareholder.hpp"
#include "demographics.hpp"
#include "mfaccount.hpp"
#include "entity.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0081_req.hpp>
#include <ifastdataimpl\dse_dstc0081_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DEMOGRAPHICS_UPDATE;
}
namespace
{
   const I_CHAR* DEMOGRAPHICSCLASSNAME = I_( "DSTCDemographicsTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS     = I_( "buildTransactions" );
}

namespace ifds
{
   // Fields used
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
}

namespace CND
{
   // Conditions used
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
   extern CLASS_IMPORT I_CHAR * const ENTITYID;
}

//******************************************************************************
void DSTCDemographicsTrxnBuilder::buildTrxnKey( DString& strKey, MFAccount *pMFAccount, Demographics* demogrph )
{
   assert( pMFAccount != NULL );
   DString accountNum;

   //get the shareholder number off the sjareholder
   pMFAccount->getField( ifds::AccountNum, accountNum, BF::HOST, true );
   accountNum.stripLeading( '0' );
   accountNum.strip();
   //build the key
   addIDITagValue( strKey, TRXNTAG::DEMOGRAPHICSTAG, accountNum );
}

//******************************************************************************
SEVERITY DSTCDemographicsTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                         BFAbstractCBO* pObj,
                                                         HostTransactionContainer* pTrCont, 
                                                         BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, DEMOGRAPHICSCLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* mfaccount = dynamic_cast<MFAccount*>(pObj);
   Demographics* demogrphlist = NULL;

   //check if the demographics itself is updated,
   //do not ask the children (call hasTransactionUpdates with false) and
   //if no list do not go and get one from the database
   if( mfaccount != NULL )
   {
      severity = mfaccount->getDemographicsList( demogrphlist, BF::HOST, false );
      if( demogrphlist != NULL && severity <= WARNING && demogrphlist->hasTransactionUpdates( ) )
      {
         BFData* request = new BFData( ifds::DSTC0081_REQ );
         BFData* response = new BFData( ifds::DSTC0081_VW );
         DString strTrack,strAvtivity;
         demogrphlist->getTrackActivity(strTrack,strAvtivity);;

         request->setElementValue( ifds::Track, strTrack, false, false );
         request->setElementValue( ifds::Activity, strAvtivity, false, false );

         //fill in the request update, only the part for which the Demographics is responsible
         demogrphlist->getData( *request, BF::HOST );
         //because is part of the shareholder record,
         //demographics will have the object activity of the shareholder
         DSTCWorkSession::setRunMode( request, objActivity );
         DString strKey;

         //get the string key for the demographics
         DSTCDemographicsTrxnBuilder::buildTrxnKey( strKey, mfaccount, demogrphlist );

         DString mgmtCoId;
         workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
         request->setElementValue( ifds::CompanyId, mgmtCoId );


         DString keyTypes, accountNum;
         mfaccount->getField( ifds::AccountNum, accountNum, BF::HOST, true );
         accountNum.stripLeading( '0' );
         accountNum.strip();
         request->setElementValue( ifds::AccountNum, accountNum, false, false );

         addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, accountNum );

         JData *jdata = new JData( DSTC_REQUEST::DEMOGRAPHICS_UPDATE, request, response );
         pTrCont->addTransaction( strKey, jdata, objActivity, NOT_PERSISTENT, keyTypes );

         // DemograhicChild update
         DSTCDemographicsChildTxnBuilder::buildTransactions (workSession, demogrphlist, pTrCont, objActivity);

      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void DSTCDemographicsTrxnBuilder::buildTrxnKey1( DString& strKey, Entity *pEntity, Demographics* demogrph )
{
   assert( pEntity != NULL );

   DString strEntityId;

   pEntity->getField( ifds::EntityId, strEntityId, BF::HOST, true );
   strEntityId.stripLeading( '0' );
   strEntityId.strip();

   //build the key
   addIDITagValue( strKey, TRXNTAG::DEMOGRAPHICSTAG, strEntityId );
}

//******************************************************************************
SEVERITY DSTCDemographicsTrxnBuilder::buildTransactions1( DSTCWorkSession &workSession,
                                                          BFAbstractCBO* pObj,
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, DEMOGRAPHICSCLASSNAME, I_( "buildTransactions1" ) );

   SEVERITY severity = SEVERE_ERROR;

   Entity *pEntity = dynamic_cast<Entity*>(pObj);

   Demographics* demogrphlist = NULL;

   //check if the demographics itself is updated,
   //do not ask the children (call hasTransactionUpdates with false) and
   //if no list do not go and get one from the database
   if( pEntity != NULL )
   {
      severity = pEntity->getDemographicsList( demogrphlist, BF::HOST, false );
      if( demogrphlist != NULL && severity <= WARNING && demogrphlist->hasTransactionUpdates( ) )
      {
         BFData* request = new BFData( ifds::DSTC0081_REQ );
         BFData* response = new BFData( ifds::DSTC0081_VW );
         DString strTrack,strAvtivity;
         demogrphlist->getTrackActivity(strTrack,strAvtivity);;

         request->setElementValue( ifds::Track, strTrack, false, false );
         request->setElementValue( ifds::Activity, strAvtivity, false, false );

         //fill in the request update, only the part for which the Demographics is responsible
         demogrphlist->getData( *request, BF::HOST );
         //because is part of the shareholder record,
         //demographics will have the object activity of the shareholder
         DSTCWorkSession::setRunMode( request, objActivity );
         DString strKey;

         //get the string key for the demographics
         DSTCDemographicsTrxnBuilder::buildTrxnKey1( strKey, pEntity, demogrphlist );

         DString mgmtCoId;
         workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
         request->setElementValue( ifds::CompanyId, mgmtCoId );

         DString keyTypes, strEntityId;
         pEntity->getField( ifds::EntityId, strEntityId, BF::HOST, true );
         strEntityId.stripLeading( '0' );
         strEntityId.strip();
         request->setElementValue( ifds::AccountNum, I_( "0" ), false, false );
         request->setElementValue( ifds::EntityId, strEntityId, false, false );

         addIDITagValue( keyTypes, KEYTYPES::ENTITYID, strEntityId );

         JData *jdata = new JData( DSTC_REQUEST::DEMOGRAPHICS_UPDATE, request, response );
         pTrCont->addTransaction( strKey, jdata, objActivity, NOT_PERSISTENT, keyTypes );

         // DemograhicChild update
         DSTCDemographicsChildTxnBuilder::buildTransactions (workSession, demogrphlist, pTrCont, objActivity);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCDemographicsTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.15   Sep 12 2008 06:20:00   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.14   Nov 14 2004 14:31:58   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.13   Jul 11 2003 16:03:30   FENGYONG
 * move demographic from shareholder to MFAccount
 * 
 *    Rev 1.12   Mar 21 2003 18:04:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:54:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:55:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:27:28   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   Feb 25 2002 18:55:24   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.7   23 May 2001 14:39:52   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.6   03 May 2001 14:06:14   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   09 Feb 2001 15:01:28   SMITHDAV
 * Removed commented code; Removed unneeded includes; Some fixes.
 * 
 *    Rev 1.4   Jan 31 2001 16:10:56   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.3   Jan 16 2001 14:02:56   OLTEANCR
 * modified buildTransaction(..)
 * 
 *    Rev 1.2   Jan 16 2001 13:53:32   OLTEANCR
 * 
 *    Rev 1.1   Dec 17 2000 20:23:02   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Feb 15 2000 10:59:54   SMITHDAV
 * Initial revision.
// 
//    Rev 1.13   Feb 03 2000 10:51:56   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.12   Feb 02 2000 10:33:54   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.11   Jan 31 2000 12:49:10   POPESCUS
// fix to create the a new demographics
// 
//    Rev 1.10   Jan 31 2000 12:23:40   POPESCUS
// took out the hack
// 
//    Rev 1.9   Jan 30 2000 17:56:50   POPESCUS
// SIT fixes
// 
//    Rev 1.8   Jan 10 2000 18:23:50   POPESCUS
// do not do the trxn if shareholder is null
// 
//    Rev 1.7   Jan 09 2000 13:18:36   POPESCUS
// added the group id to the lists
// 
//    Rev 1.6   Dec 16 1999 15:41:52   WINNIE
// Assignment for shareholder number for request record
// 
//    Rev 1.5   Dec 15 1999 11:47:36   POPESCUS
// do not get the list from the database if there is none in repository
// 
//    Rev 1.4   Dec 12 1999 17:55:16   POPESCUS
// Delete the XchgData object and minor fixes
// 
*/