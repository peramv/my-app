/*****************************************************************************/
//
//  COPYRIGHT:
//
//          The computer systems, procedures, data bases and programs
//          created and maintained by DST Systems, Inc., are proprietary
//          in nature and as such are confidential.  Any unauthorized
//          use or disclosure of such information may result in civil
//          liabilities.
//
//          Copyright 1993 by DST Systems, Inc.
//          All Rights Reserved.
//
//
//  FILE:   $Workfile:   VMDLL.H  $
//
//  AUTHOR: Joel Trigger
//
//  DATE:   05/24/93
//
//  DESCRIPTION:
//     This file contains the internal definitions and function prototypes
//  used by View Manager/NT.
//
//  $Log:   Y:/VCS/DSTCProjects/3rdParty/infra/inc/win32/VMDLL.H-arc  $
//
//   Rev 1.0   Jul 05 2002 10:15:30   SMITHDAV
//Initial revision.
// 
//    Rev 1.4   Jul 16 1997 12:48:24   DBWR
// AWD/View 1.5.0.0 Production Release
//
//    Rev 1.3   May 09 1997 12:16:06   djwb
// changed max open attempts to 50 from 300
// changed VMFILE definition for 32 bit file IO
// added fnSetMemTrace prototype
//
//
//    Rev 1.2   Dec 12 1996 08:18:16   djwb
// changed VmCheckConnect to be WINAPI so outside users can check to see if an App is connected without actually calling the EXE like VmIsAppConnected does
//
//    Rev 1.1   Dec 05 1996 12:36:02   djwb
// changes to support vmshutdn functionality
//
//     Rev 1.0   Nov 04 1996 17:16:40   djwb
//  Initial revision.
//
/*****************************************************************************/

/*****************************/
/**  Macro Inclusion Guard  **/
/*****************************/

#ifndef VMDLL_H
#define VMDLL_H

#pragma pack( 4 )

#ifndef VM_H
#include "vm.h"
#endif

/***********************/
/**  General defines  **/
/***********************/

#define VM_MAX_CONNECTS              1000
#define VM_MAX_OPEN_ATTEMPTS         50

/**********************************************/
/**  Define memory options for fnAllocMem()  **/
/**********************************************/

#define VM_ALLOC_GIVEABLE    0x0001L
#define VM_ALLOC_GETTABLE    0x0002L
#define VM_ALLOC_COMMIT      0x0004L
#define VM_ALLOC_SUBALLOC    0x0008L

/*******************************/
/**  Define file handle type  **/
/*******************************/

typedef HANDLE VMFILE;

/************************************************/
/**  Define return value for VmCheckConnect()  **/
/************************************************/

#define VM_NO_CONNECTION    -1
#define VM_APP_NAME_IN_USE  -2

/****************************************/
/**  Return values for fnReadConfig()  **/
/****************************************/

#define READ_CFG_OK                0
#define READ_CFG_OPEN_ERR          1
#define READ_CFG_READ_ERR          2
#define READ_CFG_MEMORY_ERR        3
#define READ_CFG_SIGNATURE_ERR     4
#define READ_CFG_VERSION_ERR       5

/****************************************/
/**  Define connection list structure  **/
/****************************************/

typedef struct
{
  CHAR          szIdent[VM_IDENT_LEN+1];
  DWORD         pid;
  FILETIME      ft;
  VMCONNECT     vmReq;
  VMCONNECT     vmResp;
  HANDLE        hSlot;
  BOOL          fUsed;
  DWORD         pidExe;    // process id of the runtime exe
  FILETIME      ftExe;     // process start time of the runtime exe
} VMWHO, *PVMWHO;

/*******************************/
/**  Defines for VmConvert()  **/
/*******************************/

#define VMC_OK             0
#define VMC_NO_FILE        1
#define VMC_INVALID_FILE   2

#define VMC_LENGTH        32
#define VMC_LINE_BREAK    17

/***************************************/
/**  Function prototypes - VMDLLOS.C  **/
/***************************************/

VOID            fnInitSecurity     ( PSECURITY_ATTRIBUTES );
BOOL            fnVerifyProcessTime( LPFILETIME, LPFILETIME );
VOID            fnGetProcessTime   ( LPFILETIME );
DWORD           fnGetProcessId     ( VOID );
VOID            fnSendToQueue      ( PVMWHO, PVM, PVOID, ULONG, ULONG, BOOL );
VOID            VmLoadConfig       ( PVM );


//#if (defined(__IBMC__) || defined(__IBMCPP__))
//   extern PVOID  fnAllocMem         ( ULONG, ULONG );
//   extern PVOID  fnSubAllocMem      ( PVOID, ULONG );
//   extern BOOL   fnFreeMem          ( PVOID );
//   extern BOOL   fnSubFreeMem       ( PVOID, PVOID, ULONG );
//   extern BOOL   fnGetMem           ( PVOID );
//   extern BOOL   fnGiveMem          ( PVOID, DWORD );
//   extern BOOL   VmNotifyTarget     ( PVMCONNECT, char *, PVOID, ULONG );
//
//   extern VMFILE fnOpenFile         ( char *, BOOL );
//   extern BOOL   fnWriteToFile      ( VMFILE, char *, PVOID, ULONG );
//   extern VOID   fnCloseFile        ( VMFILE );
//   extern BOOL   fnReadFromFile     ( VMFILE, char *, PVOID, PUSHORT );
//   extern BOOL   fnGetFileName      ( char *, ULONG );
//   extern PVOID  fnGetNextRequest   ( HANDLE, PDWORD, PULONG, HANDLE, ULONG,
//                                 PBOOL );
//
//   extern VOID * fnReadSlot         ( HANDLE, PULONG );
//   extern HANDLE fnCreateSlot       ( char *, ULONG );
//   extern HANDLE fnOpenSlot         ( PVM, char *, BOOL );
//   extern BOOL   fnSendToSlot       ( PVM, HANDLE, char *, VOID *, ULONG );
//
//   extern BOOL   fnCreateQueue      ( PHANDLE, char *, PHANDLE );
//   extern BOOL   fnOpenQueue        ( PDWORD, PHANDLE, char * );
//   extern BOOL   fnCloseQueue       ( HANDLE, HANDLE );
//   extern BOOL   fnPostToQueue      ( HANDLE, ULONG, PVOID, ULONG );
//   extern BOOL   fnConfigConflict   ( char * );
//   extern UINT   fnFormatErrMsg     ( USHORT, ULONG, char *, BOOL, ... );
//#else
   PVOID  WINAPI   fnAllocMem         ( ULONG, ULONG );
   PVOID  WINAPI   fnSubAllocMem      ( PVOID, ULONG );
   BOOL   WINAPI   fnFreeMem          ( PVOID );
   BOOL   WINAPI   fnSubFreeMem       ( PVOID, PVOID, ULONG );
   BOOL   WINAPI   fnGetMem           ( PVOID );
   BOOL   WINAPI   fnGiveMem          ( PVOID, DWORD );
   BOOL   WINAPI   VmNotifyTarget     ( PVMCONNECT, char *, PVOID, ULONG );

   VMFILE WINAPI   fnOpenFile         ( char *, BOOL );
   BOOL   WINAPI   fnWriteToFile      ( VMFILE, char *, PVOID, ULONG );
   VOID   WINAPI   fnCloseFile        ( VMFILE );
   BOOL   WINAPI   fnReadFromFile     ( VMFILE, char *, PVOID, PUSHORT );
   BOOL   WINAPI   fnGetFileName      ( char *, ULONG );
   PVOID  WINAPI   fnGetNextRequest   ( HANDLE, PDWORD, PULONG, HANDLE, ULONG,
                                        PBOOL );

   VOID * WINAPI   fnReadSlot         ( HANDLE, PULONG );
   HANDLE WINAPI   fnCreateSlot       ( char *, ULONG );
   HANDLE WINAPI   fnOpenSlot         ( PVM, char *, BOOL );
   BOOL   WINAPI   fnSendToSlot       ( PVM, HANDLE, char *, VOID *, ULONG );

   BOOL   WINAPI   fnCreateQueue      ( PHANDLE, char *, PHANDLE );
   BOOL   WINAPI   fnOpenQueue        ( PDWORD, PHANDLE, char * );
   BOOL   WINAPI   fnCloseQueue       ( HANDLE, HANDLE );
   BOOL   WINAPI   fnPostToQueue      ( HANDLE, ULONG, PVOID, ULONG );
   BOOL   WINAPI   fnConfigConflict   ( char * );
   UINT   WINAPI   fnFormatErrMsg     ( USHORT, ULONG, char *, BOOL, ... );
   VOID   WINAPI   fnSetMemTrace      ( BOOL );
   BOOL   WINAPI   fnVerifyProcessId  ( DWORD );
   VOID   WINAPI   fnFormatName       ( char * );
//#endif

/*************************************/
/**  Function prototypes - VMDLL.C  **/
/*************************************/

SHORT   VmSearchConnect     ( char *, BOOL );
VOID    VmConnect           ( PVM );
VOID    VmDisConnect        ( PVM, SHORT );
VOID    VmNotify            ( PVM, SHORT );
VOID    VmInvokeTrace       ( PVM, SHORT );
VOID    VmDispose           ( PVM, SHORT );
VOID    VmShutdown          ( PVM, SHORT );
VOID    VmPrivate           ( PVM, SHORT );
VOID    VmAppAvail          ( PVM );

//#if (defined(__IBMC__) || defined(__IBMCPP__))
//   extern VOID    fnTrimSpace  ( char * );
//   extern USHORT  VmConvert    ( BYTE *, unsigned long, BOOL, char *, char * );
//#else
   SHORT   WINAPI VmCheckConnect( PVM );
   VOID    WINAPI fnTrimSpace  ( char * );
   USHORT  WINAPI VmConvert    ( BYTE *, unsigned long, BOOL, char *, char * );
//#endif

USHORT  VmLoadConvertFile   ( char * );

/****************************************/
/**  Function prototypes - VMDLLSND.C  **/
/****************************************/

VOID    VmSendToExe         ( PVM, SHORT );

/****************************************/
/**  Function prototypes - VMDLLMSG.C  **/
/****************************************/

VOID    VmErrorText         ( PVM );

/*************************************/
/**  Function prototypes - VMCFG.C  **/
/*************************************/

//#if (defined(__IBMC__) || defined(__IBMCPP__))
//   extern USHORT fnReadConfig        ( char *, PVOID );
//   extern VOID   fnFreeConfig        ( PVOID );
//#else
   USHORT WINAPI fnReadConfig        ( char *, PVOID );
   VOID   WINAPI fnFreeConfig        ( PVOID );
//#endif

/**************************************************/
/**  NO ENTRIES SHOULD EXIST BEYOND THIS #endif  **/
/**************************************************/

#pragma pack()

#endif
