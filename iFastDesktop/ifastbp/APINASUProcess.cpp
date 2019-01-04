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
//    AUTHOR : Zijian Ying
//    DATE   : 12/02/2001
//
//
//    Copyright 2001 by DST Systems, Inc.
//
//******************************************************************************

#include "stdafx.h"
#include "apinasuprocess.hpp"

namespace
{
   // Trace literals
   const I_CHAR*  const CLASSNAME = I_( "APINASUProcess" );
}

namespace CND
{
}
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_APINASU;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< APINASUProcess > processCreator( CMD_BPROC_APINASU );


//******************************************************************************
APINASUProcess::APINASUProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************
APINASUProcess::~APINASUProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY APINASUProcess::doInit()
{
   return(NO_CONDITION);
}

//******************************************************************************
E_COMMANDRETURN APINASUProcess::doProcess()
{  
   return(CMD_MODELESS_INPROCESS);
}
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/APINASUProcess.cpp-arc  $
// 
//    Rev 1.9   Apr 02 2003 12:19:38   PURDYECH
// Code cleanup
//
