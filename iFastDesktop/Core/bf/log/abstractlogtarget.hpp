#pragma once

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

#include <dstring.hpp>

namespace bf {
namespace log {

/**
 * This is a base class for 
 */
class BFUTIL_LINKAGE AbstractLogTarget 
{
public:
   virtual ~AbstractLogTarget() {}

   /**
    * This function is called when the a LogStream needs to be put to this
    * LogTarget. 
    * 
    * In general a concrete log target which is suspended by a call to
    * the suspend function should ignore requests to write data.
    * 
    * @param str    A DString which contains the formatted information to put to the
    *               concrete log target.
    * 
    * @see #suspend
    */
   virtual void write( const DString& str ) = 0;

   /**
    * This function is called when the logging target is to be suspended.
    * A suspended logging target should ignore all flush and write requests.
    * 
    * A suspended logging target is restarted by a call to the restart function.
    * 
    * @see #flush
    * @see #write
    * @see #suspend
    */
   virtual void suspend() = 0;
   /**
    * This function is called when the logging target is to be restarted
    * after a previous suspension.
    * 
    * @see #suspend
    */
   virtual void restart() = 0;

   virtual bool isSuspended() const = 0;

protected:
   AbstractLogTarget() 
   {}
   AbstractLogTarget( const AbstractLogTarget& rhs );    // no implementation ... noncopyable

};


}  // namespace log
}  // namespace bf


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bf/log/abstractlogtarget.hpp-arc  $
//
//   Rev 1.1   Feb 20 2009 14:03:22   purdyech
//ZTS_Revision 6
//
//   Rev 1.0   Aug 12 2003 10:14:02   PURDYECH
//Initial revision.
//
