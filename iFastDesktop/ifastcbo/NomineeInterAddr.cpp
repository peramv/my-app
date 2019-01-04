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
// ^FILE   : NomineeInterAddr.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/08/2000
//
// ^CLASS    : NomineeInterAddr
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "nomineeinteraddr.hpp"
#include "nomineeinteraddrlist.hpp"
#include <ifastdataimpl\dse_dstc0116_req.hpp>
#include <ifastdataimpl\dse_dstc0116_vw.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "NomineeInterAddr" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,        State Flags,       Group Flags 
   { ifds::BrokerCode,    BFCBO::REQUIRED, 0 }, 
   { ifds::BrokerName,    BFCBO::NONE,     0 }, 
   { ifds::RegAddrCode,   BFCBO::NONE,     0 }, 
   { ifds::Addr11Line1,   BFCBO::NONE,     0 }, 
   { ifds::Addr11Line2,   BFCBO::NONE,     0 }, 
   { ifds::Addr11Line3,   BFCBO::NONE,     0 }, 
   { ifds::Addr11Line4,   BFCBO::NONE,     0 }, 
   { ifds::Addr11Line5,   BFCBO::NONE,     0 }, 
   { ifds::AddrCntryCode, BFCBO::NONE,     0 }, 
   { ifds::PostalCode,    BFCBO::NONE,     0 }, 
   { ifds::Default,       BFCBO::NONE,     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,    State Flags,         Group Flags 
   {  I_(""),        BFCBO::NONE,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
NomineeInterAddr::NomineeInterAddr( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS,
                       (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//****************************************************************************
NomineeInterAddr::~NomineeInterAddr()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
SEVERITY NomineeInterAddr::init( const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(InstData), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/NomineeInterAddr.cpp-arc  $
 // 
 //    Rev 1.8   Nov 14 2004 14:50:46   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.7   Oct 09 2002 23:54:48   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.6   Aug 29 2002 12:56:22   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.5   22 May 2002 18:29:36   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.4   03 May 2001 14:06:54   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.3   Feb 19 2001 12:30:38   DINACORN
 // Add Revision Control Entries
 * 
 */
