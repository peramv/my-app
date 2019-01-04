//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : CancellationInstrDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 11/01/2005
//
// ^CLASS    : CancellationInstrDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef CANCELLATIONINSTRDLG_H
   #include "CancellationInstrDlg.h"
#endif
#include <ifastbp\CancellationInstrProcessIncludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstedit.h>
#include <uibase\DSTListCtrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\TransCancelProcessincludes.h>
#include <ifastgui\basemaindlg.h>
#include <uibase\ifdslistctrl.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_CANCELLATION_INSTR;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< CancellationInstrDlg > dlgCreator( CMD_GUI_CANCELLATION_INSTR );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_CANCEL;

namespace
{
   const I_CHAR * const YES             = I_( "Y" );
   const I_CHAR * const NO              = I_( "N" );
   const I_CHAR * const CLASSNAME       = I_( "CancellationInstrDlg" );
   const I_CHAR * const LV_RESULTS      = I_( "ResultsList" );
   const I_CHAR * const CRITERIA_SCREEN = I_( "CriteriaScreen" );
   const I_CHAR * const RESULTS_SCREEN  = I_( "ResultsScreen" );
   const I_CHAR *pTRANSNUM              = I_( "TransNum" );
}

namespace 
{
   const I_CHAR * const SEARCH_TYPE     = I_("SearchType");
   const I_CHAR * const TRANS_STATUS    = I_("TransStat"); 
   const I_CHAR * const ADJUST_TYPE     = I_("AdjustType");
}

namespace CND
{//Conditionsused
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
  
  
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CancSearchType;
   extern CLASS_IMPORT const BFTextFieldId SearchUsing;
   extern CLASS_IMPORT const BFTextFieldId TranStatus;
   extern CLASS_IMPORT const BFTextFieldId AdjustType;
   extern CLASS_IMPORT const BFTextFieldId CancellationInstr;
}


class LVCancellationInstrData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVCancellationInstrData() {}

   DString m_dstrCancellationType, m_dstrTransNum, m_dstrTransType, m_dstrTradeDate;
	DString m_dstrFund, m_dstrClass, m_dstrFundISIN, m_dstrFundWKN;
	DString m_dstrTranStatus, m_dstrVerifyDate, m_dstrVerifiedBy;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {

      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::CancellationType, m_dstrCancellationType );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TransNum, m_dstrTransNum );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TransType, m_dstrTransType );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TradeDate, m_dstrTradeDate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Fund, m_dstrFund );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Class, m_dstrClass );
		pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundISIN, m_dstrFundISIN );
	   pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundWKN, m_dstrFundWKN );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TranStatus, m_dstrTranStatus );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::VerifyDate, m_dstrVerifyDate);
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::VerifiedBy, m_dstrVerifiedBy );
   }
};

class LVCancellationInstrAdapter : public IFDSListCtrlAdapter< LVCancellationInstrData >
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
      } else if( *pFieldId == ifds::TransNum ) {
			// TransNum column, should be sorted as integer
			int iInvSummId1 = pData1->m_dstrTransNum.asInteger();
         int iInvSummId2 = pData2->m_dstrTransNum.asInteger();
         if ( iInvSummId1 > iInvSummId2 )
				result = 1;
			else if ( iInvSummId1 < iInvSummId2 )
				result = -1;
       
      } else if( *pFieldId == ifds::CancellationType ) {
         result = i_strcmp( pData1->m_dstrCancellationType.c_str(), pData2->m_dstrCancellationType.c_str() );
		 } else if( *pFieldId == ifds::TransType ) {
         result = i_strcmp( pData1->m_dstrTransType.c_str(), pData2->m_dstrTransType.c_str() );
		 } else if( *pFieldId == ifds::TradeDate ) {
         int dater_order = DSTCommonFunctions::CompareDates (
               pData1->m_dstrTradeDate.c_str(), 
               pData2->m_dstrTradeDate.c_str(),
               BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? -1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : 1;
		
      } else if( *pFieldId == ifds::Fund ) {
         result = i_strcmp( pData1->m_dstrFund.c_str(), pData2->m_dstrFund.c_str() );
		 } else if( *pFieldId == ifds::Class ) {
         result = i_strcmp( pData1->m_dstrClass.c_str(), pData2->m_dstrClass.c_str() );
      } else if( *pFieldId == ifds::FundISIN ) {
         result = i_strcmp( pData1->m_dstrFundISIN.c_str(), pData2->m_dstrFundISIN.c_str() );
		} else if( *pFieldId == ifds::FundWKN) {
         result = i_strcmp( pData1->m_dstrFundWKN.c_str(), pData2->m_dstrFundWKN.c_str() );
		} else if( *pFieldId == ifds::TranStatus ) {
         result = i_strcmp( pData1->m_dstrTranStatus.c_str(), pData2->m_dstrTranStatus.c_str() );
    	}  else if( *pFieldId == ifds::VerifyDate ) {
         int dater_order = DSTCommonFunctions::CompareDates (
               pData1->m_dstrVerifyDate.c_str(), 
               pData2->m_dstrVerifyDate.c_str(),
               BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? -1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : 1;
			
		} else if( *pFieldId == ifds::VerifiedBy ) {
         result = i_strcmp( pData1->m_dstrVerifiedBy.c_str(), pData2->m_dstrVerifiedBy.c_str() );
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
         } else if( *pFieldId == ifds::CancellationType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrCancellationType.c_str();
         } else if( *pFieldId == ifds::TransNum ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTransNum.c_str();
         } else if( *pFieldId == ifds::TransType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTransType.c_str();
         } else if( *pFieldId == ifds::TradeDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTradeDate.c_str();
         } else if( *pFieldId == ifds::Fund ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFund.c_str();
         } else if( *pFieldId == ifds::Class ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrClass.c_str();
			} else if( *pFieldId == ifds::FundISIN ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFundISIN.c_str();
			} else if( *pFieldId == ifds::FundWKN ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFundWKN.c_str();
         } else if( *pFieldId == ifds::TranStatus ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTranStatus.c_str();
         } else if( *pFieldId == ifds::VerifyDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrVerifyDate.c_str();
         } else if( *pFieldId == ifds::VerifiedBy ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrVerifiedBy.c_str();
         } 

         return( 1 );
      }
      return( 0 );
   }
};

//******************************************************************************

CancellationInstrDlg::CancellationInstrDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( CancellationInstrDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_strScreenType(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	
   //{{AFX_DATA_INIT(CancellationInstrDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
CancellationInstrDlg::~CancellationInstrDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void CancellationInstrDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(CancellationInstrDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CancellationInstrDlg, BaseMainDlg)
//{{AFX_MSG_MAP(CancellationInstrDlg)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_MORE,    OnBtnMore)
	ON_BN_CLICKED(IDC_BTN_DETAIL,  OnBtnDetails)
	ON_BN_CLICKED(IDC_BTN_ADMIN,   OnBtnAdmDates )
	ON_BN_CLICKED(IDC_BTN_SEARCH,  OnBtnSearch)
	
	//}}AFX_MSG_MAP
   
   ON_NOTIFY(NM_DBLCLK, IDC_LV_RESULTS, OnDblclkLvResults)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CancellationInstrDlg message handlers


//******************************************************************************
void CancellationInstrDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   CWaitCursor wait;
   addControls();
   showCriteria();
}

//******************************************************************************
SEVERITY CancellationInstrDlg::doInit()
{
   SEVERITY sevRtn = NO_CONDITION;

   return(sevRtn);
}

//******************************************************************************
void CancellationInstrDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );    

	//list controls
	//AddListControl( CLASSNAME,IDC_LV_RESULTS, LV_RESULTS, ifds::CancellationInstr,
      //IFASTBP_PROC::CANCELLATION_INSTR_LIST, 0,true, LISTFLAG_NOT_AUTO_ADD );

   IFDSListCtrl* pCtrl = 
      new IFDSAdaptedListCtrl< LVCancellationInstrAdapter >
         ( this, CLASSNAME, 
			  IDC_LV_RESULTS,
			  0, /*LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE*/0, true, true );
  
   AddIFDSListControl( pCtrl, 
                       LV_RESULTS, 
                       IFASTBP_PROC::CANCELLATION_INSTR_LIST,
                       ifds::CancellationInstr );
	
	if ( NULL != pCtrl )		
		pCtrl->SortOnColumn( 1 );


	//controls   
   AddControl( CTRL_COMBO, IDC_CMB_USING, IFASTBP_PROC::CRITERIA, ifds::CancSearchType,
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
   AddControl( CTRL_COMBO, IDC_CMB_VALUE, IFASTBP_PROC::CRITERIA, ifds::SearchUsing, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );      
}

//******************************************************************************
bool CancellationInstrDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   return(true);
}

//******************************************************************************
void CancellationInstrDlg::OnBtnRefresh() 
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnRefresh" ) );

	GetDlgItem(IDC_BTN_REFRESH)->SetFocus();
	CWaitCursor wait;

    if ( !getParent ()->send( this, I_( "RefreshCancelData" ) ) )
	{
		// Display error
		ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
	}		
	else
	{
		getParent()->reset(this, IFASTBP_PROC::CRITERIA);
		ReregisterObservers();

		showCriteria();
	}
}

//******************************************************************************
void CancellationInstrDlg::OnBtnDetails() 
{	
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDetails" ) ); 
	
   CWaitCursor wait;  

   try
   {
      int iItemNumber = 0;
	  iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::CANCELLATION_INSTR_LIST );		
	  if ( iItemNumber > 0 )
	  {		
		DString dstrTransNum, dstrTradeAdjustId;
		getParent()->getField( this, IFASTBP_PROC::CANCELLATION_INSTR_LIST, ifds::TransNum,      dstrTransNum,      true );			 
		getParent()->getField( this, IFASTBP_PROC::CANCELLATION_INSTR_LIST, ifds::TradeAdjustID, dstrTradeAdjustId, true );	 

		if ( 0 == dstrTransNum.asInteger() )
		{
			setParameter( TRANSCANCEL::BULK_CANCEL, I_( "Y" ) );			
		}
		else 
			setParameter( pTRANSNUM, dstrTransNum );

		setParameter( TRANSCANCEL::TRADE_ADJUST_ID,  dstrTradeAdjustId );			
				
		E_COMMANDRETURN eRtn = CMD_OK;
		SetMessageStatusBar( TXT_LOAD_TRANSCANCEL );

		eRtn = invokeCommand( getParent(), 
							  CMD_BPROC_TRANS_CANCEL, 
							  PROC_SUPPORT, 
							  true, 
							  NULL );

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

//**********************************************************************************
void CancellationInstrDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );

   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::CANCELLATION_INSTR_LIST );
}

//******************************************************************************
void CancellationInstrDlg::OnBtnMore() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnMore" ) );

	GetDlgItem(IDC_BTN_MORE)->SetFocus();
	CWaitCursor wait;

   SEVERITY sev = NO_SEVERITY;

   sev = getParent()->performSearch(this, IFASTBP_PROC::CANCELLATION_INSTR_LIST, SEARCH_NEXT_BLOCK );
   
   if (sev>WARNING)
   {
      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      return;
   }
   showResults();
}

//******************************************************************************
void CancellationInstrDlg::OnBtnSearch() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSearch" ) );

	GetDlgItem(IDC_BTN_SEARCH)->SetFocus();

	DString dstrSearchType, dstrSearchUsing;

	getParent()->getField( this, IFASTBP_PROC::CRITERIA, ifds::CancSearchType, dstrSearchType, false );
	getParent()->getField( this, IFASTBP_PROC::CRITERIA, ifds::SearchUsing, dstrSearchUsing, false);

	//getParent()->getField(this, ifds::SearchUsing, dstrSearchUsing, false);
		
	setParameter( CANCEL_INSTR::SEARCH_TYPE, dstrSearchType );

	if ( dstrSearchType == I_("TransStat") )
	{
		setParameter( TRANS_STATUS, dstrSearchUsing );
		setParameter( ADJUST_TYPE, NULL_STRING);
		setParameter( SEARCH_TYPE, I_("TransStat") ); 
	}
	else if (dstrSearchType == I_("AdjustType") )
	{
		setParameter( TRANS_STATUS, NULL_STRING );
		setParameter( ADJUST_TYPE, dstrSearchUsing);
		setParameter( SEARCH_TYPE, I_("AdjustType") ); 
	}

	CWaitCursor wait;
   SetMessageStatusBar( TXT_SEARCHING );

   SEVERITY sev = NO_SEVERITY;
   
   sev = getParent()->performSearch(this, IFASTBP_PROC::CANCELLATION_INSTR_LIST, SEARCH_START );
   if (sev>WARNING)
   {
      SetMessageStatusBar( NULL_STRING );
      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      return;
   }

	else
	{
		showResults();
		SetMessageStatusBar( NULL_STRING );
	}

	if ( !getParent ()->send( this, I_( "ClearUpdatedFields" ) ) )
	{
		// Display error
		ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
	}		
}

//******************************************************************************
void CancellationInstrDlg::showResults()
{
	TRACE_METHOD( CLASSNAME, I_( "showResults" ) );

	m_strScreenType = RESULTS_SCREEN;

	GetDlgItem(IDC_CMB_USING)->EnableWindow(false);
	GetDlgItem(IDC_CMB_VALUE)->EnableWindow(false);
	

	GetList(IDC_LV_RESULTS)->ShowWindow(SW_SHOW);
	
	//buttons
	GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(false);
	GetDlgItem(IDC_BTN_ADMIN)  ->EnableWindow(true);
	
    int iItemNumber = 0;
	iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::CANCELLATION_INSTR_LIST );		
	if ( iItemNumber > 0 )
		GetDlgItem( IDC_BTN_DETAIL )->EnableWindow( true );

	//static controls, frames (group boxes)
	GetDlgItem(IDC_RESULTS_FRAME)->ShowWindow(SW_SHOW);
  

   ConnectListToData( IDC_LV_RESULTS, true ); 

   LoadListControl(IDC_LV_RESULTS);
 
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::CANCELLATION_INSTR_LIST ) );

	GetList(IDC_LV_RESULTS)->SetFocus();
	

	//CheckPermission();
}

//******************************************************************************
void CancellationInstrDlg::showCriteria()
{
	TRACE_METHOD( CLASSNAME, I_( "showCriteria" ) );

	m_strScreenType = CRITERIA_SCREEN;

	//list controls
	GetList( IDC_LV_RESULTS )->ShowWindow( false );

	//static controls, frames (group boxes)
	GetDlgItem( IDC_RESULTS_FRAME )->ShowWindow( SW_HIDE );

   //combo boxes
	GetControl( IDC_CMB_USING )->Show( true );
	GetControl( IDC_CMB_VALUE )->Show( true );
	GetDlgItem(IDC_CMB_USING)->EnableWindow(true);
	GetDlgItem(IDC_CMB_VALUE)->EnableWindow(true);

	ConnectControlsToData();
   ConnectListToData( IDC_LV_RESULTS, false ); 
		
	LoadControls();

	//buttons
	GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(true);
	GetDlgItem(IDC_BTN_DETAIL)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MORE)  ->EnableWindow(false);
	GetDlgItem(IDC_BTN_ADMIN) ->EnableWindow(false);

	GetDlgItem(IDC_CMB_USING)->SetFocus();
	//CheckPermission();
}

//******************************************************************************
void CancellationInstrDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
	TRACE_METHOD( CLASSNAME, I_( "ControlUpdated" ) );
	
	switch( controlID )
   {
      case IDC_CMB_USING:
         {
				LoadControl( IDC_CMB_VALUE );				
	      }
         break;
		case IDC_CMB_VALUE:
         {
				
			}
			break;
				
		default:
         break;
   }
}

//******************************************************************************
bool CancellationInstrDlg::doDisableControl(UINT nID, bool bIsNew)
{
	TRACE_METHOD( CLASSNAME, I_( "doDisableControl" ) );

	//rules :
	//when showing criteria screen all the criteria fields are updateable
	//when showing results, all the controls are read-only
	if( nID == IDC_CMB_USING || nID == IDC_CMB_VALUE )
   {
      return (getCurrentScreenType() != CRITERIA_SCREEN);
   }

   return(false);
}

//******************************************************************************
void CancellationInstrDlg::OnDblclkLvResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnDblclkLvResults" ) );

   if (GetList(IDC_LV_RESULTS)->GetNextSelection()>=0)
      OnBtnDetails();

   *pResult = 0;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/CancellationInstrDlg.cpp-arc  $
// 
//    Rev 1.9   Dec 29 2005 13:18:40   porteanm
// Incident 501804 - Allow multiple Bulk Cancellation Instructions for the same Trade Date/Fund/Class.
// 
//    Rev 1.8   Dec 14 2005 11:58:06   ZHANGCEL
// Incident #492786 -- Fix the order issue on TradeDate and VerifyDate
// 
//    Rev 1.7   Dec 13 2005 13:46:04   ZHANGCEL
// Incident #492786 -- Fix the order issue on Status column
// 
//    Rev 1.6   Nov 30 2005 13:17:08   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.5   Nov 18 2005 13:51:26   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.4   Nov 15 2005 16:07:40   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.3   Nov 14 2005 18:04:24   ZHANGCEL
// PET1286 - FN01 -- Add logic to use the ifdsListControl with sorable columns.
// 
//    Rev 1.2   Nov 12 2005 15:10:22   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.1   Nov 11 2005 17:02:04   ZHANGCEL
// PET 1286 FN01 -- Make it works properly for the Cancellation Instruction search screen
// 
//    Rev 1.0   Nov 04 2005 11:50:56   ZHANGCEL
// Initial revision.
*/