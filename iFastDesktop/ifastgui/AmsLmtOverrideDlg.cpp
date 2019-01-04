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
//    Copyright 2002 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : AmsLmtOverrideDlg.cpp
// ^AUTHOR : May Lin
// ^DATE   : May. 7,2003
//
// ----------------------------------------------------------
//
// ^CLASS    : AmsLmtOverrideDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "AmsLmtOverrideDlg.h"
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\AmsLmtOverrideProcessincludes.h>
#include <uibase\dstedit.h>
#include <bfproc\abstractprocess.hpp>


#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_AMS_LMT_OVERRIDE;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AmsLmtOverrideDlg > dlgCreator( CMD_GUI_AMS_LMT_OVERRIDE );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME			= I_("AmsLmtOverrideDlg");
   const I_CHAR * const YES					= I_("Y");
   const I_CHAR * const NO					= I_("N");
   const I_CHAR * const COLUMN				= I_( ":" );
   const I_CHAR * const SPACE				= I_( " " );
   const I_CHAR *const ALLOWED_TAX_TYPES	= I_("0123456789,ABCDEFGHIKLMNPRTX!*");
   const I_CHAR *const ALLOWED_ACCOUNT_TYPES = I_("0123456789,*!FGNM");
   const I_CHAR * const AMS_DETAIL			= I_( "AMSDetail" );  


}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
}

namespace UAF
{
// extern CLASS_IMPORT I_CHAR * const AMS_LMT_OVERRIDE;
	extern CLASS_IMPORT I_CHAR * const AMS_GLOBAL;

}


//*****************************************************************************
// Public methods
//*****************************************************************************
AmsLmtOverrideDlg::AmsLmtOverrideDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AmsLmtOverrideDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(AmsLmtOverrideDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void AmsLmtOverrideDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AmsLmtOverrideDlg)

   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY AmsLmtOverrideDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );
//   getParameter( AMS_LMT_Para::AMS_EFFECTIVE_DATE, _dstrEffectiveDate );
   getParameter( AMS_LMT_Para::AMS_CODE, _dstrAmsCode );
   getParameter( AMS_LMT_Para::FROM_SCR, _dstrFromScr );

   return(NO_CONDITION);
}

//******************************************************************************
bool AmsLmtOverrideDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   return(true);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(AmsLmtOverrideDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AmsLmtOverrideDlg)

ON_BN_CLICKED( IDC_BTN_RESET,  OnBtnReset )
ON_BN_CLICKED( IDC_BTN_ADD,  OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DELETE,  OnBtnDel )
ON_BN_CLICKED( IDC_BTN_ADM_DATES,  OnBtnAdmDates )
ON_BN_CLICKED( IDC_BTN_HISTORICAL,  OnBtnHistorical )
ON_BN_CLICKED( IDC_BTN_MORE,  OnBtnMore )


//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL AmsLmtOverrideDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();
   setDlgTitle();
   return(TRUE);
}


//******************************************************************************
void AmsLmtOverrideDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));

	ResetListItem( IDC_LV_AMS_LMT_OVERRIDE_LIST );

}
//*********************************************************************
void AmsLmtOverrideDlg::OnBtnAdd()
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnAdd") );
	AddToListControl( IDC_LV_AMS_LMT_OVERRIDE_LIST );

}
//**********************************************************************
void AmsLmtOverrideDlg::OnBtnDel()
{
  TRACE_METHOD( CLASSNAME, I_("OnBtnDel") );

  DeleteFromListControl( IDC_LV_AMS_LMT_OVERRIDE_LIST ); 
}

//*****************************************************************************
void AmsLmtOverrideDlg::OnPostInitDialog()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnInit" ) );

   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   SetUserAccesFunctionCode(UAF::AMS_GLOBAL);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_AMS_LMT_OVERRIDE_LIST);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_AMS_LMT_OVERRIDE_LIST);
   addControls( );
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );

   LoadListControl(IDC_LV_AMS_LMT_OVERRIDE_LIST);

}

//********************************************************************************

bool AmsLmtOverrideDlg::addControls( )
{ 
   TRACE_METHOD( CLASSNAME, I_("addControls") );
   AddListControl(CLASSNAME, IDC_LV_AMS_LMT_OVERRIDE_LIST, I_("AMS_LMT_OVERRIDE_LIST"), ifds::AmsLmtOverrideHeading, 
		IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );


   AddControl( CTRL_COMBO, IDC_CMB_RULE_TYPE, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::RuleType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_AMS_LMT_OVERRIDE_LIST);

   AddControl( CTRL_EDIT, IDC_EDT_OVERRIDE_DECIMAL, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::OverrideDecimal, 0 , IDC_LV_AMS_LMT_OVERRIDE_LIST);

   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_OVERRIDE_DECIMAL))->SetAllowedChars(I_("0123456789."));

   AddControl( CTRL_COMBO, IDC_CMB_OVERRIDE_LOGICAL, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::OverrideLogical, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_AMS_LMT_OVERRIDE_LIST);
   AddControl( CTRL_COMBO, IDC_CMB_OVERRIDE_FUND_LEVEL, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::OverrideFundLevel, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_AMS_LMT_OVERRIDE_LIST);

   AddControl( CTRL_EDIT, IDC_EDT_TAX_JURIS_CODE, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::AMSTaxJurisCode, 0 , IDC_LV_AMS_LMT_OVERRIDE_LIST);
   AddControl( CTRL_EDIT, IDC_EDT_RES_PROV_CODE, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::AMSResProvCode, 0 , IDC_LV_AMS_LMT_OVERRIDE_LIST);
   AddControl( CTRL_EDIT, IDC_EDT_ACCT_TYPE, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::AMSAcctType, 0 , IDC_LV_AMS_LMT_OVERRIDE_LIST);
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ACCT_TYPE))->SetAllowedChars(ALLOWED_ACCOUNT_TYPES);

   AddControl( CTRL_EDIT, IDC_EDT_TAX_TYPE, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::AMSTaxType, 0 , IDC_LV_AMS_LMT_OVERRIDE_LIST);
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_TAX_TYPE))->SetAllowedChars(ALLOWED_TAX_TYPES);

   AddControl( CTRL_EDIT, IDC_EDT_ACCT_DESIGNATION, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::AMSAcctDesignation, 0 , IDC_LV_AMS_LMT_OVERRIDE_LIST);

   AddControl( CTRL_COMBO, IDC_CMB_ONLINE_EWI, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::OnLineEWI, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_AMS_LMT_OVERRIDE_LIST);
   AddControl( CTRL_COMBO, IDC_CMB_CYCLE_EWI, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::CycleEWI, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_AMS_LMT_OVERRIDE_LIST);
   AddControl( CTRL_COMBO, IDC_CMB_ESG_EWI, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, 
               ifds::ESGEWI, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_AMS_LMT_OVERRIDE_LIST);

   return(true);
}

//********************************************************************************
void AmsLmtOverrideDlg::setDlgTitle()
{

   CString caption = GetBaseCaption().c_str();

   caption += COLUMN;
   caption += SPACE;
   caption += _dstrAmsCode.c_str();

   SetWindowText( caption );
}

//**********************************************************************************
void AmsLmtOverrideDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
}

//**********************************************************************************
void AmsLmtOverrideDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;
   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, I_("MULTI") );
}

//********************************************************************************
void AmsLmtOverrideDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl(IDC_LV_AMS_LMT_OVERRIDE_LIST);   
   }
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//**********************************************************************************
void AmsLmtOverrideDlg::EnableControls( )
{
	if( _dstrFromScr == AMS_DETAIL )
	{

		GetControl(IDC_CMB_RULE_TYPE)->Enable( false );
		GetControl(IDC_EDT_OVERRIDE_DECIMAL )->Enable( false );
		GetControl(IDC_CMB_OVERRIDE_LOGICAL )->Enable( false );
		GetControl(IDC_CMB_OVERRIDE_FUND_LEVEL )->Enable( false );
		GetControl(IDC_EDT_TAX_JURIS_CODE )->Enable( false );
		GetControl(IDC_EDT_RES_PROV_CODE )->Enable( false );
		GetControl(IDC_EDT_ACCT_TYPE )->Enable( false );
		GetControl(IDC_EDT_TAX_TYPE )->Enable( false );
		GetControl(IDC_EDT_ACCT_DESIGNATION )->Enable( false );
		GetControl(IDC_CMB_ONLINE_EWI )->Enable( false );
		GetControl(IDC_CMB_CYCLE_EWI )->Enable( false );
		GetControl(IDC_CMB_ESG_EWI )->Enable( false );

		GetDlgItem(IDC_BTN_ADD)->EnableWindow(false);
		GetDlgItem(IDC_BTN_DELETE)->EnableWindow(false);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);
	}
}

//************************************************************************************
void AmsLmtOverrideDlg::DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey,
                                 bool bIsNewItem ,
                                 bool bIsDummyItem
                                 )
{

   if( listControlID == IDC_LV_AMS_LMT_OVERRIDE_LIST )
   {
      EnableControls();		  

      // History
      GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( (bIsNewItem || bIsDummyItem) ? FALSE : TRUE );
   }		 
}

//*************************************************************************
void AmsLmtOverrideDlg::ControlUpdated( UINT controlID, 
													 const DString &strValue )
{   
   switch( controlID )
   {		
		case IDC_CMB_RULE_TYPE:
			{							
				LoadControl( IDC_CMB_OVERRIDE_FUND_LEVEL );
			}
			break;					
		default:
			break;
	}
}

//***********************************************************************************
bool AmsLmtOverrideDlg::doDisablePermCheckButton(UINT nID)
{
	if( _dstrFromScr == AMS_DETAIL )
		return true;
	return false;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AmsLmtOverrideDlg.cpp-arc  $
// 
//    Rev 1.10   Sep 15 2005 15:10:30   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.9   Mar 10 2004 12:18:34   HERNANDO
// PET965 FN11 - Added iFastHistoricalInfo parameter.
// 
//    Rev 1.8   Feb 27 2004 15:56:22   HERNANDO
// PET965 FN11 - Enable/Disable Historical Button based on list item in doListItemChanged.
// 
//    Rev 1.7   Feb 17 2004 16:36:10   VADEANUM
// PTS 10026510 - AMS Limitation, Override Fund Level
// 
//    Rev 1.6   Aug 14 2003 09:13:14   linmay
// modified doDisablePermcheckButton()
// 
//    Rev 1.5   Aug 13 2003 16:15:54   linmay
// added enablecontrol(), dodisablepermcheckbutton, dolistitemchanged()
// 
//    Rev 1.4   Aug 13 2003 12:12:22   linmay
// modified addControls()
// 
//    Rev 1.3   Aug 13 2003 10:24:26   linmay
// change TaxType to AMSTaxType,..
// 
//    Rev 1.2   Aug 11 2003 09:44:42   linmay
// fix bug
// 
//    Rev 1.1   Aug 05 2003 11:25:30   linmay
// fix bug
// 
//    Rev 1.0   Jul 23 2003 09:26:06   linmay
// Initial Revision
// 

 */





