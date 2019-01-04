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

#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif

#ifndef DSTRINGA_HPP
   #include "dstringa.hpp"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef JAVAVM_HPP
   #include "javavm.hpp"
#endif

#ifdef DST_UNICODE

DStringA::DStringA( const DString &dstring_in )
: imp( "" )
{
   if( !( NULL == &dstring_in ) )
   {
      ::DStringToDStringA( dstring_in, *this );
   }
}

DStringA::DStringA( const I_CHAR *i_s, const std::allocator< I_CHAR > & al )
: imp( "" )
{
   if( NULL != i_s )
   {
      DString d_s( i_s, al );
      DStringToDStringA( i_s, *this );
   }
}

#else

DStringA::DStringA( const DString &dstring_in )
: A_STRING( dstring_in.c_str() )
{
}

#endif



DStringA DStringA::asString( int nValue )
{
#ifdef DST_UNICODE
   return(static_cast< DStringA >( ::asAsciiString( nValue ) ));
#else
   return(static_cast< DStringA >( ::asString( nValue ) ));
#endif
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/dstringa.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:42:00   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:06   SMITHDAV
// Initial revision.
// 
//    Rev 1.13   May 04 2000 16:32:02   DT14177
// removed jni.h dependency
// 
//    Rev 1.12   Apr 11 2000 11:00:34   DT14177
// remove jni
// 
//    Rev 1.11   Jan 03 2000 17:08:04   DT14177
// added JavaDoc comments
// 
//    Rev 1.10   Jul 22 1999 11:39:42   DMUM
// Condition re-work
// 
//    Rev 1.9   May 05 1999 12:04:44   DTWK
//  
//
//    Rev 1.8   May 03 1999 12:37:46   DTWK
// Add allocjstring()
//
//    Rev 1.7   Apr 15 1999 11:46:30   DMUM
// String development/enhancement
//

