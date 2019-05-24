// Generated file
#include <srcprag.h>
#include <commonport.h>
#include <windows.h>
#include "version_App.hpp"


#define STRINGIZE( s ) L#s
#define MAKESTRING( m, s ) m(s)

#define THIS_BUILD I_("0") 
#define THIS_COMPUTER I_("Local Computer")
#define THIS_VERSION Dev

#define THIS_VERSION_DEBUG THIS_VERSION## (Checked Build)
#define THIS_VERSION_STR MAKESTRING( STRINGIZE, THIS_VERSION )
#define THIS_VERSION_STR_D MAKESTRING( STRINGIZE, THIS_VERSION_DEBUG )

namespace ifds {
   const DString& getAppVersion()
   {
#ifdef _DEBUG
      static const DString sVersion( THIS_VERSION_STR_D );
#else
      static const DString sVersion( THIS_VERSION_STR );
#endif
      return(sVersion);
   }

   unsigned long getAppBuildNumber()
   {
      static const unsigned long ulBuildNumber = 0; /* THIS_BUILD; */
      return(ulBuildNumber);
   }

   DString getAppBuildNumberS()
   {
      static const DString sBuildNumber = THIS_BUILD;
      return(sBuildNumber);
   }

   const DString& getAppBuildComputer()
   {
      static const DString sBuildComputer( THIS_COMPUTER );
      return(sBuildComputer);
   }

   IfdsVersionInfo::IfdsVersionInfo(DString versionIn): versionMajor(I_("")), versionMinor(I_("")), isQA(false)
   {
      DString::size_type pos=0;
      I_CHAR c = versionIn[pos];
      DString::size_type paramLen = versionIn.length();
      while(pos < paramLen && (c < '0' || c > '9'))
      {
         c = versionIn[++pos];
      }
      int numDot = 0;
      while(pos < paramLen && (c >= '0' || c <= '9' || c == '.'))
      {
         
         if(c == '.')
         {
            if(numDot++ > 0)
            {
               c = versionIn[++pos];
               break; // just consuming the dot
            }
         }
         versionMajor += c;
         c = versionIn[++pos];
      }

      while(pos < paramLen && (c >= '0' || c <= '9' || c == '.'))
      {
         versionMinor += c;
         c = versionIn[++pos];
      }
      if(versionMinor.length() > 2 && versionMinor[0] == '0' && versionMinor[1] == '.' )
         isQA = true;

   }

}  // namespace ifds
