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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : RedCodeByTaxType.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/20/2000
//
// ^CLASS    : RedCodeByTaxType
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "redcodebytaxtype.hpp"
#include "redcodebytaxtypelist.hpp"
#include <ifastdataimpl\dse_dstc0138_vwrepeat_record.hpp>

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::RedCode,     BFCBO::NONE, 0 }, 
   { ifds::RedCodeDesc, BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "RedCodeByTaxType" );
}




RedCodeByTaxType::RedCodeByTaxType( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);
}

RedCodeByTaxType::~RedCodeByTaxType()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

SEVERITY RedCodeByTaxType::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject(const_cast<BFData&>(data), false, true );  //true
   return(GETCURRENTHIGHESTSEVERITY());

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RedCodeByTaxType.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:51:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Oct 09 2002 23:54:50   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:56:26   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   22 May 2002 18:29:40   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   03 May 2001 14:06:58   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.1   May 09 2000 11:36:04   YINGZ
// initial revision

*/
