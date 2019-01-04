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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DuplicateTradeCheck.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : July, 2001
//
// ^CLASS    : DuplicateTradeCheck
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "duplicatetradecheck.hpp"
#include <ifastdataimpl\dse_dstc0156_req.hpp>
#include <ifastdataimpl\dse_dstc0156_vw.hpp>

namespace CORFAX
{
   extern CLASS_IMPORT const DSTCHost HOST;
   const char *const CFX_TRANS      = "CFXTRAN";
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DUPLICATE_TRADE_CHECK;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "DuplicateTradeCheck" );
   const I_CHAR * const YES = I_("Y");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,     Group Flags 
   { ifds::DuplicateTrade, BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );



//******************************************************************************
DuplicateTradeCheck::DuplicateTradeCheck( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
DuplicateTradeCheck::~DuplicateTradeCheck()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}



//******************************************************************************
SEVERITY DuplicateTradeCheck::init( const DString&  strAccountNum, 
                                    const DString&  strFundCode, const DString&  strClassCode, const DString&  strTransType,
                                    const DString&  strAmountType, const DString&  strAmount, 
									const DString&  strEffectiveDate, 
									const DString&  strIndc, const DString& strSettleCurrency,
									const DString& strSettleDate, const DString& strToFundCode, 
									const DString& strToClassCode, const DString& strToAccount,
									const DString&  strRecId/* = NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   m_AccountNum=strAccountNum;
   m_FundCode=strFundCode;
   m_ClassCode=strClassCode;
   m_TransType=strTransType;
   m_Amount=strAmount;
   m_AmountType=strAmountType;
   m_EffectiveDate=strEffectiveDate;
   m_RecId=strRecId;
   m_Indc=strIndc;
   m_SettleCurrency=strSettleCurrency;
   m_SettleDate=strSettleDate;
   m_ToFundCode=strToFundCode;
   m_ToClassCode=strToClassCode;
   m_ToAccount=strToAccount;

   BFData queryData(ifds::DSTC0156_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::AccountNum, strAccountNum );
   queryData.setElementValue( ifds::FundCode, strFundCode );
   queryData.setElementValue( ifds::ClassCode, strClassCode );
   queryData.setElementValue( ifds::TransType, strTransType );
   queryData.setElementValue( ifds::Amount, strAmount );
   queryData.setElementValue( ifds::PUD, strAmountType );
   queryData.setElementValue( ifds::EffectiveDate, strEffectiveDate, false, false );
   queryData.setElementValue( ifds::InterDetlRid, strRecId );
   queryData.setElementValue( ifds::Indc, strIndc );
   queryData.setElementValue( ifds::SettleCurrency, strSettleCurrency );
   queryData.setElementValue( ifds::SettleDate, strSettleDate, false, false );
   queryData.setElementValue( ifds::FundTo, strToFundCode );
   queryData.setElementValue( ifds::ClassTo, strToClassCode );
   queryData.setElementValue( ifds::AccountTo, strToAccount );

   ReceiveData( DSTC_REQUEST::DUPLICATE_TRADE_CHECK, queryData, ifds::DSTC0156_VW,DSTCRequestor(getSecurity(), true, true) );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool DuplicateTradeCheck::isChanged(const DString&  strAccountNum, const DString&  strFundCode, 
                                    const DString&  strClassCode, const DString&  strTransType,
                                    const DString&  strAmountType , const DString&  strAmount, 
                                    const DString&  strEffectiveDate, const DString&  strRecId/* = NULL_STRING*/ )
{
   if( m_AccountNum!=strAccountNum )
      return(true);
   if( m_FundCode!=strFundCode )
      return(true);
   if( m_ClassCode!=strClassCode )
      return(true);
   if( m_TransType!=strTransType )
      return(true);
   if( m_Amount!=strAmount )
      return(true);
   if( m_AmountType!=strAmountType )
      return(true);
   if( m_EffectiveDate!=strEffectiveDate )
      return(true);
   if( m_RecId!=strRecId )
      return(true);
   return(false);
}
//******************************************************************************

bool DuplicateTradeCheck::isDuplicate()
{
   TRACE_METHOD( CLASSNAME, I_("isDuplicate") );

   DString strDuplicate;
   getField(ifds::DuplicateTrade, strDuplicate, BF::HOST, false);
   return(strDuplicate.strip() == YES);
}

//******************************************************************************

SEVERITY DuplicateTradeCheck::refresh(const DString&  strAccountNum, 
                                      const DString&  strFundCode, const DString&  strClassCode, const DString&  strTransType,
                                      const DString&  AmountType, const DString&  Amount, 
									  const DString&  strEffectiveDate, 
									  const DString&  strIndc, const DString& strSettleCurrency,
									  const DString& strSettleDate, const DString& strToFundCode, 
									  const DString& strToClassCode, const DString& strToAccount,
									  const DString&  strRecId/* = NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "refresh" ) );
   BFCBO::refresh(true);
   init( strAccountNum, strFundCode, strClassCode, strTransType, 
         AmountType, Amount, strEffectiveDate,strIndc,strSettleCurrency, 
		 strSettleDate,strToFundCode, strToClassCode, strToAccount, strRecId);
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DuplicateTradeCheck.cpp-arc  $*/
// 
//    Rev 1.8   Nov 14 2004 14:36:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.7   Mar 21 2003 18:07:38   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Oct 09 2002 23:54:24   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Aug 29 2002 12:55:42   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   Jul 08 2002 10:16:18   KOVACSRO
// Bug fixed for InterDetlRid.
// 
//    Rev 1.3   22 May 2002 18:28:28   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   13 Jul 2001 14:46:42   YINGZ
// add company id for view
// 
//    Rev 1.1   10 Jul 2001 15:51:48   KOVACSRO
// Session management changes.
// 
//    Rev 1.0   09 Jul 2001 10:54:02   KOVACSRO
// Initial revision.
