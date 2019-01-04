/*
 *   COMPONENT_NAME: somk
 *
 *   ORIGINS: 27
 *
 *
 *   10H9767, 10H9769  (C) COPYRIGHT International Business Machines Corp. 1992,1994
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/* %Z% %I% %W% %G% %U% [%H% %T%] */

/*
 */

/*
 *    SOMBTYPE.H
 *    SOM Base Data Types
 */

#ifndef sombtype_h
#define sombtype_h

#include <stdarg.h>
#include <stddef.h>

/*--------------------------------------------------------------
 * Basic SOM data types for C and C++
 */
/* -- Generic SOM Method Procedure Pointers */

typedef void* SOMLINK somMethodProc(void*);
typedef somMethodProc SOMDLINK *somMethodPtr;
typedef void SOMLINK somTP_somClassInitFunc(void *somSelf);

#ifndef NULL
#define NULL 0
#endif

typedef char integer1;
typedef short integer2;
typedef unsigned short uinteger2;
typedef long integer4;
typedef unsigned long uinteger4;
typedef float float4;
typedef double float8;
typedef char *zString;                 /* NULL terminated string */
typedef char *fString;                 /* non-terminated string  */
typedef char **somId;
typedef void *somToken;                /* Uninterpretted value   */

#ifndef SOM_BOOLEAN
  #define SOM_BOOLEAN
  typedef unsigned char boolean;  
#endif /* SOM_BOOLEAN */

#define SOM_DynamicMethod  1
#define SOM_StaticMethod   0

/*
 *    Comment macros for arguments
 */
#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif


#endif /* sombtype_h */
