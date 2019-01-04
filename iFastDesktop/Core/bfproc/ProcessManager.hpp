#pragma once
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

#include <commonport.h>
#include <bfproc\abstractcommanddispatcher.hpp>

// Forward declarations
class Session;
class Command;
class CommandDispatcher;
class GenericInterface;
class ProcessDispatcher;

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * Singleton class which is the dispatcher class for business processes.
 *
 * This class creates the business process which matches a command for the
 * CommandDispatcher.  CommandDispatcher is a friend class and the only class
 * which can use this class.
 * getInstance and killInstance should also be private when 
 * there is a designated startup class.  Right now GuiDispatcher is acting as the
 * designated startup class, basically starting up the whole command dispatching
 * mechanism.
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 12/09/98</dd></dl>
 * @version 0.1
 */

class BPBASE_LINKAGE ProcessManager : public AbstractCommandDispatcher
{
public:
   friend CommandDispatcher;

   ProcessManager();
   virtual ~ProcessManager();

private:

   /**
    * This method is used to invoke a command with the sub-dispatcher.
    * 
    * @returns an enum representing the return type
    * @param rpGIC      - A reference pointer to the GenericInterfaceContainer the
    *                   command is associated with.
    * @param rpGIParent - A reference pointer to the parent GenericInterface.
    * @param rCommand   - A reference to the Command object for this command.
    * @param rpGIModelessOut
    *                   - A pointer to a reference pointer which is set by
    *                   this method.  A non-null pointer means that a modeless process/dialog is
    *                   still in process.  This pointer may be used to communicate with the
    *                   process/dialog, but caution should be used since these pointers may
    *                   become invalid when the modeless process is shut down.  Always use
    *                   validateModelessPointer prior to use.
    * 
    * @return 
    */
   E_COMMANDRETURN invokeCommand( GenericInterfaceContainer *rpGIC,
                                  GenericInterface *rpGIParent,
                                  const Command& rCommand,
                                  GenericInterface **rpGIModelessOut );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/ProcessManager.hpp-arc  $
 * 
 *    Rev 1.5   Jan 14 2003 11:04:46   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.4   Oct 09 2002 17:41:00   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.3   22 Mar 2002 15:12:04   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.2   11 Oct 2001 17:48:18   SMITHDAV
 * No longer as singleton...
 * 
 *    Rev 1.1   Oct 26 2000 10:40:58   DT24433
 * change to pass GIC instead of session
 * 
 *    Rev 1.0   Mar 02 2000 15:29:12   MCNABBGL
 * Initial revision.
 * 
 *    Rev 1.1   Feb 15 2000 18:56:40   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:18   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:03:54   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
