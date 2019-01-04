/* 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999, 2000 by DST Systems, Inc.
 */

/**
 *   Class: DString
 *  
 *
 *       Private Member Variables: none allowed by design.
 *
 */

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef INCLUDED_STRINGFUNCTIONS
#define INCLUDED_STRINGFUNCTIONS
#include "stringfunctions.hpp"
#endif

#ifndef INCLUDED_DSTRING
#define INCLUDED_DSTRING
#include "dstring.hpp"
#endif

#ifndef INCLUDED_DSTRINGA
#define INCLUDED_DSTRINGA
#include "dstringa.hpp"
#endif

#ifndef JAVAVM_HPP
   #include "javavm.hpp"
#endif

#ifdef DST_UNICODE

DString::DString( const DStringA &dstringa_in)
: imp( I_("") )
{
   if( !( NULL == &dstringa_in ) )
   {
      DStringAToDString( dstringa_in, *this );
   }
}

DString::DString( const A_STRING &a_string_in )
: imp( I_("") )
{
   if( !( NULL == &a_string_in ) )
   {
      asciistringToUnicodestring( a_string_in, ( I_STRING & )*this );
   }
}

const A_STRING DString::asA() const
{
   A_STRING ascii;
   unicodestringToAsciistring( ( const I_STRING & )*this, ascii );
   return(ascii);
}


#else

DString::DString( const DStringA &dstringa_in )
: I_STRING( dstringa_in.c_str() )
{
}

#endif

DString DString::asString( int nValue )
{
   return(static_cast< DString >( ::asString( nValue ) ));
}


#ifdef DST_UNICODE

void DStringToDStringA( const DString & dstring, DStringA & ascii )
{
   unicodestringToAsciistring( ( const I_STRING & )dstring,
                               ( A_STRING & )ascii );
}

void DStringAToDString( const DStringA & ascii, DString & dstring )
{
   asciistringToUnicodestring( ( const A_STRING & )ascii,
                               ( I_STRING & )dstring );
}

#else

void DStringToDStringA( const DString & dstring, DStringA & ascii )
{
   ascii = dstring;
}

void DStringAToDString( const DStringA & ascii, DString & dstring )
{
   dstring = ascii;
}

#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/dstring.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:41:58   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:06   SMITHDAV
// Initial revision.
// 
//    Rev 1.12   May 04 2000 16:32:00   DT14177
// removed jni.h dependency
// 
//    Rev 1.11   Apr 11 2000 11:00:32   DT14177
// remove jni
// 
//    Rev 1.10   Jan 03 2000 17:08:02   DT14177
// added JavaDoc comments
// 
//    Rev 1.9   Jul 22 1999 11:39:38   DMUM
// Condition re-work
// 
//    Rev 1.8   May 05 1999 12:04:42   DTWK
// Stop includes from breaking scandeps
//
//    Rev 1.7   May 03 1999 12:37:44   DTWK
// Add allocjstring()
//
//    Rev 1.6   Apr 21 1999 09:00:40   DMUM
// asA() now returns A_STRING in place of DStringA
//
//    Rev 1.5   Apr 15 1999 11:46:30   DMUM
// String development/enhancement
//

