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
// ^FILE   : DefaultSplitCommList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/05/2001
//
// ^CLASS    : DefaultSplitCommList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "defaultsplitcommlist.hpp"
#include <ifastdataimpl\dse_dstc0158_req.hpp>
#include <ifastdataimpl\dse_dstc0158_vw.hpp>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "DefaultSplitCommList" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DEF_SPLIT_COMMISSION_LIST;
}

//******************************************************************************
DefaultSplitCommList::DefaultSplitCommList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}


//******************************************************************************
DefaultSplitCommList::~DefaultSplitCommList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY DefaultSplitCommList::init( const DString& Account,
                                     const DString& AccountTo,
                                     const DString& Fund,
                                     const DString& FundTo,
                                     const DString& Class,
                                     const DString& ClassTo,
                                     const DString& PUD,
                                     const DString& FlatPrcnt,
                                     const DString& InPayType,
                                     const DString& IAmount,
                                     const DString& InTransType,
                                     const DString& EffectiveDate,
                                     const DString& InGrossNet,
                                     const DString& InBrokerCode,
                                     const DString& InBranchCode,
                                     const DString& InSlsRepCode,
                                     const DString& dstrTrack,
                                     const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData _requestData(ifds::DSTC0158_REQ);

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::Account,   Account  );
   _requestData.setElementValue( ifds::AccountTo,   AccountTo  );
   _requestData.setElementValue( ifds::Fund,      Fund );
   _requestData.setElementValue( ifds::FundTo,    FundTo );
   _requestData.setElementValue( ifds::Class,     Class );
   _requestData.setElementValue( ifds::ClassTo,   ClassTo );
   _requestData.setElementValue( ifds::PUD,     PUD );
   _requestData.setElementValue( ifds::FlatPrcnt,   FlatPrcnt );
   _requestData.setElementValue( ifds::InPayType,   InPayType );
   _requestData.setElementValue( ifds::IAmount,   IAmount );
   _requestData.setElementValue( ifds::InTransType, InTransType );
   _requestData.setElementValue( ifds::EffectiveDate, EffectiveDate, false, false );
   _requestData.setElementValue( ifds::InGrossNet,  InGrossNet );
   _requestData.setElementValue( ifds::InBrokerCode,  InBrokerCode );
   _requestData.setElementValue( ifds::InBranchCode,  InBranchCode );
   _requestData.setElementValue( ifds::InSlsRepCode,  InSlsRepCode );

   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   AsyncReceiveData(DSTC_REQUEST::DEF_SPLIT_COMMISSION_LIST, _requestData, ifds::DSTC0158_VW, DSTCRequestor( getSecurity(), false ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DefaultSplitCommList::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DefaultSplitCommList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut = new DefaultSplitCommList((BFAbstractCBO&)(*this));
   ( ( DefaultSplitCommList* ) ( pObjOut ) )->init( const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultSplitCommList.cpp-arc  $
// 
//    Rev 1.7   Nov 14 2004 14:30:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Mar 21 2003 18:02:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Oct 09 2002 23:54:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:55:16   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   22 May 2002 18:26:46   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   03 May 2001 14:06:08   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.1   Apr 02 2001 15:09:46   OLTEANCR
// fix: setElementValue(DBR::EffectiveDate,..  )
// 
//    Rev 1.0   Mar 06 2001 13:45:42   YINGZ
// Initial revision.
 * 
// 
*/