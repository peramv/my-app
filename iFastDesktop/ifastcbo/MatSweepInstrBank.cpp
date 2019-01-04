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
//    ^FILE   : MatSweepInstrBank.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : May 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : MatSweepInstrBank
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "matsweepinstrbank.hpp"
#include "funddetail.hpp"
#include <ifastdataimpl\dse_dstc0428_vwrepeat_record.hpp> 

namespace 
{
   const I_CHAR * CLASSNAME = I_("MatSweepInstrBank");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId PaymentReason;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId Currency;
}

namespace CND
{  // Conditions used
   extern const long ERR_BANK_ACCOUNT_SHOULD_MATCH_SYSTEMATIC_CURRECNCY;
   extern const long ERR_SYSTEMATIC_BANK_INSTRUCTIONS_CURRENCY_MISMATCH;
}

namespace AcctUseCode
{
   extern const I_CHAR * const EFT_REDEMPTION;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const MATURITY_INSTRUCTIONS;
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

const BANKFIELDMAPPINGINFO matSweepInstr_bankFieldMappingInfo[] = {

   {ifds::BankAcctId,		   ifds::AcctID,        false},
   {ifds::BankIdType,		   ifds::BankIdType,    true},
   {ifds::BankIdValue,		   ifds::BankIdValue,   true},
   {ifds::BankTransitNo,		ifds::TransitNo,     true},
   {ifds::BankSwiftCode,		ifds::SwiftCode,     true},
   {ifds::BankRefNumber,		ifds::RefNumber,     true},
   {ifds::InstName,		      ifds::InstName,      true},
   {ifds::BankAddr1,		      ifds::BankAddr1,     true},
   {ifds::BankAddr2,		      ifds::BankAddr2,     true},
   {ifds::BankAddr3,		      ifds::BankAddr3,     true},
   {ifds::BankAddr4,		      ifds::BankAddr4,     true},
   {ifds::BankAddr5,		      ifds::BankAddr5,     true},
   {ifds::BankPostal,		   ifds::BankPostal,    true},
   {ifds::BankCountry,		   ifds::BankCountry,   true},
   {ifds::BankAcctType,		   ifds::BankAcctType,  true},
//   {ifds::BankAcctTypeDesc,	ifds::BankAcctTypeDesc, false},
   {ifds::BankAcctCurrency,	ifds::BankAcctCurrency, true},
   {ifds::BankEffectiveDate,	ifds::EffectiveDate,    true},
   {ifds::BankStopDate,		   ifds::StopDate,      true},
   {ifds::ACHProcessor,		   ifds::ACHProcessor,  true},
	{ifds::BankContact,		   ifds::BankContact,   true},
   {ifds::BankId,		         ifds::BankId,        true},
   {ifds::BankAcctNum,		   ifds::BankAcctNum,   true},
   {ifds::BankAcctName,		   ifds::BankAcctName,  true},
   {ifds::BankAcctUse,        ifds::AcctUseCode,   true},
   {ifds::PayMethod,          ifds::PayMethod,     true},
   {ifds::BankCorrespondent,  ifds::CorrespBankId, true},

   //these fields will not be copied over to the matSweepInstr object
   {ifds::Currency,           ifds::BankAcctCurrency, false},


   //matSweepInstr,         //bank instructions     //is bank field
 //  {ifds::BankIdValue,       ifds::BankIdValue,      true},
 //  {ifds::BankIdType,        ifds::BankIdType,       true},
 //  {ifds::BankId,            ifds::BankId,           true},
 //  {ifds::InstName,          ifds::InstName,         true},
 //  {ifds::TransitNo,         ifds::TransitNo,        true},
 //  {ifds::BankAcctNum,       ifds::BankAcctNum,      true},
 //  {ifds::BankAcctName,      ifds::BankAcctName,     true},
 //  {ifds::BankAcctType,      ifds::BankAcctType,     true},
 //  {ifds::BankAcctTypeDesc,  ifds::BankAcctTypeDesc, true},
 //  {ifds::BankAcctCurrency,  ifds::BankAcctCurrency, true},
 //  {ifds::ModDate,           ifds::ModDate,          true},
 //  {ifds::ModUser,           ifds::ModUser,          true},
 //  {ifds::Username,          ifds::Username,         true},
 //  {ifds::ProcessDate,       ifds::ProcessDate,      true},
 //  {ifds::PayReason1,        ifds::PayReason1,       true},
 //  {ifds::PayReason2,        ifds::PayReason2,       true},
 //  {ifds::ACHProcessor,      ifds::ACHProcessor,     true},
 //  {ifds::FFC,               ifds::FFC,              true},
 //  {ifds::FFC1,              ifds::FFC1,             true},
 //  {ifds::BankAddr1,         ifds::BankAddr1,        true},
	//{ifds::BankAddr2,			ifds::BankAddr2,			true},
 //  {ifds::BankAddr3,         ifds::BankAddr3,        true},
 //  {ifds::BankAddr4,         ifds::BankAddr4,        true},
 //  {ifds::BankAddr5,         ifds::BankAddr5,        true},
 //  {ifds::BankContact,       ifds::BankContact,      true},
 //  {ifds::BankCountry,       ifds::BankCountry,      true},
 //  {ifds::BankPostal,        ifds::BankPostal,       true},
   //these fields will not be copied over to the matSweepInstr object
   //{ifds::TransType,         ifds::TransType,        false},
   //{ifds::FundCode,          ifds::FundCode,         false},
   //{ifds::ClassCode,         ifds::ClassCode,        false},
   //{ifds::StopDate,          ifds::StopDate,         false},
   //{ifds::EffectiveDate,     ifds::EffectiveDate,    false},
};

int matSweepInstr_bankFieldMappingInfo_size = 
   sizeof(matSweepInstr_bankFieldMappingInfo) / sizeof(_bankFieldMappingInfo);

//******************************************************************************
MatSweepInstrBank::MatSweepInstrBank(BFAbstractCBO &parent) 
: BankInstructionsEx(parent, BANKTYPE::MATURITY_INSTRUCTIONS, 
   matSweepInstr_bankFieldMappingInfo, matSweepInstr_bankFieldMappingInfo_size)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
}

//******************************************************************************
MatSweepInstrBank::~MatSweepInstrBank()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY MatSweepInstrBank::getParentProcessDate ( DString &processDate, 
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
SEVERITY MatSweepInstrBank::getParentCurrency ( DString &currency,
                                                         DString &description,
                                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getParentCurrency"));

   assert (getParent() && getParent()->getParent());
   if (getParent() && getParent()->getParent())
   {
      getParent()->getParent()->getField (
            ifds::Currency, currency, idDataGroup, false);
      getParent()->getParent()->getField (
            ifds::Currency, description, idDataGroup, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MatSweepInstrBank::doInitBeforeCloning (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInitBeforeCloning"));

   assert (getParent() && getParent()->getParent());
   
   DString transType,
      fileProcessor,
	  payMethod;

//matSweepInstr object is the grand-parent
   getParent()->getParent()->
         getField (ifds::TransType, transType, idDataGroup, false);
   getParent()->getParent()->
         getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
   getParent()->getParent()->
	   getField (ifds::PayMethod, payMethod, idDataGroup, false);
   setFieldNoValidate (ifds::TransType, transType, idDataGroup, 
      false, true, false, false);
   setFieldNoValidate (ifds::ACHProcessor, fileProcessor, idDataGroup, 
      false, true, false, false);
   setFieldNoValidate (ifds::PayMethod, payMethod, idDataGroup, 
      false, true, false, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MatSweepInstrBank::doApplyRelatedChanges(const BFFieldId& idField, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (BankInstructionsEx::doApplyRelatedChanges (idField, idDataGroup) <=WARNING)
   {
      if (idField == ifds::BankAcctCurrency)
      {
         assert (getParent() && getParent()->getParent());
         DString multiCurrency;
   
         getWorkSession().getOption (ifds::MultiCurrency, multiCurrency, 
            BF::HOST, false);
         if (multiCurrency == I_("N"))
         {
            DString fundCode, 
               classCode,
            bankAcctCurrency;
            FundDetail *pFundDetail = NULL;

            getField (ifds::BankAcctCurrency, 
               bankAcctCurrency, idDataGroup, false);
            //this should point to the matSweepInstr_bankFieldMappingInfo object
            getParent()->getParent()->getField (ifds::FundCode, 
               fundCode, idDataGroup, false);
            getParent()->getParent()->getField (ifds::ClassCode, 
               classCode, idDataGroup, false);
            if (getWorkSession().getFundDetail (fundCode, classCode, 
               idDataGroup, pFundDetail) && pFundDetail)
            {
               DString fundCurrency;

               pFundDetail->getField (ifds::Currency, fundCurrency, 
                  idDataGroup, false);
               if (fundCurrency != bankAcctCurrency)
               {
                  DString transDescription, 
                     fundCurrencyDescription,
                     bankAcctCurrencyDescription,
                     idiString;

                  getParent()->getParent()->getField (ifds::TransType, 
                     transDescription, idDataGroup, true);
                  pFundDetail->getField (ifds::Currency, fundCurrencyDescription, 
                     idDataGroup, true);
                  getField (ifds::BankAcctCurrency, bankAcctCurrencyDescription, 
                     idDataGroup, true);
                  addIDITagValue (idiString, I_("transdescription"), transDescription); 
                  addIDITagValue (idiString, I_("fundcurrency"), fundCurrencyDescription); 
                  addIDITagValue (idiString, I_("bankcurrency"), bankAcctCurrencyDescription); 
                  ADDCONDITIONFROMFILEIDI (CND::ERR_BANK_ACCOUNT_SHOULD_MATCH_SYSTEMATIC_CURRECNCY, 
                     idiString);
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MatSweepInstrBank::postInit(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("postInit"));
   DString transType;

   //getField (ifds::TransType, transType, idDataGroup, false);
   
   setFieldReadOnly (ifds::AcctUseCode, idDataGroup, true);
   
   setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::EFT_REDEMPTION, idDataGroup, false);

   setFieldReadOnly (ifds::PayMethod, idDataGroup, true);
   //calls the base
   BankInstructionsEx::postInit(idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatSweepInstrBank.cpp-arc  $
// 
//    Rev 1.3   Feb 07 2012 15:47:54   if991250
// removing BankAcctTypeDesc from mapping since is not needed
// 
//    Rev 1.2   Feb 07 2012 13:36:00   jankovii
// Blanked out BankAcctId.
// 
//    Rev 1.1   Feb 02 2012 15:05:30   if991250
// Maturity/Interest Instructions banking
// 
//    Rev 1.0   Feb 01 2012 13:32:46   if991250
// Initial revision.
// 
 */