// JavaSimpleDateFormat Class Implementation
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
// ^FILE   : JavaSimpleDateFormat.hpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 10 March 1999
//
// ^CLASS  : JavaSimpleDateFormat
// ^PARENT : none
//
// ^CLASS DESCRIPTION :
//
// ^MEMBER VARIABLES :
//    private:
//  jmethodID jMidSimpleDateFormatformat;
//
//******************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include <srcprag.h>
#endif

#ifndef JAVASIMPLEDATEFORMAT_HPP
   #include "javasimpledateformat.hpp"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
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

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

#ifndef JAVALOCALE_HPP
   #include "javalocale.hpp"
#endif

#ifdef _MSC_VER
   // Disable the following compiler warnings
   // 4800 forcing value to boolean (performance warning)
   #pragma warning( disable : 4800 )

#endif

const DString JAVASIMPLEDATEFORMAT_NAME = I_( "JavaSimpleDateFormat" );

MsgPair en_usJavaSimpleDateFormat[] = 
{
   { 
      JavaSimpleDateFormat::JAVASIMPLEDATEFORMAT_JNI_EXCEPTION_LOCATE,
      I_("Java Exception Occurred in locating %METHOD% method."),
      I_("Check Java Runtime Environment.")   
   },

   { 
      JavaSimpleDateFormat::JAVASIMPLEDATEFORMAT_JNI_EXCEPTION_EXECUTE,
      I_("Java Exception Occurred in %METHOD%."),
      I_("Check Java Runtime Environment.")   
   },

   { 
      JavaSimpleDateFormat::JAVASIMPLEDATEFORMAT_ICU_ERROR,
      I_("ICU error has occurred with value %VALUE%."),
      I_("Check ICU Runtime Environment.")   
   }
};

Condition::mapCodePagesToLanguages languagesMapForJavaSimpleDateFormat[] =
{ 
   {
      I_( "C" ), en_usJavaSimpleDateFormat
   },

   // End slot marger
   {
      NULL, NULL
   }
};


// Class Implementation

// Public Default Constructor
JavaSimpleDateFormat::JavaSimpleDateFormat( bool fThreadSafe )
{
   if ( fThreadSafe )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }

    errorConstruct = U_ZERO_ERROR; 

    simpleDateFormat = new SimpleDateFormat( errorConstruct );
}


JavaSimpleDateFormat::JavaSimpleDateFormat( const DString & dstrPattern, 
                                            const ClientLocale & pClientLocale,
                                            bool fThreadSafe ) 
{
   if ( fThreadSafe )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }

    errorConstruct = U_ZERO_ERROR; 

    const JavaLocale * javaLocale = pClientLocale.getJavaLocale();

    Locale * locale = const_cast< JavaLocale * >( javaLocale )->getLocale();

    UnicodeString uPattern;
    uPattern = dstrPattern.c_str();
    
    simpleDateFormat = new SimpleDateFormat( uPattern, 
                                             *locale, 
                                             errorConstruct );
}


JavaSimpleDateFormat::JavaSimpleDateFormat( const DString & dstrPattern, 
                                            const JavaLocale & locale,
                                            bool fThreadSafe ) 
{
   if ( fThreadSafe )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }

    errorConstruct = U_ZERO_ERROR; 

    UnicodeString uPattern;
    uPattern = dstrPattern.c_str();
    
    simpleDateFormat = new icu_3_6::SimpleDateFormat( uPattern, 
       *(const_cast< JavaLocale & >( locale ).getLocale()), errorConstruct );

}


JavaSimpleDateFormat::~JavaSimpleDateFormat()
{
   if ( m_pLock )
   {
      delete m_pLock;
      m_pLock = 0;
   }

   delete simpleDateFormat;
}


JavaSimpleDateFormat::JavaSimpleDateFormat( const JavaSimpleDateFormat& copy ) 
{

   if ( simpleDateFormat )
      delete simpleDateFormat;

   simpleDateFormat = new SimpleDateFormat( *(copy.simpleDateFormat) );

   if ( copy.m_pLock )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }
}


// Static Method Function
JavaSimpleDateFormat *JavaSimpleDateFormat::US(const DString& Pattern, bool fThreadSafe )
{
   return ( new JavaSimpleDateFormat( Pattern, *(JavaLocale::getUSInstance()), fThreadSafe ) );
}


DString JavaSimpleDateFormat::format( JavaDate *pJavaDate )
{
   Guard crit( m_pLock );

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( errorConstruct ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVASIMPLEDATEFORMAT_NAME,
                         I_("JavaSimpleDateFormat::constructor"),
                         JavaSimpleDateFormat::JAVASIMPLEDATEFORMAT_ICU_ERROR,
                         languagesMapForJavaSimpleDateFormat,
                         idiStr);
   }

   UnicodeString result;

   simpleDateFormat->format( pJavaDate->getUDate(), result );

   DString returnValue;
   ICUStringtoIString( result, returnValue.getImp() );
   return returnValue;
}


DString &JavaSimpleDateFormat::format( JavaDate& javaDate, DString& dstrRet )
{
   Guard crit( m_pLock );

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( errorConstruct ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVASIMPLEDATEFORMAT_NAME,
                         I_("JavaSimpleDateFormat::constructor"),
                         JavaSimpleDateFormat::JAVASIMPLEDATEFORMAT_ICU_ERROR,
                         languagesMapForJavaSimpleDateFormat,
                         idiStr);
   }


   UnicodeString result;

   simpleDateFormat->format( javaDate.getUDate(), result );

   ICUStringtoIString( result, dstrRet.getImp() );
   return dstrRet;
}


bool JavaSimpleDateFormat::equals( JavaSimpleDateFormat *pJavaSimpleDateFormat)
{
   Guard crit( m_pLock );

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( errorConstruct ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVASIMPLEDATEFORMAT_NAME,
                         I_("JavaSimpleDateFormat::constructor"),
                         JavaSimpleDateFormat::JAVASIMPLEDATEFORMAT_ICU_ERROR,
                         languagesMapForJavaSimpleDateFormat,
                         idiStr);
   }

   return ( simpleDateFormat == (pJavaSimpleDateFormat->simpleDateFormat ) );
}


JavaDate *JavaSimpleDateFormat::parse( const DString& dstrDate )
{
   Guard crit( m_pLock );

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( errorConstruct ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVASIMPLEDATEFORMAT_NAME,
                         I_("JavaSimpleDateFormat::constructor"),
                         JavaSimpleDateFormat::JAVASIMPLEDATEFORMAT_ICU_ERROR,
                         languagesMapForJavaSimpleDateFormat,
                         idiStr);
   }

   enum UErrorCode error = U_ZERO_ERROR; 

   UnicodeString uDateStr( dstrDate.c_str() );

   UDate uDate = simpleDateFormat->parse( uDateStr, error );

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( errorConstruct ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVASIMPLEDATEFORMAT_NAME,
                         I_("JavaSimpleDateFormat::parse()"),
                         JavaSimpleDateFormat::JAVASIMPLEDATEFORMAT_ICU_ERROR,
                         languagesMapForJavaSimpleDateFormat,
                         idiStr);
   }

   JavaDate *retDate = new JavaDate();
   retDate->setTime( (long long)uDate );

   return retDate;
}


void JavaSimpleDateFormat::setLenient( bool fLenient )
{
   Guard crit( m_pLock );

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( errorConstruct ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVASIMPLEDATEFORMAT_NAME,
                         I_("JavaSimpleDateFormat::constructor"),
                         JavaSimpleDateFormat::JAVASIMPLEDATEFORMAT_ICU_ERROR,
                         languagesMapForJavaSimpleDateFormat,
                         idiStr);
   }

   simpleDateFormat->setLenient( fLenient );
}


bool JavaSimpleDateFormat::isLenient( void )
{
   Guard crit( m_pLock );

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( errorConstruct ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVASIMPLEDATEFORMAT_NAME,
                         I_("JavaSimpleDateFormat::constructor"),
                         JavaSimpleDateFormat::JAVASIMPLEDATEFORMAT_ICU_ERROR,
                         languagesMapForJavaSimpleDateFormat,
                         idiStr);
   }

   return simpleDateFormat->isLenient();
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
// $Log:   Y:/VCS/iFastAWD/dicore/javasimpledateformat.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:16   kovacsro
// Initial revision.
// 
//    Rev 1.21   May 18 2001 14:44:34   dt24433
//  
// 
//    Rev 1.20   Jan 08 2001 14:55:06   dt24433
// Made ClientLocale parms const.
// 
//    Rev 1.19   Jun 05 2000 07:42:06   dtwk
// Add thread-safety flag
// 
//    Rev 1.18   May 26 2000 20:26:28   DT14177
// Added ClientLocale support
// 
//    Rev 1.17   10 May 2000 12:08:36   dt20842
// Removed unneeded static JavaSimpleDateFormat
// 
//    Rev 1.16   11 Apr 2000 21:45:04   dt20842
// Remove unneeded delete
// 
//    Rev 1.15   Apr 11 2000 15:09:56   DT14177
// fixed the Unicode build
// 
//    Rev 1.14   Apr 11 2000 09:46:54   DT14177
// ICUString macro name change syncup
// 
//    Rev 1.13   10 Apr 2000 10:30:28   dt20842
// Switch to ICU and clean up error handling
// 
//    Rev 1.12   Mar 22 2000 17:33:18   DT14177
// removed compile warnings - 4800
// 
//    Rev 1.11   Sep 03 1999 12:39:50   dtwk
// Add setLenient(), getLenient(), copy constructor
// 
//    Rev 1.10   Jul 22 1999 11:40:24   DMUM
// Condition re-work
// 
//    Rev 1.9   Jun 27 1999 15:30:20   DT11700
//  
// 
//    Rev 1.8   Jun 17 1999 09:55:06   DT14177
// Added revision control blocks.
// 

