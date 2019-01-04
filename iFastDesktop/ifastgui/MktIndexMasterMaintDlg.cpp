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
// ^FILE   : MktIndexMasterMaintDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : MktIndexMasterMaintDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "MktIndexMasterMaintDlg.h"
#include <ifastcbo\dstcworksession.hpp>
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\MktIndexMasterMaintProcessIncludes.h>
#include <uibase\dstedit.h>
#include <bfproc\abstractprocess.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_MKT_INDEX_MASTER;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< MktIndexMasterMaintDlg > dlgCreator( CMD_GUI_MKT_INDEX_MASTER );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME      = I_("MktIndexMasterMaintDlg");
   const I_CHAR * const FUNDNUMBER     = I_( "FUNDNUMBER" );
   const I_CHAR * const FUNDDESCRIPTION= I_( "FUNDDESCRIPTION" );
}

namespace PARAMETER
{
   const I_CHAR * const FUND_CODE      = I_( "FundCode" );    // Used for F4-Fund Search Dialog
   const I_CHAR * const FUND_NUMBER    = I_( "FundNumber" );  // Used for F4-Fund Search Dialog
   const I_CHAR * const CLASS_CODE     = I_( "ClassCode" );   // Used for F4-Fund Search Dialog
}

namespace CND
{
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const MKT_INDEX_MASTER;
}
namespace ifds 
{
   extern CLASS_IMPORT const BFTextFieldId InputDataType;
   extern CLASS_IMPORT const BFTextFieldId DaysBasis;
}

//*****************************************************************************
// Public methods
//*****************************************************************************

MktIndexMasterMaintDlg::MktIndexMasterMaintDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( MktIndexMasterMaintDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_bFundNumberSupported( false )
, m_bIsIndexNewItem( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(MktIndexMasterMaintDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************

void MktIndexMasterMaintDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(MktIndexMasterMaintDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(MktIndexMasterMaintDlg, BaseMainDlg)
//{{AFX_MSG_MAP(MktIndexMasterMaintDlg)
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_ADD_INDEX, OnBtnAddIndex )
ON_BN_CLICKED( IDC_BTN_DEL_INDEX, OnBtnDelIndex )
ON_BN_CLICKED( IDC_BTN_ADD_FUND, OnBtnAddFund )
ON_BN_CLICKED( IDC_BTN_DEL_FUND, OnBtnDelFund )
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL MktIndexMasterMaintDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   DString dstrMarket = DSTCommonFunctions::getMarket();
   m_bFundNumberSupported = ( dstrMarket == MARKET_IDS::CANADA || dstrMarket == MARKET_IDS::LUXEMBOURG );
m_bFundNumberSupported = false;  // temp until FundNumber is implemented

   if( !m_bFundNumberSupported )
   {
      GetDlgItem( IDC_EDT_FUND_NUMBER )->ShowWindow( SW_HIDE );
   }

   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//*****************************************************************************

void MktIndexMasterMaintDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   ResetListItem( IDC_LST_INDICES );
}

//*********************************************************************

void MktIndexMasterMaintDlg::OnBtnAddIndex()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAddIndex") );
   AddToListControl( IDC_LST_INDICES );
}

//**********************************************************************
void MktIndexMasterMaintDlg::OnBtnDelIndex()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnDelIndex") );
   DeleteFromListControl( IDC_LST_INDICES );
}

//************************************************************************

void MktIndexMasterMaintDlg::OnBtnAddFund()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAddFund") );
   AddToListControl( IDC_LST_FUNDS );
}

//************************************************************************

void MktIndexMasterMaintDlg::OnBtnDelFund()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnDelFund") );
   DeleteFromListControl( IDC_LST_FUNDS ); 
}

//************************************************************************

void MktIndexMasterMaintDlg::OnBtnAdmDates() 
{
   ShowAdminDates( IFASTBP_PROC::INDICES_LIST );
}

//*****************************************************************************

void MktIndexMasterMaintDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode( UAF::MKT_INDEX_MASTER );
   addBtnAddForPermissionCheck( IDC_BTN_ADD_INDEX, IDC_LST_INDICES );
   addBtnDeleteForPermissionCheck( IDC_BTN_DEL_INDEX, IDC_LST_INDICES );
   addBtnAddForPermissionCheck( IDC_BTN_ADD_FUND, IDC_LST_FUNDS );
   addBtnDeleteForPermissionCheck( IDC_BTN_DEL_FUND, IDC_LST_FUNDS );

   AddListControl(CLASSNAME, IDC_LST_INDICES, I_("INDEX_INDICES"), ifds::IndexMasterHeading, IFASTBP_PROC::INDICES_LIST );
   AddListControl(CLASSNAME, IDC_LST_FUNDS, I_("INDEX_FUNDS"), ifds::IndexFundsHeading, IFASTBP_PROC::FUNDS_LIST, IDC_LST_INDICES, true, LISTFLAG_NOT_AUTO_ADD );

   AddControl( CTRL_EDIT, IDC_EDT_INDEX_CODE, IFASTBP_PROC::INDICES_LIST, ifds::IndexCode, 0 , IDC_LST_INDICES );
	AddControl( CTRL_EDIT, IDC_EDT_INDEX_DESC, IFASTBP_PROC::INDICES_LIST, ifds::IndexName, 0 , IDC_LST_INDICES );
   if( m_bFundNumberSupported ) 
   {
      AddControl( CTRL_EDIT, IDC_EDT_FUND_NUMBER, BF::NullContainerId, ifds::FundNumber, 0 , IDC_LST_INDICES );
   }
   AddControl( CTRL_COMBO, IDC_CMB_DAY_BASIS, IFASTBP_PROC::INDICES_LIST, ifds::DaysBasis, CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_LST_INDICES );
   AddControl( CTRL_COMBO, IDC_CMB_INPUT_DATATYPE, IFASTBP_PROC::INDICES_LIST, ifds::InputDataType, CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_LST_INDICES );

   AddControl( CTRL_EDIT, IDC_EDT_FUND, IFASTBP_PROC::FUNDS_LIST, ifds::FundCode, 0 , IDC_LST_FUNDS );
   AddControl( CTRL_EDIT, IDC_EDT_CLASS, IFASTBP_PROC::FUNDS_LIST, ifds::ClassCode, 0 , IDC_LST_FUNDS );
   AddControl( CTRL_STATIC, IDC_TXT_FUND_DESC, IFASTBP_PROC::FUNDS_LIST, INDEX_MASTER::FUNDDESC, 0, IDC_LST_FUNDS );

   LoadListControl( IDC_LST_INDICES );
}

//******************************************************************************

bool MktIndexMasterMaintDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   return(true);
}

//********************************************************************************

LRESULT MktIndexMasterMaintDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   DString dstrMarket = DSTCommonFunctions::getMarket();
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      CString cstrValue;

      setParameter( PARAMETER::FUND_CODE, NULL_STRING );
      setParameter( PARAMETER::FUND_NUMBER, NULL_STRING );
      setParameter( PARAMETER::CLASS_CODE, NULL_STRING );
      GetFocus()->GetWindowText( cstrValue );
      DString dstrValue( cstrValue );
      switch( GetFocus()->GetDlgCtrlID() )
      {
         case IDC_EDT_FUND:
            setParameter( PARAMETER::FUND_CODE, dstrValue );
            break;    
         case IDC_EDT_FUND_NUMBER:
            setParameter( PARAMETER::FUND_NUMBER, dstrValue );
            break;    
         case IDC_EDT_CLASS:
            setParameter( PARAMETER::CLASS_CODE, dstrValue );
            break;    
      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;
               getParameter ( PARAMETER::FUND_CODE, dstrFundCode );
               getParameter ( PARAMETER::CLASS_CODE, dstrClassCode );
               getParameter ( PARAMETER::FUND_NUMBER, dstrFundNumber );

               getParent()->setField( this, IFASTBP_PROC::FUNDS_LIST, ifds::FundCode, dstrFundCode );
               getParent()->setField( this, IFASTBP_PROC::FUNDS_LIST, ifds::ClassCode, dstrClassCode );
               if( m_bFundNumberSupported ) 
               {
///                  getParent()->setField( this, INDEX_MASTER::FUNDS_LIST, ifds::FundNumber, dstrFundNumber );
                  LoadControl( IDC_EDT_FUND_NUMBER );
               }
               LoadControl( IDC_EDT_FUND );
               LoadControl( IDC_EDT_CLASS );
               break;
            }
         case CMD_CANCEL:
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
   return(0);
}

//******************************************************************************

BOOL MktIndexMasterMaintDlg::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
   {
      return( TRUE );
   }

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 )
   {
      if(   GetFocus() == GetDlgItem( IDC_EDT_FUND ) 
            || GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) 
            || GetFocus() == GetDlgItem( IDC_EDT_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
      }
      return( TRUE );
   }
   return( BaseMainDlg::PreTranslateMessage( pMsg ) );
}  

//**********************************************************************************

bool MktIndexMasterMaintDlg::doDisablePermCheckButton(UINT nID)
{
   if( nID == IDC_BTN_DEL_INDEX )
   {
      return( !m_bIsIndexNewItem );
   }
   return false;  // return true to disable
}

//**********************************************************************************

void MktIndexMasterMaintDlg::DoListItemChanged(UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   if( listControlID == IDC_LST_INDICES )
   {
      m_bIsIndexNewItem = bIsNewItem;
   }
}

//*******************************************************************************************

bool MktIndexMasterMaintDlg::filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag)
{
   bool bReturn = true;

	if( ifds::IndexFundsHeading == idSubstitute )
	{
		if( dstrTag == FUNDNUMBER )
		{
         bReturn = m_bFundNumberSupported;
		}
	}	
	return bReturn;
}

//**********************************************************************************

bool MktIndexMasterMaintDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
{
   if( lSubstituteId == ifds::IndexFundsHeading.getId() )
   {
      if( dstrColumnKey == FUNDNUMBER )
      {
         DString dstrFund, dstrClass;
         getParent()->getField (this, IFASTBP_PROC::FUNDS_LIST, ifds::FundCode, dstrFund );
         getParent()->getField (this, IFASTBP_PROC::FUNDS_LIST, ifds::ClassCode, dstrClass );
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber( dstrFund, dstrClass, dstrOut );
         return( true );
      }
      else if( dstrColumnKey == FUNDDESCRIPTION )
      {
         getParent()->getField (this, IFASTBP_PROC::FUNDS_LIST, INDEX_MASTER::FUNDDESC, dstrOut );
         return( true );
      }
   }
   return( false );
}

//**********************************************************************************

void MktIndexMasterMaintDlg::ControlUpdated(UINT controlID, const DString &strValue )
{
   if( controlID == IDC_EDT_FUND )
   {
      LoadControl( IDC_TXT_FUND_DESC );
   }
   else if( controlID == IDC_CMB_INPUT_DATATYPE )
   {
      LoadControl( IDC_CMB_DAY_BASIS );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MktIndexMasterMaintDlg.cpp-arc  $
// 
//    Rev 1.10   Jan 16 2012 13:48:32   wp040027
// P0188394_Performance Fees - Benchmark Upload
// 
//    Rev 1.9   Sep 15 2005 15:14:02   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.8   Mar 21 2003 18:39:14   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Feb 07 2003 16:09:58   HERNANDO
// Added ControlUpdated.
// 
//    Rev 1.6   Feb 07 2003 14:16:04   HERNANDO
// Added Fund Description.
// 
//    Rev 1.5   Feb 05 2003 13:23:56   HERNANDO
// Revised UAF for MKT_INDEX.
// 
//    Rev 1.4   Feb 03 2003 15:25:38   HERNANDO
// Added DoListItemChanged and implemented doDisablePermCheckButton by using a new flag.
// 
//    Rev 1.3   Jan 31 2003 14:59:22   HERNANDO
// Added User Access to controls.  
// 
//    Rev 1.2   Jan 29 2003 12:57:42   HERNANDO
// Revised.
// 
//    Rev 1.1   Jan 25 2003 18:34:56   HERNANDO
// Revised.
// 
//    Rev 1.0   Jan 23 2003 10:32:38   HERNANDO
// Initial Revision
 * 
 */





