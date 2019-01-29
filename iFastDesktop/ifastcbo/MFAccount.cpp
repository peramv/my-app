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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : MFAccount.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//******************************************************************************
#include "stdafx.h"
#include "mfaccount.hpp"

#include "acblist.hpp"
#include "accountdistributionlist.hpp"
#include "accountentityxref.hpp"
#include "accountentityxrefobject.hpp"
#include "accountholdingsbycurrencylist.hpp"
#include "accountmailinginfo.hpp"
#include "accountmailinglist.hpp"
#include "acctmailingoverridelist.hpp"
#include "accountreviewlist.hpp"
#include "accounttradeslist.hpp"
#include "acctcategorylist.hpp"
#include "accountcommitment.hpp"
#include "accountcontractlist.hpp"
#include "acctcontrolrecord.hpp"
#include "acctcontrolrecordlist.hpp"
#include "acctguaranteeguardoptlist.hpp"
#include "acctownershipallocationlist.hpp"
#include "acctroundingrulelist.hpp"
#include "acctsettlementinstrlist.hpp"
#include "acctsplitcommlist.hpp"
#include "acctcutofftimeslist.hpp"
#include "acctsettlementrulelist.hpp"
#include "accshrnumcheck.hpp"
#include "agent.hpp"
#include "amsacctlvllist.hpp"
#include "amsmstrinfo.hpp"
#include "amsmstrlist.hpp"
#include "address.hpp"
#include "addresslist.hpp"
#include "agentlist.hpp"
#include "amsfundalloclist.hpp"
#include "aspensionplan.hpp"
#include "branch.hpp"
#include "branchlist.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "certificatelist.hpp"
#include "contractinfolist.hpp"
#include "currencyclass.hpp"
#include "currency.hpp"
#include "currencylist.hpp"
#include "deffundalloclist.hpp"
#include "demographics.hpp"
#include "directtradinglist.hpp"
#include "errmsgruleslist.hpp"
#include "entity.hpp"
#include "entityids.hpp"
#include "entityidslist.hpp"
#include "esopinfo.hpp"
#include "entityregdetailslist.hpp"
#include "entityregjurisdetailslist.hpp"
#include "feeparamlist.hpp"
#include "freeunitlist.hpp"
#include "fundmasterlist.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "fundmgmtsettlementinstrlist.hpp"
#include "fundservbrokervalidation.hpp"
#include "grouplist.hpp"
#include "group.hpp"
#include "groupfundlist.hpp"
#include "groupfund.hpp"
#include "hyporedcriteria.hpp"
#include "investorauthorizationlist.hpp"
#include "investorauthorization.hpp"
#include "intermediarylist.hpp"
#include "mastercontractlist.hpp"
#include "matchtransferlist.hpp"
#include "mfaccountholdinglist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "nomineeinteraddr.hpp"
#include "paytoentity.hpp"
#include "paytoentitylist.hpp"
#include "pendingtradedetails.hpp"
#include "pendingtradelist.hpp"
#include "pensioninfo.hpp"
#include "protectedfundlist.hpp"
#include "prodportfoliofundlist.hpp"
#include "prodportfolioinfolist.hpp"
#include "prodportfolioplaninfolist.hpp"
#include "regdocumentlist.hpp"
#include "residency.hpp"
#include "respbeneficiaryallocationlist.hpp"
#include "rrif_lif_lrif_infolist.hpp"
#include "respinfo.hpp"
#include "resptransactionslist.hpp"
#include "recipienttypelist.hpp"
#include "regplantransferlist.hpp"
#include "remarkslist.hpp"
#include "resptransferlist.hpp"
#include "rspcontributionlist.hpp"
#include "shareholder.hpp"
#include "shralloctype.hpp"
#include "shralloctypelist.hpp"
#include "systematiclist.hpp"
#include "taxtyperule.hpp"
#include "taxtyperulelist.hpp"
#include "tradeacctalloc.hpp"
#include "tradeacctalloclist.hpp"
#include "tradefromfundalloclist.hpp"
#include "tradefundalloc.hpp"
#include "tradefundalloclist.hpp"
#include "trademinamtcheck.hpp"
#include "transactionlist.hpp"
#include "userdefmatlist.hpp"
#include "worksessionentitylist.hpp"
#include "tradeauthorization.hpp"
#include "inventorysummarylist.hpp"
#include "taxexemptauthorizationlist.hpp"
#include "taxexemptauthorization.hpp"
#include "translationtable.hpp" 
#include "MatSweepInstrList.hpp"
#include "FeeModelList.hpp"
#include "RESPTransactionTypesList.hpp"
#include "RESPBeneficiaryList.hpp"
#include "RESPTradeSearchCriteria.hpp"
#include "RESPInfoUpdateValidationList.hpp" //QESI3FN03
#include "ContractMaturityInstructionList.hpp"
#include "AcctRegDetailsList.hpp"
#include "FinInstRegDetlList.hpp"
#include "AlertMessageList.hpp"
#include "coanavig.hpp"

//requests
#include <ifastdataimpl\dse_dstc0004_req.hpp>
#include <ifastdataimpl\dse_dstc0076_req.hpp>
//views
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0011_vw.hpp>
#include <ifastdataimpl\dse_dstc0015_vw.hpp>
#include <ifastdataimpl\dse_dstc0020_vw.hpp>
#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0054_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0091_vw.hpp>
#include <ifastdataimpl\dse_dstc0092_vw.hpp>
#include <ifastdataimpl\dse_dstc0088_vw.hpp>
#include <ifastdataimpl\dse_dstc0120_vw.hpp>
#include <ifastdataimpl\dse_dstc0142_vw.hpp>
#include <ifastdataimpl\dse_dstc0144_req.hpp>
#include <ifastdataimpl\dse_dstc0144_vw.hpp>
#include <ifastdataimpl\dse_dstc0179_vw.hpp>
#include <ifastdataimpl\dse_dstc0179_req.hpp>
#include <ifastdataimpl\dse_dstc0250_vw.hpp>
#include <ifastdataimpl\dse_dstc0250_req.hpp>
#include <ifastdataimpl\dse_dstc0050_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0003_req.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastdataimpl\dse_dstc0265_vw.hpp>
#include <ifastdataimpl\dse_dstc0018_vw.hpp>
#include <ifastdataimpl\dse_dstc0385_req.hpp>
#include <ifastdataimpl\dse_dstc0385_vw.hpp>
#include <ifastdataimpl\dse_dstc0386_req.hpp>
#include <ifastdataimpl\dse_dstc0386_vw.hpp>
#include "DefFundAllocList.hpp"

const I_CHAR * const ALLOW_NEGBAL_FUNDCLASS = I_("28"); 

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MFACCOUNT;
   extern CLASS_IMPORT const DSTCRequest LIP_RATE_EXIST;
   extern CLASS_IMPORT const DSTCRequest AMS_CODE;
   extern CLASS_IMPORT const DSTCRequest SEARCH;
   extern CLASS_IMPORT const DSTCRequest AMS_BROKER_LIST;
   extern CLASS_IMPORT const DSTCRequest AFFLUENT_VALIDATION;
   extern CLASS_IMPORT const DSTCRequest ACCT_CONTROL_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME                 = I_( "MFAccount" );
   const I_CHAR * const DATE_FORMAT               = I_( "MMddyyyy" );
   const I_CHAR * const THREE_STRING              = I_( "3" );
   const I_CHAR * const JOINT_CODE                = I_( "2" );
   const I_CHAR * const VALIDVALUESFORACCTNUMCTRL = I_( "Mm" );//for Morgan

   // for trade
   const I_CHAR * const FUND                       = I_( "FUND" );
   const I_CHAR * const CLASS                      = I_( "CLASS" );
   const I_CHAR * const MINIMUM_AMT                = I_( "MINIMUM_AMT") ;  
   const I_CHAR * const MINIMUM_BAL                = I_( "MINIMUM_BAL") ; 
   const I_CHAR * const TRADE_TYPE                 = I_( "TRADE_TYPE") ;
   const I_CHAR * const MAXIMUM_AMT                = I_( "MAXIMUM_AMT") ;

   const I_CHAR * const PURCHASE_CODE              = I_( "ED" );     // trade trans type Purchase
   const I_CHAR * const REDEMPTION_CODE            = I_( "PW" );     // trade trans type Redemption
   const I_CHAR * const EXCHANGE_TRANSFER_CODE     = I_( "TR" );     // trade trans type Transfer 
   const I_CHAR * const EX_FER_IN_CODE             = I_( "XFIN" );   // trade trans type Exchange In 
   const I_CHAR * const EX_FER_OUT_CODE            = I_( "XFOUT" );  // trade trans type Exchange Out
   const I_CHAR * const EXCHANGE_OUT_CODE          = I_( "EXOUT" );  // trade trans type Exchange Out
   const I_CHAR * const TRANSFER_OUT_CODE          = I_( "TFOUT" );  // trade trans type Transfer Out
   const I_CHAR * const ADDR_CHG                   = I_( "ADDR_CHANGE" ); //address change

   const I_CHAR * const YES                            = I_( "Y" );
   const I_CHAR * const NO                             = I_( "N" );

   const I_CHAR * const ACCOUNT_GROUP_LEVEL            = I_( "A" ); 
   const I_CHAR * const SHAREHOLDER_GROUP_LEVEL        = I_( "S" ); 

   const I_CHAR * const CLIENT_ACCT_DESIGNATION        = I_( "1" );  
   const I_CHAR * const INTERMEDIARY_ACCT_DESIGNATION  = I_( "3" ); 

   const I_CHAR * const NON_REGISTERED_TAX_TYPE        = I_( "0" ); 
   const I_CHAR * const RRSP_TAX_TYPE                  = I_( "1" ); 
   const I_CHAR * const RRIF_TAX_TYPE                  = I_( "2" ); 
   const I_CHAR * const INDIVIDUAL_RESP_TAX_TYPE       = I_( "9" );
   const I_CHAR * const LRSP_TAX_TYPE                  = I_( "U" );
   const I_CHAR * const LRIF_TAX_TYPE                  = I_( "L" );
   const I_CHAR * const PRIF_TAX_TYPE                  = I_( "R" );	
   const I_CHAR * const FAMILY_RESP_TAX_TYPE           = I_( "M" );
   const I_CHAR * const SD_EXTERNAL_RESP               = I_( "F" );
   const I_CHAR * const AS_PENSION_PLAN_TAX_TYPE       = I_( "P" );
   const I_CHAR * const TFSA_TAX_TYPE                  = I_( "V" );
   const I_CHAR * const INDIVIDUAL_ACCT_TYPE           = I_( "0" ); 
   const I_CHAR * const JOINT_ACCT_TYPE                = I_( "2" ); 
   const I_CHAR * const CORPORATE_ACCT_TYPE            = I_( "4" );
   const I_CHAR * const LOCKED_IN                      = I_( "5" );
   const I_CHAR * const RESTRICTED                     = I_( "O" );

   const I_CHAR * const TAX_TYPE_OA                    = I_( "OA" );
   const I_CHAR * const TAX_TYPE_SA                    = I_( "SA" );
   const I_CHAR * const TAX_TYPE_SRS                   = I_( "SR" );

   const I_CHAR * const REDIRECT_TO_RA_ID              = I_( "98" );

   const I_CHAR * const ACTIVE_ACCT_STATUS              = I_( "10" ); //PET0168296FN09
   const I_CHAR * const TERMINATED_ACCT_STATUS          = I_( "30" ); 
   const I_CHAR * const DEATH_ACCT_STATUS               = I_( "40" ); 
   const I_CHAR * const DEATH_TRANSFER_ACCT_STATUS      = I_( "41" ); 

   const I_CHAR * const EXTEMPT_HOLDING_EXCESS_RRSP_FEE = I_( "4" ); 

   const I_CHAR * const UNASSIGNED_COUNTRY_CODE         = I_( "0000" ); 
   const I_CHAR * const FEDERAL_COUNTRY_CODE            = I_( "9999" ); 

   const I_CHAR * const ACCOUNT_OWNER_ENTITY_TYPE           = I_( "01" );
   const I_CHAR * const NOMINEE_OWNER_ENTITY_TYPE           = I_( "21" );
   const I_CHAR * const ESCROW_REPRESENTATIVE_ENTITY_TYPE   = I_( "11" ); 
   const I_CHAR * const RESP_BENEFICIARY_ENTITY_TYPE        = I_( "50" );
   const I_CHAR * const PARENT_GUARDIAN_ENTITY_TYPE         = I_( "51" );
   const I_CHAR * const RESP_DSGN_INST_ENTITY_TYPE          = I_( "52" );
   const I_CHAR * const RESP_PCG_INDIV_ENTITY_TYPE          = I_( "55" );
   const I_CHAR * const RESP_PCG_INST_ENTITY_TYPE           = I_( "56" );


   const I_CHAR * const N_A_RECIPIENT_TYPE         = I_( "0" );
   const I_CHAR * const INDIVIDUAL_RECIPIENT_TYPE  = I_( "1" );
   const I_CHAR * const JOINT_RECIPIENT_TYPE       = I_( "2" );
   const I_CHAR * const CORPORATION_RECIPIENT_TYPE = I_( "3" );
   const I_CHAR * const TRUST_RECIPIENT_TYPE       = I_( "4" );

   const I_CHAR * const BLANK_SUBSTITUTION         = I_( " = ;"); // substitution with only one element with tag = value = " " 
   const int FULL_LIST                             = 0;

   const I_CHAR * const ESOP_INVESTMENT            = I_( "D" );
   const I_CHAR * const ESOP_PARTICIPATION         = I_( "E" );
   const I_CHAR * const ASPENSIONPLAN              = I_("AsPensionPlan");
   const I_CHAR * const SORTED_BY_LAST_NAME        = I_( "LN" );
   const I_CHAR * const HYPO_RED_CRITERIA          = I_( "HypoRedCriteria" );
   const I_CHAR * const AMS_ACCT_ALLOC_LIST        = I_( "AmsAcctAllocList" );
   const I_CHAR * const ACCT_CATEGORY_LIST         = I_( "AcctCategoryList" );
   const I_CHAR * const REG_DOCUMENT_LIST          = I_( "RegDocumentList" );
   const I_CHAR * const ACCT_LVL_SETTLMNT_RULE_LIST= I_( "AcctLvlSttlmntRuleList" );
   const I_CHAR * const ACCOUNT_COMMITMENT         = I_( "AcctCommit" );

   //account categories
   const I_CHAR * const LOAN                       = I_( "01" );
   const I_CHAR * const MARGIN                     = I_( "02" );
   const I_CHAR * const CHEQUE_PRIVILEGE           = I_( "03" );
   const I_CHAR * const WRAP                       = I_( "04" );
   const I_CHAR * const TRADING_CLIENT             = I_( "07" );
   const I_CHAR * const PUEV_CAPABLE               = I_( "09" );
   const I_CHAR * const INVESTRO_CAPABLE           = I_( "08" );
   const I_CHAR * const CLIENT_MONTHLY_STATEMENT   = I_( "54" ); // statement and confirm   

   //account designation
   const I_CHAR * const NOMINEE                     = I_( "02" );
   const I_CHAR * const THIRD_PARTY                 = I_( "03" );
   const I_CHAR * const ITF_INDIVIDUAL_ENTITY_TYPE  = I_( "14" );
   const I_CHAR * const CANADA_PROVINCE             = I_("0001,0002,0003,0004,0005,0006,0007,0008,0009,0010,0011,0012");
   const I_CHAR * const YOUTH_POTFOLIO              = I_( "YP" );
   const I_CHAR * const CAN_PAC                     = I_( "P" );
   const I_CHAR * const CAN_SWP                     = I_( "S" );
   const I_CHAR * const CAN_AT_IN                   = I_( "AI" );
   const I_CHAR * const CAN_AT_OUT                  = I_( "AO" );
   const I_CHAR * const MIN_PAC                     = I_( "MP" );
   const I_CHAR * const MIN_SWP                     = I_( "MS" );
   const I_CHAR * const CAN_PURCHASE                = I_( "CP" );
   const I_CHAR * const CAN_REDEEM                  = I_( "CR" );
   const I_CHAR * const CAN_TRANSFER_IN             = I_( "CTI" );
   const I_CHAR * const CAN_TRANSFER_OUT            = I_( "CTO" );
   const I_CHAR * const DEFNETWORKCONTROLIND        = I_( "0" );
   const I_CHAR * const SCHEDULE01                  = I_( "01" );
   const I_CHAR * const KYC_SYSTEM                  = I_( "03" );
   const I_CHAR * const DECEASED_SYSTEM             = I_( "04" );
   const I_CHAR * const ACCTREG                     = I_( "0" );
   const I_CHAR * const NI_31_103_STMT              = I_( "NISTMT" );  // statement and confirm   
   const I_CHAR * const SSG_SOCIAL_CODE_LIST        = I_( "AM,CH,CT,CI,EI,HF,IR,IT,MF,OF,PM,PT,PC,PE,PS,SO,WM,WD" );
   
   //const long ERR_SALES_REP_ALREADY_EXISTS          = 40002706;

   const I_CHAR * const ERISA_ORG_TYPE              = I_( "02,03,04,05");
   const I_CHAR * const EXCLUDED_ORG_TYPE           = I_( "06,07,08");

   const I_CHAR * const UNASSIGNED_TAX_JURIS        = I_( "0000" );
   //P0186486FN09 - Employee and Agent Account Gap#8A
   const I_CHAR * const EMPLOYEE                    = I_("08"); 
   const I_CHAR * const AGENT                       = I_("09");
   const I_CHAR * const SHAREHOLDER_OUTPUT_TYPE     = I_("SOT"); 

   const I_CHAR * const FATCA					    = I_("FA");
   const I_CHAR * OMNIBUS						    = I_("OM");
   const I_CHAR * const BLANK_SUBSTITUTION_VALUE    = I_("= ;");

   //Account control record list rule "30" and rule "80"
   const I_CHAR *const ACCOUNT_TYPE_RULE            = I_("ACCTPYMTRULE");
   const I_CHAR *const ORDER_ROUTING_RULE           = I_("OrderRouting");

   //P0274738, Australia product
   const I_CHAR * const SOCIAL_CODE					= I_("SO");

   const I_CHAR * const RDSP_TAX_TYPE				= I_("RS");
}

namespace IDS
{
   const I_CHAR * const FAST                 = I_("30");
   const I_CHAR * const iFAST_SICAV          = I_("31");
   const I_CHAR * const iFAST_OEIC           = I_("32");
}

namespace SHAREHOLDER_OUTPUT_FORMAT
{
   const I_CHAR * const REGULAR_PRINT        = I_("REG");
   const I_CHAR * const LARGE_PRINT          = I_("LRG");
   const I_CHAR * const BRAILLE              = I_("BRL");
   const I_CHAR * const AUDIO                = I_("AUD");
}



namespace COMPLY_RULE
{
   extern CLASS_IMPORT const DString AcctRegistration; 
   extern CLASS_EXPORT const DString DeathClaim ;
   extern CLASS_EXPORT const DString TaxCompliant;
   extern CLASS_EXPORT const DString AccountholderRisk;
}

extern BF_OBJ_TYPE OBJ_TYPE_ACCOUNT_MAILING;

namespace CND
{
   // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_FIELD_REQUIRED_PLS_SELECT;
   extern const long WARN_FIELD_REQUIRED_PLS_SELECT;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
   extern const long ERR_INVALID_TAX_TYPE;
   extern const long ERR_ACCT_BALANCE_TERM_AND_DEL;
   extern const long ERR_GROUP_CODE_LEVEL;
   extern const long ERR_BROKER_BRANCH_CFG;
   extern const long ERR_REP_BY_BRANCH_CFG;
   extern const long ERR_MULTIPLE_ACCT_OWNER_NEEDED;
   extern const long ERR_ACCOUNT_NUMBER_EXISTS;
   extern const long INFO_SHAREHOLDER_HAS_MULTIPLE_ADDRESSES;
   extern const long ERR_EFFECTIVE_DATE_BACKWARD;
   extern const long ERR_ACCOUNT_NUM_CANNOT_BE_LEFT_EMPTY;
   extern const long ERR_ACCOUNT_NUMBER_CANNOT_START_WITH_ZERO;
   extern const long ERR_NOT_A_RIF_ACCOUNT;
   extern const long ERR_ACCT_INACTIVE_ON_TRADE_DATE;
   extern const long ERR_ACCOUNT_STOP_FLAG_ON;
   extern const long ERR_GROUP_STOP_FLAG_ON;
   extern const long ERR_BROKER_EMPTY;
   extern const long ERR_BRANCH_EMPTY;
   extern const long ERR_SALES_REP_EMPTY;
   extern const long ERR_ACCOUNT_EMPTY;
   //   extern const long ERR_TAX_TYPE_EMTPY;
   //   extern const long ERR_ACCOUNT_TYPE_EMPTY;
   extern const long ERR_ACCT_BALANCE_TERM_AND_DEL_MAINT;
   extern const long ERR_MINIMUM_FUND_BALANCE;
   extern const long ERR_ACCT_BALANCE_ZERO;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_TO_GROUP;
   extern const long ERR_FUND_CLASS_STOP_FLAG_ON;
   extern const long ERR_ESCROW_LOCKED_ALL_UNITS;
   extern const long ERR_ESCROW_LOCKED_PARTIAL_UNITS;  
   extern const long ERR_EXEMPT_HOLDING_EXCESS;
   extern const long ERR_INVALID_PENSION;
   extern const long ERR_FEDERAL_JURISDICTION;
   extern const long ERR_NO_TAX_TYPE_RULES;
   extern const long ERR_RIF_BAD_RECORD;
   extern const long ERR_SALESPERSON_IS_NOT_PERMITTED;
   extern const long ERR_CONTRACT_STATUS;
   extern const long ERR_CURRENT_FUND_BALANCES;
   extern const long ERR_NO_PENSION_INFORMATION;
   extern const long ERR_NO_DATE_OF_BIRTH;
   extern const long ERR_CLIENTS_AGE_BEYOND;
   extern const long ERR_SHAREHOLDER_BELOW_69;
   extern const long ERR_ACC_TAX_TYPE_NOT_MATCH;
   extern const long ERR_CANNOT_CHANGE_TAX_TYPE;
   extern const long ERR_ESCROW_REP_SHOULD_BE_DELETED;
   extern const long ERR_NO_ESCROW_REP_RECORD_AVAILABLE;
   extern const long ERR_PARENT_HAS_NOT_BEEN_SETUP;
   extern const long ERR_DESIGNATION_INSTITUTION_HAS_NOT_BEEN_SETUP;

   extern const long ERR_ACCOUNT_OWNER_ENTITY_MUST_BE_SETUP;
   extern const long ERR_RESP_BENEFICIARY_ENTITY_MUST_BE_SETUP;
   extern const long ERR_RESP_BENEFICIARY_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE;
   extern const long ERR_PARENT_ENTITY_SHOULD_BE_SETUP;
   extern const long ERR_ONLY_ONE_PARENT_ENTITY_IS_ALLOWED;
   extern const long ERR_RESP_DESIGNATED_INSTIT_ENTITY_SHOULD_BE_SETUP;
   extern const long ERR_ANNUITANT_ENTITY_SHOULD_BE_SETUP;
   extern const long ERR_ANNUITANT_ENTITY_IS_NOT_ALLOWED;
   extern const long ERR_ONLY_ONE_ACCOUNT_OWNER_ENTITY_IS_ALLOWED;
   extern const long ERR_MULTIPLE_ACCOUNT_OWNER_ENTITY_SHOULD_SETUP;
   extern const long ERR_TRUSTEE_ENTITY_SHOULD_BE_SETUP;
   extern const long ERR_ITF_ENTITY_SHOULD_BE_SETUP;
   extern const long ERR_ESCROW_REPREZENTATIVE_ENTITY_MUST_BE_SETUP;
   extern const long ERR_NOMINEE_OWNER_ENTITY_MUST_BE_SETUP;
   extern const long ERR_SECONDARY_BENEFICIARY_ENTITY_ONLY_ALLOWED_IF_PRIMARY_ENTITY_EXIST;
   extern const long ERR_SPOUSAL_CONTRIBUTOR_ENTITY_SHOULD_BE_SETUP;
   extern const long ERR_ACCT_TYPE_NOT_VALID_FOR_TAX_TYPE;

   extern const long ERR_TAX_TYPE_NOT_FOR_ACCT_DESIGNATION;

   extern const long ERR_GROUP_NUMBER_IS_REQUIRED;
   extern const long ERR_INTERMEDIARY_CODE_IS_REQUIRED;
   extern const long ERR_INTERMEDIARY_ACCOUNT_NUMBER_IS_REQUIRED;
   extern const long ERR_DATE_OF_REGISTRATION;
   extern const long ERR_W_ENTITY_AGE_OVER_69;
   extern const long ERR_E_ENTITY_AGE_OVER_69;

   extern const long ERR_ACCOUNT_REDEMPTION_FLAG_ENABLED;
   extern const long ERR_WARN_ACCOUNT_REDEMPTION_FLAG_ENABLED;
   extern const long ERR_WARN_ACCT_LOCKED_NO_REDEMPTION_AVAILABLE;
   extern const long ERR_ACCT_LOCKED_NO_REDEMPTION_AVAILABLE;

   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_BROKER_NOT_FOUND;
   extern const long ERR_GIC_PURCHASE_NOT_ALLOWED;
   extern const long ERR_RIF_AMS_FUND_FUND_CODE;
   extern const long ERR_RB_NOT_ALLOWED;
   extern const long ERR_INVALID_ACCOUNT_NUMBER;
   extern const long ERR_WARN_DUPLICATE_ALTACCOUNT;
   extern const long ERR_WRONG_COMBINATION_TAXTYPE_JURISDICTION;
   extern const long ERR_WARN_WRONG_COMBINATION_TAXTYPE_JURISDICTION;
   extern const long ERR_PENSION_JURIS_IS_MANDATORY;
   extern const long ERR_EMPLOYEE_LOCKED_IN_AT_GROUP;
   extern const long ERR_EMPLOYER_LOCKED_IN_AT_GROUP;
   extern const long ERR_EMPLOYER_EMPLOYEE_LOCKED_IN_AT_GROUP;
   extern const long ERR_FUND_NOT_MARGIN_ELIGIBLE;

   // protected fund errors
   extern const long ERR_ACCTHOLDER_DOFBIRTH_MISSING;
   extern const long ERR_ACCTHOLDER_OVER_AGE_FOR_PROTECTED_FUND;
   extern const long ERR_SIN_MISSING_FOR_TRADING_PROTECTED_FUND;
   extern const long ERR_BENEFICAL_OWNER_NAME_FOR_PROTECTED_FUND;
   extern const long ERR_ACCTOWNER_SIN_MISSING;
   extern const long WARN_MARGIN_ACCT_LETTER_REQ;
   extern const long ERR_BROKER_INVALID_AS_OF_DATE;
   extern const long ERR_BROKER_NOT_EFFECTIVE;
   extern const long ERR_NO_BROKER_INTER_ADDRESS;
   extern const long ERR_NON_VISCOUNT_FUND;
   extern const long ERR_BROKER_NOT_ELIGIBLE_FOR_ACCT;
   extern const long ERR_AGENT_NOT_ELIGIBLE_FOR_ACCT;
   extern const long ERR_NO_ALLOWED_FOR_AS_PENSION_PLAN;

   extern const long ERR_ACCT_INELIGIBILE_PAY_OPTION_WAIVED;
   extern const long ERR_ACCT_INELIGIBILE_PAY_OPTION_WAIVED;
   extern const long ERR_INVALID_BUSINESSNO;
   extern const long WARN_INVALID_BUSINESSNO;
   extern const long ERR_AMS_ACCOUNT_RESIDENT_PROVINCE;
   extern const long ERR_AMS_ACCOUNT_TAX_JURISDICTION;
   extern const long ERR_AMS_ACCOUNT_DESIGNATION;
   extern const long ERR_AMS_ACCOUNT_TAX_TYPE;
   extern const long ERR_AMS_ACCOUNT_TYPE;
   extern const long AMS_ERR_CANNOT_PURCHASE_FUND_OUTSIDE_ALLOC;
   extern const long AMS_ERR_USER_NO_PERMISSION_OVERRIDE_AMS_ALLOC;
   extern const long ERR_GIC_FUND_NOT_ALLOWED_IN_AMS;
   extern const long ERR_MPS_FUND_NOT_ALLOWED_IN_AMS;
   extern const long WARN_CHANGE_CLEARINFID_PENDING;
   extern const long ERR_UNSETTLED_TRADES_WITH_AMS;
   extern const long WARN_UNSETTLED_TRADES_WITH_AMS;
   extern const long ERR_PENDING_TRADES_WITH_AMS;
   extern const long WARN_PENDING_TRADES_WITH_AMS;	
   extern const long ERR_SALS_CODE_HAS_TO_BE_5;
   extern const long WAR_SALS_CODE_HAS_TO_BE_5;	
   extern const long ERR_SALES_CODE_CAN_NOT_LONGER_THAN_6;
   extern const long ERR_ALTACCT_REQUIRED_FOR_PUEV_INVESTRO;
   extern const long ERR_FEEMODEL_CODE_NOT_SETUP;
   extern const long ERR_FEEMODEL_CODE_NOT_ACTIVE;
   extern const long WARN_ACCT_CATEG_PUEV_SHOULD_BE_SETUP_BASED_ON_CLEARINGID;
   extern const long ERR_ACCT_EFFECTIVE_DATE_VALIDATE;
   extern const long WARN_EFFECTIVE_DATE_BACKWARD;
   extern const long WARN_BRKBRREP_INACTIVE_CURRBUSDATE;

   // NSCC error
   extern const long WARN_ACCT_SWITCH_TO_NON_NSCC_BROKER;
   extern const long WARN_ACCT_SWITCH_TO_NSCC_BROKER;
   extern const long ERR_NO_ONE_EQUAL_TO_BROKER_CODE;
   extern const long ERR_AGENTFORFIRM_INVALID;
   extern const long ERR_AGENTFORFIRM_NOT_RELATED_TO_CLEARINGFIRM;
   extern const long ERR_TPA_INVALID;
   extern const long ERR_TPA_NOT_RELATED_TO_CLEARINGFIRM;
   extern const long ERR_AGENT_TPA_SAME;
   extern const long ERR_INPUTED_VALUES_IS_NOT_NSCC_COMPLIANT;
   extern const long ERR_CLEARINGFIRM_IS_MANDATORY;
   extern const long ERR_CLEARINGFIRM_ALREADY_EQUAL_TO_BROKER;
   extern const long ERR_PARTICIPANTID_MISSING;
   extern const long ERR_DELETE_PRIVATE_ACCOUNT_CATEGORY;

   extern const long ERR_AMS_ACCOUNT_HOLD_GIC;
   extern const long WARN_AMS_ACCOUNT_HOLD_GIC;
   extern const long ERR_AMS_ESCROW_FOR_ACCOUNT;
   extern const long WARN_AMS_ESCROW_FOR_ACCOUNT;
   extern const long ERR_AMS_SETUP_FOR_PAC;
   extern const long WARN_AMS_SETUP_FOR_PAC;
   extern const long ERR_AMS_SETUP_FOR_SWP;
   extern const long WARN_AMS_SETUP_FOR_SWP;
   extern const long ERR_AMS_CANNOT_SETUP_FOR_ACCOUNT_HOLDING_MULTICURRENCY_FUND;
   extern const long WARN_AMS_CANNOT_SETUP_FOR_ACCOUNT_HOLDING_MULTICURRENCY_FUND;

   extern const long ERR_RESP_NASU_NOT_AVAILABLE;
   extern const long WARN_RESP_NASU_NOT_AVAILABLE;
   extern const long ERR_AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL;
   extern const long WARN_AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL;
   extern const long ERR_ACCOUNT_ESCROW_FLAG_IS_ACTIVE;
   extern const long WARN_ACCOUNT_ESCROW_FLAG_IS_ACTIVE;
   extern const long ERR_AMS_SETUP_NOT_ALLOWED_IF_STOP_PURCH_REDEM;
   extern const long WARN_AMS_SETUP_NOT_ALLOWED_IF_STOP_PURCH_REDEM;

   extern const long ERR_AMS_ACTIVE_CERTS_EXIST;
   extern const long WARN_AMS_ACTIVE_CERTS_EXIST;
   extern const long ERR_TAX_TYPE_NO_LONGER_SUPPORTED_AFTER_DATE;
   extern const long ERR_SYSTEM_STOP_REASON;
   extern const long ERR_TAX_TYPE_LIMIT_RULE_NOT_SUPPORTED_BEFORE_DATE;
   extern const long ERR_CANNOT_SWITCH_FROM_RESTRICTED_TO_NON_RESTRICTED;

   extern const long ERR_NON_RESIDENT_TAX_JURID;
   extern const long WARN_NON_RESIDENT_TAX_JURID;
   extern const long ERR_CANNOT_CHANGE_TAXTYPE;
   extern const long ERR_RECIPIENT_TYPE_NOT_VALID_FOR_JURISDICTION;
   extern const long WARN_IA_BRK_BRNCH_SLSREP_NOT_SAME_WITH_ACCOUNT;
   extern CLASS_IMPORT const long ERR_NO_BRANCH_FOUND; 
   extern const long ERR_AGENT_NOT_FOUND_FOR_BROKER_BRANCH;
   extern const long ERR_CANNOT_SWITCH_TAXTYPE;
   extern const long WARN_SIBLING_ONLY_BLANK_OR_NO;
   extern const long WARN_CLNT_MTH_STMT_SHOULD_BELONG_ACCT_NON_MFDA;
   extern const long ERR_ACCT_CATEGORY_NOT_ALLOWED_FOR_ACCOUNT;
   extern const long WARN_ACCOUNT_IS_BEING_ACTIVATED; //PET0168296FN09
   extern const long ERR_ACCOUNT_IS_BEING_ACTIVATED; //PET0168296FN09
   extern const long WARN_SOCIAL_CODE_NOT_APPLICABLE;
   extern const long ERR_SOCIAL_CODE_NOT_APPLICABLE;
   extern const long WARN_TFSA_ACCT_STATUS_CHANGED;      
   extern const long ERR_PROD_PORTFOLIO_RELATED_FIELDS_REQUIRED;
   extern const long WARN_PROD_PORTFOLIO_RELATED_FIELDS_REQUIRED;
   extern const long ERR_UNABLE_TO_CHANGE_ACCT_PORTFOLIO;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_TO_CURRENT_ACCT_PORTFOLIO;
   //P0186486FN09 - Employee and Agent Account Gap#8A
   extern const long ERR_CHANGE_REPS_IS_NOT_APPLICABLE;
   extern const long WARN_CHANGE_REPS_IS_NOT_APPLICABLE;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP;
   extern const long ERR_COMPENSATION_AGENT_MUST_BE_CHANGED;
   extern const long WARN_COMPENSATION_AGENT_MUST_BE_CHANGED;
   //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
   extern const long ERR_STOP_ADJDATE_GREATER_THAN_EFFECTIVEDATE;
   
   extern const long ERR_NET_TRANS_AMT_CANNOT_BE_EARLIER_THAN_INIT_DATE;
   extern const long ERR_DATE_CANNOT_BE_FUTURE;
   extern const long ERR_INVALID_NEGATIVE_AMOUNT;
   extern const long ERR_DATE_CANNOT_BE_EARLIER_THAN_ACCOUNT_EFFECTIVE;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
   extern const long ERR_SRVCE_AGENT_BELONGS_TO_FUNDSERV_BROKER;
   extern const long WARN_SRVCE_AGENT_BELONGS_TO_FUNDSERV_BROKER;
   extern const long ERR_REGULATORY_DOC_STATUS_NEEDS_TO_BE_MANUALLY_UPDATED;
   extern const long WARN_REGULATORY_DOC_STATUS_NEEDS_TO_BE_MANUALLY_UPDATED;
   extern const long ERR_ACCOUNT_ATTATCHED_TFR_NEED_TO_BE_STOPPED;
   extern const long WARN_ACCOUNT_ATTATCHED_TFR_NEED_TO_BE_STOPPED;
   extern CLASS_IMPORT const long ERR_SALES_REP_ALREADY_EXISTS;
   extern const long ERR_SERVICE_ONLY_SALES_REP;
   extern const long WARN_SERVICE_ONLY_SALES_REP;
   extern const long ERR_SALE_REP_IS_NOT_ELIGIBLE_FOR_FUND_CLASS;
   extern const long WARN_SALE_REP_IS_NOT_ELIGIBLE_FOR_FUND_CLASS;
   extern const long ERR_BROKER_IS_NOT_ELIGIBLE_FOR_FUND_CLASS;
   extern const long WARN_BROKER_IS_NOT_ELIGIBLE_FOR_FUND_CLASS;
   extern const long ERR_ACCT_NOT_ELIGIBLE_MONEY_IN_AGE_LESS_THAN_MINIMUM;
   extern const long WARN_ACCT_NOT_ELIGIBLE_MONEY_IN_AGE_LESS_THAN_MINIMUM;
   extern const long ERR_UNREVERSED_TERMINATION_ENTRIES_EXIST;
   extern const long WARN_UNREVERSED_TERMINATION_ENTRIES_EXIST;

   //P0266360 HSBC - Custodian
   extern const long ERR_PIM_INST_ACCT_MUST_BE_ADDED_TO_CUSTODIAN;
   extern const long WARN_PIM_INST_ACCT_MUST_BE_ADDED_TO_CUSTODIAN;
}

namespace IFASTERR
{
   // if order source is valid for account designation
   extern CLASS_IMPORT I_CHAR * const AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL;
   extern CLASS_IMPORT I_CHAR * const AMS_SETUP_NOT_ALLOWED_IF_STOP_PURCH_REDEM;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_ESCROW_FLAG_IS_ACTIVE;
   extern CLASS_IMPORT I_CHAR * const RESP_NASU_NOT_AVAILABLE;
   extern CLASS_IMPORT I_CHAR * const AMS_ACTIVE_CERTS_EXIST;
   extern CLASS_IMPORT I_CHAR * const NON_RESIDENT_TAX_JURID;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_IS_BEING_ACTIVATED; //PET0168296FN09
   extern CLASS_IMPORT I_CHAR * const SOCIAL_CODE_NOT_APPLICABLE;
   extern CLASS_IMPORT I_CHAR * const PROD_PORTFOLIO_RELATED_FIELDS_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const CHANGE_REPS_IS_NOT_APPLICABLE;//P0186486FN09 - Employee and Agent Account Gap#8A
   extern CLASS_IMPORT I_CHAR * const COMPENSATION_AGENT_MUST_BE_CHANGED;
   extern CLASS_IMPORT I_CHAR * const DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern CLASS_IMPORT I_CHAR * const DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
   extern CLASS_IMPORT I_CHAR * const SRVCE_AGENT_BELONGS_TO_FUNDSERV_BROKER;
   extern CLASS_IMPORT I_CHAR * const REG_DOC_STATUS_NEEDS_TO_BE_MANUALLY_UPDATED;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_ATTATCHED_TFR_NEED_TO_BE_STOPPED;
   extern CLASS_IMPORT I_CHAR * const SERVICE_ONLY_SALES_REP;
   extern CLASS_IMPORT I_CHAR * const SALE_REP_IS_NOT_ELIGIBLE_FOR_FUND_CLASS;
   extern CLASS_IMPORT I_CHAR * const BROKER_IS_NOT_ELIGIBLE_FOR_FUND_CLASS;
   extern CLASS_IMPORT I_CHAR * const ACCT_NOT_ELIGIBLE_MONEY_IN_AGE_LESS_THAN_MINIMUM;
   extern CLASS_IMPORT I_CHAR * const PIM_INST_ACCT_MUST_BE_ADDED_TO_CUSTODIAN;
   extern CLASS_IMPORT I_CHAR * const UNREVERSED_TERMINATION_ENTRIES_EXIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId GroupCode;
   extern CLASS_IMPORT const BFTextFieldId DefaultGrp;
   extern CLASS_IMPORT const BFTextFieldId rxGroupCode;
   extern CLASS_IMPORT const BFTextFieldId GroupType;
   extern CLASS_IMPORT const BFTextFieldId MorganAcctTypeForX;
   extern CLASS_IMPORT const BFTextFieldId MorganAcctTypeForT;
   extern CLASS_IMPORT const BFTextFieldId MorganTaxType;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForRep;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForMail;
   extern CLASS_IMPORT const BFDecimalFieldId MinFndClsBal;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId EscrowFund;
   extern CLASS_IMPORT const BFTextFieldId EscrowClass;
   extern CLASS_IMPORT const BFDateFieldId EscrowDeff;
   extern CLASS_IMPORT const BFDateFieldId EscrowStopDate;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFDecimalFieldId AmtAssigned;
   extern CLASS_IMPORT const BFTextFieldId GICallowed;
   extern CLASS_IMPORT const BFTextFieldId FundType;
   extern CLASS_IMPORT const BFTextFieldId AccountTypes;
   extern CLASS_IMPORT const BFTextFieldId InitPurch;
   extern CLASS_IMPORT const BFTextFieldId SettledFieldsInitialized;
   extern CLASS_IMPORT const BFDateFieldId DofBirth;
   extern CLASS_IMPORT const BFDateFieldId DofDeath;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForSWPStop;
   extern CLASS_IMPORT const BFTextFieldId SWPallowed;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeAcctType;
   extern CLASS_IMPORT const BFTextFieldId BrokerClrFirmAgtFirmTPA;
   extern CLASS_IMPORT const BFTextFieldId ClrFirmAgtFirmTPA;
   extern CLASS_IMPORT const BFTextFieldId AgentTPA;
   extern CLASS_IMPORT const BFTextFieldId MaximumApplies;
   extern CLASS_IMPORT const BFTextFieldId DuplicateAltAcct;
   extern CLASS_IMPORT const BFTextFieldId SortBy;
   extern CLASS_IMPORT const BFTextFieldId SrchAltAcct;
   extern CLASS_IMPORT const BFTextFieldId SrchBroker;
   extern CLASS_IMPORT const BFTextFieldId TaxTypePensionJuris;
   extern CLASS_IMPORT const BFTextFieldId MarginEligible;
   extern CLASS_IMPORT const BFTextFieldId RestrictAMSBroker;
   extern CLASS_IMPORT const BFTextFieldId FundAllow;
   extern CLASS_IMPORT const BFTextFieldId SummitAccountsLowerBound;
   extern CLASS_IMPORT const BFTextFieldId SummitAccountsUpperBound;
   extern CLASS_IMPORT const BFTextFieldId ResProvCode;
   extern CLASS_IMPORT const BFTextFieldId DefaultAllocOverride;
   extern CLASS_IMPORT const BFTextFieldId ExclDTAAccountType;
   extern CLASS_IMPORT const BFTextFieldId DefaultSTTRFlag;
   extern CLASS_IMPORT const BFTextFieldId DefaultERFlag;
   extern CLASS_IMPORT const BFTextFieldId FileTypeD;
   extern CLASS_IMPORT const BFTextFieldId ClearingIdDefault;
   extern CLASS_IMPORT const BFTextFieldId RelatedToClrFirm;
   extern CLASS_IMPORT const BFTextFieldId ActiveOnly;
   extern CLASS_IMPORT const BFTextFieldId AcctCategory;
   extern CLASS_IMPORT const BFTextFieldId ActCatNegBal;

   extern CLASS_IMPORT const BFTextFieldId ValidNetworkType;
   extern CLASS_IMPORT const BFTextFieldId ConsolTransType;
   extern CLASS_IMPORT const BFTextFieldId Consolidation;
   extern CLASS_IMPORT const BFTextFieldId ConsolDefault;
   extern CLASS_IMPORT const BFTextFieldId PurchNetting;

   extern CLASS_IMPORT const BFTextFieldId SettlementRuleExist;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeScheduleApplicable;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeTaxTypeSchedule;
   extern CLASS_IMPORT const BFTextFieldId EligExtTrfGainLoss;
   extern CLASS_IMPORT const BFTextFieldId CSSStopSINMatch;
   extern CLASS_IMPORT const BFTextFieldId IdType;
   extern CLASS_IMPORT const BFTextFieldId IdValue;
   extern CLASS_IMPORT const BFTextFieldId StopReason;
   extern CLASS_IMPORT const BFTextFieldId AdditionalStopReason;
   extern CLASS_IMPORT const BFDateFieldId DofDeathNotice;
   extern CLASS_IMPORT const BFTextFieldId AlwdTaxType;
   extern CLASS_IMPORT const BFTextFieldId DirectDepositBankApplicable;
   extern CLASS_IMPORT const BFTextFieldId CESGEligible;
   extern CLASS_IMPORT const BFTextFieldId SiblingOnly;
   extern CLASS_IMPORT const BFTextFieldId Pre98Contrib;
   extern CLASS_IMPORT const BFTextFieldId QESIClient;
   extern CLASS_IMPORT const BFTextFieldId RESPReportHRDC;
   extern CLASS_IMPORT const BFTextFieldId GrandFathered;
   extern CLASS_IMPORT const BFTextFieldId BrokerCategoryList;
   extern CLASS_IMPORT const BFTextFieldId GuaranteeGuardOn;
   extern CLASS_IMPORT const BFTextFieldId EPABroker;
   extern CLASS_IMPORT const BFTextFieldId TFSAAcctCatCodeList;
   extern CLASS_IMPORT const BFTextFieldId RRSPAcctCatCodeList;
   extern CLASS_IMPORT const BFTextFieldId TFSALastAmendTaxYear;
   extern CLASS_IMPORT const BFDateFieldId DeathSettlementDate;
   extern CLASS_IMPORT const BFTextFieldId ProdPortfolioUUID;
   extern CLASS_IMPORT const BFTextFieldId ProdPortfolioPlanUUID;
   extern CLASS_IMPORT const BFTextFieldId PortfolioPlanName;
   extern CLASS_IMPORT const BFTextFieldId DefaultPlan;
   extern CLASS_IMPORT const BFTextFieldId PortfolioName;   
   extern CLASS_IMPORT const BFTextFieldId IWTTaxJurisList; 
   extern CLASS_IMPORT const BFTextFieldId TaxJuris;   
   extern CLASS_IMPORT const BFTextFieldId TaxExType;   
   extern CLASS_IMPORT const BFTextFieldId PorfolioIsRequried;
   extern CLASS_IMPORT const BFTextFieldId hasERISAProhibitedFund;
   extern CLASS_IMPORT const BFTextFieldId FundRelnCode;//P0186486FN09 - Employee and Agent Account Gap#8A
   extern CLASS_IMPORT const BFTextFieldId GuaranteeCalcByRules;
   extern CLASS_IMPORT const BFTextFieldId FundServBroker;
   extern CLASS_IMPORT const BFTextFieldId BrokerBranchRepXEdit;
   extern CLASS_IMPORT const BFTextFieldId PortfolioXEdit;
   extern CLASS_IMPORT const BFTextFieldId FundEligSlsRepLvl;
   extern CLASS_IMPORT const BFTextFieldId ValidationPassed;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeRuleCurrSet;
   extern CLASS_IMPORT const BFTextFieldId RegAgentCode;
   extern CLASS_IMPORT const BFTextFieldId FundSERVValidation;
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
   extern CLASS_IMPORT const BFDateFieldId TaxableTrustDate;
   extern CLASS_IMPORT const BFTextFieldId ServiceAgentUpdated;

   extern CLASS_IMPORT const BFDateFieldId InitialDate;
   extern CLASS_IMPORT const BFDecimalFieldId InitialMarketValue;
   extern CLASS_IMPORT const BFDecimalFieldId NetTransAmt;
   extern CLASS_IMPORT const BFDateFieldId NetTransAmtAsOfDate;
   extern CLASS_IMPORT const BFTextFieldId InitDateNetTransAmtAsOfXEdit;
   extern CLASS_IMPORT const BFTextFieldId MstrActAttrbName;
   extern CLASS_IMPORT const BFTextFieldId MstrActAttrbValue;
   extern CLASS_IMPORT const BFTextFieldId MstrActActive;
   extern CLASS_IMPORT const BFTextFieldId AcctRegulatoryExist;
   extern CLASS_IMPORT const BFTextFieldId AutoDocTracking;
   extern CLASS_IMPORT const BFTextFieldId TfrClass;
   extern CLASS_IMPORT const BFTextFieldId TfrFund;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId Cancelled;
   extern CLASS_IMPORT const BFTextFieldId MgmtFeePayOptOvd;
   extern CLASS_IMPORT const BFTextFieldId PrintAcctConf;
   extern CLASS_IMPORT const BFTextFieldId TFRExists;
   extern CLASS_IMPORT const BFTextFieldId TFRApplicable;
   extern CLASS_IMPORT const BFTextFieldId SlsrepType;
   extern CLASS_IMPORT const BFTextFieldId MoneyInExist;
   extern CLASS_IMPORT const BFTextFieldId RegDocStatus;
   extern CLASS_IMPORT const BFTextFieldId NotApplicable;
   extern CLASS_IMPORT const BFTextFieldId AlertViewed;
   extern CLASS_IMPORT const BFTextFieldId AlertCode;
   extern CLASS_IMPORT const BFTextFieldId ReqAcctCustodian;
   extern CLASS_IMPORT const BFTextFieldId AccountClosingReasonRDSP;
   extern CLASS_IMPORT const BFTextFieldId DistrAcctTypeDetl;
}

namespace ACCOUNT_GROUPING
{
   const long ACCOUNT_INFO       = 0x0001;
   const long ACCOUNT_AMS        = 0x0002;
   const long ACCOUNT_RESP_INFO  = 0x0004;
   const long VALUE_VARIATION    = 0x0008;
}

namespace ALERT_MSG_CODE
{
    extern CLASS_IMPORT I_CHAR * const REMARK_ALERT;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AMS_MIX_OVERRIDE;
   extern CLASS_IMPORT I_CHAR * const PORTFOLIO_SETUP;
   extern CLASS_IMPORT I_CHAR * const UNCLM_REMIT_DATE_UPDATE;   
}

namespace PAYMENT_FOR
{
   extern const I_CHAR * DISTRIBUTION;
   extern const I_CHAR * REDEMPTION;
}

namespace ACCOUNT_CATEGORY
{
   extern I_CHAR * const PRIVATE;
   extern I_CHAR * const EPA_APP;
}

namespace REG_AGENT_TAX_TYPE
{
	const I_CHAR * const ORD_ACC = I_("OA"); 
	const I_CHAR * const SPL_ACC = I_("SA");
	const I_CHAR * const SRS_ACC = I_("SR"); 
}

namespace ACCOUNT_TYPE
{
 const I_CHAR * const INDIVIDUAL_ACCT_TYPE           = I_( "0" ); 
 const I_CHAR * const SPOUSAL_ACCT_TYPE              = I_( "1" ); 
 const I_CHAR * const JOINT_ACCT_TYPE                = I_( "2" ); 
 const I_CHAR * const CORPORATE_ACCT_TYPE            = I_( "4" );
 const I_CHAR * const TRUST_ACCT_TYPE                = I_( "3" );
}
namespace INV_CLASSIFICATION
{
 const I_CHAR * const RETAIL           = I_( "RETL" ); 
 const I_CHAR * const PROFESSIONAL     = I_( "PROF" );
}
namespace TAX_MODEL
{
 const I_CHAR * const NOT_APPLICABLE             = I_( "00" );
 const I_CHAR * const INDIVIDUAL_TAX_MODEL       = I_( "01" ); 
 const I_CHAR * const CORPORATE_TAX_MODEL        = I_( "02" );
 const I_CHAR * const SUPERANN_TAX_MODEL         = I_( "03" );
 const I_CHAR * const TRUST_TAX_MODEL            = I_( "04" );

}
namespace TRADETYPE // See:  ifastids/ifastradeids.cpp
{
 extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE; 
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,                       State Flags,            Group Flags 
    { ifds::ShrNum,                   BFCBO::REQUIRED,             0 },
    { ifds::AccountNum,               BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::BeneficialOwner,          BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::AcctType,                 BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::TaxType,                  BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::RecipientType,            BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::Currency,                 BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::BrokerCode,               BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::BranchCode,               BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::Slsrep,                   BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::AcctStatus,               BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::DateOfReg,                BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::PensionJuris,             BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::MarketMail,               BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::EffectiveDate,            BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::AltAccount,               BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    //{ ifds::AMSCode,                  BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_AMS },
    //{ ifds::AMSROCode,                BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_AMS },
    //{ ifds::Rebalance,                BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_AMS },
    //{ ifds::UpdatePACSWP,             BFCBO::REQUIRED,             ACCOUNT_GROUPING::ACCOUNT_AMS },
    { ifds::PensionLegCode,           BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::FeeModelCode,             BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },

    { ifds::ClientAMSType,            BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_AMS },
    { ifds::RegistrationInfo,         BFCBO::NONE,                 0 }, 


    //these fields are here for beingable to retrieve them from view#90,#91,#92
    { ifds::BrokerName,               BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::BranchName,               BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::SlsrepName,               BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::SlsrepAltName,            BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },

    { ifds::AcctGroup,                BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::AcctGroupName,            BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },

    { ifds::LockedIn,                 BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::InterCode,                BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO }, //in1405052
    //signals GUI that it should ask if the rep should be added
    { ifds::ShouldAskForRep,          BFCBO::NONE,                 0 },
    { ifds::ShouldAskForMail,         BFCBO::NONE,                 0 },

    { ifds::AccountNumManual,         BFCBO::NONE,                 0 },
    { ifds::XrefNum,                  BFCBO::NONE,                 0 },
    { ifds::InterAccount,             BFCBO::NONE,                 0 },
    { ifds::RRSPFee,                  BFCBO::NONE,                 0 },
    { ifds::StopPurchase,             BFCBO::NONE,                 0 },
    { ifds::StopXferIn,               BFCBO::NONE,                 0 },
    { ifds::StopXferOut,              BFCBO::NONE,                 0 },
    { ifds::StopRed,                  BFCBO::NONE,                 0 },
    { ifds::FeeWaived,                BFCBO::NONE,                 0 },
    { ifds::Unseizable,               BFCBO::NONE,                 0 },
    { ifds::RegCompleted,             BFCBO::NONE,                 0 },
    { ifds::SupConf,                  BFCBO::NONE,                 0 },
    { ifds::SupEmpConf,               BFCBO::NONE,                 0 },
    { ifds::InTrustFor,               BFCBO::NONE,                 0 },
    { ifds::Escrow,                   BFCBO::NONE,                 0 },
    { ifds::AcctMstrVer,              BFCBO::NONE,                 0 },
    { ifds::AcctMstrRid,              BFCBO::NONE,                 0 },
    { ifds::AcctDesignation,          BFCBO::NONE,                 0 },
    { ifds::AccountBalance,           BFCBO::NONE,                 0 },
    { ifds::Username,                 BFCBO::NONE,                 0 },
    { ifds::ModDate,                  BFCBO::NONE,                 0 },
    { ifds::ModUser,                  BFCBO::NONE,                 0 },
    { ifds::Employee,                 BFCBO::NONE,                 0 },
    { ifds::TaxTypeSchedule,          BFCBO::NONE,                 0 },
    { ifds::AddAcctFlag,              BFCBO::NONE,                 0 },
    { ifds::MarketMailChgSh,          BFCBO::NONE,                 0 },                              
    { ifds::CreateRep,                BFCBO::NONE,                 0 },                              
    { ifds::TransFound,               BFCBO::NONE,                 0 },                              
    { ifds::ExistBeneficiary,         BFCBO::NONE,                 0 },                              
    { ifds::ExistAssignee,            BFCBO::NONE,                 0 },                              
    { ifds::ContractExist,            BFCBO::NONE,                 0 },                              
    { ifds::SocialCode,               BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },                              
    { ifds::StopFCrebal,              BFCBO::NONE,                 0 },                              
    { ifds::GSTExempt,                BFCBO::NONE,                 0 },                              
    { ifds::ApplyPST,                 BFCBO::NONE,                 0 },                              
    { ifds::BankChrgs,                BFCBO::NONE,                 0 },                              
    { ifds::ConsolidEFT,              BFCBO::NONE,                 0 },                              
    { ifds::AcctPurpose,              BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO }, 
    { ifds::BusinessNo,               BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO }, 
    { ifds::AdditionalInfo,           BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO }, 
    { ifds::TelFaxAgreement,          BFCBO::NONE,                 0 },                              
    { ifds::HoldDivPymt,              BFCBO::NONE,                 0 },                              

    //filters for substitutions values
    { ifds::MorganAcctTypeForX,       BFCBO::NONE,                 0 },                              
    { ifds::MorganAcctTypeForT,       BFCBO::NONE,                 0 },                              
    { ifds::MorganTaxType,            BFCBO::NONE,                 0 },                              
    //COA flags
    { ifds::PendingTrade,             BFCBO::CALCULATED_FIELD,     0 },                              
    { ifds::Certificates,             BFCBO::CALCULATED_FIELD,     0 },                              
    { ifds::SystemTrsfr,              BFCBO::CALCULATED_FIELD,     0 },                              
    { ifds::LSIFPAC,                  BFCBO::CALCULATED_FIELD,     0 },
    { ifds::PAC,                      BFCBO::CALCULATED_FIELD,     0 },
    { ifds::SWP,                      BFCBO::CALCULATED_FIELD,     0 },
    { ifds::AcctAlloc,                BFCBO::CALCULATED_FIELD,     0 },
    { ifds::ClanPlan,                 BFCBO::CALCULATED_FIELD,     0 },
    { ifds::UnsettledTrn,             BFCBO::CALCULATED_FIELD,     0 },
    { ifds::SavePlanExist,            BFCBO::CALCULATED_FIELD,     0 },
    { ifds::PensionJurisExists,       BFCBO::CALCULATED_FIELD,     0 },

    { ifds::SettledFieldsInitialized, BFCBO::NONE,                 0 }, //PLEASE do not call setField or setFieldNoValidate against this field in MFAccount.cpp .
    { ifds::SettledValue,             BFCBO::NONE,                 0 },                              
    { ifds::UnsettledValue,           BFCBO::NONE,                 0 },                              
    { ifds::AcctFeesExist,            BFCBO::NONE,                 0 },                              
    { ifds::SettleLocExist,           BFCBO::NONE,                 0 },                              
    { ifds::ClearingID,               BFCBO::NONE,                 0 },                              
    { ifds::ClearingFirm,             BFCBO::NONE,                 0 }, // NSCC enhancement
    { ifds::AgentForFirm,             BFCBO::NONE,                 0 }, // NSCC enhancement
    { ifds::TPA,                      BFCBO::NONE,                 0 }, // NSCC enhancement
    { ifds::ParticipantID,            BFCBO::NONE,                 0 }, // NSCC enhancement
    { ifds::NSCCSocialCode,           BFCBO::NONE,                 0 },

    { ifds::Networkcontrolind,        BFCBO::NONE,                 0 },                              
    { ifds::FirstEffective,           BFCBO::NONE,                 0 }, 

    { ifds::NetworkID,                BFCBO::NONE,                 0 },

    { ifds::StopSWP,                  BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::ShouldAskForSWPStop,      BFCBO::NONE,                 0 },                             
    { ifds::TaxTypeAcctType,          BFCBO::IMMEDIATE_VALIDATION, ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::TaxTypePensionJuris,      BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::TaxTypeTaxTypeSchedule,   BFCBO::IMMEDIATE_VALIDATION, ACCOUNT_GROUPING::ACCOUNT_INFO },

    // NSCC broker cross edit
    //{ ifds::ClrFirmAgtFirmTPA,        BFCBO::NONE,               ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::BrokerClrFirmAgtFirmTPA,  BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    //{ ifds::AgentTPA,               BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    // pay fee options 
    { ifds::MgmtFeePayOption,         BFCBO::REQUIRED,             0},

    //{ ifds::AMSType,                BFCBO::CALCULATED_FIELD,     ACCOUNT_GROUPING::ACCOUNT_AMS},

    // Early redemtion fee
    { ifds::ChargeERFee,              BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::ChargeSTTRFee,            BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },

    { ifds::AcctCategoryExist,        BFCBO::NONE,                 0}, 
    { ifds::StopAMSRebalancing,       BFCBO::NONE,                 0 },
    { ifds::StopRedSettle,            BFCBO::NONE,                 0 },
    { ifds::MaxApplies,               BFCBO::NONE,                 0 },
    { ifds::FedJurisAllowed,          BFCBO::NONE,                 0 },
    { ifds::PlanType,                 BFCBO::NONE,                 0 },
    { ifds::SelfDirected,             BFCBO::NONE,                 0 },
    { ifds::ActiveOnly,               BFCBO::CALCULATED_FIELD,     0 },
    { ifds::ConsolTypePW,             BFCBO::NONE,                 0 },
    { ifds::ConsolTypeID,             BFCBO::NONE,                 0 },
    { ifds::AccountClosingReason,     BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::Affluent,                 BFCBO::NONE,                 0 },

    //Active Certificate Check
    { ifds::ActiveCert,               BFCBO::NONE,                 0 },

    { ifds::SettlementRuleExist,      BFCBO::NONE,                 0 },
    { ifds::StopReason,               BFCBO::NONE,                 0 },
    { ifds::AdditionalStopReason,     BFCBO::NONE,                 0 },
    { ifds::DocListExists,            BFCBO::NONE,                 0 },
    
    //QESI
    { ifds::CESGEligible,             BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_RESP_INFO },
    { ifds::SiblingOnly,              BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_RESP_INFO },
    { ifds::Pre98Contrib,             BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_RESP_INFO },
    { ifds::GrandFathered,            BFCBO::NONE,                 0 },
    { ifds::AIPWithdrawalExists,      BFCBO::NONE,                 0 },
    { ifds::ConsolTypeED,             BFCBO::NONE,                 0 },

    // Product portfolio
    { ifds::ProdPortfolioUUID,        BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::ProdPortfolioPlanUUID,    BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::PortfolioPlanName,        BFCBO::NONE,                 0 },
    { ifds::DefaultPlan,              BFCBO::NONE,                 0 },
    { ifds::PortfolioName,            BFCBO::NONE,                 0 },  
    { ifds::UnclmRemitDate,           BFCBO::NONE,                 0 },  
    { ifds::OrgType,                  BFCBO::NONE,                 0 },  
    { ifds::SubOrgType,               BFCBO::NONE,                 0 },  
    { ifds::CommitmentStatus,         BFCBO::NONE,                 0 },  
    { ifds::NonFinConfirm,            BFCBO::NONE,                 0 },  
    { ifds::SettleCurrency,           BFCBO::NONE,                 0 },  
    { ifds::BrokerBranchRepXEdit,     BFCBO::IMMEDIATE_VALIDATION, ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::PortfolioXEdit,           BFCBO::IMMEDIATE_VALIDATION, ACCOUNT_GROUPING::ACCOUNT_INFO },
    { ifds::StopAdjDate,              BFCBO::NONE,                 ACCOUNT_GROUPING::ACCOUNT_INFO },//P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
    { ifds::ServiceAgentUpdated,      BFCBO::NOT_ON_HOST,          0 },
    { ifds::TaxableTrustDate,         BFCBO::NONE,                 0 },  
    { ifds::ExemptPeriod,             BFCBO::NONE,                 0 },  
    { ifds::ShrOutputType,            BFCBO::NONE,                 0 },  

	{ ifds::InitialDate,              BFCBO::NONE,                 ACCOUNT_GROUPING::VALUE_VARIATION},  
	{ ifds::InitialMarketValue,       BFCBO::NONE,                 ACCOUNT_GROUPING::VALUE_VARIATION },  
	{ ifds::NetTransAmt,              BFCBO::NONE,                 ACCOUNT_GROUPING::VALUE_VARIATION },  
	{ ifds::NetTransAmtAsOfDate,      BFCBO::NONE,                 ACCOUNT_GROUPING::VALUE_VARIATION },  
	{ ifds::InitDateNetTransAmtAsOfXEdit, BFCBO::IMMEDIATE_VALIDATION, ACCOUNT_GROUPING::VALUE_VARIATION},
	{ ifds::AnnuitantYoungerAge,      BFCBO::NONE,                 0 },  
    { ifds::InvestorClassification,   BFCBO::NONE,                 0 }, 
    { ifds::AIFMDInvestorCategory,    BFCBO::NONE,                 0 },
	{ ifds::SlsrepType,               BFCBO::NONE,				   0 },
    { ifds::AggregationType,          BFCBO::NONE,                 0 },
    { ifds::MoneyInExist,             BFCBO::NONE,                 0 },
	{ ifds::AcctTaxModel,             BFCBO::NONE,                 0 },
	{ ifds::TermEntryExist,           BFCBO::NONE,                 0 },
	{ ifds::AccountClosingReasonRDSP, BFCBO::NONE,                 0 },
	{ ifds::DistrAcctTypeDetl,        BFCBO::NONE,                 0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
    //  Object Label,                    State Flags,      Group Flags 
    { I_( "MFAccountHoldingList" ),      BFCBO::NONE,            0},
    { I_( "TransactionList" ),           BFCBO::NONE,            0},
    { I_( "AllTransactionList" ),        BFCBO::NONE,            0},
    { I_( "PendingTradeList" ),          BFCBO::NONE,            0},
    { I_( "SystematicList" ),            BFCBO::NONE,            0},
    { I_( "AccountDistributionList" ),   BFCBO::NONE,            0},
    { I_( "AccountTradesList" ),         BFCBO::NONE,            0},
    { I_( "AccountReviewList" ),         BFCBO::NONE,            0},
    { I_( "HypoRedCriteria" ),           BFCBO::NOT_ON_HOST,     0},
    { I_( "AcctLvlSttlmntRuleList" ),    BFCBO::NONE,            0},
	{ I_( "AcctRoundingRuleList" ),		 BFCBO::NONE,            0},
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
MFAccount::MFAccount( BFAbstractCBO &parent ) 
: MFCanBFCbo (parent),
_pResponseData (NULL),
_bRefresh (false),
_dstrHouseBroker (NULL_STRING)
,_pGroupList(NULL)
,_pAcctEntityXref(NULL)
,_pShareholder(NULL)
,_pIntermediaryList(NULL)
,_pErrMsgRulesList(NULL)
,_pFundDetailList(NULL)
,_salesRepByBranch( NULL_STRING)
,_strLIPRateExist( NULL_STRING )
,_grpCodeLevel( NULL_STRING )
,_bStopReasonChanged (false)
,_dstrRegStandard (NULL_STRING)
,_recipientTypeSubstList (NULL_STRING)
,_dstrTAKey (NULL_STRING)
,_serviceAgentUpdated (NULL_STRING)
,_pCOANavig(NULL)
,_alertViewed(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo );

   addCrossEdit(ifds::TaxTypeAcctType, ifds::TaxType); 
   addCrossEdit(ifds::TaxTypeAcctType, ifds::AcctType); 

   addCrossEdit(ifds::TaxTypePensionJuris, ifds::TaxType);
   addCrossEdit(ifds::TaxTypePensionJuris, ifds::PensionJuris);

   addCrossEdit(ifds::TaxTypeTaxTypeSchedule, ifds::TaxType);
   addCrossEdit(ifds::TaxTypeTaxTypeSchedule, ifds::TaxTypeSchedule);
   addCrossEdit(ifds::TaxTypeTaxTypeSchedule, ifds::EffectiveDate);
   addCrossEdit(ifds::TaxTypeTaxTypeSchedule, ifds::PensionJuris);

   addCrossEdit(ifds::BrokerClrFirmAgtFirmTPA, ifds::BrokerCode);
   addCrossEdit(ifds::BrokerClrFirmAgtFirmTPA, ifds::ClearingFirm);
   addCrossEdit(ifds::BrokerClrFirmAgtFirmTPA, ifds::AgentForFirm);
   addCrossEdit(ifds::BrokerClrFirmAgtFirmTPA, ifds::TPA);  

   addCrossEdit(ifds::BrokerBranchRepXEdit, ifds::BrokerCode);
   addCrossEdit(ifds::BrokerBranchRepXEdit, ifds::BranchCode);
   addCrossEdit(ifds::BrokerBranchRepXEdit, ifds::Slsrep);

   addCrossEdit(ifds::PortfolioXEdit, ifds::ProdPortfolioUUID);
   addCrossEdit(ifds::PortfolioXEdit, ifds::ProdPortfolioPlanUUID);

   addCrossEdit(ifds::InitDateNetTransAmtAsOfXEdit, ifds::InitialDate);
   addCrossEdit(ifds::InitDateNetTransAmtAsOfXEdit, ifds::NetTransAmtAsOfDate);
//to get the default recipient type susbstitution set....
   BFProperties *pProperties = 
      getFieldProperties (ifds::RecipientType, BF::HOST);

   if (pProperties)
   {
      pProperties->getAllSubstituteValues (_recipientTypeSubstList);
   }   
}

//******************************************************************************
MFAccount::~MFAccount()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( _pResponseData )
      delete _pResponseData;
   if(_pCOANavig)
      delete _pCOANavig;
}

//******************************************************************************
SEVERITY MFAccount::init( const BFDataGroupId& idDataGroup, const DString& accountNum, const DString& shrNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( int )" ) );

   //load the account object with default values taken from the datadictionary
   initWithDefaultValues( idDataGroup ); 	

   DString groupCodeLevel ;
   groupCodeLevel = getGrpCodeLevel (idDataGroup);

   //get the shareholder
   Shareholder* pShareholder;

   // have to use this logic because shrNum has not yet been committed
   if( getWorkSession().getShareholder( idDataGroup, shrNum, pShareholder ) <= WARNING )
   {
      //no need to validate this    onchar
      setFieldNoValidate( ifds::ShrNum, shrNum, idDataGroup, true, true );
      if( setFieldNoValidate( ifds::AccountNum, accountNum, idDataGroup, false, true ) <= WARNING )
      {
         _initAccountNum = accountNum;
      }

      //deal with default values taken from the configuration
      DString mktMailDef, sysCurrency;

      //set the default for market mail
      if( getWorkSession().getOption( ifds::MktMailDef, mktMailDef, idDataGroup ) <= WARNING )
      {
         setFieldNoValidate( ifds::MarketMail, mktMailDef, idDataGroup, true, true );
      }
      //set the default for the currency
      if( getWorkSession().getOption( ifds::SysCurrency, sysCurrency, idDataGroup ) <= WARNING )
      {
         setFieldNoValidate( ifds::Currency, sysCurrency, idDataGroup, true );
      }

      DString acctGroupCode;
      if( groupCodeLevel == SHAREHOLDER_GROUP_LEVEL ) //get the group code from the shareholder
      {
         pShareholder->getField( ifds::GroupCode, acctGroupCode, idDataGroup, false );
         setFieldNoValidate( ifds::AcctGroup, acctGroupCode, idDataGroup, false, true );
      }
      else if( groupCodeLevel == ACCOUNT_GROUP_LEVEL )
      {
         loadGroupSubstitutionList( idDataGroup );
         if( getWorkSession().getOption( ifds::DefaultGrp, acctGroupCode, idDataGroup ) <= WARNING )
         {
            setFieldNoValidate( ifds::AcctGroup, acctGroupCode, idDataGroup, true, true );
         }
      }
      else
      {
         ADDCONDITIONFROMFILE( CND::ERR_GROUP_CODE_LEVEL );
      }

      //Set MFAccount Acct Designation
      // Rule: load the intermediary code list as a substitution list if the acctDesignation=3
      setAccountDesignation( idDataGroup );

      //the business rule is:
      //if accNumCtrl is M the user HAS TO ENTER a value
      //if is C or S the user might enter a value,
      //otherwise we should generate a number
      DString accNumCtrl;

      if( getWorkSession().getOption( ifds::AcctNumCtrl, accNumCtrl, idDataGroup ) <= WARNING )
      {
         if( accNumCtrl != I_( "M" ) && accNumCtrl != I_( "m" ) )
         {
            setFieldReadOnly( ifds::AccountNum,idDataGroup,true );
         }
      }

      //initializing the effective date & 
      //initializing the date of registration

      DString currBussinesDate;
      if( getWorkSession().getOption( ifds::CurrBusDate, currBussinesDate, idDataGroup, false ) <= WARNING )
      {
         setFieldNoValidate( ifds::DateOfReg, currBussinesDate, idDataGroup, false, true, true );

//         setFieldNoValidate( DBR::EffectiveDate, currBussinesDate, idDataGroup, false, true, true );
         DString dstrEffecDate( currBussinesDate );
         if( pShareholder && pShareholder->isNew() )
         {
            pShareholder->getField(ifds::EffectiveDate, dstrEffecDate, idDataGroup, false);
         }
         setFieldNoValidate( ifds::EffectiveDate, dstrEffecDate, idDataGroup, false, true, true );
         setFieldNoValidate( ifds::FirstEffective, dstrEffecDate, idDataGroup, false );
//         _initEffectiveDate = currBussinesDate;
         _initEffectiveDate = dstrEffecDate;
      }
/*
      //defaults for TaxType for Morgan
      if( DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN )
      {
         setFieldSubstituteValues( DBR::TaxType, idDataGroup, DBR::MorganTaxType );
      }
*/
      //deal with the broker code, branch code, agent code group 
      if( pShareholder->isNew() )
      {
         GroupList* pGroupList;

         if( acctGroupCode != NULL_STRING )
         {
            if( getGroupList( pGroupList ) <= WARNING )
            {
               BFObjIter glIter( *pGroupList, idDataGroup );

               for( glIter.begin(); !glIter.end(); ++glIter )
               {
                  DString iterGroupCode;

                  glIter.getObject()->getField( ifds::rxGroupCode, iterGroupCode, idDataGroup );
                  if( iterGroupCode == acctGroupCode )
                  {
                     DString groupType, groupName = NULL_STRING;

                     glIter.getObject()->getField( ifds::GroupType, groupType, idDataGroup );
                     glIter.getObject()->getField( ifds::GroupName, groupName, idDataGroup, false );

                     if( isNew () )
                     {
                        //set the field DBR::AcctGroupName to be used in Dlg
                        setFieldNoValidate( ifds::AcctGroupName, groupName, idDataGroup, false, true );
                     }

                     if( groupType == I_( "00" ) )
                     {
                        DString brokerCode, 
                           branchCode, 
                           slsrepCode;

                        if (pShareholder->isNew())
                        {
                           Broker* pBroker (NULL);
                           
                           glIter.getObject()->getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
                           if ( getBroker (pBroker, brokerCode, idDataGroup) <= WARNING && 
                                pBroker) 
                           {
                              _dstrHouseBroker = pBroker->isHouseBroker ( idDataGroup )?YES:NO;
                           }
                           if ( _dstrHouseBroker == NO ) {
                              glIter.getObject()->getField( ifds::BranchCode, branchCode, idDataGroup, false );
                              glIter.getObject()->getField( ifds::SalesRepCode, slsrepCode, idDataGroup, false );
                              setFieldNoValidate( ifds::BrokerCode, brokerCode, idDataGroup, false, false );                        
                              if( slsRepByBranch ( idDataGroup ) ) {
                                 setFieldNoValidate( ifds::BranchCode, branchCode, idDataGroup, false, false );
                              }else {
                                 setFieldNoValidate( ifds::BranchCode, branchCode, idDataGroup, false, true );
                              }
                              setFieldNoValidate( ifds::Slsrep, slsrepCode, idDataGroup, false, false );
                           }
//                           setValidFlag(ifds::BrokerCode, idDataGroup, false);

                           /*if( slsRepByBranch ( idDataGroup ) ) {
                              setValidFlag(ifds::BranchCode, idDataGroup, false);
                           }*/
                           //setValidFlag(ifds::Slsrep, idDataGroup, false);
                           
/*
                           if( brokerCode != NULL_STRING )
                           {
                              checkBroker( brokerCode, idDataGroup, false );
                              setFieldNoValidate( ifds::BrokerCode, brokerCode, idDataGroup, false, true );                        
                           }
                           if( branchCode != NULL_STRING )
                           {
                              checkBranches( branchCode, idDataGroup, false );
                              setFieldNoValidate( ifds::BranchCode, branchCode, idDataGroup, false, true );
                           }
                           if( slsrepCode != NULL_STRING )
                           {
                              bool bNewAgent;
                              checkAgents( slsrepCode, idDataGroup, false, bNewAgent );
                              setFieldNoValidate( ifds::Slsrep, slsrepCode, idDataGroup, false, true );
                           }*/
                        }

                        break;
                     }
                  }
               }
            }
         }
      }
      //attach this account to the list of MFAccounts
      pShareholder->attachAccountToMFAccountList( this, idDataGroup );
      //P0186486FN09 - Employee and Agent Account Gap#8A
      pShareholder->setFeeWaivedforEmployAgent(idDataGroup);

      //Rule: if TaxType-76 <> "0" then RecipientType-76 = "0"
      //   else if AcctDesignation-75 = 2, 3 or 9 then RecipientType-76 = "4"
      //   else if AccType-76 = "2" then RecipientType-76 = "2"
      //   else if AcctType-76 = "4" then RecipientType = "3"
      //   else RecipientType-76 = "1".
      //   If TaxType-76 = C or L, then system automatically assign RecipientType-76 = '1' 
      //       and skip update of this fields (LIP product enhancement)
      DString strMarket = DSTCommonFunctions::getMarket();
      if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
      {
         DString strKey, dstrTaxType;
         DString lockedIn;
         getField( ifds::TaxType, dstrTaxType, idDataGroup );

         if( !isNew() )
         {
            if( getWorkSession ().isLIRALike (dstrTaxType) || dstrTaxType == LRIF_TAX_TYPE || 
                getWorkSession ().isLIFLike (dstrTaxType) ||  dstrTaxType == PRIF_TAX_TYPE )
            {
               setFieldReadOnly( ifds::RecipientType, idDataGroup, true );
            }
         }
         else if( strMarket == MARKET_IDS::LUXEMBOURG && dstrTaxType == NULL_STRING )  // default tax type to 'Non Register'
         {
            setFieldNoValidate( ifds::TaxType, NON_REGISTERED_TAX_TYPE, idDataGroup, false, true );
         }

         //        getField( DBR::LockedIn, lockedIn, idDataGroup );

         if( getWorkSession ().isLIFLike (dstrTaxType) || 
			 getWorkSession ().isLIRALike (dstrTaxType) || 
             dstrTaxType == LRIF_TAX_TYPE || dstrTaxType == PRIF_TAX_TYPE)
         {
            setFieldReadOnly( ifds::PensionJuris, idDataGroup, false );
            setValidFlag(ifds::PensionJuris, idDataGroup, false);
            /*if( !isNew() )
               setFieldReadOnly( DBR::RecipientType, idDataGroup, true );*/
         }
         else
         {
            setFieldReadOnly( ifds::PensionJuris, idDataGroup, true );     
         }
      }  // if CFDS 
   }

   // must be place after the setNoValidate or else it will set the state flag back to valid
   // validation must happen in case the default value is blank or invalid
   if( groupCodeLevel == ACCOUNT_GROUP_LEVEL )
   {
      //setFieldStateFlags( DBR::AcctGroup, idDataGroup, BFBase::STATE_FLAGS::REQUIRED );
      setValidFlag(ifds::AcctGroup, idDataGroup, false);

   }

   setFieldNoValidate( ifds::StopFCrebal, I_( "N" ), idDataGroup, false, true, true );
//   setFieldNoValidate( ifds::AMSCode, NULL_STRING, idDataGroup, false, true, false, false );   
	//setFieldNoValidate( DBR::GSTExempt, I_( "N" ), idDataGroup, false, true, true );

   setFieldNoValidate( ifds::HoldDivPymt, I_( "N" ), idDataGroup, false, true, true );

   if( isNew() )//we don't have a doInitWithDefaultValues for MFAccount !!??!!
   {
      DString str;
      if( getWorkSession().getOption( ifds::BankChrgs, str, BF::HOST, false ) <= WARNING )
         setFieldNoValidate(ifds::BankChrgs, str, idDataGroup, false);
      str = NULL_STRING;
      if( getWorkSession().getOption( ifds::ConsolidEFT, str, BF::HOST, false ) <= WARNING )
         setFieldNoValidate(ifds::ConsolidEFT, str, idDataGroup, false);
      str = NULL_STRING;
      if( getWorkSession().getOption( ifds::ClearingIdDefault, str, BF::HOST, false ) <= WARNING )
         setFieldNoValidate(ifds::ClearingID, str, idDataGroup, false);
      setFieldNoValidate(ifds::Affluent, I_("O"), idDataGroup, false); //not applicable

      // QESI      
      setFieldNoValidate( ifds::GrandFathered, I_("N"), idDataGroup, false );
   }

      //set the default for ChargeERFee and ChargeSTTRFee

   DString dstrDefaultERFlag, dstrDefaultSTTRFlag ;
  
   if( getWorkSession().getOption( ifds::DefaultERFlag, dstrDefaultERFlag, idDataGroup ) <= WARNING )
   {
      setFieldNoValidate( ifds:: ChargeERFee, dstrDefaultERFlag, idDataGroup, true, true );
   }

   if( getWorkSession().getOption( ifds::DefaultSTTRFlag, dstrDefaultSTTRFlag, idDataGroup ) <= WARNING )
   {
      setFieldNoValidate( ifds:: ChargeSTTRFee, dstrDefaultSTTRFlag, idDataGroup, true,true );
   }

   setFieldNoValidate( ifds::ShrOutputType, SHAREHOLDER_OUTPUT_FORMAT::REGULAR_PRINT, idDataGroup, false,true );

   initFieldsAndSubst( idDataGroup );
   checkForReadOnly( idDataGroup );
   clearUpdatedFlags( idDataGroup, false );
   loadSettleCurrencySubstitutionList(idDataGroup);
   addBlankToSubSet(ifds::AIFMDInvestorCategory, idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());
}     
//******************************************************************************
SEVERITY MFAccount::init( const BFData &refData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(int, BFData&)" ) );

   BFData* accCopy = new BFData( refData );
   attachDataObject( *accCopy, true, true );
   _initAccountNum = refData.getElementValue( ifds::AccountNum );
   _initAccountNum.stripLeading( '0' ).strip();
   _initEffectiveDate = refData.getElementValue( ifds::EffectiveDate );
   loadSettleCurrencySubstitutionList(BF::HOST);


   //attachDataObject( const_cast <Data&> ( refData ), false, true );
   initFieldsAndSubst( BF::HOST );
   clearUpdatedFlags( BF::HOST, false );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::init( const DString& acctNum, const DString& dstrTrack,const DString& dstrPageName  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(int, DString)" ) );


   BFData requestData(ifds::DSTC0004_REQ);
   BFData response(ifds::DSTC0004_VW);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::EntityId, I_( "" ) );
   requestData.setElementValue( ifds::InputAcctNum, acctNum );
   requestData.setElementValue( ifds::InputShrNum, I_( "" ) );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   SEVERITY sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::MFACCOUNT, 
                                                            requestData, 
                                                            response, 
                                                            DSTCRequestor( getSecurity(), true ) );   
   if( sevRtn <= WARNING )
   {
      BFData* repeat = new BFData( response.getRepeat( 0 ));
      //attach the repeat
      attachDataObject( *repeat, true, false );
      _initAccountNum = acctNum;
      _initAccountNum.stripLeading( '0' ).strip();
      _initEffectiveDate = repeat->getElementValue( ifds::EffectiveDate );  
      loadSettleCurrencySubstitutionList(BF::HOST);
      initFieldsAndSubst( BF::HOST );
      setFieldReadOnly( ifds::TaxableTrustDate, BF::HOST, true );  
      setFieldReadOnly( ifds::ExemptPeriod, BF::HOST, true );  

      clearUpdatedFlags( BF::HOST, false );

      bool bSettlementRuleExist = isSettlementRuleExist( BF::HOST );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//support for refresh
//******************************************************************************
SEVERITY MFAccount::doPreClearFields()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPreClearFields" ) );

   //for now we do refresh only in HOST
   getField( ifds::AccountNum, _reinitAccountNum, BF::HOST );
   getField( ifds::ServiceAgentUpdated, _serviceAgentUpdated, BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::reInit() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );

   if( !isNew() )
   {
	   init( _reinitAccountNum );

	   if( isAMSAccount( BF::HOST ) )
	   {
		   // when user select update pac/swp from ams, systematic needs refresh 
		   SystematicList* pSystematicList = NULL;
		   setObject( pSystematicList, I_( "SystematicList" ), OBJ_ACTIVITY_NONE, BF::HOST ); 
		   getSystematicList(  pSystematicList, BF::HOST , true);

		   // when user update account level ams, default allocation needs refresh
		   Shareholder *pShareholder = NULL;
		   getShareholder ( pShareholder, BF::HOST );
		   {
			   ShrAllocTypeList *pShrAllocTypeList = NULL;
			   pShareholder->getAllocationList( pShrAllocTypeList, BF::HOST, true );
			   if( pShrAllocTypeList )
			   {
				   pShrAllocTypeList->initExisting();
            }
         }
      }

      if(_serviceAgentUpdated.strip().upperCase() == I_("Y"))
      {
         refreshShareholder( BF::HOST );
      }

      BFObjIter iterAcctOwnershipAllocation (*this, BF::HOST);

      iterAcctOwnershipAllocation.positionByKey (I_("AcctOwnershipAllocationList"));
      if (!iterAcctOwnershipAllocation.end ())
      {
         iterAcctOwnershipAllocation.removeObjectFromMap (true);
      }

      BFObjIter iterFeeParamList(*this, BF::HOST);

      iterFeeParamList.positionByKey (I_("FeeParamList"));
      if (!iterFeeParamList.end ())
      {
          iterFeeParamList.removeObjectFromMap (true);
      }

      discardAlertMessageList();
   }

   _bRefresh = false;
   return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************
void MFAccount::discardAlertMessageList()
{
    BFObjIter iterAlertMessages(*this, BF::HOST);
    iterAlertMessages.setKeyFilter(I_("AlertMessageList"), true);

    while (!iterAlertMessages.end())
    {
        iterAlertMessages.removeObjectFromMap(true);
    }
}

//*************************************************************************************
bool MFAccount::needsRefresh (const BFDataGroupId& idDataGroup) const
{
   return _bRefresh ? _bRefresh : hasUpdatedFields (idDataGroup);
}

//*************************************************************************************
void MFAccount::refreshMe (bool bRefreshMe)
{
   _bRefresh = bRefreshMe;
}

//******************************************************************************
//this is overriden for the second init (the one with the AccNum as param)
SEVERITY MFAccount::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   init( data );
   pObjOut = this;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getAccountHoldingList ( MFAccountHoldingList*& pAccountHoldingList, 
                                            const BFDataGroupId& idDataGroup, 
                                            bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAccountHoldingList"));

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pAccountHoldingList = dynamic_cast<MFAccountHoldingList*>(getObject( I_( "MFAccountHoldingList" ), idDataGroup ) );

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if (!pAccountHoldingList)
   {
      if (isNew()) //check if the account is new
      {
         pAccountHoldingList = new MFAccountHoldingList (*this);
         pAccountHoldingList->init ();
      }
      else if (inquireDatabase)
      {
         DString accountNum, 
            activeOnly ;

         getField (ifds::AccountNum, accountNum, idDataGroup);
			getField (ifds::ActiveOnly, activeOnly, idDataGroup);

         if (activeOnly.empty()) 
         {
//kinda of an ugly fix...it just happenes that the inits are called too late in some cases.
            setFieldNoValidate (ifds::ActiveOnly, I_("N"), idDataGroup, true, true);
            activeOnly = I_("N");
         }
         pAccountHoldingList = new MFAccountHoldingList (*this);

//PTS 10037310 - remove as of date == curr buss date, retrieve all holdings
            pAccountHoldingList->init ( accountNum, 
                                        NULL_STRING,  //as of date
                                        NULL_STRING,  //fund code
                                        NULL_STRING,  //class code
                                        activeOnly);
//if we inquire the database the group id should be the host
            idWorkingDataGroup = BF::HOST;
      }
      if (pAccountHoldingList)
      {
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
         {
            setObject (pAccountHoldingList, I_("MFAccountHoldingList"), OBJ_ACTIVITY_NONE, idWorkingDataGroup);
         }
         else
         {
            delete pAccountHoldingList;
            pAccountHoldingList = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MFAccount::getAccountHoldingsAsOfDate ( const DString &asOfDate,
										                   MFAccountHoldingList *&pMFAccountHoldingList,
										                   const BFDataGroupId &idDataGroup,
                                                 const DString &fundCode /*= NULL_STRING*/,
                                                 const DString &classCode /*= NULL_STRING*/)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAccountHoldingsAsOfDate"));

   pMFAccountHoldingList = NULL;

   DString accountNum;

   getField (ifds::AccountNum, accountNum, idDataGroup);
   accountNum.stripLeading ('0');

   if ( !accountNum.empty() &&
        !asOfDate.empty())
   {
      DString dstrKey = I_("Holdings_Account=") + accountNum + 
                        I_(";FundCode=") + fundCode +
                        I_(";ClassCode=") + classCode +
                        I_(";EffectiveDate=") + asOfDate;

      pMFAccountHoldingList = dynamic_cast <MFAccountHoldingList*> (getObject (dstrKey, idDataGroup));
      if (!pMFAccountHoldingList)
      {                        
         pMFAccountHoldingList = new MFAccountHoldingList (*this);
         if (pMFAccountHoldingList->init (accountNum, asOfDate, fundCode, classCode) <= WARNING)
         {
            setObject ( pMFAccountHoldingList, 
                        dstrKey, 
                        OBJ_ACTIVITY_NONE, 
                        idDataGroup);
         }
         else
         {
            delete pMFAccountHoldingList;
            pMFAccountHoldingList = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getTransactionsList( TransactionList *&pTransactionsList, 
                                         const BFDataGroupId& idDataGroup, 
                                         bool allFundsMode, 
                                         bool inquireDatabase /*= true*/,
                                         bool bStartEmptyList /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTransactionsList" ) );

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   if( allFundsMode )
   {
      pTransactionsList = dynamic_cast<TransactionList *>( BFCBO::getObject( I_( "AllTransactionList" ), idDataGroup ) );
   }
   else
   {
      pTransactionsList = dynamic_cast<TransactionList *>( BFCBO::getObject( I_( "TransactionList" ), idDataGroup ) ) ;
   }
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pTransactionsList )
   {
      if( isNew() ) //check if the account is new
      {
         pTransactionsList = new TransactionList( *this );
         pTransactionsList->init();
      }
      else if( inquireDatabase ) //make the view call
      {
         DString accountNum;

         getField( ifds::AccountNum, accountNum, idDataGroup );
         pTransactionsList = new TransactionList( *this );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;

         if( allFundsMode )
         {
            DString fundCode, classCode, allFunds( I_( "Y" ) );
            DString numEntry( THREE_STRING );

            pTransactionsList->init( accountNum, fundCode, classCode, numEntry, allFunds );
         }
         else if( bStartEmptyList )
         {
            pTransactionsList->init();
         }
         else
         {
            MFAccountHoldingList *pMFAccountHoldingList = NULL;
            DString fundCode, classCode, allFunds( NO );
            DString numEntry( THREE_STRING );
            int firstTime = true;

            if( getAccountHoldingList( pMFAccountHoldingList, idWorkingDataGroup ) <= WARNING )
            {
               BFObjIter iter( *pMFAccountHoldingList, BF::HOST );

               for( iter.begin(); !iter.end(); ++iter )
               {
                  iter.getObject()->getField( ifds::rxFundCode, fundCode, idWorkingDataGroup );
                  fundCode.stripAll();
                  iter.getObject()->getField( ifds::rxClassCode, classCode, idWorkingDataGroup );
                  classCode.stripAll();
                  if( firstTime )
                  {
                     if( pTransactionsList->init( accountNum, fundCode, classCode, numEntry, allFunds ) > WARNING )
                     {
                        break;
                     }
                     firstTime = false;
                  }
                  else
                  {
                     if( pTransactionsList->anotherAccount( accountNum, fundCode, classCode, numEntry, allFunds ) > WARNING )
                     {
                        break;
                     }
                  }
               }
            }
         }
      }
      if( pTransactionsList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            if( allFundsMode )
            {
               setObject( pTransactionsList, I_( "AllTransactionList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup );
            }
            else
            {
               setObject( pTransactionsList, I_( "TransactionList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup );
            }
         }
         else
         {
            delete pTransactionsList;
            pTransactionsList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getPendingTradesList( PendingTradeList *&pPendingTradesList, 
                                          const BFDataGroupId& idDataGroup, int nNumEntry /*= -1*/,
                                          DString ExtTransNum /*=NULL_STRING*/, bool bRefresh /* = false*/) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getPendingTradesList" ) );

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pPendingTradesList = NULL;

   assert (nNumEntry >= -1);

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   DString dstrKey( I_("PendingTradeList") );
   dstrKey += ExtTransNum;
   if ( bRefresh ) // clear pending trade list
   {      
      setObject( pPendingTradesList, dstrKey, OBJ_ACTIVITY_NONE, isNew()?idWorkingDataGroup:BF::HOST );
   }
   pPendingTradesList = dynamic_cast<PendingTradeList *>(BFCBO::getObject( dstrKey, idDataGroup ) );
   if( !pPendingTradesList )
   {
      if( isNew() )
      {
         pPendingTradesList = new PendingTradeList( *this );
         pPendingTradesList->init();
      }
      else
      {
         DString accountNum;
         DString strNumEntry = DString::asString( nNumEntry );

         pPendingTradesList = new PendingTradeList( *this );
         getField( ifds::AccountNum, accountNum, idDataGroup );
         if( ExtTransNum.empty() )
         {
            pPendingTradesList->init( accountNum, strNumEntry );
         }
         else
         {
            pPendingTradesList->initSearch(
                                 I_("ExtTransnum"),
						               accountNum,
                                 NULL_STRING,
                                 NULL_STRING, 
                                 NULL_STRING, 
                                 ExtTransNum, 
                                 NULL_STRING,
                                 NULL_STRING, 
                                 NULL_STRING,
                                 NULL_STRING, 
                                 NULL_STRING,
						         NULL_STRING,
						         NULL_STRING,
						         NULL_STRING );
         }
         idWorkingDataGroup = BF::HOST;
      }
      if( pPendingTradesList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pPendingTradesList, dstrKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup );
         }
         else
         {
            delete pPendingTradesList;
            pPendingTradesList = NULL;
         }
      }
   }
   else//PendingTradeList already exists
   {
      if( nNumEntry != -1 )//if called with NumEntry == -1, just return the pointer
      {
         if( pPendingTradesList->doMoreRecordsExist() )
         {
            if( nNumEntry == FULL_LIST )//caller expects all the available items
               pPendingTradesList->getMore(FULL_LIST);
            else //user wants only up to nNumEntry items
            {
               int nPrevReqNoOfItems = pPendingTradesList->getNoOfPreviouslyRequestedItems();
               if( nPrevReqNoOfItems < nNumEntry )
                  pPendingTradesList->getMore(nNumEntry - nPrevReqNoOfItems);
            }
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getDemographicsList(Demographics*& pDemographics, 
   const BFDataGroupId& idDataGroup, bool inquireDatabase )  //=true
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDemographicsList"));
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pDemographics = dynamic_cast< Demographics* >(BFCBO::getObject(I_("DemographicsList"), idDataGroup));
   if (!pDemographics)
   {
      BFDataGroupId idWorkingDataGroup = idDataGroup;
      DString accountNum;
      bool newshrhld = false;

      getField(ifds::AccountNum, accountNum, idDataGroup);      
      accountNum.stripLeading('0');
      accountNum.strip();

      Shareholder* pShareholder;
      if( getShareholder( pShareholder, idDataGroup ) <= WARNING )
      {
         if(pShareholder->isNew()) newshrhld = true;
      }

      if (isNew() && newshrhld)
      {
         //new empty list
         pDemographics = new Demographics(*this);
         pDemographics->initNew(accountNum,idWorkingDataGroup);
      }
      else if (inquireDatabase)
      {
         DString strEntityId = I_( "0" );

         pDemographics = new Demographics(*this);
         //pDemographics->init(accountNum, idWorkingDataGroup);
         pDemographics->init(accountNum, strEntityId, idWorkingDataGroup);
      }

      if (pDemographics)
      {
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
         {
            setObject(pDemographics, I_("DemographicsList"), OBJ_ACTIVITY_NONE, idWorkingDataGroup);
         }
         else
         {
            delete pDemographics;
            pDemographics = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getDirectTradingList( DirectTradingList *&pDirectTradingList, 
                                          const BFDataGroupId& idDataGroup, bool inquireDatabase /* = true */) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDirectTradingList" ) );

   DString accountNum;

   getField( ifds::AccountNum, accountNum, idDataGroup );
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pDirectTradingList = dynamic_cast<DirectTradingList *>( BFCBO::getObject( I_( "DirectTradingList" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pDirectTradingList )
   {
      if( isNew() ) //check if account is new
      {
         pDirectTradingList = new DirectTradingList( *this );
         pDirectTradingList->initNew( accountNum );
      }
      else if( inquireDatabase ) //make the view call
      {
         pDirectTradingList = new DirectTradingList( *this );
         pDirectTradingList->init( accountNum );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pDirectTradingList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            //TODO:  Should be idWorkingDataGroup???
            setObject( pDirectTradingList, I_( "DirectTradingList" ), OBJ_ACTIVITY_NONE, BF::HOST ); 
         }
         else
         {
            delete pDirectTradingList;
            pDirectTradingList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY MFAccount::getSystematicList( SystematicList*& pSystematicList, 
                                       const BFDataGroupId& idDataGroup, 
									   bool inquireDatabase /*= true*/,
									   const DString &payType /* = NULL_STRING*/,
							           const DString &amount /*= NULL_STRING*/,
							           const DString &amountType /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSystematicList" ) );

   DString accountNum;

   getField( ifds::AccountNum, accountNum, idDataGroup );
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pSystematicList = dynamic_cast<SystematicList *>( BFCBO::getObject( I_( "SystematicList" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pSystematicList )
   {
      if( isNew()) //check if account is new
      {
         pSystematicList = new SystematicList( *this );
         pSystematicList->initNew( accountNum , payType, amount, amountType );
      }
      else if( inquireDatabase ) //make the view call
      {
         pSystematicList = new SystematicList( *this );
         pSystematicList->init( accountNum, payType, amount, amountType  );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pSystematicList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            //TODO:  Should be idWorkingDataGroup???
            setObject( pSystematicList, I_( "SystematicList" ), OBJ_ACTIVITY_NONE, BF::HOST ); 
         }
         else
         {
            delete pSystematicList;
            pSystematicList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getAccDistributionsList( AccountDistributionList*& pAccDistributionList,
   const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccDistributionsList" ) );

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pAccDistributionList = dynamic_cast<AccountDistributionList *>(
                                                                 BFCBO::getObject( I_( "AccountDistributionList" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pAccDistributionList )
   {
      if( inquireDatabase )
         bCreate = true;

      if( !bCreate )
         return(GETCURRENTHIGHESTSEVERITY());

      DString dstrAccountNum, dstrShareholderNum;

      getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
      getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
      dstrShareholderNum.strip().stripLeading( I_CHAR( '0' ) );

      pAccDistributionList = new AccountDistributionList( *this );
      if( isNew() ) //check if account is new
      {
         pAccDistributionList->init( false, idDataGroup, dstrAccountNum, dstrShareholderNum, ACCOUNT_LEVEL );
      }
      else
      {
         pAccDistributionList->init( inquireDatabase, BF::HOST, dstrAccountNum, dstrShareholderNum, ACCOUNT_LEVEL );
         idWorkingDataGroup = BF::HOST;
      }
      if( pAccDistributionList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pAccDistributionList, I_( "AccountDistributionList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup );
         }
         else
         {
            delete pAccDistributionList;
            pAccDistributionList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getRRIF_LIF_LRIF_InfoList(RRIF_LIF_LRIF_InfoList *&pRRIF_LIF_LRIF_InfoList, 
   const BFDataGroupId& idDataGroup, bool inquireDatabase/* = true*/, bool bPermit)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRRIF_LIF_LRIF_InfoList" ) );

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pRRIF_LIF_LRIF_InfoList = dynamic_cast< RRIF_LIF_LRIF_InfoList * >(
      BFCBO::getObject(I_("RRIF_LIF_LRIF_InfoList"), idDataGroup ) );
   if( !pRRIF_LIF_LRIF_InfoList && !inquireDatabase && !isNew() )//if called from the transaction builder
      return(GETCURRENTHIGHESTSEVERITY());

   if (!isRRIFAccount(idDataGroup))
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pRRIF_LIF_LRIF_InfoList )
   {
      DString dstrAccountNum;  
      getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
      pRRIF_LIF_LRIF_InfoList = new RRIF_LIF_LRIF_InfoList( *this );
      pRRIF_LIF_LRIF_InfoList->setPermit(bPermit); 


      if(isNew()) //check if account is new
      {
         pRRIF_LIF_LRIF_InfoList->init();
      }
      else if (inquireDatabase)
      {
         pRRIF_LIF_LRIF_InfoList->init( dstrAccountNum );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if (pRRIF_LIF_LRIF_InfoList)
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject(pRRIF_LIF_LRIF_InfoList, I_( "RRIF_LIF_LRIF_InfoList" ), 
               OBJ_ACTIVITY_NONE, idWorkingDataGroup);
         }
         else
         {
            delete pRRIF_LIF_LRIF_InfoList;
            pRRIF_LIF_LRIF_InfoList = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getRESPInfo( RESPInfo *&pRESPInfo, const BFDataGroupId& idDataGroup, bool inquireDatabase )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRESPInfo" ) );

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   pRESPInfo = dynamic_cast< RESPInfo * >( BFCBO::getObject( I_( "RESPInfo" ), idDataGroup ) );
   if( !pRESPInfo )
   {
      DString strAcctNum;
      getField( ifds::AccountNum, strAcctNum, idDataGroup );

      if( isNew() )
      {
         pRESPInfo = new RESPInfo( *this );
         pRESPInfo->initNew( strAcctNum );
      }
      else if( inquireDatabase )
      {
         pRESPInfo = new RESPInfo( *this );

         pRESPInfo->init( strAcctNum );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }

      if( pRESPInfo )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pRESPInfo, I_( "RESPInfo" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pRESPInfo;
            pRESPInfo = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getRESPTransactionsList( RESPTransactionsList *&pRESPTransactionsList,
                                             const DString& dstrHistoryPending,
                                             const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRESPTransactionsList" ) );

   //check cbobase to see if we've already built it
   //otherwise, create and store with base

   DString dstrKey = I_( "RESPTransactionsList" ) + dstrHistoryPending;

   pRESPTransactionsList = dynamic_cast< RESPTransactionsList * >( BFCBO::getObject(dstrKey, idDataGroup ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getMatSweepInstrList (MatSweepInstrList *&pMatSweepInstrList,
                                          const DString& instructionType,
                                          const DString& dstrLevel,
                                          const DString& dstrFund,
                                          const DString& dstrClass,
                                          const DString& dstrTransNum,
                                          const DString& dstrTransId,
                                          const DString& dstrIntInvestId,
                                          const DString& dstrPrincipalAmount,
                                          const DString& dstrAccuredAmount,
                                          const BFDataGroupId& idDataGroup,
                                          bool inquireDatabase)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMatSweepInstrList" ) );

   DString strKey,
      accountNum;

   strKey = I_("MatSweepInstrList");// + instructionType + dstrLevel + dstrFund +
   //		     dstrClass + dstrTransNum + dstrTransId + dstrIntInvestId;

   pMatSweepInstrList = dynamic_cast< MatSweepInstrList * >( BFCBO::getObject (strKey, idDataGroup));

   BFDataGroupId idWorkingDataGroup = idDataGroup;

   getField (ifds::AccountNum, accountNum, idDataGroup);  
   if (!pMatSweepInstrList)
   {
      if (inquireDatabase)
      {
         pMatSweepInstrList = new MatSweepInstrList( *this );
         pMatSweepInstrList->init ( accountNum, 
                                    instructionType, 
                                    dstrFund, 
                                    dstrClass,
                                    dstrTransNum, 
                                    dstrTransId,
                                    dstrIntInvestId,
                                    dstrLevel,
                                    dstrPrincipalAmount,
                                    dstrAccuredAmount,
                                    idDataGroup);
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if (pMatSweepInstrList)
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject (pMatSweepInstrList, strKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup); 
         }
         else
         {
            delete pMatSweepInstrList;
            pMatSweepInstrList = NULL;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::removeMatSweepInstrList()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMatSweepInstrList" ) );

   BFObjIter iter( *this, BF::HOST, true, BFObjIter::ITERTYPE::NON_DELETED );
   if(iter.positionByKey( I_("MatSweepInstrList")))
   {
      iter.removeObjectFromMap(true, true);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getRESPTransactionsList( RESPTransactionsList *&pRESPTransactionsList,
                                             const DString& dstrHistoryPending,
                                             const DString& dstrTransId,
                                             const DString& dstrRESPBenefId,
                                             const DString& dstrRESPBenefName,
                                             const DString& dstrFromDate,
                                             const DString& dstrToDate,
                                             const DString& dstrTransTypeDesc,
                                             const DString& dstrTfrStat,
                                             const DString& dstrRepHRDC,
                                             const BFDataGroupId& idDataGroup,
                                             bool inquireDatabase )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRESPTransactionsList" ) );

   //check cbobase to see if we've already built it
   //otherwise, create and store with base

   DString dstrKey = I_( "RESPTransactionsList" ) + dstrHistoryPending;

   pRESPTransactionsList = dynamic_cast< RESPTransactionsList * >( BFCBO::getObject(dstrKey, idDataGroup ) );
   DString strAcctNum;
   getField( ifds::AccountNum, strAcctNum, idDataGroup );

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pRESPTransactionsList || inquireDatabase)
   {
      if( isNew() )
      {
         pRESPTransactionsList = new RESPTransactionsList( *this );
         pRESPTransactionsList->initNew( strAcctNum, dstrHistoryPending );
      }
      else if( inquireDatabase )
      {
         DString dstrTransType;
         DString dstrRedCode;
         DString dstrDepositType;

         if (dstrTransTypeDesc == I_("ALL") || dstrTransTypeDesc == I_("ALLCONTR"))
         {
            dstrTransType = dstrTransTypeDesc;
            dstrRedCode = NULL_STRING;
            dstrDepositType = NULL_STRING;
         }
         else
         {
            RESPTransactionTypesList	*pRESPTransactionTypesList = NULL;

            if (getRESPTransactionTypesList (pRESPTransactionTypesList, dstrTransId, dstrHistoryPending, idDataGroup, false) && pRESPTransactionTypesList) 
            {
               pRESPTransactionTypesList->getTransTypeInfo(dstrTransTypeDesc, 
                                                           dstrTransType,
                                                           dstrRedCode,
                                                           dstrDepositType,
                                                           idDataGroup);
            }
         }

         if (pRESPTransactionsList != NULL)
         {
            // delete old elements when doing inquiry from trans history
            BFObjIter bfIter (*this, idDataGroup);

            if (bfIter.positionByKey (dstrKey))
            {
               bfIter.removeObjectFromMap (true);
               pRESPTransactionsList = NULL;
            }
         }

         if (pRESPTransactionsList == NULL)
         {
            pRESPTransactionsList = new RESPTransactionsList( *this );
         }

         pRESPTransactionsList->init( strAcctNum, 
                                      dstrHistoryPending, 
                                      dstrTransId,
                                      dstrTransType,
                                      dstrRESPBenefId,
                                      dstrRESPBenefName,
                                      dstrFromDate,
                                      dstrToDate,
                                      dstrDepositType,
                                      dstrRedCode,
                                      dstrTfrStat,
                                      dstrRepHRDC,
									  idDataGroup);
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }

      if( pRESPTransactionsList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pRESPTransactionsList, dstrKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pRESPTransactionsList;
            pRESPTransactionsList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
} 

//******************************************************************************
SEVERITY MFAccount::getRESPTransactionTypesList (RESPTransactionTypesList *&pRESPTransactionTypesList,
                                                 const DString &dstrTransId,
                                                 const DString& dstrHistoryPending,
                                                 const BFDataGroupId& idDataGroup,
                                                 bool inquireDatabase )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRESPTransactionTypesList" ) );

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   DString strAcctNum;
   getField( ifds::AccountNum, strAcctNum, idDataGroup );

   DString strKey = I_( "RESPTransactionTypesList" ) + strAcctNum + dstrTransId + dstrHistoryPending;

   pRESPTransactionTypesList = dynamic_cast< RESPTransactionTypesList * >( BFCBO::getObject (strKey, idDataGroup));

   BFDataGroupId idWorkingDataGroup = idDataGroup;

   if( !pRESPTransactionTypesList )
   {
      if( inquireDatabase )
      {
         pRESPTransactionTypesList = new RESPTransactionTypesList( *this );
         pRESPTransactionTypesList->init (strAcctNum, dstrTransId, dstrHistoryPending);
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }

      if( pRESPTransactionTypesList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pRESPTransactionTypesList, strKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pRESPTransactionTypesList;
            pRESPTransactionTypesList = NULL;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getRESPBeneficiaryList (RESPBeneficiaryList *&pRESPBeneficiaryList,
                                            const BFDataGroupId& idDataGroup,
                                            bool inquireDatabase )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRESPBeneficiaryList" ) );

   pRESPBeneficiaryList = dynamic_cast< RESPBeneficiaryList * >( BFCBO::getObject (I_( "RESPBeneficiaryList" ), idDataGroup));

   DString strAcctNum;
   getField( ifds::AccountNum, strAcctNum, idDataGroup );

   BFDataGroupId idWorkingDataGroup = idDataGroup;

   if( !pRESPBeneficiaryList )
   {
      if( inquireDatabase )
      {
         pRESPBeneficiaryList = new RESPBeneficiaryList( *this );
         pRESPBeneficiaryList->init (strAcctNum);
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }

      if( pRESPBeneficiaryList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pRESPBeneficiaryList, I_( "RESPBeneficiaryList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pRESPBeneficiaryList;
            pRESPBeneficiaryList = NULL;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
} 

//******************************************************************************
SEVERITY MFAccount::getRESPTradeSearchCriteria (RESPTradeSearchCriteria *&pRESPTradeSearchCriteria, 
                                                const DString &dstrTransId,
                                                const DString &dstrTradeDate,
                                                const DString &dstrHistoryPending,
                                                const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRESPTradeSearchCriteria" ) );

   pRESPTradeSearchCriteria = dynamic_cast< RESPTradeSearchCriteria * >( BFCBO::getObject (I_( "RESPTradeSearchCriteria" ), idDataGroup));

   DString strAcctNum;
   getField( ifds::AccountNum, strAcctNum, idDataGroup );

   BFDataGroupId idWorkingDataGroup = idDataGroup;

   if( !pRESPTradeSearchCriteria )
   {
      pRESPTradeSearchCriteria = new RESPTradeSearchCriteria (*this );
      pRESPTradeSearchCriteria->init (strAcctNum, dstrTransId, dstrTradeDate, dstrHistoryPending, idDataGroup);
      //if we inquire the database the group id should be the host
      idWorkingDataGroup = BF::HOST;


      if( pRESPTradeSearchCriteria )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pRESPTradeSearchCriteria, I_( "pRESPTradeSearchCriteria" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pRESPTradeSearchCriteria;
            pRESPTradeSearchCriteria = NULL;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getCertificateList( CertificateList*& pCertificateList, 
                                        const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getCertificateList" ) );

   DString accountNum, nullstring (NULL_STRING);

   getField( ifds::AccountNum, accountNum, idDataGroup );
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   pCertificateList = dynamic_cast<CertificateList *>( BFCBO::getObject( I_( "CertificateList" ), idDataGroup ) );
   if( !pCertificateList )
   {
      if( inquireDatabase ) //make the view call
      {
         pCertificateList = new CertificateList( *this );
         pCertificateList->init( accountNum, nullstring, nullstring, nullstring );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pCertificateList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pCertificateList, I_( "CertificateList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pCertificateList;
            pCertificateList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getAcctMailingOverrideList( AcctMailingOverrideList*& pAcctMailingOverrideList, 
                                                const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundsList" ) );

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pAcctMailingOverrideList = dynamic_cast<AcctMailingOverrideList*>(BFCBO::getObject( I_( "AcctMailingOverrideList" ), idDataGroup ) );

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pAcctMailingOverrideList )
   {
      DString dstrAcctNum;
      getField( ifds::AccountNum, dstrAcctNum, idDataGroup );

      if( isNew()) //check if the account is new
      {
         pAcctMailingOverrideList = new AcctMailingOverrideList( *this );
         pAcctMailingOverrideList->initNew(dstrAcctNum, idDataGroup);
      }
      else if( inquireDatabase )
      {
         pAcctMailingOverrideList = new AcctMailingOverrideList( *this );
         pAcctMailingOverrideList->init( dstrAcctNum, idDataGroup );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;

      }
      if( pAcctMailingOverrideList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pAcctMailingOverrideList, I_( "AcctMailingOverrideList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pAcctMailingOverrideList;
            pAcctMailingOverrideList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::canPurchase ( const DString&  dstrTradeDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canPurchase" ) );

   SEVERITY sevRtn = canTrade( I_( "Purchase" ), ifds::StopPurchase, dstrTradeDate, idDataGroup );
   if ( sevRtn < WARNING ) {
      bool bFundOverride;
      DString dstrAmount;
      checkAMSRestriction( dstrTradeDate, CAN_PURCHASE, idDataGroup, bFundOverride, dstrAmount, true );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::validateMoneyInTFSA(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMoneyInTFSA"));

   DString dstrTaxType;
   getField(ifds::TaxType, dstrTaxType, idDataGroup);

   if (dstrTaxType == TFSA_TAX_TYPE)
   {
       ACCTENTITYOBJ_VECTOR vAcctOwners;
       getAcctOwners(vAcctOwners, idDataGroup);

       for (int i = 0; i < vAcctOwners.size(); i++)
       {
           DString seq;
           vAcctOwners[i]->getField(ifds::SeqNumber, seq, idDataGroup);

           if (asInteger(seq) == 1)
           {
               if (!vAcctOwners[i]->acctOwnerAgeEligibleForTFSA(idDataGroup))
               {
                   getErrMsg(IFASTERR::ACCT_NOT_ELIGIBLE_MONEY_IN_AGE_LESS_THAN_MINIMUM,
                             CND::ERR_ACCT_NOT_ELIGIBLE_MONEY_IN_AGE_LESS_THAN_MINIMUM,
                             CND::WARN_ACCT_NOT_ELIGIBLE_MONEY_IN_AGE_LESS_THAN_MINIMUM,
                             idDataGroup);
               }
           }
       }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::escrowPurchase ( const DString&  dstrTradeDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "escrowPurchase" ) );

   // Check escrow account, but not for eFan, until further instructions

   DString acctNum, strSettledFieldsInitialized;

   getField(ifds::SettledFieldsInitialized, strSettledFieldsInitialized, idDataGroup, false);

   //Settled and Unsettled fields were set by eCom, 'we are eFan', no need for escrow check
   if( strSettledFieldsInitialized.strip() == YES )
      return(GETCURRENTHIGHESTSEVERITY());


   getField(ifds::AccountNum, acctNum, idDataGroup);
   acctNum.strip().stripLeading( '0' );

   AccountEntityXref *pAccountEntityXref = NULL;

   if( getAccountEntityXref( pAccountEntityXref, idDataGroup ) <= WARNING )
   {
      DString strKey;

      if( acctNum != NULL_STRING )
         SEVERITY sevRtn = pAccountEntityXref->escrowAccount( acctNum, PURCHASE_CODE, NULL_STRING, dstrTradeDate, idDataGroup);

   } // if found AccountEntityXref
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY MFAccount::canRedeem ( const DString&  dstrTradeDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canRedeem" ) );

   SEVERITY sevRtn = canTrade( I_( "Redemption" ), ifds::StopRed, dstrTradeDate, idDataGroup );

   if( sevRtn > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());


   DString acctType, pensionJuris, dstrRdLckdE, dstrRdLckdW;
   getField( ifds::AcctType, acctType, idDataGroup ); 
   getField( ifds::PensionJuris, pensionJuris, idDataGroup );
   getWorkSession().getOption( ifds::RdLckdE, dstrRdLckdE, idDataGroup, false );
   getWorkSession().getOption( ifds::RdLckdW, dstrRdLckdW, idDataGroup, false );

   if( acctType.strip().upperCase() == LOCKED_IN )
   {
      if( dstrRdLckdE == NO && pensionJuris != I_("0006") )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCT_LOCKED_NO_REDEMPTION_AVAILABLE );
      }
      else if( dstrRdLckdW ==YES )
      {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCT_LOCKED_NO_REDEMPTION_AVAILABLE );
      }
   }

   DString dstrLockedIn;

   sevRtn = groupLockedIn ( idDataGroup, dstrLockedIn );

   if ( dstrLockedIn == I_( "1" ) ) // Employer locked-in
      ADDCONDITIONFROMFILE( CND::ERR_EMPLOYER_LOCKED_IN_AT_GROUP );

   if ( dstrLockedIn == I_( "2" ) ) // Employee locked-in
      ADDCONDITIONFROMFILE( CND::ERR_EMPLOYEE_LOCKED_IN_AT_GROUP );

   if ( dstrLockedIn == I_( "3" ) ) // Employer and Employee are both locked-in
      ADDCONDITIONFROMFILE( CND::ERR_EMPLOYER_EMPLOYEE_LOCKED_IN_AT_GROUP );

   if ( sevRtn < WARNING ) {  
      bool bFundOverride;           
      DString dstrAmount;
      checkAMSRestriction( dstrTradeDate, CAN_REDEEM, idDataGroup, bFundOverride, dstrAmount );
   }

   return(GETCURRENTHIGHESTSEVERITY());
} 

//******************************************************************************
SEVERITY MFAccount::escrowRedeem ( const DString&  dstrTradeDate, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "escrowRedeem" ) );

   // Check escrow account, but not for eFan, until further instructions
   DString acctNum, strSettledFieldsInitialized;

   getField(ifds::SettledFieldsInitialized, strSettledFieldsInitialized, idDataGroup, false);

   //Settled and Unsettled fields were set by eCom, 'we are eFan', no need for escrow check
   if( strSettledFieldsInitialized.strip() == YES )
      return(GETCURRENTHIGHESTSEVERITY());

   getField(ifds::AccountNum, acctNum, idDataGroup);
   acctNum.strip().stripLeading( '0' );

   AccountEntityXref *pAccountEntityXref = NULL;

   if( getAccountEntityXref( pAccountEntityXref, idDataGroup ) <= WARNING )
   {
      DString strKey;

      if( acctNum != NULL_STRING )
         SEVERITY sevRtn = pAccountEntityXref->escrowAccount( acctNum, REDEMPTION_CODE, NULL_STRING, dstrTradeDate, idDataGroup);

   } // if found AccountEntityXref
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY MFAccount::canTrfExchIn ( const DString& dstrTradeDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canTrfExchIn" ) );

   SEVERITY sevRtn = canTrade( I_( "Transfer/Exchange In" ), ifds::StopXferIn, dstrTradeDate, idDataGroup );

   if ( sevRtn < WARNING ) {
      bool bFundOverride;
      DString dstrAmount;
      checkAMSRestriction( dstrTradeDate, CAN_TRANSFER_IN, idDataGroup, bFundOverride, dstrAmount, true );
   }
   return(GETCURRENTHIGHESTSEVERITY());
} 

//******************************************************************************
SEVERITY MFAccount::canTrfExchOut ( const DString& dstrTradeDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canTrfExchOut" ) );

   SEVERITY sevRtn = canTrade( I_( "Transfer/Exchange Out" ), ifds::StopXferOut, dstrTradeDate, idDataGroup );

   DString dstrLockedIn;

   sevRtn = groupLockedIn ( idDataGroup, dstrLockedIn );

   if ( dstrLockedIn == I_( "1" ) ) // Employer locked-in
      ADDCONDITIONFROMFILE( CND::ERR_EMPLOYER_LOCKED_IN_AT_GROUP );

   if ( dstrLockedIn == I_( "2" ) ) // Employee locked-in
      ADDCONDITIONFROMFILE( CND::ERR_EMPLOYEE_LOCKED_IN_AT_GROUP );

   if ( dstrLockedIn == I_( "3" ) ) // Employer and Employee are both locked-in
      ADDCONDITIONFROMFILE( CND::ERR_EMPLOYER_EMPLOYEE_LOCKED_IN_AT_GROUP );

   if ( GETCURRENTHIGHESTSEVERITY() < WARNING ) {      
      bool bFundOverride;
      DString dstrAmount;
      checkAMSRestriction( dstrTradeDate, CAN_TRANSFER_OUT, idDataGroup, bFundOverride, dstrAmount );
   }
   return(GETCURRENTHIGHESTSEVERITY());
} 

//******************************************************************************
bool MFAccount::accountActive ( const DString& dstrDate,  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "accountActive" ) );

   bool bAcctActive (true);
   DString acctStatus, acctEffectiveOn;

   ///////////////////////// Check if account status is active ////////////////////////////
   getField ( ifds::AcctStatus, acctStatus, idDataGroup );
   if( isNew() )
      getField ( ifds::EffectiveDate, acctEffectiveOn, idDataGroup, false );
   else
      getField ( ifds::FirstEffective, acctEffectiveOn, idDataGroup, false );

   if( acctStatus >= TERMINATED_ACCT_STATUS ||
       (DSTCommonFunctions::CompareDates( dstrDate,acctEffectiveOn) == DSTCommonFunctions::FIRST_EARLIER) )
      bAcctActive = false;

   return(bAcctActive);
}

//******************************************************************************
SEVERITY MFAccount::canTrade( const DString& TransType, const BFFieldId& idField, const DString& dstrTradeDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canTrade" ) );

   DString shrGroupCode, groupStopFlag, acctStopFlag, shrNum;

   DString idiStr, TRADE_TYPE ( I_("TRADE_TYPE")), GROUP_CODE (I_("GROUP_CODE"));

   if( !accountActive ( dstrTradeDate, idDataGroup ) )
   {
      // insert error message : account inactive 
      ADDCONDITIONFROMFILE( CND::ERR_ACCT_INACTIVE_ON_TRADE_DATE );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   ///////////////////////// Account Level Stop Flag //////////////////////////////////////
   getField( idField, acctStopFlag, idDataGroup );

   if( acctStopFlag == YES )
   {
      bool bCodeInList;
      if( idField == ifds::StopRed )
      {
         DString taxType, dstrTaxTypeList;
         dstrTaxTypeList = I_("2,5,G,GR,L,I,R,K");
         getField( ifds::TaxType, taxType, idDataGroup );
         bool bIsRIFLike = getWorkSession ().isLIFLike (taxType);

         if( bCodeInList = ( DSTCommonFunctions::codeInList( taxType, dstrTaxTypeList) )
			 || bIsRIFLike)
         {
            ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCOUNT_REDEMPTION_FLAG_ENABLED );
         }
         else
         {
            ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_REDEMPTION_FLAG_ENABLED );
         }

      }
      else
      {
         // insert error message : Account level stop trade flag is turned on 
         addIDITagValue( idiStr, TRADE_TYPE, TransType );
         ADDCONDITIONFROMFILEIDI( CND::ERR_ACCOUNT_STOP_FLAG_ON, idiStr.c_str() );
      }
   }

   ////////////////////////// Check if group level has stop flag turned on ////////////////
   else
   {
      /* Get the shareholder CBO and loop thru the GroupList to find the Group that the account
      belongs to. Check the StopPurchase flag at Group Level */
      GroupList* pGroupList;

      getField( ifds::AcctGroup, shrGroupCode, idDataGroup );
      if( getGroupList( pGroupList ) <= WARNING )
      {
         pGroupList->getField( shrGroupCode, idField, groupStopFlag, idDataGroup, false ) ;

         if( groupStopFlag == YES )
         {
            // insert error message : group level stop trade flag is turned on 
            addIDITagValue( idiStr, TRADE_TYPE, TransType );
            addIDITagValue( idiStr, GROUP_CODE, shrGroupCode );
            ADDCONDITIONFROMFILEIDI( CND::ERR_GROUP_STOP_FLAG_ON, idiStr.c_str() );
         }
      } // if GroupList found

   } // else to check group level stop flag

   return(GETCURRENTHIGHESTSEVERITY());
} 
/*

//********Old version still called by Allocation.cpp and Systematic ************************************
SEVERITY MFAccount::canTrade( const DString& TransType, const DString& dstrTradeDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "CanAcctTrade" ) );

   DString shrGroupCode, groupStopFlag, acctStopFlag, shrNum, acctStatus, acctEffectiveOn;
   MgmtCo *pMgmtCoOut = NULL;
   DString idiStr, tradeType, TRADE_TYPE ( I_("TRADE_TYPE")), GROUP_CODE (I_("GROUP_CODE"));
   DString dstrPurchase ( I_( "Purchase" ));
   DString dstrExchangeIn ( I_( "Exchange In" ));
   DString dstrExchangeOut ( I_( "Exchange Out" ));
   DString dstrRedemption ( I_( "Redemption" ));

   ///////////////////////// Check if account status is active ////////////////////////////
   getField ( DBR::AcctStatus, acctStatus, idDataGroup );
   if ( isNew() )
   {
      getField ( DBR::EffectiveDate, acctEffectiveOn, idDataGroup, false );
   }
   else
   {
      getField ( DBR::FirstEffective, acctEffectiveOn, idDataGroup, false );
   }

   if ( acctStatus >= TERMINATED_ACCT_STATUS ||
        (DSTCommonFunctions::CompareDates( dstrTradeDate,acctEffectiveOn) == DSTCommonFunctions::FIRST_EARLIER))
   {        
   // insert error message : account inactive 
      ADDCONDITIONFROMFILE( CND::ERR_ACCT_INACTIVE_ON_TRADE_DATE );
   }

   ///////////////////////// Account Level Stop Flag //////////////////////////////////////
   else if ( TransType == PURCHASE_CODE)
   {
      getField( DBR::StopPurchase, acctStopFlag, idDataGroup );
      tradeType = dstrPurchase;
   }
   else if ( TransType == EX_FER_OUT_CODE )
   {
      getField( DBR::StopXferOut, acctStopFlag, idDataGroup );
      tradeType = dstrExchangeIn;
   }
   else if ( TransType == EX_FER_IN_CODE)
   {
      getField( DBR::StopXferIn, acctStopFlag, idDataGroup );
      tradeType = dstrExchangeOut;
   }
   else if ( TransType == REDEMPTION_CODE )
   {
      getField( DBR::StopRed, acctStopFlag, idDataGroup );
      tradeType = dstrRedemption;
   }
   
   

   if ( acctStopFlag == YES )
   {  
      // insert error message : Account level stop trade flag is turned on 
      addIDITagValue( idiStr, TRADE_TYPE, tradeType );
      ADDCONDITIONFROMFILEIDI( CND::ERR_ACCOUNT_STOP_FLAG_ON, idiStr.c_str() );
   }
   
   ////////////////////////// Check if group level has stop flag turned on ////////////////
   else
   {
      GroupList* pGroupList;

      /* Get the shareholder CBO and loop thru the GroupList to find the Group that the account
      belongs to. Check the StopPurchase flag at Group Level 
      
      getField( DBR::AcctGroup, shrGroupCode, idDataGroup );
      if( getGroupList( pGroupList ) <= WARNING )
      {
         BFObjIter glIter( *pGroupList, idDataGroup );

         for( glIter.begin(); !glIter.end(); ++glIter )
         {
            DString iterGroupCode;

            glIter.getObject()->getField( DBR::rxGroupCode, iterGroupCode, idDataGroup );
            if ( iterGroupCode == shrGroupCode )
            {
               if ( TransType == PURCHASE_CODE )
                  glIter.getObject()->getField( DBR::StopPurchase, groupStopFlag, idDataGroup );
               else if ( TransType == EX_FER_OUT_CODE )
                  glIter.getObject()->getField( DBR::StopXferOut, groupStopFlag, idDataGroup );
               else if ( TransType == EX_FER_IN_CODE ) 
                  glIter.getObject()->getField( DBR::StopXferIn, groupStopFlag, idDataGroup );
               else if ( TransType == REDEMPTION_CODE )
                  glIter.getObject()->getField( DBR::StopRed, groupStopFlag, idDataGroup );

               if ( groupStopFlag == YES )
               {
                  // insert error message : group level stop trade flag is turned on 
                  addIDITagValue( idiStr, TRADE_TYPE, tradeType );
                  addIDITagValue( idiStr, GROUP_CODE, shrGroupCode );
                  ADDCONDITIONFROMFILEIDI( CND::ERR_GROUP_STOP_FLAG_ON, idiStr.c_str() );
               }
            }
         }  // loop thru groupList
      } // if GroupList found

   } // else to check group level stop flag

   return GETCURRENTHIGHESTSEVERITY();
} */

//******************************************************************************



void MFAccount::getInitialAccountNumber( DString  &initAccountNum )
{
   initAccountNum = _initAccountNum;
}

//******************************************************************************
bool MFAccount::isJoint( const BFDataGroupId& idDataGroup )
{
   DString acctType;

   getField( ifds::AcctType, acctType, idDataGroup );
   return(acctType == JOINT_CODE);
}

//******************************************************************************
//the rules are:
//1. link this account to the account holder, sequence 1 entity;
//2. copy the broker code, branch code and slsrep from model
//3. create a new account mailing info under the same shareholder
SEVERITY MFAccount::cloneFromModel( const DString& modelAccountNum, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "cloneFromModel" ) );

   SEVERITY sevRtn = NO_CONDITION;

   AccountEntityXref *pAccountEntityXref = NULL;
   MFAccount *pMFAccountModel = NULL;

   if( getAccountEntityXref( pAccountEntityXref, idDataGroup ) <= WARNING && pAccountEntityXref &&
       getWorkSession().getMFAccount( idDataGroup, modelAccountNum, pMFAccountModel ) <= WARNING && pMFAccountModel)
   {
      //copy the broker code and ....from model to the new MFAccount
      DString brokerCode, branchCode, slsrepCode, intercode;

	  //If system supports Master Account -AMS C, copy fields specified by backend and set as readonly.
	  DString dstrMstrActActive, dstrCSSStopSINMatch;
	  bool doesSupportMstrActAMSC = false;
	  if (getWorkSession().getOption(ifds::MstrActActive, dstrMstrActActive, BF::HOST, false) <= WARNING &&
		  getWorkSession().getOption(ifds::CSSStopSINMatch, dstrCSSStopSINMatch, BF::HOST, false) <= WARNING)
      { 
			  doesSupportMstrActAMSC = dstrMstrActActive == Y && dstrCSSStopSINMatch == Y;
      }

	  if (doesSupportMstrActAMSC)
      {
		  DString tmpMstrActAttrbVal;
		  DString dstrAMSCode = NULL_STRING;
	  
		  if (getMstrActAttrbValue(I_("AcctDesMatch"), tmpMstrActAttrbVal, idDataGroup) <= WARNING && 
			  tmpMstrActAttrbVal.upperCase() == YES)
          {
		      setFieldFromModelAcct(ifds::AcctDesignation, idDataGroup, pMFAccountModel, true);
		  }
		  
		  if (getMstrActAttrbValue(I_("IntIntAcctMatchIndex"), tmpMstrActAttrbVal, idDataGroup) <= WARNING && 
			  tmpMstrActAttrbVal.upperCase() == YES)
          {
			  setFieldFromModelAcct(ifds::InterCode, idDataGroup, pMFAccountModel, true);
			  setFieldFromModelAcct(ifds::InterAccount, idDataGroup, pMFAccountModel, true);
		  }
		  
		  if (getMstrActAttrbValue(I_("TaxTypeMatch"), tmpMstrActAttrbVal, idDataGroup) <= WARNING && 
			  tmpMstrActAttrbVal.upperCase() == YES)
          {
			  setFieldFromModelAcct(ifds::TaxType, idDataGroup, pMFAccountModel, true);
		  }

		  if (getMstrActAttrbValue(I_("DlrDlrAcctMatchIndex"), tmpMstrActAttrbVal, idDataGroup) <= WARNING && 
			  tmpMstrActAttrbVal.upperCase() == YES)
          {
			  setFieldFromModelAcct(ifds::BrokerCode, idDataGroup, pMFAccountModel, true, true); //validate
			  setFieldFromModelAcct(ifds::BranchCode, idDataGroup, pMFAccountModel, true, true); //validate
			  setFieldFromModelAcct(ifds::Slsrep,     idDataGroup, pMFAccountModel, true, true); //validate
			  setFieldFromModelAcct(ifds::AltAccount, idDataGroup, pMFAccountModel, true);
		  }

		  if (getMstrActAttrbValue(I_("AcctTypeMatch"), tmpMstrActAttrbVal, idDataGroup) <= WARNING && 
			  tmpMstrActAttrbVal.upperCase() == YES)
		  {
			  setFieldFromModelAcct(ifds::AcctType, idDataGroup, pMFAccountModel, true);
		  }

	     //Unspecified fields would be the same as model account and editable.
		 setFieldFromModelAcct(ifds::BeneficialOwner, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::ProdPortfolioUUID, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::ProdPortfolioPlanUUID, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::ExemptPeriod, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::TaxableTrustDate, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::AcctGroup, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::AcctGroupName, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::XrefNum, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::PensionJuris, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::TaxTypeSchedule, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::SocialCode, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::InTrustFor, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::Escrow, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::Currency, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::RegCompleted, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::AdditionalInfo, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::RegistrationInfo, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::UnclmRemitDate, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::AcctPurpose, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::BusinessNo, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::RRSPFee, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::RecipientType, idDataGroup, pMFAccountModel, false);
		 setFieldFromModelAcct(ifds::AccountClosingReason, idDataGroup, pMFAccountModel, false);
	  }
	  else 
      { 
		  pMFAccountModel->getField( ifds::BrokerCode, brokerCode, idDataGroup, false );
		  sevRtn = checkBroker( brokerCode, idDataGroup, false );
		  setFieldNoValidate( ifds::BrokerCode, brokerCode, idDataGroup, false, true, true );
		  if ( !isHouseBroker( idDataGroup ) ) {
			  pMFAccountModel->getField( ifds::BranchCode, branchCode, idDataGroup, false );
			  sevRtn = checkBranches( branchCode, idDataGroup, false );
			  setFieldNoValidate( ifds::BranchCode, branchCode, idDataGroup, false, true, true );
			  pMFAccountModel->getField( ifds::Slsrep, slsrepCode, idDataGroup, false );
			  bool bNewAgent;
			  sevRtn = checkAgents( slsrepCode, idDataGroup, false, bNewAgent );
			  setFieldNoValidate( ifds::Slsrep, slsrepCode, idDataGroup, false, true, true );
		  }

		  pMFAccountModel->getField( ifds::InterCode, intercode, idDataGroup, false );

		  setFieldNoValidate( ifds::InterCode, intercode, idDataGroup, false, true, true );
	  }

      // Clone Entity 01 and 21 of the matching account
      DString strKey, accountNum;
      //get the account number for this account
      getField( ifds::AccountNum, accountNum, idDataGroup, false );

      //deal with the address mailing info
      //get the shareholder from repository
      Shareholder *pShareholder;
      if( getShareholder( pShareholder, idDataGroup ) <= WARNING )
      {
         AccountMailingList *pAccountMailingList;

         if( pShareholder->getAccountMailingList( pAccountMailingList, idDataGroup ) <= WARNING )
         {
            DString strKey;
            BFObjIter mailingIter( *pAccountMailingList, idDataGroup );

            mailingIter.begin( OBJ_TYPE_ACCOUNT_MAILING );
            pAccountMailingList->setNewAccountNumber( accountNum );
            //we should create a new element for the account mailing list
            mailingIter.addNewObject( strKey );

            AccountMailingInfo* pAccountMailingInfo = 
            dynamic_cast<AccountMailingInfo*>(mailingIter.getObject());

            if( pAccountMailingInfo != NULL )
            {
               //set the account number to the new mailing info
               pAccountMailingInfo->setField( ifds::AccountNum, accountNum, idDataGroup );
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//after the user hits cancel on the screen, if there is any clone we should roll it back
//we'll be using the initialAccountNumber, as the account number for the clone,
//since nothing has been commited
SEVERITY MFAccount::rollbackClone( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "rollbackClone" ) );

   //get the links from the account entity cross refernce object and remove them from
   //the map
   AccountEntityXref *pAccountEntityXref = NULL;

   if( getAccountEntityXref( pAccountEntityXref, idDataGroup) <= WARNING )
   {
      DString strKey;
      BFObjIter xrefIter( *pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

      //build the key to retrieve all the links for the cloned account 
      AccountEntityXref::buildPartialKeyForAccount( strKey, _initAccountNum );
      if( xrefIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey ) )
      {
         //remove all links for the clone
         while( !xrefIter.end() ) //we found a link for the cloned account
         {
            xrefIter.removeObjectFromMap( true );
            //++xrefIter;
         }
      }
   }


   //deal with the cloned AccountMailingInfo
   Shareholder* pShareholder;

   if( getShareholder( pShareholder, idDataGroup ) <= WARNING )
   {
      AccountMailingList *pAccountMailingList;

      if( pShareholder->getAccountMailingList( pAccountMailingList, idDataGroup ) <= WARNING )
      {
         DString strKey;
         BFObjIter mailingIter( *pAccountMailingList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

         //build the key to retrieve all the mailing infos for the cloned account 
         AccountMailingList::buildKey( strKey, _initAccountNum );
         if( mailingIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey ) )
         {
            while( !mailingIter.end() )
            {
               mailingIter.removeObjectFromMap( true );
               //++mailingIter;
            }
         }
      }
      //remove the account from the MFAccountList of the shareholder
      pShareholder->detachAccountFromMFAccountList( this, idDataGroup );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//the rule: an account can be model only if the entity we are checking for,
//is an accountholder and the sequence of it is 1
bool MFAccount::isAccountModel( const DString& entityId, const BFDataGroupId& idDataGroup )
{

   AccountEntityXref *pAccountEntityXref = NULL;
   bool isModel = false;

   if( getAccountEntityXref( pAccountEntityXref, idDataGroup) <= WARNING )
   {
      DString strKey, accountNum;
      BFObjIter xrefIter( *pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

      //build the key
      getField( ifds::AccountNum, accountNum, idDataGroup, false );
      AccountEntityXref::buildKey( strKey, 
                                   accountNum,
                                   ACCOUNT_OWNER_ENTITY_TYPE,
                                   I_( "1" ),  //sequence number
                                   entityId );

      if( xrefIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey ) )
      {
         isModel = !xrefIter.end();
      }
   }
   return(isModel);
}

//******************************************************************************
bool MFAccount::isAcctDTAEligible( const BFDataGroupId& idDataGroup )
{
   bool DTAEligible = false;

   DString dstrResidency1, dstrResidency2, dstrResidency3, dstrTaxJurisCode, dstrShrNum;
   DString dstrExclAcctType, dstrAcctType;
   getWorkSession().getOption( ifds::Residency1, dstrResidency1, idDataGroup, false );
   getWorkSession().getOption( ifds::Residency2, dstrResidency2, idDataGroup, false );
   getWorkSession().getOption( ifds::Residency3, dstrResidency3, idDataGroup, false );

   getField( ifds::ShrNum, dstrShrNum, idDataGroup );
   Shareholder* pShareholder = NULL;
   if( getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder ) <= WARNING )
   {
   pShareholder->getField( ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup );
   }

   if( ( DSTCommonFunctions::codeInList( dstrTaxJurisCode, dstrResidency1 ) ||
         DSTCommonFunctions::codeInList( dstrTaxJurisCode, dstrResidency2 ) ||
         DSTCommonFunctions::codeInList( dstrTaxJurisCode, dstrResidency3 ) 
       )
     )
   {
      TaxTypeRule *ptaxTypeRule = NULL;
      if( getTaxTypeRule ( ptaxTypeRule, idDataGroup ) <= WARNING && ptaxTypeRule != NULL )
      {
         getField( ifds::AcctType, dstrAcctType, idDataGroup, false );
         ptaxTypeRule->getField(ifds::ExclDTAAccountType, dstrExclAcctType, idDataGroup, false);
         if( dstrExclAcctType.find( dstrAcctType ) == DString::npos )
         {
            DTAEligible = true;
         }
      }
   }

   return (DTAEligible);
}

//******************************************************************************
void MFAccount::getField( const BFFieldId& idField, 
                          DString& strFieldValue, 
                          const BFDataGroupId& idDataGroup, 
                          bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );
   if( idField == ifds::AccountBalance && formattedReturn )
   {
      DString currency;
      getField( ifds::Currency, currency, idDataGroup, false );
      currency.strip();

      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( currency, strFieldValue, strFieldValue );
   }
   else if( idField == ifds::AccountNum )
   {
      strFieldValue.strip().stripLeading( I_CHAR( '0' ) );
   }
   else if( idField == ifds::TaxType )
   {
      strFieldValue.strip().upperCase() ;
   }
   else if ( idField == ifds::TaxTypeScheduleApplicable )
   {
      bool bApplic;
      const_cast<MFAccount*>(this)->isTaxTypeScheduleApplicable(bApplic, NULL_STRING, NULL_STRING, NULL_STRING, idDataGroup);
      strFieldValue = bApplic?YES:NO;
   }

}
//********************************************************************************
int  MFAccount::CheckEffectiveForAT(DString strEffective,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "CheckEffectiveForAT" ) );
   DString curEffectDate;
   getField(ifds::FirstEffective,curEffectDate,idDataGroup,false);
   curEffectDate.strip();

   if( DSTCommonFunctions::CompareDates( strEffective,curEffectDate) == DSTCommonFunctions::FIRST_EARLIER )
   {
      return(ACCOUNT_NOT_EFFECT);
   }

   AgentList agentList( *this );
   DString brokerCode, branchCode,slsrepCode;

   getField( ifds::BrokerCode, brokerCode, idDataGroup );
   getField( ifds::BranchCode, branchCode, idDataGroup );
   getField( ifds::Slsrep,slsrepCode,idDataGroup );
   //checks for the validity of the agent code. by making a view call, and raising a condition
   //we do not want to make the view call when the slslrep code is NULL, because the view will
   //return us all the agents for this broker and branch
   if( slsrepCode != NULL_STRING && agentList.init( brokerCode, branchCode, slsrepCode ) <= WARNING )
   {
      BFObjIter bfIter( agentList, idDataGroup );
      DString  curDate,strStopDate;

      getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, curDate, BF::HOST,false );
      curDate.strip();

      bfIter.begin();
      if( !bfIter.end() )
      {
         bfIter.getObject()->getField( ifds::StopDate, strStopDate, idDataGroup,false );
         strStopDate.strip();
         if( DSTCommonFunctions::CompareDates( curDate,strStopDate) == DSTCommonFunctions::FIRST_EARLIER
             && DSTCommonFunctions::CompareDates( strEffective,strStopDate) == DSTCommonFunctions::FIRST_EARLIER )
            return(ACCOUNT__SALES_REP_OK);
      }
   }

   return(SALES_REP_NOT_EFFECT);
}
//********************************************************************************
BFAbstractCBO* MFAccount::getTopLevelAncestor() 
{
   return(this);
}

///VALIDATION ROUTINES
//******************************************************************************
SEVERITY MFAccount::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   SEVERITY sevRtn = NO_CONDITION;

   if( idField == ifds::AccountNum )
   {
      bool acctNumFound = false;
      /*if( strValue == NULL_STRING )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_EMPTY );
      }
      else
      {*/
         //check the account number only if the account is new
         if( isNew() && checkTheAccountNumber( strValue, idDataGroup, acctNumFound ) <= WARNING )
         {
            if( acctNumFound )
            {
               ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_NUMBER_EXISTS );
            }
         }
      //}
   }
   else if (idField == ifds::TaxType)
   {
      if (!strValue.empty())
      {
         // Added by Celia for the ticket 10013951 -- Stop user from selecting As Pension Plan in 
         // Canadian market. 
         if( strValue == AS_PENSION_PLAN_TAX_TYPE && DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA  )
         {
            ADDCONDITIONFROMFILE( CND::ERR_NO_ALLOWED_FOR_AS_PENSION_PLAN );
         }

         validateTaxType ( strValue, idDataGroup );
      }
   }
   else if (idField == ifds::AcctType)
   {
      if (!strValue.empty())
      {
         TaxTypeRule *ptaxTypeRule = NULL;

         if (getTaxTypeRule (ptaxTypeRule, idDataGroup) <= WARNING && ptaxTypeRule)
         {
            // if the account type is not valid account type under the tax type, then give error message
            if (!ptaxTypeRule->validAcctType (strValue, idDataGroup))
            {
               ADDCONDITIONFROMFILE (CND::ERR_ACCT_TYPE_NOT_VALID_FOR_TAX_TYPE);
            }
         }
         if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
         {
            if (strValue == I_("4")) //corporate account
            {
               //check if account is marked private, give a warning and delete the acct category
               AcctCategoryList *pAcctCategoryList (NULL);
               if ( getAcctCategoryList (pAcctCategoryList, idDataGroup) <= WARNING && 
                    pAcctCategoryList)
               {
                  BFObjIter iter (*pAcctCategoryList, idDataGroup);

                  while (!iter.end ())
                  {
                     DString acctCategory;
                     
                     iter.getObject () ->getField (ifds::AcctCategory, acctCategory, idDataGroup, false);
                     if (acctCategory == ACCOUNT_CATEGORY::PRIVATE)
                     {
                        ADDCONDITIONFROMFILE (CND::ERR_DELETE_PRIVATE_ACCOUNT_CATEGORY);
                        break;
                     }
                     ++iter;
                  }
               }
            }

            DString dstrBrokerCode,
               dstrAcctDesignation,
               dstrAcctTaxType;

            getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup,false);
            getField (ifds::AcctDesignation, dstrAcctDesignation, idDataGroup,false);
            getField (ifds::TaxType, dstrAcctTaxType, idDataGroup,false);

            validateAcctCatEPA(dstrBrokerCode,
                               dstrAcctDesignation,
                               strValue,
                               dstrAcctTaxType,
                               idDataGroup);
         }
      }
   }
   else if( idField == ifds::AcctGroup )  // validate Account Group Code
   {
      DString groupCodeLevel = getGrpCodeLevel (idDataGroup);

      if( groupCodeLevel == ACCOUNT_GROUP_LEVEL )
      {
         if( strValue == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_GROUP_NUMBER_IS_REQUIRED );
         }
         else
         {
            GroupList *pGroupList;
            if( getGroupList( pGroupList ) <= WARNING )
            {
               sevRtn = pGroupList->getField(strValue, ifds::GroupName, _GroupName, idDataGroup, true);
            }
            else _GroupName = NULL_STRING;
         }
      } // if account level group code
   }
   else if (idField == ifds::BrokerCode)
   {
      DString brokerCode (strValue);
      brokerCode.stripAll();

      if (brokerCode.empty())
      {
         ADDCONDITIONFROMFILE (CND::ERR_BROKER_EMPTY);
      }
      else
      {
         checkBroker (brokerCode, idDataGroup, true);
         validateBrokerIA(idDataGroup);
         // R99 Statement and Confirm
         validateBrokerNI31103STMT(brokerCode, idDataGroup);

         DString dstrAcctType,
            dstrAcctDesignation,
            dstrAcctTaxType;

         getField (ifds::AcctDesignation, dstrAcctDesignation, idDataGroup,false);
         getField (ifds::AcctType, dstrAcctType, idDataGroup,false);
         getField (ifds::TaxType, dstrAcctTaxType, idDataGroup,false);

         validateAcctCatEPA(brokerCode,
                            dstrAcctDesignation,
                            dstrAcctType,
                            dstrAcctTaxType,
                            idDataGroup);

		 validateBrokerChangeForDocList(idDataGroup);
         validateBrokerChangeForTrailerFee (brokerCode, idDataGroup);
      }
   }
   else if (idField == ifds::BrokerClrFirmAgtFirmTPA)
   {
      DString brokerCode;
      getField (ifds::BrokerCode, brokerCode, idDataGroup);
      validateBrokerForNSCC( brokerCode, idDataGroup );
   }

   else if (idField == ifds::ClearingFirm)
   {
      // ClearingFirm is mandatory and NSCCComplant and effective 
      validateClearingFirm( idDataGroup );
   }

   else if (idField == ifds::BranchCode)
   {
      DString brokerCode, 
         branchCode (strValue);

      branchCode.stripAll();
      if (branchCode.empty() && slsRepByBranch (idDataGroup))
      {
         ADDCONDITIONFROMFILE (CND::ERR_BRANCH_EMPTY);
      }
      else
      {
         getField (ifds::BrokerCode, brokerCode, idDataGroup);
         if (validateField (ifds::BrokerCode, brokerCode, idDataGroup) <= WARNING)
         {
            checkBranches (branchCode, idDataGroup, true);
            validateBranchIA(idDataGroup);
         }
         else
         {
            CLEARCONDITIONS ();
         }
      }
   }
   else if( idField == ifds::Slsrep )
   {
      DString branchCode, CopyStr( strValue);

      CopyStr.stripAll();
      sevRtn = validateLengthForBrokerBranchSalsRep(I_("SalsRep"),CopyStr,idDataGroup);
      if(sevRtn > WARNING )
      {
         setFieldNoValidate( ifds::ShouldAskForRep, NO, idDataGroup, false );			
      }
      else
      {
         if( CopyStr == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_SALES_REP_EMPTY);
         }
         else
         {
            if( slsRepByBranch ( idDataGroup ) )
            {
               getField( ifds::BranchCode, branchCode, idDataGroup );
               sevRtn = validateField( ifds::BranchCode, branchCode, idDataGroup );
            }
            else
            {
               sevRtn = NO_CONDITION;
            }

            if( sevRtn <= WARNING )
            {
               bool bNewAgent = false;
               checkAgents( strValue, idDataGroup, true, bNewAgent );
               if( bNewAgent )
               {
                  if ( _dstrHouseBroker == YES )
                     setFieldNoValidate( ifds::ShouldAskForRep, NO, idDataGroup, false );
                  else 
                  {
                     DString strShouldAskForrep = YES;
                     int count = CONDITIONCOUNT( );
                     Condition   *c = NULL;
                     for( int i = 0; i < count; i++ )
                     {
                        c = new Condition( *GETCONDITION( i ));
                        if (c->getCode() == CND::ERR_SALES_REP_ALREADY_EXISTS )
                        {
                           strShouldAskForrep = NO;
                           delete c;
                           break;
                        }
                        delete c;
                     };
                     setFieldNoValidate( ifds::ShouldAskForRep, strShouldAskForrep, idDataGroup, false );
                  }
               }
               else
               {
                  setFieldNoValidate( ifds::ShouldAskForRep, NO, idDataGroup, false );
                  // reset CeateRep, otherwise it is still 'Y' when user select an existing salesrep
                  setFieldNoValidate( ifds::CreateRep, NO, idDataGroup, false );  
               }
               //clear the update flag
               setUpdatedFlag( ifds::ShouldAskForRep, idDataGroup, false );
            }

            //P0186486FN09 - Employee and Agent Account Gap#8A
            validateIASlsRepForEmployeeAgent(idDataGroup);
            validateSlsRepIA(idDataGroup);

			validateServiceOnlySlsRep(idDataGroup);
         }

         DString segClient;
         getWorkSession().getOption( ifds::SegClient, segClient, idDataGroup, false );
         if(GETCURRENTHIGHESTSEVERITY () <= WARNING && segClient==YES)
         {
            //Rule: If NewBusiness-92 is No and SegClient = Yes issue warning 
            //   "Salesperson is not permitted new business activity"
            AgentList agentList( *this );
            DString brokerCode,
               slsrepCode,
               newBusiness;


            getField( ifds::BrokerCode, brokerCode, idDataGroup );
            getField( ifds::BranchCode, branchCode, idDataGroup );
            getField( ifds::Slsrep, slsrepCode, idDataGroup );
            if( slsrepCode != NULL_STRING && 
               agentList.init( brokerCode, branchCode, slsrepCode ) <= WARNING )
            {
               BFObjIter bfIter( agentList, idDataGroup );

               bfIter.begin();
               if( !bfIter.end() )
               {
                  bfIter.getObject()->getField( ifds::NewBusiness, newBusiness, idDataGroup );
                  //      bfIter.getObject()->getField( DBR::SegClient, segClient, idDataGroup );
               }
            }
            else
            {
               newBusiness = NULL_STRING;
            }

            getWorkSession().getOption( ifds::SegClient, segClient, idDataGroup, false );

            if( NO == newBusiness)
            {
               ADDCONDITIONFROMFILE( CND::ERR_SALESPERSON_IS_NOT_PERMITTED );
            }
         }
      }
   }
   else if( idField == ifds::MarketMail )
   {
      if( strValue == NO )
      {
         setFieldNoValidate( ifds::ShouldAskForMail, YES, idDataGroup, false );
      }
      else
      {
         setFieldNoValidate( ifds::ShouldAskForMail, NO, idDataGroup, false );
      }
      setUpdatedFlag( ifds::ShouldAskForMail, idDataGroup, false );

   }
   else if( idField == ifds::AcctStatus )
   {
      bool b30or90 = strValue == TERMINATED_ACCT_STATUS || strValue == I_( "90" );

      // user cannot select status code 30 (terminated) or 90 (delete) 
      // if there is balance in the account or if the account in new
      if( b30or90 && isNew() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCT_BALANCE_TERM_AND_DEL );
      }
      else if( b30or90 && ( !ZeroBalance( idDataGroup ) ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCT_BALANCE_TERM_AND_DEL_MAINT );
      }
      //Rule: if CotClient-83 = Yes  and  DeathClaim-4 = NO,  AcctStat-76 must 
      //   be <> '41' and <> '40' . Otherwise issue error: : Contract status must be set to 
      //   pending death claim before changing account status to death.
      DString cotClient, dstrPorfolioIsRequried;
      getWorkSession().getOption( ifds::CotClient, cotClient, idDataGroup, false );
      getWorkSession().getOption (ifds::PorfolioIsRequried, dstrPorfolioIsRequried, BF::HOST, false);
      dstrPorfolioIsRequried.upperCase();

      if (YES == cotClient && ( DEATH_TRANSFER_ACCT_STATUS == strValue || 
                                DEATH_ACCT_STATUS == strValue ))
      {
			if ( dstrPorfolioIsRequried == NO || // for non-portfolio clients
             (dstrPorfolioIsRequried == YES && hasSegFundsWithinPortfolio (idDataGroup))) 
         {
            //get deathClaim
			   DString deathClaim;
			   getField (ifds::DeathClaim, deathClaim, idDataGroup);

			   if( NO == deathClaim )
				   ADDCONDITIONFROMFILE( CND::ERR_CONTRACT_STATUS );
         }
         //Rule: if cotClient-83 = Yes and AccountBalance-4 <>0 AcctStat-76 must 
         //   be <> '41' and <>'40' . Otherwise issue errror: There are current fund 
         //balances for this account, There are current fund balances for this account
         if( !ZeroBalance( idDataGroup ) )
            ADDCONDITIONFROMFILE( CND::ERR_CURRENT_FUND_BALANCES );
      }
	  //PET0168296FN09 - give warning when user's trying to update from TERMINATED to ACTIVE
      if(strValue == ACTIVE_ACCT_STATUS)
      {
         DString acctStatus;
         getField( ifds::AcctStatus, acctStatus, BF::HOST, false  );
         if (acctStatus == TERMINATED_ACCT_STATUS)
         {
            getErrMsg (IFASTERR::ACCOUNT_IS_BEING_ACTIVATED,
                        CND::ERR_ACCOUNT_IS_BEING_ACTIVATED,
                        CND::WARN_ACCOUNT_IS_BEING_ACTIVATED,
                        idDataGroup,
                        NULL_STRING);
                        
            DString strTaxType;
            getField( ifds::TaxType, strTaxType, idDataGroup, false );
            
            if ( strTaxType == TFSA_TAX_TYPE )
            {
               DString strLatestAmendYear,
                  strEffectiveDate,
                  strEffectiveYear;
               getLatestAmendmentYearOfOwnerSeq01(strLatestAmendYear,idDataGroup);
               getField( ifds::EffectiveDate, strEffectiveDate, idDataGroup, false );
               int year_pos = DSTCommonFunctions::getYearPosition();
               strEffectiveYear.assign(strEffectiveDate,year_pos,4);
               unsigned long iLatestAmendYear = convertToULong (strLatestAmendYear);
               unsigned long iEffectiveYear = convertToULong (strEffectiveYear);
               
               if( abs((long)(iLatestAmendYear-iEffectiveYear)) != 0 )
               {
                  ADDCONDITIONFROMFILE( CND::WARN_TFSA_ACCT_STATUS_CHANGED );
               }
            }

			if ( DSTCommonFunctions::codeInList (strTaxType, I_("9,M")) )
			{
				DString dstrTermEntryExist;
				getField(ifds::TermEntryExist, dstrTermEntryExist, idDataGroup);
				dstrTermEntryExist.stripAll();

				if (!dstrTermEntryExist.empty() && dstrTermEntryExist.upperCase() == I_("Y"))  
				{
					getErrMsg (IFASTERR::UNREVERSED_TERMINATION_ENTRIES_EXIST,
							   CND::ERR_UNREVERSED_TERMINATION_ENTRIES_EXIST,
							   CND::WARN_UNREVERSED_TERMINATION_ENTRIES_EXIST,
							   idDataGroup);
				}
			}
         }
      }
   }
   else if( idField == ifds::EffectiveDate )
   {
      updateTaxTypeSchedule( NULL_STRING, NULL_STRING, NULL_STRING, strValue, idDataGroup );
      Shareholder* pShareholder = NULL;
      // allow backdate when it's new
      if( !isNew() && getShareholder( pShareholder, idDataGroup ) <= WARNING )
      {
         DString shrEffectiveDate, latestEffectiveDate;

         pShareholder->getField( ifds::EffectiveDate, shrEffectiveDate, idDataGroup );
         getField( ifds::LastEffectiveDate, latestEffectiveDate, idDataGroup );

         if( DSTCommonFunctions::CompareDates( strValue, shrEffectiveDate ) == 
             DSTCommonFunctions::FIRST_EARLIER )
         {
            //ADDCONDITIONFROMFILE( CND::ERR_EFFECTIVE_DATE_BACKWARD );
            ADDCONDITIONFROMFILE( CND::WARN_EFFECTIVE_DATE_BACKWARD );
         }

         //Sync up to base on April 29, 2005, Account effective must 
         //either be less than or equal to the first account effective date or greater than or equal to the latest effective date.
         if( DSTCommonFunctions::CompareDates( strValue, _initEffectiveDate  ) == 
               DSTCommonFunctions::SECOND_EARLIER && 
             DSTCommonFunctions::CompareDates( strValue, latestEffectiveDate ) == 
                  DSTCommonFunctions::FIRST_EARLIER )
         {
            ADDCONDITIONFROMFILE( CND::ERR_ACCT_EFFECTIVE_DATE_VALIDATE );
         }
      }
   }
   else if( idField == ifds::InterAccount )
   {
      //Rule = Mandatory if AcctDesignation-75='3'. Canadian Enhancement
      //Rule = Updatable if AcctDesignation-75='3'. Canadian Enhancement
      DString acctDesignation;

      getField( ifds::AcctDesignation, acctDesignation, idDataGroup );

      if( INTERMEDIARY_ACCT_DESIGNATION == acctDesignation && NULL_STRING == strValue )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INTERMEDIARY_ACCOUNT_NUMBER_IS_REQUIRED );
      }
   }
   else if (idField == ifds::InterCode)
   {
      //Rule = Updatable and Mandatory if AcctDesignation-75='3'. Canadian Enhancement
      DString acctDesignation;

      getField (ifds::AcctDesignation, acctDesignation, idDataGroup);
      if (INTERMEDIARY_ACCT_DESIGNATION == acctDesignation)
      {
         if (strValue.empty())
         {
            ADDCONDITIONFROMFILE (CND::ERR_INTERMEDIARY_CODE_IS_REQUIRED);
         }
      }
   }
   else if( idField == ifds::RRSPFee )
   {
      //Rule = Add/Mod Mode:  Value '4' is not allowed, error message '
      //   '4' Exempt - Holding excess is System generated only"

      if( EXTEMPT_HOLDING_EXCESS_RRSP_FEE == strValue )
      {
         ADDCONDITIONFROMFILE( CND::ERR_EXEMPT_HOLDING_EXCESS );
      }
   }
   else if( idField == ifds::PensionJuris )
   {
      updateTaxTypeSchedule( NULL_STRING, NULL_STRING, strValue, NULL_STRING, idDataGroup );
      //if not read-only it shouldn't be blank
      if( strValue == NULL_STRING )
      {
         BFProperties * pBFProperties = NULL;
         pBFProperties = getFieldProperties( idField, idDataGroup );
         if( pBFProperties )
         {
            if( !pBFProperties->isReadOnly() )
            {
               ADDCONDITIONFROMFILE( CND::ERR_PENSION_JURIS_IS_MANDATORY );
            }
         }
      }

      //Rule = TT-PE; (Value '0000' is not allowed, error message 
      //   'Invalid Pension Jurisdiction')

      //Rule: Validation only applicable to TaxType-76 = B, C, L  (RIF and LIRA). 
      //  Otherwise, this field must be blank (can stop user from updating this field if 
      //   TaxType-76 = B, C or L. Otherwise must be > '0000' for TaxType-76 = B , L, C

      DString taxType;
      getField( ifds::TaxType, taxType, idDataGroup );

      if (getWorkSession ().isLIFLike (taxType) || getWorkSession ().isLIRALike (taxType) ||
          LRIF_TAX_TYPE == taxType || PRIF_TAX_TYPE == taxType )
      {
         /* if ( !isNew() )
            setValidFlag( ifds::TaxType, idDataGroup, true );*/
         if( UNASSIGNED_COUNTRY_CODE == strValue )
         {
            ADDCONDITIONFROMFILE( CND::ERR_INVALID_PENSION );
         }
      }
   }
   else if( idField == ifds::Unseizable )
   {
      //Rule = If TaxType-76 gets changed to taxtype <> '1' (RRSP), 
      //   set Unseizable to No.

      DString taxType;

      getField( ifds::TaxType, taxType, idDataGroup );
      if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
      {
         if( taxType != RRSP_TAX_TYPE )
         {
            setFieldNoValidate( ifds::Unseizable, NO, idDataGroup, false, true, true );
         }
      }
   }
   else if( idField == ifds::DateOfReg )
   {/*
      if ( !isNew() )
      {
         DString dstrOrgDateOfReg;
         getField ( DBR::DateOfReg, dstrOrgDateOfReg, BF::HOST  );
         int ret;
         if( ( ret = DSTCommonFunctions::CompareDates( strValue, dstrOrgDateOfReg ) ) == 
                  DSTCommonFunctions::DATE_ORDER::FIRST_EARLIER) 
         {
            ADDCONDITIONFROMFILE( CND::ERR_DATE_OF_REGISTRATION );  
         }
      }
   */
   }
//   else if( idField == ifds::AMSCode || idField == ifds::AMSROCode )
//   {
//      validateAMSCode( idField, strValue, idDataGroup );
//   }
   else if( idField == ifds::TaxTypeAcctType )
   {
      validateTaxTypeAcctType( idDataGroup );
   }

   else if( idField == ifds::TaxTypePensionJuris )
   {
      validateTaxTypePensionJuris( idDataGroup );
   }

   else if( idField == ifds::AltAccount )
   {
      validateAltAcct( strValue, idDataGroup );
   }
   else if( idField == ifds::MgmtFeePayOption )
   {
      validateMgmtFeePayOption( idDataGroup );
   }
   else if( idField == ifds::BusinessNo )
   {
      DString dstrBusinessNo;
      getField( ifds::BusinessNo, dstrBusinessNo, idDataGroup, false );
      if( dstrBusinessNo.strip() != NULL_STRING )
      {
         validateBusinessNo(idDataGroup);
      }
   }
   else if( idField == ifds::PensionLegCode )
   {
      DString dstrAcctType, dstrTaxType;
      getField( ifds::AcctType, dstrAcctType, idDataGroup, false );
      getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
      if( dstrAcctType == LOCKED_IN && dstrTaxType == RRSP_TAX_TYPE )
      {
         if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
         {
            if( strValue == NULL_STRING )
               getErrMsg( I_("373"), CND::ERR_FIELD_REQUIRED_PLS_SELECT, CND::WARN_FIELD_REQUIRED_PLS_SELECT, idDataGroup, NULL_STRING );
         }
      }
   }
   else if(idField == ifds::ClearingID ) 
   {
      validateClearingID( idDataGroup );
   }
   else if (idField == ifds::StopReason)
   {
      if (strValue == KYC_SYSTEM || strValue == DECEASED_SYSTEM)
      {
         ADDCONDITIONFROMFILE( CND::ERR_SYSTEM_STOP_REASON);
      }
  	  _bStopReasonChanged = true; 
   }
   else if( idField == ifds::FeeModelCode )
   {
      validateModelCode( idDataGroup );
   }
   else if( idField == ifds::TaxTypeSchedule )
   {
      updateTaxTypeSchedule( NULL_STRING, strValue, NULL_STRING, NULL_STRING, idDataGroup );
   }
   else if( idField == ifds::TaxTypeTaxTypeSchedule )
   {
      DString dstrTaxTypeSchedule, curDate, grandFatheredDate;
      getField( ifds::EffectiveDate, curDate, idDataGroup, false );
      curDate.strip();
      getGrandfatheredDate( grandFatheredDate, idDataGroup, NULL_STRING, NULL_STRING, NULL_STRING );
      if( DSTCommonFunctions::CompareDates( grandFatheredDate, curDate ) == DSTCommonFunctions::FIRST_EARLIER )
      {
         bool bApplic = false;
         DString strTaxTypeDesc, TaxTypeSchedDesc, strJurisdDesc;

         isTaxTypeScheduleApplicable(bApplic, NULL_STRING, NULL_STRING, NULL_STRING, idDataGroup);
         getGrandfatheredDate( grandFatheredDate, idDataGroup, NULL_STRING, NULL_STRING, NULL_STRING, true );

         getField( ifds::TaxType, strTaxTypeDesc, idDataGroup, true );
         getField( ifds::PensionJuris, strJurisdDesc, idDataGroup, true );
         getField( ifds::TaxTypeSchedule, TaxTypeSchedDesc, idDataGroup, true );

         DString idiStr, strTemp = NULL_STRING;
         strTemp += strJurisdDesc;
         strTemp += I_(" ");
         strTemp += strTaxTypeDesc;
         if( bApplic )
         {
            strTemp += I_(" ");
            strTemp += TaxTypeSchedDesc;
         }
         addIDITagValue( idiStr, I_("VAR1"), strTemp );
         addIDITagValue( idiStr, I_("GRANDFATHEREDDATE"), grandFatheredDate );
         ADDCONDITIONFROMFILEIDI( CND::ERR_TAX_TYPE_NO_LONGER_SUPPORTED_AFTER_DATE, idiStr);
      }

      validateTaxTypeTaxTypeSchedWithJurisEffDate( idDataGroup );
   }
   else if (idField == ifds::RecipientType)
   {
      DString taxType, 
         acctType,
         taxJuris,
         taxJurisDescr,
         shrNum;

      getField (ifds::TaxType, taxType, idDataGroup);
      getField (ifds::AcctType, acctType, idDataGroup);
      getField (ifds::ShrNum, shrNum, idDataGroup);

      Shareholder *pShareholder (NULL);
      
      if (getWorkSession().getShareholder (idDataGroup, shrNum, pShareholder) <= WARNING &&
          pShareholder)
      {
         pShareholder->getField (ifds::TaxJurisCode, taxJuris, idDataGroup);
         pShareholder->getField (ifds::TaxJurisCode, taxJurisDescr, idDataGroup, true);
      }
      //values 6 and 7 are only allowed for the provice of Quebec
      if ( taxJuris != I_("0006") && 
          //(strValue == I_("6") || 
          // strValue == I_("7")))
          strValue == I_("7"))
      {
         //raise error
         DString recCodeDescr,
            idiStr;
         
         getField (ifds::RecipientType, recCodeDescr, idDataGroup, true);
         addIDITagValue (idiStr, I_("REC"), recCodeDescr);
         addIDITagValue (idiStr, I_("JURISD"), taxJurisDescr);
         ADDCONDITIONFROMFILEIDI (CND::ERR_RECIPIENT_TYPE_NOT_VALID_FOR_JURISDICTION, idiStr);
      }
   }
   else if ( idField == ifds::SiblingOnly )
   {
      validateSiblingOnly(idDataGroup);
   }
   else if ( idField == ifds::SocialCode )
   {
      // validate social code for SSG.
      // Social code list is applicable for SSG but it is not applicable for other clients.
      if ( DSTCommonFunctions::codeInList (strValue, SSG_SOCIAL_CODE_LIST) )
      {
         getErrMsg (IFASTERR::SOCIAL_CODE_NOT_APPLICABLE,
                    CND::ERR_SOCIAL_CODE_NOT_APPLICABLE,
                    CND::WARN_SOCIAL_CODE_NOT_APPLICABLE,
                    idDataGroup);
      }
   }
   else if ( idField == ifds::PortfolioXEdit )
   {
      validatePortfolioField(idDataGroup);
   }
   else if ( idField == ifds::BrokerBranchRepXEdit)
   {
      DString brokerCode, branchCode, slsRep;
      getField (ifds::BrokerCode, brokerCode, idDataGroup,false);
      getField( ifds::BranchCode, branchCode, idDataGroup,false );
      getField( ifds::Slsrep,slsRep, idDataGroup,false );
      brokerCode.strip().upperCase();
      branchCode.strip().upperCase();
      slsRep.strip().upperCase();

      validateBlockTransfer(brokerCode,branchCode,slsRep,idDataGroup);
   }
    else if(idField == ifds::StopAdjDate)
   { //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
      validationStopAdjustmentDate(strValue, idDataGroup);  
   } 
    else if(idField == ifds::InitialDate || idField == ifds::NetTransAmtAsOfDate)
    {
       DString dstrCurrBusDate;
       getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, BF::HOST,false );

       if(DSTCommonFunctions::CompareDates(strValue, dstrCurrBusDate) == 
          DSTCommonFunctions::SECOND_EARLIER)
       {
          ADDCONDITIONFROMFILE(CND::ERR_DATE_CANNOT_BE_FUTURE);
       }
       DString dstrEffectiveDate;
       getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
       if(DSTCommonFunctions::CompareDates(strValue, dstrEffectiveDate) == 
          DSTCommonFunctions::FIRST_EARLIER)
       {
          ADDCONDITIONFROMFILE(CND::ERR_DATE_CANNOT_BE_EARLIER_THAN_ACCOUNT_EFFECTIVE);
       }
    }
    else if(idField == ifds::InitialMarketValue || idField == ifds::NetTransAmt)
    {
       double value = DSTCommonFunctions::convertToDouble(strValue);
       if(value < 0.0)
       {
          ADDCONDITIONFROMFILE(CND::ERR_INVALID_NEGATIVE_AMOUNT);
       }
    }
    else if(idField == ifds::InitDateNetTransAmtAsOfXEdit)
    {
       DString dstrInitialDate, dstrNetTransAmtAsOfDate;

       getField(ifds::InitialDate, dstrInitialDate, idDataGroup);
       getField(ifds::NetTransAmtAsOfDate, dstrNetTransAmtAsOfDate, idDataGroup);

       if(DSTCommonFunctions::CompareDates(dstrInitialDate, dstrNetTransAmtAsOfDate) ==
          DSTCommonFunctions::SECOND_EARLIER)
       {
         ADDCONDITIONFROMFILE(CND::ERR_NET_TRANS_AMT_CANNOT_BE_EARLIER_THAN_INIT_DATE);
       }
    }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY MFAccount::validateLengthForBrokerBranchSalsRep(const DString& dstrType,
                                                         const DString& strValue,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateLengthForBrokerBranchSalsRep" ) );
   DString dstrValue(strValue);
   dstrValue.strip();
   ErrMsgRulesList* pErrMsgRulesList = NULL;
   long lErr5Char,lWar5Char,lErr6Char;
   if( dstrValue.size() >= 6 )
   {
      SEVERITY sevRtn = getMgmtCo ().getErrMsgRulesList( pErrMsgRulesList);  
      if( pErrMsgRulesList )
      {
         if(dstrType == I_("SalsRep") )
         {
            lErr5Char = CND::ERR_SALS_CODE_HAS_TO_BE_5;
            lWar5Char = CND::WAR_SALS_CODE_HAS_TO_BE_5;

            pErrMsgRulesList->getEWI (I_("414"), lErr5Char,lWar5Char,idDataGroup);
         }
      }
      SEVERITY  sev = GETCURRENTHIGHESTSEVERITY ();
      if (sev > WARNING ) 
      {
         return sev; // we will not add more condition here, because it is already critical
      }
   }
   if(dstrValue.size() > 6 )
   {
      if(dstrType == I_("SalsRep") )
      {
         lErr6Char = CND::ERR_SALES_CODE_CAN_NOT_LONGER_THAN_6;
      }
      ADDCONDITIONFROMFILE( lErr6Char );
   }
   return(GETCURRENTHIGHESTSEVERITY());

}
//******************************************************************************
SEVERITY MFAccount::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   bool bIsRES2Client = getWorkSession ().isRES2Client();
   bool bTaxmodelNA = true;
   if (idField == ifds::TaxType /*&& idDataGroup != BF::HOST*/)
   {
      loadSettleCurrencySubstitutionList(idDataGroup);
      //Rule: If TaxType-76 = B, then system automatically assign AcctType-76 = '0' and 
      //   RecipientType-76 = '1' and skip update of these two fields (LIP product enhancement)

      //if SWP is allowed for the new tax type, we should ask user if he/she wants to stop SWPs or not
      TaxTypeRule *pTaxTypeRule = NULL;
      if( getTaxTypeRule ( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
      {
         DString strSWPallowed, strSWPExist;
         getField(ifds::SWP, strSWPExist, idDataGroup, false);
         if( strSWPExist.strip() == YES )
         {
            pTaxTypeRule->getField(ifds::SWPallowed, strSWPallowed, idDataGroup, false);
            if( strSWPallowed.strip() == YES )
               setFieldNoValidate(ifds::ShouldAskForSWPStop, YES, idDataGroup, false);
            else
               setFieldNoValidate(ifds::ShouldAskForSWPStop, NO, idDataGroup, false);
         }

         // assign tax type related fields that assigned by view 4 for existing account. 
         // assignment here take care of new account and change tax type for existing account
         DString dstrTaxRuleField;
         pTaxTypeRule->getField(ifds::LockedIn, dstrTaxRuleField, idDataGroup, false);
         setFieldNoValidate(ifds::LockedIn, dstrTaxRuleField, idDataGroup, false, true, false, false);

         pTaxTypeRule->getField(ifds::SelfDirected, dstrTaxRuleField, idDataGroup, false);
         setFieldNoValidate(ifds::SelfDirected, dstrTaxRuleField, idDataGroup, false, true, false, false);

         pTaxTypeRule->getField(ifds::MaximumApplies, dstrTaxRuleField, idDataGroup, false);
         setFieldNoValidate(ifds::MaxApplies, dstrTaxRuleField, idDataGroup, false, true, false, false);

         pTaxTypeRule->getField(ifds::PlanType, dstrTaxRuleField, idDataGroup, false);
         setFieldNoValidate(ifds::PlanType, dstrTaxRuleField, idDataGroup, false, true, false, false);

         pTaxTypeRule->getField(ifds::FedJurisAllowed, dstrTaxRuleField, idDataGroup, false);
         setFieldNoValidate(ifds::FedJurisAllowed, dstrTaxRuleField, idDataGroup, false, true, false, false);

         DString dstrAcctType, dstrTaxType;
         getField( ifds::AcctType, dstrAcctType, idDataGroup, false );
         getField( ifds::TaxType, dstrTaxType, idDataGroup, false );

         if (!dstrAcctType.empty() && !dstrTaxType.empty())
         {
            Shareholder* pShareholder = NULL;
            //dstrPensionJuris is renamed to dstrTaxJurisCode.
            DString dstrTaxJurisCode;
            DString canada_province = CANADA_PROVINCE;
            if( getShareholder( pShareholder, idDataGroup ) <= WARNING )
            {
               if( pShareholder )
               {
                  pShareholder->getField( ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup );			   
               }
            }
            if( !(( dstrAcctType == INDIVIDUAL_ACCT_TYPE || 
                    dstrAcctType == JOINT_ACCT_TYPE ) && getWorkSession().isNonRegLike( dstrTaxType ) ) 
            && ( canada_province.find(dstrTaxJurisCode) == DString::npos ) )
            {
               setFieldReadOnly (ifds::AcctPurpose, idDataGroup, true);
               setFieldNoValidate(ifds::AcctPurpose, I_( "" ), idDataGroup, true, true, true );
            }
            else 
            {
               setFieldReadOnly( ifds::AcctPurpose, idDataGroup, false );		   
            }
         }
      }

      DString taxType;

      getField (ifds::TaxType, taxType, idDataGroup, false);
      taxType.strip();

      if ( getWorkSession ().isLIFLike (taxType) || 
           LRIF_TAX_TYPE == taxType )
      {
         setFieldNoValidate (ifds::AcctType, INDIVIDUAL_ACCT_TYPE, idDataGroup, false, true, true);
         setFieldReadOnly (ifds::AcctType, idDataGroup, true );
      }
      else
      {
         setFieldReadOnly( ifds::AcctType, idDataGroup, false );
      }

      if ( getWorkSession ().isLIFLike (taxType) ||
           getWorkSession ().isLIRALike (taxType) ||
           LRIF_TAX_TYPE == taxType ||
           PRIF_TAX_TYPE == taxType)
      {
         setFieldReadOnly (ifds::PensionJuris, idDataGroup, false);
         setValidFlag (ifds::PensionJuris, idDataGroup, false);
      }
      else
      {
         setFieldNoValidate (ifds::PensionJuris, NULL_STRING, idDataGroup, false, true, true);
         setFieldReadOnly (ifds::PensionJuris, idDataGroup, true);
      }
      
      // Set Stop Redemption - If LIRA set to YES otherwise NO
      if (isNew())
      {
         setFieldNoValidate( ifds::StopRed, 
             (( getWorkSession ().isLIRALike (taxType))) ? YES : NO, idDataGroup, false, true, true );
      }

      setField(ifds::Pre98Contrib, I_( "N" ), idDataGroup, false );
      setField(ifds::CESGEligible, I_( "N" ), idDataGroup, false );

      if ( taxType.strip().upperCase() == INDIVIDUAL_RESP_TAX_TYPE )
      {
         setFieldNoValidate(ifds::SiblingOnly, I_( "Y" ), idDataGroup, false, false );

         // reset hrdc relate code
         DString accountNum;
         AccountEntityXref *pAccountEntityXref (NULL);

         getField (ifds::AccountNum, accountNum, idDataGroup);
         if (getAccountEntityXref (pAccountEntityXref, idDataGroup) <= WARNING)
         {
            BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                                idDataGroup, 
                                                true, 
                                                BFObjIter::ITERTYPE::NON_DELETED);

            DString searchKey;

            AccountEntityXref::buildPartialKeyForAccount (searchKey, accountNum);
            iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
            while (!iterAccountEntityXrefOut.end())
            {
               AccountEntityXrefObject *pObj =
                     dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXrefOut.getObject());

               if ( pObj )
               {
                  DString strEntityType;
                  pObj->getField( ifds::EntityType, strEntityType, idDataGroup, false );
                  strEntityType.strip().upperCase();

                  if ( strEntityType == RESP_BENEFICIARY_ENTITY_TYPE)
                  {
                     pObj->resetSubstitutionsRelateCodeForRESP(idDataGroup);
                  }
               }

               ++iterAccountEntityXrefOut;
            }
         }
      }
      else if ( taxType.strip().upperCase() == FAMILY_RESP_TAX_TYPE )
      {
         setFieldNoValidate(ifds::SiblingOnly, I_( "" ), idDataGroup, false, false );

         // set hrdc relate code for M
         DString accountNum;
         AccountEntityXref *pAccountEntityXref (NULL);

         getField (ifds::AccountNum, accountNum, idDataGroup);
         if (getAccountEntityXref (pAccountEntityXref, idDataGroup) <= WARNING)
         {
            BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                                idDataGroup, 
                                                true, 
                                                BFObjIter::ITERTYPE::NON_DELETED);

            DString searchKey;

            AccountEntityXref::buildPartialKeyForAccount (searchKey, accountNum);
            iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
            while (!iterAccountEntityXrefOut.end())
            {
               AccountEntityXrefObject *pObj =
                     dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXrefOut.getObject());

               if ( pObj )
               {
                  DString strEntityType;
                  pObj->getField( ifds::EntityType, strEntityType, idDataGroup, false );
                  strEntityType.strip().upperCase();

                  if ( strEntityType == RESP_BENEFICIARY_ENTITY_TYPE)
                  {
                     pObj->initSubstitutionsRelateCodeForRESP(idDataGroup);
                  }
               }

               ++iterAccountEntityXrefOut;
            }
         }
      }
      else if (taxType == TAX_TYPE_OA || taxType == TAX_TYPE_SA  || taxType == TAX_TYPE_SRS)
      {
         setFieldNoValidate(ifds::ConsolTypePW, REDIRECT_TO_RA_ID, idDataGroup, false);
         setFieldNoValidate(ifds::ConsolTypeID, REDIRECT_TO_RA_ID, idDataGroup, false);
         setFieldNoValidate(ifds::ConsolTypeED, REDIRECT_TO_RA_ID, idDataGroup, false);
      }
      //if lockedIn couldn't be read, what should we do here??

      setRecipientType (idDataGroup); // set default value
      loadAcctTypeSubstitutionList (idDataGroup);
      loadTaxTypeSubstitutionList (idDataGroup);
      refreshDefaultAddress01 (idDataGroup);
      checkDefaultMailingInfo (idDataGroup);

      DString dstrAcctType;

      getField (ifds::AcctType, dstrAcctType, idDataGroup, false);
      if (dstrAcctType == LOCKED_IN && taxType == RRSP_TAX_TYPE)
      {
         if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
         {
            setFieldRequired( ifds::PensionLegCode, idDataGroup, true);
            setValidFlag (ifds::PensionLegCode, idDataGroup, false);
         }
      }

   }
   else if( idField == ifds::AcctType)
   {
      setRecipientType ( idDataGroup ); // set default value
      DString dstrAcctType,dstrDfltConfDetlKeyValue,dstrDfltConfDetlDefValue;
	  std::map<DString, DString> mAccTypeTaxModel;
	  getWorkSession().getOption( ifds::DfltConfDetlKeyValue, dstrDfltConfDetlKeyValue, idDataGroup, false);
	  getWorkSession().getOption( ifds::DfltConfDetlDefValue, dstrDfltConfDetlDefValue, idDataGroup, false);
	  DString tmpDfltConfDetlKeyValue = dstrDfltConfDetlKeyValue;
	  DString tmpDfltConfDetlDefValue = dstrDfltConfDetlDefValue;
	  while((tmpDfltConfDetlKeyValue != NULL_STRING ) && (tmpDfltConfDetlDefValue != NULL_STRING))
	  {
		  DString::size_type pos = 0;
		  DString dstrAcctTypeList, dstrAcctTypeCode,dstrTaxModel;
		  
		  EXTRACT_VALUE(tmpDfltConfDetlKeyValue, dstrAcctTypeCode);
		  EXTRACT_VALUE(tmpDfltConfDetlDefValue, dstrTaxModel);
		  CHOP_STRING(tmpDfltConfDetlKeyValue);
		  CHOP_STRING(tmpDfltConfDetlDefValue);
		  mAccTypeTaxModel.insert(std::make_pair(dstrAcctTypeCode,dstrTaxModel));
	  }
	  
      getField( ifds::AcctType, dstrAcctType, idDataGroup, false);
      if( dstrAcctType != CORPORATE_ACCT_TYPE )
      {
         setFieldNoValidate( ifds::BusinessNo, NULL_STRING, idDataGroup, false, false, true );
         setFieldReadOnly( ifds::BusinessNo, idDataGroup, true);
      }
      else
      {
         setFieldReadOnly( ifds::BusinessNo, idDataGroup, false);
      }
      DString dstrTaxType;
      getField( ifds::TaxType, dstrTaxType, idDataGroup );
      if( dstrAcctType == LOCKED_IN && dstrTaxType == RRSP_TAX_TYPE )
      {
         if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
         {
            setFieldRequired( ifds::PensionLegCode, idDataGroup, true );
            setValidFlag( ifds::PensionLegCode, idDataGroup, false );
         }
      }

      if (!dstrAcctType.empty() && !dstrTaxType.empty())
      {
         Shareholder* pShareholder = NULL;
         //dstrPensionJuris is renamed to dstrTaxJurisCode.
         DString dstrTaxJurisCode;
         DString canada_province = CANADA_PROVINCE;
         if( getShareholder( pShareholder, idDataGroup ) <= WARNING )
         {
            if( pShareholder )
            {
               pShareholder->getField( ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup );			   
            }
         }
         if( !(( dstrAcctType == INDIVIDUAL_ACCT_TYPE || 
                 dstrAcctType == JOINT_ACCT_TYPE ) && getWorkSession().isNonRegLike( dstrTaxType ) ) 
            && ( canada_province.find(dstrTaxJurisCode) == DString::npos ) )
         {
            setFieldReadOnly (ifds::AcctPurpose, idDataGroup, true);
            setFieldNoValidate(ifds::AcctPurpose, I_( "" ), idDataGroup, true, true, true );
         }
         else 
         {
            setFieldReadOnly( ifds::AcctPurpose, idDataGroup, false );		   
         }
      }
      if(DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG)
      {
        if( ACCOUNT_TYPE::INDIVIDUAL_ACCT_TYPE == dstrAcctType ||
            ACCOUNT_TYPE::SPOUSAL_ACCT_TYPE    == dstrAcctType ||
            ACCOUNT_TYPE::JOINT_ACCT_TYPE      == dstrAcctType )
            setFieldNoValidate( ifds::InvestorClassification, INV_CLASSIFICATION::RETAIL, idDataGroup, false, false, true );
        else
          setFieldNoValidate( ifds::InvestorClassification, INV_CLASSIFICATION::PROFESSIONAL, idDataGroup, false, false, true );
      }
	 if(!mAccTypeTaxModel.empty())
	  {
		  std::map<DString,DString>::const_iterator it;

		  for (it=mAccTypeTaxModel.begin(); it!=mAccTypeTaxModel.end(); ++it)
		  {

			  DString dstrFirst,dstrSecond;
			  dstrFirst=it->first;
			  dstrSecond=it->second;
			  if(dstrFirst == dstrAcctType)
			  {
				  setFieldNoValidate( ifds::AcctTaxModel, dstrSecond, idDataGroup, false, false, true );
				  bTaxmodelNA = false;
				  break;
			  }
			  else
			  {
				  DString dstrAcctTaxModel;
				  getField (ifds::AcctTaxModel, dstrAcctTaxModel, idDataGroup);
				  if (!dstrAcctTaxModel.empty())
					  setFieldNoValidate( ifds::AcctTaxModel, I_( "" ), idDataGroup, false, false, true );
			  }
		  }
	  }
	  if(bTaxmodelNA == true)
	  setFieldNoValidate( ifds::AcctTaxModel, TAX_MODEL::NOT_APPLICABLE, idDataGroup, false, false, true );
 }
   else if( idField == ifds::BrokerCode )
   {
      setValidFlag(ifds::AltAccount, idDataGroup, false);
      if( slsRepByBranch (idDataGroup) ) // blank out the branchcode trigger the blanking out of salesrep
      {
         //clear the name, clears out related fields, branch
         _branchName = NULL_STRING;
         //mark the field as invalid and notify the observers
         setFieldNoValidate( ifds::BranchCode, NULL_STRING, idDataGroup, false, false, true );
      }
      else // blank out salesrep -> trigger branch code assignment
      {
         _agentName     = NULL_STRING;
         _agentAltName  = NULL_STRING;
         _branchName    = NULL_STRING;
         _branchCode    = NULL_STRING;

         DString brokerBranch, branchCode, brokerCode;

         if( getWorkSession().getOption( ifds::BrokerBranch, brokerBranch, idDataGroup, false ) <= WARNING )
         {
            getField( ifds::BrokerCode, brokerCode, idDataGroup );
            if( brokerBranch == YES )
            {
               branchCode = brokerCode;
            }
            else if( brokerBranch == NO )
            {
               branchCode = I_( "0000" );
            }
         }

         setFieldNoValidate( ifds::BranchCode, branchCode, idDataGroup, false, false, true );
         setFieldNoValidate( ifds::Slsrep, NULL_STRING, idDataGroup, false, false, true );
      }
      setFieldNoValidate (ifds::BrokerName, _brokerName, idDataGroup, false, true, true);
      refreshDefaultAddress01 (idDataGroup);
      checkNetworkControlind (idDataGroup);

      DString dstrBrokerCodeNew, dstrBrokerCodeOrg;
      getField( ifds::BrokerCode, dstrBrokerCodeNew, idDataGroup, false );
      getField( ifds::BrokerCode, dstrBrokerCodeOrg, BF::HOST, false );
      if ( dstrBrokerCodeNew != dstrBrokerCodeOrg )
      {
         checkNSCCBroker( idDataGroup );
      }
   }
   else if( idField == ifds::ClearingFirm )
   {
      DString dstrClearingFirm;
      getField( ifds::ClearingFirm, dstrClearingFirm, idDataGroup );
      dstrClearingFirm.strip();
      if ( dstrClearingFirm != NULL_STRING )
         setParticipantID( dstrClearingFirm, idDataGroup );

      // force to do validation for AgentForFirm and TPA
      setFieldUpdated( ifds::ParticipantID, idDataGroup, true );
      setFieldUpdated( ifds::AgentForFirm, idDataGroup, true );
      //setFieldValid( ifds::AgentForFirm, idDataGroup, false );

      setFieldUpdated( ifds::TPA, idDataGroup, true );
      //setFieldValid( ifds::TPA, idDataGroup, false );

   }
   else if( idField == ifds::BranchCode )
   {
      //clear the names
      if( slsRepByBranch ( idDataGroup ) ) // get the branch code and name from view 92 
      {
         _agentName = NULL_STRING;
         _agentAltName = NULL_STRING;
         //notify the observers
         setFieldNoValidate( ifds::Slsrep, NULL_STRING, idDataGroup, false, false, true );
      }
      setFieldNoValidate( ifds::BranchName, _branchName, idDataGroup, false, true, true );
   }
   else if( idField == ifds::Slsrep )
   {
      setFieldNoValidate( ifds::SlsrepAltName, _agentAltName, idDataGroup, false, true, true );
      setFieldNoValidate( ifds::SlsrepName, _agentName, idDataGroup, false, true, true );

      if( !slsRepByBranch ( idDataGroup ) ) // get the branch code and name from view 92 
      {
         setFieldNoValidate( ifds::BranchCode, _branchCode, idDataGroup, false, true, true );
         setFieldNoValidate( ifds::BranchName, _branchName, idDataGroup, false, true, true );
      }
   }
   else if( idField == ifds::AccountNum )
   {
      //check if the account number is valid,
      //and only in that case do the refresh of the clone
      if( isFieldValid( ifds::AccountNum, idDataGroup ) )
      {
         DString newAccountNum;

         //new account number
         getField( ifds::AccountNum, newAccountNum, idDataGroup );
         //if the value of the account number has changed,
         //flip the AccountNumManual to yes
         if( isNew() &&  _initAccountNum != NULL_STRING && //only if is new allow the account number manual to be set
             newAccountNum != _initAccountNum ) //the account numbers are different
         {
            //no side effect is needed
            setFieldNoValidate( ifds::AccountNumManual, YES, idDataGroup, false );
            //we need to refresh everything we've cloned;

            AccountEntityXref *pAccountEntityXref = NULL;

            if( getAccountEntityXref( pAccountEntityXref, idDataGroup ) <= WARNING )
            {
               //walk the cross AccountEntityXref for the old number 
               //and set the account num correct
               if( pAccountEntityXref != NULL )
               {
                  DString searchKey;

                  BFObjIter bfIter( *pAccountEntityXref, idDataGroup, true );

                  AccountEntityXref::buildPartialKeyForAccount( searchKey, _initAccountNum );
                  for( bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ); !bfIter.end(); ++bfIter )
                  {
                     //set the new account number on the objects,
                     //when commiting this the keys would be in sink
                     bfIter.getObject()->setField( ifds::AccountNum, newAccountNum, idDataGroup );
                  }
               }
            }

            Shareholder *pShareholder = NULL;

            if( getShareholder( pShareholder, idDataGroup ) <= WARNING )
            {
               AccountMailingList *pAccountMailingList;

               //refresh the account mailing list
               if( pShareholder->getAccountMailingList( pAccountMailingList, idDataGroup ) <= WARNING )
               {
                  DString strKey;
                  BFObjIter mailingIter( *pAccountMailingList, idDataGroup );

                  for( mailingIter.begin(); !mailingIter.end(); ++mailingIter )
                  {
                     AccountMailingInfo* pAccountMailingInfo = 
                     dynamic_cast<AccountMailingInfo*>( mailingIter.getObject() );

                     if( pAccountMailingInfo != NULL )
                     {
                        DString mailingAccountNum;

                        pAccountMailingInfo->getField( ifds::AccountNum, mailingAccountNum, idDataGroup );
                        if( mailingAccountNum == _initAccountNum )
                        {
                           //set the account number to the new mailing info
                           pAccountMailingInfo->setField( ifds::AccountNum, newAccountNum, idDataGroup );
                        }
                     }
                  }
               }
            }
         }
      }
   }
   else if( idField == ifds::CreateRep )
   {
      DString createRep;

      getField( ifds::CreateRep, createRep, idDataGroup );
      if( createRep == YES )
      {
         //should validate the Slsrep field
         setValidFlag( ifds::Slsrep, idDataGroup, true );

         DString slsrepcode;

         getField( ifds::Slsrep, slsrepcode, idDataGroup );
         //this will clear the field errors
         validateField( ifds::Slsrep, slsrepcode, idDataGroup );
      }
      //either way, reset the shouldAskForRep field
      setFieldNoValidate( ifds::ShouldAskForRep, NO, idDataGroup, false );
      //clear the update flag
      setUpdatedFlag( ifds::ShouldAskForRep, idDataGroup, false );
   }
   else if (idField == ifds::AcctGroup)
   {
      setFieldNoValidate (ifds::AcctGroupName, _GroupName, idDataGroup, true, true, true);

      ProdPortfolioInfoList* pProdPortfolioInfoList (NULL);
      DString strAcctGroup;
      getField (ifds::AcctGroup, strAcctGroup, idDataGroup, false);

      if (getProdPortfolioInfoList (pProdPortfolioInfoList, idDataGroup, true ) <= WARNING && 
          pProdPortfolioInfoList)
      {
         DString strProdPortfolioSubtList;
         
         if( pProdPortfolioInfoList->getSubstitutionList (strProdPortfolioSubtList, idDataGroup) <= WARNING &&
             !strProdPortfolioSubtList.empty())
         {
            BFProperties *pBFProperties = getFieldProperties (ifds::ProdPortfolioUUID, idDataGroup);

            setFieldAllSubstituteValues (ifds::ProdPortfolioUUID, idDataGroup, strProdPortfolioSubtList);
            pBFProperties->setSubstituteValues (NULL);
            setFieldValid( ifds::ProdPortfolioUUID, idDataGroup, false );
            setFieldValid( ifds::ProdPortfolioPlanUUID, idDataGroup, false );
         }
         else
         {
            // reset portoflio and plan lists:
            setFieldAllSubstituteValues (ifds::ProdPortfolioUUID, idDataGroup, NULL_STRING);
            setFieldAllSubstituteValues (ifds::ProdPortfolioPlanUUID, idDataGroup, NULL_STRING);
            setFieldNoValidate( ifds::ProdPortfolioUUID, NULL_STRING, idDataGroup, false, false, true, true );
            setFieldNoValidate( ifds::ProdPortfolioPlanUUID, NULL_STRING, idDataGroup, false, false, true, true );
         }  
      }
   }
   else if (idField == ifds::EffectiveDate)
   {
      DString dstrDate;
      getField( ifds::EffectiveDate, dstrDate, idDataGroup, false );
      setFieldNoValidate( ifds::FirstEffective, dstrDate, idDataGroup, false );
      setValidFlag( ifds::BrokerCode, idDataGroup, false );
      if ( slsRepByBranch ( idDataGroup ) ) {
         setValidFlag( ifds::BranchCode, idDataGroup, false );
      }
      DString createRep;
      getField( ifds::CreateRep, createRep, idDataGroup );
      if( createRep == NO ) {
         setValidFlag( ifds::Slsrep, idDataGroup, false );
      }
   }
   else if (idField == ifds::InterCode)
   {
      refreshDefaultAddress01 (idDataGroup);
   }
   else if( idField == ifds::AcctDesignation )
   {
      refreshDefaultAddress01(idDataGroup);
      checkDefaultMailingInfo(idDataGroup);
   }
   /*
   else if( idField == ifds::AMSCode )
   {
      DString dstrAMSCode, dstrAMSType, dstrDefaultAlloc, dstrAccountNumber;
      
      // Delete Default Fund Allocation for RO Code
      getField( ifds::AccountNum, dstrAccountNumber, idDataGroup );
      getField( ifds::AMSCode, dstrAMSCode, idDataGroup);

      if( !dstrAMSCode.empty() )
      {
         setFieldRequired( ifds::Rebalance, idDataGroup, false );
         setFieldRequired( ifds::UpdatePACSWP, idDataGroup, false );
         setField( ifds::Rebalance, NULL_STRING, idDataGroup, false, true );
         setField( ifds::UpdatePACSWP, NULL_STRING, idDataGroup, false, true );
         
         setValidFlag( ifds::Rebalance, idDataGroup, false);
         setValidFlag( ifds::UpdatePACSWP, idDataGroup, false);
         setFieldRequired( ifds::Rebalance, idDataGroup, true );
         setFieldRequired( ifds::UpdatePACSWP, idDataGroup, true );
         setFieldReadOnly( ifds::Rebalance, idDataGroup, false );
         setFieldReadOnly( ifds::UpdatePACSWP, idDataGroup, false );
      }
      else
      {
         clearFieldErrors( ifds::Rebalance, idDataGroup );
         clearFieldErrors( ifds::UpdatePACSWP, idDataGroup );
         setField( ifds::Rebalance, I_("N"), idDataGroup, false, true );
         setField( ifds::UpdatePACSWP, I_("N"), idDataGroup, false, true );
      }


      // Get pointer to master list
      Shareholder *pShareholder = NULL;
      
      DString dstrEffectiveDate(NULL_STRING);
      getWorkSession().getDateInHostFormat(dstrEffectiveDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   
      AMSMstrList* pAMSMstrList = NULL;	

      getAMSMstrList( pAMSMstrList, idDataGroup,dstrEffectiveDate );		
      pAMSMstrList->getFieldByAMSCode(I_("RB"),dstrAMSCode,dstrEffectiveDate,ifds::DefaultAlloc,dstrDefaultAlloc,idDataGroup,false);

      // If the input AMSCode should not have account level override allocation set up, then delete the RB allocation
      if ( dstrDefaultAlloc.empty() || dstrDefaultAlloc == I_("N") )      
      {
         if( getShareholder( pShareholder, idDataGroup ) <= WARNING && pShareholder )
         {
            ShrAllocTypeList *pShrAllocTypeList = NULL;

            pShareholder->getAllocationList( pShrAllocTypeList, idDataGroup, true );
            if( pShrAllocTypeList )
            {
               pShrAllocTypeList->removeShrAllocType( dstrAccountNumber, I_("RB"), NULL_STRING, idDataGroup );
            }            
         }
      }
   }
   else if( idField == ifds::AMSROCode ) 
   {
      DString dstrAMSROCode, dstrAMSType, dstrDefaultAlloc, dstrAccountNumber;
      
      // Delete Default Fund Allocation for RO Code
      getField( ifds::AccountNum, dstrAccountNumber, idDataGroup );
      getField( ifds::AMSROCode, dstrAMSROCode, idDataGroup);

      // Get pointer to master list
      Shareholder *pShareholder = NULL;
      AMSMstrList *pAMSMstrList = NULL;

      DString dstrEffectiveDate(NULL_STRING);
      getWorkSession().getDateInHostFormat(dstrEffectiveDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);  
      getAMSMstrList( pAMSMstrList, idDataGroup,dstrEffectiveDate );			  
      pAMSMstrList->getFieldByAMSCode(I_("RO"),dstrAMSROCode,dstrEffectiveDate,ifds::DefaultAlloc,
         dstrDefaultAlloc,idDataGroup,false);


      // If the input AMSCode should not have account level override allocation set up, then delete the RB allocation
      if ( dstrDefaultAlloc.empty() || dstrDefaultAlloc == I_("N") )
      {
         if( getShareholder( pShareholder, idDataGroup ) <= WARNING && pShareholder )
         {
            ShrAllocTypeList *pShrAllocTypeList = NULL;

            pShareholder->getAllocationList( pShrAllocTypeList, idDataGroup, true );
            if( pShrAllocTypeList )
            {
               pShrAllocTypeList->removeShrAllocType( dstrAccountNumber, I_("RO"), NULL_STRING, idDataGroup );
            }            
         }
      }
   }
   else if( idField == ifds::AMSType )
   {
      // force to do validation for ams code if AMSType changed
      setFieldUpdated( ifds::AMSCode, idDataGroup, true );
      setFieldValid( ifds::AMSCode, idDataGroup, false );
   }
   */

   //for the COA flags, reset the updated flag, no need to send updates if the
   //app is setting those flags
   else if( idField == ifds::PendingTrade || idField == ifds::Certificates ||
            idField == ifds::SystemTrsfr || idField == ifds::PAC || 
            idField == ifds::SWP || idField == ifds::AcctAlloc || 
            idField == ifds::ClanPlan || idField == ifds::UnsettledTrn ||
            idField == ifds::LockedIn || idField == ifds::SettledFieldsInitialized ||
            idField == ifds::SettledValue || idField == ifds::UnsettledValue ||
            idField == ifds::ShouldAskForSWPStop || idField == ifds::StopSWP ||
            idField == ifds::AcctCategoryExist
          )
   {
      setUpdatedFlag( idField, idDataGroup, false );
   }
   else if( idField == ifds::TaxTypeAcctType )
   {
      DString dstrAcctType, dstrTaxType;
      getField( ifds::AcctType, dstrAcctType, idDataGroup, false );
      getField( ifds::TaxType, dstrTaxType, idDataGroup, false );

      if (!dstrAcctType.empty() && !dstrTaxType.empty())
      {
         Shareholder* pShareholder = NULL;
         //dstrPensionJuris is renamed to dstrTaxJurisCode.
         DString dstrTaxJurisCode;
         DString canada_province = CANADA_PROVINCE;
         if( getShareholder( pShareholder, idDataGroup ) <= WARNING )
         {
            if( pShareholder )
            {
               pShareholder->getField( ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup );			   
            }
         }
         if( !(( dstrAcctType == INDIVIDUAL_ACCT_TYPE || 
                 dstrAcctType == JOINT_ACCT_TYPE ) && getWorkSession().isNonRegLike( dstrTaxType ) ) 
            && ( canada_province.find(dstrTaxJurisCode) == DString::npos ) )
         {
            setFieldReadOnly (ifds::AcctPurpose, idDataGroup, true);
            setFieldNoValidate(ifds::AcctPurpose, I_( "" ), idDataGroup, true, true, true );
         }
         else 
         {
            setFieldReadOnly( ifds::AcctPurpose, idDataGroup, false );
         }
      }
   }
   else if ( ifds::PensionJuris == idField )
   {
      setFieldValid( ifds::TaxType, idDataGroup, false );
   }
   else if (ifds::ActiveOnly == idField)
   {
      setFieldUpdated (idField, idDataGroup, false );
   }
   else if (ifds::ProdPortfolioUUID == idField)
   {
      ProdPortfolioPlanInfoList *pProdPortfolioPlanInfoList (NULL);
      DString prodPortfolioUUID;

      getField (ifds::ProdPortfolioUUID, prodPortfolioUUID, idDataGroup, false);

      //call view 419
      if ( getProdPortfolioPlanInfoList (pProdPortfolioPlanInfoList, prodPortfolioUUID, idDataGroup) <= WARNING && 
           pProdPortfolioPlanInfoList)
      {
         DString strProdPortfolioPlanSubtList;
         
         if ( pProdPortfolioPlanInfoList->getSubstitutionList (strProdPortfolioPlanSubtList, idDataGroup) <= WARNING &&
              !strProdPortfolioPlanSubtList.empty())
         {
            BFProperties *pBFProperties = getFieldProperties (ifds::ProdPortfolioPlanUUID, idDataGroup);

            setFieldAllSubstituteValues (ifds::ProdPortfolioPlanUUID, idDataGroup, strProdPortfolioPlanSubtList);
            pBFProperties->setSubstituteValues (NULL);
            setFieldNoValidate( ifds::ProdPortfolioPlanUUID, NULL_STRING, idDataGroup, false );
            setFieldValid( ifds::ProdPortfolioPlanUUID, idDataGroup, false );
         }
      }
   }
   else if (ifds::OrgType == idField)
   {
      DString dstrOrgType;
      getField( ifds::OrgType, dstrOrgType, idDataGroup, false );

      if(DSTCommonFunctions::codeInList (dstrOrgType, ERISA_ORG_TYPE))
         setFieldNoValidate( ifds::SubOrgType, I_("02"), idDataGroup, false,true,false,false);
      else if(DSTCommonFunctions::codeInList (dstrOrgType, EXCLUDED_ORG_TYPE))
         setFieldNoValidate( ifds::SubOrgType, I_("03"), idDataGroup, true,true,false,false);
      else
         setFieldNoValidate( ifds::SubOrgType, I_("01"), idDataGroup, true,true,false,false );		   
   }
   else if ( ifds::BrokerBranchRepXEdit == idField)
   {
      refreshShareholder(idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::updateTaxTypeSchedule( const DString& dstrTaxType, 
                                           const DString& dstrTaxTypeSchedule, 
                                           const DString& dstrPensionJuris, 
                                           const DString& dstrEffectiveDate, 
                                           const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "updateTaxTypeSchedule" ) );

   bool blApplicable = false;
   DString strEffectiveDate( dstrEffectiveDate );
   if( strEffectiveDate.strip().empty() )
   {
         getField( ifds::EffectiveDate, strEffectiveDate, idDataGroup );
   }
   strEffectiveDate.strip();
   isTaxTypeScheduleApplicable( blApplicable, dstrTaxType, dstrPensionJuris, strEffectiveDate, idDataGroup );
   if( !blApplicable )
   {
      setFieldNoValidate( ifds::TaxTypeSchedule, I_( "00" ), idDataGroup, true, true, true );
   }
   else
   {
      //even if applicable, we may still need to set TaxTypeSchedule to '00' if the effective date has been changed after grandfathered date
      DString strGrandFatheredDate;
      getGrandfatheredDate( strGrandFatheredDate, idDataGroup, dstrTaxType, SCHEDULE01, dstrPensionJuris );
      if( DSTCommonFunctions::CompareDates( strGrandFatheredDate, strEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER )
      {
         setFieldNoValidate( ifds::TaxTypeSchedule, I_( "00" ), idDataGroup, true, true, true );
      }
   }

   flipReadOnlyForTaxTypeSchedule( strEffectiveDate, idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MFAccount::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   Shareholder *pShareholder = NULL;

   if( getShareholder( pShareholder, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( isNew() )
   {
      AddressList *pAddressList = NULL;
      if( pShareholder->getAddressList( pAddressList, idDataGroup ) <= WARNING )
      {
         BFObjIter addressIter( *pAddressList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

         //more then one address for the shareholder, then add an informational condition
         //on the frame,
         //only if the account is new we should flag this
         if( addressIter.getNumberOfItemsInList() > 1 )
            ADDCONDITIONFROMFILE( CND::INFO_SHAREHOLDER_HAS_MULTIPLE_ADDRESSES );
      }

	  /* P0266360 HSBC Custodian */
	  validateAcctCustodian(idDataGroup);
   }
   else
   {
      if( isUpdatedForDataGroup( idDataGroup, false ) && ( lValidateGroup == ACCOUNT_GROUPING::ACCOUNT_INFO 
         ||  lValidateGroup == 0 ) )//if MFAccount fields have been updated, have to validate AccountEntityXref
      {
         AccountEntityXref *pAccountEntityXref;
         getAccountEntityXref( pAccountEntityXref, idDataGroup );
         if( pAccountEntityXref != NULL )
         {
            DString dstrAcctNum;
            getField ( ifds::AccountNum, dstrAcctNum, idDataGroup);
            pAccountEntityXref->validateOneAccount( dstrAcctNum, idDataGroup );
         }
      }
   }

   DString stopReason;
   getField ( ifds::StopReason, stopReason, idDataGroup);

   // this stop reason can be set by user or by the system
   if ((stopReason == KYC_SYSTEM || stopReason == DECEASED_SYSTEM) && _bStopReasonChanged)
   {
      ADDCONDITIONFROMFILE( CND::ERR_SYSTEM_STOP_REASON);
   }
   
   //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
   DString dstrStopAdjDate;
   getField ( ifds::StopAdjDate, dstrStopAdjDate, idDataGroup); 
   if(!dstrStopAdjDate.strip().empty())
   {
      validationStopAdjustmentDate(dstrStopAdjDate, idDataGroup);
   }

   if (isPortfolioRequired (idDataGroup))
   {
      DString dstrPortfolio, dstrPlan;

      getField (ifds::ProdPortfolioUUID, dstrPortfolio, idDataGroup, false);
      getField (ifds::ProdPortfolioPlanUUID, dstrPlan, idDataGroup, false);

      if (dstrPortfolio.strip().empty() || dstrPlan.strip().empty())
      {
         getErrMsg ( IFASTERR::PROD_PORTFOLIO_RELATED_FIELDS_REQUIRED,
                     CND::ERR_PROD_PORTFOLIO_RELATED_FIELDS_REQUIRED,
                     CND::WARN_PROD_PORTFOLIO_RELATED_FIELDS_REQUIRED,
                     idDataGroup);
      }
   }

   DString dstrBrokerCode, 
      dstrNSCCCompliant;
   getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup);
   if (getWorkSession().getOption( ifds::NSCCCompliant, dstrNSCCCompliant, idDataGroup, false ) <= WARNING )
   {
      if( dstrNSCCCompliant == YES && isBrokerNSCCCompliant( dstrBrokerCode, idDataGroup ) )
      {
         validateTPAClrFirm( idDataGroup );
         validateAgtFirmClrFirm (idDataGroup);

         DString dstrClearingFirm, dstrParticipantID ;
         getField (ifds::ClearingFirm, dstrClearingFirm, idDataGroup);
         dstrClearingFirm.strip();

         if ( dstrClearingFirm != NULL_STRING )
         {
            // Among these three fields, at least one must be equal to the value of the account level broker code
            // Email from Luke on Aug 24 :
            // The Clearing Firm and Agent for Firm or the Clearing Firm and TPA values may be the same. 
            // The Agent for Firm and TPA values cannot be the same.
            validateClrFirmAgtFirmTPA( idDataGroup );
            // Agent for firm and TPA cannot have the same value unless both are blank
            validateAgentTPA( idDataGroup );
         }
         getField (ifds::ParticipantID, dstrParticipantID, idDataGroup);
         dstrParticipantID.strip();
         if ( dstrClearingFirm != NULL_STRING  && dstrParticipantID == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_PARTICIPANTID_MISSING);
         }

      }
   }

   if(!isNew()&& isUpdatedForDataGroup (idDataGroup))
   {
      bool bDisplyWarnSICAV ,bDisplyWarnOEIC;
      displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
      if(bDisplyWarnSICAV)
         ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
      if(bDisplyWarnOEIC)
         ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::checkBroker( const DString& brokerCode, const BFDataGroupId& idDataGroup,
                                 bool condition_returned )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkBroker" ) );

   Broker *pBroker (NULL);
   if ( getBroker (pBroker, brokerCode, idDataGroup) <= WARNING && 
        pBroker) 
   {
      _brokerName = NULL_STRING;

      //checks for the validity of the broker code. by making a view call, and raising a condition
      //we do not want to make the view call when the broker code is NULL, because the view will
      _dstrHouseBroker = pBroker->isHouseBroker ( idDataGroup )?YES:NO;
      DString brokerName;
      pBroker->getField( ifds::BrokerName, brokerName, idDataGroup );

      parseName (brokerName, _brokerName);	

      DString dstrFundAllow;
      pBroker->getField ( ifds::FundAllow, dstrFundAllow, idDataGroup );
      DString dstrCurrBusDate;
      getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
      if ( pBroker->checkEffective ( dstrCurrBusDate, idDataGroup ) <= WARNING )
      {
         if (dstrFundAllow == NO) 
         {
            ADDCONDITIONFROMFILE (CND::ERR_BROKER_NOT_ELIGIBLE_FOR_ACCT);
         }
      }
   }
   
   setFieldNoValidate( ifds::BrokerName, _brokerName, idDataGroup, true, true, true, false);
   
   if (condition_returned)
      return GETCURRENTHIGHESTSEVERITY();
   else
      return NO_CONDITION;
}

//******************************************************************************
SEVERITY MFAccount::checkBranches( const DString& branchCode, const BFDataGroupId& idDataGroup,
                                   bool condition_returned )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkBranches" ) );

   BranchList branchList( *this );
   DString brokerCode;

   getField( ifds::BrokerCode, brokerCode, idDataGroup );
   //checks for the validity of the branch code. by making a view call, and raising a condition
   //we do not want to make the view call when the branch code is NULL, because the view will
   //return us all the branches for this broker
   if( branchCode != NULL_STRING && 
       branchList.init( brokerCode, branchCode ) <= WARNING )
   {
      BFObjIter bfIter( branchList, idDataGroup );
      DString branchName;

      bfIter.begin();
      if( !bfIter.end() )
      {
         DString branchName;
         Branch* pBranch = dynamic_cast <Branch*> ( bfIter.getObject() );
         pBranch->getField( ifds::BranchName, branchName, idDataGroup );

         parseName (branchName, _branchName);

         //getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
         DString dstrCurrBusDate;
         getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false ); 
         pBranch->checkEffective ( dstrCurrBusDate, idDataGroup );
      }
   }
   else
   {
      _branchName = NULL_STRING;

   }
   setFieldNoValidate( ifds::BranchName, _branchName, idDataGroup, true, true, true, false);
   if( condition_returned == true )
      return(GETCURRENTHIGHESTSEVERITY());
   else
      return(NO_CONDITION);
}

//******************************************************************************
SEVERITY MFAccount::checkAgents( const DString& slsrepCode, const BFDataGroupId& idDataGroup,
                                 bool condition_returned, bool& bNewAgent )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkAgents" ) );

   AgentList agentList( *this );
   Agent* pAgent = NULL;
   DString brokerCode, branchCode;

   getField( ifds::BrokerCode, brokerCode, idDataGroup );
   getField( ifds::BranchCode, branchCode, idDataGroup );

   DString dstrAccountNum;
   getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );
   SEVERITY sevRtn;
   if ( isNew() ) {
      sevRtn = agentList.init2( brokerCode, branchCode, slsrepCode, NULL_STRING, NULL_STRING, dstrAccountNum, NULL_STRING ); 
   } else {
      sevRtn = agentList.init2( brokerCode, branchCode, slsrepCode, NULL_STRING, NULL_STRING, dstrAccountNum, I_("Acct") );
   }   

   if (sevRtn > WARNING )
   {
      int count = CONDITIONCOUNT();
      Condition   *c = NULL;
      for( int i = 0; i < count; i++ )
      {
         c = GETCONDITION( i );
         int condCode = c->getCode();
         if ( condCode == CND::ERR_NO_BRANCH_FOUND )
         {
            CLEARCONDITION( i );
            break;
         }
      }

      DString _slsrepCode(slsrepCode);

      //getField (ifds::CreateRep, createRep, idDataGroup, false);
      DString idiStr;
      addIDITagValue( idiStr, I_("AGENT"), _slsrepCode.upperCase() );
      addIDITagValue( idiStr, I_("BROKER"), brokerCode.upperCase() );
      addIDITagValue( idiStr, I_("BRANCH"), branchCode.upperCase() );
      ADDCONDITIONFROMFILEIDI( CND::ERR_AGENT_NOT_FOUND_FOR_BROKER_BRANCH, idiStr.c_str() ); 
   }
   //checks for the validity of the agent code. by making a view call, and raising a condition
   //we do not want to make the view call when the slslrep code is NULL, because the view will
   //return us all the agents for this broker and branch
   if( slsrepCode != NULL_STRING && 
       sevRtn <= WARNING )
   {
      BFObjIter bfIter( agentList, idDataGroup );
      int iNumItems = bfIter.getNumberOfItemsInList ();
      bNewAgent = iNumItems > 0  ? false : true;
      DString slsrepName;
      DString slsrepAltName;

      bfIter.begin();
      if( !bfIter.end() )
      {
         DString branchName, agentName;
         pAgent = dynamic_cast <Agent*> ( bfIter.getObject() );
         pAgent->getField( ifds::SlsrepName, agentName, idDataGroup );
         pAgent->getField( ifds::SlsrepAltName, _agentAltName, idDataGroup );
         pAgent->getField( ifds::BranchCode, _branchCode, idDataGroup );
         pAgent->getField( ifds::BranchName, branchName, idDataGroup );
		 pAgent->getField( ifds::SlsrepType, _agentType, idDataGroup );

         parseName (branchName, _branchName);
         parseName (agentName, _agentName);

         DString dstrCurrBusDate;
         getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false ); 
         if ( pAgent->checkEffective ( dstrCurrBusDate, idDataGroup ) <= WARNING )
         {
            DString dstrValidationPassed;
            pAgent->getField ( ifds::ValidationPassed, dstrValidationPassed, idDataGroup );
            if ( dstrValidationPassed == NO ) 
            {
               ADDCONDITIONFROMFILE (CND::ERR_AGENT_NOT_ELIGIBLE_FOR_ACCT);
            }
         }
      }
   }
   else
   {
      _agentName = NULL_STRING;
      _agentAltName = NULL_STRING;
	  _agentType = NULL_STRING;
      if ( !slsRepByBranch (idDataGroup) ) {
         DString dstrBrokerBranch;
         if( getWorkSession().getOption( ifds::BrokerBranch, dstrBrokerBranch, idDataGroup, false ) <= WARNING ) {
            getField( ifds::BrokerCode, brokerCode, idDataGroup );
            if( dstrBrokerBranch == YES )
            {
               _branchCode = brokerCode;
            }
            else if( dstrBrokerBranch == NO )
            {
               _branchCode = I_( "0000" );
            }
         }
      }
      _branchName = NULL_STRING;

/*      if( !slsRepByBranch ( idDataGroup) )
      {
         _branchCode = NULL_STRING;
         _branchName = NULL_STRING;
      }*/
      bNewAgent = true;
   }

   setFieldNoValidate( ifds::SlsrepName, _agentName, idDataGroup, true, true, true, false);
   setFieldNoValidate( ifds::SlsrepAltName, _agentAltName, idDataGroup, true, true, true, false);
   setFieldNoValidate( ifds::SlsrepType, _agentType, idDataGroup, true, true, true, false);
   if ( !slsRepByBranch (idDataGroup) ) {
      setFieldNoValidate( ifds::BranchCode, _branchCode, idDataGroup, false, false, true );
   }
   setFieldNoValidate( ifds::BranchName, _branchName, idDataGroup, true, true, true, false);
   if( condition_returned == true ) {
      if ( isNew() && _dstrHouseBroker == YES && !bNewAgent )
         pAgent->canCreateAccount ( idDataGroup, true );
      return(GETCURRENTHIGHESTSEVERITY());
   } else
      return(NO_CONDITION);
}

//******************************************************************************
SEVERITY MFAccount::checkTheAccountNumber( const DString& accountNum, 
                                           const BFDataGroupId& idDataGroup, bool &found )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkTheAccountNumber" ) );

   AccShrNumCheck acctShrNumCheck( *this );
   DString strFound, tempAcctNum( accountNum );

   if( accountNum != NULL_STRING && accountNum[ 0 ] == '0' )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_NUMBER_CANNOT_START_WITH_ZERO );
   }
   else
   {
      found = false;
      //we should do that here since setting the account num to NULL_STRING if the
      //AcctNumCtrl is either M or m, will format the AcctNum to 0;
      tempAcctNum.stripLeading( '0' ).strip();
      //checks for the validity of the account number, by making a view call.
      if( tempAcctNum != NULL_STRING )
      {
         if( acctShrNumCheck.initCheck( NULL_STRING, tempAcctNum ) <= WARNING )
         {
            acctShrNumCheck.getField( ifds::DataFound, strFound, idDataGroup );
            found = strFound == YES;
         }
      }
      else //null string
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_NUM_CANNOT_BE_LEFT_EMPTY );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//return true if there is no balance in the account
bool MFAccount::ZeroBalance( const BFDataGroupId& idDataGroup ) 
{
   DString strBalance;
   double dec_acctbalance = 0;
   bool zeroBalance = true;

   getField( ifds::AccountBalance, strBalance, idDataGroup );
   dec_acctbalance = DSTCommonFunctions::convertToDouble( strBalance );
   if( dec_acctbalance > 0 )
   {
      zeroBalance = false;
   }
   else
   {
      MFAccountHoldingList *pMFAccountHoldingList = NULL;
      double dec_settledunits = 0;
      double dec_unsettledunits = 0;

      if( getAccountHoldingList( pMFAccountHoldingList, idDataGroup ) <= WARNING )
      {
         BFObjIter iterfundlist( *pMFAccountHoldingList, BF::HOST );

         while( !iterfundlist.end() )  // check if at least one fund has non zero balance
         {
            // in either settled units or unsettled units
            DString strSettledUnits, strUnsettledUnits;

            iterfundlist.getObject()->getField( ifds::SettledUnits, strSettledUnits, idDataGroup );
            dec_settledunits = DSTCommonFunctions::convertToDouble( strSettledUnits );
            iterfundlist.getObject()->getField( ifds::UnsettledUnits, strUnsettledUnits, idDataGroup );
            dec_unsettledunits = DSTCommonFunctions::convertToDouble( strUnsettledUnits );
            if( dec_settledunits != 0 || dec_unsettledunits != 0 )
            {
               zeroBalance = false;
               break;
            }
            ++iterfundlist;
         }
      }
   }
   return(zeroBalance);
}

//******************************************************************************
SEVERITY MFAccount::initFieldsAndSubst( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initFieldsAndSubst" ) );

   bool bIsRES2Client = getWorkSession ().isRES2Client();

   DString strMarket = DSTCommonFunctions::getMarket();
   if (strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG)
   {
      DString dstrTaxType;
      getField( ifds::TaxType, dstrTaxType, idDataGroup );

      if( getWorkSession ().isLIFLike (dstrTaxType) || getWorkSession ().isLIRALike (dstrTaxType) ||
          dstrTaxType == LRIF_TAX_TYPE  || dstrTaxType == PRIF_TAX_TYPE)
      {
         setFieldReadOnly( ifds::PensionJuris, idDataGroup, false );
         setValidFlag( ifds::PensionJuris, idDataGroup, false );
      }
      else
         setFieldReadOnly( ifds::PensionJuris, idDataGroup, true );  

      DString groupCodeLevel = getGrpCodeLevel (idDataGroup);
      if( groupCodeLevel == ACCOUNT_GROUP_LEVEL )
         loadGroupSubstitutionList( idDataGroup );

      DString strSiblingOnlySet;
      strSiblingOnlySet =  I_("Y=Yes;N=No;");

      if ( bIsRES2Client )
      {
         strSiblingOnlySet += I_(" = ;");
      }

      setFieldAllSubstituteValues( ifds::SiblingOnly, idDataGroup, strSiblingOnlySet );

   }  // 
//   initAcctTypeSubst( idDataGroup );
   loadAcctTypeSubstitutionList( idDataGroup );

   loadTaxTypeSubstitutionList( idDataGroup );

   loadNetworkIDValues ( idDataGroup );

   initFieldsNotInInquiry( idDataGroup );
   checkForReadOnly( idDataGroup );

   DString dstrBrokerName, dstrNewBrokerName;
   getField( ifds::BrokerName, dstrBrokerName, idDataGroup );
   
   if (dstrBrokerName.find (I_CHAR('&')) != -1)
   {
      parseName (dstrBrokerName, dstrNewBrokerName);
      setFieldNoValidate( ifds::BrokerName, dstrNewBrokerName, idDataGroup, true, true );
   }

   DString dstrBranchName, dstrNewBranchName;
   getField( ifds::BranchName, dstrBranchName, idDataGroup );
   
   if (dstrBranchName.find (I_CHAR('&')) != -1)
   {
      parseName (dstrBranchName, dstrNewBranchName);
      setFieldNoValidate( ifds::BranchName, dstrNewBranchName, idDataGroup, true, true );
   }

   DString dstrSalesRepName, dstrNewSalesRepName;
   getField( ifds::SlsrepName, dstrSalesRepName, idDataGroup );

   if (dstrSalesRepName.find (I_CHAR('&')) != -1)
   {
      parseName (dstrSalesRepName, dstrNewSalesRepName);
      setFieldNoValidate( ifds::SlsrepName, dstrNewSalesRepName, idDataGroup, true, true );
   }
   //retain the effective date
   getField( ifds::EffectiveDate, _initEffectiveDate, idDataGroup );
   setIntermAccountReadOnly();

   // Setup the AMS Tupe field with our AMS Substitution set builder
   //////////////////////////setAMSTypeSubstitutionList(idDataGroup);

   if (!isNew())
   {
      DString dstrAcctType, 
              dstrAcctPurpose, 
              dstrTaxType;

      getField (ifds::AcctType, dstrAcctType, idDataGroup, false);
      if( dstrAcctType != CORPORATE_ACCT_TYPE )
      {
         setFieldReadOnly( ifds::BusinessNo, idDataGroup, true);
      }
      getField( ifds::AcctPurpose, dstrAcctPurpose, idDataGroup, false);
      if (dstrAcctPurpose == YOUTH_POTFOLIO)
      {
         setFieldReadOnly (ifds::InTrustFor, idDataGroup, true);
      }

      Shareholder* pShareholder = NULL;
      DString canada_province = CANADA_PROVINCE;
      DString dstrPensionJuris;

     if (getShareholder( pShareholder, idDataGroup ) <= WARNING &&
        pShareholder)
      {
         pShareholder->getField( ifds::TaxJurisCode, dstrPensionJuris, idDataGroup );
      }
      getField (ifds::TaxType, dstrTaxType, idDataGroup, false);
      //To make it easier to read, here didn't used the simplified logic.
      if( !(( dstrAcctType == INDIVIDUAL_ACCT_TYPE || dstrAcctType == JOINT_ACCT_TYPE ) && 
         getWorkSession().isNonRegLike( dstrTaxType ) ) && (canada_province.find (dstrPensionJuris) == DString::npos))
      {
         setFieldReadOnly (ifds::AcctPurpose, idDataGroup, true);
      }
      /*DString dstrBrokerCode;
      getField ( ifds::BrokerCode, dstrBrokerCode, idDataGroup );
      if ( dstrBrokerCode != NULL_STRING ) {
         BrokerList brokerList (*this);
         DString dstrAccountNum;
         getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );
         SEVERITY sevRtn = brokerList.init2 ( dstrBrokerCode, NULL_STRING, I_("L"), dstrAccountNum , I_("Acct") );      
         Broker* pBroker;
         brokerList.getBroker ( dstrBrokerCode, pBroker );
         _dstrHouseBroker = pBroker->isHouseBroker ( idDataGroup )?YES:NO;
      }*/
      initDefaultAddress01 (idDataGroup);
      setFieldNoValidate( ifds::ActiveOnly, I_("N"), idDataGroup, true, true );
      setRecipientType (idDataGroup, false);

      setFieldValid(ifds::InitialDate, idDataGroup, true);
      setFieldValid(ifds::NetTransAmtAsOfDate, idDataGroup, true);
   }

   // init field CESGEligible and Pre98Contrib
   DString dstrCESGEligible, dstrPre98Contrib;
   getField( ifds::CESGEligible, dstrCESGEligible, idDataGroup, false );
   getField( ifds::Pre98Contrib, dstrPre98Contrib, idDataGroup, false );
   dstrCESGEligible.strip().upperCase();
   dstrPre98Contrib.strip().upperCase();
   if (dstrCESGEligible == NULL_STRING)
   {
      setField( ifds::CESGEligible, NO, idDataGroup, false );
   }
   if (dstrPre98Contrib == NULL_STRING)
   {
      setField( ifds::Pre98Contrib, NO, idDataGroup, false );
   }

   if( getWorkSession().isFunctionActivated(UAF::PORTFOLIO_SETUP) )
   {
      DString strAcctGroup;
      ProdPortfolioInfoList* pProdPortfolioInfoList = NULL;

      //call view 418
      if( getProdPortfolioInfoList(pProdPortfolioInfoList,idDataGroup) <= WARNING && 
         pProdPortfolioInfoList )
      {
         DString strProdPortfolioUUID;
         getField(ifds::ProdPortfolioUUID, strProdPortfolioUUID,idDataGroup,false);

         DString strProdPortfolioSubtList;
         if( pProdPortfolioInfoList->getSubstitutionList(strProdPortfolioSubtList,idDataGroup) <= WARNING &&
            !strProdPortfolioSubtList.empty() )
         {
            BFProperties *pBFProperties = getFieldProperties( ifds::ProdPortfolioUUID, idDataGroup );

            setFieldAllSubstituteValues (ifds::ProdPortfolioUUID, idDataGroup, strProdPortfolioSubtList);
            pBFProperties->setSubstituteValues(NULL);
            setFieldValid( ifds::ProdPortfolioUUID, idDataGroup, false );
         }

         ProdPortfolioPlanInfoList* pProdPortfolioPlanInfoList = NULL;

         //call view 419
         if( getProdPortfolioPlanInfoList(pProdPortfolioPlanInfoList,strProdPortfolioUUID,idDataGroup)<= WARNING &&
            pProdPortfolioPlanInfoList != NULL )
         {
            DString strProdPortfolioPlanSubtList;
            if( pProdPortfolioPlanInfoList->getSubstitutionList(strProdPortfolioPlanSubtList,idDataGroup) <= WARNING &&
               !strProdPortfolioPlanSubtList.empty() )
            {
               BFProperties *pBFProperties = getFieldProperties( ifds::ProdPortfolioPlanUUID, idDataGroup );

               setFieldAllSubstituteValues (ifds::ProdPortfolioPlanUUID, idDataGroup, strProdPortfolioPlanSubtList);
               pBFProperties->setSubstituteValues(NULL);
               setFieldValid( ifds::ProdPortfolioPlanUUID, idDataGroup, false );
            }
         }
      }
   }

   initializeSubstitutionList (ifds::ShrOutputType,SHAREHOLDER_OUTPUT_TYPE,idDataGroup);
   initializeSubstitutionList (ifds::SocialCode, SOCIAL_CODE, idDataGroup);

   bool bReadOnly = !(getWorkSession().hasUpdatePermission( UAF::UNCLM_REMIT_DATE_UPDATE ));
   setFieldReadOnly( ifds::UnclmRemitDate, idDataGroup, bReadOnly );
   
   DString bDefaultValue = getMgmtFeePayOptOvdSetup(idDataGroup);
   if (bDefaultValue != I_(""))
   {
		setFieldNoValidate(ifds::MgmtFeePayOption, bDefaultValue, idDataGroup, false, true);
   }

   DString dstrPrintAcctConf;
   getWorkSession().getOption(ifds::PrintAcctConf, dstrPrintAcctConf, idDataGroup, false);

   if (isNew() && dstrPrintAcctConf.stripAll().upperCase() == YES)
   {
       setFieldNoValidate(ifds::NonFinConfirm, YES, idDataGroup, false, true);
   }
   addBlankToSubSet(ifds::AIFMDInvestorCategory, idDataGroup);
   
   if (isRDSPAccount(idDataGroup))
   {
	   setFieldSubstituteValues( ifds::AccountClosingReason, idDataGroup, ifds::AccountClosingReasonRDSP );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool MFAccount::isAMSRBOnly(const BFDataGroupId& idDataGroup)
{
   DString dstrClientAMSType;

   // Get AMS Type options
   getWorkSession().getOption( ifds::ClientAMSType, dstrClientAMSType, BF::HOST, false );    // RO,RB
   dstrClientAMSType.stripAll().upperCase();

   // True if the only option is "Rebalnancing Asset Mix"
   return( dstrClientAMSType == I_("RB") );
}

//******************************************************************************
bool MFAccount::isAMSAnOption(const BFDataGroupId& idDataGroup)
{
   if( isAMSRBOnly(idDataGroup) ) {
      GroupList *pGroupList;
      DString   dstrGroupCode;
      getField(ifds::AcctGroup, dstrGroupCode, idDataGroup);
      if(getGroupList(pGroupList) > WARNING) {
         return false;
      }
      DString dstrAMS;
      pGroupList->getField(dstrGroupCode, ifds::AMS, dstrAMS, idDataGroup, false);
      if (dstrAMS != YES) {
         return false;
      }
      return true;
   } else {
      return true;
   }
}

//******************************************************************************
SEVERITY MFAccount::validateAMSForStopPurchaseRedeem (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSForEscrow"));

   DString dstrStopPurchase, dstrStopRed;
   getField (ifds::StopPurchase, dstrStopPurchase, idDataGroup);
   getField (ifds::StopRed, dstrStopRed, idDataGroup);
   dstrStopPurchase.strip().upperCase();
   dstrStopRed.strip().upperCase();
   if (dstrStopPurchase == Y || dstrStopRed == Y) {
      getErrMsg( IFASTERR::AMS_SETUP_NOT_ALLOWED_IF_STOP_PURCH_REDEM, 
                 CND::ERR_AMS_SETUP_NOT_ALLOWED_IF_STOP_PURCH_REDEM,
                 CND::WARN_AMS_SETUP_NOT_ALLOWED_IF_STOP_PURCH_REDEM, 
                 idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::validateAMSforCertificates (const BFDataGroupId& idDataGroup, 
      DefFundAllocList *&pFundAllocList)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSforCertificates"));


   CertificateList *pCertificateList = NULL;
   getCertificateList( pCertificateList, idDataGroup, !isNew() );

   if( pCertificateList )
   {
      BFObjIter iterCertList( *pCertificateList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iterCertList.end() )
      {
         DString certFundCode, certStatus;
         iterCertList.getObject()->getField ( ifds::rxFundCode, certFundCode, idDataGroup, false );
         iterCertList.getObject()->getField ( ifds::StatusCode, certStatus, idDataGroup, false);
         //If the cert's status is not 'active', do not bother to check further
         if(certStatus != I_("A"))
         {
            ++iterCertList;
            continue;
         }
         BFObjIter iterFundAllocList( (const_cast<DefFundAllocList &>(*pFundAllocList)), 
            idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
         while( !iterFundAllocList.end() )
         {
            DString allocFundCode;
            iterFundAllocList.getObject()->getField ( ifds::FundCode, allocFundCode, idDataGroup, false );

            if(certFundCode.strip().upperCase() == allocFundCode.strip().upperCase())
            {
               DString idiStr;
               addIDITagValue( idiStr, I_("FUNDCODE"), certFundCode );
               getErrMsg( IFASTERR::AMS_ACTIVE_CERTS_EXIST, 
                  CND::ERR_AMS_ACTIVE_CERTS_EXIST,
                  CND::WARN_AMS_ACTIVE_CERTS_EXIST, 
                  idDataGroup,idiStr);		

               return GETCURRENTHIGHESTSEVERITY();
            } // if(certFundCode == allocFundCode)
            ++iterFundAllocList;
         } // while( !iterFundAllocList.end() )
         ++iterCertList;
      } // while( !iterCertList.end() )
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::doesFundHaveCertificateUnits ( const DString &fundCode, 
                                                   const DString &classCode, 
                                                   const BFDataGroupId& idDataGroup,
                                                   bool &bFoundCertificate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doesFundHaveCertificateUnits"));

   bFoundCertificate = false;
      
   if (!isNew())
   {
      MFAccountHoldingList *pMFAccountHoldingList = NULL;

	   DString dstrCurrentBusinessDate;
	   getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false );

      if ( getAccountHoldingsAsOfDate (dstrCurrentBusinessDate, pMFAccountHoldingList, idDataGroup, fundCode, classCode ) <= WARNING  &&
           pMFAccountHoldingList)
	   {
		   BFObjIter iterAcctHolding (*pMFAccountHoldingList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
    
		   while (!iterAcctHolding.end()) 
		   {
			   DString _fundCode, _classCode, activeCert;

			   iterAcctHolding.getObject()->getField (ifds::rxFundCode, _fundCode, idDataGroup);
			   iterAcctHolding.getObject()->getField (ifds::rxClassCode, _classCode, idDataGroup);
            
			   if (_fundCode.strip() == fundCode && _classCode.strip() == classCode) 
			   {
				   iterAcctHolding.getObject()->getField (ifds::ActiveCert, activeCert, idDataGroup);   				
				   bFoundCertificate = activeCert == I_("Y");

				   break;
			   }
			   ++iterAcctHolding;
		   }
	   }
   }
	return GETCURRENTHIGHESTSEVERITY ();
}

/******************************************************************************
SEVERITY MFAccount::validateAMSForEscrow (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSForEscrow"));

   DString dstrCertExists, 
      strEscrow;
   getField (ifds::Certificates, dstrCertExists, idDataGroup, false);
   getField (ifds::Escrow, strEscrow, idDataGroup, false);
   if (dstrCertExists.strip().upperCase() == Y || strEscrow.strip().upperCase() == Y ) 
   {
      getErrMsg( IFASTERR::ACCOUNT_ESCROW_FLAG_IS_ACTIVE, 
                 CND::ERR_ACCOUNT_ESCROW_FLAG_IS_ACTIVE,
                 CND::WARN_ACCOUNT_ESCROW_FLAG_IS_ACTIVE, 
                 idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

*///******************************************************************************
SEVERITY MFAccount::validateAMSForInstitutionalCode (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSForInstitutionalCode"));

   DString socialCode;
   getField (ifds::SocialCode, socialCode, idDataGroup);
   if (socialCode == I_("IS"))  //institutional
   {
      getErrMsg( IFASTERR::AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL, 
                 CND::ERR_AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL,
                 CND::WARN_AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL, 
                 idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getAMSAcctLvlList( const BFDataGroupId &idDataGroup,
                                       AMSAcctLvlList *&pAMSAcctLvlList,
                                       bool bCreate/*=true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAMSAcctLvlList" ) );

   DString dstrKey = I_( "AMSAcctLvlList" );
   pAMSAcctLvlList = dynamic_cast <AMSAcctLvlList*> (getObject (dstrKey, idDataGroup));

   if( !pAMSAcctLvlList && bCreate )
   {
      DString dstrAccountNum,
         dstrShrNum;
      getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );
      getField ( ifds::ShrNum, dstrShrNum, idDataGroup );

      pAMSAcctLvlList = new AMSAcctLvlList( *this );
      if( isNew() ) {
         pAMSAcctLvlList->initNew( dstrShrNum, dstrAccountNum );
      } else {
         pAMSAcctLvlList->init( dstrShrNum, dstrAccountNum );
      }

      if( pAMSAcctLvlList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pAMSAcctLvlList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
         }
         else
         {
            delete pAMSAcctLvlList;
            pAMSAcctLvlList = NULL;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::initFieldsNotInInquiry( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initFieldsNotInInquiry" ) );

   if( !isNew() )
   {
      DString strTemp;
      //getField( DBR::AccountNumManual, strTemp, idDataGroup );
      //if( strTemp == NULL_STRING )
      setFieldNoValidate( ifds::AccountNumManual, NO, idDataGroup, false );
      //getField( DBR::MarketMailChgSh, strTemp, idDataGroup );
      //if( strTemp == NULL_STRING )
      setFieldNoValidate( ifds::MarketMailChgSh, NO, idDataGroup, false );
      //getField( DBR::CreateRep, strTemp, idDataGroup );
      //if( strTemp == NULL_STRING )
      setFieldNoValidate( ifds::CreateRep, NO, idDataGroup, false );
   }
   setFieldNoValidate( ifds::SettledFieldsInitialized, NO, idDataGroup, false );
   setFieldNoValidate( ifds::SettledValue, NULL_STRING, idDataGroup, false );
   setFieldNoValidate( ifds::UnsettledValue, NULL_STRING, idDataGroup, false);
   setFieldNoValidate( ifds::ShouldAskForSWPStop, NO, idDataGroup, false);
   setFieldNoValidate( ifds::StopSWP, NO, idDataGroup, false);
   ///////////////////////////////////
   /*
   setFieldNoValidate( ifds::Rebalance, NO, idDataGroup, false);
   setFieldNoValidate( ifds::UpdatePACSWP, NO, idDataGroup, false);
   //This fixes a bug logged by the client where the extract for the logical fields was not set.
   setFieldNoValidate( ifds::Rebalance, NO, idDataGroup, false);
   setFieldReadOnly( ifds::Rebalance, idDataGroup, true );
   setFieldReadOnly( ifds::UpdatePACSWP, idDataGroup, true );
   */

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::checkForReadOnly( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkForReadOnly" ) );

   //deal with the TaxType
   DString taxTypeUpd, transFound, pendingTrade, taxType, allowedTaxTypeUpd; 
   bool taxTypeReadOnly;

   //the rule is:
   //cannot upadte the taxType if we are in maintenance mode,
   //and the config flag is set to N; or
   //if the config flag is set to Y and we have either pending trades or,
   //transaction found
   getField( ifds::TaxType, taxType, idDataGroup ); 
   getField( ifds::PendingTrade, pendingTrade, idDataGroup );
   getField( ifds::TransFound, transFound, idDataGroup );
   getWorkSession().getOption( ifds::TaxTypeUpd,taxTypeUpd, idDataGroup, false ) ;
   getWorkSession().getOption( ifds::AlwdTaxType,allowedTaxTypeUpd, idDataGroup, false ) ;

   //taxTypeReadOnly = (!isNew() && taxTypeUpd == NO /*&& ( pendingTrade == YES || transFound == YES )*/);

   if (isNew ())
   {
      taxTypeReadOnly = false;
   }
   else
   {
      if (taxTypeUpd == NO)
      {
         taxTypeReadOnly = true;
      }
      else // taxTypeUpd == YES
      {
         // if tax type update is allowed check if tax type BR or CR is found in GC, 
         // if found check if there are any transacitons on this account.
         if (DSTCommonFunctions::codeInList (taxType, allowedTaxTypeUpd))
         {
            taxTypeReadOnly = pendingTrade == YES || transFound == YES ? true : false;
         }
         else
         {
            // this is for other tax types:
            taxTypeReadOnly = false;
         }
      }
   }

   setFieldReadOnly( ifds::TaxType, idDataGroup, taxTypeReadOnly );
   //setFieldReadOnly( DBR::AcctType, idDataGroup, taxTypeReadOnly );
   //setFieldReadOnly( DBR::Unseizable, idDataGroup, taxTypeReadOnly );

   if( !slsRepByBranch (idDataGroup) )
   {
      setFieldReadOnly( ifds::BranchCode, idDataGroup, true );
      setFieldReadOnly( ifds::BranchName, idDataGroup, true );
   }

   DString accNumCtrl;
   DString validAcctNumCtrl( VALIDVALUESFORACCTNUMCTRL );

   //if it is not manual do not allow the account num to be changed
   if( getWorkSession().getOption( ifds::AcctNumCtrl, accNumCtrl, idDataGroup ) <= WARNING &&
       validAcctNumCtrl.find( accNumCtrl.c_str() ) == DString::npos )
   {
      if( accNumCtrl == I_("M") )
      {
         setFieldReadOnly( ifds::AccountNum, idDataGroup, false );
      }
   }

   // Rule: Check ModRecipType_83, if it is 'Y', then use the existing default value rule for
   //       RecipientType. Otherwise, RecipientType should be readonly and value will be changed
   //       (in doApplyRelatedChanges) when user change the combination of TaxType and AccountType.

   DString dstrModRecipType;
   if( getWorkSession().getOption( ifds::ModRecipType, dstrModRecipType, idDataGroup, false ) <= WARNING )
   {
      setFieldReadOnly( ifds::RecipientType, idDataGroup, !( dstrModRecipType == YES ) );
   }

   DString groupCodeLevel = getGrpCodeLevel (idDataGroup);
   {
      setFieldReadOnly( ifds::AcctGroup, idDataGroup, (groupCodeLevel == SHAREHOLDER_GROUP_LEVEL) );
   }

   /*
   //if field AMS from GroupList is yes, AMSCode is updatable
   GroupList* pGroupList;
   DString dstrAMS, dstrGroupCode;
   getField(ifds::AcctGroup, dstrGroupCode, idDataGroup);      

   if( getGroupList( pGroupList ) <= WARNING )
   {
      pGroupList->getField( dstrGroupCode, ifds::AMS, dstrAMS, idDataGroup, false );

      if( dstrAMS == YES )
         setFieldReadOnly( ifds::AMSCode, idDataGroup, false );
      else
         setFieldReadOnly( ifds::AMSCode, idDataGroup, true );
   }
   */

   //setFieldReadOnly( ifds::ClearingFirm, idDataGroup, false );
   // NSCC enhancement
   checkNSCCBroker( idDataGroup );
   checkNetworkControlind( idDataGroup );
   checkPWConsolType(idDataGroup);
   checkIDConsolType(idDataGroup);
   checkEDConsolType(idDataGroup);

   flipReadOnlyForTaxTypeSchedule( NULL_STRING, idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MFAccount::flipReadOnlyForTaxTypeSchedule( const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "flipReadOnlyForTaxTypeSchedule" ) );

   DString grandFatheredDate, strActivityExists, strEffectiveDate(dstrEffectiveDate);
   if( strEffectiveDate.strip().empty() )
   {
      getField( ifds::EffectiveDate, strEffectiveDate, idDataGroup, false );
   }

   strEffectiveDate.strip();
   getGrandfatheredDate( grandFatheredDate, idDataGroup, NULL_STRING, SCHEDULE01, NULL_STRING );	
   getField( ifds::AcctActivityExists, strActivityExists, BF::HOST, false );
   if( strActivityExists.strip().upperCase() == YES ||
      DSTCommonFunctions::CompareDates( grandFatheredDate, strEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER )
   {
      setFieldReadOnly( ifds::TaxTypeSchedule, idDataGroup, true );
   }
   else
   {
      setFieldReadOnly( ifds::TaxTypeSchedule, idDataGroup, false );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void MFAccount::checkNSCCBroker( const BFDataGroupId& idDataGroup )
{
   DString dstrNSCCCompliant, dstrBrokerCode;
   getField( ifds::BrokerCode, dstrBrokerCode, idDataGroup, false );

   if( getWorkSession().getOption( ifds::NSCCCompliant, dstrNSCCCompliant, idDataGroup, false ) <= WARNING )
   {
      if( dstrNSCCCompliant == YES && isBrokerNSCCCompliant( dstrBrokerCode, idDataGroup ) )
      {
         setFieldReadOnly( ifds::ClearingFirm, idDataGroup, false );
         setFieldRequired( ifds::ClearingFirm, idDataGroup, true );
         setFieldValid( ifds::ClearingFirm, idDataGroup, false );

         setFieldReadOnly( ifds::AgentForFirm, idDataGroup, false );
         setFieldValid( ifds::AgentForFirm, idDataGroup, false );

         setFieldReadOnly( ifds::TPA, idDataGroup, false );
         setFieldValid( ifds::TPA, idDataGroup, false );
      }
      else 
      {
         setFieldNoValidate( ifds::ClearingFirm, NULL_STRING, idDataGroup, false, true, true );
         setFieldReadOnly( ifds::ClearingFirm, idDataGroup, true );
         setFieldRequired( ifds::ClearingFirm, idDataGroup, false );
         setFieldValid( ifds::ClearingFirm, idDataGroup, true );

         setFieldNoValidate( ifds::AgentForFirm, NULL_STRING, idDataGroup, false, true, true );
         setFieldReadOnly( ifds::AgentForFirm, idDataGroup, true );
         setFieldValid( ifds::AgentForFirm, idDataGroup, true );

         setFieldNoValidate( ifds::TPA, NULL_STRING, idDataGroup, false, true, true );
         setFieldReadOnly( ifds::TPA, idDataGroup, true );
         setFieldValid( ifds::TPA, idDataGroup, true );

         setFieldNoValidate( ifds::ParticipantID, NULL_STRING, idDataGroup, false, true, true );
      }
   }

}
//******************************************************************************
void MFAccount::checkNetworkControlind( const BFDataGroupId& idDataGroup )
{
   DString dstrNSCCCompliant, dstrBrokerCode;
   getField( ifds::BrokerCode, dstrBrokerCode, idDataGroup, false );
   if( getWorkSession().getOption( ifds::NSCCCompliant, dstrNSCCCompliant, idDataGroup, false ) <= WARNING )
   {
      if( dstrNSCCCompliant == YES && isBrokerNSCCCompliant( dstrBrokerCode, idDataGroup ) )
      {
         setFieldReadOnly( ifds::Networkcontrolind, idDataGroup, false );
         setFieldRequired( ifds::Networkcontrolind, idDataGroup, true );
      }
      else 
      {
         setFieldNoValidate( ifds::Networkcontrolind, DEFNETWORKCONTROLIND, idDataGroup, false );
         setFieldReadOnly( ifds::Networkcontrolind, idDataGroup, true );
         setFieldRequired( ifds::Networkcontrolind, idDataGroup, false );
      }
   }
}
//******************************************************************************
//return true if it is the first trade of the fund/class for this account
bool MFAccount::pendingOfFundExist( const DString& fundCode, const DString& classCode, const BFDataGroupId& idDataGroup ) 
{
   bool pendingExists = false;
   DString positionKey;

   MFAccountHoldingList *pMFAccountHoldingList = NULL;
   PendingTradeList     *pPendingTradesList = NULL;

   if( getPendingTradesList( pPendingTradesList, idDataGroup, FULL_LIST ) <= WARNING )//get the whole list
   {
      pendingExists = pPendingTradesList->fundclassExist( fundCode, classCode, idDataGroup );
   }

   return(pendingExists);
}

//******************************************************************************
bool MFAccount::changeTaxType(const DString& taxType, const BFDataGroupId& idDataGroup ) 
{
   DString allowedTaxTypeUpd;
   DString pendingTrade;
   DString transFound;

   if (isNew () || !isFieldUpdated (ifds::TaxType, idDataGroup))
      return true;

   getWorkSession().getOption( ifds::AlwdTaxType,allowedTaxTypeUpd, idDataGroup, false ) ;

   getField( ifds::PendingTrade, pendingTrade, idDataGroup );
   getField( ifds::TransFound, transFound, idDataGroup );

   if (DSTCommonFunctions::codeInList (taxType, allowedTaxTypeUpd))
   {
      return pendingTrade == YES || transFound == YES ? false : true;
   }

   return true; 
}

//******************************************************************************
//return the fund/class holding of this account
double MFAccount::fundClassBalance( const DString &fundCode,
                                    const DString &classCode,
                                    bool &recordFound,
                                    const BFFieldId &idField,
                                    const BFDataGroupId &idDataGroup,
                                    const DString &asOfDate /*=NULL_STRING*/)
{
   double fundbalance = 0;
   DString positionKey, 
      reqValue;
   MFAccountHoldingList *pMFAccountHoldingList = NULL;
   
   recordFound = false;
   if ( getAccountHoldingsAsOfDate (asOfDate, pMFAccountHoldingList, idDataGroup, fundCode, classCode ) <= WARNING  &&
        pMFAccountHoldingList)
   {
      BFObjIter iterAcctHolding (*pMFAccountHoldingList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
 
      while (!iterAcctHolding.end()) 
      {
         DString _fundCode, 
            _classCode;

         iterAcctHolding.getObject()->getField (ifds::rxFundCode, _fundCode, idDataGroup);
         iterAcctHolding.getObject()->getField (ifds::rxClassCode, _classCode, idDataGroup);
         if (_fundCode.strip() == fundCode && _classCode.strip() == classCode) 
         {
            iterAcctHolding.getObject()->getField (idField, reqValue, idDataGroup);
            fundbalance = DSTCommonFunctions::convertToDouble (reqValue);
            recordFound = true;
            break;
         }
         ++iterAcctHolding;
      }
   } // if the fund holding is available
   return fundbalance;
}

//******************************************************************************
/*
SEVERITY MFAccount::fundClassTradeMinimum ( const DString&  strFundCode, const DString&  strClassCode, 
                                            const DString&  strTransType, const DString&  strAmountType, const DString&  strAmount,
                                            const DString&  strEffectiveDate, const DString&  strSettleCurrency, DString &strInitial,
                                            const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "fundClassTradeMinimum" ) );

   DString strAccountNum;
   getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
   TradeMinAmtCheck * pTradeMinAmtCheck = NULL;
   if( getTradeMinAmtCheck(strAccountNum, strFundCode, strClassCode, strTransType, strAmountType, 
                           strAmount, strEffectiveDate, strSettleCurrency, pTradeMinAmtCheck, idDataGroup) <= WARNING )
   {
      pTradeMinAmtCheck->addConditions();
      pTradeMinAmtCheck->getField(ifds::InitPurch, strInitial, idDataGroup, false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
} */

//******************************************************************************
SEVERITY MFAccount::groupContributMax ( const BFDataGroupId& idDataGroup, DString &strOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "groupContributMax" ) );
   SEVERITY sevRtn = NO_CONDITION;

   GroupList*  pGroupList= NULL;
   sevRtn =  getGroupList( pGroupList );
   if( sevRtn <= WARNING )
   {
      DString dstrGroupCode, dstrContributionLimit;
      getField(ifds::AcctGroup, dstrGroupCode, idDataGroup);
      dstrGroupCode.strip().upperCase();
      pGroupList->getField( dstrGroupCode, ifds::ContributionLimit, dstrContributionLimit, idDataGroup );
      strOut = dstrContributionLimit.strip().stripLeading( '0' );
      if( strOut.find( I_(".")) != DString::npos )
         strOut.stripTrailing( '0' );
   }
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY MFAccount::groupLockedIn ( const BFDataGroupId& idDataGroup, DString &strOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "groupLockedIn" ) );
   SEVERITY sevRtn = NO_CONDITION;

   GroupList*  pGroupList= NULL;
   sevRtn =  getGroupList( pGroupList );
   if( sevRtn <= WARNING )
   {
      DString dstrGroupCode, dstrLockedInCode;
      getField(ifds::AcctGroup, dstrGroupCode, idDataGroup);
      dstrGroupCode.strip().upperCase();
      pGroupList->getField( dstrGroupCode, ifds::LockedInCode, dstrLockedInCode, idDataGroup );
      strOut = dstrLockedInCode;
   }

   return(GETCURRENTHIGHESTSEVERITY());

}
//******************************************************************************
SEVERITY MFAccount::canTradeFundClass ( const DString& fundCode,
                                        const DString& classCode, 
                                        const DString& transType,
                                        const DString& tradeDate,
                                        const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canTradeFundClass" ) );
   SEVERITY sevRtn = NO_CONDITION;

   if( transType == PURCHASE_CODE )
   {
      sevRtn = canContributeFundClass ( fundCode, classCode, transType, tradeDate, idDataGroup);
   }
   else if( transType == REDEMPTION_CODE )
   {
      sevRtn = canRedeemFundClass ( fundCode, classCode, tradeDate, idDataGroup );
   }
   else if( transType == EX_FER_IN_CODE )
   {
      sevRtn = canContributeFundClass ( fundCode, classCode, transType, tradeDate, idDataGroup);
   }
   else if( transType == EX_FER_OUT_CODE )
   {
      sevRtn = canExchOutFundClass ( fundCode, classCode, tradeDate, idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY MFAccount::canRedeemFundClass ( const DString &fundCode,
                                         const DString &classCode, 
                                         const DString &tradeDate,
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canRedeemFundClass" ) );
   SEVERITY sevRtn = NO_CONDITION;

   //sevRtn = fundClassInGroup ( fundCode, classCode, REDEMPTION_CODE, tradeDate, idDataGroup);

   sevRtn = fundClassInGroup ( fundCode, classCode, tradeDate, idDataGroup);

   /// If balance of the FromFund/Class is zero, give warning
   DString acctNum, idiStr, dstrWireSettleAcct;
   getField(ifds::AccountNum, acctNum, idDataGroup);
   acctNum.strip().stripLeading( '0' );

   getWorkSession().getOption( ifds::SpecAcctNum, dstrWireSettleAcct, idDataGroup );
   dstrWireSettleAcct.strip().stripLeading( '0' );

   sevRtn = fundClassInGroup ( fundCode, classCode, tradeDate, idDataGroup);

   if( sevRtn > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   bool recordFound (false);
   //if SettledFieldsInitialized is YES we don't want to call view 20 to get a value which we already know
   DString strSettledFieldsInitialized, strSettledValue, strUnsettledValue;
   getField(ifds::SettledFieldsInitialized, strSettledFieldsInitialized, idDataGroup, false);

   double dec_fundbalance = 0;
   if( strSettledFieldsInitialized.strip() == YES )
   {
      getField(ifds::SettledValue, strSettledValue, idDataGroup, false);
      getField(ifds::UnsettledValue, strUnsettledValue, idDataGroup, false);
      dec_fundbalance = DSTCommonFunctions::convertToDouble(strSettledValue) + DSTCommonFunctions::convertToDouble(strUnsettledValue);;
   }
   else
      dec_fundbalance = fundClassBalance (fundCode, classCode, recordFound, ifds::SettledValue, idDataGroup, tradeDate)+
                        fundClassBalance (fundCode, classCode, recordFound, ifds::UnsettledValue, idDataGroup, tradeDate); 
   //no escrow check for eFAN , until further instructions
   if( recordFound ) //check if fund and class has been locked-in
   {
      sevRtn = lockedInFundClass ( fundCode, classCode, tradeDate, idDataGroup );        
   }

   sevRtn = GETCURRENTHIGHESTSEVERITY();

   if( sevRtn <= WARNING && acctNum != dstrWireSettleAcct && dec_fundbalance <= 0 )
   {
      if (!negativeBalanceAllowed (idDataGroup, fundCode, classCode)) //isCategoryExist ( idDataGroup, TRADING_CLIENT ) )	
      {
         addIDITagValue( idiStr, I_("ACCTNUM"), acctNum);
         addIDITagValue( idiStr, I_("FUND"), fundCode);
         addIDITagValue( idiStr, I_("CLASS"), classCode);
         ADDCONDITIONFROMFILEIDI( CND::ERR_ACCT_BALANCE_ZERO, idiStr );
      }
   }

   bool bMarginAcct = isCategoryExist ( idDataGroup, MARGIN );
   if (bMarginAcct) 
   {
      ADDCONDITIONFROMFILE (CND::WARN_MARGIN_ACCT_LETTER_REQ);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::canExchOutFundClass ( const DString& fundCode,
                                          const DString& classCode, 
                                          const DString& tradeDate,
                                          const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canExchOutFundClass" ) );
   SEVERITY sevRtn = NO_CONDITION;

   //sevRtn = fundClassInGroup ( fundCode, classCode, EX_FER_OUT_CODE, tradeDate, idDataGroup);
   sevRtn = fundClassInGroup ( fundCode, classCode, tradeDate, idDataGroup);

   if( sevRtn > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   bool recordFound (false);
   //if SettledValue was set by eCom we don't want to call view 20 to get a value which we already know
   DString strSettledFieldsInitialized, strSettledValue,strUnsettledValue;
   getField(ifds::SettledFieldsInitialized, strSettledFieldsInitialized, idDataGroup, false);
   double dec_fundbalance = 0;
   if( strSettledFieldsInitialized.strip() == YES )
   {
      getField(ifds::SettledValue, strSettledValue, idDataGroup, false);
      getField(ifds::UnsettledValue, strUnsettledValue, idDataGroup, false);
      dec_fundbalance = DSTCommonFunctions::convertToDouble(strSettledValue) + DSTCommonFunctions::convertToDouble(strUnsettledValue);
   }
   else
      dec_fundbalance = fundClassBalance( fundCode, classCode, recordFound, ifds::SettledValue, idDataGroup, tradeDate )+
                        fundClassBalance( fundCode, classCode, recordFound, ifds::UnsettledValue, idDataGroup, tradeDate);

   //no escrow check for eFAN, until further instructions
   if (recordFound) //check if fund and class has been locked-in
   {
      sevRtn = lockedInFundClass (fundCode, classCode, tradeDate, idDataGroup);
   }
   sevRtn = GETCURRENTHIGHESTSEVERITY();
   // if not fail in lockInFundClass and fundClassInGroup, give warning if balance <= 0
   if( sevRtn <= WARNING && dec_fundbalance <= 0 )
   {
      if (!negativeBalanceAllowed(idDataGroup, fundCode, classCode) )
      {
         DString acctNum, idiStr;

         getField(ifds::AccountNum, acctNum, idDataGroup);
         acctNum.strip().stripLeading( '0' );

         addIDITagValue( idiStr, I_("ACCTNUM"), acctNum );
         addIDITagValue( idiStr, I_("FUND"), fundCode);
         addIDITagValue( idiStr, I_("CLASS"), classCode);
         ADDCONDITIONFROMFILEIDI( CND::ERR_ACCT_BALANCE_ZERO, idiStr );
      }
   }
   bool bMarginAcct = isCategoryExist ( idDataGroup, MARGIN );
   if ( bMarginAcct ) {
      ADDCONDITIONFROMFILE( CND::WARN_MARGIN_ACCT_LETTER_REQ );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::canContributeFundClass ( const DString& fundCode,
                                             const DString& classCode, 
                                             const DString& transType,
                                             const DString& tradeDate,
                                             const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canContributeFundClass" ) );
   SEVERITY sevRtn = NO_CONDITION;

   if ( isAMSAccount ( idDataGroup ) ) {
      DString dstrDefAllocOverride;
      getWorkSession().getOption( ifds::DefaultAllocOverride, dstrDefAllocOverride, idDataGroup, false); 
      if ( dstrDefAllocOverride == YES)  {
         bool bAMSMixOverride = getWorkSession().hasUpdatePermission( UAF::AMS_MIX_OVERRIDE );
         if ( bAMSMixOverride ) {
            DString dstrAMSCode = NULL_STRING;   
            getField ( ifds::AMSCode, dstrAMSCode, idDataGroup );           
            // AMS Code is defined, there we will assume it is an AMS Account.
            if ( dstrAMSCode != NULL_STRING ) {
               AMSMstrList* pAMSMstrList = NULL;
               getAMSMstrList( pAMSMstrList, idDataGroup, tradeDate );
               if( pAMSMstrList )  {
                  AmsMstrInfo *pAMSMstrInfo = NULL;
                  pAMSMstrList->getAMSMstrInfo ( I_("RB"), dstrAMSCode, tradeDate, pAMSMstrInfo, idDataGroup );
                  if ( pAMSMstrInfo ) {
                     if ( !pAMSMstrInfo->isFundInAMS ( fundCode, classCode, idDataGroup ) )
                        ADDCONDITIONFROMFILE( CND::AMS_ERR_CANNOT_PURCHASE_FUND_OUTSIDE_ALLOC );
                  }
               }
            } 
         } /*else {
            ADDCONDITIONFROMFILE( CND::AMS_ERR_USER_NO_PERMISSION_OVERRIDE_AMS_ALLOC );
         }*/
      }
      AMSFundAllow ( fundCode, classCode, idDataGroup );
   }

   //sevRtn = fundClassInGroup ( fundCode, classCode, transType, tradeDate, idDataGroup);
   sevRtn = fundClassInGroup ( fundCode, classCode, tradeDate, idDataGroup);

   // Check if the non-self-direct plan type of the account is eligible to trade the fund/class
   DString dstrSelfDirect (NULL_STRING);
   getField ( ifds::SelfDirected, dstrSelfDirect, idDataGroup);
   bool bMarginAcct = isCategoryExist ( idDataGroup, MARGIN );

   if( sevRtn <= WARNING && dstrSelfDirect == NO || bMarginAcct )
   {
      DString dstrPlanType (NULL_STRING);
      DString dstrCheckPlanType;      
      
      getField ( ifds::PlanType, dstrPlanType, idDataGroup);

      dstrCheckPlanType = I_( "RSP,LIRA,RIF,LRSP" );
      bool bcheckPlanType = DSTCommonFunctions::codeInList( dstrPlanType, dstrCheckPlanType) ;
         
      if( bcheckPlanType || bMarginAcct)
      {
         if( getFundDetailList() )
         {
				if( _pFundDetailList )
				{
            FundDetail *pFundDetail = NULL;
            _pFundDetailList->getFundDetail( fundCode, classCode, idDataGroup, pFundDetail );

            if( pFundDetail )
            {
               if ( bcheckPlanType )
                  pFundDetail->fundClassForPlanType( dstrPlanType, idDataGroup );

               // check if the fund is eligible for margin account
               if ( bMarginAcct )
               {
                  DString dstrMarginEligible;
                  pFundDetail->getField( ifds::MarginEligible, dstrMarginEligible, idDataGroup);
                  if ( dstrMarginEligible == NO)
                  {
                     ADDCONDITIONFROMFILE( CND::ERR_FUND_NOT_MARGIN_ELIGIBLE );
                  }
               }
            }
         }
      }
		}
   }

   //Protected Fund edit check : for buying protected fund, account owner must be less than 80 years old
   canContributeProtectedFund ( fundCode, classCode, idDataGroup);


   return(GETCURRENTHIGHESTSEVERITY());
}


//*********************************************************************************************
// check if fund and class are locked in for this account 

SEVERITY MFAccount::lockedInFundClass ( const DString& fundCode,
                                        const DString& classCode, 
                                        const DString& tradeDate,
                                        const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "lockedInFundClass" ) );
   SEVERITY sevRtn = NO_CONDITION;

   DString acctNum;
   getField(ifds::AccountNum, acctNum, idDataGroup);
   acctNum.strip().stripLeading( '0' );

   AccountEntityXref *pAccountEntityXref = NULL;

   if( getAccountEntityXref( pAccountEntityXref, idDataGroup ) <= WARNING )
   {
      DString strKey;

      if( acctNum != NULL_STRING )
         sevRtn = pAccountEntityXref->escrowAccountFundClass( acctNum, fundCode, classCode, tradeDate, idDataGroup);

   } // if found AccountEntityXref
   return(GETCURRENTHIGHESTSEVERITY());

}

//*********************************************************************************************
// check if the fund/class is available for group of the account
// if fund and class is available to the group, check if trade type and trade date is valid
SEVERITY MFAccount::fundClassInGroup( const DString& fundCode,
                                      const DString& classCode,
                                      const DString& tradeDate,
                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "fundClassInGroup" ) );

   DString dstrGroupCode, idiStr, strKey ;
   SEVERITY sevRtn = NO_CONDITION;

   if( fundCode == NULL_STRING || classCode == NULL_STRING )
   {
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   ///////////////////////////////////////////////////////////////////////////////////////// 
   //// Check if fund/class is available for the GROUP FUND LIST that the account belongs to

//   getWorkSession().getMgmtCo()->getGroupFundList( pGroupFundList );

   getField(ifds::AcctGroup, dstrGroupCode, idDataGroup);
   dstrGroupCode.strip().upperCase();
   GroupFundList *pGroupFundList = NULL;
   getGroupFundListFromGroup( dstrGroupCode, fundCode,idDataGroup, pGroupFundList );
   if( pGroupFundList )
   {
      BFData data;
      data.setElementValue( ifds::GroupCode, dstrGroupCode, true, NULL );
      data.setElementValue( ifds::FundCode, fundCode, true, NULL );
      data.setElementValue( ifds::ClassCode, classCode, true, NULL );

      pGroupFundList->getStrKey( strKey, &data );

      BFObjIter iterGroupFund(const_cast<GroupFundList &>(*pGroupFundList ), BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );

      addIDITagValue( idiStr, I_( "FUNDNAME"), fundCode );
      addIDITagValue( idiStr, CLASS, classCode );

      if( !iterGroupFund.positionByKey( strKey ) )
      {
         ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_AVAILABLE_TO_GROUP, idiStr );
      }
      else
      {
         GroupFund* groupFund = dynamic_cast<GroupFund*>( iterGroupFund.getObject() );

         if( groupFund != NULL )
            sevRtn = groupFund->validateFndClsTradeType( tradeDate, idDataGroup ) ;
      }
   }

   DString dstrProdPortfolioUUID;
   getField (ifds::ProdPortfolioUUID, dstrProdPortfolioUUID, idDataGroup, false);
   ProdPortfolioFundList *pProdPortfolioFundList = NULL;
   if( getFundListFromGroupAndPortfolio(pProdPortfolioFundList,
                                          dstrGroupCode,
                                          dstrProdPortfolioUUID, 
                                          idDataGroup) <= WARNING &&
      pProdPortfolioFundList )
   {
      idiStr = NULL_STRING;
      BFObjIter iterProdPortfolioFund(*pProdPortfolioFundList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

      addIDITagValue( idiStr, I_( "FUNDNAME"), fundCode );
      addIDITagValue( idiStr, CLASS, classCode );

      DString tmpFundCode = fundCode;
      DString tmpClassCode = classCode;

      tmpFundCode.strip().upperCase ();
      tmpClassCode.strip().upperCase ();

      iterProdPortfolioFund.begin();

      bool bFoundInPortfolioList = false;
      while(!iterProdPortfolioFund.end())
      {
         DString strFundCode, strClassCode;
         iterProdPortfolioFund.getObject()->getField(ifds::FundCode, strFundCode, idDataGroup, false);
         iterProdPortfolioFund.getObject()->getField(ifds::ClassCode, strClassCode, idDataGroup, false);
         strFundCode.strip().upperCase ();
         strClassCode.strip().upperCase ();

         if(strFundCode == tmpFundCode && strClassCode == tmpClassCode)
         {
            bFoundInPortfolioList = true;
            break;
         }

         ++iterProdPortfolioFund;
      }

      if(!bFoundInPortfolioList)
      {
         ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_AVAILABLE_TO_CURRENT_ACCT_PORTFOLIO, idiStr );
      }
   }

/*   if ( pGroupFundList )
	   delete pGroupFundList;*/

   return(GETCURRENTHIGHESTSEVERITY());

}

//********************************************************************************
SEVERITY MFAccount::getGroupFundListFromGroup( DString dstrGroupCode, DString dstrFundCode, const BFDataGroupId& idDataGroup, 
                                               GroupFundList *& pGroupFundList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getGroupFundList" ) );
   if( dstrGroupCode != NULL_STRING )
   {
      GroupList* pGroupList;
      if( getGroupList( pGroupList ) <= WARNING )
      {
         BFObjIter glIter( *pGroupList, idDataGroup );
         if( glIter.positionByKey( dstrGroupCode ) )
         {
            Group* pGroup;
            pGroup = dynamic_cast<Group*>( glIter.getObject() );
            if( pGroup )
            {
               pGroup->getGroupFundListByFund( pGroupFundList, dstrFundCode );           
            }
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY MFAccount::getFundListFromGroupAndPortfolio( ProdPortfolioFundList *&pProdPortfolioFundList,
                                                      const DString& dstrGroupCode,
                                                      const DString& dstrProdPortfolioUUID, 
                                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundListFromGroupAndPortfolio" ) );
   if (isPortfolioRequired (idDataGroup) &&
       dstrGroupCode != NULL_STRING && 
       dstrProdPortfolioUUID != NULL_STRING)
   {
      DString strKey = NULL_STRING;
      strKey  = I_("PortfolioFundList_PortfolioUUID=");
      strKey += dstrProdPortfolioUUID;
      strKey += I_(";");

      pProdPortfolioFundList = dynamic_cast <ProdPortfolioFundList*> (getObject (strKey, idDataGroup));

      if (!pProdPortfolioFundList)
      {
         pProdPortfolioFundList = new ProdPortfolioFundList (*this);
         
         if (pProdPortfolioFundList->init (dstrGroupCode, dstrProdPortfolioUUID) <= WARNING)
         {
            setObject (pProdPortfolioFundList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
         }
         else
         {
            delete pProdPortfolioFundList;
            pProdPortfolioFundList = NULL;         
         }
      }
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY MFAccount::getContractInfoList( ContractInfoList*& pContractInfoList, 
                                         const BFDataGroupId& idDataGroup,
                                         bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getContractInfoList" ) );

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pContractInfoList = dynamic_cast< ContractInfoList* >( BFCBO::getObject( I_( "ContractInfoList" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pContractInfoList )
   {
      DString dstrAcctNum;         
      getField( ifds::AccountNum, dstrAcctNum, idDataGroup );
      if( isNew() ) //checks if the account is new
      {
         pContractInfoList = new ContractInfoList( *this );
         pContractInfoList->init( idDataGroup, dstrAcctNum, false );
      }
      else if( inquireDatabase ) //make the view call
      {
         pContractInfoList = new ContractInfoList( *this );
         pContractInfoList->init( idDataGroup, dstrAcctNum );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pContractInfoList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pContractInfoList, I_( "ContractInfoList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup );
         }
         else
         {
            delete pContractInfoList;
            pContractInfoList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY MFAccount::getRegPlanTransferList( RegPlanTransferList*& pRegPlanTransferList, const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getContractInfoList" ) );

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pRegPlanTransferList = dynamic_cast< RegPlanTransferList* >( BFCBO::getObject( I_( "RegPlanTransferList" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pRegPlanTransferList )
   {
      DString dstrAcctNum;         
      getField( ifds::AccountNum, dstrAcctNum, idDataGroup );
      if( isNew() ) //checks if the account is new
      {
         pRegPlanTransferList = new RegPlanTransferList( *this );
         pRegPlanTransferList->init( idDataGroup, dstrAcctNum, false );
      }
      else if( inquireDatabase ) //make the view call
      {
         pRegPlanTransferList = new RegPlanTransferList( *this );
         pRegPlanTransferList->init( idDataGroup, dstrAcctNum );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pRegPlanTransferList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pRegPlanTransferList, I_( "RegPlanTransferList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup );
         }
         else
         {
            delete pRegPlanTransferList;
            pRegPlanTransferList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************
bool MFAccount:: isATAllowed( const BFDataGroupId& idDataGroup )
{
   DString strStopXferOut,strEscrow;
   getField( ifds::Escrow, strEscrow, idDataGroup, false );
   getField( ifds::StopXferOut, strStopXferOut, idDataGroup, false );
   strStopXferOut.strip();strEscrow.strip();
   if( strStopXferOut == I_("Y") ||  strEscrow == I_("Y") )
   {
      return(false);
   }

   return(true);
}
//******************************************************************************
SEVERITY MFAccount::loadIntermCodeSubstitutionList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadIntermCodeSubstitutionList" ) );

   DString dstSubstList = NULL_STRING;

   if( _pIntermediaryList ) // if pIntermediaryList is not null, sustitutionlist already loaded
   {
      _pIntermediaryList->getInterCodeList( dstSubstList, true);
      dstSubstList.upperCase();
      setFieldAllSubstituteValues( ifds::InterCode, idDataGroup, dstSubstList );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   if( getMgmtCo().getIntermediaryList( _pIntermediaryList) <= WARNING )
   {
      _pIntermediaryList->getInterCodeList( dstSubstList, true);
      dstSubstList.upperCase();
      setFieldAllSubstituteValues( ifds::InterCode, idDataGroup, dstSubstList );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************************************
SEVERITY MFAccount::loadGroupSubstitutionList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadGroupSubstitutionList" ) );

   GroupList*  pGroupList= NULL;
   DString dstSubstList = NULL_STRING;

   if( getGroupList( pGroupList )  <= WARNING )
   {
      pGroupList->getGroupSubstList( dstSubstList, true);
      dstSubstList.upperCase();
      setFieldAllSubstituteValues( ifds::AcctGroup, BF::HOST, dstSubstList );
      setFieldAllSubstituteValues( ifds::AcctGroup, idDataGroup, dstSubstList );

   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************************************
SEVERITY MFAccount::loadAcctTypeSubstitutionList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadAcctTypeSubstitutionList" ) );

   DString strAccountTypes;   
   bool bLoadedSubstList;

   TaxTypeRule *pTaxTypeRule = NULL;
   DString dstrTaxType;
   getField(ifds::TaxType,dstrTaxType,idDataGroup,false );
   dstrTaxType.strip();
   if( dstrTaxType == NULL_STRING )
   {
      setFieldAllSubstituteValues( ifds::AcctType, idDataGroup, BLANK_SUBSTITUTION ); 
      return(NO_CONDITION);
   }
   SEVERITY sevRtn = getTaxTypeRule ( pTaxTypeRule, idDataGroup );
   if( pTaxTypeRule != NULL && sevRtn <= WARNING )
   {
      pTaxTypeRule->getField( ifds::AccountTypes, strAccountTypes, idDataGroup );

      if( strAccountTypes.empty() )
      {

         //assert(0);  //codes list is empty
         bLoadedSubstList = false;
      }
      else
      {
         bLoadedSubstList = loadSubstitutionList( ifds::AcctType, idDataGroup, strAccountTypes );
      }

      if( bLoadedSubstList == false )
      {
         setFieldAllSubstituteValues( ifds::AcctType, idDataGroup, BLANK_SUBSTITUTION );
         //setFieldNoValidate( ifds::AcctType, NULL_STRING, idDataGroup, false );
         setField( ifds::AcctType, NULL_STRING, idDataGroup, false );
      }

   }//if( pTaxTypeRule != NULL ...

   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************************************
SEVERITY MFAccount::loadSettleCurrencySubstitutionList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadTaxTypeSubstitutionList" ) );

   DString strTaxTypes;
   
   TaxTypeRule* pTaxTypeRule = NULL;
   
   getTaxTypeRule ( pTaxTypeRule, idDataGroup);

   DString dstrAllCurrencies;
   BFProperties *pBFPropertiesHost = getFieldProperties( ifds::SettleCurrency, BF::HOST );
   pBFPropertiesHost->getAllSubstituteValues (dstrAllCurrencies);
   
   DString firstCurrency;

   setFieldAllSubstituteValues (ifds::SettleCurrency, idDataGroup, dstrAllCurrencies);

   if(pTaxTypeRule)
   {
      DString dstrSettleCurrencyAllowedValues;
      pTaxTypeRule->getField(ifds::TaxTypeRuleCurrSet, dstrSettleCurrencyAllowedValues, idDataGroup); 
      dstrSettleCurrencyAllowedValues.strip();

      if(dstrSettleCurrencyAllowedValues != I_("") && dstrSettleCurrencyAllowedValues != I_("*"))
      {
         dstrSettleCurrencyAllowedValues += I_(",");
         DString currSubstList;
         I_CHAR *temp = const_cast<I_CHAR*> (dstrAllCurrencies.c_str ());
         DString::size_type minPos = DString::npos;
         do 
         {
            DString currencyCode;
            DString currencyDescr;

            temp = parseIdiString (temp, currencyCode, currencyDescr);         
   //find if currency code is valid
//            if (isCodeInList (currencyCode, dstrSettleCurrencyAllowedValues))
            DString::size_type foundPos = dstrSettleCurrencyAllowedValues.find(currencyCode);
            if (foundPos != DString::npos)
            {
               if(minPos > foundPos && minPos != DString::npos || minPos == DString::npos)
               {
                  minPos = foundPos;
                  firstCurrency = currencyCode;
               }
               //if(firstCurrency == I_(""))
               //   firstCurrency = currencyCode;
               currSubstList += currencyCode + I_("=") + currencyDescr + I_(";");
            }
         } while (temp && temp != NULL_STRING && *temp);
         setFieldAllSubstituteValues (ifds::SettleCurrency, idDataGroup, currSubstList);
      }
      else
      {
         DString currencyCode;
         DString currencyDescr;
         I_CHAR *temp = const_cast<I_CHAR*> (dstrAllCurrencies.c_str ());
         
         temp = parseIdiString (temp, currencyCode, currencyDescr);   
         currencyCode.stripAll();
         if(dstrSettleCurrencyAllowedValues == I_("*") && currencyCode != I_(""))
         {
            currencyCode = I_(" ");
            dstrAllCurrencies = I_("= ;") + dstrAllCurrencies;
            setFieldAllSubstituteValues (ifds::SettleCurrency, idDataGroup, dstrAllCurrencies);
         }

         firstCurrency = currencyCode;
      }
   }

   if(isNew() && firstCurrency != I_(""))
   {
      DString settleCurrency;
      getField(ifds::SettleCurrency, settleCurrency, idDataGroup); 
      settleCurrency.strip();

      if(settleCurrency == I_(""))
      {
         setFieldNoValidate(ifds::SettleCurrency, firstCurrency, idDataGroup, false, false, false); 
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//**********************************************************************************
SEVERITY MFAccount::loadTaxTypeSubstitutionList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadTaxTypeSubstitutionList" ) );

   DString strTaxTypes;
   bool bLoadedSubstList;


   TaxTypeRuleList *ptaxTypeRuleList=NULL;

   SEVERITY sevRtn = getMgmtCo().getTaxTypeRuleList( ptaxTypeRuleList );

   if( ptaxTypeRuleList != NULL && sevRtn <= WARNING )
   {
      ptaxTypeRuleList->createTaxTypesList(strTaxTypes);

      if( strTaxTypes.empty() )
      {
         assert(0);  //codes list is empty
         bLoadedSubstList = false;
      }
      else
      {
         bLoadedSubstList = loadSubstitutionList( ifds::TaxType,
                                                  idDataGroup, 
                                                  strTaxTypes );
      }

      if( bLoadedSubstList == false )
      {
         setFieldAllSubstituteValues( ifds::TaxType, idDataGroup, BLANK_SUBSTITUTION );
         DString strTaxType;
         getField( ifds::TaxType, strTaxType, idDataGroup, false );
         if( !strTaxType.strip().empty() )
         {
            setFieldNoValidate( ifds::TaxType, NULL_STRING, idDataGroup, false );
         }
      }

   }// if( ptaxTypeRuleList != NULL 

   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************
SEVERITY MFAccount::validateLifLiraLRif ( const DString& taxType,
                                          Shareholder *&pShareholder,
                                          const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRifLifLRif" ) );

   //get pensionJuris, fedJurAllowed
   DString pensionJuris,lockedIn, FedJurisAllowed, taxTypeRules;

   getField( ifds::PensionJuris, pensionJuris, idDataGroup );
   getField( ifds::LockedIn, lockedIn, idDataGroup );
   getField( ifds::FedJurisAllowed, FedJurisAllowed, idDataGroup );
   getField( ifds::TaxTypeRules, taxTypeRules, idDataGroup );

   pensionJuris.strip().upperCase();
   lockedIn.strip().upperCase();
   FedJurisAllowed.strip().upperCase();
   taxTypeRules.strip().upperCase();

   if( FEDERAL_COUNTRY_CODE == pensionJuris && YES == lockedIn && NO == FedJurisAllowed )
   {
      ADDCONDITIONFROMFILE( CND::ERR_FEDERAL_JURISDICTION);
   }

   //Rule: b) For TaxType-76 = B, BR, C, CR, L and AcctDesignation-75 = '1' and PensionJuris-4 > '0000' 
   //   and LockedIn-4 = Yes, (TaxTypeRules-4 must be Yes) -- this condition changed to check
	// TaxJurisdictionaLimitationListExist or not. If it exists, we should allow user update 
	// Jurisdiction. Otherwise, Issue error: 
   //   "No Tax Type rules for this combination of Pension Jurisdiction and Tax Type"  

   if( pensionJuris > UNASSIGNED_COUNTRY_CODE && YES == lockedIn &&
		 !doesTaxJurisdictionLimitationListExist( idDataGroup ) ) //&& NO == taxTypeRules )
   {
      ADDCONDITIONFROMFILE( CND::ERR_NO_TAX_TYPE_RULES);
   }

   //Rule: c) For TaxType-76 = B, BR, C, CR, L and AcctDesignation-75 = '1' and 
   //   LockedIn-4 = Yes, DofB-11 should be <> ?. If it is unknown, issue 
   //   warning: "No Date of Birth was entered"

   if( pShareholder->isNew() ) // if new shareholder and new account, no Date of Birth is available yet
      return(GETCURRENTHIGHESTSEVERITY());

   //Rule: d) For TaxType-76 = B, BR, C, CR, L and AcctDesignation-75 = '1 either 
   //   TaxTypeRules-4 or DefTaxTypeRule-4 must be Yes; Error (severe) 
   //   = "No pension information available"

   DString defTaxTypeRules;
   getField( ifds::DefTaxTypeRules, defTaxTypeRules, idDataGroup );
   defTaxTypeRules.strip().upperCase();

   if( taxTypeRules == YES || defTaxTypeRules == YES )
   {
      //get defTaxTypeRules

      if( taxTypeRules == YES && defTaxTypeRules == YES )
      {
         ADDCONDITIONFROMFILE( CND::ERR_NO_PENSION_INFORMATION);
      }

      //Rule: e) For TaxType-76 = B, BR, C, CR, L and AcctDesignation-75 = '1'  and ( TaxTypeRules-4 = Yes or 
      //   TaxTypeRulesDefault-4 = Yes), age  must be within MinAge-4 and MaxAge-4. If the age is 
      //   beyond allowable age range, issue error message. Error (severe) 
      //   = "Client's age is beyond allowable age range to hold the locked in account"

	  AccountEntityXref *pAccountEntityXref = NULL;
      SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );
   
      if (pAccountEntityXref != NULL)
      {
          DString strAccountNum;
		  getField(ifds::AccountNum, strAccountNum, idDataGroup);

          pAccountEntityXref->validateDateOfBirth (strAccountNum, idDataGroup);
      }
   }


   return(GETCURRENTHIGHESTSEVERITY());

} // ValidateRifLifLRif 


//**********************************************************************************

SEVERITY MFAccount::validateRESP ( const DString& taxType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRESP" ) );

   //Rule: If RunMode = M and T550ReportMethod-83 = Yes,  TaxType-76 = "9" 
   //   and entered TaxType-76 = "M" then issue error message "Cannot change 
   //   tax type to/from RESP or RESFP".

   if( taxType != FAMILY_RESP_TAX_TYPE && taxType != INDIVIDUAL_RESP_TAX_TYPE )
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }

   //get taxTypeNew = taxType & taxTypeOld
   DString taxTypeOld;
   getField( ifds::TaxType, taxTypeOld, BF::HOST );

   DString t550ReportMethod;
   SEVERITY sevRtn = getWorkSession().getOption( ifds::T550ReportMethod, t550ReportMethod, idDataGroup, false );

   //Rule: If RunMode = M and T550ReportMethod = Yes,  TaxType-76 = "M"
   //   and entered TaxType-76 = "9" then issue error message "Cannot change 
   //   tax type to/from RESP or RESFP".

   if ( !getWorkSession ().isRES2Client() )
   {
      // QESI env will allow to change from 9 -> M
      if( !isNew() && t550ReportMethod == YES && 
          FAMILY_RESP_TAX_TYPE == taxTypeOld && INDIVIDUAL_RESP_TAX_TYPE == taxType )
      {
         ADDCONDITIONFROMFILE( CND::ERR_CANNOT_CHANGE_TAX_TYPE);
      }
   }
   else
   {
      if( !isNew() && t550ReportMethod == YES && 
         (INDIVIDUAL_RESP_TAX_TYPE == taxTypeOld && FAMILY_RESP_TAX_TYPE == taxType || FAMILY_RESP_TAX_TYPE == taxTypeOld && INDIVIDUAL_RESP_TAX_TYPE == taxType) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_CANNOT_CHANGE_TAX_TYPE);
      }
   }

   //Rule: g) If TaxType-88  is  9 or M, TaxType-76 must be either 9 or M. otherwise,
   //  issue error message 'Account tax type does not match the group tax type'.
   //   To get TaxType-88, AcctGroup-4 have to match rxGroupCode-88

   DString acctGroup, rxGroupCode, GrouptaxType;

   getField( ifds::AcctGroup, acctGroup, idDataGroup );
   GroupList* pGroupList;

   if( getGroupList( pGroupList )  <= WARNING )
   {
      sevRtn = pGroupList->getField ( acctGroup, ifds::TaxType, GrouptaxType, idDataGroup, false);

      if( sevRtn <= WARNING && (GrouptaxType == FAMILY_RESP_TAX_TYPE || GrouptaxType == INDIVIDUAL_RESP_TAX_TYPE) 
          && taxType != GrouptaxType )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACC_TAX_TYPE_NOT_MATCH );
      }
   } // getGroupList

   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************************

SEVERITY MFAccount::getTaxTypeSchedule( DString &dstrTaxTypeSchedule, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTaxTypeSchedule" ) );

   getField( ifds::TaxTypeSchedule, dstrTaxTypeSchedule, idDataGroup );
   if( dstrTaxTypeSchedule.strip().empty() )
   {
      dstrTaxTypeSchedule = I_( "00" );;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************************
SEVERITY MFAccount::getTaxTypeRule ( TaxTypeRule *&pTaxTypeRule, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTaxTypeRule" ) );

   pTaxTypeRule = NULL;
   BFData data;
   DString dstrTaxType, strTaxTypeSchedule, dstrKey;

   getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
   getTaxTypeSchedule( strTaxTypeSchedule, idDataGroup );

   if( dstrTaxType.strip().upperCase().empty() )
      return(GETCURRENTHIGHESTSEVERITY());

   TaxTypeRuleList *ptaxTypeRuleList=NULL;
   if( getMgmtCo().getTaxTypeRuleList( ptaxTypeRuleList )<=WARNING && ptaxTypeRuleList )
   {
	  ptaxTypeRuleList->getStrKey( dstrKey, dstrTaxType, strTaxTypeSchedule );
      BFObjIter iterTaxType(const_cast<TaxTypeRuleList &>(*ptaxTypeRuleList ), BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
      if( iterTaxType.positionByKey( dstrKey ) )
         pTaxTypeRule = dynamic_cast<TaxTypeRule*>( iterTaxType.getObject() );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************************

SEVERITY MFAccount::isTaxTypeScheduleApplicable( bool &bApplicable, const DString& dstrTaxType, 
       const DString& dstrPensionJuris, const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isTaxTypeScheduleApplicable" ) );

   bApplicable = false;
   //business rules
   //Schedule field is applicable if for the taxType and pensionJurisdiction there is an entry with '01' in tax jurisdiction list
   //and for new accounts, only if effectiveDate of the account is before grandfathered date
   TaxTypeRuleList *ptaxTypeRuleList=NULL;
   if( getMgmtCo().getTaxTypeRuleList( ptaxTypeRuleList )<=WARNING && ptaxTypeRuleList )
   {
      DString strPensionJuris( dstrPensionJuris );
	  if( strPensionJuris.strip().empty() )
	  {
         getField( ifds::PensionJuris, strPensionJuris, idDataGroup, false );
	  }
      if( !strPensionJuris.strip().empty() )
	  {
         DString strTaxType(dstrTaxType);
		 if( strTaxType.strip().empty() )
	     {
            getField( ifds::TaxType, strTaxType, idDataGroup, false );	  
         }
         //create iterator on ptaxTypeRuleList and try to position on TaxType and TaxTypeSchedule = 01			
         BFObjIter iterList( *ptaxTypeRuleList, BF::HOST, false );
         DString strKey;
		 ptaxTypeRuleList->getStrKey( strKey, strTaxType, SCHEDULE01 );
         if( iterList.positionByKey( strKey ) )
		 {
            TaxTypeRule *pTaxTypeRule = dynamic_cast<TaxTypeRule*>(iterList.getObject());
			bool bApplicableForTaxType = false;
            pTaxTypeRule->isTaxTypeSchedule01Exist( bApplicableForTaxType, strPensionJuris, idDataGroup);
            if( bApplicableForTaxType )
			{
				//check grandfathered date; if before effectiveDate, this field is not applicable for new accounts
				DString grandFatheredDate, strEffectiveDate(dstrEffectiveDate);
				if( strEffectiveDate.strip().empty() )
				{
				   getField( ifds::EffectiveDate, strEffectiveDate, idDataGroup, false );
				}
				strEffectiveDate.strip();
				getGrandfatheredDate( grandFatheredDate, idDataGroup, strTaxType, SCHEDULE01, strPensionJuris );
				if( DSTCommonFunctions::CompareDates( grandFatheredDate, strEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER )
				{
				   //after grandfatheredDate TaxTypeSchedule is not applicable for new accounts
				   bApplicable = !isNew();
				}
				else
				{
				   bApplicable = true;
				}
			}
        }
     } 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************************

SEVERITY MFAccount::getGrandfatheredDate( DString& dstrGrandFatheredDate, const BFDataGroupId& idDataGroup, 
	   const DString& dstrTaxType, const DString& dstrTaxTypeSchedule, const DString& dstrPensionJuris, bool blFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getGrandfatheredDateForPensJuris" ) );

   dstrGrandFatheredDate = I_("12319999");
   DString dstrKey, strTaxType(dstrTaxType), strTaxTypeSchedule(dstrTaxTypeSchedule), strPensionJuris(dstrPensionJuris);

   if( strTaxTypeSchedule.strip().empty() )
   {
      getTaxTypeSchedule( strTaxTypeSchedule, idDataGroup );
   }
   strTaxTypeSchedule.strip();
   if( strTaxType.strip().empty() )
   {
      getField( ifds::TaxType, strTaxType, idDataGroup, false );   
   }
   

   if( strTaxType.strip().upperCase().empty() )
      return(GETCURRENTHIGHESTSEVERITY());

   TaxTypeRuleList *ptaxTypeRuleList=NULL;
   TaxTypeRule *pTaxTypeRule = NULL;
   if( getMgmtCo().getTaxTypeRuleList( ptaxTypeRuleList )<=WARNING && ptaxTypeRuleList )
   {
	  ptaxTypeRuleList->getStrKey( dstrKey, strTaxType, strTaxTypeSchedule );
      BFObjIter iterTaxType(const_cast<TaxTypeRuleList &>(*ptaxTypeRuleList ), BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
      if( iterTaxType.positionByKey( dstrKey ) )
	  {
         pTaxTypeRule = dynamic_cast<TaxTypeRule*>( iterTaxType.getObject() );
         if( strPensionJuris.strip().empty() )
		 {
	        getField( ifds::PensionJuris, strPensionJuris, idDataGroup );
         }
         dstrGrandFatheredDate = pTaxTypeRule->getJurisLimitField( ifds::GrandFatheredDate, strPensionJuris.strip(), idDataGroup, blFormatted );
	     if( dstrGrandFatheredDate.strip().empty() )
	     {
            dstrGrandFatheredDate = I_("12319999");
	     }
	  }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************************
void MFAccount::setRecipientType ( const BFDataGroupId& idDataGroup,
                                   bool assign /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setRecipientType" ) );

   //get taxType
   DString taxType, 
      acctDesignation, 
      acctType, 
      recipientType, 
      taxJurisCode,
      shrNum,
      lockedIn;

   getField (ifds::TaxType, taxType, idDataGroup);
   getField (ifds::AcctType, acctType, idDataGroup);
   getField (ifds::AcctDesignation, acctDesignation, idDataGroup);
   getField (ifds::LockedIn, lockedIn, idDataGroup);
   getField (ifds::ShrNum, shrNum, idDataGroup);

   acctType.upperCase();
   acctDesignation.upperCase();
   Shareholder *pShareholder (NULL);
   
   if (getWorkSession().getShareholder (idDataGroup, shrNum, pShareholder) <= WARNING &&
       pShareholder)
   {
      pShareholder->getField (ifds::TaxJurisCode, taxJurisCode, idDataGroup);
   }

   if (!taxType.empty() && !acctType.empty())
   {

      // Rule: Check ModRecipType_83, if it is 'Y', then use the existing default value rule for
      //       RecipientType. Otherwise, RecipientType should be readonly and value will be changed
      //       (in doApplyRelatedChanges) when user change the combination of TaxType and AccountType.

      bool bRecipientExit = false;
      DString modRecipType;

      if (getWorkSession().getOption (ifds::ModRecipType, modRecipType, idDataGroup, false) <= WARNING)
      {
         if (modRecipType == N)
         {
            RecipientTypeList *pRecipientTypeList (NULL);

            SEVERITY sevRtn = getMgmtCo().getRecipientTypeList (pRecipientTypeList);
            if (pRecipientTypeList)
            {
               if (pRecipientTypeList->getRecipientType (taxType, acctType, taxJurisCode, recipientType, idDataGroup) <= WARNING)
               {
                  bool bReadOnly = true;
                  DString substList (_recipientTypeSubstList);
                  
                  if (!recipientType.empty())
                  {
                     if (assign)
                     {
                        setFieldNoValidate (ifds::RecipientType, recipientType, idDataGroup, false, true, true);                     
                     }

                     bReadOnly = taxType != I_("0") || (acctType != I_("2") && 
                                                        acctType != I_("3") && 
                                                        acctType != I_("8"));
                     if (!bReadOnly)
                     {
                        //to get the default recipient type susbstitution set....
                        DString validRecipentCodeList (NULL_STRING);
                           
                        if (acctType == I_("2")) //filter the recipient code list to 2 and 7, 
                        {
                           validRecipentCodeList = I_("2,7");
                        }
                        else if (acctType == I_("3") || 
                                 acctType == I_("8")) // filter the recipient code list to 4 and 6
                                                      // however, after FundServ 20 enh, code '6'
                                                      // was removed from selectable list.
                        {
                           //validRecipentCodeList = I_("4,6");
                           validRecipentCodeList = I_("4");
                        }
                        if (!validRecipentCodeList.empty())
                        {
                           substList = NULL_STRING; //reset the subst list...
                           I_CHAR *temp = const_cast<I_CHAR*> (_recipientTypeSubstList.c_str ());

                           do
                           {
                              DString recipientCode,
                                 recipientDescr;

                              temp = parseIdiString (temp, recipientCode, recipientDescr);
                              //find if recipient code is valid
                              if (isCodeInList (recipientCode, validRecipentCodeList))
                              {
                                 substList += recipientCode + I_("=") + recipientDescr + I_(";");
                              }
                           } while (temp && temp != NULL_STRING && *temp);
                           if (substList.empty())
                           {
                              substList = _recipientTypeSubstList;
                           }
                        }
                     }
                  }
                  setFieldReadOnly (ifds::RecipientType, idDataGroup, bReadOnly);
                  //set the substitution set on to the field
                  setFieldAllSubstituteValues (ifds::RecipientType, idDataGroup, substList);
                  //have to force validation, because substitute values have changed
                  setFieldValid (ifds::RecipientType, idDataGroup, false);
               }
            }
         }
         if (modRecipType == YES || (modRecipType == N && recipientType.empty()))
         {
            if( getWorkSession ().isLIRALike (taxType) || LRIF_TAX_TYPE == taxType || 
                getWorkSession ().isLIFLike (taxType) || PRIF_TAX_TYPE == taxType || 
                lockedIn == YES )
            {
			   if(assign == true)
				  setFieldNoValidate (ifds::RecipientType, INDIVIDUAL_RECIPIENT_TYPE, idDataGroup, false, true, true);
				  
               setFieldReadOnly (ifds::RecipientType, idDataGroup, true);
            }
            else  // other tax type
            {
               if (recipientType.empty() && assign == true)   // assign the default value only if the value is null
               {                                              // and it is requested to. 
                  if( !getWorkSession().isNonRegLike (taxType))
                  {
                     setFieldNoValidate (ifds::RecipientType, N_A_RECIPIENT_TYPE, idDataGroup, false, true, true);
                  }
                  else if( CLIENT_ACCT_DESIGNATION != acctDesignation )
                  {
                     setFieldNoValidate (ifds::RecipientType, TRUST_RECIPIENT_TYPE, idDataGroup, false, true, true);
                  }
                  else if (JOINT_ACCT_TYPE == acctType)
                  {
                     setFieldNoValidate (ifds::RecipientType, JOINT_RECIPIENT_TYPE, idDataGroup, false, true, true);
                  }
                  else if (CORPORATE_ACCT_TYPE == acctType)
                  {
                     setFieldNoValidate (ifds::RecipientType, CORPORATION_RECIPIENT_TYPE, idDataGroup, false, true, true);
                  }
                  else
                  {
                     setFieldNoValidate (ifds::RecipientType, INDIVIDUAL_RECIPIENT_TYPE, idDataGroup, false, true, true);
                  }
               }
               setFieldReadOnly (ifds::RecipientType, idDataGroup, modRecipType == NO);
            }
         }
      }
   }
}

//******************************************************************************
DString MFAccount::getGrpCodeLevel ( const BFDataGroupId& idDataGroup )
{
   if( _grpCodeLevel == NULL_STRING )
   {
      SEVERITY sevRtn = getWorkSession().getOption( ifds::GrpCodeLevel, _grpCodeLevel, idDataGroup, false );
      if( sevRtn > WARNING )
      {
         _grpCodeLevel = SHAREHOLDER_GROUP_LEVEL;
      }
      _grpCodeLevel.strip().upperCase();
   }

   return(_grpCodeLevel);

}

//******************************************************************************
SEVERITY MFAccount::getGroupList ( GroupList *&pGroupList ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getGroupList" ) );

   getMgmtCo().getGroupList (pGroupList) ;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************       
SEVERITY MFAccount::getAccountEntityXref ( AccountEntityXref *&pAccountEntityXref, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountEntityXref" ) );


   if( _pAcctEntityXref == NULL )
   {
      SEVERITY sevRtn = getWorkSession().getAccountEntityXref( idDataGroup, _pAcctEntityXref ) ;
   }

   pAccountEntityXref = _pAcctEntityXref;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************       
SEVERITY MFAccount::getShareholder ( Shareholder *&pShareholder, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getShareholder" ) );

   if( _pShareholder == NULL )
   {
      DString shrNum;
      getField( ifds::ShrNum, shrNum, idDataGroup );

      SEVERITY sevRtn = getWorkSession().getShareholder( idDataGroup, shrNum, _pShareholder ) ;
   }

   pShareholder = _pShareholder;

   return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************************
void   MFAccount::setAccountDesignation(const BFDataGroupId& idDataGroup)
{ 
   DString acctDesignation;
   Shareholder* pShareholder;

   if( getShareholder( pShareholder, idDataGroup ) <= WARNING )
   {
      DString acctDesignation;
      
      pShareholder->getField (ifds::AcctDesignation, acctDesignation, idDataGroup, false);
      setFieldNoValidate (ifds::AcctDesignation, acctDesignation, idDataGroup, false, true);
      // force to do validation for Tax Type
      setFieldValid (ifds::TaxType, idDataGroup, false);
      if (acctDesignation == INTERMEDIARY_ACCT_DESIGNATION)
      {
         setFieldRequired (ifds::InterCode, idDataGroup, true);
         setFieldValid (ifds::InterCode, idDataGroup, false);
         setFieldRequired (ifds::InterAccount, idDataGroup, true);
         setFieldGroupFlags (ifds::InterCode, idDataGroup, ACCOUNT_GROUPING::ACCOUNT_INFO);
         setFieldGroupFlags (ifds::InterAccount, idDataGroup, ACCOUNT_GROUPING::ACCOUNT_INFO);
         loadIntermCodeSubstitutionList (idDataGroup);
         setFieldReadOnly (ifds::InterAccount, idDataGroup, false);
      }
      else
      {
         setFieldRequired (ifds::InterCode, idDataGroup, false);
         setFieldReadOnly (ifds::InterCode, idDataGroup, false);
         setFieldRequired (ifds::InterAccount, idDataGroup, false);
         setFieldReadOnly (ifds::InterAccount, idDataGroup, false);
         setFieldGroupFlags (ifds::InterCode,    idDataGroup, 0);
         setFieldGroupFlags (ifds::InterAccount, idDataGroup, 0);
         _pIntermediaryList = NULL;
         setFieldAllSubstituteValues (ifds::InterCode, idDataGroup, BLANK_SUBSTITUTION);
         setFieldNoValidate (ifds::InterAccount, NULL_STRING, idDataGroup, false);
         setFieldReadOnly (ifds::InterAccount, idDataGroup, true);
      }
   }
}

//******************************************************************************   
void MFAccount::setIntermAccountReadOnly()
{   
   DString acctDesignation;
   getField( ifds::AcctDesignation, acctDesignation, BF::HOST );
   if( acctDesignation == INTERMEDIARY_ACCT_DESIGNATION )
   {
      setFieldReadOnly( ifds::InterAccount, BF::HOST, false );  
   }
   else
   {
      setFieldReadOnly( ifds::InterAccount, BF::HOST, true );  
   }
}

//******************************************************************************   


bool MFAccount::slsRepByBranch ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "slsRepByBranc" ) );

   if( _salesRepByBranch == NULL_STRING )
   {
      getWorkSession().getOption( ifds::RepByBranch, _salesRepByBranch, idDataGroup, false );
   }

   return( _salesRepByBranch == YES );
}
//******************************************************************************   

SEVERITY MFAccount::getLIPRateExist(DString &strLIPRateExist, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getLIPRateExist" ) );

   if( _strLIPRateExist == NULL_STRING )
   {
      //view 144 call
      DString strAccountNum;
      getField(ifds::AccountNum, strAccountNum, idDataGroup);

      BFData requestData(ifds::DSTC0144_REQ);   

      BFData *responseData = new BFData(ifds::DSTC0144_VW);

      DString mgmtCoIdOut;
      requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      requestData.setElementValue( ifds::AccountNum, strAccountNum );

      ReceiveData(DSTC_REQUEST::LIP_RATE_EXIST, requestData, *responseData, DSTCRequestor( getSecurity(), true) );
      if( GETHIGHESTSEVERITY() <= WARNING )
         responseData->getElementValue( ifds::LIPRateExist, _strLIPRateExist );

   }

   strLIPRateExist = _strLIPRateExist;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getErrMsg( DString dstrErrNum, long lErrConditionId, 
                               long lWarnConditionId, const BFDataGroupId& idDataGroup, DString idiStr )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getErrMsg" ) );

   if( _pErrMsgRulesList == NULL )
   {
      SEVERITY sevRtn = getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }

   if( _pErrMsgRulesList )
      _pErrMsgRulesList->getEWI( dstrErrNum, lErrConditionId, lWarnConditionId, idDataGroup, idiStr );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::validateTaxType( const DString &taxType, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTaxType" ) );

   if (!changeTaxType (taxType, idDataGroup))
   {
      ADDCONDITIONFROMFILE( CND::ERR_CANNOT_CHANGE_TAXTYPE);
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   updateTaxTypeSchedule( taxType, NULL_STRING, NULL_STRING, NULL_STRING, idDataGroup );

   DString dstrAcctDesignation;

   TaxTypeRule *ptaxTypeRule = NULL;

   getField ( ifds::AcctDesignation, dstrAcctDesignation, idDataGroup, false );

   if( getTaxTypeRule ( ptaxTypeRule, idDataGroup) <= WARNING && ptaxTypeRule &&
       ptaxTypeRule->validAcctDesignation ( dstrAcctDesignation , idDataGroup) == false )
   {
//###    NEXT CONDITION MUST BE ADDED IN DATA DICTIONARY
      ADDCONDITIONFROMFILE( CND::ERR_TAX_TYPE_NOT_FOR_ACCT_DESIGNATION);
      return(GETCURRENTHIGHESTSEVERITY());
   }

   //Rule: a) For TaxType-76 = B, BR, C, CR, L and AcctDesignation-75 = '1'and PensionJuris-4 = '9999'
   //   and LockedIn-4 = Yes FedJurAllowed-4 must be Yes. If it is not, issue error 
   //   "Federal Jurisdiction is not permitted for this Tax Type"

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
   {
      //get acctDesignation
      Shareholder *pShareholder = NULL;
      SEVERITY sevRtn = NO_CONDITION;

      if( getShareholder( pShareholder, idDataGroup ) <= WARNING )
      {
         if( (getWorkSession ().isLIFLike (taxType) || getWorkSession ().isLIRALike (taxType) || LRIF_TAX_TYPE == taxType ||
              PRIF_TAX_TYPE == taxType)
             && CLIENT_ACCT_DESIGNATION == dstrAcctDesignation )
         {
            sevRtn = validateLifLiraLRif ( taxType, pShareholder, idDataGroup );
         }
      }

      if( taxType == FAMILY_RESP_TAX_TYPE || taxType == INDIVIDUAL_RESP_TAX_TYPE )
      {
         sevRtn = validateRESP ( taxType, idDataGroup );
      }

      // check if RRSP or RRIF plan offer by the province
      if( taxType == RRSP_TAX_TYPE || taxType == RRIF_TAX_TYPE )
      {
         Shareholder* pShareholder = NULL;
         DString dstrPensionJuris;
         if( getShareholder( pShareholder, idDataGroup ) <= WARNING )
         {
            if( pShareholder )
            {
               pShareholder->getField( ifds::TaxJurisCode, dstrPensionJuris, idDataGroup );
               TaxTypeRule *ptaxTypeRule = NULL;
               sevRtn = getTaxTypeRule ( ptaxTypeRule, idDataGroup);
               if( ptaxTypeRule && !ptaxTypeRule->isValidPensionJurisdiction( dstrPensionJuris, idDataGroup ) )
               {
                  DString idiStr, dstrTaxTypeDesc, dstrPensionJurisName;
                  if( taxType == RRSP_TAX_TYPE )
                     dstrTaxTypeDesc = I_("RRSP");
                  else
                     dstrTaxTypeDesc = I_("RRIF");
                  pShareholder->getField( ifds::TaxJurisCode, dstrPensionJurisName, idDataGroup, true );
                  addIDITagValue( idiStr, I_("TAXTYPE"), dstrTaxTypeDesc );
                  addIDITagValue( idiStr, I_("TAXJURIS"), dstrPensionJurisName );
                  ADDCONDITIONFROMFILEIDI( CND::ERR_WARN_WRONG_COMBINATION_TAXTYPE_JURISDICTION, idiStr);
               }
            }
         }
      }

      //if( taxType == FAMILY_RESP_TAX_TYPE     ||
      //    taxType == INDIVIDUAL_RESP_TAX_TYPE ||
      //    taxType == SD_EXTERNAL_RESP )
      if( taxType == SD_EXTERNAL_RESP )
      {
         getErrMsg ( IFASTERR::RESP_NASU_NOT_AVAILABLE,
                     CND::ERR_RESP_NASU_NOT_AVAILABLE,
                     CND::WARN_RESP_NASU_NOT_AVAILABLE,
                     idDataGroup,
                     NULL_STRING);
      }
      
      if( taxType == FAMILY_RESP_TAX_TYPE     ||
          taxType == INDIVIDUAL_RESP_TAX_TYPE )
      {
         validateRESPTaxType(taxType,idDataGroup);
      }

      if( taxType == TFSA_TAX_TYPE )
      {
         Residency* residency;
         DString strJurisd;
         Shareholder *pShareholder = NULL;

         if ( getShareholder (pShareholder, idDataGroup) <= WARNING && pShareholder)
         {
            pShareholder->getField( ifds::TaxJurisCode, strJurisd, idDataGroup, false );
         }
         if( getWorkSession().getResidency( residency, taxType, strJurisd, idDataGroup ) <= WARNING && residency )
         {
            if( !residency->isTaxJurisdictionValid() )
            {
               getErrMsg ( IFASTERR::NON_RESIDENT_TAX_JURID,
                           CND::ERR_NON_RESIDENT_TAX_JURID,
                           CND::WARN_NON_RESIDENT_TAX_JURID,
                           idDataGroup,
                           NULL_STRING);
            }
         }
      }
/*
      //Rule: if TaxType is 1 ( RRSP ) or C ( LIRA ) or S ( ???? ), the age of the entity cannot be >=70 
      if ( !isNew() && ( taxType == RRSP_TAX_TYPE || taxType == LIRA_TAX_TYPE ) ) // || strTaxType == WILL_DEFIND_TAX_TYPE )
      {
         AccountEntityXref *pAccountEntityXref = NULL;
         sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );
         if ( pAccountEntityXref != NULL )
         {
            DString dstrEntityId ( I_("-1"));
            GetEntityIdForAcctOwnerSeq1 ( idDataGroup, dstrEntityId );
            dstrEntityId.stripLeading( '0' );

            if ( dstrEntityId != I_("-1") )
            {
               Entity *pEntity = NULL ;
               dstrEntityId.stripLeading( '0' );
               if ( dstrEntityId != NULL_STRING )
               {
                  getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
                  if ( pEntity )
                  {
                     int RRSP_LIRA_Owner_iAge = pEntity->getEntityAge( idDataGroup );
                     if ( RRSP_LIRA_Owner_iAge >= 70 )
                     {
                        DString idiStr, strTaxTypeDes;
                        getField ( ifds::TaxType, strTaxTypeDes, idDataGroup, true );
                        addIDITagValue( idiStr, I_("RRSPLIRA"), strTaxTypeDes );

                        sevRtn = getErrMsg( I_( "233" ), CND::ERR_E_ENTITY_AGE_OVER_69, 
                                            CND::ERR_W_ENTITY_AGE_OVER_69, idDataGroup, idiStr );
                     }
                  } // if( pEntity )
               }
            }
         } // if ( pAccountEntityXref != NULL )
      } */
   } // CFDS

   DString dstrBrokerCode,
      dstrAcctType;

   getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup,false);
   getField (ifds::AcctDesignation, dstrAcctDesignation, idDataGroup,false);
   getField (ifds::AcctType, dstrAcctType, idDataGroup,false);

   validateAcctCatEPA(dstrBrokerCode,
                      dstrAcctDesignation,
                      dstrAcctType,
                      taxType,
                      idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());

} // end of validateTaxType


//******************************************************************************
bool MFAccount::getFundDetailList ( ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundDetailList" ) );

   if( !_pFundDetailList )
   {
      getMgmtCo().getFundDetailList( _pFundDetailList );
   }

   if( _pFundDetailList )
   {
      return(true);
   }
   else
   {
      return(false);
   }
}


//******************************************************************************
SEVERITY MFAccount::purchaseGICAllow ( DString &dstrFund, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "purchaseGICAllow" ) );

   // check if Tax Type allow GIC fund
   DString dstrTaxType, dstrGICAllow, dstrFundType (NULL_STRING);
   getField ( ifds::TaxType, dstrTaxType, idDataGroup);
   TaxTypeRule *pTaxTypeRule = NULL;

   SEVERITY sevRtn = getTaxTypeRule ( pTaxTypeRule, idDataGroup );
   if( pTaxTypeRule )
   {
      pTaxTypeRule->getField ( ifds::GICallowed, dstrGICAllow, idDataGroup);

      FundMasterList *pFundMasterList; 
      sevRtn = getMgmtCo().getFundMasterList( pFundMasterList );
      if ( dstrGICAllow.strip().upperCase() == NO && pFundMasterList->isGICFund(dstrFund ) )
         ADDCONDITIONFROMFILE( CND::ERR_GIC_PURCHASE_NOT_ALLOWED );
/*
      if( pFundMasterList )
      {
         pFundMasterList->getField( dstrFund, ifds::FundType, dstrFundType, idDataGroup, false);
         dstrFundType.strip().upperCase();
      }

      DString dstrGICFundType = I_( "C,S" ); // compound interest and simple interest 
      if( dstrGICAllow.strip().upperCase() == NO && DSTCommonFunctions::codeInList( dstrFundType, dstrGICFundType) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_GIC_PURCHASE_NOT_ALLOWED );
      }*/
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::AMSFundAllow ( const DString &dstrFund, const DString &dstrClass, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "AMSFundAllow" ) );

   if ( isAMSAccount ( idDataGroup ) ) 
   {
      FundMasterList *pFundMasterList; 
      SEVERITY sevRtn = getMgmtCo().getFundMasterList( pFundMasterList );
      if ( pFundMasterList && pFundMasterList->isGICFund(dstrFund) ) {
         ADDCONDITIONFROMFILE( CND::ERR_GIC_FUND_NOT_ALLOWED_IN_AMS )
      } else if ( pFundMasterList && pFundMasterList->isMPSFund ( dstrFund) ) {
         ADDCONDITIONFROMFILE( CND::ERR_MPS_FUND_NOT_ALLOWED_IN_AMS )
      } else {
         DString dstrAMSOrder, dstrAMSFund = NO;
         getWorkSession().getOption( ifds::AMSOrder, dstrAMSOrder, idDataGroup, false );
         if( YES == dstrAMSOrder ) {
            getFundDetailList();
            FundDetail *pFundDetail = nullptr;
            if( _pFundDetailList ) {
               _pFundDetailList->getField ( dstrFund, dstrClass, ifds::AMSFund, dstrAMSFund, idDataGroup, false );
               dstrAMSFund.strip();
               _pFundDetailList->getFundDetail(dstrFund, dstrClass, idDataGroup, pFundDetail);
            }
            if( NO == dstrAMSFund ) {
               ADDCONDITIONFROMFILE( CND::ERR_RIF_AMS_FUND_FUND_CODE );
            }
         }
      }
   }

/*
   DString dstrAMSOrder, dstrAMSCode, dstrAMSFund = NO;

   getWorkSession().getOption( ifds::AMSOrder, dstrAMSOrder, idDataGroup, false );
   if( YES == dstrAMSOrder )
   {
      getField( ifds::AMSCode, dstrAMSCode, idDataGroup );
      dstrAMSCode.strip();

      if( !dstrAMSCode.empty() )
      {
         getFundDetailList();
         if( _pFundDetailList )
         {
            _pFundDetailList->getField ( dstrFund, dstrClass, ifds::AMSFund, dstrAMSFund, idDataGroup, false );
            dstrAMSFund.strip();
         }

         if( NO == dstrAMSFund )
         {
            ADDCONDITIONFROMFILE( CND::ERR_RIF_AMS_FUND_FUND_CODE );
            // warning: AMS fund is entered for a non-AMS account
         }
      }
   }*/
   return(GETCURRENTHIGHESTSEVERITY());

}
//******************************************************************************

SEVERITY MFAccount::getAccountReviewList( AccountReviewList*& pAccountReviewList, const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountReviewList" ) );

   pAccountReviewList = dynamic_cast<AccountReviewList*>( BFCBO::getObject( I_( "AccountReviewList" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pAccountReviewList )
   {
      if( isNew() )
      {
         pAccountReviewList = new AccountReviewList( *this );
         pAccountReviewList->init();
      }
      else if( inquireDatabase ) //make the view call
      {
         pAccountReviewList = new AccountReviewList( *this );

         DString dstrAccountNum;
         getField( ifds::AccountNum, dstrAccountNum, idDataGroup );

         pAccountReviewList->init( dstrAccountNum );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pAccountReviewList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pAccountReviewList, I_( "AccountReviewList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pAccountReviewList;
            pAccountReviewList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MFAccount::getAccountTradesList(AccountTradesList *&pAccountTradesList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountTradesList" ) );

   DString accountNum;

   getField( ifds::AccountNum, accountNum, idDataGroup );
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pAccountTradesList = dynamic_cast<AccountTradesList *>( BFCBO::getObject( I_( "AccountTradesList" ), idDataGroup ) );
   if( !pAccountTradesList )
   {
      pAccountTradesList = new AccountTradesList( *this );
      pAccountTradesList->init (accountNum, idDataGroup);
      if( pAccountTradesList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject (pAccountTradesList, I_("AccountTradesList"), OBJ_ACTIVITY_NONE, idDataGroup); 
         }
         else
         {
            delete pAccountTradesList;
            pAccountTradesList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void MFAccount::getAcctOwnerEntities(  ENTITIES_VECTOR & acctOwnerEntities, const BFDataGroupId& idDataGroup )
{
   DString dstrAcctNum;
   getField ( ifds::AccountNum, dstrAcctNum, idDataGroup);
   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );
   if( pAccountEntityXref != NULL )
   {
      pAccountEntityXref->getAcctOwnerEntities(  acctOwnerEntities, dstrAcctNum, idDataGroup );
   }
}

//******************************************************************************
void MFAccount::getBeneficiaries(  ACCTENTITYOBJ_VECTOR & vBenefEntities, const BFDataGroupId& idDataGroup )
{
   DString dstrAcctNum;
   getField ( ifds::AccountNum, dstrAcctNum, idDataGroup);
   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );
   if( pAccountEntityXref != NULL )
   {
      pAccountEntityXref->getBeneficiaries(  vBenefEntities, dstrAcctNum, idDataGroup );
   }
}

//******************************************************************************
void MFAccount::getAnnitants(  ACCTENTITYOBJ_VECTOR & vAnnitantEntities, const BFDataGroupId& idDataGroup )
{
   DString dstrAcctNum;
   getField ( ifds::AccountNum, dstrAcctNum, idDataGroup);
   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );
   if( pAccountEntityXref != NULL )
   {
      pAccountEntityXref->getAnnitants(  vAnnitantEntities, dstrAcctNum, idDataGroup );
   }
}

//******************************************************************************
void MFAccount::getAcctOwners(  ACCTENTITYOBJ_VECTOR & vAcctOwnerEntities, const BFDataGroupId& idDataGroup )
{
   DString dstrAcctNum;
   getField ( ifds::AccountNum, dstrAcctNum, idDataGroup);
   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );
   if( pAccountEntityXref != NULL )
   {
      pAccountEntityXref->getAcctOwners(  vAcctOwnerEntities, dstrAcctNum, idDataGroup );
   }
}

//******************************************************************************
bool MFAccount::isSpousalBeneficiary( const DString &dstrEntityIdIn, 
                                      const BFDataGroupId &idDataGroup)
{
   bool bIsSpousalBeneficiary = false;
   ACCTENTITYOBJ_VECTOR vBenEnitiesVector;

   getBeneficiaries (vBenEnitiesVector, idDataGroup);

   int iNumOfBen = vBenEnitiesVector.size();
   DString cssStopSINMatch;

   getWorkSession ().getOption ( ifds::CSSStopSINMatch, 
                                 cssStopSINMatch, 
                                 BF::HOST,
                                 false);  
   for (int i = 0; i < iNumOfBen; ++i)
   {
      DString dstrEntityId;

      dynamic_cast <AccountEntityXrefObject*>(vBenEnitiesVector[i])->getField (ifds::EntityId, dstrEntityId, idDataGroup);
      if (cssStopSINMatch == I_("Y"))
      {
         bIsSpousalBeneficiary = isSINMatching (dstrEntityIdIn, dstrEntityId, idDataGroup);
      }
      else if (dstrEntityId == dstrEntityIdIn)
      {
         bIsSpousalBeneficiary = true;
      }
      if (bIsSpousalBeneficiary)
      {
         DString dstrSpouseBenefReLn,
            dstrRelateCode;

         getWorkSession().getOption (ifds::SpouseBenefReLn, dstrSpouseBenefReLn, idDataGroup);
         dynamic_cast <AccountEntityXrefObject*> (vBenEnitiesVector[i])->getField (ifds::RelateCode, dstrRelateCode, idDataGroup);                 
         bIsSpousalBeneficiary = DSTCommonFunctions::codeInList (dstrRelateCode, dstrSpouseBenefReLn);
         if (bIsSpousalBeneficiary)
         {
            break;
         }
      }
   }
   return bIsSpousalBeneficiary;
}

//******************************************************************************
bool MFAccount::isChildBeneficiary ( const DString &dstrEntityIdIn, 
                                     const BFDataGroupId &idDataGroup)
{
   bool bIsChildBeneficiary = false;
   ACCTENTITYOBJ_VECTOR vBenEnitiesVector;

   getBeneficiaries (vBenEnitiesVector, idDataGroup);

   int iNumOfBen = vBenEnitiesVector.size();
   DString cssStopSINMatch;

   getWorkSession ().getOption ( ifds::CSSStopSINMatch, 
                                 cssStopSINMatch, 
                                 BF::HOST,
                                 false);  
   for (int i = 0; i < iNumOfBen; ++i)
   {
      DString dstrEntityId;

      dynamic_cast <AccountEntityXrefObject*>(vBenEnitiesVector[i])->getField (ifds::EntityId, dstrEntityId, idDataGroup);
      if (cssStopSINMatch == I_("Y"))
      {
         bIsChildBeneficiary = isSINMatching (dstrEntityIdIn, dstrEntityId, idDataGroup);
      }
      else if (dstrEntityId == dstrEntityIdIn)
      {
         bIsChildBeneficiary = true;
      }
      if (bIsChildBeneficiary)
      {
         DString dstrChildBenefReLn,
            dstrRelateCode;

         getWorkSession().getOption (ifds::ChildBenefReLn, dstrChildBenefReLn, idDataGroup);
         dynamic_cast <AccountEntityXrefObject*>(vBenEnitiesVector[i])->getField (ifds::RelateCode, dstrRelateCode, idDataGroup);
         bIsChildBeneficiary = DSTCommonFunctions::codeInList (dstrRelateCode, dstrChildBenefReLn);
         if (bIsChildBeneficiary)
         {
            break;
         }
      }
   }
   return bIsChildBeneficiary;
}

//******************************************************************************
bool MFAccount::isBeneficiary (const DString &dstrEntityIdIn, 
                               const BFDataGroupId &idDataGroup)
{
   bool bOk = false;
   DString dstrEntityId,
      cssStopSINMatch;
   ACCTENTITYOBJ_VECTOR vBenEnitiesVector;
   getBeneficiaries (vBenEnitiesVector, idDataGroup);
   int iNumOfBen = vBenEnitiesVector.size();
   getWorkSession ().getOption ( ifds::CSSStopSINMatch, 
                                 cssStopSINMatch, 
                                 BF::HOST,
                                 false);

//if the generic control is turned on we need to look if the SIN# are matching
   for (int i = 0; i < iNumOfBen; ++i)
   {
      dynamic_cast <AccountEntityXrefObject*>(vBenEnitiesVector[i])->getField (ifds::EntityId, dstrEntityId, idDataGroup);
      if (cssStopSINMatch == I_("Y"))
      {
         bOk = isSINMatching (dstrEntityIdIn, dstrEntityId, idDataGroup);
         if (bOk)
         {
            break;
         }
      }
      else if (dstrEntityId == dstrEntityIdIn)
      {
         bOk = true;
         break;
      }
   }
   return bOk;
}

//******************************************************************************
bool MFAccount::isSINMatching (const DString &entityId1, const DString& entityId2,
                               const BFDataGroupId &idDataGroup)
{
   bool bSINMatching = false;
   Entity *pEntity1 (NULL),
      *pEntity2 (NULL);
   if ( getWorkSession().getEntity ( idDataGroup, 
                                     entityId1, 
                                     pEntity1) <= WARNING &&
        pEntity1 &&
        getWorkSession().getEntity ( idDataGroup, 
                                     entityId2, 
                                     pEntity2) <= WARNING &&
        pEntity2)
   {
      EntityIdsList *pEntityIdsList1 (NULL),
         *pEntityIdsList2 (NULL);

      if ( pEntity1->getEntityIdsList (pEntityIdsList1, idDataGroup) <= WARNING &&
           pEntityIdsList1 &&
           pEntity2->getEntityIdsList (pEntityIdsList2, idDataGroup) <= WARNING &&
           pEntityIdsList2)
      {
         BFObjIter iter1 (*pEntityIdsList1, idDataGroup);

         while (!iter1.end())
         {
            DString idType1;

            iter1.getObject()->getField (ifds::IdType, idType1, idDataGroup);
            if (idType1 == I_("06")) //SIN
            {
               DString idValue1;

               iter1.getObject()->getField (ifds::IdValue, idValue1, idDataGroup);
               BFObjIter iter2 (*pEntityIdsList2, idDataGroup);

               while (!iter2.end())
               {
                  DString idType2;

                  iter2.getObject()->getField (ifds::IdType, idType2, idDataGroup);
                  if (idType2 == I_("06")) //SIN
                  {
                     DString idValue2;

                     iter2.getObject()->getField (ifds::IdValue, idValue2, idDataGroup);
                     if (idValue1 == idValue2)
                     {
                        bSINMatching = true;
                        break;
                     }
                  }
                  ++iter2;
               }
            }
            if (bSINMatching)
            {
               break;
            }
            ++iter1;
         }
      }
   }
   return bSINMatching;
}

//******************************************************************************
void MFAccount::GetEntityIdForAcctOwnerSeq1( const BFDataGroupId& idDataGroup, DString& entityId )
{
   DString dstrAcctNum;
   getField ( ifds::AccountNum, dstrAcctNum, idDataGroup);
   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );
   if( pAccountEntityXref != NULL )
   {
      pAccountEntityXref->GetEntityIdForAccountOwnerSequence1( dstrAcctNum, idDataGroup, entityId );
   }
}

//******************************************************************************
//void MFAccount::GetEntityInfoForAcctOwner( const BFDataGroupId& idDataGroup, const DString& seqNumber, 
//										DString& entityId, DString& firstName, DString& lastName )
//{
//   DString dstrAcctNum;
//   getField ( ifds::AccountNum, dstrAcctNum, idDataGroup);
//   AccountEntityXref *pAccountEntityXref = NULL;
//   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );
//   if( pAccountEntityXref != NULL )
//   {
//      pAccountEntityXref->GetAcctOwnerEntityInfo( dstrAcctNum, seqNumber, idDataGroup, entityId, firstName, lastName );
//   }
//}

//******************************************************************************
SEVERITY MFAccount::getACBList( ACBList *&pACBList, 
                                const BFDataGroupId& idDataGroup, 
                                const DString& strFund,
                                const DString& strClass,
                                bool inquireDatabase )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getACBList" ) );

   DString strKey = I_("ACBList_");
   strKey += strFund;
   strKey += I_("_");
   strKey += strClass;

   pACBList = dynamic_cast<ACBList*>(BFCBO::getObject( strKey, idDataGroup ) );

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pACBList )
   {
      if( inquireDatabase )
      {
         DString accountNum, AsofDate;

         getField( ifds::AccountNum, accountNum, idDataGroup );
         pACBList = new ACBList( *this );

         if( getWorkSession().getOption( ifds::CurrBusDate, AsofDate, idDataGroup, false ) <= WARNING )
         {
            DString empty( NULL_STRING );
            pACBList->init( accountNum, strFund, strClass );
            //if we inquire the database the group id should be the host
            idWorkingDataGroup = BF::HOST;
         }
      }
      if( pACBList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pACBList, strKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pACBList;
            pACBList = NULL;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
unsigned int MFAccount::getNumOfEmbededACBList(const BFDataGroupId& idDataGroup )
{
   unsigned int iNumOfEmbededACBList = 0;
   BFObjIter iterListOfACBs( *this, idDataGroup);
   iterListOfACBs.begin();

   while (!iterListOfACBs.end())
   {
      if( dynamic_cast<ACBList*>(iterListOfACBs.getObject ()))
      {
         iNumOfEmbededACBList++;
      }

      ++iterListOfACBs;
   }

   return iNumOfEmbededACBList;
}

//******************************************************************************
SEVERITY MFAccount::getEmbededACBListBySeq( unsigned int iNumSeq,
                                            ACBList *&pACBList, 
                                            const BFDataGroupId& idDataGroup, 
                                            DString& strFund,
                                            DString& strClass )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEmbededACBListBySeq" ) );

   unsigned int iNumOfEmbededACBList = 0;
   BFObjIter iterListOfACBs( *this, idDataGroup);
   iterListOfACBs.begin();

   while (!iterListOfACBs.end())
   {
      if( dynamic_cast<ACBList*>(iterListOfACBs.getObject ()))
      {
         if(iNumSeq == iNumOfEmbededACBList)
         {
            pACBList = dynamic_cast<ACBList*>(iterListOfACBs.getObject ());
            BFObjectKey objKey = iterListOfACBs.getKey();
            
            DString strACBKey(objKey.getStringKey());
            DString acbFundCode, acbClassCode;
            pACBList->getField (ifds::FundCode, acbFundCode, idDataGroup, false);
            pACBList->getField (ifds::ClassCode, acbClassCode, idDataGroup, false);
            strFund = acbFundCode;
            strClass = acbClassCode;
            break;
         }
         iNumOfEmbededACBList++;
      }

      ++iterListOfACBs;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getFreeUnitList(FreeUnitList *&pFreeUnitList, 
                                    const BFDataGroupId& idDataGroup,
                                    const DString& AcctLvlDSCFund,
                                    const DString& AllFundMode,
                                    const DString& AllFundGroupMode,
                                    bool inquireDatabase)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFreeUnitList"));

   DString objKey = I_("FreeUnitList;AcctLvlDSCFund=") + AcctLvlDSCFund + 
                    I_(";AllFundMode=") + AllFundMode + 
                    I_(";AllFundGroupMode=") + AllFundGroupMode;

   pFreeUnitList = dynamic_cast<FreeUnitList*>(BFCBO::getObject(objKey, idDataGroup));

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pFreeUnitList )
   {
      if( inquireDatabase )
      {
         DString accountNum;

         getField( ifds::AccountNum, accountNum, idDataGroup );
         pFreeUnitList = new FreeUnitList( *this );

         pFreeUnitList->init(accountNum, AcctLvlDSCFund, AllFundMode, AllFundGroupMode);
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pFreeUnitList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pFreeUnitList, objKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pFreeUnitList;
            pFreeUnitList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getFreeUnitListBy(FreeUnitList *&pFreeUnitList, 
                                      const BFDataGroupId& idDataGroup,
                                      const DString& FundCode,
							          const DString& ClassCode,
                                      const DString& FundGroup,
                                      bool inquireDatabase)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFreeUnitListBy"));

   DString objKey = I_("FreeUnitList;FundCode=") + FundCode + 
                    I_(";ClassCode=") + ClassCode + 
                    I_(";FundGroup=") + FundGroup;

   pFreeUnitList = dynamic_cast<FreeUnitList*>(BFCBO::getObject(objKey, idDataGroup));

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pFreeUnitList )
   {
      if( inquireDatabase )
      {
         DString accountNum;

         getField( ifds::AccountNum, accountNum, idDataGroup );
         pFreeUnitList = new FreeUnitList( *this );

         pFreeUnitList->init2(accountNum, FundCode, ClassCode, FundGroup);
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pFreeUnitList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pFreeUnitList, objKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pFreeUnitList;
            pFreeUnitList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getFreeUnitList( FreeUnitList *&pFreeUnitList, const BFDataGroupId& idDataGroup, bool inquireDatabase )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFreeUnitList" ) );
   pFreeUnitList = dynamic_cast<FreeUnitList*>(BFCBO::getObject( I_( "FreeUnitList" ), idDataGroup ) );

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pFreeUnitList )
   {
      if( inquireDatabase )
      {
         DString accountNum;

         getField( ifds::AccountNum, accountNum, idDataGroup );
         pFreeUnitList = new FreeUnitList( *this );

         pFreeUnitList->init( accountNum );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pFreeUnitList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pFreeUnitList, I_( "FreeUnitList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pFreeUnitList;
            pFreeUnitList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//This list will not be populated if we don't call getAccountHoldingList(), getACBHoldingsList() and/or getFreeUnitsList() before
SEVERITY MFAccount::getAccountHoldingsByCurrencyList( AccountHoldingsByCurrencyList *&pAccountHoldingsByCurrencyList, const BFDataGroupId& idDataGroup, bool inqDatabase )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountHoldingsByCurrencyList" ) );

   pAccountHoldingsByCurrencyList = dynamic_cast<AccountHoldingsByCurrencyList*>(BFCBO::getObject( I_( "AccountHoldingsByCurrencyList" ), idDataGroup ) );

   if( !pAccountHoldingsByCurrencyList )
   {
      pAccountHoldingsByCurrencyList = new AccountHoldingsByCurrencyList( *this );
      pAccountHoldingsByCurrencyList->init(); 
      if( pAccountHoldingsByCurrencyList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pAccountHoldingsByCurrencyList, I_( "AccountHoldingsByCurrencyList" ), OBJ_ACTIVITY_NONE, idDataGroup );
         }
         else
         {
            delete pAccountHoldingsByCurrencyList;
            pAccountHoldingsByCurrencyList = NULL;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool MFAccount::pendingOfFundExist( const DString fundCode, const DString classCode,const DString TransType, const BFDataGroupId& idDataGroup ) 
{
   bool pendingExists = false;
   DString positionKey;

   MFAccountHoldingList *pMFAccountHoldingList = NULL;
   PendingTradeList     *pPendingTradesList = NULL;

   if( getPendingTradesList( pPendingTradesList, idDataGroup, FULL_LIST ) <= WARNING )//get the whole list
   {
      pendingExists = pPendingTradesList->fundclassExist( fundCode, classCode, idDataGroup, TransType );
   }

   return(pendingExists);
}

//******************************************************************************
bool MFAccount::pendingRedemptionExist( const DString& dstrfundCode, const DString& dstrclassCode, 
                                        const BFDataGroupId& idDataGroup ) 
{
   bool pendingRedemptionExists = false;
   DString positionKey;

   PendingTradeList     *pPendingTradesList = NULL;

   if( getPendingTradesList( pPendingTradesList, idDataGroup, FULL_LIST ) <= WARNING )//get the whole list
   {
      pendingRedemptionExists = pPendingTradesList->redemptionExist( dstrfundCode, dstrclassCode, 
                                                                     idDataGroup );
   }

   return(pendingRedemptionExists);
}

/* move to Trade.cpp
//******************************************************************************
SEVERITY MFAccount::getTradeMinAmtCheck(const DString&  strAccountNum,const DString&  strFundCode, 
                                        const DString&  strClassCode, const DString&  strTransType, const DString&  strAmountType, 
                                        const DString&  strAmount, const DString&  strEffectiveDate, const DString&  strSettleCurrency,
                                        TradeMinAmtCheck*& pTradeMinAmtCheck, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTradeMinAmtCheck" ) );
   pTradeMinAmtCheck = dynamic_cast<TradeMinAmtCheck*>(BFCBO::getObject( I_( "TradeMinAmtCheck" ), idDataGroup ) );

   if( !pTradeMinAmtCheck )
   {
      pTradeMinAmtCheck = new TradeMinAmtCheck( *this );
      if( pTradeMinAmtCheck->init(strAccountNum, strFundCode, strClassCode, strTransType, strAmountType,
                                  strAmount, strEffectiveDate, strSettleCurrency) <= WARNING )
      {
         setObject( pTradeMinAmtCheck, I_( "TradeMinAmtCheck" ), OBJ_ACTIVITY_NONE, BF::HOST ); 
      }
      else
      {
         delete pTradeMinAmtCheck;
         pTradeMinAmtCheck = NULL;
      }
   }
   else if( pTradeMinAmtCheck->isChanged(strAccountNum, strFundCode, strClassCode,
                                         strTransType, strAmountType, strAmount, strEffectiveDate, strSettleCurrency) )
   {
      if( pTradeMinAmtCheck->refresh(strAccountNum, strFundCode, strClassCode,
                                     strTransType, strAmountType, strAmount, strEffectiveDate, strSettleCurrency) > WARNING )
      {
         pTradeMinAmtCheck = NULL;
         deleteObject(I_( "TradeMinAmtCheck" ), BF::HOST, true );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
} */

//******************************************************************************
SEVERITY MFAccount::getESoPInfo( ESoPInfo *&pESoPInfo, const BFDataGroupId& idDataGroup, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getESoPInfo" ) );
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   BF_OBJ_ACTIVITY activity = isNew() ? OBJ_ACTIVITY_ADDED : OBJ_ACTIVITY_NONE;

   pESoPInfo = dynamic_cast<ESoPInfo*>(BFCBO::getObject( I_( "ESoPInfo" ), idDataGroup , OBJ_TYPE_NONE, activity ));

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pESoPInfo && bCreate )
   {
      DString dstrTaxType;
      getField( ifds::TaxType, dstrTaxType, idDataGroup );
      if( dstrTaxType != ESOP_INVESTMENT && dstrTaxType != ESOP_PARTICIPATION )
         return(GETCURRENTHIGHESTSEVERITY());

      pESoPInfo = new ESoPInfo( *this );
      if( isNew() ) //if the account is new, no need to inquire database
         pESoPInfo->initNew(idDataGroup);
      else
      {
         pESoPInfo->init(idDataGroup);
         idWorkingDataGroup = BF::HOST;
      }

      if( pESoPInfo )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
            setObject( pESoPInfo, I_( "ESoPInfo" ), activity, idWorkingDataGroup );
         else
         {
            delete pESoPInfo;
            pESoPInfo = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY MFAccount::getRSPContributionList( RSPContributionList *&pRSPContributionList, const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRSPContributionList" ) );

   //Should not be able to get RSPContributionList if is a new Account
   if( isNew() )
      assert (0);

   pRSPContributionList = dynamic_cast<RSPContributionList*>(BFCBO::getObject( I_( "RSPContributionList" ), idDataGroup ) );

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pRSPContributionList )
   {
      if( inquireDatabase )
      {
         DString accountNum;
         getField( ifds::AccountNum, accountNum, idDataGroup );

         pRSPContributionList = new RSPContributionList( *this );
         pRSPContributionList->init( accountNum );
         idWorkingDataGroup = BF::HOST;
      }
      if( pRSPContributionList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
            setObject( pRSPContributionList, I_( "RSPContributionList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup );
         else
         {
            delete pRSPContributionList;
            pRSPContributionList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getTransactionHistoryList ( TransactionList *&pTransactionList, 
                                                const DString& dstrFundCode, 
                                                const DString& dstrClassCode, 
                                                const DString& dstrNumEntry, 
                                                const DString& allFundsMode, 
                                                const DString& strReqTransid,
                                                const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/,
                                                DString ExtTransNum, /*=NULL_STRING*/
												bool receiveAll,
												DString TransNum,
												const DString& strWireOrder)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTransactionHistoryList" ) );
   //No History availiable on New Account
   if( isNew() )
      assert (0);

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( inquireDatabase )
   {
      DString dstrAccountNum;
      getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );
      pTransactionList = new TransactionList( *this );
      if( ExtTransNum.empty() )
      {
		  if( TransNum.empty() && strWireOrder.empty ())
		  {
			pTransactionList->init ( dstrAccountNum, dstrFundCode, dstrClassCode, dstrNumEntry, allFundsMode, strReqTransid, 
				I_("N"), NULL_STRING, NULL_STRING, I_("N"), NULL_STRING, NULL_STRING, 
				I_("N"), NULL_STRING, NULL_STRING, NULL_STRING, receiveAll );
		  }
		  else if (!strWireOrder.empty ())
		  {
				pTransactionList->initSearch( I_("AcctWire"),
						                      dstrAccountNum,
											  NULL_STRING,
                                              strWireOrder, 
                                              NULL_STRING, 
                                              NULL_STRING, 
                                              NULL_STRING,
                                              NULL_STRING, 
                                              NULL_STRING,
                                              NULL_STRING, 
                                              NULL_STRING,
						                      NULL_STRING,
						                      NULL_STRING,
				                              NULL_STRING,
				                              NULL_STRING,
				                              NULL_STRING,
				                              NULL_STRING,
				                              NULL_STRING,
				                              NULL_STRING );
		  }
		  else
		  {
				pTransactionList->initSearch( I_("Transnum"),
						         dstrAccountNum,
                           TransNum,
                           NULL_STRING, 
                           NULL_STRING, 
                           NULL_STRING, 
                           NULL_STRING,
                           NULL_STRING, 
                           NULL_STRING,
                           NULL_STRING, 
                           NULL_STRING,
						   NULL_STRING,
						   NULL_STRING,
				           NULL_STRING,
				           NULL_STRING,
				           NULL_STRING,
				           NULL_STRING,
				           NULL_STRING,
				           NULL_STRING );
		  }
	  }
	  else
      {
         pTransactionList->initSearch( I_("ExtTransnum"),
                                       dstrAccountNum,
                                       NULL_STRING,
                                       NULL_STRING, 
                                       NULL_STRING, 
                                       ExtTransNum, 
                                       NULL_STRING,
                                       NULL_STRING, 
                                       NULL_STRING,
                                       NULL_STRING, 
                                       NULL_STRING,
                                       NULL_STRING,
                                       NULL_STRING,
                                       NULL_STRING,
                                       NULL_STRING,
                                       NULL_STRING,
                                       NULL_STRING,
                                       NULL_STRING,
                                       NULL_STRING );
      }
      idWorkingDataGroup = BF::HOST;
   }
   else
   {
      pTransactionList = dynamic_cast<TransactionList*>(BFCBO::getObject( I_( "TransactionHistoryList" ), idDataGroup ) );
   }

   if( pTransactionList && GETCURRENTHIGHESTSEVERITY() <= WARNING )
   {
      setObject ( pTransactionList, I_( "TransactionHistoryList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup );      
   }
   else
   {
      delete pTransactionList;
      pTransactionList = NULL;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool MFAccount::IsTransactionPending( const DString& ExtTransNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "IsTransactionPending" ) );

   if( isNew() )
      assert (0);

   DString AccountNum;
   getField( ifds::AccountNum, AccountNum, BF::HOST );

   PendingTradeList *pPendingTradeList = new PendingTradeList( *this );
   SEVERITY sevReturn = pPendingTradeList->initSearch( I_("ExtTransnum"),
                                                       AccountNum,
                                                       NULL_STRING,
                                                       NULL_STRING, 
                                                       NULL_STRING, 
                                                       ExtTransNum, 
                                                       NULL_STRING,
                                                       NULL_STRING, 
                                                       NULL_STRING,
                                                       NULL_STRING, 
                                                       NULL_STRING,
                                                       NULL_STRING,
                                                       NULL_STRING,
                                                       NULL_STRING );
   int iNumberOfItems = 0;
   if( pPendingTradeList )
   {
      BFObjIter iterList( *pPendingTradeList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
      iNumberOfItems = iterList.getNumberOfItemsInList();
      delete pPendingTradeList;
      pPendingTradeList = NULL;
   }
   CLEARCONDITIONS();
   return( sevReturn <= WARNING && iNumberOfItems );
}

//******************************************************************************
void MFAccount::getLastActiveTransactionHistoryList ( TransactionList *&pTransactionList, const BFDataGroupId& idDataGroup )
{
   pTransactionList = dynamic_cast<TransactionList*>(BFCBO::getObject( I_( "TransactionHistoryList" ), idDataGroup ) );   
}

//******************************************************************************
SEVERITY MFAccount::getMatchTransferList ( MatchTransferList *&pMatchTransferList, DString& dstrTransId,
                                           const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMatchTransferList" ) );
   //No History availiable on New Account
//CP20030319   if( isNew() )
//CP20030319      assert (0);
   assert( isNew() );

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( inquireDatabase )
   {
      DString dstrAccountNum;
      getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );
      pMatchTransferList = new MatchTransferList( *this );
      pMatchTransferList->init ( dstrTransId, I_( "N" ), NULL_STRING  );
      idWorkingDataGroup = BF::HOST;
   }
   else
   {
      pMatchTransferList = dynamic_cast<MatchTransferList*>(BFCBO::getObject( I_( "MatchTransferList" ), idDataGroup ) );
   }

   if( pMatchTransferList && GETCURRENTHIGHESTSEVERITY() <= WARNING )
   {
      setObject ( pMatchTransferList, I_( "MatchTransferList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup );      
   }
   else
   {
      delete pMatchTransferList;
      pMatchTransferList = NULL;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getAsPensionPlan( AsPensionPlan *&pAsPensionPlan, const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAsPensionPlan" ) );
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pAsPensionPlan = dynamic_cast<AsPensionPlan*>(BFCBO::getObject(ASPENSIONPLAN, idDataGroup ) );

   bool bCreate = false;
   if( !pAsPensionPlan /*&& inquireDatabase*/ )
   {
      DString dstrTaxType;
      getField( ifds::TaxType, dstrTaxType, idDataGroup );
      if( dstrTaxType != I_( "P" ) )
         return(GETCURRENTHIGHESTSEVERITY());
      if( isNew() )
      {
         pAsPensionPlan = new AsPensionPlan( *this );
         pAsPensionPlan->init( idDataGroup );        
      }
      else if( inquireDatabase )
      {
         //idDataGroup = BF::HOST;
         DString accountNum;
         getField( ifds::AccountNum, accountNum, idDataGroup );

         pAsPensionPlan = new AsPensionPlan( *this );
         SEVERITY sev = pAsPensionPlan->init( accountNum, idDataGroup );
         if( sev > WARNING )
         {
            Frame* fm =  FRAMEBELOW();
            unsigned count = fm->getCount( );
            Condition   *c = NULL;
            for( unsigned i = 0; i < count; i++ )
            {
               c = fm->getCondition( i );
               if( c->getCode() == CND::ERR_DATA_NOT_FOUND )
               {
                  fm->clearCondition( i );
                  delete   pAsPensionPlan;      
                  pAsPensionPlan = new AsPensionPlan( *this );
                  pAsPensionPlan->init( idDataGroup );        
                  break;
               }
            } 
         }
      }
      if( pAsPensionPlan )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            if( !isNew() )
               setObject( pAsPensionPlan, ASPENSIONPLAN, OBJ_ACTIVITY_NONE, BF::HOST );
            else
               setObject( pAsPensionPlan, ASPENSIONPLAN, OBJ_ACTIVITY_ADDED, idDataGroup );
         }
         else
         {
            delete pAsPensionPlan;
            pAsPensionPlan = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
SEVERITY MFAccount::getFeeParamList(FeeParamList *&pFeeParamList,const BFDataGroupId& idDataGroup,bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeParamList" ) );
   pFeeParamList = dynamic_cast<FeeParamList*>(BFCBO::getObject( I_( "FeeParamList" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pFeeParamList )
   {
      DString dstrAccountNum;
      getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
      if( isNew () )
      {
         pFeeParamList = new FeeParamList( *this );
         pFeeParamList->initNew( dstrAccountNum, idDataGroup );
      }
      else if( inquireDatabase )
      {
         pFeeParamList = new FeeParamList( *this );
         pFeeParamList->init( dstrAccountNum,BF::HOST );
         idWorkingDataGroup = BF::HOST;
      }
      if( pFeeParamList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
            if( isNew() )
               setObject( pFeeParamList, I_( "FeeParamList" ), OBJ_ACTIVITY_ADDED, idWorkingDataGroup );
            else
               setObject( pFeeParamList, I_( "FeeParamList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup );
         else
         {
            delete pFeeParamList;
            pFeeParamList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY MFAccount::getAcctSplitCommList( AcctSplitCommList *&pAcctSplitCommList, const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAcctSplitCommList" ) );

   pAcctSplitCommList = dynamic_cast<AcctSplitCommList*>(BFCBO::getObject( I_( "AcctSplitCommList" ), idDataGroup ) );

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pAcctSplitCommList )
   {
      DString dstrAccountNum;
      getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
      if( isNew () )
      {
         pAcctSplitCommList = new AcctSplitCommList( *this );
         pAcctSplitCommList->initNew( dstrAccountNum );
      }
      else if( inquireDatabase )
      {
         pAcctSplitCommList = new AcctSplitCommList( *this );
         pAcctSplitCommList->init( dstrAccountNum );
         idWorkingDataGroup = BF::HOST;
      }
      if( pAcctSplitCommList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
            if( isNew() )
               setObject( pAcctSplitCommList, I_( "AcctSplitCommList" ), OBJ_ACTIVITY_ADDED, idWorkingDataGroup );
            else
               setObject( pAcctSplitCommList, I_( "AcctSplitCommList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup );
         else
         {
            delete pAcctSplitCommList;
            pAcctSplitCommList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::exchEscrow ( const DString&  dstrTradeDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "exchEscrow" ) );

   DString acctNum;
   getField(ifds::AccountNum, acctNum, idDataGroup);
   acctNum.strip().stripLeading( '0' );

   AccountEntityXref *pAccountEntityXref = NULL;

   if( getAccountEntityXref( pAccountEntityXref, idDataGroup ) <= WARNING )
   {
      DString strKey;

      if( acctNum != NULL_STRING )
         SEVERITY sevRtn = pAccountEntityXref->escrowAccount( acctNum, EXCHANGE_OUT_CODE, NULL_STRING, dstrTradeDate, idDataGroup);
   } // if found AccountEntityXref

   return(GETCURRENTHIGHESTSEVERITY());
} 

//******************************************************************************
SEVERITY MFAccount::trferEscrow ( const DString&  dstrTradeDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "exchEscrow" ) );

   DString acctNum;
   getField(ifds::AccountNum, acctNum, idDataGroup);
   acctNum.strip().stripLeading( '0' );

   AccountEntityXref *pAccountEntityXref = NULL;

   if( getAccountEntityXref( pAccountEntityXref, idDataGroup ) <= WARNING )
   {
      DString strKey;

      if( acctNum != NULL_STRING )
         SEVERITY sevRtn = pAccountEntityXref->escrowAccount( acctNum, TRANSFER_OUT_CODE, NULL_STRING, dstrTradeDate, idDataGroup);

   } // if found AccountEntityXref

   return(GETCURRENTHIGHESTSEVERITY());
} 

//******************************************************************************
SEVERITY MFAccount::addrEscrow ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addrEscrow" ) );

   DString acctNum;
   getField(ifds::AccountNum, acctNum, idDataGroup);
   acctNum.strip().stripLeading( '0' );

   AccountEntityXref *pAccountEntityXref = NULL;

   if( getAccountEntityXref( pAccountEntityXref, idDataGroup ) <= WARNING )
   {
      DString strKey;
      DString currBussinesDate;
      getWorkSession().getOption( ifds::CurrBusDate, currBussinesDate, idDataGroup, false ) ;

      if( acctNum != NULL_STRING )
         SEVERITY sevRtn = pAccountEntityXref->escrowAccount( acctNum, ADDR_CHG, NULL_STRING, currBussinesDate, idDataGroup);

   } // if found AccountEntityXref

   return(GETCURRENTHIGHESTSEVERITY());
} 

//********************************************************************************
void MFAccount::doPopulateField( const BFFieldId& idField, DString & strValue, bool formattedReturn )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPopulateField" ) );
   strValue = NULL_STRING;
   DString strAccountNum;
   BFData* pResponse = NULL;
   getResponseData(pResponse);
   if( idField != ifds::AccountNum && BFData::exists( pResponse->getRepeatId(), idField) )
   {
      BFCBO::getField( ifds::AccountNum, strAccountNum, BF::HOST, false );
      if( init(strAccountNum) <= WARNING )
         BFCBO::getField( idField, strValue, BF::HOST, formattedReturn );
   }
}

//********************************************************************************
void MFAccount::getResponseData(BFData*& pResponse)
{
   if( !_pResponseData )
      _pResponseData = new BFData(ifds::DSTC0004_VW);
   pResponse = _pResponseData;
}

//******************************************************************************
SEVERITY MFAccount::getDofBirthofOwnerSeq01( DString& dstrDofBirth, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDofBirthofOwnerSeq01" ) );

   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );

   if( pAccountEntityXref != NULL )
   {
      DString dstrEntityId ( I_("-1"));
      GetEntityIdForAcctOwnerSeq1( idDataGroup, dstrEntityId );
      dstrEntityId.stripLeading( '0' );

      if( dstrEntityId != I_("-1") )
      {
         Entity *pEntity;
         dstrEntityId.stripLeading( '0' );

         if( dstrEntityId != NULL_STRING )
         {
            getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
            if( pEntity )
            {
               pEntity->getField( ifds::DofBirth, dstrDofBirth, idDataGroup, false );
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
int MFAccount::getAgeofOwnerSeq01( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDofBirthofOwnerSeq01" ) );

   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );
   int OwnerAge;

   if( pAccountEntityXref != NULL )
   {
      DString dstrEntityId ( I_("-1"));
      GetEntityIdForAcctOwnerSeq1( idDataGroup, dstrEntityId );
      dstrEntityId.stripLeading( '0' );

      if( dstrEntityId != I_("-1") )
      {
         Entity *pEntity;
         dstrEntityId.stripLeading( '0' );

         if( dstrEntityId != NULL_STRING )
         {
            getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
            if( pEntity )
            {

               TaxTypeRule *pTaxTypeRule = NULL;
               getTaxTypeRule(pTaxTypeRule, idDataGroup);

               int ageCalcBasedOn = 0;

               if( pTaxTypeRule )
               {
                  DString dstrJurisdiction;

                  getField( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
                  pTaxTypeRule->getAgeCalcBasedOn (ageCalcBasedOn, dstrJurisdiction, idDataGroup);
               }

               OwnerAge = pEntity->getEntityAge( ageCalcBasedOn, idDataGroup );
            }
         }
      }
   }

   return(OwnerAge);

}

//******************************************************************************
SEVERITY MFAccount::validateAccountNum(const DString& strAccountNum, DSTCWorkSession &workSession)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountNum" ) );

   DString tempAccountNum(strAccountNum);
   if( tempAccountNum.strip().empty() || !tempAccountNum.isAllDigits() )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_ACCOUNT_NUMBER);
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   AccShrNumCheck checkAccNum(workSession);
   if( checkAccNum.initAccNum(strAccountNum) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());
   DString strFound;
   checkAccNum.getField(ifds::DataFound, strFound, BF::HOST, false);
   if( strFound.strip() != YES )
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_ACCOUNT_NUMBER);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::refreshDataObject()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "refreshDataObject" ) );
   doPreClearFields( );
   clearFieldMap( );
   eraseDataObjectContainers( );
   reInit( );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getDofDeathofOwnerSeq01( DString& dstrDofDeath, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDofDeathofOwnerSeq01" ) );

   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );

   if( pAccountEntityXref != NULL )
   {
      DString dstrEntityId ( I_("-1"));
      GetEntityIdForAcctOwnerSeq1( idDataGroup, dstrEntityId );
      dstrEntityId.stripLeading( '0' );

      if( dstrEntityId != I_("-1") )
      {
         Entity *pEntity;
         dstrEntityId.stripLeading( '0' );

         if( dstrEntityId != NULL_STRING )
         {
            getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
            if( pEntity )
            {
               pEntity->getField( ifds::DofDeath, dstrDofDeath, idDataGroup, false );
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY MFAccount::getPensionInfo( PensionInfo *&pPensionInfo, const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getPensionInfo" ) );   
   DString dstrTaxType;
   getField ( ifds::TaxType, dstrTaxType, idDataGroup );

   if( !getWorkSession ().isLIFLike (dstrTaxType) && !getWorkSession ().isLIRALike (dstrTaxType) && 
        dstrTaxType != LRIF_TAX_TYPE && dstrTaxType != PRIF_TAX_TYPE )
      return(GETCURRENTHIGHESTSEVERITY());
   pPensionInfo = dynamic_cast<PensionInfo*>(BFCBO::getObject( I_( "aaPensionInfo" ), idDataGroup ) );

   DString dstrPensionJurisExists;
   getField ( ifds::PensionJurisExists, dstrPensionJurisExists, idDataGroup, false );
   dstrPensionJurisExists.strip().upperCase();
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pPensionInfo )
   {
      if( isNew() )
      {
         pPensionInfo = new PensionInfo( *this );
         pPensionInfo->initNew ( idDataGroup );
      }
      else if( inquireDatabase )
      {
         idWorkingDataGroup = BF::HOST;
         if( dstrPensionJurisExists == NO )
         {
            pPensionInfo = new PensionInfo( *this );
            pPensionInfo->initNew ( idDataGroup );
         }
         else
         {
            pPensionInfo = new PensionInfo( *this );
            pPensionInfo->init( idDataGroup );
         }
      }
      if( pPensionInfo )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
            if( isNew() )
               setObject( pPensionInfo, I_( "aaPensionInfo" ), OBJ_ACTIVITY_ADDED, idWorkingDataGroup );
            else
               setObject( pPensionInfo, I_( "aaPensionInfo" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup );
         else
         {
            delete pPensionInfo;
            pPensionInfo = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::validateTaxTypeAcctType( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTaxTypeAcctType" ) );
   DString dstrTaxType, 
      dstrAcctType;

   getField ( ifds::TaxType, dstrTaxType, idDataGroup, false );
   getField ( ifds::AcctType, dstrAcctType, idDataGroup, false );
/*   if( dstrTaxType == NULL_STRING )
   {
      ADDCONDITIONFROMFILE( CND::ERR_TAX_TYPE_EMTPY );
      return(GETCURRENTHIGHESTSEVERITY());
   }
   if( dstrAcctType == NULL_STRING )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_TYPE_EMPTY );
      return(GETCURRENTHIGHESTSEVERITY());
   }
*/
   if (!dstrTaxType.empty() && !dstrAcctType.empty())
   {
      TaxTypeRule *ptaxTypeRule = NULL;

      SEVERITY sevRtn = getTaxTypeRule ( ptaxTypeRule, idDataGroup );

      if( sevRtn <= WARNING && ptaxTypeRule != NULL )
      {
         // if the account type is not valid account type under the tax type, then give error message
         if( !ptaxTypeRule->validAcctType ( dstrAcctType, idDataGroup ) )
         {
            ADDCONDITIONFROMFILE( CND::ERR_ACCT_TYPE_NOT_VALID_FOR_TAX_TYPE );  
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::validateTaxTypePensionJuris( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTaxTypePensionJuris" ) );
   SEVERITY sevRtn = NO_CONDITION;

   DString dstrPensionJuris, dstrTaxType;
   getField( ifds::TaxType, dstrTaxType, idDataGroup, false );

   if( getWorkSession ().isLIFLike (dstrTaxType) || dstrTaxType   == LRIF_TAX_TYPE || 
       getWorkSession ().isLIRALike (dstrTaxType) || PRIF_TAX_TYPE == dstrTaxType)
   {
      getField( ifds::PensionJuris, dstrPensionJuris, idDataGroup );

      if( dstrPensionJuris != NULL_STRING )
      {
         TaxTypeRule *ptaxTypeRule = NULL;
         sevRtn = getTaxTypeRule ( ptaxTypeRule, idDataGroup );
         if( sevRtn <= WARNING && ptaxTypeRule != NULL )
         {
            if( !ptaxTypeRule->isValidPensionJurisdiction( dstrPensionJuris, idDataGroup ) )
               ADDCONDITIONFROMFILE( CND::ERR_WRONG_COMBINATION_TAXTYPE_JURISDICTION );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool MFAccount::doesTaxJurisdictionLimitationListExist(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doesTaxJurisdictionLimitationListExist" ) );
   SEVERITY sevRtn = NO_CONDITION;

   DString dstrTaxType;
   getField( ifds::TaxType, dstrTaxType, idDataGroup, false );

   if( getWorkSession ().isLIFLike (dstrTaxType) || dstrTaxType == LRIF_TAX_TYPE || 
	   getWorkSession ().isLIRALike (dstrTaxType) || dstrTaxType == PRIF_TAX_TYPE )
   {
      TaxTypeRule *ptaxTypeRule = NULL;
      sevRtn = getTaxTypeRule ( ptaxTypeRule, idDataGroup );
      if( sevRtn <= WARNING && ptaxTypeRule != NULL )
      {
        return ( ptaxTypeRule->doesTaxJurisdictionLimitationListExist( idDataGroup ) );
      }
   }

   return false;
}

//**************************************************************************************
SEVERITY MFAccount::validateAltAcct( const DString& dstrAltAcctNum, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAltAcct" ) );

   SEVERITY sevRtn = SEVERE_ERROR;

   DString dstrDuplicateAltAcct, dstrBrokerCode;
   DString strCopyOfAltAcctNum = dstrAltAcctNum;
   strCopyOfAltAcctNum.strip();
   if( getWorkSession().getOption( ifds::DuplicateAltAcct, dstrDuplicateAltAcct, idDataGroup, false ) <= WARNING )
   {
      if( dstrDuplicateAltAcct.strip() == YES && !strCopyOfAltAcctNum.empty() )
      {
         getField( ifds::BrokerCode, dstrBrokerCode, idDataGroup );
         dstrBrokerCode.strip();

         BFData requestData (ifds::DSTC0003_REQ);
         BFData *responseData = new BFData(ifds::DSTC0003_VW);

         DString mgmtCoIdOut;
         requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
         requestData.setElementValue( ifds::AllAccounts, YES );
         requestData.setElementValue( ifds::SortBy, SORTED_BY_LAST_NAME );

         requestData.setElementValue( ifds::SrchAltAcct, strCopyOfAltAcctNum );
         requestData.setElementValue( ifds::SrchBroker, dstrBrokerCode );

         //should not request all the records for this warning; use 'false' for DSCRequestor
         if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::SEARCH, 
                                                   requestData, *responseData, DSTCRequestor( getSecurity(), false) ) <= WARNING )
         {
            DString dstrNumOfAcct;

            responseData->getElementValue( ifds::RepeatCount, dstrNumOfAcct );
            if( DSTCommonFunctions::convertToDouble( dstrNumOfAcct ) > 0 )
            {
               int cRepeats = responseData->getRepeatCount();
               for( int i = 0; i < cRepeats; i++ )
               {
                  const BFData &data = responseData->getRepeat( i );
                  DString strAccountNum, strSearchAcctNum;
                  getField( ifds::AccountNum, strAccountNum, idDataGroup, false );
                  strSearchAcctNum = data.getElementValue( ifds::AccountNum );
                  if( strAccountNum.strip() == strSearchAcctNum.strip() )
                     continue;

                  ADDCONDITIONFROMFILE(CND::ERR_WARN_DUPLICATE_ALTACCOUNT);
               }
            }
         }

         delete responseData;
         responseData = NULL;
      }
   }

   // AltAccountNum cannot be blank if account is either INVESTRO_CAPABLE or PUEV_CAPABLE
   if ( strCopyOfAltAcctNum.strip() == NULL_STRING )
   {
      if ( (isCategoryExist ( idDataGroup, PUEV_CAPABLE ) ) || (isCategoryExist ( idDataGroup, INVESTRO_CAPABLE )) )
         ADDCONDITIONFROMFILE(CND::ERR_ALTACCT_REQUIRED_FOR_PUEV_INVESTRO);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// return entity object pointer to the calling program
void MFAccount::getSpouseEntity(  ACCTENTITYOBJ_VECTOR & vSpouseEntitiesVertor, 
   bool bSpouse, Entity *&pEntity, const BFDataGroupId& idDataGroup )
{
   DString dstrAcctNum, dstrEntityId ( NULL_STRING);
   getField ( ifds::AccountNum, dstrAcctNum, idDataGroup);
   AccountEntityXref *pAccountEntityXref = NULL;
   pEntity = NULL;

   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );
   if( pAccountEntityXref != NULL )
   {
      pAccountEntityXref->getSpouse(  vSpouseEntitiesVertor, dstrAcctNum, bSpouse, idDataGroup );
   }

   int iNumOfSpouse = vSpouseEntitiesVertor.size();
   for( int i = 0; i < iNumOfSpouse; ++i )
   {
      dynamic_cast < AccountEntityXrefObject* >(vSpouseEntitiesVertor[i])->getField( ifds::EntityId, dstrEntityId, idDataGroup );
      if( dstrEntityId.strip() != NULL_STRING )
      {
         getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
      }
   }
}

//******************************************************************************
SEVERITY MFAccount::checkSpouseValidSINExists( bool &bSINExists, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkSpouseValidSINExists" ) );

   bool bOk (false);
   Entity *pEntity = NULL; 
   ACCTENTITYOBJ_VECTOR vSpouseEntitiesVertor;

   getSpouseEntity( vSpouseEntitiesVertor, true, pEntity, idDataGroup );
   // check if SIN is unknown
   if( pEntity )
   {
      DString sin, entityId, entityTypeFmt;
      pEntity->getField( ifds::SIN, sin, idDataGroup, false );
      pEntity->getField( ifds::EntityType, entityTypeFmt, idDataGroup, true );
      pEntity->getEntityId (entityId);

      if (sin.strip().empty())
      {
         bOk = false;
      }
      else // if even warning the SIN value is invalid 
      {
         bOk = EntityIds::validateSIN (getWorkSession(), sin, entityTypeFmt, idDataGroup) < WARNING;
      }
   }

   bSINExists = bOk;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::checkSpouseTransfereeValidSINExists( bool &bSINExists, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkSpouseTransfereeValidSINExists" ) );

   bool bOk (false);
   Entity *pEntity = NULL; 
   ACCTENTITYOBJ_VECTOR vSpouseEntitiesVertor;

   getSpouseEntity( vSpouseEntitiesVertor, false, pEntity, idDataGroup );
   // check if date of birth is unknown
   if( pEntity )
   {
      DString sin, entityId, entityTypeFmt;
      pEntity->getField( ifds::SIN, sin, idDataGroup, false );
      pEntity->getField( ifds::EntityType, entityTypeFmt, idDataGroup, true );
      pEntity->getEntityId (entityId);
      if( sin.strip().empty() )
      {
         bOk = false;
      }
      else // if even warning the SIN value is invalid 
      {
         bOk = EntityIds::validateSIN (getWorkSession(), sin, entityTypeFmt, idDataGroup) < WARNING;
      }
   }

   bSINExists = bOk;
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY MFAccount::initDefaultAddress01 (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(  CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("initDefaultAddress01"));

   Shareholder *pShareholder = NULL;
   if ( getShareholder (pShareholder, idDataGroup) <= WARNING && 
        pShareholder)
   {
      AddressList *pAddressList = NULL;

      if ( pShareholder->getAddressList (pAddressList, idDataGroup, true) <= WARNING && 
           pAddressList)
      {
         DString designation;

         pShareholder->getField (ifds::AcctDesignation, designation, idDataGroup);
         designation.strip();
//saves a view call to 43 - if shareholder is neither intermediary, nor nominee
         if (!designation.empty() && 
            (designation == I_("2") || designation == I_("3")))
         {
            DString accountNum;

            getField (ifds::AccountNum, accountNum, idDataGroup, false);
            pAddressList->setField ( ifds::AccountNum, 
                                     accountNum, 
                                     BF::HOST, 
                                     false);
            pAddressList->refreshDefaultAddress01 (idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::refreshDefaultAddress01 (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(  CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "refreshDefaultAddress01" ) );

   Shareholder *pShareholder = NULL;
   if (getShareholder (pShareholder, idDataGroup) <= WARNING && 
      pShareholder )
   {
      AddressList* pAddressList = NULL;
      if (pShareholder->getAddressList (pAddressList, idDataGroup, 
            true) <= WARNING && 
         pAddressList)
      {
         pAddressList->refreshDefaultAddress01 (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::checkDefaultMailingInfo(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDefaultMailingInfo" ) );

   if( !isNew() )
      return(NO_CONDITION);

   Shareholder *pShareholder = NULL;
   if( getShareholder(pShareholder, idDataGroup)<=WARNING && pShareholder )
   {
      AccountMailingList *pAccountMailingList = NULL;
      if( pShareholder->getAccountMailingList( pAccountMailingList, idDataGroup, false ) <= WARNING && pAccountMailingList )
      {
         DString strKey;
         BFObjIter mailingIter( *pAccountMailingList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
         mailingIter.begin();
         if( !mailingIter.end() )
         {
            AccountMailingInfo* pAccountMailingInfo = 
            dynamic_cast<AccountMailingInfo*>(mailingIter.getObject());
            pAccountMailingInfo->setDefaultValue(idDataGroup);
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void MFAccount::getAcctName(DString &dstrAcctName, const BFDataGroupId& idDataGroup, bool kanji)
{
   ENTITIES_VECTOR acctOwnerEntities;
   dstrAcctName = NULL_STRING;
   if( !isJoint(idDataGroup) )
   {
      DString strAcctNum;
      getField(ifds::AccountNum, strAcctNum, idDataGroup, false);
      if( !strAcctNum.strip().empty() )
         getWorkSession().getFirstSequenced01AccountholderEntityName(idDataGroup, strAcctNum.strip(), dstrAcctName, kanji);
      return;
   }
   //this is a joint account
   getAcctOwnerEntities(acctOwnerEntities, idDataGroup);
   if( !acctOwnerEntities.size() )
      return;
   for( ENTITIES_VECTOR::size_type i = 0; i < acctOwnerEntities.size(); ++i )
   {
      DString dstrEntityId;
      dstrEntityId = acctOwnerEntities[i];

      WorkSessionEntityList *pWorkEntityList = NULL;
      Entity *pEntity = NULL;
      getWorkSession().getWorkSessionEntityList(pWorkEntityList);
      if( pWorkEntityList )
         pWorkEntityList->getEntity( idDataGroup, dstrEntityId, pEntity );
      if( pEntity )
      {
         DString strFirst, strLast;
         pEntity->getField(ifds::FirstName, strFirst, idDataGroup, false);
         pEntity->getField(ifds::LastName, strLast, idDataGroup, false);
         if( !strFirst.strip().empty() || !strLast.strip().empty() )
         {
            dstrAcctName += strFirst;
            dstrAcctName += I_(" ");
            dstrAcctName += strLast;
            dstrAcctName += I_(" & ");
         }
      }
   }
   if( dstrAcctName.length() >= 3 )
      dstrAcctName = dstrAcctName.left(dstrAcctName.length()-3);
}

//******************************************************************************
SEVERITY MFAccount::getHypoRedCriteria( HypoRedCriteria *&pHypoRedCriteria, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getHypoRedCriteria" ) );
   pHypoRedCriteria = dynamic_cast<HypoRedCriteria *>(getObject(HYPO_RED_CRITERIA, idDataGroup ));
   if (!pHypoRedCriteria)
   {
      pHypoRedCriteria = new HypoRedCriteria(*this);
      if (pHypoRedCriteria->init(idDataGroup)<=WARNING)
         setObject(pHypoRedCriteria, HYPO_RED_CRITERIA, OBJ_ACTIVITY_NONE, idDataGroup );
      else
      {
         delete pHypoRedCriteria;
         pHypoRedCriteria = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getAccountCommitment( AccountCommitment *&pAccountCommitment, const BFDataGroupId& idDataGroup, bool createNew)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountCommitment" ) );
   pAccountCommitment = dynamic_cast<AccountCommitment*>(getObject(ACCOUNT_COMMITMENT, idDataGroup ));
   if (!pAccountCommitment && createNew)
   {
      DString dstrAcctNum;
      getField(ifds::AccountNum, dstrAcctNum, idDataGroup, false);
      pAccountCommitment = new AccountCommitment(*this);
      if(!isNew())
      {
         if (pAccountCommitment->init(dstrAcctNum)<=WARNING)
            setObject(pAccountCommitment, ACCOUNT_COMMITMENT, OBJ_ACTIVITY_NONE, idDataGroup );
         else
         {
            delete pAccountCommitment;
            pAccountCommitment = NULL;
         }
      }
      else
      {
         if (pAccountCommitment->initNew(idDataGroup)<=WARNING)
            setObject(pAccountCommitment, ACCOUNT_COMMITMENT, OBJ_ACTIVITY_NONE, idDataGroup );
         else
         {
            delete pAccountCommitment;
            pAccountCommitment = NULL;
         }
      }

   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getAMSFundAllocList(const DString& dstrAMSType, const DString &dstrEffectiveDate, 
                                        AmsFundAllocList* &pAMSFundAllocList, 
                                        const BFDataGroupId& idDataGroup, bool bCreate /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAMSFundAllocList" ) );
/*   pAMSFundAllocList = NULL;

   DString dstrAMSCode (NULL_STRING);
//   DString dstrAMSType; // this logic is to be corrected, this won't work for API or if both RB and RO co-exists

//   getField( ifds::AMSType, dstrAMSType, idDataGroup, false);
   
   if ( dstrAMSType == I_("RB"))
      getField( ifds::AMSCode, dstrAMSCode, idDataGroup, false);
   else if ( dstrAMSType == I_("RO"))
      getField( ifds::AMSROCode, dstrAMSCode, idDataGroup, false);

//   dstrAMSType = ( dstrAMSCode != NULL_STRING )?I_("RB"):I_("RO");
   if ( dstrAMSCode != NULL_STRING )
   {
      pAMSFundAllocList = new AmsFundAllocList( *this );
      pAMSFundAllocList->setField( ifds::AMSCode, dstrAMSCode, BF::HOST, false );
      pAMSFundAllocList->setField( ifds::AMSType, dstrAMSType, BF::HOST, false );
      pAMSFundAllocList->setField( ifds::EffectiveDate, dstrEffectiveDate, BF::HOST, false );
      pAMSFundAllocList->initExisting(I_("N"), NULL_STRING );
   }
*/

// We will return the Global AMS Fund Allocations here.

   if ( isAMSAccount ( idDataGroup ) ) {
      DString dstrAMSCode = NULL_STRING;   
      getField ( ifds::AMSCode, dstrAMSCode, idDataGroup );                 
      if ( dstrAMSCode != NULL_STRING ) {
         AMSMstrList* pAMSMstrList = NULL;
         getAMSMstrList( pAMSMstrList, idDataGroup, dstrEffectiveDate );
         if( pAMSMstrList )  {
            AmsMstrInfo *pAMSMstrInfo = NULL;
            pAMSMstrList->getAMSMstrInfo ( I_("RB"), dstrAMSCode, dstrEffectiveDate, pAMSMstrInfo, idDataGroup );
            if ( pAMSMstrInfo ) {
               pAMSMstrInfo->getAMSFundAllocList ( pAMSFundAllocList, idDataGroup );
            }
         }
      }
/*
      if( pAMSFundAllocList ) {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING ) {
            setObject( pAMSFundAllocList, I_( "AMSFundAllocList" ), OBJ_ACTIVITY_NONE, BF::HOST ); 
         } else {
            delete pAMSFundAllocList;
            pAMSFundAllocList = NULL;
         }
      }*/
   } else {
      //Why are we asking for AMS allocations on non ams account??
      assert(0);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//because AmsFundAllocList is used to default trade allocations, we need the same structure for ams allocations
//as we have for trade : account allocations ---> fund allocations
SEVERITY MFAccount::getAMSAcctAllocList(AbstractAllocList* &pAmsAcctAllocList, const BFDataGroupId& idDataGroup, bool bCreate/*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAMSAcctAllocList" ) );
   pAmsAcctAllocList = dynamic_cast<AbstractAllocList *>(getObject(AMS_ACCT_ALLOC_LIST, idDataGroup ));
   if (!pAmsAcctAllocList)
   {
      //there is no AmsAcctAllocList CBO, so we'll use a TradeAcctAllocList CBO 
      pAmsAcctAllocList = new TradeAcctAllocList(*this);
      DString strAccNum;
      getField(ifds::AccountNum, strAccNum, idDataGroup, false);
      if (pAmsAcctAllocList->initNew(idDataGroup, false)<=WARNING &&
         pAmsAcctAllocList->addNewAllocation(strAccNum.strip().stripLeading('0'), idDataGroup, false, false, false)<=WARNING)
      {
         setObject(pAmsAcctAllocList, AMS_ACCT_ALLOC_LIST, OBJ_ACTIVITY_NONE, idDataGroup );
      }
      else
      {
         delete pAmsAcctAllocList;
         pAmsAcctAllocList = NULL;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getAccountContractList( AccountContractList*& pAccountContractList, 
                                            DString dstrAccountNum, DString dstrFundCode,
                                            DString dstrClassCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountContractList" ) );
   DString dstrKey;
   dstrKey = dstrAccountNum + I_(" ") + dstrFundCode + I_(" ") + dstrClassCode;
   dstrKey.strip();
   pAccountContractList = dynamic_cast<AccountContractList *>(getObject(dstrKey, idDataGroup ));
   if ( !pAccountContractList ) {
      pAccountContractList = new AccountContractList ( *this );
      if ( pAccountContractList->init ( dstrAccountNum, dstrFundCode, dstrClassCode ) <= WARNING ) {
         setObject(pAccountContractList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getAcctCategoryList(AcctCategoryList* &pAcctCategoryList, 
                      const BFDataGroupId& idDataGroup, bool bCreate/*=true*/, bool bRefresh /*=false*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAcctCategoryList" ) );

   pAcctCategoryList = dynamic_cast<AcctCategoryList *>(getObject(ACCT_CATEGORY_LIST, idDataGroup ));
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( (!pAcctCategoryList && bCreate) || bRefresh)
   {
      pAcctCategoryList = new AcctCategoryList( *this );
      DString strCategExist;
      getField(ifds::AcctCategoryExist, strCategExist, idDataGroup, false);

	  if (bRefresh)
	  {
 		pAcctCategoryList->init();
	  }
	  else
	  {
		if(isNew() || strCategExist.strip().upperCase() != YES) //check if the account is new, or if Category exist
		{
			pAcctCategoryList->initNew(idDataGroup);
		}
		else
		{
			pAcctCategoryList->init();
		}
	  }
	  
	  if (!isNew())
	  {
		idWorkingDataGroup = BF::HOST;
	  }

      if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
      {
         setObject( pAcctCategoryList, ACCT_CATEGORY_LIST, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
      }
      else
      {
         delete pAcctCategoryList;
         pAcctCategoryList = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool MFAccount::isCategoryExist( const BFDataGroupId& idDataGroup, const DString& dstrCategoryType )
{
   AcctCategoryList *pAcctCategoryList = NULL;
   BFDataGroupId idWorkingDataGroup = isNew() ? idDataGroup : BF::HOST;

   if (getAcctCategoryList(pAcctCategoryList, idWorkingDataGroup)<=WARNING && pAcctCategoryList)
   {
      DString strCategoryType(dstrCategoryType);
      return pAcctCategoryList->isCategoryExist(idDataGroup, strCategoryType.strip());
   }
   return false;
}

//******************************************************************************
SEVERITY MFAccount::getRegDocumentsList( RegDocumentList *&pRegDocumentList,
                                         const DString &entityId,
                                         const BFDataGroupId &idDataGroup, 
                                         bool bCreate,
										 bool bAcctRegDocListForDeadEntity)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRegDocumentsList"));

   DString dstrKey (NULL_STRING),
      regStandard,
      complyRule;
   Demographics *pDemographics (NULL);
//find the regulatory standard, get this from the demographics object
   if (getDemographicsList (pDemographics, idDataGroup) <= WARNING && 
       pDemographics)
   {
      pDemographics->getField (ifds::RegulatoryStandard, regStandard, idDataGroup);
   }

   if (!entityId.empty())
   {
      WorkSessionEntityList *pWorkEntityList = NULL;
      getWorkSession().getWorkSessionEntityList (pWorkEntityList);
      if (pWorkEntityList)
      {
         Entity *pEntity (NULL);

         pWorkEntityList->getEntity (idDataGroup, entityId, pEntity);
         if (pEntity)
         {
            DString complyRule = !bAcctRegDocListForDeadEntity ? I_("0") : pEntity->getTheRegulatoryStandardComplyRule (idDataGroup);

            regStandard = (complyRule != I_("0") || regStandard.empty ()) ? I_("0") : regStandard;
            getRegDocumentsList(pRegDocumentList, entityId, complyRule, regStandard, idDataGroup, bCreate, bAcctRegDocListForDeadEntity);
	      }
      }
   }
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getRegDocumentsList(RegDocumentList* &pRegDocumentList,
                                        const DString &dstrEntityId,
                                        const DString &dstrComplyRule,
                                        const DString &dstrRegStandard,
                                        const BFDataGroupId &idDataGroup,
                                        bool bCreate,
										bool bAcctRegDocListForDeadEntity)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRegDocumentsList"));
   if (dstrRegStandard != I_("0") || dstrComplyRule != I_("0"))
   {
      DString accountNum, dstrKey;
      getField (ifds::AccountNum, accountNum, idDataGroup);	
      dstrKey =  I_("EntityID=") + dstrEntityId + I_(";");
      dstrKey += I_("RegulatoryStd=") + dstrRegStandard + I_(";");
      dstrKey += I_("ComplyRule=") + dstrComplyRule;
	   pRegDocumentList = dynamic_cast <RegDocumentList *>(getObject (dstrKey, idDataGroup));
      
	   if ((!pRegDocumentList /*|| bAcctRegDocListForDeadEntity*/) && bCreate)
	   {
		   pRegDocumentList = new RegDocumentList (*this);
         if (pRegDocumentList->init ( accountNum , 
                                       dstrEntityId , 
                                       dstrRegStandard, 
                                       dstrComplyRule,                                        
									   idDataGroup, I_("N"), NULL_STRING, bAcctRegDocListForDeadEntity) <= WARNING)
		   {
			   setObject (pRegDocumentList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup); 
		   }
		   else
		   {
			   delete pRegDocumentList;
			   pRegDocumentList = NULL;
		   }
      }
   }
   else if (dstrComplyRule == I_("0") && dstrRegStandard == I_("0"))
   {
       DString accountNum, dstrKey;
       getField (ifds::AccountNum, accountNum, idDataGroup);	
       dstrKey =  I_("EntityID=") + dstrEntityId + I_(";");
       dstrKey += I_("RegulatoryStd=") + dstrRegStandard + I_(";");
       dstrKey += I_("ComplyRule=") + dstrComplyRule;
       pRegDocumentList = dynamic_cast <RegDocumentList *>(getObject (dstrKey, idDataGroup));

       if (!pRegDocumentList)
       {
           Entity *pEntity = NULL;
           SEVERITY serv = NO_CONDITION;
           pRegDocumentList = new RegDocumentList(*this);

           if (getWorkSession().getEntity(idDataGroup, dstrEntityId, pEntity) <= WARNING && pEntity &&
               pEntity->isNew())
           {
               serv = pRegDocumentList->initNew(accountNum, 
                                                dstrEntityId , 
                                                dstrRegStandard, 
                                                dstrComplyRule,                                        
                                                idDataGroup);
           }
           else
           {
               serv = pRegDocumentList->init(accountNum, 
                                             dstrEntityId , 
                                             dstrRegStandard, 
                                             dstrComplyRule,                                        
									         idDataGroup, I_("N"), NULL_STRING, bAcctRegDocListForDeadEntity);
           }

           if (serv <= WARNING && pRegDocumentList)
           {
               setObject(pRegDocumentList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup); 
           }
           else
           {
               delete pRegDocumentList;
               pRegDocumentList = NULL;
           }
       }
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************

SEVERITY MFAccount::removeRegDocumentList(const DString& dstrEntityId,
                                 const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("removeRegDocumentList"));
    Entity *pEntity;
    Demographics *pDemographics (NULL);
    DString regStandard;
    getWorkSession().getEntity (idDataGroup, dstrEntityId, pEntity);
    bool flag = pEntity->isNew();
    DString complyRule = pEntity->getTheRegulatoryStandardComplyRule (idDataGroup);

    if(pEntity && pEntity->isNew() && I_("0") == complyRule )
    {
          
        if (getDemographicsList (pDemographics, idDataGroup, false) <= WARNING && pDemographics)
        {
            pDemographics->getField (ifds::RegulatoryStandard, regStandard, idDataGroup);
            BFObjIter iterMFAccount(*this, idDataGroup ); 
            DString accountNum, dstrKey;
            getField (ifds::AccountNum, accountNum, idDataGroup);  
            dstrKey =  I_("EntityID=") + dstrEntityId + I_(";");
            dstrKey += I_("RegulatoryStd=") + regStandard + I_(";");
            dstrKey += I_("ComplyRule=") + complyRule;

            iterMFAccount.positionByKey (dstrKey);
            if( !iterMFAccount.end() )
            {
                 iterMFAccount.removeObjectFromMap(true, true);
            }
        } 
    }
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::canContributeProtectedFund ( const DString fundCode,
                                                 const DString classCode, 
                                                 const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canContributeProtectedFund" ) );
   SEVERITY sevRtn = NO_CONDITION;
   DString dstrFundCode ( fundCode ), dstrClassCode ( classCode );

   ProtectedFundList *pProtectedFundList;
   pProtectedFundList = NULL;
   getWorkSession().getProtectedFundList( pProtectedFundList );

   if ( !pProtectedFundList ) 
      return ( sevRtn );

   bool bProtectedFund = pProtectedFundList->isProtectedFund ( dstrFundCode, dstrClassCode, idDataGroup);

   if ( !bProtectedFund )
      return ( sevRtn );


   DString dstrAccHldDofB;

   getDofBirthofOwnerSeq01( dstrAccHldDofB, idDataGroup );

   if ( dstrAccHldDofB.strip() == NULL_STRING )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ACCTHOLDER_DOFBIRTH_MISSING );
   }
   else // must be less than 80 years old
   {
   
      DString strCurrentDate;
      getWorkSession().getOption( ifds::CurrSysDate, strCurrentDate, idDataGroup, false );

      int maxAge = 80, iAge;

      //calculate age
      DString strAge, strMonth;
      // return true means bad date
      if( DSTCommonFunctions::BuildAge( dstrAccHldDofB, strCurrentDate, strAge, strMonth ) )
      {
         strAge = NULL_STRING;
      }

      iAge = convertToULong( strAge );

      if( iAge >= maxAge )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCTHOLDER_OVER_AGE_FOR_PROTECTED_FUND);
      }

   }

   // if benefical owner is blank then give error 
   DString dstrBeneficalOwner;
   getField ( ifds::BeneficialOwner, dstrBeneficalOwner, idDataGroup);
   
   if ( dstrBeneficalOwner.strip() == NULL_STRING )
   {
      DString dstrAcctDesignation;
      getField ( ifds::AcctDesignation, dstrAcctDesignation, idDataGroup);
      if (( dstrAcctDesignation == NOMINEE ) || ( dstrAcctDesignation == THIRD_PARTY )) {
         ADDCONDITIONFROMFILE( CND::ERR_BENEFICAL_OWNER_NAME_FOR_PROTECTED_FUND);
      }
   }

   // if account owner missing SIN, issue error message
   DString dstrSIN (NULL_STRING);

   getSINAcctOwnerSeq01 ( dstrSIN, idDataGroup );
   
   if( dstrSIN.strip() == NULL_STRING )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ACCTOWNER_SIN_MISSING );
   }


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getSINAcctOwnerSeq01( DString& dstrSIN, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSINAcctOwnerSeq01" ) );

   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );

   if( pAccountEntityXref != NULL )
   {
      DString dstrEntityId ( I_("-1"));
      GetEntityIdForAcctOwnerSeq1( idDataGroup, dstrEntityId );
      dstrEntityId.stripLeading( '0' );

      if( dstrEntityId != I_("-1") )
      {
         Entity *pEntity;
         dstrEntityId.stripLeading( '0' );

         if( dstrEntityId != NULL_STRING )
         {
            getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
            if( pEntity )
            {
               pEntity->getField( ifds::SIN, dstrSIN, idDataGroup, false );
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
// This method will set/unset the default values for WRAP Account.
// When the bSetDefault paramter is true, the field MgmtFeePayOption is set to 
// 3, which is broker (default).  The field AMSROCode is set only when the 
// system option ClientAMSType is RO.  The value set for AMSROCode depends on the
// system level setup.  When the bSetDefault parameter is false, the MgmtFeePayOption
// field is reset to 0 (N/A) and the AMSROCode is set to NULL_STRING when the
// system option ClinetAMSType is RO.
// @param   bool bSetDefault - True, set the fields to defaults for WRAP account.
//                             false, undo the defaults for WRAP account.
//          const BFDataGroupId& idDataGroup - current data group id.
//******************************************************************************
void MFAccount::setWRAPAcctDefaults ( bool bSetDefault, const BFDataGroupId& idDataGroup ) 
{
   DString dstrAMSType;
   if ( bSetDefault ) {  
      DString dstrDefaultValue;
      getWorkSession().getMgmtCoOptions()->getField(ifds::ProfileCodeDflt, dstrDefaultValue, idDataGroup, false);
      setField( ifds::AMSROCode, dstrDefaultValue, idDataGroup );
      getWorkSession().getMgmtCoOptions()->getField(ifds::MgmtFeePayOptDflt, dstrDefaultValue, idDataGroup, false);
      setField ( ifds::MgmtFeePayOption, dstrDefaultValue, idDataGroup );
     // setFieldNoValidate ( ifds::MgmtFeePayOption, I_("3"), idDataGroup );
      /*
      //If the account is ro then set amsrocode to default from generic control
      getWorkSession().getMgmtCoOptions()->getField(ifds::ClientAMSType, dstrAMSType, idDataGroup, false);
      if ( dstrAMSType == I_("RO") ) {
         DString dstrDefaultValue;
         //getWorkSession().getMgmtCoOptions()->getField(ifds::ClientAMSType, dstrDefaultValue, idDataGroup, false);
         setFieldNoValidate ( ifds::AMSROCode, dstrDefaultValue, idDataGroup );
      } */     
   } else {
      setFieldNoValidate ( ifds::MgmtFeePayOption, I_("0"), idDataGroup );      
      //If the account is RO then set the amsrocode field to NULL_STRING
  //    getWorkSession().getMgmtCoOptions()->getField(ifds::ClientAMSType, dstrAMSType, idDataGroup, false);
  //    if ( dstrAMSType == I_("RO") ) {
         setFieldNoValidate ( ifds::AMSROCode, NULL_STRING, idDataGroup );
      }
      
 //  }
}

//*************************************************************************************************
void MFAccount::setAlertViewedFlag(const bool bFlag)
{
    _alertViewed = bFlag;
}

//*************************************************************************************************
bool MFAccount::getAlertViewedFlag()
{
    return _alertViewed;
}

//*************************************************************************************************
SEVERITY MFAccount::validateMgmtFeePayOption( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMgmtFeePayOption" ) );

   DString dstrMgmtFeePayOption;
   getField( ifds::MgmtFeePayOption, dstrMgmtFeePayOption, idDataGroup, false );
   if( dstrMgmtFeePayOption == I_("4") )  // 4 - Waived
   {
      DString dstrAccountNum;
      getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );
      dstrAccountNum.stripAll( I_(' ') );
      dstrAccountNum.padLeft( 10, I_('0') );
      DString dstrSummitAccountsLowerBound, dstrSummitAccountsUpperBound;
      getWorkSession().getOption( ifds::SummitAccountsLowerBound, dstrSummitAccountsLowerBound, idDataGroup );
      getWorkSession().getOption( ifds::SummitAccountsUpperBound, dstrSummitAccountsUpperBound, idDataGroup );
      // get values from fields, stripall spaces
      dstrSummitAccountsLowerBound.stripAll( I_(' ') );
      dstrSummitAccountsUpperBound.stripAll( I_(' ') );
      
      // Parse
      bool bInRange = false;
      int iPos1 = 0, iPos2 = 0;
      DString dstrUpper, dstrLower;
      while ( !bInRange && dstrSummitAccountsLowerBound.length() )
      {
         iPos1 = dstrSummitAccountsLowerBound.find( I_CHAR(',') );
         iPos2 = dstrSummitAccountsUpperBound.find( I_CHAR(',') );
         if (iPos1 != -1 && iPos2 != -1) 
         {        
            dstrLower = dstrSummitAccountsLowerBound.substr( 0, iPos1 );
            dstrUpper = dstrSummitAccountsUpperBound.substr( 0, iPos2 );
            dstrSummitAccountsLowerBound = dstrSummitAccountsLowerBound.substr( iPos1+1 );
            dstrSummitAccountsUpperBound = dstrSummitAccountsUpperBound.substr( iPos2+1 );
         }
         else
         {
            dstrLower = dstrSummitAccountsLowerBound;
            dstrUpper = dstrSummitAccountsUpperBound;
            dstrSummitAccountsLowerBound = NULL_STRING;
            dstrSummitAccountsUpperBound = NULL_STRING;
         }

         dstrLower.padLeft( 10, I_('0') );
         dstrUpper.padLeft( 10, I_('0') );

         // Check
         if( dstrLower.stricmp( dstrAccountNum ) > 0 ) break;
         if( ( dstrAccountNum.stricmp( dstrLower ) >= 0 ) && ( dstrAccountNum.stricmp( dstrUpper ) <= 0 ) )
         {
            bInRange = true;
         }
      }

      // Report
      if( !bInRange )
      {
         // Error; at the moment set Error and Warning to the same value since there's no Warning case.
         getErrMsg( I_("359"), CND::ERR_ACCT_INELIGIBILE_PAY_OPTION_WAIVED, CND::ERR_ACCT_INELIGIBILE_PAY_OPTION_WAIVED, idDataGroup, NULL_STRING );
      }
   }
   return( GETCURRENTHIGHESTSEVERITY() );
}

//*************************************************************************************************
SEVERITY MFAccount::validateBusinessNo( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMgmtFeePayOption" ) );

   DString strErrValue;
   bool	validate_businessNo = true;

   if( _pErrMsgRulesList == NULL )
   {
      SEVERITY sevRtn = getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }
   if( _pErrMsgRulesList )
   {
      _pErrMsgRulesList->getEWIValue(I_("370"), idDataGroup, strErrValue );

      if( !(strErrValue.upperCase() == I_("E") || strErrValue.upperCase() == I_("W") ))
      {
         return( GETCURRENTHIGHESTSEVERITY() );
      }
   }

   DString dstrBusinessNo;
   getField( ifds::BusinessNo, dstrBusinessNo, idDataGroup, false );


   dstrBusinessNo.stripAll('-');
   dstrBusinessNo.stripAll(' ');
   
   DString charactors = dstrBusinessNo.left(11);
   charactors = charactors.right(2);
   const I_CHAR * tmpchar = charactors.c_str();
   for( int i=0 ; i< 2; i++ )
   {
	   I_CHAR c1 = tmpchar[i];	   
	   if( !( c1>= I_('a') && c1 <= I_('z') ) && !( c1>= I_('A') && c1 <= I_('Z') ) ) 
	   {
		   validate_businessNo = false;
		   break;
	   }

   }
   
   DString digitval = dstrBusinessNo.right(4);
   if( dstrBusinessNo.length() != 15 || !digitval.isAllDigits() ) 
   {
		validate_businessNo = false;
   }

   if( validate_businessNo )
   {
	   DString dstrValidSIN, dstrSIN;
	   DString IdValueCopy;
	   IdValueCopy = dstrBusinessNo.left(9);

	   bool bSINOkay;

	   getWorkSession().getOption( ifds::SinException, dstrValidSIN, idDataGroup, false );
	   dstrValidSIN = I_( "," ) + dstrValidSIN + I_( "," );
	   dstrSIN = I_( "," ) + IdValueCopy.strip() + I_( "," );

	   bSINOkay = (dstrValidSIN.find(dstrSIN) != DString::npos);

	   if( !bSINOkay )
	   {
		  if( IdValueCopy.isAllDigits() )
		  {
			 if( IdValueCopy.length() == 9 )
			 {
				int even1, even2, even3, even4;
				int odd1 , odd2 , odd3 , odd4;

				DString strEven, strOdd;

				strEven = IdValueCopy.substr( 1, 1 );
				even1   = strEven.asInteger() * 2;
				strEven = IdValueCopy.substr( 3, 1 );
				even2   = strEven.asInteger() * 2;
				strEven = IdValueCopy.substr( 5, 1 );
				even3   = strEven.asInteger() * 2;
				strEven = IdValueCopy.substr( 7, 1 );
				even4   = strEven.asInteger() * 2;

				strOdd = IdValueCopy.substr( 0, 1 );
				odd1   = strOdd.asInteger();
				strOdd = IdValueCopy.substr( 2, 1 );
				odd2   = strOdd.asInteger();
				strOdd = IdValueCopy.substr( 4, 1 );
				odd3   = strOdd.asInteger();
				strOdd = IdValueCopy.substr( 6, 1 );
				odd4   = strOdd.asInteger();

				if( even1 > 9 )
				{
				   even1 = even1 - 9;
				}
				if( even2 > 9 )
				{
				   even2 = even2 - 9;
				}
				if( even3 > 9 )
				{
				   even3 = even3 - 9;
				}
				if( even4 > 9 )
				{
				   even4 = even4 - 9;
				}

				even1 = even1 + even2 + even3 + even4;
				odd1  = odd1  + odd2  + odd3  + odd4;

				even1 = even1 + odd1;

				even1 = even1 % 10;

				if( even1 == 0 )
				   even1 = 0;
				else
				   even1 = 10 - even1;

				if( even1 != (IdValueCopy.asInteger()) % 10 )
				{
					validate_businessNo = false;
				}
			 }
			 else
			 {
				validate_businessNo = false;
			 }
		  }
		  else
		  {
			validate_businessNo = false;
		  }
	   }
   }

   if( !validate_businessNo )
   {
	   if( strErrValue.upperCase() == I_("E") )
		{
			ADDCONDITIONFROMFILE( CND::ERR_INVALID_BUSINESSNO );
		}
		else if( strErrValue.upperCase() == I_("W") )
		{
			ADDCONDITIONFROMFILE( CND::WARN_INVALID_BUSINESSNO );
		}
   }

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
bool MFAccount::isRRIFAccount(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRRIFAccount"));

   DString dstrTaxType;

   getField(ifds::TaxType, dstrTaxType, idDataGroup, false);
   return getWorkSession ().isLIFLike (dstrTaxType) || dstrTaxType == LRIF_TAX_TYPE ||
          dstrTaxType == RRIF_TAX_TYPE || dstrTaxType == PRIF_TAX_TYPE;
}
//******************************************************************************

SEVERITY MFAccount::getAMSMstrList( AMSMstrList*& pAMSMstrList, const BFDataGroupId& idDataGroup,
                                    const DString& dstrInquryDate)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAMSMstrList"));
   DString dstrKey = I_( "AMSMstrList" ) + dstrInquryDate;

   pAMSMstrList = dynamic_cast<AMSMstrList*>(BFCBO::getObject( dstrKey, idDataGroup ) );
   if( !pAMSMstrList )
   {
      pAMSMstrList =  new AMSMstrList( *this );
      setObject( pAMSMstrList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup ); 
   }

   return( GETCURRENTHIGHESTSEVERITY() );
}
//********************************************************************************
SEVERITY MFAccount::validatePendingTradesForAMSEligibleFunds( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "validatePendingTradesForAMSEligibleFunds( BFDataGroupId & )" ) );
   
	bool blRaiseErr = false;

	if( getFundDetailList() && NULL != _pFundDetailList )
	{
		PendingTradeList *pPendingTradeList = NULL;	
		if ( getPendingTradesList( pPendingTradeList, idDataGroup, FULL_LIST ) <= WARNING &&
			  NULL != pPendingTradeList )
		{
			BFObjIter iterPendingTradesList( *pPendingTradeList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
			iterPendingTradesList.begin();

			while( !iterPendingTradesList.end() )
			{                  
				PendingTradeDetails *pPendingTradeDetails = static_cast<PendingTradeDetails*>(iterPendingTradesList.getObject());	
				if ( NULL != pPendingTradeDetails )
				{
					DString dstrGoodBad;
					pPendingTradeDetails->getField( ifds::GoodBad, dstrGoodBad, idDataGroup );					

					if ( I_( "Y" ) == dstrGoodBad.strip().upperCase() )
					{
						DString dstrPendingTradeDetailKey = iterPendingTradesList.getStringKey();								
						pPendingTradeList->getItem( dstrPendingTradeDetailKey, idDataGroup );				

						DString dstrTransType;
						pPendingTradeDetails->getField( ifds::TransType, dstrTransType, idDataGroup );
						dstrTransType.strip().upperCase();
						
						// In any of the cases below, get the fund detail based on fund/class code and
						// check if the fund is AMS eligible (AMSFund = Y).
						// If Yes, then set blRaiseErr to True and break;

						// if not Transfer/Exchange/All Funds Transfer, then check From Fund(s) and if any of it is AMS Fund
						if ( I_( "TR" )   != dstrTransType &&
							  I_( "XR" )   != dstrTransType &&
							  I_( "AFTR" ) != dstrTransType )						
						{																													
							DString dstrAllocationExists;
							pPendingTradeDetails->getField (ifds::Allocation, dstrAllocationExists, idDataGroup, false );					
							if ( I_( "Y" ) == dstrAllocationExists.strip().upperCase() )
							{
								DString dstrAccountNum;
								getField( ifds::AccountNum, dstrAccountNum, idDataGroup );

								TradeAcctAllocList *pTradeAcctAllocList = NULL;
								if ( pPendingTradeDetails->getAccountAllocationList( pTradeAcctAllocList, 
																									  idDataGroup, 
																									  dstrAccountNum ) <= WARNING &&
									  NULL != pTradeAcctAllocList )
								{
									BFObjIter iterTradeAcctAllocList( *pTradeAcctAllocList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
									iterTradeAcctAllocList.begin();

									while( !iterTradeAcctAllocList.end() )
									{         
										TradeAcctAlloc *pTradeAcctAlloc = dynamic_cast<TradeAcctAlloc*>( iterTradeAcctAllocList.getObject( ) );						
										if ( NULL != pTradeAcctAlloc )
										{
											TradeFundAllocList *pTradeFundAllocList = NULL;
											if ( pTradeAcctAlloc->getFundAllocationList( pTradeFundAllocList,idDataGroup ) <= WARNING &&
												  NULL != pTradeFundAllocList )
											{
												BFObjIter iterTradeFundAllocList( *pTradeFundAllocList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
												iterTradeFundAllocList.begin();	 
												while( !iterTradeFundAllocList.end() )
												{													
													TradeFundAlloc *pTradeFundAlloc = dynamic_cast<TradeFundAlloc*>( iterTradeFundAllocList.getObject( ) );																																
													if ( NULL != pTradeFundAlloc )
													{
														DString dstrFund, dstrClass;
														pTradeFundAlloc->getField( ifds::FundCode,  dstrFund,  idDataGroup );
														pTradeFundAlloc->getField( ifds::ClassCode, dstrClass, idDataGroup );
																				
														FundDetail *pFundDetail = NULL;
														if ( _pFundDetailList->getFundDetail( dstrFund, 
																										  dstrClass, 
																										  idDataGroup, 
																										  pFundDetail ) &&
															  NULL != pFundDetail )
														{
															DString dstrAMSFund;
															pFundDetail->getField( ifds::AMSEligible, dstrAMSFund, idDataGroup );

															if ( I_( "Y" ) == dstrAMSFund.strip().upperCase() )
															{
																blRaiseErr = true;
																break;
															}
														}	
													}

													++iterTradeFundAllocList;
												}
											}
										}							
										++iterTradeAcctAllocList;
									}
								}					
							}
							else
							{
								DString dstrFund, dstrClass;
								pPendingTradeDetails->getField( ifds::rxFundCode,  dstrFund, idDataGroup );
								pPendingTradeDetails->getField( ifds::rxClassCode, dstrClass, idDataGroup );
								FundDetail *pFundDetail = NULL;
								if ( _pFundDetailList->getFundDetail( dstrFund, 
																				  dstrClass, 
																				  idDataGroup, 
																				  pFundDetail ) &&
									  NULL != pFundDetail )
								{
									DString dstrAMSFund;
									pFundDetail->getField( ifds::AMSEligible, dstrAMSFund, idDataGroup );

									if ( I_( "Y" ) == dstrAMSFund.strip().upperCase() )
									{
										blRaiseErr = true;
										break;
									}
								}									
							}
						}
						// If Transfer or Exchange, then get the From allcoation list
						else if ( I_( "TR" )   == dstrTransType ||
							       I_( "XR" ) == dstrTransType )
						{													
							TradeFromFundAllocList *pTradeFromFundAllocList = NULL;
							if ( pPendingTradeDetails->getFromFundAllocationList( pTradeFromFundAllocList, 
								                                                   idDataGroup )<= WARNING &&
								  NULL != pTradeFromFundAllocList )
							{
								BFObjIter iterTradeFromFundAllocList( *pTradeFromFundAllocList, 
									                                   idDataGroup, 
																				  true, 
																				  BFObjIter::ITERTYPE::NON_DELETED );
								iterTradeFromFundAllocList.begin();
								while( !iterTradeFromFundAllocList.end() )
								{         
									BFAbstractCBO *pTradeFromFundAlloc = dynamic_cast<BFAbstractCBO*>( iterTradeFromFundAllocList.getObject( ) );						
									if ( NULL != pTradeFromFundAlloc )
									{
										DString dstrFund, dstrClass;
										pTradeFromFundAlloc->getField( ifds::FundCode,  dstrFund,  idDataGroup );
										pTradeFromFundAlloc->getField( ifds::ClassCode, dstrClass, idDataGroup );
											
										FundDetail *pFundDetail = NULL;
										if ( _pFundDetailList->getFundDetail( dstrFund, 
																						  dstrClass, 
																						  idDataGroup, 
																						  pFundDetail ) &&
											  NULL != pFundDetail )
										{
											DString dstrAMSFund;
											pFundDetail->getField( ifds::AMSEligible, dstrAMSFund, idDataGroup );

											if ( I_( "Y" ) == dstrAMSFund.strip().upperCase() )
											{
												blRaiseErr = true;
												break;
											}
										}									
									}							
									++iterTradeFromFundAllocList;
								}
							}
							else   // If no From allocation list is available, then just get from fund and class
							{
								DString dstrFund, dstrClass;
								pPendingTradeDetails->getField( ifds::rxFundCode,  dstrFund, idDataGroup );
								pPendingTradeDetails->getField( ifds::rxClassCode, dstrClass, idDataGroup );
								FundDetail *pFundDetail = NULL;
								if ( _pFundDetailList->getFundDetail( dstrFund, 
																				  dstrClass, 
																				  idDataGroup, 
																				  pFundDetail ) &&
									  NULL != pFundDetail )
								{
									DString dstrAMSFund;
									pFundDetail->getField( ifds::AMSEligible, dstrAMSFund, idDataGroup );

									if ( I_( "Y" ) == dstrAMSFund.strip().upperCase() )
									{
										blRaiseErr = true;
										break;
									}
								}							
							}
								
							// If we are still in, check the To side of the Exchange
							DString dstrAllocationExists;
							pPendingTradeDetails->getField ( ifds::Allocation, dstrAllocationExists, idDataGroup, false );					
							if ( I_( "XR" ) == dstrTransType &&
								  I_( "Y" )  == dstrAllocationExists )
							{	
								DString dstrAccountNum;
								getField( ifds::AccountNum, dstrAccountNum, idDataGroup );

								TradeAcctAllocList *pTradeAcctAllocList = NULL;
								if ( pPendingTradeDetails->getAccountAllocationList( pTradeAcctAllocList, 
																									  idDataGroup, 
																									  dstrAccountNum ) <= WARNING &&
									  NULL != pTradeAcctAllocList )
								{
									BFObjIter iterTradeAcctAllocList( *pTradeAcctAllocList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
									iterTradeAcctAllocList.begin();

									while( !iterTradeAcctAllocList.end() )
									{         
										BFAbstractCBO *pTradeAcctAlloc = dynamic_cast<BFAbstractCBO*>( iterTradeAcctAllocList.getObject( ) );						
										if ( NULL != pTradeAcctAlloc )
										{
											DString dstrFund, dstrClass;
											pTradeAcctAlloc->getField( ifds::FundCode,  dstrFund,  idDataGroup );
											pTradeAcctAlloc->getField( ifds::ClassCode, dstrClass, idDataGroup );
											
											FundDetail *pFundDetail = NULL;
											if ( _pFundDetailList->getFundDetail( dstrFund, 
																							  dstrClass, 
																							  idDataGroup, 
																							  pFundDetail ) &&
												  NULL != pFundDetail )
											{
												DString dstrAMSFund;
												pFundDetail->getField( ifds::AMSEligible, dstrAMSFund, idDataGroup );

												if ( I_( "Y" ) == dstrAMSFund.strip().upperCase() )
												{
													blRaiseErr = true;
													break;
												}
											}									
										}							
										++iterTradeAcctAllocList;
									}
								}					
							}
							else if ( I_( "XR" ) == dstrTransType &&
										 I_( "N" )  == dstrAllocationExists )
							{	
								DString dstrFundTo, dstrClassTo;
								pPendingTradeDetails->getField( ifds::FundTo,      dstrFundTo,  idDataGroup );
								pPendingTradeDetails->getField( ifds::ClassToCode, dstrClassTo, idDataGroup );
								FundDetail *pFundDetail = NULL;
								if ( _pFundDetailList->getFundDetail( dstrFundTo, 
																				  dstrClassTo, 
																				  idDataGroup, 
																				  pFundDetail ) &&
									  NULL != pFundDetail )
								{
									DString dstrAMSFund;
									pFundDetail->getField( ifds::AMSEligible, dstrAMSFund, idDataGroup );

									if ( I_( "Y" ) == dstrAMSFund.strip().upperCase() )
									{
										blRaiseErr = true;
										break;
									}
								}							
							}
						}
						else  if ( I_( "AFTR" ) == dstrTransType )// If All Funds Transfer
						{
							// go through the Account Holdings list
							MFAccountHoldingList *pMFAccountHoldingList = NULL;
							if ( getAccountHoldingList( pMFAccountHoldingList, 
																 idDataGroup, 
																 true ) <= WARNING &&  //inquire the database based on 
																												  // CurrBusDate   
								  NULL != pMFAccountHoldingList )
							{
								BFObjIter iterMFAccountHoldingList( *pMFAccountHoldingList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
								iterMFAccountHoldingList.begin();
								while ( !iterMFAccountHoldingList.end () ) 
								{
									BFAbstractCBO *pMFAccountHolding = iterMFAccountHoldingList.getObject();
									if ( NULL != pMFAccountHolding )
									{										
										DString dstrFund, dstrClass;
										pMFAccountHolding->getField( ifds::rxFundCode,  dstrFund,  idDataGroup );
										pMFAccountHolding->getField( ifds::rxClassCode, dstrClass, idDataGroup );

										FundDetail *pFundDetail = NULL;
										if ( _pFundDetailList->getFundDetail( dstrFund, 
																						  dstrClass, 
																						  idDataGroup, 
																						  pFundDetail ) &&

											  NULL != pFundDetail )
										{
											DString dstrAMSFund;
											pFundDetail->getField( ifds::AMSEligible, dstrAMSFund, idDataGroup );

											if ( I_( "Y" ) == dstrAMSFund.strip().upperCase() )
											{
												blRaiseErr = true;
												break;
											}
										}
									}

									++iterMFAccountHoldingList;
								}
							}
						}
					}
				}

				++iterPendingTradesList; 
			}
		}
	}

	if ( blRaiseErr )
	{
		ErrMsgRulesList *pErrMsgRulesList = NULL;
		if ( getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
			  NULL != pErrMsgRulesList )
		{
			DString dstrErrValue;
			pErrMsgRulesList->getEWIValue( I_( "405" ), idDataGroup, dstrErrValue );
			
			dstrErrValue.strip().upperCase();
			if ( dstrErrValue == I_("E") )
			{
				// Accounts with pending trades are not eligible for AMS rebalancing.
				ADDCONDITIONFROMFILE( CND::ERR_PENDING_TRADES_WITH_AMS );				
			}
			else if (dstrErrValue == I_("W") )
			{
				// Accounts with pending trades are not eligible for AMS rebalancing.
				ADDCONDITIONFROMFILE( CND::WARN_PENDING_TRADES_WITH_AMS );
			}
		}
	}

   return( GETCURRENTHIGHESTSEVERITY() );
}


//********************************************************************************
SEVERITY MFAccount::validateUnsettledUnitsForAMSEligibleFunds( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "validateUnsettledUnitsForAMSEligibleFunds( BFDataGroupId & )" ) );

   bool blRaiseErr = false;

   MFAccountHoldingList *pMFAccountHoldingList = NULL;
   if ( getAccountHoldingList( pMFAccountHoldingList, 
                               idDataGroup, 
                               true ) <= WARNING &&  //inquire the database based on 
                                                     // CurrBusDate   
        NULL != pMFAccountHoldingList )
   {
      BFObjIter iterMFAccountHoldingList( *pMFAccountHoldingList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
      iterMFAccountHoldingList.begin();
      while ( !iterMFAccountHoldingList.end () ) 
      {
         BFAbstractCBO *pMFAccountHolding = iterMFAccountHoldingList.getObject();
         if ( NULL != pMFAccountHolding )
         {
            DString dstrUnsettledUnits;
            pMFAccountHolding->getField ( ifds::UnsettledUnits, dstrUnsettledUnits, idDataGroup );
            double dblUnsettledUnits = DSTCommonFunctions::convertToDouble( dstrUnsettledUnits );												

            if ( 0 != dblUnsettledUnits )
            {
               DString dstrFund, dstrClass;
               pMFAccountHolding->getField( ifds::rxFundCode,  dstrFund,  idDataGroup );
               pMFAccountHolding->getField( ifds::rxClassCode, dstrClass, idDataGroup );

               if (getWorkSession().isAMSFundClass(dstrFund, dstrClass, idDataGroup))
               {
                   blRaiseErr = true;
                   break;
               }
            }
         }

         ++iterMFAccountHoldingList;
      }			
   }

   if ( blRaiseErr )
   {
      ErrMsgRulesList *pErrMsgRulesList = NULL;
      if ( getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
         NULL != pErrMsgRulesList )
      {
         DString dstrErrValue;
         pErrMsgRulesList->getEWIValue( I_( "406" ), idDataGroup, dstrErrValue );

         dstrErrValue.strip().upperCase();
         if ( dstrErrValue == I_("E") )
         {
            // Accounts with unsettled trades are not eligible for AMS rebalancing
            ADDCONDITIONFROMFILE( CND::ERR_UNSETTLED_TRADES_WITH_AMS );				
         }
         else if (dstrErrValue == I_("W") )
         {
            // Accounts with unsettled trades are not eligible for AMS rebalancing
            ADDCONDITIONFROMFILE( CND::WARN_UNSETTLED_TRADES_WITH_AMS );
         }			
      }
   }

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
bool MFAccount::isAMSAccount ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAMSAccount"));
   DString dstrActiveAMSExists;
   getField ( ifds::ActiveAMSExists, dstrActiveAMSExists, idDataGroup );
   return ( dstrActiveAMSExists.strip() == YES );
}

//******************************************************************************
SEVERITY MFAccount::canPAC( const DString& dstrDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("canPAC"));   
   bool bFundOverride;
   DString dstrAmount;
   checkAMSRestriction( dstrDate, CAN_PAC, idDataGroup, bFundOverride, dstrAmount, true );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY MFAccount::canSWP( const DString& dstrDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("canSWP"));
   bool bFundOverride;
   DString dstrAmount;
   checkAMSRestriction( dstrDate, CAN_SWP, idDataGroup, bFundOverride, dstrAmount);
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY MFAccount::minPAC( const DString& dstrDate, const DString& dstrAmount, bool& bFundOverride, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("minPAC"));
   checkAMSRestriction( dstrDate, MIN_PAC, idDataGroup, bFundOverride, dstrAmount );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY MFAccount::minSWP( const DString& dstrDate, const DString& dstrAmount, bool& bFundOverride, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("minSWP"));
   checkAMSRestriction( dstrDate, MIN_SWP, idDataGroup, bFundOverride, dstrAmount);
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY MFAccount::canATIn( const DString& dstrDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("canATIn"));   
   bool bFundOverride;
   DString dstrAmount;
   checkAMSRestriction( dstrDate, CAN_AT_IN, idDataGroup, bFundOverride, dstrAmount, true );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY MFAccount::canATOut( const DString& dstrDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("canATOut"));
   bool bFundOverride;
   DString dstrAmount;
   checkAMSRestriction( dstrDate, CAN_AT_OUT, idDataGroup, bFundOverride, dstrAmount );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY MFAccount::checkAMSRestriction( const DString& dstrDate, const DString& dstrTransType, const BFDataGroupId& idDataGroup, bool& bFundOverride, const DString& dstrAmount,bool bCheckGrandFather  )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("canATOut"));
   if ( isAMSAccount ( idDataGroup ) ) {
      DString dstrAMSCode = NULL_STRING;   
      getField ( ifds::AMSCode, dstrAMSCode, idDataGroup );           
      // AMS Code is defined, there we will assume it is an AMS Account.
      if ( dstrAMSCode != NULL_STRING ) {
         AMSMstrList* pAMSMstrList = NULL;
         getAMSMstrList( pAMSMstrList, idDataGroup, dstrDate );
         if( pAMSMstrList )  {
            AmsMstrInfo *pAMSMstrInfo = NULL;
            pAMSMstrList->getAMSMstrInfo ( I_("RB"), dstrAMSCode, dstrDate, pAMSMstrInfo, idDataGroup );
            if ( pAMSMstrInfo ) {
               DString dstrTaxType,dstrTaxJuris, dstrProvResid, dstrAccountType, dstrAcctDesign;               
               Shareholder *pShareholder;
               if( getShareholder( pShareholder, idDataGroup ) <= WARNING ) {
                  pShareholder->getField ( ifds::TaxJurisCode, dstrTaxJuris, idDataGroup ); //Shareholder
                  pShareholder->getField ( ifds::ResProvCode, dstrProvResid, idDataGroup ); //Shareholder
               } else {
               // There should be a shareholder cbo always
                  assert ( 0 );
               }
               getField ( ifds::AcctDesignation, dstrAcctDesign, idDataGroup );
               getField ( ifds::AcctType, dstrAccountType, idDataGroup );
               getField ( ifds::TaxType, dstrTaxType, idDataGroup );    
               SEVERITY sevGrandFatheredDate = NO_CONDITION;
               if ( bCheckGrandFather ) {
                  bool bAMSMixOverride = false;
                  DString dstrDefAllocOverride, dstrAccountBalance;
                  double dAccountBalance = 0.0;
                  getField ( ifds::AccountBalance, dstrAccountBalance, idDataGroup );
                  dAccountBalance = DSTCommonFunctions::convertToDouble( dstrAccountBalance );                              
                  getWorkSession().getOption( ifds::DefaultAllocOverride, dstrDefAllocOverride, idDataGroup, false); 
                  if ( dstrDefAllocOverride == YES)  {
                     bAMSMixOverride = getWorkSession().hasUpdatePermission( UAF::AMS_MIX_OVERRIDE );
                  }               

                  if ( dAccountBalance <= 0 ) {
                     sevGrandFatheredDate = pAMSMstrInfo->checkGrandfatheredDate ( dstrDate, idDataGroup, !bAMSMixOverride );
                  } 
               }
               if ( sevGrandFatheredDate <= WARNING ) {
                  if ( dstrTransType == CAN_PAC )
                     pAMSMstrInfo->canPAC ( dstrTaxJuris, dstrProvResid, dstrAccountType, dstrTaxType, dstrAcctDesign, idDataGroup );
                  else if ( dstrTransType == CAN_SWP )
                     pAMSMstrInfo->canSWP ( dstrTaxJuris, dstrProvResid, dstrAccountType, dstrTaxType, dstrAcctDesign, idDataGroup );
                  else if ( dstrTransType == CAN_AT_IN )
                     pAMSMstrInfo->canATIn ( dstrTaxJuris, dstrProvResid, dstrAccountType, dstrTaxType, dstrAcctDesign, idDataGroup );
                  else if ( dstrTransType == CAN_AT_OUT )
                     pAMSMstrInfo->canATOut ( dstrTaxJuris, dstrProvResid, dstrAccountType, dstrTaxType, dstrAcctDesign, idDataGroup );
                  else if ( dstrTransType == MIN_PAC )
                     pAMSMstrInfo->minPAC ( dstrTaxJuris, dstrProvResid, dstrAccountType, dstrTaxType, dstrAcctDesign, dstrAmount, bFundOverride, idDataGroup );
                  else if ( dstrTransType == MIN_SWP )
                     pAMSMstrInfo->minSWP ( dstrTaxJuris, dstrProvResid, dstrAccountType, dstrTaxType, dstrAcctDesign, dstrAmount, bFundOverride, idDataGroup );
                  else if ( dstrTransType == CAN_PURCHASE )
                     pAMSMstrInfo->canPurchase ( dstrTaxJuris, dstrProvResid, dstrAccountType, dstrTaxType, dstrAcctDesign, idDataGroup );                     
                  else if ( dstrTransType == CAN_REDEEM) 
                     pAMSMstrInfo->canRedeem ( dstrTaxJuris, dstrProvResid, dstrAccountType, dstrTaxType, dstrAcctDesign, idDataGroup );
                  else if ( dstrTransType == CAN_TRANSFER_IN )
                     pAMSMstrInfo->canTransferIn ( dstrTaxJuris, dstrProvResid, dstrAccountType, dstrTaxType, dstrAcctDesign, idDataGroup );
                  else if ( dstrTransType == CAN_TRANSFER_OUT )
                     pAMSMstrInfo->canTransferOut ( dstrTaxJuris, dstrProvResid, dstrAccountType, dstrTaxType, dstrAcctDesign, idDataGroup );
                  else
                     assert (0);
               }
            }
         }         
      }
   }
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
bool MFAccount::isHouseBroker (const BFDataGroupId& idDataGroup)
{
   if (_dstrHouseBroker == NULL_STRING)
   {
      DString brokerCode;

      getField (ifds::BrokerCode, brokerCode, idDataGroup);
      if (!brokerCode.empty())
      {
         Broker *pBroker (NULL);

         if ( getBroker (pBroker, brokerCode, idDataGroup) <= WARNING && 
              pBroker)
         {
            _dstrHouseBroker = pBroker->isHouseBroker (idDataGroup) ? YES : NO;
         }
      }
   }
   return _dstrHouseBroker == YES;
}


//******************************************************************************
bool MFAccount::isBrokerFileTypeD( const BFDataGroupId& idDataGroup )
{
   DString dstrClearingFirm,
         dstrFileTypeD = NO;

   getField (ifds::ClearingFirm, dstrClearingFirm, idDataGroup);
   if (dstrClearingFirm != NULL_STRING)
   {
      Broker *pBroker (NULL);

      if ( getBroker ( pBroker, dstrClearingFirm, idDataGroup ) <= WARNING && pBroker )
      {
         pBroker->getField( ifds::FileTypeD, dstrFileTypeD, idDataGroup );
      }
   }
   return dstrFileTypeD == YES;
}

//************************************************************************************
SEVERITY MFAccount::setField(const BFFieldId& idField, const DString& dstrValue,
                                           const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect, bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setField"));

   if( idField == ifds::BusinessNo )
   {
      DString dstrBusinessNo( dstrValue );
      dstrBusinessNo.stripAll('-');
      BFCBO::setField( idField, dstrBusinessNo, idDataGroup, bFormatted, bSideEffect );
   }   
   ///////////////////////////
   /*
   else if ( idField == ifds::UpdatePACSWP )
   {
	   BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);	   

	   DString dstrEffectiveDate(NULL_STRING), dstrDefaultAlloc, dstrAMSCode;

	   getField( ifds::AMSCode, dstrAMSCode, idDataGroup);
	   if(  dstrAMSCode.strip() != NULL_STRING )
	   {
		    Shareholder *pShareholder = NULL; 
   			getWorkSession().getDateInHostFormat(dstrEffectiveDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   
			AMSMstrList* pAMSMstrList = NULL;	
			getAMSMstrList( pAMSMstrList, idDataGroup,dstrEffectiveDate );		
			pAMSMstrList->getFieldByAMSCode(I_("RB"),dstrAMSCode,dstrEffectiveDate,ifds::DefaultAlloc,dstrDefaultAlloc,idDataGroup,false);
		    
			// If the input AMSCode should not have account level override allocation set up, then delete the RB allocation
			if ( dstrDefaultAlloc == I_("Y") && getShareholder( pShareholder, idDataGroup ) <= WARNING && pShareholder ) 
			{
					ShrAllocTypeList *pShrAllocTypeList = NULL;

					pShareholder->getAllocationList( pShrAllocTypeList, idDataGroup, true );
					if( pShrAllocTypeList )
					{
					pShrAllocTypeList->setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);
					}            
			}
	   }
   }   
   */
   else
   {
      BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect, bCheckCurrentValue);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
SEVERITY MFAccount::getFundMgmtSettlementInstrList( FundMgmtSettlementInstrList *&pFundMgmtSettlementInstrList, 
                                                    const BFDataGroupId& idDataGroup, 
                                                    bool binquireDatabase /*= true*/  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( " getFundMgmtSettlementInstrList " ) );
   DString accountNum;
   getField( ifds::AccountNum, accountNum, idDataGroup );
   
	pFundMgmtSettlementInstrList = dynamic_cast<FundMgmtSettlementInstrList *>( BFCBO::getObject( I_( "AcctFundMgmtSettlementInstrList" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pFundMgmtSettlementInstrList )
   {
      if( isNew() )
      {
         pFundMgmtSettlementInstrList = new FundMgmtSettlementInstrList ( *this );
         pFundMgmtSettlementInstrList->init( accountNum, I_( "" ), idDataGroup );
      }
      else if( binquireDatabase )
      {
         pFundMgmtSettlementInstrList = new FundMgmtSettlementInstrList ( *this );
         pFundMgmtSettlementInstrList ->init( accountNum, I_("") );
         idWorkingDataGroup = BF::HOST;
      }
      if(pFundMgmtSettlementInstrList)
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject(pFundMgmtSettlementInstrList, I_( "AcctFundMgmtSettlementInstrList" ), OBJ_ACTIVITY_NONE, BF::HOST ); 
         }
         else
         {
            delete pFundMgmtSettlementInstrList;
            pFundMgmtSettlementInstrList = NULL;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
SEVERITY MFAccount::getSettlementInstrList( AcctSettlementInstrList *& pAcctSettlementInstrList, 
                                            const BFDataGroupId& idDataGroup,
                                            bool bInquireDatabase )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( " getSettlementInstrList " ) );

   DString dstrAccountNum;
   getField( ifds::AccountNum, dstrAccountNum, idDataGroup );

   pAcctSettlementInstrList = dynamic_cast<AcctSettlementInstrList *>( BFCBO::getObject( I_( "AcctSettlementInstrList" ), idDataGroup ) );   
   if( NULL == pAcctSettlementInstrList )
   {
      if( isNew() )
      {
         pAcctSettlementInstrList = new AcctSettlementInstrList ( *this );
         pAcctSettlementInstrList->init( idDataGroup, dstrAccountNum, I_( "" ) );
      }
      else if( bInquireDatabase )
      {
         pAcctSettlementInstrList = new AcctSettlementInstrList ( *this );
         pAcctSettlementInstrList ->init( dstrAccountNum, I_( "" ), idDataGroup );         
      }

      if( NULL != pAcctSettlementInstrList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject(pAcctSettlementInstrList, I_( "AcctSettlementInstrList" ), OBJ_ACTIVITY_NONE, idDataGroup ); 
         }
         else
         {
            delete pAcctSettlementInstrList;
            pAcctSettlementInstrList = NULL;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
bool MFAccount::isClearingAcount( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isClearingAcount" ) );

   bool blIsClearingAccount = false;

   DString dstrClearingAccount;
   getField( ifds::ClearingID, dstrClearingAccount, idDataGroup );

   if ( 0 != dstrClearingAccount.stripAll().length() )
        blIsClearingAccount = true;

   return blIsClearingAccount;
}

//************************************************************************************
bool MFAccount::hasSettlementLocation( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "hasSettlementLocation" ) );

   bool blHasSettlementLocation = false;

   DString dstrHasSettlementLocation;
   getField( ifds::SettleLocExist, dstrHasSettlementLocation, idDataGroup );

   if ( I_( "Y" ) == dstrHasSettlementLocation.stripAll() )
      blHasSettlementLocation = true;

   return blHasSettlementLocation;
}
//************************************************************************************
SEVERITY MFAccount::validateClearingID( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( " validateClearingID " ) );
   DString dstrOldValue,dstrNewValue, dstrPendingTrade;
   getField( ifds::ClearingID, dstrOldValue,BF::HOST,false);
   getField( ifds::ClearingID, dstrNewValue,idDataGroup,false);
   getField( ifds::PendingTrade,dstrPendingTrade,idDataGroup,false );
   dstrOldValue.stripAll();
   dstrNewValue.stripAll();
   dstrPendingTrade.strip().upperCase();
   bool bIssueWarning = dstrPendingTrade == YES && dstrOldValue != dstrNewValue &&
                        ( dstrOldValue == NULL_STRING || dstrNewValue == NULL_STRING );
   if( bIssueWarning )
   {
         ADDCONDITIONFROMFILE( CND::WARN_CHANGE_CLEARINFID_PENDING );	
   }

   if ( dstrNewValue == I_( "P" ) )
   {
      ADDCONDITIONFROMFILE( CND::WARN_CHANGE_CLEARINFID_PENDING );	
   }

   bool bPUEVAcct = isCategoryExist ( idDataGroup, PUEV_CAPABLE );

   if ( dstrNewValue == I_( "P" ) && !( bPUEVAcct )  )
   {
      ADDCONDITIONFROMFILE( CND::WARN_ACCT_CATEG_PUEV_SHOULD_BE_SETUP_BASED_ON_CLEARINGID );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************
SEVERITY MFAccount::validateModelCode( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( " validateClearingID " ) );

	DString dstrFeeModelCode;
	getField( ifds::FeeModelCode, dstrFeeModelCode,idDataGroup,false);
	dstrFeeModelCode.stripAll();

   if( NULL_STRING == dstrFeeModelCode )
	{
	
		return NO_CONDITION;
	
	}

   FeeModelList* pFeeModelList = NULL;
   if (getFeeModelInfo (pFeeModelList, dstrFeeModelCode, idDataGroup) <= WARNING &&
        pFeeModelList)
   {
      DString dstrCurrBusDate;
      getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

      int ret = pFeeModelList->isValidFeeModelCode(idDataGroup, dstrFeeModelCode, dstrCurrBusDate);
 
      if(ret == 1)
      {
         DString dstrTemp;                 
			addIDITagValue( dstrTemp, I_("FEEMODELCODE"), dstrFeeModelCode );
         ADDCONDITIONFROMFILEIDI( CND::ERR_FEEMODEL_CODE_NOT_SETUP, dstrTemp);	
      }
      if(ret == 2 )
      {
         DString dstrTemp;                 
			addIDITagValue( dstrTemp, I_("FEEMODELCODE"), dstrFeeModelCode );
         addIDITagValue( dstrTemp, I_("DATE"), dstrCurrBusDate );
         ADDCONDITIONFROMFILEIDI( CND::ERR_FEEMODEL_CODE_NOT_ACTIVE, dstrTemp);	
      }
 
	}

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY MFAccount::getInventorySummaryList( InventorySummaryList*& pInventorySummaryList, 
                                            DString dstrAccountNum, DString dstrFundCode,
                                            DString dstrClassCode, DString dstrActiveOnly,
                                            const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getInventorySummaryList" ) );
   DString dstrKey;
   dstrKey = dstrAccountNum + I_(" ") + dstrFundCode + I_(" ") + dstrClassCode + I_(" ") + dstrActiveOnly;
   dstrKey.strip();
   pInventorySummaryList = dynamic_cast<InventorySummaryList *>(getObject(dstrKey, idDataGroup ));
   if ( !pInventorySummaryList ) {
      pInventorySummaryList = new InventorySummaryList ( *this );
      if ( pInventorySummaryList->init ( dstrAccountNum, dstrFundCode, dstrClassCode, dstrActiveOnly ) <= WARNING ) 
		{
         setObject(pInventorySummaryList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
      }
		else
      {
			delete pInventorySummaryList;
         pInventorySummaryList = NULL;
		}
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
bool  MFAccount::isSettleRedeptionAllowed(const BFDataGroupId& idDataGroup  )
{
	DString dstrStopRedSettle;
    getField(ifds::StopRedSettle,dstrStopRedSettle,idDataGroup,false);
	dstrStopRedSettle.strip().upperCase();
	return (dstrStopRedSettle == NO );
	

}

//******************************************************************************
SEVERITY MFAccount::getTaxExemptAuthorizationList( TaxExemptAuthorizationList*& pTaxExemptAuthorizationList, 
                                            DString dstrAccountNum, const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTaxExemptAuthorizationList" ) );
   DString dstrKey;
   dstrKey = dstrAccountNum;
   dstrKey.strip();
   pTaxExemptAuthorizationList = dynamic_cast<TaxExemptAuthorizationList *>(getObject(dstrKey, idDataGroup ));
   if ( !pTaxExemptAuthorizationList )
	{
		if( isNew() ) //check if account is new
      {
         pTaxExemptAuthorizationList = new TaxExemptAuthorizationList( *this );
         pTaxExemptAuthorizationList->initNew( dstrAccountNum );
      }
	
		else if (inquireDatabase ) 
		{
			pTaxExemptAuthorizationList = new TaxExemptAuthorizationList ( *this );
		   pTaxExemptAuthorizationList->init ( idDataGroup, dstrAccountNum ); 
		}
      if( pTaxExemptAuthorizationList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject(pTaxExemptAuthorizationList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
         }
         else
         {
            delete pTaxExemptAuthorizationList;
            pTaxExemptAuthorizationList = NULL;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY MFAccount::getContractMaturityInfoList( ContractMaturityInstructionList*& pContractMaturityInstructionList,
                                                 const DString& dstrAccountNum, DString& dstrCotAcctRid,
                                                 const DString& dstrContractType, const DString& dstrContractTypeId,
                                                 const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/  )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getContractMaturityInfoList" ) );

	DString dstrKey;
	dstrKey = dstrAccountNum;
	dstrKey.strip();

	pContractMaturityInstructionList = NULL;
	pContractMaturityInstructionList = dynamic_cast<ContractMaturityInstructionList*>(getObject(dstrKey, idDataGroup ));

	if ( pContractMaturityInstructionList && dstrCotAcctRid.empty() )
			pContractMaturityInstructionList->getCotAcctRid(dstrCotAcctRid);
	
	if ( !pContractMaturityInstructionList )
	{
		if( isNew() ) //check if account is new
		{
			pContractMaturityInstructionList = new ContractMaturityInstructionList( *this );
			pContractMaturityInstructionList->initNew ( dstrAccountNum, dstrCotAcctRid );
		}
		else if ( inquireDatabase )
		{
			pContractMaturityInstructionList = new ContractMaturityInstructionList( *this );
			pContractMaturityInstructionList->init (dstrAccountNum, dstrContractType, dstrContractTypeId, idDataGroup);
		}
		
		if( pContractMaturityInstructionList )
		{
			pContractMaturityInstructionList->setContractMatInstrAddFields ( dstrAccountNum, dstrCotAcctRid );

			if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			{
				setObject ( pContractMaturityInstructionList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup);
			}
			else
			{
				delete pContractMaturityInstructionList;
				pContractMaturityInstructionList = NULL;
			}

		} //-if( pContractMaturityInstructionList )

	} //-if ( !pContractMaturityInstructionList )

	return GETCURRENTHIGHESTSEVERITY();
}


//*******************************************************************************
/*
SEVERITY  MFAccount::setAMSRebalanceReadOnlyFlag( const BFDataGroupId &idDataGroup, bool bReadOnly )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAMSRebalanceReadOnlyFlag" ) );

	setFieldReadOnly( ifds::Rebalance, idDataGroup, bReadOnly );

	return(GETCURRENTHIGHESTSEVERITY());
}
*/

//******************************************************************************
SEVERITY MFAccount::getUserDefMatList( UserDefMatList*& pUserDefMatList, 
									            const BFDataGroupId& idDataGroup, 
									            bool inquireDatabase /*= true*/, 
									            const DString& LegalMaturityDate /*=NULL_STRING*/, 
									            const DString& ContractType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getUserDefMatList" ) );

   DString dstrKey = I_( "UserDefMatList" ) + ContractType;
   pUserDefMatList = dynamic_cast<UserDefMatList*>( BFCBO::getObject( dstrKey, idDataGroup ) );
   
   BFDataGroupId idWorkingDataGroup = idDataGroup;   
   if( !pUserDefMatList )
   {
      DString dstrAccountNum;
      getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
      if( isNew() )
      {
         pUserDefMatList = new UserDefMatList( *this );
         pUserDefMatList->initNew( dstrAccountNum, ContractType, idDataGroup );
      }
      else if( inquireDatabase ) //make the view call
      {
         pUserDefMatList = new UserDefMatList( *this );
         pUserDefMatList->init( dstrAccountNum, idDataGroup, LegalMaturityDate, ContractType );
         idWorkingDataGroup = BF::HOST;
      }

      if( pUserDefMatList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pUserDefMatList, dstrKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pUserDefMatList;
            pUserDefMatList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::isBrokerBranchRepActive( const DString& dstrEffectiveDate, 
                                             const BFDataGroupId& idDataGroup)
{
   
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isBrokerBranchRepActive" ) );

   DString brokerCode, branchCode, agentCode, dstrCurrBusDate, dstrStopDate, dstrStartDate, dstrAsOfDate ;

   getField( ifds::BrokerCode, brokerCode, idDataGroup );
   getField( ifds::BranchCode, branchCode, idDataGroup );
   getField( ifds::Slsrep, agentCode, idDataGroup );

	Broker* pBroker (NULL);

	getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false ); 

	// IN 353592: validate against dstrEffectiveDate or current businessdate, whichever is later;
	// isBrkBrRepActiveAsOf will not be used anymore since pre-existing Systematics will no longer be validated
	dstrAsOfDate = dstrEffectiveDate;
	if ( (DSTCommonFunctions::CompareDates( dstrEffectiveDate,dstrCurrBusDate) == DSTCommonFunctions::FIRST_EARLIER) ) 
		dstrAsOfDate = dstrCurrBusDate;

	if( getBroker (pBroker, brokerCode, idDataGroup) <= WARNING &&
		 pBroker)
	{
		if (pBroker->checkEffective(dstrAsOfDate, idDataGroup) <= WARNING)
		{
			//pBroker->getField(ifds::StopDate, dstrStopDate, idDataGroup);
			//pBroker->getField(ifds::EffectiveDate, dstrStartDate, idDataGroup);
			//isBrkBrRepActiveAsOf (dstrCurrBusDate, dstrStartDate, dstrStopDate);

			BranchList pBranchList( *this );

			if( branchCode != NULL_STRING && 
				 pBranchList.init( brokerCode, branchCode ) <= WARNING)
			{
				BFObjIter bfIter( pBranchList, idDataGroup );
				bfIter.begin();
				if( !bfIter.end() )
				{
					Branch* pBranch = dynamic_cast <Branch*> ( bfIter.getObject() );
					if (pBranch)
					{
						if (pBranch->checkEffective (dstrAsOfDate, idDataGroup) <= WARNING)
						{
							//pBranch->getField(ifds::StopDate, dstrStopDate, idDataGroup);
							//pBranch->getField(ifds::EffectiveDate, dstrStartDate, idDataGroup);
							//isBrkBrRepActiveAsOf (dstrCurrBusDate, dstrStartDate, dstrStopDate);
						}
					}
				}

				AgentList pAgentList( *this );

				if (agentCode != NULL_STRING &&
					pAgentList.init(brokerCode, branchCode, agentCode) <= WARNING )
				{
					BFObjIter bfIter( pAgentList, idDataGroup );
					bfIter.begin();
					if( !bfIter.end() )
					{
						Agent* pAgent = dynamic_cast <Agent*> ( bfIter.getObject() );
						if (pAgent)
						{
							if (pAgent->checkEffective ( dstrAsOfDate, idDataGroup ) <= WARNING)
							{
								//pAgent->getField(ifds::StopDate, dstrStopDate, idDataGroup);
								//pAgent->getField(ifds::EffectiveDate, dstrStartDate, idDataGroup);
								//isBrkBrRepActiveAsOf(dstrCurrBusDate, dstrStartDate, dstrStopDate);
							}
						}
					}
				} 
			} 
   	}
	}
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::isBrkBrRepActiveAsOf(	const DString& dstrAsOfDate,
													   const DString& dstrEffectiveDate,
														const DString& dstrStopDate)
{
   
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isBrkBrRepActiveBusDate" ) );

	if ( (DSTCommonFunctions::CompareDates( dstrStopDate,dstrAsOfDate) == DSTCommonFunctions::FIRST_EARLIER) ) 
	{
		ADDCONDITIONFROMFILE(CND::WARN_BRKBRREP_INACTIVE_CURRBUSDATE);
	}
   else if (( DSTCommonFunctions::CompareDates( dstrAsOfDate, dstrEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER)  )
	{	
		ADDCONDITIONFROMFILE(CND::WARN_BRKBRREP_INACTIVE_CURRBUSDATE);    
	}		
		
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getBroker ( Broker *&pBroker, 
                                const DString& dstrBrokerCode,
                                const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBroker") );
   pBroker = NULL;
	
	SEVERITY sevRtn = NO_CONDITION;

   DString dstrAccountNum;
	
	getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );

   if (!dstrBrokerCode.empty())
   {
      DString strKey (I_("Broker=") + dstrBrokerCode);
//look for the list
      BrokerList *pBrokerList = 
            dynamic_cast <BrokerList*> (getObject ( strKey, 
                                                    idDataGroup));
      if (!pBrokerList) //make view call
      {
         pBrokerList = new BrokerList (*this);


			if ( isNew() ) 
			{
				sevRtn = pBrokerList->init2 ( dstrBrokerCode, NULL_STRING, I_("L"), dstrAccountNum , NULL_STRING );     
			} 
			else 
			{
				sevRtn = pBrokerList->init2 ( dstrBrokerCode, NULL_STRING, I_("L"), dstrAccountNum , I_("Acct") );
			}

         if ( sevRtn <= WARNING )
         {
            setObject ( pBrokerList, strKey, OBJ_ACTIVITY_NONE, idDataGroup );
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
bool MFAccount::checkIfClrFirmRelated (const DString& dstrBrokerCode, const BFDataGroupId &idDataGroup,
													const DString& dstrClearingFirmBroker, const DString& dstrRelationType )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("checkIfClrFirmRelated") );
	BrokerList brokerList (*this) ;
	Broker* pBroker = NULL;
	
	DString dstrRelatedToClrFirm = NO;

	DString dstrAccountNum;
	getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );

   if ( isNew() ) 
	{
		brokerList.initNSCC( dstrBrokerCode, NULL_STRING, I_("L"), dstrAccountNum , NULL_STRING, 
			                  dstrClearingFirmBroker, dstrRelationType );     
	} 
	else 
	{
		brokerList.initNSCC( dstrBrokerCode, NULL_STRING, I_("L"), dstrAccountNum , I_("Acct"),
								   dstrClearingFirmBroker, dstrRelationType );
	}
	if( brokerList.getBroker( dstrBrokerCode, pBroker) <= WARNING &&	 pBroker )
	{
		
      pBroker->getField ( ifds::RelatedToClrFirm, dstrRelatedToClrFirm, idDataGroup );
   }
  
	return ( dstrRelatedToClrFirm == YES ? true : false );
}

//*******************************************************************************
SEVERITY MFAccount::validateBrokerForNSCC( const DString& brokerCode,	const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBrokerForNSCC" ) );
	
	DString dstrNSCCCompliant;
   if( getWorkSession().getOption( ifds::NSCCCompliant, dstrNSCCCompliant, idDataGroup, false ) <= WARNING )
   {
		if( dstrNSCCCompliant == YES )
		{
			if ( !(isBrokerNSCCCompliant( brokerCode, idDataGroup ) ) )
			{				
				if (!isNew())
            {
               ADDCONDITIONFROMFILE( CND::WARN_ACCT_SWITCH_TO_NON_NSCC_BROKER );
            }
			}
			else
			{
				DString dstrClearingFirm;
				getField (ifds::ClearingFirm, dstrClearingFirm, idDataGroup);
				if( dstrClearingFirm.empty())
				{
					if(!isNew ())
					{
						ADDCONDITIONFROMFILE( CND::ERR_CLEARINGFIRM_IS_MANDATORY); 
					}

					ADDCONDITIONFROMFILE( CND::WARN_ACCT_SWITCH_TO_NSCC_BROKER );
				}
			}

		}
	}

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY MFAccount::validateClearingFirm( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClearingFirm" ) );

  
	DString dstrClearingFirm, dstrParticipantID ;
	getField (ifds::ClearingFirm, dstrClearingFirm, idDataGroup);
	dstrClearingFirm.strip();

	if ( dstrClearingFirm == NULL_STRING )
	{
		ADDCONDITIONFROMFILE( CND::ERR_CLEARINGFIRM_IS_MANDATORY); 
	}
	else if ( isBrokerNSCCCompliant( dstrClearingFirm, idDataGroup ) )
	{
		checkIfNSCCComplant( dstrClearingFirm, idDataGroup );
	}
	else
	{
		DString idiStr;
		addIDITagValue( idiStr,I_("NSCC"), dstrClearingFirm);
      ADDCONDITIONFROMFILEIDI( CND::ERR_INPUTED_VALUES_IS_NOT_NSCC_COMPLIANT, idiStr); 
	}
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MFAccount::validateClrFirmAgtFirmTPA( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClrFirmAgtFirmTPA" ) );

  
	DString dstrClearingFirm, dstrAgentForFirm, dstrTPA ;
	getField (ifds::ClearingFirm, dstrClearingFirm, idDataGroup);
	dstrClearingFirm.strip();

	getField (ifds::AgentForFirm, dstrAgentForFirm, idDataGroup);
	dstrAgentForFirm.strip();

	getField (ifds::TPA, dstrTPA, idDataGroup);
	dstrTPA.strip();

	DString dstrBrokerCode;
	getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup);
	dstrBrokerCode.strip();
	// Among these three fields, at least one must be equal to the value of the account level broker code
	if ( dstrClearingFirm != dstrBrokerCode && dstrAgentForFirm != dstrBrokerCode && dstrTPA != dstrBrokerCode )
	{
		ADDCONDITIONFROMFILE( CND::ERR_NO_ONE_EQUAL_TO_BROKER_CODE);
	}
	/* Incident #388060 -- Email from Luke: 
	 * The Clearing Firm and Agent for Firm or the Clearing Firm and TPA values may be the same. 
	 * The Agent for Firm and TPA values cannot be the same.
	 * Base on above, following code are commented out
	else if ( dstrClearingFirm == dstrBrokerCode && ( dstrAgentForFirm != NULL_STRING || dstrTPA != NULL_STRING ) )
	{
		//Both Agent For Firm and TPA must be blank if ClearingFire equal to Broker
		ADDCONDITIONFROMFILE( CND::ERR_CLEARINGFIRM_ALREADY_EQUAL_TO_BROKER);
	}*/

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::validateAgtFirmClrFirm( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAgtFirmClrFirm" ) );


	DString dstrAgentForFirm, dstrClearingFirm, dstrBrokerCode;

	getField (ifds::AgentForFirm, dstrAgentForFirm, idDataGroup);
	dstrAgentForFirm.strip();


	getField (ifds::ClearingFirm, dstrClearingFirm, idDataGroup);
	dstrClearingFirm.strip();


	getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup);
	dstrBrokerCode.strip();

	// Agent for firm is not valid if It is not blank and not equal to BrokerCode
	if( dstrAgentForFirm != NULL_STRING && dstrAgentForFirm != dstrBrokerCode )
	{
		ADDCONDITIONFROMFILE ( CND::ERR_AGENTFORFIRM_INVALID);
	}
	if ( dstrAgentForFirm == dstrBrokerCode )
	{
		if( ! ( checkIfClrFirmRelated( dstrAgentForFirm, idDataGroup, dstrClearingFirm, I_("F") ) ) )
		{
			// Agent for firm is not valid if it is not related to Clearing firm.
			ADDCONDITIONFROMFILE( CND::ERR_AGENTFORFIRM_NOT_RELATED_TO_CLEARINGFIRM);
		}
	}
	
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::validateTPAClrFirm( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTPAClrFirm" ) );

	DString dstrClearingFirm, dstrTPA, dstrBrokerCode;
	getField (ifds::ClearingFirm, dstrClearingFirm, idDataGroup);
	dstrClearingFirm.strip();

	getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup);
	dstrBrokerCode.strip();

	getField (ifds::TPA, dstrTPA, idDataGroup);
	dstrTPA.strip();


	// TPA is not valid if It is not blank and not equal to BrokerCode
	if( dstrTPA != NULL_STRING && dstrTPA != dstrBrokerCode )
	{
		ADDCONDITIONFROMFILE ( CND::ERR_TPA_INVALID );
	}
	if (  dstrTPA == dstrBrokerCode )
	{
		if( ! ( checkIfClrFirmRelated( dstrTPA, idDataGroup, dstrClearingFirm, I_("F") ) ) )
		{
			//PTA is not valid if it is not related to Clearing firm.
			ADDCONDITIONFROMFILE( CND::ERR_TPA_NOT_RELATED_TO_CLEARINGFIRM);
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::validateAgentTPA( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAgentTPA" ) );

	DString dstrNSCCCompliant, dstrBrokerCode;
	getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup);

 	if( getWorkSession().getOption( ifds::NSCCCompliant, dstrNSCCCompliant, idDataGroup, false ) <= WARNING )
   {
	   if( dstrNSCCCompliant == YES && isBrokerNSCCCompliant( dstrBrokerCode, idDataGroup ) )
		{
			
			DString dstrAgentForFirm, dstrTPA ;
			
			getField (ifds::AgentForFirm, dstrAgentForFirm, idDataGroup);
			dstrAgentForFirm.strip();

			getField (ifds::TPA, dstrTPA, idDataGroup);
			dstrTPA.strip();

			// Agent for firm and TPA cannot have the same value unless both are blank
			if( dstrAgentForFirm != NULL_STRING && dstrTPA != NULL_STRING )
			{
				if( dstrAgentForFirm == dstrTPA )
				{
					ADDCONDITIONFROMFILE( CND::ERR_AGENT_TPA_SAME );
				}
			}
		}
	}
	return(GETCURRENTHIGHESTSEVERITY());
}


//********************************************************************************
SEVERITY MFAccount::validateAMSRBForEscrow( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAMSRBForEscrow" ) );

	DString dstrEscrow;
	getField( ifds::Escrow,  dstrEscrow,  idDataGroup, false );

	if( dstrEscrow.strip().upperCase() == YES ) 
   {
		// AMS portfolio cannot be set up for AMS account
		getErrMsg( I_("374"), CND::ERR_AMS_ESCROW_FOR_ACCOUNT, CND::WARN_AMS_ESCROW_FOR_ACCOUNT, idDataGroup, NULL_STRING );		
	}
		
   return( GETCURRENTHIGHESTSEVERITY() );
}

//*******************************************************************************
SEVERITY MFAccount::validateAMSRBForSWP( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSRBForSWP"));

   SystematicList* pSystematicList = NULL;	

	getSystematicList( pSystematicList, idDataGroup );
	if( pSystematicList ) 
   {
		DString dstrDate;
		getWorkSession().getDateInHostFormat(dstrDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   

		if( pSystematicList->hasGoodSWPAtDate(idDataGroup,dstrDate) ) {
			getErrMsg( I_("375"), CND::ERR_AMS_SETUP_FOR_SWP, CND::WARN_AMS_SETUP_FOR_SWP, idDataGroup, NULL_STRING );
		}
	}
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**********************************************************************************
SEVERITY MFAccount::validateAMSRBForGICFund( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSRBForGICFund"));

	MFAccountHoldingList*  pMFAccountHoldingList;
   getAccountHoldingList( pMFAccountHoldingList,idDataGroup );
	if( pMFAccountHoldingList ) 
   {
		if( pMFAccountHoldingList->hasHeldGICFund( idDataGroup) ) 
      {
         ADDCONDITIONFROMFILE( CND::ERR_AMS_ACCOUNT_HOLD_GIC );
		}
	}
   return( GETCURRENTHIGHESTSEVERITY() );
}

//*******************************************************************************
SEVERITY MFAccount::validateAMSRBForPendingPAC( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSRBForPendingPAC"));

   PendingTradeList* pPendingTradeList = NULL;	
	getPendingTradesList( pPendingTradeList, idDataGroup, FULL_LIST );

	if( pPendingTradeList ) 
   {
		if( pPendingTradeList->PendingPACExist(idDataGroup) ) 
      {
			getErrMsg( I_("376"), CND::ERR_AMS_SETUP_FOR_PAC, CND::WARN_AMS_SETUP_FOR_PAC, idDataGroup, NULL_STRING );
		}
	}
   return( GETCURRENTHIGHESTSEVERITY() );
}


//**********************************************************************************
SEVERITY MFAccount::validateAMSRBForFundCurrency( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSROForFundCurrency"));

   MFAccountHoldingList*  pMFAccountHoldingList = NULL;
   getAccountHoldingList( pMFAccountHoldingList,idDataGroup );
	if( pMFAccountHoldingList )
	{
		if( pMFAccountHoldingList->hasHeldMultiCurrencyFund( idDataGroup ) )
		{
			getErrMsg( I_("378"), CND::ERR_AMS_CANNOT_SETUP_FOR_ACCOUNT_HOLDING_MULTICURRENCY_FUND,
				CND::WARN_AMS_CANNOT_SETUP_FOR_ACCOUNT_HOLDING_MULTICURRENCY_FUND, idDataGroup, NULL_STRING );		
		}
	}
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY MFAccount::checkIfNSCCComplant( const DString& dstrBrokerCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkIfNSCCComplant" ) );

   DString dstrNSCCCompliant;

	if( getWorkSession().getOption( ifds::NSCCCompliant, dstrNSCCCompliant, idDataGroup, false ) <= WARNING )
   {
	   if( dstrNSCCCompliant == YES )
		{
			DString idiStr;
			if ( ! isBrokerNSCCCompliant( dstrBrokerCode, idDataGroup ) )
			{
				
				addIDITagValue( idiStr,I_("NSCC"), dstrBrokerCode);
         	ADDCONDITIONFROMFILEIDI( CND::ERR_INPUTED_VALUES_IS_NOT_NSCC_COMPLIANT, idiStr); 
			}
			else 
			{
				checkIfBrokerEffective( dstrBrokerCode, idDataGroup );
			}
		}
	}
		
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool MFAccount::isBrokerNSCCCompliant(const DString& brokerCode, const BFDataGroupId& idDataGroup )
{

   DString  dstrBrokerNSCCCompliant = NO;

	Broker *pBroker;

   if ( getBroker ( pBroker, brokerCode, idDataGroup ) <= WARNING && pBroker )
   {
      
      pBroker->getField (ifds::NSCCCompliant, dstrBrokerNSCCCompliant, idDataGroup, false);
	}
	

   return ( dstrBrokerNSCCCompliant == YES )?true:false;
}

//******************************************************************************
SEVERITY MFAccount::checkIfBrokerEffective (const DString& brokerCode, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("checkIfBrokerEffective")
                         );
	Broker* pBroker (NULL);

	DString dstrCurrBusDate;

	getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false ); 

   if ( getBroker ( pBroker, brokerCode, idDataGroup ) <= WARNING && pBroker )
   {
      
      pBroker->checkEffective (dstrCurrBusDate, idDataGroup);
	}
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::setParticipantID (const DString& dstrClearingFirm, const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setParticipantID"));

	Broker *pBroker;
	
   if ( dstrClearingFirm != NULL_STRING && getBroker( pBroker, dstrClearingFirm, idDataGroup ) <= WARNING && pBroker )
   {
      DString dstrParticipantID;
      pBroker->getField( ifds::ParticipantID, dstrParticipantID, idDataGroup );
		setFieldNoValidate( ifds::ParticipantID, dstrParticipantID, idDataGroup, false, true, true );
	}
	
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************

SEVERITY MFAccount::getAcctCutOffTimesList( AcctCutOffTimesList*& pCutOffTimeList, const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getCutOffTimeList" ) );

   pCutOffTimeList = dynamic_cast<AcctCutOffTimesList*>( BFCBO::getObject( I_( "AcctCutOffTimesList" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pCutOffTimeList )
   {
      if( isNew() )
      {
         pCutOffTimeList = new AcctCutOffTimesList( *this );
         pCutOffTimeList->init();
      }
      else if( inquireDatabase )
      {
         pCutOffTimeList = new AcctCutOffTimesList( *this );

         DString dstrAccountNum;
         getField( ifds::AccountNum, dstrAccountNum, idDataGroup );

         pCutOffTimeList->init( dstrAccountNum );
         idWorkingDataGroup = BF::HOST;
      }
      if( pCutOffTimeList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pCutOffTimeList, I_( "AcctCutOffTimesList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pCutOffTimeList;
            pCutOffTimeList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool MFAccount::negativeBalanceAllowed( const BFDataGroupId& idDataGroup, const DString &fundCode, const DString &classCode)
{
   bool bAllowNegativeBalance = false;

   DString dstrActCatNegBal;

   getWorkSession().getOption( ifds::ActCatNegBal, dstrActCatNegBal, idDataGroup, false ); 

   if (!dstrActCatNegBal.empty())
   {
      if (dstrActCatNegBal == I_("*") )
         bAllowNegativeBalance = true;

      else  // check if at least 1 of acct categories is listed in generic control 
      {
         DString dstrActCatExists;

         getField (ifds::AcctCategoryExist, dstrActCatExists, idDataGroup, false);

         if (dstrActCatExists == I_("Y"))
         {
            AcctCategoryList *pAcctCategoryList = NULL;

            if (getAcctCategoryList( pAcctCategoryList, idDataGroup ) <= WARNING)
            {
               BFObjIter iter( *pAcctCategoryList, idDataGroup);

               for( iter.begin(); !iter.end(); ++iter )
               {
                  DString dstrAcctCategory;

                  iter.getObject()->getField( ifds::AcctCategory, dstrAcctCategory, idDataGroup );
                  dstrAcctCategory.stripAll();

                  if (isCodeInList (dstrAcctCategory, dstrActCatNegBal))
                  {
                     bAllowNegativeBalance = true;
                     break;
                  }
               }
            }
         }
      }
   }
   if(bAllowNegativeBalance == false)	//At Fund/Class Level
   {
		FundDetailList *pFundDetailList = NULL;
		if(getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING  && pFundDetailList)
		{	
			DString dstrFundSubCat;

			FundDetail *pFundDetail = NULL;
			if( pFundDetailList->getFundDetail(fundCode, classCode, idDataGroup, pFundDetail ) && pFundDetail )
			{
				pFundDetail->getField(ifds::FundSubCat, dstrFundSubCat, idDataGroup, false);
				dstrFundSubCat.stripAll();

				if (isCodeInList (ALLOW_NEGBAL_FUNDCLASS, dstrFundSubCat))
                {
                    bAllowNegativeBalance = true;
                }
			}
		}  
	}

   return bAllowNegativeBalance;
}

//******************************************************************************

SEVERITY MFAccount::loadNetworkIDValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("loadNetworkIDValues"));

   DString dstrvalidNetworkType; 

   getWorkSession().getOption ( ifds::ValidNetworkType,
                                dstrvalidNetworkType,
                                BF::HOST,
                                false);

   if (!dstrvalidNetworkType.empty())
   {
      loadSubstitutionList (ifds::NetworkID, idDataGroup, dstrvalidNetworkType);

      BFProperties *pBFPropNetworkID = 
         getFieldProperties (ifds::NetworkID, idDataGroup);

      assert (pBFPropNetworkID);
      if (pBFPropNetworkID)
      {
         DString networkIDSubstList;

         pBFPropNetworkID->getAllSubstituteValues (networkIDSubstList);
         {
            //networkIDSubstList = I_("= ;") + networkIDSubstList;
            setFieldAllSubstituteValues (ifds::NetworkID, idDataGroup, networkIDSubstList);
         }
      }
   }
   else
   {
      DString networkIDSubstList = NULL_STRING;
      //networkIDSubstList = I_("= ;");
      setFieldAllSubstituteValues (ifds::NetworkID, idDataGroup, networkIDSubstList);
      setFieldReadOnly( ifds::NetworkID, idDataGroup, true );  
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool MFAccount::checkPWConsolType( const BFDataGroupId& idDataGroup )
{
   DString dstrConsolTypePW;	
   getFieldBeforeImage( ifds::ConsolTypePW, dstrConsolTypePW );
   bool bReadOnly = true;

   dstrConsolTypePW.strip();	
   if ( dstrConsolTypePW != I_( "99" ) )
   {
      DString dstrConsolidation, dstrConsolDefault;
      DString dstrConsolTransType = I_("PW");

      getDefaultConsolType ( dstrConsolTransType, dstrConsolidation, dstrConsolDefault, idDataGroup );

      if ( isNew() &&
         dstrConsolidation == NO &&
         dstrConsolTypePW == NULL_STRING )
      {
         setFieldNoValidate( ifds::ConsolTypePW, I_("0"), idDataGroup, true, true );			
      }
      else if ( dstrConsolidation == YES )
      {
         BFProperties *pBFPropertiesConsolType = getFieldProperties (ifds::ConsolTypePW, idDataGroup);
         if (pBFPropertiesConsolType)
         {
            DString ConsolTypeSubst, dstrPurchNetting;
            getWorkSession().getOption ( ifds::PurchNetting, dstrPurchNetting, BF::HOST, false);
            pBFPropertiesConsolType->getAllSubstituteValues (ConsolTypeSubst);
            if ( dstrPurchNetting == I_("0") )
            {
               ConsolTypeSubst = removeItemFromSubtList ( ConsolTypeSubst, I_("2")  );
            }
            ConsolTypeSubst = removeItemFromSubtList ( ConsolTypeSubst, I_("99")  );
            setFieldAllSubstituteValues ( ifds::ConsolTypePW, idDataGroup, ConsolTypeSubst );
         }

         if ( isNew() )
         {
            setFieldNoValidate( ifds::ConsolTypePW, dstrConsolDefault, idDataGroup, true, true );
         }

         bReadOnly = false;
      }
   }

   return bReadOnly;
}

//******************************************************************************
bool MFAccount::checkIDConsolType( const BFDataGroupId& idDataGroup )
{
   DString dstrConsolTypeID;
   //getField( ifds::ConsolTypeID, dstrConsolTypeID, idDataGroup, false );
   getFieldBeforeImage( ifds::ConsolTypeID, dstrConsolTypeID );
   bool bReadOnly = true;
   dstrConsolTypeID.strip();

   if ( dstrConsolTypeID != I_( "99" ) )
   {
      DString dstrConsolidation, dstrConsolDefault;
      DString dstrConsolTransType = I_("ID");

      getDefaultConsolType ( dstrConsolTransType, dstrConsolidation, dstrConsolDefault, idDataGroup );

      if ( isNew() &&
         dstrConsolidation == NO &&
         dstrConsolTypeID == NULL_STRING )
      {
         setFieldNoValidate( ifds::ConsolTypeID, I_("0"), idDataGroup, true, true );			
      }
      else if ( dstrConsolidation == YES )
      {
         BFProperties *pBFPropertiesConsolType = getFieldProperties (ifds::ConsolTypeID, idDataGroup);			
         if (pBFPropertiesConsolType)
         {
            DString ConsolTypeSubst;

            pBFPropertiesConsolType->getAllSubstituteValues (ConsolTypeSubst);
            ConsolTypeSubst = removeItemFromSubtList ( ConsolTypeSubst, I_("99")  );
            ConsolTypeSubst = removeItemFromSubtList ( ConsolTypeSubst, I_("2")  );
            setFieldAllSubstituteValues ( ifds::ConsolTypeID, idDataGroup, ConsolTypeSubst );
         }

         if ( isNew() )
         {
            setFieldNoValidate( ifds::ConsolTypeID, dstrConsolDefault, idDataGroup, true, true );
         }

         bReadOnly = false;
      }
   }

   return bReadOnly;
}

//******************************************************************************
bool MFAccount::checkEDConsolType( const BFDataGroupId& idDataGroup )
{
   DString dstrConsolTypeED;
   getFieldBeforeImage( ifds::ConsolTypeED, dstrConsolTypeED );
   bool bReadOnly = true;

   dstrConsolTypeED.strip();
   if ( dstrConsolTypeED != I_( "99" ) )
   {      
      DString dstrConsolidation, dstrConsolDefault;
      DString dstrConsolTransType = I_("ED");

      getDefaultConsolType ( dstrConsolTransType, dstrConsolidation, dstrConsolDefault, idDataGroup );

      if ( isNew() &&
           dstrConsolidation == NO &&
           dstrConsolTypeED == NULL_STRING )
      {
         setFieldNoValidate( ifds::ConsolTypeED, I_("0"), idDataGroup, true, true );
      }
      else if ( dstrConsolidation == YES )
      {
         BFProperties *pBFPropertiesConsolType = getFieldProperties (ifds::ConsolTypeED, idDataGroup);
         if (pBFPropertiesConsolType)
         {
            DString ConsolTypeSubst, dstrPurchNetting;
            getWorkSession().getOption ( ifds::PurchNetting, dstrPurchNetting, BF::HOST, false);
            pBFPropertiesConsolType->getAllSubstituteValues (ConsolTypeSubst);
            ConsolTypeSubst = removeItemFromSubtList ( ConsolTypeSubst, I_("2")  );
            ConsolTypeSubst = removeItemFromSubtList ( ConsolTypeSubst, I_("99")  );
            setFieldAllSubstituteValues ( ifds::ConsolTypeED, idDataGroup, ConsolTypeSubst );
         }

         if ( isNew() )
         {
            setFieldNoValidate( ifds::ConsolTypeED, dstrConsolDefault, idDataGroup, true, true );
         }

         bReadOnly = false;
      }
   }

   return bReadOnly;
}

//******************************************************************************
SEVERITY MFAccount::getDefaultConsolType ( DString &dstrConsolTransType, 
                                           DString &dstrConsolidation, 
                                           DString &dstrConsolDefault,
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDefaultPWConsolType"));
   
   DString dstrConsolTransTypeList, dstrConsolidationList, dstrConsolDefaultList;
      
//initialize the output parameters
   dstrConsolidation = dstrConsolDefault  = NULL_STRING;
   getWorkSession().getOption ( ifds::ConsolTransType, dstrConsolTransTypeList, BF::HOST, false);
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
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getMstrActAttrbValue(const DString &dstrMstrActAttrbName, DString &dstrMstrActAttrbValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMstrActAttrbValue"));
   
   DString dstrMstrActAttrbNameList, dstrMstrActAttrbValueList;
      
//initialize the output parameters
   dstrMstrActAttrbValue = NULL_STRING;
   getWorkSession().getOption ( ifds::MstrActAttrbName, dstrMstrActAttrbNameList, BF::HOST, false);
   getWorkSession().getOption ( ifds::MstrActAttrbValue, dstrMstrActAttrbValueList, BF::HOST, false);
   
//start chopping the strings
   do
   {
      DString::size_type pos = 0;
      DString tmpMstrActAttrbName;

      EXTRACT_VALUE(dstrMstrActAttrbNameList, tmpMstrActAttrbName)
      if (tmpMstrActAttrbName == dstrMstrActAttrbName) //found the transaction type
      {
         EXTRACT_VALUE (dstrMstrActAttrbValueList, dstrMstrActAttrbValue)
         break;
      }
      else //cut the strings
      {
         CHOP_STRING (dstrMstrActAttrbNameList)
         CHOP_STRING (dstrMstrActAttrbValueList)
      }
   }
   while (dstrMstrActAttrbNameList != NULL_STRING);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getPayToEntity( DString &payToEntity,
                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getPayToEntity"));

   payToEntity = NULL_STRING;

   DString broker;

   getField (ifds::BrokerCode, broker, idDataGroup, false);
   if (!broker.empty())
   {
      DString strKey (I_("PayToEntity_BrokerCode=") + broker);
      PayToEntity *pPayToEntity = NULL;

      pPayToEntity = 
         dynamic_cast <PayToEntity*> ( getObject ( strKey, 
                                                   idDataGroup));
      if (!pPayToEntity)
      {
//we need to go through this search only once...
         PayToEntityList *pPayToEntityList = 
               dynamic_cast <PayToEntityList*> ( getObject ( I_("PayToEntityList_BrokerCode=") + broker, idDataGroup));
         DString defaultPaymentFor (PAYMENT_FOR::DISTRIBUTION);

         if (!pPayToEntityList)
         {
            pPayToEntityList = new PayToEntityList (*this);
            if (pPayToEntityList->init (broker, NULL_STRING, idDataGroup) <= WARNING)
            {
               //walk the list to get the active one...
               //use current business date
               BFObjIter iter ( *pPayToEntityList, 
                                 idDataGroup, 
                                 0, 
                                 BFObjIter::ITERTYPE::NON_DELETED);
               while (!iter.end ())
               {
                  PayToEntity *pPayToEntity_ = dynamic_cast <PayToEntity*> (iter.getObject());
                  if (pPayToEntity_)
                  {
                     DString effectiveDate,
                        stopDate,
                        paymentFor,
                        currBussinesDate;
                     
                     getWorkSession().getOption (ifds::CurrBusDate, currBussinesDate, idDataGroup, false);
                     pPayToEntity_->getField (ifds::EffectiveDate, effectiveDate, idDataGroup);
                     pPayToEntity_->getField (ifds::StopDate, stopDate, idDataGroup);
                     pPayToEntity_->getField (ifds::PaymentFor, paymentFor, idDataGroup);
                     if ( defaultPaymentFor == paymentFor &&
                          DSTCommonFunctions::IsDateBetween (effectiveDate, stopDate, currBussinesDate))
                     {
                        pPayToEntity = pPayToEntity_;
                        setObject ( pPayToEntity, 
                                    strKey, 
                                    OBJ_ACTIVITY_NONE, 
                                    idDataGroup,
                                    OBJ_TYPE_NONE,
                        //because the pay to entity object belongs to the pay to entity list
                        //the pointer should be destroyed when its parent dies, not when trade dies
                        //trade holds a link to it just for convenience
                                    BFCBO::OBJ_DELETE::NO_DELETE_ON_DTOR);
                        break; //found the active pay to entity
                     }
                  }
                  ++iter;
               }
               //so the list will be deleted when the account distribution object dies
               setObject ( pPayToEntityList,
                           DString (I_("PayToEntityList_BrokerCode=") + broker), 
                           OBJ_ACTIVITY_NONE,
                           idDataGroup);
            }
         }
      }
      //if we have found the active one for redemption get the pay to entity code
      if (pPayToEntity)
      {
         pPayToEntity->getField (ifds::PayToEntity, payToEntity, idDataGroup, false);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MFAccount::getPayToEntityForRedemption( DString &payToEntity,
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getPayToEntityForRedemption"));

   payToEntity = NULL_STRING;

   DString broker;

   getField (ifds::BrokerCode, broker, idDataGroup, false);
   if (!broker.empty())
   {
      DString strKey (I_("PayToEntityForRedemption_BrokerCode=") + broker);
      PayToEntity *pPayToEntity = NULL;

      pPayToEntity = 
         dynamic_cast <PayToEntity*> ( getObject ( strKey, 
                                                   idDataGroup));
      if (!pPayToEntity)
      {
//we need to go through this search only once...
         PayToEntityList *pPayToEntityList = 
               dynamic_cast <PayToEntityList*> ( getObject ( I_("PayToEntityListForRedemption_BrokerCode=") + broker, idDataGroup));
         DString defaultPaymentFor (PAYMENT_FOR::REDEMPTION);

         if (!pPayToEntityList)
         {
            pPayToEntityList = new PayToEntityList (*this);
            if (pPayToEntityList->init (broker, NULL_STRING, idDataGroup) <= WARNING)
            {
               //walk the list to get the active one...
               //use current business date
               BFObjIter iter ( *pPayToEntityList, 
                                 idDataGroup, 
                                 0, 
                                 BFObjIter::ITERTYPE::NON_DELETED);
               while (!iter.end ())
               {
                  PayToEntity *pPayToEntity_ = dynamic_cast <PayToEntity*> (iter.getObject());
                  if (pPayToEntity_)
                  {
                     DString effectiveDate,
                        stopDate,
                        paymentFor,
                        currBussinesDate;

                     getWorkSession().getOption (ifds::CurrBusDate, currBussinesDate, idDataGroup, false);
                     pPayToEntity_->getField (ifds::EffectiveDate, effectiveDate, idDataGroup);
                     pPayToEntity_->getField (ifds::StopDate, stopDate, idDataGroup);
                     pPayToEntity_->getField (ifds::PaymentFor, paymentFor, idDataGroup);
                     if ( defaultPaymentFor == paymentFor &&
                          DSTCommonFunctions::IsDateBetween (effectiveDate, stopDate, currBussinesDate))
                     {
                        pPayToEntity = pPayToEntity_;
                        setObject ( pPayToEntity, 
                                    strKey, 
                                    OBJ_ACTIVITY_NONE, 
                                    idDataGroup,
                                    OBJ_TYPE_NONE,
                        //because the pay to entity object belongs to the pay to entity list
                        //the pointer should be destroyed when its parent dies, not when trade dies
                        //trade holds a link to it just for convenience
                                    BFCBO::OBJ_DELETE::NO_DELETE_ON_DTOR);
                        break; //found the active pay to entity
                     }
                  }
                  ++iter;
               }
               //so the list will be deleted when the account distribution object dies
               setObject ( pPayToEntityList,
                           DString (I_("PayToEntityListForRedemption_BrokerCode=") + broker), 
                           OBJ_ACTIVITY_NONE,
                           idDataGroup);
            }
         }
      }
      //if we have found the active one for redemption get the pay to entity code
      if (pPayToEntity)
      {
         pPayToEntity->getField (ifds::PayToEntity, payToEntity, idDataGroup, false);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
int MFAccount::validateAffluent( const BFDataGroupId& idDataGroup )
{
   DString dstrAffluent, dstrAffluentOld ;
   getField (ifds::Affluent, dstrAffluent, idDataGroup);
   getFieldBeforeImage (ifds::Affluent, dstrAffluentOld);
   dstrAffluent.strip();
   dstrAffluentOld.strip();

   if ( dstrAffluent == I_( "O" ) )
   {
      // only applies to existing accounts (for new accounts it is OK to set Affluent to 'O'
      if( isNew() || dstrAffluentOld == I_( "O" ) )
      {
         return 0;
      }
      return 1;
   }
   else if ( dstrAffluent == I_( "W" ) )
   {

      if( dstrAffluentOld == I_( "W" ) )
      {
         return 0;
      }

      //if new account, don't allow to change to 'W'
      if( isNew() )
      {
         return 3;
      }

      // only call the view for existing accounts
      try {
            //view 385 call
            DString strAccountNum,strLink;
            getField(ifds::AccountNum, strAccountNum, idDataGroup);
            getField(ifds::LinkMFR, strLink, idDataGroup);

            BFData requestData(ifds::DSTC0385_REQ);   
            BFData responseData(ifds::DSTC0385_VW);

            DString mgmtCoIdOut;
            requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
            requestData.setElementValue( ifds::AccountNum, strAccountNum );
            requestData.setElementValue( ifds::LinkMFR, strLink );
            requestData.setElementValue( ifds::AffluentFrom, dstrAffluentOld );
            requestData.setElementValue( ifds::AffluentTo, dstrAffluent );

            DSTCRequestor& dstcRequestor = DSTCRequestor( getSecurity(), true);
            dstcRequestor.setRecycleOnReceive( true );
            bool blMoreRec = false;
            SEVERITY sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::AFFLUENT_VALIDATION, requestData, responseData, DSTCRequestor( getSecurity(), true), &blMoreRec );
            if( sevRtn <= WARNING )
            {
               DString strChgAllowed;
               responseData.getElementValue( ifds::AffluentChgAllowed, strChgAllowed );
               if( strChgAllowed.strip() == I_( "Y" ) )
               {
                  return 0;
               }
            }
      } 
      catch( ... ) {}

      return 2;
   }

   return 0;
}

//******************************************************************************
SEVERITY MFAccount::getAcctSettlementRuleList( AcctLvlSttlmntRuleList *&pAcctSettlementRuleList, 
                                               const BFDataGroupId& idDataGroup,
                                               bool bCreate)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAcctSettlementRuleList" ) );


    DString dstrAccountNum;
    getField( ifds::AccountNum, dstrAccountNum, idDataGroup );

    pAcctSettlementRuleList = dynamic_cast<AcctLvlSttlmntRuleList *>(getObject(ACCT_LVL_SETTLMNT_RULE_LIST, idDataGroup ));
    
    if( !pAcctSettlementRuleList && bCreate)
    {
      BFDataGroupId idWorkingDataGroup = idDataGroup;
      pAcctSettlementRuleList = new AcctLvlSttlmntRuleList( *this );
      
      if( isNew() || !isSettlementRuleExist( idDataGroup ) ) //check if the account is new, or if Settlement Rules do not exist
      {
         pAcctSettlementRuleList->initNew(dstrAccountNum, idDataGroup);
      }
      else
      {
         pAcctSettlementRuleList->init(dstrAccountNum, idDataGroup);
      }

      if (!isNew())
      {
         idWorkingDataGroup = BF::HOST;
      }

      if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
      {
         setObject( pAcctSettlementRuleList, ACCT_LVL_SETTLMNT_RULE_LIST, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
      }
      else
      {
         delete pAcctSettlementRuleList;
         pAcctSettlementRuleList = NULL;
      }
    }

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool MFAccount::isSettlementRuleExist( const BFDataGroupId& idDataGroup )
{
    TRACE_METHOD( CLASSNAME, I_("isSettlementRuleExist") );

   DString dstrSettlementRuleExist;
   getField( ifds::SettlementRuleExist, dstrSettlementRuleExist, idDataGroup );

   return ( dstrSettlementRuleExist.strip().upperCase() == I_("Y") );
}

//******************************************************************************

SEVERITY MFAccount::isLIFGainLossEligible( const BFDataGroupId& idDataGroup, DString& strEligible )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isLIFGainLossApplicable" ) );

   TaxTypeRule *pTaxTypeRule = NULL;
   strEligible = I_("N");

   if ( getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
   {
      DString dstrJurisdiction;
      getField( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
      strEligible = pTaxTypeRule->getJurisLimitField( ifds::EligExtTrfGainLoss, dstrJurisdiction, idDataGroup );
      strEligible.strip();
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::validateTaxTypeTaxTypeSchedWithJurisEffDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, 
      I_( "validateTaxTypeTaxTypeSchedWithJurisEffDate" ) );

   DString dstrAcctEffDate, taxJurisEffectiveDate, dstrFmtTaxJurisEffDate, taxJurisStopDate;
   DString dstrTaxType, dstrPensionJuris,dstrTaxTypeSched;

   getField( ifds::TaxType, dstrTaxType, idDataGroup );
   getField( ifds::PensionJuris, dstrPensionJuris, idDataGroup );
   getField( ifds::TaxTypeSchedule, dstrTaxTypeSched, idDataGroup, false );
   getField( ifds::EffectiveDate, dstrAcctEffDate, idDataGroup, false );

   TaxTypeRule *pTaxTypeRule = NULL;
   if ( getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
   {
      DString  ruleTaxTypeSchedEffDate;
      ruleTaxTypeSchedEffDate = pTaxTypeRule->getJurisLimitField( ifds::EffectiveDate, dstrPensionJuris, idDataGroup );

      if(  !ruleTaxTypeSchedEffDate.strip().empty() &&
          ( DSTCommonFunctions::CompareDates( dstrAcctEffDate , ruleTaxTypeSchedEffDate) == 
            DSTCommonFunctions::FIRST_EARLIER )
         )
      {
         bool bTaxTypeScheduleApplic = false;

         DString strTaxTypeDesc, TaxTypeSchedDesc, strJurisdDesc;
         getField( ifds::TaxType, strTaxTypeDesc, idDataGroup, true );
         getField( ifds::PensionJuris, strJurisdDesc, idDataGroup, true );
         getField( ifds::TaxTypeSchedule, TaxTypeSchedDesc, idDataGroup, true );
         dstrFmtTaxJurisEffDate = 
            pTaxTypeRule->getJurisLimitField(ifds::EffectiveDate, dstrPensionJuris, idDataGroup, true);

         DString idiStr, strTemp = NULL_STRING;
         strTemp += strJurisdDesc;
         strTemp += I_(" ");
         strTemp += strTaxTypeDesc;

         isTaxTypeScheduleApplicable( bTaxTypeScheduleApplic, NULL_STRING, NULL_STRING, NULL_STRING, idDataGroup);
         if( bTaxTypeScheduleApplic )
         {
            strTemp += I_(" ");
            strTemp += TaxTypeSchedDesc;
         }

         addIDITagValue( idiStr, I_("VAR1"), strTemp );
         addIDITagValue( idiStr, I_("TAXJURISEFFECTIVEDATE"), dstrFmtTaxJurisEffDate );
         ADDCONDITIONFROMFILEIDI( CND::ERR_TAX_TYPE_LIMIT_RULE_NOT_SUPPORTED_BEFORE_DATE, idiStr);

      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY MFAccount::getEntitySubstList (const BFDataGroupId &idDataGroup, 
                                        DString &entitySubstList, 
                                        bool isDeathClaim)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntitySubstList"));

   entitySubstList = NULL_STRING;

   DString accountNum;
   ENTITIES_VECTOR acctOwnerEntities;
   WorkSessionEntityList *pWorkEntityList = NULL;

   getWorkSession().getWorkSessionEntityList(pWorkEntityList);
   getAcctOwnerEntities (acctOwnerEntities, idDataGroup);
   AccountEntityXref *pAccountEntityXref (NULL);

   getField (ifds::AccountNum, accountNum, idDataGroup);

   int iNumOfEntities = acctOwnerEntities.size();

   for (int i = 0; i < iNumOfEntities; ++i)
   {
      DString entityId = acctOwnerEntities[i] ;
      DString firstName,
         lastName,
         entityTypeDescr;
      Entity *pEntity = NULL;

      if (pWorkEntityList)
      {
         pWorkEntityList->getEntity (idDataGroup, entityId, pEntity);
         if (getAccountEntityXref (pAccountEntityXref, idDataGroup) <= WARNING)
         {
            BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                                idDataGroup, 
                                                true, 
                                                BFObjIter::ITERTYPE::NON_DELETED);

            DString searchKey;

            AccountEntityXref::buildPartialKeyForEntityType (searchKey, I_("01"));
            iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
            while (!iterAccountEntityXrefOut.end())
            {
               DString key = iterAccountEntityXrefOut.getStringKey ();
               
               DString _entityId,
                  _accountNum;
               
               AccountEntityXref::getValueForTag (key, I_("EntityId"), _entityId);
               AccountEntityXref::getValueForTag (key, I_("AccountNum"), _accountNum);
               if (_accountNum.stripLeading ('0') == accountNum && 
                   _entityId == entityId)
               {
                  iterAccountEntityXrefOut.getObject () ->getField (ifds::EntityType, entityTypeDescr, idDataGroup, true);
                  break;
               }
               ++iterAccountEntityXrefOut;
            }
         }

         if (pEntity)
         {
            bool bDead = pEntity->isDead (idDataGroup);

            if (isDeathClaim)
            {
               if (!bDead)
                  continue;
            }
           /* else
            {
               if (bDead)
                  continue;
            }*/
            pEntity->getField (ifds::FirstName, firstName, idDataGroup, false);
            pEntity->getField (ifds::LastName, lastName, idDataGroup, false);
         }
         entitySubstList += entityId + I_("=") + lastName + I_(", ") + firstName + 
               I_("(") + entityTypeDescr + I_(")") + I_(";");
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getDeadEntities (const BFDataGroupId &idDataGroup, 
                                     DString &entitySubstList)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDeadEntities"));
   entitySubstList = NULL_STRING;

   DString accountNum;
   AccountEntityXref *pAccountEntityXref (NULL);

   getField (ifds::AccountNum, accountNum, idDataGroup);
   if (getAccountEntityXref (pAccountEntityXref, idDataGroup) <= WARNING)
   {
      BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                           idDataGroup, 
                                           true, 
                                           BFObjIter::ITERTYPE::NON_DELETED);

      DString searchKey;

      AccountEntityXref::buildPartialKeyForAccount (searchKey, accountNum);
      iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
      while (!iterAccountEntityXrefOut.end())
      {
         DString key = iterAccountEntityXrefOut.getStringKey ();
         
         DString entityId;
         
         AccountEntityXref::getValueForTag (key, I_("EntityId"), entityId);
         
         WorkSessionEntityList *pWorkEntityList = NULL;
         Entity *pEntity (NULL);

         getWorkSession().getWorkSessionEntityList (pWorkEntityList);
         if (pWorkEntityList && 
             pWorkEntityList->getEntity (idDataGroup, entityId, pEntity) &&
             pEntity)
         {
            if (pEntity->isDead (idDataGroup))
            {
               DString firstName, 
                  lastName,
                  entityTypeDescr;

               pEntity->getField (ifds::FirstName, firstName, idDataGroup, false);
               pEntity->getField (ifds::LastName, lastName, idDataGroup, false);
               iterAccountEntityXrefOut.getObject () ->getField (ifds::EntityType, entityTypeDescr, idDataGroup, true);
               entitySubstList += entityId + I_("=") + lastName + I_(", ") + firstName + 
                     I_("(") + entityTypeDescr + I_(")") + I_(";");
            }
         }
         ++iterAccountEntityXrefOut;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MFAccount::getEntitySubstSet(const BFDataGroupId &idDataGroup, 
	   DString &entitySubstSet, 
	   const DString& dstrEntityType,
      const bool& isAppendEntityType)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDeadEntities"));

	std::map<DString, DString> entityMap;
	AccountEntityXref *pAccountEntityXref (NULL);
	DString dstrAccountNum;
	getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	if (getAccountEntityXref (pAccountEntityXref, idDataGroup) <= WARNING)
	{
		BFObjIter iter (*pAccountEntityXref, 
				idDataGroup, 
				true, 
				BFObjIter::ITERTYPE::NON_DELETED);

		DString searchKey;
		AccountEntityXref::buildPartialKeyForAccount (searchKey, dstrAccountNum);
		
		for(iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
			!iter.end();
			++iter)
		{
			DString dstrEntityId, dstrIterEntityType;
			iter.getObject()->getField(ifds::EntityId, dstrEntityId, idDataGroup);
			iter.getObject()->getField(ifds::EntityType, dstrIterEntityType, idDataGroup);

         if(dstrEntityType != I_(""))
			{	
				if(dstrEntityType != dstrIterEntityType)
					continue;
			}
         DString dstrFormattedEntityType;
         iter.getObject()->getField(ifds::EntityType, dstrFormattedEntityType, idDataGroup, true);

			if(entityMap[dstrEntityId] == I_(""))
         {
            entityMap[dstrEntityId] = dstrFormattedEntityType;
         }
         else
         {  
            entityMap[dstrEntityId] = entityMap[dstrEntityId] + I_(", ") + dstrFormattedEntityType;
         }
		}      
	}

   std::map<DString, DString>::const_iterator iter;
   for(iter = entityMap.begin(); iter != entityMap.end(); ++iter)
   {
      DString entityId = iter->first;
      DString entityTypeList = iter->second;
      DString dstrFullName;
      getFullEntityName(idDataGroup, entityId, dstrFullName);

      if(isAppendEntityType)
      {
         entitySubstSet += entityId + I_("=") + dstrFullName + I_(" (")+ entityTypeList +I_(")") + I_(";");
      }
      else
      {
         entitySubstSet += entityId + I_("=") + dstrFullName + I_(";");
      }
   }
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MFAccount::getFullEntityName (const BFDataGroupId &idDataGroup, 
                                       const DString &dstrEntityId, 
                                       DString &dstrFullEntityName)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityName"));

   dstrFullEntityName = NULL_STRING;

   DString strEntityId, firstName, lastName;
   ENTITIES_VECTOR acctOwnerEntities;
   WorkSessionEntityList *pWorkEntityList = NULL;
   Entity *pEntity = NULL;

   getWorkSession().getWorkSessionEntityList(pWorkEntityList);
   getAcctOwnerEntities (acctOwnerEntities, idDataGroup);

   if (pWorkEntityList)
   pWorkEntityList->getEntity( idDataGroup, dstrEntityId, pEntity );

   if (pEntity)
   {
      pEntity->getField(ifds::FirstName, firstName, idDataGroup, false);
      pEntity->getField(ifds::LastName, lastName, idDataGroup, false);

      dstrFullEntityName = lastName + I_(", ") + firstName; 
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MFAccount::getTradeAuthorization (TradeAuthorization *&pTradeAuthorization,
                                           const DString &recordType,
                                           const DString &transNum,
                                           const DString &transId,
                                           const DString &authorization,
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTradeAuthorization"));

   DString dstrKey = NULL_STRING;

   dstrKey =  I_("RecordType=") + recordType + I_(";");
   dstrKey += I_("TransNum=") + transNum + I_(";");
   dstrKey += I_("TransId=") + transId;

   _dstrTAKey = dstrKey;

   pTradeAuthorization = dynamic_cast <TradeAuthorization *>(getObject (dstrKey, idDataGroup));

   if (!pTradeAuthorization) 
   {
      pTradeAuthorization = new TradeAuthorization (*this);

      if (pTradeAuthorization->init (recordType, transNum, transId, authorization, idDataGroup) <= WARNING)
      {
         setObject (pTradeAuthorization, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup); 
      }
      else
      {
         delete pTradeAuthorization;
         pTradeAuthorization = NULL;
      }
   }
   else
   {
      pTradeAuthorization->init (recordType, transNum, transId, authorization, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getTradeAuthorization (TradeAuthorization *&pTradeAuthorization,
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTradeAuthorization"));

   pTradeAuthorization = NULL;

   if (!_dstrTAKey.empty ())
      pTradeAuthorization = dynamic_cast <TradeAuthorization *>(getObject (_dstrTAKey, idDataGroup));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getRESPTransferList ( RESPTransferList *&pRESPTransferList, 
                                          const BFDataGroupId &idDataGroup,
                                          const DString &accountNumTo,
                                          const DString &transId,
                                          const DString &transType,
                                          const DString &tradeDate,
                                          const DString &depositType,
                                          const DString &redCode, 
                                          const DString &amount,
                                          const DString &tradeType /*= I_("Pend")*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRESPTransferList"));

   DString strKey = I_("RESPTransferList"); 
   pRESPTransferList = dynamic_cast< RESPTransferList* >(getObject (strKey, idDataGroup));   

   if (!pRESPTransferList)
   {
      DString accountNum;

      getField (ifds::AccountNum, accountNum, idDataGroup);
      pRESPTransferList = new RESPTransferList (*this);

      if (pRESPTransferList->init (accountNum, accountNumTo, transId, transType, tradeDate,
                                   depositType, redCode, amount, tradeType, tradeType == I_("Pend")) <= WARNING)
      {
         setObject (pRESPTransferList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pRESPTransferList;
         pRESPTransferList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getInvestorAuthorizationList ( InvestorAuthorizationList *&pInvestorAuthorizationList, 
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getInvestorAuthorizationList"));
   pInvestorAuthorizationList = NULL;

   pInvestorAuthorizationList = 
      dynamic_cast< InvestorAuthorizationList* >(getObject(I_("InvestorAuthorizationList"), idDataGroup));
   
   if (!pInvestorAuthorizationList && !isNew() )
   {
      BFDataGroupId idWorkingDataGroup = idDataGroup;

      DString accountNum;

      getField(ifds::AccountNum, accountNum, idDataGroup );
      accountNum.stripLeading('0');
      accountNum.strip();

      pInvestorAuthorizationList = new InvestorAuthorizationList (*this);
      
      if (pInvestorAuthorizationList->init (accountNum, idDataGroup) <= WARNING)
      {
         setObject (pInvestorAuthorizationList, I_("InvestorAuthorizationList"), OBJ_ACTIVITY_NONE, idWorkingDataGroup);
      }
      else
      {
         delete pInvestorAuthorizationList;
         pInvestorAuthorizationList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getRESPBenefAllocationList ( RESPBeneficiaryAllocationList *&pRESPBeneficiaryAllocationList, 
                                                 const BFDataGroupId &idDataGroup,
                                                 const DString &transId,
                                                 const DString &tradeType /*= I_("Pend")*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRESPBenefAllocationList"));

   DString strKey = I_("RESPBeneficiaryAllocationList");

   pRESPBeneficiaryAllocationList = 
      dynamic_cast< RESPBeneficiaryAllocationList* >(getObject (strKey, idDataGroup));   

   if (!pRESPBeneficiaryAllocationList)
   {
      DString accountNum;

      getField (ifds::AccountNum, accountNum, idDataGroup);
      pRESPBeneficiaryAllocationList = new RESPBeneficiaryAllocationList (*this);      
      if (pRESPBeneficiaryAllocationList->init (accountNum, transId, tradeType) <= WARNING)
      {
         setObject (pRESPBeneficiaryAllocationList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pRESPBeneficiaryAllocationList;
         pRESPBeneficiaryAllocationList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getInvestorAuthorization( InvestorAuthorization *&pInvestorAuthorization, 
                                              const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getInvestorAuthorization"));
   pInvestorAuthorization = NULL;
   InvestorAuthorizationList *pInvestorAuthorizationList = NULL;
   
   if ( getInvestorAuthorizationList(pInvestorAuthorizationList, idDataGroup) <= WARNING && 
        pInvestorAuthorizationList )
   {
      DString strCurrBusDate;
      getWorkSession().getOption( ifds::CurrBusDate, strCurrBusDate, BF::HOST, false ); 

      BFObjIter iterIAList( *pInvestorAuthorizationList, idDataGroup);
      iterIAList.begin();
      
      pInvestorAuthorization = NULL;
      bool bFound = false;
      while( !iterIAList.end() )
      {
         pInvestorAuthorization = 
            dynamic_cast<InvestorAuthorization*>( iterIAList.getObject( ) );
         if ( NULL != pInvestorAuthorization )
         {
            DString strIAEffectiveDate, strIAStopDate;
            pInvestorAuthorization->getField( ifds::EffectiveDate, strIAEffectiveDate, idDataGroup );
            pInvestorAuthorization->getField( ifds::StopDate, strIAStopDate, idDataGroup );

            if( DSTCommonFunctions::IsDateBetween (strIAEffectiveDate, strIAStopDate, strCurrBusDate))
            {
               bFound = true;
               break;
            }
         }
         ++iterIAList;
      }

      if ( !bFound ) // not found, so pInvestorAuthorization should be NULL
      {
         pInvestorAuthorization = NULL;
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void MFAccount::parseName (const DString &originalName, DString &newName)
{
   if( originalName.find( I_CHAR('&')) == DString::npos )
   {
      newName = originalName;
      return;
   }

   DString tmpBrokerName = originalName;
   int iPos = 0;
   bool bFound = false;

   newName = NULL_STRING;

   while (iPos != -1)
   {
      iPos = tmpBrokerName.find( I_CHAR('&') );

      if (iPos == -1 && bFound)
      {
         newName += tmpBrokerName;
      }
      else
      {
         newName += tmpBrokerName.substr (0, iPos + 1) + I_("&");
         tmpBrokerName = tmpBrokerName.substr (iPos + 1, tmpBrokerName.length ());
         bFound = true;
      }
   }

}

//******************************************************************************
SEVERITY MFAccount::validateBrokerIA(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateBrokerForIA"));

   DString dstrDirDepsBnkApplicable;
   getWorkSession ().getOption ( ifds::DirectDepositBankApplicable, 
                                 dstrDirDepsBnkApplicable, BF::HOST, false);

   if ( dstrDirDepsBnkApplicable == I_("Y") && !isNew() )
   {
      InvestorAuthorization *pInvestorAuthorization = NULL;
      if( getInvestorAuthorization(pInvestorAuthorization,idDataGroup) <= WARNING && 
         pInvestorAuthorization)
      {
         DString strIABroker,
                 strBroker;
         getField( ifds::BrokerCode, strBroker, idDataGroup );
         pInvestorAuthorization->getField( ifds::BrokerCode, strIABroker, idDataGroup );

         if ( strBroker.strip().upperCase() != strIABroker.strip().upperCase() )
         {
            ADDCONDITIONFROMFILE( CND::WARN_IA_BRK_BRNCH_SLSREP_NOT_SAME_WITH_ACCOUNT );
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::validateBranchIA(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateBranchForIA"));

   DString dstrDirDepsBnkApplicable;
   getWorkSession ().getOption ( ifds::DirectDepositBankApplicable, 
                                 dstrDirDepsBnkApplicable, BF::HOST, false);

   if ( dstrDirDepsBnkApplicable == I_("Y") && !isNew() )
   {
      InvestorAuthorization *pInvestorAuthorization = NULL;
      if( getInvestorAuthorization(pInvestorAuthorization,idDataGroup) <= WARNING && 
         pInvestorAuthorization)
      {
         DString strIABranch,
                 strBranch;
         getField( ifds::BranchCode, strBranch, idDataGroup );
         pInvestorAuthorization->getField( ifds::BranchCode, strIABranch, idDataGroup );

         if ( strBranch.strip().upperCase() != strIABranch.strip().upperCase() )
         {
            ADDCONDITIONFROMFILE( CND::WARN_IA_BRK_BRNCH_SLSREP_NOT_SAME_WITH_ACCOUNT );
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::validateSlsRepIA(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateSlsRepIA"));

   DString dstrDirDepsBnkApplicable;
   getWorkSession().getOption ( ifds::DirectDepositBankApplicable, 
                                 dstrDirDepsBnkApplicable, BF::HOST, false);

   if ( dstrDirDepsBnkApplicable == I_("Y") && !isNew() )
   {
      InvestorAuthorization *pInvestorAuthorization = NULL;
      if( getInvestorAuthorization(pInvestorAuthorization,idDataGroup) <= WARNING && 
         pInvestorAuthorization)
      {
         DString strIASlsRep,
                 strSlsRep;
         getField( ifds::Slsrep, strSlsRep, idDataGroup );
         pInvestorAuthorization->getField( ifds::SlsrepCode, strIASlsRep, idDataGroup );

         if ( strSlsRep.strip().upperCase() != strIASlsRep.strip().upperCase() )
         {
            ADDCONDITIONFROMFILE( CND::WARN_IA_BRK_BRNCH_SLSREP_NOT_SAME_WITH_ACCOUNT );
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MFAccount::validateSiblingOnly(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateSiblingOnly"));
                          
   DString strSiblingOnly;
   getField( ifds::SiblingOnly, strSiblingOnly, idDataGroup, false );
   strSiblingOnly.strip().upperCase();

   if ( strSiblingOnly != I_("Y") || strSiblingOnly.empty())
   {
      ADDCONDITIONFROMFILE( CND::WARN_SIBLING_ONLY_BLANK_OR_NO );
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MFAccount::validateRESPTaxType(const DString &taxType, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateRESPTaxType"));

   bool bIsRES2Client = getWorkSession ().isRES2Client();

   if ( bIsRES2Client )
   {
      if ( !isNew() ) // It might be possible to change tax type during NASU
      {
         DString strCurTaxType, strCurTaxTypeFmt,strTaxTypeFrm,strTaxTypeTo;
         DString strTaxTypeFmt = strCurTaxType;
         
         formatField (ifds::TaxType, strTaxTypeFmt, idDataGroup);

         getField( ifds::TaxType, strCurTaxType, idDataGroup, false );
         getField( ifds::TaxType, strCurTaxTypeFmt, idDataGroup, true );

         strTaxTypeFrm  = strCurTaxTypeFmt;
         strTaxTypeFrm += I_("(");
         strTaxTypeFrm += strCurTaxType;
         strTaxTypeFrm += I_(")");

         strTaxTypeTo   = strTaxTypeFmt;
         strTaxTypeTo  += I_("(");
         strTaxTypeTo  += taxType;
         strTaxTypeTo  += I_(")");
         
         DString t550ReportMethod;
         
         getWorkSession().getOption( ifds::T550ReportMethod, t550ReportMethod, idDataGroup, false );

         bool bValidationPass = true;
         if ( t550ReportMethod != YES )
         {
            if ( strCurTaxType == INDIVIDUAL_RESP_TAX_TYPE && taxType != FAMILY_RESP_TAX_TYPE )
            {
               // condition, 9 to any except to M , not allowed
               bValidationPass = false;
            }
            else if ( strCurTaxType == FAMILY_RESP_TAX_TYPE )
            {
               // condition, M to any , not allowed
               bValidationPass = false;
            }
            else if ( taxType == INDIVIDUAL_RESP_TAX_TYPE || taxType == FAMILY_RESP_TAX_TYPE )
            {
               // condition, any to 9 or M , not allowed
               if ( strCurTaxType != INDIVIDUAL_RESP_TAX_TYPE || strCurTaxType != FAMILY_RESP_TAX_TYPE )
               {
                  bValidationPass = false;
               }
            }
         }
         //else
         //{
         //   bValidationPass = false;
         //}
         
         if( !bValidationPass )
         {
            DString dstrTemp;
            addIDITagValue( dstrTemp, I_("TAX_FRM"), strTaxTypeFrm );
            addIDITagValue( dstrTemp, I_("TAX_TO"), strTaxTypeTo );
            ADDCONDITIONFROMFILEIDI( CND::ERR_CANNOT_SWITCH_TAXTYPE, dstrTemp);

         }
      }
   }
   else
   {
      getErrMsg ( IFASTERR::RESP_NASU_NOT_AVAILABLE,
                  CND::ERR_RESP_NASU_NOT_AVAILABLE,
                  CND::WARN_RESP_NASU_NOT_AVAILABLE,
                  idDataGroup,
                  NULL_STRING);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::validateBrokerNI31103STMT(DString& brokerCode, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateBrokerNI31103STMT"));

   Broker *pBroker(NULL);
   // query BrokerCategoryList
   if ( getBroker (pBroker, brokerCode, idDataGroup) <= WARNING &&
        pBroker)
   {
      DString dstrBrokerCategoryList;
      pBroker->getField(ifds::BrokerCategoryList, dstrBrokerCategoryList, idDataGroup, false);
      dstrBrokerCategoryList.strip().upperCase();
      if ( !DSTCommonFunctions::codeInList (NI_31_103_STMT, dstrBrokerCategoryList))
      {
         // check account category list
         AcctCategoryList *pAcctCategoryList (NULL);
         if ( getAcctCategoryList (pAcctCategoryList, idDataGroup) <= WARNING && 
              pAcctCategoryList)
         {
            BFObjIter iter (*pAcctCategoryList, idDataGroup);
            iter.begin();
            while (!iter.end ())
            {
               DString dstrAcctCategory;
               iter.getObject ()->getField (ifds::AcctCategory, dstrAcctCategory, idDataGroup, false);
               if(dstrAcctCategory == CLIENT_MONTHLY_STATEMENT)
               {
                  // add warning message
                  ADDCONDITIONFROMFILE( CND::WARN_CLNT_MTH_STMT_SHOULD_BELONG_ACCT_NON_MFDA );
                  break;
               }

               ++iter;
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getAcctGuaranteeGuardOptList ( AcctGuaranteeGuardOptList *&pAcctGuaranteeGuardOptList, 
                                                   const BFDataGroupId &idDataGroup,
                                                   bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("getAcctGuaranteeGuardOptList"));

   DString strKey = I_("AcctGuaranteeGuardOptList"),
      guaranteeGuardOn, dstrShrNum, dstrGroupCode, dstrHasGWOContract;

   getWorkSession().getOption( ifds::GuaranteeGuardOn, guaranteeGuardOn, idDataGroup, false );
   guaranteeGuardOn.strip().upperCase();

   // get Shareholder
   Shareholder *pShareholder = NULL;
   getField( ifds::ShrNum, dstrShrNum, idDataGroup );
   getShareholder ( pShareholder, BF::HOST );
   
   assert(pShareholder);
   pShareholder->getField (ifds::GroupCode, dstrGroupCode, idDataGroup, false);
   dstrGroupCode.strip().upperCase();

   GroupList *pGroupList = NULL;
   getGroupList(pGroupList);
   assert(pGroupList);
   
   BFObjIter glIter( *pGroupList, idDataGroup );

   bool bFoundGroup = glIter.positionByKey( dstrGroupCode );

   if( bFoundGroup )
   {
      Group* pGroup;
      if( pGroup = dynamic_cast<Group*>( glIter.getObject() ) )
      {
         DString dstrHasGWOContract;
         pGroup->getField(ifds::HasGWOContract, dstrHasGWOContract, idDataGroup, false);
         dstrHasGWOContract.strip().upperCase();

         if( dstrHasGWOContract != I_("Y") || guaranteeGuardOn != I_("Y") )
         {
            return GETCURRENTHIGHESTSEVERITY();
         }

         pAcctGuaranteeGuardOptList = 
               dynamic_cast< AcctGuaranteeGuardOptList* >(getObject (strKey, idDataGroup));   

         if (!pAcctGuaranteeGuardOptList)
         {
            DString accountNum, acctGuarGuardExists;

            BFDataGroupId idWorkingDataGroup = idDataGroup;
            getField (ifds::AccountNum, accountNum, idDataGroup);
            pAcctGuaranteeGuardOptList = new AcctGuaranteeGuardOptList (*this);      

            getField (ifds::AcctGuarGuardExists,acctGuarGuardExists,idDataGroup,false);
            acctGuarGuardExists.strip().upperCase();

            if( isNew() || acctGuarGuardExists == I_("N") )
            {
               pAcctGuaranteeGuardOptList->setField( ifds::AccountNum, accountNum, idDataGroup, false );
               pAcctGuaranteeGuardOptList->initNew(idDataGroup);
            }
            else if  (inquireDatabase ) //make the view call
            {
               idWorkingDataGroup = BF::HOST;
               pAcctGuaranteeGuardOptList->init(accountNum, idDataGroup);
            }
            if ( pAcctGuaranteeGuardOptList )
            {
               if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
               {
                  setObject( pAcctGuaranteeGuardOptList, strKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
               }
               else
               {
                  delete pAcctGuaranteeGuardOptList;
                  pAcctGuaranteeGuardOptList = NULL;
               }
            }
         }   
      }
   }
   else if (!bFoundGroup && guaranteeGuardOn == I_("Y"))
   {
      BFDataGroupId idWorkingDataGroup = idDataGroup;
      pAcctGuaranteeGuardOptList = 
            dynamic_cast< AcctGuaranteeGuardOptList* >(getObject (strKey, idWorkingDataGroup));   

      if (!pAcctGuaranteeGuardOptList)
      {
         DString accountNum, acctGuarGuardExists;

         
         getField (ifds::AccountNum, accountNum, idWorkingDataGroup);
         pAcctGuaranteeGuardOptList = new AcctGuaranteeGuardOptList (*this);      

         getField (ifds::AcctGuarGuardExists,acctGuarGuardExists,idWorkingDataGroup,false);
         acctGuarGuardExists.strip().upperCase();

         if( isNew() || acctGuarGuardExists == I_("N") )
         {
            pAcctGuaranteeGuardOptList->setField( ifds::AccountNum, accountNum, idWorkingDataGroup, false );
            pAcctGuaranteeGuardOptList->initNew(idDataGroup);
         }
         else if  (inquireDatabase ) //make the view call
         {
            idWorkingDataGroup = BF::HOST;
            pAcctGuaranteeGuardOptList->init(accountNum, idWorkingDataGroup);
         }
      }

      if ( pAcctGuaranteeGuardOptList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pAcctGuaranteeGuardOptList, strKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pAcctGuaranteeGuardOptList;
            pAcctGuaranteeGuardOptList = NULL;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getRESPInfoUpdateValidationList (RESPInfoUpdateValidationList *&pRESPInfoUpdateValidationList, 
                                                     const DString &dstrTransID, /*TransId*/
                                                     const DString &dstrNewTaxJuris, /*NewTaxJuris*/
                                                     const DString &dstrNewSibling, /*NewSibling*/
                                                     const DString &dstrValidateType, /*ValidationType*/
                                                     const DString &dstrBenefIdList, /*BenefIdList*/
                                                     const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("getRESPInfoUpdateValidationList"));

   DString dstrKey = I_("TransId=") + dstrTransID + 
                     I_(";TaxJuris=") + dstrNewTaxJuris +
                     I_(";Sibling=") + dstrNewSibling +
                     I_(";ValidateType=") + dstrValidateType +
                     I_(";BenefIdList=") + dstrBenefIdList;

   DString accountNum;

   getField (ifds::AccountNum, accountNum, idDataGroup);

   pRESPInfoUpdateValidationList = dynamic_cast <RESPInfoUpdateValidationList*> (getObject (dstrKey, idDataGroup));

   if (!pRESPInfoUpdateValidationList)
   {
      pRESPInfoUpdateValidationList = new RESPInfoUpdateValidationList (*this);

      //call view 415
      if ( pRESPInfoUpdateValidationList->init ( accountNum,
                                                 dstrTransID, /*TransId*/
                                                 dstrNewTaxJuris, /*NewTaxJuris*/
                                                 dstrNewSibling, /*NewSibling*/
                                                 dstrValidateType, /*ValidationType*/
                                                 dstrBenefIdList, /*BenefIdList*/
                                                 idDataGroup ) <= WARNING )
      {
         setObject ( pRESPInfoUpdateValidationList, 
                     dstrKey, 
                     OBJ_ACTIVITY_NONE, 
                     idDataGroup );
      }
      else
      {
         delete pRESPInfoUpdateValidationList;
         pRESPInfoUpdateValidationList = NULL;
      }

   }   // end if !RESPInfoUpdateValidationList

   return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************
SEVERITY MFAccount::validateAcctCatEPA(const DString& dstrBrokerCode,
                                       const DString& dstrAcctDesignation,
                                       const DString& dstrAcctType,
                                       const DString& dstrAcctTaxType,
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAcctCatEPA" ) );

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket != MARKET_IDS::CANADA )
      return GETCURRENTHIGHESTSEVERITY();

   DString brokerCode(dstrBrokerCode),
      dstrEPABroker;
   Broker* pBroker = NULL;
   //getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
   if ( getBroker (pBroker, dstrBrokerCode, idDataGroup) <= WARNING &&
        pBroker)
   {
      pBroker->getField(ifds::EPABroker, dstrEPABroker, idDataGroup, false);
      dstrEPABroker.strip().upperCase();

      DString acctDesignation(dstrAcctDesignation),
         acctType(dstrAcctType),
         acctTaxType(dstrAcctTaxType),
         tfsaAcctCatCodeList,
         rrspAcctCatCodeList;

      getWorkSession().getOption(ifds::TFSAAcctCatCodeList, tfsaAcctCatCodeList, idDataGroup, false);
      getWorkSession().getOption(ifds::RRSPAcctCatCodeList, rrspAcctCatCodeList, idDataGroup, false);
      acctType.strip().upperCase();
      acctDesignation.strip().upperCase();
      acctTaxType.strip().upperCase();
      tfsaAcctCatCodeList.strip().upperCase();
      rrspAcctCatCodeList.strip().upperCase();

      bool bAcctCatNotAllowed = false;

      // check account category list
      bool bAcctCatEPAAppExist = false;
      AcctCategoryList *pAcctCategoryList (NULL);
      if ( getAcctCategoryList (pAcctCategoryList, idDataGroup) <= WARNING && 
           pAcctCategoryList)
      {
         BFObjIter iter (*pAcctCategoryList, idDataGroup);
         iter.begin();
         while (!iter.end ())
         {
            DString dstrAcctCategory;
            iter.getObject ()->getField (ifds::AcctCategory, dstrAcctCategory, idDataGroup, false);
            if(dstrAcctCategory == ACCOUNT_CATEGORY::EPA_APP )
            {
               bAcctCatEPAAppExist = true;
               break;
            }

            ++iter;
         }
      }

      bool bIsAccountNew = isNew();
      if ( DSTCommonFunctions::codeInList (acctType, I_("4,8,3")) || 
          !DSTCommonFunctions::codeInList (acctTaxType, I_("0,1,V") ) )
      {
         //corporate, trust, estate account won't be allowed to use add EPA APP(57)
         bAcctCatNotAllowed = true; 
      }
      else
      {
         if ( DSTCommonFunctions::codeInList (acctTaxType, I_("1,V") ) && 
              dstrEPABroker == I_("Y") && 
              acctDesignation == CLIENT_ACCT_DESIGNATION)
         {
            if ( ( acctTaxType == I_("V") && 
                   DSTCommonFunctions::codeInList (I_("57"),tfsaAcctCatCodeList )) || //TFSA
                 ( acctTaxType == I_("1") && 
                   DSTCommonFunctions::codeInList (I_("57"),rrspAcctCatCodeList )) )  // RRSP
            {
               bAcctCatNotAllowed = false;
            }
         }
         else
         {
            if( acctTaxType == I_("0") && bIsAccountNew &&
                dstrEPABroker == I_("Y") && 
                acctDesignation == CLIENT_ACCT_DESIGNATION )
            {
               // new non-register account will be allowed to have 'EPA App'
               // as account category
               bAcctCatNotAllowed = false;
            }
            else
            {
               bAcctCatNotAllowed = true;
            }
         }
      }

      if( bAcctCatNotAllowed && bAcctCatEPAAppExist )
      {
         // in case of changing broker, account designation or taxtype
         ADDCONDITIONFROMFILE( CND::ERR_ACCT_CATEGORY_NOT_ALLOWED_FOR_ACCOUNT );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY MFAccount::getFeeModelInfo (FeeModelList *&pFeeModelList, 
                                     const DString &dstrFeeModelCode,
                                     const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeModelInfo" ) );

   DString strKey = I_("FeeModelList") + dstrFeeModelCode;
   strKey.stripAll();

   pFeeModelList = dynamic_cast <FeeModelList*> (BFCBO::getObject (strKey, idDataGroup));

   if (!pFeeModelList)
   {

      pFeeModelList = new FeeModelList (*this);
      pFeeModelList->init (dstrFeeModelCode, idDataGroup); 

      if (pFeeModelList)
      {
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
         {
            setObject (pFeeModelList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
         }
         else
         {
            delete pFeeModelList;
            pFeeModelList = NULL;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getDefaultPaymentTypeInfo( const DString &strTradeType,
                                               const DString &strFundCode,
                                               const DString &strClassCode,
                                               DString &strPaymentType,
                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDefaultPaymentTypeInfo" ) );

   DString strAcctPaymentType = NULL_STRING;

   DString dstrCurrBusDate;
   getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false ); 

   AcctControlRecordList *pAcctControlRecordList = NULL;

   if( getAcctControlRecordList(pAcctControlRecordList, 
                                I_("30"),
                                strFundCode,
                                strClassCode,
                                dstrCurrBusDate, // effective date
                                dstrCurrBusDate, // stop date,
								ACCOUNT_TYPE_RULE,
                                idDataGroup ) <= WARNING && 
      pAcctControlRecordList )
   {
      BFObjIter iter (*pAcctControlRecordList, idDataGroup);
      iter.begin();

      // pick only first one, regardless effective or stopdate, or fund/class
      if (!iter.end ())
      {
         DString dstrOverrideChar;
         iter.getObject ()->getField (ifds::OverrideChar, dstrOverrideChar, idDataGroup, false);
         dstrOverrideChar.strip().upperCase();

         strAcctPaymentType = dstrOverrideChar;
      }
   }

   if( !strAcctPaymentType.empty())
   {
      strPaymentType = strAcctPaymentType;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getAcctControlRecordList( AcctControlRecordList *&pAcctControlRecordList,
                                              const DString &strRuleType,
                                              const DString &strFundCode,
                                              const DString &strClassCode,
                                              const DString &strEffectiveDate,
                                              const DString &strStopDate,
											  const DString &strInquiryType,
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAcctControlRecordList" ) );

   DString strKey = I_("AcctControlRecordList=") + strRuleType + I_(";");
   strKey += I_("FundCode=") + strFundCode + I_(";");
   strKey += I_("ClassCode=") + strClassCode;
   strKey.stripAll();

   pAcctControlRecordList = dynamic_cast <AcctControlRecordList*> (BFCBO::getObject (strKey, idDataGroup));

   if (!pAcctControlRecordList)
   {
      DString strAccountNum;
      getField( ifds::AccountNum, strAccountNum, idDataGroup, false );
      pAcctControlRecordList = new AcctControlRecordList (*this);
      pAcctControlRecordList->init (strAccountNum, 
                                    idDataGroup,
                                    strEffectiveDate,
									strStopDate,
									strInquiryType,
                                    strRuleType,
                                    strFundCode,
                                    strClassCode); 

      if (pAcctControlRecordList)
      {
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
         {
            setObject (pAcctControlRecordList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
         }
         else
         {
            delete pAcctControlRecordList;
            pAcctControlRecordList = NULL;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getLatestAmendmentYearOfOwnerSeq01( DString& dstrLatestAmendYear, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDofBirthofOwnerSeq01" ) );

   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );

   if( pAccountEntityXref != NULL )
   {
      DString dstrEntityId ( I_("-1"));
      GetEntityIdForAcctOwnerSeq1( idDataGroup, dstrEntityId );
      dstrEntityId.stripLeading( '0' );

      if( dstrEntityId != I_("-1") )
      {
         Entity *pEntity;
         dstrEntityId.stripLeading( '0' );

         if( dstrEntityId != NULL_STRING )
         {
            getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
            if( pEntity )
            {
               pEntity->getField( ifds::TFSALastAmendTaxYear, dstrLatestAmendYear, idDataGroup, false );
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getBenefDeathSettlementDate(const DString& strLinkEntityID,DString& strDeathSettleDate,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getBenefDeathSettlementDate" ) );
   
   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );

   if( pAccountEntityXref != NULL )
   {
      DString dstrEntityId ( strLinkEntityID );
      dstrEntityId.stripLeading( '0' );

      if( dstrEntityId != I_("-1") && dstrEntityId != NULL_STRING && !dstrEntityId.empty())
      {
         Entity *pEntity;

         getWorkSession().getEntity( idDataGroup, strLinkEntityID, pEntity );
         if( pEntity )
         {
            pEntity->getField( ifds::DeathSettlementDate, strDeathSettleDate, idDataGroup, false );
         }
      }
   }
      
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::getDofDeathofEntityType( const DString& dstrEntityType, DString& dstrDofDeath, const BFDataGroupId& idDataGroup ) //Modified function name for INC0033364
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDofDeathofEntityType" ) ); //Modified function name for INC0033364
   
   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );

   DString dstrAcctNum;
   getField ( ifds::AccountNum, dstrAcctNum, idDataGroup);
   
   if( pAccountEntityXref != NULL )
   {
      DString dstrEntityId ( I_("-1"));
      //GetEntityIdForEntityTypeSeq1( dstrEntityType, idDataGroup, dstrEntityId );
	  pAccountEntityXref->GetEntityIdForEntityType( dstrAcctNum, dstrEntityType,idDataGroup, dstrEntityId );//Modified for INC0033364
      dstrEntityId.stripLeading( '0' );

      if( dstrEntityId != I_("-1") )
      {
         Entity *pEntity;
         dstrEntityId.stripLeading( '0' );

         if( dstrEntityId != NULL_STRING )
         {
            getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
            if( pEntity )
            {
               pEntity->getField( ifds::DofDeath, dstrDofDeath, idDataGroup, false );
            }
         }
      }
   }   
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY  MFAccount::GetEntityIdForEntityTypeSeq1( const DString& entityType, const BFDataGroupId& idDataGroup, DString& entityId )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "GetEntityIdForEntityTypeSeq1" ) );
   
   DString dstrAcctNum;
   getField ( ifds::AccountNum, dstrAcctNum, idDataGroup);
   AccountEntityXref *pAccountEntityXref = NULL;
   SEVERITY sevRtn = getAccountEntityXref( pAccountEntityXref, idDataGroup );
   if( pAccountEntityXref != NULL )
   {
      pAccountEntityXref->GetEntityIdForEntityType( dstrAcctNum, entityType, I_("1"), idDataGroup, entityId );
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}


//********************************************************************************
SEVERITY MFAccount::getProdPortfolioPlanInfoList (ProdPortfolioPlanInfoList*& pProdPortfolioPlanInfoList,
                                                  const DString& prodPortfolioUUID,
                                                  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getProdPortfolioPlanInfoList" ) );

   DString acctGroup;

   getField (ifds::AcctGroup, acctGroup, idDataGroup, false);
   if ( isPortfolioRequired (idDataGroup) && 
        !acctGroup.empty() && 
        !prodPortfolioUUID.empty())
   {
      DString strKey = I_("AcctGroup=") + acctGroup + 
                       I_("ProdPortfolioUUID=") + prodPortfolioUUID;

      strKey.stripAll();
      pProdPortfolioPlanInfoList = dynamic_cast <ProdPortfolioPlanInfoList*> (BFCBO::getObject (strKey, idDataGroup));
      if (!pProdPortfolioPlanInfoList)
      {
         pProdPortfolioPlanInfoList = new ProdPortfolioPlanInfoList (*this);
         pProdPortfolioPlanInfoList->init (prodPortfolioUUID, idDataGroup); 
         if (pProdPortfolioPlanInfoList)
         {
            if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
            {
               setObject (pProdPortfolioPlanInfoList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
            }
            else
            {
               delete pProdPortfolioPlanInfoList;
               pProdPortfolioPlanInfoList = NULL;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY MFAccount::getProdPortfolioInfoList (ProdPortfolioInfoList*& pProdPortfolioInfoList,
                                              const BFDataGroupId& idDataGroup,
                                              bool bViewCall)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getProdPortfolioInfoList" ) );

   DString acctGroup;

   getField (ifds::AcctGroup, acctGroup, idDataGroup, false);
   if (isPortfolioRequired (idDataGroup) && !acctGroup.empty())
   {
      DString strKey = I_("ProdPortfolioInfoList;");
      addIDITagValue(strKey, I_("AcctGroup"), acctGroup);
      strKey.stripAll();

      pProdPortfolioInfoList = dynamic_cast <ProdPortfolioInfoList*> (BFCBO::getObject (strKey, idDataGroup));

      if (!pProdPortfolioInfoList || bViewCall)
      {
         pProdPortfolioInfoList = new ProdPortfolioInfoList (*this);
         pProdPortfolioInfoList->init (acctGroup, idDataGroup); 

         if (pProdPortfolioInfoList)
         {
            if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
            {
               setObject (pProdPortfolioInfoList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
            }
            else
            {
               delete pProdPortfolioInfoList;
               pProdPortfolioInfoList = NULL;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::validatePortfolioField(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validatePortfolioField" ) );

   if ( isPortfolioRequired (idDataGroup) &&
       (isFieldUpdated (ifds::ProdPortfolioUUID, idDataGroup) ||
        isFieldUpdated (ifds::ProdPortfolioPlanUUID, idDataGroup)) )
   {
      TransactionList *pTransactionList = NULL;
      PendingTradeList *pPendingTradesList = NULL;

      bool bAccountHasTrade = false;

      if( getTransactionsList(pTransactionList,idDataGroup, true) <= WARNING && 
          pTransactionList != NULL )
      {
         BFObjIter iter( *pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

         if( iter.getNumberOfItemsInList() > 1 || !iter.end())
         {
            bAccountHasTrade = true;
         }
      }

      if( !bAccountHasTrade && 
         getPendingTradesList(pPendingTradesList,idDataGroup) <= WARNING && 
         pPendingTradesList != NULL )
      {
         BFObjIter iter( *pPendingTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

         if( iter.getNumberOfItemsInList() > 1 || !iter.end())
         {
            bAccountHasTrade = true;
         }
      }

      if(bAccountHasTrade)
      {
         // Account has either processed or pending trade, raise up error
         ADDCONDITIONFROMFILE( CND::ERR_UNABLE_TO_CHANGE_ACCT_PORTFOLIO );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool MFAccount::canSetupTaxExemptProvincial(const BFDataGroupId& idDataGroup)
{
   /*
      As comment from Nitin (BA), the account that could be considered to be Non-Taxable.
      It must be IWT client, Tax Juris must be in the Tax Juris list from Generic Controls.      
      If this method returns as true, that means the IWT is applicable.
   */
   bool bCanSetupTaxExemptProvincial = false;
   DString dstrIWTTaxJurisList, dstrEntityId ( I_("-1"));
   Entity *pEntity = NULL;
   AccountEntityXref *pAccountEntityXref = NULL;

   if( getWorkSession().isIWTClient( idDataGroup ) )
   {
      getWorkSession().getOption( ifds::IWTTaxJurisList, dstrIWTTaxJurisList, idDataGroup, false );
      dstrIWTTaxJurisList.strip().upperCase();

      // get Account Entity
      getAccountEntityXref( pAccountEntityXref, idDataGroup );
      
      GetEntityIdForAcctOwnerSeq1( idDataGroup, dstrEntityId );
      dstrEntityId.stripLeading( '0' );

      if( dstrEntityId != I_("-1") )
      {
         dstrEntityId.stripLeading( '0' );

         if( dstrEntityId != NULL_STRING )
         {
            getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
            if( pEntity )
            {
               //IN2766093: Account tax jurisdiction Prim-Mstr.TaxJuris is the field used for Tax Jurisdiction
               DString dstrTaxJurisCode, dstrShrNum;
               getField (ifds::ShrNum, dstrShrNum, idDataGroup);
               Shareholder *pShareholder = NULL;

               if ( getWorkSession().getShareholder (idDataGroup, dstrShrNum, pShareholder) <= WARNING &&
                  pShareholder)
               {
                  pShareholder->getField (ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup);
                  dstrTaxJurisCode.strip().upperCase();
               }

               // check TaxJuris in list.
               bCanSetupTaxExemptProvincial = DSTCommonFunctions::codeInList ( dstrTaxJurisCode, dstrIWTTaxJurisList );         
            }
         }
      }
   }

   return bCanSetupTaxExemptProvincial;
}
//******************************************************************************
bool MFAccount::isIWTNonTaxable(const BFDataGroupId& idDataGroup)
{
   /*
      As Nitin comment, the Non-Taxable account is the account 
      that has TaxExemp 'Provincial' setup or TaxType = 'X'.
   */
   bool bIsIWTNonTaxable  = false;
   DString dstrTaxExType;
   
   if( getWorkSession().isIWTClient( idDataGroup ) )
   {

      // if the account can setup TaxExempt that means account could be the Non-Taxable
      if( canSetupTaxExemptProvincial( idDataGroup ) )
      {
         DString dstrTaxType;
         getField(ifds::TaxType, dstrTaxType, idDataGroup, false);
         dstrTaxType.strip().upperCase();

         if( dstrTaxType == I_("X") )
         {
            bIsIWTNonTaxable = true;               
         }
         else
         {
            // for others taxtypes, could be Non-Taxable if there is tax exempt 'Provincial' setup.
            DString dstrAccountNum;
            getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );

            TaxExemptAuthorizationList* pTaxExemptAuthorizationList = NULL;
            getTaxExemptAuthorizationList( pTaxExemptAuthorizationList, dstrAccountNum, idDataGroup );

            BFObjIter iter( *pTaxExemptAuthorizationList, idDataGroup );
            iter.begin();
            while( !iter.end() )
            {
               TaxExemptAuthorization* pTaxExemptAuthorization = NULL;
               pTaxExemptAuthorization = dynamic_cast<TaxExemptAuthorization*>( iter.getObject() );
               pTaxExemptAuthorization->getField( ifds::TaxExType, dstrTaxExType, idDataGroup, false );
               dstrTaxExType.strip().upperCase();

               if ( dstrTaxExType == I_("PROV") )
               {
                  bIsIWTNonTaxable = true;
                  break;
               }
               ++iter;
            }
         }
 
      }
   
   }

   return bIsIWTNonTaxable;
}

//******************************************************************************
bool MFAccount::hasGIAHolding(const BFDataGroupId& idDataGroup)
{
   DString dstrHasGIAHolding;

   getField(ifds::HasGIAHolding, dstrHasGIAHolding, idDataGroup, false);
   dstrHasGIAHolding.strip();

   return dstrHasGIAHolding == I_("Y") ? true : false;
}

//******************************************************************************
bool MFAccount::hasSegFundsWithinPortfolio (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("hasSegFundWithinPortfolio"));
   bool bHasSegFund = false;
   
   ProdPortfolioInfoList* pProdPortfolioInfoList (NULL);
   
   if ( getProdPortfolioInfoList (pProdPortfolioInfoList, idDataGroup) <= WARNING && 
        pProdPortfolioInfoList)
   {
      DString prodPortfolioUUID;

      getField (ifds::ProdPortfolioUUID, prodPortfolioUUID, idDataGroup, false);      
      if (!prodPortfolioUUID.empty())
      {
         bHasSegFund = pProdPortfolioInfoList->hasPortfolioSegFunds (prodPortfolioUUID, idDataGroup);
      }
   }
   return bHasSegFund;
}

//******************************************************************************
bool MFAccount::isCommitmentApplicable (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("hasSegFundWithinPortfolio"));
   bool bIsCommitmentApplicable = false;
   
   ProdPortfolioInfoList* pProdPortfolioInfoList (NULL);
   
   if ( getProdPortfolioInfoList (pProdPortfolioInfoList, idDataGroup) <= WARNING && 
        pProdPortfolioInfoList)
   {
      DString prodPortfolioUUID;

      getField (ifds::ProdPortfolioUUID, prodPortfolioUUID, idDataGroup, false);      
      if (!prodPortfolioUUID.empty())
      {
         bIsCommitmentApplicable = pProdPortfolioInfoList->isCommitmentApplicable (prodPortfolioUUID, idDataGroup);
      }
   }
   return bIsCommitmentApplicable;
}

//******************************************************************************
bool MFAccount::isPortfolioRequired (const BFDataGroupId &idDataGroup)
{
   DString dstrPorfolioIsRequried;
   getWorkSession().getOption (ifds::PorfolioIsRequried, dstrPorfolioIsRequried, idDataGroup, false);

   return dstrPorfolioIsRequried == YES;
}

//********************************************************************************
SEVERITY MFAccount::getMasterContractListByPortfolio( MasterContractList *&pMasterContractList,
                                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterContractListByPortfolio" ) );

   DString dstrGroupCode,
      dstrProdPortfolioUUID;
      
   getField(ifds::AcctGroup, dstrGroupCode, idDataGroup, false);
   getField(ifds::ProdPortfolioUUID, dstrProdPortfolioUUID, idDataGroup, false);

   if (isPortfolioRequired (idDataGroup) &&
       dstrGroupCode != NULL_STRING && 
       dstrProdPortfolioUUID != NULL_STRING)
   {
      DString strKey = NULL_STRING;
      strKey  = I_("MasterContractList_PortfolioUUID=");
      strKey += dstrProdPortfolioUUID;
      strKey += I_(";");

      pMasterContractList = dynamic_cast <MasterContractList*> (getObject (strKey, idDataGroup));

      ProdPortfolioInfoList* pProdPortfolioInfoList (NULL);
      getProdPortfolioInfoList (pProdPortfolioInfoList,idDataGroup);

      DString* pStrProdPortfolioCode = new DString;
      pProdPortfolioInfoList->getPortfolioCodebyPortfolioUUID(dstrProdPortfolioUUID,
                                                              pStrProdPortfolioCode,
                                                              idDataGroup);

      if (!pMasterContractList)
      {
         pMasterContractList = new MasterContractList (*this);

         if (pMasterContractList->initWithPortfolio (dstrGroupCode, *pStrProdPortfolioCode) <= WARNING)
         //if (pMasterContractList->initWithPortfolio (dstrGroupCode, dstrProdPortfolioUUID) <= WARNING)
         {
            setObject (pMasterContractList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
         }
         else
         {
            delete pMasterContractList;
            pMasterContractList = NULL;
         }
      }

      delete pStrProdPortfolioCode;
      pStrProdPortfolioCode = NULL;
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************************************
bool MFAccount:: validateSubOrgType( const BFDataGroupId& idDataGroup )
{
   DString dstrSubOrgType, dstrSubOrgTypeOld,dstrERISAProhibitedFund ;
   getField (ifds::SubOrgType, dstrSubOrgType, idDataGroup);
   getFieldBeforeImage (ifds::SubOrgType, dstrSubOrgTypeOld);
   dstrSubOrgType.strip();
   dstrSubOrgTypeOld.strip();

   if( dstrSubOrgType == I_("02") && (dstrSubOrgTypeOld == I_("01") || dstrSubOrgTypeOld == I_("03")) )
   {
      MFAccountHoldingList *pMFAccountHoldingList = NULL;
      getAccountHoldingList( pMFAccountHoldingList, idDataGroup );
      if(pMFAccountHoldingList)
      {
         pMFAccountHoldingList->getField (ifds::hasERISAProhibitedFund, dstrERISAProhibitedFund, idDataGroup, false);
      }
   }

   return (dstrERISAProhibitedFund == YES);
}

//**************************************************************************************
inline bool MFAccount::isERISAAccount ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("isERISAAccount"));
   DString dstrSubOrgType;
   getField ( ifds::SubOrgType, dstrSubOrgType, idDataGroup );
   return ( dstrSubOrgType.strip() == I_("02") );
}

//**************************************************************************************
SEVERITY MFAccount::getAlertMessageList(const DString &dstrFromScreen, AlertMessageList *&pAlertMessageList, const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAlertMessagesList")); 

    DString dstrEffectiveDate;
    getWorkSession().getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrEffectiveDate, idDataGroup, false);

    DString dstrKey = I_("AlertMessageList;FromScreen=") + dstrFromScreen + I_(";EffectiveDate=") + dstrEffectiveDate;
    pAlertMessageList = dynamic_cast<AlertMessageList*>(getObject(dstrKey, idDataGroup));

    if (!pAlertMessageList && !isNew())
    {
        DString dstrAccountNum;
        getField(ifds::AccountNum, dstrAccountNum, idDataGroup );

        pAlertMessageList = new AlertMessageList(*this);

        if (pAlertMessageList->init(dstrAccountNum, dstrEffectiveDate, dstrFromScreen) <= WARNING && pAlertMessageList)
        {
            setObject(pAlertMessageList, dstrKey, OBJ_ACTIVITY_NONE, BF::HOST);
        } 
        else
        {
            delete pAlertMessageList;
            pAlertMessageList = NULL;
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool MFAccount::isAlertMessageExists(const DString &dstrFromScreen, const BFDataGroupId& idDataGroup)
{
    AlertMessageList *pAlertMessageList = NULL;

    if (getAlertMessageList(dstrFromScreen, pAlertMessageList, idDataGroup) <= WARNING && pAlertMessageList)
    {
        BFObjIter iterRemarkAlerts(*pAlertMessageList, idDataGroup);
        return iterRemarkAlerts.getNumberOfItemsInList() > 0;
    }

    return false;
}

//******************************************************************************
bool MFAccount::isRemarkAlertExists(const DString &dstrFromScreen, const BFDataGroupId& idDataGroup)
{
    AlertMessageList *pAlertMessageList = NULL;

    if (getAlertMessageList(dstrFromScreen, pAlertMessageList, idDataGroup) <= WARNING && pAlertMessageList)
    {
        BFObjIter iterRemarkAlerts(*pAlertMessageList, idDataGroup);

        while (!iterRemarkAlerts.end())
        {
            DString dstrAlertCode;
            iterRemarkAlerts.getObject()->getField(ifds::AlertCode, dstrAlertCode, idDataGroup, false);
            
            if (dstrAlertCode == ALERT_MSG_CODE::REMARK_ALERT)
                return true;

            ++iterRemarkAlerts;
        }
    }

    return false;
}

//******************************************************************************
SEVERITY MFAccount::getIDOfSequenced01OfEntityObject( const DString& idType, const DString& entityType, DString& idValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getIDOfSequenced01OfEntityObject" ) );	

   DString _entityId;
   GetEntityIdForEntityTypeSeq1( entityType, idDataGroup, _entityId );

   Entity* pEntityOut = NULL;
   getWorkSession().getEntity( idDataGroup, _entityId, pEntityOut );
   if(pEntityOut)
   {
      EntityIdsList* pEntityIdsList = NULL;
      pEntityOut->getEntityIdsList (pEntityIdsList, idDataGroup);

      if (pEntityIdsList)
      {
         BFObjIter iter ( *pEntityIdsList, 
            idDataGroup, 
            false, 
            BFObjIter::ITERTYPE::NON_DELETED);

         while (!iter.end ())
         {
            DString dstrIdType;
            EntityIds *pEntityIds= dynamic_cast <EntityIds*> (iter.getObject ());
            if (pEntityIds)
            {
               pEntityIds->getField (ifds::IdType, dstrIdType, idDataGroup,false);
               if (dstrIdType.strip().upperCase() == idType)
               {
                  pEntityIds->getField (ifds::IdValue, idValue, idDataGroup,false);
                  break;
               }
            }
            ++iter;
         }
      }
   }
   else
   {
      idValue = NULL_STRING;
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//***************************************************************************
SEVERITY MFAccount::isNonRegNonResident(DString &dstrNonRegNonResident, 
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isNonRegNonResident"));

   DString dstrTaxJuris;
   DString dstrTaxType;
   DString dstrShrNum;
   Shareholder *pShareholder = NULL;

   dstrNonRegNonResident = I_("N");

   getField (ifds::ShrNum, dstrShrNum, idDataGroup);
   getField (ifds::TaxType, dstrTaxType, idDataGroup);

    if (getWorkSession ().getShareholder (idDataGroup, dstrShrNum, pShareholder) <= WARNING &&
        pShareholder) 
    {
       pShareholder->getField (ifds::TaxJurisCode, dstrTaxJuris, idDataGroup);    
       dstrTaxJuris.strip ();

       if (!dstrTaxJuris.empty () && getWorkSession().isNonRegLike (dstrTaxType))
       {
          // check if Canadian resident:
          DString dstrResidency1, dstrResidency2, dstrResidency3;

          getWorkSession().getOption (ifds::Residency1, dstrResidency1, idDataGroup, false);
          getWorkSession().getOption (ifds::Residency2, dstrResidency2, idDataGroup, false);
          getWorkSession().getOption (ifds::Residency3, dstrResidency3, idDataGroup, false);

          if (!( DSTCommonFunctions::codeInList (dstrTaxJuris, dstrResidency1) ||
                 DSTCommonFunctions::codeInList (dstrTaxJuris, dstrResidency2) ||
                 DSTCommonFunctions::codeInList (dstrTaxJuris, dstrResidency3) ) ||
               dstrTaxJuris == UNASSIGNED_TAX_JURIS)
          {
             dstrNonRegNonResident = I_("Y");
          }
          else
          {
             dstrNonRegNonResident = I_("N");
          }
       }
    }

    return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MFAccount::validateIASlsRepForEmployeeAgent(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
      CLASSNAME, 
      I_("validateIASlsRepForEmployeeAgent"));

   //P0186486FN09 - Employee and Agent Account Gap#8A
   //Employee/Agent account is not allowed to change reps
   Shareholder *pShareholder = NULL;
   if (getShareholder (pShareholder, idDataGroup) <= WARNING && 
      pShareholder )
   {
      DString acctDesignation,
         slsRepcode,
         slsRepcodePre,
         fundRelCode;


      pShareholder->getField (ifds::FundRelnCode, fundRelCode, idDataGroup);
      fundRelCode.strip();

      getField (ifds::AcctDesignation, acctDesignation, idDataGroup);
      getField( ifds::Slsrep, slsRepcode, idDataGroup );
      slsRepcode.strip().upperCase();

      getField( ifds::Slsrep, slsRepcodePre, BF::HOST );
      slsRepcodePre.strip().upperCase();

      if(!isNew() && (slsRepcode != slsRepcodePre))
      {
         if(acctDesignation == CLIENT_ACCT_DESIGNATION && 
            (fundRelCode == EMPLOYEE || fundRelCode == AGENT))
         {
            DString strIDI;
            if(fundRelCode == EMPLOYEE)
            {
               addIDITagValue( strIDI, I_("ACCOUNT_TYPE"), I_("Employee") );
            }
            else
            {
               addIDITagValue( strIDI, I_("ACCOUNT_TYPE"), I_("Agent") );
            }

            getErrMsg ( IFASTERR::CHANGE_REPS_IS_NOT_APPLICABLE,
                        CND::ERR_CHANGE_REPS_IS_NOT_APPLICABLE, 
                        CND::WARN_CHANGE_REPS_IS_NOT_APPLICABLE, 
                        idDataGroup,
                        strIDI);
         }
      }//---
   } 

   return GETCURRENTHIGHESTSEVERITY ();

}

/*******************************************************************************
Input:BFDataGroupID.
PutPut:None
Return:bool
Functionality:Call the function to see if the Account is of Tax Type Related 
              to reg agent
*******************************************************************************/
bool MFAccount::bIsTaxTypeRelatedtoRegAgent (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("bIsTaxTypeRelatedtoRegAgent"));
   DString dstrRegAgentCode;
   getField (ifds::RegAgentCode, dstrRegAgentCode, idDataGroup);
   dstrRegAgentCode.strip ().upperCase (); 
   return(!dstrRegAgentCode.empty());
}

//******************************************************************************
SEVERITY MFAccount::validateBlockTransfer( const DString& brokerCode, 
                                           const DString& branchCode,
                                           const DString& slsRep, 
                                           const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBlockTransfer" ) );	

   DString serviceAgentUpdated;

   getField( ifds::ServiceAgentUpdated, serviceAgentUpdated, idDataGroup );

   if (!isNew () && serviceAgentUpdated != I_("Y"))
   {
      DString accountNum;

      getField( ifds::AccountNum, accountNum, idDataGroup, false);
      accountNum.strip().upperCase();

      FundSERVBrokerValidation fundSERVBrokerValidation(*this);
      DString brokerCodeHost, 
         branchCodeHost,
         slsRepHost;

      getFieldBeforeImage( ifds::BrokerCode, brokerCodeHost);
      getFieldBeforeImage( ifds::BranchCode, branchCodeHost);
      getFieldBeforeImage( ifds::Slsrep,slsRepHost);
      brokerCodeHost.strip().upperCase();
      branchCodeHost.strip().upperCase();
      slsRepHost.strip().upperCase();

      if( fundSERVBrokerValidation.init(I_("ServiceAgent"),
                                          accountNum,
                                          brokerCodeHost,
                                          branchCodeHost,
                                          slsRepHost,
                                          brokerCode,
                                          branchCode,
                                          slsRep)<= WARNING)
      {
         // no data broker error but it might some result return
         DString warnCode;
         fundSERVBrokerValidation.getField( ifds::WarnCode, warnCode, idDataGroup, false );
         warnCode.strip().upperCase();

         if(warnCode.asInteger() == 1296 )
         {
            // IN# 3124545 - aditional logic on service agent
            // 1. changing from FundServ agent to non-FundServ and 
            //    current service agent is same with compensate agent
            //    error message, service agent must be change via 
            //    compensation sceen

            getErrMsg( IFASTERR::SRVCE_AGENT_BELONGS_TO_FUNDSERV_BROKER, 
                       CND::ERR_SRVCE_AGENT_BELONGS_TO_FUNDSERV_BROKER, 
                       CND::WARN_SRVCE_AGENT_BELONGS_TO_FUNDSERV_BROKER, 
                       idDataGroup);
         }
         else if(warnCode.asInteger() == 1246 )
         {
            getErrMsg( IFASTERR::COMPENSATION_AGENT_MUST_BE_CHANGED, 
                       CND::ERR_COMPENSATION_AGENT_MUST_BE_CHANGED, 
                       CND::WARN_COMPENSATION_AGENT_MUST_BE_CHANGED, 
                       idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::validateSalesrepFund( const DString& dstrBroker,
                                          const DString& dstrBranch,
                                          const DString& dstrSlsRep,
                                          const DString& dstrFund, 
                                          const DString& dstrClass, 
                                          const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSalesrepFund"));
   
   AgentList agentList ( *this );
   
   //if( dstrFund.empty() || dstrClass.empty() )
   //{
   //   GETCURRENTHIGHESTSEVERITY ();
   //}
   
   DString dstrAccountNum,
      dstrValidationPassed;
   getField( ifds::AccountNum,dstrAccountNum, idDataGroup, false);
   dstrAccountNum.strip().upperCase();
   
   if( agentList.init2( dstrBroker, 
                        dstrBranch, 
                        dstrSlsRep, 
                        dstrFund, 
                        dstrClass, 
                        dstrAccountNum ) <= WARNING )
   {
      BFObjIter iterAgent( agentList, idDataGroup );

      iterAgent.begin();
      if( !iterAgent.end() )
      {
         iterAgent.getObject()->getField( ifds::ValidationPassed, dstrValidationPassed, idDataGroup,false );
         
         if (dstrValidationPassed != YES)
         {
            DString idiStr;
            addIDITagValue( idiStr, FUND, dstrFund );
            addIDITagValue( idiStr, CLASS, dstrClass );
            addIDITagValue( idiStr, I_("AGENT"), dstrSlsRep );

            ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP, idiStr );
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
SEVERITY MFAccount::validationStopAdjustmentDate(const DString& strValue,const BFDataGroupId& idDataGroup)
{
   //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validationStopAdjustmentDate" ) );  

   DString dstrStopAdjDate(strValue), 
      dstrEffectiveDate,
      dstrEffectiveDateUnfmt, 
      dstrStopAdjDateUnfmt;

   DSTCommonFunctions::UnformatDate( dstrStopAdjDate, dstrStopAdjDateUnfmt);
   getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
   DSTCommonFunctions::UnformatDate( dstrEffectiveDate, dstrEffectiveDateUnfmt);

   if(  !dstrStopAdjDateUnfmt.strip().empty() &&
      !dstrEffectiveDateUnfmt.strip().empty() &&
      ( DSTCommonFunctions::CompareDates( dstrStopAdjDateUnfmt , dstrEffectiveDateUnfmt) == 
      DSTCommonFunctions::FIRST_EARLIER )
      )
   {
      ADDCONDITIONFROMFILE( CND::ERR_STOP_ADJDATE_GREATER_THAN_EFFECTIVEDATE);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::refreshShareholder(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "refreshShareholder" ) );  
   Shareholder *pShareholder = NULL;
   if( getShareholder( pShareholder, idDataGroup ) <= WARNING  && 
       pShareholder )
   {
      RemarksList* pRemarksList = NULL;

      if( pShareholder->getRemarksList(pRemarksList, idDataGroup) < WARNING &&
          pRemarksList)
      {
         pRemarksList->refreshMe (true); //refresh remark directly
         const bool isNeedRemarkRefresh = pRemarksList->needsRefresh(idDataGroup);

         if(isNeedRemarkRefresh)
         {
            BFObjIter iter (*pShareholder, idDataGroup);
            
            iter.setKeyFilter(I_("RemarksList"), true);
            if (!iter.end ())
            {
               iter.removeObjectFromMap (true);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getAgeOfSequenced01OfEntityObject( const DString& entityType, 
                                                       DString& ageInYear,
                                                       DString& ageInMnth, 
                                                       const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAgeOfSequenced01OfEntityObject" ) );

   DString _entityId;
   GetEntityIdForEntityTypeSeq1( entityType, idDataGroup, _entityId );

   Entity* pEntityOut = NULL;
   getWorkSession().getEntity( idDataGroup, _entityId, pEntityOut );
   if(pEntityOut)
   {
      DString strDofBirth,
         strCurrBusDate,
         date_yr, 
         date_mo;

      pEntityOut->getField (ifds::DofBirth, strDofBirth, idDataGroup, false);
      getWorkSession().getOption(ifds::CurrBusDate, strCurrBusDate, idDataGroup, false ); 
      strDofBirth.strip().upperCase();
      strCurrBusDate.strip().upperCase();

      DSTCommonFunctions::BuildAge (strDofBirth, strCurrBusDate, ageInYear, ageInMnth);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getAcctOwnershipAllocationList(AcctOwnershipAllocationList *&pAcctOwnershipAllocationList,
                                                   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAcctOwnershipAllocationList" ) );
   
   if(!isNew())
   {
      DString strKey = I_("AcctOwnershipAllocationList");
      pAcctOwnershipAllocationList = dynamic_cast<AcctOwnershipAllocationList*>(getObject (strKey, idDataGroup));

      if(!pAcctOwnershipAllocationList)
      {
         pAcctOwnershipAllocationList = new AcctOwnershipAllocationList(*this);
         
         DString strAccountNum;
         getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
         strAccountNum.strip().upperCase();
         if( pAcctOwnershipAllocationList->init(strAccountNum,idDataGroup) <= WARNING )
         {
            setObject (pAcctOwnershipAllocationList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);   
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
DString MFAccount::getMgmtFeePayOptOvdSetup(const BFDataGroupId& idDataGroup)
{
	DString dstrMgmtFeePayOptOvd,bResult;
	bResult = I_("");
	getWorkSession().getMgmtCoOptions()->getField(ifds::MgmtFeePayOptOvd, dstrMgmtFeePayOptOvd, idDataGroup, false);
	if (isNew() && dstrMgmtFeePayOptOvd != I_("") && dstrMgmtFeePayOptOvd != NULL_STRING)
	{
		bResult = dstrMgmtFeePayOptOvd;
		//setFieldReadOnly( ifds::MgmtFeePayOption, idDataGroup, true );
	}
   return bResult;
}

//******************************************************************************
bool MFAccount::hasAcctOwnershipAllocationRecord(const BFDataGroupId& idDataGroup)
{
   bool bResult = false;

   AcctOwnershipAllocationList* pAcctOwnershipAllocationList = NULL;
   if( getAcctOwnershipAllocationList(pAcctOwnershipAllocationList, idDataGroup ) <= WARNING &&
       pAcctOwnershipAllocationList )
   {
      BFObjIter bfIter( *pAcctOwnershipAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      
      int iNumItems = bfIter.getNumberOfItemsInList (); 

      bResult = (iNumItems >= 1) ? true : false;
   }

   return bResult;
}
/**************************************************************************************
Input:IdType to check ,BFDataGroupID
Output:bool IDExists return true if a match found
Return:SEVERITY
Functionality:Call the function to check if an ID exists,using an MFAccount obj
/*******************************************************************************************/
SEVERITY MFAccount::checkIdForAccOwner(const DString &dstrCheckIDType,bool &bIDExists,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkUniqueIdPresentForAccOwner" ) );
   ENTITIES_VECTOR acctOwnerEntities;
   getAcctOwnerEntities (acctOwnerEntities, idDataGroup); 
   int iNumOfEntities = acctOwnerEntities.size();

   for (int i = 0; i < iNumOfEntities; ++i)
   {

      DString dstrEntityId;
      dstrEntityId = acctOwnerEntities[i];	
      Entity *pEntity = NULL;
      if ( getWorkSession().getEntity ( idDataGroup, 
         dstrEntityId, 
         pEntity) <= WARNING &&
         pEntity)
      {
         EntityIdsList *pEntityIdsList = NULL;

         if ( pEntity->getEntityIdsList (pEntityIdsList, BF::HOST /*idDataGroup*/) <= WARNING &&
            pEntityIdsList)
         {
            bIDExists = pEntityIdsList->bCheckIdTypeExistsInDB( dstrCheckIDType );
         }
      }
      if(bIDExists)
         break;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

/**************************************************************************************
Input:DataGroup ID
Output:bool bDisplyWarnSICAV and bDisplyWarnOEIC returns true if it is SICAV or OEIC environment
Return:SEVERITY
Functionality:Call the function to return true for SICAV or OEIC environemnt if unique Id exists for an account
//*************************************************************************************************************/
SEVERITY MFAccount::displayEnvXrefWarningOnUpdate(const BFDataGroupId& idDataGroup,bool &bDisplyWarnSICAV,bool &bDisplyWarnOEIC)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "displayEnvXrefWarningOnUpdate(" ) );

   ErrMsgRulesList *pErrMsgRulesList = NULL;
   bDisplyWarnSICAV = false ;
   bDisplyWarnOEIC  = false;
   if ( getWorkSession().getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
      NULL != pErrMsgRulesList )
   {
      DString dstrErrValueSICAV,dstrErrValueOEIC;	 
      pErrMsgRulesList->getEWIValue (IFASTERR::DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV, idDataGroup, dstrErrValueSICAV);
      pErrMsgRulesList->getEWIValue (IFASTERR::DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC, idDataGroup, dstrErrValueOEIC);
      dstrErrValueSICAV.strip().upperCase();
      dstrErrValueOEIC.strip().upperCase();
      if ((I_("W") == dstrErrValueSICAV.strip().upperCase()||
         I_("W") == dstrErrValueOEIC.strip().upperCase() ) )
      {
         bool bIDExists = false;
         ENTITIES_VECTOR vIDList;
         vIDList.push_back(IDS::FAST);
         vIDList.push_back(IDS::iFAST_SICAV);
         vIDList.push_back(IDS::iFAST_OEIC);
         int idListSize = vIDList.size(); 
         while(idListSize)
         {
            idListSize--;
            checkIdForAccOwner(vIDList[idListSize],bIDExists,idDataGroup);
            if(bIDExists)
            {
               (dstrErrValueSICAV.strip() == I_("W") ? bDisplyWarnSICAV :bDisplyWarnOEIC) =true ;
               break;
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void MFAccount::initializeSubstitutionList( const BFFieldId& idField, 
                                            const DString &dstrGroupCode, 
                                            const BFDataGroupId& idDataGroup)
{
   TranslationTable* pTranslationTable = NULL;
   DString dstrAvailableList, dstrSubstitutionList;

   getMgmtCo().getTranslationTable (dstrGroupCode, pTranslationTable);

   if (pTranslationTable)
   {
      pTranslationTable->getCodeList(dstrAvailableList);
      loadSubstitutionList(idField, idDataGroup, dstrAvailableList );
   }
}

//******************************************************************************
SEVERITY MFAccount::setFieldFromModelAcct(const BFFieldId& idField, 
							const BFDataGroupId& idDataGroup, 
							MFAccount *pMFAccountModel, 
							bool readOnly,
							bool validateNow)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFieldFromModelAcct" ) );

	DString tmpStr;

	pMFAccountModel->getField(idField, tmpStr, idDataGroup, false);

	if (validateNow)
	{
		setField(idField, tmpStr, idDataGroup, false);
	}
	else
	{
		setFieldNoValidate(idField, tmpStr, idDataGroup, false, false, true);
	}

	setFieldReadOnly(idField, idDataGroup, readOnly);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool MFAccount::isAccountAttachedAMSC(const BFDataGroupId& idDataGroup)
{
	if (isAMSAccount(idDataGroup))
	{
		DString dstrAMSCode, dstrCurrBuss, dstrTradeViaParent;
        AMSMstrList *pAMSMstrList = NULL;
		AmsMstrInfo *pAMSMstrInfo = NULL;

		getField(ifds::AMSCode, dstrAMSCode, idDataGroup);
		getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBuss, idDataGroup, false );
		
		if (dstrAMSCode != NULL_STRING && 
			getAMSMstrList( pAMSMstrList, idDataGroup, dstrCurrBuss ) <= WARNING && pAMSMstrList)
		{
			pAMSMstrList->getAMSMstrInfo(I_("RB"), dstrAMSCode, dstrCurrBuss, pAMSMstrInfo, idDataGroup);

			if (pAMSMstrInfo)
			{
				return pAMSMstrInfo->isAMSC(idDataGroup);
			}
		}
	}

	return false;
}

//******************************************************************************
SEVERITY MFAccount::getAnnuitantYoungerAge( DString &dstrAnnuitantYoungerAge, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAnnuitantYoungerAge" ) );   

   getField ( ifds::AnnuitantYoungerAge, dstrAnnuitantYoungerAge, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool MFAccount::hasBlankAnnuitantGender(const BFDataGroupId& idDataGroup)
{
	DString dstrEntityId, dstrAnnuitantGender;
	ACCTENTITYOBJ_VECTOR v_annuitants;
	ACCTENTITYOBJ_VECTOR::iterator v_iter;
	Entity *pEntity = NULL;
	bool bHasBlankAnnuitantGender = false;

	getAnnitants (v_annuitants, idDataGroup);
	int iNumOfAnnuitants = v_annuitants.size();
	for (int i = 0; i < iNumOfAnnuitants; ++i)
	{
		dynamic_cast <AccountEntityXrefObject*>(v_annuitants[i])->getField (ifds::EntityId, dstrEntityId, idDataGroup);
		if ( getWorkSession().getEntity ( idDataGroup, dstrEntityId, pEntity) <= WARNING && pEntity)
		{
			pEntity->getGender( dstrAnnuitantGender, idDataGroup );
			if (dstrAnnuitantGender.empty())
				bHasBlankAnnuitantGender = true;
		}
	}

	return bHasBlankAnnuitantGender;
}

//******************************************************************************
bool MFAccount::isSingle( const BFDataGroupId& idDataGroup )
{
   DString acctType;
   getField( ifds::AcctType, acctType, idDataGroup );

   return(acctType == INDIVIDUAL_ACCT_TYPE);
}

//******************************************************************************
SEVERITY MFAccount::getAcctRegDetailsList(AcctRegDetailsList *&pAcctRegDetailsList,   
										  const BFDataGroupId &idDataGroup,
										  const DString &dstrComplyRule)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAcctRegDetailsList")); 

	DString dstrKey = I_("AcctRegDetailsList");
	pAcctRegDetailsList = dynamic_cast <AcctRegDetailsList*>(getObject(dstrKey, idDataGroup));

	if( !pAcctRegDetailsList)
	{
		DString dstrAccountNum;
		getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );

		pAcctRegDetailsList = new AcctRegDetailsList( *this );
		if (!isNew())
		{
			pAcctRegDetailsList->init(dstrAccountNum , dstrComplyRule);
		}

		if( pAcctRegDetailsList )
		{
			if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			{
				setObject( pAcctRegDetailsList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
			}
			else
			{
				delete pAcctRegDetailsList;
				pAcctRegDetailsList = NULL;
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MFAccount::getEntityRegDetailsList(EntityRegDetailsList *&pEntityRegDetailsList,   
				   						    const DString &dstrEntityId,
										    const BFDataGroupId &idDataGroup,
											bool inquireDatabase /*= true*/)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityRegDetailsList")); 

	DString dstrAccountNum;
	getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );

	//DString dstrKey = I_("EntRegDetails_Account=") + dstrAccountNum + I_("_EntityId=") + dstrEntityId;
	DString dstrKey = I_("EntityRegDetailsList");
	pEntityRegDetailsList = dynamic_cast <EntityRegDetailsList*>(getObject(dstrKey, idDataGroup));

	if( !pEntityRegDetailsList )
	{
		BFDataGroupId idWorkingDataGroup = idDataGroup;

		if (isNew())
		{
			pEntityRegDetailsList = new EntityRegDetailsList( *this );
			pEntityRegDetailsList->setField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
			pEntityRegDetailsList->initNew();
		}
		else if( inquireDatabase )
		{
			pEntityRegDetailsList = new EntityRegDetailsList( *this );
			idWorkingDataGroup = BF::HOST;
			pEntityRegDetailsList->setField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
			pEntityRegDetailsList->init(dstrAccountNum , dstrEntityId);
		}

		if( pEntityRegDetailsList )
		{
			if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			{				
				setObject( pEntityRegDetailsList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
			}
			else
			{
				delete pEntityRegDetailsList;
				pEntityRegDetailsList = NULL;
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MFAccount::getEntityRegJurisDetailsList(EntityRegJurisDetailsList *&pEntityRegJurisDetailsList,   
 												 const DString &dstrEntityId,
												 const BFDataGroupId &idDataGroup,
												 bool inquireDatabase /*= true*/)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityRegJurisDetailsList")); 

	DString dstrAccountNum;
	getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );

	//DString dstrKey = I_("EntRegJurisDetails_Account=") + dstrAccountNum + I_("_EntityId=") + dstrEntityId;
	DString dstrKey = I_("EntityRegJurisDetailsList");	
	pEntityRegJurisDetailsList = dynamic_cast <EntityRegJurisDetailsList*>(getObject(dstrKey, idDataGroup));

	if( !pEntityRegJurisDetailsList )
	{
		BFDataGroupId idWorkingDataGroup = idDataGroup;

		if (isNew())
		{
			pEntityRegJurisDetailsList = new EntityRegJurisDetailsList( *this );
			pEntityRegJurisDetailsList->setField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
			pEntityRegJurisDetailsList->initNew();
		}
		else if( inquireDatabase )
		{
			pEntityRegJurisDetailsList = new EntityRegJurisDetailsList( *this );
			idWorkingDataGroup = BF::HOST;
			pEntityRegJurisDetailsList->setField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
			pEntityRegJurisDetailsList->init(dstrAccountNum , dstrEntityId);
		}

		if( pEntityRegJurisDetailsList )
		{
			if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			{
				setObject( pEntityRegJurisDetailsList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
			}
			else
			{
				delete pEntityRegJurisDetailsList;
				pEntityRegJurisDetailsList = NULL;
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MFAccount::getAccountLvlEntityRegJurisDetailsList(EntityRegJurisDetailsList *&pEntityRegJurisDetailsList,   
								   						   const DString &dstrAccountNum,
														   const DString &dstrEntityId,
														   const DString &dstrFATCACode,
														   const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAccountLvlEntityRegJurisDetailsList")); 


	//DString dstrKey = I_("Account=") + dstrAccountNum + I_("_EntityId=") + dstrEntityId + I_("_FATCACode=") + dstrFATCACode;	
	DString dstrKey = I_("AccountEntityRegJurisDetailsList");	
	pEntityRegJurisDetailsList = dynamic_cast <EntityRegJurisDetailsList*>(getObject(dstrKey, idDataGroup));

	if( !pEntityRegJurisDetailsList )
	{
		pEntityRegJurisDetailsList = new EntityRegJurisDetailsList( *this );

		if (!isNew())
		{
            pEntityRegJurisDetailsList->setField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
			pEntityRegJurisDetailsList->init(dstrAccountNum , dstrEntityId, dstrFATCACode);
		}

		if( pEntityRegJurisDetailsList )
		{
			if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			{
				setObject( pEntityRegJurisDetailsList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
			}
			else
			{
				delete pEntityRegJurisDetailsList;
				pEntityRegJurisDetailsList = NULL;
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getFinInstRegDetlList(FinInstRegDetlList *&pFinInstRegDetlList,
                                          const DString &dstrComplyRule, 
                                          const BFDataGroupId& idDataGroup, 
                                          bool bCreate,
                                          const DString& dstrTrack,
                                          const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFinInstRegDetlList") );

   getMgmtCo().getFinInstRegDetlList(dstrComplyRule,pFinInstRegDetlList);

   //DString dstrAcctNum, dstrKey, dstrAcctDesignation, dstrBrokerCode, dstrInterCode;
   //BFDataGroupId idWorkingDataGroup = idDataGroup;

   //getField(ifds::AccountNum, dstrAcctNum, idDataGroup);
   //getField(ifds::AcctDesignation, dstrAcctDesignation, idDataGroup);
   //getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup);
   //getField(ifds::InterCode, dstrInterCode, idDataGroup);

   //dstrKey = I_("FinInstRegDetlList_") + dstrComplyRule;

   //pFinInstRegDetlList = NULL;
   //pFinInstRegDetlList = dynamic_cast<FinInstRegDetlList*>(BFCBO::getObject(dstrKey, idDataGroup));

   //if ( !pFinInstRegDetlList && bCreate )
   //{
   //   pFinInstRegDetlList = new FinInstRegDetlList( *this );
   //   //do a database inquiry
   //   if (pFinInstRegDetlList->init(idDataGroup, 
   //                                 dstrComplyRule, 
   //                                 dstrAcctNum , 
   //                                 dstrAcctDesignation,
   //                                 dstrBrokerCode, 
   //                                 dstrInterCode,
   //                                 bReadAll,
   //                                 dstrTrack, 
   //                                 dstrPageName) > WARNING )
   //   {
   //      delete pFinInstRegDetlList;
   //      pFinInstRegDetlList = NULL;
   //   }
   //   else
   //   {
   //      //if (bReadAll)
   //      //{
   //      //   while (pFinInstRegDetlList->doMoreRecordsExist( ))
   //      //   {
   //      //   }
   //      //}
   //      setObject(pFinInstRegDetlList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup);
   //   }
   //}

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::validateBrokerChangeForDocList(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBrokerChangeForDocList"));

	DString dstrBrokerCode, dstrOrigBrokerCode, dstrEPABroker, dstrOrigEPABroker, dstrRegulatoryStandard;
	Broker *pBroker = NULL;
	Broker *pOrigBroker = NULL;
	Demographics *pDemographics = NULL;

	getFieldBeforeImage(ifds::BrokerCode, dstrOrigBrokerCode);
	getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup);

	if (!isNew() && getDemographicsList (pDemographics, idDataGroup) <= WARNING && pDemographics &&
		getBroker(pOrigBroker, dstrOrigBrokerCode, idDataGroup) <= WARNING && pOrigBroker &&
		getBroker(pBroker, dstrBrokerCode, idDataGroup) <= WARNING && pBroker)
	{
		pOrigBroker->getField(ifds::EPABroker, dstrOrigEPABroker, idDataGroup);
		pBroker->getField(ifds::EPABroker, dstrEPABroker, idDataGroup);
		pDemographics->getField(ifds::RegulatoryStandard, dstrRegulatoryStandard, idDataGroup);

		dstrOrigEPABroker.strip().upperCase();	
		dstrEPABroker.strip().upperCase();	

		if (dstrRegulatoryStandard != NULL_STRING && dstrOrigEPABroker != dstrEPABroker)
		{
			getErrMsg(IFASTERR::REG_DOC_STATUS_NEEDS_TO_BE_MANUALLY_UPDATED, 
				CND::ERR_REGULATORY_DOC_STATUS_NEEDS_TO_BE_MANUALLY_UPDATED, 
				CND::WARN_REGULATORY_DOC_STATUS_NEEDS_TO_BE_MANUALLY_UPDATED, 
				idDataGroup);
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MFAccount::validateBrokerChangeForTrailerFee(const DString& dstrBrokerCode,
                                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBrokerChangeForTrailerFee"));

   DString dstrOrigBrokerCode, dstrNewBrokerCode, dstrTFRExists, dstrTFRApplicable;

   //getFieldBeforeImage(ifds::BrokerCode, dstrOrigBrokerCode);
   dstrNewBrokerCode = dstrBrokerCode;
   getField(ifds::BrokerCode, dstrOrigBrokerCode, BF::HOST);
   getField(ifds::TFRExists, dstrTFRExists, idDataGroup);
   dstrOrigBrokerCode.strip().upperCase();
   dstrNewBrokerCode.strip().upperCase();

   getWorkSession().getOption(ifds::TFRApplicable, dstrTFRApplicable, idDataGroup, false);

   if (dstrTFRApplicable.stripAll().upperCase() == YES &&
       dstrTFRExists.stripAll().upperCase() == YES && 
       dstrOrigBrokerCode != dstrNewBrokerCode)
   {
      getErrMsg(IFASTERR::ACCOUNT_ATTATCHED_TFR_NEED_TO_BE_STOPPED, 
                CND::ERR_ACCOUNT_ATTATCHED_TFR_NEED_TO_BE_STOPPED, 
                CND::WARN_ACCOUNT_ATTATCHED_TFR_NEED_TO_BE_STOPPED,
                idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool MFAccount::hasAMSTrades(const BFDataGroupId& idDataGroup)
{
   bool retVal = false;
   
	MFAccountHoldingList*  pMFAccountHoldingList;
   getAccountHoldingList( pMFAccountHoldingList,idDataGroup );
	if( pMFAccountHoldingList ) 
   {
		if( pMFAccountHoldingList->hasNonAMSFunds(idDataGroup)) 
      {
         retVal = true;
      }
   }

   PendingTradeList *pPendingTradesList = NULL;
   
   if(!retVal && getPendingTradesList(pPendingTradesList, idDataGroup) <= WARNING && pPendingTradesList)
   {
		if(pPendingTradesList->hasNonAMSFunds(idDataGroup)) 
      {
         retVal = true;
      }
   }

	SystematicList* pSystematicList = NULL;
   
	if(!retVal && getSystematicList(  pSystematicList, BF::HOST , true) <= WARNING && pSystematicList ) 
   {
		if(pSystematicList->hasNonAMSFunds(idDataGroup)) 
      {
         retVal = true;
      }
   }

   return retVal;
};
/******************************************************************************
 Input: Acct Num ,BFDataGroupId
 OutPut:None
 Return:bool
 Functionality:Return true if the account is Omnibus
 ******************************************************************************/
bool MFAccount::isAccountOmnibus(DString& dstrAccountNum, const BFDataGroupId &idDataGroup)
{
  MFAccount *pMFAccount = NULL;
  DString dstrAcctType;
  dstrAccountNum.strip().stripLeading('0');
  if(!dstrAccountNum.empty())
  {      
   getField (ifds::SocialCode, dstrAcctType, idDataGroup);
  }
  return (OMNIBUS == dstrAcctType);
}
/******************************************************************************
 Input: Fund,Class,Date,BFDataGroupId
 OutPut:None
 Return:bool
 Functionality:Return true if the account has subsequent trades after the  
			   date for the input Fund and class in from or to side of the tarde
			   Pending,Processed.Systematic tardes placed will be in processed list
 ******************************************************************************/
bool MFAccount::accountHasTradeAfterDate(DString& dstrFund, DString& dstrClass, 
										 DString& dstrDate, const BFDataGroupId &idDataGroup)
{
  bool bTradeExists = false;
  DString dstrAccountNum, dstrTradedFromFund, dstrTradedFromClass, dstrTradedDate, dstrTradedStatus, dstrTransType,
	      dstrTradedToFund, dstrTradedToClass;
  dstrFund.upperCase();
  dstrClass.upperCase();
  DSTCommonFunctions::addDays(dstrDate, dstrDate, 1);//GetTradeDatePlusOne
  getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
  if(dstrFund.stripAll().empty()|| dstrClass.stripAll().empty() || dstrDate.stripAll().empty())
	  return bTradeExists;
  PendingTradeList lPendingTradesList(*this);
  if (lPendingTradesList.initSearch(I_("FundCode"),
									  dstrAccountNum,
   									  NULL_STRING , //const DString& strTransNum,
									  NULL_STRING , //const DString& strWireOrdNum, 
									  NULL_STRING , //const DString& strNetworkID, 
									  NULL_STRING , //const DString& strExtTransNum, 
									  NULL_STRING , //const DString& strSendRefNum,
									  NULL_STRING , //const DString& strMasterRefNum, 
									  NULL_STRING , //const DString& strPartRefNum,
									  dstrDate, //const DString& strFromDate, 
									  NULL_STRING , //const DString& strToDate,
									  NULL_STRING ,// const DString& strExternalIdType,
									  NULL_STRING , //const DString& strExternalId,
									  NULL_STRING , //const DString& strNSCCControlNumber,
									  I_("N") , //const DString& rebook,
									  I_("N"),//const DString& dstrTrack,
									  NULL_STRING , //const DString& dstrPageName,
									  dstrFund,//const DString& dstrFundCode,
									  dstrClass,//const DString& dstrClassCode,
									  I_("ALL") )//const DString& dstrTransType 
									  <=WARNING)
	{
		//setObject( pPendingTradesList, PENDING_LIST, OBJ_ACTIVITY_NONE, idDataGroup );
		BFObjIter iter(lPendingTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		BFAbstractCBO *pCurrEntry  = NULL;
		while (!iter.end()&& !bTradeExists)
		{
		pCurrEntry = iter.getObject(); 
		pCurrEntry->getField( ifds::GoodBad, dstrTradedStatus, idDataGroup);
		if(YES == dstrTradedStatus) //if trade is marked as good only ,then report
		{
			bTradeExists = true;
		}//if trade status
		++iter;
		}//while  end of pendign trade check
	}

	if( !bTradeExists )
	{
		TransactionList lTransactionList(*this);
		DString dstrCancelled ;
		if( lTransactionList.initSearch( I_("FundCode") ,//const DString& strSearchType,
											dstrAccountNum, //const DString& strAccountNum,
											NULL_STRING , //const DString& strTransNum,
											NULL_STRING , //const DString& strWireOrdNum, 
                  					        NULL_STRING , //const DString& strNetworkID, 
                  					        NULL_STRING , //const DString& strExtTransNum, 
                   					        NULL_STRING ,//const DString& strSendRefNum,
                   					        NULL_STRING ,//const DString& strMasterRefNum, 
                   					        NULL_STRING ,//const DString& strPartRefNum,
											dstrDate ,	 //const DString& strFromDate, 
											NULL_STRING, //const DString& strToDate,
					 						NULL_STRING, //const DString& strExternalIdType,
											NULL_STRING, //const DString& strExternalId,
											NULL_STRING, //const DString& strAltAccount,
											NULL_STRING, //const DString& strFundIDType,
											NULL_STRING, //const DString& strFundIDValue,
											I_("ALL"),   //const DString& strTransType,
											NULL_STRING, //const DString& strUnits,
											NULL_STRING, //const DString& strNSCCControlNumber,
											NULL_STRING, //const DString& strTradeDate
											dstrFund,	 //const DString& strFundCode 
											dstrClass,   //const DString& strClassCode 
										    I_("N"),	 //const DString& AllFundMode 
											NULL_STRING, //const DString& TradeStatus 
											NULL_STRING, //const DString&   EUSDScope
											NULL_STRING, //const DString& ReportingCurrency
											I_("Y"),	 //const DString& ExcludeReversal
											I_("Y"),     //const DString& ExcludeCancelled 
											I_("N"),     //const DString& dstrTrack
											NULL_STRING ) //const DString& dstrPageName 
											<= WARNING )
		{
			BFObjIter iter(lTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
			BFAbstractCBO *pCurrEntry  = NULL;
			while (!iter.end()&& !bTradeExists)
			{
			 bTradeExists = true ;
			 ++iter;
			}
		}
	} //processsed trades  
  return bTradeExists;
}
/******************************************************************************
Input:Field ID ,DataGroupID
OutPut:
Return:Severity
Functionality:Append a blank value to sub list
******************************************************************************/
void  MFAccount::addBlankToSubSet(const BFFieldId &idField ,const BFDataGroupId &idDataGroup, bool dstrUseNotApplicableAsDesc /*= false */ )
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
}
//******************************************************************************
SEVERITY MFAccount::validateServiceOnlySlsRep(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateServiceOnlySlsRep"));

	DString slsRepType;
	getField( ifds::SlsrepType, slsRepType, idDataGroup );
	slsRepType.stripAll().upperCase();

	if ( isNew() && slsRepType == I_("S") )
	{
		getErrMsg ( IFASTERR::SERVICE_ONLY_SALES_REP,
					CND::ERR_SERVICE_ONLY_SALES_REP,
					CND::WARN_SERVICE_ONLY_SALES_REP,
					idDataGroup,
					NULL_STRING);
	}

	return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
void MFAccount::setDefaultAggregationType ( const DString dstrAggrType,const BFDataGroupId& idDataGroup ) 
{

  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setDefaultAggregationType"));
  
  setFieldNoValidate( ifds::AggregationType, dstrAggrType, idDataGroup ); 
  setFieldUpdated(ifds::AggregationType, idDataGroup, true); 
}
//******************************************************************************
SEVERITY MFAccount::getAccountLevelCOA( COANavig*& pCOANavig, const DString& dstrAcctNum,const BFDataGroupId& idDataGroup, bool bForceRefresh /* = false*/) 
{

  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAccountLevelCOA"));

  if( bForceRefresh &&  _pCOANavig)
  {
    delete _pCOANavig;
    _pCOANavig =NULL;
    return GETCURRENTHIGHESTSEVERITY ();
  }
  if(! _pCOANavig )
  {
    //DString dstrDate;
    //getWorkSession().getOption( ifds::CurrBusDate, dstrDate, idDataGroup, false );
    pCOANavig = new COANavig(*this);
    pCOANavig->init(dstrAcctNum,I_("N"),NULL_STRING);
    _pCOANavig = pCOANavig;
  }  
  pCOANavig = _pCOANavig;
  return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
bool MFAccount::isRegDocumentsOutStanding( const DString& dstrEntityId,
                                           const DString& dstrComplyRule,
                                           const BFDataGroupId& idDataGroup,	
                                           bool bCreate /*= true*/,
								           bool bAcctRegDocListForDeadEntity /*= false*/)
{
    RegDocumentList* pRegDocumentList = NULL;
    bool bRegDocumentOutStanding = false;
    DString  dstrRegStandard = NULL_STRING;
    Demographics *pDemographics (NULL);

    //find the regulatory standard, get this from the demographics object for applicable comply rules.
    if (getDemographicsList (pDemographics, idDataGroup) <= WARNING && 
        pDemographics && ( dstrComplyRule == COMPLY_RULE::AccountholderRisk || dstrComplyRule == COMPLY_RULE::AcctRegistration) )
            pDemographics->getField (ifds::RegulatoryStandard, dstrRegStandard, idDataGroup);

    if( getRegDocumentsList( pRegDocumentList, dstrEntityId, dstrComplyRule, dstrRegStandard, idDataGroup, bCreate, 
                             bAcctRegDocListForDeadEntity) <= WARNING && 
                             pRegDocumentList)
    {
       BFObjIter bfIter( *pRegDocumentList, idDataGroup );
	    bfIter.begin();
       DString dstrDocStatus;
       if(!bfIter.getNumberOfItemsInList())
          bRegDocumentOutStanding = false;
       while(!bfIter.end() && !bRegDocumentOutStanding)
       {
          bfIter.getObject()->getField( ifds::RegDocStatus, dstrDocStatus, idDataGroup);
          if( I_("O") == dstrDocStatus.upperCase())
              bRegDocumentOutStanding = true;
          ++bfIter;
       }
    }
    return bRegDocumentOutStanding;
}

//******************************************************************************
SEVERITY MFAccount::getBrokerFundAllow(const DString& dstrFundCode, 
                                       const DString& dstrClassCode,
                                       BrokerList *&pBrokerList,
                                       const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBrokerFundAllow"));

    DString dstrAcctNum, dstrBrokerCode;
    DString tmpFundCode(dstrFundCode), tmpClassCode(dstrClassCode);

    getField(ifds::AccountNum, dstrAcctNum, idDataGroup, false);
    getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup);

    pBrokerList = NULL;

    if (!dstrBrokerCode.empty() && !dstrFundCode.empty() && 
        !dstrClassCode.empty() && !dstrAcctNum.empty())
    {
        DString objKey = I_("BrokerList;") + 
                         dstrAcctNum + I_(";") + 
                         dstrBrokerCode + I_(";") + 
                         tmpFundCode.upperCase() + I_(";") + 
                         tmpClassCode.upperCase() + I_(";");

        pBrokerList = dynamic_cast<BrokerList*>(getObject(objKey, idDataGroup));

	    if (!pBrokerList)
        {
            pBrokerList = new BrokerList(*this);

            if (pBrokerList->initFundAllowed(dstrBrokerCode, dstrFundCode, dstrClassCode, dstrAcctNum) <= WARNING && pBrokerList)
            {
                setObject(pBrokerList, objKey, OBJ_ACTIVITY_NONE, idDataGroup);
            }
            else 
            {
                delete pBrokerList;
                pBrokerList = NULL;
            }
        }
    }

    return GETHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::getAgentFundAllow(const DString& dstrFundCode,
                                      const DString& dstrClassCode,
                                      AgentList *&pAgentList,
                                      const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAgentFundAllow"));

    DString dstrBrokerCode, dstrBranchCode, dstrSlsRepCode, dstrAcctNum;
    DString tmpFundCode(dstrFundCode), tmpClassCode(dstrClassCode);

    getField(ifds::AccountNum, dstrAcctNum, idDataGroup, false);
    getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup);
    getField(ifds::BranchCode, dstrBranchCode, idDataGroup);
    getField(ifds::Slsrep, dstrSlsRepCode, idDataGroup);

    pAgentList = NULL;

    if (!dstrBrokerCode.empty() && !dstrBranchCode.empty() && 
        !dstrSlsRepCode.empty() && !dstrFundCode.empty() && 
        !dstrClassCode.empty() && !dstrAcctNum.empty())
    {
        DString objKey = I_("AgentList;") + 
                         dstrAcctNum + I_(";") + 
                         dstrBrokerCode + I_(";") + 
                         dstrBranchCode + I_(";") + 
                         dstrSlsRepCode + I_(";") + 
                         tmpFundCode.upperCase() + I_(";") + 
                         tmpClassCode.upperCase() + I_(";");

        pAgentList = dynamic_cast<AgentList*>(getObject(objKey, idDataGroup));

	    if (!pAgentList)
        {
            pAgentList = new AgentList(*this);

            if (pAgentList->init2(dstrBrokerCode, 
                                  dstrBranchCode, 
                                  dstrSlsRepCode, 
                                  dstrFundCode, 
                                  dstrClassCode, 
                                  dstrAcctNum) <= WARNING && pAgentList)
            {
                setObject(pAgentList, objKey, OBJ_ACTIVITY_NONE, idDataGroup);
            }
            else 
            {
                delete pAgentList;
                pAgentList = NULL;
            }
        }
    }

    return GETHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::validateToFundClassAgainstFundEligible(const DString& dstrFundCode,
                                                           const DString& dstrClassCode,
                                                           const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateToFundClassAgainstFundEligible")); 

    DString dstrBrokerFund, dstrFundEligSlsRepLvl, dstrBrokerCode, dstrBranchCode, dstrSlsRepCode;
    BrokerList *brokerList = NULL;
    AgentList *agentList = NULL;

    getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup);
    getField(ifds::BranchCode, dstrBranchCode, idDataGroup);
    getField(ifds::Slsrep, dstrSlsRepCode, idDataGroup);

    if (!dstrFundCode.empty() && !dstrClassCode.empty())
    {
        getWorkSession().getOption(ifds::BrokerFund, dstrBrokerFund, idDataGroup, false);
        getWorkSession().getOption(ifds::FundEligSlsRepLvl, dstrFundEligSlsRepLvl, idDataGroup, false);

        if (dstrBrokerFund == Y &&
            getBrokerFundAllow(dstrFundCode, dstrClassCode, brokerList, idDataGroup) <= WARNING && brokerList)
        {
            DString dstrFundAllowed;
            BFObjIter iter(*brokerList, idDataGroup);

            if (!iter.end())
            {
                iter.getObject()->getField(ifds::FundAllow, dstrFundAllowed, idDataGroup, false);
            }

            if (dstrFundAllowed != Y)
            {
                DString idiStr;
                addIDITagValue(idiStr, I_("FUND"), dstrFundCode);
                addIDITagValue(idiStr, I_("CLASS"), dstrClassCode);
                addIDITagValue(idiStr, I_("BROKER_CODE"), dstrBrokerCode);

                getErrMsg(IFASTERR::BROKER_IS_NOT_ELIGIBLE_FOR_FUND_CLASS,
                          CND::ERR_BROKER_IS_NOT_ELIGIBLE_FOR_FUND_CLASS,
                          CND::WARN_BROKER_IS_NOT_ELIGIBLE_FOR_FUND_CLASS,
                          idDataGroup,
                          idiStr);
            }
        }
        else if (dstrFundEligSlsRepLvl == Y &&
                 getAgentFundAllow(dstrFundCode, dstrClassCode, agentList, idDataGroup) <= WARNING && agentList)
        {
            DString dstrValidationPassed;
            BFObjIter iterAgent(*agentList, idDataGroup);

            if (!iterAgent.end())
            {
                iterAgent.getObject()->getField(ifds::ValidationPassed, dstrValidationPassed, idDataGroup,false);
            }

            if (dstrValidationPassed != Y)
            {
                DString idiStr;
                addIDITagValue(idiStr, I_("FUND"), dstrFundCode);
                addIDITagValue(idiStr, I_("CLASS"), dstrClassCode);
                addIDITagValue(idiStr, I_("SLSREP_CODE"), dstrSlsRepCode);

                getErrMsg(IFASTERR::SALE_REP_IS_NOT_ELIGIBLE_FOR_FUND_CLASS,
                          CND::ERR_SALE_REP_IS_NOT_ELIGIBLE_FOR_FUND_CLASS,
                          CND::WARN_SALE_REP_IS_NOT_ELIGIBLE_FOR_FUND_CLASS,
                          idDataGroup,
                          idiStr);
            }
        }
    }

    return GETHIGHESTSEVERITY();
}

//********************************************************************************
bool MFAccount::hasTransTypePendingTrades( const DString &dstrTransType,
										   const DString &dstrAccountNum,
										   const DString &dstrFundCode,
										   const DString &dstrClassCode,
										   const BFDataGroupId &idDataGroup)
{
	bool bHasTransTypePendingTrades = false;
	DString strTradedStatus;

	PendingTradeList lPendingTradesList (*this); 

	if (lPendingTradesList.initSearch( I_(""),		   // strSearchType
									   dstrAccountNum, // strAccountNum
									   NULL_STRING ,   // strTransNum,
									   NULL_STRING ,   // strWireOrdNum, 
									   NULL_STRING ,   // strNetworkID, 
									   NULL_STRING ,   // strExtTransNum, 
									   NULL_STRING ,   // strSendRefNum,
									   NULL_STRING ,   // strMasterRefNum, 
									   NULL_STRING ,   // strPartRefNum,
									   NULL_STRING ,   // strFromDate, 
									   NULL_STRING ,   // strToDate,
									   NULL_STRING ,   // strExternalIdType,
									   NULL_STRING ,   // strExternalId,
									   NULL_STRING ,   // strNSCCControlNumber,
									   NULL_STRING ,   // rebook,
									   NULL_STRING ,   // dstrTrack,
									   NULL_STRING ,   // dstrPageName,
									   dstrFundCode,   // dstrFundCode,
									   dstrClassCode,  // dstrClassCode,
									   dstrTransType ) // dstrTransType 
									   <= WARNING )
	{		
		BFObjIter iter(lPendingTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		BFAbstractCBO *pCurrEntry  = NULL;

		while (!iter.end()&& !bHasTransTypePendingTrades)
		{
			pCurrEntry = iter.getObject();
			pCurrEntry->getField( ifds::GoodBad, strTradedStatus, idDataGroup);
			strTradedStatus.stripAll().upperCase();

			if (strTradedStatus == YES) // exclude bad trades
			{				
				bHasTransTypePendingTrades = true;
			}
			++iter;
		}
	}

	return bHasTransTypePendingTrades;
}

//********************************************************************************
bool MFAccount::hasTransTypeProccessedTrades( const DString &dstrTransType,
											  const DString &dstrAccountNum,
											  const DString &dstrFundCode,
											  const DString &dstrClassCode,
											  const BFDataGroupId &idDataGroup)
{
	bool bhasTransTypeProccessedTrades = false;
	DString strTradedStatus;

	TransactionList lTransactionList (*this); 

	if (lTransactionList.initSearch( I_("") ,		 // strSearchType,
									 dstrAccountNum, // strAccountNum,
									 NULL_STRING ,   // strTransNum,
									 NULL_STRING ,   // strWireOrdNum, 
									 NULL_STRING ,   // strNetworkID, 
									 NULL_STRING ,   // strExtTransNum, 
									 NULL_STRING ,   // strSendRefNum,
									 NULL_STRING ,	 // strMasterRefNum, 
									 NULL_STRING ,	 // strPartRefNum,
									 NULL_STRING,	 // strFromDate, 
									 NULL_STRING,	 // strToDate,
									 NULL_STRING,	 // strExternalIdType,
									 NULL_STRING,	 // strExternalId,
									 NULL_STRING,	 // strAltAccount,
									 NULL_STRING,	 // strFundIDType,
									 NULL_STRING,	 // strFundIDValue,
									 dstrTransType,  // strTransType,
									 NULL_STRING,	 // strUnits,
									 NULL_STRING,	 // strNSCCControlNumber,
									 NULL_STRING,	 // strTradeDate
									 dstrFundCode,   // strFundCode 
									 dstrClassCode,	 // strClassCode 
									 NULL_STRING,	 // AllFundMode 
									 NULL_STRING,	 // TradeStatus 
									 NULL_STRING,	 // EUSDScope
									 NULL_STRING,	 // ReportingCurrency
									 NULL_STRING,	 // ExcludeReversal
									 NULL_STRING,	 // ExcludeCancelled 
									 NULL_STRING,	 // dstrTrack
									 NULL_STRING )	 // dstrPageName 
									 <= WARNING )									 

	{		
		BFObjIter iter(lTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		BFAbstractCBO *pCurrEntry  = NULL;

		while (!iter.end())
		{				
			bhasTransTypeProccessedTrades = true;			
			break;
		}
	}

	return bhasTransTypeProccessedTrades;
}

//******************************************************************************
SEVERITY MFAccount::getAcctRoundingRuleList( AcctRoundingRuleList *&pAcctRoundingRuleList, 
                                             const BFDataGroupId& idDataGroup,
                                             bool bCreate)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAcctRoundingRuleList" ) );


	DString dstrAccountNum;
	getField( ifds::AccountNum, dstrAccountNum, idDataGroup );

	pAcctRoundingRuleList = dynamic_cast<AcctRoundingRuleList *>(getObject(I_( "AcctRoundingRuleList" ), idDataGroup ));

	if( !pAcctRoundingRuleList && bCreate)
	{
		BFDataGroupId idWorkingDataGroup = idDataGroup;
		pAcctRoundingRuleList = new AcctRoundingRuleList( *this );

		if( isNew() )
		{
			pAcctRoundingRuleList->initNew(dstrAccountNum, idDataGroup);
		}
		else
		{
			pAcctRoundingRuleList->init(dstrAccountNum, idDataGroup);
		}

		if (!isNew())
		{
			idWorkingDataGroup = BF::HOST;
		}

		if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
		{
			setObject( pAcctRoundingRuleList, I_( "AcctRoundingRuleList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
		}
		else
		{
			delete pAcctRoundingRuleList;
			pAcctRoundingRuleList = NULL;
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool MFAccount::hasAcctRoundingRule(const BFDataGroupId& idDataGroup)
{
	bool bResult = false;

	AcctRoundingRuleList* pAcctRoundingRuleList = NULL;
	if( getAcctRoundingRuleList (pAcctRoundingRuleList, idDataGroup ) <= WARNING &&	pAcctRoundingRuleList )
	{
		BFObjIter bfIter( *pAcctRoundingRuleList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

		int iNumItems = bfIter.getNumberOfItemsInList (); 

		bResult = (iNumItems >= 1) ? true : false;
	}

	return bResult;
}
//******************************************************************************
SEVERITY MFAccount::getDefaultOrderRoutingInfo( DString &dstrAcctOrderRouting,
													const DString &tradeDate,
													const BFDataGroupId& idDataGroup )
                                       
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDefaultOrderRoutingInfo" ) );

   AcctControlRecordList *pAcctControlRecordList = NULL;
	 
   DString dstrOverrideLogical = NULL_STRING,
	   dstrStartDate = NULL_STRING,
	   dstrStopDate = NULL_STRING;

   if( getAcctControlRecordList( pAcctControlRecordList,
                                            I_("80"),
											NULL_STRING,
											NULL_STRING,
											tradeDate,// effective date
											tradeDate, // stop date
											ORDER_ROUTING_RULE,
											idDataGroup) <= WARNING && 
      pAcctControlRecordList )
   {
      BFObjIter iter (*pAcctControlRecordList, idDataGroup);
      iter.begin();

	   if (!iter.end ())
	   {
		   iter.getObject() ->getField(ifds::EffectiveDate,dstrStartDate,idDataGroup,false);
		   iter.getObject() ->getField(ifds::StopDate,dstrStopDate,idDataGroup,false);
		   iter.getObject ()->getField (ifds::OverrideLogical, dstrOverrideLogical, idDataGroup, false);
		   dstrOverrideLogical.strip().upperCase();
	   }
   }


   if( !dstrOverrideLogical.empty() 
 	   && DSTCommonFunctions::IsDateBetween(dstrStartDate,dstrStopDate,tradeDate))
   {
	   dstrAcctOrderRouting = dstrOverrideLogical;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccount::validateAcctCustodian(const BFDataGroupId& idDataGroup)
{
	/* P0266360 HSBC Custodian */
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAcctCustodian"));
	Broker *pBroker = NULL;
	DString brokerCode;
	getField(ifds::BrokerCode, brokerCode, idDataGroup, false);
	if(getBroker(pBroker, brokerCode, idDataGroup) <= WARNING && pBroker) 
	{
		DString reqAcctCustodian;
		pBroker->getField(ifds::ReqAcctCustodian, reqAcctCustodian, idDataGroup, false);
		if(reqAcctCustodian == I_("Y"))
			getErrMsg(IFASTERR::PIM_INST_ACCT_MUST_BE_ADDED_TO_CUSTODIAN, 
					CND::ERR_PIM_INST_ACCT_MUST_BE_ADDED_TO_CUSTODIAN,
					CND::WARN_PIM_INST_ACCT_MUST_BE_ADDED_TO_CUSTODIAN, 
					idDataGroup);
	}
	return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
bool MFAccount::isRDSPAccount(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRDSPAccount"));

	DString taxType;

	getField(ifds::TaxType, taxType, idDataGroup, false);
	taxType.stripAll().upperCase();

	bool isRDSPAccount = (taxType == RDSP_TAX_TYPE) ? true : false;

	return isRDSPAccount;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MFAccount.cpp-arc  $
 * 
 * History:
 * 07-Mar-2014	Supareuk Sukjaitham P0221545 FN01 DFT0030180 T54906
 *              - Added a new field MgmtFeePayOptOvd
 *              - Recheck with the new task T54906
 *
 *    Rev 1.633   Aug 13 2012 00:16:34   popescu
 * IN2972860 - Cannot changes account status to death and death transfer.
 * 
 *    Rev 1.632   Aug 10 2012 17:58:28   kitticha
 * IN2972860 - Cannot changes account status to death and death transfer.
 * 
 *    Rev 1.631   Aug 09 2012 14:12:02   dchatcha
 * IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
 * 
 *    Rev 1.630   Jul 24 2012 19:02:38   dchatcha
 * P0179630 FN01 FATCA Project - Acct Ownership Allocation
 * 
 *    Rev 1.629   Jul 23 2012 12:29:52   wutipong
 * PETP0179630_FN01 FATCA Account Entity Document Tracking
 * 
 *    Rev 1.628   Jul 19 2012 23:23:14   popescu
 * Synch up: IN# 2994672 - Block Service Unit Transfers, simplified logic that let account cbo update b\b\s
 * 
 *    Rev 1.627   Jul 12 2012 10:30:34   dchatcha
 * Synch up: IN# 2994672 - Block Service Unit Transfers, simplified logic that let account cbo update b\b\s
 * 
 *    Rev 1.626   Jul 09 2012 19:31:24   dchatcha
 * Synch up : IN# 2994672 - Block Service Unit Transfers.
 * 
 *    Rev 1.625   Jun 05 2012 11:39:10   dchatcha
 * IN#2969458- Bypass  the editing for age difference if the new "Guarantees Override" flag set as "Yes"
 * 
 *    Rev 1.624   Jun 04 2012 09:28:46   if991250
 * CPF: PAC
 * 
 *    Rev 1.623   May 21 2012 14:15:02   dchatcha
 * P0186479 FN10 -Gap 14G - Block Service Unit Transfers, revise code.
 * 
 *    Rev 1.622   May 18 2012 15:21:24   dchatcha
 * P0186479 FN10 -Gap 14G - Block Service Unit Transfers, revise code.
 * 
 *    Rev 1.621   May 17 2012 18:00:58   popescu
 * Incident 2957242 - remove the validation for block service unit transfer - for new account.
 * 
 *    Rev 1.620   May 16 2012 05:01:40   panatcha
 * P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
 * 
 *    Rev 1.619   May 14 2012 16:23:38   dchatcha
 * P0186479 FN10 -Gap 14G - Block Service Unit Transfers.
 * 
 *    Rev 1.618   May 14 2012 04:53:44   panatcha
 * P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
 * 
 *    Rev 1.617   May 14 2012 15:40:36   dchatcha
 * P0186479 FN10 -Gap 14G - Block Service Unit Transfers.
 * 
 *    Rev 1.616   May 11 2012 10:06:40   if991250
 * CPF - account settlement currency
 * 
 *    Rev 1.615   May 04 2012 11:45:20   wp040039
 * PETP0187485 - Trade Entry And Processing
 * 
 *    Rev 1.614   Apr 25 2012 09:56:58   if991250
 * added loadSettleCurrencySubstitutionList
 * 
 *    Rev 1.613   Apr 19 2012 06:01:40   wutipong
 * IN2845929 - Contract Info List not update
 * 
 *    Rev 1.612   Apr 18 2012 10:10:40   dchatcha
 * Synch up: IN# 2918245 - Portfolio keep display error after update on any field on account information screen, cross edit field is not field information list then validation logic was skipped.
 * 
 *    Rev 1.611   Apr 16 2012 17:28:22   if991250
 * CPF Account Setup
 * 
 *    Rev 1.610   Apr 14 2012 11:38:08   panatcha
 * P0186486FN09 - Employee and Agent Account Gap#8A
 * 
 *    Rev 1.609   Apr 12 2012 10:38:52   dchatcha
 * Synch up: IN# 2918245 - Portfolio keep display error after update on any field on account information screen.
 * 
 *    Rev 1.608   Apr 11 2012 14:38:28   jankovii
 * Sync up: IN 2898233 - R12.3-P0186477-Enable manual tax calculation of money out transactions for NR
 * 
 *    Rev 1.607   Apr 10 2012 05:07:48   panatcha
 * P0186486FN09 - Employee and Agent Account Gap#8A
 * 
 *    Rev 1.606   Apr 03 2012 22:59:06   panatcha
 * IN2766093 - IWT TIN Warning Message
 * 
 *    Rev 1.605   Mar 30 2012 11:31:12   jankovii
 * IN 2898233 - R12.3-P0186477-Enable manual tax calculation of money out transactions for NR
 * 
 *    Rev 1.604   Mar 16 2012 17:45:58   wp040100
 * P0186484 FN05 - Contract Maturity Instruction Changes
 * 
 *    Rev 1.603   Mar 08 2012 12:36:04   jankovii
 * Sync up: IN 2859411 - P0186477_FN02_Interest Instruction-Err displayed on split type 'Amount' instrctn
 * 
 *    Rev 1.602   Mar 05 2012 12:27:50   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.601   Mar 02 2012 12:54:34   if991250
 * Account Commitment in NASU
 * 
 *    Rev 1.600   Feb 28 2012 14:02:24   if991250
 * do not send create acct commit if not applicable
 * 
 *    Rev 1.599   Feb 24 2012 16:06:30   popescu
 * NASU - Added commitment.
 * 
 *    Rev 1.598   Feb 21 2012 17:22:54   if991250
 * added function to remove the maturity instructions list
 * 
 *    Rev 1.597   Feb 21 2012 15:46:02   wp040100
 * P0186484 FN05 - Contract Maturity Instruction Changes
 * 
 *    Rev 1.596   Feb 17 2012 10:04:54   popescu
 * refresh portfolio - temporary backed the code out.
 * 
 *    Rev 1.595   Feb 16 2012 16:14:46   jankovii
 * Sync up: IN 2850590 - P0186477_FN02_Interest Crediting process_issues in desktop
 * 
 *    Rev 1.594   Feb 16 2012 16:08:38   if991250
 * added Account Commitment
 * 
 *    Rev 1.593   Feb 13 2012 17:19:58   if991250
 * added CommitmentStatus
 * 
 *    Rev 1.592   Feb 13 2012 22:59:46   dchatcha
 * Synch up: IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.591   Feb 03 2012 15:17:40   jankovii
 * Sync up: IN 2826242- Maturity/Interest Instruction on Trading Screen
 * 
 *    Rev 1.590   Feb 01 2012 16:34:48   dchatcha
 * Synch up: IN# 2799812 - Contract Screen Issues, refresh portfolio list during NASU.
 * 
 *    Rev 1.589   Jan 23 2012 12:07:40   jankovii
 * Sync up: IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
 * 
 *    Rev 1.588   Jan 21 2012 09:38:38   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.587   Jan 16 2012 13:50:46   wp040027
 * P0188394_Performance Fees - ERISA Functionality
 * 
 *    Rev 1.586   Jan 06 2012 16:17:28   jankovii
 *  P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.585   Jan 06 2012 12:34:34   jankovii
 * Sync up: P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.584   Dec 27 2011 00:44:24   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.583   Dec 19 2011 23:32:20   popescu
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.582   Dec 14 2011 16:54:52   popescu
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.581   Dec 14 2011 18:42:38   dchatcha
 * P0186477/FN03 - GIA - Purchase, validate trade fund\class against portfolio.
 * 
 *    Rev 1.580   Dec 14 2011 18:16:18   dchatcha
 * P0186477/FN03 - GIA - Purchase, validate trade fund\class against portfolio.
 * 
 *    Rev 1.579   Dec 12 2011 11:59:56   wp040100
 * P0186477/FN03 - GIA - Investment History Changes
 * 
 *    Rev 1.578   Dec 08 2011 14:14:28   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.577   Dec 02 2011 14:30:40   jankovii
 * IN 2742091 - P0186477-FN01-NASU-Portfolio fields should be mandatory based on generic control
 * 
 *    Rev 1.576   Nov 27 2011 22:29:16   popescu
 * 2740236 - TIN Validation
 * 
 *    Rev 1.575   Nov 14 2011 12:01:00   jankovii
 * IN 2736408 - P0186477_FN01_NASU screen-Validation & Functional issues - LIST4
 * 
 *    Rev 1.574   Nov 11 2011 15:47:06   jankovii
 * Fixed porfolio/plan issues.
 * 
 *    Rev 1.573   Nov 07 2011 07:59:56   kitticha
 * PETP0188150 FN01 IN2713809 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.572   Oct 28 2011 04:43:40   kitticha
 * PETP0188150 FN01 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.571   Oct 21 2011 09:33:16   kitticha
 * PETP0188150 FN01 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.570   Oct 07 2011 22:57:58   dchatcha
 * P0186477 FN01 - GIA Enhancement, validate portfolio field against trade existed account  only when field value is not blank.
 * 
 *    Rev 1.569   Oct 07 2011 14:23:28   dchatcha
 * P0191592 FN01 - NSCC Social Code
 * 
 *    Rev 1.568   Oct 07 2011 14:12:34   dchatcha
 * P0186477 FN01 - GIA Enhancements, Unable to change account portfolio with trade existed account.
 * 
 *    Rev 1.567   Oct 07 2011 01:07:52   kitticha
 * PETP0183105 FN02 - Unclaimed Property Alberta.
 * 
 *    Rev 1.566   Oct 05 2011 14:25:08   dchatcha
 * P0186477 FN01 - GIA Enhancements, guard calling to view 418 & 419 with functionality activation
 * 
 *    Rev 1.565   Oct 04 2011 18:21:46   dchatcha
 * P0186477 FN01 - GIA Enhancements, display validate portfolio fields based on environment functionality(UAF).
 * 
 *    Rev 1.564   Oct 03 2011 15:31:56   dchatcha
 * P0186477 FN01 - GIA Enhancements, forgot to remove fields from field info.
 * 
 *    Rev 1.563   Oct 03 2011 14:42:46   dchatcha
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.562   Sep 30 2011 10:07:10   popescu
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.561   Sep 28 2011 17:13:26   dchatcha
 * P0186477 FN01 - GIA Enhancements, Integration test.
 * 
 *    Rev 1.560   Sep 16 2011 18:00:50   dchatcha
 * P0186477 FN01 - GIA Enhancements, Create substitution list
 * 
 *    Rev 1.559   Sep 16 2011 06:33:00   kitticha
 * PETP0186486 - KYC Risk Tolerance.
 * 
 *    Rev 1.558   Sep 01 2011 18:54:02   dchatcha
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.557   Aug 04 2011 11:33:50   dchatcha
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.556   Jul 20 2011 18:02:20   dchatcha
 * P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
 * 
 *    Rev 1.555   Jul 07 2011 18:59:30   dchatcha
 * P0181953 FN01 - TFSA Amendment.
 * 
 *    Rev 1.554   May 02 2011 02:15:38   kitticha
 * PETP0181067 FN00 IN2483647 - SSG Social Code enhancement.
 * 
 *    Rev 1.553   Apr 21 2011 07:52:34   kitticha
 * PETP0181067 FN00 IN2483647 - SSG Social Code enhancement.
 * 
 *    Rev 1.552   Mar 11 2011 11:30:50   kitticha
 * IN2450642 - Modify program to support fund-class hierarchy.
 * 
 *    Rev 1.551   Feb 03 2011 12:10:56   dchatcha
 * Synch up: IN# 2395138 - EPA App Acct Category does not apply to client name non-reg accounts, new non-register account is allowed.
 * 
 *    Rev 1.550   Jan 31 2011 18:53:16   dchatcha
 * Synch up: P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.549   Jan 24 2011 14:16:34   dchatcha
 * IN# 2395138 - EPA App Acct Category does not apply to client name non-reg accounts
 * 
 *    Rev 1.548   Jan 19 2011 03:27:56   panatcha
 * Update according to Code Review for P0178584 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.547   Jan 14 2011 04:37:12   panatcha
 * P0178584_FN01 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.546   Jan 11 2011 10:42:22   jankovii
 * IN 2350361 - iFast performance issue
 * 
 *    Rev 1.545   Dec 28 2010 05:32:32   dchatcha
 * IN# 2370625 - Can not add Account Category 'EAP App' to TFSA and RRSP account.
 * 
 *    Rev 1.544   Dec 17 2010 00:21:02   panatcha
 * PET0168296FN09 - TFSA Cancellation: Add new code for Stop Reason field and Rej-Error for changing account status from Terminated to Active.
 * 
 *    Rev 1.543   Dec 09 2010 15:04:02   jankovii
 * IN 2339013 - P0175778: Uptreaming QA testing
 * 
 *    Rev 1.542   Dec 01 2010 06:20:40   dchatcha
 * P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
 * 
 *    Rev 1.541   Nov 24 2010 18:52:28   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.540   Nov 24 2010 03:01:16   kitticha
 * PET165541_FN03_QESI_Phase3_Non_Finance - revise.
 * 
 *    Rev 1.539   Nov 23 2010 14:27:50   jankovii
 * PET175778F N01 - Upstreaming Phase 2
 * 
 *    Rev 1.538   Sep 29 2010 11:35:50   jankovii
 * PET0175377 FN01 - AIP for Joint RESP Account
 * 
 *    Rev 1.537   Sep 17 2010 07:55:36   kitticha
 * PETP0173756 FN02 Don't Bust the Rules.
 * 
 *    Rev 1.536   Sep 15 2010 13:44:42   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.535   Aug 20 2010 14:16:46   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.534   Aug 16 2010 15:56:02   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.533   Aug 11 2010 19:39:52   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.532   Aug 09 2010 16:12:16   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.531   Aug 06 2010 14:03:38   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.530   Jul 09 2010 09:04:48   wutipong
 * IN#2124791 - VT24893 - Incorrect recipient code is on the AA (month file)
 * 
 *    Rev 1.529   May 13 2010 03:50:50   dchatcha
 * RESP QESI Synch-up 1.522.1.6
 * 
 *    Rev 1.528   Apr 30 2010 16:11:16   popescu
 * RESP QESI Synch-up 1.522.1.5
 * 
 *    Rev 1.527   Apr 26 2010 04:08:38   dchatcha
 * RESP QESI Synch-up 1.522.1.4
 * 
 *    Rev 1.526   Apr 19 2010 10:33:38   popescu
 * Rel QESI - synch-ups
 * 
 *    Rev 1.525   Apr 19 2010 07:18:14   popescu
 * RQESI - Synch-up 1.522.1.2
 * 
 *    Rev 1.524   Apr 14 2010 02:19:00   kitticha
 * PET0165541-FN01 QESI RESP Trading.
 * 
 *    Rev 1.523   Apr 06 2010 12:37:54   kitticha
 * PET0169756_FN01_N131-103 Statement and Confirm.
 * 
 *    Rev 1.522   Apr 06 2010 06:34:20   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, take out method that set sibling only valid flag, no longer use, and ensure that HRDC relate code field's possible value is change properly during changing of taxtype on account information screen.
 * 
 *    Rev 1.521   Apr 05 2010 00:09:42   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, default fields to No for other taxtype which is not RESP
 * 
 *    Rev 1.520   Apr 03 2010 02:21:40   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.519   Mar 31 2010 00:24:36   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - bene allocation updates
 * 
 *    Rev 1.518   Mar 26 2010 09:19:36   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.517   Mar 12 2010 14:53:04   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.516   Feb 12 2010 17:11:16   popescu
 * Incident 2003785 - AMS Setup error - trigger the active cert error only for existing accounts
 * 
 *    Rev 1.515   Feb 06 2010 01:29:58   dchatcha
 * P0166183 FN04 - FundSERV Standards V20, Removed Recipient code '6' from selectable list.
 * 
 *    Rev 1.514   Jan 22 2010 02:24:06   dchatcha
 * IN# 1976746 - Pay Instruction button enabled with Pay type X and error displayed.
 * 
 *    Rev 1.513   Oct 26 2009 16:30:18   jankovii
 * PET157825 FN08 FN11 FN14 AMS Gaps
 * 
 *    Rev 1.512   07 Aug 2009 10:48:30   sibuhatm
 * As per the IN1737120 - R94 - DSK returns inconsistent err when changing salesrep on account info screen, we have resolved the error message issue.There was the error messages not cleared, so we have cleared the old error messages and displayed the proper err messages
 * 
 *    Rev 1.511   Aug 05 2009 22:24:38   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Error Unknown Account during NASU, issue found while working on IN#1761005.
 * 
 *    Rev 1.510   Aug 05 2009 18:30:16   dchatcha
 * Synch up: IN#1761005 - R93 - Unable to backdate the effective date on desktop., Restored validation logic of effective date from 1.493.
 * 
 *    Rev 1.509   Aug 03 2009 23:17:54   dchatcha
 * PET156681 FN14 H36 Investor Authorization, revise validation logic of broker/branch/slsrep.
 * 
 *    Rev 1.508   Jul 24 2009 07:57:46   dchatcha
 * PET156681 FN14 H36 Investor Authorization, fix on missing logic that force revalidation Broker/Branch/SlsRep if they are changed against with Investor Authorization.
 * 
 *    Rev 1.507   Jul 23 2009 08:41:42   dchatcha
 * PET156681 FN14 H36 Investor Authorization, fix on missing implementaion of get IA method.
 * 
 *    Rev 1.506   22 Jul 2009 18:09:04   popescu
 * PET156681 FN14 H36 Investor Authorization - clean-up various fixes.
 * 
 *    Rev 1.505   Jul 22 2009 08:28:04   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Code review. 
 * 
 *    Rev 1.504   Jul 16 2009 19:48:26   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Integration issues.
 * 
 *    Rev 1.503   Jun 30 2009 15:02:36   jankovii
 * Sync up: IN1654123 Account Purpose does not change to updatable/readonly when acct type is updated.
 * 
 *    Rev 1.502   Jun 30 2009 18:25:18   wutipong
 * IN1732879 - Fix the parsename() function to accept the input that does not contain '&' (ampersand). -- sync up
 * 
 *    Rev 1.501   29 Jun 2009 16:10:12   popescu
 * PET 156681 - FN 14 - Investor Authorization
 * 
 *    Rev 1.500   11 Jun 2009 16:58:10   popescu
 * IN1654123 Account Purpose does not change to updatable/readonly when acct type is updated.
 * 
 *    Rev 1.499   May 22 2009 18:07:08   wutipong
 * IN1654123 Account Purpose does not change to updatable/readonly when acct type is updated.
 * 
 *    Rev 1.498   May 21 2009 18:09:02   wutipong
 * IN 1654123 Code reverted
 * 
 *    Rev 1.497   Apr 22 2009 18:31:46   wutipong
 * IN 1654123 - move the setFieldValid(...,true) to another function.
 * 
 *    Rev 1.496   Apr 21 2009 18:31:40   wutipong
 * IN1654123 - account purpose does not changed to read-only/updatable  when account type is updated.
 * 
 *    Rev 1.495   Apr 01 2009 09:39:40   jankovii
 * IN 1642475 - Character not compatible - IFast desktop / Base
 * 
 *    Rev 1.494   30 Mar 2009 14:52:38   kovacsro
 * IN#1605081 - do not allow backdated acct-mstr.deff in desktop code. (basically, backed out the 2005 code change)
 * 
 *    Rev 1.493   25 Mar 2009 17:31:28   popescu
 * Incident 1510492  - cached the broker at account level
 * 
 *    Rev 1.492   Mar 11 2009 10:27:36   jankovii
 * IN 1622275  - R92 Regression - mifmarqa - NASU error
 * 
 *    Rev 1.491   Mar 04 2009 14:12:52   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.490   Mar 02 2009 09:59:24   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.489   Feb 05 2009 15:57:24   jankovii
 * IN 1578637 - Project PBSA - Issue on Non Financial Update in Desktop - MMF#007
 * 
 *    Rev 1.488   Jan 23 2009 14:18:32   jankovii
 * IN 1563274 - On RLIF accounts with no pending trades can't change from BR to B.
 * 
 *    Rev 1.487   Jan 12 2009 11:12:18   jankovii
 * IN 1549377 Estate and Death of Notification acct category can only be added by the system
 * 
 *    Rev 1.486   24 Dec 2008 12:06:40   popescu
 * Incident 1531239 - Recipient Type 6 and 7 cannot be modified in Desktop
 * 
 *    Rev 1.485   09 Dec 2008 10:00:24   popescu
 * Incident 1507900 Recipient Code Changes in Base and Desktop - fixed compile issues
 * 
 *    Rev 1.484   08 Dec 2008 12:46:02   popescu
 * Incident 1507900
 * Recipient Code Changes in Base and Desktop
 * 
 *    Rev 1.483   28 Nov 2008 15:24:38   kovacsro
 * PET 142196 FN01 Federal Restricted LIF and LIRA (put some code back which was commented out for the short term solution)
 * 
 *    Rev 1.482   28 Nov 2008 14:50:48   kovacsro
 * synch-up for  IN#1425864 - GL-1323 AS file discrepancy (sales rep uniqueness revisited) from 1.479.1.0
 * 
 *    Rev 1.481   Nov 28 2008 14:39:20   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.480   Nov 25 2008 11:22:04   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.479   21 Nov 2008 10:57:10   popescu
 * Incident 1491961 - proper fix for 1405052
 * 
 *    Rev 1.478   Nov 03 2008 23:29:36   phiwponp
 * IN 1405052 - No error message when intermediary code not entered for an intermediary account.
 * 
 *    Rev 1.477   03 Nov 2008 17:32:42   popescu
 * KYC/AML - Joint accounts feature - after System Integrated Testing
 * 
 *    Rev 1.476   31 Oct 2008 16:18:42   popescu
 * KYC/AML - joint accounts feature
 * 
 *    Rev 1.475   Oct 28 2008 08:32:42   jankovii
 * PET 59888 FN03 AML KYC.
 * 
 *    Rev 1.474   06 Oct 2008 13:19:02   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.473   12 Sep 2008 15:40:58   kovacsro
 * PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
 * 
 *    Rev 1.472   Sep 12 2008 06:32:48   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.471   Aug 29 2008 14:33:48   jankovii
 * IN 1388930.
 * 
 *    Rev 1.470   Aug 28 2008 15:02:50   jankovii
 * IN 1388930 - NASU flow does not update document list unless at least one document.
 * 
 *    Rev 1.469   28 Aug 2008 11:43:34   kovacsro
 * PET142196FN01 Federal LockedIn RRSP - short term solution
 * 
 *    Rev 1.468   Aug 01 2008 11:43:12   jankovii
 * PET 59888 FN01 AML Enhancement.
 * 
 *    Rev 1.467   Jul 29 2008 17:38:18   daechach
 * in#1327144 - New ON LIF with effective date of Dec 31, 2007, synched up from R87.
 * 
 *    Rev 1.466   Jul 25 2008 14:28:22   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.465   Jul 16 2008 10:18:44   jankovii
 * PET 59888 - AML Enhancemement.
 * 
 *    Rev 1.464   Jun 23 2008 14:43:04   jankovii
 * PET 59888 FN01 - AML Enhancement.
 * 
 *    Rev 1.463   23 May 2008 10:05:12   popescu
 * Incident 1253513 - The issue has been solved by checking if the SIN number of the "account from" beneficiary matches the SIN number of the "account to" account owner.
 * This is done only in environments where the entity ids of the above are different. This occurs if the generic control CSSStopSINMatch is turned on.
 * 
 *    Rev 1.462   05 May 2008 14:51:02   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.461   01 May 2008 13:57:40   kovacsro
 * PET2255 FN47 - New Ontario LIF - finalized
 * 
 *    Rev 1.460   Apr 18 2008 17:43:14   daechach
 * Synch up R86 for PET2385 FN 02
 * 
 *    Rev 1.459   16 Apr 2008 09:20:00   kovacsro
 * PET2255FN47 - avoid infinite looping
 * 
 *    Rev 1.458   15 Apr 2008 12:09:38   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.457   26 Mar 2008 16:18:08   kovacsro
 * PET2385 FN02&07 - code review
 * 
 *    Rev 1.456   Mar 11 2008 20:13:38   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.455   Feb 22 2008 11:30:00   yingz
 * incident 1193717 - refresh systematic adn default alloc for trading
 * 
 *    Rev 1.454   Jan 16 2008 14:52:42   jankovii
 * IN 1039201 - Bank acct name.
 * 
 *    Rev 1.453   Dec 07 2007 17:40:02   smithdav
 * PET2400 FN01 - Dividend Processing
 * 
 *    Rev 1.452   06 Dec 2007 09:34:56   kovacsro
 * IN#1039915 - synched up from rel82 branch
 * 
 *    Rev 1.451   Dec 06 2007 19:41:46   smithdav
 * PET1200 FN02 - Dividend Processing enhancement.
 * 
 *    Rev 1.450   03 Dec 2007 09:29:04   kovacsro
 * commented out view385 call (because it did not pass integration testing)
 * 
 *    Rev 1.449   28 Nov 2007 16:20:42   kovacsro
 * IN#1093158 - synch up from 1.447.0.1
 * 
 *    Rev 1.448   26 Nov 2007 16:40:34   kovacsro
 * IN#1039915 - calling view 385 for Affluent validation
 * 
 *    Rev 1.447   Nov 16 2007 15:12:26   smithdav
 * IN#1024380 - Edit for active certificates only
 * 
 *    Rev 1.446   09 Nov 2007 11:18:38   kovacsro
 * IN#1039915 - fix for new accounts (the rules only apply to existing accounts)
 * 
 *    Rev 1.445   Nov 06 2007 18:31:08   smithdav
 * IN1024380 -  Change AMS certificates edit to check at the fund level instead of the account level.
 * 
 *    Rev 1.444   01 Nov 2007 14:30:38   kovacsro
 * IN#1039915 - removed unnecessary condition
 * 
 *    Rev 1.443   29 Oct 2007 15:58:12   kovacsro
 * IN#1039915 - added one more business rule for Affluent field
 * 
 *    Rev 1.442   26 Oct 2007 16:31:38   kovacsro
 * IN# 1039915 - added validation for Affluent field
 * 
 *    Rev 1.441   Oct 24 2007 19:10:20   smithdav
 * IN1024380 - AMSAcctLevel active Certificates edit.
 * 
 *    Rev 1.440   Oct 08 2007 12:16:28   smithdav
 * IN  1005517,1020252 - LRSP logic
 * 
 *    Rev 1.439   20 Sep 2007 10:55:26   popescu
 * Incident 1002765 - fixed the validation for institutional code AMS
 * 
 *    Rev 1.438   19 Sep 2007 16:24:18   popescu
 * Incident 1002765 - social code fix for isAmsRBAllowed = IS
 * 
 *    Rev 1.437   19 Sep 2007 14:28:18   kovacsro
 * IN1003591 - allow AMS even if Escrow or Certificates is set to 'Y'
 * 
 *    Rev 1.436   18 Sep 2007 10:38:38   popescu
 * Incident 1008550 - set default value for Affluent is 'O'
 * 
 *    Rev 1.435   14 Sep 2007 09:57:44   popescu
 * GAP 2360/02 - passed the shr num down to the amsacctlvl list to retrieve existing allocations
 * 
 *    Rev 1.434   Aug 30 2007 11:03:18   smithdav
 * Add AccountNum parameter to the initNew of the AMSAcctLvlList.
 * 
 *    Rev 1.433   Aug 14 2007 17:47:10   popescu
 * Incident# 962948 - made the afluent flag available in the COA dialog box
 * 
 *    Rev 1.432   Aug 08 2007 17:29:40   kovacsro
 * PET 2360 FN 29 RESP
 * 
 *    Rev 1.431   Aug 03 2007 09:34:58   smithdav
 * PET 2360 FN02
 * 
 *    Rev 1.430   Jul 27 2007 10:09:06   smithdav
 * Add return to isAMSRBAllowed method.
 * 
 *    Rev 1.429   Jul 27 2007 16:54:46   kovacsro
 * PET 2372 FN02 FDP-AIM KYC
 * 
 *    Rev 1.428   Jul 18 2007 09:35:58   smithdav
 * PET2360 FN02
 * 
 *    Rev 1.427   Jul 11 2007 16:20:40   smithdav
 * PET 2360 FN02 - AMS - Interim changes
 * 
 *    Rev 1.426   28 Jun 2007 16:43:40   popescu
 * PET 2236 - Gap 50 - Private act
 * 
 *    Rev 1.425   27 Jun 2007 23:58:08   popescu
 * PET 2236 - Gap 50 - Private act
 * 
 *    Rev 1.424   Jun 27 2007 14:58:24   porteanm
 * PET 2360 FN02 - AMS.
 * 
 *    Rev 1.423   Jun 22 2007 14:22:10   porteanm
 * PET 2360 FN02 - AMS - work in progress.
 * 
 *    Rev 1.422   27 Apr 2007 15:25:44   porteanm
 * Incident 867015 - Consolidation Type fix.
 * 
 *    Rev 1.421   Feb 15 2007 14:37:18   popescu
 * Incident# 819881 - MFS slowness with the distribution screen
 *  - release 76 and above, synch-up
 * 
 *    Rev 1.420   Jan 26 2007 15:50:04   ZHANGCEL
 * PET2306 FN02 -- Some modification for the enhancement
 * 
 *    Rev 1.419   Jan 24 2007 16:49:32   ZHANGCEL
 * PET2306 FN02 -- Add logic for ConsolTypeID and ConsolTypePW
 * 
 *    Rev 1.418   Oct 13 2006 17:40:06   fengyong
 * Add transnum search
 * 
 *    Rev 1.417   Sep 21 2006 18:36:26   ZHANGCEL
 * PET2212 FN10 - Add a function to deal with ConsolType issue
 * 
 *    Rev 1.416   Aug 31 2006 13:47:14   ZHANGCEL
 * PET2212 FN10 -- Add a new field ConsolType
 * 
 *    Rev 1.415   Jul 04 2006 13:38:44   ZHANGCEL
 * PET2145 FN01 -- Add "ExistAssignee" in ClassFieldInfo[]
 * 
 *    Rev 1.414   Mar 02 2006 16:27:06   jankovii
 * PET 2072 FN01- NSCC Control Number.
 * 
 *    Rev 1.413   Feb 21 2006 10:18:48   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.412   Dec 05 2005 16:31:40   porteanm
 * Incident 462307 - NASU: TaxType should be validated again after TaxType has been changed.
 * 
 *    Rev 1.411   Nov 19 2005 15:51:18   popescu
 * BPS Performance issue - cached view call 20 and passed params fund/class in as params
 * 
 *    Rev 1.410   Nov 16 2005 10:03:24   popescu
 * PET 1250_08 - active only init value
 * 
 *    Rev 1.409   Nov 03 2005 15:36:34   porteanm
 * Incident 442910 - Changed key when getting UserDefMatList.
 * 
 *    Rev 1.408   Oct 25 2005 12:51:32   popescu
 * Incident# 434042 - removed the deletes of the group fund list. since now is cached at the mgmt co leve.
 * 
 *    Rev 1.407   Oct 24 2005 12:30:56   porteanm
 * PET1250_FN09 : modified validation
 * 
 *    Rev 1.406   Oct 06 2005 17:38:44   AGUILAAM
 * PET1250_FN09 : modified validation
 * 
 *    Rev 1.405   Sep 29 2005 09:15:44   popescu
 * Incident# 406322 - cached call to view 98
 * 
 *    Rev 1.404   Sep 28 2005 17:35:40   popescu
 * Incident # 406322  - fixed minor compilation error
 * 
 *    Rev 1.403   Sep 28 2005 17:20:06   popescu
 * Incident #406322 - bps performance improvements, saves a view call to 43 - if shareholder is neither intermediary, nor nominee
 * 
 *    Rev 1.402   Sep 26 2005 09:56:08   AGUILAAM
 * PET1250_FN08: update to initialize ActiveOnly to NO for API use
 * 
 *    Rev 1.401   Sep 20 2005 12:51:16   fengyong
 * Incident 402113 - In Transaction history screen:
 * All fund mode and select fund combo box, do not need check transId.
 * 
 *    Rev 1.400   Sep 20 2005 12:15:16   AGUILAAM
 * PET1250_FN09_Custody Client Accounts and Negative Balances; also fixed Refresh functionality for Settlements.
 * 
 *    Rev 1.399   Sep 02 2005 13:15:22   popescu
 * Incident 390227 - do not raise warning during NASU flow if broker is not NSCC, synch-up 64.0.0.5
 * 
 *    Rev 1.398   Sep 01 2005 13:19:46   AGUILAAM
 * PET1250_FN07_Fund Merge: support display of active only or all  holdings based on generic control
 * 
 *    Rev 1.397   Aug 25 2005 16:35:52   ZHANGCEL
 * Incident #388060 -- 1.Change logic to allow AgentForFirm and TPA to be the same as ClearingFirm; 2.Code clean up
 * 
 *    Rev 1.396   Jul 27 2005 18:43:00   AGUILAAM
 * IN 353952 - refine validations of Systematic records against broker/branch/rep effective/stop dates.
 * 
 *    Rev 1.395   Jul 27 2005 17:31:50   ZHANGCEL
 * PET1141 - FN05 -- Minor change in validateAgtFirmClrFirm and TPAClrFirm
 * 
 *    Rev 1.394   Jul 20 2005 14:01:24   Yingbaol
 * PET1235,FN01: fix refresh pending trade
 * 
 *    Rev 1.393   Jul 15 2005 13:55:42   ZHANGCEL
 * PET1141 - FN05 -- Bug fix after UIT testing
 * 
 *    Rev 1.392   Jul 08 2005 16:46:28   hernando
 * Incident 344960 - Modified getUserDefMatList.  Sync'd with 1.387.1.0
 * 
 *    Rev 1.391   Jul 07 2005 15:58:26   ZHANGCEL
 * PET1141-FN05 -- Added another parameter in setParticipantID()
 * 
 *    Rev 1.388   Jul 06 2005 10:58:58   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.386   Jun 20 2005 02:33:08   popescu
 * Incident # 336954 - should not request all the records for validateAltAcct warning; use 'false' for DSCRequestor
 * 
 *    Rev 1.385   May 17 2005 13:50:18   AGUILAAM
 * IN 299732: re-added v1.383 changes (fix for IN 293479) overwritten by v1.384
 * 
 *    Rev 1.384   May 16 2005 09:39:26   AGUILAAM
 * IN 299732 - inactive broker/branch/rep not allowed for systematics
 * 
 *    Rev 1.382   Apr 21 2005 17:29:50   hernando
 * Incident #278666 - Switched TransNum to ExtTransNum.  Incident #279078 - Added key to Pending Trade List; Added ExtTransNum to Pending Trade List and Transaction History List get fns.  Synchronized with 1.376.1.1-1.376.1.3
 * 
 *    Rev 1.381   Apr 21 2005 10:15:20   ZHANGCEL
 * Incident #292340 -- For a new account, call initNew for the TexExemptAutorization
 * 
 *    Rev 1.380   Apr 14 2005 10:06:38   hernando
 * PET1024 FN02 - Added parameter, Contract Type.
 * 
 *    Rev 1.379   Apr 12 2005 10:29:30   porteanm
 * PET1190 FN14 - Wire order redemption against unsettled units.
 * 
 *    Rev 1.378   Mar 23 2005 15:12:34   Fengyong
 * incident 271027 - broker check must be called when broker code is not NULL
 * 
 *    Rev 1.377   Mar 20 2005 15:03:58   hernando
 * PET1024 FN02 - Added getUserDefMatList.
 * 
 *    Rev 1.376   Mar 13 2005 17:31:54   winnie
 * Restore prevous version. Delete GroupFundList pointer after finish using it.
 * 
 *    Rev 1.375   Mar 11 2005 14:27:54   smithdav
 * Fixed bug in Group::getGroupFundListByFund function where BPS threads clashed the function call concurrently.
 *
 *    Rev 1.374   Feb 17 2005 13:19:02   yingbaol
 * magic#237768 Sync. 1.370.1.0 GetGroupFundByFundCode
 * 
 *    Rev 1.373   Feb 04 2005 15:00:48   porteanm
 * PTS 10033798 - "Should this Account be rebalanced in the next cycle" support.
 * 
 *    Rev 1.372   Feb 01 2005 10:59:00   porteanm
 * PTS 10033798 - "Should this Account be rebalanced in the next cycle" support.
 * 
 *    Rev 1.371   Jan 19 2005 10:38:12   porteanm
 * PTS 10037310 - getAccountHoldingList() will call view 20 with blank date. The view will take care of assigning the correct date.
 * 
 *    Rev 1.370   Dec 21 2004 16:04:56   popescu
 * PTS 10037131, removed 'deletePendingTradesList' method at the account level; it is dangerous to have such a public method; dealt with removing the list when necessary after trade is being modified, in trades process
 * 
 *    Rev 1.369   Dec 10 2004 17:40:14   vadeanum
 * PET1117_FN21: settlement instructions
 * 
 *    Rev 1.368   Dec 10 2004 13:19:12   Fengyong
 * PET10034197 - PAC allocation not being changed after account level AMS set flag change pac/swp is yes.
 * 
 *    Rev 1.367   Dec 07 2004 15:50:26   popescu
 * Fix cross-edit validation, acctype/taxtype
 * 
 *    Rev 1.366   Dec 07 2004 14:39:08   winnie
 * Add missing fields to Class field info
 * 
 *    Rev 1.365   Nov 25 2004 11:05:00   popescu
 * pet 1117/minor change
 * 
 *    Rev 1.364   Nov 23 2004 16:09:22   popescu
 * Turned versioning off, removed idDataGroup from TaxTypeRuleList::createTaxTypesList
 * 
 *    Rev 1.363   Nov 23 2004 15:53:34   aguilaam
 * PET1117_FN21: settlement instructions
 * 
 *    Rev 1.362   Nov 19 2004 17:33:10   aguilaam
 * PET117_FN21: settlement instructions enhancement (temporary check-in for build)
 * 
 *    Rev 1.361   Nov 14 2004 14:49:36   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.360   Nov 06 2004 00:41:56   popescu
 * PET 1117/06, synch changes
 * 
 *    Rev 1.359   Nov 05 2004 17:35:58   AGUILAAM
 * PET1170_FN21: settlement instructions enhancement
 * 
 *    Rev 1.358   Oct 21 2004 17:50:08   FENGYONG
 * PTS10034976 - Error message of Fee ModelCode not active
 * 
 *    Rev 1.357   Oct 20 2004 17:58:22   YINGBAOL
 * PTS10034800: change validattion for FeeModelCode
 * 
 *    Rev 1.356   Oct 20 2004 17:49:40   VADEANUM
 * PET 1117 FN21 - Backed out changes for Settlement Instruction support.
 * 
 *    Rev 1.355   Oct 13 2004 13:53:16   VADEANUM
 * PET 1117 FN21 - Settlement Instruction support.
 * 
 *    Rev 1.354   Oct 06 2004 10:40:24   YINGBAOL
 * sync. version PTS10034442
 * 
 *    Rev 1.353   Sep 22 2004 09:12:26   WINNIE
 * PET1082 FN02 Tax Exemption : add new parameter to indicate if getting data from database is required or not. When transaction builder invoke this method, it does not require getting data from the database.
 * 
 *    Rev 1.352   Sep 02 2004 12:31:04   FENGYONG
 * Add Conditions for PET1117 FN5
 * 
 *    Rev 1.351   Aug 31 2004 17:30:24   FENGYONG
 * change Field names
 * 
 *    Rev 1.350   Aug 11 2004 18:37:32   FENGYONG
 * Temp check in  PET 117 FN5  for other enhancement compiling
 * 
 *    Rev 1.349   Aug 11 2004 12:00:06   AGUILAAM
 * PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
 * 
 *    Rev 1.348   Aug 06 2004 17:31:54   ZHANGCEL
 * PET 1082 FNrlc - Add a new function -- getTaxExemptAuthorizationList()
 * 
 *    Rev 1.347   Jul 23 2004 10:00:28   YINGBAOL
 * PET1117: Add isSettleRedeptionAllowed method.
 * 
 *    Rev 1.346   Jun 09 2004 11:37:06   YINGBAOL
 * PTS10031028:Refresh systemaic when UpdatePACSWP is changed and implement logic for UpdatePACSWP and rebalancing flag.
 * 
 *    Rev 1.345   May 28 2004 10:38:28   YINGBAOL
 * PTS10027992:how come code only checked in partially?
 * 
 *    Rev 1.344   May 27 2004 17:23:52   YINGBAOL
 * PTS10027992: Limit length only apply to sales rep
 * 
 *    Rev 1.343   May 26 2004 18:21:04   popescu
 * PET 985, fn 01, Shareholder tax jurisdiction refresh, added LSIFPAC field to the MFAccount object
 * 
 *    Rev 1.342   May 26 2004 11:01:40   YINGBAOL
 * PTS10027992:add limit for BrokerCode,BranchCode and SalsRepCode based on the ifast setting.
 * 
 *    Rev 1.341   May 25 2004 22:39:02   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.340   May 25 2004 20:32:16   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.339   May 20 2004 14:17:00   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.338   May 12 2004 17:49:34   HERNANDO
 * PET1046 FN01 - Added ActiveOnly to getInventorySummaryList.
 * 
 *    Rev 1.337   May 11 2004 15:49:32   popescu
 * PET 985, FN 01, LSIF Trade Entry, added handy methods to fund master list, to check whether a fund is LSIF/Money Market, GIC
 * 
 *    Rev 1.336   May 06 2004 11:24:24   HERNANDO
 * PET1046 FN01 - Changed getInventorySummaryList to include Active Only value.
 * 
 *    Rev 1.335   Apr 16 2004 16:41:58   VADEANUM
 * PET1005 FN11 - AMS Gaps for 56.1- added AMSEligible to view 56 as per Winnie's email.
 * 
 *    Rev 1.334   Apr 13 2004 17:45:28   FENGYONG
 * PET944 FN01 NSCC Broker - set Networkcontrolind required when NSCC applicable.
 * 
 *    Rev 1.333   Apr 13 2004 10:30:52   VADEANUM
 * PET1005 FN11 - AMS Gaps - uncommented out what was there just for testing purposes.
 * 
 *    Rev 1.332   Apr 12 2004 16:18:02   VADEANUM
 * PET1005 FN11 - AMS Gaps.
 * 
 *    Rev 1.331   Apr 05 2004 17:29:40   FENGYONG
 * PET944 FN01, release 56.1 NSCC Broker Matrix
 * 
 *    Rev 1.330   Mar 08 2004 15:46:00   HERNANDO
 * PTS10026849 - Changed format for retrieving DuplicateAltAcct.
 * 
 *    Rev 1.329   Mar 08 2004 11:15:28   HERNANDO
 * PTS10026849 - Changed format flag for retrieving ModRecipType.
 * 
 *    Rev 1.328   Mar 03 2004 16:35:00   popescu
 * PTS 10027578, set the _bRefresh flag to false after a refresh (reInit)
 * 
 *    Rev 1.327   Mar 03 2004 16:21:22   popescu
 * PTS 10027578, refresh the account information after updating the mailing address info and demographics info; changed the name of the refreshMe method, to be consistent with the shareholder object
 * 
 *    Rev 1.326   Mar 03 2004 15:29:38   ZHANGCEL
 * PET1001-FN01 -- delete pointer in get InventorySummaryList
 * 
 *    Rev 1.325   Feb 25 2004 14:28:34   ZHANGCEL
 * PET1001-FN01: Added a function to get InventorySummaryList
 * 
 *    Rev 1.324   Feb 18 2004 17:00:22   YINGBAOL
 * PTS10027208: syc. version 1.321.1.0 add validation for clearing ID
 * 
 *    Rev 1.323   Jan 27 2004 12:11:16   AGUILAAM
 * PET1014  FN13 : default ChargeSTTRFee and ChargeERFee per generic controls 'ShortTermTrading' on new account set-up
 * 
 *    Rev 1.322   Jan 09 2004 17:05:28   VADEANUM
 * PTS 10025910 - Search for Business No.
 * 
 *    Rev 1.321   Jan 07 2004 10:46:08   YINGBAOL
 * PTS 10021623
 * 
 *    Rev 1.320   Jan 02 2004 15:12:10   popescu
 * PTS 10025696, NASU flow crash 
 * 
 *    Rev 1.319   Nov 27 2003 10:36:56   HERNANDO
 * PET892 FN1 - Added Clearing ID.
 * 
 *    Rev 1.318   Nov 25 2003 11:30:08   VADEANUM
 * PET859 FN1 - Added SettleLocExist to the Field Info array - Merged with v. 1.316.1.0
 * 
 *    Rev 1.317   Nov 25 2003 11:21:16   VADEANUM
 * PET859 FN1 - Settlement Location at Trade Level support - added isClearingAccount() and hasSettlementLocation().
 * Also included May's changes in validatePendingPAC().
 * 
 *    Rev 1.316   Nov 20 2003 18:11:54   HERNANDO
 * PET859 FN1 - Added getSettlementLocationAcctLvlList.
 * 
 *    Rev 1.315   Nov 20 2003 10:59:46   HSUCHIN
 * PTS 10023905 - bug fix for branch verification when salesrepbybranch is turned off.
 * 
 *    Rev 1.314   Nov 20 2003 09:12:34   linmay
 * added validatePendingPAC( ) for PTS #10024070
 * 
 *    Rev 1.313   Nov 10 2003 17:36:44   AGUILAAM
 * Synch-up with 1.306.1.5
 * 
 *    Rev 1.312   Nov 05 2003 15:38:36   HSUCHIN
 * Sync up 1.306.1.4
 * 
 *    Rev 1.311   Nov 05 2003 11:48:24   VADEANUM
 * PTS 10023031 - Unable to assign pre-existing AMS model to account AMS - Added specialized conditions for each type of error in ValidateAMSRestrictionForBrokers()
 * 
 *    Rev 1.310   Oct 31 2003 15:27:16   popescu
 * Synch-up Rel 54 PTS 10023438
 * 
 *    Rev 1.309   Oct 31 2003 10:24:02   FENGYONG
 * Syncup release 53 fix for PTS 10023560
 * 
 *    Rev 1.308   Oct 23 2003 17:54:32   FENGYONG
 * Add ExclDTAAcctType field
 * 
 *    Rev 1.307   Oct 16 2003 12:20:14   FENGYONG
 * PET809 FN08 Direct Trading enhancement
 * 
 *    Rev 1.306   Oct 03 2003 13:40:44   FENGYONG
 * PTS 10022488, validate broker AMS restriction in account level.
 * 
 *    Rev 1.305   Sep 18 2003 15:45:36   FENGYONG
 * Call init new for oerridemailing for new account
 * 
 *    Rev 1.304   Sep 18 2003 14:17:32   FENGYONG
 * get Demographic list need inquiry new account for existing shareholder
 * 
 *    Rev 1.303   Sep 15 2003 14:20:06   YINGBAOL
 * add refresh me and needsrefresh methods
 * 
 *    Rev 1.302   Sep 12 2003 13:48:58   FENGYONG
 * business no will be striped all the '-' before set field,
 * the validation need also validate the middlt 2 charactors.
 * 
 *    Rev 1.301   Sep 10 2003 11:48:42   HERNANDO
 * Sync'd with 1.276.1.0; PTS 10013951.
 * 
 *    Rev 1.300   Sep 05 2003 15:24:54   HSUCHIN
 * bug fix to ams validation of fund/class for ams eligibility.  Error indicating user has no permission to override is removed as dialog handles this case.
 * 
 *    Rev 1.299   Aug 25 2003 14:23:14   YINGBAOL
 * default AMSType to RB if it is a new account
 * 
 *    Rev 1.298   Aug 22 2003 13:05:04   HSUCHIN
 * changed getAMSFundAlloc to get allocation from global ams
 * 
 *    Rev 1.297   Aug 21 2003 17:21:08   HSUCHIN
 * change getAMSFundAllocation to take in effective date
 * 
 *    Rev 1.296   Aug 21 2003 11:53:16   YINGBAOL
 * add validateAMSRRIF
 * 
 *    Rev 1.295   Aug 20 2003 14:42:12   YINGBAOL
 * take off validation for AMSROType and TaxJurisdiction etc....
 * 
 *    Rev 1.294   Aug 20 2003 13:04:42   linmay
 * added field TelFaxAgreement
 * 
 *    Rev 1.293   Aug 19 2003 17:22:26   HSUCHIN
 * bug fix for check to see if sales rep can create account.
 * 
 *    Rev 1.292   Aug 19 2003 14:25:50   YINGBAOL
 * change validateall and default AMSType
 * 
 *    Rev 1.291   Aug 19 2003 09:08:20   HSUCHIN
 * added isHouseBroker method and house broker validation
 * 
 *    Rev 1.290   Aug 16 2003 11:35:20   HSUCHIN
 * added check for AMS restriction.  Purchase outside of AMS mix is not allowed when DefaultAllocOverride is on.
 * 
 *    Rev 1.289   Aug 15 2003 15:26:38   HSUCHIN
 * added AMS Restriction support canPAC, minPAC etc.
 * 
 *    Rev 1.288   Aug 12 2003 16:26:50   FENGYONG
 * empty business no should not be validate
 * 
 *    Rev 1.287   Aug 11 2003 17:20:46   FENGYONG
 * Add validation group to the additionalInfo, BusinessNo, AcctPurpose
 * 
 *    Rev 1.286   Aug 11 2003 12:03:10   YINGBAOL
 * Added validateAccountTaxTypeAccountDesTaxJurisProvRes,
 * validateAMSFundCurrency, validateAMSGICFund, validateAMSSWP,validEscrowAccount.
 * 
 *    Rev 1.285   Jul 31 2003 15:45:42   FENGYONG
 * control required field by error Number
 * 
 *    Rev 1.284   Jul 30 2003 16:58:46   FENGYONG
 * logic for entity type initial changed.
 * 
 *    Rev 1.283   Jul 30 2003 11:26:34   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.282   Jul 29 2003 10:20:26   linmay
 * modified getAmsMstrList for CIBC
 * 
 *    Rev 1.281   Jul 28 2003 16:07:30   FENGYONG
 * account purpose field logic chnage - temp
 * 
 *    Rev 1.280   Jul 28 2003 14:17:22   HERNANDO
 * Added MemorableWord, MemorablePlace, and MemorableDate to classFieldInfo array.
 * 
 *    Rev 1.279   Jul 24 2003 17:56:40   FENGYONG
 * Add AcctPurpose , BusinessNo and associate validation for CIBC AcctSetUp
 * 
 * temp check in 
 * 
 *    Rev 1.278   Jul 17 2003 10:44:02   FENGYONG
 * Add fields
 * 
 *    Rev 1.277   Jul 11 2003 16:03:38   FENGYONG
 * move demographic from shareholder to MFAccount
 * 
 *    Rev 1.276   Jun 12 2003 14:48:48   YINGBAOL
 * sync. version 1.266.1.5
 * 
 *    Rev 1.275   Jun 06 2003 15:44:30   FENGYONG
 * 10017878
 * 
 *    Rev 1.274   Jun 01 2003 17:07:52   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.273   May 31 2003 20:30:14   popescu
 * RRIF work part ||
 * 
 *    Rev 1.272   May 31 2003 11:55:08   popescu
 * RRIF bank work
 * 
 *    Rev 1.271   May 27 2003 16:37:58   popescu
 * NASU flow AMS :data not found issue fix and removed some memory leaks 
 * 
 *    Rev 1.270   May 23 2003 18:42:36   HERNANDO
 * Added validateMgmtFeePayOption.
 * 
 *    Rev 1.269   May 22 2003 14:12:54   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.268   May 20 2003 18:06:12   YINGBAOL
 * Sync. Version 1.266.1.0
 * 
 *    Rev 1.267   May 13 2003 16:09:28   HERNANDO
 * PET792.FN04.3 - Added StopAMSRebalancing.
 * 
 *    Rev 1.266   May 02 2003 14:11:58   HERNANDO
 * Removed setField and setFieldReadOnly of AMSType.  Added extra conditions for ValidateAMSCode.
 * 
 *    Rev 1.265   Apr 29 2003 13:59:52   sanchez
 * sync up with r.1.250.1.6 PTS 10016120, 10016387
 * 
 *    Rev 1.264   Apr 22 2003 10:43:58   HERNANDO
 * Added setField to set AMSType to Read Only.
 * 
 *    Rev 1.263   Apr 21 2003 14:13:18   YINGBAOL
 * fix account number empty issue in Address List
 * 
 *    Rev 1.262   Apr 21 2003 09:47:28   YINGBAOL
 * change getFieldByAMSCode sync.
 * 
 *    Rev 1.261   Apr 16 2003 18:03:34   linmay
 * Ticket PTS 10014986, PTS10014988, PTS10015336 sync up version 1.250.1.3
 * 
 *    Rev 1.260   Apr 15 2003 10:50:46   linmay
 * Sync up with 1.258.1.1
 * 
 *    Rev 1.259   Apr 09 2003 15:28:12   ZHANGCEL
 * PTS ticket 10015597 : Bug fix for the error when transfer from LIRA to LIF in the case of Jurisdiction empty
 * 
 *    Rev 1.257   Apr 02 2003 17:40:46   HERNANDO
 * Added AMS Type in getAMSFundAllocList to support Pre51 addition of requiring AMS Type in the request.
 * 
 *    Rev 1.256   Apr 02 2003 13:53:14   HERNANDO
 * Sync'd with 1.252.1.3
 * 
 *    Rev 1.255   Apr 01 2003 16:40:30   FENGYONG
 * Add AcctMailingOverride list
 * 
 *    Rev 1.254   Mar 21 2003 19:27:10   PURDYECH
 * Sync 1.252.1.0 to trunk
 * 
 *    Rev 1.253   Mar 21 2003 18:18:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.252   Mar 18 2003 17:59:14   HERNANDO
 * [updated] Dev-revision for AMS.
 * 
 *    Rev 1.251   Mar 14 2003 08:24:00   sanchez
 * Add ChargeERFee and ChargeSTTRFee fields
 * 
 *    Rev 1.250   Mar 05 2003 11:54:22   HSUCHIN
 * PTS 10014446 - fixed broker/branch/salesrep validation to check effective/stop date.
 * 
 *    Rev 1.249   Feb 26 2003 17:16:54   HSUCHIN
 * PTS - 10014118 - bug fix so that beneficiary name required error only occurs for nominee/3rd party accounts
 * 
 *    Rev 1.248   Feb 19 2003 15:45:56   HSUCHIN
 * PTS 10013802/10013803
 * 
 *    Rev 1.247   Feb 06 2003 15:04:04   HSUCHIN
 * added method setWRAPAcctDefaults to set/unset defaults for WRAP accounts
 * 
 *    Rev 1.246   Feb 06 2003 10:44:40   WINNIE
 * New method canContributeProtecedFund to validate if account owner is valid for buying or transfer into protected fund
 * 
 *    Rev 1.245   Feb 04 2003 12:25:20   WINNIE
 * Add group level lockedin edit check to Transfer out as per EBS for Dyn Group Processing
 * 
 *    Rev 1.244   Jan 29 2003 13:52:00   sanchez
 * New functions :isAMSOnly(const BFDataGroupId& idDataGroup)
 * isAMSAnOption(const BFDataGroupId& idDataGroup) to check if RB AND RO or only RO
 * 
 *    Rev 1.243   Jan 26 2003 18:32:34   WINNIE
 * Margin account validation for fund eligibility
 * 
 *    Rev 1.242   Jan 26 2003 15:23:34   KOVACSRO
 * Data group fixes for Account Category.
 * 
 *    Rev 1.241   Jan 25 2003 17:03:40   KOVACSRO
 * Added isCategoryExist and other
 * 
 *    Rev 1.240   Jan 23 2003 16:28:48   KOVACSRO
 * Added Account Category list
 * 
 *    Rev 1.239   Jan 21 2003 19:09:56   WINNIE
 * Add edit check for redemption for Group level locked-in for employer or employee
 * 
 *    Rev 1.238   Jan 21 2003 18:37:20   WINNIE
 * remove method fundclasstradeMinimum. Method to be build in Trade.cpp instead. Correction of account contract key build
 * 
 *    Rev 1.237   Jan 20 2003 15:18:50   HSUCHIN
 * added getAccountContractList
 * 
 *    Rev 1.236   Jan 16 2003 19:00:52   WINNIE
 * Remove logic in dorelatedchange that affect AMSRO data when user change the AMSCode and vice versa. Correct logic to check AMSType before getting the corresponding allocation
 * 
 *    Rev 1.235   Jan 14 2003 17:56:50   HERNANDO
 * Changed validateAMSCode to send AMSType.
 * 
 *    Rev 1.234   Jan 14 2003 14:54:36   sanchez
 * Modified validateAMSCode
 * 
 *    Rev 1.233   Jan 13 2003 20:13:42   WINNIE
 * Fix infinite looping; add condition for invalid AMSCode; add logic to trigger validation for AMSROCode
 * 
 *    Rev 1.232   Jan 09 2003 14:01:12   sanchez
 * merge with 310.11
 * 
 *    Rev 1.231   Jan 09 2003 10:21:00   sanchez
 * Rebalancing Target Mix. functions modified: doApplyRelatedChanges() ,setAMSTypeSubstitutionList(), validateAMSCode()
 * 
 *    Rev 1.230   Dec 30 2002 10:28:48   sanchez
 *   - Added pay fee options
 * 
 *    Rev 1.229   Dec 19 2002 11:48:06   YINGBAOL
 * fix PTS10011841
 * 
 *    Rev 1.228   Dec 10 2002 16:17:16   HSUCHIN
 * bug fix to getAMSFundAllocList
 * 
 *    Rev 1.227   Dec 06 2002 10:54:14   YINGBAOL
 * sync. 1.222.1.0 
 * 
 * 
 *    Rev 1.226   Dec 05 2002 15:55:44   HERNANDO
 * Changed doApplyRelatedChanges for AMSCode.
 * 
 *    Rev 1.225   Dec 05 2002 14:38:20   HERNANDO
 * Added AMSCode to doApplyRelatedChanges.
 * 
 *    Rev 1.224   Nov 29 2002 15:46:26   HERNANDO
 * Set AMSCode in getAMSFundAllocList.
 * 
 *    Rev 1.223   Nov 29 2002 10:51:46   KOVACSRO
 * implemented getAMSAcctAlloc.
 * 
 *    Rev 1.222   Nov 26 2002 14:56:44   HERNANDO
 * Defined getAMSFundAllocList -- retrieves Fund Alloc List for Global AMS Code.
 * 
 *    Rev 1.221   Nov 25 2002 16:29:14   KOVACSRO
 * minor fix.
 * 
 *    Rev 1.220   Nov 25 2002 16:03:32   KOVACSRO
 * Added  getAMSFundAllocList(AmsFundAllocList and getAMSAcctAllocList (empty implementations for now).
 * 
 *    Rev 1.219   Nov 25 2002 09:50:18   KOVACSRO
 * version 1.218 undid my ver. 1.216. Undone what what has been undone in ver. 218.
 * 
 *    Rev 1.218   Nov 18 2002 10:54:36   PURDYECH
 * BFObjectKey changes.
 * 
 *    Rev 1.217   Nov 01 2002 14:59:40   KOVACSRO
 * Data group change.
 * 
 *    Rev 1.216   Oct 29 2002 10:52:40   KOVACSRO
 * added getHypoRedCriteria.
 * 
 *    Rev 1.215   Oct 09 2002 23:54:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.214   Sep 18 2002 11:08:26   KOVACSRO
 * PTS 10009879 : fixed duplicate alternate account.
 * 
 *    Rev 1.213   Sep 12 2002 17:34:44   ZHANGCEL
 * 1. PTS 10009775--Change the default LRIF account type to Individal rather than blank; 2. Comment out the logic for the age validation of RRSP and LIRA
 * 
 *    Rev 1.212   Sep 04 2002 17:10:02   KOVACSRO
 * Added getAcctName()
 * 
 *    Rev 1.211   Aug 29 2002 12:56:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.210   Aug 16 2002 10:10:40   HSUCHIN
 * bug fix for when Pension Account with no Pension Info.
 * 
 *    Rev 1.209   Aug 06 2002 15:00:50   HERNANDO
 * PTS 10009268 - Clean up.  Removed ERR_DATE_FUNCTIONS from Namespace.
 * 
 *    Rev 1.208   Aug 02 2002 16:30:48   KOVACSRO
 * Added fund and class for zero account balance.
 * 
 *    Rev 1.207   Aug 02 2002 14:43:20   KOVACSRO
 * PTS 10009253 : nominee, itermediary address fixes
 * 
 *    Rev 1.206   Aug 01 2002 16:31:00   HSUCHIN
 * bug fix for Pension Info.  
 * 
 *    Rev 1.205   Jul 26 2002 14:57:34   ZHANGCEL
 * PTS 10009159: change logic for RRSP and RRIF validation against tax jurisdiction
 * 
 *    Rev 1.204   Jul 06 2002 19:10:36   WINNIE
 * Clean up edit check for RRSP and RRIF tax type against shareholder Tax jurisdiction
 * 
 *    Rev 1.203   Jul 05 2002 18:50:06   WINNIE
 * set stopredeem flag for new account only
 * 
 *    Rev 1.202   Jul 05 2002 17:19:50   HERNANDO
 * Set Stop Redemption according to Tax Type; LIRA - YES, other NO.
 * 
 *    Rev 1.201   Jul 04 2002 14:14:34   ZHANGCEL
 * Bug fix: added logic in validateTaxtTypePensionJurist()
 * 
 *    Rev 1.200   Jul 03 2002 13:51:52   ZHANGCEL
 * Bug fix for the problem of " Desktop allows creation of account without any broker or sales rep"
 * 
 *    Rev 1.199   Jul 02 2002 14:04:14   WINNIE
 * Pension jurisdiction only applicable to taxtype B, C and L, correct logic that refer to RRSP
 * 
 *    Rev 1.198   Jul 02 2002 13:28:40   HSUCHIN
 * bug fix.   Added LRIF taxtype to doApplyRelatedc...to set Pension Jurisdiction combo to not readonly
 * 
 *    Rev 1.197   Jul 02 2002 12:04:26   HSUCHIN
 * bug fixed - Pension Jurisdiction is not required for RRSP and RRIF accounts
 * 
 *    Rev 1.196   Jul 02 2002 11:10:44   WINNIE
 * Tax legislation enhancement to check spouse SIN for marriage break down redemption and transfer
 * 
 *    Rev 1.195   Jun 28 2002 16:47:18   ZHANGCEL
 * Bug fixed for taxTypePensionJurist cross edit validation problem
 * 
 *    Rev 1.194   Jun 27 2002 17:07:26   ZHANGCEL
 * Added proper logci for the locked_in taxtype account setup
 * 
 *    Rev 1.193   Jun 25 2002 15:19:14   ZHANGCEL
 * PTS 10008253: Bug fix for unable to select correct taxtype
 * 
 *    Rev 1.192   Jun 19 2002 15:53:16   ZHANGCEL
 * PTS 10008491: Added a function - checkForDuplicateAltAcct() for the duplicate alternate account checking
 * 
 *    Rev 1.191   Jun 17 2002 12:31:58   HSUCHIN
 * bug fix for pension info building when account does not have pension info
 * 
 *    Rev 1.190   13 Jun 2002 14:40:24   YINGZ
 * add reqtransid to support settlement
 * 
 *    Rev 1.189   13 Jun 2002 10:43:24   WINNIE
 * assign fields that are taxtyperule related otherwise edit check in accountentityxrefobject.cpp will not trigger in NASU flow
 * 
 *    Rev 1.188   Jun 10 2002 16:42:46   KOVACSRO
 * Formatted versus unformatted.
 * 
 *    Rev 1.187   08 Jun 2002 18:55:56   HERNANDO
 * Added logic to doapplyrelatedchanges for 'TaxType' to set StopRedeem to 'Y'es.
 * 
 *    Rev 1.186   Jun 05 2002 17:45:48   ZHANGCEL
 * PTS 10008253: added a cross edit for TaxType and AcctType to avoid invalid TaxType and AcctType combination being accepted.
 * 
 *    Rev 1.185   02 Jun 2002 17:19:02   KOVACSRO
 * Added BankChrgs and ConsolidEFT
 * 
 *    Rev 1.184   31 May 2002 13:24:04   HERNANDO
 * Account Review - Added getAccountReviewList fn.
 * 
 *    Rev 1.183   May 30 2002 16:42:46   HSUCHIN
 * added method to getPensionInfo
 * 
 *    Rev 1.182   May 23 2002 13:17:24   PURDYECH
 * BFData Implementation Verification Corrections
 * 
 *    Rev 1.181   22 May 2002 18:29:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.180   Apr 25 2002 14:39:54   YINGBAOL
 * move version 1.179.1.0 to trunk
 * 
 *    Rev 1.179.1.0   Apr 25 2002 13:44:30   YINGBAOL
 * fix AccountType and ApplyPST related issues
 * 
 *    Rev 1.179   18 Apr 2002 16:31:02   KOVACSRO
 * fixed getTaxTypeRule ().
 * 
 *    Rev 1.178   18 Apr 2002 15:56:08   KOVACSRO
 * StopSWP changes.
 * 
 *    Rev 1.177   17 Apr 2002 17:00:14   KOVACSRO
 * Added StopSWP.
 * 
 *    Rev 1.176   08 Apr 2002 13:51:46   YINGBAOL
 * force to validate TaxType when AccountDesignation has been changed from shareholder
 * 
 *    Rev 1.175   Apr 04 2002 08:24:08   JANKAREN
 * PTS 10007540 - PensionJuris is updatable when taxtype is B, C, L
 * 
 *    Rev 1.174   Apr 03 2002 11:08:06   YINGBAOL
 * Add AcctFeeExist to FieldInfo--- take care of default values
 * 
 *    Rev 1.173   Mar 27 2002 15:38:58   JANKAREN
 * PTS 10007590 - bug fix for Intermediary code when Account Information screen is called the second time.
 * 
 *    Rev 1.172   Mar 26 2002 14:36:58   JANKAREN
 * PTS 10007540 - change logic in doApplyRelatedChanges() - PensionJuris is updatable only when Taxtype is B, C and L.
 * 
 *    Rev 1.171   Mar 26 2002 12:32:46   JANKAREN
 * PTS 10007540 - PensionJuris is updatable only when taxType is B, C and L
 * 
 *    Rev 1.170   Mar 22 2002 10:25:56   YINGBAOL
 * take GSTExempt default value off
 * 
 *    Rev 1.169   Mar 12 2002 16:04:12   JANKAREN
 * Added getDofDeathofOwnerSeq01()
 * 
 *    Rev 1.168   05 Mar 2002 16:26:04   KOVACSRO
 * Added refreshDataObject(), which is a partial refresh for MFAccount (it will only refresh view 4, not the contained objects)
 * 
 *    Rev 1.167   Feb 25 2002 19:11:00   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.166   25 Feb 2002 11:58:16   WINNIE
 * remove parameter for fundIngroup method. This logic will be called directly by Purchase, Redemption and Transfer class for the Navigator Broker Exception List enhancement
 * 
 *    Rev 1.165   18 Feb 2002 10:13:30   KOVACSRO
 * Added new checks in validateAccNum().
 * 
 *    Rev 1.164   Feb 11 2002 12:08:00   YINGBAOL
 * 1.add FeeParameterList
 * 2. Set default Value for GSTExempt
 * 
 *    Rev 1.163   11 Feb 2002 10:08:56   KOVACSRO
 * Added validateAccountNum static method.
 * 
 *    Rev 1.162   Feb 07 2002 08:17:20   JANKAREN
 * Added GSTExempt
 * 
 *    Rev 1.161   Feb 06 2002 17:31:18   ZHANGCEL
 * Change the function validateLifLiraLRif()
 * 
 *    Rev 1.160   10 Jan 2002 16:06:46   KOVACSRO
 * DataGroup change.
 * 
 *    Rev 1.159   Dec 27 2001 10:55:06   YINGBAOL
 * change GetAsPensionPlan: if there is Data_Not_found error appears, clear condition and create a new record for PentionPlan.
 * 
 *    Rev 1.158   17 Dec 2001 11:04:46   KOVACSRO
 * Bug fixed for AMS code.
 * 
 *    Rev 1.157   14 Dec 2001 15:54:18   KOVACSRO
 * bug fixed for response data.
 * 
 *    Rev 1.156   13 Dec 2001 17:24:24   KOVACSRO
 * Changed some get... methods, not to call view 4, if called from transaction builder
 * 
 *    Rev 1.155   Dec 13 2001 13:54:00   JANKAREN
 * Added extra logic for AMSCode
 * 
 *    Rev 1.154   07 Dec 2001 17:23:52   KOVACSRO
 * minor change for getEsopInfo
 * 
 *    Rev 1.153   Dec 03 2001 15:37:02   ZHANGCEL
 * Added a new function: getGroupFundFromGroup()
 * 
 *    Rev 1.152   Nov 29 2001 16:29:22   ZHANGCEL
 * Change logic in function FundClassInGroup() due to moving GroupFundList to Group CBO
 * 
 *    Rev 1.151   Nov 28 2001 12:34:26   JANKAREN
 * Added getDofBirthofOwnerSeq01, getAgeofOwnerSeq01 and logic for AMSCode
 * 
 *    Rev 1.150   20 Nov 2001 16:42:56   KOVACSRO
 * Modified getTransactionList() to be able to start with an empty list which can grow with every anotherAccount() call on it.
 * 
 *    Rev 1.149   19 Nov 2001 09:53:34   KOVACSRO
 * delete response data if receive failed.
 * 
 *    Rev 1.148   14 Nov 2001 13:32:56   KOVACSRO
 * bug fixed in init() (was going into an infinite loop when severity was greater than warning)
 * 
 *    Rev 1.147   14 Nov 2001 09:34:06   KOVACSRO
 * synch up to 1.144.1.2 and some doPopulateField changes.
 * 
 *    Rev 1.146   Oct 17 2001 15:20:50   FENGYONG
 * bug fix for calculate fundbalance
 * 
 *    Rev 1.145   15 Oct 2001 12:15:06   KOVACSRO
 * init will not call anymore view 4. view 4 will be called by doPopulateField, when needed.
 * 
 *    Rev 1.144   Oct 05 2001 16:06:28   YINGBAOL
 * put addcondition back for taxtype and account designation check
 * 
 *    Rev 1.143   04 Oct 2001 15:05:52   KOVACSRO
 * Added SettledFieldsInitialized in order to clarify if these fields were set by eCom.
 * 
 *    Rev 1.142   03 Oct 2001 15:21:22   KOVACSRO
 * Reversed 1.140. This bug fixed in JTradesProcess.
 * 
 *    Rev 1.141   02 Oct 2001 11:44:26   KOVACSRO
 * Removed getEsopHistoricalList() and modified getEsopInfo.
 * 
 *    Rev 1.140   Oct 01 2001 13:08:18   FENGYONG
 * bug fix for ecom flag
 * 
 *    Rev 1.139   26 Sep 2001 14:04:26   WINNIE
 * title restriction enhancement
 * 
 *    Rev 1.138   24 Sep 2001 12:27:52   KOVACSRO
 * Added getESoPHistoricalList.
 * 
 *    Rev 1.137   20 Sep 2001 15:36:32   WINNIE
 * fix memory leak; skip age 69 validation if entityid = 0
 * 
 *    Rev 1.136   17 Sep 2001 16:45:04   WINNIE
 * title restriction escrow enhancement
 * 
 *    Rev 1.135   Sep 12 2001 11:03:10   ZHANGCEL
 * Comment  the code for cloneing AccountEntityXref. move it to AccountEntityXref.cpp 
 * 
 *    Rev 1.134   03 Sep 2001 13:20:16   HSUCHIN
 * getAcctSplitCommList bug fix
 * 
 *    Rev 1.133   23 Aug 2001 14:45:20   HSUCHIN
 * added getAcctSplitCommList
 * 
 *    Rev 1.132   Aug 23 2001 12:48:22   JANKAREN
 * Added getAsPensionPlan()
 * 
 *    Rev 1.131   16 Aug 2001 14:03:24   KOVACSRO
 * ESoP changes.
 * 
 *    Rev 1.130   Aug 16 2001 13:27:02   ZHANGCEL
 * Added a new function: getMatchTransferList()
 * 
 *    Rev 1.129   15 Aug 2001 14:18:28   KOVACSRO
 * small change.
 * 
 *    Rev 1.128   10 Aug 2001 17:05:34   WINNIE
 * default value for StopFCbal
 * 
 *    Rev 1.127   10 Aug 2001 13:40:06   KOVACSRO
 * Took out view 50 and 51 for eFan.
 * 
 *    Rev 1.126   Aug 10 2001 09:40:12   ZHANGCEL
 * Added a missing field StopFCrebal into CLASS_FIELD_INFO
 * 
 *    Rev 1.125   08 Aug 2001 14:21:26   HSUCHIN
 * added two functions getTransactionHistoryList and getLastActiveTransactionHistoryList
 * 
 *    Rev 1.124   08 Aug 2001 14:17:04   KOVACSRO
 * Getting some fields from eCom for Efan.
 * 
 *    Rev 1.123   05 Aug 2001 16:14:04   HSUCHIN
 * added getRSPcontributionList function
 * 
 *    Rev 1.122   Aug 04 2001 22:01:56   YINGBAOL
 * condition clearance
 * 
 *    Rev 1.121   Aug 02 2001 03:28:10   YINGBAOL
 * take out validation for DateOfReg after consulting Patrick
 * 
 *    Rev 1.120   31 Jul 2001 17:04:00   KOVACSRO
 * Added getESoPInfo.
 * 
 *    Rev 1.119   27 Jul 2001 14:03:06   KOVACSRO
 * Changed FundClassTradeMin.
 * 
 *    Rev 1.118   13 Jul 2001 14:47:06   YINGZ
 * fix 0 cut problem for cnd
 * 
 *    Rev 1.117   Jul 11 2001 10:52:28   JANKAREN
 * Bug fix
 * 
 *    Rev 1.116   Jul 04 2001 16:09:08   JANKAREN
 * bug fix for percent of units
 * 
 *    Rev 1.115   11 Jun 2001 10:14:02   YINGZ
 * add SavePlanExist
 * 
 *    Rev 1.114   22 May 2001 14:26:16   KOVACSRO
 * syncup SSB(1.108.1.9)
 * 
 *    Rev 1.113   22 May 2001 09:44:42   KOVACSRO
 * Sync up SSB(1.108.1.8)
 * 
 *    Rev 1.112   May 18 2001 12:47:42   JANKAREN
 * Sync up SSB(1.108.1.7)
 * 
 *    Rev 1.111   11 May 2001 11:50:52   HSUCHIN
 * Sync up with SSB (1.108.1.6)
 * 
 *    Rev 1.110   May 08 2001 16:35:12   FENGYONG
 * Add transtype for Pending of fundexist
 * 
 *    Rev 1.109   03 May 2001 14:06:46   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.108   Apr 02 2001 11:17:28   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.107   30 Mar 2001 17:09:26   BUZILAMI
 * Systematic bank changes
 * 
 *    Rev 1.105   19 Mar 2001 11:59:48   BUZILAMI
 * fixed a refresh problem
 * 
 *    Rev 1.104   Mar 18 2001 19:20:56   WINNIE
 * add social code to class field info
 * 
 *    Rev 1.103   Mar 13 2001 11:09:24   YINGZ
 * add functions getAccountHoldingsByCurrencyList etc
 * 
 *    Rev 1.102   Mar 06 2001 15:52:26   WINNIE
 * bug fix for assignment of default value for branch code if salesrepByBranch feature is not active
 * 
 *    Rev 1.101   Mar 01 2001 16:43:20   BUZILAMI
 * field NumEntry was removed from view
 * 
 *    Rev 1.100   Mar 01 2001 14:21:54   ZHANGCEL
 * Added a new function: getEntityIdForAcctOwnerSeq1()
 * 
 *    Rev 1.99   Feb 20 2001 13:30:18   DINACORN
 * EffectiveDate taken from Shareholder in NASU
 * 
 *    Rev 1.98   Feb 19 2001 15:16:46   ZHANGCEL
 * Adde new functions: getAcctOwnerEntities(), getBeneficiaries(), getAnnitants() , getAcctOwners(), isSpousalBemeficiary(), isChildBeneficiary() and isBeneficiary()
 * 
 *    Rev 1.97   Feb 12 2001 16:58:22   KOVACSRO
 * Implemented getAccountTradesList().
 * 
 *    Rev 1.96   Feb 01 2001 10:50:14   JANKAREN
 * Sync up to C2/C3 - taxation type permission check.
 * 
 *    Rev 1.95   Jan 31 2001 14:30:44   JANKAREN
 * move checking of plan type and minimum from FundDetailList to FundDetail
 * 
 *    Rev 1.94   Jan 24 2001 12:50:22   KOVACSRO
 * Modified getPendingTradeList();
 * 
 *    Rev 1.93   Jan 22 2001 11:18:56   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.92   Jan 17 2001 12:03:16   KOVACSRO
 * Added worksessionID param. for getMgmtCoOptions().
 * 
 *    Rev 1.91   Jan 17 2001 10:34:00   KOVACSRO
 * Modified getPendingTradesList and added deletePendingTradeList.
 * 
 *    Rev 1.90   Jan 11 2001 16:36:10   VASILEAD
 * Fixed the linking warning
 * 
 *    Rev 1.89   Jan 10 2001 18:03:32   WINNIE
 * add PurchaseGICAllow and AMSFundAllow method
 * 
 *    Rev 1.87   Dec 20 2000 16:17:08   WINNIE
 * move checking of minimum at fund class level to FundDetailList; move calculation of amount value in fundcurrency to Trade.cpp; fix bug for minimum fund balance; define class level pointer for FundDetailList
 * 
 *    Rev 1.86   Dec 17 2000 20:21:58   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.85   Dec 06 2000 12:16:52   DINACORN
 * Synchronization to C2/C3: Added logic in setRecipientType ( Check both TaxType and AccountType), Reset the CreateRep when user select an existing salesrep; Added LockedIn to classFieldInfo; Add getErrMsg(), validateRESPEntity(), added logic for getting RecipientType fro recipientTypeList; Create validateTaxType method, including validation against acctdesignation; Skip checking of age in NASU flow since information has not yet been entered.
 * 
 *    Rev 1.84   Nov 24 2000 12:08:58   WINNIE
 * break up canTradeFundClass into multiple methods based on trade type; move escow checking to AcctEntityXref etc.
 * 
 *    Rev 1.83   Nov 20 2000 13:42:30   OLTEANCR
 * enabled conditions
 * 
 *    Rev 1.82   Nov 17 2000 14:10:46   OLTEANCR
 * added acct.nr. validations in canRedeem and canTrade
 * 
 *    Rev 1.81   Nov 15 2000 15:35:04   WINNIE
 * add canPurchase, canRedeem, canTrfExchIn, canTrfExhcOut, getCertificateList etc.
 * 
 *    Rev 1.80   Nov 08 2000 10:25:04   YINGBAOL
 * fix bug with locale
 * 
 *    Rev 1.79   Nov 02 2000 15:58:06   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.78   Nov 02 2000 14:25:20   VASILEAD
 * Added workSeesionId parameter for Mgmtco based CBOs
 * 
 *    Rev 1.77   Oct 31 2000 17:00:16   KOVACSRO
 * Changed logic for Pension Jurisdiction to work same for new or old accounts.
 * 
 *    Rev 1.76   Oct 31 2000 10:53:40   KOVACSRO
 * Added validation for PensionJurisdiction (whenever is updateable it must be not null)
 * 
 *    Rev 1.75   Oct 30 2000 18:46:06   ZHANGCEL
 * Added a new field ExistBeneficiary and validation for DateOfReg
 * 
 *    Rev 1.74   Oct 27 2000 10:23:04   KOVACSRO
 * Implemented getLipRaterExist().
 * 
 *    Rev 1.73   Oct 24 2000 09:58:08   KOVACSRO
 * Added setUpdatedFlag(..,false) for LockedIn field.
 * 
 *    Rev 1.72   Oct 23 2000 12:44:10   KOVACSRO
 * Bug fixed for LockedIn field.
 * 
 *    Rev 1.71   Oct 22 2000 15:46:32   WINNIE
 * broker name assignment
 * 
 *    Rev 1.70   Oct 20 2000 15:46:26   KOVACSRO
 * Fixed IntermAccount field.
 * 
 *    Rev 1.69   Oct 19 2000 10:48:48   WINNIE
 * Fix display of broker, branch, salesrep name
 * 
 *    Rev 1.68   Oct 18 2000 17:14:28   KOVACSRO
 * Bug fixed.
 * 
 *    Rev 1.67   Oct 18 2000 15:54:06   KOVACSRO
 * Fixed 'PensionJurisdiction' field.
 * 
 *    Rev 1.66   Oct 18 2000 15:26:12   DINACORN
 * Changes in logic for dynamic loading of AcctType based on TaxType
 * 
 *    Rev 1.65   Oct 18 2000 14:49:44   WINNIE
 * If salesRepByBranch is inactive, system should allow branch be blank and populate the value from AgentList CBO
 * 
 *    Rev 1.64   Oct 17 2000 14:23:50   KOVACSRO
 * Modified getContractInfoList()
 * 
 *    Rev 1.63   Oct 17 2000 13:32:34   DINACORN
 * Logic for dynamic loading of account type based on TaxType
 * 
 *    Rev 1.62   Oct 13 2000 15:18:54   KOVACSRO
 * Modified getContractInfoList() to initialize list for new accounts too.
 * 
 *    Rev 1.61   Oct 13 2000 13:39:22   ZHANGCEL
 * Add function GroupContributMax() for Trad amount validation
 * 
 *    Rev 1.60   Oct 04 2000 11:51:02   YINGBAOL
 * fix crash for launching RIF from NASU
 * 
 *    Rev 1.59   Oct 03 2000 18:28:22   WINNIE
 * Check effective date for new account; else check FirstEffectiveDate
 * 
 *    Rev 1.58   Sep 29 2000 13:27:12   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.57   Sep 28 2000 15:29:00   YINGBAOL
 * change get RRIF_LIF_LIST
 * 
 *    Rev 1.56   Sep 27 2000 16:03:24   YINGZ
 * clone first/last names
 * 
 *    Rev 1.55   Sep 26 2000 19:13:16   WINNIE
 * Load substitution list for intermediary
 * 
 *    Rev 1.54   Sep 25 2000 15:36:02   WINNIE
 * bug fixes for RESP taxtype validation
 * 
 *    Rev 1.53   Sep 25 2000 10:17:14   WINNIE
 * Bug fix for taxtype readonly flag; bug fix for cloning account method: changing checkagents to void function; bug fix for RESP account : should getfield with format = false for field comparsion.
 * 
 *    Rev 1.52   Sep 23 2000 15:59:40   WINNIE
 * Remove Escrow edit check, logic already exists in AccountEntityXref->ValidateOneAccount
 * 
 *    Rev 1.51   Sep 23 2000 15:43:44   DINACORN
 * Fix for InterAccount field
 * 
 *    Rev 1.50   Sep 14 2000 13:16:50   DINACORN
 * Logic in setAccountDesignation() for IntermCode and IntermAcct.; modified some conditions; logic in getField() for AccountNum and TaxType.
 * 
 *    Rev 1.49   Sep 11 2000 17:52:16   DINACORN
 * Fixed error message bugs for InterCode and InterAccount fields
 * 
 *    Rev 1.48   Sep 11 2000 16:32:16   KOVACSRO
 * fixed crash for init when data not found.
 * 
 *    Rev 1.47   Sep 08 2000 14:55:54   DINACORN
 * moved setFieldReadOnly for InterAccount and InterCode in init()
 * 
 *    Rev 1.46   Sep 08 2000 14:29:04   DINACORN
 * Fixed the IntermediaryCode bug
 * 
 *    Rev 1.45   Sep 06 2000 14:49:10   YINGBAOL
 * change sync.
 * 
 *    Rev 1.44   Sep 05 2000 10:46:12   WINNIE
 * Error message for account type
 * 
 *    Rev 1.43   Aug 31 2000 14:35:12   DINACORN
 * Added more constants in namespace
 * 
 *    Rev 1.42   Aug 30 2000 10:09:06   YINGBAOL
 * add setaccountdesignation method
 * 
 *    Rev 1.41   Aug 28 2000 17:16:58   WINNIE
 * Bug fix for pendingofFundExist
 * 
 *    Rev 1.40   Aug 25 2000 17:20:14   WINNIE
 * Include changes in version 1.38 and 1.37
 * 
 *    Rev 1.38   Aug 25 2000 09:40:10   WINNIE
 * Add AcctGroup validation; Remove ValidateEntityType, code is moved to AccountEntityXref CBO; Add new CBO pointers for Shareholder, GroupList, GroupName, AccountEntityXref and new methods for getting the values.
 * 
 *    Rev 1.37   Aug 23 2000 12:06:58   DINACORN
 * Removed the setting for DRB::GrpCodeLevel, used getField() for DBR::LockedIn, fixed some conditions
 * 
 *    Rev 1.36   Aug 16 2000 10:33:56   DINACORN
 * Added method loadGroupSubstitutionList(), set the field GrpCodeLevel to be used in Dlg
 * 
 *    Rev 1.35   Aug 15 2000 10:10:50   WINNIE
 * Move initialization from dovalidatefield to initialization method; move set field from dovalidatefield to dorelatedchanges; 
 * 
 *    Rev 1.34   Aug 09 2000 10:57:42   WINNIE
 * Add logic to check stop redemption flag
 * 
 *    Rev 1.33   Aug 08 2000 14:21:00   WINNIE
 * Add business rule to validate account type based on the tax type of the account
 * 
 *    Rev 1.32   Aug 02 2000 11:32:08   WINNIE
 * clone entity 01 and 21 for add new account under an existing shareholder; bug fix for getContractInfoList for transaction builder
 * 
 *    Rev 1.31   Aug 01 2000 13:53:42   WINNIE
 * initial acct designation; use acctGroup rather than shareholder group code; clean up taxtype rule and account entity relationship validation
 * 
 *    Rev 1.30   Jul 28 2000 14:27:22   DINACORN
 * Added EntityType rules and fixed more bussiness rules
 * 
 *    Rev 1.29   Jul 12 2000 13:24:48   DINACORN
 * Added more bussines rules
 * 
 *    Rev 1.28   Jun 29 2000 14:50:48   WINNIE
 * Check effective of the account using FirstEffective 
 * 
 *    Rev 1.27   Jun 27 2000 13:18:48   WINNIE
 * Add new parameter to CanTrade to validate the account against trade date
 * 
 *    Rev 1.26   Jun 23 2000 17:38:16   DINACORN
 * Added view 142 and more business rules
 * 
 *    Rev 1.25   Jun 16 2000 13:31:24   DINACORN
 * Added conditions for canadian enhancement
 * 
 *    Rev 1.24   Jun 15 2000 14:10:10   DINACORN
 * Add conditions for Canadian Enhancement
 * 
 *    Rev 1.23   Jun 13 2000 17:33:38   HUANGSHA
 * validation for trade
 * 
 *    Rev 1.22   May 31 2000 16:15:48   YINGBAOL
 * more validation added
 * 
 *    Rev 1.21   May 16 2000 17:57:30   WINNIE
 * Fix edit check for escrow :M3
 * 
 *    Rev 1.20   May 12 2000 17:45:20   ZHANGCEL
 * Added function getContractInfoList( )
 * 
 *    Rev 1.19   May 12 2000 14:50:38   WINNIE
 * fix escrow date comparison
 * 
 *    Rev 1.18   May 05 2000 16:48:16   WINNIE
 * M3 : exchange rate
 * 
 *    Rev 1.17   May 02 2000 13:29:04   WINNIE
 * m3 fix
 * 
 *    Rev 1.16   May 01 2000 12:38:46   WINNIE
 * check allocation and account level locked-in
 * 
 *    Rev 1.15   Apr 18 2000 11:12:36   WINNIE
 * more trade business rule
 * 
 *    Rev 1.14   Apr 15 2000 15:28:28   WINNIE
 * fix for index set up in funtolist; fix allowable exchange edit chk; fix account balance ;
 * 
 *    Rev 1.13   Apr 14 2000 17:55:42   WINNIE
 * Move validation to Groupfund and MFAccount CBO to allow other CBO to use the same method. Bug fix for NumOfDecimals function
 * 
 *    Rev 1.12   Apr 12 2000 19:02:18   WINNIE
 * trade minimum checking
 * 
 *    Rev 1.11   Apr 07 2000 18:24:48   WINNIE
 * add index to get account fund class balance 
 * 
 *    Rev 1.10   Mar 31 2000 14:29:40   HSUCHIN
 * M2 sync up
 * 
 *    Rev 1.9   Mar 29 2000 15:55:02   YINGZ
 * code sync
 * 
 *    Rev 1.8   Mar 27 2000 14:22:20   WINNIE
 * Add condition for trading validation : CanTrade method
 * 
 *    Rev 1.7   Mar 22 2000 09:00:28   PETOLESC
 * Added Tax Rates, RESP dialogs.
 * 
 *    Rev 1.6   Mar 17 2000 16:48:14   PETOLESC
 * Added RESP objects loading. For now, I commented them out.
 * 
 *    Rev 1.5   Mar 15 2000 09:49:28   BUZILA
 * fixed ShrNum in CanTrade
 * 
 *    Rev 1.4   Mar 15 2000 09:45:40   PETOLESC
 * temp checkin
 * 
 *    Rev 1.3   Mar 14 2000 11:38:02   WINNIE
 * new method for trade checking
 * 
 *    Rev 1.2   Mar 06 2000 17:14:46   WINNIE
 * Add new function 'CanAcctTrade' to check if the selected account can trade with the particular transaction type
 * 
 *    Rev 1.1   Feb 28 2000 15:31:08   PRAGERYA
 * Check-in For Mihai
 * 
 *    Rev 1.0   Feb 15 2000 11:00:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.88   Feb 07 2000 12:24:36   WINNIE
 * Add validation for account effective date to stop user from entering date before the current account effectivedate.
 * 
 *    Rev 1.87   Feb 03 2000 09:09:02   BUZILA
 * Marked non updatable COA flags as CALCULATED_FIELD
 * 
 *    Rev 1.86   Feb 02 2000 17:54:04   POPESCUS
 * quick fix to another quick fix
 * 
 *    Rev 1.85   Feb 02 2000 14:56:26   POPESCUS
 * quick fix
 * 
 *    Rev 1.84   Feb 01 2000 14:36:28   BUZILA
 * added lValidateGroup parameter to doValidateAll method
 * 
 *    Rev 1.83   Feb 01 2000 12:34:08   POPESCUS
 * remove the account from the shareholder mfaccount list when rolling back
 * 
 *    Rev 1.82   Jan 30 2000 17:56:52   POPESCUS
 * SIT fixes
 * 
 *    Rev 1.81   Jan 28 2000 15:20:46   POPESCUS
 * fixes to SIT's
 * 
 *    Rev 1.80   Jan 28 2000 12:26:42   POPESCUS
 * lock the account number if accnum is C or S
 * 
 *    Rev 1.79   Jan 26 2000 19:44:56   POPESCUS
 * fixes for th release
 * 
 *    Rev 1.78   Jan 25 2000 17:14:32   POPESCUS
 * fixes for validation of a new account
 * 
 *    Rev 1.77   Jan 24 2000 14:06:22   POPESCUS
 * fix for Zijan
 * 
 *    Rev 1.76   Jan 23 2000 18:48:44   POPESCUS
 * changes related to creating a slsrep on the fly
 * 
 *    Rev 1.75   Jan 21 2000 13:14:56   BUZILA
 * using dg 0 in Distributions Init
 * 
 *    Rev 1.74   Jan 21 2000 11:40:58   POPESCUS
 * fixes to the validation for the number
 * 
 *    Rev 1.73   Jan 21 2000 11:11:50   POPESCUS
 * the user can change the account number and the shareholder number
 * 
 *    Rev 1.72   Jan 19 2000 14:48:22   POPESCUS
 * fix
 * 
 *    Rev 1.71   Jan 19 2000 14:42:48   POPESCUS
 * Set a L for the reuquest type, when searching for broker
 * 
 *    Rev 1.70   Jan 19 2000 10:47:00   POPESCUS
 * probably, some fixes
 * 
 *    Rev 1.69   Jan 18 2000 18:18:12   POPESCUS
 * check in for point release
 * 
 *    Rev 1.68   Jan 17 2000 14:51:48   POPESCUS
 * fix some comments
 * 
 *    Rev 1.67   Jan 17 2000 14:00:24   POPESCUS
 * support for refresh and misc
 * 
 *    Rev 1.66   Jan 16 2000 16:59:48   POPESCUS
 * changes to the children lists
 * 
 *    Rev 1.65   Jan 14 2000 17:55:38   PRAGERYA
 * GetDistributionList function modified
 * 
 *    Rev 1.64   Jan 14 2000 15:41:38   POPESCUS
 * another quick fix
 * 
 *    Rev 1.63   Jan 14 2000 14:12:24   POPESCUS
 * fix compiling error
 * 
 *    Rev 1.62   Jan 14 2000 14:06:10   POPESCUS
 * init New for systematic
 * 
 *    Rev 1.61   Jan 14 2000 12:13:06   POPESCUS
 * two fileds are not required any more
 * 
 *    Rev 1.60   Jan 14 2000 09:35:58   POPESCUS
 * fixes in validation
 * 
 *    Rev 1.59   Jan 13 2000 09:52:54   POPESCUS
 * fix a showstopper
 * 
 *    Rev 1.58   Jan 12 2000 11:59:48   POPESCUS
 * cloning an account
 * 
 *    Rev 1.57   Jan 12 2000 08:58:24   POPESCUS
 * changes related to cloning an account and fixing some validation, adding subst sets
 * 
 *    Rev 1.56   Jan 11 2000 08:40:40   POPESCUS
 * fixes and validation
 * 
 *    Rev 1.55   Jan 09 2000 19:11:20   POPESCUS
 * bug fixes?
 * 
 *    Rev 1.54   Jan 09 2000 16:41:24   PRAGERYA
 * Made compilable!
 * 
 *    Rev 1.53   Jan 09 2000 13:19:00   POPESCUS
 * for yakov
 * 
 *    Rev 1.52   Jan 08 2000 15:07:14   POPESCUS
 * ?
 * 
 *    Rev 1.51   Jan 08 2000 14:33:06   POPESCUS
 * added the datagroupid when quering for children lists
 * 
 *    Rev 1.50   Jan 07 2000 15:54:30   POPESCUS
 * just checking in...
 * 
 *    Rev 1.49   Jan 06 2000 12:52:08   POPESCUS
 * fixes for validation
 * 
 *    Rev 1.48   Jan 06 2000 09:58:24   POPESCUS
 * cleanup code and remove some unused methods
 * 
 *    Rev 1.47   Jan 04 2000 10:55:14   POPESCUS
 * cross edits
 * 
 *    Rev 1.46   Dec 31 1999 13:16:00   POPESCUS
 * validations, fixes and misc
 * 
 *    Rev 1.45   Dec 30 1999 14:44:06   POPESCUS
 * added initialization method for fields that are not in the inquiry mode
 * 
 *    Rev 1.44   Dec 24 1999 10:29:52   VASILEAD
 * Fixed NASU flow
 * 
 *    Rev 1.43   Dec 22 1999 18:00:36   BUZILA
 * added COA flags
 * 
 *    Rev 1.42   Dec 22 1999 11:55:52   POPESCUS
 * validation and misc
 * 
 *    Rev 1.41   Dec 21 1999 13:37:14   POPESCUS
 * validations and misc
 * 
 *    Rev 1.40   Dec 20 1999 16:14:42   POPESCUS
 * misc validation
 * 
 *    Rev 1.39   Dec 20 1999 11:21:58   POPESCUS
 * validation and get the top level object
 * 
 *    Rev 1.38   Dec 15 1999 11:08:12   POPESCUS
 * added new boolean param to the lists accessor methods; whether to inquire the database or not
 * 
 *    Rev 1.37   Dec 14 1999 18:06:16   BUZILA
 * added AllTransactionList to objectFieldInfo, taken  out NO_BASE_DELETE
 * 
 *    Rev 1.36   Dec 14 1999 17:52:50   ZHANGCEL
 * Modify validattion
 * 
 *    Rev 1.35   Dec 14 1999 09:48:08   ZHANGCEL
 * Validations for TaxType, AcctType and BrokerCode
 * 
 *    Rev 1.34   Dec 12 1999 16:25:46   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
 * 
 *    Rev 1.33   Dec 10 1999 12:47:48   POPESCUS
 * code review, added mailing address in the commit logic and some other minor changes
 * 
 *    Rev 1.32   Dec 09 1999 10:43:38   POPESCUS
 * Fixed some memory leaks
*/
