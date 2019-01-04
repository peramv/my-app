#ifndef JAVADATEFORMAT_HPP
#define JAVADATEFORMAT_HPP
#pragma message( "including "__FILE__ )

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


#ifndef JAVADATE_HPP
   #include "javadate.hpp"
#endif


#ifndef DATEFMT_H
   #include <datefmt.h>
#endif

class JavaLocale;
class ClientLocale;

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class DICORE_LINKAGE JavaDateFormat
{

// Implementation
public:

   // Start with 1 (0 reserved)
   enum {
            JAVADATEFORMAT_JNI_EXCEPTION_LOCATE = 1,
            JAVADATEFORMAT_JNI_EXCEPTION_EXECUTE = 2
        } ElementalCondition;
   ~JavaDateFormat();

   /**
    * Creates a dateTime formatter that uses the
    * short style for both the date (MM/DD/YY) and the time
    * with the default locale from the host system
    *
    * @return a JavaDateFormat object
    */
   static JavaDateFormat getInstance(void);

   /**
    * Creates a  date formatter that uses the
    * medium style for both the date (e.g., Jan 3, 1990) and the time
    * with the default locale from the host system
    *
    * @return a JavaDateFormat object
    */
   static JavaDateFormat getDateInstance(void);

   /**
    * Creates a  date formatter that uses the
    * medium style for both the date (e.g., Jan 3, 1990) and the time
    *
    * @param loc    - the locale with which to initialize the DateFormat
    *                 object
    *
    * @return a JavaDateFormat object
    */
   static JavaDateFormat getDateInstance( JavaLocale * loc );


   /**
    * Creates a  dateTime formatter that uses the
    * medium style for both the date (e.g., Jan 3, 1990) and the time
    *
    * @param loc    - the locale with which to initialize the DateFormat
    *                 object
    *
    * @return a JavaDateFormat object
    */
   static JavaDateFormat getDateInstance( ClientLocale * loc );
   //static JavaDateFormat* getDateInstance(int style, JavaLocale* aLocale);
   //static JavaDateFormat* getDateTimeInstance(int datestyle, int timestyle, JavaLocale* aLocale);

   /**
    * Creates a dateTime formatter that uses the
    * medium style for both the date (e.g., Jan 3, 1990) and the time
    * with the default locale from the host system
    *
    * @return a JavaDateFormat object
    */
   static JavaDateFormat getDateTimeInstance( void );

   /**
    * formats a JavaDate
    *
    * @param dateToFormat
    *
    * @return - the date string
    */
   const DString format( JavaDate * dateToFormat );

   /**
    * compares this JavaDateFormat with the parameter
    *
    * @param JavaDateFormat
    *
    * @return - true, if equal
    *           false, otherwise
    */
   bool equals( JavaDateFormat & );

   /**
    * parses a string, creating a JavaDate
    *
    * @param const DString & - a date string
    *
    * @return a pointer to the new JavaDate
    */
   JavaDate * parse( const DString & );

   /**
    * checks whether the isLenient flag is set to allow
    * flexible interpretation of date formats
    *
    * @return - true, if the lenient flag is set
    *           false, otherwise
    */
   bool isLenient( void );

   /**
    * sets the isLenient flag
    *
    * @param lenient
    */
   void setLenient( bool lenient );


private:


   // we don' wan' no steenkeen' shallow copies
    JavaDateFormat( JavaDateFormat & );
    JavaDateFormat & operator=( JavaDateFormat & );

    JavaDateFormat( );
    JavaDateFormat( DateFormat *dateFormatIn );
    static int defaultStyle;

    DateFormat *dateFormat;

// Attributes
private:
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
// $Log:   Y:/VCS/iFastAWD/inc/javadateformat.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:00   kovacsro
//Initial revision.
// 
//    Rev 1.11   Aug 09 2001 10:07:06   DT11159
// Removed spaces inside preprocessor directives.
//
//    Rev 1.10   Jun 01 2000 14:39:22   DT14177
// added & edited javadoc comments
//
//    Rev 1.9   Jun 01 2000 12:13:30   DT14177
// added javadoc comments
//
//    Rev 1.8   May 26 2000 20:26:32   DT14177
// Added ClientLocale support
//
//    Rev 1.7   Apr 10 2000 16:57:32   dtwk
// Change #includes of icu classes to <> instead of ""
//
//    Rev 1.6   10 Apr 2000 10:30:54   dt20842
// Switch to ICU and clean up error handling
//
//    Rev 1.5   Jun 08 1999 14:12:32   DT14177
// Added stuff needed by dDate.
//
//    Rev 1.4   Jun 01 1999 17:22:10   DTWK
//
//
//    Rev 1.3   May 12 1999 09:22:00   DT20842
// Added elemental conditions
//
//    Rev 1.2   Apr 08 1999 13:02:16   DMUM
// Added import/export macros
//
//    Rev 1.1   Apr 02 1999 11:26:24   DT20842
// Removed java dependancy (compile/link) when using dicore
//
//    Rev 1.0   Mar 04 1999 14:40:22   DTWK
//
//
//    Rev 1.0   Mar 01 1999 13:50:48   MarkT
//
//
//
#endif