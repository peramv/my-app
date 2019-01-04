#include "stdafx.h"
#include <bfproc\commandtraits.hpp>


CLASS_EXPORT const I_CHAR *CMD_GUI_LIST_SELECTION = I_( "GUIDLG_LIST_SELECTION" );
static CommandTraits cmdTrait_CMD_GUI_LIST_SELECTION( CMD_GUI_LIST_SELECTION,
                                                      GUI_TYPE | DIALOG_TYPE,
                                                      1,
                                                      1,
                                                      MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_BUSINFO = I_( "GUIDLG_BUSINFO" );
static CommandTraits cmdTrait_CMD_GUI_BUSINFO( CMD_GUI_BUSINFO,
                                               GUI_TYPE | DIALOG_TYPE,
                                               1,
                                               1,
                                               MODE_MODELESSONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_ENTITY_SEARCH = I_( "GUIDLG_ENTITY_SEARCH" );
static CommandTraits cmdTrait_CMD_GUI_ENTITY_SEARCH( CMD_GUI_ENTITY_SEARCH,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_IDCALLER = I_( "GUIDLG_IDCALLER" );
static CommandTraits cmdTrait_CMD_GUI_IDCALLER( CMD_GUI_IDCALLER,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MANAGEMENT_COMPANY = I_( "GUIDLG_MANAGEMENT_COMPANY" );
static CommandTraits cmdTrait_CMD_GUI_MANAGEMENT_COMPANY( CMD_GUI_MANAGEMENT_COMPANY,
                                                          GUI_TYPE | DIALOG_TYPE,
                                                          1,
                                                          1,
                                                          MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_SYSTEMATIC = I_( "GUIDLG_SYSTEMATIC" );
static CommandTraits cmdTrait_CMD_GUI_SYSTEMATIC (CMD_GUI_SYSTEMATIC,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_LOGON = I_( "GUIDLG_LOGON" );
static CommandTraits cmdTrait_CMD_GUI_LOGON( CMD_GUI_LOGON,
                                             GUI_TYPE | DIALOG_TYPE,
                                             1,
                                             1,
                                             MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_WHEREUSED = I_( "GUIDLG_WHEREUSED" );
static CommandTraits cmdTrait_CMD_GUI_WHEREUSED( CMD_GUI_WHEREUSED,
                                                 GUI_TYPE | DIALOG_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ENTITY_MAINTENANCE = I_( "GUIDLG_ENTITY_MAINTENANCE" );
static CommandTraits cmdTrait_CMD_GUI_ENTITY_MAINTENANCE( CMD_GUI_ENTITY_MAINTENANCE,
                                                          GUI_TYPE | DIALOG_TYPE,
                                                          1,
                                                          1,
                                                          MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCOUNT_DETAILS = I_( "GUIDLG_ACCOUNT_DETAILS" );
static CommandTraits cmdTrait_CMD_GUI_ACCOUNT_DETAILS( CMD_GUI_ACCOUNT_DETAILS,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_SYSTEMATIC_FEE = I_( "GUIDLG_SYSTEMATIC_FEE" );
static CommandTraits cmdTrait_CMD_GUI_SYSTEMATIC_FEE( CMD_GUI_SYSTEMATIC_FEE,
                                                      GUI_TYPE | DIALOG_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_CERTIFICATE = I_( "GUIDLG_CERTIFICATE" );
static CommandTraits cmdTrait_CMD_GUI_CERTIFICATE( CMD_GUI_CERTIFICATE,
                                                   GUI_TYPE | DIALOG_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRANS_HISTORY = I_( "GUIDLG_TRANS_HISTORY" );
static CommandTraits cmdTrait_CMD_GUI_TRANS_HISTORY( CMD_GUI_TRANS_HISTORY,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_DEMOGRAPHICS = I_( "GUIDLG_DEMOGRAPHICS" );
static CommandTraits cmdTrait_CMD_GUI_DEMOGRAPHICS( CMD_GUI_DEMOGRAPHICS,
                                                    GUI_TYPE | DIALOG_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_REMARKS = I_( "GUIDLG_REMARKS" );
static CommandTraits cmdTrait_CMD_GUI_REMARKS( CMD_GUI_REMARKS,
                                               GUI_TYPE | DIALOG_TYPE,
                                               1,
                                               1,
                                               MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCRUALS = I_( "GUIDLG_ACCRUALS" );
static CommandTraits cmdTrait_CMD_GUI_ACCRUALS( CMD_GUI_ACCRUALS,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_BANK_INSTRUCTIONS = I_( "GUIDLG_BANK_INSTRUCTIONS" );
static CommandTraits cmdTrait_CMD_GUI_BANK_INSTRUCTIONS( CMD_GUI_BANK_INSTRUCTIONS,
                                                         GUI_TYPE | DIALOG_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_SYS_INDEX = I_( "GUIDLG_SYS_INDEX" );
static CommandTraits cmdTrait_CMD_GUI_SYS_INDEX( CMD_GUI_SYS_INDEX,
                                                 GUI_TYPE | DIALOG_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_HISTORICAL_ACCOUNT = I_( "GUIDLG_HISTORICAL_ACCOUNT" );
static CommandTraits cmdTrait_CMD_GUI_HISTORICAL_ACCOUNT( CMD_GUI_HISTORICAL_ACCOUNT,
                                                          GUI_TYPE | DIALOG_TYPE,
                                                          1,
                                                          1,
                                                          MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_HISTORICAL_SHAREHOLDER = I_( "GUIDLG_HISTORICAL_SHAREHOLDER" );
static CommandTraits cmdTrait_CMD_GUI_HISTORICAL_SHAREHOLDER( CMD_GUI_HISTORICAL_SHAREHOLDER,
                                                          GUI_TYPE | DIALOG_TYPE,
                                                          1,
                                                          1,
                                                          MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_HISTORICAL_SYS_INDEX = I_( "GUIDLG_HISTORICAL_SYS_INDEX" );
static CommandTraits cmdTrait_CMD_GUI_HISTORICAL_SYS_INDEX( CMD_GUI_HISTORICAL_SYS_INDEX,
                                                            GUI_TYPE | DIALOG_TYPE,
                                                            1,
                                                            1,
                                                            MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_HISTORICAL_MARKET_VALUE = I_( "GUIDLG_HISTORICAL_MARKET_VALUE" );
static CommandTraits cmdTrait_CMD_GUI_HISTORICAL_MARKET_VALUE( CMD_GUI_HISTORICAL_MARKET_VALUE,
                                                               GUI_TYPE | DIALOG_TYPE,
                                                               1,
                                                               1,
                                                               MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRANSACTION_BANK_INSTRUCTION = I_( "GUIDLG_TRANSACTION_BANK_INSTRUCTION" );
static CommandTraits cmdTrait_CMD_GUI_TRANSACTION_BANK_INSTRUCTION( CMD_GUI_TRANSACTION_BANK_INSTRUCTION,
                                                                    GUI_TYPE | DIALOG_TYPE,
                                                                    1,
                                                                    1,
                                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FUNDINFO = I_( "GUIDLG_FUNDINFO" );
static CommandTraits cmdTrait_CMD_GUI_FUNDINFO( CMD_GUI_FUNDINFO,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ADDRESSES = I_( "GUIDLG_ADDRESSES" );
static CommandTraits cmdTrait_CMD_GUI_ADDRESSES( CMD_GUI_ADDRESSES,
                                                 GUI_TYPE | DIALOG_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACB = I_( "GUIDLG_ACB" );
static CommandTraits cmdTrait_CMD_GUI_ACB( CMD_GUI_ACB,
                                           GUI_TYPE | DIALOG_TYPE,
                                           1,
                                           1,
                                           MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_CHEQUE = I_( "GUIDLG_CHEQUE" );
static CommandTraits cmdTrait_CMD_GUI_CHEQUE( CMD_GUI_CHEQUE,
                                              GUI_TYPE | DIALOG_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_CONFIRMATION = I_( "GUIDLG_CONFIRMATION" );
static CommandTraits cmdTrait_CMD_GUI_CONFIRMATION( CMD_GUI_CONFIRMATION,
                                                    GUI_TYPE | DIALOG_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_COA = I_( "GUIDLG_COA" );
static CommandTraits cmdTrait_CMD_GUI_COA( CMD_GUI_COA,
                                           GUI_TYPE | DIALOG_TYPE,
                                           1,
                                           1,
                                           MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_SHAREHOLDER = I_( "GUIDLG_SHAREHOLDER" );
static CommandTraits cmdTrait_CMD_GUI_SHAREHOLDER( CMD_GUI_SHAREHOLDER,
                                                   GUI_TYPE | DIALOG_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_CASH_DIVIDEND = I_( "GUIDLG_CASH_DIVIDEND" );
static CommandTraits cmdTrait_CMD_GUI_CASH_DIVIDEND( CMD_GUI_CASH_DIVIDEND,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_DISTRIBUTION = I_( "GUIDLG_DISTRIBUTION" );
static CommandTraits cmdTrait_CMD_GUI_DISTRIBUTION ( CMD_GUI_DISTRIBUTION ,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_SIMPLE_ALLOCATION = I_( "CMD_GUI_SIMPLE_ALLOCATION" );
static CommandTraits cmdTrait_CMD_GUI_SIMPLE_ALLOCATION( CMD_GUI_SIMPLE_ALLOCATION,
                                                   GUI_TYPE | DIALOG_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRANSACTION_ALLOCATIONS = I_( "GUIDLG_TRANSACTION_ALLOCATIONS" );
static CommandTraits cmdTrait_CMD_GUI_TRANSACTION_ALLOCATIONS( CMD_GUI_TRANSACTION_ALLOCATIONS,
                                                               GUI_TYPE | DIALOG_TYPE,
                                                               1,
                                                               1,
                                                               MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ADMINDATES = I_( "GUIDLG_ADMINDATES" );
static CommandTraits cmdTrait_CMD_GUI_ADMINDATES ( CMD_GUI_ADMINDATES ,
                                                   GUI_TYPE | DIALOG_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MGMTDETAILS = I_( "GUIDLG_MGMTDETAILS" );
static CommandTraits cmdTrait_CMD_GUI_MGMTDETAILS ( CMD_GUI_MGMTDETAILS ,
                                                    GUI_TYPE | DIALOG_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCINFO = I_( "GUIDLG_ACCINFO" );
static CommandTraits cmdTrait_CMD_GUI_ACCINFO( CMD_GUI_ACCINFO,
                                               GUI_TYPE | DIALOG_TYPE,
                                               1,
                                               1,
                                               MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FREEUNIT = I_( "GUIDLG_FREEUNIT" );
static CommandTraits cmdTrait_CMD_GUI_FREEUNIT( CMD_GUI_FREEUNIT,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_BANK = I_( "GUIDLG_BANK" );
static CommandTraits cmdTrait_CMD_GUI_BANK( CMD_GUI_BANK,
                                            GUI_TYPE | DIALOG_TYPE,
                                            1,
                                            1,
                                            MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_BROKER = I_( "GUIDLG_BROKER" );
static CommandTraits cmdTrait_CMD_GUI_BROKER( CMD_GUI_BROKER,
                                              GUI_TYPE | DIALOG_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_BRANCH = I_( "GUIDLG_BRANCH" );
static CommandTraits cmdTrait_CMD_GUI_BRANCH( CMD_GUI_BRANCH,
                                              GUI_TYPE | DIALOG_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_SLSREP = I_( "GUIDLG_SLSREP" );
static CommandTraits cmdTrait_CMD_GUI_SLSREP( CMD_GUI_SLSREP,
                                              GUI_TYPE | DIALOG_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_RRIF_LIF_LRIF_INFO = I_( "GUIDLG_RRIF_LIF_LRIF_INFO" );
static CommandTraits cmdTrait_CMD_GUI_RRIF_LIF_LRIF_INFO( CMD_GUI_RRIF_LIF_LRIF_INFO,
                                                          GUI_TYPE | DIALOG_TYPE,
                                                          1,
                                                          1,
                                                          MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRADES = I_( "GUIDLG_TRADES" );
static CommandTraits cmdTrait_CMD_GUI_TRADES( CMD_GUI_TRADES,
                                              GUI_TYPE | DIALOG_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );

/*CLASS_EXPORT const I_CHAR *CMD_GUI_TRADES2 = I_( "GUIDLG_Trades2" );
static CommandTraits cmdTrait_CMD_GUI_TRADES2(CMD_GUI_TRADES2,
                                              GUI_TYPE | DIALOG_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );
*/

CLASS_EXPORT const I_CHAR *CMD_GUI_IDENT_ACC = I_( "GUIDLG_IDENT_ACC" );
static CommandTraits cmdTrait_CMD_GUI_IDENT_ACC( CMD_GUI_IDENT_ACC,
                                                 GUI_TYPE | DIALOG_TYPE,
                                                 1,
                                                 1,
                                                 MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_CONTRACTINFO = I_( "GUIDLG_CONTRACTINFO" );
static CommandTraits cmdTrait_CMD_GUI_CONTRACTINFO( CMD_GUI_CONTRACTINFO,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_REG_PLAN_TRANSFER = I_( "GUIDLG_REG_PLAN_TRANSFER" );
static CommandTraits cmdTrait_CMD_GUI_REG_PLAN_TRANSFER( CMD_GUI_REG_PLAN_TRANSFER,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_REG_PLAN_TRANSFER_SEARCH = I_( "GUIDLG_REG_PLAN_TRANSFER_SEARCH" );
static CommandTraits cmdTrait_CMD_GUI_REG_PLAN_TRANSFER_SEARCH( CMD_GUI_REG_PLAN_TRANSFER_SEARCH,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_GUARANTEEINFO = I_( "GUIDLG_GUARANTEEINFO" );
static CommandTraits cmdTrait_CMD_GUI_GUARANTEEINFO( CMD_GUI_GUARANTEEINFO,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MINMAXINFO = I_( "GUIDLG_MINMAXINFO" );
static CommandTraits cmdTrait_CMD_GUI_MINMAXINFO( CMD_GUI_MINMAXINFO,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_TAXRATES = I_( "GUIDLG_TAXRATES" );
static CommandTraits cmdTrait_CMD_GUI_TAXRATES( CMD_GUI_TAXRATES,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_RESPINFO = I_( "GUIDLG_RESPINFO" );
static CommandTraits cmdTrait_CMD_GUI_RESPINFO( CMD_GUI_RESPINFO,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_RESPTRANSACTIONS = I_( "GUIDLG_RESPTRANSACTIONS" );
static CommandTraits cmdTrait_CMD_GUI_RESPTRANSACTIONS( CMD_GUI_RESPTRANSACTIONS,
                                                        GUI_TYPE | DIALOG_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_HYPOTHETICALRED = I_( "GUIDLG_HYPOTHETICALRED" );
// no command traits!

CLASS_EXPORT const I_CHAR *CMD_GUI_FUNDCLASS = I_( "GUIDLG_FUNDCLASS" );
static CommandTraits cmdTrait_CMD_GUI_FUNDCLASS( CMD_GUI_FUNDCLASS,
                                                 GUI_TYPE | DIALOG_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH);

CLASS_EXPORT const I_CHAR *CMD_GUI_FUNDGROUP = I_( "GUIDLG_FUNDGROUP" );
static CommandTraits cmdTrait_CMD_GUI_FUNDGROUP( CMD_GUI_FUNDGROUP,
                                                 GUI_TYPE | DIALOG_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_REDCODEBYTAXTYPE = I_( "GUIDLG_REDCODEBYTAXTYPE" );
// no command traits!

CLASS_EXPORT const I_CHAR *CMD_GUI_RESPBENREL = I_( "GUIDLG_RESPBENREL" );
static CommandTraits cmdTrait_CMD_GUI_RESPBENREL( CMD_GUI_RESPBENREL,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_SPLITCOMMISSION = I_( "GUIDLG_SPLITCOMMISSION" );
static CommandTraits cmdTrait_CMD_GUI_SPLITCOMMISSION( CMD_GUI_SPLITCOMMISSION,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_FINANCIAL_INSTITUTION = I_( "GUIDLG_FINANCIAL_INSTITUTION" );
static CommandTraits cmdTrait_CMD_GUI_FINANCIAL_INSTITUTION( CMD_GUI_FINANCIAL_INSTITUTION,
                                                   GUI_TYPE | DIALOG_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FINANCIAL_INSTITUTION_SEARCH = I_( "GUIDLG_FINANCIAL_INSTITUTION_SEARCH" );
static CommandTraits cmdTrait_CMD_GUI_FINANCIAL_INSTITUTION_SEARCH( CMD_GUI_FINANCIAL_INSTITUTION_SEARCH,
                                                   GUI_TYPE | DIALOG_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_SYSTEMATIC_INDEXING = I_( "GUIDLG_SYSTEMATIC_INDEXING" );
static CommandTraits cmdTrait_CMD_GUI_SYSTEMATIC_INDEXING( CMD_GUI_SYSTEMATIC_INDEXING,
                                                           GUI_TYPE | DIALOG_TYPE,
                                                           1,
                                                           1,
                                                           MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ESOPINFO = I_( "GUIDLG_ESOPINFO" );
static CommandTraits cmdTrait_CMD_GUI_ESOPINFO( CMD_GUI_ESOPINFO,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_AMS_GLOBAL = I_( "GUIDLG_AMSGLOBAL" );
static CommandTraits cmdTrait_CMD_GUI_AMS_GLOBAL( CMD_GUI_AMS_GLOBAL,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_YTD_CONTRIBUTION = I_( "GUIDLG_YTD_CONTRIBUTION" );
static CommandTraits cmdTrait_CMD_GUI_YTD_CONTRIBUTION( CMD_GUI_YTD_CONTRIBUTION,
                                                        GUI_TYPE | DIALOG_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MATCHTRANSFER = I_( "GUIDLG_MATCHTRANSFER" );
static CommandTraits cmdTrait_CMD_GUI_MATCHTRANSFER( CMD_GUI_MATCHTRANSFER,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_AS_PENSION_PLAN = I_( "GUIDLG_AS_PENSION_PLAN" );
static CommandTraits cmdTrait_CMD_GUI_AS_PENSION_PLAN( CMD_GUI_AS_PENSION_PLAN,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCT_SPLITCOMM = I_( "GUIDLG_ACCT_SPLITCOMM" );
static CommandTraits cmdTrait_CMD_GUI_ACCT_SPLITCOMM( CMD_GUI_ACCT_SPLITCOMM,
                                                      GUI_TYPE | DIALOG_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ESOP_HISTORICAL = I_( "GUIDLG_ESOP_HISTORICAL" );
static CommandTraits cmdTrait_CMD_GUI_ESOP_HISTORICAL( CMD_GUI_ESOP_HISTORICAL,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FEE_PARAMETER = I_( "GUIDLG_FEE_PARAMETER" );
static CommandTraits cmdTrait_CMD_GUI_FEE_PARAMETER( CMD_GUI_FEE_PARAMETER,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_SETTELEMENT = I_( "GUIDLG_SETTLEMENT" );
static CommandTraits cmdTrait_CMD_GUI_SETTLEMENT( CMD_GUI_SETTELEMENT,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ADDRESS_SELECTION = I_( "GUIDLG_ADDRESS_SELECTION" );
static CommandTraits cmdTrait_CMD_GUI_ADDRESS_SELECTION( CMD_GUI_ADDRESS_SELECTION,
                                                         GUI_TYPE | DIALOG_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCOUNTREVIEW = I_( "GUIDLG_ACCOUNTREVIEW" );
static CommandTraits cmdTrait_CMD_GUI_ACCOUNTREVIEW( CMD_GUI_ACCOUNTREVIEW,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_PENSION_INFO = I_( "GUIDLG_PENSION_INFO" );
static CommandTraits cmdTrait_CMD_GUI_PENSION_INFO( CMD_GUI_PENSION_INFO,
                                                    GUI_TYPE | DIALOG_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ESTATEMENT = I_( "GUIDLG_ESTATEMENT" );
static CommandTraits cmdTrait_CMD_GUI_ESTATEMENT( CMD_GUI_ESTATEMENT,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_HYPO_RED = I_( "GUIDLG_HYPO_RED" );
static CommandTraits cmdTrait_CMD_GUI_HYPO_RED( CMD_GUI_HYPO_RED,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FOREIGN_CONTENT_WORKSHEET= I_( "GUIDLG_FOREIGN_CONTENT_WORKSHEET" );
static CommandTraits cmdTrait_CMD_GUI_FOREIGN_CONTENT_WORKSHEET( CMD_GUI_FOREIGN_CONTENT_WORKSHEET,
                                                                 GUI_TYPE | DIALOG_TYPE,
                                                                 1,
                                                                 1,
                                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_AMSACCTLVL = I_( "GUIDLG_AMSACCTLVL" );
static CommandTraits cmdTrait_CMD_GUI_AMSACCTLVL( CMD_GUI_AMSACCTLVL,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_AMSBRKLVL = I_( "GUIDLG_AMSBRKLVL" );
static CommandTraits cmdTrait_CMD_GUI_AMSBRKLVL( CMD_GUI_AMSBRKLVL,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MKT_INDEX_MASTER = I_( "GUIDLG_MKTINDEXMASTER" );
static CommandTraits cmdTrait_CMD_GUI_MKT_INDEX_MASTER( CMD_GUI_MKT_INDEX_MASTER,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MKT_INDEX_VALUES = I_( "GUIDLG_MKTINDEXVALUES" );
static CommandTraits cmdTrait_CMD_GUI_MKT_INDEX_VALUES( CMD_GUI_MKT_INDEX_VALUES,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCT_LVL_CUT_OFF_TIMES = I_( "GUIDLG_ACCT_LVL_CUT_OFF_TIMES" );
static CommandTraits cmdTrait_CMD_GUI_ACCT_LVL_CUT_OFF_TIMES( CMD_GUI_ACCT_LVL_CUT_OFF_TIMES,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MSG = I_( "GUIDLG_MSG" );
static CommandTraits cmdTrait_CMD_GUI_MSG( CMD_GUI_MSG,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MSG_SEARCH = I_( "GUIDLG_MSGSEARCH" );
static CommandTraits cmdTrait_CMD_GUI_MSG_SEARCH( CMD_GUI_MSG_SEARCH,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MSG_DETAIL = I_( "GUIDLG_MSGDETAIL" );
static CommandTraits cmdTrait_CMD_GUI_MSG_DETAIL( CMD_GUI_MSG_DETAIL,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FILE_INQUIRY = I_( "GUIDLG_FILEINQUIRY" );
static CommandTraits cmdTrait_CMD_GUI_FILE_INQUIRY( CMD_GUI_FILE_INQUIRY,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FILE_SEARCH = I_( "GUIDLG_FILESEARCH" );
static CommandTraits cmdTrait_CMD_GUI_FILE_SEARCH( CMD_GUI_FILE_SEARCH,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_USERDEFMAT = I_( "GUIDLG_USERDEFMAT" );
static CommandTraits cmdTrait_CMD_GUI_USERDEFMAT( CMD_GUI_USERDEFMAT,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ENTITY_ADDRESS_SEARCH = I_( "GUIDLG_ENTITY_ADDRESS_SEARCH" );
static CommandTraits cmdTrait_CMD_GUI_ENTITY_ADDRESS_SEARCH( CMD_GUI_ENTITY_ADDRESS_SEARCH,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_SETTLEMENT_INSTRUCTIONS_SYSLVL = I_( "GUIDLG_SETTLEMENT_INSTRUCTIONS_SYSLVL" );
static CommandTraits cmdTrait_CMD_GUI_SETTLEMENT_INSTRUCTIONS_SYSLVL( CMD_GUI_SETTLEMENT_INSTRUCTIONS_SYSLVL,
                                                                      GUI_TYPE | DIALOG_TYPE,
                                                                      1,
                                                                      1,
                                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_SETTLEMENT_INSTRUCTIONS_ACCTLVL = I_( "GUIDLG_SETTLEMENT_INSTRUCTIONS_ACCTLVL" );
static CommandTraits cmdTrait_CMD_GUI_SETTLEMENT_INSTRUCTIONS_ACCTLVL( CMD_GUI_SETTLEMENT_INSTRUCTIONS_ACCTLVL,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_SETTLEMENT_LOCATION_TRADE = I_( "GUIDLG_SETTLEMENT_LOCATION_TRADE" );
static CommandTraits cmdTrait_CMD_GUI_SETTLEMENT_LOCATION_TRADE( CMD_GUI_SETTLEMENT_LOCATION_TRADE,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MANUAL_DIVIDEND = I_( "GUIDLG_MANUALDIVIDEND" );
static CommandTraits cmdTrait_CMD_GUI_MANUAL_DIVIDEND( CMD_GUI_MANUAL_DIVIDEND,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_REPORT = I_( "GUIDLG_REPORT" );
static CommandTraits cmdTrait_CMD_GUI_REPORT( CMD_GUI_REPORT,
                                              GUI_TYPE | DIALOG_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_REPORT_STATUS = I_( "GUIDLG_REPORT_STATUS" );
static CommandTraits cmdTrait_CMD_GUI_REPORT_STATUS( CMD_GUI_REPORT_STATUS,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_REPORT_VIEW = I_( "GUIDLG_REPORT_VIEW" );
static CommandTraits cmdTrait_CMD_GUI_REPORT_VIEW( CMD_GUI_REPORT_VIEW,
                                                   GUI_TYPE | DIALOG_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_PRINTER_LIST = I_( "GUIDLG_PRINTER_LIST" );
static CommandTraits cmdTrait_CMD_GUI_PRINTER_LIST( CMD_GUI_PRINTER_LIST,
                                                    GUI_TYPE | DIALOG_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FTP_LOGON = I_( "GUIDLG_FTP_LOGON" );
static CommandTraits cmdTrait_CMD_GUI_FTP_LOGON( CMD_GUI_FTP_LOGON,
                                                 GUI_TYPE | DIALOG_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );
//csc
CLASS_EXPORT const I_CHAR *CMD_GUI_SHR_FAMILY = I_( "CMD_GUI_SHR_FAMILY" );
static CommandTraits cmdTrait_CMD_GUI_SHR_FAMILY( CMD_GUI_SHR_FAMILY,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCOUNT_CONTRACT = I_( "CMD_GUI_ACCOUNT_CONTRACT" );
static CommandTraits cmdTrait_CMD_CMD_GUI_ACCOUNT_CONTRACT( CMD_GUI_ACCOUNT_CONTRACT,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCT_CATEGORY = I_( "CMD_GUI_ACCT_CATEGORY" );
static CommandTraits cmdTrait_CMD_GUI_ACCT_CATEGORY( CMD_GUI_ACCT_CATEGORY,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRADE_SETTLEMENT_LOCATIONS = I_( "GUIDLG_TRADE_SETTLEMENT_LOCATIONS" );
static CommandTraits cmdTrait_CMD_GUI_TRADE_SETTLEMENT_LOCATIONS( CMD_GUI_TRADE_SETTLEMENT_LOCATIONS,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_RESP_BENEF_ALLOCATION_LIST = I_( "GUIDLG_RESP_BENEF_ALLOCATION_LIST" );
static CommandTraits cmdTrait_CMD_GUI_RESP_BENEF_ALLOCATION_LIST( CMD_GUI_RESP_BENEF_ALLOCATION_LIST,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_RESP_TRANSFER = I_( "GUIDLG_RESP_TRANSFER " );
static CommandTraits cmdTrait_CMD_GUI_RESP_TRANSFER ( CMD_GUI_RESP_TRANSFER,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_GUI_REG_DOCUMENT_LIST = I_( "CMD_GUI_REG_DOCUMENT_LIST" );
static CommandTraits cmdTrait_CMD_GUI_REG_DOCUMENT_LIST( CMD_GUI_REG_DOCUMENT_LIST,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MATSWP_INSTRUCTIONS = I_( "CMD_GUI_MATSWP_INSTRUCTIONS" );
static CommandTraits cmdTrait_CMD_GUI_MATSWP_INSTRUCTIONS( CMD_GUI_MATSWP_INSTRUCTIONS,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MATSWP_INSTR = I_( "CMD_GUI_MATSWP_INSTR" );
static CommandTraits cmdTrait_CMD_GUI_MATSWP_INSTR( CMD_GUI_MATSWP_INSTR,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MATSWP_INSTR_DETLS = I_( "CMD_GUI_MATSWP_INSTR_DETLS" );
static CommandTraits cmdTrait_CMD_GUI_MATSWP_INSTR_DETLS( CMD_GUI_MATSWP_INSTR_DETLS,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_GUI_TRADE_AUTHORIZATION = I_( "CMD_GUI_TRADE_AUTHORIZATION" );
static CommandTraits cmdTrait_CMD_GUI_TRADE_AUTHORIZATION( CMD_GUI_TRADE_AUTHORIZATION,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRADE_SOURCE_OF_FUNDS_CHECKED = I_( "CMD_GUI_TRADE_SOURCE_OF_FUNDS_CHECKED" );
static CommandTraits cmdTrait_CMD_GUI_TRADE_SOURCE_OF_FUND_CHECKED( CMD_GUI_TRADE_SOURCE_OF_FUNDS_CHECKED,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_BATCH = I_( "CMD_GUI_BATCH" );
static CommandTraits cmdTrait_CMD_GUI_BATCH( CMD_GUI_BATCH,
                                             GUI_TYPE | DIALOG_TYPE,
                                             1,
                                             1,
                                             MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_KYC_BROKER = I_( "CMD_GUI_KYC_BROKER" );
static CommandTraits cmdTrait_CMD_GUI_KYC_BROKER( CMD_GUI_KYC_BROKER,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_RESET_INSTR = I_( "CMD_GUI_RESET_INSTR" );
static CommandTraits cmdTrait_CMD_CMD_GUI_RESET_INSTR( CMD_GUI_RESET_INSTR,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_PROTECTED_FUND = I_( "GUIDLG_PROTECTED_FUND" );
static CommandTraits cmdTrait_CMD_GUI_PROTECTED_FUND( CMD_GUI_PROTECTED_FUND,
                                                   GUI_TYPE | DIALOG_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FEE_PARAMETER_SYSTEM = I_( "GUIDLG_FEE_PARAMETER_SYSTEM" );
static CommandTraits cmdTrait_CMD_GUI_FEE_PARAMETER_SYSTEM( CMD_GUI_FEE_PARAMETER_SYSTEM,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_HISTORICAL_INFO = I_( "CMD_GUI_HISTORICAL_INFO" );
static CommandTraits cmdTrait_CMD_GUI_HISTORICAL_INFO( CMD_GUI_HISTORICAL_INFO,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_HISTORICAL_INFO_SRCH = I_( "CMD_GUI_HISTORICAL_INFO_SRCH" );
static CommandTraits cmdTrait_CMD_GUI_HISTORICAL_INFO_SRCH( CMD_GUI_HISTORICAL_INFO_SRCH,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRADE_SEARCH = I_( "CMD_GUI_TRADE_SEARCH" );
static CommandTraits cmdTrait_CMD_GUI_TRADE_SEARCH( CMD_GUI_TRADE_SEARCH,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );
												  
CLASS_EXPORT const I_CHAR *CMD_GUI_TRADE_VERIFICATION_SEARCH= I_( "CMD_GUI_TRADE_VERIFICATION_SEARCH" );
static CommandTraits cmdTrait_CMD_GUI_TRADE_VERIFICATION_SEARCH( CMD_GUI_TRADE_VERIFICATION_SEARCH,
                                                                 GUI_TYPE | DIALOG_TYPE,
                                                                 1,
                                                                 1,
                                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_BROKER_ADDRESS = I_( "CMD_GUI_BROKER_ADDRESS" );
static CommandTraits cmdTrait_CMD_GUI_BROKER_ADDRESS( CMD_GUI_BROKER_ADDRESS,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FROM_TO_ALLOCATION = I_( "CMD_GUI_FROM_TO_ALLOCATION" );
static CommandTraits cmdTrait_CMD_GUI_FROM_TO_ALLOCATION( CMD_GUI_FROM_TO_ALLOCATION,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FEATURES_SEARCH = I_( "CMD_GUI_FEATURES_SEARCH" );
static CommandTraits cmdTrait_CMD_GUI_FEATURES_SEARCH( CMD_GUI_FEATURES_SEARCH,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_PAY_TO_ENTITY = I_( "CMD_GUI_PAY_TO_ENTITY" );
static CommandTraits cmdTrait_CMD_GUI_PAY_TO_ENTITY( CMD_GUI_PAY_TO_ENTITY,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_PAYMENT_INSTRUCTIONS = I_( "CMD_GUI_PAYMENT_INSTRUCTIONS" );
static CommandTraits cmdTrait_CMD_GUI_PAYMENT_INSTRUCTIONS( CMD_GUI_PAYMENT_INSTRUCTIONS,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );
CLASS_EXPORT const I_CHAR *CMD_GUI_AMS_LMT_OVERRIDE = I_( "GUIDLG_AMSLMTOVERRIDE" );
static CommandTraits cmdTrait_CMD_GUI_AMS_LMT_OVERRIDE(  CMD_GUI_AMS_LMT_OVERRIDE,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_AMS_HYPO_ALLOC = I_( "GUIDLG_AMSHYPOALLOC" );
static CommandTraits cmdTrait_CMD_GUI_AMS_HYPO_ALLOC(  CMD_GUI_AMS_HYPO_ALLOC,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_AMS_DELTA_ALLOC = I_( "GUIDLG_AMSDELTAALLOC" );
static CommandTraits cmdTrait_CMD_GUI_AMS_DELTA_ALLOC(  CMD_GUI_AMS_DELTA_ALLOC,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_MULTI_FUND_ALLOCATION = I_( "GUIDLG_MULTIFUNDALLOCATION" );
static CommandTraits cmdTrait_CMD_GUI_MULTI_FUND_ALLOCATION( CMD_GUI_MULTI_FUND_ALLOCATION,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRADES_TAXRATE = I_( "GUIDLG_TRADES_TAXRATE" );
static CommandTraits cmdTrait_CMD_GUI_TRADES_TAXRATE( CMD_GUI_TRADES_TAXRATE,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_MODALONLY );
CLASS_EXPORT const I_CHAR *CMD_GUI_DIRECT_TRADING = I_( "GUIDLG_DIRECT_TRADING" );
static CommandTraits cmdTrait_CMD_GUI_DIRECT_TRADING( CMD_GUI_DIRECT_TRADING,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRANSITS = I_( "GUIDLG_TRANSITS" );
static CommandTraits cmdTrait_CMD_GUI_TRANSITS( CMD_GUI_TRANSITS,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_FUND_FACTORS = I_( "GUIDLG_FUND_FACTORS" );
static CommandTraits cmdTrait_CMD_GUI_FUND_FACTORS( CMD_GUI_FUND_FACTORS,
                                                GUI_TYPE | DIALOG_TYPE,
                                                1,
                                                1,
                                                MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_FIRE_FIGHTER_LOGON = I_( "GUIDLG_FIRE_FIGHTER_LOGON" );
static CommandTraits cmdTrait_CMD_GUI_FIRE_FIGHTER_LOGON( CMD_GUI_FIRE_FIGHTER_LOGON,
                                             GUI_TYPE | DIALOG_TYPE,
                                             1,
                                             1,
                                             MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_DAILY_TRANSACTION_FEES = I_( "GUIDLG_DAILY_TRANSACTION_FEES" );
static CommandTraits cmdTrait_CMD_GUI_DAILY_TRANSACTION_FEES( CMD_GUI_DAILY_TRANSACTION_FEES,
                                                              GUI_TYPE | DIALOG_TYPE,
                                                              1,
                                                              1,
                                                              MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRANSACTION_HISTORY_DEDUCT_DETAIL = I_( "GUIDLG_TRANSACTION_HISTORY_DEDUCT_DETAIL" );
static CommandTraits cmdTrait_CMD_GUI_TRANSACTION_HISTORY_DEDUCT_DETAIL( CMD_GUI_TRANSACTION_HISTORY_DEDUCT_DETAIL,
                                                                         GUI_TYPE | DIALOG_TYPE,
                                                                         1,
                                                                         1,
                                                                         MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_AWD_COMMENT = I_( "GUI_AWD_COMMENT" );
static CommandTraits cmdTrait_CMD_GUI_AWD_COMMENT( CMD_GUI_AWD_COMMENT,
                                                   GUI_TYPE | DIALOG_TYPE,
                                                   1,
                                                   1,
                                                   MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_INVENTORY_SUMMARY = I_( "GUIDLG_INVENTORY_SUMMARY" );
static CommandTraits cmdTrait_CMD_GUI_INVENTORY_SUMMARY( CMD_GUI_INVENTORY_SUMMARY,
                                                                         GUI_TYPE | DIALOG_TYPE,
                                                                         1,
                                                                         1,
                                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_SHR_FUND_SPONSOR_AGREEMENT = I_( "GUIDLG_SHR_FUND_SPONSOR_AGREEMENT" );
static CommandTraits cmdTrait_CMD_GUI_SHR_FUND_SPONSOR_AGREEMENT( CMD_GUI_SHR_FUND_SPONSOR_AGREEMENT,
                                                              GUI_TYPE | DIALOG_TYPE,
                                                              1,
                                                              1,
                                                              MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_SHR_FUND_BROKER = I_( "GUIDLG_SHR_FUND_BROKER" );
static CommandTraits cmdTrait_CMD_GUI_SHR_FUND_BROKER( CMD_GUI_SHR_FUND_BROKER,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_TAX_EXEMPT_AUTHORIZATION = I_( "GUIDLG_TAX_EXEMPT_AUTHORIZATION" );
static CommandTraits cmdTrait_CMD_GUI_TAX_EXEMPT_AUTHORIZATION( CMD_GUI_TAX_EXEMPT_AUTHORIZATION,
                                                              GUI_TYPE | DIALOG_TYPE,
                                                              1,
                                                              1,
                                                              MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_FEE_MODEL = I_( "GUIDLG_FEE_MODEL" );
static CommandTraits cmdTrait_CMD_GUI_FEE_MODEL( CMD_GUI_FEE_MODEL,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FEE_MODEL_COPY_TO = I_( "GUIDLG_FEE_MODEL_COPY_TO" );
static CommandTraits cmdTrait_CMD_GUI_FEE_MODEL_COPY_TO( CMD_GUI_FEE_MODEL_COPY_TO,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_GUI_HOLDING_COMP = I_( "GUIDLG_HOLDING_COMP" );
static CommandTraits cmdTrait_CMD_GUI_HOLDING_COMP( CMD_GUI_HOLDING_COMP,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );
CLASS_EXPORT const I_CHAR *CMD_GUI_FEE_PARAM_MAINT = I_( "GUIDLG_FEE_PARAM_MAINT" );
static CommandTraits cmdTrait_CMD_GUI_FEE_PARAM_MAINT( CMD_GUI_FEE_PARAM_MAINT,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );



CLASS_EXPORT const I_CHAR *CMD_GUI_FUNDSPONSOR_FEE_MODEL = I_( "GUIDLG_FUNDSPONSOR_FEE_MODEL" );
static CommandTraits cmdTrait_CMD_GUI_FUNDSPONSOR_FEE_MODEL( CMD_GUI_FUNDSPONSOR_FEE_MODEL,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRANSACTION_EXTERNAL_LINKS = I_( "GUIDLG_TRANSACTION_EXTERNAL_LINKS" );
static CommandTraits cmdTrait_CMD_GUI_TRANSACTION_EXTERNAL_LINKS( CMD_GUI_TRANSACTION_EXTERNAL_LINKS,
                                                                  GUI_TYPE | DIALOG_TYPE,
                                                                  1,
                                                                  1,
                                                                  MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_FUND_BROKER = I_( "GUIDLG_FUND_BROKER" );
static CommandTraits cmdTrait_CMD_GUI_FUND_BROKER( CMD_GUI_FUND_BROKER,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_AGGREGATED_ORDER = I_( "AGGREGATED_ORDER" );
static CommandTraits cmdTrait_CMD_GUI_AGGREGATED_ORDER( CMD_GUI_AGGREGATED_ORDER,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_FUND_BROKER_SETTLEMENT_INSTR = I_( "GUIDLG_FUND_BROKER_SETTLEMENT_INSTR" );
static CommandTraits cmdTrait_CMD_GUI_FUND_BROKER_SETTLEMENT_INSTR( CMD_GUI_FUND_BROKER_SETTLEMENT_INSTR,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_INVENTORY_DETAIL_DEDUCTION = I_( "GUIDLG_INVENTORY_DETAIL_DEDUCTION" );
static CommandTraits cmdTrait_CMD_GUI_INVENTORY_DETAIL_DEDUCTION( CMD_GUI_INVENTORY_DETAIL_DEDUCTION,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRANS_CANCEL = I_( "GUIDLG_TRANS_CANCEL" );
static CommandTraits cmdTrait_CMD_GUI_TRANS_CANCEL( CMD_GUI_TRANS_CANCEL,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_DILUTION = I_( "GUIDLG_DILUTION" );
static CommandTraits cmdTrait_CMD_GUI_DILUTION( CMD_GUI_DILUTION,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ENTITY_ALONE = I_( "GUIDLG_ENTITY_ALONE" );
static CommandTraits cmdTrait_CMD_GUI_ENTITY_ALONE( CMD_GUI_ENTITY_ALONE,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_CONFIRM_REPRINT = I_( "GUIDLG_CONFIRM_REPRINT" );
static CommandTraits cmdTrait_CMD_GUI_CONFIRM_REPRINT( CMD_GUI_CONFIRM_REPRINT,
                                                            GUI_TYPE | DIALOG_TYPE,
                                                      1,
                                                    1,
                                                    MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_OPC_CONFIRM_REPRINT = I_( "GUIDLG_OPC_CONFIRM_REPRINT" );
static CommandTraits cmdTrait_CMD_GUI_OPC_CONFIRM_REPRINT( CMD_GUI_OPC_CONFIRM_REPRINT,
                                                           GUI_TYPE | DIALOG_TYPE,
                                                           1,
                                                           1,
                                                           MODE_MODALONLY );


CLASS_EXPORT const I_CHAR *CMD_GUI_REBOOK_PARAM = I_( "GUIDLG_REBOOK_PARAM" );
static CommandTraits cmdTrait_CMD_GUI_REBOOK_PARAM( CMD_GUI_REBOOK_PARAM,
                                                    GUI_TYPE | DIALOG_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_GUI_TRANS_LINK = I_( "GUIDLG_TRANS_LINK" );
static CommandTraits cmdTrait_CMD_GUI_TRANS_LINK( CMD_GUI_TRANS_LINK,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_CANCELLATION_INSTR = I_( "GUIDLG_CANCELLATION_INSTR" );
static CommandTraits cmdTrait_CMD_GUI_CANCELLATION_INSTR( CMD_GUI_CANCELLATION_INSTR,
                                                    GUI_TYPE | DIALOG_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_GUI_SAVINGS_DIRECTIVE = I_( "GUIDLG_SAVINGS_DIRECTIVE" );
static CommandTraits cmdTrait_CMD_GUI_SAVINGS_DIRECTIVE( CMD_GUI_SAVINGS_DIRECTIVE,
                                                         GUI_TYPE | DIALOG_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_BROWSER_LAUNCH = I_( "GUIDLG_BROWSER_LAUNCH" );
static CommandTraits cmdTrait_CMD_GUI_BROWSER_LAUNCH( CMD_GUI_BROWSER_LAUNCH,
                                                      GUI_TYPE | DIALOG_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_TRADE_PAYMENT_INSTRUCTIONS = I_( "GUIDLG_TRADE_PAYMENT_INSTRUCTIONS" );
static CommandTraits cmdTrait_CMD_GUI_TRADE_PAYMENT_INSTRUCTIONS( CMD_GUI_TRADE_PAYMENT_INSTRUCTIONS,
                                                                  GUI_TYPE | DIALOG_TYPE,
                                                                  1,
                                                                  1,
                                                                  MODE_BOTH);

CLASS_EXPORT const I_CHAR *CMD_GUI_CLONE_ACCOUNT = I_( "GUIDLG_CLONE_ACCOUNT" );
static CommandTraits cmdTrait_CMD_GUI_CLONE_ACCOUNT( CMD_GUI_CLONE_ACCOUNT,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_MODALONLY);

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCT_REGIS_MAINT = I_( "GUIDLG_ACCT_REGIS_MAINT" );
static CommandTraits cmdTrait_CMD_GUI_ACCT_REGIS_MAINT( CMD_GUI_ACCT_REGIS_MAINT,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_MODALONLY);

CLASS_EXPORT const I_CHAR *CMD_GUI_ENT_REG_MAINT = I_( "GUIDLG_ENT_REG_MAINT" );
static CommandTraits cmdTrait_CMD_GUI_ENT_REG_MAINT( CMD_GUI_ENT_REG_MAINT,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_MODALONLY);

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCT_LEVEL_SETTLEMENT_RULE = I_( "GUIDLG_ACCT_LEVEL_SETTLEMENT_RULE" );
static CommandTraits cmdTrait_CMD_GUI_ACCT_LEVEL_SETTLEMENT_RULE( CMD_GUI_ACCT_LEVEL_SETTLEMENT_RULE,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH);

CLASS_EXPORT const I_CHAR *CMD_GUI_PROGRESS_CTRL = I_( "GUIDLG_PROGRESS_CTRL" );
static CommandTraits cmdTrait_CMD_GUI_PROGRESS_CTRL( CMD_GUI_PROGRESS_CTRL,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_MODALONLY);
                                                     
CLASS_EXPORT const I_CHAR *CMD_GUI_ADDR_TAX_JURIS_UPDATE = I_( "GUIDLG_ADDR_TAX_JURIS_UPDATE" );
static CommandTraits cmdTrait_CMD_GUI_ADDR_TAX_JURIS_UPDATE( CMD_GUI_ADDR_TAX_JURIS_UPDATE,
                                                      GUI_TYPE|DIALOG_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_INVESTOR_AUTHORIZATION_INFORMATION = I_( "GUIDLG_INVESTOR_AUTHORIZATION_INFORMATION" );
static CommandTraits cmdTrait_CMD_GUI_INVESTOR_AUTHORIZATION_INFORMATION( CMD_GUI_INVESTOR_AUTHORIZATION_INFORMATION,
                                                      GUI_TYPE|DIALOG_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_RESP_ACCT_INFO_NASU = I_( "GUIDLG_RESP_ACCT_INFO_NASU" );
static CommandTraits cmdTrait_CMD_GUI_RESP_ACCT_INFO_NASU( CMD_GUI_RESP_ACCT_INFO_NASU,
                                                      GUI_TYPE|DIALOG_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_PSE_EAP = I_( "GUIDLG_PSE_EAP" );
static CommandTraits cmdTrait_CMD_GUI_PSE_EAP( CMD_GUI_PSE_EAP,
                                               GUI_TYPE | DIALOG_TYPE,
                                               1,
                                               1,
                                               MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCT_GUARNT_GUARD_OPTN = I_( "GUIDLG_ACCT_GUARNT_GUARD_OPTN" );
static CommandTraits cmdTrait_CMD_GUI_ACCT_GUARNT_GUARD_OPTN( CMD_GUI_ACCT_GUARNT_GUARD_OPTN,
                                                              GUI_TYPE | DIALOG_TYPE,
                                                              1,
                                                              1,
                                                              MODE_BOTH );
                                                             
CLASS_EXPORT const I_CHAR *CMD_GUI_GIA_INVEST_ATTRIBS = I_( "GUIDLG_GIA_INVEST_ATTRIBS" );
static CommandTraits cmdTrait_CMD_GUI_GIA_INVEST_ATTRIBS( CMD_GUI_GIA_INVEST_ATTRIBS,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCOUNT_COMMITMENT = I_( "GUIDLG_ACCOUNT_COMMITMENT" );
static CommandTraits cmdTrait_CMD_GUI_ACCOUNT_COMMITMENT( CMD_GUI_ACCOUNT_COMMITMENT,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_GI_INVESTMENT_DETAILS = I_( "GUIDLG_GI_INVESTMENT_DETAILS" );
static CommandTraits cmdTrait_CMD_GUI_GI_INVESTMENT_DETAILS( CMD_GUI_GI_INVESTMENT_DETAILS,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_INVESTMENT_HISTORY_LIST = I_( "CMD_GUI_INVESTMENT_HISTORY_LIST" );
static CommandTraits cmdTrait_CMD_GUI_INVESTMENT_HISTORY_LIST( CMD_GUI_INVESTMENT_HISTORY_LIST,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ESTATE_ALLOCATION = I_( "CMD_GUI_ESTATE_ALLOCATION" );
static CommandTraits cmdTrait_CMD_GUI_ESTATE_ALLOCATION( CMD_GUI_ESTATE_ALLOCATION,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_PROGRESSIVE_INTEREST_RATE_LIST = I_( "CMD_GUI_PROGRESSIVE_INTEREST_RATE_LIST" );
static CommandTraits cmdTrait_CMD_GUI_PROGRESSIVE_INTEREST_RATE_LIST( CMD_GUI_PROGRESSIVE_INTEREST_RATE_LIST,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_INTEREST_SEGMENT_LIST = I_( "CMD_GUI_INTEREST_SEGMENT_LIST" );
static CommandTraits cmdTrait_CMD_GUI_INTEREST_SEGMENT_LIST ( CMD_GUI_INTEREST_SEGMENT_LIST,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_CONTRACT_MATURITY_INSTRUCTIONS = I_( "CMD_GUI_CONTRACT_MATURITY_INSTRUCTIONS" );
static CommandTraits cmdTrait_CMD_GUI_CONTRACT_MATURITY_INSTRUCTIONS ( CMD_GUI_CONTRACT_MATURITY_INSTRUCTIONS,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_VALUE_VARIATION = I_( "CMD_GUI_VALUE_VARIATION" );
static CommandTraits cmdTrait_CMD_GUI_VALUE_VARIATION ( CMD_GUI_VALUE_VARIATION,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_AWDHISTORY = I_( "CMD_GUI_AWDHISTORY" );
static CommandTraits cmdTrait_CMD_GUI_AWDHISTORY( CMD_GUI_AWDHISTORY,
                                                 GUI_TYPE | DIALOG_TYPE,
                                                 1,
                                                 1,
                                                 MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_AWDHISTORY_BROWSER = I_( "CMD_GUI_AWDHISTORY_BROWSER" );
static CommandTraits cmdTrait_CMD_GUI_AWDHISTORY_BROWSER( CMD_GUI_AWDHISTORY_BROWSER,
                                                 GUI_TYPE | DIALOG_TYPE,
                                                 1,
                                                 1,
                                                 MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_GUI_ALERT_MESSAGES = I_( "GUIDLG_ALERT_MESSAGES" );
static CommandTraits cmdTrait_CMD_GUI_ALERT_MESSAGES(CMD_GUI_ALERT_MESSAGES,
                                                     GUI_TYPE | DIALOG_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_PRICE_ADDITIONAL = I_( "GUIDLG_PRICE_ADDITIONAL" );
static CommandTraits cmdTrait_CMD_GUI_PRICE_ADDITIONAL(CMD_GUI_PRICE_ADDITIONAL,
                                                       GUI_TYPE | DIALOG_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_EXTERNAL_INSTITUTION_SEARCH = I_( "CMD_GUI_EXTERNAL_INSTITUTION_SEARCH" );
static CommandTraits cmdTrait_CMD_GUI_EXTERNAL_INSTITUTION_SEARCH ( CMD_GUI_EXTERNAL_INSTITUTION_SEARCH,
                                                                    GUI_TYPE | DIALOG_TYPE,
                                                                    1,
                                                                    1,
                                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_ACCT_ROUNDING_RULE = I_( "GUIDLG_ACCT_ROUNDING_RULE" );
static CommandTraits cmdTrait_CMD_GUI_ACCT_ROUNDING_RULE( CMD_GUI_ACCT_ROUNDING_RULE,
                                                              GUI_TYPE | DIALOG_TYPE,
                                                              1,
                                                              1,
                                                              MODE_BOTH ); 

/***********************************************************************************************/
CLASS_EXPORT const I_CHAR *CMD_BPROC_SETTLEMENT = I_( "BPROC_SettlementProcess" );
static CommandTraits cmdTrait_CMD_BPROC_SETTLEMENT( CMD_BPROC_SETTLEMENT,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ENTITY = I_( "BPROC_EntityProcess" );
static CommandTraits cmdTrait_CMD_BPROC_ENTITY( CMD_BPROC_ENTITY,
                                                BUSINESS_PROCESS_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_IDCALLER = I_( "BPROC_IDCALLER" );
static CommandTraits cmdTrait_CMD_BPROC_IDCALLER( CMD_BPROC_IDCALLER,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

static CommandTraits cmdTrait_CMD_BPROC_USER_SESSION( CMD_BPROC_USER_SESSION,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_MODELESSONLY );

static CommandTraits cmdTrait_CMD_BPROC_WORK_SESSION( CMD_BPROC_WORK_SESSION,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_MODELESSONLY );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MANAGEMENT_COMPANY = I_( "BPROC_MANAGEMENT_COMPANY" );
static CommandTraits cmdTrait_CMD_BPROC_MANAGEMENT_COMPANY( CMD_BPROC_MANAGEMENT_COMPANY,
                                                            BUSINESS_PROCESS_TYPE,
                                                            1,
                                                            1,
                                                            MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ENTITY_SEARCH = I_( "BPROC_EntitySearchProcess" );
static CommandTraits cmdTrait_CMD_BPROC_ENTITY_SEARCH( CMD_BPROC_ENTITY_SEARCH,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_MODALONLY );


CLASS_EXPORT const I_CHAR *CMD_BPROC_ACC_DETAILS = I_( "BPROC_AC_DETAILS" );
static CommandTraits cmdTrait_CMD_BPROC_ACC_DETAILS( CMD_BPROC_ACC_DETAILS,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SYSTEMATIC = I_( "BPROC_SYSTEMATIC" );
static CommandTraits cmdTrait_CMD_BPROC_SYSTEMATIC( CMD_BPROC_SYSTEMATIC,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SYSTEMATIC_FEE = I_( "BPROC_SYSTEMATIC_FEE" );
static CommandTraits cmdTrait_CMD_BPROC_SYSTEMATIC_FEE( CMD_BPROC_SYSTEMATIC_FEE,
                                                        BUSINESS_PROCESS_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_CERTIFICATE = I_( "BPROC_CERTIFICATE" );
static CommandTraits cmdTrait_CMD_BPROC_CERTIFICATE( CMD_BPROC_CERTIFICATE,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRANS_HISTORY = I_( "BPROC_TRANS_HISTORY" );
static CommandTraits cmdTrait_CMD_BPROC_TRANS_HISTORY( CMD_BPROC_TRANS_HISTORY,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_DEMOGRAPHICS = I_( "BPROC_DEMOGRAPHICS" );
static CommandTraits cmdTrait_CMD_BPROC_DEMOGRAPHICS( CMD_BPROC_DEMOGRAPHICS,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REMARKS = I_( "BPROC_REMARKS" );
static CommandTraits cmdTrait_CMD_BPROC_REMARKS( CMD_BPROC_REMARKS,
                                                 BUSINESS_PROCESS_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCRUALS = I_( "BPROC_ACCRUALS" );
static CommandTraits cmdTrait_CMD_BPROC_ACCRUALS( CMD_BPROC_ACCRUALS,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_BANK_INSTRUCTIONS = I_( "BPROC_BankInstructionProcess" );
static CommandTraits cmdTrait_CMD_BPROC_BANK_INSTRUCTIONS( CMD_BPROC_BANK_INSTRUCTIONS,
                                                           BUSINESS_PROCESS_TYPE,
                                                           1,
                                                           1,
                                                           MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SYS_INDEX = I_( "BPROC_SYS_INDEX" );
static CommandTraits cmdTrait_CMD_BPROC_SYS_INDEX( CMD_BPROC_SYS_INDEX,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_HISTORICAL_ACCOUNT = I_( "BPROC_HISTORICAL_ACCOUNT" );
static CommandTraits cmdTrait_CMD_BPROC_HISTORICAL_ACCOUNT( CMD_BPROC_HISTORICAL_ACCOUNT,
                                                            BUSINESS_PROCESS_TYPE,
                                                            1,
                                                            1,
                                                            MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_HISTORICAL_SHAREHOLDER = I_( "BPROC_HISTORICAL_SHAREHOLDER" );
static CommandTraits cmdTrait_CMD_BPROC_HISTORICAL_SHAREHOLDER( CMD_BPROC_HISTORICAL_SHAREHOLDER,
                                                            BUSINESS_PROCESS_TYPE,
                                                            1,
                                                            1,
                                                            MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_HISTORICAL_SYS_INDEX = I_( "BPROC_HISTORICAL_SYS_INDEX" );
static CommandTraits cmdTrait_CMD_BPROC_HISTORICAL_SYS_INDEX( CMD_BPROC_HISTORICAL_SYS_INDEX,
                                                              BUSINESS_PROCESS_TYPE,
                                                              1,
                                                              1,
                                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_HISTORICAL_MARKET_VALUE = I_( "BPROC_HISTORICAL_MARKET_VALUE" );
static CommandTraits cmdTrait_CMD_BPROC_HISTORICAL_MARKET_VALUE( CMD_BPROC_HISTORICAL_MARKET_VALUE,
                                                                 BUSINESS_PROCESS_TYPE,
                                                                 1,
                                                                 1,
                                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUNDINFO = I_( "BPROC_FUNDINFO" );
static CommandTraits cmdTrait_CMD_BPROC_FUNDINFO( CMD_BPROC_FUNDINFO,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_UNITFACTORS = I_( "BPROC_UNITFACTORS" );
static CommandTraits cmdTrait_CMD_BPROC_UNITFACTORS( CMD_BPROC_UNITFACTORS,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ADDRESSES = I_( "BPROC_AddressProcess" );
static CommandTraits cmdTrait_CMD_BPROC_ADDRESSES( CMD_BPROC_ADDRESSES,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_ACB = I_( "BPROC_ACB" );
static CommandTraits cmdTrait_CMD_BPROC_ACB( CMD_BPROC_ACB,
                                             BUSINESS_PROCESS_TYPE,
                                             1,
                                             1,
                                             MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_CHEQUE = I_( "BPROC_CHEQUE" );
static CommandTraits cmdTrait_CMD_BPROC_CHEQUE( CMD_BPROC_CHEQUE,
                                                BUSINESS_PROCESS_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

static CommandTraits cmdTrait_CMD_BPROC_CONFIRMATION( CMD_BPROC_CONFIRMATION,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_COA = I_( "BPROC_COA" );
static CommandTraits cmdTrait_CMD_BPROC_COA( CMD_BPROC_COA,
                                             BUSINESS_PROCESS_TYPE,
                                             1,
                                             1,
                                             MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SHAREHOLDER = I_( "BPROC_ShareholderProcess" );
static CommandTraits cmdTrait_CMD_BPROC_SHAREHOLDER( CMD_BPROC_SHAREHOLDER,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_DISTRIBUTION = I_( "BPROC_AccountDistributionProcess" );
static CommandTraits cmdTrait_CMD_BPROC_DISTRIBUTION( CMD_BPROC_DISTRIBUTION,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ALLOCATIONS = I_( "BPROC_ALLOCATIONS" );
static CommandTraits cmdTrait_CMD_BPROC_ALLOCATIONS( CMD_BPROC_ALLOCATIONS,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNTALLOCATIONS = I_( "BPROC_AccountAllocationProcess" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNTALLOCATIONS( CMD_BPROC_ACCOUNTALLOCATIONS,
                                                            BUSINESS_PROCESS_TYPE,
                                                            1,
                                                            1,
                                                            MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRANSACTION_ALLOCATIONS = I_( "BPROC_TRANSACTION_ALLOCATIONS" );
static CommandTraits cmdTrait_CMD_BPROC_TRANSACTION_ALLOCATIONS( CMD_BPROC_TRANSACTION_ALLOCATIONS,
                                                                 BUSINESS_PROCESS_TYPE,
                                                                 1,
                                                                 1,
                                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ADMINDATES = I_( "BPROC_ADMINDATES" );
static CommandTraits cmdTrait_CMD_BPROC_ADMINDATES( CMD_BPROC_ADMINDATES,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MGMTDETAILS = I_( "BPROC_MGMTDETAILS" );
static CommandTraits cmdTrait_CMD_BPROC_MGMTDETAILS( CMD_BPROC_MGMTDETAILS,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_CLEANUP = I_( "BPROC_CLEANUP" );
static CommandTraits cmdTrait_CMD_BPROC_CLEANUP( CMD_BPROC_CLEANUP,
                                                 BUSINESS_PROCESS_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FILL_SEARCH_CRITERIA = I_( "BPROC_FILL_SEARCH_CRITERIA" );
static CommandTraits cmdTrait_CMD_BPROC_FILL_SEARCH_CRITERIA( CMD_BPROC_FILL_SEARCH_CRITERIA,
                                                              BUSINESS_PROCESS_TYPE,
                                                              1,
                                                              1,
                                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCINFO = I_( "BPROC_AccountInfoProcess" );
static CommandTraits cmdTrait_CMD_BPROC_ACCINFO( CMD_BPROC_ACCINFO,
                                                 BUSINESS_PROCESS_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_WHEREUSED = I_( "BPROC_WHEREUSED" );
static CommandTraits cmdTrait_CMD_BPROC_WHEREUSED ( CMD_BPROC_WHEREUSED ,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SEARCH = I_( "BPROC_SEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_SEARCH( CMD_BPROC_SEARCH,
                                                BUSINESS_PROCESS_TYPE,
                                                1,
                                                1,
                                                MODE_MODALONLY );


CLASS_EXPORT const I_CHAR *CMD_BPROC_FREEUNIT = I_( "BPROC_FREEUNIT" );
static CommandTraits cmdTrait_CMD_BPROC_FREEUNIT( CMD_BPROC_FREEUNIT,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_CLIENT = I_( "BPROC_ClientSearch" );
static CommandTraits cmdTrait_CMD_BPROC_CLIENT( CMD_BPROC_CLIENT,
                                                BUSINESS_PROCESS_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_TRANS = I_( "BPROC_ACCT_TRANS" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_TRANS( CMD_BPROC_ACCT_TRANS,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCTDETL = I_( "BPROC_AccountDetailsProcess" );
static CommandTraits cmdTrait_CMD_BPROC_ACCTDETL( CMD_BPROC_ACCTDETL,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_NASU = I_( "BPROC_NASU" );
static CommandTraits cmdTrait_CMD_BPROC_NASU   ( CMD_BPROC_NASU   ,
                                                 BUSINESS_PROCESS_TYPE,
                                                 1,
                                                 1,
                                                 MODE_MODALONLY );


CLASS_EXPORT const I_CHAR *CMD_BPROC_FUNDSRCH = I_( "BPROC_FundSearchProcess" );
static CommandTraits cmdTrait_CMD_BPROC_FUNDSRCH( CMD_BPROC_FUNDSRCH,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_BROKER = I_( "BPROC_BROKER" );
static CommandTraits cmdTrait_CMD_BPROC_BROKER( CMD_BPROC_BROKER,
                                                BUSINESS_PROCESS_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_BRANCH = I_( "BPROC_BRANCH" );
static CommandTraits cmdTrait_CMD_BPROC_BRANCH( CMD_BPROC_BRANCH,
                                                BUSINESS_PROCESS_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_SLSREP = I_( "BPROC_SLSREP" );
static CommandTraits cmdTrait_CMD_BPROC_SLSREP( CMD_BPROC_SLSREP,
                                                BUSINESS_PROCESS_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_RRIF_LIF_LRIF_INFO = I_( "BPROC_RRIF_LIF_LRIF_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_RRIF_LIF_LRIF_INFO( CMD_BPROC_RRIF_LIF_LRIF_INFO,
                                                            BUSINESS_PROCESS_TYPE,
                                                            1,
                                                            1,
                                                            MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_TRADES = I_( "BPROC_Trade" );
static CommandTraits cmdTrait_CMD_BPROC_TRADES( CMD_BPROC_TRADES,
                                                BUSINESS_PROCESS_TYPE,
                                                1,
                                                1,
                                                MODE_BOTH );

/*CLASS_EXPORT const I_CHAR *CMD_BPROC_TRADES2  = I_( "BPROC_Trades2" );
static CommandTraits cmdTrait_CMD_BPROC_TRADES2( CMD_BPROC_TRADES2,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );
*/
CLASS_EXPORT const I_CHAR *CMD_BPROC_PURCHASE = I_( "BPROC_Purchase" );
static CommandTraits cmdTrait_CMD_BPROC_PURCHASE  ( CMD_BPROC_PURCHASE  ,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_REDEMPTION = I_( "BPROC_Redemption" );
static CommandTraits cmdTrait_CMD_BPROC_REDEMPTION( CMD_BPROC_REDEMPTION,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_EXCHANGE = I_( "BPROC_Exchange" );
static CommandTraits cmdTrait_CMD_BPROC_EXCHANGE( CMD_BPROC_EXCHANGE,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_IDENT_ACC = I_( "BPROC_IDENT_ACC" );
static CommandTraits cmdTrait_CMD_BPROC_IDENT_ACC( CMD_BPROC_IDENT_ACC,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_MODALONLY );


CLASS_EXPORT const I_CHAR *CMD_BPROC_CONTRACTINFO = I_( "BPROC_CONTRACTINFO" );
static CommandTraits cmdTrait_CMD_BPROC_CONTRACTINFO( CMD_BPROC_CONTRACTINFO,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REG_PLAN_TRANSFER = I_( "BPROC_REG_PLAN_TRANSFER" );
static CommandTraits cmdTrait_CMD_BPROC_REG_PLAN_TRANSFER( CMD_BPROC_REG_PLAN_TRANSFER,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REG_PLAN_TRANSFER_SEARCH = I_( "BPROC_REG_PLAN_TRANSFER_SEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_REG_PLAN_TRANSFER_SEARCH( CMD_BPROC_REG_PLAN_TRANSFER_SEARCH,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_MINMAXINFO = I_( "BPROC_MINMAXINFO" );
static CommandTraits cmdTrait_CMD_BPROC_MINMAXINFO( CMD_BPROC_MINMAXINFO,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_TAXRATES = I_( "BPROC_TAXRATES" );
static CommandTraits cmdTrait_CMD_BPROC_TAXRATES( CMD_BPROC_TAXRATES,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_RESPINFO = I_( "BPROC_RESPINFO" );
static CommandTraits cmdTrait_CMD_BPROC_RESPINFO( CMD_BPROC_RESPINFO,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_RESPTRANSACTIONS = I_( "BPROC_RESPTRANSACTIONS" );
static CommandTraits cmdTrait_CMD_BPROC_RESPTRANSACTIONS( CMD_BPROC_RESPTRANSACTIONS,
                                                          BUSINESS_PROCESS_TYPE,
                                                          1,
                                                          1,
                                                          MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_ADVISORINFO = I_( "BPROC_SalesRepProcess" );
static CommandTraits cmdTrait_CMD_BPROC_ADVISORINFO( CMD_BPROC_ADVISORINFO,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_JBROKERLIST = I_( "BPROC_JBROKERLIST" );
static CommandTraits cmdTrait_CMD_BPROC_JBROKERLIST( CMD_BPROC_JBROKERLIST,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_JBRANCHLIST = I_( "BPROC_JBRANCHLIST" );
static CommandTraits cmdTrait_CMD_BPROC_JBRANCHLIST( CMD_BPROC_JBRANCHLIST,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_JFUNDLIST = I_( "BPROC_JFUNDLIST" );
static CommandTraits cmdTrait_CMD_BPROC_JFUNDLIST( CMD_BPROC_JFUNDLIST,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_JADVISORTRANS = I_( "BPROC_JADVISORTRANS" );
static CommandTraits cmdTrait_CMD_BPROC_JADVISORTRANS( CMD_BPROC_JADVISORTRANS,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_JADVISORSUMM = I_( "BPROC_JADVISORSUMM" );
static CommandTraits cmdTrait_CMD_BPROC_JADVISORSUMM( CMD_BPROC_JADVISORSUMM,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_JSHRSUMM = I_( "BPROC_JSHRSUMM" );
static CommandTraits cmdTrait_CMD_BPROC_JSHRSUMM( CMD_BPROC_JSHRSUMM,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_JFUNDINDIV = I_( "BPROC_JFUNDINDIV" );
static CommandTraits cmdTrait_CMD_BPROC_JFUNDINDIV( CMD_BPROC_JFUNDINDIV,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_HYPOTHETICALRED = I_( "BPROC_HypoRedemptionProcess" );
static CommandTraits cmdTrait_CMD_BPROC_HYPOTHETICALRED( CMD_BPROC_HYPOTHETICALRED,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_REDCODEBYTAXTYPE = I_( "BPROC_REDCODEBYTAXTYPE" );
static CommandTraits cmdTrait_CMD_BPROC_REDCODEBYTAXTYPE( CMD_BPROC_REDCODEBYTAXTYPE,
                                                          BUSINESS_PROCESS_TYPE,
                                                          1,
                                                          1,
                                                          MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_RESPBENREL = I_( "BPROC_RESPBENREL" );
static CommandTraits cmdTrait_CMD_BPROC_RESPBENREL( CMD_BPROC_RESPBENREL,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_VERIFICATIONCONF = I_( "BPROC_VERIFICATIONCONF" );
static CommandTraits cmdTrait_CMD_BPROC_VERIFICATIONCONF( CMD_BPROC_VERIFICATIONCONF,
                                                          BUSINESS_PROCESS_TYPE,
                                                          1,
                                                          1,
                                                          MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_MAINTENANCE = I_( "BPROC_MAINTENANCE" );
static CommandTraits cmdTrait_CMD_BPROC_MAINTENANCE( CMD_BPROC_MAINTENANCE,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_JENTITY = I_( "BPROC_JENTITY" );
static CommandTraits cmdTrait_CMD_BPROC_JENTITY( CMD_BPROC_JENTITY,
                                                 BUSINESS_PROCESS_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_JACCTMAIL = I_( "BPROC_AccountMailProcess" );
static CommandTraits cmdTrait_CMD_BPROC_JACCTMAIL( CMD_BPROC_JACCTMAIL,
                                                 BUSINESS_PROCESS_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_JACCTMAILPRD_OVERRIDE = I_( "BPROC_AccountMailProdProcess" );
static CommandTraits cmdTrait_CMD_BPROC_JACCTMAILPRD_OVERRIDE( CMD_BPROC_JACCTMAILPRD_OVERRIDE,
                                                 BUSINESS_PROCESS_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_JPENDING = I_( "BPROC_JPENDING" );
static CommandTraits cmdTrait_CMD_BPROC_JPENDING( CMD_BPROC_JPENDING,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_FUNDCLASS = I_( "BPROC_FUNDCLASS" );
static CommandTraits cmdTrait_CMD_BPROC_FUNDCLASS( CMD_BPROC_FUNDCLASS,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUNDGROUP = I_( "BPROC_FUNDGROUP" );
static CommandTraits cmdTrait_CMD_BPROC_FUNDGROUP( CMD_BPROC_FUNDGROUP,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SETDATASERVER = I_( "BPROC_SETDATASERVER" );
static CommandTraits cmdTrait_CMD_BPROC_SETDATASERVER( CMD_BPROC_SETDATASERVER,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ALLFUNDINFO = I_( "BPROC_ALLFUNDINFO" );
static CommandTraits cmdTrait_CMD_BPROC_ALLFUNDINFO( CMD_BPROC_ALLFUNDINFO,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUNDTOLIST = I_( "BPROC_FUNDTOLIST" );
static CommandTraits cmdTrait_CMD_BPROC_FUNDTOLIST( CMD_BPROC_FUNDTOLIST,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_AVAILABILITY = I_( "BPROC_AvailabilityProcess" );
static CommandTraits cmdTrait_CMD_BPROC_AVAILABILITY( CMD_BPROC_AVAILABILITY,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_APINASU = I_( "BPROC_NASUProcess" );
static CommandTraits cmdTrait_CMD_BPROC_APINASU( CMD_BPROC_APINASU,
                                                 BUSINESS_PROCESS_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNTHOLDINGSINQUIRY = I_( "BPROC_ACCOUNTHOLDINGSINQUIRY" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNTHOLDINGSINQUIRY( CMD_BPROC_ACCOUNTHOLDINGSINQUIRY,
                                                                BUSINESS_PROCESS_TYPE,
                                                                1,
                                                                1,
                                                                MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_SPLITCOMMISSION = I_( "BPROC_SplitCommissionProcess" );
static CommandTraits cmdTrait_CMD_BPROC_SPLITCOMMISSION( CMD_BPROC_SPLITCOMMISSION,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_FINANCIAL_INSTITUTION = I_( "BPROC_FINANCIAL_INSTITUTION" );
static CommandTraits cmdTrait_CMD_BPROC_FINANCIAL_INSTITUTION( CMD_BPROC_FINANCIAL_INSTITUTION,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FINANCIAL_INSTITUTION_SEARCH = I_( "BPROC_FINANCIAL_INSTITUTION_SEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_FINANCIAL_INSTITUTION_SEARCH( CMD_BPROC_FINANCIAL_INSTITUTION_SEARCH,
                                                                      BUSINESS_PROCESS_TYPE,
                                                                      1,
                                                                      1,
                                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRANSACTION_SUMMARY = I_( "BPROC_TRANSACTION_SUMMARY" );
static CommandTraits cmdTrait_CMD_BPROC_TRANSACTION_SUMMARY( CMD_BPROC_TRANSACTION_SUMMARY,
                                                             BUSINESS_PROCESS_TYPE,
                                                             1,
                                                             1,
                                                             MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNT_INQUIRY = I_( "BPROC_ACCOUNT_INQUIRY" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNT_INQUIRY( CMD_BPROC_ACCOUNT_INQUIRY,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MGMT_CO_REFRESH = I_( "BPROC_MgmtCoRefresh" );
static CommandTraits cmdTrait_CMD_BPROC_MGMT_CO_REFRESH( CMD_BPROC_MGMT_CO_REFRESH,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_ESOPINFO = I_( "BPROC_ESoPInfo" );
static CommandTraits cmdTrait_CMD_BPROC_ESOPINFO( CMD_BPROC_ESOPINFO,
                                                  BUSINESS_PROCESS_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_YTD_CONTRIBUTION = I_( "BPROC_YTD_CONTRIBUTION" );
static CommandTraits cmdTrait_CMD_BPROC_YTD_CONTRIBUTION( CMD_BPROC_YTD_CONTRIBUTION,
                                                          BUSINESS_PROCESS_TYPE,
                                                          1,
                                                          1,
                                                          MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MATCHTRANSFER = I_( "BPROC_MATCHTRANSFER" );
static CommandTraits cmdTrait_CMD_BPROC_MATCHTRANSFER( CMD_BPROC_MATCHTRANSFER,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_AS_PENSION_PLAN = I_( "BPROC_AS_PENSION_PLAN" );
static CommandTraits cmdTrait_CMD_BPROC_AS_PENSION_PLAN( CMD_BPROC_AS_PENSION_PLAN,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_SPLITCOMM = I_( "BPROC_ACCT_SPLITCOMM" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_SPLITCOMM( CMD_BPROC_ACCT_SPLITCOMM,
                                                        BUSINESS_PROCESS_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ESOP_HISTORICAL = I_( "BPROC_ESoPHistorical" );
static CommandTraits cmdTrait_CMD_BPROC_ESOP_HISTORICAL( CMD_BPROC_ESOP_HISTORICAL,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNT_SEARCH = I_( "BPROC_AccountSearch" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNT_SEARCH( CMD_BPROC_ACCOUNT_SEARCH,
                                                        BUSINESS_PROCESS_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FEE_PARAMETER = I_( "BPROC_FeeParameter" );
static CommandTraits cmdTrait_CMD_BPROC_FEE_PARAMETER( CMD_BPROC_FEE_PARAMETER,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_USER_ACCESS = I_( "BPROC_USER_ACCESS" );
static CommandTraits cmdTrait_CMD_BPROC_USER_ACCESS( CMD_BPROC_USER_ACCESS,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_CASH_DIVIDEND = I_( "BPROC_CASH_DIVIDEND" );
static CommandTraits cmdTrait_CMD_BPROC_CASH_DIVIDEND( CMD_BPROC_CASH_DIVIDEND,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNTREVIEW = I_( "BPROC_ACCOUNTREVIEW" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNTREVIEW( CMD_BPROC_ACCOUNTREVIEW,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_PENSION_INFO = I_( "BPROC_PENSION_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_PENSION_INFO( CMD_BPROC_PENSION_INFO,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ESTATEMENT = I_( "BPROC_ESTATEMENT" );
static CommandTraits cmdTrait_CMD_BPROC_ESTATEMENT( CMD_BPROC_ESTATEMENT,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_HYPO_RED = I_( "BPROC_HYPO_RED" );
static CommandTraits cmdTrait_CMD_BPROC_HYPO_RED( CMD_BPROC_HYPO_RED,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FOREIGN_CONTENT_WORKSHEET = I_( "BPROC_FOREIGN_CONTENT_WORKSHEET" );
static CommandTraits cmdTrait_CMD_BPROC_FOREIGN_CONTENT_WORKSHEET( CMD_BPROC_FOREIGN_CONTENT_WORKSHEET,
                                                                   BUSINESS_PROCESS_TYPE,
                                                                   1,
                                                                   1,
                                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_AMSACCTLVL = I_( "BPROC_AMSACCTLVL" );
static CommandTraits cmdTrait_CMD_BPROC_AMSACCTLVL( CMD_BPROC_AMSACCTLVL,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_AMSBROKER = I_( "BPROC_AMSBrokerProcess" );
static CommandTraits cmdTrait_CMD_BPROC_AMSBROKER( CMD_BPROC_AMSBROKER,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MKT_INDEX_MASTER = I_( "BPROC_MKTINDEXMASTER" );
static CommandTraits cmdTrait_CMD_BPROC_MKT_INDEXMASTER( CMD_BPROC_MKT_INDEX_MASTER,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MKT_INDEX_VALUES = I_( "BPROC_MKTINDEXVALUES" );
static CommandTraits cmdTrait_CMD_BPROC_MKT_INDEXVALUES( CMD_BPROC_MKT_INDEX_VALUES,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES = I_( "BPROC_ACCT_LVL_CUT_OFF_TIMES" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES( CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MSG = I_( "BPROC_MSG" );
static CommandTraits cmdTrait_CMD_BPROC_MSG( CMD_BPROC_MSG,
                                             BUSINESS_PROCESS_TYPE,
                                             1,
                                             1,
                                             MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MSG_SEARCH = I_( "BPROC_MSGSEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_MSG_SEARCH( CMD_BPROC_MSG_SEARCH,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MSG_DETAIL = I_( "BPROC_MSGDETAIL" );
static CommandTraits cmdTrait_CMD_BPROC_MSG_DETAIL( CMD_BPROC_MSG_DETAIL,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FILE_INQUIRY = I_( "BPROC_FILEINQUIRY" );
static CommandTraits cmdTrait_CMD_BPROC_FILE_INQUIRY( CMD_BPROC_FILE_INQUIRY,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FILE_SEARCH = I_( "BPROC_FILESEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_FILE_SEARCH( CMD_BPROC_FILE_SEARCH,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_USERDEFMAT = I_( "BPROC_USERDEFMAT" );
static CommandTraits cmdTrait_CMD_BPROC_USERDEFMAT( CMD_BPROC_USERDEFMAT,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ENTITY_ADDRESS_SEARCH = I_( "BPROC_ENTITY_ADDRESS_EARCH" );
static CommandTraits cmdTrait_CMD_BPROC_ENTITY_ADDRESS_SEARCH( CMD_BPROC_ENTITY_ADDRESS_SEARCH,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SETTLEMENT_INSTRUCTIONS_SYSLVL = I_( "BPROC_SETTLEMENT_INSTRUCTIONS_SYSLVL" );
static CommandTraits cmdTrait_CMD_BPROC_SETTLEMENT_INSTRUCTIONS_SYSLVL( CMD_BPROC_SETTLEMENT_INSTRUCTIONS_SYSLVL,
                                                                        BUSINESS_PROCESS_TYPE,
                                                                        1,
                                                                        1,
                                                                        MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SETTLEMENT_INSTRUCTIONS_ACCTLVL = I_( "BPROC_SETTLEMENT_INSTRUCTIONS_ACCTLVL" );
static CommandTraits cmdTrait_CMD_BPROC_SETTLEMENT_INSTRUCTIONS_ACCTLVL( CMD_BPROC_SETTLEMENT_INSTRUCTIONS_ACCTLVL,
                                                                         BUSINESS_PROCESS_TYPE,
                                                                         1,
                                                                         1,
                                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SETTLEMENT_LOCATION_TRADE = I_( "BPROC_SETTLEMENT_LOCATION_TRADE" );
static CommandTraits cmdTrait_CMD_BPROC_SETTLEMENT_LOCATION_TRADE( CMD_BPROC_SETTLEMENT_LOCATION_TRADE,
                                                                   BUSINESS_PROCESS_TYPE,
                                                                   1,
                                                                   1,
                                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MANUAL_DIVIDEND = I_( "BPROC_MANUALDIVIDEND" );
static CommandTraits cmdTrait_CMD_BPROC_MANUAL_DIVIDEND( CMD_BPROC_MANUAL_DIVIDEND,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_AMS_GLOBAL = I_( "BPROC_AMSGLOBAL" );
static CommandTraits cmdTrait_CMD_BPROC_AMSGLOBAL( CMD_BPROC_AMS_GLOBAL,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REPORT = I_( "BPROC_REPORT" );
static CommandTraits cmdTrait_CMD_BPROC_REPORT( CMD_BPROC_REPORT,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REPORT_STATUS = I_( "BPROC_REPORT_STATUS" );
static CommandTraits cmdTrait_CMD_BPROC_REPORT_STATUS( CMD_BPROC_REPORT_STATUS,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REPORT_VIEW = I_( "BPROC_REPORT_VIEW" );
static CommandTraits cmdTrait_CMD_BPROC_REPORT_VIEW( CMD_BPROC_REPORT_VIEW,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_PRINTER_LIST = I_( "BPROC_PRINTER_LIST" );
static CommandTraits cmdTrait_CMD_BPROC_PRINTER_LIST( CMD_BPROC_PRINTER_LIST,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FTP_LOGON = I_( "BPROC_FTP_LOGON" );
static CommandTraits cmdTrait_CMD_BPROC_FTP_LOGON( CMD_BPROC_FTP_LOGON,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_PROTECTED_FUND = I_( "BPROC_PROTECTED_FUND" );
static CommandTraits cmdTrait_CMD_BPROC_PROTECTED_FUND( CMD_BPROC_PROTECTED_FUND,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );
CLASS_EXPORT const I_CHAR *CMD_BPROC_SHR_FAMILY = I_( "BPROC_SHR_FAMILY" );
static CommandTraits cmdTrait_CMD_BPROC_SHR_FAMILY( CMD_BPROC_SHR_FAMILY,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FEE_PARAMETER_SYSTEM = I_( "BPROC_FeeParameter_System" );
static CommandTraits cmdTrait_CMD_BPROC_FEE_PARAMETER_SYSTEM( CMD_BPROC_FEE_PARAMETER_SYSTEM,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNT_CONTRACT = I_( "CMD_BPROC_ACCOUNT_CONTRACT" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNT_CONTRACT( CMD_BPROC_ACCOUNT_CONTRACT,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_CATEGORY = I_( "BPROC_ACCT_CATEGORY" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_CATEGORY( CMD_BPROC_ACCT_CATEGORY,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REG_DOCUMENT_LIST = I_( "BPROC_REG_DOCUMENT_LIST" );
static CommandTraits cmdTrait_CMD_BPROC_REG_DOCUMENT_LIST( CMD_BPROC_REG_DOCUMENT_LIST,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRADE_SETTLEMENT_LOCATIONS = I_( "BPROC_TRADE_SETTLEMENT_LOCATIONS" );
static CommandTraits cmdTrait_CMD_BPROC_TRADE_SETTLEMENT_LOCATIONS( CMD_BPROC_TRADE_SETTLEMENT_LOCATIONS,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_BENEF_ALLOCATION_LIST = I_( "BPROC_RESP_BENEF_ALLOCATION_LIST" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_BENEF_ALLOCATION_LIST( CMD_BPROC_RESP_BENEF_ALLOCATION_LIST,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_TRANSFER = I_( "BPROC_RESP_TRANSFER" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_TRANSFER( CMD_BPROC_RESP_TRANSFER,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_KYC_BROKER = I_( "BPROC_KYC_BROKER" );
static CommandTraits cmdTrait_CMD_BPROC_KYC_BROKER( CMD_BPROC_KYC_BROKER,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESET_INSTR = I_( "CMD_BPROC_RESET_INSTR" );
static CommandTraits cmdTrait_CMD_BPROC_RESET_INSTR( CMD_BPROC_RESET_INSTR,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );
CLASS_EXPORT const I_CHAR *CMD_BPROC_HISTORICAL_INFO = I_( "CMD_BPROC_HISTORICAL_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_HISTORICAL_INFO( CMD_BPROC_HISTORICAL_INFO,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_HISTORICAL_INFO_SRCH = I_( "CMD_BPROC_HISTORICAL_INFO_SRCH" );
static CommandTraits cmdTrait_CMD_BPROC_HISTORICAL_INFO_SRCH( CMD_BPROC_HISTORICAL_INFO_SRCH,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRADE_SEARCH = I_( "CMD_BPROC_TRADE_SEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_TRADE_SEARCH( CMD_BPROC_TRADE_SEARCH,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRADE_VERIFICATION_SEARCH = I_( "CMD_BPROC_TRADE_VERIFICATION_SEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_TRADE_VERIFICATION_SEARCH( CMD_BPROC_TRADE_VERIFICATION_SEARCH,
                                                                   BUSINESS_PROCESS_TYPE,
                                                                   1,
                                                                   1,
                                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_BROKER_ADDRESS = I_( "CMD_BPROC_BROKER_ADDRESS" );
static CommandTraits cmdTrait_CMD_BPROC_BROKER_ADDRESS( CMD_BPROC_BROKER_ADDRESS,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_MODALONLY );


CLASS_EXPORT const I_CHAR *CMD_BPROC_FROM_TO_ALLOCATION = I_( "CMD_BPROC_FROM_TO_ALLOCATION" );
static CommandTraits cmdTrait_CMD_BPROC_FROM_TO_ALLOCATION( CMD_BPROC_FROM_TO_ALLOCATION,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FEATURES_SEARCH = I_( "CMD_BPROC_FEATURES_SEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_FEATURES_SEARCH( CMD_BPROC_FEATURES_SEARCH,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_GUARANTEEINFO = I_( "BPROC_GUARANTEEINFO" );
static CommandTraits cmdTrait_CMD_BPROC_GUARANTEEINFO( CMD_BPROC_GUARANTEEINFO,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_PAY_TO_ENTITY = I_( "CMD_BPROC_PAY_TO_ENTITY" );
static CommandTraits cmdTrait_CMD_BPROC_PAY_TO_ENTITY( CMD_BPROC_PAY_TO_ENTITY,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_PAYMENT_INSTRUCTIONS = I_( "CMD_BPROC_PAYMENT_INSTRUCTIONS" );
static CommandTraits cmdTrait_CMD_BPROC_PAYMENT_INSTRUCTIONS( CMD_BPROC_PAYMENT_INSTRUCTIONS,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_AMS_LMT_OVERRIDE = I_( "BPROC_AMSLMTOVERRIDE" );
static CommandTraits cmdTrait_CMD_BPROC_AMSLMTOVERRIDE( CMD_BPROC_AMS_LMT_OVERRIDE,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_AMS_HYPO_ALLOC = I_( "BPROC_AMSHYPOALLOC" );
static CommandTraits cmdTrait_CMD_BPROC_AMSHYPOALLOC( CMD_BPROC_AMS_HYPO_ALLOC,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_AMS_DELTA_ALLOC = I_( "BPROC_AMSDELTAALLOC" );
static CommandTraits cmdTrait_CMD_BPROC_AMSDELTAALLOC( CMD_BPROC_AMS_DELTA_ALLOC,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MULTI_FUND_ALLOCATION = I_( "BPROC_MULTIFUNDALLOCATION" );
static CommandTraits cmdTrait_CMD_BPROC_MULTI_FUND_ALLOCATION(CMD_BPROC_MULTI_FUND_ALLOCATION,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SIMPLE_ALLOCATION = I_( "BPROC_SIMPLEALLOCATION" );
static CommandTraits cmdTrait_CMD_BPROC_SIMPLE_ALLOCATION(CMD_BPROC_SIMPLE_ALLOCATION,
                                                    BUSINESS_PROCESS_TYPE,
                                                    1,
                                                    1,
                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRADES_TAXRATE = I_( "BPROC_TradeTaxRateProcess");
static CommandTraits cmdTrait_CMD_BPROC_TRADES_TAXRATE( CMD_BPROC_TRADES_TAXRATE,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_DIRECT_TRADING = I_( "BPROC_DirectTradingProcess");
static CommandTraits cmdTrait_CMD_BPROC_DIRECT_TRADING( CMD_BPROC_DIRECT_TRADING,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRANSITS = I_( "BPROC_TRANSITS" );
static CommandTraits cmdTrait_CMD_BPROC_TRANSITS( CMD_BPROC_TRANSITS,
                                                  BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FIRE_FIGHTER_LOGON = I_( "BPROC_FIRE_FIGHTER_LOGON" );
static CommandTraits cmdTrait_CMD_BPROC_FIRE_FIGHTER_LOGON( CMD_BPROC_FIRE_FIGHTER_LOGON,
                                                            BUSINESS_PROCESS_TYPE,
                                                            1,
                                                            1,
                                                            MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_DAILY_TRANSACTION_FEES = I_( "BPROC_DAILY_TRANSACTION_FEES" );
static CommandTraits cmdTrait_CMD_BPROC_DAILY_TRANSACTION_FEES( CMD_BPROC_DAILY_TRANSACTION_FEES,
                                                                BUSINESS_PROCESS_TYPE,
                                                                1,
                                                                1,
                                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_AWD_COMMENT = I_( "BPROC_AWD_COMMENT" );
static CommandTraits cmdTrait_CMD_BPROC_AWD_COMMENT( CMD_BPROC_AWD_COMMENT,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_INVENTORY_SUMMARY  = I_( "BPROC_INVENTORY_SUMMARY" );
static CommandTraits cmdTrait_CMD_BPROC_INVENTORY_SUMMARY( CMD_BPROC_INVENTORY_SUMMARY,
                                                                BUSINESS_PROCESS_TYPE,
                                                                1,
                                                                1,
                                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SHR_FUND_SPONSOR_AGREEMENT = I_( "BPROC_SHR_FUND_SPONSOR_AGREEMENT" );
static CommandTraits cmdTrait_CMD_BPROC_SHR_FUND_SPONSOR_AGREEMENT( CMD_BPROC_SHR_FUND_SPONSOR_AGREEMENT,
                                                                BUSINESS_PROCESS_TYPE,
                                                                1,
                                                                1,
                                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TAX_EXEMPT_AUTHORIZATION = I_( "BPROC_TAX_EXEMPT_AUTHORIZATION" );
static CommandTraits cmdTrait_CMD_BPROC_TAX_EXEMPT_AUTHORIZATION( CMD_BPROC_TAX_EXEMPT_AUTHORIZATION,
                                                                BUSINESS_PROCESS_TYPE,
                                                                1,
                                                                1,
                                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FEE_MODEL = I_( "BPROC_FeeModel" );
static CommandTraits cmdTrait_CMD_BPROC_FEE_MODEL( CMD_BPROC_FEE_MODEL,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FEE_MODEL_COPY_TO = I_( "BPROC_FeeModel_COPY_TO" );
static CommandTraits cmdTrait_CMD_BPROC_FEE_MODEL_COPY_TO( CMD_BPROC_FEE_MODEL_COPY_TO,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_HOLDING_COMP = I_( "BPROC_HoldingComp" );
static CommandTraits cmdTrait_CMD_BPROC_HOLDING_COMP( CMD_BPROC_HOLDING_COMP,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FEE_PARAM_MAINT = I_( "BPROC_FeeParamMaint" );
static CommandTraits cmdTrait_CMD_BPROC_FEE_PARAM_MAINT( CMD_BPROC_FEE_PARAM_MAINT,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );
CLASS_EXPORT const I_CHAR *CMD_BPROC_FUNDSPONSOR_FEE_MODEL = I_( "BPROC_FundSponsor_FeeModel" );
static CommandTraits cmdTrait_CMD_BPROC_FUNDSPONSOR_FEE_MODEL( CMD_BPROC_FUNDSPONSOR_FEE_MODEL,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SHR_FUND_BROKER = I_( "BPROC_SHR_FUND_BROKER" );
static CommandTraits cmdTrait_CMD_BPROC_SHR_FUND_BROKER( CMD_BPROC_SHR_FUND_BROKER,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUND_BROKER = I_( "BPROC_FundBroker" );
static CommandTraits cmdTrait_CMD_BPROC_FUND_BROKER( CMD_BPROC_FUND_BROKER,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_BROKER_REMARK  = I_( "BPROC_BrokerRemark" );
static CommandTraits cmdTrait_CMD_BPROC_BROKER_REMARK( CMD_BPROC_BROKER_REMARK,
                                                                BUSINESS_PROCESS_TYPE,
                                                                1,
                                                                1,
                                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_AGGREGATED_ORDER  = I_( "BPROC_AggregatedOrder" );
static CommandTraits cmdTrait_CMD_BPROC_AGGREGATED_ORDER( CMD_BPROC_AGGREGATED_ORDER,
                                                                BUSINESS_PROCESS_TYPE,
                                                                1,
                                                                1,
                                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_BPAGGREGATED_ORDER  = I_( "BPROC_BPAggregatedOrderProcess" );
static CommandTraits cmdTrait_CMD_BPROC_BPAGGREGATED_ORDER( CMD_BPROC_BPAGGREGATED_ORDER,
                                                                BUSINESS_PROCESS_TYPE,
                                                                1,
                                                                1,
                                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUND_BROKER_SETTLEMENT_INSTR = I_( "BPROC_FUND_BROKER_SETTLEMENT_INSTR" );
static CommandTraits cmdTrait_CMD_BPROC_FUND_BROKER_SETTLEMENT_INSTR( CMD_BPROC_FUND_BROKER_SETTLEMENT_INSTR,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_INVENTORY_DETAIL_DEDUCTION = I_( "BPROC_INVENTORY_DETAIL_DEDUCTION" );
static CommandTraits cmdTrait_CMD_BPROC_INVENTORY_DETAIL_DEDUCTION( CMD_BPROC_INVENTORY_DETAIL_DEDUCTION,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRANS_CANCEL = I_( "BPROC_TRANS_CANCEL" );
static CommandTraits cmdTrait_CMD_BPROC_TRANS_CANCEL( CMD_BPROC_TRANS_CANCEL,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_DILUTION = I_( "BPROC_DILUTION" );
static CommandTraits cmdTrait_CMD_BPROC_DILUTION( CMD_BPROC_DILUTION,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ENTITY_ALONE_PROCESS = I_( "BPROC_ENTITY_ALONE" );
static CommandTraits cmdTrait_CMD_BPROC_ENTITY_ALONE( CMD_BPROC_ENTITY_ALONE_PROCESS,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_CONFIRM_REPRINT = I_( "BPROC_CONFIRM_REPRINT" );
static CommandTraits cmdTrait_CMD_BPROC_CONFIRM_REPRINT( CMD_BPROC_CONFIRM_REPRINT,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_OPC_CONFIRM_REPRINT = I_( "BPROC_OPC_CONFIRM_REPRINT" );
static CommandTraits cmdTrait_CMD_BPROC_OPC_CONFIRM_REPRINT( CMD_BPROC_OPC_CONFIRM_REPRINT,
                                              BUSINESS_PROCESS_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_REBOOK = I_( "BPROC_REBOOK" );
static CommandTraits cmdTrait_CMD_BPROC_REBOOK( CMD_BPROC_REBOOK,
                                              BUSINESS_PROCESS_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REFUND = I_( "BPROC_REFUND" );
static CommandTraits cmdTrait_CMD_BPROC_REFUND( CMD_BPROC_REFUND,
                                              BUSINESS_PROCESS_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REBOOK_PARAM = I_( "BPROC_REBOOK_PARAM" );
static CommandTraits cmdTrait_CMD_BPROC_REBOOK_PARAM( CMD_BPROC_REBOOK_PARAM,
                                              BUSINESS_PROCESS_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRANS_LINK = I_( "BPROC_TRANS_LINK" );
static CommandTraits cmdTrait_CMD_BPROC_TRANS_LINK( CMD_BPROC_TRANS_LINK,
                                              BUSINESS_PROCESS_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_CANCELLATION_INSTR = I_( "BPROC_CANCELLATION_INSTR" );
static CommandTraits cmdTrait_CMD_BPROC_CANCELLATION_INSTR( CMD_BPROC_CANCELLATION_INSTR,
                                              BUSINESS_PROCESS_TYPE,
                                              1,
                                              1,
                                              MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SAVINGS_DIRECTIVE = I_( "BPROC_CSAVINGS_DIRECTIVE" );
static CommandTraits cmdTrait_CMD_BPROC_SAVINGS_DIRECTIVE(  CMD_BPROC_SAVINGS_DIRECTIVE,
                                                            BUSINESS_PROCESS_TYPE,
                                                            1,
                                                            1,
                                                            MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_BROWSER_LAUNCH = I_( "BPROC_BROWSER_LAUNCH" );
static CommandTraits cmdTrait_CMD_BPROC_BROWSER_LAUNCH( CMD_BPROC_BROWSER_LAUNCH,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRADE_PAYMENT_INSTRUCTIONS = I_( "BPROC_TRADE_PAYMENT_INSTRUCTIONS" );
static CommandTraits cmdTrait_CMD_BPROC_TRADE_PAYMENT_INSTRUCTIONS( CMD_BPROC_TRADE_PAYMENT_INSTRUCTIONS,
                                                                    BUSINESS_PROCESS_TYPE,
                                                                    1,
                                                                    1,
                                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRADE_AUTHORIZATION = I_( "BPROC_TRADE_AUTHORIZATION" );
static CommandTraits cmdTrait_CMD_BPROC_TRADE_AUTHORIZATION( CMD_BPROC_TRADE_AUTHORIZATION,
                                                                    BUSINESS_PROCESS_TYPE,
                                                                    1,
                                                                    1,
                                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MATSWP_INSTRUCTIONS = I_( "BPROC_MATSWP_INSTRUCTIONS" );
static CommandTraits cmdTrait_CMD_BPROC_MATSWP_INSTRUCTIONS( CMD_BPROC_MATSWP_INSTRUCTIONS,
                                                                    BUSINESS_PROCESS_TYPE,
                                                                    1,
                                                                    1,
                                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MATSWP_INSTR = I_( "BPROC_MATSWP_INSTR" );
static CommandTraits cmdTrait_CMD_BPROC_MATSWP_INSTR( CMD_BPROC_MATSWP_INSTR,
                                                                    BUSINESS_PROCESS_TYPE,
                                                                    1,
                                                                    1,
                                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_MATSWP_INSTR_DETLS = I_( "BPROC_MATSWP_INSTR_DETLS" );
static CommandTraits cmdTrait_CMD_BPROC_MATSWP_INSTR_DETLS( CMD_BPROC_MATSWP_INSTR_DETLS,
                                                                    BUSINESS_PROCESS_TYPE,
                                                                    1,
                                                                    1,
                                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_CLONE_ACCOUNT = I_( "BPROC_CLONE_ACCOUNT" );
static CommandTraits cmdTrait_CMD_BPROC_CLONE_ACCOUNT( CMD_BPROC_CLONE_ACCOUNT,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_REGIS_MAINT = I_( "BPROC_ACCT_REGIS_MAINT" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_REGIS_MAINT( CMD_BPROC_ACCT_REGIS_MAINT,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_MODALONLY);

CLASS_EXPORT const I_CHAR *CMD_BPROC_ENT_REG_MAINT = I_( "BPROC_ENT_REG_MAINT" );
static CommandTraits cmdTrait_CMD_BPROC_ENT_REG_MAINT( CMD_BPROC_ENT_REG_MAINT,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_MODALONLY);

CLASS_EXPORT const I_CHAR *CMD_BPROC_ALERT_MESSAGES = I_( "BPROC_ALERT_MESSAGES" );
static CommandTraits cmdTrait_CMD_BPROC_ALERT_MESSAGES( CMD_BPROC_ALERT_MESSAGES,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_MODALONLY);

CLASS_EXPORT const I_CHAR *CMD_BPROC_PRICE_ADDITIONAL = I_( "BPROC_PRICE_ADDITIONAL" );
static CommandTraits cmdTrait_CMD_BPROC_PRICE_ADDITIONAL(CMD_BPROC_PRICE_ADDITIONAL,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_MODALONLY);

//web pages
CLASS_EXPORT const I_CHAR *CMD_BPROC_GUARANTEEINFO_BROWSER = I_( "BPROC_GUARANTEEINFO_BROWSER" );
static CommandTraits cmdTrait_CMD_BPROC_GUARANTEEINFO_BROWSER( CMD_BPROC_GUARANTEEINFO_BROWSER,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with GuaranteeInformation
                                                               680 + 0 ,
                                                               725 + 0 );


CLASS_EXPORT const I_CHAR *CMD_BPROC_CLONE_ACCOUNT_BROWSER = I_( "BPROC_CLONE_ACCOUNT_BROWSER" );
static CommandTraits cmdTrait_CMD_BPROC_CLONE_ACCOUNT_BROWSER( CMD_BPROC_CLONE_ACCOUNT_BROWSER,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with CloneAccount
                                                               330 + 0 ,
                                                               670 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SHARE_LOT_BROWSER = I_( "BPROC_SHARE_LOT_BROWSER" );
static CommandTraits cmdTrait_CMD_BPROC_SHARE_LOT_BROWSER( CMD_BPROC_SHARE_LOT_BROWSER,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with SharelotSummary
                                                               680 + 0 ,
                                                               715 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_VALUATION_DETAILS_BROWSER = I_( "BPROC_VALUATION_DETAILS_BROWSER" );
static CommandTraits cmdTrait_CMD_BPROC_VALUATION_DETAILS_BROWSER( CMD_BPROC_VALUATION_DETAILS_BROWSER,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with ClassSetup_ValuationBasic
                                                               725 + 0 ,
                                                               715 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ADDRESS_LOOKUP_BROWSER = I_( "BPROC_ADDRESS_LOOKUP_BROWSER" );
static CommandTraits cmdTrait_CMD_BPROC_ADDRESS_LOOKUP_BROWSER( CMD_BPROC_ADDRESS_LOOKUP_BROWSER,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"),
                                                               470 + 0 ,
                                                               625 + 0 
                                                               );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TAX_JURIS_HISTORY = I_( "BPROC_TAX_JURIS_HISTORY" );
static CommandTraits cmdTrait_CMD_BPROC_TAX_JURIS_HISTORY( CMD_BPROC_TAX_JURIS_HISTORY,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with EntTaxHist
                                                               500 + 0 ,
                                                               730 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_ACCOUNT_TERMINATION = I_( "BPROC_RESP_ACCOUNT_TERMINATION" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_ACCOUNT_TERMINATION( CMD_BPROC_RESP_ACCOUNT_TERMINATION,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with RESPAcctTermInfo
                                                               400 + 0 ,
                                                               725 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ZERO_GRANT_REPAYMENT = I_( "BPROC_ZERO_GRANT_REPAYMENT" );
static CommandTraits cmdTrait_CMD_BPROC_ZERO_GRANT_REPAYMENT( CMD_BPROC_ZERO_GRANT_REPAYMENT,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with RESPZeroRpymt
                                                               375 + 0 ,
                                                               600 + 0 );//DesktopWeb conversion

CLASS_EXPORT const I_CHAR *CMD_BPROC_INTERFACE_FILE = I_( "BPROC_INTERFACE_FILE" );
static CommandTraits cmdTrait_CMD_BPROC_INTERFACE_FILE( CMD_BPROC_INTERFACE_FILE,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with RESPInterfaceFile
                                                               485 + 0 ,        // 485 + 96, 81 added for adjustment 
                                                               750 + 0 );  // 42 added for adjustment 

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_ALLOC_HISTROY = I_( "BPROC_RESP_ALLOC_HISTROY" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_ALLOC_HISTROY( CMD_BPROC_RESP_ALLOC_HISTROY,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with BeneAllocHist
                                                               250 + 0 ,
                                                               600 + 0 );//DesktopWeb conversion

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_ACCOUNT_INFO = I_( "BPROC_RESP_ACCOUNT_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_ACCOUNT_INFO( CMD_BPROC_RESP_ACCOUNT_INFO,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with RESPAccountInfo
                                                               490 + 0 ,
                                                               800 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_NOTIONAL_INFO = I_( "BPROC_RESP_NOTIONAL_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_NOTIONAL_INFO( CMD_BPROC_RESP_NOTIONAL_INFO,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with RESPNotional
                                                               525 + 0 ,
                                                               700 + 0 );//DesktopWeb conversion

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_GRANTS = I_( "BPROC_RESP_GRANTS" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_GRANTS( CMD_BPROC_RESP_GRANTS,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with RESPGrantInfo
                                                               670 + 0 ,
                                                               680 + 0 );//DesktopWeb conversion

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_GRANTS2 = I_( "BPROC_RESP_GRANTS2" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_GRANTS2( CMD_BPROC_RESP_GRANTS2,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with RESPGrantInfo2
                                                               670 + 0 ,
                                                               680 + 0 );//DesktopWeb conversion

CLASS_EXPORT const I_CHAR *CMD_BPROC_PAYMENT_SEARCH = I_( "BPROC_PAYMENT_SEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_PAYMENT_SEARCH( CMD_BPROC_PAYMENT_SEARCH,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), 
												   610 + 0 ,
												   720 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRANS_PAYMENT_SEARCH = I_( "BPROC_TRANS_PAYMENT_SEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_TRANS_PAYMENT_SEARCH( CMD_BPROC_TRANS_PAYMENT_SEARCH,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("PaymentSearch_MainScreen"));

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUND_CLASS_LIMITATION = I_( "BPROC_FUND_CLASS_LIMITATION" );
static CommandTraits cmdTrait_CMD_BPROC_FUND_CLASS_LIMITATION( CMD_BPROC_FUND_CLASS_LIMITATION,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with OvrdLimit
                                                   600 + 0 ,
                                                   740 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REGULATORY_STANDARDS = I_( "BPROC_REGULATORY_STANDARDS" );
static CommandTraits cmdTrait_CMD_BPROC_REGULATORY_STANDARDS( CMD_BPROC_REGULATORY_STANDARDS,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with RegStd
                                                   685 + 0 ,            // 81 added for adjustment 
                                                   700 + 0 );	         // 42 added for adjustment 

CLASS_EXPORT const I_CHAR *CMD_BPROC_REGULATORY_DOCUMENTS = I_( "BPROC_REGULATORY_DOCUMENTS" );
static CommandTraits cmdTrait_CMD_BPROC_REGULATORY_DOCUMENTS( CMD_BPROC_REGULATORY_DOCUMENTS,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with RegDoc
                                                   240 + 0 ,
                                                   750 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SMART_FORM = I_( "BPROC_SMART_FORM" );
static CommandTraits cmdTrait_CMD_BPROC_SMART_FORM( CMD_BPROC_SMART_FORM,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("LoadSmartForm"));

CLASS_EXPORT const I_CHAR *CMD_BPROC_GLOBAL_SEARCH = I_( "BPROC_GLOBAL_SEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_GLOBAL_SEARCH( CMD_BPROC_GLOBAL_SEARCH,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with GlobalSearch
                                                   400 + 0 ,
                                                   650 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUND_MASTER = I_( "BPROC_FUND_MASTER" );
static CommandTraits cmdTrait_CMD_BPROC_FUND_MASTER( CMD_BPROC_FUND_MASTER,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("FundMaster_Main")); // need to confrim this

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUND_DETAIL = I_( "BPROC_FUND_DETAIL" );
static CommandTraits cmdTrait_CMD_BPROC_FUND_DETAIL( CMD_BPROC_FUND_DETAIL,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("FundDetail_Main")); // need to confrim this

CLASS_EXPORT const I_CHAR *CMD_BPROC_PAYMENT_BATCH = I_( "BPROC_PAYMENT_BATCH" );
static CommandTraits cmdTrait_CMD_BPROC_PAYMENT_BATCH( CMD_BPROC_PAYMENT_BATCH,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                    555 + 0 ,
                                                    720 + 0 
                                                    );

CLASS_EXPORT const I_CHAR *CMD_BPROC_HISTORICAL_PAYMENTS = I_( "BPROC_HISTORICAL_PAYMENTS" );
static CommandTraits cmdTrait_CMD_BPROC_HISTORICAL_PAYMENTS( CMD_BPROC_HISTORICAL_PAYMENTS,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("PaymentSearch_Historical"));

// ++PMI
CLASS_EXPORT const I_CHAR *CMD_BPROC_MANAGEMENT_FEE_REBATE = I_( "BPROC_MANAGEMENT_FEE_REBATE" );
static CommandTraits cmdTrait_CMD_BPROC_MANAGEMENT_FEE_REBATE( CMD_BPROC_MANAGEMENT_FEE_REBATE,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("ManagementFeeRebate_Main"));

CLASS_EXPORT const I_CHAR *CMD_BPROC_MANAGEMENT_FEE = I_( "BPROC_MANAGEMENT_FEE" );
static CommandTraits cmdTrait_CMD_BPROC_MANAGEMENT_FEE( CMD_BPROC_MANAGEMENT_FEE,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("ManagementFee_Main"));

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNT_BALANCE_OVERRIDE = I_( "BPROC_ACCOUNT_BALANCE_OVERRIDE" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNT_BALANCE_OVERRIDE( CMD_BPROC_ACCOUNT_BALANCE_OVERRIDE,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with AcctBalOvrd
                                                   300 + 0 ,   // 300 + 80, 80 added for adjustment
                                                   600 + 0 );  // 600 + 40, 40 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_DILUTION_CALCULATOR = I_( "BPROC_DILUTION_CALCULATOR" );
static CommandTraits cmdTrait_CMD_BPROC_DILUTION_CALCULATOR( CMD_BPROC_DILUTION_CALCULATOR,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with DilutionCalculator
                                                   455 + 0 ,   // 455 + 80, 80 added for adjustment
                                                   580 + 0);	// 580 + 40, 40 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_MANAGEMENT_FEE_REBATE_DETAILS = I_( "BPROC_MANAGEMENT_FEE_REBATE_DETAILS" );
static CommandTraits cmdTrait_CMD_BPROC_MANAGEMENT_FEE_REBATE_DETAILS( CMD_BPROC_MANAGEMENT_FEE_REBATE_DETAILS,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("ManagementFeeRebate_Details"));

CLASS_EXPORT const I_CHAR *CMD_BPROC_MANAGEMENT_FEE_ID = I_( "BPROC_MANAGEMENT_FEE_ID" );
static CommandTraits cmdTrait_CMD_BPROC_MANAGEMENT_FEE_ID( CMD_BPROC_MANAGEMENT_FEE_ID,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("ManagementFee_FeeIDMain"));
                                                   
// --PMI
CLASS_EXPORT const I_CHAR *CMD_BPROC_AMS_ASSET_INFO = I_( "BPROC_AMS_ASSET_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_AMS_ASSET_INFO( CMD_BPROC_AMS_ASSET_INFO,
                                                        BUSINESS_PROCESS_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH,
                                                        I_("DisplayScreen"), // mapping with AMSAssetInfo
                                                        250 + 0 ,
                                                        600 + 0 );//DesktopWeb conversion

CLASS_EXPORT const I_CHAR *CMD_BPROC_DOT_AND_ADDENDUM= I_( "CMD_BPROC_DOT_AND_ADDENDUM" );
static CommandTraits cmdTrait_CMD_BPROC_DOT_AND_ADDENDUM( CMD_BPROC_DOT_AND_ADDENDUM,
                                                          BUSINESS_PROCESS_TYPE,
                                                          1,
                                                          1,
                                                          MODE_BOTH,
                                                          I_("DisplayScreen"), // mapping with DOT and ADDENDUM
                                                          325 + 0 ,
                                                          500 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_LIF_GAIN_LOSS= I_( "CMD_BPROC_LIF_GAIN_LOSS" );
static CommandTraits cmdTrait_CMD_BPROC_LIF_GAIN_LOSS( CMD_BPROC_LIF_GAIN_LOSS,
                                                          BUSINESS_PROCESS_TYPE,
                                                          1,
                                                          1,
                                                          MODE_BOTH,
                                                          I_("DisplayScreen"), // mapping with LIFGainLoss
                                                          235 + 0 ,
                                                          600 + 0 );//DesktopWeb conversion

CLASS_EXPORT const I_CHAR *CMD_BPROC_TFSA_CONTRIBUTION_INFO = I_( "CMD_BPROC_TFSA_CONTRIBUTION_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_TFSA_CONTRIBUTION_INFO( CMD_BPROC_TFSA_CONTRIBUTION_INFO,
                                                          BUSINESS_PROCESS_TYPE,
                                                          1,
                                                          1,
                                                          MODE_BOTH,
                                                          I_("DisplayScreen"), // mapping with TFSAContribInfo
                                                          225 + 0 ,
                                                          730 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE = I_( "BPROC_ACCT_LEVEL_SETTLEMENT_RULE" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE( CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE,
                                                                    BUSINESS_PROCESS_TYPE,
                                                                    1,
                                                                    1,
                                                                    MODE_BOTH,
                                                                    I_("AccountLevelSettlementRule_Main"));

CLASS_EXPORT const I_CHAR *CMD_BPROC_RELEASE_FROZEN_ACCOUNT = I_( "BPROC_RELEASE_FROZEN_ACCOUNT" );
static CommandTraits cmdTrait_CMD_BPROC_RELEASE_FROZEN_ACCOUNT( CMD_BPROC_RELEASE_FROZEN_ACCOUNT,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),	// mapping with ReleaseFrozenAcct, DesktopWeb conversion
                                                   315 + 0,    // 315 + 80, 80 added for adjustment
                                                   560 + 0);	// 560 + 40, 40 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUND_CLASS_COPY = I_( "BPROC_FUND_CLASS_COPY" );
static CommandTraits cmdTrait_CMD_BPROC_FUND_CLASS_COPY( CMD_BPROC_FUND_CLASS_COPY,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with ClassCopy
                                                   410 + 0,    // 410 + 80, 80 added for adjustment
                                                   685 + 0     // 685 + 42, 42 added for adjustment
												   ); //DesktopWeb conversion

CLASS_EXPORT const I_CHAR *CMD_BPROC_RENEW_SESSION_TOKEN = I_( "BPROC_RENEW_SESSION_TOKEN" );
static CommandTraits cmdTrait_CMD_BPROC_RENEW_SESSION_TOKEN( CMD_BPROC_RENEW_SESSION_TOKEN,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("RenewSessionToken_Main")); 


CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNT_STATIC_DATA_VERIFY = I_( "CMD_BPROC_ACCOUNT_STATIC_DATA_VERIFY" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNT_STATIC_DATA_VERIFY( CMD_BPROC_ACCOUNT_STATIC_DATA_VERIFY,
                                                                    BUSINESS_PROCESS_TYPE,
                                                                    1,
                                                                    1,
                                                                    MODE_BOTH,
                                                                    I_("DisplayScreen"),// mapping with AcctStDataVerify
                                                                    300 + 0 ,
                                                                    720 + 0 ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUND_CLASS_MAINTENANCE = I_( "CMD_BPROC_FUND_CLASS_MAINTENANCE" );
static CommandTraits cmdTrait_CMD_BPROC_FUND_CLASS_MAINTENANCE( CMD_BPROC_FUND_CLASS_MAINTENANCE,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with ClassSetup_Search
                                                   670 + 0 ,   // 670 + 95, 95 added for adjustment
                                                   750 + 0     // 750 + 42, 42 added for adjustment
												   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_INVOICE_INSTRUCTION = I_( "CMD_BPROC_INVOICE_INSTRUCTION" );
static CommandTraits cmdTrait_CMD_BPROC_INVOICE_INSTRUCTION( CMD_BPROC_INVOICE_INSTRUCTION,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),// mapping with InvoiceInstr
                                                   670 + 0 ,            // -> 763
                                                   750 + 0 );           // -> 794

CLASS_EXPORT const I_CHAR *CMD_BPROC_REPORT_GROUP = I_( "CMD_BPROC_REPORT_GROUP" );
static CommandTraits cmdTrait_CMD_BPROC_REPORT_GROUP( CMD_BPROC_REPORT_GROUP,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),// mapping with ReportGroup
                                                   580 + 0 ,
                                                   800 + 0 ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_ADDITIONAL_ASSETS = I_( "CMD_BPROC_ADDITIONAL_ASSETS" );
static CommandTraits cmdTrait_CMD_BPROC_ADDITIONAL_ASSETS( CMD_BPROC_ADDITIONAL_ASSETS,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),// mapping with AdditionalAsset
                                                   405 + 0 ,
                                                   700 + 0 ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNT_ASSOCIATION = I_( "CMD_BPROC_ACCOUNT_ASSOCIATION" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNT_ASSOCIATION( CMD_BPROC_ACCOUNT_ASSOCIATION,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with AcctAssociate
                                                   505 + 0 ,            // 605 + 95, 95 added for adjustment
                                                   715 + 0              // 750 + 42, 42 added for adjustment
                                                   );

CLASS_EXPORT const I_CHAR *CMD_BPROC_GRANT_CONTRIB = I_( "CMD_BPROC_GRANT_CONTRIB" );
static CommandTraits cmdTrait_CMD_BPROC_GRANT_CONTRIB( CMD_BPROC_GRANT_CONTRIB,
                                                       BUSINESS_PROCESS_TYPE,
                                                       1,
                                                       1,
                                                       MODE_BOTH,
                                                       I_("DisplayScreen"),// mapping with GrantContrib
                                                       280 + 0 ,
                                                       715 + 0 );//DesktopWeb conversion

CLASS_EXPORT const I_CHAR *CMD_BPROC_GOVT_FILING_AMENDMENT = I_( "CMD_BPROC_GOVT_FILING_AMENDMENT" );
static CommandTraits cmdTrait_CMD_BPROC_GOVT_FILING_AMENDMENT( CMD_BPROC_GOVT_FILING_AMENDMENT,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_BOTH,
                                                               I_("DisplayScreen"),// mapping with GovtAmendment
                                                               325 + 0 ,
                                                               762 + 0 ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_PORTFOLIO_SETUP = I_( "CMD_BPROC_PORTFOLIO_SETUP" );
static CommandTraits cmdTrait_CMD_BPROC_PORTFOLIO_SETUP( CMD_BPROC_PORTFOLIO_SETUP,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_BOTH,
                                                               I_("DisplayScreen"), // mapping with PortfolioSetup
                                                               390 + 0 ,   // 80 added for adjustment
                                                               830 + 0);   // 830 + 43, 43 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_COMMISSION_REDUCTION = I_( "CMD_BPROC_COMMISSION_REDUCTION" );
static CommandTraits cmdTrait_CMD_BPROC_COMMISSION_REDUCTION( CMD_BPROC_COMMISSION_REDUCTION,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_BOTH,
                                                               I_("DisplayScreen"), // mapping with CommRed
                                                               450 + 0 ,   // 450 + 80, 80 added for adjustment
                                                               454 + 0 );  // 454 + 39, 39 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_INTEREST_MAINTENANCE = I_( "CMD_BPROC_INTEREST_MAINTENANCE" );
static CommandTraits cmdTrait_CMD_BPROC_INTEREST_MAINTENANCE( CMD_BPROC_INTEREST_MAINTENANCE,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_BOTH,
                                                              I_("DisplayScreen"), // mapping with IntRateMain
                                                               555 + 0 ,   // 555 + 85, 85 added for adjustment
                                                               800 + 0 );  // 800 + 42, 42 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_INTEREST_CONFIGURATION = I_( "CMD_BPROC_INTEREST_CONFIGURATION" );
static CommandTraits cmdTrait_CMD_BPROC_INTEREST_CONFIGURATION( CMD_BPROC_INTEREST_CONFIGURATION,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_BOTH,
                                                               I_("DisplayScreen"), // mapping with InterestRateConfig
                                                               515 + 0 ,   // 515 + 84, 84 added for adjustment
                                                               575 + 0 );  // 575 + 40, 40 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_GIA_ATTRIBUTES = I_( "CMD_BPROC_GIA_ATTRIBUTES" );
static CommandTraits cmdTrait_CMD_BPROC_GIA_ATTRIBUTES( CMD_BPROC_GIA_ATTRIBUTES,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_BOTH,
                                                               I_("DisplayScreen"));

CLASS_EXPORT const I_CHAR *CMD_BPROC_SEG_ATTRIBUTES = I_( "CMD_BPROC_SEG_ATTRIBUTES" );
static CommandTraits cmdTrait_CMD_BPROC_SEG_ATTRIBUTES( CMD_BPROC_SEG_ATTRIBUTES,
                                                        BUSINESS_PROCESS_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH,
                                                        I_("DisplayScreen"),  // mapping with SEGAttributes
                                                        650 + 0 ,             // 95 added for adjustment
                                                        750 + 0 );            // 42 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_SEG_GUARANTEE_RULES = I_( "CMD_BPROC_SEG_GUARANTEE_RULES" );
static CommandTraits cmdTrait_CMD_BPROC_SEG_GUARANTEE_RULES( CMD_BPROC_SEG_GUARANTEE_RULES,
                                                        BUSINESS_PROCESS_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH,
                                                        I_("DisplayScreen"), // mapping with GuaranteeRule
                                                        440 + 0 ,       // 81 added for adjustment
                                                        750 + 0 );      // 42 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_DIPLOMA= I_( "CMD_BPROC_RESP_DIPLOMA" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_DIPLOMA( CMD_BPROC_RESP_DIPLOMA,
                                                        BUSINESS_PROCESS_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH,
                                                        I_("DisplayScreen"), // mapping with RESPDiploma
                                                        400 + 0 ,		 // 400 + 80, 80 added for adjustment
                                                        440 + 0);		 // 440 + 38, 38 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_SEG_PROCESSING = I_( "CMD_BPROC_SEG_PROCESSING" );
static CommandTraits cmdTrait_CMD_BPROC_SEG_PROCESSING( CMD_BPROC_SEG_PROCESSING,
                                                        BUSINESS_PROCESS_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH,
                                                        I_("DisplayScreen"),// mapping with SEGProcessing
                                                        280 + 0 ,
                                                        715 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_VERSION_FEATURE = I_( "CMD_BPROC_VERSION_FEATURE" );
static CommandTraits cmdTrait_CMD_BPROC_VERSION_FEATURE( CMD_BPROC_VERSION_FEATURE,
                                                        BUSINESS_PROCESS_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH,
                                                        I_("DisplayScreen"),// mapping with VersionFeatures
                                                        280 + 0 ,
                                                        700 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_EVENT_DATE_GEN = I_( "BPROC_EVENT_DATE_GEN" );
static CommandTraits cmdTrait_CMD_BPROC_EVENT_DATE_GEN( CMD_BPROC_EVENT_DATE_GEN,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),// mapping with ClassSetup_EventGen
                                                   255 + 0 ,
                                                   450 + 0 ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_EVENT_SCH_MAIN = I_( "BPROC_EVENT_SCH_MAIN" );
static CommandTraits cmdTrait_CMD_BPROC_EVENT_SCH_MAIN( CMD_BPROC_EVENT_SCH_MAIN,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),// mapping with ClassSetup_EvenMain
                                                   705 + 0 ,
                                                   715 + 0 ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRADE_SCH_MAIN = I_( "BPROC_TRADE_SCH_MAIN" );
static CommandTraits cmdTrait_CMD_BPROC_TRADE_SCH_MAIN( CMD_BPROC_TRADE_SCH_MAIN,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),// mapping with TradeDateMain
                                                   355 + 0 ,
                                                   715 + 0 ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_GUARANTEE_FEE = I_( "CMD_BPROC_GUARANTEE_FEE" );
static CommandTraits cmdTrait_CMD_BPROC_GUARANTEE_FEE( CMD_BPROC_GUARANTEE_FEE,
                                                        BUSINESS_PROCESS_TYPE,
                                                        1,
                                                        1,
                                                        MODE_BOTH,
                                                        I_("DisplayScreen"),// mapping with GuaranteeFee
                                                        500 + 0 ,
                                                        715 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FOREIGN_TAX_REVIEW = I_( "BPROC_FOREIGN_TAX_REVIEW" );
static CommandTraits cmdTrait_CMD_BPROC_FOREIGN_TAX_REVIEW( CMD_BPROC_FOREIGN_TAX_REVIEW,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with AcctGovFile
                                                   675 + 0 ,		      // 81 added for adjustment
                                                   715 + 0 );           // 42 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_OWNERSHIP_ALLOCATION = I_( "BPROC_ACCT_OWNERSHIP_ALLOCATION" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_OWNERSHIP_ALLOCATION( CMD_BPROC_ACCT_OWNERSHIP_ALLOCATION,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),// mapping with AcctTaxAlloc
                                                   300 + 0 ,
                                                   600 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_FEE_MODEL_ASSOCIATION = I_( "BPROC_ACCT_ACCT_FEE_MODEL_ASSOCIATION" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_FEE_MODEL_ASSOCIATION( CMD_BPROC_ACCT_FEE_MODEL_ASSOCIATION,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),// mapping with AcctAssociate
                                                   505 + 0 ,
                                                   715 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_SHR_STATEMENT_SCHED = I_( "BPROC_SHR_STATEMENT_SCHED" );
static CommandTraits cmdTrait_CMD_BPROC_SHR_STATEMENT_SCHED( CMD_BPROC_SHR_STATEMENT_SCHED,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),// mapping with ShrStmtSched
                                                   285 + 0 ,
                                                   615 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_IDENTIFIER = I_( "BPROC_ACCT_IDENTIFIER" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_IDENTIFIER( CMD_BPROC_ACCT_IDENTIFIER,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with AccountIdentifier
                                                   290 + 0 ,   // 290 + 82, 82 added for adjustment
                                                   612 + 0);   // 612 + 40, 40 added for adjustment

CLASS_EXPORT const I_CHAR *CMD_BPROC_IDENTIFICATION_MAINT = I_( "BPROC_IDENTIFICATION_MAINT" );
static CommandTraits cmdTrait_CMD_BPROC_IDENTIFICATION_MAINT( CMD_BPROC_IDENTIFICATION_MAINT,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with FinInstIden
                                                   400 + 0 ,
                                                   660 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_FFI_MAINT = I_( "BPROC_FFI_MAINT" );
static CommandTraits cmdTrait_CMD_BPROC_FFI_MAINT( CMD_BPROC_FFI_MAINT,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with FinanInst
                                                   670 + 0 ,
                                                   750 + 0 
                                                   ); 
CLASS_EXPORT const I_CHAR *CMD_BPROC_FUNDGROUP_REGULATORY = I_( "BPROC_FUNDGROUP_REGULATORY" );
static CommandTraits cmdTrait_CMD_BPROC_FUNDGROUP_REGULATORY( CMD_BPROC_FUNDGROUP_REGULATORY,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with FinanInst
                                                   670 + 0 ,
                                                   750 + 0 
                                                   );  
CLASS_EXPORT const I_CHAR *CMD_BPROC_BROKER_REGULATORY = I_( "BPROC_BROKER_REGULATORY" );
static CommandTraits cmdTrait_CMD_BPROC_BROKER_REGULATORY( CMD_BPROC_BROKER_REGULATORY,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with FinanInst
                                                   615 + 0 ,
                                                   700 + 0 
                                                   );  
CLASS_EXPORT const I_CHAR *CMD_BPROC_INTERMEDIARY_REGULATORY = I_( "BPROC_INTERMEDIARY_REGULATORY" );
static CommandTraits cmdTrait_CMD_BPROC_INTERMEDIARY_REGULATORY( CMD_BPROC_INTERMEDIARY_REGULATORY,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with FinanInst
                                                   615 + 0 ,
                                                   700 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRAILER_FEES_INQUIRY = I_( "BPROC_TRAILER_FEES_INQUIRY" );
static CommandTraits cmdTrait_CMD_BPROC_TRAILER_FEES_INQUIRY( CMD_BPROC_TRAILER_FEES_INQUIRY,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   550 + 0 ,
                                                   625 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNT_GROUP = I_( "BPROC_ACCOUNT_GROUP" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNT_GROUPY( CMD_BPROC_ACCOUNT_GROUP,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   520 + 0 ,
                                                   720 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_PRIVATE_WEALTH_INFO = I_( "BPROC_PRIVATE_WEALTH_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_PRIVATE_WEALTH_INFO( CMD_BPROC_PRIVATE_WEALTH_INFO,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   450 + 0 ,
                                                   720 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_TAX_SLIPS = I_( "BPROC_TAX_SLIPS" );
static CommandTraits cmdTrait_CMD_BPROC_TAX_SLIPS( CMD_BPROC_TAX_SLIPS,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   450 + 0 ,
                                                   650 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_PDF_VIEWER = I_( "BPROC_PDF_VIEWER" );
static CommandTraits cmdTrait_CMD_BPROC_PDF_VIEWER( CMD_BPROC_PDF_VIEWER,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   450 + 0 ,
                                                   650 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_FATCA_FILING_DETAIL = I_( "BPROC_FATCA_FILING_DETAIL" );
static CommandTraits cmdTrait_CMD_BPROC_FATCA_FILING_DETAIL( CMD_BPROC_FATCA_FILING_DETAIL,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   740 + 0 ,
                                                   830 + 0 
                                                   ); 


CLASS_EXPORT const I_CHAR *CMD_BPROC_REG_ACCT_EXTR = I_( "BPROC_REG_ACCT_EXTR" );
static CommandTraits cmdTrait_CMD_BPROC_REG_ACCT_EXTR( CMD_BPROC_REG_ACCT_EXTR,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   670 + 0 ,
                                                   750 + 0 
                                                   );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REG_ACCT_INFO_REV = I_( "BPROC_REG_ACCT_INFO_REV" );
static CommandTraits cmdTrait_CMD_BPROC_REG_ACCT_INFO_REV( CMD_BPROC_REG_ACCT_INFO_REV,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   670 + 0 ,
                                                   750 + 0 
                                                   );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNT_GROUPING_INFO = I_( "BPROC_ACCOUNT_GROUPING_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNT_GROUPING_INFO( CMD_BPROC_ACCOUNT_GROUPING_INFO,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   440 + 0 ,
                                                   660 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUND_RULES_MAINTENANCE = I_( "BPROC_FUND_RULES_MAINTENANCE" );
static CommandTraits cmdTrait_CMD_BPROC_FUND_RULES_MAINTENANCE( CMD_BPROC_FUND_RULES_MAINTENANCE,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   600 + 0 ,
                                                   680 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRANSFER_OF_ACCOUNTS = I_( "BPROC_TRANSFER_OF_ACCOUNTS" );
static CommandTraits cmdTrait_CMD_BPROC_TRANSFER_OF_ACCOUNTS( CMD_BPROC_TRANSFER_OF_ACCOUNTS,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   600 + 0 ,
                                                   750 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_SEG_DATES = I_( "BPROC_SEG_DATES" );
static CommandTraits cmdTrait_CMD_BPROC_SEG_DATES( CMD_BPROC_SEG_DATES,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   300 + 0 ,
                                                   400 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_CONTRACT_OVERRIDE = I_( "BPROC_CONTRACT_OVERRIDE" );
static CommandTraits cmdTrait_CMD_BPROC_CONTRACT_OVERRIDE( CMD_BPROC_CONTRACT_OVERRIDE,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   200 + 0 ,
                                                   400 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_INVEST_INFO = I_( "BPROC_INVEST_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_INVSET_INFO( CMD_BPROC_INVEST_INFO,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   600 + 0 ,
                                                   750 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_REGULATORY_AGREEMENT = I_( "BPROC_REGULATORY_AGREEMENT" );
static CommandTraits cmdTrait_CMD_BPROC_REGULATORY_AGREEMENT( CMD_BPROC_REGULATORY_AGREEMENT,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   615 + 0 ,
                                                   758 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_EXTERNAL_TA_FUND_LINKAGE = I_( "BPROC_EXTERNAL_TA_FUND_LINKAGE" );
static CommandTraits cmdTrait_CMD_BPROC_EXTERNAL_TA_FUND_LINKAGE( CMD_BPROC_EXTERNAL_TA_FUND_LINKAGE,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   320 + 0 ,
                                                   720 + 0 
                                                   ); 

//end web pages...

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACTIVE_BATCH = I_( "BPROC_ACTIVE_BATCH" );
static CommandTraits cmdTrait_CMD_BPROC_ACTIVE_BATCH( CMD_BPROC_ACTIVE_BATCH,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_PROGRESS_CTRL = I_( "CMD_BPROC_PROGRESS_CTRL" );
static CommandTraits cmdTrait_CMD_BPROC_PROGRESS_CTRL( CMD_BPROC_PROGRESS_CTRL,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ADDR_TAX_JURIS_UPDATE = I_( "BPROC_ADDR_TAX_JURIS_UPDATE" );
static CommandTraits cmdTrait_CMD_BPROC_ADDR_TAX_JURIS_UPDATE( CMD_BPROC_ADDR_TAX_JURIS_UPDATE,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION = I_( "BPROC_INVESTOR_AUTHORIZATION_INFORMATION" );
static CommandTraits cmdTrait_CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION( CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION,
                                                                    BUSINESS_PROCESS_TYPE,
                                                                    1,
                                                                    1,
                                                                    MODE_BOTH );


CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_ACCT_INFO_NASU = I_( "BPROC_RESP_ACCT_INFO_NASU" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_ACCT_INFO_NASU( CMD_BPROC_RESP_ACCT_INFO_NASU,
                                                                    BUSINESS_PROCESS_TYPE,
                                                                    1,
                                                                    1,
                                                                    MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_PSE_EAP = I_( "BPROC_PSE_EAP" );
static CommandTraits cmdTrait_CMD_BPROC_PSE_EAP( CMD_BPROC_PSE_EAP,
                                                 BUSINESS_PROCESS_TYPE,
                                                 1,
                                                 1,
                                                 MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_GUARNT_GUARD_OPTN = I_( "BPROC_ACCT_GUARNT_GUARD_OPTN" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_GUARNT_GUARD_OPTN( CMD_BPROC_ACCT_GUARNT_GUARD_OPTN,
                                                                BUSINESS_PROCESS_TYPE,
                                                                1,
                                                                1,
                                                                MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_TRAILER_FEE_SETUP = I_( "BPROC_TRAILER_FEE_SETUP" );
static CommandTraits cmdTrait_CMD_BPROC_TRAILER_FEE_SETUP( CMD_BPROC_TRAILER_FEE_SETUP,
                                                           BUSINESS_PROCESS_TYPE,
                                                           1,
                                                           1,
                                                           MODE_BOTH,
                                                           I_("DisplayScreen"), // mapping with TrailerFeeSetup
                                                           550 + 0 ,    // 550 + 86, 86 added for adjustment 
                                                           765 + 0 );   // 42 added for adjustment 

CLASS_EXPORT const I_CHAR *CMD_BPROC_GIA_INVEST_ATTRIBS = I_( "BPROC_GIA_INVEST_ATTRIBS" );
static CommandTraits cmdTrait_CMD_BPROC_GIA_INVEST_ATTRIBS( CMD_BPROC_GIA_INVEST_ATTRIBS,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_GI_INVESTMENT_DETAILS = I_( "BPROC_GI_INVESTMENT_DETAILS" );
static CommandTraits cmdTrait_CMD_BPROC_GI_INVESTMENT_DETAILS( CMD_BPROC_GI_INVESTMENT_DETAILS,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ESTATE_ALLOCATION = I_( "BPROC_ESTATE_ALLOCATION" );
static CommandTraits cmdTrait_CMD_BPROC_ESTATE_ALLOCATION( CMD_BPROC_ESTATE_ALLOCATION,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCOUNT_COMMITMENT = I_( "BPROC_ACCOUNT_COMMITMENT" );
static CommandTraits cmdTrait_CMD_BPROC_ACCOUNT_COMMITMENT( CMD_BPROC_ACCOUNT_COMMITMENT,
                                                         BUSINESS_PROCESS_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_INVESTMENT_HISTORY_LIST = I_( "BPROC_INVESTMENT_HISTORY_LIST" );
static CommandTraits cmdTrait_CMD_BPROC_INVESTMENT_HISTORY_LIST( CMD_BPROC_INVESTMENT_HISTORY_LIST,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_PROGRESSIVE_INTEREST_RATE_LIST = I_( "BPROC_PROGRESSIVE_INTEREST_RATE_LIST" );
static CommandTraits cmdTrait_CMD_BPROC_PROGRESSIVE_INTEREST_RATE_LIST( CMD_BPROC_PROGRESSIVE_INTEREST_RATE_LIST,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_INTEREST_SEGMENT_LIST = I_( "BPROC_INTEREST_SEGMENT_LIST" );
static CommandTraits cmdTrait_CMD_BPROC_INTEREST_SEGMENT_LIST( CMD_BPROC_INTEREST_SEGMENT_LIST,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_GUI_PAYMENT_INFO_FLAG = I_( "GUIDLG_PAYMENT_INFO_FLAG" );
static CommandTraits cmdTrait_CMD_GUI_PAYMENT_INFO_FLAG( CMD_GUI_PAYMENT_INFO_FLAG,
                                                         GUI_TYPE | DIALOG_TYPE,
                                                         1,
                                                         1,
                                                         MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_PAYMENT_INFO_FLAG = I_( "BPROC_PAYMENT_INFO_FLAG" );
static CommandTraits cmdTrait_CMD_BPROC_PAYMENT_INFO_FLAG(  CMD_BPROC_PAYMENT_INFO_FLAG,
                                                            BUSINESS_PROCESS_TYPE,
                                                            1,
                                                            1,
                                                            MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_CONTRACT_MATURITY_INSTRUCTIONS = I_( "BPROC_CONTRACT_MATURITY_INSTRUCTIONS" );
static CommandTraits cmdTrait_CMD_BPROC_CONTRACT_MATURITY_INSTRUCTIONS( CMD_BPROC_CONTRACT_MATURITY_INSTRUCTIONS,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_VALUE_VARIATION = I_( "CMD_BPROC_VALUE_VARIATION" );
static CommandTraits cmdTrait_CMD_BPROC_VALUE_VARIATION( CMD_BPROC_VALUE_VARIATION,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_REMIT_UNCLM_ACCT = I_( "BPROC_REMIT_UNCLM_ACCT" );
static CommandTraits cmdTrait_CMD_BPROC_REMIT_UNCLM_ACCT( CMD_BPROC_REMIT_UNCLM_ACCT,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),// mapping with RemitUnclmAcct
                                                          200 + 0 ,
                                                          500 + 0 ); 

CLASS_EXPORT const I_CHAR *CMD_BPROC_AWDHISTORY = I_( "BPROC_AWDHISTORY" );
static CommandTraits cmdTrait_CMD_BPROC_AWDHISTORY( CMD_BPROC_AWDHISTORY,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_BPROC_AWDHISTORY_BROWSER = I_( "BPROC_AWDHISTORY_BROWSER" );
static CommandTraits cmdTrait_CMD_BPROC_AWDHISTORY_BROWSER( CMD_BPROC_AWDHISTORY_BROWSER,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_MODALONLY );

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_NOTIONAL_BALANCE_INFO = I_( "BPROC_RESP_NOTIONAL_BALANCE_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_NOTIONAL_BALANCE_INFO( CMD_BPROC_RESP_NOTIONAL_BALANCE_INFO,
																	BUSINESS_PROCESS_TYPE,
																	1,
																	1,
																	MODE_MODALONLY,
																	I_("DisplayScreen"), // mapping with RESPNotionalBalance
																	650 + 0 ,
																	750 + 0 );//DesktopWeb conversion

CLASS_EXPORT const I_CHAR *CMD_BPROC_RESP_NOTIONAL_ACTIVITY = I_( "BPROC_RESP_NOTIONAL_ACTIVITY" );
static CommandTraits cmdTrait_CMD_BPROC_RESP_NOTIONAL_ACTIVITY( CMD_BPROC_RESP_NOTIONAL_ACTIVITY,
																	BUSINESS_PROCESS_TYPE,
																	1,
																	1,
																	MODE_MODALONLY,
																	I_("DisplayScreen"), // mapping with RESPNotionalActivity
																	650 + 0 ,
																	750 + 0 );//DesktopWeb conversion

CLASS_EXPORT const I_CHAR *CMD_GUI_RESP_TRANSFORMATION_TRANSFER = I_( "GUIDLG_RESP_TRANSFORMATION_TRANSFER" );
static CommandTraits cmdTrait_CMD_GUI_RESP_TRANSFORMATION_TRANSFER ( CMD_GUI_RESP_TRANSFORMATION_TRANSFER,
                                                  GUI_TYPE | DIALOG_TYPE,
                                                  1,
                                                  1,
                                                  MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_EXTERNAL_INSTITUTION_SEARCH = I_( "BPROC_EXTERNAL_INSTITUTION_SEARCH" );
static CommandTraits cmdTrait_CMD_BPROC_EXTERNAL_INSTITUTION_SEARCH( CMD_BPROC_EXTERNAL_INSTITUTION_SEARCH,
                                                                     BUSINESS_PROCESS_TYPE,
                                                                     1,
                                                                     1,
                                                                     MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUND_GROUP = I_( "BPROC_FUND_GROUP" );
static CommandTraits cmdTrait_CMD_BPROC_FUND_GROUP( CMD_BPROC_FUND_GROUP,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with FundGroup
                                                   550 + 0 ,
                                                   720 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUND_BROKER_LINKAGE = I_( "BPROC_FUND_BROKER_LINKAGE" );
static CommandTraits cmdTrait_CMD_BPROC_FUND_BROKER_LINKAGE( CMD_BPROC_FUND_BROKER_LINKAGE,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with FundBrokerLinkage
                                                   550 + 0 ,
                                                   740 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_ROUNDING_RULE = I_( "BPROC_ACCT_ROUNDING_RULE" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_ROUNDING_RULE( CMD_BPROC_ACCT_ROUNDING_RULE,
                                                      BUSINESS_PROCESS_TYPE,
                                                      1,
                                                      1,
                                                      MODE_BOTH );

CLASS_EXPORT const I_CHAR *CMD_BPROC_ACCT_DELETION_REVIEW = I_( "BPROC_ACCT_DELETION_REVIEW" );
static CommandTraits cmdTrait_CMD_BPROC_ACCT_DELETION_REVIEW( CMD_BPROC_ACCT_DELETION_REVIEW,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with AcctDelReview
                                                   330 + 0 ,
                                                   720 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_WITHHODLDING_TAX_RATES_MAINTANENCE = I_( "BPROC_WITHHODLDING_TAX_RATES_MAINTANENCE" );
static CommandTraits cmdTrait_CMD_BPROC_WITHHODLDING_TAX_RATES_MAINTANENCE( CMD_BPROC_WITHHODLDING_TAX_RATES_MAINTANENCE,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with AcctDelReview
                                                   480 + 0 ,
                                                   720 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_FUND_DISTRIBUTION_SPLIT_MAINTENANCE = I_( "BPROC_FUND_DISTRIBUTION_SPLIT_MAINTENANCE" );
static CommandTraits cmdTrait_CMD_BPROC_FUND_DISTRIBUTION_SPLIT_MAINTENANCE( CMD_BPROC_FUND_DISTRIBUTION_SPLIT_MAINTENANCE,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"), // mapping with AcctDelReview
                                                   550 + 0 ,
                                                   680 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_RDSP_ACCOUNT_INFO = I_( "BPROC_RDSP_ACCOUNT_INFO" );
static CommandTraits cmdTrait_CMD_BPROC_RDSP_ACCOUNT_INFO( CMD_BPROC_RDSP_ACCOUNT_INFO,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with RDSPAccountInfo
                                                               760 + 0 ,
                                                               760 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_RDSP_NOTIONAL_BALANCE = I_( "BPROC_RDSP_NOTIONAL_BALANCE" );
static CommandTraits cmdTrait_CMD_BPROC_RDSP_NOTIONAL_BALANCE( CMD_BPROC_RDSP_NOTIONAL_BALANCE,
                                                               BUSINESS_PROCESS_TYPE,
                                                               1,
                                                               1,
                                                               MODE_MODALONLY,
                                                               I_("DisplayScreen"), // mapping with RDSPNotionalBalance
                                                               660 + 0 ,
                                                               760 + 0 );

CLASS_EXPORT const I_CHAR *CMD_BPROC_RDSP_NOTIONAL_ACTIVITY = I_( "BPROC_RDSP_NOTIONAL_ACTIVITY" );
static CommandTraits cmdTrait_CMD_BPROC_RDSP_NOTIONAL_ACTIVITY( CMD_BPROC_RDSP_NOTIONAL_ACTIVITY,
                                                                BUSINESS_PROCESS_TYPE,
                                                                1,
                                                                1,
                                                                MODE_MODALONLY,
                                                                I_("DisplayScreen"), // mapping with RDSPNotionalActivity
                                                                700 + 0 ,
                                                                750 + 0 );
//RDSP Transfer Screen
CLASS_EXPORT const I_CHAR *CMD_BPROC_RDSP_TRANSFER = I_( "BPROC_RDSP_TRANSFER" );
static CommandTraits cmdTrait_CMD_BPROC_RDSP_TRANSFER( CMD_BPROC_RDSP_TRANSFER,
                                                     BUSINESS_PROCESS_TYPE,
                                                     1,
                                                     1,
                                                     MODE_BOTH );
//RDSP Interface Transactions
CLASS_EXPORT const I_CHAR *CMD_BPROC_RDSP_INTERFACE_TRANSACTIONS = I_( "BPROC_RDSP_INTERFACE_TRANSACTIONS" );
static CommandTraits cmdTrait_CMD_BPROC_RDSP_INTERFACE_TRANSACTIONS( CMD_BPROC_RDSP_INTERFACE_TRANSACTIONS,
                                                   BUSINESS_PROCESS_TYPE,
                                                   1,
                                                   1,
                                                   MODE_BOTH,
                                                   I_("DisplayScreen"),
                                                   900 + 0 ,
                                                   750 + 0 
                                                   ); 

CLASS_EXPORT const I_CHAR *CMD_GUI_RDSP_TRANSFER = I_( "CMD_GUI_RDSP_TRANSFER" );
static CommandTraits cmdTrait_CMD_GUI_RDSP_TRANSFER ( CMD_GUI_RDSP_TRANSFER,
													  GUI_TYPE | DIALOG_TYPE,
													  1,
													  1,
													  MODE_BOTH );


// These command traits don't actually have implemented processes

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/processids.cpp-arc  $
// 
//    Rev 1.167   Jul 20 2012 23:17:38   dchatcha
// P0179630 FN01 FATCA Project - Foriegn Tax Review, Acct Ownership Allocation
// 
//    Rev 1.166   Jul 20 2012 09:34:50   if991250
// Added ESTATE_ALLOCATION ids
// 
//    Rev 1.165   Jul 06 2012 18:25:20   wp040240
// IN 2938135 - Desktop/Web screens - to be converted to new Java/Script library 
// 
//    Rev 1.164   Feb 21 2012 15:44:02   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.163   Feb 15 2012 12:25:18   if991250
// RESP Diploma Desktop Web
// 
//    Rev 1.162   Feb 08 2012 04:12:34   panatcha
// DesktopWeb conversion
// 
//    Rev 1.161   Feb 01 2012 15:32:18   dchatcha
// P0184684 FN02 - Guarantee Fee Screen
// 
//    Rev 1.160   Jan 23 2012 23:56:00   panatcha
// P0188394 - iFast Performance Fee
// 
//    Rev 1.159   Jan 20 2012 16:23:28   if991250
// Account Commitment
// 
//    Rev 1.158   Jan 19 2012 12:22:24   dchatcha
// P0186484 - FN 05 - Activate Feature Option button on contract information screen
// 
//    Rev 1.157   Jan 18 2012 17:29:12   wp040027
// P0188394_Performance Fees - Launching valuation dtl/Sharelot Screens
// 
//    Rev 1.156   Jan 16 2012 14:06:28   dchatcha
// P0186484 - FN 05 - SEG Processing Screen
// 
//    Rev 1.155   Jan 06 2012 13:38:14   if991250
// IA money out
// 
//    Rev 1.154   Dec 19 2011 23:45:46   popescu
// DSK French / last screens to be converted to extJS
// 
//    Rev 1.153   Dec 08 2011 21:42:02   wp040032
// P0183989 - Money Market Non Receipt
// 
//    Rev 1.152   Dec 07 2011 16:22:14   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.151   Nov 27 2011 21:33:14   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.150   Nov 17 2011 14:17:48   popescu
// INA - called Guarante Info Browser screen
// 
//    Rev 1.149   Nov 16 2011 19:47:12   dchatcha
// Desktop French changes
// 
//    Rev 1.148   Nov 10 2011 20:10:58   wp040100
// P0186477/FN03 - GIA - Added Investment History processes
// 
//    Rev 1.147   Nov 09 2011 04:02:42   panatcha
// P0186477_FN03_10D - GIA Money In
// 
//    Rev 1.146   Oct 31 2011 14:15:24   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.145   Oct 28 2011 13:50:20   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.144   Oct 19 2011 23:32:38   popescu
// SEG - Configuration  S1 (SEG and Desktop skeleton)
// 
//    Rev 1.143   Aug 22 2011 15:07:30   jankovii
// P0186477 FN01 - GIA Enhancements
// 
//    Rev 1.142   Aug 04 2011 11:30:00   dchatcha
// P0186477 FN01 - GIA Enhancements
// 
//    Rev 1.141   Jul 28 2011 11:35:50   jankovii
// PET186484 - Global Search
// 
//    Rev 1.140   Mar 16 2011 15:53:12   jankovii
// PET 179563 FN01 - Smart Forms
// 
//    Rev 1.139   Jan 31 2011 17:51:48   popescu
// P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
// 
//    Rev 1.138   Dec 01 2010 13:41:14   popescu
// QESI Phase 3B
// 
//    Rev 1.137   Nov 17 2010 01:54:18   dchatcha
// PET0165541 FN03 - QESI Phase3, integrtation with browser screen.
// 
//    Rev 1.136   Oct 28 2010 11:00:06   jankovii
// Sync up; IN 2305655 - FN03 QESI - RESP Beneficiary Allocation History Button
// 
//    Rev 1.135   Oct 28 2010 10:26:16   dchatcha
// PET0165541 FN03 - QESI Phase3
// 
//    Rev 1.134   Sep 30 2010 10:04:00   jankovii
// PET168727 FN22 - Trailer Fee Setup
// 
//    Rev 1.133   Sep 17 2010 07:15:30   kitticha
// PETP0173756 FN02 Don't Bust the Rules.
// 
//    Rev 1.132   Aug 06 2010 13:51:30   jankovii
// PET165541 FN03 SOC14 & SOC6
// 
//    Rev 1.131   Jun 15 2010 11:25:14   jankovii
// PE165541_FN09_QESI Phase 2
// 
//    Rev 1.130   Apr 20 2010 00:53:24   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading - PSE/EAP   screen
// 
//    Rev 1.129   Apr 15 2010 18:10:12   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading - F4 Browser screen helper...
// 
//    Rev 1.128   Apr 14 2010 09:53:54   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.127   Mar 16 2010 17:18:56   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU - Fix some of the job names
// 
//    Rev 1.126   Mar 12 2010 14:19:32   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.125   Mar 05 2010 15:56:30   jankovii
// PET165541 FN01 - QESI - RESP Gap.
// 
//    Rev 1.124   Jan 28 2010 17:03:26   jankovii
// PET165541 FN01 - QESI - RESP Gap.
// 
//    Rev 1.123   Jan 26 2010 13:41:34   jankovii
// PET165541 FN01 - QESI - RESP Gap
// 
//    Rev 1.122   Dec 02 2009 09:53:50   popescu
// P0160872 - Fund Setup Phase II
// 
//    Rev 1.121   Nov 20 2009 11:42:18   popescu
// Static Data - entity verify names -linked the web screen
// 
//    Rev 1.120   Oct 25 2009 09:35:54   purdyech
// Added RENEW_SESSION_TOKEN
// 
//    Rev 1.119   Aug 11 2009 11:57:00   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields
// 
//    Rev 1.118   Jul 09 2009 14:11:08   dchatcha
// PET156681 FN14 H36 Investor Authorization.
// 
//    Rev 1.117   08 Jul 2009 17:38:20   walkerro
// PET156681 FN03 - Postal Code Lookup added
// 
//    Rev 1.116   17 Jun 2009 16:44:32   popescu
// PET160872 FN01 Fund Setup-Class Level. - corrected the name of the job
// 
//    Rev 1.115   May 14 2009 11:42:10   dchatcha
// PET160872 FN01 Fund Setup-Class Level.
// 
//    Rev 1.114   May 12 2009 11:59:56   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.113   Mar 09 2009 10:52:56   jankovii
// PET 142007 FN04 - TFSA.
// 
//    Rev 1.112   Mar 09 2009 10:27:28   jankovii
// PET 142007 FN04 - TFSA.
// 
//    Rev 1.111   Mar 02 2009 09:54:20   jankovii
// PET0159508 FN03 ESG In Cash Transfer 
// 
//    Rev 1.110   Nov 03 2008 05:25:28   yaviratp
// PET5517 FN71B2 Unclaimed Property - new browser screen (Release Frozen Account).
// 
//    Rev 1.109   Oct 29 2008 21:05:56   wongsakw
// PET0096390 FN01 Tax Jurisdiction Update
// 
//    Rev 1.108   Oct 09 2008 11:55:32   jankovii
// IN 1437673 KYC Broker info.
// 
//    Rev 1.107   Aug 11 2008 15:04:08   jankovii
// PET0057430 FN01 - Performance Fee.
// 
//    Rev 1.106   06 Aug 2008 10:11:02   kovacsro
// PET59888 FN01 - AML Enhancement.
// 
//    Rev 1.105   17 Jul 2008 15:04:56   popescu
// Incident 1190617 - checked in for 88 the progress bar process
// 
//    Rev 1.104   Jul 11 2008 16:25:06   jankovii
// PET59888 FN01 - AML Enhancement.
// 
//    Rev 1.103   17 Apr 2008 15:38:30   kovacsro
// PET2255 FN47 - New Ontario LIF - changed the name for jobname
// 
//    Rev 1.102   15 Apr 2008 12:09:30   kovacsro
// PET2255 FN47 - New Ontario LIF
// 
//    Rev 1.101   Mar 11 2008 19:21:24   daechach
// PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
// 
//    Rev 1.100   Feb 20 2008 12:46:24   jankovii
// PET 5517 FN80B -DOT and Addendum.
// 
//    Rev 1.99   06 Dec 2007 15:20:00   popescu
// Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
// 
//    Rev 1.98   27 Sep 2007 14:00:38   kovacsro
// IN#1015356 - added Active_Batch proc
// 
//    Rev 1.97   18 Sep 2007 17:46:38   popescu
// AMS/GAP 2360-6 - integrating the AMS AssetInfo screen with Desktop
// 
//    Rev 1.96   Aug 10 2007 11:49:24   ivespaul
// PET2360 - Web Integration.
//
//    Rev 1.95   Apr 19 2007 17:43:28   smithdav
// Add Historical Payments process.
//
//    Rev 1.94   Mar 15 2007 14:54:26   jankovii
// PET 2302 FN01 - Payment Release.
//
//    Rev 1.93   Feb 27 2007 21:15:30   popescu
// Incident#  831221 - backed the code of Web Account Clone feature for CDN market
//
//    Rev 1.92   Nov 09 2006 00:13:36   popescu
// PET 2281/fn01 - clone account - TA - synch-up rel 73
//
//    Rev 1.91   Oct 19 2006 09:40:20   fengyong
// Temp check in for PET 2185 - fund limitation
//
//    Rev 1.90   Aug 29 2006 10:44:10   fengyong
// PET2192 FN17 - Add new jobname for transaction payment search
//
//    Rev 1.89   Aug 23 2006 14:56:18   fengyong
// PET2192 - Add Payment search process Id
//
//    Rev 1.88   Aug 22 2006 15:33:50   popescu
// PET 2212/02 - STP
//
//    Rev 1.87   Jun 08 2006 13:50:10   fengyong
// Add browser launcher
//
//    Rev 1.86   Nov 29 2005 15:23:24   AGUILAAM
// PET_1228_FN02: EUSD Phase 2
//
//    Rev 1.85   Nov 10 2005 13:03:58   porteanm
// PET 1286 FN01 - Bulk Cancellation.
//
//    Rev 1.84   Nov 04 2005 10:41:08   ZHANGCEL
// PET 1286  FN01 -- Add Cancellation Instruction related issue
//
//    Rev 1.83   Oct 24 2005 17:20:08   ZHANGCEL
// PET1332 FN09A -- Add JACCTMAIL and JACCTMAILPROD_OVRRIDE
//
//    Rev 1.82   Aug 17 2005 16:50:22   porteanm
// Incident 351033 - Removed Contract and Guarantee, renamed Contract1 and Guarantee1 to Contract and Guarantee.
//
//    Rev 1.81   Jul 14 2005 17:16:22   popescu
// Incident 357000 - fixed call of inventory screen from transaction history - make it modeless
//
//    Rev 1.80   Jul 06 2005 16:38:56   Yingbaol
// PEt1235,FN01:add rebook, rebook param and transaction link process
//
//    Rev 1.79   Jun 14 2005 11:47:14   hernando
// PET1250 FN01 - Cut Off Times at Acct Level.
//
//    Rev 1.78   May 24 2005 12:44:48   porteanm
// PET OPC Confirm Reprint - Renamed OPC files. Changed class hierarchy.
//
//    Rev 1.77   May 06 2005 12:13:06   porteanm
// PET OPC Confirm Reprint - Added OPC_ONLINE_CONFIRM_REPRINT for Release 63.
//
//    Rev 1.76   May 05 2005 13:52:08   porteanm
// PET OPC Confirm Reprint - Added OPC_CONFIRM_REPRINT for Release 63.
//
//    Rev 1.75   Mar 07 2005 09:52:18   hernando
// PET1024 FN02 - Added CMD_GUI_USERDEFMAT and CMD_BPROC_USERDEFMAT.
//
//    Rev 1.74   Mar 07 2005 08:35:50   yingbaol
// PET1171,FN01: change name for entity alone process
//
//    Rev 1.73   Mar 03 2005 11:56:22   Fengyong
// PET1190 FN5 - Add Dilution
//
//    Rev 1.72   Mar 02 2005 15:24:46   yingbaol
// PET1171,FN01: Change process name to follow our convention
//
//    Rev 1.71   Mar 01 2005 15:45:10   yingbaol
// PET1171.FN01: EU saving, add all entity dialog
//
//    Rev 1.70   Feb 28 2005 16:11:36   Fengyong
// PET1190 FN05 - Transaction cancellation enhancement
//
//    Rev 1.69   Feb 24 2005 17:15:34   ZHANGCEL
// PET1117 FN66-68 - Added File Inquiry and EntityAddressSearch
//
//    Rev 1.68   Feb 08 2005 16:01:34   hernando
// PET1117 FN66-68 - Added FILE and FILE_SEARCH.
//
//    Rev 1.67   Feb 07 2005 15:50:08   hernando
// PET1117 FN66-68 - Added MSG, NetworkID, and MSG_DETAIL Process and Dialog cmd traits.
//
//    Rev 1.66   Feb 07 2005 11:35:32   aguilaam
// PET1198_FN01: LSIF Reason Code enhancement - Inventory_Detail_Deduction
//
//    Rev 1.65   Jan 26 2005 10:58:56   yingbaol
// PET1117 FN67 Add BPAggregateOrder Process
//
//    Rev 1.64   Nov 19 2004 17:32:02   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
//
//    Rev 1.63   Nov 07 2004 14:06:20   popescu
// PET 1117/06, synch changes
//
//    Rev 1.62   Nov 04 2004 11:19:52   VADEANUM
// PET1117 FN08 - Shareholder Fund Broker Support.
//
//    Rev 1.61   Nov 04 2004 11:08:18   ZHANGCEL
// PET1117/08 Add Aggregated Order
//
//    Rev 1.60   Oct 13 2004 15:11:18   VADEANUM
// PET1117 FN21 - Renamed SettleLoc to SettlementInstr
//
//    Rev 1.59   Oct 07 2004 16:33:08   YINGBAOL
// PET1145 FN01 Sync. up version 1.50.1.0
//
//    Rev 1.58   Oct 01 2004 12:23:54   FENGYONG
// Add FundBroker
//
//    Rev 1.57   Sep 21 2004 11:36:12   HERNANDO
// PET1094 FN06 - Added Fund Group.
//
//    Rev 1.56   Aug 30 2004 16:34:46   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
//
//    Rev 1.55   Aug 24 2004 16:28:46   HERNANDO
// PET1117 FN22 - Added CMB_BPROC_UNITFACTORS.
//
//    Rev 1.54   Aug 13 2004 18:53:16   popescu
// PET 1117, FN 06, added TradesDlg2 and TradesProcess2 new files that support the new trade entry screen
//
//    Rev 1.53   Aug 10 2004 11:13:42   FENGYONG
// PET117 FN5 - Client Condition Fee
//
//    Rev 1.52   Jul 28 2004 14:56:22   ZHANGCEL
// PET1082 FNrlc -- New Quebec withholding Tax
//
//    Rev 1.51   Jul 26 2004 10:05:36   VADEANUM
// PET1117 FN01 - Shareholder Static Data support.
//
//    Rev 1.50   Jun 23 2004 15:54:42   SMITHDAV
// Expose hypothetical redemptions as an API interface.
//
//    Rev 1.49   May 11 2004 14:26:30   FENGYONG
// PET1046 FN1 - transfer-switch -Rel57
//
//    Rev 1.48   May 05 2004 15:02:14   VADEANUM
// PET1017 - AWD Comments.
//
//    Rev 1.47   Apr 21 2004 15:29:24   VADEANUM
// PET985 FN01 - LSIF.
//
//    Rev 1.46   Mar 04 2004 11:02:02   HERNANDO
// PET965 FN11 - Modified Mode for Historical.
//
//    Rev 1.45   Feb 24 2004 10:38:36   ZHANGCEL
// PET1001-FN01:Add CMD_GUI_INVENTORY_SUMMARY
//
//    Rev 1.44   Feb 06 2004 14:09:28   HERNANDO
// PET965 FN11 - Added CMD_GUI_HISTORICAL_SHAREHOLDER and CMD_BPROC_HISTORICAL_SHAREHOLDER.
//
//    Rev 1.43   Jan 30 2004 16:45:22   VADEANUM
// PET 859 FN 23 - ADL support.
//
//    Rev 1.42   Dec 11 2003 11:50:36   linmay
// added process id for Fire fighter logon
//
//    Rev 1.41   Nov 20 2003 16:31:56   AGUILAAM
// PET859_FN17: added factors screen - daily equalization.
//
//    Rev 1.40   Nov 10 2003 15:12:22   VADEANUM
// PET 892 FN1 - Trade Settlement Location support for the Process layer.
//
//    Rev 1.39   Nov 10 2003 14:36:22   VADEANUM
// PET892 FN1 - Support for Trade Settlement Location.
//
//    Rev 1.38   Nov 05 2003 17:48:36   HERNANDO
// PET892 FN1 - Added Acct Lvl & Sys Lvl Settlement Location Dialog and Process Traits.
//
//    Rev 1.37   Oct 04 2003 15:56:58   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
//
//    Rev 1.36   Sep 30 2003 10:11:22   FENGYONG
// PET 809 FN08 Direct trading enhancement
//
//    Rev 1.35   Aug 15 2003 14:22:00   FENGYONG
// Add tradestaxrate relate process and dialog
//
//    Rev 1.34   Aug 14 2003 15:44:10   popescu
// Added new process ids for multi-fund gui and bp layer. Changed the id of the allocation process and dialog from *_ALLOCATIONS to *SIMPLE_ALLOCATION; introduced a new process(AllocationSplitProcess) with the Id *_ALLOCATIONS only at the bp level, that will decide which allocation screen should be invoked
//
//    Rev 1.33   Jul 18 2003 11:19:26   linmay
// modified for CIBC AMS
//
//    Rev 1.32   Jun 27 2003 18:13:00   popescu
// Pay To Entity feature, dialog, process and CBO
//
//    Rev 1.31   Jun 09 2003 11:33:10   YINGBAOL
// small fix
//
//    Rev 1.30   May 28 2003 17:26:42   YINGBAOL
// FromToAllocation Process and Dialog ID added
//
//    Rev 1.29   May 22 2003 14:11:40   popescu
// Replaced name 'BankInstr' with 'BankInstructions';
// simplified child lists getters for the Shareholder object
//
//    Rev 1.28   May 07 2003 16:34:42   HERNANDO
// Added CMD_GUI_MANUAL_DIVIDEND and CMD_BPROC_MANUAL_DIVIDEND.
//
//    Rev 1.27   Apr 02 2003 10:52:08   YINGBAOL
// add broker address
//
//    Rev 1.26   Mar 03 2003 17:23:16   FENGYONG
// add Broker AMS process
//
//    Rev 1.25   Mar 03 2003 09:35:28   KOVACSRO
// Added TradeSearch (gui and process)
//
//    Rev 1.24   Feb 06 2003 10:12:58   popescu
// New ids for Historical Info Search Process and dialog
//
//    Rev 1.23   Jan 26 2003 17:08:24   popescu
// Added the historical info process
//
//    Rev 1.22   Jan 24 2003 10:56:48   HSUCHIN
// added reset instr ids.
//
//    Rev 1.21   Jan 23 2003 15:32:12   HERNANDO
// Renamed INDEX_MASTER and INDEX_VALUES to MKT_INDEX_MASTER and MKT_INDEX_VALUES.
//
//    Rev 1.20   Jan 21 2003 15:53:22   KOVACSRO
// Added AcctCategory
//
//    Rev 1.19   Jan 20 2003 15:20:12   HSUCHIN
// added prot contract id
//
//    Rev 1.18   Jan 13 2003 15:19:56   linmay
// added CMD_BPROC_FEE_PARAMETER_SYSTEM,
// CMD_GUI_FEE_PARAMETER_SYSTEM
//
//    Rev 1.17   Jan 13 2003 10:14:24   HERNANDO
// Added INDEX_MASTER and INDEX_VALUES.
//
//    Rev 1.16   Jan 13 2003 10:01:36   sanchez
// Changes for shareholder family process
//
//    Rev 1.15   Jan 10 2003 10:01:48   popescu
// Added ids for Protected fund process and GUI
//
//    Rev 1.14   Dec 10 2002 09:53:48   HSUCHIN
// added ftp id
//
//    Rev 1.13   Dec 08 2002 21:54:08   HSUCHIN
// added report view and printer dialog ids
//
//    Rev 1.12   Nov 29 2002 13:11:28   HSUCHIN
// added report status dialog id
//
//    Rev 1.11   Nov 27 2002 11:42:54   HSUCHIN
// added report id
//
//    Rev 1.10   Nov 07 2002 11:20:16   HERNANDO
// Renamed AMSDETAILS to AMSACCTLVL for clarity.
//
//    Rev 1.9   Nov 07 2002 11:14:32   YINGBAOL
// add e CMD_BPROC_AMS_GLOBAL and  CMD_GUI_AMS_GLOBAL.
//
//    Rev 1.8   Oct 29 2002 10:38:38   HERNANDO
// Added AMSDETAILS.
//
//    Rev 1.7   Oct 29 2002 10:32:18   KOVACSRO
// Added HYPO_RED dialog and process ids.
//
//    Rev 1.6   Oct 09 2002 23:53:32   PURDYECH
// PVCS Database Conversion
//
//    Rev 1.5   31 Jul 2002 09:34:34   HUANGSHA
// Added CMD_BPROC_ESTATEMENT and CMD_GUI_ESTATEMENT
//
//    Rev 1.4   Jun 11 2002 11:44:28   YINGBAOL
// create AddressListDialoge for Settlement
//
//    Rev 1.3   May 27 2002 14:23:36   HSUCHIN
// added ids for Pension Jurisdiction
 */