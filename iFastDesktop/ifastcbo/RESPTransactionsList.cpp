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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPTransactionsList.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 20/01/2000
//
// ^CLASS    : RESPTransactionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "resptransactionslist.hpp"
#include "resptransactionsdetails.hpp"
#include <ifastdataimpl\dse_dstc0111_vw.hpp>
#include <ifastdataimpl\dse_dstc0111_req.hpp>

namespace CND
{
   extern CLASS_IMPORT const long ERR_NO_PENDING_TRADES_FOUND;
   extern CLASS_IMPORT const long ERR_NO_PROCESSED_TRADES_FOUND;
}

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "RESPTransactionsList" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESPTRANSACTIONS_DETAILS;
}


//
// Constructors/Destructors
//
//******************************************************************************
RESPTransactionsList::RESPTransactionsList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_requestData(ifds::DSTC0111_REQ),
_accountNum (NULL_STRING),
_idDataGroup (BF::HOST)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//******************************************************************************
RESPTransactionsList::~RESPTransactionsList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY RESPTransactionsList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData( DSTC_REQUEST::RESPTRANSACTIONS_DETAILS, _requestData, ifds::DSTC0111_VW, DSTCRequestor( getSecurity(), false ) );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RESPTransactionsList::initNew (const DString& accountNum, 
                                        const DString historyPending)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init(int, DString&)"));
   _accountNum = accountNum;
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY RESPTransactionsList::init (const DString& dstrAccountNum, 
                                     const DString& dstrHistoryPending, 
                                     const DString& dstrTransId,
									 const DString& dstrTransType,
									 const DString& dstrRESPBenefId,
									 const DString& dstrRESPBenefName,
									 const DString& dstrFromDate,
									 const DString& dstrToDate,
									 const DString& dstrDepositType,
									 const DString& dstrRedCode,
                                     const DString& dstrTfrStat,
									 const DString& dstrRepHRDC,
									 const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init(int, DString&)"));

   DString mgmtCoIdOut;

   _accountNum = dstrAccountNum;
   _idDataGroup = idDataGroup;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   _requestData.setElementValue( ifds::HistoryPending, dstrHistoryPending );
   _requestData.setElementValue( ifds::ReqTransid, dstrTransId );
   _requestData.setElementValue( ifds::RESPBenefId, dstrRESPBenefId );
   _requestData.setElementValue( ifds::BeneName, dstrRESPBenefName );
   _requestData.setElementValue( ifds::FromDate, dstrFromDate );
   _requestData.setElementValue( ifds::ToDate, dstrToDate );
   _requestData.setElementValue( ifds::DepositType, dstrDepositType );
   _requestData.setElementValue( ifds::RedCode, dstrRedCode );
   _requestData.setElementValue( ifds::TfrStat, dstrTfrStat );
   _requestData.setElementValue( ifds::RepHRDC, dstrRepHRDC );
   _requestData.setElementValue( ifds::TransType, dstrTransType );

   DSTCRequestor requestor( getSecurity(), false );
   requestor.filterHostCondition (CND::ERR_NO_PENDING_TRADES_FOUND);
   requestor.filterHostCondition (CND::ERR_NO_PROCESSED_TRADES_FOUND);
   
   ReceiveData (DSTC_REQUEST::RESPTRANSACTIONS_DETAILS, _requestData, ifds::DSTC0111_VW, requestor);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransactionsList::doCreateObject (const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ));

   pObjOut = new RESPTransactionsDetails( *this );
   ( ( RESPTransactionsDetails* ) ( pObjOut ) )->init( _accountNum, const_cast<BFData&>(data), _idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPTransactionsList.cpp-arc  $
 * 
 *    Rev 1.11   Aug 06 2010 14:04:34   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.10   May 13 2010 01:32:10   popescu
 * RESP-QESI fixes
 * 
 *    Rev 1.9   Mar 29 2010 23:00:56   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.8   Mar 29 2010 10:56:30   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.7   Nov 14 2004 14:52:26   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.6   Oct 09 2002 23:54:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Aug 29 2002 12:56:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 18:29:44   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   03 May 2001 14:07:02   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Dec 17 2000 20:24:22   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.1   Mar 22 2000 09:02:48   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.2   Feb 16 2000 10:06:48   PETOLESC
// Included the list in MFAccount.
// 
//    Rev 1.1   Feb 07 2000 11:02:30   PETOLESC
// Minor corrections and code cleaning.
 * 
 *
 */