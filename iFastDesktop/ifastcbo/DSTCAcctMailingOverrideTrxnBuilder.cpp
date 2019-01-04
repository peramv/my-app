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
// ^FILE   : DSTCAcctMailingOverrideTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : January 21, 2003
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAcctMailingOverrideTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcAcctMailingOverrideTrxnbuilder.hpp"

#include "AcctMailingOverride.hpp"
#include "AcctMailingOverrideList.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0216_req.hpp>
#include <ifastdataimpl\dse_dstc0216_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0216_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_MAILING_OVERRIDE_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME         = I_( "DSTCAcctMailingOverrideTrxnBuilder" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
SEVERITY DSTCAcctMailingOverrideTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);

   AcctMailingOverrideList  *pAcctMailingOverrideList  = NULL;


   if( pMFaccount )
   {
      DString dstAccountNum, dstTrnKey, dstKeyTypes;
      pMFaccount->getField( ifds::AccountNum, dstAccountNum, BF::HOST, true );
      addIDITagValue( dstTrnKey,   TRXNTAG::ACCTMAILINGOVERRIDETAG, dstAccountNum.stripLeading('0').strip() );
	  addIDITagValue( dstTrnKey, TRXNTAG::ACCTTAG, dstAccountNum );

      HostTransactionContainerIterator iterTrxnContList( pTrCont );

      iterTrxnContList.walkStrKey( dstTrnKey );
      iterTrxnContList.walkTrxnGroup( NO_GROUP );
      iterTrxnContList.walkTrxnSubType( 0 );

      if (pMFaccount->getAcctMailingOverrideList(pAcctMailingOverrideList, BF::HOST, false) <= WARNING && pAcctMailingOverrideList)
      {
         BFData *pDataReq = NULL;
         BFData *pDataRes = NULL;

         BFObjIter iter( *pAcctMailingOverrideList, BF::HOST );
         AcctMailingOverride* pAcctMailingOverride = NULL;

         iter.begin();
         while( !iter.end() )
         {
            pAcctMailingOverride = dynamic_cast<AcctMailingOverride*>( iter.getObject() );

            if( iter.hasTransactionUpdates() )
            {
               iterTrxnContList.begin();

               //fill in the fixed area
               if( iterTrxnContList.end() )
               {
				  TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_MAILING_OVERRIDE : UPDATE_MAILING_OVERRIDE;

                  pDataReq = new BFData( ifds::DSTC0216_REQ );
                  pDataRes = new BFData( ifds::DSTC0216_VW );

                  DString strTrack, strActivity;

                  pAcctMailingOverrideList->getTrackActivity(strTrack,strActivity);         
                  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                  //fill in the request update
                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
                  pDataReq->setElementValue( ifds::AccountNum, dstAccountNum );

                  JData *jdata = new JData( DSTC_REQUEST::ACCT_MAILING_OVERRIDE_UPDATE, pDataReq, pDataRes );
                  pTrCont->addTransaction( dstTrnKey, jdata, objActivity, trxnType, dstKeyTypes );
               }
               else
                  pDataRes = (*iterTrxnContList)->getRequestDataObject();


               //create a repeat for the request and fill it in
               BFData repeat( ifds::DSTC0216_REQRepeat_Record);
               
               //fill in the request update
               pAcctMailingOverride->getData( repeat, BF::HOST );

               //set the RunMode field 
               DSTCWorkSession::setRunMode( &repeat, iter.getKey().getActivity() );

               //add the lDataRepeat to the request
               pDataReq->addRepeat( repeat );
               DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
               pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );
            }
            //move to the next AcctMailingOverride
            ++iter;
         } //meaning we have at least one AcctMailingOverride
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctMailingOverrideTrxnBuilder.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:31:14   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Apr 02 2003 13:21:58   FENGYONG
// Add acct mailing override update to persistent group
// 
//    Rev 1.1   Apr 02 2003 11:31:48   FENGYONG
// view no change
// 
//    Rev 1.0   Apr 02 2003 10:44:30   FENGYONG
// Initial Revision
// 
 */