//************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//************************************************************************
//
// ^FILE   : ConditionException.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 5/23/97
//
// ----------------------------------------------------------
//
// ^CLASS    : ConditionException
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//************************************************************************
#define DICORE_DLL

#define CM_LOCAL           // Condition Manager is local

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef CONDITIONEXCEPTION_HPP
   #include "conditionexception.hpp"
#endif

#ifndef INCLUDED_IOSTREAM
#define INCLUDED_IOSTREAM
#include <iostream>
#endif

#ifdef _WIN32

   #include <strstream>
   #include <tchar.h>
   #include <winuser.h>
   #include "registrykey.hpp"
   #include "registryvalue.hpp"

   #undef MessageBox
   #ifdef DST_UNICODE
      #define MessageBox  MessageBoxW
   #else
      #define MessageBox  MessageBoxA
   #endif

#endif

void fnDebugOptions( const ConditionException &ce )
{

#ifdef _WIN32
   RegistryKey rkOption( "SOFTWARE\\DST\\Debug" );
   RegistryValue rvAssert = rkOption.getValue( "AssertLevel" );
   RegistryValue rvDisplay = rkOption.getValue( "DisplayBeforeThrowLevel" );

   bool bAssert = false;
   unsigned long level = 99;

   if( RegistryValue::DWORD == rvDisplay.getType() )
   {
      level = rvDisplay.getAsDWORD();
#pragma warning( push )
#pragma warning( disable: 4018 )
      if( ce.getSeverity() >= level )
#pragma warning( pop )
      {
         DString strMsg;

         strMsg = I_("ConditionException!\n");
         strMsg += asString( ce.getCode() );
         strMsg += I_("(");
         strMsg += asString( (int)ce.getSeverity() );
         strMsg += I_( ")\n" );
         strMsg += ce.getComponentName();
         strMsg += I_( ": " );
         strMsg += ce.getMethodName();
         strMsg += I_( ")\n" );
         strMsg += DString( DStringA( ce.getFileName() ) );
         strMsg += I_( " at " );
         strMsg += asString( ce.getLineNumber() );
         strMsg += I_( "\nMessage: " );
         strMsg += ce.getMessage();
         strMsg += I_( "\nCorrection: " );
         strMsg += ce.getCorrection();

         int ret = MessageBox( NULL,
                               strMsg.c_str(),
                               I_("Display Before Throw"),
                               MB_OKCANCEL |
                               MB_ICONEXCLAMATION |
                               MB_SETFOREGROUND );

         if( IDCANCEL == ret )
         {
            exit(1);
         }
      }
   }

   if( RegistryValue::DWORD == rvAssert.getType() )
   {
      level = rvAssert.getAsDWORD();
#pragma warning( push )
#pragma warning( disable: 4018 )
      bAssert = ce.getSeverity() >= level;
#pragma warning( pop )
   }

   bool ConditionExceptionAssertion = !bAssert;
   _ASSERTE( ConditionExceptionAssertion );

#else

   I_CHAR *pDisplay = NULL;

   try
   {
      pDisplay = i_getenv( I_("ENABLE_DISPLAY") );
   }
   catch( ... )
   {
      pDisplay = NULL;
   }

   if( pDisplay )
   {
      ce.what();
   }

   I_CHAR *pEnable = NULL;

   try
   {
      pEnable = i_getenv( I_("ENABLE_ASSERT") );
   }
   catch( ... )
   {
      pEnable = NULL;
   }

   _ASSERT( pEnable );

#endif

}

//************************************************************************
//              Public Methods
//************************************************************************

ConditionException::ConditionException(const DString & componentName,
                                       const DString & methodName,
                                       long code,
                                       const I_CHAR* codeStr,
                                       const char * fileName,
                                       unsigned lineNumber,
                                       Condition::mapCodePagesToLanguages elementalTable[],
                                       const DString & str ) :
_cnd(componentName, methodName, code, codeStr, fileName, lineNumber,
     elementalTable, str)
{
   fnDebugOptions( *this );
}



ConditionException::ConditionException( const DString &componentName,
                                        const DString &methodName,
                                        long code,
                                        const I_CHAR* codeStr,
                                        const char * fileName,
                                        unsigned lineNumber,
                                        int level,
                                        BOOL baseCondition,
                                        const I_CHAR *cndPath,
                                        SEVERITY severity,
                                        const DString & str1,
                                        const ClientLocale *clientLocale ) :
_cnd( componentName, methodName, code, codeStr, fileName, lineNumber,
      baseCondition, cndPath, severity, str1, clientLocale )
{
   fnDebugOptions( *this );
}

ConditionException::ConditionException( const Condition& condition ) :
_cnd( condition )
{
   fnDebugOptions( *this );
}

void ConditionException::what()
{
   i_cout << ( int ) getSeverity();

   //
   DString str( I_( " " ) );
   str += getComponentName();
   str += I_( "/" );
   str += getMethodName();
   str += I_( " at " );
   str += DString( DStringA( getFileName() ) );
   str += I_( ":" );
   i_cout << str << getLineNumber() << std::endl;
   i_cout << I_( "Code = " );
   i_cout << getCode() << I_(" (") << getCodeString() << I_(")") << std::endl;
   i_cout << I_( " msg = " );
   i_cout << getMessage() << std::endl;
   i_cout << I_( " correction = " );
   i_cout << getCorrection() << std::endl;
}

ConditionException::ConditionException( const ConditionException &copy )
: _cnd(copy._cnd)
{
   // This copy constructor is not meant to be used.  By not implementing it
   // linker errors will result when someone attempts to use this operator.

   //*this = copy;
}

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// $Log:   Y:/VCS/iFastAWD/dicore/conditionexception.cpp-arc  $
// 
//    Rev 1.1   Nov 02 2011 04:42:54   purdyech
// Registry Cleanup
//
//   Rev 1.3   Sep 23 2009 01:29:10   purdyech
//Track Condition Name as well as Code.
//Add "Display Details" option to system menu on Error Popup.
//
//   Rev 1.2   Oct 22 2004 09:02:08   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.1   Oct 09 2002 17:41:46   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:12:44   SMITHDAV
// Initial revision.
// 
//    Rev 1.18   28 Aug 2000 17:35:14   dt20842
// Condition getters const again
// 
//    Rev 1.17   23 Aug 2000 21:18:10   dt20842
// Added ability to pass clientLocale through macros.
// Added lazy initialization.
// 
//    Rev 1.16   Dec 06 1999 10:58:16   DT20842
// Added constructror with Condition parameter
// 
//    Rev 1.15   Aug 27 1999 08:27:48   DMUM
// Added filename to messagebox
//
//    Rev 1.14   Aug 26 1999 14:32:36   DMUM
// Now has been unicode tested
//
//    Rev 1.13   Aug 26 1999 12:52:06   DMUM
// The assert now checks the registry and will only assert
// if the severity is greater or equal to the level indicated in
// the registry.  In addition, will now display a condition in a
// messagebox before throwing.
//
//    Rev 1.12   Aug 25 1999 13:58:18   DMUM
// Now added the I_() which was forgotten earlier.
//
//    Rev 1.11   Aug 24 1999 08:37:10   DMUM
// Changed char * to I_CHAR * for unicode.
//
//    Rev 1.10   Aug 24 1999 08:04:10   DMUM
// Removed ASSERTE macros from throw macros.
// The ASSERTE macro was moved to the constructor for ConditionException
// so that logic could be put in to determine at *RUNTIME* whether or not to
// assert.
//
//    Rev 1.9   Jun 22 1999 11:10:02   DT14177
// Changed type for condition code from int to long.
//
//    Rev 1.8   May 12 1999 09:20:10   DT20842
// Added elemental conditions
//
//    Rev 1.7   Apr 15 1999 14:32:16   DT14177
// sync up with DString and DStringA changes
//
//    Rev 1.6   29 Mar 1999 11:50:52   DT14177
// ConditionException Constructor now takes a DString reference as a parameter instead of I_CHAR *
//
//    Rev 1.5   04 Mar 1999 09:28:50   DT14177
// Fixed conditionException NULL pointer bug, duplicate SEVERE_ERROR definition bug, and the ASCII Condition file read bug.
//
//    Rev 1.4   24 Feb 1999 10:43:56   DT14177
// sync up with tracer
//
//    Rev 1.3   22 Feb 1999 13:57:12   DT14177
// more UNICODE stuff
//
//    Rev 1.2   18 Feb 1999 10:31:30   DT14177
// UNICODE
//
//    Rev 1.1   Jan 28 1999 14:02:26   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:50:52   DMUM
//
//
//    Rev 1.4   Jun 16 1998 16:10:56   dt27994
// Removed old tracing code.
//
//    Rev 1.3   Nov 09 1997 15:35:36   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.2   Sep 26 1997 12:31:06   dkaw
// pass condition path to constructor
//
//    Rev 1.1   Jul 22 1997 16:18:22   dkaw
// add trace filtering, use ditrace
//
//    Rev 1.0   Jun 13 1997 12:54:52   DTWK
//

