#pragma once

#include <algorithm>
#include <srcprag.h>
#include <commonport.h>
#include <condition.hpp>

// Reminder Macros
// Programmer can force a compile message to appear as a 'reminder' to complete a task
// Syntax:
//    #pragma BF_REMINDER( message )
#define BF_STRINGIZE( L )	#L
#define BF_MAKESTRING( M, L )	M(L)
#define BF_SRCLINE \
	BF_MAKESTRING( BF_STRINGIZE, __LINE__ )
#define BF_REMINDER_TEXT \
	__FILE__ "(" BF_SRCLINE ") : Reminder: "

#define BF_REMINDER( M ) message( BF_REMINDER_TEXT #M )



// Common algorithms for IFDS
namespace ifds
{
   // function object to delete an object
   // can be used for stl container cleanup in containing class dtors.
   struct DeleteObject
   {
      template< typename T >
      void operator()( const T* ptr ) const
      {
         delete ptr;
      }
   };

   template<class _MAP> inline
   void clean_map(_MAP _M )
   {
      // we *must* post-increment the iterator (i.e. iter++, not ++iter)
      // or the iterator will be invalid.  Post-incrementation semantics 
      // cause a *copy* of the iterator to be passed to the std::erase function
      // and the *original* iterator to be incremented
      for( _MAP::iterator iter = _M.begin(); iter != _M.end(); _M.erase( iter++ ) )
      {
         // delete the value pointer
         delete ((*iter).second);
      }
   }

   template< class _VEC> inline
   void clean_vector( _VEC _V )
   {
      std::for_each( _V.begin(), _V.end(), DeleteObject() );
   }

};

