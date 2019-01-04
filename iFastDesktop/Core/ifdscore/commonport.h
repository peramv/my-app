// DTWK - Do not put inclusion guards here.
//        Put inclusion guards around each #include or #define statement
//        because this file will be inclued multiple times.

// DTWK - inclusion guards are OK now.  This file will no longer be included
//        Multiple times.
#ifndef COMMONPORT_H
#define COMMONPORT_H

#pragma warning(disable: 4005)


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


#ifdef DST_UNICODE
   #undef DST_MULTIBYTE
#endif

#ifndef COMMONPORT1_H
   #include <win32\commonport1.h>
#endif



// Is the std c++ class library NOT in the std namespace?
// This macro is set in commonport1.h
#if defined( NO_STD_NAMESPACE )
   #define std
#endif

#ifndef INCLUDED_STRING
   #define INCLUDED_STRING
   #include <string>
#endif

// This is always ascii
typedef std::string A_STRING;

// This is always unicode
typedef std::wstring U_STRING;

// internationalization

// commented-out macros should be in platform-specific files



#ifdef DST_UNICODE

//CP#  pragma message( "Text Type: UNICODE" )
   #define _UNICODE

typedef wchar_t I_CHAR;
typedef U_STRING I_STRING;
typedef wchar_t I_UCHAR;
   #define i_cout            std::wcout
   #define i_cin             std::wcin
   #define i_cerr            std::wcerr
   #define i_istream         std::wistream
   #define i_ostream         std::wostream
   #define i_ifstream        std::wifstream
   #define i_ofstream        std::wofstream
   #define i_fstream         std::wfstream
   #define i_filebuf         std::wfilebuf
   #define i_ios             std::wios
   #define i_iostream        std::wiostream
   #define i_stringstream    std::wstringstream
   #define i_istringstream   std::wistringstream
   #define i_ostringstream   std::wostringstream

   #define I_(a)  L ## a

   #define i_isascii     iswascii
//#  define i_access      _waccess
//#  define i_chdir       _wchdir
//#  define i_chmod       _wchmod
//#  define i_creat       _wcreat
//#  define i_execl       _wexecl
//#  define i_execle      _wexecle
//#  define i_execlp      _wexeclp
//#  define i_execlpe     _wexeclpe
//#  define i_execv       _wexecv
//#  define i_execve      _wexecve
//#  define i_execvp      _wexecvp
//#  define i_execvpe     _wexeclvpe
//#  define i_fdopen      _wfdopen
//#  define i_findfirst   _wfindfirst
//#  define i_findnext    _wfindnext
//#  define i_fsopen      _wfsopen
//#  define i_fullpath    _wfullpath
//#  define i_getcwd      _wgetcwd
//#  define i_itot        _itow
//#  define i_ltot        _ltow
//#  define i_i64tot      _i64tow
//#  define i_ui64tot     _ui64tow
//#  define i_makepath    _wmakepath
//#  define i_mkdir       _wmkdir
//#  define i_mktemp      _wmktemp
//#  define i_open        _wopen
//#  define i_popen       _wpopen
//#  define i_rmdir       _wrmdir
//#  define i_searchenv   _wsearchenv
//#  define i_snprintf    _wsnwprintf
//#  define i_sopen       _wsopen
//#  define i_spawnl      _wspawnl
//#  define i_spawnle     _wspawnle
//#  define i_spawnlp     _wspawnlp
//#  define i_spawnlpe    _wspawnlpe
//#  define i_spawnv      _wspawnv
//#  define i_spawnve     _wspawnve
//#  define i_spawnvp     _wspawnvp
//#  define i_spawnvpe    _wspawnvpe
//#  define i_splitpath   _wsplitpath
//#  define i_stat        _wstat
//#  define i_strdate     _wstrdate
//#  define i_strdec      _wcsdec
//#  define i_strdup      _wcsdup
//#  define i_stricmp     _wcsicmp
//#  define i_stricoll    _wcsicoll
//#  define i_strinc      _wcsinc
//#  define i_strlwr      _wcslwr
//#  define i_strncnt     _wcscnt
//#  define i_strnextc    _wcsnextc
//#  define i_strnicmp    _wcsnicmp
//#  define i_strnicoll   _wcsnicoll
//#  define i_strninc     _wcsninc
//#  define i_strnset     _wcsnset
//#  define i_strnbset    _wcsnbset
//#  define i_strrev      _wcsrev
//#  define i_strset      _wcsset
//#  define i_strspnp     _wcsspnp
//#  define i_strtime     _wstrtime
//#  define i_strupr      _wcsupr
//#  define i_tempnam     _wtempnam
//#  define i_ultot       _ultow
//#  define i_unlink      _wunlink
//#  define i_utime       _wutime
//#  define i_vsnprintf   _vsnwprintf
//#  define i_asctime     _wasctime
//#  define i_ttoi        _wtoi
//#  define i_ttol        _wtol
//#  define i_ctime       _wctime
   #define i_fgetc       fgetwc
//#  define i_fgetchar    _fgetwchar
   #define i_fgets       fgetws
//#  define i_fopen       _wfopen
   #define i_fprintf     fwprintf
   #define i_fputc       fputwc
//#  define i_fputchar    _fputwchar
   #define i_fputs       fputws
//#  define i_freopen     _wfreopen
   #define i_fscanf      fwscanf
   #define i_getc        getwc
   #define i_getchar     getwchar
//#  define i_getenv      _wgetenv
   #define i_gets        getws
   #define i_isalnum     iswalnum
   #define i_isalpha     iswalpha
   #define i_iscntrl     iswcntrl
   #define i_isdigit     iswdigit
   #define i_isgraph     iswgraph
   #define i_islower     iswlower
   #define i_ispunct     iswpunct
   #define i_isspace     iswspace
   #define i_isupper     iswupper
   #define i_isxdigit    iswxdigit
   #define i_main        wmain
//#  define i_perror      _wperror
   #define i_printf      wprintf
   #define i_putc        putwc
   #define i_putchar     putwchar
   #define i_puts        putws
//#  define i_remove      _wremove
//#  define i_rename      _wrename
   #define i_scanf       wscanf
   #define i_setlocale   _wsetlocale
   #define i_sprintf     swprintf
   #define i_sscanf      swscanf
   #define i_strcat      wcscat
   #define i_strchr      wcschr
   #define i_strcmp      wcscmp
   #define i_strcoll     wcscoll
   #define i_strcpy      wcscpy
   #define i_strcspn     wcscspn
   #define i_strftime    wcsftime
   #define i_strlen      wcslen
   #define i_strncat     wcsncat
   #define i_strnbcat    wcsnbcat
   #define i_strncmp     wcsncmp
   #define i_strnbcmp    wcsnbcmp
   #define i_strncpy     wcsncpy
   #define i_strnbcpy    wcsnbcpy
   #define i_strpbrk     wcspbrk
   #define i_strrchr     wcsrchr
   #define i_strspn      wcsspn
   #define i_strstr      wcsstr
   #define i_strtod      wcstod
   #define i_strtok      wcstok
   #define i_strtol      wcstol
   #define i_strtoul     wcstoul
   #define i_strxfrm     wcsxfrm
//#  define i_system      _wsystem
//#  define i_tmpnam      _wtmpnam
   #define i_tolower     towlower
   #define i_toupper     towupper
   #define i_ungetc      ungetwc
   #define i_vfprintf    vfwprintf
   #define i_vprintf     vwprintf
   #define i_vsprintf    vswprintf

inline void asciistringToUnicodestring( const A_STRING & ascii,
                                        I_STRING & saveString )
{
   unsigned length = ascii.length();
   I_CHAR * save = new I_CHAR[ ( length + 1 ) * sizeof( I_CHAR ) ];

   unsigned i = 0;
   for( i = 0; i < length; ++i )
   {
      save[ i ] = ( unsigned char )ascii[ i ];
   }

   save[ i ] = '\0';

   saveString = save;
   delete [] save;
}


inline void unicodestringToAsciistring( const I_STRING & unicode,
                                        A_STRING & saveString )
{
   unsigned length = unicode.length();
   char * save = new char[ length + 1 ];

   unsigned i = 0;
   for( i = 0; i < length; ++i )
   {
      save[ i ] = ( char ) unicode[ i ];
   }

   save[ i ] = '\0';
   saveString = save;
   delete [] save;
}



#else


typedef char I_CHAR;
typedef A_STRING I_STRING;
typedef unsigned char I_UCHAR;
   #define i_cout            std::cout
   #define i_cin             std::cin
   #define i_cerr            std::cerr
   #define i_istream         std::istream
   #define i_ostream         std::ostream
   #define i_ifstream        std::ifstream
   #define i_ofstream        std::ofstream
   #define i_fstream         std::fstream
   #define i_filebuf         std::filebuf
   #define i_ios             std::ios
   #define i_iostream        std::iostream
   #define i_stringstream    std::stringstream
   #define i_istringstream   std::istringstream
   #define i_ostringstream   std::ostringstream

   #define I_(a)  a

   #ifdef DST_MULTIBYTE
      #define _MBCS

//CP#  pragma message( "Text Type: MULTIBYTE" )



//#  define i_isascii     __isascii
//#  define i_access      _access
//#  define i_chdir       _chdir
//#  define i_chmod       _chmod
//#  define i_creat       _creat
//#  define i_execl       _execl
//#  define i_execle      _execle
//#  define i_execlp      _execlp
//#  define i_execlpe     _execlpe
//#  define i_execv       _execv
//#  define i_execvp      _execvp
//#  define i_execve      _execve
//#  define i_execvpe     _execvpe
//#  define i_fdopen      _fdopen
//#  define i_findfirst   _findfirst
//#  define i_findnext    _findnext
//#  define i_fsopen      _fsopen
//#  define i_fullpath    _fullpath
//#  define i_getcwd      _getcwd
//#  define i_itot        _itoa
//#  define i_ltot        _ltoa
//#  define i_i64tot      _i64toa
//#  define i_ui64tot     _ui64toa
//#  define i_makepath    _makepath
//#  define i_mkdir       _mkdir
//#  define i_mktemp      _mktemp
//#  define i_open        _open
//#  define i_rmdir       _popen
//#  define i_searchenv   _rmdir
//#  define i_snprintf    _searchenv
//#  define i_sopen       _snprintf
//#  define i_spawnl      _sopen
//#  define i_spawnle     _spawnl
//#  define i_spawnlp     _spawnle
//#  define i_spawnlpe    _spawnlp
//#  define i_spawnv      _spawnlpe
//#  define i_spawnve     _spawnv
//#  define i_spawnvp     _spawnve
//#  define i_spawnvpe    _spawnvpe
//#  define i_splitpath   _splitpath
//#  define i_stat        _stat
//#  define i_strdate     _strdate
//#  define i_strdec      _mbsdec
//#  define i_strdup      _mbsdup
//#  define i_stricmp     _mbsicmp
//#  define i_stricoll    _mbsicoll
//#  define i_strinc      _mbsinc
//#  define i_strlwr      _mbslwr
//#  define i_strncnt     _mbsncnt
//#  define i_strnextc    _mbsnextc
//#  define i_strnicmp    _mbsnicmp
//#  define i_strnicoll   _mbsnicoll
//#  define i_strninc     _mbsninc
//#  define i_strnset     _mbsnset
//#  define i_strnbset    _mbsnbset
//#  define i_strrev      _mbsrev
//#  define i_strset      _mbsset
//#  define i_strspnp     _mbsspnp
//#  define i_strtime     _strtime
//#  define i_strupr      _mbsupr
//#  define i_tempnam     _tempnam
//#  define i_ultot       _ultoa
//#  define i_unlink      _unlink
//#  define i_utime       _utime
//#  define i_vsnprintf   _vsnprintf
      #define i_asctime     asctime
      #define i_ttoi        atoi
      #define i_ttol        atol
      #define i_ctime       ctime
      #define i_fgetc       fgetc
      #define i_fgetchar    fgetchar
      #define i_fgets       fgets
      #define i_fopen       fopen
      #define i_fprintf     fprintf
      #define i_fputc       fputc
      #define i_fputchar    fputchar
      #define i_fputs       fputs
      #define i_freopen     freopen
      #define i_fscanf      fscanf
      #define i_getc        getc
      #define i_getchar     getchar
      #define i_getenv      getenv
      #define i_gets        gets
//#  define i_isalnum     _ismbcalnum
//#  define i_isalpha     _ismbcalpha
//#  define i_iscntrl     _ismbccntrl
//#  define i_isdigit     _ismbcdigit
//#  define i_isgraph     _ismbcgraph
//#  define i_islower     _ismbclower
//#  define i_ispunct     _ismbcpunct
//#  define i_isspace     _ismbcspace
//#  define i_isupper     _ismbcupper
//#  define i_isxdigit    _ismbcxdigit
      #define i_main        main
      #define i_perror      perror
      #define i_printf      printf
      #define i_putc        putc
      #define i_putchar     putchar
      #define i_puts        puts
      #define i_remove      remove
      #define i_rename      rename
      #define i_scanf       scanf
      #define i_setlocale   setlocale
      #define i_sprintf     sprintf
      #define i_sscanf      sscanf
//#  define i_strcat      _mbscat
//#  define i_strchr      _mbschr
//#  define i_strcmp      _mbscmp
      #define i_strcoll     strcoll
//#  define i_strcpy      _mbscpy
//#  define i_strcspn     _mbscspn
      #define i_strftime    strftime
//#  define i_strlen      _mbslen
//#  define i_strncat     _mbsncat
//#  define i_strnbcat    _mbsnbcat
//#  define i_strncmp     _mbsncmp
//#  define i_strnbcmp    _mbsnbcmp
//#  define i_strncpy     _mbsncpy
//#  define i_strnbcpy    _mbsnbcpy
//#  define i_strpbrk     _mbsbrk
//#  define i_strrchr     _mbsrchr
//#  define i_strspn      _mbsspn
//#  define i_strstr      _mbsstr
      #define i_strtod      strtod
//#  define i_strtok      _mbstok
      #define i_strtol      strtol
      #define i_strtoul     strtoul
      #define i_strxfrm     strxfrm
      #define i_system      system
      #define i_tmpnam      tmpnam
//#  define i_tolower     _mbctolower
//#  define i_toupper     _mbctoupper
      #define i_ungetc      ungetc
      #define i_vfprintf    vfprintf
      #define i_vprintf     vprintf
      #define i_vsprintf    vsprintf

   #else

//CP#  pragma message( "Text Type: ASCII" )

// SBCS
//#  define i_isascii     __isascii
//#  define i_access      _access
//#  define i_chdir       _chdir
//#  define i_chmod       _chmod
//#  define i_creat       _creat
//#  define i_execl       _execl
//#  define i_execle      _execle
//#  define i_execlp      _execlp
//#  define i_execlpe     _execlpe
//#  define i_execv       _execv
//#  define i_execve      _execve
//#  define i_execvp     _execvp
//#  define i_execvpe     _execvpe
//#  define i_fdopen      _fdopen
//#  define i_findfirst   _findfirst
//#  define i_findnext    _findnext
//#  define i_fsopen      _fsopen
//#  define i_fullpath    _fullpath
//#  define i_getcwd      _getcwd
//#  define i_itot        _itoa
//#  define i_ltot        _ltoa
//#  define i_makepath    _makepath
//#  define i_mkdir       _mkdir
//#  define i_mktemp      _mktemp
//#  define i_open        _open
//#  define i_rmdir       _popen
//#  define i_searchenv   _rmdir
//#  define i_snprintf    _searchenv
//#  define i_sopen       _snprintf
//#  define i_spawnl      _sopen
//#  define i_spawnle     _spawnl
//#  define i_spawnlp     _spawnle
//#  define i_spawnlpe    _spawnlp
//#  define i_spawnv      _spawnlpe
//#  define i_spawnve     _spawnv
//#  define i_spawnvp     _spawnve
//#  define i_spawnvpe    _spawnvpe
//#  define i_splitpath   _splitpath
//#  define i_stat        _stat
//#  define i_strdate     _strdate
//#  define i_strdec      _strdec
//#  define i_strdup      _strdup
//#  define i_stricmp     _stricmp
//#  define i_stricoll    _stricoll
//#  define i_strinc      _strinc
//#  define i_strlwr      _strlwr
//#  define i_strncnt     _strncnt
//#  define i_strnextc    _strnextc
//#  define i_strnicmp    _strnicmp
//#  define i_strnicoll   _strnicoll
//#  define i_strninc     _strninc
//#  define i_strnset     _strnset
//#  define i_strnbset    _strnbset
//#  define i_strrev      _strrev
//#  define i_strset      _strset
//#  define i_strspnp     _strspnp
//#  define i_strtime     _strtime
//#  define i_strupr      _strupr
//#  define i_tempnam     _tempnam
//#  define i_ultot       _ultoa
//#  define i_unlink      _unlink
//#  define i_utime       _utime
//#  define i_vsnprintf   _vsnprintf
      #define i_asctime     asctime
      #define i_ttoi        atoi
      #define i_ttol        atol
      #define i_ctime       ctime
      #define i_fgetc       fgetc
      #define i_fgetchar    fgetchar
      #define i_fgets       fgets
      #define i_fopen       fopen
      #define i_fprintf     fprintf
      #define i_fputc       fputc
      #define i_fputchar    fputchar
      #define i_fputs       fputs
      #define i_freopen     freopen
      #define i_fscanf      fscanf
      #define i_getc        getc
      #define i_getchar     getchar
      #define i_getenv      getenv
      #define i_gets        gets
      #define i_isalnum     isalnum
      #define i_isalpha     isalpha
      #define i_iscntrl     iscntrl
      #define i_isdigit     isdigit
      #define i_isgraph     isgraph
      #define i_islower     islower
      #define i_ispunct     ispunct
      #define i_isspace     isspace
      #define i_isupper     isupper
      #define i_isxdigit    isxdigit
      #define i_main        main
      #define i_perror      perror
      #define i_printf      printf
      #define i_putc        putc
      #define i_putchar     putchar
      #define i_puts        puts
      #define i_remove      remove
      #define i_rename      rename
      #define i_scanf       scanf
      #define i_setlocale   setlocale
      #define i_sprintf     sprintf
      #define i_sscanf      sscanf
      #define i_strcat      strcat
      #define i_strchr      strchr
      #define i_strcmp      strcmp
      #define i_strcoll     strcoll
      #define i_strcpy      strcpy
      #define i_strcspn     strcspn
      #define i_strftime    strftime
      #define i_strlen      strlen
      #define i_strncat     strncat
      #define i_strnbcat    strnbcat
      #define i_strncmp     strncmp
      #define i_strnbcmp    strnbcmp
      #define i_strncpy     strncpy
      #define i_strnbcpy    strnbcpy
      #define i_strpbrk     strbrk
      #define i_strrchr     strrchr
      #define i_strspn      strspn
      #define i_strstr      strstr
      #define i_strtod      strtod
      #define i_strtok      strtok
      #define i_strtol      strtol
      #define i_strtoul     strtoul
      #define i_strxfrm     strxfrm
      #define i_system      system
      #define i_tmpnam      tmpnam
      #define i_tolower     tolower
      #define i_toupper     toupper
      #define i_ungetc      ungetc
      #define i_vfprintf    vfprintf
      #define i_vprintf     vprintf
      #define i_vsprintf    vsprintf

   #endif


#endif



#if !defined(__OS2__)

// this should account for process and thread ID values on other platforms
typedef unsigned long PID;
typedef unsigned long TID;
typedef unsigned long APIRET;

#endif   //__OS2__

#if !defined(_WIN32)

   #define TRUE         1
   #define FALSE        0
   #define VOID            void

// this won't compile with Visual Age 3.0 for OS2
//typedef void            VOID;

typedef unsigned long   DWORD;
typedef char *          PCHAR;
typedef void *          PVOID;
typedef const char *    PCCH;
typedef unsigned long   HANDLE;
typedef unsigned char   byte;
typedef unsigned short  WORD;

typedef struct _SYSTEMTIME
{
   WORD wYear;
   WORD wMonth;
   WORD wDayOfWeek;
   WORD wDay;
   WORD wHour;
   WORD wMinute;
   WORD wSecond;
   WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

   #define SH_READ      SH_DENYWR
   #define _O_RDONLY    O_RDONLY

#endif   // _WIN32





/*******************************************************************************
//              Revision Control Entries
//#*****************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/commonport.h-arc  $
//
//   Rev 1.1   Oct 09 2002 17:41:46   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:34   SMITHDAV
//Initial revision.
// 
//    Rev 1.21   May 21 2001 13:03:38   DT21858
// Fix in ICUStringtoIString() and ICUStringtoAString()
// 
//    Rev 1.20   23 Oct 2000 13:10:34   dt14177
// cleanup
// 
//    Rev 1.19   Aug 15 2000 11:53:46   DT14177
// fixed typo for strtod
// 
//    Rev 1.18   Jun 26 2000 17:09:22   DT14177
// added constructors and assignment operators to MathString
// 
//    Rev 1.17   Apr 11 2000 09:06:52   DT14177
// changed name of ICUStringToDString macro to ICUStringToIString; added ICUStringToAString macro
// 
//    Rev 1.16   Apr 10 2000 16:57:26   dtwk
// Change #includes of icu classes to <> instead of ""
// 
//    Rev 1.15   06 Apr 2000 09:55:24   dt20842
// Added ICUStringtoDString
// 
//    Rev 1.14   Nov 04 1999 15:04:02   DT29758
// remove the i_ostrstream definition
// since it is not part of the std namespace
// 
//    Rev 1.13   Oct 25 1999 15:54:04   DT29758
// added a #define for ostrstream  and
//  strstream
// 
//    Rev 1.12   Jul 13 1999 16:14:28   dtwk
// Change delete to delete[]
// 
//    Rev 1.11   May 14 1999 10:21:20   DT20842
// Uncommented setlocale function for Unicode
// 
//    Rev 1.10   Apr 15 1999 11:44:58   DMUM
// String development/enhancement
// 
//    Rev 1.9   05 Mar 1999 09:14:34   DT14177
// Added stream stuff
// 
//    Rev 1.8   26 Feb 1999 11:08:56   DT14177
// Added streams and filebuf
// 
//    Rev 1.7   22 Feb 1999 11:46:40   DT14177
// fixed DString and const I_CHAR stuff
//
//    Rev 1.6   18 Feb 1999 10:28:40   DT14177
// UNICODE
//
//    Rev 1.4   Jan 28 1999 14:05:30   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:40:00   DMUM
// Check in for DICORE
//
//    Rev 1.8   Nov 09 1997 15:34:28   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.7   Feb 11 1997 13:22:32   DTWK
// Use RogueWave Standard C++ Library/
// Split CLogSll to DIVIEW and DIOS/ change
// SCLXTNSN to DISCLXTN
//
//    Rev 1.6   Dec 18 1996 11:59:32   DTWK
// Remove inclusion guards
 *
 *    Rev 1.5   Nov 21 1996 14:37:12   DRUS
 *
//
//    Rev 1.4   Nov 20 1996 17:07:18   DRUS
//
//
*/

#endif // commonport_h


