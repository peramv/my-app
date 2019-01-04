//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial  Ltd.
//
//******************************************************************************
//
// ^FILE   : FeeParamDlg.h
// ^AUTHOR : Yingbao Li
// ^DATE   : 02/28/02
//
// ^CLASS    : FeeParamDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <uibase\DSTEdit.h>
#include "FeeParamDlg.h"
#include <ifastbp\FeeParamProcessInclude.h>
#include <ifastbp\FundClassProcessIncludes.h>
#include <uibase\DSTListCtrl.h>
#include <uibase\DSTComboBox.h>
#include <uibase\DSTOleDateTime.h>
#include <uibase\DSTDateTime.h>


extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_FEE_PARAMETER;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FeeParamDlg > dlgCreator( CMD_GUI_FEE_PARAMETER );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME							= I_( "FeeParamDlg" );
   const I_CHAR * const YES									= I_( "Y" );
   const I_CHAR * const NO										= I_( "N" );

   const I_CHAR* const  LV_ACCOUNT_FEE						= I_( "AccountFee" );
   const I_CHAR* const  LV_SCALE_FEE						= I_( "ScaleFee" );
   const I_CHAR* const  PERCENT								= I_( "Percent" );
   const I_CHAR * const FLAT									= I_( "0" );
   const I_CHAR * const PERCENTAGE							= I_( "1" );
   const I_CHAR * const SCALE									= I_( "2" );
   const I_CHAR * const TIER									= I_( "3" );
   const I_CHAR * const FEE_CODE_MANAGEMENT_FEE			= I_("18");
   const I_CHAR * const FEE_CPDE_MANAGEMENT_REBATE		= I_("95");
   const I_CHAR * const FEE_CODE_MANAGEMENT_DISCOUNT	= I_("180");


   const I_CHAR * const NUMBERS = I_("0123456789.");
	const I_CHAR * const	NOT_APPLY  =  I_("NA");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const FEE_PARAMETER;
}


//******************************************************************************

FeeParamDlg::FeeParamDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FeeParamDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(FeeParamDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
FeeParamDlg::~FeeParamDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void FeeParamDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(FeeParamDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FeeParamDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FeeParamDlg)
ON_BN_CLICKED(IDC_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_ADD_FEE, OnBtnAddFeeParam)
ON_BN_CLICKED(IDC_DEL_FEE, OnBtnDelFeeParam)
ON_BN_CLICKED(IDC_MORE, OnBtnMoreFeeParam)
ON_BN_CLICKED(IDC_ADD_SCALE, OnBtnAddFeeScale)
ON_BN_CLICKED(IDC_DEL_SCALE, OnBtnDelFeeScale)
ON_BN_CLICKED(IDC__ADMIN, OnBtnAdmDates)
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_BN_CLICKED( IDC_BTN_HISTORICAL_ACCOUNT, OnBtnHistoricalAccount)
ON_BN_CLICKED( IDC_BTN_HISTORICAL_SCALE, OnBtnHistoricalScale)

//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FeeParamDlg message handlers


//******************************************************************************
void FeeParamDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   SetUserAccesFunctionCode(UAF::FEE_PARAMETER);
   addBtnAddForPermissionCheck(IDC_ADD_FEE, IDC_ACCOUNT_FEE_LIST);
   addBtnDeleteForPermissionCheck(IDC_DEL_FEE, IDC_ACCOUNT_FEE_LIST);
   addBtnAddForPermissionCheck(IDC_ADD_SCALE, IDC_FEE_SCALE_LIST);
   addBtnDeleteForPermissionCheck(IDC_DEL_SCALE, IDC_FEE_SCALE_LIST);
   addControls();
   GetDlgItem(IDC_BTN_HISTORICAL_ACCOUNT)->EnableWindow(
      getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::FEE_PARAM_LIST) > 0 );
   doRefresh(this, NULL);
   GetDlgItem(IDC_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//******************************************************************************
SEVERITY FeeParamDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;
   return(sevRtn);
}
//******************************************************************************
void FeeParamDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );

   AddListControl( CLASSNAME,IDC_ACCOUNT_FEE_LIST,     LV_ACCOUNT_FEE,     ifds::FeeParamListSet,           IFASTBP_PROC::FEE_PARAM_LIST, 
                   0, true );
   AddControl( CTRL_STATIC, IDC_TXT_GST_EXEMPTION, IFASTBP_PROC::MFACOUNT, ifds::GSTExempt );
   AddControl( CTRL_COMBO,  IDC_CMB_FEE_TYPE,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::FeeCode,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_ACCOUNT_FEE_LIST);
   AddControl( CTRL_STATIC, IDC_TXT_BROKER_CODE, IFASTBP_PROC::FEE_PARAM_LIST, ifds::BrokerCode,
               0, IDC_ACCOUNT_FEE_LIST);

   AddControl( CTRL_DATE,   IDC_DTP_EFFECTIVE_DATE,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::EffectiveDate,0,IDC_ACCOUNT_FEE_LIST);
   AddControl( CTRL_COMBO,  IDC_CMB_COMM_GROUP,  IFASTBP_PROC::FEE_PARAM_LIST,
	   ifds::CommGroup,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_ACCOUNT_FEE_LIST);	
   AddControl( CTRL_COMBO,  IDC_CMB_BASED_ON,  IFASTBP_PROC::FEE_PARAM_LIST,
	   ifds::BasedOn,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_ACCOUNT_FEE_LIST);	

   AddControl( CTRL_DATE,   IDC_DTP_STOP_DATE,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::StopDate,0,IDC_ACCOUNT_FEE_LIST);
   AddControl( CTRL_EDIT,    IDC_FUND_NUM,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::FundNumber,0,IDC_ACCOUNT_FEE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_FUND,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::FundCode,0,IDC_ACCOUNT_FEE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_CLASS,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::ClassCode,0,IDC_ACCOUNT_FEE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_FEE_RATE,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::Rate,0,IDC_ACCOUNT_FEE_LIST);

   AddControl( CTRL_COMBO,    IDC_CMB_SCALE_TYPE,   IFASTBP_PROC::FEE_PARAM_LIST, 
               ifds::ParamFeeType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_ACCOUNT_FEE_LIST);

   AddControl( CTRL_STATIC, IDC_TXT_CURRENCY, IFASTBP_PROC::FEE_PARAM_LIST, ifds::Currency,
               0, IDC_ACCOUNT_FEE_LIST);

   AddListControl( CLASSNAME,IDC_FEE_SCALE_LIST,LV_SCALE_FEE,ifds::FeeScaleListSet,IFASTBP_PROC::FEE_SCALE_LIST, 
                   0, true );

   AddControl( CTRL_STATIC,IDC_TXT_FEE_SCALE_TYPE,BF::NullContainerId,ifds::NullFieldId,CTRLFLAG_GUI_FIELD, IDC_FEE_SCALE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_LOWER_BOUND,   IFASTBP_PROC::FEE_SCALE_LIST, 
               ifds::LowerBound,0,IDC_FEE_SCALE_LIST);

   AddControl( CTRL_EDIT,    IDC_EDT_UPPER_BOUND,   IFASTBP_PROC::FEE_SCALE_LIST, 
               ifds::UpperBound,0,IDC_FEE_SCALE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_SCALE_RATE,   IFASTBP_PROC::FEE_SCALE_LIST, 
               ifds::ScaleRate,0,IDC_FEE_SCALE_LIST);


   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_UPPER_BOUND ) )->SetAllowedChars( NUMBERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_SCALE_RATE ) )->SetAllowedChars( NUMBERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_LOWER_BOUND ) )->SetAllowedChars( NUMBERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_FEE_RATE ) )->SetAllowedChars( NUMBERS );

   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_UPPER_BOUND ) )->SetMaxCharNum( 13 );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_SCALE_RATE ) )->SetMaxCharNum( 13 );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_LOWER_BOUND ) )->SetMaxCharNum( 13 );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_FEE_RATE ) )->SetMaxCharNum( 13 );


}
//******************************************************************************
bool FeeParamDlg::GetDataForControl(UINT controlID,DString &strValueOut,bool bFormatted,int index) const
{
   bool bRet = false;
   switch( controlID )
   {
      case IDC_TXT_FEE_SCALE_TYPE:
         strValueOut = PERCENT;
         bRet = true;  
         break;
      case IDC_TXT_GST_EXEMPTION:
         getParent()->getField( this,IFASTBP_PROC::MFACOUNT,ifds::GSTExempt,strValueOut,bFormatted );
         bRet = true;  
         break;
      case IDC_EDT_FEE_RATE:
         getParent()->getField( this,IFASTBP_PROC::FEE_PARAM_LIST,ifds::Rate,strValueOut,bFormatted );
         bRet = true;  
         break;
		case 	IDC_CMB_COMM_GROUP:
			getParent()->getField(this,IFASTBP_PROC::FEE_PARAM_LIST, ifds::CommGroup, strValueOut,false);
			strValueOut.strip();
			if(strValueOut == NULL_STRING)strValueOut = NOT_APPLY;
			bRet = true;
			break;
   }
   return(bRet);
}
//*******************************************************************************
void FeeParamDlg::DispFeeTypeRelated()
{
   DString dstrFeeType;

   getParent()->getField(this,IFASTBP_PROC::FEE_PARAM_LIST,ifds::ParamFeeType,dstrFeeType,false);
   dstrFeeType.strip();
   bool bShow = dstrFeeType == SCALE || dstrFeeType == TIER;

   ShowControl(IDC_EDT_LOWER_BOUND,bShow );
   ShowControl(IDC_EDT_UPPER_BOUND,bShow );
   ShowControl(IDC_EDT_SCALE_RATE,bShow );
   ShowControl(IDC_TXT_FEE_SCALE_TYPE,bShow );
   int nCmdShow = bShow? SW_SHOW :SW_HIDE;
   GetDlgItem( IDC_TXT_LOWER_BOUND )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_RATE )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_UPPER_BOUND )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_AMT_TYPE )->ShowWindow( nCmdShow ); 
   GetDlgItem( IDC_ADD_SCALE )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_DEL_SCALE )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_BTN_HISTORICAL_SCALE )->ShowWindow( nCmdShow );
   int nCmdShow1 = bShow ? SW_HIDE :SW_SHOW;
   LoadControl(IDC_EDT_FEE_RATE);
   GetDlgItem( IDC_EDT_FEE_RATE )->ShowWindow( nCmdShow1 );
   GetDlgItem( IDC_TXT_FEE_RATE )->ShowWindow( nCmdShow1 );
   ConnectListToData(IDC_FEE_SCALE_LIST,bShow,true);
   if( bShow )
      LoadListControl(IDC_FEE_SCALE_LIST);

}

//*********************************************************************************
void FeeParamDlg::ControlUpdated( UINT controlID,
                                  const DString &strValue )
{
   switch( controlID )
   {
      case IDC_CMB_SCALE_TYPE:
         {
            DispFeeTypeRelated();

            DString dstrFeeType(strValue);
            dstrFeeType.strip().upperCase();

            if( dstrFeeType == SCALE || dstrFeeType == TIER)
            {
               ConnectListToData(IDC_FEE_SCALE_LIST, true);
               ConnectControlToData(IDC_EDT_LOWER_BOUND, true);
               ConnectControlToData(IDC_EDT_UPPER_BOUND, true);
               ConnectControlToData(IDC_EDT_SCALE_RATE, true);

               LoadListControl(IDC_FEE_SCALE_LIST);
               LoadControl(IDC_EDT_LOWER_BOUND);
               LoadControl(IDC_EDT_UPPER_BOUND);
               LoadControl(IDC_EDT_SCALE_RATE);
            }
            else
            {
               ConnectListToData(IDC_FEE_SCALE_LIST, false);
               ConnectControlToData(IDC_EDT_LOWER_BOUND, false);
               ConnectControlToData(IDC_EDT_UPPER_BOUND, false);
               ConnectControlToData(IDC_EDT_SCALE_RATE, false);
            }
         }
         break;

      case IDC_EDT_FUND:
      case IDC_EDT_CLASS:     
         LoadControl( IDC_TXT_CURRENCY );
         break;

      case IDC_CMB_FEE_TYPE: //FeeCode
         {
            bool bShow = strValue != FEE_CODE_MANAGEMENT_DISCOUNT;
            ShowControl(IDC_TXT_CURRENCY,bShow );
            int nCmdShow = bShow? SW_SHOW :SW_HIDE;
            GetDlgItem( IDC_STC_CURRENCY )->ShowWindow( nCmdShow );

         }
         break; 

      default:
         break;

   }
}
//******************************************************************************
void FeeParamDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );
   DString strShrNum, strAccountNum, strEmptyString,dstrEntityName;
   getParent()->getField(this, IFASTBP_PROC::MFACOUNT, ifds::ShrNum, strShrNum, false);
   getParent()->getField(this, IFASTBP_PROC::MFACOUNT, ifds::AccountNum, strAccountNum, false);
   getParent()->getField( this, FEEPARAM::PRIMARY_ACCOUNT_OWNER, dstrEntityName );

   SetShrAcctCaption(strShrNum, strAccountNum, dstrEntityName);
}

//******************************************************************************

bool FeeParamDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   SetDlgCaption();
   ConnectControlsToData();
   LoadListControl(IDC_ACCOUNT_FEE_LIST);
   LoadControl(IDC_TXT_GST_EXEMPTION);
   return(true);
}

//******************************************************************************

BOOL FeeParamDlg::PreTranslateMessage( MSG* pMsg ) 
{

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_FUND_NUM ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_FUND_NUM;
      }
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}
//******************************************************************************
LRESULT FeeParamDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;  

      DString dstrAccountNum,dstrFeeCode;  

      getParent()->getField( this, IFASTBP_PROC::MFACOUNT, ifds::AccountNum, dstrAccountNum, false );
      dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );

      setParameter ( FUNDCLASSLIST::ACCT_NUM , dstrAccountNum );
      getParent()->getField(this,IFASTBP_PROC::FEE_PARAM_LIST,ifds::FeeCode,dstrFeeCode,false);
      dstrFeeCode.strip();
      DString dstrManagementFee = NULL_STRING;
      DString dstrManagementFeeRebate = NULL_STRING;
      if( FEE_CODE_MANAGEMENT_FEE == dstrFeeCode )
      {
         dstrManagementFee = YES;    
      }
      else if( FEE_CPDE_MANAGEMENT_REBATE == dstrFeeCode )
      {
         dstrManagementFeeRebate = YES;
      }
      setParameter ( FUNDCLASSLIST::MANAGEMENTFEE, dstrManagementFee);
      setParameter ( FUNDCLASSLIST::MANAGEMENTFEE_REBATE, dstrManagementFeeRebate);
      switch( m_uiClassCodeDialogItem )
      {
         case IDC_EDT_FUND:
            {
               CString cstrFundCode;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundCode );
               DString dstrFundCode = cstrFundCode;
               setParameter( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_CLASS:
            {
               CString cstrFundClass;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundClass );
               DString dstrFundClass = cstrFundClass;
               setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::CLASS_CODE, dstrFundClass );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;
         case IDC_FUND_NUM:
            {
               CString cstrFundNumber;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundNumber );
               DString dstrFundNumber = cstrFundNumber;
               setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, dstrFundNumber );
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
               getParameter ( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               getParameter ( FUNDCLASSLIST::CLASS_CODE, dstrClassCode );
               getParameter ( FUNDCLASSLIST::FUND_NUMBER, dstrFundNumber );
               getParent()->setField (this,IFASTBP_PROC::FEE_PARAM_LIST, ifds::FundCode, dstrFundCode );
               getParent()->setField (this,IFASTBP_PROC::FEE_PARAM_LIST, ifds::ClassCode, dstrClassCode );
               if( dstrFundCode.strip()== NULL_STRING &&  dstrClassCode.strip() == NULL_STRING )
                  getParent()->setField (this, IFASTBP_PROC::FEE_PARAM_LIST, ifds::FundNumber, dstrFundNumber );
               LoadControl(IDC_EDT_FUND );
               LoadControl(IDC_EDT_CLASS );
               LoadControl(IDC_FUND_NUM );
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
//******************************************************************
void FeeParamDlg::OnBtnHistoricalAccount()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;
   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::FEE_PARAM_LIST);
}

//******************************************************************
void FeeParamDlg::OnBtnHistoricalScale()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;
   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::FEE_SCALE_LIST);
}

//******************************************************************************
void FeeParamDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnReset" ) );
   ResetListItem( IDC_ACCOUNT_FEE_LIST );
   GetList( IDC_ACCOUNT_FEE_LIST )->SetFocus();
}

//*********************************************************************************
void FeeParamDlg::OnBtnAddFeeParam()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddFeeParam" ) );
   AddToListControl( IDC_ACCOUNT_FEE_LIST );
   GetList( IDC_ACCOUNT_FEE_LIST )->SetFocus();
}

//********************************************************************************
void FeeParamDlg::OnBtnDelFeeParam()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelFeeParam" ) );
   DeleteFromListControl( IDC_ACCOUNT_FEE_LIST );
   GetList( IDC_ACCOUNT_FEE_LIST )->SetFocus();
}

//**********************************************************************************
void FeeParamDlg::OnBtnMoreFeeParam()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnMoreFeeParam" ) );
   CWaitCursor wait;
   static int cursel;
   cursel = GetList( IDC_ACCOUNT_FEE_LIST )->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);  
   const DString *crtKey = &getParent()->getCurrentListItemKey( this,IFASTBP_PROC::FEE_PARAM_LIST );
   if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_ACCOUNT_FEE_LIST );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_ACCOUNT_FEE_LIST )->SetSelection( crtKey );
      }
   }
   GetDlgItem(IDC_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   GetList( IDC_ACCOUNT_FEE_LIST )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);   
}

//**********************************************************************************
void FeeParamDlg::OnBtnAddFeeScale()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddFeeScale" ) );
   AddToListControl( IDC_FEE_SCALE_LIST );
   GetList( IDC_FEE_SCALE_LIST )->SetFocus();
}
//**********************************************************************************
void FeeParamDlg::OnBtnDelFeeScale()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelFeeScale" ) );
   DeleteFromListControl( IDC_FEE_SCALE_LIST );
   LoadListControl( IDC_FEE_SCALE_LIST );
   GetList( IDC_FEE_SCALE_LIST )->SetFocus();
}

//********************************************************************************
bool FeeParamDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{
   DString str;  
   if( lSubstituteId == ifds::FeeScaleListSet.getId() )
   {
      if( ColumnKey == I_("Type") )
      {
         strOut = PERCENT;   
         return(true);
      }
   }

   if( lSubstituteId == ifds::FeeParamListSet.getId() )
   {
      if( ColumnKey == I_("Status") )
      {
         getParent()->getField(this,IFASTBP_PROC::FEE_PARAM_LIST,ifds::Status,strOut); 
         return(true);
      }
   }



   return(false);

}

//**********************************************************************************
void FeeParamDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::FEE_PARAM_LIST );
}

//************************************************************************************
void FeeParamDlg::DoListItemChanged(
                                   UINT listControlID,
                                   const DString &strKey, 
                                   bool bIsNewItem ,
                                   bool bIsDummyItem
                                   )
{
   if( listControlID == IDC_ACCOUNT_FEE_LIST )
   {
      DString dstrFeeType;
      getParent()->getField(this,IFASTBP_PROC::FEE_PARAM_LIST,ifds::ParamFeeType,dstrFeeType,false);
      dstrFeeType.strip();
      if( dstrFeeType == SCALE || dstrFeeType == TIER )
      {
         ConnectControlsToData(IDC_FEE_SCALE_LIST,true);
         LoadListControl( IDC_FEE_SCALE_LIST );
      }
      else
      {
         ConnectControlsToData(IDC_FEE_SCALE_LIST,false);    
      }

      // Historical
      GetDlgItem(IDC_BTN_HISTORICAL_ACCOUNT)->EnableWindow( (bIsNewItem || bIsDummyItem) ? FALSE : TRUE );
   }
   else if( listControlID == IDC_FEE_SCALE_LIST)
   {
      // Historical
      GetDlgItem(IDC_BTN_HISTORICAL_SCALE)->EnableWindow( (bIsNewItem || bIsDummyItem) ? FALSE : TRUE );
   }
}

//******************************************************************************

void FeeParamDlg::InitControl(
                         UINT controlID
                         )
{

/*	switch(controlID)
	{

		default:

		break;
	}
*/
}


//****************************************************************************

bool FeeParamDlg::SetDataFromControl(
                                UINT controlID,
                                const DString &strValue,
                                bool bFormatted,
                                SEVERITY &sevRtn,
                                int index
                                )
{
	bool bRet = false;
	switch(controlID)
	{
	case 	IDC_CMB_COMM_GROUP:
		{
			DString dstr;
			if( strValue != NOT_APPLY ) dstr = strValue;
			sevRtn = getParent()->setField( this, IFASTBP_PROC::FEE_PARAM_LIST, ifds::CommGroup, dstr,false );
			bRet =  true;
			break;
		}

	case  IDC_DTP_STOP_DATE:
		{
	       DSTOleDateTime date;
		   DSTDateTime* pdt = dynamic_cast<DSTDateTime* >( GetControl(controlID ));
			if(pdt )
			{
			  pdt->GetTime(date);
			  CString tmp;
			  DString dstr;
              date.DSTHostFormat( tmp );
              dstr = tmp.GetBuffer(0);
              tmp.ReleaseBuffer(-1);
      		  getParent()->setField( this, IFASTBP_PROC::FEE_PARAM_LIST, ifds::StopDate, dstr,false );
              bRet = true;

			}
		    break;
		}

	default:
		break;

	}
	return bRet;
}

//*****************************************************************************
bool FeeParamDlg::doDisableControl(UINT nID, bool bIsNew)
{
   const DString *crtKey = &getParent()->getCurrentListItemKey( this,IFASTBP_PROC::FEE_PARAM_LIST );
	if( crtKey )
	{
		DString dstrModPerm;
		getParent()->getField(this, IFASTBP_PROC::FEE_PARAM_LIST,ifds::ModPerm,dstrModPerm,false );
		dstrModPerm.strip().upperCase();
		if(dstrModPerm == NO && !bIsNew  )
			return true;
	}
	return false;

};
//******************************************************************************
bool FeeParamDlg::doDisablePermCheckButton(UINT nID)
{
	if( nID == IDC_ADD_SCALE || nID ==IDC_DEL_SCALE )
	{
		const DString *crtKey = &getParent()->getCurrentListItemKey( this,IFASTBP_PROC::FEE_PARAM_LIST );
		if( crtKey )
		{
			DString dstrModPerm;
			getParent()->getField(this, IFASTBP_PROC::FEE_PARAM_LIST,ifds::ModPerm,dstrModPerm,false );
			dstrModPerm.strip().upperCase();
			if( dstrModPerm == NO  )
				return true;			
		}
	}
	return(false);
}

//***************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FeeParamDlg.cpp-arc  $
// 
//    Rev 1.32   Mar 12 2012 15:06:02   dchatcha
// IN# 2864027 - NCE_MF Offset Rate_Program error if setup offset with FeeType Scale or Tier
// 
//    Rev 1.31   Sep 15 2005 15:12:06   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.30   Nov 12 2004 16:59:30   YINGBAOL
// PTS10034116: when user change stop date from a validate date to 12/31/9999, desktop save empty string to the database.
// 
//    Rev 1.29   Feb 28 2004 16:34:04   HERNANDO
// PET965 FN11 - Enable/Disable Historical Button based on list item in doListItemChanged.
// 
//    Rev 1.28   Oct 27 2003 17:39:30   linmay
// PTS Ticket #10023393, modified dispFeeTypeRelated()
// 
//    Rev 1.27   Oct 27 2003 14:49:22   YINGBAOL
// PTS10021667 restricting number of characters for numeric fields, 
// 
//    Rev 1.26   Jun 03 2003 10:05:34   linmay
// added BasedOn field
// 
//    Rev 1.25   Apr 12 2003 18:38:16   YINGBAOL
// small fix
// 
//    Rev 1.24   Mar 21 2003 18:36:22   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.23.1.0   Mar 05 2003 11:31:18   PURDYECH
// Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
// 
//    Rev 1.23   Feb 20 2003 09:28:02   YINGBAOL
// add doDisableControl and doDisablePermCheckButton
// 
//    Rev 1.22   Feb 14 2003 16:26:18   linmay
// added brokercode
// 
//    Rev 1.21   Jan 29 2003 18:42:30   popescu
// disable the historical button for the Account level fee list
// 
//    Rev 1.20   Jan 29 2003 16:26:46   popescu
// Disableing the historical button for the scale list
// 
//    Rev 1.19   Jan 29 2003 16:22:22   popescu
// Added the historical button for FeeParamSysDlg and FeeParamDlg
// 
//    Rev 1.18   Jan 22 2003 17:49:28   YINGBAOL
// clean some unused code
// 
//    Rev 1.17   Jan 03 2003 19:39:28   YINGBAOL
// add logic for commission Group
// 
//    Rev 1.16   Jan 03 2003 16:26:34   linmay
// rename CommGroupCode to FundGroup
// 
//    Rev 1.15   Jan 02 2003 15:11:06   linmay
// add control for CommGroup
// 
//    Rev 1.14   Oct 09 2002 23:55:40   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.13   Sep 30 2002 11:01:40   PURDYECH
// BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
// 
//    Rev 1.12   Aug 29 2002 12:57:20   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.11   Aug 12 2002 13:36:44   YINGBAOL
// adjust sequence for set fundnumber
// 
//    Rev 1.10   Jun 17 2002 11:03:54   YINGBAOL
// fix FundClass problem when select one from FundClass screen
// 
//    Rev 1.9   22 May 2002 19:16:02   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   Apr 04 2002 11:46:36   YINGBAOL
// reload list after delete an item
// 
//    Rev 1.7   27 Mar 2002 20:01:08   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.6   Mar 21 2002 13:23:32   YINGBAOL
// small change
// 
//    Rev 1.5   Mar 19 2002 09:45:52   YINGBAOL
// add Fee Discount
// 
//    Rev 1.4   Feb 27 2002 13:15:38   YINGBAOL
// load currency when FundCode or Class Code changed
// 
//    Rev 1.3   Feb 26 2002 13:09:50   YINGBAOL
// limit charactters for Rate etc..
// 
//    Rev 1.2   Feb 26 2002 10:30:24   YINGBAOL
// populate Fund Class and Fund Number
// 
//    Rev 1.1   Feb 22 2002 14:17:28   YINGBAOL
// add more function
// 
//    Rev 1.0   Feb 01 2002 15:16:14   YINGBAOL
// Initial revision.
 * 


*/





