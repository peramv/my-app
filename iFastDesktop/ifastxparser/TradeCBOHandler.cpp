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

#include "tradecbohandler.hpp"
#include <bfproc\abstractprocess.hpp>
#include <bfcbo\hosttransactioncontainer.hpp>
#include <bfcbo\bfworksession.hpp>
#include <dataimpl\dse_dstc0115_vw.hpp>
#include <dataimpl\dse_dstc0115_req.hpp>
#include <dataimpl\dse_dstc0064_vw.hpp>

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME = I_( "TradeCBOHandler" );

   const I_CHAR * const END = I_( "end" );

   const I_CHAR * const YES        = I_("Y");
   const I_CHAR * const NO         = I_("N");

   const I_CHAR * const PURCHASE_PERM = I_( "PurchasePerm" );
   const I_CHAR * const REDEMPTION_PERM = I_( "RedemptionPerm" );
   const I_CHAR * const EXCHANGE_PERM = I_( "ExchangePerm" );
}

namespace UAF
{

   extern CLASS_IMPORT I_CHAR * const TRADING_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const TRADING_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const TRADING_EXCHANGE;
}

namespace CND
{
   extern const long ERR_NO_PERMISSION_FOR_TRADE;
}

//******************************************************************************
TradeCBOHandler::TradeCBOHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes )
: CBOHandler( parentHandler, elementName, attributes )
, transNum_( NULL_STRING )
{
}

//******************************************************************************
SEVERITY TradeCBOHandler::doValidate( CBOAction action, 
                                      AbstractProcess *process, 
                                      const BFContainerId& idContainer )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTXPARSER_CONDITION, I_("TradeCBOHandler"), I_("doValidate") )

   if( action == xp::CBO_ACTION_ADD )
   {
      bool permission = true;
      DString userAccessFunctionCode, strParamTag, strPerm;

      const DString &processName = getParent()->getName();

      if( processName == I_("Purchase") )
      {
         userAccessFunctionCode = UAF::TRADING_PURCHASE;
         strParamTag = PURCHASE_PERM;
      }
      else if( processName == I_("Redemption") )
      {
         userAccessFunctionCode = UAF::TRADING_REDEMPTION;
         strParamTag = REDEMPTION_PERM;
      }
      else if( processName == I_("Exchange") )
      {
         userAccessFunctionCode = UAF::TRADING_EXCHANGE;
         strParamTag = EXCHANGE_PERM;
      }

      process->getParameter(strParamTag, strPerm);

      if( strPerm.strip() == YES )
         permission = true;
      else if( strPerm == NO )
         permission = false;
      else if( !( process->hasCreatePermission( userAccessFunctionCode.c_str() ) ) )
         permission = false;

      if( !permission )
      {
         ADDCONDITIONFROMFILE( CND::ERR_NO_PERMISSION_FOR_TRADE );
      }

   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void TradeCBOHandler::writeFields( CBOAction action, 
                                   AbstractProcess *process, 
                                   const BFContainerId& idContainer,
                                   BFDocument &out ) 
{
   process->getField( process, idContainer, ifds::TransNum, transNum_, true );
   transNum_.strip();
   transNum_.stripLeading( '0' );

   writeField( ifds::EffectiveDate, process, idContainer, out );
   writeField( ifds::SettleDate,    process, idContainer, out );

}

//******************************************************************************
void TradeCBOHandler::writeCommitFields( CBOAction action, 
                                         AbstractProcess *wsProcess, 
                                         BFDocument &out )
{
   if( (action == xp::CBO_ACTION_ADD || action == xp::CBO_ACTION_UPDATE) && transNum_ != NULL_STRING )
   {
      BFWorkSession *workSession = wsProcess->getBFWorkSession();
      HostTransactionContainerIterator htcIter( &workSession->getHostTransactionContainer() );

      htcIter.begin();//start the iteration
      while( !htcIter.end() )
      {
         DString strKey = htcIter.strKey();
         if( strKey.find( I_( "TransNum" ) ) != DString::npos && strKey.find( transNum_ ) != DString::npos )
         {
            const BFData &response = (*htcIter.getResponse());

            writeField(response, ifds::ConfNum, wsProcess, out);
            writeField(response, ifds::BODate,  wsProcess, out);
            writeField(response, ifds::BOTime,  wsProcess, out);
            writeField(response, ifds::BOZone,  wsProcess, out);
            writeField(response, ifds::FIDate,  wsProcess, out);
            writeField(response, ifds::FITime,  wsProcess, out);
            writeField(response, ifds::FIZone,  wsProcess, out);

            break;
         }
         ++htcIter;
      }

   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/TradeCBOHandler.cpp-arc  $
// 
//    Rev 1.8   Jan 27 2005 16:10:06   smithdav
// Made enum name changes related to base changes.
// 
//    Rev 1.7   Nov 16 2004 11:14:32   PURDYECH
// PET910 - .NET Conversion
// 
//    Rev 1.6   May 10 2004 18:23:38   PURDYECH
// PET910 - Xerces2 compatibility fixes
// 
//    Rev 1.5   Mar 21 2003 18:48:34   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Oct 09 2002 23:56:32   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Oct 07 2002 17:01:18   SMITHDAV
// Changed xp::Document to BFDocument.
// 
//    Rev 1.2   Aug 21 2002 15:37:48   FENGYONG
// modify a trade also need dealtime return back
// 
//    Rev 1.1   Aug 02 2002 17:13:38   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
// 
//    Rev 1.0   07 Jun 2002 10:56:52   SMITHDAV
// Initial revision.
 * 
 */
