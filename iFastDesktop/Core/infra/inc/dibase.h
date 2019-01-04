#ifndef DIBASE_H
#define DIBASE_H

#  pragma message( "including "__FILE__ )

static const I_CHAR *DI_BASE_CONDITION = I_( "DIBASE" );

//Begin DIOS
   //    Begin DllObj
#define DIBASE_DLL_LOAD_FAIL 1000 
#define DIBASE_FUNCTION_LOAD_FAIL 1001
   //    End DllObj

   //    Begin EventSemaphore
#define DIBASE_EVENTSEM_CREATE_FAIL 1100
#define DIBASE_EVENTSEM_OPEN_FAIL 1101
#define DIBASE_EVENTSEM_SET_FAIL 1102
#define DIBASE_EVENTSEM_WAIT_FAIL 1103
#define DIBASE_EVENTSEM_RESET_FAIL 1104
   //    End EventSemaphore

   //    Begin MutexSemaphore
#define DIBASE_MUTEXSEM_CREATE_FAIL 1200
#define DIBASE_MUTEXSEM_OPEN_FAIL 1201
#define DIBASE_MUTEXSEM_RELEASE_FAIL 1202
#define DIBASE_MUTEXSEM_WAIT_FAIL 1203
   //    End MutexSemaphore

   //    Begin ProgramStarter
#define DIBASE_PROCESS_CREATE_FAIL 1300
   //    End ProgramStarter
   
   //    Begin TransactPipeClient / TransactPipeServer
#define DIBASE_PIPE_INIT_FAIL 1400
#define DIBASE_OVERSIZE_BUFFER 1401
#define DIBASE_BAD_PACKET 1402
   //    End TransactPipeClient / TransactPipeServer

   //    Begin IPCClient / IPCServer
#define DIBASE_IPC_SYNCH_FAIL 1500
   //    End IPCClient / IPCServer
//End DIOS


//Begin DIVIEW
#define DIBASE_VMCONNECT_FAIL   10001
#define DIBASE_VMDISCONNECT_FAIL   10002
#define DIBASE_VMNOTIFYSEM_FAIL 10003
#define DIBASE_VMAPPREQUEST_FAIL 10004
#define DIBASE_VMNOTIFY_SUCCESS 10005
#define DIBASE_VMAPPREQUEST_SUCCESS 10007
#define DIBASE_VMREADRESPONSE_FAIL 10008
#define DIBASE_VMREQUEST_FAIL 10009
#define DIBASE_VIEW_RETURN_CODE 10010
#define DIBASE_VMREQUEST_INIT_FAIL 10011
#define DIBASE_VMREQUEST_WAIT_FAIL 10012
#define DIBASE_VMREQUEST_CALLBACK_ERROR_CONDITION 10013
#define DIBASE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN 10014
#define DIBASE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN 10015
#define DIBASE_VMAPPREQUEST_TIMEOUT 10016
//End DIVIEW


//Begin DIMTHSTR
#define DIBASE_BUFFER_SIZE_TOO_SMALL 14000
#define DIBASE_DIVIDE_BY_ZERO 14001
//End DIMTHSTR

//Begin PARSE_IDI
#define DIBASE_PARSE_IDI_MISSING_TERMINATOR  15000
//End PARSE_IDI

#endif //#ifndef DIBase_h


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



