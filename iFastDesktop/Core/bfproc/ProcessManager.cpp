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
///
//******************************************************************************
//
// ^FILE   : ProcessManager.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 12/09/98
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ProcessManager
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "bpglobal.h"
#include "processmanager.hpp"
#include "command.hpp"
#include "genericinterface.hpp"
#include "genericinterfacecontainer.hpp"
#include <assert.h>
#include "bfprocessfactory.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ProcessManager" );
   const I_CHAR * const INVOKECOMMAND = I_( "invokeCommand" );

   // Literals
   const I_CHAR * const CMD = I_( "COMMAND" );
}

namespace CND
{  // Conditions used
   extern const long BP_ERR_COMMAND_NOT_FOUND;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD : ProcessManager::ProcessManager
//
// ^DESCRIPTION : Private constructor to support Singleton pattern
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//******************************************************************************

ProcessManager::ProcessManager()
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

ProcessManager::~ProcessManager()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************

E_COMMANDRETURN ProcessManager::invokeCommand( // Go to specified process
                                               GenericInterfaceContainer *rpGIC,
                                               GenericInterface *rpGIParent,
                                               const Command& rCommand,
                                               GenericInterface **rpGIModelessOut
                                             )                                         
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, INVOKECOMMAND );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   // Start as invalid
   if( rpGIModelessOut )
      *rpGIModelessOut = NULL;
   GenericInterface *pGI = NULL;

   pGI = BFProcessFactory::getInstance().create( rpGIC, rpGIParent, rCommand );
   if( !pGI )
   {
      DString strIDI;
      addIDITagValue( strIDI, CMD, rCommand.getName() ); 
      assert( 0 );    // INVALID_PROCESS - need error condition
      throw EXCEPTIONFROMFILEIDI( CND::BP_ERR_COMMAND_NOT_FOUND, strIDI );
   }

// Ignoring warnings here ??
//CP20030108   if( pGI->init( rpGIC, rpGIParent, *rpCommand ) <= WARNING )
   if( pGI->init() <= WARNING )
   {
      // Save object in GIC
      rpGIC->add( pGI );

      rtn = pGI->process();
      if( rtn != CMD_MODELESS_INPROCESS )
      {  // if not a continueing modeless GI, we are done with it
         rpGIC->destroySelf( pGI );
      }
      else if( rpGIModelessOut )
      {  // User wants pointer for modeless
         *rpGIModelessOut = pGI;
      }
   }
   else
   {  // Never made it into GIC, so delete
      delete pGI;
   }

   return(rtn);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/ProcessManager.cpp-arc  $
 * 
 *    Rev 1.14   Jan 22 2003 12:52:04   PURDYECH
 * Fixed Condition IDI string keyword.
 * 
 *    Rev 1.13   Jan 14 2003 11:04:42   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.12   Jan 06 2003 16:44:10   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 17:41:00   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.10   Aug 29 2002 13:47:16   PURDYECH
 * Base Condition split out
 * 
 *    Rev 1.9   22 May 2002 17:57:06   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   27 Mar 2002 19:47:02   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.7   11 Oct 2001 17:48:18   SMITHDAV
 * No longer as singleton...
 * 
 *    Rev 1.6   Oct 31 2000 11:31:24   VASILEAD
 * Check for valid rpGIModelessOut
 * 
 *    Rev 1.5   Oct 26 2000 10:39:46   DT24433
 * change to pass GIC instead of session
 * 
 *    Rev 1.4   Apr 04 2000 14:32:48   DT24433
 * changed for GIC userid change
 * 
 *    Rev 1.3   Apr 03 2000 13:25:40   DT24433
 * added delete if GI failed init
 * 
 *    Rev 1.2   Mar 30 2000 12:27:34   POPESCUS
 * made some temporary changes to support batch processing
 * 
 *    Rev 1.1   Mar 21 2000 10:44:52   DT24433
 * changed to add modal as well as modeless objects to GenericInterfaceContainer
 * 
 *    Rev 1.0   Mar 02 2000 15:28:36   MCNABBGL
 * Initial revision.
 * 
 *    Rev 1.1   Feb 29 2000 15:21:16   BUZILA
 * added Trading screen/process/CBO
 * 
 *    Rev 1.0   Feb 15 2000 10:59:36   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.16   Jan 19 2000 11:09:32   WINNIE
 * add broker screen
 * 
 *    Rev 1.15   Dec 22 1999 11:46:08   ZHANGCEL
 * Add BranchListDlg, BranchListProcess, SalesRepGlg and SaleRepProcess
 * 
 *    Rev 1.14   Nov 26 1999 14:04:58   YINGZ
 * add bakn dlg
 * 
 *    Rev 1.13   Nov 24 1999 09:50:32   FENGYONG
 * Add JFundSrchProcess 
 * 
 *    Rev 1.12   Nov 23 1999 18:05:38   POPESCUS
 * NASU flow
 * 
 *    Rev 1.11   Nov 22 1999 12:11:30   FENGYONG
 * Add BP for vision team
 * 
 *    Rev 1.10   Nov 22 1999 11:34:50   HUANGSHA
 * Added SystematicFee process & gui
 * 
 *    Rev 1.9   Oct 30 1999 15:08:48   HSUCHIN
 * Added Historical Account
 * 
 *    Rev 1.8   Sep 27 1999 10:45:22   PRAGERYA
 * Allocations checked in for release; transaction allocations not debugged yet
 * 
 *    Rev 1.7   Sep 24 1999 10:09:38   PRAGERYA
 * "Milestone" check in
 * 
 *    Rev 1.6   Sep 21 1999 18:17:32   VASILEAD
 * Added FreeUnits support
 * 
 *    Rev 1.5   Jul 28 1999 13:16:04   POPESCUS
 * Added a new process for entity search
 * 
 *    Rev 1.4   Jul 27 1999 16:01:50   BUZILA
 * Increment M2
 * 
 *    Rev 1.3   Jul 23 1999 10:22:30   POPESCUS
 * Added a new Process that will fill in the dstc front end combos
 * 
 *    Rev 1.2   Jul 20 1999 11:14:12   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:02:10   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
