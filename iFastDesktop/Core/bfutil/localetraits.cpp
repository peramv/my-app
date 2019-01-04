#include "stdafx.h"

#include "localetraits.hpp"
#include "bfcritsec.hpp"
#include "bfguard.hpp"

namespace CND
{
   extern const long BFUTILERR_UnsupportedLocaleException;
}

namespace bfutil
{

LocaleTraits::LocaleTraits( const ClientLocale& rLocale, bool forDisp )
{
   DString cfgString = rLocale.getLocale();
   cfgString += I_("_DN");
   DString dstrFormattingOptions = GetConfigValueAsString( ConfigManager::getApplication(), I_( "FormattingOptions" ), cfgString );

   if( rLocale.getLocale() == I_("enUS") ||
       rLocale.getLocale() == I_("enCA") ||
       rLocale.getLocale() == I_("enGB") ||
       rLocale.getLocale() == I_("enIE") ||
       rLocale.getLocale() == I_("jaJP") )
   {
      radixSeparator_ = I_( '.' );
      groupSeparator_ = I_( ',' );
      negativeSign_ = I_( '-' );
      cGroupDigits_ = 3;
      if( dstrFormattingOptions.size() != 0 )
      {
         int radixPos = dstrFormattingOptions.pos( I_( ".=" ) );
         if( -1 != radixPos && dstrFormattingOptions.size() > ( radixPos + 2 ) )
         {
            radixSeparator_ = dstrFormattingOptions[ radixPos + 2 ];
         }
         int groupPos = dstrFormattingOptions.pos( I_( ",=" ) );
         if( -1 != groupPos && dstrFormattingOptions.size() > ( groupPos + 2 ) )
         {
            groupSeparator_ = dstrFormattingOptions[ groupPos + 2 ];
         }
      }
   }
   else if( rLocale.getLocale() == I_("frFR") || 
            rLocale.getLocale() == I_("frCA") )
   {
#ifdef FIXED_CRT_LOCALE_THREAD
      radixSeparator_ = I_( ',' );
      groupSeparator_ = I_( ' ' );
#else
      radixSeparator_ = I_( '.' );
      groupSeparator_ = I_( ',' );
#endif
      negativeSign_ = I_( '-' );
      cGroupDigits_ = 3;
      if( dstrFormattingOptions.size() != 0 )
      {
         int radixPos = dstrFormattingOptions.pos( I_( ".=" ) );
         if( -1 != radixPos && dstrFormattingOptions.size() > ( radixPos + 2 ) )
         {
            radixSeparator_ = dstrFormattingOptions[ radixPos + 2 ];
         }
         int groupPos = dstrFormattingOptions.pos( I_( ",=" ) );
         if( -1 != groupPos && dstrFormattingOptions.size() > ( groupPos + 2 ) )
         {
            groupSeparator_ = dstrFormattingOptions[ groupPos + 2 ];
         }
      }
   }
   else if( rLocale.getLocale() == I_("deDE") ||
            rLocale.getLocale() == I_("esES") ||
            rLocale.getLocale() == I_("nlNL") ||
            rLocale.getLocale() == I_("itIT") )
   {
	   if( forDisp )
	   {
		radixSeparator_ = I_( ',' );
		groupSeparator_ = I_( '.' );
	   }
	   else 
	   {
#ifdef FIXED_CRT_LOCALE_THREAD
      radixSeparator_ = I_( ',' );
      groupSeparator_ = I_( '.' );
#else
      radixSeparator_ = I_( '.' );
      groupSeparator_ = I_( ',' );
#endif
	   }
      negativeSign_ = I_( '-' );
      cGroupDigits_ = 3;
      if( dstrFormattingOptions.size() != 0 )
      {
         int radixPos = dstrFormattingOptions.pos( I_( ".=" ) );
         if( -1 != radixPos && dstrFormattingOptions.size() > ( radixPos + 2 ) )
         {
            radixSeparator_ = dstrFormattingOptions[ radixPos + 2 ];
         }
         int groupPos = dstrFormattingOptions.pos( I_( ",=" ) );
         if( -1 != groupPos && dstrFormattingOptions.size() > ( groupPos + 2 ) )
         {
            groupSeparator_ = dstrFormattingOptions[ groupPos + 2 ];
         }
      }
   }
   else
   {
      THROWFROMFILE( CND::BFUTIL_CONDITION, I_( "LocaleTraits" ), CND::BFUTILERR_UnsupportedLocaleException );
   }
}

BFCritSec cs_enUS;
BFCritSec cs_enCA;
BFCritSec cs_enGB;
BFCritSec cs_enIE;
BFCritSec cs_frFR;
BFCritSec cs_frCA;
BFCritSec cs_jaJP;
BFCritSec cs_deDE;
BFCritSec cs_esES;
BFCritSec cs_nlNL;
BFCritSec cs_itIT;
BFCritSec cs_Def;

const LocaleTraits& LocaleTraits::get( const ClientLocale& rLocale, bool forDisp )
{
   if( rLocale.getLocale() == I_( "enUS" ) )
   {
      BFGuard g( cs_enUS );
      static const LocaleTraits enUSLocaleTraits( rLocale );
      return(enUSLocaleTraits);
   }
   else if( rLocale.getLocale() == I_( "enCA" ) )
   {
      BFGuard g( cs_enCA );
      static const LocaleTraits enCALocaleTraits( rLocale );
      return(enCALocaleTraits);
   }
   else if( rLocale.getLocale() == I_( "enGB" ) )
   {
      BFGuard g( cs_enGB );
      static const LocaleTraits enGBLocaleTraits( rLocale );
      return(enGBLocaleTraits);
   }
   else if( rLocale.getLocale() == I_( "jaJP" ) )
   {
      BFGuard g( cs_jaJP );
      static const LocaleTraits jaJPLocaleTraits( rLocale );
      return(jaJPLocaleTraits);
   }
   else if( rLocale.getLocale() == I_( "enIE" ) )
   {
      BFGuard g( cs_enIE );
      static const LocaleTraits enIELocaleTraits( rLocale );
      return(enIELocaleTraits);
   }
   else if( rLocale.getLocale() == I_( "frFR" ) )
   {
      BFGuard g( cs_frFR );
      static const LocaleTraits frFRLocaleTraits( rLocale );
      return(frFRLocaleTraits);
   }
   else if( rLocale.getLocale() == I_( "frCA" ) )
   {
      BFGuard g( cs_frCA );
      static const LocaleTraits frCALocaleTraits( rLocale );
      return(frCALocaleTraits);
   }
   else if( rLocale.getLocale() == I_( "deDE" ) )
   {
      BFGuard g( cs_deDE );
	  if( forDisp )
	  {
		static const LocaleTraits deDELocaleTraitsDisp( rLocale, forDisp );
		return(deDELocaleTraitsDisp);
	  }
	  else
	  {
		static const LocaleTraits deDELocaleTraits( rLocale );
		return(deDELocaleTraits);
	  }      
   }
   else if( rLocale.getLocale() == I_( "esES" ) )
   {
      BFGuard g( cs_esES );
      static const LocaleTraits esESLocaleTraits( rLocale );
      return(esESLocaleTraits);
   }
   else if( rLocale.getLocale() == I_( "nlNL" ) )
   {
      BFGuard g( cs_nlNL );
      static const LocaleTraits nlNLLocaleTraits( rLocale );
      return(nlNLLocaleTraits);
   }
   else if( rLocale.getLocale() == I_( "itIT" ) )
   {
      BFGuard g( cs_itIT );
      static const LocaleTraits itITLocaleTraits( rLocale );
      return(itITLocaleTraits);
   }
   BFGuard g( cs_Def );
   static const LocaleTraits defLocale( rLocale );
   return(defLocale);
}

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/localetraits.cpp-arc  $
//
//   Rev 1.5   Jun 30 2005 16:56:58   Fengyong
//PET1250 FN02 - European numeric enhancement
//
//   Rev 1.4   Aug 30 2004 15:59:32   popescu
//PET 991, FN 02, added support for Dutch and Italian
//
//   Rev 1.3   Aug 12 2003 10:05:50   PURDYECH
//Added Spanish as a valid language.
//
