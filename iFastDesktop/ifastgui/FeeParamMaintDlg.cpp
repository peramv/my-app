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
// ^FILE   : FeeParamMaintDlg.h
// ^AUTHOR : 
// ^DATE   : 07/26/04
//
// ^CLASS    : FeeParamMaintDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <uibase\DSTEdit.h>
#include "feeparammaintdlg.h"
#include <ifastbp\feeparammaintprocessinclude.h>
#include <uibase\DSTListCtrl.h>
#include <uibase\DSTComboBox.h>
#include <ifastbp/mfcaninterprocparam.hpp>
#include <discardmsgdlg.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastbp\FeeParamMaintProcess.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FEE_PARAM_MAINT;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FeeParamMaintDlg > dlgCreator( CMD_GUI_FEE_PARAM_MAINT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADMINDATES;

namespace
{
   const I_CHAR * const CLASSNAME                     = I_( "FeeParamMaintDlg" );
   const I_CHAR * const YES                           = I_( "Y" );
   const I_CHAR * const NO                            = I_( "N" );

   const I_CHAR* const  LV_FEE_MODEL_LIST             = I_( "FeeParamMaint" );
   const I_CHAR* const  LV_SCALE_FEE                  = I_( "ScaleFee" );
   const I_CHAR* const  PERCENT                       = I_( "Percent" );
   const I_CHAR * const FLAT                          = I_( "0" );
   const I_CHAR * const PERCENTAGE                    = I_( "1" );
   const I_CHAR * const SCALE                         = I_( "2" );
   const I_CHAR * const TIER                          = I_( "3" );
   const I_CHAR * const FEE_CODE_MANAGEMENT_FEE       = I_("18");
   const I_CHAR * const FEE_CPDE_MANAGEMENT_REBATE    = I_("95");
   const I_CHAR * const FEE_CODE_MANAGEMENT_DISCOUNT  = I_("180");


   const I_CHAR * const NUMBERS = I_("0123456789.");
   const I_CHAR * const	NOT_APPLY  =  I_("NA");

   const I_CHAR *MODUSER                  = I_( "ModUser" );
   const I_CHAR *MODDATE                  = I_( "ModDate" );
   const I_CHAR *PROCESSUSER              = I_( "Username" );
   const I_CHAR *PROCESSDATE              = I_( "ProcessDate" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const FEE_PARAMETER_SYSTEM;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
}

//******************************************************************************

FeeParamMaintDlg::FeeParamMaintDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FeeParamMaintDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(FeeParamMaintDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
FeeParamMaintDlg::~FeeParamMaintDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void FeeParamMaintDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(FeeParamMaintDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FeeParamMaintDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FeeParamMaintDlg)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_ADD_THRSHLD, OnBtnAddThrshld)
ON_BN_CLICKED(IDC_BTN_DEL_THRSHLD, OnBtnDelThrshld)
ON_BN_CLICKED(IDC_BTN_ADD_SCALE, OnBtnAddScale)
ON_BN_CLICKED(IDC_BTN_DEL_SCALE, OnBtnDelScale)
ON_BN_CLICKED(IDC_ADMIN_SCALE, OnBtnAdmDatesScale)
ON_BN_CLICKED(IDC_ADMIN_THRSHLD, OnBtnAdmDatesThrshld)

ON_BN_CLICKED(IDC_BTN_HISTORICAL_THRSHLD, OnBtnHistThrshld)
ON_BN_CLICKED(IDC_BTN_HISTORICAL_SCALE,   OnBtnHistScale)
//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FeeParamMaintDlg message handlers


//******************************************************************************
void FeeParamMaintDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );

   SetUserAccesFunctionCode (UAF::FEE_PARAMETER_SYSTEM);

	addControlGroupIDForPermissionCheck(IDC_FEE_SCALE_LIST);
   addControlGroupIDForPermissionCheck(IDC_FEE_TRESHOLD_LIST);

   addBtnAddForPermissionCheck(IDC_BTN_ADD_SCALE,      IDC_FEE_SCALE_LIST);
   addBtnDeleteForPermissionCheck(IDC_BTN_DEL_SCALE,   IDC_FEE_SCALE_LIST);

   addBtnAddForPermissionCheck(IDC_BTN_ADD_THRSHLD,    IDC_FEE_TRESHOLD_LIST);
//   addBtnDeleteForPermissionCheck(IDC_BTN_DEL_THRSHLD, IDC_FEE_TRESHOLD_LIST);

   addControls();
   doRefresh(this, NULL);
   DispScaleFeeTypeRelated();
}

//**********************************************************************************
bool FeeParamMaintDlg::doDisablePermCheckButton(UINT nID)
{
   FeeParamMaintProcess* pFeeParamMaintProcess = dynamic_cast<FeeParamMaintProcess*>(getParent());
   if(!pFeeParamMaintProcess->canUpdate())
   {
      return true;
   }

   if(nID == IDC_BTN_ADD_THRSHLD && 
      (m_FeeType != FEETYPE::TIER_BY_THRESHOLD && 
      m_FeeType != FEETYPE::SCALE_BY_THRESHOLD))
   {      
      return true;
   }


   return false;
}

//******************************************************************************
SEVERITY FeeParamMaintDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;
   getParameter (MFCAN_IP_PARAM::FEE_TYPE, m_FeeType);
   
   return(sevRtn);
}
//******************************************************************************
void FeeParamMaintDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );

   AddListControl( CLASSNAME, IDC_FEE_SCALE_LIST, I_("SYSTEM_FEE_SCALE_LIST"),
                   ifds::FeeScaleSysHeading, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, IDC_SYSTEM_FEE_LIST, true);

   if(m_FeeType == FEETYPE::TIER_BY_THRESHOLD ||
      m_FeeType == FEETYPE::SCALE_BY_THRESHOLD)
   {
      AddListControl( CLASSNAME, IDC_FEE_TRESHOLD_LIST, I_("SYSTEM_FEE_THRESHOLD_LIST"),
                     ifds::FeeThresholdSysHeading, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, IDC_SYSTEM_FEE_LIST, true);
   }

   AddControl(CTRL_COMBO, IDC_CMB_FEE_CODE,       IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FeeCode,      CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_NOT_UPDATABLE);
   AddControl(CTRL_COMBO, IDC_CMB_SCALE_TYPE,     IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ParamFeeType, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_NOT_UPDATABLE);
   AddControl(CTRL_EDIT,  IDC_EDT_FROM_FUND,      IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FundCode,     CTRLFLAG_NOT_UPDATABLE);
   AddControl(CTRL_EDIT,  IDC_EDT_FROM_FUND_CLASS,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ClassCode,    CTRLFLAG_NOT_UPDATABLE);
   AddControl(CTRL_COMBO, IDC_CMB_COMM_GROUP,     IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::CommGroup,    CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_NOT_UPDATABLE);	
   AddControl(CTRL_EDIT,  IDC_EDT_FEE_MODEL,      IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FeeModelCode, CTRLFLAG_NOT_UPDATABLE);
   AddControl(CTRL_COMBO, IDC_CMB_CURRENCY,       IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::Currency,     CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_NOT_UPDATABLE);    
   AddControl(CTRL_COMBO, IDC_CMB_TAX_INCLUSIVE,  IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::TaxInclusive, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_NOT_UPDATABLE);    
   

   AddControl( CTRL_EDIT, IDC_EDT_LOWER_BOUND,  IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, ifds::LowerBound, 0,IDC_FEE_SCALE_LIST);    
   AddControl( CTRL_EDIT, IDC_EDT_UPPER_BOUND,  IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, ifds::UpperBound, 0,IDC_FEE_SCALE_LIST);    
   AddControl( CTRL_EDIT, IDC_EDT_SCALE_RATE,   IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, ifds::ScaleRate,  0,IDC_FEE_SCALE_LIST);    
   AddControl( CTRL_EDIT, IDC_EDT_MIN,          IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, ifds::MinFee,     0,IDC_FEE_SCALE_LIST);    
   AddControl( CTRL_EDIT, IDC_EDT_MAX,          IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, ifds::MaxFee,     0,IDC_FEE_SCALE_LIST);    
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_MIN ) )->SetMaxCharNum( 9 );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_MAX ) )->SetMaxCharNum( 9 );
   
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_LOWER_BOUND) )->SetMaxCharNum( 13 );
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_UPPER_BOUND) )->SetMaxCharNum( 13 );
   if(m_FeeType == FEETYPE::TIER_BY_THRESHOLD ||
      m_FeeType == FEETYPE::SCALE_BY_THRESHOLD)
   {
      AddControl( CTRL_EDIT, IDC_EDT_TRSHLD_LEVEL,       IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, ifds::ThrshldLevel,0,IDC_FEE_TRESHOLD_LIST);
      AddControl( CTRL_EDIT, IDC_EDT_TRSHLD_LOWER_BOUND, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, ifds::ThrshldLower,0,IDC_FEE_TRESHOLD_LIST);
      AddControl( CTRL_EDIT, IDC_EDT_TRSHLD_UPPER_BOUND, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, ifds::ThrshldUpper,0,IDC_FEE_TRESHOLD_LIST);
      dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_TRSHLD_LOWER_BOUND) )->SetMaxCharNum( 13 );
      dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_TRSHLD_UPPER_BOUND) )->SetMaxCharNum( 13 );
    }
   else if(m_FeeType == FEETYPE::PERCENTAGE)
   {
	   //invest term scale
		AddControl ( CTRL_STATIC, IDC_TXT_SCALE_INV_TERM, CTRLFLAG_GUI_FIELD);
		AddControl ( CTRL_EDIT,   IDC_EDT_SCALE_INV_TERM,   IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, 
				       ifds::InvestTerm, 0, IDC_FEE_SCALE_LIST);
		dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_SCALE_INV_TERM) )->SetMaxCharNum( 13 );
		dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_SCALE_INV_TERM) )->SetAllDigits(true);
   }

//   GetControl(IDC_EDT_FROM_FUND)->SetCtrlReadOnly(true); 
//IDC_CMB_FEE_CODE,      
//IDC_CMB_SCALE_TYPE,    
//,     
//IDC_EDT_FROM_FUND_CLASS
//IDC_CMB_COMM_GROUP,    
//IDC_EDT_FEE_MODEL,     
//IDC_CMB_CURRENCY,      
//IDC_CMB_TAX_INCLUSIVE, 


   //AddListControl( CLASSNAME,IDC_LST_FEE_MODEL,     LV_FEE_MODEL_LIST,     ifds::FeeParamMaintListSet,           IFASTBP_PROC::FEE_MODEL_LIST, 
   //                0, true );

   //AddControl( CTRL_EDIT,    IDC_EDT_MODEL_CODE,   IFASTBP_PROC::FEE_MODEL_LIST, 
   //            ifds::FeeParamMaintCode,0,IDC_LST_FEE_MODEL);
   //AddControl( CTRL_EDIT,    IDC_EDT_DESCRIPTION,   IFASTBP_PROC::FEE_MODEL_LIST, 
   //            ifds::FeeParamMaintDesc,0,IDC_LST_FEE_MODEL);
   //AddControl( CTRL_COMBO,   IDC_CMB_FEE_MODEL_TYPE,   IFASTBP_PROC::FEE_MODEL_LIST, 
   //            ifds::FeeParamMaintType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_FEE_MODEL);
   //AddControl( CTRL_DATE,   IDC_DTP_EFFECTIVE,   IFASTBP_PROC::FEE_MODEL_LIST, 
   //            ifds::EffectiveDate,0,IDC_LST_FEE_MODEL);
   //AddControl( CTRL_DATE,   IDC_DTP_STOP,   IFASTBP_PROC::FEE_MODEL_LIST, 
   //            ifds::StopDate,0,IDC_LST_FEE_MODEL);

 //  dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_MODEL_CODE ) )->SetMaxCharNum( 6 );

}

//*********************************************************************************
void FeeParamMaintDlg::ControlUpdated(UINT controlID,
                                 const DString &strValue )
{
   switch( controlID )
   {
	   case IDC_CMB_SCALE_TYPE:
      {
		  if(m_FeeType == FEETYPE::PERCENTAGE)
			  {
				  ReInitListControl (IDC_FEE_SCALE_LIST, 
                            ifds::FeeScaleSysInvestTermHeading, 
                            IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST,
                            I_("SYSTEM_FEE_SCALE_LIST"));
				  ConnectListToData (IDC_FEE_SCALE_LIST, true, true);
				  LoadListControl (IDC_FEE_SCALE_LIST);
		  }
		  DispScaleFeeTypeRelated();
		  break;
      }
      case IDC_EDT_MODEL_CODE: //FeeCode
         {
         }
         break; 

      default:
         break;

   }
}
//******************************************************************************
void FeeParamMaintDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );
/*   DString strShrNum, strAccountNum, strEmptyString,dstrEntityName;
   getParent()->getField(this, IFASTBP_PROC::MFACOUNT, ifds::ShrNum, strShrNum, false);
   getParent()->getField(this, IFASTBP_PROC::MFACOUNT, ifds::AccountNum, strAccountNum, false);
   getParent()->getField( this, FEEPARAM::PRIMARY_ACCOUNT_OWNER, dstrEntityName );

   SetShrAcctCaption(strShrNum, strAccountNum, dstrEntityName);*/
}

//******************************************************************************

bool FeeParamMaintDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   SetDlgCaption();
   ConnectControlsToData();
   LoadControls(IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST);
   LoadListControl(IDC_FEE_SCALE_LIST);

   if(m_FeeType == FEETYPE::TIER_BY_THRESHOLD || 
      m_FeeType == FEETYPE::SCALE_BY_THRESHOLD)
   {
      LoadListControl(IDC_FEE_TRESHOLD_LIST);
   }

   if(m_FeeType == FEETYPE::TIER_BY_THRESHOLD ||
      m_FeeType == FEETYPE::SCALE_BY_THRESHOLD)
   {
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      bool enableThrshldDel = dstWorkSession->hasDeletePermission(UAF::FEE_PARAMETER_SYSTEM);
      if(GetList(IDC_FEE_TRESHOLD_LIST)->GetItemCount() < 1)
         enableThrshldDel = false;
      FeeParamMaintProcess* pFeeParamMaintProcess = dynamic_cast<FeeParamMaintProcess*>(getParent());
      if(!pFeeParamMaintProcess->canUpdate())
         enableThrshldDel = false;

      GetDlgItem (IDC_BTN_DEL_THRSHLD)->EnableWindow (enableThrshldDel);
   }
   else
   {
      GetDlgItem (IDC_EDT_TRSHLD_LEVEL)->EnableWindow (false);
      GetDlgItem (IDC_EDT_TRSHLD_LOWER_BOUND)->EnableWindow (false);
      GetDlgItem (IDC_EDT_TRSHLD_UPPER_BOUND)->EnableWindow (false);

      GetDlgItem(IDC_BTN_ADD_THRSHLD)->EnableWindow (false);
      GetDlgItem(IDC_BTN_DEL_THRSHLD)->EnableWindow (false);
      GetDlgItem(IDC_ADMIN_THRSHLD)->EnableWindow (false);
      GetDlgItem(IDC_BTN_HISTORICAL_THRSHLD)->EnableWindow (false);
      GetDlgItem(IDC_TXT_TRSHLD_LEVEL)->EnableWindow (false);
      GetDlgItem(IDC_TXT_TRSHLD_LOWER_BOUND)->EnableWindow (false);
      GetDlgItem(IDC_TXT_TRSHLD_UPPER_BOUND)->EnableWindow (false);
   }

   return(true);
}

//******************************************************************************
void FeeParamMaintDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnReset" ) );
   //ResetListItem( IDC_LST_FEE_MODEL );
   //GetList( IDC_LST_FEE_MODEL )->SetFocus();  
}

//*********************************************************************************
void FeeParamMaintDlg::OnBtnAddThrshld()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddThrshld" ) );
   AddToListControl( IDC_FEE_TRESHOLD_LIST );
   GetList( IDC_FEE_TRESHOLD_LIST )->SetFocus();
}

void FeeParamMaintDlg::OnBtnAddScale()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddScale" ) );
   AddToListControl( IDC_FEE_SCALE_LIST );
   GetList( IDC_FEE_SCALE_LIST )->SetFocus();
}
//********************************************************************************
void FeeParamMaintDlg::OnBtnDelThrshld()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelThrshld" ) );
   DeleteFromListControl( IDC_FEE_TRESHOLD_LIST );
   GetList( IDC_FEE_TRESHOLD_LIST )->SetFocus();
}

void FeeParamMaintDlg::OnBtnDelScale()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelScale" ) );
   DeleteFromListControl( IDC_FEE_SCALE_LIST );
   GetList( IDC_FEE_SCALE_LIST )->SetFocus();
}

//**********************************************************************************
void FeeParamMaintDlg::OnBtnAdmDatesScale() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAdmDatesScale" ) );
   DString str;

   getParent()->getField( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, ifds::ThrshldModUser, str );
   str.strip();
   setParameter(MODUSER, str );
   getParent()->getField( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, ifds::ThrshldModDate, str );
   str.strip();
   setParameter(MODDATE, str );
   getParent()->getField( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, ifds::ProcessDate, str );
   str.strip();
   setParameter(PROCESSDATE, str );
   getParent()->getField( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, ifds::ThrshldUserName, str );
   str.strip();
   setParameter(PROCESSUSER, str );

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ADMINDATES, PROC_NO_TYPE, true, NULL );
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
void FeeParamMaintDlg::OnBtnAdmDatesThrshld() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAdmDatesThrshld"));
   DString str;

   getParent()->getField( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, ifds::ThrshldModUser, str );
   str.strip();
   setParameter(MODUSER, str );
   getParent()->getField( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, ifds::ThrshldModDate, str );
   str.strip();
   setParameter(MODDATE, str );
   getParent()->getField( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, ifds::ThrshldProcDate, str );
   str.strip();
   setParameter(PROCESSDATE, str );
   getParent()->getField( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, ifds::ThrshldUserName, str );
   str.strip();
   setParameter(PROCESSUSER, str );

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ADMINDATES, PROC_NO_TYPE, true, NULL );
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


//******************************************************************************
void FeeParamMaintDlg::DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey,
                                 bool bIsNewItem ,
                                 bool bIsDummyItem
                                 )
{
	if( listControlID ==  IDC_FEE_TRESHOLD_LIST  )
	{
		LoadListControl( IDC_FEE_SCALE_LIST, &strKey );
	}
}




//******************************************************************************
void FeeParamMaintDlg::OnBtnHistScale()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnHistScale" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;

   IFastHistoricalInfo historicalInfo;
   historicalInfo( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, I_("SINGLE") );
}

//******************************************************************************
void FeeParamMaintDlg::OnBtnHistThrshld()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnHistThrshld" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;

   IFastHistoricalInfo historicalInfo;
   historicalInfo( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, I_("SINGLE") );
}

bool FeeParamMaintDlg::canCancel()
{
   if(getParent()->workSessionHasUpdates())
   {
      DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_MSGA, TXT_DISCARD_MSGB, TXT_DISCARD);

      return(discardDlg.DoModal() != IDCANCEL);         
   }

   return(true);
}

//*******************************************************************************
void FeeParamMaintDlg::DispScaleFeeTypeRelated ()
{
	bool bShowScale = m_FeeType == FEETYPE::SCALE || m_FeeType == FEETYPE::TIER; 
    bool bShowTerm = m_FeeType == FEETYPE::PERCENTAGE;
	auto nCmdShowScale = bShowScale ? SW_SHOW : SW_HIDE;
    auto nCmdShowTerm = bShowTerm ? SW_SHOW : SW_HIDE;
   
	ShowControl (IDC_EDT_SCALE_RATE, bShowScale || bShowTerm);
	GetDlgItem (IDC_TXT_RATE)->ShowWindow ((bShowScale || bShowTerm)? SW_SHOW : SW_HIDE);

	//invest term
	GetDlgItem (IDC_TXT_SCALE_INV_TERM)->ShowWindow (nCmdShowTerm);
	GetDlgItem (IDC_EDT_SCALE_INV_TERM)->ShowWindow (nCmdShowTerm);
	
	//scale features
    ShowControl (IDC_EDT_LOWER_BOUND, bShowScale);
    ShowControl (IDC_EDT_UPPER_BOUND, bShowScale);
    ShowControl (IDC_EDT_MIN, bShowScale);
    ShowControl (IDC_EDT_MAX, bShowScale);

    GetDlgItem (IDC_TXT_LOWER_BOUND)->ShowWindow (nCmdShowScale);
    GetDlgItem (IDC_TXT_UPPER_BOUND)->ShowWindow (nCmdShowScale);
    GetDlgItem (IDC_TXT_MIN)->ShowWindow (nCmdShowScale);
    GetDlgItem (IDC_TXT_MAX)->ShowWindow (nCmdShowScale);
}
