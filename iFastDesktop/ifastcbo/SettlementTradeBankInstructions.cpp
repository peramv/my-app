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
//    ^FILE   : SettlementTradeBankInstructions.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : May 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : SettlementTradeBankInstructions
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "settlementtradebankinstructions.hpp"

namespace 
{
   const I_CHAR * CLASSNAME = I_( "SettlementTradeBankInstructions" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFTextFieldId TradesPayType;
   extern CLASS_IMPORT const BFTextFieldId PayMethod;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SETTLEMENT;
}

namespace AcctUseCode
{
   extern const I_CHAR * const EFT;
   extern const I_CHAR * const EFT_REDEMPTION;
   extern const I_CHAR * const DIRECT_DEPOSIT;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const DIRECT_DEPOSIT;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SETTLE_PAY_INSTRUCTION;
}

const BANKFIELDMAPPINGINFO settlementtrade_bankFieldMappingInfo[] = {
                         //SettlementTrade,        //bank instructions,       //is a bank field   
   {ifds::BankIdValue,       ifds::BankIdValue,         true},
   {ifds::BankIdType,        ifds::BankIdType,          true},
   {ifds::BankId,            ifds::BankId,              true},
   {ifds::TransitNo,         ifds::TransitNo,           true},
   {ifds::InstName,          ifds::InstName,            true},
   {ifds::BankAcctNum,       ifds::BankAcctNum,         true},
   {ifds::BankAcctName,      ifds::BankAcctName,        true},
   {ifds::BankAcctType,      ifds::BankAcctType,        true},
   {ifds::BankAcctCurrency,  ifds::BankAcctCurrency,    true},
   //{ifds::SettleCurrency,    ifds::BankAcctCurrency,    true},
   {ifds::BankAddr1,         ifds::BankAddr1,           true},
   {ifds::BankAddr2,         ifds::BankAddr2,           true},
   {ifds::BankAddr3,         ifds::BankAddr3,           true},
   {ifds::BankAddr4,         ifds::BankAddr4,           true},
   {ifds::BankAddr5,         ifds::BankAddr5,           true},
   {ifds::BankContact,       ifds::BankContact,         true},
   {ifds::BankCountry,       ifds::BankCountry,         true},
   {ifds::BankPostal,        ifds::BankPostal,          true},
   {ifds::BankIdValueCB,     ifds::BankIdValueCB,       true},
   {ifds::BankIdTypeCB,      ifds::BankIdTypeCB,        true},   
   {ifds::TransitNoCB,       ifds::TransitNoCB,         true},
   {ifds::InstNameCB,        ifds::InstNameCB,          true},
   {ifds::BankAddrCB1,       ifds::BankAddrCB1,         true},
   {ifds::BankAddrCB2,       ifds::BankAddrCB2,         true},
   {ifds::BankAddrCB3,       ifds::BankAddrCB3,         true},
   {ifds::BankAddrCB4,       ifds::BankAddrCB4,         true},
   {ifds::BankAddrCB5,       ifds::BankAddrCB5,         true},
   {ifds::BankContactCB,     ifds::BankContactCB,       true},
   {ifds::BankCountryCB,     ifds::BankCountryCB,       true},
   {ifds::BankPostalCB,      ifds::BankPostalCB,        true},
   {ifds::CorrespBankId,     ifds::CorrespBankId,       true},
   {ifds::SwiftCode,         ifds::SwiftCode,           true},
   {ifds::RefNumber,         ifds::RefNumber,           true},
   {ifds::PayReason1,        ifds::PayReason1,          true},
   {ifds::PayReason2,        ifds::PayReason2,          true},
   {ifds::FFC,               ifds::FFC,                 true},
   {ifds::FFC1,              ifds::FFC1,                true},
   {ifds::FFC1,              ifds::FFC1,                true},
   {ifds::AcctID,            ifds::AcctID,              true},
   {ifds::VerifyStat,        ifds::VerifyStat,              true},
   {ifds::rxAcctNum,        ifds::rxAcctNum,            true}, 
   {ifds::rxBankingEntity,  ifds::rxBankingEntity,      true},
   //non-bank fields
   {ifds::ACHProcessor,      ifds::ACHProcessor,        false},   
   {ifds::TransType,         ifds::TransType,           false},
   {ifds::FundCode,          ifds::FundCode,            false},
   {ifds::ClassCode,         ifds::ClassCode,           false},
   {ifds::TradeDate,         ifds::EffectiveDate,       false},
   {ifds::TradeDate,         ifds::StopDate,            false},
};

int settlementtrade_bankFieldMappingInfo_size = 
   sizeof(settlementtrade_bankFieldMappingInfo) / sizeof(_bankFieldMappingInfo);

const BFFieldId fieldsInSettlementBank[]=   
{    
   ifds::BankIdValue, 
   ifds::BankIdType, 
   ifds::BankId, 
   ifds::TransitNo, 
   ifds::InstName, 
   ifds::BankAcctNum,     
   ifds::BankAcctName,    
   ifds::BankAcctType,    
   ifds::BankAcctCurrency,         
   ifds::BankAddr1,       
   ifds::BankAddr2,		  
   ifds::BankAddr3,       
   ifds::BankAddr4,       
   ifds::BankAddr5,       
   ifds::BankContact,     
   ifds::BankCountry,     
   ifds::BankPostal,      
   ifds::BankIdValueCB,   
   ifds::BankIdTypeCB,  
   ifds::TransitNoCB, 
   ifds::InstNameCB,      
   ifds::BankAddrCB1,     
   ifds::BankAddrCB2,	
   ifds::BankAddrCB3,     
   ifds::BankAddrCB4,     
   ifds::BankAddrCB5,     
   ifds::BankContactCB,   
   ifds::BankCountryCB,   
   ifds::BankPostalCB,    
   ifds::CorrespBankId,   
   ifds::SwiftCode,       
   ifds::RefNumber,       
   ifds::FFC,      
   ifds::PayReason1,
   ifds::PayReason2,
   ifds::VerifyStat,
   ifds::AcctID,
   ifds::rxAcctNum,
   ifds::rxBankingEntity,
};

static const int numFieldsInSettlementBank = sizeof (fieldsInSettlementBank) / sizeof (BFFieldId);

//******************************************************************************
SettlementTradeBankInstructions::SettlementTradeBankInstructions(BFAbstractCBO &parent) 
: BankInstructionsEx(parent, BANKTYPE::SETTLEMENT, 
   settlementtrade_bankFieldMappingInfo, settlementtrade_bankFieldMappingInfo_size)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************
SettlementTradeBankInstructions::~SettlementTradeBankInstructions()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY SettlementTradeBankInstructions::getParentCurrency ( DString &currency,
                                                              DString &description,
                                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getParentCurrency"));

   assert (getParent() && getParent()->getParent());
   if (getParent() && getParent()->getParent())
   {
      getParent()->getParent()->getField (ifds::SettleCurrency, currency, idDataGroup, false);
      getParent()->getParent()->getField (ifds::SettleCurrency, description, idDataGroup, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SettlementTradeBankInstructions::getParentProcessDate ( DString &processDate, 
                                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getParentProcessDate"));
   if (getParent() && getParent()->getParent())
   {
      getParent()->getParent()->getField (ifds::TradeDate, processDate, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SettlementTradeBankInstructions::doInitBeforeCloning (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInitBeforeCloning"));

   assert (getParent() && getParent()->getParent());
   
   DString transType,
      fileProcessor;

//distribution object is the grand-parent
   getParent()->getParent()->
         getField (ifds::TransType, transType, idDataGroup, false);
   getParent()->getParent()->
         getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
   setFieldNoValidate (ifds::TransType, transType, idDataGroup, 
      false, true, false, false);
   setFieldNoValidate (ifds::ACHProcessor, fileProcessor, idDataGroup, 
      false, true, false, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SettlementTradeBankInstructions::preInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("notOnHostCommonInit"));
   //calls the base
   BankInstructionsEx::preInit (idDataGroup);
   DString dstrTransType;

   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   if (dstrTransType == TRADETYPE::PURCHASE)
   {
      setFieldNoValidate(ifds::AcctUseCode, AcctUseCode::EFT, idDataGroup, false);
   }
   else if (dstrTransType == TRADETYPE::REDEMPTION)
   {
      DString payType;
      getParent()->getParent()->getField (ifds::TradesPayType, 
                                          payType, 
                                          idDataGroup, 
                                          false);

      if ( payType == PAYTYPE::DIRECT_DEPOSIT )
      {
         setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::DIRECT_DEPOSIT, idDataGroup, false);
      }
      else
      {
         setFieldNoValidate(ifds::AcctUseCode, AcctUseCode::EFT_REDEMPTION, idDataGroup, false);
      }

	  /* Passing PayMethod and FileProcessor value from Systematic to Bank setup */
	  DString payMethod, fileProcessor;
      getParent()->getParent()->getField (ifds::PayMethod, 
                                          payMethod, 
                                          idDataGroup, 
                                          false);
	  setFieldNoValidate(ifds::PayMethod, payMethod, idDataGroup, false);

	  getParent()->getParent()->getField (ifds::ACHProcessor, 
                                          fileProcessor, 
                                          idDataGroup, 
                                          false);
	  setFieldNoValidate(ifds::ACHProcessor, fileProcessor, idDataGroup, false);
   }
   setFieldReadOnly(ifds::AcctUseCode, idDataGroup, true);
   setFieldReadOnly(ifds::ACHProcessor, idDataGroup, true);
   setFieldReadOnly(ifds::PayMethod, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SettlementTradeBankInstructions::postInit(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("postInit"));
   //calls the base
   BankInstructionsEx::postInit (idDataGroup);
   DString currency;

   getField (ifds::BankAcctCurrency, currency, idDataGroup, false);
   if (currency == NULL_STRING)
   {
      //set a default for bank account currency
      assert(getParent()->getParent());

      DString settleCurrency;

      getParent()->getParent()->getField (ifds::SettleCurrency, 
         settleCurrency, idDataGroup, false);
      setFieldNoValidate (ifds::BankAcctCurrency, settleCurrency, 
         idDataGroup, false);
   }

   setFieldsReadOnly( idDataGroup, !hasPermChangeAddrBank());
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void SettlementTradeBankInstructions::setFieldsReadOnly (const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bReadOnly /*= true*/)
{	
   for (int i = 0; i < numFieldsInSettlementBank; i++)
   {
		setFieldReadOnly (fieldsInSettlementBank[i], idDataGroup, bReadOnly);
   }
}

//****************************************************************************
bool SettlementTradeBankInstructions::hasPermChangeAddrBank ()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("copyAddress") );

   bool PermCreate = true;
   bool PermUpdate = true;

   PermCreate = getWorkSession().hasUpdatePermission( UAF::SETTLE_PAY_INSTRUCTION );
   PermUpdate = getWorkSession().hasCreatePermission( UAF::SETTLE_PAY_INSTRUCTION );

   //return PermCreate && PermUpdate;
   return PermUpdate;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTradeBankInstructions.cpp-arc  $
// 
//    Rev 1.15   Nov 26 2009 13:24:02   jankovii
// PET0166583 FN01 Static Data Changes Banking 
// 
//    Rev 1.14   Aug 14 2009 11:15:26   dchatcha
// PET 156681 - FN 14 - Investor Authorization, Settlement screen issue.
// 
//    Rev 1.13   09 Jul 2008 10:31:32   kovacsro
// IN#1339598 - re-arranged the field order, so the bank name does noy get blanked out
// 
//    Rev 1.12   Sep 29 2005 18:57:34   popescu
// Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
// 
//    Rev 1.11   Dec 17 2004 11:28:42   popescu
// PTS 10036680, restored file processor at shareholder level banking, for API use, and removed copying the file processor for SettlementTrade banking if bank is cloned. This is a synch-up from release 58.
// 
//    Rev 1.10   Nov 14 2004 14:54:16   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Sep 23 2004 10:10:26   popescu
// PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
// 
//    Rev 1.8   Sep 09 2004 13:19:56   popescu
// PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
// 
//    Rev 1.7   Feb 09 2004 10:15:46   FENGYONG
// PET965.FN1 SSB Profile restriction
// 
//    Rev 1.6   Dec 29 2003 18:35:46   popescu
// PTS 10025597, cleared the TransitNum if the bank id type changes and the bank id type doesn't support transits
// 
//    Rev 1.5   Oct 19 2003 19:16:22   popescu
// synch-up from 54, for  PTS 10023054
// 
//    Rev 1.4   Oct 04 2003 16:00:58   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
// 
//    Rev 1.3   Aug 02 2003 11:39:38   popescu
// more banking
// 
//    Rev 1.2   Jul 30 2003 11:35:06   popescu
// Correspondent banking is enabled for Distribution banking, AcctUsage EFT, and moved some acct usage codes under the namespace AcctUseCode
// 
//    Rev 1.1   Jun 18 2003 17:45:12   popescu
// RRIF Banking Enhancement , business rules, bug fixes 
// 
//    Rev 1.0   Jun 10 2003 16:13:08   popescu
// Initial revision.
// 
 */