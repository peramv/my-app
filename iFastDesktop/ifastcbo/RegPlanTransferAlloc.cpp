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
//    Copyright 1997 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : RegPlanTransferAlloc.cpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RegPlanTransferAlloc
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"

#include "regplantransferalloc.hpp"
#include "regplantransferalloclist.hpp"
#include "regplantransfer.hpp"
#include "funddetail.hpp"

#include <ifastdataimpl\dse_dstc0473_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0474_req.hpp>
#include <ifastdataimpl\dse_dstc0474_reqrepeat_record.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_("RegPlanTransferAlloc");
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const INVALID_AMOUNT_TYPE_BY_SEG_RULES;
   extern CLASS_IMPORT I_CHAR * const PLAN_CANNOT_BE_MANUALLY_CREATED;
}

namespace AMT_TYPE
{
    extern CLASS_IMPORT I_CHAR * const CUSTOM;
    extern CLASS_IMPORT I_CHAR * const PORTFOLIO;
}

namespace CND
{  // Conditions used
   extern const long ERR_BLANK_CLASS;
   extern const long ERR_BLANK_FUND;
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_VALUE_CANNOT_BE_ZERO;
   extern const long ERR_INVALID_FUND_NUMBER;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId LoadType;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   {ifds::RegTransferMstrUUID,   BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::RegTransferAllocUUID,  BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::FundNumber,            BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::FundCode,              BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::ClassCode,             BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::Percentage,            BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::Amount,                BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::AllocAmount,           BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::Version,               BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::ModDate,               BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::ModUser,               BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::ProcessDate,           BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::Username,              BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::Commission,            BFCBO::INIT_TO_DEFAULT,      0}, 
};
   
//const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//   { I_("SplitCommissionList"),           BFCBO::NONE,     0},
//};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
//static const int NUM_OBJECTS = sizeof(classObjectInfo) / sizeof(BFCBO::CLASS_OBJECT_INFO);

//******************************************************************************
RegPlanTransferAlloc::RegPlanTransferAlloc(BFAbstractCBO &parent) :
MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);

   registerMemberData(NUM_FIELDS,(const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);

   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);
}

//******************************************************************************
RegPlanTransferAlloc::~RegPlanTransferAlloc()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY RegPlanTransferAlloc::init()
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RegPlanTransferAlloc::init(const BFData &viewData)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   //attach the data object
   attachDataObject(const_cast<BFData&>(viewData), false, true);

   //set the fund number
   DString fundCode, classCode, fundNumber;

   fundCode = viewData.getElementValue(ifds::FundCode);
   classCode = viewData.getElementValue(ifds::ClassCode);
   getWorkSession().GetFundNumber(fundCode.strip().upperCase(), classCode.strip().upperCase(), fundNumber);
   setFundNumber(ifds::ClassCode, BF::HOST);//because ToFundNumber doesn't come from the host

   DString dstrAmountTypeAlloc;
   getParent()->getParent()->getField(ifds::AmountTypeAlloc, dstrAmountTypeAlloc, BF::HOST, false);
   DString dstrAllocAmount;
   getField(ifds::AllocAmount, dstrAllocAmount, BF::HOST, false);
   if(dstrAmountTypeAlloc == I_("P"))
   {
      setField(ifds::Percentage, dstrAllocAmount, BF::HOST, false);
      setFieldValid(ifds::Percentage, BF::HOST, true);
   }
   else if(dstrAmountTypeAlloc == I_("D"))
   {
      setField(ifds::Amount, dstrAllocAmount, BF::HOST, false);
      setFieldValid(ifds::Amount, BF::HOST, true);
   }
   setPercentTypeAlloc(BF::HOST, dstrAmountTypeAlloc == I_("P"));

   FundDetail *pFundDetail = NULL;
   DString dstrFund = fundCode.strip().upperCase();
   DString dstrClass = classCode.strip().upperCase();

   if (!dstrFund.empty() && !dstrClass.empty() &&
      getWorkSession().getFundDetail (dstrFund, dstrClass, BF::HOST, pFundDetail) &&  pFundDetail)
   {
      DString loadType;

      pFundDetail->getField (ifds::LoadType, loadType, BF::HOST, false);
      setFieldReadOnly(ifds::Commission, BF::HOST, I_("FEL") != loadType);
   }           

   clearUpdatedFlags(BF::HOST);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void RegPlanTransferAlloc::getField(const BFFieldId& idField, DString &dstrFieldValue, 
                              const BFDataGroupId& idDataGroup, bool formattedReturn) const
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getField"));
   BFCBO::getField(idField, dstrFieldValue, idDataGroup, formattedReturn);

   if (idField == ifds::FundCode || idField == ifds::ClassCode)
      dstrFieldValue.strip().upperCase();
   else if (idField == ifds::Amount)
   {
      CurrencyClass::getFormattedValue(getWorkSession(), dstrFieldValue, I_(""), I_("D"));
   }
   else if(idField == ifds::Commission)
   {
	   if(formattedReturn)
	   {
		   BFCBO::getField(idField, dstrFieldValue, idDataGroup, false);
		   DSTCommonFunctions::formattedField(ifds::USDollar, 4, dstrFieldValue);
	   }
   }
}

//******************************************************************************
SEVERITY RegPlanTransferAlloc::doValidateField(const BFFieldId& idField,
                                         const DString& strValue,
                                         const BFDataGroupId& idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   DString dstr;
   if (idField == ifds::FundCode)
   {
      validateFundCode (strValue, idDataGroup);
      setValidFlag(ifds::FundClass, idDataGroup, false); 
   }
   else if(idField == ifds::ClassCode)
   {
      DString dstrFundCode;
      getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
      validateClassCode(dstrFundCode, strValue, idDataGroup);
      setValidFlag(ifds::FundClass, idDataGroup, false);
   }
   else if (idField == ifds::FundClass)
   {
      validateFundClass(idDataGroup);
   }
   else if (idField == ifds::Amount)
   {
      validateAmount(strValue, idDataGroup);
   }
   else if (idField == ifds::Percentage)
   {
      validatePercentage (strValue, idDataGroup);
   }
   else if (idField == ifds::FundNumber)
   {
      DString dstrFundCode,dstrClassCode;

      if (!getWorkSession().GetFundClassCode(strValue, dstrFundCode, dstrClassCode))
      {
         ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUND_NUMBER);
      }
   }

   return (GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
void RegPlanTransferAlloc::validateFundClass(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateFundClass"));

   DString dstrFundCode, dstrClassCode, strKey;
   ////////////////////////////////////////////
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   if(dstrClassCode.empty())
   {
      setFieldNoValidate(ifds::FundNumber, NULL_STRING, idDataGroup, false);
      ADDCONDITIONFROMFILE(CND::ERR_BLANK_CLASS);
      return;
   }
   if(dstrFundCode.empty())
   {
      setFieldNoValidate(ifds::FundNumber, NULL_STRING, idDataGroup, false);
      ADDCONDITIONFROMFILE(CND::ERR_BLANK_FUND);
      return;
   }

}

//******************************************************************************
void RegPlanTransferAlloc::validatePercentage(const DString& strValue,const BFDataGroupId& idDataGroup) const
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidatePercentage"));

   DString dstrPercentage(strValue);
   dstrPercentage.strip();
   if(dstrPercentage.empty())
   {
      ADDCONDITIONFROMFILE(CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      return;
   }

   I_CHAR *stopstring;
   double dPercent = wcstod(dstrPercentage.c_str(), &stopstring);

   if(dPercent > 100)
   {
      ADDCONDITIONFROMFILE(CND::ERR_VALUE_BETWEEN_0_AND_100);
      return;
   }

   DString dstrPercentageMask = DSTCommonFunctions::getRawMask(ifds::Percentage);
   dstrPercentageMask.strip();
   int iMaskNumDigitsAfterDecimalPoint = dstrPercentageMask.length() - dstrPercentageMask.find(I_(".")) - 1;

   double dMinValue = pow(10.0, -iMaskNumDigitsAfterDecimalPoint);

   if(dPercent < dMinValue)
      ADDCONDITIONFROMFILE(CND::ERR_VALUE_CANNOT_BE_ZERO);
}

//******************************************************************************

void RegPlanTransferAlloc::validateAmount(const DString& Amount, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateAmount"));

   DString dstrAmount(Amount);
   dstrAmount.stripAll(I_(','));
   double dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);
   DString dstrFundCode, dstrClassCode, dstrTotalAmount;
   RegPlanTransfer* pRegPlanTransfer = dynamic_cast< RegPlanTransfer* >(getParent()->getParent());

   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   pRegPlanTransfer->getField(ifds::Amount, dstrTotalAmount, idDataGroup, false);
   dstrTotalAmount.stripAll(I_(','));

   double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount);

   if(dTotalAmount == 0 && dAmount == 0)
      return;
}

//******************************************************************************
void RegPlanTransferAlloc::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{

}

//******************************************************************************
SEVERITY RegPlanTransferAlloc::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
   
   if (idField == ifds::Amount) 
   {

   }
   else if(idField == ifds::FundCode || idField == ifds::ClassCode)
   {
      DString fundCode, classCode;

      getField(ifds::FundCode, fundCode, idDataGroup, false);
      getField(ifds::ClassCode, classCode, idDataGroup, false);

      setFundNumber(idField,idDataGroup);
      FundDetail *pFundDetail = NULL;

      DString dstrFund = fundCode.strip().upperCase();
      DString dstrClass = classCode.strip().upperCase();

      if (!dstrFund.empty() && !dstrClass.empty() &&
         getWorkSession().getFundDetail (dstrFund, dstrClass, idDataGroup, pFundDetail) &&  pFundDetail)
      {
         DString loadType;

         pFundDetail->getField (ifds::LoadType, loadType, BF::HOST, false);
         setFieldReadOnly(ifds::Commission, idDataGroup, I_("FEL") != loadType);
      }
   }
   else if(idField == ifds::FundNumber)
   {
      setFundClassCode(idField,idDataGroup);
   }
   if(idField == ifds::Percentage || idField == ifds::Amount)
   {  
      setValidFlag(ifds::FundClass, idDataGroup, false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RegPlanTransferAlloc::setField(const BFFieldId& idField, 
                                  const DString& dstrValue,
                                  const BFDataGroupId& idDataGroup, 
                                  bool bFormatted, 
                                  bool bSideEffect,
                                  bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setField"));

   RegPlanTransfer* pRegPlanTransfer = dynamic_cast< RegPlanTransfer* >(getParent()->getParent());
   
   if(idField == ifds::Percentage || idField == ifds::Amount)
   {
      DString dstrOrgValue;
      getField(idField, dstrOrgValue, idDataGroup, bFormatted);
      dstrOrgValue.strip().stripAll(I_CHAR(','));

      DString dstrSetValue(dstrValue);
      dstrSetValue.strip().stripAll(I_CHAR(','));
      if(idField == ifds::Amount)
      {
         //Format the value based on the Currency and the system defined Precisition
         dstrSetValue.strip().stripAll(I_CHAR(','));
      }
      SEVERITY  sevRtn = BFCBO::setField(idField, dstrSetValue, idDataGroup, bFormatted, bSideEffect);
      if(dstrSetValue != dstrOrgValue)
      {
         //get the Total Allocation Amount from the Trade record
         DString dstrTotalAmount;

         pRegPlanTransfer->getField(ifds::ExpectedAmt, dstrTotalAmount, idDataGroup, false);
         dstrTotalAmount.strip().stripAll(I_CHAR(','));

         double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount);

         if(dTotalAmount > 0)
         {
            double dTotalAllocAmount, dTotalAllocPercent;
            RegPlanTransferAllocList *pRegPlanTransferAllocList = dynamic_cast<RegPlanTransferAllocList *>(getParent());
            pRegPlanTransferAllocList->getTotalAllocAmountPercent(idDataGroup, dTotalAllocAmount, dTotalAllocPercent);

            double dPercentage, dAmount;
//            char szBuffer[50]; 
            if(idField == ifds::Percentage)                    //Percentage
            {
               dPercentage = DSTCommonFunctions::convertToDouble(dstrSetValue);
               if(dPercentage == 0)
               {
                  dAmount = 0;
               }
               else if(fabs(dTotalAllocPercent - 100) < 0.0000000001)
               {
                  DString dstrOrgAmount;
                  getField(ifds::Amount, dstrOrgAmount, idDataGroup, false);
                  dstrOrgAmount.strip().stripAll(I_CHAR(','));
                  dAmount = dTotalAmount - (dTotalAllocAmount - DSTCommonFunctions::convertToDouble(dstrOrgAmount));
               }
               else
               {
                  dAmount = dTotalAmount * dPercentage / 100;
               }
               //DString dstrAmount(DStringA(_gcvt(dAmount, 40, szBuffer)));
               DString dstrAmount = DSTCommonFunctions::doubleToDString(ifds::Amount, dAmount);

               dstrAmount.strip().stripAll(I_CHAR(','));
               BFCBO::setField(ifds::Amount, dstrAmount, idDataGroup, false, true);
            }
            else                                                    //Amount
            {
               dAmount = DSTCommonFunctions::convertToDouble(dstrSetValue);
               if(dAmount == 0)
               {
                  dPercentage = 0;
               }
               else if(fabs(dTotalAllocAmount - dTotalAmount) < 0.0000000001)
               {
                  DString dstrOrgPercent;
                  getField(ifds::Percentage, dstrOrgPercent, idDataGroup, false);
                  dstrOrgPercent.strip().stripAll(I_CHAR(','));
                  dPercentage = 100 - (dTotalAllocPercent - DSTCommonFunctions::convertToDouble(dstrOrgPercent));
               }
               else
               {
                  dPercentage = dAmount / dTotalAmount * 100;
               }
               DString dstrPercentage = DSTCommonFunctions::doubleToDString(ifds::Percentage, dPercentage);
               dstrPercentage.strip().stripAll(I_CHAR(','));

               BFCBO::setField(ifds::Percentage, dstrPercentage, idDataGroup, false, true);
            }
         }
      }
      return(GETCURRENTHIGHESTSEVERITY());
   }

   SEVERITY  sevRtn = BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);
   return(GETCURRENTHIGHESTSEVERITY());
}




//*******************************************************************************
void RegPlanTransferAlloc::setFundClassCode(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundClassCode"))
   DString dstrFundNumber,dstrFundCode,dstrClassCode;

   getField(ifds::FundNumber, dstrFundNumber, idDataGroup,false);

   if(dstrFundNumber.strip() != NULL_STRING)
   {
      if(getWorkSession().GetFundClassCode(dstrFundNumber, dstrFundCode, dstrClassCode))
      {
         DString oldFundCode, oldClassCode;
         getField(ifds::FundCode, oldFundCode, idDataGroup, false);
         getField(ifds::ClassCode, oldClassCode, idDataGroup, false);
         if(oldFundCode != dstrFundCode)
            setField(ifds::FundCode, dstrFundCode, idDataGroup, false,true);
         if(oldClassCode != dstrClassCode)
            setField(ifds::ClassCode, dstrClassCode, idDataGroup, false,true);
//         validateAllocCurrency(idDataGroup);
      }
   }
}

//*****************************************************************************
void RegPlanTransferAlloc::setFundNumber(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundNumber"))
   DString dstrFundNumber, dstrFundCode, dstrClassCode, dstrSplitComm, dstrTransType;

   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   if(dstrFundCode.empty() || dstrClassCode.empty())
      return;

   getWorkSession().GetFundNumber(dstrFundCode, dstrClassCode, dstrFundNumber);
   DString oldFundNumber;

   getField(ifds::FundNumber, oldFundNumber, idDataGroup, false);
   if(oldFundNumber.strip() != dstrFundNumber)
   {
      setFieldNoValidate(ifds::FundNumber, dstrFundNumber, idDataGroup, false,true,true);      
   }
   
}

//******************************************************************************
SEVERITY RegPlanTransferAlloc::validateFundCode(const DString& dstrfundCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundCode"));

   DString dstrClassCode;
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   if(dstrClassCode.strip().upperCase() == NULL_STRING)
   {
      setValidFlag(ifds::ClassCode, idDataGroup,  false);
   }
   
   RegPlanTransfer* pRegPlanTransfer = dynamic_cast< RegPlanTransfer* >(getParent()->getParent());

   pRegPlanTransfer->validateFundCode(dstrfundCode, idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());  
}

//******************************************************************************
SEVERITY RegPlanTransferAlloc::validateClassCode(const DString& dstrfundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateClassCode"));

   RegPlanTransfer* pRegPlanTransfer = dynamic_cast< RegPlanTransfer* >(getParent()->getParent());
   pRegPlanTransfer->validateClassCode(dstrfundCode, dstrClassCode, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());  
}

void RegPlanTransferAlloc::setPercentTypeAlloc(const BFDataGroupId& idDataGroup, boolean isPercent)
{
   setFieldReadOnly (ifds::Percentage, idDataGroup, !isPercent);
   setFieldReadOnly (ifds::Amount,     idDataGroup, isPercent);
}

void RegPlanTransferAlloc::ModelOffer(RegPlanTransferAlloc* Model, const BFDataGroupId& idDataGroup)
{
   BFData DSTC0473RepeatData(ifds::DSTC0473_VWRepeat_Record);

   BFDataFieldIter dIter(DSTC0473RepeatData);
   DString str;

   for(;dIter; ++dIter)
   {
      const BFFieldId& idField = dIter().getId();
      
      //DistribDetlRid should not be copied over.
      if( idField == ifds::FundCode || 
         idField == ifds::ClassCode )
      {
         Model->getField(idField, str, idDataGroup, false);
         setField(idField, str, idDataGroup, false);
      }
      else
      {
         setField(idField, I_(""), idDataGroup, false);
      }
   };
   Model->getField(ifds::Percentage, str, idDataGroup, false);
   setField(ifds::Percentage, str, idDataGroup, false);
   Model->getField(ifds::Amount, str, idDataGroup, false);
   setField(ifds::Amount, str, idDataGroup, false);
}

