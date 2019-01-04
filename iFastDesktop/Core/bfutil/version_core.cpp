// Generated file
#include "stdafx.h"
#include <srcprag.h>
#include <commonport.h>
#include <windows.h>
#include "version_Core.hpp"


#define STRINGIZE( s ) L#s
#define MAKESTRING( m, s ) m(s)

#define THIS_BUILD 0
#define THIS_COMPUTER I_("Local Computer")
#define THIS_VERSION BF Core Dev

#define THIS_VERSION_DEBUG THIS_VERSION## (Checked Build)
#define THIS_VERSION_STR MAKESTRING( STRINGIZE, THIS_VERSION )
#define THIS_VERSION_STR_D MAKESTRING( STRINGIZE, THIS_VERSION_DEBUG )

namespace ifds {
   const DString& getCoreVersion()
   {
#ifdef _DEBUG
      static const DString sVersion( THIS_VERSION_STR_D );
#else
      static const DString sVersion( THIS_VERSION_STR );
#endif
      return sVersion;
   }
   
   unsigned long getCoreBuildNumber()
   {
      static const unsigned long ulBuildNumber = THIS_BUILD;
      return ulBuildNumber;
   }

   const DString& getCoreBuildComputer()
   {
      static const DString sBuildComputer( THIS_COMPUTER );
      return sBuildComputer;
   }
}  // namespace ifds
