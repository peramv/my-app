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
// ^FILE   : ProdPortfolioPlanInfoList.cpp
// ^AUTHOR : 
// ^DATE   : Aug, 2011
//
// ^CLASS    : ProdPortfolioPlanInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0419_vw.hpp>
#include <ifastdataimpl\dse_dstc0419_req.hpp>
#include <ifastdataimpl\dse_dstc0419_vwrepeat_record.hpp>

#include "ProdPortfolioPlanInfo.hpp"
#include "ProdPortfolioPlanInfoList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PROD_PORTFOLIO_PLAN_INFO_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "ProdPortfolioPlanInfoList" );
}

namespace ifds
{
}

namespace CND
{
}

//******************************************************************************
ProdPortfolioPlanInfoList::ProdPortfolioPlanInfoList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
, requestData419(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( 0,
                       NULL,
                       0,
                       NULL );

   setObjectAsList( );
}

//******************************************************************************
ProdPortfolioPlanInfoList::~ProdPortfolioPlanInfoList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if ( requestData419 != NULL )
   {
      delete requestData419;
      requestData419 = NULL;
   }
}

//********************************************************************************
SEVERITY ProdPortfolioPlanInfoList::init(const DString& prodPortFolioUUID,
                                         const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;
   requestData419 = new BFData(ifds::DSTC0419_REQ);

   requestData419->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData419->setElementValue (ifds::ProdPortfolioUUID,prodPortFolioUUID);

   BFData* responseData = new BFData (ifds::DSTC0419_VW);
   ReceiveData( DSTC_REQUEST::PROD_PORTFOLIO_PLAN_INFO_INQUIRY,
                *requestData419, 
                *responseData, 
                DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ProdPortfolioPlanInfoList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new ProdPortfolioPlanInfo( *this );
   ((ProdPortfolioPlanInfo*) pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ProdPortfolioPlanInfoList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::PROD_PORTFOLIO_PLAN_INFO_INQUIRY, 
                  *requestData419, 
                  ifds::DSTC0419_VW, 
                  DSTCRequestor( getSecurity(), false ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ProdPortfolioPlanInfoList::getSubstitutionList(DString& dstrSubstitutionList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSubstitutionList" ) );

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString strTempSubList = I_("");
   while( !iter.end() )
   {
      ProdPortfolioPlanInfo* pObj = dynamic_cast<ProdPortfolioPlanInfo*>(iter.getObject());
      if(pObj)
      {
         DString strPortfolioPlanName, strProdPortfolioPlanUUID;
         pObj->getField(ifds::PortfolioPlanName, strPortfolioPlanName, idDataGroup, false);
         pObj->getField(ifds::ProdPortfolioPlanUUID, strProdPortfolioPlanUUID, idDataGroup, false);
         strTempSubList += strProdPortfolioPlanUUID;
         strTempSubList += I_("=");
         strTempSubList += strPortfolioPlanName;
         strTempSubList += I_(";");
      }
      ++iter; 
   }

   dstrSubstitutionList = strTempSubList;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ProdPortfolioPlanInfoList.cpp-arc  $
// 
//    Rev 1.2   Sep 28 2011 17:11:26   dchatcha
// P0186477 FN01 - GIA Enhancements, Integration test.
// 
//    Rev 1.1   Sep 16 2011 17:59:02   dchatcha
// P0186477 FN01 - GIA Enhancements, Create substitution list
// 
//    Rev 1.0   Aug 25 2011 17:10:10   dchatcha
// Initial revision.
// 
