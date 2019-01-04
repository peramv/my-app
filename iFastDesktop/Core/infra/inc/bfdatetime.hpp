#ifndef BFDATETIME_HPP
#define BFDATETIME_HPP

/** 
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

/**@pkg DITABUSCORE */    

#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef TIME_H
#include <time.h>
#define TIME_H
#endif

#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

#ifndef INCLUDED_STRING
#include <string>
#define INCLUDED_STRING
#endif

#ifndef DDATE_HPP
#include "DDate.hpp"
#endif

//use namespace std for the Standard C++ library
using namespace std;

//forward declares


// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

class DITABUSCORE_LINKAGE BFDateTime
{
            // %BEGIN_INTERFACE%
            
            public://data


            public: //methods

                                // Class-Level Members
            static void   asDisplay( DString& strDateOut );//returns the current date in the format DF_FSMMDDCCYY e.g 04/20/1998
            static bool   getNextBusinessDay( DString& strDateOut, DDate::DATE_FORMAT dfFormat = DDate::DF_NULL );
            static time_t getCurrentDateTime(void);
            static bool   getCurrentDateTime( DString& strDateOut, DString& strTimeOut, DDate::DATE_FORMAT dfFormat = DDate::DF_NULL );
            static bool   getCurrentDate( DString& strDateOut, DDate::DATE_FORMAT dfFormat = DDate::DF_NULL );
            static bool   getCurrentTime( DString& strTimeOut );

            // The getProcDateFromI12() method retrieves the the current processing date, next processing date,
            // and the JMU006 nigtly status code off of the I12 DB2 table.  The current processing date and next processing date
            // have be pre-adjusted for weekends and holidays and whether or not the nightly jobs are in process.
            // The JMU status code is mainly used for purchase ACH edits.

            static bool getProcessingDatesAndStatusCode( DString& strProcDate, DString& strNextBusDate,
                                                         DString& strStatusCode, DDate::DATE_FORMAT dfFormat = DDate::DF_NULL );
            // The "getCalendarAgeInYearsMonthsDays" function computes calendar age in years, months, and days
            // between two dates.  User supplies a begin date (i.e. birthdate) and an ending or calc date.  The
            // dates must be valid and in one of the recognized BFDateTime formats.  The calc date must be
            // greater than the birth or begin date.  The last three int parms are user supplied and used to
            // return the calendar age in years, months and days.

            static bool getCalendarAgeInYearsMonthsDays( const DString &strBirthDate, const DString &strCalcDate,
                                                         int &nAgeInYears, int &nAgeInMonths, int &AgeInDays );

            static DString getJulianDate( const DString& strDateIn );

            static bool addYears( const DString& strDateIn, DString& strDateOut, int nYears = 1 );            
            static bool addDays( const DString& strDateIn, DString& strDateOut, int nDays = 1 );
            static bool subtractDays( const DString& strDateIn, DString& strDateOut, int nDays = 1 );            

            static bool addBusinessDays( const DString& strDateIn, DString& strDateOut, int nDays =1 );
            static bool subtractBusinessDays(  const DString& strDateIn, DString& strDateOut, int nDays = 1 );
            static bool isValidBusinessDay( const DString& strDate );
            static bool isMonthDayComboValid( const DString& strMonthDay );
            static int  compareMonthDayCombo( const DString& strMonthDay1, const DString& strMonthDay2 );
            static int  compareDates( const DString& strDate1, const DString& strDate2 );
            static int  compareTimes( const DString& strTime1, const DString& strTime2 );
            
            // %END_INTERFACE%


        private: //data
            
           //The following data members are used for keeping the
           //NT workstation date/time values in sync with the 
           //TA2000 mainframe date/time values
           static unsigned long _ulStartMilliseconds;
           static bool _fInitialized;
           static int _nStartYear;
           static int _nStartMonth;
           static int _nStartDay;
           static int _nStartHour;
           static int _nStartMinute;
           static int _nStartSecond;
           static int _nStartMilliSecond;
           //end sync-up values

        private: //methods

            BFDateTime();
            ~BFDateTime();

            BFDateTime( const BFDateTime &copy );
            BFDateTime& operator=( const BFDateTime& copy );
            static bool   _isValidBusinessDay( long lDateOffset );
};

#endif

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
// $Log:   Y:/VCS/iFastAWD/inc/bfdatetime.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:08   kovacsro
//Initial revision.
// 
//    Rev 1.2   23 Oct 2000 12:40:42   dt14177
// cleanup
// 
//    Rev 1.1   Nov 11 1999 16:31:06   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0.1.2   Oct 04 1999 12:33:26   DT29758
// Added method getCurrentDateTime() that
// returns a the current time from the host
// in a time_t format
// 
//    Rev 1.0.1.1   Jul 22 1999 13:35:40   DT22388
// Performed code clean-up and added #undefs
// for the substitution string i.e. $strParentImplClass$.
// Also, added #includes for test classes.
// 
// 
//    Rev 1.0.1.0   Jul 19 1999 17:49:40   DT22388
// Performed some code clean-up
// 
//    Rev 1.0   Jun 21 1999 17:06:46   DT22388
//  
// 
//    Rev 1.15   Apr 20 1998 10:26:48   dt22388
// Removed any non year 2K compliant
// date formats.  Removed public constuctor.
// Made all methods static.  Changed BFHolidayList
// to use the new view1136 to retrieve a list of DST
// holidays.  Made offset methods private.  Enhanced
// overall performance.
// 
//    Rev 1.14   Apr 02 1998 09:48:00   dt22388
// Performed code clean-up on the isValidDate()
// method and the isHoliday() method.  Also enhanced
// BFdatetime methods to handle a date format
// of CCYYMMDD. And removed the old getprocdatefromI12
// method.
// 
//    Rev 1.13   Mar 26 1998 11:24:30   dmal
// changed BFholiday class to be a singleton to
// enhance performance
// 
//    Rev 1.12   Mar 17 1998 17:04:36   DT21815
// Changed some method arguments to accept const string&
// instread of string (by value).
// 
//    Rev 1.11   Feb 20 1998 10:03:14   dt22388
// Added two new methods:  
//      subtractBusinessDays( )
//      compareMonthDayCombo( )
// for financials
// 
//    Rev 1.10   Jan 13 1998 09:41:26   dt22388
// Added method addBusinessDays() that
// will add days to the date passed in.  The method
// adds a day only if it is a valid business day.

