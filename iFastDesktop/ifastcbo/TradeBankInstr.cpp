//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : TradeBankInstr.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 06/14/02
//
// ^CLASS    : TradeBankInstr
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "trade.hpp"
#include "tradeacctalloclist.hpp"
#include "tradebankinstr.hpp"
#include "tradebanklist.hpp"

#include <dataimpl\dse_dstc0052_vw.hpp>
#include <dataimpl\dse_dstc0055_vw.hpp>


namespace CND
{  // Conditions used

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId PayMethod;
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FromFund;
   extern CLASS_IMPORT const BFTextFieldId FromClass;
   extern CLASS_IMPORT const BFTextFieldId TradesTransType;
   extern CLASS_IMPORT const BFTextFieldId InternationalWire;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId DefaultBankType;
   extern CLASS_IMPORT const BFTextFieldId DefaultBankUpd;
   extern CLASS_IMPORT const BFTextFieldId BankInstrType;
   extern CLASS_IMPORT const BFTextFieldId BankInsType;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId BankAcctType;   
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const PENDING_TRADE;
   extern CLASS_IMPORT I_CHAR * const TRADE;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
	extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME            = I_( "TradeBankInstr" );
   const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const NO                   = I_( "N" );
   const I_CHAR * const WIRE                 = I_( "WIRE" );
   //const I_CHAR * const ORDINARYDEPOSIT      = I_( "1" );  // Default bank account type
   I_CHAR *  DIRECT_TRADING				= I_( "31" );
}
//******************************************************************************
const BFFieldId DirectTradingReadOnlyFields[]=
{
   ifds::TransitNo,
   ifds::BankAcctNum,
   ifds::BankAcctName,
   ifds::BankIdValue,
   ifds::BankIdType,    
   ifds::BankCountry,
   ifds::BankAcctType   
};
static const int numDTReadOnlyFields = sizeof( DirectTradingReadOnlyFields ) / sizeof( BFFieldId );

//******************************************************************************
const BFFieldId readOnlyFields[]=
{
   ifds::AcctUseCode,
   ifds::EffectiveDate,
   ifds::StopDate,
   ifds::BankAcctCurrency,
   ifds::PayMethod,
   ifds::ACHProcessor
};
static const int numReadOnlyFields = sizeof( readOnlyFields ) / sizeof( BFFieldId );

const BFFieldId tradeFields[]=
{
   ifds::EffectiveDate,
   ifds::PayMethod,
   ifds::ACHProcessor,
   ifds::FromFund,
   ifds::FromClass,
};
static const int numTradeFields = sizeof( tradeFields ) / sizeof( BFFieldId );

extern const BFFieldId fieldsInBeneficialBank[];
extern const BFFieldId fieldsInCorresBank[];

//******************************************************************************


TradeBankInstr::TradeBankInstr( BFAbstractCBO &parent ):
BankInstructions(parent),
m_pTrade(NULL),
m_pInitData(NULL),
m_dstrAcctUseCode(NULL_STRING),
m_dstSettleCurrency(NULL_STRING),
m_dstrAccountNum(NULL_STRING),
m_bNoModelBank(true)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************
TradeBankInstr::~TradeBankInstr()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//******************************************************************************
void TradeBankInstr::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   setAcctUseSubstList(idDataGroup);
   //*these fields will be overwritten by initFieldsFromData() if there is a Data object
   //and the values are not NULL_STRING
   //setFieldNoValidate( ifds::BankAcctType, ORDINARYDEPOSIT, idDataGroup, false );//??
   setFieldNoValidate( ifds::AcctUseCode, m_dstrAcctUseCode, idDataGroup, false );
   setFieldNoValidate( ifds::BankAcctCurrency, m_dstSettleCurrency, idDataGroup, false );
   setStopDate9999( idDataGroup );
   //*

   setFieldNoValidate(ifds::BankInstrType, BANKTYPE::TRADE, idDataGroup, false);
   setFieldNoValidate(ifds::BankInsType, BANKTYPE::TRADE, idDataGroup, false);

   initFieldsFromData(idDataGroup);
   setDefaultBankIdType(idDataGroup, m_bNoModelBank);
   setFieldsFromTrade(idDataGroup);
   getParent()->setField(ifds::AccountNum, m_dstrAccountNum, idDataGroup, false);

   setBankAccountName ( idDataGroup );

   processCorrBankInfo(idDataGroup);
   setDefaultBankIdType(idDataGroup, false);
   setBankAcctTypeRequired ( idDataGroup );
   setACHProcessorRequired( idDataGroup );
   setFieldsReadOnly( readOnlyFields, numReadOnlyFields, idDataGroup);
   //Direct trading should not invock this function.
   /*if( dstrAcctUseCode == DIRECT_TRADING )
   {
	   setFieldsReadOnly(DirectTradingReadOnlyFields, numDTReadOnlyFields, idDataGroup);
   }*/
   getBankInfo(fieldsInBeneficialBank, idDataGroup);
   fileProcessorRelatedChanges(idDataGroup);
   clearUpdatedFlags( idDataGroup );

}

//**************************************************************************************
//Initialization for bankInstr CBO for an existing pending EFT trade or International Wire Trade
void TradeBankInstr::initPendingTradeBank( const BFData& data, const Trade* pTrade, 
                                           const DString& dstrAcctUseCode, const DString& dstSettleCurrency, const BFDataGroupId& idDataGroup )
{
   m_pTrade = pTrade;
   attachDataObject(const_cast<BFData&>(data), false, true );

   setFieldNoValidate(ifds::BankInstrType, BANKTYPE::PENDING_TRADE, idDataGroup, false);
   setFieldNoValidate(ifds::BankInsType, BANKTYPE::PENDING_TRADE, idDataGroup, false);
   commonInit(dstrAcctUseCode, dstSettleCurrency, idDataGroup); 
}
//**************************************************************************************

void TradeBankInstr::commonInit(const DString& dstrAcctUseCode, const DString& dstSettleCurrency, const BFDataGroupId& idDataGroup )
{
   setAcctUseSubstList(idDataGroup);
   setFieldsFromTrade(idDataGroup);
   setFieldNoValidate( ifds::AcctUseCode, dstrAcctUseCode, idDataGroup, false );

   DString transitNo, 
      transitNoCB;

   getField (ifds::TransitNo, transitNo, idDataGroup, false);
   getField (ifds::TransitNoCB, transitNoCB, idDataGroup, false);

   if (transitNo == I_("0"))
   {
      setFieldNoValidate (ifds::TransitNo, NULL_STRING, 
         idDataGroup, false, true, true);
   }

   if (transitNoCB == I_("0"))
   {
      setFieldNoValidate (ifds::TransitNoCB, NULL_STRING, 
         idDataGroup, false, true, true);
   }

   m_dstrAcctUseCode = dstrAcctUseCode;
   DString strSettleCurr(dstSettleCurrency);
   if( !strSettleCurr.strip().empty() )
      setFieldNoValidate(ifds::BankAcctCurrency, dstSettleCurrency, idDataGroup);
   else
   {
      m_pTrade->getField ( ifds::SettleCurrency, strSettleCurr, idDataGroup, false);
      if( !strSettleCurr.strip().empty() )  // trade level settle currency
         setFieldNoValidate( ifds::BankAcctCurrency, strSettleCurr, idDataGroup, false );
   }
   m_dstSettleCurrency = strSettleCurr;
   getParent()->setField(ifds::AccountNum, m_dstrAccountNum, idDataGroup, false);

   setBankAccountName( idDataGroup );

   DString dstrBankIdValue;
   getField( ifds::BankIdValue, dstrBankIdValue, idDataGroup );
   if( dstrBankIdValue.strip() != NULL_STRING || dstrAcctUseCode == DIRECT_TRADING )
      setBenBankInfoReadOnly(idDataGroup);
   getField( ifds::BankIdValueCB, dstrBankIdValue, idDataGroup );
   if( dstrBankIdValue.strip() != NULL_STRING || dstrAcctUseCode == DIRECT_TRADING )
      setCorrBankInfoReadOnly(idDataGroup);

   setDefaultBankIdType(idDataGroup, false);
   setStopDate9999( idDataGroup );
   setBankAcctTypeRequired ( idDataGroup );
   setACHProcessorRequired( idDataGroup );
   setFieldsReadOnly(readOnlyFields, numReadOnlyFields, idDataGroup);
   if( dstrAcctUseCode == DIRECT_TRADING )
   {
	   setFieldsReadOnly(DirectTradingReadOnlyFields, numDTReadOnlyFields, idDataGroup);
   }
   //pay method related changes
   fileProcessorRelatedChanges(idDataGroup);
   if (m_pTrade)
   {
      DString fileProc;
      m_pTrade->getField (ifds::ACHProcessor, fileProc, idDataGroup, false);
      setFieldNoValidate (ifds::ACHProcessor, fileProc, idDataGroup, false, 
         false, true, true);
      setFieldReadOnly (ifds::ACHProcessor, idDataGroup, true);
   }
   processCorrBankInfo(idDataGroup);
   clearUpdatedFlags( idDataGroup );
}

//**************************************************************************************
//Initialization for bankInstr CBO for a new EFT trade or International Wire Trade
void TradeBankInstr::initNewTradeBank( const BFData& data, const bool noModelBank, 
                                       DString& dstAcctNum, const Trade* pTrade, const DString& dstrAcctUseCode, const BFDataGroupId& idDataGroup )
{
   m_pTrade = pTrade;
   m_pInitData = const_cast<BFData*>(&data);
   m_dstrAccountNum = dstAcctNum;
   m_bNoModelBank = noModelBank;

   initFieldsFromData(idDataGroup);
   setObjectNew();

   setFieldNoValidate(ifds::BankInstrType, BANKTYPE::TRADE, idDataGroup, false);
   setFieldNoValidate(ifds::BankInsType, BANKTYPE::TRADE, idDataGroup, false);
   commonInit(dstrAcctUseCode, NULL_STRING, idDataGroup); 

   //setFieldsSubsValuesForTrade(idDataGroup );
   setDefaultBankIdType(idDataGroup, m_bNoModelBank);

   clearUpdatedFlags( idDataGroup );
}
//**************************************************************************************
void TradeBankInstr::initLastEFT( const BFData& data, bool bBaseDelete )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject(const_cast<BFData&>(data), bBaseDelete, true );
   setAllFieldsValid(BF::HOST);      

}
//**************************************************************************************

SEVERITY TradeBankInstr::setFieldsFromTrade(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFieldsFromTrade" ) );

   DString dstr, dstTradesTransType;
   if( !m_pTrade )
      return(GETCURRENTHIGHESTSEVERITY());

   for( int i=0; i<numTradeFields; i++ )
   {
      m_pTrade->getField ( tradeFields[i], dstr, idDataGroup, false);
      if( i==3 )
         setFieldNoValidate( ifds::FundCode, dstr, idDataGroup, false, true, true, false );
      else if( i==4 )
         setFieldNoValidate( ifds::ClassCode, dstr, idDataGroup, false, true, true, false );
      else
         setFieldNoValidate( tradeFields[i], dstr, idDataGroup, false, false, true, false );
   }

   m_pTrade->getField ( ifds::TradesTransType, dstTradesTransType, idDataGroup, false);
   setFieldNoValidate( ifds::TransType, dstTradesTransType, idDataGroup, false );

   if( m_bNoModelBank )//get the fields from trade
   {
      for( int i=0; i<numFieldsInBeneficialBank; i++ )
      {
         m_pTrade->getField ( fieldsInBeneficialBank[i], dstr, idDataGroup, false);
         if( !dstr.strip().empty() && dstr!=I_("0") )//we should use BFDataField::isDefault(), but it seems it doesn't work so well
            setFieldNoValidate( fieldsInBeneficialBank[i], dstr, idDataGroup, false, false, true, false );
      }
      for( i=0; i<numFieldsInCorresBank; i++ )
      {
         m_pTrade->getField ( fieldsInCorresBank[i], dstr, idDataGroup, false);
         if( !dstr.strip().empty() && dstr!=I_("0") )//we should use BFDataField::isDefault(), but it seems it doesn't work so well
            setFieldNoValidate( fieldsInCorresBank[i], dstr, idDataGroup, false, false, true, false );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeBankInstr::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "TradeBankInstr::doApplyRelatedChanges" ) )
   if( BankInstructions::doApplyRelatedChanges(idField, idDataGroup) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY TradeBankInstr::doValidateField( const BFFieldId& idField,
                                          const DString& strValue,
                                          const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "TradeBankInstr::doValidateField" ) );
   if( BankInstructions::doValidateField(idField, strValue, idDataGroup) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}

/******************************************************************************
void TradeBankInstr::setFieldsSubsValuesForTrade( const BFDataGroupId& idDataGroup )
{
   const I_CHAR * const ACCTUSECODESUBLIST  = I_( "1EFTTrade=EFTTrade;2Default=Default;3LastUsedEFT=LastUsedEFT;4Custom=Custom;Trade=Trade;LastTrade=LastTrade;" ); 

//   setFieldAllSubstituteValues( DBR::AcctUseCode,  idDataGroup, ACCTUSECODESUBLIST );
}*/


//******************************************************************************

bool TradeBankInstr::doIsInternationalWire( const DString& strSettleCurr,  const DString& strCountry, const BFDataGroupId& idDataGroup)
{
   assert(0);//~IntWireStuff~
   return(true);//~IntWireStuff~

   bool bIntWire = false;
   TradeAcctAllocList *pTradeAcctAllocList = NULL;
   if( m_pTrade )
   {
      DString strType, strPayMethod;
      m_pTrade->getField(ifds::TradesTransType, strType, idDataGroup, false);
      getField(ifds::PayMethod, strPayMethod, idDataGroup, false);
      if( (strType.strip() == TRADETYPE::REDEMPTION ||
			  strType.strip() == TRADETYPE::ADMIN_FEE  )&& strPayMethod == WIRE )
         const_cast<Trade*>(m_pTrade)->getAccountAllocationList(pTradeAcctAllocList, idDataGroup, false);//don't create
   }
   if( pTradeAcctAllocList )
      pTradeAcctAllocList->hasInternationalWireAlloc(strSettleCurr, strCountry, bIntWire, idDataGroup);

   return(bIntWire);
}

//******************************************************************************
void TradeBankInstr::setACHProcessorRequired( const BFDataGroupId& idDataGroup )
{
   setFieldRequired(ifds::ACHProcessor , idDataGroup, false );
}
//******************************************************************************

void TradeBankInstr::initFieldsFromData( const BFDataGroupId& idDataGroup )
{
   if( !m_pInitData )
      return;

   BFDataFieldIter dIter( *m_pInitData );
   DString str;
   for( ;dIter; ++dIter )
   {
      BFDataField& idField = dIter();
      m_pInitData->getElementValue(idField.getId(), str);
      if( !str.strip().empty() && str!=I_("0") )//we should use BFDataField::isDefault(), but it seems it doesn't work so well
         setFieldNoValidate( idField.getId(), str, idDataGroup, false, false, true, false);
   };
}

//******************************************************************************


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeBankInstr.cpp-arc  $
// 
//    Rev 1.26   Sep 09 2004 09:56:40   ZHANGCEL
// PET1094_FN8 -- AdminFee related changes
// 
//    Rev 1.25   Feb 17 2004 14:07:40   popescu
// PTS 10027188 set the transit number CB to empty string when modifying a bank in pending trade update mode, if the value of it is '0'; otherwise the validation doesn't pass
// 
//    Rev 1.24   Feb 13 2004 18:04:14   popescu
// PTS 10027188, copy the value of the file processor field into trading screen, and trade banking screen, when modifying a pending trade; removed the substitution list of the BankInstrType, since the combo is being loaded anyhow in the dialog. This field is not  updatable. Assign the correct transaction type to the bankinstructions4trxn object and set all the fields to read only in postInit
// 
//    Rev 1.23   Jan 30 2004 15:04:48   popescu
// PTS 10026408, 
// Removed hard coding of the file processor for banking, for broker/branch/slsrep, systematic,distribution,trade,shareholder.
// Set the value of the file processor to NULL_STRING if there are no values from the back-end, 
// For banking and distributions set the file processor NOT required if there are no values at the back-end
// 
//    Rev 1.22   Oct 29 2003 17:41:42   FENGYONG
// direct trading banking can not be modified from trading level
// 
//    Rev 1.21   Oct 28 2003 10:43:20   FENGYONG
// if direct trading banking, all field will be read only in the trading banking screen
// 
//    Rev 1.20   Aug 11 2003 10:53:26   popescu
// fixed issue with setting the default bank account name
// 
//    Rev 1.19   Aug 05 2003 15:50:40   popescu
// put a quick and dirty fix in to solve an issue with setting the subst list for the AcctUsage. Things with tradeBank needs to be revisited, and adapted to the new design
// 
//    Rev 1.18   Jun 18 2003 17:45:16   popescu
// RRIF Banking Enhancement , business rules, bug fixes 
// 
//    Rev 1.17   May 31 2003 11:55:34   popescu
// RRIF bank work
// 
//    Rev 1.16   May 23 2003 10:04:26   popescu
// Part of bank instructions cleaning up process, moved the bank types into the ifastids project
// 
//    Rev 1.15   May 22 2003 14:13:36   popescu
// Replaced name 'BankInstr' with 'BankInstructions'; 
// simplified child lists getters for the Shareholder object
// 
//    Rev 1.14   Mar 21 2003 18:26:54   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.13   Oct 09 2002 23:55:10   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.12   Sep 09 2002 12:17:18   KOVACSRO
// Sync-up PTS 10009768 : removed corr bank edit check and some fixes
// 
//    Rev 1.11   Aug 29 2002 12:56:54   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.10   Jul 05 2002 16:34:06   KOVACSRO
// commented out processCorrBankInfo since it will be called by payMethodRelatedChanges.
// 
//    Rev 1.9   Jul 05 2002 11:59:34   KOVACSRO
// Dynamically loading AcctUse subst. list.
// 
//    Rev 1.8   Jun 28 2002 13:46:20   KOVACSRO
// Force loading ACHProcessor substitution list.
// 
//    Rev 1.7   Jun 28 2002 11:52:48   KOVACSRO
// Don't trigger applyRelatedChanges when copying data from backend or from trade.
// 
//    Rev 1.6   Jun 21 2002 17:44:46   KOVACSRO
// adde initLastEFT and some bug fixes
// 
//    Rev 1.5   Jun 20 2002 13:33:50   KOVACSRO
// International wire fixes.
// 
//    Rev 1.4   Jun 17 2002 17:28:50   KOVACSRO
// fixed reset
// 
//    Rev 1.3   Jun 16 2002 17:04:42   KOVACSRO
// using the new methods from bankInstr.cpp
// 
//    Rev 1.2   Jun 15 2002 16:40:16   KOVACSRO
// new object  versus existing object.
// 
//    Rev 1.1   Jun 14 2002 17:37:02   KOVACSRO
// some fixes.
// 
//    Rev 1.0   Jun 14 2002 16:45:46   KOVACSRO
// Initial revision.
// 

 * 
*/
