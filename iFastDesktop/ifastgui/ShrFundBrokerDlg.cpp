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
//******************************************************************************
//
// ^FILE   : ShrFundBrokerDlg.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : ShrFundBroker
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#include "ShrFundBrokerdlg.h"

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\ShrFundBrokerprocessincludes.h>

#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\dstcworksession.hpp>

#include <uibase\DSTEdit.h>


extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SHR_FUND_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_SHR_FUND_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<ShrFundBrokerDlg> dlgCreator( CMD_GUI_SHR_FUND_BROKER );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("ShrFundBroker");
   const I_CHAR *LV_SHR_FUND_BROKER_LIST = I_("ShrFundBrokerList");   
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
	 extern CLASS_IMPORT I_CHAR * const SHR_FUND_BROKER;
}

namespace ifds
{
   //field ids used	
   extern CLASS_IMPORT const BFTextFieldId ShrFundBrokerHeading;   		
}



class LVShrFundBrokerData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVShrFundBrokerData() {}
   DString FundCode_;
   DString FundWKN_;
   DString FundISIN_; 
	DString FundName_;   
	DString FundBroker_;   
	DString FundBrokerName_;   
	
   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FundCode,   FundCode_ );
      FundCode_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FundWKN,    FundWKN_ );
      FundWKN_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FundISIN,   FundISIN_ );
      FundISIN_.strip();  		
	   pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FundName, FundName_ );
      FundName_.strip();      
		pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FundBroker, FundBroker_ );
      FundBroker_.strip();
		pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FundBrokerName, FundBrokerName_ );
      FundBrokerName_.strip();
   }
};

class LVShrFundBrokerAdapter : public IFDSListCtrlAdapter< LVShrFundBrokerData >
{
public:
   // required overrides
   virtual int compare(IFDSListBase* pCtrl, int iSortColumn, bool bAscending, 
      RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2)
   {
      int result = 0;

      const BFFieldId* pFieldId = pCtrl->getColumnField(iSortColumn - 1);
      if (1 == iSortColumn) 
      {
         // Condition indicator column.  Sort on image index
         result = (IFDSListBase::getColumnLVItem(lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem(lParam2, iSortColumn - 1)->iImage);
      } 
      else if (NULL == pFieldId) 
      {
         return (0);
      } 
      else if ( *pFieldId == ifds::FundCode ) 
      {
         result = i_strcmp(pData1->FundCode_.c_str(), pData2->FundCode_.c_str());
      } 
		else if ( *pFieldId == ifds::FundWKN ) 
      {
         result = i_strcmp(pData1->FundWKN_.c_str(), pData2->FundWKN_.c_str());
      } 
      else if ( *pFieldId == ifds::FundISIN ) 
      {	
			if ( DSTCommonFunctions::CompareDates( pData1->FundISIN_.c_str(), pData2->FundISIN_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = 1;
			else if ( DSTCommonFunctions::CompareDates( pData2->FundISIN_.c_str(), pData1->FundISIN_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = -1;
			// for equal, result will be 0         
      }    				
		else if ( *pFieldId == ifds::FundName ) 
      {
         result = i_strcmp(pData1->FundName_.c_str(), pData2->FundName_.c_str());
      } 
		else if ( *pFieldId == ifds::FundBroker ) 
      {

         result = i_strcmp(pData1->FundBroker_.c_str(), pData2->FundBroker_.c_str());
      } 
		else if (*pFieldId == ifds::FundBrokerName) 
      {
         result = i_strcmp(pData1->FundBrokerName_.c_str(), pData2->FundBrokerName_.c_str());
      } 
      
      return (bAscending ? result : -result);
   }

   virtual LRESULT onGetDispInfo(IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo)
   {
      if (pDispInfo->item.mask & LVIF_TEXT)
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField(pDispInfo->item.iSubItem);

         if (NULL == pFieldId) 
         {
            pDispInfo->item.pszText = I_("");
         } 
         else if (*pFieldId == ifds::FundCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundCode_.c_str();
         } 
         else if (*pFieldId == ifds::FundWKN) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundWKN_.c_str();
         } 
			else if (*pFieldId == ifds::FundISIN)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundISIN_.c_str();
         }          
         else if (*pFieldId == ifds::FundName) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundName_.c_str();
         } 
			else if (*pFieldId == ifds::FundBroker) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundBroker_.c_str();
         } 
			else if (*pFieldId == ifds::FundBrokerName) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundBrokerName_.c_str();
         } 
         
         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
ShrFundBrokerDlg::ShrFundBrokerDlg( CWnd* pParent, 
												GenericInterfaceContainer* pGIC, 
												GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(ShrFundBrokerDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_pWndItemInFocus(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(ShrFundBroker)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void ShrFundBrokerDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ShrFundBroker)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY ShrFundBrokerDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter( SHR_FUND_BROKER::ACCOUNT_NUMBER,     _dstrAccount );
	getParameter( SHR_FUND_BROKER::SHAREHOLDER_NUMBER, _dstrShareholder );	
	   
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(ShrFundBrokerDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ShrFundBroker)
ON_MESSAGE(UM_OPENFUNDLISTDLG, OpenFundListDlg)
ON_BN_CLICKED(IDC_BTN_ADMIN_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL ShrFundBrokerDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*****************************************************************************
void ShrFundBrokerDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);
   
	IFDSListCtrl* ifdsListControlShrFundBroker = 
      new IFDSAdaptedListCtrl< LVShrFundBrokerAdapter >( this, 
		                                                      CLASSNAME, 
                                                            IDC_LV_SHR_FUND_BROKER_LIST, 
																				0, 
																				0, 
																				true, 
																				true );

   AddIFDSListControl( ifdsListControlShrFundBroker, 
							  LV_SHR_FUND_BROKER_LIST, 
							  IFASTBP_PROC::SHR_FUND_BROKER_LIST, 
                       ifds::ShrFundBrokerHeading );   

	// Default the sorting column to Fund Name
	if ( NULL != ifdsListControlShrFundBroker )		
		ifdsListControlShrFundBroker->SortOnColumn( 5 ); 
	
	AddControl( CTRL_EDIT, 
		         IDC_EDIT_FUND, 
					IFASTBP_PROC::SHR_FUND_BROKER_LIST, 
					ifds::FundCode, 
					CTRLFLAG_DEFAULT,
					(UINT)IDC_LV_SHR_FUND_BROKER_LIST );

	AddControl( CTRL_EDIT, 
		         IDC_EDIT_FUND_WKN, 
					IFASTBP_PROC::SHR_FUND_BROKER_LIST, 
					ifds::FundWKN, 
					CTRLFLAG_DEFAULT,
					(UINT)IDC_LV_SHR_FUND_BROKER_LIST );
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDIT_FUND_WKN))->SetMaxCharNum( 20 );

	AddControl( CTRL_EDIT, 
		         IDC_EDIT_ISIN, 
					IFASTBP_PROC::SHR_FUND_BROKER_LIST, 
					ifds::FundISIN, 
					CTRLFLAG_DEFAULT,
					(UINT)IDC_LV_SHR_FUND_BROKER_LIST );
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDIT_ISIN))->SetMaxCharNum( 20 );

	AddControl( CTRL_STATIC, 
		         IDC_TXT_FUND_NAME, 
					IFASTBP_PROC::SHR_FUND_BROKER_LIST, 
               ifds::FundName, 
					CTRLFLAG_DEFAULT, 
					(UINT)IDC_LV_SHR_FUND_BROKER_LIST ); 

	AddControl( CTRL_EDIT, 
		         IDC_EDIT_FUND_BROKER, 
					IFASTBP_PROC::SHR_FUND_BROKER_LIST, 
					ifds::FundBroker, 
					CTRLFLAG_DEFAULT,
					(UINT)IDC_LV_SHR_FUND_BROKER_LIST );
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDIT_FUND_BROKER))->SetMaxCharNum( 6 );	
	
	
	AddControl( CTRL_STATIC, 
		         IDC_TXT_FUND_BROKER_NAME, 
					IFASTBP_PROC::SHR_FUND_BROKER_LIST, 
               ifds::FundBrokerName, 
					CTRLFLAG_DEFAULT, 
					(UINT)IDC_LV_SHR_FUND_BROKER_LIST ); 

   doRefresh(this, NULL);
}


//******************************************************************************
bool ShrFundBrokerDlg::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   //when called by the process from doRefresh, 	
   if (DString(szOriginalCommand) == I_("ReloadParams"))
   {
      getParameter( SHR_FUND_BROKER::ACCOUNT_NUMBER,     _dstrAccount );
		getParameter( SHR_FUND_BROKER::SHAREHOLDER_NUMBER, _dstrShareholder );
   }
    
   //this will load the connected controls
   LoadListControl( IDC_LV_SHR_FUND_BROKER_LIST );    
   
   GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist( this, IFASTBP_PROC::SHR_FUND_BROKER_LIST ) );
   
   DSTListCtrl *pPIDSTListCtrl = GetList( IDC_LV_SHR_FUND_BROKER_LIST );

   if( pPIDSTListCtrl )
   {
     if( pPIDSTListCtrl->GetItemCount() <= 0 )
     {         
         //add a new row if list is empty, to simulate the normal behaviour
         AddToListControl(IDC_LV_SHR_FUND_BROKER_LIST);
      }
   }
	
   SetDlgCaption();

	GetDlgItem( IDC_BTN_ADD )->EnableWindow( hasCreatePermission( UAF::SHR_FUND_BROKER ) );
	GetDlgItem( IDC_BTN_DELETE )->EnableWindow( hasDeletePermission( UAF::SHR_FUND_BROKER ) );
	GetDlgItem( IDOK )->EnableWindow( hasCreatePermission( UAF::SHR_FUND_BROKER ) ||
		                               hasUpdatePermission( UAF::SHR_FUND_BROKER ) ||
												 hasDeletePermission( UAF::SHR_FUND_BROKER ) );	

	GetDlgItem( IDC_BTN_RESET )->EnableWindow( hasCreatePermission( UAF::SHR_FUND_BROKER ) ||
															 hasUpdatePermission( UAF::SHR_FUND_BROKER ) ||
															 hasDeletePermission( UAF::SHR_FUND_BROKER ) );
	
   return true;
}

//*************************************************************************
void ShrFundBrokerDlg::SetDlgCaption()
{
   DString dstrCaption = I_("Daily Transaction Fees"); 

	DString dstrEntityName;
	dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),
																																	 _dstrAccount,
																																	 dstrEntityName );
   SetShrAcctCaption( _dstrShareholder, _dstrAccount, dstrEntityName );
}

//*************************************************************************
void ShrFundBrokerDlg::ControlUpdated( UINT controlID, 
															 const DString &strValue )
{   
   switch( controlID )
   {		
      case IDC_EDIT_FUND :
		   {							            
            LoadControl( IDC_EDIT_FUND_WKN );
            LoadControl( IDC_EDIT_ISIN );
			   LoadControl( IDC_TXT_FUND_NAME );
		   }
      case IDC_EDIT_FUND_WKN:
         {
            LoadControl( IDC_EDIT_FUND );            
            LoadControl( IDC_EDIT_ISIN );
            LoadControl( IDC_TXT_FUND_NAME );
         }
      case IDC_EDIT_ISIN:
         {
            LoadControl( IDC_EDIT_FUND );
            LoadControl( IDC_EDIT_FUND_WKN );            
            LoadControl( IDC_TXT_FUND_NAME );
         }
		case IDC_EDIT_FUND_BROKER:
			{							
				LoadControl( IDC_TXT_FUND_BROKER_NAME );
			}
			break;					
		default:
			break;
	}
}

//******************************************************************************
void ShrFundBrokerDlg::OnBtnAdd()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnAdd"));

   CWaitCursor wait;

   AddToListControl( IDC_LV_SHR_FUND_BROKER_LIST );
}

//******************************************************************************
void ShrFundBrokerDlg::OnBtnDelete()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnDelete"));

   CWaitCursor wait;
 
	DeleteFromListControl( IDC_LV_SHR_FUND_BROKER_LIST );
}

//******************************************************************************
void ShrFundBrokerDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel = GetList( IDC_LV_SHR_FUND_BROKER_LIST )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );
   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::SHR_FUND_BROKER_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::SHR_FUND_BROKER_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl(IDC_LV_SHR_FUND_BROKER_LIST);
      if (*crtKey != NULL_STRING)
      {
         GetList( IDC_LV_SHR_FUND_BROKER_LIST )->SetSelection( crtKey );
      }
   }

   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::SHR_FUND_BROKER_LIST));
   
	GetList( IDC_LV_SHR_FUND_BROKER_LIST )->SetSelection( cursel, true, true );
}
//****************************************************************
void ShrFundBrokerDlg::OnBtnReset()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnReset"));

   CWaitCursor wait;

   ResetListItem(IDC_LV_SHR_FUND_BROKER_LIST);
}

//*************************************************************************
void ShrFundBrokerDlg::OnBtnAdmDates()
{
   ShowAdminDates( IFASTBP_PROC::SHR_FUND_BROKER_LIST );
}

//******************************************************************
BOOL ShrFundBrokerDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   //do not allow F4 on the edit controls that are not updateable
   if (pMsg->message == WM_KEYDOWN && 
      (int)(pMsg->wParam) == VK_F4 && 
      !IsSelectedCtrlUpdateable())
   {
      return TRUE;
   }
   
	if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4)
   {
      m_pWndItemInFocus = GetFocus();
      
		if( m_pWndItemInFocus == GetDlgItem( IDC_EDIT_FUND ) )
      {
         PostMessage( UM_OPENFUNDLISTDLG );
      }      		
   }
   return BaseMainDlg::PreTranslateMessage(pMsg);
}

//******************************************************************
LRESULT ShrFundBrokerDlg::OpenFundListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundListDlg" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      if( m_pWndItemInFocus == GetDlgItem( IDC_EDIT_FUND ) ) 
      {
         DString dstrFundCode;

         GetControlText( IDC_EDIT_FUND, dstrFundCode);
         setParameter (I_("FundCode"), dstrFundCode);
      }       
      
		//invoke the fund class dialog and process
      SetMessageStatusBar (TXT_LOAD_FUND_INFO);
      eRtn = invokeCommand( getParent(), 
								    CMD_BPROC_FUNDCLASS, 
								    PROC_SUPPORT, 
									 true, 
									 NULL );
      switch (eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, 
                       dstrClassCode;

               getParameter (I_("FundCode"), dstrFundCode);
               getParent()->setField ( this, 
                                       IFASTBP_PROC::SHR_FUND_BROKER_LIST, 
                                       ifds::FundCode, 
                                       dstrFundCode);               

               LoadControl( IDC_EDIT_FUND );   
               LoadControl( IDC_EDIT_FUND_WKN );
               LoadControl( IDC_EDIT_ISIN );
					LoadControl( IDC_TXT_FUND_NAME );
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            SetMessageStatusBar (NULL_STRING);
            break;
      }
      SetMessageStatusBar (NULL_STRING);
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return eRtn;
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/ShrFundBrokerDlg.cpp-arc  $
// 
//    Rev 1.3   Sep 15 2005 15:15:14   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.2   Nov 28 2004 14:11:12   vadeanum
// PET1117 FN08 - Shareholder Fund Broker support 
// 
//    Rev 1.1   Nov 11 2004 16:32:50   vadeanum
// PET1117 FN08 - Shareholder Fund Broker support - work in progress.
// 
//    Rev 1.0   Nov 04 2004 10:31:44   VADEANUM
// Initial revision.
//
