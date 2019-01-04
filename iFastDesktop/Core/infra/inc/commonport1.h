// #ifndef COMMONPORT1_H
// #define COMMONPORT1_H

#  pragma message( "including "__FILE__ )

/*
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

// DESCRIPTION : WIN32 implementation of commonport.h


#define DSTWINDOWHANDLE void *

// Is this Microsoft Visual C++ compiler?
#if defined( _MSC_VER )
// Is this version prior to Visual C++ 5.0 and does not have the
// stl in the std namespace
#if _MSC_VER < 1100
#define NO_STD_NAMESPACE
#endif
#endif

#ifndef WIN32
#define WIN32
#endif

#if defined( _WIN32 )
   #if !defined( _MT ) || !defined( _DLL )
      #error Use a Multi-Threaded DLL run-time library (compile option /MD for release or /MDd for debug).
   #endif
   #if !defined( _CPPRTTI )
      #error Enable Run-Time Type Information (compile option /GR).
   #endif
#endif

#define CLASS_EXPORT _declspec( dllexport )
#define CLASS_IMPORT _declspec( dllimport )

#define EXPORTOS2
#define EXPORTWIN _declspec( dllexport )
#define CMNEXPORT _declspec( dllexport )

#define EXPORTOS2C
#define EXPORTWINC  _declspec( dllexport )

#define NULLHANDLE NULL

#define OPT_LINKAGE __cdecl
#define SYSTEM_LINKAGE __cdecl

#define ALLOCATOR(X) allocator< X >

#define HEADER_THROW
#define HEADER_THROW1(X)
#define HEADER_THROW2(X1, X2)

#define SH_READ   filebuf::sh_read

#define DIINT64   __int64

// Added these for Java JNI portability
#define DIJAVABYTE signed char
#define DIJAVAINT long

#ifdef DST_UNICODE

#  define i_isascii     iswascii  // NT
#  define i_access      _waccess  // NT
#  define i_chdir       _wchdir   // NT
#  define i_chmod       _wchmod   // NT
#  define i_creat       _wcreat   // NT
#  define i_execl       _wexecl   // NT
#  define i_execle      _wexecle   // NT
#  define i_execlp      _wexeclp   // NT
#  define i_execlpe     _wexeclpe    // NT
#  define i_execv       _wexecv      // NT
#  define i_execve      _wexecve     // NT
#  define i_execvp      _wexecvp     // NT
#  define i_execvpe     _wexeclvpe   // NT
#  define i_fdopen      _wfdopen     // 95 & NT
#  define i_findfirst   _wfindfirst  // NT
#  define i_findnext    _wfindnext   // NT
#  define i_fsopen      _wfsopen     // NT
#  define i_fullpath    _wfullpath   // NT
#  define i_getcwd      _wgetcwd     // NT
#  define i_itot        _itow        // 95 & NT
#  define i_ltot        _ltow        // 95 & NT
#  define i_i64tot      _i64tow      // 95 & NT
#  define i_ui64tot     _ui64toa     // 95 & NT
#  define i_makepath    _wmakepath   // 95 & NT
#  define i_mkdir       _wmkdir      // NT
#  define i_mktemp      _wmktemp     // 95 & NT
#  define i_open        _wopen       // NT
#  define i_popen       _wpopen      // NT
#  define i_rmdir       _wrmdir      // NT
#  define i_searchenv   _wsearchenv  // NT
#  define i_snprintf    _snwprintf   // 95 & NT
#  define i_sopen       _wsopen      // NT
#  define i_spawnl      _wspawnl     // NT
#  define i_spawnle     _wspawnle    // NT
#  define i_spawnlp     _wspawnlp    // NT
#  define i_spawnlpe    _wspawnlpe   // NT
#  define i_spawnv      _wspawnv     // NT
#  define i_spawnve     _wspawnve    // NT
#  define i_spawnvp     _wspawnvp    // NT
#  define i_spawnvpe    _wspawnvpe   // NT
#  define i_splitpath   _wsplitpath  // 95 & NT
#  define i_stat        _wstat       // NT
#  define i_strdate     _wstrdate    // 95 & NT
#  define i_strdec      _wcsdec      // 95 & NT
#  define i_strdup      _wcsdup      // 95 & NT
#  define i_stricmp     _wcsicmp     // 95 & NT
#  define i_stricoll    _wcsicoll    // 95 & NT
#  define i_strinc      _wcsinc      // 95 & NT
#  define i_strlwr      _wcslwr      // 95 & NT
#  define i_strncnt     _wcsncnt     // 95 & NT
#  define i_strnextc    _wcsnextc    // 95 & NT
#  define i_strnicmp    _wcsnicmp    // 95 & NT
#  define i_strnicoll   _wcsnicoll   // 95 & NT
#  define i_strninc     _wcsninc     // 95 & NT
#  define i_strnset     _wcsnset     // 95 & NT
#  define i_strrev      _wcsrev      // 95 & NT
#  define i_strset      _wcsset      // 95 & NT
#  define i_strspnp     _wcsspnp     // 95 & NT
#  define i_strtime     _wstrtime    // 95 & NT
#  define i_strupr      _wcsupr      // 95 & NT
#  define i_tempnam     _wtempnam    // 95 & NT
#  define i_ultot       _ultow       // 95 & NT
#  define i_unlink      _wunlink     // NT
#  define i_utime       _wutime      // 95 & NT
#  define i_vsnprintf   _vsnwprintf  // 95 & NT
#  define i_asctime     _wasctime    // 95 & NT
#  define i_ttoi        _wtoi        // 95 & NT
#  define i_ttol        _wtol        // 95 & NT
#  define i_ctime       _wctime      // 95 & NT
//#  define i_fgetc       fgetwc
#  define i_fgetchar    _fgetwchar   // 95 & NT
//#  define i_fgets       fgetws
#  define i_fopen       _wfopen      // NT
//#  define i_fprintf     fwprintf
//#  define i_fputc       fputwc
#  define i_fputchar    _fputwchar   // 95 & NT
//#  define i_fputs       fputws
#  define i_freopen     _wfreopen    // NT
//#  define i_fscanf      fwscanf
//#  define i_getc        getwc
//#  define i_getchar     getwchar
#  define i_getenv      _wgetenv     // 95 & NT
//#  define i_gets        getws
//#  define i_isalnum     iswalnum
//#  define i_isalpha     iswalpha
//#  define i_iscntrl     iswcntrl
//#  define i_isdigit     iswdigit
//#  define i_isgraph     iswgraph
//#  define i_islower     iswlower
//#  define i_ispunct     iswpunct
//#  define i_isspace     iswspace
//#  define i_isupper     iswupper
//#  define i_isxdigit    iswxdigit
//#  define i_main        wmain
#  define i_perror      _wperror     // 95 & NT
//#  define i_printf      wprintf
//#  define i_putc        putwc
//#  define i_putchar     putwchar
//#  define i_puts        putws
#  define i_remove      _wremove     // NT
#  define i_rename      _wrename     // NT
//#  define i_scanf       wscanf
#  define i_setlocale   _wsetlocale  // NT
//#  define i_sprintf     swprintf
//#  define i_sscanf      swscanf
//#  define i_strcat      wcscat
//#  define i_strchr      wcschr
//#  define i_strcmp      wcscmp
//#  define i_strcoll     wcscoll
//#  define i_strcpy      wcscpy
//#  define i_strcspn     wcscspn
//#  define i_strftime    wcsftime
//#  define i_strlen      wcslen
//#  define i_strncat     wcsncat
//#  define i_strnbcat    wcsnbcat
//#  define i_strncmp     wcsncmp
//#  define i_strnbcmp    wcsnbcmp
//#  define i_strncpy     wcsncpy
//#  define i_strnbcpy    wcsnbcpy
//#  define i_strpbrk     wcspbrk
//#  define i_strrchr     wcsrchr
//#  define i_strspn      wcsspn
//#  define i_strstr      wcsstr
//#  define i_strtod      wcstod
//#  define i_strtok      wcstok
//#  define i_strtol      wcstol
//#  define i_strtoul     wcstoul
//#  define i_strxfrm     wcsxfrm
#  define i_system      _wsystem      // NT
#  define i_tmpnam      _wtmpnam      // 95 & NT
//#  define i_tolower     towlower
//#  define i_toupper     towupper
//#  define i_ungetc      ungetwc
//#  define i_vfprintf    vfwprintf
//#  define i_vprintf     vwprintf
//#  define i_vsprintf    vswprintf

#else

#ifdef DST_MULTIBYTE

#  define i_isascii     __isascii
#  define i_access      _access
#  define i_chdir       _chdir
#  define i_chmod       _chmod
#  define i_creat       _creat
#  define i_execl       _execl
#  define i_execle      _execle
#  define i_execlp      _execlp
#  define i_execlpe     _execlpe
#  define i_execv       _execv
#  define i_execvp      _execve
#  define i_execvpe     _execvp
#  define i_fdopen      _execvpe
#  define i_findfirst   _findfirst
#  define i_findnext    _findnext
#  define i_fsopen      _fsopen
#  define i_fullpath    _fullpath
#  define i_getcwd      _getcwd
#  define i_itot        _itoa
#  define i_ltot        _ltoa
#  define i_i64tot      _i64toa
#  define i_ui64tot     _ui64toa
#  define i_makepath    _makepath
#  define i_mkdir       _mkdir
#  define i_mktemp      _mktemp
#  define i_open        _open
#  define i_rmdir       _popen
#  define i_searchenv   _rmdir
#  define i_snprintf    _searchenv
#  define i_sopen       _snprintf
#  define i_spawnl      _sopen
#  define i_spawnle     _spawnl
#  define i_spawnlp     _spawnle
#  define i_spawnlpe    _spawnlp
#  define i_spawnv      _spawnlpe
#  define i_spawnve     _spawnv
#  define i_spawnvp     _spawnve
#  define i_spawnvpe    _spawnvpe
#  define i_splitpath   _splitpath
#  define i_stat        _stat
#  define i_strdate     _strdate
#  define i_strdec      _mbsdec
#  define i_strdup      _mbsdup
#  define i_stricmp     _mbsicmp
#  define i_stricoll    _mbsicoll
#  define i_strinc      _mbsinc
#  define i_strlwr      _mbslwr
#  define i_strncnt     _mbsncnt
#  define i_strnextc    _mbsnextc
#  define i_strnicmp    _mbsnicmp
#  define i_strnicoll   _mbsnicoll
#  define i_strninc     _mbsninc
#  define i_strnset     _mbsnset
#  define i_strnbset    _mbsnbset
#  define i_strrev      _mbsrev
#  define i_strset      _mbsset
#  define i_strspnp     _mbsspnp
#  define i_strtime     _strtime
#  define i_strupr      _mbsupr
#  define i_tempnam     _tempnam
#  define i_ultot       _ultoa
#  define i_unlink      _unlink
#  define i_utime       _utime
#  define i_vsnprintf   _vsnprintf
//#  define i_asctime     asctime
//#  define i_ttoi        atoi
//#  define i_ttol        atol
//#  define i_ctime       ctime
//#  define i_fgetc       fgetc
//#  define i_fgetchar    fgetchar
//#  define i_fgets       fgets
//#  define i_fopen       fopen
//#  define i_fprintf     fprintf
//#  define i_fputc       fputc
//#  define i_fputchar    fputchar
//#  define i_fputs       fputs
//#  define i_freopen     freopen
//#  define i_fscanf      fscanf
//#  define i_getc        getc
//#  define i_getchar     getchar
//#  define i_getenv      getenv
//#  define i_gets        gets
#  define i_isalnum     _ismbcalnum
#  define i_isalpha     _ismbcalpha
#  define i_iscntrl     _ismbccntrl
#  define i_isdigit     _ismbcdigit
#  define i_isgraph     _ismbcgraph
#  define i_islower     _ismbclower
#  define i_ispunct     _ismbcpunct
#  define i_isspace     _ismbcspace
#  define i_isupper     _ismbcupper
#  define i_isxdigit    _ismbcxdigit
//#  define i_main        main
//#  define i_perror      perror
//#  define i_printf      printf
//#  define i_putc        putc
//#  define i_putchar     putchar
//#  define i_puts        puts
//#  define i_remove      remove
//#  define i_rename      rename
//#  define i_scanf       scanf
//#  define i_setlocale   setlocale
//#  define i_sprintf     sprintf
//#  define i_sscanf      sscanf
#  define i_strcat      _mbscat
#  define i_strchr      _mbschr
#  define i_strcmp      _mbscmp
//#  define i_strcoll     strcoll
#  define i_strcpy      _mbscpy
#  define i_strcspn     _mbscspn
//#  define i_strftime    strftime
#  define i_strlen      _mbslen
#  define i_strncat     _mbsncat
#  define i_strnbcat    _mbsnbcat
#  define i_strncmp     _mbsncmp
#  define i_strnbcmp    _mbsnbcmp
#  define i_strncpy     _mbsncpy
#  define i_strnbcpy    _mbsnbcpy
#  define i_strpbrk     _mbsbrk
#  define i_strrchr     _mbsrchr
#  define i_strspn      _mbsspn
#  define i_strstr      _mbsstr
//#  define i_strtod      strod
#  define i_strtok      _mbstok
//#  define i_strtol      strtol
//#  define i_strtoul     strtoul
//#  define i_strxfrm     strxfrm
//#  define i_system      system
//#  define i_tmpnam      tmpnam
#  define i_tolower     _mbctolower
#  define i_toupper     _mbctoupper
//#  define i_ungetc      ungetc
//#  define i_vfprintf    vfprintf
//#  define i_vprintf     vprintf
//#  define i_vsprintf    vsprintf

#  else

   // SBCS
#  define i_isascii     __isascii
#  define i_access      _access
#  define i_chdir       _chdir
#  define i_chmod       _chmod
#  define i_creat       _creat
#  define i_execl       _execl
#  define i_execle      _execle
#  define i_execlp      _execlp
#  define i_execlpe     _execlpe
#  define i_execv       _execv
#  define i_execvp      _execve
#  define i_execvpe     _execvp
#  define i_fdopen      _execvpe
#  define i_findfirst   _findfirst
#  define i_findnext    _findnext
#  define i_fsopen      _fsopen
#  define i_fullpath    _fullpath
#  define i_getcwd      _getcwd
#  define i_itot        _itoa
#  define i_ltot        _ltoa
#  define i_i64tot      _i64toa
#  define i_ui64tot     _ui64toa
#  define i_makepath    _makepath
#  define i_mkdir       _mkdir
#  define i_mktemp      _mktemp
#  define i_open        _open
#  define i_rmdir       _popen
#  define i_searchenv   _rmdir
#  define i_snprintf    _searchenv
#  define i_sopen       _snprintf
#  define i_spawnl      _sopen
#  define i_spawnle     _spawnl
#  define i_spawnlp     _spawnle
#  define i_spawnlpe    _spawnlp
#  define i_spawnv      _spawnlpe
#  define i_spawnve     _spawnv
#  define i_spawnvp     _spawnve
#  define i_spawnvpe    _spawnvpe
#  define i_splitpath   _splitpath
#  define i_stat        _stat
#  define i_strdate     _strdate
#  define i_strdec      _strdec
#  define i_strdup      _strdup
#  define i_stricmp     _stricmp
#  define i_stricoll    _stricoll
#  define i_strinc      _strinc
#  define i_strlwr      _strlwr
#  define i_strncnt     _strncnt
#  define i_strnextc    _strnextc
#  define i_strnicmp    _strnicmp
#  define i_strnicoll   _strnicoll
#  define i_strninc     _strninc
#  define i_strnset     _strnset
#  define i_strnbset    _strnbset
#  define i_strrev      _strrev
#  define i_strset      _strset
#  define i_strspnp     _strspnp
#  define i_strtime     _strtime
#  define i_strupr      _strupr
#  define i_tempnam     _tempnam
#  define i_ultot       _ultoa
#  define i_utime       _utime
#  define i_unlink      _unlink
#  define i_vsnprintf   _vsnprintf
//#  define i_asctime     asctime
//#  define i_ttoi        atoi
//#  define i_ttol        atol
//#  define i_ctime       ctime
//#  define i_fgetc       fgetc
//#  define i_fgetchar    fgetchar
//#  define i_fgets       fgets
//#  define i_fopen       fopen
//#  define i_fprintf     fprintf
//#  define i_fputc       fputc
//#  define i_fputchar    fputchar
//#  define i_fputs       fputs
//#  define i_freopen     freopen
//#  define i_fscanf      fscanf
//#  define i_getc        getc
//#  define i_getchar     getchar
//#  define i_getenv      getenv
//#  define i_gets        gets
//#  define i_isalnum     isalnum
//#  define i_isalpha     isalpha
//#  define i_iscntrl     iscntrl
//#  define i_isdigit     isdigit
//#  define i_isgraph     isgraph
//#  define i_islower     islower
//#  define i_ispunct     ispunct
//#  define i_isspace     isspace
//#  define i_isupper     isupper
//#  define i_isxdigit    isxdigit
//#  define i_main        main
//#  define i_perror      perror
//#  define i_printf      printf
//#  define i_putc        putc
//#  define i_putchar     putchar
//#  define i_puts        puts
//#  define i_remove      remove
//#  define i_rename      rename
//#  define i_scanf       scanf
//#  define i_setlocale   setlocale
//#  define i_sprintf     sprintf
//#  define i_sscanf      sscanf
//#  define i_strcat      strcat
//#  define i_strchr      strchr
//#  define i_strcmp      strcmp
//#  define i_strcoll     strcoll
//#  define i_strcpy      strcpy
//#  define i_strcspn     strcspn
//#  define i_strftime    strftime
//#  define i_strlen      strlen
//#  define i_strncat     strncat
//#  define i_strnbcat    strnbcat
//#  define i_strncmp     strncmp
//#  define i_strnbcmp    strnbcmp
//#  define i_strncpy     strncpy
//#  define i_strnbcpy    strnbcpy
//#  define i_strpbrk     strbrk
//#  define i_strrchr     strrchr
//#  define i_strspn      strspn
//#  define i_strstr      strstr
//#  define i_strtod      strod
//#  define i_strtok      strtok
//#  define i_strtol      strtol
//#  define i_strtoul     strtoul
//#  define i_strxfrm     strxfrm
//#  define i_system      system
//#  define i_tmpnam      tmpnam
//#  define i_tolower     tolower
//#  define i_toupper     toupper
//#  define i_ungetc      ungetc
//#  define i_vfprintf    vfprintf
//#  define i_vprintf     vprintf
//#  define i_vsprintf    vsprintf

#  endif

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
// $Log:   Y:/VCS/iFastAWD/inc/commonport1.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:28   kovacsro
//Initial revision.
// 
//    Rev 1.14   Jan 28 2002 17:18:32   DT20842
// Added checks for run-type information turn on and
// correct memory model
// 
//    Rev 1.13   30 Nov 2000 10:31:12   dt14177
// cleanup
// 
//    Rev 1.12   Jun 28 2000 18:05:48   DT14177
// fixed some ASCII build problems
// 
//    Rev 1.11   Jun 26 2000 17:09:28   DT14177
// added constructors and assignment operators to MathString
// 
//    Rev 1.10   May 02 2000 13:10:02   dtwk
// Add support in TA2000DB for AWD / View VmNotifyWin interface
// 
//    Rev 1.9   Jan 11 2000 13:34:28   DT14177
// made sure WIN32 was defined in order
// to eliminate compile problems for
// conditional directives
// 
//    Rev 1.8   May 24 1999 10:29:10   DTWK
// Added some #defines for Java JNI portability
//
//    Rev 1.7   Mar 23 1999 09:33:04   DT20842
// Added DIINT64 typedef
//
//    Rev 1.6   22 Feb 1999 14:14:20   DT14177
// more UNICODE stuff
//
//    Rev 1.5   18 Feb 1999 10:29:10   DT14177
// UNICODE
//
//    Rev 1.3   Jan 28 1999 14:07:30   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Jan 27 1999 11:39:04   DTWK
// Update with STD namespace macro
//
//    Rev 1.1   Dec 17 1998 17:17:22   DMUM
// Removed macro inclusions for platforms specific headers
//
//    Rev 1.0   Dec 14 1998 15:11:22   DMUM
//
//

// #endif // commonport_h

