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
//    Copyright 2001 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCViewTimeTxnStatElement.cpp
// ^AUTHOR : Chris Purdye
// ^DATE   : 2001
//
//******************************************************************************
#include "stdafx.h"

#include "DSTCViewTimeTxnStatElement.hpp"
#include <iomanip>

using std::setw;
using std::setfill;

DSTCViewTimeTxnStatElement::DSTCViewTimeTxnStatElement( const BFRequest &request,
                                                        const BFRequestor &requestor )
: _name( request.getId() )
, _elapsed( requestor.getRequestTime() )
, _assignTime( requestor.getAssignTime() )
, _timeStamp( timeStamp() )
{
//CP   // dump to monitor
//CP   i_cout << I_("View ") << _name.c_str() << I_(" took " ) << _elapsed << I_(" milliseconds.") << std::endl;
}

DSTCViewTimeTxnStatElement::DSTCViewTimeTxnStatElement( const DString& viewName )
: _name( viewName )
, _elapsed( 0 )
, _assignTime( 0 )
, _timeStamp( timeStamp() )
{
}

const DString& DSTCViewTimeTxnStatElement::getName() const
{
   return( _name );
}

DString DSTCViewTimeTxnStatElement::getAsIDIString() const
{
   DString dstrIDI;
   dstrIDI =  I_( ";ViewTimeStamp=" );
   dstrIDI += _timeStamp;
   dstrIDI += I_( ";ViewName=" );
   dstrIDI += getName();
   dstrIDI += I_( ";ViewTime=" );
   dstrIDI += DString::asString( _elapsed );
   dstrIDI += I_( ";ViewAssignTime=" );
   dstrIDI += DString::asString( _assignTime );
   return( dstrIDI );
}

void DSTCViewTimeTxnStatElement::writeXML( BFDocument& out )
{
   ElementWriter ew( out, I_( "View" ) );
   ElementWriter::write( out, I_( "Name" ),        getName() );
   ElementWriter::write( out, I_( "ElapsedTime" ), DString::asString( _elapsed ) );
   ElementWriter::write( out, I_( "AssignTime" ),  DString::asString( _assignTime ) );
   ElementWriter::write( out, I_( "Timestamp" ),   _timeStamp );
}



DString DSTCViewTimeTxnStatElement::timeStamp()
{
   DString dstrDate;

   SYSTEMTIME st;
   GetSystemTime( &st );
   I_CHAR szTimeStamp[ 64 ];
   i_sprintf( szTimeStamp, I_( "%04d/%02d/%02d-%02d:%02d:%02d" ),
              st.wYear,
              st.wMonth,
              st.wDay,
              st.wHour,
              st.wMinute,
              st.wDay );
   return( DString( szTimeStamp ) );


}




