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
// ^FILE   : ProgressCtrlProcess.cpp
// ^AUTHOR : Serban Popescu  
// ^DATE   : July 08
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ProgressCtrlProcess
//    This class sets processes IdCaller.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "progressctrlprocess.hpp"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_PROGRESS_CTRL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PROGRESS_CTRL;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ProgressCtrlProcess > processCreator( CMD_BPROC_PROGRESS_CTRL );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ProgressCtrlProcess" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319ProgressCtrlProcess::ProgressCtrlProcess() : 
ProgressCtrlProcess::ProgressCtrlProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

ProgressCtrlProcess::~ProgressCtrlProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool ProgressCtrlProcess::doModelessChildComplete(const Command &cmd)
{
   return true;
}

//******************************************************************************
bool ProgressCtrlProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;

   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

//******************************************************************************
E_COMMANDRETURN ProgressCtrlProcess::doProcess()
{  // If we are modal, interaction with the screen will occur before returning
   //  from the invokeCommand, if we are modeless the interactions will occur
   //  between the invokeCommand and when modelessChildComplete is called.
   TRACE_METHOD( CLASSNAME, DOPROCESS );

   E_COMMANDRETURN rtn = invokeCommand( this, CMD_GUI_PROGRESS_CTRL, PROC_NO_TYPE,
                                        isModal(), &_rpChildGI );

   return(rtn);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ProgressCtrlProcess.cpp-arc  $
// 
//    Rev 1.0   17 Jul 2008 15:05:36   popescu
// Initial revision.
 *
 */
