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
// ^FILE   : RRIF_LIF_LRIF_Info.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : Feb 07, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RRIF_LIF_LRIF_Info
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "address.hpp"
#include "addresslist.hpp"
#include "demographics.hpp"
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include <ifastdataimpl\dse_dstc0011_vw.hpp>
#include <ifastdataimpl\dse_dstc0067_vw.hpp>
#include <ifastdataimpl\dse_dstc0067_req.hpp>
#include <ifastdataimpl\dse_dstc0068_vw.hpp>
#include <ifastdataimpl\dse_dstc0068_req.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>
#include <ifastdataimpl\dse_dstc0129_req.hpp>
#include <ifastdataimpl\dse_dstc0129_vw.hpp>
#include <ifastdataimpl\dse_dstc0130_vw.hpp>
#include <ifastdataimpl\dse_dstc0130_req.hpp>
#include <ifastdataimpl\dse_dstc0375_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include "bankinstructions.hpp"
#include "financialinstitution.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "rrif_lif_lrif_info.hpp"
#include "rrif_lif_lrif_infolist.hpp"
#include "ToFundAllocList.hpp"
#include "FromFundAllocList.hpp"
#include "TaxTypeRule.hpp"
#include "TaxTypeRuleList.hpp"
#include "GMWBValidation.hpp"
#include "rrif_lif_lrif_paymentscalculation.hpp"
#include "RRIFBankInstructionsList.hpp"
#include "shareholder.hpp"
#include "errmsgruleslist.hpp"
#include "RRIFUnusedMaxAmt.hpp"

#include <bfutil\clientlocalecontext.hpp>

namespace
{
   // Trace literals
    const I_CHAR * const CLASSNAME = I_( "RRIF_LIF_LRIF_Info" );

    const I_CHAR * const RIF_ID_FIELD           = I_( "RIFId" );
    const I_CHAR * const YES                    = I_( "Y" );
    const I_CHAR * const NO                     = I_( "N" );
    const I_CHAR * const RIF_SRCOFFOUND_VALUE1  = I_( "E" );
    const I_CHAR * const RIF_SRCOFFOUND_VALUE2  = I_( "I" );
    const I_CHAR * const GROSS                  = I_( "01" );
    const I_CHAR * const NET                    = I_( "02" );
    const I_CHAR * const NET_OF_FEES            = I_( "03" );
    const I_CHAR * const PERCENT            = I_( "Percent" );
    const I_CHAR * const DOLLAR             = I_( "Dollar" );
    const I_CHAR * const ZERO               = I_( "0" );
    const int MININDEXRATE                  = 0;
    const int MAXINDEXRATE                  = 20;
    const I_CHAR * const ACCOUNT_TYPE       = I_( "ACCOUNT_TYPE" );
    const I_CHAR * const CURRENT_BUS_DATE   = I_( "CURRENT_BUS_DATE" );
    const I_CHAR * const MAND_AMT_YR_SYS_CALC = I_( "MAND_AMT_YR_SYS_CALC" );
    const I_CHAR * const RATE_SYS_CALC      = I_( "RATE_SYS_CALC" );
    const I_CHAR * const LEG_MIN_WITH_AGE   = I_( "LEG_MIN_WITH_AGE" );
    const I_CHAR * const FUND_ALLOC_LIMIT   = I_( "FUND_ALLOC_LIMIT" );
    const I_CHAR * const SYS_CURRENCY       = I_( "SYS_CURRENCY" );
    const I_CHAR * const AMOUNT             = I_( "AMOUNT" );
    const I_CHAR * const CALCULATED         = I_( "CALCULATED" );
    const I_CHAR * const RATE_PUID          = I_( "RATE_PUID" );
    const I_CHAR * const BLANKSTRING        = I_( " " );
    const I_CHAR * const MIN                = I_( "MIN" );
    const I_CHAR * const MAX                = I_( "MAX" );

    const I_CHAR * const FREQ_DAILY         = I_( "0" );
    const I_CHAR * const FREQ_WEEKLY        = I_( "1" );
    const I_CHAR * const FREQ_BIWEEKLY      = I_( "2" );
    const I_CHAR * const FREQ_MONTHLY       = I_( "3" );
    const I_CHAR * const FREQ_SEMIMONTHLY   = I_( "4" );
    const I_CHAR * const FREQ_QUARTERLY     = I_( "5" );
    const I_CHAR * const FREQ_SEMIANNUALLY  = I_( "6" );
    const I_CHAR * const FREQ_ANNUALLY      = I_( "7" );
    const I_CHAR * const FREQ_OTHER         = I_( "8" );

    const I_CHAR * const NON_REGISTERED_TAX_TYPE    = I_( "0" ); 
    const I_CHAR * const RRSP_TAX_TYPE              = I_( "1" ); 
    const I_CHAR * const RRIF_TAX_TYPE              = I_( "2" ); 
    const I_CHAR * const INDIVIDUAL_RESP_TAX_TYPE   = I_( "9" );
    const I_CHAR * const LIRA_TAX_TYPE              = I_( "C" ); 
    const I_CHAR * const LRSP_TAX_TYPE              = I_( "U" ); 
    const I_CHAR * const LRIF_TAX_TYPE              = I_( "L" );
    const I_CHAR * const PRIF_TAX_TYPE              = I_( "R" );	
    const I_CHAR * const FAMILY_RESP_TAX_TYPE       = I_( "M" );
 
    const I_CHAR * const PAY_OPTION_FIX             = I_( "F" );
    const I_CHAR * const PAY_OPTION_INDEX           = I_( "I" );
    const I_CHAR * const PAY_OPTION_MINIMUM         = I_( "M" );
    const I_CHAR * const PAY_OPTION_MAXIMUM         = I_( "X" );
    const I_CHAR * const PAY_OPTION_PERCENT         = I_( "P" );
    const I_CHAR * const FROMFUNDALLOCLIST          = I_( "FromFundAllocList" );
    const I_CHAR * const TOFUNDALLOCLIST            = I_( "ToFundAllocList" );
    const I_CHAR * const EX_FER_IN_CODE             = I_( "XFIN" );   // trade trans type Exchange In 
    const I_CHAR * const SUPPRESS					    = I_( "X" );
	const I_CHAR * const FEDERAL                     = I_( "9999" ); 

    const I_CHAR * const GWLWA_OPTIONS				    = I_( "G,L" );

    const double dSmallValue                        = .0000000001;

    const I_CHAR * const GROSS_NET_METHOD_GROSS     = I_("01");
    const I_CHAR * const PAY_METHOD_GWA             = I_("G");
    const I_CHAR * const PAY_METHOD_LWA             = I_("L");

}

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
   extern const long INFO_SHAREHOLDER_HAS_MULTIPLE_ADDRESSES;
   extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
   extern const long ERR_RIF_EMPTY_EFFECTIVE_DATE;     
   extern const long ERR_RIF_PAST_EFFECTIVE_DATE;      
   extern const long ERR_RIF_WRONG_STOP_DATE;          
   extern const long ERR_RIF_INVALID_RIF_SRC_OF_FUND;  
   extern const long ERR_RIF_TOO_BIG_MAND_AMT_YR;      
   extern const long ERR_RIF_WRONG_VALUE_MAND_AMT_YR;  
   extern const long ERR_RIF_TOO_SMALL_MAX_AMT_YR;     
   extern const long ERR_RIF_MONTH;                    
   extern const long ERR_RIF_NEGATIVE_AMOUNT;          
   extern const long ERR_RIF_ZERO_OR_NEGATIVE_AMOUNT;  
   extern const long ERR_RIF_TOO_SMALL_AMOUNT;         
   extern const long ERR_RIF_TOO_BIG_AMOUNT;           
   extern const long ERR_RIF_NON_ZERO_RATE;            
   extern const long ERR_RIF_TOO_BIG_RATE;             
   extern const long ERR_RIF_TOO_MANY_DECIMALS_RATE;   
   extern const long ERR_RIF_SUM_TOO_BIG1_RATE;        
   extern const long ERR_RIF_SUM_TOO_BIG2_RATE;        
   extern const long ERR_RIF_QUALIFIED;                
   extern const long ERR_RIF_INVALID_RATE_PUD;         
   extern const long ERR_RIF_FUTURE_BIRTHDATE;         
   extern const long ERR_RIF_NO_SHAREHOLDER_BIRTHDATE; 
   extern const long ERR_RIF_INVALID_PAY_OPTION;       
   extern const long ERR_RIF_NO_MAXIMUM_PAY_OPTION;    
   extern const long ERR_RIF_OUT_OF_RANGE_INDEX_RATE;  
   extern const long ERR_RIF_NON_ZERO_INDEX_RATE;      
   extern const long ERR_RIF_INVALID_GROSS_OR_NET;     
   extern const long ERR_RIF_UNKNOWN_ADDRESS_CODE;     
   extern const long ERR_RIF_MANDATORY_PAY_TYPE;       
   extern const long ERR_RIF_INVALID_PAY_TYPE;         
   extern const long ERR_RIF_TOO_BIG_MIN_WITH_AGE;     
   extern const long ERR_RIF_MANDATORY_MIN_WITH_AGE;   
   extern const long ERR_RIF_EOM_MONTH_END;            
   extern const long ERR_RIF_NO_PAYMENT_MONTH_END;     
   extern const long ERR_RIF_FUTURE_EFFECTIVE_DATE;   
   extern const long ERR_RIF_EOM_EFFECTIVE_DATE;      
   extern const long ERR_RIF_TOO_BIG_MAX_AMT_YR;       
   extern const long ERR_RIF_WRONG_RATE;               
   extern const long ERR_RIF_SPOUSE_OLDER_BIRTHDATE;   
   extern const long ERR_RIF_NOT_MIN_AMOUNT;
   extern const long ERR_RIF_BAD_RECORD;
   extern const long ERR_INVALID_CHAR;
   extern const long ERR_RIF_DIFF_CALC_VALUE;
   extern const long ERR_LESS_THAN_XII_MONTH;
   extern const long ERR_RRIF_LIF_RATE_PUID;
   extern const long ERR_INSTCODE_NOT_EXIST;
   extern const long ERR_TRANSITNO_NOT_EXIST;
   extern const long ERR_INSTCODE_TRANSITNO_NOT_EXIST;
   extern const long ERR_AMOUNT_GREAT_THAN_MAX;
   extern const long ERR_PAYMENT_BELOW_MIN;
   extern const long ERR_NET_AMOUNT_LESS_THEN_ZERO;
   extern const long ERR_RIF_SPOUSE_OLDER_THAN_SHAREHOLDER;
   extern const long WARN_RIF_SPOUSE_OLDER_THAN_SHAREHOLDER;
   extern const long ERR_TaxOnMin_SuppFedTax_SuppProvTax;
   extern const long ERR_WARN_RIF_SameMonthLastProcDateAsCurBusDate;
   extern const long ERR_RRIF_PayOptionMaximumNotAllowed;
   extern const long ERR_RRIFAmountCannotBeLessEqualZero;
   extern const long ERR_RIF_NO_SHAREHOLDER_BIRTHDATE;
   extern const long ERR_RIF_WARN_NO_SHAREHOLDER_BIRTHDATE;
   extern const long ERR_TO_ACCOUNT_CANNOT_BE_SAME_AS_FROM_ACCOUNT;
   extern const long ERR_PRE_YR_PERCENT;
   extern const long ERR_PRE_PERCENT_IN_BETWEEN;
   extern const long ERR_TRANSFER_TO_ACCOUNT_IS_NOT_ALLOWED;
   extern const long ERR_TRANSFER_TAX_TYPE;
   extern const long ERR_RRIF_ONE_MONTH_INDICATE_MISSING2;
   extern const long ERR_RRIF_ONE_MONTH_INDICATE_MISSING;
   extern const long ERR_RIF_MAX_AMOUNT_LESS_THAN_UNUSED_AMOUNT; 
   extern const long ERR_RIF_UNUSED_AMT_CANNOT_BE_NEGATIVE;
   extern const long ERR_EXACTLY_TWO_RIFF_DAYS_OF_MONTH_REQUIRED;
   extern const long ERR_DAYS_OF_MONTH_INVALID;
   extern const long ERR_RIF_FED_RATE_LESS_THAN_DEFAULT;
   extern const long ERR_RIF_PROV_RATE_LESS_THAN_DEFAULT;
   extern const long ERR_RIF_INVALID_GROSS_NET_METHOD_AFTER_NETOFFEES_DATE;
   extern const long ERR_RIF_INVALID_GROSS_NET_METHOD_BEFORE_NETOFFEES_DATE;
   extern const long ERR_CANNOT_CHANGE_CURRENT_YEAR;
   extern const long ERR_FEDERAL_QUALIFIED_NOT_ALLOWED;
   extern const long WARN_RIF_PROV_RATE_LESS_THAN_DEFAULT;
   extern const long WARN_RIF_FED_RATE_LESS_THAN_DEFAULT;
   extern const long WARN_ORIG_PLAN_DEFF_WILL_BE_CHANGED;
   extern const long ERR_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND;//P0186486_FN15_The Source of Funds
   extern const long WARN_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND;
   extern const long ERR_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE; 
   extern const long WARN_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE; 
   extern const long ERR_AMT_TYPE_NOTAPPLICABLE;
   extern const long ERR_RRIF_CANNOT_BESETUP;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId MonthIndicator;
   extern CLASS_IMPORT const BFTextFieldId RRIFcrossEffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId RRIFcrossStopDate;
   extern CLASS_IMPORT const BFTextFieldId RRIFcrossEndOfMonth;
   extern CLASS_IMPORT const BFTextFieldId RRIFcrossFedRate;
   extern CLASS_IMPORT const BFTextFieldId RRIFcrossProvRate;
   extern CLASS_IMPORT const BFTextFieldId RRIFcrossRate;
   extern CLASS_IMPORT const BFTextFieldId RRIFcrossIndexRate;
   extern CLASS_IMPORT const BFTextFieldId RRIFcrossGrossNetMethod;
   extern CLASS_IMPORT const BFTextFieldId RRIFcrossAddrCode;
   extern CLASS_IMPORT const BFTextFieldId CrossInstTransit;
   extern CLASS_IMPORT const BFTextFieldId SettleCross1;
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFTextFieldId isRRIFOverrUnusedAmtApplic;
   extern CLASS_IMPORT const BFTextFieldId XEditUnusedMaxAmt;
   extern CLASS_IMPORT const BFTextFieldId GrossNetMethod2;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeSchedule;
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_IA; //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_IA_RIF; 
   extern CLASS_IMPORT const BFTextFieldId NetOfFeesFlag;
   extern CLASS_IMPORT const BFTextFieldId SrcOfFundSrcOfAcctXEdit;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
}

namespace RRIF_GROUP
{

   const long RRIF_INFO = 0x0001;
   const long RRIF_ALLOCATION = 0x0002;

}

extern BF_OBJ_TYPE OBJ_TYPE_RRIF_UNUSED_MAX_AMOUNT;

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_FIELD_INFO;
}

namespace ACCOUNTINFOLITERALS
{
   const I_CHAR * const ACCOUNT_NUM        = I_( "AccountNum" );
   const I_CHAR * const SHAREHOLDER_NUMBER = I_( "ShrNum" );
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const RIF_PROV_RATE_LESS_THAN_DEFAULT;
   extern CLASS_IMPORT I_CHAR * const RIF_FED_RATE_LESS_THAN_DEFAULT;
   extern CLASS_IMPORT I_CHAR * const REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND; //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT I_CHAR * const SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE; 
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//    Field DD Id,            State Flags,   Group Flags 
   { ifds::RunMode,                BFCBO::NONE,                 0 },                           
   { ifds::PlanType,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::RecType,                BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::RecTypeDesc,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::SuppFedTax,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::SuppProvTax,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::FedRate,                BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::FedRatePUD,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::ProvRate,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::ProvRatePUD,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::RRIFAmount,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::PensionJuris,           BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::GrossNetMethod,         BFCBO::REQUIRED,				RRIF_GROUP::RRIF_INFO },       
   { ifds::NetAmt,                 BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::NowPlanValue,           BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::PYEPlanValue,           BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::CalcMandYr,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::CalcMaxYr,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::MandAmtPay,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::MandAmtYr,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::RIFPayType,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::PayOption,              BFCBO::REQUIRED,             RRIF_GROUP::RRIF_INFO },       
   { ifds::PayOptionDesc,          BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::MaxAmtYr,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::TaxOnMin,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::OverrideAmtYr,          BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::RIFSrcOfFund,           BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::RIFSrcOfFundDesc,       BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::January,                BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::February,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::March,                  BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::April,                  BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::May,                    BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::June,                   BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::July,                   BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::August,                 BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::September,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::October,                BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::November,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::December,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::EndOfMonth,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::LastProcessDate,        BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::AddrCode,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::GoodBad,                BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::EffectiveFrom,          BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::ModDate,                BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::StopDate,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::AddrLine1,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::AddrLine2,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::AddrLine3,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::AddrLine4,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::AddrLine5,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::PostalCode,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::IndexRate,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::Qualified,              BFCBO::REQUIRED,             RRIF_GROUP::RRIF_INFO },       
   { ifds::Username,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::BatchEffective,         BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::BatchName,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::BatchTrace,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::RRIFBatchTrace,         BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::rxBatchName,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::SpouseBirth,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::PayTerm,                BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::PayTermDesc,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::Factor,                 BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::CansimRate,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::ModUser,                BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::ProcessDate,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::MinWithAge,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::Frequency,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::CalcFedProvTax,         BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::MonthIndicator,         BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::SetAsDefault,           BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::SetRTAsDefault,         BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::DayOfWeek,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::DaysOfMonth,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },

   { ifds::AccountNum,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::ShrNum,                 BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },

   { ifds::AccountTo,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::PreYrPercent,           BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::RefTempInc,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },       
   { ifds::AdjLifeInc,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO }, 
   { ifds::ExternalAssets,         BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },//P0186486_FN03 - RRIF Annuities      
   
   { ifds::RRIFcrossEffectiveDate, BFCBO::NONE,                 0 },
   { ifds::RRIFcrossStopDate,      BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::RRIFcrossEndOfMonth,    BFCBO::NONE,                 0 },
   { ifds::RRIFcrossProvRate,      BFCBO::NONE,                 0 },
   { ifds::RRIFcrossFedRate,       BFCBO::NONE,                 0 },
   { ifds::RRIFcrossRate,          BFCBO::NONE,                 0 },
   { ifds::RRIFcrossIndexRate,     BFCBO::NONE,                 0 },
   { ifds::RRIFcrossGrossNetMethod,BFCBO::NONE,                 0 },
   { ifds::RRIFcrossAddrCode,      BFCBO::NONE,                 0 },
   { ifds::CrossInstTransit,       BFCBO::NONE,                 0 },
   { ifds::SettleCross1,           BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::CompoundDate,           BFCBO::NONE,                 0 },

   { ifds::AmountType,             BFCBO::NONE,                 0 },
   //banking fields 
   { ifds::InstCode,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::InstName,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::TransitNo,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::BankAcctNum,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::BankType,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::BankContact,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::CountryCode,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::PostalCode,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::BankAddr1,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::BankAddr2,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::BankAddr3,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::BankAddr4,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::BankAddr5,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::BankIdNum,              BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::InstName,               BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::OverrideUnusedMax,      BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::PYUnusedMax,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::RIFId,                  BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO }, 
   { ifds::VersionNum,             BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::Allocations,            BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO }, 
   { ifds::ToAllocations,          BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::XEditUnusedMaxAmt,      BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },  	
   { ifds::OrigPlanDeff,           BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },  	   
   { ifds::OrigPlanDeffApplied,    BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO }, 
   { ifds::RRIFSrcOfFund,          BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::RRIFSrcOfAcct,          BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::SrcOfFundSrcOfAcctXEdit,BFCBO::NONE,                 RRIF_GROUP::RRIF_INFO },
   { ifds::SrcOfFunds_IA,          BFCBO::NONE,                 0}, //P0186486_FN15_The Source of Funds
    	   
};


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "RRIF_LIF_LRIF_AllocList" ),           BFCBO::NONE, 0},
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************

static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
RRIF_LIF_LRIF_Info::RRIF_LIF_LRIF_Info( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),GetFromToFundAllocListInterFace(),
_pAccount( NULL ), 
_pShareholder( NULL ),
_effectiveDateYear (0),
_bInitExisting(false),
_bIsUserEnteredValidOrigPlanDeff(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO*)&classFieldInfo,
                       NUM_OBJECTS,(const CLASS_OBJECT_INFO*)& classObjectInfo );


   addCrossEdit(ifds::RRIFcrossEffectiveDate,  ifds::EffectiveFrom);               //DBR::EffectiveDate);
   addCrossEdit(ifds::RRIFcrossEffectiveDate,  ifds::EndOfMonth);

   addCrossEdit(ifds::RRIFcrossStopDate,       ifds::StopDate);
   addCrossEdit(ifds::RRIFcrossStopDate,       ifds::EffectiveFrom);

   addCrossEdit(ifds::RRIFcrossEndOfMonth,     ifds::EndOfMonth);
   addCrossEdit(ifds::RRIFcrossEndOfMonth,     ifds::LastProcessDate);

   addCrossEdit(ifds::RRIFcrossFedRate,        ifds::FedRate);
   addCrossEdit(ifds::RRIFcrossFedRate,        ifds::FedRatePUD);
   addCrossEdit(ifds::RRIFcrossFedRate,        ifds::SuppFedTax);

   addCrossEdit(ifds::RRIFcrossProvRate,       ifds::ProvRate);
   addCrossEdit(ifds::RRIFcrossProvRate,       ifds::ProvRatePUD);
   addCrossEdit(ifds::RRIFcrossProvRate,       ifds::SuppProvTax);

   addCrossEdit(ifds::RRIFcrossRate,           ifds::FedRate);
   addCrossEdit(ifds::RRIFcrossRate,           ifds::ProvRate);
   addCrossEdit(ifds::RRIFcrossRate,           ifds::FedRatePUD);
   addCrossEdit(ifds::RRIFcrossRate,           ifds::ProvRatePUD);
   addCrossEdit(ifds::RRIFcrossRate,           ifds::GrossNetMethod);

   addCrossEdit(ifds::RRIFcrossIndexRate,      ifds::IndexRate);
   addCrossEdit(ifds::RRIFcrossIndexRate,      ifds::PayOption);

   addCrossEdit(ifds::RRIFcrossGrossNetMethod, ifds::GrossNetMethod);
   addCrossEdit(ifds::RRIFcrossGrossNetMethod, ifds::PayOption);

   addCrossEdit(ifds::RRIFcrossAddrCode,       ifds::AddrCode);
   addCrossEdit(ifds::RRIFcrossAddrCode,       ifds::RIFPayType);

   addCrossEdit(ifds::CrossInstTransit,        ifds::InstCode);
   addCrossEdit(ifds::CrossInstTransit,        ifds::TransitNo);

   addCrossEdit(ifds::SettleCross1,            ifds::TaxOnMin);
   addCrossEdit(ifds::SettleCross1,            ifds::SuppFedTax);
   addCrossEdit(ifds::SettleCross1,            ifds::SuppProvTax);

   addCrossEdit(ifds::CompoundDate,            ifds::StopDate);
   addCrossEdit(ifds::CompoundDate,            ifds::EffectiveFrom);
   addCrossEdit(ifds::CompoundDate,            ifds::MonthIndicator);

   addCrossEdit(ifds::XEditUnusedMaxAmt,       ifds::MaxAmtYr );
   addCrossEdit(ifds::XEditUnusedMaxAmt,       ifds::PYUnusedMax);	
  
   addCrossEdit(ifds::SrcOfFundSrcOfAcctXEdit, ifds::RRIFSrcOfAcct);
   addCrossEdit(ifds::SrcOfFundSrcOfAcctXEdit, ifds::RRIFSrcOfFund);

   setAddCopy(); 
}
//******************************************************************************
RRIF_LIF_LRIF_Info::~RRIF_LIF_LRIF_Info()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//this fuction is called in docreatobject
SEVERITY RRIF_LIF_LRIF_Info::init( const BFData &data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString dstrRIFId = data.getElementValue( RIF_ID_FIELD );
   dstrRIFId.strip();

   attachDataObject( const_cast< BFData & >( data ), false, true );

   //_pRRIF_LIF_LRIF_AllocList = new RRIF_LIF_LRIF_AllocList( this );
   //_pRRIF_LIF_LRIF_AllocList->init( dstrRIFId, *pDataRRIF_LIF_LRIF_Alloc);

   //setObject( _pRRIF_LIF_LRIF_AllocList, I_( "RRIF_LIF_LRIF_AllocList" ), OBJ_ACTIVITY_NONE, BF::HOST );

   commonInit( BF::HOST );

   setFieldsAsReadOnly(BF::HOST);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// this method is called in doCreateNewObject() main
//
SEVERITY RRIF_LIF_LRIF_Info::init( const BFDataGroupId& idDataGroup )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   /*_pRRIF_LIF_LRIF_AllocList = new RRIF_LIF_LRIF_AllocList( this );
   _pRRIF_LIF_LRIF_AllocList->init( idDataGroup );
   _pRRIF_LIF_LRIF_AllocList->initWithDefaultAllocations( idDataGroup );*/

   //setObject( _pRRIF_LIF_LRIF_AllocList, I_( "RRIF_LIF_LRIF_AllocList" ), OBJ_ACTIVITY_NONE, BF::HOST );
   setObjectNew( ); 

   commonInit( idDataGroup );
   setField(ifds::GoodBad,I_("Y"),idDataGroup);

   setBatchParam(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
void RRIF_LIF_LRIF_Info::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
    SEVERITY         sevRtn         = NO_CONDITION;
    MFAccount      * pAccount       = NULL;
    DString          strValue       = NULL_STRING;
    DString          strShrNum      = NULL_STRING;

    if( isAddCopy() ) return; // if during  AddCopy, we do not need to set default value. 
	
	setFieldNoValidate( ifds::Qualified,      NO,      idDataGroup );

    getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, strValue, idDataGroup ,false );
    setFieldNoValidate( ifds::EffectiveFrom, strValue, idDataGroup, false ); //this should be called EffectiveDate

    //Set StopDate to 31 December, year of CurrBusDate. 

    // look in the registry for the date format mask
    // the current date should be in host format
    DString dstrConfiguration( I_( "HostMasks" ) );
    DString dstrKey( I_("D") );
    DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );

    int field_pos = mask.find( I_("dd") ); 
    strValue.replace( field_pos, 2, I_("31") ); //set the day

    field_pos = mask.find( I_("MM") ); 
    strValue.replace( field_pos, 2, I_("12") ); //set the month

    setFieldNoValidate( ifds::StopDate, strValue, idDataGroup, false );

    setFieldNoValidate( ifds::RIFSrcOfFund,   I_("I"), idDataGroup );
    setFieldNoValidate( ifds::TaxOnMin,       NO,      idDataGroup );
    setFieldNoValidate( ifds::SuppFedTax,     NO,      idDataGroup );
    setFieldNoValidate( ifds::SuppProvTax,    NO,      idDataGroup );
    setFieldNoValidate( ifds::OverrideAmtYr,  NO,      idDataGroup );
    setFieldNoValidate( ifds::January,        YES,     idDataGroup );
    setFieldNoValidate( ifds::February,       YES,     idDataGroup );
    setFieldNoValidate( ifds::March,          YES,     idDataGroup );
    setFieldNoValidate( ifds::April,          YES,     idDataGroup );
    setFieldNoValidate( ifds::May,            YES,     idDataGroup );
    setFieldNoValidate( ifds::June,           YES,     idDataGroup );
    setFieldNoValidate( ifds::July,           YES,     idDataGroup );
    setFieldNoValidate( ifds::August,         YES,     idDataGroup );
    setFieldNoValidate( ifds::September,      YES,     idDataGroup );
    setFieldNoValidate( ifds::October,        YES,     idDataGroup );
    setFieldNoValidate( ifds::November,       YES,     idDataGroup );
    setFieldNoValidate( ifds::December,       YES,     idDataGroup );
    // setFieldNoValidate( DBR::RRIFAmount,   ZERO,    idDataGroup );
    setFieldNoValidate( ifds::NetAmt,         ZERO,    idDataGroup );
    setFieldNoValidate( ifds::FedRate,        ZERO,    idDataGroup );
    setFieldNoValidate( ifds::ProvRate,       ZERO,    idDataGroup );
    setFieldNoValidate( ifds::RefTempInc,     ZERO,    idDataGroup );
    setFieldNoValidate( ifds::AdjLifeInc,     ZERO,    idDataGroup );
    setFieldNoValidate( ifds::FedRatePUD,     PERCENT, idDataGroup );
    setFieldNoValidate( ifds::ProvRatePUD,    PERCENT, idDataGroup );
    //setFieldNoValidate( ifds::Qualified,      NO,      idDataGroup );
    setFieldNoValidate( ifds::SpouseBirth,    I_(" "), idDataGroup );
    setFieldNoValidate( ifds::PayOption,      PAY_OPTION_MINIMUM, idDataGroup );
    setFieldNoValidate( ifds::IndexRate,      ZERO,    idDataGroup );   
	setFieldNoValidate( ifds::OverrideUnusedMax, NO,    idDataGroup, true, true, true, false );
    setFieldNoValidate( ifds::EndOfMonth,     NO,      idDataGroup );
    setFieldNoValidate( ifds::DayOfWeek,      I_("1"), idDataGroup, false );
    setFieldNoValidate( ifds::DaysOfMonth,    I_("15,31"), idDataGroup );


/*
    DString dstrtaxType;
    _pAccount->getField( DBR::TaxType, dstrtaxType, idDataGroup );

    if( dstrtaxType == I_( "B" ) || dstrtaxType == I_( "L" ) )
    {
        setFieldNoValidate( DBR::Qualified, NULL_STRING, idDataGroup, false, true, true );
    }
    else
    {
        setFieldNoValidate( DBR::Qualified, NO, idDataGroup, false, true, true );
    }
*/
    // setFieldNoValidate( DBR::InstCode, ZERO, idDataGroup );
    // setFieldNoValidate( DBR::TransitNo, ZERO, idDataGroup );
    // setFieldNoValidate( DBR::BankAcctNum, I_(" "), idDataGroup );
    setFieldNoValidate( ifds::RIFPayType, I_("S"), idDataGroup );
    setFieldNoValidate( ifds::Frequency, FREQ_MONTHLY, idDataGroup );

    setFieldNoValidate( ifds::AddrCode, I_("01"), idDataGroup );

    _pAccount->getField(ifds::MinWithAge, strValue, idDataGroup);
    setFieldNoValidate( ifds::MinWithAge, strValue, idDataGroup );

    _pAccount->getField(ifds::PensionJuris, strValue, idDataGroup);
    setFieldNoValidate( ifds::PensionJuris, strValue, idDataGroup );

    setMonthIndicator( idDataGroup );
    RRIF_LIF_LRIF_PaymentsCalculation *pPaymentsCalc;
    getPaymentsCalculationForDefaultValues(pPaymentsCalc, idDataGroup, isNew()? I_("1"):I_("2") );    
    setFieldsAsReadOnly(idDataGroup);
    //if( _pRRIF_LIF_LRIF_AllocList )
    //_pRRIF_LIF_LRIF_AllocList->clearUpdatedFlags( idDataGroup, true );      

	setFieldReadOnly( ifds::OverrideUnusedMax, 
			              idDataGroup, 
			              isOverrideUnusedAmtReadOnly( idDataGroup ) );	
	setFieldReadOnly( ifds::PYUnusedMax, idDataGroup, true );	
	
   populatedOrigPlanDeffApplied(idDataGroup);
  	setGrossNetMethod(idDataGroup, true);
  	
  	//P0186486_FN15_The Source of Funds
  	loadBusinessTypeSubslist(idDataGroup);
}

//**********************************************************************************
//
/*   {  DBR::InstCode,          BFBase::NONE,  0},
   {  DBR::InstName,          BFBase::NONE,  0},
   {  DBR::TransitNo,         BFBase::NONE,  0},
  // {  DBR::EffectiveDate,     BFBase::NONE,  0},
   {  DBR::BankAcctNum,       BFBase::NONE,  0},
*/
//************************************************************************
bool RRIF_LIF_LRIF_Info::isEFT(const BFDataGroupId& idDataGroup)
{
   DString dstrPayType;
   getField(ifds::RIFPayType,dstrPayType,idDataGroup,false);
   if( dstrPayType.strip() == I_("E") ) return(true);
   return(false); 
}


//***************************************************************************
//bank related validation added by yingbao
SEVERITY RRIF_LIF_LRIF_Info::ValidateInstCode(const DString& InstCode,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateInstCode" ) );
   DString str=InstCode;
   str.strip().strip('0');
   if( isEFT(idDataGroup) )
   {
      if( str == NULL_STRING )
      {
         ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//***********************************************************************************
//yingbao
bool RRIF_LIF_LRIF_Info::HaveToCheckBankPara(const BFDataGroupId& idDataGroup )
{
   DString strRRIFValidation;

   getWorkSession().getMgmtCoOptions()->getField(ifds::RRIFValidation,strRRIFValidation,idDataGroup,false);
   if( strRRIFValidation.strip() == I_("Y") )
      return(true);

   return(false);

}

//***********************************************************************************
//yingbao
SEVERITY RRIF_LIF_LRIF_Info::ValidateTransNo(const DString& TransNo,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateTransNo" ) );
   DString tmp=TransNo;
   DString FieldName;

   tmp.strip().strip('0');
   if( isEFT(idDataGroup) )
   {
      if( tmp == NULL_STRING )
      {
         ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   SEVERITY  sevRtn            = NO_CONDITION;
   DString   strValue          = NULL_STRING;
   DString   strGrossNetMethod = NULL_STRING;

   if( idField == ifds::RRIFAmount )
   {
      setAllocField(idField, ifds::Amount, idDataGroup);
   }
   else if( idField == ifds::RIFPayType )
   {
      getField( idField , strValue, idDataGroup );
      if( strValue == I_("S") )
         setFieldRequired( ifds::AddrCode, idDataGroup,true );
      else
         setFieldRequired( ifds::AddrCode, idDataGroup,false );
		if( strValue == I_("T") )
		{
			setValidFlag( ifds::AccountTo, idDataGroup, false );
		 // force to validate account to
		}
		else {
			setFieldNoValidate(ifds::AccountTo,I_("0"),idDataGroup ); // clear AccountTo.
		}

      if( strValue == I_("E") ) //then make the fields updateable
      {

         setFieldValid( ifds::InstCode, idDataGroup, false );
         setFieldRequired( ifds::InstCode, idDataGroup, true );

         setFieldRequired( ifds::TransitNo, idDataGroup, true );
         setFieldValid( ifds::TransitNo, idDataGroup, false );

         setFieldRequired( ifds::BankAcctNum, idDataGroup, true );
         setFieldValid( ifds::BankAcctNum, idDataGroup, false );

		 /*RRIFBankInstructionsList *pRRIFBankInstructionsList = NULL;
		 getBankInstructionsList(pRRIFBankInstructionsList, idDataGroup);*/
      }
      else
      {

         setFieldRequired( ifds::InstCode, idDataGroup, false );
         setFieldValid( ifds::InstCode, idDataGroup, true );

         setFieldRequired( ifds::TransitNo, idDataGroup, false );
         setFieldValid( ifds::TransitNo, idDataGroup, true );

         setFieldRequired( ifds::BankAcctNum, idDataGroup, false );
         setFieldValid( ifds::BankAcctNum, idDataGroup, true );
         //clear bank related fields
         BFCBO::setField( ifds::InstCode, NULL_STRING, idDataGroup);
         BFCBO::setField( ifds::TransitNo, NULL_STRING, idDataGroup );
         BFCBO::setField( ifds::BankAcctNum, NULL_STRING, idDataGroup );
         notifyObservers ( ifds::InstCode, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ));
         notifyObservers ( ifds::TransitNo, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ));
         notifyObservers ( ifds::BankAcctNum, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ));
      }
	  setGrossNetMethod(idDataGroup);
   }
   //yingbao finish
   else if( idField == ifds::GrossNetMethod )
   {
      setNetAmountReadOnly(true,idDataGroup); // add by yingbao
      setAmountReadOnly(true,idDataGroup);  //add by yingbao

   }
   else if( idField == ifds::PayOption )
   {
      setNetAmountReadOnly(true,idDataGroup); // add by yingbao
      setAmountReadOnly(true,idDataGroup);  //add by yingbao
      getField( idField , strValue, idDataGroup );
      if( strValue == PAY_OPTION_INDEX )
      {
         setFieldReadOnly( ifds::IndexRate, idDataGroup, false );
      }
      else
      {
         setFieldReadOnly( ifds::IndexRate, idDataGroup, true );
         setFieldNoValidate( ifds::IndexRate,I_("0"),idDataGroup,false,true,true);
      }

		// Set GrossNetMethod when Paytion is Min/Max
		setGrossNetMethod(idDataGroup);

      if(strValue != PAY_OPTION_PERCENT )  //clear PreYrPercent
      {		
          setFieldNoValidate( ifds::PreYrPercent,I_("0"),idDataGroup,false,true,true );		
      }


		DString dstrAcctNumber;

      getParent()->getParent()->getField(ifds::AccountNum, dstrAcctNumber, idDataGroup);
      dstrAcctNumber.stripLeading( '0' ).strip();
      MFAccount* pMFAccount = NULL;

      if (!dstrAcctNumber.empty() && getWorkSession().getMFAccount(idDataGroup, dstrAcctNumber, pMFAccount) <= WARNING && 
             pMFAccount )
      { 
		   DString dstrGWLWAAvailOptions;
         pMFAccount->getField ( ifds::GWLWAAvailOptions, dstrGWLWAAvailOptions, idDataGroup, false );  
         dstrGWLWAAvailOptions.strip ();
         
         if (DSTCommonFunctions::codeInList (strValue, dstrGWLWAAvailOptions)) 
         {
            DString dstrNetOfFees;
            getNetOfFeesApplicable(dstrNetOfFees, idDataGroup);
            if(dstrNetOfFees == I_("Y"))
            {
            	setFieldNoValidate( ifds::GrossNetMethod, NET_OF_FEES, idDataGroup,false,true,true);
            }
         }
      }


/*  take out by yingbao
      if ( strValue == I_("I") || strValue == I_("F") )   
      {
         getField( DBR::GrossOrNet , strGrossOrNet, idDataGroup );
         if ( GROSS == strGrossOrNet )
         {
            setFieldReadOnly( DBR::RRIFAmount, idDataGroup, false );
            setFieldReadOnly( DBR::NetAmt, idDataGroup, true );
         } else //strGrossOrNet == NET
         {
            setFieldReadOnly( DBR::RRIFAmount, idDataGroup, true );
            setFieldReadOnly( DBR::NetAmt, idDataGroup, false );
         }
      }
   */
   }
   else if( idField == ifds::SuppFedTax )
   {
      getField( idField , strValue, idDataGroup );
      if( strValue == NO ) //  yingbao
      {
         setFieldReadOnly( ifds::FedRate, idDataGroup, false );  //updatable
         setFieldReadOnly( ifds::FedRatePUD, idDataGroup, false );
      }
      else
      {  //else add by yingbao  // set to readonly
         setFieldReadOnly( ifds::FedRate, idDataGroup, true );  //readonly
         setFieldReadOnly( ifds::FedRatePUD, idDataGroup, true );
         setFieldNoValidate(ifds::FedRate,I_("0.0"),idDataGroup,true,true,true);  // clear the field

      }
   }
   else if( idField == ifds::SuppProvTax )
   {
      getField( idField , strValue, idDataGroup );
      if( strValue == NO )  // same as above
      {
         setFieldReadOnly( ifds::ProvRate, idDataGroup, false );
         setFieldReadOnly( ifds::ProvRatePUD, idDataGroup, false );
         setFieldNoValidate(ifds::ProvRate,I_("0.0"),idDataGroup,true,true,true);  // clear the field
         setFieldNoValidate(ifds::ProvRatePUD, PERCENT, idDataGroup, true, true, true);  // clear the field

      }
      else
      {
         setFieldReadOnly( ifds::ProvRate, idDataGroup, true );
         setFieldReadOnly( ifds::ProvRatePUD, idDataGroup, true );
         setFieldNoValidate(ifds::ProvRate,I_("0.0"),idDataGroup,true,true,true);  // clear the field
         //setFieldNoValidate(DBR::ProvRatePUD, NULL_STRING, idDataGroup, true, true, true );
      }
   }

   else if( idField == ifds::ProvRate )
   {
      setFieldNoValidate( ifds::CalcFedProvTax, YES, idDataGroup );
   }
   else if( idField == ifds::ProvRatePUD )
   {
      setFieldNoValidate( ifds::CalcFedProvTax, YES, idDataGroup );
   }
   else if( idField == ifds::FedRate )
   {
      setFieldNoValidate( ifds::CalcFedProvTax, YES, idDataGroup );
   }
   else if( idField == ifds::FedRatePUD )
   {
      setFieldNoValidate( ifds::CalcFedProvTax, YES, idDataGroup );
   }
   else if( idField == ifds::TaxOnMin )
   {
      setFieldNoValidate( ifds::CalcFedProvTax, YES, idDataGroup );
      getField( ifds::TaxOnMin , strValue, idDataGroup,false );
      if( YES == strValue )
      {
         setFieldNoValidate( ifds::SuppProvTax, NO, idDataGroup );
         setFieldNoValidate( ifds::SuppFedTax, NO, idDataGroup );
      }
   }
   else if( idField == ifds::Frequency )
   {
      getField( ifds::Frequency, strValue, idDataGroup );
      if( strValue == FREQ_WEEKLY || strValue == FREQ_BIWEEKLY  ) 
      {
         setFieldNoValidate( ifds::DayOfWeek, I_("1"), idDataGroup, false, true, true );
		 setEOMandMonthIndicator( idDataGroup );
      }
      else if( strValue == FREQ_SEMIMONTHLY ) 
      {
         setFieldNoValidate( ifds::DaysOfMonth, I_("15,31"), idDataGroup, true, true, true );
		 setEOMandMonthIndicator( idDataGroup );
      }
      else  
      {
         setMonthlyIndicatorByDeffFreq( idDataGroup );
      }
   }


   else if( idField == ifds::AddrCode )  // if AddressCode  Changed we should go to address to obtain address lines
   {
      setAddressLine(idDataGroup);
   }

   else if( idField == ifds::OverrideAmtYr )
   {
      DString dstrOverrideAmtYr,strTaxType;
      getField ( ifds::OverrideAmtYr, dstrOverrideAmtYr, idDataGroup );
      _pAccount->getField(ifds::TaxType, strTaxType, idDataGroup);
      strTaxType.strip();
      DString dstrMaxApply;
      _pAccount->getField(ifds::MaxApplies,dstrMaxApply,idDataGroup,false);

      bool bUpdate = ( strTaxType == LRIF_TAX_TYPE || getWorkSession ().isLIFLike (strTaxType)) &&
                     dstrOverrideAmtYr == YES && dstrMaxApply.strip() == YES;
      setFieldReadOnly( ifds::MaxAmtYr, idDataGroup, !bUpdate );

      bUpdate = (strTaxType == LRIF_TAX_TYPE || strTaxType == RRIF_TAX_TYPE  ||
						strTaxType == PRIF_TAX_TYPE || getWorkSession ().isLIFLike (strTaxType)) && dstrOverrideAmtYr == YES; 
      setFieldReadOnly( ifds::MandAmtYr, idDataGroup, !bUpdate );
   }
   else if( idField == ifds::MonthIndicator )
   {
      setMonthsFrequencyByIndicator( idDataGroup );
   }
   else if( idField == ifds::EffectiveFrom || 
	   idField == ifds::StopDate || 
	   idField == ifds::ExternalAssets) //P0186486_FN03 - RRIF Annuities
   {
      if(idField == ifds::EffectiveFrom)
      {
         if( isEffectiveDateInCurrentYr( idDataGroup ) == 2 )
         { // future date
            setFieldNoValidate( ifds::PYEPlanValue, I_("0.0"), idDataGroup );
            setFieldNoValidate( ifds::CalcMaxYr,    I_("0"),   idDataGroup,true,true,true);
            setFieldNoValidate( ifds::MandAmtPay,   I_("0"),   idDataGroup,true,true,true);
            setFieldNoValidate( ifds::PayTerm,      I_("0"),   idDataGroup,true,true,true);
            setFieldNoValidate( ifds::Factor,       I_("0"),   idDataGroup,true,true,true);
            setFieldNoValidate( ifds::CalcMandYr,   I_("0"),   idDataGroup,true,true,true);
            setFieldNoValidate( ifds::MandAmtYr,    I_("0"),   idDataGroup,true,true,true);
            setFieldNoValidate( ifds::MaxAmtYr,     I_("0"),   idDataGroup,true,true,true);
            setFieldNoValidate( ifds::NowPlanValue, I_("0"),   idDataGroup,true,true,true);

            setMonthlyIndicatorByDeffFreq( idDataGroup );
         }
         setAllocField(idField, ifds::EffectiveDate, idDataGroup);	
         //Set GrossNetMethod when EffectiveDate is changed
         setGrossNetMethod( idDataGroup );
      }	        
      
      populatedOrigPlanDeffApplied(idDataGroup);

      //if( isOrigPlanDeffApplied( idDataGroup ) )
      //{
      //   // refresh OrigPlanDeff field
      //   DString dstrOrigPlanDeff;
      //   _pAccount->getField( ifds::OrigPlanDeff, dstrOrigPlanDeff, idDataGroup, false);
   
      //   if(dstrOrigPlanDeff != NULL_STRING)
      //      setFieldNoValidate( ifds::OrigPlanDeff, dstrOrigPlanDeff, idDataGroup, false, false, true );
      //   else
      //   {
      //      DString dstrEffectiveDate;
      //      getField( ifds::EffectiveFrom, dstrEffectiveDate, idDataGroup, false );
      //      setFieldNoValidate( ifds::OrigPlanDeff, dstrEffectiveDate, idDataGroup, false, false, true );
      //   }
      //}
   }
   else if ( ifds::OverrideUnusedMax == idField )
   {
	   bool bUnusedMaxReadOnly = true;
	   DString dstrOverrideUnusedMax;
	   getField( ifds::OverrideUnusedMax, dstrOverrideUnusedMax, idDataGroup );
	   if ( I_( "Y" ) == dstrOverrideUnusedMax &&
		    !isOverrideUnusedAmtReadOnly( idDataGroup ) )
	   {
		   bUnusedMaxReadOnly = false;
	   }
	   else
	   {		
		 // Unused Max & Max Annual Amt should be populated with the value returned by the view
		 RRIF_LIF_LRIF_PaymentsCalculation *pPaymentsCalc;
         if( getPaymentsCalculation(pPaymentsCalc, idDataGroup ) <= WARNING && pPaymentsCalc )
		 {
				DString dstrUnusedAmount, dstrMaxAmount;
				pPaymentsCalc->getField( ifds::PYUnusedMaxSysCalc, dstrUnusedAmount, idDataGroup );
				//pPaymentsCalc->getField( ifds::MaxAmount,    dstrMaxAmount,    idDataGroup );
								
				setFieldNoValidate( ifds::PYUnusedMax, dstrUnusedAmount, idDataGroup, true, true, false, false );
				//setFieldNoValidate( ifds::MaxAmtYr,    dstrMaxAmount,    idDataGroup, true, true, false, false );								
		  }   
	   }

	   setFieldReadOnly( ifds::PYUnusedMax, idDataGroup, bUnusedMaxReadOnly );
   }
   else if ( ifds::PYUnusedMax == idField )
   {
	   /* I don't think that the following logic needs to be here
		// Max Annual Amt should be recalculated
	   DString dstrBefUnusedMax, dstrCurrUnusedMax, dstrMaxAnnualAmt, dstrOverrideAmtYr;
	   getFieldBeforeImage( ifds::PYUnusedMax, dstrBefUnusedMax );
	   getField( ifds::PYUnusedMax, dstrCurrUnusedMax, idDataGroup );
	   //getField( ifds::MaxAmtYr,    dstrMaxAnnualAmt,  idDataGroup );

		getField ( ifds::OverrideAmtYr, dstrOverrideAmtYr, idDataGroup );
		if ( dstrOverrideAmtYr == I_("Y") )
		{
			getField( ifds::MaxAmtYr, dstrMaxAnnualAmt, idDataGroup );
		}
		else
		{
			getFieldBeforeImage( ifds::MaxAmtYr,    dstrMaxAnnualAmt );
		}
	   
	   double dBefUnusedMax  = DSTCommonFunctions::convertToDouble( dstrBefUnusedMax );
	   double dCurrUnusedMax = DSTCommonFunctions::convertToDouble( dstrCurrUnusedMax );
	   double dMaxAnnualAmt  = DSTCommonFunctions::convertToDouble( dstrMaxAnnualAmt );

	   dMaxAnnualAmt = dMaxAnnualAmt - dBefUnusedMax + dCurrUnusedMax;

	   dstrMaxAnnualAmt = DSTCommonFunctions::doubleToDString (ifds::MaxAmtYr, dMaxAnnualAmt );

	   setFieldNoValidate(ifds::MaxAmtYr, dstrMaxAnnualAmt, idDataGroup,true,true,true,false);*/
   }

	else if ( idField == ifds::MaxAmtYr )
	{
		/* I don't think that the following logic needs to be here
		DString dstrOverrideAmtYr, dstrOverrideUnusedMax;
      getField ( ifds::OverrideAmtYr, dstrOverrideAmtYr, idDataGroup );
		getField ( ifds::OverrideUnusedMax, dstrOverrideUnusedMax, idDataGroup );
		
		if ( dstrOverrideAmtYr == I_("Y") && dstrOverrideUnusedMax == I_("Y") )
		{
			DString dstrBefUnusedMax, dstrCurrUnusedMax, dstrMaxAnnualAmt;
			getFieldBeforeImage( ifds::PYUnusedMax, dstrBefUnusedMax );
			getField( ifds::PYUnusedMax, dstrCurrUnusedMax, idDataGroup );
			getField( ifds::MaxAmtYr, dstrMaxAnnualAmt, idDataGroup );
			double dBefUnusedMax  = DSTCommonFunctions::convertToDouble( dstrBefUnusedMax );
			double dCurrUnusedMax = DSTCommonFunctions::convertToDouble( dstrCurrUnusedMax );
			double dMaxAnnualAmt  = DSTCommonFunctions::convertToDouble( dstrMaxAnnualAmt );

			dMaxAnnualAmt = dMaxAnnualAmt - dBefUnusedMax + dCurrUnusedMax;

			dstrMaxAnnualAmt = DSTCommonFunctions::doubleToDString (ifds::MaxAmtYr, dMaxAnnualAmt );

			setFieldNoValidate(ifds::MaxAmtYr, dstrMaxAnnualAmt, idDataGroup,false,true,true,false);
		}*/
	}
	else if ( idField  == ifds::DaysOfMonth )
	{
		//make sure that the dates do not start with a zero (e.g. 1,15 - instead of 01,15)
		DString strDays;
		getField(ifds::DaysOfMonth, strDays, idDataGroup);
		if( strDays.strip()[0] == '0' )
		{
			strDays.stripLeading( '0' );
			setFieldNoValidate( ifds::DaysOfMonth, strDays, idDataGroup, true, true, true );
		}
	}	
   else if ( idField  == ifds::OrigPlanDeffApplied )
   {
      DString strOrigPlanDeffApplied;

      getField( idField, strOrigPlanDeffApplied, idDataGroup, false );

      if( strOrigPlanDeffApplied == I_("Y") && 
          getWorkSession().hasUpdatePermission (UAF::RIF_LIF_LRIF_FIELD_INFO) )
      {
         // refresh OrigPlanDeff field
         DString dstrOrigPlanDeff;
         _pAccount->getField( ifds::OrigPlanDeff, dstrOrigPlanDeff, idDataGroup, false);

         if(dstrOrigPlanDeff != NULL_STRING)
            setFieldNoValidate( ifds::OrigPlanDeff, dstrOrigPlanDeff, idDataGroup, false, false, true );
         else
         {
            DString dstrEffectiveDate;
            getField( ifds::EffectiveFrom, dstrEffectiveDate, idDataGroup, false );
            // set OrigPlanDeff, not trig related change.
            setFieldNoValidate( ifds::OrigPlanDeff, dstrEffectiveDate, idDataGroup, false, false, true, false );       
         }
         // it's not user entered, it is system calculation.
         _bIsUserEnteredValidOrigPlanDeff = false;
      }
   }
   else if ( idField  == ifds::OrigPlanDeff )
   {
      DString dstrOrigPlanDeff, strDate12319999;
      getField(idField, dstrOrigPlanDeff, idDataGroup, false);
      DSTCommonFunctions::getFormat12319999Date(strDate12319999);

      // 12319999 for OrigPlanDeff, it mean the value is invalid      
      if(DSTCommonFunctions::CompareDates( dstrOrigPlanDeff, strDate12319999 ) != DSTCommonFunctions::EQUAL)
      {
         // user enter the value and pass the validation         
         _bIsUserEnteredValidOrigPlanDeff = true;
      }     
   }
   else if( idField == ifds::RRIFSrcOfFund )
   {
      //P0186486_FN15_The Source of Funds
      sourceOfFundRelatedChanges( idDataGroup );
   }
   if( isNew() )  // force to do validation
   {
      setValidFlag( ifds::SpouseBirth, idDataGroup, false );
   }
   else
   {
      // This block for existing record
      if( !_bInitExisting &&
          getWorkSession().hasUpdatePermission (UAF::RIF_LIF_LRIF_FIELD_INFO) &&
          idField != ifds::BatchTrace && 
          idField != ifds::rxBatchName &&
          idField != ifds::BatchName &&
          idField != ifds::RRIFBatchTrace &&
          idField != ifds::BatchEffective &&
          idField != ifds::OrigPlanDeffApplied )
      {
         // replace original plan effective date if it is 12319999
         DString dstrOrigPlanDeff, strDate12319999;
         getField(ifds::OrigPlanDeff, dstrOrigPlanDeff, idDataGroup, false);
         DSTCommonFunctions::getFormat12319999Date(strDate12319999);

         if(DSTCommonFunctions::CompareDates( dstrOrigPlanDeff, strDate12319999 ) == DSTCommonFunctions::EQUAL)
         {
            populatedOrigPlanDeffApplied(idDataGroup);            
         }
      }     
      
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
// setAddressLine() implemented by yingbao
//

void  RRIF_LIF_LRIF_Info::setAddressLine(const BFDataGroupId& idDataGroup)
{
   const BFFieldId addrLine[]=
   {
      ifds::AddrLine1,
      ifds::AddrLine2,
      ifds::AddrLine3,
      ifds::AddrLine4,
      ifds::AddrLine5,  
   };
   AddressList *pAddressList = NULL;
   DString dstrAddrCode,dstrValue = NULL_STRING;
   getField(ifds::AddrCode,dstrAddrCode,idDataGroup,false);
   dstrAddrCode.strip();
   if( _pShareholder->getAddressList( pAddressList, idDataGroup ) <= WARNING )
   {
      Address* pAddress = NULL;

      if (pAddressList->getAddress (pAddress, dstrAddrCode, 
            NULL_STRING, idDataGroup) <= WARNING &&
         pAddress)
      {
         for( int i = 0;i<5;i++ )
         {
            pAddress->getField( addrLine[i],dstrValue,idDataGroup,false);
            setFieldNoValidate( addrLine[i], dstrValue, idDataGroup,false );
         }

      }
      else
      {  // clear AddrLine
         for( int i = 0;i<5;i++ )
         {
            setFieldNoValidate( addrLine[i], dstrValue, idDataGroup, false );
         }     
      }
      notifyObservers( addrLine[0], idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ) );
   }
}

//******************************************************************************

SEVERITY RRIF_LIF_LRIF_Info::getFromFundAllocList(
               FromFundAllocList *&pFromFundAllocList , const BFDataGroupId& idDataGroup, bool bCreate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFromFundAllocList" ) );

   pFromFundAllocList = NULL;


   pFromFundAllocList = dynamic_cast<FromFundAllocList*>(getObject( FROMFUNDALLOCLIST, idDataGroup ) );
   if( pFromFundAllocList || !bCreate )
      return(GETCURRENTHIGHESTSEVERITY());

   pFromFundAllocList = new FromFundAllocList( *this );
   DString strAllocExist;
   getField(ifds::Allocations, strAllocExist, idDataGroup, false);
   if( isNew() || strAllocExist.strip()!=YES )
   {
      pFromFundAllocList->initNew( idDataGroup, isNew() );
      setObject( pFromFundAllocList, FROMFUNDALLOCLIST, OBJ_ACTIVITY_NONE, idDataGroup );
   }
   else
   {
      if( pFromFundAllocList->initExisting() <= WARNING )
         setObject( pFromFundAllocList, FROMFUNDALLOCLIST, OBJ_ACTIVITY_NONE, BF::HOST );
      else
      {
         delete pFromFundAllocList;
         pFromFundAllocList = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::getToFundAllocList(
               ToFundAllocList *&pToFundAllocList , const BFDataGroupId& idDataGroup, bool bCreate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFromFundAllocList" ) );

   pToFundAllocList = NULL;
	
/*	DString dstrPayType;
	getField(ifds::RIFPayType,dstrPayType,idDataGroup );
	dstrPayType.strip();
	if( dstrPayType != I_("T") )
	{
		assert(0);  // should not be called
	
	} */
   pToFundAllocList = dynamic_cast<ToFundAllocList*>(getObject( TOFUNDALLOCLIST, idDataGroup ) );
   if( pToFundAllocList || !bCreate )
      return(GETCURRENTHIGHESTSEVERITY());


   DString strAllocExist;
   getField(ifds::ToAllocations, strAllocExist, idDataGroup, false);

  	pToFundAllocList = new ToFundAllocList( *this );

	if( isNew() || strAllocExist.strip()!=YES )
		{
			pToFundAllocList->initNew( idDataGroup, isNew() );
			setObject( pToFundAllocList, TOFUNDALLOCLIST, OBJ_ACTIVITY_NONE, idDataGroup );
		}
		else
		{
			if( pToFundAllocList->initExisting() <= WARNING )
				setObject( pToFundAllocList, TOFUNDALLOCLIST, OBJ_ACTIVITY_NONE, BF::HOST );
			else
			{
				delete pToFundAllocList;
				pToFundAllocList = NULL;
			}
		}
  
   return(GETCURRENTHIGHESTSEVERITY());
}
//*************************************************************************
//setBatchParam reimplemented by yingbao

//**************************************************************************
void  RRIF_LIF_LRIF_Info::setBatchParam(const BFDataGroupId& idDataGroup )
{
   DString strBatchTrace;
   DString strrxBatchName;
   DString strEffectiveDate;
   dynamic_cast<RRIF_LIF_LRIF_InfoList*>(getParent())->getBachParam(strBatchTrace,
                                                                    strrxBatchName,strEffectiveDate);   
   if( idDataGroup != BF::HOST )
   {
      int iBatchTrace = strBatchTrace.asInteger();
      ++iBatchTrace;
      strBatchTrace = DString::asString( iBatchTrace );

   }
   setFieldNoValidate( ifds::BatchTrace, strBatchTrace, idDataGroup );   
   setFieldNoValidate( ifds::rxBatchName, strrxBatchName, idDataGroup ); 
   if( isNew() )
   {
      setFieldNoValidate( ifds::BatchName, strrxBatchName, idDataGroup );
      setFieldNoValidate( ifds::RRIFBatchTrace, strBatchTrace, idDataGroup );
   }
   setFieldNoValidate( ifds::BatchEffective, strEffectiveDate, idDataGroup, false ); 

}

//******************************************************************************
//	doValidateAll  reimplemented by Yingbao
// yingbao


SEVERITY RRIF_LIF_LRIF_Info::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   if( isUpdatedForDataGroup( idDataGroup, true ) || isNew() )  
		// when allocation has been changed
		// we also need a active batch.
	{
		setBatchParam(BF::HOST);
		validateTransfer(idDataGroup);
		
		if(!isNew())
		{
   		   DString dstrOrigPlanDeffApplied;
           getField(ifds::OrigPlanDeffApplied, dstrOrigPlanDeffApplied, idDataGroup, false);
           dstrOrigPlanDeffApplied.strip().upperCase();
           if(dstrOrigPlanDeffApplied == I_("Y"))
           {
              DString dstrOrigPlanDeff, dstrDate;

              getField(ifds::OrigPlanDeff, dstrOrigPlanDeff, idDataGroup, false);
              DSTCommonFunctions::getFormat12319999Date(dstrDate);
              if (!_bIsUserEnteredValidOrigPlanDeff)
              {
                if ( ! (DSTCommonFunctions::CompareDates( dstrOrigPlanDeff, dstrDate ) == DSTCommonFunctions::EQUAL) )  
                {
                   ADDCONDITIONFROMFILE( CND::WARN_ORIG_PLAN_DEFF_WILL_BE_CHANGED );	 
                }
              }
		   }
		}
	}	
   if( isUpdatedForDataGroup( idDataGroup, false ) || isNew() )
   {
      if( GETCURRENTHIGHESTSEVERITY() <= WARNING )  // in case there is no active batch for modification
      {
         validateAgainst130(idDataGroup);
      }
   }

   validateSpouseDOB (idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( isAddCopy() )
      return(GETCURRENTHIGHESTSEVERITY());  // we do not do any validation if we are in addcopy

   if( idField == ifds::EffectiveFrom )  //Effective Date
   {
      int effectiveDateYear = extractFieldFromDate( strValue );

      DString strCurrBusDate;
      getWorkSession().getOption( ifds::CurrBusDate, strCurrBusDate, idDataGroup, false );
      int currBusDateYear = extractFieldFromDate( strCurrBusDate );

      DString strRRIFPrevYear( I_("") );
      getWorkSession().getOption( ifds::RRIFPrevYear, strRRIFPrevYear, idDataGroup,false );

      if( I_("N") == strRRIFPrevYear && effectiveDateYear < currBusDateYear )
      {
         DString strTaxType,strCurrBusDate;
         _pAccount->getField(ifds::TaxType, strTaxType, idDataGroup,true);
         // use format date for display
         getWorkSession().getOption( ifds::CurrBusDate, strCurrBusDate, idDataGroup, true );

         DString idiStr;
         addIDITagValue( idiStr, ACCOUNT_TYPE, strTaxType );
         addIDITagValue( idiStr, CURRENT_BUS_DATE, strCurrBusDate );
         ADDCONDITIONFROMFILEIDI( CND::ERR_RIF_PAST_EFFECTIVE_DATE, idiStr);   
      }

	  if (!isNew () && _effectiveDateYear != effectiveDateYear)
	  {
	 	   ADDCONDITIONFROMFILE( CND::ERR_CANNOT_CHANGE_CURRENT_YEAR );
	  }
	  else
	  {
		if( effectiveDateYear > currBusDateYear )
		{
			ADDCONDITIONFROMFILE( CND::ERR_RIF_FUTURE_EFFECTIVE_DATE );
		}
	  }
   }
   else if( idField == ifds::StopDate )
   {
   }
   else if( idField == ifds::RIFSrcOfFund )
   {
      if( !( RIF_SRCOFFOUND_VALUE1 == strValue || RIF_SRCOFFOUND_VALUE2 == strValue ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_RIF_INVALID_RIF_SRC_OF_FUND ); 
      }
   }
   else if( idField == ifds::MandAmtYr )
   {

      DString dstrMaxApply;
      _pAccount->getField(ifds::MaxApplies,dstrMaxApply,idDataGroup,false);
      if( dstrMaxApply.strip() ==  YES )
      {
         double mandAmtYr = DSTCommonFunctions::convertToDouble( strValue );
         DString strMaxAmtYr;
         getField(ifds::MaxAmtYr, strMaxAmtYr, idDataGroup);
         double maxAmtYr = DSTCommonFunctions::convertToDouble( strMaxAmtYr );

         if( maxAmtYr < mandAmtYr )
         {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_TOO_BIG_MAND_AMT_YR ); 
         }
      }
   }
   else if( idField == ifds::MaxAmtYr )
   {      
      if( isFieldReadOnly( ifds::MaxAmtYr, idDataGroup ) == false )
      {   
		 double maxAmtYr = DSTCommonFunctions::convertToDouble( strValue );
         DString strMandAmtYr;
         getField(ifds::MandAmtYr, strMandAmtYr, idDataGroup);
         int mandAmtYr = convertToULong( strMandAmtYr );
         RRIF_LIF_LRIF_PaymentsCalculation *pPaymentsCalc;
         if(isEffectiveDateInCurrentYr(idDataGroup) == 1 && 
            getPaymentsCalculation(pPaymentsCalc, idDataGroup ) <= WARNING && pPaymentsCalc )
		 {
			DString strAcctValue;
            pPaymentsCalc->getField(ifds::AcctValue, strAcctValue, idDataGroup);
            int acctValue = convertToULong( strAcctValue );

            if( maxAmtYr < mandAmtYr )
            {
               ADDCONDITIONFROMFILE( CND::ERR_RIF_TOO_SMALL_MAX_AMT_YR ); 
            }
            else if( maxAmtYr > acctValue )
            {
               ADDCONDITIONFROMFILE( CND::ERR_RIF_TOO_BIG_MAX_AMT_YR ); 
               // warning that maximum account is greater than current AccountValue
            }
         }
      }	  	  
   }
   else if( idField == ifds::PYUnusedMax )
   {
	  ///// if 211.CarryForUnusedMax = yes, then UnusedMax should be >= 0 
	  DString dstrUnusedMax;
	  getField( ifds::PYUnusedMax, dstrUnusedMax, idDataGroup );
	  double dUnusedMax  = DSTCommonFunctions::convertToDouble( dstrUnusedMax );	
	  DString dstrTaxType, dstrProvReg;
	  if ( dUnusedMax < 0 )
	  {			
         MFAccount *pAccount = dynamic_cast<MFAccount*> (getParent()->getParent());
		 if ( getWorkSession ().getMFAccount ( idDataGroup, 
											  _strAccountNum, 
											  pAccount ) <= WARNING && NULL != pAccount )
		 {
            pAccount->getField( ifds::PensionJuris, dstrProvReg, idDataGroup );				

				/*
				if ( dstrProvReg.stripAll().empty() )
				{	
					DString dstrShrNum;
					pAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup );

					Shareholder *pShareholder = NULL;
					getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder );
					if ( NULL != pShareholder )
						pShareholder->getField( ifds::TaxJurisCode, dstrProvReg, idDataGroup );
				}*/
		 }	

		TaxTypeRule *pTaxTypeRule = NULL;

		if ( pAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
		{
		   bool bCarryForwardUnusedMax = pTaxTypeRule->isCarryForwardUnusedMaxApplic( dstrProvReg, idDataGroup );
		   if ( bCarryForwardUnusedMax )
		   {
		      // Unused Max Amount cannot be negative
                 ADDCONDITIONFROMFILE( CND::ERR_RIF_UNUSED_AMT_CANNOT_BE_NEGATIVE );                
		   }
		}
	  }
   }
   else if ( idField == ifds::XEditUnusedMaxAmt	) 
   {
      if ( !isOverrideUnusedAmtReadOnly( idDataGroup ) )
	  {
			// MaxAmtYr should be greater than Unused Max
			DString dstrUnusedMax, dstrMaxAmtYr;
			getField( ifds::PYUnusedMax, dstrUnusedMax, idDataGroup );
			getField( ifds::MaxAmtYr,    dstrMaxAmtYr,  idDataGroup );
			double dUnusedMax  = DSTCommonFunctions::convertToDouble( dstrUnusedMax );	
			double dMaxAmtYr = DSTCommonFunctions::convertToDouble( dstrMaxAmtYr );
			if ( dMaxAmtYr < dUnusedMax )
			{
					// Max Annual Amount should be greater than Unused Amount
					ADDCONDITIONFROMFILE( CND::ERR_RIF_MAX_AMOUNT_LESS_THAN_UNUSED_AMOUNT ); 
			}
	  }
   }
   else if( idField == ifds::EndOfMonth )
   {
      //_strOldMonthEnd is populated in doPreSetField with the old value of DBR::MonthEnd.
      if( NO == strValue && YES == _strOldMonthEnd )
      {
         ADDCONDITIONFROMFILE( CND::ERR_RIF_NO_PAYMENT_MONTH_END ); 
      }
      else if( NO == _strOldMonthEnd && YES == strValue )
      {
         DString dstrLastProcessDate,dstrCurBusDate;
         getField(ifds::LastProcessDate,dstrLastProcessDate,idDataGroup,false);
         getWorkSession().getOption( ifds::CurrBusDate, dstrCurBusDate, idDataGroup, false );
         int iLastProcMonth = extractFieldFromDate( dstrLastProcessDate, I_("MM") );
         int iCurBusMonth = extractFieldFromDate( dstrCurBusDate, I_("MM") );
         if( iCurBusMonth == iLastProcMonth )
         {
            ADDCONDITIONFROMFILE( CND::ERR_WARN_RIF_SameMonthLastProcDateAsCurBusDate );        
         }
      }
   }
   else if( idField == ifds::MonthIndicator )
   {
      DString tmp;
	  DString::size_type index;

      // I am testing only up to strValue.length() because the missing months will be 
      // filled with the value of the last completed month.
      if( strValue.length() != 12 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_LESS_THAN_XII_MONTH );
         return(GETCURRENTHIGHESTSEVERITY());
      }

	  for( index = 0; index < strValue.length() ; ++index )
      {
         tmp = strValue.substr(index, 1);
         if( tmp != I_("Y")  && tmp != I_("N") )
         {
            ADDCONDITIONFROMFILE( CND::ERR_INVALID_CHAR );
         }
      }

      // I am testing only up to strValue.length() because the missing months will be 
      // filled with the value of the last completed month.
	  for( index = 0; index < strValue.length() ; index++ )
      {
         tmp = strValue.substr(index, 1); 
         if( tmp == I_("Y") )
         {
            break;
         }
      }
      if( index == strValue.length() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_RIF_MONTH );
      }
      else // Save month values into CBO.
      {
         const BFFieldId monthID[] = {ifds::January, ifds::February, ifds::March, ifds::April, ifds::May, ifds::June, 
            ifds::July, ifds::August, ifds::September, ifds::October, ifds::November,ifds::December};
         DString strMonthIndicator = strValue;

         // Now filling the last missing months, if any.
         int lastPosition = strMonthIndicator.length() - 1;
         DString strLastMonthCompleted = strMonthIndicator.substr( lastPosition, 1 ); // Getting the value of the last completed month.
         for( index = lastPosition + 1; index < 12; index ++ )
         {
            strMonthIndicator += strLastMonthCompleted;
         }

         for( index = 0; index < 12; index++ )
         {
            setFieldNoValidate( monthID[index], strMonthIndicator.substr( index, 1), idDataGroup );
         }
         setFieldNoValidate ( ifds::MonthIndicator, strMonthIndicator, idDataGroup, true, true, true); // Update and notify observers.
         //we have to notify control 
         notifyObservers( ifds::MonthIndicator, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_STATE_CHANGE, I_( "" ));


         setFieldNoValidate ( ifds::Frequency, FREQ_OTHER, idDataGroup, true, true, true); // Update and notify observers.
      }

   }
   else if( idField == ifds::RRIFAmount )
   {
      double amount = DSTCommonFunctions::convertToDouble( strValue );
      if( amount < 0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_RIF_NEGATIVE_AMOUNT );
      }
   }
   else if( idField == ifds::MandAmtPay )
   {
   }
   else if( idField == ifds::NetAmt )
   {
      double netAmount = DSTCommonFunctions::convertToDouble( strValue );

      if( netAmount < 0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_RIF_NEGATIVE_AMOUNT );
      }

   }
   else if( idField == ifds::FedRate )
   {


   }
   else if( idField == ifds::ProvRate )
   {



   }
   else if( idField == ifds::FedRatePUD )
   {
      if( strValue != PERCENT && strValue != DOLLAR )
      {
         ADDCONDITIONFROMFILE( CND::ERR_RIF_INVALID_RATE_PUD );
      }

   }
   else if( idField == ifds::ProvRatePUD )
   {
      if( strValue != PERCENT && strValue != DOLLAR )
      {
         ADDCONDITIONFROMFILE( CND::ERR_RIF_INVALID_RATE_PUD );
      }

   }
   else if( idField == ifds::Qualified )
   {
      DString strRRIFQualified( I_("") );
      _pAccount->getField(ifds::RRIFQualified, strRRIFQualified, idDataGroup);

      if( YES == strRRIFQualified && YES == strValue )
      {
         ADDCONDITIONFROMFILE( CND::ERR_RIF_QUALIFIED );
      }

	  DString strPensionJurisCode;

      _pAccount->getField(ifds::PensionJuris, strPensionJurisCode, idDataGroup);

	  if (YES == strValue && strPensionJurisCode == FEDERAL)
	  {
           ADDCONDITIONFROMFILE( CND::ERR_FEDERAL_QUALIFIED_NOT_ALLOWED );
	  }
   }
   else if( idField == ifds::SpouseBirth )
   {
      DString spouseBirthDate(strValue);
      spouseBirthDate.strip();

      if( NULL_STRING != spouseBirthDate )
      {
         DString strCurrentDate;
         getWorkSession().getOption( ifds::CurrSysDate, strCurrentDate, idDataGroup, false );
         if( DSTCommonFunctions::CompareDates( strCurrentDate, spouseBirthDate  ) 
                     == DSTCommonFunctions::FIRST_EARLIER )
         {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_FUTURE_BIRTHDATE ); 
         }
      }

      DString strTaxType;
      _pAccount->getField(ifds::TaxType, strTaxType, idDataGroup);

      DString strBirthDate;
      _pAccount->getDofBirthofOwnerSeq01( strBirthDate, idDataGroup );
      strBirthDate.strip();

      //spouse birthday must be entered if shareholder's birthday is unknown
      if( NULL_STRING == spouseBirthDate && NULL_STRING == strBirthDate &&  
          (getWorkSession ().isLIFLike (strTaxType) ||  strTaxType == RRIF_TAX_TYPE ||  strTaxType == PRIF_TAX_TYPE  ) )
      {
         getErrMsg( I_("336"), 
                    CND::ERR_RIF_NO_SHAREHOLDER_BIRTHDATE, 
                    CND::ERR_RIF_WARN_NO_SHAREHOLDER_BIRTHDATE, 
                    idDataGroup ); 
      }


      if( NULL_STRING != spouseBirthDate && NULL_STRING != strBirthDate )
      {
         if ( DSTCommonFunctions::CompareDates( spouseBirthDate, strBirthDate ) 
               == DSTCommonFunctions::FIRST_EARLIER ) 
         {
            DString strPensionJuris;
            _pAccount->getField( ifds::PensionJuris, strPensionJuris, idDataGroup );

            if( (getWorkSession ().isLIFLike (strTaxType) || strTaxType == LRIF_TAX_TYPE ) && 
                ( strPensionJuris == I_("0006") || strPensionJuris == I_("0008") ) )
            {
               getErrMsg( I_("971"), 
                          CND::ERR_RIF_SPOUSE_OLDER_THAN_SHAREHOLDER, 
                          CND::WARN_RIF_SPOUSE_OLDER_THAN_SHAREHOLDER, 
                          idDataGroup ); 
//               ADDCONDITIONFROMFILE( CND::ERR_RIF_SPOUSE_OLDER_THAN_SHAREHOLDER ); 
            }
         }
      }
   }
   else if( idField == ifds::PayOption )
   {
      DString strMaxApplies( I_("") );
      _pAccount->getField(ifds::MaxApplies, strMaxApplies, idDataGroup,false);

		MFAccount *pMFAccount = NULL;
		DString dstrAcctNumber;

      getParent()->getParent()->getField(ifds::AccountNum, dstrAcctNumber, idDataGroup);
      dstrAcctNumber.stripLeading( '0' ).strip();

      if (!dstrAcctNumber.empty() && getWorkSession().getMFAccount(idDataGroup, dstrAcctNumber, pMFAccount) <= WARNING && 
             pMFAccount )
      { 
			if (DSTCommonFunctions::codeInList (strValue, GWLWA_OPTIONS))
			{
				// validate GWA, LWA
		   	DString dstrGWLWAAvailOptions;

				pMFAccount->getField ( ifds::GWLWAAvailOptions, dstrGWLWAAvailOptions, idDataGroup, false );  
	
				dstrGWLWAAvailOptions.strip ();

				if (!DSTCommonFunctions::codeInList (strValue, dstrGWLWAAvailOptions))
				{
					ADDCONDITIONFROMFILE (CND::ERR_AMT_TYPE_NOTAPPLICABLE);
				}
				else
				{
					DString dstrSWPGLOpt;

					pMFAccount->getField ( ifds::SWPGLOpt, dstrSWPGLOpt, idDataGroup, false );  

					if (!dstrSWPGLOpt.empty ())
					{
						ADDCONDITIONFROMFILE (CND::ERR_RRIF_CANNOT_BESETUP);
					}
				}
			}
			else
			{   // old validation...
				if( strValue != PAY_OPTION_FIX   && strValue != PAY_OPTION_MINIMUM && 
					strValue != PAY_OPTION_INDEX && strValue != PAY_OPTION_MAXIMUM &&
					strValue != PAY_OPTION_PERCENT
				)
				{
					ADDCONDITIONFROMFILE( CND::ERR_RIF_INVALID_PAY_OPTION ); 
				}
			}
		}

        if( NO == strMaxApplies && strValue == PAY_OPTION_MAXIMUM )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_NO_MAXIMUM_PAY_OPTION ); 
        }
        DString dstrTaxType;
        _pAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup,false);
        if( ( dstrTaxType == RRIF_TAX_TYPE || dstrTaxType == PRIF_TAX_TYPE ) && strValue == PAY_OPTION_MAXIMUM )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RRIF_PayOptionMaximumNotAllowed ); 

        }
   }
   else if( idField == ifds::IndexRate )
   {
        int indexRate = convertToULong( strValue );

        if( indexRate < MININDEXRATE || indexRate > MAXINDEXRATE )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_OUT_OF_RANGE_INDEX_RATE ); 
        }

   }
   else if( idField == ifds::GrossNetMethod )
   {
   }
   else if( idField == ifds::AddrCode )
   {
   }
   else if( idField == ifds::RIFPayType )
   {
        if( strValue == NULL_STRING )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_MANDATORY_PAY_TYPE );
        }

        if( I_("E") != strValue && I_("S") != strValue && I_("M") != strValue && I_("X") != strValue && I_("T") != strValue )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_INVALID_PAY_TYPE ); 
        }
        
        // P0186486_FN15_The Source of Funds
        {
           DString srcOfFund, dstrRIFPayType;
           
           getField(ifds::RRIFSrcOfFund, srcOfFund, idDataGroup, false); 
           getField(ifds::RIFPayType, dstrRIFPayType, idDataGroup, false); 
           srcOfFund.stripAll().upperCase();
           dstrRIFPayType.stripAll().upperCase();

           if(!srcOfFund.empty())
           {
              if(getWorkSession ().isSrcOfFundRequired(srcOfFund, idDataGroup))
              {
                 if(dstrRIFPayType != SUPPRESS)
                 {
                    getErrMsg (IFASTERR::SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE, 
                       CND::ERR_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE, 
                       CND::WARN_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE, 
                       idDataGroup);
                 }
              }
           }
        }
        
   }
   else if( idField == ifds::MinWithAge )
   {
        DString dstr;
        getField( ifds::TaxType, dstr, idDataGroup );
        dstr.strip().upperCase();
        if( getWorkSession ().isLIFLike (dstr) || dstr == LRIF_TAX_TYPE )
        {
            DString strLegMinWithAge( I_("") );
            _pAccount->getField(ifds::LegMinWithAge, strLegMinWithAge, idDataGroup);
            int legMinWithAge = convertToULong( strLegMinWithAge );

            if( strValue == NULL_STRING )
            {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_MANDATORY_MIN_WITH_AGE );
            }

            int minWithAge = convertToULong( strValue );
            if( minWithAge < legMinWithAge )
            {
            DString idiStr;
            addIDITagValue( idiStr, LEG_MIN_WITH_AGE, strLegMinWithAge );       
            ADDCONDITIONFROMFILEIDI( CND::ERR_RIF_TOO_BIG_MIN_WITH_AGE, idiStr ); 
            }
        }

   }
   else if( idField == ifds::TaxOnMin )
   {
   }
   else if( idField == ifds::RRIFcrossEffectiveDate )
   {
        DString strEffectiveDate;
        DString strMonthEnd;
        getField(ifds::EffectiveFrom, strEffectiveDate, idDataGroup);
        getField(ifds::EndOfMonth, strMonthEnd, idDataGroup);
        int effectiveDateDay = extractFieldFromDate( strEffectiveDate, I_("dd")  );

        if( effectiveDateDay > 28 && NO == strMonthEnd )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_EOM_EFFECTIVE_DATE );
            // generate warning "Effective Date is 29th, 30th or 31st"
        }

   }
   else if( idField == ifds::RRIFcrossStopDate )
   {
        DString strEffectiveDate;
        DString strStopDate;
        getField(ifds::StopDate, strStopDate, idDataGroup);
        getField(ifds::EffectiveFrom, strEffectiveDate, idDataGroup);
        int stopDateYear = extractFieldFromDate( strStopDate );
        int effectiveDateYear = extractFieldFromDate( strEffectiveDate );

        if( ( DSTCommonFunctions::CompareDates( strStopDate,strEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER 
            || stopDateYear != effectiveDateYear ) )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_WRONG_STOP_DATE );
        }

   }
   else if( idField == ifds::RRIFcrossEndOfMonth )
   {
        //_strOldMonthEnd is populated in doPreSetField with the old value of DBR::MonthEnd.
        DString strEndOfMonth;
        getField(ifds::EndOfMonth, strEndOfMonth, idDataGroup);

        DString strCurrBusDate;
        getWorkSession().getOption( ifds::CurrBusDate, strCurrBusDate, idDataGroup, false );
        int currBusDateMonth = extractFieldFromDate( strCurrBusDate, I_("MM") );

        DString strLastProcessDate;
        getField(ifds::LastProcessDate, strLastProcessDate, idDataGroup);
        int lastProcessDateMonth = extractFieldFromDate( strLastProcessDate, I_("MM") );

        if( YES == strEndOfMonth && NO == _strOldMonthEnd && currBusDateMonth == lastProcessDateMonth )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_EOM_MONTH_END ); 
        }
   }
   else if( idField == ifds::RRIFcrossFedRate )
   {
        DString strSuppFedTax;
        DString strFedRatePUD;
        DString strFedRate;
        getField(ifds::SuppFedTax, strSuppFedTax, idDataGroup);
        getField(ifds::FedRatePUD, strFedRatePUD, idDataGroup);
        getField(ifds::FedRate, strFedRate, idDataGroup);
        double fedRate = DSTCommonFunctions::convertToDouble( strFedRate );

        if( YES == strSuppFedTax && fedRate != 0 )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_NON_ZERO_RATE );
        }

        if( PERCENT == strFedRatePUD && fedRate > 100 )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_TOO_BIG_RATE );
        }

        if( strFedRatePUD == DOLLAR && DSTCommonFunctions::NumOfDecimals(strFedRate) > 2 )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_TOO_MANY_DECIMALS_RATE );
        }

   }
   else if( idField == ifds::RRIFcrossProvRate )
   {
        DString strSuppProvTax;
        DString strProvRatePUD;
        DString strProvRate;
        getField(ifds::SuppProvTax, strSuppProvTax, idDataGroup);
        getField(ifds::ProvRatePUD, strProvRatePUD, idDataGroup);
        getField(ifds::ProvRate, strProvRate, idDataGroup);
        double provRate = DSTCommonFunctions::convertToDouble( strProvRate );

        if( YES == strSuppProvTax && provRate != 0 )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_NON_ZERO_RATE );
        }

        if( strProvRatePUD == DOLLAR && DSTCommonFunctions::NumOfDecimals(strProvRate) > 2 )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_TOO_MANY_DECIMALS_RATE );
        }

        if( PERCENT == strProvRatePUD && provRate > 100 )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_TOO_BIG_RATE );
        }

   }
   else if( idField == ifds::RRIFcrossRate )
   {
        DString strFedRatePUD     = NULL_STRING;
        DString strProvRatePUD    = NULL_STRING;
        DString strGrossNetMethod = NULL_STRING;
        DString strFedRate        = NULL_STRING;
        DString strProvRate       = NULL_STRING;

        getField(ifds::FedRatePUD,     strFedRatePUD,     idDataGroup);
        getField(ifds::ProvRatePUD,    strProvRatePUD,    idDataGroup);
        getField(ifds::GrossNetMethod, strGrossNetMethod, idDataGroup);
        getField(ifds::FedRate,        strFedRate,        idDataGroup);
        getField(ifds::ProvRate,       strProvRate,       idDataGroup);

        double fedRate  = DSTCommonFunctions::convertToDouble( strFedRate );
        double provRate = DSTCommonFunctions::convertToDouble( strProvRate );

        if( PERCENT == strFedRatePUD && PERCENT == strProvRatePUD )
        {
            if( GROSS == strGrossNetMethod && (fedRate + provRate) > 100 ) //GROSS
            {
                ADDCONDITIONFROMFILE( CND::ERR_RIF_SUM_TOO_BIG1_RATE );
            }
            else if( NET == strGrossNetMethod && (fedRate + provRate) > 100 ) //NET
            {
                ADDCONDITIONFROMFILE( CND::ERR_RIF_SUM_TOO_BIG2_RATE );
            }
            else if ( NET_OF_FEES == strGrossNetMethod && (fedRate + provRate) > 100 ) // NET OF FEES
            {
                ADDCONDITIONFROMFILE( CND::ERR_RIF_SUM_TOO_BIG1_RATE );
            }  
        }
   }
   else if( idField == ifds::RRIFcrossIndexRate )
   {
        DString strIndexRate;
        getField(ifds::IndexRate, strIndexRate, idDataGroup);
        int indexRate = convertToULong( strIndexRate );

        DString strPayOption;
        getField(ifds::PayOption, strPayOption, idDataGroup);

        if( PAY_OPTION_INDEX != strPayOption && indexRate != 0 )
        {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_NON_ZERO_INDEX_RATE ); 
        }

   }
   else if( idField == ifds::RRIFcrossGrossNetMethod )
   {
        DString strGrossNetMethod;
        getField(ifds::GrossNetMethod, strGrossNetMethod, idDataGroup);

        DString strPayOption;
        getField(ifds::PayOption, strPayOption, idDataGroup);

        // old logic : if PayOption == PAY_OPTION_MINIMUM or PayOption == PAY_OPTION_MAXIMUM
        // only GROSS is allowed for strGrossNetMethod

        //if( ( strPayOption == PAY_OPTION_MINIMUM || strPayOption == PAY_OPTION_MAXIMUM ) && GROSS != strGrossNetMethod )
        //{
        //   ADDCONDITIONFROMFILE( CND::ERR_RIF_INVALID_GROSS_OR_NET ); 
        //}

        if( ( strPayOption == PAY_OPTION_MINIMUM || strPayOption == PAY_OPTION_MAXIMUM ) )
        {
            DString dstrNetOfFeesDate = NULL_STRING;
            DString dstrEffectiveDate = NULL_STRING;
            DString dstrAcctNumber    = NULL_STRING;
            DString dstrDSCFeeLevel   = NULL_STRING;
            MFAccount *pMFAccount     = NULL;

            getWorkSession().getOption( ifds::NetOfFeesDate, dstrNetOfFeesDate, idDataGroup, false );
            getField(ifds::EffectiveFrom, dstrEffectiveDate, idDataGroup);

            getParent()->getParent()->getField(ifds::AccountNum, dstrAcctNumber, idDataGroup);
            dstrAcctNumber.stripLeading( '0' ).strip();

            if ( !dstrAcctNumber.empty() && 
                  getWorkSession().getMFAccount(idDataGroup, dstrAcctNumber, pMFAccount) <= WARNING && 
                  pMFAccount 
                )
            {
                pMFAccount->getField(ifds::DSCFeeLevel, dstrDSCFeeLevel, idDataGroup);

                // if DSCFeeLevel is invalid value, force it to be '0'
                if ( ( dstrDSCFeeLevel == NULL_STRING ) || dstrDSCFeeLevel.empty() )
                {
                    setFieldNoValidate( ifds::DSCFeeLevel,I_("0"), idDataGroup,false, true, true, false);
                }
            }

			// the following logic is removed due to its conflic with new logic in RRIF_LIF_LRIF_Info::setGrossNetMethod
			// when paytype is transfer - confirmed bt Jennifer
            //// if EffectiveDate of setting up RRIF is before NetOfFeesDate
            //// use new logic , only 'GROSS' is allowed for Maximum and minimum payoption
            //if ( DSTCommonFunctions::CompareDates( dstrNetOfFeesDate,dstrEffectiveDate ) == DSTCommonFunctions::SECOND_EARLIER )
            //{
            //    if ( ( I_("0") == dstrDSCFeeLevel ) && ( GROSS != strGrossNetMethod ) )
            //    {
            //        ADDCONDITIONFROMFILE( CND::ERR_RIF_INVALID_GROSS_NET_METHOD_BEFORE_NETOFFEES_DATE );
            //    }
            //}
            //else
            //{
            //    // if EffectiveDate of setting up RRIF is same or after NetOfFeesDate and 
            //    // GrossNetMethod is not 'net of fees' or DSCFeelevel is not equal '0'
            //    // raise the condition
            //    if ( ( ( NET_OF_FEES != strGrossNetMethod ) ) || ( I_("0") != dstrDSCFeeLevel ))
            //    {
            //        ADDCONDITIONFROMFILE( CND::ERR_RIF_INVALID_GROSS_NET_METHOD_AFTER_NETOFFEES_DATE );
            //    }
            //}
        }
   }
   else if( idField == ifds::RRIFcrossAddrCode )
   {
      DString strAddrCode;
      DString strPayType;
      getField(ifds::AddrCode, strAddrCode, idDataGroup);
      getField(ifds::RIFPayType, strPayType, idDataGroup);

      if( I_("S") == strPayType )
      {
         AddressList *pAddressList = NULL;

         if( _pShareholder->getAddressList( pAddressList, idDataGroup ) <= WARNING )
         {
            bool bValid = false;
            if( !(pAddressList->IsValidateAddressCode( strAddrCode, idDataGroup, bValid ) ) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_RIF_UNKNOWN_ADDRESS_CODE ); 
            }
         }
      }
   }
   else if( idField == ifds::CrossInstTransit )
   {
      validateCrossInstTransit(idDataGroup);
   }
   else if( idField == ifds::InstCode )
   {
      ValidateInstCode(strValue,idDataGroup);  
   }
   else if( idField == ifds::TransitNo )
   {
      ValidateTransNo(strValue,idDataGroup);
   }
   else if( idField == ifds::BankAcctNum )
   {
   }
   else if( idField == ifds::InstName )
   {
   }
   else if( idField == ifds::SettleCross1 )
   {
      ValidateTaxOnMinSuppFedAndProvTax(idDataGroup);
   }
   else if( idField == ifds::AccountTo )
   {
      validateAcctTo( idDataGroup );	
   }
   else if( idField == ifds::PreYrPercent )
   {	
      validatePercent( ifds::PreYrPercent, idDataGroup );	
   }
	else if ( idField  == ifds::CompoundDate )
	{						
		validateEffectiveStopMonthIndicator(  idDataGroup );
	}		
	else if ( idField  == ifds::DayOfWeek )
	{
//		validateDayOfWeek(  idDataGroup );
	}		
	else if ( idField  == ifds::DaysOfMonth )
	{
      std::vector<DString> vDays;
      DSTCommonFunctions::tokenizeString( strValue, vDays ); 

      if( vDays.size() != 2 ) {
         ADDCONDITIONFROMFILE( CND::ERR_EXACTLY_TWO_RIFF_DAYS_OF_MONTH_REQUIRED ); 
      }

      std::vector<DString>::iterator iter = vDays.begin();
      for ( ; iter!=vDays.end(); ++iter ) {
         int iDayOfMonth = (*iter).strip().asInteger();
         if ( iDayOfMonth<1 || iDayOfMonth>31 ) {
            ADDCONDITIONFROMFILE( CND::ERR_DAYS_OF_MONTH_INVALID ); 
            break;
         }
      }
	}
	
	else if ( idField  == ifds::SrcOfFundSrcOfAcctXEdit )
	{//P0186486_FN15_The Source of Funds
	      ValidateSourceOfAccount(idDataGroup);
	}		
	return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
//  setFieldsAsReadOnly()
//  implemented  by yingbao
//  check status if bad: readonly
//  check permission if no: readonly
//  if it is not current year: readonly //added oct. 25,2001
void RRIF_LIF_LRIF_Info::setFieldsAsReadOnly(const BFDataGroupId& idDataGroup)
{
   DString strGoodBad;
   getField(ifds::GoodBad, strGoodBad, idDataGroup);
   bool bPermit37 = getWorkSession().hasUpdatePermission(UAF::RIF_LIF_LRIF_FIELD_INFO);
   bool bGood = strGoodBad == YES;  // for status equals to bad, we set all the fields as readonly
   bool bSameYr = isEffectiveDateInCurrentYr( idDataGroup ) != 0 ? true : false;
   bool bReadOnly = !(bSameYr && bGood  );

   setFieldReadOnly(ifds::EffectiveFrom, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::StopDate, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::Qualified, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::SpouseBirth, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::RIFSrcOfFund, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::PayOption, idDataGroup, bReadOnly);
   
   if( bReadOnly )
   {
      setFieldReadOnly(ifds::OverrideUnusedMax, idDataGroup, true);
      setFieldReadOnly( ifds::PYUnusedMax, idDataGroup, true);
   }
   //setFieldReadOnly(ifds::GrossNetMethod, idDataGroup, bReadOnly);

   // We will check RIFOverrides to determine whether the OverrideAmtYr is 
   // updatable.
   //if (bPermit37)
   {
      setFieldReadOnly(ifds::OverrideAmtYr, idDataGroup, bReadOnly);      
      setFieldReadOnly( ifds::SuppFedTax, idDataGroup, bReadOnly );
      setFieldReadOnly( ifds::SuppProvTax, idDataGroup, bReadOnly );	  
   }
   /*else 
   {
      setFieldReadOnly(ifds::OverrideAmtYr, idDataGroup, true);
      setFieldReadOnly( ifds::OverrideAmtYr, idDataGroup, true );
      setFieldReadOnly( ifds::SuppFedTax, idDataGroup, true );
	  setFieldReadOnly( ifds::SuppProvTax, idDataGroup, true );
   }*/
   
   setFieldReadOnly(ifds::RIFPayType, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::AddrCode, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::BatchTrace, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::AccountTo, idDataGroup, bReadOnly);

   DString strValue;
   bool bIndexRateRO = false;
   
   getField(ifds::PayOption, strValue, idDataGroup);
   if( strValue != PAY_OPTION_INDEX )
   {
      bIndexRateRO = true;
   }
   setFieldReadOnly(ifds::IndexRate, idDataGroup, bReadOnly | bIndexRateRO);

   // GrossNetMethod will be read when rifpaytype=T or bReadOnly
   DString dstrRIFPayType = NULL_STRING;
   getField(ifds::RIFPayType, dstrRIFPayType, idDataGroup, false);
   setFieldReadOnly( ifds::GrossNetMethod, idDataGroup, dstrRIFPayType == I_("T") || bReadOnly );

   DString strTaxJurisCode;

   _pShareholder->getField(ifds::TaxJurisCode,strTaxJurisCode,idDataGroup,false);
   int iValue =  strTaxJurisCode.asInteger();
   bool bTax = iValue == 15 || iValue < 13; 

   setFieldReadOnly( ifds::TaxOnMin, idDataGroup, bReadOnly | !bTax );

//---------------------------------------------------------------------
   DString dstrOverrideAmtYr,strTaxType;
   getField ( ifds::OverrideAmtYr, dstrOverrideAmtYr, idDataGroup );
   _pAccount->getField(ifds::TaxType, strTaxType, idDataGroup);
   strTaxType.strip();
   DString dstrMaxApply;
   _pAccount->getField(ifds::MaxApplies,dstrMaxApply,idDataGroup,false);

	//business rule changed: see PTS 10014772 Isabella's answer
	//yingbao May 22,2003
   //bool bUpdate = ( strTaxType == LRIF_TAX_TYPE || getWorkSession ().isLIFLike (strTaxType)) &&
   bool bUpdate = dstrOverrideAmtYr == YES && dstrMaxApply.strip() == YES;// && bPermit37;

   setFieldReadOnly( ifds::MaxAmtYr, idDataGroup, bReadOnly | !bUpdate );
   setFieldReadOnly( ifds::FedRatePUD, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::ProvRatePUD, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::Frequency, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::MonthIndicator, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::EndOfMonth, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::DayOfWeek, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::DaysOfMonth, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::RRIFBatchTrace, idDataGroup, true ); //we always set the  field as read only

   DString strOverrideAmtYr;
   getField(ifds::OverrideAmtYr, strOverrideAmtYr, idDataGroup);
   strOverrideAmtYr.strip();

// after checking with Isabella, Qualified should be always updateable July 18,2002, yingbao 
   if( getWorkSession ().isLIFLike (strTaxType) || strTaxType == LRIF_TAX_TYPE )
   {
      setFieldReadOnly( ifds::MinWithAge, idDataGroup, false | bReadOnly );
      //	setFieldReadOnly( ifds::Qualified, idDataGroup, true );

   }
   else
   {
      setFieldReadOnly( ifds::MinWithAge, idDataGroup, true );
      //	setFieldReadOnly( ifds::Qualified, idDataGroup, false | bReadOnly );

   }
   bUpdate = bSameYr && bGood /*&& bPermit37*/ &&
                  (strTaxType == RRIF_TAX_TYPE ||
						strTaxType == PRIF_TAX_TYPE
						||  strTaxType == LRIF_TAX_TYPE ) &&
                  strOverrideAmtYr == YES;

   setFieldReadOnly( ifds::MandAmtYr, idDataGroup, !bUpdate );


   bUpdate = bSameYr && bGood /*&& bPermit37*/ && /*strTaxType == LRIF_TAX_TYPE  && */
             strOverrideAmtYr == YES && dstrMaxApply.strip() == YES;
   setFieldReadOnly( ifds::MaxAmtYr, idDataGroup, !bUpdate );


   setAmountReadOnly(bSameYr && bGood,idDataGroup);

   DString strSuppProvTax;
   getField(ifds::SuppProvTax, strSuppProvTax, idDataGroup,false);
   strSuppProvTax.strip();
   bUpdate = bSameYr && bGood && (strSuppProvTax == NO);
   setFieldReadOnly( ifds::ProvRate, idDataGroup, !bUpdate );

   DString strSuppFedTax;
   getField(ifds::SuppFedTax, strSuppFedTax, idDataGroup,false);
   strSuppFedTax.strip();
   bUpdate = bSameYr && bGood && (strSuppFedTax == NO);
   setFieldReadOnly( ifds::FedRate, idDataGroup, !bUpdate );

   DString dstrProvReg;   
   _pAccount->getField( ifds::PensionJuris, dstrProvReg, idDataGroup );

   TaxTypeRule *pTaxTypeRule = NULL;
   if ( _pAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
   {
      if ( !pTaxTypeRule->canUseSpousesAge( dstrProvReg, idDataGroup ) )
      {
         setFieldReadOnly( ifds::SpouseBirth, idDataGroup, true );
      }
   }

   if( !isNew() )
   {
      setNetAmountReadOnly(bSameYr && bGood,idDataGroup);
   }

   setFieldReadOnly( ifds::OrigPlanDeff, idDataGroup, bReadOnly );


}
//****************************************************************************
//  setNetAmountReadOnly
// implemented by yingbao
void RRIF_LIF_LRIF_Info::setNetAmountReadOnly(bool bGood,const BFDataGroupId& idDataGroup)
{
   DString strPayOption,strGrossNetMethod,strMandAmtYr,strRRIFOrPayment;
   bool bReadOnly = false;
   getField(ifds::PayOption,strPayOption,idDataGroup,false);
   strPayOption.strip().upperCase();

   getField( ifds::GrossNetMethod , strGrossNetMethod, idDataGroup,false );
   strGrossNetMethod.strip();       

   getWorkSession().getOption( ifds::RRIFOrPayment, strRRIFOrPayment, idDataGroup, false );
   strRRIFOrPayment.strip();

   DString strTaxType;
   _pAccount->getField(ifds::TaxType, strTaxType, idDataGroup,false);
   // PayOption is Minimum
   if( strPayOption == PAY_OPTION_MINIMUM && (strTaxType == RRIF_TAX_TYPE || getWorkSession ().isLIFLike (strTaxType) || 
			strTaxType == LRIF_TAX_TYPE || strTaxType == PRIF_TAX_TYPE ) )
      bReadOnly = true;
   else if( strPayOption == PAY_OPTION_MAXIMUM && ( getWorkSession ().isLIFLike (strTaxType) || strTaxType == LRIF_TAX_TYPE || 
			strTaxType == PRIF_TAX_TYPE ) )
      bReadOnly = true;
   else if( (strPayOption      == PAY_OPTION_FIX || strPayOption      == PAY_OPTION_INDEX ) && 
            (strGrossNetMethod == GROSS          || strGrossNetMethod == NET_OF_FEES      ) && //fix a
            (strTaxType        == RRIF_TAX_TYPE  || getWorkSession ().isLIFLike (strTaxType) || 
             strTaxType        == LRIF_TAX_TYPE  || strTaxType        == PRIF_TAX_TYPE	  )    
          )
   {
      bReadOnly = true;
   }
   else if ( strPayOption == PAY_OPTION_PERCENT ) 
      bReadOnly = true;
   else if(strPayOption == PAY_METHOD_GWA || strPayOption == PAY_METHOD_LWA ) 
      bReadOnly = true;

   bReadOnly |= !bGood;
   setFieldReadOnly( ifds::NetAmt, idDataGroup, bReadOnly );

}

//*****************************************************************************
//  setAmountReadOnly
// implemented by yingbao
void RRIF_LIF_LRIF_Info::setAmountReadOnly(bool bGood,const BFDataGroupId& idDataGroup)
{
   DString strPayOption,strGrossNetMethod,strMandAmtYr,strRRIFOrPayment;
   bool bReadOnly = false;
   getField(ifds::PayOption,strPayOption,idDataGroup,false);
   strPayOption.strip();

   getField( ifds::GrossNetMethod , strGrossNetMethod, idDataGroup,false );
   strGrossNetMethod.strip();       

   getField(ifds::MandAmtYr,strMandAmtYr,idDataGroup,false);
   strMandAmtYr.strip();
   double mandAmtYr = DSTCommonFunctions::convertToDouble( strMandAmtYr );

   getWorkSession().getOption( ifds::RRIFOrPayment, strRRIFOrPayment, idDataGroup, false );
   strRRIFOrPayment.strip();


   DString dstrTaxType;
   _pAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup );
   dstrTaxType.strip().upperCase();

   if( strPayOption == PAY_OPTION_MAXIMUM && ( getWorkSession ().isLIFLike (dstrTaxType) || dstrTaxType == LRIF_TAX_TYPE ) )//payOption is max
      bReadOnly =true;
   else if( (strGrossNetMethod == NET ) && (strPayOption == PAY_OPTION_FIX || strPayOption == PAY_OPTION_INDEX )  //pay option fixed and index
            && ( getWorkSession ().isLIFLike (dstrTaxType) || dstrTaxType == LRIF_TAX_TYPE || dstrTaxType == RRIF_TAX_TYPE
				|| dstrTaxType == PRIF_TAX_TYPE ) )
      bReadOnly = true;
   else if( (strPayOption == PAY_OPTION_MINIMUM ) /*&& (mandAmtYr != 0.0 || strRRIFOrPayment != YES )*/  //pay option is Minimum PTS 10009021
            && (getWorkSession ().isLIFLike (dstrTaxType) || dstrTaxType == LRIF_TAX_TYPE || dstrTaxType == RRIF_TAX_TYPE 
				|| dstrTaxType == PRIF_TAX_TYPE	) )
      bReadOnly = true;
   else if ( strPayOption == PAY_OPTION_PERCENT ) 
      bReadOnly = true;
   else if(strPayOption == PAY_METHOD_GWA || strPayOption == PAY_METHOD_LWA ) 
      bReadOnly = true;

   bReadOnly |= !bGood;
   setFieldReadOnly( ifds::RRIFAmount, idDataGroup, bReadOnly );

}

//******************************************************************************
// strDateField must be "dd" to extract a day, "yyyy" for year and "MM" for month.
// strDateField defaults to "yyyy"
int RRIF_LIF_LRIF_Info::extractFieldFromDate( DString const &strField, DString strDateField )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "extractFieldFromDate" ) );
   // look in the registry for the date format mask
   // the current date should be in host format
   DString dstrConfiguration( I_( "HostMasks" ) );
   DString dstrKey( I_("D") );
   DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
   int field = 0;

   DString strDateFld;
   int field_pos = mask.find( strDateField);

   if( strField == NULL_STRING )
   {
      return(field);
   }
   else if( DString::npos != field_pos )
   {
      strDateFld.assign( strField, field_pos, strDateField.length() );
      field = convertToULong( strDateFld );
   }

   return(field);
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::commonInit(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "commonInit" ));

   getParent()->getParent()->getField(ifds::AccountNum, _strAccountNum, idDataGroup);
   _strAccountNum.strip().stripLeading( '0' );

   _pAccount = dynamic_cast<MFAccount*> (getParent()->getParent());

   DString strShrNum,strValue,dstr;
   _pAccount->getField( ifds::ShrNum, strShrNum, idDataGroup );
   getWorkSession().getShareholder( idDataGroup, strShrNum, _pShareholder );

   _pAccount->getField( ifds::TaxType, dstr, idDataGroup );
   dstr.strip().upperCase();
   if( getWorkSession ().isLIFLike (dstr) || dstr == I_("L") )
   {
      _pAccount->getField(ifds::MinWithAge, strValue, idDataGroup);
      setFieldNoValidate( ifds::MinWithAge, strValue, idDataGroup );
   }
   _pAccount->getField(ifds::PensionJuris, strValue, idDataGroup);
   setFieldNoValidate( ifds::PensionJuris, strValue, idDataGroup );

   //Now create the month indicator field.
   if( !isNew() )
      setMonthIndicator( idDataGroup );
   setFieldNoValidate( ifds::CalcFedProvTax, NO, idDataGroup );
   //setFieldNoValidate( DBR::Frequency, FREQ_OTHER, idDataGroup );
   setFieldNoValidate( ifds::SetAsDefault, NO, idDataGroup );
   setFieldNoValidate( ifds::SetRTAsDefault, NO, idDataGroup );

   BFProperties* pBFP   =  getFieldProperties(ifds::RIFPayType,idDataGroup);
   if( pBFP )
   {
      DString strSubValue,strLeft,strRight,strValue( I_("W=") );
      pBFP->getAllSubstituteValues( strSubValue );
      int pos1 = strSubValue.find(strValue );

	  // ; at the end of the substitution should also be removed.
      int pos2 =  strSubValue.find(I_(";"),pos1 ) + 1 ;
						
		pos2 = strSubValue.length() - pos2;
      strLeft= strSubValue.left( pos1 );
      strRight = strSubValue.right ( pos2 );
      strSubValue =  strLeft + strRight;
      setFieldAllSubstituteValues( ifds::RIFPayType, idDataGroup, strSubValue );
   }
	// frequency we support is 
	//1---weekly
	//2---bi-weekly
	//3---monthly
	//3---semi-monthly
	//5---quarterly
	//6---semianually
	//7---Annually
	//8---Other
	DString dstrCode[] ={I_("1"),I_("2"),I_("3"),I_("4"),I_("5"),I_("6"),I_("7"),I_("8")};
	DString dstrDesc,strSubValue;
	strSubValue = NULL_STRING;
	pBFP   =  getFieldProperties(ifds::Frequency,idDataGroup);
   if( pBFP )
   {
		for( int i = 0; i<8; i++ )
		{
			dstrDesc = dstrCode[i];
			strSubValue += dstrCode[i];
			pBFP->formatValue(ifds::Frequency,dstrDesc,true);
			strSubValue += I_("=")+dstrDesc + I_(";");				
		}
      setFieldAllSubstituteValues( ifds::Frequency, idDataGroup, strSubValue );
	}
   setFieldNoValidate( ifds::AmountType, I_("D"), idDataGroup ); // set AmountType to Amount
   
   DString dstrOverrideMax;
   getField( ifds::OverrideUnusedMax, dstrOverrideMax, idDataGroup );
   setFieldReadOnly( ifds::OverrideUnusedMax, 
			         idDataGroup, 
			         isOverrideUnusedAmtReadOnly( idDataGroup ) );

   setFieldReadOnly( ifds::PYUnusedMax, idDataGroup, isOverrideUnusedAmtReadOnly( idDataGroup ) || dstrOverrideMax == I_( "N" ) );   

   DString dstrNetOfFeesDate = NULL_STRING;
   DString dstrEffectiveDate = NULL_STRING;

   getWorkSession().getOption( ifds::NetOfFeesDate, dstrNetOfFeesDate, idDataGroup, false );
   getField(ifds::EffectiveFrom, dstrEffectiveDate, idDataGroup);

   // EffectiveFrom's value is not set yet, get if from current business date of system
   if ( (dstrEffectiveDate == NULL_STRING ) || dstrEffectiveDate.empty() )
   {
       getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrEffectiveDate, idDataGroup ,false );
   }

   if ( ( DSTCommonFunctions::CompareDates( dstrNetOfFeesDate,dstrEffectiveDate ) == DSTCommonFunctions::SECOND_EARLIER ) ||
        ( DSTCommonFunctions::CompareDates( dstrNetOfFeesDate,dstrEffectiveDate ) == DSTCommonFunctions::EQUAL )          ||
        ( dstrNetOfFeesDate == NULL_STRING) )
   {
       setFieldSubstituteValues (ifds::GrossNetMethod, BF::HOST,    ifds::GrossNetMethod2);
       setFieldSubstituteValues (ifds::GrossNetMethod, idDataGroup, ifds::GrossNetMethod2);
   }

   DString effectiveDate;
   getField( ifds::EffectiveFrom , effectiveDate, idDataGroup );
   
   _effectiveDateYear = extractFieldFromDate( effectiveDate );

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
void RRIF_LIF_LRIF_Info::setMonthIndicator(const BFDataGroupId& idDataGroup)
{
   DString strMonthIndicator = I_("");
   DString strTemp;
   const BFFieldId monthID[] = {ifds::January, ifds::February, ifds::March, ifds::April, ifds::May, ifds::June, 
      ifds::July, ifds::August, ifds::September, ifds::October, ifds::November,ifds::December};
   for( int index = 0; index < 12 ; index++ )
   {
      getField( monthID[index], strTemp, idDataGroup );
      strMonthIndicator = strMonthIndicator + strTemp.substr(0, 1);
   };
   setFieldNoValidate( ifds::MonthIndicator, strMonthIndicator, idDataGroup );
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::setMonthlyIndicatorByDeffFreq( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setMonthlyIndicatorByDeffFreq" ));

	DString dstrMon[12] = { NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO};
      const BFFieldId monthID[] = {ifds::January, ifds::February, ifds::March, ifds::April, ifds::May, ifds::June, 
         ifds::July, ifds::August, ifds::September, ifds::October, ifds::November,ifds::December};

	  DString strValue;
      //get month of EffectiveDate, all periodical payments are based on this month.
      getField( ifds::EffectiveFrom , strValue, idDataGroup );
      int baseMonth = extractFieldFromDate( strValue, I_("MM") );
      baseMonth--;

      getField( ifds::Frequency, strValue, idDataGroup );

      int paymentPeriod;

      if( strValue == FREQ_MONTHLY )
      {
         paymentPeriod = 1;
      }
      else if( strValue == FREQ_QUARTERLY )
      {
         paymentPeriod = 3;
      }
      else if( strValue == FREQ_SEMIANNUALLY )
      {
         paymentPeriod = 6;
      }
      else if( strValue == FREQ_ANNUALLY )
      {
         paymentPeriod = 12;
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY()); // Do not change anything.
      }

      int index = baseMonth;
      while( dstrMon[index] != YES )
      {
         dstrMon[index] = YES;
         index = (index + paymentPeriod)%12;
      };

      strValue = I_("");
      for( index = 0; index < 12 ; index++ )
      {
         setFieldNoValidate( monthID[index], dstrMon[index], idDataGroup ); 
         strValue = strValue + dstrMon[index].substr(0, 1);
      };

      setFieldNoValidate( ifds::MonthIndicator, strValue,  idDataGroup, true, true, true ); // Notify the observers.

	  return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************************************************
//	ForceToDoCalculation() is an interface method, which will be called by process 
// when user presses Calc button on the screen
SEVERITY RRIF_LIF_LRIF_Info::ForceToDoCalculation(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ForceToDoCalculation" ) );

   updateAmountsForGrossPayTypeGEL(idDataGroup);
   validateAgainst130(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY RRIF_LIF_LRIF_Info::updateAmountsForGrossPayTypeGEL(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "updateAmountsForGrossPayTypeGEL" ) );

   RRIF_LIF_LRIF_PaymentsCalculation *pPaymentsCalc;
   if( getPaymentsCalculation(pPaymentsCalc, idDataGroup ) <= WARNING && pPaymentsCalc )
   {
      DString dstrPayOption;
      DString dstrGrossNetMethod;
      getField(ifds::PayOption, dstrPayOption, idDataGroup, false); 
      getField(ifds::GrossNetMethod, dstrGrossNetMethod, idDataGroup, false);

      if(dstrGrossNetMethod == GROSS_NET_METHOD_GROSS &&
         (dstrPayOption == PAY_METHOD_LWA ||
          dstrPayOption == PAY_METHOD_GWA ))
      {
         DString dstrAmountSysCalc;
         DString dstrNetAmountSysCalc;

         pPaymentsCalc->getField(ifds::AmountSysCalc,    dstrAmountSysCalc,    idDataGroup, false);
         pPaymentsCalc->getField(ifds::NetAmountSysCalc, dstrNetAmountSysCalc, idDataGroup, false);
 
         setField(ifds::RRIFAmount, dstrAmountSysCalc,    idDataGroup, false, true);
         setField(ifds::NetAmt,     dstrNetAmountSysCalc, idDataGroup, false, true);

      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::ValidateValueAgainstCalc( const BFFieldId& idField, const BFFieldId& calculatedFieldId, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateValueAgainstCalc" ) );

   DString strValue,strCalculated,strRatePUD,strSuppTax;

   getField(idField, strValue, idDataGroup,true);   
   RRIF_LIF_LRIF_PaymentsCalculation *pPaymentsCalc;
   if( getPaymentsCalculation(pPaymentsCalc, idDataGroup ) <= WARNING && pPaymentsCalc )
   {
	   pPaymentsCalc->getField( calculatedFieldId, strCalculated, idDataGroup,true);
   }

   double dValue = DSTCommonFunctions::convertToDouble( strValue );
   double dCalculated = DSTCommonFunctions::convertToDouble( strCalculated );
   bool bIssueWarning = true;
   if( idField == ifds::FedRate || idField == ifds::ProvRate )
   {
	  // Remove any edits added during the previous validation, then notify the status changes. This is needed 
	  // because this function could be called outside the usual validation process.
	  clearFieldErrors(idField, idDataGroup);
	  notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_STATE_CHANGE, I_( "" ));

      BFFieldId fieldPUD = ifds::ProvRatePUD;
      BFFieldId fieldSuppTax = ifds::SuppProvTax;   
	
      if( idField == ifds::FedRate )
      {
         fieldPUD = ifds::FedRatePUD;
         fieldSuppTax = ifds::SuppFedTax; 
      }

      getField( fieldPUD, strRatePUD,idDataGroup,false);
      getField( fieldSuppTax, strSuppTax,idDataGroup,false);
      strSuppTax.strip();
      if( strRatePUD != PERCENT && strSuppTax == NO )
      {  // it is dollar,unit, we do not know if it is right
         DString idiStr;
         DString /*locale,*/ lLabel;
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get( fieldPUD );
         lLabel = pProps->getLabel( ClientLocaleContext::get() );  
         addIDITagValue( idiStr, RATE_PUID, lLabel );       
         ADDCONDITIONFROMFILEIDI( CND::ERR_RRIF_LIF_RATE_PUID, idiStr );
         setFieldValid( idField, idDataGroup, false );
         bIssueWarning = false;
      } // if( strRatePUD != PERCENT && strSuppTax == NO )
      if( dValue < dCalculated )
      {
         if(idField == ifds::FedRate) 
         {
            //ADDCONDITIONFROMFILE( CND::ERR_RIF_FED_RATE_LESS_THAN_DEFAULT); 
            getErrMsg ( IFASTERR::RIF_FED_RATE_LESS_THAN_DEFAULT,
                        CND::ERR_RIF_FED_RATE_LESS_THAN_DEFAULT,
                        CND::WARN_RIF_FED_RATE_LESS_THAN_DEFAULT,
                        idDataGroup);
         }
         else //idField == ifds::ProvRate
         {
            //ADDCONDITIONFROMFILE( CND::ERR_RIF_PROV_RATE_LESS_THAN_DEFAULT);
            getErrMsg ( IFASTERR::RIF_PROV_RATE_LESS_THAN_DEFAULT,
                        CND::ERR_RIF_PROV_RATE_LESS_THAN_DEFAULT,
                        CND::WARN_RIF_PROV_RATE_LESS_THAN_DEFAULT,
                        idDataGroup);
         }
         setFieldValid( idField, idDataGroup, false );
         setCrossEditInvalid(idField, idDataGroup );
      }

	  if(isNew())
	  {
			bool bIsFirstOfYear = true;
			//Check if there are any other records with the same year
			{
				
				DString dstrDeff;
				getField(ifds::EffectiveFrom, dstrDeff, idDataGroup);
				int year = extractFieldFromDate(dstrDeff);

				for( BFObjIter iter(*getParent(), idDataGroup);
					!iter.end();
					++iter)
				{
					if( iter.getObject() == this )
						continue;

					DString dstrIterDeff;
					iter.getObject()->getField(ifds::EffectiveFrom, dstrIterDeff, idDataGroup);
					
					if( extractFieldFromDate(dstrIterDeff) == year)
					{
						bIsFirstOfYear = false;
						break;
					}
				}
			}
			if(bIsFirstOfYear)
			{
				DString dstrGrossNetMethod;
				DString dstrRRIFAmount;
				DString dstrMandAmtPay;

				getField(ifds::GrossNetMethod, dstrGrossNetMethod, idDataGroup);
				getField(ifds::RRIFAmount, dstrRRIFAmount, idDataGroup);
				getField(ifds::MandAmtPay, dstrMandAmtPay, idDataGroup);
				if(dstrGrossNetMethod != I_("02") /* || dstrRRIFAmount.asInteger() <= dstrMandAmtPay.asInteger()*/)
				{
					bIssueWarning = false;
				}
			}
	  }
   } // if( idField == ifds::FedRate || idField == ifds::ProvRate )
   if( dValue != dCalculated ) //if the existing view 130 value is different from the new one.
   {
      if( bIssueWarning )
      {
         DString idiStr;
         DSTCommonFunctions::formattedField(ifds::USDollar, 2, strCalculated);
         addIDITagValue( idiStr, CALCULATED, strCalculated );       
         ADDCONDITIONFROMFILEIDI( CND::ERR_RIF_DIFF_CALC_VALUE, idiStr ); 
         setFieldValid( idField, idDataGroup, false );
         setCrossEditInvalid(idField, idDataGroup );
      }
   } // if( dValue != dCalculated ) //if the existing view 130 value is different from the new one.
   

   SEVERITY sevRtn = GETCURRENTHIGHESTSEVERITY( );
   if( sevRtn >= WARNING )
   {
      CONDITIONVECTOR* _pCond;

      getFieldConditionVector(idField,idDataGroup,_pCond );
      if( _pCond == NULL )
         _pCond = new CONDITIONVECTOR;
      int count = CURRENTCONDITIONCOUNT( );
      Condition   *c = NULL;
      for( int i = 0; i < count; i++ )
      {
         c = new Condition( *GETCURRENTCONDITION( i ));
         _pCond->push_back( c );
      };
      setFieldConditionVector(idField, idDataGroup,_pCond );
      notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ) );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************************
// 0 ealier year
// 1 same year
// 2 future year

int RRIF_LIF_LRIF_Info::isEffectiveDateInCurrentYr(const BFDataGroupId& idDataGroup)
{

   DString dstrEffectiveDate;

   getField(ifds::EffectiveFrom,dstrEffectiveDate,idDataGroup,false );
   int effectiveDateYear = extractFieldFromDate( dstrEffectiveDate );
   DString strCurrBusDate;
   getWorkSession().getOption( ifds::CurrBusDate, strCurrBusDate, idDataGroup, false );
   int currBusDateYear = extractFieldFromDate( strCurrBusDate );
   if( currBusDateYear == effectiveDateYear ) return(1);
   else if( currBusDateYear > effectiveDateYear ) return(0);
   else return(2);    
}
//********************************************************************************
bool RRIF_LIF_LRIF_Info::isOnlySpouseBirthDateUpdated(const BFDataGroupId& idDataGroup)
{

   bool bUpdated = isFieldUpdated(  ifds::SpouseBirth, idDataGroup );
   const BFFieldId idField[] = {
      ifds::PayOption,
      ifds::TaxOnMin,
      ifds::FedRatePUD,
      ifds::ProvRatePUD,
      ifds::MandAmtYr,
      ifds::RRIFAmount,
      ifds::NetAmt,
      ifds::MaxAmtYr,
      ifds::FedRate,
      ifds::ProvRate,
      ifds::MandAmtPay,
      ifds::NullFieldId};
   int i = 0;
   while( idField[i] != ifds::NullFieldId )
   {
      if( isFieldUpdated( idField[i], idDataGroup ) )
      {
         bUpdated =  false;  // if there is another field updated, the result is false 
         break;
      }
      ++i;
   }
   return(bUpdated);  
}
//***********************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::validateRRIFAmount(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRRIFAmount" ) );
   DString strTemp,strValue,dstrGrossNetMethod,dstrAmount;
   
	getField(ifds::RRIFAmount,dstrAmount,idDataGroup, false );
   double dAmount = ( DSTCommonFunctions::convertToDouble( dstrAmount ) );

   RRIF_LIF_LRIF_PaymentsCalculation *pPaymentsCalc;
   if( getPaymentsCalculation(pPaymentsCalc, idDataGroup ) <= WARNING && pPaymentsCalc )
   {
      pPaymentsCalc->getField(ifds::AmountSysCalc,strValue,idDataGroup);
   }
   double dAmountSys = ( DSTCommonFunctions::convertToDouble( strValue ) ); 
   
	//If it is a Net.  Get the RRIFF amount from View 130 before applying business rules.

   getField(ifds::GrossNetMethod,dstrGrossNetMethod,idDataGroup,false);
   dstrGrossNetMethod.strip();
   if( dstrGrossNetMethod == NET || isFieldReadOnly(ifds::RRIFAmount,idDataGroup)  )
   { // if it is readonly or Net, take the value from view 130
      if( dAmountSys != dAmount )
      {
         setFieldNoValidate(ifds::RRIFAmount, strValue, idDataGroup,true,true,true);        
         dAmount = dAmountSys;
      }
   }
   /*rule 1:  RRIFAmount must be > 0 if MandAmtYrSysCalc !=  0 and 
      year of EffectiveDate is the same year of CurrBusDate.
   */
   bool bAddCondition = false;
   if( isEffectiveDateInCurrentYr( idDataGroup ) == 1  && dAmountSys != 0.0 )
   {
      if( dAmount <= 0.0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_RRIFAmountCannotBeLessEqualZero ); 
         bAddCondition = true;
      }
   }
	// RRIFAmount is readonly
   /*if ( isFieldReadOnly( ifds::RRIFAmount, idDataGroup ) )
	{
		// Incident 738173 -- Change logic to be consistant with the Base
		DString dstrMaxAmtYr, dstrTotRedem;
		double  dMaxAmtYr, dTotRedem;
				
		getField(ifds::MaxAmtYr,dstrMaxAmtYr,idDataGroup,false);
		dMaxAmtYr = DSTCommonFunctions::convertToDouble( dstrMaxAmtYr );

		_pRRIF_LIF_LRIF_PaymentsCalculation->getField(ifds::TotRedem, dstrTotRedem,idDataGroup, false );
      dTotRedem = ( DSTCommonFunctions::convertToDouble( dstrTotRedem ) );
		
		if ( dAmountSys > dTotRedem && dMaxAmtYr != 0 )
		{
			ADDCONDITIONFROMFILE( CND::ERR_AMOUNT_GREAT_THAN_MAX );
         bAddCondition = true;
		}

		return(GETCURRENTHIGHESTSEVERITY());
	}*/
/*  removed by check FERule Nov 19,01
      if(strTemp.strip().upperCase() == I_("M") /*|| dstrGrossNet.strip() == I_("N") && bUpdated ) //
      {
         getField(DBR::MandAmtPay,strValue,idDataGroup);
         double dAmountSys = ( DSTCommonFunctions::convertToDouble( strValue ) ); 
         if( dAmountSys != dAmount ){
            setField(DBR::RRIFAmount, strValue, idDataGroup,true,true);
         }
      } 
*/
   // RRIFAmount is updatable
   DString dstrMandAmount,/*dstrTotRedem,*/dstrMaxApplies;
   if( pPaymentsCalc )
   {
      pPaymentsCalc->getField(ifds::MandAmtPaySysCalc,dstrMandAmount,idDataGroup,false);   
   }
   double dMandAmount = ( DSTCommonFunctions::convertToDouble( dstrMandAmount ) );
   SEVERITY sevRtn;
   // Amount can not be less than MandAmtPaySysCalc

   DString strPayOption;
   getField(ifds::PayOption, strPayOption, idDataGroup); 

   if(!DSTCommonFunctions::codeInList (strPayOption, GWLWA_OPTIONS) && 
      dAmount < dMandAmount && isEffectiveDateInCurrentYr( idDataGroup ) == 1 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_PAYMENT_BELOW_MIN );
      bAddCondition = true;
   }
   //rule 2
   DString dstrMaxAmt, dstrTotRedem;
   getField(ifds::MaxAmtYr,dstrMaxAmt,idDataGroup,false);
   double  dMaxAmt = DSTCommonFunctions::convertToDouble( dstrMaxAmt );

   
   if( pPaymentsCalc )
   {
      pPaymentsCalc->getField(ifds::TotRedem,dstrTotRedem,idDataGroup, false );
   }
   double dTotRed = ( DSTCommonFunctions::convertToDouble( dstrTotRedem ) ); 
   
   _pAccount = dynamic_cast<MFAccount*> (getParent()->getParent());
   _pAccount->getField(ifds::MaxApplies,dstrMaxApplies,idDataGroup, false );
   sevRtn = GETCURRENTHIGHESTSEVERITY( );
   if( YES == dstrMaxApplies.strip() && isEffectiveDateInCurrentYr( idDataGroup ) == 1 )
   {
      if( dAmount > dTotRed && dMaxAmt > 0.0 )       
      {
         ADDCONDITIONFROMFILE( CND::ERR_AMOUNT_GREAT_THAN_MAX );
         bAddCondition = true;
      }
   }
   sevRtn = GETCURRENTHIGHESTSEVERITY( );
   if( sevRtn >= WARNING && bAddCondition )
   {
      const BFFieldId& idField = ifds::RRIFAmount;
      setFieldValid(idField, idDataGroup, false );
      setCrossEditInvalid(idField, idDataGroup );

      CONDITIONVECTOR* _pCond;

      getFieldConditionVector(idField,idDataGroup,_pCond );
      if( _pCond == NULL )
         _pCond = new CONDITIONVECTOR;
      int count = CURRENTCONDITIONCOUNT( );
      _pCond->push_back(  new Condition( *GETCURRENTCONDITION( --count )) );           
      setFieldConditionVector(idField, idDataGroup,_pCond );
      notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::validateNetAmount(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateNetAmount" ) );

   DString strGrossNetMethod,strValue;
   getField(ifds::GrossNetMethod,strGrossNetMethod,idDataGroup,false);
   if( ( GROSS       == strGrossNetMethod.strip().upperCase() ) ||
       ( NET_OF_FEES == strGrossNetMethod.strip().upperCase() ) ) //Gross or Net of Fees
   {
	  RRIF_LIF_LRIF_PaymentsCalculation *pPaymentsCalc;
      if( getPaymentsCalculation(pPaymentsCalc, idDataGroup ) <= WARNING && pPaymentsCalc )
      {
         pPaymentsCalc->getField(ifds::NetAmountSysCalc,strValue,idDataGroup);
	  }
      DString oldValue;
      getField(ifds::NetAmt,oldValue, idDataGroup );
      double dNetAmt = ( DSTCommonFunctions::convertToDouble( oldValue ) ); 
      double dNetAmtSys = ( DSTCommonFunctions::convertToDouble( strValue ) ); 
      if( dNetAmtSys != dNetAmt )
      {
         setField(ifds::NetAmt, strValue, idDataGroup,true,true);
      }
   }
   else // Net 
   {
      DString dstrMandAmtYrSysCalc,dstrNetAmt;
	  RRIF_LIF_LRIF_PaymentsCalculation *pPaymentsCalc;
      if( getPaymentsCalculation(pPaymentsCalc, idDataGroup ) <= WARNING && pPaymentsCalc )
      {
         pPaymentsCalc->getField(ifds::MandAmtYrSysCalc,dstrMandAmtYrSysCalc,idDataGroup,false);  
	  }
      double dMandAmtYr = ( DSTCommonFunctions::convertToDouble( dstrMandAmtYrSysCalc ) );
      if( isEffectiveDateInCurrentYr( idDataGroup ) == 1 && dMandAmtYr != 0.0 )
      {
         getField(ifds::NetAmt,dstrNetAmt,idDataGroup,false);
         double dNetAmt = ( DSTCommonFunctions::convertToDouble( dstrNetAmt ) );
         if( dNetAmt <= 0.0 )
         {
            SEVERITY sevRtn = GETCURRENTHIGHESTSEVERITY( );
            if( sevRtn <= WARNING )
            {
               ADDCONDITIONFROMFILE( CND::ERR_NET_AMOUNT_LESS_THEN_ZERO );

               const BFFieldId& idField = ifds::NetAmt;
               setFieldValid(idField, idDataGroup, false );
               setCrossEditInvalid(idField, idDataGroup );

               CONDITIONVECTOR* _pCond;

               getFieldConditionVector(idField,idDataGroup,_pCond );
               if( _pCond == NULL )
                  _pCond = new CONDITIONVECTOR;
               int count = CURRENTCONDITIONCOUNT( );
               Condition   *c = NULL;
               c = new Condition( *GETCURRENTCONDITION( --count  ));
               _pCond->push_back( c );          
               setFieldConditionVector(idField, idDataGroup,_pCond );
               notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ) );
            }
         }
      }
      ValidateValueAgainstCalc( ifds::NetAmt, ifds::NetAmountSysCalc, idDataGroup  );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
// validateAgainst130
// implemented by yingbao
//
SEVERITY RRIF_LIF_LRIF_Info::validateAgainst130(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAgainst130" ) );
   // if it is not current year we do not make view call
   // Oct. 25,2001
   if( isEffectiveDateInCurrentYr( idDataGroup ) != 1 )
      return(GETCURRENTHIGHESTSEVERITY());
   RRIF_LIF_LRIF_PaymentsCalculation *pPaymentsCalc;
   if( getPaymentsCalculation(pPaymentsCalc, idDataGroup ) <= WARNING && pPaymentsCalc )      
   {
      // if it is only Spouse BirthDate updated, we do not issue warning message.
      DString dstrOverrideAmtYr;
      getField ( ifds::OverrideAmtYr, dstrOverrideAmtYr, idDataGroup );
      dstrOverrideAmtYr.strip();
      if( !isOnlySpouseBirthDateUpdated( idDataGroup ) && ( dstrOverrideAmtYr == NO ) )
      {
         //issue warning message
         ValidateValueAgainstCalc( ifds::MandAmtYr, ifds::MandAmtYrSysCalc, idDataGroup  );
      }
      if( isFieldReadOnly( ifds::MandAmtYr, idDataGroup ) )
      {
         //assign calculate value
         DString strValue,oldValue;
         pPaymentsCalc->getField( ifds::MandAmtYrSysCalc, strValue, idDataGroup );
         getField(ifds::MandAmtYr,oldValue, idDataGroup );
         double dMandAmtYr = ( DSTCommonFunctions::convertToDouble( oldValue ) ); 
         double dMandAmtYrSys = ( DSTCommonFunctions::convertToDouble( strValue ) ); 
         if( dMandAmtYrSys != dMandAmtYr )
         {
            setFieldNoValidate(ifds::MandAmtYr, strValue, idDataGroup,true,true,true);
            setUpdatedFlag( ifds::MandAmtYr, idDataGroup, true );
         }
      }
   }  


//	if(getFieldStateFlags( DBR::MandAmtPay, idDataGroup ) & VALID )  //
   if( isEffectiveDateInCurrentYr( idDataGroup) != 2 ) //not future dated
   {
      DString strValue,oldValue;
	  if( pPaymentsCalc )
	  {
         pPaymentsCalc->getField( ifds::MandAmtPaySysCalc, strValue, idDataGroup );
	  }
      getField(ifds::MandAmtPay,oldValue, idDataGroup );
      double dMandAmt = ( DSTCommonFunctions::convertToDouble( oldValue ) ); 
      double dMandSys = ( DSTCommonFunctions::convertToDouble( strValue ) ); 
      if( dMandSys != dMandAmt )
      {
         setFieldNoValidate(ifds::MandAmtPay, strValue, idDataGroup,true,true,true);
         setUpdatedFlag( ifds::MandAmtPay, idDataGroup, true );
      }
   }

   DString strPayOption;
   getField(ifds::PayOption, strPayOption, idDataGroup);
   if( strPayOption == PAY_OPTION_PERCENT  )
      validatePreYrPercent ( idDataGroup );
   validateRRIFAmount( idDataGroup ); 
   validateNetAmount( idDataGroup );

//	if(getFieldStateFlags( DBR::MaxAmtYr, idDataGroup )  ) //Max. Amount Year


	// Incident #770827, 768775
	DString dstrOverrideUnusedMax;
	getField ( ifds::OverrideUnusedMax, dstrOverrideUnusedMax, idDataGroup );
	
	if ( dstrOverrideUnusedMax == I_("N") )
   {
      DString strValue,oldValue;
	  if( pPaymentsCalc )
	  {
         pPaymentsCalc->getField( ifds::MaxAmtYrSysCalc, strValue, idDataGroup );
	  }
      getField(ifds::MaxAmtYr,oldValue, idDataGroup );
      double dMaxAmt = ( DSTCommonFunctions::convertToDouble( oldValue ) ); 
      double dMaxSys = ( DSTCommonFunctions::convertToDouble( strValue ) ); 
      if( dMaxSys != dMaxAmt )
      {
         setField(ifds::MaxAmtYr, strValue, idDataGroup,true,true); // trig validation		
      }
   }

   // These 2 fields should be revalidated regardless of their validness.
   ValidateValueAgainstCalc( ifds::FedRate, ifds::FedRateSysCalc, idDataGroup );
   ValidateValueAgainstCalc( ifds::ProvRate, ifds::ProvRateSysCalc, idDataGroup );

   DString strValue;
   if( isEffectiveDateInCurrentYr( idDataGroup ) != 2 )
   { // if it is not future date 
	   if( pPaymentsCalc )
	  {
         pPaymentsCalc->getField( ifds::PayTerm, strValue, idDataGroup );
         setField(ifds::PayTerm, strValue, idDataGroup,true,true);
         pPaymentsCalc->getField( ifds::Factor, strValue, idDataGroup );
         setField(ifds::Factor, strValue, idDataGroup,true,true);
	  }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//ValidateAllocationList
//implemented by Yingbao
SEVERITY RRIF_LIF_LRIF_Info::ValidateAllocationList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateAllocationList" ));
   DString dstrStatus;
   getField(ifds::GoodBad,dstrStatus,idDataGroup,false);

   FromFundAllocList*   pAllocList;
   getFromFundAllocList( pAllocList, idDataGroup, false );
   if( pAllocList != NULL && dstrStatus == YES )
   {
      pAllocList->validateAll(idDataGroup);
   }
	DString dstrPayType;
	getField(ifds::RIFPayType,dstrPayType,idDataGroup, false );
	dstrPayType.strip().upperCase();

	if(dstrPayType == I_("T"))
	{

		ToFundAllocList*   pToAllocList;
		getToFundAllocList( pToAllocList, idDataGroup, false );
		if( pToAllocList != NULL && dstrStatus == YES )
		{
			pToAllocList->validateAll(idDataGroup);
		}
	}
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPreSetField" ));
   if( idField == ifds::EndOfMonth )
   {
      getField(ifds::EndOfMonth, _strOldMonthEnd, idDataGroup);
   }
   else if( idField == ifds::MonthIndicator )
   { //added by yingbao
      strValue.upperCase();
   }
   else if( idField == ifds::PayOption )
   {
      DString strOldValue;
      getField(idField,strOldValue,idDataGroup,bFormatted );
      DString strOldValue1(strOldValue);
      if( strValue != strOldValue && strValue == strOldValue1.upperCase() )
      {
         strValue = strOldValue;
      }
   }


   return(GETCURRENTHIGHESTSEVERITY( ));
};

//**************************************************************************************
// AddCopy
// yingbao
void RRIF_LIF_LRIF_Info::ModelOffer(RRIF_LIF_LRIF_Info *Model, const BFDataGroupId& idDataGroup)
{
   BFData *tmp = new BFData(ifds::DSTC0067_VWRepeat_Record);  //RRIF_INFO

   setAddCopy(true); 

   BFDataFieldIter dIter( *tmp );
   BFFieldId idField = ifds::NullFieldId;
   DString str;
   for( ;dIter; ++dIter )
   {
      idField = dIter().getId();
      
      if(idField == ifds::PayTypeDesc) continue;

	   if(idField != ifds::OrigPlanDeff)
	   {
	      Model->getField( idField, str, idDataGroup, false );
		   setField(idField, str, idDataGroup, false);
	   }
     
   };

   delete tmp;
   idField = ifds::MonthIndicator;
   Model->getField( idField, str, idDataGroup, false );
   setField(idField, str, idDataGroup, false);

   idField = ifds::Frequency;
   Model->getField( idField, str, idDataGroup, false );
   if(str != FREQ_WEEKLY || str != FREQ_BIWEEKLY )
   {
	   idField = ifds::DayOfWeek;
   	   setField(idField, I_("1"), idDataGroup, false);
   }
  
// copy from fund list
   FromFundAllocList* pModelAllocList = NULL,*pDestAllocList = NULL;
   Model->getFromFundAllocList( pModelAllocList, idDataGroup, false );

   if( pModelAllocList )
   {
      getFromFundAllocList( pDestAllocList, idDataGroup ); 

      pDestAllocList->modelOffer(pModelAllocList, idDataGroup);
   }
// copy to fund list
   ToFundAllocList* pModelToAllocList = NULL,*pDestToAllocList = NULL;
   Model->getToFundAllocList( pModelToAllocList, idDataGroup, false );

   if( pModelToAllocList )
   {
      getToFundAllocList( pDestToAllocList, idDataGroup ); 

      pDestToAllocList->modelOffer(pModelToAllocList, idDataGroup);
   }

   setAddCopy(); 

}
//*******************************************************************************
//yingbao March 27,2001
//
SEVERITY RRIF_LIF_LRIF_Info::validateCrossInstTransit(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateCrossInstTransit" ) );

   if ( HaveToCheckBankPara (idDataGroup))
   {
      DString strInstCode,
         strTransitNo;

      getField (ifds::InstCode, strInstCode, idDataGroup, false);
      getField (ifds::TransitNo, strTransitNo, idDataGroup, false);
      strInstCode.strip();
      strTransitNo.strip();

      if (strInstCode != NULL_STRING &&  strTransitNo != NULL_STRING)
      {
         if (FinancialInstitution::validateBankTransitNum(
            getWorkSession(), 
            I_("03"), //canadian bank
            strInstCode,
            strTransitNo) > WARNING)
         {
            ADDCONDITIONFROMFILE (CND::ERR_INSTCODE_TRANSITNO_NOT_EXIST);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//***********************************************************************************
//yingbao July 31, 2001
//

SEVERITY RRIF_LIF_LRIF_Info::setMonthsFrequencyByIndicator(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setMonths" ) );
   DString strMonthIndicator, strOldFreq, val;

   getField(ifds::Frequency, strOldFreq, idDataGroup, false);
   if( strOldFreq != FREQ_DAILY && strOldFreq != FREQ_WEEKLY && 
	   strOldFreq != FREQ_BIWEEKLY && strOldFreq != FREQ_SEMIMONTHLY )
   {
      getField(ifds::MonthIndicator, strMonthIndicator, idDataGroup, false);
      strMonthIndicator.strip().upperCase();
      assert(strMonthIndicator.length() == 12);
      const BFFieldId month[] = {ifds::January, ifds::February, ifds::March, ifds::April,
         ifds::May, ifds::June, ifds::July, ifds::August,
         ifds::September, ifds::October, ifds::November,ifds::December};
      for( int i=0; i<12;i++ )
      {
         val = strMonthIndicator.substr(i, 1);
         setField(month[i], val, idDataGroup, false);
      }

      if( getNoOfYes(strMonthIndicator) == 12 )
      {
         if( strOldFreq != FREQ_SEMIMONTHLY )
            setFieldNoValidate(ifds::Frequency, FREQ_MONTHLY, idDataGroup, false, true, true, false);
      }
      else
      {
         if( isAnnualy(strMonthIndicator) )
            setFieldNoValidate(ifds::Frequency, FREQ_ANNUALLY, idDataGroup, false, true, true, false);
         else if( isSemiAnnualy(strMonthIndicator) )
            setFieldNoValidate(ifds::Frequency, FREQ_SEMIANNUALLY, idDataGroup, false, true, true, false);
         else if( isQuarterly(strMonthIndicator) )
            setFieldNoValidate(ifds::Frequency, FREQ_QUARTERLY, idDataGroup, false, true, true, false);
         else
            setFieldNoValidate(ifds::Frequency, FREQ_OTHER, idDataGroup, false, true, true, false);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************************

bool RRIF_LIF_LRIF_Info::isAnnualy(const DString& strMonthIndicator)
{
   bool bRetVal = false;
   if( getNoOfYes(strMonthIndicator) == 1 )
   {
      int iPos;
      iPos = strMonthIndicator.find(I_("Y"));

      DString strTemp, strTemp1;
      strTemp = strMonthIndicator.substr(iPos, strMonthIndicator.length()-iPos);
      strTemp1 = strMonthIndicator.substr(0, iPos);
      strTemp += strTemp1;

      iPos = strTemp.find(I_("NNNNNNNNNNN"));

      if( iPos != DString::npos )
         bRetVal = true;
   }
   return(bRetVal);
}
//*****************************************************

bool RRIF_LIF_LRIF_Info::isSemiAnnualy(const DString& strMonthIndicator)
{
   bool bRetVal = false;
   if( getNoOfYes(strMonthIndicator) == 2 )
   {
      int iPos;
      iPos = strMonthIndicator.find(I_("Y"));

      DString strTemp, strTemp1;
      strTemp = strMonthIndicator.substr(iPos, strMonthIndicator.length()-iPos);
      strTemp1 = strMonthIndicator.substr(0, iPos);
      strTemp += strTemp1;

      while( true )
      {
         iPos = strTemp.find( I_( "Y" ) );
         if( iPos == DString::npos ) break;
         strTemp.replace( iPos, 1, BLANKSTRING );
      }

      if( strTemp.words() == 2 )
      {
         for( int i=0; i<2; i++ )
         {
            if( strTemp.word(i) != I_("NNNNN") )
               return(false);
         }
         bRetVal = true;
      }
   }
   return(bRetVal);
}
//****************************************************************************** 

bool RRIF_LIF_LRIF_Info::isQuarterly(const DString& strMonthIndicator)
{
   bool bRetVal = false;
   if( getNoOfYes(strMonthIndicator) == 4 )
   {
      int iPos;
      iPos = strMonthIndicator.find(I_("Y"));

      DString strTemp, strTemp1;
      strTemp = strMonthIndicator.substr(iPos, strMonthIndicator.length()-iPos);
      strTemp1 = strMonthIndicator.substr(0, iPos);
      strTemp += strTemp1;

      while( true )
      {
         iPos = strTemp.find( I_( "Y" ) );
         if( iPos == DString::npos ) break;
         strTemp.replace( iPos, 1, BLANKSTRING );
      }

      if( strTemp.words() == 4 )
      {
         for( int i=0; i<4; i++ )
         {
            if( strTemp.word(i) != I_("NN") )
               return(false);
         }
         bRetVal = true;
      }
   }
   return(bRetVal);
}


//****************************************************************************** 
int RRIF_LIF_LRIF_Info::getNoOfYes(const DString& strMonthIndicator)
{
   DString val;
   int nNoOfYes = 0;
   for( int i=0; i<12;i++ )
   {
      val = strMonthIndicator.substr(i, 1);
      if( val == YES )
         nNoOfYes++;
   }
   return(nNoOfYes);
}
//*******************************************************************************
// this function may not be necessarilly here, it is for fixing View problem
void RRIF_LIF_LRIF_Info::doPopulateField( const BFFieldId& idField, DString & strValue, bool formattedReturn ){

   if( idField == ifds::PayOption )
   {
      strValue = strValue.upperCase();
   }
}
//*********************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::ValidateTaxOnMinSuppFedAndProvTax(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateTaxOnMinSuppFedAndProvTax") );
   DString dstrTaxOnMin,dstrSuppFedTax,dstrSuppProvTax;
   getField(ifds::TaxOnMin,dstrTaxOnMin,idDataGroup,false);
   getField(ifds::SuppFedTax,dstrSuppFedTax,idDataGroup,false);
   getField(ifds::SuppProvTax,dstrSuppProvTax,idDataGroup,false);
   dstrTaxOnMin.strip();dstrSuppFedTax.strip();dstrSuppProvTax.strip();
   if( dstrTaxOnMin == YES && (dstrSuppFedTax == YES || dstrSuppProvTax == YES) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_TaxOnMin_SuppFedTax_SuppProvTax ); 
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************** 
SEVERITY RRIF_LIF_LRIF_Info::getErrMsg( const DString& dstrErrNum, long lErrConditionId, 
                                        long lWarnConditionId, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getErrMsg" ) );
   ErrMsgRulesList* pErrMsgRulesList = NULL;

   getMgmtCo().getErrMsgRulesList( pErrMsgRulesList );

   DString idiStr(NULL_STRING);
   if( pErrMsgRulesList )
      pErrMsgRulesList->getEWI( dstrErrNum, lErrConditionId, lWarnConditionId, idDataGroup, idiStr );

   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************** 

void RRIF_LIF_LRIF_Info::setAllocField(const BFFieldId& fromFieldID, const BFFieldId& toFieldID, const BFDataGroupId& idDataGroup)
{
   DString str;
   getField(fromFieldID, str, idDataGroup, false);

   FromFundAllocList *pFromFundAllocList = NULL;
   getFromFundAllocList( pFromFundAllocList , idDataGroup, false);
   if( pFromFundAllocList )
   {   
		pFromFundAllocList->setField(toFieldID, str, idDataGroup, false);
	}
	DString dstrPayType;
	getField(ifds::RIFPayType,dstrPayType,idDataGroup );
	dstrPayType.strip();
	if( dstrPayType == I_("T") )
	{
	   ToFundAllocList *pToFundAllocList = NULL;
		getToFundAllocList( pToFundAllocList , idDataGroup, false);
		if( pToFundAllocList )
		{	
			pToFundAllocList->setField(toFieldID, str, idDataGroup, false);
		}	
	}

}

//**********************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::validateAcctTo( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAcctTo") );
	DString dstrAcctFrom,dstrAcctTo,dstrPayType;
	getField(ifds::RIFPayType,dstrPayType,idDataGroup, false );
	dstrPayType.strip();
	getParent()->getParent()->getField(ifds::AccountNum,dstrAcctFrom,idDataGroup,false );
	dstrAcctFrom.strip().stripLeading('0');
	getField(ifds::AccountTo,dstrAcctTo,idDataGroup,false);
	dstrAcctTo.strip().stripLeading('0');

	if( dstrPayType == I_("T") )
	{		
		if( dstrAcctFrom == 	dstrAcctTo )
		{
		  ADDCONDITIONFROMFILE( CND::ERR_TO_ACCOUNT_CANNOT_BE_SAME_AS_FROM_ACCOUNT );
		  return (GETCURRENTHIGHESTSEVERITY());
		}		
		MFAccount::validateAccountNum(dstrAcctTo, getWorkSession() );

		/* Celia Zhand add at Sep 5, 2003
		 * PTS ticket 10021399 ( Rule missing issue )
		 * Validation for transfer between different taxtype account
		 */
		DString dstrTaxTypeFr, dstrTaxTypeTo, dstrTaxTypeFrForm, dstrTaxTypeToForm;
		bool bOkay = false;
		_pAccount->getField( ifds::TaxType, dstrTaxTypeFr, idDataGroup ); // get code
		_pAccount->getField( ifds::TaxType, dstrTaxTypeFrForm, idDataGroup, true ); // get description

		DString dstrToAccount;
		getField(ifds::AccountTo,dstrToAccount,idDataGroup,false);
		dstrToAccount.strip();
		MFAccount* pMFAccount = NULL;
		getWorkSession().getMFAccount( idDataGroup, dstrToAccount,pMFAccount );
		if( pMFAccount )
		{
			pMFAccount->getField( ifds::TaxType, dstrTaxTypeTo, idDataGroup ); // get code
			pMFAccount->getField( ifds::TaxType, dstrTaxTypeToForm, idDataGroup, true ); // get description

			TaxTypeRule *pTaxTypeRule = NULL;
            if ( pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
			{
				// search TaxTypeFr in TaxTypeTo list. If it exists, return true
				bOkay = pTaxTypeRule->validTransfer ( dstrTaxTypeFr, idDataGroup ); 
			}
		}
		if( !bOkay )
		{
			DString idiStr;
			addIDITagValue( idiStr, I_( "FROMTAX"), dstrTaxTypeFrForm );
			addIDITagValue( idiStr, I_( "TOTAX"), dstrTaxTypeToForm );
			ADDCONDITIONFROMFILEIDI( CND::ERR_TRANSFER_TAX_TYPE, idiStr  );
		}
	}
// there will be more business rules need to be implemented in the future
//yingbao Jan. 12, 2003

   return(GETCURRENTHIGHESTSEVERITY());
}
//********************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::validatePercent( const BFFieldId& idField,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validatePercent") );
	DString dstrPercent;
	getField(idField,dstrPercent,idDataGroup,false );
   double dPercent = DSTCommonFunctions::convertToDouble(dstrPercent);
   if( ( dPercent - 100 ) > 0.0000000001 || dPercent < 0.0000000001)
      ADDCONDITIONFROMFILE( CND::ERR_PRE_YR_PERCENT );

   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************

SEVERITY RRIF_LIF_LRIF_Info::validatePreYrPercent(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validatePreYrPercent" ) );
   DString dstrPreYrPercent, dstrMinPreYrPercent, dstrMaxPreYrPercent;
   getField(ifds::PreYrPercent,dstrPreYrPercent,idDataGroup, false );
   double dPreYrPercent = ( DSTCommonFunctions::convertToDouble( dstrPreYrPercent ) ); 
   double dMinPreYrPercent = 0.0;
   double dMaxPreYrPercent = 100.0;
   RRIF_LIF_LRIF_PaymentsCalculation *pPaymentsCalc;
   if( getPaymentsCalculation(pPaymentsCalc, idDataGroup ) <= WARNING && pPaymentsCalc )
   {
      pPaymentsCalc->getField(ifds::MinPrevYrBalPctSysCalc,dstrMinPreYrPercent,idDataGroup);
      dMinPreYrPercent = ( DSTCommonFunctions::convertToDouble( dstrMinPreYrPercent ) ); 
      pPaymentsCalc->getField(ifds::MaxPrevYrBalPctSysCalc,dstrMaxPreYrPercent,idDataGroup);
      dMaxPreYrPercent = ( DSTCommonFunctions::convertToDouble( dstrMaxPreYrPercent ) ); 
   }
   bool bAddCondition = false;
   if (( dPreYrPercent < dMinPreYrPercent ) || ( dPreYrPercent > dMaxPreYrPercent )) {
      DString idiStr;
	  DSTCommonFunctions::DisplayFormat( dstrMinPreYrPercent,ifds::MinPrevYrBalPctSysCalc );
	  DSTCommonFunctions::DisplayFormat( dstrMaxPreYrPercent,ifds::MaxPrevYrBalPctSysCalc );
      addIDITagValue( idiStr, MIN, dstrMinPreYrPercent );       
      addIDITagValue( idiStr, MAX, dstrMaxPreYrPercent );       
      ADDCONDITIONFROMFILEIDI( CND::ERR_PRE_PERCENT_IN_BETWEEN, idiStr );      
      bAddCondition = true;
   }

   SEVERITY sevRtn = GETCURRENTHIGHESTSEVERITY( );
   if( sevRtn >= WARNING && bAddCondition )
   {
      const BFFieldId &idField = ifds::PreYrPercent;
//      long lFlags  = getFieldStateFlags( idField, idDataGroup );
//      lFlags &= ~VALID; //clear valid; 
//      setFieldStateFlags(idField, idDataGroup,lFlags );
      setFieldValid( idField, idDataGroup, false );
      setCrossEditInvalid(idField, idDataGroup );

      CONDITIONVECTOR* _pCond;

      getFieldConditionVector(idField,idDataGroup,_pCond );
      if( _pCond == NULL )
         _pCond = new CONDITIONVECTOR;
      int count = CURRENTCONDITIONCOUNT( );
      _pCond->push_back(  new Condition( *GETCURRENTCONDITION( --count )) );           
      setFieldConditionVector(idField, idDataGroup,_pCond );
      notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::getBankInstructionsList(
   RRIFBankInstructionsList *&pRRIFBankInstructionsList, 
   const BFDataGroupId& idDataGroup, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBankInstructionsList"));

   //the bank instructions list can be created only if the 
   //RRIF payment method is EFT
   if (isEFT(idDataGroup))
   {
      BFObjectKey objKey(I_("RRIF_LIF_LRIF_BankInstructionsList"), idDataGroup, 
         OBJ_ACTIVITY_NONE, OBJ_TYPE_NONE);

      pRRIFBankInstructionsList = NULL;
      pRRIFBankInstructionsList = 
         dynamic_cast<RRIFBankInstructionsList *>(findObject(objKey));
      if (!pRRIFBankInstructionsList && bCreate)
      {
         pRRIFBankInstructionsList = new RRIFBankInstructionsList(*this);
         if (pRRIFBankInstructionsList)
         {
            SEVERITY severity = isNew() ? 
               pRRIFBankInstructionsList->initNew(_strAccountNum, idDataGroup) : 
               pRRIFBankInstructionsList->init(_strAccountNum, idDataGroup);

            if (severity <= WARNING)
            {
				BFObjIter iter (*pRRIFBankInstructionsList, idDataGroup);
				if (!iter.end()) //the bank list has only one item
				{
					iter.getObject()->setField (ifds::PayMethod, NULL_STRING, idDataGroup, false);
					iter.getObject()->setField (ifds::ACHProcessor, NULL_STRING, idDataGroup, false);
				}
				setObject(objKey, pRRIFBankInstructionsList);
            }
            else
            {
               delete pRRIFBankInstructionsList;
               pRRIFBankInstructionsList = NULL;
            }
         }
      }
   } 
   return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::validateTransfer( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateTransfer"));
	DString dstrPayType,dstrStatus;
	getField(ifds::RIFPayType,dstrPayType,idDataGroup );
	dstrPayType.strip().upperCase();

	getField(ifds::GoodBad,dstrStatus,idDataGroup,false );
	dstrStatus.strip().upperCase();
	if( dstrPayType != I_("T")  || dstrStatus == NO ) // we don't need to validate for bad record
	{
		return NO_CONDITION;
	}
	DString dstrToAccount;
	getField(ifds::AccountTo,dstrToAccount,idDataGroup,false);
	dstrToAccount.strip();
   MFAccount* pMFAccount = NULL;
	getWorkSession().getMFAccount( idDataGroup, dstrToAccount,pMFAccount );
	if( pMFAccount )
	{
     	FromFundAllocList* pFromFundAllocList = NULL;
		getFromFundAllocList( pFromFundAllocList, idDataGroup, false);
		if(!pFromFundAllocList )
		{
			return NO_CONDITION;
		}
		ToFundAllocList* pToFundAllocList = NULL;
		getToFundAllocList( pToFundAllocList, idDataGroup, false);
		BFObjIter* iterTo;
		if(pToFundAllocList != NULL )
		{
			iterTo = new BFObjIter( *pToFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			int iNum = iterTo->getNumberOfItemsInList();
			
			if( pToFundAllocList == NULL || iNum == 0 || iNum == 1 && iterTo->isDummy() )
			{
				 DString dstrEffectiveDate;
				 getField(ifds::EffectiveFrom,dstrEffectiveDate,idDataGroup,false);
				 dstrEffectiveDate.strip();
				 BFObjIter iter( *pFromFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
				 while(!iter.end() )
				 {
					DString dstrFundCode,dstrClassCode;
					iter.getObject()->getField(ifds::FundCode,dstrFundCode,idDataGroup,false );
					iter.getObject()->getField(ifds::ClassCode,dstrClassCode,idDataGroup,false );
					SEVERITY sev = pMFAccount->canTradeFundClass(dstrFundCode,dstrClassCode,EX_FER_IN_CODE,dstrEffectiveDate,idDataGroup );
					if( sev > WARNING )
					{
						CLEARCONDITIONS();
						DString idiStr;
						addIDITagValue( idiStr, I_("FUND"), dstrFundCode );
						addIDITagValue( idiStr, I_("CLASS"), dstrClassCode );
						addIDITagValue( idiStr, I_("ACCOUNT"), dstrToAccount );
						ADDCONDITIONFROMFILEIDI( CND::ERR_TRANSFER_TO_ACCOUNT_IS_NOT_ALLOWED, idiStr);   					
					}
					++iter;			 
				 }
			}
		}
		delete iterTo;
	}

   SEVERITY sevRtn = GETCURRENTHIGHESTSEVERITY( );
   if( sevRtn >= WARNING )
   {
      CONDITIONVECTOR* _pCond;

      getFieldConditionVector(ifds::AccountTo,idDataGroup,_pCond );
      if( _pCond == NULL )
         _pCond = new CONDITIONVECTOR;
      int count = CURRENTCONDITIONCOUNT( );
      Condition   *c = NULL;
      for( int i = 0; i < count; i++ )
      {
         c = new Condition( *GETCURRENTCONDITION( i ));
         _pCond->push_back( c );
      };
      setFieldConditionVector(ifds::AccountTo, idDataGroup,_pCond );
      notifyObservers( ifds::AccountTo, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ) );
   }


  return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY  RRIF_LIF_LRIF_Info::validateEffectiveStopMonthIndicator(  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEffectiveStopMonthIndicator" ) );

      DString strEffectiveDate;
      DString strStopDate;
      getField(ifds::StopDate, strStopDate, idDataGroup,false);
      getField(ifds::EffectiveFrom, strEffectiveDate, idDataGroup,false);
      int stopDateYear = extractFieldFromDate( strStopDate );
      int effectiveDateYear = extractFieldFromDate( strEffectiveDate );

      if( ( DSTCommonFunctions::CompareDates( strStopDate,strEffectiveDate ) == DSTCommonFunctions::SECOND_EARLIER 
            && stopDateYear == effectiveDateYear ) ) 
		{
			DString strCurrBusDate,dstrStartDate = strEffectiveDate ;
			getWorkSession().getOption( ifds::CurrBusDate, strCurrBusDate, idDataGroup, false );
         if( DSTCommonFunctions:: IsDateBetween( strEffectiveDate,strStopDate,strCurrBusDate ) )
			{			
				dstrStartDate = strCurrBusDate;
			}	              
			int iStartMonth  = extractFieldFromDate( dstrStartDate, I_("MM") );
			int iStopMonth = extractFieldFromDate( strStopDate, I_("MM") );

		   const BFFieldId monthID[] = {ifds::January, ifds::February, ifds::March, ifds::April, ifds::May, ifds::June, 
			ifds::July, ifds::August, ifds::September, ifds::October, ifds::November,ifds::December};
			if( iStopMonth == iStartMonth ) // at same month
			{
				DString dstrMonthPay;
				getField(monthID[iStopMonth - 1 ],dstrMonthPay,idDataGroup,false );
				if( dstrMonthPay.strip().upperCase() == NO )
				{
					// add condtion here
					DString idiStr;
					DString dstrMonthName = monthID[iStopMonth - 1].getName( );
					addIDITagValue( idiStr, I_("MONTH"), dstrMonthName );       
					ADDCONDITIONFROMFILEIDI( CND::ERR_RRIF_ONE_MONTH_INDICATE_MISSING, idiStr );
				}						
			}
			else if( iStopMonth > iStartMonth )
			{
				DString dstrMonthPay1,dstrMonthPay = NULL_STRING;
				for( int i = iStartMonth; i<= iStopMonth; i++ )
				{
					getField(monthID[ i-1 ],dstrMonthPay1,idDataGroup,false );
					dstrMonthPay1.strip().upperCase();
					dstrMonthPay += dstrMonthPay1;				
				}
				if( dstrMonthPay.find(YES) == DString::npos )
				{
					//addcondition here.
					DString idiStr;
					addIDITagValue( idiStr, I_( "MONTH1" ), monthID[iStartMonth - 1].getName( ) );
					addIDITagValue( idiStr, I_( "MONTH2" ), monthID[iStopMonth - 1].getName( ) );					
					ADDCONDITIONFROMFILEIDI( CND::ERR_RRIF_ONE_MONTH_INDICATE_MISSING2, idiStr );
				}			
			}
		}
   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************
bool RRIF_LIF_LRIF_Info::isOverrideUnusedAmtReadOnly( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isOverrideUnusedAmtReadOnly" ) );
	
	DString dstrIsRRIFOverrUnusedAmtApplic;
	getParent()->getField( ifds::isRRIFOverrUnusedAmtApplic, dstrIsRRIFOverrUnusedAmtApplic, idDataGroup );
	dstrIsRRIFOverrUnusedAmtApplic.stripAll().upperCase();	

	return dstrIsRRIFOverrUnusedAmtApplic != I_( "Y" );
}

//**********************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::setEOMandMonthIndicator( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setEOMandMonthIndicator" ) );
	
    const BFFieldId monthID[] = {ifds::January, ifds::February, ifds::March, ifds::April, ifds::May, ifds::June, 
         ifds::July, ifds::August, ifds::September, ifds::October, ifds::November,ifds::December};
  
     for( int index = 0; index < 12 ; index++ )
     {
        setFieldNoValidate( monthID[index], YES, idDataGroup );         
     };

     setFieldNoValidate( ifds::MonthIndicator, I_("YYYYYYYYYYYY"),  idDataGroup, true, true, true ); // Notify the observers.
     setFieldNoValidate( ifds::EndOfMonth, NO, idDataGroup ); 
	
	return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::validateSpouseDOB( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateSpouseDOB" ) );
	
    DString	spouseBirthDate;

	getField (ifds::SpouseBirth , spouseBirthDate, idDataGroup);

	spouseBirthDate.strip();

	DString strTaxType;
    _pAccount->getField(ifds::TaxType, strTaxType, idDataGroup);

    DString strBirthDate;
    _pAccount->getDofBirthofOwnerSeq01( strBirthDate, idDataGroup );
    strBirthDate.strip();

	DString	dstrDate;
    DSTCommonFunctions::getFormat12319999Date(dstrDate);

	bool bBirthDate = strBirthDate == NULL_STRING || strBirthDate == dstrDate ? true : false;
	bool bSpouseBirthDate = spouseBirthDate == NULL_STRING || spouseBirthDate == dstrDate ? true : false;

    //spouse birthday must be entered if shareholder's birthday is unknown
    if (bBirthDate && bSpouseBirthDate && ( getWorkSession ().isLIFLike (strTaxType) ||  strTaxType == RRIF_TAX_TYPE ||  
		                                    strTaxType == PRIF_TAX_TYPE || strTaxType == LRIF_TAX_TYPE))
    {
		getErrMsg (I_("336"), 
                   CND::ERR_RIF_NO_SHAREHOLDER_BIRTHDATE, 
                   CND::ERR_RIF_WARN_NO_SHAREHOLDER_BIRTHDATE, 
                   idDataGroup ); 
    } 
	
	return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************

SEVERITY RRIF_LIF_LRIF_Info::getPaymentsCalculation( RRIF_LIF_LRIF_PaymentsCalculation *& pPaymentsCalc, 
	                                                 const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getPaymentsCalculation" ) );
   DString str;
   bool bAddMode = isNew()? true:false;   

   DString strKey = I_("PaymentsCalculation");
   if( buildPaymentCalcKey( strKey, idDataGroup ) <= WARNING ) 
   {
		BFObjectKey objKey( strKey, idDataGroup, OBJ_ACTIVITY_NONE );
		pPaymentsCalc = dynamic_cast< RRIF_LIF_LRIF_PaymentsCalculation * >( findObject( objKey ) );

		if( !pPaymentsCalc )
		{
			pPaymentsCalc = new RRIF_LIF_LRIF_PaymentsCalculation( *this );

			if(pPaymentsCalc->init( _strAccountNum, 
									 I_("2"),//strCallNum, 
									 this, 
									 idDataGroup,
									 false,//bFirstCall,
									 bAddMode ) <= WARNING )
			{
				setObject( objKey, pPaymentsCalc );
				//always refresh CalcMandYr and CalcMaxYr fields with the values returned by the view
				DString str;
				pPaymentsCalc->getField(ifds::CalcMandYr, str, idDataGroup);
				setFieldNoValidate(ifds::CalcMandYr, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::MaxAmtYrSysCalc, str, idDataGroup);
				setFieldNoValidate(ifds::MaxAmtYr, str, idDataGroup,true,true,true);
				if( isEffectiveDateInCurrentYr( idDataGroup ) == 2 )
				{ //future dated
					setFieldNoValidate(ifds::CalcMaxYr, I_("0"), idDataGroup,true,true,true);
				}
				else
				{
					pPaymentsCalc->getField(ifds::CalcMaxYr, str, idDataGroup);
					setFieldNoValidate(ifds::CalcMaxYr, str, idDataGroup,true,true,true);
				}
			}
			else
			{
				delete pPaymentsCalc;
				pPaymentsCalc = NULL;
			}
		}
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::getOrigPlanDeffApplied(DString &dstrOrigPlanDeffApplied,
                                                    const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getOrigPlanDeffApplied" ) );
   DString str;
   bool bAddMode = isNew()? true:false;   

   RRIF_LIF_LRIF_PaymentsCalculation *pPaymentsCalc = new RRIF_LIF_LRIF_PaymentsCalculation( *this );

   if( pPaymentsCalc->init( _strAccountNum, 
      I_("2"),//strCallNum, 
      this, 
      idDataGroup,
      false,//bFirstCall,
      bAddMode ) <= WARNING )
   {
      pPaymentsCalc->getField(ifds::OrigPlanDeffApplied, dstrOrigPlanDeffApplied, idDataGroup, false);
      dstrOrigPlanDeffApplied.strip().upperCase();     
   }

   delete pPaymentsCalc;
   pPaymentsCalc = NULL;
   
   return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************

SEVERITY RRIF_LIF_LRIF_Info::getPaymentsCalculationForDefaultValues( RRIF_LIF_LRIF_PaymentsCalculation *& pPaymentsCalc, 
	                                                 const BFDataGroupId& idDataGroup, const DString& strCallNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getPaymentsCalculationForDefaultValues" ) );
   DString str;
   bool bAddMode = isNew()? true:false;   

   DString strKey = I_("PaymentsCalculation");
   if( buildPaymentCalcKey( strKey, idDataGroup ) <= WARNING ) 
   {
		BFObjectKey objKey( strKey, idDataGroup, OBJ_ACTIVITY_NONE );
		pPaymentsCalc = dynamic_cast< RRIF_LIF_LRIF_PaymentsCalculation * >( findObject( objKey ) );

		if( !pPaymentsCalc )
		{
			pPaymentsCalc = new RRIF_LIF_LRIF_PaymentsCalculation( *this );

			if( pPaymentsCalc->init( _strAccountNum, 
									 strCallNum, 
									 this, 
									 idDataGroup,
									 true,//bFirstCall
									 bAddMode ) <= WARNING )
			{
				setObject( objKey, pPaymentsCalc );		
				DString str;
				pPaymentsCalc->getField(ifds::CalcMandYr, str, idDataGroup);
				setFieldNoValidate(ifds::CalcMandYr, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::CalcMaxYr, str, idDataGroup);
				setFieldNoValidate(ifds::CalcMaxYr, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::PayTerm, str, idDataGroup);
				setFieldNoValidate(ifds::PayTerm, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::Factor, str, idDataGroup);
				setFieldNoValidate(ifds::Factor, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::PYEPlanValue, str, idDataGroup);
				setFieldNoValidate(ifds::PYEPlanValue, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::NowPlanValue, str, idDataGroup);
				setFieldNoValidate(ifds::NowPlanValue, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::MandAmtYrSysCalc, str, idDataGroup);
				setFieldNoValidate(ifds::MandAmtYr, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::MaxAmtYrSysCalc, str, idDataGroup);
				setFieldNoValidate(ifds::MaxAmtYr, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::MandAmtPaySysCalc, str, idDataGroup);      
				setFieldNoValidate(ifds::MandAmtPay, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::AmountSysCalc, str, idDataGroup);
				setFieldNoValidate(ifds::RRIFAmount, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::ProvRateSysCalc, str, idDataGroup);
				setFieldNoValidate(ifds::ProvRate, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::FedRateSysCalc, str, idDataGroup);
				setFieldNoValidate(ifds::FedRate, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField(ifds::NetAmountSysCalc, str, idDataGroup);
				setFieldNoValidate(ifds::NetAmt, str, idDataGroup,true,true,true);
				pPaymentsCalc->getField( ifds::PYUnusedMaxSysCalc, str, idDataGroup );
				setFieldNoValidate( ifds::PYUnusedMax, str, idDataGroup, true, true, true);
			}
			else
			{
				delete pPaymentsCalc;
				pPaymentsCalc = NULL;
			}
		}
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY RRIF_LIF_LRIF_Info::buildPaymentCalcKey( DString &dstrKey, const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "buildPaymentCalcKey" ) );

   //the following fields should be part of the key   
   
   // Noom [Apr 7, 2011]
   // SuppFedTax and SuppProvTax should be included, as per fix for IN#2395598. 
   // These field are commentted out as the incident is excluded from Release 11.4.
   const BFFieldId keyFields[]=
   {
	  ifds::GrossNetMethod,
      ifds::RRIFAmount,
      ifds::NetAmt,
      ifds::MaxAmtYr,
      //ifds::MandAmtPay,
      ifds::MandAmtYr, 
	  //ifds::SuppFedTax,
      ifds::FedRate,
      ifds::FedRatePUD,
      ifds::PayOption,
	  //ifds::SuppProvTax,
      ifds::ProvRate,
      ifds::ProvRatePUD,
      ifds::TaxOnMin,
      //ifds::PreYrPercent,
      ifds::SpouseBirth,      
	  ifds::OverrideUnusedMax,
	  ifds::PYUnusedMax,
	  ifds::Frequency,
	  ifds::MonthIndicator,
      ifds::NullFieldId
   };

   int i = 0;
   DString str;

   BFFieldId idField = keyFields[0];
   do
   {
	  idField = keyFields[i++];
	  getField( idField, str, idDataGroup, true );
	  dstrKey+= I_("_"); 
      dstrKey += str;            	  
   }
   while( idField != ifds::NullFieldId );
   
   return GETCURRENTHIGHESTSEVERITY();

}

/******************************************************************************
The logic:

There are 3 possible options in GrossNetMethod dropdown:
1.  Gross
2.  Net
3.  Net of Fees

The actual options in GrossNetMethod dropdown changes When the PayOption/RIFPayType is set/change based on the logic below:


if RIFPayType is transfer

	set GrossNetMethod to Gross and GrossNetMethod will be read only.

if RIFPayType is not transfer, set GrossNetMethod to NOT read only

	if Net of Fee is effective
	
		GrossNetMethod drop down should contain all 3 options
		if pay option is MIN or MAX
		
			default GrossNetMethod to Net of Fees
		otherwise
			default GrossNetMethod to Gross
		
	otherwise
		GrossNetMethod drop down should contain options 1 and 2
		default GrossNetMethod to Gross
		*/
void  RRIF_LIF_LRIF_Info::setGrossNetMethod(const BFDataGroupId& idDataGroup, bool bIsInit)
{
	 DString dstrNetOfFeesDate = NULL_STRING;
    DString dstrEffectiveDate = NULL_STRING;
    DString dstrAcctNumber    = NULL_STRING;
    DString dstrDSCFeeLevel   = NULL_STRING;
    MFAccount *pMFAccount     = NULL;

    // check net of fees date
    getWorkSession().getOption( ifds::NetOfFeesDate, dstrNetOfFeesDate, idDataGroup, false );
    getField(ifds::EffectiveFrom, dstrEffectiveDate, idDataGroup);

    // get account number
    getParent()->getParent()->getField(ifds::AccountNum, dstrAcctNumber, idDataGroup);
    dstrAcctNumber.stripLeading( '0' ).strip();

    if ( !dstrAcctNumber.empty() && 
            getWorkSession().getMFAccount(idDataGroup, dstrAcctNumber, pMFAccount) <= WARNING && 
            pMFAccount 
        )
    {
        pMFAccount->getField(ifds::DSCFeeLevel, dstrDSCFeeLevel, idDataGroup);
    }
	
	DString dstrRIFPayType = NULL_STRING;
	getField(ifds::RIFPayType, dstrRIFPayType, idDataGroup, false);

	if(dstrRIFPayType == I_("T"))
	{
		setFieldNoValidate( ifds::GrossNetMethod, GROSS, idDataGroup,false,true,true);
		setFieldReadOnly( ifds::GrossNetMethod, idDataGroup, true );
	}
	else
	{
		setFieldReadOnly( ifds::GrossNetMethod, idDataGroup, false );
		if ( DSTCommonFunctions::CompareDates( dstrNetOfFeesDate,dstrEffectiveDate ) == DSTCommonFunctions::SECOND_EARLIER &&
			( dstrDSCFeeLevel != NULL_STRING ) && !dstrDSCFeeLevel.empty() && ( I_("0") == dstrDSCFeeLevel ) )
		{
			setFieldSubstituteValues (ifds::GrossNetMethod, idDataGroup, ifds::GrossNetMethod2);
			if(bIsInit)
			{
				setFieldNoValidate( ifds::GrossNetMethod, GROSS, idDataGroup,false,true,true);
			}
			else
			{
				DString dstrGrossNetMethod;
				getField(ifds::GrossNetMethod, dstrGrossNetMethod, idDataGroup, false);
				if( dstrGrossNetMethod == NET_OF_FEES ) //Net of Fees is unavailable
					//This is invalid data, validate it!!
					setFieldNoValidate( ifds::GrossNetMethod, NULL_STRING, idDataGroup,false,false,true);
			}
		}
		else
		{
			setFieldSubstituteValues (ifds::GrossNetMethod, idDataGroup, ifds::GrossNetMethod);

			DString   strValue = NULL_STRING;
			getField( ifds::PayOption , strValue, idDataGroup );
			DString defaultGrossNetMethod = (strValue == PAY_OPTION_MINIMUM || strValue == PAY_OPTION_MAXIMUM)?
				NET_OF_FEES : GROSS;
			if(bIsInit)
			{
				setFieldNoValidate( ifds::GrossNetMethod, defaultGrossNetMethod, idDataGroup,false,true,true);
			}
		}
	}
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::populatedOrigPlanDeffApplied(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "populatedOrigPlanDeffApplied" ) );

	// call 130 for existing to refresh field and for new record

	DString dstrOrigPlanDeffApplied = NULL_STRING;	
	if( getOrigPlanDeffApplied(dstrOrigPlanDeffApplied, idDataGroup ) <= WARNING )
	{
	 //  pPaymentsCalc->getField(ifds::OrigPlanDeffApplied, dstrOrigPlanDeffApplied, idDataGroup, false);
		//dstrOrigPlanDeffApplied.strip().upperCase();	
		// set field from child to parent
		setFieldNoValidate( ifds::OrigPlanDeffApplied, 
							     dstrOrigPlanDeffApplied, 
							     idDataGroup, 
							     false,   // format
                          true,    // value from back-end always valid
							     false,   // side effect
                          true);   // apply related change	 
	}

   //bIsApplied = dstrOrigPlanDeffApplied == I_("Y")? true:false;

   //return bIsApplied;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RRIF_LIF_LRIF_Info::setInitExistingFlag(bool bFlag)
{
   _bInitExisting = bFlag;
}

//******************************************************************************
void RRIF_LIF_LRIF_Info::doReset( const BFDataGroupId& idDataGroup )
{
   // if the original plan effective date is modified by the system
   // fields should be reset while the screen closed but doesn't delete cbo object.
   DString dstrOrigPlanDeff, dstrOrigPlanDeffApplied;
   getField(ifds::OrigPlanDeff, dstrOrigPlanDeff, BF::HOST, false);
   getField(ifds::OrigPlanDeffApplied, dstrOrigPlanDeffApplied, BF::HOST, false);
   dstrOrigPlanDeffApplied.strip().upperCase();

   setFieldNoValidate(ifds::OrigPlanDeff, dstrOrigPlanDeff, idDataGroup, false, true, false, false);
   setFieldNoValidate(ifds::OrigPlanDeffApplied, dstrOrigPlanDeffApplied, idDataGroup, false, true, false, false);
}
//******************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::loadBusinessTypeSubslist( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,CLASSNAME, I_("loadBusinessTypeSubslist"));
   //P0186486_FN15_The Source of Funds
   DString sourceOfFundApp;

   getWorkSession().getOption(ifds::SourceOfFundApp, sourceOfFundApp, idDataGroup, false);
   sourceOfFundApp.strip().upperCase();

   if(sourceOfFundApp == I_("Y")) 
   {
      DString SrcOfFunds_IA_RIF_List; 
      getWorkSession().getOption(ifds::SrcOfFunds_IA_RIF, SrcOfFunds_IA_RIF_List, idDataGroup, false);
      SrcOfFunds_IA_RIF_List.strip().upperCase();
      if(!SrcOfFunds_IA_RIF_List.empty())
      {
         replaceSubstitutionList(SrcOfFunds_IA_RIF_List,
            ifds::SrcOfFunds_IA, 
            ifds::RRIFSrcOfFund, idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}
//*******************************************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::sourceOfFundRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,CLASSNAME, I_("sourceOfFundRelatedChanges"));
   //P0186486_FN15_The Source of Funds

   DString rrifSrcOfFund;
   getField(ifds::RRIFSrcOfFund, rrifSrcOfFund, idDataGroup, false); 
   rrifSrcOfFund.stripAll().upperCase();

   if( !rrifSrcOfFund.empty() && 
      getWorkSession ().isSrcOfFundRequired(rrifSrcOfFund, idDataGroup))
   {
         setFieldRequired (ifds::RIFPayType, idDataGroup, true);
         setValidFlag ( ifds::RIFPayType, idDataGroup, false ); 
      }
      else
      {
         setFieldRequired (ifds::RIFPayType, idDataGroup, false);
         setValidFlag ( ifds::RIFPayType, idDataGroup, true ); 
      }
   return GETCURRENTHIGHESTSEVERITY(); 
}
//****************************************************
void RRIF_LIF_LRIF_Info::ValidateSourceOfAccount(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateSourceOfAccount" ) );

   //P0186486_FN15_The Source of Funds
   DString srcOfAcct;
   getField(ifds::RRIFSrcOfAcct, srcOfAcct, idDataGroup, false); 

   DString srcOfFund;
   getField(ifds::RRIFSrcOfFund, srcOfFund, idDataGroup, false);

   if( !srcOfFund.empty() && 
      srcOfAcct.empty() &&
      getWorkSession ().isSrcOfFundRequired(srcOfFund, idDataGroup))
   {
      getErrMsg (IFASTERR::REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND, 
         CND::ERR_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND, 
         CND::WARN_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND, 
         idDataGroup);
   }
   
}

SEVERITY RRIF_LIF_LRIF_Info::getNetOfFeesApplicable(DString &dstrNetOfFees, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getNetOfFeesApplicable" ) );

	GMWBValidation *pGMWBValidation = NULL;
		
	DString dstrAccountNum;
	DString dstrValidateType = I_("RRIF");
	DString dstrEffectiveDate;
	DString dstrStopDate;
	DString dstrTransNum = I_("R");
	DString dstrFundCode ;
	DString dstrClassCode;
	DString dstrPayOption;
	DString dstrRecId;
	DString dstrRunMode = isNew () ? I_("A") : I_("M");

	getParent ()->getParent ()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false );
	getField (ifds::EffectiveFrom, dstrEffectiveDate, idDataGroup, false );
	getField (ifds::StopDate, dstrStopDate, idDataGroup, false );
	getField (ifds::PayOption, dstrPayOption, idDataGroup, false );
	getField (ifds::RIFId, dstrRecId, idDataGroup, false );
	
	dstrAccountNum.strip ();
	dstrValidateType.strip ();
	dstrEffectiveDate.strip ();
	dstrStopDate.strip ();
	dstrTransNum.strip ();
	dstrPayOption.strip ();
	dstrRecId.strip ();

   GMWBValidation rGMWBValidation(*this);
   if(rGMWBValidation.init (dstrAccountNum, dstrValidateType, dstrTransNum, dstrFundCode,
								    dstrClassCode, dstrEffectiveDate, dstrStopDate, dstrPayOption,
									 dstrRecId, dstrRunMode) <= WARNING)
   {
      rGMWBValidation.getField(ifds::NetOfFeesFlag, dstrNetOfFees, idDataGroup, false);
	}


   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************
SEVERITY RRIF_LIF_LRIF_Info::validateGMWB (const DString &fundCode, const DString &classCode, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateGMWB" ) );

	GMWBValidation *pGMWBValidation = NULL;
		
	DString dstrAccountNum;
	DString dstrValidateType = I_("RRIF");
	DString dstrEffectiveDate;
	DString dstrStopDate;
	DString dstrTransNum = I_("R");
	DString dstrFundCode (fundCode);
	DString dstrClassCode (classCode);
	DString dstrPayOption;
	DString dstrRecId;
	DString dstrRunMode = isNew () ? I_("A") : I_("M");

	getParent ()->getParent ()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false );
	getField (ifds::EffectiveFrom, dstrEffectiveDate, idDataGroup, false );
	getField (ifds::StopDate, dstrStopDate, idDataGroup, false );
	getField (ifds::PayOption, dstrPayOption, idDataGroup, false );
	getField (ifds::RIFId, dstrRecId, idDataGroup, false );
	
	dstrAccountNum.strip ();
	dstrValidateType.strip ();
	dstrEffectiveDate.strip ();
	dstrStopDate.strip ();
	dstrTransNum.strip ();
	dstrFundCode.strip ();
	dstrClassCode.strip ();
	dstrPayOption.strip ();
	dstrRecId.strip ();

	if (!dstrFundCode.empty () && !dstrClassCode.empty ())
	{
		DString strKey;

		GMWBValidation::buildKey (dstrAccountNum,
								  dstrValidateType,
								  dstrTransNum,
								  dstrFundCode,
								  dstrClassCode,
								  dstrEffectiveDate,
								  dstrStopDate,
								  dstrPayOption,
								  dstrRecId,
								  dstrRunMode,
								  strKey);

		pGMWBValidation = dynamic_cast<GMWBValidation *> (BFCBO::getObject (strKey, idDataGroup));

		if (!pGMWBValidation)
		{
			pGMWBValidation = new GMWBValidation (*this);
			
			if (pGMWBValidation->init (	dstrAccountNum,
										dstrValidateType,
										dstrTransNum,
										dstrFundCode,
										dstrClassCode,
										dstrEffectiveDate,
										dstrStopDate,
										dstrPayOption,
										dstrRecId,
										dstrRunMode) <= WARNING)
			{
				setObject (pGMWBValidation,  strKey, OBJ_ACTIVITY_NONE,  idDataGroup);
			}
			else
			{
				delete pGMWBValidation;
				pGMWBValidation = NULL;
			}
		}
	}

	if (pGMWBValidation)
	{
		pGMWBValidation-> validateGMWB (dstrFundCode, dstrClassCode, idDataGroup);
	}
	
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIF_LIF_LRIF_Info.cpp-arc  $
 * 
 *    Rev 1.162   Jun 29 2012 09:40:06   if991250
 * Removing EWA Pay option
 * 
 *    Rev 1.161   Jun 28 2012 11:41:44   if991250
 * Adding lsideEffect=true to the amount setFields
 * 
 *    Rev 1.160   Jun 27 2012 12:30:46   if991250
 * IN2981340 : RRIF
 * 
 *    Rev 1.159   May 14 2012 15:39:02   jankovii
 * P0186481FN07-GWA LWA Payment Options for SWP RRIF.
 * 
 *    Rev 1.158   May 11 2012 13:51:30   jankovii
 * P0186481 FN07 - GWA LWA Payment Options for SWP RRIF
 * 
 *    Rev 1.157   May 04 2012 11:04:28   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.156   Apr 24 2012 23:47:56   panatcha
 * removed unused field
 * 
 *    Rev 1.155   Apr 23 2012 09:35:06   kitticha
 * P0186486_FN15_The Source of Funds - Fixed 12.4 build error.
 * 
 *    Rev 1.154   Apr 20 2012 05:56:16   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.153   Apr 20 2012 04:02:18   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.152   Mar 02 2012 07:29:58   panatcha
 * IN2866702 : fix the issue relating to the update of the PYE 
 * 
 *    Rev 1.151   Feb 13 2012 04:21:46   panatcha
 * P0186486_FN03 - RRIF Annuities
 * 
 *    Rev 1.150   Oct 25 2011 05:04:16   wutipong
 * IN2704378 - Paytype X is not allowed for RRIF account.
 * 
 *    Rev 1.149   Apr 07 2011 10:35:34   wutipong
 * Fix of IN#2395598 is commented out, as the incident is excluded from Rel 11.4.
 * 
 *    Rev 1.148   Mar 02 2011 08:43:24   wutipong
 * IN1970273 - RIF/LIF Tax overide in Desktop
 * 
 *    Rev 1.147   Feb 25 2011 09:13:42   wutipong
 * IN#2395598 - RRIF payment info not correctly detailed for Net of fee functionality.
 * 
 *    Rev 1.146   Jan 21 2011 12:16:54   dchatcha
 * Synch up: IN# 2393765 - Major alert for Mifprod at 19:06 RTS Error 9.
 * 
 *    Rev 1.145   Jan 19 2011 03:36:58   wutipong
 * IN2253366 The ‘Gross/Net Pretax’ field in RRIF payment screen is being updated incorrectly
 * 
 *    Rev 1.144   Oct 04 2010 06:36:22   kitticha
 * PET0168176 FN01 Locked In Product Changes.
 * 
 *    Rev 1.143   Jul 21 2010 08:34:06   kitticha
 * PET0168176 FN01 - Locked In Product.
 * 
 *    Rev 1.142   May 26 2010 13:19:24   yingz
 * remove conflict/duplicated logic for incident 1885614
 * 
 *    Rev 1.141   May 21 2010 09:51:44   yingz
 * fix incident 1885614
 * 
 *    Rev 1.139   Sep 23 2009 02:47:50   dchatcha
 * IN#1825476 - error raised instead of warning.
 * 
 *    Rev 1.138   Aug 21 2009 10:12:00   jankovii
 * IN 1795247 - R94 - Desktop does not validate  tax type rules, allows to setup Qualified LIF
 * 
 *    Rev 1.137   Apr 23 2009 11:31:32   wutipong
 * PET157825 FN03 MISC RRIF GAPS
 * 
 *    Rev 1.136   Apr 02 2009 09:28:36   jankovii
 * IN 1643940 - Stop user change RIF deff of current year to next year
 * 
 *    Rev 1.135   19 Mar 2009 15:02:34   kovacsro
 * IN#1490538 - Error message when creating a LIF record with "Maximum" pay option (added a couple of fields to view 130 request and one field to 130 response)
 * 
 *    Rev 1.135   19 Mar 2009 14:41:30   kovacsro
 * IN#1490538 - Error message when creating a LIF record with "Maximum" pay option (redesigned view 130 call and eliminated calls to view 375)
 * 
 *    Rev 1.134   26 Jan 2009 09:16:14   kovacsro
 * Un-done the change that went under 1.132 - dealing with the rounding issue
 * 
 *    Rev 1.133   Dec 12 2008 13:44:44   wongsakw
 * IN1495798 - GL-1460 cannot change provincial tax dollar amount.
 * 
 *    Rev 1.132   05 Dec 2008 15:08:36   kovacsro
 *  synchup from 1.130.1.0 (IN#1121661 - fixed rounding issue)
 * 
 *    Rev 1.131   Nov 25 2008 11:27:26   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.130   Jun 22 2008 23:44:28   wongsakw
 * IN1121661 - Error msg Amount exceed LIF maximum incorrectly
 * 
 *    Rev 1.129   04 Jun 2008 14:36:16   kovacsro
 * IN#1291378 - when EffectiveDate is changed for RRIF, it needs to be updated for the allocation, too
 * 
 *    Rev 1.128   05 May 2008 14:51:10   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.127   24 Apr 2008 13:35:32   kovacsro
 * PET2255 FN47 - New Ontario LIF - added EligExtTrfGainLoss
 *
 *    Rev 1.126   Apr 22 2008 14:51:44   jankovii
 * IN 1222272  - spouse birth od date validation for LRIF accounts.
 * 
 *    Rev 1.125   15 Apr 2008 12:09:56   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.124   Mar 25 2008 13:09:02   jankovii
 * IN 1222272 - Desktop does not check for ac owner's dob when setting up a RRIF.
 * 
 *    Rev 1.123   Mar 04 2008 13:36:10   wongsakw
 * INC#1121661 Error msg Incorrect - Amount exceed LIF Maximum
 * 
 *    Rev 1.122   Dec 26 2007 17:28:04   daechach
 * IN#1130286-'Net of fees' option not defaulted on Min Pay out 2008
 * 
 *    Rev 1.121   06 Dec 2007 11:49:06   kovacsro
 * IN#1058816 - fix for PET2360FN76,91
 * 
 *    Rev 1.120   Nov 30 2007 18:27:08   daechach
 * PET5517 FN 97 - RRIF Net of Fees
 * 
 *    Rev 1.119   09 Oct 2007 16:12:24   kovacsro
 * IN#997360 - fixed semi-monthly frequency
 * 
 *    Rev 1.118   04 Oct 2007 11:56:02   kovacsro
 * IN#1027897 - restored rev. 1.116 (DSK fix no longer nedeed - the fix was done at the view side)
 * 
 *    Rev 1.117   01 Oct 2007 14:53:40   kovacsro
 * IN#1027897 - for new items, call Calculate view (DSTC0130), even if no fields have been updated
 * 
 *    Rev 1.116   Aug 22 2007 17:09:46   smithdav
 * IN 982850,  IN    - Add DayOfMonth field conditions to RRIF.
 * 
 *    Rev 1.115   Aug 10 2007 17:07:02   smithdav
 * PET2360 FN76,91
 * 
 *    Rev 1.114   Feb 12 2007 16:38:42   ZHANGCEL
 * Incident #818160 -- Fix problem to trigger validation for Fixed net minimum amout checking.
 * 
 *    Rev 1.113   Dec 06 2006 14:11:42   ZHANGCEL
 * Incident #770827 #768775 -- Fix problem related with MaxAnnualAmt and UnusedMaxAmt
 * 
 *    Rev 1.112   Nov 17 2006 16:51:34   ZHANGCEL
 * Incident #738173 -- Fix net amount validation issue
 * 
 *    Rev 1.111   Sep 25 2006 17:24:06   porteanm
 * Incident 716157 - Monthly Indicator default.
 * 
 *    Rev 1.110   Sep 25 2006 15:13:44   porteanm
 * Incident 716157 - Monthly Indicator default.
 * 
 *    Rev 1.109   Sep 22 2006 13:50:18   ZHANGCEL
 * PET2216 FN35 - RRIF Locked-In products -  PYUnusedMax validation shouldn't check shareHolder TaxJurisCode
 * 
 *    Rev 1.108   Sep 14 2006 17:34:40   ZHANGCEL
 * PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt.
 * 
 *    Rev 1.107   Sep 11 2006 10:21:04   porteanm
 * PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt.
 * 
 *    Rev 1.106   Sep 07 2006 17:48:08   porteanm
 * PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt.
 * 
 *    Rev 1.105   Jul 11 2005 17:24:10   Fengyong
 * PET1250FN02 - European numeric enahncement - conditions
 * decimal format 
 * 
 *    Rev 1.104   Nov 14 2004 14:53:12   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.103   May 20 2004 14:17:08   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.102   Mar 01 2004 11:55:24   YINGBAOL
 * PTS10027517:add some business rules for PRIF
 * 
 *    Rev 1.101   Dec 04 2003 11:48:06   YINGBAOL
 * PTS10020360
 * 
 *    Rev 1.100   Oct 04 2003 16:00:40   popescu
 * CIBC PET 809, FN 13;
 * also cleaned-up BankSearch and BankList objects,
 * replaced with FinancialInstitutionList
 * 
 *    Rev 1.99   Sep 12 2003 13:51:56   YINGBAOL
 * PTS 10020931 add validation for effectivedate,stop date current business date and monthly indicator
 * 
 *    Rev 1.98   Sep 05 2003 11:07:54   ZHANGCEL
 * PTS ticket 10021399: added validation for valid  transfer checking between different taxtype account
 * 
 *    Rev 1.97   Jul 31 2003 13:50:56   popescu
 * PTS 10020265, added more bank fields to the RRIF object so they can be copied over to the update view 129, in case new bank mstr needs to be created
 * 
 *    Rev 1.96   Jul 21 2003 16:20:08   YINGBAOL
 * fix Gross and NetAmount readonly issue
 * 
 *    Rev 1.95   Jun 27 2003 10:15:30   YINGBAOL
 * tuning
 * 
 *    Rev 1.94   Jun 24 2003 09:45:04   YINGBAOL
 * When Amount changes To allocation amount should be changed too
 * 
 *    Rev 1.93   Jun 23 2003 10:01:38   YINGBAOL
 * add validateTransfer
 * 
 *    Rev 1.92   Jun 18 2003 15:10:14   popescu
 * bank instructions should be created only whe the payment method of the RRIF is EFT
 * 
 *    Rev 1.91   Jun 16 2003 10:01:48   YINGBAOL
 * set PrePercentage to 0 if PayOption is not percentage
 * 
 *    Rev 1.90   Jun 13 2003 15:58:46   YINGBAOL
 * Fix GrossNet
 * 
 *    Rev 1.89   Jun 12 2003 17:45:22   YINGBAOL
 * more changes for Allocation and sync. up version 1.83.1.1
 * 
 *    Rev 1.88   Jun 09 2003 11:45:26   YINGBAOL
 * RRIF Enhancement
 * 
 *    Rev 1.87   Jun 01 2003 17:07:54   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.86   May 31 2003 20:30:20   popescu
 * RRIF work part ||
 * 
 *    Rev 1.85   May 31 2003 11:55:14   popescu
 * RRIF bank work
 * 
 *    Rev 1.84   May 27 2003 13:14:06   popescu
 * RRIF Banking work
 * 
 *    Rev 1.83   May 23 2003 10:23:14   YINGBAOL
 * PTS10014772,PTS10016362
 * 
 *    Rev 1.82   May 07 2003 14:04:28   sanchez
 * sync up with v.1.78.1.6 (PTS 10015838 and 10016363)
 * 
 *    Rev 1.81   Apr 29 2003 13:37:00   sanchez
 * sync up with v1.78.1.4 PTS# 10015550
 * 
 *    Rev 1.80   Apr 17 2003 13:20:44   HERNANDO
 * Sync with 1.78.1.3 - 
 * PTS 10015838
 * PTS 10015550
 * PTS 10015081
 * PTS 10015554
 * PTS 10015338
 * PTS 10015039
 * PTS 10015839
 * PTS 10014759
 * 
 *    Rev 1.79   Mar 21 2003 18:22:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.78   Mar 13 2003 13:54:28   HSUCHIN
 * PTS 10014759 - Qualified field is no longer updatable on Bad records.
 * 
 *    Rev 1.77   Mar 07 2003 11:56:38   YINGBAOL
 * change PayOption to be modifiable for existing records____PTS10014560 item 2
 * 
 *    Rev 1.76   Jan 15 2003 14:35:14   YINGBAOL
 * clear AccountTo if Pay type is not "T"
 * 
 *    Rev 1.75   Jan 13 2003 09:41:36   YINGBAOL
 * change Prevouse Year Percentage should also affect calculation
 * 
 *    Rev 1.74   Jan 12 2003 16:39:58   YINGBAOL
 * RRIF Enhancement for Dynamic
 * 
 *    Rev 1.73   Dec 06 2002 09:32:20   YINGBAOL
 * PRIF Enhancement
 * 
 *    Rev 1.72   Nov 12 2002 10:30:28   KOVACSRO
 * synced-up PTS 10010949.
 * 
 *    Rev 1.71   Oct 09 2002 23:54:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.70   Oct 09 2002 14:43:36   ZHANGCEL
 * PTS 10009912 and 10009914 -- bug fix for validation of SpouseBirth
 * 
 *    Rev 1.69   Sep 04 2002 18:44:54   PURDYECH
 * Corrected incorrect use of BFFieldId arrays.
 * 
 *    Rev 1.68   Aug 29 2002 12:56:32   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.67   Aug 20 2002 10:25:40   KOVACSRO
 * not calling default allocations for an existing RRIF.
 * 
 *    Rev 1.66   Aug 19 2002 11:01:28   KOVACSRO
 * new field Allocations, controls the view call
 * 
 *    Rev 1.65   Aug 13 2002 10:45:56   KOVACSRO
 * sync-up 1.63.1.2 PTS10009021
 * 
 *    Rev 1.64   Aug 06 2002 10:03:00   KOVACSRO
 * Release 48. Converted allocations.
 * 
 *    Rev 1.63   Jul 26 2002 11:07:18   ZHANGCEL
 * PTS 10008159: add Apousal DOB checking to RRIF
 * 
 *    Rev 1.62   Jul 19 2002 11:44:08   YINGBAOL
 * Code Clean up
 * 
 *    Rev 1.61   Jul 05 2002 13:44:10   YINGBAOL
 * fix validation for amount
 * 
 *    Rev 1.60   Jun 19 2002 15:03:06   KOVACSRO
 * formatted versus unformatted.
 * 
 *    Rev 1.59   Jun 18 2002 14:53:12   ZHANGCEL
 * PTS 10008159: Added logic in doValidateAll for the Spousal's birth date edit checking
 * 
 *    Rev 1.58   24 May 2002 15:07:52   KOVACSRO
 * doPresetField changes.
 * 
 *    Rev 1.57   22 May 2002 18:29:46   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.56   May 17 2002 13:00:16   YINGBAOL
 * change error message for EffectiveFrom
 * 
 *    Rev 1.55   May 15 2002 15:18:36   YINGBAOL
 * small change
 * 
 *    Rev 1.54   May 15 2002 11:23:02   YINGBAOL
 * change Stop date validation and fix isOnlySpouseBirthDateUpdated
 * 
 *    Rev 1.53   May 13 2002 10:50:20   YINGBAOL
 * modify business rules for EffectiveFrom and StopDate since base allow user to set up RRIF with 12/31/2002 to 12/31/2002
 * 
 *    Rev 1.52   May 08 2002 13:35:30   YINGBAOL
 * PTS10007955 and PTS10007953
 * 
 *    Rev 1.51   Feb 25 2002 18:55:50   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.50   Dec 05 2001 14:25:12   ZHANGCEL
 * Fixed the problem regarding future year record updatable
 * 
 *    Rev 1.49   Nov 22 2001 14:30:44   YINGBAOL
 * skip validation for MaxAmtYr if it is readonly
 * 
 *    Rev 1.48   Nov 20 2001 10:47:52   YINGBAOL
 * add more business rules to amount
 * 
 *    Rev 1.47   Nov 07 2001 11:25:26   YINGBAOL
 * fix minwithdraw and defauly allocation issue
 * 
 *    Rev 1.46   Nov 01 2001 10:19:20   YINGBAOL
 * change Amount to RRIFAmount, check spouse age against shareholder age, fix MandAmtPay, PayType etc.
 * 
 *    Rev 1.45   Oct 16 2001 11:37:54   YINGBAOL
 * fix payoption, amount and related issues
 * 
 *    Rev 1.44   Oct 05 2001 16:07:28   YINGBAOL
 * fix minwithDraw and default allocation
 * 
 *    Rev 1.43   Oct 02 2001 09:00:32   YINGBAOL
 * change error message
 * 
 *    Rev 1.42   Oct 01 2001 14:27:54   YINGBAOL
 * more rules implemented
 * 
 *    Rev 1.41   Sep 27 2001 16:24:28   YINGBAOL
 * add 2 rules for amount validation
 * 
 *    Rev 1.40   Sep 27 2001 13:02:06   ZHANGCEL
 * mark field as updated if set value from calc.
 * 
 *    Rev 1.39   Aug 30 2001 10:50:24   YINGBAOL
 * check MaxApplies flag
 * 
 *    Rev 1.38   Aug 25 2001 14:06:48   YINGBAOL
 * fix frequency issue and other bugs
 * 
 *    Rev 1.37   Jul 26 2001 16:25:38   ZHANGCEL
 * Added logic to set value for MandAmtPay
 * 
 *    Rev 1.36   Jul 20 2001 10:09:22   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.35   Jul 19 2001 15:41:36   ZHANGCEL
 * Added logic in ValidateAgeinst130() in order to set value of Amount and  NetAmount to be NetAmountSysCalc.
 * 
 *    Rev 1.34   Jul 16 2001 17:12:16   ZHANGCEL
 * 1.Do not validate Bank if RRIFValidation is not active; 2.  set status flag of object RRIF_LIF_LRIF_AllocList to be NONE instead of REQUIRED
 * 
 *    Rev 1.33   Jun 26 2001 12:55:08   PURDYECH
 * Infrastructure Release 1.9 Integration.
 * 
 *    Rev 1.32   11 May 2001 08:44:46   HSUCHIN
 * Sync up with SSB (1.30.1.3)
 * 
 *    Rev 1.31   03 May 2001 14:07:04   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.30   Apr 03 2001 15:16:58   YINGBAOL
 * change validation logic for bank since view100 has been changed
 * 
 *    Rev 1.29   Feb 12 2001 15:53:42   JANKAREN
 * Bug fix
 * 
 *    Rev 1.28   Jan 26 2001 17:50:48   ZHANGCEL
 * Synchronized to C2/C3 : Added code in doFieldValidate() for the TaxType checking when validate MinWithAge
 * 
 *    Rev 1.27   Jan 17 2001 12:08:26   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.26   Dec 17 2000 20:24:24   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.25   Dec 04 2000 15:55:20   WINNIE
 * validateAll only if the record has been updated. This is to avoid view 130 when user only switch between records during inquiry. Call setBatchParam to sure there is active batch when user a record
 * 
 *    Rev 1.24   Nov 17 2000 10:45:04   YINGBAOL
 * fix some value inconsistent issues
 * 
 *    Rev 1.23   Nov 14 2000 10:01:14   YINGBAOL
 * fix value issue
 * 
 *    Rev 1.22   Nov 07 2000 13:22:04   YINGBAOL
 * fix validate effective and stop date
 * 
 *    Rev 1.21   Nov 02 2000 13:22:34   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.20   Oct 27 2000 13:24:58   YINGBAOL
 * clean up
 * 
 *    Rev 1.19   Oct 20 2000 14:23:12   YINGBAOL
 * implement setamount logic
 * 
 *    Rev 1.18   Oct 20 2000 13:20:08   YINGBAOL
 * fix warning message cleared for view130
 * 
 *    Rev 1.17   Oct 19 2000 15:25:24   YINGBAOL
 * introduce GroupFlag for fields and modify logic for FedTax and ProviceTax
 * 
 *    Rev 1.16   Oct 17 2000 14:54:00   YINGBAOL
 * add addcopy fundction and fix other issues
 * 
 *    Rev 1.15   Oct 03 2000 13:28:40   YINGBAOL
 * add monthindicate logic and fix bug for call view130
 * 
 *    Rev 1.14   Sep 28 2000 15:04:34   YINGBAOL
 * greate change in order to make it work
 * 
 *    Rev 1.13   Sep 08 2000 11:26:40   PETOLESC
 * Concentrated the logic for calling view 130 in testIfCallingPaymentsCalculation().
 * 
 *    Rev 1.12   Aug 30 2000 14:37:56   PETOLESC
 * Modified crossedits and logic to call view 130.
 * 
 *    Rev 1.11   Aug 04 2000 09:42:48   PETOLESC
 * Moved call to view 124 in DoValidateAll().
 * 
 *    Rev 1.10   Jul 20 2000 14:58:36   PETOLESC
 * Fiddled once more with the call order for view 130.
 * 
 *    Rev 1.9   Jul 18 2000 13:48:58   PETOLESC
 * Modified order of calls for view 130.
 * 
 *    Rev 1.8   Jun 28 2000 15:01:00   PETOLESC
 * Added Frequency field, changed logic for view 130 call sequence and a BIG bunch of other changes.
 * 
 *    Rev 1.7   Jun 09 2000 18:01:38   PETOLESC
 * Save work.
 * 
 *    Rev 1.6   May 19 2000 17:30:10   PETOLESC
 * save work
 * 
 *    Rev 1.5   May 12 2000 16:03:22   PETOLESC
 * Updated validation rules.
 * 
 *    Rev 1.4   May 08 2000 11:53:18   PETOLESC
 * Added getRRIF_LIF_LRIF_AllocList().
 * 
 *    Rev 1.3   Apr 25 2000 16:11:18   PETOLESC
 * Added doValidateField. temporary save.
 * 
 *    Rev 1.2   Mar 20 2000 15:35:26   YINGBAOL
 * field changed
 * 
 *    Rev 1.0   Feb 15 2000 11:00:04   SMITHDAV
 * Initial revision.
// 
*/