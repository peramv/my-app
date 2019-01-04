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
// ^FILE   : DSTCAccountEntityTrxnBuilder.cpp
// ^AUTHOR : Serban Popescu & Adrian Vasile
// ^DATE   : October 1999
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCACCOUNTENTITYTRXNBUILDER
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "accountentityxref.hpp"
#include <ifastdataimpl\dse_dstc0077_req.hpp>
#include <ifastdataimpl\dse_dstc0077_vw.hpp>
#include "dstcaccountentitytrxnbuilder.hpp"
#include "dstcentityaddresstrxnbuilder.hpp"
#include "dstcentityaddressmailingtrxnbuilder.hpp"
#include "entity.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "DSTCommonFunction.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCOUNTENTITY_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCAccountEntityTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
   const I_CHAR* ACCOUNT_OWNER      = I_( "01" );
   const I_CHAR* RESP_BENEFICIARY   = I_( "50" );
   const I_CHAR* RELATED_PARTY      = I_( "71" );
   const I_CHAR* RELATED_PARTY_AML_ENTITY_TYPE = I_( "78" );
   const I_CHAR * const APPLICABLE_TO_ALL	= I_( "*" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId RepeatCount;
   extern CLASS_IMPORT const BFTextFieldId    CRSEntityList;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ENTITYID;
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

int DSTCAccountEntityTrxnBuilder::buildIndex = 0;

//******************************************************************************
void DSTCAccountEntityTrxnBuilder::buildTrxnKey( DString& dstStrKey, MFAccount* mfAccount )
{
   DString entityId, accountNum;

   mfAccount->getField( ifds::AccountNum, accountNum, BF::HOST, true );
   accountNum.stripLeading( '0' );
   accountNum.strip();
   //build the key
   addIDITagValue( dstStrKey, TRXNTAG::ACCTTAG, accountNum );
   addIDITagValue( dstStrKey, TRXNTAG::ACCTENTITYTAG, DString::asString( buildIndex++ ) );
}

//******************************************************************************
SEVERITY DSTCAccountEntityTrxnBuilder::buildTransactions( DSTCWorkSession &workSession, 
                                                          BFAbstractCBO* pObj, 
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   AccountEntityXref* pAccountEntityXref = dynamic_cast<AccountEntityXref*>(pObj);

   if( pAccountEntityXref != NULL )
   {
      BFObjIter iterAccountEntityXref( *pAccountEntityXref, BF::HOST, true );
      bool flg_upd = false;

      while( !iterAccountEntityXref.end() )
      {
         DString dstAccNum;
         DString keyTypes;
         const BFObjectKey& bfKey = iterAccountEntityXref.getKey();

         BFData* pDataReq; //= new Data( ifds::DSTC0077_REQ );
         BFData* pDataRes; //= new Data( ifds::DSTC0077_VW );

         if( iterAccountEntityXref.hasTransactionUpdates( ) )
         {
            //create an iterator which will walk the current account
            BFObjIter iterAccount( *pAccountEntityXref, BF::HOST, true );
            DString searchKey;

            AccountEntityXref::getValueForTag( bfKey.getStringKey(), I_( "AccountNum" ), dstAccNum );
            iterAccountEntityXref.getObject()->getField( ifds::AccountNum, dstAccNum, BF::HOST );
            AccountEntityXref::buildPartialKeyForAccount( searchKey, dstAccNum );
            iterAccount.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
            iterAccount.positionByKey( bfKey.getStringKey() );

            dstAccNum.stripLeading( '0' ).strip();
            addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, dstAccNum );

            int count = 0;
            bool bFirstTime = true;
            do
            {
               const BFObjectKey& bfAccKey = iterAccount.getKey();
               if( !iterAccount.end() && iterAccount.hasTransactionUpdates( ) )
               {

                  if( bFirstTime )
                  {
                     pDataReq    = new BFData( ifds::DSTC0077_REQ );
                     pDataRes    = new BFData( ifds::DSTC0077_VW );
                     bFirstTime  = false;
                  }

                  DString entityId,dstrEffectiveDate;
                  BFData repeat( ifds::DSTC0077_REQRepeat_Record );

                  iterAccount.getObject()->getField( ifds::EntityId, entityId, BF::HOST );
                  iterAccount.getObject()->getField( ifds::EffectiveDate, dstrEffectiveDate, BF::HOST );


                  //get values from the aexref object
                  BFCBO* pCBO = dynamic_cast< BFCBO* >( iterAccount.getObject() );
                  pCBO->getData( repeat, BF::HOST );

                  Entity* pEntity;

                  workSession.getEntity( BF::HOST, entityId, pEntity );
                  //get values from the entity object
                  pEntity->getData( repeat, BF::HOST );

                  pDataReq->setElementValue( ifds::EffectiveDate, dstrEffectiveDate, false, false );

                  DSTCWorkSession::setRunMode( &repeat, bfAccKey.getActivity() );
                  pDataReq->addRepeat( repeat );
                  count++;
                  entityId.stripLeading('0').strip();
                  addIDITagValue( keyTypes, KEYTYPES::ENTITYID, entityId );

                  // only resp benef which creating during NASU
                  if ( iterAccount.getObject()->isNew() )
                  {
                     DString strEntityType, strPCGId, strAssocEntityId;
                     iterAccount.getObject()->getField( ifds::EntityType, strEntityType, BF::HOST, false );
                     strEntityType.strip().upperCase();
                     
                     if ( strEntityType == RESP_BENEFICIARY )
                     {
                        iterAccount.getObject()->getField( ifds::RESPPCGId, strPCGId, BF::HOST, false );
                        addIDITagValue( keyTypes, I_("RESPPCGId"), strPCGId );
                     }
                     
                     DString dstrCRSEntityList;
					 workSession.getOption ( ifds::CRSEntityList, dstrCRSEntityList, BF::HOST, false);
                                          
                     if (strEntityType != ACCOUNT_OWNER && (DSTCommonFunctions::codeInList(strEntityType, dstrCRSEntityList) || dstrCRSEntityList == APPLICABLE_TO_ALL || strEntityType == RELATED_PARTY_AML_ENTITY_TYPE))
                     {
						 iterAccount.getObject()->getField(ifds::AssocEntityId, strAssocEntityId, BF::HOST, false);
						 if((!strAssocEntityId.stripLeading('0').strip().empty()))
							 addIDITagValue( keyTypes, I_("ASSOCENTITYId"), strAssocEntityId );
                     }
                  }
               }
               ++iterAccount;
               ++iterAccountEntityXref;
               flg_upd = true;
            } while( !iterAccount.end() );
            pDataReq->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
         }
         if( !flg_upd )
            ++iterAccountEntityXref;
         else
         {

            DString dstTrack, dstActivity;
            pAccountEntityXref->getTrackActivity(dstTrack, dstActivity);
            pDataReq->setElementValue( ifds::Track,    dstTrack,    false, false );
            pDataReq->setElementValue( ifds::Activity, dstActivity, false, false );

            DString mgmtCoId;
            workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
            pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

            DString dstStrKey;
            MFAccount* pMFAccount;
            workSession.getMFAccount( BF::HOST, dstAccNum, pMFAccount );
            //get the string key for the entity
            DSTCAccountEntityTrxnBuilder::buildTrxnKey( dstStrKey, pMFAccount );
            pDataReq->setElementValue( ifds::AccountNum, dstAccNum, false, false );

            TRXN_TYPE trxnType = bfKey.getActivity() == OBJ_ACTIVITY_ADDED ? NEW_ACCOUNT_ENTITY : UPDATE_ACCOUNT_ENTITY;
            //add the transaction to the container; the right side of the XchgData
            JData *pJData = new JData( DSTC_REQUEST::ACCOUNTENTITY_UPDATE, pDataReq, pDataRes );
            pTrCont->addTransaction( dstStrKey, pJData, bfKey.getActivity(), trxnType, keyTypes );

            // Entity Address
            DSTCEntityAddressTrxnBuilder::buildTransactions( workSession, pAccountEntityXref, pTrCont, objActivity );
            // build the Account entity mailing info transaction.
            DSTCEntityAddressMailingTrxnBuilder::buildTransactions( workSession, pAccountEntityXref, pTrCont, objActivity );			
            flg_upd = false;
         }
         //delete acctEntityUpdate;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAccountEntityTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.18   Mar 23 2010 13:46:38   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.17   Mar 16 2005 11:11:36   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.16   Nov 14 2004 14:31:08   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.15   Mar 21 2003 18:03:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Oct 09 2002 23:54:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.13   Sep 17 2002 10:10:34   HSUCHIN
 * added account entity mailing builder
 * 
 *    Rev 1.12   Aug 29 2002 12:55:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.11   22 May 2002 18:26:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.10   Feb 25 2002 18:55:14   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.9   Oct 30 2001 15:44:14   YINGBAOL
 * fix effective date
 * 
 *    Rev 1.8   Sep 21 2001 16:10:00   YINGBAOL
 * fix memory leak
 * 
 *    Rev 1.7   23 May 2001 14:39:56   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.6   03 May 2001 14:06:10   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   09 Mar 2001 18:03:46   BUZILAMI
 * XchgData elimination fixes
 * 
 *    Rev 1.4   09 Feb 2001 15:01:06   SMITHDAV
 * Removed commented code; Removed unneeded includes; Some fixes.
 * 
 *    Rev 1.3   Jan 31 2001 16:10:50   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.2   Jan 16 2001 13:53:04   OLTEANCR
 * changed buildTransaction(..)
 * 
 *    Rev 1.1   Dec 17 2000 20:22:58   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Feb 15 2000 10:59:52   SMITHDAV
 * Initial revision.
// 
//    Rev 1.19   Feb 03 2000 10:51:54   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.18   Feb 02 2000 10:33:52   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.17   Jan 23 2000 19:34:26   VASILEAD
// Reset functionality
// 
//    Rev 1.16   Jan 21 2000 11:11:48   POPESCUS
// the user can change the account number and the shareholder number
// 
//    Rev 1.15   Dec 24 1999 15:18:22   VASILEAD
// Fixed transactions
// 
//    Rev 1.14   Dec 17 1999 18:49:00   POPESCUS
// fixes related to the commit logic
// 
//    Rev 1.13   Dec 12 1999 17:55:04   POPESCUS
// Delete the XchgData object and minor fixes
// 
*/