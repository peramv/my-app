#ifndef JAVAGREGORIANCALENDAR_HPP
#define JAVAGREGORIANCALENDAR_HPP
#  pragma message( "including "__FILE__ )

/** 
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

/**@pkg DICORE */    


#ifndef DSTRING_HPP
    #include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
    #include "commonport.h"
#endif

class JavaLocale;
class ClientLocale;

#ifndef JAVADATE_HPP
   #include "javadate.hpp"
#endif


#ifndef GREGOCAL_H
   #include <gregocal.h>
#endif


// Values to be used for Querying elements of the Date
namespace DICalendar
{
   enum Value
   {
       ERA,
       YEAR,
       MONTH,
       WEEK_OF_YEAR,
       WEEK_OF_MONTH,
       DAY_OF_MONTH,
       DAY_OF_YEAR,
       DAY_OF_WEEK,
       DAY_OF_WEEK_IN_MONTH,
       AM_PM,
       HOUR,
       HOUR_OF_DAY,
       MINUTE,
       SECOND,
       MILLISECOND
   };
}

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class DICORE_LINKAGE JavaGregorianCalendar
{

// Implementation
public:

   // Start with 1 (0 reserved)
   enum {
            JAVAGREGORIANCALENDAR_JNI_EXCEPTION_LOCATE = 1,
            JAVAGREGORIANCALENDAR_JNI_EXCEPTION_EXECUTE = 2,
            JAVAGREGORIANCALENDAR_ICU_ERROR = 3
        } ElementalCondition;


   /**
    * constructor
    * 
    * @param JavaLocale *
    */
   JavaGregorianCalendar( JavaLocale * );
   
   /**
    * constructor
    * 
    * @param ClientLocale *
    */
   JavaGregorianCalendar( ClientLocale * );

   /**
    * destructor
    */
   virtual ~JavaGregorianCalendar();

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   bool before( JavaGregorianCalendar * );

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   bool after( JavaGregorianCalendar * );

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   bool isLeapYear( int year );

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void add( int field, int amount );

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void roll( int field, bool up );

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   bool equals( JavaGregorianCalendar * );

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   int  get( int DateElement );

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void setTime( JavaDate & );

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void set( int field, int value );

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   JavaDate getTime();
   

protected:
   void computeFields( void );
   void computeTime( void );

private:
   GregorianCalendar *gregorianCalendar;

    // Constructor allows for error codes, so functions will check and 
    //   if error happened during construction, throw ElementalConditionException
    enum UErrorCode errorConstruct; 


// Attributes
private:
   JavaGregorianCalendar();
   const JavaGregorianCalendar & operator= ( const JavaGregorianCalendar & );
   JavaGregorianCalendar( const JavaGregorianCalendar & );
};
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
// $Log:   Y:/VCS/iFastAWD/inc/javagregoriancalendar.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:02   kovacsro
//Initial revision.
// 
//    Rev 1.12   Jun 06 2000 15:37:42   DT14177
// added javadoc comments
// 
//    Rev 1.11   May 26 2000 20:26:36   DT14177
// Added ClientLocale support
// 
//    Rev 1.10   Apr 10 2000 16:57:34   dtwk
// Change #includes of icu classes to <> instead of ""
// 
//    Rev 1.9   10 Apr 2000 10:30:56   dt20842
// Switch to ICU and clean up error handling
// 
//    Rev 1.8   Sep 17 1999 13:39:04   DT14177
// fix compile problem
// 
//    Rev 1.6   Jul 16 1999 11:26:44   DT14177
// Added getOffset() to dDate and minus() to JavaDate
// 
//    Rev 1.5   Jun 21 1999 13:36:16   DT14177
// Hid the default constructor, operator=, copy constructor
// 
//    Rev 1.4   Jun 01 1999 17:22:18   DTWK
//  
// 
//    Rev 1.3   May 12 1999 09:22:04   DT20842
// Added elemental conditions
// 
//    Rev 1.2   Apr 08 1999 13:02:18   DMUM
// Added import/export macros
//
//    Rev 1.1   Apr 02 1999 11:26:26   DT20842
// Removed java dependancy (compile/link) when using dicore
//
//    Rev 1.0   Mar 04 1999 14:40:36   DTWK
//
//
//    Rev 1.0   Mar 01 1999 13:50:48   MarkT
//
//
//
#endif