//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial
//    are proprietary in nature and as such are confidential.
//    Any unauthorised use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 International Financial Data Services Ltd.
//
//******************************************************************************
//
// ^FILE   : bfdate.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : May 2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : bfdate
//    Provides commonly used static and non static helper function for date
//    handling, including formatting.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "bfdate.hpp"
#include <configmanager.hpp>
#include <srcprag.h>
#include <xutility>
#include <assert.h>
#include <limits>
#include "clientlocalecontext.hpp"

// Implement BFDate here for now
const int BFDate::secondsPerMinute = 60;
const int BFDate::secondsPerHour = 60 * secondsPerMinute;
const int BFDate::secondsPerDay = 24 * secondsPerHour;

// how many days are there per 400 years?  The question really is
// how many leap years there are.  Simply, there are (400 / 4) -
// (400 / 100 ) + ( 400 / 400 ) = 79
const int BFDate::daysPer400Years = 365 * 400 + 97;       // 146097
const int BFDate::daysPer100Years = 365 * 100 + 24;       // 36524
const int BFDate::daysPer4Years   = 365 * 4 + 1;            // 1461
const int BFDate::daysPerYear     = 365;

static long aMonthDays[2][12] =
{
   31,28,31,30,31,30,31,31,30,31,30,31,
   31,29,31,30,31,30,31,31,30,31,30,31
};
static long aDayYear[2][13] =
{
   0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365,
   0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366
};

//*****************************************************************************
BFDate::BFDate()
: days_( 0 )
{
}

BFDate::BFDate( const SYSTEMTIME& st )
: days_( 0 )
{
   set( st );
}


// temporary ctor ... assume that only date formats supported are mdy and ymd
BFDate::BFDate( const I_CHAR* pszDate, DATE_FORMAT eFormat )
: days_( 0 )
{
   set( pszDate, eFormat );
}

BFDate::BFDate( const DString& dstrDate, DATE_FORMAT eFormat )
: days_( 0 )
{
   set( dstrDate.c_str(), eFormat );
}

//*****************************************************************************
BFDate::BFDate( int iDay, int iMonth, int iYear )
:days_( 0 )
{
   SYSTEMTIME st;
   st.wYear = iYear;
   st.wMonth = iMonth;
   st.wDay = iDay;

   if( isValidDate( st ) )
   {
      set( st );
   }
   else
   {
      throw BFDateInvalidException();
   }
}

//*****************************************************************************
BFDate::~BFDate()
{
}

//*****************************************************************************
BFDate::BFDate( const BFDate& rhs )
: days_( rhs.days_ )
{
}

//*****************************************************************************
BFDate& BFDate::operator=( const BFDate& rhs )
{
   if( this != &rhs )
   {
      days_ = rhs.days_;
   }

   return(*this);
}

//*****************************************************************************
bool BFDate::operator>( const BFDate& rhs ) const
{
   if( rhs == highDate() ) // we can never be greater than the high date
   {
      return( false );
   }
   else if( (*this) == highDate() ) // if we are the high date then we are greater than everything else (except the high date!)
   {
      return( true );
   }
   return( days_ > rhs.days_ );
}

//*****************************************************************************
bool BFDate::operator<( const BFDate& rhs ) const
{
   if( rhs == lowDate() )  // we can never be less than the low date
   {
      return( false );
   } 
   else if( (*this) == lowDate() )  // if we are the low date then we are less than everything else (except the low date!)
   {
      return( true );
   }
   return( days_ < rhs.days_ );
}

//*****************************************************************************
bool BFDate::operator==( const BFDate& rhs ) const
{
   return( days_ == rhs.days_ );
}

DString BFDate::get( DATE_FORMAT eFormat ) const
{
   assert( eFormat > DF_NULL && eFormat < DF_ANYVALIDFORMAT );
   if( days_ == 0 )
   {
      throw BFDateInvalidException();
   }
   if( eFormat <= DF_NULL || eFormat >= DF_ANYVALIDFORMAT )
   {
      throw BFDateInvalidFormatException();
   }
   DString dateStr;
   if( formatDate( eFormat, dateStr ) == true )
   {
      return( dateStr );
   }
   throw BFDateException();
}

DString BFDate::get( const DString& dstrMask ) const
{
   DString dstrDate = dstrMask;

   SYSTEMTIME st;
   cvtToSysTime( days_, st );

   // find the components of the mask ...
   int cb = dstrDate.size();
   int iMonth = 10;
   int iYear = 1000;
   int iDay = 10;
   int iMask;
   for( iMask = 0; iMask < cb; ++iMask )
   {
      switch( dstrDate[ iMask ] )
      {
         case I_( 'M' ):
         case I_( 'm' ):
            dstrDate[ iMask ] = st.wMonth % iMonth;
            iMonth /= 10;
            break;
         case I_( 'D' ):
         case I_( 'd' ):
            dstrDate[ iMask ] = st.wDay % iDay;
            iDay /= 10;
            break;
         case I_( 'Y' ):
         case I_( 'y' ):
            dstrDate[ iMask ] = st.wYear % iYear;
            iYear /= 10;
            break;
      }
   }
   return( dstrDate );
}

bool BFDate::set( const SYSTEMTIME& st )
{
   if( isValidDate( st ) )
   {
      days_ = cvtFromSysTime( st );
      return( true );
   }
   return( false );
}

bool BFDate::set( int iDay, int iMonth, int iYear )
{
   if( !isValidDate( iDay, iMonth, iYear ) )
   {
      return( false );
//CP20021121      throw BFDateInvalidException();
   }
   SYSTEMTIME st;
   st.wYear = iYear;
   st.wMonth = iMonth;
   st.wDay = iDay;
   days_ = cvtFromSysTime( st );
   return( true );
}

bool BFDate::set( const DString& dstrDate, DATE_FORMAT eFormat )
{
   return( set( dstrDate.c_str(), eFormat ) );
}

bool BFDate::set( const I_CHAR* pszDate, DATE_FORMAT eFormat )
{
   SYSTEMTIME st;
   int iDay = 0, iMonth = 0, iYear = 0;
   if( extractDateComponents( pszDate, eFormat, st ) && isValidDate( st ) )
   {
      set( st );
   }
   else
   {
      days_ = 0;
      return( false );
   }
   return( true );
}

void BFDate::cvtToSysTime( long days, SYSTEMTIME& st )
{
   long day = days;
   // determine the date based on the number of days since 01Jan0001
   long year = day / daysPer400Years * 400;
   day -= ( day / daysPer400Years ) * daysPer400Years;
   if( day == 0 )
   {
      day = 366;  // it's December 31st
      --year;
   }
   else
   {
      year += day / daysPer100Years * 100;
      day -= ( day / daysPer100Years ) * daysPer100Years;
      if( day == 0 )
      {
         day = 365;  // it's December 30th
         --year;
      }
      else
      {
         year += day / daysPer4Years * 4;
         day -= ( day / daysPer4Years ) * daysPer4Years;
         if( day == 0 )
         {
            day = 366;  // it's December 31st
            --year;
         }
         else
         {
            year += day / daysPerYear;
            day -= ( day / daysPerYear ) * daysPerYear;
            if( day == 0 )
            {
               day = 365;     // it's December 30th!
               --year;
            }
         }
      }
   }

   ++year;

   int iIsLeapYear = ( year % 4 == 0 ) && ( year % 100 != 0 || year % 400 == 0 );

   int iMonth = 0;
   for( iMonth = 0;
      day > aMonthDays[iIsLeapYear][iMonth];
      day -= aMonthDays[iIsLeapYear][iMonth], ++iMonth );

#pragma warning( push )
#pragma warning( disable: 4244 )
   st.wYear = year;
   st.wMonth = iMonth + 1;
   st.wDay = day;
#pragma warning( pop )
   st.wHour = 0;
   st.wMinute = 0;
   st.wSecond = 0;
   st.wMilliseconds = 0;
   st.wDayOfWeek = -1;
}

bool BFDate::addDays( long cDays )
{
   *this += cDays;
   return( true );
}

bool BFDate::addMonths( long cMonths )
{
   SYSTEMTIME st;
   cvtToSysTime( days_, st );
   long wMonth = st.wMonth + cMonths;
   long wYear = st.wYear;
   while( wMonth < 1 )
   {
      wMonth+=12; wYear--;
   }
   while( wMonth > 12 )
   {
      wMonth-=12; wYear++;
   }
#pragma warning( push )
#pragma warning( disable:4244 )
   st.wMonth = wMonth;
#pragma warning( pop )
   if( wYear < 1 || wYear > 9999 )
   {
      throw BFDateInvalidException();
   }
#pragma warning( push )
#pragma warning( disable:4244 )
   st.wYear = wYear;
#pragma warning( pop )

   // now adjust day-of-month to reflect new month/year
   int iLeapYear = isLeapYear( st.wYear );
   if( aMonthDays[ iLeapYear ][ st.wMonth - 1 ] < st.wDay )
   {
#pragma warning( push )
#pragma warning( disable:4244 )
      st.wDay = aMonthDays[ iLeapYear ][ st.wMonth - 1 ];
#pragma warning( pop )
   }
   days_ = cvtFromSysTime( st );
   return( true );
}

bool BFDate::addYears( long cYears )
{
   SYSTEMTIME st;
   cvtToSysTime( days_, st );
   long wYear = st.wYear + cYears;
   if( wYear < 1 || wYear > 9999 )
   {
      throw BFDateInvalidException();
   }
#pragma warning( push )
#pragma warning( disable:4244 )
   st.wYear = wYear;
#pragma warning( pop )

   // now adjust day-of-month to reflect new year
   int iLeapYear = isLeapYear( st.wYear );
   if( aMonthDays[ iLeapYear ][ st.wMonth - 1 ] < st.wDay )
   {
#pragma warning( push )
#pragma warning( disable:4244 )
      st.wDay = aMonthDays[ iLeapYear ][ st.wMonth - 1 ];
#pragma warning( pop )
   }
   days_ = cvtFromSysTime( st );
   return( true );
}

//******************************************************************************
long BFDate::cvtFromSysTime( const SYSTEMTIME& st )
{
   // convert the systemtime to the number of days which have elapsed
   // since 01Jan0001
   int iIsLeapYear = ( st.wYear % 4 == 0 )
                     && ( st.wYear % 100 != 0 || st.wYear % 400 == 0 );

   long y = st.wYear - 1;
   long d = y * 365           // 365 days per year
            + ( y / 4 )         // plus one for each leap year
            - ( y / 100 )       // no leap year on century
            + ( y / 400 );      // unless divisible by 400 also

   // add days for current month
   int iMonth = 0;
   d += aDayYear[iIsLeapYear][ st.wMonth - 1 ];
   d += st.wDay;

   return( d );
}

//*****************************************************************************
int BFDate::getDay() const
{
   SYSTEMTIME st;
   cvtToSysTime( days_, st );
   return( st.wDay );
}

//*****************************************************************************
int BFDate::getMonth() const
{
   SYSTEMTIME st;
   cvtToSysTime( days_, st );
   return( st.wMonth );
}

//*****************************************************************************
int BFDate::getYear() const
{
   SYSTEMTIME st;
   cvtToSysTime( days_, st );
   return( st.wYear );
}

//*****************************************************************************
int BFDate::getWeekDay() const
{
   return( days_ % 7 );
}

//***************************************************************
bool BFDate::isValidDate( const DString& dstrDate, DATE_FORMAT eFormat )
{
   try
   {
      SYSTEMTIME st;
      if( extractDateComponents( dstrDate.c_str(), eFormat, st ) )
      {
         return( isValidDate( st ) );
      }

   }
   catch( BFDateInvalidException& )
   {
      return( false );
   }
   return( false );
}

//***************************************************************
bool BFDate::isValidDate( const SYSTEMTIME& st )
{
   return( isValidDate( st.wDay, st.wMonth, st.wYear ) );
}

//***************************************************************
bool BFDate::isValidDate( int iDay,
                          int iMonth,
                          int iYear )
{
   if( isValidYear( iYear ) &&
       isValidMonth( iMonth ) &&
       isValidDay( iDay, iMonth, iYear ) )
   {
      return( true );
   }
   return( false );
}

//***************************************************************
bool BFDate::isValidYear( int iYear )
{
   return( true );
}

//***************************************************************
bool BFDate::isValidMonth( int iMonthIn )
{
   if( 0 < iMonthIn && 13 > iMonthIn )
   {
      return(true);
   }
   else
      return(false);
}

//***************************************************************
bool BFDate::isValidDay( int iDayIn, int iMonthIn, int iYearIn )
{
   if( iDayIn < 1 || iMonthIn < 1 )
   {
      return(false);
   }

   if( aMonthDays[ isLeapYear( iYearIn )][iMonthIn - 1] >= iDayIn )
   {
      return( true );
   }
   return(false);
}

//*****************************************************************************
bool BFDate::setDay( int iDay )
{
   SYSTEMTIME st;
   cvtToSysTime( days_, st );
   st.wDay = iDay;
   if( isValidDate( st ) )
   {
      days_ = cvtFromSysTime( st );
      return( true );
   }
   return( false );
}

//*****************************************************************************
bool BFDate::setMonth( int iMonth )
{
   SYSTEMTIME st;
   cvtToSysTime( days_, st );
   st.wMonth = iMonth;
   if( isValidDate( st ) )
   {
      days_ = cvtFromSysTime( st );
      return( true );
   }
   return( false );
}

//*****************************************************************************
bool BFDate::setYear( int iYear )
{
   SYSTEMTIME st;
   cvtToSysTime( days_, st );
   st.wYear = iYear;
   if( isValidDate( st ) )
   {
      days_ = cvtFromSysTime( st );
      return( true );
   }
   return( false );
}

//*****************************************************************************
bool BFDate::extractDateComponents( const I_CHAR* pszDate,
                                    DATE_FORMAT fmt,
                                    SYSTEMTIME& st )
{

   if( DF_NULL == fmt ||
       DF_ANYVALIDFORMAT <= fmt )
   {
      return(false);
   }
   else
   {
      int iDay = 0, iMonth = 0, iYear = 0;
      switch( resolveFormat( fmt, pszDate ) )
      {
         case DF_ISO:                               
         case DF_CCYYMMDD:
            i_sscanf( pszDate, I_( "%04d%02d%02d" ), &iYear, &iMonth, &iDay );
            break;
         case DF_FDISO:
         case DF_FDCCYYMMDD:
            i_sscanf( pszDate, I_( "%04d-%02d-%02d" ), &iYear, &iMonth, &iDay );
            break;
         case DF_FSISO:
         case DF_FSCCYYMMDD:
            i_sscanf( pszDate, I_( "%04d/%02d/%02d" ), &iYear, &iMonth, &iDay );
            break;
         case DF_US:
         case DF_MMDDCCYY:                            
            i_sscanf( pszDate, I_( "%02d%02d%04d" ), &iMonth, &iDay, &iYear );
            break;
         case DF_FSUS:
         case DF_FSMMDDCCYY:                          
            i_sscanf( pszDate, I_( "%02d/%02d/%04d" ), &iMonth, &iDay, &iYear );
            break;
         case DF_FDUS:
         case DF_FDMMDDCCYY:                          
            i_sscanf( pszDate, I_( "%02d-%02d-%04d" ), &iMonth, &iDay, &iYear );
            break;

         case DF_EURO:
         case DF_DDMMCCYY:
            i_sscanf( pszDate, I_( "%02d%02d%04d" ), &iDay, &iMonth, &iYear );
            break;
         case DF_FSEURO:
         case DF_FSDDMMCCYY:
            i_sscanf( pszDate, I_( "%02d/%02d/%04d" ), &iDay, &iMonth, &iYear );
            break;
         case DF_FDEURO:
         case DF_FDDDMMCCYY:
            i_sscanf( pszDate, I_( "%02d-%02d-%04d" ), &iDay, &iMonth, &iYear );
            break;

         case DF_NULL:
            return( false );

         default:
            assert( 0 );
            throw BFDateInvalidFormatException();
      }
      st.wYear = iYear;
      st.wMonth = iMonth;
      st.wDay = iDay;

      return(true);
   }
}

//*****************************************************************************
bool BFDate::formatDate( DATE_FORMAT fmt,
                         DString &dstrDateOut ) const
{

   if( DF_NULL == fmt ||
       DF_ANYVALIDFORMAT < fmt ||
       days_ == 0 )
   {
      return(false);
   }
   else
   {
      SYSTEMTIME st;
      cvtToSysTime( days_, st );

      dstrDateOut = I_( "" );
      I_CHAR szDate[ 11 ];

      switch( resolveFormat( fmt ) )
      {
         // ISO Date formats
         case DF_ISO:
         case DF_CCYYMMDD:
            i_sprintf( szDate, I_( "%04d%02d%02d" ), st.wYear, st.wMonth, st.wDay );
            break;
         case DF_FDISO:
         case DF_FDCCYYMMDD:
            i_sprintf( szDate, I_( "%04d-%02d-%02d" ), st.wYear, st.wMonth, st.wDay );
            break;
         case DF_FSISO:
         case DF_FSCCYYMMDD:
            i_sprintf( szDate, I_( "%04d/%02d/%02d" ), st.wYear, st.wMonth, st.wDay );
            break;

         // US Date formats
         case DF_US:
         case DF_MMDDCCYY:
            i_sprintf( szDate, I_( "%02d%02d%04d" ), st.wMonth, st.wDay, st.wYear );
            break;
         case DF_FSUS:
         case DF_FSMMDDCCYY:
            i_sprintf( szDate, I_( "%02d/%02d/%04d" ), st.wMonth, st.wDay, st.wYear );
            break;
         case DF_FDUS:
         case DF_FDMMDDCCYY:
            i_sprintf( szDate, I_( "%02d-%02d-%04d" ), st.wMonth, st.wDay, st.wYear );
            break;
        
         // European Date formats
         case DF_EURO:
         case DF_DDMMCCYY:
            i_sprintf( szDate, I_( "%02d%02d%04d" ), st.wDay, st.wMonth, st.wYear );
            break;
         case DF_FSEURO:
         case DF_FSDDMMCCYY:
            i_sprintf( szDate, I_( "%02d/%02d/%04d" ), st.wDay, st.wMonth, st.wYear );
            break;
         case DF_FDEURO:
         case DF_FDDDMMCCYY:
            i_sprintf( szDate, I_( "%02d-%02d-%04d" ), st.wDay, st.wMonth, st.wYear );
            break;

         default:
            return(false);
      }
      dstrDateOut = szDate;
      return(true);
   }
}

//*****************************************************************************
int BFDate::getJulianDay() const
{
   SYSTEMTIME st;
   cvtToSysTime( days_, st );
   return( aDayYear[ isLeapYear( st.wYear ) ][ st.wMonth - 1 ] + st.wDay );
}

//*****************************************************************************
bool BFDate::setJulianDay( int iDayOfYear )
{
   assert( iDayOfYear >= 0 && iDayOfYear <= 366 );
   SYSTEMTIME st;
   cvtToSysTime( days_, st );
   int iLeapYear = isLeapYear( st.wYear );
   if( iDayOfYear < 1 || ( iDayOfYear > ( 365 + iLeapYear ) ) )
   {
      return( false );
   }


   int iMonth;
   for( iMonth = 0; iMonth < 12; ++iMonth )
   {
      if( iDayOfYear > aDayYear[ iLeapYear ][ iMonth ] &&
          iDayOfYear <= aDayYear[ iLeapYear ][ iMonth + 1 ] )
      {
         break;
      }
   }

   if( iMonth > 11 )
   {
      iMonth = 11;
   }

   st.wMonth = iMonth + 1;
#pragma warning( push )
#pragma warning( disable:4244 )
   st.wDay = iDayOfYear - aDayYear[ iLeapYear ][ iMonth ];
#pragma warning( pop )

   days_ = cvtFromSysTime( st );
   return( true );
}

//*****************************************************************************
bool BFDate::isLeapYear( int iYear )
{
   return( !( iYear & 3 ) && ( ( iYear % 100 ) || !( iYear & 15 ) ) );
}

const BFDate& BFDate::highDate()
{
   static BFDate hd( 31, 12, 9999 );
   return( hd );
}

const BFDate& BFDate::lowDate()
{
   static BFDate ld( 1, 1, 1 );
   return( ld );
}

SYSTEMTIME BFDate::today()
{
   SYSTEMTIME lt;
   GetLocalTime( &lt );
   return( lt );
}

BFDate::DATE_FORMAT BFDate::inferFormat( const DString& dstrDate )
{
   return( inferFormat( dstrDate.c_str() ) );
}

BFDate::DATE_FORMAT BFDate::inferFormat( const I_CHAR* pszDate )
{
   // don't support EURO format!
   switch( i_strlen( pszDate ) )
   {
      case 8:
         // is either mmddccyy or ccyymmdd ... how to decide?
         // well, if we assume, and DDate does, that the year must be greater than 1200, 
         // then if the first two digits of the string are 01 to 12 then it must be a 
         // mmddccyy string, other it is ccyymmdd
         {
            I_CHAR szNum[3];
            i_strncpy( szNum, pszDate, 2 );
            szNum[2] = 0x00;
            I_CHAR* pEnd = NULL;
            int nTest = i_strtol( szNum, &pEnd, 10 );
            if( nTest > 12 )
            {
               // ISO!
               return(DF_ISO);
            }
            return( DF_US );
         }

         break;
      case 10:
         // Currently, this handles:  ccyy-mm-dd (DF_FDISO), ccyy/mm/dd (DF_FSISO)
         //                           mm-dd-ccyy (DF_FDUS), mm/dd/ccyy (DF_FSUS)  [Yuck].
         if( i_isdigit( pszDate[2] ) )
         {
            return(pszDate[4] == I_CHAR('-') ? DF_FDISO : DF_FSISO);
         }
         return(pszDate[2] == I_CHAR('-') ? DF_FDUS : DF_FSUS);
         break;
      case 0:
         return( DF_NULL );
         break;
   }
   return( DF_NULL );
}

BFDate::DATE_FORMAT BFDate::hostFormat() 
{
   // get the host format from the registry and return the matching value
   static const DString dstrConfiguration( I_( "HostMasks" ) );
   static const DString dstrType( I_( "D" ) );
   DString dstrKey;
   dstrKey.append( dstrType );

   DString mask = GetConfigValueAsString( I_( "DICORE" ),
                                          dstrConfiguration,
                                          dstrKey );

   if( mask.size() == 0 )
   {
      throw BFDateInvalidMaskException();
   }

   return( inferMaskFormat( mask ) );
}

BFDate::DATE_FORMAT BFDate::displayFormat( const ClientLocale& rLocale ) 
{
   // get the host format from the registry and return the matching value
   static const DString dstrConfiguration( I_( "DisplayMasks" ) );
   DString dstrKey = rLocale.getLocale() + I_( "-D" );

   DString mask = GetConfigValueAsString( ConfigManager::getApplication(), 
                                          dstrConfiguration,
                                          dstrKey );
   if( mask.size() == 0 )
   {
      throw BFDateInvalidMaskException();
   }

   return( inferMaskFormat( mask ) );
}

BFDate::DATE_FORMAT BFDate::inferMaskFormat( const DString& dstrMask )
{
   // look for the dd|DD, the mm|MM, and the ccyy|CCYY|yyyy|YYYY
   int iDay = dstrMask.find( I_( "DD" ) );
   if( iDay == dstrMask.npos ) iDay = dstrMask.find( I_( "dd" ) );

   int iMonth = dstrMask.find( I_( "MM" ) );
   if( iMonth == dstrMask.npos ) iMonth = dstrMask.find( I_( "mm" ) );

   int iYear = dstrMask.find( I_( "CCYY" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "ccyy" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "YYYY" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "yyyy" ) );

   // if day, month, or year are not known then give up
   if( iDay == dstrMask.npos ||
       iMonth == dstrMask.npos ||
       iYear == dstrMask.npos )
   {
      return( DF_NULL );
   }

   // what is the separator?
   bool bFS = false;
   bool bFD = false;
   if( dstrMask.find( I_( "/" ) ) != dstrMask.npos ) bFS = true;
   else if( dstrMask.find( I_( "-" ) ) != dstrMask.npos ) bFD = true;

   if( iYear < iMonth )
   {
      // it's ISO
      if( bFS ) return( DF_FSISO );
      if( bFD ) return( DF_FDISO );
      return( DF_ISO );
   }
   else if( iDay < iMonth )
   {
      // it's European format (dd/mm/yyyy)
      if( bFS ) return( DF_FSEURO );
      if( bFD ) return( DF_FDEURO );
      return( DF_EURO );
   }
   else if( iMonth < iDay && iDay < iYear )
   {
      // it's US format
      if( bFS ) return( DF_FSUS );
      if( bFD ) return( DF_FDUS );
      return( DF_US );
   }
   //unknown format!
   assert( 0 );
   throw BFDateInvalidFormatException();
}

int BFDate::getDaysInMonth( int iYear, int iMonth )
{
   if( iMonth < 1 || iMonth > 12 ||
       iYear < 1 || iYear > 9999 )
   {
      return( -1 );
   }
   return( aMonthDays[ isLeapYear( iYear ) ][ iMonth - 1 ] );
}

BFDate::DATE_FORMAT BFDate::resolveFormat( DATE_FORMAT fmt, const I_CHAR* pszDate )
{
   if( DF_HOST == fmt )
   {
      return( hostFormat() );
   }
   if( DF_DISPLAY == fmt )
   {
      return( displayFormat( ClientLocaleContext::get() ) );
   }
   if( DF_DDATE_DEPRECATED == fmt )
   {
      fmt = inferFormat( pszDate );
   }

   return( fmt );
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/bfdate.cpp-arc  $
//
//   Rev 1.9   Oct 22 2004 08:59:10   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.8   Jan 27 2003 14:49:38   PURDYECH
// Little fixes for backward compatibility
// 
//    Rev 1.7   Jan 07 2003 10:12:08   PURDYECH
// Added comments.
// Added support for DF_DISPLAY.
// 
//    Rev 1.6   Oct 09 2002 17:41:10   PURDYECH
// New PVCS Database
// 
//    Rev 1.5   Aug 30 2002 15:28:32   HERNANDO
// Fixed inferFormat to handle 10-character dates (US, ISO) correctly.
// 
//    Rev 1.4   Jul 29 2002 13:58:58   ROSIORUC
// Ten character dates were not inferring format correctly.
// 
//    Rev 1.3   Jul 29 2002 13:55:46   ROSIORUC
// Revert to original meaning of DF_US format
// 
//    Rev 1.2   Jul 26 2002 15:45:18   ROSIORUC
// Corrected the US date format in extractDateComponents()
// 
//    Rev 1.1   Jul 05 2002 11:49:34   PURDYECH
// Infrastructure Fixup ... no more ICU!
// 
//    Rev 1.0   May 28 2002 12:02:26   PURDYECH
// Initial revision.
//
