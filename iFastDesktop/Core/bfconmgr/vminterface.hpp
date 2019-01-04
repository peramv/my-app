#pragma once

#include <bfutil\dll_interface.hpp>

#include <win32\vm.h>
#include <win32\vmdst.h>
#include <win32\vmdll.h>

// From VMDST.HPP
class VMDll_Interface : public Dll_Interface
{
private:
   VMDll_Interface();
   virtual bool load();

public:
   virtual ~VMDll_Interface();

public:
   static VMDll_Interface& get();
   VOID ViewMgr( PVOID u1 );
   BOOL ViewErrorString( USHORT u1, USHORT u2, PSZ u3 );
   USHORT VmNotifySem( PSZ u1, PSZ u2, USHORT u3, PBYTE u4, ULONG u5, PSZ u6, ULONG u7 );
   USHORT VmNotifyQueue( PSZ u1, PSZ u2, USHORT u3, PSZ u4, ULONG u5 );
   USHORT VmNotifyWin( PSZ u1, HWND u2, ULONG u3, USHORT u4, PBYTE u5, ULONG u6, PSZ u7, ULONG u8 );
   USHORT VmConnectApp( PSZ u1, PSZ u2, ULONG u3 );
   USHORT VmDisconnectApp( PSZ u1, PSZ u2, ULONG u3 );
   USHORT VmAppRequest( PSZ u1, PSZ u2, PSZ u3, PSZ u4, ULONG u5, PBYTE u6, ULONG u7, ULONG u8, USHORT u9, PSZ u10, ULONG u11 );
   USHORT VmAppRequestProt( PSZ u1, PSZ u2, PSZ u3, PSZ u4, ULONG u5, PBYTE u6, ULONG u7, ULONG u8, USHORT u9, PSZ u10, ULONG u11, PBYTE u12, ULONG u13 );
   USHORT VmAppRequestPriv( PSZ u1, USHORT u2, PSZ u3, PBYTE u4, ULONG u5, ULONG u6, USHORT u7, PSZ u8, ULONG u9 );
   USHORT VmAppRequestPrivProt( PSZ u1, USHORT u2, PSZ u3, PBYTE u4, ULONG u5, ULONG u6, USHORT u7, PSZ u8, ULONG u9, PBYTE u10, ULONG u11 );
   USHORT VmShutdownExe( USHORT u1, PSZ u2, ULONG u3 );
   BOOL VmErrorMsg( PSZ u1, USHORT u2, PBYTE u3, ULONG u4 );
   BOOL VmExtractResp( PBYTE u1, PVMDSTRESP u2 );
   USHORT VmIsAppConnected( PSZ u1 );
   PVMAPPRESP VmReadResponse( char* u1 );
   BOOL VmFree( PVOID u1 );

private:
   typedef VOID ( WINAPI *PFN_VIEWMGR)( PVOID );
   typedef BOOL ( WINAPI *PFN_VIEWERRORSTRING )( USHORT, USHORT, PSZ );
   typedef USHORT ( WINAPI *PFN_VMNOTIFYSEM )( PSZ, PSZ, USHORT, PBYTE, ULONG, PSZ, ULONG );
   typedef USHORT ( WINAPI *PFN_VMNOTIFYQUEUE )( PSZ, PSZ, USHORT, PSZ, ULONG );
   typedef USHORT ( WINAPI *PFN_VMNOTIFYWIN )( PSZ, HWND, ULONG, USHORT, PBYTE, ULONG, PSZ, ULONG );
   typedef USHORT ( WINAPI *PFN_VMCONNECTAPP )( PSZ, PSZ, ULONG );
   typedef USHORT ( WINAPI *PFN_VMDISCONNECTAPP )( PSZ, PSZ, ULONG );

   typedef USHORT ( WINAPI *PFN_VMAPPREQUEST )( PSZ, PSZ, PSZ, PSZ, ULONG, PBYTE, ULONG, ULONG, USHORT, PSZ, ULONG );
   typedef USHORT ( WINAPI *PFN_VMAPPREQUESTPROT ) ( PSZ, PSZ, PSZ, PSZ, ULONG, PBYTE, ULONG, ULONG, USHORT, PSZ, ULONG, PBYTE, ULONG );
   typedef USHORT ( WINAPI *PFN_VMAPPREQUESTPRIV ) ( PSZ, USHORT, PSZ, PBYTE, ULONG, ULONG, USHORT, PSZ, ULONG );
   typedef USHORT ( WINAPI *PFN_VMAPPREQUESTPRIVPROT ) ( PSZ, USHORT, PSZ, PBYTE, ULONG, ULONG, USHORT, PSZ, ULONG, PBYTE, ULONG );
   typedef USHORT ( WINAPI *PFN_VMSHUTDOWNEXE ) ( USHORT, PSZ, ULONG );
   typedef BOOL ( WINAPI *PFN_VMERRORMSG ) ( PSZ, USHORT, PBYTE, ULONG );
   typedef BOOL ( WINAPI *PFN_VMEXTRACTRESP ) ( PBYTE, PVMDSTRESP );
   typedef USHORT ( WINAPI *PFN_VMISAPPCONNECTED ) ( PSZ );
   typedef PVMAPPRESP ( WINAPI *PFN_VMREADRESPONSE )( char * );
   typedef BOOL ( WINAPI *PFN_VMFREE )( VOID * );

   PFN_VIEWMGR pfnViewMgr_;
   PFN_VIEWERRORSTRING pfnViewErrorString_;
   PFN_VMNOTIFYSEM pfnVmNotifySem_;
   PFN_VMNOTIFYQUEUE pfnVmNotifyQueue_;
   PFN_VMNOTIFYWIN pfnVmNotifyWin_;
   PFN_VMCONNECTAPP pfnVmConnectApp_;
   PFN_VMDISCONNECTAPP pfnVmDisconnectApp_;
   PFN_VMAPPREQUEST pfnVmAppRequest_;
   PFN_VMAPPREQUESTPROT pfnVmAppRequestProt_;
   PFN_VMAPPREQUESTPRIV pfnVmAppRequestPriv_;
   PFN_VMAPPREQUESTPRIVPROT pfnVmAppRequestPrivProt_;;
   PFN_VMSHUTDOWNEXE pfnVmShutdownExe_;
   PFN_VMERRORMSG pfnVmErrorMsg_;
   PFN_VMEXTRACTRESP pfnVmExtractResp_;
   PFN_VMISAPPCONNECTED pfnVmIsAppConnected_;
   PFN_VMREADRESPONSE pfnVmReadResponse_;
   PFN_VMFREE pfnVmFree_;
};

class VMDST_Interface : public Dll_Interface
{
private:
   VMDST_Interface();
   virtual bool load();

public:
   virtual ~VMDST_Interface();

public:
   static VMDST_Interface& get();

   SHORT VmSearchConnect( char* u1, BOOL u2 );
   VOID  VmConnect( PVM u1 );
   VOID  VmDisconnect( PVM u1, SHORT u2 );
   VOID  VmNotify( PVM u1, SHORT u2 );
   VOID  VmInvokeTrace( PVM u1, SHORT u2 );
   VOID  VmDispose( PVM u1, SHORT u2 );
   VOID  VmShutdown( PVM u1, SHORT u2 );
   VOID  VmPrivate( PVM u1, SHORT u2 );
   VOID  VmAppAvail( PVM u1 );

private:
   // From VMDLL.HPP
   typedef SHORT   ( *PFN_VMSEARCHCONNECT    ) ( char *, BOOL );
   typedef VOID    ( *PFN_VMCONNECT          ) ( PVM );
   typedef VOID    ( *PFN_VMDISCONNECT       ) ( PVM, SHORT );
   typedef VOID    ( *PFN_VMNOTIFY           ) ( PVM, SHORT );
   typedef VOID    ( *PFN_VMINVOKETRACE      ) ( PVM, SHORT );
   typedef VOID    ( *PFN_VMDISPOSE          ) ( PVM, SHORT );
   typedef VOID    ( *PFN_VMSHUTDOWN         ) ( PVM, SHORT );
   typedef VOID    ( *PFN_VMPRIVATE          ) ( PVM, SHORT );
   typedef VOID    ( *PFN_VMAPPAVAIL         ) ( PVM );

   PFN_VMSEARCHCONNECT    pfnVmSearchConnect_;
   PFN_VMCONNECT          pfnVmConnect_;
   PFN_VMDISCONNECT       pfnVmDisconnect_;
   PFN_VMNOTIFY           pfnVmNotify_;
   PFN_VMINVOKETRACE      pfnVmInvokeTrace_;
   PFN_VMDISPOSE          pfnVmDispose_;
   PFN_VMSHUTDOWN         pfnVmShutdown_;
   PFN_VMPRIVATE          pfnVmPrivate_;
   PFN_VMAPPAVAIL         pfnVmAppAvail_;
};


