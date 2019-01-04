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

// this file should only be included in the .CPP file

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef COMMONPORT_H
    #include "commonport.h"
#endif

#ifndef INFRADATEFORMAT_HPP
   #include "infradateformat.hpp"
#endif

#ifndef CONDITION_HPP
   #include "Condition.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "ConditionManager.hpp"
#endif

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif

#ifndef DATEFMT_H
   #include <datefmt.h>
#endif

#ifndef DSTRING_HPP
    #include "dstring.hpp"
#endif

#ifndef INFRACLIENTLOCALE_HPP
   #include "infraclientlocale.hpp"
#endif

#ifndef INFRALOCALE_HPP
   #include "infralocale.hpp"
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

#ifdef _MSC_VER
   // Disable the following compiler warnings
   // 4800 forcing value to boolean (performance warning)
   #pragma warning( disable : 4800 )

#endif

const I_CHAR *DATEFORMAT_NAME = I_( "DateFormat" );

MsgPair en_usDateFormat[] = 
{
   { 
      Infra::DateFormat::ICU_ERROR,
      I_("ICU error has occurred with value %VALUE%."),
      I_("Check ICU Runtime Environment.")   
   }
};

Condition::mapCodePagesToLanguages languagesMapForDateFormat[] =
{ 
   {
      I_( "C" ), en_usDateFormat
   },

   // End slot marker
   {
      NULL, NULL
   }
};


Infra::DateFormat::~DateFormat()
{
   logStdOut( I_( "DateFormat::" )
              I_( "~DateFormat()" ) );
   delete _dateFormat;
   logStdOut( I_( "DateFormat::" )
              I_( "~DateFormat() exit" ) );
}


Infra::DateFormat Infra::DateFormat::getInstance( 
                                               bool fThreadSafe )
{
   logStdOut( I_( "DateFormat::" )
              I_( "getInstance() noexit" ) );
   return Infra::DateFormat( icu_3_6::DateFormat::createInstance(),
                      fThreadSafe );
}


Infra::DateFormat Infra::DateFormat::getDateInstance(
                                            Infra::Locale * loc,
                                            bool fThreadSafe )
{
   logStdOut( I_( "DateFormat::" )
              I_( "getDateInstance(Locale *) noexit" ) );
   return DateFormat( ::DateFormat::createDateInstance(
                             ::DateFormat::kShort,
                             *( loc->getLocale() ) ),
                      fThreadSafe );
}


Infra::DateFormat Infra::DateFormat::getDateInstance( 
                                      Infra::ClientLocale * loc,
                                      bool fThreadSafe )
{
   logStdOut( I_( "DateFormat::" )
              I_( "getDateInstance(ClientLocale *) noexit" ) );
   const Infra::Locale * locale = loc->getLocale();
   
   return DateFormat( ::DateFormat::createDateInstance(
                                            ::DateFormat::kShort,
                                 *( const_cast< Infra::Locale * >
                                     ( locale ) )->getLocale() ),
                      fThreadSafe );
}


Infra::DateFormat Infra::DateFormat::getDateInstance( 
                                               bool fThreadSafe )
{
   logStdOut( I_( "DateFormat::" )
              I_( "getDateInstance() noexit" ) );
   return DateFormat( ::DateFormat::createDateInstance(),
                      fThreadSafe );
}


Infra::DateFormat Infra::DateFormat::getDateTimeInstance( 
                                               bool fThreadSafe )
{
   logStdOut( I_( "DateFormat::" )
              I_( "getDateTimeInstance() noexit" ) );
   return DateFormat( ::DateFormat::createDateTimeInstance(),
                      fThreadSafe );
}


bool Infra::DateFormat::equals( Infra::DateFormat & pDateFormat )
{
   TRACER_METHOD( I_( "equals( Infra::DateFormat & ) ") );

   logStdOut( I_( "DateFormat::" )
              I_( "equals()" ) );
   Guard crit( _lock );
   bool retVal = ( *_dateFormat == *( pDateFormat._dateFormat) );
   logStdOut( I_( "DateFormat::" )
              I_( "equals() exit" ) );
   return retVal;
}


void Infra::DateFormat::setLenient( bool bIsLenient )
{
   TRACER_METHOD( I_( "setLenient( bool bIsLenient ) ") );

   logStdOut( I_( "DateFormat::" )
              I_( "setLenient()" ) );
   Guard crit( _lock );
   _dateFormat->setLenient( bIsLenient );
   logStdOut( I_( "DateFormat::" )
              I_( "setLenient() exit" ) );
}


bool Infra::DateFormat::isLenient( void )
{
   TRACER_METHOD( I_( "isLenient( void ) ") );

   return ( _dateFormat->isLenient() );
}


// private methods

Infra::DateFormat::DateFormat( ::DateFormat * dateFormatIn,
                               bool fThreadSafe )
  : _dateFormat( dateFormatIn )
{
   TRACER_CONSTRUCTOR( I_( "DateFormat( ::DateFormat * )" ) );
   logStdOut( I_( "DateFormat::" )
              I_( "DateFormat(::DateFormat *) noexit" ) );
   if ( fThreadSafe )
   {
      _lock = new CriticalSectionLock();
   }
   else
   {
      _lock = 0;
   }
}


double Infra::DateFormat::parse( const DString & strDate )
{
   TRACER_METHOD( I_( "parse( const DString & date ) " ) );

   logStdOut( I_( "DateFormat::" )
              I_( "parse(DString &)" ) );
   Guard crit( _lock );
   UnicodeString uStr( strDate.c_str() );
   UErrorCode code = U_ZERO_ERROR;
   double date = ( double ) _dateFormat->parse( uStr, code );
   if ( U_FAILURE( code ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( code ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( DATEFORMAT_NAME,
		                   I_( "parse( const DString & date ) " ),
                         Infra::DateFormat::ICU_ERROR,
                         languagesMapForDateFormat,
                         idiStr );
   }
   logStdOut( I_( "DateFormat::" )
              I_( "parse(DString &) exit" ) );
   return date;
}


const DString Infra::DateFormat::format( double date )
{
   TRACER_METHOD( I_( "format( double date ) " ) );

   logStdOut( I_( "DateFormat::" )
              I_( "format(double)" ) );
   Guard crit( _lock );
   UnicodeString uStr;
   _dateFormat->format( date, uStr );

   DString returnValue;
   ICUStringtoIString( uStr, returnValue.getImp() );
   logStdOut( I_( "DateFormat::" )
              I_( "format(double) exit" ) );
   return returnValue;
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
// $Log:   Y:/VCS/iFastAWD/dicore/infradateformat.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:54   kovacsro
// Initial revision.
//
//   Rev 1.1   May 18 2001 14:27:22   dt24433
// 
//
//   Rev 1.0   28 Dec 2000 08:55:06   dt14177
// 
// 
//    Rev 1.14   May 26 2000 20:26:18   DT14177
// Added ClientLocale support
// 
//    Rev 1.13   May 11 2000 08:53:26   DT14177
// changed kdefault to kshort in getDateInstance( locale )
// 
//    Rev 1.12   Apr 11 2000 09:46:50   DT14177
// ICUString macro name change syncup
// 
//    Rev 1.11   10 Apr 2000 10:30:20   dt20842
// Switch to ICU and clean up error handling
// 
//    Rev 1.10   Mar 22 2000 17:33:06   DT14177
// removed compile warnings - 4800
// 
//    Rev 1.9   Oct 05 1999 16:54:12   DT14177
// Added suppression and language severity enhancements; fixed multi-threading issues
// 
//    Rev 1.8   Jul 22 1999 11:39:50   DMUM
// Condition re-work
// 
//    Rev 1.7   Jun 27 1999 15:30:00   DT11700
//  
// 
//    Rev 1.6   Jun 17 1999 09:37:42   DT14177
// Added a revision control block
// 

