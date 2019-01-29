//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : DilutionAlloc.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : DilutionAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "dilutionalloc.hpp"
#include "dilutionalloclist.hpp"
#include "intermediary.hpp"
#include "intermediarylist.hpp"
#include "accshrnumcheck.hpp"
#include "mfaccount.hpp"

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "brokerlist.hpp"
#include "broker.hpp"
#include "trade.hpp"
#include "transcancel.hpp"
#include "TransactionList.hpp"
#include "TransactionDetails.hpp"
#include "dstcworksession.hpp"

#include <ifastdataimpl\dse_dstc0339_req.hpp>
#include <ifastdataimpl\dse_dstc0339_vw.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME   = I_( "DilutionAlloc" );
   const I_CHAR * const BROKER      = I_( "BROK" );
   const I_CHAR * const INTERCODE   = I_( "INTR" );
   const I_CHAR * const NA          = I_( "NA" );
   const I_CHAR * const BOTH        = I_( "0" );
   const I_CHAR * const USE_PERCENT = I_( "1" );
   const I_CHAR * const USE_DATE    = I_( "2" );
   const I_CHAR * const FSRV        = I_( "FSRV" );
   const I_CHAR * const DILUTION_NSM_ELIGIBLE = I_( "ED,PW,XR,EI,EO,AW" );
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId ReadOnly;  
   extern CLASS_IMPORT const BFTextFieldId RecordType;
   extern CLASS_IMPORT const BFNumericFieldId AssociatedAcctNum;
   extern CLASS_IMPORT const BFTextFieldId BillingToEntity;
   extern CLASS_IMPORT const BFTextFieldId BillingToEntityType;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId DataFound;
   extern CLASS_IMPORT const BFTextFieldId SplitPreferenceOption;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFTextFieldId Username;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFTextFieldId ShowExSysDilPymtNSM;
   extern CLASS_IMPORT const BFTextFieldId IntrCssStatus;
   extern CLASS_IMPORT const BFTextFieldId BrokCssStatus;
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit1;
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit2;
   extern CLASS_IMPORT const BFTextFieldId IsNetworkSettleEligible;
   extern CLASS_IMPORT const BFTextFieldId IsDilutionNSMEligible;
   extern CLASS_IMPORT const BFTextFieldId ShowDilution;
   extern CLASS_IMPORT const BFTextFieldId BrokCompliantNW;
   extern CLASS_IMPORT const BFTextFieldId BrokCssStatus;
   extern CLASS_IMPORT const BFTextFieldId IntrCssStatus;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId SettleNetwork;
   extern CLASS_IMPORT const BFTextFieldId NSMParticipants;
   extern CLASS_IMPORT const BFTextFieldId DilutionNSM;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId Reversal;
   extern CLASS_IMPORT const BFTextFieldId BillingToEntityDilutionNSMXEdit;
   extern CLASS_IMPORT const BFTextFieldId MatchingKey;
}

namespace CND
{  // Conditions used
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_DUPLICATE_RECORD;
   extern const long ERR_DILUTION_ALLOC_SPLIT_FACTOR_MANDATORY;
   extern const long ERR_DILUTION_ALLOC_ONLY_ONE_SPLIT_FACTOR_MANDATORY;

   extern const long ERR_DILUTION_ALLOC_RESP_DATE_SPLIT_METHOD;
   extern const long ERR_DILUTION_ALLOC_PERCENTAGE_MUST_BE_ZERO;
   extern const long ERR_DILUTION_ALLOC_RESP_DATE_MUST_BE_BETWEEN_TRADE_AND_SETTLEMENT_DATES;
   extern const long ERR_DILUTION_ALLOC_PERCENTAGE_SPLIT_METHOD;
   extern const long ERR_RESP_DATE_MUST_BE_12319999;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
   extern const long ERR_INVALID_ACCOUNT_NUMBER;
   extern const long ERR_ACCT_INACTIVE;
   extern const long ERR_DIFFERENT_ACCOUNTABLE_THAN_CANCELLATION_NOT_THROUGH_FUNDSERV;
   extern const long WARN_DIFFERENT_ACCOUNTABLE_THAN_CANCELLATION_NOT_THROUGH_FUNDSERV;
   extern const long ERR_FUNDSERV_SETTLE_DILUTION_OF_REBOOK_MUST_BE_THE_SAME_AS_CANCELLATION_TRADE;
   extern const long ERR_DILUTION_NSM_EXTERNAL_NSM_ONLY_ONE_YES;
   extern const long WARN_DILUTION_NSM_EXTERNAL_NSM_ONLY_ONE_YES;
}

namespace IFASTERR
{
  extern CLASS_IMPORT I_CHAR * const DIFFERENT_ACCOUNTABLE_THAN_CANCELLATION_NOT_THROUGH_FUNDSERV;
  extern CLASS_IMPORT I_CHAR * const DILUTION_NSM_EXTERNAL_NSM_ONLY_ONE_YES;
}

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                 State Flags,         Group Flags
   { ifds::Accountable,          BFCBO::REQUIRED,        0 },
   { ifds::BackDatedReason,      BFCBO::REQUIRED,        0 },
   { ifds::RespDate,             BFCBO::NONE,            0 },
   { ifds::AllocPercent,         BFCBO::NONE,            0 },
   { ifds::RecordType,           BFCBO::NONE,            0 },
   { ifds::AssociatedAcctNum,    BFCBO::NONE,            0 },
   { ifds::BillingToEntity,      BFCBO::NONE,            0 },
   { ifds::BillingToEntityType,  BFCBO::NONE,            0 },
   { ifds::InterCode,            BFCBO::NONE,            0 },
   { ifds::TransId,              BFCBO::NONE,            0 },
   { ifds::ExSysDilPymtNSM,      BFCBO::NONE,                  0 },
   { ifds::ShowExSysDilPymtNSM,  BFCBO::NOT_ON_HOST,           0 }, // to control the apperance of field at GUI level
   { ifds::ShowDilution,         BFCBO::NOT_ON_HOST,           0 }, // to control the apperance of field at GUI level
   { ifds::Username,             BFCBO::NONE,                  0 },
   { ifds::ProcessDate,          BFCBO::NONE,                  0 },
   { ifds::ModDate,              BFCBO::NONE,                  0 },
   { ifds::ModUser,              BFCBO::NONE,                  0 },
   { ifds::FieldCrossEdit1,      BFCBO::IMMEDIATE_VALIDATION,  0 },
   { ifds::FieldCrossEdit2,      BFCBO::IMMEDIATE_VALIDATION,  0 },
   { ifds::DilVersion,           BFCBO::NONE,                  0 },
   { ifds::SplitAccCodeRID,      BFCBO::NONE,                  0 },
   
   { ifds::DilutionNSM,          BFCBO::NONE,            0 },
   { ifds::IsDilutionNSMEligible,	   BFCBO::CALCULATED_FIELD,	0 },
   { ifds::BillingToEntityDilutionNSMXEdit,	   BFCBO::IMMEDIATE_VALIDATION,	0 },
   { ifds::MatchingKey,          BFCBO::NONE,            0 },

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

DilutionAlloc::DilutionAlloc( BFAbstractCBO &parent )
: MFCanBFCbo (parent),
_pIntermediaryList(NULL),
bInitNewWithDataSet_(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );

   addCrossEdit(ifds::FieldCrossEdit1, ifds::BillingToEntityType);
   addCrossEdit(ifds::FieldCrossEdit1, ifds::BillingToEntity);

   addCrossEdit(ifds::FieldCrossEdit2, ifds::BillingToEntityType);
   addCrossEdit(ifds::FieldCrossEdit2, ifds::InterCode);

   addCrossEdit(ifds::BillingToEntityDilutionNSMXEdit, ifds::BillingToEntityType);
   addCrossEdit(ifds::BillingToEntityDilutionNSMXEdit, ifds::BillingToEntity);
   addCrossEdit(ifds::BillingToEntityDilutionNSMXEdit, ifds::DilutionNSM);
   addCrossEdit(ifds::BillingToEntityDilutionNSMXEdit, ifds::InterCode);
}
//******************************************************************************************
DilutionAlloc::~DilutionAlloc()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//************************************************************************************
SEVERITY DilutionAlloc::initNew (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));  	

   DString strSplitPrefOpt, strCurrBusDate, strShowExSysDilPymtNSM;
   getWorkSession().getOption ( ifds::SplitPreferenceOption, strSplitPrefOpt, BF::HOST, false );
   getWorkSession().getOption ( ifds::CurrBusDate, strCurrBusDate, idDataGroup, false );
   getWorkSession().getOption ( ifds::ShowExSysDilPymtNSM, strShowExSysDilPymtNSM, idDataGroup, false);
   strSplitPrefOpt.strip().upperCase();
   strShowExSysDilPymtNSM.strip().upperCase();

   DilutionAllocList *pDilutionAllocList = dynamic_cast<DilutionAllocList*>( getParent( ) );
   if ( NULL != pDilutionAllocList )
   {
      DString dstrTransId = pDilutionAllocList->getTransId();
      setFieldNoValidate( ifds::TransId, dstrTransId, idDataGroup );
   }
   loadBillToEntityTypeSubstList (idDataGroup);
   loadIntermCodeSubstitutionList (idDataGroup);

   if ( strSplitPrefOpt == USE_PERCENT )
   {
      setFieldReadOnly (ifds::RespDate, idDataGroup, true );
      //setFieldNoValidate( ifds::RespDate, strCurrBusDate, idDataGroup, false );
      setFieldReadOnly (ifds::AllocPercent, idDataGroup, false );
      setFieldNoValidate( ifds::AllocPercent, I_("100"), idDataGroup, false );
   }
   else if ( strSplitPrefOpt == USE_DATE )
   {
      setFieldReadOnly (ifds::RespDate, idDataGroup, false );
      setFieldNoValidate( ifds::RespDate, strCurrBusDate, idDataGroup, false );
      setFieldReadOnly (ifds::AllocPercent, idDataGroup, true );
      setFieldNoValidate( ifds::AllocPercent, I_("0"), idDataGroup, false );
   }
   else // both
   {
      setFieldReadOnly (ifds::RespDate, idDataGroup, false );
      //setFieldNoValidate( ifds::RespDate, strCurrBusDate, idDataGroup, false );
      setFieldReadOnly (ifds::AllocPercent, idDataGroup, false );
      setFieldNoValidate( ifds::AllocPercent, I_("100"), idDataGroup, false );
   } 

   setFieldNoValidate( ifds::IsDilutionNSMEligible, I_("N"), BF::HOST, false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY DilutionAlloc::loadBillToEntityTypeSubstList (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadBillToEntityTypeSubstList"));

//set the 'other confirm type subst set'
   BFProperties *pBFPropertiesBTET = 
      getFieldProperties (ifds::BillingToEntityType, idDataGroup);

   assert (pBFPropertiesBTET);
   if (pBFPropertiesBTET)
   {
      DString billingToEntityTypeSubstList;

      pBFPropertiesBTET->getAllSubstituteValues (billingToEntityTypeSubstList);
      {
         billingToEntityTypeSubstList = I_(" =N/A;") + billingToEntityTypeSubstList;
         setFieldAllSubstituteValues (ifds::BillingToEntityType, idDataGroup, billingToEntityTypeSubstList);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY DilutionAlloc::init (const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   attachDataObject (const_cast<BFData&>(data), false);  
   setFieldNoValidate (ifds::RecordType, I_("Dilution"), BF::HOST, false );
   loadBillToEntityTypeSubstList (BF::HOST);
   CommInit (&data, BF::HOST);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY DilutionAlloc::initNew (const BFData& data, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   setFieldNoValidate( ifds::IsDilutionNSMEligible, I_("N"), BF::HOST, false);

   bInitNewWithDataSet_ = true;
   setData(data,idDataGroup);
   setFieldNoValidate (ifds::RecordType, I_("Dilution"), idDataGroup, false );
   loadBillToEntityTypeSubstList (idDataGroup);
   CommInit (&data, idDataGroup);
   bInitNewWithDataSet_ = false;

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************************
void  DilutionAlloc::CommInit ( const BFData *pData,
                                const BFDataGroupId &idDataGroup)
{
   DString dstrBillingToEntityType = NULL_STRING;
   DString dstrBillingToEntity = NULL_STRING;
   DString dstrSplitPrefOpt;
   DString dstrCurrBusDate;
   DString dstrShowExSysDilPymtNSM;

   getWorkSession().getOption ( ifds::SplitPreferenceOption, dstrSplitPrefOpt, BF::HOST, false );
   getWorkSession().getOption ( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
   getWorkSession().getOption ( ifds::ShowExSysDilPymtNSM, dstrShowExSysDilPymtNSM, idDataGroup, false);
   dstrSplitPrefOpt.strip().upperCase();
   dstrShowExSysDilPymtNSM.strip().upperCase();

   loadIntermCodeSubstitutionList (idDataGroup);

   if (pData)
   {
      pData->getElementValue (ifds::BillingToEntityType, dstrBillingToEntityType);
      pData->getElementValue (ifds::BillingToEntity, dstrBillingToEntity);

      dstrBillingToEntityType.strip ().upperCase();
      dstrBillingToEntity.strip ().upperCase();
      setFieldNoValidate (ifds::BillingToEntityType, dstrBillingToEntityType, idDataGroup, false, true, true, false);
      setFieldNoValidate (ifds::BillingToEntity, dstrBillingToEntity, idDataGroup, false, true, true, false);
   }
   else
   {
      setFieldNoValidate (ifds::BillingToEntityType, NULL_STRING, idDataGroup, true, true, true, false);
      getField (ifds::BillingToEntityType, dstrBillingToEntityType,  idDataGroup, false);
   }

   dstrBillingToEntityType.strip ().upperCase();
   dstrBillingToEntity.strip ().upperCase();

   if (dstrBillingToEntityType == INTERCODE)
   {
      setFieldNoValidate (ifds::InterCode,dstrBillingToEntity, idDataGroup, false );
      setFieldRequired (ifds::InterCode, idDataGroup, true);
      setFieldValid (ifds::InterCode, idDataGroup, false);
   }
   else if (dstrBillingToEntityType == BROKER)
   {
      setFieldRequired (ifds::BillingToEntity, idDataGroup, true);
      setFieldValid (ifds::BillingToEntity, idDataGroup, false);
   }
   else if (dstrBillingToEntityType.empty())
   {
      setFieldNoValidate (ifds::BillingToEntity, I_(""), idDataGroup, true, true, true, false);
   }

   setFieldReadOnly (ifds::BillingToEntity, idDataGroup, dstrBillingToEntityType.empty());

   if ( dstrSplitPrefOpt == USE_PERCENT )
   {
      setFieldReadOnly (ifds::RespDate, idDataGroup, true );
      setFieldReadOnly (ifds::AllocPercent, idDataGroup, false );
   }
   else if ( dstrSplitPrefOpt == USE_DATE )
   {
      setFieldReadOnly (ifds::RespDate, idDataGroup, false );
      setFieldReadOnly (ifds::AllocPercent, idDataGroup, true );
   }
   else // both
   {
      setFieldReadOnly (ifds::RespDate, idDataGroup, false );
      setFieldReadOnly (ifds::AllocPercent, idDataGroup, false );
   }

   billingToEntityFieldsReleatedChanges(idDataGroup);

   DString dstrDilutionNSM;
   getField(ifds::DilutionNSM, dstrDilutionNSM, idDataGroup, false);
   setFieldNoValidate(ifds::IsDilutionNSMEligible, dstrDilutionNSM == I_("01") ? I_("N"): I_("Y"), idDataGroup, false, true, false, false);
   
   DString dstrReadOnly;
   getParent()->getField(ifds::ReadOnly, dstrReadOnly, idDataGroup, false);
   dstrReadOnly.strip().upperCase();
   if (dstrReadOnly == Y)
   {
      DString dstrExSysDilPymtNSM;
      getField(ifds::ExSysDilPymtNSM, dstrExSysDilPymtNSM, idDataGroup,false);
      dstrExSysDilPymtNSM.strip().upperCase();

      if(dstrExSysDilPymtNSM != I_("01"))
      {
         setFieldReadOnly (ifds::ExSysDilPymtNSM, idDataGroup, false );
         setFieldRequired (ifds::ExSysDilPymtNSM, idDataGroup, true);
         setFieldValid (ifds::ExSysDilPymtNSM, idDataGroup, false);

         setFieldReadOnly (ifds::AssociatedAcctNum, idDataGroup, false );
         setFieldValid (ifds::AssociatedAcctNum, idDataGroup, false);
      }
      else
      {
         setFieldReadOnly (ifds::ExSysDilPymtNSM, idDataGroup, true );
         setFieldRequired (ifds::ExSysDilPymtNSM, idDataGroup, false);
         setFieldValid (ifds::ExSysDilPymtNSM, idDataGroup, true);
      }
   }
}

//***********************************************************************************
SEVERITY DilutionAlloc::doValidateField( const BFFieldId &idField,
                                         const DString &strValue,
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   if (idField == ifds::Accountable)
   {
      validateAccountability (strValue, idDataGroup);
   }
   if (idField == ifds::AllocPercent)
   {
      validatePercent( idDataGroup );
   }
   else if (idField == ifds::BillingToEntity)
   {
      DString brokerCode (strValue);
      brokerCode.stripAll();

      DString dstrBillingToEntityType;
      getField (ifds::BillingToEntityType, dstrBillingToEntityType,  idDataGroup, false);

      if (!brokerCode.empty () && dstrBillingToEntityType == BROKER)
      {
         setBrokerName (strValue, idDataGroup);
      }
   }
   else if(idField == ifds::BillingToEntityDilutionNSMXEdit)
   {
      validateBillingToEntityDilutionNSMXEdit(idDataGroup);
   }

   else if (idField == ifds::InterCode)
   {
      setFieldNoValidate (ifds::BillingToEntity, strValue, idDataGroup, false );
   }
   else if (idField == ifds::AssociatedAcctNum)
   {
      if (strValue != NULL_STRING && !strValue.empty () && strValue != I_("0"))
      {
         if (validateAssociatedAcctNum (strValue, idDataGroup) <= WARNING)
         {
            checkAccountStatus (strValue, idDataGroup);
         }
      }
   }
   else if (idField == ifds::DilutionNSM)
   {
      validateDilutionNSM(idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY DilutionAlloc::validateDilutionNSM(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateDilutionNSM"));

    DString dstrDilutionNSM;
    getField(ifds::DilutionNSM, dstrDilutionNSM, idDataGroup);

    DilutionAllocList *adjDilutionList = NULL;
    DString dstrAdjTransNum = getAdjTransNum(idDataGroup);

    TransactionList *pAdjTransactionList = NULL;
    if(!dstrAdjTransNum.empty()) getWorkSession().getTransactionList(pAdjTransactionList, dstrAdjTransNum, idDataGroup);

    if(pAdjTransactionList != NULL) 
    {
        TransactionDetails *pTransDetl = NULL;
        for (BFObjIter iter(*pAdjTransactionList, idDataGroup, false, BFObjIter::NON_DELETED);
            !iter.end(); 
            ++iter)
        {
            DString dstrReversal;
            iter.getObject()->getField(ifds::Reversal, dstrReversal, idDataGroup);
            if(dstrReversal == I_("Y")) 
            {
                pTransDetl = dynamic_cast<TransactionDetails*>(iter.getObject());
                break;
            }
        }
        if(pTransDetl != NULL)
        {
            DString transId;
            pTransDetl->getField(ifds::TransId, transId, idDataGroup);
            getWorkSession().getTransHistDilutionAllocList(transId, adjDilutionList, idDataGroup);
        }
    }

    if(adjDilutionList  != NULL)
    {
        BFObjIter iterAdjDilutionList(*adjDilutionList, idDataGroup, false, BFObjIter::NON_DELETED);

        if(!iterAdjDilutionList.end())
        {
            DString dstrAdjDilutionNSM;

            iterAdjDilutionList.getObject()->getField(ifds::DilutionNSM, dstrAdjDilutionNSM, idDataGroup);

            // Only if both dilution records on cancellation(adjust) and on rebook are applicable for DilutionNSM flag
            // does this validation take place.
            if (dstrAdjDilutionNSM != I_("01") &&
                dstrDilutionNSM != I_("01") &&
                dstrAdjDilutionNSM != dstrDilutionNSM)
            {
                ADDCONDITIONFROMFILE(CND::ERR_FUNDSERV_SETTLE_DILUTION_OF_REBOOK_MUST_BE_THE_SAME_AS_CANCELLATION_TRADE);
            }
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
void DilutionAlloc::setFieldsReadOnly ( const BFDataGroupId &idDataGroup, 
                                        bool bReadOnly) 
{
   DString dstrSplitPrefOpt;
   getWorkSession().getOption ( ifds::SplitPreferenceOption, 
                                dstrSplitPrefOpt, 
                                BF::HOST, 
                                false );
   dstrSplitPrefOpt.strip().upperCase();

   setFieldReadOnly (ifds::Accountable,      idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::BackDatedReason,  idDataGroup, bReadOnly);

   if ( dstrSplitPrefOpt == USE_PERCENT )
   {
      setFieldReadOnly (ifds::RespDate,         idDataGroup, true );
      setFieldReadOnly (ifds::AllocPercent,     idDataGroup, false );
   }
   else if ( dstrSplitPrefOpt == USE_DATE )
   {
      setFieldReadOnly (ifds::RespDate,         idDataGroup, false );
      setFieldReadOnly (ifds::AllocPercent,     idDataGroup, true );
   }
   else
   {
      setFieldReadOnly (ifds::RespDate,         idDataGroup, bReadOnly);
      setFieldReadOnly (ifds::AllocPercent,     idDataGroup, bReadOnly);
   }

   DString dstrBillingToEntityType;
   getField(ifds::BillingToEntityType, dstrBillingToEntityType, idDataGroup);
   dstrBillingToEntityType.stripAll().upperCase();

   setFieldReadOnly (ifds::AssociatedAcctNum,idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::BillingToEntity,  idDataGroup, dstrBillingToEntityType.empty() ? true:bReadOnly);
   setFieldReadOnly (ifds::InterCode,        idDataGroup, bReadOnly);

   setFieldReadOnly (ifds::DilutionNSM,	idDataGroup, bReadOnly);
}
//*****************************************************************************************
SEVERITY DilutionAlloc::doApplyRelatedChanges( const BFFieldId &idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (idField == ifds::BillingToEntityType)
   {
      DString dstrBillingToEntityType;
      getField (ifds::BillingToEntityType, dstrBillingToEntityType,  idDataGroup, false);

      billingToEntityReleatedChanges (dstrBillingToEntityType, idDataGroup);
   }
   else if(idField == ifds::FieldCrossEdit1 ||
           idField == ifds::FieldCrossEdit2)
   {
      billingToEntityFieldsReleatedChanges(idDataGroup);
   }

   else if (idField == ifds::IsDilutionNSMEligible)
   {
	   DString eligible ;
	   getField(ifds::IsDilutionNSMEligible, eligible, idDataGroup);
	   
	   setFieldNoValidate(ifds::DilutionNSM, eligible == I_("Y") ?  I_("02") :I_("01"), 
			   idDataGroup, false, eligible != I_("Y"), true);

     DString dstrSettleNetwork, dstrShowExSysDilPymtNSM;
     getParent()->getField(ifds::SettleNetwork, dstrSettleNetwork, idDataGroup, false);
     getWorkSession().getOption(ifds::ShowExSysDilPymtNSM, dstrShowExSysDilPymtNSM, idDataGroup, false);
     /* When settle network = FSRV and NSMEligible = yes, DilutionNSM = 02 and disabled
      Otherwise, DilutionNSM is enabled.
     */
     if(eligible == I_("Y") && dstrSettleNetwork == FSRV)
     {
       setFieldNoValidate(ifds::DilutionNSM, I_("02"), idDataGroup, false, eligible != I_("Y"), true);
     }
   }
   
   if( idField == ifds::BillingToEntityType ||
	   idField == ifds::BillingToEntity)
   {
	   refreshNSMEligibility(ifds::IsDilutionNSMEligible, idDataGroup);
   }
   if (idField == ifds::DilutionNSM)
   {
     DString dstrShowExSysDilPymtNSM, dstrShowDilution, dstrDilutionNSM, dstrExSysDilPymtNSM, dstrSettleNetwork;
     getWorkSession().getOption(ifds::ShowExSysDilPymtNSM, dstrShowExSysDilPymtNSM, idDataGroup, false);
     getWorkSession().getOption(ifds::ShowDilution, dstrShowDilution, idDataGroup, false);
     getField(ifds::DilutionNSM, dstrDilutionNSM, idDataGroup, false);
     getParent()->getField(ifds::SettleNetwork, dstrSettleNetwork, idDataGroup, false);

     if(dstrShowExSysDilPymtNSM == I_("Y") && dstrShowDilution == I_("Y"))
     {
       if(dstrDilutionNSM == I_("02"))
         dstrExSysDilPymtNSM = I_("03");
       else if (dstrDilutionNSM == I_("03"))
         dstrExSysDilPymtNSM = I_("02");
       else
         dstrExSysDilPymtNSM = I_("01");

       setFieldNoValidate(ifds::ExSysDilPymtNSM, dstrExSysDilPymtNSM, idDataGroup, false, false, true, true);
       notifyObservers(ifds::ExSysDilPymtNSM, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_(""));
     }

     if(dstrSettleNetwork != FSRV && dstrDilutionNSM != I_("02"))
     {
       getParent()->setField(ifds::DilutionLinkNum, NULL_STRING, idDataGroup, false, true, true);
     }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void DilutionAlloc::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{

   DString respDate, strReadOnly;

   setFieldRequired (ifds::BackDatedReason, idDataGroup, true );
   setFieldRequired (ifds::Accountable, idDataGroup, true );
   //getWorkSession().getDateInHostFormat (respDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);   
//for the trade's transaction builder
   setFieldNoValidate (ifds::RecordType, I_("Dilution"), idDataGroup, false );

   //setFieldNoValidate( ifds::IsDilutionNSMEligible, I_("N"), BF::HOST, false);
   getParent()->getField(ifds::ReadOnly, strReadOnly, BF::HOST, false);
   if (strReadOnly == Y)
   {
      setFieldsReadOnly (idDataGroup, true);
   }
   else
   {
      CommInit (NULL, idDataGroup);
   }
   
}

//************************************************************************************
SEVERITY DilutionAlloc::validateAccountability (const DString &dstrAccountableCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountability" ) );

   //duplicate checking
   DString dstrAccountable;

   //get the values for broker/branch/sales rep and payment for, to check against
   getField (ifds::Accountable, dstrAccountable, idDataGroup, false);
   dstrAccountable.stripAll();
   
   bool hasDuplicate = false;
   
   DilutionAllocList* pList = dynamic_cast<DilutionAllocList* >(getParent());

   BFObjIter iter(*pList, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);
   while (!iter.end())
   {
      DilutionAlloc *pDilutionAlloc = 
         dynamic_cast<DilutionAlloc*> (iter.getObject());

      if (pDilutionAlloc != this)
      {
         DString accountable_;

         pDilutionAlloc->getField (ifds::Accountable, accountable_, idDataGroup, false);
         accountable_.stripAll();
         if (accountable_ == dstrAccountable)
         {
            hasDuplicate = true;
            break;
         }
      }
      ++iter;
   }
   if (hasDuplicate)
   {
      ADDCONDITIONFROMFILE (CND::ERR_DUPLICATE_RECORD);
   }   

   return GETCURRENTHIGHESTSEVERITY();
}
//********************************************************************************

SEVERITY DilutionAlloc::validateAssociatedAcctNum (const DString &dstrAssociatedAcctNum, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAssociatedAcctNum" ) );

   AccShrNumCheck *pAccShrNumCheck = NULL;
   DString strKey (I_("AccShrNumCheck=") + dstrAssociatedAcctNum);

   pAccShrNumCheck = dynamic_cast <AccShrNumCheck*> (getObject ( strKey, idDataGroup));
   if (!pAccShrNumCheck) //make view call
   {
      pAccShrNumCheck = new AccShrNumCheck (*this);
      if (pAccShrNumCheck->initAccNum (dstrAssociatedAcctNum) <= WARNING)
      {
         setObject ( pAccShrNumCheck,
                     strKey,
                     OBJ_ACTIVITY_NONE,
                     idDataGroup);
      }
      else 
      {
         delete pAccShrNumCheck;
         pAccShrNumCheck = NULL;
      }

      DString dataFound;

      pAccShrNumCheck->getField (ifds::DataFound, dataFound, BF::HOST, false);
      if (dataFound.strip() != Y)
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_ACCOUNT_NUMBER);
      }
   }
   else
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_ACCOUNT_NUMBER);

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY DilutionAlloc::checkAccountStatus (const DString &dstrAssociatedAcctNum, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkAccountStatus" ) );

   MFAccount *pMFAccount = NULL;

   if (getWorkSession().getMFAccount ( idDataGroup, 
                                       dstrAssociatedAcctNum, 
                                       pMFAccount) <= WARNING && pMFAccount)
   {
      DString date; // need to confirm this with Wendy!!!
      getWorkSession().getOption (ifds::CurrBusDate, date, idDataGroup, false);

      if (!pMFAccount->accountActive (date, idDataGroup))
         ADDCONDITIONFROMFILE( CND::ERR_ACCT_INACTIVE );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY DilutionAlloc::validatePercent( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidatePercentage"));

   DString dstrPercentage;
   
   getField(ifds::AllocPercent, dstrPercentage, idDataGroup, false);
   dstrPercentage.strip().stripAll(I_CHAR(','));

   I_CHAR *stopstring;
   double dPercent = wcstod (dstrPercentage.c_str(), &stopstring);

   if (dPercent > 100)
   {
      ADDCONDITIONFROMFILE (CND::ERR_VALUE_BETWEEN_0_AND_100);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY DilutionAlloc::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   DString dstrSplitMethod, dstrTradeDate, dstrCurrBusDate;
   DilutionAllocList *pDilutionAllocList = dynamic_cast<DilutionAllocList*>( getParent( ) ); 
   
   getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

   if ( NULL != pDilutionAllocList )
   {
      pDilutionAllocList->getDilutionSplitMethod( dstrSplitMethod, idDataGroup );
      dstrTradeDate  = pDilutionAllocList->getTransHistTradeDate();
      //dstrSettleDate = pDilutionAllocList->getTransHistSettleDate();
      dstrSplitMethod.stripAll();
   }

   DString dstrPercent, dstrRespDate;
   getField (ifds::AllocPercent, dstrPercent,  idDataGroup, false);
   getField( ifds::RespDate,     dstrRespDate, idDataGroup, false );

   double dPercent = DSTCommonFunctions::convertToDouble( dstrPercent );

   if ( ( dstrRespDate == I_("12319999") || dstrRespDate == NULL_STRING ) && 0 == dPercent )
   {
      // Either Allocation Percentage or Responsability Code is mandatory.
      ADDCONDITIONFROMFILE( CND::ERR_DILUTION_ALLOC_SPLIT_FACTOR_MANDATORY );	
   }
   // This is for a new record	
   else if ( dstrSplitMethod.empty() &&
            ( dstrRespDate != I_("12319999") && dstrRespDate != NULL_STRING ) && 0 != dPercent )
   {
      // Cannot enter both Allocation Percentage and Responsability Code. Only one is mandatory.
      ADDCONDITIONFROMFILE( CND::ERR_DILUTION_ALLOC_ONLY_ONE_SPLIT_FACTOR_MANDATORY );	
   }
   else if ( dstrSplitMethod == I_( "D" ) )       // Date method
   {
      if( dstrRespDate == I_( "12319999" ) || dstrRespDate == NULL_STRING )
      {
         // Enter Responsability Date or modify all records to contain only Percentage.
         ADDCONDITIONFROMFILE( CND::ERR_DILUTION_ALLOC_RESP_DATE_SPLIT_METHOD );
      }
      else if( 0 != dPercent  ) 
      {
         // Percentage must be 0. Based on the first record, split factor is based on Responsability Date
         ADDCONDITIONFROMFILE( CND::ERR_DILUTION_ALLOC_PERCENTAGE_MUST_BE_ZERO );
      }
      else if (!dstrTradeDate.empty() && !dstrCurrBusDate.empty())
      {
         DString idiStr,
                 dstrDispTradeDate(dstrTradeDate),
                 dstrDispCurrBusDate(dstrCurrBusDate);
         DSTCommonFunctions::FormatDate (dstrDispTradeDate);
         DSTCommonFunctions::FormatDate (dstrDispCurrBusDate);
         addIDITagValue( idiStr, I_("TRADEDATE"), dstrDispTradeDate );
         addIDITagValue( idiStr, I_("SETTLEDATE"), dstrDispCurrBusDate );

         DString dstrSplitPrefOpt;
         getWorkSession().getOption ( ifds::SplitPreferenceOption, dstrSplitPrefOpt, BF::HOST, false );
         dstrSplitPrefOpt.strip().upperCase();
         
         if ( dstrSplitPrefOpt == USE_DATE )
         {
            if ( !DSTCommonFunctions::IsDateBetween( dstrTradeDate, dstrCurrBusDate, dstrRespDate) )
            {
               // Responsability Date must be between Trade Date %TRADEDATE% and Current Business Day.
               ADDCONDITIONFROMFILEIDI (CND::ERR_DILUTION_ALLOC_RESP_DATE_MUST_BE_BETWEEN_TRADE_AND_SETTLEMENT_DATES, idiStr)
            }
         }
         else // existing rule
         {
            if (!DSTCommonFunctions::IsDateBetween( dstrTradeDate, dstrCurrBusDate, dstrRespDate) ||
               DSTCommonFunctions::CompareDates (dstrRespDate, dstrCurrBusDate) == DSTCommonFunctions::EQUAL)
            {
               // Responsability Date must be between Trade Date %TRADEDATE% and Current Business Day.
               ADDCONDITIONFROMFILEIDI (CND::ERR_DILUTION_ALLOC_RESP_DATE_MUST_BE_BETWEEN_TRADE_AND_SETTLEMENT_DATES, idiStr)
            }
         }
      }
   }
   else if ( dstrSplitMethod == I_( "P" ) )     // Percentage method
   {
      if ( 0 == dPercent )
      {
         // Enter Percentage or modify all records to contain only Responsability Date.			
         ADDCONDITIONFROMFILE( CND::ERR_DILUTION_ALLOC_PERCENTAGE_SPLIT_METHOD );
      }
      else if( dstrRespDate != I_("12319999") && dstrRespDate != NULL_STRING  ) 
      {
         // Responsability Date must be 12/31/9999. Based on the first record, split factor is based on Percentage.
         ADDCONDITIONFROMFILE( CND::ERR_RESP_DATE_MUST_BE_12319999 );
      }
   }

   /* In case both ShowDilution and ShowExSysDilPymtNSM = yes, DilutionNSM and ExternalNSM can be "Yes" only one flag. */
   DString dstrDilutionNSM, dstrExSysDilPymtNSM;
   getField(ifds::DilutionNSM, dstrDilutionNSM,  idDataGroup, false);
   getField(ifds::ExSysDilPymtNSM, dstrExSysDilPymtNSM, idDataGroup, false);
   if(dstrDilutionNSM == I_("02") && dstrExSysDilPymtNSM == I_("02"))
     getErrMsg(IFASTERR::DILUTION_NSM_EXTERNAL_NSM_ONLY_ONE_YES,
               CND::ERR_DILUTION_NSM_EXTERNAL_NSM_ONLY_ONE_YES,
               CND::WARN_DILUTION_NSM_EXTERNAL_NSM_ONLY_ONE_YES,
               idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY DilutionAlloc::setRespDateInvalid (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setRespInvalid" ) );

   setValidFlag (ifds::RespDate, idDataGroup, false);
   setUpdatedFlag (ifds::RespDate, idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY DilutionAlloc::setTradeDateToRespDate ( const DString &tradeDate, 
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setTradeDateToRespDate"));

   DString strSplitPrefOpt;
   
   getWorkSession().getOption (ifds::SplitPreferenceOption, strSplitPrefOpt, BF::HOST, false);
   if (strSplitPrefOpt == USE_DATE)
   {
      setFieldNoValidate (ifds::RespDate, tradeDate, idDataGroup, false, false, true, true);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DilutionAlloc::loadIntermCodeSubstitutionList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadIntermCodeSubstitutionList" ) );

   if( _pIntermediaryList ) // if pIntermediaryList is not null, sustitutionlist already loaded
   {
      //_pIntermediaryList->getInterCodeList( dstrInterCodesList, true);
      //dstrInterCodesList.upperCase();
      setFieldAllSubstituteValues( ifds::InterCode, idDataGroup, dstrInterCodesList );

      return(GETCURRENTHIGHESTSEVERITY());
   }

   if( getMgmtCo().getIntermediaryList( _pIntermediaryList) <= WARNING )
   {
      _pIntermediaryList->getInterCodeList( dstrInterCodesList, true);
      dstrInterCodesList.upperCase();
      setFieldAllSubstituteValues( ifds::InterCode, idDataGroup, dstrInterCodesList );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DilutionAlloc::billingToEntityReleatedChanges( const DString &billingToEntityType,
                                                        const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("billingToEntityReleatedChanges"));

   bool bBrokerCodeRequired = billingToEntityType == BROKER ? true : false;
   bool bInterCodeRequired = billingToEntityType == INTERCODE ? true : false;

   setFieldNoValidate (ifds::BillingToEntity, I_(""), idDataGroup, false, false, true, false);
   setFieldAllSubstituteValues( ifds::InterCode, idDataGroup, dstrInterCodesList );

   setFieldRequired (ifds::InterCode, idDataGroup, bInterCodeRequired );
   setValidFlag(ifds::InterCode, idDataGroup, !bInterCodeRequired);

   setFieldRequired (ifds::BillingToEntity, idDataGroup, bBrokerCodeRequired );
   setValidFlag(ifds::BillingToEntity, idDataGroup, !bBrokerCodeRequired);

   setFieldReadOnly (ifds::BillingToEntity, idDataGroup, billingToEntityType == I_(""));

   // If 'Billing To Entity Type' is changed to N/A, ExSysDilPymtNSM should be N/A as well.
   if (billingToEntityType.empty())
   {
       setFieldNoValidate(ifds::ExSysDilPymtNSM, I_("01"), idDataGroup, false, true, true, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionAlloc::setBrokerName( const DString &brokerCode,
                                     const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setBrokerName"));

   Broker *pBroker (NULL);

   if ( getBroker ( pBroker, idDataGroup) <= WARNING &&
        pBroker)
   {
      DString dstrCurrBusDate;

      getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false); 
      pBroker->checkEffective (dstrCurrBusDate, idDataGroup);

   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionAlloc::getBroker ( Broker *&pBroker,
                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBroker"));
   pBroker = NULL;

   DString brokerCode;

   getField (ifds::BillingToEntity, brokerCode, idDataGroup, false);
   if (!brokerCode.empty())
   {
      DString strKey (I_("Broker=") + brokerCode);
      //look for the list
      BrokerList *pBrokerList = 
         dynamic_cast <BrokerList*> (getObject ( strKey, idDataGroup));

      if (!pBrokerList) //make view call
      {
         pBrokerList = new BrokerList (*this);

         if (pBrokerList->init2 ( brokerCode, 
                                  NULL_STRING, 
                                  I_("L"),  //exact match
                                  NULL_STRING, 
                                  NULL_STRING) <= WARNING)
         {
            setObject ( pBrokerList,
                        strKey,
                        OBJ_ACTIVITY_NONE,
                        idDataGroup);
         }
         else 
         {
            delete pBrokerList;
            pBrokerList = NULL;
         }
      }

      //get the broker
      if (pBrokerList)
      {
         BFObjIter bfIter (*pBrokerList, idDataGroup);

         if (!bfIter.end())
         {
            pBroker = dynamic_cast <Broker*> (bfIter.getObject());
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionAlloc::billingToEntityFieldsReleatedChanges(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("billingToEntityFieldsReleatedChanges"));

   DString dstrBillingToEntityType, dstrBillingToEntity, dstrInterCode;
   getField (ifds::BillingToEntityType, dstrBillingToEntityType, idDataGroup, false);
   dstrBillingToEntityType.strip().upperCase();

   getField (ifds::BillingToEntity, dstrBillingToEntity, idDataGroup, false);
   getField (ifds::InterCode, dstrInterCode, idDataGroup, false);
   dstrBillingToEntity.strip().upperCase();
   dstrInterCode.strip().upperCase();

   bool bSetRecordLevelShowFlag = false;

   // beause we allow ExSysDilPymtNSM to depend only billing entity type and billing to entity
   // and no need to involve with the account which is owner of the trade therefore
   // the logic would be simpler than ever
   DString dstrNSMFlag;
   if (dstrBillingToEntityType == INTERCODE && !dstrInterCode.empty())
   {
      Intermediary *pIntermediary = NULL;
      if(_pIntermediaryList->getIntermediary(idDataGroup,dstrInterCode, pIntermediary) && 
         pIntermediary != NULL)
      {
         pIntermediary->getField(ifds::IntrCssStatus,dstrNSMFlag,idDataGroup,false);
         dstrNSMFlag.strip().upperCase();

         bSetRecordLevelShowFlag = dstrNSMFlag == I_("S");
      }
   }
   else if(dstrBillingToEntityType == BROKER && !dstrBillingToEntity.empty())
   {
      Broker *pBroker = NULL;
      if( getBroker(pBroker,idDataGroup) <= WARNING && pBroker != NULL)
      {
         pBroker->getField(ifds::BrokCssStatus,dstrNSMFlag,idDataGroup,false);
         dstrNSMFlag.strip().upperCase();

         bSetRecordLevelShowFlag = dstrNSMFlag == I_("S");
      }
   }

   DString dstrShowExSysDilPymtNSM;
   getWorkSession().getOption(ifds::ShowExSysDilPymtNSM, dstrShowExSysDilPymtNSM, idDataGroup, false);

   if(bSetRecordLevelShowFlag && dstrShowExSysDilPymtNSM == I_("Y"))
   {
      setFieldNoValidate(ifds::ShowExSysDilPymtNSM,I_("Y"),idDataGroup,false);

      DString dstrDilutionNSM, dstrExSysDilPymtNSM;
      getField(ifds::DilutionNSM, dstrDilutionNSM, idDataGroup, false);
      if (isNew() && !bInitNewWithDataSet_) // a new record would have its default value
      {
        if(dstrDilutionNSM == I_("02"))
          dstrExSysDilPymtNSM = I_("03");
        else if(dstrDilutionNSM == I_("03"))
          dstrExSysDilPymtNSM = I_("02");
        
        setFieldNoValidate(ifds::ExSysDilPymtNSM, dstrExSysDilPymtNSM,idDataGroup, false, false);
        setFieldRequired (ifds::ExSysDilPymtNSM, idDataGroup, true );
      }

      setFieldReadOnly (ifds::ExSysDilPymtNSM, idDataGroup, false);
      setFieldValid (ifds::ExSysDilPymtNSM, idDataGroup, false);
   }
   else
   {
      setFieldNoValidate(ifds::ShowExSysDilPymtNSM,I_("N"),idDataGroup,false);

      if(isNew())
      {
         setFieldNoValidate(ifds::ExSysDilPymtNSM,I_("01"),idDataGroup,false);
      }

      setFieldReadOnly (ifds::ExSysDilPymtNSM, idDataGroup, true );
      setFieldRequired (ifds::ExSysDilPymtNSM, idDataGroup, false);
      setFieldValid (ifds::ExSysDilPymtNSM, idDataGroup, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY DilutionAlloc::refreshIsDilutionNSMEligible (DString& eligibility, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE(CLASSNAME, I_("IsDilutionNSMEligible"));

	eligibility = N;

	DString dstrShowDilution, dstrShowExSysDilPymtNSM;
	getWorkSession().getOption(ifds::ShowDilution, dstrShowDilution, idDataGroup, false);
  getWorkSession().getOption(ifds::ShowExSysDilPymtNSM, dstrShowExSysDilPymtNSM, idDataGroup, false);
	
	if(dstrShowDilution != I_("Y")) return GETCURRENTHIGHESTSEVERITY();
	
   DString dstrAccountable;
   getField(ifds::Accountable, dstrAccountable, idDataGroup, false);

   if(dstrAccountable != I_("01") && dstrAccountable != I_("03")) return GETCURRENTHIGHESTSEVERITY();

	int numItem = 0;
	for(BFObjIter iter(*getParent(), idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false);
		!iter.end();
		++iter)
	{
		if(dynamic_cast<DilutionAlloc*>(iter.getObject()) != NULL) ++numItem;
	}
	
	if(numItem != 1 && dstrShowExSysDilPymtNSM != I_("Y")) return GETCURRENTHIGHESTSEVERITY();

	DString dstrTransType;
	Trade* pTrade = dynamic_cast<Trade*>(getParent()->getParent());
	if (pTrade != NULL)
	{
		pTrade->getField(ifds::TradesTransType, dstrTransType, idDataGroup);
	}
	else
	{
		TransactionList *pTransactionList = dynamic_cast<DilutionAllocList*>(getParent())->getTransactionList(idDataGroup);
		if(pTransactionList == NULL) return GETCURRENTHIGHESTSEVERITY();
		
		BFObjIter transDetlIter (*pTransactionList, idDataGroup, false);
		
		if(transDetlIter.end()) return GETCURRENTHIGHESTSEVERITY();
		
		TransactionDetails *pTransactionDetails = dynamic_cast<TransactionDetails*>(transDetlIter.getObject());
		if(pTransactionDetails != NULL)
		{
			pTransactionDetails->getField(ifds::TransType, dstrTransType, idDataGroup);
		}
	}
	
	if(!DSTCommonFunctions::codeInList(dstrTransType, DILUTION_NSM_ELIGIBLE))
	{
		return GETCURRENTHIGHESTSEVERITY();
	}

	DString dstrBillingToEntity, dstrBillingToEntityType;
	
	getField(ifds::BillingToEntityType, dstrBillingToEntityType, idDataGroup);
	getField(ifds::BillingToEntity, dstrBillingToEntity, idDataGroup);

	if(dstrBillingToEntity.stripAll().empty()) return GETCURRENTHIGHESTSEVERITY();

	if(dstrBillingToEntityType == I_("BROK"))
	{
		BrokerList *pBrokerList = NULL;
		if( getWorkSession().getBrokerList(pBrokerList, idDataGroup) > WARNING ||
			pBrokerList == NULL )
		{
			return GETCURRENTHIGHESTSEVERITY();
		}

		Broker *pBroker = NULL;
		if( pBrokerList->getBroker(dstrBillingToEntity, pBroker) > WARNING||
			pBroker == NULL)
		{
			return GETCURRENTHIGHESTSEVERITY();
		}

		DString dstrBrokCompliantNW, dstrBrokCssStatus;
		pBroker->getField(ifds::BrokCompliantNW, dstrBrokCompliantNW, idDataGroup, false);
		pBroker->getField(ifds::BrokCssStatus, dstrBrokCssStatus, idDataGroup, false);

		if(dstrBrokCompliantNW != I_("F") || dstrBrokCssStatus !=I_("S")) 
		{
			return GETCURRENTHIGHESTSEVERITY();
		}
	}
	else if(dstrBillingToEntityType == I_("INTR"))
	{	
		IntermediaryList *pIntermediaryList;
		if(	getWorkSession().getMgmtCo().getIntermediaryList(pIntermediaryList) > WARNING ||
			pIntermediaryList == NULL)
		{
			return GETCURRENTHIGHESTSEVERITY();
		}

		Intermediary *pIntermediary;
		
		if(!pIntermediaryList->getIntermediary(idDataGroup, dstrBillingToEntity, pIntermediary)||
			pIntermediary == NULL)
		{
			return GETCURRENTHIGHESTSEVERITY();
		}

		DString dstrIntrCssStatus;
		pIntermediary->getField(ifds::IntrCssStatus, dstrIntrCssStatus, idDataGroup, false);

		if(dstrIntrCssStatus !=I_("S")) return GETCURRENTHIGHESTSEVERITY();
	}
	else
	{
		return GETCURRENTHIGHESTSEVERITY();
	}

	eligibility = Y;

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************

SEVERITY DilutionAlloc::refreshNSMEligibility(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE(CLASSNAME, I_("refreshNSMEligibility"));

	DString eligibility;
	if(idField == ifds::IsDilutionNSMEligible)
	{
		refreshIsDilutionNSMEligible(eligibility, idDataGroup);
	}
	DString before;
	getField(idField, before, idDataGroup, false);
	
	if (before != eligibility)
		setFieldNoValidate(idField, eligibility, idDataGroup, false);

  setFieldNoValidate(ifds::ShowDilution, eligibility, idDataGroup, false);
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionAlloc::validateBillingToEntityDilutionNSMXEdit(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE(CLASSNAME, I_("validateBillingToEntityDilutionNSMXEdit"));

   DString dstrDilutionNSM;
   getField(ifds::DilutionNSM, dstrDilutionNSM, idDataGroup);
   if(dstrDilutionNSM == I_("02"))
   {
      DilutionAllocList *adjDilutionList = NULL;
      DString dstrAdjTransNum = getAdjTransNum(idDataGroup);

      TransactionList *pAdjTransactionList = NULL;
      if(!dstrAdjTransNum.empty()) getWorkSession().getTransactionList(pAdjTransactionList, dstrAdjTransNum, idDataGroup);

	   if(pAdjTransactionList != NULL) 
      {
         TransactionDetails *pTransDetl = NULL;
         for (BFObjIter iter(*pAdjTransactionList, idDataGroup, false, BFObjIter::NON_DELETED);
               !iter.end(); 
               ++iter)
         {
            DString dstrReversal;
            iter.getObject()->getField(ifds::Reversal, dstrReversal, idDataGroup);
            if(dstrReversal == I_("Y")) 
            {
               pTransDetl = dynamic_cast<TransactionDetails*>(iter.getObject());
               break;
            }
         }
         if(pTransDetl != NULL)
         {
            DString transId;
            pTransDetl->getField(ifds::TransId, transId, idDataGroup);
            getWorkSession().getTransHistDilutionAllocList(transId, adjDilutionList, idDataGroup);
         }
      }

      if(adjDilutionList  != NULL)
      {
         BFObjIter iter(*adjDilutionList, idDataGroup, false, BFObjIter::NON_DELETED);
         if(!iter.end())
         {
            DString adjBillingToEntity, adjBillingToEntityType, adjInterCode;

            iter.getObject()->getField(ifds::BillingToEntity, adjBillingToEntity, idDataGroup);
            iter.getObject()->getField(ifds::BillingToEntityType, adjBillingToEntityType, idDataGroup);
            iter.getObject()->getField(ifds::InterCode, adjInterCode, idDataGroup);

            DString dstrBillingToEntity, dstrBillingToEntityType, dstrInterCode;

            getField(ifds::BillingToEntity, dstrBillingToEntity, idDataGroup, false);
			   getField(ifds::BillingToEntityType, dstrBillingToEntityType, idDataGroup, false);
            getField(ifds::InterCode, dstrInterCode, idDataGroup);

            bool differentAccountble = false;
            if (dstrBillingToEntityType != adjBillingToEntityType)
			   {
				   differentAccountble = true;
			   }
            else if(dstrBillingToEntityType == I_("BROK") && 
               dstrBillingToEntity != adjBillingToEntity)
            {
               differentAccountble = true;
            }
            else if(dstrBillingToEntityType == I_("INTR") &&
               dstrInterCode != adjInterCode)
            {
               differentAccountble = true;
            }

            if(differentAccountble)
            {
               getErrMsg(IFASTERR::DIFFERENT_ACCOUNTABLE_THAN_CANCELLATION_NOT_THROUGH_FUNDSERV,
					   CND::ERR_DIFFERENT_ACCOUNTABLE_THAN_CANCELLATION_NOT_THROUGH_FUNDSERV,
					   CND::WARN_DIFFERENT_ACCOUNTABLE_THAN_CANCELLATION_NOT_THROUGH_FUNDSERV,
					   idDataGroup );
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
DString DilutionAlloc::getAdjTransNum(const BFDataGroupId& idDataGroup)
{
   TransactionList *pAdjTransactionList = NULL;
   DString adjTransNum;

	Trade* pTrade = dynamic_cast<Trade*>(getParent()->getParent());
	if(pTrade != NULL)
	{
		pTrade->getField(ifds::AdjTransNum, adjTransNum, idDataGroup);
	} 
   else 
   {
      TransactionList *pTransactionList = 
            dynamic_cast<DilutionAllocList*>(getParent())->getTransactionList(idDataGroup);
      if(pTransactionList)
      {
         BFObjIter iter(*pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		   if(!iter.end())
         {
            iter.getObject()->getField(ifds::AdjTransNum, adjTransNum, idDataGroup);
         }
      }
   }
   return adjTransNum;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DilutionAlloc.cpp-arc  $
// 
//    Rev 1.24   Oct 23 2009 17:47:42   popescu
// Incident 1874666 - Rel 95 - PET 156681 FN04 - H4_H6_H8 -Default responsibility date to current date
// 
//    Rev 1.23   Aug 17 2009 16:47:32   dchatcha
// IN#1798090 - Unable to split dilution with error message.
// 
//    Rev 1.22   Aug 03 2009 18:54:02   dchatcha
// PET 157825 - FN 13 - Dilution Allocation Enhancements.
// 
//    Rev 1.21   Nov 16 2007 13:07:22   jankovii
// IN #1074083 - Error message when cancelling trade using date range split.
// 
//    Rev 1.20   Sep 25 2007 11:41:38   jankovii
// IN #1008841- Associated a/c field requires edits on terminated and invalid a/c number.
// 
//    Rev 1.19   Sep 20 2007 10:54:36   jankovii
// IN #1007476 - Dilution: associated account field.
// 
//    Rev 1.18   31 Aug 2007 11:25:10   popescu
// PET 2360 FN11 - Dilution.
// 
//    Rev 1.17   31 Aug 2007 11:11:18   popescu
// PET 2360 FN11 - Dilution.
// 
//    Rev 1.16   31 Aug 2007 10:44:14   popescu
// PET 2360 FN11 - Dilution.
// 
//    Rev 1.15   31 Aug 2007 10:17:52   popescu
// PET 2360 FN11 - Dilution.
// 
//    Rev 1.14   31 Aug 2007 10:02:54   popescu
// PET 2360 FN11 - Dillution.
// 
//    Rev 1.13   Aug 30 2007 15:18:40   jankovii
// PET 2360 FN11 - Dilution.
// 
//    Rev 1.12   Mar 13 2006 13:00:52   porteanm
// Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
// 
//    Rev 1.11   Feb 01 2006 12:01:54   AGUILAAM
// IN 534084 - format tradedate/ settledate for error message
// 
//    Rev 1.10   Dec 18 2005 15:12:40   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.9   Dec 16 2005 20:50:08   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.8   Sep 01 2005 14:01:28   popescu
// Incident# 388632 - trans cancel screen code overhaul
// 
//    Rev 1.7   Jul 29 2005 11:55:28   Fengyong
// Incident 331149 - TransCancel and dilution have different sub list for revcode and backdatereason
// 
//    Rev 1.6   Jul 07 2005 12:18:24   AGUILAAM
// PET1235 : dilution, part of Rebook/Cancellation
// 
//    Rev 1.5   Jun 23 2005 14:43:22   popescu
// Incident #340934 - do not default the RespDate to 31/12/9999 causes progress error - leave it blank
// 
//    Rev 1.4   Jun 01 2005 15:52:38   ZHANGCEL
// Incident #323301 and #322193 : Change ReasonCode to BackDatedReason
// 
//    Rev 1.3   Mar 08 2005 13:36:38   Fengyong
// PET1190 FN04 - Uncommon enhance code after DD sync up
// 
//    Rev 1.2   Mar 07 2005 13:55:18   Fengyong
// PET1190FN04 - accountableCode validation
// 
//    Rev 1.1   Mar 04 2005 17:01:18   Fengyong
// PET1190 FN04 - TranCancel tempary check in for other coder
*/
