//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : FundLmtOverride.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : January 09,2003
//
// ^CLASS    : FundLmtOverride
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include "stdafx.h"
#include "FundLmtOverride.hpp"
#include "FundLmtOverrideList.hpp"
#include <ifastdataimpl\dse_dstc0236_req.hpp>
//#include <ifastdataimpl\dse_dstc0236_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0236_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "FundLmtOverride" );
}


//****************************************************************************
FundLmtOverride::FundLmtOverride( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//****************************************************************************
FundLmtOverride::~FundLmtOverride()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY FundLmtOverride::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}


//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundLmtOverride.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:42:40   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Jan 13 2003 09:56:08   WINNIE
// Correct the view number for hpp
// 
//    Rev 1.0   Jan 12 2003 16:04:00   WINNIE
// Initial revision.
// 

*/