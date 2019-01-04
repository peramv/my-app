#ifndef MESSAGE_H
#define MESSAGE_H


#include "Messaging.h"
#include "IMessage.h"


namespace MessagingFramework
{

class MessagingAgent;
class ICommChannel;
class KeyValuePairs;
class IMessageReceiver;



/**
 * The Message class is used primarily be applications that must "send" a message
 * to another application.  This class is the <B>ONLY CLASS THAT YOU NEED IN ORDER
 * TO SEND A MESSAGE (synchronously)</b>.
 */
class DIMESSAGE_LINKAGE Message : public IMessage
{
   public:
      /**
       * Default constructor.  This constructor should only be used for constructing
       * an empty message to be populated with a message response.
       */
      Message();


      /**
       * Constructor - constructs a message to send to a service
       *
       * @param strProductOrService - the name of the service to receive the message
       * @param strDomain - the domain identifier of the message
       * @param strRequestIdentifier - the request identifier of the message
       */
      Message( const std::string& strProductOrService,
               const std::string& strDomain,
               const std::string& strRequestIdentifier );


      /**
       * Destructor
       */
      ~Message();



      /**
       * Sets the XML document. Use of this method implies that key/value pairs
       * are not used.
       *
       * @param strXMLDocument - the XML document to set
       */
      virtual void setXMLDocument( const std::string& strXMLDocument );


      /**
       * Retrieves the XML document.  Callers should only call this method after
       * first calling "isFormatXML" and getting a return of 'true'.
       *
       * @return the XML document as a string
       */
      virtual const std::string& getXMLDocument() const;


      /**
       * Adds a key/value pair as an argument.  Use of this method implies that XML
       * documents are not used.
       *
       * @param strKey - the key
       * @param strValue - the value
       */
      virtual void addArgument( const std::string& strKey, const std::string& strValue );


      /**
       * Determines whether a key/value pair associated with the specified key is
       * present as an argument.
       *
       * @param strKey - the key
       *
       * @return boolean indicating whether the key is present
       */
      virtual bool hasArgument( const std::string& strKey ) const;


      /**
       * Retrieves the value for the specified key.
       *
       * @param strKey - the key
       *
       * @return the value associated with the key
       */
      virtual const std::string& getArgument( const std::string& strKey ) const;


      /**
       * Resets the value associated with the specified key.  The implementation (and
       * any side effects) of this method are not necessarily the same as for the
       * "addArgument" method.
       *
       * @param strKey - the key whose value is to updated
       * @param strValue - the new value for the specified key
       */
      virtual void setArgument( const std::string& strKey, const std::string& strValue );


      /**
       * Retrieves the list of all keys in the collection of key/value pair arguments.
       *
       * @param vecKeys - a vector of strings that will be populated with keys
       */
      void getArgumentList( STRING_LIST& vecKeys ) const;


      /**
       * Returns the arguments encoded as an IDI string.  This method is useful for
       * debugging/diagnostics.
       *
       * @return string containing the key/value pairs encoded in IDI format
       */
      virtual std::string argumentsToIDI() const;


      /**
       * Allows the addition of multiple key value pairs at one time.
       *
       * @param strData - An IDI string containing one or more key value pairs.
       */
      virtual void addIDIToArguments( const std::string& strData );


      /**
       * Retrieves the destination for the message.
       *
       * @return string containing the message destination
       */
      virtual const std::string& getDestination() const;


      /**
       * Retrieves the format of the message.  This method should be used primarily
       * as a debugging/diagnostic/information tool.  It should not be used for
       * processing logic.
       *
       * @return string indicating the encoding type
       */
      virtual const std::string& getFormat() const;


      /**
       * This method is used internally within the messaging framework.  If you're
       * "outside" (user) of the framework DON'T USE IT!!!
       */
      virtual int getCodedFormat() const;


      /**
       * Retrieves the request identifier for this message.
       *
       * @return string containing the request identifier
       */
      virtual const std::string& getRequest() const;


      /**
       * Retrieves the domain for this message.
       *
       * @return string containing the domain
       */
      virtual const std::string& getDomain() const;


      /**
       * Retrieves the application-specific message data as a string.  This method
       * should be only used for debugging/diagnostic purposes.  If the message is
       * using Key/Value pair encoding, the message data is returned in IDI encoding.
       *
       * @param strMessageData - the string to populate with message data
       */
      virtual void getMessageData( std::string& strMessageData ) const;


      /**
       * Retrieves all of the message data (both header and application data) as a string.
       * This method should only be used for debugging/diagnostic purposes.
       *
       * @return string containing all of the data (header and application) for this message
       */
      virtual std::string flatten() const;


      /**
       * Retrieves all of the header data as a string.  This method should only be used
       * for debugging/diagnostic purposes.
       *
       * @return string containing the header data
       */
      virtual std::string flattenHeader() const;


      /**
       * Retrieves all of the application data as a string (regardless of internal coding).
       * This method should only be used for debugging/diagnostic purposes.
       *
       * @return string containing the application data
       */
      virtual std::string flattenBody() const;


      /**
       * Sends a <b>1-way</b> message to its destination.  The response message (if
       * any) is ignored.
       *
       * @return boolean indicating success/failure
       */
      virtual bool send();


      /**
       * Sends a <b>2-way synchronous</b> message to its destination.
       *
       * @param responseMessage - the response message to populate on return from destination
       *
       * @return boolean indicating success/failure
       */
      virtual bool send( IMessage& responseMessage );


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
      virtual bool sendAsync( IMessageReceiver& messageReceiver );


      /**
       * Writes the message object contents out to the communications channel.
       *
       * @param pCommChannel - pointer to the communications channel object to write to
       *
       * @return boolean indicating success/failure
       */
      bool write( ICommChannel* pCommChannel ) const;


      /**
       * Retrieves the header section of the message object as a collection of
       * key/value pairs.
       *
       * @return reference to KeyValuePairs object
       *
       * @see KeyValuePairs
       */
      virtual const KeyValuePairs& getHeader() const;


      /**
       * Retrieves the application/user data associated with the message.  This is all
       * data other than that which is stored in the message header.  If the message
       * is an XML message, this method returns the XML document.  If it's a key/value
       * pairs message, it retuns the collection of key/value pairs encoded as an IDI
       * string.
       *
       * @return the application level data associated with the message
       */
      std::string getUserData() const;


      /**
       * Retrieves the collection of key/value pairs for this message.  This method
       * should only be used for key/value "mode" of encoding (i.e., "addPair")
       *
       * @return reference to the KeyValuePairs object that contains the collection
       *
       * @see KeyValuePairs
       */
      const KeyValuePairs& getNameValuePairs() const;


      /**
       * Determines if the message is using XML "format" for its application-specific
       * data.
       *
       * @return boolean indicating whether XML "format" is used
       */
      bool isFormatXML() const;


      /**
       * Determines if the message is using Key/Value pairs "format" for its
       * application-specific data.
       *
       * @return boolean indicating whether Key/Value pairs is used
       */
      bool isFormatNameValuePairs() const;


      /**
       * Marks a message as being "1-way" only (no response).  This should only be used on
       * "request" messages.
       *
       * @see isOneWay
       */
      void makeOneWay() const;


      /**
       * Determines if a message is marked as "1-way" (no response).  This should only be
       * used on "request" messages.
       *
       * @return boolean indicating whether it's marked as "1-way"
       *
       * @see makeOneWay
       */
      bool isOneWay() const;


      /**
       * Retrieves the major version of the messaging framework library
       *
       * @return integer representing the major version of the library
       *
       * @see getLibraryMinorVersion
       * @see getMajorVersion
       * @see getMinorVersion
       */
      static int getLibraryMajorVersion();


      /**
       * Retrieves the minor version of the messaging framework library
       *
       * @return integer representing the minor version of the library
       *
       * @see getLibraryMajorVersion
       * @see getMajorVersion
       * @see getMinorVersion
       */
      static int getLibraryMinorVersion();


      /**
       * Retrieves the major version of the framework used to generate the message.
       * Note that this can be different from the local library version if the message
       * object was sent from another application.
       *
       * @return integer representing the major version of the message
       *
       * @see getMinorVersion
       * @see getLibraryMajorVersion
       * @see getLibraryMinorVersion
       */
      int getMajorVersion() const;


      /**
       * Retrieves the minor version of the framework used to generate the message.
       * Note that this can be different from the local library version if the message
       * object was sent from another application.
       *
       * @return integer representing the minor version of the message
       *
       * @see getMajorVersion
       * @see getLibraryMajorVersion
       * @see getLibraryMinorVersion
       */
      int getMinorVersion() const;


      /**
       * Retrieves a message header value for the specified key.
       *
       * @param strKey - the key for the message header variable
       *
       * @return string value associated with the header key
       */
      const std::string& getHeaderValue( const std::string& strKey ) const;


      /**
       * Reads a string from the communications channel into a buffer
       * allocated by the caller of this method.
       *
       * @param buffer - pointer to the buffer to populate
       * @param bufferLen - size of the buffer
       *
       * @return boolean indicating success/failure
       */
      bool hasHeaderValue( const std::string& strKey ) const;


      /**
       * Sets an error text on the message object.  <b>Invoking this method will
       * mark the message as being "in an error state"</b>.
       *
       * @param pszErrorText - description of the error
       */
      void setError( const char* pszErrorText );


      /**
       * Determines if the message object is in an "error state" (see setError).
       *
       * @return boolean indicating whether its in an error state
       */
      bool isError() const;


      /**
       * Retrieves the error text associated with the message object.
       *
       * @return the error text as a string
       */
      const std::string& getErrorText() const;


      /**
       * Updates the message object to indicate that it's a reply message
       */
      void markAsReply();


      /**
       * Establishes the sender identity for all messages that are sent. This
       * method can be called once and will automatically set the sender identity
       * for all messages subsequently sent.
       *
       * @param strSenderIdentity - string indicating the name of the message sender
       *
       * @see setSender
       * @see getSender
       */
      static void setSenderIdentity( const std::string& strSenderIdentity );


      /**
       * Establishes the message sender's identity for this message.  The
       * setSenderIdentity should be preferable for most uses.
       *
       * @param strSender - string indicating the name of the message sender
       *
       * @see getSender
       * @see setSenderIdentity
       */
      void setSender( const std::string& strSender );


      /**
       * Retrieves the message sender's identity
       *
       * @return string indicating the name of the message sender.  If the message
       * sender's identity has not been set, an empty string is returned.
       *
       * @see setSender
       * @see setSenderIdentity
       */
      const std::string& getSender() const;

      /**
       * Clears the message data and resets the error state allowing a client
       * to reuse of a single message object to send multiple, sequential,
       * messages using the same service/domain/request id.
       */
      virtual void clearData();

      /**
       * Retrieves a list of all registered services.
       *
       * @param lstServices - a vector of strings that will be populated with the service names
       *
       * @return boolean indicating success/failure
       *
       * @see queryServiceProviders
       * @see isServiceRegistered
       */
      static bool queryServices( STRING_LIST& lstServices );


      /**
       * Retrieves a list of all registered services and their providers.
       *
       * @param mapServiceProviders - a KeyValuePairs object that will be populated with
       * all registered services (the key) and their corresponding service providers.
       *
       * @return boolean indicating success/failure
       *
       * @see queryServices
       * @see isServiceRegistered
       * @see isProviderRegistered
       */
      static bool queryServiceProviders( KeyValuePairs& mapServiceProviders );


      /**
       * Determines if the specified service name is registered
       *
       * @param strServiceName - the name of the service to check
       *
       * @return boolean indicating whether the service is registered
       *
       * @see queryServices
       * @see queryServiceProviders
       * @see isProviderRegistered
       */
      static bool isServiceRegistered( const std::string& strServiceName );


      /**
       * Determines if the specified service provider name is registered
       *
       * @param strProviderName - the name of the service provider to check
       *
       * @return boolean indicating whether the provider is registered
       *
       * @see queryServices
       * @see queryServiceProviders
       * @see isServiceRegistered
       */
      static bool isProviderRegistered( const std::string& strProviderName );


      /**
       * Retrieves the provider name for the specified service name.  A call to
       * "isServiceRegistered" should be made with a "true" return code prior to
       * calling this method.
       *
       * @param strServiceName - the name of the service whose provider is requested
       *
       * @return string containing the service provider's name
       *
       * @see queryServices
       * @see queryServiceProviders
       * @see isServiceRegistered
       */
      static const std::string& getServiceProvider( const std::string& strServiceName );


      /**
       * Logs a message if the current logging level is greater than or equal to the
       * logging level associated with the message.
       *
       * @param logLevel - the logging level associated with the specified message
       * @param pszLogMessage - the logging message
       *
       * @see getLogLevel
       * @see setLogLevel
       */
      static void log( int logLevel, const char* pszLogMessage );


      /**
       * Retrieves the current logging level.  This logging level applies to all
       * logging messages.
       *
       * @return integer representing the current logging level
       *
       * @see setLogLevel
       */
      static int getLogLevel();


      /**
       * Sets the new logging level.  This logging level applies to all
       * logging messages and will be retained until the subsequent call of this method.
       *
       * @param nLogLevel - integer representing the new logging level
       *
       * @see getLogLevel
       */
      static void setLogLevel( int nLogLevel );


      /**
       * Turns on/off logging to the console.  This method should be avoided for any
       * GUI application.  This method only pertains to non-GUI server applications that
       * run in "console" mode.
       *
       * @param isLoggingToConsole - boolean indicating whether logging messages should appear on the console
       *
       * @see isLoggingToConsole
       */
      static void logToConsole( bool isLoggingToConsole );


      /**
       * Determines whether logging messages are being sent to the console.  This method
       * should be avoided for any GUI application.  This method only pertains to non-GUI
       * server applications that run in "console" mode.
       *
       * @return boolean indicating whether logging messages appear on the console
       *
       * @see logToConsole
       */
      static bool isLoggingToConsole();



   protected:
      /**
       * Initializes the message object on construction.
       */
      void initOnConstruction();


      /**
       * Sets a value (key/value pair) in the message header section.
       *
       * @param strKey - the header variable name
       * @param strValue - the header variable value
       */
      void putHeaderValue( const std::string& strKey, const std::string& strValue );


      /**
       * Constructs a new message object by reading its data from the communications
       * channel.  The caller is responsible for deleting the returned Message object.
       *
       * @param pCommChannel - pointer to the communications channel object to read from
       *
       * @return pointer to newly constructed Message object
       */
      static Message* reconstruct( ICommChannel* pCommChannel );


      /**
       * Rebuilds a message object by reading its data from the communications channel.
       * This method <b>may destroy any existing contents</b> of the message object.
       *
       * @param pCommChannel - pointer to the communications channel object to read from
       *
       * @return boolean indicating success/failure
       */
      bool reconstitute( ICommChannel* pCommChannel );


   private:
      friend class MessagingAgent;
      friend class MessageFactory;



      Message( KeyValuePairs* pHashHeader,
               KeyValuePairs* pHashData );

      Message( KeyValuePairs* pHashHeader,
               const std::string& strXMLDocument );

      bool construct( const std::string& strHeader,
                      const std::string& strBody );

      std::string m_strXMLDocument;
      KeyValuePairs* m_pHashUserData;
      KeyValuePairs* m_pHashHeader;

      static MessagingAgent* s_pMsgAgent;
      static std::string s_strSenderIdentity;
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


