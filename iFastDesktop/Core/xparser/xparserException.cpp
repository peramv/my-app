#include "stdafx.h"
#include "xparserexception.hpp"



//CP20030814#include "CData.hpp"
namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "XparserException" );
   const I_CHAR * const FORMATMESSAGE = I_( "formatMessage" );
   const I_CHAR * const CRITICAL = I_( "-3" );
   const I_CHAR * const EWARNING = I_( "-2" );

   const I_CHAR * const S0 = I_( "3;Return_Value=");
   const I_CHAR * const S1 = I_(";ErrorCode=" );
   const I_CHAR * const S2 = I_( ";ErrorMessage=" );
   const I_CHAR * const S3 = I_( ";" );
}

namespace CND
{
   //local conditions
}

namespace TAGS
{
   const I_CHAR * const RESULT = I_( "RESULT" );
   const I_CHAR * const RESULTTYPE = I_( "type" );
   const I_CHAR * const FAILURE = I_( "Failure" );
   const I_CHAR * const ERRORCODE = I_( "code" );
   const I_CHAR * const ERRORDESCRIPTION = I_( "description" );
}

XparserException::XparserException() :
_errorCode( -1 ), _errorMessage( NULL_STRING ), _locale(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING )
}

XparserException::XparserException( I_CHAR* format, ... ) :
_errorCode( -1 ), _errorMessage( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING )
   va_list arguments;

   va_start( arguments, format );

   I_CHAR buffer[ BUFSIZ ];

   *buffer = 0;
   i_vsprintf( buffer, format, arguments );
   _errorMessage = buffer;
   va_end( arguments );
}


void XparserException::getOutMessage( DString &strOut )
{
   strOut = S0+_errortype+S1;
   strOut += DString::asString(_errorCode).c_str();
   strOut += S2;
   strOut += _errorMessage;
   strOut += S3;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/xparserException.cpp-arc  $
//
//   Rev 1.3   Aug 14 2003 14:15:44   PURDYECH
//References to XData and CData were removed
// 
//    Rev 1.2   Oct 09 2002 17:43:28   PURDYECH
// New PVCS Database
// 
//    Rev 1.1   Jul 05 2002 11:32:00   PURDYECH
// Include file fixups
// 
//    Rev 1.0   Aug 28 2001 10:36:52   FENGYONG
// Initial revision.
 */
