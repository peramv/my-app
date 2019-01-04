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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : HistoricalDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : January 2003
//
// ----------------------------------------------------------
//
// ^CLASS    : HistoricalDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#include <bfawdi\bfawdinterface.hpp>
#include <bfsessn\bfawdsession.hpp>

#include <bfproc\AbstractProcess.hpp>
#include "historicaldlg.hpp"
#include <ifastbp\historicalinfoprocessincludes.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <uibase\dstlistctrl.h>
#include <ifastawd\DSTCAWDSession.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_HISTORICAL_INFO;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< HistoricalDlg > dlgCreator( CMD_GUI_HISTORICAL_INFO );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "HistoricalDlg" );
   const I_CHAR *LV_HISTORICAL_LIST = I_("HistoricalList"); 
}

namespace CND
{  // Conditions used
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId SalesRepCode;
}

class LVHistoricalData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVHistoricalData() {}
   DString m_dstrFieldLabel;
   DString m_dstrPreviousDisp;
   DString m_dstrNewDisp;
   DString m_dstrModDate;
   DString m_dstrModTime;
   DString m_dstrModUser;
   DString m_workType;
   DString m_awdObjectID;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FieldLabel, m_dstrFieldLabel );
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::PreviousDisp, m_dstrPreviousDisp );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::NewDisp, m_dstrNewDisp );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ModDate, m_dstrModDate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ModTime, m_dstrModTime );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ModUser, m_dstrModUser );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::WorkType, m_workType );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::AWDObjectId, m_awdObjectID );
   }
};

class LVHistoricalAdapter : public IFDSListCtrlAdapter< LVHistoricalData >
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
      } else if( *pFieldId == ifds::FieldLabel ) {
         result = i_strcmp( pData1->m_dstrFieldLabel.c_str(), pData2->m_dstrFieldLabel.c_str() );
      } else if( *pFieldId == ifds::PreviousDisp ) {
         result = i_strcmp( pData1->m_dstrPreviousDisp.c_str(), pData2->m_dstrPreviousDisp.c_str() );
      } else if( *pFieldId == ifds::NewDisp ) {
         result = i_strcmp( pData1->m_dstrNewDisp.c_str(), pData2->m_dstrNewDisp.c_str() );
      } else if( *pFieldId == ifds::ModDate ) {
         result = i_strcmp( pData1->m_dstrModDate.c_str(), pData2->m_dstrModDate.c_str() );
      } else if( *pFieldId == ifds::ModTime ) {
         result = i_strcmp( pData1->m_dstrModTime.c_str(), pData2->m_dstrModTime.c_str() );
      } else if( *pFieldId == ifds::ModUser ) {
         result = i_strcmp( pData1->m_dstrModUser.c_str(), pData2->m_dstrModUser.c_str() );
      } else if( *pFieldId == ifds::WorkType ) {
         result = i_strcmp( pData1->m_workType.c_str(), pData2->m_workType.c_str() );
      } else if( *pFieldId == ifds::AWDObjectId ) {
         result = i_strcmp( pData1->m_awdObjectID.c_str(), pData2->m_awdObjectID.c_str() );
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
         } else if( *pFieldId == ifds::FieldLabel ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFieldLabel.c_str();
         } else if( *pFieldId == ifds::PreviousDisp ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrPreviousDisp.c_str();
         } else if( *pFieldId == ifds::NewDisp ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrNewDisp.c_str();
         } else if( *pFieldId == ifds::ModDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrModDate.c_str();
         } else if( *pFieldId == ifds::ModTime ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrModTime.c_str();
         } else if( *pFieldId == ifds::ModUser ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrModUser.c_str();
         } else if( *pFieldId == ifds::WorkType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_workType.c_str();
         } else if( *pFieldId == ifds::AWDObjectId ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_awdObjectID.c_str();
         } 

         return( 1 );
      }
      return( 0 );
   }
/*
   // optional overrides
   virtual void prepareColumns( IFDSListCtrl* pCtrl,
                                COLUMN_INFO_VECTOR& rvColumns )
   {
      COLUMN_INFO_VECTOR::iterator itCI = rvColumns.begin();
      for( ; itCI != rvColumns.end(); ++itCI )
      {
         if( &ifds::ClassCode == (*itCI).pFieldId_ ) (*itCI).fmt_ = LVCFMT_RIGHT;
         if( &ifds::Baycom == (*itCI).pFieldId_ ) (*itCI).fmt_ = LVCFMT_RIGHT;
      }
   }
*/
};


//*****************************************************************************
// Public methods
//*****************************************************************************
HistoricalDlg::HistoricalDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( HistoricalDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(HistoricalDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void HistoricalDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(HistoricalDlg)
   DDX_Control(pDX, IDMORE, m_BtnMore);
   //}}AFX_DATA_MAP

}

//*****************************************************************************
SEVERITY HistoricalDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP( HistoricalDlg, BaseMainDlg )
//{{AFX_MSG_MAP(HistoricalDlg)
ON_BN_CLICKED(IDMORE, OnBtnMore)
ON_BN_CLICKED(IDC_AWD_LOOKUP, OnBtnAwdLookup)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL HistoricalDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();
   DisplayCaption();

   return(TRUE);
}

//*****************************************************************************
void HistoricalDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
/*
   AddListControl( CLASSNAME, IDC_LV_HISTORICAL, LV_HISTORICAL_LIST, 
      ifds::HistoricalListHeadingSet, IFASTBP_PROC::HISTORICAL_INFO_LIST, 0, true, 
      CTRLFLAG_NOT_UPDATABLE);
*/
   IFDSListCtrl* pCtrl = 
      new IFDSAdaptedListCtrl< LVHistoricalAdapter >
         ( this, CLASSNAME, IDC_LV_HISTORICAL, 0, LISTFLAG_NOT_UPDATABLE, true, true );
   AddIFDSListControl( pCtrl, 
                       LV_HISTORICAL_LIST,
                       IFASTBP_PROC::HISTORICAL_INFO_LIST,
                       ifds::HistoricalListHeadingSet );

   m_BtnMore.EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   doRefresh( this, NULL_STRING );

   DString dstrAwdSourcePtr = getSession()->getSessionData( I_("_AwdInterface_Ptr_") );
   BFAwdInterface *pAwdInterface = (BFAwdInterface *)dstrAwdSourcePtr.asInteger();

   GetDlgItem (IDC_AWD_LOOKUP)->EnableWindow (pAwdInterface && pAwdInterface->isLoggedOn() &&
	   getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::HISTORICAL_INFO_LIST) );
}


//******************************************************************************
void HistoricalDlg::OnBtnMore() 
{
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel;

   cursel = GetList( IDC_LV_HISTORICAL )->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::HISTORICAL_INFO_LIST );

   if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_HISTORICAL );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_HISTORICAL )->SetSelection( crtKey );
      }
   }
   m_BtnMore.EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   GetList( IDC_LV_HISTORICAL )->SetSelection(cursel, true, true);
}

//******************************************************************************
void HistoricalDlg::OnBtnAwdLookup ()
{
   // TODO: Add your control notification handler code here
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAwdLookup "));
   
   DString dstrAwdSourcePtr = getSession()->getSessionData( I_("_AwdInterface_Ptr_") );
   BFAwdInterface *pAwdInterface = (BFAwdInterface *)dstrAwdSourcePtr.asInteger();

   if (pAwdInterface->isLoggedOn())
   { 
      DString awdObjectID;
      
	  if( getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::HISTORICAL_INFO_LIST) )
	  {
		getParent()->getField (this, IFASTBP_PROC::HISTORICAL_INFO_LIST, ifds::AWDObjectId, awdObjectID, false);
		if (!awdObjectID.empty())
		{
			DSTCAWDSession* pSession = dynamic_cast<DSTCAWDSession* >(getSession());
			if (pSession)
			{
				if (pSession->lookupAWDImageByObjectId (awdObjectID) > WARNING )
				{
				  ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
				}
			}
		}
	  }
   }
}

//******************************************************************************

bool HistoricalDlg::doRefresh( GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   DisplayCaption();

   ConnectControlsToData();
   LoadListControl( IDC_LV_HISTORICAL );
   LoadControls( -1L ); // Using -1 to load all controls
   return(true);
}

//******************************************************************************

void HistoricalDlg::DisplayCaption() 
{
   DString dstrShrNum, dstrAccountNum, dstrEntityName;
   DString dstrBrokerCode, dstrBranchCode, dstrSalesRepCode;

   // Get Shareholder Number
   getParent()->getField(this, BF::NullContainerId, ifds::ShrNum, dstrShrNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   // Get Account Number
   getParent()->getField(this, BF::NullContainerId, ifds::AccountNum, dstrAccountNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   // Get Entity Name
   if ( !dstrAccountNum.empty() ) {
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), dstrAccountNum, dstrEntityName);
   }

   // Get Broker, Branch, Sales Rep
   getParent()->getField( this, BF::NullContainerId, ifds::BrokerCode, dstrBrokerCode );
   getParent()->getField( this, BF::NullContainerId, ifds::BranchCode, dstrBranchCode );
   getParent()->getField( this, BF::NullContainerId, ifds::SalesRepCode, dstrSalesRepCode );
   
   if( !dstrBrokerCode.empty() || !dstrBranchCode.empty() || !dstrSalesRepCode.empty() )
   {
      CString cstrText;
      CString caption = GetBaseCaption().c_str();
      // for compatibility
      int i = caption.Find( _T(":") );
      if( i != -1 )
      {
         caption = caption.Left( i );
      }
      caption += I_(":");  // Add Colon
      if( !dstrBrokerCode.empty() )
      {
         cstrText.LoadString( TXT_TRANS_BROKERCODE );
         caption += I_(" ");
         caption += cstrText;
         caption += I_(" ");
         caption += dstrBrokerCode.c_str();
         caption += I_(";");
      }
      if( !dstrBranchCode.empty() )
      {
         cstrText.LoadString( TXT_TRANS_BRANCHCODE );
         caption += I_(" ");
         caption += cstrText;
         caption += I_(" ");
         caption += dstrBranchCode.c_str();
         caption += I_(";");
      }
      if( !dstrSalesRepCode.empty() )
      {
         cstrText.LoadString( TXT_TRANS_SALESREPCODE );
         caption += I_(" ");
         caption += cstrText;
         caption += I_(" ");
         caption += dstrSalesRepCode.c_str();
         caption += I_(";");
      }
      SetWindowText( caption );
   }
   else
   {

      SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
      }
   
}


//******************************************************************************

bool HistoricalDlg::ListViewControlFilter(long lSubstituteId, const DString *strKey)
{
   bool rv = true;  // one exit point
   if( lSubstituteId == ifds::HistoricalListHeadingSet.getId() )
   {
      DString dstrFieldLabel;
      const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::HISTORICAL_INFO_LIST );
      getParent()->getField(this, ifds::FieldLabel, dstrFieldLabel);
      dstrFieldLabel.upperCase();
      if( dstrFieldLabel == I_("MODDATE") || dstrFieldLabel == I_("MODUSER") )
      {
         rv = false;
      }
   }
   return(rv);
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HistoricalDlg.cpp-arc  $
// 
//    Rev 1.14   Sep 15 2008 03:42:20   phiwponp
// IN 1394896    Inconsistence of Historical screen title under pending trade - clean code
// 
//    Rev 1.13   Sep 10 2008 06:00:28   phiwponp
// IN 1394896     - Inconsistence of Historical screen title under pending trade
// 
//    Rev 1.12   10 Mar 2008 14:58:18   kovacsro
// IN#1143048 - fixed the crash when clicking on AWD Historical button, when the historical list is empty
// 
//    Rev 1.11   15 Nov 2007 18:25:54   popescu
// InternlAudit Project - 5563/01 added code for handling the AWD lookup button on the Historical Screen
// 
//    Rev 1.10   07 Nov 2007 00:18:40   popescu
// InternlAudit Project - 5563/01 added code for handling the AWD lookup button on the Historical Screen
// 
//    Rev 1.9   Sep 15 2005 15:13:16   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.8   Mar 03 2004 17:07:58   HERNANDO
// PET965 FN11 - Added ListViewControlFilter to filter-out 'ModDate' and 'ModUser'.  This was implemented until view side can filter this before sending records.  The draw back is that of the 25 records returned, less than 25 may be shown for each view call.  When View fixes this, desktop doesn't have to remove this code.
// 
//    Rev 1.7   Feb 28 2004 16:01:42   HERNANDO
// PET965 FN11 - Additional historical enhancement.  Changed list control.
// 
//    Rev 1.6   Oct 31 2003 16:20:36   HERNANDO
// PTS 10022670 - Support displaying Broker Code, Branch Code, and Sales Rep Code.
// 
//    Rev 1.5   Oct 10 2003 16:18:28   HERNANDO
// PTS 10022670 - Supporting Account Num and Shareholder Num for Title display from Historical through Account.  Added DisplayCaption.
// 
//    Rev 1.4   Mar 21 2003 18:37:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Feb 03 2003 11:56:50   popescu
// Displaying the history button only when the item is not new, and adding some txt message for the status bar
// 
//    Rev 1.2   Jan 28 2003 16:56:40   popescu
// Fixes for the More button in the Historical Info dialog
// 
//    Rev 1.1   Jan 28 2003 13:16:28   popescu
// Historical Info feature implementation
// 
//    Rev 1.0   Jan 26 2003 14:10:08   popescu
// Initial Revision
 * 
 */

