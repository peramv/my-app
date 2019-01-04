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
// ^FILE   : FundGroupType.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 01/09/02
//
// ^CLASS    : FundGroupType
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "FundGroupType.hpp"


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME   = I_( "FundGroupType" );
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

FundGroupType::FundGroupType( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   //setVersionable( false );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);
}

//******************************************************************************
FundGroupType::~FundGroupType()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     
//******************************************************************************

void FundGroupType::init(const BFData& data)
{
   attachDataObject(const_cast<BFData&>(data), true, false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundGroupType.cpp-arc  $
// 
//    Rev 1.3   Nov 24 2004 10:18:32   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.2   Nov 18 2004 13:28:08   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.1   Nov 14 2004 14:42:32   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Jan 13 2003 10:15:02   KOVACSRO
// Initial revision.

*/
