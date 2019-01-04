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
//    ^FILE   : DistributionBankInstructions.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : May 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : DistributionBankInstructions
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "distributionbankinstructions.hpp"

namespace 
{
   const I_CHAR * CLASSNAME = I_( "DistributionBankInstructions" );
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId DistributionPayType;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId PayMethod;
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

namespace CND
{  // Conditions used
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
}

namespace AcctUseCode
{
   extern const I_CHAR * const EFT;
}

const BANKFIELDMAPPINGINFO distribution_bankFieldMappingInfo[] = {
                         //Distribution,              /bank instructions,        //is bank field
   {ifds::BankIdValue,          ifds::BankIdValue,         true},
   {ifds::BankIdType,           ifds::BankIdType,          true},
   {ifds::BankId,               ifds::BankId,              true},
   {ifds::TransitNo,            ifds::TransitNo,           true},
   {ifds::InstName,             ifds::InstName,            true},
   {ifds::BankAcctNum,          ifds::BankAcctNum,         true},
   {ifds::BankAcctName,         ifds::BankAcctName,        true},
   {ifds::BankAcctType,         ifds::BankAcctType,        true},
//   {ifds::BankAcctTypeDesc,     ifds::BankAcctTypeDesc,    true},
   {ifds::Currency,             ifds::BankAcctCurrency,    true},
   {ifds::TransType,            ifds::TransType,           true},
   {ifds::ModDate,              ifds::ModDate,             true},
   {ifds::ModUser,              ifds::ModUser,             true},
   {ifds::Username,             ifds::Username,            true},
   {ifds::ProcessDate,          ifds::ProcessDate,         true},
   {ifds::PayReason1,           ifds::PayReason1,          true},
   {ifds::PayReason2,           ifds::PayReason2,          true},
   {ifds::ACHProcessor,         ifds::ACHProcessor,        true},
   {ifds::FFC,                  ifds::FFC,                 true},
   {ifds::FFC1,                 ifds::FFC1,                true},
   {ifds::BankAddr1,            ifds::BankAddr1,           true},
	{ifds::BankAddr2,			     ifds::BankAddr2,			  true},
   {ifds::BankAddr3,            ifds::BankAddr3,           true},
   {ifds::BankAddr4,            ifds::BankAddr4,           true},
   {ifds::BankAddr5,            ifds::BankAddr5,           true},
   {ifds::BankContact,          ifds::BankContact,         true},
   {ifds::BankCountry,          ifds::BankCountry,         true},
   {ifds::BankPostal,           ifds::BankPostal,          true},
   {ifds::BankIdValueCB,        ifds::BankIdValueCB,       true},
   {ifds::BankIdTypeCB,         ifds::BankIdTypeCB,        true},   
   {ifds::TransitNoCB,          ifds::TransitNoCB,         true},
   {ifds::InstNameCB,           ifds::InstNameCB,          true},
   {ifds::BankAddrCB1,          ifds::BankAddrCB1,         true},
	{ifds::BankAddrCB2,			  ifds::BankAddrCB2,		     true},
   {ifds::BankAddrCB3,          ifds::BankAddrCB3,         true},
   {ifds::BankAddrCB4,          ifds::BankAddrCB4,         true},
   {ifds::BankAddrCB5,          ifds::BankAddrCB5,         true},
   {ifds::BankContactCB,        ifds::BankContactCB,       true},
   {ifds::BankCountryCB,        ifds::BankCountryCB,       true},
   {ifds::BankPostalCB,         ifds::BankPostalCB,        true},
   {ifds::CorrespBankId,        ifds::CorrespBankId,       true},
   //these fields will not be copied over to the distribution object
   {ifds::DistribDetlRid,       ifds::DistribDetlRid,      false},
   {ifds::FundCode,             ifds::FundCode,            false},
   {ifds::ClassCode,            ifds::ClassCode,           false},
   {ifds::EffectiveDate,        ifds::EffectiveDate,       false},

};

int distribution_bankFieldMappingInfo_size = 
   sizeof(distribution_bankFieldMappingInfo) / sizeof(_bankFieldMappingInfo);

//******************************************************************************
DistributionBankInstructions::DistributionBankInstructions(BFAbstractCBO &parent) 
: BankInstructionsEx(parent, BANKTYPE::DISTRIBUTION, 
   distribution_bankFieldMappingInfo, distribution_bankFieldMappingInfo_size)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************
DistributionBankInstructions::~DistributionBankInstructions()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY DistributionBankInstructions::getParentProcessDate ( DString &processDate, 
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
SEVERITY DistributionBankInstructions::getParentCurrency ( DString &currency,
                                                           DString &description,
                                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getParentCurrency"));

   assert (getParent() && getParent()->getParent());
   if (getParent() && getParent()->getParent())
   {
      getParent()->getParent()->getField (ifds::Currency, currency, idDataGroup, false);
      getParent()->getParent()->getField (ifds::Currency, description, idDataGroup, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DistributionBankInstructions::doInitBeforeCloning (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInitBeforeCloning"));

   assert (getParent() && getParent()->getParent());
   
   DString transType,
      fileProcessor,
	  payMethod;

//distribution object is the grand-parent
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
SEVERITY DistributionBankInstructions::preInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("preInit"));

   BankInstructionsEx::preInit (idDataGroup);
   
   assert (getParent()->getParent());
   
   DString dstrPayMethod,dstrFileProcessor;

  setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::EFT, idDataGroup);
  setFieldReadOnly (ifds::AcctUseCode, idDataGroup, true);

   /* Passing PayMethod and FileProcessor value from Distribution to Bank setup */
   getParent()->getParent()->getField (ifds::PayMethod, 
      dstrPayMethod, idDataGroup, false);   
   setFieldNoValidate (ifds::PayMethod, dstrPayMethod, idDataGroup);
   getParent()->getParent()->getField (ifds::ACHProcessor,
					                   dstrFileProcessor,
									   idDataGroup,
									   false);
   setFieldNoValidate (ifds::ACHProcessor, dstrFileProcessor, idDataGroup, false);

   setFieldReadOnly (ifds::PayMethod, idDataGroup, true);
   setFieldReadOnly (ifds::ACHProcessor, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DistributionBankInstructions::postInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("postInit"));

   BankInstructionsEx::postInit (idDataGroup);
   
   setFieldReadOnly (ifds::ACHProcessor, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DistributionBankInstructions.cpp-arc  $
// 
//    Rev 1.17   09 Jun 2008 15:29:48   kovacsro
// IN#1301713 - changed the order of the fields, so the inst. name does not get blanked out
// 
//    Rev 1.16   Feb 14 2006 13:09:04   porteanm
// Incident 543959 - Two lines of instructions (Pay Reason).
// 
//    Rev 1.15   Sep 29 2005 18:57:20   popescu
// Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
// 
//    Rev 1.14   Dec 17 2004 16:06:02   popescu
// PET 910, removed BankAcctTypeDesc from the mapping information between distribution and bank instructions objects
// 
//    Rev 1.13   Nov 14 2004 14:30:50   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.12   Sep 23 2004 10:10:06   popescu
// PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
// 
//    Rev 1.11   Sep 09 2004 13:19:02   popescu
// PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
// 
//    Rev 1.10   Feb 13 2004 18:49:24   popescu
// PTS 10027180, set the file processor field to read only for distribution banking
// 
//    Rev 1.9   Jan 27 2004 20:04:06   popescu
// PTS 10026408, CITIBNK is not listed in Drop-down list for File Processor in setting up bank information, by Account - Income Distribution
// 
//    Rev 1.8   Dec 29 2003 18:35:40   popescu
// PTS 10025597, cleared the TransitNum if the bank id type changes and the bank id type doesn't support transits
// 
//    Rev 1.7   Dec 22 2003 16:38:24   popescu
// PTS 10025157, Rel 54 synch-up v 1.5.1.0
// 
//    Rev 1.7   Dec 22 2003 16:28:22   popescu
// PTS 10025157, Rel 54 synch-up v 1.5.1.0
// 
//    Rev 1.6   Oct 04 2003 15:58:44   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
// 
//    Rev 1.5   Aug 02 2003 11:39:36   popescu
// more banking
// 
//    Rev 1.4   Jul 30 2003 11:35:04   popescu
// Correspondent banking is enabled for Distribution banking, AcctUsage EFT, and moved some acct usage codes under the namespace AcctUseCode
// 
//    Rev 1.3   Jul 08 2003 15:45:28   popescu
// Fix crash in DistributiobBanking, fields that are not part of the account distribution repeat view were copied over to banking information (not good!)
// 
//    Rev 1.2   Jun 18 2003 17:45:06   popescu
// RRIF Banking Enhancement , business rules, bug fixes 
// 
//    Rev 1.1   Jun 03 2003 20:58:40   popescu
// Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
// 
//    Rev 1.0   Jun 01 2003 17:09:32   popescu
// Initial revision.
// 
// 
 */