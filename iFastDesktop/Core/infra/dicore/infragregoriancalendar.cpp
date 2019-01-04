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


#ifndef INFRAGREGORIANCALENDAR_HPP
   #include "infragregoriancalendar.hpp"
#endif


#ifndef INFRACLIENTLOCALE_HPP
   #include "infraclientlocale.hpp"
#endif


#ifndef INFRALOCALE_HPP
   #include "infralocale.hpp"
#endif


#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif


#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif


#ifdef _MSC_VER
   // Disable the following compiler warnings
   // 4800 forcing value to boolean (performance warning)
   #pragma warning( disable : 4800 )

#endif

const DString GREGORIANCALENDAR_NAME = I_( "GregorianCalendar" );

MsgPair en_usGregorianCalendar[] = 
{
   { 
      Infra::GregorianCalendar::ICU_ERROR,
      I_("ICU error has occurred with value %VALUE%."),
      I_("Check ICU Runtime Environment.")   
   }

};

Condition::mapCodePagesToLanguages 
                      languagesMapForGregorianCalendar[] =
{ 
   {
      I_( "C" ), en_usGregorianCalendar
   },

   // End slot marker
   {
      NULL, NULL

   }


};


static void throwIfNeeded( UErrorCode code,
                           I_CHAR * methodName )
{
   if ( U_FAILURE( code ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName( code ) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( GREGORIANCALENDAR_NAME,
		                   methodName,
                         Infra::GregorianCalendar::ICU_ERROR,
                         languagesMapForGregorianCalendar,
                         idiStr );
   }
}


Infra::GregorianCalendar::GregorianCalendar( 
                                         const Locale * pLocale ) 
   : errorConstruct( U_ZERO_ERROR ),
     _gregorianCalendar( new ::GregorianCalendar( 
                               *( ( const_cast< Infra::Locale * >
                                    ( pLocale ) )->getLocale() ), 
                                               errorConstruct ) )
{
}


Infra::GregorianCalendar::GregorianCalendar( 
                             const ClientLocale * pClientLocale ) 
   : errorConstruct( U_ZERO_ERROR ),
     _gregorianCalendar( new ::GregorianCalendar( 
                                 *( const_cast< Infra::Locale * >
                   ( pClientLocale->getLocale() )->getLocale() ), 
                                               errorConstruct ) )
{
}


Infra::GregorianCalendar::~GregorianCalendar( void )
{
   delete _gregorianCalendar;
}


bool Infra::GregorianCalendar::equals( 
            const Infra::GregorianCalendar * pGregorianCalendar )
{
   throwIfNeeded( errorConstruct,
                  I_( "equals( " )
                  I_( "const Infra::GregorianCalendar * )" ) );

   return ( *_gregorianCalendar == 
            *( pGregorianCalendar->_gregorianCalendar ) ); 
}


bool Infra::GregorianCalendar::before( 
    const Infra::GregorianCalendar * pGregorianCalendar)
{
   static I_CHAR * methodName = 
                      I_( "GregorianCalendar::before( " )
                      I_( "const Infra::GregorianCalendar * )" );

   throwIfNeeded( errorConstruct,
                  methodName );

   enum UErrorCode error = U_ZERO_ERROR; 

   bool returnValue = _gregorianCalendar->before( 
                     *( pGregorianCalendar->_gregorianCalendar ), 
                     error );
   
   throwIfNeeded( error,
                  methodName );

   return returnValue;
}


bool Infra::GregorianCalendar::after( 
            const Infra::GregorianCalendar * pGregorianCalendar )
{
   static I_CHAR * methodName = 
                      I_( "GregorianCalendar::after( " )
                      I_( "const Infra::GregorianCalendar * )" );

   throwIfNeeded( errorConstruct,
                  methodName );

   enum UErrorCode error = U_ZERO_ERROR; 

   bool returnValue = 
        _gregorianCalendar->after( *( pGregorianCalendar->
                                         _gregorianCalendar ), 
                                      error );

   throwIfNeeded( error,
                  methodName );

   return returnValue;
}


bool Infra::GregorianCalendar::isLeapYear( int Year )
{
   throwIfNeeded( errorConstruct,
                  I_( "GregorianCalendar::isLeapYear( " )
                  I_( "int Year )" ) );

   return _gregorianCalendar->isLeapYear( Year );
}


void Infra::GregorianCalendar::add( int Field,
                                    int Amount )
{
   static I_CHAR * methodName = I_( "GregorianCalendar::add( " )
                                I_( "int Field, int Amount )" );

   throwIfNeeded( errorConstruct,
                  methodName );

   enum UErrorCode error = U_ZERO_ERROR; 

   _gregorianCalendar->add( ( enum ::Calendar::EDateFields ) Field,
                            Amount, error );
   
   throwIfNeeded( error,
                  methodName );
}


void Infra::GregorianCalendar::roll( int Field, bool Up )
{
   static I_CHAR * methodName = I_( "GregorianCalendar::roll( " )
                                I_( "int Field, bool Up )" );

   throwIfNeeded( errorConstruct,
                  methodName );

   // ICU code says not to use the roll function with boolean and
   // instead use the integer version, so will convert bool to
   //   -/+ 1 value
   int moveValue = -1;
   if ( true == Up )
      moveValue = 1;

   enum UErrorCode error = U_ZERO_ERROR; 

   _gregorianCalendar->roll( ( enum ::Calendar::EDateFields ) 
                             Field, 
                             moveValue, 
                             error );

   throwIfNeeded( error,
                  methodName );
}


int Infra::GregorianCalendar::get( int Operation )
{
   static I_CHAR * methodName = I_( "GregorianCalendar::get( " )
                                I_( "int Operation )" );

   throwIfNeeded( errorConstruct,
                  methodName );

   enum UErrorCode error = U_ZERO_ERROR; 

   int returnInt = _gregorianCalendar->get( 
                                 ( enum ::UCalendarDateFields ) 
                                 Operation, 
                                 error );

   throwIfNeeded( error,
                  methodName );
   
   return returnInt;
}


double Infra::GregorianCalendar::getTime()
{
   static I_CHAR * methodName = I_( "GregorianCalendar::" )
                                I_( "getTime() " );

   throwIfNeeded( errorConstruct,
                  methodName );

   enum UErrorCode error = U_ZERO_ERROR; 

   UDate uDate = _gregorianCalendar->getTime( error );

   throwIfNeeded( error,
                  methodName );

   return ( double ) uDate;
}


void Infra::GregorianCalendar::setTime( double date )
{
   static I_CHAR * methodName =
                             I_( "GregorianCalendar::setTime( " )
                             I_( "double date )" );
   throwIfNeeded( errorConstruct,
                  methodName );

   enum UErrorCode error = U_ZERO_ERROR; 

   _gregorianCalendar->setTime( date, error );

   throwIfNeeded( error,
                  methodName );
}


void Infra::GregorianCalendar::set( int field,
                                    int value )
{
   throwIfNeeded( errorConstruct,
                  I_( "GregorianCalendar::set( " )
                  I_( "int field, int value )" ) );

   _gregorianCalendar->set( ( enum::UCalendarDateFields ) 
                            field, 
                            value );
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
// $Log:   Y:/VCS/iFastAWD/dicore/infragregoriancalendar.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:56   kovacsro
// Initial revision.
//
//   Rev 1.0   28 Dec 2000 08:55:14   dt14177
// 
// 
//    Rev 1.14   May 26 2000 20:26:22   DT14177
// Added ClientLocale support
// 
//    Rev 1.13   May 11 2000 08:25:02   DT14177
// lots of fixes for DDate
// 
//    Rev 1.12   Apr 11 2000 15:09:48   DT14177
// fixed the Unicode build
// 
//    Rev 1.11   10 Apr 2000 10:30:22   dt20842
// Switch to ICU and clean up error handling
// 
//    Rev 1.10   Mar 22 2000 17:33:10   DT14177
// removed compile warnings - 4800
// 
//    Rev 1.9   Sep 16 1999 16:28:10   DT14177
// memory leak cleanup
// 
//    Rev 1.8   Jul 22 1999 11:39:56   DMUM
// Condition re-work
// 
//    Rev 1.6   Jun 27 1999 15:30:04   DT11700
//  
// 
//    Rev 1.5   Jun 17 1999 09:54:54   DT14177
// Added revision control blocks.
// 
