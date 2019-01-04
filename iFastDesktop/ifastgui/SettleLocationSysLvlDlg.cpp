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
// ^FILE   : SettleLocationSysLvlDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : SettleLocationSysLvlDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "SettleLocationSysLvlDlg.h"
#include <ifastcbo\dstcworksession.hpp>
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\SettleLocationSysLvlProcessIncludes.h>
#include <uibase\dstedit.h>
#include <bfproc\abstractprocess.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_SETTLEMENT_LOCATION_SYSLVL;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< SettleLocationSysLvlDlg > dlgCreator( CMD_GUI_SETTLEMENT_LOCATION_SYSLVL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("SettleLocationSysLvlDlg");
}

namespace CND
{
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SETTLE_LOCATION_SYS_LVL;
}

//*****************************************************************************
// Public methods
//*****************************************************************************

SettleLocationSysLvlDlg::SettleLocationSysLvlDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( SettleLocationSysLvlDlg::IDD, pParent, pGIC, pGIParent, rCommand )
, m_bIsEntryNew( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(SettleLocationSysLvlDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************

void SettleLocationSysLvlDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(SettleLocationSysLvlDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(SettleLocationSysLvlDlg, BaseMainDlg)
//{{AFX_MSG_MAP(SettleLocationSysLvlDlg)
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DEL, OnBtnDel )
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL SettleLocationSysLvlDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//*****************************************************************************

void SettleLocationSysLvlDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   ResetListItem( IDC_LST_SETTLEMENT_LOCATIONS );
}

//*********************************************************************

void SettleLocationSysLvlDlg::OnBtnAdd()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAdd") );
   AddToListControl( IDC_LST_SETTLEMENT_LOCATIONS );
}

//**********************************************************************
void SettleLocationSysLvlDlg::OnBtnDel()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnDel") );
   DeleteFromListControl( IDC_LST_SETTLEMENT_LOCATIONS );
}

//************************************************************************

void SettleLocationSysLvlDlg::OnBtnAdmDates() 
{
   ShowAdminDates( IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
}

//************************************************************************

void SettleLocationSysLvlDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   const DString *dstrCurrentKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LST_SETTLEMENT_LOCATIONS );
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//*****************************************************************************

void SettleLocationSysLvlDlg::OnBtnHistorical() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical") );   
   CWaitCursor wait;   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
}

//*****************************************************************************

void SettleLocationSysLvlDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode( UAF::SETTLE_LOCATION_SYS_LVL );
   addBtnAddForPermissionCheck( IDC_BTN_ADD, IDC_LST_SETTLEMENT_LOCATIONS );
   addBtnDeleteForPermissionCheck( IDC_BTN_DEL, IDC_LST_SETTLEMENT_LOCATIONS );

   AddListControl(CLASSNAME, IDC_LST_SETTLEMENT_LOCATIONS, I_("Settle_Locations"), ifds::SettleLocationSysLvlHeading, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );

   AddControl( CTRL_EDIT, IDC_EDT_SETTLEMENT_LOCATION, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::SettleLocationCode, 0, IDC_LST_SETTLEMENT_LOCATIONS );
   AddControl( CTRL_EDIT, IDC_EDT_DESCRIPTION, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::SettleLocationDesc, 0, IDC_LST_SETTLEMENT_LOCATIONS );
   AddControl( CTRL_EDIT, IDC_EDT_ACCOUNT, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::SettleAccountNum, 0, IDC_LST_SETTLEMENT_LOCATIONS );
   AddControl( CTRL_EDIT, IDC_EDT_INT_SETL_ACC, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::InterSettleAccountNum, 0, IDC_LST_SETTLEMENT_LOCATIONS );
   AddControl( CTRL_COMBO, IDC_CMB_STATUS, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::Active, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LST_SETTLEMENT_LOCATIONS );

   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_INT_SETL_ACC ) )->SetMaxCharNum( 25 );
   LoadListControl( IDC_LST_SETTLEMENT_LOCATIONS );
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//******************************************************************************

bool SettleLocationSysLvlDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   return(true);
}

//**********************************************************************************

bool SettleLocationSysLvlDlg::doDisablePermCheckButton(UINT nID)
{
   bool bReturn = false;
   if( nID == IDC_BTN_DEL )
   {
      DString dstrInUseAcct, dstrInUseTrade;
      getParent()->getField( this, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::InUseAcct, dstrInUseAcct, false );
      getParent()->getField( this, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, ifds::InUseTrade, dstrInUseTrade, false );
      bReturn = !( m_bIsEntryNew || ( dstrInUseAcct == I_("N") && dstrInUseTrade == I_("N") ) );
   }
   return bReturn;  // return true to disable
}

//**********************************************************************************

void SettleLocationSysLvlDlg::DoListItemChanged(UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   if( listControlID == IDC_LST_SETTLEMENT_LOCATIONS )
   {
      m_bIsEntryNew = bIsNewItem;

      // Keep historical button grayed for new and dummy items
      GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( !bIsNewItem && !bIsDummyItem );
   }
}

//**********************************************************************************

bool SettleLocationSysLvlDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
{
   if( lSubstituteId == ifds::SettleLocationSysLvlHeading.getId() )
   {
   }
   return( false );
}

//**********************************************************************************

void SettleLocationSysLvlDlg::ControlUpdated(UINT controlID, const DString &strValue )
{
}

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/SettleLocationSysLvlDlg.cpp-arc  $
// 
//    Rev 1.1   Feb 27 2004 16:00:14   HERNANDO
// PET965 FN11 - Enable/Disable Historical Button based on list item in DoListItemChanged.
// 
//    Rev 1.0   Nov 24 2003 16:51:58   HERNANDO
// Initial revision.
// 
