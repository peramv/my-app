//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : UnitFactor.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "UnitFactor.hpp"
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0313_req.hpp>
#include <ifastdataimpl\dse_dstc0313_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "UnitFactor" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,			Group Flags 
   { ifds::UnitId,           BFCBO::NONE,                 0 }, 
   { ifds::UnitFactor,       BFCBO::NONE,                 0 },
   { ifds::UnitFactorDesc,   BFCBO::NONE,                 0 }, 
   { ifds::FactorRate,       BFCBO::NONE,                 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

UnitFactor::UnitFactor( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************

UnitFactor::~UnitFactor()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************

SEVERITY UnitFactor::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
   clearUpdatedFlags( BF::HOST );

	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************

void UnitFactor::initNew(const BFDataGroupId& idDataGroup )
{
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/UnitFactor.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:59:06   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Sep 09 2004 11:27:44   HERNANDO
// Initial revision.
