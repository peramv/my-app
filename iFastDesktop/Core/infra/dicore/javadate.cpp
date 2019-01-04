// JavaDate Class Implementation
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
// ^FILE   : JavaDate.hpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 01 March 1999
//
// ^CLASS  : JavaDate
// ^PARENT : none
//
// ^CLASS DESCRIPTION :
//
// ^MEMBER VARIABLES :
//    private:
//    jmethodID jMidDateafter;
//    jmethodID jMidDatebefore;
//    jmethodID jMidDateequals;
//    jmethodID jMidDategetTime;
//    jmethodID jMidDatesetTime;
//    jmethodID jMidDatetoString;
//
//************************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef JAVADATE_HPP
   #include "javadate.hpp"
#endif

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif

#ifndef WCHAR_H
   #include <wchar.h>
#endif

#ifndef CALENDAR_H
   #include <calendar.h>
#endif

#ifndef DATEFMT_H
   #include <datefmt.h>
#endif

#ifdef _MSC_VER
   // Disable the following compiler warnings
   // 4800 forcing value to boolean (performance warning)
   #pragma warning( disable : 4800 )

#endif

const DString JAVADATE_NAME = I_("JavaDate");


MsgPair en_usJavaDate[] = 
{

   { 
      JavaDate::JAVADATE_JNI_EXCEPTION_LOCATE,
      I_("Java Exception Occurred in locating %METHOD% method."),
      I_("Check Java Runtime Environment.")   
   },

   { 
      JavaDate::JAVADATE_JNI_EXCEPTION_EXECUTE,
      I_("Java Exception Occurred in %METHOD%."),
      I_("Check Java Runtime Environment.")   
   }
};

Condition::mapCodePagesToLanguages languagesMapForJavaDate[] =
{ 
   {
      I_( "C" ), en_usJavaDate
   },

   // End slot marger
   {
      NULL, NULL

   }
};


JavaDate::JavaDate( DIINT64 ltime )
{
   setTime( ltime );
}


JavaDate::JavaDate( const JavaDate & copy )
{
   cDate = copy.cDate;
}


JavaDate::~JavaDate()
{
}


JavaDate::JavaDate( ) 
{
   setUDate();
}



bool JavaDate::before( JavaDate *jDate )
{
   return (cDate < (jDate->cDate) );
}


bool JavaDate::equals( JavaDate *jDate )
{
   return ( cDate == (jDate->cDate) );
}


DIINT64 JavaDate::getTime()
{
   return (DIINT64)cDate;
}


void JavaDate::setTime( DIINT64 lTime )
{
   cDate = (UDate)lTime;
}


const DString JavaDate::toString( void )
{
   DateFormat * dfmt = DateFormat::createDateTimeInstance( DateFormat::kFull, 
                                                           DateFormat::kFull);
   UnicodeString myString;
   dfmt->format( cDate, myString );

   DString returnValue;
   ICUStringtoIString( myString, returnValue.getImp() );
   return returnValue;
}

   
DIINT64 JavaDate::operator-( JavaDate & subtrahend )
{
   return ( getTime() - subtrahend.getTime() ) / ( 24 * 60 * 60 * 1000 );
}
   

// returns the offset in days
DIINT64 JavaDate::minus( JavaDate & subtrahend )
{
   return ( getTime() - subtrahend.getTime() ) / ( 24 * 60 * 60 * 1000 );
}


   // returns the day
JavaDate & JavaDate::plus( DIINT64 offset, 
                           JavaDate & result )
{
   DIINT64 time = getTime();
   time += offset * 24 * 60 * 60 * 1000;
   result.setTime( time );
   return result;
}


// ***************** protected Methods *********************//

void JavaDate::setUDate( void )
{
   cDate = Calendar::getNow();
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
// $Log:   Y:/VCS/iFastAWD/dicore/javadate.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:10   kovacsro
// Initial revision.
// 
//    Rev 1.20   May 18 2001 14:37:28   dt24433
// Changed setUDate implementation.  (Performance)
// 
//    Rev 1.19   Jun 27 2000 17:02:00   DT14177
// moved some date member variables from JavaDate to DDate
// 
//    Rev 1.18   Jun 13 2000 13:15:34   DT14177
// fixed: addDays(), subtractDays(), getDayOfYearFromDate().
// added conditional operators
// 
//    Rev 1.17   May 23 2000 13:08:42   DT14177
// fixed setTime to update the member variables and the constructor to clear the calendar
// 
//    Rev 1.16   May 11 2000 08:24:58   DT14177
// lots of fixes for DDate
// 
//    Rev 1.15   Apr 11 2000 09:48:18   DT14177
// ICUString macro name change syncup
// 
//    Rev 1.14   11 Apr 2000 07:16:20   dt20842
// Added condition includes
// 
//    Rev 1.13   Apr 10 2000 16:58:20   dtwk
// Change #includes of icu classes to <> instead of ""
// 
//    Rev 1.12   06 Apr 2000 14:16:10   dt20842
// Changed to ICU
// 
//    Rev 1.11   Mar 22 2000 17:33:04   DT14177
// removed compile warnings - 4800
// 
//    Rev 1.10   Sep 16 1999 16:28:08   DT14177
// memory leak cleanup
// 
//    Rev 1.9   Jul 22 1999 11:39:46   DMUM
// Condition re-work
// 
//    Rev 1.7   Jun 27 1999 15:29:58   DT11700
// changed m_pEnv to getEnv() to support
// multi-threaded use of Infrastructure with
// Java.
// 
//    Rev 1.6   Jun 17 1999 09:54:52   DT14177
// Added revision control blocks.
// 

