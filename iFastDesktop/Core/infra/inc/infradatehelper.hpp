#ifndef INFRADATEHELPER_HPP
#define INFRADATEHELPER_HPP

#  pragma message( "including "__FILE__ )

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

#ifndef GREGOCAL_H
   #include <gregocal.h>
#endif

#ifndef INFRALOCALE_HPP
   #include "infralocale.hpp"
#endif

#ifndef TRACERCLIENT_HPP
   #include "TracerClient.hpp"
#endif

/**@#-*/  // forward declarations
namespace Infra
{
   class DateFormat;
   class SimpleDateFormat;
   class Date;
   class DateHelper;
   class GregorianCalendar;
   class Locale;
   class ClientLocale;
};

class DString;
/**@#+*/

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif


#ifndef INFRADATEHELPER_CPP

void initGregorianFormatMap( void );
void resetGregorianFormatMap( Infra::Locale & locale );

#endif


/**
 * The DateHelper class provides commonly used static
 * helper functions for date handling, including formatting.        
 *
 * The class has some international capability but is based 
 * primarily on a Gregorian Calendar. Gregorian only methods are 
 * currently marked with Gregorian as part of the name.
 */

class DICORE_LINKAGE Infra::DateHelper
{
public:

   enum {
            ICU_ERROR = 1
        } ElementalCondition;

   // This enumeration is used for the specialized gregorian 
   // formatting                  
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
                     
   /** Returns the current date as a DString for the specified
    *     date helper
    *  @param arg - a Infra::DateFormat object
    *  @returns - DString containing the current date */ 
   static DString getCurrentDateAsString( Infra::DateFormat & 
                                          arg );

   /** Returns the current date as a DString for the specified
     *   locale
    *  @param loc - a pointer to Locale 
    *  @returns - DString containing the current date */ 
   static DString getCurrentDateAsString( Infra::Locale * loc );

   /** Returns the current date as a DString usingstatic member
    *    defaultFormat.
    *  If defaultFormat is NULL, the default Locale is used to
    *  get the Date Instance for defaultFormat.
    *  @returns - DString containing the current date */ 
   static DString getCurrentDateAsString();

   /** Returns the offset of two dates (minuend - subtrahend) in
    *     Dstring format: YYYYMMDD
    *  @param minuend - a DString object 
    *  @param subtrahend - a DString object
    *  @param result - DString containg the offset result   
    *     offset = minuend - subtrahend */
   static DString & getGregorianOffset( DString & minuend, 
                                        DString & subtrahend, 
                                        DString & result );
   
   /** Determines the difference between two Gregorian dates and
    *     stores the results in YYYYMMDD format
    *  @param minuend - a DString object 
    *  @param subtrahend - a DString object
    *  @param yearDiff - DString to recieve year offset
    *  @param monthDiff - DString to recieve month offset
    *  @param dayDiff - DString to recieve day offset */
   static void subtractGregorian( const DString & minuend, 
                                  const DString & subtrahend,
                                  DString & yearDiff,
                                  DString & monthDiff,
                                  DString & dayDiff );

   /** Determines the difference between two Gregorian dates and
    *     stores the results in YYYYMMDD format
    *  @param minuend - a DString object 
    *  @param subtrahend - a DString object
    *  @param yearDiff - DString to recieve year offset
    *  @param monthDiff - DString to recieve month offset
    *  @param dayDiff - DString to recieve day offset */
   static void subtractGregorian( const Infra::Date & minuend, 
                                  const Infra::Date & subtrahend,
                                  DString & yearDiff,
                                  DString & monthDiff,
                                  DString & dayDiff );

   /** Adds a Gregorian offset of year month day to a DString
    *  @param date - DString for Gregorian offset to be applied
    *  @param yearDiff - DString containing year offset
    *  @param monthDiff - DString containing month offset
    *  @param dayDiff - DString containing day offset 
    *  @returns - the total in a DString format */
   static DString & addGregorian( DString & date, 
                                  const DString & yearDiff,
                                  const DString & monthDiff,
                                  const DString & dayDiff );

   /** Adds a Gregorian offset of year month day to a DString
    *  @param date - DString for Gregorian offset to be applied
    *  @param yearDiff - integer containing year offset
    *  @param monthDiff - integer containing month offset
    *  @param dayDiff - integer containing day offset 
    *  @returns - the total in a DString format */
   static DString & addGregorian( DString & date, 
                                  int yearDiff,
                                  int monthDiff,
                                  int dayDiff );

   /** Method that will add an integer number of Days to a
    *     DString
    *  @param date - DString to be incremented
    *  @param nDays - number of days to add to DString
    *  @returns - true if successful */
   static bool addDays( DString & date, int nDays );
  
   /** Method that will add an integer number of Days to a
    *     DString
    *  @param date - DString to be incremented
    *  @param nDays - number of days to add to DString
    *  @returns - true if successful */
   static bool addDays( DString & date, const DString & nDays );
  
   /** Method that will add an integer number of Days to a
    *     Infra::Date
    *  @param date - Infra::Date to be incremented
    *  @param nDays - number of days to add to Infra::Date
    *  @returns - true if successful */
   static bool addDays( Infra::Date & date, 
                        const DString & nDays );
  
   /** Method that will add an integer number of Days to a
    *     Infra::Date
    *  @param date - Infra::Date to be incremented
    *  @param nDays - number of days to add to Infra::Date
    *  @returns - true if successful */
   static bool addDays( Infra::Date & date, int nDays );
  
   /** Method that will add an integer number of years to a
    *     DString
    *  @param date - DString to be incremented
    *  @parma nDays - number of years to add to DString
    *  @returns - true if successful */
   static bool addYears( DString & date, 
                         const DString & nYears );

   /** Method that will add an integer number of years to a
    *     DString
    *  @param date - DString to be incremented
    *  @parma nDays - number of years to add to DString
    *  @returns - true if successful */
   static bool addYears( DString & date, 
                         const int nYears );

   /** Method that will add an integer number of years to a
    *     Infra::Date
    *  @param date - Infra::Date to be incremented
    *  @parma nDays - number of years to add to Infra::Date
    *  @returns - true if successful */
   static bool addYears( Infra::Date & date, 
                         const int nYears );

   /** Method retrieves the day of year from a date string
    *  @param date - DString supplied to extract day of year 
    *  @returns - day of year as an integer */
   static int getDayOfYear( DString & date );

   /**
   /** Method retrieves the year from a date string
    *  @param date - DString supplied to extract year 
    *  @returns - year as an integer */
   static int getYear( DString & date );

   /**
    * determines if the difference between two dates spans a year
    * 
    * @param startDate
    * @param endDate
    * @return true if year is spanned
    *         false otherwise
    */
   static bool spanYear( const DString & startDate,
                         const DString & endDate );

   /**
    * This function compares two times.  If Time1 is less
    * than Time2 the function returns -1.  If the two Times are
    * equal the function returns 0. If Time1 is greater than Time2
    * the function returns 1.
    * 
    * @param strTime1
    * @param strTime2
    * @return 
    */
   static int compareTimes( const DString& strTime1, 
                            const DString& strTime2 );

   /** Compares two DString dates formatted to the HostMasks
    *     settings
    *  @param date1 - DString date for comparison
    *  @param date2 - DString date for comparison
    *  @returns - 0 if equal    1 if date1 > date2,
    *                          -1 if date1 < date2
    *  (will throw if date formats do not match HostMasks) */
   static int compareHostGregorianDates( const DString &date1, 
                                         const DString &date2);  


   /** (Gregorian only)Determines if a year is a leap year
    *  @param nYear - year in question
    *  @returns - true if year sent is a leap year */
   static bool isLeapYear( const int nYear );

   /** (Gregorian only)Converts the date format to the Date
    *     Format passed to the function
    *  @param strDateIn - DString date to be converted
    *  @param strDateOut - DString date returned with new format
    *  @param dfFormat - enumerated format type for conversion
    *  @returns bool if successful */
   static bool formatGregorianDate( const DString & strDateIn, 
                                    DString & strDateOut,
                                    const DString & dfFormat );

   /** (Gregorian only)Gets the enumerated date format type of a
    *     DString Date
    *  @param strDate - formatted DString date 
    *  @returns - const DString &
    *     passed in */
   static bool getGregorianDateFormat( const DString & date,
                                       DString & format );

   /** (Gregorian only)Determines if a day is a reasonable value
    *     to a month
    *  @param nDayIn - day in question
    *  @param nMonthIn - month in question
    *  @returns - true if day is a reasonable value for the
    *     supplied month */
   static bool isDayInMonth( const int nDayIn, 
                             const int nMonthIn );
   
   /** (Gregorian only)Method will return the day of the week as
    *     a zero-based integer
    *  @param lDateOffset - offset from base date
    *  @returns - zero base integer where Sunday = 0
    *                                     Saturday = 6 */
   static int getWeekDay( Infra::Date & date );

   /**
    * (Gregorian only)Method determines if the date passed to it
    *     is a valid date
    *  @returns - true if is the date is valid
    * @param strDate date to be tested
    * @param dFormat format to test the date against
    * @return 
    */
   static bool isValidGregorianDate( const DString & strDate,
                                     const DString & dFormat );
   
   /**
    * (Gregorian only)Method determines if the date passed to it
    *     is a valid date
    *  @returns - true if is the date is valid
    * @param strDate date to be tested
    * @return 
    */
   static bool isValidGregorianDate( const DString & strDate );
   
   /** Checks to see if string is null, full of blanks, or full 
    *     of 0000's
    *  @param strDate - DString date in question
    *  @returns true if date is a NULL value (NON-VALID = TRUE)*/
   static bool isNullValue( const DString& strDate );      

   //   It's a friend because it needs to know about the private
   // methods which use the internal double date format.
   friend Infra::SimpleDateFormat;

   //   It's a friend because it needs to know about the private
   // format strings.
   //friend void resetGregorianFormatMap( Infra::Locale & locale );
   static void resetGregorianFormatMap( Infra::Locale& locale );

public: // Attributes

   static const long _lStartOfMonthOffsets[ 12 ];
   static const int _nDaysInMonth[ 13 ];
   static const DString DF_MMDDCCYY;
   static const DString DF_FSMMDDCCYY;
   static const DString DF_FDMMDDCCYY;
   static const DString DF_CCYYMMDD;
   static const DString DF_FSCCYYMMDD;
   static const DString DF_FDCCYYMMDD;
   static const DString DF_DDMMCCYY;
   static const DString DF_FPDDMMCCYY;

private: // Methods
   
   static double addDayOffset( double start,
                               double dayoffset, 
                               double & result );

   static DString & getGregorianOffset( double minuend, 
                                        double subtrahend, 
                                        DString & result );
   
   static void subtractGregorian( double minuend, 
                                  double subtrahend,
                                  DString & yearDiff,
                                  DString & monthDiff,
                                  DString & dayDiff );

   static double addGregorian( double date, 
                             const DString & yearDiff,
                             const DString & monthDiff,
                             const DString & dayDiff );

   static double addGregorian( double date, 
                             int yearDiff,
                             int monthDiff,
                             int dayDiff );

   static bool addDays( double & date, const DString & nDays );
  
   static bool addDays( double & date, const int nDays );
   
   static bool addYears( double & date, 
                         const DString & nYears );

   static bool addYears( double & date, 
                         const int nYears );

   /** Method retrieves the day of year from a double
    *  @param date - double supplied to extract day of year 
    *  @returns - day of year as an integer */
   static int getDayOfYear( double date );

   /** Method retrieves the year from a double
    *  @param date - double supplied to extract year 
    *  @returns - year as an integer */
   static int getYear( double date );

   static bool spanYear( double startDate,
                         double endDate );

   static void getGregorianYearMonthDayOffsets( double offset, 
                                                double subtrahend,
                                                int & yearDiff,
                                                int & monthDiff,
                                                int & dayDiff );

   static void extractGregorianDateComponents( 
                                    const DString & strDate, 
                                    const DString & format, 
                                    DString & day, 
                                    DString & month, 
                                    DString & year,
                                   const Infra::Locale * locale =
                            Infra::Locale::getDefaultInstance() );

   static bool getStringDateAsDouble( const DString & strDate,
                                      double & retVal );

private: // Attributes

   typedef std::map< DString,
                     Infra::SimpleDateFormat * > 
                                              gregorianFormatMap;

private:
   static gregorianFormatMap gregorianFormatMapInstance;

#ifdef ENABLE_TRACING
   public:
      static TracerClient& getTracerClient() { return tracerClient;};
   private:
      static TracerClient tracerClient;
#endif

};


inline bool Infra::DateHelper::isLeapYear( const int nYear )
{
   return ( !( nYear & 3 ) && ( ( nYear % 100 ) || 
                                !( nYear & 15 ) ) );
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
// $Log:   Y:/VCS/iFastAWD/inc/infradatehelper.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:44   kovacsro
//Initial revision.
//
//   Rev 1.2   May 18 2001 14:23:50   dt24433
// 
//
//   Rev 1.1   04 Jan 2001 18:40:06   dt14177
//fixed TRACER_VARIABLE release
//compile problems
//
//   Rev 1.0   28 Dec 2000 08:58:48   dt14177
// 

#endif  // INFRADATEHELPER_HPP
