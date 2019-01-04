#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif   

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

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * This is the main command dispatcher.
 *
 * This dispatcher is the only one that is visible to the rest of the system.
 * All of the sub-dispatchers are visible only to this dispatcher (mostly).  The
 * virtual invokeCommand from AbstractCommandDispatcher is overloaded instead
 * of overridden.  The invokeCommand method implemented here is the only command
 * dispatch interface available to the rest of the code base.
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 11/17/98</dd></dl>
 * @version 0.1
 */

class BPBASE_LINKAGE CommandDispatcher : public AbstractCommandDispatcher
{
public:
   /**
    * This is a class method implementing the creation side of the singleton
    * pattern.
    * @returns a pointer to the singleton CommandDispatcher
    */
   static CommandDispatcher *getInstance();
   /**
    * This is a class method implementing the destruction side of the singleton
    * pattern.
    */
   static void killInstance();

   /**
    * This method is used to invoke a command with the dispatcher.
    * 
    * @returns an enum representing the return type
    * @param rpGIC      A reference pointer to the GenericInterfaceContainer the
    *                   command is associated with.
    * @param rpGIParent A reference pointer to the parent GenericInterface.
    * @param szCommand  A string literal representing the command to be
    *                   invoked.  This is used to lookup the command and create the command
    *                   object which is associated.
    * @param type       An enum representing the process type for the command.
    *                   This type is used to create the command object associated with this
    *                   command.
    * @param bModal     Flag where true is modal and false is modeless.
    * @param rpGIModelessOut
    * 
    * @return 
    */
   E_COMMANDRETURN invokeCommand(
                                GenericInterfaceContainer *rpGIC,
                                GenericInterface *rpGIParent,
                                const I_CHAR *szCommand,
                                E_PROCESSTYPE type,
                                bool bModal,
                                GenericInterface **rpGIModelessOut  // If not null, this will be set to
                                // NULL or pointer to active modeless
                                );
   /**
    * This alternate method is used to invoke a command with the dispatcher
    * pulling the necessary GenericInterfaceContainer from the parent.  The
    * parent may not be NULL with this method.
    * 
    * @returns an enum representing the return type
    * @param rpGIParent A reference pointer to the parent GenericInterface.
    * @param szCommand  A string literal representing the command to be
    *                   invoked.  This is used to lookup the command and create the command
    *                   object which is associated.
    * @param type       An enum representing the process type for the command.
    *                   This type is used to create the command object associated with this
    *                   command.
    * @param bModal     Flag where true is modal and false is modeless.
    * @param rpGIModelessOut
    *                   A pointer to a reference pointer which is set by
    *                   this method.  A non-null pointer means that a modeless process/dialog is
    *                   still in process.  This pointer may be used to communicate with the
    *                   process/dialog, but caution should be used since these pointers may
    *                   become invalid when the modeless process is shut down.  Always use
    *                   validateModelessPointer prior to use.
    * 
    * @return 
    */
   E_COMMANDRETURN invokeCommand(
                                GenericInterface *rpGIParent,
                                const I_CHAR *szCommand,
                                E_PROCESSTYPE type,
                                bool bModal,
                                GenericInterface **rpGIModelessOut // NULL or pointer if active modeless
                                );
private:
   static CommandDispatcher *_pCommandDispatcher;

   CommandDispatcher();
   virtual ~CommandDispatcher();
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/CommandDispatcher.hpp-arc  $
 * 
 *    Rev 1.6   Jan 14 2003 11:04:12   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.5   Nov 27 2002 15:04:28   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.4   Oct 09 2002 17:40:54   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.3   22 Mar 2002 15:11:50   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.2   Oct 26 2000 10:38:18   DT24433
 * change to pass GIC instead of session
 * 
 *    Rev 1.1   Feb 15 2000 18:54:58   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:48   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:03:38   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
