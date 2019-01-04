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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : ChequeList.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 16/04/99
//
// ^CLASS    : ChequeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "chequelist.hpp"
#include "chequedetailslist.hpp"
#include "cheque.hpp"
#include "chequedetails.hpp"
#include "currencyclass.hpp"
#include <ifastdataimpl\dse_dstc0021_vw.hpp>
#include <ifastdataimpl\dse_dstc0021_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CHEQUE;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ChequeList" );
   const I_CHAR * const SUMMARY   = I_( "S" );
   const I_CHAR * const DETAIL    = I_( "D" );

}

//******************************************************************************

ChequeList::ChequeList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_requestData(ifds::DSTC0021_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}


//******************************************************************************

ChequeList::~ChequeList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************

SEVERITY ChequeList::init( DString& TransId, 
                           DString& AccountNum, 
                           DString& InCheqNum, 
                           DString& Broker, 
                           DString& Status, 
                           bool bIgnoreDataNotFound,
                           bool bIgnoreUnknAcct, 
                           const DString& dstrTrack,
                           const DString& dstrPageName)                             
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::TransId, TransId ); 
   _requestData.setElementValue( ifds::AccountNum, AccountNum );
   _requestData.setElementValue( ifds::InCheqNum, InCheqNum );
   
   _requestData.setElementValue( ifds::BrokerCode, Broker );
   _requestData.setElementValue( ifds::ChqStatus, Status );

   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   SEVERITY sevRtn = ReceiveData( DSTC_REQUEST::CHEQUE, _requestData, ifds::DSTC0021_VW, DSTCRequestor( getSecurity() ,false ), false );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ChequeList::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ChequeList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut = NULL;
   //view 21 returns summary as well as detail records (it's a mix)
   //filter here: create a Cheque object for each summary record and a ChequeDetail for each detail record
   DString strRecType;
   data.getElementValue( ifds::RecType, strRecType);
   if( strRecType.strip() == SUMMARY )
   {
      pObjOut = new Cheque( *this );
      ( ( Cheque* ) ( pObjOut ) )->init( const_cast<BFData&>(data) );
   }
   else if ( strRecType.strip() == DETAIL )
   {
      DString strPrintDate, strRefNumber;
      data.getElementValue( ifds::PrintDate, strPrintDate);
	  data.getElementValue( ifds::RefNumber, strRefNumber);
      Cheque* pCheque;
	  if( getCheque( pCheque, strRefNumber.strip(), strPrintDate.strip(), BF::HOST ) <= WARNING && pCheque)
	  {
         ChequeDetailsList *pDetailsList;
		 ChequeDetails *pDetails;
		 if( pCheque->getDetailsList( pDetailsList, BF::HOST) <= WARNING && pDetailsList )
		 {            
            pDetails = new ChequeDetails( *this );
            pDetails->init( const_cast<BFData&>(data) );
			pDetailsList->addRecord( pDetails );
         }
	  }
   }
   else
   {
      //invalid RecType?
	  assert(0);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ChequeList::getMore()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

	if( doMoreRecordsExist() )
	{
		const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
		ReceiveData( DSTC_REQUEST::CHEQUE, _requestData, ifds::DSTC0021_VW, DSTCRequestor(getSecurity(), false));
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ChequeList::getCheque( Cheque*& pCheque, const DString& dstrRefNumber, 
							    const DString& dstrPrintDate, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getCheque" ) );

    DString strKey;
    buildKey( strKey, dstrRefNumber, dstrPrintDate ); 
    pCheque = dynamic_cast<Cheque*>(getObject( strKey, idDataGroup ));

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************

void ChequeList::getStrKey( DString &strKey, const BFData *data  )
{
	if ( data )
	{
       DString dstrPrintDate, dstrRefNum;

       dstrPrintDate =  data->getElementValue( I_( "PrintDate" ) );         
       dstrRefNum =  data->getElementValue( I_( "RefNumber" ) );
	
	   buildKey( strKey, dstrRefNum, dstrPrintDate ); 
	}
	else
	{
		assert(0);
	}
}
//******************************************************************************

void ChequeList::buildKey( DString &strKey, const DString &strRefNum, const DString &strPrintDate  )
{
	DString dstrPrintDate(strPrintDate);
	DString dstrRefNum(strRefNum);
    strKey = dstrPrintDate.strip() + I_("_") + dstrRefNum.strip(); 
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ChequeList.cpp-arc  $
 * 
 *    Rev 1.17   08 Jan 2009 14:30:24   kovacsro
 * IN#1521695 - GL #1541 - Users received an internal problem error msg from Desktop
 * 
 *    Rev 1.16   Sep 11 2008 16:33:02   jankovii
 * PET 5517 FN71 Stale Cheque.
 * 
 *    Rev 1.15   Sep 08 2008 16:03:50   jankovii
 * PET 5517 FN71 - Stale Cheque.
 * 
 *    Rev 1.14   Nov 14 2004 14:29:34   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.13   Mar 21 2003 18:01:34   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:54:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Sep 25 2002 14:49:00   HERNANDO
 * Bug fix - Display details list; clean-up, minor fixes.
 * 
 *    Rev 1.10   Aug 29 2002 12:55:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:26:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   03 May 2001 14:06:04   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.7   Jan 18 2001 16:04:12   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.6   Dec 17 2000 20:22:46   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.5   Dec 06 2000 10:47:08   OLTEANCR
 * changed ReceiveData
 * 
 *    Rev 1.4   Nov 02 2000 13:22:50   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.3   Sep 01 2000 15:25:38   HUANGSHA
 * added pClientLocale in setField(...)
 * 
 *    Rev 1.2   Jun 09 2000 11:47:30   BUZILA
 * cheque fix
 * 
 *    Rev 1.1   May 04 2000 16:56:16   WINNIE
 * change CURRENCY_HPP to CURRENCYCLASS_HPP
 * 
 *    Rev 1.0   Feb 15 2000 10:59:50   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.15   Jan 05 2000 20:10:40   BUZILA
 * adding list flag
 * 
 *    Rev 1.14   Dec 12 1999 16:25:14   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/