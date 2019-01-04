//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2009 by International Financial Data Services, Inc.
//
//******************************************************************************
//
// ^FILE   :InvestorAuthorizationDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : InvestorAuthorizationDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "InvestorAuthorizationDlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>

#include <configmanager.hpp>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcworksession.hpp>
#include <assert.h>
#include <ifastgui\ifasthistoricalinfo.hpp>

#include <ifastbp\InvestorAuthorizationInfoProcessIncludes.h>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;

extern CLASS_IMPORT const I_CHAR* CMD_GUI_INVESTOR_AUTHORIZATION_INFORMATION;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< InvestorAuthorizationDlg > dlgCreator( CMD_GUI_INVESTOR_AUTHORIZATION_INFORMATION ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME            = I_("InvestorAuthorizationDlg");
   const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const NO                   = I_( "N" );
   const I_CHAR * const USER_ACCESS_CODE     = I_( "UserAccessCode" );

   const I_CHAR * const DIRECT_DEPOSIT_BANK  = I_( "37" );
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const INVESTOR_AUTHORIZATION_INFO;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId InvestorAuthorizationHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId HouseBroker;
   extern CLASS_IMPORT const BFTextFieldId RepByBranch;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
}

namespace MFCAN_IP_PARAM
{
   extern CLASS_IMPORT const I_CHAR * const BROKER_CODE;
   extern CLASS_IMPORT const I_CHAR * const BRANCH_CODE;
   extern CLASS_IMPORT const I_CHAR * const SALES_REP_CODE;
   extern CLASS_IMPORT const I_CHAR * const DIRCT_DEPST_APPLIC;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
}

namespace AcctUseCode
{
   extern CLASS_IMPORT const I_CHAR * const DIRECT_DEPOSIT;
}

class LVInvestorAuthorizationData : public IFDSListCtrlRowDataBase
{
public:
    virtual ~LVInvestorAuthorizationData() {}
    DString BrokerCode, BranchCode, SlsrepCode, IAFundIndicator, EffectiveDate, StopDate;

    virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
    {
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::BrokerCode, BrokerCode, false );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::BranchCode, BranchCode, false );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::SlsrepCode, SlsrepCode, false);
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::IAFundIndicator, IAFundIndicator );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EffectiveDate, EffectiveDate );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::StopDate, StopDate );
    }
};

class LVInvestorAuthorizationAdapter : public IFDSListCtrlAdapter< LVInvestorAuthorizationData >
{
public:
    // required overrides
    virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2 )
    {
        int result = 0;

        const BFFieldId* pFieldId = pCtrl->getColumnField( iSortColumn - 1 );
        if( 1 == iSortColumn ) {
            // Condition indicator column.  Sort on image index
            result = ( IFDSListBase::getColumnLVItem( lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem( lParam2, iSortColumn - 1)->iImage );
        } else if( NULL == pFieldId ) {
            return( 0 );
        } else if( *pFieldId == ifds::BrokerCode ) {
            result = i_strcmp( pData1->BrokerCode.c_str(), pData2->BrokerCode.c_str() );
        } else if( *pFieldId == ifds::BranchCode ) {
            result = i_strcmp( pData1->BranchCode.c_str(), pData2->BranchCode.c_str() );
        } else if( *pFieldId == ifds::SlsrepCode ) {
            result = i_strcmp( pData1->SlsrepCode.c_str(), pData2->SlsrepCode.c_str() );
        } else if( *pFieldId == ifds::IAFundIndicator ) {
            result = i_strcmp( pData1->IAFundIndicator.c_str(), pData2->IAFundIndicator.c_str() );
        } else if( *pFieldId == ifds::EffectiveDate ) {
            //result = i_strcmp( pData1->EffectiveDate.c_str(), pData2->EffectiveDate.c_str() );
            if ( DSTCommonFunctions::CompareDates (pData1->EffectiveDate, pData2->EffectiveDate) == DSTCommonFunctions::FIRST_EARLIER ) {
               result = -1;
            } else if ( DSTCommonFunctions::CompareDates (pData1->EffectiveDate, pData2->EffectiveDate) == DSTCommonFunctions::EQUAL )  {
               result = 0;
            } else {
               result = 1;
            }
        } else if( *pFieldId == ifds::StopDate ) {
            //result = i_strcmp( pData1->StopDate.c_str(), pData2->StopDate.c_str() );
            if ( DSTCommonFunctions::CompareDates (pData1->StopDate, pData2->StopDate) == DSTCommonFunctions::FIRST_EARLIER ) {
               result = -1;
            } else if ( DSTCommonFunctions::CompareDates (pData1->StopDate, pData2->StopDate) == DSTCommonFunctions::EQUAL )  {
               result = 0;
            } else {
               result = 1;
            }
        }

        return( bAscending ? result : -result );
    }

    virtual LRESULT onGetDispInfo( IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo )
    {
        if( pDispInfo->item.mask & LVIF_TEXT )
        {
            const BFFieldId* pFieldId = pCtrl->getColumnField( pDispInfo->item.iSubItem );

            if( NULL == pFieldId ) {
            pDispInfo->item.pszText = I_( "" );
            } else if( *pFieldId == ifds::BrokerCode ) {
               pDispInfo->item.pszText = (I_CHAR*)pData->BrokerCode.c_str();
            } else if( *pFieldId == ifds::BranchCode ) {
               pDispInfo->item.pszText = (I_CHAR*)pData->BranchCode.c_str();
            } else if( *pFieldId == ifds::SlsrepCode ) {
               pDispInfo->item.pszText = (I_CHAR*)pData->SlsrepCode.c_str();
            } else if( *pFieldId == ifds::IAFundIndicator ) {
               pDispInfo->item.pszText = (I_CHAR*)pData->IAFundIndicator.c_str();
            } else if( *pFieldId == ifds::EffectiveDate ) {
               pDispInfo->item.pszText = (I_CHAR*)pData->EffectiveDate.c_str();
            } else if( *pFieldId == ifds::StopDate ) {
               pDispInfo->item.pszText = (I_CHAR*)pData->StopDate.c_str();
            }
            return( 1 );
        }
        return( 0 );
    }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
InvestorAuthorizationDlg::InvestorAuthorizationDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( InvestorAuthorizationDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_bDialogInit (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(InvestorAuthorizationDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void InvestorAuthorizationDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(InvestorAuthorizationDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(InvestorAuthorizationDlg, BaseMainDlg)
ON_MESSAGE( UM_OPENBROKERLISTDLG, OpenBrokerListDlg )
ON_MESSAGE( UM_OPENBRANCHLISTDLG, OpenBranchListDlg )
ON_MESSAGE( UM_OPENSLSREPLISTDLG, OpenSlsRepListDlg )
//{{AFX_MSG_MAP(InvestorAuthorizationDlg)
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DEL, OnBtnDel )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_BANK, OnBtnBank )
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmin )
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
ON_BN_CLICKED( IDC_RADIO_ALL_FUND_DIRECT_DEPOSIT, OnRadioAllFundDirectDeposit)
ON_BN_CLICKED( IDC_RADIO_TIF_DIRECT_DEPOSIT, OnRadioTIFDirectDeposit)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL InvestorAuthorizationDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog(); 

   return TRUE;
}

//******************************************************************************
void InvestorAuthorizationDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode (UAF::INVESTOR_AUTHORIZATION_INFO); 
   addControlGroupIDForPermissionCheck(0);

   addBtnAddForPermissionCheck (IDC_BTN_ADD, IDC_LV_INVESTOR_AUTHORIZATION_LIST);
   addBtnDeleteForPermissionCheck (IDC_BTN_DEL, IDC_LV_INVESTOR_AUTHORIZATION_LIST);

   IFDSListCtrl* ifdsListInvestorAuthorization = 
      new IFDSAdaptedListCtrl< LVInvestorAuthorizationAdapter >( this, 
                                                                 CLASSNAME, 
                                                                 IDC_LV_INVESTOR_AUTHORIZATION_LIST, 
                                                                 0, 
                                                                 //CTRLFLAG_DEFAULT | LISTFLAG_NOT_AUTO_ADD, 
                                                                 LISTFLAG_NOT_AUTO_ADD , 
                                                                 true /*ShowSelAlways*/, 
                                                                 true /*ShowConditions*/);

   AddIFDSListControl( ifdsListInvestorAuthorization, 
                       I_("INVESTOR_AUTHORIZATION_INFO"), 
                       IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                       ifds::InvestorAuthorizationHeadingSet );   

   // Broker
   AddControl ( CTRL_EDIT, 
                IDC_EDT_BROKER_CODE, 
                IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                ifds::BrokerCode, 
                CTRLFLAG_DEFAULT | CTRLFLAG_AUTO_UPDATE_ON_CHANGE , 
                IDC_LV_INVESTOR_AUTHORIZATION_LIST);
   // Branch
   AddControl ( CTRL_EDIT, 
                IDC_EDT_BRANCH_CODE, 
                IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                ifds::BranchCode, 
                CTRLFLAG_DEFAULT | CTRLFLAG_AUTO_UPDATE_ON_CHANGE , 
                IDC_LV_INVESTOR_AUTHORIZATION_LIST);
   // Sale Rep.
   AddControl ( CTRL_EDIT, 
                IDC_EDT_SLS_REP_CODE, 
                IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                ifds::SlsrepCode, 
                CTRLFLAG_DEFAULT | CTRLFLAG_AUTO_UPDATE_ON_CHANGE , 
                IDC_LV_INVESTOR_AUTHORIZATION_LIST);

    AddControl( CTRL_DATE,
                IDC_DTP_EFFECTIVE_DATE,
                IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO,
                ifds::EffectiveDate,
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                IDC_LV_INVESTOR_AUTHORIZATION_LIST );

    AddControl( CTRL_DATE,
                IDC_DTP_STOP_DATE, 
                IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO,
                ifds::StopDate,
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                IDC_LV_INVESTOR_AUTHORIZATION_LIST );
//the radio buttons...
   AddControl( CTRL_CHECKBOX, 
               IDC_RADIO_ALL_FUND_DIRECT_DEPOSIT, 
               IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
               ifds::IAFundIndicator, 
               CTRLFLAG_DEFAULT, 
               IDC_LV_INVESTOR_AUTHORIZATION_LIST);

   AddControl( CTRL_CHECKBOX, 
               IDC_RADIO_TIF_DIRECT_DEPOSIT, 
               IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
               ifds::IAFundIndicator, 
               CTRLFLAG_DEFAULT, 
               IDC_LV_INVESTOR_AUTHORIZATION_LIST);
                
   AddControl( CTRL_STATIC,   IDC_STC_BROKER_NAME,               CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC,   IDC_STC_BRANCH_NAME,               CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC,   IDC_STC_SLSREP_NAME,               CTRLFLAG_GUI_FIELD );                

   ConnectListToData( IDC_LV_INVESTOR_AUTHORIZATION_LIST, true );
   LoadListControl( IDC_LV_INVESTOR_AUTHORIZATION_LIST );

   //ConnectControlsToData ();
   //LoadControls();

   m_bDialogInit = false;
   
   doRefresh (this, NULL);
}

//*****************************************************************************
SEVERITY InvestorAuthorizationDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   m_bDialogInit = true;

   return NO_CONDITION;
}

//******************************************************************************
void InvestorAuthorizationDlg::OnRadioAllFundDirectDeposit() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnRadioAllFundDirectDeposit" ) );

   getParent()->setField( this, 
                          IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                          ifds::IAFundIndicator, 
                          I_("A"), false);

   LoadListControl(IDC_LV_INVESTOR_AUTHORIZATION_LIST);
}

//******************************************************************************
void InvestorAuthorizationDlg::OnRadioTIFDirectDeposit() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnRadioTIFDirectDeposit" ) );

   getParent()->setField( this, 
                          IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                          ifds::IAFundIndicator, 
                          I_("I"), false);

   LoadListControl(IDC_LV_INVESTOR_AUTHORIZATION_LIST);
}

//******************************************************************************
void InvestorAuthorizationDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString strShrNum, strAccountNum, dstrEntityName;
   CString strName;
   getParent()->getField(this, BF::NullContainerId, ifds::ShrNum, strShrNum, false);
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, strAccountNum, false);

   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
   getFirstSequenced01AccountholderEntityName(getDataGroupId(),
                                             strAccountNum,dstrEntityName);

   SetShrAcctCaption(strShrNum, strAccountNum, dstrEntityName);
}

//************************************************************************
bool InvestorAuthorizationDlg::doRefresh ( GenericInterface * rpGICaller, 
                                           const I_CHAR * szOriginalCommand)
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   SetDlgCaption();

   DSTListCtrl *pPIDSTListCtrl = GetList(IDC_LV_INVESTOR_AUTHORIZATION_LIST);

   if (pPIDSTListCtrl)
   {
      if (pPIDSTListCtrl->GetItemCount() <= 0)
      {
         //add a new row if list is empty, to simulate
         //the normal behaviour
         AddToListControl (IDC_LV_INVESTOR_AUTHORIZATION_LIST);
      }
   }
   return true;
}

//************************************************************************
void InvestorAuthorizationDlg::OnBtnAdmin() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAdmin") );

   ShowAdminDates( IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
}

//******************************************************************************
void InvestorAuthorizationDlg::OnBtnAdd() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAdd"));

   AddToListControl( IDC_LV_INVESTOR_AUTHORIZATION_LIST );
   DSTListCtrl *pPIDSTListCtrl = GetList(IDC_LV_INVESTOR_AUTHORIZATION_LIST);

   assert (pPIDSTListCtrl);
   if (pPIDSTListCtrl)
   {
      pPIDSTListCtrl->SetFocus();
   }
   if (pPIDSTListCtrl && pPIDSTListCtrl->GetItemCount() > 0)
   {
      GetDlgItem (IDC_BTN_ADM_DATES)->EnableWindow (TRUE);
      GetDlgItem (IDC_BTN_HISTORICAL)->EnableWindow (TRUE);
      GetDlgItem (IDC_BTN_RESET)->EnableWindow (TRUE);      
   }
}

//******************************************************************************
void InvestorAuthorizationDlg::OnBtnDel() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnDel"));

   DeleteFromListControl( IDC_LV_INVESTOR_AUTHORIZATION_LIST );
   DSTListCtrl *pPIDSTListCtrl = GetList(IDC_LV_INVESTOR_AUTHORIZATION_LIST);

   assert (pPIDSTListCtrl);
   if (pPIDSTListCtrl)
   {
      pPIDSTListCtrl->SetFocus();
   }

   if (pPIDSTListCtrl && pPIDSTListCtrl->GetItemCount() <= 0)
   {
      ClearControl( IDC_EDT_BROKER_CODE );
      ClearControl( IDC_EDT_BRANCH_CODE );
      ClearControl( IDC_EDT_SLS_REP_CODE);

      ClearControl( IDC_STC_BROKER_NAME );
      ClearControl( IDC_STC_BRANCH_NAME );
      ClearControl( IDC_STC_SLSREP_NAME );
      
      GetDlgItem (IDC_BTN_ADM_DATES)->EnableWindow (FALSE);
      GetDlgItem (IDC_BTN_HISTORICAL)->EnableWindow (FALSE);
      GetDlgItem (IDC_BTN_RESET)->EnableWindow (FALSE);      
   }
}

//******************************************************************************
void	InvestorAuthorizationDlg::DoListItemChanged( UINT ListControlID,
                                                   const DString &strKey, 
                                                   bool bIsNewItem , 
                                                   bool bIsDummyItem)
{
   DString strFundIndicator (NULL_STRING);

   getParent()->getField( this, 
                          IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                          ifds::IAFundIndicator, 
                          strFundIndicator, false);

   bool bSelAllFund = strFundIndicator == I_("A") ? true : false;

   ((CButton* )GetDlgItem (IDC_RADIO_ALL_FUND_DIRECT_DEPOSIT))->SetCheck (bSelAllFund);
   ((CButton* )GetDlgItem (IDC_RADIO_TIF_DIRECT_DEPOSIT))->SetCheck (!bSelAllFund);
}

//******************************************************************************
void InvestorAuthorizationDlg::OnBtnBank()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, 
                          CLASSNAME, 
                          I_( "OnBtnBank" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString strAccountNum;
      getParent()->getField( this, 
                            IFASTBP_PROC::MFACCOUNT_CBO, 
                            ifds::AccountNum, 
                            strAccountNum ); 

      setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::SHAREHOLDER );
      setParameter(USER_ACCESS_CODE,DIRECT_DEPOSIT_BANK);
      setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, strAccountNum );

      //invoke the bank dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BANK_INSTRUCTIONS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               break;
            }
         case CMD_CANCEL:
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

//******************************************************************************
void InvestorAuthorizationDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));

   ResetListItem( IDC_LV_INVESTOR_AUTHORIZATION_LIST );
   GetList( IDC_LV_INVESTOR_AUTHORIZATION_LIST )->SetFocus();
   doRefresh( this, NULL_STRING );
}

//******************************************************************************
void InvestorAuthorizationDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;

   E_COMMANDRETURN eRtn = CMD_CANCEL;
   DString dstrAccountNum;

   getParent()->getField( this, 
                          IFASTBP_PROC::MFACCOUNT_CBO, 
                          ifds::AccountNum, 
                          dstrAccountNum ); 

   setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum);

   IFastHistoricalInfo historicalInfo;
   historicalInfo( this, IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, I_( "SINGLE" ) );
}

//******************************************************************
void InvestorAuthorizationDlg::ControlUpdated ( UINT controlID, 
                                                const DString &strValue)
{
   switch (controlID)
   {
      case IDC_EDT_BROKER_CODE :
         ConnectControlToData(IDC_STC_BROKER_NAME,true);
         LoadControl (IDC_STC_BROKER_NAME);
         break;
      case IDC_EDT_BRANCH_CODE :
         ConnectControlToData(IDC_STC_BRANCH_NAME,true);
         LoadControl (IDC_STC_BRANCH_NAME);
         break;
      case IDC_EDT_SLS_REP_CODE :
         ConnectControlToData(IDC_STC_SLSREP_NAME,true);
         LoadControl (IDC_STC_SLSREP_NAME);
         break;
      default:
         break;
   }
}

//******************************************************************
bool InvestorAuthorizationDlg::GetDataForControl( UINT controlID, 
                                                  DString &strValueOut, 
                                                  bool bFormatted, 
                                                  int index ) const
{
   strValueOut = NULL_STRING;

   switch( controlID )
   {
      case IDC_STC_BROKER_NAME :
         getParent()->getField( this, 
                                IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                                ifds::BrokerName, 
                                strValueOut, 
                                true);
         break;
      case IDC_STC_BRANCH_NAME :
         getParent()->getField( this, 
                                IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                                ifds::BranchName, 
                                strValueOut, 
                                true);
         break;
      case IDC_STC_SLSREP_NAME :
         getParent()->getField( this, 
                                IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                                ifds::SlsrepName, 
                                strValueOut, 
                                true);
         break;

      default :
         return(false);
   }
   return(true);
}

//******************************************************************
BOOL InvestorAuthorizationDlg::PreTranslateMessage( MSG* pMsg ) 
{
   BOOL isTranslated = FALSE;

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4 )
   {
      if( GetFocus()== GetDlgItem( IDC_EDT_BROKER_CODE ) )
      {
         PostMessage( UM_OPENBROKERLISTDLG );
      }
      else if( GetFocus()== GetDlgItem( IDC_EDT_BRANCH_CODE ) )
      {
         PostMessage( UM_OPENBRANCHLISTDLG );
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_SLS_REP_CODE ) )
      {
         PostMessage( UM_OPENSLSREPLISTDLG );
      }
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************
LRESULT InvestorAuthorizationDlg::OpenBrokerListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBrokerListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString brokerCode;

      GetControlText( IDC_EDT_BROKER_CODE, brokerCode );
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString brokerCode;

               getParameter( MFCAN_IP_PARAM::BROKER_CODE, brokerCode );
               if( brokerCode != NULL_STRING )
               {
                  ConnectControlToData(IDC_EDT_BROKER_CODE, false);

                  getParent()->setField ( this, 
                                          IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                                          ifds::BrokerCode, 
                                          brokerCode, 
                                          false);

                  ConnectControlToData(IDC_EDT_BROKER_CODE, true);
                  LoadControl( IDC_EDT_BROKER_CODE );

                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_STC_BROKER_NAME ));
                  if ( pBC )
                  {
                     pBC->Load();
                  }
               }
               break;
            }
         case CMD_CANCEL:
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
   return(0);
}

/*************************************************************************************/
LRESULT InvestorAuthorizationDlg::OpenBranchListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBranchListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString brokerCode;

      GetControlText(IDC_EDT_BROKER_CODE, brokerCode);
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      //invoke the branch dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BRANCH, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the branch code that the user selected from the branch list and 
               //set the field on the account object
               DString branchCode;

               getParameter( MFCAN_IP_PARAM::BRANCH_CODE, branchCode );
               if( !branchCode.empty() )
               {
                  ConnectControlToData(IDC_EDT_BRANCH_CODE, false);

                  getParent()->setField ( this, 
                                          IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                                          ifds::BranchCode, 
                                          branchCode, 
                                          false);

                  ConnectControlToData(IDC_EDT_BRANCH_CODE, true);
                  LoadControl( IDC_EDT_BRANCH_CODE );

                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_STC_BRANCH_NAME ));
                  if ( pBC )
                  {
                     pBC->Load();
                  }
               }
               break;
            }
         case CMD_CANCEL:
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
   return(0);
}

//************************************************************************
LRESULT InvestorAuthorizationDlg::OpenSlsRepListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenSlsRepListDlg" ) );
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString brokerCode, branchCode;

      GetControlText( IDC_EDT_BROKER_CODE, brokerCode );
      setParameter( MFCAN_IP_PARAM::BROKER_CODE, brokerCode );
      GetControlText( IDC_EDT_BRANCH_CODE, branchCode );
      setParameter( MFCAN_IP_PARAM::BRANCH_CODE, branchCode );
      //invoke the agents dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_SLSREP, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the agent code that the user selected from the agents list and 
               //set the field on the account object
               DString slsrepCode, branchCode;

               getParameter(MFCAN_IP_PARAM::SALES_REP_CODE, slsrepCode);
               getParameter(MFCAN_IP_PARAM::BRANCH_CODE, branchCode);

               if( !slsrepCode.empty() )
               {
                  ConnectControlToData(IDC_EDT_SLS_REP_CODE, false);

                  getParent()->setField ( this, 
                                          IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, 
                                          ifds::SlsrepCode, 
                                          slsrepCode, 
                                          false);

                  ConnectControlToData(IDC_EDT_SLS_REP_CODE, true);
                  LoadControl( IDC_EDT_SLS_REP_CODE );

                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_STC_SLSREP_NAME ));
                  if ( pBC )
                  {
                     pBC->Load();
                  }
               }
               break;
            }
         case CMD_CANCEL:
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

   return(0);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastgui/InvestorAuthorizationDlg.cpp-arc  $
// 
//    Rev 1.8   Dec 24 2009 03:22:32   dchatcha
// IN# 1947288 - Delete button enabled in error on Inv Auth screen. Code review,removed logic that usually done by  framework.
// 
//    Rev 1.7   Dec 23 2009 02:41:50   dchatcha
// IN# 1947288 - Delete button enabled in error on Inv Auth screen.
// 
//    Rev 1.6   23 Jul 2009 12:59:06   popescu
// PET156681 FN14 H36 Investor Authorization, some more fixes
// 
//    Rev 1.5   23 Jul 2009 09:40:12   popescu
// Forced a check in to see if my pvcs works
// 
//    Rev 1.4   Jul 23 2009 08:45:48   dchatcha
// PET156681 FN14 H36 Investor Authorization, fix on error after delete all IA records.
// 
//    Rev 1.3   22 Jul 2009 18:09:24   popescu
// PET156681 FN14 H36 Investor Authorization - clean-up various fixes.
// 
//    Rev 1.2   Jul 16 2009 18:47:26   dchatcha
// PET156681 FN14 H36 Investor Authorization, Code Review.
// 
//    Rev 1.1   Jul 10 2009 14:26:12   dchatcha
// PET156681 FN14 H36 Investor Authorization, Code review.
// 
//    Rev 1.0   Jul 09 2009 13:17:20   dchatcha
// Initial revision.
//
