#ifndef INFRAGREGORIANCALENDAR_HPP
#define INFRAGREGORIANCALENDAR_HPP
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
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/**@pkg DICORE */    

#ifndef GREGOCAL_H
   #include <gregocal.h>
#endif

#ifndef COMMONPORT_H
    #include "commonport.h"
#endif

#ifndef DSTRING_HPP
    #include "dstring.hpp"
#endif

#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif


/**@#-*/  // forward declarations
namespace Infra
{
   class Date;
   class DateHelper;
   class GregorianCalendar;
   class Locale;
   class ClientLocale;
};
/**@#+*/

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * A GregorianCalendar provides functionality to manipulate
 * and compare dates
 */
class DICORE_LINKAGE Infra::GregorianCalendar
{

// Implementation
public:

   // Start with 1 (0 reserved)
   enum {
            ICU_ERROR = 1
        } ElementalCondition;


   /**
    * constructor
    * 
    * @param DiLocale *
    */
   GregorianCalendar( const Locale * );
   
   /**
    * constructor
    * 
    * @param ClientLocale *
    */
   GregorianCalendar( const ClientLocale * );

   /**
    * destructor
    */
   virtual ~GregorianCalendar();

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   bool before( const GregorianCalendar * );

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   bool after( const GregorianCalendar * );

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
   bool equals( const GregorianCalendar * );

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
   void setTime( double );

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
   void set( int year, int month, int day_of_month )
   {
      _gregorianCalendar->set( year, month, day_of_month );
   }

   /**
    * see GregorianCalendar's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   double getTime();
   

protected:
   void computeFields( void );
   void computeTime( void );

private:
   ::GregorianCalendar * _gregorianCalendar;

    // Constructor allows for error codes, so functions will check and 
    //   if error happened during construction, throw ElementalConditionException
    enum UErrorCode errorConstruct; 

    TRACER_CLASS_VARIABLE;


// Attributes
private:
   GregorianCalendar();
   const GregorianCalendar & operator= ( 
                                     const GregorianCalendar & );
   GregorianCalendar( const GregorianCalendar & );
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
// $Log:   Y:/VCS/iFastAWD/inc/infragregoriancalendar.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:46   kovacsro
//Initial revision.
//
//   Rev 1.0   28 Dec 2000 08:58:52   dt14177
// 
// 

#endif // INFRAGREGORIANCALENDAR_HPP
