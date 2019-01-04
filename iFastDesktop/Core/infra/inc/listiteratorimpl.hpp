#ifndef LISTITERATORIMPL_HPP
#define LISTITERATORIMPL_HPP

#  pragma message( "including "__FILE__ )

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

/**@pkg DICBOCORE */    


#include <vector>

#include "data.hpp"

class ListIteratorImpl
{
   public:
      ListIteratorImpl();
      ListIteratorImpl( const ListIteratorImpl& copy );
      ~ListIteratorImpl();

      const ListIteratorImpl& operator=( const ListIteratorImpl& copy );

      bool operator==( const ListIteratorImpl& copy ) const;
      bool operator!=( const ListIteratorImpl& copy ) const;

      void makeEnd();
      void addItem( const Data* pData );

      const Data* operator*() const;
      void operator++();
      ListIteratorImpl operator++( int );


   private:
      bool _bEnd;
      int  _nCurrentIndex;
      std::vector< const Data * > _vecDataRecords;
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
// $Log:   Y:/VCS/iFastAWD/inc/listiteratorimpl.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:12   kovacsro
//Initial revision.
// 
//    Rev 1.5   06 Nov 2000 14:37:42   dt14177
// removed the javadoc-style comments
// from around the copyright notice
// 
//    Rev 1.4   31 Oct 2000 11:17:52   dt14177
// fixed namespace dependency
// 
//    Rev 1.3   27 Oct 2000 14:40:00   dt14177
// cleanup
// 
//    Rev 1.2   Jan 04 2000 04:46:26   DT29758
//  
// 
//    Rev 1.1   Dec 30 1999 08:04:42   DT29758
// Modified comments to Java-Doc style
// 
//    Rev 1.0   Jun 21 1999 17:15:28   DT22388
//  
// 
//    Rev 1.0   Feb 25 1999 10:55:38   DMAL
//  
//
//


#endif


