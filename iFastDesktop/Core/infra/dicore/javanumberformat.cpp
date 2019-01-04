// JavaNumberFormat Class Implementation
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
// ^FILE   : JavaNumberFormat.cpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 01 March 1999
//
// ^CLASS  : JavaNumberFormat
// ^PARENT : none
//
// ^CLASS DESCRIPTION : Class Wrapper for Java Runtime class java.text.NumberFormat.
//
// ^MEMBER VARIABLES :
//    private:
//
//******************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef JAVANUMBERFORMAT_HPP
   #include "javanumberformat.hpp"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
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


#ifdef _MSC_VER
   // Disable the following compiler warnings
   // 4800 forcing value to boolean (performance warning)
   #pragma warning( disable : 4800 )

#endif

namespace
{
   const I_CHAR * const JAVANUMBERFORMAT_NAME = I_( "JavaNumberFormat" );
}

MsgPair en_usJavaNumberFormat[] = 
{
   { 
      JavaNumberFormat::JAVANUMBERFORMAT_ICU_ERROR,
      I_("ICU error has occurred with value %VALUE%."),
      I_("Report ICU Error to the Support Desk.")   
   }
};

Condition::mapCodePagesToLanguages languagesMapForJavaNumberFormat[] =
{ 
   {
      I_( "C" ), en_usJavaNumberFormat
   },

   // End slot marker
   {
      NULL, NULL
   }
};



JavaNumberFormat::JavaNumberFormat( bool fThreadSafe ) 
   : m_numberFormat( NULL )
{
   UErrorCode error = U_ZERO_ERROR;
   m_numberFormat = NumberFormat::createInstance( error );
   if ( U_FAILURE( error ) )
   {
      m_numberFormat = NULL;
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( error ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVANUMBERFORMAT_NAME,
                         I_("JavaNumberFormat::JavaNumberFormat()"),
                         JavaNumberFormat::JAVANUMBERFORMAT_ICU_ERROR,
                         languagesMapForJavaNumberFormat,
                         idiStr );
   }

   if ( fThreadSafe )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }
}


JavaNumberFormat::JavaNumberFormat( const ClientLocale *pClientLocale, 
                                    bool fThreadSafe ) 
   : m_numberFormat( NULL )
{
   UErrorCode error = U_ZERO_ERROR;
   const JavaLocale * javaLocale = pClientLocale->getJavaLocale();

   Locale * locale = const_cast< JavaLocale * >( javaLocale )->getLocale();

   m_numberFormat = NumberFormat::createInstance( *locale, error );
   if ( U_FAILURE( error ) )
   {
      m_numberFormat = NULL;
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( error ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVANUMBERFORMAT_NAME,
                         I_("JavaNumberFormat::JavaNumberFormat()"),
                         JavaNumberFormat::JAVANUMBERFORMAT_ICU_ERROR,
                         languagesMapForJavaNumberFormat,
                         idiStr );
    }

   if ( fThreadSafe )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }
}


JavaNumberFormat::JavaNumberFormat( JavaLocale * pJavaLocale,
                                    bool fThreadSafe ) 
   : m_numberFormat( NULL )
{
   UErrorCode error = U_ZERO_ERROR;
   m_numberFormat = NumberFormat::createInstance( *( pJavaLocale->getLocale() ), error );
   if ( U_FAILURE( error ) )
   {
      m_numberFormat = NULL;
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( error ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVANUMBERFORMAT_NAME,
                         I_("JavaNumberFormat::JavaNumberFormat()"),
                         JavaNumberFormat::JAVANUMBERFORMAT_ICU_ERROR,
                         languagesMapForJavaNumberFormat,
                         idiStr );
    }

   if ( fThreadSafe )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }
}


JavaNumberFormat::~JavaNumberFormat()
{
   if ( m_pLock )
   {
      delete m_pLock;
      m_pLock = 0;
   }
}


// Static Member functions implementation
JavaNumberFormat * JavaNumberFormat::getInstance( bool fThreadSafe )
{
   return new JavaNumberFormat( fThreadSafe );
}


JavaNumberFormat * JavaNumberFormat::getInstance( const ClientLocale *pClientLocale,
                                                  bool fThreadSafe )
{
   return new JavaNumberFormat( pClientLocale, fThreadSafe );
}


JavaNumberFormat * JavaNumberFormat::getInstance( JavaLocale * pJavaLocale,
                                                  bool fThreadSafe )
{
   return new JavaNumberFormat( pJavaLocale, fThreadSafe );
}


JavaDecimalFormat * JavaNumberFormat::getNumberInstance( bool fThreadSafe )
{
   UErrorCode error = U_ZERO_ERROR;
   JavaDecimalFormat * retVal = new JavaDecimalFormat( error, fThreadSafe );

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( error ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVANUMBERFORMAT_NAME,
                         I_("JavaNumberFormat::JavaNumberFormat()"),
                         JavaNumberFormat::JAVANUMBERFORMAT_ICU_ERROR,
                         languagesMapForJavaNumberFormat,
                         idiStr );
   }
   return retVal;
}


JavaDecimalFormat * JavaNumberFormat::getNumberInstance( 
                                                   const ClientLocale *pClientLocale,
                                                   bool fThreadSafe )
{
   UErrorCode error = U_ZERO_ERROR;
   const JavaLocale * javaLocale = pClientLocale->getJavaLocale();

   Locale * locale = const_cast< JavaLocale * >( javaLocale )->getLocale();

   DecimalFormat * tmp = 
      reinterpret_cast< DecimalFormat * >
           ( NumberFormat::createInstance( *locale,
                                           error ) );

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( error ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVANUMBERFORMAT_NAME,
                         I_("JavaNumberFormat::JavaNumberFormat()"),
                         JavaNumberFormat::JAVANUMBERFORMAT_ICU_ERROR,
                         languagesMapForJavaNumberFormat,
                         idiStr );
   }
   
   JavaDecimalFormat * retVal = new JavaDecimalFormat( *tmp, fThreadSafe );
   delete tmp;
   return retVal;
}


JavaDecimalFormat * JavaNumberFormat::getNumberInstance( 
                                                       JavaLocale * pJavaLocale,
                                                       bool fThreadSafe )
{
   UErrorCode error = U_ZERO_ERROR;
   DecimalFormat * tmp = 
      reinterpret_cast< DecimalFormat * >
           ( NumberFormat::createInstance( *( pJavaLocale->getLocale() ),
                                           error ) );

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( error ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVANUMBERFORMAT_NAME,
                         I_("JavaNumberFormat::JavaNumberFormat()"),
                         JavaNumberFormat::JAVANUMBERFORMAT_ICU_ERROR,
                         languagesMapForJavaNumberFormat,
                         idiStr );
   }
   
   JavaDecimalFormat * retVal = new JavaDecimalFormat( *tmp, fThreadSafe );
   delete tmp;
   return retVal;
}


JavaNumberFormat * JavaNumberFormat::getPercentInstance( bool fThreadSafe )
{
   UErrorCode error = U_ZERO_ERROR;
   NumberFormat * tmp = NumberFormat::createPercentInstance( error );
   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( error ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVANUMBERFORMAT_NAME,
                         I_("JavaNumberFormat::JavaNumberFormat()"),
                         JavaNumberFormat::JAVANUMBERFORMAT_ICU_ERROR,
                         languagesMapForJavaNumberFormat,
                         idiStr );
   }
   JavaNumberFormat * retVal = new JavaNumberFormat( tmp, fThreadSafe );
   return retVal;
}


JavaNumberFormat * JavaNumberFormat::getCurrencyInstance( bool fThreadSafe )
{
   UErrorCode error = U_ZERO_ERROR;
   NumberFormat * tmp = NumberFormat::createCurrencyInstance( error );
   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( error ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVANUMBERFORMAT_NAME,
                         I_("JavaNumberFormat::JavaNumberFormat()"),
                         JavaNumberFormat::JAVANUMBERFORMAT_ICU_ERROR,
                         languagesMapForJavaNumberFormat,
                         idiStr );
   }
   JavaNumberFormat * retVal = new JavaNumberFormat( tmp, fThreadSafe );
   return retVal;
}


// Local Member function implementation

bool JavaNumberFormat::equals( JavaNumberFormat * pJavaNumberFormat)
{
   Guard crit( m_pLock );
   return ( *m_numberFormat == *( pJavaNumberFormat->getParentClassPointer() ) );
}


const I_STRING JavaNumberFormat::format( double dNumber )
{
   Guard crit( m_pLock );
   UnicodeString output;
   I_STRING retVal;
   m_numberFormat->format( dNumber, output );
   ICUStringtoIString( output, retVal );

   return retVal;
}


const I_STRING JavaNumberFormat::format( long dNumber )
{
   Guard crit( m_pLock );
   UnicodeString output;
   I_STRING retVal;
   m_numberFormat->format( dNumber, output );
   ICUStringtoIString( output, retVal );

   return retVal;
}


void JavaNumberFormat::parse( const I_STRING & pszNumString, JavaNumber &number )
{
   Guard crit( m_pLock );
   Formattable fmt( number.doubleValue() );
   UErrorCode error = U_ZERO_ERROR;
   UnicodeString input( pszNumString.c_str() );
   m_numberFormat->parse( input, fmt, error );
   

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( error ) );
      idiStr += DString( tmp );
      THROWELEMENTALIDI( JAVANUMBERFORMAT_NAME,
                         I_("parse( const I_STRING & pszNumString, JavaNumber &number )"),
                         JavaNumberFormat::JAVANUMBERFORMAT_ICU_ERROR,
                         languagesMapForJavaNumberFormat,
                         idiStr );
   }
}


int JavaNumberFormat::getMaximumFractionDigits(void)
{
   Guard crit( m_pLock );
   return m_numberFormat->getMaximumFractionDigits();
}


int JavaNumberFormat::getMaximumIntegerDigits(void)
{
   Guard crit( m_pLock );
   return m_numberFormat->getMaximumIntegerDigits();
}


int JavaNumberFormat::getMinimumFractionDigits(void)
{
   Guard crit( m_pLock );
   return m_numberFormat->getMinimumFractionDigits();
}


int JavaNumberFormat::getMinimumIntegerDigits(void)
{
   Guard crit( m_pLock );
   return m_numberFormat->getMinimumIntegerDigits();
}


void JavaNumberFormat::setMaximumFractionDigits( int iNewVal )
{
   Guard crit( m_pLock );
   m_numberFormat->setMaximumFractionDigits( iNewVal );
}


void JavaNumberFormat::setMaximumIntegerDigits(int iNewVal)
{
   Guard crit( m_pLock );
   m_numberFormat->setMaximumIntegerDigits( iNewVal );
}


void JavaNumberFormat::setMinimumFractionDigits( int iNewVal )
{
   Guard crit( m_pLock );
   m_numberFormat->setMinimumFractionDigits( iNewVal );
}


void JavaNumberFormat::setMinimumIntegerDigits( int iNewVal )
{
   Guard crit( m_pLock );
   m_numberFormat->setMinimumIntegerDigits( iNewVal );
}


void JavaNumberFormat::setParseIntegerOnly( bool bNewVal )
{
   Guard crit( m_pLock );
   m_numberFormat->setParseIntegerOnly( bNewVal );
}


bool JavaNumberFormat::isParseIntegerOnly( void )
{
   Guard crit( m_pLock );
   return m_numberFormat->isParseIntegerOnly();
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
// $Log:   Y:/VCS/iFastAWD/dicore/javanumberformat.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:16   kovacsro
// Initial revision.
// 
//    Rev 1.19   May 18 2001 14:44:30   dt24433
//  
// 
//    Rev 1.18   Jan 08 2001 14:55:44   dt24433
// Made ClientLocale parms const
// 
//    Rev 1.17   Jun 13 2000 16:30:08   DT14177
// getNumberInstance() :
// mem leak fix for ClientLocale
// threadsafe flag for JavaLocale
// 
//    Rev 1.16   Jun 07 2000 10:50:30   DT14177
// fixed getNumberInstance mem leak
// 
//    Rev 1.15   Jun 05 2000 07:42:02   dtwk
// Add thread-safety flag
// 
//    Rev 1.14   May 26 2000 20:26:26   DT14177
// Added ClientLocale support
// 
//    Rev 1.13   12 Apr 2000 06:56:58   dt20842
// Initialize error code to known good state
// 
//    Rev 1.12   Apr 11 2000 16:01:10   DT14177
// added static method JavaDecimalFormat * JavaNumberFormat::getNumberInstance( JavaLocale * )
// 
//    Rev 1.11   Apr 11 2000 15:09:54   DT14177
// fixed the Unicode build
// 
//    Rev 1.10   Apr 10 2000 16:38:46   DT14177
// ICU syncup
// 
//    Rev 1.9   Mar 22 2000 17:33:16   DT14177
// removed compile warnings - 4800
// 
//    Rev 1.8   Jul 22 1999 11:40:20   DMUM
// Condition re-work
// 
//    Rev 1.7   Jun 27 1999 15:30:18   DT11700
//  
// 
//    Rev 1.6   Jun 17 1999 09:55:04   DT14177
// Added revision control blocks.
// 

