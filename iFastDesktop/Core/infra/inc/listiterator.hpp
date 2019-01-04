#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP

#  pragma message( "including "__FILE__ )

/** 
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

/**@pkg DICBOCORE */  


#include "commonport.h"

class ListIteratorImpl;
class Data;


// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif


class CBOBASE_LINKAGE ListIterator
{
   public:
      ListIterator();
      ListIterator( const ListIterator& copy );
      ~ListIterator();

      const ListIterator& operator=( const ListIterator& copy );

      bool operator==( const ListIterator& copy ) const;
      bool operator!=( const ListIterator& copy ) const;

      const Data* operator*() const;
      void operator++();
      ListIterator operator++( int );

      friend class ListBaseImpl;

      void makeEnd();
      void addItem( const Data * pData );

   private:

      ListIteratorImpl * _pImpl;
};



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
// $Log:   Y:/VCS/iFastAWD/inc/listiterator.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:12   kovacsro
//Initial revision.
// 
//    Rev 1.4   28 Nov 2001 12:42:06   dt14177
// fixed linkage define
// 
//    Rev 1.3   27 Oct 2000 14:22:40   dt14177
// cleanup
// 
//    Rev 1.2   Jan 04 2000 04:46:24   DT29758
//  
// 
//    Rev 1.1   Dec 30 1999 08:04:40   DT29758
// Modified comments to Java-Doc style
// 
//    Rev 1.0   Jun 21 1999 17:15:22   DT22388
//  
// 
//    Rev 1.1   May 27 1999 13:33:32   DMAL
// moved to methods from private to public.  Code
// checked in for Dave Sayers.
// 
//    Rev 1.0   Feb 25 1999 10:55:34   DMAL
//  
//
//



#endif


