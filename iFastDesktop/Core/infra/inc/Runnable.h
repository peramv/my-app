#ifndef RUNNABLE_H
#define RUNNABLE_H


namespace MessagingFramework
{

/**
 * The Runnable class is an abstract base class (ABC) (or "interface" in
 * Java terminology) that's used to mimic Java's approach to multi-threading.
 * As with Java, this class is meant to be subclassed for your derived
 * class to "run" on a separate thread.
 *
 * @see Thread
 *
 * @author: Paul Dardeau
 */
class DIMESSAGE_LINKAGE Runnable
{
   public:
      /**
       * Destructor
       */
      virtual ~Runnable() {}

      /**
       * "Run"/execute the derived class' functionality. This is typically
       * used in the context of multi-threading where a Thread object will
       * call this method when the thread is started.
       */
      virtual void run() = 0;
};

}

#endif


//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//


