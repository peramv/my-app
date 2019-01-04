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
// ^FILE   : Configuration.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 12 May 97
//
// ----------------------------------------------------------
//
// ^CLASS    : Configuration
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef SYMBOL_H
   #include "symbols.h"
#endif

#ifndef CONFIGURATION_HPP
   #include "configuration.hpp"
#endif


//******************************************************************************
//              Public Methods
//******************************************************************************

Configuration::Configuration()
   : _name( NULL_STRING )
{
}

Configuration::Configuration( const DString &name )
   : _name( name )
{
}

Configuration::Configuration( const Configuration &copy )
{
   this->operator =( copy );
}

Configuration::~Configuration()
{
}

const DString &Configuration::getName() const
{
   return _name;
}

void Configuration::setName( const DString &name )
{
   _name = name;
}

ConfigValue Configuration::getValue( const DString &key ) const
{
   ConfigValue value;

   // Find the key
   config_const_iterator iter = _data.find( key );

   if ( iter != _data.end() )
   {
      // if found, grab the value
      value =  ( *iter ).second;
   }

   return value;
}

DString Configuration::getValueAsString( const DString &key ) const
{
   return getValue( key ).asString();
}

int Configuration::getValueAsInt( const DString &key ) const
{
   return getValue( key ).asInt();
}

long Configuration::getValueAsLong( const DString &key ) const
{
   return getValue( key ).asLong();
}

double Configuration::getValueAsDouble( const DString &key ) const
{
   return getValue( key ).asDouble();
}

bool Configuration::isEmpty()
{
   return _data.empty();
}

void Configuration::set( const DString &key, const ConfigValue &value )
{
   // See if the key has already been stored
   config_iterator iter = _data.find( key );

   if ( iter == _data.end() )
   {
      // Key not found, insert the pair
      _data.insert( config_type( key, value ) );
   }
   else
   {
      // Override the previous value
      ( *iter ).second = value;
   }
}

void Configuration::set( const ConfigPair &configPair )
{
   // See if the key has already been stored
   config_iterator iter = _data.find( configPair._pair.first );

   if ( iter == _data.end() )
   {
      // Key not found, insert the pair
      _data.insert( configPair._pair );
   }
   else
   {
      // Override the previous value
      ( *iter ).second = configPair._pair.second;
   }
}

bool Configuration::set( const DString &keyEqValue )
{
   bool success = false;
   DString::size_type eq;

   if ( DString::npos != ( eq = keyEqValue.find( '=' ) ) )
   {
      // Extract the key
      DString key = keyEqValue.substr( 0, eq );
      // Extract the value
      DString value = keyEqValue.substr( eq + 1 );

      strip( key );
      strip( value );

      // Make sure we have a key.  The value can be null
      if ( ! key.empty() )
      {
         // Store them
         ConfigValue cvValue( value );
         set( key, cvValue );
         success = true;
      }
   }

   return success;
}

Configuration &Configuration::operator =( const Configuration &copy )
{
   if ( this != &copy )
   {
      this->_name = copy._name;
      this->_data = copy._data;
   }

   return *this;
}

Configuration::iterator Configuration::begin()
{
   return Configuration::iterator( _data.begin(), _data.end() );
}

Configuration::iterator Configuration::end()
{
   return Configuration::iterator( _data.end(), _data.end() );
}

//******************************************************************************
//
// CLASS:   ConfigPair
//
// ^MEMBER VARIABLES :
//
//    config_type _pair - A key and value
//
//******************************************************************************

Configuration::ConfigPair::ConfigPair( const DString &key,
                                       const ConfigValue &value )
  : _pair( key, value )
{
}

Configuration::ConfigPair::ConfigPair( const config_type &data )
   : _pair( data.first, data.second )
{
}

Configuration::ConfigPair::ConfigPair( const ConfigPair &copy )
{
   this->operator =( copy );
}

Configuration::ConfigPair::~ConfigPair()
{
}

const DString &Configuration::ConfigPair::getKey() const
{
   return _pair.first;
}

const ConfigValue &Configuration::ConfigPair::getValue() const
{
   return _pair.second;
}

int Configuration::ConfigPair::getValueAsInt() const
{
   return _pair.second.asInt();
}

DString Configuration::ConfigPair::getValueAsString() const
{
   return _pair.second.asString();
}

long Configuration::ConfigPair::getValueAsLong() const
{
   return _pair.second.asLong();
}

double Configuration::ConfigPair::getValueAsDouble() const
{
   return _pair.second.asDouble();
}

Configuration::ConfigPair &Configuration::
ConfigPair::operator =( const ConfigPair &copy )
{
   if ( this != &copy )
   {
      (DString &)this->_pair.first = copy._pair.first;
      this->_pair.second = copy._pair.second;
   }

   return *this;
}

//******************************************************************************
//
// CLASS:   iterator
//
// ^MEMBER VARIABLES :
//
//    config_iterator _configPtr - pointer to a pair
//    config_iterator _endPtr    - pointer to the end (one passed the end)
//
//
//******************************************************************************

Configuration::iterator::iterator()
{
}

Configuration::iterator::iterator( const iterator &copy )
{
   this->operator =( copy );
}

Configuration::iterator::~iterator()
{
}

Configuration::ConfigPair Configuration::iterator::operator *() const
{
   return Configuration::ConfigPair( *_configPtr );
}

Configuration::iterator &Configuration::iterator::operator ++()
{
   if ( ! ( _configPtr == _endPtr ) )
   {
      // Not at end, so increment
      ++_configPtr;
   }

   return *this;
}

Configuration::iterator &Configuration::
iterator::operator =( const iterator &copy )
{
   if ( this != &copy )
   {
      this->_configPtr = copy._configPtr;
      this->_endPtr    = copy._endPtr;
   }

   return *this;
}

bool Configuration::iterator::operator ==( const iterator &compare ) const
{
   return this->_configPtr == compare._configPtr;
}

bool Configuration::iterator::operator !=( const iterator &compare ) const
{
   return ! operator ==( compare );
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : Configuration::iterator::iterator
//
// ^DESCRIPTION : Private Constructor
//
// ^PARAMETERS  :
//   ^^ const config_iterator &configPtr -
//   ^^ const config_iterator &endPtr -
//
// ^RETURNS     : none
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
Configuration::iterator::iterator( const config_iterator &configPtr,
                                   const config_iterator &endPtr )
   : _configPtr( configPtr ), _endPtr( endPtr )
{
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
// $Log:   Y:/VCS/iFastAWD/dicore/configuration.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:28   kovacsro
// Initial revision.
// 
//    Rev 1.3   22 Feb 1999 13:57:22   DT14177
// more UNICODE stuff
// 
//    Rev 1.2   18 Feb 1999 10:35:20   DT14177
// UNICODE
// 
//    Rev 1.1   Jan 28 1999 14:02:36   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:00   DMUM
//
//
//    Rev 1.4   Jul 11 1998 16:08:10   dmum
// Development - too many changes to describe
//
//    Rev 1.3   Nov 10 1997 13:02:58   DSZD
// Configuration extension. IMPORT/EXPORT.
// MACRO inclusion
//
//    Rev 1.2   25 Jun 1997 08:12:48   dmum
// Conforming to C++ standards
//
//    Rev 1.1   24 Jun 1997 13:47:20   dmum
//
//
//    Rev 1.0   02 Jun 1997 12:31:20   dmum
//
//
//

