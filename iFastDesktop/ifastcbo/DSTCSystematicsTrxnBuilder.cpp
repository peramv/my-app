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
// ^FILE   : DSTCSystematicsTrxnBuilder.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October 1999 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCSystematicsTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcsystematicstrxnbuilder.hpp"
#include "mfaccount.hpp"
#include "systematic.hpp"
#include "systematiclist.hpp"
#include "sysallocation.hpp"
#include "sysallocationlist.hpp"
#include "autoaccttransallocationlist.hpp"
#include "autoaccttransallocation.hpp"
#include "autotransallocation.hpp"
#include "autotransallocationlist.hpp"
#include "dstcommonfunction.hpp"
#include "splitcommission.hpp"
#include "splitcommissionlist.hpp"
#include "sysindex.hpp"
#include "sysindexlist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0084_req.hpp>
#include <ifastdataimpl\dse_dstc0084_vw.hpp>
#include "mgmtcooptions.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SYSTEMATICS_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCSystematicsTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
   const I_CHAR * const CFDS = I_("Canada");
   const I_CHAR * const RECORD_TYPE_INDEXING = I_( "I" );
   const I_CHAR * const RECORD_TYPE_NON_INDEX = I_( "C" );
   const I_CHAR * const TRANS_TYPE_AT     = I_( "AT" );
   const I_CHAR * const YES = I_("Y");
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   //extern CLASS_IMPORT const long ; 
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId StatusCode;
   extern CLASS_IMPORT const BFDecimalFieldId BankDetlVer;
   extern CLASS_IMPORT const BFTextFieldId ReplaceAsDefault;
   extern CLASS_IMPORT const BFNumericFieldId AllocAccountNum;
   extern CLASS_IMPORT const BFNumericFieldId InstCode;
   extern CLASS_IMPORT const BFTextFieldId SplitComm;
   extern CLASS_IMPORT const BFDecimalFieldId DistribDetlVer;
   extern CLASS_IMPORT const BFDecimalFieldId Level;
   extern CLASS_IMPORT const BFTextFieldId PACSWPOverride;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

const BFFieldId fieldsInSysAlloc[]=
{
   ifds::FundCode,
   ifds::ClassCode,
   ifds::Percentage,
   ifds::AllocAmount,
   ifds::DistribDetlRid,
   ifds::DistribDetlVer,
   ifds::DistribLevel,
   ifds::AllocAccountNum,
};
static const int numFieldsInSysAlloc = sizeof( fieldsInSysAlloc ) / sizeof( BFFieldId );

const BFFieldId fieldsInSplitComm[]=
{
   ifds::CommPrcnt,
   ifds::BrokerCode,
   ifds::BranchCode,
   ifds::SlsrepCode,
   ifds::CommLevel,
   ifds::CommRate,
   ifds::TransSeq,
   ifds::TradesPayType,
   ifds::Fixed,
   ifds::GrossOrNet,   
   ifds::SplitCommRid,   
   ifds::RenunAmount,   

};
static const int numFieldsInSplitComm = sizeof( fieldsInSplitComm ) / sizeof( BFFieldId );

const BFFieldId fieldsInSysIndex[]=
{
   ifds::IndexAmt,
   ifds::IndexType,
   ifds::IndexFrequency,
   ifds::StartDate,
   ifds::EndDate,
   ifds::PACIndexRid,
   ifds::PACIndexVer,
   ifds::NextIndexDate,
};
static const int numFieldsInSysIndex = sizeof( fieldsInSysIndex ) / sizeof( BFFieldId );

//******************************************************************************

void DSTCSystematicsTrxnBuilder::fillingData( BFAbstractCBO* pObj, BFData* data, const BFFieldId fieldIds[], int numFields )
{
   DString value;
   for( int i=0; i< numFields; ++i )
   {
      pObj->getField( fieldIds[i], value, BF::HOST, false);
      data->setElementValue( fieldIds[i], value, false, false );
   }
}

//******************************************************************************

void DSTCSystematicsTrxnBuilder::buildTrxnKey( DString& strKey, Systematic* systematic, MFAccount* mfAccount )
{
	DString sPACSWPId;
	
	systematic->getField( ifds::PACSWPId, sPACSWPId, BF::HOST);
	addIDITagValue(strKey, I_("PACSWPId"), sPACSWPId);
   
}


//******************************************************************************
SEVERITY DSTCSystematicsTrxnBuilder::buildTransactions( DSTCWorkSession &workSession, 
                                                        BFAbstractCBO* pObj,
                                                        HostTransactionContainer* pTrCont, 
                                                        BF_OBJ_ACTIVITY objActivity /*= OBJ_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* mfAccount = dynamic_cast<MFAccount*>(pObj);
   DString accountnum;
   DString dLevel = I_( "3" );
   bool bCreateAllocations = true;
   int iAcctAllocNum ;
   if( mfAccount != NULL )
   {
      //walk the list of systematics
      SystematicList* systematicList = NULL;
      mfAccount->getField( ifds::AccountNum, accountnum, BF::HOST );
      accountnum.stripLeading( '0' );
      accountnum.strip();
      

      //if no list do not go and get one from the database
      severity = mfAccount->getSystematicList( systematicList, BF::HOST, false );

      if( systematicList != NULL && severity <= WARNING )
      {
         //define an iterator on the systematics list
         BFObjIter iterSystematicList( *systematicList, BF::HOST );

         DString AcctLvlRunMode, FundLvlRunMode, splitCommRunmode, DistribAcctLvlRid, DistribAcctLvlVer, 
         DistribDetlRid, DistribDetlVer, PACSWPId;

         while( !iterSystematicList.end() )
         {
            Systematic* systematic = dynamic_cast<Systematic*>( iterSystematicList.getObject() );

            BF_OBJ_ACTIVITY listObjActivity = iterSystematicList.getKey().getActivity();

            if( systematic != NULL && (listObjActivity == OBJ_ACTIVITY_ADDED || systematic->hasTransactionUpdates( ) || listObjActivity == OBJ_ACTIVITY_DELETED ) )
            {
               systematic->getField( ifds::PACSWPId, PACSWPId, BF::HOST, false );

               DString strKey;
               //**  Data* req;
               BFData *request = new BFData( ifds::DSTC0084_REQ );
               BFData *response = new BFData( ifds::DSTC0084_VW );
               DString strTrack, strActivity;
               systematicList->getTrackActivity(strTrack,strActivity);                    
               request->setElementValue( ifds::Track, strTrack, false, false );
               request->setElementValue( ifds::Activity, strActivity, false, false );

               DString mgmtCoId;
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               request->setElementValue( ifds::CompanyId, mgmtCoId );

               int count = 0;

               DSTCSystematicsTrxnBuilder::buildTrxnKey( strKey, systematic, mfAccount );

               //define an iterator on the HostTransactionContainer
               HostTransactionContainerIterator iterTrxnContList( pTrCont );

               // get the key for this systematic
               // look for the systematic record in the HostTransactionContainer
               iterTrxnContList.walkStrKey( strKey );
               //the trxn hasn't been handled yet, no group and sub type set,
               iterTrxnContList.walkTrxnGroup( NO_GROUP );
               iterTrxnContList.walkTrxnSubType( 0 );
               iterTrxnContList.begin();


               systematic->getData( *request, BF::HOST ); 
               request->setElementValue( ifds::AccountNum, accountnum, false, false );
               DString dstrAmount(NULL_STRING);
               systematic->getField(ifds::Amount,dstrAmount,BF::HOST);
               DSTCWorkSession::setRunMode( request, listObjActivity );
               DString keyTypes;

               addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, accountnum );

               JData *jdata = new JData( DSTC_REQUEST::SYSTEMATICS_UPDATE, request, response );
               pTrCont->addTransaction( strKey, jdata, listObjActivity, NOT_PERSISTENT, keyTypes );

               // get allocation data
               SysAllocationList *AllocList;
               SEVERITY sevRtn1 = systematic->getSysAllocationList( AllocList );

               severity = std::max( severity, sevRtn1 );
			   
			   DString dstrEventReceiptTime,dstrEventReceiptDate; 
			   systematic->getField(ifds::EventReceiptTime, dstrEventReceiptTime, BF::HOST); 
			   systematic->getField(ifds::EventReceiptDate, dstrEventReceiptDate, BF::HOST);
 			    //if date is empty for what ever reason,time should also be empty
			    if(dstrEventReceiptDate.stripAll().empty())
				{
					request->setElementValue( ifds::EventReceiptTime, NULL_STRING);
				}
                //remove the mask and send the time to the view
				else if(!dstrEventReceiptTime.stripAll().empty())
				{
					removeMaskFromString(dstrEventReceiptTime,I_("##:##:##"));
					request->setElementValue( ifds::EventReceiptTime, dstrEventReceiptTime);
				}
               SplitCommissionList* pSplitCommissionList = NULL ;
               SplitCommission* pSplitCommission;

               if( AllocList != NULL && 
                   !(systematic->findTransType(BF::HOST, TRANS_TYPE_AT)) && 
                   severity <= WARNING )  //if available allocation list
               {
                  DString setAsDefault = I_( "N" );
                  AllocList->getField( ifds::ReplaceAsDefault, setAsDefault, BF::HOST );
                  DString dstrVer,dstrRid;

                  AllocList->GetAccountLevelInfo(dstrVer,dstrRid);

                  BFObjIter iteralloc( *AllocList, BF::HOST );

                  iAcctAllocNum = iteralloc.getNumberOfItemsInList();

                  int nDeletedItems = 0;
                  iteralloc.begin();
                  while( !iteralloc.end() )
                  {
                     if( iteralloc.getKey().getActivity() == OBJ_ACTIVITY_DELETED ) ++ nDeletedItems;
                     ++iteralloc;
                  }

                  int nEffectedItems = iAcctAllocNum - nDeletedItems;

                  //check if there is any allocation attached to the allocation list
                  iteralloc.begin();
                  if ( mfAccount->isAMSAccount (BF::HOST) ){
                     DString dstrPACSWPOverride;
                     workSession.getMgmtCoOptions()->getField(ifds::PACSWPOverride, dstrPACSWPOverride, BF::HOST);
                     if ( dstrPACSWPOverride == YES )
                        bCreateAllocations = false;
                  }
                  
                  while( !iteralloc.end() && bCreateAllocations )
                  {

                     //convert the current object to systematic allocation
                     SysAllocation* systemalloc = dynamic_cast<SysAllocation*>( iteralloc.getObject() );
                     BF_OBJ_ACTIVITY listObjActivity = iteralloc.getKey().getActivity();
                     DString dstrFundVer;
                     systemalloc->getField( ifds::DistribDetlRid, DistribDetlRid, BF::HOST, false );
                     systemalloc->getField( ifds::DistribDetlVer, dstrFundVer, BF::HOST, false );

                     //Let's ignore the 100% deleted Allocations
                     if( listObjActivity == OBJ_ACTIVITY_DELETED && DistribDetlRid == I_("0") )
                     {
                        ++iteralloc;
                        continue;
                     }

                     FundLvlRunMode = iAcctAllocNum >1 && ( DistribDetlRid == I_("0") || DistribDetlRid == NULL_STRING)? 
                                      RUNMODE::ADDED : DSTCWorkSession::getRunMode( iteralloc.getKey().getActivity(), 
                                                                                    systemalloc->hasTransactionUpdates( ) ); 

                     // if record is updated or if setAsDefault is turned on, sent transaction 
//						   if( systemalloc != NULL  && ( setAsDefault == I_( "Y" ) || iteralloc.hasTransactionUpdates( false ) ))
                     if( systemalloc != NULL )
                     {
                        systemalloc->getSplitCommissionList( pSplitCommissionList, BF::HOST );
                        bool okayToSend = OkToSend ( systemalloc, listObjActivity, iteralloc.hasTransactionUpdates( false ) );

                        if( okayToSend || pSplitCommissionList )
                        {
                           if( pSplitCommissionList && pSplitCommissionList->hasCBOObject() )
                           {
                              BFObjIter iterSplitCommissionList(*pSplitCommissionList, BF::HOST);
                              while( !iterSplitCommissionList.end() )
                              {
                                 pSplitCommission = 
                                 dynamic_cast<SplitCommission*>(iterSplitCommissionList.getObject());
                                 if( OkToSendSplitComm( nEffectedItems, listObjActivity, 
                                                        iterSplitCommissionList.getKey().getActivity(),
                                                        DistribDetlRid != I_("0") && DistribDetlRid != NULL_STRING,
                                                        pSplitCommission, splitCommRunmode ) )
                                 {

                                    if( pSplitCommission )
                                    {
                                       BFData dataRepeat(ifds::DSTC0084_REQRepeat_Record);

                                       fillingData( pSplitCommission, &dataRepeat, fieldsInSplitComm, numFieldsInSplitComm );                                    
                                       dataRepeat.setElementValue( ifds::CommRunMode, splitCommRunmode );
                                       dataRepeat.setElementValue( ifds::RecordType, RECORD_TYPE_NON_INDEX, false, false );

                                       // fix for rts 
                                       dataRepeat.setElementValue( ifds::IndexRunMode, RUNMODE::UNCHANGED, false, false );

                                       fillingData( systemalloc, &dataRepeat, fieldsInSysAlloc, numFieldsInSysAlloc );

                                       // assignment of this field due to Level is always blank even though CBO has the default value
                                       // view # 7 and view # 84 repeatrecord does not have the same field name for AccountNum
                                       // code to be removed after correction.
                                       dataRepeat.setElementValue( ifds::DistribLevel, dLevel, false, false );
                                       dataRepeat.setElementValue( ifds::AllocAccountNum, accountnum, false, false );

                                       dataRepeat.setElementValue( ifds::DistribAcctLvlVer, dstrVer, false, false );
                                       dataRepeat.setElementValue( ifds::DistribAcctLvlRid, dstrRid, false, false );
                                       dataRepeat.setElementValue( ifds::AcctLvlAmount, dstrAmount, false, false );
                                       dataRepeat.setElementValue( ifds::AcctPrcnt, I_("100"), false, false );
                                       dataRepeat.setElementValue( ifds::DistribFundLvlVer, dstrFundVer, false, false );

                                       dataRepeat.setElementValue( ifds::AcctLvlRunMode, AcctLvlRunMode );
                                       AcctLvlRunMode = RUNMODE::UNCHANGED;

                                       dataRepeat.setElementValue( ifds::RunMode, FundLvlRunMode );
                                       FundLvlRunMode = RUNMODE::UNCHANGED;

                                       //DSTCWorkSession::setRunMode( &dataRepeat, listObjActivity );
                                       request->addRepeat(dataRepeat);
                                       ++ count; 
                                    }
                                 }
                                 ++iterSplitCommissionList;
                              }                         
                           }
                           else
                           { // when there is no split commission
                              BFData dataRepeat(ifds::DSTC0084_REQRepeat_Record);

                              dataRepeat.setElementValue( ifds::CommRunMode, RUNMODE::UNCHANGED );
                              dataRepeat.setElementValue( ifds::RecordType, RECORD_TYPE_NON_INDEX, false, false );
                              systemalloc->getData(dataRepeat, BF::HOST);

                              // assignment of this field due to Level is always blank even though CBO has the default value
                              // view # 7 and view # 84 repeatrecord does not have the same field name for AccountNum
                              // code to be removed after correction.
                              dataRepeat.setElementValue( ifds::DistribLevel, dLevel, false, false );
                              dataRepeat.setElementValue( ifds::AllocAccountNum, accountnum, false, false );

                              dataRepeat.setElementValue( ifds::DistribAcctLvlVer, dstrVer, false, false );
                              dataRepeat.setElementValue( ifds::DistribAcctLvlRid, dstrRid, false, false );
                              dataRepeat.setElementValue( ifds::AcctLvlAmount, dstrAmount, false, false );
                              dataRepeat.setElementValue( ifds::AcctPrcnt, I_("100"), false, false );
                              dataRepeat.setElementValue( ifds::DistribFundLvlVer, dstrFundVer, false, false );

                              AcctLvlRunMode = RUNMODE::UNCHANGED;

                              dataRepeat.setElementValue( ifds::AcctLvlRunMode, AcctLvlRunMode );


                              dataRepeat.setElementValue( ifds::RunMode, FundLvlRunMode );
                              FundLvlRunMode = RUNMODE::UNCHANGED;

                              //DSTCWorkSession::setRunMode( &dataRepeat, listObjActivity );
                              request->addRepeat(dataRepeat);
                              ++ count; 
                           }                          
                        }
                     }
                     ++iteralloc;
                  } //while allocation list has more than one item    

                  // Create Indexing information
                  SysIndexList *pSysIndexList;
                  systematic->getSystematicIndexList( BF::HOST, pSysIndexList );
                  if( pSysIndexList )
                  {
                     BFObjIter iterSysIndexList(*pSysIndexList, BF::HOST);
                     SysIndex *pSysIndex;
                     while( !iterSysIndexList.end() )
                     {
                        pSysIndex = dynamic_cast <SysIndex *> ( iterSysIndexList.getObject() );
                        if( pSysIndex )
                        {
                           BFData dataRepeat(ifds::DSTC0084_REQRepeat_Record);                                
                           fillingData( pSysIndex, &dataRepeat, fieldsInSysIndex, numFieldsInSysIndex );
                           dataRepeat.setElementValue( ifds::RecordType, RECORD_TYPE_INDEXING, false, false );
                           dataRepeat.setElementValue( ifds::IndexRunMode, 
                                                       DSTCWorkSession::getRunMode( iterSysIndexList.getKey().getActivity(),                                      
                                                                                    pSysIndex->hasTransactionUpdates( ) ) ); 
                           dataRepeat.setElementValue( ifds::DistribLevel, dLevel, false, false );
                           dataRepeat.setElementValue( ifds::AllocAccountNum, accountnum, false, false );
                           DSTCWorkSession::setRunMode( &dataRepeat, listObjActivity );
                           request->addRepeat(dataRepeat);
                           ++ count; 
                        }
                        ++iterSysIndexList;
                     }
                  }

                  request->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
                  request->setElementValue( ifds::SetAsDefault, setAsDefault, false, false );
               }  // if allocation list is available

               if( systematic->findTransType(BF::HOST, TRANS_TYPE_AT) )
               {
                  // Automatic Trasfer Allocation acct Level
                  AutoAcctTransAllocationList* pAtAcctAllocList;
                  sevRtn1 = systematic->getAtAcctAllocationList( pAtAcctAllocList );                     
                  severity = std::max( severity, sevRtn1 );
                  if( pAtAcctAllocList != NULL && severity <= WARNING )
                  {
                     BFObjIter iter(*pAtAcctAllocList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
                     iAcctAllocNum = iter.getNumberOfItemsInList();

                     DString dstrAllocAccountNum;
                     BFObjIter iterATAcctalloc( *pAtAcctAllocList, BF::HOST );
                     if ( mfAccount->isAMSAccount (BF::HOST) ){
                        DString dstrPACSWPOverride;
                        workSession.getMgmtCoOptions()->getField(ifds::PACSWPOverride, dstrPACSWPOverride, BF::HOST);
                        if ( dstrPACSWPOverride == YES )
                           bCreateAllocations = false;
                     }
                     while( !iterATAcctalloc.end() && bCreateAllocations )
                     {
                        AutoAcctTransAllocation* atAcctAlloc = dynamic_cast<AutoAcctTransAllocation*>( iterATAcctalloc.getObject() );                    
                        BF_OBJ_ACTIVITY listObjActivity = iterATAcctalloc.getKey().getActivity();

                        atAcctAlloc->getField( ifds::DistribDetlRid, DistribAcctLvlRid, BF::HOST, false );
                        atAcctAlloc->getField( ifds::DistribDetlVer, DistribAcctLvlVer, BF::HOST, false );
                        AcctLvlRunMode = ( DistribAcctLvlRid == I_("0") || DistribAcctLvlRid == NULL_STRING)? 
                                         RUNMODE::ADDED : DSTCWorkSession::getRunMode( iterATAcctalloc.getKey().getActivity(), 
                                                                                       atAcctAlloc->hasTransactionUpdates( ) ); 

                        DString setAsDefault = I_( "N" );
                        pAtAcctAllocList->getField( ifds::ReplaceAsDefault, setAsDefault, BF::HOST );

                        atAcctAlloc->getField( ifds::AllocAccountNum, dstrAllocAccountNum, BF::HOST );
                        if( setAsDefault==I_("") ) setAsDefault = I_("N");
                        DString acctPercent,acctAmount;  
                        atAcctAlloc->getField( ifds::Percentage, acctPercent, BF::HOST );
                        atAcctAlloc->getField( ifds::AllocAmount, acctAmount, BF::HOST );

                        // if record is updated or if setAsDefault is turned on, sent transaction 
//								if( atAcctAlloc != NULL  && ( setAsDefault == I_( "Y" ) || iterATAcctalloc.hasTransactionUpdates( false ) ))
                        bool bAcctAllocUpdated(false);
                        if( atAcctAlloc != NULL )
                        {
                           if( iAcctAllocNum > 1 )
                              bAcctAllocUpdated = true;
                           else
                              bAcctAllocUpdated = IsATAllocUpdated (atAcctAlloc, listObjActivity, setAsDefault == I_("Y"));//OkToSend ( atAcctAlloc, listObjActivity, iterATAcctalloc.hasTransactionUpdates( false ) );

                        }
                        //Automatic Tras allocation Fund Level
/*
                        if ( iAcctAllocNum == 1 && acctPercent == I_("100") ) {
                           request->setElementValue( ifds::AccountTo, dstrAllocAccountNum, false, false );
                        }
*/
                        AutoTransAllocationList* pAtTransAllocList;
                        sevRtn1 = atAcctAlloc->getAtAllocationList(pAtTransAllocList);
                        severity = std::max( severity, sevRtn1 );
                        if( bAcctAllocUpdated && pAtTransAllocList != NULL && severity <= WARNING )
                        {
                           BFObjIter iterAtAlloc( *pAtTransAllocList, BF::HOST );
                           while( !iterAtAlloc.end() )
                           {
                              AutoTransAllocation* atAlloc = dynamic_cast<AutoTransAllocation*>( iterAtAlloc.getObject() );                              
                              BF_OBJ_ACTIVITY listObjActivity = iterAtAlloc.getKey().getActivity();

                              atAlloc->getField( ifds::DistribDetlRid, DistribDetlRid, BF::HOST, false );

                              //Let's ignore the 100% deleted Allocations
                              if( listObjActivity == OBJ_ACTIVITY_DELETED && DistribDetlRid == I_("0") )
                              {
                                 ++iterAtAlloc;
                                 continue;
                              }

                              FundLvlRunMode = ( DistribDetlRid == I_("0") || DistribDetlRid == NULL_STRING)? 
                                               RUNMODE::ADDED : DSTCWorkSession::getRunMode( iterAtAlloc.getKey().getActivity(), 
                                                                                             atAlloc->hasTransactionUpdates( ) ); 

                              if( atAlloc != NULL  && 
                                  (bAcctAllocUpdated || setAsDefault == I_("Y") || iterAtAlloc.hasTransactionUpdates(false)) )
                              {
                                 atAlloc->getSplitCommissionList( pSplitCommissionList, BF::HOST );

                                 bool okayToSend = OkToSend(atAlloc, listObjActivity, atAlloc->hasTransactionUpdates(false));
                                 //bool okayToSend = IsATAllocUpdated (atAlloc, listObjActivity, setAsDefault == I_("Y"));
                                 if( okayToSend || pSplitCommissionList )
                                 {
                                    if( pSplitCommissionList && pSplitCommissionList->hasCBOObject() )
                                    {
                                       BFObjIter iterSplitCommissionList(*pSplitCommissionList, BF::HOST);
                                       while( !iterSplitCommissionList.end() )
                                       {
                                          if( (DistribDetlRid != I_("0") && DistribDetlRid != NULL_STRING &&
                                              iterSplitCommissionList.getKey().getActivity() == OBJ_ACTIVITY_DELETED) ||
                                              (DistribDetlRid == I_("0") && iterSplitCommissionList.getKey().getActivity() 
                                              != OBJ_ACTIVITY_DELETED))
                                          {
                                             pSplitCommission =  dynamic_cast<SplitCommission*>(iterSplitCommissionList.getObject());
                                             if( pSplitCommission )
                                             {
                                                BFData dataRepeat(ifds::DSTC0084_REQRepeat_Record);

                                                fillingData( pSplitCommission, &dataRepeat, fieldsInSplitComm, numFieldsInSplitComm );
                                                dataRepeat.setElementValue( ifds::RecordType, RECORD_TYPE_NON_INDEX, false, false );
                                                dataRepeat.setElementValue( ifds::CommRunMode, ( DistribDetlRid == I_("0") || DistribDetlRid == NULL_STRING)? 
                                                                            RUNMODE::ADDED : DSTCWorkSession::getRunMode( iterSplitCommissionList.getKey().getActivity(), 
                                                                                                                          pSplitCommission->hasTransactionUpdates( )));
                                                fillingData( atAlloc, &dataRepeat, fieldsInSysAlloc, numFieldsInSysAlloc );

                                                // assignment of this field due to Level is always blank even though CBO has the default value
                                                // view # 7 and view # 84 repeatrecord does not have the same field name for AccountNum
                                                // code to be removed after correction.
                                                dataRepeat.setElementValue( ifds::DistribLevel, dLevel, false, false );
                                                dataRepeat.setElementValue( ifds::DistribAcctLvlRid, DistribAcctLvlRid, false, false );
                                                dataRepeat.setElementValue( ifds::DistribAcctLvlVer, DistribAcctLvlVer, false, false );
                                                //dataRepeat.setElementValue( ifds::DistribDetlRid, DistribDetlRid, false, false );
                                                //dataRepeat.setElementValue( ifds::DistribDetlVer, DistribDetlVer, false, false );
                                                dataRepeat.setElementValue( ifds::AllocAccountNum, dstrAllocAccountNum, false, false );
                                                dataRepeat.setElementValue( ifds::RecordType, RECORD_TYPE_NON_INDEX, false, false );                                                                        
                                                dataRepeat.setElementValue( ifds::AcctLvlAmount, acctAmount, false, false );                                                                       
                                                dataRepeat.setElementValue( ifds::AcctPrcnt, acctPercent, false, false );                                                                       

                                                dataRepeat.setElementValue( ifds::AcctLvlRunMode, AcctLvlRunMode );
                                                AcctLvlRunMode = RUNMODE::UNCHANGED;

                                                dataRepeat.setElementValue( ifds::RunMode, FundLvlRunMode );
                                                FundLvlRunMode = RUNMODE::UNCHANGED;

                                                //DSTCWorkSession::setRunMode( &dataRepeat, listObjActivity );
                                                request->addRepeat(dataRepeat);
                                                ++count; 
                                                request->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
                                             }
                                          }
                                          ++iterSplitCommissionList;
                                       }
                                    }
                                    else
                                    { // when there is no split commission
                                       BFData dataRepeat( ifds::DSTC0084_REQRepeat_Record );

                                       atAlloc->getData( dataRepeat, BF::HOST ); 

                                       // assignment of this field due to Level is always blank even though CBO has the default value
                                       // view # 7 and view # 84 repeatrecord does not have the same field name for AccountNum
                                       // code to be removed after correction.
                                       dataRepeat.setElementValue( ifds::DistribLevel, dLevel, false, false );
                                       dataRepeat.setElementValue( ifds::DistribAcctLvlRid, DistribAcctLvlRid, false, false );
                                       dataRepeat.setElementValue( ifds::DistribAcctLvlVer, DistribAcctLvlVer, false, false );
                                       dataRepeat.setElementValue( ifds::AllocAccountNum, dstrAllocAccountNum, false, false );
                                       dataRepeat.setElementValue( ifds::RecordType, RECORD_TYPE_NON_INDEX, false, false );
                                       DSTCWorkSession::setRunMode( &dataRepeat, listObjActivity );
                                       dataRepeat.setElementValue( ifds::AcctLvlAmount, acctAmount, false, false );                                                                       
                                       dataRepeat.setElementValue( ifds::AcctPrcnt, acctPercent, false, false );                                                                       
                                       dataRepeat.setElementValue( ifds::IndexRunMode, RUNMODE::UNCHANGED, false, false );                                                                         

                                       dataRepeat.setElementValue( ifds::AcctLvlRunMode, AcctLvlRunMode );
                                       AcctLvlRunMode = RUNMODE::UNCHANGED;

                                       dataRepeat.setElementValue( ifds::RunMode, FundLvlRunMode );
                                       FundLvlRunMode = RUNMODE::UNCHANGED;

                                       //**Data &rptRecord = const_cast< Data & >(req->getData( DEFAULT_REPEAT_RECORD ));
                                       request->addRepeat( dataRepeat );

                                       count++;  // set repeat count
                                       /*req->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
                                       req->setElementValue( ifds::SetAsDefault, setAsDefault, false, false );*/
                                       request->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
                                       request->setElementValue( ifds::SetAsDefault, setAsDefault, false, false );
                                    }
                                 }
                              }
                              ++iterAtAlloc;                         
                           }// end of while iterAtAlloc;
                        } // if pAtTransAllocList not equal to null;
                        ++iterATAcctalloc;                                             
                     }              
                  }// if AtAcctAllocList not equal to null
               }//if AT
            }  // if systematic not equal to null and has been updated
            ++iterSystematicList;
         }  // while loopAcctLvlRunMode
      }  // systematiclist not null
   }  // MFaccount not null
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************************

bool DSTCSystematicsTrxnBuilder::IsATAllocUpdated ( BFAbstractCBO* allocation, BF_OBJ_ACTIVITY& ObjActivity, bool bSetAsDefault )
{
   if( allocation == NULL )
      return(false);

   bool iupdate ( false );

   DString distribDetlRid;
   allocation->getField( ifds::DistribDetlRid, distribDetlRid, BF::HOST );
   distribDetlRid.strip().stripLeading(I_('0'));

   bool bTransactionUpdates = allocation->hasTransactionUpdates(false );
   if( bSetAsDefault || ObjActivity == OBJ_ACTIVITY_ADDED || bTransactionUpdates || ObjActivity == OBJ_ACTIVITY_DELETED )
   {
      //iupdate = true;
      iupdate = OkToSend(allocation, ObjActivity, bTransactionUpdates);
   }

   // check if fund level allocation changed
   if( iupdate == false && ((distribDetlRid == I_( "0" ) || distribDetlRid == NULL_STRING )) )
   {
      bool bUpdateFlag(false);
      if( typeid(*allocation) == typeid(AutoAcctTransAllocation) )
      {
         AutoTransAllocationList* pAtTransAllocList;
         AutoAcctTransAllocation* pAtAcctAlloc = dynamic_cast<AutoAcctTransAllocation*>(allocation);
         pAtAcctAlloc->getAtAllocationList(pAtTransAllocList);
         if( pAtTransAllocList != NULL )
         {
            BF_OBJ_ACTIVITY listObjActivity;
            BFObjIter iterAllocList( *pAtTransAllocList, BF::HOST );
            while( !iterAllocList.end() &&  !iupdate )
            {
               listObjActivity = iterAllocList.getKey().getActivity();
               BFAbstractCBO* pBFBase = dynamic_cast< BFAbstractCBO* >( iterAllocList.getObject() );
               iupdate = OkToSend(pBFBase, listObjActivity, pBFBase->hasTransactionUpdates(false));
               //iupdate = IsATAllocUpdated ( iterAllocList.getObject(), listObjActivity, bSetAsDefault);   				
               if( iupdate )
               {
                  bUpdateFlag = true;
                  if( listObjActivity != OBJ_ACTIVITY_ADDED )
                     break;
               }
               ++iterAllocList;
            }// end of while 
            if( bUpdateFlag && ObjActivity == OBJ_ACTIVITY_NONE && 
                (listObjActivity == OBJ_ACTIVITY_ADDED || listObjActivity == OBJ_ACTIVITY_NONE) )
            {
               ObjActivity = OBJ_ACTIVITY_ADDED;
            }
            iupdate = bUpdateFlag;
         }// if pAtTransAllocList
      }// if typeid
   }

   if( iupdate == false )
   {
      AutoTransAllocationList* pAtTransAllocList;
      AutoAcctTransAllocation* pAtAcctAlloc = dynamic_cast<AutoAcctTransAllocation*>(allocation);
      pAtAcctAlloc->getAtAllocationList(pAtTransAllocList);

      BFObjIter iter(*pAtTransAllocList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
      int iFundAllocNum = iter.getNumberOfItemsInList();
      if( iFundAllocNum > 1 )
         iupdate = true;
   }
   return(iupdate);
}
//---------------------------------------------------------------------------------------
bool DSTCSystematicsTrxnBuilder::OkToSend( BFAbstractCBO* allocation, BF_OBJ_ACTIVITY &objActivity, bool IsUpdated )
{

   DString  distribDetlRid;
   DString  allocPercentage;
   DString  splitComm;
   bool     okayToSend ( true );
   I_CHAR   *stopstring;

   allocation->getField( ifds::DistribDetlRid, distribDetlRid, BF::HOST );
   allocation->getField( ifds::Percentage, allocPercentage, BF::HOST );
   allocation->getField( ifds::SplitComm, splitComm, BF::HOST, false );

   double   percentage = wcstod( allocPercentage.c_str(), &stopstring );
   bool     Norecid =  (distribDetlRid == I_( "0" ) || distribDetlRid == NULL_STRING );  


   /*********** Skip transaction being build *************/
   // user changed fund or class on a dummy allocation, no need to send the transaction 
   if( Norecid && ( objActivity == OBJ_ACTIVITY_NONE ) && IsUpdated && percentage == 100 )
   {
      okayToSend = false;
   }
   // user delete a dummy record, no need to send the transaction 
   if( Norecid && ( objActivity == OBJ_ACTIVITY_DELETED ) )
   {
      okayToSend = false;
   }
   // user add a dummy record with 100%, no need to send the transaction 
/* yingbao take out
   if ( Norecid && ( objActivity == OBJ_ACTIVITY_ADDED ) && percentage == 100 )
   {  
      okayToSend = false;
   } 

*/
   /********** Change Activity flag (modification, add, delete) *******/
   // user change from one fund to multiple fund, the original dummy record now become a new record
   if( Norecid && ( objActivity == OBJ_ACTIVITY_NONE ) && percentage != 100 )
   {
      objActivity = OBJ_ACTIVITY_ADDED;
   }
   // user change multiple funds to one fund, original allocation now become a dummy, send delete request
   if( Norecid && ( objActivity == OBJ_ACTIVITY_NONE ) && percentage == 100 && splitComm != I_("Y") )
   {
      objActivity = OBJ_ACTIVITY_DELETED;
   }


   return(okayToSend);
}

bool DSTCSystematicsTrxnBuilder::OkToSendSplitComm ( int nEffectedItems, BF_OBJ_ACTIVITY &fundAllocActivity,
                                                     const BF_OBJ_ACTIVITY &splitCommActivity, bool bRecordExistInDB,
                                                     SplitCommission* pSplitCommission, DString& splitCommRunmode )
{
   if( nEffectedItems == 1 && fundAllocActivity != OBJ_ACTIVITY_DELETED && splitCommActivity != OBJ_ACTIVITY_DELETED )
   {
      splitCommRunmode = RUNMODE::ADDED;
      return(true);
   }
   else if( nEffectedItems > 1 )
   {
      if( bRecordExistInDB )
      {
         splitCommRunmode = DSTCWorkSession::getRunMode( splitCommActivity, 
                                                         pSplitCommission->hasTransactionUpdates( ));
         return(true);
      }
      else if( !bRecordExistInDB && splitCommActivity != OBJ_ACTIVITY_DELETED )
      {
         splitCommRunmode = RUNMODE::ADDED;

         return(true);
      }
   }
   return(false);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCSystematicsTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.45   Sep 20 2011 00:33:44   wutipong
 * IN2043788 - PAC system issue
 * 
 *    Rev 1.44   Feb 17 2005 17:04:28   aguilaam
 * incident # 239846 - pass and display RenunAmount (checked in for Serban)
 * 
 *    Rev 1.43   Nov 14 2004 14:33:50   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.42   Dec 12 2003 10:48:12   YINGBAOL
 * PTS10023634 AccountTo should not be changed in builder.
 * 
 *    Rev 1.41   Sep 18 2003 16:05:02   HSUCHIN
 * PTS 10021918 - Bug fix to builder to patch AccountTo field to get account number from allocation when the account level allocation is 100%
 * 
 *    Rev 1.40   Aug 15 2003 15:24:20   HSUCHIN
 * added support for PAC SWP Override to not create allocations when the this generic control is Yes
 * 
 *    Rev 1.39   Apr 25 2003 16:33:28   popescu
 * pts 10016245
 * 
 *    Rev 1.38   Apr 22 2003 09:35:32   WINNIE
 * Ticket 10016243 : Missing copy of field SplitCommRid therefore split comm record not being updated with the change
 * 
 *    Rev 1.37   Mar 21 2003 18:07:12   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.36   Oct 09 2002 23:54:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.35   Aug 29 2002 12:55:36   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.34   22 May 2002 18:28:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.33   Feb 25 2002 18:55:36   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.32   27 Dec 2001 10:55:32   KOVACSRO
 * Bug fixed for NextIndexDate, SysIndex.
 * 
 *    Rev 1.31   Aug 21 2001 14:05:56   YINGBAOL
 * change traansaction for PAC and SWP
 * 
 *    Rev 1.30   Aug 17 2001 17:14:36   YINGBAOL
 * fix allocaccountNum issue
 * 
 *    Rev 1.29   03 Aug 2001 12:22:50   HSUCHIN
 * bug fix - RunMode for 100% Allocations are no longer sent to the back end as Added.
 * 
 *    Rev 1.28   Aug 02 2001 02:55:24   YINGBAOL
 * fix build transaction for AT
 * 
 *    Rev 1.27   16 Jul 2001 17:24:44   YINGZ
 * index runmode fix for rts
 * 
 *    Rev 1.26   04 Jul 2001 16:44:20   YINGZ
 * bug fix
 * 
 *    Rev 1.25   28 Jun 2001 09:13:44   YINGZ
 * change runmode
 * 
 *    Rev 1.24   25 Jun 2001 16:59:16   YINGZ
 * bug fix for pac swp 
 * 
 *    Rev 1.23   18 Jun 2001 14:30:42   YINGZ
 * not finished yet
 * 
 *    Rev 1.22   16 Jun 2001 14:29:46   YINGZ
 * fix AT
 * 
 *    Rev 1.21   13 Jun 2001 16:35:44   HSUCHIN
 * bug fix for systematic indexing
 * 
 *    Rev 1.20   13 Jun 2001 10:04:00   YINGZ
 * change function signature
 * 
 *    Rev 1.19   11 Jun 2001 10:25:56   HSUCHIN
 * added indexing
 * 
 *    Rev 1.18   08 Jun 2001 14:56:38   HSUCHIN
 * sync up with 1.14.2.4
 * 
 *    Rev 1.17   23 May 2001 14:39:28   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.16   10 May 2001 12:20:44   HSUCHIN
 * Sync up with SSB (1.14.2.3)
 * 
 *    Rev 1.14.2.3   May 08 2001 11:13:10   YINGBAOL
 * fix automatic transfer transaction builder
 * 
 *    Rev 1.14.2.2   May 03 2001 13:37:00   YINGZ
 * splicomm fix
 * 
 *    Rev 1.14.2.1   Apr 17 2001 13:22:20   WINNIE
 * no longer need to set BankIdValue with InstCode value
 * 
 *    Rev 1.14.2.0   15 Apr 2001 13:00:16   HSUCHIN
 * added split commission support for auto transfers
 * 
 *    Rev 1.14   04 Apr 2001 11:17:22   BUZILAMI
 * Systematic Bank fixes
 * 
 *    Rev 1.13   Apr 01 2001 15:27:04   YINGZ
 * add fillingData and build transactions for split comm
 * 
 *    Rev 1.12   Mar 22 2001 14:34:00   WINNIE
 * assignment for level using a new field name
 * 
 *    Rev 1.11   09 Mar 2001 18:03:42   BUZILAMI
 * XchgData elimination fixes
 * 
 *    Rev 1.10   09 Feb 2001 15:01:32   SMITHDAV
 * Removed commented code; Removed unneeded includes; Some fixes.
 * 
 *    Rev 1.9   Jan 31 2001 16:11:00   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.8   Jan 16 2001 13:53:38   OLTEANCR
 * 
 *    Rev 1.7   Dec 17 2000 20:23:14   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.6   Sep 29 2000 13:27:10   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.5   Aug 23 2000 11:59:10   HUANGSHA
 * attaching the original allocation records to changed sytemtic record
 * 
 *    Rev 1.4   Aug 01 2000 12:04:04   HUANGSHA
 * make the AT working, need to furthur clean up
 * 
 *    Rev 1.3   Jun 16 2000 14:12:14   YINGBAOL
 * fix AT update  error
 * 
 *    Rev 1.2   Jun 12 2000 16:42:10   YINGBAOL
 * remove check CFDS
 * 
 *    Rev 1.1   May 31 2000 16:15:44   YINGBAOL
 * more validation added
 * 
 *    Rev 1.0   Feb 15 2000 10:59:58   SMITHDAV
 * Initial revision.
// 
//    Rev 1.23   Feb 03 2000 17:40:14   WINNIE
// Additional logic to skip allocation being sent or change the activity flag
// 
//    Rev 1.22   Feb 03 2000 10:52:02   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.21   Feb 02 2000 10:34:00   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.20   Jan 28 2000 17:34:56   WINNIE
// implement Replace As Default function
// 
//    Rev 1.19   Jan 27 2000 15:19:02   WINNIE
// fix allocation creation
// 
//    Rev 1.18   Jan 09 2000 13:18:50   POPESCUS
// added the group id to the lists
// 
//    Rev 1.17   Jan 07 2000 17:16:28   WINNIE
// fix deletion problem
// 
//    Rev 1.16   Jan 06 2000 12:03:06   POPESCUS
// fix related to filter more the HTC 
// 
//    Rev 1.15   Jan 05 2000 16:32:14   WINNIE
// change build key logic; add new transaction for each systematic record; get the runmode from the allocation record for the repeating section
// 
//    Rev 1.14   Dec 15 1999 11:48:02   POPESCUS
// do not get the list from the database if there is none in repository
// 
//    Rev 1.13   Dec 12 1999 17:55:52   POPESCUS
// Delete the XchgData object and minor fixes
// 
*/