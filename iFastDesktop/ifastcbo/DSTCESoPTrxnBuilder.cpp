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
// ^FILE   : DSTCESoPTrxnBuilder.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : September 17, 2001
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCESoPTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcesoptrxnbuilder.hpp"
#include "dstcmfaccounttrxnbuilder.hpp"
#include "esopinfo.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0168_req.hpp>
#include <ifastdataimpl\dse_dstc0168_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ESOP_INFO_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCESoPTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
void DSTCESoPTrxnBuilder::buildTrxnKey( DString& strKey, MFAccount* pMFAccount )
{
   DString dstrAccountNum;

   pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
   dstrAccountNum.stripLeading( '0' );
   dstrAccountNum.strip();
   //build the key
   addIDITagValue( strKey, TRXNTAG::ESOPTAG, dstrAccountNum );

}

//******************************************************************************
SEVERITY DSTCESoPTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                 BFAbstractCBO* pObj,
                                                 HostTransactionContainer* pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);
   ESoPInfo* pESoPInfo = NULL;

   //check if the ESoPInfo itself is updated,
   //do not ask the children (call hasTransactionUpdates with false)
   if( pMFAccount != NULL )
   {
      severity = pMFAccount->getESoPInfo( pESoPInfo, BF::HOST, false );

      if( pESoPInfo != NULL && severity <= WARNING && pESoPInfo->hasTransactionUpdates( ) )
      {

         //some fields have not been set
         DString strShrNum, strBrokerCode, strBranchCode, strSalesRep, strLastName, strFirstName, 
         dstrEntityName, dstrAccountNum;
         pMFAccount->getField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
         pMFAccount->getField(ifds::ShrNum, strShrNum, BF::HOST, false);
         pMFAccount->getField(ifds::BrokerCode, strBrokerCode, BF::HOST, false);
         pMFAccount->getField(ifds::BranchCode, strBranchCode, BF::HOST, false);
         pMFAccount->getField(ifds::Slsrep, strSalesRep, BF::HOST, false);
         workSession.getFirstSequenced01AccountholderEntityName( BF::HOST, dstrAccountNum, dstrEntityName);
         int nPos = dstrEntityName.pos( I_(";") );
         strLastName = dstrEntityName.substr(0, nPos);
         strFirstName = dstrEntityName.substr(nPos+1, dstrEntityName.length());

         pESoPInfo->setField(ifds::ShrNum, strShrNum.strip(), BF::HOST, false);
         pESoPInfo->setField(ifds::BrokerCode, strBrokerCode.strip(), BF::HOST, false);
         pESoPInfo->setField(ifds::BranchCode, strBranchCode.strip(), BF::HOST, false);
         pESoPInfo->setField(ifds::SalesRepCode, strSalesRep.strip(), BF::HOST, false);
         pESoPInfo->setField(ifds::LastName, strLastName.strip(), BF::HOST, false);
         pESoPInfo->setField(ifds::FirstName, strFirstName.strip(), BF::HOST, false);

         BFData *request = new BFData( ifds::DSTC0168_REQ );
         BFData *response = new BFData( ifds::DSTC0168_VW );

         DString strTrack,strAvtivity, mgmtCoId, keyTypes;
         pESoPInfo->getTrackActivity(strTrack,strAvtivity);
         pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
         dstrAccountNum.stripLeading( '0' );
         dstrAccountNum.strip();

         workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

         request->setElementValue( ifds::Track, strTrack, false, false );
         request->setElementValue( ifds::Activity, strAvtivity, false, false );
         request->setElementValue( ifds::AccountNum, dstrAccountNum, false, false );
         request->setElementValue( ifds::CompanyId, mgmtCoId );

         addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );   

         pESoPInfo->getData( *request, BF::HOST );
         BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE;//can't delete esop information once added;
         if( pESoPInfo->isNew() )
            objActivity = OBJ_ACTIVITY_ADDED;

         DSTCWorkSession::setRunMode( request, objActivity );

         DString strKey;

         DSTCESoPTrxnBuilder::buildTrxnKey( strKey, pMFAccount );

         TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_ESOP : UPDATE_ESOP;

         JData *jdata = new JData( DSTC_REQUEST::ESOP_INFO_UPDATE, request, response );
         pTrCont->addTransaction( strKey, jdata, objActivity, trxnType, keyTypes );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCESoPTrxnBuilder.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:32:22   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Mar 21 2003 18:05:28   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Oct 09 2002 23:54:20   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Aug 29 2002 12:55:30   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.2   22 May 2002 18:27:54   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   Feb 25 2002 18:55:30   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.0   19 Sep 2001 14:58:48   KOVACSRO
// Initial revision.
// 

 * 
 * 
*/