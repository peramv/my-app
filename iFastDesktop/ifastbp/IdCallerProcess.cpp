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
// ^FILE   : IdCallerProcess.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 12/08/1998
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : IdCallerProcess
//    This class sets processes IdCaller.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "idcallerprocess.hpp"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_IDCALLER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_IDCALLER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< IdCallerProcess > processCreator( CMD_BPROC_IDCALLER );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "IdCallerProcess" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319IdCallerProcess::IdCallerProcess() : 
IdCallerProcess::IdCallerProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

IdCallerProcess::~IdCallerProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool IdCallerProcess::doModelessChildComplete(
                                             const Command &cmd
                                             )
{
   return(true);            // All done, ready to be self destructed
}

//******************************************************************************

bool IdCallerProcess::doModelessSetFocus(
                                        GenericInterface *rpGICaller
                                        )
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;

   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

//******************************************************************************

E_COMMANDRETURN IdCallerProcess::doProcess()
{  // If we are modal, interaction with the screen will occur before returning
   //  from the invokeCommand, if we are modeless the interactions will occur
   //  between the invokeCommand and when modelessChildComplete is called.
   TRACE_METHOD( CLASSNAME, DOPROCESS );

   E_COMMANDRETURN rtn = invokeCommand( this, CMD_GUI_IDCALLER, PROC_NO_TYPE,
                                        isModal(), &_rpChildGI );

   return(rtn);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/IdCallerProcess.cpp-arc  $
 * 
 *    Rev 1.5   Mar 21 2003 17:41:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:53:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   22 May 2002 18:24:20   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   27 Mar 2002 19:54:58   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.1   15 Dec 2000 12:43:32   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:34   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.4   Dec 21 1999 14:41:28   DT24433
 * removed doRefresh
 * 
 *    Rev 1.3   Oct 29 1999 10:24:38   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.2   Aug 17 1999 18:28:00   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.1   Jul 08 1999 10:02:06   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
