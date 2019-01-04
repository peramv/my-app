//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : BrokerAMSList.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Feb 21, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : BrokerAMSList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "BrokerAMSList.hpp"
#include "BrokerAMS.hpp"
#include <ifastdataimpl\dse_dstc0250_req.hpp>
#include <ifastdataimpl\dse_dstc0250_vw.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest AMS_BROKER_LIST;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "BrokerAMSList" );
   const I_CHAR * const YES		 = I_( "Y" );
   const I_CHAR * const NO			 = I_( "N" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,							State Flags,				Group Flags
   { ifds::BrokerCode,  BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

BrokerAMSList::BrokerAMSList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_requestData(ifds::DSTC0250_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
   setObjectAsList();
}

//*****************************************************************************
BrokerAMSList::~BrokerAMSList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
SEVERITY BrokerAMSList::init( const DString& dstrBrokerCode, 
                            const DString& dstrAMSCode, 
                            const bool Allresult,
                            const DString& dstrTrack,
                            const DString& dstrPageName )               
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   //strOverrideRepeats should be less or equal to MaxRepeatCount (that's a backend rule)
   //if called with default -1 for nNoOfNewItems, the list could grow up to maxRepeatCount (25) elements
   //if called with 0 for nNoOfNewItems, the list will grow to contain all the existing elements
   //if called with a positive number for nNoOfNewItems, the list could grow up to the specified number of elements

   DString strOverrideRepeats = I_("-1");
   DString dstrexactmatch = I_("N");

   _dstrBrokerCode = dstrBrokerCode;

   if (Allresult)
   {
      strOverrideRepeats = I_("0");
   }

   if(dstrAMSCode != NULL_STRING ) dstrexactmatch = I_("Y");

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::BrokerCode, dstrBrokerCode );
   _requestData.setElementValue( ifds::AMSCode, dstrAMSCode );
   _requestData.setElementValue( ifds::OverrideRepeats,   strOverrideRepeats );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
   _requestData.setElementValue( ifds::ExactMatch, dstrexactmatch );
   

   ReceiveData(DSTC_REQUEST::AMS_BROKER_LIST, _requestData, ifds::DSTC0250_VW, DSTCRequestor( getSecurity(), Allresult, false ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY BrokerAMSList::initExisting(const DString& dstrBrokerCode, 
                            const DString& dstrAMSCode, 
                            const bool Allresult,const DString& dstrTrack,
							const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reinit" ) );

   //setListFields(BF::HOST);
   if( !isNew() )
   {
      init( dstrBrokerCode, dstrAMSCode,  Allresult);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY BrokerAMSList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::AMS_BROKER_LIST, _requestData, ifds::DSTC0250_VW, DSTCRequestor( getSecurity(), false ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void BrokerAMSList::buildKey( const DString& strGoodBad, const DString& strAMSCode, DString &strKey )
{
   strKey = strAMSCode;
   strKey.strip();
   strKey += I_(" ");
   strKey +=strGoodBad;
   strKey.strip();
   strKey.upperCase();
}

//******************************************************************************
void BrokerAMSList::getStrKey (DString &strKey, const BFData *data)
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString strAMSCode = data->getElementValue( I_( "AMSCode" ) );
	  DString strGoodBad = data->getElementValue( I_( "GoodBad" ) );
	  
      strKey = strAMSCode.strip();
	  strKey += I_(" ");
	  strKey +=strGoodBad.strip();
      strKey.upperCase();
   }
   else
   {
     BFCBO::getStrKey( strKey , NULL );
   }
}

//******************************************************************************
SEVERITY BrokerAMSList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   BrokerAMS * pBrokerAMS = new BrokerAMS( *this );
   pBrokerAMS->init( this, data );
   pObjOut = pBrokerAMS;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY BrokerAMSList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new BrokerAMS( *this );
   ((BrokerAMS* )pBase)->init( this, idDataGroup ); 
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY BrokerAMSList::getBrokerAMS( const DString &dstrAMSCode, 
												  const DString &dstrGoodBad,
		                                const BFDataGroupId& idDataGroup,
							            	  BrokerAMS *&pBrokerAMS )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getBrokerAMS" ) );

	pBrokerAMS = NULL;
	DString dstrLocalAMSCode( dstrAMSCode ),
		     dstrLocalGoodBad( dstrGoodBad );

	DString dstrKey = dstrLocalAMSCode.strip() 
		             + I_(" ")
	                + dstrLocalGoodBad.strip();
   dstrKey.upperCase();
   
   pBrokerAMS = dynamic_cast<BrokerAMS * >( getObject( dstrKey, idDataGroup ) );

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
void BrokerAMSList::getTrackActivity(DString& strTrack,DString& strActivity)
{
   strTrack = I_("Y");
   strActivity = I_("BrokerAMS");
}

//******************************************************************************
SEVERITY BrokerAMSList::setField(const BFFieldId& idField, const DString& dstrValue,
                         const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect, bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setField"));
   
   BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);

   if(idField == ifds::BrokerCode)
   {
		setUpdatedFlag( ifds::BrokerCode, idDataGroup, false );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
bool BrokerAMSList::isAMSCodeValid( DString& dstrAMSCode,const BFDataGroupId& idDataGroup,bool bValid0001 )
{
	bool bValid = false;
	dstrAMSCode.strip();
	if( bValid0001 == false && dstrAMSCode ==  I_("0001") )
		return false;
    BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   /*
	DString strkey;
	buildKey(I_("Y"), dstrAMSCode, strkey);
	
	if add two new CBOs, with same AMSCode, the key of the new CBO will be 9990000n instead of AMDCode and GoodBad.
	if(iter.positionByKey( strkey ) )
	{
		bValid = true;	
	}
	else{
		bValid = isAmsCodeExistAtbackEnd(dstrAMSCode, idDataGroup );	
	}*/

	DString GoodBad, AMSCode;
	int cnt = 0;
	while(!iter.end())
	{
		iter.getObject( )->getField(ifds::AMSCode, AMSCode, idDataGroup );
		iter.getObject( )->getField(ifds::GoodBad, GoodBad, idDataGroup );
		if( GoodBad == YES && AMSCode.upperCase() == dstrAMSCode.upperCase() )	cnt ++;
		++iter;
	}
	if(cnt > 1) bValid = true;
	else
	{
		bValid = isAmsCodeExistAtbackEnd(dstrAMSCode, idDataGroup );
	}
	return bValid;
}

//********************************************************************************************
bool BrokerAMSList::isAmsCodeExistAtbackEnd(const DString& dstrAMSCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAmsCodeExistAtbackEnd") );

	BFData requestData(ifds::DSTC0250_REQ);
	DString dstrTrack(NO);
	DString dstrPageName( NULL_STRING );

    DString mgmtCoIdOut;
    requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
    requestData.setElementValue( ifds::BrokerCode, _dstrBrokerCode );
    requestData.setElementValue( ifds::AMSCode, dstrAMSCode );
    requestData.setElementValue( ifds::OverrideRepeats,   I_("-1") );
    requestData.setElementValue( ifds::Track, dstrTrack );
    requestData.setElementValue( ifds::Activity, dstrPageName );
    requestData.setElementValue( ifds::ExactMatch, YES );
    requestData.setElementValue( ifds::NextKey,     NULL_STRING );
	
    SEVERITY sevRtn = SEVERE_ERROR;
	DSTCRequestor requestor( getSecurity(), true, true );
	BFData receivedData(ifds::DSTC0250_VW);
	bool bExist = false;

    if( BFDataBroker::getInstance( )->receive( DSTC_REQUEST::AMS_BROKER_LIST, 
		requestData, receivedData, requestor )<= WARNING )
	{
		bExist = true;
	}
	CLEARCONDITIONS();
	return bExist;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BrokerAMSList.cpp-arc  $
// 
//    Rev 1.13   Mar 10 2009 10:53:38   jankovii
// IN 1619627 - Account Level AMS screen
// 
//    Rev 1.12   Nov 14 2004 14:29:22   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.11   Nov 20 2003 17:11:52   ZHANGCEL
// PTS 10023667: Back out 1.10 to 1.9
// 
//    Rev 1.9   Nov 05 2003 11:41:58   VADEANUM
// PTS 10023031 - Unable to assign pre-existing AMS model to account AMS - removed isAmsCodeAndDateValid(), moved validation to list item according to OO principles.
// 
//    Rev 1.8   Jun 19 2003 11:29:52   HERNANDO
// PTS 10018460 - Fixed duplicate checking and Description display.
// 
//    Rev 1.7   Apr 16 2003 11:32:00   FENGYONG
// Add more button
// 
//    Rev 1.6   Apr 15 2003 10:45:10   linmay
// Sync up with 1.4.1.0
// 
//    Rev 1.5   Mar 21 2003 18:01:12   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Mar 14 2003 17:24:40   FENGYONG
// Add setfield for AMS code
// 
//    Rev 1.3   Mar 14 2003 15:32:30   FENGYONG
// Add setfield for brokercode
// 
//    Rev 1.2   Mar 14 2003 11:01:00   FENGYONG
// Add BrokerCode as a list level field
// 
//    Rev 1.1   Mar 07 2003 16:45:54   FENGYONG
// groupid fix
// 
//    Rev 1.0   Mar 03 2003 16:33:54   FENGYONG
// Initial revision.
 * 
// 
*/