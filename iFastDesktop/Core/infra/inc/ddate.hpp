#ifndef DDATE_HPP
#define DDATE_HPP

#pragma message( "including "__FILE__ )

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DICORE */    

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif
#ifndef BASE_H
   #include "base.h"
#endif
#ifndef DICORE_H
   #include "dicore.h"
#endif

/**@#-*/
//forward declares
class DDate;
class JavaDate;
class JavaDateFormat;
class JavaLocale;
/**@#+*/


#ifndef JAVAGREGORIANCALENDAR_HPP
   #include "javagregoriancalendar.hpp"
#endif

#ifndef JAVADATE_HPP
   #include "javadate.hpp"
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * DDate Class provides commonly used static and non static helper function for date handling, including formatting.        
 *   It uses format enumerations of DF_NULL, DF_CCYYMMDD, DF_MMDDCCYY, DF_FSCCYYMMDD, DF_FSMMDDCCYY, DF_FDCCYYMMDD, DF_FDMMDDCCYY 
 * --Where CC = Century , YY = Year , MM = Month, DD = Day FS = Formated with a Slash, FD = Formated with a Dash.
 * The class derives from JavaDate and has some international capability but is based primarily on a Gregorian Calendar.  
 * Gregorian only methods are currently marked as such.
 *
 * IMPORTANT NOTE FOR IMPLEMENTERS: Remember to call setTime() after any JavaDate changes. */
class DICORE_LINKAGE DDate : public JavaDate
{
public:

        // CC = Century , YY = Year , MM = Month, DD = Day
        // FS = Formated with a Slash, FD = Formated with a Dash.
   enum  DATE_FORMAT {  DF_NULL,        // place holder.
                        DF_CCYYMMDD,    // 19970420
                        DF_MMDDCCYY,    // 04201997
                        DF_FSCCYYMMDD,  // 1997/04/20
                        DF_FSMMDDCCYY,  // 04/20/1997
                        DF_FDCCYYMMDD,  // 1997-04-20
                        DF_FDMMDDCCYY,  // 04-20-1997
                        DF_ANYVALIDFORMAT
                     };
   // This enumeration is used for the specialized gregorian formatting                  
   enum MONTH
   {  JANUARY = 0,
      FEBRUARY,
      MARCH,
      APRIL,
      MAY,
      JUNE,
      JULY,
      AUGUST,
      SEPTEMBER,
      OCTOBER,
      NOVEMBER,
      DECEMBER
   };
                     
   /** Default Constructor */
   DDate();
   
   /** Overloaded Constructor 
    *  @param strDate - DString containing a date in a valid format */
   DDate(const DString &strDate);
   
   /** Copy Constructor */
   DDate( const DDate &copy );
   
   /** Assignment operator */
   DDate & operator=( const DDate& copy );

   /** Destructor */
   virtual ~DDate();
   
   /**
    * 
    * @return the date as a string in MM/DD/CCYY format
    */
   DString & get()
   {
      return _strDate;
   }

   /**
    * greater than operator
    * 
    * @param right
    * @return 
    */
   bool operator>( const DDate & right ) const;

   /**
    * less than operator
    * 
    * @param right
    * @return 
    */
   bool operator<( const DDate & right ) const;

   /**
    * equal comparison operator
    * 
    * @param right
    * @return 
    */
   bool operator==( const DDate & right ) const;

   /**
    * greater than or equal comparison operator
    * 
    * @param right
    * @return 
    */
   bool operator>=( const DDate & right ) const
   {
      return !( *this < right );
   }

   /**
    * less than or equal comparison operator
    * 
    * @param right
    * @return 
    */
   bool operator<=( const DDate & right ) const
   {
      return !( *this > right );
   }

   /**
    * unequal comparison operator
    * 
    * @param right
    * @return 
    */
   bool operator!=( const DDate & right ) const
   {
      return !( *this == right );
   }

   static DString cvtUTCtoDString( DIINT64 );

   static DIINT64 cvtDStringToUTC( DString & );

   /** Returns the current date as a DString for the specified date helper
    *  @param arg - a JavaDateFormat object
    *  @returns - DString containing the current date */ 
   static DString getCurrentDateAsString( JavaDateFormat & arg );

   /** Returns the current date as a DString for the specified locale
    *  @param loc - a pointer to  JavaLocale 
    *  @returns - DString containing the current date */ 
   static DString getCurrentDateAsString( JavaLocale * loc );

   /** Returns the current date as a DString usingstatic member defaultFormat.
    *  If defaultFormat is NULL, the default Locale is used to get the Date Instance for defaultFormat.
    *  @returns - DString containing the current date */ 
   static DString getCurrentDateAsString();

   /** Returns the offset of two date (minuend - subtrahend) as a Dstring format: YYYYMMDD
    *  @param minuend - a JavaDate object 
    *  @param subtrahend - a JavaDate object
    *  @param result - DString containg the offset result   offset = minuedn - subtrahend */
   static DString & getGregorianOffset( JavaDate & minuend, JavaDate & subtrahend, DString & result );
   
   /** Determines the difference between two Gregorian dates and stores the results in YYYYMMDD format
    *  @param minuend - a JavaDate object 
    *  @param subtrahend - a JavaDate object
    *  @param yearDiff - DString to recieve year offset
    *  @param monthDiff - DString to recieve month offset
    *  @param dayDiff - DString to recieve day offset */
   static void subtractGregorian( JavaDate & minuend, 
                                  JavaDate & subtrahend,
                                  DString & yearDiff,
                                  DString & monthDiff,
                                  DString & dayDiff );

// #### This Method Not yet implemented
   /** Adds a Gregorian offset of year month day to a JavaDate
    *  @param date - JavaDate for Gregorian offset to be applied
    *  @param yearDiff - DString containing year offset
    *  @param monthDiff - DString to containing month offset
    *  @param dayDiff - DString to containing day offset 
    *  @returns - the total in a JavaDate format */
   static JavaDate addGregorian( JavaDate & date, 
                             const DString & yearDiff,
                             const DString & monthDiff,
                             const DString & dayDiff ) { return JavaDate(); }

   /** Adds a Gregorian offset of year month day to a JavaDate
    *  @param date - JavaDate for Gregorian offset to be applied
    *  @param yearDiff - integer containing year offset
    *  @param monthDiff - integer containing month offset
    *  @param dayDiff - integer containing day offset 
    *  @returns - the total in a JavaDate format */
   static JavaDate addGregorian( JavaDate & date, 
                             int yearDiff,
                             int monthDiff,
                             int dayDiff );

   /** Method that will add an integer number of Days to a JavaDate
    *  @param date - JavaDate to be incremented
    *  @param nDays - number of days to add to JavaDate
    *  @returns - true if successful */
   static bool addDays( JavaDate & date, const DString & nDays )
   {
       addGregorian( date, 
                     DString( I_( "" ) ), 
                     DString( I_( "" ) ), 
                     nDays ); 
       return true;
   }
  
   /** Method that will add an integer number of years to a JavaDate
    *  @param date - JavaDate to be incremented
    *  @param nDays - number of years to add to JavaDate
    *  @returns - true if successful */
   static bool addYears( JavaDate & date, const DString & nYears )
   {
       addGregorian( date, 
                     nYears, 
                     DString( I_( "" ) ), 
                     DString( I_( "" ) ) ) ;
       return true;
   }

// #### This Method Not yet implemented
   /** Method retrieves the day of year from a JavaDate
    *  @param date - JavaDate supplied to extract day of year 
    *  @returns - day of year as an integer */
   static int getDayOfYear( JavaDate & date );

// #### This Method Not yet implemented
   /** Method retrieves the year from a JavaDate
    *  @param date - JavaDate supplied to extract year 
    *  @returns - year as an integer */
   static int getYear( JavaDate & date );

   /** Method that will add an integer number of years to a JavaDate
    *  @param date - JavaDate to be incremented
    *  @param nDays - number of years to add to JavaDate
    *  @returns - true if successful */
   static bool addDays( JavaDate & date, const int nDays = 1 )
   {
       date = addGregorian( date, 0, 0, nDays ); 
       date.setTime( date.getTime() );
       return true;
   }
   
   /** Method that will add an integer number of years to a JavaDate
    *  @param date - JavaDate to be incremented
    *  @param nDays - number of years to add to JavaDate
    *  @returns - true if successful */
   static bool addYears( JavaDate & date, const int nYears = 1 )
   {
       date = addGregorian( date, nYears, 0, 0 );
       date.setTime( date.getTime() );
       return true;
   }

   /** Compares two DString dates formatted to the HostMasks settings
    *  @param date1 - DString date for comparison
    *  @param date2 - DString date for comparison
    *  @returns - 0 if equal    1 if date1 > date2,  -1 if date1 < date2  (will throw if date formats do not match HostMasks) */
   static int compareHostGregorianDates( const DString &date1, const DString &date2);  


// ################### STUFF FROM OLD DDATE FROM HERE DOWN #########################################

   /** (Gregorian only)Retrieves the Gregorian date from the DDate class in same format as previously set or constructed 
    *  @returns - The Date formatted in a DString */
   DString getDate( void ) const;

   /** (Gregorian only)Sets the Gregorian date of the DDate class 
    *  @returns true if successful */
   bool  setDate( const DString& strDate );

   /** (Gregorian only)Retrieves the day of year from the DDate class 
    *  @returns - the day as an integer range 1 to 365 (366 for leap year) */
   int getDayOfYear( void ) const;

   /** (Gregorian only)Retrieves the year from the DDate class 
    *  @returns - the year as an integer*/
   int getYear( void )const;

   /** (Gregorian only)Retrieves the month from the DDate class 
    *  @returns - the month as an integer (1-based)*/
   int getMonth( void )const
   {
      return _nMonth + 1;
   }

   /** (Gregorian only)Retrieves the day of the month from the DDate class 
    *  @returns - the day as an integer (1-based)*/
   int getDayOfMonth( void )const
   {
      return _nDayOfMonth;
   }

   /** (Gregorian only)Method determines the date format of a DDate object.
    *  @returns = the enumerated date format type */
   DATE_FORMAT getDateFormat( void )const;

   /** (Gregorian only)Method determines if the date calling it is a valid date
    *  @returns - true if is the date is valid */
   bool isValidDate(void) const;

   /** (Gregorian only)Method that will add an integer number of days to a DDate
    *  @param nDays - number of days to add to DDate
    *  @returns - true if successful */
   bool addDays( const int nDays = 1);

   /** (Gregorian only)Method that will subtract an integer number of days from a DDate
    *  @param nDays - number of days to subtract to DDate
    *  @returns - true if successful */
   bool subtractDays( const int nDays = 1);

   /** (Gregorian only)Method that will add an integer number of years to a DDate
    *  @param nYears - number of years to add to DDate
    *  @returns - true if successful */
   bool addYears( const int nYears = 1);

   /** (Gregorian only)Determines if a year is a leap year
    *  @param nYear - year in question
    *  @returns - true if year sent is a leap year */
   static bool isLeapYear( const int nYear );

   /** (Gregorian only)Converts the date format to the Date Format passed to the function
    *  @param strDateIn - DString date to be converted
    *  @param strDateOut - DString date returned with new format
    *  @param dfFormat - enumerated format type for conversion
    *  @returns bool if successful */
   static bool formatDate( const DString& strDateIn, DString& strDateOut, DATE_FORMAT dfFormat );

   /** (Gregorian only)Gets the enumerated date format type of a DString Date
    *  @param strDate - formatted DString date 
    *  @returns - DATE_FORMAT enumeration of DString passed in */
   static DATE_FORMAT getDateFormat( const DString& strDate );

   /** (Gregorian only)Determines if a day is a reasonable value to a month
    *  @param nDayIn - day in question
    *  @param nMonthIn - month in question
    *  @returns - true if day is a reasonable value for the supplied month */
   static bool isDayInMonth( const int nDayIn, const int nMonthIn );
   
   /** (Gregorian only)Method will return the day of the week as a zero-based integer
    *  @param lDateOffset - offset from base date
    *  @returns - zero base integer where Sunday = 0   Saturday = 6 */
   static int getWeekDay( const long lDateOffset );

   /** (Gregorian only)Gets a formatted DString date using a provided offset from a base date
    *
    *  This method is deprecated.
    *
    *  @param - lDateOffset - offset provided to apply to base date
    *  @param - strDateOut - DString to be fill with the new date */
   static void getDateFromOffset( const long lDateOffset, DString & strDateOut );

   /** (Gregorian only)Gets the individual date parts using a provided offset from a base date
    *
    *  This method is deprecated.
    *
    *  @param lDateOffset - offset provided to apply to base date
    *  @param nDay - day of the offset as an int
    *  @param nMonth - month of the offset as an int (1-based)
    *  @param nYear - year of the offset as an int */
   static void getDatePartsFromOffset( const long lDateOffset, int & nDay, int & nMonth, int & nYear )
   {
      _getDatePartsFromOffset( lDateOffset, nDay, nMonth, nYear );
      ++nMonth;
   }

   /** (Gregorian only)Gets the offset between the  Base date and the DString date provided
    *  @param strdate - DString date to compare with base date
    *  @returns  long number representing the offset */
   static long getOffsetFromDate( const DString & strDate );

   /** (Gregorian only)Method determines if the date passed to it is a valid date
    *  @returns - true if is the date is valid */
   static bool isValidDate( const DString & strDate, DATE_FORMAT format = DF_ANYVALIDFORMAT );
   
protected:

   void setUDate( void );

   void set( DIINT64 ltime );

   void set( const DString & date );

      
private: //Methods
   
   /** (Gregorian only)Gets the individual date parts using a provided offset from a base date
    *  @param lDateOffset - offset provided to apply to base date
    *  @param nDay - day of the offset as an int
    *  @param nMonth - month of the offset as an int (0-based)
    *  @param nYear - year of the offset as an int */
   static void _getDatePartsFromOffset( const long lDateOffset, int & nDay, int & nMonth, int & nYear );

   /** (Gregorian only) This method is a helper the takes a gregorian date passed in and its format and convert it to yyyymmdd for comparisons 
    *  @param strDateIn - DString date to be normalised
    *  @param strFormatIn - the format of the Gregorian date valid formats are  any combination of the following
    *  @ 1,2,4 characters for year;  1,2 characters for month; 1,2 characters for day separated by - or /
    *  @returns true if successful */
   static bool normaliseGregorianDate( DString &strDateIn, DString &strFormatIn ); 

   /** (Gregorian only) Compares two normalised dates
    *  @param strDate1 - a normalised date to be compared
    *  @param strDate2 - a normalized date to be compared
    *  @returns - 0 if equal,  -1 if strDate1 < strDate2,  1 if strDate1 > strDate2 */
   static int compareNormalisedDates(DString& strDate1, DString& strDate2 );

   /** (Gregorian only) Retrieves the offset date in individual parts
    *  @param offset - offset number to be applied to JavaDate
    *  @param subtrahend - JavaDate object to apply the offset to 
    *  @param yearDiff - year value of the offset date
    *  @param monthDiff - month value of the offset date
    *  @param dayDiff - day value of the offset date */
   static void getGregorianYearMonthDayOffsets( DIINT64 offset, 
                                                JavaDate & subtrahend,
                                                int & yearDiff,
                                                int & monthDiff,
                                                int & dayDiff );

   /** (Gregorian only) Fills individual DStrings with the parts of the supplied date
    *  @param date - supplied DString date in a valid format
    *  @param month - DString to be filled with the month
    *  @param day - DString to be filled with the day
    *  @param year - DString to be filled with the year */
   static void _splitDateToParts( DString & date, DString & month, DString & day, DString & year );
      
   /** Checks to see if string is null, full of blanks, or full of 0000's
    *  @param strDate - DString date in question
    *  @returns true if date is a NULL value (NON-VALID = TRUE)*/
   static bool _isNullValue( const DString& strDate );      
 
   /** Fills the _nDayOfMonth, _nDayOfYear, _nMonth, _nYear attributes of a DDate object */
   void _splitDateToParts( void );
   
   /** Fill the _strDate attribute of a DDate object based on format of _dfFormat) */
   void _buildDateFromParts( void );
   
   /** Fills the _strDate attribute of DDate object base on value of _nDayOfYear */
   void _getDateFromDayOfYear( void );
   
   /** Fills the _DayOfYear attribute of DDate object base on value of _strDate */
   void _getDayOfYearFromDate( void );

   void updateIUCoffset( void );

   static void extractDateComponents( const DString & strDate, 
                                      DATE_FORMAT format, 
                                      DString & day, 
                                      DString & month, 
                                      DString & year );

   void setTime( DIINT64 lTime );

protected:

   int         _nDayOfMonth;
   int         _nDayOfYear;
   int         _nMonth;
   int         _nYear;
   DString     _strDate;


private://Data

       //  Define a year to use as a base; this must be a year that starts
       //  on a Sunday.  Using short ints (16 bits) gives us a range of 89.7 years
       //  each way (179.42 total).  Using Long ints (32 bits) gives a range
       //  of +/- 2,147,483,648 days ((+/- 5,879,489.8 years, or 11,758,979.6
       //  years total).  Since we may have to calculate the age of 90+ year olds,
       //  we need to use LONGs for the dates from 1900 - 2078.


   static const int _nBaseYear;
   static const long _lStartOfMonthOffsets[12];
   static const int _nDaysInMonth[13];

   DATE_FORMAT _dfFormat;   
};


inline bool DDate::isLeapYear( const int nYear )
{
   return ( !( nYear & 3 ) && ( ( nYear % 100 ) || !( nYear & 15 ) ) );
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
// $Log:   Y:/VCS/iFastAWD/inc/ddate.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:56   kovacsro
//Initial revision.
// 
//    Rev 1.25   08 Aug 2001 12:19:56   DT14177
// removed spaces inside preprocessor
// directives
// 
//    Rev 1.24   11 Dec 2000 12:09:40   dt14177
// made the ddate comparison operators
// const and JavaDate::getUDate() const
// 
//    Rev 1.23   30 Nov 2000 09:52:02   dt14177
// cleanup
// 
//    Rev 1.22   Jul 14 2000 10:31:52   DT14177
// getDatePartsFromOffset interface changes
// 
//    Rev 1.21   Jul 12 2000 11:35:54   DT14177
// added getMonth() and getDayOfMonth()
// 
//    Rev 1.20   Jul 06 2000 15:31:50   DT14177
// changed isValidDate to accept a DATE_FORMAT parameter
// 
//    Rev 1.19   Jun 27 2000 17:02:04   DT14177
// moved some date member variables from JavaDate to DDate
// 
//    Rev 1.17   Jun 16 2000 11:21:44   DT14177
// fixed isValidDate(); some cleanup
// 
//    Rev 1.16   Jun 14 2000 09:46:04   DT14177
// fixed dash formatting (e.g., "MM-DD-CCYY")
// 
//    Rev 1.15   Jun 13 2000 13:15:36   DT14177
// fixed: addDays(), subtractDays(), getDayOfYearFromDate().
// added conditional operators
// 
//    Rev 1.13   Jan 04 2000 06:49:20   DT29758
// Editted java-doc style comments
// 
//    Rev 1.12   Jan 04 2000 06:22:10   DT29758
// added JavaDoc-style comments
// 
//    Rev 1.11   Dec 02 1999 09:05:36   DT29758
// edited ccdoc style comments
// 
//    Rev 1.10   Dec 01 1999 08:47:38   DT29758
// added cc-doc style comments
// 
//    Rev 1.9   Nov 19 1999 14:54:20   DT29758
// added method compareHostGregorianDates
// 
// 
//    Rev 1.8   Nov 12 1999 08:02:50   DT29758
// Merged with 1.7 DDate class for retrofit
// 
//    Rev 1.7   Oct 12 1999 09:54:16   DT14177
// changed to inherit from JavaDate; made constructor public
// 
//    Rev 1.6   Sep 16 1999 16:28:14   DT14177
// memory leak cleanup
// 
//    Rev 1.5   Jul 16 1999 14:44:42   DT14177
// reworked the subtract/offset interface.
// 
//    Rev 1.4   Jul 16 1999 11:32:28   DT14177
// added comments
// 
//    Rev 1.3   Jul 16 1999 11:26:38   DT14177
// Added getOffset() to DDate and minus() to JavaDate
// 
//    Rev 1.2   Jun 18 1999 12:35:00   DT14177
// Added code to get the Date format string from the registry.
// 
//    Rev 1.1   Jun 14 1999 12:18:38   DT14177
// Added revision control blocks.
// 
#endif   // DDATE_HPP

