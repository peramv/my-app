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
// ^FILE   : AbstractCommandDispatcher.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 11/17/1998
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AbstractCommandDispatcher
//    This class provides an interface for command handlers.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "bpglobal.h"
#include "abstractcommanddispatcher.hpp"
#include "abstractfactory.hpp"
#include "command.hpp"
#include <idistring.hpp>
#include <assert.h>
#include <bfutil/seh_exception.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AbstractCommandDispatcher" );

   const I_CHAR * const DEREGISTERDISPATCHER = I_( "deregisterDispatcher" );
   const I_CHAR * const DEREGISTERFACTORY = I_( "deregisterFactory" );
   const I_CHAR * const INVOKECOMMANDFORREGISTEREDDISPATCHERS =
   I_( "invokeCommandForRegisteredDispatchers" );
   const I_CHAR * const REGISTERDISPATCHER   = I_( "registerDispatcher" );
   const I_CHAR * const REGISTERFACTORY   = I_( "registerFactory" );

   // Literals
   const I_CHAR * const TYPE = I_( "TYPE" );
}

namespace CND
{  // Conditions used
   extern const long BP_ERR_DUPLICATE_DISPATCHER;
   extern const long BP_ERR_SEH_EXCEPTION;
   extern const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

AbstractCommandDispatcher::AbstractCommandDispatcher()
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

AbstractCommandDispatcher::~AbstractCommandDispatcher()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _dispatchers.clear();
}

//******************************************************************************

void AbstractCommandDispatcher::deregisterDispatcher(
                                                    AbstractCommandDispatcher *rpDispatcher
                                                    )
{  // Find in list
   EXECHISTI( I_( "deregisterDispatcher( AbstractCommandDispatcher * )" ) );

   HANDLERS_ITER iter;

   for( iter = _dispatchers.begin(); iter != _dispatchers.end(); ++iter )
   {
      if( ( *iter ).second == rpDispatcher )
      {  // Remove from list
         _dispatchers.erase( iter );
         return;
      }
   }
   // Dispatcher not found
   assert( 0 );
}

//******************************************************************************


//******************************************************************************

void AbstractCommandDispatcher::registerDispatcher(
                                                  AbstractCommandDispatcher *rpDispatcher,
                                                  int type
                                                  )
{  
   EXECHISTI( I_( "registerDispatcher( AbstractCommandDispatcher *, int )" ) );


   if( !rpDispatcher )
   {  // Shouldn't try to register a null dispatcher
      assert( 0 );
      return;
   }

   if( _dispatchers.end() != _dispatchers.find( type ) )
   {  // Only allow one dispatcher per type
      DString strIDI;
      addIDITagValue( strIDI, TYPE, type );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, REGISTERDISPATCHER,
                         CND::BP_ERR_DUPLICATE_DISPATCHER, strIDI );
   }

   // add to list
   _dispatchers.insert( std::make_pair( type, rpDispatcher ) );
}

//******************************************************************************


//******************************************************************************
//              Protected Methods
//******************************************************************************

E_COMMANDRETURN AbstractCommandDispatcher::invokeCommandForRegisteredDispatchers(
                                                                                GenericInterfaceContainer *rpGIC,
                                                                                GenericInterface *rpGIParent,
                                                                                const Command& rCommand,
                                                                                GenericInterface **rpModeless       // NULL or pointer if active modeless
                                                                                )
{
   EXECHISTI( I_( "invokeCommandForRegisteredDispatchers( GenericInterfaceContainer *, GenericInterface *, const Command &, GenericInterface ** )" ) );

   HANDLERS_ITER iter;
   E_COMMANDRETURN rtn = CMD_NO_RETURN;

   try
   {
      for( iter = _dispatchers.begin(); iter != _dispatchers.end(); ++iter )
      {
         if( rCommand.isCommandTypeOf( ( *iter ).first ) )
         {
            // Split out to facilitate debugging
            AbstractCommandDispatcher *rpDispatcher = ( *iter ).second;
            return(rpDispatcher->invokeCommand( rpGIC, rpGIParent, 
                                                rCommand, rpModeless ));
         }
      }
      // No one wanted the command
      rtn = CMD_NOT_FOUND;
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, INVOKECOMMANDFORREGISTEREDDISPATCHERS, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, 
                      INVOKECOMMANDFORREGISTEREDDISPATCHERS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfproc/AbstractCommandDispatcher.cpp-arc  $
//
//   Rev 1.10   Feb 20 2009 14:48:24   purdyech
//ZTS Revision 6
//
//   Rev 1.9   Feb 12 2004 12:19:04   PURDYECH
//Catch SEH_Exceptions and throw them as BP_ERR_SEH_EXCEPTION conditions.
 * 
 *    Rev 1.8   Jan 14 2003 11:03:40   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.7   Jan 06 2003 16:42:54   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 17:40:46   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.5   Aug 29 2002 13:47:10   PURDYECH
 * Base Condition split out
 * 
 *    Rev 1.4   22 May 2002 17:57:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   27 Mar 2002 19:47:30   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.2   Oct 26 2000 10:35:48   DT24433
 * change to pass GIC instead of session
 * 
 *    Rev 1.1   Mar 02 2000 10:54:38   DT24433
 * added factory registration
 * 
 *    Rev 1.0   Feb 15 2000 10:57:34   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Jul 20 1999 11:13:10   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:01:44   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
