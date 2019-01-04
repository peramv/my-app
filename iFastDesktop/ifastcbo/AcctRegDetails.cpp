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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctRegDetails.cpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 14 June 2013
//
// ^CLASS    : AcctRegDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "AcctRegDetails.hpp"

#include <bfutil\bfdate.hpp>
#include "dstcommonfunction.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "FinInstRegDetlList.hpp"
#include "ErrMsgRulesList.hpp"

namespace
{
   const I_CHAR * const CLASSNAME               = I_("AcctRegDetails");
   const I_CHAR * const YES                     = I_("Y"); 
   const I_CHAR * const NO                      = I_("N");
   const I_CHAR * const FATCA                   = I_("FA");
   const I_CHAR * const FATCA_CRSRP				= I_("FA,CRSRP");
   const I_CHAR * const SINGLE_REPORT_FFI       = I_("02");
   const I_CHAR * const MULTIPLE_REPORT_FFI     = I_("03");
   const I_CHAR * const INDIVIDUAL_ACCOUNT      = I_("0,1,2");
   const I_CHAR * const REJERR_ERROR            = I_("E");
   const I_CHAR * const REJERR_WARNING          = I_("W");
   const I_CHAR * const REJERR_IGNORE           = I_("I");
   const I_CHAR * const TAG_FFI_STARTDATE       = I_("STARTDATE");
   const I_CHAR * const TAG_FFI_STOPDATE        = I_("STOPDATE");
   const I_CHAR * const TAG_REC_STARTDATE       = I_("STARTDATE");
   const I_CHAR * const TAG_REC_STOPDATE        = I_("STOPDATE");
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId FICategory;
   extern CLASS_IMPORT const BFTextFieldId FinInstRegDetlUUID;
   extern CLASS_IMPORT const BFTextFieldId AcctRegDetailsUUID;
   extern CLASS_IMPORT const BFTextFieldId ComplyAction;
   extern CLASS_IMPORT const BFTextFieldId Consented;
   extern CLASS_IMPORT const BFNumericFieldId VersionAcctRegDetl;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId Username;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFTextFieldId Description;
   extern CLASS_IMPORT const BFTextFieldId Regulatory;
   extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId ReportFFIType;
   extern CLASS_IMPORT const BFTextFieldId DefaultReportingFFI;
   extern CLASS_IMPORT const BFDecimalFieldId AcctRegDetailRid;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId ComplyRuleDesc;
}

namespace CND
{  
   extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
   extern const long ERR_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI;
   extern const long WARN_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,              State Flags,    Group Flags 
   {ifds::EffectiveDate,         BFCBO::NONE,         0 }, 
   {ifds::StopDate,              BFCBO::NONE,         0 }, 
   {ifds::Regulatory,            BFCBO::NONE,         0 }, // ComplyRule
   {ifds::FinInstRegDetlUUID,    BFCBO::NONE,         0 },
   {ifds::FICategory,            BFCBO::NONE,         0 },
   {ifds::AcctRegDetailsUUID,    BFCBO::NONE,         0 },
   {ifds::ComplyAction,          BFCBO::NONE,         0 },
   {ifds::Consented,             BFCBO::NONE,         0 },
   {ifds::VersionAcctRegDetl,    BFCBO::NONE,         0 },
   {ifds::ProcessDate,           BFCBO::NONE,         0 },
   {ifds::Username,              BFCBO::NONE,         0 },
   {ifds::ModDate,               BFCBO::NONE,         0 },
   {ifds::ModUser,               BFCBO::NONE,         0 },
   {ifds::AcctRegDetailRid,      BFCBO::NONE,         0 },
   {ifds::DefaultReportingFFI,   BFCBO::NOT_ON_HOST,  0 },
   {ifds::ComplyRuleDesc,		 BFCBO::NONE,         0 },

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
AcctRegDetails::AcctRegDetails (BFAbstractCBO &parent) :
   MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   addCrossEdit(ifds::EffectiveStopDate, ifds::EffectiveDate);
   addCrossEdit(ifds::EffectiveStopDate, ifds::StopDate);
}

//****************************************************************************
AcctRegDetails::~AcctRegDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY AcctRegDetails::init (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   commonInit(BF::HOST);

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY AcctRegDetails::initNew (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY AcctRegDetails::commonInit(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   //DString dstrNewSub, dstrReportFFIType;
   //BFProperties *pBFProperties = NULL;
   //MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getParent()->getParent());

   ////For Category field, user is allowed to not select any value.
   //pBFProperties = getFieldProperties(ifds::FICategory, idDataGroup);
   //pBFProperties->getAllSubstituteValues(dstrNewSub);
   //dstrNewSub = I_(" = ;") + dstrNewSub;
   //setFieldAllSubstituteValues(ifds::FICategory, idDataGroup, dstrNewSub);

   ////For consented field, user is allowed to not select any value.
   //pBFProperties = getFieldProperties(ifds::Consented, idDataGroup);
   //pBFProperties->getAllSubstituteValues(dstrNewSub);
   //dstrNewSub = I_(" =NA;") + dstrNewSub;
   //setFieldAllSubstituteValues(ifds::Consented, idDataGroup, dstrNewSub);

   ////For action field, user is allowed to not select any value.
   //pBFProperties = getFieldProperties(ifds::ComplyAction, idDataGroup);
   //pBFProperties->getAllSubstituteValues(dstrNewSub);
   //dstrNewSub = I_(" = ;") + dstrNewSub;
   //setFieldAllSubstituteValues(ifds::ComplyAction, idDataGroup, dstrNewSub);

   ////If environment is single reporting FFI then set as read-only.
   //getWorkSession().getOption(ifds::ReportFFIType, dstrReportFFIType, BF::HOST, false);
   //if (dstrReportFFIType == SINGLE_REPORT_FFI)
   //{
   //	setFieldReadOnly(ifds::FinInstRegDetlUUID, idDataGroup, true);
   //}

   setReportingFFISubstitution(idDataGroup);

   ////Only non individual account applicable for Classification

   //if (pMFAccount)
   //{
   //	DString dstrAcctType;
   //	bool isIndividualAcct;

   //	pMFAccount->getField(ifds::AcctType, dstrAcctType, idDataGroup);

   //	isIndividualAcct = DSTCommonFunctions::codeInList(dstrAcctType, INDIVIDUAL_ACCOUNT);
   //	setFieldReadOnly(ifds::FICategory, idDataGroup, isIndividualAcct);
   //}

   //setDefaultReportingFFI(idDataGroup);

   //setFieldReadOnly(ifds::Regulatory, idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void AcctRegDetails::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
   //DString dstrCurrBusDate, dstrReportFFIType, defaultStopDate;

   //getWorkSession().getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
   //setFieldNoValidate(ifds::EffectiveDate, dstrCurrBusDate, idDataGroup);

   //getWorkSession().getDateInHostFormat(defaultStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   //setFieldNoValidate(ifds::StopDate, defaultStopDate, idDataGroup);

   //setFieldNoValidate(ifds::Regulatory, FATCA, idDataGroup, false, true);

   //commonInit(idDataGroup);

   ////If environment is set as single reporting FFI then set it as NULL.
   //getWorkSession().getOption(ifds::ReportFFIType, dstrReportFFIType, BF::HOST, false);
   //if (dstrReportFFIType == SINGLE_REPORT_FFI)
   //{
   //	setFieldNoValidate(ifds::FinInstRegDetlUUID, NULL_STRING, idDataGroup);
   //}
}

//********************************************************************************************
SEVERITY AcctRegDetails::doValidateField(const BFFieldId& idField,
                                         const DString& strValue,
                                         const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   //FinInstRegDetlList *pFinInstRegDetlList = NULL;
   //MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getParent()->getParent());
   //DString ffiStartDate, ffiStopDate, acctStartDate, acctStopDate;

   //getField(ifds::EffectiveDate, acctStartDate, idDataGroup, true);
   //getField(ifds::StopDate, acctStopDate, idDataGroup, true);

   //if (pMFAccount->getFinInstRegDetlList(pFinInstRegDetlList, FATCA, idDataGroup) <= WARNING && pFinInstRegDetlList)
   //{
   //	DString dstrFinInstRegDetlUUID;
   //	getField(ifds::FinInstRegDetlUUID, dstrFinInstRegDetlUUID, idDataGroup);
   //	pFinInstRegDetlList->getFFIStartStopDate(idDataGroup, dstrFinInstRegDetlUUID, ffiStartDate, ffiStopDate);
   //}

   //if (ifds::EffectiveStopDate == idField)
   //{
   //	if (DSTCommonFunctions::CompareDates(acctStopDate, acctStartDate) == DSTCommonFunctions::FIRST_EARLIER)
   //	{
   //		ADDCONDITIONFROMFILE(CND::ERR_STOP_DATE_LESS_THAN_DEFF);
   //	}
   //}
   //else if (ifds::FinInstRegDetlUUID == idField)
   //{
   //	if (ffiStartDate != NULL_STRING && ffiStopDate != NULL_STRING &&	
   //		DSTCommonFunctions::CompareDates(acctStartDate, ffiStartDate) == DSTCommonFunctions::FIRST_EARLIER ||
   //		DSTCommonFunctions::CompareDates(acctStopDate, ffiStopDate) == DSTCommonFunctions::SECOND_EARLIER)
   //	{
   //		DString strTag;
   //		//addIDITagValue(strTag, TAG_FFI_STARTDATE, ffiStartDate);
   //		//addIDITagValue(strTag, TAG_FFI_STOPDATE, ffiStopDate);
   //		addIDITagValue(strTag, TAG_REC_STARTDATE, acctStartDate);

   //		getErrMsg(IFASTERR::START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI,
   //		CND::ERR_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI, 
   //		CND::WARN_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI, 
   //		idDataGroup,
   //		strTag);
   //	}
   //}
   //else if (ifds::EffectiveDate == idField)
   //{
   //	if (ffiStartDate != NULL_STRING && ffiStopDate != NULL_STRING &&
   //		DSTCommonFunctions::CompareDates(acctStartDate, ffiStartDate) == DSTCommonFunctions::FIRST_EARLIER)
   //	{
   //		DString strTag;
   //		//addIDITagValue(strTag, TAG_FFI_STARTDATE, ffiStartDate);
   //		//addIDITagValue(strTag, TAG_FFI_STOPDATE, ffiStopDate);
   //		addIDITagValue(strTag, TAG_REC_STARTDATE, acctStartDate);

   //		getErrMsg(IFASTERR::START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI,
   //		CND::ERR_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI, 
   //		CND::WARN_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI, 
   //		idDataGroup,
   //		strTag);
   //	}
   //}
   //else if (ifds::StopDate == idField)
   //{
   //	if (ffiStartDate != NULL_STRING && ffiStopDate != NULL_STRING &&
   //		DSTCommonFunctions::CompareDates(acctStopDate, ffiStopDate) == DSTCommonFunctions::SECOND_EARLIER)
   //	{
   //		DString strTag;
   //		//addIDITagValue(strTag, TAG_FFI_STARTDATE, ffiStartDate);
   //		//addIDITagValue(strTag, TAG_FFI_STOPDATE, ffiStopDate);
   //		addIDITagValue(strTag, TAG_REC_STARTDATE, acctStartDate);

   //		getErrMsg(IFASTERR::START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI,
   //		CND::ERR_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI, 
   //		CND::WARN_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI, 
   //		idDataGroup,
   //		strTag);
   //	}
   //}


   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY AcctRegDetails::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY AcctRegDetails::doApplyRelatedChanges (const BFFieldId &idField, 
                                                const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   DString dstrIdValue;
   getField(idField, dstrIdValue, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void AcctRegDetails::doReset (const BFDataGroupId &idDataGroup)
{

}

//****************************************************************************
SEVERITY AcctRegDetails::setReportingFFISubstitution(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setReportingFFISubstitution"));

   DString dstrSubstitution, dstrAcctNum = NULL_STRING;
   FinInstRegDetlList *pFinInstRegDetlList = NULL;
   MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getParent()->getParent());

   dstrSubstitution = I_(" = ;");

   if (pMFAccount && !pMFAccount->isNew())
   {
      pMFAccount->getField(ifds::AccountNum, dstrAcctNum, idDataGroup);

      if (pMFAccount && pMFAccount->getFinInstRegDetlList(pFinInstRegDetlList, FATCA_CRSRP, idDataGroup, true) <= WARNING && 
          pFinInstRegDetlList)
      {
         BFObjIter iter(*pFinInstRegDetlList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
         iter.begin();

         while (!iter.end())
         {
            DString ffiUUID, ffiDescription;

            iter.getObject()->getField(ifds::FinInstRegDetlUUID, ffiUUID, idDataGroup);
            iter.getObject()->getField(ifds::Description, ffiDescription, idDataGroup);

            dstrSubstitution += ffiUUID + I_("=") + ffiDescription + I_(";");

            ++iter;
         }

         setFieldAllSubstituteValues(ifds::FinInstRegDetlUUID, idDataGroup, dstrSubstitution);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY AcctRegDetails::setDefaultReportingFFI(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setDefaultReportingFFI"));

   //MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getParent()->getParent());
   //FinInstRegDetlList *pFinInstRegDetlList = NULL;
   //DString dstrDefaultFFI;

   //if (pMFAccount && pMFAccount->getFinInstRegDetlList(pFinInstRegDetlList, FATCA, idDataGroup) <= WARNING && pFinInstRegDetlList)
   //{
   //	pFinInstRegDetlList->getField(ifds::DefaultReportingFFI, dstrDefaultFFI, idDataGroup);
   //	setFieldNoValidate(ifds::DefaultReportingFFI, dstrDefaultFFI, idDataGroup, false, true);
   //}

   //setFieldReadOnly(ifds::DefaultReportingFFI, idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY();
}
