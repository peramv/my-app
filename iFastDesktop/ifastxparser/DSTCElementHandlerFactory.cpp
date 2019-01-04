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

#include "DSTCElementHandlerFactory.hpp"
#include "DSTCPackageHandler.hpp"
#include "DSTCProcessHandler.hpp"
#include "TradeCBOHandler.hpp"
#include "NASUProcessHandler.hpp"
#include "NASUChildProcessHandler.hpp"
#include "AggrOrderProcessHandler.hpp"
#include "AcctMailProcessHandler.hpp"
#include "AcctMailProdProcessHandler.hpp"

using namespace xp;

namespace ELEMENT_NAME
{
   const DString IFAST_PACKAGE              = I_( "iFAST_Package" );
   const I_CHAR * BATCH                 = I_( "Batch" );

   // process name
   const I_CHAR * NASU                 = I_( "NASUProcess" );      
   const I_CHAR * AGGRORDERPROCESS     = I_( "BPAggregatedOrderProcess" );      
   const I_CHAR * PURCHASE             = I_( "Purchase" );   
   const I_CHAR * REDEMPTION           = I_( "Redemption" ); 
   const I_CHAR * EXCHANGE             = I_( "Exchange" );   
   const I_CHAR * SHAREHOLDERPROCESS   = I_( "ShareholderProcess");
	const I_CHAR * ACCTMAILPROCESS      = I_( "AccountMailProcess" );
	const I_CHAR * ACCTMAILPRDPROCESS   = I_( "AccountMailProdProcess" );
   const I_CHAR * const ACCOUNTINFOPROCESS   = I_("AccountInfoProcess");
   const I_CHAR * const ENTITYPROCESS        = I_("EntityProcess");
   const I_CHAR * const ADDRESSPROCESS       = I_("AddressProcess");
   const I_CHAR * const MGMTCOREFRESHPROCESS = I_("MgmtCoRefresh");

   // cbo name
   const I_CHAR * const TRADE                = I_( "Trade" );        
};

//******************************************************************************
const DString &DSTCElementHandlerFactory::getRootElementName()
{
   return(ELEMENT_NAME::IFAST_PACKAGE);
}

//******************************************************************************
RootHandler *DSTCElementHandlerFactory::createRootHandler()
{
   return(new DSTCPackageHandler( ELEMENT_NAME::IFAST_PACKAGE ));
}

//******************************************************************************
RootHandler *DSTCElementHandlerFactory::createRootHandler( xercesc::AttributeList &attributes )
{
   return(new DSTCPackageHandler( ELEMENT_NAME::IFAST_PACKAGE, attributes ));
}

//******************************************************************************
ProcessHandler *DSTCElementHandlerFactory::createProcessHandler( ElementHandler *parentHandler,
                                                                 const DString &elementName,
                                                                 xercesc::AttributeList &attributes )
{

   if( elementName == ELEMENT_NAME::NASU ) {
      return(new NASUProcessHandler( parentHandler, elementName, attributes ));

   } else if( elementName == ELEMENT_NAME::AGGRORDERPROCESS ) {
      return(new AggrOrderProcessHandler( parentHandler, elementName, attributes ));

   } else if( parentHandler->getName() == ELEMENT_NAME::NASU ) {
      return(new NASUChildProcessHandler( parentHandler, elementName, attributes ));

   } else if( elementName == ELEMENT_NAME::ACCTMAILPROCESS ) {
      return(new AcctMailProcessHandler( parentHandler, elementName, attributes ));

   } else if( elementName  == ELEMENT_NAME::ACCTMAILPRDPROCESS ) {
      return(new AcctMailProdProcessHandler( parentHandler, elementName, attributes ));
   }

   return(new DSTCProcessHandler( parentHandler, elementName, attributes ));
}

//******************************************************************************
CBOHandler *DSTCElementHandlerFactory::createCBOHandler( ElementHandler *parentHandler,
                                                         const DString &elementName,
                                                         xercesc::AttributeList &attributes )
{
   if( elementName == ELEMENT_NAME::TRADE ) {
      return(new TradeCBOHandler( parentHandler, elementName, attributes ));
   }
   return(NULL);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/DSTCElementHandlerFactory.cpp-arc  $
// 
//    Rev 1.11   Oct 24 2005 17:30:42   ZHANGCEL
// PET1332 FN09A -- JAcctMailProcessHandler and JAcctMailPrdProcessHandler
// 
//    Rev 1.10   Apr 18 2005 12:02:10   smithdav
// Add AggrOrderProcessHandler class.
// 
//    Rev 1.9   Nov 17 2004 15:01:02   PURDYECH
// PET910 - .NET Conversion
// 
//    Rev 1.8   Nov 16 2004 11:14:14   PURDYECH
// PET910 - .NET Conversion
// 
//    Rev 1.7   May 10 2004 18:22:02   PURDYECH
// PET910 - Xerces2 compatibility fixes
// 
//    Rev 1.6   Oct 09 2002 23:56:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Jul 04 2002 15:23:22   SMITHDAV
// NASU support and minor interface changes.
// 
//    Rev 1.4   Jun 14 2002 17:59:34   SMITHDAV
// Restored activity tracking code.
// 
//    Rev 1.3   07 Jun 2002 17:08:54   SMITHDAV
// Add support for root level attributes to turn on statistics writing and verbose conditions.
// 
//    Rev 1.2   14 May 2002 16:42:40   SMITHDAV
// put xparser code namespace xp.
// 
//    Rev 1.1   30 Apr 2002 12:05:28   SMITHDAV
// Added TradeCBOHandler.
// 
//    Rev 1.0   02 Apr 2002 14:00:42   SMITHDAV
// Initial revision.
 * 
 */
