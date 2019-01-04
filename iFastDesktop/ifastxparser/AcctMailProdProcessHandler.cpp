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

#include "AcctMailProdProcessHandler.hpp"
#include <bfproc\abstractprocess.hpp>
#include <dataimpl\dse_dstcglob_vw.hpp>


using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AcctMailProdProcessHandler" );
}

namespace ELEMENT_NAME
{
   extern const I_CHAR * ACCTMAILPROCESS;
}
namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
}
//******************************************************************************
AcctMailProdProcessHandler::AcctMailProdProcessHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes ) :
DSTCProcessHandler( parentHandler, elementName, attributes )
{
}


//******************************************************************************
void AcctMailProdProcessHandler::writeCommitParms( AbstractProcess *wsProcess, BFDocument &out )
{
   DString parameter;

   wsProcess->getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, parameter );
   writeParm(I_("AccountNum"), parameter, out );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/AcctMailProdProcessHandler.cpp-arc  $
// 
//    Rev 1.0   Oct 24 2005 17:34:32   ZHANGCEL
// Initial revision.
 * 
 */
