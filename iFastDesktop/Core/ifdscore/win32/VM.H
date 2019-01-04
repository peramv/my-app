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
//  FILE:   $Workfile:   VM.H  $
//
//  AUTHOR: Joel Trigger
//
//  DATE:   05/24/93
//
//  DESCRIPTION:
//     This file contains the internal definitions and function prototypes
//  used by View Manager/NT.
//
//  $Log:   Y:/VCS/DSTCProjects/3rdParty/infra/inc/win32/VM.H-arc  $
//
//   Rev 1.0   Jul 05 2002 10:15:28   SMITHDAV
//Initial revision.
// 
//    Rev 1.11   Sep 18 1997 17:52:02   DBWR
// Changed version text to 1.5.0.2
// 
//    Rev 1.10   Aug 28 1997 16:44:36   DBWR
// New revision of AWD/View (1.5.0.1)
//
//    Rev 1.9   Jul 16 1997 12:46:00   DBWR
// AWD/View 1.5.0.0 Production Release
// Updated the version information
//
//
//    Rev 1.8   May 09 1997 11:52:50   djwb
// changed szEvent to szSem to match other
// structures.
//
//    Rev 1.7   Apr 29 1997 15:08:46   djwb
// changed version to 1.5.0.0 Beta 4
// changed VMPRIV structure to use the
// name of the semaphore instead of the
// handle.
//
//    Rev 1.6   Feb 18 1997 12:02:56   djwb
//
//
//    Rev 1.4   Feb 04 1997 17:06:46   djwb
// incremented to BETA 3
//
//    Rev 1.3   Dec 05 1996 12:36:00   djwb
// changes to support vmshutdn functionality
//
//     Rev 1.2   Nov 11 1996 17:15:56   djwb
//  changed version text to RK1
//
//     Rev 1.1   Nov 11 1996 17:06:44   djwb
//  changed version to 1.5.0
//
//     Rev 1.0   Nov 04 1996 17:16:40   djwb
//  Initial revision.
//
/*****************************************************************************/

/*****************************/
/**  MACRO INCLUSION GUARD  **/
/*****************************/

#ifndef VM_H
#define VM_H

#pragma pack( 4 )

/******************************/
/**  Define version numbers  **/
/******************************/

#define VM_VERSION10          10
#define VM_VERSION11          11
#define VM_VERSION12          12
#define VM_VERSION13          13
#define VM_VERSION            13
#define VM_VERSION_TEXT       "1.5.0.2"

/**********************************************/
/**  Define View Manager/NT operation codes  **/
/**********************************************/

#define VM_OP_CONNECT            1
#define VM_OP_DISCONNECT         2
#define VM_OP_NOTIFY             3
#define VM_OP_REQUEST            4
#define VM_OP_ADV_REQUEST        5
#define VM_OP_TRACE              6
#define VM_OP_DISASTER           7
#define VM_OP_ERROR_TEXT         8
#define VM_OP_APP_AVAIL          9
#define VM_OP_REQUEST_DIRECT    10
#define VM_OP_REQUEST_PROTOCOL  11
#define VM_OP_VERSION           12
#define VM_OP_PRIVATE           13
#define VM_OP_REQUEST_PRIVATE   14
#define VM_OP_REQUEST_PRIVPROT  15
#define VM_OP_DISPOSE           16
#define VM_OP_SHUTDOWN          17

/**********************************************/
/**  Define bit flags for operation options  **/
/**********************************************/

#define VM_NOTIFY_REQUEST       0x0001
#define VM_NOTIFY_RESPONSE      0x0002
#define VM_NOTIFY_SEM           0x0004
#define VM_NOTIFY_WIN           0x0008
#define VM_NOTIFY_PIPE          0x0010
#define VM_NOTIFY_SLOT          0x0020
#define VM_BUFF_DEFINED         0x0040
#define VM_BUFF_ALLOC           0x0080
#define VM_TRACE_API            0x0100
#define VM_TRACE_API_AND_DATA   0x0200

/********************************************/
/**  Define View Manager/NT return values  **/
/********************************************/

#define VM_P_OK                              0
#define VM_P_WARNING                         1
#define VM_P_ERROR                           2

#define VM_S_OK                              0
#define VM_S_LOG_MESSAGE                     1
#define VM_S_MEMORY_ALLOCATE                 2
#define VM_S_MEMORY_FREE                     3
#define VM_S_MEMORY_GIVE                     4
#define VM_S_UNABLE_TO_OPEN_QUEUE            5
#define VM_S_ERROR_WRITE_TO_QUEUE            6
#define VM_S_INVALID_OPERATION               7
#define VM_S_NO_CONNECTION                   8
#define VM_S_ALREADY_CONNECTED               9
#define VM_S_INVALID_VERSION                10
#define VM_S_NO_SUCH_TARGET                 11
#define VM_S_TARGET_NO_RECEIVE              12
#define VM_S_TARGET_BUFF_TOO_SMALL          13
#define VM_S_CANT_ACCESS_TARGET_BUFF        14
#define VM_S_UNABLE_TO_GET_ERROR_TEXT       15
#define VM_S_UNABLE_TO_NOTIFY_TARGET        16
#define VM_S_UNABLE_TO_START_VIEW_SERVER    17
#define VM_S_CONFIG_NOT_FOUND               18
#define VM_S_CONFIG_INVALID_VERSION         19
#define VM_S_CONFIG_INVALID_SIGNATURE       20
#define VM_S_CONFIG_OPEN_ERROR              21
#define VM_S_CONFIG_READ_ERROR              22
#define VM_S_UNABLE_TO_FIND_VIEW_SERVER     23
#define VM_S_NO_RESPONSE_NOTIFICATION       24
#define VM_S_VIEW_NOT_CONFIGURED            25
#define VM_S_APP_NAME_IN_USE                26
#define VM_S_HOST_THREAD_TERMINATED         27
#define VM_S_PROTOCOL_ERROR                 28
#define VM_S_TARGET_AND_HOST                29
#define VM_S_TARGET_HOST_OR_VIEW            30
#define VM_S_OPERATION_NOT_AVAILABLE        31
#define VM_S_NO_DEFINED_BUFFER              32
#define VM_S_NO_DEFINED_BUFFER_PTR          33
#define VM_S_NO_WINDOW_HANDLE               34
#define VM_S_NO_WINDOW_MESSAGE              35
#define VM_S_NO_NOTIFICATION_TYPE           36
#define VM_S_NO_NOTIFICATION_METHOD         37
#define VM_S_NO_BUFFER_TYPE                 38
#define VM_S_TIMEOUT                        39
#define VM_S_NO_DATA_LEN                    40
#define VM_S_USER_EXIT_ERROR                41
#define VM_S_NO_NOTIFICATION_BUFFER_LEN     42
#define VM_S_EXE_TERMINATED                 43
#define VM_S_CONFIG_CONFLICT                44
#define VM_S_STARTUP_ERROR                  45
#define VM_S_INVALID_PRIVATE                46
#define VM_S_INVALID_HOST                   47
#define VM_S_PRIV_SEMAPHORE                 48
#define VM_S_NO_CONNECTION_NUM              49
#define VM_S_VIEW_TO_APP                    50
#define VM_S_INVALID_OWNER                  51
#define VM_S_INVALID_CONNECTION_NUM         52
#define VM_S_PROTOCOL_NO_COMMANDS           53
#define VM_S_PROTOCOL_COMMAND_ERROR         54
#define VM_S_PROTOCOL_NOT_FOUND             55
#define VM_S_UNABLE_TO_LOAD_PROTOCOL        56
#define VM_S_INVALID_PROTOCOL_MODULE        57
#define VM_S_CANNOT_SPECIFY_DEFAULT         58
#define VM_S_INVALID_PARAMETER_LENGTH       59
#define VM_S_STARTUP_TIMEOUT                60
#define VM_S_THREADS_STILL_ACTIVE           61

/*********************/
/**  Define limits  **/
/*********************/

#define VM_FILE_LEN      256           // File specification length
#define VM_NAME_LEN      8             // Short name length
#define VM_NAME_LEN_TXT  "8"           // Short name length text format
#define VM_DESC_LEN      80            // Long description length
#define VM_DLL_LEN       32            // DLL module name length
#define VM_PROC_LEN      32            // DLL Procedure name length
#define VM_SIG_LEN       8             // Configuration signature length

/***************************/
/**  Define data lengths  **/
/***************************/

#define VM_IDENT_LEN     8
#define VM_ACCESS_LEN   65
#define VM_MSG_LEN     256

/*******************************************/
/**  Define name for View Manager SERVER  **/
/*******************************************/

#define VM_SERVER_NAME       "VMSERVER"

/*************************************************************/
/**  Define value for Request Identifier for a new request  **/
/*************************************************************/

#define VM_NEW_REQUEST       0L

#define VM_SHUTDOWN_NORMAL   0
#define VM_SHUTDOWN_ABNORMAL 1

/**************************************/
/**  Define queue record operations  **/
/**************************************/

#define QUEUE_REC_REQ               0
#define QUEUE_REC_THREAD_TERM       1
#define QUEUE_REC_MAIN_TERM         2
#define QUEUE_REC_TRACE             3
#define QUEUE_REC_PRIVATE           4
#define QUEUE_REC_CONNECT           5
#define QUEUE_REC_DISPOSE           6
#define QUEUE_REC_SHUTDOWN          7

/***********************************************/
/**  Define COMMANDS for PRIVATE CONNECTIONS  **/
/***********************************************/

#define PUBLIC_CONNECTION        0

#define VM_PRIV_CREATE           0x0001
#define VM_PRIV_DESTROY          0x0002
#define VM_PRIV_CONNECT          0x0004
#define VM_PRIV_DISCONNECT       0x0008

/**************************************************/
/**  Define VIEW application function structure  **/
/**************************************************/

typedef struct
{
  CHAR    szRemote[65];           // Name of remote computer
  PSZ     pszFilePath;            // Path where to look for data files
  CHAR    szViewName[9];          // View Name
  PBYTE   pbBuff;                 // Incoming buffer pointer
  ULONG   ulBuffSize;             // Incoming buffer defined size
  ULONG   ulDataSize;             // Incoming buffer data length
  ULONG   ulUserData;             // User data
  PBYTE   pbRetBuff;              // Returned buffer pointer
  ULONG   ulRetBuffSize;          // Returned buffer data length
  BOOL    fFreeRetBuff;           // Free the return buffer
} VSERV, *PVSERV;

/*****************************************/
/**  Define operation header structure  **/
/*****************************************/

typedef struct
{
  USHORT         usOpCode;
  USHORT         usVersion;
  USHORT         usRcPrimary;
  USHORT         usRcSecondary;
  CHAR           szIdent[VM_IDENT_LEN+1];
  PSZ            pszErrMsg;
  ULONG          ulMsgSize;
} VM, *PVM;

/********************************************/
/**  Define user exit "module" structures  **/
/********************************************/

typedef BOOL (WINAPI *PFNVSERV)(PVSERV);

typedef struct
{
  CHAR       szModule[VM_DLL_LEN+1];   // User exit module name
  CHAR       szProc[VM_PROC_LEN+1];    // User exit procedure name
  HMODULE    hmod;
  PFNVSERV   pfn;
} VMMOD, *PVMMOD;

/******************************************/
/**  Define CONNECT operation structure  **/
/******************************************/

typedef struct
{
  VM             Vm;
} VMCON, *PVMCON;

/*********************************************/
/**  Define DISCONNECT operation structure  **/
/*********************************************/

typedef struct
{
  VM             Vm;
} VMDISCON, *PVMDISCON;

/*******************************************/
/**  Define SHUTDOWN operation structure  **/
/*******************************************/

typedef struct
{
  VM             Vm;
  USHORT         usShutdownType;
  CHAR           szSem[VM_ACCESS_LEN+1];
} VMSHUTDOWN, *PVMSHUTDOWN;

/*****************************************/
/**  Define NOTIFY operation structure  **/
/*****************************************/

typedef struct
{
  VM             Vm;
  USHORT         usType;
  USHORT         usMode;
  PSZ            pszSem;
  HWND           hwnd;
  ULONG          ulMsg;
  PSZ            pszSlot;
  PSZ            pszPipe;
  PBYTE          pbBuff;
  ULONG          ulBuffSize;
  PSZ            pszBuffSem;
} VMNOTIFY, *PVMNOTIFY;

/*************************************************/
/**  Define SIMPLE REQUEST operation structure  **/
/*************************************************/

typedef struct
{
  VM             Vm;
  CHAR           szViewName[VM_IDENT_LEN+1];
  CHAR           szTargetApp[VM_IDENT_LEN+1];
  CHAR           szHost[VM_IDENT_LEN+1];
  ULONG          ulReqIdent;
  ULONG          ulUserData;
  USHORT         usTimeout;
  PBYTE          pbBuff;
  ULONG          ulBuffSize;
} VMREQ, *PVMREQ;

/******************************************************************/
/**  Define SIMPLE REQUEST operation structure with direct send  **/
/******************************************************************/

typedef struct
{
  VM             Vm;
  CHAR           szViewName[VM_IDENT_LEN+1];
  CHAR           szTargetApp[VM_IDENT_LEN+1];
  CHAR           szHost[VM_IDENT_LEN+1];
  CHAR           szSourceApp[VM_IDENT_LEN+1];
  ULONG          ulReqIdent;
  ULONG          ulUserData;
  PBYTE          pbBuff;
  ULONG          ulBuffSize;
} VMREQD, *PVMREQD;

/***************************************************/
/**  Define PROTOCOL REQUEST operation structure  **/
/***************************************************/

typedef struct
{
  VM             Vm;
  CHAR           szViewName[VM_IDENT_LEN+1];
  CHAR           szTargetApp[VM_IDENT_LEN+1];
  CHAR           szHost[VM_IDENT_LEN+1];
  ULONG          ulReqIdent;
  ULONG          ulUserData;
  USHORT         usTimeout;
  PBYTE          pbBuff;
  ULONG          ulBuffSize;
  PBYTE          pbProtBuff;
  ULONG          ulProtBuffSize;
} VMREQPROT, *PVMREQPROT;

/*************************************************************/
/**  Define PRIVATE CONNECTION REQUEST operation structure  **/
/*************************************************************/

typedef struct
{
  VM             Vm;
  CHAR           szViewName[VM_IDENT_LEN+1];
  USHORT         usConnection;
  ULONG          ulUserData;
  USHORT         usTimeout;
  PBYTE          pbBuff;
  ULONG          ulBuffSize;
} VMPRIVREQ, *PVMPRIVREQ;

/****************************************************************/
/**  Define PRIVATE CONNECTION REQUEST WITH PROTOCOL OVERRIDE  **/
/**  operation structure                                       **/
/****************************************************************/

typedef struct
{
  VM             Vm;
  CHAR           szViewName[VM_IDENT_LEN+1];
  USHORT         usConnection;
  ULONG          ulUserData;
  USHORT         usTimeout;
  PBYTE          pbBuff;
  ULONG          ulBuffSize;
  PBYTE          pbProtBuff;
  ULONG          ulProtBuffSize;
} VMPRIVREQPROT, *PVMPRIVREQPROT;

/******************************************/
/**  Define VERSION operation structure  **/
/******************************************/

typedef struct
{
  VM             Vm;
  CHAR          *pszVersion;
  CHAR          *pszConfigFile;
} VMVERS, *PVMVERS;

/***************************************************/
/**  Define ADVANCED REQUEST operation structure  **/
/***************************************************/

typedef struct
{
  VM             Vm;
  CHAR           szViewName[VM_IDENT_LEN+1];
  CHAR           szTargetApp[VM_IDENT_LEN+1];
  BOOL           fSendAsReturnedView;
  CHAR           szHost[VM_IDENT_LEN+1];
  ULONG          ulUserData;
  USHORT         usTimeout;
  PBYTE          pbBuff;
  ULONG          ulBuffSize;
  USHORT         usMode;
  PSZ            pszSem;
  HWND           hwnd;
  ULONG          ulMsg;
  PSZ            pszSlot;
  PSZ            pszPipe;
  PBYTE          pbNotifyBuff;
  ULONG          ulNotifyBuffSize;
  PSZ            pszBuffSem;
} VMADVREQ, *PVMADVREQ;

/******************************************/
/**  Define TRACING operation structure  **/
/******************************************/

typedef struct
{
  VM             Vm;
  CHAR           szSem[VM_ACCESS_LEN+1];
  BOOL           fEnable;
  USHORT         fusTrace;
  CHAR           szTraceFile[257];
  CHAR           szTraceApp[9];
  CHAR           szTraceView[9];
  CHAR           szTraceHost[9];
} VMTRACE, *PVMTRACE;

/************************************************/
/**  Define DISASTER MODE operation structure  **/
/************************************************/

typedef struct
{
  VM             Vm;
  BOOL           fEnable;
} VMDISASTER, *PVMDISASTER;

/*********************************************/
/**  Define ERROR TEXT operation structure  **/
/*********************************************/

typedef struct
{
  VM             Vm;
  USHORT         usRcSecondary;
  PCHAR          pchBuff;
  ULONG          ulBuffSize;
} VMERRTEXT, *PVMERRTEXT;

/***************************************************/
/**  Define COMMAND PRIVATE CONNECTION structure  **/
/***************************************************/

typedef struct
{
  VM             Vm;
  CHAR           szViewName[VM_IDENT_LEN+1];
  CHAR           szHost[VM_IDENT_LEN+1];
  USHORT         usConnection;
  USHORT         usCommand;
  CHAR           szSem[VM_ACCESS_LEN+1];
} VMPRIV, *PVMPRIV;

/************************************************/
/**  Define APP AVAILABLE operation structure  **/
/************************************************/

typedef struct
{
  VM             Vm;
  USHORT         usRcSecondary;
  CHAR           szTargetApp[VM_IDENT_LEN+1];
} VMAPPAVAIL, *PVMAPPAVAIL;

/***********************************************/
/**  Define connection information structure  **/
/***********************************************/

typedef struct
{
  CHAR           szIdent[VM_IDENT_LEN+1];
  DWORD          pid;
  USHORT         usType;
  USHORT         usMode;
  CHAR           szSem[VM_ACCESS_LEN+1];
  HWND           hwnd;
  ULONG          ulMsg;
  CHAR           szSlot[VM_ACCESS_LEN+1];
  CHAR           szPipe[VM_ACCESS_LEN+1];
  PBYTE          pbBuff;
  ULONG          ulBuffSize;
  CHAR           szBuffSem[VM_ACCESS_LEN+1];
  CHAR           szAppSlot[VM_ACCESS_LEN+1];
  HANDLE         hSlot;
  UINT           uiId;
} VMCONNECT, *PVMCONNECT;

/*************************************************************/
/**  Define structure for passed VIEW request buffer setup  **/
/*************************************************************/

typedef struct
{
  VMCONNECT   vmTarget;
  CHAR        szViewName[VM_IDENT_LEN+1];
  CHAR        szTargetApp[VM_IDENT_LEN+1];
  CHAR        szHost[VM_IDENT_LEN+1];
  ULONG       ulReqIdent;
  ULONG       ulUserData;
  USHORT      usTimeout;
  ULONG       ulStartTime;
  ULONG       ulBuffSize;
  PBYTE       pbBuff;
  PVMMOD      pvmModOut;
  PVMMOD      pvmModIn;
  PVMMOD      pvmModLocal;
  PVMMOD      pvmModPre;
  PVMMOD      pvmModPost;
  PBYTE       pbProtBuff;
  ULONG       ulProtBuffSize;
  USHORT      usConnectionNum;
} VMVIEWREQ, *PVMVIEWREQ;

/****************************************************************/
/**  Define structure for incoming requests to an application  **/
/****************************************************************/

typedef struct
{
  CHAR        szIdent[VM_IDENT_LEN+1];
  CHAR        szViewName[VM_IDENT_LEN+1];
  ULONG       ulReqIdent;
  ULONG       ulBuffSize;
  PBYTE       pbBuff;
} VMAPPREQ, *PVMAPPREQ;

/******************************************************************/
/**  Define structure for returned view data for an application  **/
/******************************************************************/

typedef struct
{
  CHAR        szIdent[VM_IDENT_LEN+1];
  CHAR        szViewName[VM_IDENT_LEN+1];
  CHAR        szHost[VM_IDENT_LEN+1];
  USHORT      usRcPrimary;
  USHORT      usRcSecondary;
  ULONG       ulBuffSize;
  PBYTE       pbBuff;
} VMAPPRESP, *PVMAPPRESP;

/********************************/
/**  Define DISPOSE structure  **/
/********************************/

typedef struct
{
  VM             Vm;
  CHAR           szViewName[VM_IDENT_LEN+1];
  CHAR           szHost[VM_IDENT_LEN+1];
  USHORT         usNumDisposed;
  CHAR           szSem[VM_ACCESS_LEN+1];
} VMDISP, *PVMDISP;

/***********************************/
/**  Define SHARED MEM structure  **/
/***********************************/

typedef struct
{
  VM             Vm;
  CHAR           szMemName[256];
  ULONG          ulDataLen;
} VMSHMEM, *PVMSHMEM;

/******************************************************/
/**  View Manager/NT entry point Function Prototype  **/
/******************************************************/

//#if (defined(__IBMC__) || defined(__IBMCPP__))
//   extern VOID        ViewMgr           ( PVOID );
//   extern CHAR *      VmGetHostList     ( CHAR *, ULONG );
//   extern VOID        VmFreeHostList    ( CHAR * );
//
//   extern BOOL        VmFree            ( VOID * );
//   extern PVMAPPREQ   VmReadRequest     ( char * );
//   extern PVMAPPRESP  VmReadResponse    ( char * );
//   extern PVMAPPREQ   VmReadRequestId   ( WPARAM );
//   extern PVMAPPRESP  VmReadResponseId  ( WPARAM );
//#else
   VOID        WINAPI ViewMgr           ( PVOID );
   CHAR *      WINAPI VmGetHostList     ( CHAR *, ULONG );
   VOID        WINAPI VmFreeHostList    ( CHAR * );

   BOOL        WINAPI VmFree            ( VOID * );
   PVMAPPREQ   WINAPI VmReadRequest     ( char * );
   PVMAPPRESP  WINAPI VmReadResponse    ( char * );
   PVMAPPREQ   WINAPI VmReadRequestId   ( WPARAM );
   PVMAPPRESP  WINAPI VmReadResponseId  ( WPARAM );
//#endif

/**************************************************/
/**  NO ENTRIES SHOULD EXIST BEYOND THIS #endif  **/
/**************************************************/

#pragma pack()

#endif
