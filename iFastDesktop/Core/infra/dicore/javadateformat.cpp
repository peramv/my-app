// JavaDateFormat Class Implementation
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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : JavaDateFormat.hpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 01 March 1999
//
// ^CLASS  : JavaDateFormat
// ^PARENT : none
//
// ^CLASS DESCRIPTION :
//
// ^MEMBER VARIABLES :
//    private:
//
//******************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef JAVADATEFORMAT_HPP
   #include "javadateformat.hpp"
#endif

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

#ifndef JAVALOCALE_HPP
   #include "javalocale.hpp"
#endif

#ifdef _MSC_VER
   // Disable the following compiler warnings
   // 4800 forcing value to boolean (performance warning)
   #pragma warning( disable : 4800 )

#endif

namespace
{
   const I_CHAR * const JAVADATEFORMAT_NAME = I_("JavaDateFormat");
}

int JavaDateFormat::defaultStyle = 0;

MsgPair en_usJavaDateFormat[] =
{

   {
      JavaDateFormat::JAVADATEFORMAT_JNI_EXCEPTION_LOCATE,
      I_("Java Exception Occurred in locating %METHOD% method."),
      I_("Check Java Runtime Environment.")
   },

   {
      JavaDateFormat::JAVADATEFORMAT_JNI_EXCEPTION_EXECUTE,
      I_("Java Exception Occurred in %METHOD%."),
      I_("Check Java Runtime Environment.")
   }

};

Condition::mapCodePagesToLanguages languagesMapForJavaDateFormat[] =
{
   {
      I_( "C" ), en_usJavaDateFormat
   },

   // End slot marger
   {
      NULL, NULL

   }
};



JavaDateFormat::JavaDateFormat( DateFormat *dateFormatIn )
{

   dateFormat = dateFormatIn;

}


JavaDateFormat::~JavaDateFormat()
{

   delete dateFormat;
}

JavaDateFormat JavaDateFormat::getInstance()
{


   return JavaDateFormat( DateFormat::createInstance() );

}


JavaDateFormat JavaDateFormat::getDateInstance( JavaLocale * loc )
{
   return JavaDateFormat( DateFormat::createDateInstance(
                             DateFormat::kShort,
                             *(loc->getLocale() ) ) );
}


JavaDateFormat JavaDateFormat::getDateInstance( ClientLocale * loc )
{
   const JavaLocale * javaLocale = loc->getJavaLocale();

   Locale * locale = const_cast< JavaLocale * >( javaLocale )->getLocale();
   return JavaDateFormat( DateFormat::createDateInstance(
                             DateFormat::kShort,
                             *locale ) );
}


JavaDateFormat JavaDateFormat::getDateInstance()
{

   return JavaDateFormat( DateFormat::createDateInstance() );

}

JavaDateFormat JavaDateFormat::getDateTimeInstance()
{

   return JavaDateFormat( DateFormat::createDateTimeInstance() );

}

const DString JavaDateFormat::format( JavaDate *pJavaDate )
{

   UnicodeString uStr;
   dateFormat->format( pJavaDate->getUDate(), uStr);

   DString returnValue;
   ICUStringtoIString( uStr, returnValue.getImp() );
   return returnValue;


}


bool JavaDateFormat::equals( JavaDateFormat & pJavaDateFormat)
{

   return ( *dateFormat == *( pJavaDateFormat.dateFormat) );

}


void JavaDateFormat::setLenient( bool bIsLenient)
{

   dateFormat->setLenient( bIsLenient );

}


bool JavaDateFormat::isLenient( void)
{

   return ( dateFormat->isLenient() );

}

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/dicore/javadateformat.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:10   kovacsro
// Initial revision.
// 
//    Rev 1.17   Aug 09 2001 10:07:04   DT11159
// Removed spaces inside preprocessor directives.
//
//    Rev 1.16   Apr 26 2001 14:45:30   dt24433
// Removed unused variables and changed static string to I_CHAR.
//
//    Rev 1.15   Apr 26 2001 14:05:50   dt24433
// Remove unused header.
//
//    Rev 1.14   May 26 2000 20:26:18   DT14177
// Added ClientLocale support
//
//    Rev 1.13   May 11 2000 08:53:26   DT14177
// changed kdefault to kshort in getDateInstance( locale )
//
//    Rev 1.12   Apr 11 2000 09:46:50   DT14177
// ICUString macro name change syncup
//
//    Rev 1.11   10 Apr 2000 10:30:20   dt20842
// Switch to ICU and clean up error handling
//
//    Rev 1.10   Mar 22 2000 17:33:06   DT14177
// removed compile warnings - 4800
//
//    Rev 1.9   Oct 05 1999 16:54:12   DT14177
// Added suppression and language severity enhancements; fixed multi-threading issues
//
//    Rev 1.8   Jul 22 1999 11:39:50   DMUM
// Condition re-work
//
//    Rev 1.7   Jun 27 1999 15:30:00   DT11700
//
//
//    Rev 1.6   Jun 17 1999 09:37:42   DT14177
// Added a revision control block
//

