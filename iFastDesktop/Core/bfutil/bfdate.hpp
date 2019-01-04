#pragma once

#include <commonport.h>
#include <dicore.h>
#include <dstring.hpp>

#include <bfutil\bfexception.hpp>
#include <bfdata\bfdataexception.hpp>

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class BFUTIL_LINKAGE BFDateException : public BFException
{
};
class BFUTIL_LINKAGE BFDateInvalidException : public BFDateException
{
};
class BFUTIL_LINKAGE BFDateInvalidFormatException : public BFDateException
{
};
class BFUTIL_LINKAGE BFDateInvalidMaskException : public BFDateException
{
};

/**
 * This class represents Gregorian dates.  The class will validate 
 * dates, compare two dates, perform simple arithmetic, and format
 * dates.
 * 
 * @author Chris Purdye
 */
class BFUTIL_LINKAGE BFDate
{
public:
   /**
    * Subtract one date from another and get the corresponding number of days
    * between them
    * @param lhs  First date
    * @param rhs  Second date
    * @return difference (in days) between the two dates.
    */
   friend long operator-( const BFDate& lhs, const BFDate& rhs );

   /**
    * Subtract a number of days from a date.
    * @param lhs Date to subtract days from
    * @param cDays number of days to subtract
    * @return A new BFDate object which is cDays earlier than the original date.
    */
   friend BFDate operator-( const BFDate& lhs, long cDays );
   /**
    * Add a number of days to a date.
    * @param lhs Date to add days to
    * @param cDays number of days to add
    * @return A new BFDate object which is cDays later than the original date.
    */
   friend BFDate operator+( const BFDate& lhs, long cDays );

   /**
    *!Date format specifier.
    * Date format specifier.  These values are used when passing date
    * strings into or out of the BFDate object.  
    * <dl>
    * <dt>CC</dt><dd>Century</dd>
    * <dt>YY</dt><dd>Year in century</dd>
    * <dt>MM</dt><dd>Month</dd>
    * <dt>DD</dt><dd>Day</dd>
    * <dt>FS</dt><dd>Formated with a Forward Slash( <b>/</b> )</dd>
    * <dt>FD</dt><dd>Formated with a Dash ( <b>-</b> )</dd>
    * </dl>
    */
   enum  DATE_FORMAT
   {
      DF_NULL            //! place holder.
      // US formats
      , DF_US            //! Standard US Date format with no separators (e.g. 04201997).  Same as DF_MMDDCCYY.
      , DF_MMDDCCYY      //! Standard US Date format with no separators (e.g. 04201997).  Same as DF_US.
      , DF_FSUS          //! Standard US Date format with forward slashes as separators (e.g. 04/20/1997).  
      , DF_FSMMDDCCYY    //! Standard US Date format with forward slashes as separators (e.g. 04/20/1997).  Same as DF_FSMMDDCCYY
      , DF_FDUS          //! Standard US Date format with dashes as separators (e.g. 04-20-1997).  
      , DF_FDMMDDCCYY    //! Standard US Date format with dashes as separators (e.g. 04-20-1997).  Same as DF_FDMMDDCCYY

      // ISO formats
      , DF_ISO            //! ISO Date format with no separators (e.g. 19970420).  Same as DF_CCYYMMDD
      , DF_CCYYMMDD       //! ISO Date format with no separators (e.g. 19970420).  Same as DF_ISO
      , DF_FDISO          //! ISO Date format with dashes as separators (e.g. 1997-04-20).
      , DF_FDCCYYMMDD     //! ISO Date format with dashes as separators (e.g. 1997-04-20).  Same as DF_FDISO
      , DF_FSISO          //! ISO Date format with forward slashes as separators (e.g. 1997/04/20). 
      , DF_FSCCYYMMDD     //! ISO Date format with forward slashes as separators (e.g. 1997/04/20).  Same as DF_FSISO
        
      // European formats
      , DF_EURO           //! European Date format with no separators (e.g. 20041997).  Same as DF_DDMMCCYY
      , DF_DDMMCCYY       //! European Date format with no separators (e.g. 20041997).  Same as DF_EURO
      , DF_FSEURO         //! European Date format with forward slashes as separators (e.g. 20/04/1997).  
      , DF_FSDDMMCCYY     //! European Date format with forward slashes as separators (e.g. 20/04/1997).  Same as DF_FSEURO
      , DF_FDEURO         //! European Date format with dashes as separators (e.g. 20-04-1997).  
      , DF_FDDDMMCCYY     //! European Date format with dashes as separators (e.g. 20-04-1997).  Same as DF_FDEURO

      // Registry specified formats
      , DF_HOST           //! Use registry defined Host Display format
      , DF_DISPLAY        //! Use registry defined User Display format

      , DF_DDATE_DEPRECATED   //! Use DDate class inference rules.  Infer from the values in the date string which ISO or US date format it is.

      , DF_ANYVALIDFORMAT     //! place holder
   };

   /** Default Constructor */
   BFDate();

   /**
    * construct a BFDate object from a SYSTEMTIME struct
    * 
    * @param st     A SYSTEMTIME struct.  Only the wYear, wMonth, and wDay fields are used.
    */
   BFDate( const SYSTEMTIME& st );

   /** Construct a BFDate object from a C String
    *  @param pszDate - DString containing a date in a valid format 
    *  @param eFormat - Format of pszDate
    */
   BFDate( const I_CHAR* pszDate, DATE_FORMAT eFormat );
   /** Construct a BFDate object from a DString
    *  @param dstrDate - DString containing a date in a valid format 
    *  @param eFormat - Format of dstrDate
    */
   BFDate( const DString& dstrDate, DATE_FORMAT eFormat );

   /**
    * Construct this BFDate object from the day, month, and year
    * 
    * @param iDay   The day of the month.  Starts at 1.  Valid end-values of the range
    *               depends upon the month and year
    * @param iMonth The month of the year.  Valid values are 1 to 12.
    * @param iYear  The year.  This should be expressed as the complete year since the
    *               baseline date of 01Jan0000.
    */
   BFDate( int iDay, int iMonth, int iYear );

   /**
    * Copy Constructor
    * 
    * @param rhs    BFDate object to copy from
    */
   BFDate( const BFDate& rhs );

   /**
    * Assignment operator
    * 
    * @param rhs    BFDate object to assign from
    * 
    * @return A non-const reference to this object.
    */
   BFDate& operator=( const BFDate& rhs );

   /** Destructor */
   ~BFDate();

   /**
    * Get the date as a string
    * 
    * @param eFormat The desired format.
    * 
    * @return the date as a string in the desired format
    */
   DString get( DATE_FORMAT eFormat ) const;


   /**
    * Get the date as a string.
    * 
    * @param dstrMask A mask string.  Use mm to represent the month position, dd to
    *                 represent the day position, and yyyy to represent the year
    *                 position.  e.g. "MM/DD/YYYY"
    * 
    * @return the date as a string in the desired format
    */
   DString get( const DString& dstrMask ) const;

   /**
    * greater than operator
    * 
    * @param rhs    BFDate object to compare to
    * 
    * @return true if this BFDate object is later than rhs.
    */
   bool operator>( const BFDate& rhs ) const;

   /**
    * less than operator
    * 
    * @param rhs    BFDate object to compare to
    * 
    * @return true if this BFDate object is earlier than rhs.
    */
   bool operator<( const BFDate& rhs ) const;

   /**
    * equal comparison operator
    * 
    * @param rhs    BFDate object to compare to
    * 
    * @return true if this BFDate object represents the same date as rhs.
    */
   bool operator==( const BFDate& rhs ) const;

   /**
    * greater than or equal comparison operator
    * 
    * @param rhs    BFDate object to compare to
    * 
    * @return true if this BFDate object represents a date which is not earlier than rhs
    */
   bool operator>=( const BFDate& rhs ) const
   {
      return(!( *this < rhs ));
   }

   /**
    * less than or equal comparison operator
    * 
   * @param rhs    BFDate object to compare to
   * 
   * @return true if this BFDate object represents a date which is not later than rhs
    */
   bool operator<=( const BFDate& rhs ) const
   {
      return(!( *this > rhs ));
   }

   /**
    * unequal comparison operator
    * 
   * @param rhs    BFDate object to compare to
   * 
   * @return true if this BFDate object represents a date which is not the same as rhs
    */
   bool operator!=( const BFDate& rhs ) const
   {
      return(!( *this == rhs ));
   }


   /**
    * Make this object earlier.
    * 
    * @param days   The number of days by which this BFDate object should be made earlier.
    * 
    * @return A non-const reference to this BFDate object.
    */
   BFDate& operator-=( long days )
   {
      if( ( days_ - days ) > 0 )
      {
         days_ -= days;
      }
      return( *this );
   }

   /**
    * Make this object later.
    * 
    * @param days   The number of days by which this BFDate object should be made later.
    * 
    * @return A non-const reference to this BFDate object.
    */
   BFDate& operator+=( long days )
   {
      if( ( days_ + days ) <= highDate().days_ )
      {
         days_ += days;
      }
      return( *this );
   }

   /**
    * Will add an integer number of days to this BFDate
    * 
    * @param cDays  number of days to add
    * 
    * @return true if successful
    */
   bool addDays( long cDays );
   /**
    * Will add an integer number of months to this BFDate
    * 
    * @param cMonths Number of months to add.  The day may be set to the last valid day of the new month
    *                if the current value of day is invalid for the new month/year combination.
    *                e.g. Adding 1 month to 2002/10/31 will yield 2002/11/30.
    * 
    * @return true if successful
    */
   bool addMonths( long cMonths );
   /**
    * Add an integer number of years to this BFDate object.
    * 
    * @param cYears Number of years to add.  The day may be set to the last valid day
    *               of the new month if the current value of day is invalid for the new
    *               month/year combination.  e.g. Adding 1 year to 2004/02/29 will
    *               yield 2005/02/28.
    * 
    * @return true if successful
    */
   bool addYears( long cYears );

   /**
    * Get the day as a integer
    * 
    * @return The day of this BFDate object
    */
   int getDay() const;
   /**
    * Get the month as a integer
    * 
    * @return The month of this BFDate object
    */
   int getMonth() const;
   /**
    * Get the year as a integer
    * 
    * @return The year of this BFDate object
    */
   int getYear() const;
   /**
    * Get the day of the week.
    * 
    * @return An integer representing the day of the week.  0 = Sunday, 1 = Monday, ... 6 = Saturday
    */
   int getWeekDay() const;

   /**
    * Determine if this date is empty (i.e. is not a valid date)
    * 
    * @return true if this BFDate object is not a valid date.
    */
   bool isNull() const { return( 0 == days_ );}

   /**
    * Determine if this date is the high date (i.e. the latest possible date)
    * 
    * @return true if this BFDate object is equal to the latest possible date.
    */
   bool isHighDate() const { return (*this == highDate() ); }

   /**
    * Determine if this date is the low date (i.e. the earliest possible date)
    * 
    * @return true if this BFDate object is equal to the earliest possible date.
    */
   bool isLowDate() const { return (*this == lowDate() ); }

   /**
    * Determine if a given date string is valid given a format specifier
    * 
    * @param dstrDate The date string.  This will be interpreted according to the format
    *                 specifier
    * @param eFormat  A valid format specifier.
    * 
    * @return true if the date is valid.
    */
   static bool isValidDate( const DString& dstrDate, DATE_FORMAT eFormat );

   /**
    * Determine if a given SYSTEMTIME structure contains a valid date.
    * 
    * @param st     A reference to a SYSTEMTIME structure.
    * 
    * @return true if the date is valid.
    */
   static bool isValidDate( const SYSTEMTIME& st );

   /**
    * Determine if a given combination of day, month, and year contains a valid date.
    * 
    * @param iDay   The day of the month.  Starts at 1.  Valid end-values of the range
    *               depends upon the month and year
    * @param iMonth The month of the year.  Valid values are 1 to 12.
    * @param iYear  The year.  This should be expressed as the complete year since the
    *               baseline date of 01Jan0000.
    * 
    * @return true if the date is valid.
    */
   static bool isValidDate( int iDay, int iMonth, int iYear );

   /**
    * Is the year valid.  Valid years are from 0 to 9999.
    * 
    * @param iYear  year to test
    * 
    * @return true if the year is valid for BFDate
    */
   static bool isValidYear( int iYear );

   /**
    * Determine if the specified year a leap year.
    * 
    * @param iYear  The year to test.
    * 
    * @return true if the specified year is a leap year.
    */
   static bool isLeapYear( int iYear );

   /**
    * Determine if the specified month is valid.
    * 
    * @param iMonth the month to test.  Valid months are in the range 1 to 12.
    * 
    * @return true if the specified month is valid
    */
   static bool isValidMonth( int iMonth );

   /**
    * Determine if the specified day is valid in the context of a month and year.
    * 
    * @param iDayIn   The day of the month.  Starts at 1.  Valid end-values of the range
    *                 depends upon the month and year
    * @param iMonthIn The month of the year.  Valid values are 1 to 12.
    * @param iYearIn  The year.  This should be expressed as the complete year since the
    *                 baseline date of 01Jan0000.
    * 
    * @return true if the specified day is valid
    */
   static bool isValidDay( int iDayIn, int iMonthIn, int iYearIn );


   /**
    * Determine what the most likely date format is given a date string.
    * This method evaluates between ISO (year,month,day) and US (month, day, year)
    * date formats when making its evaluation.  It does not consider the
    * European date format (day,month,year).
    * 
    * @param pszDate The date string to test.
    * 
    * @return A date format specifier.
    */
   static DATE_FORMAT inferFormat( const I_CHAR* pszDate );

   /**
    * Determine what the most likely date format is given a date string.
    * This method evaluates between ISO (year,month,day) and US (month, day, year)
    * date formats when making its evaluation.  It does not consider the
    * European date format (day,month,year).
    * 
    * @param dstrDate The date string to test.
    * 
    * @return A date format specifier.
    */
   static DATE_FORMAT inferFormat( const DString& dstrDate );

   /**
    * Determine what the current HostFormat date specifier is.  This
    * is taken from the Registry key HKLM/Software/DST/DICORE/Config/HostMasks.
    * The value data for the value D represents a date mask using MM, DD, 
    * and YYYY to designate the positions of those elements.
    * 
    * @return The date format specifier used by Host dates.
    */
   static DATE_FORMAT hostFormat();

   /**
    * Determine what the current DisplayFormat date specifier is.  This
    * is taken from the Registry key HKLM/Software/DST/(Application}/Config/DisplayMasks.
    * The value data for the value [language][Country]-D represents a date mask using MM, DD, 
    * and YYYY to designate the positions of those elements.
    * 
    * @return The date format specifier used by Display dates.
    */
   static DATE_FORMAT displayFormat( const ClientLocale& rLocale );

   /**
    * Given any date mask determine an appropriate date format specifier.
    * 
    * @param dstrMask The mask to use when making the inference.
    * 
    * @return A date format specifier.
    * @exception BFDateInvalidFormatException
    *                   The date mask conforms to no known date format.
    */
   static DATE_FORMAT inferMaskFormat( const DString& dstrMask );

   /**
    * Get the number of days in a specific month and year
    * 
    * @param iYear  The year
    * @param iMonth The month.  Use 1 for January, 2 for February, ...
    * 
    * @return The number of days in that month for that year.
    */
   static int getDaysInMonth( int iYear, int iMonth );

   /**
    * Set the day of the date.  This method will fail if the date would be invalid.
    * 
    * @param iDay   The new day.
    * 
    * @return true if the day was successfully set.  If the new day would cause
    *         the date to be invalid the date is not changed and false is returned.
    */
   bool setDay( int iDay );
   /**
    * Set the month of the date.  This method will fail if the date would be invalid.
    * 
    * @param iMonth The new month.  Use 1 for January, 2 for February, ...
    * 
    * @return true if the month was successfully set.  If the new month would cause
    *         the date to be invalid the date is not changed and false is returned.
    */
   bool setMonth( int iMonth );

   /**
    * Set the year of the date.  This method will fail if the date would be invalid.
    * 
    * @param iYear  The new year.
    * 
    * @return true if the day was successfully set.  If the new year would cause
    *         the date to be invalid the date is not changed and false is returned.
    */
   bool setYear( int iYear );

   /**
    * Set the date from a SYSTEMTIME struct.
    * 
    * @param st     The SYSTEMTIME to use.  Only the wYear, wMonth, and wDay fields
    *               are used.
    * 
    * @return true if the date was successfully set.  If the SYSTEMTIME is not
    *         valid then this object is not changed.
    */
   bool set( const SYSTEMTIME& st );

   /**
    * Set the date from a combination of day, month, and year.
    * 
    * @param iDay   The day of the month.  Starts at 1.  Valid end-values of the range
    *               depends upon the month and year
    * @param iMonth The month of the year.  Valid values are 1 to 12.
    * @param iYear  The year.  This should be expressed as the complete year since the
    *               baseline date of 01Jan0000.
    * 
    * @return true if the date was successfully set.  If the the date specified year, month,
    *         and day are not valid then false is returned and the date is not changed.
    */
   bool set( int iDay, int iMonth, int iYear );

   /**
    * Set the date from a C String and a date format specifier
    * 
    * @param pszDate A C date string.
    * @param eFormat A date format specifier which conforms to the date string
    * 
    * @return true if the date string is valid and was set in.  If the date string
    *         was not valid for the format specifier then this date object is set
    *         to a Null Date and false is returned.
    */
   bool set( const I_CHAR* pszDate, DATE_FORMAT eFormat );

   /**
    * Set the date from a DString and a date format specifier
    * 
    * @param dstrDate A DString date.
    * @param eFormat  A date format specifier which conforms to the date string
    * 
    * @return true if the date string is valid and was set in.  If the date string
    *         was not valid for the format specifier then this date object is set
    *         to a Null Date and false is returned.
    */
   bool set( const DString& dstrDate, DATE_FORMAT eFormat );

   /**
    * Return a const reference to a BFDate object which has the highest
    * possible date.
    * 
    * @return a const-reference to a BFDate object.  This object is guaranteed
    *         to be greater than or equal to any other date object.
    */
   static const BFDate& highDate();

   /**
    * Return a const reference to a BFDate object which has the lowest
    * possible date.
    * 
    * @return a const-reference to a BFDate object.  This object is guaranteed
    *         to be less than or equal to any other date object.
    */
   static const BFDate& lowDate();

   /**
    * Get a SYSTEMTIME struct which has the value appropriate for today.
    * 
    * @return A SYSTEMTIME struct with the wYear, wMonth, and wDay fields being
    *         correct for the current date.
    */
   static SYSTEMTIME today();

   /**
    * Get the julian day for this date object.
    * 
    * @return The Julian day.  This will be a value in the range of 1 to 366.
    */
   int getJulianDay() const;

   /**
    * Set the Julian day for this date object.
    * 
    * @param iJulian The Julian day.  The valid value is in the range 1 to 365 for non-leap
    *                years and 1 to 366 for leap years.
    * 
    * @return true if the Julian day was successfully set.
    */
   bool setJulianDay( int iJulian );
protected:

private: //Methods

   static bool extractDateComponents( const I_CHAR* pszDate, 
                                      DATE_FORMAT format, 
                                      SYSTEMTIME& st );

   /**
    * Create a string representation of the date using a specified format
    *
    * @param fmt
    *               - date format to use 
    * @param dstrDateOut
    *               - DString date returned with new format
    * @return bool if successful
    */
   bool formatDate( DATE_FORMAT fmt,
                    DString &dstrDateOut ) const;

public:
   // constants used to calculate values
   static const int secondsPerMinute;  //! number of seconds in a minute
   static const int secondsPerHour;    //! number of seconds in an hour
   static const int secondsPerDay;     //! number of seconds in a day

   static const int daysPer400Years;   //! number of days every 400 years
   static const int daysPer100Years;   //! number of days every 100 years
   static const int daysPer4Years;     //! number of days every 4 years
   static const int daysPerYear;       //! number of days in a year

private:
   long     days_;                     //! number of days since baseline date
   static long cvtFromSysTime( const SYSTEMTIME& st );
   static void cvtToSysTime( long dt, SYSTEMTIME& st );

   static BFDate::DATE_FORMAT resolveFormat( DATE_FORMAT fmt, const I_CHAR* pszDate = NULL );

};

inline BFDate operator-( const BFDate& lhs, long cDays )
{
   return( BFDate( lhs ) -= cDays );
}

inline long operator-( const BFDate& lhs, const BFDate& rhs )
{
   // subtract two BFDate objects to determine the number of days betwixt 'em
//CP20030122   assert( lhs != BFDate::lowDate() && rhs != BFDate::lowDate() );
//CP20030122   assert( lhs != BFDate::highDate() && rhs != BFDate::highDate() );
   return( lhs.days_ - rhs.days_ );
}

inline BFDate operator+( const BFDate& lhs, long cDays )
{
   return( BFDate( lhs ) += cDays );
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/bfdate.hpp-arc  $
//
//   Rev 1.6   Jan 27 2003 14:49:30   PURDYECH
//Little fixes for backward compatibility
//
//   Rev 1.5   Jan 07 2003 10:12:02   PURDYECH
//Added comments.
//Added support for DF_DISPLAY.
//
//   Rev 1.4   Oct 09 2002 17:41:10   PURDYECH
//New PVCS Database
//
//   Rev 1.3   Jul 09 2002 13:14:24   DINACORN
//File had an absurd last-update time of December 18, 2007
//
//   Rev 1.2   Jul 09 2002 12:31:16   PURDYECH
//Infrastructure Changeover
//
//   Rev 1.1   Jul 05 2002 11:49:36   PURDYECH
//Infrastructure Fixup ... no more ICU!
//
