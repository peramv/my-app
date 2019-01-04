//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : GuaranteeSummary.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : August 2005
//
// ^CLASS    : GuaranteeSummary
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "GuaranteeSummary.hpp"
#include "GuaranteeInfoList.hpp"

#include <ifastdataimpl\dse_dstc0170_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "GuaranteeSummary" );
}

//****************************************************************************
GuaranteeSummary::GuaranteeSummary( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//****************************************************************************
GuaranteeSummary::~GuaranteeSummary()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY GuaranteeSummary::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY GuaranteeSummary::init( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );  

   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GuaranteeSummary.cpp-arc  $
// 
//    Rev 1.1   Jun 05 2006 16:53:02   porteanm
// Incident 635750 - Crash when no record available.
// 
//    Rev 1.0   Aug 17 2005 16:23:14   porteanm
// Initial revision.
 * 
 */
