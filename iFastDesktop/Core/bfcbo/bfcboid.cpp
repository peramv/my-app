#include "bfcboid.hpp"
#include <bfutil\bfcritsec.hpp>
#include <bfutil\bfguard.hpp>
#include <dstring.hpp>

#include <map>

static BFCritSec g_sLastId;

static std::map< DString, int > g_mapCBOId;

int BF_OBJ_TYPE::s_lastId_ = 0;

BF_OBJ_TYPE OBJ_TYPE_NONE( I_("") );

BF_OBJ_TYPE::BF_OBJ_TYPE()
: id_( 0 )
{
}

BF_OBJ_TYPE::BF_OBJ_TYPE( const I_CHAR* pszName )
: id_( 0 )
{
   std::map< DString, int >::iterator it;
   DString key( pszName );

   BFGuard g( g_sLastId );
   it = g_mapCBOId.find( key );

   if( it != g_mapCBOId.end() )
   {
      id_ = (*it).second;
      return;
   }
   
   id_ = ++s_lastId_;
   g_mapCBOId[ key ] = id_;
}


