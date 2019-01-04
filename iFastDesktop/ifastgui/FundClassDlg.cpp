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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FundClassDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : FundClassDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//
//******************************************************************************
#include "stdafx.h"

#include "MFDSTC.h"
#include "resource.h"
#include "FundClassDlg.h"
#include <ifastbp\FundClassProcessIncludes.h>
#include <bfproc\BPGlobal.h>
#include <bfdata\bfdatafieldproperties.hpp>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <uibase\DSTListCtrl.h>
#include <ifastcbo\dstcworksession.hpp>	

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FUNDCLASS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FundClassDlg > dlgCreator( CMD_GUI_FUNDCLASS );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR *CLASSNAME              = I_( "FundClassDlg" );
   const I_CHAR *INIT2                  = I_( "Init2" );
   const I_CHAR *LV_FUNDCLASS           = I_( "FundClassList" );
   const I_CHAR *ELNAME                 = I_( "ElongName1" );
   const I_CHAR *FLNAME                 = I_( "FLongName" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId LV_FundNumberCodeClassHeading;
   extern CLASS_IMPORT const BFTextFieldId SearchFund;
   extern CLASS_IMPORT const BFTextFieldId SearchFundUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchFundType;
   extern CLASS_IMPORT const BFTextFieldId Name;

   extern CLASS_IMPORT const BFTextFieldId ElongName1;
   extern CLASS_IMPORT const BFTextFieldId FLongName;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId Baycom;
   extern CLASS_IMPORT const BFTextFieldId FundIDList;
   extern CLASS_IMPORT const BFTextFieldId CUSIP;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
   extern CLASS_IMPORT const BFNumericFieldId AltFndIdntfr;
}

namespace CND
{
   extern const long GUI_ERR_DATA_NOT_FOUND;
}

I_CHAR * const FUNDIDENTIFIER_COLUMN = I_("Valoren,TDCC,CUSIP,FundLFC");

class LVFundData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVFundData() {}
   DString fundName_;
   DString fundFName_;
   DString fundCode_;
   DString fundNumber_;
   DString classCode_;
   DString fundISIN_;
   DString fundWKN_;
   DString fundLFC_;
   DString fundVALOREN_;
   DString fundCUSIP_;
   DString fundTDCC_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::ElongName1, fundName_ );
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FLongName, fundFName_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundCode, fundCode_ );
      fundCode_.strip();
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ClassCode, classCode_ );
      classCode_.strip().upperCase();
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Baycom, fundNumber_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundWKN, fundWKN_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundISIN, fundISIN_ );
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Valoren, fundVALOREN_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TDCC,    fundTDCC_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::CUSIP,   fundCUSIP_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundLFC,   fundLFC_ );
   }
};

class LVFundAdapter : public IFDSListCtrlAdapter< LVFundData >
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
      } else if( *pFieldId == ifds::ElongName1 ) {
         result = i_strcmp( pData1->fundName_.c_str(), pData2->fundName_.c_str() );
      } else if( *pFieldId == ifds::FLongName ) {
         result = i_strcmp( pData1->fundFName_.c_str(), pData2->fundFName_.c_str() );
      } else if( *pFieldId == ifds::FundCode ) {
         result = i_strcmp( pData1->fundCode_.c_str(), pData2->fundCode_.c_str() );
      } else if( *pFieldId == ifds::ClassCode ) {
         result = i_strcmp( pData1->classCode_.c_str(), pData2->classCode_.c_str() );
      } else if( *pFieldId == ifds::Baycom ) {
         result = i_strcmp( pData1->fundNumber_.c_str(), pData2->fundNumber_.c_str() );
      } else if( *pFieldId == ifds::FundWKN ) {
         result = i_strcmp( pData1->fundWKN_.c_str(), pData2->fundWKN_.c_str() );
      } else if( *pFieldId == ifds::FundISIN ) {
         result = i_strcmp( pData1->fundISIN_.c_str(), pData2->fundISIN_.c_str() );
	   }else if( ifds::TDCC == *pFieldId ) {
         result = i_strcmp( pData1->fundTDCC_.c_str(), pData2->fundTDCC_.c_str() );
	   }else if( ifds::Valoren == *pFieldId ) {
         result = i_strcmp( pData1->fundVALOREN_.c_str(), pData2->fundVALOREN_.c_str() );
	   }else if( ifds::CUSIP == *pFieldId) {
         result = i_strcmp( pData1->fundCUSIP_.c_str(), pData2->fundCUSIP_.c_str() );
	   }else if( ifds::FundLFC == *pFieldId) {
         result = i_strcmp( pData1->fundLFC_.c_str(), pData2->fundLFC_.c_str() );
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
         } else if( *pFieldId == ifds::ElongName1 ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundName_.c_str();
         } else if( *pFieldId == ifds::FLongName ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundFName_.c_str();
         } else if( *pFieldId == ifds::FundCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundCode_.c_str();
         } else if( *pFieldId == ifds::ClassCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->classCode_.c_str();
         } else if( *pFieldId == ifds::Baycom ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundNumber_.c_str();
         } else if( *pFieldId == ifds::FundWKN ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundWKN_.c_str();
         } else if( *pFieldId == ifds::FundISIN ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundISIN_.c_str();
		   }else if( ifds::TDCC == *pFieldId ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundTDCC_.c_str();
	      }else if( ifds::CUSIP == *pFieldId ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundCUSIP_.c_str();
         }else if( ifds::Valoren == *pFieldId ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundVALOREN_.c_str();
         }else if( ifds::FundLFC == *pFieldId ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundLFC_.c_str();
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
         if( &ifds::ClassCode == (*itCI).pFieldId_ ) (*itCI).fmt_ = LVCFMT_RIGHT;
         if( &ifds::Baycom == (*itCI).pFieldId_ ) (*itCI).fmt_ = LVCFMT_RIGHT;
      }
   }
};


/////////////////////////////////////////////////////////////////////////////
// FundClassDlg dialog


FundClassDlg::FundClassDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FundClassDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_dstrSearchFor( CODE_FOR_FUND )
, m_dstrSearchUsing( CODE_USING_FUND_NAME )
, m_bPerformSearch( false )
, m_dstrFundCode( NULL_STRING )
, m_dstrFundNumber( NULL_STRING )
, m_dstrFundClass( NULL_STRING )
, m_dstrNameLanguage( NULL_STRING )
, m_fundCategory (NULL_STRING)
,m_dstrSearchValue(NULL_STRING)
{
   //{{AFX_DATA_INIT(FundClassDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

FundClassDlg::~FundClassDlg()
{
}

//******************************************************************************

SEVERITY FundClassDlg::init2() {
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, DOINIT );

   getParameter( PARM_FUND_CODE, m_dstrFundCode );
   getParameter( PARM_FUND_NUMBER, m_dstrFundNumber );
   getParameter( PARM_FUND_CLASS, m_dstrFundClass );
   getParameter( I_("FundCategory"), m_fundCategory );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

BOOL FundClassDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   UpdateData(FALSE);

   // Search
   CString cstrTemp = NULL_STRING;
   if( !m_dstrFundCode.empty() )
   {
      cstrTemp = m_dstrFundCode.c_str();
      GetDlgItem( IDC_EDT_NAME )->SetWindowText( cstrTemp );
      m_dstrSearchUsing = CODE_USING_FUND_CODE;
      m_bPerformSearch = true;  
   }
   else if( !m_dstrFundNumber.empty() )
   {
      cstrTemp = m_dstrFundNumber.c_str();
      GetDlgItem( IDC_EDT_NAME )->SetWindowText( cstrTemp );
      m_dstrSearchUsing = CODE_USING_FUND_NUMBER;
      m_bPerformSearch = true;
   }
   else if( !m_dstrFundClass.empty() )
   {
      cstrTemp = m_dstrFundClass.c_str();
      GetDlgItem( IDC_EDT_NAME )->SetWindowText( cstrTemp );
      m_dstrSearchUsing = CODE_USING_FUND_CLASS;
      m_bPerformSearch = true;    
   }


   return(TRUE);   // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void FundClassDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   IFDSListCtrl* pCtrl = 
      new IFDSAdaptedListCtrl< LVFundAdapter >
         ( this, CLASSNAME, IDC_LV_FUND, 0, LISTFLAG_NOT_UPDATABLE, true, true );
   AddIFDSListControl( pCtrl, 
                       LV_FUNDCLASS,
                       IFASTBP_PROC::FUNDDETAIL_LIST,
                       ifds::LV_FundNumberCodeClassHeading );
   HideColumnForFundIDGrid(pCtrl);
   AddControl( CTRL_COMBO, IDC_CMB_SEARCH, BF::NullContainerId, ifds::SearchFund, CTRLFLAG_INITCOMBO_BY_SUB_LIST /*| CTRLFLAG_GUI_FIELD*/ );
   AddControl( CTRL_COMBO, IDC_CMB_NAME, BF::NullContainerId, ifds::SearchFundType, CTRLFLAG_INITCOMBO_BY_SUB_LIST /*| CTRLFLAG_GUI_FIELD*/ );
   AddControl( CTRL_EDIT, IDC_EDT_NAME, BF::NullContainerId, ifds::Name, 0 );

   FocusOnControl( IDC_EDT_NAME );
   ConnectControlsToData();
   LoadControls();   

   if( m_bPerformSearch )
   {
      OnSelchangeCmbUsing();      // Change Label to reflect ComboBox selection
      PostMessage( WM_COMMAND, IDC_BTN_SEARCH );
   }
}

//*****************************************************************************

bool FundClassDlg::PreOk()
{
   TRACE_METHOD( CLASSNAME, PREOK );

   DSTListCtrl *dstListCtrlTemp = GetList(IDC_LV_FUND);
   int iValue = dstListCtrlTemp->GetNextSelection();
   setParameter( PARM_SEARCHITEMFOUND, (iValue == -1) ? NULL_STRING : I_( "T" ) );

   return(true);
}

//*****************************************************************************

bool FundClassDlg::GetDataForControl(
                                    UINT controlID,
                                    DString &strValueOut,
                                    bool bFormatted,
                                    int index
                                    ) const
{
   bool bRtn = false;

   switch( controlID )
   {
      case IDC_CMB_SEARCH:
         strValueOut = m_dstrSearchFor;
         break;
      case IDC_CMB_NAME:
         strValueOut = m_dstrSearchUsing;
         break;
   }
   return(bRtn);
}

//*****************************************************************************

bool FundClassDlg::SetDataFromControl(
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
      case IDC_CMB_SEARCH:
         m_dstrSearchFor = strValue;
         getParent()->setField( this, BF::NullContainerId, ifds::SearchFund, strValue );
         bRtn = true;
         break;
      case IDC_CMB_NAME:
         m_dstrSearchUsing = strValue;
         break;
   }
   return(bRtn);
}

//*****************************************************************************

void FundClassDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(FundClassDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(FundClassDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FundClassDlg)
// NOTE: the ClassWizard will add message map macros here
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore)
ON_NOTIFY(NM_DBLCLK, IDC_LV_FUND, OnDblclkFundClassList)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_CBN_SELCHANGE(IDC_CMB_NAME, OnSelchangeCmbUsing)
ON_CBN_SELCHANGE(IDC_CMB_SEARCH, OnSelchangeCmbFor)
ON_EN_KILLFOCUS(IDC_EDT_NAME, OnKillfocusSearchValue)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
bool FundClassDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{

   DString pkey = getParent()->getCurrentListItemKey (this, IFASTBP_PROC::FUNDDETAIL_LIST ); 
   if( ( ColumnKey == ELNAME ) || ( ColumnKey == FLNAME) )
   {
      strOut = pkey;
      getParent()->getField(this, (ColumnKey == ELNAME) ? ifds::ElongName1 : ifds::FLongName, strOut);
      strOut.strip();
      return(true);
   }

   return(false);   
}

//*****************************************************************************

void FundClassDlg::OnDblclkFundClassList( NMHDR* pNMHDR, LRESULT* pResult ) 
{
   PostMessage( WM_COMMAND, IDOK );
   *pResult = 0;
}

//*****************************************************************************

void FundClassDlg::OnBtnSearch() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSearch" ) );
   CWaitCursor wait;

   SEVERITY sev = getParent()->performSearch( this, IFASTBP_PROC::FUNDDETAIL_LIST, SEARCH_START );
   if( ( sev > WARNING ) && ( GETCURRENTHIGHESTSEVERITY() == sev ) )
   {
      ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY() );
   }
   else
   {
      ConnectListToData( IDC_LV_FUND, true );
      LoadListControl( IDC_LV_FUND );
      int numListItems = GetList( IDC_LV_FUND )->GetItemCount( );
      if( numListItems == 0 )
      {
         DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_DATA_NOT_FOUND);
      }
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::FUNDDETAIL_LIST ) );
   }
   setUpdateFlag(false);      // Clears Update for Dialog
   SetDefID( IDOK );
}


//*****************************************************************************
void FundClassDlg::OnSelchangeCmbUsing()
{
   CString cstrComboBoxText;
   GetDlgItem( IDC_CMB_NAME )->GetWindowText( cstrComboBoxText );
   cstrComboBoxText += I_(":");
   GetDlgItem( IDC_TXT_NAME )->SetWindowText( cstrComboBoxText );
}

//*****************************************************************************
void FundClassDlg::OnSelchangeCmbFor()
{
   if( m_dstrSearchFor == CODE_FOR_FUND )
   {
      GetDlgItem( IDC_CMB_NAME )->EnableWindow( TRUE );
      GetDlgItem( IDC_EDT_NAME )->EnableWindow( TRUE );
      GetDlgItem( IDC_CMB_NAME )->ShowWindow( TRUE );
      GetDlgItem( IDC_TXT_USING )->ShowWindow( TRUE );
      GetDlgItem( IDC_TXT_NAME )->ShowWindow( TRUE );
      GetDlgItem( IDC_EDT_NAME )->ShowWindow( TRUE );
   }
   else
   {    // All Funds
      CString cstrTemp = NULL_STRING;
      GetDlgItem( IDC_CMB_NAME )->EnableWindow( FALSE );
      GetDlgItem( IDC_EDT_NAME )->EnableWindow( FALSE );
      GetDlgItem( IDC_EDT_NAME )->SetWindowText( cstrTemp );
      GetDlgItem( IDC_CMB_NAME )->ShowWindow( FALSE );
      GetDlgItem( IDC_TXT_USING )->ShowWindow( FALSE );
      GetDlgItem( IDC_TXT_NAME )->ShowWindow( FALSE );
      GetDlgItem( IDC_EDT_NAME )->ShowWindow( FALSE );
   }
}

//*****************************************************************************
void FundClassDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   BaseControl * pControl = nullptr;

   switch( controlID )
   {
      case IDC_CMB_NAME:
         m_dstrSearchValue = NULL_STRING;
         GetDlgItem( IDC_EDT_NAME )->SetWindowText( m_dstrSearchValue.c_str() ); 
         pControl = dynamic_cast<BaseControl*>(GetDlgItem( IDC_EDT_NAME ));
         if(pControl)
            pControl->SetText(m_dstrSearchValue, false, 0, true); //forcing cleanup of internal cache
         getParent()->setField( this, BF::NullContainerId, ifds::Name, m_dstrSearchValue );
         SetDefID( IDC_BTN_SEARCH );
         PostMessage(DM_SETDEFID, IDC_BTN_SEARCH, 0);
         break;
      default:
         break;
   }
   setUpdateFlag(false);   // Clears Update for Dialog
}

//*******************************************************************************
void FundClassDlg::OnKillfocusSearchValue()
{
   CString cstrValue;
   GetDlgItem( IDC_EDT_NAME )->GetWindowText( cstrValue ); 
   m_dstrSearchValue = cstrValue;
   m_dstrSearchValue.strip().upperCase();	
   SetDefID( IDC_BTN_SEARCH );
   PostMessage(DM_SETDEFID, IDC_BTN_SEARCH, 0);
}

//*******************************************************************************

void FundClassDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore") );

   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::FUNDDETAIL_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::FUNDDETAIL_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_FUND );   
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//*******************************************************************************

bool FundClassDlg::ListViewControlFilter(long lSubstituteId, const DString *strKey)
{
   bool bReturnValue = true;
   if( lSubstituteId == ifds::LV_FundNumberCodeClassHeading.getId() )
   {
      DString dstrUseGroupFundList;
      getParent()->getField(this, BF::NullContainerId, FUNDCLASS::USE_GROUPFUNDLIST, dstrUseGroupFundList );
      if( dstrUseGroupFundList == I_("Y") )
      {
         DString dstrInGroupFundList;
         const DString *dstrKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::FUNDDETAIL_LIST );
         getParent()->getField( this, BF::NullContainerId, FUNDCLASS::IS_IN_GROUPFUNDLIST, dstrInGroupFundList );
         bReturnValue = (dstrInGroupFundList == I_("Y"));
      }
   }
   return( bReturnValue );
}

/******************************************************************************
 Input: IFDSListBase pointer
 OutPut:None
 Return:None
 Functionality:Hide FundId's coloums if not present in env level GC. 
 ******************************************************************************/
void FundClassDlg::HideColumnForFundIDGrid(IFDSListBase* const pBaseCtrl)
{
   DString dstrSubstList;
   DString dstrFundIDList,FundIDList;
   int iColumnNum =0;
   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA  )   //the fields are removed using DD for Canada 
      return;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   if( pDSTCWorkSession && 
      WARNING >= pDSTCWorkSession->getOption(ifds::FundIDList, dstrFundIDList, BF::HOST, false ))
   {
      DString dstrAltFndIdntfr;
      pDSTCWorkSession->getOption(ifds::AltFndIdntfr, dstrAltFndIdntfr, BF::HOST, false );
      dstrAltFndIdntfr.stripAll();
      boolean removeWKNColumn = I_("") != dstrAltFndIdntfr && I_("0") != dstrAltFndIdntfr;
	  boolean removeLFCColumn = I_("") != dstrAltFndIdntfr && I_("1") != dstrAltFndIdntfr;

      const BFDataFieldProperties*   pBFDataProp = BFDataFieldProperties::get( ifds::LV_FundNumberCodeClassHeading );
      pBFDataProp->getAllSubstituteValues(dstrSubstList, ClientLocaleContext::get(), true /* No Sort ,get the raw sub order */);
      I_CHAR *temp = const_cast<I_CHAR*> (dstrSubstList.c_str ());
      do
      {
         iColumnNum++;
         DString dstrSubListCode,dstrSubListDescr;   
         temp = parseIdiString (temp, dstrSubListCode, dstrSubListDescr );
         if(DSTCommonFunctions::codeInList (dstrSubListCode, FUNDIDENTIFIER_COLUMN))
         {
            bool bShowColumn = (dstrFundIDList.find(dstrSubListCode) != DString::npos); 
            pBaseCtrl->showColumn(iColumnNum, bShowColumn );
         } 
         if(I_("FundWKN") == dstrSubListCode && removeWKNColumn)
            pBaseCtrl->showColumn(iColumnNum, false);

		 if(I_("FundLFC") == dstrSubListCode && removeLFCColumn)
			 pBaseCtrl->showColumn(iColumnNum, false);

      } while (temp && temp != NULL_STRING && *temp);
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/FundClassDlg.cpp-arc  $
 // 
 //    Rev 1.27   Sep 15 2005 15:13:00   popescu
 // Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 // 
 //    Rev 1.26   Oct 21 2004 11:44:34   HERNANDO
 // PET1117 FN22 - Clears Value on changing the 'Using' Combo box.  
 // 
 //    Rev 1.25   Sep 12 2004 17:19:38   HERNANDO
 // PET1117 FN22 - Support for Group Fund List.
 // 
 //    Rev 1.24   Sep 09 2004 11:42:36   HERNANDO
 // PET1117 FN22 - WKN & ISIN Enhancement.

