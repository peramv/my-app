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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCRRIFInfoTrxnBuilder.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : May 2000
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCRRIFInfoTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcrrifinfotrxnbuilder.hpp"
#include <ifastdataimpl\dse_dstc0129_req.hpp>
#include <ifastdataimpl\dse_dstc0129_vw.hpp>
#include <ifastdataimpl\dse_dstc0067_vw.hpp>
#include "mfaccount.hpp"
#include "rrif_lif_lrif_info.hpp"
#include "rrif_lif_lrif_infolist.hpp"
#include "fromfundalloclist.hpp"
#include "fromfundalloc.hpp"
#include "tofundalloclist.hpp"
#include "tofundalloc.hpp"
#include "FundAlloc.hpp"
#include "FundAllocList.hpp"


#include "mgmtco.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RRIF_LIF_LRIF_INFO_UPDATE;
}
namespace
{
   const I_CHAR* const CLASSNAME = I_( "DSTCRRIFInfoTrxnBuilder" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId rxBatchName;
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}


int DSTCRRIFInfoTrxnBuilder::buildIndex = 0;

//******************************************************************************
void DSTCRRIFInfoTrxnBuilder::buildTrxnKey( DString& dstStrKey, 
                                            RRIF_LIF_LRIF_Info* pRRIF_LIF_LRIF_Info, 
                                            MFAccount* pMFAccount, 
                                            const BFDataGroupId& idDataGroup )
{
   DString dstAccountNum, dstRIFId(NULL_STRING);

   pMFAccount->getField( ifds::AccountNum, dstAccountNum, BF::HOST, true );
   addIDITagValue( dstStrKey, TRXNTAG::ACCTTAG, dstAccountNum.strip().stripLeading('0'));

   if( pRRIF_LIF_LRIF_Info != NULL )
   {
      pRRIF_LIF_LRIF_Info->getField( ifds::RIFId, dstRIFId, idDataGroup );
      addIDITagValue( dstStrKey, TRXNTAG::RIFIDTAG, dstRIFId.strip().stripLeading('0') );
   }
   addIDITagValue( dstStrKey, TRXNTAG::RRIFINFOTAG, DString::asString( buildIndex++ ) );
}

//******************************************************************************
SEVERITY DSTCRRIFInfoTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                     BFAbstractCBO* pObj,
                                                     HostTransactionContainer* pTrCont, 
                                                     BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);

   if( pMFAccount != NULL )
   {
      DString dstAccountNum;
      bool bRRIFRecUpdated( false );

      //walk the RRIF list
      RRIF_LIF_LRIF_InfoList* pRRIF_LIF_LRIF_InfoList = NULL;

      pMFAccount->getField( ifds::AccountNum, dstAccountNum, BF::HOST );
      dstAccountNum.strip().stripLeading( '0' );

      //if no list do not go and get one from the database

      severity = pMFAccount->getRRIF_LIF_LRIF_InfoList( pRRIF_LIF_LRIF_InfoList, BF::HOST, false );
      if( pRRIF_LIF_LRIF_InfoList != NULL && severity <= WARNING )
      {
         //define an iterator on the RRIF list
         BFObjIter iterRRIFInfoList( *pRRIF_LIF_LRIF_InfoList, BF::HOST );

         DString keyString;
         DSTCRRIFInfoTrxnBuilder::buildTrxnKey( keyString, NULL, pMFAccount, BF::HOST );

         //define an iterator on the HostTransactionContainer
         HostTransactionContainerIterator iterTrxnContList( pTrCont );
         //set filter to look for distribution fixed area
         iterTrxnContList.walkStrKey( keyString );
         //the trxn hasn't been handled yet, no group and sub type set,
         iterTrxnContList.walkTrxnGroup( NO_GROUP );
         iterTrxnContList.walkTrxnSubType( 0 );


         while( !iterRRIFInfoList.end() )
         {
            RRIF_LIF_LRIF_Info* pRRIF_LIF_LRIF_Info = dynamic_cast<RRIF_LIF_LRIF_Info*>( iterRRIFInfoList.getObject() );
            BF_OBJ_ACTIVITY listObjActivity = iterRRIFInfoList.getKey().getActivity();

            // check if any record under this distribution set up has been updated
            bRRIFRecUpdated = RRIFUpdated ( pRRIF_LIF_LRIF_Info, listObjActivity );
				bool bUpdateRRIFGroup = pRRIF_LIF_LRIF_Info->hasFieldsUpdateForGroup(RRIF_GROUP::RRIF_INFO);

            BFData * pDataReq = NULL;
            BFData * pDataRes = NULL;

            if( bRRIFRecUpdated )
            {
               iterTrxnContList.begin();
               // If first update then update fix area : build key and add transaction
               if( iterTrxnContList.end() )
               {

                  pDataReq = new BFData( ifds::DSTC0129_REQ );
                  pDataRes = new BFData( ifds::DSTC0129_VW );

                  DString strTrack,strActivity;
                  pRRIF_LIF_LRIF_InfoList->getTrackActivity(strTrack, strActivity);
                  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

                  //fill in the request update
                  pRRIF_LIF_LRIF_Info->getData( *pDataReq, BF::HOST );
                  DString strName;  //we should use the new BatchName to build transaction
                  pRRIF_LIF_LRIF_Info->getField(ifds::rxBatchName,strName,BF::HOST,false);
                  pDataReq->setElementValue(ifds::BatchName,strName,false,false);

                  DSTCWorkSession::setRunMode(pDataReq, listObjActivity);
                  DString dstStrKey;
                  DSTCRRIFInfoTrxnBuilder::buildTrxnKey( dstStrKey, pRRIF_LIF_LRIF_Info, pMFAccount, BF::HOST );

                  //Set RRIFModified to NO if only the Allocation List has changed, to tell the database not to 
                  //'update' the view. This is done because, when 'updating' a record, Progress marks the old one 
                  //as 'bad' and inserts a new 'good' one. At least with view 129. ;-)
                  // added by yingbao
						// June 24, 2003
						// after discussing with Amelia, RRIFModied should be Y
						// when 1) RRIF change or allocation change, back end uses the flag to  
						//	create bad record with allocation

                  //if( bUpdateRRIFGroup )
                     pDataReq->setElementValue( ifds::RRIFModified, I_("Y"), false, false );
                  //else
                  //   pDataReq->setElementValue( ifds::RRIFModified, I_("N"), false, false );

                  pDataReq->setElementValue( ifds::AccountNum, dstAccountNum, false, false );

                  DString keyTypes;
                  addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum );

                  JData *jdata = new JData( DSTC_REQUEST::RRIF_LIF_LRIF_INFO_UPDATE, pDataReq, pDataRes);
                  pTrCont->addTransaction( dstStrKey, jdata, listObjActivity, NOT_PERSISTENT, keyTypes );
               }  // if first object on the update list
               else
               {
                  pDataRes = (*iterTrxnContList)->getRequestDataObject();
               }

					// from Allocation list
               FromFundAllocList* pRRIF_LIF_LRIF_AllocList = NULL;

               SEVERITY sev1 = pRRIF_LIF_LRIF_Info->getFromFundAllocList( pRRIF_LIF_LRIF_AllocList, BF::HOST, false );
               if( pRRIF_LIF_LRIF_AllocList != NULL )
               {
        
						builAllocation(pRRIF_LIF_LRIF_Info, pRRIF_LIF_LRIF_AllocList,pDataReq,true );						
						
					}																
					// to Allocation list
					DString dstrPayType,dstrToAllocations;
					pRRIF_LIF_LRIF_Info->getField(ifds::ToAllocations,dstrToAllocations,BF::HOST);
					dstrToAllocations.strip().upperCase();
					pRRIF_LIF_LRIF_Info->getField(ifds::RIFPayType,dstrPayType,BF::HOST);
					dstrPayType.strip().upperCase();
					if ( dstrPayType == I_("T") || dstrToAllocations == I_("Y"))  // to account
					{
						ToFundAllocList* pAllocList = NULL;

						SEVERITY sev1 = pRRIF_LIF_LRIF_Info->getToFundAllocList( pAllocList, BF::HOST, false );
						if( pAllocList != NULL )
						{
							// originally there is toallocation and user changed paytype from "T"
							//to something else we need to delete to allocation in the data base.
							bool bDelToAlloc = dstrPayType != I_("T") && dstrToAllocations == I_("Y");
							builAllocation(pRRIF_LIF_LRIF_Info, pAllocList,pDataReq,true,bDelToAlloc );						
							
						}						
					}
				}
				++iterRRIFInfoList;
         }  // while loop
      } // pRRIF_LIF_LRIF_InfoList
   }  // MFaccount not null
   return(GETCURRENTHIGHESTSEVERITY());
}
//*********************************************************************************

SEVERITY DSTCRRIFInfoTrxnBuilder::builAllocation(RRIF_LIF_LRIF_Info* pRRIFInfo, 
												FundAllocList* pAllocList,BFData* pDataReq,
												bool bRRIFUpdated,bool bDelToAlloc )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("builAllocation"));
   SEVERITY severity = SEVERE_ERROR;
   if( pAllocList != NULL )
   {
      BFObjIter iterAllocList( *pAllocList, BF::HOST );

      while( !iterAllocList.end() )
      {
         FundAlloc* pAlloc = dynamic_cast<FundAlloc*>( iterAllocList.getObject() );
         BF_OBJ_ACTIVITY objActivity = iterAllocList.getKey().getActivity();
			
			bool bTransactionUpdates = pAlloc->hasTransactionUpdates(false );
			// if user modify RRIF info, or add/delete allocation or modify allocation
			// build allocation transaction


         if( bRRIFUpdated || objActivity == OBJ_ACTIVITY_DELETED ||  
					objActivity == OBJ_ACTIVITY_ADDED || bTransactionUpdates )
         {
            //create a repeat for the request and filled in
            BFData repeat( ifds::DSTC0129_REQRepeat_Record );


            //fill in the request update, only the part for which this distribution is responsible
            pAlloc->getData( repeat, BF::HOST );

            /*
              * Because the AllocRunMode is not standard RunMode
              */
            //DSTCHostDataManager::setRunMode(&dataRepeat, ObjActivityAlloc);
            //set the RunMode field to the distribution trxn
				if( bDelToAlloc && objActivity != OBJ_ACTIVITY_ADDED )  					
				{
					//the record is in the back end and user change PayType to something else, 
					//we need to delete allocation 
					repeat.setElementValue( ifds::AllocRunMode, RUNMODE::DELETED );
				}
				else if (bRRIFUpdated && objActivity != OBJ_ACTIVITY_DELETED ) // when user modify RRIF info, the allocRunMode is always ADD
				{
				    repeat.setElementValue( ifds::AllocRunMode, RUNMODE::ADDED );	
				}
				else
				{
					if( objActivity == OBJ_ACTIVITY_NONE )
						repeat.setElementValue( ifds::AllocRunMode, RUNMODE::MODIFIED );
					else if( objActivity == OBJ_ACTIVITY_ADDED )
						repeat.setElementValue( ifds::AllocRunMode, RUNMODE::ADDED );
					else if( objActivity == OBJ_ACTIVITY_DELETED )
						repeat.setElementValue( ifds::AllocRunMode, RUNMODE::DELETED );
				}
			   DString dstrAllocType;	
				pAlloc->getField(ifds::TransType,dstrAllocType,BF::HOST,false);
				repeat.setElementValue(ifds::AllocType,dstrAllocType);


            //add the repeat to the retrieved request
            //**Data &rptRecord = const_cast< Data & >(req->getData( DEFAULT_REPEAT_RECORD ) );
            pDataReq->addRepeat( repeat );
				int iCount = pDataReq->getRepeatCount(); 
            pDataReq->setElementValue( ifds::RepeatCount, DString::asString( pDataReq->getRepeatCount() ) );
         }
         ++iterAllocList;
      }
   } 
	return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
bool DSTCRRIFInfoTrxnBuilder::RRIFUpdated ( BFAbstractCBO* pRRIF, BF_OBJ_ACTIVITY ObjActivity, bool recursive )
{
   bool iupdate ( false );

   if( pRRIF == NULL )
   {
      iupdate = false;
   }
   else if( ObjActivity == OBJ_ACTIVITY_ADDED || pRRIF->hasTransactionUpdates( recursive ) || ObjActivity == OBJ_ACTIVITY_DELETED )
   {
      iupdate = true;
   }

   return(iupdate);
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCRRIFInfoTrxnBuilder.cpp-arc  $
// 
//    Rev 1.23   Nov 14 2004 14:33:22   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.22   Jun 27 2003 10:14:10   YINGBAOL
// change code due to view's requirement.
// 
//    Rev 1.21   Jun 12 2003 16:49:30   YINGBAOL
// RRIF Allocation RunMode change
// 
//    Rev 1.20   Jun 09 2003 11:48:24   YINGBAOL
// RRIF enhancement
// 
//    Rev 1.19   Mar 21 2003 18:06:46   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.18   Oct 09 2002 23:54:22   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.17   Aug 29 2002 12:55:34   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.16   Aug 06 2002 10:01:36   KOVACSRO
// Release 48. Converted allocations.
// 
//    Rev 1.15   22 May 2002 18:27:58   PURDYECH
// BFData Implementation
// 
//    Rev 1.14   Feb 25 2002 18:55:34   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.13   Jul 16 2001 17:31:00   ZHANGCEL
// Fixed the crash due to multiple declar pointer
// 
//    Rev 1.12   23 May 2001 14:39:28   SMITHDAV
// Fill CompanyId to all request Data objects that are posted to the HTC.
// 
//    Rev 1.11   03 May 2001 14:06:20   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.10   09 Mar 2001 18:03:42   BUZILAMI
// XchgData elimination fixes
// 
//    Rev 1.9   09 Feb 2001 15:01:32   SMITHDAV
// Removed commented code; Removed unneeded includes; Some fixes.
// 
//    Rev 1.8   Jan 31 2001 16:11:00   YINGBAOL
// set track and activity values for update transactions
// 
//    Rev 1.7   Jan 16 2001 13:53:36   OLTEANCR
// 
//    Rev 1.6   Dec 17 2000 20:23:12   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.5   Oct 23 2000 11:41:48   YINGBAOL
// fix run mode bug for add a new RRIF
// 
//    Rev 1.4   Oct 19 2000 15:26:54   YINGBAOL
// introduce group and modify building Transaction logic
// 
//    Rev 1.3   Oct 17 2000 14:53:56   YINGBAOL
// add addcopy fundction and fix other issues
// 
//    Rev 1.2   Jun 28 2000 15:00:44   PETOLESC
// Added Frequency field, changed logic for view 130 call sequence and a BIG bunch of other changes.
// 
//    Rev 1.1   Jun 09 2000 18:01:28   PETOLESC
// Save work.
// 
//    Rev 1.0   May 04 2000 13:46:02   PETOLESC
// Initial revision.
 * 
 *
 */