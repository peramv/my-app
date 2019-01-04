#ifndef DEBUGMGR_HPP
#define DEBUGMGR_HPP

#  pragma message( "including "__FILE__ )

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
   #include "mutexsemaphore.hpp"
#endif

#ifndef SINGLETONREGISTER_HPP
   #include "singletonregister.hpp"
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
   #include "dstring.hpp"
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
   bool isTracing() const { return _fIsTracing; }

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
   enum LogType { LOG_NONE, LOG_SOCKET, LOG_FILE /* , SNMP */ };

   bool _fIsTracing;
   IPCChannel *_pIPC;
   std::ofstream *_logFile;
   LogType _logType;
   SingletonRegister m_register;
   MutexSemaphore m_mutex;

   static DebugMgr *s_pMgr;

};

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
// $Log:   Y:/VCS/iFastAWD/inc/debugmgr.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:58   kovacsro
//Initial revision.
// 
//    Rev 1.14   23 Oct 2000 17:07:54   dt14177
// cleanup
// 
//    Rev 1.13   Apr 13 2000 06:10:58   DMUM
// Removed Larry - Code
//
//    Rev 1.12   13 Jan 2000 14:12:02   dt20842
// Updated JavaDoc comments
//
//    Rev 1.11   Jan 04 2000 13:17:02   DT20842
// Added more JavaDoc comments
//
//    Rev 1.10   Dec 29 1999 10:42:44   DT20842
// Added package comment line
//
//    Rev 1.9   Dec 27 1999 11:56:12   DT20842
// Added JavaDocs style comments
//
//    Rev 1.8   Apr 22 1999 08:45:38   DT20842
//
//
//    Rev 1.7   Apr 16 1999 14:19:16   DT20842
// Changed from system header from quote
// include to bracket include
//
//    Rev 1.6   Apr 16 1999 13:12:58   DT20842
// Added new tracing
//
//    Rev 1.5   Feb 19 1999 08:54:06   DT20842
// Changed interface from DStringA -> DString
//
//    Rev 1.4   18 Feb 1999 10:39:02   DT14177
// UNICODE
//
//    Rev 1.3   Jan 28 1999 14:06:06   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Dec 09 1998 13:40:42   DMUM
// Check in for DICORE
//
//    Rev 1.1   Aug 13 1998 11:58:26   DMUM
// Implemented IMPORT / EXPORT and #inlcude standards
//
//    Rev 1.0   29 Jul 1998 20:37:04   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.2   Jun 16 1998 16:13:32   dt27994
// Removed old tracing code and modified existing.
//
//

