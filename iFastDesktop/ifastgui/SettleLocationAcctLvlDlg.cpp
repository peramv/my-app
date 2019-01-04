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
//    Copyright 2003 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : SettleLocationAcctLvlDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : SettleLocationAcctLvlDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "SettleLocationAcctLvlDlg.h"
#include <ifastcbo\dstcworksession.hpp>
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\SettleLocationAcctLvlProcessIncludes.h>
#include <uibase\dstbutton.h>
#include <uibase\dstedit.h>
#include <bfproc\abstractprocess.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_SETTLEMENT_LOCATION_ACCTLVL;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< SettleLocationAcctLvlDlg > dlgCreator( CMD_GUI_SETTLEMENT_LOCATION_ACCTLVL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("SettleLocationAcctLvlDlg");
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SETTLE_LOCATION_ACCT_LVL;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SettleLocationAcctLvlHeading;
}

//*****************************************************************************
// Public methods
//*****************************************************************************

SettleLocationAcctLvlDlg::SettleLocationAcctLvlDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( SettleLocationAcctLvlDlg::IDD, pParent, pGIC, pGIParent, rCommand )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(SettleLocationAcctLvlDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************

void SettleLocationAcctLvlDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(SettleLocationAcctLvlDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(SettleLocationAcctLvlDlg, BaseMainDlg)
//{{AFX_MSG_MAP(SettleLocationAcctLvlDlg)
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DEL, OnBtnDel )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL SettleLocationAcctLvlDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   // Title
   DString dstrShrNum, dstrAccountNum, dstrEntityName;

   // Get Shareholder Number
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShrNum, dstrShrNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   // Get Account Number
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   // Get Entity Name
   if ( !dstrAccountNum.empty() ) {
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), dstrAccountNum, dstrEntityName);
   }
   SetShrAcctCaption( dstrShrNum, dstrAccountNum, dstrEntityName );

   return(TRUE);
}

//******************************************************************************

void SettleLocationAcctLvlDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode( UAF::SETTLE_LOCATION_ACCT_LVL );
   addBtnAddForPermissionCheck( IDC_BTN_ADD, IDC_LST_SETTLEMENT_LOCATIONS );
   addBtnDeleteForPermissionCheck( IDC_BTN_DEL, IDC_LST_SETTLEMENT_LOCATIONS );

   AddListControl( CLASSNAME, IDC_LST_SETTLEMENT_LOCATIONS, I_("SETTLEMENT_LOCATIONS"), ifds::SettleLocationAcctLvlHeading, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_SETTLEMENT_LOCATION, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::SettleLocationCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LST_SETTLEMENT_LOCATIONS );
 //  AddControl( CTRL_STATIC, IDC_TXT_DESCRIPTION, BF::NullContainerId, ifds::SettleLocationDesc, 0, IDC_LST_SETTLEMENT_LOCATIONS );
   AddControl( CTRL_COMBO, IDC_DEFAULT, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::Default, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LST_SETTLEMENT_LOCATIONS );

   LoadListControl( IDC_LST_SETTLEMENT_LOCATIONS );
}

//*****************************************************************************

void SettleLocationAcctLvlDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   ResetListItem( IDC_LST_SETTLEMENT_LOCATIONS );
}

//*********************************************************************

void SettleLocationAcctLvlDlg::OnBtnAdd()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAdd") );
   AddToListControl( IDC_LST_SETTLEMENT_LOCATIONS );
}

//**********************************************************************

void SettleLocationAcctLvlDlg::OnBtnDel()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnDel") );
   DeleteFromListControl( IDC_LST_SETTLEMENT_LOCATIONS );
}

//************************************************************************

void SettleLocationAcctLvlDlg::OnBtnAdmDates() 
{
   ShowAdminDates( IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
}

//*****************************************************************************

void SettleLocationAcctLvlDlg::OnBtnHistorical() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical") );   
   CWaitCursor wait;   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
}

//*****************************************************************************

bool SettleLocationAcctLvlDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   return( true );
}

//********************************************************************************

bool SettleLocationAcctLvlDlg::doDisablePermCheckButton(UINT nID)
{
   return false;  // return true to disable
}

//*******************************************************************************************

bool SettleLocationAcctLvlDlg::filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag)
{
   bool bReturn = true;
	return bReturn;
}

//**********************************************************************************

bool SettleLocationAcctLvlDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
{
   if( lSubstituteId == ifds::SettleLocationAcctLvlHeading.getId() )
   {
      if( dstrColumnKey == I_("SettleLocationCode" ) )
      {
         getParent()->getField( this, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::SettleLocationCode, dstrOut, false );
         return( true );
      }
      else if( dstrColumnKey == I_("SettleLocationDesc" ) )
      {
         getParent()->getField( this, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::SettleLocationCode, dstrOut, true );
         return( true );
      }
   }
   return( false );
}

//**********************************************************************************

void SettleLocationAcctLvlDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   if( controlID == IDC_CMB_SETTLEMENT_LOCATION )
   {
      //LoadControl( IDC_TXT_DESCRIPTION );
   }
}

//**********************************************************************************

bool SettleLocationAcctLvlDlg::GetDataForControl(
                                       UINT controlID,
                                       DString &strValueOut,
                                       bool bFormatted,
                                       int index
                                       ) const
{
  /* if( controlID == IDC_TXT_DESCRIPTION )
   {
      DString dstrSettleLocationDesc;
      getParent()->getField( this, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::SettleLocationCode, dstrSettleLocationDesc, true);
      strValueOut = dstrSettleLocationDesc;
      return true;
   }
	*/
   return false;
};

//******************************************************************************

void SettleLocationAcctLvlDlg::DoListItemChanged(UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   if( listControlID == IDC_LST_SETTLEMENT_LOCATIONS )
   {
      // Keep historical button grayed for new and dummy items
      GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( !bIsNewItem && !bIsDummyItem );
   }
}


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/SettleLocationAcctLvlDlg.cpp-arc  $
// 
//    Rev 1.2   Feb 27 2004 15:58:42   HERNANDO
// PET965 FN11 - Enable/Disable Historical Button based on list item in doListItemChanged.
// 
//    Rev 1.1   Jan 16 2004 15:10:32   YINGBAOL
// PET892: Change Account level Settlement location to make it consistent with settlement loaction at trade level.
// 
//    Rev 1.0   Nov 24 2003 17:59:22   HERNANDO
// Initial revision.
