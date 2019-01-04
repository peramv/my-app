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

#include "aggrorderprocesshandler.hpp"
#include <bfproc\abstractprocess.hpp>
#include <bfcbo\hosttransactioncontainer.hpp>
#include <bfcbo\bfworksession.hpp>
#include <xparser\executionresult.hpp>
#include <dataimpl\dse_dstcglob_vw.hpp>

extern BF_OBJ_TYPE OBJ_TYPE_AGGREGATED_ORDER_LIST;

using namespace xp;

namespace CND
{
   extern const long WARN_AggregatedOrder_Loss;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AggrOrderProcessHandler" );
}

namespace ELEMENT_NAME
{
   extern const I_CHAR * SHAREHOLDERPROCESS;
}
namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId LastActiveEntityId;
   extern CLASS_IMPORT const BFTextFieldId UpdateStatus;
   extern CLASS_IMPORT const BFTextFieldId LossWarnMsg;



}
//******************************************************************************
AggrOrderProcessHandler::AggrOrderProcessHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes ) :
DSTCProcessHandler( parentHandler, elementName, attributes )
{
}


//******************************************************************************
void AggrOrderProcessHandler::writeCommitConditions( AbstractProcess *wsProcess, BFDocument &out, xp::ProcessResult &result )
{
   BFWorkSession *workSession = wsProcess->getBFWorkSession();
   HostTransactionContainerIterator htcIter( &workSession->getHostTransactionContainer() );

   htcIter.begin();//start the iteration
   while( !htcIter.end() )
   {

      //for now assume there is only one type of transaction
      //if( strKey.find( I_( "AggrOrdert" ) ) != DString::npos )  {

      const BFData &response = (*htcIter.getResponse());

      //DString updateStatus;
      //response.getElementValue( ifds::UpdateStatus, updateStatus, BFDataField::USE_MASK | BFDataField::USE_SUBSTITUTES );

      DString lossWarnMsg;
      response.getElementValue( ifds::LossWarnMsg, lossWarnMsg, BFDataField::USE_MASK | BFDataField::USE_SUBSTITUTES );
      lossWarnMsg.strip();
      if( lossWarnMsg != NULL_STRING )
      {
         // need to write the condition based on the above values.
         writeCondition( Condition( CND::IFASTXPARSER_CONDITION, 
                                    I_("AggrOrderProcessHandler::writeCommitConditions"),
                                    CND::WARN_AggregatedOrder_Loss,
                                    CM_STRINGIFY( CND::WARN_AggregatedOrder_Loss ),
                                    __FILE__, __LINE__, FALSE,
                                    g_conditionManager.getPath() ), out, result );
      }

      ++htcIter;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/AggrOrderProcessHandler.cpp-arc  $
// 
//    Rev 1.2   Oct 05 2009 07:52:18   purdyech
// Use new Condition() argument scheme
// 
//    Rev 1.1   Apr 25 2005 14:12:26   yingbaol
// Incident 279739:Add condition for aggregation order loss situation
// 
//    Rev 1.0   Apr 18 2005 12:01:42   smithdav
// Initial revision.
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
