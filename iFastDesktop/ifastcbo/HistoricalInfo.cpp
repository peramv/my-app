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
//    Copyright 2000 by DST Systems, Inc.
//
//*****************************************************************************
//
//    ^FILE   : HistoricalInfo.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : Jan 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : HistoricalInfo
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "HistoricalInfo.hpp"
#include <ifastdataimpl\dse_dstc0249_vwrepeat_record.hpp>

namespace 
{
   const I_CHAR *  CLASSNAME = I_( "HistoricalInfo" );
}

namespace CND
{  // Conditions used
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,        State Flags,       Group Flags 
   { ifds::FieldLabel,  BFCBO::NONE, 0 }, 
   { ifds::PreviousDisp, BFCBO::NONE, 0 }, 
   { ifds::NewDisp, BFCBO::NONE, 0 }, 
   { ifds::ModDate, BFCBO::NONE, 0 }, 
   { ifds::ModTime, BFCBO::NONE, 0 }, 
   { ifds::ModUser, BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//******************************************************************************
HistoricalInfo::HistoricalInfo( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//******************************************************************************
HistoricalInfo::~HistoricalInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY HistoricalInfo::init(const BFData &viewData)
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   attachDataObject( const_cast<BFData&>( viewData ), false, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HistoricalInfo.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:43:58   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Jan 28 2003 13:16:04   popescu
// Historical Info feature implementation
// 
//    Rev 1.1   Jan 26 2003 16:10:28   popescu
// List and CBO object for the Historical Info feature
// 
//    Rev 1.0   Jan 26 2003 15:53:30   popescu
// Initial Revision
// 
 */