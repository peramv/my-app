
// CsiSession.h: interface for the CsiSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CSISESSION_H__INCLUDED_)
   #define _CSISESSION_H__INCLUDED_

   #define VISIBLE_NAV false

   #include <ifastcsi\xplatform.h>
   #include <string>
   #include <map>

   #include <ifastcsi\CsiException.h>

class CsiComponent;
class CsiScreen;

typedef void (D_CALLBACK *CsiProcess)(void);

class TESession;

class  D_LINKAGE CsiSession  : public DThread
{
public:
   virtual ~CsiSession();

   static CsiSession &getInstance();

   void cleanup();
   void closeTerminalSession();
   void resetTerminalSession();

   TESession * const getTerminal() const {return(teSession);}

   void registerScreen(CsiScreen *screen);
   const CsiScreen *getScreen(const std::string &name);

   void setParameter(const std::string &name, const std::string &value);
   const std::string &getParameter(const std::string &name, const std::string &defualtValue="") const;
   void clearParameters();

   void registerPresetProcess(CsiProcess process);
   void registerResetProcess(CsiProcess process);

   void registerProcess(const std::string &name, CsiProcess process);
   CsiProcess getProcess(const std::string &name) const;
   bool executeProcess(const std::string &name);
   bool IsReflectionStart(){return(_bInitFlag == true);}

   void setSessionConfig( HWND hWnd, const std::string &sessionType, const std::string &sessionParam, const std::string &sessionHost ); // cannot be call after first execute...

   void clearProcesses();

protected:
   virtual void run();

private:

   CsiSession();
   static CsiSession session;


   void init();
   bool IsChooseManageCompany(); //1999.12.16

   DSemaphore startedSemaphore;  // prevents more than one processing thread from being started

   TESession *teSession;
   DMutex teSessionMutex; // locks the teSession pointer againt read/write contention

   CsiProcess pendingProcess;
   DMutex pendingProcessMutex;   // locks the pendingProcess variable againt read/write contention

   DEvent processPendingEvent;   // signals the processing thread that there is a pending process


   DSemaphore sessionActiveSemaphore;  // the processing thread holds this semaphore while the session is active
                                       // resetTerminalSession() checks this to determine state.

   DEvent processingCompleteEvent;     // signals the main thread that processing is complete.

   DEvent sessionCloseEvent;  // signals the processing thread to closes

   std::map<std::string, std::string> parameterMap;
   DMutex parameterMapMutex;  // locks the parameterMap againt read/write contention

   std::map<std::string, CsiScreen *> screenMap;
   DMutex screenMapMutex; // locks the screenMap againt read/write contention

   CsiProcess presetProcess;
   CsiProcess resetProcess;
   std::map<std::string, CsiProcess> processMap;
   DMutex processMapMutex; // locks the presetProcess, presetProcess, and processMap variable againt read/write contention

   HWND _hWnd;
   std::string _sessionType;
   std::string _sessionParam;
   std::string _sessionHost;
   bool _bInitFlag;

};

class CsiSessionInitFailure : public CsiException
{
public:
   CsiSessionInitFailure(const std::string &subMsg)
   : _subMsg(subMsg) {}

   virtual const std::string getMessage() {return("Csi Session initialization failed " + _subMsg);}
private:
   std::string _subMsg;
};

class CsiScreenAlreadyExists : public CsiException
{
public:
   CsiScreenAlreadyExists(const std::string &screenName)
   : _screenName(screenName) {}

   virtual const std::string getMessage() {return("A screen identified by \"" + _screenName + "\" has already been registered with the Csi Session.");}
private:
   std::string _screenName;
};

class CsiScreenNotFound : public CsiException
{
public:
   CsiScreenNotFound(const std::string &screenName)
   : _screenName(screenName) {}

   virtual const std::string getMessage() {return("A screen identified by \"" + _screenName + "\" has not been registered with the Csi Session.");}
private:
   std::string _screenName;
};

class CsiProcessAlreadyExists : public CsiException
{
public:
   CsiProcessAlreadyExists(const std::string &processName)
   : _processName(processName) {}

   virtual const std::string getMessage() {return("A process identified by \"" + _processName + "\" has already been registered with the Csi Session.");}
private:
   std::string _processName;
};

class CsiProcessNotFound : public CsiException
{
public:
   CsiProcessNotFound(const std::string &processName)
   : _processName(processName) {}

   virtual const std::string getMessage() {return("A process identified by \"" + _processName + "\" has not been registered with the Csi Session.");}
private:
   std::string _processName;
};

#endif // !defined(_CSISESSION_H__INCLUDED_)

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcsi/CsiSession.h-arc  $
 * 
 *    Rev 1.4   Nov 24 2003 15:54:36   HSUCHIN
 * PTS 10020087 - Enhanced to pass host information to TeSession
 */
