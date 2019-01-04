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
//    Copyright 2002 by Internantial Financial
//
//
//******************************************************************************
//
// ^FILE   : DSTCFeeParamTrxnBuilder.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : January 30, 2002
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCFeeParamTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcfeeparamtrxnbuilder.hpp"
#include "dstcmfaccounttrxnbuilder.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0196_req.hpp>
#include <ifastdataimpl\dse_dstc0196_vw.hpp>
#include "feeparamlist.hpp"
#include "feeparam.hpp"
#include "feescale.hpp"
#include "feescalelist.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCFeeParamTrxnBuilder" );
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

void DSTCFeeParamTrxnBuilder::buildTrxnKey( DString& strKey, FeeParam* pFeeParam, MFAccount* mfAccount )
{
   DString dstrAccountnum, dstrFeeCode;
   DString dstrFundcode;
   DString dstrClasscode;
   DString dstrEffdate,dstrCommGroup;

   mfAccount->getField( ifds::AccountNum, dstrAccountnum, BF::HOST, true );
   dstrAccountnum.stripLeading( '0' );
   dstrAccountnum.strip();
   addIDITagValue( strKey, TRXNTAG::FEEPARAMTAG, dstrAccountnum );

   //FeeCode
   pFeeParam->getField( ifds::FeeCode, dstrFeeCode, BF::HOST, true );
   dstrFeeCode.strip();
   addIDITagValue( strKey, TRXNTAG::FEETAG, dstrFeeCode );

   //FundCode
   pFeeParam->getField( ifds::FundCode, dstrFundcode, BF::HOST, true );
   dstrFundcode.strip();
   addIDITagValue( strKey, TRXNTAG::FUNDTAG, dstrFundcode );

   //ClassCode
   pFeeParam->getField( ifds::ClassCode, dstrClasscode, BF::HOST, true );
   dstrClasscode.strip();
   addIDITagValue( strKey, TRXNTAG::CLASSTAG, dstrClasscode );

   //EffectiveDate
   pFeeParam->getField( ifds::EffectiveDate, dstrEffdate, BF::HOST, true );
   dstrEffdate.strip();
   addIDITagValue( strKey, TRXNTAG::EFFDATETAG, dstrEffdate );
   
// Commission Group

   pFeeParam->getField( ifds::CommGroup, dstrCommGroup, BF::HOST, true );
   dstrEffdate.strip();
   addIDITagValue( strKey, TRXNTAG::COMMGROUPTAG, dstrCommGroup );



	
//


}

//******************************************************************************
SEVERITY DSTCFeeParamTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                     BFCBO* pObj, 
                                                     HostTransactionContainer* pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);
   FeeParamList* pFeeParamList = NULL;

   if( pMFAccount != NULL )
   {
      severity = pMFAccount->getFeeParamList( pFeeParamList, BF::HOST, false );
      int count = 0;
      if( pFeeParamList != NULL && severity <= WARNING )
      {
         DString dstrAccountNum;
         pMFAccount->getField(ifds::AccountNum, dstrAccountNum, BF::HOST);


         BFObjIter iterFeeParamList( *pFeeParamList, BF::HOST );
         while( !iterFeeParamList.end() )
         {
            FeeParam* pFeeParam = dynamic_cast<FeeParam*>( iterFeeParamList.getObject() );
            BF_OBJ_ACTIVITY listObjActivity = iterFeeParamList.getKey().getActivity();

            if( pFeeParam != NULL && (listObjActivity == OBJ_ACTIVITY_ADDED || pFeeParam->hasTransactionUpdates( ) || listObjActivity == OBJ_ACTIVITY_DELETED ) )
            {

               DString strKey;

               BFData *request = new BFData( ifds::DSTC0196_REQ );
               BFData *response = new BFData( ifds::DSTC0196_VW );
               DString strTrack, strActivity;
               pFeeParamList->getTrackActivity(strTrack,strActivity);                     
               request->setElementValue( ifds::Track, strTrack, false, false );
               request->setElementValue( ifds::Activity, strActivity, false, false );

               DString mgmtCoId;
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               request->setElementValue( ifds::CompanyId, mgmtCoId );

               int count = 0;

               DSTCFeeParamTrxnBuilder::buildTrxnKey( strKey, pFeeParam, pMFAccount );

               //define an iterator on the HostTransactionContainer
               HostTransactionContainerIterator iterTrxnContList( pTrCont );

               // look for the systematic record in the HostTransactionContainer
               iterTrxnContList.walkStrKey( strKey );
               //the trxn hasn't been handled yet, no group and sub type set,
               iterTrxnContList.walkTrxnGroup( NO_GROUP );
               iterTrxnContList.walkTrxnSubType( 0 );
               iterTrxnContList.begin();

               pFeeParam->getData( *request, BF::HOST ); 
               request->setElementValue( ifds::AccountNum, dstrAccountNum, false, false );
               DSTCWorkSession::setRunMode( request, listObjActivity );
               DString keyTypes;

               addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );

               JData *jdata = new JData( DSTC_REQUEST::FEE_PARAM_UPDATE, request, response );
               pTrCont->addTransaction( strKey, jdata, listObjActivity, NOT_PERSISTENT, keyTypes );

               FeeScaleList *pFeeScaleList = NULL;
               SEVERITY sevRtn1 = pFeeParam->getFeeScaleList( pFeeScaleList, BF::HOST );                     
               severity = std::max( severity, sevRtn1 );
               if( pFeeScaleList != NULL &&  severity <= WARNING )
               {
                  BFObjIter iterFeeScaleList( *pFeeScaleList, BF::HOST );
                  while( !iterFeeScaleList.end() )
                  {
                     FeeScale* pFeeScale = dynamic_cast<FeeScale*>( iterFeeScaleList.getObject() );
                     BF_OBJ_ACTIVITY listObjActivityChild = iterFeeScaleList.getKey().getActivity();
                     if( pFeeScale != NULL && (listObjActivityChild == OBJ_ACTIVITY_ADDED || 
                                               pFeeScale->hasTransactionUpdates( ) || listObjActivityChild == OBJ_ACTIVITY_DELETED ) )
                     {
                        BFData dataRepeat(ifds::DSTC0196_REQRepeat_Record);

                        pFeeScale->getData(dataRepeat, BF::HOST);

                        DString dstrRunMode = 
                        DSTCWorkSession::getRunMode( listObjActivityChild, pFeeScale->hasTransactionUpdates( ));                                      

                        dataRepeat.setElementValue( ifds::ScaleRunMode,dstrRunMode );


                        //DSTCWorkSession::setRunMode( &dataRepeat, listObjActivity );
                        request->addRepeat(dataRepeat);
                        ++ count; 

                     }
                     ++iterFeeScaleList;
                  } //while FeeScaleList iterater  
                  request->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
               }
            }
            ++iterFeeParamList;        
         }// end of while iterFeeParamList
      }//end of if pFeeParamList	
   }//end of if pMFAccount

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCFeeParamTrxnBuilder.cpp-arc  $
// 
//    Rev 1.8   Nov 14 2004 14:32:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.7   Nov 07 2003 15:14:44   linmay
// PTS Ticket #10023545, add FeeCode to transaction key 
// 
//    Rev 1.6   Jul 22 2003 11:40:02   YINGBAOL
// add commgroup to transaction key
// 
//    Rev 1.5   Mar 21 2003 18:05:40   PURDYECH
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
//    Rev 1.1   Feb 22 2002 14:19:10   YINGBAOL
// fix repeatcount etc..
// 
//    Rev 1.0   Feb 01 2002 15:18:14   YINGBAOL
// Initial revision.
// 

*/