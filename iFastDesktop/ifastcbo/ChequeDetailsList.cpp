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
//    Copyright 2009 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : ChequeDetailsList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 01/07/09
//
// ^CLASS    : ChequeDetailsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "chequedetailslist.hpp"
#include "chequedetails.hpp"
#include "currencyclass.hpp"
#include <ifastdataimpl\dse_dstc0021_vw.hpp>
#include <ifastdataimpl\dse_dstc0021_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CHEQUE;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ChequeDetailsList" );
}

//******************************************************************************

ChequeDetailsList::ChequeDetailsList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}


//******************************************************************************

ChequeDetailsList::~ChequeDetailsList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************

SEVERITY ChequeDetailsList::init( const DString& dstrTrack,
                                  const DString& dstrPageName)                             
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ChequeDetailsList::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ChequeDetailsList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   
   assert(0);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ChequeDetailsList::addRecord( ChequeDetails *pDetails )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addRecord" ) );

	if( pDetails )
	{
	   DString strKey; 
	   getStrKey( strKey );
	   setObject( pDetails, strKey );
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ChequeDetailsList.cpp-arc  $
// 
//    Rev 1.1   17 Feb 2009 10:34:18   kovacsro
// IN#1589333 - R91-Missing funds in Cheque Info Screen in Desktop (C22933) - fixed the key for Cheque details list
// 
//    Rev 1.0   08 Jan 2009 14:34:08   kovacsro
// Initial revision.
 * 
// 
*/