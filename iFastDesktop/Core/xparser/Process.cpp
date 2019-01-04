/*******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 *
 *******************************************************************************/
#include "stdafx.h"
#include "Process.hpp"
#include <bfproc\CommandDispatcher.hpp>
#include <bfproc\AbstractProcess.hpp>
#include <bfproc\GenericInterfaceContainer.hpp>
#include <bfcbo\validationcontrol.hpp>

using namespace xp;

//******************************************************************************
Process::Process( Process &parentProcess,
                  const DString &processName,
                  bool ignoreWarnings,
                  bool validateOnly )
: _processImpl( NULL )
, _isSessionProcess( false )
, bValidateOnly_( validateOnly )
{
   if( isValidateOnly() )
   {
      ValidationControl::get().setValidateOnly();
   }

   DString commandName = I_( "BPROC_" );
   commandName += processName;

   _processImpl = createProcess( parentProcess,
                                 commandName,
                                 !parentProcess._isSessionProcess,
                                 ignoreWarnings );

}

//******************************************************************************
Process::Process( Process &parentProcess, const DString &commandName )
: _processImpl( NULL )
, _isSessionProcess( true )
, bValidateOnly_( false )
{
   _processImpl = createProcess( parentProcess,
                                 commandName,
                                 false,
                                 false );
}

//******************************************************************************
Process::Process( GenericInterfaceContainer& gic, const DString &commandName )
: _processImpl( NULL )
, _isSessionProcess( true )
, bValidateOnly_( false )
{
   _processImpl = createProcess( &gic,
                                 NULL,
                                 commandName,
                                 false,
                                 false );
}

//******************************************************************************
Process::~Process()
{
   if( isValidateOnly() )
   {
      ValidationControl::get().unsetValidateOnly();
   }

   if( _processImpl != NULL )
   {
      try
      {
         //_processImpl->cancel(_processImpl);
         _processImpl->getGIContainer()->destroy(_processImpl);
      }
      catch( ... )
      {
//         assert(0);
      }

   }
}

//******************************************************************************
bool Process::commit()
{
   return(_processImpl->ok(_processImpl));
}

//******************************************************************************
const GenericInterfaceContainer& Process::getGIContainer() const 
{
   const GenericInterfaceContainer* pGIC = _processImpl->getGIContainer();
   assert( pGIC );
   return *pGIC;
}

//******************************************************************************
GenericInterfaceContainer& Process::getGIContainer() 
{
   GenericInterfaceContainer* pGIC = _processImpl->getGIContainer();
   assert( pGIC );
   return *pGIC;
}

//******************************************************************************
SEVERITY Process::getHighestSeverity()
{
   CONDITIONVECTOR conditions;
   _processImpl->getAllErrors(_processImpl, conditions);

   SEVERITY highestSeverity = NO_CONDITION;
   for( unsigned int i = 0; i <conditions.size(); i++ )
   {
      if( conditions[i]->getSeverity() > highestSeverity )
      {
         highestSeverity = conditions[i]->getSeverity();
      }
   }

   return(highestSeverity);

}

//******************************************************************************
AbstractProcess *Process::createProcess( Process &parentProcess,
                                         const DString &commandName,
                                         bool bModal,
                                         bool ignoreWarnings )
{
   return(createProcess( parentProcess.getProcessImpl()->getGIContainer(),
                         parentProcess.getProcessImpl(),
                         commandName,
                         bModal,
                         ignoreWarnings ));
}

//******************************************************************************
AbstractProcess *Process::createProcess( GenericInterfaceContainer* gic,
                                         AbstractProcess *parentProcess,
                                         const DString &commandName,
                                         bool bModal,
                                         bool ignoreWarnings )
{
   MAKEFRAMEAUTOPROMOTE2( CND::XPARSER_CONDITION, I_("Process"), I_("createProcess") )

   GenericInterface *gi = NULL;

   E_COMMANDRETURN eRtn = CommandDispatcher::getInstance()->invokeCommand( gic,
                                                                           parentProcess,
                                                                           commandName.c_str(),
                                                                           PROC_NO_TYPE,
                                                                           bModal,
                                                                           &gi );
   if( eRtn == CMD_FAILURE )
   {
      PROMOTECONDITIONS();
      Frame *conditionFrame = MYFRAME();
      conditionFrame->packConditions();
      int conditionCount = conditionFrame->getCount(  );
      assert( conditionCount > 0 );

      CONDITIONVECTOR conditions;
      for( int i = 0; i < conditionCount; i++ )
      {
         conditions.push_back( new Condition( *conditionFrame->getCondition( i ) ) );
      }
      throw conditions;
   }

   AbstractProcess *ap = dynamic_cast<AbstractProcess *>(gi);
   ap->setIgnoreWarningsOnOk2( ignoreWarnings );
//CP20030526   ap->setActionTypeOnOk2( validateOnly );

   return(ap);
}

//******************************************************************************
xp::UserSessionProcess::UserSessionProcess( GenericInterfaceContainer& gic )
: Process( gic, CMD_BPROC_USER_SESSION )
{
}

//******************************************************************************
xp::WorkSessionProcess::WorkSessionProcess( xp::UserSessionProcess &usProcess )
: Process( usProcess, CMD_BPROC_WORK_SESSION )
{
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/Process.cpp-arc  $
//
//   Rev 1.19   Nov 18 2005 16:12:14   FENGYONG
//Incident 414773 - do not cancel process in destructor
//
//   Rev 1.18   Apr 27 2005 13:02:16   smithdav
//Fix bug in which CONDITIONVECTOR is thrown with pointers to conditions that are destroyed before they are caught.
//
//   Rev 1.17   Oct 22 2004 09:07:12   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.16   May 14 2004 16:15:44   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.15   May 30 2003 09:37:44   PURDYECH
//Didn't make 'validate only' fix for second constructor.  Sigh!
//
//   Rev 1.14   May 26 2003 14:24:32   PURDYECH
//When in 'validate only' we now use ValidationControl BFExecutionContext stuff.
// 
//    Rev 1.13   Jan 29 2003 09:45:18   PURDYECH
// Conditions weren't being handled properly when a Process failed.
// 
//    Rev 1.12   Jan 14 2003 11:05:26   PURDYECH
// DataGroupid parentage knowledge
// 
//    Rev 1.11   Dec 18 2002 11:23:14   SMITHDAV
// Fixed Process initiation error problem.
// 
//    Rev 1.10   Oct 31 2002 10:11:30   PURDYECH
// loop counter was uninitialized in getHighestSeverity()
// 
//    Rev 1.9   Oct 09 2002 17:43:18   PURDYECH
// New PVCS Database
// 
//    Rev 1.8   Oct 03 2002 18:42:54   IVESPAUL
// Added code to support validateOnly process action.
//
//    Rev 1.7   Sep 23 2002 18:29:18   SMITHDAV
// Process HighestSeverity changes.
//
//    Rev 1.6   Aug 30 2002 09:39:32   SMITHDAV
// Remove unneeded header include.
//
//    Rev 1.5   Aug 06 2002 12:00:32   SMITHDAV
// Handle commit conditions.
//
//    Rev 1.4   Jul 29 2002 14:13:12   SMITHDAV
// Initialize processes with "ignoreWarningOnOk2" state when appropriate.
//
//    Rev 1.3   16 May 2002 11:55:44   SMITHDAV
// Process changes to add xp::WorkSessionProcess
// and xp::UserSessionProcess classes and make
// top level process modeless.
//
//    Rev 1.2   14 May 2002 16:42:58   SMITHDAV
// put xparser code namespace xp.
//
//    Rev 1.1   01 May 2002 17:11:36   SMITHDAV
// Fix bug on ok and cancel. (NULL pointer dereferenced)
//
//    Rev 1.0   02 Apr 2002 13:50:06   SMITHDAV
// Initial revision.
 *
 */