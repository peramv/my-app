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
// Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : ProdPortfolioPlanInfo.cpp
// ^AUTHOR : 
// ^DATE   : Aug, 2011
//
// ^CLASS    : ProdPortfolioPlanInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "ProdPortfolioPlanInfo.hpp"

#include <ifastdataimpl\dse_dstc0419_req.hpp>
#include <ifastdataimpl\dse_dstc0419_vw.hpp>
#include <ifastdataimpl\dse_dstc0419_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "ProdPortfolioPlanInfo" );
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
ProdPortfolioPlanInfo::ProdPortfolioPlanInfo( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( 0,
                       NULL,
                       0,
                       NULL );
}

//******************************************************************************************
ProdPortfolioPlanInfo::~ProdPortfolioPlanInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY ProdPortfolioPlanInfo::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast< BFData& >( data ), false, true );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ProdPortfolioPlanInfo.cpp-arc  $
// 
//    Rev 1.0   Aug 25 2011 17:09:34   dchatcha
// Initial revision.
// 
