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
// ^FILE   : RegistryValue.cpp
// ^AUTHOR : Michael McGarry & Mike Ward
// ^DATE   : 19 May 97
//
// ----------------------------------------------------------
//
// ^CLASS    : RegistryValue
//
// ^MEMBER VARIABLES :
//    RegistryValueType  _type     - STRING, DWORD, etc.
//    unsigned long      _ulValue  - value if type is DWORD
//    string             _strValue - value if type is STRING
//    string             _name     - name of the value
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef REGISTRYVALUE_HPP
   #include "registryvalue.hpp"
#endif
#ifndef SYMBOLS_H
   #include "symbols.h"
#endif


//******************************************************************************
//              Public Methods
//******************************************************************************

RegistryValue::RegistryValue()
   : _type( NONE),
     _ulValue( 0 ),
     _strValue( "" ),
     _name( "" )
{
   _type = NONE;
}

RegistryValue::RegistryValue( const RegistryValue &copy )
{
   this->operator =( copy );
}

RegistryValue::RegistryValue( const DStringA &name )
   : _type( NONE),
     _ulValue( 0 ),
     _strValue( "" ),
     _name( name )
{
}

RegistryValue::RegistryValue( const DStringA &name,
                              const DStringA &value )
   : _type( STRING),
     _ulValue( 0 ),
     _strValue( value ),
     _name( name )
{
}

RegistryValue::RegistryValue( const DStringA &name,
                              const unsigned long &value )
   : _type( DWORD),
     _ulValue( value ),
     _strValue( "" ),
     _name( name )
{
}

RegistryValue::~RegistryValue()
{
}

const DStringA &RegistryValue::getName() const
{
   return _name;
}

RegistryValue::RegistryValueType RegistryValue::getType() const
{
   return _type;
}

RegistryValue &RegistryValue::setName( const DStringA &name )
{
   _name = name;

   return *this;
}

unsigned long RegistryValue::getAsDWORD() const
{
   return _ulValue;
}

DStringA RegistryValue::getAsString() const
{
   return _strValue;
}

void RegistryValue::set( const DStringA &value )
{
   // set as a string
   _strValue = value;
   _type = STRING;
}

void RegistryValue::set( const unsigned long &value )
{
   // Set as an unsigned long
   _ulValue = value;
   _type = DWORD;
}

RegistryValue &RegistryValue::operator=( const RegistryValue &copy )
{
   if ( this != &copy )
   {
      this->_name     = copy._name;
      this->_type     = copy._type;
      this->_strValue = copy._strValue;
      this->_ulValue  = copy._ulValue;
   }

   return *this;
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
// $Log:   Y:/VCS/iFastAWD/dicore/registryvalue.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:26   kovacsro
// Initial revision.
// 
//    Rev 1.5   Nov 19 1999 14:49:20   DMUM
// made the get...() methods const
//
//    Rev 1.4   Jul 12 1999 09:08:30   DMUM
// Applied standards to constructors to fix an Uninitialized
// member report.
//
//    Rev 1.3   22 Feb 1999 13:57:44   DT14177
// more UNICODE stuff
//
//    Rev 1.2   18 Feb 1999 10:38:30   DT14177
// UNICODE
//
//    Rev 1.1   Jan 28 1999 14:03:20   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:36   DMUM
//
//
//    Rev 1.2   10 Nov 1997 15:25:36   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.1   20 Jun 1997 07:44:58   dmum
// Documentation
//
//    Rev 1.0   May 22 1997 15:33:40   dmum
//
//
//


