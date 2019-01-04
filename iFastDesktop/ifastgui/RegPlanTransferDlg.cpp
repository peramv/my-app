//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : RegPlanTransferDlg.cpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ^CLASS    : 
// ^SUBCLASS :    
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
// RegPlanTransferDlg.cpp : implementation file
//

#include "stdafx.h"
#include <algorithm>

#include "mfdstc.h"
#include "RegPlanTransferDlg.h"
#include <ifastbp\RegPlanTransferProcessIncludes.h>
#include <ifastbp\RegPlanTransferProcess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastbp\EntityProcessIncludes.h>
#include <configmanager.hpp>
#include <bfproc\AbstractProcess.hpp>

using std::vector;

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENTITY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_GUARANTEEINFO_BROWSER;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_REG_PLAN_TRANSFER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_USERDEFMAT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SEG_PROCESSING;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_VERSION_FEATURE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_GUARANTEE_FEE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CONTRACT_MATURITY_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SEG_DATES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CONTRACT_OVERRIDE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_EXTERNAL_INSTITUTION_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RegPlanTransferDlg > dlgCreator( CMD_GUI_REG_PLAN_TRANSFER );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//******************************************************************************
// RegPlanTransferDlg dialog

namespace
{   
   const I_CHAR * const CLASSNAME                = I_( "RegPlanTransferDlg" );
   const I_CHAR * const LV_REG_PLAN_TRANSFER     = I_( "RegPlanTransferList" );
   const I_CHAR * const LV_REG_PLAN_TRANSF_ALLOC = I_( "RegPlanTransfAllocList" );
   const I_CHAR * const SPACE_STRING             = I_( " " ); 
   const I_CHAR * const REG_PLAN_TRANSFER        = I_("RegPlanTransfer");
   const I_CHAR * const FUND_CODE                = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE               = I_( "ClassCode" );
   const I_CHAR * const FUNDNUMBER               = I_( "FundNumber" );
   const I_CHAR * const YES                      = I_( "Y" );
   const I_CHAR * const NO                       = I_( "N" );

}

namespace CND
{  
   // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
   extern const long GUI_INVALID_CONTRACT_TYPE;
   extern const long GUI_INVALID_POLICY;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForDofBirth;

   // Take these out as soon as we have them in the view
   extern CLASS_IMPORT const BFDateFieldId GWOCotAnnivDate;
   extern CLASS_IMPORT const BFDateFieldId UserDefinedMaturityDate;
   extern CLASS_IMPORT const BFTextFieldId GuaranteeCalcByRules;
   extern CLASS_IMPORT const BFTextFieldId RegPlanTransferHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId RegPlanTransfAllocHeadingSet;
   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const REG_PLAN_TRANSFER;
}

namespace CONTROL_GROUP
{   
   // group of controls with fields part of a Account Information,
   // always display whether contract information will be loaded or not
   const UINT ACCOUNT_INFORMATION_GROUP   = 1;   
}


//******************************************************************************
RegPlanTransferDlg::RegPlanTransferDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( RegPlanTransferDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
_bIsNew ( false ), m_uiClassCodeDialogItem(0)
{
   //{{AFX_DATA_INIT(RegPlanTransferDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
void RegPlanTransferDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(RegPlanTransferDlg)
   DDX_Control(pDX, IDC_CHK_ONLY_ACTIVE, m_ckbActiveOnly);
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(RegPlanTransferDlg, BaseMainDlg)
//{{AFX_MSG_MAP(RegPlanTransferDlg)
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
ON_NOTIFY( NM_KILLFOCUS, IDC_DTP_EFF_DATE, OnKillfocusDtpEffDate )
ON_BN_CLICKED( IDADD, OnAdd )
ON_BN_CLICKED( IDC_BTN_COPY, OnCopy)
ON_BN_CLICKED( IDDEL, OnDel )
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
ON_BN_CLICKED( IDC_BTN_ADD_FUND_ALLOC, OnBtnAddAlloc)
ON_BN_CLICKED( IDC_BTN_DELETE_FUND_ALLOC, OnBtnDeleteAlloc)
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore)
ON_MESSAGE (UM_OPENEXTERNALINSTITUTION, OpenExternalInstitutionSearchDlg)
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_BN_CLICKED (IDC_CHK_ONLY_ACTIVE, OnChkActiveOnly)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
SEVERITY RegPlanTransferDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   m_bNewCopyAdded = false;
   SEVERITY sevRtn = SEVERE_ERROR;

   getParameter( REG_PLAN_TRANSFER::ACCOUNT_NUMBER, m_dstrAccountNumber );
   getParameter( REG_PLAN_TRANSFER::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   
   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************
BOOL RegPlanTransferDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   setTitleBar ( );
   return(TRUE);  // return TRUE unless you set the focus to 
}

//******************************************************************************
void RegPlanTransferDlg::setTitleBar ( )
{
   m_dstrShareHoldNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();
   m_dstrAccountNumber.stripLeading(I_CHAR('0')).stripTrailing();
   
   if(m_dstrAccountNumber.empty())
   {
      getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO,ifds::AccountNum,m_dstrAccountNumber,false);
      m_dstrAccountNumber.stripLeading(I_CHAR('0')).stripTrailing();
   }
   
   if(m_dstrShareHoldNum.empty())
   {
      getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO,ifds::ShrNum,m_dstrShareHoldNum,false);
      m_dstrShareHoldNum.stripLeading(I_CHAR('0')).stripTrailing();
   }

   SetAccount( m_dstrAccountNumber );

   DString dstrEntityName;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
      getFirstSequenced01AccountholderEntityName(getDataGroupId(),
                                                 m_dstrAccountNumber,dstrEntityName);

   SetShrAcctCaption(m_dstrShareHoldNum, m_dstrAccountNumber, dstrEntityName);
}

//******************************************************************************
void RegPlanTransferDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode(UAF::REG_PLAN_TRANSFER);   

   addBtnAddForPermissionCheck(IDADD, IDC_LV_REG_PLAN_TRANSFERS);
   addBtnAddForPermissionCheck(IDC_BTN_COPY, IDC_LV_REG_PLAN_TRANSFERS);
   addBtnAddForPermissionCheck(IDC_BTN_RESET, IDC_LV_REG_PLAN_TRANSFERS);
   addBtnAddForPermissionCheck(IDC_BTN_ADD_FUND_ALLOC, IDC_LV_REG_PLAN_TRANSFERS_ALLOC);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_FUND_ALLOC, IDC_LV_REG_PLAN_TRANSFERS_ALLOC);


   // Populate dialog    
   //bEffDateChanged = false;

   AddListControl( CLASSNAME, IDC_LV_REG_PLAN_TRANSFERS,       LV_REG_PLAN_TRANSFER,     ifds::RegPlanTransferHeadingSet,    IFASTBP_PROC::REG_PLAN_TRANSFER_LIST,0, true);
   AddListControl( CLASSNAME, IDC_LV_REG_PLAN_TRANSFERS_ALLOC, LV_REG_PLAN_TRANSF_ALLOC, ifds::RegPlanTransfAllocHeadingSet, IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST,IDC_LV_REG_PLAN_TRANSFERS, true);


   AddControl( CTRL_EDIT, IDC_EDT_INST_CODE,        IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::ExternalInstitution,     0, IDC_LV_REG_PLAN_TRANSFERS);
   AddControl( CTRL_EDIT, IDC_EDT_INSTITUTION_NAME, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::ExternalInstitutionName, 0, IDC_LV_REG_PLAN_TRANSFERS);
   AddControl( CTRL_EDIT, IDC_EDT_RELINQ_ACCT_NUM,  IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::ExternalInstitutionAcct, 0, IDC_LV_REG_PLAN_TRANSFERS);
   AddControl( CTRL_EDIT, IDC_EDT_AMOUNT,           IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::ExpectedAmt,             0, IDC_LV_REG_PLAN_TRANSFERS);
   AddControl( CTRL_EDIT, IDC_EDT_AMOUNT_RECEIVED,  IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::ActualAmount,            0, IDC_LV_REG_PLAN_TRANSFERS);

   AddControl( CTRL_COMBO, IDC_CMB_ALLOC_TYPE,      IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::AmountTypeAlloc,        CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_REG_PLAN_TRANSFERS);

   AddControl( CTRL_DATE, IDC_DTP_INITIATION_DATE,  IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::InitiationDate,          0, IDC_LV_REG_PLAN_TRANSFERS);
   AddControl( CTRL_DATE, IDC_DTP_CLOSED_DATE,      IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::ClosedDate,              0, IDC_LV_REG_PLAN_TRANSFERS);
   AddControl( CTRL_COMBO,IDC_CMB_STATUS,           IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::RegTransferStatus,      CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_REG_PLAN_TRANSFERS);

   AddControl( CTRL_EDIT, IDC_EDT_FUND_NUMBER,      IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, ifds::FundNumber,        0, IDC_LV_REG_PLAN_TRANSFERS_ALLOC);
   AddControl( CTRL_EDIT, IDC_EDT_FUND,             IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, ifds::FundCode,          0, IDC_LV_REG_PLAN_TRANSFERS_ALLOC);
   AddControl( CTRL_EDIT, IDC_EDT_CLASS,            IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, ifds::ClassCode,         0, IDC_LV_REG_PLAN_TRANSFERS_ALLOC);
   AddControl( CTRL_EDIT, IDC_EDT_FUND_PERCENT,     IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, ifds::Percentage,        0, IDC_LV_REG_PLAN_TRANSFERS_ALLOC);
   AddControl( CTRL_EDIT, IDC_EDT_FUND_AMT,         IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, ifds::Amount,            0, IDC_LV_REG_PLAN_TRANSFERS_ALLOC);
   AddControl( CTRL_EDIT, IDC_EDT_COMM_RATE,        IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, ifds::Commission,        0, IDC_LV_REG_PLAN_TRANSFERS_ALLOC);

   AddControl( CTRL_STATIC, IDC_TXT_FUND_TOTAL_PRC_VAL, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD, IDC_LV_REG_PLAN_TRANSFERS_ALLOC );
   AddControl( CTRL_STATIC, IDC_TXT_FUND_TOTAL_AMT_VAL, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD, IDC_LV_REG_PLAN_TRANSFERS_ALLOC );


   LoadListControl(IDC_LV_REG_PLAN_TRANSFERS);
//   LoadControls(IDC_LV_REG_PLAN_TRANSFERS);

   DString strIsDuringNASU;
   //getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST,ifds::IsDuringNASU,strIsDuringNASU,false);
   strIsDuringNASU.strip().upperCase();

   bool bEnableBtn = strIsDuringNASU==I_("Y")?false:true;

   doRefresh(this, NULL_STRING);
   
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   //GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::CONTRACTINFO_LIST ) );
}




//******************************************************************************
void RegPlanTransferDlg::OnBtnAdmDates() 
{
   // TODO: Add your control notification handler code here
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnAdmDates() " ) );
   ShowAdminDates( IFASTBP_PROC::REG_PLAN_TRANSFER_LIST );
}

//******************************************************************************
void RegPlanTransferDlg::OnBtnReset() 
{
   ResetListItem(IDC_LV_REG_PLAN_TRANSFERS);
   m_ckbActiveOnly.SetCheck (0);
   //m_ckbActiveOnly.SetCheck (0);
   //OnChkActiveOnly ();
}

//******************************************************************************
bool RegPlanTransferDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
{
   dstrOut = I_( "" );

   bool bReturn = false;
   if( lSubstituteId == ifds::MultiContractsListHeading.getId() )
   {
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );

      DString Date = GetConfigValueAsString( dstrConfiguration,
                                             dstrKey );

      Date.replace(Date.find(I_("MM")), 2, I_("MM/"));
      Date.replace(Date.find(I_("dd")), 2, I_("dd/"));
      
      Date.replace(Date.find(I_("MM")), 2, I_("12"));
      Date.replace(Date.find(I_("dd")), 2, I_("31"));
      Date.replace(Date.find(I_("yyyy")), 4, I_("9999"));

      DString strFieldValue;
      if( dstrColumnKey == I_("EffectiveDate" ) )
      {
         //getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::EffectiveDate, strFieldValue, false );
         
         if(strFieldValue.strip().empty())
         {
            bReturn = true;
            dstrOut = Date;
         }
         else
         {
            bReturn = false;
         }
      }
      else if( dstrColumnKey == I_("IssueDate" ) )
      {
         //getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::IssueDate, strFieldValue, false);
         
         if(strFieldValue.strip().empty())
         {
            bReturn = true;
            dstrOut = Date;
         }
         else
         {
            bReturn = false;
         }
      }
      else if( dstrColumnKey == I_("ContractMaturityDate" ) )
      {
         //getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractMaturityDate, strFieldValue, false);
         
         if(strFieldValue.strip().empty())
         {
            bReturn = true;
            dstrOut = Date;
         }
         else
         {
            bReturn = false;
         }
      }
   }

   return(bReturn);
}




//******************************************************************************
bool RegPlanTransferDlg::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{
   TRACE_METHOD( CLASSNAME, I_("doRefresh"));
   
   DString strOrgCommand(szOriginalCommand);

   //getParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber );
   //getParameter( CONTRACT::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   //getParameter( CONTRACT::TRANSID_EMPTY, m_dstrTransIdEmpty );

   setTitleBar ( );
   
   int iItemNumber = 0;
   iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   if( iItemNumber != 0 )
   {
      ConnectControlsToData(IDC_LV_REG_PLAN_TRANSFERS);
      LoadListControl(IDC_LV_REG_PLAN_TRANSFERS);
      LoadControls(IDC_LV_REG_PLAN_TRANSFERS);

      GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( false );
   }
   else
   {
      AddToListControl (IDC_LV_REG_PLAN_TRANSFERS);

      GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( false );
      GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( false );
   }   
   
   return(true);
}

//******************************************************************************
bool RegPlanTransferDlg::GetDataForControl(UINT controlID,
                                        DString &strValueOut,
                                        bool bFormatted,
                                        int index ) const
{
   boolean retVal = false;
   strValueOut=NULL_STRING;
   DString dstr, dstr2;
   CString cstrMonthDay, cstrYear;
   int idx = 0;

   switch( controlID )
   {
      
      case IDC_TXT_FUND_TOTAL_PRC_VAL:
         getParent()->getField(this, IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, ifds::TotPercentage, strValueOut);
         retVal = true;
         break;

      case IDC_TXT_FUND_TOTAL_AMT_VAL:
         getParent()->getField(this, IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, ifds::TotAmount, strValueOut);
         retVal = true;
         break;
	}
   strValueOut.strip();
   return retVal;
}


//******************************************************************************
bool RegPlanTransferDlg::SetDataFromControl( UINT controlID,
                                          const DString &strValue,
                                          bool bFormatted,
                                          SEVERITY &sevRtn,
                                          int index )
{
   bool bRtn = false;
   sevRtn = NO_CONDITION;
   return(bRtn);
}

//*******************************************************************************************
void RegPlanTransferDlg::DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   switch( listControlID )
   {
      case IDC_LV_REG_PLAN_TRANSFERS:
         {
            DString dstrIssueDate;
            DString dstrGuaranteeFeeAppl;
            //getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::IssueDate, dstrIssueDate );
            //getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::GuaranteeFeeAppl, dstrGuaranteeFeeAppl);
            dstrGuaranteeFeeAppl.strip().upperCase();
            break;
         }
      default:
         break;
   }
}

//*******************************************************************************************
void RegPlanTransferDlg::UpdateLatestItemStopDate()
{

}

//******************************************************************************
void RegPlanTransferDlg::OnKillfocusDtpEffDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   *pResult = 0;
   //bEffDateChanged = true;
}



//****************************************************************************
void RegPlanTransferDlg::OnAdd() 
{
   AddToListControl( IDC_LV_REG_PLAN_TRANSFERS );
   LoadListControl(IDC_LV_REG_PLAN_TRANSFERS);
   LoadControls(IDC_LV_REG_PLAN_TRANSFERS);
   GetList( IDC_LV_REG_PLAN_TRANSFERS )->SetFocus();
   int iNumItem = GetList( IDC_LV_REG_PLAN_TRANSFERS )->GetItemCount();
   GetList( IDC_LV_REG_PLAN_TRANSFERS )->SetSelection(iNumItem-1);

}

//****************************************************************************
void RegPlanTransferDlg::OnCopy() 
{
   CWaitCursor wait;      
   DString _dstrOrgKey = GetList(IDC_LV_REG_PLAN_TRANSFERS)->GetCurrentKey();
   
   AddToListControl(IDC_LV_REG_PLAN_TRANSFERS);
   DString _dstrDestKey = GetList(IDC_LV_REG_PLAN_TRANSFERS)->GetCurrentKey();
   
   RegPlanTransferProcess* pRegPlanTransferProcess = dynamic_cast<RegPlanTransferProcess*>(getParent());

   pRegPlanTransferProcess->copyData(this, _dstrOrgKey, _dstrDestKey);

   RefreshListItem(IDC_LV_REG_PLAN_TRANSFERS);
   LoadListControl(IDC_LV_REG_PLAN_TRANSFERS, const_cast<DString*>(&_dstrDestKey) );
}
//****************************************************************************
void RegPlanTransferDlg::OnBtnAddAlloc() 
{
   AddToListControl( IDC_LV_REG_PLAN_TRANSFERS_ALLOC );
   LoadListControl(IDC_LV_REG_PLAN_TRANSFERS_ALLOC);
   LoadControls(IDC_LV_REG_PLAN_TRANSFERS_ALLOC);
   GetList( IDC_LV_REG_PLAN_TRANSFERS_ALLOC )->SetFocus();
   int iNumItem = GetList( IDC_LV_REG_PLAN_TRANSFERS_ALLOC )->GetItemCount();
   GetList( IDC_LV_REG_PLAN_TRANSFERS_ALLOC )->SetSelection(iNumItem-1);

}

//*****************************************************************************
void RegPlanTransferDlg::OnDel() 
{  
   DeleteFromListControl( IDC_LV_REG_PLAN_TRANSFERS ); 
   LoadListControl(IDC_LV_REG_PLAN_TRANSFERS);
   LoadControls(IDC_LV_REG_PLAN_TRANSFERS);
   GetList( IDC_LV_REG_PLAN_TRANSFERS )->SetFocus();

}

//*****************************************************************************
void RegPlanTransferDlg::OnBtnDeleteAlloc() 
{  
   DeleteFromListControl(IDC_LV_REG_PLAN_TRANSFERS_ALLOC); 
   LoadListControl(IDC_LV_REG_PLAN_TRANSFERS_ALLOC);
   LoadControls(IDC_LV_REG_PLAN_TRANSFERS_ALLOC);
   GetList(IDC_LV_REG_PLAN_TRANSFERS_ALLOC)->SetFocus();
}


//*****************************************************************************
void RegPlanTransferDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   switch( controlID )
   {

      case IDC_EDT_FUND_PERCENT:
      case IDC_EDT_FUND_AMT:
         LoadControl(IDC_TXT_FUND_TOTAL_PRC_VAL);
         LoadControl(IDC_TXT_FUND_TOTAL_AMT_VAL);
         break;
      case IDC_EDT_AMOUNT:
         LoadListControl(IDC_LV_REG_PLAN_TRANSFERS_ALLOC);
         break;
	}
}

//**********************************************************************************
void RegPlanTransferDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;

   //IFastHistoricalInfo f;
   //f( this, IFASTBP_PROC::CONTRACTINFO_LIST, I_("MULTI") );
}

void RegPlanTransferDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore") );

   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   if( getParent()->performSearch( this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_REG_PLAN_TRANSFERS );   
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_REG_PLAN_TRANSFERS )->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

BOOL RegPlanTransferDlg::PreTranslateMessage( MSG* pMsg ) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus()== GetDlgItem( IDC_EDT_INST_CODE ) )
         PostMessage( UM_OPENEXTERNALINSTITUTION );
      else if( GetFocus() == GetDlgItem( IDC_EDT_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND_NUMBER;
      }
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************************
LRESULT RegPlanTransferDlg::OpenExternalInstitutionSearchDlg (WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("OpenExternalInstitutionSearchDlg"));
   try
   {
      DString tradeKey;

//      tradeKey = getParent ()->getCurrentListItemKey ( this, IFASTBP_PROC::TRADES_LIST);

      setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
      setParameter (MFCAN_IP_PARAM::CALLER,   I_("RegPlanTransfer"));

      switch (getParentProcess()->invokeProcessFromChild ( this, CMD_BPROC_EXTERNAL_INSTITUTION_SEARCH, PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString extInstitutionCode;

               getParameter (I_("ExternalInstitution"), extInstitutionCode);
               if (!extInstitutionCode.empty ())
               {
                  getParent()->setField ( this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::ExternalInstitution, extInstitutionCode, false);
                  LoadControl(IDC_EDT_INST_CODE);
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox ( FRAMEBELOW (), GETHIGHESTSEVERITY ());
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
   return 0;
}

LRESULT RegPlanTransferDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );
   DString strMarket = DSTCommonFunctions::getMarket();

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;      

      // Set FUND Code for Fund Dialog
      switch( m_uiClassCodeDialogItem )
      {
         case IDC_EDT_FUND:
            {
               CString cstrFundCode;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundCode );
               DString dstrFundCode = cstrFundCode;
               setParameter( FUND_CODE, dstrFundCode );
               setParameter( CLASS_CODE, NULL_STRING );
               setParameter( FUNDNUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_CLASS:
            {
               CString cstrFundClass;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundClass );
               DString dstrFundClass = cstrFundClass;
               setParameter( FUND_CODE, NULL_STRING );
               setParameter( CLASS_CODE, dstrFundClass );
               setParameter( FUNDNUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_FUND_NUMBER:
            {
               CString cstrFundNumber;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundNumber );
               DString dstrFundNumber = cstrFundNumber;
               setParameter( FUND_CODE, NULL_STRING );
               setParameter( CLASS_CODE, NULL_STRING );
               setParameter( FUNDNUMBER, dstrFundNumber );
            }
            break;
      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;
               getParameter ( FUND_CODE, dstrFundCode );
               getParameter ( CLASS_CODE, dstrClassCode );

               DString strMarket = DSTCommonFunctions::getMarket();
               if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
               {
                  getParameter ( FUNDNUMBER, dstrFundNumber );
                  if( dstrFundCode == NULL_STRING && dstrClassCode == NULL_STRING )
                     dstrFundNumber = NULL_STRING;
               }

               getParent()->setField (this, IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, ifds::FundCode, dstrFundCode );
               getParent()->setField (this, IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, ifds::ClassCode, dstrClassCode );
               getParent()->setField (this, IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, ifds::FundNumber, dstrFundNumber );
               LoadControl ( IDC_EDT_FUND );
               LoadControl ( IDC_EDT_CLASS );
                  LoadControl ( IDC_EDT_FUND_NUMBER );
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

bool RegPlanTransferDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
   if( lSubstituteId == ifds::RegPlanTransferHeadingSet.getId() )
   {
      return m_ckbActiveOnly.GetCheck() == 1 ? !isCurrentRegPlanTransferRecordInactive() : true;
   }
   else if (lSubstituteId == ifds::RegPlanTransfAllocHeadingSet.getId())
   {
      DSTListCtrl *rpList = GetList (IDC_LV_REG_PLAN_TRANSFERS);

      if (m_ckbActiveOnly.GetCheck() == 1 && rpList && rpList->GetItemCount () == 0)
      {
         return false;
      }
   }
   return true;
}

void RegPlanTransferDlg::OnChkActiveOnly()
{
   if (m_ckbActiveOnly.GetCheck() == 1)
   {
      //if on the last reg transf inactive record we need to add a dummy one, since the inactive record(s) will be removed from display,
      //when the active only check box is checked

      DString areAllRecordsInactive (I_("N"));
      getParent()->getField (this, REG_PLAN_TRANSFER::AreAllRecordsInactive, areAllRecordsInactive, false);
      if (areAllRecordsInactive == I_("Y"))
      {
         AddToListControl (IDC_LV_REG_PLAN_TRANSFERS);
      }
   }
   LoadListControl(IDC_LV_REG_PLAN_TRANSFERS);
}

bool RegPlanTransferDlg::isCurrentRegPlanTransferRecordInactive ()
{
   DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   DString dstrStopDate (NULL_STRING);
   DString dstrRecordStatus (YES);
   DString dstrCurBusDate (NULL_STRING);

   if (pDSTCWorkSession)
   {      
      getParent()->getField (this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::ClosedDate, dstrStopDate, false);
      getParent()->getField (this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::RegTransferStatus, dstrRecordStatus, false);
      pDSTCWorkSession->getOption (ifds::CurrBusDate, dstrCurBusDate, getParent()->getDataGroupId(), false);

      dstrStopDate.strip().upperCase();
      dstrRecordStatus.strip().upperCase();
      dstrCurBusDate.strip().upperCase();
   }
   return DSTCommonFunctions::CompareDates (dstrStopDate, dstrCurBusDate) == DSTCommonFunctions::FIRST_EARLIER || dstrRecordStatus.strip() != I_("1");
}
