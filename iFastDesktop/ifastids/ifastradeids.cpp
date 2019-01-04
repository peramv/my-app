#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

namespace TRADETYPE
{
   extern CLASS_EXPORT I_CHAR * const TRANSFER                       = I_("TR");
   extern CLASS_EXPORT I_CHAR * const TRANSFER_OUT                   = I_("TO");
   extern CLASS_EXPORT I_CHAR * const TRANSFER_OUT_2                 = I_("TO04,TO08");
   extern CLASS_EXPORT I_CHAR * const TRANSFER_IN                    = I_("TI");
   extern CLASS_EXPORT I_CHAR * const TRANSFER_IN_2                  = I_("TI04,TI08");
   extern CLASS_EXPORT I_CHAR * const EXCHANGE                       = I_("XR");
   extern CLASS_EXPORT I_CHAR * const EXCHANGE_OUT                   = I_("EO");
   extern CLASS_EXPORT I_CHAR * const EXCHANGE_IN                    = I_("EI");
   extern CLASS_EXPORT I_CHAR * const REDEMPTION                     = I_("PW");
   extern CLASS_EXPORT I_CHAR * const PURCHASE                       = I_("ED");
   extern CLASS_EXPORT I_CHAR * const REINVEST_PURCHASE              = I_("RC");
   extern CLASS_EXPORT I_CHAR * const ALL_FUND_TRANSFER              = I_("AFTR");
   extern CLASS_EXPORT I_CHAR * const MGMT_FEE                       = I_("AF91");
   extern CLASS_EXPORT I_CHAR * const MGMT_FEE_REBATE                = I_("ID59");
   extern CLASS_EXPORT I_CHAR * const MANUAL_MGMT_FEE_REBATE         = I_("MFR");
   extern CLASS_EXPORT I_CHAR * const FOREIGN_CAP_GAIN_ALLOC_ADJUSTMENT = I_("ID63");
   extern CLASS_EXPORT I_CHAR * const PAC                               = I_("P");
   extern CLASS_EXPORT I_CHAR * const SWP                               = I_("S");
   extern CLASS_EXPORT I_CHAR * const AUTO_TRANSFER_IN               = I_("ATI");
   extern CLASS_EXPORT I_CHAR * const AUTO_TRANSFER_OUT              = I_("ATO");
   extern CLASS_EXPORT I_CHAR * const AUTO_TRANSFER                  = I_("AT");
   extern CLASS_EXPORT I_CHAR * const SAVING_PLAN                    = I_("V");
   extern CLASS_EXPORT I_CHAR * const ROLLOVER                       = I_("LR");
   extern CLASS_EXPORT I_CHAR * const DIVIDEND                       = I_("ID");
   extern CLASS_EXPORT I_CHAR * const ADMIN_FEE                      = I_("AF");
   extern CLASS_EXPORT I_CHAR * const ADVISOR_FEE                    = I_("AFDF");
   extern CLASS_EXPORT I_CHAR * const REDEMPTION_LIKE                = I_("PW,PW71,PW72,PW73,PW82,PW96,PW98,AW,AF,AF91,AFDF");  // redemption, swp, admin fee,
   extern CLASS_EXPORT I_CHAR * const PURCHASE_LIKE                  = I_("ED,ED71,ED72,ED73,ED91,ED98,RC,ID59,MFR");     //purchase, reinvest purchase, mgmt feerebate
   extern CLASS_EXPORT I_CHAR * const ONE_SIDE_TRADE                 = I_("ED,ED71,ED72,ED73,ED91,ED98,RC,PW,PW71,PW72,PW73,PW82,PW96,PW98,AW,AF,AF91,P,S,V,ID59,AFDF");
   extern CLASS_EXPORT I_CHAR * const ALLOC_ELIG                     = I_("ED,ED71,ED72,ED73,ED91,PW,PW71,PW72,PW73,PW82,AW,AF,AF91,RC,P,S,V");
   extern CLASS_EXPORT I_CHAR * const EXCHANGE_LIKE                  = I_("TI,TO,EI,EO,XR,TR,AFTR,XR33,EI33,EO33,XR45,EI45,EO45");
   extern CLASS_EXPORT I_CHAR * const EXCHANGE_LIKE_2                = I_("TI04,TO04,TI08,TO08");
   extern CLASS_EXPORT I_CHAR * const LINKED_NOTES_ROLLOVER          = I_("AT38"); 
   extern CLASS_EXPORT I_CHAR * const AUTO_WITHDRAW                  = I_("AW"); 
   extern CLASS_EXPORT I_CHAR * const REBOOK_ALLOWABLE_TRANS_TYPES   = I_("ED,ED71,ED72,ED73,ED91,ED98,PW,PW71,PW72,PW73,PW96,PW98,TR,XR,AW,AF91,AFTR,RR,RP,TI,TO,EI,EO,ID59,EI33,EO33,AFDF,EI45,EO45");
   extern CLASS_EXPORT I_CHAR * const MONEY_OUT_TRADES               = I_("TO,EO,PW,PW71,PW72,PW73,PW98,AW");
   extern CLASS_EXPORT I_CHAR * const ALLOW_TO_MODIFY_PENDING_TRXN   = I_("ED,ED71,ED72,ED73,ED91,ED98,PW,PW71,PW72,PW73,PW82,PW96,PW98,AW,TR,XR,AF91,ID59,AFTR,LR,AF,RC,XR33,AFDF,XR45");
   extern CLASS_EXPORT I_CHAR * const MANUAL_TRADES                  = I_("ID,MFR");
   extern CLASS_EXPORT I_CHAR * const INSPECIES_PURCHASE             = I_("ED71");
   extern CLASS_EXPORT I_CHAR * const HYBRID_PURCHASE                = I_("ED72");
   extern CLASS_EXPORT I_CHAR * const INSPECIES_REDEMPTION           = I_("PW71");
   extern CLASS_EXPORT I_CHAR * const REFUND_REDEMPTION              = I_("PW82");
   extern CLASS_EXPORT I_CHAR * const REFUND_REDEMPTION_INDC         = I_("82");
   extern CLASS_EXPORT I_CHAR * const HYBRID_REDEMPTION              = I_("PW72");
   extern CLASS_EXPORT I_CHAR * const CUSIP_ROLLOVER                 = I_("ED91");
   extern CLASS_EXPORT I_CHAR * const PTC_PURCHASE                   = I_("ED,RC,ED71,ED72,ED73,MFR");
   extern CLASS_EXPORT I_CHAR * const PTC_REDEMPTION                 = I_("PW,PW71,PW72,PW73,LR");
   extern CLASS_EXPORT I_CHAR * const PTC_TRANSFER                   = I_("TR,XR,AFTR");
   extern CLASS_EXPORT I_CHAR * const PTC_AF                         = I_("AF,AF91");
   extern CLASS_EXPORT I_CHAR * const PTC_AW                         = I_("AW");
   extern CLASS_EXPORT I_CHAR * const INSP_NON_PRO_RATA_PURCHASE     = I_("ED73");
   extern CLASS_EXPORT I_CHAR * const INSP_NON_PRO_RATA_REDEMPTION   = I_("PW73"); 
   extern CLASS_EXPORT I_CHAR * const FULL_EAP_REDEMPTION            = I_("PW96"); 
   extern CLASS_EXPORT I_CHAR * const CAPITAL_GAIN_INCOME            = I_("IDCI");
   extern CLASS_EXPORT I_CHAR * const SUPPLEMENTAL_INCOME            = I_("IDSI");
   extern CLASS_EXPORT I_CHAR * const ROLLOVER_EXCHANGE              = I_("XR33");
   extern CLASS_EXPORT I_CHAR * const ROLLOVER_EXCHANGE_IN           = I_("EI33");
   extern CLASS_EXPORT I_CHAR * const ROLLOVER_EXCHANGE_OUT          = I_("EO33");
   extern CLASS_EXPORT I_CHAR * const INTER_CLASS_SWITCH_IN          = I_("EI45");
   extern CLASS_EXPORT I_CHAR * const INTER_CLASS_SWITCH_OUT         = I_("EO45");
   extern CLASS_EXPORT I_CHAR * const MANUAL_DIVIDEND_ADJ            = I_("PD59");
   extern CLASS_EXPORT I_CHAR * const CAPITAL_GAIN_INCOME_ADJ        = I_("CI");
   extern CLASS_EXPORT I_CHAR * const SUPPLEMENTARY_INCOME_ADJ       = I_("SI");
   extern CLASS_EXPORT I_CHAR * const FOREIGN_CAPGAIN_ALLOCATION_ADJ = I_("FC");
   extern CLASS_EXPORT I_CHAR * const MGMT_FEE_REBATE_ADJ            = I_("MR59");
   extern CLASS_EXPORT I_CHAR * const POST_DIVIDEND_ADJUSTMENT_LIST  = I_("PD59,CI,SI,FC");
   extern CLASS_EXPORT I_CHAR * const POST_ADJUSTMENT_LIST           = I_("PD59,CI,SI,FC,MR59");
   extern CLASS_EXPORT I_CHAR * const CROSS_SYSTEM_TRANSFER_IN       = I_("ED98");
   extern CLASS_EXPORT I_CHAR * const CROSS_SYSTEM_TRANSFER_OUT      = I_("PW98");
   extern CLASS_EXPORT I_CHAR * const MFR_TARDES                     = I_("ID59,MFR");
   extern CLASS_EXPORT I_CHAR * const INTER_CLASS_SWITCH             = I_("XR45");
   extern CLASS_EXPORT I_CHAR * const PURCHASE_LIKE_2                = I_("ED,ED71,ED72,ED73");
} 


namespace PAYTYPE
{
   extern CLASS_EXPORT I_CHAR * const BRANCH_PURCHASE    = I_("B");
   extern CLASS_EXPORT I_CHAR * const CASH               = I_("C");
   extern CLASS_EXPORT I_CHAR * const CLEARING           = I_("R");
   extern CLASS_EXPORT I_CHAR * const DIRECT             = I_("D");
   extern CLASS_EXPORT I_CHAR * const EFT                = I_("E");
   extern CLASS_EXPORT I_CHAR * const MANUAL_CHEQUE      = I_("M");
   extern CLASS_EXPORT I_CHAR * const SUPPRESS           = I_("X");
   extern CLASS_EXPORT I_CHAR * const SYSTEM_CHEQUE      = I_("S");
   extern CLASS_EXPORT I_CHAR * const WIRE               = I_("W");
   extern CLASS_EXPORT I_CHAR * const PAY_TO_ENTITY      = I_("P");
   extern CLASS_EXPORT I_CHAR * const DIRECT_DEPOSIT     = I_("D1");
} 