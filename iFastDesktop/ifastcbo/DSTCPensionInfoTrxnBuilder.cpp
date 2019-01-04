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
//    Copyright 2001 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCPensionInfoTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : May 30, 2002
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCPensionInfoTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  : 
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "pensioninfo.hpp"
#include "dstcpensioninfotrxnbuilder.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0203_req.hpp>
#include <ifastdataimpl\dse_dstc0203_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PENSION_INFO_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCPensionInfoTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

const BFFieldId fieldsInPensionInfo[]=
{
   ifds::PenSourceLine1,
   ifds::PenSourceLine2,
   ifds::PenSourceLine3,
   ifds::EffectiveDate,
   ifds::MinWithAge,
   ifds::UniSexPer,
   ifds::SexDistinctPer,
   ifds::LIPPenInfoVer,
   ifds::LIPPenInfoRid,
};
static const int numFieldsInPensionInfo = sizeof( fieldsInPensionInfo ) / sizeof( BFFieldId );

int DSTCPensionInfoTrxnBuilder::buildIndex = 0;

//******************************************************************************
void DSTCPensionInfoTrxnBuilder::buildTrxnKey( DString& dstStrKey, MFAccount* mfAccount )
{
   DString dstrAccountNum;

   mfAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
   dstrAccountNum.stripLeading( '0' );
   dstrAccountNum.strip();
   //build the key
   addIDITagValue( dstStrKey, TRXNTAG::ACCTTAG, dstrAccountNum );
   addIDITagValue( dstStrKey, TRXNTAG::PENSIONINFOPARAMTAG, DString::asString( buildIndex++ ) );
}

//******************************************************************************
SEVERITY DSTCPensionInfoTrxnBuilder::buildTransactions( DSTCWorkSession &workSession, 
                                                        BFAbstractCBO* pObj, 
                                                        HostTransactionContainer* pTrCont, 
                                                        BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);

   if( pMFAccount != NULL )
   {
      PensionInfo *pPensionInfo = NULL;
      SEVERITY severity = SEVERE_ERROR;      

      //do not retrieve list from database.
      severity = pMFAccount->getPensionInfo ( pPensionInfo, BF::HOST, false);

      if( severity <= WARNING && pPensionInfo )
      {
         DString dstrTrack,dstrActivity, dstrAccountNum, dstrMgmtCo, dstrStrKey, dstrKeyTypes, dstrShrNum;

         buildTrxnKey( dstrStrKey, pMFAccount );
         BFData* pRequest = new BFData( ifds::DSTC0203_REQ );
         BFData* pResponse = new BFData( ifds::DSTC0203_VW );
         pMFAccount->getField ( ifds::AccountNum, dstrAccountNum, BF::HOST );
         pMFAccount->getField ( ifds::ShrNum, dstrShrNum, BF::HOST );
         pPensionInfo->getTrackActivity( dstrTrack,dstrActivity );                         
         workSession.getMgmtCo().getField(ifds::CompanyId, dstrMgmtCo, BF::HOST);
         pRequest->setElementValue( ifds::CompanyId, dstrMgmtCo );
         pRequest->setElementValue( ifds::Track, dstrTrack, false, false );
         pRequest->setElementValue( ifds::Activity, dstrActivity, false, false );         
         pRequest->setElementValue( ifds::AccountNum, dstrAccountNum, false, false );
         pRequest->setElementValue( ifds::ShrNum, dstrShrNum, false, false );

         addIDITagValue( dstrKeyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );

         JData *jdata = new JData( DSTC_REQUEST::PENSION_INFO_UPDATE, pRequest, pResponse );
         pTrCont->addTransaction( dstrStrKey, jdata, objActivity, UPDATE_ACCOUNT, dstrKeyTypes );
         if( pPensionInfo )
         {
            fillingData( pPensionInfo, pRequest, fieldsInPensionInfo, numFieldsInPensionInfo );
            if( pPensionInfo->isNew() )
               objActivity = OBJ_ACTIVITY_ADDED;
            DSTCWorkSession::setRunMode( pRequest, objActivity );
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void DSTCPensionInfoTrxnBuilder::fillingData( BFCBO* pObj, BFData* data, const BFFieldId fieldIds[], int numFields )
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCPensionInfoTrxnBuilder.cpp-arc  $
// 
//    Rev 1.5   Nov 14 2004 14:33:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   Mar 21 2003 18:06:22   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Oct 09 2002 23:54:22   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Aug 29 2002 12:55:34   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.1   Jun 11 2002 21:32:26   HSUCHIN
// fixed shareholder number bug
// 
//    Rev 1.0   Jun 03 2002 09:54:38   HSUCHIN
// Initial revision.
*/