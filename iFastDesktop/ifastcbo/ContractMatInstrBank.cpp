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
//    ^FILE   : ContractMatInstrBank.cpp
//    ^AUTHOR : 
//    ^DATE   : 
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ContractMatInstrBank
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "ContractMatInstrBank.hpp"
#include "funddetail.hpp"
#include <ifastdataimpl\dse_dstc0430_vw.hpp> 
#include <ifastdataimpl\dse_dstc0430_vw.hpp> 
#include <ifastdataimpl\dse_dstc0430_vwrepeat_record.hpp> 
#include <ifastdataimpl\dse_dstc0431_reqrepeat_record.hpp> //reqrepeat_record

namespace 
{
   const I_CHAR * CLASSNAME			= I_("ContractMatInstrBank");
   const I_CHAR * CURRENCY_CDN		= I_("CDN");
}

namespace CND
{  
   
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SysCurrency;
}
   
namespace AcctUseCode
{
   extern const I_CHAR * const EFT_REDEMPTION;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const CONTRACTMAT_INSTRUCTIONS;
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

const BANKFIELDMAPPINGINFO ConMatInstr_bankFieldMappingInfo[] = 
{
   //ContMatInstrCBO					BankInstructions 
   {ifds::AcctID,						ifds::AcctID,			true}, //For Bank
   {ifds::SwiftCode,              		ifds::SwiftCode,        true},
   {ifds::RefNumber,              		ifds::RefNumber,        true},
   {ifds::BankAcctNum,            		ifds::BankAcctNum,      true}, //For Bank
   {ifds::BankAcctName,           		ifds::BankAcctName,     true}, //For Bank
   {ifds::BankAcctType,           		ifds::BankAcctType,     true},
   {ifds::BankAcctCurrency,       		ifds::BankAcctCurrency, true},
   {ifds::PayReason1,             		ifds::PayReason1,       true},
   {ifds::PayReason2,             		ifds::PayReason2,       true},
   {ifds::InstName,               		ifds::InstName,         true},
   {ifds::TransitNo,              		ifds::TransitNo,        true},
   {ifds::ACHProcessor,           		ifds::ACHProcessor,     true},
   {ifds::BankPstl,             		   ifds::BankPostal,       true},
   {ifds::BankCntry,            		   ifds::BankCountry,      true},
   {ifds::BankContact,            		ifds::BankContact,      true},
   {ifds::BankAddr1,              		ifds::BankAddr1,        true},
   {ifds::BankAddr2,              		ifds::BankAddr2,        true},
   {ifds::BankAddr3,              		ifds::BankAddr3,        true},
   {ifds::BankAddr4,              		ifds::BankAddr4,        true},
   {ifds::BankAddr5,              		ifds::BankAddr5,        true},
   {ifds::BankId,                 		ifds::BankId,           true},
// {ifds::PayMethod,              		ifds::PayMethod,        true},
   {ifds::CreditInfoLine1,				ifds::FFC,              true},
   {ifds::CreditInfoLine2,				ifds::FFC1,             true},
   {ifds::BankType,						ifds::BankIdType,       true},
   {ifds::BankIdNum,					ifds::BankIdValue,      true}, //For Bank
   {ifds::TransitNum,					ifds::TransitNo,		true}, //For Bank
   {ifds::AcctUseCode,					ifds::AcctUseCode,		true},
   {ifds::StopDate,						ifds::StopDate,         true},
   {ifds::EffectiveDate,				ifds::EffectiveDate,    true},
   {ifds::BankAcctVer,					ifds::BankAcctVer,		true},
};

int ConMatInstr_bankFieldMappingInfo_size = 
   sizeof(ConMatInstr_bankFieldMappingInfo) / sizeof(_bankFieldMappingInfo);

//******************************************************************************
ContractMatInstrBank::ContractMatInstrBank(BFAbstractCBO &parent) 
: BankInstructionsEx(parent, BANKTYPE::CONTRACTMAT_INSTRUCTIONS, 
   ConMatInstr_bankFieldMappingInfo, ConMatInstr_bankFieldMappingInfo_size)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
}

//******************************************************************************
ContractMatInstrBank::~ContractMatInstrBank()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY ContractMatInstrBank::getParentProcessDate ( DString &processDate, 
                                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getParentProcessDate"));

   assert ( getParent() && getParent()->getParent() );

   if (getParent() && getParent()->getParent())
   {
      getParent()->getParent()->getField (ifds::EffectiveDate, processDate, idDataGroup, false);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ContractMatInstrBank::getParentCurrency ( DString &currency,
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
SEVERITY ContractMatInstrBank::doInitBeforeCloning (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInitBeforeCloning"));

   assert (getParent() && getParent()->getParent());
   
   DString sysCurrency;
   getWorkSession().getOption( ifds::SysCurrency, sysCurrency, idDataGroup );
   
   setFieldNoValidate (ifds::BankAcctCurrency, sysCurrency, idDataGroup, false, true, false, false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ContractMatInstrBank::doApplyRelatedChanges(const BFFieldId& idField, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   BankInstructionsEx::doApplyRelatedChanges (idField, idDataGroup);
   setFieldReadOnly (ifds::EffectiveDate, idDataGroup, false);
   setFieldReadOnly (ifds::StopDate, idDataGroup, false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ContractMatInstrBank::postInit(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("postInit"));
   
   setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::EFT_REDEMPTION, idDataGroup, false);

   DString sysCurrency;
   getWorkSession().getOption( ifds::SysCurrency, sysCurrency, idDataGroup );

   setFieldNoValidate (ifds::BankAcctCurrency, sysCurrency, idDataGroup, false);

   setFieldReadOnly (ifds::AcctUseCode, idDataGroup, true);

   BankInstructionsEx::postInit(idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ContractMatInstrBank.cpp-arc  $
// 
//    Rev 1.6   Apr 12 2012 10:20:14   wp040240
// Contract Maturity Instruction Changes
// 
//    Rev 1.5   Mar 28 2012 17:53:06   wp040100
// P0186484 FN05 - Contract Maturity Instruction - Changed the the field in V431 from BankAcctVersion to BankAcctVer - Banking Screen Update Fix
// 
//    Rev 1.4   Mar 22 2012 18:37:56   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.3   Mar 16 2012 17:44:32   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.2   Mar 15 2012 19:33:04   wp040100
// IN 2874666 - P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.1   Mar 05 2012 20:36:50   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.0   Mar 02 2012 16:10:46   wp040100
// Initial revision.
// 
// 
// 
 */