/*****************************************************************************/
//
//  COPYRIGHT:
//
//          The computer systems, procedures, data bases and programs
//          created and maintained by DST Systems, Inc., are proprietary
//          in nature and as such are confidential.  Any unauthorized
//          use or disclosure of such information may result in civil
//          liabilities.
//
//          Copyright 1993 by DST Systems, Inc.
//          All Rights Reserved.
//
//
//  FILE:   $Workfile:   Vmdst.h  $
//
//  AUTHOR: Joel Trigger
//
//  DATE:   05/24/93
//
//  DESCRIPTION:
//     This file contains the internal definitions and function prototypes
//  used for the high-level interface to View Manager/2.
//
//  $Log:   Y:/VCS/iFastAWD/inc_share/Vmdst.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:34:38   kovacsro
//Initial revision.
// 
//    Rev 1.3   Aug 28 1997 16:48:16   DBWR
// Changed packing from 1 byte to 4 byte
// 
//    Rev 1.2   Aug 05 1997 17:57:24   DBWR
//  
// 
//    Rev 1.1   Dec 05 1996 12:36:02   djwb
// changes to support vmshutdn functionality
//
//     Rev 1.0   Nov 04 1996 17:16:42   djwb
//  Initial revision.
//
/*****************************************************************************/

/*****************************/
/**  MACRO INCLUSION GUARD  **/
/*****************************/

#ifndef VMDST_H
#define VMDST_H

#pragma pack( 4 )

/***********************************/
/**  Define VIEW request buffers  **/
/***********************************/

typedef struct
{
  CHAR pchRequestCode[4];
  CHAR pchDataviewID[8];
  CHAR pchOperator[8];
  CHAR pchDataLength[3];
} REQUEST_HEADER, *PREQUEST_HEADER;

/**********************************************/
/**  Define VIEW request buffers with NULLs  **/
/**********************************************/

typedef struct
{
  CHAR pchRequestCode[5];
  CHAR pchDataviewID[9];
  CHAR pchOperator[9];
  CHAR pchDataLength[4];
} REQUEST_NULL, *PREQUEST_NULL;

/**********************************/
/**  Define APPC return buffers  **/
/**********************************/

typedef struct
{
  CHAR pchFixedArea[5];
  CHAR pchRepeatArea[5];
  CHAR pchNumberOfRepeats[3];
  CHAR pchOperator[8];
  CHAR pchReturnCode[3];
  CHAR pchDataLength[3];
} RESPONSE_HEADER, *PRESPONSE_HEADER;

/********************************************/
/**  Define alternate APPC return buffers  **/
/********************************************/

typedef struct
{
  CHAR pchRequestType[4];
  CHAR pchViewName[8];
  CHAR pchNetName[10];
  CHAR pchOperator[8];
  CHAR pchFixedArea[5];
  CHAR pchRepeatArea[5];
  CHAR pchNumberOfRepeats[3];
  CHAR pchReturnCode[3];
  CHAR pchDataLength[3];
} VMGR_RESPONSE_HEADER, *PVMGR_RESPONSE_HEADER;

/*********************************************/
/**  Define string table error message ids  **/
/*********************************************/

#define IDS_END_OF_DATA                 1
#define IDS_DATA_NOT_FOUND              2
#define IDS_INVALID_VIEW                3
#define IDS_SYSTEM_ID_ERROR             4
#define IDS_SYSTEM_DOWN                 5
#define IDS_MAX_IO_LIMIT                6
#define IDS_INFO_UNAVAILABLE           99
#define IDS_INVALID_DATA_REQUEST      100
#define IDS_INVALID_FUND_CODE         101
#define IDS_INVALID_ACCOUNT_NUMBER    102
#define IDS_INVALID_DATE              103
#define IDS_INVALID_CERT_NUMBER       104
#define IDS_INVALID_DEALER_NUMBER     105
#define IDS_INVALID_DEALER_BRANCH     106
#define IDS_INVALID_TAX_ID_NUMBER     107
#define IDS_INVALID_ALPHA_CODE        108
#define IDS_INVALID_BANK_MICR_ID      109
#define IDS_INVALID_REQUEST_COUNT     110
#define IDS_INVALID_RES_STATE_CODE    111
#define IDS_INVALID_DEBIT_CARD        112
#define IDS_INVALID_DEBIT_TYPE        113
#define IDS_INVALID_LOI_NUMBER        114
#define IDS_INVALID_TRANS_NUMBER      115
#define IDS_NO_UPDATES_TO_APPLY       116
#define IDS_CHANGED_BY_DIF_OPERATOR   117
#define IDS_MGMT_NOT_FOUND_ON_A52     118
#define IDS_INVALID_ACCUM_YEARS       119
#define IDS_INVALID_START_YEAR        120
#define IDS_INVALID_START_MONTH       121
#define IDS_INVALID_ARRAY_ROWS        122
#define IDS_INVALID_REIN_DOLLAR       123
#define IDS_INVALID_DSCS_APPREC       124
#define IDS_INVALID_FRONT_END         125
#define IDS_INVALID_REIN_SHARES       126
#define IDS_INVALID_FID_ACCOUNT       127
#define IDS_INVALID_PAF_BUCKET        128
#define IDS_INVALID_FUNCTION_TYPE     129
#define IDS_B08_RECORD_NOT_FOUND      130
#define IDS_NO_UPDATE_DETECTED        131
#define IDS_INVALID_PRE_AGREEMENT     132
#define IDS_INVALID_PST_AGREEMENT     133
#define IDS_INVALID_PURCH_CANCEL      134
#define IDS_INVALID_REDMPT_CANCEL     135
#define IDS_INVALID_EXCH_PUR_CANC     136
#define IDS_INVALID_EXCH_RED_CANC     137
#define IDS_INVALID_MONTHLY_ACCUM     138
#define IDS_TAF_NOT_EQUAL_MASTER      139
#define IDS_SO_MASTER_NOT_FOUND       140
#define IDS_RECORD_ALREADY_EXIST      141
#define IDS_B07_REC_NOT_FOUND         142
#define IDS_AUDIT_FILE_BAD_OPEN       143
#define IDS_AUDIT_REC_NOT_WRITTEN     144
#define IDS_F16_REC_NOT_FOUND         145
#define IDS_F17_REC_NOT_FOUND         146
#define IDS_B06_REC_NOT_FOUND         147
#define IDS_INVALID_DLR_BRN_SEC       148
#define IDS_OPER_NOT_AUTH_DEALER      149
#define IDS_OPER_NOT_AUTH_DLR_BR      150
#define IDS_INVALID_DLR_SUMMARY       151
#define IDS_INVALID_DLR_BR_SUMMRY     152
#define IDS_INVALID_BATCH_NUM         153
#define IDS_NO_A53_FOR_VERIFY_DTE     154
#define IDS_INVALID_PRICE             155
#define IDS_DEL_REC_NOT_FOUND         156
#define IDS_NO_A53_DUMMY_REC          157
#define IDS_A58_REC_NOT_FOUND         158
#define IDS_INVALID_YIELD_DATE        159
#define IDS_CURR_A79_NOT_DEL          160
#define IDS_CHG_REC_NOT_FOUND         161
#define IDS_INVALID_NET_CHG           162
#define IDS_NO_A79_FOR_VERIFY_DTE     163
#define IDS_NO_A56_REC_FOUND          164
#define IDS_INVALID_CUMDISC           165
#define IDS_INVALID_CUMDISC_PLAN      166
#define IDS_RETURN_ACCT_EXISTS        167
#define IDS_RETURN_NASU_ACCT          168
#define IDS_F74_XREF_NOT_FOUND        169
#define IDS_F74_XREF_ADD_RECORD       170
#define IDS_F74_RECORD_IN_USE         171
#define IDS_F74_UPDATE_PREVENTD       172
#define IDS_F74_RETAIL_KEY_DUP        173
#define IDS_F74_INST_KEY_DUP          174
#define IDS_F74_FULL_KEY_DUP          175
#define IDS_F74_DELETE_PREVENTD       176
#define IDS_F71_RETAIL_KEY_DUP        177
#define IDS_F71_INST_KEY_DUPL         178
#define IDS_F71_RECORD_IN_USE         179
#define IDS_F71_ROW_NOT_FOUND         180
#define IDS_F71_INV_FOREIGN_KEY       181
#define IDS_INVALID_GS_FUND           182
#define IDS_INVALID_GS_PORT           183
#define IDS_INVALID_GS_CLASS          184
#define IDS_INVALID_GS_CUST_ID        185
#define IDS_INVALID_GS_CUST_BR_ID     186
#define IDS_INVALID_GS_CUST_ACCT      187
#define IDS_INVALID_GS_CLIENT_ID      188
#define IDS_INVALID_GS_CONV_TYPE      189
#define IDS_SEVERE_SQL_ERROR          190
#define IDS_SQL_TIMESTAMP_ERROR       191
#define IDS_SQL_DEADLOCK              192
#define IDS_WARN_JUMBO_LINK_CHNG      500
#define IDS_INVALID_OPERATOR_ID       900
#define IDS_INVALID_PASSWORD          901
#define IDS_NOT_SIGNED_ON             902
#define IDS_NOT_AUTHORIZED            903
#define IDS_TRANS_BACKED_OUT          904
#define IDS_INVALID_DATA_PASSED       905
#define IDS_OPER_ALREADY_SIGNED_ON    906
#define IDS_DEALER_NOT_AUTHORIZED     910
#define IDS_PASSWDEXP                 911
#define IDS_PASSWDSIMILAR             912
#define IDS_OPERATOR_ID_DISABLED      913
#define IDS_POTENTIAL_DUPLICATE       914
#define IDS_SEVERE_ERROR              999

/**************************/
/**  Define return code  **/
/**************************/

#define RETURN_NORMAL                    "000"
#define RETURN_END_OF_DATA               "001"
#define RETURN_DATA_NOT_FOUND            "002"
#define RETURN_INVALID_VIEW              "003"
#define RETURN_SYSTEM_ID_ERROR           "004"
#define RETURN_SYSTEM_DOWN               "005"
#define RETURN_MAX_IO_LIMIT              "006"
#define RETURN_INFO_UNAVAILABLE          "099"
#define RETURN_INVALID_DATA_REQUEST      "100"
#define RETURN_INVALID_FUND_CODE         "101"
#define RETURN_INVALID_ACCOUNT_NUMBER    "102"
#define RETURN_INVALID_DATE              "103"
#define RETURN_INVALID_CERT_NUMBER       "104"
#define RETURN_INVALID_DEALER_NUMBER     "105"
#define RETURN_INVALID_DEALER_BRANCH     "106"
#define RETURN_INVALID_TAX_ID_NUMBER     "107"
#define RETURN_INVALID_ALPHA_CODE        "108"
#define RETURN_INVALID_BANK_MICR_ID      "109"
#define RETURN_INVALID_REQUEST_COUNT     "110"
#define RETURN_INVALID_RES_STATE_CODE    "111"
#define RETURN_INVALID_DEBIT_CARD        "112"
#define RETURN_INVALID_DEBIT_TYPE        "113"
#define RETURN_INVALID_LOI_NUMBER        "114"
#define RETURN_INVALID_TRANS_NUMBER      "115"
#define RETURN_NO_UPDATES_TO_APPLY       "116"
#define RETURN_CHANGED_BY_DIF_OPERATOR   "117"
#define RETURN_MGMT_NOT_FOUND_ON_A52     "118"
#define RETURN_INVALID_ACCUM_YEARS       "119"
#define RETURN_INVALID_START_YEAR        "120"
#define RETURN_INVALID_START_MONTH       "121"
#define RETURN_INVALID_ARRAY_ROWS        "122"
#define RETURN_INVALID_REIN_DOLLAR       "123"
#define RETURN_INVALID_DSCS_APPREC       "124"
#define RETURN_INVALID_FRONT_END         "125"
#define RETURN_INVALID_REIN_SHARES       "126"
#define RETURN_INVALID_FID_ACCOUNT       "127"
#define RETURN_INVALID_PAF_BUCKET        "128"
#define RETURN_INVALID_FUNCTION_TYPE     "129"
#define RETURN_B08_RECORD_NOT_FOUND      "130"
#define RETURN_NO_UPDATE_DETECTED        "131"
#define RETURN_INVALID_PRE_AGREEMENT     "132"
#define RETURN_INVALID_PST_AGREEMENT     "133"
#define RETURN_INVALID_PURCH_CANCEL      "134"
#define RETURN_INVALID_REDMPT_CANCEL     "135"
#define RETURN_INVALID_EXCH_PUR_CANC     "136"
#define RETURN_INVALID_EXCH_RED_CANC     "137"
#define RETURN_INVALID_MONTHLY_ACCUM     "138"
#define RETURN_TAF_NOT_EQUAL_MASTER      "139"
#define RETURN_SO_MASTER_NOT_FOUND       "140"
#define RETURN_RECORD_ALREADY_EXIST      "141"
#define RETURN_B07_REC_NOT_FOUND         "142"
#define RETURN_AUDIT_FILE_BAD_OPEN       "143"
#define RETURN_AUDIT_REC_NOT_WRITTEN     "144"
#define RETURN_F16_REC_NOT_FOUND         "145"
#define RETURN_F17_REC_NOT_FOUND         "146"
#define RETURN_B06_REC_NOT_FOUND         "147"
#define RETURN_INVALID_DLR_BRN_SEC       "148"
#define RETURN_OPER_NOT_AUTH_DEALER      "149"
#define RETURN_OPER_NOT_AUTH_DLR_BR      "150"
#define RETURN_INVALID_DLR_SUMMARY       "151"
#define RETURN_INVALID_DLR_BR_SUMMRY     "152"
#define RETURN_INVALID_BATCH_NUM         "153"
#define RETURN_NO_A53_FOR_VERIFY_DTE     "154"
#define RETURN_INVALID_PRICE             "155"
#define RETURN_DEL_REC_NOT_FOUND         "156"
#define RETURN_NO_A53_DUMMY_REC          "157"
#define RETURN_A58_REC_NOT_FOUND         "158"
#define RETURN_INVALID_YIELD_DATE        "159"
#define RETURN_CURR_A79_NOT_DEL          "160"
#define RETURN_CHG_REC_NOT_FOUND         "161"
#define RETURN_INVALID_NET_CHG           "162"
#define RETURN_NO_A79_FOR_VERIFY_DTE     "163"
#define RETURN_NO_A56_REC_FOUND          "164"
#define RETURN_INVALID_CUMDISC           "165"
#define RETURN_INVALID_CUMDISC_PLAN      "166"
#define RETURN_RETURN_ACCT_EXISTS        "167"
#define RETURN_RETURN_NASU_ACCT          "168"
#define RETURN_F74_XREF_NOT_FOUND        "169"
#define RETURN_F74_XREF_ADD_RECORD       "170"
#define RETURN_F74_RECORD_IN_USE         "171"
#define RETURN_F74_UPDATE_PREVENTD       "172"
#define RETURN_F74_RETAIL_KEY_DUP        "173"
#define RETURN_F74_INST_KEY_DUP          "174"
#define RETURN_F74_FULL_KEY_DUP          "175"
#define RETURN_F74_DELETE_PREVENTD       "176"
#define RETURN_F71_RETAIL_KEY_DUP        "177"
#define RETURN_F71_INST_KEY_DUPL         "178"
#define RETURN_F71_RECORD_IN_USE         "179"
#define RETURN_F71_ROW_NOT_FOUND         "180"
#define RETURN_F71_INV_FOREIGN_KEY       "181"
#define RETURN_INVALID_GS_FUND           "182"
#define RETURN_INVALID_GS_PORT           "183"
#define RETURN_INVALID_GS_CLASS          "184"
#define RETURN_INVALID_GS_CUST_ID        "185"
#define RETURN_INVALID_GS_CUST_BR_ID     "186"
#define RETURN_INVALID_GS_CUST_ACCT      "187"
#define RETURN_INVALID_GS_CLIENT_ID      "188"
#define RETURN_INVALID_GS_CONV_TYPE      "189"
#define RETURN_SEVERE_SQL_ERROR          "190"
#define RETURN_SQL_TIMESTAMP_ERROR       "191"
#define RETURN_SQL_DEADLOCK              "192"
#define RETURN_WARN_JUMBO_LINK_CHNG      "500"
#define RETURN_CANNOT_LOAD_DLL           "500"
#define RETURN_CANNOT_LOAD_PROCEDURE     "501"
#define RETURN_INVALID_OPERATOR_ID       "900"
#define RETURN_INVALID_PASSWORD          "901"
#define RETURN_NOT_SIGNED_ON             "902"
#define RETURN_NOT_AUTHORIZED            "903"
#define RETURN_TRANS_BACKED_OUT          "904"
#define RETURN_INVALID_DATA_PASSED       "905"
#define RETURN_OPER_ALREADY_SIGNED_ON    "906"
#define RETURN_DEALER_NOT_AUTHORIZED     "910"
#define RETURN_PASSWDEXP                 "911"
#define RETURN_PASSWDSIMILAR             "912"
#define RETURN_OPERATOR_ID_DISABLED      "913"
#define RETURN_POTENTIAL_DUPLICATE       "914"
#define RETURN_SEVERE_ERROR              "999"

/************************************/
/**  Define extracted VIEW header  **/
/************************************/

typedef struct
{
  CHAR        szIdent[9];
  CHAR        szViewName[9];
  CHAR        szHost[9];
  USHORT      usRcPrimary;
  USHORT      usRcSecondary;
  USHORT      usRcView;
  USHORT      usFixedLen;
  USHORT      usRepeatLen;
  USHORT      usNumRepeat;
  PVOID       pvData;
  PVOID       pvFixed;
  PVOID       pvRepeat;
} VMDSTRESP, *PVMDSTRESP;

/*******************************************************/
/**  Define for Cobol to C conversion and vice versa  **/
/*******************************************************/

#define VM_DST_CBL2C         0x0001L
#define VM_DST_C2CBL         0x0002L
#define VM_DST_NONE          0x0004L
#define VM_DST_CBL2IDI             0x0009L

#define MAX_TAG_SIZE  36                                // this would be the maximum size of an idi tag based on the current field
                                                                                                // size in *.vw files + 6 characters for the seq. number ("_#000=")

/***************************/
/**  Function prototypes  **/
/***************************/

//#if (defined(__IBMC__) || defined(__IBMCPP__))
//   extern  BOOL       ViewErrorString      ( USHORT, USHORT, PSZ );
//
//   extern  USHORT     VmNotifySem          ( PSZ, PSZ, USHORT, PBYTE, ULONG,
//                                             PSZ, ULONG );
//   extern  USHORT     VmNotifyQueue        ( PSZ, PSZ, USHORT, PSZ, ULONG );
//   extern  USHORT     VmNotifyWin          ( PSZ, HWND, ULONG, USHORT,
//                                             PBYTE, ULONG, PSZ, ULONG );
//   extern  USHORT     VmConnectApp         ( PSZ, PSZ, ULONG );
//   extern  USHORT     VmDisConnectApp      ( PSZ, PSZ, ULONG );
//   extern  USHORT     VmAppRequest         ( PSZ, PSZ, PSZ, PSZ, ULONG, PBYTE,
//                                             ULONG, ULONG, USHORT, PSZ, ULONG );
//   extern  USHORT     VmAppRequestProt     ( PSZ, PSZ, PSZ, PSZ, ULONG, PBYTE,
//                                             ULONG, ULONG, USHORT, PSZ, ULONG,
//                                             PBYTE, ULONG );
//   extern  USHORT     VmAppRequestPriv     ( PSZ, USHORT, PSZ, PBYTE, ULONG,
//                                             ULONG, USHORT, PSZ, ULONG );
//   extern  USHORT     VmAppRequestPrivProt ( PSZ, USHORT, PSZ, PBYTE, ULONG,
//                                             ULONG, USHORT, PSZ, ULONG, PBYTE,
//                                             ULONG );
//   extern  BOOL       VmErrorMsg           ( PSZ, USHORT, PBYTE, ULONG );
//   extern  BOOL       VmExtractResp        ( PBYTE, PVMDSTRESP );
//   extern  USHORT     VmIsAppConnected     ( PSZ );
//#else
   BOOL    WINAPI     ViewErrorString      ( USHORT, USHORT, PSZ );

   USHORT  WINAPI     VmNotifySem          ( PSZ, PSZ, USHORT, PBYTE, ULONG,
                                             PSZ, ULONG );
   USHORT  WINAPI     VmNotifyQueue        ( PSZ, PSZ, USHORT, PSZ, ULONG );
   USHORT  WINAPI     VmNotifyWin          ( PSZ, HWND, ULONG, USHORT,
                                             PBYTE, ULONG, PSZ, ULONG );
   USHORT  WINAPI     VmConnectApp         ( PSZ, PSZ, ULONG );
   USHORT  WINAPI     VmDisConnectApp      ( PSZ, PSZ, ULONG );
   USHORT  WINAPI     VmAppRequest         ( PSZ, PSZ, PSZ, PSZ, ULONG, PBYTE,
                                             ULONG, ULONG, USHORT, PSZ, ULONG );
   USHORT  WINAPI     VmAppRequestProt     ( PSZ, PSZ, PSZ, PSZ, ULONG, PBYTE,
                                             ULONG, ULONG, USHORT, PSZ, ULONG,
                                             PBYTE, ULONG );
   USHORT  WINAPI     VmAppRequestPriv     ( PSZ, USHORT, PSZ, PBYTE, ULONG,
                                             ULONG, USHORT, PSZ, ULONG );
   USHORT  WINAPI     VmAppRequestPrivProt ( PSZ, USHORT, PSZ, PBYTE, ULONG,
                                             ULONG, USHORT, PSZ, ULONG, PBYTE,
                                             ULONG );
   USHORT  WINAPI     VmShutdownExe        ( USHORT, PSZ, ULONG );
   BOOL    WINAPI     VmErrorMsg           ( PSZ, USHORT, PBYTE, ULONG );
   BOOL    WINAPI     VmExtractResp        ( PBYTE, PVMDSTRESP );
   USHORT  WINAPI     VmIsAppConnected     ( PSZ );
//#endif

/**************************************************/
/**  NO ENTRIES SHOULD EXIST BEYOND THIS #endif  **/
/**************************************************/

#pragma pack()

#endif
