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
//    Copyright 1996 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DataComponent.cpp
// ^AUTHOR : Tony Stryker
// ^DATE   : 11/16/96
//
// ----------------------------------------------------------
//
// ^CLASS : DataComponent
//
// ^INHERITS FROM : None
//
// ^MEMBER VARIABLES :
//    ^NAME :        _value
//    ^TYPE :        string
//    ^DESCRIPTION:  Contains the value for this object.
//
//    ^NAME :        _dataProperties
//    ^TYPE :        DataComponentProperties *
//    ^DESCRIPTION:  Pointer to the properties for this object.  Points to
//                   either a DataProperties object or a DataElementProperties
//                   object.
//
//    ^NAME :        _pBase
//    ^TYPE :        DataComponent *
//    ^DESCRIPTION:  Pointer to the "base" DataComponent.
//
//                   DataComponent's descendants are designed to be able to
//                   contain other DataComponent descendants.  The base pointer
//                   points to the "top level" DataComponent instance.  The
//                   "top level's" _pBase is NULL.
//
//                   **Note that this is not a pointer the instance one
//                    level up, but a pointer to the very top level.
//
//                   It is important that it is not possible to set _pBase
//                   from any public interface of DC or any of its descendants.
//
//                   Also, if someone gets a copy, DC1, of DC2, and DC2 is
//                   inside DC3, the copy's _pBase should be set to NULL,
//                   because the copy (DC1) is NOT a part of DC3.
//
//
//
// ^CODING COMMENTS  :
//
// The DataComponent class is the parent class in a "Composite" pattern, that
// includes the Data and DataElement classes.
//
// Many of the function return values that are pointers to DataComponent
// objects or references, will need to be typecast to either Data or DataElement
// objects.
//
//******************************************************************************

#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef DATACOMPONENT_HPP
   #include "datacomponent.hpp"
#endif
#ifndef DATACOMPONENTPROPERTIES_HPP
   #include "datacomponentproperties.hpp"
#endif
#ifndef DATAELEMENT_HPP
   #include "dataelement.hpp"
#endif
#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif

#ifndef DIDBRKR_H
   #include "didbrkr.h"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

typedef DataComponentProperties DCP;

const long DataComponent::REPEAT_INDEX_NOT_FOUND = -1L;

//******************************************************************************
//              Public Methods
//******************************************************************************

DataComponent::~DataComponent()
{
}


bool DataComponent::operator== ( const DataComponent &data ) const
{
   if ( _dataProperties  &&  data._dataProperties )
   {
      if ( *_dataProperties != *data._dataProperties )
      {
         return false;
      }
   }
   else if ( ( _dataProperties  &&  !data._dataProperties )  ||
             ( !_dataProperties  &&  data._dataProperties ) )
   {
      return false;
   }

   return true;
}


bool DataComponent::operator!= ( const DataComponent &data ) const
{
   return !(*this == data);
}


long DataComponent::findRepeatIndex( const DString &value ) const
{
   return DataComponent::REPEAT_INDEX_NOT_FOUND;
}


unsigned long DataComponent::getRepeatCount() const
{
   return 0;
}


unsigned long DataComponent::getId() const
{
   if ( _dataProperties )
   {
      return _dataProperties->getId();
   }
   else
   {
      return _id;
   }
}


//******************************************************************************
//              Protected Methods
//******************************************************************************

DataComponent::DataComponent( const DString &value,
                              DataComponentProperties *properties,
                              bool checkValidity,
                              DataComponent *pBase,
                              const ClientLocale &clientLocale ) :
   _dataProperties( properties ), _pBase( pBase ),
   _id( ULONG_MAX )
{
}


DataComponent::DataComponent( DataComponent *pBase,
                              const DString &value,
                              DataComponentProperties *properties,
                              bool checkValidity,
                              const ClientLocale &clientLocale ) :
   _dataProperties( properties ), _pBase( pBase ),
   _id( ULONG_MAX )
{
}


DataComponent::DataComponent( const DataComponent &copy ) :
   _dataProperties( 0 ),
   _id( ULONG_MAX )
{
   *this = copy;
}


DataComponent &DataComponent::operator=( const DataComponent &copy )
{
   if ( this == &copy )
   {
      return *this;
   }

   return *this;
}


DataComponent * DataComponent::_getBase()
{
   return _pBase ? _pBase : this;
}


const DataComponent * DataComponent::_getBaseConst() const
{
   return _pBase ? _pBase : const_cast<DataComponent *> (this);
}


bool DataComponent::_setValue( const DString &value, bool checkValidity,
                               const ClientLocale *pClientLocale,
                               bool displayFormat,
                               const DString &i18nFormat )
{
   return true;
}


//******************************************************************************
//              Private Methods
//******************************************************************************


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
// $Log:   Y:/VCS/iFastAWD/didbrkr/datacomponent.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:18   kovacsro
// Initial revision.
// 
//    Rev 1.17   Mar 02 2001 14:17:22   dt24433
// Changed getId to no longer take unsigned long reference parameter.
// 
//    Rev 1.16   Nov 22 2000 07:04:42   dt17817
// Reduce runtime memory requirements of Data objects
// 
//    Rev 1.15   Sep 05 2000 06:19:48   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
// 
// 
//    Rev 1.14   May 31 2000 09:32:38   dtwk
// Change locale string to ClientLocale object
// 
//    Rev 1.13   Oct 06 1999 11:35:14   DCYK
// Add support for redefines.
// 
// 
//    Rev 1.12   Jul 28 1999 14:19:12   DCYK
// Performance improvements.
// 
// 
//    Rev 1.11   Jul 26 1999 09:49:24   DCYK
// Change "USen" to "enUS".
// 
// 
//    Rev 1.10   Jul 14 1999 15:43:42   DCYK
// Fix problem with initializing one-byte signed fields.
// 
// 
//    Rev 1.9   Jul 07 1999 09:53:12   DCYK
// Fix for 1-byte signed fields.
// 
// 
//    Rev 1.8   Jun 29 1999 09:45:34   DCYK
// Added setLocale methods.
// Fixed minor bugs.
// 
// 
//    Rev 1.7   24 Jun 1999 16:03:46   DCYK
// Fix minor bugs.
// 
// 
//    Rev 1.6   Jun 18 1999 09:33:48   DCYK
// Add ID's for dynamically created elements.
// 
// 
//    Rev 1.5   Jun 06 1999 13:22:54   DTWK
// Cleanup I18N formatting
// 
//    Rev 1.4   May 24 1999 10:41:20   DTWK
// Add internationalized formatting and new types (date, decimal, percent, currency)
//
//    Rev 1.3   Apr 20 1999 16:49:26   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.2   Mar 05 1999 10:25:22   DCYK
// Changes for I18N.
//
//
//    Rev 1.1   Jan 28 1999 14:03:46   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   29 Jul 1998 20:30:40   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.10   Jul 22 1998 11:45:18   dcyk
// Performance improvements
// by Paul D.
//
//
//    Rev 1.9   Jul 08 1998 10:04:52   dcyk
// Performance improvements.
//
//
//    Rev 1.8   Jun 18 1998 11:11:04   dcyk
// Remove tracing.
//
//
//    Rev 1.7   Nov 11 1997 10:11:14   dcyk
// Fixed inclusion guards for srcprag.h
//
//
//    Rev 1.6   Nov 10 1997 16:38:24   dcyk
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//
//    Rev 1.5   09 Sep 1997 12:27:58   dcyk
// Delete the _value pointer in the
// destructor.
//
//
//    Rev 1.4   08 Sep 1997 14:25:52   dcyk
// Changes to reduce memory usage.
//
//
//    Rev 1.3   07 Aug 1997 15:04:34   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.2   24 Jul 1997 09:33:04   dcyk
// Use new tracing stuff.
//
// Switch to unsigned long, UINT, UCHAR &
// USHORT to save space.
//
//
//    Rev 1.1   08 Jul 1997 09:02:20   dcyk
// Removed "_repeatValues".
// Added STL casting operators and RTTI.
//
//
//    Rev 1.0   Jun 13 1997 16:31:28   DTWK
//
//
//    Rev 1.13   13 Jun 1997 16:20:00   dcyk
//
//
//    Rev 1.12   Jun 08 1997 18:48:54   DTWK
// Add Certificate Authentication / Remove dependencies on class Returncode.
//
//    Rev 1.11   05 Jun 1997 17:57:42   dcyk
// Added default parameter to getValue.
// Made findRepeatIndex return a -1,
// an error.  This function should not be called.
//
//
//    Rev 1.10   May 09 1997 16:42:22   dcyk
// Improved standards compliance.
//
//
//    Rev 1.9   May 01 1997 08:42:40   dcyk
// Added documentation.
//
//
//    Rev 1.8   Apr 11 1997 08:56:52   dcyk
//
//
//    Rev 1.7   Mar 25 1997 15:47:06   dcyk
// Removed:  isPropertyChanged,
// isPropertyDefined.
//
// Made isDefault and resetValue pure virtual.
//
//
//    Rev 1.6   Feb 11 1997 14:16:40   dcyk
// Added #include "srcprag.h" to suppress
// compiler warnings.
//
//
//    Rev 1.5   Jan 27 1997 14:10:04   DRUS
// Removed error in copy.  The repeat count pointer is
// now updated after the copy.
//
//    Rev 1.4   Jan 19 1997 12:58:04   DRUS
// Implemented == and != operators.  Fixed copy constructor.
// Fixed isValid to handle proper lengths in decimals.
//
//    Rev 1.3   Jan 10 1997 08:47:14   DRUS
// Implemented getRepeatCount and removed unneeded
// methods which are available through other classes to
// get, set, and reset values and to determine if repeatable.
//
//    Rev 1.2   Dec 31 1996 13:41:54   DRUS
// Implemented the isElement() method to identify objects as either
// Data or DataElements.  Checked the validity of values passed into the
// setValue() method.
//
//    Rev 1.1   Nov 21 1996 14:38:08   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:10   DRUS
//
//

