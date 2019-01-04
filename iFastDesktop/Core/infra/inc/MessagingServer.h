#ifndef MESSAGINGSERVER_H
#define MESSAGINGSERVER_H

#include "Messaging.h"

#include "IMessagingServerHandler.h"
#include "Runnable.h"
#include "Mutex.h"
#include "Thread.h"

#include <map>

namespace MessagingFramework
{

class IMessage;
class ServerSocket;
class ICommChannel;
class RequestProcessor;
class MessagingAgent;
class MessagingService;
class Socket;
class MessageFactory;


/**
 * The MessagingServer class is used to establish a server/listener in
 * the messaging framework.  The use of the word "server" here does not
 * necessarily mean a true "server" in the normal sense -- it just means
 * an entity that will "listen" for messages from other applications and
 * process each message request as it arrives.
 *
 * <h2>Sample Usage</h2>
 * <pre>
 * MessagingServer msgServer( "TA2000 Desktop 3.7" );
 * if( msgServer.init( new ServerHandler ) )
 * {
 *    // set up a handler for handling 'financials' requests
 *    msgServer.setDomainHandler( "financials", new FinancialsMsgHandler );
 *
 *    // start the messaging server on a background thread
 *    msgServer.startOnThread();
 * }
 * </pre>
 */
class DIMESSAGE_LINKAGE MessagingServer : public Runnable,
                                          public IThreadDoneObserver
{
   public:
      /**
       * Constructor
       *
       * @param strProvider - the "service provider" name of this
       * messaging server
       */
      MessagingServer( const std::string& strProvider );


      /**
       * Destructor
       */
      ~MessagingServer();


      /**
       * Initializes the MessagingServer object. <b>This method
       * MUST be called successfully before the MessagingServer
       * can be started.<b>
       *
       * @param pHandler - pointer to a IMessagingServerHandler interface
       * to use as a "global" handler (in the absence of a domain-specific
       * or request-specific handler).
       *
       * @return boolean indicating success/failure of the MessagingServer
       * object's initialization
       *
       * @see IMessagingServerHandler
       */
      bool init( IMessagingServerHandler* pHandler );


      /**
       * Retrieves the port number used by this MessagingServer
       *
       * @return the port number
       */
      int getPort() const;


      /**
       * Establishes a global/general (i.e., for all domains) handler. <b>The
       * use of domains (setDomainHandler) is recommended over this approach.
       *
       * @param pHandler - pointer to the global/general handler
       *
       * @return boolean indicating success/failure
       *
       * @see IMessagingServerHandler
       */
      bool setGeneralHandler( IMessagingServerHandler* pHandler );


      /**
       * Registers a domain-specific handler
       *
       * @param pszDomain - the domain name this handler will service
       * @param pHandler - pointer to the handler object
       *
       * @return success/failure
       *
       * @see IMessagingServerHandler
       */
      bool setDomainHandler( const char* pszDomain,
                             IMessagingServerHandler* pHandler );

      /**
       * Registers a request-specific handler
       *
       * @param pszDomain - the domain name (used in conjunction with the
       * request name)
       * @param pszRequest - the request name (used in conjunction with
       * the domain name)
       * @param pHandler - pointer to the handler object
       *
       * @return success/failure
       *
       * @see IMessagingServerHandler
       */
      bool setDomainRequestHandler( const char* pszDomain,
                                    const char* pszRequest,
                                    IMessagingServerHandler* pHandler );

      /**
       * Retrieves the registered object (conforming to the IMessagingServerHandler
       * interface) for this message.  The method first searches for a
       * request-specific handler, then a domain-specific handler, and then
       * finally for a "general" (global) handler.  The first handler found
       * is returned.
       *
       * @param message - the Message object whose handler is needed
       *
       * @return pointer to IMessagingServerHandler interface
       *
       * @see IMessage
       * @see IMessagingServerHandler
       */
      IMessagingServerHandler* getHandlerForMessage( const IMessage& message );


      /**
       * Starts the MessagingServer on a separate (new) thread.
       *
       * @return boolean indicating success/failure of starting
       * the new thread.
       */
      bool startOnThread();


      /**
       * Starts the MessagingServer in the current thread.  Once this
       * method is called, the server starts running and continues to
       * run until explicitly stopped (due to program termination, or
       * by invoking the "shutdown" method).
       */
      void run();


      /**
       * Terminates the MessagingServer from its "run" method. Once the
       * MessagingServer is terminated, no more messages will be processed
       * until the server is started again (via "run" or "startOnThread").
       *
       * @return success/failure of server termination
       */
      bool shutdown();


      /**
       * Notification to let the messaging server know that one
       * of its RequestProcessor objects running in a separate thread has
       * terminated (it's done).
       *
       * @param pThread - pointer to the Thread that's terminating
       *
       * @see Thread
       */
      virtual void notifyOnThreadDone( Thread* pThread );


      /**
       * Determines whether each request is handled by a separate thread.
       *
       * @return boolean indicating whether each request is handled by a
       * separate thread
       */
      bool isEachRequestThreaded() const;


      /**
       * Lets the messaging server know that an individual request has just
       * completed.
       */
      void requestCompleted();


      /**
       * Accepts a message with the specified log level and text
       * for logging. If logged (based on the logging "level" in
       * force at runtime), the message will indicate which MessagingServer
       * the message is associated.
       *
       * @param logLevel - the logging level associated with this message
       * @param pszLogMsg - the logging message text
       */
      void log( int logLevel, const char* pszLogMsg );


      /**
       * Sends a normal (non-error) reply to the client.
       *
       * @param message - the original request message
       * @param strReturnData - the return data
       * @param pCommChannel - the connection
       *
       * @return boolean indicating success/failure
       *
       * @see IMessage
       * @see ICommChannel
       */
      bool sendReply( const IMessage& message,
                      const std::string& strReturnData,
                      ICommChannel* pCommChannel );


      /**
       * Sends an error reply to the client.
       *
       * @param message - the original request message
       * @param pCommChannel - the connection
       * @param pszErrorText - error description
       *
       * @see IMessage
       * @see ICommChannel
       */
      void sendErrorReply( const IMessage& message,
                           ICommChannel* pCommChannel,
                           const char* pszErrorText );


      /**
       * Sends an error reply to the client indicating that there
       * is no handler available to process the request.
       *
       * @param message - the original request message
       * @param pCommChannel - the connection
       *
       * @see IMessage
       * @see ICommChannel
       */
      void sendNoHandlerErrorReply( const IMessage& message,
                                    ICommChannel* pCommChannel );


      /**
       * Sends an error reply to the client indicating that the
       * message content format is unknown or unsupported.
       *
       * @param message - the original request message
       * @param pCommChannel - the connection
       *
       * @see IMessage
       * @see ICommChannel
       */
      void sendUnknownFormatErrorReply( const IMessage& message,
                                        ICommChannel* pCommChannel );


      /**
       * Determines if the specified configuration setting is present
       *
       * @param strKey - the string name of the configuration setting
       *
       * @return boolean indicating whether the configuration setting is available
       */
      bool hasConfigSetting( const std::string& strKey ) const;


      /**
       * Determines if the specified private configuration setting is present
       *
       * @param strKey - the string name of the private configuration setting
       *
       * @return boolean indicating whether the private configuration setting is available
       */
      bool hasPrivateConfigSetting( const std::string& strKey ) const;


      /**
       * Retrieves the specified configuration setting.  The "hasConfigSetting"
       * should always be called prior to calling this method.
       *
       * @param strKey - the string name of the configuration setting
       *
       * @return string containing configuration setting
       *
       * @see hasConfigSetting
       */
      const std::string& getConfigSetting( const std::string& strKey ) const;


      /**
       * Retrieves the specified private configuration setting.  The "hasPrivateConfigSetting"
       * should always be called prior to calling this method.
       *
       * @param strKey - the string name of the private configuration setting
       *
       * @return string containing private configuration setting
       *
       * @see hasPrivateConfigSetting
       */
      const std::string& getPrivateConfigSetting( const std::string& strKey ) const;



   protected:
      /**
       * Starts the processing of a new request on a separate (new) thread. The
       * RequestProcessor argument implements the "Runnable" interface, which
       * allows it to be easily used on a separate thread.
       *
       * @param pProcessor - pointer to the RequestProcessor that will be used
       * to process the request on the new thread.
       *
       * @see RequestProcessor
       */
      void startRequestThread( RequestProcessor* pProcessor );


      /**
       * Indicates that a request being processed on a new thread has completed.
       */
      void endRequestThread();


      /**
       * Increments the number of worker threads that are currently alive.
       */
      void incrementThreadCount();


      /**
       * Decrements the number of worker threads that are currently alive.
       */
      void decrementThreadCount();


      /**
       * Starts the messaging server.
       *
       * @return boolean indicating success/failure
       */
      bool start_server();


      /**
       * Completes the request by shutting down the communications connection.
       *
       * @param pCommChannel - the connection to terminate
       *
       * @see ICommChannel
       */
      void completeRequest( ICommChannel* pCommChannel );


      /**
       * Retrieves the appropriate key (internal identifier) for a particular
       * domain/request combination.
       *
       * @param pszDomain - the domain for the message request
       * @param pszRequest - the request identifier for the message request
       *
       * @return string indicating the internal key for the domain/request combination
       */
      std::string getDomainRequestKey( const char* pszDomain,
                                       const char* pszRequest );


      /**
       * Handler to register (dynamically) a new service.  The Message
       * argument is supposed to contain all relevant data necessary
       * to define a new service.
       *
       * @param pMessage - the message
       * @param pCommChannel - the connection
       *
       * @see IMessage
       * @see ICommChannel
       */
      void registerService( IMessage* pMessage, ICommChannel* pCommChannel );


      /**
       * Handler to deregister (dynamically) a service.
       *
       * @param pMessage - the message
       * @param pCommChannel - the connection
       *
       * @see IMessage
       * @see ICommChannel
       */
      void deregisterService( IMessage* pMessage, ICommChannel* pCommChannel );


      /**
       * Handler for a ping
       *
       * @param pMessage - the message
       * @param pCommChannel - the connection
       *
       * @see IMessage
       * @see ICommChannel
       */
      void ping( IMessage* pMessage, ICommChannel* pCommChannel );


      /**
       * Handler to echo the request message
       *
       * @param pMessage - the message
       * @param pCommChannel - the connection
       *
       * @see IMessage
       * @see ICommChannel
       */
      void echoRequest( IMessage* pMessage, ICommChannel* pCommChannel );


      /**
       * Handler to shutdown the messaging server.  This message has
       * no effect if the configuration parameter "shutdown_prohibited"
       * is turned on.
       *
       * @param pMessage - the message
       * @param pCommChannel - the connection
       *
       * @see IMessage
       * @see ICommChannel
       */
      void shutdown( IMessage* pMessage, ICommChannel* pCommChannel );


      /**
       * Sends a response back to the client.
       *
       * @param pCommChannel - the connection
       * @param strHeader - the response message header
       * @param strReturnData - the response message body (application) data
       *
       * @return boolean indicating success/failure
       *
       * @see ICommChannel
       */
      bool sendToClient( ICommChannel* pCommChannel,
                         const std::string& strHeader,
                         const std::string& strReturnData );


      /**
       * Initializes the new communications channel (Socket) after being established.
       *
       * @param pSocket - pointer to the newly established Socket
       *
       * @return boolean indicating success/failure of the initialization
       *
       * @see Socket
       */
      bool initChannel( Socket* pSocket );


      /**
       * Returns a newly established and fully initialized communications channel.
       * The caller of this method is responsible for deleting the ICommChannel
       * object at the appropriate time.
       *
       * @return pointer to newly allocated ICommChannel object
       *
       * @see ICommChannel
       */
      ICommChannel* getConnection();



   private:
      typedef std::map< std::string, IMessagingServerHandler* > MAP_DOMAIN_HANDLERS;
      typedef std::map< std::string, IMessagingServerHandler* > MAP_REQUEST_HANDLERS;

      ServerSocket* m_pServerSocket;
      Thread* m_pSocketThread;
      IMessagingServerHandler*  m_pHandler;
      std::string m_strProvider;
      std::string m_strLogProvider;
      bool m_isTimeToQuit;
      bool m_isEachRequestThreaded;
      bool m_isShutdownProhibited;
      int m_nCurrentThreads;
      int m_nPort;
      std::string m_strPort;
      MAP_DOMAIN_HANDLERS m_mapDomainHandlers;
      MAP_REQUEST_HANDLERS m_mapRequestHandlers;
      Mutex m_mutexThreadCount;
      Mutex m_mutexTimeToQuit;
      MessagingAgent* m_pAgent;
      MessagingService* m_pService;
      MessageFactory* m_pMessageFactory;
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



