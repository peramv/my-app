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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ShutdownProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/09/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MgmtCoRefresh
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "shutdownprocess.hpp"
#include "server.hpp"

// put the command traits here as we don't really want to create a separate processids.cpp file 
// to hold only one small item - CP 27Mar2002
SRVBASE_LINKAGE const I_CHAR *CMD_SPROC_SHUTDOWN            = I_( "BPROC_Shutdown" );
#include <bfproc\commandtraits.hpp>
static CommandTraits cmdTraits( CMD_SPROC_SHUTDOWN, SERVER_PROCESS_TYPE, 1, 1, MODE_BOTH );

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ShutdownProcess > processCreator( CMD_SPROC_SHUTDOWN );


namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ShutdownProcess" );
   const I_CHAR * const SHUTDOWN_MODE = I_( "ShutdownMode" );
   const I_CHAR * const EXIT = I_( "exit" );
   const I_CHAR * const RESTART = I_( "restart" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
ShutdownProcess::ShutdownProcess( GenericInterfaceContainer* pGIC,
                                  GenericInterface* pGIParent,
                                  const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _restart(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************
ShutdownProcess::~ShutdownProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY ShutdownProcess::doInit()
{

   try
   {
      _restart = false;

      DString shutdownMode;
      getParameter( SHUTDOWN_MODE, shutdownMode );

      if( shutdownMode == RESTART )
         _restart = true;
   }
   catch( ... )
   {
   }

   return(NO_CONDITION);
}

//******************************************************************************
E_COMMANDRETURN ShutdownProcess::doProcess()
{  
   E_COMMANDRETURN rtn = CMD_MODELESS_INPROCESS;

   if( _restart )
      Server::getInstance()->postRestart();
   else
      Server::getInstance()->postExit();

   return(CMD_MODELESS_INPROCESS);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/srvbase/ShutdownProcess.cpp-arc  $
//
//   Rev 1.4   Jan 27 2005 15:36:44   smithdav
//Remove SRVBASE_DLL definition
// 
//    Rev 1.3   Jan 14 2003 11:04:52   PURDYECH
// DataGroupid parentage knowledge
// 
//    Rev 1.2   Oct 09 2002 17:42:28   PURDYECH
// New PVCS Database
// 
//    Rev 1.1   27 Mar 2002 19:44:12   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.0   11 Oct 2001 17:52:54   SMITHDAV
// Initial revision.
 */
