//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2009 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : SystemVerificationDetailsList.cpp
// ^AUTHOR : 
// ^DATE   : Nov, 2009
//
// ^CLASS    : SystemVerificationDetailsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0400_vw.hpp>
#include <ifastdataimpl\dse_dstc0400_req.hpp>
#include <ifastdataimpl\dse_dstc0400_vwrepeat_record.hpp>

#include "SystemVerificationDetails.hpp"
#include "SystemVerificationDetailsList.hpp"

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest SYSTEM_VERIFICATION_DETAILS_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "SystemVerificationDetailsList" );
}

namespace ifds
{
}

namespace CND
{
}

//const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
//{
//   // Field DD Id,                     State Flags,          Group Flags 
//};
//
//static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
SystemVerificationDetailsList::SystemVerificationDetailsList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //registerMemberData( NUM_FIELDS,
   //                    (const CLASS_FIELD_INFO *)&classFieldInfo,
   //                    0,
   //                    NULL );

   setObjectAsList( );
}

//******************************************************************************
SystemVerificationDetailsList::~SystemVerificationDetailsList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************
SEVERITY SystemVerificationDetailsList::init( const DString& dstrTrack,
                                              const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init( DString&, BFDataGroupId& )"));

   DString mgmtCoIdOut;
   BFData requestData (ifds::DSTC0400_REQ);

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName);

   ReceiveData( DSTC_REQUEST::SYSTEM_VERIFICATION_DETAILS_INQUIRY,
                requestData, 
                ifds::DSTC0400_VW, 
                DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SystemVerificationDetailsList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new SystemVerificationDetails( *this );
   ((SystemVerificationDetails*) pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SystemVerificationDetailsList::canVerify (const BFDataGroupId &idDataGroup,
												   const DString &dstrVerifyCategory, 
												   const DString &dstrVerifyLevel,
												   DString &dstrActive,
												   DString &dstrVerifyFilter)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canVerify" ) );

	DString tmpVerifyCategory, tmpVerifyLevel;

	BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

    while( !iter.end() )
    {
		BFAbstractCBO* pObj = iter.getObject();
        if( pObj )
        {
            pObj->getField(ifds::VerifyCategory, tmpVerifyCategory,idDataGroup,false );
            pObj->getField(ifds::VerifyLevel, tmpVerifyLevel,idDataGroup,false );
            tmpVerifyCategory.strip();
            tmpVerifyLevel.strip();
            
			if (tmpVerifyCategory == dstrVerifyCategory && tmpVerifyLevel == dstrVerifyLevel)
			{
				pObj->getField(ifds::Active, dstrActive,idDataGroup, false);
				pObj->getField(ifds::VerifyFilter, dstrVerifyFilter, idDataGroup, false );
				break;
			}
        }
        ++iter;
    }
   
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SystemVerificationDetailsList.cpp-arc  $
// 
//    Rev 1.1   Nov 17 2009 15:13:56   jankovii
// PET0166583 FN01 Static Data Changes Banking 
// 
//    Rev 1.0   Nov 16 2009 06:17:34   dchatcha
// Initial revision.
// 
