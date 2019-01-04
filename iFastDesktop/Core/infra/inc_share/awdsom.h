#include "exceptn.xh"
#include "awdassrt.h" // renamed "error.h" because of conflict with MSDEV

#define LEFT_END   0       // for editfunc.c functions
#define RIGHT_END  1       // for editfunc.c functions
#define BOTH_ENDS  2       // for editfunc.c functions

#define error( ev, exceptiontype, msg, rc )              \
        createexception( ev, exceptiontype, msg, rc,     \
                          __FILE__, __LINE__ )

#define awdAssert( fFlag, exception, msg, rc )       \
        fnAwdAssert( fFlag, exception, msg, rc, __FILE__, __LINE__ )

void memstr( char* psz1, char* pcharbuffer, unsigned short uslength );
char* strsafecpy( char* psz1, char* psz2, int nmaxlength );
int strsafecmp( char* psz1, char* psz2, int nmaxlength );
unsigned short fnStrip( char* szStrip, char* szStripChars );
char* fnPadStr( char* szPad, char chPad, unsigned short usPadDir, unsigned short usSize );
void fnRevStr( char* szRevStr );
unsigned short fnTrim( char* szTrimStr, char* szTrimChars, unsigned short usDirection );
unsigned short fnCStrip( char* szStrip, char* szKeepChars );
unsigned long fnCopyFile( char* pszDestination, char* pszSource );
int fnFileExists( char* pszFullFileName );
int fnCopyCsdFile( char* pszCsd );
int fnVerifyDrive( char cDrive );
