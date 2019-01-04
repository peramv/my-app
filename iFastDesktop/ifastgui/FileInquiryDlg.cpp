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
// ^FILE   : FileInquiryDlg.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/15/2005
//
// ^CLASS    : FileInquiryDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include <bfproc\AbstractProcess.hpp>

#include "FileInquiryDlg.h"
#include "MsgDlg.h"
#include <ifastcbo\dstcworksession.hpp>
#include <configmanager.hpp>
#include <ifastbp\FileInquiryProcessInclude.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>
#include <uibase\dstbutton.h>
#include <ifastcbo\dstcommonfunction.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FILE_INQUIRY;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FileInquiryDlg > dlgCreator( CMD_GUI_FILE_INQUIRY);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FILE_INQUIRY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MSG;

namespace
{
	const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );
   const I_CHAR * const CLASSNAME         = I_( "FileInquiryDlg" );
	const I_CHAR * const LV_FILE_INQUIRY_LIST = I_( "File Inquiry List" );
	const I_CHAR * const LV_MESSAGE_EVENT_LIST = I_( "Message Event List" );
}

namespace CND
{//Conditionsused
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FileInquiryListHeader;
   extern CLASS_IMPORT const BFTextFieldId MsgEventHeading;
}

class LVFileInquiryData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVFileInquiryData() {}

   DString m_dstrNetWorkId, m_dstrFileName, m_dstrProcessDate, m_dstrProcessTime, m_dstrEnvelopeStatus;
   
   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {

      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::NetworkID, m_dstrNetWorkId );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FileName, m_dstrFileName );
		pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EnvelopeStatus, m_dstrEnvelopeStatus );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ProcessDate, m_dstrProcessDate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ProcessTime, m_dstrProcessTime );           
   }
};

class LVFileInquiryAdapter : public IFDSListCtrlAdapter< LVFileInquiryData >
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
         result = i_strcmp( pData1->m_dstrNetWorkId.c_str(), pData2->m_dstrNetWorkId.c_str() );
      } else if( *pFieldId == ifds::FileName ) {
         result = i_strcmp( pData1->m_dstrFileName.c_str(), pData2->m_dstrFileName.c_str() );
		} else if( *pFieldId == ifds::EnvelopeStatus ) {
         result = i_strcmp( pData1->m_dstrEnvelopeStatus.c_str(), pData2->m_dstrEnvelopeStatus.c_str() );
		} else if( *pFieldId == ifds::ProcessDate ) {
			if ( DSTCommonFunctions::CompareDates( pData1->m_dstrProcessDate.c_str(), pData2->m_dstrProcessDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = 1;
			else if ( DSTCommonFunctions::CompareDates( pData2->m_dstrProcessDate.c_str(), pData1->m_dstrProcessDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = -1;
		} else if( *pFieldId == ifds::ProcessTime ) {
         result = i_strcmp( pData1->m_dstrProcessTime.c_str(), pData2->m_dstrProcessTime.c_str() );
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
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrNetWorkId.c_str();
         } else if( *pFieldId == ifds::FileName ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFileName.c_str();
         } else if( *pFieldId == ifds::EnvelopeStatus ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrEnvelopeStatus.c_str();
         } else if( *pFieldId == ifds::ProcessDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrProcessDate.c_str();
         } else if( *pFieldId == ifds::ProcessTime ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrProcessTime.c_str();
         } 
         return( 1 );
      }
      return( 0 );
   }
};

//******************************************************************************

FileInquiryDlg::FileInquiryDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FileInquiryDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	
   //{{AFX_DATA_INIT(FileInquiryDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
FileInquiryDlg::~FileInquiryDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void FileInquiryDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(FileInquiryDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FileInquiryDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FileInquiryDlg)

	ON_BN_CLICKED(IDC_BTN_MESSAGE, OnBtnMessage)
	ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FileInquiryDlg message handlers


//******************************************************************************

BOOL FileInquiryDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   // Get Parameters
  
   return(TRUE);
}


//******************************************************************************
void FileInquiryDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   CWaitCursor wait;
   addControls();
}

//******************************************************************************
SEVERITY FileInquiryDlg::doInit()
{
   SEVERITY sevRtn = NO_CONDITION;

   return(sevRtn);
}
//******************************************************************************
void FileInquiryDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );    
	
	//controls
   
   IFDSListCtrl* pCtrl = 
      new IFDSAdaptedListCtrl< LVFileInquiryAdapter >
         ( this, CLASSNAME, 
			  IDC_LV_FILES_LIST,
			  0, LISTFLAG_NOT_UPDATABLE, true, true );
  
   AddIFDSListControl( pCtrl, 
                       LV_FILE_INQUIRY_LIST, 
                       IFASTBP_PROC::MSG_ENVELOPE_LIST,
                       ifds::FileInquiryListHeader );
	

	AddListControl( CLASSNAME, 
                   IDC_LV_ERROR_LIST,
                   LV_MESSAGE_EVENT_LIST,
                   ifds::MsgEventHeading,
						 IFASTBP_PROC::MSG_EVENT_LIST, IDC_LV_FILES_LIST, true, LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE );

   
    LoadListControl( IDC_LV_FILES_LIST );
	 GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::MSG_ENVELOPE_LIST ) );
}

//******************************************************************************

bool FileInquiryDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );
	LoadListControl( IDC_LV_FILES_LIST );
   return(true);
}



//******************************************************************************

void FileInquiryDlg::OnBtnMore() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnMore" ) );

	SetMessageStatusBar( IDS_LOADING_FILE_SEARCH );
   CWaitCursor wait;
   static int cursel;

   cursel = GetList( IDC_LV_FILES_LIST )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::MSG_ENVELOPE_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::MSG_ENVELOPE_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_FILES_LIST );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_FILES_LIST )->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::MSG_ENVELOPE_LIST ) );
   GetList( IDC_LV_FILES_LIST )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);
}


//******************************************************************************
void FileInquiryDlg::OnBtnMessage() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnMessage" ) );

	try
   {
		E_COMMANDRETURN eRtn = CMD_CANCEL;
		SetMessageStatusBar( IDS_LOADING_MSG );
		CWaitCursor wait;
		static int cursel;
	
	// Set Enevelope ID Parameter
		DString EnvelopeID;
		getParent()->getField(this, IFASTBP_PROC::MSG_ENVELOPE_LIST, ifds::EnvelopeID, EnvelopeID, false);
		setParameter( MFCAN_IP_PARAM::ENVELOPE_ID, EnvelopeID );
		// Set Search Type
		setParameter( MFCAN_IP_PARAM::SEARCH_TYPE, I_("EnvelopeID") );

		eRtn = invokeCommand( getParent(), CMD_BPROC_MSG, PROC_SUPPORT, true, NULL );
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

//******************************************************************************
/* void FileInquiryDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
	TRACE_METHOD( CLASSNAME, I_( "ControlUpdated" ) );

	switch( controlID )
   {
      break;

		default:
         break;
   }
}*/

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FileInquiryDlg.cpp-arc  $
// 
//    Rev 1.1   Sep 15 2005 15:12:12   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.0   Feb 24 2005 17:48:08   ZHANGCEL
// Initial revision.
//
*/