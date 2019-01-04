#ifndef JAVANUMBERFORMAT_HPP
#define JAVANUMBERFORMAT_HPP
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

#include <numfmt.h>

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

// Forward references
class CriticalSectionLock;
class JavaNumber;
class JavaDecimalFormat;

class DICORE_LINKAGE JavaNumberFormat
{

// Implementation
public:
   // Start with 1 (0 reserved)
   enum {
          JAVANUMBERFORMAT_ICU_ERROR = 1
        } ElementalCondition;

   /**
    * destructor
    */
   virtual ~JavaNumberFormat();

   /**
    * constructs a JavaNumberFormat with the default
    * locale
    * 
    * @param threadSafetyFlag
    *               - determines whether to run in thread-safe mode.
    * @return JavaNumberFormat
    */
   static JavaNumberFormat * getInstance( bool threadSafetyFlag = false );

   /**
    * constructs a JavaNumberFormat using the locale
    * parameter
    * 
    * @param JavaLocale
    * @param threadSafetyFlag
    *                   - determines whether to run in thread-safe mode.
    * @return JavaNumberFormat
    */
   static JavaNumberFormat * getInstance( JavaLocale*, bool threadSafetyFlag = false );

   /**
    * constructs a JavaNumberFormat using the locale
    * associated with the ClientLocale parameter
    * 
    * @param ClientLocale *
    *
    * @return JavaNumberFormat *
    */
   static JavaNumberFormat * getInstance( const ClientLocale*, bool threadSafetyFlag = false );

   /**
    * used to construct a default JavaDecimal object
    * 
    * @param threadSafetyFlag
    *               - determines whether to run in thread-safe mode.
    * @return JavaDecimalFormat *
    */
   static JavaDecimalFormat * getNumberInstance( bool threadSafetyFlag = false );

   /**
   * used to construct a JavaDecimal object for the specified locale
    * 
    * @param JavaLocale
    * @param threadSafetyFlag
    *                   - determines whether to run in thread-safe mode.
    * @return JavaDecimalFormat *
    */
   static JavaDecimalFormat * getNumberInstance( JavaLocale *, bool threadSafetyFlag = false );

   /**
   * used to construct a JavaDecimal object for the specified ClientLocale
    * 
    * @param JavaLocale
    * @param threadSafetyFlag
    *                   - determines whether to run in thread-safe mode.
    * @return JavaDecimalFormat *
    */
   static JavaDecimalFormat * getNumberInstance( const ClientLocale *, bool threadSafetyFlag = false );

   /**
    * constructs a JavaNumberFormat with the default
    * locale with a percent format
    * 
    * @param threadSafetyFlag
    *               - determines whether to run in thread-safe mode.
    * @return JavaNumberFormat *
    */
   static JavaNumberFormat * getPercentInstance( bool threadSafetyFlag = false );

   /**
    * constructs a JavaNumberFormat with the default
    * locale with a currency format
    * 
    * @param threadSafetyFlag
    *               - determines whether to run in thread-safe mode.
    * @return JavaNumberFormat *
    */
   static JavaNumberFormat * getCurrencyInstance( bool threadSafetyFlag = false );

   /**
    * determines whether two JavaNumber objects are equal
    * in value
    * 
    * @param JavaNumberFormat
    * @return - true, if equal
    *         - false, otherwise
    */
   bool equals(JavaNumberFormat*);

   /**
    * formats a text string based on the value of the
    * double sent to it.
    * 
    * @return the formatted number
    */
   const I_STRING format(double);

   /**
    * formats a text string based on the value of the
    * long sent to it.
    * 
    * @return the formatted number
    */
   const I_STRING format(long);

   /**
    * parses the string passed and stores the result
    * in the JavaNumber parameter
    * 
    * @param string - where to store the result
    * @param number
    */
   void parse(const I_STRING & string, JavaNumber &number);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   int getMaximumFractionDigits(void);
   
   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   int getMaximumIntegerDigits(void);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   int getMinimumFractionDigits(void);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   int getMinimumIntegerDigits(void);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void setMaximumFractionDigits(int newval);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void setMaximumIntegerDigits(int newval);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void setMinimumFractionDigits(int newval);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void setMinimumIntegerDigits(int newval);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   bool isParseIntegerOnly(void);

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   void setParseIntegerOnly(bool mode);
   
   /**
    * 
    * @return 
    */
   const NumberFormat * const getParentClassPointer()
   {
      return m_numberFormat;
   }

private:
   NumberFormat * m_numberFormat;
   CriticalSectionLock *m_pLock;

   JavaNumberFormat( bool threadSafetyFlag = false );
   JavaNumberFormat( NumberFormat * parm, bool threadSafetyFlag = false )
   {
      m_numberFormat = parm;
   }
   JavaNumberFormat( JavaLocale *pJavaLocale, bool threadSafetyFlag = false );
   JavaNumberFormat( const ClientLocale *pClientLocale, bool threadSafetyFlag = false );
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
// $Log:   Y:/VCS/iFastAWD/inc/javanumberformat.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:06   kovacsro
//Initial revision.
// 
//    Rev 1.14   May 18 2001 14:42:24   dt24433
//  
// 
//    Rev 1.13   Jan 08 2001 14:56:22   dt24433
// Made ClientLocale parms const
// 
//    Rev 1.12   Jun 06 2000 15:02:48   DT14177
// fixed a compile problem
// 
//    Rev 1.11   Jun 06 2000 13:08:24   DT14177
// added javadoc comments
// 
//    Rev 1.10   Jun 05 2000 07:42:12   dtwk
// Add thread-safety flag
// 
//    Rev 1.9   May 26 2000 20:26:38   DT14177
// Added ClientLocale support
// 
//    Rev 1.8   Apr 11 2000 16:01:14   DT14177
// added static method JavaDecimalFormat * JavaNumberFormat::getNumberInstance( JavaLocale * )
// 
//    Rev 1.7   Apr 11 2000 11:00:44   DT14177
// remove jni
// 
//    Rev 1.6   Apr 10 2000 16:38:56   DT14177
// ICU syncup
// 
//    Rev 1.5   Jun 06 1999 13:24:04   DTWK
// Minor tweaks
// 
//    Rev 1.4   Jun 01 1999 17:22:40   DTWK
//  
// 
//    Rev 1.3   May 12 1999 09:23:16   DT20842
// Added elemental conditions
// 
//    Rev 1.2   Apr 08 1999 13:02:26   DMUM
// Added import/export macros
//
//    Rev 1.1   Apr 02 1999 11:26:36   DT20842
// Removed java dependancy (compile/link) when using dicore
//
//    Rev 1.0   Mar 04 1999 14:41:20   DTWK
//
//
//    Rev 1.0   Mar 01 1999 13:50:48   MarkT
//
//
//
#endif