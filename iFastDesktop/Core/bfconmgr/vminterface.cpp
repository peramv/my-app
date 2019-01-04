#include <srcprag.h>
#include <commonport.h>
#include "vminterface.hpp"
#include <windows.h>

/*==========================================================================
 *--------------------------- Interface to VMDLL ---------------------------
 *==========================================================================*/

VMDll_Interface& VMDll_Interface::get()
{
   static VMDll_Interface instance;
   return( instance );
}

VMDll_Interface::VMDll_Interface()
: Dll_Interface()
, pfnViewMgr_( NULL )
, pfnViewErrorString_( NULL )
, pfnVmNotifySem_( NULL )
, pfnVmNotifyQueue_( NULL )
, pfnVmNotifyWin_( NULL )
, pfnVmConnectApp_( NULL )
, pfnVmDisconnectApp_( NULL )
, pfnVmAppRequest_( NULL )
, pfnVmAppRequestProt_( NULL )
, pfnVmAppRequestPriv_( NULL )
, pfnVmAppRequestPrivProt_( NULL )
, pfnVmShutdownExe_( NULL )
, pfnVmErrorMsg_( NULL )
, pfnVmExtractResp_( NULL )
, pfnVmReadResponse_( NULL )
, pfnVmFree_( NULL )
{
}

VMDll_Interface::~VMDll_Interface()
{
}

bool VMDll_Interface::load()
{
   static const char* pszDll = "VMDLL";
   if( NULL != hMod_ )
   {
      hMod_ = reinterpret_cast< HINSTANCE >( LoadLibrary( pszDll ) );
      if( NULL != hMod_ )
      {
         resolve( pfnViewMgr_, "ViewMgr" );
         resolve( pfnViewErrorString_, "ViewErrorString" );
         resolve( pfnVmNotifySem_, "VmNotifySem" );
         resolve( pfnVmNotifyQueue_, "VmNotifyQueue" );
         resolve( pfnVmNotifyWin_, "VmNotifyWin" );
         resolve( pfnVmConnectApp_, "VmConnectApp" );
         resolve( pfnVmDisconnectApp_, "VmDisconnectApp" );
         resolve( pfnVmAppRequest_, "VmAppRequest" );
         resolve( pfnVmAppRequestProt_, "VmAppRequestProt" );
         resolve( pfnVmAppRequestPriv_, "VmAppRequestPriv" );
         resolve( pfnVmAppRequestPrivProt_, "VmAppRequestPrivProt" );
         resolve( pfnVmShutdownExe_, "VmShutdownExe" );
         resolve( pfnVmErrorMsg_, "VmErrorMsg" );
         resolve( pfnVmExtractResp_, "VmExtractResp" );
         resolve( pfnVmIsAppConnected_, "VmIsAppConnected" );
         resolve( pfnVmReadResponse_, "VmReadResponse" );
         resolve( pfnVmFree_, "VmFree" );
      }
      else
      {
         DllLoadFailureMsg( pszDll );
      }
   }
   return( hMod_ != NULL );
}

VOID VMDll_Interface::ViewMgr( PVOID u1 )
{
   load();
   if( NULL != pfnViewMgr_ )
   {
      pfnViewMgr_( u1 );
      return;
   }
   throw "Dll not loaded";
}

PVMAPPRESP VMDll_Interface::VmReadResponse( char* u1 )
{
   load();
   if( NULL != pfnVmReadResponse_ )
   {
      return( pfnVmReadResponse_( u1 ) );
   }
   throw "Dll not loaded";
}

BOOL VMDll_Interface::VmFree( PVOID u1 )
{
   load();
   if( NULL != pfnVmFree_ )
   {
      return( pfnVmFree_( u1 ) );
   }
   throw "Dll not loaded";
}

BOOL VMDll_Interface::ViewErrorString( USHORT u1, USHORT u2, PSZ u3 )
{
   load();
   if( NULL != pfnViewErrorString_ )
   {
      return( pfnViewErrorString_( u1, u2, u3 ) );
   }
   throw "Dll not loaded";
}

USHORT VMDll_Interface::VmNotifySem( PSZ u1, PSZ u2, USHORT u3, PBYTE u4, ULONG u5, PSZ u6, ULONG u7 )
{
   load();
   if( NULL != pfnVmNotifySem_ )
   {
      return( pfnVmNotifySem_( u1, u2, u3, u4, u5, u6, u7 ) );
   }
   throw "Dll not loaded";
}

USHORT VMDll_Interface::VmNotifyQueue( PSZ u1, PSZ u2, USHORT u3, PSZ u4, ULONG u5 )
{
   load();
   if( NULL != pfnVmNotifyQueue_ )
   {
      return( pfnVmNotifyQueue_( u1, u2, u3, u4, u5 ) );
   }
   throw "Dll not loaded";
}

USHORT VMDll_Interface::VmNotifyWin( PSZ u1, HWND u2, ULONG u3, USHORT u4, PBYTE u5, ULONG u6, PSZ u7, ULONG u8 )
{
   load();
   if( NULL != pfnVmNotifyWin_ )
   {
      return( pfnVmNotifyWin_( u1, u2, u3, u4, u5, u6, u7, u8 ) );
   }
   throw "Dll not loaded";
}

USHORT VMDll_Interface::VmConnectApp( PSZ u1, PSZ u2, ULONG u3 )
{
   load();
   if( NULL != pfnVmConnectApp_ )
   {
      return( pfnVmConnectApp_( u1, u2, u3 ) );
   }
   throw "Dll not loaded";
}

USHORT VMDll_Interface::VmDisconnectApp( PSZ u1, PSZ u2, ULONG u3 )
{
   load();
   if( NULL != pfnVmDisconnectApp_ )
   {
      return( pfnVmDisconnectApp_( u1, u2, u3 ) );
   }
   throw "Dll not loaded";
}

USHORT VMDll_Interface::VmAppRequest( PSZ u1, PSZ u2, PSZ u3, PSZ u4, ULONG u5, PBYTE u6, ULONG u7, ULONG u8, USHORT u9, PSZ u10, ULONG u11 )
{
   load();
   if( NULL != pfnVmAppRequest_ )
   {
      return( pfnVmAppRequest_( u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11 ) );
   }
   throw "Dll not loaded";
}

USHORT VMDll_Interface::VmAppRequestProt( PSZ u1, PSZ u2, PSZ u3, PSZ u4, ULONG u5, PBYTE u6, ULONG u7, ULONG u8, USHORT u9, PSZ u10, ULONG u11, PBYTE u12, ULONG u13 )
{
   load();
   if( NULL != pfnVmAppRequestProt_ )
   {
      return( pfnVmAppRequestProt_( u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12, u13 ) );
   }
   throw "Dll not loaded";
}

USHORT VMDll_Interface::VmAppRequestPriv( PSZ u1, USHORT u2, PSZ u3, PBYTE u4, ULONG u5, ULONG u6, USHORT u7, PSZ u8, ULONG u9 )
{
   load();
   if( NULL != pfnVmAppRequestPriv_ )
   {
      return( pfnVmAppRequestPriv_( u1, u2, u3, u4, u5, u6, u7, u8, u9 ) );
   }
   throw "Dll not loaded";
}

USHORT VMDll_Interface::VmAppRequestPrivProt( PSZ u1, USHORT u2, PSZ u3, PBYTE u4, ULONG u5, ULONG u6, USHORT u7, PSZ u8, ULONG u9, PBYTE u10, ULONG u11 )
{
   load();
   if( NULL != pfnVmAppRequestPrivProt_ )
   {
      return( pfnVmAppRequestPrivProt_( u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11 ) );
   }
   throw "Dll not loaded";
}

USHORT VMDll_Interface::VmShutdownExe( USHORT u1, PSZ u2, ULONG u3 )
{
   load();
   if( NULL != pfnVmShutdownExe_ )
   {
      return( pfnVmShutdownExe_( u1, u2, u3 ) );
   }
   throw "Dll not loaded";
}

BOOL VMDll_Interface::VmErrorMsg( PSZ u1, USHORT u2, PBYTE u3, ULONG u4 )
{
   load();
   if( NULL != pfnVmErrorMsg_ )
   {
      return( pfnVmErrorMsg_( u1, u2, u3, u4 ) );
   }
   throw "Dll not loaded";
}

BOOL VMDll_Interface::VmExtractResp( PBYTE u1, PVMDSTRESP u2 )
{
   load();
   if( NULL != pfnVmExtractResp_ )
   {
      return( pfnVmExtractResp_( u1, u2 ) );
   }
   throw "Dll not loaded";
}

USHORT VMDll_Interface::VmIsAppConnected( PSZ u1 )
{
   load();
   if( NULL != pfnVmIsAppConnected_ )
   {
      return( pfnVmIsAppConnected_( u1 ) );
   }
   throw "Dll not loaded";
}


/*==========================================================================
 *--------------------------- Interface to VMDST ---------------------------
 *==========================================================================*/

VMDST_Interface& VMDST_Interface::get()
{
   static VMDST_Interface instance;
   return( instance );
}

VMDST_Interface::VMDST_Interface()
: Dll_Interface()
{}

VMDST_Interface::~VMDST_Interface()
{
}


bool VMDST_Interface::load()
{
   static const char* pszDll = "VMDST";
   if( NULL != hMod_ )
   {
      hMod_ = reinterpret_cast< HINSTANCE >( LoadLibrary( pszDll ) );
      if( NULL != hMod_ )
      {
         resolve( pfnVmSearchConnect_, "VmSearchConnect" );
         resolve( pfnVmConnect_, "VmConnect" );
         resolve( pfnVmDisconnect_, "VmDisconnect" );
         resolve( pfnVmNotify_, "VmNotify" );
         resolve( pfnVmInvokeTrace_, "VmInvokeTrace" );
         resolve( pfnVmDispose_, "VmDispose" );
         resolve( pfnVmShutdown_, "VmShutdown" );
         resolve( pfnVmPrivate_, "VmPrivate" );
         resolve( pfnVmAppAvail_, "VmAppAvail" );
      }
      else
      {
         DllLoadFailureMsg( pszDll );
      }
   }
   return( hMod_ != NULL );
}


SHORT VMDST_Interface::VmSearchConnect( char* u1, BOOL u2 )
{
   load();
   if( NULL != pfnVmSearchConnect_ )
   {
      return( pfnVmSearchConnect_( u1, u2 ) );
   }
   throw "Dll not loaded";
}

VOID  VMDST_Interface::VmConnect( PVM u1 )
{
   load();
   if( NULL != pfnVmConnect_ )
   {
      pfnVmConnect_( u1 );
      return;
   }
   throw "Dll not loaded";
}

VOID  VMDST_Interface::VmDisconnect( PVM u1, SHORT u2 )
{
   load();
   if( NULL != pfnVmDisconnect_ )
   {
      pfnVmDisconnect_( u1, u2 );
      return;
   }
   throw "Dll not loaded";
}

VOID  VMDST_Interface::VmNotify( PVM u1, SHORT u2 )
{
   load();
   if( NULL != pfnVmNotify_ )
   {
      pfnVmNotify_( u1, u2 );
      return;
   }
   throw "Dll not loaded";
}

VOID  VMDST_Interface::VmInvokeTrace( PVM u1, SHORT u2 )
{
   load();
   if( NULL != pfnVmInvokeTrace_ )
   {
      pfnVmInvokeTrace_( u1, u2 );
      return;
   }
   throw "Dll not loaded";
}

VOID  VMDST_Interface::VmDispose( PVM u1, SHORT u2 )
{
   load();
   if( NULL != pfnVmDispose_ )
   {
      pfnVmDispose_( u1, u2 );
      return;
   }
   throw "Dll not loaded";
}

VOID  VMDST_Interface::VmShutdown( PVM u1, SHORT u2 )
{
   load();
   if( NULL != pfnVmShutdown_ )
   {
      pfnVmShutdown_( u1, u2 );
      return;
   }
   throw "Dll not loaded";
}

VOID  VMDST_Interface::VmPrivate( PVM u1, SHORT u2 )
{
   load();
   if( NULL != pfnVmPrivate_ )
   {
      pfnVmPrivate_( u1, u2 );
      return;
   }
   throw "Dll not loaded";
}

VOID  VMDST_Interface::VmAppAvail( PVM u1 )
{
   load();
   if( NULL != pfnVmAppAvail_ )
   {
      pfnVmAppAvail_( u1 );
      return;
   }
   throw "Dll not loaded";
}



