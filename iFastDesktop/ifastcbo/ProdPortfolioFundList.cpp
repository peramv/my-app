//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : ProdPortfolioFundList.cpp
// ^AUTHOR : 
// ^DATE   : Dec, 2011
//
// ^CLASS    : ProdPortfolioFundList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0098_req.hpp>
#include <ifastdataimpl\dse_dstc0098_vw.hpp>
#include <ifastdataimpl\dse_dstc0098_vwrepeat_record.hpp>

#include "prodportfoliofundlist.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest GROUPFUNDLIST;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "ProdPortfolioFundList" );
}

namespace ifds
{
}

//******************************************************************************
ProdPortfolioFundList::ProdPortfolioFundList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
ProdPortfolioFundList::~ProdPortfolioFundList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************
SEVERITY ProdPortfolioFundList::init( const DString& dstrGroupCode,
                                      const DString& dstrProdPortfolioUUID,
                                      const DString& dstrTrack,
                                      const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init( DString&, BFDataGroupId& )"));

   DString mgmtCoIdOut;
   BFData requestData (ifds::DSTC0098_REQ);

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName);
   requestData.setElementValue (ifds::GroupCode, dstrGroupCode);
   requestData.setElementValue (ifds::ProdPortfolioUUID, dstrProdPortfolioUUID);

   ReceiveData( DSTC_REQUEST::GROUPFUNDLIST,
                requestData, 
                ifds::DSTC0098_VW, 
                DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ProdPortfolioFundList.cpp-arc  $
// 
//    Rev 1.0   Dec 14 2011 18:07:32   dchatcha
// Initial revision.
// 
