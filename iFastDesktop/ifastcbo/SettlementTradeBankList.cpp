#error "This file is obsolete!"
//use SettlementTradeBankInstructionsList.cpp instead

//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//*****************************************************************************
//
// ^FILE   : SettlementTradeBankList.cpp
// ^AUTHOR : 
// ^DATE   : June 9, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : SettlementTradeBankList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
/*#include "stdafx.h"
#include "bankinstructions.hpp"
#include "bankinstructionslist.hpp"
#include "settlementtradebank.hpp"
#include "settlementtradebanklist.hpp"
#include "settlementtrade.hpp"
#include <dataimpl\dse_dstc0052_vw.hpp>
#include <dataimpl\dse_dstc0200_vw.hpp>

const BFFieldId SettlementTradeBankFields[] = 
{   //Bank Fields
   ifds::FundCode,
   ifds::ClassCode,
   ifds::BankIdType,
   ifds::BankIdValue,
   ifds::TransitNo,
   ifds::InstName,
   ifds::BankPostal,
   ifds::BankCountry,
   ifds::BankContact,
   ifds::BankAddr1,
   ifds::BankAddr2,
   ifds::BankAddr3,
   ifds::BankAddr4,
   ifds::BankAddr5,
   ifds::BankId,
   ifds::BankIdTypeCB,
   ifds::BankIdValueCB,
   ifds::TransitNoCB,
   ifds::InstNameCB,
   ifds::BankPostalCB,
   ifds::BankCountryCB,
   ifds::BankContactCB,
   ifds::BankAddrCB1,
   ifds::BankAddrCB2,
   ifds::BankAddrCB3,
   ifds::BankAddrCB4,
   ifds::BankAddrCB5,
   ifds::CorrespBankId,
   ifds::BankAcctNum,
   ifds::BankAcctType,
   ifds::BankAcctName,
   ifds::AcctUseCode,
   ifds::SwiftCode,
   ifds::RefNumber,
   ifds::SettleCurrency,
   ifds::PayReason1,
   ifds::PayReason2,
   ifds::FFC,
   ifds::FFC1,
   ifds::ACHProcessor,
   ifds::PayMethod,
   ifds::TradeDate,
};
const BFFieldId BankFields[] = 
{   //Bank Fields
   ifds::FundCode,
   ifds::ClassCode,
   ifds::BankIdType,
   ifds::BankIdValue,
   ifds::TransitNo,
   ifds::InstName,
   ifds::BankPostal,
   ifds::BankCountry,
   ifds::BankContact,
   ifds::BankAddr1,
   ifds::BankAddr2,
   ifds::BankAddr3,
   ifds::BankAddr4,
   ifds::BankAddr5,
   ifds::BankId,
   ifds::BankIdTypeCB,
   ifds::BankIdValueCB,
   ifds::TransitNoCB,
   ifds::InstNameCB,
   ifds::BankPostalCB,
   ifds::BankCountryCB,
   ifds::BankContactCB,
   ifds::BankAddrCB1,
   ifds::BankAddrCB2,
   ifds::BankAddrCB3,
   ifds::BankAddrCB4,
   ifds::BankAddrCB5,
   ifds::CorrespBankId,
   ifds::BankAcctNum,
   ifds::BankAcctType,
   ifds::BankAcctName,
   ifds::AcctUseCode,
   ifds::SwiftCode,
   ifds::RefNumber,
   ifds::BankAcctCurrency,
   ifds::PayReason1,
   ifds::PayReason2,
   ifds::FFC,
   ifds::FFC1,
   ifds::ACHProcessor,
   ifds::PayMethod,
   ifds::EffectiveDate,
};

const BFFieldId BankToSettlementFields[] = 
{   //Bank Fields
   ifds::BankIdType,
   ifds::BankIdValue,
   ifds::TransitNo,
   ifds::InstName,
   ifds::BankPostal,
   ifds::BankCountry,
   ifds::BankContact,
   ifds::BankAddr1,
   ifds::BankAddr2,
   ifds::BankAddr3,
   ifds::BankAddr4,
   ifds::BankAddr5,
   ifds::BankId,
   ifds::BankIdTypeCB,
   ifds::BankIdValueCB,
   ifds::TransitNoCB,
   ifds::InstNameCB,
   ifds::BankPostalCB,
   ifds::BankCountryCB,
   ifds::BankContactCB,
   ifds::BankAddrCB1,
   ifds::BankAddrCB2,
   ifds::BankAddrCB3,
   ifds::BankAddrCB4,
   ifds::BankAddrCB5,
   ifds::CorrespBankId,
   ifds::BankAcctNum,
   ifds::BankAcctType,
   ifds::BankAcctName,
//	ifds::AcctUseCode,
   ifds::SwiftCode,
   ifds::RefNumber,
//	ifds::BankAcctCurrency,
   ifds::PayReason1,
   ifds::PayReason2,
   ifds::FFC,
   ifds::FFC1,
//	ifds::ACHProcessor,
//	ifds::PayMethod,
};

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "SettlementTradeBankList" );
   const I_CHAR * const BANK_KEY = I_("SettlementTradeBank");
}

static const int _numSettlementTradeBankFields = sizeof(SettlementTradeBankFields)/sizeof(BFFieldId);
static const int _numBankToSettlementFields = sizeof(BankToSettlementFields)/sizeof(BFFieldId);

//******************************************************************************
SettlementTradeBankList::SettlementTradeBankList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
SettlementTradeBankList::~SettlementTradeBankList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY SettlementTradeBankList::getBankInstructions( const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBankInstr") );

   DString dstrKey;
   getBankKey ( dstrKey, idDataGroup );

   SettlementTradeBank *pSettlementTradeBank = dynamic_cast<SettlementTradeBank *>( BFCBO::getObject( dstrKey, idDataGroup) );

   if( !pSettlementTradeBank )
   {
      DString dstrTransType;
      pSettlementTradeBank = new SettlementTradeBank( *this );      
      getParent()->getField ( ifds::TransType, dstrTransType, idDataGroup );
      pSettlementTradeBank->doInitWithDefaultValues ( BF::HOST );
      pSettlementTradeBank->init ( getParent(), SettlementTradeBankFields, BankFields, _numSettlementTradeBankFields, dstrTransType, idDataGroup );
      setObject( pSettlementTradeBank, dstrKey );
   };
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY SettlementTradeBankList::copyToSettlementTrade(SettlementTrade* pSettlementTrade, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "copyToSettlementTrade" ) );

   DString dstrKey, dstrTemp;
   getBankKey ( dstrKey, idDataGroup );

   SettlementTradeBank *pSettlementTradeBank = dynamic_cast<SettlementTradeBank *>( BFCBO::getObject( dstrKey, idDataGroup) );
   if( pSettlementTradeBank )
   {
      for( int i=0; i<_numBankToSettlementFields; i++ )
      {
         pSettlementTradeBank->getField ( BankToSettlementFields [i], dstrTemp, idDataGroup, false );
         pSettlementTrade->setField ( BankToSettlementFields[i], dstrTemp, idDataGroup, false );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY SettlementTradeBankList::removeBankInstr( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "removeBankInstr" ) );
   DString dstrKey;
   getBankKey ( dstrKey, idDataGroup );
   deleteObject( dstrKey, idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void SettlementTradeBankList::getBankKey( DString& dstrKey, const BFDataGroupId& idDataGroup )
{
   DString dstrTransId;
   BFCBO *pParent = getParent();
   pParent->getField(ifds::TransId, dstrTransId, idDataGroup, false);
   dstrKey = BANK_KEY + dstrTransId;
}*/

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTradeBankList.cpp-arc  $
// 
//    Rev 1.12   Nov 14 2004 14:54:22   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.11   Jun 10 2003 16:11:36   popescu
// Changed the SettlementTrade bank instructions files to match new design for bank instructions that are not on host
// 
//    Rev 1.10   May 22 2003 14:13:10   popescu
// Replaced name 'BankInstr' with 'BankInstructions'; 
// simplified child lists getters for the Shareholder object
// 
//    Rev 1.9   Mar 21 2003 18:24:18   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Oct 09 2002 23:55:00   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.7   Aug 29 2002 12:56:38   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   Jul 22 2002 11:11:10   HSUCHIN
// bug fix for copying data.  doinitwithdefault did not set the correct datagroup.
// 
//    Rev 1.5   Jun 18 2002 16:42:16   HSUCHIN
// setField potential bug fix
// 
//    Rev 1.4   Jun 17 2002 11:43:50   HSUCHIN
// bug fix when it is a new bank
// 
//    Rev 1.3   Jun 16 2002 12:58:34   HSUCHIN
// changed to use SettlementTradeBank
// 
//    Rev 1.2   Jun 15 2002 11:26:56   HSUCHIN
// datagroup bug fix
// 
//    Rev 1.1   Jun 13 2002 17:37:12   HSUCHIN
// more enhancments
// 
//    Rev 1.0   Jun 11 2002 21:33:40   HSUCHIN
// Initial revision.
*/

