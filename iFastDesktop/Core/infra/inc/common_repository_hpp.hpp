#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999 by DST Systems, Inc.
 */

/**@pkg DICBOCORE */    

  public:
      static bool deregister( $ImplClass$ * pInstance,
                              const DString& strKey,
                              bool fKeepUnused=false );
      static bool deleteAllUnused( void );
      static bool deleteAll( void );
      static bool getInstanceList( vector<DString>& keyList );
      static bool getInstanceList( map<DString, int, less<DString> >& keyMap );
      static $ImplClass$ * getInstancePointer( $ImplClass$ * pInstance );
      static bool isRepositoryEmpty( );
      static void dumpRepository( DString &strOut );

  private:
      static TRepository<DString,$ImplClass$> repository;

