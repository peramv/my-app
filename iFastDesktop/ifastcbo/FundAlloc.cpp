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
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundAlloc.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : FundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all the fund allocations 
//
//******************************************************************************
#include "stdafx.h"
#include "abstractalloc.hpp"
#include "abstractalloclist.hpp"
#include "acctalloc.hpp"
#include "bankinstructionslist.hpp"
#include "fundalloc.hpp"
#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "segtradeentryvalidation.hpp"
#include "seqfundvalidation.hpp"
#include "splitcommissionlist.hpp"
#include "mfaccount.hpp"
#include "rrif_lif_lrif_info.hpp"

#include <ifastdataimpl\dse_dstc0436_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME                  = I_( "FundAlloc" );
   const I_CHAR * const SEG_FUND_VALIDATION        = I_( "SeqFundValidation" );
   const I_CHAR * const YES                        = I_( "Y" );
   const I_CHAR * const NO                         = I_( "N" );
   const I_CHAR * const SOFT_CAPPED_TRANS_LIST     = I_("AT,DD,ED,GR,SG,BG,QE,CL,RO,RB"); //AMS - RB/RO

   const double dSmallValue                        = .0000000001;
}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_BLANK_FUND;
   extern const long ERR_BLANK_CLASS;
   extern const long ERR_RIF_NON_FRACTIONAL;
   extern const long ERR_AMOUNT_EXCEED_MAX_LIMIT;
   extern const long ERR_RIF_OUT_OF_LIMITS_ALLOC_AMOUNT;
   extern const long ERR_RIF_ZERO_ALLOC_AMOUNT;
   extern const long ERR_FUND_HAS_CERTIFICATE_UNITS;
   extern const long WARN_FUND_HAS_CERTIFICATE_UNITS;
   extern const long ERR_CONTRACT_TYPE_AND_VERSION_REQUIRED;
   extern const long WARN_CONTRACT_TYPE_AND_VERSION_REQUIRED;
   extern const long ERR_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT;
   extern const long WARN_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT;
   extern const long ERR_TRADE_NOT_ALLOWED_TO_CANCEL;
   extern const long WARN_TRADE_NOT_ALLOWED_TO_CANCEL;
   extern const long ERR_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE;
   extern const long WARN_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE;
   extern const long ERR_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA;
   extern const long WARN_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA;
   extern const long ERR_SEG_VALIDATION_BACKDATED_NOT_ALLOWED;
   extern const long ERR_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE;
   extern const long WARN_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE;
   extern const long ERR_FUND_CLASS_CANNOT_PARENT;
   extern const long WARN_FUND_CLASS_CANNOT_PARENT;
}


namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId SegClient;
   extern CLASS_IMPORT const BFTextFieldId CotClient;
   extern CLASS_IMPORT const BFTextFieldId FundClassTradeDate;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId SplitComm;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId MarginEligible;
   extern CLASS_IMPORT const BFTextFieldId RecordType;
   extern CLASS_IMPORT const BFDecimalFieldId FELComm;
   extern CLASS_IMPORT const BFTextFieldId FELCommType;
   extern CLASS_IMPORT const BFTextFieldId AMSModelType;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const FUND_HAS_CERTIFICATE_UNITS;
   extern CLASS_IMPORT I_CHAR * const CONTRACT_TYPE_AND_VERSION_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const TRADE_NOT_ALLOWED_TO_CANCEL;
   extern CLASS_IMPORT I_CHAR * const BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE;
   extern CLASS_IMPORT I_CHAR * const BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA;
   extern CLASS_IMPORT I_CHAR * const LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE;
   extern CLASS_IMPORT I_CHAR * const PARENT_FUND_CLASS_CANNOT_BE_A_PART_OF_ASSET_ALLOCATION_MIX;
}

//******************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                 State Flags,               Group Flags 
   { ifds::FundCode,             BFCBO::REQUIRED,             0 }, 
   { ifds::ClassCode,            BFCBO::REQUIRED,             0 }, 
   { ifds::ToFundNumber,         BFCBO::NONE,                 0 }, 
   { ifds::Default,              BFCBO::NONE,                 0 }, 
   { ifds::SettleCurrency,       BFCBO::NONE,                 0 }, 
   { ifds::RecordType,           BFCBO::NONE,                 0 }, 

   //cross edits
   { ifds::FundClass,            BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FundClassTradeDate,   BFCBO::NONE,                 0 }, 

   { ifds::FELComm,              BFCBO::NONE,                 0 },
   { ifds::FELCommType,          BFCBO::NONE,                 0 },

};

//******************************************************************************
const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                  State Flags,      Group Flags
   { I_( "SegFundValidation" ),       BFCBO::NONE,     0},

};

//******************************************************************************
static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );
static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************
FundAlloc::FundAlloc( BFAbstractCBO &parent ) 
: AbstractAlloc( parent ),
m_bSettingFundClass(false),
m_bSettingFundNumber(false){
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,  (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo);

   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);

   //cross edit for Fund, Class, AccountNum and EffectiveDate
   addCrossEdit(ifds::FundClassTradeDate, ifds::FundCode);
   addCrossEdit(ifds::FundClassTradeDate, ifds::ClassCode);
   addCrossEdit(ifds::FundClassTradeDate, ifds::AccountNum);
   addCrossEdit(ifds::FundClassTradeDate, ifds::EffectiveDate);
}

//******************************************************************************
FundAlloc::~FundAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FundAlloc::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( AbstractAlloc::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if (idField == ifds::FundClass)
   {
      setFundNumber(idDataGroup);
	  setFieldValid (ifds::AllocPercentage, idDataGroup, false);
   }
   else if (idField == ifds::ToFundNumber)
   {
      setFundClassCode(idDataGroup);
   }
   else if (idField == ifds::AllocAmount) 
   {
      //we should look if this fund allocation has split commission list,
      //and if it has we should change the commission amounts and rates;
      SplitCommissionList* pSplitCommissionList = NULL;

      if (getSplitCommissionList(pSplitCommissionList, idDataGroup) <= WARNING && 
            pSplitCommissionList)
      {
         DString dstrAmount;

         getField(idField, dstrAmount, idDataGroup);
         pSplitCommissionList->setField(ifds::Amount, dstrAmount, idDataGroup);
      }
   }
   else if (idField == ifds::AccountNum)
   {
       setFieldValid(ifds::FundClass, idDataGroup, false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( AbstractAlloc::doValidateField( idField, strValue, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::FundCode )
      validateFundCode( strValue, idDataGroup );
   else if( idField == ifds::ClassCode )
      validateClassCode( strValue, idDataGroup );
   else if( idField == ifds::ToFundNumber )
      validateFundNumber(strValue, idDataGroup);
   else if( idField == ifds::FundClass )
      validateFundClass ( idDataGroup );
   else if( idField == ifds::FundClassTradeDate )
      validateFundClassAccNumDate ( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundAlloc::validateFundCode( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );

   DString dstrFundCode( strValue );

   if( dstrFundCode.strip().upperCase().empty() )
   {
      ADDCONDITIONFROMFILE( CND::ERR_BLANK_FUND );
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   FundMasterList *pFundMasterList = NULL;
   if( getMgmtCo().getFundMasterList(pFundMasterList)<=WARNING && pFundMasterList )
      if( !(pFundMasterList->IsFundExist( dstrFundCode, idDataGroup ) ) )
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );

   validateFundClassCertificate (idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundAlloc::validateClassCode( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClassCode" ) );

   DString dstrClassCode( strValue );
   if( dstrClassCode.strip().empty() && isClassRequired(idDataGroup) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_BLANK_CLASS );
      return(GETCURRENTHIGHESTSEVERITY());
   }
   setFundNumber(idDataGroup);

   validateFundClassCertificate (idDataGroup);


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundAlloc::validateFundNumber( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundNumber" ) );
   DString dstrFundCode,dstrClassCode;
   if( !strValue.empty() && !getWorkSession().GetFundClassCode( strValue,dstrFundCode,dstrClassCode ) )
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_NUMBER );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundAlloc::validateFundClass( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );

   FundDetail *pFundDetail = NULL;
   DString dstrClassCode, dstrFundCode, dstrTransType, dstrAccountNum, dstrEffectiveDate;

   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
   getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);

   if (!dstrFundCode.strip().upperCase().empty() && !dstrClassCode.strip().upperCase().empty())
   {
	   getFundDetail( dstrFundCode, dstrClassCode, pFundDetail );
	   if( !pFundDetail && isClassRequired(idDataGroup) )
	   {
		   ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
	   }

       if (DSTCommonFunctions::codeInList(dstrTransType, SOFT_CAPPED_TRANS_LIST))
       {
           getWorkSession().fundClassSoftCappedCheck(dstrAccountNum, dstrFundCode, dstrClassCode, I_("DD"), dstrEffectiveDate, idDataGroup);
       }
   }

   RRIF_LIF_LRIF_Info *pRRIF_LIF_LRIF_Info = dynamic_cast< RRIF_LIF_LRIF_Info * >(getParent()->getParent());

   if (pRRIF_LIF_LRIF_Info)
   {
	   pRRIF_LIF_LRIF_Info->validateGMWB (dstrFundCode, dstrClassCode, idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY FundAlloc::validateParentFundClass(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateParentFundClass" ) );
   
   FundDetail *pFundDetail = NULL;
   DString dstrClassCode, dstrFundCode;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   
   if (!dstrFundCode.strip().upperCase().empty() && !dstrClassCode.strip().upperCase().empty())
   {
	   getFundDetail( dstrFundCode, dstrClassCode, pFundDetail );
	   /*
	       The allocation could not be the parent fund class.
	       Not only AMS Model C, it should be applied to all the allocation's scenarios.
	   */
	   if ( pFundDetail )
	   {
		   DString dstrAMSModelType;
		   pFundDetail->getField(ifds::AMSModelType, dstrAMSModelType, idDataGroup, false);

		   if ( dstrAMSModelType == I_("01") )
		   {
            getErrMsg (IFASTERR::PARENT_FUND_CLASS_CANNOT_BE_A_PART_OF_ASSET_ALLOCATION_MIX,
                       CND::ERR_FUND_CLASS_CANNOT_PARENT,
                       CND::WARN_FUND_CLASS_CANNOT_PARENT,
                       idDataGroup);            
		   }

	   }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY FundAlloc::setFundClassCode(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundClassCode" ) );

   DString dstrFundNumber,dstrFundCode,dstrClassCode;

   getField(ifds::ToFundNumber,dstrFundNumber,idDataGroup,false);

   if( !dstrFundNumber.strip().empty() )
   {
      if( !m_bSettingFundNumber && getWorkSession().GetFundClassCode(
                                                                    dstrFundNumber,dstrFundCode, dstrClassCode) )
      {
         m_bSettingFundClass = true;
         setField(ifds::FundCode, dstrFundCode, idDataGroup, false, true);
         setField( ifds::ClassCode, dstrClassCode, idDataGroup, false,true); 
         m_bSettingFundClass = false;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundAlloc::setFundNumber(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundNumber" ) );

   DString dstrFundNumber,dstrFundCode,dstrClassCode;

   getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
   getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);

   getWorkSession().GetFundNumber( dstrFundCode.strip().upperCase(), 
                                   dstrClassCode.strip().upperCase(), dstrFundNumber );

   if( !(m_bSettingFundClass) )
   {
      m_bSettingFundNumber = true;
      setField( ifds::ToFundNumber, dstrFundNumber, idDataGroup, false,true );
      m_bSettingFundNumber = false;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FundAlloc::getMFAccount( MFAccount *&pAcctOut, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMFAccount" ) );

   pAcctOut = NULL;
   DString strAccountNum;
   AbstractAlloc* pParentAlloc = getParentList()->getParentAllocation();
   if( pParentAlloc )//there is an account level allocation
      pParentAlloc->getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
   else//the fund allocation is the first level allocation
      getParentList()->getField(ifds::AccountNum, strAccountNum, idDataGroup, false);

   if( strAccountNum.strip().stripLeading('0').empty() )//account num hasn't been entered yet
      return(GETCURRENTHIGHESTSEVERITY());

   getWorkSession().getMFAccount( idDataGroup, strAccountNum, pAcctOut, I_("N"), NULL_STRING, true, true  );//validate account num

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
const AcctAlloc* FundAlloc::getParentAcctAlloc()
{
   AbstractAllocList* pParent = getParentList();
   AcctAlloc* pParentAcctAlloc = dynamic_cast<AcctAlloc*>(pParent->getParentAllocation());
   return(pParentAcctAlloc);
}

//********************************************************************************
SEVERITY FundAlloc::getSeqFundValidation( SeqFundValidation *&pSeqFundValidation,
                                          const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSeqFundValidation" ) );

   //check cbobase to see if we've already built it
   //if it is already built, check if the parameters are changed
   //if not built create and store with base
   //if built but parameter(s) changed, reInit with the new ones
   pSeqFundValidation = NULL;
   DString strAccountNum, strFundCode, strClassCode, strEffectiveDate;
   getField(ifds::FundCode,strFundCode,idDataGroup,false);
   getField(ifds::ClassCode,strClassCode,idDataGroup,false);
   getField(ifds::AccountNum,strAccountNum,idDataGroup,false);
   if( strAccountNum == I_("0"))
   {
	   AbstractAlloc* pParentAlloc = getParentList()->getParentAllocation();
	   if( pParentAlloc )//there is an account level allocation
			pParentAlloc->getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
	   else//the fund allocation is the first level allocation
			getParentList()->getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
   }

   getField(ifds::EffectiveDate,strEffectiveDate,idDataGroup,false);

	// Enhancement PET1244 -- pass EventTansType as NULL_STRING to make view140 call
	
	DString strEventTransType;
   strEventTransType = NULL_STRING;

   if( strAccountNum.strip().empty() || strFundCode.strip().upperCase().empty() 
       || strClassCode.strip().upperCase().empty() || strEffectiveDate.strip().empty() )
      return(GETCURRENTHIGHESTSEVERITY());


   DString dstrKey = I_("SeqFundValidation_AccountNum=") + strAccountNum 
	               + I_(";FundCode=")     + strFundCode 
				   + I_(";ClassCode=")       + strClassCode 
				   + I_(";TradeDate=")       + strEffectiveDate
					+ I_(";EventTransType=")  + strEventTransType
				   + I_(";FundCodeTo=")   + I_( "" )            
				   + I_(";ClassCodeTo=")  + I_( "" ) 
				   + I_(";AccountNumTo=") + I_( "" );
   
   pSeqFundValidation = 
      dynamic_cast<SeqFundValidation *> (BFCBO::getObject (dstrKey, idDataGroup));
   

   if( pSeqFundValidation )
   {
      if( pSeqFundValidation->isChanged(strFundCode, strClassCode, strAccountNum, strEffectiveDate, strEventTransType) )
         pSeqFundValidation->reInit(strFundCode, strClassCode, strAccountNum, strEffectiveDate, strEventTransType);
   }
   else
   {
      pSeqFundValidation = new SeqFundValidation ( *this );
      if( pSeqFundValidation->init( strFundCode, strClassCode, strAccountNum, strEffectiveDate, strEventTransType) <= WARNING )
         setObject( pSeqFundValidation, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
      else
      {
         delete pSeqFundValidation;
         pSeqFundValidation = NULL;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool FundAlloc::isSegCotClient()
{
   DString strSegClient, strCotClient;
   getWorkSession().getOption(ifds::SegClient, strSegClient, BF::HOST );
   getWorkSession().getOption(ifds::CotClient, strCotClient, BF::HOST );
   return(strSegClient.strip() == YES && strCotClient.strip() == YES);
}

//******************************************************************************
SEVERITY FundAlloc::validateFundClassAccNumDate ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClassAccNumDate" ) );

   //ask derived class if seg fund validation is required
   if (!isSegFundValidationReq())
      return(GETCURRENTHIGHESTSEVERITY());

   // if SegClient and CotClient do the SegFundValidation

   DString accountNum,
      fundCode,
      classCode,
      tradeDate,
      transType;

   getField (ifds::AccountNum, accountNum, idDataGroup, false);
   if( accountNum == I_("0"))
   {
	   AbstractAlloc* pParentAlloc = getParentList()->getParentAllocation();
	   if( pParentAlloc )//there is an account level allocation
			pParentAlloc->getField(ifds::AccountNum, accountNum, idDataGroup, false);
	   else//the fund allocation is the first level allocation
			getParentList()->getField(ifds::AccountNum, accountNum, idDataGroup, false);
   }
   getField (ifds::FundCode,fundCode,idDataGroup,false);
   getField (ifds::ClassCode, classCode, idDataGroup,false);
   getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
   getField (ifds::TransType, transType, idDataGroup, false);

   if( isSegCotClient() || isSEGFund(fundCode))
   {
      SeqFundValidation *pSeqFundValidation = NULL;
      if( getSeqFundValidation( pSeqFundValidation, idDataGroup ) <= WARNING && pSeqFundValidation )
      {
         pSeqFundValidation->canTradeFundClass( idDataGroup );
         pSeqFundValidation->addSegFundValidationWarnings( idDataGroup );
      }
   }

   if( isSEGFund(fundCode) )
   {
      SEGTradeEntryValidation validationObj(*this);

      if( validationObj.init(accountNum,
                             fundCode,
                             classCode,
                             NULL_STRING, // account to
                             NULL_STRING, // fund to
                             NULL_STRING, // class to
                             tradeDate,
                             I_("Fund"),
                             transType,
                             I_("0")) <= WARNING )
      {
         DString strErrorCode;
         validationObj.getField(ifds::WarnCode, strErrorCode, idDataGroup, false);
         strErrorCode.strip().upperCase();

         switch( strErrorCode.asInteger())
         {
            case 1213:
            {
               DString strIDI,
                  strWarnValue1,
                  strWarnValue2;
               validationObj.getField(ifds::WarnValue1, strWarnValue1, idDataGroup, false);
               validationObj.getField(ifds::WarnValue2, strWarnValue2, idDataGroup, false);
               addIDITagValue( strIDI, I_( "CONTRACT_TYPE" ), strWarnValue1 );
               addIDITagValue( strIDI, I_( "CONTRACT_VERSION" ), strWarnValue2 );
               getErrMsg ( IFASTERR::CONTRACT_TYPE_AND_VERSION_REQUIRED,
                           CND::ERR_CONTRACT_TYPE_AND_VERSION_REQUIRED, 
                           CND::WARN_CONTRACT_TYPE_AND_VERSION_REQUIRED, 
                           idDataGroup,
                           strIDI);
            }
               break;
            case 1221:
            {
               getErrMsg ( IFASTERR::FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT,
                           CND::ERR_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT, 
                           CND::WARN_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT, 
                           idDataGroup);
            }
               break;
            default:
               break;
         }
      }

      if( validationObj.init(accountNum,
                             fundCode,
                             classCode,
                             NULL_STRING, // account to
                             NULL_STRING, // fund to
                             NULL_STRING, // class to
                             tradeDate,
                             I_("TradeDate"),
                             transType,
                             I_("0")) <= WARNING )
      {
         DString strErrorCode;
         validationObj.getField(ifds::WarnCode, strErrorCode, idDataGroup, false);
         strErrorCode.strip().upperCase();
         
         switch( strErrorCode.asInteger())
         {
            case 1214:
            {
               DString strIDI,
                  strDateFormat,
                  strWarnValue1,
                  strWarnValue2;
               validationObj.getField(ifds::WarnValue1, strWarnValue1, idDataGroup, false);
               validationObj.getField(ifds::WarnValue2, strWarnValue2, idDataGroup, false);
               strWarnValue2.lowerCase();
               DSTCommonFunctions::FormatDateByString (strWarnValue1, strWarnValue2);
               addIDITagValue( strIDI, I_( "TRADE_DATE" ), strWarnValue1 );
               getErrMsg ( IFASTERR::TRADE_NOT_ALLOWED_TO_CANCEL,
                           CND::ERR_TRADE_NOT_ALLOWED_TO_CANCEL, 
                           CND::WARN_TRADE_NOT_ALLOWED_TO_CANCEL, 
                           idDataGroup,
                           strIDI);
            }
               break;
            case 1215:
            {
               getErrMsg ( IFASTERR::BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE,
                           CND::ERR_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE, 
                           CND::WARN_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE, 
                           idDataGroup);
            }
               break;
            case 1216:
            {
               getErrMsg ( IFASTERR::BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA,
                           CND::ERR_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA, 
                           CND::WARN_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA, 
                           idDataGroup);
            }
               break;
            case 1229:
            {
               getErrMsg ( IFASTERR::LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE,
                           CND::ERR_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE, 
                           CND::WARN_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE, 
                           idDataGroup);
            }
               break;
            default:
               break;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundAlloc::setAllocFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAllocFields" ) );

   AbstractAllocList *pParentList = getParentList();
   DString str;
   pParentList->getField(ifds::TransType, str, idDataGroup, false);
   if( !str.strip().empty() )
      setField(ifds::TransType, str, idDataGroup, false);//no validate?
   pParentList->getField(ifds::EffectiveDate, str, idDataGroup, false);
   if( !str.strip().empty() )
      setField(ifds::EffectiveDate, str, idDataGroup, false);//no validate?
   pParentList->getField(ifds::AllocAmtType, str, idDataGroup, false);
   if( !str.strip().empty() )
      setField(ifds::AllocAmtType, str, idDataGroup, false);//no validate?
   pParentList->getField(ifds::AccountNum, str, idDataGroup, false);
   if( !str.strip().stripLeading('0').empty() )
      setField(ifds::AccountNum, str, idDataGroup, false);//no validate?

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
void FundAlloc::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   loadSubstitutions( idDataGroup );
   setAllocFields(idDataGroup); 
   setAmount(idDataGroup);

   clearUpdatedFlags( idDataGroup );
}

//******************************************************************************

SEVERITY FundAlloc::initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initDefault" ) )

   AbstractAlloc::initDefault(pDefaultAlloc, idDataGroup);

   DString str;

   pDefaultAlloc->getField(ifds::FundCode, str, BF::HOST, false);
   setFieldNoValidate(ifds::FundCode, str.strip().upperCase(), BF::HOST, false, false);

   pDefaultAlloc->getField(ifds::ClassCode, str, BF::HOST, false);
   setFieldNoValidate(ifds::ClassCode, str.strip().upperCase(), BF::HOST, false, false);

   setFundNumber(BF::HOST);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY FundAlloc::isInternationalWire(const DString& strSettleCurrency, const DString& strCountryCode,
                                        bool &bIsInternationalWire, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isInternationalWire" ) );

   DString dstrFundCode, dstrClassCode;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   BankInstructionsList::isInternationalWire(*this, dstrFundCode, dstrClassCode, 
      strSettleCurrency, strCountryCode, bIsInternationalWire);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void FundAlloc::setAllocFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly)
{
   AbstractAlloc::setAllocFieldsReadOnly(idDataGroup, bReadOnly);
   setFieldReadOnly( ifds::FundCode, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::ClassCode, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::ToFundNumber, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::FELComm, idDataGroup, bReadOnly );
}
//******************************************************************************

bool FundAlloc::isMarginEligible(const BFDataGroupId& idDataGroup)
{
   DString dstrFundCode, dstrClassCode;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   FundDetail *pFundDetail = NULL;
   if (getFundDetail(dstrFundCode, dstrClassCode, pFundDetail) <= WARNING && pFundDetail)
   {
      DString dstrMarginEligible;
      pFundDetail->getField(ifds::MarginEligible, dstrMarginEligible, BF::HOST, false);
      return (dstrMarginEligible.strip().upperCase() == YES);
   }
   return false;
}
//************************************************************************************
// cash might be a valid one

SEVERITY FundAlloc::validateFundCodeCash( const DString& strValue, const BFDataGroupId& idDataGroup,bool bCashValid ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCodeCash" ) );

   DString dstrFundCode( strValue );
   if( dstrFundCode.strip().upperCase() == I_( "CASH" ) && bCashValid == false )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      return(GETCURRENTHIGHESTSEVERITY());  
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//*************************************************************************************

SEVERITY FundAlloc::validateFractional(const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFractional"));

   DString dstrFundCode, dstrClassCode, strVal(strValue);
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   DString dstrCurrency;
   CurrencyClass::getFundCurrency( getWorkSession(), dstrFundCode, dstrClassCode, dstrCurrency );

   int precision =  CurrencyClass::getPrecision(getWorkSession(), dstrCurrency);

   if( precision == 0 )
   {
      double dValue = DSTCommonFunctions::convertToDouble(strVal);
      if( dValue != floor( dValue ) )
      {
         // Error: Fractional values not allowed when Precision = 0.
         ADDCONDITIONFROMFILE( CND::ERR_RIF_NON_FRACTIONAL );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundAlloc::validateAmount( const DString& strValue, 
                                    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAmount" ) );
   // validation for amount not to exceed total is done by AbstractAlloc class
   // if trade total amount is zero, there is no need to do the validation

   DString dstrTotalAmount;
   getParentList()->getField(ifds::Amount, dstrTotalAmount, idDataGroup, false);
   double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount.strip());
   if( dTotalAmount <= dSmallValue )
      return(NO_CONDITION);

   DString dstrAmount(strValue);
   dstrAmount.strip().stripAll(I_CHAR(','));
   double dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);

   ////// Amount must be > 0 , cannot be  negative for all transtype; must be <= 12 digits /////
   if( dAmount < 0 )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_RIF_OUT_OF_LIMITS_ALLOC_AMOUNT, I_( "FIELDNAME=AllocAmount " ) );
      return(GETCURRENTHIGHESTSEVERITY());
   }
   else if( dAmount > 999999999999 )
   {
      DString FieldName(I_("999,999,999,999.00"));
      DSTCommonFunctions::DisplayFormat(FieldName, ifds::Amount );
      ADDCONDITIONFROMFILEIDI( CND::ERR_AMOUNT_EXCEED_MAX_LIMIT, (I_("Amount=")+FieldName).c_str() );
      return(GETCURRENTHIGHESTSEVERITY());;
   }
   else if( dAmount <= dSmallValue )
   {
      // warning: When Accounts Amount is zero, only funds percent is allowed.
      ADDCONDITIONFROMFILE( CND::ERR_RIF_ZERO_ALLOC_AMOUNT );
   }

   validateFractional(strValue, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundAlloc::validateFundClassCertificate  (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"));

   DString dstrFund, dstrClass, dstrTransType, dstrAccount;

   getField (ifds::TransType, dstrTransType, idDataGroup);
   dstrTransType.strip().upperCase();

   bool isAMS = dstrTransType == I_("RB") || dstrTransType == I_("RO") ? true : false;

   if (!isAMS)
   {
      return GETCURRENTHIGHESTSEVERITY();
   }

   getField (ifds::FundCode, dstrFund, idDataGroup);
   getField (ifds::ClassCode, dstrClass, idDataGroup);
   getField (ifds::AccountNum, dstrAccount, idDataGroup);

   if (!dstrFund.empty () && !dstrClass.empty ())
   {
      MFAccount *pMFAccount = NULL;

      if (getMFAccount (pMFAccount, idDataGroup) <= WARNING && pMFAccount != NULL )
      {
         bool bHasCertificate = false;

         pMFAccount->doesFundHaveCertificateUnits (dstrFund, dstrClass, idDataGroup, bHasCertificate);

         if (bHasCertificate)
         {
            getErrMsg (IFASTERR::FUND_HAS_CERTIFICATE_UNITS, 
                       CND::ERR_FUND_HAS_CERTIFICATE_UNITS, 
                       CND::WARN_FUND_HAS_CERTIFICATE_UNITS, 
                       idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
bool FundAlloc::isSEGFund ( const DString& fundCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isSEGFund" ) );
   bool bIsSEGFund = false;
   FundMasterList *pFundMasterList = NULL;

   if ( !fundCode.empty() && 
         getMgmtCo().getFundMasterList (pFundMasterList) && 
         NULL != pFundMasterList )
   {
      if (pFundMasterList->isSEGFund(fundCode))
      {
         bIsSEGFund = true;
      }
   }

   return bIsSEGFund;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundAlloc.cpp-arc  $
// 
//    Rev 1.34   May 11 2012 13:33:56   jankovii
// P0186481 FN07 - GWA LWA Payment Options for SWP RRIF
// 
//    Rev 1.33   Apr 11 2012 11:56:14   dchatcha
// IN# 2901157 - Issue on SEG Trade Processing, revise allocation related logics.
// 
//    Rev 1.32   Mar 16 2012 13:37:30   dchatcha
// P0186484 FN05 - SEG Trade Processing, new validations.
// 
//    Rev 1.31   Mar 05 2012 11:58:12   dchatcha
// P0186484 FN05 - SEG Trade Processing.
// 
//    Rev 1.30   Oct 26 2009 16:32:52   jankovii
// PET157825 FN08 FN11 FN14 AMS Gaps
// 
//    Rev 1.29   16 Dec 2008 09:34:24   kovacsro
// PET22486 - FN03 - RESP Grant Commission - code review
// 
//    Rev 1.28   Dec 11 2008 09:29:40   sopitwek
// PET22486 - FN03 - RESP Grant Commission
// 
//    Rev 1.27   Sep 28 2005 16:20:48   ZHANGCEL
// PET1244 - FN01 - Seg Fund Evolution enhancement
// 
//    Rev 1.26   Sep 23 2005 18:24:22   ZHANGCEL
// PET1244 FN01 -- Seg Func Evolution enhancement
// 
//    Rev 1.25   Jul 11 2005 17:23:18   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.24   Jun 15 2005 15:48:42   porteanm
// PET1024 FN40 - Guarantee Adjustments.
// 
//    Rev 1.23   Nov 14 2004 14:41:16   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.22   Nov 04 2004 17:37:36   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.21   Sep 01 2003 21:32:32   popescu
// PET 809, FN 02 CIBC Multi Fund Transfer
// 
//    Rev 1.20   Jul 07 2003 11:36:16   YINGBAOL
// cosmetic changes
// 
//    Rev 1.19   May 22 2003 14:12:36   popescu
// Replaced name 'BankInstr' with 'BankInstructions'; 
// simplified child lists getters for the Shareholder object
// 
//    Rev 1.18   May 16 2003 17:46:38   popescu
// fixed split commission calculation in fund alloc
// 
//    Rev 1.17   May 13 2003 10:06:00   popescu
// Split commission re-work
// 
//    Rev 1.16   Apr 15 2003 10:47:30   linmay
// Sync up with 1.14.1.0
// 
//    Rev 1.15   Mar 21 2003 18:10:26   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.14   Feb 12 2003 16:48:56   KOVACSRO
// Added isMarginEligible()
// 
//    Rev 1.13   Jan 12 2003 18:54:06   KOVACSRO
// Added isClassRequired
// 
//    Rev 1.12   Nov 12 2002 11:27:38   KOVACSRO
// Added isSegFundValidationReq() to clarify which allocations require this validation.
// 
//    Rev 1.11   Oct 09 2002 23:54:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.10   Aug 29 2002 12:55:52   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.9   Aug 19 2002 15:22:54   KOVACSRO
// Added setAllocFieldsReadOnly
// 
//    Rev 1.8   Aug 06 2002 10:02:28   KOVACSRO
// Release 48. 
// 
//    Rev 1.7   Jun 27 2002 17:19:26   KOVACSRO
// AllocAmtType versus AmountType.
// 
//    Rev 1.6   Jun 07 2002 17:45:36   KOVACSRO
// International Wire modifications.
// 
//    Rev 1.5   24 May 2002 15:45:34   KOVACSRO
// Fund, Class, FundNumber issue.
// 
//    Rev 1.4   22 May 2002 18:28:40   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   08 May 2002 16:52:50   KOVACSRO
// More implementation.
// 
//    Rev 1.2   29 Apr 2002 16:23:50   KOVACSRO
// Added initDefault()
// 
//    Rev 1.1   12 Apr 2002 16:57:52   KOVACSRO
// More implementation.
 * 
 * 
 */