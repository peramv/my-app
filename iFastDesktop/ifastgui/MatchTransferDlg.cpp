// MatchTransferDlg.cpp : implementation file
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
//    Copyright 1999 by DST Systems, Inc.
//
//****************************************************************************** 
//
// ^FILE   : MatchTransferDlg.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : August 9, 2001
//
// ----------------------------------------------------------
#include "stdafx.h"
#include "mfdstc.h"
#include "matchtransferdlg.h"

#include <bfproc\abstractprocess.hpp>
#include <bfdata\bffieldid.hpp>
#include <ifastbp\matchtransferprocessincludes.h>
#include <ifastbp\splitcommissionsprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\transactionallocationsprocessincludes.h>
#include <ifastbp\allocationsprocessincludes.h>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\DSTCUserSession.hpp>
#include <ifastcbo\AccountEntityXref.hpp>
#include <bfproc\genericinterfacecontainer.hpp>

//Hllapi
#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>
#include <bfproc\commanddispatcher.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CERTIFICATE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CHEQUE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANSACTION_ALLOCATIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SPLITCOMMISSION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADMINDATES;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_MATCHTRANSFER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACC_DETAILS;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< MatchTransferDlg > dlgCreator( CMD_GUI_MATCHTRANSFER );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _BROKER_INFORMATION            5030 //TRANSACTION_PROCESSING_MENU
#define _BRANCH_INFORMATION            5050
#define _TRANSACTION_PROCESSING_MENU   5060
#define _SETTLEMENTS                   5080
#define _SALES_REP_INFORMATION         5090


namespace
{
   const I_CHAR * const CLASSNAME              = I_( "MatchTransferDlg" );
   const I_CHAR * const GR_TRANSFER_ATTRIBUTE  = I_( "TransferAttribute" );
   const I_CHAR * const LV_MATCHTRANSFER       = I_( "MatchTransferList" );
   const I_CHAR * const LV_ATTRIBUTE           = I_( "Attribute" );
   const I_CHAR * const FUND_NUMBER            = I_( "Baycom" );
   const I_CHAR * Y                            = I_( "Y" );
   const I_CHAR * N                            = I_( "N" );
   const I_CHAR * CASH                         = I_( "CASH" );
   const I_CHAR * MINUS                        = I_(" - ");

   // Paremeter for Certificate
   const I_CHAR *INACCTNUM          = I_( "InAcctNum" );
   const I_CHAR *INFUND             = I_( "InFund" );
   const I_CHAR *INCERTNUM          = I_( "InCertNum" );
   const I_CHAR *INXREFNUM          = I_( "InXrefNum" );

   // Parameter for FundInfo
   const I_CHAR *FUNDCODEVALUE      = I_( "FundCodeValue" );
   const I_CHAR *CLASSCODEVALUE     = I_( "ClassCodeValue" );
   const I_CHAR *FROMDATEVALUE      = I_( "FromDateValue" );
   const I_CHAR *TODATEVALUE        = I_( "ToDateValue" );

   const I_CHAR *MODUSER            = I_( "ModUser" );
   const I_CHAR *MODDATE            = I_( "ModDate" );
   const I_CHAR *PROCESSUSER        = I_( "Username" );
   const I_CHAR *PROCESSDATE        = I_( "ProcessDate" );
   const I_CHAR *pINQUIRYONLY       = I_( "InquiryOnly" );

   const int CERTIFICATE                 = 0;
   const int FUNDINFO                    = 1;
   const int CHEQUE                      = 2;
   const int ADDRESSES                   = 3;
   const int TRANSACTION_ALLOCATIONS     = 4;
   const int BANK_INSTR                  = 5;
   const int SPLITCOMMISSION             = 6;

   const I_CHAR *szCmd[]=
   {
      CMD_BPROC_CERTIFICATE,
      CMD_BPROC_FUNDINFO,
      CMD_BPROC_CHEQUE,
      CMD_BPROC_ADDRESSES,
      CMD_BPROC_TRANSACTION_ALLOCATIONS,
      CMD_BPROC_BANK_INSTRUCTIONS,
      CMD_BPROC_SPLITCOMMISSION,
   };

}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSACTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AltAccount;
   extern CLASS_IMPORT const BFTextFieldId SettleBatch;
   extern CLASS_IMPORT const BFTextFieldId OrderBatch;
   extern CLASS_IMPORT const BFTextFieldId Baycom;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId RemarksLine;
   extern CLASS_IMPORT const BFTextFieldId MatchTransferHeading;
   extern CLASS_IMPORT const BFTextFieldId MatchTransferAttrTop;
   extern CLASS_IMPORT const BFTextFieldId MatchTransferAttrLeft;
   extern CLASS_IMPORT const BFTextFieldId InqPerm;
}

namespace CND
{//Conditionsused
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//user access codes
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ADDRESS_BOOK;
}

/////////////////////////////////////////////////////////////////////////////
// MatchTransferDlg dialog


MatchTransferDlg::MatchTransferDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( MatchTransferDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(MatchTransferDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


/***********************************************************************/

void MatchTransferDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(MatchTransferDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


/***********************************************************************/
BEGIN_MESSAGE_MAP(MatchTransferDlg, BaseMainDlg)
//{{AFX_MSG_MAP(MatchTransferDlg)
ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDCANCEL3, OnBtnClose)
ON_BN_CLICKED(IDC_BTN_GET_ACCOUNT, OnBtnGetAccount)
ON_NOTIFY(NM_DBLCLK, IDC_LV_ATTRIBUTES, OnDblclkLvAttributes)
ON_NOTIFY(NM_CLICK, IDC_LV_ATTRIBUTES, OnClickLvAttributes)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MatchTransferDlg message handlers

/***********************************************************************/
SEVERITY MatchTransferDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));
   SEVERITY sevRtn = SEVERE_ERROR;
//   getParameter( GUARANTEE::KEY_PARAM, m_dstrKey );
   getParameter( MATCHTRANSFER::SHAREHOLDERNUM, m_dstrShareHoldNum );
   getParameter( MATCHTRANSFER::ACCOUNTNUM, m_dstrAccountNumber );
   getParameter( MATCHTRANSFER::TRANSID, m_dstrTransId );
   getParameter( MATCHTRANSFER::ENTITYID, m_dstrEntityId );
   getParameter( pINQUIRYONLY, _InquiryOnly ); 

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

/***********************************************************************/

BOOL MatchTransferDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   // set AccountNum, ShareHolderNum and Entity Name in the title bar
   setTitleBar ( );

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//*****************************************************************************
void MatchTransferDlg::setTitleBar ( )
{

   m_dstrShareHoldNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();
   m_dstrAccountNumber.stripLeading(I_CHAR('0')).stripTrailing();

   SetAccount( m_dstrAccountNumber );

   DString dstrEntityName;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
   getAccountholder01EntityName(getDataGroupId(),
                                              m_dstrAccountNumber,dstrEntityName);

   SetShrAcctCaption(m_dstrShareHoldNum, m_dstrAccountNumber, dstrEntityName);

}

//*****************************************************************************
void MatchTransferDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   AddControl( CTRL_STATIC, IDC_TXT_FUND_NUMBER,   IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::Baycom );
   AddControl( CTRL_EDIT,   IDC_EDIT_FUNDLONGNAME, IFASTBP_PROC::FUNDMASTER_LIST,   ifds::ElongName1, CTRLFLAG_NOT_UPDATABLE );
   AddControl( CTRL_STATIC, IDC_TXT_TRANS_NBR,     IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::TransNum );
   AddControl( CTRL_STATIC, IDC_TXT_FUND_CURRENCY, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::Currency );
   AddControl( CTRL_STATIC, IDC_TXT_PREV_BAL,      IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::PrevUnitBal );
   AddControl( CTRL_STATIC, IDC_TXT_SETTLE_DATE,   IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::SettleDate );
   AddControl( CTRL_STATIC, IDC_TXT_SETTLE_BATCH,  IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::SettleBatch );
   AddControl( CTRL_STATIC, IDC_TXT_BATCH_NUM,     IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::OrderBatch );
   AddControl( CTRL_STATIC, IDC_TXT_NET_AMT,       IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::NetAmt );
   AddControl( CTRL_STATIC, IDC_TXT_ALT_ACCT,      IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::AltAccount );
   AddControl( CTRL_EDIT,   IDC_EDIT_BROKER,       IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::BrokerName, CTRLFLAG_NOT_UPDATABLE );
   AddControl( CTRL_EDIT,   IDC_EDIT_BRANCH,       IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::BranchName, CTRLFLAG_NOT_UPDATABLE );
   AddControl( CTRL_EDIT,   IDC_EDIT_SLSREP,       IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::SlsrepName, CTRLFLAG_NOT_UPDATABLE );
   AddControl( CTRL_EDIT,   IDC_EDT_REMARK,        IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::RemarksLine,
               CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_FIELDS_FROM_SUB_LIST );

   AddListControl( CLASSNAME, IDC_LV_TRANSFER, LV_MATCHTRANSFER, ifds::MatchTransferHeading,
                   IFASTBP_PROC::MATCHTRANSFER_CBO, 0, true, LISTFLAG_NOT_UPDATABLE);
   AddAttributeListControl( CLASSNAME, IDC_LV_ATTRIBUTES, LV_ATTRIBUTE, ifds::MatchTransferAttrTop, 
                            ifds::MatchTransferAttrLeft, IFASTBP_PROC::MATCHTRANSFER_CBO, IDC_LV_TRANSFER, true, LISTFLAG_NOT_UPDATABLE);

   const DString *pdstrKey = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::MATCHTRANSFER_CBO));
   if( *pdstrKey != NULL_STRING )
   {
      ConnectControlsToData();
      LoadListControl( IDC_LV_TRANSFER );
      LoadControls();
   }
}

/***********************************************************************/
bool MatchTransferDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{
   bool bRet = false;
   if( lSubstituteId == ifds::MatchTransferHeading.getId() )
   {
      if( ColumnKey == FUND_NUMBER )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::rxFundCode, dstrFundCode );
         getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::rxClassCode, dstrClassCode );
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber ( dstrFundCode, dstrClassCode, strOut );
         bRet = true;
      }
   }


   else if( lSubstituteId == ifds::MatchTransferAttrLeft.getId() )
   {
      if( ColumnKey == I_( "OrderSource" ) )
         bRet = DisplayCodeDesc( ifds::OrderSource, ifds::OrderSrcDesc, strOut );

      else if( ColumnKey == I_( "Accountable" ) )
         bRet = DisplayCodeDesc( ifds::Accountable, ifds::AcctableDesc, strOut );

      else if( ColumnKey == I_( "RedCode" ) )
         bRet = DisplayCodeDesc( ifds::RedCode, ifds::RedCodeDesc, strOut );

      else if( ColumnKey == I_( "DepositType" ) )
         bRet = DisplayCodeDesc( ifds::DepositType, ifds::DepositTypeDesc, strOut );

      else if( ColumnKey == I_( "SettleSource" ) )
         bRet = DisplayCodeDesc( ifds::SettleSource, ifds::SettleSrcDesc, strOut );

      else if( ColumnKey == I_( "SettleType" ) )
         bRet = DisplayCodeDesc( ifds::SettleType, ifds::SettleTypeDesc, strOut );

      else if( ColumnKey == I_( "RvCode" ) )
         bRet = DisplayCodeDesc( ifds::RvCode, ifds::RvCodeDesc, strOut );

      else if( ColumnKey == I_( "SrcOfFund" ) )
         bRet = DisplayCodeDesc( ifds::SrcOfFund, ifds::SrcOfFundDesc, strOut );

      else if( ColumnKey == I_( "PayType" ) )
         bRet = DisplayCodeDesc( ifds::PayType, ifds::PayTypeDesc, strOut );

      else if( ColumnKey == I_( "SettledBy" ) )
         bRet = DisplayCodeDesc( ifds::SettledBy, ifds::SettledByDesc, strOut );

      else if( ColumnKey == I_( "ChqSupCode" ) )
         bRet = DisplayCodeDesc( ifds::ChqSupCode, ifds::ChqSupCodeDesc, strOut );

      else if( ColumnKey == FUND_NUMBER )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::rxFundCode, dstrFundCode );
         getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::rxClassCode, dstrClassCode );
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber ( dstrFundCode, dstrClassCode, strOut );
         bRet = true;
      }

   }
   return(bRet);
}

/***********************************************************************/

void MatchTransferDlg::OnBtnBrowse() 
{
   // TODO: Add your control notification handler code here

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSplitCom" ) );

   CWaitCursor wait;

   DString dstrCurSelKey = GetList( IDC_LV_ATTRIBUTES )->GetCurrentKey();

   int DlgSel = WhichDlgShouldBeLaunchedTrans( dstrCurSelKey );

   SetMessageStatusBar( NULL_STRING );

   DString Para1, Para2, Para3;
   if( DlgSel == _BROKER_INFORMATION )
   {
      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::BrokerCode, Para1 );
      Para1.stripAll();
      setCsiParameter( DcCsiParameters::BROKER_NUMBER, DStringA(Para1) );
      executeCsiProcess( DcCsiProcesses::BROKER_INFORMATION );
      return;
   }
   if( DlgSel == _BRANCH_INFORMATION )
   {
      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::BrokerCode, Para1 );
      Para1.stripAll();
      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::BranchCode, Para2 );
      Para2.stripAll();
      setCsiParameter( DcCsiParameters::BROKER_NUMBER, DStringA(Para1) );
      setCsiParameter( DcCsiParameters::BRANCH_NUMBER, DStringA(Para2) );
      executeCsiProcess( DcCsiProcesses::BRANCH_INFORMATION ); 
      return;
   }

   if( DlgSel == _SALES_REP_INFORMATION )
   {
      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::BrokerCode, Para1 );
      Para1.stripAll();
      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::BranchCode, Para2 );
      Para2.stripAll();
      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::SalesRepCode, Para3 );
      Para3.stripAll();
      setCsiParameter( DcCsiParameters::BROKER_NUMBER, DStringA(Para1) );
      setCsiParameter( DcCsiParameters::BRANCH_NUMBER, DStringA(Para2) );
      setCsiParameter( DcCsiParameters::SALES_REP_NUMBER, DStringA(Para3) );
      executeCsiProcess( DcCsiProcesses::SALES_REP_INFORMATION );    
      return;
   }


   if( DlgSel == _TRANSACTION_PROCESSING_MENU )
   {
      executeCsiProcess( DcCsiProcesses::TRANSACTION_PROCESSING_MENU ); 
      return;
   }
   if( DlgSel == _SETTLEMENTS )
   {
      executeCsiProcess( DcCsiProcesses::SETTLEMENTS );     
      return;
   }
   switch( DlgSel )
   {
      case -1:
         break;

      default:  // launch dlg
         try
         {
            E_COMMANDRETURN eRtn;
            SetMessageStatusBar( TXT_LOADING_GUI );
            eRtn = getParentProcess()->invokeProcessFromChild( this, LPCTSTR( szCmd[DlgSel]), PROC_SUPPORT );
            SetMessageStatusBar( NULL_STRING );

            switch( eRtn )
            {
               case CMD_OK:
               case CMD_CANCEL:
               case CMD_MODELESS_INPROCESS:
                  break;
               default:
                  // Display error
                  ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
                  break;
            }
         }
         catch( ConditionException &ce )
         {
            ConditionMessageBox( ce );
         }
         catch( ... )
         {
            DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
         }
   }
}

/***********************************************************************/

void MatchTransferDlg::OnBtnAdmDates() 
{
   // TODO: Add your control notification handler code here
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnAdmDates() " ) );

   DString str;
   DString ModUser,ModDate,ProcUser,ProcessDate;

   getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::ModDate, ModDate );
   ModDate.stripAll();
   getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::CancelUser, ModUser );
   ModUser.stripAll();
   getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::ProcessDate, ProcessDate );
   ProcessDate.stripAll();
   getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::OrderUser, ProcUser );
   ProcUser.stripAll();

   setParameter(MODUSER, ModUser );
   setParameter(MODDATE, ModDate );
   setParameter(PROCESSDATE, ProcessDate );
   setParameter(PROCESSUSER, ProcUser );

   try
   {
      bool bModal = true;   
      E_COMMANDRETURN eRtn = CMD_OK;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ADMINDATES, PROC_NO_TYPE, bModal, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}


//**********************************************************************************
bool MatchTransferDlg::GetDataForControl(
                                        UINT controlID,
                                        DString &strValueOut,
                                        bool bFormatted,
                                        int index
                                        ) const
{    
   DString dstrFundCode, dstrClassCode;
   switch( controlID )
   {
      
      case IDC_TXT_FUND_NUMBER:

         getParent()->getField(this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::rxFundCode, dstrFundCode);
         getParent()->getField(this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::rxClassCode, dstrClassCode);
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber( dstrFundCode, dstrClassCode, strValueOut );
         break;

      case IDC_EDIT_FUNDLONGNAME:

         getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::rxFundCode, dstrFundCode );
         getParent()->setCurrentListItem( this, IFASTBP_PROC::FUNDMASTER_LIST, dstrFundCode.upperCase() );
         getParent()->getField( this, IFASTBP_PROC::FUNDMASTER_LIST, ifds::ElongName1/*FUND_NAME*/, strValueOut );
         break;

      default :
         return(false);
   }     
   return(true);
}

//**********************************************************************************
bool MatchTransferDlg::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{  

   TRACE_METHOD( CLASSNAME, I_("doRefresh"));

   getParameter( MATCHTRANSFER::SHAREHOLDERNUM, m_dstrShareHoldNum );
   getParameter( MATCHTRANSFER::ACCOUNTNUM, m_dstrAccountNumber );

   //setTitleBar ( );

   LoadControls();

   return(true);
}


//**********************************************************************************
void MatchTransferDlg::OnDblclkLvAttributes(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnDblclkLvAttributes" ) );

   OnBtnBrowse();

   *pResult = 0;
}

//**********************************************************************************
void MatchTransferDlg::OnClickLvAttributes(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   TRACE_METHOD( CLASSNAME, I_("OnClickLvAttributes"));

   DString dstrCurSelKey = GetList( IDC_LV_ATTRIBUTES )->GetCurrentKey();
   CWnd *tmp = GetDlgItem(IDC_BTN_BROWSE);
   tmp->EnableWindow( WhichDlgShouldBeLaunchedTrans( dstrCurSelKey ) != -1);

   *pResult = 0;
}

//**********************************************************************************
int MatchTransferDlg::WhichDlgShouldBeLaunchedTrans( DString dstrCurSelKey )
{
   DString str;
   procType = PROC_NO_TYPE;

   SetMessageStatusBar( NULL_STRING );

   if (_InquiryOnly.strip() == Y)
      return(-1);

   if( dstrCurSelKey == I_( "UnitPrice" ) )
   {
      SetMessageStatusBar( TXT_BROWSE_FUND_INFO );
      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::rxFundCode, str );
      if( str != CASH )
      {
         str.stripAll().upperCase();
         setParameter( FUNDCODEVALUE,  str ); 
         getParent()->getField( this,  IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::rxClassCode, str );
         str.stripAll().upperCase();
         setParameter( CLASSCODEVALUE, str); 
         getParent()->getField( this,  IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::SettleDate, str, false );
         setParameter( FROMDATEVALUE,  str); 
         setParameter( TODATEVALUE,    str);

         return(FUNDINFO); 
      }
      else
         return(-1);
   }

   // paytype code: 'E' EFT, 'S' System, 'M' Manual, 'X' Suppress
   if( dstrCurSelKey == I_( "PayType" ) )
   {
      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::PayType, str, false );
      str.stripAll().upperCase();

      if( str == I_("E") || str == I_("I") )   // Previously BDEW
      {
         // bank
         SetMessageStatusBar( TXT_BROWSE_BANK );

         DString dstrTradeDate;
         getParent()->getField(this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::TradeDate, dstrTradeDate );
         dstrTradeDate.strip();
//       setParameter( MFCAN_IP_PARAM::TRADE_DATE, dstrTradeDate );
         setParameter( MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::TRANSACTION  );
         setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM,  m_dstrAccountNumber );
         setParameter( MFCAN_IP_PARAM::TRANS_ID,  m_dstrTransId );
         setParameter( MFCAN_IP_PARAM::TRANS_PENDING, I_("T") );
         setParameter( MFCAN_IP_PARAM::PENDING_RID,  NULL_STRING );

         return(BANK_INSTR);
      }

      if( str == I_("M") || str == I_("S") )
      { // cheque
         SetMessageStatusBar( TXT_BROWSE_CHEQUE );
         setParameter( MATCHTRANSFER::TRANSID, m_dstrTransId ); 
         return(CHEQUE);
      }
   }

   if( dstrCurSelKey == I_( "Allocation" ) )
   {
      SetMessageStatusBar( TXT_BROWSE_ALLOCATION );
      getParent()->setParameter( ALLOCATIONSPROC::ALLOCATION_TYPE, 
                                 ALLOCATIONSPROC::TRANSACTION_ONE_TIME );
      setParameter( ALLOCATIONSPROC::PENDING_OR_TRANS_HIST, 
                    ALLOCATIONSPROC::TRANS_HIST ); 
      setParameter( ALLOCATIONSPROC::ACCOUNT_NUM, m_dstrAccountNumber );

      getParent()->getField(this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::TransNum, str );
      setParameter( ALLOCATIONSPROC::TRANS_NUM, str );

      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::TradeDate, str );
      str.strip();
      setParameter( ALLOCATIONSPROC::TRADE_DATE, str );

      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::TransType, str, false );
      str.stripAll();
      setParameter( ALLOCATIONSPROC::TRANS_CODE, str ); 

      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::SettleCurrency, str );
      str.strip();
      setParameter( ALLOCATIONSPROC::SETTLE_CURRENCY, str ); 

      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::SettleCurrency, str, false );
      str.strip();
      setParameter( I_("SettleCurrencyCode"), str ); 

      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::Amount, str );
      str.strip();
      setParameter( ALLOCATIONSPROC::TRANSACTION_AMOUNT, str );

      str = getParent()->getCurrentListItemKey( this, IFASTBP_PROC::MATCHTRANSFER_CBO ); 
      setParameter( TRANSACTION_ALLOCATIONSPROC::PENDING_LIST_CURKEY, str );

      return(TRANSACTION_ALLOCATIONS); // allocation
   }

   if( dstrCurSelKey == I_( "CertRequired" ) )
   {
      DString str;
      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::rxFundCode, str );
      SetMessageStatusBar( TXT_BROWSE_CERTIFICATE );
      setParameter( INACCTNUM  , m_dstrAccountNumber ); 
      setParameter( INFUND  , str.strip()   );
      setParameter( INCERTNUM  , NULL_STRING );
      setParameter( INXREFNUM  , NULL_STRING );
      return(CERTIFICATE); // certificate
   }

   if( dstrCurSelKey == I_( "ConfIssued" ) || dstrCurSelKey == I_( "ConfirmReq" ) )
   {
      if( hasReadPermission( UAF::ADDRESS_BOOK ) ) //, DBR::InqPerm ) )
      {
         SetMessageStatusBar( TXT_BROWSE_ADDRESS_BOOK );
         setParameter( MATCHTRANSFER::ACCOUNTNUM, m_dstrAccountNumber );
         setParameter( MATCHTRANSFER::ENTITYID, m_dstrEntityId );
         return(ADDRESSES); //address book
      }
      else
      {
         return(-1); //disable access to the address book
      }

   }

   if( dstrCurSelKey == I_( "SettleBatch" ) ||
       dstrCurSelKey == I_( "SettleUser" )  ||
       dstrCurSelKey == I_( "SettleTrace" ) )
   {
      SetMessageStatusBar( TXT_BROWSE_SETTLEMENT );
      return(_SETTLEMENTS);
   }

   if( dstrCurSelKey == I_( "OrderBatch" )  || 
       dstrCurSelKey == I_( "OrderTrace" )  ||
       dstrCurSelKey == I_( "OrderUser" )   ||
       dstrCurSelKey == I_( "CancelBatch" ) ||
       dstrCurSelKey == I_( "CancelTrace" ) ||
       dstrCurSelKey == I_( "CancelUser" )  ||
       dstrCurSelKey == I_( "WireOrdNum" ) )
   {
      SetMessageStatusBar( TXT_BROWSE_TRANS_PROCESS );
      return(_TRANSACTION_PROCESSING_MENU);
   }

   if( dstrCurSelKey == I_( "BranchCode" ) || dstrCurSelKey == I_( "BranchName" ) )
   {
      SetMessageStatusBar( TXT_BROWSE_BRANCH_INFO );
      return(_BRANCH_INFORMATION);
   }

   if( dstrCurSelKey == I_( "BrokerCode" ) ||  dstrCurSelKey == I_( "BrokerName" ) )
   {
      SetMessageStatusBar( TXT_BROWSE_BROKER_INFO );
      return(_BROKER_INFORMATION);
   }

   if( dstrCurSelKey == I_( "SalesRepCode" ) || dstrCurSelKey == I_( "SlsrepName" ) )
   {
      SetMessageStatusBar( TXT_BROWSE_SELREP );
      return(_SALES_REP_INFORMATION);
   }

   if( dstrCurSelKey == I_( "SplitComm" ) )
   {
      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::SplitComm, str, false );
      if( str == Y )
      {
         /*str = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::MATCHTRANSFER_CBO);
         setParameter(SPLITCOMM::MAIN_LIST_KEY, str);*/
         setParameter(SPLITCOMM::CALLER, SPLITCOMM::MATCH_TRANSFER);
         setParameter(SPLITCOMM::ACCOUNT_NUM, m_dstrAccountNumber);
         setParameter(SPLITCOMM::MATCH_TRANSACTION_ID, m_dstrTransId);
         procType = PROC_SUPPORT;
         return(SPLITCOMMISSION);
      }

   }

   return(-1);
}

//********************************************************************************************
bool MatchTransferDlg::ListViewControlFilter( const BFFieldId &idSubstitute, const DString *strKey )
{
   bool bRet = true;
   DString str;

   if( idSubstitute == ifds::MatchTransferAttrTop )
   {
      if( *strKey == I_( "Allocation" ) )
      {
         getParent()->getField(this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::Allocation, str );
         str.strip().upperCase();
         if( str == I_( "Y" ) )
            bRet = true;
         else
            bRet = false;
      }
      else if( *strKey == I_( "CancelBatch" ) || *strKey == I_( "CancelTrace" ) || *strKey == I_( "CancelUser" ) )
      {
         DString dstrCancelBatch, dstrCancelTrace;
         getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::CancelBatch, dstrCancelBatch );
         dstrCancelBatch.strip();

         getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, ifds::CancelTrace, dstrCancelTrace );
         dstrCancelTrace.strip('0');
         if( !dstrCancelBatch.empty() && !dstrCancelTrace.empty() )
            bRet = true;
         else
            bRet = false;
      }
      else
      {
         const BFFieldId &idField = BFFieldId::getId( *strKey );
         bRet = DisplayItem( idField );

      }

   }

   return(bRet );
}


//************************************************************************************
bool MatchTransferDlg::DisplayCodeDesc( const BFFieldId &idCode, const BFFieldId &idDesc, DString &strOut )
{
   DString str1,str2;

   getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, idCode, str1, false);
   str1.stripAll();
   if( !str1.empty() )
   {
      getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, idDesc, str2, true);
      str2.stripAll();
      str1 += MINUS + str2;
   }
   if( !str1.empty() )
   {
      strOut = str1;
      return(true);
   }
   else
   {
      return(false);
   }
}

//************************************************************************************
bool MatchTransferDlg::DisplayItem( const BFFieldId &idField )
{
   DString str;
   bool rtn = true;
   getParent()->getField( this, IFASTBP_PROC::MATCHTRANSFER_CBO, idField, str, false);
   str.stripAll();
   if( str.empty() )
   {
      rtn = false;
   }
   return(rtn);

}

//**********************************************************************************
void MatchTransferDlg::OnBtnClose() 
{
   // TODO: Add your control notification handler code here
   PostMessage( WM_COMMAND, IDOK );
}

/***********************************************************************/
void MatchTransferDlg::OnBtnGetAccount()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnGetAccount() " ) );
   CWaitCursor wait;
   try
   {
      E_COMMANDRETURN eRtn = CMD_FAILURE;
	  
	  GenericInterface* snd_rpGIWorkSession = NULL;  
	  GenericInterface * pUserSessionProcess = getWorkSession()->getParent();     

     DSTCWorkSession * dstWorkSession = dynamic_cast<DSTCUserSession *> ( pUserSessionProcess->getBFSession() )->FindWorksessionByAccount( m_dstrAccountNumber );
	  //Check account in existing Worksession? 
	  //get BEUserSession, go through _sessionSet, find account in the account list.
	  if( dstWorkSession )
	  {         
		   //find DSTCWorksession which have this account.
		   GenericInterface *pGI = getGIContainer()->findGI( dstWorkSession, CMD_BPROC_ACC_DETAILS );
		   if( pGI )
		   {
             DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(pGI->getBFSession());
             AccountEntityXref *pAccountEntityXref;
             if( dstWorkSession->getAccountEntityXref( BF::HOST, pAccountEntityXref ) <= WARNING )
             {
                  DString entityId;
                  //get the entity id which is the account holder with sequence 1
                  if( pAccountEntityXref->PopulateAccountOwner( BF::HOST, NULL_STRING, m_dstrAccountNumber ) <= WARNING && 
                      pAccountEntityXref->GetEntityIdForAccountOwnerSequence1( m_dstrAccountNumber, BF::HOST, entityId ) <= WARNING )
                  {
                     pGI->setParameter( I_("AccountNum"), m_dstrAccountNumber );
                     pGI->setParameter( I_("EntityId"), entityId );
                  }
             }             
				 pGI->send( pGI, I_("Lantch AccountDetail") );
             return;
		   }
         else
         {
            snd_rpGIWorkSession = getGIContainer()->findGI( dstWorkSession, CMD_BPROC_WORK_SESSION );
         }
	  }
	  else
	  {		
        int numberOfWS = dynamic_cast<DSTCUserSession *> ( pUserSessionProcess->getBFSession() )->getNumberOfWorksession();
        if( numberOfWS >=5 ) 
        {
           //after Syncup to release58, this message should be defind in resource
           CString message("Can not open more then 5 Sessions");
           AfxMessageBox( message );
           return;
        }

		  if( CommandDispatcher::getInstance()->invokeCommand( pUserSessionProcess,
								  CMD_BPROC_WORK_SESSION, PROC_NO_TYPE, false, &snd_rpGIWorkSession )
				 != CMD_MODELESS_INPROCESS )
		  {  // Error handling
				ASSERT( 0 );
				return;
		  }
	  }

      dstWorkSession = dynamic_cast<DSTCWorkSession *>(snd_rpGIWorkSession->getBFWorkSession());
      AccountEntityXref *pAccountEntityXref;
      if( dstWorkSession->getAccountEntityXref( BF::HOST, pAccountEntityXref ) <= WARNING )
      {
         DString entityId;
         //get the entity id which is the account holder with sequence 1
         if( pAccountEntityXref->PopulateAccountOwner( BF::HOST, NULL_STRING, m_dstrAccountNumber ) <= WARNING && 
             pAccountEntityXref->GetEntityIdForAccountOwnerSequence1( m_dstrAccountNumber, BF::HOST, entityId ) <= WARNING )
         {
            snd_rpGIWorkSession->setParameter( I_("AccountNum"), m_dstrAccountNumber );
            snd_rpGIWorkSession->setParameter( I_("EntityId"), entityId );
            //set the worksession process as a parent for AccDetails
            eRtn = CommandDispatcher::getInstance()->invokeCommand( snd_rpGIWorkSession, 
                                                                    CMD_BPROC_ACC_DETAILS, PROC_NO_TYPE, false, NULL );
            switch( eRtn )
            {
               case CMD_OK:
               case CMD_MODELESS_INPROCESS:
               case CMD_CANCEL:
                  break;
               default:
                  // Display error
                  ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
                  break;
            }
         }
         else
         {
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         }
      }
      else
      {
         // Display error
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return;
}


//*****************************************************************************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MatchTransferDlg.cpp-arc  $
// 
//    Rev 1.22   Sep 15 2005 15:13:56   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.21   Nov 14 2004 15:00:44   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.20   Aug 12 2004 14:29:00   FENGYONG
// PTS 10032837 - limit user open 5 sessions
// 
//    Rev 1.19   May 26 2004 11:03:24   FENGYONG
// PET1046 - FN01 - transfer switch - rel57
// 
//    Rev 1.18   May 11 2004 14:24:50   FENGYONG
// PET1046 FN1 - transfer-switch -Rel57
// 
//    Rev 1.17   Mar 01 2004 09:35:16   HERNANDO
// PTS10027400 - Changed function signature.
// 
//    Rev 1.16   May 23 2003 10:04:34   popescu
// Part of bank instructions cleaning up process, moved the bank types into the ifastids project
// 
//    Rev 1.15   May 22 2003 14:14:06   popescu
// Replaced name 'BankInstr' with 'BankInstructions'; 
// simplified child lists getters for the Shareholder object
// 
//    Rev 1.14   May 13 2003 10:07:28   popescu
// Split commission re-work
// 
//    Rev 1.13   Mar 21 2003 18:38:46   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.12   Mar 03 2003 14:08:54   KOVACSRO
// Added parameter InquiryOnly
// 
//    Rev 1.11   Oct 09 2002 23:55:48   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.10   Aug 29 2002 12:57:24   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.9   May 28 2002 12:19:52   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.8   22 May 2002 19:16:14   PURDYECH
// BFData Implementation
// 
//    Rev 1.7   27 Mar 2002 20:01:16   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.6   Mar 21 2002 20:02:34   HERNANDO
// Added 'Transfer Fund Number' to attributes.
// 
//    Rev 1.5   Jan 28 2002 11:28:44   YINGBAOL
// HLLAPI Changes
// 
//    Rev 1.4   Nov 07 2001 17:58:20   ZHANGCEL
// Haspermission changes
// 
//    Rev 1.3   Sep 14 2001 16:44:30   ZHANGCEL
// Fixed the bug regarding Admin/Date crash
// 
//    Rev 1.2   Sep 07 2001 16:27:04   ZHANGCEL
// Added many new methods 
// 
//    Rev 1.1   Aug 16 2001 14:19:46   ZHANGCEL
// Minal change
// 
//    Rev 1.0   Aug 16 2001 13:57:32   ZHANGCEL
// Initial revision.
 * 
 */



