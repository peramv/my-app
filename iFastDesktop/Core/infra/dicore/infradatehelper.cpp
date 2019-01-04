/* 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

// Make sure the linkage is right!

#define DICORE_DLL

#define INFRADATEHELPER_CPP

#define COMPONENT_NAME I_( "DICORE" )

// this file should only be included in the .CPP file

#ifndef SRCPRAG_H
   #include <srcprag.h>
#endif

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif


#ifndef XUTILITY
   #define XUTILITY
   #pragma message( "including xutility" )
   #include <xutility>
#endif


#include <map>

#ifndef DATEFMT_H
   #include <datefmt.h>
#endif



#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef BASE_H
   #include "base.h"
#endif

#ifndef DICORE_H
   #include "dicore.h"
#endif

#ifndef DSTRING_HPP
#include "dstring.hpp"
#endif


#ifndef DICORE_CONDITIONS_HPP
#include "dicore_conditions.hpp"
#endif


#ifndef STRINGFUNCTIONS_HPP
#include "stringfunctions.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
#include "conditionmanager.hpp"
#endif

#ifndef CONFIGMANAGER_HPP
#include "configmanager.hpp"
#endif

#ifndef CRITICALSECTION_HPP
#include "criticalsection.hpp"
#endif

#ifndef RESOURCELOCK_HPP
#include "swmrresourcelock.hpp"
#endif

#include "infradatehelper.hpp"

#ifndef INFRAGREGORIANCALENDAR_HPP
   #include "infragregoriancalendar.hpp"
#endif

#ifndef INFRADATE_HPP
#include "infradate.hpp"
#endif

#ifndef INFRASIMPLEDATEFORMAT_HPP
   #include "infrasimpledateformat.hpp"
#endif


#ifndef INFRADATEFORMAT_HPP
   #include "infradateformat.hpp"
#endif



#include <assert.h>

Infra::DateHelper::gregorianFormatMap 
                   Infra::DateHelper::gregorianFormatMapInstance;

const int NUMBER_OF_MILLISECONDS_PER_DAY = 24 * 60 * 60 * 1000;

const long Infra::DateHelper::_lStartOfMonthOffsets[ 12 ] =
{  // Days until start of month
     0L,  31L,  59L,  90L, 120L, 151L,
   181L, 212L, 243L, 273L, 304L, 334L 
};

const int Infra::DateHelper::_nDaysInMonth[ 13 ]  = {
   31, 28, 31, 30, 31, 30, 31,
   31, 30, 31, 30, 31
   };


#ifdef ENABLE_TRACING
TracerClient Infra::DateHelper::tracerClient;
#endif

static MutexSemaphore tracerLock;

const DString Infra::DateHelper::DF_MMDDCCYY( I_( "MMddyyyy" ) );
const DString Infra::DateHelper::DF_FSMMDDCCYY( 
                                            I_( "MM/dd/yyyy" ) );
const DString Infra::DateHelper::DF_FDMMDDCCYY(
                                            I_( "MM-dd-yyyy" ) );
const DString Infra::DateHelper::DF_CCYYMMDD( I_( "yyyyMMdd" ) );
const DString Infra::DateHelper::DF_FSCCYYMMDD(
                                            I_( "yyyy/MM/dd" ) );
const DString Infra::DateHelper::DF_FDCCYYMMDD(
                                            I_( "yyyy-MM-dd" ) );
const DString Infra::DateHelper::DF_DDMMCCYY( I_( "ddMMyyyy" ) );
const DString Infra::DateHelper::DF_FPDDMMCCYY( I_(
                                                "dd.MM.yyyy" ) );

Infra::SimpleDateFormat * DF_MMDDCCYY_format;
Infra::SimpleDateFormat * DF_FSMMDDCCYY_format;
Infra::SimpleDateFormat * DF_FDMMDDCCYY_format;
Infra::SimpleDateFormat * DF_CCYYMMDD_format;
Infra::SimpleDateFormat * DF_FSCCYYMMDD_format;
Infra::SimpleDateFormat * DF_FDCCYYMMDD_format;
Infra::SimpleDateFormat * DF_DDMMCCYY_format;
Infra::SimpleDateFormat * DF_FPDDMMCCYY_format;

extern DString formatDateToStandard( DString & tmp );

static int daysInGregorianMonth( 
                             Infra::GregorianCalendar & calendar,
                             int currMonth,
                             int currYear );

const DString DATEHELPER_NAME = I_( "Infra::DateHelper" );

MsgPair en_usDateHelper[] = 
{

   { 
      Infra::DateHelper::ICU_ERROR,
      I_("ICU error has occurred with value %VALUE%."),
      I_("Check ICU Runtime Environment.")   
   }

};

Condition::mapCodePagesToLanguages languagesMapForDateHelper[] =
{ 
   {
      I_( "C" ), en_usDateHelper
   },
};


#ifndef IOSTREAM_INCLUDED
#define IOSTREAM_INCLUDED
#include <iostream>
#endif

static MutexSemaphore msgSema4;

/*void DICORE_LINKAGE logStdOut( const I_CHAR * message )
{
   CriticalSection cs( msgSema4 );
   i_cout << message << std::endl;
}*/


static void throwIfNeeded( UErrorCode code,
				               I_CHAR * methodName )
{
   logStdOut( I_( "DateHelper::" )
              I_( "throwIfNeeded()" ) );
   if ( U_FAILURE( code ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( code ) );
      idiStr += DString( tmp );
      DString logStr = I_( "throwIfNeeded: " );
      logStr += methodName;
      logStr += I_( "()  " );
      logStr += idiStr;
      logStdOut( logStr.c_str() );

#ifdef ENABLE_TRACING
      {
         CriticalSection cs( tracerLock );

         if ( Infra::DateHelper::getTracerClient().isTracing() )
            Infra::DateHelper::getTracerClient().logMessage( logStr );
      }
#endif

      THROWELEMENTALIDI( DATEHELPER_NAME,
		                   methodName,
                         Infra::DateHelper::ICU_ERROR,
                         languagesMapForDateHelper,
                         idiStr );
   }
}


/* ########################################################### *
 *                                                             *
 *                       public methods                        *
 *                                                             *
 * ########################################################### */


bool Infra::DateHelper::addDays( DString & date, int nDays )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(DString &,int)" ) );
   addGregorian( date, 
                 0,
                 0,
                 nDays ); 
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(DString &,int) exit" ) );
   return true;
}


bool Infra::DateHelper::addDays( DString & date, 
                                 const DString & nDays )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(DString &,DString &)" ) );
   addGregorian( date, 
                 DString( I_( "" ) ), 
                 DString( I_( "" ) ), 
                 nDays ); 
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(DString &,DString &) exit" ) );
   return true;
}


bool Infra::DateHelper::addDays( Infra::Date & date, 
                                 const DString & nDays )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(Date &,DString &)" ) );
   addGregorian( date.getDate(),
                 DString( I_( "" ) ), 
                 DString( I_( "" ) ), 
                 nDays ); 
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(Date &,DString &) exit" ) );
   return true;
}


bool Infra::DateHelper::addDays( Infra::Date & date, int nDays )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(Date &,int)" ) );
   double newDate = addGregorian( date.getDateAsDouble(),
                                  0,
                                  0,
                                  nDays );
   date.set( newDate );
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(Date &,int) exit" ) );
   return true;
}


DString & Infra::DateHelper::addGregorian( DString & date, 
                                        const DString & yearDiff,
                                        const DString & monthDiff,
                                        const DString & dayDiff )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addGregorian(DString &,DString &)" )
              I_( "DString &,DString &)" ) );
   double addDate;

   if ( getStringDateAsDouble( date, addDate ) )
       date = asString( (long long)addGregorian( asInteger( date ),
                                      asInteger( yearDiff ),
                                      asInteger( monthDiff ),
                                      asInteger( dayDiff ) ) );
   logStdOut( I_( "DateHelper::" )
              I_( "addGregorian(DString &,DString &)" )
              I_( "DString &,DString &) exit" ) );
   return date;
}


DString & Infra::DateHelper::addGregorian( DString & date, 
                                           int yearDiff,
                                           int monthDiff,
                                           int dayDiff )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addGregorian(DString &,int)" )
              I_( "int,int)" ) );
   double addDate;

   if ( getStringDateAsDouble( date, addDate ) )
   {
      Infra::Date tmpDate;
      tmpDate.set( addGregorian( addDate,
                                 yearDiff,
                                 monthDiff,
                                 dayDiff ) );
      date = tmpDate.getDate();
   }
   logStdOut( I_( "DateHelper::" )
              I_( "addGregorian(DString &,int)" )
              I_( "int,int) exit" ) );
   return date;
}


bool Infra::DateHelper::addYears( DString & date, 
                                  const DString & nYears )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addYears(DString &, DString &)" ) );
   addGregorian( date, 
                 nYears, 
                 DString( I_( "" ) ), 
                 DString( I_( "" ) ) ) ;
   logStdOut( I_( "DateHelper::" )
              I_( "addYears(DString &, DString &) exit" ) );
   return true;
}


bool Infra::DateHelper::addYears( DString & date, 
                                  const int nYears )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addYears(DString &, int)" ) );
   date = addGregorian( date, nYears, 0, 0 );
   logStdOut( I_( "DateHelper::" )
              I_( "addYears(DString &, int) exit" ) );
   return true;
}


bool Infra::DateHelper::addYears( Infra::Date & date, 
                                  const int nYears )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addYears(Date &, int)" ) );
   date = addGregorian( date.getDate(),
                        nYears,
                        0,
                        0 );
   logStdOut( I_( "DateHelper::" )
              I_( "addYears(Date &, int) exit" ) );
   return true;
}


bool Infra::DateHelper::formatGregorianDate( const DString & 
                                                       strDateIn, 
                                       DString & strDateOut, 
                                       const DString & dfFormat )
{
   logStdOut( I_( "DateHelper::" )
              I_( "formatGregorianDate()" ) );
   {
      CriticalSection cs( tracerLock );
      TRACER_METHOD( I_( "DateHelper::formatGregorianDate( " )
                     I_( "const DString & strDateIn, " )
                     I_( "DString & strDateOut, " )
                     I_( "const DString & dfFormat )" ) );

   }
   /*MAKEFRAMENOTRACE( COMPONENT_NAME, 
              I_( "DateHelper::formatGregorianDate( " )
              I_( "const DString & dateIn, " )
              I_( "DString & dateOut, " )
              I_( "const DString & dfFormat )") );*/

   DString inputFormat;

   if ( false == getGregorianDateFormat( strDateIn,
                                         inputFormat ) )
   {
      logStdOut( I_( "DateHelper::" )
                 I_( "formatGregorianDate() exit 1" ) );
      return false;
   }
   try
   {
      bool isError;
      double date = gregorianFormatMapInstance[ inputFormat ]->
                                                parse( strDateIn,
                                                       isError );
      if ( false == isError )
      {
         gregorianFormatMapInstance[ dfFormat ]->format( date,
                                                    strDateOut );
      }
   }
   catch ( ConditionException & ce )
   {
      /*TRACER_ERROR( ce.getMessage() );*/
      
      ce.getCode();
      logStdOut( I_( "DateHelper::" )
                 I_( "formatGregorianDate() exit 2" ) );
      return false;
   }
   logStdOut( I_( "DateHelper::" )
              I_( "formatGregorianDate() exit 3" ) );
   return true;
}


DString Infra::DateHelper::getCurrentDateAsString( 
                                        Infra::DateFormat & arg )
{
   logStdOut( I_( "DateHelper::" )
              I_( "getCurrentDateAsString(DateFormat &)" ) );
   UErrorCode code = U_ZERO_ERROR;
   ::Calendar * calendar = ::Calendar::createInstance( code );
   
   if ( U_FAILURE( code ) )
      delete calendar;
   
   throwIfNeeded( code,
				  I_( "DateHelper::getCurrentDateAsString" )
				  I_( "( Infra::DateFormat & )") );
   
   calendar->clear();
   double currDate = calendar->getNow();
   
   DString tmp = arg.format( currDate );
   delete calendar;
   DString retVal = formatDateToStandard( tmp );
   logStdOut( I_( "DateHelper::" )
              I_( "getCurrentDateAsString(DateFormat & )" ) );
   return retVal;
}


DString Infra::DateHelper::getCurrentDateAsString( Infra::Locale 
                                                          * loc )
{
   logStdOut( I_( "DateHelper::" )
              I_( "getCurrentDateAsString(Locale *)" ) );
   UErrorCode code = U_ZERO_ERROR;
   ::Calendar * calendar = ::Calendar::createInstance( code );
   if ( U_FAILURE( code ) )
	  delete calendar;
   throwIfNeeded( code,
				  I_( "DateHelper::getCurrentDateAsString" )
				  I_( "( Infra::Locale * )") );
   
   calendar->clear();
   double currDate = calendar->getNow();
   DString tmp = Infra::DateFormat::getDateInstance( loc ).
      format( currDate );
   delete calendar;
   DString retVal = formatDateToStandard( tmp );
   logStdOut( I_( "DateHelper::" )
              I_( "getCurrentDateAsString(Locale *) exit" ) );
   return retVal;
}


extern bool getCfgDisplayMask( const DString & lcv, 
                               DString & mask );

DString Infra::DateHelper::getCurrentDateAsString()
{
   logStdOut( I_( "DateHelper::" )
              I_( "getCurrentDateAsString()" ) );
   UErrorCode code = U_ZERO_ERROR;
   ::Calendar * calendar = ::Calendar::createInstance( code );
   if ( U_FAILURE( code ) )
	  delete calendar;
   throwIfNeeded( code,
				     I_( "DateHelper::getCurrentDateAsString" ) );
   
   calendar->clear();
   double currDate = calendar->getNow();
   DString lcv;
   DString mask;
   DString retVal;

   // get the language, country, variant DString from the current
   // locale
   Infra::Locale * locale = Infra::Locale::getCurrentInstance();
   locale->getLCV( lcv );

   //  look in the registry for the date format mask
   if ( true == getCfgDisplayMask( lcv, mask ) )
   {
      Infra::SimpleDateFormat simple( mask, *locale );
      simple.format( currDate, retVal );
   }
   else  // use the default date format mask
   {
      mask = Infra::DateHelper::DF_FSMMDDCCYY;
      Infra::SimpleDateFormat * simple = 
         Infra::SimpleDateFormat::US( mask );
      simple->format( currDate, retVal );
      delete simple;
   }
   delete calendar;
   logStdOut( I_( "DateHelper::" )
              I_( "getCurrentDateAsString() exit" ) );
   return retVal;
}


bool Infra::DateHelper::getGregorianDateFormat( const DString & 
                                                            date,
                                               DString & format )
{
   logStdOut( I_( "DateHelper::" )
              I_( "getGregorianDateFormat(DString &," )
              I_( "DString &)" ) );
   {
      CriticalSection cs( tracerLock );
      TRACER_METHOD( I_( "DateHelper::getGregorianDateFormat( " )
                     I_( "const DString& )" ) );
   }

   bool fParsed = false;
   
   // loop thru the formats until one parses Ok
   
   gregorianFormatMap::iterator iter = 
                              gregorianFormatMapInstance.begin();
   if ( gregorianFormatMapInstance.end() == iter )
   {
      logStdOut( I_( "DateHelper::" )
                 I_( "getGregorianDateFormat(DString &," )
                 I_( "DString &) exit 1" ) );
      return false;
   }
   
   do
   {
      try
      {
	      if ( iter->second )
		   {
            bool isError;
            iter->second->parse( date,
                                 isError );
            if ( false == isError )
            {
               format = iter->first;
               fParsed = true;
               break;
            }
         }
      }  // if the parse fails, it throws
	      // not a problem -- we continue
      catch ( ConditionException & ce )
      {
         ce.getCode();
      }
	  catch ( ... )
	  {
		  ;
	  }
      
      ;	  
   } while ( ++iter != gregorianFormatMapInstance.end() );

   logStdOut( I_( "DateHelper::" )
              I_( "getGregorianDateFormat(DString &," )
              I_( "DString &) exit 2" ) );
   return fParsed;
}


DString & Infra::DateHelper::getGregorianOffset( 
                                            DString & minuend, 
                                            DString & subtrahend, 
                                            DString & result )
{
   logStdOut( I_( "DateHelper::" )
              I_( "getGregorianOffset(DString &," )
              I_( "DString &,DString &)" ) );
   double min, sub;

   getStringDateAsDouble( minuend, min );
   getStringDateAsDouble( subtrahend, sub );
   
   getGregorianOffset( min, sub, result );
   logStdOut( I_( "DateHelper::" )
              I_( "getGregorianOffset(DString &," )
              I_( "DString &,DString &) exit" ) );
   return result;
}


int Infra::DateHelper::getWeekDay( Infra::Date & date )
{
   logStdOut( I_( "DateHelper::" )
              I_( "getWeekDay()" ) );
   {
      CriticalSection cs( tracerLock );
      TRACER_METHOD( I_("DateHelper::getWeekDay( Infra::Date )") );
   }

   Infra::GregorianCalendar calendar( Infra::Locale::
                                          getCurrentInstance() );
   calendar.setTime( date.getDateAsDouble() );
   int retVal = calendar.get( ::GregorianCalendar::DAY_OF_WEEK ) 
                                                             - 1;
   logStdOut( I_( "DateHelper::" )
              I_( "getWeekDay() exit" ) );
   return retVal;
}


bool Infra::DateHelper::isDayInMonth( const int nDayIn, 
                                      const int nMonthIn ) 
{
   logStdOut( I_( "DateHelper::" )
              I_( "isDayInMonth()" ) );
   {
      CriticalSection cs( tracerLock );
      TRACER_METHOD( I_("DateHelper::getDayOfYear( void ) const") );
   }

   if( nDayIn <= 0 || nMonthIn < 0 )
   {
      logStdOut( I_( "isDayInMonth() exit 1" ) );
      return false;   
   }

   if( FEBRUARY == nMonthIn && nDayIn < 30 )
   {
      logStdOut( I_( "DateHelper::" )
                 I_( "isDayInMonth() exit 2" ) );
      return true;
   }
   else
   {
      if( nDayIn > _nDaysInMonth[ nMonthIn ] )
      {
         logStdOut( I_( "DateHelper::" )
                    I_( "isDayInMonth() exit 3" ) );
         return false;
      }
   }

   logStdOut( I_( "DateHelper::" )
              I_( "isDayInMonth() exit 4" ) );
   return true;
}


bool Infra::DateHelper::isNullValue( const DString & strDate )
{
   logStdOut( I_( "DateHelper::" )
              I_( "isNullValue()" ) );
   {
      CriticalSection cs( tracerLock );
      TRACER_METHOD( I_( "DateHelper::isNullValue( " )
                     I_( "const DString & )" ) );
   }

   //Check the values for null or spaces or all zeros
   if ( stringHasOnly( strDate, I_(" ") ) || 
        strDate == I_("") || 
        stringHasOnly( strDate, I_("0") )  )
   {
      logStdOut( I_( "isNullValue() exit 1" ) );
      return true;
   }

   logStdOut( I_( "DateHelper::" )
              I_( "isNullValue() exit 2" ) );
   return false;
}


bool Infra::DateHelper::isValidGregorianDate( const DString & 
                                                        strDate )
{
   logStdOut( I_( "DateHelper::" )
              I_( "isValidGregorianDate(DString &)" ) );
   {
      CriticalSection cs( tracerLock );
      TRACER_METHOD( I_( "DateHelper::isValidGregorianDate( " )
                     I_( "const DString & strDate )" ) );
   }

   DString format;
   bool retVal = getGregorianDateFormat( strDate, format );
   logStdOut( I_( "DateHelper::" )
              I_( "isValidGregorianDate(DString &) exit" ) );
   return retVal;
}

   
bool Infra::DateHelper::isValidGregorianDate( const DString & 
                                                         strDate, 
                                      const DString & argFormat ) 
{
   logStdOut( I_( "DateHelper::" )
              I_( "isValidGregorianDate(DString &,DString &)" ) );
   {
      CriticalSection cs( tracerLock );
      TRACER_METHOD( I_( "DateHelper::isValidGregorianDate( " )
                     I_( "const DString & strDate, " )
                     I_( "const DString & argformat )" ) );
   }

   Infra::SimpleDateFormat * tmp = gregorianFormatMapInstance[ 
                                                    argFormat ];
   if ( ( ( Infra::SimpleDateFormat * ) NULL ) == tmp )
   {
      logStdOut( I_( "DateHelper::" )
                 I_( "isValidGregorianDate(DString &,DString &)" )
                 I_( " exit 1" ) );
      return false;
   }

   try
   {
      bool isError;
      tmp->parse( strDate,
                  isError );
      return !isError;
   }
   catch ( ConditionException & ce )
   {
      ce.getCode();
      logStdOut( I_( "DateHelper::" )
                 I_( "isValidGregorianDate(DString &,DString &)" )
                 I_( " exit 2" ) );
      return false;
   }
   catch ( ... ) // if the Infra::SimpleDateFormat * is not found
	             // in the map, we'll end up here
   {
      logStdOut( I_( "DateHelper::" )
                 I_( "isValidGregorianDate(DString &,DString &)" )
                 I_( " exit 3" ) );
	   return false;
   }

   logStdOut( I_( "DateHelper::" )
              I_( "isValidGregorianDate(DString &,DString &)" )
              I_( " exit 4" ) );
   return true;
}


bool Infra::DateHelper::spanYear( const DString & startDate,
                                  const DString & endDate )
{
   logStdOut( I_( "DateHelper::" )
              I_( "spanYear(DString &,DString &)" ) );
   {
      CriticalSection cs( tracerLock );
      TRACER_METHOD( I_( "DateHelper::spanYear( " )
                     I_( "const DString & startDate, " )
                     I_( "const DString & endDate )" ) );
   }
   
   double start, end;
   getStringDateAsDouble( startDate, start );
   getStringDateAsDouble( endDate, end );
   bool retVal = spanYear( start, end );
   logStdOut( I_( "DateHelper::" )
              I_( "spanYear(DString &,DString &) exit" ) );
   return retVal;
}


void Infra::DateHelper::subtractGregorian( 
                                      const DString & minuend, 
                                      const DString & subtrahend,
                                      DString & yearDiff,
                                      DString & monthDiff,
                                      DString & dayDiff )
{
   logStdOut( I_( "DateHelper::" )
              I_( "subtractGregorian(DString &,DString &," )
              I_( "DString &,DString &,DString &)" ) );
   {
      CriticalSection cs( tracerLock );
      TRACER_METHOD( I_( "DateHelper::subtractGregorian( " )
                     I_( "const DString & minuend, " )
                     I_( "const DString & subtrahend, " )
                     I_( "DString & yearDiff, " )
                     I_( "DString & monthDiff, " )
                     I_( "DString & dayDiff )") );
   }

   double minDate, subDate;

   if ( getStringDateAsDouble( minuend, minDate ) &&
        getStringDateAsDouble( subtrahend, subDate ) )
      subtractGregorian( minDate,
                         subDate,
                         yearDiff,
                         monthDiff,
                         dayDiff );
   logStdOut( I_( "DateHelper::" )
              I_( "subtractGregorian(DString &,DString &," )
              I_( "DString &,DString &,DString &) exit" ) );
}


void Infra::DateHelper::subtractGregorian( 
                                  const Infra::Date & minuend, 
                                  const Infra::Date & subtrahend,
                                  DString & yearDiff,
                                  DString & monthDiff,
                                  DString & dayDiff )
{
   logStdOut( I_( "DateHelper::" )
              I_( "subtractGregorian(Date &," )
              I_( "Date &,DString &,DString &,DString &)" ) );
   {
      CriticalSection cs( tracerLock );
      TRACER_METHOD( I_( "DateHelper::subtractGregorian( " )
                     I_( "const Infra::Date & minuend, " )
                     I_( "const Infra::Date & subtrahend, " )
                     I_( "DString & yearDiff, " )
                     I_( "DString & monthDiff, " )
                     I_( "DString & dayDiff )") );
   }

   subtractGregorian( minuend.getDateAsDouble(),
                      subtrahend.getDateAsDouble(),
                      yearDiff,
                      monthDiff,
                      dayDiff );
   logStdOut( I_( "DateHelper::" )
              I_( "subtractGregorian(Date &," )
              I_( "Date &,DString &,DString &,DString &) " )
              I_( "exit" ) );
}


/* ########################################################### *
 *                                                             *
 *                      private methods                        *
 *                                                             *
 * ########################################################### */


/**
 * add offset in milliseconds and store it in result
 * 
 * @param start  - initial time as an offset from 2400 01-01-1970
 * @param offset - days to offset
 * @param result - location to store the result
 * @return - the result
 */

double Infra::DateHelper::addDayOffset( double start,
                                        double dayoffset, 
                                        double & result )
{
   start += dayoffset * NUMBER_OF_MILLISECONDS_PER_DAY;
   result = start;
   return result;
}


/** Method that will add an integer number of Days to a
 *     double
 *  @param date - location of date to be incremented
 *  @param nDays - number of days to add to UDate
 *  @returns - true if successful */

bool Infra::DateHelper::addDays( double & date, 
                                 const DString & nDays )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(double &,const DString &)" ) );
   date = addGregorian( date, 
                        DString( I_( "" ) ), 
                        DString( I_( "" ) ), 
                        nDays ); 
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(double &,const DString &) exit" ) );
   return true;
}


/** Method that will add an integer number of years to a
 *     double
 *  @param date - double to be incremented
 *  @param nDays - number of years to add to double
 *  @returns - true if successful */

bool Infra::DateHelper::addDays( double & date, 
                                 const int nDays )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(double &,int)" ) );
   date = addGregorian( date, 0, 0, nDays ); 
   logStdOut( I_( "DateHelper::" )
              I_( "addDays(double &,int) exit" ) );
   return true;
}


/** Adds a Gregorian offset of year month day to a double
 *  @param date - double for Gregorian offset to be applied
 *  @param yearDiff - DString containing year offset
 *  @param monthDiff - DString to containing month offset
 *  @param dayDiff - DString to containing day offset 
 *  @returns - the total in a double */

double Infra::DateHelper::addGregorian( double date, 
                                        const DString & yearDiff,
                                        const DString & monthDiff,
                                        const DString & dayDiff )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addGregorian(" )
              I_( "double date, const DString &," )
              I_( "const DString &,const DString &)" ) );
   double retVal = addGregorian( date,
                                 asInteger( yearDiff ),
                                 asInteger( monthDiff ),
                                 asInteger( dayDiff ) );
   logStdOut( I_( "DateHelper::" )
              I_( "addGregorian(" )
              I_( "double,DString &," )
              I_( "DString &,DString &) exit" ) );
   return retVal;
}


/** Adds a Gregorian offset of year month day to a double
 *  @param date - double for Gregorian offset to be applied
 *  @param yearDiff - integer containing year offset
 *  @param monthDiff - integer containing month offset
 *  @param dayDiff - integer containing day offset 
 *  @returns - the total in a double */

double Infra::DateHelper::addGregorian( double date,
                                        int yearDiff,
                                        int monthDiff,
                                        int dayDiff )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addGregorian(double date,int,int,int)" ) );
   Infra::GregorianCalendar calendar( 
      Infra::Locale::getCurrentInstance() );
   calendar.setTime( date );

   int prevYear, prevMonth, prevDay;
   prevYear = calendar.get( ::GregorianCalendar::YEAR );
   prevMonth = calendar.get( ::GregorianCalendar::MONTH );
   prevDay = calendar.get( ::GregorianCalendar::DATE );
      
   int days;
   
   // advance to first of a month
   days = daysInGregorianMonth( calendar, 
                                prevMonth,
                                prevYear );
   if ( ( days - prevDay ) < dayDiff )
   {
      dayDiff -= days - prevDay + 1;
      prevDay = 1;
      ++prevMonth;
      if ( DECEMBER < prevMonth )
      {
         prevMonth = JANUARY;
         ++prevYear;
      }
   }

   // add years
   prevYear += yearDiff;
   if ( 12 < monthDiff )
   {
      prevYear += monthDiff / 12;
      monthDiff %= 12;
   }

   // add months
   while ( monthDiff )
   {
      // make sure we're not past the end of the month
      days = daysInGregorianMonth( calendar, 
                                   prevMonth,
                                   prevYear );
      if ( days < prevDay )
      {
         dayDiff -= prevDay - days;
         prevDay -= days;
         ++prevMonth;
      }
   
      ++prevMonth;
      --monthDiff;
      if ( 12 == prevMonth )
      {
         ++prevYear;
         prevMonth = 0;
      }
   }

   // add days
   while( ( days = daysInGregorianMonth( calendar, 
                                         prevMonth,
                                         prevYear ) ) < dayDiff )
   {
      if ( ++prevMonth == 12 )
      {
         prevMonth = 0;
         ++prevYear;
      }
      dayDiff -= days;
   }
   calendar.set( prevYear, prevMonth, prevDay + dayDiff );

   logStdOut( I_( "DateHelper::" )
              I_( "addGregorian(double date,int,int,int) " )
              I_( "exit" ) );
   return calendar.getTime();
}


/** Method that will add an integer number of years to a
 *     double
 *  @param date - double to be incremented
 *  @param nDays - number of years to add to double
 *  @returns - true if successful */

bool Infra::DateHelper::addYears( double & date, 
                                  const DString & nYears )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addYears(double&,DString&)" ) );
   date = addGregorian( date, 
                        nYears, 
                        DString( I_( "" ) ), 
                        DString( I_( "" ) ) ) ;
   logStdOut( I_( "DateHelper::" )
              I_( "addYears(double&,DString&) exit" ) );
   return true;
}


/** Method that will add an integer number of years to a
 *     double
 *  @param date - location of date to be incremented
 *  @parma nDays - number of years to add to double
 *  @returns - true if successful */

bool Infra::DateHelper::addYears( double & date, 
                                  const int nYears )
{
   logStdOut( I_( "DateHelper::" )
              I_( "addYears(double&,int)" ) );
   date = addGregorian( date, nYears, 0, 0 );
   logStdOut( I_( "DateHelper::" )
              I_( "addYears(double&,int) exit" ) );
   return true;
}


/**
 * extracts the year, month, and day from a DString
 * date passed in and places them in locations
 * passed in
 * 
 * @param strDate The string containing the date
 * @param format  the format to use to parse the date string
 * @param day
 * @param month
 * @param year
 * @param locale  the locale to use to specify the calendar
 */

void Infra::DateHelper::extractGregorianDateComponents( 
                                         const DString & strDate, 
                                         const DString & format, 
                                         DString & day, 
                                         DString & month, 
                                         DString & year,
                                   const Infra::Locale * locale )
{
   logStdOut( I_( "DateHelper::" )
              I_( "extractGregorianDateComponents()" ) );
   DString inputFormat;

   if ( false == getGregorianDateFormat( strDate,
                                         inputFormat ) )
   {
      logStdOut( I_( "DateHelper::" )
                 I_( "extractGregorianDateComponents() exit 1" ) );
      return;
   }

   bool isError;
   double date = gregorianFormatMapInstance[ inputFormat ]->
                                                parse( strDate,
                                                       isError );
   if ( false == isError )
   {
      Infra::GregorianCalendar * calendar = 
                             new Infra::GregorianCalendar( locale );

      calendar->setTime( date );
      day = calendar->get( ::GregorianCalendar::DATE );
      month = calendar->get( ::GregorianCalendar::MONTH );
      year = calendar->get( ::GregorianCalendar::YEAR );
      delete calendar;
   }
   logStdOut( I_( "DateHelper::" )
              I_( "extractGregorianDateComponents() exit 2" ) );
}


/** Returns the offset of two dates (minuend - subtrahend) in
 *     DString format: YYYYMMDD
 *  @param minuend - a UDate object 
 *  @param subtrahend - a UDate object
 *  @param result - DString containing the offset result   
 *     offset = minuend - subtrahend */

DString & Infra::DateHelper::getGregorianOffset( double minuend, 
                                            double subtrahend,
                                            DString & result )
{
   logStdOut( I_( "DateHelper::" )
              I_( "getGregorianOffset()" ) );
   if ( minuend < subtrahend )
       std::swap( minuend, subtrahend );
   
   double offset = minuend - subtrahend;
   int year, month, day;
   getGregorianYearMonthDayOffsets( offset /
	                                   ( 1000 * 60 * 60 * 24 ), 
                                    subtrahend, 
                                    year, 
                                    month, 
                                    day );
   I_CHAR tmp[ 9 ];
   i_sprintf( tmp, 
              I_( "%04.4d%02.2d%02.2d" ), year, month, day );   
   result = tmp;
   logStdOut( I_( "DateHelper::" )
              I_( "getGregorianOffset() exit" ) );
   return result;
}


/** (Gregorian only) Retrieves the offset date in individual
 *     parts
 *  @param offset - offset number to be applied to long
 *  @param subtrahend - long to apply the offset to 
 *  @param yearDiff - year value of the offset date
 *  @param monthDiff - month value of the offset date
 *  @param dayDiff - day value of the offset date */

void Infra::DateHelper::getGregorianYearMonthDayOffsets( double
                                                          offset, 
                                               double subtrahend,
                                               int & year,
                                               int & month,
                                               int & day )
{
   logStdOut( I_( "DateHelper::" )
              I_( "getGregorianYearMonthDayOffsets()" ) );
   Infra::GregorianCalendar calendar( 
      Infra::Locale::getCurrentInstance() );

   calendar.setTime( subtrahend );

   int prevYear, prevMonth, checkYear, daysInYear;
   prevYear = calendar.get( ::GregorianCalendar::YEAR );
   prevMonth = calendar.get( ::GregorianCalendar::MONTH );
   
   
   month = 0, year = 0;
   int currMonth = prevMonth;
   int currYear = checkYear = prevYear;
   int days;

   if ( prevMonth > 1 ) // March or later month
      ++checkYear;

   while ( offset >= ( daysInYear = 
                       365 + calendar.isLeapYear( checkYear ) ) )
   {
      offset -= daysInYear;
      ++checkYear;
      ++currYear;
      ++year;
   }

   while( ( days = daysInGregorianMonth( calendar, 
                                         currMonth,
                                         currYear ) ) < offset )
   {
      ++month;
      if ( ++currMonth == 12 )
      {
         currMonth = 0;
         ++currYear;
      }
      offset -= days;
   }
   day = (int)offset;
   logStdOut( I_( "DateHelper::" )
              I_( "getGregorianYearMonthDayOffsets() exit" ) );
}


/**
 * - attempts to parse a string date and return it in
 *   a double location passed in
 * 
 * @param strDate - the string date
 * @param retVal  - the location to store the result
 * @return - true, if the date could be parsed
 *         - false, otherwise
 */
bool Infra::DateHelper::getStringDateAsDouble( const DString & 
                                                         strDate,
                                               double & retVal )
{
   logStdOut( I_( "DateHelper::" )
              I_( "getStringDateAsDouble()" ) );
   bool fParsed = false;
   // loop thru the formats until one parses Ok
   gregorianFormatMap::iterator iter = 
                              gregorianFormatMapInstance.begin();
   
   if ( gregorianFormatMapInstance.end() == iter )
   {
      logStdOut( I_( "DateHelper::" )
                 I_( "getStringDateAsDouble() exit 1" ) );
      return false;
   }

   // loop infinitely
   while ( 1 )
   {
      try
      {
         if ( iter->second )
         {
            bool isError;
            retVal = ( double ) iter->second->parse( strDate,
                                                     isError );
            if ( false == isError )
            {
               fParsed = true;
               break;
            }
         }
      }  //if the parse fails, it throws
      catch ( ConditionException & ce )
      {
         ce.getCode();
      }
	  catch ( ... )
	  {
		  ;
	  }
      
      ++iter;
      if ( gregorianFormatMapInstance.end() == iter )
         break;
   }
   logStdOut( I_( "DateHelper::" )
              I_( "getStringDateAsDouble() exit 2" ) );
   return fParsed;
}


/** Determines the difference between two Gregorian dates and
 *     stores the results in year/month/day strings
 *  @param minuend - a double
 *  @param subtrahend - a double
 *  @param yearDiff - DString to receive year offset
 *  @param monthDiff - DString to receive month offset
 *  @param dayDiff - DString to receive day offset */

void Infra::DateHelper::subtractGregorian( double minuend, 
                                           double subtrahend,
                                           DString & year,
                                           DString & month,
                                           DString & day )
{
   logStdOut( I_( "DateHelper::" )
              I_( "subtractGregorian()" ) );
   if ( minuend <subtrahend )
      std::swap( minuend, subtrahend );

   double offset = minuend - subtrahend;
   int yearOffset, monthOffset, dayOffset;
   getGregorianYearMonthDayOffsets( offset /
	                                ( 1000 * 60 * 60 * 24 ), 
                                    subtrahend, 
                                    yearOffset, 
                                    monthOffset, 
                                    dayOffset );
   I_CHAR tmp[ 5 ];
   i_sprintf( tmp, I_( "%04.4d" ), yearOffset );   
   year = tmp;
   i_sprintf( tmp, I_( "%02.2d" ), monthOffset );   
   month = tmp;
   i_sprintf( tmp, I_( "%02.2d" ), dayOffset );   
   day = tmp;
   logStdOut( I_( "DateHelper::" )
              I_( "subtractGregorian() exit" ) );
}


/**
 * determines if the difference between two dates spans a year
 * 
 * @param startDate
 * @param endDate
 * @return true if a year is spanned (>= 1 year)
 *         false otherwise
 */

bool Infra::DateHelper::spanYear( double lesserDate,
                                  double greaterDate )
{
   logStdOut( I_( "DateHelper::" )
              I_( "spanYear()" ) );
   if ( greaterDate < lesserDate )
       std::swap( greaterDate, lesserDate );

   Infra::DateHelper::addYears( lesserDate, 1 );

   bool retVal = ( lesserDate <= greaterDate );
   logStdOut( I_( "DateHelper::" )
              I_( "spanYear() exit" ) );
   return retVal;
}

/************************
**                     **
**   static functions  **
**                     **
************************/

static int daysInGregorianMonth( 
                             Infra::GregorianCalendar & calendar,
                             int currMonth,
                             int currYear )
{
   static char daysInMonth[] = { 31, 28, 31, 
                                 30, 31, 30, 
                                 31, 31, 30, 
                                 31, 30, 31 };

   logStdOut( I_( "DateHelper::" )
              I_( "daysInGregorianMonth()" ) );
   int addLeapDay = ( calendar.isLeapYear( currYear )
                      && ( currMonth == 1 ) ) ? 1 :
                                                0;

   logStdOut( I_( "DateHelper::" )
              I_( "daysInGregorianMonth() exit" ) );
   return daysInMonth[ currMonth ] + addLeapDay;
}
  

/************************
**                     **
**   public functions  **
**                     **
************************/

void Infra::DateHelper::resetGregorianFormatMap( Infra::Locale & locale )
{
   logStdOut( I_( "DateHelper::" )
              I_( "resetGregorianFormatMap()" ) );
   static MutexSemaphore sema4;
   CriticalSection cs( &sema4 );

   // delete the map's previous contents

   Infra::DateHelper::gregorianFormatMap::iterator iter
       = Infra::DateHelper::gregorianFormatMapInstance.begin();
   int count = 0;

   while ( iter != Infra::
                   DateHelper::gregorianFormatMapInstance.end() )
   {
      if ( iter->second )
         delete iter->second;
      ++count;
      ++iter;
   }

   DF_MMDDCCYY_format = new 
         Infra::SimpleDateFormat( Infra::DateHelper::DF_MMDDCCYY,
                                  locale,
                                  true );
   DF_FSMMDDCCYY_format = new
       Infra::SimpleDateFormat( Infra::DateHelper::DF_FSMMDDCCYY,
                                locale,
                                true );
   DF_FDMMDDCCYY_format = new
       Infra::SimpleDateFormat( Infra::DateHelper::DF_FDMMDDCCYY,
                                locale,
                                true ); 
   DF_CCYYMMDD_format = new 
         Infra::SimpleDateFormat( Infra::DateHelper::DF_CCYYMMDD,
                                  locale,
                                  true );
   DF_FSCCYYMMDD_format = new
       Infra::SimpleDateFormat( Infra::DateHelper::DF_FSCCYYMMDD,
                                locale,
                                true );
   DF_FDCCYYMMDD_format = new
       Infra::SimpleDateFormat( Infra::DateHelper::DF_FDCCYYMMDD,
                                locale,
                                true );
   DF_DDMMCCYY_format = new
         Infra::SimpleDateFormat( Infra::DateHelper::DF_DDMMCCYY,
                                  locale,
                                  true );
   DF_FPDDMMCCYY_format = new
       Infra::SimpleDateFormat( Infra::DateHelper::DF_FPDDMMCCYY,
                                locale,
                                true );

   DF_MMDDCCYY_format->setLenient( false ); // strict
   Infra::DateHelper::gregorianFormatMapInstance[ Infra::
                  DateHelper::DF_MMDDCCYY ] = DF_MMDDCCYY_format;
   DF_FSMMDDCCYY_format->setLenient( false ); // strict
   Infra::DateHelper::gregorianFormatMapInstance[ Infra::
              DateHelper::DF_FSMMDDCCYY ] = DF_FSMMDDCCYY_format;
   DF_FDMMDDCCYY_format->setLenient( false ); // strict
   Infra::DateHelper::gregorianFormatMapInstance[ Infra::
              DateHelper::DF_FDMMDDCCYY ] = DF_FDMMDDCCYY_format;
   DF_CCYYMMDD_format->setLenient( false ); // strict
   Infra::DateHelper::gregorianFormatMapInstance[ Infra::
                  DateHelper::DF_CCYYMMDD ] = DF_CCYYMMDD_format;
   DF_FSCCYYMMDD_format->setLenient( false ); // strict
   Infra::DateHelper::gregorianFormatMapInstance[ Infra::
              DateHelper::DF_FSCCYYMMDD ] = DF_FSCCYYMMDD_format;
   DF_FDCCYYMMDD_format->setLenient( false ); // strict
   Infra::DateHelper::gregorianFormatMapInstance[ Infra::
              DateHelper::DF_FDCCYYMMDD ] = DF_FDCCYYMMDD_format;
   DF_DDMMCCYY_format->setLenient( false ); // strict
   Infra::DateHelper::gregorianFormatMapInstance[ Infra::
                  DateHelper::DF_DDMMCCYY ] = DF_DDMMCCYY_format;
   DF_FPDDMMCCYY_format->setLenient( false ); // strict
   Infra::DateHelper::gregorianFormatMapInstance[ Infra::
              DateHelper::DF_FPDDMMCCYY ] = DF_FPDDMMCCYY_format;
   logStdOut( I_( "DateHelper::" )
              I_( "resetGregorianFormatMap() exit" ) );
}

// the following function must be called from dllMain()
void initGregorianFormatMap( void )
{
   logStdOut( I_( "DateHelper::" )
              I_( "initGregorianFormatMap()" ) );
   Infra::Locale * locale = Infra::Locale::getDefaultInstance();
   Infra::DateHelper::resetGregorianFormatMap( *locale );
   logStdOut( I_( "DateHelper::" )
              I_( "initGregorianFormatMap() exit" ) );
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
// $Log:   Y:/VCS/iFastAWD/dicore/infradatehelper.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:54   kovacsro
// Initial revision.
//
//   Rev 1.1   04 Jan 2001 18:40:02   dt14177
//fixed TRACER_VARIABLE release
//compile problems
//
//   Rev 1.0   28 Dec 2000 08:55:10   dt14177
// 
// 

