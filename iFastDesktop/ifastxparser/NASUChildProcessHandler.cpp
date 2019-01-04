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

#include "nasuchildprocesshandler.hpp"
#include <bfproc\abstractprocess.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\interprocessdata.hpp>
#include <ifastbp\nasuprocessincludes.h>
#include <dataimpl\dse_dstcglob_vw.hpp>


using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME = I_( "NASUChildProcessHandler" );

   const I_CHAR * const SHAREHOLDER_NUM = I_( "ShareholderNum" );
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const ENTITY_ID = I_( "EntityId" );

   const I_CHAR * const Y = I_("Y");
   const I_CHAR * const N = I_("N");

}

namespace ELEMENT_NAME
{
   extern const I_CHAR * SHAREHOLDERPROCESS;
}
namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId LastActiveEntityId;
}
//******************************************************************************
NASUChildProcessHandler::NASUChildProcessHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes ) :
DSTCProcessHandler( parentHandler, elementName, attributes )
{
}


//******************************************************************************
void NASUChildProcessHandler::setProcessParms( AbstractProcess *process )
{
   InterProcessData& ipd = process->getGIContainer()->getInterProcessData();

   if( getName() == ELEMENT_NAME::SHAREHOLDERPROCESS )
   {
      ipd.setParameter( NASULIT::CREATING_SHAREHOLDER, Y );
      cachePut( NASULIT::CREATING_SHAREHOLDER, Y );
   }
   else
   {
      const DString &creatingSharholder = cacheGet( NASULIT::CREATING_SHAREHOLDER );
      ipd.setParameter( NASULIT::CREATING_SHAREHOLDER, creatingSharholder );

      if( creatingSharholder == Y )
      {
         ipd.setParameter( SHAREHOLDER_NUM, cacheGet( SHAREHOLDER_NUM ) );
      }
   }

   ipd.setParameter( NASULIT::CREATING_ACCOUNT, Y );
   ipd.setParameter( ACCOUNT_NUM, cacheGet( ACCOUNT_NUM ) );
   ipd.setParameter( NASULIT::TRXNS_ERROR, N );
   ipd.setParameter( ENTITY_ID, cacheGet( ENTITY_ID ) );


   DSTCProcessHandler::setProcessParms( process );
}

//******************************************************************************
void NASUChildProcessHandler::getProcessParms( AbstractProcess *process )
{
   DString parameter;
   InterProcessData& ipd = process->getGIContainer()->getInterProcessData();

   ipd.getParameter( ACCOUNT_NUM, parameter );
   if( parameter != NULL_STRING )
   {
      cachePut( ACCOUNT_NUM, parameter );
      process->setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, parameter );

   }

   ipd.getParameter( SHAREHOLDER_NUM, parameter );
   if( parameter != NULL_STRING )
   {
      cachePut( SHAREHOLDER_NUM, parameter );
      process->setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, parameter );
   }

   ipd.getParameter( ENTITY_ID, parameter );
   if( parameter != NULL_STRING )
   {
      cachePut( ENTITY_ID, parameter );
      process->setGlobal( WORK_GLOBAL, ifds::LastActiveEntityId, parameter );
   }

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/NASUChildProcessHandler.cpp-arc  $
// 
//    Rev 1.9   Nov 17 2004 15:01:10   PURDYECH
// PET910 - .NET Conversion
// 
//    Rev 1.8   Nov 16 2004 11:14:30   PURDYECH
// PET910 - .NET Conversion
// 
//    Rev 1.7   May 27 2004 16:29:54   SMITHDAV
// Changes to InterProcessData to move "global data" to the session level.
// 
//    Rev 1.6   May 10 2004 18:23:16   PURDYECH
// PET910 - Xerces2 compatibility fixes
// 
//    Rev 1.5   Oct 09 2002 23:56:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Jul 12 2002 15:25:30   FENGYONG
// Add entity Id to global
// 
//    Rev 1.3   Jul 04 2002 15:23:22   SMITHDAV
// NASU support and minor interface changes.
// 
//    Rev 1.2   Jul 03 2002 10:54:12   SMITHDAV
// Write specific implementation.
// 
//    Rev 1.1   Jun 14 2002 17:59:36   SMITHDAV
// Restored activity tracking code.
// 
//    Rev 1.0   07 Jun 2002 10:56:52   SMITHDAV
// Initial revision.
 * 
 */
