#include "stdafx.h"
#include "regdocumenttype.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "RegDocumentType" );
}

RegDocumentType::RegDocumentType( BFAbstractCBO &parent ) :
      MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}
//****************************************************************************
RegDocumentType::~RegDocumentType(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//****************************************************************************
SEVERITY RegDocumentType::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}