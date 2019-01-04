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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ContractInfoDlg1.cpp
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
#include "ContractInfoDlg1.h"
#include <ifastbp\ContractInfoProcessIncludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastbp\EntityProcessIncludes.h>
#include <configmanager.hpp>

using std::vector;

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENTITY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_GUARANTEEINFO;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_CONTRACTINFO1;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_USERDEFMAT;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ContractInfoDlg1 > dlgCreator( CMD_GUI_CONTRACTINFO1 );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//******************************************************************************
// ContractInfoDlg dialog

namespace
{   
   const I_CHAR * const CLASSNAME      = I_( "ContractInfoDlg1" );
   const I_CHAR * const LV_CONTRACT    = I_( "ContractInfoList" );
   const I_CHAR * const TERM           = I_( "ContractTerm" );
   const int MONTH = 13;
   const I_CHAR * const SPACE_STRING = I_( " " ); 

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
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForDofBirth;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_MULTI_CONTRACT;
}

bool CompareItemPtr ( const EffectiveDateSort1* pLeft, EffectiveDateSort1* pRight)
{
   return( *pLeft) <= ( *pRight );
}

//******************************************************************************

ContractInfoDlg1::ContractInfoDlg1(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ContractInfoDlg1::IDD, pParent, pGIC, pGIParent, rCommand )
{
   //{{AFX_DATA_INIT(ContractInfoDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************

void ContractInfoDlg1::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ContractInfoDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(ContractInfoDlg1, BaseMainDlg)
//{{AFX_MSG_MAP(ContractInfoDlg)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_ENTITY, OnBtnEntity)
ON_BN_CLICKED(IDC_BTN_GUARANTEE, OnBtnGuarantee)
ON_BN_CLICKED(IDC_BTN_USERDEFMAT, OnBtnUserDefMat)
ON_NOTIFY(NM_KILLFOCUS, IDC_DTP_EFF_DATE, OnKillfocusDtpEffDate)
ON_BN_CLICKED(IDADD, OnAdd)
ON_BN_CLICKED(IDDEL, OnDel)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************

SEVERITY ContractInfoDlg1::doInit()
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

BOOL ContractInfoDlg1::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   setTitleBar ( );
   return(TRUE);  // return TRUE unless you set the focus to 
}

//******************************************************************************
void ContractInfoDlg1::setTitleBar ( )
{

   m_dstrShareHoldNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();
   m_dstrAccountNumber.stripLeading(I_CHAR('0')).stripTrailing();

   SetAccount( m_dstrAccountNumber );

   DString dstrEntityName;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
   getFirstSequenced01AccountholderEntityName(getDataGroupId(),
                                              m_dstrAccountNumber,dstrEntityName);

   SetShrAcctCaption(m_dstrShareHoldNum, m_dstrAccountNumber, dstrEntityName);

}

//******************************************************************************
void ContractInfoDlg1::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode(UAF::SEG_FUND_MULTI_CONTRACT);   
   addBtnAddForPermissionCheck(IDADD, IDC_LV_CONTRACT);
   addBtnDeleteForPermissionCheck(IDDEL, IDC_LV_CONTRACT);
   // Populate dialog    
   bEffDateChanged = false;
   AddListControl( CLASSNAME, IDC_LV_CONTRACT, LV_CONTRACT, ifds::MultiContractsListHeading, 
                   IFASTBP_PROC::CONTRACTINFO_LIST);

   AddControl( CTRL_COMBO, IDC_CMB_CONTRACT_TYPE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractType,
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT  );

   AddControl( CTRL_EDIT, IDC_ACC_GR, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::AcctGroup,
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT  );

   AddControl( CTRL_STATIC, IDC_TXT_ISSUE_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::IssueDate,
               0, IDC_LV_CONTRACT );//CTRLFLAG_NOT_UPDATABLE, 0);
   AddControl( CTRL_STATIC, IDC_TXT_TYPEID, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractTypeId,
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_CONTRACT );//CTRLFLAG_NOT_UPDATABLE, 0);
   AddControl( CTRL_STATIC, IDC_TXT_LAST_RESET, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::LastResetDate,
               0, IDC_LV_CONTRACT );//CTRLFLAG_NOT_UPDATABLE, 0);
   AddControl( CTRL_STATIC, IDC_TXT_POLICY_NUMBER, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::PolicyNum,
               0, IDC_LV_CONTRACT );//CTRLFLAG_NOT_UPDATABLE, 0);
   AddControl( CTRL_STATIC, IDC_TXT_MATURITY_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::LegalMaturityDate,
               0, IDC_LV_CONTRACT );//CTRLFLAG_NOT_UPDATABLE, 0);
   AddControl( CTRL_STATIC, IDC_TXT_AGE_BASEDON, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::AgeBasedOnDesc,
               0, IDC_LV_CONTRACT );//CTRLFLAG_NOT_UPDATABLE, 0);
   AddControl( CTRL_STATIC, IDC_TXT_ANNIV_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::AnnivMonth,
               0, IDC_LV_CONTRACT );//CTRLFLAG_NOT_UPDATABLE, 0);
   AddControl( CTRL_STATIC, IDC_TXT_BAILOUT_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::BailMaturityDate,
               0, IDC_LV_CONTRACT );//CTRLFLAG_NOT_UPDATABLE, 0);

   AddControl( CTRL_COMBO, IDC_CMB_STATUS, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::Status, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT );
   AddControl( CTRL_COMBO, IDC_CMB_PROV_REG, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ProvinceCanada, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT );

   AddControl( CTRL_EDIT, IDC_EDT_TERM, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractTerm,
               0, IDC_LV_CONTRACT);
   AddControl( CTRL_DATE, IDC_DTP_EFF_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::EffectiveDate,
               0, IDC_LV_CONTRACT);
   AddControl( CTRL_DATE, IDC_DTP_STOP_DATE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::StopDate, 
               0, IDC_LV_CONTRACT);

   // PET1024 FN02
   AddControl( CTRL_DATE, IDC_DATE_MATURITY, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractMaturityDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_DATE, IDC_DATE_LEGALMATURITY, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::LegalMaturityDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_DATE, IDC_DATE_CLOSINGDECADE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::CDStartDate,
               0, IDC_LV_CONTRACT );
   AddControl( CTRL_DATE, IDC_DATE_REDUCTIONAGE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::RedAgeDate,
               0, IDC_LV_CONTRACT );
   
   AddControl( CTRL_COMBO, IDC_CMB_SUSPECT_GUAR_TYPE, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::SuspectGuarType, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CONTRACT );	


   int iItemNumber = 0;
   iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::CONTRACTINFO_LIST );
   if( iItemNumber != 0 )
   {
      LoadListControl( IDC_LV_CONTRACT);

      GetDlgItem( IDC_BTN_ENTITY )->EnableWindow( true );//Cri

      m_bNewCopyAdded = false;
      GetDlgItem( IDC_ACC_GR )->EnableWindow( false );
   }

   else
   {
      setParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber ); 
//      LoadListControl( IDC_LV_CONTRACT);  // When the system executes this function, it adds a new record automaticly
      DString dstrOrgKey = GetList(IDC_LV_CONTRACT)->GetCurrentKey();
      getParent()->setField(this, BF::NullContainerId, CONTRACT::ORG_KEY, dstrOrgKey);
      DString dstrIsAddNew = I_( "Y" );
      getParent()->setField(this, BF::NullContainerId, CONTRACT::ISADDNEW, dstrIsAddNew);      
//      m_bNewCopyAdded = true;
//      getParent()->setField(this, 0, CONTRACT::CHECKDOFBIRTH, I_("Y") );
      GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( false );
      LoadContractInfo();
   }
}

//******************************************************************************

void ContractInfoDlg1::LoadContractInfo()
{
   TRACE_METHOD( CLASSNAME, I_("LoadContractInfo"));

   GetDlgItem( IDC_ACC_GR )->EnableWindow( false );
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
      GetDlgItem( IDC_BTN_ENTITY )->EnableWindow( true );

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
      GetDlgItem( IDC_BTN_ENTITY )->EnableWindow( true );
   }

   if( cMessage == NULL_STRING )
   {
      LoadListControl( IDC_LV_CONTRACT);
      //    GetDlgItem( IDC_BTN_ENTITY )->EnableWindow( true );  
      GetDlgItem( IDC_DTP_EFF_DATE )->EnableWindow( true );
      GetDlgItem( IDC_DTP_STOP_DATE )->EnableWindow( true );
      GetDlgItem( IDC_CMB_STATUS )->EnableWindow( true );
      GetDlgItem( IDC_CMB_PROV_REG )->EnableWindow( true );
      GetDlgItem( IDADD )->EnableWindow( true );
   }
   else
   {
//      GetDlgItem( IDC_BTN_ADD_COPY )->EnableWindow( false );
      GetDlgItem( IDC_DTP_EFF_DATE )->EnableWindow( false );
      GetDlgItem( IDC_DTP_STOP_DATE )->EnableWindow( false );
      GetDlgItem( IDC_CMB_STATUS )->EnableWindow( false );
      GetDlgItem( IDC_CMB_PROV_REG )->EnableWindow( false );
      GetDlgItem( IDADD )->EnableWindow( false );
      AfxMessageBox( cMessage ); //, MB_ICONSTOP );
   }
}

//******************************************************************************

void ContractInfoDlg1::OnBtnAdmDates() 
{
   // TODO: Add your control notification handler code here
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnAdmDates() " ) );
   ShowAdminDates( IFASTBP_PROC::CONTRACTINFO_LIST );
}

//******************************************************************************
bool ContractInfoDlg1::GetOverrideItemString( long lSubstituteId, const DString& ColumnKey, DString& strOut )
{

   if( lSubstituteId == ifds::MultiContractsListHeading.getId() )
   {
      if( ColumnKey == TERM )
      {
         CString cstrYear;
         DString dstr;
         getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractTerm, dstr );
         dstr.strip();
         cstrYear.LoadString ( TXT_YEARS );
         strOut = dstr + I_(" ") + DString (cstrYear);
         return(true);
      }
   }
   return(false);
}

//*****************************************************************************

void ContractInfoDlg1::OnBtnEntity() 
{   
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnEntity"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnEntity() " ) );

   setParameter( ENTPROC::ACCOUNT_NUM, m_dstrAccountNumber);

   SetMessageStatusBar( TXT_LOAD_ENTITY );
   const DString& dstrOrgKey = (getParent()->getCurrentListItemKey(this, IFASTBP_PROC::CONTRACTINFO_LIST));
   DString dstrCheckDofBirth = I_("Y");
   try
   {
      bool bModal = true;   // set it to be modal
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ENTITY, PROC_NO_TYPE, bModal, NULL );
      switch( eRtn )
      {
         case CMD_OK:
            // Through setField to call ContractInfoProcess.GetDofBirth() and 
            // ContractInfoList.PassDofBirthForCheck() and call ContractInfo.CheckDofBirth() indirectly
            setParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber ); // have to set it again, otherwise it will be empty
            getParent()->setField(this, BF::NullContainerId, CONTRACT::ORG_KEY, dstrOrgKey);
            getParent()->setField(this, BF::NullContainerId, CONTRACT::CHECKDOFBIRTH, dstrCheckDofBirth);

            LoadContractInfo();
            GetList(IDC_LV_CONTRACT)->SetSelection( &dstrOrgKey);
            break;
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

void ContractInfoDlg1::OnBtnGuarantee() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnGuarantee"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnGuarantee() " ) );

   // For the user click Entity button at GuaranteeInfoDlg

   setParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber);
   setParameter( CONTRACT::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   SetMessageStatusBar( TXT_LOAD_GUARANTEE );

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_GUARANTEEINFO, PROC_NO_TYPE, bModal, NULL );
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

bool ContractInfoDlg1::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{  

   TRACE_METHOD( CLASSNAME, I_("doRefresh"));

   getParameter( CONTRACT::ACCOUNT_NUMBER, m_dstrAccountNumber );
   getParameter( CONTRACT::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   getParameter( CONTRACT::TRANSID_EMPTY, m_dstrTransIdEmpty );
   setTitleBar ( );
   LoadContractInfo();
   return(true);
}


//******************************************************************************

bool ContractInfoDlg1::GetDataForControl(
                                        UINT controlID,
                                        DString &strValueOut,
                                        bool bFormatted,
                                        int index
                                        ) const
{
   strValueOut=NULL_STRING;
   DString dstr, dstr2;
   CString cstrMonthDay, cstrYear;
   int idx;

   switch( controlID )
   {
      
      case IDC_TXT_ANNIV_DATE:
         getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::AnnivMonth, dstr);
         idx = dstr.stripAll().asInteger();
         cstrMonthDay =InttoMonth[idx];
         getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::AnnivDay, dstr);           
         strValueOut =((DString)cstrMonthDay) + (I_(" ")) + dstr.stripAll().stripLeading('0');            
         break;

      case IDC_EDT_TERM:           
         cstrYear.LoadString ( TXT_YEARS );
         getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractTerm, dstr );
         strValueOut = dstr + I_(" ") + DString (cstrYear);
         break;

      default :
         return(false);
   }     
   return(true);
}

//******************************************************************************

bool ContractInfoDlg1::SetDataFromControl(
                                         UINT controlID,
                                         const DString &strValue,
                                         bool bFormatted,
                                         SEVERITY &sevRtn,
                                         int index
                                         )
{
   bool bRtn = false;
   DString dstrSubTerm;
   int iPos;
   switch( controlID )
   {
      case IDC_EDT_TERM:
         iPos = strValue.find( I_(" ") );
         dstrSubTerm = strValue.substr( 0, iPos );
         getParent()->setField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractTerm, dstrSubTerm);
         bRtn = true;
         break;
      default :
         bRtn = false;
   }
   sevRtn = NO_CONDITION;
   return(bRtn);
}

//*******************************************************************************************

void ContractInfoDlg1::DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{

   GetDlgItem( IDC_ACC_GR )->EnableWindow( false );
   switch( listControlID )
   {
      case IDC_LV_CONTRACT:
         {
            DString dstrIssueDate;
            getParent()->getField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::IssueDate, dstrIssueDate );
            if( dstrIssueDate == NULL_STRING )
            {
               GetDlgItem( IDC_BTN_GUARANTEE )->EnableWindow( false );
            }
            else
            {
               GetDlgItem( IDC_BTN_GUARANTEE )->EnableWindow( true ); 
            }
            if( ( dstrIssueDate == NULL_STRING ) || ( bIsNewItem ) )
            {
               GetDlgItem( IDDEL )->EnableWindow( true );
            }
            else
               GetDlgItem( IDDEL )->EnableWindow( true );

            // PET1024 FN02 - Set User Def Button
            DString ContMatDateBasedOn, MatDateBasedOn;
            const DString *pKey = &( getParent()->getFirstListItemKey( this, IFASTBP_PROC::MASTER_CONTRACT_LIST ) );
            getParent()->getField( this, BF::NullContainerId, ifds::ContMatDateBasedOn, ContMatDateBasedOn );
            getParent()->getField( this, BF::NullContainerId, ifds::MatDateBasedOn, MatDateBasedOn );
            GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow( ContMatDateBasedOn == I_("02") || MatDateBasedOn == I_("01") );

            // Contract/Deposit Maturity Date Label
            CString cstrLabel;
            cstrLabel.LoadString(  ContMatDateBasedOn == I_("02") ? IDS_TXT_CONTRACT_MATURITY_DATE : IDS_TXT_DEPOSIT_MATURITY_DATE );
            GetDlgItem( IDC_STC_MATURE_DATE )->SetWindowText( cstrLabel );
            break;
         }      
      default:
         break;
   }
}
//*******************************************************************************************

void ContractInfoDlg1::UpdateLatestItemStopDate()
{
   vector<EffectiveDateSort1*> dateList;
   DString dstrEffDate, dstr;
   EffectiveDateSort1* pItem;

   // Keep current item key for resetting
   DString CurrentKey = getParent()->getCurrentListItemKey( this, IFASTBP_PROC::CONTRACTINFO_LIST );
   getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::EffectiveDate, dstrEffDate, false );

   // set vector dateList
   DString dstrKey = (getParent()->getFirstListItemKey(this, IFASTBP_PROC::CONTRACTINFO_LIST));
   while( dstrKey != NULL_STRING )
   {
      getParent()->getField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::EffectiveDate, dstr, false );
      pItem = new EffectiveDateSort1( dstrKey.stripAll(), dstr.stripAll() );
      dateList.push_back( pItem );
      dstrKey = (getParent()->getNextListItemKey(this, IFASTBP_PROC::CONTRACTINFO_LIST));
   }

   // sort the dateList by EffectiveDate
   std::sort(dateList.begin(), dateList.end(), CompareItemPtr);

   // get the latest record and change it's stop date by current record's EffectiveDate - 1
   std::vector<EffectiveDateSort1*>::iterator iter;
   iter = dateList.begin();
   while( iter != dateList.end() )
   {
      if( ( *iter )->key == CurrentKey )
         break;
      iter ++;
   }
   if( iter != dateList.begin() )
   {
      DString dstrEffDateMinusOne;
      if( GetEffDateMinusOne( dstrEffDate, dstrEffDateMinusOne ) )
      {
         iter --;
         getParent()->setCurrentListItem( this, IFASTBP_PROC::CONTRACTINFO_LIST, ( *iter )->key );
         getParent()->setField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::StopDate, dstrEffDateMinusOne, false);
      }
   }
   getParent()->setCurrentListItem( this, IFASTBP_PROC::CONTRACTINFO_LIST, CurrentKey);

   // delete all pointers those are in dateList 
   for( iter = dateList.begin(); iter != dateList.end(); iter++ )
      delete *iter;

   // stop date updateing successful, so change the flag to be false that means no longer need to 
   // call this function any more during the ControlUpdate is involked.
   bEffDateChanged = false;

}


//******************************************************************************
void ContractInfoDlg1::OnKillfocusDtpEffDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   *pResult = 0;
   bEffDateChanged = true;
}

//******************************************************************************
bool ContractInfoDlg1::GetEffDateMinusOne( DString& dstrEffDate, DString& dstrEffDateMinusOne )
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
void ContractInfoDlg1::OnAdd() 
{
   getParent()->setField(this, BF::NullContainerId, CONTRACT::CHECKDOFBIRTH, I_("Y") );
   LoadContractInfo();
   AddToListControl( IDC_LV_CONTRACT );
   GetList( IDC_LV_CONTRACT )->SetFocus();
}

//*****************************************************************************
void ContractInfoDlg1::OnDel() 
{  
   DeleteFromListControl( IDC_LV_CONTRACT ); 
   GetList( IDC_LV_CONTRACT )->SetFocus();
}

//*****************************************************************************

void ContractInfoDlg1::OnBtnUserDefMat() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnUserDefMat"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnUserDefMat" ) );

   // Determine whether it's Contract or Deposit
   DString ContMatDateBasedOn, MatDateBasedOn, IsContract, LegalMaturityDate, SegTransExist, ContractType;
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

   // Set Parameters
   setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNumber );
   setParameter( MFCAN_IP_PARAM::SHR_NUM, m_dstrShareHoldNum );
   setParameter( I_("IsContract"), IsContract );
   setParameter( I_("LegalMaturityDate"), LegalMaturityDate );
   setParameter( MFCAN_IP_PARAM::SEG_TRANS_EXIST, SegTransExist );
   setParameter( MFCAN_IP_PARAM::CONTRACT_TYPE, ContractType );

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
               getParent()->setField( this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractMaturityDate, ContractMaturityDate );
               LoadControl( IDC_DATE_MATURITY );
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

void ContractInfoDlg1::ControlUpdated( UINT controlID, const DString &strValue )
{
   if( controlID == IDC_CMB_CONTRACT_TYPE )
   {
      // PET1024 FN02 - Set User Def Button
      DString ContMatDateBasedOn, MatDateBasedOn;
      const DString *pKey = &( getParent()->getFirstListItemKey( this, IFASTBP_PROC::MASTER_CONTRACT_LIST ) );
      getParent()->getField( this, BF::NullContainerId, ifds::ContMatDateBasedOn, ContMatDateBasedOn );
      getParent()->getField( this, BF::NullContainerId, ifds::MatDateBasedOn, MatDateBasedOn );
      GetDlgItem( IDC_BTN_USERDEFMAT )->EnableWindow( ContMatDateBasedOn == I_("02") || MatDateBasedOn == I_("01") );

      // Contract/Deposit Maturity Date Label
      CString cstrLabel;
      cstrLabel.LoadString(  ContMatDateBasedOn == I_("02") ? IDS_TXT_CONTRACT_MATURITY_DATE : IDS_TXT_DEPOSIT_MATURITY_DATE );
      GetDlgItem( IDC_STC_MATURE_DATE )->SetWindowText( cstrLabel );
   }
}


//******************************************************************************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/contractinfodlg1.cpp-arc  $
// 
//    Rev 1.24   Aug 22 2005 10:51:40   ZHANGCEL
// PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
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
