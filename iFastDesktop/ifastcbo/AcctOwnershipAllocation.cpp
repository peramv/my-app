//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2012 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : AcctOwnershipAllocation.cpp
// ^AUTHOR : 
// ^DATE   : Jul, 2012
//
// ^CLASS    : AcctOwnershipAllocation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "AcctOwnershipAllocation.hpp"

#include <ifastdataimpl\dse_dstc0444_req.hpp>
#include <ifastdataimpl\dse_dstc0444_vw.hpp>
#include <ifastdataimpl\dse_dstc0444_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "AcctOwnershipAllocation" );
}

namespace ifds
{
}

namespace CND
{  // Conditions used
}

namespace IFASTERR
{
}

//******************************************************************************************
AcctOwnershipAllocation::AcctOwnershipAllocation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( 0,
                       NULL,
                       0,
                       NULL );
}

//******************************************************************************************
AcctOwnershipAllocation::~AcctOwnershipAllocation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY AcctOwnershipAllocation::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast< BFData& >( data ), false, true );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctOwnershipAllocation.cpp-arc  $
// 
//    Rev 1.0   Jul 24 2012 18:59:32   dchatcha
// Initial revision.
// 
