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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : Broker.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 29/08/2000
//
// ^CLASS    : Broker
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "broker.hpp"
#include "nomineeinteraddr.hpp"
#include "nomineeinteraddrlist.hpp"
#include <ifastdataimpl\dse_dstc0090_req.hpp>
#include <ifastdataimpl\dse_dstc0090_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BROKER_LIST;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "Broker" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
}

namespace CND
{
   extern const long ERR_BROKER_INTERMEDIARY_ADDRESS_NOT_FOUND;
   extern const long ERR_BROKER_INVALID_AS_OF_DATE;
   extern const long ERR_BROKER_NOT_EFFECTIVE;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Default;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,        State Flags,       Group Flags 
   { ifds::BrokerCode, BFCBO::NONE, 0 }, 
   { ifds::KYCRequired, BFCBO::NONE, 0 }, 
   { ifds::FileTypeD, BFCBO::NONE, 0 }, 
   { ifds::FileTypeJ, BFCBO::NONE, 0 }, 
};
static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,                          State Flags,         Group Flags 
   { I_( "NomineeInterAddressList" ),      BFCBO::NONE,        0},

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
Broker::Broker( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   _pResponseData = NULL;

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS,
                       (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//****************************************************************************
Broker::~Broker()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( _pResponseData )
      delete _pResponseData;
}     

//****************************************************************************
SEVERITY Broker::init( const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(InstData), false, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

SEVERITY Broker::init( const DString& strBrokerCode, bool bForceViewCall /*= false*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   if( bForceViewCall )
   {
      BFData requestData (ifds::DSTC0090_REQ);
      BFData *responseData = NULL;
      getResponseData(responseData);

      DString mgmtCoIdOut;
      requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      requestData.setElementValue( ifds::BrokerCode, strBrokerCode );
      requestData.setElementValue( ifds::RequestType, I_("L") );
      requestData.setElementValue( ifds::ValidateType, I_("Trade") );

      SEVERITY sevRtn = BFDataBroker::getInstance()->receive( DSTC_REQUEST::BROKER_LIST, 
                                                              requestData, 
                                                              *responseData, 
                                                              DSTCRequestor( getSecurity(), true) );  

      if( sevRtn <= WARNING )
      {
         BFData* repeat = new BFData( responseData->getRepeat( 0 ));
         attachDataObject( *repeat, true, false );
      }
      else
      {
         delete _pResponseData;
         _pResponseData = NULL;
      }
   }
   else
      setFieldNoValidate( ifds::BrokerCode, strBrokerCode, BF::HOST, false);

   clearUpdatedFlags( BF::HOST );
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

SEVERITY Broker::getNomineeInterAddressList( const BFDataGroupId& idDataGroup, NomineeInterAddrList *&pNomInterAddrList)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDefaultAddress") );
   pNomInterAddrList = NULL;
   DString strBrokerCode;
   getField(ifds::BrokerCode , strBrokerCode, idDataGroup);

   //check cbobase to see if we've already built it
   //if not built, create and store with base
   DString strTag = I_("NomineeInterAddressList");
   pNomInterAddrList = dynamic_cast<NomineeInterAddrList *>( BFCBO::getObject( strTag, idDataGroup ) );
   if( ! pNomInterAddrList )
   {
      pNomInterAddrList = new NomineeInterAddrList( *this );
      if( pNomInterAddrList->init( strBrokerCode ) <= WARNING )
      {
         setObject( pNomInterAddrList, strTag, OBJ_ACTIVITY_NONE, idDataGroup ); 
      }
      else
      {
         delete pNomInterAddrList;
         pNomInterAddrList = NULL;
      }
   }
   if( !pNomInterAddrList )
      ADDCONDITIONFROMFILE( CND::ERR_BROKER_INTERMEDIARY_ADDRESS_NOT_FOUND);
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

void Broker::doPopulateField( const BFFieldId& idField, DString & strValue, bool formattedReturn )
{
   TRACE_METHOD( CLASSNAME, I_( "doPopulateField" ));

   DString strBrokerCode;
   BFData* pResponse = NULL;
   getResponseData(pResponse);
   if( idField != ifds::BrokerCode && BFData::exists( pResponse->getRepeatId(), idField ) )
   {
      BFCBO::getField( ifds::BrokerCode, strBrokerCode, BF::HOST, false );
      if( init(strBrokerCode, true) <= WARNING )
      {
         BFCBO::getField( idField, strValue, BF::HOST, formattedReturn );
      }
   }
}
//****************************************************************************

void Broker::getResponseData(BFData*& pResponse)
{
   if( !_pResponseData )
      _pResponseData = new BFData(ifds::DSTC0090_VW);
   pResponse = _pResponseData;
}

//****************************************************************************

SEVERITY Broker::checkEffective( const DString& dstrAsOfDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isEffective") );
   DString dstrEffectiveDate, dstrStopDate, idiStr;
   getField( ifds::StopDate, dstrStopDate, idDataGroup, false );
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
   
   if ( (DSTCommonFunctions::CompareDates( dstrStopDate,dstrAsOfDate) != DSTCommonFunctions::SECOND_EARLIER) ) {            
      getField( ifds::StopDate, dstrStopDate, idDataGroup, true );
      addIDITagValue( idiStr, I_("DATE"), dstrStopDate);
      ADDCONDITIONFROMFILEIDI( CND::ERR_BROKER_INVALID_AS_OF_DATE, idiStr );
   } else if ( (DSTCommonFunctions::CompareDates( dstrAsOfDate, dstrEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER) ) {
      getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, true );
      addIDITagValue( idiStr, I_("DATE"), dstrEffectiveDate);
      ADDCONDITIONFROMFILEIDI( CND::ERR_BROKER_NOT_EFFECTIVE, idiStr );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

bool Broker::isHouseBroker( const BFDataGroupId& idDataGroup )
{
   DString dstrHouseBroker = NO;
   getField ( ifds::HouseBroker, dstrHouseBroker, idDataGroup );
   return (dstrHouseBroker == YES );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Broker.cpp-arc  $
 // 
 //    Rev 1.17   Jul 27 2005 18:43:06   AGUILAAM
 // IN 353952 - refine validations of Systematic records against broker/branch/rep effective/stop dates.
 // 
 //    Rev 1.16   Nov 14 2004 14:29:16   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.15   Apr 05 2004 17:29:38   FENGYONG
 // PET944 FN01, release 56.1 NSCC Broker Matrix
 // 
 //    Rev 1.14   Aug 19 2003 09:07:40   HSUCHIN
 // added isHouseBroker
 // 
 //    Rev 1.13   Jul 11 2003 16:13:34   FENGYONG
 // add field KYCRequired
 // 
 //    Rev 1.12   Mar 21 2003 18:01:02   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.11   Mar 05 2003 11:59:52   HSUCHIN
 // PTS 10014446 - added new method checkEffective to check whether the broker is effective or not
 // 
 //    Rev 1.10   Jan 03 2003 17:43:50   WINNIE
 // Add validationtype as new parameter. View side expect a value.
 // 
 //    Rev 1.9   Oct 09 2002 23:54:06   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.8   Aug 29 2002 12:55:10   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.7   22 May 2002 18:26:32   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.6   29 Nov 2001 14:32:38   KOVACSRO
 // code clean up.
 // 
 //    Rev 1.5   15 Oct 2001 12:00:42   KOVACSRO
 // all the brokers are added at BF::HOST level.
 // 
 //    Rev 1.4   03 May 2001 14:06:02   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.3   Feb 16 2001 13:02:00   DINACORN
 // Add Revision Control Entries
 * 
 */