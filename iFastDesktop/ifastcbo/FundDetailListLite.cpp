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
//    Copyright 2004 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundDetailListLite.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FundDetailListLite
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "funddetaillistlite.hpp"
#include <ifastcbo\mgmtco.hpp>
#include "dstcworksession.hpp"


namespace
{
   const I_CHAR * const CLASSNAME             = I_( "FundDetailListLite" );
   const I_CHAR * const CLASS                 = I_( "CLASS") ;
}


//******************************************************************************
FundDetailListLite::FundDetailListLite( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
}


//******************************************************************************
FundDetailListLite::~FundDetailListLite()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
void FundDetailListLite::AssociateObject( const DString& dstrType, const DString& dstrValue )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "AssociateObject" ) );

   FundDetail* pFundDetail = NULL;
   FundDetailList* pFundDetailList = NULL;
   if( getWorkSession().getMgmtCo().getFundDetailList( pFundDetailList ) <= WARNING )
   {
      if( dstrType == I_("FNUM") )
      {
         pFundDetail = pFundDetailList->getFundDetailByFundNumber( dstrValue );
      }
      else if( dstrType == I_("WKN") )
      {
         pFundDetail = pFundDetailList->getFundDetailByWKN( dstrValue );
      }
      else if( dstrType == I_("LFC") )
      {
         pFundDetail = pFundDetailList->getFundDetailByLFC( dstrValue );
      }
      else if( dstrType == I_("ISIN") )
      {
         pFundDetail = pFundDetailList->getFundDetailByISIN( dstrValue );
      }
	  else if( I_("Valoren") == dstrType )
      {
         pFundDetail = pFundDetailList->getFundDetailByVAL( dstrValue );
      }
	  else if( I_("TDCC") == dstrType )
      {
         pFundDetail = pFundDetailList->getFundDetailByTDCC( dstrValue );
      }
	  else if( I_("CUSIP") == dstrType )
      {
         pFundDetail = pFundDetailList->getFundDetailByCUSIP( dstrValue );
      }
      if( pFundDetail )
      {
         setObject( pFundDetail, 
                  dstrValue, 
                  OBJ_ACTIVITY_NONE, 
                  BF::HOST, 
                  OBJ_TYPE_NONE,
                  BFCBO::OBJ_DELETE::NO_DELETE_ON_DTOR );
      }
   }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundDetailListLite.cpp-arc  $
// 
//    Rev 1.0   Dec 03 2004 16:50:40   hernando
// Initial revision.
