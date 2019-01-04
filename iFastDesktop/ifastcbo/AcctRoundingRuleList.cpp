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
//    Copyright 2008 by IFDS Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctRoundingRuleList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AcctRoundingRuleList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "AcctRoundingRuleList.hpp"
#include "AcctRoundingRule.hpp"
#include "mfaccount.hpp"

#include <ifastdataimpl\dse_dstc0480_req.hpp>
#include <ifastdataimpl\dse_dstc0480_vw.hpp>
#include <ifastdataimpl\dse_dstc0480_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest ACCT_ROUNDING_RULE_INQUIRY;
}

namespace
{
    const I_CHAR * const CLASSNAME = I_( "AcctRoundingRuleList" );
}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

namespace CND
{ 
	extern const long ERR_ACCOUNT_ROUNDING_RULE_EXISTS;
	extern const long WARN_ACCOUNT_ROUNDING_RULE_EXISTS;
}

namespace IFASTERR
{  		
	extern CLASS_IMPORT I_CHAR * const ACCOUNT_ROUNDING_RULE_EXISTS;	
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
    // Field DD Id,             State Flags,            Group Flags
    { ifds::AccountNum,			BFCBO::NONE,			0 },	    
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
AcctRoundingRuleList::AcctRoundingRuleList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
, m_requestData( ifds::DSTC0480_REQ )
{
    TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

    setObjectAsList( );
	registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
}

//******************************************************************************
AcctRoundingRuleList::~AcctRoundingRuleList(void)
{
    TRACE_DESTRUCTOR( CLASSNAME );   
}

//******************************************************************************
void AcctRoundingRuleList::getStrKey( DString &dstrKey, const BFData *data)
{
   if ( data )
   {      
      buildKey( dstrKey, _accountNum);
   }
   else
   {
      BFCBO::getStrKey (dstrKey, NULL);
   }
}

//******************************************************************************
SEVERITY AcctRoundingRuleList::initNew( const DString &strAccountNumber,
                                        const BFDataGroupId& idDataGroup,
                                        const DString &strTrack,
                                        const DString &strPageName )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

    _accountNum = strAccountNumber;

    return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctRoundingRuleList::init( const DString &strAccountNumber,
                                     const BFDataGroupId& idDataGroup,                                        
                                     const DString &strTrack,
                                     const DString &strPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   DString mgmtCoIdOut;

   _accountNum = strAccountNumber;  

   BFData responseData(ifds::DSTC0480_VW);
  
   // Set request fields
   m_requestData.setElementValue( ifds::Track, strTrack );
   m_requestData.setElementValue( ifds::Activity, strPageName );
   m_requestData.setElementValue( ifds::AccountNum, strAccountNumber );      
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );

   ReceiveData( DSTC_REQUEST::ACCT_ROUNDING_RULE_INQUIRY, m_requestData, ifds::DSTC0480_VW, DSTCRequestor(getSecurity()) );

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctRoundingRuleList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new AcctRoundingRule( *this );
   ((AcctRoundingRule*) pObjOut )->init( data );

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctRoundingRuleList::doCreateNewObject( BFCBO *&pObjOut, 
                                                  DString &strKey, 
                                                  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pObjOut = new AcctRoundingRule( *this );
   ((AcctRoundingRule*) pObjOut )->initNew( _accountNum, idDataGroup );

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
void AcctRoundingRuleList::buildKey( DString &dstrKey, 
									 const DString &dstrAccountNum
									)
{
    DString strAccountNum(dstrAccountNum);          

    dstrKey = I_("AccountNum=") + strAccountNum.stripAll();
}

//******************************************************************************
SEVERITY AcctRoundingRuleList::validateRoundingRule( const BFDataGroupId &idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateRoundingRule"));	

	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

	int nItems = iter.getNumberOfItemsInList();

	if (nItems > 1) // 1960 - Account Rounding Rules record already exists.
	{
		getErrMsg( IFASTERR::ACCOUNT_ROUNDING_RULE_EXISTS, 	  
				   CND::ERR_ACCOUNT_ROUNDING_RULE_EXISTS, 		  
				   CND::WARN_ACCOUNT_ROUNDING_RULE_EXISTS, 	
				   idDataGroup); 		  
	} 

	return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctRoundingRuleList::doValidateAll( const BFDataGroupId& idDataGroup, 
                                              long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   validateRoundingRule( idDataGroup);
   
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctRoundingRuleList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData( DSTC_REQUEST::ACCT_ROUNDING_RULE_INQUIRY, m_requestData, ifds::DSTC0480_VW, DSTCRequestor(getSecurity()) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


