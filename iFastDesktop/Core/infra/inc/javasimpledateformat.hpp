#ifndef JAVASIMPLEDATEFORMAT_HPP
#define JAVASIMPLEDATEFORMAT_HPP
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


#ifndef COMMONPORT_H
    #include "commonport.h"
#endif

#ifndef DSTRING_HPP
    #include "dstring.hpp"
#endif

#ifndef JAVADATE_HPP
#include "javadate.hpp"
#endif

class JavaLocale;
class ClientLocale;
class CriticalSectionLock;

#ifndef SMPDTFMT_H
#include <smpdtfmt.h>
#endif


#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

namespace icu_3_6
{
   class SimpleDateFormat;
}


class DICORE_LINKAGE JavaSimpleDateFormat
{

// Implementation
public:
   // Start with 1 (0 reserved)
   enum {
            JAVASIMPLEDATEFORMAT_JNI_EXCEPTION_LOCATE = 1,
            JAVASIMPLEDATEFORMAT_JNI_EXCEPTION_EXECUTE = 2,
            JAVASIMPLEDATEFORMAT_ICU_ERROR = 3
        } ElementalCondition;

   /**
    * constructor
    * 
    * @param bool - specify whether this object should be threadsafe
    */
   JavaSimpleDateFormat( bool = false );

   /**
    * constructor
    * 
    * @param DString - a pattern string (see ICU's SimpleDateFormat)
    * @param JavaLocale - this localizes the date format
    * @param bool - specify whether this object should be threadsafe
    */
   JavaSimpleDateFormat( const DString&, const JavaLocale&, bool = false );

   /**
    * constructor
    * 
    * @param DString - a pattern string (see ICU's SimpleDateFormat)
    * @param ClientLocale - this localizes the date format
    * @param bool - specify whether this object should be threadsafe
    */
   JavaSimpleDateFormat( const DString&, const ClientLocale&, bool = false );

   /**
    * destructor
    */
   virtual ~JavaSimpleDateFormat();
   
   /**
    * copy constructor
    * 
    * @param copy
    */
   JavaSimpleDateFormat( const JavaSimpleDateFormat & copy );

   /**
    * constructs a date format object for the US locale;
    * the caller is responsible for deleting the object
    * 
    * @param DString - a pattern string
    * @param bool - specify whether this object should be threadsafe
    *
    * @return - a US date format object
    */
   static JavaSimpleDateFormat * US(const DString&, bool = false );

   /**
    * formats a JavaDate
    * 
    * @param dateToFormat
    *
    * @return - the date string
    */
   DString format( JavaDate * dateToFormat );

   /**
    * formats a JavaDate
    * 
    * @param JavaDate
    * @param DString - the location to put the formatted date string
    * @return - the date string
    */
   DString &format( JavaDate&, DString& );

   /**
    * compares this JavaSimpleDateFormat with the parameter
    * 
    * @param JavaSimpleDateFormat - second object of the comparison
    *                               operation
    *
    * @return - true, if equal
    *           false, otherwise
    */
   bool equals( JavaSimpleDateFormat * );

   /**
    * parses a string, creating a JavaDate
    * 
    * @param const DString & - a date string to parse
    *
    * @return a pointer to the new JavaDate
    */
   JavaDate * parse( const DString & );

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

// Attributes
private:
    icu_3_6::SimpleDateFormat * simpleDateFormat;
    // Constructor allows for error codes, so functions will check and 
    //   if error happened during construction, throw ElementalConditionException
    enum UErrorCode errorConstruct;
    CriticalSectionLock *m_pLock;
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
// $Log:   Y:/VCS/iFastAWD/inc/javasimpledateformat.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:06   kovacsro
//Initial revision.
// 
//    Rev 1.16   May 18 2001 14:39:42   dt24433
// Switched to use Guard/CriticalSectionLock from CriticalSection\MutexSemaphore.
// 
//    Rev 1.15   Jan 08 2001 14:56:24   dt24433
//  
// 
//    Rev 1.14   Jun 05 2000 07:42:16   dtwk
// Add thread-safety flag
// 
//    Rev 1.13   Jun 01 2000 14:39:26   DT14177
// added & edited javadoc comments
// 
//    Rev 1.12   May 26 2000 20:26:40   DT14177
// Added ClientLocale support
// 
//    Rev 1.11   10 May 2000 12:07:48   dt20842
// Removed unneeded static JavaSimpleDateFormat
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
// Removed java dependancy (compile/link) when using dicore
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