#pragma once


#include <dstring.hpp>
#include <bf/log/logtargetdisk.hpp>


class IFastLogFile : public bf::log::LogTargetDisk {
private:
   DString appName_;
   DString logFile_;
public:
   IFastLogFile( const DString& dstrPath, const DString& dstrFile, bool bEnabled )
   : LogTargetDisk( dstrPath.c_str(), dstrFile.c_str(), false, true, bEnabled )
   {}
    
public:

   virtual const I_CHAR* getOpenMode( const DString& dstrFile, bool bAppend, bool bUnicode ) const {
      // always open in append mode with no unicode
      return( I_("a") );
   }
};
