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
// ^FILE   : DSTCDistributionsTrxnBuilder.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October 1999
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCDistributionsTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "dstcdistributionstrxnbuilder.hpp"
#include "accountdistribution.hpp"
#include "accountdistributionlist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0096_req.hpp>
#include <ifastdataimpl\dse_dstc0096_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DISTRIBUTIONS_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCDistributionsTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

int DSTCDistributionsTrxnBuilder::buildIndex = 0;

//******************************************************************************
void DSTCDistributionsTrxnBuilder::buildTrxnKey( DString& dstStrKey, AccountDistribution* acctDistrib, MFAccount* mfAccount )
{
   DString dstAccountNum;
   mfAccount->getField( ifds::AccountNum, dstAccountNum, BF::HOST, true );
   addIDITagValue( dstStrKey, TRXNTAG::ACCTTAG,         dstAccountNum.stripLeading('0').strip() );
   addIDITagValue( dstStrKey, TRXNTAG::DISTRIBUTIONTAG, DString::asString( buildIndex++ ) );
}

//******************************************************************************
SEVERITY DSTCDistributionsTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                          BFAbstractCBO* pObj,
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* mfAccount = dynamic_cast<MFAccount*>(pObj);

   if( mfAccount != NULL )
   {
      DString dstAccountNum;
      bool bDistribRecUpdated = false;

      //walk the list of account distributions
      AccountDistributionList* accDistributionList = NULL;

      mfAccount->getField( ifds::AccountNum, dstAccountNum, BF::HOST );
      dstAccountNum.stripLeading( '0' );
      dstAccountNum.strip();

      //if no list do not go and get one from the database
      severity = mfAccount->getAccDistributionsList( accDistributionList, BF::HOST, false, false );
      if( accDistributionList != NULL && severity <= WARNING )
      {
         //define an iterator on the account distributions list
         BFObjIter iterAccDistribList( *accDistributionList, BF::HOST );

         DString dstStrKey;
         DSTCDistributionsTrxnBuilder::buildTrxnKey( dstStrKey, NULL, mfAccount );

         //define an iterator on the HostTransactionContainer
         HostTransactionContainerIterator iterTrxnContList( pTrCont );
         //set filter to look for distribution fixed area
         iterTrxnContList.walkStrKey( dstStrKey );
         //the trxn hasn't been handled yet, no group and sub type set,
         iterTrxnContList.walkTrxnGroup( NO_GROUP );
         iterTrxnContList.walkTrxnSubType( 0 );

         int count = 0;
         while( !iterAccDistribList.end() )
         {
            BFData* pDataReq  = NULL;
            BFData* pDataRes = NULL;

            AccountDistribution* acctDistribution = dynamic_cast<AccountDistribution*>( iterAccDistribList.getObject() );
            BF_OBJ_ACTIVITY listObjActivity = iterAccDistribList.getKey().getActivity();

            // check if any record under this distribution set up has been updated
            bDistribRecUpdated = DistribUpdated ( acctDistribution, listObjActivity );

            if( bDistribRecUpdated )
            {
//               int count = 0;


               iterTrxnContList.begin();
               // If first update then update fix area : build key and add transaction
               if( iterTrxnContList.end() )
               {

                  pDataReq = new BFData( ifds::DSTC0096_REQ );
                  pDataRes = new BFData( ifds::DSTC0096_VW );

                  DString dstTrack, dstActivity;
                  accDistributionList->getTrackActivity(dstTrack,dstActivity);;

                  pDataReq->setElementValue( ifds::Track, dstTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, dstActivity, false, false );

                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

                  pDataReq->setElementValue( ifds::AccountNum, dstAccountNum, false, false );

                  DString dstKeyTypes;
                  addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum );

                  JData *jdata = new JData( DSTC_REQUEST::DISTRIBUTIONS_UPDATE, pDataReq, pDataRes );
                  pTrCont->addTransaction( dstStrKey, jdata, listObjActivity, NOT_PERSISTENT, dstKeyTypes );
               }  // if first object on the update list
               else
                  pDataReq = (*iterTrxnContList)->getRequestDataObject();


               //#######################################################
               //      Now look for fund to break down                 #
               //#######################################################

               AccountDistributionList* FundToDistribList;

               acctDistribution->getSplitList( FundToDistribList );


               if( FundToDistribList != NULL )
               {
                  BFObjIter iterDistribFundToList( *FundToDistribList, BF::HOST );

                  while( !iterDistribFundToList.end() )
                  {
                     AccountDistribution* FundToDistrib = dynamic_cast<AccountDistribution*>( iterDistribFundToList.getObject() );
                     BF_OBJ_ACTIVITY FundToObjActivity = iterDistribFundToList.getKey().getActivity();

                     bDistribRecUpdated = DistribUpdated ( FundToDistrib, FundToObjActivity );

                     if( FundToObjActivity == OBJ_ACTIVITY_DELETED && (bDistribRecUpdated || listObjActivity == OBJ_ACTIVITY_DELETED ) )
                     {
                        //create a repeat for the request and filled in
                        BFData repeat( ifds::DSTC0096_REQRepeat_Record );

                        count++;
                        pDataReq->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );

                        //fill in the request update, only the part for which this distribution is responsible
                        FundToDistrib->getData( repeat, BF::HOST );

                        //set the RunMode field to the distribution trxn
                        if( listObjActivity == OBJ_ACTIVITY_DELETED )
                        {
                           DSTCWorkSession::setRunMode( &repeat, listObjActivity );     
                        }
                        else
                        {
                           DSTCWorkSession::setRunMode( &repeat, FundToObjActivity );     
                        }

                        //add the repeat to the retrieved request
                        pDataReq->addRepeat( repeat );
                     }
                     ++iterDistribFundToList;
                  }
                  iterDistribFundToList.begin();
                  while( !iterDistribFundToList.end() )
                  {
                     AccountDistribution* FundToDistrib = dynamic_cast<AccountDistribution*>( iterDistribFundToList.getObject() );
                     BF_OBJ_ACTIVITY FundToObjActivity = iterDistribFundToList.getKey().getActivity();

                     bDistribRecUpdated = DistribUpdated ( FundToDistrib, FundToObjActivity );

                     if( FundToObjActivity != OBJ_ACTIVITY_DELETED &&
                         (bDistribRecUpdated || listObjActivity == OBJ_ACTIVITY_DELETED ) )
                     {
                        //create a repeat for the request and filled in
                        BFData repeat( ifds::DSTC0096_REQRepeat_Record );

                        count++;
                        pDataReq->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );

                        //fill in the request update, only the part for which this distribution is responsible
                        FundToDistrib->getData( repeat, BF::HOST );

                        //set the RunMode field to the distribution trxn
                        if( listObjActivity == OBJ_ACTIVITY_DELETED )
                        {
                           DSTCWorkSession::setRunMode( &repeat, listObjActivity );     
                        }
                        else
                        {
                           DSTCWorkSession::setRunMode( &repeat, FundToObjActivity );     
                        }

                        //add the repeat to the retrieved request
                        pDataReq->addRepeat( repeat );
                     }
                     ++iterDistribFundToList;
                  }
               } // FundToDistribList !=NULL

               //#######################################################
               //      fund to break down finished                     #
               //#######################################################

            }// acctDistribution available
            ++iterAccDistribList;
         }  // while loop
      } // account distribution list not null
   }  // MFaccount not null
   return(GETCURRENTHIGHESTSEVERITY());
}


bool DSTCDistributionsTrxnBuilder::DistribUpdated ( AccountDistribution* acctDistrib, BF_OBJ_ACTIVITY ObjActivity )
{
   bool iupdate ( false );

   if( acctDistrib == NULL )
   {
      iupdate = false;
   }
   else if( ObjActivity == OBJ_ACTIVITY_ADDED || acctDistrib->hasTransactionUpdates( ) || ObjActivity == OBJ_ACTIVITY_DELETED )
   {
      iupdate = true;
   }
   else  // go further down
   {
      AccountDistributionList* pMoreDistribList;
      acctDistrib->getSplitList( pMoreDistribList );

      if( pMoreDistribList != NULL )
      {
         BFObjIter iterDistribList( *pMoreDistribList, BF::HOST );

         while( !iterDistribList.end() && !iupdate )
         {
            AccountDistribution* moreDistrib = dynamic_cast<AccountDistribution*>( iterDistribList.getObject() );
            BF_OBJ_ACTIVITY listObjActivity = iterDistribList.getKey().getActivity();

            iupdate = DistribUpdated ( moreDistrib, listObjActivity  );                   

            if( iupdate )
            {
               break;
            }

            ++iterDistribList;
         }   // while loop
      } // if not NULL
   }      // else

   return(iupdate);
}






//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCDistributionsTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.18   Nov 14 2004 14:32:10   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.17   Mar 21 2003 18:04:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.16   Oct 09 2002 23:54:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 12:55:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   22 May 2002 18:27:28   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.13   Feb 25 2002 18:55:26   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.12   15 Oct 2001 12:04:38   KOVACSRO
 * Don't create the list if not there.
 * 
 *    Rev 1.11   23 May 2001 14:39:52   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.10   09 May 2001 16:23:32   HSUCHIN
 * Sync up with SSB
 * 
 *    Rev 1.9   03 May 2001 14:06:16   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Mar 19 2001 17:23:24   ZHANGCEL
 * Fixed the bug regarding count
 * 
 *    Rev 1.7   09 Mar 2001 18:03:44   BUZILAMI
 * XchgData elimination fixes
 * 
 *    Rev 1.6   09 Feb 2001 15:01:28   SMITHDAV
 * Removed commented code; Removed unneeded includes; Some fixes.
 * 
 *    Rev 1.5   Jan 31 2001 16:10:56   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.4   Jan 30 2001 16:22:02   YINGZ
 * temp set Track to N
 * 
 *    Rev 1.3   Jan 16 2001 14:03:28   OLTEANCR
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
//    Rev 1.20   Feb 03 2000 10:51:58   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.19   Feb 02 2000 10:33:56   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.18   Jan 26 2000 13:45:10   WINNIE
// Fix deletion logic
// 
//    Rev 1.17   Jan 21 2000 19:13:08   WINNIE
// changes for new design of distribution CBO
// 
//    Rev 1.16   Jan 09 2000 13:18:38   POPESCUS
// added the group id to the lists
// 
//    Rev 1.15   Jan 06 2000 12:02:54   POPESCUS
// fix related to filter more the HTC 
// 
//    Rev 1.14   Dec 15 1999 11:47:36   POPESCUS
// do not get the list from the database if there is none in repository
// 
//    Rev 1.13   Dec 12 1999 17:55:20   POPESCUS
// Delete the XchgData object and minor fixes
// 
*/