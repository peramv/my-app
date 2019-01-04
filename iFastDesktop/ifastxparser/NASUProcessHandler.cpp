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

#include "nasuprocesshandler.hpp"
#include <bfproc\abstractprocess.hpp>
#include <dataimpl\dse_dstcglob_vw.hpp>


using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME = I_( "NASUProcessHandler" );
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
NASUProcessHandler::NASUProcessHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes ) :
DSTCProcessHandler( parentHandler, elementName, attributes )
{
}


//******************************************************************************
void NASUProcessHandler::writeCommitParms( AbstractProcess *wsProcess, BFDocument &out )
{
   DString parameter;

   wsProcess->getGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, parameter );
   writeParm(I_("ShrNum"), parameter, out );

   wsProcess->getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, parameter );
   writeParm(I_("AccountNum"), parameter, out );

   wsProcess->getGlobal( WORK_GLOBAL, ifds::LastActiveEntityId, parameter );
   writeParm(I_("EntityId"), parameter, out );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/NASUProcessHandler.cpp-arc  $
// 
//    Rev 1.7   Nov 17 2004 15:01:12   PURDYECH
// PET910 - .NET Conversion
// 
//    Rev 1.6   Nov 16 2004 11:14:32   PURDYECH
// PET910 - .NET Conversion
// 
//    Rev 1.5   May 10 2004 18:23:22   PURDYECH
// PET910 - Xerces2 compatibility fixes
// 
//    Rev 1.4   Oct 09 2002 23:56:32   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Oct 07 2002 17:01:16   SMITHDAV
// Changed xp::Document to BFDocument.
// 
//    Rev 1.2   Aug 02 2002 17:13:36   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
// 
//    Rev 1.1   Jul 12 2002 15:25:44   FENGYONG
// Add EntityId to Global
// 
//    Rev 1.0   Jul 04 2002 15:24:08   SMITHDAV
// Initial revision.
 * 
 */
