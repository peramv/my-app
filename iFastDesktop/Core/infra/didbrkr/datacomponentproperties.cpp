//******************************************************************************
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
// ^FILE   : DataComponentProperties.cpp
// ^AUTHOR : Tony Stryker
// ^DATE   : 10/31/96
//
// ----------------------------------------------------------
//
// ^CLASS : DataComponentProperties
//
// ^MEMBER VARIABLES :
//    ^NAME :        _id
//    ^TYPE :        string
//    ^DESCRIPTION : Name of this DataComponentProperties object
//
//    ^NAME :        _defaultValue
//    ^TYPE :        string
//    ^DESCRIPTION : Default value for DataComponent objects with this property.
//
//    ^NAME :        _repeatable
//    ^TYPE :        boolean
//    ^DESCRIPTION : Specifies if DataComponent objects with this property can
//                   have repeat areas.
//
//    ^NAME :        _fixedRepeatSize
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Size of the fixed repeat area.
//
//    ^NAME :        _repeatComponentName
//    ^TYPE :        string
//    ^DESCRIPTION : Name of the repeat component.
//
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DIDBRKR_DLL

#ifndef INCLUDED_FSTREAM
#define INCLUDED_FSTREAM
   #include <fstream>
#endif

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef DATACOMPONENTPROPERTIES_HPP
   #include "datacomponentproperties.hpp"
#endif

//******************************************************************************
//              Public Methods
//******************************************************************************

void reverseEndian( char * tp, int count )
{
   char ch;
   int mid  = ( count + 1 ) >> 1;
   for ( int i = 0; i <= mid; ++i )
   {
       ch = tp[ i ];
       tp[ i ] = tp[ count - i - 1 ];
       tp[ count - i - 1 ] = ch;
   }
}


SEVERITY readLine( i_istream & fCnd,
                   DString & linebuf,
                   unsigned long numToRead,
                   bool fBigEndian )
{
   // read an individual line
   I_CHAR ch;
   unsigned long chCount = 0;
   while ( 1 )
   {
      fCnd.read( ( I_CHAR * ) &ch, sizeof( ch ) );
      ++chCount;
      if ( fBigEndian )
      {
         reverseEndian( ( char * ) &ch, sizeof( ch ) );
      }
      if ( 0 == ch )
      {
         break;
      }
      linebuf.append( 1, ch );
      if ( chCount == numToRead )
      {
         break;
      }
   }
   return NO_SEVERITY;
}


DataComponentProperties::~DataComponentProperties()
{
}



bool DataComponentProperties::operator== (
                              const DataComponentProperties &properties ) const
{
     if ( _repeatable != properties._repeatable )
   {
      return false;
   }

   return true;
}



bool DataComponentProperties::operator!= (
                              const DataComponentProperties &properties ) const
{
   return !(*this == properties);
}



//******************************************************************************
//              Protected Methods
//******************************************************************************

DataComponentProperties::DataComponentProperties(
 const DString &id,
 bool repeatable,
 EPROPERTY_TYPE eType
 ) :
   _repeatable( repeatable ),
   _vectorIndex( 0L ),
   _cameFromRepository( false ),
   _eType( eType )
{
}



DataComponentProperties::DataComponentProperties(
   const DataComponentProperties &copy ) :
   _repeatable( false ),
   _vectorIndex( 0L )
{
   *this = copy;
}



DataComponentProperties &
DataComponentProperties::operator= ( const DataComponentProperties &copy )
{
   if ( this == &copy )
   {
      return *this;
   }

   _repeatable = copy._repeatable;
   _cameFromRepository = copy._cameFromRepository;
   _eType = copy._eType;

   return *this;
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
// $Log:   Y:/VCS/iFastAWD/didbrkr/datacomponentproperties.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:20   kovacsro
// Initial revision.
// 
//    Rev 1.17   Apr 26 2001 13:30:18   dt24433
// Remove unused headers.
// 
//    Rev 1.16   Mar 02 2001 14:16:12   dt24433
// Added support for getType (used instead of dynamic casting & RTTI).
// Split getId into getId and getName as appropriate.
// 
//    Rev 1.15   Jan 19 2001 16:54:40   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.14   Nov 22 2000 07:04:44   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.13   Sep 27 2000 13:34:20   dt17817
// Remove ClientLocale from DataCompoentProperties
//
//    Rev 1.12   Jun 08 2000 11:49:44   dtwk
// Add support for case-insensitivity
//
//    Rev 1.11   May 31 2000 09:32:42   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.10   Jan 16 2000 14:10:30   dtwk
// Remove dead method
//
//    Rev 1.9   Oct 06 1999 11:35:18   DCYK
// Add support for redefines.
//
//
//    Rev 1.8   Oct 04 1999 15:24:54   DCYK
// More changes for thread safety.  Make all functions that returned
// a DString & or a const DString &, just return a DString.
//
//
//    Rev 1.7   Oct 04 1999 10:23:10   DCYK
// Threading fixes.
//
//
//    Rev 1.6   Jul 16 1999 09:19:42   DCYK
// .
//
//    Rev 1.5   May 26 1999 17:20:56   DCYK
// Add support for getting & setting numerical id's.
//
//
//    Rev 1.4   May 06 1999 16:43:58   DCYK
// Fixes for repository.
//
//
//    Rev 1.3   Apr 20 1999 16:49:28   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.2   Mar 05 1999 10:25:24   DCYK
// Changes for I18N.
//
//
//    Rev 1.1   Jan 28 1999 14:03:48   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   29 Jul 1998 20:30:44   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.8   Jul 22 1998 10:12:38   dcyk
// Performance improvements
// from Paul D.
//
//
//    Rev 1.7   Jun 18 1998 11:11:16   dcyk
// Remove tracing.
//
//
//    Rev 1.6   Nov 10 1997 14:46:58   dcyk
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//
//    Rev 1.5   23 Sep 1997 16:27:46   dcyk
// Added vectorIndex member, to support
// Data objects storing elements in a vector,
// not a map.
//
//
//    Rev 1.4   08 Sep 1997 14:26:06   dcyk
// Changes to reduce memory usage.
//
//
//    Rev 1.3   07 Aug 1997 15:04:48   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.2   24 Jul 1997 09:33:16   dcyk
// Use new tracing stuff.
//
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
//
//
//    Rev 1.1   08 Jul 1997 09:02:50   dcyk
// Added STL casting operators and RTTI.
//
//
//    Rev 1.0   Jun 13 1997 16:31:30   DTWK
//
//
//    Rev 1.10   13 Jun 1997 16:20:02   dcyk
//
//
//    Rev 1.9   May 01 1997 08:42:54   dcyk
// Added documentation.
//
//
//    Rev 1.8   Apr 11 1997 08:56:54   dcyk
//
//
//    Rev 1.7   Apr 04 1997 09:03:58   dcyk
// Minor performance improvement
// by in-lining getId().
//
//
//    Rev 1.6   Mar 25 1997 15:48:10   dcyk
// Removed setId.
//
// Made getDefaultValue, formatValue,
// getMaxLength pure virtual.
//
//
//    Rev 1.5   Feb 11 1997 14:18:34   dcyk
// Added #include "srcprag.h" to suppress
// compiler warnings.
// Removed references to ReturnCode
// member data _lastReturn, since no one
// is using it.  This partially alleviates the
// memory leak from not deleting
// DataProperties objects.
//
//
//    Rev 1.4   Jan 19 1997 12:51:14   DRUS
// Added == and != operators.  Fixed error in copy constructor.
//
//    Rev 1.3   Jan 15 1997 17:26:38   dcyk
// Changed the "_id" member variable so it
// is just an ID, and not the file name.
//
//    Rev 1.2   Jan 10 1997 08:39:56   DRUS
// Reordered methods.
//
//    Rev 1.1   Nov 21 1996 14:38:10   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:12   DRUS
//
//


