#pragma once

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

#include <iostream>
#include <bf/log/abstractlogtarget.hpp>

namespace bf {
namespace log {

class BFUTIL_LINKAGE LogTargetConsole : public AbstractLogTarget {
private:
   LogTargetConsole()
      : bSuspend_( false )
   {}
public:
   ~LogTargetConsole() {}

   static LogTargetConsole* create();

   virtual void write( const DString& str );

   void suspend() { bSuspend_ = true; }
   bool isSuspended() const { return bSuspend_; }
   void restart() { bSuspend_ = false; }

private:
   bool bSuspend_;

private:
   LogTargetConsole( const LogTargetConsole& rhs );
};

}  // namespace log
}  // namespace bf


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bf/log/logtargetconsole.hpp-arc  $
//
//   Rev 1.1   Feb 20 2009 14:44:26   purdyech
//ZTS Revision 6
//
//   Rev 1.0   Aug 12 2003 10:14:10   PURDYECH
//Initial revision.
//
