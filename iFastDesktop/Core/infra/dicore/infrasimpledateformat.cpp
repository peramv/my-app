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
   #include <srcprag.h>
#endif

#ifndef COMMONPORT_H
    #include "commonport.h"
#endif

#ifndef INFRASIMPLEDATEFORMAT_HPP
   #include "infrasimpledateformat.hpp"
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

#ifndef INFRACLIENTLOCALE_HPP
   #include "infraclientlocale.hpp"
#endif

#ifndef INFRADATEHELPER_HPP
    #include "infradatehelper.hpp"
#endif

#ifndef INFRADATEFORMAT_HPP
   #include "infradateformat.hpp"
#endif

#ifndef SMPDTFMT_H
   #include <smpdtfmt.h>
#endif


#ifdef _MSC_VER
   // Disable the following compiler warnings
   // 4800 forcing value to boolean (performance warning)
   #pragma warning( disable : 4800 )

#endif

const DString SIMPLEDATEFORMAT_NAME = I_( "SimpleDateFormat" );


MsgPair en_usSimpleDateFormat[] = 
{
   { 
      Infra::SimpleDateFormat::ICU_ERROR,
      I_("ICU error has occurred with value %VALUE%."),
      I_("Check ICU Runtime Environment.")   
   }
};

Condition::mapCodePagesToLanguages 
                         languagesMapForSimpleDateFormat[] =
{ 
   {
      I_( "C" ), en_usSimpleDateFormat
   },

   // End slot marker
   {
      NULL, NULL
   }
};


static void throwIfNeeded( UErrorCode code,
				               I_CHAR * methodName )
{
   logStdOut( I_( "throwIfNeeded()" ) );
   if ( U_FAILURE( code ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( code ) );
      idiStr += DString( tmp );

      /*THROWELEMENTALIDI( I_( "DICORE" ),
		                   methodName,
                         Infra::SimpleDateFormat::ICU_ERROR,
                         languagesMapForSimpleDateFormat,
                         I_( "" ) );*/
      /*ConditionException ce( I_( "DICORE" ),
                             methodName,
                             Infra::SimpleDateFormat::ICU_ERROR,
                             __FILE__,
                             __LINE__,
                             languagesMapForSimpleDateFormat,
                             idiStr );*/
      throw( 2 );
   }
   logStdOut( I_( "throwIfNeeded() exit" ) );
}


// Public Default Constructor
Infra::SimpleDateFormat::SimpleDateFormat( bool fThreadSafe )
{
   logStdOut( I_( "SimpleDateFormat::SimpleDateFormat()" ) );
   errorConstruct = U_ZERO_ERROR;
   _simpleDateFormat = new icu::SimpleDateFormat( errorConstruct );
   if ( fThreadSafe )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }
   logStdOut( I_( "SimpleDateFormat::SimpleDateFormat() exit" ) );
}


Infra::SimpleDateFormat::SimpleDateFormat(
                             const DString & dstrPattern, 
                             Infra::ClientLocale & pClientLocale,
                             bool fThreadSafe ) 
{
   logStdOut( I_( "SimpleDateFormat::" )
              I_( "SimpleDateFormat(DString &,ClientLocale &," )
              I_( "bool)" ) );
   errorConstruct = U_ZERO_ERROR;
   _simpleDateFormat = new ::SimpleDateFormat( 
                                             dstrPattern.c_str(), 
                               *( ( const_cast< Infra::Locale * >
                                ( pClientLocale.getLocale() ) )->
                                  getLocale() ),
                                              errorConstruct );
   if ( fThreadSafe )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }
   logStdOut( I_( "SimpleDateFormat::" )
              I_( "SimpleDateFormat(DString &,ClientLocale &," )
              I_( "bool) exit" ) );
}


Infra::SimpleDateFormat::SimpleDateFormat( 
                                     const DString & dstrPattern, 
                                     Infra::Locale & locale,
                                     bool fThreadSafe ) 
{
   logStdOut( I_( "SimpleDateFormat::" )
              I_( "SimpleDateFormat(DString &,Locale &," )
              I_( "bool)" ) );
   errorConstruct = U_ZERO_ERROR;
   _simpleDateFormat = new ::SimpleDateFormat( 
                                             dstrPattern.c_str(), 
                                         *( locale.getLocale() ),
                                             errorConstruct );
   if ( fThreadSafe )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }
   logStdOut( I_( "SimpleDateFormat::" )
              I_( "SimpleDateFormat(DString &,Locale &," )
              I_( "bool) exit" ) );
}


Infra::SimpleDateFormat::~SimpleDateFormat()
{
   logStdOut( I_( "SimpleDateFormat::" )
              I_( "~SimpleDateFormat()" ) );
   if ( _simpleDateFormat )
   {
      delete _simpleDateFormat;
      _simpleDateFormat = NULL;
   }
   if ( m_pLock )
   {
      delete m_pLock;
      m_pLock = 0;
   }
   logStdOut( I_( "SimpleDateFormat::" )
              I_( "~SimpleDateFormat() exit" ) );
}


Infra::SimpleDateFormat::SimpleDateFormat( const Infra::
                                        SimpleDateFormat & copy ) 
{
   logStdOut( I_( "SimpleDateFormat::" )
              I_( "SimpleDateFormat(SimpleDateFormat&)" ) );
   _simpleDateFormat = new ::SimpleDateFormat( 
                                   *( copy._simpleDateFormat ) );

   if ( copy.m_pLock )
   {
      m_pLock = new CriticalSectionLock();
   }
   else
   {
      m_pLock = 0;
   }
   logStdOut( I_( "SimpleDateFormat::" )
              I_( "SimpleDateFormat(SimpleDateFormat&) exit" ) );
}


// Static Method Function
Infra::SimpleDateFormat * Infra::SimpleDateFormat::US( const
                                                DString& Pattern, 
                                               bool fThreadSafe )
{
   logStdOut( I_( "SimpleDateFormat::" )
              I_( "US() noexit" ) );
   return ( new SimpleDateFormat( Pattern, 
                             *( Infra::Locale::getUSInstance() ),
                                  fThreadSafe ) );
}



DString & Infra::SimpleDateFormat::format( DString & dateToFormat,
                                           DString & result )
{
   logStdOut( I_( "SimpleDateFormat::" )
              I_( "format(DString &,DString &)" ) );
   Guard crit( m_pLock );

   double formatDate;
   
   Infra::DateHelper::getStringDateAsDouble( dateToFormat,
                                             formatDate );
   format( formatDate, result );
   logStdOut( I_( "SimpleDateFormat::" )
              I_( "format(DString &,DString &) exit" ) );
   return result;
}


bool Infra::SimpleDateFormat::equals( Infra::SimpleDateFormat * 
                                          pSimpleDateFormat)
{
   logStdOut( I_( "SimpleDateFormat::equals()" ) );
   Guard crit( m_pLock );

   throwIfNeeded( errorConstruct,
				      I_( "SimpleDateFormat::equals( " )
                  I_( "Infra::SimpleDateFormat * )" ) );

   bool retVal = ( *_simpleDateFormat == *( pSimpleDateFormat->
                                           _simpleDateFormat ) );
   logStdOut( I_( "SimpleDateFormat::equals() exit" ) );
   return retVal;
}


void Infra::SimpleDateFormat::setLenient( bool fLenient )
{
   logStdOut( I_( "SimpleDateFormat::setLenient()" ) );
   Guard crit( m_pLock );

   throwIfNeeded( errorConstruct,
                  I_( "SimpleDateFormat::setLenient( " )
                  I_( "bool fLenient )" ) );

   _simpleDateFormat->setLenient( fLenient );
   logStdOut( I_( "SimpleDateFormat::setLenient() exit" ) );
}


bool Infra::SimpleDateFormat::isLenient( void )
{
   logStdOut( I_( "SimpleDateFormat::isLenient() noexit" ) );
   Guard crit( m_pLock );

   throwIfNeeded( errorConstruct,
                  I_( "SimpleDateFormat::isLenient()" ) );

   return _simpleDateFormat->isLenient();
}


// private methods

DString Infra::SimpleDateFormat::format( double pDate )
{
   logStdOut( I_( "SimpleDateFormat::format(double)" ) );
   Guard crit( m_pLock );

   throwIfNeeded( errorConstruct,
                  I_( "SimpleDateFormat::format( " )
                  I_( "double pDate )" ) );

   UnicodeString result;

   _simpleDateFormat->format( pDate, result );

   DString returnValue;
   ICUStringtoIString( result, returnValue.getImp() );
   logStdOut( I_( "SimpleDateFormat::format(double) exit" ) );
   return returnValue;
}


DString& Infra::SimpleDateFormat::format( double date, 
                                     DString & dstrRet )
{
   logStdOut( I_( "SimpleDateFormat::format(double," )
              I_( "DString &)" ) );
   Guard crit( m_pLock );

   throwIfNeeded( errorConstruct,
                  I_( "SimpleDateFormat::format( " )
                  I_( "double pDate, DString & dstrRet )" ) );

   UnicodeString result;

   _simpleDateFormat->format( date, result );

   ICUStringtoIString( result, dstrRet.getImp() );
   logStdOut( I_( "SimpleDateFormat::format(double," )
              I_( "DString &) exit" ) );
   return dstrRet;
}


double Infra::SimpleDateFormat::parse( const DString & dstrDate,
                                       bool & isError )
{
   logStdOut( I_( "SimpleDateFormat::parse(DString &)" ) );
   enum UErrorCode error = U_ZERO_ERROR; 
   double date = 0;
   static I_CHAR * methodName = I_( "SimpleDateFormat::parse( " )
                              I_( "const DString & dstrDate )" );

   {
      Guard crit( m_pLock );

      throwIfNeeded( errorConstruct,
                     methodName );

      UnicodeString uDateStr;
      uDateStr = dstrDate.c_str();

      try
      {
         date = _simpleDateFormat->parse( uDateStr, error );
      }
      catch ( ... )
      {
         date = date + 1.0;
      }
   }
   isError = ( U_FAILURE( error ) );
   throwIfNeeded( error,
                  methodName );

   logStdOut( I_( "SimpleDateFormat::parse(DString &) exit" ) );
   return date;
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
// $Log:   Y:/VCS/iFastAWD/dicore/infrasimpledateformat.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:02   kovacsro
// Initial revision.
//
//   Rev 1.1   May 18 2001 14:27:30   dt24433
// 
//
//   Rev 1.0   28 Dec 2000 08:55:22   dt14177
// 
// 
//    Rev 1.19   Jun 05 2000 07:42:06   dtwk
// Add thread-safety flag
// 
//    Rev 1.18   May 26 2000 20:26:28   DT14177
// Added ClientLocale support
// 
//    Rev 1.17   10 May 2000 12:08:36   dt20842
// Removed unneeded static Infra::SimpleDateFormat
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

