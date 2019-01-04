//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2010 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : DSTCAcctGuaranteeGuardOptTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : Aug 2010
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAcctGuaranteeGuardOptTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "ifasthosttransactioncontainer.hpp"

#include "DSTCAcctGuaranteeGuardOptTrxnBuilder.hpp"
#include "AcctGuaranteeGuardOptList.hpp"
#include "AcctGuaranteeGuardOpt.hpp"
#include "MgmtCo.hpp"
#include "MFAccount.hpp"
#include "DSTCWorkSession.hpp"

#include <ifastdataimpl\dse_dstc0413_req.hpp>
#include <ifastdataimpl\dse_dstc0413_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_GUARNT_GUARD_OPTN_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCAcctGuaranteeGuardOptTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

//******************************************************************************
void DSTCAcctGuaranteeGuardOptTrxnBuilder::buildTrxnKey ( DString& dstrKey, BFAbstractCBO *pObj) 
{
   DString dstrAccountNum;

   pObj->getParent()->getParent()->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
   dstrAccountNum.stripLeading( '0' );
   dstrAccountNum.strip();

   //build the key
   addIDITagValue( dstrKey, TRXNTAG::ACCTGUARNTGUARDOPTNTAG, dstrAccountNum );
   addIDITagValue( dstrKey, KEYTYPES::ACCOUNTNUM, dstrAccountNum );
   addIDITagValue( dstrKey, TRXNTAG::ACCTTAG, dstrAccountNum );
}

//******************************************************************************
SEVERITY DSTCAcctGuaranteeGuardOptTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                                  BFAbstractCBO *pObj, 
                                                                  HostTransactionContainer *pTrCont, 
                                                                  BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);

   if (pMFaccount)
   {
      DString dstAccountNum, 
         dstTrnKey, 
         dstKeyTypes;

      pMFaccount->getField (ifds::AccountNum, dstAccountNum, BF::HOST, true);

      bool bIsGuarGuardAllowed = workSession.isGuarGuardAllowed(dstAccountNum, BF::HOST);
      AcctGuaranteeGuardOptList *pAcctGuaranteeGuardOptList = NULL;
      if (pMFaccount->getAcctGuaranteeGuardOptList(pAcctGuaranteeGuardOptList, BF::HOST, false) <= WARNING && 
          pAcctGuaranteeGuardOptList && bIsGuarGuardAllowed )
      {

		  BFObjIter bfIter( *pAcctGuaranteeGuardOptList, BF::HOST );
		  bfIter.begin();

		  while( !bfIter.end() )
		  {

			  AcctGuaranteeGuardOpt* pAcctGuaranteeGuardOpt = 
				dynamic_cast<AcctGuaranteeGuardOpt*>( bfIter.getObject() );
			  BF_OBJ_ACTIVITY lObjActivity = bfIter.getKey().getActivity();

			  if( pAcctGuaranteeGuardOpt != NULL && ( lObjActivity == OBJ_ACTIVITY_DELETED || 
				  lObjActivity == OBJ_ACTIVITY_ADDED || lObjActivity == OBJ_ACTIVITY_MODIFIED ||
				  pAcctGuaranteeGuardOpt->hasTransactionUpdates( false ) ) )
			  {
				  //define an iterator on the HostTransactionContainer
				  HostTransactionContainerIterator iterTrxnContList( pTrCont );

				  DString keyString;

				  buildTrxnKey( keyString, pAcctGuaranteeGuardOpt );

				  iterTrxnContList.walkStrKey( keyString );
				  //the trxn hasn't been handled yet, no group and sub type set,
				  iterTrxnContList.walkTrxnGroup( NO_GROUP );
				  iterTrxnContList.walkTrxnSubType( 0 );
				  //check if the fixed area of the 'Entity' update request is already in the HostTransactionContainer
				  iterTrxnContList.begin();
		  
				  BFData* pDataReq = NULL;
				  BFData* pDataRes = NULL;
				  
				  if( iterTrxnContList.end() )
					  // Fixed Area either does not exists, so create a new one
				  {
					  pDataReq   = new BFData( ifds::DSTC0413_REQ );
					  pDataRes   = new BFData( ifds::DSTC0413_VW );

					  DString strTrack,strActivity;
					  pAcctGuaranteeGuardOpt->getTrackActivity(strTrack,strActivity);
					  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
					  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

					  DString mgmtCoId;
					  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
					  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

					  DString keyTypes;
					  dstAccountNum.stripLeading( '0' );
					  dstAccountNum.strip();

                      addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum );

					  TRXN_TYPE trxnType = lObjActivity == OBJ_ACTIVITY_ADDED ? NEW_ACCOUNT_GUARNT_GUARD_OPTN : UPDATE_ACCOUNT_GUARNT_GUARD_OPTN;

					  //add the transaction to the container;
					  JData *jdata = new JData( DSTC_REQUEST::ACCT_GUARNT_GUARD_OPTN_UPDATE, pDataReq, pDataRes );
					  pTrCont->addTransaction( keyString, jdata, lObjActivity, trxnType, keyTypes );
				  }
				  else
				  {
					  pDataReq = (*iterTrxnContList)->getRequestDataObject();
				  }

				  DSTCWorkSession::setRunMode( pDataReq, lObjActivity );

				  pAcctGuaranteeGuardOpt->getData( *pDataReq, BF::HOST );
			  }

			  ++bfIter;
		  }
		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctGuaranteeGuardOptTrxnBuilder.cpp-arc  $
// 
//    Rev 1.0   Sep 17 2010 04:13:56   kitticha
// Initial revision.
//