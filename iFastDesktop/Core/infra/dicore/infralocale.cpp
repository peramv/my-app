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

// Make sure the linkage is right!

#define DICORE_DLL

// This file should only be included in .CPP files.

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef INFRALOCALE_HPP
   #include "infralocale.hpp"
#endif

#ifndef LOCID_H
   #include <locid.h>
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
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

#ifdef _MSC_VER
   // Disable the following compiler warnings
   // 4800 forcing value to boolean (performance warning)
   #pragma warning( disable : 4800 )

#endif

CriticalSectionLock diLCVLock;
CriticalSectionLock diIteratorLock;
CriticalSectionLock dicreateLocaleLock;

const I_CHAR *LOCALE_NAME = I_( "Locale" );

Infra::Locale::InstanceMap Infra::Locale::instanceMap;

MsgPair en_usLocale[] = 
{
   { 
      Infra::Locale::ICU_ERROR,
      I_( "ICU error has occurred with value %VALUE%." ),
      I_( "Check ICU Runtime Environment." )   
   }
};

Condition::mapCodePagesToLanguages languagesMapForLocale[] =
{ 
   {
      I_( "C" ), en_usLocale
   },

   // End slot marker
   {
      NULL, NULL

   }
};


bool Infra::Locale::fInit = false;
Infra::Locale * Infra::Locale::currentInstance = NULL;
Infra::Locale * Infra::Locale::defaultInstance = NULL;
Infra::Locale * Infra::Locale::USInstance = NULL;
Infra::Locale * Infra::Locale::JAPANInstance = NULL;
Infra::Locale * Infra::Locale::GERMANYInstance = NULL;
Infra::Locale * Infra::Locale::CANADA_FRENCHInstance = NULL;
Infra::Locale * Infra::Locale::CANADAInstance = NULL;
Infra::Locale * Infra::Locale::UKInstance = NULL;
Infra::Locale * Infra::Locale::FRANCEInstance = NULL;
Infra::Locale * Infra::Locale::ITALYInstance = NULL;
Infra::Locale * Infra::Locale::KOREAInstance = NULL;
Infra::Locale * Infra::Locale::CHINAInstance = NULL;
Infra::Locale * Infra::Locale::TAIWANInstance = NULL;

DString Infra::Locale::currentLCV;



static void throwIfNeeded( UErrorCode code,
                           I_CHAR * methodName )
{
   if ( U_FAILURE( code ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( code ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( LOCALE_NAME,
		                   methodName,
                         Infra::Locale::ICU_ERROR,
                         languagesMapForLocale,
                         idiStr );
   }
}


Infra::Locale * Infra::Locale::getJAPANInstance( void )
{
   if ( JAPANInstance )
   {
      return JAPANInstance;
   }
   Guard cs( &dicreateLocaleLock );
   return ( JAPANInstance ) ? JAPANInstance :
                   JAPANInstance = getLocaleInstance( I_( "ja" ),
                                                    I_( "JP" ) );
}


Infra::Locale * Infra::Locale::getUSInstance( void )
{
   if ( USInstance )
   {
      return USInstance;
   }

   Guard cs( &dicreateLocaleLock );
   return ( USInstance ) ? USInstance :
                      USInstance = getLocaleInstance( I_( "en" ), 
                                                    I_( "US" ) );
}


Infra::Locale * Infra::Locale::getFRANCEInstance( void )
{
   if ( FRANCEInstance )
   {
      return FRANCEInstance;
   }
   Guard cs( &dicreateLocaleLock );
   return ( FRANCEInstance ) ? FRANCEInstance :
                  FRANCEInstance = getLocaleInstance( I_( "fr" ), 
                                                    I_( "FR" ) );
}


Infra::Locale * Infra::Locale::getGERMANYInstance( void )
{
   if ( GERMANYInstance )
   {
      return GERMANYInstance;
   }
   Guard cs( &dicreateLocaleLock );
   return ( GERMANYInstance ) ? GERMANYInstance :
                 GERMANYInstance = getLocaleInstance( I_( "de" ), 
                                                    I_( "DE" ) );
}


Infra::Locale * Infra::Locale::getITALYInstance( void )
{
   if ( ITALYInstance )
   {
      return ITALYInstance;
   }
   Guard cs( &dicreateLocaleLock );
   return ( ITALYInstance ) ? ITALYInstance :
                   ITALYInstance = getLocaleInstance( I_( "it" ), 
                                                    I_( "IT" ) );
}


Infra::Locale * Infra::Locale::getKOREAInstance( void )
{
   if ( KOREAInstance )
   {
      return KOREAInstance;
   }

   Guard cs( &dicreateLocaleLock );
   return ( KOREAInstance ) ? KOREAInstance :
                   KOREAInstance = getLocaleInstance( I_( "ko" ), 
                                                    I_( "KR" ) );
}


Infra::Locale * Infra::Locale::getCHINAInstance( void )
{
   if ( CHINAInstance )
   {
      return CHINAInstance;
   }

   Guard cs( &dicreateLocaleLock );
   return ( CHINAInstance ) ? CHINAInstance :
                   CHINAInstance = getLocaleInstance( I_( "zh" ), 
                                                    I_( "CN" ) );
}


Infra::Locale * Infra::Locale::getTAIWANInstance( void )
{
   if ( TAIWANInstance )
   {
      return TAIWANInstance;
   }
   Guard cs( &dicreateLocaleLock );
   return ( TAIWANInstance ) ? TAIWANInstance :
                  TAIWANInstance = getLocaleInstance( I_( "tw" ), 
                                                    I_( "TW" ) );
}


Infra::Locale * Infra::Locale::getUKInstance( void )
{
   if ( UKInstance )
   {
      return UKInstance;
   }
   Guard cs( &dicreateLocaleLock );
   return ( UKInstance ) ? UKInstance :
                      UKInstance = getLocaleInstance( I_( "en" ), 
                                                    I_( "GB" ) );
}


Infra::Locale * Infra::Locale::getCANADAInstance( void )
{
   if ( CANADAInstance )
   {
      return CANADAInstance;
   }
   Guard cs( &dicreateLocaleLock );
   return ( CANADAInstance ) ? CANADAInstance :
                  CANADAInstance = getLocaleInstance( I_( "en" ), 
                                                    I_( "CA" ) );
}


Infra::Locale * Infra::Locale::getCANADA_FRENCHInstance( void )
{
   if ( CANADA_FRENCHInstance )
   {
      return CANADA_FRENCHInstance;
   }

   Guard cs( &dicreateLocaleLock );
   return ( CANADA_FRENCHInstance ) ? CANADA_FRENCHInstance :
                  CANADA_FRENCHInstance = getLocaleInstance(
                                                      I_( "fr" ), 
                                                    I_( "CA" ) );
}


Infra::Locale * Infra::Locale::getDefaultInstance( void )
{
   if ( defaultInstance )
   {
      return defaultInstance;
   }

   Guard cSect( &diLCVLock );

   if ( NULL == defaultInstance )
   {
      defaultInstance = new Locale();
   }

   return defaultInstance;
}


const ::Locale * Infra::Locale::getLocale( void )
{
   throwIfNeeded( errorConstruct,
                  I_( "getLocale()" ) );

   return _locale;
}


Infra::Locale * Infra::Locale::getLocaleInstance( const DString &
                                                      lcvString )
{
   Infra::Locale * retVal;

   {
       Guard cs( &diIteratorLock );
       // if not found in map, insert it!
       InstanceMap::iterator iter;
       DString key( lcvString );
       if ( instanceMap.end() == ( iter = instanceMap.find( 
                                                        key ) ) )
       {
          retVal = new Infra::Locale( lcvString );
          instanceMap[ key ] = retVal;
       }
       else
          retVal = ( *iter ).second;
    }

    return retVal;
}


Infra::Locale * Infra::Locale::getLocaleInstance( const DString &
                                                 alanguage, 
                                        const DString & acountry)
{
   Infra::Locale * retVal;

   {
       Guard cs( &diIteratorLock );
       // if not found in map, insert it!
       InstanceMap::iterator iter;
       DString key( alanguage + acountry );
       if ( instanceMap.end() == ( iter = instanceMap.find( 
                                                        key ) ) )
       {
          retVal = new Infra::Locale( alanguage,
                                   acountry );
          instanceMap[ key ] = retVal;
       }
       else
          retVal = ( *iter ).second;
    }

    return retVal;
}


Infra::Locale * Infra::Locale::getLocaleInstance( const DString &
                                                 alanguage,
                                        const DString & acountry,
                                        const DString & avariant)
{
   Infra::Locale * retVal;

   {
       Guard cs( &diIteratorLock );
       // if not found in map, insert it!
       InstanceMap::iterator iter;
       DString key( alanguage + acountry + avariant );
       if ( instanceMap.end() == ( iter = instanceMap.find( 
                                                        key ) ) )
       {
          retVal = new Infra::Locale( alanguage,
                                   acountry,
                                   avariant );
          instanceMap[ key ] = retVal;
       }
       else
          retVal = ( *iter ).second;
    }

    return retVal;
}


DString &Infra::Locale::getISO3Country( DString &country ) const
{
   throwIfNeeded( errorConstruct,
                  I_( "getISO3Country()" ) );

   country = _locale->getISO3Country();
   return country;
}


DString &Infra::Locale::getISO3Language( DString &language) const
{
   throwIfNeeded( errorConstruct,
                  I_( "getISO3Language()" ) );

   language = _locale->getISO3Language();
   return language;
}


DString &Infra::Locale::getCountry( DString &country ) const
{
   throwIfNeeded( errorConstruct,
                  I_( "getCountry()" ) );

   country = _locale->getCountry();
   return country;
}


DString &Infra::Locale::getLanguage( DString &language ) const
{
   throwIfNeeded( errorConstruct,
                  I_( "getLanguage()" ) );

   language = _locale->getLanguage();
   return language;
}


DString &Infra::Locale::getVariant( DString &variant ) const
{
   throwIfNeeded( errorConstruct,
                  I_( "getVariant()" ) );

   variant = _locale->getVariant();
   return variant;
}


DString Infra::Locale::getDisplayVariant() const
{
   throwIfNeeded( errorConstruct,
                  I_( "getDisplayVariant()" ) );

   UnicodeString result2;

   _locale->getDisplayVariant(result2 );

   DString returnValue;
   ICUStringtoIString( result2, returnValue.getImp() );
   return returnValue;
}


DString Infra::Locale::getDisplayCountry() const
{
   throwIfNeeded( errorConstruct,
                  I_( "getDisplayCountry()" ) );

   UnicodeString result2;

   _locale->getDisplayCountry(result2 );

   DString returnValue;
   ICUStringtoIString( result2, returnValue.getImp() );
   return returnValue;
}


DString Infra::Locale::getDisplayLanguage() const
{
   throwIfNeeded( errorConstruct,
                  I_( "getDisplayLanguage()" ) );

   UnicodeString result2;

   _locale->getDisplayLanguage(result2 );

   DString returnValue;
   ICUStringtoIString( result2, returnValue.getImp() );
   return returnValue;
}


DString Infra::Locale::getDisplayName() const
{
   throwIfNeeded( errorConstruct,
                  I_( "getDisplayName()" ) );

   UnicodeString result2;

   _locale->getDisplayName( result2 );

   DString returnValue;
   ICUStringtoIString( result2, returnValue.getImp() );
   return returnValue;
}


DString& Infra::Locale::getLCV( DString &dstrLCV )
{
   if ( 0 != currentLCV.size() )
      return ( dstrLCV = currentLCV );
      
   Guard cSect( &diLCVLock );

   if ( 0 == currentLCV.size() )
   {
      Infra::Locale * arg = getCurrentInstance();
      currentLCV = arg->getLCV();
   }
   return ( dstrLCV = currentLCV );
}


bool Infra::Locale::equals( Infra::Locale * pInfraLocale )
{
   throwIfNeeded( errorConstruct,
                  I_( "equals( Infra::Locale * )" ) );

   return ( *_locale == *( pInfraLocale->_locale ) );
}


Infra::Locale * Infra::Locale::getCurrentInstance()
{
   if ( NULL == currentInstance )
   {
      currentInstance = getDefaultInstance();
   }
   return currentInstance;
}


Infra::Locale * Infra::Locale::setCurrentInstance( Infra::Locale
                                                   * arg )
{
   Guard cSect( &diLCVLock );

   setDefault( arg );
   currentLCV = arg->getLCV();

   return currentInstance = arg;
}


Infra::Locale * Infra::Locale::setCurrentInstance( 
                                   const DString & localeString )
{
   DString lang, cntry, varnt;

   localeString.parseLocale( lang, cntry, varnt );
   return setCurrentInstance( getLocaleInstance( lang,
                                                 cntry,
                                                 varnt ) );
}


void Infra::Locale::setDefault( Infra::Locale * arg )
{
   enum UErrorCode error = U_ZERO_ERROR; 
   ::Locale::setDefault( *( arg->_locale ), error );

   throwIfNeeded( error,
                  I_( "setDefault( Infra::Locale * )" ) );
}


void Infra::Locale::freeLocaleInstanceMap()
{
   Infra::Locale::InstanceMap::iterator iter;
   while ( ( iter = instanceMap.begin() ) != instanceMap.end() )
   {
      delete ( *iter ).second;
      instanceMap.erase( iter );
   }
}


//***************************************************************
//
// ^PRIVATE METHOD : Locale
//
// ^DESCRIPTION : Creates a Locale Object.
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
//***************************************************************

Infra::Locale::Locale( const DString & lcvString ) 
{
   DString jsLanguage;
   DString jsCountry;
   DString jsVariant;

   LCV = lcvString;
   lcvString.parseLocale( jsLanguage, jsCountry, jsVariant );
   _locale = new ::Locale( jsLanguage.asA().c_str(), 
                           jsCountry.asA().c_str(), 
                           jsVariant.asA().c_str() );
}


Infra::Locale::Locale( const DString & jsLanguage, 
                       const DString & jsCountry ) 
{
   LCV = jsLanguage;
   LCV += jsCountry;
   _locale = new ::Locale( jsLanguage.asA().c_str(), 
                           jsCountry.asA().c_str() );
}


Infra::Locale::Locale( ) 
{
   _locale = new ::Locale( ::Locale::getDefault() );
   DString str;
   LCV = getLanguage( str );
   LCV.append( getCountry( str ) );
   LCV.append( getVariant( str ) );
}

Infra::Locale::Locale( const DString & jsLanguage,
                       const DString & jsCountry, 
                       const DString & jsVariant ) 
{
   LCV = jsLanguage;
   LCV += jsCountry;
   LCV += jsVariant;
   _locale = new ::Locale( jsLanguage.asA().c_str(), 
                           jsCountry.asA().c_str(), 
                           jsVariant.asA().c_str() );
}


Infra::Locale::~Locale()
{
   delete _locale;
}



//***************************************************************
//
//  DiCore Internal methods used in dllmain
//
//***************************************************************


void diFreeLocaleInstanceMap()
{
   Infra::Locale::freeLocaleInstanceMap();
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
// $Log:   Y:/VCS/iFastAWD/dicore/infralocale.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:00   kovacsro
// Initial revision.
//
//   Rev 1.1   May 18 2001 14:27:26   dt24433
// 
//
//   Rev 1.0   28 Dec 2000 08:55:18   dt14177
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
// Added suppression and language severity enhancements;
// fixed multi-threading issues
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
