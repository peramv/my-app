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

#include <bfproc\AbstractCommandDispatcher.hpp>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

// Forward declarations
class AbstractBaseMainDlg;
class Command;
class CommandDispatcher;
class GenericInterface;

/**
 * Singleton class which is the dispatcher class for dialogs.
 *
 * This class creates the dialog which matches a command for the GuiDispatcher
 * GuiDispatcher is a friend class and the only class which can use this class.
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 07/16/97</dd></dl>
 * @version 0.1
 */

class WIN32UIBASE_LINKAGE WindowManager : public AbstractCommandDispatcher
{
public:
   friend CommandDispatcher;
   // Class methods
   /**
    * This is a class method implementing the creation side of the singleton
    * pattern.
    * @returns a pointer to the singleton ProcessManager
    */
   static WindowManager *getInstance(        // Get singleton instance,
                                    );                                     //  create if necessary
   /**
    * This is a class method implementing the destruction side of the singleton
    * pattern.
    */
   static void killInstance(                 // Delete Singleton instance, if
                           );                                     //  necessary

private:
   static WindowManager * _pInstance;        // For Singleton pattern

   WindowManager();
   virtual ~WindowManager();

   // Go to specified dialog
   E_COMMANDRETURN doModelessDialog( const Command& rCommand,                     
                                     GenericInterfaceContainer *rpGIC,
                                     GenericInterface *rpGIParent,
                                     AbstractBaseMainDlg **rpDlgModelessOut );                                     // Ptr to dialog, NULL if fail

   // Go to specified dialog
   // RETURNS dialog return code
   E_COMMANDRETURN doModalDialog( const Command& rCommand,                     
                                  GenericInterfaceContainer *rpGIC,
                                  GenericInterface *rpGIParent );
   /**
    * This method is used to invoke a command with the sub-dispatcher.
    * 
    * @param rpGIC      A reference pointer to the GenericInterfaceContainer the
    *                   command is associated with.
    * @param rpGIParent A reference pointer to the parent GenericInterface.
    * @param rCommand   A reference to the Command object for this command.
    * @param rpGIModelessOut
    *                   A pointer to a reference pointer which is set by this
    *                   method.  A non-null pointer means that a modeless process/dialog is still
    *                   in process.  This pointer may be used to communicate with the process/dialog,
    *                   but caution should be used since these pointers may become invalid when the
    *                   modeless process is shut down.  Always use validateModelessPointer
    *                   prior to use.
    * 
    * @return an enum representing the return type
    */
   virtual E_COMMANDRETURN invokeCommand( GenericInterfaceContainer *rpGIC,
                                          GenericInterface *rpGIParent,
                                          const Command& rCommand,
                                          GenericInterface **rpGIModelessOut );

   /**
    * Shared method to start a dialog
    * 
    * @param rCommand   A reference to the Command object for this command.
    * @param rpGIC      A reference pointer to the GenericInterfaceContainer the
    *                   command is associated with.
    * @param rpParentGI A reference pointer to the parent GenericInterface.
    * @param rpDlgModelessOut
    *                   A pointer to a reference pointer which is set by this method.  A
    *                   non-null pointer means that a modeless process/dialog is still
    *                   in process.  This pointer may be used to communicate with the
    *                   process/dialog, but caution should be used since these pointers
    *                   may become invalid when the modeless process is shut down.
    *                   Always use validateModelessPointer prior to use.
    * 
    * @return an enum representing the return type
    */
   E_COMMANDRETURN startDialog( const Command& rCommand,                     
                                GenericInterfaceContainer *rpGIC,
                                GenericInterface *rpParentGI,
                                AbstractBaseMainDlg **rpDlgModelessOut );
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/uibase/WindowManager.hpp-arc  $
 * 
 *    Rev 1.4   Feb 11 2003 10:45:12   PURDYECH
 * Use new dialog creation idiom.  The GIC, the parent GI and the command are now passed as construction parameters.
 * 
 *    Rev 1.3   Oct 09 2002 17:42:58   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   19 Mar 2002 13:36:14   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   Oct 26 2000 10:51:22   DT24433
 * change to pass GIC instead of session
 * 
 *    Rev 1.0   Mar 02 2000 15:27:44   MCNABBGL
 * Initial revision.
 * 
 *    Rev 1.2   Feb 28 2000 16:56:22   DT24433
 * removed unused active window code
 * 
 *    Rev 1.1   Feb 15 2000 18:59:56   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:30   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Aug 24 1999 14:54:46   DT24433
 * misc. cleanup
 * 
 *    Rev 1.1   Jul 08 1999 10:06:06   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
