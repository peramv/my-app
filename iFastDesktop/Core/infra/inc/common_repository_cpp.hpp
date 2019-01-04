#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

TRepository<DString,$ImplClass$> $ImplClass$::repository;

//****************************************************************************
//     * * *  Begin   STATIC (Class) Methods   * * *
//****************************************************************************

bool $ImplClass$::deregister( $ImplClass$ * pInstance,
                              const DString& strKey,
                              bool fKeepUnused )
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, "deregister( " $ImplClassStr$ " *, const DString&, bool )" );
#else
   TRACE_METHOD( "$ImplClass$", "deregister( $ImplClass$ *, const DString&, bool )" );
#endif

   return $ImplClass$::repository.deregister( strKey, fKeepUnused );
}



bool $ImplClass$::deleteAllUnused( void )
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, "deleteAllUnused()" );
#else
   TRACE_METHOD( "$ImplClass$", "deleteAllUnused()" );
#endif

   return $ImplClass$::repository.deleteAllUnused();
}



bool $ImplClass$::deleteAll( void )
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, "deleteAll()" );
#else
   TRACE_METHOD( "$ImplClass$", "deleteAll()" );
#endif

   return $ImplClass$::repository.deleteAll();
}



bool $ImplClass$::getInstanceList( vector<DString>& keyList )
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, "getInstanceList( vector<DString>& )" );
#else
   TRACE_METHOD( "$ImplClass$", "getInstanceList( vector<DString>& )" );
#endif

   return $ImplClass$::repository.getInstanceList( keyList );
}


bool $ImplClass$::getInstanceList( map<DString, int, less<DString> >& keyMap )
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, "getInstanceList( map<DString, int, less<DString> >& )" );
#else
   TRACE_METHOD( "$ImplClass$", "getInstanceList( map<DString, int, less<DString> >& )" );
#endif

   return $ImplClass$::repository.getInstanceList( keyMap );
}


$ImplClass$ * $ImplClass$::getInstancePointer( $ImplClass$ * pInstance )
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, "getInstancePointer( " $ImplClassStr$ " * )" );
#else
   TRACE_METHOD( "$ImplClass$", "getInstancePointer( $ImplClass$ * )" );
#endif

   return ($ImplClass$ *) $ImplClass$::repository.getInstancePointer( pInstance->getKey() );
}

bool $ImplClass$::isRepositoryEmpty()
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, "isRepositoryEmpty( )" );
#else
   TRACE_METHOD( "$ImplClass$", "isRepositoryEmpty( )" );
#endif

   return $ImplClass$::repository.isEmpty( );
}

void $ImplClass$::dumpRepository( DString &strOut )
{
#ifdef $ImplClassStr$
   TRACE_METHOD( $ImplClassStr$, "dumpRepository( DString &)" );
#else
   TRACE_METHOD( "$ImplClass$", "dumpRepository( DString &)" );
#endif
   
   strOut = "";

   map< DString, int, less<DString> > keyMap;

   $ImplClass$::repository.getInstanceList( keyMap );

   map< DString, int, less<DString> >::const_iterator iter = keyMap.begin();
   map< DString, int, less<DString> >::const_iterator end  = keyMap.end();

   char buffer[20];

   while ( iter != end )
   {
      strOut += "Item : ";
      strOut += (*iter).first;
      strOut += " Has ";
      strOut += itoa( (*iter).second, buffer, 10);
      strOut += " references.\r\n";

      ++iter;
   }
}

//****************************************************************************
//     * * *  End   STATIC (Class) Methods   * * *
//****************************************************************************
