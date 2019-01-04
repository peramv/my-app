// CsiSession.cpp: implementation of the CsiSession class.
//
//////////////////////////////////////////////////////////////////////

#include "CsiSession.h"
#include <tesession\TESession.h>
#include <tesession\TESessionFactory.h>

#include "CsiScreen.h"

#include "CsiIdentifier.h"

#include <assert.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static const char *CHOOSE_MANAGE_COMP1          = "ChooseManageCompany";

CsiSession CsiSession::session; 

CsiSession::CsiSession()
: teSession(NULL)
, pendingProcess(NULL)
, presetProcess(NULL)
, resetProcess(NULL)
, _hWnd(NULL)
, _sessionType()
, _sessionParam()
, _sessionHost()
, _bInitFlag(false)
{
   // init the session config parameters to default

   HKEY hSessionKey; // handle to the session key
   if( ERROR_SUCCESS != RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\DST\\Csi\\TESession\\", &hSessionKey) )
   {
      return;
   }

   DWORD size, type;
   // find the size of the Session Name
   if( ERROR_SUCCESS == RegQueryValueEx(hSessionKey, "Type", NULL, &type, NULL, &size ) || type!=REG_SZ )
   {
      //  get Session Name
      char *cstrValue = new char[size];
      if( ERROR_SUCCESS == RegQueryValueEx(hSessionKey, "Type", NULL, &type, (LPBYTE)cstrValue, &size ) )
      {
         _sessionType = std::string(cstrValue);
      }
      delete[] cstrValue;
   }

   // find the size of the Session Param
   if( ERROR_SUCCESS == RegQueryValueEx(hSessionKey, "Param", NULL, &type, NULL, &size ) || type!=REG_SZ )
   {
      //  get Session Param
      char *cstrValue = new char[size];
      if( ERROR_SUCCESS == RegQueryValueEx(hSessionKey, "Param", NULL, &type, (LPBYTE)cstrValue, &size ) )
      {
         _sessionParam = std::string(cstrValue);
      }
      delete[] cstrValue;
   }

   // find the size of the Session Param
   if( ERROR_SUCCESS == RegQueryValueEx(hSessionKey, "Host", NULL, &type, NULL, &size ) || type!=REG_SZ )
   {
      //  get Session Param
      char *cstrValue = new char[size];
      if( ERROR_SUCCESS == RegQueryValueEx(hSessionKey, "Host", NULL, &type, (LPBYTE)cstrValue, &size ) )
      {
         _sessionHost = std::string(cstrValue);
      }
      delete[] cstrValue;
   }

   RegCloseKey(hSessionKey);

}

CsiSession::~CsiSession()
{
   cleanup();
}

CsiSession &
CsiSession::getInstance() 
{
   return(session);
}

void
CsiSession::cleanup()
{
   closeTerminalSession();

   std::map<std::string, CsiScreen*>::iterator &i = screenMap.begin();

   while( i != screenMap.end() )
   {
      delete (*i).second;
      i++;
//      i = screenMap.erase(i);
   }

   screenMap.clear();
}

void
CsiSession::run()
{

   teSessionMutex.wait();

   if( NULL != teSession )
   {
      TESessionFactory::ReleaseTESession(teSession);
      teSession=NULL;
   }

   try
   {
      init();
   }
   catch( CsiSessionInitFailure /*&e*/ )
   {
      //DSystem::userMessage(e.getMessage(), "Csi Session");
      teSessionMutex.release();
      startedSemaphore.release();
      processingCompleteEvent.set();
      return;
   }

   teSessionMutex.release();

   try
   {
      while( 1 )
      {
         processPendingEvent.wait();

         sessionActiveSemaphore.wait();

         pendingProcessMutex.wait();
         if( NULL != pendingProcess )
         {
            try
            {
               if( !IsChooseManageCompany() )
               {
                  if( presetProcess )
                     presetProcess();
               }

               pendingProcess();


               processingCompleteEvent.set();

               teSession->setVisible(true);
               teSession->doneWait(tes::TIMEOUT_INFINITE);
               teSession->setVisible(VISIBLE_NAV);

            }
            catch( CsiException &e )
            {
               processingCompleteEvent.set();
               DSystem::userMessage(e.getMessage(), "Csi Session");
               teSession->setVisible(true);
               teSession->doneWait(tes::TIMEOUT_INFINITE);
               teSession->setVisible(VISIBLE_NAV);
            }
            catch( ... )
            {
               processingCompleteEvent.set();
               pendingProcess = NULL;
               pendingProcessMutex.release();
               sessionActiveSemaphore.release();
               throw;
            }

            try
            {
               if( !IsChooseManageCompany() )
               {
                  if( resetProcess )
                     resetProcess();
               }

            }
            catch( CsiException &e )
            {
               DSystem::userMessage(e.getMessage(), "Csi Session");
            }
            catch( ... )
            {
               pendingProcess = NULL;
               pendingProcessMutex.release();
               sessionActiveSemaphore.release();
               throw;
            }

         }
         pendingProcess = NULL;
         pendingProcessMutex.release();
         sessionActiveSemaphore.release();


         if( sessionCloseEvent.wait(0) )
            break;

      }
   }
   catch( DPlatformException &e )
   {
      DSystem::userMessage(e.getMessage(), "Csi Session");
   }
   catch( CsiException &e )
   {
      DSystem::userMessage(e.getMessage(), "Csi Session");
   }
   catch( ... )
   {
      DSystem::userMessage("Unknown Exception in Csi session loop.", "Csi Session");
   }

   teSessionMutex.wait();
   if( teSession!=NULL )
   {
      TESessionFactory::ReleaseTESession(teSession);
      teSession=NULL;
   }
   teSessionMutex.release();

   startedSemaphore.release();

}

bool CsiSession::IsChooseManageCompany()
{
   bool _bRet = false;


   processMapMutex.wait(); // lock the process map
   std::map<std::string, CsiProcess>::iterator &iterator = processMap.find( CHOOSE_MANAGE_COMP1 );

   if( iterator == processMap.end() )
   {

      _bRet = false;
   }
   else if( pendingProcess ==(*iterator).second )
   {

      _bRet = true;
   }
   processMapMutex.release();
   return(_bRet);


}

void 
CsiSession::closeTerminalSession()
{
   sessionCloseEvent.set();

   do {
      sessionCloseEvent.set();

      resetTerminalSession();

      while( !pendingProcessMutex.wait(0) ) {
         DSystem::yeild();
      }
      pendingProcess = NULL;
      processPendingEvent.set();
      pendingProcessMutex.release();

   } while( !join(1000) );
}

void 
CsiSession::resetTerminalSession()
{
      teSessionMutex.wait();
      if( NULL != teSession ) {
         teSession->invokeCancel();
      }
      teSessionMutex.release();

      do {
         DSystem::yeild();
      } while( !sessionActiveSemaphore.wait(0) );
      sessionActiveSemaphore.release();
}

void 
CsiSession::setSessionConfig( HWND hWnd, const std::string &sessionType, const std::string &sessionParam, const std::string &sessionHost )
{
   assert( !_bInitFlag );
   _hWnd = hWnd;
   _sessionType = sessionType;
   _sessionParam = sessionParam;
   _sessionHost = sessionHost;
}

void
CsiSession::init() 
{

   if( teSession == NULL )
   {

      if( _sessionType == "" || _sessionParam  == "" )
      {
         throw CsiSessionInitFailure("Invalid session configuration.");
      }

      teSession = TESessionFactory::CreateTESession( _hWnd, _sessionType, _sessionParam, _sessionHost);
      if( NULL == teSession )
      {
		 DSystem::userMessage("This feature need license for "+ _sessionType + " software, Please contact a support representative for solution. ", "Csi Session");		  
         throw CsiSessionInitFailure("creating session for " + _sessionType + "(" + _sessionParam + ")");		 
      }

      _bInitFlag = true;

   }
}


void
CsiSession::registerScreen(CsiScreen *screen)
{
   screenMapMutex.wait();

   std::map<std::string, CsiScreen *>::iterator &iterator = screenMap.find(screen->getName());
   if( iterator != screenMap.end() )
   {
      screenMapMutex.release();
      delete screen;
      throw CsiScreenAlreadyExists(screen->getName());
   }

   screenMap.insert(std::map<std::string, CsiScreen *>::value_type(screen->getName(), screen));
   screenMapMutex.release();

}

const CsiScreen *
CsiSession::getScreen(const std::string &name)
{
   screenMapMutex.wait();

   std::map<std::string, CsiScreen *>::iterator &iterator = screenMap.find(name);
   if( iterator == screenMap.end() )
   {
      screenMapMutex.release();
      throw CsiScreenNotFound(name);
   }

   screenMapMutex.release();
   return(*iterator).second;
}

void
CsiSession::setParameter(const std::string &name, const std::string &value)
{

   parameterMapMutex.wait();

   std::map<std::string, std::string>::iterator &iterator = parameterMap.find(name);
   if( iterator != parameterMap.end() )
      parameterMap.erase(iterator);

   parameterMap.insert( std::map<std::string, std::string>::value_type(name, value) );

   parameterMapMutex.release();
}

const std::string &
CsiSession::getParameter(const std::string &name, const std::string &defaultValue) const
{
   parameterMapMutex.wait();

   std::map<std::string, std::string>::const_iterator &iterator = parameterMap.find(name);

   if( iterator == parameterMap.end() )
   {
      parameterMapMutex.release();
      return(defaultValue);
   }

   parameterMapMutex.release();
   return(*iterator).second;
}

void
CsiSession::clearParameters()
{
   parameterMapMutex.wait();

   parameterMap.clear();

   parameterMapMutex.release();
}

void
CsiSession::registerPresetProcess(CsiProcess process) 
{
   processMapMutex.wait();
   presetProcess = process;
   processMapMutex.release();
}

void
CsiSession::registerResetProcess(CsiProcess process) 
{
   processMapMutex.wait();
   resetProcess = process;
   processMapMutex.release();
}

void
CsiSession::registerProcess(const std::string &name, CsiProcess process)
{
   processMapMutex.wait();

   std::map<std::string, CsiProcess>::iterator &iterator = processMap.find(name);
   if( iterator != processMap.end() )
   {
      processMapMutex.release();
      throw CsiScreenAlreadyExists(name);
   }

   processMap.insert( std::map<std::string, CsiProcess>::value_type(name, process) );
   processMapMutex.release();
}

CsiProcess
CsiSession::getProcess(const std::string &name) const
{
   processMapMutex.wait();
   std::map<std::string, CsiProcess>::const_iterator &iterator = processMap.find(name);

   if( iterator == processMap.end() )
   {
      processMapMutex.release();
      throw CsiScreenNotFound(name);
   }

   processMapMutex.release();
   return(*iterator).second;
}

bool
CsiSession::executeProcess(const std::string &name)
{
/*
   //for C23 DEMO mode 
   char *rpEnv = NULL;
   rpEnv = getenv( "VIEW_FILES_ONLY" );
   if( rpEnv && !strcmp( rpEnv, "1" ) )
   {
      MessageBox( NULL, "Integrated acces to iFAST", "CSI Session", MB_OK );
      return true;
   }
*/
   //for C4 DEMO mode
   char *rpEnv = NULL;
   rpEnv = getenv( "STUB_MODE" );
   if( rpEnv && !strcmp( rpEnv, "OFFLINE" ) )
   {
      MessageBox( NULL, "Integrated acces to iFAST", "CSI Session", MB_OK );
      return(true);
   }

   if( startedSemaphore.wait(0) ) {
      start(); // not already started
   } else {
      resetTerminalSession();
  }


   processMapMutex.wait(); // lock the process map
   std::map<std::string, CsiProcess>::iterator &iterator = processMap.find(name);

   if( iterator == processMap.end() )
   {
      processMapMutex.release();
//      throw (CsiProcessNotRegistered(name));
      return(false);
   }

   if( !pendingProcessMutex.wait(0) ) // lock the processPending pointer
   {
      processMapMutex.release();
      return(false);
   }

   pendingProcess = (*iterator).second;
   processPendingEvent.set();

   pendingProcessMutex.release();

   processMapMutex.release();

//   processingCompleteEvent.wait();
   while( !processingCompleteEvent.wait(500) )
   {  // shunt paint messages on half second intervals
      DSystem::yeild();
   }
   DSystem::yeild();

   return(true);
}

void
CsiSession::clearProcesses()
{
   processMapMutex.wait();

   processMap.clear();

   processMapMutex.release();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcsi/CsiSession.cpp-arc  $
 * 
 *    Rev 1.7   Oct 02 2006 14:38:14   fengyong
 * #721319 - modify error message when reflection is not set up.
 * 
 *    Rev 1.6   Jul 17 2006 12:06:30   smithdav
 * Fixed dead-lock problem with Reflection v12  by adding message pump to the resetTerminal function while waiting for session close.
 * 
 *    Rev 1.5   Nov 24 2003 15:54:30   HSUCHIN
 * PTS 10020087 - Enhanced to pass host information to TeSession
 * 
 *    Rev 1.4   Jun 09 2003 15:58:02   SMITHDAV
 * Changes related to Attachmate EXTRA integration
 * 
 *    Rev 1.3   Oct 09 2002 23:55:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   Sep 20 2002 15:23:26   SMITHDAV
 * Changes to support multiple Csi configurations for mutliple instances of desktops.
 * 
 *    Rev 1.1   May 22 2001 18:37:04   DINACORN
 * Inserted message in executeProcess() for Demo mode
 *
 */
