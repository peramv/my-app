// XVisSrv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stack_support.hpp"


#include "BPConsoleConnectionMonitor.hpp"
#include "BPConsoleDataBrokerMonitor.hpp"
#include "BPConsolePortalMonitor.hpp"
#include "ConsoleMenu.hpp"
#include "ConfigProvider.hpp"

#include "SonicMQPortal.hpp"

#include <ConfigManager.hpp>
#include <SingletonRegister.hpp>

#include <bfutil\Console.hpp>
#include <bfutil\consolecanvas.hpp>
#include <bfutil\txnstats.hpp>
#include <bfutil\bfexception.hpp>
#include <bfutil\BFIPBlast.hpp>
#include <bfutil\verify.hpp>
#include <bfutil\version_core.hpp>
#include <bfutil\programoptions.hpp>

#include <bf/log/log.hpp>
#include <bf/log/logtargetconsole.hpp>
#include <bf/log/logtargetdisk.hpp>

#include <bfconmgr\BFConnectionManager.hpp>

#include <ifastdbrkr\DSTCHost.hpp>
#include <ifastdbrkr\DSTCRequestor.hpp>
#include <ifastdbrkr\RTSSocketConnectionFactory.hpp>
#include <ifastdbrkr\SonicConnectionFactory.hpp>
#include <bfcbo\bfcbo.hpp>
#include <bfproc\CommandDispatcher.hpp>
#include <bfproc\GenericInterfaceContainer.hpp>
#include <bfproc\ProcessManager.hpp>
#include <srvbase\Server.hpp>
#include <srvbase\SocketPortal.hpp>

#include <ifastcbo\version_app.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\persistentusersession.hpp>
#include <ifastxparser\DSTCElementHandlerFactory.hpp>

#include <xercesc\util\PlatformUtils.hpp>
#include <xercesc\dom\DOMException.hpp>
#include <sstream>
#include <iomanip>
#include <vector>


bool init( const bps::ConfigProvider& cp, bool monitorSonicMQ );
void terminatesrv();
extern "C" { WINBASEAPI BOOL WINAPI IsDebuggerPresent( VOID );}

class OurProgramOptions : public bf::opts::ProgramOptions
{
public:
   OurProgramOptions( int argc, char** argv ) : ProgramOptions( argc, argv ) {}
protected:
   virtual bool validate(const bf::opts::P_Option *pOption, long lValue, std::string& strMessage ) const {
      if( 'p' == pOption->getShortName() && 0 > lValue ) {
         strMessage = "Must be a positive number";
         return( false );
      } else if( 'c' == pOption->getShortName() && 0 > lValue ) {
         strMessage = "Category can't be 0";
         return( false );
      }
      return( true );
   }
   virtual bool validate(const bf::opts::P_Option *pOption, double dValue, std::string& strMessage ) const {
      return( true );
   }
   virtual bool validate(const bf::opts::P_Option *pOption, const std:: string &strValue, std::string& strMessage ) const {
      if( 'k' == pOption->getShortName() ) {
         switch( strValue[0] ) {
            case 'i':
            case 'w':
            case 's':
            case 'c':
            case 'n':
            case 'q':
               break;
            default:
               return( false );

         }
      }
      return( true );
   }
};

namespace bps {

   class ParseOptionLogLevel {
   public:
      typedef std::string OType;
      enum bf::log::LogStream::Level operator()( const bf::opts::ProgramOptions::OptionValue<OType> *optValue ) {
         std::string strValue =  optValue->get();
         bf::log::LogStream::Level eLevel = bf::log::LogStream::e_information;
         switch( strValue[0] ) {
            case 'i': eLevel = bf::log::LogStream::e_information; break;
            case 'w': eLevel = bf::log::LogStream::e_warning; break;
            case 's': eLevel = bf::log::LogStream::e_severe; break;
            case 'c': eLevel = bf::log::LogStream::e_critical; break;
            case 'n': eLevel = bf::log::LogStream::e_notify; break;
            case 'q': eLevel = bf::log::LogStream::e_silent; break;
         }
         return eLevel;
      }
   };

   class ParseConfigLogLevel {
   public:
      enum bf::log::LogStream::Level operator()( const std::wstring &strVal ) {
         // read the following lines as: 
         //            upperStrVal = strVal.toupper();
         // std is beautiful
         std::wstring upperStrVal(strVal);
         std::use_facet< std::ctype<wchar_t> > ( std::locale() ).toupper( &upperStrVal[0], &upperStrVal[upperStrVal.size()-1] );

         if ( upperStrVal == L"INFORMATION" ) {
            return bf::log::LogStream::e_information;
         }
         if ( upperStrVal == L"WARNING" ) {
            return bf::log::LogStream::e_warning;
         }
         if ( upperStrVal == L"SEVERE" ) {
            return bf::log::LogStream::e_severe;
         }
         if ( upperStrVal == L"CRITICAL" ) {
            return bf::log::LogStream::e_critical;
         }
         if ( upperStrVal == L"NOTIFY" ) {
            return bf::log::LogStream::e_notify;
         }
         if ( upperStrVal == L"SILENT" ) {
            return bf::log::LogStream::e_silent;
         }

         return bf::log::LogStream::e_information;
      }
   };

   typedef ParseOptionFirst<'@'> ParseOptionUserId;
   typedef ParseOptionSecond<'@'> ParseOptionPassword;

   // specific property types
   typedef bps::ConfigProperty< DString, ParseConfigDString, ParseOptionUserId > UserIdProperty;
   typedef bps::ConfigProperty< DString, ParseConfigDString, ParseOptionPassword > PasswordProperty;
   typedef bps::ConfigProperty< enum bf::log::LogStream::Level, ParseConfigLogLevel, ParseOptionLogLevel > LogLevelProperty;

} // namespace bps


namespace {

   // application properties
   bps::DStringProperty g_propAppName ( 'N', L"AppName",      I_("iFastBPS") );
   bps::DStringProperty g_propAppDesc ( 'D', L"AppDesc",      I_("") );
   bps::DStringProperty g_propAppReg  ( 'm', L"AppReg",       I_("MFDSTC") );
   bps::BooleanProperty g_propPlain   ( 'q', L"PlainConsole", false );

   // logging properties
   bps::DStringProperty    g_propLogsDir      (      L"Logging/LogsDir",      I_("") );
   bps::BooleanProperty    g_propLogOn        ( 'l', L"Logging/LoggingOn",    true );
   bps::LogLevelProperty   g_propLogLevel     ( 'k', L"Logging/Level",        bf::log::LogStream::e_information);
   bps::HexNumericProperty g_propLogCat       ( 'c', L"Logging/Catagory",     bf::log::all );
   bps::BooleanProperty    g_propTransTraceOn ( 'x', L"Logging/TransTraceOn", false );
   bps::BooleanProperty    g_propTransStatsOn ( 't', L"Logging/TransStatsOn", false );

   // host properties
   bps::DStringProperty    g_propHostName           (      L"Host/HostName",        I_("IFAST") );
   bps::DStringProperty    g_propHostAddress        ( 'a', L"Host/HostAddress",     I_("") );
   bps::DecNumericProperty g_propHostPort           ( 's', L"Host/HostPort",        0 );
   bps::UserIdProperty     g_propHostAdminUser      ( 'u', L"Host/AdminUser",       I_("") );
   bps::PasswordProperty   g_propHostAdminPassword  ( 'u', L"Host/AdminPassword",   I_("") );
   bps::DecNumericProperty g_propHostTimeout        ( 'T', L"Host/Timeout",         0  );
   bps::DecNumericProperty g_propHostMinConnections (      L"Host/MinConnections",  10 );
   bps::DecNumericProperty g_propHostMaxConnections (      L"Host/MaxConnections",  50 );

   // SonicMQ Host Properties
   bps::BooleanProperty    g_propHostUseSMQ         (      L"Host/UseSMQ",          false );
   bps::DStringProperty    g_propHostSMQBroker      (      L"Host/SMQBroker",       I_("") );
   bps::DStringProperty    g_propHostSMQSingleQueue (      L"Host/SMQSingleQueue",  I_("") );
   bps::DStringProperty    g_propHostSMQMultiQueue  (      L"Host/SMQMultiQueue",   I_("") );
   bps::DStringProperty    g_propHostSMQUser        (      L"Host/SMQUser",         I_("") );
   bps::DStringProperty    g_propHostSMQPassword    (      L"Host/SMQPassword",     I_("") );
   bps::DStringProperty    g_propHostSMQWaitTimeout (      L"Host/SMQWaitTimeout",  I_("120") );
   bps::DStringProperty    g_propHostSMQCswAcl      (      L"Host/SMQCswAcl",       I_("") );

   // socket portal properties
   bps::DStringProperty    g_propSockPortalName (      L"SocketPortal/PortalName",     I_("Socket Portal") );
   bps::DecNumericProperty g_propSockThreads    ( 'n', L"SocketPortal/ThreadPoolSize", 10 );
   bps::DecNumericProperty g_propSockMaxJobs    ( 'j', L"SocketPortal/JobQueueSize",   50 );
   bps::DecNumericProperty g_propSockPort       ( 'p', L"SocketPortal/ListenPort",     5000);

   // sonic MQ portal properties
   bps::DStringProperty    g_propSMQPortalName          (      L"SonicMQPortal/PortalName",            I_("SonicMQ Portal") );
   bps::DecNumericProperty g_propSMQThreads             ( 'n', L"SonicMQPortal/ThreadPoolSize",        10 );
   bps::DStringProperty    g_propSMQBroker              ( 'B', L"SonicMQPortal/SMQBroker",             I_("") );
   bps::UserIdProperty     g_propSMQUser                ( 'U', L"SonicMQPortal/SMQUser",               I_("") );
   bps::PasswordProperty   g_propSMQPassword            ( 'U', L"SonicMQPortal/SMQPassword",           I_("") );
   bps::DStringProperty    g_propSMQInQueue             ( 'I', L"SonicMQPortal/InboundQueue",          I_("") );
   bps::DStringProperty    g_propSMQOutQueue            ( 'O', L"SonicMQPortal/OutboundQueue",         I_("") );
   bps::DStringProperty    g_propSMQErrQueue            ( 'E', L"SonicMQPortal/ErrorQueue",            I_("") );
   bps::BooleanProperty    g_propSendCritErrRespToErrQ  (      L"SonicMQPortal/CriticalErrorHandling", true );

   // sonic MQ portal rouing properties
   bps::DStringProperty     g_propSMQRouteInActType     ( L"InActivityType",     I_("") );
   bps::DStringProperty     g_propSMQRouteOutActType    ( L"OutActivityType",    I_("") );
   bps::DStringProperty     g_propSMQRouteOutMsgType    ( L"OutMessageType",     I_("") );
   bps::DStringProperty     g_propSMQRouteReplyTo       ( L"ReplyToQueue",       I_("") );
   bps::DStringProperty     g_propSMQRouteLookupActType ( L"LookupActivityType", I_("") );
   bps::DStringProperty     g_propSMQRouteLookupMsgType ( L"LookupMessageType",  I_("") );
   bps::DStringProperty     g_propSMQRouteLookupReplyTo ( L"LookupReplyToQueue", I_("") );

   static DString s_logsDir;
   static DString s_appName;
   static DString s_appDesc;

   bool g_bVerifyConfig = false;

   /**
    * Verify that all expected components are present and are the expected
    * versions.  Report errors and throw exception on error
    */
   bool verifyConfiguration() {
      bool bRc = true;
      if( false == bfutil::getLibraryVerifier().verify( bfutil::LibraryVerifier::Category::core, bfutil::LibraryVersion( I_("iFAST_3.01.10") ) ) ) { bRc = false; }
      if( false == bfutil::getLibraryVerifier().verify( bfutil::LibraryVerifier::Category::app_shared, bfutil::LibraryVersion( I_("Rel_65.0.0") ) ) ) { bRc = false; }
      if( false == bfutil::getLibraryVerifier().verify( bfutil::LibraryVerifier::Category::app_client, bfutil::LibraryVersion( I_("Rel_65.0.0") ) ) ) { bRc = false; }
      return( bRc );
   }

   // monitor objects
   static ConsoleMenu                *s_pConsoleMenu = NULL;
   static ConsoleAppInfo             *s_pConsoleAppInfo = NULL;
   static BPConsoleDataBrokerMonitor *s_pDataBrokerMonitor = NULL;
   static BPConsolePortalMonitor     *s_pSocketPortalMonitor = NULL;
   static BPConsolePortalMonitor     *s_pSonicMQPortalMonitor = NULL;

   // process dispatch objects
   ProcessManager *g_businessProcessMgr = NULL;
}

#include "ifastlogfile.hpp"

#if 0
class IFastLogFile : public bf::log::LogTargetDisk
{
private:
   DString appName_;
   DString logsDir_;
public:
   IFastLogFile( const DString &appName, const DString &logsDir )
   : LogTargetDisk( NULL, false ), appName_(appName), logsDir_(logsDir)
   {
   }

protected:
   virtual DString getFileName( const I_CHAR* pszHint ) const
   {
      // file name is of the form
      // {registry appname}_[pid]_[year]-[month]-[day]-[hour]:[minute]:[second].log
      // file goes in current directory

      std::wstringstream wss;
      wss << std::setfill( I_('0') );
      if ( logsDir_.size() > 0 ) {
         wss << logsDir_;
         if ( logsDir_[logsDir_.size()-1] != I_('\\') ) {
            wss << I_('\\');
         }
      }
      wss << appName_;
      if( wss.str().empty() ) {
         wss << I_( "iFastBPS" );
      }
      SYSTEMTIME lt;
      GetLocalTime( &lt );
      wss << I_( "_" );
      wss << std::dec << std::setw( 4 ) << static_cast<unsigned long>(lt.wYear);
      wss << I_( "-" ) << std::setw( 2 ) << static_cast<unsigned long>(lt.wMonth);
      wss << I_( "-" ) << std::setw( 2 ) << static_cast<unsigned long>(lt.wDay);
      wss << I_( "-" ) << std::setw( 2 ) << static_cast<unsigned long>(lt.wHour);
      wss << I_( "." ) << std::setw( 2 ) << static_cast<unsigned long>(lt.wMinute);
      wss << I_( "." ) << std::setw( 2 ) << static_cast<unsigned long>(lt.wSecond);

      wss << I_( "_" ) << std::hex << std::setw( 4 ) << ::GetCurrentProcessId();

      wss << I_( ".log" );
      return( wss.str() );
   }

   virtual const I_CHAR* getOpenMode( const DString& dstrFile, bool bAppend, bool bUnicode ) const 
   {
      // always open in append mode with no unicde
      return( I_("a") );
   }
};

#endif

HANDLE hCtrlBreak = INVALID_HANDLE_VALUE;

// this is a Win32 Ctrl-Break handler function.
BOOL __stdcall ctrlBreakHandler( unsigned long ctrlType )
{
   BOOL bRc = FALSE;
   // ctrl break pressed ... signal the main thread to exit
   switch( ctrlType )
   {
      case CTRL_C_EVENT:
      case CTRL_BREAK_EVENT:
         {
            bf::log::LogStream ls( bf::log::all );
            ls << bf::log::endl << I_( "Ctrl-Break detected ... exiting" ) << bf::log::endlf;
         }
         terminatesrv();
         ::SetEvent( hCtrlBreak );
         bRc = TRUE;
         break;
      case CTRL_SHUTDOWN_EVENT:
         {
            bf::log::LogStream ls( bf::log::all );
            ls << bf::log::endl << I_( "Shutdown detected ... exiting" ) << bf::log::endlf;
         }
         bRc = FALSE;
         break;
      case CTRL_LOGOFF_EVENT:
         {
            bf::log::LogStream ls( bf::log::all );
            ls << bf::log::endl << I_( "Logoff detected ... exiting" ) << bf::log::endlf;
         }
         bRc = FALSE;
         break;
      case CTRL_CLOSE_EVENT:
         {
            bf::log::LogStream ls( bf::log::all );
            ls << bf::log::endl << I_( "User Close detected ... exiting" ) << bf::log::endlf;
         }
         terminatesrv();
         ::SetEvent( hCtrlBreak );
         bRc = TRUE;
         break;

   }
   return( bRc );
}

int main( int argc, char* argv[] )
{
   StackSupportInit();

   hCtrlBreak = ::CreateEvent( NULL, TRUE, FALSE, NULL );
   ::SetConsoleCtrlHandler( ctrlBreakHandler, TRUE );

   xercesc::XMLPlatformUtils::Initialize();
   bfutil::setServerContext( true );

   int i = 1;

   OurProgramOptions p( argc, argv );
   try {
      p.addOption( 0x00, "verify_config", "Verify configuration at startup", bf::opts::boolean );

      // configuration file
      p.addOption( 'C', "configfile", "Path of a configuration file.", bf::opts::path );

      // application parameters
      p.addOption( g_propAppName.cmdLineOpt, "appname", "Application Name",            bf::opts::string | bf::opts::required );
      p.addOption( g_propAppDesc.cmdLineOpt, "appdesc", "Application Description",     bf::opts::string | bf::opts::required );
      p.addOption( g_propAppReg.cmdLineOpt,  "appreg",  "Application registratry key", bf::opts::string | bf::opts::required );
      p.addOption( g_propPlain.cmdLineOpt,   "plain",   "Don't use fancy console",     bf::opts::boolean );

      // logging and trace configuration
      p.addOption( g_propLogOn.cmdLineOpt,        "log",         "Activate logging",                        bf::opts::boolean );
      p.addOption( g_propLogLevel.cmdLineOpt,     "loglevel",    "Minimum level of logging to allow",       bf::opts::string | bf::opts::required );
      p.addOption( g_propLogCat.cmdLineOpt,       "logcategory", "Hex mask of logging categories to allow", bf::opts::numeric | bf::opts::hex | bf::opts::required );
      p.addOption( g_propTransTraceOn.cmdLineOpt, "txntrace",    "Activate Transaction Trace Logging",      bf::opts::boolean );
      p.addOption( g_propTransStatsOn.cmdLineOpt, "txnstats",    "Activate Transaction Statistic Tracking", bf::opts::boolean );

      // host configuration
      p.addOption( g_propHostAddress.cmdLineOpt,   "host",           "RTS Host",                                       bf::opts::string );
      p.addOption( g_propHostPort.cmdLineOpt,      "slot",           "RTS Slot port number",                           bf::opts::numeric );
      p.addOption( g_propHostAdminUser.cmdLineOpt, "admin",          "Admin UserId/Password, in form userid@password", bf::opts::string );
      p.addOption( g_propHostTimeout.cmdLineOpt,   "socket_timeout", "Server Socket Timeout, in seconds",              bf::opts::numeric );

      // SonicMQ host configuration
      p.addOption( g_propHostSMQBroker.cmdLineOpt,           "host-broker",  "SonicMQ Host Broker",                            bf::opts::string );
      p.addOption( g_propHostSMQSingleQueue.cmdLineOpt,      "host-singleq", "SonicMQ Host SingleReq Queue", bf::opts::string );
      p.addOption( g_propHostSMQMultiQueue.cmdLineOpt,       "host-multiq",  "SonicMQ Host MultiReq Queue", bf::opts::string );
      p.addOption( g_propHostSMQUser.cmdLineOpt,             "host-user",    "SonicMQ Host User", bf::opts::string );
      p.addOption( g_propHostSMQPassword.cmdLineOpt,         "host-password","SonicMQ Host Password", bf::opts::string );
      p.addOption( g_propHostSMQWaitTimeout.cmdLineOpt,      "host-timeout", "SonicMQ Host Wait Timeout", bf::opts::string );
      p.addOption( g_propHostSMQCswAcl.cmdLineOpt,           "host-acl",     "SonicMQ Host CSWACL value", bf::opts::string );
      p.addOption( g_propHostUseSMQ.cmdLineOpt,              "host-smq",     "Use SonicMQ as BackEnd", bf::opts::string );

      // socket portal configuration
      p.addOption( g_propSockThreads.cmdLineOpt, "worker_threads", "Number of worker threads to start", bf::opts::numeric | bf::opts::required );
      p.addOption( g_propSockMaxJobs.cmdLineOpt, "jobs",           "Maximum number of pending jobs",    bf::opts::numeric | bf::opts::required );
      p.addOption( g_propSockPort.cmdLineOpt,    "port",           "Listening port number",             bf::opts::numeric | bf::opts::required );

      p.addOption( g_propSMQBroker.cmdLineOpt,   "mq-broker",    "SonicMQ broker",                                bf::opts::string );
      p.addOption( g_propSMQUser.cmdLineOpt,     "mq-user",      "SonicMQ user/pasword, in form userid@password", bf::opts::string );
      p.addOption( g_propSMQInQueue.cmdLineOpt,  "mq-in-queue",  "SonicMQ inbound queue",                         bf::opts::string );
      p.addOption( g_propSMQOutQueue.cmdLineOpt, "mq-out-queue", "SonicMQ outbound queue",                        bf::opts::string );
      p.addOption( g_propSMQErrQueue.cmdLineOpt, "mq-err-queue", "SonicMQ error queue",                           bf::opts::string );
      
//      p.addOption( 'R', "mq-out-queue", "SonicMQ network outbound queues(ReplyTo for MsgTrack) in form network:qname", 
//                                                                                            bf::opts::string | bf::opts::multiple );

      p.parse();
      if( p.getErrorCount() > 0 ) {
         const std::vector< std::string >& v = p.getErrorMessages();
         std::vector< std::string >::const_iterator it = v.begin();
         for( ; v.end() != it; ++it ) {
            std::cout << (*it) << std::endl;
         }
         return( 8 );
      }

      bps::ConfigProvider cp( p );

      s_logsDir = cp.getPropertyValue(g_propLogsDir);
      s_appName = cp.getPropertyValue(g_propAppName);
      s_appDesc = cp.getPropertyValue(g_propAppDesc);

      Console *pConsole = Console::getInstance( cp.getPropertyValue(g_propPlain) );

      // The following line of code causes BPStarter to fail. 
      // The "kill" function used the window title to "find" the application.
      // This line should be uncommented when BPStarter is put to rest...
      //pConsole->setTitle( DString(I_("BPServer - ")) + s_appName );

      pConsole->setMode( Console::Mode::MAIN );
      ConfigManager::setApplication( cp.getPropertyValue(g_propAppReg) );
      ConfigManager::setClientName( s_appName );

      TxnStats::autoEnable(  cp.getPropertyValue(g_propTransStatsOn) );
      bf::log::theLog.setReportingThreshold( cp.getPropertyValue(g_propLogLevel) );

      // attach logging targets 
      // release & debug both use a file target
      if( cp.getPropertyValue(g_propLogOn) )
      {
         bf::log::theLog.setReportingCategory( cp.getPropertyValue(g_propLogCat) );
         bf::log::theLog.addTarget( I_( "disk" ), new IFastLogFile(s_appName, s_logsDir, true) );
         bf::log::theLog.addTarget( I_( "console" ), bf::log::LogTargetConsole::create() );
#ifndef _DEBUG
         // release builds will not output to console
         bf::log::theLog.suspendTarget( I_( "console" ) );
#endif
      }

      bf::log::theLog << bf::log::endl;
      bf::log::theLog << I_( "App Name:     " ) << s_appName << I_( " - " ) << cp.getPropertyValue(g_propAppDesc) << bf::log::endl;
      bf::log::theLog << I_( "Reg Key:      " )  << cp.getPropertyValue(g_propAppReg) << bf::log::endl;
      bf::log::theLog << I_( "Listen port:  " ) << static_cast<unsigned long>(cp.getPropertyValue(g_propSockPort)) << bf::log::endl;
      bf::log::theLog << I_( "Core version: " ) << ifds::getCoreVersion() << I_( " bld" ) << ifds::getCoreBuildNumber() << I_( "@" ) << ifds::getCoreBuildComputer() << bf::log::endl;
      bf::log::theLog << I_( "App version:  " ) << ifds::getAppVersion() << I_( " bld" ) << ifds::getAppBuildNumber() << I_( "@" ) << ifds::getAppBuildComputer() << bf::log::endl;
      bf::log::theLog << I_( "----------------------------------------------------------------------------" ) << bf::log::endl;
      bf::log::theLog << bf::log::endlf;

      // don't allow BFCBO to use asynchronous thread calls
      BFCBO::allowThreads( false );
      int exitCode = 13;

      try
      {     
         Server* pServer = Server::getInstance();
         pServer->setTrace(cp.getPropertyValue(g_propTransTraceOn));

         pServer->putPortal( new SocketPortal( cp.getPropertyValue(g_propSockPortalName), cp.getPropertyValue(g_propSockPort), 
                                               cp.getPropertyValue(g_propSockThreads),    cp.getPropertyValue(g_propSockMaxJobs), 0) );

         bool sonicPortalInstalled = false;
         const DString sonicMQBroker = cp.getPropertyValue(g_propSMQBroker);
         if ( sonicMQBroker != I_("") ) {

            SonicMQPortal *smqp = new SonicMQPortal( cp.getPropertyValue(g_propSMQPortalName),
                                                     sonicMQBroker, 
                                                     cp.getPropertyValue(g_propSMQInQueue), 
                                                     cp.getPropertyValue(g_propSMQOutQueue), 
                                                     cp.getPropertyValue(g_propSMQErrQueue),
                                                     cp.getPropertyValue(g_propSMQUser), 
                                                     cp.getPropertyValue(g_propSMQPassword), 
                                                     cp.getPropertyValue(g_propSMQThreads),
                                                     cp.getPropertyValue(g_propSendCritErrRespToErrQ) ); 

            // add routings
            bps::ConfigIterator citer = cp.iterator( L"SonicMQPortal", L"SMQRouting" );
            while ( cp.next(citer) ) {
               smqp->addRouting( SonicMQRouting( cp.getPropertyValue( citer, g_propSMQRouteInActType     ),
                                                 cp.getPropertyValue( citer, g_propSMQRouteOutActType    ),
                                                 cp.getPropertyValue( citer, g_propSMQRouteOutMsgType    ),
                                                 cp.getPropertyValue( citer, g_propSMQRouteReplyTo       ),
                                                 cp.getPropertyValue( citer, g_propSMQRouteLookupActType ),
                                                 cp.getPropertyValue( citer, g_propSMQRouteLookupMsgType ),
                                                 cp.getPropertyValue( citer, g_propSMQRouteLookupReplyTo ) ));
            }

            pServer->putPortal( smqp );
            sonicPortalInstalled = true;

         }

         if( true == init( cp, sonicPortalInstalled ) ) 
         {
            exitCode = pServer->run();
         }
         bf::log::LogStream ls( bf::log::service );
         ls << bf::log::information << I_( "BPServer terminating..." ) << bf::log::endl;
//moved into try section - Incident# 393028
         terminatesrv();
         Server::killInstance();       
      }
      catch( ConditionException & )
      {
         Console::getInstance()->setMode(Console::MESSAGE);
         bf::log::LogStream ls( bf::log::service );
         ls << I_( "BPServer terminating with (ce) errors..." ) << bf::log::endl;
      }
      catch( BFException &bfe )
      {
         Console::getInstance()->setMode(Console::MESSAGE);
         bf::log::LogStream ls( bf::log::service );
         ls << I_( "BPServer terminating with errors..." ) << bf::log::endl;
         ls << DString( DStringA( bfe.getErrorMessage() ) ) << bf::log::endl;
         return( exitCode );
      }
      catch( ... )
      {
         Console::getInstance()->setMode(Console::MESSAGE);
         bf::log::LogStream ls( bf::log::service );
         ls << I_( "BPServer terminating with unknown errors..." ) << bf::log::endl;
      }
      return(exitCode);

   } catch( bf::opts::ProgramOptionsException& e ) {
      std::cout << std::endl << "Program Options Exception:" << std::endl;
      std::cout << "    " << e.getMessage() << std::endl;
      return( 16 );
   } catch( xercesc::DOMException& e ) {
      std::cout << std::endl << "Program Config File Exception:" << std::endl;
      std::cout << "    Error code:" << e.code << std::endl;
      return( 17 );
   } 

}

bool init( const bps::ConfigProvider& cp, bool monitorSonicMQ )
{
#ifdef _DEBUG
   verifyConfiguration();
#else
   if( false == verifyConfiguration() && g_bVerifyConfig ) {
      return( false );
   }
#endif

   //register dispatchers
   CommandDispatcher *rpDispatch = CommandDispatcher::getInstance();

   // register business process dispatcher
   g_businessProcessMgr = new ProcessManager();
   rpDispatch->registerDispatcher( g_businessProcessMgr, BUSINESS_PROCESS_TYPE );
   rpDispatch->registerDispatcher( g_businessProcessMgr, SERVER_PROCESS_TYPE );

   xp::ElementHandlerFactory::registerInstance( new DSTCElementHandlerFactory() );

   BFConnectionFactory *connectionFactory = NULL;
   if( cp.getPropertyValue( g_propHostUseSMQ ) ) {
      DString singleQueue = cp.getPropertyValue(g_propHostSMQSingleQueue);
      DString multiQueue = cp.getPropertyValue(g_propHostSMQMultiQueue);
      DString user = cp.getPropertyValue(g_propHostSMQUser);
      DString password = cp.getPropertyValue(g_propHostSMQPassword);
      DString timeout = cp.getPropertyValue(g_propHostSMQWaitTimeout);
      DString brokerURLs = cp.getPropertyValue(g_propHostSMQBroker);

      int iTimeout = timeout.convertToULong();
      if( !iTimeout ) { iTimeout = 120; }
      
      connectionFactory = new SonicConnectionFactory( brokerURLs,
                                                      singleQueue,
                                                      multiQueue,
                                                      I_(""),
                                                      user,
                                                      password,
                                                      500, // recycle interval.  should be configurable?
                                                      iTimeout,
                                                      cp.getPropertyValue(g_propHostSMQCswAcl));
   }
   else {
      connectionFactory = new RTSSocketConnectionFactory( cp.getPropertyValue(g_propHostAddress),
                                                          cp.getPropertyValue(g_propHostPort),
                                                          -1, 
                                                          cp.getPropertyValue(g_propHostTimeout) );
   }
   DString hostName = cp.getPropertyValue(g_propHostName);
   DSTCHost::setPrimaryHost( hostName );
   BFConnectionManager::getInstance()->createHostConnectionManager( hostName, 
                                                                    connectionFactory, 
                                                                    cp.getPropertyValue(g_propHostMaxConnections), 
                                                                    true, 
                                                                    cp.getPropertyValue(g_propHostMinConnections));

   // setup console/monitors
   if( false == Console::getInstance()->isQuiet() )
   {
      s_pConsoleAppInfo = new ConsoleAppInfo( s_appDesc );
      s_pConsoleMenu = new ConsoleMenu();
      s_pSocketPortalMonitor = new BPConsolePortalMonitor(cp.getPropertyValue(g_propSockPortalName));
      if ( monitorSonicMQ ) {
         s_pSonicMQPortalMonitor = new BPConsolePortalMonitor(cp.getPropertyValue(g_propSMQPortalName));
      }
      s_pDataBrokerMonitor = new BPConsoleDataBrokerMonitor();
      BFConnectionManager::getInstance()->setConnectionMonitor(new BPConsoleConnectionMonitor());
   }


   // create the persistent UserSession object and initialize it. This is a feature of the
   // Vision Server DLL.
   if ( NULL == PersistentUserSession::getInstance( cp.getPropertyValue(g_propHostAdminUser), 
                                                    cp.getPropertyValue(g_propHostAdminPassword) ) ) {
      bf::log::LogStream ls( bf::log::service );
      ls << I_( "Persistent User Session was not created.  Check UserId/Password." ) << bf::log::endl;
      return false;   
   }
   return true;
}

void terminatesrv()
{
   // remove console/monitors
   delete s_pConsoleAppInfo;
   s_pConsoleAppInfo = NULL;

   delete s_pConsoleMenu;
   s_pConsoleMenu = NULL;

   delete s_pDataBrokerMonitor;
   s_pDataBrokerMonitor = NULL;

   delete s_pSocketPortalMonitor;
   s_pSocketPortalMonitor  = NULL;

   delete s_pSonicMQPortalMonitor;
   s_pSonicMQPortalMonitor = NULL;

   BFConnectionManager::getInstance()->setConnectionMonitor(NULL);
   Console::killInstance();

   BFConnectionManager::killInstance();
   CommandDispatcher::killInstance();

   delete g_businessProcessMgr;
   g_businessProcessMgr = NULL;

   BFConnectionManager::killInstance();
   PersistentUserSession::killInstance();
   xp::ElementHandlerFactory::killInstance();

   BFIPBlast::killInstance();

   SingletonRegister::releaseSingletons();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbps/XVisSrv.cpp-arc  $
 // 
 //    Rev 1.87   Aug 10 2009 13:12:32   purdyech
 // Use new SonicConnectionFactory interface
 // 
 //    Rev 1.86   Jun 05 2009 08:18:32   purdyech
 // Fixed names of SonicSingle and SonicMulti queues in configuration.
 // SonicErrorMessages are now handled appropriately.
 // 
 //    Rev 1.85   May 25 2009 10:36:24   purdyech
 // Reference the local copy of ifastlogfile.hpp instead of the one in ifastgui
 // 
 //    Rev 1.84   15 May 2009 14:15:28   popescu
 // Fix compile issue?
 // 
 //    Rev 1.83   May 01 2009 09:16:46   purdyech
 // Support Sonic Backend
 // 
 //    Rev 1.82   Jul 07 2006 14:52:16   fengyong
 // Incident #659311 - Add flag check client name
 // 
 //    Rev 1.81   Sep 23 2005 14:03:02   purdyech
 // Incident 393028 - Write log message when Persistent User Session can not be created.
 // 
 //    Rev 1.80   Sep 18 2005 09:24:28   purdyech
 // PET910 - Updated version number to correct value.
 // 
 //    Rev 1.79   Sep 18 2005 09:23:42   purdyech
 // PET910 - Update version number to correct value.
 // 
 //    Rev 1.78   Sep 16 2005 11:42:46   popescu
 // Incident# 393028 - With this fix the logon errors are trapped and the persistent user session is not created. Hence, the BPServer exits gracefully.
 // 
 //    Rev 1.77   Apr 10 2005 16:07:04   smithdav
 // Add configuration property to allow "critical error handling" in the SonicMQ portal to be turned off( on by default ).
 // 
 //    Rev 1.76   Mar 15 2005 17:14:14   smithdav
 // Fixed Max/MinConnection configuration.
 // 
 //    Rev 1.75   Mar 08 2005 09:44:26   smithdav
 // Add configurable Log directory.
 // 
 //    Rev 1.74   Feb 18 2005 13:29:08   smithdav
 // Add support for routing transactions with critical errors to an "error queue"
 // 
 //    Rev 1.73   Feb 18 2005 11:33:42   smithdav
 // Add config and call for transaction tracing.
 // 
 //    Rev 1.72   Feb 07 2005 18:05:48   smithdav
 // Removed line that causes BPStarted program to stop working.
 // 
 //    Rev 1.71   Feb 04 2005 21:02:12   smithdav
 // Add support for configurable SonicMQ routings. Was hard coded.
 // 
 //    Rev 1.70   Jan 28 2005 16:30:10   smithdav
 // Fixed default configuration names.
 // 
 //    Rev 1.69   Jan 27 2005 16:38:46   smithdav
 // Restructuring to support a sonicMQ portal and XML base configurables.
 // 
 //    Rev 1.68   Nov 17 2004 15:03:34   PURDYECH
 // PET910 - .NET Conversion
 // 
 //    Rev 1.67   Oct 01 2004 10:19:44   PURDYECH
 // PET910 - Added CommandLine option -T to influence timeout value for RTSSocketConnections.
 // 
 //    Rev 1.66   May 10 2004 19:19:50   SMITHDAV
 // Xerces2 changes, add server process dispatcher, kill server properly.
 // 
 //    Rev 1.65   Mar 26 2004 12:12:16   PURDYECH
 // Added Exception Tracing support
 // Removed potentially fatal call to PlatformUtils::Terminate()
 // Fixed Logging category statements
 // Made configuration errors non-fatal unless --verify_config is specified.
 // 
 //    Rev 1.64   Feb 27 2004 11:53:30   PURDYECH
 // PET910 - Use new program options parsing.
 // 
 //    Rev 1.63   Jan 30 2004 14:04:02   PURDYECH
 // Server information wasn't being logged.
 // 
 //    Rev 1.62   Jan 22 2004 14:47:18   PURDYECH
 // PET910 - Make more robust in the style of FAST BPServer.
 // 
 //    Rev 1.61   Aug 21 2003 11:00:44   PURDYECH
 // Services are no longer support.  Vision Server is now in this project.
 // Support for new logging scheme.
 // 
 //    Rev 1.60   Jul 29 2003 10:46:50   FENGYONG
 // Add bTrace
 // 
 //    Rev 1.59   Mar 21 2003 17:52:50   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.58   Feb 19 2003 15:18:38   SMITHDAV
 // Update VisionServer to have a sigleton interface and expected by the core classes.
 // 
 //    Rev 1.57   Oct 09 2002 23:53:48   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.56   Aug 29 2002 12:57:40   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.55   Jul 30 2002 10:57:34   PURDYECH
 // Once application is defined we must set the default market from the registry
 // 
 //    Rev 1.54   07 Jun 2002 10:55:26   SMITHDAV
 // Sync-up with Chris' changes.
 // 
 //    Rev 1.53   14 May 2002 16:44:16   SMITHDAV
 // put xparser code namespace xp.
 // 
 //    Rev 1.52   10 May 2002 12:55:14   SMITHDAV
 // Console interface changes.
 // 
 //    Rev 1.51   02 Apr 2002 13:42:40   SMITHDAV
 // Change the way XML processing is handled.
 // 
 //    Rev 1.50   11 Oct 2001 17:49:20   SMITHDAV
 // Moved keyboard loop to Server, changed process
 // manager related stuff.
 // 
 //    Rev 1.49   Oct 05 2001 14:00:56   PURDYECH
 // Merged with some changes from Dave Smith for JobQueues.
 // 
 //    Rev 1.48   25 Sep 2001 13:25:08   PURDYECH
 // Added a Ctrl-Break handler.
 // 
 //    Rev 1.47   20 Sep 2001 09:56:50   PURDYECH
 // Added 'q' option to turn off Dave's Fancy Console(tm).
 // 
 //    Rev 1.46   19 Sep 2001 11:47:28   PURDYECH
 // Added BFIPBlast cleanup
 // 
 //    Rev 1.45   18 Sep 2001 11:33:22   PURDYECH
 // Added 'b' command line option for IPBlast recording
 // Added 'e' command line option to set environment variables
 // Added 'N' command line option to set the minimum number of Server threads.
 // 
 //    Rev 1.44   31 Jul 2001 14:25:04   PURDYECH
 // Surround all strings with I_() when used by i_cout.
 // 
 //    Rev 1.43   17 Jul 2001 11:38:54   PURDYECH
 // TxnStats::enable changed to TxnStats::autoEnable
 // 
 //    Rev 1.42   Jun 26 2001 12:55:28   PURDYECH
 // Infrastructure Release 1.9 Integration.
 // 
 //    Rev 1.41   10 May 2001 14:46:08   SMITHDAV
 // New Session stuff.
 // 
 //    Rev 1.40   Feb 21 2001 16:13:42   YINGZ
 // make it compilable for new stuff
 // 
 //    Rev 1.39   Feb 13 2001 10:44:42   HSUCHIN
 // fixed to use DSTCRequestor to set the Host information.
 // 
 //    Rev 1.38   Feb 09 2001 16:47:52   YINGZ
 // change dstsaxstatefactory to dstsaxfactory
 // 
 //    Rev 1.37   Feb 09 2001 14:32:32   YINGZ
 // fix
 // 
 //    Rev 1.36   Feb 09 2001 14:11:44   YINGZ
 // add dstxparser project
 // 
 //    Rev 1.35   31 Jan 2001 14:09:58   PURDYECH
 // Dave Smith's fancy consoles were deleted accidentally.  They have been readded.
 // 
 //    Rev 1.34   Jan 30 2001 16:26:22   YINGZ
 // init SaxStateFactory
 // 
 //    Rev 1.33   Jan 25 2001 17:04:56   OLTEANCR
 // call setWorkSessionDetailsFactory(.. ) in void init(..) 
 // 
 //    Rev 1.32   Jan 25 2001 16:58:34   YINGZ
 // add saxfactory
 // 
 //    Rev 1.31   06 Dec 2000 16:24:40   SMITHDAV
 // Tweak monitors, and add thread pool monitor
 // 
 //    Rev 1.30   06 Dec 2000 11:47:46   SMITHDAV
 // Update monitoring console; Added DataBroker monitor.
 // 
 //    Rev 1.29   04 Dec 2000 11:38:44   SMITHDAV
 // Add console connection monitoring support.
 // 
 //    Rev 1.28   Nov 24 2000 14:51:34   HSUCHIN
 // added RIP Processing option
 // 
 //    Rev 1.27   Nov 21 2000 10:20:50   VASILEAD
 // Added bfconmgr_d.lib for link
 // 
 //    Rev 1.26   Nov 15 2000 14:19:40   DT24433
 // changes for xerces xml
 // 
 //    Rev 1.25   Sep 14 2000 11:59:16   YINGZ
 // change to create new service for each page request
 // 
 //    Rev 1.24   Sep 07 2000 12:01:46   FENGYONG
 // Add new service
 // 
 //    Rev 1.23   Aug 15 2000 14:57:42   YINGZ
 // disable sysload
 // 
 //    Rev 1.22   Aug 11 2000 17:00:06   FENGYONG
 // add EntityList service
 // 
 //    Rev 1.21   Aug 04 2000 11:11:42   YINGZ
 // add command line param
 // 
 //    Rev 1.20   Aug 03 2000 11:28:36   YINGZ
 // support RTSSocket
 // 
 //    Rev 1.19   Aug 02 2000 16:20:48   VASILEAD
 // Added Maintenance Service
 // 
 //    Rev 1.18   Jul 28 2000 16:35:12   VASILEAD
 // Added VerificationConf service back
 // 
 //    Rev 1.17   Jul 25 2000 17:34:08   YINGZ
 // add internal logon off service
 // 
 //    Rev 1.16   Jul 21 2000 14:57:40   VASILEAD
 // Fixed VerificationConf
 // 
 //    Rev 1.15   Jul 20 2000 15:18:34   VASILEAD
 // Added VerificationConf service, process and CBO
 // 
 //    Rev 1.14   Jun 27 2000 11:37:14   VASILEAD
 // simplified the connection model, took out AbstractConnectionManager
 // 
 //    Rev 1.13   Jun 16 2000 10:36:14   VASILEAD
 // Reduced the number of transacions to be sent
 // 
 //    Rev 1.12   Jun 06 2000 10:47:50   POPESCUS
 // cleaned up the code to support only one threading model
 // 
 //    Rev 1.11   May 24 2000 10:43:54   VASILEAD
 // Changed BrokerList and BranchList services
 // 
 //    Rev 1.10   May 23 2000 10:33:18   POPESCUS
 // fixed listening to one port mechanism
 // 
 //    Rev 1.9   May 17 2000 11:05:34   POPESCUS
 // added mechanism to support levels of logging to the server
 // 
 //    Rev 1.8   May 12 2000 16:21:44   YINGZ
 // increase mac connection num
 // 
 //    Rev 1.7   May 11 2000 11:34:34   SMITHDAV
 // New required parameter for VmPrivateConnectionFactory constructor.
 // 
 //    Rev 1.6   May 08 2000 17:08:54   YINGZ
 // add RedCodeByTaxType service
 // 
 //    Rev 1.5   Apr 25 2000 16:11:34   YINGZ
 // add new service
 // 
 //    Rev 1.4   Apr 20 2000 15:15:54   DT24433
 // added several singleton startup/cleanup calls
 // 
 //    Rev 1.3   Apr 17 2000 10:36:40   POPESCUS
 // save work
 // 
 //    Rev 1.2   Apr 13 2000 14:24:16   FENGYONG
 // fix
 // 
 //    Rev 1.1   Apr 06 2000 16:10:28   FENGYONG
 // change geIinstance()
 // 
 //    Rev 1.0   Apr 04 2000 10:28:10   POPESCUS
 // Initial revision.
 * 
 *    Rev 1.0   Feb 16 2000 12:49:56   POPESCUS
 * Initial revision.
 * 
 */