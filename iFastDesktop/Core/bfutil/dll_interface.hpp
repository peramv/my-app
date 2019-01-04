#pragma once

#include <dstring.hpp>
#include <windows.h>
#include <assert.h>
#include <boost\utility.hpp>
#include <condition.hpp>

#pragma warning( push )
#pragma warning( disable: 4275 )
class Dll_Interface : public boost::noncopyable
{
public:
   Dll_Interface()
   : hMod_( NULL )
   {}

   virtual ~Dll_Interface()
   {
      if( NULL == hMod_ )
      {
         ::FreeLibrary( hMod_ );
         hMod_ = NULL;
      }
   }


   virtual bool load() = 0;
protected:
   virtual void DllLoadFailureMsg( const char* pszDll )
   {
      assert( FALSE );
      // console app or windowed?
   }

   virtual void ProcLoadFailureMsg( const char* pszDll, const char* pszProcedure )
   {
      assert( FALSE );
      // console app or windowed?
   }


   template< typename _FP >
   _FP resolve( _FP& fp, const char* pszProcName )
   {
      fp = reinterpret_cast< _FP >( ::GetProcAddress( hMod_, pszProcName ) );
      if( NULL == fp )
      {
         ProcLoadFailureMsg( NULL, pszProcName );
      }
      return(fp);
   }

   HMODULE hMod_;
};


#pragma warning( pop )
