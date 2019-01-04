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
// ^FILE   : DefFundAlloc.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : DefFundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : default fund allocation
//
//******************************************************************************
#include "stdafx.h"
#include "abstractalloclist.hpp"
#include "acctalloc.hpp"
#include "deffundalloc.hpp"
#include "dynamicsublistholder.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "fundmasterlist.hpp"
#include "fundmaster.hpp"
#include "fundgrouptypelist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "AMSAcctLvl.hpp"
#include "brokerlist.hpp"
#include "acqFeeInquiry.hpp"
#include "fundlmtoverride.hpp"//IN2818924 - DSK_AMS Validation for CDIC
#include "fundlmtoverridelist.hpp"

#include <ifastdataimpl\dse_dstc0380_vw.hpp> 
#include <ifastdataimpl\dse_dstc0083_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME                   = I_( "DefFundAlloc" );
   const I_CHAR * const NO                          = I_( "N" );
   const I_CHAR * const YES                         = I_( "Y" );
   const I_CHAR * const FUND_LEVEL                  = I_( "3" );
   const I_CHAR * const FUNDNAME1                   = I_( "FUNDNAME" );
   const I_CHAR * const CLASSNAME1                  = I_( "CLASSNAME" );
   const I_CHAR * const TRADE_TYPE                  = I_( "TRADE_TYPE") ;
   const I_CHAR * const PURCHASECODELIST            = I_( "ED,DD,GP" );
   const I_CHAR * const REDEMPTIONCODELIST          = I_( "PW,AW,RF,LF,LR" );
   const I_CHAR * const TRANSFERCODELIST            = I_( "TR,AT" );
   const I_CHAR * const FOREIGN_CONTENT_REBALANCING = I_( "XS" );
   const I_CHAR * const MANAGEMENT_FEE_CODE         = I_( "MF" );
   const I_CHAR * const CLASS_MUST_BE_BLANK         = I_( "1" );
   const I_CHAR * const CLASS_MUST_BE_SUPPLIED      = I_( "0" );
   const I_CHAR * const REBALANCE					    = I_("RB");
   const I_CHAR * const REPORT_ONLY	 				    = I_("RO");
   const I_CHAR * const DEFAULT_AMS_TYPE			    = I_("ROFND");
   const I_CHAR * const DEFAULT_AMS_GROUP_CODE		 = I_("VISCNT");
   const I_CHAR * const DEFAULT_AMS_TYPE_REBAL		 = I_("REBAL");

   //frank russel have diffrent default amttype from the other client
   const I_CHAR * const DEFAULT_AMS_TYPE_FRK        = I_("REPORT");
   const I_CHAR * const DEFAULT_AMS_GROUP_CODE_FRK  = I_("TARAST");
   // RESP GRANT Commission project
   const I_CHAR * const RESP_GRANT                  = I_("GR");
   const I_CHAR * const FRONT_END_LOAD              = I_("FEL");
   // QESI 
   const I_CHAR * const QESI                        = I_( "QE" );
   const I_CHAR * const QESI_RETURN                 = I_( "QR" );
//FEL Comm applicable trans types
   const I_CHAR * const FEL_COMM_APPLICABLE         = I_("QE,GR");
   const I_CHAR * const  BANKRUPTCY = I_("43"); //IN2818924 - DSK_AMS Validation for CDIC
}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_FUND_CLASS_NOT_EFFECTIVE;
   extern const long ERR_CASH_FUND_NOT_ALLOWED;
   extern const long ERR_ONLY_GIC_PURCHASES_ALLOWED;
   extern const long ERR_INVALID_FOR_FOREIGN_CONTENT_TRANSFER;
   extern const long ERR_INPUT_FUND_DOMESTIC;
   extern const long ERR_CURRENCY_SHOULD_BE_SAME;
   extern const long ERR_FUND_CLASS_STOP_FLAG_ON;
   extern const long ERR_CLASS_CODE_MUST_BE_BLANK;
   extern const long ERR_FUND_CODE_MUST_BE_IN_GROUP;
   extern const long ERR_FUND_CLASS_MUST_BE_IN_GROUP;
   extern const long ERR_FUND_NOT_ELIGIBLE_FCTRFR;
   extern const long ERR_FUND_SYSGENTRFIN_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_SYSGENTRFIN_STOP_FLAG_ON;
   extern const long ERR_AMS_FUND_CLASS_INVALID;
   extern const long ERR_FUND_ALLOC_ONE_FUND_ONLY;
   extern const long ERR_UNABLE_GET_FEE_VALUE_RESP_GRANT;
   extern const long ERR_FEE_MORE_THAN_MAX_RESP_GRANT;
   extern const long ERR_FEE_LESS_THAN_MIN_RESP_GRANT;
   extern const long ERR_INVALID_FEE_VALUE_RESP_GRANT;
   extern const long ERR_DEALER_NOT_ELIGIBLE_FOR_FUND_CLASS;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER;
   extern const long ERR_ALLOCATION_OPTION_NOT_AVAILABLE;
   extern const long WARN_ALLOCATION_OPTION_NOT_AVAILABLE;
   extern const long ERR_ACCOUNT_AMS_MODEL_CANNOT_HOLD_GLOBAL_MODEL_FUNDS;
   extern const long WARN_ACCOUNT_AMS_MODEL_CANNOT_HOLD_GLOBAL_MODEL_FUNDS;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const ALLOCATION_OPTION_NOT_AVAILABLE;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_AMS_MODEL_CANNOT_HOLD_GLOBAL_MODEL_FUNDS;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId FrngSweep;
   extern CLASS_IMPORT const BFTextFieldId SysCurrency;
   extern CLASS_IMPORT const BFTextFieldId Domestic;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFDecimalFieldId Level;
   extern CLASS_IMPORT const BFTextFieldId AcctTradeType;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId rxTransTypeJapanese;
   extern CLASS_IMPORT const BFTextFieldId rxTransType;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId XSFundsValidate;
   extern CLASS_IMPORT const BFIntegerFieldId ClassRule;
   extern CLASS_IMPORT const BFTextFieldId FundGroupCE;
   extern CLASS_IMPORT const BFTextFieldId FundGroupCode;
   extern CLASS_IMPORT const BFTextFieldId ClassE;
   extern CLASS_IMPORT const BFTextFieldId FundType;
   extern CLASS_IMPORT const BFTextFieldId FundClassTradeType;
   extern CLASS_IMPORT const BFTextFieldId FCTransferElig;
   extern CLASS_IMPORT const BFTextFieldId StopSysGenTrnfrIn;
   extern CLASS_IMPORT const BFTextFieldId AMSFund;
	extern CLASS_IMPORT const BFTextFieldId AMSEligible;
   extern CLASS_IMPORT const BFTextFieldId StopPurchase;
   extern CLASS_IMPORT const BFTextFieldId StopRed;
   extern CLASS_IMPORT const BFTextFieldId StopXferIn;
	extern CLASS_IMPORT const BFTextFieldId UpdatePACSWP;
	extern CLASS_IMPORT const BFTextFieldId Rebalance;
	extern CLASS_IMPORT const BFTextFieldId LoadType;
	extern CLASS_IMPORT const BFTextFieldId BrokerCode;
	extern CLASS_IMPORT const BFDecimalFieldId MinFee;
	extern CLASS_IMPORT const BFDecimalFieldId MaxFee;
	extern CLASS_IMPORT const BFDecimalFieldId MinPercent;
	extern CLASS_IMPORT const BFDecimalFieldId MaxPercent;
	extern CLASS_IMPORT const BFTextFieldId AllocTypeForBrokerValidation;
	extern CLASS_IMPORT const BFTextFieldId FundAllow;
	extern CLASS_IMPORT const BFTextFieldId AddPerm;
	extern CLASS_IMPORT const BFTextFieldId ValidationPassed;
	extern CLASS_IMPORT const BFTextFieldId MaxFeeActive;
	extern CLASS_IMPORT const BFDecimalFieldId MaxFlatFundCurr;
	extern CLASS_IMPORT const BFDecimalFieldId FELComm;
	extern CLASS_IMPORT const BFTextFieldId FELCommType;
	extern CLASS_IMPORT const BFTextFieldId FELCommFundClass;
	extern CLASS_IMPORT const BFTextFieldId FELCommOnGrant;
	extern CLASS_IMPORT const BFTextFieldId  StopFlag;
}
//******************************************************************************

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   { ifds::FundGroup, BFCBO::NONE, 0 }, 
      //cross edits
   { ifds::AcctTradeType,      BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FundGroupCE,        BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FundGroupCode,      BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::ClassE,             BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FundType,           BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FundClassTradeType, BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::FELCommFundClass,   BFCBO::IMMEDIATE_VALIDATION, 0 }, 

};

//******************************************************************************

static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
DefFundAlloc::DefFundAlloc( BFAbstractCBO &parent ) 
: FundAlloc( parent ),
m_bBankruptcyApplied(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );

   //crossedit for TransType, AccountNum, FundCode, ClassCode, EffectiveDate
   addCrossEdit(ifds::AcctTradeType, ifds::TransType);
   addCrossEdit(ifds::AcctTradeType, ifds::AccountNum);
   addCrossEdit(ifds::AcctTradeType, ifds::FundCode);
   addCrossEdit(ifds::AcctTradeType, ifds::ClassCode);
   addCrossEdit(ifds::AcctTradeType, ifds::EffectiveDate);

   //crossedit for FundGroup, FundCode, ClassCode, TransType
   addCrossEdit(ifds::FundGroupCE, ifds::FundCode);
   addCrossEdit(ifds::FundGroupCE, ifds::ClassCode);
   addCrossEdit(ifds::FundGroupCE, ifds::FundGroup);
   addCrossEdit(ifds::FundGroupCE, ifds::TransType);

   //crossedit for FundGroup, FundCode, TransType
   addCrossEdit(ifds::FundGroupCode, ifds::FundCode);
   addCrossEdit(ifds::FundGroupCode, ifds::FundGroup);
   addCrossEdit(ifds::FundGroupCode, ifds::TransType);

   //crossedit for ClassCode, TransType
   addCrossEdit(ifds::ClassE, ifds::ClassCode);
   addCrossEdit(ifds::ClassE, ifds::TransType);

   //crossedit for FundCode, TransType
   addCrossEdit(ifds::FundType, ifds::FundCode);
   addCrossEdit(ifds::FundType, ifds::TransType);

   //crossedit for FundCode, ClassCode, TransType
   addCrossEdit(ifds::FundClassTradeType, ifds::FundCode);
   addCrossEdit(ifds::FundClassTradeType, ifds::ClassCode);
   addCrossEdit(ifds::FundClassTradeType, ifds::TransType);

   //crossedit for FundCode, ClassCode, FEL Commission   
   addCrossEdit(ifds::FELCommFundClass, ifds::FundCode);
   addCrossEdit(ifds::FELCommFundClass, ifds::ClassCode);
   addCrossEdit(ifds::FELCommFundClass, ifds::FELComm);

}

//******************************************************************************
DefFundAlloc::~DefFundAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY DefFundAlloc::initNew( const BFDataGroupId& idDataGroup,
                                const DString& dstrTrack ,
                                const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   m_bBankruptcyApplied = false;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void DefFundAlloc::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
   setFieldNoValidate(ifds::Level, FUND_LEVEL, idDataGroup, false);

   setFieldRequired(ifds::TransType, idDataGroup, true);
   setFieldRequired(ifds::EffectiveDate, idDataGroup, true);
   setFieldRequired(ifds::AccountNum, idDataGroup, true);
   if (!isClassRequired (idDataGroup))
   {
      setFieldRequired (ifds::ClassCode, idDataGroup, false);
   }     
   setFieldReadOnly (ifds::FELComm, idDataGroup, !isRESPFELCommApplicable (idDataGroup));

   FundAlloc::doInitWithDefaultValues(idDataGroup);
}

//******************************************************************************
SEVERITY DefFundAlloc::initExisting (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   attachDataObject( const_cast< BFData & >( data ), false, true ); 

   setFundNumber(BF::HOST);//because ToFundNumber doesn't come from the host
   loadSubstitutions( BF::HOST);
   setAllocFields(BF::HOST);
   if (!isClassRequired(BF::HOST))
      setFieldRequired(ifds::ClassCode, BF::HOST, false);
   setAllFieldsValid (BF::HOST);

   setFieldReadOnly (ifds::FELComm, BF::HOST, !isRESPFELCommApplicable (BF::HOST));

   //IN2818924 - DSK_AMS Validation for CDIC
   //AMSCODE 0001, disable editing base on BANKRUPTCY
   DString dstrFundCode, 
      dstrClassCode;

   getField (ifds::FundCode, dstrFundCode, BF::HOST);
   getField (ifds::ClassCode, dstrClassCode, BF::HOST);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   if(isFieldsDisabledBaseOnRuleType(dstrFundCode, dstrClassCode, BANKRUPTCY, BF::HOST))
   {
	   m_bBankruptcyApplied = true;
	   setFieldReadOnly( ifds::FundCode,BF::HOST,        true );
	   setFieldReadOnly( ifds::ClassCode,BF::HOST,       true );
	   setFieldReadOnly( ifds::ToFundNumber,BF::HOST,    true );
   }

   clearUpdatedFlags( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAlloc::getSplitCommissionList ( SplitCommissionList *&pSplitCommissionList, const BFDataGroupId& idDataGroup, 
                                                bool bCreate /*= true*/,
                                                bool bGetDefault /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSplitCommissionList" ) );

	pSplitCommissionList = NULL;//no split commissions for default allocations

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAlloc::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( FundAlloc::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField != ifds::TransType && idField != ifds::EffectiveDate && idField != ifds::AccountNum
       && idField != ifds::FundCode && idField != ifds::ClassCode && idField != ifds::ToFundNumber
       && idField != ifds::AllocPercentage && idField != ifds::FundGroup && idField != ifds::FELComm)
      setUpdatedFlag(idField, idDataGroup, false);

   if (idField == ifds::TransType)
   {
      transTypeRelChanges (idDataGroup);
   }

	// if user changes the fund allocation of an existing AMS, and it is in effect, UpdatePACSWP
   // combobox should be enabled.
   if( idDataGroup != BF::HOST )
   {
	   MFAccount *pMFAccount=NULL;
	   if( getMFAccount(pMFAccount, idDataGroup) > WARNING || !pMFAccount )
		   return(GETCURRENTHIGHESTSEVERITY());

	   if( pMFAccount->isAMSAccount( idDataGroup ) )
	   {
		   AMSAcctLvl *pAMSAcctLvl = dynamic_cast <AMSAcctLvl*>(getParent()->getParent()->getParent()->getParent()->getParent()->getParent());
		   if( pAMSAcctLvl != NULL )
		   {
			   DString dstrCurrentBusinessDate, dstrEffecDate, dstrStopDate;
			   getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false );

			   pAMSAcctLvl->getField (ifds::Deff, dstrEffecDate, idDataGroup, false);
			   pAMSAcctLvl->getField (ifds::StopDate, dstrStopDate, idDataGroup, false);
			   if( ( DSTCommonFunctions::CompareDates (dstrEffecDate, dstrCurrentBusinessDate) == DSTCommonFunctions::FIRST_EARLIER ||
				   DSTCommonFunctions::CompareDates (dstrEffecDate, dstrCurrentBusinessDate) == DSTCommonFunctions::EQUAL)  && 
				   ( DSTCommonFunctions::CompareDates (dstrCurrentBusinessDate, dstrStopDate) == DSTCommonFunctions::FIRST_EARLIER ||
				   DSTCommonFunctions::CompareDates (dstrCurrentBusinessDate, dstrStopDate) == DSTCommonFunctions::EQUAL) )
			   {
				   pAMSAcctLvl->setFieldReadOnly( ifds::UpdatePACSWP,    idDataGroup,  FALSE ); 
				   pAMSAcctLvl->setFieldReadOnly( ifds::Rebalance,    idDataGroup,  FALSE );
			   }
		   }
	   }
   }

   if (!isRESPFELCommApplicable (idDataGroup))
   {      
      setFieldNoValidate (ifds::FELComm, I_("0.00"), idDataGroup, false, false, true, false);
      setFieldReadOnly (ifds::FELComm, idDataGroup, true);
   }
   else
   {
      // Field is not readonly
      setFieldReadOnly (ifds::FELComm, idDataGroup, false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY DefFundAlloc::transTypeRelChanges (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "transTypeRelChanges" ) );

   if (isClassRequired (idDataGroup))
   {
      setFieldRequired (ifds::ClassCode, idDataGroup, true);
      setValidFlag (ifds::ClassCode, idDataGroup, false);
   }
   else
   {
      setFieldRequired (ifds::ClassCode, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY DefFundAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( FundAlloc::doValidateField( idField, strValue, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::FundCode )
      validateFundCode( strValue, idDataGroup );
   else if( idField == ifds::ClassCode )
      validateClassCode( strValue, idDataGroup );
   else if( idField == ifds::FundClass )
      validateFundClass ( idDataGroup );
   else if( idField == ifds::AcctTradeType )
      validateTransTypeFundClass(idDataGroup);
   else if ( idField == ifds::FundGroupCE )
      validateFundClassInGroup(idDataGroup);
   else if ( idField == ifds::FundGroupCode )
      validateFundInGroup(idDataGroup);
   else if ( idField == ifds::ClassE )
      validateClassType(idDataGroup);
   else if ( idField == ifds::FundType )
      validateFundType(idDataGroup);
   else if ( idField == ifds::FundClassTradeType )
      validateFundClassType(idDataGroup);
   else if ( idField == ifds::AllocPercentage )
      validateAllocPercentage( idDataGroup );
   else if ( idField == ifds::FELCommFundClass )
      validateFeeFund( idDataGroup ); 
   else if ( idField == ifds::TransType )
	  validateTransType( idDataGroup ); 

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAlloc::validateFundCode( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );
   //validation for blank fund and isFundExist in FundMasterList is already done by FundAlloc superclass

   DString dstrFundCode( strValue );
   dstrFundCode.strip().upperCase();

   //cash fund code is invalid for default fund allocations
   if( dstrFundCode == I_( "CASH" ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAlloc::validateClassCode( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClassCode" ) );

   //validation against blank class (whenever applicable) is done by FundAlloc
   
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY DefFundAlloc::validateFundClassType(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClassType" ) );

   DString dstrClassCode, dstrTransType, dstrFundCode;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   getField(ifds::FundCode,  dstrFundCode,  idDataGroup, false);
      
   //for FC rebalancing
   if( dstrTransType.strip().upperCase() == FOREIGN_CONTENT_REBALANCING)
   {
      FundDetail *pFundDetail = NULL;
      if( getFundDetail( dstrFundCode.strip().upperCase(), dstrClassCode.strip().upperCase(), 
         pFundDetail )>WARNING || !pFundDetail )
         return(GETCURRENTHIGHESTSEVERITY());

      //1. fund has to be domestic
      DString dstrDomestic;
      pFundDetail->getField( ifds::Domestic, dstrDomestic, idDataGroup, false);
      if( dstrDomestic.strip() == NO )
         ADDCONDITIONFROMFILE( CND::ERR_INPUT_FUND_DOMESTIC );
      //2. fund and class must be FC rebalancing eligible
      DString dstrFCTransferElig = YES;
      pFundDetail->getField( ifds::FCTransferElig, dstrFCTransferElig, idDataGroup );
      if( dstrTransType == FOREIGN_CONTENT_REBALANCING && dstrFCTransferElig == NO )
      {
         DString idiStr;
         addIDITagValue( idiStr, I_("FUND"), dstrFundCode );
         ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_NOT_ELIGIBLE_FCTRFR, idiStr );
      }
      //3. StopSysGenTrnfrIn should be 'Y' (fund/class shouldn't have AutoXferInStop flag set to 'N')
      DString dstrXferInStop;
      pFundDetail->getField( ifds::StopSysGenTrnfrIn, dstrXferInStop, idDataGroup, false);
      if( dstrXferInStop.strip() == YES )
      {
         DString idiStr;
         addIDITagValue( idiStr, I_("FUND"), dstrFundCode );
         addIDITagValue( idiStr, I_("CLASS"), dstrClassCode );
         ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_SYSGENTRFIN_STOP_FLAG_ON, idiStr );
      }
   }
   else if (dstrTransType.strip().upperCase() == REBALANCE)
   {
      FundDetail *pFundDetail;
      getFundDetail( dstrFundCode, dstrClassCode, pFundDetail );
      if(pFundDetail )
      {
          if(getWorkSession().isMasterActWithOneChild(idDataGroup))
          {
              if (pFundDetail->isAMSParentFund(idDataGroup) || pFundDetail->isAMSChildFund(idDataGroup))
              {
                  getErrMsg(IFASTERR::ACCOUNT_AMS_MODEL_CANNOT_HOLD_GLOBAL_MODEL_FUNDS,
                            CND::ERR_ACCOUNT_AMS_MODEL_CANNOT_HOLD_GLOBAL_MODEL_FUNDS,
                            CND::WARN_ACCOUNT_AMS_MODEL_CANNOT_HOLD_GLOBAL_MODEL_FUNDS,
                            idDataGroup);
              }
          }

          DString dstrAMSFund;
          pFundDetail->getField(ifds::AMSEligible,dstrAMSFund,idDataGroup,false );
          if (dstrAMSFund.strip().upperCase() == NO)
          {
              DString idiStr;
              addIDITagValue( idiStr, I_( "FUNDNAME" ),  dstrFundCode.strip() );
              addIDITagValue( idiStr, I_( "CLASSNAME" ), dstrClassCode.strip() );
              ADDCONDITIONFROMFILEIDI( CND::ERR_AMS_FUND_CLASS_INVALID, idiStr );
              return(GETCURRENTHIGHESTSEVERITY());
          }
      }
   }
   else if ( dstrTransType.strip().upperCase() == REPORT_ONLY	)
   {
      //This enhacement make frank russel doesn't work, May 15, 2003
      //To make frank russel work, winnie and shaobo agree the change for checking frank russel default type also.
      FundGroupTypeList *pFundGroupTypeList = NULL;
      bool fundclassexist = false;
      if(getMgmtCo().getFundGroupTypeList( pFundGroupTypeList, DEFAULT_AMS_TYPE ) <= WARNING )
      {
         if (pFundGroupTypeList)
         {
            if (pFundGroupTypeList->isFundClassExist(
               dstrFundCode.strip().upperCase(), dstrClassCode, DEFAULT_AMS_TYPE, DEFAULT_AMS_GROUP_CODE) )
            {
               fundclassexist = true;
            }
         }
      }
      if(!fundclassexist && getMgmtCo().getFundGroupTypeList( pFundGroupTypeList, DEFAULT_AMS_TYPE_FRK ) <= WARNING )
      {
         if (pFundGroupTypeList)
         {
            if (pFundGroupTypeList->isFundClassExist(
               dstrFundCode.strip().upperCase(), dstrClassCode, DEFAULT_AMS_TYPE_FRK, DEFAULT_AMS_GROUP_CODE_FRK) )
            {
               fundclassexist = true;
            }
         }
      }
      if(!fundclassexist)
      {
         DString idiStr;
         addIDITagValue( idiStr, I_( "FUNDNAME" ),  dstrFundCode.strip() );
         addIDITagValue( idiStr, I_( "CLASSNAME" ), dstrClassCode.strip() );
         ADDCONDITIONFROMFILEIDI( CND::ERR_AMS_FUND_CLASS_INVALID, idiStr );
         return(GETCURRENTHIGHESTSEVERITY());
      }
   }
   else if ( isBrokerFundValidationApplicable( dstrTransType, idDataGroup ) )
   {
      MFAccount *pMFAccount=NULL;
      if( getMFAccount(pMFAccount, idDataGroup) > WARNING || !pMFAccount )
         return(GETCURRENTHIGHESTSEVERITY());

      DString dstrBrokerCode;
      pMFAccount->getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup);
        
      if ( !dstrFundCode.empty() && !dstrClassCode.empty() )
      {
         // Check Broker eligible for fund
         if ( validateBrokerFund ( dstrBrokerCode, 
                                   dstrTransType, 
                                   NULL_STRING, 
                                   dstrFundCode, 
                                   dstrClassCode, 
                                   idDataGroup ) > WARNING )
         {
            // raise up condition
            ADDCONDITIONFROMFILE( CND::ERR_DEALER_NOT_ELIGIBLE_FOR_FUND_CLASS );
         }

      }	// end if fund and class not empty

   }	// end Validations of RESP GRANT Commission Project

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAlloc::validateClassType(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClassType" ) );

   DString dstrClassCode, dstrTransType;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

   //for FC rebalancing
   //class must be blank
   if( dstrTransType.strip().upperCase() == FOREIGN_CONTENT_REBALANCING)
   {
      DString strClassReq;
      getWorkSession().getOption(ifds::ClassRule, strClassReq, BF::HOST, false);
      if (strClassReq == CLASS_MUST_BE_BLANK && !dstrClassCode.empty())
         ADDCONDITIONFROMFILE( CND::ERR_CLASS_CODE_MUST_BE_BLANK );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAlloc::validateFundType(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundType" ) );

   DString dstrFundCode, dstrTransType;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   if (isClassRequired(idDataGroup))
   {
      //only Fund, Class, Transtype validations which do not depend on AccountNum and/or EffectiveDate should go in here
      DString dstrClassCode;
      getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

      return(GETCURRENTHIGHESTSEVERITY());
   }
   //only Fund and Type validations should go in here which do NOT depend on Class and any other fields

   FundMasterList *pFundMasterList = NULL;
   FundDetailList *pFundDetailList = NULL;
      // for FC rebal, 
   if( dstrTransType.strip().upperCase() == FOREIGN_CONTENT_REBALANCING )
   {
         //1.Fund must be domestic
      if( getMgmtCo().getFundMasterList(pFundMasterList)<=WARNING && pFundMasterList )
      {
         FundMaster* pFundMaster = NULL;
         if ( pFundMasterList->getFundMaster( dstrFundCode.strip().upperCase(), idDataGroup, pFundMaster) 
            && pFundMaster )
         {

            DString strDomestic = YES;
            pFundMaster->getField(ifds::Domestic, strDomestic, BF::HOST, false);
            if( strDomestic.strip() == NO )
               ADDCONDITIONFROMFILE( CND::ERR_INPUT_FUND_DOMESTIC );
         }
      }

      if( getMgmtCo().getFundDetailList(pFundDetailList)<=WARNING && pFundDetailList )
      {
         //2. Fund must be FC transfer eligible
         if (!pFundDetailList->isFundFCRebalElig(dstrFundCode))
         {
            DString idiStr;
            addIDITagValue( idiStr, I_("FUND"), dstrFundCode );
            ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_NOT_ELIGIBLE_FCTRFR, idiStr );
         }
         //3. StopSysGenTrnfrIn should be 'N' for at least one fund/class 
         if (pFundDetailList->isStopSysGenTrfrIn(dstrFundCode))
         {
            DString idiStr;
            addIDITagValue( idiStr, I_("FUND"), dstrFundCode );
            ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_SYSGENTRFIN_STOP_FLAG_ON, idiStr );
         }
      }
   }

     
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DefFundAlloc::validateFundClass( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );
   DString dstrClassCode, dstrFundCode;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

   //if ( !(getFundDetail( dstrFundCode, dstrClassCode, pFundDetail )) )
   //   ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES ); ------->  done by FundAlloc, whenever applicable

   //if validation requires the account number, transType and/or effective date, 
   //it should also go into validateTransTypeFundClass()
   

   //IN2818924 - DSK_AMS Validation for CDIC
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   if(isFieldsDisabledBaseOnRuleType(dstrFundCode, dstrClassCode, BANKRUPTCY, idDataGroup))
   {
	  DString idiStr;  
      addIDITagValue( idiStr, I_("TRADE_TYPE"), I_(" ") );
      addIDITagValue( idiStr, I_("FUND"), dstrFundCode );
      addIDITagValue( idiStr, I_("CLASS"), dstrClassCode );
      ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_STOP_FLAG_ON, idiStr );

   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAlloc::validateFundClassInGroup(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClassInGroup" ) );

   DString dstrClassCode, dstrFundCode, dstrTransType;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   getField(ifds::TransType, dstrTransType, idDataGroup, false);

   if( !dstrClassCode.strip().upperCase().empty() && 
      dstrTransType.strip().upperCase() == FOREIGN_CONTENT_REBALANCING &&
      isClassRequired(idDataGroup) )
   {
      DString idiStr, dstrGroupCode, dstrGroupName;
      getField(ifds::FundGroup, dstrGroupCode, idDataGroup, false);
      getParent()->getParent()->getField(ifds::FundGroup, dstrGroupName, idDataGroup, true);
      addIDITagValue( idiStr, I_("GROUP_CODE"), dstrGroupName );

      FundGroupTypeList* pFundTypeList = NULL;
      if( !dstrGroupCode.strip().empty() && getMgmtCo().getFundGroupTypeList(pFundTypeList, DEFAULT_AMS_TYPE_REBAL)<=WARNING 
		  && pFundTypeList )
      {
         if ( !pFundTypeList->isFundClassExist(
              dstrFundCode.strip().upperCase(), dstrClassCode, DEFAULT_AMS_TYPE_REBAL, dstrGroupCode.strip()) )
         {
            ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_MUST_BE_IN_GROUP, idiStr);  
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAlloc::validateFundInGroup(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundInGroup" ) );

   DString dstrClassCode, dstrFundCode, dstrTransType;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   //Fund must be in group
   if( dstrTransType.strip().upperCase() == FOREIGN_CONTENT_REBALANCING )
   {
      DString idiStr, dstrGroupCode, dstrGroupName;
      getField(ifds::FundGroup, dstrGroupCode, idDataGroup, false);
      getParent()->getParent()->getField(ifds::FundGroup, dstrGroupName, idDataGroup, true);
      addIDITagValue( idiStr, I_("GROUP_CODE"), dstrGroupName );

      FundGroupTypeList* pFundTypeList = NULL;
      if( !dstrGroupCode.strip().empty() && getMgmtCo().getFundGroupTypeList(pFundTypeList,DEFAULT_AMS_TYPE_REBAL)<=WARNING 
		  && pFundTypeList )
      {
         if ( !pFundTypeList->isFundExist(dstrFundCode, DEFAULT_AMS_TYPE_REBAL, dstrGroupCode.strip()) )
         {
            ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CODE_MUST_BE_IN_GROUP, idiStr);  
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefFundAlloc::validateTransTypeFundClass( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   MFAccount *pMFAccount=NULL;
   if( getMFAccount(pMFAccount, idDataGroup) > WARNING || !pMFAccount )
      return(GETCURRENTHIGHESTSEVERITY());

   FundDetail *pFundDetail = NULL;
   DString dstrTransType, dstrTaxType, dstrFundCode, dstrClassCode, dstrEffectiveDate;

   getField( ifds::FundCode, dstrFundCode, idDataGroup, false );
   dstrFundCode.strip();
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrClassCode.strip();
   getField( ifds::TransType, dstrTransType, idDataGroup );
   dstrTransType.strip().upperCase();
   getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
   pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup );

   //*********** Effective Date related **************//

   DString idiStr;
   addIDITagValue( idiStr, FUNDNAME1, dstrFundCode );
   addIDITagValue( idiStr, CLASSNAME1, dstrClassCode );
   FundMasterList *pFundMasterList = NULL;
   if( getMgmtCo().getFundMasterList(pFundMasterList)<=WARNING && pFundMasterList )
      if( !(pFundMasterList->IsFundValidAtDate ( dstrFundCode, dstrEffectiveDate, idDataGroup) ) )
         ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_EFFECTIVE, idiStr );

   if( getFundDetail( dstrFundCode, dstrClassCode, pFundDetail )>WARNING || !pFundDetail )
      return(GETCURRENTHIGHESTSEVERITY());

   if( !(pFundDetail->IsFundValidAtDate ( dstrEffectiveDate, idDataGroup)) )
   {
      DString idiStr;
      addIDITagValue( idiStr, FUNDNAME1, dstrFundCode );
      addIDITagValue( idiStr, CLASSNAME1,dstrClassCode );

      ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_EFFECTIVE, idiStr ); 
   }

   // validate fund/class in group 
   if( pMFAccount->fundClassInGroup ( dstrFundCode, dstrClassCode, dstrEffectiveDate, idDataGroup) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   //*********** TransType related **************//

   // if contribution, check if GIC fund is allowed for the tax type of the account
   if( DSTCommonFunctions::codeInList( dstrTransType, PURCHASECODELIST ) )
   {
      pMFAccount->purchaseGICAllow ( dstrFundCode, idDataGroup);
   }

   if( dstrFundCode == I_("CASH") && !( dstrTransType == I_("FM") && dstrTaxType != I_("7") ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_CASH_FUND_NOT_ALLOWED );
   }

   /*How could this code work? For a new allocation FrngSweep is always blank
   and for an existing allocation it will have an incorrect value when user changes the fund and/or class
   DString dstrFrgnSweepFund;
   getField( ifds::FrngSweep, dstrFrgnSweepFund, idDataGroup );
   if( dstrTransType == FOREIGN_CONTENT_REBALANCING && dstrFrgnSweepFund == NO )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FOR_FOREIGN_CONTENT_TRANSFER );
   }*/

   DString dstrSysCurrency;
   getWorkSession().getOption( ifds::SysCurrency, dstrSysCurrency, idDataGroup, false ); 
   // Getting Domestic and Currency.
   DString dstrTradeType = NULL_STRING;   
   DString dstrDomestic(I_("")), dstrCurrency;

   pFundDetail->getField( ifds::Domestic, dstrDomestic, idDataGroup, false);
   pFundDetail->getField( ifds::Currency, dstrCurrency, idDataGroup, false);
   //the following code has been moved to validateFundClassType, since it does not depend on EffectiveDate and AccountNum
   /*if( dstrTransType == FOREIGN_CONTENT_REBALANCING && dstrDomestic.strip() == NO )
      ADDCONDITIONFROMFILE( CND::ERR_INPUT_FUND_DOMESTIC );*/

   if( dstrTransType == FOREIGN_CONTENT_REBALANCING && dstrCurrency.strip() != dstrSysCurrency.strip() )
   {
      DString idiStr;
      addIDITagValue( idiStr, I_("SYS_CURRENCY"), dstrSysCurrency );
      addIDITagValue( idiStr, I_("CURRENCY"), dstrCurrency );
      ADDCONDITIONFROMFILEIDI( CND::ERR_CURRENCY_SHOULD_BE_SAME, idiStr);   
   }

   //check the stop flag
   bool bStopFlag (false);

   if( DSTCommonFunctions::codeInList( dstrTransType, PURCHASECODELIST ) )
   {
      DString stopPurchase;
      
      pFundDetail->getField (ifds::StopPurchase, stopPurchase, idDataGroup, false);
      stopPurchase.strip().upperCase();
      bStopFlag = stopPurchase == YES;
   }
   else if( DSTCommonFunctions::codeInList( dstrTransType, REDEMPTIONCODELIST ) )
   {
      DString stopRed;
      
      pFundDetail->getField (ifds::StopRed, stopRed, idDataGroup, false);
      stopRed.strip().upperCase();
      bStopFlag = stopRed == YES;
   }
   else if( DSTCommonFunctions::codeInList( dstrTransType, TRANSFERCODELIST ) )
   {
      DString stopXferIn;
      
      pFundDetail->getField (ifds::StopXferIn, stopXferIn, idDataGroup, false);
      stopXferIn.strip().upperCase();
      bStopFlag = stopXferIn == YES;
   }
   if (bStopFlag)
   {
      DString idiStr, dstrFormatTransType;
      getField ( ifds::TransType, dstrFormatTransType, idDataGroup, true );     
      addIDITagValue( idiStr, TRADE_TYPE, dstrFormatTransType );
      addIDITagValue( idiStr, I_("FUND"), dstrFundCode );
      addIDITagValue( idiStr, I_("CLASS"), dstrClassCode );
      ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_STOP_FLAG_ON, idiStr );
   }

   //*********** TaxType related **************//

   if( dstrTaxType == I_("7") &&  
       !( ( dstrFundCode == I_("CASH") && dstrTransType == I_("FM") ) || 
          pFundMasterList->isGICFund( dstrFundCode )) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ONLY_GIC_PURCHASES_ALLOWED );
   }

   //*********** other validations **************//

   // check if AMSCode feature is active; if account is an AMS account, check if the input fund is AMS fund
   pMFAccount->AMSFundAllow ( dstrFundCode, dstrClassCode, idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefFundAlloc::validateAllocPercentage(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAllocPercentage" ) );

   DString dstrTransType, dstrAllocPercentage;
   getField( ifds::TransType, dstrTransType, idDataGroup, false );

   if( dstrTransType == MANAGEMENT_FEE_CODE )
   {
      getField( ifds::AllocPercentage, dstrAllocPercentage, idDataGroup, false );
      double dAllocPercentage = DSTCommonFunctions::convertToDouble ( dstrAllocPercentage );
      if( dAllocPercentage != 100.0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_FUND_ALLOC_ONE_FUND_ONLY );  // ERR_FUND_ALLOC_ONE_FUND_ONLY
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefFundAlloc::loadSubstitutions( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadSubstitutions" ) );

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN )
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::rxTransTypeJapanese );
   else  // for Canada and any other market
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::rxTransType);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAlloc::setAllocFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAllocFields" ) );

   FundAlloc::setAllocFields(idDataGroup);

   AbstractAllocList *pParentList = getParentList();
   DString str;
   pParentList->getField(ifds::FundGroup, str, idDataGroup, false);
   if( !str.strip().empty() )
      setField(ifds::FundGroup, str, idDataGroup, false);//no validate?
   
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool DefFundAlloc::isClassRequired(const BFDataGroupId& idDataGroup)
{
   DString dstrTransType, strClassReq;
   getField( ifds::TransType, dstrTransType, idDataGroup );
   if (dstrTransType.strip().upperCase() == FOREIGN_CONTENT_REBALANCING)
   {
      getWorkSession().getOption(ifds::ClassRule, strClassReq, BF::HOST, false);
      if (strClassReq != CLASS_MUST_BE_SUPPLIED)
         return false;
   }
   return true;
}
//******************************************************************************

bool DefFundAlloc::isFundGroupApplicable(const BFDataGroupId& idDataGroup)
{
   //XSFundsValidate has to be set to YES
   DString strFundGroupApplic = NO;
   getWorkSession().getOption( ifds::XSFundsValidate , strFundGroupApplic, BF::HOST, false );
   if (strFundGroupApplic.strip() != YES)
      return false;

   //allocation type has to be FOREIGN_CONTENT_REBALANCING
   DString strTransType;
   getField( ifds::TransType, strTransType, idDataGroup, false);
   if (strTransType.strip() != FOREIGN_CONTENT_REBALANCING)
      return false;

   return true;
}
//******************************************************************************

SEVERITY DefFundAlloc::validateFeeFund( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeFund" ) );

   if (isRESPFELCommApplicable (idDataGroup))
   {
      DString strFELComm, strMin, strMax;
      AcqFeeInquiry *pAcqFeeInquiry = NULL;
      if ( getAcqFeeInquiry( pAcqFeeInquiry, idDataGroup) <= WARNING && pAcqFeeInquiry )
      {
         // Min and Max Fee always be Percent, from RESP GRANT Commission project
         DString strMaxFeeActive;
         pAcqFeeInquiry->getField(ifds::MaxFeeActive, strMaxFeeActive, idDataGroup, false); // get From VEW121

         if ( strMaxFeeActive == YES )
         {
            pAcqFeeInquiry->getField ( ifds::MinPercent, strMin, idDataGroup, false );
            pAcqFeeInquiry->getField ( ifds::MaxPercent, strMax, idDataGroup, false );
         }
         else
         {
            strMax = I_("100");
            strMin = I_("0");
         }

      } // end get AcqFeeInquiry
      else
      {
         assert(0);
      }
      // Checking Min and Max value of commission
      if ( !strMax.empty() && !strMin.empty() )
      {
         getField(ifds::FELComm, strFELComm, idDataGroup, false);
         
         double dMax = DSTCommonFunctions::convertToDouble( strMax );
         double dMin = DSTCommonFunctions::convertToDouble( strMin );
         double dFee = DSTCommonFunctions::convertToDouble( strFELComm );
         
         
         if ( dFee > dMax )	// if user enter commission more than max value
         {
            DString strIDI,strClassCode,strFundCode;
            getField(ifds::FundCode,  strFundCode,  idDataGroup, false);
            getField(ifds::ClassCode, strClassCode, idDataGroup, false);
            
            addIDITagValue( strIDI, I_("FUND"), strFundCode );
            addIDITagValue( strIDI, I_("CLASS"), strClassCode );
            ADDCONDITIONFROMFILEIDI( CND::ERR_FEE_MORE_THAN_MAX_RESP_GRANT, strIDI );
         }
         else if ( dFee < dMin )	  // if user enter commission less than min value
         {
            DString strIDI,strClassCode,strFundCode;
            getField(ifds::FundCode,  strFundCode,  idDataGroup, false);
            getField(ifds::ClassCode, strClassCode, idDataGroup, false);
            
            addIDITagValue( strIDI, I_("FUND"), strFundCode );
            addIDITagValue( strIDI, I_("CLASS"), strClassCode );
            ADDCONDITIONFROMFILEIDI( CND::ERR_FEE_LESS_THAN_MIN_RESP_GRANT, strIDI );
         }
       }// end if string empty
       else
       {
          //Invalid data
          assert(0);
        }
   } // end if isRESPFELCommApplicable

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefFundAlloc::getAcqFeeInquiry(AcqFeeInquiry *&pAcqFeeInquiry, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAcqFeeInquiry"));

      pAcqFeeInquiry = NULL;

   DString dstrTaxType, 
           dstrFundCode, 
           dstrClassCode, 
           dstrFundCurrency, 
           dstrBrokerCode;

   DString dstrTransType, 
           dstrEffectiveDate, 
           dstrAmount, 
           dstrAmountType, 
           dstrCurrency, 
           dstrFee, 
           dstrAccountNum;

   getField( ifds::TransType, dstrTransType, idDataGroup, false );
   getField( ifds::FundCode, dstrFundCode, idDataGroup, false );
   getField( ifds::ClassCode, dstrClassCode, idDataGroup, false );   
   
   dstrTransType.strip().upperCase();
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
    
   if( dstrFundCode == NULL_STRING || dstrClassCode == NULL_STRING )
   return(GETCURRENTHIGHESTSEVERITY());

   MFAccount *pMFAccount=NULL;
   if( getMFAccount( pMFAccount, idDataGroup) > WARNING || !pMFAccount )
   return(GETCURRENTHIGHESTSEVERITY());

   pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
   pMFAccount->getField( ifds::BrokerCode, dstrBrokerCode, idDataGroup, false );
   pMFAccount->getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );

   getField( ifds::EffectiveDate, dstrEffectiveDate,  idDataGroup, false );

   CurrencyClass::getFundCurrency( getWorkSession(), dstrFundCode, dstrClassCode, dstrFundCurrency);

   dstrFundCurrency.strip().upperCase();
   dstrTaxType.strip().upperCase();

   DString dstrKey = I_("AcqFeeInquiry;FundCode=")    + dstrFundCode
                   + I_(";ClassCode=")                + dstrClassCode
                   + I_(";FundCurrency=")             + dstrFundCurrency
                   + I_(";BrokerCode=")               + dstrBrokerCode
                   + I_(";FELCommType=")              + NO				// always be Percent
                   + I_(";EffectiveDate=")            + dstrEffectiveDate
                   + I_(";TransType=")                + dstrTransType
                   + I_(";TaxType=")                  + dstrTaxType
                   + I_(";Amount=")                   + I_("0")
                   + I_(";AmountType=")               + I_("D");
               

   pAcqFeeInquiry = 
      dynamic_cast<AcqFeeInquiry *> (BFCBO::getObject (dstrKey, idDataGroup));

   if( !pAcqFeeInquiry )
   {
      pAcqFeeInquiry = new AcqFeeInquiry ( *this );
      pAcqFeeInquiry->setFundCurrency(dstrFundCurrency);

      SEVERITY sevRtn = pAcqFeeInquiry->init( NULL_STRING,
                                             dstrTransType,
                                             dstrEffectiveDate,
                                             I_("0"),          // Amount
                                             I_("D"),          // AmountType
                                             dstrFundCode,
                                             dstrClassCode,
                                             dstrFundCurrency,
                                             dstrBrokerCode, 
                                             NULL_STRING,
                                             NULL_STRING,
                                             NO,               // always be Percent
                                             I_("N"),          // track default
                                             NULL_STRING ,     // activity default
                                             dstrTaxType ,// ToTaxType
											 dstrAccountNum);    
      if( sevRtn <= WARNING )
      {
         setObject( pAcqFeeInquiry, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
      }
      else
      {
         delete pAcqFeeInquiry;
         pAcqFeeInquiry = NULL;
      }
   }

   

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAlloc::validateBrokerFund ( const DString &dstrBroker,
                                            const DString &dstrTransType,
                                            const DString &dstrAccountNum,
                                            const DString &dstrFundCode, 
                                            const DString &dstrClassCode, 
                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBrokerFund"));

   DString dstrFundAllowed ( I_("Y"));
  
   if ( !dstrFundCode.empty() && !dstrClassCode.empty())
   {
      BrokerList brokerList (*this);

      if ( !dstrBroker.empty() &&
            brokerList.initFundAllowed ( dstrBroker, 
                                         dstrFundCode, 
                                         dstrClassCode, 
                                         dstrAccountNum, 
                                         dstrTransType) <= WARNING)
	  {
	     
		 BFObjIter bfIter (brokerList, idDataGroup);
         bfIter.begin ();
         if (!bfIter.end ())
         {
            // fundAllowed (FundAllow) indicates if the broker is allowed to trade the fund/class
            bfIter.getObject()->getField (ifds::FundAllow, dstrFundAllowed, idDataGroup);
            dstrFundAllowed.strip();
         }
	  
	  }
  
   }
   if (!isBrokerAllowed ( dstrTransType, dstrAccountNum, dstrFundCode, dstrClassCode, idDataGroup) && dstrFundAllowed != YES )
   {
      DString idiStr;
      addIDITagValue (idiStr, I_("FUND"), dstrFundCode);
      addIDITagValue (idiStr, I_("CLASS"), dstrClassCode);
      addIDITagValue (idiStr, I_("BROKER"), dstrBroker);
      ADDCONDITIONFROMFILEIDI ( CND::ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER, idiStr );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool DefFundAlloc::isBrokerAllowed ( const DString &dstrTransType,
                                     const DString &dstrAccountNum,
                                     const DString &dstrFundCode, 
                                     const DString &dstrClassCode,
                                     const BFDataGroupId &idDataGroup )
{
   //this implementation is overriden in redemption/transfer (for trsf out and in-kind)
   return false;
}

//******************************************************************************

bool DefFundAlloc::isFELCommGCOn(const BFDataGroupId& idDataGroup)
{
   bool bRetVal = false;
   DString strFELCommOnGrant;
   getWorkSession().getOption( ifds::FELCommOnGrant, strFELCommOnGrant, BF::HOST, false );
   if( strFELCommOnGrant == YES)
   {
	   bRetVal = true;
   }

   return bRetVal;
}

//******************************************************************************
bool DefFundAlloc::isRESPFELCommApplicable (const BFDataGroupId& idDataGroup)
{
   bool bRetVal = false;
	
   if (!isFELCommGCOn (idDataGroup))
	{
		return bRetVal;
	}

	DString strTransType, 
      strFundCode, 
      strClassCode, 
      strLoadType;

   getField (ifds::TransType, strTransType, idDataGroup);
   getField (ifds::FundCode, strFundCode, idDataGroup);
   getField (ifds::ClassCode, strClassCode, idDataGroup);
   strTransType.strip().upperCase();
   strFundCode.strip().upperCase();
   strClassCode.strip().upperCase();

   FundDetail *pFundDetail (NULL);
   
   if ( getFundDetail (strFundCode, strClassCode, pFundDetail) <= WARNING && 
        pFundDetail)
   {
      pFundDetail->getField (ifds::LoadType, strLoadType, BF::HOST, false);
      
      if ( DSTCommonFunctions::codeInList (strTransType, FEL_COMM_APPLICABLE) &&
		     strLoadType == FRONT_END_LOAD)
      {
         bRetVal = true;
      }
   }
   return bRetVal;
}

//******************************************************************************

bool DefFundAlloc::isBrokerFundValidationApplicable(const DString &dstrTransType, const BFDataGroupId& idDataGroup)
{
   bool bRetVal = false;
   DString strTransType(dstrTransType);
   //get AllocType for Broker/Fund Validation list 
   DString strAllocTransTypeList;
   getWorkSession().getOption( ifds::AllocTypeForBrokerValidation, strAllocTransTypeList, BF::HOST, false );
   if( !strAllocTransTypeList.upperCase().empty() && 
	           DSTCommonFunctions::codeInList( strTransType.strip().upperCase(), strAllocTransTypeList ) )
   {
      bRetVal = true;
   }
   return bRetVal;
}
//****************************************************************************
//IN2818924 - DSK_AMS Validation for CDIC
SEVERITY DefFundAlloc::getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList,
                                              const DString& transType,
                                              const DString& fundCode,
                                              const DString& classCode,
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFundLmtOverrideList"));

   pFundLmtOverrideList = NULL;
   
   DString strKey;
   
   strKey = I_("FundLmtOverrideList");
   strKey += I_(";TransType=");
   strKey += transType;
   strKey += I_(";FundCode=");
   strKey += fundCode;   
   strKey += I_(";ClassCode=");
   strKey += classCode;   
   pFundLmtOverrideList = 
      dynamic_cast<FundLmtOverrideList *>(BFCBO::getObject(strKey, idDataGroup));

   if (!pFundLmtOverrideList )
   {
      pFundLmtOverrideList = new FundLmtOverrideList (*this);
      if (pFundLmtOverrideList->init (fundCode, classCode, transType) <= WARNING)
      {
         setObject (pFundLmtOverrideList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
      }
      else
      {
         delete pFundLmtOverrideList;
         pFundLmtOverrideList = NULL;
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//IN2818924 - DSK_AMS Validation for CDIC
bool DefFundAlloc::isFieldsDisabledBaseOnRuleType( const DString& fundCode,
											    const DString& classCode,
												const DString& ruleType, 
                                                const BFDataGroupId &idDataGroup)
{
   DString transType(I_("AMS")),
	   strAccountNum;

   getField(ifds::AccountNum,strAccountNum,idDataGroup,false);

   strAccountNum.strip();

   bool bReadOnlyBaseOnRuleType = false;
 
   FundLmtOverrideList *pFundLmtOverrideList = NULL;

   if(!fundCode.empty() && !classCode.empty())
   {
	   getFundLmtOverrideList(pFundLmtOverrideList,
		   transType,
		   fundCode,
		   classCode,
		   idDataGroup);

	   FundLmtOverride *pFundLmtOverride = NULL;
	   if ( pFundLmtOverrideList != NULL &&
		   pFundLmtOverrideList->getFundLmtOverride ( getWorkSession(), 
		   strAccountNum, 
		   ruleType, 
		   pFundLmtOverride, 
		   idDataGroup) <= WARNING && 
		   pFundLmtOverride)
	   {
		   // disable fields
		   DString stopFlag;
		   pFundLmtOverride->getField (ifds::StopFlag, stopFlag, idDataGroup, false);
		   stopFlag.strip().upperCase();

		   bReadOnlyBaseOnRuleType = stopFlag == I_("Y");
	   }
   }

   return bReadOnlyBaseOnRuleType;
}

//******************************************************************************

SEVERITY DefFundAlloc::validateTransType( const BFDataGroupId& idDataGroup ) 
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTransType" ) );

	DString transType;
	getField (ifds::TransType, transType, idDataGroup);
	transType.stripAll();

	if (DSTCommonFunctions::codeInList (transType, I_("SG,SR")))
	{
		getErrMsg (IFASTERR::ALLOCATION_OPTION_NOT_AVAILABLE, 
			CND::ERR_ALLOCATION_OPTION_NOT_AVAILABLE, 
			CND::WARN_ALLOCATION_OPTION_NOT_AVAILABLE, 
			idDataGroup);
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefFundAlloc.cpp-arc  $
// 
//    Rev 1.41   Apr 24 2012 20:59:18   wp040039
// PETP0187485 - Trade Entry And Processing
// 
//    Rev 1.40   Jan 31 2012 07:19:22   panatcha
// IN2818924 - DSK_AMS Validation for CDIC
// 
//    Rev 1.39   Apr 30 2010 17:34:28   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU - Fixed FEL Comm fee applicable
// 
//    Rev 1.38   Apr 26 2010 18:17:34   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU - Fixed FEL Comm fee applicable
// 
//    Rev 1.37   Apr 26 2010 17:53:58   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU - Fixed FEL Comm fee applicable
// 
//    Rev 1.36   Apr 05 2010 14:45:24   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.35   Jan 20 2009 01:53:20   sopitwek
// PET22486 FN03 IN1555932 - Issues on the field FeeComm
// 
//    Rev 1.34   Jan 19 2009 23:26:06   sopitwek
// PET22486 FN03 IN1555932 - Field FeeComm should not be updatable for Low Load or BEL funds.
// 
//    Rev 1.33   16 Dec 2008 13:58:42   kovacsro
// PET22486 - FN03 - RESP Grant Commission - code review
// 
//    Rev 1.32   16 Dec 2008 09:34:18   kovacsro
// PET22486 - FN03 - RESP Grant Commission - code review
// 
//    Rev 1.31   Dec 11 2008 09:27:34   sopitwek
// PET22486 - FN03 - RESP Grant Commission
// 
//    Rev 1.30   Nov 17 2008 01:00:10   daechach
// restored rev.1.28
// 
//    Rev 1.29   Nov 11 2008 05:00:18   phiwponp
// IN 1416918 - Unable to select fund 028 CA as allocation fund.
// 
//    Rev 1.28   03 Jun 2008 15:40:34   kovacsro
// restored rev. 1.26
// 
//    Rev 1.27   30 May 2008 16:25:36   kovacsro
// PET6873 - Cut Off Time
// 
//    Rev 1.26   Feb 15 2008 10:51:44   yingz
// more to 1101619, make rebalance flag behaves the same as updatepacswp flag
// 
//    Rev 1.25   Feb 12 2008 15:56:50   yingz
// fix 1101619 - When submit the modification of Acct level AMS code or AMS allocation, user has a choice to refresh the existing PAC with the same allocation. The refresh should be done with the effective AMS allcation
// 
//    Rev 1.24   Nov 14 2004 14:30:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.23   Nov 06 2004 00:40:08   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.22   Jun 25 2004 16:37:54   popescu
// PST 10031525, fund limitation override issues
// 
//    Rev 1.21   May 11 2004 15:49:14   popescu
// PET 985, FN 01, LSIF Trade Entry, added handy methods to fund master list, to check whether a fund is LSIF/Money Market, GIC
// 
//    Rev 1.20   Apr 16 2004 16:39:44   VADEANUM
// PET1005 FN11 - AMS Gaps for 56.1- added AMSEligible to view 56 and replaced AMSFund as per Winnie's email.
// 
//    Rev 1.19   Jun 19 2003 16:45:06   HERNANDO
// PTS 10018533 - Added Class Code to Condition Message.
// 
//    Rev 1.18   Jun 12 2003 11:44:34   FENGYONG
// if fail to get fundgrouplist, treat it the same as failed to find fundclass exist in it
// 
//    Rev 1.17   Jun 12 2003 10:38:24   FENGYONG
// fix
// 
//    Rev 1.16   Jun 11 2003 13:47:24   FENGYONG
// 10018204
// 
//    Rev 1.15   May 14 2003 12:03:28   FENGYONG
// 10017087 frank russell
// 
//    Rev 1.14   Apr 25 2003 14:26:12   HERNANDO
// Prudential Broker Level Fee - PET792.FN07.2 - Added validateAllocPercentage.
// 
//    Rev 1.13   Apr 15 2003 10:46:10   linmay
// Sync up with 1.11.2.0
// 
//    Rev 1.12   Mar 21 2003 19:44:20   PURDYECH
// Sync 1.11.1.0 back to trunk
// 
//    Rev 1.11.1.0   Mar 21 2003 18:02:56   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.11   Jan 14 2003 17:26:48   KOVACSRO
// Added validations for FCRebal.
// 
//    Rev 1.10   Jan 13 2003 10:56:56   KOVACSRO
// Name change : FundType into FundGroupType
// 
//    Rev 1.9   Jan 12 2003 18:37:10   KOVACSRO
// Added FundGroup logic for FC rebalancing
// 
//    Rev 1.8   Dec 04 2002 16:17:50   KOVACSRO
// As Winnie asked, we'll keep double names for trans type (see AMS Trade & Systematic ESS, ver. 1.1) 
// 
//    Rev 1.6   Nov 12 2002 11:25:50   KOVACSRO
// getSplitCommissionList should only return a NULL pointer if not applicable. No assert is necessary.
// 
//    Rev 1.5   Oct 09 2002 23:54:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:55:16   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   Aug 06 2002 10:01:16   KOVACSRO
// Release 48. 
// 
//    Rev 1.2   22 May 2002 18:26:46   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   12 Apr 2002 16:55:58   KOVACSRO
// More implementation.
 * 
 * 
 */