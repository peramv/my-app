//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial
//
//
//******************************************************************************
//
// ^FILE   : FeeModel.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : FeeModel
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feemodel.hpp"
#include "feemodellist.hpp"
#include "feemodelsetuplist.hpp"
#include "feemodelcopytogrouplist.hpp"

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0305_vw.hpp>
#include <ifastdataimpl\dse_dstc0305_req.hpp>
#include <ifastdataimpl\dse_dstc0305_vwrepeat_record.hpp>
#include "holdingcomp.hpp"
#include "holdingcomplist.hpp"
#include "fundcommgrouplist.hpp"

namespace  
{
   const I_CHAR * const CLASSNAME                  = I_( "FeeModel" );
   const I_CHAR * const YES                        = I_("Y");
   const I_CHAR * const FEE_MODEL_TYPE_ADVISOR_FEE = I_("DF");
   const I_CHAR * const NULL_DATE                  = I_("12319999");
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId FeeModelType;
   extern CLASS_IMPORT const BFTextFieldId ApplFeeModelType;
   extern CLASS_IMPORT const BFTextFieldId AutoGenFeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId ModelAggregationMethod;
   extern CLASS_IMPORT const BFTextFieldId CompanyUsage;
   extern CLASS_IMPORT const BFTextFieldId AggregationMethod;
   extern CLASS_IMPORT const BFTextFieldId FundGroupType;
   extern CLASS_IMPORT const BFTextFieldId FundGrpTypeList;
   extern CLASS_IMPORT const BFTextFieldId AggregationMethodList;
   extern CLASS_IMPORT const BFTextFieldId CalcRateTypeList;
   extern CLASS_IMPORT const BFTextFieldId FeeModelOptionList;
   extern CLASS_IMPORT const BFTextFieldId SchedSetupFreqAppl;
   extern CLASS_IMPORT const BFTextFieldId FeeModelTypeCode;
   extern CLASS_IMPORT const BFTextFieldId HoldingEntityAppl;
   extern CLASS_IMPORT const BFTextFieldId CalcCurrencyAppl;
   extern CLASS_IMPORT const BFTextFieldId AutoGenOverride;
   extern CLASS_IMPORT const BFTextFieldId GroupDest;
   extern CLASS_IMPORT const BFTextFieldId AllowCopy;
   extern CLASS_IMPORT const BFTextFieldId SameDlrBrnRep;
   extern CLASS_IMPORT const BFTextFieldId ReqMode;
   extern CLASS_IMPORT const BFTextFieldId AcctGrpType;
   extern CLASS_IMPORT const BFIntegerFieldId FullMoneyOutApplicable;
}

namespace CND
{  // Conditions used
   extern const long ERR_EFF_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_EFFECTIVE_DATE_FORWARD;
   extern const long ERR_INVALID_HOLDING_COMP_CODE;
   extern const long ERR_HOLDING_COMP_CODE_IS_REQUIRED;
   extern const long ERR_FEE_MODEL_ALREADY_IN_USE;
   extern const long ERR_FEE_MODEL_DEFF_NOT_APPLIC_TO_ACCT_ASSOC;
   extern const long WARN_FEE_MODEL_DEFF_NOT_APPLIC_TO_ACCT_ASSOC;
   extern const long ERR_FEE_MODEL_STOP_DATE_NOT_APPLIC_TO_ACCT_ASSOC;
   extern const long WARN_FEE_MODEL_STOP_DATE_NOT_APPLIC_TO_ACCT_ASSOC;
   extern const long ERR_FEE_MODEL_CANNOT_BE_STOPPED_BEFORE_LAST_PROCESS_DATE;
   extern const long WARN_FEE_MODEL_CANNOT_BE_STOPPED_BEFORE_LAST_PROCESS_DATE;
}
namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const FEE_MODEL_DEFF_NOT_APPLIC_TO_ACCT_ASSOC;
   extern CLASS_IMPORT I_CHAR * const FEE_MODEL_CANNOT_BE_STOPPED_BEFORE_LAST_PROCESS_DATE;
}
//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                    State Flags,         Group Flags       

   { ifds::FeeModelCode,            BFCBO::REQUIRED,        0 }, 
   { ifds::FeeModelDesc,            BFCBO::REQUIRED,        0 },
   { ifds::FeeModelType,            BFCBO::REQUIRED,        0 },
   { ifds::FeeModelTypeCode,        BFCBO::CALCULATED_FIELD,0 },
   { ifds::EffectiveDate,           BFCBO::NONE,            0 },
   { ifds::StopDate,                BFCBO::NONE,            0 },
   { ifds::CompoundDate,            BFCBO::NONE,            0 },
   { ifds::ApplFeeModelType,        BFCBO::NOT_ON_HOST,     0 },

   { ifds::HoldingCompCode,         BFCBO::NONE,            0 }, 
   { ifds::Program,                 BFCBO::REQUIRED,        0 },
   { ifds::CalcCurrency,            BFCBO::REQUIRED,        0 },
   { ifds::EligibleFundBy,          BFCBO::REQUIRED,        0 },
   { ifds::FeeModelFundGroup,       BFCBO::NONE,            0 },
   { ifds::ModelAggregationMethod,  BFCBO::REQUIRED,        0 },
   { ifds::ScheduleFreqID,          BFCBO::NONE,            0 },
   { ifds::CalcRateType,            BFCBO::NONE,            0 },
   { ifds::ShrAcctFeeExist,         BFCBO::NONE,            0 },
   { ifds::FeeParmExist,            BFCBO::NONE,            0 },
   { ifds::FullMoneyOutApplicable,  BFCBO::NONE,            0 },
   { ifds::ReqMode,                 BFCBO::NONE,            0 },
   { ifds::AcctGrpType,             BFCBO::NONE,            0 },
   { ifds::AllowCopy,               BFCBO::CALCULATED_FIELD,0 },
   { ifds::SameDlrBrnRep,           BFCBO::CALCULATED_FIELD,0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

FeeModel::FeeModel( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, orgDEFF( NULL_STRING )
, _bIsCloned(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   addCrossEdit(ifds::CompoundDate, ifds::EffectiveDate);
   addCrossEdit(ifds::CompoundDate, ifds::StopDate);

}
//******************************************************************************************
FeeModel::~FeeModel()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//************************************************************************************
SEVERITY FeeModel::InitNew( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(long)" ) );

   FeeModelSetupList* pFeeModelSetupList = NULL;
   getWorkSession().getMgmtCo().getFeeModelSetupList(pFeeModelSetupList);

   if(pFeeModelSetupList)
   {
      DString dstrAvailableFeeModelTypes;
      pFeeModelSetupList->getAvailableFeeModelTypes(dstrAvailableFeeModelTypes);
      loadSubstitutionList(ifds::FeeModelType, idDataGroup, dstrAvailableFeeModelTypes);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
SEVERITY FeeModel::Init(const BFData& data)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&)" ) );

   FeeModelSetupList* pFeeModelSetupList = NULL;
   getWorkSession().getMgmtCo().getFeeModelSetupList(pFeeModelSetupList);

   if(pFeeModelSetupList)
   {
      DString dstrAvailableFeeModelTypes;
      pFeeModelSetupList->getAvailableFeeModelTypes(dstrAvailableFeeModelTypes);
      loadSubstitutionList(ifds::FeeModelType, BF::HOST, dstrAvailableFeeModelTypes);
   }

   attachDataObject(const_cast<BFData&>(data), false);  

   setFieldReadOnly(ifds::FeeModelCode,BF::HOST,true);
   setFieldReadOnly(ifds::FeeModelType,BF::HOST,true);
   setFieldReadOnly(ifds::EligibleFundBy, BF::HOST, true);

   orgDEFF = data.getElementValue( ifds::EffectiveDate );

   DString dstrShrAcctFeeExist;
   DString dstrFeeParmExist; 
   getField(ifds::ShrAcctFeeExist, dstrShrAcctFeeExist,  BF::HOST);
   getField(ifds::FeeParmExist,    dstrFeeParmExist,     BF::HOST);
   if(dstrShrAcctFeeExist == I_("Y") || dstrFeeParmExist == I_("Y"))
   {
      setFieldReadOnly(ifds::FeeModelCode,         BF::HOST,true);
      setFieldReadOnly(ifds::FeeModelType,         BF::HOST,true);
      setFieldReadOnly(ifds::HoldingCompCode,      BF::HOST,true);
      setFieldReadOnly(ifds::EligibleFundBy,       BF::HOST,true);
      setFieldReadOnly(ifds::FeeModelFundGroup,    BF::HOST,true);
      setFieldReadOnly(ifds::ModelAggregationMethod,BF::HOST,true);
      setFieldReadOnly(ifds::Program,              BF::HOST,true);
   }
   
   DString dstrFeeModelType;
   getField(ifds::FeeModelType, dstrFeeModelType,  BF::HOST);
   setFieldNoValidate(ifds::FeeModelTypeCode, dstrFeeModelType,  BF::HOST);

   setFieldReadOnly(ifds::ScheduleFreqID, BF::HOST, dstrFeeModelType != I_("MFR"));
   setFieldReadOnly(ifds::CalcRateType,   BF::HOST, dstrFeeModelType != I_("MFR"));
   
   UpdateFeeModelFundGroupSubst(BF::HOST);
   FeeModelTypeRelatedChanges(BF::HOST);

   DString dstrLastProcDate;
   getField(ifds::LastProcDate, dstrLastProcDate, BF::HOST, false);
   if(dstrLastProcDate != NULL_STRING && dstrLastProcDate != I_("12319999")) 
   {
      // if the Fee Model has already been processed make all the fields except stop date
      setCBOFieldsReadOnly(BF::HOST);
   }

   if(pFeeModelSetupList)
   {
      BFObjIter iter( *pFeeModelSetupList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

      iter.begin();

      while (!iter.end())
      {
         DString strFeeModelSetupModelType;
         iter.getObject()->getField(ifds::FeeModelType,strFeeModelSetupModelType,BF::HOST,false);

         if (dstrFeeModelType.strip().upperCase() == strFeeModelSetupModelType.strip().upperCase())
         {
            DString strAllowCopy;
            iter.getObject()->getField(ifds::AllowCopy,strAllowCopy,BF::HOST,false);
            strAllowCopy.strip().upperCase();
            setFieldNoValidate(ifds::AllowCopy, strAllowCopy, BF::HOST, false);
            break;
         }
         ++iter;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
SEVERITY FeeModel::InitNew(const BFData& data,const BFDataGroupId& idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&)" ) );

   _bIsCloned = true;
   DString newModelType, newModelCode, newModelDesc;
   data.getElementValue(ifds::FeeModelType,newModelType);
   data.getElementValue(ifds::FeeModelCode,newModelCode);
   data.getElementValue(ifds::FeeModelDesc,newModelDesc);
   newModelType.strip().upperCase();
   newModelCode.strip().upperCase();
   newModelDesc.strip();
   attachDataObject(const_cast<BFData&>(data), true);  

   orgDEFF = data.getElementValue( ifds::EffectiveDate );

   setFieldNoValidate(ifds::FeeModelType, newModelType,idDataGroup,false,true,false,false);
   setFieldUpdated(ifds::FeeModelType, idDataGroup, true);

   setFieldNoValidate(ifds::FeeModelCode, newModelCode,idDataGroup,false,true,false,false);
   setFieldUpdated(ifds::FeeModelCode, idDataGroup, true);

   setFieldNoValidate(ifds::FeeModelDesc, newModelDesc,idDataGroup,false,true,false,false);
   setFieldUpdated(ifds::FeeModelDesc, idDataGroup, true);

   DString dstrFeeModelType;
   getField(ifds::FeeModelType, dstrFeeModelType,  idDataGroup);
   setFieldNoValidate(ifds::FeeModelTypeCode, dstrFeeModelType,  idDataGroup);

   setFieldNoValidate(ifds::ReqMode, I_("CopyToGroup"),idDataGroup,false);
   setFieldUpdated(ifds::ReqMode, idDataGroup, true);

   setFieldRequired(ifds::FeeModelCode, idDataGroup, false);
   setFieldRequired(ifds::Program, idDataGroup, false);
   setFieldRequired(ifds::CalcCurrency, idDataGroup, false);
   setFieldRequired(ifds::ModelAggregationMethod, idDataGroup, false);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
void FeeModel::setCBOFieldsReadOnly(const BFDataGroupId& idDataGroup)
{
   setFieldReadOnly(ifds::FeeModelCode,         idDataGroup,true);
//   setFieldReadOnly(ifds::FeeModelDesc,         idDataGroup,true);
   setFieldReadOnly(ifds::FeeModelType,         idDataGroup,true);
   setFieldReadOnly(ifds::FeeModelTypeCode,     idDataGroup,true);
   setFieldReadOnly(ifds::EffectiveDate,        idDataGroup,true);
   setFieldReadOnly(ifds::CompoundDate,         idDataGroup,true);
   setFieldReadOnly(ifds::ApplFeeModelType,     idDataGroup,true);
   setFieldReadOnly(ifds::HoldingCompCode,      idDataGroup,true);
   setFieldReadOnly(ifds::Program,              idDataGroup,true);
//   setFieldReadOnly(ifds::CalcCurrency,         idDataGroup,true);
   setFieldReadOnly(ifds::EligibleFundBy,       idDataGroup,true);
   setFieldReadOnly(ifds::FeeModelFundGroup,    idDataGroup,true);
   setFieldReadOnly(ifds::ModelAggregationMethod, idDataGroup,true);
//   setFieldReadOnly(ifds::ScheduleFreqID,       idDataGroup,true);
//   setFieldReadOnly(ifds::CalcRateType,         idDataGroup,true);
   setFieldReadOnly(ifds::ShrAcctFeeExist,      idDataGroup,true);
   setFieldReadOnly(ifds::FeeParmExist,         idDataGroup,true);
}



//***********************************************************************************
SEVERITY FeeModel::doValidateField( const BFFieldId &idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if ( idField == ifds::CompoundDate )
   {
      validateEffectiveStopDate( idDataGroup );
   }
   else if ( idField == ifds::FeeModelCode )
   {
      validateOverlap( idDataGroup );
      validateFeeModelCode(idDataGroup);
   }
   else if ( idField == ifds::EffectiveDate )
   {
      if( !isNew() )
      {
         //int ret = DSTCommonFunctions::CompareDates(orgDEFF, strValue);
         //if (ret == DSTCommonFunctions::FIRST_EARLIER)
         //{
         //   ADDCONDITIONFROMFILE(CND::ERR_EFFECTIVE_DATE_FORWARD);
         //}
         DString dstrShrAcctDeff;
         DString dstrEffectiveDate;
         DString dstrOrigEffectiveDate;
         getField(ifds::ShrAcctDeff, dstrShrAcctDeff, idDataGroup);
         getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
         getFieldBeforeImage(ifds::EffectiveDate, dstrOrigEffectiveDate);
         if(dstrShrAcctDeff != I_("12319999") && 
            DSTCommonFunctions::CompareDates(dstrEffectiveDate, dstrShrAcctDeff) == DSTCommonFunctions::SECOND_EARLIER)
         {
		      getErrMsg( IFASTERR::FEE_MODEL_DEFF_NOT_APPLIC_TO_ACCT_ASSOC, 
                  CND::ERR_FEE_MODEL_DEFF_NOT_APPLIC_TO_ACCT_ASSOC, 
                  CND::WARN_FEE_MODEL_DEFF_NOT_APPLIC_TO_ACCT_ASSOC,
                  idDataGroup ); 
         }
      }
   }
   else if ( idField == ifds::StopDate )
   {
      if( !isNew() )
      {
         //int ret = DSTCommonFunctions::CompareDates(orgDEFF, strValue);
         //if (ret == DSTCommonFunctions::FIRST_EARLIER)
         //{
         //   ADDCONDITIONFROMFILE(CND::ERR_EFFECTIVE_DATE_FORWARD);
         //}
         DString dstrShrAcctDeff;
         DString dstrStopDate;
         DString dstrOrigStopDate;
         getField(ifds::ShrAcctDeff, dstrShrAcctDeff, idDataGroup);
         getField(ifds::StopDate, dstrStopDate, idDataGroup);
         getFieldBeforeImage(ifds::StopDate, dstrOrigStopDate);
         if(dstrShrAcctDeff != I_("12319999") && dstrShrAcctDeff != NULL_STRING && 
            DSTCommonFunctions::CompareDates(dstrStopDate, dstrOrigStopDate) == DSTCommonFunctions::FIRST_EARLIER)
         {
		      getErrMsg( IFASTERR::FEE_MODEL_DEFF_NOT_APPLIC_TO_ACCT_ASSOC, 
                  CND::ERR_FEE_MODEL_STOP_DATE_NOT_APPLIC_TO_ACCT_ASSOC, 
                  CND::WARN_FEE_MODEL_STOP_DATE_NOT_APPLIC_TO_ACCT_ASSOC,
                  idDataGroup ); 
         }

         DString dstrFeeModelType, dstrLastProcDate;
         getField(ifds::FeeModelType, dstrFeeModelType, idDataGroup);
         getField(ifds::LastProcDate, dstrLastProcDate, idDataGroup, false);

         if (dstrFeeModelType == FEE_MODEL_TYPE_ADVISOR_FEE && !dstrLastProcDate.empty() && dstrLastProcDate != NULL_DATE &&
             DSTCommonFunctions::CompareDates(dstrStopDate, dstrLastProcDate) == DSTCommonFunctions::FIRST_EARLIER)
         {
             getErrMsg( IFASTERR::FEE_MODEL_CANNOT_BE_STOPPED_BEFORE_LAST_PROCESS_DATE, 
                  CND::ERR_FEE_MODEL_CANNOT_BE_STOPPED_BEFORE_LAST_PROCESS_DATE, 
                  CND::WARN_FEE_MODEL_CANNOT_BE_STOPPED_BEFORE_LAST_PROCESS_DATE,
                  idDataGroup ); 
         }
      }
   }
   else if (idField == ifds::HoldingCompCode)
   {
      validateHoldingCompCodeMandatory(idDataGroup);
      validateHoldingCompCode(idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************
SEVERITY FeeModel::validateHoldingCompCode( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateOverlap" ) );
   DString dstrHoldingCompCode;
   getField(ifds::HoldingCompCode, dstrHoldingCompCode, idDataGroup);

   if(dstrHoldingCompCode != I_(""))
   {
      bool isFromHoldingComp = true;
      FeeModelList *pFeeModelList = dynamic_cast<FeeModelList*>(getParent());
      if(pFeeModelList)
         isFromHoldingComp = I_("") != pFeeModelList->getFromHoldingCompanyCode();

      HoldingCompList* pHoldingCompList = NULL;
      getWorkSession().getHoldingCompList(pHoldingCompList, idDataGroup, dstrHoldingCompCode, I_(""), I_("Y"), I_("12319999"), !isFromHoldingComp, true );
      if(pHoldingCompList)
      {
         HoldingComp* pHoldingComp = NULL;
         pHoldingCompList->getHoldingComp(dstrHoldingCompCode, pHoldingComp, idDataGroup);
         if(!pHoldingComp)
         {
            ADDCONDITIONFROMFILE(CND::ERR_INVALID_HOLDING_COMP_CODE);
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
};

//***********************************************************************************
SEVERITY FeeModel::validateHoldingCompCodeMandatory( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateOverlap" ) );
   DString dstrHoldingCompCode;
   DString dstrFeeModelType;
   getField(ifds::HoldingCompCode, dstrHoldingCompCode, idDataGroup);
   getField(ifds::FeeModelType, dstrFeeModelType, idDataGroup);

   BFAbstractCBO* pFeeModelSetup = NULL;
   getFeeModelSetup(idDataGroup, pFeeModelSetup);
   DString dstrHoldingEntityAppl;
   if(pFeeModelSetup)
   {
      pFeeModelSetup->getField(ifds::HoldingEntityAppl, dstrHoldingEntityAppl, idDataGroup);

      if(dstrHoldingEntityAppl == Y && dstrFeeModelType.stripAll() == I_("MF") && //Hard coding for MF, not so nice, would be nice to have it in FeeModelSetup
         dstrHoldingCompCode.stripAll() == I_(""))
      {
         ADDCONDITIONFROMFILE(CND::ERR_HOLDING_COMP_CODE_IS_REQUIRED);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY()); 
};

//******************************************************************************************
void FeeModel::setFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly) 
{
}

//*****************************************************************************************
SEVERITY FeeModel::doApplyRelatedChanges( const BFFieldId &idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (idField == ifds::FeeModelType)
   {
      DString dstrFeeModelType;
      getField(ifds::FeeModelType, dstrFeeModelType,  idDataGroup);

      setFieldNoValidate(ifds::Program, I_(""), idDataGroup, false, true);
      setFieldNoValidate(ifds::EligibleFundBy, I_(""), idDataGroup, false, true);
      setFieldNoValidate(ifds::FeeModelFundGroup, I_(""), idDataGroup, false, true);
      setFieldNoValidate(ifds::ModelAggregationMethod, I_(""), idDataGroup, false, true);

      setFieldReadOnly(ifds::ScheduleFreqID, idDataGroup, dstrFeeModelType != I_("MFR"));
      setFieldReadOnly(ifds::CalcRateType,   idDataGroup, dstrFeeModelType != I_("MFR"));

      setFieldRequired(ifds::ScheduleFreqID, idDataGroup, dstrFeeModelType == I_("MFR"));
      setFieldRequired(ifds::CalcRateType,   idDataGroup, dstrFeeModelType == I_("MFR"));

      if(dstrFeeModelType != I_("MFR"))
      {
         setFieldNoValidate(ifds::ScheduleFreqID, I_(""), idDataGroup, false, true);
         setFieldValid(ifds::ScheduleFreqID, idDataGroup, true);
         setFieldNoValidate(ifds::CalcRateType,   I_(""), idDataGroup, false, true);
         setFieldValid(ifds::CalcRateType, idDataGroup, true);
      }
 
      setFieldValid(ifds::ScheduleFreqID, idDataGroup, false);
      setFieldValid(ifds::CalcRateType,   idDataGroup, false);

      setFieldNoValidate(ifds::FeeModelTypeCode, dstrFeeModelType,  idDataGroup);
   
      FeeModelTypeRelatedChanges(idDataGroup);
      
      setFieldValid(ifds::HoldingCompCode, idDataGroup, false);

      if (isNew() && !dstrFeeModelType.empty())
      {
          bool bReadOnly = false;
          DString dstrAutoGenFeeModelCode, dstrAutoGenOverride;
          BFAbstractCBO *pFeeModelSetup = NULL;

          getFeeModelSetup(idDataGroup, pFeeModelSetup);
          getWorkSession ().getOption (ifds::AutoGenFeeModelCode, dstrAutoGenFeeModelCode, BF::HOST, false);   

          if (pFeeModelSetup)
          {
              pFeeModelSetup->getField(ifds::AutoGenOverride, dstrAutoGenOverride, idDataGroup, false);
          }

          bReadOnly = dstrAutoGenFeeModelCode == YES || dstrAutoGenOverride == YES;

          if (bReadOnly && !_bIsCloned)
          {
              setFieldNoValidate(ifds::FeeModelCode, NULL_STRING, idDataGroup, false);
          }

          setFieldRequired(ifds::FeeModelCode, idDataGroup, !bReadOnly);
          setFieldReadOnly(ifds::FeeModelCode, idDataGroup, bReadOnly);

          //0 = Checked, 1 = Unchecked
          setFieldNoValidate(ifds::FullMoneyOutApplicable, dstrFeeModelType == FEE_MODEL_TYPE_ADVISOR_FEE ? I_("0"):I_("1"), idDataGroup, false, true, true, true);
      }

      if (!dstrFeeModelType.empty()) {
         FeeModelSetupList* pFeeModelSetupList = NULL;
         getWorkSession().getMgmtCo().getFeeModelSetupList(pFeeModelSetupList);
         if(pFeeModelSetupList)
         {
            BFObjIter iter( *pFeeModelSetupList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

            iter.begin();

            while (!iter.end())
            {
               DString strFeeModelSetupModelType;
               iter.getObject()->getField(ifds::FeeModelType,strFeeModelSetupModelType,BF::HOST,false);

               if (dstrFeeModelType.strip().upperCase() == strFeeModelSetupModelType.strip().upperCase())
               {
                  DString strAllowCopy;
                  iter.getObject()->getField(ifds::AllowCopy,strAllowCopy,BF::HOST,false);
                  strAllowCopy.strip().upperCase();
                  setFieldNoValidate(ifds::AllowCopy, strAllowCopy, idDataGroup, false);
                  break;
               }
               ++iter;
            }
         }
      }
   }
   else if (idField == ifds::Program)
   {
      DString dstrProgram;
      getField(ifds::Program, dstrProgram,  idDataGroup);
      if(dstrProgram == I_("AP") || dstrProgram == I_("PP"))
      {
         setFieldNoValidate (ifds::EligibleFundBy, I_("FGP"), idDataGroup, false );
         setFieldReadOnly(ifds::EligibleFundBy, idDataGroup, true);
         setFieldReadOnly(ifds::FeeModelFundGroup, idDataGroup, false);

         DString newSubst = removeItemFromAllSubtList (ifds::ModelAggregationMethod, I_("TGA"), BF::HOST);
         newSubst = removeItemFromSubtList (newSubst, I_("FLK"));
         setFieldAllSubstituteValues(ifds::ModelAggregationMethod, idDataGroup, newSubst);

         if(dstrProgram == I_("AP"))
         {
            setFieldNoValidate (ifds::ModelAggregationMethod, I_("ALL"), idDataGroup, false );
         }
         else 
         {
            setFieldNoValidate (ifds::ModelAggregationMethod, I_("IND"), idDataGroup, false );
         }
         setFieldReadOnly(ifds::ModelAggregationMethod, idDataGroup, false);
      }
      else if(dstrProgram == I_("FA"))
      {
         DString newSubst = removeItemFromAllSubtList (ifds::ModelAggregationMethod, I_("TGA"), BF::HOST);
         setFieldAllSubstituteValues(ifds::ModelAggregationMethod, idDataGroup, newSubst);
         setFieldNoValidate (ifds::ModelAggregationMethod, I_("FLK"), idDataGroup, false );
         setFieldReadOnly(ifds::ModelAggregationMethod, idDataGroup, false);

         setFieldNoValidate (ifds::EligibleFundBy, I_("IND"), idDataGroup, false );
         setFieldReadOnly(ifds::EligibleFundBy, idDataGroup, true);
         setFieldRequired(ifds::FeeModelFundGroup, idDataGroup, false);
         setFieldNoValidate(ifds::FeeModelFundGroup, I_(""), idDataGroup);
         setFieldReadOnly(ifds::FeeModelFundGroup, idDataGroup, true);
      }
      else if(dstrProgram == I_("TGA"))
      {
         DString newSubst = removeItemFromAllSubtList (ifds::ModelAggregationMethod, I_("ALL"), BF::HOST);
         newSubst = removeItemFromSubtList (newSubst, I_("IND"));
         newSubst = removeItemFromSubtList (newSubst, I_("FLK"));
         setFieldAllSubstituteValues(ifds::ModelAggregationMethod, idDataGroup, newSubst);
         setFieldNoValidate (ifds::ModelAggregationMethod, I_("TGA"), idDataGroup, false );
         setFieldReadOnly(ifds::ModelAggregationMethod, idDataGroup, true);

         setFieldNoValidate (ifds::EligibleFundBy, I_("IND"), idDataGroup, false );
         setFieldReadOnly(ifds::EligibleFundBy, idDataGroup, true);
         setFieldRequired(ifds::FeeModelFundGroup, idDataGroup, false);
         setFieldNoValidate(ifds::FeeModelFundGroup, I_(""), idDataGroup);
         setFieldReadOnly(ifds::FeeModelFundGroup, idDataGroup, true);
      }
      else
      {
         setFieldNoValidate (ifds::EligibleFundBy, I_("IND"), idDataGroup, false );
         setFieldReadOnly(ifds::EligibleFundBy, idDataGroup, true);
         setFieldReadOnly(ifds::FeeModelFundGroup, idDataGroup, true);
      }
   }
   else if (idField == ifds::EligibleFundBy)
   {
      UpdateFeeModelFundGroupSubst(idDataGroup);
   }
   else if (idField == ifds::HoldingCompCode)
   {
      DString dstrHoldingCompCode;
      getField(ifds::HoldingCompCode, dstrHoldingCompCode, idDataGroup);
      UpdateHoldingCompRelated(dstrHoldingCompCode, idDataGroup);
   }


   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY FeeModel::UpdateHoldingCompRelated(const DString& dstrHoldingCompCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "UpdateHoldingCompRelated" ) );

   bool isFromHoldingComp = true;
   FeeModelList *pFeeModelList = dynamic_cast<FeeModelList*>(getParent());
   if(pFeeModelList)
      isFromHoldingComp = I_("") != pFeeModelList->getFromHoldingCompanyCode();
 
   HoldingCompList* pHoldingCompList = NULL;
   getWorkSession().getHoldingCompList(pHoldingCompList, idDataGroup, dstrHoldingCompCode, I_(""), I_("Y"), I_("1231999"), !isFromHoldingComp, true);

   if(dstrHoldingCompCode != I_("") && pHoldingCompList)
   {
      HoldingComp* pHoldingComp = NULL;
      pHoldingCompList->getHoldingComp(dstrHoldingCompCode, pHoldingComp, idDataGroup);
      
//      setFieldReadOnly(ifds::HoldingCompCode, idDataGroup, true);

      DString dstrFeeModelType;
      DString dstrProgram;
      DString dstrHoldingCompAggregationMethod;
      DString dstrModelAggregationMethod;
      if(pHoldingComp)
      {
         pHoldingComp->getField(ifds::CompanyUsage, dstrFeeModelType, idDataGroup, false);
         setFieldNoValidate(ifds::FeeModelType, dstrFeeModelType, idDataGroup);

         pHoldingComp->getField(ifds::AggregationMethod, dstrProgram, idDataGroup, false);
         setFieldNoValidate(ifds::Program, dstrProgram, idDataGroup);
         setFieldReadOnly(ifds::Program, idDataGroup, true);

         pHoldingComp->getField(ifds::AggregationMethod, dstrHoldingCompAggregationMethod, idDataGroup, false);
         if(dstrHoldingCompAggregationMethod == I_("FA"))
         {
            DString newSubst = removeItemFromAllSubtList (ifds::ModelAggregationMethod, I_("TGA"), idDataGroup);
            setFieldAllSubstituteValues(ifds::ModelAggregationMethod, idDataGroup, newSubst);
         }

         setFieldReadOnly(ifds::FeeModelType, idDataGroup, true);
      }
   }
   else
   {
      DString newSubst = removeItemFromAllSubtList (ifds::Program, I_("TGA"), idDataGroup);
      newSubst = removeItemFromSubtList (newSubst, I_("FA"));
      setFieldAllSubstituteValues(ifds::Program, idDataGroup, newSubst);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY FeeModel::UpdateFeeModelFundGroupSubst(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "UpdateFeeModelFundGroupSubst" ) );

   DString dstrEligibleFundBy;
   getField(ifds::EligibleFundBy, dstrEligibleFundBy,  idDataGroup);

   if(dstrEligibleFundBy == I_("FGP"))
   {
      setFieldReadOnly(ifds::FeeModelFundGroup, idDataGroup, false);

      FeeModelSetupList* pFeeModelSetupList = NULL;
      getWorkSession().getMgmtCo().getFeeModelSetupList(pFeeModelSetupList);
      if(pFeeModelSetupList)
      {
         DString dstrFeeModelType;
         getField(ifds::FeeModelType, dstrFeeModelType, idDataGroup);
         BFAbstractCBO* pFeeModelSetup = NULL;
         pFeeModelSetupList->getFeeModelSetup(pFeeModelSetup, dstrFeeModelType);

         if(pFeeModelSetup)
         {
            DString dstrFundGroupType;
            pFeeModelSetup->getField(ifds::FundGroupType, dstrFundGroupType, idDataGroup, false);

            FundCommGroupList* pFundCommGroupList = NULL;

            if(dstrFundGroupType.strip().upperCase() != NULL_STRING && 
               getMgmtCo().getFundCommGroupList(dstrFundGroupType, pFundCommGroupList ) <= WARNING )
            {
               DString dstrSubList;
               pFundCommGroupList->getCommGroupSubstitute(dstrSubList, false);
               setFieldAllSubstituteValues(ifds::FeeModelFundGroup, idDataGroup, dstrSubList);
               setFieldRequired(ifds::FeeModelFundGroup, idDataGroup, true);
            }
         } 
      }
   }
   else
   {
      setFieldNoValidate(ifds::FeeModelFundGroup, I_(""), idDataGroup);
      setFieldUpdated(ifds::FeeModelFundGroup, idDataGroup, false);
      setFieldReadOnly(ifds::FeeModelFundGroup, idDataGroup, true);
      setFieldAllSubstituteValues(ifds::FeeModelFundGroup, idDataGroup, I_(""));
      setFieldRequired(ifds::FeeModelFundGroup, idDataGroup, false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************
SEVERITY FeeModel::getFeeModelSetup(const BFDataGroupId& idDataGroup, BFAbstractCBO*& pFeeModelSetup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "StatusRelatedChanges" ) );

   FeeModelSetupList* pFeeModelSetupList = NULL;
   getWorkSession().getMgmtCo().getFeeModelSetupList(pFeeModelSetupList);
   if(pFeeModelSetupList)
   {
      DString dstrFeeModelType;
      getField(ifds::FeeModelType, dstrFeeModelType, idDataGroup);
//      BFAbstractCBO* pFeeModelSetup = NULL;
      pFeeModelSetupList->getFeeModelSetup(pFeeModelSetup, dstrFeeModelType);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY FeeModel::FeeModelTypeRelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "StatusRelatedChanges" ) );

   DString str;

   FeeModelSetupList* pFeeModelSetupList = NULL;
   getWorkSession().getMgmtCo().getFeeModelSetupList(pFeeModelSetupList);
   if(pFeeModelSetupList)
   {
      DString dstrAvailableFeeModelTypes;
      pFeeModelSetupList->getAvailableFeeModelTypes(dstrAvailableFeeModelTypes);
      loadSubstitutionList(ifds::FeeModelType, idDataGroup, dstrAvailableFeeModelTypes);
   }

   BFAbstractCBO* pFeeModelSetup = NULL;
   getFeeModelSetup(idDataGroup, pFeeModelSetup);
   
   DString dstrFeeModelType;
   getField(ifds::FeeModelType, dstrFeeModelType, idDataGroup);
   pFeeModelSetupList->getFeeModelSetup(pFeeModelSetup, dstrFeeModelType);

   if(pFeeModelSetup)
   {
      DString dstrFundGroupType;
      DString dstrFundGrpTypeList;
      DString dstrAggregationMethodList;
      DString dstrCalcRateTypeList;
      DString dstrFeeModelOptionList;
      DString dstrSchedSetupFreqAppl;

      DString dstrHoldingEntityAppl;
      DString dstrCalcCurrencyAppl;


      pFeeModelSetup->getField(ifds::FundGroupType,         dstrFundGroupType,         idDataGroup, false);
      pFeeModelSetup->getField(ifds::FundGrpTypeList,       dstrFundGrpTypeList,       idDataGroup, false);
      pFeeModelSetup->getField(ifds::AggregationMethodList, dstrAggregationMethodList, idDataGroup, false);
      pFeeModelSetup->getField(ifds::CalcRateTypeList,      dstrCalcRateTypeList,      idDataGroup, false);
      pFeeModelSetup->getField(ifds::FeeModelOptionList,    dstrFeeModelOptionList,    idDataGroup, false);
      pFeeModelSetup->getField(ifds::SchedSetupFreqAppl,    dstrSchedSetupFreqAppl,    idDataGroup, false);
      pFeeModelSetup->getField(ifds::HoldingEntityAppl,     dstrHoldingEntityAppl,     idDataGroup, false);
      pFeeModelSetup->getField(ifds::CalcCurrencyAppl,      dstrCalcCurrencyAppl,      idDataGroup, false);

      resetSubstBasedOnFeeModelType(ifds::CalcRateType, dstrCalcRateTypeList.stripAll(), idDataGroup);
//      resetSubstBasedOnFeeModelType(ifds::CalcCurrency, dstrCalcCurrencyAppl.stripAll(), idDataGroup);
      resetSubstBasedOnFeeModelType(ifds::Program,      dstrFeeModelOptionList.stripAll(), idDataGroup);
      resetSubstBasedOnFeeModelType(ifds::ModelAggregationMethod, dstrAggregationMethodList.stripAll(), idDataGroup);
      resetSubstBasedOnFeeModelType(ifds::EligibleFundBy,dstrFundGrpTypeList.stripAll(), idDataGroup);
      
      resetSubstBasedOnFeeModelType(ifds::CalcCurrency, dstrCalcCurrencyAppl.stripAll() == I_("N") ? 
                  NULL_STRING : dstrCalcCurrencyAppl, idDataGroup, true);
      setFieldReadOnly(ifds::EligibleFundBy, BF::HOST, true);

      resetSubstBasedOnFeeModelType(ifds::ScheduleFreqID, dstrSchedSetupFreqAppl.stripAll() == I_("N") ? 
                  NULL_STRING : dstrSchedSetupFreqAppl, idDataGroup, true);

      if(dstrHoldingEntityAppl != I_("Y"))
//      {
//         FeeModelList *pFeeModelList = dynamic_cast<FeeModelList*>(getParent());
//         if(pFeeModelList)
//         {
//            DString dstrHoldingCompCode = pFeeModelList->getFromHoldingCompanyCode();
//            setFieldReadOnly(ifds::HoldingCompCode, idDataGroup, dstrHoldingCompCode != NULL_STRING);
////            setFieldNoValidate(ifds::HoldingCompCode, dstrHoldingCompCode , idDataGroup);
//         }
//      }
//      else
      {
         setFieldReadOnly(ifds::HoldingCompCode, idDataGroup, true);
         setFieldNoValidate(ifds::HoldingCompCode, NULL_STRING, idDataGroup, false, true, true, false);
      }

      
      
/*
      loadSubstitutionList(ifds::EligibleFundBy,         idDataGroup, dstrFundGrpTypeList);


      if(dstrAggregationMethodList.strip() != NULL_STRING)
      {
         loadSubstitutionList(ifds::ModelAggregationMethod, idDataGroup, dstrAggregationMethodList);
      }
      else
      {
         BFCBO::getFieldProperties(ifds::ModelAggregationMethod, idDataGroup)->setSubstituteValues(NULL);
         setFieldAllSubstituteValues(ifds::ModelAggregationMethod, idDataGroup, NULL_STRING);
         setFieldRequired(ifds::ModelAggregationMethod, idDataGroup, false);
         setFieldNoValidate(ifds::ModelAggregationMethod, NULL_STRING, idDataGroup, false);
      }



      if(dstrFeeModelOptionList.stripAll() != NULL_STRING)
      {
         DString strAllSubstList;
         BFProperties * pBFProperties = getFieldProperties(ifds::Program, idDataGroup);
         pBFProperties->reinitAllSubstValues();
         loadSubstitutionList(ifds::Program, idDataGroup, dstrFeeModelOptionList);
         notifyObservers(ifds::Program, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
         setFieldRequired(ifds::Program, idDataGroup, true); 
      }
      else
      {
         BFProperties * pBFProperties = getFieldProperties(ifds::Program, idDataGroup);
         pBFProperties->setAllSubstituteValues(NULL_STRING);
         pBFProperties->setSubstituteValues(NULL);
         notifyObservers(ifds::Program, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
         setFieldRequired(ifds::Program, idDataGroup, false); 
      }


      if(dstrCalcCurrencyAppl == Y)
      {
         DString strAllSubstList;
         BFProperties * pBFProperties = getFieldProperties(ifds::CalcCurrency, idDataGroup);
         pBFProperties->reinitAllSubstValues();
         notifyObservers(ifds::CalcCurrency, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
         setFieldRequired(ifds::CalcCurrency, idDataGroup, true); 
      }
      else
      {
         BFProperties * pBFProperties = getFieldProperties(ifds::CalcCurrency, idDataGroup);
         pBFProperties->setAllSubstituteValues(NULL_STRING);
         notifyObservers(ifds::Program, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
         setFieldRequired(ifds::CalcCurrency, idDataGroup, false); 
      }


      if(dstrCalcRateTypeList.stripAll() != NULL_STRING)
      {
         DString strAllSubstList;
         BFProperties * pBFProperties = getFieldProperties(ifds::CalcRateType, idDataGroup);
         pBFProperties->reinitAllSubstValues();
         loadSubstitutionList(ifds::CalcRateType, idDataGroup, dstrCalcRateTypeList);
         notifyObservers(ifds::CalcRateType, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
         setFieldRequired(ifds::CalcRateType, idDataGroup, true); 
      }
      else
      {
         BFProperties * pBFProperties = getFieldProperties(ifds::CalcRateType, idDataGroup);
         pBFProperties->setAllSubstituteValues(NULL_STRING);
         pBFProperties->setSubstituteValues(NULL);
         notifyObservers(ifds::CalcRateType, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
         setFieldRequired(ifds::CalcRateType, idDataGroup, false); 
         setFieldNoValidate(ifds::CalcRateType, I_(""), idDataGroup, false); 
      }
*/     
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
void FeeModel::resetSubstBasedOnFeeModelType(const BFFieldId& idField, const DString& dstrSubstValues, const BFDataGroupId& idDataGroup, bool showAll)
{
   BFProperties * pBFProperties = getFieldProperties(idField, idDataGroup);
   
   if(dstrSubstValues != NULL_STRING)
   {
      pBFProperties->reinitAllSubstValues();
      if(!showAll)
      {
         loadSubstitutionList(idField, idDataGroup, dstrSubstValues);
      }
   }
   else
   {
      pBFProperties->setAllSubstituteValues(NULL_STRING);
      pBFProperties->setSubstituteValues(NULL);
   }
   
   setFieldRequired(idField, idDataGroup, dstrSubstValues != NULL_STRING); 
   setFieldReadOnly(idField, idDataGroup, dstrSubstValues == NULL_STRING); 
}

//*****************************************************************************************
SEVERITY FeeModel::validateFeeModelCode( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeModelCode" ) );

   DString dstrFeeModelCode;
   getField(ifds::FeeModelCode, dstrFeeModelCode, idDataGroup, false);
   FeeModelList lFeeModelList(*this);
   if(dstrFeeModelCode.stripAll() != NULL_STRING)
   {
      lFeeModelList.init(idDataGroup, I_("N"), NULL_STRING, I_(""), I_(""), dstrFeeModelCode);
   //   if(isNew() && lHoldingCompList.
      DString dstrRepeatCount;
      
      lFeeModelList.getField(ifds::RepeatCount, dstrRepeatCount, idDataGroup, false);
      dstrRepeatCount.stripAll();
      if(dstrRepeatCount != I_("") && dstrRepeatCount != I_("0"))
      {
         ADDCONDITIONFROMFILE( CND::ERR_FEE_MODEL_ALREADY_IN_USE );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
void FeeModel::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString stopDate, dstrCurrBusDate, dstrAutoGenFeeModelCode, dstrApplFeeModelType;

   getWorkSession ().getOption (ifds::AutoGenFeeModelCode, dstrAutoGenFeeModelCode, BF::HOST, false);   
//   getWorkSession ().getOption (ifds::ApplFeeModelType, dstrApplFeeModelType, BF::HOST, false ); 

   FeeModelSetupList* pFeeModelSetupList = NULL;
   getWorkSession().getMgmtCo().getFeeModelSetupList(pFeeModelSetupList);
   if(pFeeModelSetupList)
   {
      DString dstrAvailableFeeModelTypes;
      pFeeModelSetupList->getAvailableFeeModelTypes(dstrApplFeeModelType);
   }
   
   setFieldAllSubstituteValues(ifds::FeeModelFundGroup, idDataGroup, I_(""));

   bool bAutoGenFeeModelCode = dstrAutoGenFeeModelCode.strip().upperCase() == I_("Y");
   setFieldRequired (ifds::FeeModelCode, idDataGroup, !bAutoGenFeeModelCode);
   setFieldReadOnly (ifds::FeeModelCode, idDataGroup, bAutoGenFeeModelCode);
   setFieldRequired (ifds::FeeModelDesc, idDataGroup, true );
   setFieldRequired (ifds::EffectiveDate, idDataGroup, true );
   setFieldRequired (ifds::StopDate, idDataGroup, true );

   std::vector<DString> vModelType;
   DSTCommonFunctions::tokenizeString( dstrApplFeeModelType, vModelType ); 

//   loadSubstitutionList(ifds::FeeModelType, idDataGroup, dstrApplFeeModelType);

   if (vModelType.size() > 1)
   {
      setFieldNoValidate (ifds::FeeModelType, I_(""), idDataGroup, false );
      setFieldReadOnly (ifds::FeeModelType, idDataGroup, false);
      setFieldRequired (ifds::StopDate, idDataGroup, true );
   }
   else if( vModelType.size() == 1)
   {
      DString strDefaultFeeModelType = vModelType.at(0);
      setFieldNoValidate (ifds::FeeModelType, strDefaultFeeModelType, idDataGroup, false );
      setFieldReadOnly (ifds::FeeModelType, idDataGroup, true);
   }
   else // vModelType.size() == 0
   {
      setFieldNoValidate (ifds::FeeModelType, I_(""), idDataGroup, false );
      setFieldReadOnly (ifds::FeeModelType, idDataGroup, true);
      setFieldRequired (ifds::FeeModelType, idDataGroup, false );
   }

   setFieldReadOnly (ifds::FeeModelCode, idDataGroup, bAutoGenFeeModelCode);
   setFieldRequired (ifds::FeeModelCode, idDataGroup, !bAutoGenFeeModelCode);

   getWorkSession().getDateInHostFormat (stopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false );
   getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false);

 
   FeeModelList *pFeeModelList = dynamic_cast<FeeModelList*>(getParent());
   if(pFeeModelList)
   {
      DString dstrHoldingCompCode = pFeeModelList->getFromHoldingCompanyCode();

//      UpdateHoldingCompRelated(dstrHoldingCompCode, idDataGroup); 
      if(dstrHoldingCompCode != I_(""))
      {
         setFieldNoValidate(ifds::HoldingCompCode, dstrHoldingCompCode, idDataGroup, true);
         setFieldReadOnly(ifds::HoldingCompCode, idDataGroup, true);
      }
      
      //HoldingCompList* pHoldingCompList = NULL;
      //getWorkSession().getHoldingCompList(pHoldingCompList, idDataGroup, dstrHoldingCompCode, 
      //   I_(""), I_("Y"), I_("Y"), false);
 
      //if(dstrHoldingCompCode != I_("") && pHoldingCompList)
      //{
      //   HoldingComp* pHoldingComp = NULL;
      //   pHoldingCompList->getHoldingComp(dstrHoldingCompCode, pHoldingComp, idDataGroup);
      //   
      //   setField(ifds::HoldingCompCode, dstrHoldingCompCode, idDataGroup, true);
      //   setFieldReadOnly(ifds::HoldingCompCode, idDataGroup, true);

      //   DString dstrFeeModelType;
      //   DString dstrProgram;
      //   DString dstrHoldingCompAggregationMethod;
      //   DString dstrModelAggregationMethod;
      //   if(pHoldingComp)
      //   {
      //      pHoldingComp->getField(ifds::CompanyUsage, dstrFeeModelType, idDataGroup, false);
      //      setFieldNoValidate(ifds::FeeModelType, dstrFeeModelType, idDataGroup);

      //      pHoldingComp->getField(ifds::AggregationMethod, dstrProgram, idDataGroup, false);
      //      setFieldNoValidate(ifds::Program, dstrProgram, idDataGroup);
      //      setFieldReadOnly(ifds::Program, idDataGroup, true);

      //      pHoldingComp->getField(ifds::AggregationMethod, dstrHoldingCompAggregationMethod, idDataGroup, false);
      //      if(dstrHoldingCompAggregationMethod == I_("FA"))
      //      {
      //         DString newSubst = removeItemFromAllSubtList (ifds::ModelAggregationMethod, I_("TGA"), idDataGroup);
      //         setFieldAllSubstituteValues(ifds::ModelAggregationMethod, idDataGroup, newSubst);
      //      }

      //      setFieldReadOnly(ifds::FeeModelType, idDataGroup, true);
      //   }
      //}
      //else
      //{
      //   DString newSubst = removeItemFromAllSubtList (ifds::Program, I_("TGA"), idDataGroup);
      //   newSubst = removeItemFromSubtList (newSubst, I_("FA"));
      //   setFieldAllSubstituteValues(ifds::Program, idDataGroup, newSubst);
      //}
   }
}

//*****************************************************************************************
SEVERITY FeeModel::validateOverlap( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateOverlap" ) );

   FeeModelList *pFeeModelList = dynamic_cast<FeeModelList*>(getParent());

   pFeeModelList->validateOverlapping(this, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY FeeModel::validateEffectiveStopDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEffectiveStopDate" ) );

   DString dstrEffectDate, dstrStopDate;
   getField(ifds::EffectiveDate,dstrEffectDate,idDataGroup,false);
   getField(ifds::StopDate,dstrStopDate,idDataGroup,false);

   if( DSTCommonFunctions::CompareDates( dstrStopDate, dstrEffectDate ) == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_EFF_DATE_LATE_THAN_STOP_DATE );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void FeeModel::setFromHoldingCompany(const DString& dstrHoldingCompCode, const BFDataGroupId& idDataGroup )
{
   m_dstrFromHoldingComp = dstrHoldingCompCode;
   
   setFieldReadOnly(ifds::FeeModelType, idDataGroup, true);
   setFieldReadOnly(ifds::Program, idDataGroup, true);
   setFieldReadOnly(ifds::ModelAggregationMethod, idDataGroup, true);
   setFieldReadOnly(ifds::HoldingCompCode, idDataGroup, true);
}

//******************************************************************************
SEVERITY FeeModel::getFeeModelCopyToGroupList(FeeModelCopyToGroupList *&pFeeModelCopyToGroupList,
                                              const DString feeModel,
                                              const BFDataGroupId& idDataGroup,
                                              bool bCreated)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeModelCopyToGroupList" ) );

   DString dstrKey = I_("FeeModelCopyToGroupList");

   pFeeModelCopyToGroupList = dynamic_cast <FeeModelCopyToGroupList*>(getObject(dstrKey, idDataGroup));

   if( !pFeeModelCopyToGroupList && bCreated)
   {
      pFeeModelCopyToGroupList = new FeeModelCopyToGroupList( *this );

      pFeeModelCopyToGroupList->init();

      if( pFeeModelCopyToGroupList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pFeeModelCopyToGroupList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
         }
         else
         {
            delete pFeeModelCopyToGroupList;
            pFeeModelCopyToGroupList = NULL;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FeeModel::removeFeeModelCopyToGroupList(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "removeFeeModelCopyToGroupList" ) );

   DString dstrKey = I_("FeeModelCopyToGroupList");
   BFObjIter bfIter (*this, idDataGroup);

   bfIter.begin();
   bfIter.positionByKey(dstrKey);
   bfIter.removeObjectFromMap();

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeModel.cpp-arc  $
// 
//    Rev 1.6   Dec 22 2004 10:14:14   Fengyong
// PTS10036889 - Effective can be changed backward
// 
//    Rev 1.5   Dec 21 2004 17:26:58   hernando
// PTS10036889 - Removed read-only from Effective Date.
// 
//    Rev 1.4   Nov 14 2004 14:40:04   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Sep 01 2004 15:21:36   FENGYONG
// Add condition for PET1117
// 
//    Rev 1.2   Aug 31 2004 17:30:58   FENGYONG
// change Field names
// 
//    Rev 1.1   Aug 10 2004 11:24:00   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.0   Aug 09 2004 10:06:06   FENGYONG
// Initial Revision
// 
// 
*/
