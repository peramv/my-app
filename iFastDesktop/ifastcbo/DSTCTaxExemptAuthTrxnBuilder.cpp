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
// ^FILE   : DSTCTaxExemptAuthTrxnBuilder.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : July 15, 2004
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCTaxExemptAuthTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "dstcworksession.hpp"
#include "TaxExemptAuthorization.hpp"
#include "TaxExemptAuthorizationList.hpp"
#include <ifastdataimpl\dse_dstc0302_req.hpp>
#include <ifastdataimpl\dse_dstc0302_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0302_vw.hpp>
#include "DSTCTaxExemptAuthTrxnBuilder.hpp"
#include "mfaccount.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TAX_EXEMPT_AUTHORIZATION_LIST_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCTaxExemptAuthTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}


namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFNumericFieldId EntityId;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
	extern CLASS_IMPORT I_CHAR * const ENTITYID;
}

//******************************************************************************
SEVERITY DSTCTaxExemptAuthTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);

   if( pMFaccount )
   {

		TaxExemptAuthorizationList* pTaxExemptAuthorizationList = NULL;
		TaxExemptAuthorization* pTaxExemptAuthorization = NULL;

      DString dstAccountNum, dstTrnKey, dstKeyTypes;
      pMFaccount->getField( ifds::AccountNum, dstAccountNum, BF::HOST, true );
      addIDITagValue( dstTrnKey,   TRXNTAG::EXEMPTTAG, dstAccountNum.stripLeading('0').strip() );
      addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum );

      HostTransactionContainerIterator iterTrxnContList( pTrCont );

      iterTrxnContList.walkStrKey( dstTrnKey );
      iterTrxnContList.walkTrxnGroup( NO_GROUP );
      iterTrxnContList.walkTrxnSubType( 0 );
      int i = 0;
      if ( pMFaccount->getTaxExemptAuthorizationList( pTaxExemptAuthorizationList, dstAccountNum, BF::HOST, false ) &&
			  NULL != pTaxExemptAuthorizationList )
		{
         BFData *pDataReq = NULL;
         BFData *pDataRes = NULL;

         BFObjIter iter( *pTaxExemptAuthorizationList, BF::HOST );
         TaxExemptAuthorization* pTaxExemptAuthorization = NULL;

         iter.begin();
         while( !iter.end() )
         {
            pTaxExemptAuthorization = dynamic_cast<TaxExemptAuthorization*>( iter.getObject() );
            ++i;
            if( iter.hasTransactionUpdates() )
            {
               iterTrxnContList.begin();

               //fill in the fixed area
               if( iterTrxnContList.end() )
               {
                  pDataReq = new BFData( ifds::DSTC0302_REQ );
                  pDataRes = new BFData( ifds::DSTC0302_VW );

                  DString strTrack, strActivity;

                  pTaxExemptAuthorizationList->getTrackActivity(strTrack,strActivity);         
                  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                  //fill in the request update
                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
                  pDataReq->setElementValue( ifds::AccountNum, dstAccountNum );

                  const BFObjectKey& bfKey = iter.getKey();						
                  DString dstrEntityId; 

                  pTaxExemptAuthorization->getField(ifds::EntityId, dstrEntityId, BF::HOST);
                  addIDITagValue (dstKeyTypes, KEYTYPES::ENTITYID, dstrEntityId);
                  JData *jdata = new JData( DSTC_REQUEST::TAX_EXEMPT_AUTHORIZATION_LIST_UPDATE, pDataReq, pDataRes );
                  DString post = I_("0000");
                  post.appendInt( i );
                  DString strKey = I_("TaxExemptAuthTrxn") + post;
                  pTrCont->addTransaction (strKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes);
               }
               else
                  pDataRes = (*iterTrxnContList)->getRequestDataObject();


               //create a repeat for the request and fill it in
               BFData repeat( ifds::DSTC0302_REQRepeat_Record);
               
               //fill in the request update
               pTaxExemptAuthorization->getData( repeat, BF::HOST );

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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCTaxExemptAuthTrxnBuilder.cpp-arc  $
// 
//    Rev 1.7   May 05 2005 16:25:26   yingbaol
// Incident 305495: fix multiple transaction issue.
// 
//    Rev 1.6   Apr 29 2005 11:47:24   popescu
// Incident #293920 - code clean-up
// 
//    Rev 1.5   Apr 27 2005 17:39:38   ZHANGCEL
// Incident #293920 -- Fix problem for the EntityId setup during the NASU flow
// 
//    Rev 1.4   Apr 21 2005 10:22:16   ZHANGCEL
// Incident #292340 -- Rewrite buildTransactions
// 
//    Rev 1.3   Nov 14 2004 14:33:52   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Sep 22 2004 09:08:44   WINNIE
// PET 1082 Tax Exemption project : add new parameter to getTaxExemptAuthorizationList for not to get data from database. If the pointer is NULL in MFAccount, then simply exit
// 
//    Rev 1.1   Sep 20 2004 10:29:28   ZHANGCEL
// PET1094 -FN8 Adminfee enchancement
 */
