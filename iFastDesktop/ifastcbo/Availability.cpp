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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : Availabilty.cpp
// ^AUTHOR : Cristina Oltean
// ^DATE   : Jan, 2001
//
// ^CLASS    : Availabilty
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "availability.hpp"
#include <ifastdataimpl\dse_dstc0150_req.hpp>
#include <ifastdataimpl\dse_dstc0150_vw.hpp>
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AVAILABILITY;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "Availability" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,     Group Flags 
   { ifds::Track,    BFCBO::NONE, 0 }, 
   { ifds::Activity, BFCBO::NONE, 0 }, 
   { ifds::Trading,  BFCBO::NONE, 0 }, 
   { ifds::Inquiry,  BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


namespace CND
{  // Conditions used
   // extern const long ERR_EFFECTIVE_DATE_BACKWARD;
}

//******************************************************************************
Availability::Availability( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
Availability::~Availability()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}



//******************************************************************************
SEVERITY Availability::init( const DString& dstrTrack, const DString& dstrActivity )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0150_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrActivity );

   ReceiveData( DSTC_REQUEST::AVAILABILITY, queryData, ifds::DSTC0150_VW,DSTCRequestor( getSecurity(), false ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void Availability::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{

   setFieldNoValidate( ifds::Trading, I_("N"), idDataGroup );
   setFieldNoValidate( ifds::Inquiry, I_("N"), idDataGroup );

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Availability.cpp-arc  $
// 
//    Rev 1.9   Nov 14 2004 14:27:48   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Mar 21 2003 17:59:48   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:54:02   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 12:55:04   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   22 May 2002 18:26:26   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   03 May 2001 14:05:58   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.3   Feb 16 2001 12:09:52   DINACORN
// Add Revision Control Entries
 * 
 */
