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
// ^FILE   : DSTCAccountCommitmentTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAccountCommitmentTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  : Create the transaction and put it into the container
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcaccountcommitmenttrxnbuilder.hpp"
#include "dstcmfshareholdertrxnbuilder.hpp"
#include "shareholder.hpp"
#include "accountcommitment.hpp"
#include "MFAccount.hpp"
#include "Entity.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0434_req.hpp>
#include <ifastdataimpl\dse_dstc0434_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_COMMIT_UPDATE;
}
namespace
{
   const I_CHAR* ACCT_COMMIT_CLASSNAME = I_( "DSTCAccountCommitmentTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
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
void DSTCAccountCommitmentTrxnBuilder::buildTrxnKey( DString& strKey, MFAccount *pMFAccount, AccountCommitment* pAccountCommitment)
{
   assert( pMFAccount != NULL );
   DString accountNum;

   //get the shareholder number off the sjareholder
   pMFAccount->getField( ifds::AccountNum, accountNum, BF::HOST, true );
   accountNum.stripLeading( '0' );
   accountNum.strip();
   //build the key
   addIDITagValue( strKey, TRXNTAG::ACCTCOMMTAG, accountNum );
}

//******************************************************************************
SEVERITY DSTCAccountCommitmentTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                         BFAbstractCBO* pObj,
                                                         HostTransactionContainer* pTrCont, 
                                                         BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, ACCT_COMMIT_CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* mfaccount = dynamic_cast<MFAccount*>(pObj);
   AccountCommitment* pAccountCommitment = NULL;

   if( mfaccount != NULL && mfaccount->isCommitmentApplicable (BF::HOST))
   {
      severity = mfaccount->getAccountCommitment( pAccountCommitment, BF::HOST, false);
      if( pAccountCommitment != NULL && severity <= WARNING && pAccountCommitment->hasTransactionUpdates( ) )
      {
         BFData* request = new BFData( ifds::DSTC0434_REQ );
         BFData* response = new BFData( ifds::DSTC0434_VW );
         DString strTrack,strAvtivity;
         pAccountCommitment->getTrackActivity(strTrack,strAvtivity);;

         request->setElementValue( ifds::Track, strTrack, false, false );
         request->setElementValue( ifds::Activity, strAvtivity, false, false );

         pAccountCommitment->getData( *request, BF::HOST );

//         DSTCWorkSession::setRunMode( request, objActivity );
         DString strKey;

         //get the string key for the demographics
         DSTCAccountCommitmentTrxnBuilder::buildTrxnKey( strKey, mfaccount, pAccountCommitment);

         DString mgmtCoId;
         workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
         request->setElementValue( ifds::CompanyId, mgmtCoId );


         DString keyTypes, accountNum;
         mfaccount->getField( ifds::AccountNum, accountNum, BF::HOST, true );
         accountNum.stripLeading( '0' );
         accountNum.strip();
         request->setElementValue( ifds::AccountNum, accountNum, false, false );

         addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, accountNum );

         JData *jdata = new JData( DSTC_REQUEST::ACCT_COMMIT_UPDATE, request, response );
         pTrCont->addTransaction( strKey, jdata, objActivity, NOT_PERSISTENT, keyTypes );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}




//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAccountCommitmentTrxnBuilder.cpp-arc  $
// 
//    Rev 1.1   Feb 28 2012 14:02:10   if991250
// do not send create acct commit if not applicable
// 
//    Rev 1.0   Feb 22 2012 17:04:54   if991250
// Initial revision.
 * 
// 
*/