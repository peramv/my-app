#pragma message("including "__FILE__ )
#ifndef PLATFORM_H
   #include <win32\platform.h>
#endif

#ifndef BFREQUEST_HPP
   #include "DSTCRequest.hpp"
#endif

namespace CORFAX
{
   const char *const CFLOGON_TRANS  = "CFLOGON";
   const char *const CFLOGOFF_TRANS = "CFLOGOFF";
   const char *const CFX_TRANS      = "CFXTRAN";
}

namespace DSTC_REQUEST
{

   extern CLASS_EXPORT const DSTCRequest LOGON                                   ( CORFAX::CFLOGON_TRANS,  "00001", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest LOGOFF                                  ( CORFAX::CFLOGOFF_TRANS, "00002", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SEARCH                                  ( CORFAX::CFX_TRANS,      "00003", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest MFACCOUNT                               ( CORFAX::CFX_TRANS,      "00004", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest REMARKS                                 ( CORFAX::CFX_TRANS,      "00005", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SYSTEMATIC                              ( CORFAX::CFX_TRANS,      "00006", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SYSTEMATIC_ALLOCATIONS                  ( CORFAX::CFX_TRANS,      "00007", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DEMOGRAPHICS                            ( CORFAX::CFX_TRANS,      "00011", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACB                                     ( CORFAX::CFX_TRANS,      "00015", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACC_DISTRIB                             ( CORFAX::CFX_TRANS,      "00016", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRANSACTION_LIST                        ( CORFAX::CFX_TRANS,      "00017", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CERTIFICATE                             ( CORFAX::CFX_TRANS,      "00018", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FREE_UNIT                               ( CORFAX::CFX_TRANS,      "00019", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest MFACCOUNT_HOLDINGS                      ( CORFAX::CFX_TRANS,      "00020", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest HISTORICAL_MARKET_VALUE                 ( CORFAX::CFX_TRANS,      "00020", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CHEQUE                                  ( CORFAX::CFX_TRANS,      "00021", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRANSACTION_DETAILS                     ( CORFAX::CFX_TRANS,      "00022", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FUND_INFO                               ( CORFAX::CFX_TRANS,      "00023", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CHANGE_PASSWORD                         ( CORFAX::CFX_TRANS,      "00039", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ADDRESS                                 ( CORFAX::CFX_TRANS,      "00043", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest COA_NAVIG                               ( CORFAX::CFX_TRANS,      "00049", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ENTITY                                  ( CORFAX::CFX_TRANS,      "00050", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ENTITY_IDS                              ( CORFAX::CFX_TRANS,      "00051", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest BANK_INSTRUCTION                        ( CORFAX::CFX_TRANS,      "00052", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PENDING_TRADE                           ( CORFAX::CFX_TRANS,      "00053", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PENDING_TRADE_DETAILS                   ( CORFAX::CFX_TRANS,      "00054", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRANSACTIONBANKINSTR                    ( CORFAX::CFX_TRANS,      "00055", DSTCRequest::TYPE_QUERY );
#ifdef _GUI                                                                      
   extern CLASS_EXPORT const DSTCRequest FUND_DETAIL                             ( CORFAX::CFX_TRANS,      "00056", DSTCRequest::TYPE_SYSLOAD );
#else                                                                            
   extern CLASS_EXPORT const DSTCRequest FUND_DETAIL                             ( CORFAX::CFX_TRANS,      "00056", DSTCRequest::TYPE_QUERY );
#endif                                                                           
   extern CLASS_EXPORT const DSTCRequest ALLOCATIONS                             ( CORFAX::CFX_TRANS,      "00058", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AUTOTRANSFER                            ( CORFAX::CFX_TRANS,      "00059", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PT_ALLOCATIONS                          ( CORFAX::CFX_TRANS,      "00060", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest WHERE_USED                              ( CORFAX::CFX_TRANS,      "00061", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest INTEREST_ACCRUAL                        ( CORFAX::CFX_TRANS,      "00062", DSTCRequest::TYPE_QUERY );
#ifdef _GUI                                                                      
   extern CLASS_EXPORT const DSTCRequest FUND_MASTER                             ( CORFAX::CFX_TRANS,      "00063", DSTCRequest::TYPE_SYSLOAD );
#else                                                                            
   extern CLASS_EXPORT const DSTCRequest FUND_MASTER                             ( CORFAX::CFX_TRANS,      "00063", DSTCRequest::TYPE_QUERY );
#endif                                                                           
   extern CLASS_EXPORT const DSTCRequest USER_ACCESS                             ( CORFAX::CFX_TRANS,      "00064", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESPINFO                                ( CORFAX::CFX_TRANS,      "00066", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RRIF_LIF_LRIF_INFO                      ( CORFAX::CFX_TRANS,      "00067", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RRIF_LIF_LRIF_ALLOC                     ( CORFAX::CFX_TRANS,      "00068", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SHAREHOLDER                             ( CORFAX::CFX_TRANS,      "00069", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ADDRESSES_ENTITY                        ( CORFAX::CFX_TRANS,      "00071", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ADDRESSBOOK_UPDATE                      ( CORFAX::CFX_TRANS,      "00072", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest PERSISTENCE_START                       ( CORFAX::CFX_TRANS,      "00073", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest PERSISTENCE_ROLLBACK                    ( CORFAX::CFX_TRANS,      "10074", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest PERSISTENCE_COMMIT                      ( CORFAX::CFX_TRANS,      "00074", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest SHAREHOLDER_UPDATE                      ( CORFAX::CFX_TRANS,      "00075", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest MFACCOUNT_UPDATE                        ( CORFAX::CFX_TRANS,      "00076", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ACCOUNTENTITY_UPDATE                    ( CORFAX::CFX_TRANS,      "00077", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ENTITY_UPDATE                           ( CORFAX::CFX_TRANS,      "00078", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ENTITYSEARCHID_UPDATE                   ( CORFAX::CFX_TRANS,      "00079", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ENTITYADDRESS_UPDATE                    ( CORFAX::CFX_TRANS,      "00080", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest DEMOGRAPHICS_UPDATE                     ( CORFAX::CFX_TRANS,      "00081", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest MGMT_CO_OPTIONS                         ( CORFAX::CFX_TRANS,      "00083", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest SYSTEMATICS_UPDATE                      ( CORFAX::CFX_TRANS,      "00084", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest REMARKS_UPDATE                          ( CORFAX::CFX_TRANS,      "00085", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest INTERMEDIARY                            ( CORFAX::CFX_TRANS,      "00086", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TAXTYPE_RULE                            ( CORFAX::CFX_TRANS,      "00087", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest GROUP                                   ( CORFAX::CFX_TRANS,      "00088", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ALLOCATIONS_UPDATE                      ( CORFAX::CFX_TRANS,      "00089", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest BROKER                                  ( CORFAX::CFX_TRANS,      "00090", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest BROKER_LIST                             ( CORFAX::CFX_TRANS,      "00090", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest BRANCH                                  ( CORFAX::CFX_TRANS,      "00091", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ADVISOR                                 ( CORFAX::CFX_TRANS,      "00092", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest JADVISORTRANS                           ( CORFAX::CFX_TRANS,      "00093", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest JADVISORSUMM                            ( CORFAX::CFX_TRANS,      "00094", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AUMATICTRANSFER_UPDATE                  ( CORFAX::CFX_TRANS,      "00095", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest DISTRIBUTIONS_UPDATE                    ( CORFAX::CFX_TRANS,      "00096", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest BANKING_UPDATE                          ( CORFAX::CFX_TRANS,      "00097", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest GROUPFUNDLIST                           ( CORFAX::CFX_TRANS,      "00098", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FUND_TO                                 ( CORFAX::CFX_TRANS,      "00099", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest BANKLIST                                ( CORFAX::CFX_TRANS,      "00100", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CURRENCYLIST                            ( CORFAX::CFX_TRANS,      "00101", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest JSHRSUMM                                ( CORFAX::CFX_TRANS,      "00103", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest JFUNDINDIV                              ( CORFAX::CFX_TRANS,      "00104", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CONTRACTINFO_LIST                       ( CORFAX::CFX_TRANS,      "00105", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest GUARANTEEINFO                           ( CORFAX::CFX_TRANS,      "00106", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FEEINFOINQUIRY                          ( CORFAX::CFX_TRANS,      "00107", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest MINMAX                                  ( CORFAX::CFX_TRANS,      "00109", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest HISTORICAL_ACCOUNT                      ( CORFAX::CFX_TRANS,      "00110", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESPTRANSACTIONS_DETAILS                ( CORFAX::CFX_TRANS,      "00111", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TAXRATES                                ( CORFAX::CFX_TRANS,      "00112", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCOUNT_MAILING                         ( CORFAX::CFX_TRANS,      "00113", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCTMAILING_UPDATE                      ( CORFAX::CFX_TRANS,      "00114", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest TRADES_LIST                             ( CORFAX::CFX_TRANS,      "00115", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest NOMINEE_INTER_ADDRESS                   ( CORFAX::CFX_TRANS,      "00116", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRANSACTION_SUMMARY                     ( CORFAX::CFX_TRANS,      "00117", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCOUNT_INQUIRY                         ( CORFAX::CFX_TRANS,      "00118", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SYS_INDEX                               ( CORFAX::CFX_TRANS,      "00119", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCSHRNUMCHECK                          ( CORFAX::CFX_TRANS,      "00120", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACQFEEINQUIRY                           ( CORFAX::CFX_TRANS,      "00121", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACTIVE_BATCH                            ( CORFAX::CFX_TRANS,      "00124", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FUND_TYPE_LIST                          ( CORFAX::CFX_TRANS,      "00126", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRANS_NUM                               ( CORFAX::CFX_TRANS,      "00127", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RRIF_LIF_LRIF_INFO_UPDATE               ( CORFAX::CFX_TRANS,      "00129", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest RRIF_LIF_LRIF_PAYMENT_CALC              ( CORFAX::CFX_TRANS,      "00130", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CONTRACT_UPDATE                         ( CORFAX::CFX_TRANS,      "00131", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest MASTER_CONTRACT                         ( CORFAX::CFX_TRANS,      "00133", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest EXCH_RATE                               ( CORFAX::CFX_TRANS,      "00134", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DATE_VALIDATION                         ( CORFAX::CFX_TRANS,      "00135", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRANSLATION_LIST                        ( CORFAX::CFX_TRANS,      "00136", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest HYPOTHETICALRED                         ( CORFAX::CFX_TRANS,      "00137", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest REDCODEBYTAXTYPE                        ( CORFAX::CFX_TRANS,      "00138", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SEQ_FUND_VALIDATION                     ( CORFAX::CFX_TRANS,      "00140", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ERR_MSG_RULES                           ( CORFAX::CFX_TRANS,      "00142", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest REDEMPTION_VALIDATION                   ( CORFAX::CFX_TRANS,      "00143", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest LIP_RATE_EXIST                          ( CORFAX::CFX_TRANS,      "00144", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest VERIFICATIONCONF                        ( CORFAX::CFX_TRANS,      "00145", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RECIPIENT_LIST                          ( CORFAX::CFX_TRANS,      "00146", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DEPOSIT                                 ( CORFAX::CFX_TRANS,      "00147", DSTCRequest::TYPE_QUERY );  
   extern CLASS_EXPORT const DSTCRequest FUND_SPONSORS                           ( CORFAX::CFX_TRANS,      "00148", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest MGMT_CO_OPTIONS_NEXT                    ( CORFAX::CFX_TRANS,      "00149", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest AVAILABILITY                            ( CORFAX::CFX_TRANS,      "00150", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SPLIT_COMMISSION_LIST                   ( CORFAX::CFX_TRANS,      "00151", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DEF_SPLIT_COMMISSION_LIST               ( CORFAX::CFX_TRANS,      "00158", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SAVINGPLAN_MASTER_LIST                  ( CORFAX::CFX_TRANS,      "00159", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest HIST_SYS_INDEX_LIST                     ( CORFAX::CFX_TRANS,      "00160", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest DUPLICATE_TRADE_CHECK                   ( CORFAX::CFX_TRANS,      "00156", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest MULTI_CONTRACT_UPDATE                   ( CORFAX::CFX_TRANS,      "00161", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest TRADE_MIN_AMT_CHECK                     ( CORFAX::CFX_TRANS,      "00167", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ESOP_INFO_UPDATE                        ( CORFAX::CFX_TRANS,      "00168", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ESOP_INFO                               ( CORFAX::CFX_TRANS,      "00169", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest GUARANTEE_SUMMARY                       ( CORFAX::CFX_TRANS,      "00170", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AS_PENSION_PLAN                         ( CORFAX::CFX_TRANS,      "00171", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AS_PENSION_PLAN_UPDATE                  ( CORFAX::CFX_TRANS,      "00172", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest RSP_CONTRIBUTION_LIST                   ( CORFAX::CFX_TRANS,      "00173", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RSP_RECEIPT_LIST                        ( CORFAX::CFX_TRANS,      "00174", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCOUNT_SPLITCOMM_LIST                  ( CORFAX::CFX_TRANS,      "00175", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCOUNT_SPLITCOMM_UPDATE                ( CORFAX::CFX_TRANS,      "00176", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ESOP_HISTORICAL_ACCOUNT                 ( CORFAX::CFX_TRANS,      "00178", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_MASTER_LIST                         ( CORFAX::CFX_TRANS,      "00179", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_CODE                                ( CORFAX::CFX_TRANS,      "00179", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRADE_DATE_LAG_VALIDATION               ( CORFAX::CFX_TRANS,      "00181", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SLSREP_LIST                             ( CORFAX::CFX_TRANS,      "00191", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SEQ_FUND_VALIDATION_NUSU                ( CORFAX::CFX_TRANS,      "00193", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCOUNT_SEARCH                          ( CORFAX::CFX_TRANS,      "00198", DSTCRequest::TYPE_QUERY ); 
   extern CLASS_EXPORT const DSTCRequest FEE_PARAM                               ( CORFAX::CFX_TRANS,      "00194", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FEE_SCALE                               ( CORFAX::CFX_TRANS,      "00195", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FEE_PARAM_UPDATE                        ( CORFAX::CFX_TRANS,      "00196", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FUND_FEE                                ( CORFAX::CFX_TRANS,      "00197", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest MF_ACCRUAL                              ( CORFAX::CFX_TRANS,      "00199", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SETTLEMENT_LIST                         ( CORFAX::CFX_TRANS,      "00200", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SETTLEMENT_UPDATE                       ( CORFAX::CFX_TRANS,      "00201", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest PENSION_INFO                            ( CORFAX::CFX_TRANS,      "00202", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PENSION_INFO_UPDATE                     ( CORFAX::CFX_TRANS,      "00203", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ACCOUNTREVIEW_LIST                      ( CORFAX::CFX_TRANS,      "00204", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCOUNTREVIEW_LIST_UPDATE               ( CORFAX::CFX_TRANS,      "00205", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest SETTLEMENT_TOTAL                        ( CORFAX::CFX_TRANS,      "00206", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRANSTYPE_FILEPROC_LIST                 ( CORFAX::CFX_TRANS,      "00207", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SETTLEMENT_MAIN                         ( CORFAX::CFX_TRANS,      "00208", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest INTERNATIONAL_WIRE                      ( CORFAX::CFX_TRANS,      "00210", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TAXJURISDICTIONLIMIT_LIST               ( CORFAX::CFX_TRANS,      "00211", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest BANK_ACCT_USAGE                         ( CORFAX::CFX_TRANS,      "00212", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest MEXT_PROC_DATE                          ( CORFAX::CFX_TRANS,      "00213", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ENTITY_ADDRESS_MAILING                  ( CORFAX::CFX_TRANS,      "00214", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ENTITY_MAIL_DELIVER_OPTION              ( CORFAX::CFX_TRANS,      "00215", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_MAILING_OVERRIDE_UPDATE            ( CORFAX::CFX_TRANS,      "00216", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ENTITYADDRESSMAILING_UPDATE             ( CORFAX::CFX_TRANS,      "00216", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest HYPO_REDEMPTION_SUMMARY                 ( CORFAX::CFX_TRANS,      "00398", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest AMS_FUND_ALLOC_LIST                     ( CORFAX::CFX_TRANS,      "00218", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_INFO_UPDATE                         ( CORFAX::CFX_TRANS,      "00219", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest REPORT_UPDATE                           ( CORFAX::CFX_TRANS,      "00220", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest REPORT_STATUS                           ( CORFAX::CFX_TRANS,      "00221", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PRINTER_LIST                            ( CORFAX::CFX_TRANS,      "00222", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_ACCOUNT_CHECK                       ( CORFAX::CFX_TRANS,      "00223", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest REPORT_PARAM                            ( CORFAX::CFX_TRANS,      "00224", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PRINT_REQUEST                           ( CORFAX::CFX_TRANS,      "00225", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest HYPO_REDEMPTION_DETAILS                 ( CORFAX::CFX_TRANS,      "00227", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest TIMEZONE                                ( CORFAX::CFX_TRANS,      "00228", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FUND_COMM_GROUP_LIST                    ( CORFAX::CFX_TRANS,      "00229", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FEE_PARAM_SYSTEM_LIST                   ( CORFAX::CFX_TRANS,      "00230", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FEE_PARAM_SYSTEM_SCALE_LIST             ( CORFAX::CFX_TRANS,      "00231", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FEE_PARAM_SYSTEM_UPDATE                 ( CORFAX::CFX_TRANS,      "00232", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FUNDLMTOVERRIDELIST                     ( CORFAX::CFX_TRANS,      "00236", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SHR_FAMILY                              ( CORFAX::CFX_TRANS,      "00233", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SHR_FAMILY_UPDATE                       ( CORFAX::CFX_TRANS,      "00234", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FAMILY_MASTER                           ( CORFAX::CFX_TRANS,      "00235", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PROTECTED_FUND_LIST                     ( CORFAX::CFX_TRANS,      "00237", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PROTECTED_FUND_LIST_UPDATE              ( CORFAX::CFX_TRANS,      "00238", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ACCOUNT_CONTRACT_LIST                   ( CORFAX::CFX_TRANS,      "00239", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest INDEX_MASTER_LIST                       ( CORFAX::CFX_TRANS,      "00240", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest INDEX_FUNDS_LIST                        ( CORFAX::CFX_TRANS,      "00241", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest INDEX_MASTER_UPDATE                     ( CORFAX::CFX_TRANS,      "00242", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest RESET_INSTR_LIST                        ( CORFAX::CFX_TRANS,      "00243", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESET_INSTR_UPDATE                      ( CORFAX::CFX_TRANS,      "00244", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ACCT_CATEGORY_LIST                      ( CORFAX::CFX_TRANS,      "00245", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_CATEGORY_UPDATE                    ( CORFAX::CFX_TRANS,      "00246", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest MKT_INDEX_VALUES_LIST                   ( CORFAX::CFX_TRANS,      "00247", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest MKT_INDEX_VALUES_UPDATE                 ( CORFAX::CFX_TRANS,      "00248", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest HISTORICAL_INFO_LIST                    ( CORFAX::CFX_TRANS,      "00249", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_BROKER_LIST                         ( CORFAX::CFX_TRANS,      "00250", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_BROKER_UPDATE                       ( CORFAX::CFX_TRANS,      "00251", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest PROVINCE_LIST_INQUIRY                   ( CORFAX::CFX_TRANS,      "00252", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest FEE_PARAM_CONFIG_LIST                   ( CORFAX::CFX_TRANS,      "00253", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DOCUMENT_TYPE_OVERRIDE_LIST             ( CORFAX::CFX_TRANS,      "00254", DSTCRequest::TYPE_QUERY );   // DEPRECATED!
   extern CLASS_EXPORT const DSTCRequest MISC_INFO_TRANSLATION_TABLE             ( CORFAX::CFX_TRANS,      "00254", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PAYMENT_INSTRUCTIONS_LIST               ( CORFAX::CFX_TRANS,      "00256", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PAYMENT_INSTRUCTIONS_UPDATE             ( CORFAX::CFX_TRANS,      "00257", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest PAY_TO_ENTITY_LIST                      ( CORFAX::CFX_TRANS,      "00258", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PAY_TO_ENTITY_LIST_UPDATE               ( CORFAX::CFX_TRANS,      "00259", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest AMS_REB_DATE_CALC                       ( CORFAX::CFX_TRANS,      "00260", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_LMT_OVERRIDE_LIST_UPDATE            ( CORFAX::CFX_TRANS,      "00261", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest AMS_LMT_OVERRIDE_LIST                   ( CORFAX::CFX_TRANS,      "00262", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest MGMT_CO_OPTIONS_AMS_RESTRICTION         ( CORFAX::CFX_TRANS,      "00263", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest FINANCIAL_INSTITUTION_LIST_UPDATE       ( CORFAX::CFX_TRANS,      "00264", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest DIRECT_TRADING                          ( CORFAX::CFX_TRANS,      "00265", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DIRECT_TRADING_UPDATE                   ( CORFAX::CFX_TRANS,      "00266", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest SETTLE_LOCATION_SYS_INQUIRY             ( CORFAX::CFX_TRANS,      "00267", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SETTLE_LOCATION_SYS_UPDATE              ( CORFAX::CFX_TRANS,      "00268", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FUND_MGMT_SETTLEMENT_INSTR_LIST_INQ     ( CORFAX::CFX_TRANS,      "00269", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_EXTERNAL_TRFR_MASTER               ( CORFAX::CFX_TRANS,      "00270", DSTCRequest::TYPE_MAINT );   
   extern CLASS_EXPORT const DSTCRequest ACCT_EXTERNAL_TRFR_DETAIL               ( CORFAX::CFX_TRANS,      "00271", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest TRANSFER_TYPE_LIST                      ( CORFAX::CFX_TRANS,      "00272", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest FUND_MGMT_SETTLEMENT_INSTR_LIST_UPD     ( CORFAX::CFX_TRANS,      "00274", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FIRE_FIGHTER_LOGON                      ( CORFAX::CFX_TRANS,      "00276", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DAILY_TRANSACTIONS_FEE_LIST             ( CORFAX::CFX_TRANS,      "00284", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DAILY_TRANSACTIONS_FEE_LIST_UPDATE      ( CORFAX::CFX_TRANS,      "00285", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest INVENTORY_SUMMARY_LIST                  ( CORFAX::CFX_TRANS,      "00287", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest HISTORICAL_SHAREHOLDER                  ( CORFAX::CFX_TRANS,      "00288", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest HISTORICAL_ACCT_KYC                     ( CORFAX::CFX_TRANS,      "00289", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SUPPORTED_PRODUCTS                      ( CORFAX::CFX_TRANS,      "00291", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest INVENTORY_DETAILS_LIST                  ( CORFAX::CFX_TRANS,      "00292", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest HYPO_TRADE_ACB                          ( CORFAX::CFX_TRANS,      "00294", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest LSIF_CODES                              ( CORFAX::CFX_TRANS,      "00295", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest LSIF_ROLLOVER_RULES                     ( CORFAX::CFX_TRANS,      "00296", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CHQNAMEINQUIRY                          ( CORFAX::CFX_TRANS,      "00297", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRANSACTION_FEES                        ( CORFAX::CFX_TRANS,      "00298", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SHR_FUND_SPONSOR_AGREEMENT_LIST         ( CORFAX::CFX_TRANS,      "00299", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SHR_FUND_SPONSOR_AGREEMENT_LIST_UPDATE  ( CORFAX::CFX_TRANS,      "00300", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest TAX_EXEMPT_AUTHORIZATION_LIST           ( CORFAX::CFX_TRANS,      "00301", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TAX_EXEMPT_AUTHORIZATION_LIST_UPDATE    ( CORFAX::CFX_TRANS,      "00302", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FEE_MODEL                               ( CORFAX::CFX_TRANS,      "00305", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FEE_MODEL_UPDATE                        ( CORFAX::CFX_TRANS,      "00306", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FUNDSPONSOR_FEE_MODEL                   ( CORFAX::CFX_TRANS,      "00307", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FUNDSPONSOR_FEE_MODEL_UPDATE            ( CORFAX::CFX_TRANS,      "00308", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FEE_SETUP_TRADE_RULES                   ( CORFAX::CFX_TRANS,      "00309", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest REINVEST_PURCHASE_SCHEDULE              ( CORFAX::CFX_TRANS,      "00310", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DISCOUNT_RATE_CALCULATION               ( CORFAX::CFX_TRANS,      "00311", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest UNIT_FACTOR_LIST                        ( CORFAX::CFX_TRANS,      "00313", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRANSACTION_EXTERNAL_LINKS_LIST         ( CORFAX::CFX_TRANS,      "00314", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest BROKER_REMARK_LIST                      ( CORFAX::CFX_TRANS,      "00315", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest BROKER_REMARK_LIST_UPDATE               ( CORFAX::CFX_TRANS,      "00316", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest SETTLEMENT_INSTRUCTIONS_LIST_INQUIRY    ( CORFAX::CFX_TRANS,      "00317", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SETTLEMENT_INSTRUCTIONS_LIST_UPDATE     ( CORFAX::CFX_TRANS,      "00318", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FUND_BROKER_LIST_UPDATE                 ( CORFAX::CFX_TRANS,      "00320", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FUND_BROKER_ELIGIBLE                    ( CORFAX::CFX_TRANS,      "00321", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest NEXT_FUND_BROKER                        ( CORFAX::CFX_TRANS,      "00322", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AGGREGATED_ORDER_LIST                   ( CORFAX::CFX_TRANS,      "00323", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AGGREGATED_ORDER_LIST_UPDATE            ( CORFAX::CFX_TRANS,      "00324", DSTCRequest::TYPE_MAINT );   
   extern CLASS_EXPORT const DSTCRequest FUND_BROKER_DEFAULT                     ( CORFAX::CFX_TRANS,      "00325", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FUND_BROKER_LIST                        ( CORFAX::CFX_TRANS,      "00326", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest SHR_FUND_BROKER                         ( CORFAX::CFX_TRANS,      "00327", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest SHR_FUND_BROKER_UPDATE                  ( CORFAX::CFX_TRANS,      "00328", DSTCRequest::TYPE_MAINT );   
   extern CLASS_EXPORT const DSTCRequest INVENTORY_DETAIL_DEDUCTION_LIST         ( CORFAX::CFX_TRANS,      "00329", DSTCRequest::TYPE_QUERY ); 
   extern CLASS_EXPORT const DSTCRequest TRANS_DECIMALS_LIST_INQUIRY             ( CORFAX::CFX_TRANS,      "00330", DSTCRequest::TYPE_QUERY ); 
   extern CLASS_EXPORT const DSTCRequest WHEREUSE_LIST_UPDATE                    ( CORFAX::CFX_TRANS,      "00331", DSTCRequest::TYPE_MAINT ); 
   extern CLASS_EXPORT const DSTCRequest MSG_ENVELOPE_LIST                       ( CORFAX::CFX_TRANS,      "00332", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest MSG_PROCESS_LIST                        ( CORFAX::CFX_TRANS,      "00333", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest MSG_DETAIL_LIST                         ( CORFAX::CFX_TRANS,      "00334", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest MSG_EVENT_LIST                          ( CORFAX::CFX_TRANS,      "00335", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest MSG_ACTIVITY_LIST                       ( CORFAX::CFX_TRANS,      "00336", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest TRANS_CANCEL                            ( CORFAX::CFX_TRANS,      "00337", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest TRANS_CANCEL_UPDATE                     ( CORFAX::CFX_TRANS,      "00338", DSTCRequest::TYPE_MAINT );   
   extern CLASS_EXPORT const DSTCRequest DILUTION_LIST                           ( CORFAX::CFX_TRANS,      "00339", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest USER_DEF_MAT_LIST                       ( CORFAX::CFX_TRANS,      "00340", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest USER_DEF_MAT_LIST_UPDATE                ( CORFAX::CFX_TRANS,      "00341", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest TRADE_CONTROL_OPTION                    ( CORFAX::CFX_TRANS,      "00344", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CONFIRM_REPRINT_INQUIRY                 ( CORFAX::CFX_TRANS,      "00345", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest CONFIRM_REPRINT_UPDATE                  ( CORFAX::CFX_TRANS,      "00346", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest CUT_OFF_TIMES_LIST                      ( CORFAX::CFX_TRANS,      "00348", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest CUT_OFF_TIMES_LIST_UPDATE               ( CORFAX::CFX_TRANS,      "00349", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest INTERNAL_TRANSLINK_LIST                 ( CORFAX::CFX_TRANS,      "00350", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest GUARANTEEDETAIL_INQUIRY                 ( CORFAX::CFX_TRANS,      "00351", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest DEFAULT_MAILOPTION_LIST                 ( CORFAX::CFX_TRANS,      "00352", DSTCRequest::TYPE_QUERY ); 
   extern CLASS_EXPORT const DSTCRequest SEQ_FUND_VALIDATION_354                 ( CORFAX::CFX_TRANS,      "00354", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest BULK_CANCEL_UPDATE                      ( CORFAX::CFX_TRANS,      "00355", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest DECODE_ACCTID                           ( CORFAX::CFX_TRANS,      "00356", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRANS_HIST_DILUTION_ALLOC_UPDATE        ( CORFAX::CFX_TRANS,      "00357", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest SAVINGS_DIRECTIVE_UPDATE                ( CORFAX::CFX_TRANS,      "00358", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest EUSD_VALIDATE_TRADE                     ( CORFAX::CFX_TRANS,      "00366", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest COT_LEGAL_AGE                           ( CORFAX::CFX_TRANS,      "00367", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AGENCY_NEGATIVE_COMMISSION              ( CORFAX::CFX_TRANS,      "00370", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRADE_PAY_INSTRUCT                      ( CORFAX::CFX_TRANS,      "00374", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RRIF_UNUSED_MAX_AMOUNT                  ( CORFAX::CFX_TRANS,      "00375", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PAYMENT_INSTR_VALIDATION                ( CORFAX::CFX_TRANS,      "00376", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CLONE_ACCOUNT                           ( CORFAX::CFX_TRANS,      "00377", DSTCRequest::TYPE_MAINT );   
   extern CLASS_EXPORT const DSTCRequest DISTRIB_OPTIONS                         ( CORFAX::CFX_TRANS,      "00379", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_ACCT_LEVEL_LIST                     ( CORFAX::CFX_TRANS,      "00380", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_ACCT_LEVEL_UPDATE                   ( CORFAX::CFX_TRANS,      "00381", DSTCRequest::TYPE_MAINT );   
   extern CLASS_EXPORT const DSTCRequest FREQUENCY_LIST                          ( CORFAX::CFX_TRANS,      "00382", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_NEXT_PROC_DATE_INQUIRY              ( CORFAX::CFX_TRANS,      "00383", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest NON_EXCHANGABLE_FUNDS                   ( CORFAX::CFX_TRANS,      "00384", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AFFLUENT_VALIDATION                     ( CORFAX::CFX_TRANS,      "00385", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_CONTROL_INQUIRY                    ( CORFAX::CFX_TRANS,      "00386", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_CONTROL_MAINTENANCE                ( CORFAX::CFX_TRANS,      "00387", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest REGULATORY_STANDARDS                    ( CORFAX::CFX_TRANS,      "00388", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest REG_DOCLIST_INQUIRY                     ( CORFAX::CFX_TRANS,      "00389", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest REG_DOCLIST_MAINTENANCE                 ( CORFAX::CFX_TRANS,      "00390", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest CHEQUE_MAINTENANCE                      ( CORFAX::CFX_TRANS,      "00391", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest RESIDENCY                               ( CORFAX::CFX_TRANS,      "00392", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRADE_AUTHORIZATION                     ( CORFAX::CFX_TRANS,      "00393", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest BATCH_LIST                              ( CORFAX::CFX_TRANS,      "00394", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest INVESTOR_AUTHORIZATION_INQUIRY          ( CORFAX::CFX_TRANS,      "00395", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest INVESTOR_AUTHORIZATION_UPDATE           ( CORFAX::CFX_TRANS,      "00396", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest MULTI_SETTLEMENT_LOCATIONS_INQUIRY      ( CORFAX::CFX_TRANS,      "00397", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest SYSTEM_VERIFICATION_DETAILS_INQUIRY     ( CORFAX::CFX_TRANS,      "00400", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRADED_UNIT_POSTION_INQUIRY             ( CORFAX::CFX_TRANS,      "00401", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESP_BENEF_ALLOCATION_INQUIRY           ( CORFAX::CFX_TRANS,      "00402", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESP_BENEF_ALLOCATION_UPDATE            ( CORFAX::CFX_TRANS,      "00403", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest PSE_EAP_INQUIRY                         ( CORFAX::CFX_TRANS,      "00404", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESP_TRADE_VALIDATION_INQUIRY           ( CORFAX::CFX_TRANS,      "00405", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESP_TRANSFER_INQUIRY                   ( CORFAX::CFX_TRANS,      "00406", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESP_TRANSFER_UPDATE                    ( CORFAX::CFX_TRANS,      "00407", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest RESP_NEQ_INQUIRY                        ( CORFAX::CFX_TRANS,      "00408", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESP_TRANSFER_BENE_INQUIRY              ( CORFAX::CFX_TRANS,      "00409", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESP_TRANS_TYPES_INQUIRY                ( CORFAX::CFX_TRANS,      "00410", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESP_BENEFICIARY_LIST_INQUIRY           ( CORFAX::CFX_TRANS,      "00411", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_GUARNT_GUARD_OPTN_INQUIRY          ( CORFAX::CFX_TRANS,      "00412", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_GUARNT_GUARD_OPTN_UPDATE           ( CORFAX::CFX_TRANS,      "00413", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest SEG_COT_TRX_VALIDATION_INQUIRY          ( CORFAX::CFX_TRANS,      "00414", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESP_INFO_UPDATE_VALIDATION_INQUIRY     ( CORFAX::CFX_TRANS,      "00415", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RESP_TRADE_CONSTANT_INQUIRY             ( CORFAX::CFX_TRANS,      "00416", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ENTITY_SEARCHID_VALIDATION_INQUIRY      ( CORFAX::CFX_TRANS,      "00417", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PROD_PORTFOLIO_INFO_INQUIRY             ( CORFAX::CFX_TRANS,      "00418", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PROD_PORTFOLIO_PLAN_INFO_INQUIRY        ( CORFAX::CFX_TRANS,      "00419", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest GIA_ATTRIBS_INQUIRY                     ( CORFAX::CFX_TRANS,      "00420", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest INVESTMENT_HISTORY_INQUIRY              ( CORFAX::CFX_TRANS,      "00421", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest INTEREST_SEGMENT_INQUIRY                ( CORFAX::CFX_TRANS,      "00422", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest PROGRESSIVE_INT_RATE_INQUIRY            ( CORFAX::CFX_TRANS,      "00423", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest INVESTMENT_HISTORY_TRAN_INQUIRY         ( CORFAX::CFX_TRANS,      "00424", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest INVESTMENT_HISTORY_INT_INQUIRY          ( CORFAX::CFX_TRANS,      "00425", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest GIA_MATURITY_DATE_INQUIRY               ( CORFAX::CFX_TRANS,      "00426", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CASHSWEEP_MATURITY_INSTR_INQUIRY        ( CORFAX::CFX_TRANS,      "00427", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CASHSWEEP_MATURITY_INSTR_DTLS_INQUIRY   ( CORFAX::CFX_TRANS,      "00428", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CASHSWEEP_MATURITY_INSTR_UPDATE         ( CORFAX::CFX_TRANS,      "00429", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest CONTRACT_MATURITY_INSTR_INQUIRY         ( CORFAX::CFX_TRANS,      "00430", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest CONTRACT_MATURITY_INSTR_UPDATE          ( CORFAX::CFX_TRANS,      "00431", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ACCT_COMMIT_INQUIRY                     ( CORFAX::CFX_TRANS,      "00432", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ACCT_COMMIT_DETAIL_ACTIVITY_INQUIRY     ( CORFAX::CFX_TRANS,      "00433", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ACCT_COMMIT_UPDATE                      ( CORFAX::CFX_TRANS,      "00434", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest COMMITMENT_PRODUCT_SETUP_INQUIRY        ( CORFAX::CFX_TRANS,      "00435", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest SEG_TRADE_ENTRY_VALIDATION              ( CORFAX::CFX_TRANS,      "00436", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest AMOUNT_CALCULATION                      ( CORFAX::CFX_TRANS,      "00437", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest GMWB_VALIDATION                         ( CORFAX::CFX_TRANS,      "00438", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest FUND_SERV_BROKER_VALIDATION             ( CORFAX::CFX_TRANS,      "00439", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest RESP_PAC_DATE_CALCULATION               ( CORFAX::CFX_TRANS,      "00440", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest ESTATE_ALLOCATION                       ( CORFAX::CFX_TRANS,      "00441", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RDR_ADVICE                              ( CORFAX::CFX_TRANS,      "00442", DSTCRequest::TYPE_QUERY );  
   extern CLASS_EXPORT const DSTCRequest REG_DOCUMENT_TYPE                       ( CORFAX::CFX_TRANS,      "00443", DSTCRequest::TYPE_QUERY );   
   extern CLASS_EXPORT const DSTCRequest ACCT_OWNERSHIP_ALLOCATION_INQUIRY       ( CORFAX::CFX_TRANS,      "00444", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest EVENT_COMMISSION_INQUIRY                ( CORFAX::CFX_TRANS,      "00445", DSTCRequest::TYPE_QUERY );  
   extern CLASS_EXPORT const DSTCRequest ACCT_ENTITY_VALIDATION			         ( CORFAX::CFX_TRANS,      "00446", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACB_UPDATE                              ( CORFAX::CFX_TRANS,      "00447", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest HOLDING_COMPANY                         ( CORFAX::CFX_TRANS,      "00448", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FEE_MODEL_SETUP                         ( CORFAX::CFX_TRANS,      "00449", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FIN_INST_REG_DETL_INQUIRY               ( CORFAX::CFX_TRANS,      "00450", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_REG_DETAILS_INQUIRY                ( CORFAX::CFX_TRANS,      "00451", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_REG_DETAILS_UPDATE                 ( CORFAX::CFX_TRANS,      "00452", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest DEFAULT_REG_STANDARD_INQUIRY            ( CORFAX::CFX_TRANS,      "00453", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DEFAULT_SYSTEM_CONFIG                   ( CORFAX::CFX_TRANS,      "00454", DSTCRequest::TYPE_QUERY ); 
   extern CLASS_EXPORT const DSTCRequest DEFAULT_SYSTEM_CONFIG_DETAIL            ( CORFAX::CFX_TRANS,      "00455", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ENT_REG_DETAILS_INQUIRY                 ( CORFAX::CFX_TRANS,      "00456", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ENT_REG_DETAILS_UPDATE                  ( CORFAX::CFX_TRANS,      "00457", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ENT_REG_JURIS_DETAILS_INQUIRY           ( CORFAX::CFX_TRANS,      "00458", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ENT_REG_JURIS_DETAILS_UPDATE            ( CORFAX::CFX_TRANS,      "00459", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FATCA_MASTER_INQUIRY                    ( CORFAX::CFX_TRANS,      "00460", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest NETWORK_CONFIG_DETAIL                   ( CORFAX::CFX_TRANS,      "00461", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRADE_LEVEL_OVERRIDE_RULES              ( CORFAX::CFX_TRANS,      "00462", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRADE_VERIFICATION_UPDATE               ( CORFAX::CFX_TRANS,      "00463", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest TRADEOVERIDERULEWARNINGS_LIST           ( CORFAX::CFX_TRANS,      "00464", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DEMOGRAPHICS_CHILD_LIST_INQUIRY         ( CORFAX::CFX_TRANS,      "00465", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest DEMOGRAPHICS_CHILD_LIST_UPDATE          ( CORFAX::CFX_TRANS,      "00466", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest RESP_REG_MSTR_INQUIRY                   ( CORFAX::CFX_TRANS,      "00467", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_GRP_CONFIG_INQUIRY                 ( CORFAX::CFX_TRANS,      "00468", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest REGULATORY_VALIDATIONS                  ( CORFAX::CFX_TRANS,      "00469", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ALERT_MESSAGES_INQUIRY                  ( CORFAX::CFX_TRANS,      "00470", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest FUND_RULES_INQUIRY                      ( CORFAX::CFX_TRANS,      "00471", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest REG_PLAN_TRANSF_INQUIRY                 ( CORFAX::CFX_TRANS,      "00472", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest REG_PLAN_TRANSF_ALLOC_INQUIRY           ( CORFAX::CFX_TRANS,      "00473", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest REG_PLAN_TRANSF_UPDATE                  ( CORFAX::CFX_TRANS,      "00474", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest PENDING_TRADE_ERROR_UPDATE              ( CORFAX::CFX_TRANS,      "00475", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest ACCT_FUND_LEVEL_SETTLEDAYS_INQUIRY      ( CORFAX::CFX_TRANS,      "00476", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ENTITY_RISK_INQUIRY                     ( CORFAX::CFX_TRANS,      "00477", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ENTITY_RISK_UPDATE                      ( CORFAX::CFX_TRANS,      "00478", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest UNUSUAL_TRADING_VALIDATION              ( CORFAX::CFX_TRANS,      "00479", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_ROUNDING_RULE_INQUIRY              ( CORFAX::CFX_TRANS,      "00480", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ACCT_ROUNDING_RULE_UPDATE               ( CORFAX::CFX_TRANS,      "00481", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest RESP_REG_RULE_INQUIRY		             ( CORFAX::CFX_TRANS,      "00482", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_DELTA_ALLOC_LIST                    ( CORFAX::CFX_TRANS,      "00483", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest AMS_DELTA_ALLOC_LIST_UPDATE			 ( CORFAX::CFX_TRANS,      "00484", DSTCRequest::TYPE_MAINT );
   extern CLASS_EXPORT const DSTCRequest FUND_SUSPENSION_VALIDATION			     ( CORFAX::CFX_TRANS,      "00486", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest TRADE_INTRA_DAY_PRICING			     ( CORFAX::CFX_TRANS,      "00487", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest RDSP_TRANSFER_INQUIRY				     ( CORFAX::CFX_TRANS,      "00488", DSTCRequest::TYPE_QUERY );
   extern CLASS_EXPORT const DSTCRequest ENTITYSEARCHID_VALIDATION       	     ( CORFAX::CFX_TRANS,      "00490", DSTCRequest::TYPE_QUERY );

/* N.B. -- use:
 * DSTCRequest::TYPE_QUERY for non-updating requests
 * DSTCRequest::TYPE_MAINT for updating requests
 * DSTCRequest::TYPE_SYSLOAD for non-updating requests that are to persist localy
 */
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/dstcdbrkr_Constants.cpp-arc  $
// 
//    Rev 1.197   Aug 15 2012 14:02:00   wp040027
// IN#3008167-P187485-CPF- Account Entity (RA) validation
// 
//    Rev 1.196   Aug 15 2012 09:57:26   dchatcha
// PETP0186479 FN11 - Event Commission on Transfer In, new view 445.
// 
//    Rev 1.195   Jul 25 2012 13:46:04   wp040027
// P0198518 - RDR Functionality
// 
//    Rev 1.194   Jul 24 2012 19:04:24   dchatcha
// P0179630 FN01 FATCA Project - Acct Ownership Allocation
// 
//    Rev 1.193   Jul 23 2012 12:59:24   wutipong
// PETP0179630_FN01 FATCA Account Entity Document Tracking
// 
//    Rev 1.192   Jul 13 2012 16:56:22   if991250
// Added ESTATE_ALLOCATION
// 
//    Rev 1.191   Jun 26 2012 17:26:48   if991250
// DSC Scale at Contract level
// 
//    Rev 1.190   May 11 2012 13:14:50   jankovii
// P0186481 FN07 - GWA LWA Payment Options for SWP RRIF
// 
//    Rev 1.189   May 03 2012 09:41:54   dchatcha
// P0186486 FN10 -Gap 14G - Block Service Unit Transfers
// 
//    Rev 1.188   Mar 05 2012 11:15:04   dchatcha
// P0186484 FN05 - SEG Trade Processing.
// 
//    Rev 1.187   Feb 21 2012 15:46:28   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.186   Feb 14 2012 13:36:48   if991250
// added Account comitment views
// 
//    Rev 1.185   Dec 12 2011 12:00:30   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.184   Dec 05 2011 15:02:00   jankovii
// P0186477 FN03 - Maturity Cash Sweep Instructions
// 
//    Rev 1.183   Nov 30 2011 00:24:12   dchatcha
// P0186477/FN03 - GIA - Purchase
// 
//    Rev 1.182   Nov 27 2011 21:48:14   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.181   Nov 23 2011 05:25:10   panatcha
// P0186477_FN03_10D - GIA Money In
// 
//    Rev 1.180   Nov 21 2011 21:07:30   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.179   Nov 17 2011 15:58:14   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.178   Aug 25 2011 17:02:28   dchatcha
// P0186477 FN01 - GIA Enhancements.
// 
//    Rev 1.177   Nov 26 2010 06:20:08   wutipong
// IN#2143362
// 
//    Rev 1.176   Oct 29 2010 03:42:30   kitticha
// PET0165541 FN03 - QESI Phase3
// 
//    Rev 1.175   Sep 17 2010 06:45:48   kitticha
// PETP0173756 FN02 Don't Bust the Rules.
// 
//    Rev 1.174   Aug 06 2010 13:52:22   jankovii
// PET165541 FN03 SOC14 & SOC6
// 
//    Rev 1.173   Apr 28 2010 10:42:56   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading,  - added view 409 -
// 
//    Rev 1.172   Apr 21 2010 23:07:18   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading, RESP Trade Validation
// 
//    Rev 1.171   Apr 21 2010 17:20:56   popescu
// RESP-QESI Resp transfer screen
// 
//    Rev 1.170   Apr 15 2010 10:28:04   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.169   Mar 22 2010 15:05:40   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.168   Dec 18 2009 10:38:30   jankovii
// PET0166095 FN01 Validations on Money Out Transactions
// 
//    Rev 1.167   Nov 16 2009 06:52:00   dchatcha
// P0166583 - Static Data Change Phase 2 - FN02-03-04
// 
//    Rev 1.166   Sep 11 2009 16:39:32   yingz
// change HYPO_REDEMPTION_SUMMARY def
// 
//    Rev 1.165   Aug 11 2009 11:58:58   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields.
// 
//    Rev 1.164   Jul 09 2009 15:58:58   dchatcha
// PET156681 FN14 H36 Investor Authorization.
// 
//    Rev 1.163   29 Jun 2009 16:10:34   popescu
// PET 156681 - FN 14 - Investor Authorization
// 
//    Rev 1.162   May 12 2009 11:55:08   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.161   Mar 24 2009 10:23:56   purdyech
// Changes for ZTS.  Release 9 for Phase II of POC
// 
//    Rev 1.160   Feb 06 2009 14:52:44   purdyech
// Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
// 
//    Rev 1.159   23 Sep 2008 16:19:46   kovacsro
// PET 142007 FN01 TFSA
// 
//    Rev 1.158   Sep 08 2008 16:03:00   jankovii
// PET 5517 FN71 - Stale Cheque.
// 
//    Rev 1.157   Jul 25 2008 14:20:20   jankovii
// PET 59888 - AML Enhancement.
// 
//    Rev 1.156   Jul 16 2008 10:17:46   jankovii
// PET 59888 - AML Enhancemement.
// 
//    Rev 1.155   Mar 11 2008 19:30:26   daechach
// PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
// 
//    Rev 1.154   26 Nov 2007 16:30:52   kovacsro
// IN#1039915 - added view385
// 
//    Rev 1.153   Sep 11 2007 08:49:36   smithdav
// IN 979244. exchange limitations.
// 
//    Rev 1.152   Jun 21 2007 10:39:50   porteanm
// PET 2360 FN02 - AMS - added support for AMS Next Proc Date.
// 
//    Rev 1.151   Jun 20 2007 12:17:20   porteanm
// PET 2360 FN02 - AMS - added support for AMS Acct Level and Frequency.
// 
//    Rev 1.150   Jun 14 2007 11:45:58   porteanm
// PET 2360 FN48 - GAPS 48 - Cleanup.
// 
//    Rev 1.149   Jun 14 2007 11:44:36   porteanm
// PET 2360 FN48 - GAPS 48 - for BKK.
// 
//    Rev 1.148   Mar 12 2007 14:09:10   purdyech
// Corrected TYPE_MAINT and TYPE_QUERY for all DSTCRequest objects.
// Put DSTCRequest definitions back to numerical order
// Prettied up the whitespace
// 
//    Rev 1.147   Nov 08 2006 17:29:56   popescu
// PET 2281/FN 01- copy account for TA 
// 
//    Rev 1.146   Oct 18 2006 15:44:10   ZHANGCEL
// STP - PET2192 FN10/11 -- Payment Instruction validation view376
// 
//    Rev 1.145   Sep 06 2006 11:06:20   porteanm
// PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt.
// 
//    Rev 1.144   Sep 05 2006 13:58:54   popescu
// PET 2217/17 - STP project
// 
//    Rev 1.143   May 31 2006 17:57:04   porteanm
// PET2132 FN03 - Edit check for Negative Commission.
// 
//    Rev 1.142   May 25 2006 17:41:56   ZHANGCEL
// PET 2102 FN01 -- Add 4 new error conditons for view367 in ifastdbrkr
// 
//    Rev 1.141   Mar 22 2006 16:24:26   jankovii
// EUSD Backdated trade validation.
// 
//    Rev 1.140   Dec 13 2005 19:16:28   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.139   Nov 29 2005 15:27:22   AGUILAAM
// PET1228_FN02: EUSD Phase 2
// 
//    Rev 1.138   Nov 05 2005 15:36:22   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.137   Oct 24 2005 17:29:10   ZHANGCEL
// PET1332 FN09A -- Add view 356
// 
//    Rev 1.136   Sep 23 2005 18:27:44   ZHANGCEL
// PET1244 FN01 -- Seg Func Evolution enhancement
// 
//    Rev 1.135   Sep 22 2005 11:15:30   yingbaol
// PEt1277,FN01,Fund Investment disclosure
// 
//    Rev 1.134   Aug 17 2005 16:38:44   porteanm
// Incident 351033 - New view 351.
// 
//    Rev 1.133   Jun 27 2005 15:30:16   Yingbaol
// PET1235,FN01: add view 350
// 
//    Rev 1.132   Jun 16 2005 13:33:40   hernando
// PET1250 FN01 - Added 348 and 349.  Acct Lvl Cut Off Time Enhancement.
// 
//    Rev 1.131   May 24 2005 12:40:46   porteanm
// PET OPC Confirm Reprint - Renamed OPC files. Changed class hierarchy.
// 
//    Rev 1.130   May 12 2005 14:47:14   yingbaol
// PET1203,FN01: add view 344, trade general control
// 
//    Rev 1.129   May 05 2005 16:02:18   porteanm
// PET OPC Confirm Reprint - For Release 63 added OPC_CONFIRM_REPRINT_INQUIRY and OPC_CONFIRM_REPRINT_UPDATE.
// 
//    Rev 1.128   Mar 06 2005 17:00:16   hernando
// PET1024 FN02 - Added USER_DEF_MAT_LIST (340) and USER_DEF_MAT_LIST_UPDATE (341).
// 
//    Rev 1.127   Mar 03 2005 17:57:12   Fengyong
// PET1190 FN05 - Add transaction cancellation
// 
//    Rev 1.126   Mar 03 2005 14:34:12   aguilaam
// PET1171_FN01: display view 330 details on Transaction Detail screen (history) EUSDSavings - others
// 
//    Rev 1.125   Feb 28 2005 11:31:20   porteanm
// PET 1171 FN01 - EUSD Province List support.
// 
//    Rev 1.124   Feb 24 2005 11:40:02   yingbaol
// PET1171,FN01, EU Saving add whereused list update
// 
//    Rev 1.123   Feb 24 2005 11:22:38   ZHANGCEL
// PET1117 FN66-68 - Added MSG_ENVELOPE_LIST
// 
//    Rev 1.122   Feb 15 2005 16:59:56   hernando
// PET1117 FN66-68 - Added MSG_PROCESS_LIST, MSG_ACTIVITY_LIST, MSG_EVENT_LIST, and MSG_DETAIL_LIST.
// 
//    Rev 1.121   Feb 07 2005 11:25:56   aguilaam
// PET1198_FN01: LSIF Reason Code enhancement, new view 329
// 
//    Rev 1.120   Nov 18 2004 14:03:36   popescu
// PET 1117/06, two new views
// 
//    Rev 1.119   Nov 11 2004 16:11:00   vadeanum
// PET1117 FN08 - Shareholder Fund Broker support.
// 
//    Rev 1.118   Nov 05 2004 15:46:42   popescu
// PET 1117/06, added constants for  views 298
// 
//    Rev 1.117   Nov 05 2004 10:51:30   FENGYONG
// view team change the number of view from 319 to 326
// 
//    Rev 1.116   Nov 04 2004 14:58:36   FENGYONG
// PET1117 FN54 - Fund Broker Static Temp check in for 59 build
// 
//    Rev 1.115   Nov 04 2004 09:34:38   popescu
// PET 1117/06. added constant for view 311
// 
//    Rev 1.114   Nov 02 2004 18:20:02   SMITHDAV
// Allow DSTRequest instances to be typed as either "maint" or "query" request. This crude form of specialization was chosen so that all of the CBO files would not have to be changed.
// 
//    Rev 1.113   Nov 02 2004 14:02:36   popescu
// PET 1117/06, added constants for two new views 309/310
// 
//    Rev 1.112   Nov 01 2004 17:06:16   ZHANGCEL
// PET 1117 FN8 -- Aggregation order related changes
// 
//    Rev 1.111   Oct 19 2004 14:35:48   FENGYONG
// PET1117 FN54 - Fund Broker static
// 
//    Rev 1.110   Oct 13 2004 13:54:48   VADEANUM
// PET 1117 FN21 - Settlement Instruction support.
// 
//    Rev 1.109   Oct 04 2004 15:31:08   YINGBAOL
// PET1145 FN01 Dynamic API
// 
//    Rev 1.108   Aug 30 2004 15:27:24   HERNANDO
// PET1117 FN22 - Added UNIT_FACTOR_LIST (313)
// 
//    Rev 1.107   Aug 30 2004 14:23:52   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.106   Aug 10 2004 11:33:06   FENGYONG
// PET1117 FN5 - Client Condition Fee
// 
//    Rev 1.105   Aug 06 2004 17:35:32   ZHANGCEL
// PET 1082 FNrlc - Tax Exempt Authorization support
// 
//    Rev 1.104   Jul 26 2004 10:06:50   VADEANUM
// PET1117 FN01 - Shareholder Static Data support.
// 
//    Rev 1.103   Jul 05 2004 15:50:56   AGUILAAM
// PET10030921 - get name1 and name2 from new view 297 for settlement cheque
// 
//    Rev 1.102   May 19 2004 17:40:52   YINGBAOL
// Add view 294
// 
//    Rev 1.101   May 12 2004 09:10:02   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.100   May 09 2004 20:11:28   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.99   May 06 2004 15:03:52   popescu
// PET 985, FN 01, added view 291 supported products
// 
//    Rev 1.98   May 06 2004 14:47:34   HERNANDO
// PET1046 FN01 - Added INVENTORY_DETAILS_LIST (292)
// 
//    Rev 1.97   Mar 01 2004 10:25:30   HERNANDO
// PET965 FN11 - Added View 289; Historical Account KYC.
// 
//    Rev 1.96   Feb 18 2004 16:08:54   ZHANGCEL
// PET1001_FN01 - Added view287 -- Inventory Summary
// 
//    Rev 1.95   Feb 06 2004 13:49:42   HERNANDO
// PET965 FN11 - Added View 288 - Historical Shareholder
// 
//    Rev 1.94   Feb 06 2004 09:44:34   VADEANUM
// PET859 FN23 - ADL - added DAILY_TRANSACTIONS_FEE...
// 
//    Rev 1.93   Dec 11 2003 11:46:00   linmay
// added FIRE_FIGHTER_LOGON
// 
//    Rev 1.92   Nov 12 2003 13:45:40   HERNANDO
// PET892 FN1 - Added SETTLE_LOCATION_ACCT_UPDATE, SETTLE_LOCATION_ACCT_INQUIRY.
// 
//    Rev 1.91   Nov 07 2003 16:08:40   HERNANDO
// Added SETTLE_LOCATION_SYS_INQUIRY and SETTLE_LOCATION_SYS_UPDATE.
// 
//    Rev 1.90   Oct 20 2003 14:10:18   popescu
// change the name of the financial institution view update constant
// 
//    Rev 1.89   Oct 20 2003 12:09:40   popescu
// added constants for FinancialInsitution updates (view 264) and DirectTrading, views (265 and 266)
// 
//    Rev 1.88   Oct 20 2003 09:14:30   HSUCHIN
// added new constants for account external transfers
// 
//    Rev 1.87   Oct 07 2003 17:06:06   HERNANDO
// Added MISC_INFO_TRANSLATION_TABLE.
// 
//    Rev 1.86   Jul 31 2003 12:57:00   linmay
// modified aor ams lmt override
// 
//    Rev 1.85   Jul 30 2003 13:59:10   linmay
// added contants for amsrebdatecalc
// 
//    Rev 1.84   Jul 18 2003 11:36:48   linmay
// modified for CIBC AMS
// 
//    Rev 1.83   Jun 30 2003 16:59:52   popescu
// added payment instructions trxn
// 
//    Rev 1.82   Jun 25 2003 17:52:40   popescu
// added view 258 & 259 inquiry and updates - pay to entity feature
// 
//    Rev 1.81   May 02 2003 18:18:14   ZHANGCEL
// PTS 10016099: added REDEMPTION_VALIDATION
// 
//    Rev 1.80   Apr 17 2003 11:32:18   YINGBAOL
// view 254
// 
//    Rev 1.79   Apr 02 2003 13:20:02   FENGYONG
// mailing update trxn number is 216
// 
//    Rev 1.78   Apr 02 2003 11:33:48   FENGYONG
// add Acct mailing override update dstc request
// 
//    Rev 1.77   Mar 07 2003 13:40:26   linmay
// added   FEE_PARAM_CONFIG_LIST
// 
//    Rev 1.76   Feb 27 2003 11:09:16   FENGYONG
// Add broker level AMS inquriy and update 250, 251
// 
//    Rev 1.75   Jan 26 2003 17:19:54   popescu
// added a new DSTC Requestor for view 249
// 
//    Rev 1.74   Jan 25 2003 19:37:16   HERNANDO
// Added MKT_INDEX_VALUES_LIST and MKT_INDEX_VALUES_UPDATE.  (View 247, View 248).
// 
//    Rev 1.73   Jan 21 2003 12:51:26   KOVACSRO
// Added view 245,246 and 235.
// 
//    Rev 1.72   Jan 20 2003 16:37:46   HERNANDO
// Added Index Master Update.
// 
//    Rev 1.71   Jan 20 2003 15:43:56   popescu
// Checked in for unit testing the ProtectedFundSetup feature
// 
//    Rev 1.70   Jan 17 2003 17:43:54   HERNANDO
// Added INDEX_MASTER_LIST and INDEX_FUNDS_LIST.
// 
//    Rev 1.69   Jan 17 2003 13:35:10   HSUCHIN
// added RESET_INSTR_LIST and RESET_INSTR_UPDATE
// 
//    Rev 1.68   Jan 17 2003 13:32:58   HSUCHIN
// added ACCOUNT_CONTRACT_LIST
// 
//    Rev 1.67   Jan 15 2003 16:25:22   popescu
// Added ids for view 0237 protected fund setup
// 
//    Rev 1.66   Jan 14 2003 17:45:08   sanchez
// added 
// extern CLASS_EXPORT const DSTCRequest SHR_FAMILY_UPDATE           ( CORFAX::CFX_TRANS,      "00234" );
// 
//    Rev 1.65   Jan 13 2003 18:47:58   sanchez
// changes for shareholder family
// 
//    Rev 1.64   Jan 12 2003 18:08:34   WINNIE
// Add view 236
// 
//    Rev 1.63   Jan 11 2003 13:12:36   KOVACSRO
// Added FUND_TYPE_LIST (view 126)
// 
//    Rev 1.62   Jan 08 2003 19:16:26   YINGBAOL
// add FEE_PARAM_SYSTEM_LIST,FEE_PARAM_SCALE_LIST and FEE_PARAM_SYSTEM_UPDATE
// 
//    Rev 1.61   Jan 02 2003 17:25:42   linmay
// add    FUND_COMM_GROUP_LIST       
// 
//    Rev 1.60   Nov 27 2002 11:45:06   HSUCHIN
// added timezone for reports
// 
//    Rev 1.59   Nov 25 2002 16:27:16   HSUCHIN
// added view 220,222,224,225
// 
//    Rev 1.58   Nov 19 2002 10:17:10   HSUCHIN
// added view 221/223
// 
//    Rev 1.57   Nov 18 2002 15:35:46   HSUCHIN
// added view 223
// 
//    Rev 1.56   Nov 18 2002 15:29:12   YINGBAOL
// add AMS_MASTER_LIST etc.
// 
//    Rev 1.55   Nov 05 2002 11:29:52   KOVACSRO
// Added HYPO_REDEMPTION_DETAILS, since the view team changed the original design.
// 
//    Rev 1.54   Oct 29 2002 10:34:22   KOVACSRO
// Added HYPO_REDEMPTION
// 
//    Rev 1.53   Oct 09 2002 23:55:22   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.52   Sep 17 2002 10:10:08   HSUCHIN
// added view 216
// 
//    Rev 1.51   Sep 12 2002 11:37:58   YINGBAOL
// change ID for DocumentType
// 
//    Rev 1.50   Sep 10 2002 14:01:58   YINGBAOL
// add EntityAddressMailing
// 
//    Rev 1.49   Jul 25 2002 14:48:18   ZHANGCEL
// PTS 10008129: Added MEXT_PROC_DATE
// 
//    Rev 1.48   Jul 05 2002 11:50:04   KOVACSRO
// Added BankAcctUsage
// 
//    Rev 1.47   Jun 12 2002 20:59:54   VASILEAD
// Added SETTLEMENT_MAIN
// 
//    Rev 1.46   08 Jun 2002 18:05:40   HERNANDO
// Added TAXJURISDICTIONLIMIT_LIST (211).
// 
//    Rev 1.45   Jun 05 2002 14:43:28   KOVACSRO
// Added International Wire check.
// 
//    Rev 1.44   Jun 03 2002 10:02:42   YINGZ
// add TRANSTYPE_FILEPROC_LIST
// 
//    Rev 1.43   May 30 2002 14:31:20   YINGBAOL
// Add Settlement Total
// 
//    Rev 1.42   May 30 2002 10:14:30   HSUCHIN
// added Pension Info view 202/203
// 
//    Rev 1.41   May 30 2002 10:09:42   YINGBAOL
// Add Setlement List and Setlement List Update
// 
//    Rev 1.40   08 May 2002 17:59:14   HERNANDO
// Added ACCOUNTREVIEW_LIST and ACCOUNTREVIEW_LIST_UPDATE.
// 
//    Rev 1.39   21 Feb 2002 15:48:42   HSUCHIN
// added MFAccrual
// 
//    Rev 1.38   Feb 05 2002 09:33:36   YINGBAOL
// add FundFee, view 197
// 
//    Rev 1.37   Jan 31 2002 14:52:24   YINGBAOL
// add view 194,195,196
// 
//    Rev 1.36   Jan 25 2002 11:51:20   FENGYONG
// Add Account Search
//  
//    Rev 1.35   Jan 04 2002 10:18:08   FENGYONG
// Add view 191 slsrepupdate
// 
//    Rev 1.34   Dec 14 2001 10:32:08   ZHANGCEL
// Added RADE_DATE_LAG_VALIDATION and SEQ_FUND_VALIDATION_NUSU 
// 
//    Rev 1.33   Nov 28 2001 09:51:56   JANKAREN
// added AMSCode
// 
//    Rev 1.32   20 Sep 2001 13:53:54   KOVACSRO
// Added Esop Historical.
// 
//    Rev 1.31   Aug 24 2001 11:53:04   JANKAREN
// fixed request number
// 
//    Rev 1.30   Aug 23 2001 12:31:18   JANKAREN
// Added As Pension Plan
// 
//    Rev 1.29   22 Aug 2001 12:45:58   HSUCHIN
// added Account SplitComm
// 
//    Rev 1.28   01 Aug 2001 15:21:36   HSUCHIN
// added RSP view definitions
// 
//    Rev 1.27   29 Jul 2001 15:20:04   KOVACSRO
// Added ESoP stuff.
// 
//    Rev 1.26   Jul 27 2001 15:32:02   OLTEANCR
// added GUARANTEE_SUMMARY
// 
//    Rev 1.25   27 Jul 2001 14:00:40   KOVACSRO
// Added TradeMinAmtCheck.
// 
//    Rev 1.24   Jul 16 2001 19:05:46   OLTEANCR
//  addedt MULTI_CONTRACT_UPDATE       
// 
//    Rev 1.23   10 Jul 2001 15:34:06   KOVACSRO
// Added Duplicate Trade Check (view 156).
// 
//    Rev 1.22   06 Jun 2001 13:32:36   HSUCHIN
// new fields/conditions for Indexing/Savings Plan
// 
//    Rev 1.21   25 May 2001 15:03:46   YINGZ
// add SAVINGPLAN_MASTER_LIST
// 
//    Rev 1.20   24 May 2001 15:33:08   HSUCHIN
// clean up and added SYS_INDEX (view 119)
// 
//    Rev 1.19   May 11 2001 13:07:16   HERNANDO
// Added HIST_SYS_INDEX_LIST (Historical Systematic Index List)
// 
//    Rev 1.18   03 May 2001 14:03:30   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.17   Mar 21 2001 15:13:10   FENGYONG
// Add FEEINFOINQUIRY
// 
//    Rev 1.16   Mar 18 2001 18:15:28   VASILEAD
// Added ACCOUNT_INQUIRY
// 
//    Rev 1.15   Mar 12 2001 12:57:20   VASILEAD
// Added TransactionSummary view 117
// 
//    Rev 1.14   Mar 09 2001 11:38:24   OLTEANCR
// added constant MGMT_CO_OPTIONS_NEXT
// 
//    Rev 1.13   Mar 06 2001 14:46:36   YINGZ
// add def_split_comm
// 
//    Rev 1.12   Jan 30 2001 10:43:16   OLTEANCR
// added AVAILABILTY
// 
//    Rev 1.11   Jan 19 2001 13:33:58   YINGBAOL
// add RECIPIENT_LIST
// 
//    Rev 1.10   Dec 06 2000 14:17:52   WINNIE
// correct spelling for ACTIVE_BATCH
// 
//    Rev 1.9   Nov 18 2000 18:20:16   VASILEAD
// Added FUNDSPONSOR
// 
//    Rev 1.8   Nov 17 2000 12:01:16   OLTEANCR
// added new const
// 
//    Rev 1.7   Nov 15 2000 17:16:08   WINNIE
// duplicate definition for ENTITY, view 55 belongs to transaction banking
// 
//    Rev 1.6   Nov 02 2000 14:49:48   YINGBAOL
// put brokerback
// 
//    Rev 1.5   Nov 01 2000 12:56:58   OLTEANCR
// added constants
// 
//    Rev 1.4   Nov 01 2000 11:56:56   YINGBAOL
// add sysLoad support function
// 
//    Rev 1.3   Oct 31 2000 15:00:36   YINGBAOL
// more view added and add version control
 * 


  */

