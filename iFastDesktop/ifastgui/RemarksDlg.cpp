//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial.
//
//******************************************************************************
//
// ^FILE   : RemarksDlg.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : 3/99
//
// ----------------------------------------------------------
//
// ^CLASS    : RemarksDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Remarks dialog
//
//******************************************************************************

#include "stdafx.h"
#include <bfdata\bfdata.hpp>
#include "mfdstc.h"
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>

#include "remarksdlg.h"

#include <uibase\dstedit.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstcfuncs.h>
#include <uibase\ifdslistctrl.h>

#include <ifastdataimpl\dse_dstcglob_vw.hpp>

#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\Shareholder.hpp>
#include <ifastbp\remarksprocessincludes.h>

#include <assert.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_REMARKS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RemarksDlg > dlgCreator( CMD_GUI_REMARKS );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME        = I_( "RemarksDlg" );
   const I_CHAR * const LV_REMARKS       = I_( "Remarks" );

   const I_CHAR * const NAME             = I_( "Name" );

   const int MAX_CHAR_NUM_OF_REMARK      = 70;
   const int MAX_NUM_LINES_FOR_REMARKS   = 10;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const REMARKS;
   extern CLASS_IMPORT I_CHAR * const REMARK_ALERT;
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId ModPerm;
   extern CLASS_IMPORT const BFTextFieldId AddPerm;
   extern CLASS_IMPORT const BFTextFieldId DelPerm;
   extern CLASS_IMPORT const BFTextFieldId Remark_sub;
   extern CLASS_IMPORT const BFTextFieldId MoreThanOneAccount;
   extern CLASS_IMPORT const BFTextFieldId RemarkFilterBy;
}  

namespace REMARK_FILTER_BY
{
    extern CLASS_IMPORT I_CHAR * const ALL;
    extern CLASS_IMPORT I_CHAR * const ACTIVE;
    extern CLASS_IMPORT I_CHAR * const INACTIVE;
}

class LVRemarksData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVRemarksData() {}
   DString dstrEffectiveDate_;
   DString dstrRemarkType_;
   DString dstrRefAccount_;
   DString dstrRemark1_;
   DString dstrActive_;
   DString dstrRemarkAlert_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EffectiveDate, dstrEffectiveDate_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::RemarkType, dstrRemarkType_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::AccountNum, dstrRefAccount_ );      
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Remark1, dstrRemark1_ );      
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Active, dstrActive_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::RemarkAlert, dstrRemarkAlert_ );
   }
};

class LVRemarksAdapter : public IFDSListCtrlAdapter< LVRemarksData >
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
      } else if( *pFieldId == ifds::EffectiveDate ) 
	  {         
         int dater_order = DSTCommonFunctions::CompareDates ( pData1->dstrEffectiveDate_.c_str(), 
															  pData2->dstrEffectiveDate_.c_str(),
															  BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? 1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : -1;
		 // for equal, result will be 0       
      } else if( *pFieldId == ifds::RemarkType ) {
         //By: RemarkType -> EffectiveDate
         result = i_strcmp( pData1->dstrRemarkType_.c_str(), pData2->dstrRemarkType_.c_str() );

         if (result == 0)
         {
             DSTCommonFunctions::DATE_ORDER rtn = DSTCommonFunctions::CompareDates(pData1->dstrEffectiveDate_.c_str(), pData2->dstrEffectiveDate_.c_str(), BFDate::DF_DISPLAY);
             
             if (rtn == DSTCommonFunctions::FIRST_EARLIER)
                 return 1;
             else if (rtn == DSTCommonFunctions::SECOND_EARLIER ) 
                 return  -1;
         }
      } else if( *pFieldId == ifds::AccountNum ) {
         result = i_strcmp( pData1->dstrRefAccount_.c_str(), pData2->dstrRefAccount_.c_str() );
      } else if( *pFieldId == ifds::Remark1 ) {
         result = i_strcmp( pData1->dstrRemark1_.c_str(), pData2->dstrRemark1_.c_str() );
      } else if( *pFieldId == ifds::Active ) {
          //By: Active -> RemarkType -> EffectiveDate
         result = i_strcmp( pData1->dstrActive_.c_str(), pData2->dstrActive_.c_str() );

         if (result == 0)
         {
             result = i_strcmp(pData1->dstrRemarkType_.c_str(), pData2->dstrRemarkType_.c_str());

             if (result != 0)
                 return result;
             else
             {
                 DSTCommonFunctions::DATE_ORDER rtn = DSTCommonFunctions::CompareDates(pData1->dstrEffectiveDate_.c_str(), pData2->dstrEffectiveDate_.c_str(), BFDate::DF_DISPLAY);

                 if (rtn == DSTCommonFunctions::FIRST_EARLIER)
                     return 1;
                 else if (rtn == DSTCommonFunctions::SECOND_EARLIER ) 
                     return -1;
             }
         }
      } else if( *pFieldId == ifds::RemarkAlert ) {
         //By: RemarkAlert -> EffectiveDate
         result = i_strcmp(pData1->dstrRemarkAlert_.c_str(), pData2->dstrRemarkAlert_.c_str());

         if (result == 0)
         {
             DSTCommonFunctions::DATE_ORDER rtn = DSTCommonFunctions::CompareDates(pData1->dstrEffectiveDate_.c_str(), pData2->dstrEffectiveDate_.c_str(), BFDate::DF_DISPLAY);
             
             if (rtn == DSTCommonFunctions::FIRST_EARLIER)
                 return 1;
             else if (rtn == DSTCommonFunctions::SECOND_EARLIER ) 
                 return -1;
         }
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
         } else if( *pFieldId == ifds::EffectiveDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrEffectiveDate_.c_str();
         } else if( *pFieldId == ifds::RemarkType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrRemarkType_.c_str();
         } else if( *pFieldId == ifds::AccountNum ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrRefAccount_.c_str();
         } else if( *pFieldId == ifds::Remark1 ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrRemark1_.c_str();
         } else if( *pFieldId == ifds::Active ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrActive_.c_str();
         } else if( *pFieldId == ifds::RemarkAlert ) {
             pDispInfo->item.pszText = (I_CHAR*)pData->dstrRemarkAlert_.c_str();
         } 

         return( 1 );
      }
      return( 0 );
   }

   // optional overrides
   virtual void prepareColumns( IFDSListCtrl* pCtrl,
                                COLUMN_INFO_VECTOR& rvColumns )
   {
      COLUMN_INFO_VECTOR::iterator itCI = rvColumns.begin();
      for( ; itCI != rvColumns.end(); ++itCI )
      {
         if( &ifds::AccountNum == (*itCI).pFieldId_ ) (*itCI).fmt_ = LVCFMT_RIGHT;         
      }
   }
};


//******************************************************************************

RemarksDlg::RemarksDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( RemarksDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_hAccel( 0 )
, m_FormatRemarksCount(0)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   m_bShareHolderRemarks = false;
   //{{AFX_DATA_INIT(RemarksDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************

RemarksDlg::~RemarksDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

void RemarksDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(RemarksDlg)
   DDX_Control(pDX, IDC_BTN_MORE, m_BtnMore);
   DDX_Check(pDX, IDC_CHK_SHR_REMARKS, m_bShareHolderRemarks);
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(RemarksDlg, BaseMainDlg)
//{{AFX_MSG_MAP(RemarksDlg)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_CHANGE, OnBtnChange)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_COMMAND(ID_ACCEL_REMARKSLIST, OnAccelRemarkslist)
ON_COMMAND(ID_ACCEL_DETAILS, OnAccelDetails)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_EN_CHANGE(IDC_EDT_REMARKS, OnEnChangeRemarkComment)
ON_BN_CLICKED(IDC_CHK_SHR_REMARKS, OnChkShareHolderRemarks )
ON_CBN_SELCHANGE(IDC_CMB_REMARK_FILTER, OnSelRemarkFilter)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RemarksDlg message handlers

BOOL RemarksDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   DString _AccountNum;
//   DString strCaption;
   DString _ShrNum;
   DString _EntityName;

   getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _AccountNum );
   getGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, _ShrNum );
   if( _AccountNum != I_( "" ) )
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), _AccountNum,_EntityName);
   else
      _EntityName = I_( "" );
   SetShrAcctCaption(_ShrNum, _AccountNum, _EntityName);

   if( !m_hAccel )
   {
      m_hAccel = LoadAccelerators( NULL, 
                                   MAKEINTRESOURCE( IDR_ACCEL_REMARKS ) );
   }
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void RemarksDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode(UAF::REMARKS);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_REMARKS);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_REMARKS);
   
   IFDSListCtrl* ifdsListControlRemarks = new IFDSAdaptedListCtrl< LVRemarksAdapter >( this, CLASSNAME, IDC_LV_REMARKS, 0, 0, true, true );
   AddIFDSListControl( ifdsListControlRemarks, LV_REMARKS, IFASTBP_PROC::REMARKS_LIST, ifds::RemarksHeadingSet );   

   // Default the descending sorting column to Alert
	if ( NULL != ifdsListControlRemarks )		
        ifdsListControlRemarks->SortOnColumn(-7);

   AddControl( CTRL_EDIT, IDC_EDT_REMARKS, IFASTBP_PROC::REMARKS_LIST, ifds::Remark_sub, CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_WORD_WRAP, IDC_LV_REMARKS);
   AddControl( CTRL_COMBO, IDC_CMB_STATUS, IFASTBP_PROC::REMARKS_LIST, ifds::Active, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_REMARKS);
   AddControl( CTRL_DATE, IDC_DTP_EFF_DATE, IFASTBP_PROC::REMARKS_LIST, ifds::EffectiveDate, 0, IDC_LV_REMARKS );
   AddControl( CTRL_COMBO, IDC_CMB_REMARK_TYPE, IFASTBP_PROC::REMARKS_LIST, ifds::RemarkType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_REMARKS);   
   AddControl( CTRL_COMBO, IDC_CMB_REMARK_ALERT, IFASTBP_PROC::REMARKS_LIST, ifds::RemarkAlert, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_REMARKS);   

   AddControl( CTRL_COMBO, IDC_CMB_REMARK_FILTER, BF::NullContainerId, ifds::RemarkFilterBy, CTRLFLAG_INITCOMBO_BY_SUB_LIST);   
   getParent()->setField(this, BF::NullContainerId, ifds::RemarkFilterBy, REMARK_FILTER_BY::ACTIVE, false);
   
   DSTEdit *ed = dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_REMARKS ) );
   ed->SetMaxCharNum( MAX_CHAR_NUM_OF_REMARK );
   ed->LimitText( (MAX_CHAR_NUM_OF_REMARK + 2)* MAX_NUM_LINES_FOR_REMARKS - 2 );
   ed->setNumLine( MAX_NUM_LINES_FOR_REMARKS );
   
   DString dstrMoreThanOneAccount, dstrDefaultRemarksFilter;
   getParent()->getField( this, ifds::MoreThanOneAccount, dstrMoreThanOneAccount );
   ((CButton* )GetDlgItem(IDC_CHK_SHR_REMARKS))->SetCheck( I_("Y") != dstrMoreThanOneAccount );
   ((CButton* )GetDlgItem(IDC_CHK_SHR_REMARKS))->EnableWindow(I_("Y") == dstrMoreThanOneAccount );

   CWaitCursor wait;
   LoadListControl( IDC_LV_REMARKS );
   if( getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::REMARKS_LIST) > 24 )
   {
      m_BtnMore.EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   }
   else
   {
      GetDlgItem( IDC_BTN_MORE)->EnableWindow( false );
   }

   ConnectControlsToData();
   LoadControls();

   CWnd* pRemarksWnd = GetDlgItem(IDC_EDT_REMARKS);
   if (NULL != pRemarksWnd)
   {
       if (DSTEdit* pDSTEditRemarks = dynamic_cast<DSTEdit*>(pRemarksWnd))
       {
           pDSTEditRemarks->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }
}

//******************************************************************************

SEVERITY RemarksDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   getParameter( NAME, s_Name );
   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************

bool RemarksDlg::doRefresh( GenericInterface * rpGICaller, 
                            const I_CHAR * szOriginalCommand )
{
   DString _AccountNum;
   DString _ShrNum;
   DString _EntityName;
   getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _AccountNum );
   getGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, _ShrNum );
   if( _AccountNum != I_( "" ) )
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), _AccountNum,_EntityName);
   else
      _EntityName = I_( "" );
   SetShrAcctCaption(_ShrNum, _AccountNum, _EntityName);

   LoadListControl( IDC_LV_REMARKS );

   return(true);
}

//******************************************************************************

void RemarksDlg::OnBtnAdmDates() 
{
   ShowAdminDates( IFASTBP_PROC::REMARKS_LIST );
}

//******************************************************************************
void RemarksDlg::OnSelRemarkFilter()
{
    LoadListControl(IDC_LV_REMARKS);
}

//******************************************************************************

void RemarksDlg::OnBtnChange() 
{
   DString strAccountNum;
   getParent()->getField( this, ifds::AccountNum, strAccountNum );
   strAccountNum.stripLeading().stripLeading( I_CHAR( '0' ) ).stripTrailing();
   setCsiParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(strAccountNum) );
   executeCsiProcess( DcCsiProcesses::SHAREHOLDER_REMARKS );   
}

//******************************************************************************

void RemarksDlg::OnBtnAdd() 
{
   AddToListControl( IDC_LV_REMARKS );

   DString effDate;

   GetDlgItem(IDC_EDT_REMARKS)->SetFocus();
}

//******************************************************************************

void RemarksDlg::OnBtnDelete() 
{
   DeleteFromListControl( IDC_LV_REMARKS );
}

//******************************************************************************
void RemarksDlg::OnBtnMore() 
{
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel;

   cursel = GetList( IDC_LV_REMARKS )->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::REMARKS_LIST );

   SetMessageStatusBar( TXT_LOAD_REMARKS );
   if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_REMARKS );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_REMARKS )->SetSelection( crtKey );
      }
   }

   m_BtnMore.EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );

   GetList( IDC_LV_REMARKS )->SetSelection(cursel, true, true);

   SetMessageStatusBar(NULL_STRING);

}

//******************************************************************************

BOOL RemarksDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   // make certain accelerator keys are processed correctly
   if( m_hAccel != NULL )
   {
      isTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );
   }

   if( !isTranslated )
   {
      // pass message down the chain
      isTranslated = BaseMainDlg::PreTranslateMessage( pMsg );
   }

   return(isTranslated);
}

//******************************************************************************

void RemarksDlg::OnAccelRemarkslist() 
{
   // TODO: Add your command handler code here
   GetDlgItem(IDC_LV_REMARKS)->SetFocus();
}

//******************************************************************************

void RemarksDlg::OnAccelDetails() 
{
   // TODO: Add your command handler code here
   GetDlgItem(IDC_EDT_REMARKS)->SetFocus();
}

//******************************************************************************
void RemarksDlg::ControlUpdated(UINT controlID, const DString &strValue )
{
   CString cstr;
   switch( controlID )
   {
		case IDC_CMB_REMARK_TYPE:
			{
				setAccountNum();
			   ConnectControlsToData();
			   LoadControls();
			}
			break;

		case IDC_EDT_REMARKS:
		case IDC_CMB_STATUS:
		case IDC_DTP_EFF_DATE:
			{
				setAccountNum();	
			}
			break;

      default:
				break;
   }
}

//******************************************************************************
void RemarksDlg::setAccountNum()
{
	const DString &key = getParent()->getCurrentListItemKey (this, IFASTBP_PROC::REMARKS_LIST);

	if (!key.empty())
	{
		// Set the Account Num
		DString dstrAccountNum;
	
		getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum);
		dstrAccountNum.strip().stripLeading('0');
		getParent()->setField (this, IFASTBP_PROC::REMARKS_LIST, ifds::AccountNum, dstrAccountNum, false);					
	}
}

//******************************************************************************

void RemarksDlg::doPaste( UINT controlID )
{
   if( controlID == IDC_EDT_REMARKS )
   {
      m_FormatRemarksCount = 0;
   }
   return;
}

//******************************************************************************

void RemarksDlg::OnEnChangeRemarkComment()
{
   DSTEdit* remarkEdit = dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_REMARKS ) );   
   //when a text is selected in the edit box and another piece of text is being pasted - to replace the selection -
   //OnEnChangeRemarkComment() is called twice: once with the selection empty and once with the selection replaced by the new text;
   //therefore, we need to format the paragraph twice ( m_FormatRemarksCount < 2 )
   //also, we don't want to interfere with word wrapping ( !remarkEdit->isWordWrappingInProcess() )
   if( remarkEdit != NULL && m_FormatRemarksCount < 2 && !remarkEdit->isWordWrappingInProcess() )
   {	  
      CString strText;		
      int iStart,iEnd, iOffset;
      remarkEdit->GetSel(iStart, iEnd);
      remarkEdit->GetWindowText( strText );	  
	  formatParagraph( strText, iOffset, MAX_CHAR_NUM_OF_REMARK, MAX_NUM_LINES_FOR_REMARKS );	  
      remarkEdit->SetWindowText( strText );
      remarkEdit->SetSel(iStart+iOffset, iEnd+iOffset);	  
      m_FormatRemarksCount++;
   }   
}

//******************************************************************************
void RemarksDlg::OnChkShareHolderRemarks()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnChkShareHolderRemarks" ) );

   //I_CHAR* dstrMessage;
   UpdateData();
   LoadListControl ( IDC_LV_REMARKS);
}
//******************************************************************************
bool RemarksDlg::ListViewControlFilter ( long lSubstituteId, 
                                                  const DString *strKey
                                                )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "ListViewControlFilter" ) );

   bool bShow = true;

   if ( !((CButton* )GetDlgItem(IDC_CHK_SHR_REMARKS))->GetCheck() && 
         lSubstituteId == ifds::RemarksHeadingSet.getId ())
   {
     
      DString dstrFilter, dstrCurrAcctNumber, dstrAcctNumber;
      getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, dstrCurrAcctNumber);
	  dstrCurrAcctNumber.strip().stripLeading('0');
      getParent ()->getField ( this, 
                               IFASTBP_PROC::REMARKS_LIST, 
                               ifds::AccountNum, 
                               dstrAcctNumber
                             );
      bShow = (dstrCurrAcctNumber == dstrAcctNumber);
   }

   DString dstrFilterBy, dstrRemarkStatus;
   getParent()->getField(this, BF::NullContainerId, ifds::RemarkFilterBy, dstrFilterBy, false);
   getParent()->getField(this, IFASTBP_PROC::REMARKS_LIST, ifds::Active, dstrRemarkStatus, false);

   if (dstrFilterBy == REMARK_FILTER_BY::ACTIVE)
       bShow = bShow && (dstrRemarkStatus == I_("Y"));
   else if (dstrFilterBy == REMARK_FILTER_BY::INACTIVE)
       bShow = bShow && (dstrRemarkStatus == I_("N"));

   return bShow;
}

//************************************************************
bool RemarksDlg::doDisablePermCheckButton(UINT nID)
{
    if (nID == IDC_BTN_DELETE)
    {
        DString dstrRemAlert;
        getParent()->getField(this, IFASTBP_PROC::REMARKS_LIST, ifds::RemarkAlert, dstrRemAlert, false);

        if (dstrRemAlert.upperCase() == I_("Y") && !hasUpdatePermission(UAF::REMARK_ALERT))
            return true;
    }

    return false;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RemarksDlg.cpp-arc  $
 * 
 *    Rev 1.32   24 Oct 2008 10:22:34   kovacsro
 * 1399970 - GL-1254 Desktop Screen (Remarks - odd character )
 * 
 *    Rev 1.31   Sep 15 2005 15:14:46   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.30   Dec 23 2004 15:07:34   porteanm
 * PTS 10037228 - Remarks are out of sequence.
 * 
 *    Rev 1.29   Apr 20 2004 10:21:58   HERNANDO
 * PTS10029158 - Enabled Word-wrap for the Remarks Edit Control.
 * 
 *    Rev 1.28   Mar 26 2004 12:54:04   VADEANUM
 * PTS 10028335 - Inconsistent AccountNum behaviour.
 * 
 *    Rev 1.27   Dec 22 2003 17:40:38   popescu
 * PTS 10025244, Fix crash in Remarks Dialog, same issue as in ConfirmationDlg
 * 
 *    Rev 1.26   Oct 24 2003 14:14:34   HSUCHIN
 * commented out new list control and reverted back to old style
 * 
 *    Rev 1.25   Oct 03 2003 14:09:48   VADEANUM
 * Synched up from Rel 53 - PTS 10022545 - Record created when no Remark entered on the Remarks dialog - assign the AccountNum only when a Comment si entered.
 * 
 *    Rev 1.24   Oct 03 2003 13:39:42   VADEANUM
 * PTS 10022545 - Record created when no Remark entered on the Remarks dialog - assign the AccountNum only when a Comment si entered.
 * 
 *    Rev 1.23   Sep 11 2003 10:30:56   HSUCHIN
 * enhanced to use new list control
 * 
 *    Rev 1.22   Jul 30 2003 11:27:22   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.21   Mar 21 2003 18:39:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.20   Oct 09 2002 23:55:50   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.19   22 May 2002 19:16:20   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.18   27 Mar 2002 20:01:18   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.17   Jan 28 2002 11:28:46   YINGBAOL
 * HLLAPI Changes
 * 
 *    Rev 1.16   14 Jun 2001 11:58:28   SMITHDAV
 * Removed references to UserAccessProcess.
 * 
 *    Rev 1.15   14 May 2001 14:39:20   HSUCHIN
 * Session management restructuring
 * 
 *    Rev 1.14   30 Mar 2001 12:07:48   KOVACSRO
 * clean up.
 * 
 *    Rev 1.13   27 Mar 2001 16:52:26   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.12   01 Mar 2001 16:42:38   KOVACSRO
 * Modifications for permission check.
 * 
 *    Rev 1.11   Feb 23 2001 13:49:44   YINGBAOL
 * fix multiline edit isuues
 * 
 *    Rev 1.10   Feb 01 2001 16:16:44   KOVACSRO
 * Showing black text now for readonly remarks.
 * 
 *    Rev 1.9   Jan 17 2001 09:49:40   KOVACSRO
 * Fixed Add but not Modify permission check.
 * 
 *    Rev 1.8   Dec 13 2000 14:46:14   KOVACSRO
 * 1. Modified DoListItemChanged.
 * 2.Added Dummy Item logic for perm. check.
 * 
 *    Rev 1.7   Dec 05 2000 17:20:00   KOVACSRO
 * Added new item permission logic.
 * 
 *    Rev 1.6   Dec 01 2000 14:44:30   KOVACSRO
 * Added permission check.
 * 
 *    Rev 1.5   Oct 22 2000 15:39:28   WINNIE
 * diable more button if last then or equal to 24 items in the list
 * 
 *    Rev 1.4   Oct 22 2000 15:16:38   WINNIE
 * Fix crash for new account for enable more button
 * 
 *    Rev 1.3   Oct 19 2000 14:30:28   ZHANGCEL
 * Changed Delete button behaviour from disappear to disable if  "DelPerm" is "N"
 * 
 *    Rev 1.2   Oct 18 2000 14:00:18   ZHANGCEL
 * disable the 'Delete' option on Remarks screen if 'DelPerm' is 'N'
 * 
 *    Rev 1.1   Jul 26 2000 17:59:02   HUDAVID
 * added 'More' button
 * 
 *    Rev 1.0   Feb 15 2000 11:01:22   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.25   Feb 02 2000 18:10:00   BUZILA
 * changes
 * 
 *    Rev 1.24   Jan 25 2000 10:24:54   HSUCHIN
 * changed auto add flag to be on.
 * 
 *    Rev 1.23   Jan 24 2000 09:38:06   YINGBAOL
 * Hllapi Change sync.
 * 
 *    Rev 1.22   Jan 21 2000 17:24:08   HSUCHIN
 * dialog caption modification
 * 
 *    Rev 1.21   Jan 21 2000 14:41:08   BUZILA
 * init value should be set in CBO.init not in dialog
 * 
 *    Rev 1.20   Jan 19 2000 10:12:08   BUZILA
 * refresh stuf
 * 
 *    Rev 1.19   Jan 14 2000 14:44:24   HSUCHIN
 * bug fixes
 * 
 *    Rev 1.18   08 Jan 2000 14:54:54   HSUCHIN
 * modified so that effective date now defaults to next business date when new remarks is added.
 * 
 *    Rev 1.17   Dec 22 1999 11:28:32   YINGBAOL
 * Hllapi Change Sync.
 * 
 *    Rev 1.16   Dec 14 1999 12:36:26   DT24433
 * misc cleanup
 * 
 *    Rev 1.15   Dec 10 1999 10:26:02   HSUCHIN
 * added accelearators
 * 
 *    Rev 1.14   Nov 25 1999 15:50:54   HSUCHIN
 * fixed deletion of remarks
 * 
 *    Rev 1.13   Nov 24 1999 11:18:28   HSUCHIN
 * cleaned up code
 * 
 *    Rev 1.12   Nov 19 1999 16:54:26   YINGZ
 * admin
 * 
 *    Rev 1.11   Nov 19 1999 16:41:48   YINGZ
 * make it work with new controls
 * 
 *    Rev 1.10   Nov 13 1999 14:12:38   HSUCHIN
 * added add and delete functionality
 * 
 *    Rev 1.9   Nov 10 1999 11:19:22   HSUCHIN
 * modified to update transactions and using the new basedlg and controls
 * 
 *    Rev 1.8   Oct 25 1999 14:55:10   PRAGERYA
 * Minor changes
 * 
 *    Rev 1.7   Sep 22 1999 17:12:04   VASILEAD
 * modified to support C1 requirements
 * 
 *    Rev 1.6   13 Sep 1999 13:52:58   HUANGSHA
 * Synchronize with M1's changes
 * 
 *    Rev 1.5   Aug 19 1999 15:30:12   DT24433
 * changed getFieldForCurrentListItem to getField
 * 
 *    Rev 1.4   Aug 11 1999 15:10:30   BUZILA
 * fix
 * 
 *    Rev 1.3   Jul 20 1999 14:23:54   YINGZ
 * add hour glass
 * 
 *    Rev 1.2   Jul 20 1999 11:19:24   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:05:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
