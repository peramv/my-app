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
//    ^FILE   : BankInstructionsEx.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : May 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : BankInstructionsEx
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0052_vw.hpp>
#include "bankinstructionsex.hpp"
#include "distributionbankinstructions.hpp"
#include "rrifbankinstructions.hpp"
#include "systematicbankinstructions.hpp"

namespace 
{
   const I_CHAR * CLASSNAME = I_( "BankInstructionsEx" );
   const I_CHAR * const WIRE = I_ ("WIRE");
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId BankAcctCurrency;
	extern CLASS_IMPORT const BFTextFieldId ACHProcessor;
   extern CLASS_IMPORT const BFTextFieldId BankInstrType;
   extern CLASS_IMPORT const BFTextFieldId PayMethod;
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

namespace CND
{  // Conditions used
   extern const long ERR_CURRENCY_MISMATCH;
   extern const long ERR_BANK_INSTRUCTIONS_STOPPED;
   extern const long ERR_BANK_INSTRUCTIONS_NOT_EFFECTIVE;
}

//******************************************************************************
BankInstructionsEx::BankInstructionsEx( BFAbstractCBO &parent, 
                                        const DString &dstrBankType, 
                                        const BANKFIELDMAPPINGINFO *pCBO_bankFieldMappingInfo,
                                        int mappingInfoSize) : BankInstructions(parent),
_dstrBankType(dstrBankType),
_pCBO_bankFieldMappingInfo(pCBO_bankFieldMappingInfo),
_mappingInfoSize(mappingInfoSize)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************
BankInstructionsEx::~BankInstructionsEx()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY BankInstructionsEx::initBeforeCloning (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initBeforeCloning"));
   _bGetsCloned = true;
   setFieldNoValidate (ifds::BankInstrType, _dstrBankType, idDataGroup, false);
//pay method is not in view 52
//probably the right thing to do is to add this field to view 52
//until then, we know it's always Wire
   
   DString dstrPayMethod, dstrFileProcessor;
   getParent()->getParent()->getField(ifds::PayMethod, dstrPayMethod, idDataGroup);
   getParent()->getParent()->getField(ifds::ACHProcessor, dstrFileProcessor, idDataGroup);
   setFieldNoValidate (ifds::PayMethod, dstrPayMethod, idDataGroup, false);
   setFieldNoValidate (ifds::ACHProcessor, dstrFileProcessor, idDataGroup, false);
   doInitBeforeCloning (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructionsEx::initNew ( const BFDataGroupId &idDataGroup, 
                                       bool cloned /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   BFAbstractCBO *parentCBO = getParentCBO ();

   fromSpecificCBOToBankInstructions (parentCBO, 
                                      _pCBO_bankFieldMappingInfo, 
                                      _mappingInfoSize, 
                                      idDataGroup, 
                                      cloned);
   //call the base
   BankInstructions::initNew(_dstrBankType, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructionsEx::init ( const BFData &parentData,
                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   //here create a bank instructions view data, that uses view 52 repeat
   //based on the parent's view data (parentData), expand the parents's view into
   //a bank instructions view, also set parent specific values 
   //on the bank instructions
   BFData *pBFData0052Repeat = new BFData(ifds::DSTC0052_VWRepeat_Record);

   //copy over the other values,
   fromSpecificCBOToBankInstructions (parentData, _pCBO_bankFieldMappingInfo, 
      _mappingInfoSize, idDataGroup);
   //call the base class
   BankInstructions::init(*pBFData0052Repeat, _dstrBankType, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void BankInstructionsEx::doReset(const BFDataGroupId &idDataGroup)
{
   initNew (idDataGroup, false);
   if (isNew())
   {
      doInitWithDefaultValues(idDataGroup);
   }
}

//******************************************************************************
SEVERITY BankInstructionsEx::setField  ( const BFFieldId &fieldId,
                                         const DString& strValue,
                                         const BFDataGroupId& idDataGroup, 
                                         bool lFormatted /*= true*/,
                                         bool lSideEffect /*= false*/,
                                         bool bCheckCurrentValue /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("setField"));

   DString value (strValue);

   bool bSkipSetField = 
      _bGetsCloned &&  //are we in the cloning process?
      //do not copy the file processor from the object that gets cloned (i.e Shareholder banking)
      (fieldId == ifds::ACHProcessor || 
      //do not copy the bank country from the object that gets cloned if bank country is empty
      //give user a chance to enter it 
      //bank country is a required field on Desktop, 
      //so the clone object will fail, if an empty field is copied;
      //this fix is put in to avoid cases in which the data record does not contain bank country;
      //(note: bank country is not required in iFast Base)
      (fieldId == ifds::BankCountry && value.strip().empty())); 

   if (!bSkipSetField)
   {
      BankInstructions::setField ( fieldId, 
                                   strValue, 
                                   idDataGroup, 
                                   lFormatted,
                                   lSideEffect, 
                                   bCheckCurrentValue);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructionsEx::doValidateField ( const BFFieldId &idField,
                                               const DString &strValue, 
                                               const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));

   BankInstructions::doValidateField (idField, strValue, idDataGroup);
   //if cloned, stop date should be greater process date (i.e process date for trade is EffectiveDate (trade date))
   if (_bGetsCloned) 
   {
      if (idField == ifds::StopDate)
      {
         DString processDate;
         
         getParentProcessDate (processDate, idDataGroup);
         if ( !processDate.empty() && 
              DSTCommonFunctions::CompareDates (strValue, processDate) == DSTCommonFunctions::FIRST_EARLIER)
         {
            DString idiString,
               formattedValue (strValue);

            formatField (idField, formattedValue, idDataGroup);
            addIDITagValue (idiString, I_("stopdate"), formattedValue); 

   //raise an error - process date is beyond bank stop date
            ADDCONDITIONFROMFILEIDI (CND::ERR_BANK_INSTRUCTIONS_STOPPED, idiString);
         }
      }
      else if (idField == ifds::EffectiveDate)
      {
         DString processDate;
         
         getParentProcessDate (processDate, idDataGroup);
         if ( !processDate.empty() && 
              DSTCommonFunctions::CompareDates (processDate, strValue) == DSTCommonFunctions::FIRST_EARLIER)
         {
            DString idiString,
               formattedValue (strValue);

            formatField (idField, formattedValue, idDataGroup);
            addIDITagValue (idiString, I_("effectivedate"), formattedValue); 

   //raise an error - process date is before  bank effectvie date
            ADDCONDITIONFROMFILEIDI (CND::ERR_BANK_INSTRUCTIONS_NOT_EFFECTIVE, idiString);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
 SEVERITY BankInstructionsEx::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   BankInstructions::doApplyRelatedChanges (idField, idDataGroup);
   //raise error if currencies do not match
   if (_bGetsCloned && idField == ifds::BankAcctCurrency)
   {
      DString parentCurrency,
         parentCurrencyDescription,
         bankAcctCurrency;

      getParentCurrency (parentCurrency, parentCurrencyDescription, idDataGroup);
      getField (ifds::BankAcctCurrency, bankAcctCurrency, idDataGroup, false);
      if (parentCurrency != bankAcctCurrency)
      {
         DString transDescription,
            bankAcctCurrencyDescription,
            idiString;

         getField (ifds::TransType, 
            transDescription, idDataGroup, true);
         getField (ifds::BankAcctCurrency, 
            bankAcctCurrencyDescription, idDataGroup, true);
         addIDITagValue (idiString, I_("transdescription"), transDescription); 
         addIDITagValue (idiString, I_("bankcurr"), bankAcctCurrencyDescription); 
         addIDITagValue (idiString, I_("syscurr"), parentCurrencyDescription);
         ADDCONDITIONFROMFILEIDI ( CND::ERR_CURRENCY_MISMATCH, 
                                   idiString);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructionsEx::copyToSpecificCBO (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("copyToSpecificCBO"));

   BFAbstractCBO* pCBOParent = getParentCBO ();

   fromBankInstructionsToSpecificCBO (pCBOParent, _pCBO_bankFieldMappingInfo, 
      _mappingInfoSize, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructionsEx::postInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   //effective date on the bank object should be set to read only
   setFieldReadOnly (ifds::EffectiveDate, idDataGroup, true);
   setFieldReadOnly (ifds::StopDate, idDataGroup, true);
   //currency on the bank object should be set to read only
   setFieldReadOnly(ifds::BankAcctCurrency, idDataGroup, true);
	setFieldReadOnly(ifds::ACHProcessor, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
BFAbstractCBO * BankInstructionsEx::getParentCBO ()
{
   return getParent()->getParent();
}

//uses a data object
//******************************************************************************
void BankInstructionsEx::
   fromSpecificCBOToBankInstructions ( const BFData &bfData, 
                                       const BANKFIELDMAPPINGINFO *pBankFieldMappingInfo, 
                                       int mappingInfoSize,
                                       const BFDataGroupId &idDataGroup, 
                                       bool copyOnlyNonBankItems /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, 
      I_( "fromSpecificCBOToBankInstructions" ));

   for (int i = 0; i < mappingInfoSize; i++)
   {
      bool copy = !copyOnlyNonBankItems ||
         (copyOnlyNonBankItems && !pBankFieldMappingInfo[i]._isBankField);
      DString dstrValue;

      if (copy)
      {
         bool bFieldExistsInInquiry = true;

         try
         {
            bfData.getElementValue (pBankFieldMappingInfo[i]._cboSpecificFieldId, dstrValue);
         }
         catch (BFDataFieldNotFoundException)
         {
            //this might happen when the field is not part of the inquiry view,
            //but it is in the field_info of the object and needs to be set 
            //to the update view, which contains it, see RRIF
            bFieldExistsInInquiry = false;
         }
         if (bFieldExistsInInquiry)
         {
            dstrValue.strip();
            setFieldNoValidate (pBankFieldMappingInfo[i]._bankInstructionsFieldId, dstrValue, 
               idDataGroup, false, true, true);
         }
      }
   }
}

//******************************************************************************
void BankInstructionsEx::
   fromSpecificCBOToBankInstructions ( const BFAbstractCBO *bfCBO, 
                                       const BANKFIELDMAPPINGINFO *pBankFieldMappingInfo, 
                                       int mappingInfoSize, 
                                       const BFDataGroupId &idDataGroup, 
                                       bool copyOnlyNonBankItems /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "fromSpecificCBOToBankInstructions" ));

   for (int i = 0; i < mappingInfoSize; i++)
   {
      // !copyOnlyNonBankItems means copy all items (bank and non-bank)
      // if we want to only copy the non bank items then we check
      // the _isBankField flag which should be set to false
      bool copy = !copyOnlyNonBankItems ||
         (copyOnlyNonBankItems && !pBankFieldMappingInfo [i]._isBankField);
         
      if (copy)
      {
         DString strValue;

         bfCBO->getField( pBankFieldMappingInfo [i]._cboSpecificFieldId, 
                          strValue, idDataGroup, false);
         if (!strValue.empty()) //do not copy empty values
         {
            setFieldNoValidate( pBankFieldMappingInfo [i]._bankInstructionsFieldId, 
                                strValue, idDataGroup, false, true, true);
         }
      }
   }
}

//******************************************************************************
void BankInstructionsEx::
   fromBankInstructionsToSpecificCBO ( BFAbstractCBO *bfCBO, 
                                       const BANKFIELDMAPPINGINFO *pBankFieldMappingInfo, 
                                       int mappingInfoSize, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "fromBankInstructionsToSpecificCBO" ));

   for (int i = 0; i < mappingInfoSize; i++)
   {
      //copy it over to the specific CBO
      //only if it is a bank field
      if (pBankFieldMappingInfo[i]._isBankField)
      {
         DString dstrValue;

         getField ( pBankFieldMappingInfo[i]._bankInstructionsFieldId, 
                    dstrValue, idDataGroup, false);
         bfCBO->setField( pBankFieldMappingInfo[i]._cboSpecificFieldId, dstrValue, 
                          idDataGroup, false, true);
      }
   }
}
//******************************************************************************
SEVERITY BankInstructionsEx::doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup)
{
	 MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
	 BankInstructions::doValidateAll(idDataGroup, lValidateGroup);
	 return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructionsEx.cpp-arc  $
// 
//    Rev 1.16   Mar 08 2010 12:14:40   popescu
// Incident 2039534 - fixed the issue where unverified banking instruction are not copied with the proper value of the verify status field. they get reset to verified, if they are un-verified
// 
//    Rev 1.15   Jan 12 2010 15:35:44   jankovii
// IN 1964321 & 1964324 - Static data issues.
// 
//    Rev 1.14   09 Mar 2009 11:12:36   kovacsro
// IN#1609264 - PET155543R92 Bank name not display in acct level distrib instruction
// 
//    Rev 1.13   Sep 10 2006 17:58:32   popescu
// STP 2192/12
// 
//    Rev 1.12   Jul 31 2006 15:28:58   ZHANGCEL
// PET2192 FN11 -- MgmtCo Banking related changes
// 
//    Rev 1.11   Sep 29 2005 18:57:16   popescu
// Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
// 
//    Rev 1.10   Feb 28 2005 14:59:12   popescu
// PET 1117/06, should not copy bank country while cloning and field is empty, to avoid cases in which the iFastBase data record does not contain the information
// 
//    Rev 1.9   Dec 08 2004 17:22:24   aguilaam
// PET_910: clean-up for setfields
// 
//    Rev 1.8   Sep 23 2004 10:09:54   popescu
// PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
// 
//    Rev 1.7   Sep 09 2004 13:18:28   popescu
// PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
// 
//    Rev 1.6   Sep 07 2004 16:58:10   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.5   May 04 2004 10:31:00   FENGYONG
// PTS 10029835, settlementtrade banking
// 
//    Rev 1.4   Feb 11 2004 14:55:58   popescu
// PTS 10026899, the substitution list for currency it is loaded from host if empty after trying to get it dynamically; also, dealt with the 0 value of the 'TransitNo' in bank instructions
// 
//    Rev 1.3   Jan 28 2004 23:03:00   popescu
// PTS 10026408, in distribution file processor is only required when pay type is 'E' - EFT,
// BankInstructionsEx.cpp added a stripAll for the copied values
// 
//    Rev 1.2   Nov 19 2003 10:19:06   popescu
// Move postInit at the parent level, BankInstructions
// 
//    Rev 1.1   Oct 19 2003 16:43:32   popescu
// CIBC, PET809, FN 13 banking work
// 
//    Rev 1.0   Oct 04 2003 16:08:34   popescu
// Initial revision.
// 
//    Rev 1.7   Aug 11 2003 10:52:58   popescu
// Currency field should be set read only at the base class level, since everybody that inherits from BankInstructionsEx should behave the same way
// 
//    Rev 1.6   Aug 02 2003 11:39:34   popescu
// more banking
// 
//    Rev 1.5   Jul 31 2003 19:29:50   popescu
// Since PayMethod is not a field of view 52, moved the initialization of PayMethod in the commonInit function, and we know for sure that this field is always set to Wire
// 
//    Rev 1.4   Jul 31 2003 17:07:56   popescu
// set the pay method at the bank not on host level
// 
//    Rev 1.3   Jul 31 2003 13:50:54   popescu
// PTS 10020265, added more bank fields to the RRIF object so they can be copied over to the update view 129, in case new bank mstr needs to be created
// 
//    Rev 1.2   Jun 18 2003 17:45:02   popescu
// RRIF Banking Enhancement , business rules, bug fixes 
// 
//    Rev 1.1   Jun 05 2003 10:42:18   popescu
// business rules work for banking
// 
//    Rev 1.0   Jun 03 2003 21:00:52   popescu
// Initial revision.
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