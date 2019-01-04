//*****************************************************************************
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
//*****************************************************************************
//
// ^FILE   : BrokerList.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : November 07, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : BrokerList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "broker.hpp"
#include "brokerlist.hpp"
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
   const I_CHAR * const CLASSNAME = I_( "BrokerList" );
}

//*****************************************************************************
BrokerList::BrokerList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), requestData90( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//*****************************************************************************
BrokerList::~BrokerList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
SEVERITY BrokerList::init(const BFDataGroupId& idDataGroup, 
   const DString& dstrTrack /*=I_("N")*/, 
   const DString& dstrPageName /*=NULL_STRING*/)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   //this method does nothing, used to match the getObject_X template function
   //in DSTCWorkSession

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY BrokerList::init(const DString& dstrBrokerCode, 
   const DString& dstrSrchBrokerName,  const DString& dstrRequestType,
   const DString& dstrTrack, const DString& dstrPageName, bool allResults)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   
   init2(dstrBrokerCode, dstrSrchBrokerName, 
      dstrRequestType, NULL_STRING, I_("Trade"), dstrTrack, dstrPageName, allResults );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

SEVERITY BrokerList::init2(const DString&  dstrBrokerCode, 
   const DString& dstrSrchBrokerName, const DString& dstrRequestType, 
   const DString& dstrAccountNum, const DString& dstrValidateType,
   const DString& dstrTrack, const DString& dstrPageName, bool allResults)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   //BFData queryData(ifds::DSTC0090_REQ);
   //BFData *receivedData = new BFData(ifds::DSTC0090_VW);
   if (requestData90)
   {
      delete requestData90;
      requestData90 = NULL;
   }
	requestData90 = new BFData(ifds::DSTC0090_REQ);
	
   DString mgmtCoIdOut;
   requestData90->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData90->setElementValue( ifds::BrokerCode, dstrBrokerCode );
   requestData90->setElementValue( ifds::SrchBrokerName, dstrSrchBrokerName );
   requestData90->setElementValue( ifds::RequestType, dstrRequestType );
   requestData90->setElementValue( ifds::AccountNum, dstrAccountNum );
   requestData90->setElementValue( ifds::ValidateType, dstrValidateType );
   requestData90->setElementValue( ifds::Track, dstrTrack );
   requestData90->setElementValue( ifds::Activity, dstrPageName );

   //ReceiveData( DSTC_REQUEST::BROKER_LIST, queryData, *receivedData, DSTCRequestor( getSecurity() ) );
   BFData* responseData = new BFData (ifds::DSTC0090_VW);
   ReceiveData( DSTC_REQUEST::BROKER_LIST, *requestData90, *responseData, DSTCRequestor( getSecurity(), allResults ) );

   return(GETCURRENTHIGHESTSEVERITY());
}


//*****************************************************************************

SEVERITY BrokerList::initNSCC(const DString&  dstrBrokerCode, 
   const DString& dstrSrchBrokerName, const DString& dstrRequestType, 
   const DString& dstrAccountNum, const DString& dstrValidateType,
	const DString& dstrClearingFirmBroker, const DString& dstrRelationType,
   const DString& dstrTrack, const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   BFData queryData(ifds::DSTC0090_REQ);
   BFData *receivedData = new BFData(ifds::DSTC0090_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::BrokerCode, dstrBrokerCode );
   queryData.setElementValue( ifds::SrchBrokerName, dstrSrchBrokerName );
   queryData.setElementValue( ifds::RequestType, dstrRequestType );
   queryData.setElementValue( ifds::AccountNum, dstrAccountNum );
	queryData.setElementValue( ifds::ClearingFirmBroker, dstrClearingFirmBroker );
	queryData.setElementValue( ifds::RelationType, dstrRelationType );
   queryData.setElementValue( ifds::ValidateType, dstrValidateType );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::BROKER_LIST, queryData, *receivedData, DSTCRequestor( getSecurity() ) );


   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
SEVERITY BrokerList::initFundAllowed( const DString&  dstrBrokerCode, 
                                      const DString&  dstrFundCode, 
                                      const DString&  dstrClassCode,
                                      const DString&  dstrAccountNum,
                                      const DString&  dstrTransType,
                                      const DString&  dstrValidateType,
                                      const DString& dstrTrack,
                                      const DString& dstrPageName )     

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("initFundAllowed") );


   BFData queryData(ifds::DSTC0090_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::BrokerCode, dstrBrokerCode );
   queryData.setElementValue( ifds::SrchBrokerName, NULL_STRING );
   queryData.setElementValue( ifds::RequestType, I_( "L" )  );
   queryData.setElementValue( ifds::FundCode, dstrFundCode  );
   queryData.setElementValue( ifds::ClassCode, dstrClassCode  );
   queryData.setElementValue( ifds::TransType, dstrTransType  );
   queryData.setElementValue( ifds::AccountNum, dstrAccountNum );
   queryData.setElementValue( ifds::ValidateType, dstrValidateType );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::BROKER_LIST, queryData, ifds::DSTC0090_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

SEVERITY BrokerList::getBroker(DString strBrokerCode, Broker *&pBroker)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBroker") );
   pBroker = NULL;

   BFObjIter iterBroker(*this, BF::HOST);//doesn't matter who (which lDataGroup) added this broker. All brokers are set with BF::HOST
   iterBroker.positionByKey( strBrokerCode );
   if( !iterBroker.end() )
      // A match was found, get the CBO  
      pBroker = static_cast<Broker *>( iterBroker.getObject());
   else
   //broker not in the list; add it
   //don't make the view call at this moment; doPopulateField() will do it
   {
      pBroker = new Broker( *this );
      if( pBroker->init( strBrokerCode.strip() ) <= WARNING )
         setObject( pBroker, strBrokerCode );
      else
      {
         delete pBroker;
         pBroker = NULL;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//*****************************************************************************

SEVERITY BrokerList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new Broker( *this );
   ((Broker*) pObjOut)->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
void BrokerList::getStrKey( DString &strKey, const BFData *data )  //key by Broker Code
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data != NULL )
   {
      DString strBrokerCode;

      strBrokerCode = data->getElementValue( ifds::BrokerCode );
      strKey = strBrokerCode.strip();
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}

//******************************************************************************
SEVERITY BrokerList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::BROKER_LIST, *requestData90, ifds::DSTC0090_VW, DSTCRequestor(getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BrokerList.cpp-arc  $
 * 
 *    Rev 1.27   Apr 07 2009 01:09:42   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. - additional code changes for More button
 * 
 *    Rev 1.26   Apr 06 2009 04:29:58   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. - additional code changes for More button
 * 
 *    Rev 1.25   Apr 06 2009 04:20:42   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. - additional code changes for More button
 * 
 *    Rev 1.24   Jul 06 2005 10:58:10   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.23   Nov 14 2004 14:29:26   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.22   May 27 2003 18:29:30   popescu
 * due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
 * 
 *    Rev 1.21   Mar 21 2003 18:01:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.20   Jan 12 2003 15:29:40   WINNIE
 * Remove initFundAllow2 and modify initFundAllow to take the new parameters; Correct the order of input parameter to be the same a hpp
 * 
 *    Rev 1.19   Jan 03 2003 09:37:10   HSUCHIN
 * created init2/initFundAllowed2 to support dynamic
 * 
 *    Rev 1.18   Oct 09 2002 23:54:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.17   Aug 29 2002 12:55:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.16   22 May 2002 18:26:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.15   25 Feb 2002 09:42:30   WINNIE
 * Navigator : Broker exception list enhancement
 * 
 *    Rev 1.14   29 Nov 2001 14:33:24   KOVACSRO
 * code clean up.
 * 
 *    Rev 1.13   15 Oct 2001 12:01:52   KOVACSRO
 * All the brokers are added at host level.
 * 
 *    Rev 1.12   03 May 2001 14:06:02   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.11   Jan 18 2001 16:04:12   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.10   Dec 17 2000 20:22:42   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.9   Dec 06 2000 10:22:32   OLTEANCR
 * changed ReceiveData
 * 
 *    Rev 1.8   Nov 02 2000 14:37:20   YINGBAOL
 * change list name
 * 
 *    Rev 1.7   Nov 01 2000 11:50:50   OLTEANCR
 * new data brokering 
 * 
 *    Rev 1.6   Oct 27 2000 12:21:38   KOVACSRO
 * Modified getStrKey().
 * 
 *    Rev 1.5   Sep 20 2000 11:55:38   KOVACSRO
 * Modified getBroker() to use positionByKey().
 * 
 *    Rev 1.4   Sep 06 2000 16:44:52   KOVACSRO
 * Deleted getDefaultAddress() and added getBroker().
 * 
 *    Rev 1.3   Aug 18 2000 16:51:36   KOVACSRO
 * added Default field logic for getDefaultAddress.
 * 
 *    Rev 1.2   Aug 18 2000 16:33:14   WINNIE
 * Add new method to check if fund is allowed for the broker
 * 
 *    Rev 1.1   Aug 11 2000 14:23:44   KOVACSRO
 * added getDefaultAddress for a broker.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:50   SMITHDAV
 * Initial revision.
// 
//    Rev 1.3   Jan 05 2000 20:10:38   BUZILA
// adding list flag
// 
//    Rev 1.2   Dec 12 1999 16:25:12   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
*/