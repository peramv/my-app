// JavaLocale Class Implementation
//**********************************************************************
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
//**********************************************************************
//
// ^FILE   : JavaLocale.hpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 01 March 1999
//
// ^CLASS  : JavaLocale
// ^PARENT : none
//
// ^CLASS DESCRIPTION : Class Wrapper for Java Runtime class
//                      java.util.Locale.
//
// ^MEMBER VARIABLES :
//    private:
//    static JavaLocale *s_JavaLocale;
//
//**********************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
 
#ifndef JAVALOCALE_HPP
   #include "javalocale.hpp"
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

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

#ifndef LOCID_H
   #include <locid.h>
#endif

#ifdef _MSC_VER
   // Disable the following compiler warnings
   // 4800 forcing value to boolean (performance warning)
   #pragma warning( disable : 4800 )

#endif

namespace
{
   CriticalSectionLock s_LCVLock;
   CriticalSectionLock s_iteratorLock;
   CriticalSectionLock s_createLocaleLock;

   const I_CHAR * const JAVALOCALE_NAME = I_("JavaLocale");
}

JavaLocale::InstanceMap JavaLocale::s_InstanceMap;

MsgPair en_usJavaLocale[] =
{
   {
      JavaLocale::JAVALOCALE_JNI_EXCEPTION_LOCATE,
      I_("Java Exception Occurred in locating %METHOD% method."),
      I_("Check Java Runtime Environment.")
   },

   {
      JavaLocale::JAVALOCALE_JNI_EXCEPTION_EXECUTE,
      I_("Java Exception Occurred in %METHOD%."),
      I_("Check Java Runtime Environment.")
   },

   {
      JavaLocale::JAVALOCATE_ICU_ERROR,
      I_("ICU error has occurred with value %VALUE%."),
      I_("Check ICU Runtime Environment.")
   }
};

Condition::mapCodePagesToLanguages languagesMapForJavaLocale[] =
{
   {
      I_( "C" ), en_usJavaLocale
   },

   // End slot marger
   {
      NULL, NULL
   }
};

JavaLocale * JavaLocale::s_pUSInstance = NULL;
JavaLocale * JavaLocale::s_pJAPANInstance = NULL;
JavaLocale * JavaLocale::s_pGERMANYInstance = NULL;
JavaLocale * JavaLocale::s_pCANADA_FRENCHInstance = NULL;
JavaLocale * JavaLocale::s_pCANADAInstance = NULL;
JavaLocale * JavaLocale::s_pUKInstance = NULL;
JavaLocale * JavaLocale::s_pFRANCEInstance = NULL;
JavaLocale * JavaLocale::s_pITALYInstance = NULL;
JavaLocale * JavaLocale::s_pKOREAInstance = NULL;
JavaLocale * JavaLocale::s_pCHINAInstance = NULL;
JavaLocale * JavaLocale::s_pTAIWANInstance = NULL;

JavaLocale * JavaLocale::s_pCurrentInstance = NULL;
JavaLocale * JavaLocale::s_pDefaultInstance = NULL;

DString JavaLocale::s_currentLCV;

//**********************************************************************
//
// ^PRIVATE METHOD : JavaLocale::JavaLocale
//
// ^DESCRIPTION : Creates a JavaLocale Object.
//
// ^PARAMETERS  : DString jsLanguage
//                DString jsCountry
//
// ^RETURNS     : none
//
// ^THROWS      : None
//
// ^EXAMPLE     :
//
//**********************************************************************

JavaLocale::JavaLocale( const DString & lcvString )
{
   DString jsLanguage;
   DString jsCountry;
   DString jsVariant;

   lcvString.parseLocale( jsLanguage, jsCountry, jsVariant );
   init( jsLanguage, jsCountry, jsVariant );
}


JavaLocale::JavaLocale( const DString & jsLanguage,
                        const DString & jsCountry )
{
   init( jsLanguage, jsCountry, I_("") );
}


JavaLocale::JavaLocale()
{
   m_loc = new Locale( Locale::getDefault() );
   m_register.registerSingleton( releaseInstance, this, I_("coreJL") );
   initLCV();
}

JavaLocale::JavaLocale( const DString & jsLanguage,
                        const DString & jsCountry,
                        const DString & jsVariant )
{
   init( jsLanguage, jsCountry, jsVariant );
}

JavaLocale::~JavaLocale()
{
   delete m_loc;
}

void JavaLocale::init( const DString & jsLanguage,
                  const DString & jsCountry,
                  const DString & jsVariant )
{
   m_loc = new Locale( jsLanguage.asA().c_str(),
                       jsCountry.asA().c_str(),
                       jsVariant.asA().c_str() );

   m_register.registerSingleton( releaseInstance, this, I_("coreJL") );
   m_LCV = jsLanguage + jsCountry + jsVariant;
}

void JavaLocale::initLCV()
{
   DString str;

   getLanguage( m_LCV );
   m_LCV.append( getCountry( str ) );
   m_LCV.append( getVariant( str ) );
}

JavaLocale *JavaLocale::getUSInstance( void )
{
   Guard cs( &s_createLocaleLock );

   return ( s_pUSInstance ? s_pUSInstance :
      s_pUSInstance = getLocaleInstance( I_( "en" ), I_( "US" ) ) );
}

JavaLocale *JavaLocale::getJAPANInstance( void )
{
   Guard cs( &s_createLocaleLock );

   return ( s_pJAPANInstance ? s_pJAPANInstance :
      s_pJAPANInstance = getLocaleInstance( I_( "ja" ), I_( "JP" ) ) );
}

JavaLocale *JavaLocale::getGERMANYInstance( void )
{
   Guard cs( &s_createLocaleLock );

   return ( s_pGERMANYInstance ? s_pGERMANYInstance :
      s_pGERMANYInstance = getLocaleInstance( I_( "de" ), I_( "DE" ) ) );
}

JavaLocale *JavaLocale::getCANADA_FRENCHInstance( void )
{
   Guard cs( &s_createLocaleLock );

   return ( s_pCANADA_FRENCHInstance ? s_pCANADA_FRENCHInstance :
      s_pCANADA_FRENCHInstance = getLocaleInstance( I_( "fr" ), I_( "CA" ) ) );
}

JavaLocale *JavaLocale::getCANADAInstance( void )
{
   Guard cs( &s_createLocaleLock );

   return ( s_pCANADAInstance ? s_pCANADAInstance :
      s_pCANADAInstance = getLocaleInstance( I_( "en" ), I_( "CA" ) ) );
}

JavaLocale *JavaLocale::getUKInstance( void )
{
   Guard cs( &s_createLocaleLock );

   return ( s_pUKInstance ? s_pUKInstance :
      s_pUKInstance = getLocaleInstance( I_( "en" ), I_( "GB" ) ) );
}

JavaLocale *JavaLocale::getFRANCEInstance( void )
{
   Guard cs( &s_createLocaleLock );

   return ( s_pFRANCEInstance ? s_pFRANCEInstance :
      s_pFRANCEInstance = getLocaleInstance( I_( "fr" ), I_( "FR" ) ) );
}

JavaLocale *JavaLocale::getITALYInstance( void )
{
   Guard cs( &s_createLocaleLock );

   return ( s_pITALYInstance ? s_pITALYInstance :
      s_pITALYInstance = getLocaleInstance( I_( "it" ), I_( "IT" ) ) );
}

JavaLocale *JavaLocale::getKOREAInstance( void )
{

   Guard cs( &s_createLocaleLock );

   return ( s_pKOREAInstance ? s_pKOREAInstance :
      s_pKOREAInstance = getLocaleInstance( I_( "ko" ), I_( "KR" ) ) );
}

JavaLocale *JavaLocale::getCHINAInstance( void )
{
   Guard cs( &s_createLocaleLock );

   return ( s_pCHINAInstance ? s_pCHINAInstance :
      s_pCHINAInstance = getLocaleInstance( I_( "zh" ), I_( "CN" ) ) );
}

JavaLocale *JavaLocale::getTAIWANInstance( void )
{
   Guard cs( &s_createLocaleLock );

   return ( s_pTAIWANInstance ? s_pTAIWANInstance :
      s_pTAIWANInstance = getLocaleInstance( I_( "tw" ), I_( "TW" ) ) );
}

JavaLocale *JavaLocale::getLocaleInstance( const DString & lcvString )
{
   JavaLocale * retVal;

   {
      Guard cs( &s_iteratorLock );

      // if not found in map, insert it!
      InstanceMap::iterator iter;
      DString key( lcvString );

      if ( s_InstanceMap.end() == ( iter = s_InstanceMap.find( key ) ) )
      {
         retVal = new JavaLocale( lcvString );
         s_InstanceMap[ key ] = retVal;
      }
      else
      {
         retVal = ( *iter ).second;
      }
   }

   return retVal;
}

JavaLocale *JavaLocale::getLocaleInstance( const DString & alanguage,
                                           const DString & acountry)
{
   JavaLocale * retVal;

   {
      Guard cs( &s_iteratorLock );

      // if not found in map, insert it!
      InstanceMap::iterator iter;
      DString key( alanguage + acountry );

      if ( s_InstanceMap.end() == ( iter = s_InstanceMap.find( key ) ) )
      {
         retVal = new JavaLocale( alanguage, acountry );
         s_InstanceMap[ key ] = retVal;
      }
      else
      {
         retVal = ( *iter ).second;
      }
   }

   return retVal;
}

JavaLocale *JavaLocale::getLocaleInstance( const DString & alanguage,
                                           const DString & acountry,
                                           const DString & avariant )
{
   JavaLocale * retVal;

   {
      Guard cs( &s_iteratorLock );

      // if not found in map, insert it!
      InstanceMap::iterator iter;
      DString key( alanguage + acountry + avariant );

      if ( s_InstanceMap.end() == ( iter = s_InstanceMap.find( key ) ) )
      {
         retVal = new JavaLocale( alanguage, acountry, avariant );
         s_InstanceMap[ key ] = retVal;
      }
      else
      {
         retVal = ( *iter ).second;
      }
   }

   return retVal;
}

JavaLocale *JavaLocale::getDefaultInstance( void )
{
   Guard cs( &s_iteratorLock );

   if ( s_pDefaultInstance == NULL )
   {
      s_pDefaultInstance = new JavaLocale();
      DString key;
      s_pDefaultInstance->getLCV( key );

      InstanceMap::iterator iter;
      if ( s_InstanceMap.end() == ( iter = s_InstanceMap.find( key ) ) )
      {
         s_InstanceMap[ key ] = s_pDefaultInstance;
      }
      else
      {
         delete s_pDefaultInstance;
         s_pDefaultInstance = ( *iter ).second;
      }
   }

   return s_pDefaultInstance;
}

JavaLocale * JavaLocale::getCurrentInstance()
{
   if ( NULL == s_pCurrentInstance )
   {
      s_pCurrentInstance = getDefaultInstance();
   }

   return s_pCurrentInstance;
}

JavaLocale * JavaLocale::setCurrentInstance( JavaLocale * arg )
{
   Guard cSect( &s_LCVLock );

   setDefault( arg );

   s_currentLCV = arg->getLCV();
   s_pCurrentInstance = arg;

   return s_pCurrentInstance;
}

JavaLocale * JavaLocale::setCurrentInstance( const DString & localeString )
{
   DString lang, cntry, varnt;

   localeString.parseLocale( lang, cntry, varnt );

   return setCurrentInstance( getLocaleInstance( lang, cntry, varnt ) );
}

DString & JavaLocale::getLCV( DString &dstrLCV )
{
   Guard cSect( &s_LCVLock );

   if ( 0 == s_currentLCV.size() )
   {
      JavaLocale * arg = getCurrentInstance();
      s_currentLCV = arg->getLCV();
   }

   dstrLCV = s_currentLCV;

   return dstrLCV;
}

void JavaLocale::freeLocaleInstanceMap()
{
   InstanceMap::iterator iter;

   while ( ( iter = s_InstanceMap.begin() ) != s_InstanceMap.end() )
   {
      delete ( *iter ).second;
      s_InstanceMap.erase( iter );
   }
}

DString &JavaLocale::getISO3Country(
   DString &country
   ) const
{
   country = m_loc->getISO3Country();

   return country;
}


DString &JavaLocale::getISO3Language(
   DString &language
   ) const
{
   language = m_loc->getISO3Language();
   return language;
}


DString &JavaLocale::getCountry(
   DString &country
   ) const
{
   country = m_loc->getCountry();
   return country;
}


DString &JavaLocale::getLanguage(
   DString &language
   ) const
{
   language = m_loc->getLanguage();
   return language;
}


DString &JavaLocale::getVariant(
   DString &variant
   ) const
{
   variant = m_loc->getVariant();
   return variant;
}


DString JavaLocale::getDisplayVariant() const
{
   UnicodeString result2;
   m_loc->getDisplayVariant( result2 );

   DString returnValue;
   ICUStringtoIString( result2, returnValue.getImp() );

   return returnValue;
}


DString JavaLocale::getDisplayCountry() const
{
   UnicodeString result2;
   m_loc->getDisplayCountry( result2 );

   DString returnValue;
   ICUStringtoIString( result2, returnValue.getImp() );

   return returnValue;
}


DString JavaLocale::getDisplayLanguage() const
{
   UnicodeString result2;
   m_loc->getDisplayLanguage( result2 );

   DString returnValue;
   ICUStringtoIString( result2, returnValue.getImp() );

   return returnValue;
}


DString JavaLocale::getDisplayName() const
{
   UnicodeString result2;
   m_loc->getDisplayName( result2 );

   DString returnValue;
   ICUStringtoIString( result2, returnValue.getImp() );

   return returnValue;
}

bool JavaLocale::equals( JavaLocale* pJavaLocale )
{
   return ( *m_loc == *(pJavaLocale->m_loc) );
}


void JavaLocale::setDefault( JavaLocale * arg )
{
   enum UErrorCode error = U_ZERO_ERROR;

   Locale::setDefault( *(arg->m_loc), error );

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( error ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVALOCALE_NAME,
                         I_("JavaLocale::setDefault()"),
                         JavaLocale::JAVALOCATE_ICU_ERROR,
                         languagesMapForJavaLocale,
                         idiStr);
   }
}

void JavaLocale::clearStatic( const JavaLocale *pjl )
{
   Guard cs( &s_createLocaleLock );

   if ( pjl == s_pUSInstance )
   {
      s_pUSInstance = NULL;
   }
   else if ( pjl == s_pJAPANInstance )
   {
      s_pJAPANInstance = NULL;
   }
   else if ( pjl == s_pGERMANYInstance )
   {
      s_pGERMANYInstance = NULL;
   }
   else if ( pjl == s_pCANADA_FRENCHInstance )
   {
      s_pCANADA_FRENCHInstance = NULL;
   }
   else if ( pjl == s_pCANADAInstance )
   {
      s_pCANADAInstance = NULL;
   }
   else if ( pjl == s_pUKInstance )
   {
      s_pUKInstance = NULL;
   }
   else if ( pjl == s_pFRANCEInstance )
   {
      s_pFRANCEInstance = NULL;
   }
   else if ( pjl == s_pITALYInstance )
   {
      s_pITALYInstance = NULL;
   }
   else if ( pjl == s_pKOREAInstance )
   {
      s_pKOREAInstance = NULL;
   }
   else if ( pjl == s_pCHINAInstance )
   {
      s_pCHINAInstance = NULL;
   }
   else if ( pjl == s_pTAIWANInstance )
   {
      s_pTAIWANInstance = NULL;
   }

   if ( pjl == s_pCurrentInstance )
   {
      s_pCurrentInstance = NULL;
   }

   if ( pjl == s_pDefaultInstance )
   {
      s_pDefaultInstance = NULL;
   }
}

void JavaLocale::releaseInstance( void *pObj )
{
   JavaLocale *pjl = (JavaLocale *)pObj;

   clearStatic( pjl );

   Guard cs( &s_iteratorLock );

   const DString &lcv = pjl->getLCV();

   InstanceMap::iterator iter = s_InstanceMap.find( lcv );

   if ( s_InstanceMap.end() != iter )
   {
      const JavaLocale *pjl2 =( *iter ).second ;

      if ( pjl2 == pjl )
      {
         // This is the happy path and we should ALWAYS arrive here!
         s_InstanceMap.erase( iter );
         delete pjl;
      }
   }
}

void freeLocaleInstanceMap()
{
   JavaLocale::freeLocaleInstanceMap();
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
// $Log:   Y:/VCS/iFastAWD/dicore/javalocale.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:12   kovacsro
// Initial revision.
// 
//    Rev 1.35   Jul 27 2001 15:31:18   DT11159
// Fixed JavaLocale::getDefaultInstance( ) so that duplicate
// entries are not placed in s_InstanceMap. This was causing
// SingletonRegister::releaseSingletons() to loop forever if a
// ClientLocale( enUS, NO_MARKET, NO_CLIENT ) was created
// before the default locale was created.
//
//    Rev 1.34   May 18 2001 14:26:18   dt24433
// Changes for new ICU and switch to Guard/CriticalSectionLock from
// CriticalSection\MutexSemaphore.
//
//    Rev 1.33   Mar 08 2001 08:29:42   dt24433
// Fixed getDefaultInstance to add new JavaLocale to map.
//
//    Rev 1.32   Feb 21 2001 16:26:14   DT21858
//
//
//    Rev 1.31   Jun 01 2000 17:32:44   DT14177
// added LCV string to private data
//
//    Rev 1.30   May 26 2000 20:26:24   DT14177
// Added ClientLocale support
//
//    Rev 1.29   Apr 11 2000 21:54:02   dtwk
// Fix trap in constructor
//
//    Rev 1.28   Apr 11 2000 15:09:52   DT14177
// fixed the Unicode build
//
//    Rev 1.27   Apr 11 2000 09:46:52   DT14177
// ICUString macro name change syncup
//
//    Rev 1.26   Apr 10 2000 16:58:22   dtwk
// Change #includes of icu classes to <> instead of ""
//
//    Rev 1.25   10 Apr 2000 10:30:24   dt20842
// Switch to ICU and clean up error handling
//
//    Rev 1.24   06 Apr 2000 09:52:28   dt20842
// Change to ICU code
//
//    Rev 1.23   Mar 22 2000 17:33:14   DT14177
// removed compile warnings - 4800
//
//    Rev 1.22   Oct 07 1999 15:43:50   DT14177
// Fixed more threading and memory leak issues.
//
//    Rev 1.21   Oct 05 1999 16:54:14   DT14177
// Added suppression and language severity enhancements; fixed multi-threading issues
//
//    Rev 1.20   Sep 30 1999 09:24:08   DT14177
// Fixed multi-threading bug
//
//    Rev 1.19   Aug 06 1999 11:29:12   DT14177
// Fixed getLCV and bogus recursion report
//
//    Rev 1.18   Aug 05 1999 16:32:48   DT14177
// Performance improvement for getLCV()
//
//    Rev 1.17   Jul 22 1999 11:40:08   DMUM
// Condition re-work
//
//    Rev 1.16   Jul 08 1999 10:01:50   DT14177
// Fixed two memory leaks
//
//    Rev 1.15   Jun 27 1999 15:30:12   DT11700
//
//
//    Rev 1.14   Jun 18 1999 12:36:54   DT14177
// Fixed a bug where the default Locale wasn't being set.
//
//    Rev 1.13   Jun 15 1999 11:47:54   DT14177
// added setCurrentInstance()
//
//    Rev 1.12   Jun 10 1999 11:28:38   DT14177
// Changed interface to use only DString, not DStringA
//
//    Rev 1.11   Jun 08 1999 14:17:14   DT14177
// added set,getInstance(); added comments; made some methods const
//
