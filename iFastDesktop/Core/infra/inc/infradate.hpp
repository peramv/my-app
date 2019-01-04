#ifndef INFRADATE_HPP
#define INFRADATE_HPP

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

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef GREGOCAL_H
   #include <gregocal.h>
#endif

#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
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

class DateFormat;
/**@#+*/

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * The Date class provides commonly used non static
 * functions for date handling, including formatting.        
 *
 * The class has some
 * international capability but is based primarily on a Gregorian
 * Calendar. Gregorian only methods are currently marked with
 * Gregorian as part of the name.
 *
 */


class DICORE_LINKAGE Infra::Date
{
public:

   enum {
            ICU_ERROR = 1
        } ElementalCondition;

   /** Default Constructor */
   Date();
   
   /** Overloaded Constructor 
    *  @param strDate - DString containing a date in a valid 
    *  format */
   Date( const DString & strDate );
   
   /** Copy Constructor */
   Date( const Date & copy );
   
   /** Assignment operator */
   Date & operator=( const Date & copy );

   /** Destructor */
   virtual ~Date();
   
   /**
    * greater than operator
    * 
    * @param right
    * @return 
    */
   bool operator>( Date & right );

   /**
    * less than operator
    * 
    * @param right
    * @return 
    */
   bool operator<( Date & right );

   /**
    * equal comparison operator
    * 
    * @param right
    * @return 
    */
   bool operator==( Date & right );

   /**
    * greater than or equal comparison operator
    * 
    * @param right
    * @return 
    */
   bool operator>=( Date & right );
   /**
    * less than or equal comparison operator
    * 
    * @param right
    * @return 
    */
   bool operator<=( Date & right );

   /**
    * unequal comparison operator
    * 
    * @param right
    * @return 
    */
   bool operator!=( Date & right );

   /** (Gregorian only)Retrieves the Gregorian date from the
    *     Infra::Date class in same format as previously set or
    *     constructed 
    *  @returns - The Date formatted in a DString */
   DString getDate( void ) const;

   /** (Gregorian only)Retrieves the Gregorian date from the
    *     Infra::Date class in the specified format
    *  @returns - The Date formatted in a DString */
   DString getDate( const DString & format ) const;

   /** (Gregorian only)Sets the Gregorian date of the Infra::Date class 
    *  @returns true if successful */
   bool setDate( const DString& strDate );

   /** (Gregorian only)Retrieves the day of year from the Infra::Date
    *     class 
    *  @returns - the day as an integer range 1 to 365 (366 for
    *     leap year) */
   int getDayOfYear( void ) const;

   /** (Gregorian only)Retrieves the year from the Infra::Date class 
    *  @returns - the year as an integer*/
   int getYear( void )const;

   /** (Gregorian only)Retrieves the month from the Infra::Date class 
    *  @returns - the month as an integer (1-based)*/
   int getMonth( void )const
   {
      return _nMonth + 1;
   }

   /** (Gregorian only)Retrieves the day of the month from the
    *     Infra::Date class 
    *  @returns - the day as an integer (1-based) */
   int getDayOfMonth( void )const
   {
      return _nDayOfMonth;
   }

   /** (Gregorian only)Method determines the date format of a
    *     Infra::Date object.
    *  @returns = the enumerated date format type */
   const DString & getGregorianDateFormat( void )const;

   /** (Gregorian only)Method determines if the date calling it
    *     is a valid date
    *  @returns - true if is the date is valid */
   bool isValidGregorianDate( void );

   /** (Gregorian only)Method that will add an integer number of 
    *     days to a Infra::Date
    *  @param nDays - number of days to add to Infra::Date
    *  @returns - true if successful */
   bool addDays( const int nDays );

   /** (Gregorian only)Method that will subtract an integer
    *     number of days from a Infra::Date
    *  @param nDays - number of days to subtract to Infra::Date
    *  @returns - true if successful */
   bool subtractDays( const int nDays );

   /** (Gregorian only)Method that will add an integer number of 
    *     years to a Infra::Date
    *  @param nYears - number of years to add to Infra::Date
    *  @returns - true if successful */
   bool addYears( const int nYears );

   friend Infra::DateHelper;

      
private: //Methods - from old DDate implementation
   
   /**
    * returns the normalized representation of the date
    * as an offset from 01-01-1970
    * 
    * @return 
    */
   double getDateAsDouble( void ) const
   {
      return _date;
   }

   /** (Gregorian only)Sets the Gregorian date of the Infra::Date class 
    *  @returns true if successful */
   bool setDate( double date );

   /** Fills the _nDayOfMonth, _nDayOfYear, _nMonth, _nYear 
    *     attributes of a Infra::Date object */
   void _splitDateToParts( void );
   
   /** Fill the _strDate attribute of a Infra::Date object based on 
    *     format of _dfFormat) */
   void _buildDateFromParts( void );
   
   /** Fills the _strDate attribute of Infra::Date object base on value
    *     of _nDayOfYear */
   void _getDateFromDayOfYear( void );
   
   /** Fills the _DayOfYear attribute of Infra::Date object base on
    *     value of _strDate */
   void _getDayOfYearFromDate( void );

   /**
    * sets the time
    * 
    * @param lTime  the time to be set as an offset from 2400
    */
   void _setTime( double lTime )
   {
	   _date = lTime;
   }

   /**
    * sets the time and other fields derived from it
    * 
    * @param lTime  the time to be set as an offset from 2400
    */
   void setTime( double lTime );

   /**
    * sets the date
    * 
    * @param ltime  date to set (offset from 01-01-1970)
    */
   void set( double ltime );

   /**
    * sets the date
    * 
    * @param ltime  date to set (offset from 01-01-1970)
    */
   void set( const DString & date );

   /**
    * used internally to set Udate stuff after
    * a datestring change.
    */
   void setNormalizedDate( void );

   void setUDate( void );

private://Data

   double             _date;   // offset from 01-01-1970
   DString            _dfFormat;   

   int                _nDayOfMonth;
   int                _nDayOfYear;
   int                _nMonth;
   int                _nYear;
   DString     _strDate;

   TRACER_CLASS_VARIABLE

};

#ifndef INFRADATEHELPER_HPP
#include "infradatehelper.hpp"
#endif

#endif  // INFRADATE_HPP

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
// $Log:   Y:/VCS/iFastAWD/inc/infradate.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:42   kovacsro
//Initial revision.
//
//   Rev 1.0   28 Dec 2000 08:58:38   dt14177
// 

