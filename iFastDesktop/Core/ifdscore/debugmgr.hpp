#pragma once

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DICORE */    

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif

#ifndef MUTEXSEMAPHORE_HPP
   #include <mutexsemaphore.hpp>
#endif

#ifndef SINGLETONREGISTER_HPP
   #include <singletonregister.hpp>
#endif

#ifndef INCLUDED_FSTREAM
#define INCLUDED_FSTREAM
#include <fstream>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class IPCChannel;

#ifndef INCLUDED_DSTRING
#define INCLUDED_DSTRING
#include <dstring.hpp>
#endif

/**
 * Singleton (per thread) that controls tracing.
 *
 * The class is work class behind TracerClient.
 *
 * It works off configuration data stored in Configuration
 *
 * <pre>
 *
 * Name          Value            Description
 * InitialValue  on/off           Initial global trace flag
 * OutputDevice  file/socket      Target of trace statements
 * FilePath      directory path   Directory where trace file stored
 * IPAddress     xxx.xxx.xxx      Address of machine running TraceMonitor
 * PortNumber    Number           Port (TraceMonitor hard coded to 1552)
 *
 * </pre>
 */
class DICORE_LINKAGE DebugMgr
{
public:

   /**
    * Valid trace statement types
    *
    */
   enum MESSAGE_TYPE
   {
      CONSTRUCTOR,
      DESTRUCTOR,
      METHOD,
      MESSAGE
   };

   /**
    * Creates or returns an instance of this class
    *
    * @return A pointer to an instance of DebugMgr
    */
   static DebugMgr * getInstance( void );

   /**
    * Deletes the current instance of the class
    *
    *
    */
   static void kill( void );

   virtual ~DebugMgr();

   /**
    * Find out if tracing is on
    *
    * @return If the tracing is on or off
    */
   bool isTracing() const { return(_fIsTracing);}

   /**
    * Turn tracing on and off
    *
    * @param fTracing Whether or not to trace
    *
    * @return If the tracing is on or off
    */
   bool setTracing( bool fTracing );

   /**
    * Writes trace statement to socket/file.  The input parameters are
    * combined to create the string written to the output device.
    *
    * @param msgType Enum for the type of message (METHOD, ...)
    * @param sClassName Class name where the statement is being generated from
    * @param lProcessId Process id of trace statement
    * @param lThreadId Thread id of trace statement
    * @param psMethod Method name or message depending on message type
    */
   void log ( DebugMgr::MESSAGE_TYPE msgType, const DString &sClassName,
              long lProcessId, long lThreadId,
              const DString &psMethod = I_("") );

   /**
    * Function attempts to connect with socket or file
    * (depending on configuration)
    *
    * @return Success of opening socket/file
    */
   bool connectTrace();


private:
   DebugMgr();
   DebugMgr( const DebugMgr& copy );
   DebugMgr& operator=( const DebugMgr& copy );

   /**
    * Write data to the socket
    *
    * @param pszMessage String to send to the socket
    * @return If successful
    */
   bool write( const DString &pszMessage );

   inline void formatMessageHeader( MESSAGE_TYPE msgType, long lProcessId,
                                    long lThreadId, DString &strMsgHeader );

   void initTrace();
   void termTrace();
   static void deregister( void *pObj );

private:
   enum LogType
   {
      LOG_NONE, LOG_SOCKET, LOG_FILE /* , SNMP */
   };

   bool _fIsTracing;
   IPCChannel *_pIPC;
   std::ofstream *_logFile;
   LogType _logType;
   SingletonRegister m_register;
   MutexSemaphore m_mutex;

   static DebugMgr *s_pMgr;

};

