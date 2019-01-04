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
// ^FILE   : DSTCAsPensionPlanTrxnBuilder.cpp
// ^AUTHOR : Karen Jan
// ^DATE   : July 26, 2001
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAsPensionPlanTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcaspensionplantrxnbuilder.hpp"
#include "dstcmfaccounttrxnbuilder.hpp"
#include "aspensionplan.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0172_req.hpp>
#include <ifastdataimpl\dse_dstc0172_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AS_PENSION_PLAN_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCAsPensionPlanTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
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

//******************************************************************************
void DSTCAsPensionPlanTrxnBuilder::buildTrxnKey( DString& strKey, 
                                                 AsPensionPlan *pAsPensionPlan,
                                                 MFAccount* pMFAccount )
{
   DString dstrAccountNum;

   pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
   dstrAccountNum.stripLeading( '0' );
   dstrAccountNum.strip();
   //build the key
   addIDITagValue( strKey, TRXNTAG::ASPENSIONTAG, dstrAccountNum );

}

//******************************************************************************
SEVERITY DSTCAsPensionPlanTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                          BFAbstractCBO* pObj, 
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);
   AsPensionPlan* pAsPensionPlan = NULL;

   //check if the AsPensionPlan itself is updated,
   //do not ask the children (call hasTransactionUpdates with false)
   if( pMFAccount != NULL )
   {
      severity = pMFAccount->getAsPensionPlan( pAsPensionPlan, BF::HOST, false );
      // add a newone we should build up  transaction   
      if( pAsPensionPlan != NULL && severity <= WARNING && (pAsPensionPlan->isNew() || pAsPensionPlan->hasTransactionUpdates( ) ) )
      {

         BFData *request = new BFData( ifds::DSTC0172_REQ );
         BFData *response = new BFData( ifds::DSTC0172_VW );

         DString strTrack,strAvtivity, dstrAccountNum, mgmtCoId, keyTypes;
         pAsPensionPlan->getTrackActivity(strTrack,strAvtivity);
         pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
         dstrAccountNum.stripLeading( '0' );
         dstrAccountNum.strip();

         workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);


         addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );   

         pAsPensionPlan->getData( *request, BF::HOST );
         request->setElementValue( ifds::Track, strTrack, false, false );
         request->setElementValue( ifds::Activity, strAvtivity, false, false );
         request->setElementValue( ifds::AccountNum, dstrAccountNum, false, false );
         request->setElementValue( ifds::CompanyId, mgmtCoId );
         if( pAsPensionPlan->isNew() )
         {
            objActivity = OBJ_ACTIVITY_ADDED;
         }
         DSTCWorkSession::setRunMode( request, objActivity );

         DString strKey;

         DSTCAsPensionPlanTrxnBuilder::buildTrxnKey( strKey, pAsPensionPlan, pMFAccount );

         TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_AS_PENSION : UPDATE_AS_PENSION;

         JData *jdata = new JData( DSTC_REQUEST::AS_PENSION_PLAN_UPDATE, request, response );
         pTrCont->addTransaction( strKey, jdata, objActivity, trxnType, keyTypes );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAsPensionPlanTrxnBuilder.cpp-arc  $
// 
//    Rev 1.7   Nov 14 2004 14:31:38   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Mar 21 2003 18:04:20   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Oct 09 2002 23:54:16   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:55:22   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   22 May 2002 18:27:08   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   Feb 25 2002 18:55:20   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.1   Dec 27 2001 10:51:16   YINGBAOL
// fix transaction build error:
// 1. if the record is added, we should build a transaction
// 2. if the record is added, the runmode should be add
// 
//    Rev 1.0   Aug 23 2001 13:12:40   JANKAREN
// Initial revision.
 * 
 * 
*/