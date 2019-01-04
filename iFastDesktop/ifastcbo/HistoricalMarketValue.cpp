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
//    Copyright 2002 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : HistoricalMarketValue.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Feb. 4, 2002
//
// ^CLASS    : HistoricalMarketValue
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "historicalmarketvalue.hpp"
#include "historicalmarketvaluelist.hpp"
#include "FundDetail.hpp"
#include "dstcommonfunction.hpp"
#include <ifastdataimpl\dse_dstc0020_vw.hpp>

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId ACBSettlPrcnt;
   extern CLASS_IMPORT const BFDecimalFieldId MktValSettlPrcnt;
   extern CLASS_IMPORT const BFDecimalFieldId ACBTotalPrcnt;
   extern CLASS_IMPORT const BFDecimalFieldId MktValTotalPrcnt;
}

namespace  
{
   const I_CHAR * const CLASSNAME      = I_( "HistoricalMarketValue" );
   const I_CHAR * const EMPTY_STR      = I_("");
}
//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::ACBSettlPrcnt,    BFCBO::NONE, 0 }, 
   { ifds::MktValSettlPrcnt, BFCBO::NONE, 0 }, 
   { ifds::ACBTotalPrcnt,    BFCBO::NONE, 0 }, 
   { ifds::MktValTotalPrcnt, BFCBO::NONE, 0 }, 
};



static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};




HistoricalMarketValue::HistoricalMarketValue( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{

   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       (const CLASS_OBJECT_INFO *)0 );
}

//---------------------------------------------------------------------
HistoricalMarketValue::~HistoricalMarketValue()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//--------------------------------------------------------------------
SEVERITY HistoricalMarketValue::init( const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );


   attachDataObject(const_cast<BFData&>(InstData), false, true );  

   CalculatePrcnt( ifds::ACBSettl,ifds::TotalACBSettl,ifds::ACBSettlPrcnt);
   CalculatePrcnt( ifds::SettledValueAcctCurr,ifds::AccountBalance,ifds::MktValSettlPrcnt);
   CalculatePrcnt(ifds::ACBTotal,ifds::TotalACBUnSettl,ifds::ACBTotalPrcnt);
   CalculatePrcnt(ifds::CombValueAcctCurr,ifds::TotalValueAcctCurr,ifds::MktValTotalPrcnt);  
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
void HistoricalMarketValue::CalculatePrcnt( const BFFieldId& fieldFZ, const BFFieldId& fieldFM, const BFFieldId& fieldPrcnt)
{
   DString dstrFZ,dstrFM,dstrPrcnt;
   double dFZ,dFM,dPrcnt;

   HistoricalMarketValueList* pList = dynamic_cast<HistoricalMarketValueList*>(getParent( ) );

   getField( fieldFZ,dstrFZ,BF::HOST,true );
   pList->getField( fieldFM,dstrFM,BF::HOST,true );
   dFZ =  DSTCommonFunctions::convertToDouble( dstrFZ );
   dFM =  DSTCommonFunctions::convertToDouble( dstrFM );
   if( dFM <= 0.00001 ) dPrcnt = 0;
   else dPrcnt = dFZ / dFM * 100;
   dstrPrcnt = DSTCommonFunctions::doubleToDString( fieldPrcnt,dPrcnt );
   setFieldNoValidate( fieldPrcnt,dstrPrcnt,BF::HOST);
}

//********************************************************************************
bool HistoricalMarketValue::amountInventoryAppl()
{
    FundDetail *pFundDetail = NULL;
    DString fundCode, classCode;

    getField(ifds::rxFundCode, fundCode, BF::HOST);
    getField(ifds::rxClassCode, classCode, BF::HOST);

    if (getWorkSession().getFundDetail(fundCode, classCode, BF::HOST, pFundDetail) && pFundDetail)
    {
        return pFundDetail->amountInventoryAppl(BF::HOST);
    }

    return false;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HistoricalMarketValue.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:44:08   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Mar 21 2003 18:13:30   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Oct 09 2002 23:54:36   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Aug 29 2002 12:56:02   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.2   22 May 2002 18:28:52   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   Feb 22 2002 14:19:38   YINGBAOL
// fix percent issue
// 

 * 
 */