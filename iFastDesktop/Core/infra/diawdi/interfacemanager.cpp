//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : InterfaceManager.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 16 Sep 1997
//
// ----------------------------------------------------------
//
// ^CLASS    : InterfaceManager
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DIAWDI_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef INTERFACEMANAGER_HPP
   #include "interfacemanager.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif
#ifndef CONFIGMACRO_H
   #include "configmacro.h"
#endif
#ifndef DIAWDCND_H
   #include "diawdcnd.h"
#endif
#ifndef BASE_H
   #include "base.h"
#endif

namespace
{
   const DString strINTERFACE     = I_("AwdInterface");
   const DString strTYPE          = I_("AwdType");
   const DString strDLL           = I_("InterfaceDll");

   const DStringA strOBJ_FACTORY   = I_("fnObjectFactory");
   const DStringA strIS_LOGGED_ON  = I_("fnIsLoggedOn");
   const DStringA strLOGON         = I_("fnLogon");
   const DStringA strLOGOFF        = I_("fnLogoff");
   const DStringA strAWD23         = I_("DIAWD23");

   // Names used as condition tag names
   const DString strAWD_ERROR_MESSAGE = I_("AWD_ERROR_MESSAGE");

}

//******************************************************************************
//              Static member objects
//******************************************************************************

//InterfaceManager::InstanceManager InterfaceManager::s_instanceManager;
InterfaceManager *InterfaceManager::s_pInterfaceManager = NULL;

//******************************************************************************
//              Public Methods
//******************************************************************************

InterfaceManager * InterfaceManager::getManager()
{
   // return s_instanceManager.getInstance( 'A' );
   if ( NULL == s_pInterfaceManager )
   {
      s_pInterfaceManager = new InterfaceManager;
   }

   return s_pInterfaceManager;
}

AwdBaseInterface * InterfaceManager::newInterface()
{
   return m_pObjectFactory();
}

bool InterfaceManager::isLoggedOn()
{
   return m_pIsLoggedOn();
}

long InterfaceManager::logon( const DString &operatorID,
                              const DString &password,
                              const DString &newPassword )
{
   return m_pLogon( operatorID, password, newPassword );
}

long InterfaceManager::logoff()
{
   return m_pLogoff();
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : InterfaceManager::InterfaceManager
//
// ^DESCRIPTION : Constructor.  Determines which version of AWD client to
//                interface with and then dynamically loads the appropriate
//                interface dll.
//
// ^PARAMETERS  :
//
// ^RETURNS     : none
//
// ^THROWS      : ConditionException
//
//******************************************************************************
InterfaceManager::InterfaceManager()
   : m_register()
{
   TRACE_CONSTRUCTOR( I_("InterfaceManager"), I_("InterfaceManager()") )

   m_register.registerSingleton( deregister, this );

   getAwdType();

   m_hInterface = LoadLibrary( DStringA( m_interfaceDll ).c_str() );

   if ( ! m_hInterface )
   {
      LPVOID lpMsgBuf;
      DString strMsg;

      // FormatMessage called in a method that will return a ser default language message
      FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                     NULL,
                     GetLastError(),
                     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                     (LPTSTR) &lpMsgBuf,
                     0,
                     NULL );

      strMsg = strAWD_ERROR_MESSAGE;
      strMsg += '=';
      strMsg += m_interfaceDll;
      strMsg += I_(".\nLast error: ");
      strMsg += DString( DStringA( (char*)lpMsgBuf ) );
      strMsg += I_( ";" );

      // Free the buffer.
      LocalFree( lpMsgBuf );

      THROWFROMFILEIDI( DIAWDI_CONDITION,
                      I_("InterfaceManager::InterfaceManager()"),
                      DIAWDI_LOAD_MODULE_FAIL,
                      strMsg )


   }

   m_pObjectFactory = (OBJ_FACTORY)GetProcAddress( m_hInterface, strOBJ_FACTORY.c_str() );
   m_pIsLoggedOn = (IS_LOGGED_ON)GetProcAddress( m_hInterface, strIS_LOGGED_ON.c_str() );
   m_pLogon = (LOGON)GetProcAddress( m_hInterface, strLOGON.c_str() );
   m_pLogoff = (LOGOFF)GetProcAddress( m_hInterface, strLOGOFF.c_str() );

   if ( ! ( m_pObjectFactory && m_pIsLoggedOn && m_pLogon && m_pLogoff ) )
   {
      LPVOID lpMsgBuf;
      DString strMsg;

      // FormatMessage called in a method that will return a ser default language message
      FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                     NULL,
                     GetLastError(),
                     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                     (LPTSTR) &lpMsgBuf,
                     0,
                     NULL );

      strMsg = strAWD_ERROR_MESSAGE;
      strMsg += '=';
      strMsg += m_interfaceDll;
      strMsg += I_(".\nLast error = ");
      strMsg += DString( DStringA( (char*)lpMsgBuf ) );
      strMsg += I_( ";" );

      // Free the buffer.
      LocalFree( lpMsgBuf );

      THROWFROMFILEIDI( DIAWDI_CONDITION,
                      I_("InterfaceManager::InterfaceManager()"),
                      DIAWDI_LOAD_PROC_FAIL,
                      strMsg )
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : InterfaceManager::~InterfaceManager
//
// ^DESCRIPTION : Destructor.  Unloads the interface dll.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
//******************************************************************************
InterfaceManager::~InterfaceManager()
{
   // Make sure all the singletons in the DLL are deleted before releasing it.
   SingletonRegister::releaseSingletons( AwdBaseInterface::getGroup() );

   FreeLibrary( m_hInterface );
}

//******************************************************************************
//
// ^PRIVATE METHOD      : InterfaceManager::getAwdType
//
// ^DESCRIPTION : Determines which version of AWD client should be interfaced
//                with.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : ConditionException
//
//******************************************************************************
void InterfaceManager::getAwdType()
{
   TRACE_METHOD( I_("InterfaceManager"), I_("getAwdType()") )

   m_interfaceDll = GetConfigValueAsString( strINTERFACE, strTYPE, strDLL );

   if ( m_interfaceDll.empty() )
   {
      m_interfaceDll = strAWD23;
   }


   #ifdef _WIN32
      #ifdef DST_UNICODE
         m_interfaceDll += I_("U");
      #endif

      #ifdef _DEBUG
         m_interfaceDll += I_("_D");
      #endif
   #endif

   #ifdef ENABLE_TRACING
      DString msg = I_("InterfaceDll = ");
      msg += m_interfaceDll;
      msg += I_( ";" );
      TRACE_CLASS_MSG( I_("InterfaceManager"), I_("getAwdType()"), msg )
   #endif

}

void InterfaceManager::deregister( void *pObj )
{
   const InterfaceManager *pManager = (InterfaceManager *)pObj;

   if ( pManager == s_pInterfaceManager )
   {
      delete s_pInterfaceManager;
      s_pInterfaceManager = NULL;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
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
// $Log:   Y:/VCS/iFastAWD/diawdi/interfacemanager.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:18:24   kovacsro
// Initial revision.
// 
//    Rev 1.11   Mar 27 2000 11:15:12   DMUM
// Replaced SingletonBase with SingletonRegister
//
//    Rev 1.10   Oct 12 1999 10:05:56   DMUM
// Made changes to support Unicode name-mangling of DLLs
//
//    Rev 1.9   Sep 30 1999 09:20:26   DMUM
// Started using SingletonBase
//
//    Rev 1.8   Aug 27 1999 08:29:58   DMUM
// Fixed IDI string terminator missing bug
// * cannot have '=' in message
//
//    Rev 1.7   Aug 06 1999 15:19:30   DT14177
// Fixed IDI string terminator missing bug
//
//    Rev 1.6   Jul 22 1999 11:28:26   DMUM
// Condtion re-work
//
//    Rev 1.5   Apr 16 1999 17:41:08   DMUM
// Changes for unicode compile
//
//    Rev 1.4   Mar 09 1999 12:56:32   DT20842
// Changes for internationalization
//
//    Rev 1.3   Jan 28 1999 14:01:58   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Jan 28 1999 13:42:32   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 15:28:58   DMUM
// Changes for DICORE
//
//    Rev 1.3   Dec 30 1997 11:26:00   dmum
// Changed how to look for interface DLLs
//
//    Rev 1.2   Dec 16 1997 11:29:28   dmum
// Made error message more verbose
//
//    Rev 1.1   10 Nov 1997 15:21:32   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.0   20 Sep 1997 11:50:32   dmum
//
//
//

