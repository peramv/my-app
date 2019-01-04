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
// ^FILE   : DSTCAllocationTrxnBuilder.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : January 2000
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAllocationTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  : For Default Allocation
//
//******************************************************************************
#include "stdafx.h"
#include "amsacctlvl.hpp"
#include "amsacctlvllist.hpp"
#include "dstcallocationtrxnbuilder.hpp"
#include "dstcmfshareholdertrxnbuilder.hpp"
#include "ifasthosttransactioncontainer.hpp"
#include "mfaccount.hpp"
#include "shareholder.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0089_req.hpp>
#include <ifastdataimpl\dse_dstc0089_vw.hpp>
#include "shralloctypelist.hpp"
#include "shralloctype.hpp"
#include "defacctalloclist.hpp"
#include "defacctalloc.hpp"
#include "deffundalloclist.hpp"
#include "deffundalloc.hpp"
#include "DSTCAMSDeltaTrxnBuilder.hpp"

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;

}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ALLOCATIONS_UPDATE;
}


namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCAllocationTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}


namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const SHRNUM;
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

int DSTCAllocationTrxnBuilder::buildIndex = 0;

//******************************************************************************
void DSTCAllocationTrxnBuilder::buildTrxnKey (DString &dstStrKey, 
                                              BFAbstractCBO *pBFCBO)
{
   DString dstShrNum;

   pBFCBO->getField (ifds::ShrNum, dstShrNum, BF::HOST, true); //can be an account or shareholder
   addIDITagValue (dstStrKey, TRXNTAG::ALLOCTAG, dstShrNum.stripLeading ('0').strip());
   addIDITagValue (dstStrKey, TRXNTAG::ALLOCTAG, DString::asString( buildIndex++ ));

}

//******************************************************************************
SEVERITY DSTCAllocationTrxnBuilder::buildTransactions( DSTCWorkSession &workSession, 
                                                       BFAbstractCBO* pObj, 
                                                       HostTransactionContainer* pTrCont, 
                                                       BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   Shareholder *pShareholder = dynamic_cast<Shareholder*>(pObj);
   MFAccount* pMFAccount = dynamic_cast <MFAccount*>(pObj);

   if (pShareholder || pMFAccount)
   {
      DString dstShrNum,
         dstrAccountNum;

      if (pShareholder)
      {
         pShareholder->getField (ifds::ShrNum, dstShrNum, BF::HOST);
         dstShrNum.stripLeading ('0').strip();
      }
      if (pMFAccount)
      {
         pMFAccount->getField (ifds::AccountNum, dstrAccountNum, BF::HOST);
         pMFAccount->getField (ifds::ShrNum, dstShrNum, BF::HOST);
         dstrAccountNum.stripLeading( '0' ).strip();
         dstShrNum.stripLeading ('0').strip();
      }


      //#######################################################
      //      Get the Shareholder level record                #
      //#######################################################
      ShrAllocTypeList* pShrLvlAllocList (NULL);

      if (pShareholder)
      {
         //if no list do not go and get one from the database
         if (pShareholder->getAllocationList (pShrLvlAllocList, BF::HOST, false) &&
             pShrLvlAllocList)
         {
            buildTransactions ( workSession,
                                dstShrNum,
                                pShrLvlAllocList, 
                                pObj, 
                                pTrCont);
         }
      }
      if (pMFAccount)
      {
         AMSAcctLvlList  *pAMSAcctLvlList = NULL;
         if ( pMFAccount->getAMSAcctLvlList (BF::HOST, pAMSAcctLvlList, false) <= WARNING && 
              pAMSAcctLvlList)
         {
            BFObjIter iterAMSAcctLvlList (*pAMSAcctLvlList, BF::HOST);

            while (!iterAMSAcctLvlList.end())
            {
               AMSAcctLvl *pAMSAcctLvl = dynamic_cast<AMSAcctLvl *> (iterAMSAcctLvlList.getObject());

               if (pAMSAcctLvl)
               {
                  pShrLvlAllocList = dynamic_cast <ShrAllocTypeList*> (pAMSAcctLvl->getObject (I_("AllocationList"), BF::HOST));
                  if (pShrLvlAllocList)
                  {
//build the allocation transactions...
                     buildTransactions (workSession,
                                        dstShrNum,
                                        pShrLvlAllocList, 
                                        pObj, 
                                        pTrCont);
                  }
				  DSTCAMSDeltaTrxnBuilder::buildTransactions(workSession, pAMSAcctLvl,pTrCont, objActivity);
               }
               ++iterAMSAcctLvlList;
            }
         }
      }

   }  // if ShrHold != NULL
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void DSTCAllocationTrxnBuilder::buildTransactions ( DSTCWorkSession &workSession,
                                                    const DString &shrNum,
                                                    ShrAllocTypeList *pShrLvlAllocList, 
                                                    BFAbstractCBO *pObj, 
                                                    HostTransactionContainer *pTrCont)
{
   bool bTransCreated = false;

   if (pShrLvlAllocList)
   {
      BFObjIter iterShrLvlAllocList (*pShrLvlAllocList, BF::HOST);

      while (!iterShrLvlAllocList.end())
      {
         BFData *pDataReq (NULL),
            *pDataRes (NULL);

         ShrAllocType* pShrAlloc = dynamic_cast <ShrAllocType*> (iterShrLvlAllocList.getObject());
         
         if (pShrAlloc)
         {
            BF_OBJ_ACTIVITY shrObjActivity = iterShrLvlAllocList.getKey().getActivity();
            //to save those until we can add them to the container
            DString dstStrKey;
            DString dstKeyTypes;

            if( shrObjActivity == OBJ_ACTIVITY_ADDED || 
                shrObjActivity == OBJ_ACTIVITY_DELETED || 
                pShrAlloc->hasTransactionUpdates())
            {
               if (shrObjActivity != OBJ_ACTIVITY_ADDED && shrObjActivity != OBJ_ACTIVITY_DELETED )
               {
                  shrObjActivity = OBJ_ACTIVITY_MODIFIED;
               }

               int count = 0;
               DSTCAllocationTrxnBuilder::buildTrxnKey (dstStrKey, pObj);

               //define an iterator on the HostTransactionContainer
               HostTransactionContainerIterator iterTrxnContList (pTrCont);
               //set filter to look for the fixed area
               iterTrxnContList.walkStrKey (dstStrKey);
               iterTrxnContList.walkTrxnGroup (NO_GROUP);
               iterTrxnContList.walkTrxnSubType (0);

               iterTrxnContList.begin();

               // If first update then update fix area : build key and add transaction
               if (iterTrxnContList.end())
               {
                  bTransCreated = true;
                  pDataReq = new BFData (ifds::DSTC0089_REQ);
                  pDataRes = new BFData (ifds::DSTC0089_VW);
                  DString dstTrack, 
                     dstActivity;
                  
                  pShrLvlAllocList->getTrackActivity(dstTrack, dstActivity);
                  pDataReq->setElementValue (ifds::Track, dstTrack, false, false);
                  pDataReq->setElementValue (ifds::Activity, dstActivity, false, false);

                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                  pDataReq->setElementValue (ifds::CompanyId, mgmtCoId);

				      DString dstUpdatePACSWP;
				      pShrLvlAllocList->getField (ifds::UpdatePACSWP, dstUpdatePACSWP, BF::HOST);
				      pDataReq->setElementValue (ifds::UpdatePACSWP, dstUpdatePACSWP, false, false);
                  pDataReq->setElementValue (ifds::ShrNum, shrNum, false, false);
                  addIDITagValue (dstKeyTypes, KEYTYPES::SHRNUM, shrNum);

               }  // if first object on the update list
               else
               {
                  pDataReq = iterTrxnContList.getRequest();

               }

               if ( shrObjActivity == OBJ_ACTIVITY_ADDED || 
                    shrObjActivity == OBJ_ACTIVITY_DELETED || 
                    pShrAlloc->hasTransactionUpdates (false))
               {
                  //Setting the AccountNum into the Shareholder allocation if only one account level allocaion exist
                  //Otherwise the IFAST Base system is not updating the Allocation Record correctly
                  //June 15, 2002
                  DefAcctAllocList* pAcctAllocList (NULL);

                  if ( pShrAlloc->getAccountAllocationList (pAcctAllocList, BF::HOST) <= WARNING && 
                       pAcctAllocList)
                  {
                     BFObjIter iterAcctLvlAllocList (*pAcctAllocList, BF::HOST);
                     int count = 0;
                     DString dstAccountNum (NULL_STRING);

                     while (!iterAcctLvlAllocList.end())
                     {
                        DefAcctAlloc* acctAlloc = dynamic_cast<DefAcctAlloc*> (iterAcctLvlAllocList.getObject());
                        if (count == 0)
                        {
                           acctAlloc->getField (ifds::AccountNum, dstAccountNum, BF::HOST);
                        }
                        count++;
                        ++iterAcctLvlAllocList;
                     }
                     if (count != 1)
                     {
                        pShrAlloc->setField (ifds::AccountNum, I_("0"), BF::HOST, false);
                     }
                     else
                     {
                        pShrAlloc->setField (ifds::AccountNum, dstAccountNum, BF::HOST, false);
                     }
                  }
                  buildAllocRepeat (count, pDataReq, pShrAlloc, shrObjActivity);
               }


               //#######################################################
               //      Walk thru account level break down              #
               //#######################################################

               DefAcctAllocList *acctLvlAllocList;

               if ( pShrAlloc->getAccountAllocationList (acctLvlAllocList, BF::HOST) <= WARNING && 
                    acctLvlAllocList )
               {
                  BFObjIter iterAcctLvlAllocList (*acctLvlAllocList, BF::HOST);

                  while (!iterAcctLvlAllocList.end())
                  {
                     DefAcctAlloc* pAcctAlloc = dynamic_cast <DefAcctAlloc*> (iterAcctLvlAllocList.getObject());
                     BF_OBJ_ACTIVITY acctObjActivity = iterAcctLvlAllocList.getKey().getActivity();
                     
                     if (shrObjActivity == OBJ_ACTIVITY_DELETED)
                     {
                         acctObjActivity = OBJ_ACTIVITY_DELETED;
                     }

                     if (shrObjActivity == OBJ_ACTIVITY_MODIFIED)
                     {
                         acctObjActivity = OBJ_ACTIVITY_MODIFIED;
                     }

                     if ( acctObjActivity == OBJ_ACTIVITY_ADDED || 
                          acctObjActivity == OBJ_ACTIVITY_DELETED || 
                          pAcctAlloc->hasTransactionUpdates( false ) )
                     {
                        DString dstAccountNum;

                        pAcctAlloc->getField (ifds::AccountNum, dstAccountNum, BF::HOST);
                        addIDITagValue (dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum);
                        buildAllocRepeat (count, pDataReq, pAcctAlloc, acctObjActivity);
                     }


                     //#######################################################
                     //      Now look for fund level break down              #
                     //#######################################################

                     DefFundAllocList *fundLvlAllocList (NULL);

                     if (pAcctAlloc->getFundAllocationList (fundLvlAllocList , BF::HOST, false) <= WARNING &&
                         fundLvlAllocList)
                     {
                        //define an iterator on the account level allocation list
                        BFObjIter iterFundLvlAllocList (*fundLvlAllocList , BF::HOST);

                        while (!iterFundLvlAllocList.end() )
                        {
                           DefFundAlloc* pFundAlloc = dynamic_cast <DefFundAlloc*>( iterFundLvlAllocList.getObject() );
                           BF_OBJ_ACTIVITY fundObjActivity = iterFundLvlAllocList.getKey().getActivity();

                           if (acctObjActivity == OBJ_ACTIVITY_DELETED && fundObjActivity == OBJ_ACTIVITY_NONE)
                           {
                              fundObjActivity = OBJ_ACTIVITY_DELETED;
                           }

                           if (acctObjActivity == OBJ_ACTIVITY_MODIFIED && fundObjActivity == OBJ_ACTIVITY_NONE)
                           {
                              fundObjActivity = OBJ_ACTIVITY_MODIFIED;
                           }

                           if ( fundObjActivity == OBJ_ACTIVITY_ADDED || 
                                fundObjActivity == OBJ_ACTIVITY_DELETED ||
                                pFundAlloc->hasTransactionUpdates (false))
                           {
                              buildAllocRepeat (count, pDataReq, pFundAlloc, fundObjActivity);
                           }
                           ++iterFundLvlAllocList;
                        }// while loop
                     }// FundLvlAllocList != NULL
                     ++iterAcctLvlAllocList;
                  }  // while loop for account level
               } // if account level not null         
            }  // shareholder updated

            if (bTransCreated)
            {
               bTransCreated = false;
               JData* pJDataAlloc = new JData (DSTC_REQUEST::ALLOCATIONS_UPDATE, pDataReq, pDataRes);
               if (pJDataAlloc != NULL)
               {
                  pTrCont->addTransaction (dstStrKey, pJDataAlloc, shrObjActivity, NOT_PERSISTENT, dstKeyTypes);
               }
            }
            ++iterShrLvlAllocList;
         } // while loop at shareholder level
      } // if pShrLvlAllocList != NULL
   }
}

//******************************************************************************
void DSTCAllocationTrxnBuilder::buildAllocRepeat ( int &count, 
                                                   BFData* pDataReq, 
                                                   BFCBO* pAlloc, 
                                                   BF_OBJ_ACTIVITY listObjActivity)
{
   //create a repeat for the request and filled in
   BFData pDataRepeat( ifds::DSTC0089_REQRepeat_Record );
   pAlloc->getData (pDataRepeat, BF::HOST);

   count++;
   pDataReq->setElementValue (ifds::RepeatCount, DString::asString( count ), false, false);

   //set the RunMode field to the allocation trxn
   DSTCWorkSession::setRunMode (&pDataRepeat, listObjActivity);

   //add the repeat to the retrieved request
   pDataReq->addRepeat (pDataRepeat);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAllocationTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.28   Oct 21 2009 10:45:52   dchatcha
 * IN# 1610281 - Multiple GR allocation with the same eff. date were created via desktop, rework for fund allocation case.
 * 
 *    Rev 1.27   Sep 04 2009 06:00:52   dchatcha
 * IN#1815391 - R94 - Unable to add AMS allocation (C24740), restore 1.25 due to UAT showstopper.
 * 
 *    Rev 1.26   Apr 03 2009 05:58:10   dchatcha
 * IN 1610281 - Multiple GR allocation with the same eff. date were created via desktop.
 * 
 *    Rev 1.25   14 Sep 2007 10:59:28   popescu
 * Incident 1003183 (GAP2360/02) - fixed AMS allocations
 * 
 *    Rev 1.24   Dec 10 2004 13:51:40   Fengyong
 * PET10034197 - change flag in Acct AMS screen to allow change default allocation for PAC and SWP 
 * 
 *    Rev 1.23   Nov 14 2004 14:31:30   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.22   Mar 21 2003 18:04:08   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.21   Oct 09 2002 23:54:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.20   Aug 29 2002 12:55:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.19   Jul 04 2002 13:46:52   FENGYONG
 * sync with release 46 fix
 * 
 *    Rev 1.18   22 May 2002 18:27:06   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.17   22 Apr 2002 10:02:02   KOVACSRO
 * Rel.47 : new design for Allocations.
 * 
 *    Rev 1.16   Feb 25 2002 18:55:18   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.15   23 May 2001 14:39:54   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.14   09 May 2001 16:16:34   HSUCHIN
 * Sync up with SSB
 * 
 *    Rev 1.13   03 May 2001 14:06:12   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.12   15 Mar 2001 10:31:42   BUZILAMI
 * crash fix
 * 
 *    Rev 1.11   09 Mar 2001 18:03:44   BUZILAMI
 * XchgData elimination fixes
 * 
 *    Rev 1.10   09 Feb 2001 15:01:18   SMITHDAV
 * Removed commented code; Removed unneeded includes; Some fixes.
 * 
 *    Rev 1.9   Feb 05 2001 15:25:14   OLTEANCR
 * bug fix
 * 
 *    Rev 1.8   Jan 31 2001 16:10:54   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.7   Jan 29 2001 12:47:30   OLTEANCR
 * fix
 * 
 *    Rev 1.6   Jan 29 2001 12:21:22   OLTEANCR
 * bug fix
 * 
 *    Rev 1.5   Jan 29 2001 10:53:26   VASILEAD
 * This version has been modified just for compiling a release. It will need fixes due to the modification of buildTransaction()
 * 
 *    Rev 1.4   Jan 16 2001 14:01:40   OLTEANCR
 * modified buildTransaction(..)
 * 
 *    Rev 1.3   Jan 16 2001 13:53:28   OLTEANCR
 * 
 *    Rev 1.2   Dec 17 2000 20:23:00   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.1   Feb 15 2000 18:57:34   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:54   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Feb 03 2000 10:51:56   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.4   Feb 02 2000 10:33:54   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.3   Feb 01 2000 13:46:04   WINNIE
// bug fix : should pass account level flag when building account level repeat
// 
//    Rev 1.2   Jan 27 2000 14:11:52   POPESCUS
// add the trxn to the container at the end,
// so we can build properly the keyTypes 
// 
//    Rev 1.1   Jan 20 2000 18:03:42   WINNIE
// Change default allocation builder for new structure
// 
//    Rev 1.0   Jan 11 2000 16:42:40   WINNIE
// Initial revision.
*/
