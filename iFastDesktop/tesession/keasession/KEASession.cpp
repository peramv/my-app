// KEASession.cpp: implementation of the KEASession class.
//
//////////////////////////////////////////////////////////////////////

#include "KEASession.h"

extern "C"
{
   __declspec( dllexport ) TESession *
   CreateKEASession(const char *host)
   {
      // Initialize OLE 2.0 libraries
      CoInitialize(NULL);

      KEASession *session = new KEASession();
      if (NULL==session) return NULL;
      if (!session->init(host))
      {
         delete session;
         return NULL;
      }
      return session;
//    return new KEASession();
   }

   __declspec( dllexport ) void
   ReleaseKEASession(TESession *session)
   {
      delete session;
      CoUninitialize();
   }

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KEASession::KEASession()
{
   screen = NULL;
}

KEASession::~KEASession()
{
   if (NULL != screen)
      delete screen;

}

bool
KEASession::init(const char *host)
{

   COleException error;

   CLSID clsid;
   SCODE sc = AfxGetClassIDFromString("KEA!.Session", &clsid);
   if (FAILED(sc))
   {
      return false;
   }

   LPCLASSFACTORY lpcf;
   sc = CoGetClassObject(clsid, CLSCTX_ALL, NULL, IID_IClassFactory, (LPVOID *)&lpcf);
   if (FAILED(sc))
   {
      return false;
   }

   Sleep(5000);	// Wait for user to close the evalution licence Dialog
					// N.B. should be removed for licenced copy.


   LPPERSISTFILE lpPersistFile = NULL;
   sc = lpcf->CreateInstance(NULL, IID_IPersistFile, (LPVOID *)&lpPersistFile);
   if (FAILED(sc))
   {
      lpcf->Release();
      return false;
   }


   sc = lpPersistFile->Load((LPCOLESTR) L"C:\\kea\\User\\cfxint.ktc", STGM_READ);
   if (FAILED(sc))
   {
      lpPersistFile->Release();
      lpcf->Release();
      return false;
   }

   lpPersistFile->Release();


   LPUNKNOWN lpUnknown = NULL;
   sc = lpcf->CreateInstance(NULL, IID_IUnknown, (LPVOID *)&lpUnknown);
   if (FAILED(sc))
   {
      lpcf->Release();
      return false;
   }

   // query for IDispatch interface
   LPDISPATCH lpDispatch;
   lpUnknown->QueryInterface(IID_IDispatch, (LPVOID *)&lpDispatch);
   if (lpDispatch == NULL)
   {
      lpUnknown->Release();
      lpcf->Release();
      return false;
   }

   ksession.AttachDispatch(lpDispatch);

   lpUnknown->Release();
   lpcf->Release();

   LPDISPATCH pScreenDispatch = ksession.GetScreen();
   screen = new KEAScreen(pScreenDispatch);
   if (NULL == screen)
   {
      return false;
   }

   return true;
}

bool
KEASession::getVisible()
{
   return (TRUE==ksession.GetVisible());
}

void
KEASession::setVisible(bool set)
{
   if (set) ksession.Activate();
   ksession.SetVisible(set? TRUE: FALSE);
   if (set) ksession.Activate();
}

bool
KEASession::getConnected()
{
   return (TRUE==ksession.GetConnected());
}

void
KEASession::setConnected(bool set)
{
   ksession.SetConnected(set? TRUE: FALSE);
}

void 
KEASession::sendKeyboardString(const std::string &input)
{
}

void 
KEASession::sendKeyboardSpecial(keys key)
{
}

long 
KEASession::streamTextWait(long timeout, const std::string &text)
{
   screen->WaitForStream(text.c_str(), timeout*1000);
   return tes::EVENT_TIMEOUT;
}

long 
KEASession::displayTextWait(long timeout, const std::string &text, TEPosition &position)
{
   screen->WaitForString(text.c_str(), timeout*1000, position.row, position.column);
   return tes::EVENT_TIMEOUT;
}

long 
KEASession::
displayTextWait(long timeout, const std::string &text, TEPosition &startPos, TEPosition &endPos)
{
   screen->WaitForString(text.c_str(), timeout*1000, startPos.row, startPos.column);
   return tes::EVENT_TIMEOUT;
}




long 
KEASession::cursorWait(long timeout, TEPosition &position)
{
   screen->WaitForCursor(timeout*1000, position.row, position.column);
   return tes::EVENT_TIMEOUT;
}

long 
KEASession::silenceWait(long timeout, long duration)
{
   return tes::EVENT_TIMEOUT;
}

long
KEASession::doneWait(long timeout)
{
   return tes::EVENT_TIMEOUT;
}

long 
KEASession::setStreamTextWait(const std::string &text)
{
   return 0L;
}

long 
KEASession::setDisplayTextWait(const std::string &text, TEPosition &position)
{
   return 0L;
}

long 
KEASession::setCursorWait(TEPosition &position)
{
   return 0L;
}

long
KEASession::setDoneWait()
{
   return 0L;
}

long 
KEASession::setSilenceWait(long duration)
{
   return 0L;
}

long 
KEASession::wait(long timeout)
{
   return tes::EVENT_TIMEOUT;
}

TEPosition &
KEASession::getCursorPosition(TEPosition &position)
{
   return position;
}

TESelection &
KEASession::getCurrentSelection(TESelection &selection)
{
   return selection;
}

std::string &
KEASession::getDisplayText(const TESelection &selection, std::string &buffer)
{
   return buffer;
}

bool
KEASession::findDisplayText(const std::string &text, TEPosition &position)
{
      return false;
}

void
KEASession::invokeCancel()
{
}
