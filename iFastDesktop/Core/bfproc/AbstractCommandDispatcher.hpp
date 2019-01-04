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
#include <bfproc\commandenum.h>
#include <map>

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

// Forward declare
class Command;
class GenericInterface;
class GenericInterfaceContainer;

/**
 * This is the base class for all command dispatchers.
 *
 * A dispatching mechanism is established which allows multiple "sub"
 * dispatchers to be registered/deregistered.  Subclasses should override
 * the invokeCommand where they will implement whatever processing they
 * add to the process.  If they delegate to other dispatchers, then they
 * should call invokeCommandForRegisteredDispatchers which this base class
 * implements.
 * Hierarchies of command dispatchers may be built using this mechanism since
 * each subclass may have its own set of sub-dispatchers.
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 11/17/98</dd></dl>
 * @version 0.1
 */

class BPBASE_LINKAGE AbstractCommandDispatcher
{
public:
   AbstractCommandDispatcher();
   virtual ~AbstractCommandDispatcher() = 0;

   /**
     * This method is used to deregister a dispatcher.  This takes the
     * dispatcher and removes it from the command dispatcher chain.  The caller
     * is still responsible for deleting the dispatcher.
     * @param rpDispatcher - A reference pointer tothe dispatcher to deregister.
     */
   void deregisterDispatcher( AbstractCommandDispatcher *rpDispatcher );
   /**
     * This method is used to register a dispatcher.  This takes the
     * dispatcher and adds it to the command dispatcher chain.  The caller
     * is still responsible for deleting the dispatcher.
     * @param rpDispatcher - A reference pointer tothe dispatcher to deregister.
     * @param type - An integer representation of the command types this
     * dispatcher will handle.  These types are found in CommandEnum.h and can
     * be set up in hierarchies.  Only one dispatcher should exactly match
     * each command type.
     */
   void registerDispatcher( AbstractCommandDispatcher *rpDispatcher, int type );
protected:
   /**
     * This method is used to invoke a command with the dispatcher. It must be
     * overridden in the derived class to work properly.
     * @param rpGIC - A reference pointer to the GenericInterfaceContainer the
     * command is associated with.
     * @param rpGIParent - A reference pointer to the parent GenericInterface.
     * @param rCommand - A reference pointer to the Command that is being
     * invoked.
     * @param rpModeless - A pointer to a reference pointer which is set by this
     * method.  A non-null pointer means that a modeless process/dialog is still
     * in process.  This pointer may be used to communicate with the process/dialog,
     * but caution should be used since these pointers may become invalid when the
     * modeless process is shut down.  Always use validateModelessPointer 
     * prior to use.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN invokeCommand( GenericInterfaceContainer * rpGIC,
                                          GenericInterface * rpGIParent,
                                          const Command& rCommand,
                                          GenericInterface ** rpModeless /* NULL or pointer if active modeless */ )
   {
      return(CMD_FAILURE);
   }
   /**
     * This method is used to pass commands on to the sub-dispatchers.
     * @param rpGIC - A reference pointer to the GenericInterfaceContainer the
     * command is associated with.
     * @param rpGIParent - A reference pointer to the parent GenericInterface.
     * @param rCommand - A reference pointer to the Command that is being
     * invoked.
     * @param rpModeless - A pointer to a reference pointer which is set by this
     * method.  A non-null pointer means that a modeless process/dialog is still
     * in process.  This pointer may be used to communicate with the process/dialog,
     * but caution should be used since these pointers may become invalid when the
     * modeless process is shut down.  Always use validateModelessPointer 
     * prior to use.
     * @returns an enum representing the return type
     */
   E_COMMANDRETURN invokeCommandForRegisteredDispatchers( GenericInterfaceContainer *rpGIC, 
                                                          GenericInterface *rpGIParent,
                                                          const Command& rCommand,
                                                          GenericInterface **rpModeless /* NULL or pointer if active modeless */ );
private: 
   typedef std::map< int, AbstractCommandDispatcher *, std::less<int> > HANDLERS;
   typedef HANDLERS::iterator HANDLERS_ITER;

   HANDLERS _dispatchers;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/AbstractCommandDispatcher.hpp-arc  $
 * 
 *    Rev 1.8   Jan 14 2003 11:03:44   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.7   Nov 27 2002 15:04:12   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.6   Oct 09 2002 17:40:46   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.5   27 Mar 2002 19:52:36   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.4   22 Mar 2002 15:11:18   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.3   Oct 26 2000 10:37:04   DT24433
 * change to pass GIC instead of session
 * 
 *    Rev 1.2   Mar 02 2000 10:58:58   DT24433
 * added factory registration
 * 
 *    Rev 1.1   Feb 15 2000 18:54:56   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:44   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:03:20   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
