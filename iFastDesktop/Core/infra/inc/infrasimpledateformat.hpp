#ifndef INFRASIMPLEDATEFORMAT_HPP
#define INFRASIMPLEDATEFORMAT_HPP
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

class CriticalSectionLock;
class DString;
namespace icu_3_6
{
   class SimpleDateFormat;
}
/**@#+*/


#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif


/**
 * A SimpleDateFormat is used to format dates into strings and
 * is locale-specific.  Format strings are used to specify how
 * to format date strings.
 */

class DICORE_LINKAGE Infra::SimpleDateFormat
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
    * @param bool - specify whether this object should be 
    *               threadsafe
    */
   SimpleDateFormat( bool = false );

   /**
    * constructor
    * 
    * @param DString - a pattern string (see ICU's 
    *                  SimpleDateFormat)
    * @param Locale - this localizes the date format
    * @param bool - specify whether this object should be 
    *               threadsafe
    */
   SimpleDateFormat( const DString &, 
                     Infra::Locale &, 
                     bool = false );

   /**
    * constructor
    * 
    * @param DString - a pattern string (see ICU's 
    *                  SimpleDateFormat)
    * @param ClientLocale - this localizes the date format
    * @param bool - specify whether this object should be 
    *               threadsafe
    */
   SimpleDateFormat( const DString &, 
                     Infra::ClientLocale&, 
                     bool = false );

   /**
    * destructor
    */
   virtual ~SimpleDateFormat();
   
   /**
    * copy constructor
    * 
    * @param copy
    */
   SimpleDateFormat( const SimpleDateFormat & copy );

   /**
    * constructs a date format object for the US locale;
    * the caller is responsible for deleting the object
    * 
    * @param DString - a pattern string
    * @param bool - specify whether this object should be 
    *               threadsafe
    *
    * @return - a US date format object
    */
   static SimpleDateFormat * US( const DString &, bool = false );

   /**
    * formats a DString date
    * 
    * @param dateToFormat
    *
    * @return - the date string
    */
   DString & format( DString & dateToFormat,
                     DString & result );

   /**
    * compares this SimpleDateFormat with the parameter
    * 
    * @param SimpleDateFormat - second object of the comparison
    *                               operation
    *
    * @return - true, if equal
    *           false, otherwise
    */
   bool equals( SimpleDateFormat * );

   /**
    * sets the isLenient flag
    * 
    * @param lenient
    */
   void setLenient( bool fLenient );

   /**
    * checks whether the isLenient flag is set to allow
    * flexible interpretation of date formats
    * 
    * @return - true, if the lenient flag is set
    *           false, otherwise
    */
   bool isLenient();

   friend Infra::DateHelper;

private: //Methods

   /**
    * formats a date
    * 
    * @param dateToFormat
    *
    * @return - the date string
    */
   DString format( double dateToFormat );

   /**
    * formats a date
    * 
    * @param - date
    * @param - DString - the location to put the formatted date 
    *                    string
    * @return - the date string
    */
   DString & format( double, DString& );

   /**
    * parses a string, creating a date
    * 
    * @param date    - the date to parse
    * @param isError - was the method able to parse the date
    * @return - a date
    */
   double parse( const DString & date,
                 bool & isError );

   SimpleDateFormat & operator=( const SimpleDateFormat & );

// Attributes
private:
    icu_3_6::SimpleDateFormat * _simpleDateFormat;

    // Constructor allows for error codes, so functions will check
    //  and if error happened during construction, throw
    //  an ElementalConditionException
    UErrorCode errorConstruct;
    CriticalSectionLock *m_pLock;

    TRACER_CLASS_VARIABLE
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
// $Log:   Y:/VCS/iFastAWD/inc/infrasimpledateformat.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:52   kovacsro
//Initial revision.
//
//   Rev 1.1   May 18 2001 14:23:54   dt24433
// 
//
//   Rev 1.0   28 Dec 2000 08:59:06   dt14177
// 
// 
//    Rev 1.14   Jun 05 2000 07:42:16   dtwk
// Add thread-safety flag
// 
//    Rev 1.13   Jun 01 2000 14:39:26   DT14177
// added & edited didoc comments
// 
//    Rev 1.12   May 26 2000 20:26:40   DT14177
// Added ClientLocale support
// 
//    Rev 1.11   10 May 2000 12:07:48   dt20842
// Removed unneeded static SimpleDateFormat
// 
//    Rev 1.10   Apr 10 2000 16:57:38   dtwk
// Change #includes of icu classes to <> instead of ""
// 
//    Rev 1.9   10 Apr 2000 10:31:00   dt20842
// Switch to ICU and clean up error handling
// 
//    Rev 1.8   Sep 03 1999 12:40:34   dtwk
// Add setLenient(), getLenient(), copy constructor
// 
//    Rev 1.7   Jun 06 1999 13:24:08   DTWK
// Minor tweaks
// 
//    Rev 1.6   Jun 01 1999 17:22:44   DTWK
//  
// 
//    Rev 1.5   May 12 1999 09:23:18   DT20842
// Added elemental conditions
// 
//    Rev 1.4   May 03 1999 12:30:14   DTWK
// Add new construtor  and parse() method
// 
//    Rev 1.3   Apr 08 1999 13:02:28   DMUM
// Added import/export macros
//
//    Rev 1.2   Apr 02 1999 11:26:38   DT20842
// Removed di dependancy (compile/link) when using dicore
//
//    Rev 1.1   Mar 23 1999 09:42:44   DT20842
// Changes for merge dicore and dilocal
//
//    Rev 1.0   Mar 11 1999 14:09:56   DTWK
//
//
//    Rev 1.0   Mar 10 1999 13:50:48   MarkT
//
//
//
#endif