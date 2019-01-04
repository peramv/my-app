//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TradeVerification.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : JuLY 22 2014
//
//********************************************************************************
#include "stdafx.h"
#include "TradeVerification.hpp"
#include "TradeVerificationList.hpp"
#include "TradeVerificationSearch.hpp"
#include "TradeOverideRuleWarningsList.hpp"
#include "FundDetailList.hpp"
#include "FundDetail.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcworksession.hpp"
#include "Settlement.hpp"
#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0053_req.hpp>
#include <ifastdataimpl\dse_dstc0053_vwrepeat_record.hpp>
namespace  
{
   const I_CHAR * const CLASSNAME        = I_( "TradeSearchCriteria" );
   const I_CHAR * const YES              = I_( "Y" );
   const I_CHAR * const NO               = I_( "N" );
   const I_CHAR * const NETWORK          = I_( "NetworkID" );
   const I_CHAR * const TRANSNUM         = I_( "TransNum" );
   const I_CHAR * const WIREORD          = I_( "WireOrdNum" );
   const I_CHAR * const EXTTRANS         = I_( "ExtTransNum" );
   const I_CHAR * const SENDREF          = I_( "SendRefNum" );
   const I_CHAR * const PARTREF          = I_( "PartRefNum" );
   const I_CHAR * const MASTERREF        = I_( "MasterRefNum" );
   const I_CHAR * const ACCOUNTNUM       = I_( "AccountNum" );
   const I_CHAR * const EXTERNAL_ID      = I_( "ExternalIdType" );
   const I_CHAR * const FUND_CLASS       = I_( "FundCode" );  
   const I_CHAR * const TRADE_OVERIDE_WARNINGS_LIST = I_("TradeOverideRuleWarningsList"); 
   const I_CHAR * const TRADE_VERIFICATION_LIST     = I_("TradeVerificationList");
}
namespace USER_ACTION
{
 const I_CHAR * const VERIFY           = I_("V");
 const I_CHAR * const DEL              = I_("D");
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId VerifyTrade;
   extern CLASS_IMPORT const BFTextFieldId DeleteTrade;
   extern CLASS_IMPORT const BFTextFieldId UserAction;
   extern CLASS_IMPORT const BFTextFieldId VerifyAll;
   extern CLASS_IMPORT const BFTextFieldId DeleteAll;
   extern CLASS_IMPORT const BFTextFieldId LastTransNumInSetofReq;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,                State Flags,                Group Flags 
   { ifds::TransNum,		          BFCBO::NONE ,                   0 },
   { ifds::VerifyPerm,		       BFCBO::NONE,                    0 }, 
   { ifds::DeletePerm,		       BFCBO::NONE,                    0 },
   { ifds::UserAction,		       BFCBO::NONE,                    0 },
   //BFCBO::CALCULATED_FIELD 
   { ifds::VerifyTrade,		       BFCBO::CALCULATED_FIELD ,       0 }, 
   { ifds::DeleteTrade,		       BFCBO::CALCULATED_FIELD,        0 },
   { ifds::LastTransNumInSetofReq,BFCBO::CALCULATED_FIELD,        0 },   
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
 { I_( "TradeVerificationList" ),   BFCBO::NONE,      0},   
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************

TradeVerification::TradeVerification( BFAbstractCBO &parent ): MFCanBFCbo( parent ),
                   _bVerifyPerm(false), _bDeletePerm(false),  _pTradeOverideRuleWarningsList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

}

//******************************************************************************
TradeVerification::~TradeVerification()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************   
SEVERITY TradeVerification::setParameters(const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup, bool lFormatted/*= false*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setParameter" ) );

   setFieldNoValidate(idField,strValue,idDataGroup,lFormatted);
   setUpdatedFlag( idField, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************   
SEVERITY TradeVerification::setParameters(DString& dstrTransType,DString& dstrAccountNum, const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setParameter" ) );

   setFieldNoValidate(ifds::SearchType,dstrTransType,idDataGroup,false);
   setFieldNoValidate(ifds::AccountNum,dstrAccountNum,idDataGroup,false);
   setUpdatedFlag( ifds::SearchType, idDataGroup, false );
   setUpdatedFlag( ifds::AccountNum, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************   
SEVERITY TradeVerification::setParameters(DString& dstrTransType, DString& dstrAccountNum, 
								          DString& dstrWireOrderNum, const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setParameter" ) );

   setFieldNoValidate(ifds::SearchType,dstrTransType,idDataGroup,false);
   setFieldNoValidate(ifds::AccountNum,dstrAccountNum,idDataGroup,false);
   setFieldNoValidate(ifds::WireOrdNum,dstrWireOrderNum,idDataGroup,false);
   setUpdatedFlag( ifds::SearchType, idDataGroup, false );
   setUpdatedFlag( ifds::AccountNum, idDataGroup, false );
   setUpdatedFlag( ifds::WireOrdNum, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}
//*************************************************************************************
SEVERITY TradeVerification::init ( const BFDataGroupId &idDataGroup,
                                   const DString &track, /*=I_("N")*/
                                   const DString &pageName /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init"));

   TradeVerificationList *pTradeVerificationList;
   TradeVerificationSearch *pTradeVerificationSearch;   
   BFData data;
   pTradeVerificationSearch =  dynamic_cast <TradeVerificationSearch*> (getObject (I_("Criteria"), idDataGroup));
   if( pTradeVerificationSearch )
       pTradeVerificationList = dynamic_cast <TradeVerificationList *>(pTradeVerificationSearch->getObject (TRADE_VERIFICATION_LIST, idDataGroup));
   if( pTradeVerificationList )
       pTradeVerificationList->getData(data,idDataGroup);   
   init(data);
   doInitWithDefaultValues( idDataGroup );
   return GETCURRENTHIGHESTSEVERITY ();
}
////*************************************************************************************
SEVERITY TradeVerification::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   attachDataObject( const_cast<BFData&>(data), false, true);
   DString dstrTransNum;
   data.getElementValue(ifds::TransNum ,dstrTransNum);
   setFieldNoValidate(ifds::TransNum, dstrTransNum, BF::HOST, false, true, false, false);
   doInitWithDefaultValues( BF::HOST );
   return(GETCURRENTHIGHESTSEVERITY());
}
//*************************************************************************************
void TradeVerification::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInitWithDefaultValues") );

   //Create the CBO object for the verification
   setFieldNoValidate(ifds::UserAction,  NULL_STRING, idDataGroup, false, true, false, false);
   setFieldNoValidate(ifds::VerifyTrade, NULL_STRING, idDataGroup,false, true, false, false);
   setFieldNoValidate(ifds::DeleteTrade, NULL_STRING, idDataGroup, false, true, false, false);
   DString dstrVerifyPerm, dstrDeletePerm;
   getField(ifds::VerifyPerm, dstrVerifyPerm, idDataGroup);
   getField(ifds::DeletePerm, dstrDeletePerm, idDataGroup);
   //use the same permisison as in trade and enabled the verify reject fields accordignly for the trade
   _bVerifyPerm = ( dstrVerifyPerm == I_("Y") || 
                    (dstrVerifyPerm != I_("0") && dstrVerifyPerm != I_("3")));
   _bDeletePerm = ( dstrDeletePerm == I_("Y") || 
                    (dstrDeletePerm != I_("0") && dstrDeletePerm != I_("3")));

   setFieldReadOnly(ifds::VerifyTrade ,idDataGroup, !_bVerifyPerm);
   setFieldReadOnly(ifds::DeleteTrade ,idDataGroup, !_bDeletePerm);
}
//*************************************************************************************
SEVERITY TradeVerification::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY TradeVerification::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );

   DString dstrVerifyTrade, dstrDeleteTrade;
   if( idField == ifds::VerifyTrade )
   {      
      getField(ifds::VerifyTrade, dstrVerifyTrade, idDataGroup);
      //the below seems to be whered but this is the once which makes the two check boxes to be like 
      //a radio button working in parallel
      setFieldNoValidate(ifds::DeleteTrade, NULL_STRING, idDataGroup, false, true, true, false); 
      if( YES == dstrVerifyTrade )  
        setFieldNoValidate(ifds::UserAction, USER_ACTION::VERIFY, idDataGroup, false, true, true, false);
      else   
        setFieldNoValidate(ifds::UserAction, NULL_STRING, idDataGroup, false, true, true, false);

      setUpdatedFlag(ifds::UserAction, idDataGroup, YES == dstrVerifyTrade );

   }
   if( idField == ifds::DeleteTrade )
   {
      getField(ifds::DeleteTrade, dstrDeleteTrade, idDataGroup);
      //the below seems to be whered but this is the once which makes the two check boxes to be like 
      //a radio button working in parallel
      setFieldNoValidate(ifds::VerifyTrade, NULL_STRING, idDataGroup, false, true, true, false); 
      if( YES == dstrDeleteTrade )
         setFieldNoValidate(ifds::UserAction, USER_ACTION::DEL, idDataGroup, false, true, true, false);
      else 
         setFieldNoValidate(ifds::UserAction, NULL_STRING, idDataGroup, false, true, true, false);

      setUpdatedFlag(ifds::UserAction, idDataGroup, YES == dstrDeleteTrade); 
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//**************************************************************************************
void TradeVerification::setVerifyDeleteUpdated( const BFDataGroupId& idDataGroup, bool val /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setVerifyDeleteUpdated") );

   setUpdatedFlag( ifds::VerifyTrade, idDataGroup, val );
   setUpdatedFlag( ifds::DeleteTrade, idDataGroup, val );
   setUpdatedFlag( ifds::UserAction, idDataGroup, val );
}
//**************************************************************************************
SEVERITY TradeVerification::setAllTradesVerifyDeleteFlag(const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAllTradesVerifyDeleteFlag") );

  if( idField == ifds::VerifyTrade && _bVerifyPerm )
  { 
   setFieldNoValidate(ifds::VerifyTrade, YES, idDataGroup,false, true, true );
   setFieldReadOnly(ifds::DeleteTrade, idDataGroup, !_bDeletePerm);
   setFieldReadOnly(ifds::VerifyTrade, idDataGroup, !_bVerifyPerm);
   setFieldNoValidate(ifds::DeleteTrade, NULL_STRING, idDataGroup, false, true, true, false);
  // setFieldNoValidate(ifds::UserAction, USER_ACTION::VERIFY,idDataGroup, false, true, true, false);
  } 
  if( idField ==  ifds::DeleteTrade && _bDeletePerm)
  { 
   setFieldNoValidate(ifds::DeleteTrade, YES, idDataGroup, false, true, true );
   setFieldReadOnly(ifds::VerifyTrade, idDataGroup, !_bVerifyPerm);
   setFieldReadOnly(ifds::DeleteTrade, idDataGroup, !_bDeletePerm);
   setFieldNoValidate(ifds::VerifyTrade, NULL_STRING, idDataGroup, false, true, true, false);
   //setFieldNoValidate(ifds::UserAction, USER_ACTION::DEL,idDataGroup, false, true, true, false);
  } 
  if( idField ==  ifds::UserAction )
  {
   setFieldNoValidate(ifds::DeleteTrade, NULL_STRING, idDataGroup, false, true, true);
   setFieldNoValidate(ifds::VerifyTrade, NULL_STRING, idDataGroup, false, true, true);
   setFieldNoValidate(ifds::UserAction,  NULL_STRING, idDataGroup, false, true, true);
   setFieldReadOnly(ifds::VerifyTrade, idDataGroup,!_bVerifyPerm );
   setFieldReadOnly(ifds::DeleteTrade, idDataGroup,!_bDeletePerm);
  }   
  return(GETCURRENTHIGHESTSEVERITY());  
}
//************************************************************************************** 
void TradeVerification::clearAllFlags( const BFDataGroupId& idDataGroup )  
{  
   
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("clearAllFlags") );

   setFieldNoValidate(ifds::VerifyTrade, NULL_STRING, idDataGroup, false, true, true);
   setFieldNoValidate(ifds::DeleteTrade, NULL_STRING, idDataGroup, false, true, true);
   setFieldNoValidate(ifds::UserAction,  NULL_STRING, idDataGroup, false, true, true);
   setFieldReadOnly(ifds::VerifyTrade, idDataGroup, !_bVerifyPerm);
   setFieldReadOnly(ifds::DeleteTrade, idDataGroup, !_bDeletePerm);
}

//************************************************************************************** 
SEVERITY TradeVerification::getTradeOverideRuleWarningsList( TradeOverideRuleWarningsList *&pTradeOverideRuleWarningsList, 
                                                                   const DString& dstrTransNum,const BFDataGroupId& idDataGroup, bool bCreate )                                  
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTradeOverideRuleWarningsList" ) );
    //check cbobase to see if we've already built it
    //otherwise, create and store with base
    DString dstrOldTransNum;
    /*if(_pTradeOverideRuleWarningsList)
        _pTradeOverideRuleWarningsList->getTransNum(dstrOldTransNum);*/

    bCreate = NULL == _pTradeOverideRuleWarningsList ;/*&& (dstrTransNum != dstrOldTransNum); */
    if( !bCreate )
    {
      pTradeOverideRuleWarningsList = _pTradeOverideRuleWarningsList;
      return(GETCURRENTHIGHESTSEVERITY());
    }
    _pTradeOverideRuleWarningsList  = NULL;     
     setObject( NULL, TRADE_OVERIDE_WARNINGS_LIST , OBJ_ACTIVITY_NONE, idDataGroup );     
    pTradeOverideRuleWarningsList = new TradeOverideRuleWarningsList( *this );
	if( pTradeOverideRuleWarningsList ->init(dstrTransNum) <= WARNING && pTradeOverideRuleWarningsList)
    {
        setObject( pTradeOverideRuleWarningsList, TRADE_OVERIDE_WARNINGS_LIST, OBJ_ACTIVITY_NONE, idDataGroup );
        _pTradeOverideRuleWarningsList = *&pTradeOverideRuleWarningsList;
    }
    else
    {
        delete pTradeOverideRuleWarningsList;
        pTradeOverideRuleWarningsList = NULL;
    }
    return(GETCURRENTHIGHESTSEVERITY());
}
//************************************************************************************
SEVERITY TradeVerification::setField( const BFFieldId& idField, const DString& dstrValue,
                                      const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect, bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );
   //dont apply nay chnages to the field  if it doesnt have the permisison
   //this is a hack to avoid the setting of value from the grid window with the single click
   if( ( ifds::VerifyTrade == idField && !_bVerifyPerm )|| ( ifds::DeleteTrade == idField && !_bDeletePerm) ) 
        return(GETCURRENTHIGHESTSEVERITY()); //just return
   BFCBO::setField( idField, dstrValue, idDataGroup, bFormatted, bSideEffect );
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradeVerificationProcess.cpp-arc  $
// 
//    Rev 1.0  22 July 2014
// Initial revision.
*/
















