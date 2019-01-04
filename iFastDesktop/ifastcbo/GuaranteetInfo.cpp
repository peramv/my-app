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
#include "guaranteetinfo.hpp"
#include <dataimpl\dse_dstc0106_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "GuaranteeInfo" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::RecType,          BFCBO::NONE, 0 }, 
   { ifds::TransactionId,    BFCBO::NONE, 0 }, 
   { ifds::TransType,        BFCBO::NONE, 0 }, 
   { ifds::TransTypeDesc,    BFCBO::NONE, 0 }, 
   { ifds::TradeDate,        BFCBO::NONE, 0 }, 
   { ifds::FundCode,         BFCBO::NONE, 0 }, 
   { ifds::ClassCode,        BFCBO::NONE, 0 }, 
   { ifds::AmountInUnit,     BFCBO::NONE, 0 }, 
   { ifds::GuarAmount,       BFCBO::NONE, 0 }, 
   { ifds::MaturityDate,     BFCBO::NONE, 0 }, 
   { ifds::GuarAmtAtMatur,   BFCBO::NONE, 0 }, 
   { ifds::NAVBefRedPeriod,  BFCBO::NONE, 0 }, 
   { ifds::NAVBefRedAcct,    BFCBO::NONE, 0 }, 
   { ifds::RedAmountPeriod,  BFCBO::NONE, 0 }, 
   { ifds::RedAmountAcct,    BFCBO::NONE, 0 }, 
   { ifds::Percentage,       BFCBO::NONE, 0 }, 
   { ifds::NAVAftRedPeriod,  BFCBO::NONE, 0 }, 
   { ifds::NAVAftRedAcct,    BFCBO::NONE, 0 }, 
   { ifds::GuarBefRedPeriod, BFCBO::NONE, 0 }, 
   { ifds::GuarBefRedAcct,   BFCBO::NONE, 0 }, 
   { ifds::GuarRedctnPeriod, BFCBO::NONE, 0 }, 
   { ifds::GuarRedctnAct,    BFCBO::NONE, 0 }, 
   { ifds::GuarAftRedPeriod, BFCBO::NONE, 0 }, 
   { ifds::GuarAftRedAcct,   BFCBO::NONE, 0 }, 
   { ifds::ResetGuarTot,     BFCBO::NONE, 0 }, 
   { ifds::ResetMaturDate,   BFCBO::NONE, 0 }, 
   { ifds::ResetNAV,         BFCBO::NONE, 0 }, 
   { ifds::PrevGuar,         BFCBO::NONE, 0 }, 
   { ifds::ResetGuarAmount,  BFCBO::NONE, 0 }, 
   { ifds::GuarTot,          BFCBO::NONE, 0 }, 
   { ifds::ContractType,     BFCBO::NONE, 0 }, 
   { ifds::PolicyNum,        BFCBO::NONE, 0 }, 
   { ifds::PolicyTerm,       BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
GuaranteeInfo::GuaranteeInfo( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
GuaranteeInfo::~GuaranteeInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY GuaranteeInfo::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GuaranteetInfo.cpp-arc  $
 * 
 *    Rev 1.11   Nov 14 2004 14:43:50   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.10   Oct 09 2002 23:54:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:56:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:28:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   Jul 29 2001 12:57:16   OLTEANCR
 * added PolicyTerm
 * 
 *    Rev 1.6   Jul 16 2001 19:18:24   OLTEANCR
 * added two new fields
 * 
 *    Rev 1.5   11 May 2001 12:54:22   HSUCHIN
 * Session management restructuring
 * 
 *    Rev 1.4   May 11 2001 11:55:14   OLTEANCR
 * unchanged
 * 
 *    Rev 1.3   Jan 10 2001 17:28:58   ZHANGCEL
 * Added the $Log
 * 
 */
