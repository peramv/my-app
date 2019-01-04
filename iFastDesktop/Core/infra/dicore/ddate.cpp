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

#define DICORE_DLL
#define COMPONENT_NAME I_("ditabuscore")

#ifndef SRCPRAG_H
   #include <srcprag.h>
#endif

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

#ifndef DDATE_HPP
   #include "ddate.hpp"
#endif

#ifndef XUTILITY
   #define XUTILITY
   #pragma message( "including xutility" )
   #include <xutility>
#endif

#ifndef JAVAGREGORIANCALENDAR_HPP
   #include "javagregoriancalendar.hpp"
#endif

#ifndef JAVALOCALE_HPP
   #include "javalocale.hpp"
#endif

#ifndef JAVADATEFORMAT_HPP
   #include "javadateformat.hpp"
#endif

#ifndef JAVASIMPLEDATEFORMAT_HPP
   #include "javasimpledateformat.hpp"
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

#include <assert.h>

const int DDate::_nBaseYear = 1899;
const long DDate::_lStartOfMonthOffsets[ 12 ] =
{  // Days until start of month
     0L,  31L,  59L,  90L, 120L, 151L,
   181L, 212L, 243L, 273L, 304L, 334L

};

const int DDate::_nDaysInMonth[ 13 ]  = {// Days in the month
                                      31, 28, 31, 30, 31, 30, 31,
                                      31, 30, 31, 30, 31
                                      };


bool getCfgDisplayMask( const DString & lcv,
                        DString & mask );



//***************************************************************
//
//   NAME: DDate::DDate()
//
//  DESCRIPTION:
//      This function is the DDate default constructor.
//
//***************************************************************
DDate::DDate():
      _dfFormat( DF_NULL )
{
   TRACE_CONSTRUCTOR( I_("DDate"), I_("DDate::DDate()") );

}


//***************************************************************
//
//   NAME: DDate::DDate( DString& strDate )
//
//  DESCRIPTION:
//     This function is a DDate constructor that takes a DString.
//  the date passed in must be one of the valid formats.
//
//***************************************************************
DDate::DDate( const DString& strDateIn ):
      JavaDate(), // we initialize later
      _dfFormat( DF_NULL )
{
   TRACE_CONSTRUCTOR( I_("DDate"),
                      I_("DDate::DDate( DString& strDate )") );

   setDate( strDateIn );

   if( DF_NULL == _dfFormat )
   {
      if( _isNullValue( _strDate ) )
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

      if( !isValidDate() )
      {
      //our current design philosophy is to let the invalid value
      //go with no exceptions being thrown
      }

   }
}



//***************************************************************
//
//   NAME: DDate::DDate( const DDate &copy )
//
//  DESCRIPTION:
//     This function is the copy constructor for the DDate Class.
//
//***************************************************************
DDate::DDate( const DDate &copy )
    : JavaDate( copy ),
      _dfFormat( copy._dfFormat ),
      _nMonth( copy._nMonth ),
      _nYear( copy._nYear ),
      _nDayOfYear( copy._nDayOfYear ),
      _nDayOfMonth( copy._nDayOfMonth ),
      _strDate( copy._strDate )

{
   TRACE_CONSTRUCTOR( I_("DDate"),
                      I_("DDate::DDate( const DDate &copy )") );
}


//***************************************************************
//
//   NAME: DDate& DDate::operator=( const DDate& copy )
//
//  DESCRIPTION:
//      This function is the operator = function overload for the
//  DDate Class.
//
//***************************************************************
DDate& DDate::operator=( const DDate& copy )
{
   TRACE_METHOD( I_("DDate"), I_("operator=( const DDate& )") );

   if ( this == &copy )
      return *this;

   _dfFormat = copy._dfFormat;
   _nMonth = copy._nMonth;
   _nYear = copy._nYear;
   _nDayOfYear = copy._nDayOfYear;
   _nDayOfMonth = copy._nDayOfMonth;
   _strDate = copy._strDate;
   JavaDate::operator=( copy );

   return *this;
}


//***************************************************************
//
//   NAME: DDate::~DDate()
//
//  DESCRIPTION:
//      This function is the default destructor of the DDate
//  class.
//
//***************************************************************
DDate::~DDate()
{
   TRACE_DESTRUCTOR( I_("DDate") );
}



int adjustTimePeriod( DString & source,
                      DString & destination,
                      int srcOffset,
                      int destOffset )
{
   if ( '/' == source[ srcOffset + 1 ] )
   {
      destination[ destOffset + 1 ] = source[ srcOffset ];
      srcOffset += 2;
   }
   else
   {
      destination[ destOffset ] = source[ srcOffset ];
      destination[ destOffset + 1 ] = source[ srcOffset + 1 ];
      srcOffset += 3;
   }
   return srcOffset;
}


DString formatDateToStandard( DString & tmp )
{
   DString retVal( I_( "00/00/2000" ) );
   int srcOffset = 0,
       destOffset = 0;
   // do the month
   srcOffset = adjustTimePeriod( tmp,
                                 retVal,
                                 srcOffset,
                                 destOffset );
   // do the day
   srcOffset = adjustTimePeriod( tmp,
                                 retVal,
                                 srcOffset,
                                 destOffset += 3 );
   // do the year
   I_CHAR c;
   int i = tmp.find( ' ' ) - 1;
   if ( i <= 0 )
      i = tmp.length() - 1;
   for ( int j = retVal.length() - 1;
         '/' != ( c = tmp[ i ] );
         --i, --j )
      retVal[ j ] = c;
   return retVal;
}


DString DDate::getCurrentDateAsString( JavaDateFormat & arg )
{
   JavaDate currDate;
   DString tmp = arg.format( &currDate );
   return formatDateToStandard( tmp );
}


DString DDate::getCurrentDateAsString( JavaLocale * loc )
{
   JavaDate currDate;
   DString tmp = JavaDateFormat::getDateInstance( loc ).
      format( &currDate );
   return formatDateToStandard( tmp );
}


DString DDate::getCurrentDateAsString()
{
   JavaDate currDate;
   DString lcv;
   DString mask = I_( "MM/dd/yyyy" );
   DString retVal;

   // get the language, country, variant DString from the current
   // locale
   JavaLocale * locale = JavaLocale::getCurrentInstance();
   locale->getLCV( lcv );

   //  look in the registry for the date format mask
   if ( true == getCfgDisplayMask( lcv, mask ) )
   {
      JavaSimpleDateFormat simple( mask, *locale );
      simple.format( currDate, retVal );
   }
   else  // use the default date format mask
   {
      mask = I_( "MM/dd/yyyy" );
      JavaSimpleDateFormat * simple =
         JavaSimpleDateFormat::US( mask );
      simple->format( currDate, retVal );
      delete simple;
   }
   return retVal;
}


bool getCfgDisplayMask( const DString & lcv,
                        DString & mask )
{
   DString dstrConfiguration( I_( "DisplayMasks" ) );
   DString dstrType( I_( "-D" ) );
   DString dstrKey( lcv );
   dstrKey.append( dstrType );

   mask = GetConfigValueAsString( I_( "DICORE" ),
                                  dstrConfiguration,
                                  dstrKey );

   if ( !mask.length() )
   {
      return false;
   }

   return true;
}


DString & DDate::getGregorianOffset( JavaDate & minuend,
                                     JavaDate & subtrahend,
                                     DString & result )
{
   if ( minuend.before( &subtrahend ) )
       std::swap( minuend, subtrahend );

   DIINT64 offset = minuend - subtrahend;
   int year, month, day;
   getGregorianYearMonthDayOffsets( offset,
                                    subtrahend,
                                    year,
                                    month,
                                    day );
   I_CHAR tmp[ 9 ];
   i_sprintf( tmp,
              I_( "%04.4d%02.2d%02.2d" ), year, month, day );
   result = tmp;
   return result;
}



void DDate::subtractGregorian( JavaDate & minuend,
                               JavaDate & subtrahend,
                               DString & year,
                               DString & month,
                               DString & day )
{
   if ( minuend.before( &subtrahend ) )
   std::swap( minuend, subtrahend );

   DIINT64 offset = minuend - subtrahend;
   int yearOffset, monthOffset, dayOffset;
   getGregorianYearMonthDayOffsets( offset,
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
}


int daysInGregorianMonth( JavaGregorianCalendar & calendar,
                          int currMonth,
                          int currYear )
{
    static char daysInMonth[] = { 31, 28, 31,
                                  30, 31, 30,
                                  31, 31, 30,
                                  31, 30, 31 };

    int addLeapDay = ( calendar.isLeapYear( currYear )
                       && ( currMonth == 1 ) ) ? 1 :
                                                 0;

    return daysInMonth[ currMonth ] + addLeapDay;
}





JavaDate DDate::addGregorian( JavaDate & date,
                              int yearDiff,
                              int monthDiff,
                              int dayDiff )
{
   JavaGregorianCalendar calendar(
      JavaLocale::getCurrentInstance() );
   calendar.setTime( date );

   int prevYear, prevMonth, prevDay;
   prevYear = calendar.get( Calendar::YEAR );
   prevMonth = calendar.get( Calendar::MONTH );
   prevDay = calendar.get( Calendar::DATE );

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
   calendar.set( Calendar::YEAR, prevYear );
   calendar.set( Calendar::MONTH, prevMonth);
   calendar.set( Calendar::DATE, prevDay + dayDiff );

   return calendar.getTime();
}


DString cvtUTCtoDString( DIINT64 time )
{
   // convert __int64__ to long
   long tmp = (long)time;
   // convert long to time_t
   time_t _time = tmp;
   // convert time_t to struct tm
   struct tm * myTime = gmtime( &_time );
   // convert struct tm to MM/dd/yyyy DString
   I_CHAR buf[ 11 ];
   i_strftime( buf, 11, I_( "%m/%d/%Y" ), myTime );
   return DString( buf );
}


// this is stubbed out for now
DIINT64 cvtDStringToUTC( DString & time )
{
   DIINT64 retVal = 0;
   return retVal;
}

//   NEW DDATE PRIVATE METHODs
//   This method will take any gregorian date passed in and its
//   format and convert it to yyyymmdd for comparisons
bool DDate::normaliseGregorianDate( DString &strDateIn,
                                    DString &strFormatIn )
{
   DString strTempDate = stripAll( strDateIn, '/' );
   stripAll( strTempDate, '-' );
   int length = i_strlen(strTempDate.c_str());

   if ( length == 0 )
   {
      return false;
   }
   DString strTempFormat = stripAll ( strFormatIn, '/' );
   stripAll( strTempFormat, '-' );

   strTempFormat = upperCase(strTempFormat);

   // lengths should match
   if ( length != i_strlen(strTempFormat.c_str() ) )
   {
      return false;
   }

   DString strCentury, strYear, strMonth, strDay;

   // get day
   int nDayPos = pos(I_("DD"), strTempFormat);
   if( nDayPos != -1 )
   {
      strDay = strTempDate.substr( nDayPos, 2 );
   }
   else // single character day format
   {
      nDayPos = pos(I_("D"), strTempFormat);
      strDay = I_("0");
      strDay += strTempDate.substr( nDayPos, 1 );
   }

   // get month
   int nMonthPos = pos(I_("MM"), strTempFormat);
   if( nMonthPos != -1 )
   {
      strMonth = strTempDate.substr( nMonthPos, 2 );
   }
   else // single character month format
   {
      nMonthPos = pos(I_("M"), strTempFormat);
      strMonth = I_("0");
      strMonth += strTempDate.substr( nMonthPos, 1 );
   }

   // get year
   int nYearPos = pos(I_("YYYY"), strTempFormat);
   if( nYearPos != -1 )
   {
      strYear = strTempDate.substr( nYearPos, 4 );
   }
   else //two character year format
   {
      nYearPos = pos(I_("YY"), strTempFormat);
      if(nYearPos != -1)
      {
         strYear = I_("00");
         strYear += strTempDate.substr( nYearPos, 2 );
      }
      else //one character year format
      {
         nYearPos = pos(I_("Y"), strTempFormat);
         strYear = I_("0");
         strYear += strTempDate.substr( nYearPos, 1 );
      }
   }
   // normalised format will be in yyyymmdd
   strDateIn = (strYear += strMonth += strDay);
   return true;
}

// returns
// -1  if <
//  0  if =
//  1  if >
int DDate::compareNormalisedDates( DString& strDate1,
                                   DString& strDate2 )
{
   long ldate1, ldate2;
   //convert the yyyymmdd string to longs
   ldate1 = i_ttol(strDate1.c_str());
   ldate2 = i_ttol(strDate2.c_str());

   if( ldate1 < ldate2 )
   {
      return -1;
   }
   if( ldate1 > ldate2 )
   {
      return 1;
   }
   return 0;

}

void DDate::getGregorianYearMonthDayOffsets( DIINT64 offset,
                                           JavaDate & subtrahend,
                                             int & year,
                                             int & month,
                                             int & day )
{
   JavaGregorianCalendar calendar(
      JavaLocale::getCurrentInstance() );

   calendar.setTime( subtrahend );

   int prevYear, prevMonth, checkYear, daysInYear;
   prevYear = calendar.get( Calendar::YEAR );
   prevMonth = calendar.get( Calendar::MONTH );


   year = 0;
   int currMonth = prevMonth - 1;
   int currYear = checkYear = prevYear;
   int days;
   if ( -1 == currMonth )
      currMonth = 0;
   month = currMonth;

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
}


// ##############################################################
// ##############################################################
//                           FROM OLD DDATE
// ##############################################################
// ##############################################################


//***************************************************************
//
//   NAME: DDate::getDate()
//
//  DESCRIPTION:
//     This function will retrieve the date from the DDate class
//  The date will be in the same format as previously set or
//  constructed.
//
//***************************************************************

DString DDate::getDate( void ) const
{
   TRACE_METHOD( I_("DDate"), I_("getDate ( void )") );
   DString retValue;
   if ( DF_FSMMDDCCYY != _dfFormat )
      formatDate( _strDate, retValue, _dfFormat );
   else
      return _strDate;

   return retValue;
}


//***************************************************************
//
//   NAME: DDate::setDate()
//
//  DESCRIPTION:
//      This function will change the date stored in the class to
//  the new date, providing the date is valid.  This function
//  returns true if successful.
//***************************************************************
bool DDate::setDate(const DString& strDate )
{
   TRACE_METHOD(  I_("DDate"),
                  I_("DDate::setDate( const DString& ) ") );

   DATE_FORMAT dfFormat = DF_NULL;
   dfFormat = DDate::getDateFormat( strDate );

   if( DF_NULL == dfFormat )
   {
      if( _isNullValue( strDate ) )
      {
         //this is ok set everything to null
         _nDayOfMonth = 0;
         _nDayOfYear = 0;
         _nMonth = 0;
         _nYear = 0;
         _dfFormat = DF_NULL;
         _strDate = I_("");
         JavaDate::setUDate( 0 );
      }
      else
      {
      //our current design philosophy is to let the invalid value
      //go with no exceptions being thrown
         return false;
      }
   }
   else
   {
      _dfFormat = dfFormat;
      DString setString;
      formatDate( strDate, setString, DF_FSMMDDCCYY );
      set( setString );

      if( !isValidDate() )
      {
      //our current design philosophy is to let the invalid value
      //go with no exceptions being thrown
         return false;
      }

   }

   return true;
}


//***************************************************************
//
//   NAME: DDate::getDayOfYear()
//
//  DESCRIPTION:
//     This function will retrieve the day of year from the DDate
//  class The day range is 1 to 365(366 for leap year).
//
//***************************************************************

int DDate::getDayOfYear( void ) const
{
   TRACE_METHOD( I_("DDate"), I_("getDayOfYear ( void )") );

   return _nDayOfYear;
}

//***************************************************************
//
//   NAME: DDate::getYear()
//
//  DESCRIPTION:
//     This function will the year from the DDate class
//
//***************************************************************

int DDate::getYear( void ) const
{
   TRACE_METHOD( I_("DDate"), I_("getYear ( void )") );

   return _nYear;
}

//***************************************************************
//
//   NAME: DDate::compareHostGregorianDates( const DString &
//                                                         date1,
//                                           const DString &
//                                                        date2 )
//
//  DESCRIPTION:
//      determines the difference between two Host dates
//
//                and returns  1   if   date1 > date2
//                             0   if   date1 = date2
//                            -1   if   date1 < date2
//
//  THROWS:  will throw an exception condition date1 or date2
//      does not match the HostMasks format set in the Registry
//***************************************************************

int DDate::compareHostGregorianDates( const DString &date1,
                                      const DString &date2)
{

   MAKEFRAMEAUTOPROMOTE( DICORE_CONDITION,
                         I_( "DDate::compareHostDates( " )
           I_( "const DString &date1, const DString &date2)" ) );
   if ( (date1.stringHasOnly( I_( " " ) ) ) ||
        (date2.stringHasOnly( I_( " " ) ) ) ||
        (date1.length() == 0)               ||
        (date2.length() == 0) )
   {
      assert(0); // will assert if string is blank
      THROWFROMFILEIDI( DICORE_CONDITION,
                        I_( "DDate::compareHostDates( " )
             I_( "const DString &date1, const DString &date2)" ),
                        DICORE_DATE_STRING_INVALID,
                  I_("Error reading date1 and/or date2 string") )
   }

   DString dstrConfiguration( I_( "HostMasks" ) );
   DString dstrType( I_( "D" ) );
   DString dstrKey;
//   JavaLocale::getLCV(dstrKey);
   dstrKey.append( dstrType );

   DString mask = GetConfigValueAsString( I_( "DICORE" ),
                                          dstrConfiguration,
                                          dstrKey );

   if ( !mask.length() )
   {
       // will assert if registry settings do not have HostMasks
      // defined
      assert(0);
      THROWFROMFILEIDI( DICORE_CONDITION,
                        I_( "DDate::compareHostDates( const" )
                  I_( " DString &date1, const DString &date2)" ),
                        DICORE_HOSTMASKS_NOT_DEFINED_IN_REGISTRY,
                        I_("HostMasks not defined in Registry") )
   }

   DString normalisedDate1 = date1;
   DString normalisedDate2 = date2;

   if(! normaliseGregorianDate( normalisedDate1, mask ) )
   {
       // will assert if HostMasks and date are not of the same
      // format
      assert(0);
      THROWFROMFILEIDI( DICORE_CONDITION,
                        I_( "DDate::compareHostDates( const" )
                  I_( " DString &date1, const DString &date2)" ),
                        DICORE_DATE_STRING_INVALID,
                        I_(" date1 is not in HostMasks format") )
   }
   if(! normaliseGregorianDate( normalisedDate2, mask ) )
   {
      // will assert if HostMasks and date are not of the same
      // format
      assert(0);
      THROWFROMFILEIDI( DICORE_CONDITION,
                        I_( "DDate::compareHostDates( const " )
                   I_( "DString &date1, const DString &date2)" ),
                        DICORE_DATE_STRING_INVALID,
                        I_("date2 is not in HostMasks format") )
   }
   return compareNormalisedDates( normalisedDate1,
                                  normalisedDate2 );

}


//***************************************************************
//
//   NAME: DDate::getDateFormat()
//
//  DESCRIPTION:
//      This function will determine the date format of a DDate
//  object.  Currently this functions will recognize the
//  following formats: DF_MMDDCCYY, DF_CCYYMMDD DF_FSCCYYMMDD,
//  DF_FSMMDDCCYY, DF_FDCCYYMMDD, DF_FDMMDDCCYY.  The function
//  returns the enumerated date format type.
//***************************************************************
DDate::DATE_FORMAT DDate::getDateFormat( void ) const
{

   TRACE_METHOD( I_("DDate"), I_("getDate ( void )") );

   return _dfFormat;
}


//***************************************************************
//
//   NAME: DDate::isValidDate()
//
//  DESCRIPTION:
// This function will determine if the date passed to the member
// is a valid date.  This method considers the following criteria
// when inspecting the passed date for validity:
//   1.  Date must have a length of 8 or 10
//   2.  Date cannot be null
//   3.  Date cannot contain alpha characters, only numerics and
//       - or /
//   4.  Date parts are within valid ranges ie. MM >0 <13 and DD
//       >0 <32
//   5.  Date if leap year and Febuary, allows a DD of 29
//   6.  Date must have a valid DD and MM combination
//The function returns true if the date is valid.
//***************************************************************
bool DDate::isValidDate( const DString & strDate,
                         DATE_FORMAT argFormat )
{
   TRACE_METHOD( I_("DDate"),
                 I_("isValidDate( const DString& )") );

   DATE_FORMAT format = getDateFormat( strDate );

   if ( ( format != argFormat &&
        DF_ANYVALIDFORMAT != argFormat ) ||
        // we couldn't parse the date string
        ( DF_NULL == format ) )
   {
      return false;
   }


   DString strMonth;
   DString strDay;
   DString strYear;

   int month;
   int day;
   int year;

   extractDateComponents( strDate,
                          format, strDay, strMonth, strYear );
   month = asInteger( strMonth ) - 1;
   day = asInteger( strDay );
   year = asInteger( strYear );

   if ( 0 == year )
      return false;

   // check that date parts are within valid ranges ie. MM >0 <13
   // and DD >0 <32
   if( month < JANUARY ||
       month > DECEMBER || day < 1 || day > 31)
      return false;

   // check date if leap year and Febuary, allows a DD of 29
   if( isLeapYear( year ) && month == FEBRUARY )
   {
      if ( day > 29 )
         return false;
   }
   else
   {
      // check date must have a valid DD and MM combination
      if( day > _nDaysInMonth[ month ] )
         return false;
   }

   return true;
}


//***************************************************************
//
//   NAME: addDays()
//
//  DESCRIPTION:
//      This is a function that will add nOffset (days) to the
//  DDate that is passed to the function.  The function returns
//  the new Date.
//***************************************************************
bool DDate::addDays( const int nDays )
{
   TRACE_METHOD( I_("DDate"),
                 I_("DDate::addDays( const int ) ") );

   if( nDays == 0 )
   {
     return true;
   }

   assert( _nDayOfYear > 0 ); //date value is null; set in a date
                              //before calling this method

   if( _nDayOfYear == 0 )
   {
     return false;
   }


   _nDayOfYear += nDays;

   _getDateFromDayOfYear();

   setUDate();

   return true;
}

//***************************************************************
//
//   NAME: subtractDays()
//
//  DESCRIPTION:
//      This function will subtract nOffset (days) from the date
//  that is passed to the function.  The function returns the new
//  Date.
//***************************************************************
bool DDate::subtractDays( const int nDays )
{
   TRACE_METHOD( I_("DDate"),
                 I_("DDate::subtractDays( const int ) ") );

   if( nDays == 0 )
   {
     return true;
   }

   assert( _nDayOfYear > 0 );//date value is null; set in a date
                             //before calling this method

   if( _nDayOfYear == 0 )
   {
     return false;
   }

   _nDayOfYear -= nDays;

   _getDateFromDayOfYear();

   setUDate();

   return true;
}

//***************************************************************
//
//   NAME: addYears()
//
//  DESCRIPTION:
//      This function will add nOffset (years) to the date that
//  is passed to the function. The function returns the new Date.
//***************************************************************
bool DDate::addYears( const int nYears )
{
   TRACE_METHOD( I_("DDate"),
                 I_("DDate::addYears( const int ) ") );

   if( nYears == 0 )
   {
     return true;
   }

   assert( _nYear > 0 ); // date value is null; set in a date
                         // before calling this method
   if( _nYear == 0 )
   {
     return false;
   }

   _nYear += nYears;

   if( !isLeapYear( _nYear ) )
   {
      if( FEBRUARY == _nMonth )
      {
         if( _nDayOfMonth > _nDaysInMonth[ _nMonth ] )
         {
            _nDayOfMonth = 1;
            _nMonth++;
         }
      }

   }

   _getDayOfYearFromDate();

   setUDate();

   _buildDateFromParts();

   return true;
}

//***************************************************************
//
//   NAME: DDate::formatDate()
//
//  DESCRIPTION:
//      This function will convert the date format to the Date
//  Format passed to the function. Currently this functions will
//  recognize the following formats: DF_MMDDCCYY, DF_FSCCYYMMDD,
//  DF_FSMMDDCCYY, DF_FDCCYYMMDD, DF_FDMMDDCCYY.  The function
//  returns true if successful and False if the date is invalid
//  or if the new format doesn't exist.  This private method is
//  available so that we do not re validate our internaly built
//  dates.
//***************************************************************
bool DDate::formatDate( const DString& strDateIn,
                        DString& strDateOut,
                        DATE_FORMAT dfFormat )
{
   MAKEFRAME( COMPONENT_NAME,
              I_("formatDate( const DString&, " )
              I_( "DString&, DATE_FORMAT )") );

   DATE_FORMAT dfFormatIn = DF_NULL;
   dfFormatIn = DDate::getDateFormat( strDateIn );

   if ( DF_NULL == dfFormatIn )
      return false;

   DString strCentury, strYear, strMonth, strDay;

   extractDateComponents( strDateIn,
                          dfFormatIn,
                          strDay, strMonth, strYear );
   // now create new Date DString using the passed in format.
   switch( dfFormat )
   {
      case DF_MMDDCCYY:
         strDateOut = strMonth;
         strDateOut += strDay;
         strDateOut += strYear;
         break;
      case DF_CCYYMMDD:
         strDateOut = strYear;
         strDateOut += strMonth;
         strDateOut += strDay;
         break;
      case DF_FSCCYYMMDD:
         strDateOut = strYear;
         strDateOut += '/';
         strDateOut += strMonth;
         strDateOut += '/';
         strDateOut += strDay;
         break;
      case DF_FSMMDDCCYY:
         strDateOut = strMonth;
         strDateOut += '/';
         strDateOut += strDay;
         strDateOut += '/';
         strDateOut += strYear;
         break;
      case DF_FDCCYYMMDD:
         strDateOut = strYear;
         strDateOut += '-';
         strDateOut += strMonth;
         strDateOut += '-';
         strDateOut += strDay;
         break;
      case DF_FDMMDDCCYY:
         strDateOut = strMonth;
         strDateOut += '-';
         strDateOut += strDay;
         strDateOut += '-';
         strDateOut += strYear;
         break;
      default:
         return false;
   }

   return true;
}

//***************************************************************
//
//   NAME: DDate::getDateFormat()
//
//  DESCRIPTION:
//      This function will determine the date format of the
//  passed DString.  Currently this functions will recognize the
//  following formats: DF_MMDDCCYY, DF_CCYYMMDD, DF_FSCCYYMMDD,
//  DF_FSMMDDCCYY, DF_FDCCYYMMDD, DF_FDMMDDCCYY.  The function
//  returns the enumerated date format type.
//***************************************************************
DDate::DATE_FORMAT DDate::getDateFormat( const DString& strDate )
{
   TRACE_METHOD( I_( "DDate" ),
                 I_( "getDateFormat( const DString& )" ) );

   DString strBuff;
   int nMonth, nDay, nYear;
   bool bMonth = true;
   bool bDay = true;
   DATE_FORMAT dfFormat = DF_NULL;

   strBuff = strDate;

   // check length of DString
   const int nLength = strDate.length();
   if( nLength != 8 && nLength != 10 )
      return DF_NULL;

   //check for null values
   if( _isNullValue( strDate ) )
      return DF_NULL;

   // Check for '/' seperator in the date DString
   if( strBuff.find( '/' ) == 4 )// is Date Format is CCYY/MM/DD?
   {
      stripAll( strBuff, '/');

      nYear  =  asInteger( strBuff.substr( 0, 4 ) );
      nMonth =  asInteger( strBuff.substr( 4, 2 ) );
      nDay   =  asInteger( strBuff.substr( 6, 2 ) );

      if( nMonth < 1 || nMonth > 12 )
                        bMonth = false;

      if (nDay < 1 || nDay > 31 )
         bDay = false;

      if( bDay || bMonth )          // Date Format is CCYY/MM/DD
         dfFormat = DF_FSCCYYMMDD;
   }

   if( strBuff.find( '/' ) == 2 )   // is Date Format MM/DD/CCYY?
   {
       stripAll( strBuff, '/');

       nMonth =  asInteger( strBuff.substr( 0, 2 ) );
       nDay   =  asInteger( strBuff.substr( 2, 2 ) );
       nYear  =  asInteger( strBuff.substr( 4, 4 ) );

                 if( nMonth < 1 || nMonth > 12 )
          bMonth = false;

       if ( nDay < 1 || nDay > 31 )
          bDay = false;

       if( bDay || bMonth )          // Date Format is MM/DD/CCYY
          dfFormat = DF_FSMMDDCCYY;
   }

   // Check for '-' seperator in the date DString
   if( strBuff.find( '-' ) == 4 )   // is Date Format CCYY-MM-DD?
   {
      stripAll( strBuff, '-');

      nYear  = asInteger( strBuff.substr( 0, 4 ) );
      nMonth = asInteger( strBuff.substr( 4, 2 ) );
      nDay   = asInteger( strBuff.substr( 6, 2 ) );

      if( nMonth < 1 || nMonth > 12 )
         bMonth = false;

      if ( nDay < 1 || nDay > 31 )
         bDay = false;

      if( bDay || bMonth )           // Date Format is CCYY-MM-DD
         dfFormat = DF_FDCCYYMMDD;
   }

   if( strBuff.find( '-' ) == 2 )   // is Date Format MM-DD-CCYY?
   {
      stripAll( strBuff, '-');

      nMonth = asInteger( strBuff.substr( 0, 2 ) );
      nDay   = asInteger( strBuff.substr( 4, 2 ) );
      nYear  = asInteger( strBuff.substr( 4, 4 ) );

      if( nMonth < 1 || nMonth > 12 )
         bMonth = false;

      if ( nDay < 1 || nDay > 31 )
         bDay = false;

      if( bDay || bMonth )        // Date Format is MM-DD-CCYY
         dfFormat = DF_FDMMDDCCYY;
        }

   // No '/' or '-' assumming MMDDCCYY
   //If no dashes or slashes are found then the date DString must
   // be 8 characters long
   if( strDate.find( '/' ) == DString::npos )
   {
      if( strDate.find( '-' ) == DString::npos )
      {
         // check length of DString
         assert( nLength == 8 );
         if( nLength < 8 || nLength > 8 )
            return DF_NULL;

         // Get two bytes starting at the 0 offset in the DString
         int nMMtest = asInteger( strBuff.substr( 0, 2 ) );
         if( nMMtest > 12 )
         {

            // figure out if the format is DF_CCYYMMDD or the
            // default DF_MMDDCCYY
            // Get two bytes starting at the 4th position in the
            // DString
            nMMtest = asInteger( strBuff.substr( 4, 2 ) );
            if( nMMtest > 12 )
            {
               dfFormat = DF_MMDDCCYY;
               nMonth = asInteger( strBuff.substr( 0, 2 ) );
               nDay   = asInteger( strBuff.substr( 2, 2 ) );
               nYear  = asInteger( strBuff.substr( 4, 4 ) );

            }
            else
            {
               dfFormat = DF_CCYYMMDD;
               nYear  = asInteger( strBuff.substr( 0, 4 ) );
               nMonth = asInteger( strBuff.substr( 4, 2 ) );
               nDay   = asInteger( strBuff.substr( 6, 2 ) );
            }
         }
         else
         {
            //default
            dfFormat = DF_MMDDCCYY;
            nMonth = asInteger( strBuff.substr( 0, 2 ) );
            nDay   = asInteger( strBuff.substr( 2, 2 ) );
            nYear  = asInteger( strBuff.substr( 4, 4 ) );
         }

         if( nMonth < 1 || nMonth > 12 || nDay < 1 || nDay > 31)
            dfFormat = DF_NULL;

      }
   }

   return dfFormat;

}

//***************************************************************
//
//   NAME: DDate::isDayInMonth()
//
//  DESCRIPTION:
//      This function will answere the question "Is this a
//  reasonable day for the specified month?"
//
//***************************************************************
bool DDate::isDayInMonth( const int nDayIn, const int nMonthIn )
{
   TRACE_METHOD( I_("DDate"),
                 I_("getDayOfYear ( void ) const") );

   if( nDayIn <= 0 || nMonthIn < 0 )
   {
      return false;
   }

   if( FEBRUARY == nMonthIn && nDayIn < 30 )
   {
      return true;
   }
   else
   {
      if( nDayIn > _nDaysInMonth[ nMonthIn ] )
         return false;
   }

   return true;

}

//***************************************************************
//
//   NAME: DDate::getWeekDay()
//
//  DESCRIPTION:
//     This function will return the day of the Week as a
//  zero based integer
//
//***************************************************************

int DDate::getWeekDay( const long lDateOffset )
{
   TRACE_METHOD( I_("DDate"), I_("getWeekDay( const long )") );

   int nWeekDay = 0;
   if( lDateOffset >= 0L )
   {
       // Positive Offset -- Calculate the day of the week
      nWeekDay = labs( ( lDateOffset % 7L ) );
   }
   else
   {
      // Negative Offset -- Calculate the day of the week
      nWeekDay = 6L - ( ( labs( lDateOffset ) % 7L ) );
   }

   return nWeekDay;
}

//***************************************************************
//
//   NAME: DDate::getDateFromOffset()
//
//  DESCRIPTION:
//
//***************************************************************

void DDate::getDateFromOffset( const long lDateOffset,
                               DString& strDateOut )
{
   TRACE_METHOD( I_("DDate"),
                 I_("getDateFromOffset( const long lDateOffset" )
                 I_( ", DString& strDateOut )") );

   int nMonth, nDay, nYear;

   _getDatePartsFromOffset( lDateOffset, nDay, nMonth, nYear );

   // Now the date is contained in sYear, sMonth, and sDay, place
   // it back into a DString
   DString strMonth = asString( nMonth + 1 );
   DString strDay( asString( nDay ) );
   DString strYear( asString( nYear ) );

   strDateOut =  padLeft( strMonth, 2, '0' );
   strDateOut += padLeft( strDay,  2, '0' );
   strDateOut += padLeft( strYear, 4, '0' );
}

//***************************************************************
//
//   NAME: DDate::getDatePartsFromOffset()
//
//  DESCRIPTION:
//
//***************************************************************
void DDate::_getDatePartsFromOffset( const long lDateOffset,
                                     int & nDay,
                                     int & nMonth,
                                     int & nYear )
{
   TRACE_METHOD( I_("DDate"),
                 I_("getDatePartsFromOffset( const long" )
        I_( " lDateOffset, int nDay, int nMonth, int nYear )") );

   nMonth = JANUARY;

   // split the date code back into year, month, and day
   long lOffset = lDateOffset + 1;

   if( lOffset >= 0L )
   {
      // Positive Offset -- Calculate the day of the week

      // nWeekDay = abs( ( lOffset % 7L ) );
      for( nYear = _nBaseYear; lOffset > 364L; ++nYear )
      {
         lOffset -= 365L;   // Days in one year
         if( DDate::isLeapYear( nYear )  )
         {
            --lOffset; // one more day for leap year

            // 12/31 of a leap year, readjust and break out of
            // for loop
            if ( lOffset < 0L )
            {
               lOffset += 366L;
               break;
            }
         }
      }   // end of the for loop
   }
   else
   {
      // Negative Offset -- Calculate the day of the week

      // nWeekDay = 6 - ( ( labs( lOffset ) % 7L ) );

      for( nYear = _nBaseYear; lOffset < 0L; )
      {
         lOffset += 365L;  // days in one year

         --nYear;

         // check year we are skipping
         if ( DDate::isLeapYear( nYear ) )
             ++lOffset;     // add one more for the leap year

      }
   }

   if( DDate::isLeapYear( nYear ) )  // check for Leap Year
   {
      if ( 60L == lOffset )
         nMonth = FEBRUARY;
      else
      {
         if ( lOffset > 60L ) // take Feb. 29 into account
            --lOffset;

         // Search for the month we want
         while( _lStartOfMonthOffsets[ nMonth ] <= lOffset &&
                DECEMBER >= nMonth )
         {
            ++nMonth;
         }
         --nMonth;
      }
   }
   else
   {
      // Search for the month we want
      while( _lStartOfMonthOffsets[ nMonth ] <= lOffset &&
             DECEMBER >= nMonth )
      {
         ++nMonth;
      }
      --nMonth;
   }


   // where in month -- 1 based
   nDay = ( lOffset - _lStartOfMonthOffsets[ nMonth ] );
   if ( 0 == nDay )
   {
      --nMonth;
      if ( JANUARY > nMonth )
      {
         nMonth = DECEMBER;
         --nYear;
      }
      nDay = _nDaysInMonth[ nMonth ];
   }

   return;  // return the day of the week
}

//***************************************************************
//
//   NAME: DDate::getOffsetFromDate()
//
//  DESCRIPTION:
//
//***************************************************************
long DDate::getOffsetFromDate( const DString& strDate )
{
   MAKEFRAME( COMPONENT_NAME,
              I_("getOffsetFromDate( const DString& )") );

   DDate diDate;
   long lDateOffset = 0L;
   int    nMonth, nDay, nYear;
   DString strMonth, strDay, strYear;

   DDate::DATE_FORMAT dfFormat = DDate::DF_NULL;
   dfFormat = DDate::getDateFormat( strDate );

   if( DDate::DF_NULL == dfFormat )
   {
      return 0L;
   }

   // Break down the date passed in.
   switch( dfFormat )
   {
      case DDate::DF_MMDDCCYY:
         strMonth   = strDate.substr( 0, 2 );
         strDay     = strDate.substr( 2, 2 );
         strYear    = strDate.substr( 4, 4 );
         break;
      case DDate::DF_CCYYMMDD:
         strYear    = strDate.substr( 0, 4 );
         strMonth   = strDate.substr( 4, 2 );
         strDay     = strDate.substr( 6, 2 );
         break;
      case DDate::DF_FSCCYYMMDD:
         strYear    = strDate.substr( 0, 4 );
         strMonth   = strDate.substr( 5, 2 );
         strDay     = strDate.substr( 8, 2 );
                        break;
      case DDate::DF_FSMMDDCCYY:
         strMonth   = strDate.substr( 0, 2 );
         strDay     = strDate.substr( 3, 2 );
         strYear    = strDate.substr( 6, 4 );
         break;
      case DDate::DF_FDCCYYMMDD:
         strYear    = strDate.substr( 0, 4 );
         strMonth   = strDate.substr( 5, 2 );
         strDay     = strDate.substr( 8, 2 );
         break;
      case DDate::DF_FDMMDDCCYY:
         strMonth   = strDate.substr( 0, 2 );
         strDay     = strDate.substr( 3, 2 );
         strYear    = strDate.substr( 6, 4 );
                        break;
      default://DF_MMDDCCYY
         strMonth   = strDate.substr( 0, 2 );
         strDay     = strDate.substr( 2, 2 );
         strYear    = strDate.substr( 4, 4 );
         break;
   }

   // Get the month
   nMonth = asInteger( strMonth );
   --nMonth;

   // Get the day
   nDay = asInteger( strDay );

   // Get the year
   nYear = asInteger( strYear );

//      lDateOffset = 0L;

   if ( nYear >= _nBaseYear )
   {
       // Positive offset
      for ( int i = _nBaseYear; i < nYear; ++i )
      {
           // Add number of days in a year
         lDateOffset += 365L;
            // Add in leap days
         if ( diDate.isLeapYear( i ) )
             ++lDateOffset;
           }
   }
   else
   {
      for ( int i = _nBaseYear; i > nYear; --i )
      {
           // Subtract number of days in a year
         lDateOffset -= 365L;
            // Subtract leap days
         if ( diDate.isLeapYear( i ) )
              --lDateOffset;
      }
   }

    /****************************************************/
    /**  We are offset to Jan 1st of the target year.  **/
    /**  Now we need to offset to the actual day in    **/
    /**  the year.                                     **/
    /**  Note: The month and day are 1-based, but we   **/
    /**        need to be 0-based for offsetting.      **/
    /****************************************************/

    // Add in the days to the first of the month
   lDateOffset += _lStartOfMonthOffsets[ nMonth ];

    // Add in the day of the month
   lDateOffset += nDay;

    // Check for past Feb 29 in leap year
   if ( diDate.isLeapYear( nYear ) &&
        nMonth > FEBRUARY )
      ++lDateOffset;

   // Return the date's offset
   return lDateOffset - 1;

}

//***************************************************************
//
//   NAME: isValidDate( const DString& strDate )
//
//  DESCRIPTION:
// This function will determine if the date passed to the member
// is a valid date. This method will use an instance of DDate to
// aid in validating the passed in date.
//The function returns true if the date is valid.
//***************************************************************
bool DDate::isValidDate( void ) const
{
   TRACE_METHOD( I_("DDate"), I_("isValidDate( void ) const") );

   return isValidDate( _strDate );
}


bool DDate::operator>( const DDate & right ) const
{
   return ( getUDate() > right.getUDate() );
}


bool DDate::operator<( const DDate & right ) const
{
   return ( getUDate() < right.getUDate() );
}


bool DDate::operator==( const DDate & right ) const
{
   return ( getUDate() == right.getUDate() );
}


// ############## Old DDate private methods #####################
// ##############################################################

//***************************************************************
//
//   NAME: DDate::isNullValue()
//
//  DESCRIPTION:
//    This function will answer the question "Is this value
//  NULL according to the following criteria?"
//
//                1. value is empty DString(i.e. all spaces) " "
//                2. value is a null DString ""
//                3. value is zero( i.e. all zeroes ) 0
//
//***************************************************************
bool DDate::_isNullValue( const DString& strDate )
{
   TRACE_METHOD( I_("DDate"),
                 I_("_isNullValue ( const DString& )") );

   //Check the values for null or spaces or all zeros
   if ( stringHasOnly( strDate, I_(" ") ) ||
        strDate == I_("") ||
        stringHasOnly( strDate, I_("0") )  )
   {
      return true;
   }

   return false;
}



void DDate::_splitDateToParts( void )
{
   TRACE_METHOD( I_("DDate"), I_("_splitDateToParts ( void )") );

   DString strMonth, strDay, strYear;

   // Break down the date passed in.
   switch( _dfFormat )
   {
      case DF_MMDDCCYY:
         strMonth   = _strDate.substr( 0, 2 );
         strDay     = _strDate.substr( 2, 2 );
         strYear    = _strDate.substr( 4, 4 );
         break;
      case DF_CCYYMMDD:
         strYear    = _strDate.substr( 0, 4 );
         strMonth   = _strDate.substr( 4, 2 );
         strDay     = _strDate.substr( 6, 2 );
         break;
      case DF_FSCCYYMMDD:
         strYear    = _strDate.substr( 0, 4 );
         strMonth   = _strDate.substr( 5, 2 );
         strDay     = _strDate.substr( 8, 2 );
                        break;
      case DF_FSMMDDCCYY:
         strMonth   = _strDate.substr( 0, 2 );
         strDay     = _strDate.substr( 3, 2 );
         strYear    = _strDate.substr( 6, 4 );
         break;
      case DF_FDCCYYMMDD:
         strYear    = _strDate.substr( 0, 4 );
         strMonth   = _strDate.substr( 5, 2 );
         strDay     = _strDate.substr( 8, 2 );
         break;
      case DF_FDMMDDCCYY:
         strMonth   = _strDate.substr( 0, 2 );
         strDay     = _strDate.substr( 3, 2 );
         strYear    = _strDate.substr( 6, 4 );
                        break;
      default:
         //our current design philosophy is to let the invalid
         //value go with no exceptions being thrown
         break;
   }

   // Get the month
   _nMonth = asInteger( strMonth ) - 1;

   // Get the day
   _nDayOfMonth = asInteger( strDay );

   // Get the year
   _nYear = asInteger( strYear );

   //Get day of the year
   _getDayOfYearFromDate();
}


void DDate::_buildDateFromParts( void )
{
   TRACE_METHOD( I_("DDate"),
                 I_("_buildDateFromParts ( void )") );

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

}

//***************************************************************
//
//   NAME: DDate::_getDateFromDayOfYear()
//
//  DESCRIPTION:
//     This function will retrieve the day of year from the DDate
//  class.  The day range is 1 to 365(366 for leap year).
//
//***************************************************************
void DDate::_getDateFromDayOfYear( void )
{
   TRACE_METHOD( I_("DDate"),
                 I_("_getDateFromDayOfYear( void ) const") );

   DDate DDate( _strDate );
   int nYear = DDate.getYear();
   int inc = 1;
   while ( 0 >= _nDayOfYear )
   {
      --_nYear;
      _nDayOfYear += 365 + ( isLeapYear( _nYear ) ? 1 : 0 );
   }

   //calculate year

   int nYearCount = 0;
   bool fLeap;
   while ( _nDayOfYear > ( 365 +
           ( ( fLeap = isLeapYear( _nYear + nYearCount ) ) ?
             1 : 0 ) ) )
   {
      if ( inc != -1 )
      {
         if ( fLeap && 367 <= _nDayOfYear )
            --_nDayOfYear;//subtract one more for leap year
      }
      else
      {
         if ( isLeapYear( _nYear + nYearCount - 1 ) )
            --_nDayOfYear;
      }
      _nDayOfYear -= 365;
      nYearCount += inc;
   }

    _nYear += nYearCount;

   // Check for leap year
   bool fLeapYear = isLeapYear( _nYear );
   int days;
   if ( -1 == inc )
   {
      if ( 0 == _nDayOfYear )
         _nDayOfYear = 365 +
                       ( ( fLeapYear = isLeapYear( --_nYear ) ) ?
                         1 : 0 );
      else
         _nDayOfYear = ( 365 + ( ( fLeapYear ) ? 1 : 0 ) ) -
                       _nDayOfYear;
   }

   int offset = _nDayOfYear;
   _nMonth = JANUARY;

   while ( ( days = ( _nDaysInMonth[ _nMonth ] +
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
}


//***************************************************************
//
//   NAME: DDate::_getDayOfYearFromDate()
//
//  DESCRIPTION:
//     This function will retrieve the day of year from the DDate
//  class.  The day range is 1 to 365(366 for leap year).
//
//***************************************************************
void DDate::_getDayOfYearFromDate( void )
{
   TRACE_METHOD( I_("DDate"),
                 I_("_getDayOfYearFromDate ( void ) const") );

   _nDayOfYear = 0;

   //Calculate day of year
   for( int i = JANUARY; i < _nMonth; i++ )
   {
      if( FEBRUARY == i )
      {
         if( isLeapYear( _nYear ) )
         {
            _nDayOfYear += 29;//February in a Leap Year
         }
         else
         {
            _nDayOfYear += _nDaysInMonth[ i ];
         }
      }
      else
      {
         _nDayOfYear += _nDaysInMonth[ i ];
      }
   }

   _nDayOfYear += _nDayOfMonth;

}


void DDate::extractDateComponents( const DString & strDate,
                                   DATE_FORMAT format,
                                   DString & day,
                                   DString & month,
                                   DString & year )
{
   switch( format )
   {
      case DF_MMDDCCYY:
         month   = strDate.substr( 0, 2 );
         day     = strDate.substr( 2, 2 );
         year    = strDate.substr( 4, 4 );
         break;
      case DF_CCYYMMDD:
         year    = strDate.substr( 0, 4 );
         month   = strDate.substr( 4, 2 );
         day     = strDate.substr( 6, 2 );
         break;
      case DF_FSCCYYMMDD:
         year    = strDate.substr( 0, 4 );
         month   = strDate.substr( 5, 2 );
         day     = strDate.substr( 8, 2 );
         break;
      case DF_FSMMDDCCYY:
         month   = strDate.substr( 0, 2 );
         day     = strDate.substr( 3, 2 );
         year    = strDate.substr( 6, 4 );
         break;
      case DF_FDCCYYMMDD:
         year    = strDate.substr( 0, 4 );
         month   = strDate.substr( 5, 2 );
         day     = strDate.substr( 8, 2 );
         break;
      case DF_FDMMDDCCYY:
         month   = strDate.substr( 0, 2 );
         day     = strDate.substr( 3, 2 );
         year    = strDate.substr( 6, 4 );
         break;
      default:
         break;
   }
}


void DDate::setTime( DIINT64 lTime )
{
   UErrorCode code = U_ZERO_ERROR;
   UnicodeString pattern( "MM/dd/yyyy" );
   SimpleDateFormat dfmt( pattern, code );
   UnicodeString myString; 
   dfmt.format( (UDate)lTime, myString );  

   DString ddateFormat;
   ICUStringtoIString( myString, ddateFormat.getImp() );
   set( ddateFormat );
}  



// ***************** protected Methods *********************//

void DDate::setUDate( void )
{
   UErrorCode code = U_ZERO_ERROR;
   Calendar * calendar = Calendar::createInstance( code );
   calendar->clear();

   calendar->set( _nYear, _nMonth, _nDayOfMonth );
   _nDayOfYear = calendar->get( UCAL_DAY_OF_YEAR, code );
   JavaDate::setTime( (long long)calendar->getTime( code ) );
   delete calendar;
}


void DDate::set( DIINT64 ltime )
{
   I_CHAR * buf = new I_CHAR[ 11 ];
   UErrorCode code = U_ZERO_ERROR;
   Calendar * calendar = Calendar::createInstance( code );

   calendar->setTime( (UDate)ltime, code );
   _nDayOfYear = calendar->get( UCAL_DAY_OF_YEAR, code );
   _nMonth = calendar->get( UCAL_MONTH, code );
   _nDayOfMonth = calendar->get( UCAL_DATE, code );
   _nYear = calendar->get( UCAL_YEAR, code );
   setTime( ltime );
   i_sprintf( buf,
              I_( "%02.2d/%02.2d/%04.4d" ),
              _nMonth + 1,
              _nDayOfMonth,
              _nYear );
   _strDate = buf;
   delete [] buf;
   delete calendar;
}


void DDate::set( const DString & date )
{
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
// $Log:   Y:/VCS/iFastAWD/dicore/ddate.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:34   kovacsro
// Initial revision.
// 
//    Rev 1.40   23 Apr 2001 10:44:06   dt14177
// fixed subtractDays() when number is 31
// 
//    Rev 1.39   20 Mar 2001 16:39:08   DT14177
// fixed DDate == compare problem when
// an empty string is used to initialize a DDate
// 
//    Rev 1.38   Dec 12 2000 10:13:42   dt21858
// Removed the include to dicbocore.h -- should not include
// headers from DLLs that depend on DICORE.
//
//    Rev 1.37   11 Dec 2000 12:09:38   dt14177
// made the ddate comparison operators
// const and JavaDate::getUDate() const
//
//    Rev 1.36   Aug 31 2000 17:11:50   DT14177
// With null stringin and dash or slash format out,
// "//" or "--" was being put in stringout
//
//    Rev 1.35   Aug 25 2000 10:42:18   DT14177
// cleanup
//
//    Rev 1.34   Aug 24 2000 10:14:36   DT14177
// changed setTime() to use SimpleDateFormat
//
//    Rev 1.33   Aug 18 2000 17:32:16   DT14177
// fixed offset off by one problem which showed up in getWeekDay()
//
//    Rev 1.32   Jul 31 2000 13:13:24   DT14177
// fixed the checkin
//
//    Rev 1.30   Jul 14 2000 10:31:44   DT14177
// getDatePartsFromOffset interface changes
//
//    Rev 1.29   Jul 10 2000 14:55:18   DT14177
// fixed a 12-31-1967 problem with getDatePartsFromOffset()
//
//    Rev 1.27   Jun 30 2000 16:51:08   DT14177
// fixed formatDate for 3 formats - appending problem
//
//    Rev 1.26   Jun 27 2000 17:01:58   DT14177
// moved some date member variables from JavaDate to DDate
//
//    Rev 1.25   Jun 16 2000 11:21:40   DT14177
// fixed isValidDate(); some cleanup
//
//    Rev 1.24   Jun 15 2000 09:49:02   DT14177
// fixed leap day stuff in getDateFromOffset and
// getDatePartsFromOffset; fixed isValidDate where
// it was returning true for "--------" (8 dashes or slashes)
//
//    Rev 1.23   Jun 14 2000 09:46:00   DT14177
// fixed dash formatting (e.g., "MM-DD-CCYY")
//
//    Rev 1.22   Jun 13 2000 15:22:42   DT14177
// fixed addYears
//
//    Rev 1.21   Jun 13 2000 13:15:32   DT14177
// fixed: addDays(), subtractDays(), getDayOfYearFromDate().
// added conditional operators
//
//    Rev 1.19   May 23 2000 17:02:14   DT14177
// fixed setDate to accept all formats
//
//    Rev 1.18   May 12 2000 16:07:56   DT14177
// fixed a memory leak in getCurrentDateAsString
//
//    Rev 1.17   May 11 2000 16:41:16   DT14177
// fixed subtractDays
//
//    Rev 1.16   May 11 2000 08:24:54   DT14177
// lots of fixes for DDate
//
//    Rev 1.15   May 10 2000 17:23:42   DT14177
// Fixed leap year bug
//
//    Rev 1.14   Apr 10 2000 17:07:28   dtwk
// Changes in header files broke ddate.cpp
//
//    Rev 1.13   Jan 31 2000 11:01:36   DT29758
// edit method compareHostGregorianDates
// to correctly addreess Hostmaks
//
//    Rev 1.12   26 Jan 2000 19:48:40   dt20842
// Changes for module namespace
//
//    Rev 1.11   Dec 01 1999 08:49:44   DT29758
// minor code cleanup
//
//    Rev 1.10   Nov 29 1999 16:08:56   DT29758
// added throws to compareHostGregorianDates
// method
//
//    Rev 1.9   Nov 19 1999 14:53:42   DT29758
// added method compareHostGregorianDates
//
//
//    Rev 1.8   Nov 12 1999 08:02:18   DT29758
// Merged with 1.7 DDate class for retrofit
//
//    Rev 1.7   Sep 16 1999 16:28:06   DT14177
// memory leak cleanup
//
//    Rev 1.6   Jul 22 1999 11:39:32   DMUM
// Condition re-work
//
//    Rev 1.4   Jul 16 1999 11:26:28   DT14177
// Added getOffset() to DDate and minus() to JavaDate
//
//    Rev 1.3   Jul 13 1999 18:01:12   dtwk
// Change so that I18N_ registry entries do not have spaces:
// enUS- D becomes enUS-D
//
//    Rev 1.2   Jun 18 1999 12:34:56   DT14177
// Added code to get the Date format string from the registry.
//
//    Rev 1.1   Jun 14 1999 12:18:36   DT14177
// Added revision control blocks.
//
