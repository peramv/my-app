//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//*****************************************************************************
//
//    ^FILE   : TradeBankInstructions.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : October 2004
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : TradeBankInstructions
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "tradebankinstructions.hpp"

#include "trade.hpp"

namespace 
{
   const I_CHAR * CLASSNAME = I_( "TradeBankInstructions" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId DirectDepositBankApplicable;
}

namespace CND
{  // Conditions used
}


namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const TRADE;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
   extern CLASS_IMPORT I_CHAR * const AUTO_WITHDRAW;
   extern CLASS_IMPORT I_CHAR * const FULL_EAP_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const MANUAL_MGMT_FEE_REBATE;
} 

namespace AcctUseCode
{
   extern const I_CHAR * const EFT_REDEMPTION;
   extern const I_CHAR * const EFT_PURCHASE;
   extern const I_CHAR * const COMM_CLEAR;
   extern const I_CHAR * const DIRECT_DEPOSIT;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const DIRECT_DEPOSIT;
   extern CLASS_IMPORT I_CHAR * const EFT;
}

const BANKFIELDMAPPINGINFO trade_bankFieldMappingInfo[] = {
      //Trade,                //bank instructions,   //is a bank field?
      {ifds::BankIdType,       ifds::BankIdType,       true},
      {ifds::BankIdValue,      ifds::BankIdValue,      true},
      {ifds::BankId,           ifds::BankId,           true},
      {ifds::InstName,         ifds::InstName,         true},
      {ifds::TransitNo,        ifds::TransitNo,        true},
      {ifds::BankAddr1,        ifds::BankAddr1,        true},
      {ifds::BankAddr2,        ifds::BankAddr2,        true},
      {ifds::BankAddr3,        ifds::BankAddr3,        true},
      {ifds::BankAddr4,        ifds::BankAddr4,        true},
      {ifds::BankAddr5,        ifds::BankAddr5,        true},
      {ifds::BankContact,      ifds::BankContact,      true},
      {ifds::BankCountry,      ifds::BankCountry,      true},
      {ifds::BankPostal,       ifds::BankPostal,       true},
      {ifds::BankAcctNum,      ifds::BankAcctNum,      true},  
      {ifds::BankAcctName,     ifds::BankAcctName,     true},  
      {ifds::BankAcctType,     ifds::BankAcctType,     true},
      {ifds::PayReason1,       ifds::PayReason1,       true},
      {ifds::PayReason2,       ifds::PayReason2,       true},
      {ifds::FFC,              ifds::FFC,              true},
      {ifds::FFC1,             ifds::FFC1,             true},
      {ifds::SwiftCode,        ifds::SwiftCode,        true},
      {ifds::RefNumber,        ifds::RefNumber,        true},
      {ifds::BankIdValueCB,    ifds::BankIdValueCB,    true},
      {ifds::BankIdTypeCB,     ifds::BankIdTypeCB,     true},
      {ifds::InstNameCB,       ifds::InstNameCB,       true},
      {ifds::TransitNoCB,      ifds::TransitNoCB,      true},
      {ifds::BankAddrCB1,      ifds::BankAddrCB1,      true},
      {ifds::BankAddrCB2,      ifds::BankAddrCB2,      true},
      {ifds::BankAddrCB3,      ifds::BankAddrCB3,      true},
      {ifds::BankAddrCB4,      ifds::BankAddrCB4,      true},
      {ifds::BankAddrCB5,      ifds::BankAddrCB5,      true},
      {ifds::BankContactCB,    ifds::BankContactCB,    true},
      {ifds::BankCountryCB,    ifds::BankCountryCB,    true},
      {ifds::BankPostalCB,     ifds::BankPostalCB,     true},
      //these fields will not be copied over to the trade object
      {ifds::SettleCurrency,   ifds::BankAcctCurrency, false},
      {ifds::StopDate,         ifds::StopDate,         false},
      {ifds::ACHProcessor,     ifds::ACHProcessor,     false},
      {ifds::EffectiveDate,    ifds::EffectiveDate,    false},
      {ifds::rxAcctNum,        ifds::rxAcctNum,        true}, 
      {ifds::rxBankingEntity,  ifds::rxBankingEntity,  true},
      //{ifds::AccountNum,       ifds::AccountNum,       true},
      
};

int trade_bankFieldMappingInfo_size = sizeof(trade_bankFieldMappingInfo) / sizeof(_bankFieldMappingInfo);
extern const BFFieldId fieldsInBeneficialBank[];
extern const BFFieldId fieldsInCorresBank[];
extern const int numFieldsInCorresBank ;
extern const int numFieldsInBeneficialBank ;

//******************************************************************************
TradeBankInstructions::TradeBankInstructions (BFAbstractCBO &parent) :
 BankInstructionsEx (parent, 
                     BANKTYPE::TRADE, 
                     trade_bankFieldMappingInfo, 
                     trade_bankFieldMappingInfo_size)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************
TradeBankInstructions::~TradeBankInstructions()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY TradeBankInstructions::doApplyRelatedChanges ( const BFFieldId& idField, 
                                                        const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

   BankInstructionsEx::doApplyRelatedChanges (idField, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeBankInstructions::init (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init"));

   assert (getParent() && getParent()->getParent());

   Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
   if (pTrade)
   {
      BankInstructions::init (data, BANKTYPE::TRADE);
      for (int i = 0; i < trade_bankFieldMappingInfo_size; i++)
      {
         bool bFieldExistsInInquiry = true;
         DString dstrValue;

         try
         {
            data.getElementValue (trade_bankFieldMappingInfo [i]._bankInstructionsFieldId, dstrValue);
         }
         catch (BFDataFieldNotFoundException)
         {
            bFieldExistsInInquiry = false;
         }
         if (bFieldExistsInInquiry && trade_bankFieldMappingInfo [i]._isBankField)
         {
            dstrValue.strip();
            pTrade->setField ( trade_bankFieldMappingInfo [i]._cboSpecificFieldId, 
                               dstrValue, BF::HOST, false, true);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeBankInstructions::doInitBeforeCloning (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitBeforeCloning"));

   assert (getParent() && getParent()->getParent());

   DString transType,
	       fileProcessor;
   
   assert (getParent () && getParent ()->getParent ());
//Trade object is the grand-parent
   getParent()->getParent()->getField (ifds::TradesTransType, transType, idDataGroup, false);
   getParent()->getParent()->getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
   setFieldNoValidate (ifds::TransType, transType, idDataGroup, false, true, false, false);
   setFieldNoValidate (ifds::ACHProcessor, fileProcessor, idDataGroup, false, true, false, false);

   DString strDirectDepositBankApplicable,
           strAcctUseCode;
   getWorkSession ().getOption ( ifds::DirectDepositBankApplicable, 
                                 strDirectDepositBankApplicable, 
                                 BF::HOST, false);
   
   getParent()->getParent()->getField( ifds::AcctUseCode, 
                                       strAcctUseCode, 
                                       idDataGroup, 
                                       false ); 

   // if banking information is direct deposit banking
   // do not allow user to change anything on bank field.
   if ( strDirectDepositBankApplicable == I_( "Y" ) && 
        strAcctUseCode == AcctUseCode::DIRECT_DEPOSIT )
   {
      for (int i = 0; i < trade_bankFieldMappingInfo_size; i++)      	
      {
         setFieldReadOnly (trade_bankFieldMappingInfo [i]._bankInstructionsFieldId, idDataGroup, true);
      }
   }
   sSetFieldsReadOnly4RegAgent(idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeBankInstructions::getParentCurrency ( DString &currency,
                                                    DString &description,
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getParentCurrency"));
   if (getParent() && getParent()->getParent())
   {
      getParent()->getParent()->getField (ifds::SettleCurrency, currency, idDataGroup, false);
      getParent()->getParent()->getField (ifds::SettleCurrency, description, idDataGroup, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeBankInstructions::getParentProcessDate ( DString &processDate, 
                                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getParentProcessDate"));
   if (getParent() && getParent()->getParent())
   {
      getParent()->getParent()->getField (ifds::EffectiveDate, processDate, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeBankInstructions::preInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInit"));
   //call super
   BankInstructionsEx::preInit (idDataGroup);
   assert (getParent() && getParent()->getParent());

   DString transType, payType, payMethod, fileProcessor;
   
//Trade object is the grand-parent
   getParent()->getParent()->
       getField (ifds::TradesTransType, transType, idDataGroup, false);

   getParent()->getParent()->getField (ifds::TradesPayType, payType, idDataGroup, false);

   /* Passing PayMethod and FileProcessor value from Systematic to Bank setup */
   getParent()->getParent()->getField (ifds::PayMethod, payMethod, idDataGroup, false);
   setFieldNoValidate (ifds::PayMethod, payMethod, idDataGroup);
   setFieldReadOnly(ifds::PayMethod, idDataGroup, true);

   getParent()->getParent()->getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
   setFieldNoValidate (ifds::ACHProcessor, fileProcessor, idDataGroup);
   setFieldReadOnly(ifds::ACHProcessor, idDataGroup, true);
   
   if (transType == TRADETYPE::ADMIN_FEE)
   {
      setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::COMM_CLEAR, idDataGroup);
   }
   else if (transType == TRADETYPE::PURCHASE)
   {
      setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::EFT_PURCHASE, idDataGroup);
   }
   else if (transType == TRADETYPE::REDEMPTION || transType == TRADETYPE::AUTO_WITHDRAW || transType == TRADETYPE::FULL_EAP_REDEMPTION )
   {
      if ( payType == PAYTYPE::DIRECT_DEPOSIT )
      {
         setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::DIRECT_DEPOSIT, idDataGroup);
      }
      else
      {
         setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::EFT_REDEMPTION, idDataGroup);
      }
   }
   else if (transType == TRADETYPE::MANUAL_MGMT_FEE_REBATE && payType == PAYTYPE::EFT)
   {
       setFieldNoValidate(ifds::AcctUseCode, AcctUseCode::EFT_PURCHASE, idDataGroup);
   }

   setFieldReadOnly (ifds::AcctUseCode, idDataGroup, true);
   sSetFieldsReadOnly4RegAgent(idDataGroup);	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeBankInstructions::postInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("postInit"));
   //calls the base
   BankInstructionsEx::postInit (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}
/******************************************************************************
Input:DataGroupID
OutPut:None
Return:SEVRITY
Functionality:Checks the Pay instr option is redirect to reg agent or not and 
             :Set the fileds to read only for the Banking Instructions
******************************************************************************/
SEVERITY TradeBankInstructions::sSetFieldsReadOnly4RegAgent(const BFDataGroupId &idDataGroup)
{
 MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("SetFieldsReadOnly4RegAgent"));
  //Trade object is the grand-parent
 assert (getParent () && getParent ()->getParent ());
 Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
   if (pTrade)
   {
	DString dstrPayInstrOption;  
    pTrade->getField (ifds::PayInstrOption, dstrPayInstrOption, idDataGroup, false);
	setFieldNoValidate (ifds::PayInstrOption, dstrPayInstrOption, idDataGroup);
	if(I_("03") == dstrPayInstrOption )
	{
		for (int i = 0; i < trade_bankFieldMappingInfo_size; i++)      	
		{
		setFieldReadOnly (trade_bankFieldMappingInfo [i]._bankInstructionsFieldId, idDataGroup, true);
		}
		for (int i = 0; i < numFieldsInBeneficialBank; i++)      	
		{
		setFieldReadOnly (fieldsInBeneficialBank [i], idDataGroup, true);
		}
	}
   }
 return GETCURRENTHIGHESTSEVERITY();
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeBankInstructions.cpp-arc  $
// 
//    Rev 1.10   Apr 24 2012 21:25:46   wp040039
// PETP0187485 - Trade Entry And Processing
// 
//    Rev 1.9   Aug 27 2009 11:17:10   dchatcha
// IN#1808381 - R95 - Investor Authorization - User allowed to override banking details
// 
//    Rev 1.8   Jul 23 2009 08:43:42   dchatcha
// PET156681 FN14 H36 Investor Authorization, fix on displaying trade bank account usage code.
// 
//    Rev 1.7   Oct 06 2006 13:39:42   popescu
// Incident# 729080 - refreshed banking once pending trade settle currency gets changed
// 
//    Rev 1.6   Apr 12 2006 14:09:34   AGUILAAM
// IN 592786 - EFT should be supported for AW trades
// 
//    Rev 1.5   Sep 29 2005 18:58:08   popescu
// Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
// 
//    Rev 1.4   Dec 11 2004 13:25:30   popescu
// PET 1117/06, more fixes for banking instr in pending mode.
// 
//    Rev 1.3   Dec 08 2004 14:53:30   popescu
// PET 1117/56 no copy  for fields mod date, etc...
// 
//    Rev 1.2   Nov 14 2004 14:57:44   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Nov 06 2004 00:42:52   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.0   Nov 01 2004 12:46:38   popescu
// Initial revision.
// 
// Initial revision.
// 
 */