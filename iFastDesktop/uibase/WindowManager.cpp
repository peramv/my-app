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
// ^FILE   : WindowManager.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 7/16/97
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : WindowManager
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"

#include "windowmanager.hpp"
#include <bfproc\abstractfactory.hpp>
#include "abstractbasemaindlg.h"
#include <bfproc\command.hpp>
#include "conditionmessagedialog.h"
#include <bfproc\genericinterfacecontainer.hpp>
#include <idistring.hpp>
#include <bfproc\bfprocessfactory.hpp>
#include <assert.h>

// How handle a controlling window (like search screen) who wants to focus on
//  an existing window or see if existing window still operational.
// focusOnWindow, windowActive?  what are keys to search??

// Define static pointer for Singleton pattern
WindowManager *WindowManager::_pInstance = NULL;

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "WindowManager" );

   const I_CHAR *DOMODALDIALOG = I_( "doModalDialog" );
   const I_CHAR *DOMODELESSDIALOG = I_( "doModelessDialog" );
   const I_CHAR *GETINSTANCE = I_( "getInstance" );
   const I_CHAR *INVOKECOMMAND = I_( "invokeCommand" );
   const I_CHAR *KILLINSTANCE = I_( "killInstance" );
   const I_CHAR *REFRESHSCREENSFROMCBOS = I_( "refreshScreensFromCBOs" );
   const I_CHAR *STARTDIALOG = I_( "startDialog" );

   // Literals
   const I_CHAR * const CMD = I_( "CMD" );
}

namespace CND
{
   extern const long GUI_ERR_COMMAND_NOT_FOUND;
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Class Methods
//******************************************************************************

WindowManager *WindowManager::getInstance()
{
   TRACE_METHOD( CLASSNAME, GETINSTANCE );
   if( _pInstance )
   {
      return(_pInstance);
   }

   _pInstance = new WindowManager();
   return(_pInstance);
}

//******************************************************************************

void WindowManager::killInstance()
{
   TRACE_METHOD( CLASSNAME, KILLINSTANCE );
   if( _pInstance )
   {
      delete _pInstance;
      _pInstance = NULL;
   }
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD : WindowManager::WindowManager
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

WindowManager::WindowManager()
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

WindowManager::~WindowManager()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Go to specified dialog
// RETURNS process return code
E_COMMANDRETURN WindowManager::doModalDialog( const Command& rCommand,        // Command
                                              GenericInterfaceContainer *rpGIC,
                                              GenericInterface *rpGIParent )
{
   TRACE_METHOD( CLASSNAME, DOMODALDIALOG );

   return(startDialog( rCommand, rpGIC, rpGIParent, NULL ));
}

//******************************************************************************
// Go to specified dialog
// Ptr to dialog, NULL if fail
E_COMMANDRETURN WindowManager::doModelessDialog( const Command& rCommand,      // Command
                                                 GenericInterfaceContainer *rpGIC,
                                                 GenericInterface *rpGIParent,
                                                 AbstractBaseMainDlg **rpDlgModelessOut )
{
   TRACE_METHOD( CLASSNAME, DOMODELESSDIALOG );
   CWaitCursor cursor;
   E_COMMANDRETURN rtn = CMD_NO_RETURN;
   AbstractBaseMainDlg *pDlg = NULL;

   // Check to see if multiples allowed ???
   rtn = startDialog( rCommand, rpGIC, rpGIParent, &pDlg );
   if( rpDlgModelessOut )
   {  // User wants pointer to active modeless
      *rpDlgModelessOut = pDlg;
   }
   return(rtn);
}

//******************************************************************************
// Go to specified dialog
E_COMMANDRETURN WindowManager::invokeCommand( GenericInterfaceContainer *rpGIC,
                                              GenericInterface *rpGIParent,
                                              const Command& rCommand,
                                              GenericInterface **rpGIModelessOut )                                       
{
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, INVOKECOMMAND );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   CWaitCursor cursor;

   try
   {
      if( rCommand.isModal() )
      {
         rtn = doModalDialog( rCommand, rpGIC, rpGIParent );
      }
      else
      {
         AbstractBaseMainDlg *pDlg = NULL;

         rtn = doModelessDialog( rCommand, rpGIC, rpGIParent,
                                 &pDlg );
         if( rpGIModelessOut )
         {  // We want the pointer returned
            *rpGIModelessOut = dynamic_cast< GenericInterface * >( pDlg );
         }
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   if( rtn != CMD_MODELESS_INPROCESS && rtn != CMD_OK && rtn != CMD_CANCEL )
   {
      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
   }

   return(rtn);
}

//******************************************************************************

E_COMMANDRETURN WindowManager::startDialog( const Command& rCommand,
                                            GenericInterfaceContainer *rpGIC,
                                            GenericInterface *rpGIParent,
                                            AbstractBaseMainDlg **rpDlgModelessOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::GUI_CONDITION, CLASSNAME, STARTDIALOG );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   if( rpDlgModelessOut )
   {  // Start as invalid
      *rpDlgModelessOut = NULL;
   }

   GenericInterface* pGI = BFProcessFactory::getInstance().create( rpGIC, rpGIParent, rCommand );
   AbstractBaseMainDlg *pDlg = dynamic_cast< AbstractBaseMainDlg * >( pGI );

   if( pDlg == NULL )
   {
      ASSERT( 0 );
      DString strIDI;
      addIDITagValue( strIDI, CMD, rCommand.getName() );
      ADDCONDITIONFROMFILEIDI( CND::GUI_ERR_COMMAND_NOT_FOUND, strIDI );
      return(CMD_NOT_FOUND);
   }

   // Ignoring warnings here ??
   if( pDlg->init() <= WARNING )
   {
      // Save us in GIC
      rpGIC->add( pDlg );

      rtn = pDlg->process();
      if( rtn != CMD_MODELESS_INPROCESS )
      {  // if not a continueing modeless GI, we are done with it
         rpGIC->destroySelf( pDlg );
      }
      else if( rpDlgModelessOut )
      {
         *rpDlgModelessOut = pDlg;
      }
   }
   else
   {  // Never made it into GIC, so delete
      delete pDlg;
   }
   return(rtn);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/uibase/WindowManager.cpp-arc  $
 * 
 *    Rev 1.11   Feb 11 2003 10:44:58   PURDYECH
 * Use new dialog creation idiom.  The GIC, the parent GI and the command are now passed as construction parameters.
 * 
 *    Rev 1.10   Jan 31 2003 13:00:38   PURDYECH
 * Temp fix for PreR51.  Requirement for a dialogCreator function which needs to know parent GenericInterface (to access the worksession).  This fix is implemented differently in code which will be shipped for R51.
 * 
 *    Rev 1.9   Oct 09 2002 17:42:58   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.8   Sep 10 2002 14:34:46   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.7   22 May 2002 19:17:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   27 Mar 2002 20:04:38   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.5   03 May 2001 14:07:44   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   Oct 26 2000 10:47:58   DT24433
 * change to pass GIC instead of session
 * 
 *    Rev 1.3   Apr 04 2000 14:31:22   DT24433
 * changed for GIC userid change
 * 
 *    Rev 1.2   Apr 03 2000 13:27:16   DT24433
 * added delete if GI failed init
 * 
 *    Rev 1.1   Mar 21 2000 10:42:50   DT24433
 * changed to add modal as well as modeless objects to GenericInterfaceContainer
 * 
 *    Rev 1.0   Mar 02 2000 15:27:04   MCNABBGL
 * Initial revision.
 * 
 *    Rev 1.1   Feb 28 2000 16:54:50   DT24433
 * removed unused active window code
 * 
 *    Rev 1.0   Feb 15 2000 11:01:30   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.3   Aug 24 1999 14:52:40   DT24433
 * misc. cleanup
 * 
 *    Rev 1.2   Jul 20 1999 11:19:42   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:06:06   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
