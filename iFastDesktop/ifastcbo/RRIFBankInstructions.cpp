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
//    ^FILE   : RRIFBankInstructions.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : May 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RRIFBankInstructions
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "rrifbankinstructions.hpp"
#include <ifastdataimpl\dse_dstc0129_req.hpp>

namespace 
{
   const I_CHAR * CLASSNAME = I_( "RRIFBankInstructions" );
   const I_CHAR * const ORDINARYDEPOSIT = I_( "1" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId EffectiveFrom;
   extern CLASS_IMPORT const BFTextFieldId BankAcctCurrency;
   extern CLASS_IMPORT const BFTextFieldId SysCurrency;
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

namespace CND
{  // Conditions used
   extern const long ERR_RRIF_SUPPORTS_ONLY_CDN;
}

namespace CRCY
{
   extern CLASS_IMPORT I_CHAR * const CANADIAN_DOLLAR;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const RRIF;
}

namespace AcctUseCode
{
	extern const I_CHAR * const RRIF;
}
const BANKFIELDMAPPINGINFO rrif_bankFieldMappingInfo[] = {
   //RRIF,                   //bank instructions,          //is a bank field
   {ifds::InstCode,          ifds::BankIdValue,            true},
   {ifds::TransitNo,         ifds::TransitNo,              true},
   {ifds::InstName,          ifds::InstName,               true},
   {ifds::BankAcctNum,       ifds::BankAcctNum,            true},
   {ifds::BankType,          ifds::BankIdType,             true},
   {ifds::BankContact,       ifds::BankContact,            true},
   {ifds::BankAddr1,         ifds::BankAddr1,              true},
	{ifds::BankAddr2,         ifds::BankAddr2,              true},
   {ifds::BankAddr3,         ifds::BankAddr3,              true},
   {ifds::BankAddr4,         ifds::BankAddr4,              true},
   {ifds::BankAddr5,         ifds::BankAddr5,              true},
   {ifds::CountryCode,       ifds::BankCountry,            true},
   {ifds::PostalCode,        ifds::BankPostal,             true},
   {ifds::BankIdNum,         ifds::BankIdValue,            true},
   //non-bank fields
   {ifds::EffectiveFrom,     ifds::EffectiveDate,          false},
   {ifds::StopDate,          ifds::StopDate,               false},
};

int rrif_bankFieldMappingInfo_size = 
   sizeof(rrif_bankFieldMappingInfo) / sizeof(_bankFieldMappingInfo);

//******************************************************************************
RRIFBankInstructions::RRIFBankInstructions(BFAbstractCBO &parent) 
: BankInstructionsEx(parent, BANKTYPE::RRIF, 
   rrif_bankFieldMappingInfo, rrif_bankFieldMappingInfo_size)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************
RRIFBankInstructions::~RRIFBankInstructions()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY RRIFBankInstructions::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   BankInstructionsEx::doApplyRelatedChanges(idField, idDataGroup);
   if (idField == ifds::BankAcctCurrency)
   {
      DString dstrBankAcctCurrency;

      getField(ifds::BankAcctCurrency, dstrBankAcctCurrency, idDataGroup, false);
      
      DString sysCurrency;
      getWorkSession().getOption( ifds::SysCurrency, sysCurrency, idDataGroup );


      if (dstrBankAcctCurrency != sysCurrency)
      {
         ADDCONDITIONFROMFILE(CND::ERR_RRIF_SUPPORTS_ONLY_CDN);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RRIFBankInstructions::doInitBeforeCloning (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInitBeforeCloning"));

   assert (getParent() && getParent()->getParent());
   
//RRIF object is the grand-parent
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RRIFBankInstructions::getParentProcessDate ( DString &processDate, 
                                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getParentProcessDate"));

   assert (getParent() && getParent()->getParent());
   if (getParent() && getParent()->getParent())
   {
      getParent()->getParent()->getField (ifds::EffectiveFrom, processDate, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RRIFBankInstructions::getParentCurrency ( DString &currency,
                                                   DString &description,
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getParentCurrency"));

   DString sysCurrency;
   getWorkSession().getOption( ifds::SysCurrency, sysCurrency, idDataGroup );

   currency = sysCurrency;
   description = NULL_STRING;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RRIFBankInstructions::preInit(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("preInit"));
   //call super
   BankInstructionsEx::preInit (idDataGroup);
   //set the bank id type to canadian
   setFieldNoValidate(ifds::BankIdType, I_("03"), idDataGroup);
   setFieldNoValidate(ifds::AcctUseCode, AcctUseCode::RRIF, idDataGroup, false);
   setFieldNoValidate(ifds::TransType, I_("RRIF"), idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RRIFBankInstructions::postInit(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("postInit"));
   //calls the base
   BankInstructionsEx::postInit(idDataGroup);
   //if there is something to initialize for RRIF bank objects

   DString sysCurrency;
   if( getWorkSession().getOption( ifds::SysCurrency, sysCurrency, idDataGroup ) <= WARNING )
   {
      setFieldNoValidate( ifds::BankAcctCurrency, sysCurrency, idDataGroup, true );
   }

   //setFieldNoValidate (ifds::BankAcctCurrency, CRCY::CANADIAN_DOLLAR, idDataGroup);
   setFieldNoValidate (ifds::BankAcctType, ORDINARYDEPOSIT, idDataGroup, false);
   //set the bank account name as read only
   setFieldReadOnly(ifds::BankAcctName, idDataGroup, true);
   setFieldReadOnly(ifds::FFC, idDataGroup, true);
   setFieldReadOnly(ifds::PayReason1, idDataGroup, true);
   setFieldReadOnly(ifds::PayReason2, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIFBankInstructions.cpp-arc  $
// 
//    Rev 1.16   Sep 29 2005 18:57:30   popescu
// Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
// 
//    Rev 1.15   Nov 14 2004 14:53:20   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.14   Sep 23 2004 10:10:22   popescu
// PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
// 
//    Rev 1.13   Sep 09 2004 13:19:52   popescu
// PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
// 
//    Rev 1.12   Dec 29 2003 18:35:42   popescu
// PTS 10025597, cleared the TransitNum if the bank id type changes and the bank id type doesn't support transits
// 
//    Rev 1.11   Oct 04 2003 16:00:46   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
// 
//    Rev 1.10   Aug 11 2003 10:53:06   popescu
// Currency field should be set read only at the base class level, since everybody that inherits from BankInstructionsEx should behave the same way
// 
//    Rev 1.9   Aug 02 2003 11:39:38   popescu
// more banking
// 
//    Rev 1.8   Jul 31 2003 17:08:08   popescu
// set the pay method at the bank not on host level
// 
//    Rev 1.7   Jul 31 2003 13:50:58   popescu
// PTS 10020265, added more bank fields to the RRIF object so they can be copied over to the update view 129, in case new bank mstr needs to be created
// 
//    Rev 1.6   Jul 29 2003 10:42:06   popescu
// Use the AcctUsage namespace
// 
//    Rev 1.5   Jun 18 2003 17:45:08   popescu
// RRIF Banking Enhancement , business rules, bug fixes 
// 
//    Rev 1.4   Jun 05 2003 10:42:20   popescu
// business rules work for banking
// 
//    Rev 1.3   Jun 03 2003 20:59:14   popescu
// Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
// 
//    Rev 1.2   Jun 01 2003 17:07:56   popescu
// Systematic & Distribution banking work
// 
//    Rev 1.1   May 31 2003 20:30:28   popescu
// RRIF work part ||
// 
//    Rev 1.0   May 31 2003 12:00:54   popescu
// Initial revision.
// 
 */