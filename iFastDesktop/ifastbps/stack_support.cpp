#include "stdafx.h"

// imagehlp.h must be compiled with packing to eight-byte-boundaries,
// but does nothing to enforce that. I am grateful to Jeff Shanholtz
// <JShanholtz@premia.com> for finding this problem.
#pragma pack( push, before_imagehlp, 8 )
#include <imagehlp.h>
#pragma pack( pop, before_imagehlp )

#include <bfutil/seh_exception.hpp>
#include <eh.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <exechist.hpp>

#include <bfutil/bfcritsec.hpp>
#include <bfutil/bfguard.hpp>

#define gle (GetLastError())
#define lenof(a) (sizeof(a) / sizeof((a)[0]))
#define MAXNAMELEN 1024 // max name length for found symbols
#define IMGSYMLEN ( sizeof IMAGEHLP_SYMBOL )
#define TTBUFLEN 65536 // for a temp buffer

typedef enum
{
   typeDefault = 0, typeAdvancedServer = 1, typeWorkstation = 2, typeServer = 3
} NTTYPE;

#define OUT
#define IN

// SymCleanup()
typedef BOOL (__stdcall *tSC)( IN HANDLE hProcess );
tSC pSC = NULL;

// SymFunctionTableAccess()
typedef PVOID (__stdcall *tSFTA)( HANDLE hProcess, DWORD AddrBase );
tSFTA pSFTA = NULL;

// SymGetLineFromAddr()
typedef BOOL (__stdcall *tSGLFA)( IN HANDLE hProcess, IN DWORD dwAddr,
                                  OUT PDWORD pdwDisplacement, OUT PIMAGEHLP_LINE Line );
tSGLFA pSGLFA = NULL;

// SymGetModuleBase()
typedef DWORD (__stdcall *tSGMB)( IN HANDLE hProcess, IN DWORD dwAddr );
tSGMB pSGMB = NULL;

// SymGetModuleInfo()
typedef BOOL (__stdcall *tSGMI)( IN HANDLE hProcess, IN DWORD dwAddr, OUT PIMAGEHLP_MODULE ModuleInfo );
tSGMI pSGMI = NULL;

// SymGetOptions()
typedef DWORD (__stdcall *tSGO)( VOID );
tSGO pSGO = NULL;

// SymGetSymFromAddr()
typedef BOOL (__stdcall *tSGSFA)( IN HANDLE hProcess, IN DWORD dwAddr,
                                  OUT PDWORD pdwDisplacement, OUT PIMAGEHLP_SYMBOL Symbol );
tSGSFA pSGSFA = NULL;

// SymInitialize()
typedef BOOL (__stdcall *tSI)( IN HANDLE hProcess, IN PSTR UserSearchPath, IN BOOL fInvadeProcess );
tSI pSI = NULL;

// SymLoadModule()
typedef DWORD (__stdcall *tSLM)( IN HANDLE hProcess, IN HANDLE hFile,
                                 IN PSTR ImageName, IN PSTR ModuleName, IN DWORD BaseOfDll, IN DWORD SizeOfDll );
tSLM pSLM = NULL;

// SymSetOptions()
typedef DWORD (__stdcall *tSSO)( IN DWORD SymOptions );
tSSO pSSO = NULL;

// StackWalk()
typedef BOOL (__stdcall *tSW)( DWORD MachineType, HANDLE hProcess,
                               HANDLE hThread, LPSTACKFRAME StackFrame, PVOID ContextRecord,
                               PREAD_PROCESS_MEMORY_ROUTINE ReadMemoryRoutine,
                               PFUNCTION_TABLE_ACCESS_ROUTINE FunctionTableAccessRoutine,
                               PGET_MODULE_BASE_ROUTINE GetModuleBaseRoutine,
                               PTRANSLATE_ADDRESS_ROUTINE TranslateAddress );
tSW pSW = NULL;

// UnDecorateSymbolName()
typedef DWORD (__stdcall WINAPI *tUDSN)( PCSTR DecoratedName, PSTR UnDecoratedName,
                                         DWORD UndecoratedLength, DWORD Flags );
tUDSN pUDSN = NULL;



struct ModuleEntry
{
   std::string imageName;
   std::string moduleName;
   DWORD baseAddress;
   DWORD size;
};
typedef std::vector< ModuleEntry > ModuleList;
typedef ModuleList::iterator ModuleListIter;

int threadAbortFlag = 0;

void ShowStack( HANDLE hThread, CONTEXT& c, char* pszLogFile ); // dump a stack
DWORD __stdcall TargetThread( void *arg );
void ThreadFunc1();
void ThreadFunc2();
DWORD Filter( EXCEPTION_POINTERS *ep );
void enumAndLoadModuleSymbols( HANDLE hProcess, DWORD pid, FILE* );
bool fillModuleList( ModuleList& modules, DWORD pid, HANDLE hProcess, FILE* );
bool fillModuleListTH32( ModuleList& modules, DWORD pid, FILE* );
bool fillModuleListPSAPI( ModuleList& modules, DWORD pid, HANDLE hProcess, FILE* );
static void logStackDump( HANDLE hProcess, DWORD frame, FILE* pLogFile );
static void logRegisters(FILE *hf, CONTEXT& c);
static void logMachineConfiguration( FILE *hf );
//CP20040223static void logKlingonLogo( FILE* pLogFile );
static void logIFDSLogo( FILE* pLogFile );
static NTTYPE getNTVersion( void );

BFCritSec s_csEnableReporting;
static bool s_bEnableReporting = true;

void enableExceptionReporting( bool b ) 
{
   BFGuard g( s_csEnableReporting );
   s_bEnableReporting = b;
}
extern "C" { WINBASEAPI BOOL WINAPI IsDebuggerPresent( VOID );}

bool isExceptionReportingEnabled()
{
#if !defined( BFRELSYM )
   // if not a Symbols build then exception reporting is never enabled
   return( false );
#else
   if( IsDebuggerPresent() ) 
   {
      return false;
   }

   BFGuard g( s_csEnableReporting );
   return s_bEnableReporting;
#endif
}


__declspec( thread ) bool t_bReportingException = false;

int WINAPI ReportException(LPEXCEPTION_POINTERS pXP, char* pszLogFile )
{
   int rc = EXCEPTION_CONTINUE_SEARCH;
   // Don't report on nested exceptions
   if( true == t_bReportingException )
   {
      return(EXCEPTION_CONTINUE_SEARCH);
   }

   switch( pXP->ExceptionRecord->ExceptionCode )
   {
      case EXCEPTION_BREAKPOINT:
      case EXCEPTION_DATATYPE_MISALIGNMENT:
      case EXCEPTION_GUARD_PAGE:
      case EXCEPTION_SINGLE_STEP:
         // don't report for 'common' exceptions which are handled by the OS
         return(EXCEPTION_CONTINUE_SEARCH);
   }

   if( false == isExceptionReportingEnabled() ) {
      // don't report if exception reporting is disabled
      return(EXCEPTION_CONTINUE_SEARCH);
   }

   t_bReportingException = true;
   rc = EXCEPTION_EXECUTE_HANDLER;
   ShowStack( ::GetCurrentThread(), *(pXP->ContextRecord), pszLogFile );
   t_bReportingException = false;

   return(rc);

}// ReportExceptions()


void XlateFunction(unsigned int u, LPEXCEPTION_POINTERS pXP)
{
   // do some pre-processing here (like ... call ReportException() !)
   char szLogFile[ _MAX_PATH + 1 ];
   if( ReportException(pXP, szLogFile ) == EXCEPTION_EXECUTE_HANDLER )
   {
      throw(SEH_Exception( pXP->ExceptionRecord->ExceptionCode, szLogFile ));
   }
   // if we don't throw an exception it is equivalent to continuing the
   // search (i.e. EXCEPTION_CONTINUE_SEARCH)
}



static HINSTANCE hImagehlpDll = NULL;

int StackSupportInit()
{
#if !defined(BFRELSYM)
   // if not generating Symbols build then just return ... don't setup exception tracing
   return( 0 );
#else
   hImagehlpDll = LoadLibrary( "imagehlp.dll" );
   if( hImagehlpDll == NULL )
   {
      fprintf( stderr, "LoadLibrary( \"imagehlp.dll\" ): gle = %lu\n", gle );
      return(1);
   }

   pSC = (tSC) GetProcAddress( hImagehlpDll, "SymCleanup" );
   pSFTA = (tSFTA) GetProcAddress( hImagehlpDll, "SymFunctionTableAccess" );
   pSGLFA = (tSGLFA) GetProcAddress( hImagehlpDll, "SymGetLineFromAddr" );
   pSGMB = (tSGMB) GetProcAddress( hImagehlpDll, "SymGetModuleBase" );
   pSGMI = (tSGMI) GetProcAddress( hImagehlpDll, "SymGetModuleInfo" );
   pSGO = (tSGO) GetProcAddress( hImagehlpDll, "SymGetOptions" );
   pSGSFA = (tSGSFA) GetProcAddress( hImagehlpDll, "SymGetSymFromAddr" );
   pSI = (tSI) GetProcAddress( hImagehlpDll, "SymInitialize" );
   pSSO = (tSSO) GetProcAddress( hImagehlpDll, "SymSetOptions" );
   pSW = (tSW) GetProcAddress( hImagehlpDll, "StackWalk" );
   pUDSN = (tUDSN) GetProcAddress( hImagehlpDll, "UnDecorateSymbolName" );
   pSLM = (tSLM) GetProcAddress( hImagehlpDll, "SymLoadModule" );

   if( pSC == NULL || pSFTA == NULL || pSGMB == NULL || pSGMI == NULL ||
       pSGO == NULL || pSGSFA == NULL || pSI == NULL || pSSO == NULL ||
       pSW == NULL || pUDSN == NULL || pSLM == NULL )
   {
      fputs( "GetProcAddress(): some required function not found.\n", stderr );
      FreeLibrary( hImagehlpDll );
      return(1);
   }

// Ignore warning about /EHa, because we want the exceptions to flow through
// Our code handles all of the stuff that /EHa provides that /EHsc doesn't
#pragma warning( disable: 4535 )
   _set_se_translator(XlateFunction);        // set it for this function
   setGlobalSeTranslator( XlateFunction );   // set it for all threads which will be started.
   return( 0 );
#endif
}


static void ShowStack( HANDLE hThread, CONTEXT& c, char* pszLogFile )
{
   // normally, call ImageNtHeader() and use machine info from PE header
   DWORD imageType = IMAGE_FILE_MACHINE_I386;
   HANDLE hProcess = GetCurrentProcess(); // hProcess normally comes from outside
   int frameNum; // counts walked frames
   DWORD offsetFromSymbol; // tells us how far from the symbol we were
   DWORD offsetFromLine; // tells us how far from the line we were
   DWORD symOptions; // symbol handler settings
   IMAGEHLP_SYMBOL *pSym = (IMAGEHLP_SYMBOL *) malloc( IMGSYMLEN + MAXNAMELEN );
   char undName[MAXNAMELEN]; // undecorated name
   char undFullName[MAXNAMELEN]; // undecorated name with all shenanigans
   IMAGEHLP_MODULE Module;
   IMAGEHLP_LINE Line;
   std::string symSearchPath;
   char *tt = 0, *p;

   // create logfile name
   SYSTEMTIME st;
   GetSystemTime( &st );
   _snprintf( pszLogFile, _MAX_PATH + 1, "bps_%04d%02d%02d%02d%02d%02d%03d_%04x.err",
              st.wYear,
              st.wMonth,
              st.wDay,
              st.wHour,
              st.wMinute,
              st.wSecond,
              st.wMilliseconds,
              GetCurrentThreadId() );

   printf( "Writing logfile to %s\n", pszLogFile );
   FILE* pLogFile = fopen( pszLogFile, "w" );
   if( NULL == pLogFile )
   {
      *pszLogFile = 0x00;
      pLogFile = stderr;
   }

   fputs( "International Financial Data Services (Canada) proudly presents...\n", pLogFile );
   fputs( "A BPServer Exception Trace!\n", pLogFile );
   fputs( "\n", pLogFile );
   logIFDSLogo( pLogFile );
   fputs( "\n", pLogFile );
   logMachineConfiguration( pLogFile );
   logRegisters( pLogFile, c );

   STACKFRAME s; // in/out stackframe
   memset( &s, '\0', sizeof s );

   // NOTE: normally, the exe directory and the current directory should be taken
   // from the target process. The current dir would be gotten through injection
   // of a remote thread; the exe fir through either ToolHelp32 or PSAPI.

   tt = new char[TTBUFLEN]; // this is a _sample_. you can do the error checking yourself.

   // build symbol search path from:
   symSearchPath = "";
   // current directory
   if( GetCurrentDirectory( TTBUFLEN, tt ) )
      symSearchPath += tt + std::string( ";" );
   // dir with executable
   if( GetModuleFileName( 0, tt, TTBUFLEN ) )
   {
      for( p = tt + strlen( tt ) - 1; p >= tt; -- p )
      {
         // locate the rightmost path separator
         if( *p == '\\' || *p == '/' || *p == ':' )
            break;
      }
      // if we found one, p is pointing at it; if not, tt only contains
      // an exe name (no path), and p points before its first byte
      if( p != tt ) // path sep found?
      {
         if( *p == ':' ) // we leave colons in place
            ++ p;
         *p = '\0'; // eliminate the exe name and last path sep
         symSearchPath += tt + std::string( ";" );
      }
   }
   // environment variable _NT_SYMBOL_PATH
   if( GetEnvironmentVariable( "_NT_SYMBOL_PATH", tt, TTBUFLEN ) )
      symSearchPath += tt + std::string( ";" );
   // environment variable _NT_ALTERNATE_SYMBOL_PATH
   if( GetEnvironmentVariable( "_NT_ALTERNATE_SYMBOL_PATH", tt, TTBUFLEN ) )
      symSearchPath += tt + std::string( ";" );
   // environment variable SYSTEMROOT
   if( GetEnvironmentVariable( "SYSTEMROOT", tt, TTBUFLEN ) )
      symSearchPath += tt + std::string( ";" );

   if( symSearchPath.size() > 0 ) // if we added anything, we have a trailing semicolon
      symSearchPath = symSearchPath.substr( 0, symSearchPath.size() - 1 );

   fprintf( pLogFile, "symbols path: %s\n", symSearchPath.c_str() );

   // why oh why does SymInitialize() want a writeable string?
   strncpy( tt, symSearchPath.c_str(), TTBUFLEN );
   tt[TTBUFLEN - 1] = '\0'; // if strncpy() overruns, it doesn't add the null terminator

   // init symbol handler stuff (SymInitialize())
   if( ! pSI( hProcess, tt, false ) )
   {
      fprintf( pLogFile, "SymInitialize(): gle = %lu\n", gle );
      goto cleanup;
   }

   // SymGetOptions()
   symOptions = pSGO();
   symOptions |= SYMOPT_LOAD_LINES;
   symOptions &= ~SYMOPT_UNDNAME;
   pSSO( symOptions ); // SymSetOptions()

   // Enumerate modules and tell imagehlp.dll about them.
   // On NT, this is not necessary, but it won't hurt.
   enumAndLoadModuleSymbols( hProcess, GetCurrentProcessId(), pLogFile );

   // init STACKFRAME for first call
   // Notes: AddrModeFlat is just an assumption. I hate VDM debugging.
   // Notes: will have to be #ifdef-ed for Alphas; MIPSes are dead anyway,
   // and good riddance.
   s.AddrPC.Offset = c.Eip;
   s.AddrPC.Mode = AddrModeFlat;
   s.AddrFrame.Offset = c.Ebp;
   s.AddrFrame.Mode = AddrModeFlat;

   memset( pSym, '\0', IMGSYMLEN + MAXNAMELEN );
   pSym->SizeOfStruct = IMGSYMLEN;
   pSym->MaxNameLength = MAXNAMELEN;

   memset( &Line, '\0', sizeof Line );
   Line.SizeOfStruct = sizeof Line;

   memset( &Module, '\0', sizeof Module );
   Module.SizeOfStruct = sizeof Module;

   offsetFromSymbol = 0;

   ExecutionHistory::dump( pLogFile );

   fprintf( pLogFile, "\n--# FV EIP----- RetAddr- FramePtr StackPtr Symbol\n" );
   for( frameNum = 0; ; ++frameNum )
   {
      // get next stack frame (StackWalk(), SymFunctionTableAccess(), SymGetModuleBase())
      // if this returns ERROR_INVALID_ADDRESS (487) or ERROR_NOACCESS (998), you can
      // assume that either you are done, or that the stack is so hosed that the next
      // deeper frame could not be found.
      if( !pSW( imageType, hProcess, hThread, &s, &c, NULL, pSFTA, pSGMB, NULL ) )
         break;

      // display its contents
      fprintf( pLogFile, "\n%3d %c%c %08lx %08lx %08lx %08lx ",
               frameNum, s.Far? 'F': '.', s.Virtual? 'V': '.',
               s.AddrPC.Offset, s.AddrReturn.Offset,
               s.AddrFrame.Offset, s.AddrStack.Offset );

      if( s.AddrPC.Offset == 0 )
      {
         fprintf( pLogFile, "(-nosymbols- PC == 0)\n" );
      }
      else
      { // we seem to have a valid PC
         // show procedure info (SymGetSymFromAddr())
         if( !pSGSFA( hProcess, s.AddrPC.Offset, &offsetFromSymbol, pSym ) )
         {
            if( gle != 487 )
            {
               fprintf( pLogFile, "SymGetSymFromAddr(): gle = %lu\n", gle );
            }
         }
         else
         {
            // UnDecorateSymbolName()
            pUDSN( pSym->Name, undName, MAXNAMELEN, UNDNAME_NAME_ONLY );
            pUDSN( pSym->Name, undFullName, MAXNAMELEN, UNDNAME_COMPLETE );
            fprintf( pLogFile, "%s", undName );
            if( offsetFromSymbol != 0 )
            {
               fprintf( pLogFile, " %+ld bytes", (long) offsetFromSymbol );
            }
            putc( '\n', pLogFile );
            fprintf( pLogFile, "    Sig:  %s\n", pSym->Name );
            fprintf( pLogFile, "    Decl: %s\n", undFullName );
         }

         // show line number info, NT5.0-method (SymGetLineFromAddr())
         offsetFromLine = 0;
         if( pSGLFA != NULL )
         { // yes, we have SymGetLineFromAddr()
            if( ! pSGLFA( hProcess, s.AddrPC.Offset, &offsetFromLine, &Line ) )
            {
               if( gle != 487 && frameNum > 0 )
               {
                  fprintf( pLogFile, "SymGetLineFromAddr(): gle = %lu\n", gle );
               }
            }
            else
            {
               fprintf( pLogFile, "    Line: %s(%lu) %+ld bytes\n",
                        Line.FileName, Line.LineNumber, offsetFromLine );
            }
         } // yes, we have SymGetLineFromAddr()

         // show module info (SymGetModuleInfo())
         if( ! pSGMI( hProcess, s.AddrPC.Offset, &Module ) )
         {
            fprintf( pLogFile, "SymGetModuleInfo(): gle = %lu\n", gle );
         }
         else
         { // got module info OK
            char ty[80];
            switch( Module.SymType )
            {
               case SymNone:
                  strcpy( ty, "-nosymbols-" );
                  break;
               case SymCoff:
                  strcpy( ty, "COFF" );
                  break;
               case SymCv:
                  strcpy( ty, "CV" );
                  break;
               case SymPdb:
                  strcpy( ty, "PDB" );
                  break;
               case SymExport:
                  strcpy( ty, "-exported-" );
                  break;
               case SymDeferred:
                  strcpy( ty, "-deferred-" );
                  break;
               case SymSym:
                  strcpy( ty, "SYM" );
                  break;
               default:
                  _snprintf( ty, sizeof ty, "symtype=%ld", (long) Module.SymType );
                  break;
            }

            fprintf( pLogFile, "    Mod:  %s[%s], base: %08lxh\n",
                     Module.ModuleName, Module.ImageName, Module.BaseOfImage );
            fprintf( pLogFile, "    Sym:  type: %s, file: %s\n",
                     ty, Module.LoadedImageName );
         } // got module info OK

         logStackDump( GetCurrentProcess(), s.AddrFrame.Offset, pLogFile );

      } // we seem to have a valid PC

      // no return address means no deeper stackframe
      if( s.AddrReturn.Offset == 0 )
      {
         // avoid misunderstandings in the printf() following the loop
         SetLastError( 0 );
         break;
      }

   } // for ( frameNum )

   if( gle != 0 )
      fprintf( pLogFile, "\nStackWalk(): gle = %lu\n", gle );

   cleanup:
   ResumeThread( hThread );
   // de-init symbol handler etc. (SymCleanup())
   pSC( hProcess );
   free( pSym );
   delete [] tt;

   if( NULL != pLogFile && stderr != pLogFile )
   {
      fclose( pLogFile );
   }
}


static void enumAndLoadModuleSymbols( HANDLE hProcess, DWORD pid, FILE* pLogFile )
{
   ModuleList modules;
   ModuleListIter it;
   char *img, *mod;

   // fill in module list
   fillModuleList( modules, pid, hProcess, pLogFile );

   for( it = modules.begin(); it != modules.end(); ++ it )
   {
      // unfortunately, SymLoadModule() wants writeable strings
      img = new char[(*it).imageName.size() + 1];
      strcpy( img, (*it).imageName.c_str() );
      mod = new char[(*it).moduleName.size() + 1];
      strcpy( mod, (*it).moduleName.c_str() );

      if( pSLM( hProcess, 0, img, mod, (*it).baseAddress, (*it).size ) == 0 )
         fprintf( pLogFile, "Error %lu loading symbols for \"%s\"\n",
                  gle, (*it).moduleName.c_str() );
      else
         fprintf( pLogFile, "Symbols loaded: \"%s\"\n", (*it).moduleName.c_str() );

      delete [] img;
      delete [] mod;
   }
}

static bool fillModuleList( ModuleList& modules, DWORD pid, HANDLE hProcess, FILE* pLogFile )
{
   // try toolhelp32 first
   if( fillModuleListTH32( modules, pid, pLogFile ) )
      return(true);
   // nope? try psapi, then
   return(fillModuleListPSAPI( modules, pid, hProcess, pLogFile ));
}



// miscellaneous toolhelp32 declarations; we cannot #include the header
// because not all systems may have it
#define MAX_MODULE_NAME32 255
#define TH32CS_SNAPMODULE   0x00000008
#pragma pack( push, 8 )
typedef struct tagMODULEENTRY32
{
   DWORD   dwSize;
   DWORD   th32ModuleID;       // This module
   DWORD   th32ProcessID;      // owning process
   DWORD   GlblcntUsage;       // Global usage count on the module
   DWORD   ProccntUsage;       // Module usage count in th32ProcessID's context
   BYTE  * modBaseAddr;        // Base address of module in th32ProcessID's context
   DWORD   modBaseSize;        // Size in bytes of module starting at modBaseAddr
   HMODULE hModule;            // The hModule of this module in th32ProcessID's context
   char    szModule[MAX_MODULE_NAME32 + 1];
   char    szExePath[MAX_PATH];
} MODULEENTRY32;
typedef MODULEENTRY32 *  PMODULEENTRY32;
typedef MODULEENTRY32 *  LPMODULEENTRY32;
#pragma pack( pop )



static bool fillModuleListTH32( ModuleList& modules, DWORD pid, FILE* pLogFile )
{
   // CreateToolhelp32Snapshot()
   typedef HANDLE (__stdcall *tCT32S)( DWORD dwFlags, DWORD th32ProcessID );
   // Module32First()
   typedef BOOL (__stdcall *tM32F)( HANDLE hSnapshot, LPMODULEENTRY32 lpme );
   // Module32Next()
   typedef BOOL (__stdcall *tM32N)( HANDLE hSnapshot, LPMODULEENTRY32 lpme );

   // I think the DLL is called tlhelp32.dll on Win9X, so we try both
   const char *dllname[] = { "kernel32.dll", "tlhelp32.dll"};
   HINSTANCE hToolhelp;
   tCT32S pCT32S;
   tM32F pM32F;
   tM32N pM32N;

   HANDLE hSnap;
   MODULEENTRY32 me = { sizeof me};
   bool keepGoing;
   ModuleEntry e;
   int i;

   for( i = 0; i < lenof( dllname ); ++ i )
   {
      hToolhelp = LoadLibrary( dllname[i] );
      if( hToolhelp == 0 )
         continue;
      pCT32S = (tCT32S) GetProcAddress( hToolhelp, "CreateToolhelp32Snapshot" );
      pM32F = (tM32F) GetProcAddress( hToolhelp, "Module32First" );
      pM32N = (tM32N) GetProcAddress( hToolhelp, "Module32Next" );
      if( pCT32S != 0 && pM32F != 0 && pM32N != 0 )
         break; // found the functions!
      FreeLibrary( hToolhelp );
      hToolhelp = 0;
   }

   if( hToolhelp == 0 ) // nothing found?
      return(false);

   hSnap = pCT32S( TH32CS_SNAPMODULE, pid );
   if( hSnap == (HANDLE) -1 )
      return(false);

   keepGoing = !!pM32F( hSnap, &me );
   while( keepGoing )
   {
      // here, we have a filled-in MODULEENTRY32
      fprintf( pLogFile, "%08lXh %6lu %-15.15s %s\n", me.modBaseAddr, me.modBaseSize, me.szModule, me.szExePath );
      e.imageName = me.szExePath;
      e.moduleName = me.szModule;
      e.baseAddress = (DWORD) me.modBaseAddr;
      e.size = me.modBaseSize;
      modules.push_back( e );
      keepGoing = !!pM32N( hSnap, &me );
   }

   CloseHandle( hSnap );

   FreeLibrary( hToolhelp );

   return(modules.size() != 0);
}



// miscellaneous psapi declarations; we cannot #include the header
// because not all systems may have it
typedef struct _MODULEINFO
{
   LPVOID lpBaseOfDll;
   DWORD SizeOfImage;
   LPVOID EntryPoint;
} MODULEINFO, *LPMODULEINFO;



static bool fillModuleListPSAPI( ModuleList& modules, DWORD pid, HANDLE hProcess, FILE* pLogFile )
{
   // EnumProcessModules()
   typedef BOOL (__stdcall *tEPM)( HANDLE hProcess, HMODULE *lphModule, DWORD cb, LPDWORD lpcbNeeded );
   // GetModuleFileNameEx()
   typedef DWORD (__stdcall *tGMFNE)( HANDLE hProcess, HMODULE hModule, LPSTR lpFilename, DWORD nSize );
   // GetModuleBaseName() -- redundant, as GMFNE() has the same prototype, but who cares?
   typedef DWORD (__stdcall *tGMBN)( HANDLE hProcess, HMODULE hModule, LPSTR lpFilename, DWORD nSize );
   // GetModuleInformation()
   typedef BOOL (__stdcall *tGMI)( HANDLE hProcess, HMODULE hModule, LPMODULEINFO pmi, DWORD nSize );

   HINSTANCE hPsapi;
   tEPM pEPM;
   tGMFNE pGMFNE;
   tGMBN pGMBN;
   tGMI pGMI;

   int i;
   ModuleEntry e;
   DWORD cbNeeded;
   MODULEINFO mi;
   HMODULE *hMods = 0;
   char *tt = 0;

   hPsapi = LoadLibrary( "psapi.dll" );
   if( hPsapi == 0 )
      return(false);

   modules.clear();

   pEPM = (tEPM) GetProcAddress( hPsapi, "EnumProcessModules" );
   pGMFNE = (tGMFNE) GetProcAddress( hPsapi, "GetModuleFileNameExA" );
   pGMBN = (tGMFNE) GetProcAddress( hPsapi, "GetModuleBaseNameA" );
   pGMI = (tGMI) GetProcAddress( hPsapi, "GetModuleInformation" );
   if( pEPM == 0 || pGMFNE == 0 || pGMBN == 0 || pGMI == 0 )
   {
      // yuck. Some API is missing.
      FreeLibrary( hPsapi );
      return(false);
   }

   hMods = new HMODULE[TTBUFLEN / sizeof HMODULE];
   tt = new char[TTBUFLEN];
   // not that this is a sample. Which means I can get away with
   // not checking for errors, but you cannot. :)

   if( ! pEPM( hProcess, hMods, TTBUFLEN, &cbNeeded ) )
   {
      fprintf( pLogFile, "EPM failed, gle = %lu\n", gle );
      goto cleanup;
   }

   if( cbNeeded > TTBUFLEN )
   {
      fprintf( pLogFile, "More than %lu module handles. Huh?\n", lenof( hMods ) );
      goto cleanup;
   }

   for( i = 0; i < cbNeeded / sizeof hMods[0]; ++ i )
   {
      // for each module, get:
      // base address, size
      pGMI( hProcess, hMods[i], &mi, sizeof mi );
      e.baseAddress = (DWORD) mi.lpBaseOfDll;
      e.size = mi.SizeOfImage;
      // image file name
      tt[0] = '\0';
      pGMFNE( hProcess, hMods[i], tt, TTBUFLEN );
      e.imageName = tt;
      // module name
      tt[0] = '\0';
      pGMBN( hProcess, hMods[i], tt, TTBUFLEN );
      e.moduleName = tt;
      fprintf( pLogFile, "%08lXh %6lu %-15.15s %s\n", e.baseAddress,
               e.size, e.moduleName.c_str(), e.imageName.c_str() );

      modules.push_back( e );
   }

   cleanup:
   if( hPsapi )
      FreeLibrary( hPsapi );
   delete [] tt;
   delete [] hMods;

   return(modules.size() != 0);
}


//=============================================================================
// Routine to dump an arbitrary number of bytes of the stack to the exception report
//
// Parameters:
//    hf      handle of file to dump to
//
// Return Values:
//    VOID 
//=============================================================================
static void logStackDump( HANDLE hProcess, DWORD frame, FILE* pLogFile )
{
   DWORD   iStackDumpRow;
   DWORD   iStackDumpByte;
   BYTE    abStack[1024];

   memset( abStack, 0, sizeof(abStack) );

   if( frame > 0x20 ) {
      // back up the stack frame so that we can dump the arguments to the function also
      frame -= 0x20;
   }

   if( !::ReadProcessMemory( hProcess, 
                             (const void*)frame,
                             (LPVOID)&abStack[0], 
                             (DWORD)sizeof(abStack), 
                             &iStackDumpRow) )
   {
      return;
   }

   for( iStackDumpRow = 0; iStackDumpRow < 20; ++iStackDumpRow )
   {
      iStackDumpByte = iStackDumpRow * 16;
      fprintf(pLogFile, "    %08x  %02x %02x %02x %02x %02x %02x %02x %02x - %02x %02x %02x %02x %02x %02x %02x %02x  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
              iStackDumpByte + frame,
              abStack[ iStackDumpByte +  0 ],
              abStack[ iStackDumpByte +  1 ],
              abStack[ iStackDumpByte +  2 ],
              abStack[ iStackDumpByte +  3 ],
              abStack[ iStackDumpByte +  4 ],
              abStack[ iStackDumpByte +  5 ],
              abStack[ iStackDumpByte +  6 ],
              abStack[ iStackDumpByte +  7 ],
              abStack[ iStackDumpByte +  8 ],
              abStack[ iStackDumpByte +  9 ],
              abStack[ iStackDumpByte + 10 ],
              abStack[ iStackDumpByte + 11 ],
              abStack[ iStackDumpByte + 12 ],
              abStack[ iStackDumpByte + 13 ],
              abStack[ iStackDumpByte + 14 ],
              abStack[ iStackDumpByte + 15 ],
              isprint( abStack[ iStackDumpByte +  0 ]) ? abStack[ iStackDumpByte +  0 ] : '.',
              isprint( abStack[ iStackDumpByte +  1 ]) ? abStack[ iStackDumpByte +  1 ] : '.',
              isprint( abStack[ iStackDumpByte +  2 ]) ? abStack[ iStackDumpByte +  2 ] : '.',
              isprint( abStack[ iStackDumpByte +  3 ]) ? abStack[ iStackDumpByte +  3 ] : '.',
              isprint( abStack[ iStackDumpByte +  4 ]) ? abStack[ iStackDumpByte +  4 ] : '.',
              isprint( abStack[ iStackDumpByte +  5 ]) ? abStack[ iStackDumpByte +  5 ] : '.',
              isprint( abStack[ iStackDumpByte +  6 ]) ? abStack[ iStackDumpByte +  6 ] : '.',
              isprint( abStack[ iStackDumpByte +  7 ]) ? abStack[ iStackDumpByte +  7 ] : '.',
              isprint( abStack[ iStackDumpByte +  8 ]) ? abStack[ iStackDumpByte +  8 ] : '.',
              isprint( abStack[ iStackDumpByte +  9 ]) ? abStack[ iStackDumpByte +  9 ] : '.',
              isprint( abStack[ iStackDumpByte + 10 ]) ? abStack[ iStackDumpByte + 10 ] : '.',
              isprint( abStack[ iStackDumpByte + 11 ]) ? abStack[ iStackDumpByte + 11 ] : '.',
              isprint( abStack[ iStackDumpByte + 12 ]) ? abStack[ iStackDumpByte + 12 ] : '.',
              isprint( abStack[ iStackDumpByte + 13 ]) ? abStack[ iStackDumpByte + 13 ] : '.',
              isprint( abStack[ iStackDumpByte + 14 ]) ? abStack[ iStackDumpByte + 14 ] : '.',
              isprint( abStack[ iStackDumpByte + 15 ]) ? abStack[ iStackDumpByte + 15 ] : '.'
             );
   }

   fprintf(pLogFile, "\n" );
   fflush(pLogFile);
   return;
}// LogStackDump()


static void logRegisters(FILE *hf, CONTEXT& c)
{
   DWORD dwFlags;
   int iFlags;

   putc( '\n', hf );
   fputs( "--------------------------------\n", hf );
   fputs( "--- i86 Register Information ---\n", hf );
   fputs( "--------------------------------\n", hf );

   if( (c.ContextFlags) & CONTEXT_SEGMENTS )
   {
      // Segment registers
      fprintf(hf,"DS  : %4.4lX     ", c.SegDs);
      fprintf(hf,"ES  : %4.4lX     ", c.SegEs);
      fprintf(hf,"FS  : %4.4lX     ", c.SegFs);
      fprintf(hf,"GS  : %4.4lX\n",    c.SegGs);
   }
   if( (c.ContextFlags) & CONTEXT_INTEGER )
   {
      // Integer registers
      fprintf(hf,"EAX : %8.8lX ",     c.Eax);
      fprintf(hf,"EBX : %8.8lX ",     c.Ebx);
      fprintf(hf,"ECX : %8.8lX ",     c.Ecx);
      fprintf(hf,"EDX : %8.8lX\n",    c.Edx);
      fprintf(hf,"EDI : %8.8lX ",     c.Edi);
      fprintf(hf,"ESI : %8.8lX\n",    c.Esi);
   }
   if( (c.ContextFlags) & CONTEXT_CONTROL )
   {
      // control registers
      fprintf(hf,"EBP : %8.8lX ",     c.Ebp);
      fprintf(hf,"EIP : %8.8lX ",     c.Eip);
      fprintf(hf,"ESP : %8.8lX\n",    c.Esp);
      fprintf(hf,"CS  : %4.4lX     ", c.SegCs);
      fprintf(hf,"SS  : %4.4lX\n",    c.SegSs);

      // convert the flags to a bit array and log it
      dwFlags = c.EFlags;
      fprintf(hf,"EFLG: ");

      for( iFlags = 0; iFlags < (sizeof(dwFlags) * 8); iFlags++, dwFlags <<= 1 )
      {
         if( iFlags % 4 == 0 && iFlags != 0 )
         {
            fprintf(hf, " %1u", (dwFlags & 0x80000000) == 0x80000000);
         }
         else
         {
            fprintf(hf, "%1u", (dwFlags & 0x80000000) == 0x80000000);
         }
      }
   }

   putc( '\n', hf );
   putc( '\n', hf );
   fflush(hf);

   return;
}// logRegisters()

static void logMachineConfiguration( FILE *hf )
{
   OSVERSIONINFO osvi;

   osvi.dwOSVersionInfoSize = sizeof(osvi);
   GetVersionEx(&osvi);

   // Dump out windows version and processor information
   switch( osvi.dwPlatformId )
   {
      case VER_PLATFORM_WIN32_NT:
         switch( getNTVersion() )
         {
            case typeWorkstation:
               fprintf(hf, "Microsoft Windows NT Workstation %u.%u (Build %u) %s",
                       osvi.dwMajorVersion,
                       osvi.dwMinorVersion,
                       osvi.dwBuildNumber,
                       osvi.szCSDVersion);
               break;
            case typeServer:
               fprintf(hf, "Microsoft Windows NT Server %u.%u (Build %u) %s",
                       osvi.dwMajorVersion,
                       osvi.dwMinorVersion,
                       osvi.dwBuildNumber,
                       osvi.szCSDVersion);
               break;
            case typeAdvancedServer:
               fprintf(hf, "Microsoft Windows NT Advanced Server %u.%u (Build %u) %s",
                       osvi.dwMajorVersion,
                       osvi.dwMinorVersion,
                       osvi.dwBuildNumber,
                       osvi.szCSDVersion);
               break;
            default:
               fprintf(hf, "Microsoft Windows NT %u.%u (Build %u) %s",
                       osvi.dwMajorVersion,
                       osvi.dwMinorVersion,
                       osvi.dwBuildNumber,
                       osvi.szCSDVersion);
               break;
         }
         break;
      case VER_PLATFORM_WIN32_WINDOWS:  // i.e. Win95
         fprintf(hf, "Microsoft Windows 95 %u.%u (Build %u) %s",
                 osvi.dwMajorVersion,
                 osvi.dwMinorVersion,
                 osvi.dwBuildNumber,
                 osvi.szCSDVersion);
         break;
      default:
         // Unknown OS
         fprintf(hf, "Unknown Win32 platform %u.%u (Build %u) %s",
                 osvi.dwMajorVersion,
                 osvi.dwMinorVersion,
                 osvi.dwBuildNumber,
                 osvi.szCSDVersion);
         break;
   }
   fprintf(hf, "\n");


   SYSTEM_INFO si;
   GetSystemInfo(&si);

   switch( si.wProcessorArchitecture )
   {
      case PROCESSOR_ARCHITECTURE_INTEL:
         switch( si.wProcessorLevel )
         {
            case 3:     // 80386
               fprintf(hf,  "Intel 80386 step %d processor",
                       LOBYTE(si.wProcessorRevision));
               break;
            case 4:     // 80486
               fprintf(hf,  "Intel 80486 step %d processor",
                       LOBYTE(si.wProcessorRevision));
               break;
            case 5:     // Pentium
               fprintf(hf, "Intel Pentium model %d, stepping %d processor",
                       HIBYTE(si.wProcessorRevision),
                       LOBYTE(si.wProcessorRevision));
               break;
            case 6:     // Pentium II
               fprintf(hf, "Intel Pentium II model %d, stepping %d processor",
                       HIBYTE(si.wProcessorRevision),
                       LOBYTE(si.wProcessorRevision));
               break;
            case 7:     // Pentium III
               fprintf(hf, "Intel Pentium III model %d, stepping %d processor",
                       HIBYTE(si.wProcessorRevision),
                       LOBYTE(si.wProcessorRevision));
               break;
            case 8:     // Pentium IV
               fprintf(hf, "Intel Pentium II model %d, stepping %d processor",
                       HIBYTE(si.wProcessorRevision),
                       LOBYTE(si.wProcessorRevision));
               break;
            default:
               fprintf(hf, "Unknown Intel processor: %u", si.wProcessorLevel );
               break;
         }
         break;
      default:
         // we only support the intel architecture ... any other value is BAD
         fprintf(hf, "Invalid chip architecture");
         break;
   }
   fputs( "\n\n", hf );
   fflush(hf);
   return;
}


const char* const REGKEY_PRODUCT_OPTIONS = "SYSTEM\\CurrentControlSet\\Control\\ProductOptions";

static NTTYPE getNTVersion( void )
{
   char szValue[256];
   DWORD dwType = 0;
   DWORD dwSize = sizeof (szValue);
   HKEY hKey   = NULL;
   LONG lStatus;

   lStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                          REGKEY_PRODUCT_OPTIONS,
                          0,
                          KEY_QUERY_VALUE,
                          &hKey);
   if( ERROR_SUCCESS != lStatus )
   {
      // Windows NT
      return(typeDefault);
   }

   lStatus = RegQueryValueEx(hKey, TEXT("ProductType"),
                             NULL, &dwType, (LPBYTE)szValue, &dwSize);
   RegCloseKey(hKey) ;
   if( ERROR_SUCCESS != lStatus )
   {
      // Windows NT
      return(typeDefault);
   }

   if( stricmp("WINNT", szValue) == 0 )
   {
      return(typeWorkstation);         // Windows NT Workstation
   }
   else if( 0 == stricmp("SERVERNT", szValue) )
   {
      return(typeServer);             // Windows NT Server
   }
   else if( 0 == stricmp("LANMANNT", szValue) )
   {
      return(typeAdvancedServer);     // Windows NT Advanced Server (3.1)
   }

   return(typeDefault);               // Windows NT
}// GetNTVersion()

//CP20040223static void logKlingonLogo( FILE* pLogFile )
//CP20040223{
//CP20040223   fputs( "                |\n", pLogFile );
//CP20040223   fputs( "              |\n", pLogFile );
//CP20040223   fputs( "              |\n", pLogFile );
//CP20040223   fputs( "             ' `\n", pLogFile );
//CP20040223   fputs( "             | |\n", pLogFile );
//CP20040223   fputs( "             | |\n", pLogFile );
//CP20040223   fputs( "            '   ` \n", pLogFile );
//CP20040223   fputs( "         .-'|   |`-.\n", pLogFile );
//CP20040223   fputs( "        /  /     \\  \\ \n", pLogFile );
//CP20040223   fputs( "       |__,\\     /   |\n", pLogFile );
//CP20040223   fputs( "      -'   \\\\   //\\_ |\n", pLogFile );
//CP20040223   fputs( "   ,-'   ___\\\\.//   `-__\n", pLogFile );
//CP20040223   fputs( "  /__,--'       `--.____--\n", pLogFile );
//CP20040223   fputs( "         `-._____.-'\n", pLogFile );
//CP20040223   fputs( "\n", pLogFile );
//CP20040223}

static void logIFDSLogo( FILE* pLogFile )
{
   
}
