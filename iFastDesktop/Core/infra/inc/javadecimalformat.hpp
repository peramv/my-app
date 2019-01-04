#ifndef JAVADECIMALFORMAT_HPP
#define JAVADECIMALFORMAT_HPP
#  pragma message( "including "__FILE__ )
/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999, 2000 by DST Systems, Inc.
 */

/** @pkg DICORE */

/**
 * FILE: javadecimalformat.hpp
 *
 * DESCRIPTION :
 *    temporary kludge: wrapper for Decimal Format so we
 * don't change the interface for our clients yet.
 *
 */

#ifndef DSTRING_HPP
    #include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
    #include "commonport.h"
#endif

#ifndef JAVADATE_HPP
#include "javadate.hpp"
#endif

#include <decimfmt.h> 

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

// Forward references
class CriticalSectionLock;
class JavaNumber;

class DICORE_LINKAGE JavaDecimalFormat : public DecimalFormat
{

// Implementation
public:

   enum
   {
      JAVADECIMALFORMAT_ICU_ERROR
   };

   /**
    * constructor
    * 
    * @param UErrorCode needed by Decimal Format constructor.
    * @param fThreadSafe
    */
   JavaDecimalFormat( UErrorCode &, bool fThreadSafe = false );

   /**
    * constructor from a parent class
    * 
    * @param dec
    * @param fThreadSafe
    */
   JavaDecimalFormat( DecimalFormat & dec, bool fThreadSafe = false );

   /**
    * copy constructor
    * 
    * @param copy
    */
   JavaDecimalFormat( const JavaDecimalFormat& copy );   

   /**
    * destructor
    */
   virtual ~JavaDecimalFormat();

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   DString format(double);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   DString& format( JavaNumber&, DString& );

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   bool equals(JavaDecimalFormat*);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   double parse( const DString& );

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void parse(const I_STRING & string, JavaNumber &number);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void applyPattern( const DString& );

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void applyLocalizedPattern( const DString& );

   void setDecimalFormatSybols( const DecimalFormatSymbols& symbols );

   DecimalFormatSymbols& getDecimalFormatSymbols( 
      DecimalFormatSymbols& symbols );

private:
   JavaDecimalFormat( const DString );
   JavaDecimalFormat();

// Attributes
private:
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
// $Log:   Y:/VCS/iFastAWD/inc/javadecimalformat.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:00   kovacsro
//Initial revision.
// 
//    Rev 1.11   May 18 2001 14:42:20   dt24433
// Switched to use Guard/CriticalSectionLock from CriticalSection\MutexSemaphore.
// 
//    Rev 1.10   Oct 10 2000 08:50:02   dt17817
// Add methods to get and set formatting symbols for databroker overrides
// 
//    Rev 1.9   Jun 06 2000 15:22:54   DT14177
// added javadoc comments
// 
//    Rev 1.8   Jun 05 2000 07:42:10   dtwk
// Add thread-safety flag
// 
//    Rev 1.7   May 26 2000 20:26:34   DT14177
// Added ClientLocale support
// 
//    Rev 1.6   Apr 11 2000 16:01:12   DT14177
// added static method JavaDecimalFormat * JavaNumberFormat::getNumberInstance( JavaLocale * )
// 
//    Rev 1.5   Apr 10 2000 16:38:50   DT14177
// ICU syncup
// 
//    Rev 1.4   Sep 09 1999 11:13:08   dtwk
// Remove setLenient() & isLenient()
// 
//    Rev 1.3   Sep 03 1999 12:40:30   dtwk
// Add setLenient(), getLenient(), copy constructor
// 
//    Rev 1.2   Jun 06 1999 13:23:54   DTWK
// Minor tweaks
// 
//    Rev 1.1   Jun 01 1999 17:22:14   DTWK
//  
// 
//    Rev 1.0   May 24 1999 10:26:26   DTWK
//  
//
//
#endif