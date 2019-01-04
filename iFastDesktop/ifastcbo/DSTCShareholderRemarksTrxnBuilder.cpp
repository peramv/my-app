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
// ^FILE   : DSTCShareholderRemarksTrxnBuilder.cpp
// ^AUTHOR : Ram Singaram
// ^DATE   : Novemeber 1999
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
#include "dstcshareholderremarkstrxnbuilder.hpp"
#include "remarks.hpp"
#include "remarkslist.hpp"
#include "shareholder.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0085_req.hpp>
#include <ifastdataimpl\dse_dstc0085_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REMARKS_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME         = I_( "DSTCShareholderRemarksTrxnBuilder" );
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

//******************************************************************************
SEVERITY DSTCShareholderRemarksTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   Shareholder* shareholder = dynamic_cast<Shareholder*>(pObj);

   if( shareholder != NULL )
   {
      DString dstShrNum, dstTrnKey, dstKeyTypes;
      shareholder->getField( ifds::ShrNum, dstShrNum, BF::HOST, true );
      addIDITagValue( dstTrnKey,   TRXNTAG::REMARKSTAG, dstShrNum.stripLeading('0').strip() );
      addIDITagValue( dstKeyTypes, KEYTYPES::SHRNUM, dstShrNum );

      HostTransactionContainerIterator iterTrxnContList( pTrCont );
      //set filter to look for Entity fixed area
      iterTrxnContList.walkStrKey( dstTrnKey );
      iterTrxnContList.walkTrxnGroup( NO_GROUP );
      iterTrxnContList.walkTrxnSubType( 0 );

      //walk the list of remarks
      RemarksList* remarksList = NULL;

      //if no list do not go and get one from the database
      severity = shareholder->getRemarksList( remarksList, BF::HOST, false );

      if( remarksList != NULL && severity <= WARNING )
      {
         BFData *pDataReq = NULL;
         BFData *pDataRes = NULL;

         //define an iterator on the remarksList
         BFObjIter iterRemarksList( *remarksList, BF::HOST );
         Remarks* remarks = NULL;

			DString dstrAccountNum;
         iterRemarksList.begin();
         while( !iterRemarksList.end() )
         {
            //in case of a list the obj_activity is known only by the list,
            //so ask the key about it
            remarks = dynamic_cast<Remarks*>( iterRemarksList.getObject() );

            if( iterRemarksList.hasTransactionUpdates( ) )
            {
               iterTrxnContList.begin();
               
               //create a repeat for the request and fill it in
               BFData repeat( ifds::DSTC0085_REQRepeat_Record );

               //fill in the request update, only the part for which the Remarks is responsible
               remarks->getData( repeat, BF::HOST );
					dstrAccountNum = repeat.getElementValue( ifds::AccountNum );

					//fill in the fixed area
               if( iterTrxnContList.end() )
               {
                  pDataReq = new BFData( ifds::DSTC0085_REQ );
                  pDataRes = new BFData( ifds::DSTC0085_VW );

                  DString strTrack, strActivity;
                  remarksList->getTrackActivity(strTrack,strActivity);         
                  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                  //fill in the request update, only the part for which the Remarks is responsible
                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

                  pDataReq->setElementValue( ifds::ShrNum, dstShrNum );

						// This means that the Account No of the last repeat is part of the key
						// Can we have multiple accounts?
						addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );

                  JData *jdata = new JData( DSTC_REQUEST::REMARKS_UPDATE, pDataReq, pDataRes );
                  pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
               }
               else
                  pDataRes = (*iterTrxnContList)->getRequestDataObject();

					//set the RunMode field to the ShareholderRemarksUpdate trxn
               DSTCWorkSession::setRunMode( &repeat, iterRemarksList.getKey().getActivity() );
					
					//add the lDataRepeat to the request
               pDataReq->addRepeat( repeat );
               DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
               pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );
            }
            //move to the next remark
            ++iterRemarksList;
         }
         //meaning we have at least one remark
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCShareholderRemarksTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.14   Nov 14 2004 14:33:34   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.13   Oct 03 2003 10:10:12   VADEANUM
 * PTS 10022399 - Wrong Account # assigned to Remark - replaced RefAccount with AccountNum in order to have the fieldid picked up in DSTCWorkSession::commit() after including the field in the transaction key.
 * 
 *    Rev 1.12   Mar 21 2003 18:06:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:54:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:55:36   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:27:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   Feb 25 2002 18:55:36   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.7   23 May 2001 14:39:28   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.6   03 May 2001 14:06:22   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   09 Mar 2001 18:03:42   BUZILAMI
 * XchgData elimination fixes
 * 
 *    Rev 1.4   09 Feb 2001 15:01:32   SMITHDAV
 * Removed commented code; Removed unneeded includes; Some fixes.
 * 
 *    Rev 1.3   Jan 31 2001 16:11:00   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.2   Jan 16 2001 13:53:38   OLTEANCR
 * 
 *    Rev 1.1   Dec 17 2000 20:23:14   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Feb 15 2000 10:59:56   SMITHDAV
 * Initial revision.
// 
//    Rev 1.13   Feb 03 2000 10:52:02   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.12   Feb 02 2000 10:34:00   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.11   Jan 09 2000 13:18:50   POPESCUS
// added the group id to the lists
// 
//    Rev 1.10   Jan 08 2000 13:01:36   POPESCUS
// fixes for shrNum
// 
//    Rev 1.9   Jan 07 2000 11:51:32   POPESCUS
// fixes
// 
//    Rev 1.8   Jan 06 2000 17:39:18   POPESCUS
// fixed some issues related to building a trxn when nothing has been updated
// 
//    Rev 1.7   Dec 24 1999 11:37:54   WINNIE
// misc
// 
//    Rev 1.6   Dec 15 1999 11:48:00   POPESCUS
// do not get the list from the database if there is none in repository
// 
//    Rev 1.5   Dec 12 1999 17:55:46   POPESCUS
// Delete the XchgData object and minor fixes
// 
*/