//#include <som.h>
#include <exceptn.xh>


void  createexception( Environment*, AWDException_EXCEPTION_TYPE, char *, unsigned short, char *, int );

void  createexception( Environment*, AWDException_EXCEPTION_TYPE, unsigned short, unsigned short, char *, int );

void fnAwdAssert(  int fFlag,
                   AWDException_EXCEPTION_TYPE exception,
                   char *pszErrorMsg,
                   unsigned short rc,
                   char* file,
                   int line );

void fnAwdAssert( int fFlag,
                   AWDException_EXCEPTION_TYPE exception,
                   unsigned short MsgID,
                   unsigned short rc,
                   char* file,
                   int line );
