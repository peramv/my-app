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
//    Copyright 2002 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : DSTCEntityAddressMailingTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : Sept 11, 2002
//
// ^CLASS    : DSTCEntityAddressMailingTrxnBuilder
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcentityaddressmailingtrxnbuilder.hpp"
#include "accountentityxref.hpp"
#include <ifastdataimpl\dse_dstc0216_vw.hpp>
#include <ifastdataimpl\dse_dstc0216_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0216_req.hpp>
#include "entityaddressmailinglist.hpp"
#include "entityaddressmailinginfo.hpp"
#include "accountentityxrefobject.hpp"
#include "mgmtco.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITYADDRESSMAILING_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCEntityAddressMailingTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{      
   extern CLASS_IMPORT const BFNumericFieldId SeqNumber;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

const BFFieldId fieldsInEntityAddressMailingInfo[]=
{
   ifds::EntityType,
   ifds::EntityTypeSeq,
   ifds::DocumentType,
   ifds::EntityAddrCode,
   ifds::Suppress,
   ifds::DeliveryOption,
   ifds::DelOptnRecId,
   ifds::DelOptnVersion,
   ifds::Consent,
   ifds::OnHold,
   ifds::AuthCode,
   ifds::Mail,
   ifds::Fax,
   ifds::CD,
   ifds::LEmail,
   ifds::EPost,
};
static const int numfieldsInEntityAddressMailingInfo = sizeof( fieldsInEntityAddressMailingInfo ) / sizeof( BFFieldId );

int DSTCEntityAddressMailingTrxnBuilder::buildIndex = 0;

//******************************************************************************
void DSTCEntityAddressMailingTrxnBuilder::buildTrxnKey( DString& strKey, 
                                                        DString& dstrAccountNum )
                                                     
{     
   addIDITagValue( strKey, TRXNTAG::ACCTTAG, dstrAccountNum );
   addIDITagValue( strKey, TRXNTAG::ACCTENTITYADDRMAILTAG, DString::asString( buildIndex++ ) );  
}

//******************************************************************************
SEVERITY DSTCEntityAddressMailingTrxnBuilder::buildTransactions( DSTCWorkSession &workSession, 
                                                        BFAbstractCBO* pObj, 
                                                        HostTransactionContainer* pTrCont, 
                                                        BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );   
   AccountEntityXref* pAccountEntityXref = dynamic_cast<AccountEntityXref*>(pObj);

   if ( pAccountEntityXref != NULL ) {
      BFObjIter iterAccountEntityXref ( *pAccountEntityXref, BF::HOST, true );
      while ( !iterAccountEntityXref.end() ) {
         if ( iterAccountEntityXref.getObject()->hasTransactionUpdates() ) {
            AccountEntityXrefObject* pAccountEntityXrefObject = dynamic_cast <AccountEntityXrefObject*> (iterAccountEntityXref.getObject());
            EntityAddressMailingList *pEntityAddressMailingList = NULL;
            pAccountEntityXrefObject->getEntityMailingList ( pEntityAddressMailingList, BF::HOST, false );
            //If exists then update may occur.
            if ( pEntityAddressMailingList && pEntityAddressMailingList->hasTransactionUpdates ( true ) ) {
               DString dstrAccountNum, dstrStrKey, dstrMgmtCo, dstrTrack,dstrActivity;
               DString dstrEntityType, dstrEntityTypeSeq;
               //Lets get the key for the current AccountEntityXref.                       
               iterAccountEntityXref.getObject()->getField( ifds::AccountNum, dstrAccountNum, BF::HOST );
               iterAccountEntityXref.getObject()->getField( ifds::EntityType, dstrEntityType, BF::HOST );
               iterAccountEntityXref.getObject()->getField( ifds::SeqNumber, dstrEntityTypeSeq, BF::HOST );               
               buildTrxnKey ( dstrStrKey, dstrAccountNum );
               BFData* pRequest = new BFData( ifds::DSTC0216_REQ );
               BFData* pResponse = new BFData( ifds::DSTC0216_VW );
               workSession.getMgmtCo().getField(ifds::CompanyId, dstrMgmtCo, BF::HOST);
               pEntityAddressMailingList->getTrackActivity( dstrTrack,dstrActivity );	                        
               pRequest->setElementValue( ifds::CompanyId, dstrMgmtCo );
			      pRequest->setElementValue( ifds::Track, dstrTrack, false, false );
			      pRequest->setElementValue( ifds::Activity, dstrActivity, false, false );
               pRequest->setElementValue( ifds::AccountNum, dstrAccountNum, false, false );
               JData *jdata = new JData( DSTC_REQUEST::ENTITYADDRESSMAILING_UPDATE, pRequest, pResponse );
               pTrCont->addTransaction( dstrStrKey, jdata, objActivity, UPDATE_ACCOUNT_ENTITY, dstrStrKey );                                  
               int count = 0;
               BFObjIter iterEntityAddressMailingList ( *pEntityAddressMailingList, BF::HOST, true );
               while ( !iterEntityAddressMailingList.end() ) {
                  EntityAddressMailingInfo *pEntityAddressMailingInfo = dynamic_cast <EntityAddressMailingInfo*> ( iterEntityAddressMailingList.getObject() );
                  if ( pEntityAddressMailingInfo ->hasTransactionUpdates() || 
                       iterEntityAddressMailingList.getKey().getActivity() == OBJ_ACTIVITY_DELETED || 
                       iterEntityAddressMailingList.getKey().getActivity() == OBJ_ACTIVITY_ADDED ) {
                     BFData dataRepeat ( ifds::DSTC0216_REQRepeat_Record );
                     fillingData( pEntityAddressMailingInfo, &dataRepeat, fieldsInEntityAddressMailingInfo, numfieldsInEntityAddressMailingInfo );
                     DSTCWorkSession::setRunMode( &dataRepeat, iterEntityAddressMailingList.getKey().getActivity() );
                     pRequest->addRepeat( dataRepeat );
                     ++count;
                  }
                  ++iterEntityAddressMailingList;
               }
               pRequest->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
            }
         }
         ++iterAccountEntityXref;
      }
   }  
   return (GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void DSTCEntityAddressMailingTrxnBuilder::fillingData( BFCBO* pObj, BFData* data, const BFFieldId fieldIds[], int numFields )
{
	DString value;
	for( int i=0; i< numFields; ++i )
	{
		pObj->getField( fieldIds[i], value, BF::HOST, false);
		data->setElementValue( fieldIds[i], value, false, false );
	}
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCEntityAddressMailingTrxnBuilder.cpp-arc  $
// 
//    Rev 1.8   Sep 29 2005 10:49:34   yingbaol
// PET1277-FN09: Investment Fund Continuous Disclosure
// 
//    Rev 1.7   Dec 02 2004 11:36:56   yingbaol
// PET1137,FN01: Add Epost functionality.
// 
//    Rev 1.6   Nov 14 2004 14:32:14   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Mar 21 2003 18:05:02   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Oct 30 2002 10:10:46   YINGBAOL
// Sync. up from old PVCS database
// 
//    Rev 1.5   Oct 15 2002 10:36:06   HUANGSHA
// added the field CONSENT
// 
//    Rev 1.4   Oct 11 2002 11:37:36   YINGBAOL
// change AddrCode to EntityAddrCode
// 
//    Rev 1.3   Oct 11 2002 11:18:32   HUANGSHA
// hasTransaction.. set to true
// 
//    Rev 1.2   Sep 23 2002 14:34:18   HSUCHIN
// bug fix for add/deleted records not being sent
// 
//    Rev 1.1   Sep 20 2002 16:11:22   HSUCHIN
// bug fix
// 
//    Rev 1.0   Sep 17 2002 10:11:46   HSUCHIN
// Initial revision.
*/