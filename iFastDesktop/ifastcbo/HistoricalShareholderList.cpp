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
//    Copyright 1999 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : HistoricalShareholderList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : HistoricalShareholderList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "HistoricalShareholderList.hpp"
#include <dataimpl\dse_dstc0110_vw.hpp>
#include <dataimpl\dse_dstc0288_req.hpp>

// We'll use the 288 Request and the 110 Response.

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest HISTORICAL_SHAREHOLDER;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "HistoricalShareholderList" );
   const I_CHAR * const INIT = I_( "init" );
   const I_CHAR * const SEARCH = I_( "search" );
   const I_CHAR * const MORERECORDSEXIST = I_( "moreRecordsExist" );
}

HistoricalShareholderList::HistoricalShareholderList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
m_queryData(ifds::DSTC0288_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

HistoricalShareholderList::~HistoricalShareholderList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*******************************************************************************************

SEVERITY HistoricalShareholderList::init( const DString& dstrShareholderNumber, const DString& dstrTrack, const DString& dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, INIT );   

   DString dstrMgmtCoId;
   m_queryData.setElementValue( ifds::CompanyId, getMgmtCoId( dstrMgmtCoId ) );
   m_queryData.setElementValue( ifds::ShareholderNum, dstrShareholderNumber ); 
   m_queryData.setElementValue( ifds::Track, dstrTrack );
   m_queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::HISTORICAL_SHAREHOLDER, m_queryData, ifds::DSTC0110_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY HistoricalShareholderList::search( bool bClearPreviousSearch )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, SEARCH );

   if( bClearPreviousSearch )
   {
      eraseDataObjectContainers();
      eraseObjectContainer();
      m_queryData.setElementValue( ifds::NextKey, NULL_STRING );
   }
   return( ReceiveData( DSTC_REQUEST::HISTORICAL_SHAREHOLDER, m_queryData, ifds::DSTC0110_VW, DSTCRequestor( getSecurity(), false ) ) );
}

//******************************************************************************

bool HistoricalShareholderList::moreRecordsExist()
{
   MAKEFRAMEAUTOPROMOTE( CLASSNAME, MORERECORDSEXIST );
   return( doMoreRecordsExist() );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HistoricalShareholderList.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:44:14   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Feb 06 2004 14:03:36   HERNANDO
// Initial revision.
*/