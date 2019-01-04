//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS Co., Ltd.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2016 by IFDS Co., Ltd.
//
//******************************************************************************
//
// ^FILE   : ExternalInstitutionSearchDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : ExternalInstitutionSearchDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  Handles the code for the External Institution Search dialog
//
//******************************************************************************
#include "stdafx.h"

#include "MFDSTC.h"
#include "resource.h"
#include "ExternalInstitutionSearchDlg.h"
#include <ifastbp\FundClassProcessIncludes.h>
#include <bfproc\BPGlobal.h>
#include <bfdata\bfdatafieldproperties.hpp>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <uibase\DSTListCtrl.h>
#include <ifastcbo\dstcworksession.hpp>	

extern CLASS_IMPORT const I_CHAR* CMD_GUI_EXTERNAL_INSTITUTION_SEARCH;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ExternalInstitutionSearchDlg > dlgCreator( CMD_GUI_EXTERNAL_INSTITUTION_SEARCH );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR *CLASSNAME                      = I_( "ExternalInstitutionSearchDlg" );
   const I_CHAR *LV_EXTERNAL_INSTITUTION        = I_( "ExternalInstitutionList" );
   const I_CHAR *CODE_FOR_EXTERNAL_INSTITUTTION = I_( "00" );
   const I_CHAR *CODE_USING_INSTITUTTION_CODE   = I_( "00" );
}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId EXTERNAL_INSTITUTION;
   extern IFASTBP_LINKAGE const BFContainerId EXTERNAL_INSTITUTION_SEARCH;
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId CompanyName;
    extern CLASS_IMPORT const BFTextFieldId CompanyCode;
    extern CLASS_IMPORT const BFTextFieldId SearchType;
    extern CLASS_IMPORT const BFTextFieldId KeyString;
    extern CLASS_IMPORT const BFTextFieldId SearchExternalInstitution;
    extern CLASS_IMPORT const BFTextFieldId SearchExternalInstitutionUsing;
    extern CLASS_IMPORT const BFTextFieldId LV_ExternalInstitutionHeading;
}

namespace CND
{
   extern const long GUI_ERR_DATA_NOT_FOUND;
}

class LVExtInstitutionData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVExtInstitutionData() {}
   DString companyName_;
   DString companyCode_;
   DString itemKey_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::CompanyCode, companyCode_ );
      companyCode_.strip().upperCase();
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::CompanyName, companyName_ );
      companyName_.strip();

      itemKey_ = (*pKey);
   }
};

class LVExtInstitutionAdapter : public IFDSListCtrlAdapter< LVExtInstitutionData >
{
public:
   // required overrides
   virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2 )
   {
      int result = 0;

      const BFFieldId* pFieldId = pCtrl->getColumnField( iSortColumn - 1 );
      if( 1 == iSortColumn ) {
         result = i_strcmp( pData1->itemKey_.c_str(), pData2->itemKey_.c_str() );
      } 
      else if( NULL == pFieldId ) {
         return( 0 );
      } 
      else if( *pFieldId == ifds::CompanyCode ) {
         result = i_strcmp( pData1->companyCode_.c_str(), pData2->companyCode_.c_str() );
      } 
      else if( *pFieldId == ifds::CompanyName ) {
         result = i_strcmp( pData1->companyName_.c_str(), pData2->companyName_.c_str() );
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
         } else if( *pFieldId == ifds::CompanyCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->companyCode_.c_str();
         } else if( *pFieldId == ifds::CompanyName ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->companyName_.c_str();
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
         if( &ifds::CompanyCode == (*itCI).pFieldId_ ) (*itCI).fmt_ = LVCFMT_RIGHT;
      }
   }
};


/////////////////////////////////////////////////////////////////////////////
// ExternalInstitutionSearchDlg dialog


ExternalInstitutionSearchDlg::ExternalInstitutionSearchDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ExternalInstitutionSearchDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_dstrSearchFor( CODE_FOR_EXTERNAL_INSTITUTTION )
, m_dstrSearchUsing( CODE_USING_INSTITUTTION_CODE )
, m_bPerformSearch( false )
, m_dstrSearchValue(NULL_STRING)
{
   //{{AFX_DATA_INIT(ExternalInstitutionSearchDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

ExternalInstitutionSearchDlg::~ExternalInstitutionSearchDlg()
{
}

//******************************************************************************
BOOL ExternalInstitutionSearchDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   UpdateData(FALSE);

   return(TRUE);   // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void ExternalInstitutionSearchDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   IFDSListCtrl* pCtrl = 
      new IFDSAdaptedListCtrl< LVExtInstitutionAdapter >
         ( this, CLASSNAME, IDC_LV_EXTERNAL_INSTITUTION, 0, LISTFLAG_NOT_UPDATABLE, true, true );
   AddIFDSListControl( pCtrl, 
                       LV_EXTERNAL_INSTITUTION,
                       IFASTBP_PROC::EXTERNAL_INSTITUTION,
                       ifds::LV_ExternalInstitutionHeading );

   AddControl( CTRL_COMBO, 
               IDC_CMB_EXTERNAL_INSTITUTION, 
               IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, 
               ifds::SearchExternalInstitution, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST );

   AddControl( CTRL_COMBO, 
               IDC_CMB_NAME, 
               IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, 
               ifds::SearchExternalInstitutionUsing, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST  );

   AddControl( CTRL_EDIT, 
               IDC_EDT_NAME, 
               IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, 
               ifds::KeyString, 0 );

   getParent()->setField( this, IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, ifds::SearchExternalInstitution, I_("00"), false );
   getParent()->setField( this, IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, ifds::SearchExternalInstitutionUsing, I_("00"), false );

   FocusOnControl( IDC_EDT_NAME );
   ConnectControlsToData();
   LoadControls();

   GetDlgItem( IDC_BTN_MORE )->EnableWindow( false );
   GetDlgItem( IDC_EDT_NAME )->EnableWindow(true);
   OnSelchangeCmbUsing();
}

//*****************************************************************************
bool ExternalInstitutionSearchDlg::GetDataForControl(
                                    UINT controlID,
                                    DString &strValueOut,
                                    bool bFormatted,
                                    int index
                                    ) const
{
   bool bRtn = false;

   switch( controlID )
   {
      case IDC_CMB_EXTERNAL_INSTITUTION:
         strValueOut = m_dstrSearchFor;
         break;
      case IDC_CMB_NAME:
         strValueOut = m_dstrSearchUsing;
         break;
   }
   return(bRtn);
}

//*****************************************************************************
bool ExternalInstitutionSearchDlg::SetDataFromControl(
                                     UINT controlID,
                                     const DString &strValue,
                                     bool bFormatted,
                                     SEVERITY &sevRtn,
                                     int index
                                     )
{
   bool bRtn = false;

   switch( controlID )
   {
      case IDC_CMB_EXTERNAL_INSTITUTION:
         m_dstrSearchFor = strValue;
         getParent()->setField( this, IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, ifds::SearchExternalInstitution, m_dstrSearchFor, false);
         bRtn = true;
         break;
      case IDC_CMB_NAME:
         m_dstrSearchUsing = strValue;
         getParent()->setField( this, IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, ifds::SearchExternalInstitutionUsing, m_dstrSearchUsing, false);
         bRtn = true;
         break;
   }
   return(bRtn);
}

//*****************************************************************************
void ExternalInstitutionSearchDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ExternalInstitutionSearchDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(ExternalInstitutionSearchDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ExternalInstitutionSearchDlg)
// NOTE: the ClassWizard will add message map macros here
ON_NOTIFY(NM_DBLCLK, IDC_LV_EXTERNAL_INSTITUTION, OnDblclkExternalInstitutionList)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_CBN_SELCHANGE(IDC_CMB_NAME, OnSelchangeCmbUsing)
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
void ExternalInstitutionSearchDlg::OnDblclkExternalInstitutionList( NMHDR* pNMHDR, LRESULT* pResult ) 
{
   PostMessage( WM_COMMAND, IDOK );
   *pResult = 0;
}

//*****************************************************************************
void ExternalInstitutionSearchDlg::OnBtnSearch() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSearch" ) );
   CWaitCursor wait;

   m_dstrSearchValue = NULL_STRING;
   CString cstrSearchValue, cstrComboBoxText;
   GetDlgItem( IDC_EDT_NAME )->GetWindowText(cstrSearchValue);
   m_dstrSearchValue = cstrSearchValue.GetBufferSetLength(cstrSearchValue.GetLength());
   getParent()->setField( this, IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, ifds::KeyString, m_dstrSearchValue, false );

   int numListItems = GetList( IDC_LV_EXTERNAL_INSTITUTION )->GetItemCount( );

   if (numListItems > 0)
   {
      GetList ( IDC_LV_EXTERNAL_INSTITUTION )->DeleteAllItems();
   }

   SEVERITY sev = getParent()->performSearch( this, IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, SEARCH_START );
   if( ( sev > WARNING ) && ( GETCURRENTHIGHESTSEVERITY() == sev ) )
   {
      ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY() );
   }
   else
   {
      ConnectListToData( IDC_LV_EXTERNAL_INSTITUTION, true );
      LoadListControl( IDC_LV_EXTERNAL_INSTITUTION );
      numListItems = GetList( IDC_LV_EXTERNAL_INSTITUTION )->GetItemCount( );
      if( numListItems == 0 )
      {
         DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_DATA_NOT_FOUND);
      }
   }
   setUpdateFlag(false);      // Clears Update for Dialog
   SetDefID( IDOK );
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::EXTERNAL_INSTITUTION ) );
}

//*****************************************************************************
void ExternalInstitutionSearchDlg::OnSelchangeCmbUsing()
{
   CString cstrComboBoxText;
   GetDlgItem( IDC_CMB_NAME )->GetWindowText( cstrComboBoxText );
   cstrComboBoxText += I_(":");
   GetDlgItem( IDC_TXT_NAME )->SetWindowText( cstrComboBoxText );
}

//*****************************************************************************
void ExternalInstitutionSearchDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   switch( controlID )
   {
      case IDC_CMB_NAME:
         GetDlgItem( IDC_EDT_NAME )->SetWindowText( _T("") );
         break;
      default:
         break;
   }
   setUpdateFlag(false);   // Clears Update for Dialog
}

//*******************************************************************************
bool ExternalInstitutionSearchDlg::ListViewControlFilter(long lSubstituteId, const DString *strKey)
{
   bool bReturnValue = true;
   return( bReturnValue );
}

//*******************************************************************************
void ExternalInstitutionSearchDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore") );

   CWaitCursor wait;
   static int cursel;

   cursel = GetList( IDC_LV_EXTERNAL_INSTITUTION )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::EXTERNAL_INSTITUTION );

   if( getParent()->performSearch( this, IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_EXTERNAL_INSTITUTION );   

      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_EXTERNAL_INSTITUTION )->SetSelection(crtKey);
      }
   }

   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this,IFASTBP_PROC::EXTERNAL_INSTITUTION ) );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/ExternalInstitutionSearchDlg.cpp-arc  $
// 
