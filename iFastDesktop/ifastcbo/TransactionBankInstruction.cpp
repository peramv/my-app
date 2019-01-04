#error "This file is obsolete!"
//no longer used anywhere
/*
#include "stdafx.h"
#include "transactionbankinstruction.hpp"
#include <dataimpl\dse_dstc0055_vw.hpp>
#include <dataimpl\dse_dstc0055_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSACTIONBANKINSTR;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "TransactionBankInstruction" );
}

//************************************************************************************
TransactionBankInstruction::TransactionBankInstruction( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList();
}

//*************************************************************************************
TransactionBankInstruction::~TransactionBankInstruction()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//*************************************************************************************
SEVERITY TransactionBankInstruction::init( const DString& strTransId, 
                                           const DString& strPendingRid,
                                           const DString& strTransPending, 
                                           const DString& dstrTrack,
                                           const DString& dstrPageName ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0055_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::TransId, strTransId  );
   queryData.setElementValue( ifds::PendingRid, strPendingRid );
   queryData.setElementValue( ifds::TransPending, strTransPending  );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::TRANSACTIONBANKINSTR, queryData, ifds::DSTC0055_VW, DSTCRequestor( getSecurity() ) );


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionBankInstruction.cpp-arc  $
 * 
 *    Rev 1.12   Nov 14 2004 14:58:10   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.11   Sep 29 2003 14:44:06   popescu
 * this file is obsolete
 * 
 *    Rev 1.10   Mar 21 2003 18:27:34   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Oct 09 2002 23:55:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Aug 29 2002 12:56:56   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.7   22 May 2002 18:30:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   03 May 2001 14:07:14   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Apr 03 2001 15:20:34   YINGBAOL
 * clean up
 * 
 *    Rev 1.4   Jan 18 2001 16:10:38   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.3   Dec 17 2000 20:24:46   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.2   Dec 06 2000 14:55:46   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.1   Nov 01 2000 11:06:22   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.0   Feb 15 2000 11:00:08   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.5   Jan 07 2000 12:51:36   YINGZ
 * add setObjectAsList
 * 
 *    Rev 1.4   Dec 12 1999 16:25:56   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/