#ifndef IMESSAGINGSERVERHANDLER_H
#define IMESSAGINGSERVERHANDLER_H

#include "Messaging.h"

namespace MessagingFramework
{

class IMessage;
class KeyValuePairs;


/**
 * The IMessagingServerHandler interface declares the interface that is to be
 * implemented by applications that act as "messaging servers" (i.e., receive
 * and process messages sent by other products/applications.  One of the
 * serviceXXXX methods will be called on this interface by the MessagingServer
 * object when a message is received from another application.
 *
 * @see MessagingServer
 */
class DIMESSAGE_LINKAGE IMessagingServerHandler
{
   public:
      /**
       * Destructor
       */
      virtual ~IMessagingServerHandler() {}


      /**
       * This method is called by the MessagingServer object when a message encoded
       * with key/value pairs of data is received.
       *
       * @param message - the message received
       * @param strDomain - the domain identifier associated with the message
       * @param strRequest - the request identifier associated with the message
       * @param mapArgs - the KeyValuePairs object that holds all key/value pairs of data that were sent in the message
       * @param hashReturn - the KeyValuePairs object that should be populated with return data (key/value pairs) during the method call
       *
       * @see IMessage
       * @see KeyValuePairs
       */
      virtual void serviceMessage( const IMessage& message,
                                   const std::string& strDomain,
                                   const std::string& strRequest,
                                   const KeyValuePairs& mapArgs,
                                   KeyValuePairs& hashReturn ) = 0;


      /**
       * This method is called by the MessagingServer object when a message encoded
       * with an XML document is received.
       *
       * @param message - the message received
       * @param strDomain - the domain identifier associated with the message
       * @param strRequest - the request identifier associated with the message
       * @param strXMLDocument - the XML document (as a string) that was sent in the message
       *
       * @return a string containing the response XML document
       *
       * @see IMessage
       */
      virtual std::string serviceXMLMessage( const IMessage& message,
                                             const std::string& strDomain,
                                             const std::string& strRequest,
                                             const std::string& strXMLDocument ) = 0;
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



