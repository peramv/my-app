//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundType.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 01/09/02
//
// ^CLASS    : FundType
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "FundGroupSub.hpp"


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME   = I_( "FundGroupSub" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundType;
   extern CLASS_IMPORT const BFTextFieldId FundGroup;

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::FundType,    BFCBO::NONE, 0 }, 
   { ifds::FundGroup,   BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

FundGroupSub::FundGroupSub( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);
}

//******************************************************************************
FundGroupSub::~FundGroupSub()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     
//******************************************************************************

void FundGroupSub::init(const BFData& data)
{
   attachDataObject(const_cast<BFData&>(data), false, true);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundGroupSub.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:42:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Sep 23 2004 18:13:26   popescu
// PET1094 FN06 - Absatzmeldung Files enhancement
// 
//    Rev 1.0   Jan 12 2003 19:03:30   KOVACSRO
// Initial revision.
// 
// 

*/
