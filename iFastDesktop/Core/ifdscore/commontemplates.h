#pragma once

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */


#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif

#ifndef INCLUDED_VECTOR
#define INCLUDED_VECTOR
#include <vector>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
#include <map>
#endif

#ifndef INCLUDED_SET
#define INCLUDED_SET
#include <set>
#endif

#ifndef MUTEXSEMAPHORE_HPP
   #include <mutexsemaphore.hpp>
#endif

//
// Vector of strings
//
typedef std::vector<DString> string_vector;
typedef string_vector::const_iterator string_vector_const_iterator;
typedef string_vector::iterator string_vector_iterator;


//
// Vector of ulongs
//
typedef std::vector<unsigned long> ul_vector;
typedef ul_vector::const_iterator ul_vector_const_iterator;
typedef ul_vector::iterator ul_vector_iterator;


//
// Map - pair of strings
//
typedef std::map< DString, DString, std::less<DString> > string_map;
typedef string_map::value_type string_map_type;
typedef string_map::const_iterator string_map_const_iterator;
typedef string_map::iterator string_map_iterator;


//
// Map - ulong to string
//
typedef std::map< unsigned long, DString, std::less<unsigned long> > ulString_map;
typedef ulString_map::value_type ulString_map_type;
typedef ulString_map::const_iterator ulString_map_const_iterator;
typedef ulString_map::iterator ulString_map_iterator;


//
// Map - ulong to ulong
//
typedef std::map< unsigned long, unsigned long,
std::less<unsigned long> > ulul_map;
typedef ulul_map::value_type ulul_map_type;
typedef ulul_map::const_iterator ulul_map_const_iterator;
typedef ulul_map::iterator ulul_map_iterator;


//
// Set - set of strings
//
typedef std::set< DString, std::less< DString > > string_set;


template <class A>
int numElements( const A & array )
{
   return(sizeof( array ) / sizeof( array[ 0 ] ));
}



template <typename A, typename B>
typename A::iterator findInContainer( A &container, const B &element )
{
   A::iterator iter = container.begin();

   while( container.end() != iter )
   {
      if( element == *iter )
      {
         return(iter);         
      }
      ++iter;
   }

   return(container.end());
}


template <typename A, typename B>
typename A::iterator findInValueInMap( const A &mapIn, const B &value )
{
   A::const_iterator iter = mapIn.begin();

   while( mapIn.end() != iter )
   {
      if( value == ( *iter ).second )
      {
         return(iter);         
      }
      ++iter;
   }

   return(mapIn.end());
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/commontemplates.h-arc  $
//
//   Rev 1.2   Oct 22 2004 09:01:56   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.1   Oct 09 2002 17:41:46   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:36   SMITHDAV
//Initial revision.
// 
//    Rev 1.13   23 Oct 2000 13:13:50   dt14177
// cleanup
// 
//    Rev 1.12   Aug 09 2000 14:05:54   dtwk
// Fix syntax error
// 
//    Rev 1.11   Aug 09 2000 13:40:34   dtwk
//  
// 
//    Rev 1.10   Aug 09 2000 08:24:06   dtwk
// Added a couple of stl types for vectors and maps
// 
//    Rev 1.9   May 04 2000 16:36:00   DT14177
// removed TGenericMap
// 
//    Rev 1.8   Nov 29 1999 07:26:56   dtwk
// Add findInContainer template function
// 
//    Rev 1.7   Jul 15 1999 09:51:40   DT14177
// Fixed BoundsChecker-reported buffer overrun error.
// 
//    Rev 1.6   Jul 12 1999 10:42:38   DMUM
// Fixes bug where uninitialized memory was being access.
//
//    Rev 1.5   Mar 09 1999 12:47:34   DT20842
// Changed DStringA to DString
//
//    Rev 1.4   22 Feb 1999 11:46:42   DT14177
// fixed DString and const I_CHAR stuff
//
//    Rev 1.3   18 Feb 1999 10:29:28   DT14177
// UNICODE
//
//    Rev 1.2   Jan 28 1999 14:05:32   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:40:02   DMUM
// Check in for DICORE
//
//    Rev 1.3   10 Nov 1997 15:01:38   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.2   29 Aug 1997 14:01:34   dmum
// added data_obj_map
//
//    Rev 1.1   13 Jun 1997 17:22:14   dmum
// added data_ptr_map
//
//    Rev 1.0   May 22 1997 08:55:02   dmum
//
//
//


