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
// ^FILE   : HypotheticalRed.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/22/99
//
// ^CLASS    : HypotheticalRed
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "hypotheticalred.hpp"
#include <ifastdataimpl\dse_dstc0137_req.hpp>
#include <ifastdataimpl\dse_dstc0137_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest HYPOTHETICALRED;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_( "HypotheticalRed" );
}

//******************************************************************************
HypotheticalRed::HypotheticalRed( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************
HypotheticalRed::~HypotheticalRed( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY HypotheticalRed::init( DString AccountNum,
                                DString FundCode,
                                DString ClassCode,
                                DString TradeDate,
                                DString GrossOrNet,
                                DString AmountType,
                                DString FullRedem,
                                DString RedCode,
                                DString Amount,
                                DString Baycom,
                                const DString& dstrTrack,
                                const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0137_REQ);

//   D,S,T,P
//   D,U,T,P
   DString FCAmountType = AmountType;
   if ( AmountType == I_("U") ) {
      FCAmountType = I_("S");
   }

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::AccountNum, AccountNum );
   queryData.setElementValue( ifds::FundCode, FundCode );
   queryData.setElementValue( ifds::ClassCode, ClassCode ); 
   queryData.setElementValue( ifds::TradeDate, TradeDate, false, false ); 
   queryData.setElementValue( ifds::GrossOrNet, GrossOrNet ); 
   queryData.setElementValue( ifds::AmountType, AmountType ); 
   queryData.setElementValue( ifds::FullRedem, FullRedem ); 
   queryData.setElementValue( ifds::RedCode, RedCode ); 
   queryData.setElementValue( ifds::Amount, Amount ); 
   queryData.setElementValue( ifds::Baycom, Baycom ); 
   queryData.setElementValue( ifds::FCAmountType, FCAmountType ); 
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );



   ReceiveData( DSTC_REQUEST::HYPOTHETICALRED, queryData, ifds::DSTC0137_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypotheticalRed.cpp-arc  $
// 
//    Rev 1.14   Nov 14 2004 14:44:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.13   22 Jun 2004 15:36:20   SMITHDAV
// Expose hypothetical redemptions as an API interface.
// 
//    Rev 1.12   Mar 21 2003 18:14:38   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.11   Oct 09 2002 23:54:38   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.10   Aug 29 2002 12:56:04   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.9   22 May 2002 18:28:54   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   Feb 25 2002 18:55:46   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.7   03 May 2001 14:06:40   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.6   Apr 02 2001 15:12:30   OLTEANCR
// fix: setElementValue(DBR:TradeDate,..  )
// 
//    Rev 1.5   Jan 18 2001 16:05:14   YINGBAOL
// add eTracker
// 
//    Rev 1.4   Dec 17 2000 20:23:50   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.3   Dec 06 2000 12:04:32   OLTEANCR
// modif. ReceiveData
// 
//    Rev 1.2   Nov 02 2000 10:47:20   OLTEANCR
// new data brokering
// 
//    Rev 1.1   May 10 2000 10:04:02   YINGZ
// just check in
*/
