#ifndef IMESSAGE_H
#define IMESSAGE_H


#include "Messaging.h"


namespace MessagingFramework
{

class IMessageReceiver;
class KeyValuePairs;
class ICommChannel;


/**
 * The IMessage interface declares the interface used by message objects.
 * A message object conforming to the IMessage interface supports 2 types
 * of encodings for application-specific message data: (1) XML document
 * and (2) Key/Value pairs.
 */
class DIMESSAGE_LINKAGE IMessage
{
   public:
      /**
       * Destructor
       */
      virtual ~IMessage() {}


      /**
       * Sets the XML document. Use of this method implies that key/value pairs
       * are not used.
       *
       * @param strXMLDocument - the XML document to set
       */
      virtual void setXMLDocument( const std::string& strXMLDocument ) = 0;


      /**
       * Retrieves the XML document.  Callers should only call this method after
       * first calling "isFormatXML" and getting a return of 'true'.
       *
       * @return the XML document as a string
       */
      virtual const std::string& getXMLDocument() const = 0;


      /**
       * Adds a key/value pair as an argument.  Use of this method implies that XML
       * documents are not used.
       *
       * @param strKey - the key
       * @param strValue - the value
       */
      virtual void addArgument( const std::string& strKey, const std::string& strValue ) = 0;


      /**
       * Determines whether a key/value pair associated with the specified key is
       * present as an argument.
       *
       * @param strKey - the key
       *
       * @return boolean indicating whether the key is present
       */
      virtual bool hasArgument( const std::string& strKey ) const = 0;


      /**
       * Retrieves the value for the specified key.
       *
       * @param strKey - the key
       *
       * @return the value associated with the key
       */
      virtual const std::string& getArgument( const std::string& strKey ) const = 0;


      /**
       * Resets the value associated with the specified key.  The implementation (and
       * any side effects) of this method are not necessarily the same as for the
       * "addArgument" method.
       *
       * @param strKey - the key whose value is to updated
       * @param strValue - the new value for the specified key
       */
      virtual void setArgument( const std::string& strKey, const std::string& strValue ) = 0;


      /**
       * Retrieves the list of all keys in the collection of key/value pair arguments.
       *
       * @param vecKeys - a vector of strings that will be populated with keys
       */
      virtual void getArgumentList( STRING_LIST& vecKeys ) const = 0;


      /**
       * Returns the arguments encoded as an IDI string.
       *
       * @return string containing the key/value pairs encoded in IDI format
       */
      virtual std::string argumentsToIDI() const = 0;


      /**
       * Retrieves the destination for the message.
       *
       * @return string containing the message destination
       */
      virtual const std::string& getDestination() const = 0;


      /**
       * Retrieves the format of the message.  This method should be used primarily
       * as a debugging/diagnostic/information tool.  It should not be used for
       * processing logic.
       *
       * @return string indicating the encoding type
       */
      virtual const std::string& getFormat() const = 0;


      /**
       * Determines if the message is using XML "format" for its application-specific
       * data.
       *
       * @return boolean indicating whether XML "format" is used
       */
      virtual bool isFormatXML() const = 0;


      /**
       * Determines if the message is using Key/Value pairs "format" for its
       * application-specific data.
       *
       * @return boolean indicating whether Key/Value pairs is used
       */
      virtual bool isFormatNameValuePairs() const = 0;


      /**
       * Retrieves the request identifier for this message.
       *
       * @return string containing the request identifier
       */
      virtual const std::string& getRequest() const = 0;


      /**
       * Retrieves the domain for this message.
       *
       * @return string containing the domain
       */
      virtual const std::string& getDomain() const = 0;


      /**
       * Retrieves the application-specific message data as a string.  This method
       * should be only used for debugging/diagnostic purposes.  If the message is
       * using Key/Value pair encoding, the message data is returned in IDI encoding.
       *
       * @param strMessageData - the string to populate with message data
       */

      virtual void getMessageData( std::string& strMessageData ) const = 0;


      /**
       * Retrieves all of the message data (both header and application data) as a string.
       * This method should only be used for debugging/diagnostic purposes.
       *
       * @return string containing all of the data (header and application) for this message
       */
      virtual std::string flatten() const = 0;


      /**
       * Retrieves all of the header data as a string.  This method should only be used
       * for debugging/diagnostic purposes.
       *
       * @return string containing the header data
       */
      virtual std::string flattenHeader() const = 0;


      /**
       * Retrieves all of the application data as a string (regardless of internal coding).
       * This method should only be used for debugging/diagnostic purposes.
       *
       * @return string containing the application data
       */
      virtual std::string flattenBody() const = 0;


      /**
       * Sends a <b>1-way</b> message to its destination.  The response message (if
       * any) is ignored.
       *
       * @return boolean indicating success/failure
       */
      virtual bool send() = 0;


      /**
       * Sends a <b>2-way synchronous</b> message to its destination.
       *
       * @param responseMessage - the response message to populate on return from destination
       *
       * @return boolean indicating success/failure
       */
      virtual bool send( IMessage& responseMessage ) = 0;


      /**
       * Sends a <b>2-way asynchronous</b> message to its destination.
       *
       * @param messageReceiver - an object conforming to the IMessageReceiver interface that
       * will receive the message once it arrives
       *
       * @return boolean indicating success/failure of the send
       *
       * @see IMessageReceiver
       */
      virtual bool sendAsync( IMessageReceiver& messageReceiver ) = 0;


      /**
       * Marks a message as being "1-way" only (no response).  This should only be used on
       * "request" messages.
       */
      virtual void makeOneWay() const = 0;


      /**
       * Determines if a message is marked as "1-way" (no response).  This should only be
       * used on "request" messages.
       *
       * @return boolean indicating whether it's marked as "1-way"
       */
      virtual bool isOneWay() const = 0;


      /**
       * Retrieves a message header value for the specified key.
       *
       * @param strKey - the key for the message header variable
       *
       * @return string value associated with the header key
       */
      virtual const std::string& getHeaderValue( const std::string& strKey ) const = 0;


      /**
       * Reads a string from the communications channel into a buffer
       * allocated by the caller of this method.
       *
       * @param buffer - pointer to the buffer to populate
       * @param bufferLen - size of the buffer
       *
       * @return boolean indicating success/failure
       */
      virtual bool hasHeaderValue( const std::string& strKey ) const = 0;


      /**
       * Retrieves the major version of the framework used to generate the message.
       *
       * @return integer representing the major version
       */
      virtual int getMajorVersion() const = 0;


      /**
       * Retrieves the minor version of the framework used to generate the message.
       *
       * @return integer representing the minor version
       */
      virtual int getMinorVersion() const = 0;


      /**
       * Retrieves the collection of key/value pairs for this message.  This method
       * should only be used for key/value "mode" of encoding (i.e., "addPair")
       *
       * @return reference to the KeyValuePairs object that contains the collection
       *
       * @see KeyValuePairs
       */
      virtual const KeyValuePairs& getNameValuePairs() const = 0;


      /**
       * Sets an error text on the message object.  <b>Invoking this method will
       * mark the message as being "in an error state"</b>.
       *
       * @param pszErrorText - description of the error
       */
      virtual void setError( const char* pszErrorText ) = 0;


      /**
       * Determines if the message object is in an "error state" (see setError).
       *
       * @return boolean indicating whether its in an error state
       */
      virtual bool isError() const = 0;


      /**
       * Retrieves the error text associated with the message object.
       *
       * @return the error text as a string
       */
      virtual const std::string& getErrorText() const = 0;


      /**
       * Rebuilds a message object by reading its data from the communications channel.
       * This method <b>may destroy any existing contents</b> of the message object.
       *
       * @param pCommChannel - pointer to the communications channel object to read from
       *
       * @return boolean indicating success/failure
       */
      virtual bool reconstitute( ICommChannel* pCommChannel ) = 0;


      /**
       * Writes the message object contents out to the communications channel.
       *
       * @param pCommChannel - pointer to the communications channel object to write to
       *
       * @return boolean indicating success/failure
       */
      virtual bool write( ICommChannel* pCommChannel ) const = 0;


      /**
       * Updates the message object to indicate that it's a reply message
       */
      virtual void markAsReply() = 0;


      /**
       * Retrieves the header section of the message object as a collection of
       * key/value pairs.
       *
       * @return reference to KeyValuePairs object
       *
       * @see KeyValuePairs
       */
      virtual const KeyValuePairs& getHeader() const = 0;


      /**
       * Establishes the message sender's identity
       *
       * @param strSender - string indicating the name of the message sender
       */
      virtual void setSender( const std::string& strSender ) = 0;


      /**
       * Retrieves the message sender's identity
       *
       * @return string indicating the name of the message sender.  If the message
       * sender's identity has not been set, an empty string is returned.
       */
      virtual const std::string& getSender() const = 0;


      /**
       * Clears the message data and resets the error state allowing a client
       * to reuse of a single message object to send multiple, sequential,
       * messages using the same service/domain/request id.
       */
      virtual void clearData() = 0;
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



