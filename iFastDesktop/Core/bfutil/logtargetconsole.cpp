#include "stdafx.h"
#include <bf/log/logtargetconsole.hpp>

using namespace bf::log;

LogTargetConsole* LogTargetConsole::create() 
{ 
   return new LogTargetConsole; 
}

void LogTargetConsole::write( const DString& str )
{
   if( false == bSuspend_ && str.size() > 0 ) 
   { 
      // dump the contents of the string 'str' to the console,
      // but don't put the linestamp size
      const I_CHAR* psz = str.c_str();
      // skip first linestamp
      psz += 38;

      for( ; 0x00 != *psz; ++psz )
      {
         fputwc( *psz, stdout );
         if( 0x0a == *psz ) {
            int iChar = 0;
            for( ; iChar < 39 && 0x00 != (*psz); ++iChar, ++psz );
            --psz;
         }
      }
   }
}

