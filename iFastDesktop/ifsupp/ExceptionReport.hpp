#pragma once

// Import/Export resolution
#undef IFSUPP_LINKAGE
#ifdef IFSUPP_DLL
   #define IFSUPP_LINKAGE CLASS_EXPORT
#else
   #define IFSUPP_LINKAGE CLASS_IMPORT
#endif

#include <dbghelp.h>
#include <bfutil/bfcritsec.hpp>

enum BasicType
{
   btNoType = 0,
   btVoid = 1,
   btChar = 2,
   btWChar = 3,
   btInt = 6,
   btUInt = 7,
   btFloat = 8,
   btBCD = 9,
   btBool = 10,
   btLong = 13,
   btULong = 14,
   btCurrency = 25,
   btDate = 26,
   btVariant = 27,
   btComplex = 28,
   btBit = 29,
   btBSTR = 30,
   btHresult = 31
};



class IFSUPP_LINKAGE ExceptionReport
{
public:

   typedef void (__stdcall *PFNGF)( char* pszBuf, unsigned int cb );

   ExceptionReport( );
   ~ExceptionReport( );

   static PFNGF setFileGenerator( PFNGF pfngf );

   const char* getLogFileName();

   static const char* getLogFileDir();
   static void setLogFileDir( const DString& strLogFileDir );


   static bool isEnabled();
   static void enable( bool b );

   // entry point where control comes on an unhandled exception
   static LONG WINAPI unhandledExceptionFilter( PEXCEPTION_POINTERS pExceptionInfo );

private:

   typedef enum {
      typeDefault = 0, typeAdvancedServer = 1, typeWorkstation = 2, typeServer = 3
   } NTTYPE;

   static void logStackDump( DWORD frame );
   static void logRegisters( const CONTEXT& c );
   static void logMachineConfiguration( void );
   static NTTYPE getNTVersion( void );

   // where report info is extracted and generated
   static DWORD generateExceptionReport( PEXCEPTION_POINTERS pExceptionInfo );

   // Helper functions
   static const char* getExceptionString( DWORD dwCode );
   static bool getLogicalAddress(  PVOID addr,
                                   char* szModule,
                                   DWORD len,
                                   DWORD& section,
                                   DWORD& offset );

   static void writeStackDetails( PCONTEXT pContext,
                                  bool bWriteVariables );

   static BOOL CALLBACK enumerateSymbolsCallback(PSYMBOL_INFO,
                                                 ULONG,
                                                 PVOID);

   static bool formatSymbolValue( PSYMBOL_INFO,
                                  STACKFRAME *,
                                  char * pszBuffer,
                                  unsigned cbBuffer );

   static char * dumpTypeIndex( char *,
                                DWORD64,
                                DWORD,
                                unsigned,
                                DWORD_PTR,
                                bool & );

   static char * formatOutputValue( char * pszCurrBuffer,
                                    BasicType basicType,
                                    DWORD64 length,
                                    PVOID pAddress );

   static BasicType getBasicType( DWORD typeIndex,
                                  DWORD64 modBase );

   static int __cdecl _tprintf(const char* pszMask, ...);

   // Variables used by the class
   static LPTOP_LEVEL_EXCEPTION_FILTER s_previousFilter_;
   static HANDLE s_hProcess_;

   static PFNGF s_pFNGF_;

//CP20070402#if 0
//CP20070402   static HANDLE s_hReportFile_;
//CP20070402#else
//CP20070402   static FILE* s_pfReport_;
//CP20070402#endif

   static BFCritSec s_csEnableReporting_;
   static bool s_bEnableReporting_;

};


extern ExceptionReport g_ExceptionReport; //  global instance of class
