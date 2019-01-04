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
//    Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : FamilyCode.cpp
// ^AUTHOR : 
// ^DATE   : Oct, 2011
//
// ^CLASS    : FamilyCode
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0235_vw.hpp>
#include <ifastdataimpl\dse_dstc0235_req.hpp>
#include <ifastdataimpl\dse_dstc0235_vwrepeat_record.hpp>

#include "FamilyCode.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "FamilyCode" );
}

namespace ifds
{
}

namespace CND
{
}

//******************************************************************************
FamilyCode::FamilyCode( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( 0,
                       NULL,
                       0,
                       NULL );

}

//******************************************************************************
FamilyCode::~FamilyCode(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//********************************************************************************
SEVERITY FamilyCode::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast< BFData& >( data ), false, true );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FamilyCode.cpp-arc  $
// 
//    Rev 1.1   Nov 17 2011 19:10:24   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.0   Nov 08 2011 11:45:48   dchatcha
// Initial revision.
// 