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
// ^FILE   : GuaranteeInfo.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 09/03/2000
//
// ^CLASS    : GuaranteeInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "matchtransferdetails.hpp"
#include "splitcommissionlist.hpp"
#include <ifastdataimpl\dse_dstc0022_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "MatchTransferDetails" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::TfrFund,         BFCBO::NONE, 0 }, 
   { ifds::TfrClass,        BFCBO::NONE, 0 }, 
   { ifds::TransNum,        BFCBO::NONE, 0 }, 
   { ifds::PrevUnitBal,     BFCBO::NONE, 0 }, 
   { ifds::SettleDate,      BFCBO::NONE, 0 }, 
   { ifds::NetAmt,          BFCBO::NONE, 0 }, 
   { ifds::BrokerName,      BFCBO::NONE, 0 }, 
   { ifds::BranchName,      BFCBO::NONE, 0 }, 
   { ifds::SlsrepName,      BFCBO::NONE, 0 }, 
   { ifds::rxFundCode,      BFCBO::NONE, 0 }, 
   { ifds::rxClassCode,     BFCBO::NONE, 0 }, 
   { ifds::TradeDate,       BFCBO::NONE, 0 }, 
   { ifds::TransType,       BFCBO::NONE, 0 }, 
   { ifds::UnitPrice,       BFCBO::NONE, 0 }, 
   { ifds::Accountable,     BFCBO::NONE, 0 }, 
   { ifds::BackDatedReason, BFCBO::NONE, 0 }, 
   { ifds::Commission,      BFCBO::NONE, 0 }, 
   { ifds::SplitComm,       BFCBO::NONE, 0 }, 
   { ifds::TfrAcct,         BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
MatchTransferDetails::MatchTransferDetails( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
MatchTransferDetails::~MatchTransferDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY MatchTransferDetails::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void MatchTransferDetails::getField( const BFFieldId& idField, DString& strFieldValue, 
                                     const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );

   if( (  idField == ifds::GrossAmt    ||
          idField == ifds::NetAmt      ||
          idField == ifds::Commission  ||
          idField == ifds::HoldBackAmt ||
          idField == ifds::OverrideAmt ||
          idField == ifds::DeductAmt   ||
          idField == ifds::SetGrossAmt ||
          idField == ifds::SetNetAmt)  && 
       formattedReturn )
   {
      DString currency;
      getCurrency( idDataGroup, currency);

      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( currency, strFieldValue, strFieldValue );
   }
}

//******************************************************************************
void MatchTransferDetails::getCurrency(const BFDataGroupId& idDataGroup, DString &currency) const
{
   DString fundCode, classCode;
   getField( ifds::rxFundCode, fundCode, idDataGroup, true );
   fundCode.stripAll().upperCase();
   if( fundCode == I_( "Cash" ) )
      BFCBO::getField( ifds::SettleCurrency, currency, idDataGroup, false );
   else
   {
      getField( ifds::rxClassCode, classCode, idDataGroup, true );
      CurrencyClass::getFundCurrency( getWorkSession(), fundCode, classCode, currency );
   }
   currency.strip();
}

//******************************************************************************

SEVERITY MatchTransferDetails::getSplitCommissionList(SplitCommissionList *&rpSplitCommissionList,
                                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSplitCommissionList" ) );

   rpSplitCommissionList = dynamic_cast< SplitCommissionList * >( BFCBO::getObject( I_( "SplitCommissionList" ), idDataGroup ) );
   if( !rpSplitCommissionList )
   {
      DString dstrTransNum, dstrTransSeq, dstrAccountNum, dstrTransType,
         dstrFundCode, dstrClassCode, dstrBrokerCode, 
         dstrBranchCode, dstrSlsRepCode, dstrEffectiveDate;
      getField(ifds::TransNum, dstrTransNum, idDataGroup, true);
      getField(ifds::TransSeq, dstrTransSeq, idDataGroup, true);
      getField(ifds::TfrAcct, dstrAccountNum, idDataGroup, true);
      getField(ifds::TransType, dstrTransType, idDataGroup, true);
      getField(ifds::rxFundCode, dstrFundCode, idDataGroup, true) ;
      getField(ifds::rxClassCode, dstrClassCode, idDataGroup, true);
      getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, true);
      getField(ifds::BranchCode, dstrBranchCode, idDataGroup, true);
      getField(ifds::SalesRepCode, dstrSlsRepCode, idDataGroup, true);
      getField(ifds::SalesRepCode, dstrSlsRepCode, idDataGroup, true);
      getField(ifds::TradeDate, dstrEffectiveDate, idDataGroup, true);
      rpSplitCommissionList = new SplitCommissionList( *this );
      rpSplitCommissionList->init (dstrTransNum, dstrTransSeq, dstrTransType, dstrAccountNum, dstrFundCode,
         dstrClassCode, dstrBrokerCode, dstrBranchCode, dstrSlsRepCode, dstrEffectiveDate,NULL_STRING);
      if( rpSplitCommissionList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( rpSplitCommissionList, I_( "SplitCommissionList" ), OBJ_ACTIVITY_NONE, BF::HOST ); 
         }
         else
         {
            delete rpSplitCommissionList;
            rpSplitCommissionList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatchTransferDetails.cpp-arc  $
// 
//    Rev 1.8   Mar 30 2005 14:37:34   popescu
// Incident# 275373, added an extra parameter to view 151 (TransId), split commission trans history/pending trades inquiry
// 
//    Rev 1.7   Nov 14 2004 14:49:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Apr 29 2003 17:13:10   popescu
// PTS 10016204
// 
//    Rev 1.5   Apr 14 2003 16:27:30   popescu
// PTS 10011081- split commision amount is being calculated by the view side
// 
//    Rev 1.4   Mar 21 2003 18:18:08   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Oct 09 2002 23:54:44   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Aug 29 2002 12:56:08   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.1   22 May 2002 18:28:58   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   Aug 16 2001 13:42:30   ZHANGCEL
// Initial revision.
 *
 */
