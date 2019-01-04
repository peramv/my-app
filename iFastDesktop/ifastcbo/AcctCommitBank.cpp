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
//    ^FILE   : AcctCommitBank.cpp
//    ^AUTHOR : 
//    ^DATE   : 
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AcctCommitBank
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "AcctCommitBank.hpp"
#include "funddetail.hpp"
#include <ifastdataimpl\dse_dstc0432_vw.hpp> 
#include <ifastdataimpl\dse_dstc0432_vw.hpp> 
#include <ifastdataimpl\dse_dstc0428_vwrepeat_record.hpp> 

namespace 
{
   const I_CHAR * CLASSNAME = I_("AcctCommitBank");
   const I_CHAR * CURRENCY_CDN = I_("CDN");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId PaymentReason;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId SysCurrency;
}

namespace CND
{  // Conditions used
   extern const long ERR_BANK_ACCOUNT_SHOULD_MATCH_SYSTEMATIC_CURRECNCY;
   extern const long ERR_SYSTEMATIC_BANK_INSTRUCTIONS_CURRENCY_MISMATCH;
}

namespace AcctUseCode
{
   extern const I_CHAR * const EFT_PURCHASE;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_COMMITMENT;
}

namespace AcctUseCode
{
   extern const I_CHAR * const EFT;
   extern const I_CHAR * const PAC;
   extern const I_CHAR * const SWP;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
}

const BANKFIELDMAPPINGINFO acctCommit_bankFieldMappingInfo[] = {

   {ifds::SwiftCode,              		ifds::SwiftCode,        true},
   {ifds::RefNumber,              		ifds::RefNumber,        true},
   {ifds::BankAcctNum,            		ifds::BankAcctNum,      true},
   {ifds::BankAcctName,           		ifds::BankAcctName,     true},
   {ifds::BankAcctType,           		ifds::BankAcctType,     true},
   {ifds::BankAcctCurrency,       		ifds::BankAcctCurrency, true},
   {ifds::PayReason1,             		ifds::PayReason1,       true},
   {ifds::PayReason2,             		ifds::PayReason2,       true},
   {ifds::InstName,               		ifds::InstName,         true},
   {ifds::TransitNo,              		ifds::TransitNo,        true},
   {ifds::ACHProcessor,           		ifds::ACHProcessor,     true},
   {ifds::BankPostal,             		ifds::BankPstl,         true},
   {ifds::BankCountry,            		ifds::BankCntry,        true},
   {ifds::BankContact,            		ifds::BankContact,      true},
   {ifds::BankAddr1,              		ifds::BankAddr1,        true},
   {ifds::BankAddr2,              		ifds::BankAddr2,        true},
   {ifds::BankAddr3,              		ifds::BankAddr3,        true},
   {ifds::BankAddr4,              		ifds::BankAddr4,        true},
   {ifds::BankAddr5,              		ifds::BankAddr5,        true},
   {ifds::BankId,                 		ifds::BankId,           true},
   {ifds::PayMethod,              		ifds::PayMethod,        true},

   {ifds::CreditInfoLine1,             ifds::FFC,              true},
   {ifds::CreditInfoLine2,             ifds::FFC1,             true},
   {ifds::BankType,                    ifds::BankIdType,       true},
   {ifds::BankIdNum,                   ifds::BankIdValue,      true},
   {ifds::InstCode,                    ifds::BankIdValue,      true},
//need to add SourceOfBankAcct

};

int acctCommit_bankFieldMappingInfo_size = 
   sizeof(acctCommit_bankFieldMappingInfo) / sizeof(_bankFieldMappingInfo);

//******************************************************************************
AcctCommitBank::AcctCommitBank(BFAbstractCBO &parent) 
: BankInstructionsEx(parent, BANKTYPE::ACCOUNT_COMMITMENT, 
   acctCommit_bankFieldMappingInfo, acctCommit_bankFieldMappingInfo_size)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
}

//******************************************************************************
AcctCommitBank::~AcctCommitBank()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcctCommitBank::getParentProcessDate ( DString &processDate, 
                                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getParentProcessDate"));
   assert (getParent() && getParent()->getParent());
   if (getParent() && getParent()->getParent())
   {
      getParent()->getParent()->getField (ifds::EffectiveDate, processDate, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctCommitBank::getParentCurrency ( DString &currency,
                                                         DString &description,
                                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getParentCurrency"));

   DString sysCurrency;
   getWorkSession().getOption( ifds::SysCurrency, sysCurrency, idDataGroup );

   currency = sysCurrency;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctCommitBank::doInitBeforeCloning (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInitBeforeCloning"));

   assert (getParent() && getParent()->getParent());
   
   DString sysCurrency;
   getWorkSession().getOption( ifds::SysCurrency, sysCurrency, idDataGroup );

   setFieldNoValidate (ifds::BankAcctCurrency, sysCurrency, idDataGroup, false, true, false, false);

   //DString transType,
   //   fileProcessor;

   //getParent()->getParent()->
   //      getField (ifds::TransType, transType, idDataGroup, false);
   //getParent()->getParent()->
   //      getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
   //setFieldNoValidate (ifds::TransType, transType, idDataGroup, 
   //   false, true, false, false);
   //setFieldNoValidate (ifds::ACHProcessor, fileProcessor, idDataGroup, 
   //   false, true, false, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctCommitBank::doApplyRelatedChanges(const BFFieldId& idField, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   BankInstructionsEx::doApplyRelatedChanges (idField, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctCommitBank::postInit(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("postInit"));
   DString transType;
   
   setFieldReadOnly (ifds::AcctUseCode, idDataGroup, true);
   
   setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::EFT_PURCHASE, idDataGroup, false);
   setFieldNoValidate(ifds::TransType, TRADETYPE::PAC, idDataGroup, false);

   DString sysCurrency;
   getWorkSession().getOption( ifds::SysCurrency, sysCurrency, idDataGroup );

   setFieldNoValidate (ifds::BankAcctCurrency, sysCurrency, idDataGroup, false);   
   //calls the base
   BankInstructionsEx::postInit(idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCommitBank.cpp-arc  $
// 
//    Rev 1.0   Feb 27 2012 09:15:34   if991250
// Initial revision.
// 
// 
 */