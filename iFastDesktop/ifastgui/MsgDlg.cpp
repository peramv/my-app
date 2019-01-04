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
// ^FILE   : MsgDlg.cpp
// ^CLASS  : MsgDlg
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "MsgDlg.h"
#include <ifastcbo\dstcworksession.hpp>
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\MsgProcessIncludes.h>
#include <ifastbp\AggregatedOrderProcessInclude.h>
#include <uibase\dstedit.h>
#include <uibase\ifdslistctrl.h>
#include <bfproc\abstractprocess.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_MSG;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AGGREGATED_ORDER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADMINDATES;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< MsgDlg > dlgCreator( CMD_GUI_MSG );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("MsgDlg");
}

namespace CND
{
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

// Message Process List Control
class LVMsgProcessData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVMsgProcessData() {}
   DString NetworkID_, MsgProcessType_, MsgProcessStatus_, FileName_, ProcessDate_, ProcessTime_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::NetworkID, NetworkID_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::MsgProcessType, MsgProcessType_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::MsgProcessStatus, MsgProcessStatus_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FileName, FileName_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ProcessDate, ProcessDate_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ProcessTime, ProcessTime_ );
   }
};

class LVMsgProcessAdapter : public IFDSListCtrlAdapter< LVMsgProcessData >
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
      } else if( *pFieldId == ifds::NetworkID ) {
         result = i_strcmp( pData1->NetworkID_.c_str(), pData2->NetworkID_.c_str() );
      } else if( *pFieldId == ifds::MsgProcessType ) {
         result = i_strcmp( pData1->MsgProcessType_.c_str(), pData2->MsgProcessType_.c_str() );
      } else if( *pFieldId == ifds::MsgProcessStatus ) {
         result = i_strcmp( pData1->MsgProcessStatus_.c_str(), pData2->MsgProcessStatus_.c_str() );
      } else if( *pFieldId == ifds::FileName ) {
         result = i_strcmp( pData1->FileName_.c_str(), pData2->FileName_.c_str() );
      } else if( *pFieldId == ifds::ProcessDate || *pFieldId == ifds::ProcessTime ) {
			if ( DSTCommonFunctions::CompareDates( pData1->ProcessDate_.c_str(), pData2->ProcessDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = -1;
			else if ( DSTCommonFunctions::CompareDates( pData2->ProcessDate_.c_str(), pData1->ProcessDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = 1;
         else
            result = i_strcmp( pData1->ProcessTime_.c_str(), pData2->ProcessTime_.c_str() );
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
         } else if( *pFieldId == ifds::NetworkID ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->NetworkID_.c_str();
         } else if( *pFieldId == ifds::MsgProcessType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->MsgProcessType_.c_str();
         } else if( *pFieldId == ifds::MsgProcessStatus ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->MsgProcessStatus_.c_str();
         } else if( *pFieldId == ifds::FileName ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->FileName_.c_str();
         } else if( *pFieldId == ifds::ProcessDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->ProcessDate_.c_str();
         } else if( *pFieldId == ifds::ProcessTime ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->ProcessTime_.c_str();
         } 
         return( 1 );
      }
      return( 0 );
   }
};

// Activity List Control
class LVMsgActivityData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVMsgActivityData() {}
   DString ActivityType_, ActivityID_, SendRefNum_, TransNum_, OVERRIDE1_, OVERRIDE2_, MsgDate_, MsgTime_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ActivityType, ActivityType_);
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ActivityID, ActivityID_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::SendRefNum, SendRefNum_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TransNum, TransNum_ );
      if( pDlg->GetOverrideItemString(ifds::MsgActivityHeading.getId(), I_("OVERRIDE1"), OVERRIDE1_ ) == false )
      {
         pDlg->getParent()->getField( pDlg, BF::NullContainerId, OVERRIDE1, OVERRIDE1_ );
      }
      if( pDlg->GetOverrideItemString(ifds::MsgActivityHeading.getId(), I_("OVERRIDE2"), OVERRIDE2_ ) == false )
      {
         pDlg->getParent()->getField( pDlg, BF::NullContainerId, OVERRIDE2, OVERRIDE2_ );
      }
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::MsgDate, MsgDate_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::MsgTime, MsgTime_ );
   }
};

class LVMsgActivityAdapter : public IFDSListCtrlAdapter< LVMsgActivityData >
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
      } else if( *pFieldId == ifds::ActivityType ) {
         result = i_strcmp( pData1->ActivityType_.c_str(), pData2->ActivityType_.c_str() );
      } else if( *pFieldId == ifds::ActivityID ) {
         result = i_strcmp( pData1->ActivityID_.c_str(), pData2->ActivityID_.c_str() );
      } else if( *pFieldId == ifds::SendRefNum ) {
         result = i_strcmp( pData1->SendRefNum_.c_str(), pData2->SendRefNum_.c_str() );
      } else if( *pFieldId == ifds::TransNum ) {
         result = i_strcmp( pData1->TransNum_.c_str(), pData2->TransNum_.c_str() );
      } else if( *pFieldId == OVERRIDE1 ) {
         result = i_strcmp( pData1->OVERRIDE1_.c_str(), pData2->OVERRIDE1_.c_str() );
      } else if( *pFieldId == OVERRIDE2 ) {
         result = i_strcmp( pData1->OVERRIDE2_.c_str(), pData2->OVERRIDE2_.c_str() );
      } else if( *pFieldId == ifds::MsgDate || *pFieldId == ifds::MsgTime ) {
			if ( DSTCommonFunctions::CompareDates( pData1->MsgDate_.c_str(), pData2->MsgDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = -1;
			else if ( DSTCommonFunctions::CompareDates( pData2->MsgDate_.c_str(), pData1->MsgDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = 1;
         else
            result = i_strcmp( pData1->MsgTime_.c_str(), pData2->MsgTime_.c_str() );
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
         } else if( *pFieldId == ifds::ActivityType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->ActivityType_.c_str();
         } else if( *pFieldId == ifds::ActivityID ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->ActivityID_.c_str();
         } else if( *pFieldId == ifds::SendRefNum ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->SendRefNum_.c_str();
         } else if( *pFieldId == ifds::TransNum ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->TransNum_.c_str();
         } else if( pFieldId->getName() == I_("OVERRIDE1") ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->OVERRIDE1_.c_str();
         } else if( pFieldId->getName() == I_("OVERRIDE2") ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->OVERRIDE2_.c_str();
         } else if( *pFieldId == ifds::MsgDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->MsgDate_.c_str();
         } else if( *pFieldId == ifds::MsgTime ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->MsgTime_.c_str();
         } 
         return( 1 );
      }
      return( 0 );
   }
};


// Event List Control
class LVMsgEventData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVMsgEventData() {}
   DString EventCode_, EventType_, EventText_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EventCode, EventCode_);
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EventType, EventType_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EventText, EventText_ );
   }
};

class LVMsgEventAdapter : public IFDSListCtrlAdapter< LVMsgEventData >
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
      } else if( *pFieldId == ifds::EventCode ) {
         result = i_strcmp( pData1->EventCode_.c_str(), pData2->EventCode_.c_str() );
      } else if( *pFieldId == ifds::EventType ) {
         result = i_strcmp( pData1->EventType_.c_str(), pData2->EventType_.c_str() );
      } else if( *pFieldId == ifds::EventText ) {
         result = i_strcmp( pData1->EventText_.c_str(), pData2->EventText_.c_str() );
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
         } else if( *pFieldId == ifds::EventCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->EventCode_.c_str();
         } else if( *pFieldId == ifds::EventType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->EventType_.c_str();
         } else if( *pFieldId == ifds::EventText ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->EventText_.c_str();
         } 
         return( 1 );
      }
      return( 0 );
   }
};


//*****************************************************************************
// Public methods
//*****************************************************************************

MsgDlg::MsgDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( MsgDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
DisableTrade( NULL_STRING ),
DisableAggrOrder( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(MsgDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************

void MsgDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(MsgDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(MsgDlg, BaseMainDlg)
//{{AFX_MSG_MAP(MsgDlg)
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
ON_BN_CLICKED( IDC_BTN_MSG_BODY, OnBtnDetail )
ON_BN_CLICKED( IDC_BTN_TRADE, OnBtnTrade )
ON_BN_CLICKED( IDC_BTN_AGGR_ORDER, OnBtnAggrOrder )

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

SEVERITY MsgDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));
   SEVERITY sevRtn = SEVERE_ERROR;

   // Get Parameters
   getParameter( I_("DisableTrade"), DisableTrade );
   getParameter( I_("DisableAggrOrder"), DisableAggrOrder );

   sevRtn = NO_CONDITION;
   return( sevRtn );
}
//******************************************************************************

BOOL MsgDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//******************************************************************************

void MsgDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   IFDSListCtrl* ifdsListControlMsgProcesses = new IFDSAdaptedListCtrl< LVMsgProcessAdapter >( this, CLASSNAME, IDC_LV_MSG_PROCESSES, 0, LISTFLAG_NOT_UPDATABLE, true /*ShowSelAlways*/, true /*ShowConditions*/);
   AddIFDSListControl( ifdsListControlMsgProcesses, I_("MSG_PROCESSES"), IFASTBP_PROC::MSG_PROCESS_LIST, ifds::MsgProcessHeading );   

   IFDSListCtrl* ifdsListControlMsgActivities = new IFDSAdaptedListCtrl< LVMsgActivityAdapter >( this, CLASSNAME, IDC_LV_MSG_ACTIVITIES, IDC_LV_MSG_PROCESSES, LISTFLAG_NOT_UPDATABLE, true /*ShowSelAlways*/, true /*ShowConditions*/);
   AddIFDSListControl( ifdsListControlMsgActivities, I_("MSG_ACTIVITIES"), IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::MsgActivityHeading );   

   IFDSListCtrl* ifdsListControlMsgEvents = new IFDSAdaptedListCtrl< LVMsgEventAdapter >( this, CLASSNAME, IDC_LV_MSG_EVENTS, IDC_LV_MSG_ACTIVITIES, LISTFLAG_NOT_UPDATABLE, true /*ShowSelAlways*/, true /*ShowConditions*/);
   AddIFDSListControl( ifdsListControlMsgEvents, I_("MSG_EVENTS"), IFASTBP_PROC::MSG_EVENT_LIST, ifds::MsgEventHeading );   

   LoadListControl( IDC_LV_MSG_PROCESSES );
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::MSG_PROCESS_LIST ) );
}

//************************************************************************

void MsgDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAdmDates") );
   CWaitCursor wait;
   DString ProcessDate, ProcessTime;

   // Set Display Type - Admin will display onle Process Date and Process Time
   setParameter( I_("DisplayType"), I_("ProcessDateAndTime") );

   // Set Process Date
   getParent()->getField( this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::ProcessDate, ProcessDate );
   setParameter( I_( "ProcessDate" ), ProcessDate );

   // Set Process Time
   getParent()->getField( this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::ProcessTime, ProcessTime );
   setParameter( I_( "ProcessTime" ), ProcessTime );
   try
   {
      E_COMMANDRETURN eRtn;
      SetMessageStatusBar( TXT_LOAD_ADMIN_DATES );
      eRtn = invokeCommand( getParent(), CMD_BPROC_ADMINDATES, PROC_NO_TYPE,
                            true /*modal*/, NULL );
      SetMessageStatusBar( NULL_STRING );
      switch( eRtn )
      {
         case CMD_OK:
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

//************************************************************************

void MsgDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel;
   cursel = GetList( IDC_LV_MSG_PROCESSES )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::MSG_PROCESS_LIST );
   if( getParent()->performSearch( this, IFASTBP_PROC::MSG_PROCESS_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_MSG_PROCESSES );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_MSG_PROCESSES )->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   GetList( IDC_LV_MSG_PROCESSES )->SetSelection( cursel, true, true );
}

//************************************************************************

void MsgDlg::OnBtnTrade() // Transaction History (instead of Trade Inquiry)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnTrade" ) );

   DString ActivityID, AccountNum;
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      // Ext Trans Num
      getParent()->getField(this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::ActivityID, ActivityID, false);
      setParameter( MFCAN_IP_PARAM::EXTERNAL_TRANS_NUM, ActivityID );

      // Account Number
      getParent()->getField( this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::AccountNum, AccountNum );  
      setParameter( I_("AccountNum"), AccountNum );

      // Disable Message Button
      setParameter( I_("DisableMsg"), I_("DisableMsg") );

      // Inquiry only
      setParameter( I_( "InquiryOnly" ), I_("Y") );

      eRtn = invokeCommand( getParent(), CMD_BPROC_TRANS_HISTORY, PROC_SUPPORT, false, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
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

//************************************************************************

void MsgDlg::OnBtnAggrOrder()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAggrOrder" ) );

   DString OmnibusID;
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      // Aggregate Order Number (Omnibus)
      getParent()->getField(this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::OmnibusID, OmnibusID, false);
      setParameter( AGGREGATE::AGGR_ORDER_NUMBER, OmnibusID );

      // Search Type
      setParameter( AGGREGATE::SEARCH_TYPE, AGGREGATE_SEARCHTYPE::BY_AGGR_ORD_NUM );

      // Disable Message Button
      setParameter( I_("DisableMsg"), I_("DisableMsg") );

      eRtn = invokeCommand( getParent(), CMD_BPROC_AGGREGATED_ORDER, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
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
}

//*****************************************************************************

bool MsgDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   return( true );
}

//*******************************************************************************************

bool MsgDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
{
   if( dstrColumnKey == I_("OVERRIDE1") )
   {
      DString MsgProcessCategory, Type;
      getParent()->getField( this, IFASTBP_PROC::MSG_PROCESS_LIST, ifds::MsgProcessCategory, MsgProcessCategory, false );
      Type = MsgProcessCategory.left( 1 );
      if( Type == I_("T") )
      {
         DString AccountNum;
         getParent()->getField( this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::AccountNum, AccountNum, false );
         dstrOut = AccountNum;
      }
      else if( Type == I_("A") )
      {
         DString FundBrokerCode;
         getParent()->getField( this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::FundBrokerCode, FundBrokerCode, false );
         dstrOut = FundBrokerCode;
      }
      if( dstrOut.asInteger() == 0 )
      {
         dstrOut = NULL_STRING;
      }
      return( true );
   }
   else if( dstrColumnKey == I_("OVERRIDE2") )
   {
      DString MsgProcessCategory, Type;
      getParent()->getField( this, IFASTBP_PROC::MSG_PROCESS_LIST, ifds::MsgProcessCategory, MsgProcessCategory, false );
      Type = MsgProcessCategory.left( 1 );
      if( Type == I_("T") )
      {
         DString TransNum;
         getParent()->getField( this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::TransNum, TransNum, false );
         dstrOut = TransNum;
      }
      else if( Type == I_("A") )
      {
         DString OmnibusID;
         getParent()->getField( this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::OmnibusID, OmnibusID, false );
         dstrOut = OmnibusID;
      }
      if( dstrOut.asInteger() == 0 )
      {
         dstrOut = NULL_STRING;
      }
      return( true );
   }
   return( false );
}

//**********************************************************************************

bool MsgDlg::GetDataForControl(UINT controlID,
                               DString &strValueOut,
                               bool bFormatted,
                               int index
                              ) const
{
   return false;
};

//**********************************************************************************

void MsgDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
}

//**********************************************************************************

void MsgDlg::OnBtnDetail() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnDetail()" ) );

   // Set Parameter
   DString ActivityID;
   getParent()->getField( this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::ActivityID, ActivityID, false );
   setParameter( MFCAN_IP_PARAM::ACTIVITY_ID, ActivityID );

   try
   {
      bool bModal = true;   
      E_COMMANDRETURN eRtn = CMD_OK;
      eRtn = invokeCommand( getParent(), CMD_BPROC_MSG_DETAIL, PROC_NO_TYPE, bModal, NULL );
      switch( eRtn )
      {
         case CMD_OK:
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

// TODO: Chk UAFs.

void MsgDlg::DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem )
{
   if( listControlID == IDC_LV_MSG_ACTIVITIES )
   {
      //
      if( !bIsNewItem && !bIsDummyItem )
      {
         // Enable/Disable buttons
         DString TransNum, AccountNum, OmnibusID;
         getParent()->getField(this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::TransNum, TransNum, false );
         getParent()->getField(this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::AccountNum, AccountNum, false );
         getParent()->getField( this, IFASTBP_PROC::MSG_ACTIVITY_LIST, ifds::OmnibusID, OmnibusID, false );
         TransNum.stripAll();
         AccountNum.stripLeading( I_CHAR('0') ).stripAll();
         OmnibusID.stripAll();
         GetDlgItem( IDC_BTN_AGGR_ORDER )->EnableWindow( !OmnibusID.empty() && DisableAggrOrder.empty() );
         GetDlgItem( IDC_BTN_TRADE )->EnableWindow( !TransNum.empty() && !AccountNum.empty() && DisableTrade.empty() );
         GetDlgItem( IDC_BTN_MSG_BODY )->EnableWindow( TRUE );
         GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( TRUE );
      }
      else
      {
         GetDlgItem( IDC_BTN_AGGR_ORDER )->EnableWindow( FALSE );
         GetDlgItem( IDC_BTN_TRADE )->EnableWindow( FALSE );
         GetDlgItem( IDC_BTN_MSG_BODY )->EnableWindow( FALSE );
         GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( FALSE );
      }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/MsgDlg.cpp-arc  $
// 
//    Rev 1.8   Sep 15 2005 15:14:12   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.7   May 24 2005 16:35:42   porteanm
// PET OPC Confirm Reprint - Call Transaction History Dlg as non-Modal.
// 
//    Rev 1.6   Apr 21 2005 11:22:26   hernando
// Incident #278666 - Switched TransNum to ExtTransNum.  Added OVERRIDE2 and revised OVERRIDE1.
// 
//    Rev 1.5   Apr 20 2005 10:25:02   hernando
// Incident #279078 - Set Inquiry parameter for Trade Button.
// 
//    Rev 1.4   Apr 19 2005 13:37:22   hernando
// Incident #292495 - Added doInit.
// 
//    Rev 1.3   Apr 08 2005 17:55:34   hernando
// Incident #281643 - Changed Date sorting.
// 
//    Rev 1.2   Apr 06 2005 19:27:10   hernando
// Incident #281643 - Revised the sort date/time comparison for the list boxes.
// 
//    Rev 1.1   Apr 06 2005 18:44:30   hernando
// Incident #281643 - Revised the More functionality.
// 
//    Rev 1.0   Feb 21 2005 09:59:26   hernando
// Initial revision.
