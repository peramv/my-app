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
//    Copyright 2003 by Internantial Financial
//
//
//******************************************************************************
//
// ^FILE   : DSTCFeeParamSysTxnBuilder.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : January 16, 2003
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCFeeParamSysTxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "DSTCFeeParamSysTxnBuilder.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0232_req.hpp>
#include <ifastdataimpl\dse_dstc0232_vw.hpp>
#include "FeeParamSysSearchCriteria.hpp"
#include "FeeParamSysList.hpp"
#include "FeeParamSys.hpp"
#include "FeeScaleSys.hpp"
#include "FeeScaleSysList.hpp"
#include "FeeThrshldSysList.hpp"
#include "FeeThrshldSys.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM_SYSTEM_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCFeeParamSysTxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
   const I_CHAR* REC_TYPE_SCALE     = I_( "S" );
   const I_CHAR* REC_TYPE_THRESHOLD = I_( "T" );

}

namespace FEETYPE
{
   const I_CHAR * const FLAT                 = I_( "0" );
   const I_CHAR * const PERCENTAGE           = I_( "1" );
   const I_CHAR * const SCALE                = I_( "2" );
   const I_CHAR * const TIER                 = I_( "3" );
   const I_CHAR * const TIER_BY_THRESHOLD    = I_( "4" );
   const I_CHAR * const SCALE_BY_THRESHOLD   = I_( "5" );
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

int DSTCFeeParamSysTxnBuilder::buildIndex = 0;


//******************************************************************************

void DSTCFeeParamSysTxnBuilder::buildTrxnKey( DString& strKey, FeeParamSys* pFeeParam  )
{
   DString dstrFundcode,dstrFeeCode,dstrCommGroup;
   DString dstrClasscode;
   DString dstrEffdate;

   pFeeParam->getField( ifds::FeeCode, dstrFeeCode, BF::HOST, true );
   dstrFeeCode.strip();
   addIDITagValue( strKey, TRXNTAG::FEETAG, dstrFeeCode );
/*
   //FundCode
   pFeeParam->getField( ifds::FundCode, dstrFundcode, BF::HOST, true );
   dstrFundcode.strip();
   addIDITagValue( strKey, TRXNTAG::FUNDTAG, dstrFundcode );

   //ClassCode
   pFeeParam->getField( ifds::ClassCode, dstrClasscode, BF::HOST, true );
   dstrClasscode.strip();
   addIDITagValue( strKey, TRXNTAG::CLASSTAG, dstrClasscode );

   pFeeParam->getField( ifds::CommGroup, dstrCommGroup, BF::HOST, true );
   dstrCommGroup.strip();
   addIDITagValue( strKey, TRXNTAG::COMMGROUPTAG, dstrCommGroup );

   //EffectiveDate
   pFeeParam->getField( ifds::EffectiveDate, dstrEffdate, BF::HOST, true );
   dstrEffdate.strip();
   addIDITagValue( strKey, TRXNTAG::EFFDATETAG, dstrEffdate );   
*/
   addIDITagValue( strKey, TRXNTAG::FEEPARAMSYSTAG, DString::asString( buildIndex++ ) );

}

//******************************************************************************
SEVERITY DSTCFeeParamSysTxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                     BFAbstractCBO* pObj, 
                                                     HostTransactionContainer* pTrCont,
																	  BF_OBJ_ACTIVITY objActivity
																	  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   FeeParamSysSearchCriteria* pFeeParamSysSearchCriteria = dynamic_cast<FeeParamSysSearchCriteria*>(pObj);
   FeeParamSysList* pFeeParamSysList = NULL;

   if( pFeeParamSysSearchCriteria )
   {
      severity = pFeeParamSysSearchCriteria->GetFeeParamSysList( pFeeParamSysList, BF::HOST, false,false );
      int count = 0;
      if( pFeeParamSysList != NULL && severity <= WARNING )
      {


         BFObjIter iterFeeParamList( *pFeeParamSysList, BF::HOST );
         while( !iterFeeParamList.end() )
         {
            FeeParamSys* pFeeParamSys = dynamic_cast<FeeParamSys*>( iterFeeParamList.getObject() );
            BF_OBJ_ACTIVITY listObjActivity = iterFeeParamList.getKey().getActivity();

            if( pFeeParamSys != NULL && (listObjActivity == OBJ_ACTIVITY_ADDED || pFeeParamSys->hasTransactionUpdates( ) || listObjActivity == OBJ_ACTIVITY_DELETED ) )
            {

               DString strKey;

               BFData *request = new BFData( ifds::DSTC0232_REQ );
               BFData *response = new BFData( ifds::DSTC0232_VW );
               DString strTrack, strActivity;
               pFeeParamSysList->getTrackActivity(strTrack,strActivity);                     
               request->setElementValue( ifds::Track, strTrack, false, false );
               request->setElementValue( ifds::Activity, strActivity, false, false );

               DString mgmtCoId;
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               request->setElementValue( ifds::CompanyId, mgmtCoId );

               int count = 0;

               DSTCFeeParamSysTxnBuilder::buildTrxnKey( strKey, pFeeParamSys );

               //define an iterator on the HostTransactionContainer
               HostTransactionContainerIterator iterTrxnContList( pTrCont );

               // look for the systematic record in the HostTransactionContainer
               iterTrxnContList.walkStrKey( strKey );
               //the trxn hasn't been handled yet, no group and sub type set,
               iterTrxnContList.walkTrxnGroup( NO_GROUP );
               iterTrxnContList.walkTrxnSubType( 0 );
               iterTrxnContList.begin();

               pFeeParamSys->getData( *request, BF::HOST ); 
               DSTCWorkSession::setRunMode( request, listObjActivity );
               DString keyTypes;

               JData *jdata = new JData( DSTC_REQUEST::FEE_PARAM_SYSTEM_UPDATE, request, response );
               pTrCont->addTransaction( strKey, jdata, listObjActivity, NOT_PERSISTENT, keyTypes );

               FeeScaleBaseList *pFeeScaleList = NULL;
               DString dstrFeeType;
               DString basedOn;
               pFeeParamSys->getField(ifds::ParamFeeType, dstrFeeType, BF::HOST, false);
               pFeeParamSys->getField (ifds::BasedOn, basedOn, BF::HOST, false);

               bool bShowScale = dstrFeeType == FEETYPE::SCALE || dstrFeeType == FEETYPE::TIER || 
                (dstrFeeType == FEETYPE::PERCENTAGE && basedOn == I_("6")); //investment term
               bool bShowThreshold = dstrFeeType == FEETYPE::TIER_BY_THRESHOLD ||
                  dstrFeeType == FEETYPE::SCALE_BY_THRESHOLD;

               if(bShowScale)
               {
                  SEVERITY sevRtn1 = pFeeParamSys->getFeeScaleList( pFeeScaleList, BF::HOST,false );                     
                  severity = std::max( severity, sevRtn1 );
                  if( pFeeScaleList != NULL &&  severity <= WARNING )
                  {
                     BFObjIter iterFeeScaleList( *pFeeScaleList, BF::HOST );
                     while( !iterFeeScaleList.end() )
                     {
                        FeeScaleSys* pFeeScaleSys = dynamic_cast<FeeScaleSys*>( iterFeeScaleList.getObject() );
                        BF_OBJ_ACTIVITY listObjActivityChild = iterFeeScaleList.getKey().getActivity();
                        if( pFeeScaleSys != NULL && (listObjActivityChild == OBJ_ACTIVITY_ADDED || 
                                                pFeeScaleSys->hasTransactionUpdates( ) || listObjActivityChild == OBJ_ACTIVITY_DELETED ) )
                        {
                           BFData dataRepeat(ifds::DSTC0232_REQRepeat_Record);

                           pFeeScaleSys->getData(dataRepeat, BF::HOST);

                           DString dstrRunMode = 
                           DSTCWorkSession::getRunMode( listObjActivityChild, pFeeScaleSys->hasTransactionUpdates( ));                                      

                           dataRepeat.setElementValue( ifds::TSRunMode, dstrRunMode );
                           DSTCWorkSession::setRunMode( &dataRepeat, listObjActivity );
                           request->addRepeat(dataRepeat);
                           ++ count; 

                        }
                        ++iterFeeScaleList;
                     } //while FeeScaleList iterater  
                     request->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
                  }
               }
               else if(bShowThreshold)
               {
                  FeeThrshldSysList* pFeeThrshldSysList = NULL; 
                  SEVERITY sevRtn1 = pFeeParamSys->getFeeThresholdList(pFeeThrshldSysList, BF::HOST);
                  severity = std::max( severity, sevRtn1);
                  int count = 0;
                  if(pFeeThrshldSysList  &&  severity <= WARNING )
                  {
                     BFObjIter iterFeeThresholdList( *pFeeThrshldSysList, BF::HOST );
                     while( !iterFeeThresholdList.end() )
                     {
                        FeeThrshldSys* pFeeThrshldSys = dynamic_cast<FeeThrshldSys*>( iterFeeThresholdList.getObject() );
                        BF_OBJ_ACTIVITY lFeeThrshldSysActivity = iterFeeThresholdList.getKey().getActivity();
                        if(pFeeThrshldSys != NULL && (lFeeThrshldSysActivity == OBJ_ACTIVITY_ADDED || 
                                                   pFeeThrshldSys->hasTransactionUpdates( ) || 
                                                   lFeeThrshldSysActivity == OBJ_ACTIVITY_DELETED ))
                        {
                           BFData dataRepeat(ifds::DSTC0232_REQRepeat_Record);
                           pFeeThrshldSys->getData(dataRepeat, BF::HOST);
                           DString dstrRunMode = DSTCWorkSession::getRunMode( lFeeThrshldSysActivity, pFeeThrshldSys->hasTransactionUpdates( ));                                      

                           dataRepeat.setElementValue( ifds::TSRunMode,dstrRunMode );
                           DSTCWorkSession::setRunMode( &dataRepeat, listObjActivity );
                           dataRepeat.setElementValue(ifds::RecType, REC_TYPE_THRESHOLD);

                           request->addRepeat(dataRepeat);
                           ++ count; 

                           FeeScaleBaseList* pFeeScaleSysList = NULL;
                           sevRtn1 = pFeeThrshldSys->getFeeScaleSysList(pFeeScaleSysList, BF::HOST, true);
                           severity = std::max( severity, sevRtn1);  
                           if(pFeeScaleSysList &&  severity <= WARNING )
                           {
                              BFObjIter iterFeeScaleList( *pFeeScaleSysList, BF::HOST );
                              while( !iterFeeScaleList.end() )
                              {
                                 FeeScaleSys* pFeeScaleSys = dynamic_cast<FeeScaleSys*>( iterFeeScaleList.getObject() );
                                 BF_OBJ_ACTIVITY lFeeScaleActivity = iterFeeScaleList.getKey().getActivity();
                                 if(pFeeScaleSys != NULL && (lFeeScaleActivity == OBJ_ACTIVITY_ADDED || 
                                                            pFeeScaleSys->hasTransactionUpdates( ) || 
                                                            lFeeScaleActivity == OBJ_ACTIVITY_DELETED ))
                                 {
                                    BFData scaleDataRepeat(ifds::DSTC0232_REQRepeat_Record);
                                    pFeeScaleSys->getData(scaleDataRepeat, BF::HOST);
                                    DString dstrScaleRunMode = DSTCWorkSession::getRunMode( lFeeScaleActivity, pFeeScaleSys->hasTransactionUpdates( ));                                      

                                    scaleDataRepeat.setElementValue(ifds::TSRunMode, dstrScaleRunMode);
                                    DSTCWorkSession::setRunMode( &scaleDataRepeat, lFeeScaleActivity);
                                    scaleDataRepeat.setElementValue(ifds::RecType, REC_TYPE_SCALE); 

                                    request->addRepeat(scaleDataRepeat);
                                    ++ count; 
                                 }
                                 ++iterFeeScaleList;
                              }
                           }
                        }
                        ++iterFeeThresholdList;
                     }
                     request->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
                  }
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCFeeParamSysTxnBuilder.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:32:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   May 02 2003 14:48:00   linmay
// modified buildTxnKey()
// 
//    Rev 1.1   Mar 21 2003 18:05:34   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.0   Jan 20 2003 14:54:00   YINGBAOL
// Initial Revision
// 

*/