#include "stdafx.h"

#include <stdio.h>
#include <dbghelp.h>
#include <bfutil/seh_exception.hpp>
#include <ifdscore/exechist.hpp>
#include <bfutil/bfguard.hpp>
#include "ExceptionReport.hpp"

#pragma comment(linker, "/defaultlib:dbghelp.lib")

// Declare global instance of class
//#ifdef BFRELSYM
ExceptionReport g_ExceptionReport;
//#endif

__declspec( thread ) bool t_bReportingException = false;
__declspec( thread ) char t_szLogFileName[MAX_PATH] = {0};
__declspec( thread ) FILE* t_pfReport = NULL;

static char s_szLogFileDir[MAX_PATH] = ".";

const char* ExceptionReport::getLogFileDir()
{
   return s_szLogFileDir;
}

void ExceptionReport::setLogFileDir( const DString& strLogFileDir ) {
   DStringA astr( strLogFileDir );
   strcpy( s_szLogFileDir, astr.c_str() );
}

void XlateFunction(unsigned int u, LPEXCEPTION_POINTERS pXP)
{
   // do some pre-processing here (like ... call ReportException() !)
   if ( g_ExceptionReport.unhandledExceptionFilter(pXP) == EXCEPTION_EXECUTE_HANDLER )
   {
      throw( SEH_Exception( pXP->ExceptionRecord->ExceptionCode, g_ExceptionReport.getLogFileName() ) );
   }
   // if we don't throw an exception it is equivalent to continuing the
   // search (i.e. EXCEPTION_CONTINUE_SEARCH)
}

static void __stdcall defaultFileNameGeneratorFunction( char* pszBuf, unsigned int cb )
{
   char* pszComputerName = getenv( "COMPUTERNAME" );
   char* pszUserName = getenv( "USERNAME" );



   SYSTEMTIME st;
   GetSystemTime( &st );
   _snprintf( pszBuf, cb, "%s\\%s_%s_%04d%02d%02d_%02d%02d%02d.%03d_%04x.log",
              ExceptionReport::getLogFileDir(),
              pszComputerName,
              pszUserName,
              st.wYear,
              st.wMonth,
              st.wDay,
              st.wHour,
              st.wMinute,
              st.wSecond,
              st.wMilliseconds,
              GetCurrentThreadId() );
   return;
}

ExceptionReport::PFNGF ExceptionReport::setFileGenerator( PFNGF pfngf ) {
   PFNGF old = s_pFNGF_;
   s_pFNGF_ = pfngf;
   return( old );
}

LPTOP_LEVEL_EXCEPTION_FILTER ExceptionReport::s_previousFilter_;

ExceptionReport::PFNGF ExceptionReport::s_pFNGF_ = defaultFileNameGeneratorFunction;

HANDLE ExceptionReport::s_hProcess_;

bool ExceptionReport::s_bEnableReporting_ = false;
BFCritSec ExceptionReport::s_csEnableReporting_;

const char* ExceptionReport::getLogFileName() {
   return t_szLogFileName;
}

ExceptionReport::ExceptionReport( )   // Constructor
{
#pragma warning( disable: 4535 )
   _set_se_translator( XlateFunction );
   setGlobalSeTranslator( XlateFunction );   // set it for all threads which will be started.

   // Install the unhandled exception filter function
   s_previousFilter_ = SetUnhandledExceptionFilter(unhandledExceptionFilter);
   s_hProcess_ = GetCurrentProcess();
}

ExceptionReport::~ExceptionReport( )
{
   SetUnhandledExceptionFilter( s_previousFilter_ );
}

//******************************************************************************
bool ExceptionReport::isEnabled()
{
//#if !defined( BFRELSYM )
//   // if not a Symbols build then exception reporting is never enabled
//   return( false );
//#else
   if ( IsDebuggerPresent() )
   {
      return false;
   }

   BFGuard g( s_csEnableReporting_ );
   return s_bEnableReporting_;
//#endif
}

//******************************************************************************
void ExceptionReport::enable( bool b ) 
{
   BFGuard g( s_csEnableReporting_ );
   s_bEnableReporting_ = b;
}

//******************************************************************************
LONG WINAPI ExceptionReport::unhandledExceptionFilter( PEXCEPTION_POINTERS pXP )
{
   // Don't report on nested exceptions
   if ( true == t_bReportingException )
   {
      return(EXCEPTION_CONTINUE_SEARCH);
   }

   switch ( pXP->ExceptionRecord->ExceptionCode )
   {
      case EXCEPTION_BREAKPOINT:
      case EXCEPTION_DATATYPE_MISALIGNMENT:
      case EXCEPTION_IN_PAGE_ERROR:
      case EXCEPTION_GUARD_PAGE:
      case EXCEPTION_SINGLE_STEP:
         // don't report for 'common' exceptions which are handled by the OS
         return(EXCEPTION_CONTINUE_SEARCH);
   }
   if ( false == ExceptionReport::isEnabled() ) {
      // don't report if exception reporting is disabled
      return(EXCEPTION_CONTINUE_SEARCH);
   }

   t_bReportingException = true;

   (*s_pFNGF_)(t_szLogFileName, sizeof( t_szLogFileName ) / sizeof( t_szLogFileName[0]) );

   t_pfReport = fopen( t_szLogFileName, "w" );
   if( NULL != t_pfReport ) {
      generateExceptionReport( pXP );
      fclose( t_pfReport );
      {
         static char* buffer;
         HGLOBAL clipbuffer;
         OpenClipboard(NULL);
         EmptyClipboard();
         DWORD dw = strlen(t_szLogFileName) + 1;
         clipbuffer = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, dw * sizeof(char));
         buffer = (char *)GlobalLock(clipbuffer);
         strcpy(buffer, t_szLogFileName);
         GlobalUnlock(clipbuffer);
         SetClipboardData(CF_TEXT,clipbuffer);
         CloseClipboard();
      }
      DStringA msg = "iFAST/Desktop has encountered a fatal error and will shutdown.\r\n";
      msg += "An exception report file named ";
      msg += t_szLogFileName;
      msg += " has been generated.\r\n";
      msg += "The name of the file is in the clipboard and can be pasted into an e-mail or other report.\r\n";
      msg += "Please report this to the Service Desk.\r\n";
      msg += "\r\niFAST/Desktop will close after you click Ok.\r\n";
      MessageBox(HWND_DESKTOP, DString(msg).c_str(),I_("iFAST/Desktop Internal Error"), MB_ICONSTOP | MB_OK );
      t_pfReport = NULL;
      //abort();
      // if there is mail to technical support functionality enable
      // some code which send mail about detail would be around here
      exit(4);
   }

   t_bReportingException = false;


   if ( s_previousFilter_ ) {
      return s_previousFilter_( pXP );
   } 
   else {
      return EXCEPTION_CONTINUE_SEARCH;
   }
}

DWORD ExceptionReport::generateExceptionReport( PEXCEPTION_POINTERS pXI )
{
   _tprintf( "Exception Trace\n" );

   PEXCEPTION_RECORD pXR = pXI->ExceptionRecord;

   // First print information about the type of fault
   _tprintf(   "Exception code: %08X %s\n",
               pXR->ExceptionCode,
               getExceptionString(pXR->ExceptionCode) );

   // Now print information about where the fault occured
   char szFaultingModule[MAX_PATH];
   DWORD section, offset;
   getLogicalAddress(  pXR->ExceptionAddress,
                       szFaultingModule,
                       sizeof( szFaultingModule ),
                       section, offset );

   _tprintf( "Fault address:  %08X %02X:%08X %s\n",
             pXR->ExceptionAddress,
             section, offset, szFaultingModule );

   PCONTEXT pCtx = pXI->ContextRecord;

   logMachineConfiguration();
   logRegisters( *pCtx );

   ExecutionHistory::dump( t_pfReport );

   SymSetOptions( SYMOPT_DEFERRED_LOADS );

   // Initialize DbgHelp
   if ( !SymInitialize( GetCurrentProcess(), 0, TRUE ) ) {
      _tprintf("\nFailed to Initialize Symbols\n");
      fflush( t_pfReport );
      return( EXCEPTION_EXECUTE_HANDLER );
   }

   CONTEXT trashableContext = *pCtx;
   writeStackDetails( &trashableContext, false );

#ifdef _M_IX86  // X86 Only!

   _tprintf( "========================\n" );
   _tprintf( "Local Variables And Parameters\n" );

   trashableContext = *pCtx;
   writeStackDetails( &trashableContext, true );
   #if 0
   // This is HUUUUUUUUUUUUGE because so much is global, so we'll cut it out for now
   _tprintf( "========================\n" );
   _tprintf( "Global Variables\n" );

   SymEnumSymbols( GetCurrentProcess(),
                   (DWORD64)GetModuleHandleA(szFaultingModule),
                   0, enumerateSymbolsCallback, 0 );
   #endif
#endif      // X86 Only!

   SymCleanup( GetCurrentProcess() );

   _tprintf( "\n" );
   return( EXCEPTION_EXECUTE_HANDLER );
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
void ExceptionReport::logStackDump( DWORD frame )
{
   DWORD   iStackDumpRow;
   DWORD   iStackDumpByte;
   BYTE    abStack[1024];

   memset( abStack, 0, sizeof(abStack) );

   if( frame > 0x20 ) {
      // back up the stack frame so that we can dump the arguments to the function also
      frame -= 0x20;
   }

   if( !::ReadProcessMemory( s_hProcess_, 
                             (const void*)frame,
                             (LPVOID)&abStack[0], 
                             (DWORD)sizeof(abStack), 
                             &iStackDumpRow) ) {
      return;
   }

   for( iStackDumpRow = 0; iStackDumpRow < 20; ++iStackDumpRow ) {
      iStackDumpByte = iStackDumpRow * 16;
      _tprintf( "    %08x  %02x %02x %02x %02x %02x %02x %02x %02x - %02x %02x %02x %02x %02x %02x %02x %02x  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
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
         fflush( t_pfReport );
   }

   _tprintf( "\n" );
   fflush( t_pfReport );
   return;
}// LogStackDump()

void ExceptionReport::logRegisters( const CONTEXT& c )
{
   DWORD dwFlags;
   int iFlags;

   _tprintf( "\n" );
   _tprintf( "--------------------------------\n" );
   _tprintf( "--- i86 Register Information ---\n" );
   _tprintf( "--------------------------------\n" );

   if( (c.ContextFlags) & CONTEXT_SEGMENTS ) {
      // Segment registers
      _tprintf( "DS  : %4.4lX     ", c.SegDs);
      _tprintf( "ES  : %4.4lX     ", c.SegEs);
      _tprintf( "FS  : %4.4lX     ", c.SegFs);
      _tprintf( "GS  : %4.4lX\n",  c.SegGs);
   }
   if( (c.ContextFlags) & CONTEXT_INTEGER ) {
      // Integer registers
      _tprintf( "EAX : %8.8lX ",     c.Eax);
      _tprintf( "EBX : %8.8lX ",     c.Ebx);
      _tprintf( "ECX : %8.8lX ",     c.Ecx);
      _tprintf( "EDX : %8.8lX\n",  c.Edx);
      _tprintf( "EDI : %8.8lX ",     c.Edi);
      _tprintf( "ESI : %8.8lX\n",  c.Esi);
   }
   if( (c.ContextFlags) & CONTEXT_CONTROL ) {
      // control registers
      _tprintf( "EBP : %8.8lX ",     c.Ebp);
      _tprintf( "EIP : %8.8lX ",     c.Eip);
      _tprintf( "ESP : %8.8lX\n",  c.Esp);
      _tprintf( "CS  : %4.4lX     ", c.SegCs);
      _tprintf( "SS  : %4.4lX\n",  c.SegSs);

      // convert the flags to a bit array and log it
      dwFlags = c.EFlags;
      _tprintf( "EFLG: " );

      for( iFlags = 0; iFlags < (sizeof(dwFlags) * 8); iFlags++, dwFlags <<= 1 ) {
         if( iFlags % 4 == 0 && iFlags != 0 ) {
            _tprintf( " %1u", (dwFlags & 0x80000000) == 0x80000000);
         }
         else {
            _tprintf( "%1u", (dwFlags & 0x80000000) == 0x80000000);
         }
      }
   }

   _tprintf( "\n\n" );
   return;
}// logRegisters()


void ExceptionReport::logMachineConfiguration()
{
   OSVERSIONINFO osvi;

   osvi.dwOSVersionInfoSize = sizeof(osvi);
   GetVersionEx(&osvi);

   // Dump out windows version and processor information
   switch( osvi.dwPlatformId ) {
      case VER_PLATFORM_WIN32_NT:
         switch( getNTVersion() ) {
            case typeWorkstation:
               _tprintf( "Microsoft Windows NT Workstation %u.%u (Build %u) %s",
                       osvi.dwMajorVersion,
                       osvi.dwMinorVersion,
                       osvi.dwBuildNumber,
                       osvi.szCSDVersion);
               break;
            case typeServer:
               _tprintf( "Microsoft Windows NT Server %u.%u (Build %u) %s",
                       osvi.dwMajorVersion,
                       osvi.dwMinorVersion,
                       osvi.dwBuildNumber,
                       osvi.szCSDVersion);
               break;
            case typeAdvancedServer:
               _tprintf( "Microsoft Windows NT Advanced Server %u.%u (Build %u) %s",
                       osvi.dwMajorVersion,
                       osvi.dwMinorVersion,
                       osvi.dwBuildNumber,
                       osvi.szCSDVersion);
               break;
            default:
               _tprintf( "Microsoft Windows NT %u.%u (Build %u) %s",
                       osvi.dwMajorVersion,
                       osvi.dwMinorVersion,
                       osvi.dwBuildNumber,
                       osvi.szCSDVersion);
               break;
         }
         break;
      case VER_PLATFORM_WIN32_WINDOWS:  // i.e. Win95
         _tprintf( "Microsoft Windows 95 %u.%u (Build %u) %s",
                 osvi.dwMajorVersion,
                 osvi.dwMinorVersion,
                 osvi.dwBuildNumber,
                 osvi.szCSDVersion);
         break;
      default:
         // Unknown OS
         _tprintf( "Unknown Win32 platform %u.%u (Build %u) %s",
                 osvi.dwMajorVersion,
                 osvi.dwMinorVersion,
                 osvi.dwBuildNumber,
                 osvi.szCSDVersion);
         break;
   }
   _tprintf( "\n");


   SYSTEM_INFO si;
   GetSystemInfo(&si);

   switch( si.wProcessorArchitecture ) {
      case PROCESSOR_ARCHITECTURE_INTEL:
         switch( si.wProcessorLevel ) {
            case 3:     // 80386
               _tprintf(  "Intel 80386 step %d processor",
                       LOBYTE(si.wProcessorRevision));
               break;
            case 4:     // 80486
               _tprintf(  "Intel 80486 step %d processor",
                       LOBYTE(si.wProcessorRevision));
               break;
            case 5:     // Pentium
               _tprintf( "Intel Pentium model %d, stepping %d processor",
                       HIBYTE(si.wProcessorRevision),
                       LOBYTE(si.wProcessorRevision));
               break;
            case 6:     // Pentium II
               _tprintf( "Intel Pentium II model %d, stepping %d processor",
                       HIBYTE(si.wProcessorRevision),
                       LOBYTE(si.wProcessorRevision));
               break;
            case 7:     // Pentium III
               _tprintf( "Intel Pentium III model %d, stepping %d processor",
                       HIBYTE(si.wProcessorRevision),
                       LOBYTE(si.wProcessorRevision));
               break;
            case 8:     // Pentium IV
               _tprintf( "Intel Pentium IV model %d, stepping %d processor",
                       HIBYTE(si.wProcessorRevision),
                       LOBYTE(si.wProcessorRevision));
               break;
            default:
               _tprintf( "Unknown Intel processor: %u", si.wProcessorLevel );
               break;
         }
         break;
      default:
         // we only support the intel architecture ... any other value is BAD
         _tprintf( "Invalid chip architecture");
         break;
   }
   _tprintf( "\n\n" );
   return;
}

const char* const REGKEY_PRODUCT_OPTIONS = "SYSTEM\\CurrentControlSet\\Control\\ProductOptions";

ExceptionReport::NTTYPE ExceptionReport::getNTVersion( void )
{
   char szValue[256];
   DWORD dwType = 0;
   DWORD dwSize = sizeof (szValue);
   HKEY hKey   = NULL;
   LONG lStatus;

   lStatus = RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                           REGKEY_PRODUCT_OPTIONS,
                           0,
                           KEY_QUERY_VALUE,
                           &hKey);
   if( ERROR_SUCCESS != lStatus ) {
      // Windows NT
      return(typeDefault);
   }

   lStatus = RegQueryValueEx(hKey, TEXT("ProductType"),
                             NULL, &dwType, (LPBYTE)szValue, &dwSize);
   RegCloseKey(hKey) ;
   if( ERROR_SUCCESS != lStatus ) {
      // Windows NT
      return(typeDefault);
   }

   if( stricmp("WINNT", szValue) == 0 ) {
      return(typeWorkstation);         // Windows NT Workstation
   }
   else if( 0 == stricmp("SERVERNT", szValue) ) {
      return(typeServer);             // Windows NT Server
   }
   else if( 0 == stricmp("LANMANNT", szValue) ) {
      return(typeAdvancedServer);     // Windows NT Advanced Server (3.1)
   }

   return(typeDefault);               // Windows NT
}// GetNTVersion()

const char* ExceptionReport::getExceptionString( DWORD dwCode )
{
#define EXCEPTION( x ) case EXCEPTION_##x: return #x;

   switch ( dwCode ) {
      EXCEPTION( ACCESS_VIOLATION )
      EXCEPTION( DATATYPE_MISALIGNMENT )
      EXCEPTION( BREAKPOINT )
      EXCEPTION( SINGLE_STEP )
      EXCEPTION( ARRAY_BOUNDS_EXCEEDED )
      EXCEPTION( FLT_DENORMAL_OPERAND )
      EXCEPTION( FLT_DIVIDE_BY_ZERO )
      EXCEPTION( FLT_INEXACT_RESULT )
      EXCEPTION( FLT_INVALID_OPERATION )
      EXCEPTION( FLT_OVERFLOW )
      EXCEPTION( FLT_STACK_CHECK )
      EXCEPTION( FLT_UNDERFLOW )
      EXCEPTION( INT_DIVIDE_BY_ZERO )
      EXCEPTION( INT_OVERFLOW )
      EXCEPTION( PRIV_INSTRUCTION )
      EXCEPTION( IN_PAGE_ERROR )
      EXCEPTION( ILLEGAL_INSTRUCTION )
      EXCEPTION( NONCONTINUABLE_EXCEPTION )
      EXCEPTION( STACK_OVERFLOW )
      EXCEPTION( INVALID_DISPOSITION )
      EXCEPTION( GUARD_PAGE )
      EXCEPTION( INVALID_HANDLE )
   }

   // If not one of the "known" exceptions, try to get the string
   // from NTDLL.DLL's message table.

   static char szBuffer[512] = { 0};

   FormatMessageA( FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE,
                   GetModuleHandleA( "NTDLL.DLL" ),
                   dwCode, 0, szBuffer, sizeof( szBuffer ), 0 );

   return szBuffer;
}

//=============================================================================
// Given a linear address, locates the module, section, and offset containing  
// that address.                                                               
//                                                                             
// Note: the szModule paramater buffer is an output buffer of length specified 
// by the len parameter (in characters!)                                       
//=============================================================================
bool ExceptionReport::getLogicalAddress( PVOID addr, 
                                         char* szModule, 
                                         DWORD len, 
                                         DWORD& section, 
                                         DWORD& offset )
{
   MEMORY_BASIC_INFORMATION mbi;

   if ( !VirtualQuery( addr, &mbi, sizeof(mbi) ) ) {
      return( false );
   }

//   fprintf(t_pfReport, " gLA1 " ); fflush(t_pfReport);
   DWORD hMod = (DWORD)mbi.AllocationBase;

   if ( NULL == hMod || !GetModuleFileNameA( (HMODULE)hMod, szModule, len ) ) {
      return( false );
   }

   // Point to the DOS header in memory
   PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)hMod;

   // From the DOS header, find the NT (PE) header
   PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)(hMod + pDosHdr->e_lfanew);
   PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION( pNtHdr );

   DWORD rva = (DWORD)addr - hMod; // RVA is offset from module load address

   // Iterate through the section table, looking for the one that encompasses
   // the linear address.
   for (   unsigned i = 0;
       i < pNtHdr->FileHeader.NumberOfSections;
       i++, pSection++ ) {
      DWORD sectionStart = pSection->VirtualAddress;
      DWORD sectionEnd = sectionStart
                         + max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);

      // Is the address in this section???
      if ( (rva >= sectionStart) && (rva <= sectionEnd) ) {
         // Yes, address is in the section.  Calculate section and offset,
         // and store in the "section" & "offset" params, which were
         // passed by reference.
         section = i+1;
         offset = rva - sectionStart;
         return( true );
      }
   }

   return( false );
}

//============================================================
// Walks the stack, and writes the results to the report file 
//============================================================
void ExceptionReport::writeStackDetails( PCONTEXT pContext, 
                                         bool bWriteVariables )  // true if local/params should be output
{
   _tprintf( "\nCall stack:\n" );

   _tprintf( "Address   Frame     Function            SourceFile\n" );
   fflush( t_pfReport );

   DWORD dwMachineType = 0;
   // Could use SymSetOptions here to add the SYMOPT_DEFERRED_LOADS flag

   STACKFRAME sf;
   memset( &sf, 0, sizeof(sf) );

#ifdef _M_IX86
   // Initialize the STACKFRAME structure for the first call.  This is only
   // necessary for Intel CPUs, and isn't mentioned in the documentation.
   sf.AddrPC.Offset       = pContext->Eip;
   sf.AddrPC.Mode         = AddrModeFlat;
   sf.AddrStack.Offset    = pContext->Esp;
   sf.AddrStack.Mode      = AddrModeFlat;
   sf.AddrFrame.Offset    = pContext->Ebp;
   sf.AddrFrame.Mode      = AddrModeFlat;

   dwMachineType = IMAGE_FILE_MACHINE_I386;
#endif

   while ( 1 ) {
      // Get the next stack frame
      if ( ! StackWalk(  dwMachineType,
                         s_hProcess_,
                         GetCurrentThread(),
                         &sf,
                         pContext,
                         0,
                         SymFunctionTableAccess,
                         SymGetModuleBase,
                         0 ) )
         break;

      if ( 0 == sf.AddrFrame.Offset ) // Basic sanity check to make sure
         break;                      // the frame is OK.  Bail if not.

      _tprintf( "%08X  %08X  ", sf.AddrPC.Offset, sf.AddrFrame.Offset );
      fflush( t_pfReport );

      // Get the name of the function for this stack frame entry
      BYTE symbolBuffer[ sizeof(SYMBOL_INFO) + 1024 ];
      PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)symbolBuffer;
      pSymbol->SizeOfStruct = sizeof(symbolBuffer);
      pSymbol->MaxNameLen = 1024;

      DWORD64 symDisplacement = 0;    // Displacement of the input address,
                                      // relative to the start of the symbol

//      _tprintf("Boogens "); fflush( t_pfReport );
      if ( SymFromAddr(s_hProcess_,sf.AddrPC.Offset,&symDisplacement,pSymbol)) {
         _tprintf( "%hs+%I64X", pSymbol->Name, symDisplacement );
         fflush( t_pfReport );

      } 
      else {  // No symbol found.  Print out the logical address instead.
//         _tprintf("There's nobody home "); fflush( t_pfReport );
         char szModule[MAX_PATH] = "";
         DWORD section = 0, offset = 0;

         getLogicalAddress(  (PVOID)sf.AddrPC.Offset,
                             szModule, sizeof(szModule), section, offset );

//         _tprintf("A Bridge Too Far "); fflush( t_pfReport );
         _tprintf( "%04X:%08X %s", section, offset, szModule );
         fflush( t_pfReport );
      }

//      _tprintf("The Great Escape "); fflush( t_pfReport );
      // Get the source line for this stack frame entry
      IMAGEHLP_LINE lineInfo = { sizeof(IMAGEHLP_LINE)};
      DWORD dwLineDisplacement;
      if ( SymGetLineFromAddr( s_hProcess_, sf.AddrPC.Offset,
                               &dwLineDisplacement, &lineInfo ) ) {
         _tprintf( "  %s line %u",lineInfo.FileName,lineInfo.LineNumber); 
         fflush( t_pfReport );
      }

      _tprintf( "\n" );
      fflush( t_pfReport );

      // Write out the variables, if desired
      if ( bWriteVariables ) {
         // Use SymSetContext to get just the locals/params for this frame
         IMAGEHLP_STACK_FRAME imagehlpStackFrame;
         imagehlpStackFrame.InstructionOffset = sf.AddrPC.Offset;
         SymSetContext( s_hProcess_, &imagehlpStackFrame, 0 );

         // Enumerate the locals/parameters
         SymEnumSymbols( s_hProcess_, 0, 0, enumerateSymbolsCallback, &sf );

         _tprintf( "\n" );
         fflush( t_pfReport );

         logStackDump( sf.AddrFrame.Offset );

      }
   }
}

//////////////////////////////////////////////////////////////////////////////
// The function invoked by SymEnumSymbols
//////////////////////////////////////////////////////////////////////////////

BOOL CALLBACK
ExceptionReport::enumerateSymbolsCallback(
                                         PSYMBOL_INFO  pSymInfo,
                                         ULONG         SymbolSize,
                                         PVOID         UserContext )
{

   char szBuffer[2048];

   __try
   {
      if ( formatSymbolValue( pSymInfo, (STACKFRAME*)UserContext,
                              szBuffer, sizeof(szBuffer) ) )
         _tprintf( "\t%s\n", szBuffer );
   }
   __except( 1 )
   {
      _tprintf( "Ignoring symbol %s\n", pSymInfo->Name );
   }

   return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// Given a SYMBOL_INFO representing a particular variable, displays its
// contents.  If it's a user defined type, display the members and their
// values.
//////////////////////////////////////////////////////////////////////////////
bool ExceptionReport::formatSymbolValue(
                                       PSYMBOL_INFO pSym,
                                       STACKFRAME * sf,
                                       char * pszBuffer,
                                       unsigned cbBuffer )
{
   char * pszCurrBuffer = pszBuffer;

   // Indicate if the variable is a local or parameter
   if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_PARAMETER ) {
      pszCurrBuffer += sprintf( pszCurrBuffer, "Parameter " );
   } 
   else if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_LOCAL ) {
      pszCurrBuffer += sprintf( pszCurrBuffer, "Local " );
   }

   // If it's a function, don't do anything.
   if ( pSym->Tag == 5 ) {  // SymTagFunction from CVCONST.H from the DIA SDK
      return( false );
   }

   // Emit the variable name
   pszCurrBuffer += sprintf( pszCurrBuffer, "\'%s\'", pSym->Name );

   DWORD_PTR pVariable = 0;    // Will point to the variable's data in memory

   if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_REGRELATIVE ) {
      pVariable = sf->AddrFrame.Offset;
      pVariable += (DWORD_PTR)pSym->Address;
   } 
   else if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_REGISTER ) {
      return( false );   // Don't try to report register variable
   } 
   else {
      pVariable = (DWORD_PTR)pSym->Address;   // It must be a global variable
   }

   // Determine if the variable is a user defined type (UDT).  IF so, bHandled
   // will return true.
   bool bHandled = false;
#if 0
// May cause infinite loop with boost!!!
   pszCurrBuffer = dumpTypeIndex(pszCurrBuffer,pSym->ModBase, pSym->TypeIndex,
                                 0, pVariable, bHandled );
#endif
   if ( !bHandled ) {
      // The symbol wasn't a UDT, so do basic, stupid formatting of the
      // variable.  Based on the size, we're assuming it's a char, WORD, or
      // DWORD.
      BasicType basicType = getBasicType( pSym->TypeIndex, pSym->ModBase );

      pszCurrBuffer = formatOutputValue(pszCurrBuffer, basicType, pSym->Size,
                                        (PVOID)pVariable ); 
   }


   return true;
}

//////////////////////////////////////////////////////////////////////////////
// If it's a user defined type (UDT), recurse through its members until we're
// at fundamental types.  When he hit fundamental types, return
// bHandled = false, so that FormatSymbolValue() will format them.
//////////////////////////////////////////////////////////////////////////////
char* ExceptionReport::dumpTypeIndex(
                                    char * pszCurrBuffer,
                                    DWORD64 modBase,
                                    DWORD dwTypeIndex,
                                    unsigned nestingLevel,
                                    DWORD_PTR offset,
                                    bool & bHandled )
{
   bHandled = false;

   // Get the name of the symbol.  This will either be a Type name (if a UDT),
   // or the structure member name.
   WCHAR * pwszTypeName;
   if ( SymGetTypeInfo( s_hProcess_, modBase, dwTypeIndex, TI_GET_SYMNAME,
                        &pwszTypeName ) ) {
      pszCurrBuffer += sprintf( pszCurrBuffer, " %ls", pwszTypeName );
      LocalFree( pwszTypeName );
   }

   // Determine how many children this type has.
   DWORD dwChildrenCount = 0;
   SymGetTypeInfo( s_hProcess_, modBase, dwTypeIndex, TI_GET_CHILDRENCOUNT,
                   &dwChildrenCount );

   if ( !dwChildrenCount )     // If no children, we're done
      return pszCurrBuffer;

   // Prepare to get an array of "TypeIds", representing each of the children.
   // SymGetTypeInfo(TI_FINDCHILDREN) expects more memory than just a
   // TI_FINDCHILDREN_PARAMS struct has.  Use derivation to accomplish this.
   struct FINDCHILDREN : TI_FINDCHILDREN_PARAMS
   {
      ULONG   MoreChildIds[1024];
      FINDCHILDREN(){Count = sizeof(MoreChildIds) / sizeof(MoreChildIds[0]);}
   } children;

   children.Count = dwChildrenCount;
   children.Start= 0;

   // Get the array of TypeIds, one for each child type
   if ( !SymGetTypeInfo( s_hProcess_, modBase, dwTypeIndex, TI_FINDCHILDREN,
                         &children ) ) {
      return pszCurrBuffer;
   }

   // Append a line feed
   pszCurrBuffer += sprintf( pszCurrBuffer, "\n" );

   // Iterate through each of the children
   for ( unsigned i = 0; i < dwChildrenCount; i++ ) {
      // Add appropriate indentation level (since this routine is recursive)
      for ( unsigned j = 0; j <= nestingLevel+1; j++ )
         pszCurrBuffer += sprintf( pszCurrBuffer, "\t" );

      // Recurse for each of the child types
      bool bHandled2;
      pszCurrBuffer = dumpTypeIndex( pszCurrBuffer, modBase,
                                     children.ChildId[i], nestingLevel+1,
                                     offset, bHandled2 );

      // If the child wasn't a UDT, format it appropriately
      if ( !bHandled2 ) {
         // Get the offset of the child member, relative to its parent
         DWORD dwMemberOffset;
         SymGetTypeInfo( s_hProcess_, modBase, children.ChildId[i],
                         TI_GET_OFFSET, &dwMemberOffset );

         // Get the real "TypeId" of the child.  We need this for the
         // SymGetTypeInfo( TI_GET_TYPEID ) call below.
         DWORD typeId;
         SymGetTypeInfo( s_hProcess_, modBase, children.ChildId[i],
                         TI_GET_TYPEID, &typeId );

         // Get the size of the child member
         ULONG64 length;
         SymGetTypeInfo(s_hProcess_, modBase, typeId, TI_GET_LENGTH,&length);

         // Calculate the address of the member
         DWORD_PTR dwFinalOffset = offset + dwMemberOffset;

         BasicType basicType = getBasicType(children.ChildId[i], modBase );

         pszCurrBuffer = formatOutputValue( pszCurrBuffer, basicType,
                                            length, (PVOID)dwFinalOffset ); 

         pszCurrBuffer += sprintf( pszCurrBuffer, "\n" );
      }
   }

   bHandled = true;
   return pszCurrBuffer;
}

char* ExceptionReport::formatOutputValue(   char * pszCurrBuffer,
                                            BasicType basicType,
                                            DWORD64 length,
                                            PVOID pAddress )
{
   // Format appropriately (assuming it's a 1, 2, or 4 bytes (!!!)
   if ( length == 1 ) {
      pszCurrBuffer += sprintf( pszCurrBuffer, " = %X", *(PBYTE)pAddress );
   } 
   else if ( length == 2 ) {
      pszCurrBuffer += sprintf( pszCurrBuffer, " = %X", *(PWORD)pAddress );
   } 
   else if ( length == 4 ) {
      if ( basicType == btFloat ) {
         pszCurrBuffer += sprintf(pszCurrBuffer," = %f", *(PFLOAT)pAddress);
      } 
	  else if ( basicType == btChar ) {
         if ( !IsBadStringPtrA( (const char*)pAddress, 32) ) {
            pszCurrBuffer += sprintf( pszCurrBuffer, " = \"%.31s\"",
                                      *(PDWORD)pAddress );
         } 
		 else {
            pszCurrBuffer += sprintf( pszCurrBuffer, " = %X",
                                      *(PDWORD)pAddress );
         }
      } 
	  else {
         pszCurrBuffer += sprintf(pszCurrBuffer," = %X", *(PDWORD)pAddress);
      }
   } 
   else if ( length == 8 ) {
      if ( basicType == btFloat ) {
         pszCurrBuffer += sprintf( pszCurrBuffer, " = %lf",
                                   *(double *)pAddress );
      } 
	  else {
         pszCurrBuffer += sprintf( pszCurrBuffer, " = %I64X",
                                   *(DWORD64*)pAddress );
      }
   }

   return pszCurrBuffer;
}

BasicType
ExceptionReport::getBasicType( DWORD typeIndex, DWORD64 modBase )
{
   BasicType basicType;
   if ( SymGetTypeInfo( s_hProcess_, modBase, typeIndex,
                        TI_GET_BASETYPE, &basicType ) ) {
      return basicType;
   }

   // Get the real "TypeId" of the child.  We need this for the
   // SymGetTypeInfo( TI_GET_TYPEID ) call below.
   DWORD typeId;
   if (SymGetTypeInfo(s_hProcess_,modBase, typeIndex, TI_GET_TYPEID, &typeId)) {
      if ( SymGetTypeInfo( s_hProcess_, modBase, typeId, TI_GET_BASETYPE,
                           &basicType ) ) {
         return basicType;
      }
   }

   return btNoType;
}

//============================================================================
// Helper function that writes to the report file, and allows the user to use 
// printf style formating                                                     
//============================================================================
int __cdecl ExceptionReport::_tprintf(const char* pszMask, ...)
{
   char szBuf[1024];
   int retValue;
   va_list argptr;

   va_start( argptr, pszMask );
   retValue = _vsnprintf( szBuf, sizeof( szBuf ) / sizeof( szBuf[0] ), pszMask, argptr );
   va_end( argptr );

   fputs( szBuf, t_pfReport );

   return retValue;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastgui/ExceptionReport.cpp-arc  $
// 
//    Rev 1.8   Sep 16 2011 17:07:08   dchatcha
// Usability Improvement on iFAST/Desktop
// 
