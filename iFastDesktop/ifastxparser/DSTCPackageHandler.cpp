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
#define IFASTXPARSER_DLL

#include "DSTCPackageHandler.hpp"
#include <bfproc\GenericInterfaceContainer.hpp>
#include <bfproc\CommandDispatcher.hpp>
#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\UserSessionProcessIncludes.h>
#include <ifastcbo\DSTCUserSession.hpp>
#include <ifastdbrkr\DSTCHost.hpp>
#include <dataimpl\dse_dstcglob_vw.hpp>

//******************************************************************************
DSTCPackageHandler::DSTCPackageHandler( const DString &elementName, xercesc::AttributeList &attributes ) :
RootHandler( elementName, attributes ),
_logoffOnExit(true)
{
}

//******************************************************************************
DSTCPackageHandler::DSTCPackageHandler( const DString &elementName ) :
RootHandler( elementName ),
_logoffOnExit(true)
{
}

//******************************************************************************
void DSTCPackageHandler::writeParms( AbstractProcess *userSessionProcess, BFDocument &out )
{
   // store the "Logoff" parameter
   _logoffOnExit = ( cacheGet( I_("Logoff") ) == I_("no") )?false:true;

   if( !_logoffOnExit )
   {
      // write session id parm.
      DString sessionId;
      userSessionProcess->getField( NULL, BF::NullContainerId, SESSIONID, sessionId);
      writeParm( I_("SessionId"), sessionId, out );
   }
}

//******************************************************************************
void DSTCPackageHandler::logoff( AbstractProcess *userSessionProcess )
{
   if( _logoffOnExit )
   {
      DString strMessage;
      DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(userSessionProcess->getBFSession());
      dstcUserSession->logoff( DSTCHost::getPrimaryHost(), strMessage );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/DSTCPackageHandler.cpp-arc  $
// 
//    Rev 1.8   May 27 2004 16:29:50   SMITHDAV
// Changes to InterProcessData to move "global data" to the session level.
// 
//    Rev 1.7   May 10 2004 18:22:46   PURDYECH
// PET910 - Xerces2 compatibility fixes
// 
//    Rev 1.6   Mar 21 2003 18:48:28   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Oct 09 2002 23:56:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Oct 07 2002 17:01:08   SMITHDAV
// Changed xp::Document to BFDocument.
// 
//    Rev 1.3   Aug 02 2002 17:13:12   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
// 
//    Rev 1.2   07 Jun 2002 17:08:56   SMITHDAV
// Add support for root level attributes to turn on statistics writing and verbose conditions.
// 
//    Rev 1.1   07 Jun 2002 10:55:28   SMITHDAV
// Sync-up with Chris' changes.
// 
//    Rev 1.0   02 Apr 2002 14:00:42   SMITHDAV
// Initial revision.
 * 
 */
