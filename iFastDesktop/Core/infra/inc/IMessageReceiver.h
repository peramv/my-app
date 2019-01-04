#ifndef IMESSAGERECEIVER_H
#define IMESSAGERECEIVER_H

#include "Messaging.h"

namespace MessagingFramework
{

class IMessage;

/**
 * The IMessageReceiver class is an abstract base class (interface)
 * that is used for asynchronous messaging by a message client.  This
 * interface is used to provide the "callback" mechanism invoked by the
 * messaging framework once the message response is returned.
 */
class DIMESSAGE_LINKAGE IMessageReceiver
{
   public:
      /**
       * Destructor
       */
      virtual ~IMessageReceiver() {}

      /**
       * Abstract method that provides the "callback" mechanism
       * for replies in a asynchronous calling by a messaging client.
       * This method <b>MUST</b> be overridden by derived classes.
       *
       * @param message - the response message
       *
       * @see IMessage
       */
      virtual void receiveMessage( const IMessage& message ) = 0;
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


