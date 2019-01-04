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
// ^FILE   : SetDataServerProcess.cpp
// ^AUTHOR :  Adrian Vasile
// ^DATE   : 10/13/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SetDataServerProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "setdataserverprocess.hpp"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SETDATASERVER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< SetDataServerProcess > processCreator( CMD_BPROC_SETDATASERVER );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "ACBProcess" );
}

//******************************************************************************

//CP20030319SetDataServerProcess::SetDataServerProcess() : 
SetDataServerProcess::SetDataServerProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

}

//******************************************************************************

SetDataServerProcess::~SetDataServerProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************

SEVERITY SetDataServerProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

//   const BFDataGroupId& idDataGroup = BFSessionManager::getNextGroupId();
//   setMyGroupID( idDataGroup ); //setting a idDataGroup for the process

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN SetDataServerProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_MODELESS_INPROCESS;

   return(rtn);
}


//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SetDataServerProcess.cpp-arc  $
 // 
 //    Rev 1.9   Mar 21 2003 17:47:54   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.8   Oct 09 2002 23:53:36   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.7   Aug 29 2002 16:45:14   SMITHDAV
 // Condition split.
 // 
 //    Rev 1.6   22 May 2002 18:25:02   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.5   27 Mar 2002 19:55:40   PURDYECH
 // Process/WindowFactory overhaul
 // 
 //    Rev 1.4   03 May 2001 14:05:44   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.3   Apr 06 2001 17:15:40   YINGZ
 // make group id work
 // 
 //    Rev 1.2   15 Dec 2000 12:43:50   PURDYECH
 // Use precompiled header stdafx.h.
 // Removed unnecessary header files.
 // 
 //    Rev 1.1   Oct 16 2000 16:27:14   VASILEAD
 // Added Shareholder and Account in NASU
 * 
 *    Rev 1.1   Jul 08 1999 10:01:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
