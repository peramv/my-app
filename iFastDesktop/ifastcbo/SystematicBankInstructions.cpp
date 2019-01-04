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
//    ^FILE   : SystematicBankInstructions.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : May 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : SystematicBankInstructions
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "systematicbankinstructions.hpp"
#include "funddetail.hpp"

namespace 
{
   const I_CHAR * CLASSNAME = I_("SystematicBankInstructions");
   const I_CHAR * NO		= I_("N");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId PaymentReason;
   extern CLASS_IMPORT const BFTextFieldId PayMethod;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId AllowBankUpdOnProcessedPAC;
   extern CLASS_IMPORT const BFDateFieldId LastProcessDate;
   extern CLASS_IMPORT const BFTextFieldId BankIdType;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboDefault;
}
namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const  BIC_BANKING_MANDATORY_FOR_PAC;
}
namespace CND
{  // Conditions used
   extern const long ERR_BANK_ACCOUNT_SHOULD_MATCH_SYSTEMATIC_CURRECNCY;
   extern const long ERR_SYSTEMATIC_BANK_INSTRUCTIONS_CURRENCY_MISMATCH;
   extern const long ERR_BANKING_IDYPE_MANDATORY_FOR_PAC;
   extern const long WARN_BANKING_IDYPE_MANDATORY_FOR_PAC;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SYSTEMATIC;
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
namespace FILE_PROCESSOR
{
   const I_CHAR * const BAFF			 =	I_( "BAFF" );
}
namespace BANK_IDTYPE
{
   const I_CHAR * const BIC_CODE		 =	I_( "11" );
}
namespace SYSTEMATIC_TRANS_TYPE
{
   const I_CHAR * const PAC        = I_( "P" );
   const I_CHAR * const SWP        = I_( "S" );
}
const BANKFIELDMAPPINGINFO systematic_bankFieldMappingInfo[] = {
   //Systematic,            //bank instructions     //is bank field
   {ifds::BankIdValue,       ifds::BankIdValue,      true},
   {ifds::BankIdType,        ifds::BankIdType,       true},
   {ifds::BankId,            ifds::BankId,           true},
   {ifds::InstName,          ifds::InstName,         true},
   {ifds::TransitNo,         ifds::TransitNo,        true},
   {ifds::BankAcctNum,       ifds::BankAcctNum,      true},
   {ifds::BankAcctName,      ifds::BankAcctName,     true},
   {ifds::BankAcctType,      ifds::BankAcctType,     true},
   //{ifds::BankAcctTypeDesc,  ifds::BankAcctTypeDesc, true},
   {ifds::BankAcctCurrency,  ifds::BankAcctCurrency, true},
   {ifds::ModDate,           ifds::ModDate,          true},
   {ifds::ModUser,           ifds::ModUser,          true},
   {ifds::Username,          ifds::Username,         true},
   {ifds::ProcessDate,       ifds::ProcessDate,      true},
   {ifds::PayReason1,        ifds::PayReason1,       true},
   {ifds::PayReason2,        ifds::PayReason2,       true},
   {ifds::ACHProcessor,      ifds::ACHProcessor,     true},
   {ifds::FFC,               ifds::FFC,              true},
   {ifds::FFC1,              ifds::FFC1,             true},
   {ifds::BankAddr1,         ifds::BankAddr1,        true},
   {ifds::BankAddr2,		 ifds::BankAddr2,		 true},
   {ifds::BankAddr3,         ifds::BankAddr3,        true},
   {ifds::BankAddr4,         ifds::BankAddr4,        true},
   {ifds::BankAddr5,         ifds::BankAddr5,        true},
   {ifds::BankContact,       ifds::BankContact,      true},
   {ifds::BankCountry,       ifds::BankCountry,      true},
   {ifds::BankPostal,        ifds::BankPostal,       true},
   //these fields will not be copied over to the systematic object
   {ifds::TransType,         ifds::TransType,        false},
   {ifds::FundCode,          ifds::FundCode,         false},
   {ifds::ClassCode,         ifds::ClassCode,        false},
   {ifds::StopDate,          ifds::StopDate,         false},
   {ifds::EffectiveDate,     ifds::EffectiveDate,    false},
};

int systematic_bankFieldMappingInfo_size = 
   sizeof(systematic_bankFieldMappingInfo) / sizeof(_bankFieldMappingInfo);
   
const BFFieldId m_ProcessedPACBankRestrictedFields[]=
{
   ifds::BankIdValue,
   ifds::BankIdType,
   ifds::BankId,
   ifds::InstName,
   ifds::TransitNo, 
   ifds::BankAcctNum,
   ifds::BankAddr1,
   ifds::BankAddr2,
   ifds::BankAddr3,
   ifds::BankAddr4,
   ifds::BankAddr5,
   ifds::BankPostal,
   ifds::BankCountry,
};
int m_ProcessedPACBankRestrictedFields_size = 
   sizeof(m_ProcessedPACBankRestrictedFields) / sizeof(BFFieldId);

//******************************************************************************
SystematicBankInstructions::SystematicBankInstructions(BFAbstractCBO &parent) 
: BankInstructionsEx(parent, BANKTYPE::SYSTEMATIC, 
   systematic_bankFieldMappingInfo, systematic_bankFieldMappingInfo_size)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
}

//******************************************************************************
SystematicBankInstructions::~SystematicBankInstructions()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY SystematicBankInstructions::getParentProcessDate ( DString &processDate, 
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
SEVERITY SystematicBankInstructions::getParentCurrency ( DString &currency,
                                                         DString &description,
                                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getParentCurrency"));

   assert (getParent() && getParent()->getParent());
   if (getParent() && getParent()->getParent())
   {
      getParent()->getParent()->getField (
            ifds::BankAcctCurrency, currency, idDataGroup, false);
      getParent()->getParent()->getField (
            ifds::BankAcctCurrency, description, idDataGroup, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SystematicBankInstructions::doInitBeforeCloning (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInitBeforeCloning"));

   assert (getParent() && getParent()->getParent());
   
   DString transType,
      fileProcessor;

//systematic object is the grand-parent
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
SEVERITY SystematicBankInstructions::doApplyRelatedChanges(const BFFieldId& idField, 
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
            //this should point to the Systematic object
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
SEVERITY SystematicBankInstructions::postInit(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("postInit"));
   DString transType, payMethod, fileProcessor;
   /* Passing PayMethod and FileProcessor value from Systematic to Bank setup */
   getParent()->getParent()->getField (ifds::PayMethod, payMethod, idDataGroup, false);
   setFieldNoValidate (ifds::PayMethod, payMethod, idDataGroup, false, true, true);
   setFieldReadOnly(ifds::PayMethod, idDataGroup, true);

   getParent()->getParent()->getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
   setFieldNoValidate (ifds::ACHProcessor, fileProcessor, idDataGroup, false, true, true);
   setFieldReadOnly(ifds::ACHProcessor, idDataGroup, true);

   getField (ifds::TransType, transType, idDataGroup, false);
   setFieldReadOnly (ifds::AcctUseCode, idDataGroup, true);
   if (transType == TRADETYPE::PAC)
   {
      setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::PAC, idDataGroup, false);
   }
   else if (transType == TRADETYPE::SWP)
   {
      setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::SWP, idDataGroup, false);
   }
   else
   {
      //if there is something to initialize for systematic bank objects
      setFieldNoValidate(ifds::AcctUseCode, AcctUseCode::EFT, idDataGroup, false);
      setFieldReadOnly (ifds::AcctUseCode, idDataGroup, false);
   }
   //calls the base
   BankInstructionsEx::postInit(idDataGroup);
   DString dstrLastProcessDate;
   getParent()->getParent()->getField (ifds::LastProcessDate, dstrLastProcessDate, idDataGroup, false);
   if(TRADETYPE::PAC == transType && NULL_STRING != dstrLastProcessDate)
   {
	   //set the fields read only
	   DString dstrAllowBankUpdOnProcessedPAC;
	   getWorkSession().getOption (ifds::AllowBankUpdOnProcessedPAC, dstrAllowBankUpdOnProcessedPAC, idDataGroup, false);
	   for( int i = 0;i < m_ProcessedPACBankRestrictedFields_size; i++)
	   {
		 setFieldReadOnly(m_ProcessedPACBankRestrictedFields[i], idDataGroup, NO == dstrAllowBankUpdOnProcessedPAC.stripAll());
	   }
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY SystematicBankInstructions::doValidateAll (const BFDataGroupId &idDataGroup, 
													long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));   
   //call base class validations first
   BankInstructionsEx::doValidateAll(idDataGroup, lValidateGroup);
   DString dstrTransType, idiStr;  
   getField(ifds::TransType, dstrTransType, idDataGroup, false);

   if( SYSTEMATIC_TRANS_TYPE::PAC == dstrTransType )
   {
	   DString dstrFileProcessor, dstrBankIdType; 
	   getField(ifds::ACHProcessor, dstrFileProcessor, idDataGroup, false);
	   getField(ifds::BankIdType, dstrBankIdType, idDataGroup, false);

	   if( FILE_PROCESSOR::BAFF == dstrFileProcessor && BANK_IDTYPE::BIC_CODE != dstrBankIdType )
	   {
	     DString fileProc , idtype;
		 idiStr = NULL_STRING;
         addIDITagValue( idiStr, I_("FILE_PROC"), I_("BAFF"));
         addIDITagValue( idiStr, I_("IDTYPE"), I_("BIC Code"));
   		 getErrMsg(IFASTERR::BIC_BANKING_MANDATORY_FOR_PAC, CND::ERR_BANKING_IDYPE_MANDATORY_FOR_PAC, CND::WARN_BANKING_IDYPE_MANDATORY_FOR_PAC,
				   idDataGroup, idiStr);
	   }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SystematicBankInstructions.cpp-arc  $
// 
//    Rev 1.15   Feb 14 2006 14:09:02   porteanm
// Incident 543959 - Two lines of instructions (Pay Reason).
// 
//    Rev 1.14   Sep 29 2005 18:57:36   popescu
// Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
// 
//    Rev 1.13   Dec 08 2004 17:24:02   aguilaam
// PET_910: clean-up for setfields
// 
//    Rev 1.12   Nov 14 2004 14:56:42   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.11   Nov 04 2004 13:47:20   popescu
// PET1094 FN04 - Set acct usage code 31 or 32 when trans type is PAC or SWP
// 
//    Rev 1.10   Sep 23 2004 10:10:30   popescu
// PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
// 
//    Rev 1.9   Sep 09 2004 13:20:12   popescu
// PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
// 
//    Rev 1.8   Sep 07 2004 16:59:12   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.7   Nov 19 2003 10:17:20   popescu
// Fixed issue with copying banking info from Default banking to Systematic. In non-multi currency environment a bank info record should be copied only if the currencies of the sytematic transaction and bank acct match. This is a synch-up from Rel 54.0.0.0.3
// 
//    Rev 1.6   Oct 04 2003 16:01:24   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
// 
//    Rev 1.5   Aug 02 2003 11:39:40   popescu
// more banking
// 
//    Rev 1.4   Jul 31 2003 17:08:06   popescu
// set the pay method at the bank not on host level
// 
//    Rev 1.3   Jul 30 2003 11:35:08   popescu
// Correspondent banking is enabled for Distribution banking, AcctUsage EFT, and moved some acct usage codes under the namespace AcctUseCode
// 
//    Rev 1.2   Jun 18 2003 17:45:14   popescu
// RRIF Banking Enhancement , business rules, bug fixes 
// 
//    Rev 1.1   Jun 03 2003 20:59:28   popescu
// Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
// 
//    Rev 1.0   Jun 01 2003 17:09:38   popescu
// Initial revision.
// 
// 
 */