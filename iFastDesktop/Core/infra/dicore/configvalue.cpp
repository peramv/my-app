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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ConfigValue.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 12 May 97
//
// ----------------------------------------------------------
//
// ^CLASS    : ConfigValue
//
// ^MEMBER VARIABLES :
//                      string _value - value to store
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef CONFIGVALUE_HPP
   #include "configvalue.hpp"
#endif

//******************************************************************************
//              Public Methods
//******************************************************************************

ConfigValue::ConfigValue( const ConfigValue &copy )
   : _value( copy._value )
{
}

ConfigValue::ConfigValue( const DString &value )
   : _value( value )
{
}

ConfigValue::ConfigValue( const int value )
   : _value( NULL_STRING )
{
   set( value );
}

ConfigValue::~ConfigValue()
{
}

DString ConfigValue::asString() const
{
   return _value;
}

int ConfigValue::asInt() const
{
   // Convert the value to an integer
   return i_ttoi( _value.c_str() );
}

long ConfigValue::asLong() const
{
   // Convert the value to a long

   return i_ttol( _value.c_str() );
}

double ConfigValue::asDouble() const
{
   // Convert the value to a long
   // !!! we will need to write our own UNICODE version
   return atof( DStringA( _value ).c_str() );
}

bool ConfigValue::operator ==( const ConfigValue &compare ) const
{
   return this->_value == compare._value;
}

bool ConfigValue::operator !=( const ConfigValue &compare ) const
{
   return( ! this->operator ==( compare ) );
}

bool ConfigValue::isNull() const
{
   return _value.empty();
}

ConfigValue &ConfigValue::operator =( const ConfigValue &copy )
{
   if ( this != &copy )
   {
      this->_value = copy._value;
   }

   return *this;
}

void ConfigValue::set( const DString &value )
{
   _value = value;
}

void ConfigValue::set( const int value )
{
   // Convert the integer into a string
   I_CHAR  szValue[ 32 ];

   i_sprintf( szValue, I_( "%d" ), value );

   _value = szValue;
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
// $Log:   Y:/VCS/iFastAWD/dicore/configvalue.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:28   kovacsro
// Initial revision.
// 
//    Rev 1.3   22 Feb 1999 13:57:24   DT14177
// more UNICODE stuff
// 
//    Rev 1.2   18 Feb 1999 10:37:58   DT14177
// UNICODE
// 
//    Rev 1.1   Jan 28 1999 14:02:38   DMUM
// Check in for VCPP 6.0
// 
//    Rev 1.0   Dec 09 1998 13:51:02   DMUM
//  
//
//    Rev 1.4   Nov 10 1997 13:02:56   DSZD
// Configuration extension. IMPORT/EXPORT.
// MACRO inclusion
//
//    Rev 1.3   10 Jul 1997 13:05:42   dmum
// Default constructor not needed
//
//    Rev 1.2   25 Jun 1997 08:07:30   dmum
// Conforming to C++ standards
//
//    Rev 1.1   24 Jun 1997 13:47:18   dmum
//
//
//    Rev 1.0   02 Jun 1997 12:31:16   dmum
//
//
//

