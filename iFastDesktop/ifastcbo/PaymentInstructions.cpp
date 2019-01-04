//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : PaymentInstructions.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : June 2003
//    Copyright 2000 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : PaymentInstructions
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_warn_includes.h>
#include "paymentinstructions.hpp"
#include "paymentinstructionslist.hpp"
#include "paytoentity.hpp"
#include "paytoentitylist.hpp"
#include "accshrnumcheck.hpp"
#include "agencynegcomm.hpp"
#include "agent.hpp"
#include "agentlist.hpp"
#include "branch.hpp"
#include "branchlist.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "clientbankinstructionslist.hpp"
#include "distributorrepository.hpp"
#include "distributorbankinstructionslist.hpp"
#include "dynamicsublistholder.hpp"
#include "grouplist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "PaymentInstrValidation.hpp"
#include "translationtable.hpp"
#include <ifastdataimpl\dse_dstc0256_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0088_vw.hpp>

namespace 
{
   const I_CHAR * CLASSNAME = I_("PaymentInstructions");
//   const I_CHAR * EFT = I_("E");
//   const I_CHAR * SUPPRESS = I_("X");
   const I_CHAR * WIRE = I_("WIRE");
   const I_CHAR * EFT = I_("EFT");
   const I_CHAR * CREATE_TRADE = I_("R");
   const I_CHAR * NSCC = I_("N");
   const I_CHAR * CHEQUE = I_("CHQ");
//	const I_CHAR * SYSTEMCHEQUE = I_("S");
//	const I_CHAR * MANUALCHEQUE = I_("M");
   const I_CHAR * NO = I_("N");
   const I_CHAR * YES = I_("Y");
   const I_CHAR * const ACCT_STATUS_CODE_TERMINATED = I_("30");
	const I_CHAR * PAY_ENTITY = I_("PE");
	const I_CHAR * ACCOUNT = I_("AC");
	const I_CHAR * SHAREHOLDER_GROUP = I_("SH");
   const I_CHAR * MT202 = I_( "02" );
   const I_CHAR * BAFF = I_( "BAFF" );
   const I_CHAR * const GROUPCODE_SUPPRESSION_REASON  =  I_( "PRC" );
   const I_CHAR * const BLANK_SUBSTITUTION_VALUE      =  I_("= ;");
}

namespace ifds
{
   //field ids used
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFTextFieldId SalesRepName;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;
   extern CLASS_IMPORT const BFTextFieldId BrokerBranchSalesRepPaymentFor;
   extern CLASS_IMPORT const BFTextFieldId PayToEntity;
   extern CLASS_IMPORT const BFTextFieldId PayToEntityNoAll;
   extern CLASS_IMPORT const BFTextFieldId PaymentInstructionsPayType;
   extern CLASS_IMPORT const BFTextFieldId BAFFFileProcessor;
   extern CLASS_IMPORT const BFTextFieldId AddrCntryCode;
   extern CLASS_IMPORT const BFTextFieldId PostalCode;
   extern CLASS_IMPORT const BFTextFieldId BankAcctCurrency;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
   extern CLASS_IMPORT const BFTextFieldId ACHCommission;
   extern CLASS_IMPORT const BFTextFieldId ACHTrailerFee;
   extern CLASS_IMPORT const BFTextFieldId ACHRedemption;
   extern CLASS_IMPORT const BFTextFieldId ACHDividend;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId NSCCCompliant;
   extern CLASS_IMPORT const BFTextFieldId NSCCPaymentFor;
   extern CLASS_IMPORT const BFTextFieldId PaymentInstructionsPaymentFor;
   extern CLASS_IMPORT const BFTextFieldId NSCCPayType;
   extern CLASS_IMPORT const BFTextFieldId NSCCCurrencyList;
   extern CLASS_IMPORT const BFTextFieldId FileTypeD;
   extern CLASS_IMPORT const BFTextFieldId FileTypeJ;
   extern CLASS_IMPORT const BFTextFieldId EmptySetField;
   extern CLASS_IMPORT const BFTextFieldId DataFound;
   extern CLASS_IMPORT const BFTextFieldId PayMethodPlus;
   extern CLASS_IMPORT const BFTextFieldId AcctStatus;
   extern CLASS_IMPORT const BFTextFieldId HasNegativeComm;
	extern CLASS_IMPORT const BFTextFieldId PayToEntityMgmt;
	extern CLASS_IMPORT const BFTextFieldId SearchTypeMgmt;
	extern CLASS_IMPORT const BFTextFieldId Address1;
	extern CLASS_IMPORT const BFTextFieldId Address2;
	extern CLASS_IMPORT const BFTextFieldId Address3;
	extern CLASS_IMPORT const BFTextFieldId Address4;
	extern CLASS_IMPORT const BFTextFieldId Address5;
	extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
	extern CLASS_IMPORT const BFTextFieldId PaymentForConsolType;	
   extern CLASS_IMPORT const BFTextFieldId PayInstructConsolType;
   extern CLASS_IMPORT const BFTextFieldId PayInstructConsolTypeNotPW;
	extern CLASS_IMPORT const BFTextFieldId ConsolTransType;
	extern CLASS_IMPORT const BFTextFieldId ConsolTransType;
	extern CLASS_IMPORT const BFTextFieldId ConsolDefault;
	extern CLASS_IMPORT const BFTextFieldId Consolidation;
	extern CLASS_IMPORT const BFTextFieldId PurchNetting;
	extern CLASS_IMPORT const BFTextFieldId PaymentIdMethod;
	extern CLASS_IMPORT const BFTextFieldId AcctCategory;
	extern CLASS_IMPORT const BFTextFieldId	PymtRoutingMthd;
   extern CLASS_IMPORT const BFTextFieldId	XrefSuppressionReasonCode;
   extern CLASS_IMPORT const BFTextFieldId TradeFileProcessorDefault;
}

namespace PAY_TO
{
   extern I_CHAR * const BROKER;
   extern I_CHAR * const BRANCH;
   extern I_CHAR * const SALESREP;	
   extern I_CHAR * const CLIENT;
}

namespace CURRENCY_OPTION
{
   extern const I_CHAR * PAY_CURRENCY;
   extern const I_CHAR * PAY_FUND_CURRENCY;
	extern const I_CHAR * PAY_SETTLEMENT_CURRENCY;
}

namespace PAYMENT_FOR
{
   extern const I_CHAR * TRAILER_FEE;
   extern const I_CHAR * COMMISSION;
	extern const I_CHAR * REDEMPTION;
	extern const I_CHAR * DISTRIBUTION;
}

namespace AcctUseCode
{
	extern const I_CHAR * const COMMISSION;
	extern const I_CHAR * const TRAILER_FEE;
   extern const I_CHAR * const MANAGEMENT_COMPANY;
   extern const I_CHAR * const EFT_REDEMPTION;
   extern const I_CHAR * const EFT_DIVIDEND;
   extern const I_CHAR * const DIVIDEND;
   extern const I_CHAR * const DEFAULT;
}

namespace TransType
{
	extern const I_CHAR * const COMMISSION;
	extern const I_CHAR * const TRAILER_FEE;
   extern const I_CHAR * const REDEMPTION;
   extern const I_CHAR * const EFT_DIVIDEND;
}

namespace CONSOL_TYPE
{
   extern const I_CHAR * INDIVIDUAL_PAYMENT;
   extern const I_CHAR * BULKING;
	extern const I_CHAR * BULKING_NETTING;
	extern const I_CHAR * NOT_AVAILABLE;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const EFT;
   extern CLASS_IMPORT I_CHAR * const SYSTEM_CHEQUE;
   extern CLASS_IMPORT I_CHAR * const SUPPRESS;
   extern CLASS_IMPORT I_CHAR * const MANUAL_CHEQUE;
} 
namespace PAYMENT_ROUTING
{
   const I_CHAR * const MT103      = I_("01");
   const I_CHAR * const MT202	   = I_("02");
   const I_CHAR * const ACH        = I_("03");
}

namespace ACCOUNT_CATEGORY
{
   const I_CHAR * const SWIFT_PAYMENT_METHOD   = I_( "38" ); 
}


namespace CND
{  // Conditions used
	extern const long ERR_NO_BANKING_RECORDS_FOR_PAYMENT_FOR;
	extern const long ERR_NO_BANKING_RECORDS_FOR_PAYMENT_FOR_AND_CURRENCY;
	extern const long ERR_NSCC_CURRENCY_INVALID;
	extern CLASS_IMPORT const long ERR_BROKER_NOT_FOUND;
	extern CLASS_IMPORT const long ERR_NO_BRANCH_FOUND;
	extern CLASS_IMPORT const long ERR_NO_SLSREP_FOUND;
	extern CLASS_IMPORT const long ERR_INVALID_ACCOUNT_NUMBER;
	extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
	extern const long ERR_ACCT_INACTIVE;
	extern const long ERR_ACCT_TERMINATED; 
	extern const long BROKER_PAYMENT_FOR_SETUP_NOT_IN_PAIR;
	extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
	extern const long ERR_CONSOL_NOT_VALID;
	extern const long ERR_CONSOL_NOT_VALID_FOR_DISTRIBUTION;
	extern const long ERR_INVALID_CURRENCYOPTION;
	extern const long ERR_PI_DATES_NOT_WITHIN_PE_DATES;
	extern const long WARN_CORRESPONDING_DISTRIBUTION_PAYMENT_MISSING;
	extern const long WARN_CORRESPONDING_REDEMPTION_PAYMENT_MISSING;
	extern const long ERR_PAYMENT_INSTRUCTION_FOR_BULK_DISTRIBUTION_EXIST;
	extern const long ERR_PAYMENT_INSTRUCTION_FOR_BULK_REDEMPTION_EXIST;
	extern const long ERR_PAYMENT_INSTRUCTION_FOR_INDIVIDUAL_DISTRIBUTION_EXIST;
	extern const long ERR_PAYMENT_INSTRUCTION_FOR_INDIVIDUAL_REDEMPTION_EXIST;
	extern const long WARN_DEF_CONSOL_TYPE;
	extern const long ERR_INVALID_CONSOL_VALUE;
	extern const long CONSOL_TYPE_MANDATORY;

	extern const long WARN_PAYINS_SHOULD_BE_EFT; 
	extern const long ERR_PAYINS_SHOULD_BE_EFT; 
   CIFast_IFast_ifastcbo_err_suppression_reason_code_is_blank ERR_SUPRESSION_CODE_EMPTY;
   CIFast_IFast_ifastcbo_warn_suppression_reason_code_is_blank WARN_SUPRESSION_CODE_EMPTY;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const PAYTYPE_MUST_EFT_FOR_BRKLV_PAYINS;//             = I_("997");   
   extern CLASS_IMPORT I_CHAR * const SUPRESSION_CODE_EMPTY;      //                   = I_("1703");
}
	
extern BF_OBJ_TYPE OBJ_TYPE_AGENCY_NEGATIVE_COMMISSION;
extern BF_OBJ_TYPE OBJ_TYPE_PAYMENT_INSTRUCTION_VALIDATION;

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                              //  Field DD Id,        State Flags,                     Group Flags 
   {ifds::AccountNum,        BFCBO::NONE,                     0}, 
	{ifds::BrokerCode,        BFCBO::NONE    ,                 0}, 
   {ifds::BrokerName,        BFCBO::NONE,                     0}, 
   {ifds::BranchCode,        BFCBO::NONE,                     0}, 
   {ifds::BranchName,        BFCBO::NONE,                     0}, 
   {ifds::SalesRepCode,      BFCBO::NONE,                     0}, 
   {ifds::SalesRepName,      BFCBO::NONE,                     0}, 
   {ifds::PaymentFor,        BFCBO::REQUIRED,                 0}, 
   {ifds::PayMethod,         BFCBO::REQUIRED,                 0}, 
   {ifds::PayType,           BFCBO::REQUIRED,                 0}, 
   {ifds::CurrencyOption,    BFCBO::REQUIRED,                 0}, 
   {ifds::Currency,          BFCBO::NONE,                     0}, 
   {ifds::ACHProcessor,      BFCBO::NONE,                     0}, 
   {ifds::BankChrgs,         BFCBO::NONE,                     0}, 
   {ifds::UseEntityAddress,  BFCBO::REQUIRED,                 0}, 
   {ifds::AddrLine1,         BFCBO::NONE,                     0}, 
   {ifds::AddrLine2,         BFCBO::NONE,                     0}, 
   {ifds::AddrLine3,         BFCBO::NONE,                     0}, 
   {ifds::AddrLine4,         BFCBO::NONE,                     0}, 
   {ifds::AddrLine5,         BFCBO::NONE,                     0}, 
   {ifds::PostalCode,        BFCBO::NONE,                     0}, 
   {ifds::CountryCode,       BFCBO::NONE,                     0}, 
	{ifds::CompanyCode,       BFCBO::NONE,                     0},
   //helper fields
   {ifds::PayToEntity,       BFCBO::REQUIRED,                 0}, 
	
   //cross edits
   {ifds::BrokerBranchSalesRepPaymentFor,  BFCBO::IMMEDIATE_VALIDATION,       0}, 

   {ifds::DirectTo,			  BFCBO::NONE,                     0}, 
   {ifds::DirectToShrGrp,    BFCBO::NONE,                     0}, 
	// STP enhancement new fields
	{ifds::ConsolType,		  BFCBO::NONE,                     0}, 
	{ifds::PaymentIdMethod,	  BFCBO::NONE,                     0}, 
	{ifds::EffectiveDate,     BFCBO::REQUIRED,                 0}, 
	{ifds::StopDate,          BFCBO::NONE,                     0},
	{ifds::EffectiveStopDate, BFCBO::IMMEDIATE_VALIDATION,						     0},
	{ifds::PaymentForConsolType, BFCBO::IMMEDIATE_VALIDATION,  0},
   {ifds::SuppressionReasonCode,     BFCBO::NONE,                 0},
   {ifds::XrefSuppressionReasonCode, BFCBO::IMMEDIATE_VALIDATION, 0 }, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
PaymentInstructions::PaymentInstructions(BFAbstractCBO &parent) 
: MFCanBFCbo(parent),
_isNoSplitCommissionEnvironment (false),
_hostCurrenciesSet (NULL_STRING),
_searchType (NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);

   DString commissionType, bankChrgs;

   getWorkSession().getOption (ifds::CommissionType, commissionType, BF::HOST, false);
   _isNoSplitCommissionEnvironment = commissionType == I_("0");

   addCrossEdit (ifds::BrokerBranchSalesRepPaymentFor, ifds::BrokerCode);
   addCrossEdit (ifds::BrokerBranchSalesRepPaymentFor, ifds::BranchCode);
   addCrossEdit (ifds::BrokerBranchSalesRepPaymentFor, ifds::SalesRepCode);
   addCrossEdit (ifds::BrokerBranchSalesRepPaymentFor, ifds::PaymentFor);

	addCrossEdit (ifds::EffectiveStopDate, ifds::EffectiveDate);
   addCrossEdit (ifds::EffectiveStopDate, ifds::StopDate);

	addCrossEdit (ifds::PaymentForConsolType, ifds::PaymentFor);
	addCrossEdit (ifds::PaymentForConsolType, ifds::ConsolType);
   addCrossEdit(ifds::XrefSuppressionReasonCode, ifds::PayType );
   addCrossEdit(ifds::XrefSuppressionReasonCode, ifds::SuppressionReasonCode);

   //save the currencies set....
   BFProperties *pProperties = getFieldProperties(ifds::Currency, BF::HOST);
   
   pProperties->getAllSubstituteValues (_hostCurrenciesSet);
}

//******************************************************************************
PaymentInstructions::~PaymentInstructions()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY PaymentInstructions::init ( const BFData &viewData, 
                                     const DString &searchTypeMgmt)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	_searchType = searchTypeMgmt;
   attachDataObject(const_cast<BFData&>(viewData), false, true);

   DString brokerCode, 
      branchCode,
      salesRepCode, 
      paymentFor,
		accountNum;

   brokerCode = viewData.getElementValue (ifds::BrokerCode);
   branchCode = viewData.getElementValue (ifds::BranchCode);
   salesRepCode = viewData.getElementValue (ifds::SalesRepCode);
   paymentFor = viewData.getElementValue (ifds::PaymentFor);
	accountNum = viewData.getElementValue (ifds::AccountNum);

	accountNum.strip ().stripLeading ('0');
	if (accountNum.empty())
	{
		setFieldNoValidate (ifds::AccountNum, NULL_STRING, BF::HOST, false, false, false);
	}
   brokerCode.stripAll().upperCase();
   branchCode.stripAll().upperCase();
   salesRepCode.stripAll().upperCase();
   paymentFor.stripAll().upperCase();
   setPayTypeSubSet (BF::HOST);

	commonInit (brokerCode, branchCode, salesRepCode, paymentFor, BF::HOST); 
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::init( const DString &dstrBrokerCode, 
                                    const DString &dstrBranchCode, 
                                    const DString &dstrSalesRepCode,
                                    const DString &dstrPaymentFor, 
                                    const BFDataGroupId &idDataGroup,
												const DString &searchTypeMgmt)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	_searchType = searchTypeMgmt;

   DString brokerCode (dstrBrokerCode), 
      branchCode (dstrBranchCode),
      salesRepCode (dstrSalesRepCode), 
      paymentFor (dstrPaymentFor);

   brokerCode.stripAll().upperCase();
   branchCode.stripAll().upperCase();
   salesRepCode.stripAll().upperCase();
   paymentFor.stripAll().upperCase(); 
   setFieldNoValidate ( ifds::BrokerCode, brokerCode, idDataGroup, 
                        false, false, true, true);
   setFieldNoValidate ( ifds::BranchCode, branchCode, idDataGroup, 
                        false, false, true, true);
   setFieldNoValidate ( ifds::SalesRepCode, salesRepCode, idDataGroup, 
                        false, false, true, true);
   //PaymentFor relate chnage can set paytype substitution set.also set default currency option.
   setFieldNoValidate ( ifds::PaymentFor, dstrPaymentFor, idDataGroup, 
                        false, false, true, true);
	
   commonInit ( dstrBrokerCode, dstrBranchCode, dstrSalesRepCode, 
                dstrPaymentFor, idDataGroup);   
   buildPaymentRoutingSet(idDataGroup); 
  return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::commonInit ( const DString &brokerCode, 
                                           const DString &branchCode, 
                                           const DString &salesRepCode,
                                           const DString &paymentFor, 
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   bool bDataNotFound = false;
	//initConsolidation( idDataGroup );
	
   if (isMgtCoPayInstruct ())
	{
		setFieldReadOnly (ifds::CompanyCode, idDataGroup, true);
      setFieldReadOnly (ifds::PayToEntity, idDataGroup, true);
      setFieldReadOnly (ifds::DirectTo, idDataGroup, true);
      setFieldReadOnly (ifds::PaymentFor, idDataGroup, true);
      setFieldNoValidate (ifds::PayToEntity, PAY_TO::CLIENT, idDataGroup, false, true, true, false);
	}
	else
	{
		if (!brokerCode.empty())
		{
			//here we do not care if broker does not exist
			if (setBrokerName (brokerCode, idDataGroup) > WARNING)
			{
				int count = CONDITIONCOUNT();
				Condition   *c = NULL;
				for( int i = 0; i < count; i++ )
				{
					c = GETCONDITION( i );
					int condCode = c->getCode();
					if(condCode == CND::ERR_BROKER_NOT_FOUND)
					{
						CLEARCONDITION( i );
						bDataNotFound = true;
						break;
					}
				}
			}   
		}
		if (!branchCode.empty())
		{
			//here we do not care that the broker/branch has not been found
			if (setBranchName (branchCode, idDataGroup) > WARNING)
			{
				int count = CONDITIONCOUNT();
				Condition   *c = NULL;
				for( int i = 0; i < count; i++ )
				{
					c = GETCONDITION( i );
					int condCode = c->getCode();
					if ( condCode == CND::ERR_BROKER_NOT_FOUND ||
						  condCode == CND::ERR_NO_BRANCH_FOUND)
					{
						CLEARCONDITION( i );
						bDataNotFound = true;
						break;
					}
				}
			}
		}
		if (!salesRepCode.empty())
		{
			//here we do not care that the broker/branch/sales rep has not been found
			if (setSlsRepName (salesRepCode, idDataGroup) > WARNING)
			{
				int count = CONDITIONCOUNT();
				Condition *c = NULL;
				for( int i = 0; i < count; i++ )
				{
					c = GETCONDITION( i );
					int condCode = c->getCode();
					if ( condCode == CND::ERR_BROKER_NOT_FOUND ||
						  condCode == CND::ERR_NO_BRANCH_FOUND ||
						  condCode == CND::ERR_NO_SLSREP_FOUND)
					{
						CLEARCONDITION( i );
						bDataNotFound = true;
						break;
					}
				}
			}
		}

		//figure out the pay to entity based on the broker, 
		//branch and salesrep values
		setFieldAllSubstituteValues (ifds::PayToEntity, idDataGroup, ifds::PayToEntityNoAll);
		if ( !brokerCode.empty () &&
			  branchCode.empty() &&
			  salesRepCode.empty())
		{
			setFieldNoValidate (ifds::PayToEntity, PAY_TO::BROKER, idDataGroup, false, true, true, false);
		}
		else if ( !brokerCode.empty () && 
			       !branchCode.empty() && 
			       salesRepCode.empty())
		{
			setFieldNoValidate (ifds::PayToEntity, PAY_TO::BRANCH, idDataGroup, false, true, true, false);
		}
		else if ( !brokerCode.empty () && 
			       !branchCode.empty() && 
			       !salesRepCode.empty())
		{
			setFieldNoValidate (ifds::PayToEntity, PAY_TO::SALESREP, idDataGroup, false, true, true, false);
		}
		else
		{
			if (BF::HOST == idDataGroup)
			{
				assert(0);//this should not happen, wrong data
			}
			else
			{
				setFieldNoValidate ( ifds::PayToEntity, NULL_STRING, 
											idDataGroup, false, true, true, true);
			}
		}
		//set the pay to entity field to read only,
		setFieldReadOnly (ifds::PayToEntity, idDataGroup, true);
		//the below method might change the 
		//read only flag on the PayToEntity field
		payToEntityRelatedChanges (idDataGroup);
		//the values of the key should be made read only, if not a new object,
		//or broker, branch and sales rep are not null
		setFieldReadOnly ( ifds::BrokerCode, idDataGroup, 
								 idDataGroup == BF::HOST || !brokerCode.empty());
		setFieldReadOnly ( ifds::BranchCode, idDataGroup, 
								idDataGroup == BF::HOST || !branchCode.empty());
		setFieldReadOnly ( ifds::SalesRepCode, idDataGroup, 
								 idDataGroup == BF::HOST || !salesRepCode.empty());
		setFieldReadOnly (ifds::PaymentFor, idDataGroup, idDataGroup == BF::HOST);
	}
	if (BF::HOST == idDataGroup)
	{
		fillAddressInfo (idDataGroup, bDataNotFound);
		loadCurrencySet (idDataGroup);
		loadFileProcessorSet (idDataGroup);
		currencyOptionRelatedChanges (idDataGroup);

      if (paymentFor == PAYMENT_FOR::TRAILER_FEE)
		{
			setFieldReadOnly (ifds::DirectTo, idDataGroup, false);
		}
      else
      {
         setFieldReadOnly (ifds::DirectTo, idDataGroup, true);
      }
		directToRelatedChanges( idDataGroup, bDataNotFound );
//currency option, consol type...
      if ( paymentFor == PAYMENT_FOR::REDEMPTION || 
           paymentFor == PAYMENT_FOR::DISTRIBUTION)
	   {
		   setFieldReadOnly (ifds::CurrencyOption, idDataGroup, true);
		   //setFieldReadOnly (ifds::ConsolType, idDataGroup, false);
         //setFieldRequired (ifds::ConsolType, idDataGroup, true);
		   //setValidFlag (ifds::ConsolType, idDataGroup, false);
      }
      else 
      {   
		   setFieldReadOnly (ifds::CurrencyOption, idDataGroup, false);
		   //setFieldReadOnly (ifds::ConsolType, idDataGroup, true);
         //setFieldRequired (ifds::ConsolType, idDataGroup, false);
	   }
	}

	setPaymentForSubSet (idDataGroup);
	initConsolidation( idDataGroup );
	loadShareholderGroupSet (idDataGroup);
   initializeSubstitutionList(ifds::SuppressionReasonCode, GROUPCODE_SUPPRESSION_REASON, idDataGroup);    
   DString payType;      
   getField (ifds::PayType, payType, idDataGroup, false);
   setFieldReadOnly(ifds::SuppressionReasonCode, idDataGroup, PAYTYPE::SUPPRESS != payType);
   if( PAYTYPE::SUPPRESS != payType )
   {
      clearField( ifds::SuppressionReasonCode, idDataGroup );
      clearFieldErrors( ifds::SuppressionReasonCode, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void PaymentInstructions::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{	
	if (isMgtCoPayInstruct ())
	{
		DString companyCode;
		
      getWorkSession().getOption (ifds::CompanyCode, companyCode, BF::HOST, false);
      setFieldNoValidate (ifds::CompanyCode, companyCode, idDataGroup, false, true, true, true);
	}

   setFieldNoValidate (ifds::PayMethod, NULL_STRING, idDataGroup, false, true, true, false);
	setFieldNoValidate (ifds::DirectTo, PAY_ENTITY, idDataGroup, false, true, true, false);
	setAccountField (idDataGroup);

   DString bankChrgs;

   getWorkSession().getOption (ifds::BankChrgs, bankChrgs, BF::HOST, false);
   setFieldNoValidate (ifds::BankChrgs, bankChrgs, idDataGroup, false, true, true, false);
   setFieldNoValidate (ifds::UseEntityAddress, YES, idDataGroup, false, true, true, false);
//reset the read only flag on the pay to entity field
   setFieldReadOnly (ifds::PayToEntity, idDataGroup, false);

   DString payToEntity;

//by default get the pay to entity of the parent
	getParent()->getField (ifds::PayToEntity, payToEntity, idDataGroup, false);
   setFieldNoValidate (ifds::PayToEntity, payToEntity, idDataGroup, false, false, true, true);
	fillAddressInfo (idDataGroup); 

	// Enhancement for PET2192 FN13 -- Netting Bulking Redemption and Distribution
	DString date,
      stopDate;

   getWorkSession().getOption (ifds::CurrBusDate, date, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, date, idDataGroup, false, true, true);
   getWorkSession().getDateInHostFormat (stopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false, true, true );
   buildPaymentRoutingSet(idDataGroup);  
   initConsolidation( idDataGroup );
}

//******************************************************************************
void PaymentInstructions::doReset(const BFDataGroupId &idDataGroup)
{
   if (isNew())
   {
      init (NULL_STRING, NULL_STRING, NULL_STRING, NULL_STRING, idDataGroup, _searchType );	  
   }
}

//******************************************************************************
SEVERITY PaymentInstructions::setField ( const BFFieldId &idField, 
												     const DString &dstrValue,
												     const BFDataGroupId &idDataGroup, 
													  bool bFormatted, 
													  bool bSideEffect, 
													  bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setField"));

   DString value (dstrValue);

	//if acount from/to num comes as 0, then its value should be reset to null_string
//so the validation fails, and the field set as required
   if (idField == ifds::AccountNum)
   {
      value.strip().stripLeading ('0');
   }
   BFCBO::setField ( idField, 
                     value, 
                     idDataGroup,                         
							bFormatted && !(idField == ifds::AccountNum && value.empty()), 
                     bSideEffect, 
                     bCheckCurrentValue);
   
   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
SEVERITY PaymentInstructions::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::BrokerCode)
   {
//this will call apply related changes in a cascade
//branch and then sales rep
      setFieldNoValidate (ifds::BranchCode, NULL_STRING, idDataGroup, false, true, true); 
      setFieldNoValidate (ifds::BranchName, NULL_STRING, idDataGroup, true, true, true);
   }
   else if (idField == ifds::BranchCode)
   {
//this will call apply related changes in a cascade
//sales rep
      setFieldNoValidate (ifds::SalesRepCode, NULL_STRING, idDataGroup, false, true, true);
      setFieldNoValidate (ifds::SalesRepName, NULL_STRING, idDataGroup, true, true, true);
   } 
   else if (idField == ifds::SalesRepCode)
   {
      payToEntityRelatedChanges (idDataGroup);
      //fill the address info if needed
      fillAddressInfo (idDataGroup);
      setPaymentForSubSet (idDataGroup);
   } 
   else if (idField == ifds::PayToEntity)
   {
      DString payToEntity;

      getField (ifds::PayToEntity, payToEntity, idDataGroup, false);
      if (payToEntity == PAY_TO::BROKER)
      {
         //null fields
         //apply related cascade call for sales rep
         setFieldNoValidate ( ifds::BranchCode, NULL_STRING, idDataGroup, 
                              false, true, true);
         setFieldNoValidate ( ifds::BranchName, NULL_STRING, idDataGroup, 
                              true, true, true);
      }
      else if (payToEntity == PAY_TO::BRANCH)
      {
         //null fields
         setFieldNoValidate ( ifds::SalesRepCode, NULL_STRING, idDataGroup, 
                              false, true, true);
         setFieldNoValidate ( ifds::SalesRepName, NULL_STRING, idDataGroup, 
                              true, true, true);
      }
      else if (payToEntity == PAY_TO::SALESREP)
      {
         payToEntityRelatedChanges(idDataGroup);
         //fill the address info if needed
         fillAddressInfo (idDataGroup);
      }
      setFieldValid (ifds::EffectiveStopDate, idDataGroup, false);
      setFieldValid(ifds::PayType, idDataGroup, false);
   }
   else if (idField == ifds::CurrencyOption)
   {
      currencyOptionRelatedChanges (idDataGroup);
      //then filter the currencies
      loadCurrencySet (idDataGroup);
   }
   else if (idField == ifds::PayMethod)
   {
//reset the file processor field
      setFieldNoValidate (ifds::ACHProcessor, NULL_STRING, idDataGroup, true, true, true);
//fillAdressInfo method will figure out whether
//it should go ahead and fill the info, or not
      fillAddressInfo (idDataGroup);
      loadFileProcessorSet (idDataGroup);
	  setPayTypeSubSet (idDataGroup);
   }
   else if (idField == ifds::UseEntityAddress)
   {
      //set the address info if UseEntityAddress in Yes
      DString useEntityAddress;

      getField (ifds::UseEntityAddress, useEntityAddress, idDataGroup, false);
      fillAddressInfo (idDataGroup);
   }
   else if (idField == ifds::ACHProcessor)
   {
      loadCurrencySet (idDataGroup);
      currencyOptionRelatedChanges (idDataGroup);
      setDefaultPayment(idDataGroup);
   }
   else if (idField == ifds::PaymentFor)
   {
	  loadPayMethodSet(idDataGroup);
      loadCurrencySet (idDataGroup);
      currencyOptionRelatedChanges (idDataGroup);
      loadFileProcessorSet (idDataGroup);	  
      paymentForRelateChange (idDataGroup);
      setFieldValid(ifds::PayType, idDataGroup, false);		 
   }
   else if (idField == ifds::Currency)
   {
      loadFileProcessorSet (idDataGroup);
   }
   else if (idField == ifds::PayType)
   {
//load the currency sub-set, if necessary
	   loadPayMethodSet(idDataGroup);
	   loadCurrencySet (idDataGroup);
	   loadFileProcessorSet (idDataGroup);
	   //payTypeRelatedChanges method will figure out whether
	   //it should go ahead and clear out all fields
	   payTypeRelatedChanges (idDataGroup);
   }
   else if (ifds::DirectTo == idField)
   {
		directToRelatedChanges( idDataGroup );
   }  

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::doValidateField ( const BFFieldId &idField, 
                                                const DString &strValue, 
                                                const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
   
   if (idField == ifds::BrokerBranchSalesRepPaymentFor)
   {
      PaymentInstructionsList *pPaymentInstructionsList = 
            dynamic_cast<PaymentInstructionsList*>(getParent());
      
      pPaymentInstructionsList->checkDuplicate (this, idDataGroup);
//set the valid flag on the currency to be invalid,
//banking info may change 
      setValidFlag(ifds::Currency, idDataGroup, false);
   }
   else if (idField == ifds::BrokerCode)
   {
      if (!strValue.empty())
      {
         //validates the broker code, as well
         setBrokerName (strValue, idDataGroup, true);
      }
      else
      {
         //reset the broker name
         setFieldNoValidate ( ifds::BrokerName, NULL_STRING, idDataGroup, 
                              false, true, true, false);
      }
   }
   else if (idField == ifds::BranchCode)
   {
      if (!strValue.empty())
      {
         //validates the branch code, as well
         setBranchName (strValue, idDataGroup, true);
      }
      else
      {
         //reset the branch name
         setFieldNoValidate ( ifds::BranchName, NULL_STRING, idDataGroup, 
                              false, true, true, false);
      }
   }
   else if (idField == ifds::SalesRepCode)
   {
      if (!strValue.empty())
      {
         //validates the sls rep code, as well
         setSlsRepName(strValue, idDataGroup, true);
      }
      else
      {
         //reset the sls rep name
         setFieldNoValidate ( ifds::SalesRepName, NULL_STRING, idDataGroup, 
                              false, true, true, false);
      }
   }
   else if (idField == ifds::Currency)
   {
      //validateCurrency(idDataGroup);
	   DString payType, 
         currency;

      getField (ifds::PayType, payType, idDataGroup, false);
	   getField (ifds::Currency, currency, idDataGroup, false);
	   if (payType == NSCC)
	   {
		   DString nsccCurrencyList;
		   
         getWorkSession().getOption (ifds::NSCCCurrencyList, nsccCurrencyList, idDataGroup, false);
		   if (nsccCurrencyList.find (currency) == DString::npos)
		   {
			   ADDCONDITIONFROMFILE (CND::ERR_NSCC_CURRENCY_INVALID);
		   }
	   }
   }
   else if (idField == ifds::PayMethod)
   {
      //set the valid flag on the currency to be invalid,
      //banking info may change
      setValidFlag (ifds::Currency, idDataGroup, false);
   }
	else if (idField == ifds::AccountNum)
	{
		DString dstrPayType;

      getField (ifds::PayType, dstrPayType, idDataGroup, false);
		if (dstrPayType == CREATE_TRADE)
		{ 
			DString accountNum (strValue);
			
			accountNum.strip().stripLeading ('0');
			if (!accountNum.empty())
			{
				MFAccount::validateAccountNum (accountNum, getWorkSession());

				MFAccount *pMFAccount = NULL;

            if ( getWorkSession ().getMFAccount ( idDataGroup, 
                                                  accountNum, 
                                                  pMFAccount) <= WARNING && pMFAccount)
				{
					DString acctStatus;

					pMFAccount->getField (ifds::AcctStatus, acctStatus, idDataGroup, false);
					if (acctStatus == ACCT_STATUS_CODE_TERMINATED)
					{
						ADDCONDITIONFROMFILE (CND::ERR_ACCT_TERMINATED);
					}
					else if (acctStatus > ACCT_STATUS_CODE_TERMINATED)
					{
						ADDCONDITIONFROMFILE (CND::ERR_ACCT_INACTIVE);
					}
				}
			}
		}
	}
	else if (idField == ifds::EffectiveStopDate)  //cross edit
    {
		DString effectiveDate, stopDate;

		getField (ifds::StopDate, stopDate, idDataGroup, false);
		getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);

		if (DSTCommonFunctions::CompareDates (stopDate, effectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
		{
			ADDCONDITIONFROMFILE (CND::ERR_STOP_DATE_LESS_THAN_DEFF);
		}
		if (!isMgtCoPayInstruct () && GETCURRENTHIGHESTSEVERITY() <= WARNING)
		{
			DString peEffectiveDate,
				peStopDate,
				peEffDateFmt,
				peStpDateFmt;

			if (getPayEntityDates (peEffectiveDate, peStopDate, peEffDateFmt, peStpDateFmt, idDataGroup) <= WARNING)
			{
				//check duplicate
				PaymentInstructionsList *pPaymentInstructionsList = dynamic_cast<PaymentInstructionsList*>(getParent());
	      
				if (pPaymentInstructionsList)
				{
					pPaymentInstructionsList->checkDuplicate (this, idDataGroup, false); //raise the date range error
				}
			}
		}
   }
	else if (idField == ifds::PaymentForConsolType)  //cross edit
   {      
		//validatePaymentForConsolType (idDataGroup);		
   }
	else if (idField == ifds::CurrencyOption)  
   {      
		DString dstrPaymentFor;
		getField (ifds::PaymentFor, dstrPaymentFor, idDataGroup);
		dstrPaymentFor.strip().upperCase();

      if (PAYMENT_FOR::REDEMPTION != dstrPaymentFor && PAYMENT_FOR::DISTRIBUTION != dstrPaymentFor)
		{	
			if (strValue == CURRENCY_OPTION::PAY_SETTLEMENT_CURRENCY)
			{
				ADDCONDITIONFROMFILE(CND::ERR_INVALID_CURRENCYOPTION);
			}
		}
   }

   else if (idField == ifds::PayType)
   {
      DString payToEntity;

      getField (ifds::PayToEntity, payToEntity, idDataGroup, false);
      if (payToEntity == PAY_TO::BROKER)
      {
		   DString dstrPaymentFor;
		   getField (ifds::PaymentFor, dstrPaymentFor, idDataGroup);
		   dstrPaymentFor.strip().upperCase();
      	
		   if (PAYMENT_FOR::REDEMPTION == dstrPaymentFor)
		   {
			   DString payType;
		      getField (ifds::PayType, payType, idDataGroup, false);
      		
			   if (payType != I_("E"))
			   {
			      getErrMsg ( IFASTERR::PAYTYPE_MUST_EFT_FOR_BRKLV_PAYINS, 
				                  CND::ERR_PAYINS_SHOULD_BE_EFT,
				                  CND::WARN_PAYINS_SHOULD_BE_EFT, 
				                  idDataGroup); 	
			   }
		   }
      }    
   }
   else if ( ifds::XrefSuppressionReasonCode == idField  )
   {
     DString dstrPayType, dstrSuppressionReasonCode;
     getField (ifds::PayType, dstrPayType, idDataGroup);
     getField( ifds::SuppressionReasonCode, dstrSuppressionReasonCode, idDataGroup );
     TranslationTable* pTranslationTable = NULL;
     DString dstrSubstitutionList;
     getMgmtCo ().getTranslationTable (GROUPCODE_SUPPRESSION_REASON, pTranslationTable);
     if (pTranslationTable)
         pTranslationTable->getSubstitutionList (dstrSubstitutionList);
     //Display Error or warning only if there is active miscinfo option..Else the field is not mandatory ..
     if( !dstrSubstitutionList.empty() && dstrSuppressionReasonCode.empty() && PAYTYPE::SUPPRESS == dstrPayType)
   		getErrMsg (IFASTERR::SUPRESSION_CODE_EMPTY, CND::ERR_SUPRESSION_CODE_EMPTY, CND::WARN_SUPRESSION_CODE_EMPTY, idDataGroup );     
   }
  
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::setBrokerName( const DString &brokerCode,
                                             const BFDataGroupId &idDataGroup,
                                             bool checkEffective /*=false*/) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setBrokerName"));
   
   //reset the broker name
   setFieldNoValidate ( ifds::BrokerName, NULL_STRING, idDataGroup, 
                        false, true, true, false);

   Broker *pBroker (NULL);

   if ( getBroker (pBroker, idDataGroup) <= WARNING &&
        pBroker)
   {
      DString brokerName;

      pBroker->getField (ifds::BrokerName, brokerName, idDataGroup);
      setFieldNoValidate (ifds::BrokerName, brokerName, idDataGroup);
      if (checkEffective)
      {
         DString dstrCurrBusDate;

//check the effectiveness of the broker
         getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false); 
         pBroker->checkEffective (dstrCurrBusDate, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::setBranchName ( const DString &branchCode,
                                              const BFDataGroupId &idDataGroup,
                                              bool checkEffective /*=false*/) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setBrokerName"));
   
   //reset the branch name
   setFieldNoValidate ( ifds::BranchName, NULL_STRING, idDataGroup, 
                        false, true, true, false);

   Branch *pBranch (NULL);

   if ( getBranch (pBranch, idDataGroup) <= WARNING &&
        pBranch)
   {
      DString branchName;

      pBranch->getField (ifds::BranchName, branchName, idDataGroup);
      setFieldNoValidate (ifds::BranchName, branchName, idDataGroup, false, true, true, false);
      if (checkEffective)
      {
         DString dstrCurrBusDate;

//check the effectiveness of the branch
         getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false); 
         pBranch->checkEffective (dstrCurrBusDate, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::setSlsRepName ( const DString &salesRepCode,
                                              const BFDataGroupId &idDataGroup,
                                              bool checkEffective /*=false*/) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setBrokerName"));
   
   //reset the sls rep name
   setFieldNoValidate ( ifds::SalesRepName, NULL_STRING, idDataGroup, 
                        false, true, true, false);

   Agent* pAgent (NULL);

   if ( getAgent (pAgent, idDataGroup) <= WARNING &&
        pAgent)
   {
      DString slsRepName;

      pAgent->getField (ifds::SlsrepName, slsRepName, idDataGroup);
      setFieldNoValidate (ifds::SalesRepName, slsRepName, idDataGroup, false, true, true, false);
      if (checkEffective)
      {
         DString dstrCurrBusDate;

         //chech the effectiveness of the slsrep
         getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false); 
         pAgent->checkEffective (dstrCurrBusDate, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PaymentInstructions::isSuppressAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("isSuppressAllowed"));
   DString dstrPayMethod, 
      dstrPayType;

   getField (ifds::PayType, dstrPayType, idDataGroup, false);
   getField (ifds::PayMethod, dstrPayMethod, idDataGroup, false);
   return dstrPayType == PAYTYPE::SUPPRESS && dstrPayMethod == NULL_STRING;
}

//******************************************************************************
bool PaymentInstructions::isCreateTradeAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isCreateTradeAllowed"));
   DString dstrPayMethod, 
      dstrPayType;

   getField (ifds::PayType, dstrPayType, idDataGroup, false);
   getField (ifds::PayMethod, dstrPayMethod, idDataGroup, false);
   return dstrPayType == CREATE_TRADE && dstrPayMethod == NULL_STRING;
}

//******************************************************************************
bool PaymentInstructions::isBankingAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("isBankingAllowed"));
   DString dstrPayMethod, dstrPayType;

   getField (ifds::PayType, dstrPayType, idDataGroup, false);
   getField (ifds::PayMethod, dstrPayMethod, idDataGroup, false);
   return (dstrPayType == PAYTYPE::EFT && dstrPayMethod != CHEQUE) ;
}

//******************************************************************************
bool PaymentInstructions::isAddressInfoAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAddressInfoAllowed"));
   DString payMethod, 
      payType;

   getField (ifds::PayType, payType, idDataGroup, false);
   getField (ifds::PayMethod, payMethod, idDataGroup, false);
   return ( payType == PAYTYPE::EFT || 
            payType == PAYTYPE::SYSTEM_CHEQUE|| 
            payType == PAYTYPE::MANUAL_CHEQUE) && payMethod == CHEQUE;
}

//******************************************************************************
SEVERITY PaymentInstructions::fillAddressInfo ( const BFDataGroupId &idDataGroup,
                                                bool bDataNotFound /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("fillAddressInfo"));
   //the address info should be set only if banking is not allowed,
   //meaning, pay method is CHQ and pay type is EFT
   if (isAddressInfoAllowed (idDataGroup) && !bDataNotFound)
//do not want to get the address of the broker/branch/sales rep if records do not exist on the back-end
   {
//set the address info if UseEntityAddress in Yes
      DString useEntityAddress;

      getField(ifds::UseEntityAddress, useEntityAddress, idDataGroup, false);
      if (useEntityAddress == YES)
      {
         DString payToEntity, 
            address1, 
            address2, 
            address3, 
            address4, 
            address5, 
            postalCode, 
            countryCode;
         bool bFoundFiller = false;
      
         //copy broker address if Pay to Entity is BROKER
         getField(ifds::PayToEntity, payToEntity, idDataGroup, false);
			if (payToEntity == PAY_TO::CLIENT)
			{
				getWorkSession().getOption (ifds::Address1, address1, idDataGroup, false);
				getWorkSession().getOption (ifds::Address2, address2, idDataGroup, false);
				getWorkSession().getOption (ifds::Address3, address3, idDataGroup, false);
				getWorkSession().getOption (ifds::Address4, address4, idDataGroup, false);
				getWorkSession().getOption (ifds::Address5, address5, idDataGroup, false);
				getWorkSession().getOption (ifds::CountryCode, countryCode, idDataGroup, false);
				getWorkSession().getOption (ifds::PostalCode, postalCode, idDataGroup, false);
				bFoundFiller = true;

			}
         else if (payToEntity == PAY_TO::BROKER)
         {
            Broker *pBroker (NULL);

            if ( getBroker (pBroker, idDataGroup) <= WARNING &&
                 pBroker)
            {
               pBroker->getField (ifds::AddrLine1, address1, idDataGroup, false);
               pBroker->getField (ifds::AddrLine2, address2, idDataGroup, false);
               pBroker->getField (ifds::AddrLine3, address3, idDataGroup, false);
               pBroker->getField (ifds::AddrLine4, address4, idDataGroup, false);
               pBroker->getField (ifds::AddrLine5, address5, idDataGroup, false);
               pBroker->getField (ifds::AddrCntryCode, countryCode, idDataGroup, false);
               pBroker->getField (ifds::PostalCode, postalCode, idDataGroup, false);
               bFoundFiller = true;
            }
         }
         //copy branch address if Pay to Entity is BRANCH
         else if (payToEntity == PAY_TO::BRANCH)
         {
            Branch *pBranch (NULL);

            if ( getBranch (pBranch, idDataGroup) <= WARNING &&
                 pBranch)
            {                  
               pBranch->getField (ifds::AddrLine1, address1, idDataGroup, false);
               pBranch->getField (ifds::AddrLine2, address2, idDataGroup, false);
               pBranch->getField (ifds::AddrLine3, address3, idDataGroup, false);
               pBranch->getField (ifds::AddrLine4, address4, idDataGroup, false);
               pBranch->getField (ifds::AddrLine5, address5, idDataGroup, false);
               pBranch->getField (ifds::AddrCntryCode, countryCode, idDataGroup, false);
               pBranch->getField (ifds::PostalCode, postalCode, idDataGroup, false);
               bFoundFiller = true;
            }
         }
//copy branch address if Pay to Entity is REP
         else if (payToEntity == PAY_TO::SALESREP)
         {
            Agent *pAgent = NULL;

            if ( getAgent (pAgent, idDataGroup) <= WARNING &&
                 pAgent)
            {
               pAgent->getField(ifds::AddrLine1, address1, idDataGroup, false);
               pAgent->getField(ifds::AddrLine2, address2, idDataGroup, false);
               pAgent->getField(ifds::AddrLine3, address3, idDataGroup, false);
               pAgent->getField(ifds::AddrLine4, address4, idDataGroup, false);
               pAgent->getField(ifds::AddrLine5, address5, idDataGroup, false);
               pAgent->getField(ifds::AddrCntryCode, countryCode, idDataGroup, false);
               pAgent->getField(ifds::PostalCode, postalCode, idDataGroup, false);
               bFoundFiller = true;
            }
         }
         if (bFoundFiller)
         {
            setFieldNoValidate ( ifds::AddrLine1, address1, idDataGroup, 
                                 false, true, true);
            setFieldUpdated (ifds::AddrLine1, idDataGroup, false);
            setFieldNoValidate ( ifds::AddrLine2, address2, idDataGroup, 
                                 false, true, true);
            setFieldUpdated (ifds::AddrLine2, idDataGroup, false);
            setFieldNoValidate ( ifds::AddrLine3, address3, idDataGroup, 
                                 false, true, true);
            setFieldUpdated (ifds::AddrLine3, idDataGroup, false);
            setFieldNoValidate ( ifds::AddrLine4, address4, idDataGroup, 
                                 false, true, true);
            setFieldUpdated (ifds::AddrLine4, idDataGroup, false);
            setFieldNoValidate ( ifds::AddrLine5, address5, idDataGroup, 
                                 false, true, true);
            setFieldUpdated (ifds::AddrLine5, idDataGroup, false);
            setFieldNoValidate ( ifds::CountryCode, countryCode, idDataGroup, 
                                 false, true, true);
            setFieldUpdated ( ifds::CountryCode, idDataGroup, false);
            setFieldNoValidate ( ifds::PostalCode, postalCode, idDataGroup, 
                                 false, true, true);
            setFieldUpdated (ifds::PostalCode, idDataGroup, false);
         }
      }
   }
   addressInfoRelatedChanges (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::doValidateAll ( const BFDataGroupId& idDataGroup, 
                                              long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   validateCurrency (idDataGroup);
	if ( !isNew() )
	{
		validateConsolType( idDataGroup );
	}
	/*
	if( isUpdatedForDataGroup (idDataGroup, true) || isNew() )  
	{
		DString dstrPaymentFor;
		getField (ifds::PaymentFor, dstrPaymentFor, idDataGroup, false);
		dstrPaymentFor.stripAll().upperCase();
		
		if ( dstrPaymentFor == I_("PW") || dstrPaymentFor == I_("ID") )
		{
			CheckPair (idDataGroup);
		}
	}*/
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::CheckPair (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("CheckPair"));
	DString dstrBrokerCode, dstrBranchCode, dstrSalesRepCode, dstrPaymentFor;
	DString dstrEffectiveDate, dstrStopDate, dstrConsolType;

	DString pairBrokerCode, pairBranchCode, pairSalesRepCode, pairPaymentFor;
	DString pairEffectiveDate, pairStopDate, pairConsolType, pairPayInstructRID;

	getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
	dstrBrokerCode.stripAll().upperCase();
	getField (ifds::BranchCode, dstrBranchCode, idDataGroup, false);
	dstrBranchCode.stripAll().upperCase();
	getField (ifds::SalesRepCode, dstrSalesRepCode, idDataGroup, false);
	dstrSalesRepCode.stripAll().upperCase();
	getField (ifds::PaymentFor, dstrPaymentFor, idDataGroup, false);
	dstrPaymentFor.stripAll().upperCase();
	PaymentInstructionsList *pPaymentInstructionsList = 
            dynamic_cast<PaymentInstructionsList*>(getParent());

	DString lookingForPaymentFor;
	if (dstrPaymentFor == I_("ID"))
		lookingForPaymentFor = I_("PW");
	else if ( dstrPaymentFor == I_("PW") )
		lookingForPaymentFor = I_("ID");

	getField (ifds::ConsolType, dstrConsolType, idDataGroup, false);
	
	getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
	getField (ifds::StopDate, dstrStopDate, idDataGroup, false);

	PaymentInstrValidation *pPaymentInstrValidation = NULL; 	
	bool bDataNotFound = false;
   if ( getPaymentInstrValidation( dstrBrokerCode, dstrBranchCode, 
		                             dstrSalesRepCode, lookingForPaymentFor,
											  dstrEffectiveDate, dstrStopDate,
											  idDataGroup, pPaymentInstrValidation, bDataNotFound) <= WARNING &&
		 NULL != pPaymentInstrValidation)
	{
		pPaymentInstrValidation->getField (ifds::ConsolType, pairConsolType, idDataGroup, false);
		pPaymentInstrValidation->getField (ifds::PaymentFor, pairPaymentFor, idDataGroup, false);
		pPaymentInstrValidation->getField (ifds::PayInstructRID, pairPayInstructRID, idDataGroup, false);
		if ( dstrPaymentFor == I_("PW") ) 
		{
			// Condition #3
			if ( pPaymentInstructionsList->isNotDeleted ( idDataGroup, pairPayInstructRID ) &&
				  dstrConsolType == CONSOL_TYPE::INDIVIDUAL_PAYMENT && 
				  pairConsolType == CONSOL_TYPE::BULKING && 
				  pairPaymentFor == I_("ID") )
			{
				ADDCONDITIONFROMFILE (CND::ERR_PAYMENT_INSTRUCTION_FOR_BULK_DISTRIBUTION_EXIST);
			}
			// Condition #5
			if ( pPaymentInstructionsList->isNotDeleted ( idDataGroup, pairPayInstructRID ) &&
				  dstrConsolType == CONSOL_TYPE::BULKING && 
				  pairConsolType == CONSOL_TYPE::INDIVIDUAL_PAYMENT && 
				  pairPaymentFor == I_("ID") )
			{
				ADDCONDITIONFROMFILE (CND::ERR_PAYMENT_INSTRUCTION_FOR_INDIVIDUAL_DISTRIBUTION_EXIST);
			}

		}
		if ( dstrPaymentFor == I_("ID") )
		{
			// Condition #4
			if ( pPaymentInstructionsList->isNotDeleted ( idDataGroup, pairPayInstructRID ) &&
				  dstrConsolType == CONSOL_TYPE::INDIVIDUAL_PAYMENT && 
				  pairConsolType == CONSOL_TYPE::BULKING && 
				  pairPaymentFor == I_("PW") 
				 )
			{
				ADDCONDITIONFROMFILE (CND::ERR_PAYMENT_INSTRUCTION_FOR_BULK_REDEMPTION_EXIST);
			}
			// Condition #6
			if ( pPaymentInstructionsList->isNotDeleted ( idDataGroup, pairPayInstructRID ) &&
				  dstrConsolType == CONSOL_TYPE::BULKING && 
				  pairConsolType == CONSOL_TYPE::INDIVIDUAL_PAYMENT && 
				  pairPaymentFor == I_("PW") )
			{
				ADDCONDITIONFROMFILE (CND::ERR_PAYMENT_INSTRUCTION_FOR_INDIVIDUAL_REDEMPTION_EXIST);
			}
		}
	}
	else
	{
		if ( bDataNotFound == true && 
			  pPaymentInstructionsList->isNotAdded( idDataGroup,
																 dstrBrokerCode,
																 dstrBranchCode,
																 dstrSalesRepCode,
																 lookingForPaymentFor,
																 dstrEffectiveDate,
																 dstrStopDate)
			)
		{
			if ( dstrPaymentFor == I_("ID") )
			{
				ADDCONDITIONFROMFILE (CND::WARN_CORRESPONDING_REDEMPTION_PAYMENT_MISSING);
			}
			else if ( dstrPaymentFor == I_("PW") )
			{
				ADDCONDITIONFROMFILE (CND::WARN_CORRESPONDING_DISTRIBUTION_PAYMENT_MISSING);
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//**********************************************************************************
SEVERITY PaymentInstructions::getPaymentInstrValidation(  const DString &dstrBrokerCode,
							    const DString &dstrBranchCode,
								 const DString &dstrSalesRepCode,
								 const DString &dstrPaymentFor,
								 const DString &dstrEffectiveDate,
								 const DString &dstrStopDate,
								 const BFDataGroupId& idDataGroup,
								 PaymentInstrValidation *&pPaymentInstrValidation,
								 bool  &bDataNotFound /*= false*/)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getPaymentInstrValidation" ) );


   DString dstrkey = I_("PaymentInstrValidation=") 
	                + dstrBrokerCode
						 + dstrBranchCode
				       + dstrSalesRepCode
				       + dstrPaymentFor
				       + dstrEffectiveDate
						 + dstrStopDate;

   BFObjectKey objKey(dstrkey , idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_PAYMENT_INSTRUCTION_VALIDATION );
	
   pPaymentInstrValidation = NULL;
   pPaymentInstrValidation = dynamic_cast<PaymentInstrValidation*>( findObject( objKey ) );
	
   if( !pPaymentInstrValidation  )
   {
      pPaymentInstrValidation = new PaymentInstrValidation( *this );


		 if( pPaymentInstrValidation->init( dstrBrokerCode,
														dstrBranchCode,
														dstrSalesRepCode,
														dstrPaymentFor,
														dstrEffectiveDate,
														dstrStopDate ) >  WARNING )

     
      {
			int count = CONDITIONCOUNT();
			Condition   *c = NULL;
			for( int i = 0; i < count; i++ )
			{
				c = GETCONDITION( i );
				int condCode = c->getCode();
				if(condCode == CND::ERR_DATA_NOT_FOUND)
				{
					CLEARCONDITION( i );
					bDataNotFound = true;
					break;
				}
			}
	  
         delete pPaymentInstrValidation;
         pPaymentInstrValidation = NULL;
      }
      else
      {
         setObject( objKey, pPaymentInstrValidation );
      }
   }   

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::validateCurrency (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateCurrency"));

   DString currency, 
      currencyOption;
   
   getField (ifds::CurrencyOption, currencyOption, idDataGroup, false);
   getField (ifds::Currency, currency, idDataGroup, false);
   bool bValid = !isBankingAllowed (idDataGroup),
      bCurrencyACriteria = currencyOption == CURRENCY_OPTION::PAY_CURRENCY;
   //the currency must be validated against the list of banking instructions for this
   //broker, branch and sales rep combination, an also against 
   //the payment for value (TF or CO) which should match the account usage of 
   //the banking instructions records

   //look for the banking info
   if (!bValid)
   {
      BankInstructionsList *pBankInstructionsList (NULL); 
      
      if ( getBankInstructionsList( pBankInstructionsList, idDataGroup) <= WARNING &&
           pBankInstructionsList)
      {
         //BFData matchCriteria;
         DString paymentFor, 
            acctUsage;

         getField (ifds::PaymentFor, paymentFor, idDataGroup, false);
         if (isMgtCoPayInstruct ())
         {
// "33 - Mgmt Company pymt should be the acctUsage code for the MgmtCo Payment					
            acctUsage = AcctUseCode::MANAGEMENT_COMPANY; 
         }
         else if (paymentFor == PAYMENT_FOR::TRAILER_FEE)
         {
            acctUsage = AcctUseCode::TRAILER_FEE;
         }
         else if (paymentFor == PAYMENT_FOR::COMMISSION)
         {
            acctUsage = AcctUseCode::COMMISSION;
         }
         else if (paymentFor == PAYMENT_FOR::REDEMPTION)
         {
            acctUsage = DString (AcctUseCode::EFT_REDEMPTION) + I_(",") +   //="07"
                        DString (AcctUseCode::DEFAULT);                     //="00"
         }
         else if (paymentFor == PAYMENT_FOR::DISTRIBUTION)
         {
            acctUsage = DString (AcctUseCode::EFT_DIVIDEND) + I_(",") +  //="16"
                        DString (AcctUseCode::DIVIDEND) + I_(",") +      //="28"
                        DString (AcctUseCode::DEFAULT);                  //="00"
         }
         //matchCriteria.setElementValue (ifds::AcctUseCode, acctUsage, true);
         BFObjIter iter ( *pBankInstructionsList, 
                           idDataGroup, 
                           true, 
                           BFObjIter::ITERTYPE::NON_DELETED);
         
         while (!iter.end ())
         {            
            bool bCurrencyMatches = false;
            if (bCurrencyACriteria)
            {
               //add the currency criteria only if the currency option is 
               //pay currency
               //matchCriteria.setElementValue (ifds::BankAcctCurrency, currency, true);
               DString bankCurrency;

               iter.getObject ()->getField (ifds::BankAcctCurrency, bankCurrency, idDataGroup, false);
               bCurrencyMatches = bankCurrency == currency;
            }

            DString bankAcctUseCode;

            iter.getObject()->getField (ifds::AcctUseCode, bankAcctUseCode, idDataGroup, false);
            bValid = DSTCommonFunctions::codeInList (bankAcctUseCode, acctUsage);
            if (bValid && bCurrencyACriteria)
            {
               bValid = bCurrencyMatches;
            }
            if (bValid)
            {
               break;
            }
            ++iter;
         }
         //iter.positionOnNextMatch (matchCriteria, idDataGroup);
         //bValid = !iter.end();
      }
   }
   if (!bValid)
   {
      DString strIDI, 
         currency,
         paymentFor;

      getField (ifds::PaymentFor, paymentFor, idDataGroup, true);
      addIDITagValue (strIDI, I_("paymentfor"), paymentFor);
      if (bCurrencyACriteria)
      {
         getField (ifds::Currency, currency, idDataGroup, true);
         addIDITagValue(strIDI, I_("currency"), currency);
         ADDCONDITIONFROMFILEIDI (CND::ERR_NO_BANKING_RECORDS_FOR_PAYMENT_FOR_AND_CURRENCY, strIDI);
      }
      else
      {
         ADDCONDITIONFROMFILEIDI (CND::ERR_NO_BANKING_RECORDS_FOR_PAYMENT_FOR, strIDI);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::currencyOptionRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("currencyOptionRelatedChanges"));

   DString currencyOption;

   getField (ifds::CurrencyOption, currencyOption, idDataGroup, false);
   bool isPayFundOrSettleCurrency = ( currencyOption == CURRENCY_OPTION::PAY_FUND_CURRENCY ||
												  currencyOption == CURRENCY_OPTION::PAY_SETTLEMENT_CURRENCY );

   if (isPayFundOrSettleCurrency)
   {
      setFieldNoValidate (ifds::Currency, NULL_STRING, idDataGroup, true, true, true);
   }
   setValidFlag (ifds::Currency, idDataGroup, isPayFundOrSettleCurrency);
   setFieldRequired (ifds::Currency, idDataGroup, !isPayFundOrSettleCurrency);
   setFieldReadOnly (ifds::Currency, idDataGroup, isPayFundOrSettleCurrency);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::payToEntityRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("payToEntityRelatedChanges"));
   DString payToEntity;

   getField(ifds::PayToEntity, payToEntity, idDataGroup, false);
   if (payToEntity == PAY_TO::BROKER)
   {
      //required fields
      //broker code
      setValidFlag(ifds::BrokerCode, idDataGroup, false);
      setFieldRequired(ifds::BrokerCode, idDataGroup, true);
      setFieldRequired(ifds::BranchCode, idDataGroup, false);
      setFieldRequired(ifds::SalesRepCode, idDataGroup, false);
      //read only fields
      setFieldReadOnly(ifds::BrokerCode, idDataGroup, false);
      setFieldReadOnly(ifds::BranchCode, idDataGroup, true);
      setFieldReadOnly(ifds::SalesRepCode, idDataGroup, true);
   }
   else if (payToEntity == PAY_TO::BRANCH)
   {
      //required fields
      //broker code, branch code
      setValidFlag(ifds::BrokerCode, idDataGroup, false);
      setFieldRequired(ifds::BrokerCode, idDataGroup, true);
      setValidFlag(ifds::BranchCode, idDataGroup, false);
      setFieldRequired(ifds::BranchCode, idDataGroup, true);
      setFieldRequired(ifds::SalesRepCode, idDataGroup, false);
      //read only fields
      setFieldReadOnly(ifds::BrokerCode, idDataGroup, false);
      setFieldReadOnly(ifds::BranchCode, idDataGroup, false);
      setFieldReadOnly(ifds::SalesRepCode, idDataGroup, true);
   }
   else if (payToEntity == PAY_TO::SALESREP)
   {
      //required fields
      //broker code, branch code, sales rep code
      setValidFlag(ifds::BrokerCode, idDataGroup, false);
      setFieldRequired(ifds::BrokerCode, idDataGroup, true);
      setValidFlag(ifds::BranchCode, idDataGroup, false);
      setFieldRequired(ifds::BranchCode, idDataGroup, true);
      setValidFlag(ifds::SalesRepCode, idDataGroup, false);
      setFieldRequired(ifds::SalesRepCode, idDataGroup, true);
      //read only fields
      setFieldReadOnly(ifds::BrokerCode, idDataGroup, false);
      setFieldReadOnly(ifds::BranchCode, idDataGroup, false);
      setFieldReadOnly(ifds::SalesRepCode, idDataGroup, false);
   }
	else
   {
      //none of the broker, branch sales rep is required,
      //because pay to entity is required, and the user is 
      //forced to choose a value
      setFieldRequired(ifds::BrokerCode, idDataGroup, false);
      setFieldRequired(ifds::BranchCode, idDataGroup, false);
      setFieldRequired(ifds::SalesRepCode, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::addressInfoRelatedChanges(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("addressInfoRelatedChanges"));

   if (isAddressInfoAllowed(idDataGroup))
   {
      DString useEntityAddress;

      getField(ifds::UseEntityAddress, useEntityAddress, 
         idDataGroup, false);

      bool bUseEntityAddress = useEntityAddress == YES;

      setFieldReadOnly (ifds::AddrLine1, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::AddrLine2, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::AddrLine3, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::AddrLine4, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::AddrLine5, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::CountryCode, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::PostalCode, idDataGroup, bUseEntityAddress);
      setValidFlag (ifds::AddrLine1, idDataGroup, false);
      setFieldRequired (ifds::AddrLine1, idDataGroup, true);
      setValidFlag (ifds::CountryCode, idDataGroup, false);
      setFieldRequired (ifds::CountryCode, idDataGroup, true);
   }
   else
   {
      setFieldRequired (ifds::AddrLine1, idDataGroup, false);
      setFieldRequired (ifds::CountryCode, idDataGroup, false);
      //clear the address related fields
      /*setFieldNoValidate(ifds::UseEntityAddress, I_("N"), idDataGroup, 
         false, true, true, false);*/
      setFieldNoValidate ( ifds::AddrLine1, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::AddrLine2, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::AddrLine3, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::AddrLine4, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::AddrLine5, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::CountryCode, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::PostalCode, NULL_STRING, idDataGroup, 
                           false, true, true, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::payTypeRelatedChanges ( const BFDataGroupId &idDataGroup,
                                                      bool bDataNotFound /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("payTypeRelatedChanges"));

   if ( isSuppressAllowed (idDataGroup) || 
        isCreateTradeAllowed (idDataGroup))
   {
      //clear the address info fields
      addressInfoRelatedChanges (idDataGroup);
      //set the address fields to read only
      setFieldReadOnly (ifds::AddrLine1, idDataGroup, true);
      setFieldReadOnly (ifds::AddrLine2, idDataGroup, true);
      setFieldReadOnly (ifds::AddrLine3, idDataGroup, true);
      setFieldReadOnly (ifds::AddrLine4, idDataGroup, true);
      setFieldReadOnly (ifds::AddrLine5, idDataGroup, true);
      setFieldReadOnly (ifds::CountryCode, idDataGroup, true);
      setFieldReadOnly (ifds::PostalCode, idDataGroup, true);
   }
   else
   {
      //see whether the address fields can be restored
      fillAddressInfo (idDataGroup, bDataNotFound);
   }

   DString payType;   
   
   getField (ifds::PayType, payType, idDataGroup, false);
   bool bIsPayTypeNotEFT = payType != PAYTYPE::EFT;

   if (bIsPayTypeNotEFT)
   {
	   setFieldNoValidate (ifds::ACHProcessor, NULL_STRING, idDataGroup, false, true, false, false);
      if (payType == PAYTYPE::SYSTEM_CHEQUE || 
          payType == PAYTYPE::MANUAL_CHEQUE)
      {
         setFieldNoValidate ( ifds::PayMethod, I_("CHQ"), idDataGroup, 
                              false, true, true, false);
      }
      else
      {
         setFieldNoValidate ( ifds::PayMethod, NULL_STRING, idDataGroup, 
                              false, true, true, false);
      }
   }
//pay method should be read only
   setFieldReadOnly (ifds::PayMethod, idDataGroup, bIsPayTypeNotEFT);
   setFieldValid (ifds::PayMethod, idDataGroup, bIsPayTypeNotEFT);
   setFieldRequired (ifds::PayMethod, idDataGroup, !bIsPayTypeNotEFT);
	setFieldReadOnly (ifds::ACHProcessor, idDataGroup, bIsPayTypeNotEFT);
   setFieldValid (ifds::ACHProcessor, idDataGroup, bIsPayTypeNotEFT);
   setFieldRequired (ifds::ACHProcessor, idDataGroup, !bIsPayTypeNotEFT);
   setAccountField (idDataGroup);	
   setFieldReadOnly(ifds::SuppressionReasonCode, idDataGroup, PAYTYPE::SUPPRESS != payType);
   if( PAYTYPE::SUPPRESS != payType )
   {
        setFieldNoValidate( ifds::SuppressionReasonCode, NULL_STRING, idDataGroup, false, true, true );
        clearField( ifds::SuppressionReasonCode, idDataGroup );
        clearFieldErrors( ifds::SuppressionReasonCode, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::loadCurrencySet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadCurrencySet"));

   DString multiCurrency, 
      dstrACHCommission, 
      dstrACHTrailerFee,
      dstrACHRedemption,
      dstrACHDividend;

   getWorkSession().getOption ( ifds::ACHCommission, dstrACHCommission, 
                                BF::HOST, false);
   getWorkSession().getOption ( ifds::ACHTrailerFee, dstrACHTrailerFee, 
                                BF::HOST, false);
   getWorkSession().getOption ( ifds::ACHRedemption, dstrACHRedemption, 
                                BF::HOST, false);
   getWorkSession ().getOption ( ifds::ACHDividend, dstrACHDividend, 
                                 BF::HOST, false);   
   getWorkSession().getOption (ifds::MultiCurrency, multiCurrency, BF::HOST, false);
   if (multiCurrency.strip() == YES)
   {
      DString paymentFor, 
         transType;

      getField(ifds::PaymentFor, paymentFor, idDataGroup, false);
      if (paymentFor == PAYMENT_FOR::COMMISSION && 
          dstrACHCommission == YES)
      {
         transType = TransType::COMMISSION;
      }
      else if (paymentFor == PAYMENT_FOR::TRAILER_FEE && 
               dstrACHTrailerFee == YES)
      {
         transType = TransType::TRAILER_FEE;
      } 
      else if ( paymentFor == PAYMENT_FOR::REDEMPTION && 
                dstrACHRedemption == Y)
      {
         transType = TransType::REDEMPTION;
      }
      else if ( paymentFor == PAYMENT_FOR::DISTRIBUTION && 
                dstrACHDividend == Y)
      {
         transType = TransType::EFT_DIVIDEND;
      }

      DynamicSubListHolder* pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();
	   assert (pDynamicSubListHolder);

      DString payMethod, 
         fileProcessor,
         substList;

      getField (ifds::PayMethod, payMethod, idDataGroup, false);
      payMethod.strip();
      getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
      fileProcessor.strip();
      if (!fileProcessor.empty())
      {
		   substList = pDynamicSubListHolder->getCurrencySubList (transType, payMethod, fileProcessor);
      }
      else
      {
		   substList = pDynamicSubListHolder->getCurrencySubList (transType, payMethod);
      }
      if (substList.empty())
      {
         setFieldAllSubstituteValues (ifds::Currency, idDataGroup, _hostCurrenciesSet);
      }
      else
      {
		   setFieldAllSubstituteValues (ifds::Currency, idDataGroup, substList);
      }
//have to force validation, because substitute values have changed
		setValidFlag (ifds::Currency, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::loadFileProcessorSet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadFileProcessorSet"));

   DString multiCurrency,
      dstrACHCommission, 
      dstrACHTrailerFee,
      dstrACHRedemption,
      dstrACHDividend,
      substList,
      payType;

   getWorkSession().getOption (ifds::ACHCommission, dstrACHCommission, BF::HOST, false);
   getWorkSession().getOption (ifds::ACHTrailerFee, dstrACHTrailerFee, BF::HOST, false);
   getWorkSession().getOption (ifds::ACHRedemption, dstrACHRedemption, BF::HOST, false);
   getWorkSession().getOption (ifds::ACHDividend, dstrACHDividend, BF::HOST, false);   
   getWorkSession().getOption (ifds::MultiCurrency, multiCurrency, BF::HOST, false);
   getField (ifds::PayType, payType, idDataGroup);
   if (/*multiCurrency.strip() == YES &&*/ payType == PAYTYPE::EFT)
   {
      DString paymentFor, 
         transType;

      getField (ifds::PaymentFor, paymentFor, idDataGroup, false);
      if ( paymentFor == PAYMENT_FOR::COMMISSION && 
           dstrACHCommission == YES)
      {
         transType = TransType::COMMISSION;
      }
      else if ( paymentFor == PAYMENT_FOR::TRAILER_FEE && 
                dstrACHTrailerFee == YES)
      {
         transType = TransType::TRAILER_FEE;
      }
      else if ( paymentFor == PAYMENT_FOR::REDEMPTION && 
                dstrACHRedemption == Y)
      {
         transType = TransType::REDEMPTION;
      }
      else if ( paymentFor == PAYMENT_FOR::DISTRIBUTION && 
                dstrACHDividend == Y)
      {
         transType = TransType::EFT_DIVIDEND;
      }

      DynamicSubListHolder *pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();
	   assert(pDynamicSubListHolder);

      DString payMethod, 
         currency;

      getField (ifds::PayMethod, payMethod, idDataGroup, false);
      payMethod.strip();
      getField (ifds::Currency, currency, idDataGroup, false);
      currency.strip();
      if (currency.empty())
      {
	      substList = pDynamicSubListHolder->getFileProcSubList (transType, payMethod);
      }
      else 
      {
	      substList = pDynamicSubListHolder->getFileProcSubList (transType, payMethod, currency);
      }
   }
   setFieldAllSubstituteValues (ifds::ACHProcessor, idDataGroup, substList);

   bool bRequired = !substList.empty();

   //setFieldRequired (ifds::ACHProcessor, idDataGroup, bRequired);
   setValidFlag (ifds::ACHProcessor, idDataGroup, !bRequired);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::loadPayMethodSet (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadPayMethodSet"));
	
	DString dstrACHCommission, 
			dstrACHTrailerFee,
			dstrACHRedemption,
			dstrACHDividend,
			substList,
			payType;
	
	getWorkSession().getOption (ifds::ACHCommission, dstrACHCommission, BF::HOST, false);
	getWorkSession().getOption (ifds::ACHTrailerFee, dstrACHTrailerFee, BF::HOST, false);
	getWorkSession().getOption (ifds::ACHRedemption, dstrACHRedemption, BF::HOST, false);
	getWorkSession().getOption (ifds::ACHDividend, dstrACHDividend, BF::HOST, false);   
	getField (ifds::PayType, payType, idDataGroup);

	if(payType == PAYTYPE::EFT)
	{
		DString paymentFor, transType;
		
		getField(ifds::PaymentFor, paymentFor, idDataGroup, false);
		if(paymentFor == PAYMENT_FOR::COMMISSION && dstrACHCommission == YES)
		{
			transType = TransType::COMMISSION;
		}
		else if(paymentFor == PAYMENT_FOR::TRAILER_FEE && dstrACHTrailerFee == YES)
		{
			transType = TransType::TRAILER_FEE;
		}
		else if(paymentFor == PAYMENT_FOR::REDEMPTION && dstrACHRedemption == Y)
		{
			transType = TransType::REDEMPTION;
		}
		else if (paymentFor == PAYMENT_FOR::DISTRIBUTION && dstrACHDividend == Y)
		{
			transType = TransType::EFT_DIVIDEND;
		}
		
		DynamicSubListHolder *pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();
		assert(pDynamicSubListHolder);
		
		DString fileProcessor, currency;
		
		getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
		fileProcessor.strip();
		getField (ifds::Currency, currency, idDataGroup, false);
		currency.strip();

		if(currency.empty())
		{
			substList = pDynamicSubListHolder->getPayMethodSubList(transType, fileProcessor);
		}
		else 
		{
			substList = pDynamicSubListHolder->getPayMethodSubList(transType, fileProcessor, currency);
		}
	}
	setFieldAllSubstituteValues (ifds::PayMethod, idDataGroup, substList);
	bool bRequired = !substList.empty();
	setValidFlag (ifds::PayMethod, idDataGroup, !bRequired);
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::removeBankInstructionsList(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("removeBankInstructionsList"));
	BankInstructionsList *pBankInstructionList;
	if(getBankInstructionsList(pBankInstructionList, idDataGroup) <=WARNING)
	{
		BFObjIter iter(*pBankInstructionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		while(!iter.end())
		{
			iter.deleteObject();
		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::getBankInstructionsList( BankInstructionsList *&pBankInstructionsList, 
                                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBankInstructionsList"));

   //the bank instructions list can be created only if the 
   //payment method is EFT
   pBankInstructionsList = NULL;  
   BankInstructionsList *pBankInstructionsList_ = NULL;
   
   if (isBankingAllowed (idDataGroup))
   {
      DString brokerCode, 
         branchCode, 
         salesRepCode;

      getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
      getField (ifds::BranchCode, branchCode, idDataGroup, false);
      getField (ifds::SalesRepCode, salesRepCode, idDataGroup, false);

		if ( brokerCode.empty() && 
           branchCode.empty() && 
           salesRepCode.empty()) //management company get the client banking
		{
         ClientBankInstructionsList *pClientBankInstructionsList = NULL;
         if ( getWorkSession ().getClientBankInstructionsList ( pClientBankInstructionsList, 
                                                                idDataGroup) <= WARNING &&
              pClientBankInstructionsList)
         {
            pClientBankInstructionsList->setPayInstructionsAsParentCBO (this);
            pBankInstructionsList = pClientBankInstructionsList;
         }
      }
      else
      {
         DistributorRepository *pDistributorRepository = NULL;
         DistributorBankInstructionsList *pDistributorBankInstructionsList = NULL;
      
         if ( getWorkSession().getDistributorRepository (pDistributorRepository) <= WARNING && 
              pDistributorRepository)
         {
            DString brokerCode, 
               branchCode, 
               salesRepCode;

            getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
            getField (ifds::BranchCode, branchCode, idDataGroup, false);
            getField (ifds::SalesRepCode, salesRepCode, idDataGroup, false);

			   if ( !brokerCode.empty() ||
                 !branchCode.empty() || 
                 !salesRepCode.empty())
            {
               if ( pDistributorRepository->
                     getDistributorBankInstructionsList ( brokerCode, 
                                                          branchCode, 
                                                          salesRepCode, 
                                                          pDistributorBankInstructionsList, 
                                                          idDataGroup,
                                                          this) <= WARNING && 
                  pDistributorBankInstructionsList)
               {
                  pBankInstructionsList = pDistributorBankInstructionsList;
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::setPaymentForSubSet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setPaymentForSubSet"));

   DString nsccCompliant; 
   bool NSCCapply = false;
   
   if (getWorkSession().getOption ( ifds::NSCCCompliant, 
                                    nsccCompliant, 
                                    idDataGroup, 
                                    false) <= WARNING)
   {
      Broker *pBroker = NULL;

      if ( nsccCompliant == Y && 
           getBroker (pBroker, idDataGroup) <= WARNING &&
           pBroker)
      {
         DString brokerNSCCCompliant, 
            fileTypeJ;

         pBroker->getField (ifds::NSCCCompliant, brokerNSCCCompliant, idDataGroup, false);
			pBroker->getField (ifds::FileTypeJ, fileTypeJ, idDataGroup);
			if (brokerNSCCCompliant == Y && fileTypeJ == Y)
			{
				NSCCapply = true;
         }
      }
   }
   if (NSCCapply)
   {
      setFieldSubstituteValues (ifds::PaymentFor, idDataGroup, ifds::NSCCPaymentFor);
   }
   else
   {
      setFieldSubstituteValues (ifds::PaymentFor, idDataGroup, ifds::PaymentInstructionsPaymentFor);
      if (!isMgtCoPayInstruct ())
      {
		   DString payToEntitySubList = removeItemFromSubtList (ifds::PayToEntity, PAY_TO::CLIENT, idDataGroup);
		   
         setFieldAllSubstituteValues (ifds::PayToEntity, idDataGroup, payToEntitySubList);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::paymentForRelateChange (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("paymentForRelateChange"));

   DString paymentFor;
   
   getField (ifds::PaymentFor, paymentFor, idDataGroup);
   setPayTypeSubSet (idDataGroup);
  
   if ( paymentFor == I_("NC") || 
        paymentFor == I_("NT"))
   {
      setFieldNoValidate ( ifds::CurrencyOption, NULL_STRING, idDataGroup, 
                           false, true, true, true);
      setFieldNoValidate (ifds::PayType, NSCC, idDataGroup, false, true, true, false);		
   }
	else if ( paymentFor == PAYMENT_FOR::REDEMPTION || 
             paymentFor == PAYMENT_FOR::DISTRIBUTION)
	{
// Enhancement PET2212 FN10, 13, STP project - Redemption/Distribution Payment Instruction for broker
		setFieldNoValidate ( ifds::CurrencyOption, CURRENCY_OPTION::PAY_SETTLEMENT_CURRENCY, idDataGroup, 
                           false, true, true, true);
		setFieldReadOnly (ifds::CurrencyOption, idDataGroup, true);
	}
   else 
   {   
      setFieldNoValidate ( ifds::CurrencyOption, CURRENCY_OPTION::PAY_CURRENCY, idDataGroup, 
                           false, true, true, true);
      setFieldNoValidate (ifds::PayType, PAYTYPE::EFT, idDataGroup, false, true, true, false);
		setFieldReadOnly( ifds::CurrencyOption, idDataGroup, false );
	}
  	// set ConsolType
	initConsolidation( idDataGroup );

	// set payMethod
	DString payType;
   getField (ifds::PayType, payType, idDataGroup);
   if (paymentFor != PAYMENT_FOR::TRAILER_FEE && payType == CREATE_TRADE)
	{
		setFieldNoValidate (ifds::PayMethod, NULL_STRING, idDataGroup, false, true, true, false);
	}
   setAccountField (idDataGroup);
   setFieldNoValidate (ifds::DirectTo, PAY_ENTITY, idDataGroup, false, true, true, false);
   setFieldReadOnly (ifds::DirectTo, idDataGroup, paymentFor != PAYMENT_FOR::TRAILER_FEE);
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY PaymentInstructions::setPayTypeSubSet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setPayTypeSubstSet"));
   
	DString dstrPaymentFor, 
			PsyTypeSubList, 
			dstrPayType;

	getField (ifds::PaymentFor, dstrPaymentFor, idDataGroup);
	getField (ifds::PayType, dstrPayType, idDataGroup);
	setFieldAllSubstituteValues (ifds::PayType, idDataGroup, ifds::PaymentInstructionsPayType);
	if (isMgtCoPayInstruct ())
	{
		PsyTypeSubList = removeItemFromSubtList (ifds::PayType, CREATE_TRADE, idDataGroup);
		setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
      PsyTypeSubList = removeItemFromSubtList (ifds::PayType, PAYTYPE::SYSTEM_CHEQUE, idDataGroup);
		setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
      PsyTypeSubList = removeItemFromSubtList (ifds::PayType, PAYTYPE::MANUAL_CHEQUE, idDataGroup);
		setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
      PsyTypeSubList = removeItemFromSubtList (ifds::PayType, NSCC, idDataGroup);
		setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
	}
	else
	{		
		if (dstrPaymentFor == I_("NC") || dstrPaymentFor == I_("NT"))
		{
         PsyTypeSubList = removeItemFromSubtList (ifds::PayType, PAYTYPE::SUPPRESS, idDataGroup);
			setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
			PsyTypeSubList = removeItemFromSubtList (ifds::PayType, PAYTYPE::EFT, idDataGroup);
			setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
			PsyTypeSubList = removeItemFromSubtList (ifds::PayType, CREATE_TRADE, idDataGroup);
			setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
         PsyTypeSubList = removeItemFromSubtList (ifds::PayType, PAYTYPE::SYSTEM_CHEQUE, idDataGroup);
			setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
         PsyTypeSubList = removeItemFromSubtList (ifds::PayType, PAYTYPE::MANUAL_CHEQUE, idDataGroup);
			setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
		}			
		else 
		{        
			if (!dstrPaymentFor.empty())
			{
				DString dstrDirectTo;

				getField (ifds::DirectTo, dstrDirectTo, idDataGroup);
				PsyTypeSubList = removeItemFromSubtList (ifds::PayType, NSCC, idDataGroup);
				setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);

				if (dstrPaymentFor != PAYMENT_FOR::TRAILER_FEE || 
					(dstrPaymentFor == PAYMENT_FOR::TRAILER_FEE && dstrDirectTo != ACCOUNT ) )
				{
					PsyTypeSubList = removeItemFromSubtList (ifds::PayType, CREATE_TRADE, idDataGroup);
					setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
				}
			}
		}
/*
      DString dstrPayMethod;

      getField (ifds::PayMethod, dstrPayMethod, idDataGroup);
		if (dstrPayMethod == WIRE)
		{
         PsyTypeSubList = removeItemFromSubtList (ifds::PayType, PAYTYPE::SYSTEM_CHEQUE, idDataGroup);
			setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
         PsyTypeSubList = removeItemFromSubtList (ifds::PayType, PAYTYPE::MANUAL_CHEQUE, idDataGroup);
			setFieldAllSubstituteValues (ifds::PayType, idDataGroup, PsyTypeSubList);
		}
*/
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::setAccountField (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAccountField"));

 	DString dstrPayType;
	
   getField (ifds::PayType, dstrPayType, idDataGroup, false);
	
   bool bDisableAccount = dstrPayType != CREATE_TRADE;
	
   if (bDisableAccount)
	{
		setFieldNoValidate (ifds::AccountNum, NULL_STRING, idDataGroup, false, true, true);
	}
	setFieldReadOnly (ifds::AccountNum, idDataGroup, bDisableAccount);
	setFieldRequired (ifds::AccountNum, idDataGroup, !bDisableAccount);	
	setFieldValid (ifds::AccountNum, idDataGroup, bDisableAccount);
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::directToRelatedChanges( const BFDataGroupId &idDataGroup,
                                                      bool bDataNotFound /*= false*/)
{ 
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "directToRelatedChanges") );    

	DString dstrDirectTo;
	getField( ifds::DirectTo, dstrDirectTo, idDataGroup );
	dstrDirectTo.stripAll();    

	setPayTypeSubSet( idDataGroup );

	bool bDisablePayType = false,
		 bDisableDirectToShrGrp = false;


    if (ACCOUNT == dstrDirectTo)
	{		
		if (idDataGroup != BF::HOST)
		{
			// this will also trigger the clearing out the Account field
			setFieldNoValidate (ifds::PayType, I_( "R" ), idDataGroup, true, true, true, true);
			
			//Clear out shareholder group
			setFieldNoValidate (ifds::DirectToShrGrp, I_( "" ), idDataGroup) ;
		}
		else
		{			
			//payTypeRelatedChanges method will figure out whether
			//it should go ahead and clear out all fields
			payTypeRelatedChanges (idDataGroup, bDataNotFound);
		}		
		bDisablePayType = true;
		bDisableDirectToShrGrp = true;
	}
	else if (PAY_ENTITY == dstrDirectTo)
	{		
		if (idDataGroup != BF::HOST)
		{
			// this will also trigger the clearing out the Account field
         setFieldNoValidate (ifds::PayType, PAYTYPE::EFT, idDataGroup, true, true, true, true );
			
			//Clear out shareholder group			
			setFieldNoValidate( ifds::DirectToShrGrp, I_( "" ), idDataGroup );
		}
		else
		{			
			//payTypeRelatedChanges method will figure out whether
			//it should go ahead and clear out all fields
			payTypeRelatedChanges (idDataGroup, bDataNotFound);
		}				
				
		setAccountField( idDataGroup );
		bDisableDirectToShrGrp = true;
	}
	else if ( SHAREHOLDER_GROUP == dstrDirectTo )
	{				
		if ( idDataGroup != BF::HOST )
		{
			// this will also trigger the clearing out the Account field
         setFieldNoValidate( ifds::PayType, PAYTYPE::SUPPRESS, idDataGroup, true, true, true, true );
		}
		else
		{
			//payTypeRelatedChanges method will figure out whether
			//it should go ahead and clear out all fields
			payTypeRelatedChanges (idDataGroup, bDataNotFound);	
		}

		loadShareholderGroupSet( idDataGroup );	
		bDisablePayType = true;		
	}		 
	
	setFieldReadOnly( ifds::PayType, idDataGroup, bDisablePayType );	

	setFieldRequired( ifds::DirectToShrGrp, idDataGroup, !bDisableDirectToShrGrp );			
	setFieldReadOnly( ifds::DirectToShrGrp, idDataGroup, bDisableDirectToShrGrp );
	setFieldValid (ifds::DirectToShrGrp, idDataGroup, bDisableDirectToShrGrp);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::loadShareholderGroupSet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadShareholderGroupSet"));

   GroupList*  pGroupList= NULL;
   DString dstSubstList = NULL_STRING;

   if( getMgmtCo().getGroupList (pGroupList) <= WARNING &&
	   NULL != pGroupList )
   {
      DString dstSubstList;
      pGroupList->getGroupSubstList( dstSubstList, true);
      dstSubstList.upperCase();
      setFieldAllSubstituteValues( ifds::DirectToShrGrp, idDataGroup, dstSubstList );	  
   }

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::getAgencyNegCommission( const BFDataGroupId &idDataGroup,
													               AgencyNegComm *&pAgencyNegComm )
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAgencyNegCommission" ) );

   DString dstrPayInstructRID;
	
   getField (ifds::PayInstructRID, dstrPayInstructRID, idDataGroup);	

   DString dstrkey = I_("PayInstructRIDe=") + dstrPayInstructRID;

   BFObjectKey objKey (dstrkey , idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_AGENCY_NEGATIVE_COMMISSION );

   pAgencyNegComm = NULL;
   pAgencyNegComm = dynamic_cast<AgencyNegComm*>( findObject( objKey ) );

   if( !pAgencyNegComm  )
   {
      pAgencyNegComm = new AgencyNegComm( *this );
      //do a database inquiry
	  if( pAgencyNegComm->init( dstrPayInstructRID,	                            
	                            idDataGroup) > WARNING )
      {
         delete pAgencyNegComm;
         pAgencyNegComm = NULL;
      }
      else
      {
         setObject (objKey, pAgencyNegComm);
      }
   }   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PaymentInstructions::hasAgencyNegCommission (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateAgencyNegCommission" ) );

	bool bHasNegativeCommission = false;

	DString dstrPaymentFor;
	getField (ifds::PaymentFor, dstrPaymentFor, idDataGroup, false);
	
   if (dstrPaymentFor == PAYMENT_FOR::COMMISSION)
	{		
		AgencyNegComm *pAgencyNegComm = NULL;
		if ( getAgencyNegCommission( idDataGroup, pAgencyNegComm ) <= WARNING &&
			  pAgencyNegComm)
		{
			bHasNegativeCommission = pAgencyNegComm->hasNegativeCommission (idDataGroup);
		}
	}
   return bHasNegativeCommission;
}


//******************************************************************************
SEVERITY PaymentInstructions::validatePaymentForConsolType (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validatePaymentForConsolType"));

	DString paymentFor, 
      consolType;

   getField (ifds::PaymentFor, paymentFor, idDataGroup, false);
   if ( paymentFor == PAYMENT_FOR::REDEMPTION || 
        paymentFor == PAYMENT_FOR::DISTRIBUTION)
   {
      getField (ifds::ConsolType, consolType, idDataGroup, false);
      if (consolType == CONSOL_TYPE::NOT_AVAILABLE) // NOT_AVAILABLE
		{	
			DString idiStr,
            payForDescr;
         getField (ifds::PaymentFor, payForDescr, idDataGroup, true);
			addIDITagValue (idiStr, I_("PAYMENTFOR"), payForDescr);
// Consolidation Type can not be N/A for the %PAYMENTFOR%
			ADDCONDITIONFROMFILEIDI (CND::ERR_CONSOL_NOT_VALID, idiStr);
		}
	}
	/*	if ( paymentFor == PAYMENT_FOR::DISTRIBUTION && 
           consolType == CONSOL_TYPE::BULKING_NETTING) // Bulking and Netting 
// "Bulking and Netting" is not available for Distribution
			ADDCONDITIONFROMFILE (CND::ERR_CONSOL_NOT_VALID_FOR_DISTRIBUTION);
   }*/
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PaymentInstructions::isMgtCoPayInstruct ()
{
   return _searchType == I_("MGMTCO");
}

//******************************************************************************
SEVERITY PaymentInstructions::getBroker ( Broker *&pBroker,
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getBroker"));
   pBroker = NULL;

   DString brokerCode;

   getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
   if (!brokerCode.empty())
   {
      DString strKey (I_("Broker=") + brokerCode);
//look for the list
      BrokerList *pBrokerList = 
            dynamic_cast <BrokerList*> (getObject ( strKey, 
                                                    idDataGroup));
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
SEVERITY PaymentInstructions::getBranch ( Branch *&pBranch,
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getBranch"));
   pBranch = NULL;

   DString brokerCode, 
      branchCode;

   getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
   getField (ifds::BranchCode, branchCode, idDataGroup, false);
   if ( !brokerCode.empty() && 
        !branchCode.empty())
   {
      DString strKey 
            (I_("Broker=") + brokerCode + I_(";Branch=") + branchCode);

      BranchList* pBranchList = 
            dynamic_cast <BranchList*> (getObject (strKey, idDataGroup));
      if (!pBranchList) //make view call
      {
         pBranchList = new BranchList (*this);
         if (pBranchList->init ( brokerCode, //exact match
                                 branchCode) <= WARNING)
         {
            setObject ( pBranchList, 
                        strKey,
                        OBJ_ACTIVITY_NONE,
                        idDataGroup);
         }
         else 
         {
            delete pBranchList;
            pBranchList = NULL;
         }
      }
//get the branch
      if (pBranchList)
      {
         BFObjIter bfIter (*pBranchList, idDataGroup);

         bfIter.begin();
         if (!bfIter.end())
         {
            pBranch = dynamic_cast <Branch*> (bfIter.getObject());
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::getAgent ( Agent *&pAgent,
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAgent"));
   pAgent = NULL;

   DString brokerCode, 
      branchCode,
      slsrepCode,
      createRep;

   getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
   getField (ifds::BranchCode, branchCode, idDataGroup, false);
   getField (ifds::SalesRepCode, slsrepCode, idDataGroup, false);
   if ( !brokerCode.empty() && 
        !branchCode.empty() &&
        !slsrepCode.empty())
   {
      DString strKey ( I_("Broker=") + brokerCode + 
                       I_(";Branch=") + branchCode + 
                       I_(";Agent=") + slsrepCode);
      AgentList *pAgentList = dynamic_cast <AgentList*> 
                                      ( getObject ( strKey, 
                                                    idDataGroup));

      if (!pAgentList) //make view call
      {         
         pAgentList = new AgentList (*this);

         if (pAgentList->init ( brokerCode, //exact match
                                branchCode, 
                                slsrepCode) <= WARNING)
         {
            setObject ( pAgentList, 
                        strKey,
                        OBJ_ACTIVITY_NONE,
                        idDataGroup);
         }
         else
         {
            delete pAgentList;
            pAgentList = NULL;
         }
      }
//get the agent
      if (pAgentList)
      {
         BFObjIter bfIter (*pAgentList, idDataGroup);

         bfIter.begin();
         if (!bfIter.end())
         {
            pAgent = dynamic_cast <Agent*> (bfIter.getObject());
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::getPayEntityDates ( DString &effectiveDate, 
                                                  DString &stopDate, 
                                                  DString &peEfDtFmt,
                                                  DString &peStpFmt,
                                                  const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME,  I_("getPayEntityDates"));

	effectiveDate = stopDate = peEfDtFmt = peStpFmt = NULL_STRING;

	DString	broker;
	DString	instrEffectiveDate;
	DString	instrStopDate;
	bool	found = false;
   
	getField (ifds::BrokerCode, broker, idDataGroup, false);
	getField (ifds::EffectiveDate, instrEffectiveDate, idDataGroup, false);
	getField (ifds::StopDate, instrStopDate, idDataGroup, false);

	if (!broker.empty())
	{
		DString strKey (I_("PayToEntity_BrokerCode=") + broker);
		PayToEntity *pPayToEntity = NULL;

		pPayToEntity = dynamic_cast <PayToEntity*> ( getObject ( strKey, idDataGroup));
		
		if (!pPayToEntity)
		{
			PayToEntityList *pPayToEntityList (NULL); //= new PayToEntityList (*this);
			DistributorRepository *pDistributorRepository (NULL);
			if (getWorkSession().getDistributorRepository (pDistributorRepository) <= WARNING && pDistributorRepository)
			{
				if (pDistributorRepository->getPayToEntityList( broker,	NULL_STRING, pPayToEntityList, 
															idDataGroup) <= WARNING && pPayToEntityList)
				{
					DString	instrPaymentFor,
							instrPayToEntity;
					  
					getField (ifds::PaymentFor, instrPaymentFor, idDataGroup);
					getField (ifds::PayToEntity, instrPayToEntity, idDataGroup, false);
					
					if (!instrPaymentFor.empty () && !instrPayToEntity.empty())
					{
						BFObjIter iter ( *pPayToEntityList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
				      
						while (!iter.end ())
						{
							PayToEntity *pPayToEntity_ = dynamic_cast <PayToEntity*> (iter.getObject());
							
							if (pPayToEntity_)
							{
								DString	entityEffectiveDate,
										entityStopDate,
										entityPaymentFor,
										entityPayToEntity;

								pPayToEntity_->getField (ifds::PaymentFor, entityPaymentFor, idDataGroup);
								pPayToEntity_->getField (ifds::PayToEntity, entityPayToEntity, idDataGroup);
								pPayToEntity_->getField (ifds::EffectiveDate, entityEffectiveDate, idDataGroup);
								pPayToEntity_->getField (ifds::StopDate, entityStopDate, idDataGroup);
                                entityPaymentFor.upperCase();
                                entityPayToEntity.upperCase();
                                instrPaymentFor.upperCase();
                                instrPayToEntity.upperCase();

                                if ( (   entityPaymentFor  == instrPaymentFor  && 
									     entityPayToEntity == instrPayToEntity    )  ||
		   							 ( ( instrPaymentFor == I_("CO")  ||
			   						     I_("NC") == instrPaymentFor     )  && 
				  					     entityPayToEntity == I_("ALL")        )         ) 
								{
									bool bEffectiveInRange = DSTCommonFunctions::IsDateBetween ( entityEffectiveDate, entityStopDate, instrEffectiveDate);
									bool bStopInRange = DSTCommonFunctions::IsDateBetween (entityEffectiveDate, entityStopDate, instrStopDate);

									if (bEffectiveInRange && bStopInRange)
									{
										found = true;
										break; //found pay to entity
									}
						       }
					       }
					       ++iter;
						}
					}
				}
			}
		}

		if (!found)
		{
			ADDCONDITIONFROMFILE (CND::ERR_PI_DATES_NOT_WITHIN_PE_DATES);
		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PaymentInstructions::doesTransTypeHasDefault( const DString &dstrConsolTransType, const BFDataGroupId& idDataGroup )
{
	bool bFound = false;
	DString dstrConsolTransTypeList;
	getWorkSession().getOption ( ifds::ConsolTransType, dstrConsolTransTypeList, BF::HOST, false);
	bFound = DSTCommonFunctions::codeInList (dstrConsolTransType, dstrConsolTransTypeList );
	return bFound;
}

//******************************************************************************
SEVERITY PaymentInstructions::setConsolTypeSubstituteValues ( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setConsolTypeSubstituteValues"));
	DString dstrPaymentFor, dstrPurchNetting;
	getField (ifds::PaymentFor, dstrPaymentFor, idDataGroup, false);

	getWorkSession().getOption ( ifds::PurchNetting, dstrPurchNetting, BF::HOST, false);
	if ( dstrPaymentFor == I_("PW")&& dstrPurchNetting != I_("0") )//DSTCommonFunctions::codeInList (dstrPurchNetting, I_("1,2,3") ) )
	{
		setFieldAllSubstituteValues (ifds::ConsolType, idDataGroup, ifds::PayInstructConsolType);
	}
	else
	{
		setFieldAllSubstituteValues (ifds::ConsolType, idDataGroup, ifds::PayInstructConsolTypeNotPW);
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
bool PaymentInstructions::getDefaultConsolType ( DString &dstrConsolTransType, 
											 DString &dstrConsolidation, 
											 DString &dstrConsolDefault,
											 const BFDataGroupId &idDataGroup)
{
   bool bFoundTransType = false;   
   DString dstrConsolTransTypeList, dstrConsolidationList, dstrConsolDefaultList;
      
//initialize the output parameters
   dstrConsolidation = dstrConsolDefault  = NULL_STRING;
   getWorkSession().getOption ( ifds::ConsolTransType, dstrConsolTransTypeList, BF::HOST, false);
	if ( dstrConsolTransTypeList == NULL_STRING )
		return bFoundTransType;

   getWorkSession().getOption ( ifds::Consolidation, dstrConsolidationList, BF::HOST, false);
   getWorkSession().getOption ( ifds::ConsolDefault, dstrConsolDefaultList,     BF::HOST, false);
   
//start chopping the strings
   do
   {
      DString::size_type pos = 0;
      DString transType_;

      EXTRACT_VALUE(dstrConsolTransTypeList, transType_)
      if (transType_ == dstrConsolTransType) //found the transaction type
      {
         EXTRACT_VALUE (dstrConsolidationList, dstrConsolidation)
         EXTRACT_VALUE (dstrConsolDefaultList, dstrConsolDefault)
			bFoundTransType = true;
         break;
      }
      else //cut the strings
      {
         CHOP_STRING (dstrConsolTransTypeList)
         CHOP_STRING (dstrConsolidationList)
         CHOP_STRING (dstrConsolDefaultList)
      }
   }
   while (dstrConsolTransTypeList != NULL_STRING);
   return bFoundTransType;
}

//******************************************************************************
SEVERITY PaymentInstructions::validateConsolType (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateConsolType"));

	DString paymentFor, consolType;

   getField (ifds::PaymentFor, paymentFor, idDataGroup, false);
   getField (ifds::ConsolType, consolType, idDataGroup, false);
	
	DString dstrConsolidation, dstrConsolDefault;
	bool bFound =  getDefaultConsolType ( paymentFor, dstrConsolidation, dstrConsolDefault, idDataGroup );
	if ( bFound )
	{
		if ( dstrConsolidation == NO && consolType != dstrConsolDefault )
		{
			ADDCONDITIONFROMFILE (CND::WARN_DEF_CONSOL_TYPE);
		}
		if ( dstrConsolidation == YES && consolType == NULL_STRING )
		{
			ADDCONDITIONFROMFILE (CND::CONSOL_TYPE_MANDATORY);
		}
	}
	
	if ( dstrConsolidation == NULL_STRING && consolType != NULL_STRING )
	{
		ADDCONDITIONFROMFILE (CND::ERR_INVALID_CONSOL_VALUE);
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PaymentInstructions::initConsolidation ( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initConsolidation"));

   DString paymentFor;
   
   getField (ifds::PaymentFor, paymentFor, idDataGroup);
	if ( paymentFor != NULL_STRING )
	{
		DString dstrConsolidation, dstrConsolDefault;
		bool bFound = getDefaultConsolType ( paymentFor, dstrConsolidation, dstrConsolDefault, idDataGroup );
		setConsolTypeSubstituteValues ( idDataGroup ) ;
		bool bReadOnly = dstrConsolidation == I_("Y") ? false : true;
		
		if ( isNew() )
		{
			if ( bFound )
			{
				DString dstrDefaultSet;
				dstrDefaultSet = dstrConsolidation == I_("Y") ? dstrConsolDefault : I_("0");
				//setConsolTypeSubstituteValues ( idDataGroup ) ;
				setFieldNoValidate (ifds::ConsolType, dstrDefaultSet, idDataGroup, false, true, true, false);
			}
			else
			{
				setFieldNoValidate (ifds::ConsolType, 
						CONSOL_TYPE::INDIVIDUAL_PAYMENT, idDataGroup, false, true, true, false);
			}
		}

		setFieldReadOnly (ifds::ConsolType, idDataGroup, bReadOnly );
		setFieldRequired (ifds::ConsolType, idDataGroup, !bReadOnly);
		setValidFlag (ifds::ConsolType, idDataGroup, bReadOnly);
	}
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************

SEVERITY PaymentInstructions::setDefaultPayment(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setDefaultPayment"));
   DString dstrACHProcessor;
   getField( ifds::ACHProcessor, dstrACHProcessor, idDataGroup );
   if( dstrACHProcessor.strip().upperCase() == BAFF )
   {
      setFieldNoValidate( ifds::PaymentIdMethod, MT202, idDataGroup, false, true, true );
   }
   else
   {
      setFieldNoValidate( ifds::PaymentIdMethod, NULL_STRING, idDataGroup, false, true, true );
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

/******************************************************************************
Input:DataGroupID
OutPut:None
Return:Severity
Functionality:Sets the  Paymentroutingtype	sub list
******************************************************************************/
SEVERITY PaymentInstructions::buildPaymentRoutingSet(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("buildPaymentRoutingSet"));
	DString dstrTradelevelOveride,dstrPymtRoutingMthd,dstrPymtRoutingMthdSet;
	DString outdstrpymtLevelRoutingSet = NULL_STRING;

	getWorkSession ().getOption (ifds::PymtRoutingMthd,dstrPymtRoutingMthd,BF::HOST,false); 
	BFProperties *pBFProperties=
      getFieldProperties (ifds::PaymentIdMethod, idDataGroup); //changing the field name to PaymentIdMethod
    assert (pBFProperties);
    if (pBFProperties)
    {
      pBFProperties->getAllSubstituteValues (dstrPymtRoutingMthdSet);
    } 
	outdstrpymtLevelRoutingSet.stripAll();
	dstrPymtRoutingMthdSet.stripAll();
	if(	! dstrPymtRoutingMthd.empty()  ||
		! dstrPymtRoutingMthdSet.empty() )
   {
    I_CHAR *temp = const_cast<I_CHAR*> (dstrPymtRoutingMthdSet.c_str ());
    do
    {
         DString dstrPymtRoutingMthdSetCode,dstrPymtRoutingMthdSetDescr;   
         temp = parseIdiString (temp, dstrPymtRoutingMthdSetCode, dstrPymtRoutingMthdSetDescr);         
         if (isCodeInList (dstrPymtRoutingMthdSetCode,dstrPymtRoutingMthd))
         {
            outdstrpymtLevelRoutingSet += dstrPymtRoutingMthdSetCode + I_("=") + 
				                          dstrPymtRoutingMthdSetDescr + I_(";");
         }
    } while (temp && temp != NULL_STRING && *temp);
   }
   pBFProperties->setAllSubstituteValues (outdstrpymtLevelRoutingSet);
   return GETCURRENTHIGHESTSEVERITY();
}
/******************************************************************************
Input:DataGroupID
OutPut:None
Return:Void
Functionality:Loads the initializeSubstitutionList based on Misc Info status based 
              on the group code passed in
******************************************************************************/
void PaymentInstructions:: initializeSubstitutionList (const BFFieldId& idField, const DString &dstrGroupCode, const BFDataGroupId& idDataGroup)
{
   TranslationTable* pTranslationTable = NULL;
   DString dstrSubstitutionList;

   getMgmtCo ().getTranslationTable (dstrGroupCode, pTranslationTable);
   if (pTranslationTable)
   {
      pTranslationTable->getSubstitutionList (dstrSubstitutionList);
      dstrSubstitutionList =  BLANK_SUBSTITUTION_VALUE + dstrSubstitutionList ;
      setFieldAllSubstituteValues (idField, idDataGroup, dstrSubstitutionList);
   }
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PaymentInstructions.cpp-arc  $
// 
//    Rev 1.78   Aug 25 2011 11:04:44   wutipong
// IN2579232 - Bulking testing - add code fix to default consolidation type to 'individual' if the transtype does not present in GC.
// 
// Also fix the bug that when dummy object is created in payment instruction screen in the case that the screen is opened via pay to entity screen, the consolidation is not populated.
// 
//    Rev 1.77   05 Mar 2009 11:06:56   popescu
// Incident# 1612716 MSD Trailer Fee Payment Instruction Issue
// 
//    Rev 1.76   Aug 07 2008 19:17:30   wongsakw
// IN#1222816 - Pay Instruction Field No Longer Displayed
// 
//    Rev 1.75   Aug 04 2008 06:30:32   daechach
// in# 1222816 - Pay Instruction Field No Longer Displayed. (check in for Noom)
// 
//    Rev 1.74   Aug 16 2007 11:01:48   kovacsro
// PET2388FN01 - Swift Payment Method Id - finalized
// 
//    Rev 1.73   Aug 09 2007 14:04:44   jankovii
// PET 2388 FN01 - Swift Payment Method ID.
// 
//    Rev 1.72   Jun 01 2007 15:55:16   jankovii
// Incident #900128- Trailer Fee bulking
// 
//    Rev 1.71   May 01 2007 10:24:30   jankovii
// IN 862766 - Payment instr.
// 
//    Rev 1.70   Feb 16 2007 14:21:32   ZHANGCEL
// Incident #824968 -- Fix Consolidation type setting issue
// 
//    Rev 1.69   Jan 26 2007 15:50:26   ZHANGCEL
// PET2306 FN02 -- Some modification for the enhancement
// 
//    Rev 1.68   Jan 24 2007 16:51:12   ZHANGCEL
// PET2306 FN02 -- Add logic for the enhancement
// 
//    Rev 1.67   Nov 29 2006 09:59:08   popescu
// Incident 766519 - set currency option to read only if payfor = ID/PW
// 
//    Rev 1.66   Nov 27 2006 18:36:54   popescu
// Incident 766519 - synchup from release 73 
// 
//    Rev 1.65   Nov 03 2006 16:17:20   ZHANGCEL
// Incident 731541 -- Add logice to check Pair
// 
//    Rev 1.64   Oct 30 2006 15:52:24   popescu
// Incident #743221 -- Bypass EffectiveDate and StopDate validation for Mgmt company
// 
//    Rev 1.63   Oct 30 2006 15:09:08   ZHANGCEL
// Incident #743221 -- Bypass EffectiveDate and StopDate validation for Mgmt company
// 
//    Rev 1.62   Oct 25 2006 10:13:18   porteanm
// Incident 731541 - commented out the code for this Incident.
// 
//    Rev 1.61   Oct 20 2006 18:14:46   popescu
// Incident# 731541 reviewed the way related changes for  fields is working in paym instruct
// 
//    Rev 1.60   Oct 19 2006 16:24:14   ZHANGCEL
// STP PET 2213/17 -- Added Redemption/Distribution pair validation logic
// 
//    Rev 1.59   Oct 06 2006 14:21:54   popescu
// Incident# 651066 - fixed crash if salesrep/broker/branch are not found - synch from 72 
// 
//    Rev 1.58   Sep 30 2006 00:54:28   popescu
// Incident 720294 - pay entity eff. dates
// 
//    Rev 1.57   Sep 24 2006 23:19:42   popescu
// PET 2217/13 changed the criteria for validating a crcy - looks for more acct usages when PW or ID
// 
//    Rev 1.56   Sep 22 2006 18:00:38   ZHANGCEL
// PET2212 FN10 - Add logic to validate CurrencyOption
// 
//    Rev 1.55   Sep 21 2006 19:28:22   popescu
// STP PET 2213/17
// 
//    Rev 1.54   Sep 14 2006 12:35:08   porteanm
// STP 2192/FN 13
// 
//    Rev 1.53   Sep 13 2006 19:11:06   popescu
// STP 2192/FN 13
// 
//    Rev 1.52   Sep 12 2006 10:52:56   popescu
// STP - PET 2192/11
// 
//    Rev 1.51   Sep 10 2006 17:59:06   popescu
// STP 2192/12
// 
//    Rev 1.50   Aug 28 2006 15:39:14   ZHANGCEL
// PET2212 FN10 -- Added new logic for Netting Bulking Redemption and Distribution Payment
// 
//    Rev 1.49   Jul 31 2006 17:58:12   ZHANGCEL
// PET2192 FN11 - MgmtCo Banking related changes
// 
//    Rev 1.48   Jul 27 2006 18:00:14   ZHANGCEL
// PET2192 FN11 - Commission Payments to MgmtCo related changes
// 
//    Rev 1.47   Jun 07 2006 13:27:00   porteanm
// PET2132 FN03 - Edit check for Negative Commission.
// 
//    Rev 1.46   May 31 2006 17:56:40   porteanm
// PET2132 FN03 - Edit check for Negative Commission.
// 
//    Rev 1.45   Mar 24 2006 18:24:36   ZHANGCEL
// PET2132 - FN02 -- Correct Sync up mistakes
// 
//    Rev 1.44   Mar 24 2006 10:25:06   AGUILAAM
// PET2132_FN02: sync-up from Rel68. ver 1.40.1.1
// 
//    Rev 1.43   Mar 23 2006 16:27:40   ZHANGCEL
// PET2132 -- Sync up to 1.40.1.0
// 
//    Rev 1.42   Feb 17 2006 13:51:44   AGUILAAM
// PET2016_FN05: payment instructions enhancement, shrgroup is required when DirectTo is ShrGrp.
// 
//    Rev 1.41   Jan 25 2006 10:19:26   AGUILAAM
// PET2016_FN05: AXA Office Trailer Fee Indicator
// 
//    Rev 1.40   Jan 06 2006 14:41:30   popescu
// Incident# 513119 - reinvest added to payment type instead of payment method
// 
//    Rev 1.38.1.0   Jan 06 2006 14:04:52   popescu
// Incident# 513119 - reinvest added to payment type instead of payment method
// 
//    Rev 1.38   Nov 15 2005 13:02:04   AGUILAAM
// PET1243_FN00_ABN AMRO Trailer Fee Processing: added account validations and setting of paymethod substitution set
// 
//    Rev 1.37   Nov 01 2005 09:17:38   AGUILAAM
// PET1243_FN00_ABN AMRO Trailer Fee Processing - additional enhancements
// 
//    Rev 1.36   Oct 19 2005 17:16:28   AGUILAAM
// PET1243_FN00: ABN AMRO Trailer Fee Processing
// 
//    Rev 1.35   Jun 21 2005 15:27:08   Fengyong
// #Incident 336650 - if Payment for is NSCC then do not check banking for wire.
// 
//    Rev 1.34   Dec 07 2004 14:46:30   Fengyong
// PTS10034745 - syncup
// 
//    Rev 1.33   Nov 30 2004 14:15:04   hernando
// PTS 10036108 - Fixed the broker/branch/salesrep not found issue; there is a case when pay entity/instruct records are in the database but the correspondent brokers/branches/sales reps are not.  SYNCHRONIZED EXCLUSIVELY WITH 1.29.1.1
// 
//    Rev 1.32   Nov 26 2004 18:35:44   Fengyong
// Syncup PTS10034745
// 
//    Rev 1.31   Nov 26 2004 13:05:16   Fengyong
// PET10034745
// 
//    Rev 1.30   Nov 14 2004 14:50:50   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.29   May 20 2004 13:45:08   FENGYONG
// PET 944 FN01 - NSCC new reqirement, default currency option
// 
//    Rev 1.28   Apr 16 2004 16:45:50   FENGYONG
// PET944FN01 , When PayType == NSCC then set ACHProcessor readonly
// 
//    Rev 1.27   Apr 07 2004 18:38:06   FENGYONG
// PET944FN01 rel56.1 NSCC Broker
// 
//    Rev 1.26   Apr 06 2004 11:17:16   popescu
// PET944 FN01, release 56.1 NSCC Broker Matrix
// 
//    Rev 1.25   Apr 05 2004 17:29:46   FENGYONG
// PET944 FN01, release 56.1 NSCC Broker Matrix
// 
//    Rev 1.24   Mar 12 2004 12:55:10   popescu
// PTS 10027880, display/load file processor when payment made in FundCurrency
// 
//    Rev 1.23   Mar 04 2004 17:48:56   popescu
// PTS 10027865, fixed crash in Pay to entity search for inactive brokers. Disabled 'Instructions' button in pay to entity dialog if broker is inactive/not effective
// 
//    Rev 1.22   Feb 25 2004 09:10:32   popescu
// PTS 10027184, in a non-multi currency environment the file processor substitution list should be set to empty string
// 
//    Rev 1.21   Feb 18 2004 18:01:16   popescu
// PTS 10027184; - moved the ownership of the payment instructions banking list at the payment instructions CBO level.
// - clean-up the work session every time user hits 'Search' on the Features Search Dialog
// - do not add payment instructions/ pay to entity records, when refreshing the respective CBO lists in DistributorRepository, always read them from back-end. Now, this is possible since the work session is cleaned-up all the time.
// - fixed crash that happens when a new record is added to the payment instructions bank list. The scenario to get this crash is: go to pay to entity screen, then click the 'instructions' button, modify an existing payment instructions record with bank information. Hit okay, commit the changes in the parent. Go back to the payment instructions (you will notice that the previous changes are not saved -  another issue that has been fixed with this ticket), and then click the Bank button. Add a new bank record. Desktop reports an internal error.
// - use new IFDSListCtrl, for the PayToEntity list and PaymentInstructions list.
// 
//    Rev 1.20   Feb 11 2004 18:45:24   popescu
// PTS 10026899, reloaded currency set for Suppress pay type in Payment Instructions, loaded banking currency dynamically based on the file processor value if not empty
// 
//    Rev 1.19   Feb 10 2004 12:29:06   popescu
// PTS 10026204, payment instructions is loading the file processor dynamicaly; set the correct substitution set for file processor for a modified trade (copied from 'Pending Trade')
// 
//    Rev 1.18   Sep 05 2003 09:52:34   popescu
// Reversed to a hard-coded BAFF subst set, because datadictionary doesn't allow an empty code for a subst set item and fixed the defautl value for pay to entity, in case we are in an split commission environment and the Pay to entity in the Pay to entity screen is se to 'ALL'
// 
//    Rev 1.17   Aug 28 2003 17:57:16   popescu
// PTS 10021242, load the BAFF currencies after changing the currency option field Rel 52.1
// 
//    Rev 1.16   Aug 26 2003 13:54:56   HERNANDO
// PTS 10021007 - ACHProcessor becomes blank and read-only if suppressed.
// 
//    Rev 1.15   Aug 18 2003 11:26:52   popescu
// if pay in fund currency, the value of currency should be null although BAFF is selected
// 
//    Rev 1.14   Aug 18 2003 11:18:50   popescu
// PTS 10020750
// Reset the currency set to the 'ALL' currencies if the user changes the value of the file processor to an empty string
// 
//    Rev 1.13   Aug 07 2003 18:39:56   popescu
// tighten the validation of the currency in case of currency option is payment in fund currency
// 
//    Rev 1.12   Aug 07 2003 14:48:52   popescu
// simplified the doReset
// 
//    Rev 1.11   Jul 31 2003 21:59:04   popescu
// Added support for PayType 'X' and support for Historical Info at the process level
// 
//    Rev 1.10   Jul 29 2003 17:07:08   popescu
// Enabled correspondent banking for AcctUsage Commission and Trailer Fee
// 
//    Rev 1.9   Jul 26 2003 19:37:42   popescu
// fixes related with the duplicate checks
// 
//    Rev 1.8   Jul 25 2003 17:48:38   popescu
// simplified the doApplyRelatedChanges, check the validation against the TrailerrFee instead of CommssionHolding for Wire 
// 
//    Rev 1.7   Jul 25 2003 14:26:16   popescu
// Fix crash in payment instructions dialog, as result of filtering the payment instructions list, cleared the address fields when the checque option is selected for the payment method
// 
//    Rev 1.6   Jul 11 2003 20:07:24   popescu
// strip all and uppercase the br,bra, slsrep codes
// 
//    Rev 1.5   Jul 11 2003 13:46:54   popescu
// fixes related to the confirmation screen showing up even if there are no changes for the payment instructions screen, added validation for the Currency if BAAF is selected as the file processor
// 
//    Rev 1.4   Jul 10 2003 22:59:04   popescu
// latest changes to pay instruct, filtered correctly the screen, based on the input
// 
//    Rev 1.3   Jul 10 2003 22:20:54   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.2   Jul 09 2003 21:56:54   popescu
// Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
// 
//    Rev 1.1   Jul 02 2003 17:49:34   popescu
// work for payment instructions feature 
// 
//    Rev 1.0   Jul 01 2003 18:17:14   popescu
// Initial revision.
 */