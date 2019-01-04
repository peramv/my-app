// JavaDecimalFormat Class Implementation
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : JavaDecimalFormat.hpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 10 March 1999
//
// ^CLASS  : JavaDecimalFormat
// ^PARENT : none
//
// ^CLASS DESCRIPTION :
//
// ^MEMBER VARIABLES :
//    private:
//  jmethodID jMidDecimalFormatformat;
//
//******************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include <srcprag.h>
#endif

#ifndef JAVADECIMALFORMAT_HPP
   #include "javadecimalformat.hpp"
#endif

#ifndef JAVALOCALE_HPP
   #include "javalocale.hpp"
#endif

#ifndef JAVANUMBER_HPP
   #include "javanumber.hpp"
#endif

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef DCFMTSYM_H
   #include <dcfmtsym.h>
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif


#ifdef _MSC_VER
   // Disable the following compiler warnings
   // 4800 forcing value to boolean (performance warning)
   #pragma warning( disable : 4800 )

#endif

const I_CHAR JAVADECIMALFORMAT_NAME[] = I_( "JavaDecimalFormat" );

MsgPair en_usJavaDecimalFormat[] = 
{
   { 
      JavaLocale::JAVALOCATE_ICU_ERROR,
      I_("ICU error has occurred with value %VALUE%."),
      I_("Check ICU Runtime Environment.")   
   }
};

Condition::mapCodePagesToLanguages languagesMapForJavaDecimalFormat[] =
{ 
   {
      I_( "C" ), en_usJavaDecimalFormat
   },

   // End slot marker
   {
      NULL, NULL

   }
};


// Class Implementation

// Public Default Constructor
JavaDecimalFormat::JavaDecimalFormat( UErrorCode & uec, bool fThreadSafe )
    : DecimalFormat( uec )
{
   if ( fThreadSafe )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }
}

JavaDecimalFormat::JavaDecimalFormat( DecimalFormat & dec, bool fThreadSafe )
   : DecimalFormat( dec )
{
   if ( fThreadSafe )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }
}


JavaDecimalFormat::~JavaDecimalFormat()
{
   if ( m_pLock )
   {
      delete m_pLock;
      m_pLock = 0;
   }
}


JavaDecimalFormat::JavaDecimalFormat( const JavaDecimalFormat& copy )
   : DecimalFormat( copy )
{
   if ( copy.m_pLock )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }
}


DString JavaDecimalFormat::format( double dNum )
{
   Guard crit( m_pLock );
   UnicodeString formatString;
   DecimalFormat::format( dNum, formatString );
   I_STRING iString;
   ICUStringtoIString( formatString, iString );
   return iString;
}


DString& JavaDecimalFormat::format( JavaNumber & javaNumber,
                                    DString & dstrRet )
{
   Guard crit( m_pLock );
   UnicodeString formatString;
   DecimalFormat::format( javaNumber.doubleValue(), formatString );
   I_STRING iString;
   ICUStringtoIString( formatString, iString );
   dstrRet = iString;
   return dstrRet;
}


bool JavaDecimalFormat::equals( JavaDecimalFormat *pJavaDecimalFormat)
{
   Guard crit( m_pLock );
   return ( *this == *pJavaDecimalFormat );
}


double JavaDecimalFormat::parse( const DString& dstrNum )
{
   Guard crit( m_pLock );
   UnicodeString uString( dstrNum.c_str() );
   Formattable fmtbl;
   UErrorCode error = U_ZERO_ERROR;
   DecimalFormat::parse( uString, fmtbl, error );
   if ( U_FAILURE( error ) )
   {
      DStringA errorName( u_errorName( error ) );
      THROWELEMENTALIDI( JAVADECIMALFORMAT_NAME,
                         I_("JavaDecimalFormat::parse()"),
                         JavaDecimalFormat::JAVADECIMALFORMAT_ICU_ERROR,
                         languagesMapForJavaDecimalFormat,
                         DString( errorName ).c_str() );
   }
   double retVal;
   switch ( fmtbl.getType() )
   {
   case Formattable::kDouble:
      retVal = fmtbl.getDouble();
      break;
   case Formattable::kLong:
      retVal = fmtbl.getLong();
      break;
   }
   return retVal;
}


void JavaDecimalFormat::parse( const I_STRING & pszNumString, 
                               JavaNumber &number )
{
   Guard crit( m_pLock );
   UnicodeString uString( pszNumString.c_str() );
   Formattable fmtbl;
   UErrorCode error = U_ZERO_ERROR;
   DecimalFormat::parse( uString, fmtbl, error );
   if ( U_FAILURE( error ) )
   {
      DStringA errorName( u_errorName( error ) );
      THROWELEMENTALIDI( JAVADECIMALFORMAT_NAME,
                         I_("JavaDecimalFormat::parse()"),
                         JavaDecimalFormat::JAVADECIMALFORMAT_ICU_ERROR,
                         languagesMapForJavaDecimalFormat,
                         DString( errorName ).c_str() );
   }
   JavaNumber tmp( fmtbl.getDouble() );
   number = tmp;
}


void JavaDecimalFormat::applyPattern( const DString& dstrPattern )
{
   Guard crit( m_pLock );
   UnicodeString uString( dstrPattern.c_str() );
   UErrorCode error = U_ZERO_ERROR;
   DecimalFormat::applyPattern( uString, error );

   if ( U_FAILURE( error ) )
   {
      DStringA errorName( u_errorName( error ) );
      THROWELEMENTALIDI( JAVADECIMALFORMAT_NAME,
                         I_("JavaDecimalFormat::applyPattern()"),
                         JavaDecimalFormat::JAVADECIMALFORMAT_ICU_ERROR,
                         languagesMapForJavaDecimalFormat,
                         DString( errorName ).c_str() );
   }
}


void JavaDecimalFormat::applyLocalizedPattern( const DString& dstrPattern )
{
   Guard crit( m_pLock );
   UnicodeString uString( dstrPattern.c_str() );
   UErrorCode error = U_ZERO_ERROR;
   DecimalFormat::applyLocalizedPattern( uString, error );

   if ( U_FAILURE( error ) )
   {
      DStringA errorName( u_errorName( error ) );
      THROWELEMENTALIDI( JAVADECIMALFORMAT_NAME,
                         I_("JavaDecimalFormat::applyPattern()"),
                         JavaDecimalFormat::JAVADECIMALFORMAT_ICU_ERROR,
                         languagesMapForJavaDecimalFormat,
                         DString( errorName ).c_str() );
   }
}


void JavaDecimalFormat::setDecimalFormatSybols( 
   const DecimalFormatSymbols& symbols )
{
   Guard crit( m_pLock );

   DecimalFormat::setDecimalFormatSymbols( symbols );
}


DecimalFormatSymbols& JavaDecimalFormat::getDecimalFormatSymbols( 
   DecimalFormatSymbols& symbols )
{
   Guard crit( m_pLock );
   const DecimalFormatSymbols *pSymbols = 
      DecimalFormat::getDecimalFormatSymbols();
   symbols = *pSymbols;

   return symbols;
}


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
// $Log:   Y:/VCS/iFastAWD/dicore/javadecimalformat.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:12   kovacsro
// Initial revision.
// 
//    Rev 1.16   May 18 2001 14:44:26   dt24433
// Switched to use Guard/CriticalSectionLock from CriticalSection\MutexSemaphore.
// 
//    Rev 1.15   Oct 10 2000 08:49:04   dt17817
// Add methods to get and set formatting symbols for databroker overrides
// 
//    Rev 1.14   Jun 05 2000 07:41:58   dtwk
// Add thread-safety flag
// 
//    Rev 1.13   May 26 2000 20:26:20   DT14177
// Added ClientLocale support
// 
//    Rev 1.12   Apr 14 2000 12:59:18   DT14177
// fixed parse when int is passed in
// 
//    Rev 1.11   12 Apr 2000 06:56:48   dt20842
// Initialize error code to known good state
// 
//    Rev 1.10   Apr 11 2000 21:21:48   DT14177
// fixed error-checking
// 
//    Rev 1.9   11 Apr 2000 09:14:12   dt20842
// Added condition headers
// 
//    Rev 1.8   Apr 10 2000 16:38:42   DT14177
// ICU syncup
// 
//    Rev 1.7   Mar 22 2000 17:33:08   DT14177
// removed compile warnings - 4800
// 
//    Rev 1.6   Sep 09 1999 11:14:54   dtwk
// Remove setLenient() & isLenient()
// 
//    Rev 1.5   Sep 03 1999 12:39:44   dtwk
// Add setLenient(), getLenient(), copy constructor
// 
//    Rev 1.4   Jul 22 1999 11:39:52   DMUM
// Condition re-work
// 
//    Rev 1.3   Jun 27 1999 15:30:02   DT11700
//  
// 
//    Rev 1.2   Jun 06 1999 13:21:20   DTWK
// Minor tweaking
// 
//    Rev 1.1   Jun 01 1999 17:20:08   DTWK
// General cleanup
// 
//    Rev 1.0   May 24 1999 10:25:08   DTWK
//  
//
//

