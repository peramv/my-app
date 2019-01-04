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
// ^FILE   : HoldingComp.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : HoldingComp
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "holdingcomp.hpp"
#include "holdingcomplist.hpp"

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "worksessionentitylist.hpp"
#include "entity.hpp"

#include <ifastdataimpl\dse_dstc0448_vw.hpp>
#include <ifastdataimpl\dse_dstc0448_req.hpp>
#include <ifastdataimpl\dse_dstc0331_reqrepeat_record.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME                  = I_( "HoldingComp" );
   const I_CHAR * const YES                        = I_("Y");
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId LastName;
   extern CLASS_IMPORT const BFTextFieldId LanguageCode;
}

namespace CND
{  // Conditions used
   extern const long ERR_EFF_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_EFFECTIVE_DATE_FORWARD;
   extern const long ERR_CBO_HOLDING_ENTITY_CODE_ALREADY_EXISTS;
   extern const long WARN_HOLD_ENT_STOP_DATE_APPIES_TO_THE_TREE;
   extern const long WARN_HOLD_ENT_EFFECTIVE_DATE_APPIES_TO_THE_TREE;
}

//  Field DD Id,                    State Flags,         Group Flags       

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   { ifds::EntityId,           BFCBO::NONE,            0 },
   { ifds::WhereUseKey,        BFCBO::REQUIRED,        0 },
   { ifds::HoldingCompName,    BFCBO::REQUIRED,        0 },
   { ifds::Deff,               BFCBO::NONE,            0 },
   { ifds::StopDate,           BFCBO::NONE,            0 },
   { ifds::AggregationMethod,  BFCBO::REQUIRED,        0 },
   { ifds::ProcessDate,        BFCBO::NONE,            0 },
   { ifds::Username,           BFCBO::NONE,            0 },
   { ifds::ModDate,            BFCBO::NONE,            0 },
   { ifds::ModUser,            BFCBO::NONE,            0 },
   { ifds::GBCD,               BFCBO::NONE,            0 },
   { ifds::CompanyUsage,       BFCBO::REQUIRED,        0 },
   { ifds::Language,           BFCBO::REQUIRED,        0 },
   { ifds::EntityWhereUseRid,  BFCBO::NONE,            0 },
   { ifds::EntityWhereUseVer,  BFCBO::NONE,            0 },
   { ifds::FeeModelExist,      BFCBO::NONE,            0 },
   { ifds::FeeAggregationExist,BFCBO::NONE,            0 },
   { ifds::BillingInstrExist,  BFCBO::NONE,            0 },
   { ifds::ReportGroupExist,   BFCBO::NONE,            0 },
   { ifds::FirstChildRecDeff,  BFCBO::NONE,            0 },
   { ifds::ShrAcctLastProcDate,BFCBO::NONE,            0 },
   { ifds::CompoundDate,       BFCBO::IMMEDIATE_VALIDATION, 0 },

   { ifds::WhereUse,           BFCBO::NOT_ON_HOST, 0},
   { ifds::WhereUseCode,       BFCBO::NOT_ON_HOST, 0},
   { ifds::EntityType,         BFCBO::NOT_ON_HOST, 0},
   { ifds::EffectiveDate,      BFCBO::NOT_ON_HOST, 0},
   { ifds::CompUsage,          BFCBO::NOT_ON_HOST, 0},
   { ifds::LangCode,           BFCBO::NOT_ON_HOST, 0},


};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

HoldingComp::HoldingComp( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, orgDEFF( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );

   addCrossEdit(ifds::CompoundDate, ifds::Deff);
   addCrossEdit(ifds::CompoundDate, ifds::StopDate);
}
//******************************************************************************************
HoldingComp::~HoldingComp()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//************************************************************************************
SEVERITY HoldingComp::InitNew( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(long)" ) );

   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
SEVERITY HoldingComp::Init(const BFData& data)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&)" ) );

   //DString dstrApplHoldingCompType;
   //getWorkSession ().getOption (ifds::ApplHoldingCompType, dstrApplHoldingCompType, BF::HOST, false ); 

   //loadSubstitutionList(ifds::HoldingCompType, BF::HOST, dstrApplHoldingCompType);

   attachDataObject(const_cast<BFData&>(data), false);  

   setFieldReadOnly(ifds::WhereUseKey,BF::HOST,true);
   //setFieldReadOnly(ifds::HoldingCompType,BF::HOST,true);

//   DString orgDEFF = data.getElementValue( ifds::EffectiveDate );

   DString dstrFeeModelExist        = data.getElementValue( ifds::FeeModelExist);
   DString dstrFeeAggregationExist  = data.getElementValue( ifds::FeeAggregationExist);
   DString dstrBillingInstrExist    = data.getElementValue( ifds::BillingInstrExist);
   DString dstrReportGroupExist     = data.getElementValue( ifds::ReportGroupExist);

   if(dstrFeeModelExist.strip()     == I_("Y") || dstrFeeAggregationExist.strip() == I_("Y") ||   
      dstrBillingInstrExist.strip() == I_("Y") || dstrReportGroupExist.strip()    == I_("Y"))     
   {
      setFieldReadOnly(ifds::AggregationMethod, BF::HOST,true);
      setFieldReadOnly(ifds::CompanyUsage ,     BF::HOST,true);
   }
   else
   {
      setFieldReadOnly(ifds::AggregationMethod, BF::HOST,false);
      setFieldReadOnly(ifds::CompanyUsage ,     BF::HOST,false);
}

   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************
SEVERITY HoldingComp::doValidateField( const BFFieldId &idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if(idField == ifds::CompoundDate)
   {
      validateEffectiveStopDate(idDataGroup);
   }
   else if(idField == ifds::WhereUseKey)
   {
      validateHoldingCompCode(idDataGroup);
   }
   else if(idField == ifds::StopDate)
   {
      if(!isNew())
      {
         DString dstrOrigStopDate;
         DString dstrStopDate;
         DString dstrFirstChildRecDeff;
         getFieldBeforeImage( ifds::StopDate, dstrOrigStopDate);
         getField(ifds::StopDate, dstrStopDate, idDataGroup, false);
         dstrOrigStopDate.stripAll();
         dstrStopDate.stripAll();
         getField(ifds::FirstChildRecDeff, dstrFirstChildRecDeff, idDataGroup, false);
         dstrFirstChildRecDeff.stripAll();
         
         if(dstrFirstChildRecDeff != dstrOrigStopDate && dstrOrigStopDate != dstrStopDate)
         {
            ADDCONDITIONFROMFILE( CND::WARN_HOLD_ENT_STOP_DATE_APPIES_TO_THE_TREE);
         }
      }
   }
   else if(idField == ifds::Deff)
   {
      if(!isNew())
      {
         DString dstrDeff;
         DString dstrFirstChildRecDeff;
         getField(ifds::Deff, dstrDeff, idDataGroup, false);
         dstrDeff.stripAll();
         getField(ifds::FirstChildRecDeff, dstrFirstChildRecDeff, idDataGroup, false);
         dstrFirstChildRecDeff.stripAll();
         
         if(dstrFirstChildRecDeff != I_("12319999") && DSTCommonFunctions::CompareDates (dstrFirstChildRecDeff, dstrDeff) == DSTCommonFunctions::FIRST_EARLIER)
         {
            ADDCONDITIONFROMFILE( CND::WARN_HOLD_ENT_EFFECTIVE_DATE_APPIES_TO_THE_TREE);
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
void HoldingComp::setFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly) 
{
}

//*****************************************************************************************
SEVERITY HoldingComp::getEntity(Entity* &pEntity, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEntity" ) );

   DString dstrEntityId;
   getField(ifds::EntityId, dstrEntityId, idDataGroup, false);
   getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );

   return (GETCURRENTHIGHESTSEVERITY());
}


//*****************************************************************************************
SEVERITY HoldingComp::doApplyRelatedChanges( const BFFieldId &idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   DString dstrFieldValue;
   getField(idField, dstrFieldValue, idDataGroup, false);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void HoldingComp::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{

   setField(ifds::Language, I_("E"), idDataGroup, false);

   setFieldValid(ifds::CompanyUsage, idDataGroup, false);
   setFieldValid(ifds::AggregationMethod, idDataGroup, false);

   DString stopDate, dstrCurrBusDate, dstrAutoGenHoldingCompCode, dstrApplHoldingCompType;

   bool bAutoGenHoldingCompCode = dstrAutoGenHoldingCompCode.strip().upperCase() == I_("Y");
   setFieldRequired (ifds::Deff, idDataGroup, true );
   setFieldRequired (ifds::StopDate, idDataGroup, true );

   std::vector<DString> vModelType;
   DSTCommonFunctions::tokenizeString( dstrApplHoldingCompType, vModelType ); 

   getWorkSession().getDateInHostFormat (stopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false );
   getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
   setFieldNoValidate (ifds::Deff, dstrCurrBusDate, idDataGroup, false);
}

//*****************************************************************************************
SEVERITY HoldingComp::validateHoldingCompCode( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateHoldingCompCode" ) );

   DString dstrHoldingCompCode;
   getField(ifds::WhereUseKey,dstrHoldingCompCode,idDataGroup,false);
   if(dstrHoldingCompCode.stripAll() != NULL_STRING)
   {
      HoldingCompList lHoldingCompList(*this, dstrHoldingCompCode, I_(""), I_("Y"), I_("12319999"));
      lHoldingCompList.init(idDataGroup, I_("N"), NULL_STRING, false);
   //   if(isNew() && lHoldingCompList.
      DString dstrRepeatCount;
      
      lHoldingCompList.getField(ifds::RepeatCount, dstrRepeatCount, idDataGroup, false);
      dstrRepeatCount.stripAll();
      if(dstrRepeatCount != I_("") && dstrRepeatCount != I_("0"))
      {
         ADDCONDITIONFROMFILE( CND::ERR_CBO_HOLDING_ENTITY_CODE_ALREADY_EXISTS);
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY HoldingComp::validateEffectiveStopDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEffectiveStopDate" ) );

   DString dstrEffectDate, dstrStopDate;
   getField(ifds::Deff,dstrEffectDate,idDataGroup,false);
   getField(ifds::StopDate,dstrStopDate,idDataGroup,false);

   if( DSTCommonFunctions::CompareDates( dstrStopDate, dstrEffectDate ) == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_EFF_DATE_LATE_THAN_STOP_DATE );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
void HoldingComp::getField ( const BFFieldId &idField, DString &fieldValue, const BFDataGroupId &idDataGroup, 
                              bool formattedReturn) const
{
   BFFieldId lidField = idField;
   if (lidField == ifds::WhereUseCode)
      lidField = ifds::WhereUseKey;
   else if (lidField == ifds::WhereUse)
   {
      fieldValue = "06";
      return;
   }
   else if (lidField == ifds::EntityType)
   {
      fieldValue = "05";
      return;
   }
   else if (lidField == ifds::CompUsage)
      lidField = ifds::CompanyUsage;
   else if (lidField == ifds::EffectiveDate)
      lidField = ifds::Deff;
   else if (lidField == ifds::LangCode)
      lidField = ifds::Language;
   else if (lidField == ifds::RecId)
      lidField = ifds::EntityWhereUseRid;
   else if (lidField == ifds::Version)
      lidField = ifds::EntityWhereUseVer;
   BFCBO::getField (lidField, fieldValue, idDataGroup, formattedReturn);
}
