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

#define COMPONENT_NAME I_( "dicore" )

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

#ifndef SMPDTFMT_H
   #include <smpdtfmt.h>
#endif


#ifndef INFRADATE_HPP
   #include "infradate.hpp"
#endif


#ifndef INFRAGREGORIANCALENDAR_HPP
   #include "infragregoriancalendar.hpp"
#endif

#ifndef INFRASIMPLEDATEFORMAT_HPP
   #include "infrasimpledateformat.hpp"
#endif


#ifndef INFRADATEFORMAT_HPP
   #include "infradateformat.hpp"
#endif


#ifndef BASE_H
   #include "base.h"
#endif

#ifndef DICORE_H
   #include "dicore.h"
#endif

#ifndef DICORE_CONDITIONS_HPP
#include "dicore_conditions.hpp"
#endif

#ifndef DICBOCORE_H
#include "dicbocore.h"
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

#include <assert.h>

bool getCfgDisplayMask( const DString & lcv,
                        DString & mask );

const DString DATE_NAME = I_( "Date" );


MsgPair en_usInfraDate[] = 
{
   { 
      Infra::Date::ICU_ERROR,
      I_( "ICU error has occurred with value %VALUE%." ),
      I_( "Check ICU Runtime Environment." )
   }
};


Condition::mapCodePagesToLanguages languagesMapForInfraDate[] =
{ 
   {
      I_( "C" ), en_usInfraDate
   },
};


void DICORE_LINKAGE logStdOut( const I_CHAR * message )
{
}


static void throwIfNeeded( UErrorCode code,
                           I_CHAR * methodName )
{
   logStdOut( I_( "Date::" )
              I_( "throwIfNeeded()" ) );
   if ( U_FAILURE( code ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( code ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( I_( "Date" ),
		                   methodName,
                         Infra::Date::ICU_ERROR,
                         languagesMapForInfraDate,
                         idiStr );
   }
   logStdOut( I_( "Date::" )
              I_( "throwIfNeeded() exit" ) );
}


Infra::Date::Date():
      _dfFormat( I_( "" ) )
{
   TRACER_CONSTRUCTOR( I_( "Date()" ) );
   logStdOut( I_( "Date() noexit" ) );
}


Infra::Date::Date( const DString & strDateIn ):
      _dfFormat( I_( "" ) )
{
   TRACER_CONSTRUCTOR( I_( "Date( DString & strDate )" ) );
   
   logStdOut( I_( "Date::" )
              I_( "Date(DString &)" ) );
   setDate( strDateIn );

   if( I_( "" ) == _dfFormat )
   {
      if( Infra::DateHelper::isNullValue( _strDate ) )
      {
         //this is ok everything is initialized to null
         _strDate = I_("");
      }
      else
      {
      //our current design philosophy is to let the invalid value
      //go with no exceptions being thrown
      }
   }
   else
   {
      if( !isValidGregorianDate() )
      {
      //our current design philosophy is to let the invalid value
      //go with no exceptions being thrown
      }
   }
   logStdOut( I_( "Date::" )
              I_( "Date(DString &) exit" ) );
}



Infra::Date::Date( const Infra::Date &copy )
    : _dfFormat( copy._dfFormat ),
      _nMonth( copy._nMonth ),
      _nYear( copy._nYear ),
      _nDayOfYear( copy._nDayOfYear ),
      _nDayOfMonth( copy._nDayOfMonth ),
      _strDate( copy._strDate )

{
   TRACER_CONSTRUCTOR( I_( "Date( const Infra::Date & copy )") );
   logStdOut( I_( "Date::" )
              I_( "Date(DString &)" ) );
   logStdOut( I_( "Date::" )
              I_( "Date(DString &) exit" ) );
}


Infra::Date& Infra::Date::operator=( const Infra::Date& copy )
{
   TRACER_METHOD( I_("operator=( const Infra::Date & )") );

   logStdOut( I_( "Date::" )
              I_( "operator=(Date&)" ) );
   if ( this == &copy )
      return *this;

   _dfFormat = copy._dfFormat;
   _nMonth = copy._nMonth;
   _nYear = copy._nYear;
   _nDayOfYear = copy._nDayOfYear;
   _nDayOfMonth = copy._nDayOfMonth;
   _strDate = copy._strDate;
   _date = copy._date;

   logStdOut( I_( "Date::" )
              I_( "operator=(Date&) exit" ) );
   return *this;
}


Infra::Date::~Date()
{
   logStdOut( I_( "Date::" )
              I_( "~Date() noexit" ) );
}


DString Infra::Date::getDate( void ) const
{
   return _strDate;
}


DString Infra::Date::getDate( const DString & format ) const
{
   logStdOut( I_( "Date::" )
              I_( "getDate(DString &)" ) );
   DString retVal;
   Infra::DateHelper::formatGregorianDate( _strDate, 
                                      retVal,
                                      format );
   logStdOut( I_( "Date::" )
              I_( "getDate(DString &) exit" ) );
   return retVal;
}


bool Infra::Date::setDate( const DString & strDate )
{
   TRACER_METHOD( I_( "setDate( const DString & )" ) );

   logStdOut( I_( "Date::" )
              I_( "setDate(DString &)" ) );
   DString dfFormat;

   if ( false == Infra::DateHelper::getGregorianDateFormat( 
                                            strDate, dfFormat ) )
   {
      if( Infra::DateHelper::isNullValue( strDate ) )
      {
         //this is ok set everything to null
         _nDayOfMonth = 0;
         _nDayOfYear = 0; 
         _nMonth = 0;
         _nYear = 0;
         _dfFormat = I_( "" );
         _strDate = I_("");
      }
      else
      {
      //our current design philosophy is to let the invalid value 
      //go with no exceptions being thrown
         logStdOut( I_( "Date::" )
                    I_( "setDate(DString &) exit 1" ) );
         return false;
      }
   }
   else
   {
      _dfFormat = dfFormat;
      DString setString;
      Infra::DateHelper::formatGregorianDate( strDate, 
                                         setString,
                              Infra::DateHelper::DF_FSMMDDCCYY );
      set( setString );

      if( !isValidGregorianDate() )
      {
      //our current design philosophy is to let the invalid value
      //go with no exceptions being thrown
         logStdOut( I_( "Date::" )
                    I_( "setDate(DString &) exit 1" ) );
         return false;
      }

   }

   logStdOut( I_( "Date::" )
              I_( "setDate(DString &) exit 3" ) );
   return true;
}


int Infra::Date::getDayOfYear( void ) const
{
   return _nDayOfYear;
}


int Infra::Date::getYear( void ) const
{
   return _nYear;
}


const DString & Infra::Date::getGregorianDateFormat( void ) const
{
   return _dfFormat;
}


bool Infra::Date::addDays( const int nDays )
{
   TRACER_METHOD( I_("addDays( const int ) ") );

   logStdOut( I_( "Date::" )
              I_( "addDays(int)" ) );
   if( nDays == 0 )
   {
      logStdOut( I_( "Date::" )
                 I_( "addDays(int) exit 1" ) );
      return true; 
   }

   assert( _nDayOfYear > 0 ); //date value is null; set in a date
                              //before calling this method
   
   if( _nDayOfYear == 0 )
   {
      logStdOut( I_( "Date::" )
                 I_( "addDays(int) exit 2" ) );
      return false; 
   }


   _nDayOfYear += nDays;

   _getDateFromDayOfYear();

   setUDate();

   logStdOut( I_( "Date::" )
              I_( "addDays(int) exit 3" ) );
   return true;
}


bool Infra::Date::subtractDays( const int nDays )
{
   TRACER_METHOD( I_( "subtractDays( const int ) " ) );

   logStdOut( I_( "Date::" )
              I_( "subtractDays(int)" ) );
   if( nDays == 0 )
   {
      logStdOut( I_( "Date::" )
                 I_( "subtractDays(int) exit 1" ) );
      return true; 
   }

   assert( _nDayOfYear > 0 );//date value is null; set in a date
                             //before calling this method
   
   if( _nDayOfYear == 0 )
   {
      logStdOut( I_( "Date::" )
                 I_( "subtractDays(int) exit 2" ) );
      return false; 
   }
 
   _nDayOfYear -= nDays;
   
   _getDateFromDayOfYear();

   setUDate();

   logStdOut( I_( "Date::" )
              I_( "subtractDays(int) exit 3" ) );
   return true;
}


bool Infra::Date::addYears( const int nYears )
{
   TRACER_METHOD( I_( "addYears( const int ) " ) );
   
   logStdOut( I_( "Date::" )
              I_( "addYears(int)" ) );
   if( nYears == 0 )
   {
      logStdOut( I_( "Date::" )
                 I_( "addYears(int) exit 1" ) );
      return true; 
   }

   assert( _nYear > 0 ); // date value is null; set in a date
                         // before calling this method
   if( _nYear == 0 )
   {
      logStdOut( I_( "Date::" )
                 I_( "addYears(int) exit 2" ) );
      return false; 
   }
   
   _nYear += nYears;

   if( !Infra::DateHelper::isLeapYear( _nYear ) )
   {
      if( Infra::DateHelper::FEBRUARY == _nMonth )
      {
         if( _nDayOfMonth > Infra::DateHelper::_nDaysInMonth[ 
                                                      _nMonth ] )
         {
            _nDayOfMonth = 1;
            _nMonth++;
         }
      }

   }

   _getDayOfYearFromDate();

   setUDate();

   _buildDateFromParts();

   logStdOut( I_( "Date::" )
              I_( "addYears(int) exit 3" ) );
   return true;
}


bool Infra::Date::isValidGregorianDate( void )
{
   TRACER_METHOD( I_( "isValidGregorianDate( void )" ) );

   logStdOut( I_( "Date::" )
              I_( "isValidGregorianDate()" ) );
   bool retVal = Infra::DateHelper::isValidGregorianDate( _strDate,
                                                   _dfFormat );
   logStdOut( I_( "Date::" )
              I_( "isValidGregorianDate() exit" ) );
   return retVal;
}


bool Infra::Date::operator>( Infra::Date & right )
{
   logStdOut( I_( "Date::" )
              I_( "operator>()" ) );
   bool retVal = ( getDateAsDouble() > right.getDateAsDouble() );
   logStdOut( I_( "Date::" )
              I_( "operator>() exit" ) );
   return retVal;
}


bool Infra::Date::operator<( Infra::Date & right )
{
   logStdOut( I_( "Date::" )
              I_( "operator<()" ) );
   bool retVal = ( getDateAsDouble() < right.getDateAsDouble() );
   logStdOut( I_( "Date::" )
              I_( "operator<() exit" ) );
   return retVal;
}


bool Infra::Date::operator==( Infra::Date & right )
{
   logStdOut( I_( "Date::" )
              I_( "operator==()" ) );
   bool retVal = ( getDateAsDouble() == right.getDateAsDouble() );
   logStdOut( I_( "Date::" )
              I_( "operator==() exit" ) );
   return retVal;
}


bool Infra::Date::operator>=( Infra::Date & right )
{
   return !( *this < right );
}


bool Infra::Date::operator<=( Infra::Date & right )
{
   return !( *this > right );
}


bool Infra::Date::operator!=( Infra::Date & right )
{
   return !( *this == right );
}



// ############## Old DDate private methods #####################
// ##############################################################

void Infra::Date::_buildDateFromParts( void )
{
   TRACER_METHOD( I_( "_buildDateFromParts ( void )" ) );

   logStdOut( I_( "Date::" )
              I_( "_buildDateFromParts()" ) );
   DString strMonth, strDay, strYear;

   if ( 9 > _nMonth )
   {
      strMonth = I_( "0" );
      strMonth += asString( _nMonth + 1 );
   }
   else
      strMonth = asString( _nMonth + 1 );
   if ( 10 > _nDayOfMonth )
   {
      strDay = I_( "0" );
      strDay += asString( _nDayOfMonth );
   }
   else
      strDay = asString( _nDayOfMonth );
   strYear = asString( _nYear );

   _strDate = strMonth;
   _strDate += I_("/");
   _strDate += strDay;
   _strDate += I_("/");
   _strDate += strYear;

   logStdOut( I_( "Date::" )
              I_( "_buildDateFromParts() exit" ) );
}


void Infra::Date::_getDateFromDayOfYear( void )
{
   TRACER_METHOD( I_( "_getDateFromDayOfYear( void ) const" ) );

   logStdOut( I_( "Date::" )
              I_( "_getDateFromDayOfYear()" ) );
   Infra::Date date( _strDate );
   int nYear = date.getYear();
   int inc = 1;
   if ( 0 == _nDayOfYear )
   {
      --_nYear;
      _nDayOfYear = 365 + ( Infra::DateHelper::isLeapYear( 
                                              _nYear ) ? 1 : 0 );
   }

   //calculate year
   if ( _nDayOfYear < 0 )
      inc = -1;
   _nDayOfYear = abs( _nDayOfYear );

   int nYearCount = 0;
   bool fLeap;
   while ( _nDayOfYear > ( 365 + 
           ( ( fLeap = Infra::DateHelper::isLeapYear( _nYear + 
                                     nYearCount ) ) ? 1 : 0 ) ) )
   {
      if ( inc != -1 )
      {
         if ( fLeap && 367 <= _nDayOfYear )
            --_nDayOfYear;//subtract one more for leap year
      }
      else
      {
         if ( Infra::DateHelper::isLeapYear( _nYear + 
                                        nYearCount - 1 ) )
            --_nDayOfYear;
      }
      _nDayOfYear -= 365;
      nYearCount += inc;
   }

    _nYear += nYearCount;

   // Check for leap year
   bool fLeapYear = Infra::DateHelper::isLeapYear( _nYear );
   int days;
   if ( -1 == inc )
   {
      if ( 0 == _nDayOfYear )
         _nDayOfYear = 365 + 
                       ( ( fLeapYear = Infra::DateHelper::
                              isLeapYear( --_nYear ) ) ? 1 : 0 );
      else
         _nDayOfYear = ( 365 + ( ( fLeapYear ) ? 1 : 0 ) ) - 
                       _nDayOfYear;
   }

   int offset = _nDayOfYear;
   _nMonth = Infra::DateHelper::JANUARY;

   while ( ( days = ( Infra::DateHelper::_nDaysInMonth[ _nMonth ] +
                      ( ( fLeapYear && ( 1 == _nMonth ) ) ? 
                        1 : 0 ) )
           ) < offset
         )
   {
      ++_nMonth;
      offset -= days;
   }
   _nDayOfMonth = offset;
   _buildDateFromParts();
   logStdOut( I_( "Date::" )
              I_( "_getDateFromDayOfYear() exit" ) );
}


void Infra::Date::_getDayOfYearFromDate( void )
{
   TRACER_METHOD( I_( "_getDayOfYearFromDate ( void ) const" ) );

   logStdOut( I_( "Date::" )
              I_( "_getDayOfYearFromDate()" ) );
   _nDayOfYear = 0;

   //Calculate day of year
   for( int i = Infra::DateHelper::JANUARY; i < _nMonth; i++ )
   {
      if ( Infra::DateHelper::FEBRUARY == i )
      {
         if( Infra::DateHelper::isLeapYear( _nYear ) )
         {
            _nDayOfYear += 29;//February in a Leap Year
         }
         else
         {
            _nDayOfYear += Infra::DateHelper::_nDaysInMonth[ i ];
         }
      }
      else
      {
         _nDayOfYear += Infra::DateHelper::_nDaysInMonth[ i ];
      }
   }

   _nDayOfYear += _nDayOfMonth;

   logStdOut( I_( "Date::" )
              I_( "_getDayOfYearFromDate() exit" ) );
}


void Infra::Date::setTime( double lTime )
{
   logStdOut( I_( "Date::" )
              I_( "setTime(double)" ) );
   UErrorCode code = U_ZERO_ERROR;
   UnicodeString pattern( "MM/dd/yyyy" );
   ::SimpleDateFormat dfmt( pattern, code );
   throwIfNeeded( code,
				      I_( "Date::setTime( double lTime )" ) );
   
   UnicodeString myString;
   dfmt.format( lTime, myString );

   DString infraDateFormat;
   ICUStringtoIString( myString, infraDateFormat.getImp() );
   set( infraDateFormat );
   logStdOut( I_( "Date::" )
              I_( "setTime(double) exit" ) );
}


// ***************** protected Methods *********************//

void Infra::Date::setUDate( void )
{
   logStdOut( I_( "Date::" )
              I_( "setUDate()" ) );
   static I_CHAR * methodName = I_( "Date::setUDate( void )" );
   UErrorCode code = U_ZERO_ERROR;
   ::Calendar * calendar = ::Calendar::createInstance( code );
   if ( U_FAILURE( code ) )
	  delete calendar;
   throwIfNeeded( code,
                  methodName );
   
   calendar->clear();

   calendar->set( _nYear, _nMonth, _nDayOfMonth );
   code = U_ZERO_ERROR;
   _nDayOfYear = calendar->get( UCAL_DAY_OF_YEAR, code );
   if ( U_FAILURE( code ) )
	  delete calendar;
   throwIfNeeded( code,
                  methodName );
   code = U_ZERO_ERROR;
   set( calendar->getTime( code ) );
   if ( U_FAILURE( code ) )
	  delete calendar;
   throwIfNeeded( code,
                  methodName );
   delete calendar;
   logStdOut( I_( "Date::" )
              I_( "setUDate() exit" ) );
}


void Infra::Date::set( double ltime )
{
   logStdOut( I_( "Date::" )
              I_( "set(double)" ) );
   static I_CHAR * methodName = I_( "Date::set( double ltime )" );
   I_CHAR * buf = new I_CHAR[ 11 ];
   UErrorCode code = U_ZERO_ERROR;
   ::Calendar * calendar = ::Calendar::createInstance( code );
   if ( U_FAILURE( code ) )
	  delete calendar;
   throwIfNeeded( code,
                  methodName );

   code = U_ZERO_ERROR;
   calendar->setTime( ltime, code );
   if ( U_FAILURE( code ) )
	  delete calendar;
   throwIfNeeded( code,
                  methodName );
   code = U_ZERO_ERROR;
   _nDayOfYear = calendar->get( UCAL_DAY_OF_YEAR, code );
   if ( U_FAILURE( code ) )
	  delete calendar;
   throwIfNeeded( code,
                  methodName );
   code = U_ZERO_ERROR;
   _nMonth = calendar->get( UCAL_MONTH, code );
   if ( U_FAILURE( code ) )
	  delete calendar;
   throwIfNeeded( code,
                  methodName );
   code = U_ZERO_ERROR;
   _nDayOfMonth = calendar->get( UCAL_DATE, code );
   if ( U_FAILURE( code ) )
	  delete calendar;
   throwIfNeeded( code,
                  methodName );
   code = U_ZERO_ERROR;
   _nYear = calendar->get( UCAL_YEAR, code );
   if ( U_FAILURE( code ) )
	  delete calendar;
   throwIfNeeded( code,
                  methodName );
   _setTime( ltime );
   i_sprintf( buf,
              I_( "%02.2d/%02.2d/%04.4d" ), 
              _nMonth + 1, 
              _nDayOfMonth, 
              _nYear );
   _strDate = buf;
   delete [] buf;
   delete calendar;
   logStdOut( I_( "Date::" )
              I_( "set(double) exit" ) );
}


void Infra::Date::set( const DString & date )
{
   logStdOut( I_( "Date::" )
              I_( "set(DString &)" ) );
   _strDate = date;
   const I_CHAR * tmp = date.c_str();
   
   i_sscanf( tmp, I_( "%d" ), &_nMonth );
   
   if ( '/' == *( tmp + 2) )
      ++tmp;
   
   i_sscanf( tmp + 2, I_( "%d" ), &_nDayOfMonth );
   
   if ( '/' == *( tmp + 4) )
      ++tmp;
   
   i_sscanf( tmp + 4, I_( "%d" ), &_nYear );
   
   --_nMonth;
   
   setUDate();
   logStdOut( I_( "Date::" )
              I_( "set(DString &) exit" ) );
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
// $Log:   Y:/VCS/iFastAWD/dicore/infradate.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:52   kovacsro
// Initial revision.
//
//   Rev 1.0   28 Dec 2000 08:55:02   dt14177
// 
// 

