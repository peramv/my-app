// TESessionFactory.cpp: implementation of the TESessionFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "TESessionFactory.h"
#include <windows.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TESession *
TESessionFactory::CreateTESession(HWND hWnd, const std::string &TEKey, const std::string &param, const std::string &host)
{
   std::string fullKey = "SOFTWARE\\DST\\TESession\\";
   fullKey.append(TEKey);

   HKEY hSessionKey; // handle to the session key
//   if (ERROR_SUCCESS != RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\DST Canada Inc.\\TESession\\STUB", &hSessionKey))
   if( ERROR_SUCCESS != RegOpenKey(HKEY_LOCAL_MACHINE, fullKey.c_str(), &hSessionKey) )
   {
      return(NULL);
   }

   DWORD size, type;
   char *moduleName = NULL;
   char *creationImport = NULL;
   char *releaseImport = NULL;
//   long capabilities;

   // find the size of the Module Name
   if( ERROR_SUCCESS != RegQueryValueEx(hSessionKey, "ModuleName", NULL, &type, NULL, &size ) || type!=REG_SZ )
   {
      RegCloseKey(hSessionKey);
      return(NULL);
   }

   // get the Module Name
   moduleName = new char[size];
   if( ERROR_SUCCESS != RegQueryValueEx(hSessionKey, "ModuleName", NULL, &type, (LPBYTE)moduleName, &size ) )
   {
      if( NULL != moduleName ) delete[] moduleName;
      RegCloseKey(hSessionKey);
      return(NULL);
   }

   // find the size of the Creation Import
   if( ERROR_SUCCESS != RegQueryValueEx(hSessionKey, "CreationImport", NULL, &type, NULL, &size ) || type!=REG_SZ )
   {
      if( NULL != moduleName ) delete[] moduleName;
      RegCloseKey(hSessionKey);
      return(NULL);
   }

   // get the Creation Import
   creationImport = new char[size];
   if( ERROR_SUCCESS != RegQueryValueEx(hSessionKey, "CreationImport", NULL, &type, (LPBYTE)creationImport, &size ) )
   {
      if( NULL != moduleName ) delete[] moduleName;
      if( NULL != creationImport ) delete[] creationImport;
      RegCloseKey(hSessionKey);
      return(NULL);
   }

   // find the size of the Release Import
   if( ERROR_SUCCESS != RegQueryValueEx(hSessionKey, "ReleaseImport", NULL, &type, NULL, &size ) || type!=REG_SZ )
   {
      if( NULL != moduleName ) delete[] moduleName;
      RegCloseKey(hSessionKey);
      return(NULL);
   }

   // get the Creation Import
   releaseImport = new char[size];
   if( ERROR_SUCCESS != RegQueryValueEx(hSessionKey, "ReleaseImport", NULL, &type, (LPBYTE)releaseImport, &size ) )
   {
      if( NULL != moduleName ) delete[] moduleName;
      if( NULL != creationImport ) delete[] creationImport;
      if( NULL != releaseImport ) delete[] releaseImport;
      RegCloseKey(hSessionKey);
      return(NULL);
   }

   HINSTANCE hModule = LoadLibrary(moduleName);
   if( NULL == hModule )
   {
      if( NULL != moduleName ) delete[] moduleName;
      if( NULL != creationImport ) delete[] creationImport;
      if( NULL != releaseImport ) delete[] releaseImport;
      RegCloseKey(hSessionKey);
      return(NULL);
   }


   TESession *(* createProc)(HWND, const char *, const char *);
   createProc = (TESession *(*)(HWND, const char *, const char *))GetProcAddress(hModule, creationImport ); 
   if( NULL == createProc )
   {
      FreeLibrary(hModule);
      if( NULL != moduleName ) delete[] moduleName;
      if( NULL != creationImport ) delete[] creationImport;
      if( NULL != releaseImport ) delete[] releaseImport;
      RegCloseKey(hSessionKey);
      return(NULL);
   }

   void (* releaseProc)(TESession *);
   releaseProc = (void (*)(TESession *))GetProcAddress(hModule, releaseImport ); 
   if( NULL == releaseProc )
   {
      FreeLibrary(hModule);
      if( NULL != moduleName ) delete[] moduleName;
      if( NULL != creationImport ) delete[] creationImport;
      if( NULL != releaseImport ) delete[] releaseImport;
      RegCloseKey(hSessionKey);
      return(NULL);
   }

   TESession *newSession = createProc(hWnd, param.c_str(), host.c_str());
   if( NULL == newSession )
   {
      FreeLibrary(hModule);
      if( NULL != moduleName ) delete[] moduleName;
      if( NULL != creationImport ) delete[] creationImport;
      if( NULL != releaseImport ) delete[] releaseImport;
      RegCloseKey(hSessionKey);
      return(NULL);
   }

   newSession->hModule = hModule;
   newSession->releaseProc = releaseProc;

   if( NULL != moduleName ) delete[] moduleName;
   if( NULL != creationImport ) delete[] creationImport;
   if( NULL != releaseImport ) delete[] releaseImport;
   RegCloseKey(hSessionKey);

   return(newSession);
}

void 
TESessionFactory::ReleaseTESession(TESession *session)
{

   HINSTANCE hModule = session->hModule;
   void (* releaseProc)(TESession *) = session->releaseProc;

   releaseProc(session);

   FreeLibrary(hModule);

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/tesession/tesession/TESessionFactory.cpp-arc  $
 * 
 *    Rev 1.3   Nov 24 2003 16:00:54   HSUCHIN
 * PTS 10020087 - Enhanced to take host information.
 */
