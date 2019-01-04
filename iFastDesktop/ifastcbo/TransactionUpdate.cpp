//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : TransactionUpdate.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "TransactionUpdate.hpp"
#include "BatchInfoList.hpp"
#include "TranslationTable.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0393_req.hpp>
#include <ifastdataimpl\dse_dstc0149_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME            = I_( "TransactionUpdate" );
   const I_CHAR * const RECORD_TYPE          = I_( "PendProcRecordType" );
   const I_CHAR * const NA                   = I_("NA");
   const I_CHAR * const INVALID_AUTH_VALUE   = I_("NA,DN,DR");
   const I_CHAR * const IN_GOOD_ORDER           = I_( "01" );
   const I_CHAR * const NOT_IN_GOOD_ORDER       = I_( "02" );
   const I_CHAR * const STOP_TRADE_SETTLEMENT   = I_( "01" );
   const I_CHAR * const MISC_TRADE_RESTRICT_RES = I_( "TR2" );
   const I_CHAR * const BLANK_SUBSTITUTION_VALUE      = I_("= ;");
   const int AUTO_BATCHING = 2;
}

namespace CND
{
   extern const long ERR_INVALID_AUTH_VALUE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFIntegerFieldId AutoBatch;
   extern CLASS_IMPORT const BFTextFieldId PaymentInfo;
   extern CLASS_IMPORT const BFTextFieldId TradeRestriction;
   extern CLASS_IMPORT const BFTextFieldId TradeRestrictionReason;
   extern CLASS_IMPORT const BFTextFieldId IsEPATrade;
   extern CLASS_IMPORT const BFTextFieldId NotApplicable;
}

namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const MODIFY_BATCH_ID;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                  State Flags,                                 Group Flags 
   { ifds::StcPendTrdAuthorization, BFCBO::NONE,                                    0 },
   { ifds::TransId,                 BFCBO::NONE,                                    0 },
   { ifds::TransNum,                BFCBO::NONE,                                    0 },
   { ifds::PendProcRecordType,      BFCBO::NONE,                                    0 },
   { ifds::SettleBatch,             BFCBO::REQUIRED | BFCBO::APPEND_VALUE_TO_SUBST, 0 },
   { ifds::PaymentInfo,				BFCBO::NONE,                                    0 },
   { ifds::TradeRestriction,        BFCBO::READ_ONLY,    0 },
   { ifds::TradeRestrictionReason,  BFCBO::NONE,         0 },
   { ifds::SourceofFundsChecked,    BFCBO::NONE,         0 },
   { ifds::ScreenDesc,              BFCBO::NONE,         0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
TransactionUpdate::TransactionUpdate( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
m_dstrPendProcRecordType (NULL_STRING),
pBatchInfoList (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );	
}

//******************************************************************************
TransactionUpdate::~TransactionUpdate()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*******************************************************************************
SEVERITY TransactionUpdate::init(const DString &recordType,
                                 const DString &transNum,
                                 const DString &transId,
                                 const DString &authorization,
                                 const DString &originalBatch,
                                 const DString &settleUser,
                                 const DString &caller,
								 const DString &paymentInfo,
								 const DString &dstrEnableTradeAuthorization,
                                 const BFDataGroupId& idDataGroup,
								 const DString &tradeRestriction,
								 const DString &tradeRestrictionReason,
                                 const DString &dstrSourceOfFundsChecked)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   setFieldNoValidate (ifds::PendProcRecordType, recordType, idDataGroup); 
   setFieldNoValidate (ifds::TransNum, transNum, idDataGroup); 
   setFieldNoValidate (ifds::TransId, transId, idDataGroup); 

   // Even the trade is not applicable for update the field, the value should be set for displayed for user's information.
   // The values should be valid from the host, should not trig for validate.
   setFieldNoValidate (ifds::TradeRestriction, tradeRestriction, idDataGroup, false, true, true); 
   setFieldNoValidate (ifds::TradeRestrictionReason, tradeRestrictionReason, idDataGroup, true, true); 
   setFieldNoValidate (ifds::StcPendTrdAuthorization, authorization, idDataGroup, false, true, true);     
   setFieldNoValidate (ifds::SourceofFundsChecked, dstrSourceOfFundsChecked, idDataGroup, false, true, true); 
   setFieldNoValidate (ifds::ScreenDesc, caller, idDataGroup, false, true, true); 

   setPaymentStatusSubstList (idDataGroup);
   setFieldNoValidate (ifds::PaymentInfo, paymentInfo, idDataGroup, false, false, false);

   _caller = caller;

   getWorkSession().getBatchList (pBatchInfoList, idDataGroup);

   if (pBatchInfoList)
   {
      DString dstrBatchList;

      pBatchInfoList->getSubstitionList(dstrBatchList, originalBatch, idDataGroup);
      setFieldAllSubstituteValues (ifds::SettleBatch, idDataGroup, dstrBatchList);
      setFieldNoValidate (ifds::SettleBatch, originalBatch, idDataGroup, false, false, true);
   }

   if (_caller != I_("Batch"))
      setFieldRequired (ifds::SettleBatch, idDataGroup, false);

   canUserModifyBatch (settleUser, idDataGroup);

   commonInit(idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransactionUpdate::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   attachDataObject(const_cast<BFData&>(data), false); 

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY TransactionUpdate::doValidateField( const BFFieldId& idField, 
                                             const DString& dstrValue, 
                                             const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   

   if (idField == ifds::StcPendTrdAuthorization)
   {
      DString strAuthorizedValue(dstrValue);
      strAuthorizedValue.strip().upperCase();

      if ( DSTCommonFunctions::codeInList (strAuthorizedValue, INVALID_AUTH_VALUE) && 
           _caller == I_("TradeAuthorization"))
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_AUTH_VALUE);
      }
   }
   else if (idField == ifds::SettleBatch && pBatchInfoList && _caller ==  I_("Batch"))
   {
      pBatchInfoList->validateBatch (dstrValue, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
void TransactionUpdate::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{

}

//****************************************************************************
SEVERITY TransactionUpdate::initNew( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
void TransactionUpdate::canUserModifyBatch (const DString &batchUser, const BFDataGroupId &idDataGroup)
{
   bool canModify = true;

   DString autoBatching;

   getWorkSession ().getOption (ifds::AutoBatch, autoBatching, BF::HOST, false);

   bool bAutoBatching = autoBatching.asInteger () == AUTO_BATCHING ? true : false;

   if (isNew() || !bAutoBatching)
      return;

   bool bModifyBatch = getWorkSession ().hasUpdatePermission (UAF::MODIFY_BATCH_ID);

   DString dstrCurrentUser = dynamic_cast<const DSTCSecurity *> (getWorkSession ().getSecurity(DSTCHost::getPrimaryHost()))->getUserId();        

   if (dstrCurrentUser != batchUser)
   {
      canModify = !bModifyBatch;
      setFieldReadOnly (ifds::SettleBatch, idDataGroup, canModify);		
   }
}

//******************************************************************************
SEVERITY TransactionUpdate::doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::SettleBatch && _caller ==  I_("Batch"))
   {
      setFieldUpdated (ifds::SettleBatch, idDataGroup, true);
	  setFieldValid (ifds::SettleBatch, idDataGroup, false);
   }
   else if (idField == ifds::TradeRestrictionReason)
   {
	   TranslationTable *pTranslationTable = NULL;
	   DString dstrTradeRestrictionReason, dstrCategory = NULL_STRING;

	   getField(ifds::TradeRestrictionReason, dstrTradeRestrictionReason, idDataGroup);

	   if (dstrTradeRestrictionReason == NOT_IN_GOOD_ORDER &&
		   getMgmtCo().getTranslationTable(MISC_TRADE_RESTRICT_RES, pTranslationTable) <= WARNING && pTranslationTable)
	   {
			pTranslationTable->getCategory(NOT_IN_GOOD_ORDER, dstrCategory);
	   }

	   setFieldNoValidate(ifds::TradeRestriction, dstrCategory, idDataGroup, false, false, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//**********************************************************************************************
SEVERITY TransactionUpdate::setPaymentStatusSubstList (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "setPaymentStatusSubstList" ));
   
   BFProperties *pBFPropertiesPaymentInfo = getFieldProperties (ifds::PaymentInfo, idDataGroup);
   assert (pBFPropertiesPaymentInfo);
   if (pBFPropertiesPaymentInfo)
   {
      DString PaymentInfoSubst;
      pBFPropertiesPaymentInfo->getAllSubstituteValues (PaymentInfoSubst);
      
	  PaymentInfoSubst = removeItemFromSubtList ( PaymentInfoSubst,I_("O") );
	  PaymentInfoSubst = removeItemFromSubtList ( PaymentInfoSubst,I_("P") );
	  PaymentInfoSubst = removeItemFromSubtList ( PaymentInfoSubst,I_("I") );
	  
	  setFieldAllSubstituteValues (ifds::PaymentInfo, idDataGroup, PaymentInfoSubst);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY TransactionUpdate::commonInit(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

	DString dstrNewSub;
	BFProperties *pBFProperties = NULL;

	//Insert "Blank" option.
	//pBFProperties = getFieldProperties(ifds::TradeRestrictionReason, idDataGroup);
	//pBFProperties->getAllSubstituteValues(dstrNewSub);
	//dstrNewSub = I_(" = ;") + dstrNewSub;
	//setFieldAllSubstituteValues(ifds::TradeRestrictionReason, idDataGroup, dstrNewSub); 

    addBlankToSubSet(ifds::TradeRestrictionReason, idDataGroup );     
    addBlankToSubSet(ifds::SourceofFundsChecked, idDataGroup, true );

	// TradeRestriction is read-only.
	setFieldReadOnly(ifds::TradeRestriction, idDataGroup, true);

	return(GETCURRENTHIGHESTSEVERITY());
}

/******************************************************************************
Input:Field ID ,DataGroupID
OutPut:
Return:Severity
Functionality:Append a blank value to sub list
******************************************************************************/
SEVERITY TransactionUpdate::addBlankToSubSet(const BFFieldId &idField ,const BFDataGroupId &idDataGroup, bool dstrUseNotApplicableAsDesc /*= false */ )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("addBlankToSubSet"));

   DString  dstrCurrSubList,dstrSubList;
   BFProperties *pBFProperties = getFieldProperties (idField, idDataGroup); 
   assert (pBFProperties);
   if (pBFProperties) 
   {
    pBFProperties->getAllSubstituteValues (dstrCurrSubList);
    DString dstrNotApplicableLangDesc;
    BFProperties *pBFPropertiesNotApplicable = getFieldProperties (ifds::NotApplicable, idDataGroup);
    pBFPropertiesNotApplicable->getDefaultValue(dstrNotApplicableLangDesc);
    pBFPropertiesNotApplicable->formatValue( ifds::NotApplicable,dstrNotApplicableLangDesc, true );
    dstrNotApplicableLangDesc = dstrUseNotApplicableAsDesc ? ( I_(" =") + dstrNotApplicableLangDesc + I_(";")): BLANK_SUBSTITUTION_VALUE;
    
    I_CHAR *temp = const_cast<I_CHAR*> (dstrCurrSubList.c_str ());
    bool blankNotAdded = true;
    do
    {
      DString dstrCode, dstrDescr;
      temp = parseIdiString (temp, dstrCode, dstrDescr );
      //if alreday in do not add again..
      if (dstrCode == I_(" "))
       {
           blankNotAdded = false;
           break;
       }
    }while (temp && temp != NULL_STRING && *temp);
    if(blankNotAdded)
    {
        dstrSubList = dstrNotApplicableLangDesc  + dstrCurrSubList;
        pBFProperties->setAllSubstituteValues( dstrSubList ); 
    }   
   }   
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionUpdate.cpp-arc  $
// 
//    Rev 1.4   Jan 20 2012 15:43:00   wp040027
// P0188394_Performance Fees - Order Entry
// 
//    Rev 1.3   Dec 08 2011 21:52:14   wp040032
// P0183989 - Money Market Non Receipt
// 
//    Rev 1.2   Sep 15 2010 04:06:16   dchatcha
// P0175471 - FundSERV Client Name Document Tracking.
// 
// 
