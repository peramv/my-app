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
// ^FILE   : CommitmentProduct.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : CommitmentProduct
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "commitmentproduct.hpp"

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "CommitmentProduct" );
}

//******************************************************************************
CommitmentProduct::CommitmentProduct( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //setVersionable( false );

}


//******************************************************************************
CommitmentProduct::~CommitmentProduct()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY CommitmentProduct::init( const BFData &data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   attachDataObject( const_cast<BFData&>( data ), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CommitmentProduct.cpp-arc  $
// 
//    Rev 1.0   Feb 24 2012 18:10:04   if991250
// Initial revision.
// 
*/