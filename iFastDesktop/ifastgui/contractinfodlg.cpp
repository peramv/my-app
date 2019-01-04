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
// ^FILE   : ContractInfoDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
// ^SUBCLASS :    
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
// ContractInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include <algorithm>

#include "mfdstc.h"
#include "ContractInfoDlg.h"
#include <ifastbp\ContractInfoProcessIncludes.h>
#include <ifastbp\ContractMaturityInstructionsProcessIncludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastbp\EntityProcessIncludes.h>
#include <configmanager.hpp>

using std::vector;

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENTITY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_GUARANTEEINFO_BROWSER;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_CONTRACTINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_USERDEFMAT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SEG_PROCESSING;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_VERSION_FEATURE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_GUARANTEE_FEE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CONTRACT_MATURITY_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SEG_DATES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CONTRACT_OVERRIDE;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ContractInfoDlg > dlgCreator( CMD_GUI_CONTRACTINFO );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//******************************************************************************
// ContractInfoDlg dialog

namespace
{   
   const I_CHAR * const CLASSNAME      = I_( "ContractInfoDlg" );
   const I_CHAR * const LV_CONTRACT    = I_( "ContractInfoList" );
   const I_CHAR * const TERM           = I_( "ContractTerm" );
   const int MONTH                     = 13;
   const I_CHAR * const SPACE_STRING   = I_( " " ); 
}

static CString InttoMonth[MONTH] =
{
   CString(_T("")),
   CString(_T("January")),
   CString(_T("February")),
   CString(_T("March")),
   CString(_T("April")),
   CString(_T("May")),
   CString(_T("June")),
   CString(_T("July")),
   CString(_T("August")),
   CString(_T("September")),
   CString(_T("October")),
   CString(_T("November")),
   CString(_T("December"))
};

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
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_MULTI_CONTRACT;
   extern CLASS_IMPORT I_CHAR * const SEG_FORCE_TRANSACTION;
   extern CLASS_IMPORT I_CHAR * const GUARANTEE_INFORMATION;
}

namespace CONTROL_GROUP
{   
   // group of controls with fields part of a Account Information,
   // always display whether contract information will be loaded or not
   const UINT ACCOUNT_INFORMATION_GROUP   = 1;   
}

bool CompareItemPtr ( const EffectiveDateSort1* pLeft, EffectiveDateSort1* pRight)
{
   return( *pLeft) <= ( *pRight );
}

//******************************************************************************
ContractInfoDlg::ContractInfoDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ContractInfoDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
_bIsNew ( false )
{
   //{{AFX_DATA_INIT(ContractInfoDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
void ContractInfoDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ContractInfoDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(ContractInfoDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ContractInfoDlg)
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
ON_BN_CLICKED( IDC_BTN_ENTITY, OnBtnEntity )
ON_BN_CLICKED( IDC_BTN_GUARANTEE, OnBtnGuarantee )
ON_BN_CLICKED( IDC_BTN_USERDEFMAT, OnBtnUserDefMat )
ON_BN_CLICKED( IDC_BTN_FEATURE_OPT, OnBtnFeatureOpt )
ON_BN_CLICKED( IDC_BTN_CONT_MAT_INTR, OnBtnContractMaturityInstr )
ON_BN_CLICKED( IDC_BTN_SEG_PROCESSING, OnBtnSEGProcessing )
ON_BN_CLICKED( IDC_BTN_GUARANTEE_FEE, OnBtnGuaranteeFee )
ON_BN_CLICKED( IDC_BTN_SEG_DATES, OnBtnSEGDates )
ON_BN_CLICKED( IDC_BTN_OVERRIDE, OnBtnOverride )
ON_NOTIFY( NM_KILLFOCUS, IDC_DTP_EFF_DATE, OnKillfocusDtpEffDate )
ON_BN_CLICKED( IDADD, OnAdd )
ON_BN_CLICKED( IDDEL, OnDel )
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
SEVERITY ContractInfoDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   m_bNewCopyAdded = false;
   SEVERITY sevRtn = SEVERE_ERROR;

   getParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber );
   getParameter( CONTRACT::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   getParameter( CONTRACT::TRANSID_EMPTY, m_dstrTransIdEmpty );

   // get folowing parameters for DofBirth checking
   getParameter( CONTRACT::OWNER_NAME, m_dstrOwnerName );
   getParameter( CONTRACT::SPOUSE_NAME, m_dstrSpouseName );
   getParameter( CONTRACT::ASK_SPOUSE_DOFBIRTH, m_dstrAskDofBirthSp );
   getParameter( CONTRACT::ASK_ENTITY_DOFBIRTH, m_dstrAskDofBirthEntity );

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************
BOOL ContractInfoDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   setTitleBar ( );
   return(TRUE);  // return TRUE unless you set the focus to 
}

//******************************************************************************
void ContractInfoDlg::setTitleBar ( )
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
void ContractInfoDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode(UAF::SEG_FUND_MULTI_CONTRACT);   
   addBtnAddForPermissionCheck(IDADD, IDC_LV_CONTRACT);
   addBtnDeleteForPermissionCheck(IDDEL, IDC_LV_CONTRACT);


   // Populate dialog    
   //bEffDateChanged = false;
   AddControl( CTRL_STATIC, IDC_STC_ACCT_GROUP, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AcctGroupName,
               0, CONTROL_GROUP::ACCOUNT_INFORMATION_GROUP );
   AddControl( CTRL_STATIC, IDC_STC_ACCT_STAT, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AcctStatus,
               0, CONTROL_GROUP::ACCOUNT_INFORMATION_GROUP  );
   AddControl( CTRL_STATIC, IDC_TXT_ACCT_TYPE, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AcctType,
               0, CONTROL_GROUP::ACCOUNT_INFORMATION_GROUP  );
   AddControl( CTRL_STATIC, IDC_TXT_TAX_TYPE, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType,
               0, CONTROL_GROUP::ACCOUNT_INFORMATION_GROUP  );
   AddControl( CTRL_DATE, IDC_TXT_ANNIV_DATE, IFASTBP_PROC::MFACCOUNT_CBO, ifds::DateOfReg,
               0, CONTROL_GROUP::ACCOUNT_INFORMATION_GROUP  );

   AddListControl( CLASSNAME, 
                   IDC_LV_CONTRACT, 
                   LV_CONTRACT, 
                   ifds::MultiContractsListHeading, 
                   IFASTBP_PROC::CONTRACTINFO_LIST,
                   0, 
                   true);
   GetList( IDC_LV_CONTRACT )->SortOnColumn(1);

   AddControl( CTRL_COMBO, IDC_CMB_CONTRACT_TYPE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractType,
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT  );

   AddControl( CTRL_STATIC, IDC_STC_CONTRACT_VERSION, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractVer,
               0, IDC_LV_CONTRACT  );
               
   AddControl( CTRL_COMBO, IDC_CMB_CONTRACT_STATUS, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::Status,
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT  );

   AddControl( CTRL_DATE, IDC_DTP_EFF_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::EffectiveDate,
               0, IDC_LV_CONTRACT);
   AddControl( CTRL_DATE, IDC_DTP_STOP_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::StopDate, 
               0, IDC_LV_CONTRACT);

   AddControl( CTRL_STATIC, IDC_TXT_TYPEID, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractTypeId,
               0, IDC_LV_CONTRACT  );

   AddControl( CTRL_STATIC, IDC_TXT_POLICY_NUMBER, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::PolicyNum,
               0, IDC_LV_CONTRACT  );
   AddControl( CTRL_COMBO, IDC_CMB_MATURE_DATE_BASED_ON, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractMatBasedOn, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT);
   AddControl( CTRL_EDIT, IDC_EDT_CLS_TERM, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ClsPerTerm,
               0, IDC_LV_CONTRACT);
   AddControl( CTRL_EDIT, IDC_EDT_TERM, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractTerm,
               0, IDC_LV_CONTRACT);
   AddControl( CTRL_DATE, IDC_TXT_CONTRACT_ISSUE_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::IssueDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_STATIC, IDC_TXT_GWO_CONTRACT_ANNIV_MONTH, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::AnnivMonth,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_STATIC, IDC_TXT_GWO_CONTRACT_ANNIV_DAY, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::AnnivDay,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_DATE, IDC_TXT_GWO_CONTRACT_ANNIV_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::GWOCotAnnivDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_COMBO, IDC_CMB_PROV_REG, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ProvinceCanada, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT );

// PET1024 FN02
   AddControl( CTRL_DATE, IDC_TXT_CONTRACT_MATURITY_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractMaturityDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_DATE, IDC_TXT_LEGALMATURITY_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::LegalMaturityDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_DATE, IDC_TXT_BAILOUT_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::BailMaturityDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_DATE, IDC_TXT_CLOSINGDECADE_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::CDStartDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_DATE, IDC_TXT_REDUCTIONAGE_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::RedAgeDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_DATE, IDC_TXT_MATURITY_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::RefMatDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_DATE, IDC_TXT_LWA_ELECTION_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::LWAElectDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_STATIC, IDC_TXT_LWA_AGE_USED, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::LWAAgeUsed,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_STATIC, IDC_TXT_LWA_RATE_APPLY, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::LWARateApplied,
               0, IDC_LV_CONTRACT );

   AddControl( CTRL_COMBO, IDC_CMB_SUSPECT_GUAR_TYPE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::SuspectGuarType, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT );
   AddControl( CTRL_COMBO, IDC_CMB_REQ_UNIT_ADJ, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ReqUnitAdj, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT );
   AddControl( CTRL_COMBO, IDC_CMB_AGE_BASEDON, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::AgeBasedOn, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT );
   AddControl( CTRL_DATE, IDC_TXT_LAST_RESET, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::LastResetDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_EDIT, IDC_EDT_COT_VER_DESC, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::VersionDesc,
               CTRLFLAG_NOT_UPDATABLE, IDC_LV_CONTRACT );

//   int iItemNumber = 0;
//   iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::CONTRACTINFO_LIST );
//   if( iItemNumber != 0 )
//   {
//      LoadListControl( IDC_LV_CONTRACT);
//
//      //GetDlgItem( IDC_BTN_ENTITY )->EnableWindow( true );//Cri
//
//      m_bNewCopyAdded = false;
//      //GetDlgItem( IDC_ACC_GR )->EnableWindow( false );
//   }
//
//   else
//   {
////      setParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber ); 
//////      LoadListControl( IDC_LV_CONTRACT);  // When the system executes this function, it adds a new record automaticly
////      DString dstrOrgKey = GetList(IDC_LV_CONTRACT)->GetCurrentKey();
////      getParent()->setField(this, BF::NullContainerId, CONTRACT::ORG_KEY, dstrOrgKey);
////      DString dstrIsAddNew = I_( "Y" );
////      getParent()->setField(this, BF::NullContainerId, CONTRACT::ISADDNEW, dstrIsAddNew);      
//////      m_bNewCopyAdded = true;
//////      getParent()->setField(this, 0, CONTRACT::CHECKDOFBIRTH, I_("Y") );
//      GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( false );
//      GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( false );
//      //LoadContractInfo();
//   }

   DString strIsDuringNASU;
   getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST,ifds::IsDuringNASU,strIsDuringNASU,false);
   strIsDuringNASU.strip().upperCase();

   bool bEnableBtn = strIsDuringNASU==I_("Y")?false:true;
   GetDlgItem( IDC_BTN_GUARANTEE )->EnableWindow( bEnableBtn );
   GetDlgItem( IDC_BTN_GUARANTEE_FEE )->EnableWindow( bEnableBtn );
   GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow( bEnableBtn );
   GetDlgItem( IDC_BTN_FEATURE_OPT )->EnableWindow( bEnableBtn );
   GetDlgItem( IDC_BTN_CONT_MAT_INTR )->EnableWindow( bEnableBtn );
   GetDlgItem( IDC_BTN_SEG_PROCESSING )->EnableWindow( bEnableBtn );

   doRefresh(this, NULL_STRING);
   
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::CONTRACTINFO_LIST ) );

   SetContrMatrInstrBtnState();
}

//******************************************************************************
void ContractInfoDlg::SetContrMatrInstrBtnState()
{
	DString dstrContractType;
	getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractType, dstrContractType, false );

	int iNumItem = GetList( IDC_LV_CONTRACT )->GetItemCount();

	//Checking iNumItem == 1, since in case of no records call to AddToListControl will add a record.
	bool bEnable = true;
	if( iNumItem == 1 && dstrContractType.empty() )
		bEnable = false;
	else if ( iNumItem == 0 || dstrContractType.empty() )
		bEnable = false;

	GetDlgItem( IDC_BTN_CONT_MAT_INTR )->EnableWindow(  bEnable );
}

//******************************************************************************
void ContractInfoDlg::LoadContractInfo()
{
   TRACE_METHOD( CLASSNAME, I_("LoadContractInfo"));

   //GetDlgItem( IDC_ACC_GR )->EnableWindow( false );
   // 
   getParent()->getParameter( CONTRACT::OWNER_NAME, m_dstrOwnerName );
   getParent()->getParameter( CONTRACT::SPOUSE_NAME, m_dstrSpouseName );
   getParent()->getParameter( CONTRACT::ASK_SPOUSE_DOFBIRTH, m_dstrAskDofBirthSp );
   getParent()->getParameter( CONTRACT::ASK_ENTITY_DOFBIRTH, m_dstrAskDofBirthEntity );

   CString cMessage = NULL_STRING;
   CString cMessageSpouse = NULL_STRING;

   if( m_dstrAskDofBirthEntity.stripAll() == I_( "Y" ) )
      cMessage = m_dstrOwnerName.c_str();

   if( m_dstrAskDofBirthSp.stripAll() == I_( "Y" ) )
      cMessageSpouse = m_dstrSpouseName.c_str();

   CString cstrMsg1 = NULL_STRING;
   CString cstrMsg2 = NULL_STRING;
   CString cstrMsg3 = NULL_STRING;
   if( cMessage != NULL_STRING && cMessageSpouse != NULL_STRING )
   {
      cstrMsg1.LoadString(TXT_AND);
      cstrMsg2.LoadString(TXT_HAVE);
      cstrMsg3.LoadString(TXT_CONTACTINFO_INVALID_BIRTHDATE);
      cMessage += SPACE_STRING;
      cMessage += cstrMsg1;
      cMessage += SPACE_STRING;
      cMessage += cMessageSpouse; 
      cMessage += SPACE_STRING;
      cMessage += cstrMsg2;
      cMessage += SPACE_STRING;
      cMessage += cstrMsg3; 
      //GetDlgItem( IDC_BTN_ENTITY )->EnableWindow( true );

   }
   else if( cMessage != NULL_STRING || cMessageSpouse != NULL_STRING )
   {
      cstrMsg2.LoadString(TXT_HAS);
      cstrMsg3.LoadString(TXT_CONTACTINFO_INVALID_BIRTHDATE);

      cMessage += cMessageSpouse;
      cMessage += SPACE_STRING;
      cMessage += cstrMsg2;
      cMessage += SPACE_STRING;
      cMessage += cstrMsg3; 
      //GetDlgItem( IDC_BTN_ENTITY )->EnableWindow( true );
   }

   if( cMessage == NULL_STRING )
   {
      LoadListControl( IDC_LV_CONTRACT);
      //    GetDlgItem( IDC_BTN_ENTITY )->EnableWindow( true );  
      GetDlgItem( IDC_DTP_EFF_DATE )->EnableWindow( true );
      GetDlgItem( IDC_DTP_STOP_DATE )->EnableWindow( true );
      GetDlgItem( IDC_CMB_CONTRACT_STATUS )->EnableWindow( true );
      GetDlgItem( IDC_CMB_PROV_REG )->EnableWindow( true );
      GetDlgItem( IDADD )->EnableWindow( true );
   }
   else
   {
//      GetDlgItem( IDC_BTN_ADD_COPY )->EnableWindow( false );
      GetDlgItem( IDC_DTP_EFF_DATE )->EnableWindow( false );
      GetDlgItem( IDC_DTP_STOP_DATE )->EnableWindow( false );
      GetDlgItem( IDC_CMB_CONTRACT_STATUS )->EnableWindow( false );
      GetDlgItem( IDC_CMB_PROV_REG )->EnableWindow( false );
      //GetDlgItem( IDADD )->EnableWindow( false );
      AfxMessageBox( cMessage ); //, MB_ICONSTOP );
   }
}

//******************************************************************************
void ContractInfoDlg::OnBtnAdmDates() 
{
   // TODO: Add your control notification handler code here
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnAdmDates() " ) );
   ShowAdminDates( IFASTBP_PROC::CONTRACTINFO_LIST );
}

//******************************************************************************
bool ContractInfoDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
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
         getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::EffectiveDate, strFieldValue, false );
         
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
         getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::IssueDate, strFieldValue, false);
         
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
         getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractMaturityDate, strFieldValue, false);
         
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

//*****************************************************************************
void ContractInfoDlg::OnBtnEntity() 
{   
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnEntity"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnEntity() " ) );

   //setParameter( ENTPROC::ACCOUNT_NUM, m_dstrAccountNumber);

   //SetMessageStatusBar( TXT_LOAD_ENTITY );
   //const DString& dstrOrgKey = (getParent()->getCurrentListItemKey(this, IFASTBP_PROC::CONTRACTINFO_LIST));
   //DString dstrCheckDofBirth = I_("Y");
   //try
   //{
   //   bool bModal = false;   // set it to be modeless
   //   E_COMMANDRETURN eRtn;
   //   eRtn = invokeCommand( getParent(), CMD_BPROC_ENTITY, PROC_NO_TYPE, bModal, NULL );
   //   switch( eRtn )
   //   {
   //      case CMD_OK:
   //         // Through setField to call ContractInfoProcess.GetDofBirth() and 
   //         // ContractInfoList.PassDofBirthForCheck() and call ContractInfo.CheckDofBirth() indirectly
   //         setParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber ); // have to set it again, otherwise it will be empty
   //         getParent()->setField(this, BF::NullContainerId, CONTRACT::ORG_KEY, dstrOrgKey);
   //         getParent()->setField(this, BF::NullContainerId, CONTRACT::CHECKDOFBIRTH, dstrCheckDofBirth);

   //         LoadContractInfo();
   //         GetList(IDC_LV_CONTRACT)->SetSelection( &dstrOrgKey);
   //         break;
   //      case CMD_CANCEL:
   //      case CMD_MODELESS_INPROCESS:
   //         break;
   //      default:
   //         // Display error
   //         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
   //         break;
   //   }
   //}
   //catch( ConditionException &ce )
   //{
   //   ConditionMessageBox( ce );
   //}
   //catch( ... )
   //{
   //   DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   //}

   //SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void ContractInfoDlg::OnBtnGuarantee() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnGuarantee"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnGuarantee() " ) );

   setParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber);
   setParameter( CONTRACT::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   SetMessageStatusBar( TXT_LOAD_GUARANTEE );

   CString cstrGuaranteeInfo,
      cstrInfoShr,
      cstrAccountNumLabel;
   cstrGuaranteeInfo.LoadString(TXT_CONTRACT_GUARANTEE);
   cstrInfoShr.LoadString(TXT_SHRHLDR_INFO);
   cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);

   DString dstrEntityName;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
      getFirstSequenced01AccountholderEntityName(getDataGroupId(),
                                                 m_dstrAccountNumber,dstrEntityName);

   DString strBrowserTitle(cstrGuaranteeInfo);
   strBrowserTitle += cstrInfoShr;
   strBrowserTitle += m_dstrShareHoldNum;
   strBrowserTitle += cstrAccountNumLabel;
   strBrowserTitle += m_dstrAccountNumber;
   strBrowserTitle += I_(" ");
   strBrowserTitle += dstrEntityName;

   setParameter( I_("BrowserTitle"), strBrowserTitle);

   DString urlParamsIDI;

   setParameter( I_("from_screen"), I_("ContractInfoDlg") );

   addIDITagValue (urlParamsIDI, I_("AccountNum"), m_dstrAccountNumber);
   addIDITagValue (urlParamsIDI, I_("screen"), I_("GuaranteeInformation"));
   
   setParameter (I_("UrlParams"), urlParamsIDI);

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_GUARANTEEINFO_BROWSER, PROC_NO_TYPE, true, NULL );
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

   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
bool ContractInfoDlg::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{
   TRACE_METHOD( CLASSNAME, I_("doRefresh"));
   
   DString strOrgCommand(szOriginalCommand);

   getParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber );
   getParameter( CONTRACT::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   getParameter( CONTRACT::TRANSID_EMPTY, m_dstrTransIdEmpty );

   setTitleBar ( );
   
   ConnectControlsToData(CONTROL_GROUP::ACCOUNT_INFORMATION_GROUP);
   LoadControls(CONTROL_GROUP::ACCOUNT_INFORMATION_GROUP);
   
   int iItemNumber = 0;
   iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::CONTRACTINFO_LIST );
   if( iItemNumber != 0 )
   {
      ConnectControlsToData(IDC_LV_CONTRACT);
      LoadListControl(IDC_LV_CONTRACT);
      LoadControls(IDC_LV_CONTRACT);

      GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( false );
   }
   else
   {
      AddToListControl (IDC_LV_CONTRACT);

      GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( false );
      GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( false );
   }   
   
   return(true);
}

//******************************************************************************
bool ContractInfoDlg::GetDataForControl(UINT controlID,
                                        DString &strValueOut,
                                        bool bFormatted,
                                        int index ) const
{
   strValueOut=NULL_STRING;
   DString dstr, dstr2;
   CString cstrMonthDay, cstrYear;
   int idx = 0;

   bool bReturn = false;
   //switch( controlID )
   //{
   //   default :
   //      bReturn =false;
   //}     
   return(bReturn);
}

//******************************************************************************
bool ContractInfoDlg::SetDataFromControl( UINT controlID,
                                          const DString &strValue,
                                          bool bFormatted,
                                          SEVERITY &sevRtn,
                                          int index )
{
   bool bRtn = false;
   //DString dstrSubTerm;
   //int iPos;
   //switch( controlID )
   //{
   //   default :
   //      bRtn = false;
   //}
   sevRtn = NO_CONDITION;
   return(bRtn);
}

//*******************************************************************************************
void ContractInfoDlg::DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   switch( listControlID )
   {
      case IDC_LV_CONTRACT:
         {
            DString dstrIssueDate;
            DString dstrGuaranteeFeeAppl;
            getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::IssueDate, dstrIssueDate );
            getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::GuaranteeFeeAppl, dstrGuaranteeFeeAppl);
            dstrGuaranteeFeeAppl.strip().upperCase();

            DString dstrIssueDateNF;
            getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::IssueDate, dstrIssueDateNF, false);
            bool nullIssueDate = dstrIssueDateNF == NULL_STRING || dstrIssueDateNF == I_("12319999");
            if(nullIssueDate)
            {
               GetDlgItem( IDC_BTN_GUARANTEE )->EnableWindow( false );
            }
            else
            {
               bool bEnableGuarantee = hasReadPermission(UAF::GUARANTEE_INFORMATION);
               GetDlgItem( IDC_BTN_GUARANTEE )->EnableWindow( bEnableGuarantee );
            }

            if( nullIssueDate || I_("Y") != dstrGuaranteeFeeAppl)
            {
               GetDlgItem( IDC_BTN_GUARANTEE_FEE )->EnableWindow( false );
            }
            else
            {
               bool bEnableGuarantee = hasReadPermission(UAF::GUARANTEE_INFORMATION);
               GetDlgItem( IDC_BTN_GUARANTEE_FEE )->EnableWindow( bEnableGuarantee ); 
            }

            if(nullIssueDate || bIsNewItem)
            {
               GetDlgItem( IDDEL )->EnableWindow( true );
            }
            else
               GetDlgItem( IDDEL )->EnableWindow( false );

            // PET1024 FN02 - Set User Def Button
            DString ContMatDateBasedOn, MatDateBasedOn;
            const DString *pKey = &( getParent()->getFirstListItemKey( this, IFASTBP_PROC::MASTER_CONTRACT_LIST ) );
            //getParent()->getField( this, BF::NullContainerId, ifds::ContMatDateBasedOn, ContMatDateBasedOn );
            getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractMatBasedOn, ContMatDateBasedOn, false );
            getParent()->getField( this, BF::NullContainerId, ifds::MatDateBasedOn, MatDateBasedOn );
            ContMatDateBasedOn.strip().upperCase();

            bool bEnableUsrDefine = ContMatDateBasedOn == I_("04") || ContMatDateBasedOn == I_("07");
            GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow (bEnableUsrDefine);
            //if ( && bIsNewItem)
            //   GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow (false);
            //else if (ContMatDateBasedOn == I_("04"))
            //   GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow (true);
            //else
            //   GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow( !( ContMatDateBasedOn != I_("02") && MatDateBasedOn != I_( "01" ) ) );

            DString strMaturityID;
            getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::MaturityID, strMaturityID, false );
            strMaturityID.strip().upperCase();

            if(strMaturityID.empty() || strMaturityID == I_("0"))
            {
               GetDlgItem( IDC_BTN_SEG_PROCESSING )->EnableWindow( false );
            }
            else
            {
               GetDlgItem( IDC_BTN_SEG_PROCESSING )->EnableWindow( true );
            }

            DString strEnableSegDates, strEnableOverride;
            getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::EnableSegDates, strEnableSegDates, false);
            getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::EnableOverride, strEnableOverride, false);

            GetDlgItem(IDC_BTN_SEG_DATES)->EnableWindow(strEnableSegDates.stripAll().upperCase() == I_("Y"));
            GetDlgItem(IDC_BTN_OVERRIDE)->EnableWindow(strEnableOverride.stripAll().upperCase() == I_("Y"));

            _bIsNew = bIsNewItem;

            break;
         }
      default:
         break;
   }
}

//*******************************************************************************************
void ContractInfoDlg::UpdateLatestItemStopDate()
{
   //vector<EffectiveDateSort1*> dateList;
   //DString dstrEffDate, dstr;
   //EffectiveDateSort1* pItem;

   //// Keep current item key for resetting
   //DString CurrentKey = getParent()->getCurrentListItemKey( this, IFASTBP_PROC::CONTRACTINFO_LIST );
   //getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::EffectiveDate, dstrEffDate, false );

   //// set vector dateList
   //DString dstrKey = (getParent()->getFirstListItemKey(this, IFASTBP_PROC::CONTRACTINFO_LIST));
   //while( dstrKey != NULL_STRING )
   //{
   //   getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::EffectiveDate, dstr, false );
   //   pItem = new EffectiveDateSort1( dstrKey.stripAll(), dstr.stripAll() );
   //   dateList.push_back( pItem );
   //   dstrKey = (getParent()->getNextListItemKey(this, IFASTBP_PROC::CONTRACTINFO_LIST));
   //}

   //// sort the dateList by EffectiveDate
   //std::sort(dateList.begin(), dateList.end(), CompareItemPtr);

   //// get the latest record and change it's stop date by current record's EffectiveDate - 1
   //std::vector<EffectiveDateSort1*>::iterator iter;
   //iter = dateList.begin();
   //while( iter != dateList.end() )
   //{
   //   if( ( *iter )->key == CurrentKey )
   //      break;
   //   iter ++;
   //}
   //if( iter != dateList.begin() )
   //{
   //   DString dstrEffDateMinusOne;
   //   if( GetEffDateMinusOne( dstrEffDate, dstrEffDateMinusOne ) )
   //   {
   //      iter --;
   //      getParent()->setCurrentListItem( this, IFASTBP_PROC::CONTRACTINFO_LIST, ( *iter )->key );
   //      getParent()->setField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::StopDate, dstrEffDateMinusOne, false);
   //   }
   //}
   //getParent()->setCurrentListItem( this, IFASTBP_PROC::CONTRACTINFO_LIST, CurrentKey);

   //// delete all pointers those are in dateList 
   //for( iter = dateList.begin(); iter != dateList.end(); iter++ )
   //   delete *iter;

   //// stop date updateing successful, so change the flag to be false that means no longer need to 
   //// call this function any more during the ControlUpdate is involked.
   //bEffDateChanged = false;

}

//******************************************************************************
void ContractInfoDlg::OnKillfocusDtpEffDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   *pResult = 0;
   //bEffDateChanged = true;
}

//******************************************************************************
bool ContractInfoDlg::GetEffDateMinusOne( DString& dstrEffDate, DString& dstrEffDateMinusOne )
{
   if( dstrEffDate != NULL_STRING )
   {
      dstrEffDate.strip();

      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );

      int day_pos      = mask.find( I_( "dd" ) );
      int month_pos    = mask.find( I_( "MM" ) );
      int year_pos     = mask.find( I_( "yyyy" ) );
      DString strDay   = dstrEffDate.substr( day_pos, 2 );
      DString strMonth = dstrEffDate.substr( month_pos, 2 );
      DString strYear  = dstrEffDate.substr( year_pos, 4 );

      SYSTEMTIME st;
      st.wYear = strYear.asInteger();
      st.wMonth= strMonth.asInteger();
      st.wDayOfWeek = 0;//irrelevant
      st.wDay = strDay.asInteger();
      st.wHour = 0;//irrelevant
      st.wMinute = 0;//irrelevant
      st.wSecond = 0;//irrelevant
      st.wMilliseconds = 0;//irrelevant

      DSTOleDateTime *m_pEffDateMinusOne;
      m_pEffDateMinusOne = new DSTOleDateTime( st );
      *m_pEffDateMinusOne -= COleDateTimeSpan ( 1, 0, 0, 0 );

      CString sValue;
      m_pEffDateMinusOne->DSTHostFormat( sValue );
      dstrEffDateMinusOne = (DString)sValue;
      delete m_pEffDateMinusOne;
      return(true);
   }
   else
      return(false);

}

//****************************************************************************
void ContractInfoDlg::OnAdd() 
{
   AddToListControl( IDC_LV_CONTRACT );
   LoadListControl(IDC_LV_CONTRACT);
   LoadControls(IDC_LV_CONTRACT);
   GetList( IDC_LV_CONTRACT )->SetFocus();
   int iNumItem = GetList( IDC_LV_CONTRACT )->GetItemCount();
   GetList( IDC_LV_CONTRACT )->SetSelection(iNumItem-1);

   SetContrMatrInstrBtnState();
}

//*****************************************************************************
void ContractInfoDlg::OnDel() 
{  
   DeleteFromListControl( IDC_LV_CONTRACT ); 
   LoadListControl(IDC_LV_CONTRACT);
   LoadControls(IDC_LV_CONTRACT);
   GetList( IDC_LV_CONTRACT )->SetFocus();

   SetContrMatrInstrBtnState();
}

//*****************************************************************************
void ContractInfoDlg::OnBtnUserDefMat() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnUserDefMat"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnUserDefMat" ) );

   // Determine whether it's Contract or Deposit
   DString ContMatDateBasedOn, MatDateBasedOn, IsContract, LegalMaturityDate, SegTransExist, ContractType, ModPerm;
   const DString *pKey = &( getParent()->getFirstListItemKey( this, IFASTBP_PROC::MASTER_CONTRACT_LIST ) );
   getParent()->getField( this, BF::NullContainerId, ifds::ContMatDateBasedOn, ContMatDateBasedOn );
   getParent()->getField( this, BF::NullContainerId, ifds::MatDateBasedOn, MatDateBasedOn );
   IsContract = ( ContMatDateBasedOn == I_("02") ? I_("Y") : I_("N") );

   // Get Legal Maturity Date
   getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::LegalMaturityDate, LegalMaturityDate, false );

   // Get Contracty Type
   getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractType, ContractType, false );

   // Seg Trans Exist
   getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::SegTransExist, SegTransExist, false );
   SegTransExist.upperCase();

   //Get ModPerm
   getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ModPerm, ModPerm, false );

   // Set Parameters
   setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNumber );
   setParameter( MFCAN_IP_PARAM::SHR_NUM, m_dstrShareHoldNum );
   setParameter( I_("IsContract"), IsContract );
   setParameter( I_("LegalMaturityDate"), LegalMaturityDate );
   setParameter( MFCAN_IP_PARAM::SEG_TRANS_EXIST, SegTransExist );
   setParameter( MFCAN_IP_PARAM::CONTRACT_TYPE, ContractType );
   setParameter( MFCAN_IP_PARAM::MOD_PERM, ModPerm );

   try
   {
      bool bModal = true;
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_USERDEFMAT, PROC_SUPPORT, bModal, NULL );
      switch( eRtn )
      {
         case CMD_OK:
            {
               DString ContractMaturityDate;
               getParameter( MFCAN_IP_PARAM::MATURITY_DATE, ContractMaturityDate );
               //getParent()->setField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractMaturityDate, ContractMaturityDate );
               getParent()->setField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::UserDefinedMaturityDate, ContractMaturityDate );
               ConnectControlToData(IDC_TXT_CONTRACT_MATURITY_DATE,true);
               LoadControl( IDC_TXT_CONTRACT_MATURITY_DATE );
            }
            break;
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
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

//*****************************************************************************
void ContractInfoDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   if( controlID == IDC_CMB_CONTRACT_TYPE )
   {
      // PET1024 FN02 - Set User Def Button
      DString ContMatDateBasedOn, MatDateBasedOn;
      const DString *pKey = &( getParent()->getFirstListItemKey( this, IFASTBP_PROC::MASTER_CONTRACT_LIST ) );
      getParent()->getField( this, BF::NullContainerId, ifds::ContMatDateBasedOn, ContMatDateBasedOn, false );
      getParent()->getField( this, BF::NullContainerId, ifds::MatDateBasedOn, MatDateBasedOn, false );

      bool bEnableUsrDefine = ContMatDateBasedOn == I_("04") || ContMatDateBasedOn == I_("07");
      GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow (bEnableUsrDefine);

      //if ( ContMatDateBasedOn == I_("04") && _bIsNew )
      //   GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow (false);
      //else if (ContMatDateBasedOn == I_("04"))
      //   GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow (true);
      //else
      //   GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow( !( ContMatDateBasedOn != I_("02") && MatDateBasedOn != I_( "01" ) ) );

      ConnectControlToData(IDC_STC_CONTRACT_VERSION,true);
      LoadControl( IDC_STC_CONTRACT_VERSION );

      ConnectControlToData(IDC_CMB_MATURE_DATE_BASED_ON,true);
      LoadControl( IDC_CMB_MATURE_DATE_BASED_ON );      

      ConnectControlToData(IDC_CMB_PROV_REG,true);
      LoadControl( IDC_CMB_PROV_REG );

      DString strIsGWOContract;
      getParent()->getField( this, BF::NullContainerId, ifds::IsGWOContract, strIsGWOContract, false );
      strIsGWOContract.strip().upperCase();
      
      if(strIsGWOContract == I_("Y"))
      {
         ConnectControlToData(IDC_TXT_GWO_CONTRACT_ANNIV_DATE,true);
         LoadControl( IDC_TXT_GWO_CONTRACT_ANNIV_DATE );
         GetDlgItem( IDC_STATIC_GEN_32 )->ShowWindow( true );
         GetDlgItem( IDC_TXT_GWO_CONTRACT_ANNIV_DATE )->ShowWindow( true );
      }
      else
      {
         GetDlgItem( IDC_STATIC_GEN_32 )->ShowWindow( false );
         GetDlgItem( IDC_TXT_GWO_CONTRACT_ANNIV_DATE )->ShowWindow( false );
      }

      DString strGuaranteeCalcByRules;
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      dstWorkSession->getOption (ifds::GuaranteeCalcByRules, strGuaranteeCalcByRules, getParent()->getDataGroupId(), false);
      strGuaranteeCalcByRules.strip().upperCase();

      if( strGuaranteeCalcByRules == I_("Y") )
      {

         ConnectControlToData(IDC_CMB_MATURE_DATE_BASED_ON,true);
         LoadControl( IDC_CMB_MATURE_DATE_BASED_ON );

         GetDlgItem( IDC_CMB_MATURE_DATE_BASED_ON )->ShowWindow( true );
         GetDlgItem( IDC_STATIC_GEN_27 )->ShowWindow( true );
      }
      else
      {

         ConnectControlToData(IDC_CMB_MATURE_DATE_BASED_ON, false );
         GetDlgItem( IDC_CMB_MATURE_DATE_BASED_ON )->ShowWindow( false );
         GetDlgItem( IDC_STATIC_GEN_27 )->ShowWindow( false );
      }

      ConnectControlToData(IDC_TXT_MATURITY_DATE,true);
      LoadControl( IDC_TXT_MATURITY_DATE );

      ConnectControlToData(IDC_TXT_BAILOUT_DATE,true);
      LoadControl( IDC_TXT_BAILOUT_DATE );

      ConnectControlToData(IDC_TXT_CLOSINGDECADE_DATE,true);
      LoadControl( IDC_TXT_CLOSINGDECADE_DATE );

      ConnectControlToData(IDC_TXT_REDUCTIONAGE_DATE,true);
      LoadControl( IDC_TXT_REDUCTIONAGE_DATE );      

      ConnectControlToData(IDC_EDT_CLS_TERM,true);
      LoadControl( IDC_EDT_CLS_TERM );

      ConnectControlToData(IDC_TXT_CONTRACT_ISSUE_DATE,true);
      LoadControl( IDC_TXT_CONTRACT_ISSUE_DATE );

      //// Contract/Deposit Maturity Date Label
      //CString cstrLabel;
      //cstrLabel.LoadString(  ContMatDateBasedOn == I_("02") ? IDS_TXT_CONTRACT_MATURITY_DATE : IDS_TXT_DEPOSIT_MATURITY_DATE );
      //GetDlgItem( IDC_STC_MATURE_DATE )->SetWindowText( cstrLabel );

      //LoadControl( IDC_EDT_TERM );

      //DString dstrGWOContract;
      //getParent ()->getField ( this,
      //                         IFASTBP_PROC::CONTRACTINFO_LIST,
      //                         ifds::GWOContract,
      //                         dstrGWOContract,
      //                         false );

      //// New logic will be inserted here
      //if ( I_( "Y" ) == dstrGWOContract.strip().upperCase() )
      //{
      //   GetDlgItem( IDC_STATIC_GEN_17 )->ShowWindow( true );
      //   GetDlgItem( IDC_TXT_GWO_CONTRACT_ANNIV_MONTH )->ShowWindow( true );
      //   GetDlgItem( IDC_STATIC_GEN_18 )->ShowWindow( true );
      //   GetDlgItem( IDC_TXT_GWO_CONTRACT_ANNIV_DAY )->ShowWindow( true );
      //   //GetDlgItem( IDC_STATIC_SETTLEMENT_DATE )->ShowWindow( true );
      //   //GetDlgItem( IDC_TXT_SETTLEMET_DATE )->ShowWindow( true );
      //}
      //else
      //{
      //   GetDlgItem( IDC_STATIC_GEN_17 )->ShowWindow( false );
      //   GetDlgItem( IDC_TXT_GWO_CONTRACT_ANNIV_MONTH )->ShowWindow( false );
      //   GetDlgItem( IDC_STATIC_GEN_18 )->ShowWindow( false );
      //   GetDlgItem( IDC_TXT_GWO_CONTRACT_ANNIV_DAY )->ShowWindow( false );
      //   //GetDlgItem( IDC_STATIC_SETTLEMENT_DATE )->ShowWindow( false );
      //   //GetDlgItem( IDC_TXT_SETTLEMET_DATE )->ShowWindow( false );
      //}
   }
   else if( controlID == IDC_CMB_MATURE_DATE_BASED_ON)
   {
      DString dstrContMatDateBasedOn;
      getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractMatBasedOn, dstrContMatDateBasedOn, false );
      dstrContMatDateBasedOn.strip().upperCase();   
      bool bEnableUsrDefine = dstrContMatDateBasedOn == I_("04") || dstrContMatDateBasedOn == I_("07") ;
      GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow (bEnableUsrDefine);

      ConnectControlToData(IDC_TXT_CONTRACT_MATURITY_DATE,true);
      LoadControl( IDC_TXT_CONTRACT_MATURITY_DATE );   
   }
   else if( controlID == IDC_TXT_CONTRACT_MATURITY_DATE )
   {
      ConnectControlToData(IDC_TXT_CLOSINGDECADE_DATE,true);
      LoadControl( IDC_TXT_CLOSINGDECADE_DATE );      
   }
}

//**********************************************************************************
void ContractInfoDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;

   //IFastHistoricalInfo f;
   //f( this, IFASTBP_PROC::CONTRACTINFO_LIST, I_("MULTI") );
}

//**********************************************************************************
void ContractInfoDlg::OnBtnFeatureOpt()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnFeatureOpt"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnFeatureOpt" ) );
   
   try
   {
      setParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber);
      setParameter( CONTRACT::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
      SetMessageStatusBar( TXT_LOAD_VERSION_FEATURE );

      CString cstrFeatureVersion,
         cstrAccountNumLabel;
      cstrFeatureVersion.LoadString(TXT_VERSION_FEATURE);
      cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);

      DString strBrowserTitle(cstrFeatureVersion);
      strBrowserTitle += cstrAccountNumLabel;
      strBrowserTitle += m_dstrAccountNumber;

      setParameter( I_("AccountNum"), m_dstrAccountNumber );
      setParameter( I_("BrowserTitle"), strBrowserTitle);

      DString urlParamsIDI,
         strContractType,
         strVersionNumber;
         
      getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractType, strContractType, false );
      getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractVer, strVersionNumber, false );

      setParameter( I_("from_screen"), I_("ContractInfoDlg") );

      addIDITagValue (urlParamsIDI, I_("AccountNum"), m_dstrAccountNumber);
      addIDITagValue (urlParamsIDI, I_("ContractType"), strContractType);
      addIDITagValue (urlParamsIDI, I_("VersionNumber"), strVersionNumber);
      addIDITagValue (urlParamsIDI, I_("screen"), I_("VersionFeatures"));

      setParameter (I_("UrlParams"), urlParamsIDI);
   
      bool bModal = true;
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_VERSION_FEATURE, PROC_SUPPORT, bModal, NULL );
      switch( eRtn )
      {
         case CMD_OK:
            {
            }
            break;
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
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
/*
void ContractInfoDlg::OnBtnContractMaturityInstr()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnContractMaturityInstr"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnContractMaturityInstr" ) );
   
   try
   {
      //bool bModal = true;
      //E_COMMANDRETURN eRtn;
      //eRtn = invokeCommand( getParent(), CMD_BPROC_USERDEFMAT, PROC_SUPPORT, bModal, NULL );
      //switch( eRtn )
      //{
      //   case CMD_OK:
      //      {
      //         DString ContractMaturityDate;
      //         getParameter( MFCAN_IP_PARAM::MATURITY_DATE, ContractMaturityDate );
      //         getParent()->setField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractMaturityDate, ContractMaturityDate );
      //         LoadControl( IDC_DATE_MATURITY );
      //      }
      //      break;
      //   case CMD_CANCEL:
      //   case CMD_MODELESS_INPROCESS:
      //      break;
      //   default:
      //      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      //      break;
      //}
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
*/

//**********************************************************************************
void ContractInfoDlg::OnBtnContractMaturityInstr()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnContractMaturityInstr"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnContractMaturityInstr" ) );
   
   try
   {
		DString dstrCotAcctRid, dstrContractType, dstrPolicyYear, 
				dstrPolicyTerm, dstrMaturityDate, dstrContractTypeId;

		getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractType,		dstrContractType,	false ); //Used for enquiry
		getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractTypeId,		dstrContractTypeId,	false ); //Used for enquiry
		getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::CMPolicyYear,		dstrPolicyYear,		false ); //Used for update
		getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::CMPolicyTerm,		dstrPolicyTerm,		false ); //Used for update
		getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::CMMaturityDate,		dstrMaturityDate,	false ); //Used for update
		getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::CotAcctRid,			dstrCotAcctRid,		false ); //Used for update

		dstrCotAcctRid.strip();
		dstrContractType.strip();
		dstrContractTypeId.strip();
		dstrPolicyYear.strip();
		dstrPolicyTerm.strip();
		dstrMaturityDate.strip();

		if( dstrContractType.empty() || dstrContractTypeId.empty() || dstrCotAcctRid.empty() )
		{
			DISPLAYCONDITIONFROMFILE( CND::GUI_INVALID_CONTRACT_TYPE );
			return;
		}

		if( dstrPolicyYear == I_("0") && dstrPolicyTerm == I_("0")  )
		{
			DISPLAYCONDITIONFROMFILE( CND::GUI_INVALID_POLICY );
			return;
		}

		setParameter( CONMATINS_PROC::ACCOUNT_NUM_VALUE,	m_dstrAccountNumber );
		setParameter( CONMATINS_PROC::COT_REC_ID,			dstrCotAcctRid );
		setParameter( CONMATINS_PROC::CONTRACT_TYPE,		dstrContractType );
		setParameter( CONMATINS_PROC::CONTRACT_TYPE_ID,		dstrContractTypeId );
		setParameter( CONMATINS_PROC::POLICY_YEAR,			dstrPolicyYear );
		setParameter( CONMATINS_PROC::POLICY_TERM,			dstrPolicyTerm );
		setParameter( CONMATINS_PROC::MATURITY_DATE,		dstrMaturityDate );
		
		invokeCommand( getParent(), CMD_BPROC_CONTRACT_MATURITY_INSTRUCTIONS, PROC_NO_TYPE, false, NULL );
		SetMessageStatusBar( NULL_STRING );
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
void ContractInfoDlg::OnBtnSEGProcessing()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnSEGProcessing"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSEGProcessing" ) );
   
   try
   {
      bool bModal = true;

      DString urlParamsIDI;
      E_COMMANDRETURN eRtn = CMD_OK;
      
      CString cstrSEGProcessing;
      cstrSEGProcessing.LoadString(TXT_SEG_PROCESSING);      

      setParameter( I_("AccountNum"), m_dstrAccountNumber );
      setParameter (I_("BrowserTitle"), DString(cstrSEGProcessing) + m_dstrAccountNumber);
      setParameter (I_("from_screen"), I_("ContractInfo"));

      DString strContractType,
         strMaturityID;
      getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractType, strContractType, false );
      getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::MaturityID, strMaturityID, false );
      strMaturityID.strip().upperCase();

      addIDITagValue (urlParamsIDI, I_("screen"),I_("SEGProcessing") );
      addIDITagValue (urlParamsIDI, I_("AccountNum"), m_dstrAccountNumber);
      addIDITagValue (urlParamsIDI, I_("ContractType"), strContractType);
      addIDITagValue (urlParamsIDI, I_("MaturityID"), strMaturityID);

      setParameter (I_("UrlParams"), urlParamsIDI);
               
      eRtn = invokeCommand( getParent(), CMD_BPROC_SEG_PROCESSING, PROC_SUPPORT, bModal, NULL );
      switch( eRtn )
      {
         case CMD_OK:
            {
            }
            break;
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
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
void ContractInfoDlg::OnBtnGuaranteeFee() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnGuaranteeFee"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnGuaranteeFee() " ) );

   setParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber);
   setParameter( CONTRACT::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   SetMessageStatusBar( TXT_LOAD_CONTRACT_GUARANTEE_FEE  );

   CString cstrGuaranteeInfo,
      cstrInfoShr,
      cstrAccountNumLabel;
   cstrGuaranteeInfo.LoadString(TXT_CONTRACT_GUARANTEE_FEE);
   cstrInfoShr.LoadString(TXT_SHRHLDR_INFO);
   cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);

   DString dstrEntityName;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
      getFirstSequenced01AccountholderEntityName(getDataGroupId(),
                                                 m_dstrAccountNumber,dstrEntityName);

   DString strBrowserTitle(cstrGuaranteeInfo);
   strBrowserTitle += cstrInfoShr;
   strBrowserTitle += m_dstrShareHoldNum;
   strBrowserTitle += cstrAccountNumLabel;
   strBrowserTitle += m_dstrAccountNumber;
   strBrowserTitle += I_(" ");
   strBrowserTitle += dstrEntityName;

   setParameter( I_("BrowserTitle"), strBrowserTitle);

   DString urlParamsIDI;

   setParameter( I_("from_screen"), I_("ContractInfoDlg") );

   addIDITagValue (urlParamsIDI, I_("AccountNum"), m_dstrAccountNumber);
   addIDITagValue (urlParamsIDI, I_("screen"), I_("GuaranteeFee"));
   
   setParameter (I_("UrlParams"), urlParamsIDI);

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_GUARANTEE_FEE, PROC_NO_TYPE, true, NULL );
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

   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void ContractInfoDlg::OnBtnSEGDates() 
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnSEGDates"));
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSEGDates()"));

   CString cstrSegDates;
   cstrSegDates.LoadString(TXT_SEG_DATES);

   DString strBrowserTitle(cstrSegDates), urlParamsIDI, strContractType, strVersionNumber, strPolicyNum;

   setParameter(I_("BrowserTitle"), strBrowserTitle);

   getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractType, strContractType, false);
   getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractVer, strVersionNumber, false);
   getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::PolicyNum, strPolicyNum, false);

   addIDITagValue(urlParamsIDI, I_("AccountNum"), m_dstrAccountNumber);
   addIDITagValue(urlParamsIDI, I_("ContractType"), strContractType);
   addIDITagValue(urlParamsIDI, I_("ContractVer"), strVersionNumber);
   addIDITagValue(urlParamsIDI, I_("PolicyNum"), strPolicyNum);
   addIDITagValue(urlParamsIDI, I_("screen"), I_("SegEventDates"));
   
   setParameter(I_("UrlParams"), urlParamsIDI);

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand(getParent(), CMD_BPROC_SEG_DATES, PROC_NO_TYPE, true, NULL);
      switch (eRtn)
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }

   SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************
void ContractInfoDlg::OnBtnOverride() 
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnOverride"));
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnOverride()"));

   CString cstrCotOvrd;
   cstrCotOvrd.LoadString(TXT_COT_OVRD);

   DString strBrowserTitle(cstrCotOvrd), urlParamsIDI, strContractType, strVersionNumber, strPolicyNum;

   setParameter(I_("BrowserTitle"), strBrowserTitle);

   getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractType, strContractType, false);
   getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractVer, strVersionNumber, false);
   getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::PolicyNum, strPolicyNum, false);

   addIDITagValue(urlParamsIDI, I_("AccountNum"), m_dstrAccountNumber);
   addIDITagValue(urlParamsIDI, I_("ContractType"), strContractType);
   addIDITagValue(urlParamsIDI, I_("ContractVer"), strVersionNumber);
   addIDITagValue(urlParamsIDI, I_("PolicyNum"), strPolicyNum);
   addIDITagValue(urlParamsIDI, I_("screen"), I_("SegOverRate"));
   
   setParameter(I_("UrlParams"), urlParamsIDI);

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand(getParent(), CMD_BPROC_CONTRACT_OVERRIDE, PROC_NO_TYPE, true, NULL);
      switch (eRtn)
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }

   SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/contractinfodlg.cpp-arc  $
 * 
 *    Rev 1.67   Jun 18 2012 17:34:24   if991250
 * IN2937065: new CMD Based on: User Defined Mat - Transfer
 * 
 *    Rev 1.66   May 24 2012 12:05:08   dchatcha
 * IN#2883926 - Date format is not the same in UAT environment.
 * 
 *    Rev 1.65   Mar 27 2012 20:37:46   wp040100
 * P0186484 FN05 - Contract Maturity Instruction Changes
 * 
 *    Rev 1.64   Mar 27 2012 16:50:54   if991250
 * IN 2858958 - Contract info
 * 
 *    Rev 1.63   Mar 22 2012 18:37:04   wp040100
 * P0186484 FN05 - Contract Maturity Instruction Changes
 * 
 *    Rev 1.62   Mar 19 2012 21:42:56   wp040100
 * P0186484 FN05 - Contract Maturity Instruction Changes
 * 
 *    Rev 1.61   Feb 21 2012 15:50:04   wp040100
 * P0186484 FN05 - Contract Maturity Instruction Changes.
 * 
 *    Rev 1.60   Feb 16 2012 14:02:36   dchatcha
 * Synch up : IN# 2848252 - P0186484 FN02 Seg Desktop - Contract Info Screen issues for non-IA
 * 
 *    Rev 1.59   Feb 15 2012 15:59:18   dchatcha
 * Synch up: IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen regression issues.
 * 
 *    Rev 1.58   Feb 10 2012 10:34:54   dchatcha
 * P0186484 - FN 05 - SEG Processing Screen, disable button when there is no record.
 * 
 *    Rev 1.57   Feb 03 2012 19:17:16   dchatcha
 * Synch up: IN# 2799812 - Contract Screen Issues.
 * 
 *    Rev 1.56   Jan 30 2012 18:49:42   dchatcha
 * Synch up: IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.55   Jan 24 2012 17:47:40   dchatcha
 * Synch up : IN# 2809707 - Title information of new guarantee screen missing and IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.54   Jan 21 2012 09:34:32   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.53   Jan 19 2012 13:15:14   dchatcha
 * Synch up: IN# 2799812 - Contract Screen issues. New requirement to display contract anniversary date. 
 * 
 *    Rev 1.52   Jan 18 2012 13:32:52   dchatcha
 * Synch up IN# 2799812 - Contract Screen issues. and activate 'Feature Opt' button.
 * 
 *    Rev 1.51   Jan 16 2012 21:36:58   dchatcha
 * P0186484 - FN 05 - SEG Processing Screen
 * 
 *    Rev 1.50   Jan 16 2012 20:30:58   dchatcha
 * P0186484 - FN 05 - SEG Processing Screen
 * 
 *    Rev 1.49   Jan 16 2012 20:06:44   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.48   Dec 27 2011 01:09:22   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.47   Jun 06 2006 17:26:56   porteanm
 * PET 2102 FN01 - Flex support.
 * 
 *    Rev 1.46   May 25 2006 17:52:38   ZHANGCEL
 * PET 2102 FN02 -- Settlement date and GWOContractAnnivDate related changes
 * 
 *    Rev 1.45   May 02 2006 14:26:26   jankovii
 * PET 2102 Manulife Flex - User Defined Maturity Dates.
 * 
 *    Rev 1.44   Apr 21 2006 11:32:50   porteanm
 * PET2102 FN02 - For 71 - Some GWO support.
 * 
 *    Rev 1.43   Apr 20 2006 16:17:34   porteanm
 * PET2102 FN02 - For 71 - Some GWO support.
 * 
 *    Rev 1.42   Feb 14 2006 14:13:22   zhengcon
 * Incident #528284 - add one field ModPerm for updatable permission of User Defined Maturity Date of converted account
 * 
 *    Rev 1.41   Nov 03 2005 15:31:30   porteanm
 * Incident 442910 - Contract Term - reload Contract Term when Contract Type changed.
 * 
 *    Rev 1.40   Sep 15 2005 15:11:12   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.39   Aug 19 2005 11:31:48   porteanm
 * Incident 351033 - Call Entity as modeless.
 * 
 *    Rev 1.38   Aug 17 2005 16:47:32   porteanm
 * Incident 351033 - Removed Contract and Guarantee, renamed Contract1 and Guarantee1 to Contract and Guarantee.
// 
//    Rev 1.23   Jun 14 2005 15:30:26   porteanm
// PET1024 FN40 - Guarantee Adjustments.
// 
//    Rev 1.22   Apr 18 2005 13:55:16   hernando
// PET1024 FN02 - Added controlUpdated.
// 
//    Rev 1.21   Apr 14 2005 10:12:04   hernando
// PET1024 FN02 - Added Contract Type support.
// 
//    Rev 1.20   Mar 30 2005 17:24:48   hernando
// PET1024 FN02 - Changed the Process Type to PROC_SUPPORT.
// 
//    Rev 1.19   Mar 21 2005 11:50:50   hernando
// PET1024 FN02 - Added Seg Trans Exist parameter.
// 
//    Rev 1.18   Mar 20 2005 20:05:06   hernando
// PET1024 FN02 - Set additional parameters for User Def Mat.
// 
//    Rev 1.17   Mar 16 2005 14:32:40   hernando
// PET1024 FN02 - Removed MaturityType and UserMaturityDate.  Added additional controls.
// 
//    Rev 1.16   Mar 21 2003 18:34:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.15   Mar 12 2003 13:51:06   linmay
// clean up message
// 
//    Rev 1.14   Oct 09 2002 23:55:36   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.13   Sep 30 2002 11:01:38   PURDYECH
// BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
// 
//    Rev 1.12   Jul 05 2002 10:41:54   PURDYECH
// Include file cleanup.
// 
//    Rev 1.11   22 May 2002 19:15:54   PURDYECH
// BFData Implementation
// 
//    Rev 1.10   27 Mar 2002 20:01:04   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.9   Nov 15 2001 10:33:06   ZHANGCEL
// Disable Add Button when entity's birth date is invalid
// 
//    Rev 1.8   Nov 07 2001 15:31:10   ZHANGCEL
// Many changed for Multiple contracts
// 
//    Rev 1.7   18 Oct 2001 13:56:52   HSUCHIN
// code cleanup and bug fix for YEARS (changed to use string table and yrs )
// 
//    Rev 1.6   Sep 06 2001 14:07:52   ZHANGCEL
// Added second parameter in ListViewControlFilter()
// 
//    Rev 1.5   Aug 21 2001 11:28:54   OLTEANCR
// Removed AddCopy button
// 
//    Rev 1.4   Aug 10 2001 11:43:50   OLTEANCR
// disabled AddCopy button
// 
//    Rev 1.3   Aug 07 2001 12:11:18   OLTEANCR
// disabled delete button for an active contract
// 
//    Rev 1.2   Aug 03 2001 16:07:32   OLTEANCR
// modif. guarantee button
*/
