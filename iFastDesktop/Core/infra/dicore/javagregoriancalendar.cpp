// JavaGregorianCalendar Class Implementation
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
// ^FILE   : JavaGregorianCalendar.hpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 01 March 1999
//
// ^CLASS  : JavaGregorianCalendar
// ^PARENT : none
//
// ^CLASS DESCRIPTION :
//
// ^MEMBER VARIABLES :
//    private:
//
//**********************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef JAVAGREGORIANCALENDAR_HPP
   #include "javagregoriancalendar.hpp"
#endif


#ifndef JAVALOCALE_HPP
   #include "javalocale.hpp" 
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


#ifdef _MSC_VER
   // Disable the following compiler warnings
   // 4800 forcing value to boolean (performance warning)
   #pragma warning( disable : 4800 )

#endif

const DString JAVAGREGORIANCALENDAR_NAME = I_("JavaGregorianCalendar");

const DStringA javaDateClassName = "java/util/Date";

MsgPair en_usJavaGregorianCalendar[] = 
{
   { 
      JavaGregorianCalendar::JAVAGREGORIANCALENDAR_JNI_EXCEPTION_LOCATE,
      I_("Java Exception Occurred in locating %METHOD% method."),
      I_("Check Java Runtime Environment.")   
   },

   { 
     JavaGregorianCalendar::JAVAGREGORIANCALENDAR_JNI_EXCEPTION_EXECUTE,
      I_("Java Exception Occurred in %METHOD%."),
      I_("Check Java Runtime Environment.")   
   },

   { 
      JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
      I_("ICU error has occurred with value %VALUE%."),
      I_("Check ICU Runtime Environment.")   
   }

};

Condition::mapCodePagesToLanguages 
                      languagesMapForJavaGregorianCalendar[] =
{ 
   {
      I_( "C" ), en_usJavaGregorianCalendar
   },

   // End slot marger
   {
      NULL, NULL

   }


};

// JavaGregorianCalendar Implementation
JavaGregorianCalendar::JavaGregorianCalendar( JavaLocale * 
                                                         pJavaLocale ) 
{

    errorConstruct = U_ZERO_ERROR; 

    gregorianCalendar = new GregorianCalendar( *(pJavaLocale->getLocale() ), errorConstruct );

}


JavaGregorianCalendar::JavaGregorianCalendar( ClientLocale * 
                                                         pClientLocale ) 
{

    errorConstruct = U_ZERO_ERROR; 

    const JavaLocale * javaLocale = pClientLocale->getJavaLocale();

    Locale * locale = const_cast< JavaLocale * >( javaLocale )->getLocale();

    gregorianCalendar = new GregorianCalendar( *locale, errorConstruct );

}




JavaGregorianCalendar::~JavaGregorianCalendar(void)
{

   delete gregorianCalendar;

}

bool JavaGregorianCalendar::equals( JavaGregorianCalendar *
                                          pJavaGregorianCalendar)
{

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }



   return ( *gregorianCalendar == *(pJavaGregorianCalendar->gregorianCalendar ) ); 
}

bool JavaGregorianCalendar::before( JavaGregorianCalendar *
                                       pJavaGregorianCalendar)
{

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }


   enum UErrorCode error = U_ZERO_ERROR; 

   bool returnValue = gregorianCalendar->before( *(pJavaGregorianCalendar->gregorianCalendar ), error );
   

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }



   return returnValue;
}

bool JavaGregorianCalendar::after(JavaGregorianCalendar *
                                        pJavaGregorianCalendar)
{

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }



   enum UErrorCode error = U_ZERO_ERROR; 

   bool returnValue = gregorianCalendar->after( *(pJavaGregorianCalendar->gregorianCalendar ), error );
   

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }



   return returnValue;
}

bool JavaGregorianCalendar::isLeapYear(int Year)
{

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }



   return gregorianCalendar->isLeapYear( Year );

}

void JavaGregorianCalendar::add(int Field, int Amount)
{

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }


   enum UErrorCode error = U_ZERO_ERROR; 

   gregorianCalendar->add( (enum Calendar::EDateFields)Field, Amount, error );
   

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
  }
}

void JavaGregorianCalendar::roll(int Field, bool Up)
{

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }



   // ICU code says not to use the roll function with boolean and instead use the 
   //   integer version, so will convert bool to -/+ 1 value
   int moveValue = -1;
   if ( true == Up )
      moveValue = 1;

   enum UErrorCode error = U_ZERO_ERROR; 

   gregorianCalendar->roll( (enum Calendar::EDateFields)Field, moveValue, error );
   

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }

}


int JavaGregorianCalendar::get(int Operation)
{

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }


   enum UErrorCode error = U_ZERO_ERROR; 

   int returnInt = gregorianCalendar->get( (enum UCalendarDateFields) Operation, error );
   

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }



   return returnInt;

}


JavaDate JavaGregorianCalendar::getTime()
{

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }



   enum UErrorCode error = U_ZERO_ERROR; 

   UDate uDate = gregorianCalendar->getTime( error );
   

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }


   JavaDate retDate( (long long)uDate );

   return retDate;


}


void JavaGregorianCalendar::setTime( JavaDate & date )
{

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }



   enum UErrorCode error = U_ZERO_ERROR; 

   gregorianCalendar->setTime( date.getUDate(), error );
   

   if ( U_FAILURE( error ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }

}


void JavaGregorianCalendar::set( int field,
                                 int value )
{

   if ( U_FAILURE( errorConstruct ) )
   {
      DString idiStr = I_( "VALUE=" );
      DStringA tmp( u_errorName(errorConstruct) );
      idiStr += DString( tmp );

      THROWELEMENTALIDI( JAVAGREGORIANCALENDAR_NAME,
                         I_("JavaGregorianCalendar::constructor"),
                         JavaGregorianCalendar::JAVAGREGORIANCALENDAR_ICU_ERROR,
                         languagesMapForJavaGregorianCalendar,
                         idiStr);
   }


   gregorianCalendar->set( (enum UCalendarDateFields ) field, value );


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
// $Log:   Y:/VCS/iFastAWD/dicore/javagregoriancalendar.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:12   kovacsro
// Initial revision.
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
