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
// ^FILE   : CommandDispatcher.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 11/17/1998
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : CommandDispatcher
//    This class manages processes.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "BPGlobal.h"
#include "CommandDispatcher.hpp"
#include "Command.hpp"
#include "GenericInterface.hpp"
#include "GenericInterfaceContainer.hpp"
#include <assert.h>
#include <bfutil/seh_exception.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "CommandDispatcher" );

   const I_CHAR * const GETINSTANCE = I_( "getInstance" );
   const I_CHAR * const INVOKECOMMAND = I_( "invokeCommand" );
   const I_CHAR * const INVOKECOMMAND2 = I_( "invokeCommand2" );
   const I_CHAR * const KILLINSTANCE = I_( "killInstance" );
}

namespace CND
{  // Conditions used
   extern const long BP_ERR_NO_PARENT_EXISTS;
   extern const long BP_ERR_SEH_EXCEPTION;
   extern const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Class Methods
//******************************************************************************

CommandDispatcher *CommandDispatcher::_pCommandDispatcher = NULL;

//******************************************************************************

CommandDispatcher *CommandDispatcher::getInstance()
{
   TRACE_METHOD( CLASSNAME, GETINSTANCE );

   if( !_pCommandDispatcher )
   {
      _pCommandDispatcher = new CommandDispatcher();
   }
   return(_pCommandDispatcher);
}

//******************************************************************************

void CommandDispatcher::killInstance()
{
   TRACE_METHOD( CLASSNAME, KILLINSTANCE );

   delete _pCommandDispatcher;
   _pCommandDispatcher = NULL;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

E_COMMANDRETURN CommandDispatcher::invokeCommand(
                                                GenericInterfaceContainer *rpGIC,
                                                GenericInterface *rpGIParent,
                                                const I_CHAR *szCommand,
                                                E_PROCESSTYPE type,
                                                bool bModal,
                                                GenericInterface **rpGIModelessOut      // NULL or pointer if active modeless
                                                )
{  // Look up command to create Command class and then use protected
   EXECHISTI( I_( "invokeCommand( GenericInterfaceContainer *, GenericInterface *, const I_CHAR *, E_PROCESSTYPE, bool, GenericInterface ** )" ) );
   //  invokeCommand to direct to correct place.

   E_COMMANDRETURN cmdRtn = CMD_FAILURE;
   Command cmd;

   try
   {
      assert( rpGIC != NULL );
      if( cmd.init( szCommand, type, bModal ) <= WARNING )
      {
         // Here we set the key for this specific creation - currently we are
         // allowing only one per user.
         cmd.setKey( cmd.getName() );

         if( rpGIParent )
         {

            GenericInterface *rpGI = NULL;
            if( !bModal )
            {  // Only look for modeless matches
               rpGI = rpGIParent->getGIContainer()->findGI( rpGIParent->getBFSession(),
                                                            cmd.getKey() );
            }
            if( rpGI )
            {  // Already exists, go to existing one
               if( rpGI->modelessSetFocus( rpGIParent ) )
               {
                  cmdRtn = CMD_MODELESS_INPROCESS;
                  if( rpGIModelessOut )
                  {  // User wants pointer, so return one we found
                     *rpGIModelessOut = rpGI;
                  }
               }
               return(cmdRtn);
            }
         }
         cmdRtn = invokeCommandForRegisteredDispatchers( rpGIC, rpGIParent,
                                                         cmd, rpGIModelessOut );
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, INVOKECOMMAND, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, INVOKECOMMAND,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(cmdRtn);
}

//******************************************************************************

E_COMMANDRETURN CommandDispatcher::invokeCommand(
                                                GenericInterface *rpGIParent,
                                                const I_CHAR *szCommand,
                                                E_PROCESSTYPE type,
                                                bool bModal,
                                                GenericInterface **rpGIModelessOut      // NULL or pointer if active modeless
                                                )
{  // Use main invokeCommand method pulling session from parent
   EXECHISTI( I_( "invokeCommand( GenericInterface *, const I_CHAR *, E_PROCESSTYPE, bool, GenericInterface ** )" ) );

   if( !rpGIParent )
   {  // bad, if no parent
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, INVOKECOMMAND2,
                      CND::BP_ERR_NO_PARENT_EXISTS );

      return(CMD_FAILURE);
   }
   return(invokeCommand( rpGIParent->getGIContainer(), rpGIParent, szCommand,
                         type, bModal, rpGIModelessOut ));
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
//              Private Methods
//******************************************************************************

CommandDispatcher::CommandDispatcher()
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );
}

//******************************************************************************

CommandDispatcher::~CommandDispatcher()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfproc/CommandDispatcher.cpp-arc  $
//
//   Rev 1.10   Feb 20 2009 14:48:36   purdyech
//ZTS Revision 6
//
//   Rev 1.9   Feb 12 2004 12:19:12   PURDYECH
//Catch SEH_Exceptions and throw them as BP_ERR_SEH_EXCEPTION conditions.
 * 
 *    Rev 1.8   Jan 14 2003 11:04:06   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.7   Jan 06 2003 16:43:28   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 17:40:54   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.5   Aug 29 2002 13:47:16   PURDYECH
 * Base Condition split out
 * 
 *    Rev 1.4   03 May 2001 14:03:12   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.3   Oct 26 2000 10:38:54   DT24433
 * change to pass GIC instead of session
 * 
 *    Rev 1.2   Apr 07 2000 09:34:40   DT24433
 * removed userID parm to findGI
 * 
 *    Rev 1.1   Apr 04 2000 14:41:26   DT24433
 * changed for GIC userid change
 * 
 *    Rev 1.0   Feb 15 2000 10:57:34   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.3   Jan 06 2000 14:08:44   DT24433
 * changed to not search GIC for modal commands
 * 
 *    Rev 1.2   Jul 20 1999 11:14:00   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:01:58   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
