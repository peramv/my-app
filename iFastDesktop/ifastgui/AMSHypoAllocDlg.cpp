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
//    Copyright 2002 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : AMSHypoAllocDlg.cpp
// ^AUTHOR : May Lin
// ^DATE   : May. 7,2003
//
// ----------------------------------------------------------
//
// ^CLASS    : AMSHypoAllocDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "AMSHypoAllocDlg.h"
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\AmsHypoAllocProcessincludes.h>
#include <uibase\dstedit.h>
#include <bfproc\abstractprocess.hpp>
#include <uibase\dstlistctrl.h>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_AMS_HYPO_ALLOC;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AMSHypoAllocDlg > dlgCreator( CMD_GUI_AMS_HYPO_ALLOC );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME			= I_("AMSHypoAllocDlg");
   const I_CHAR * const YES					= I_("Y");
   const I_CHAR * const NO					= I_("N");
   const I_CHAR * const FUND_CODE			= I_("FundCode");
   const I_CHAR * const CLASS_CODE        = I_("ClassCode");
   const I_CHAR * const FUND_NUMBER       = I_("FundNumber");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
}

namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const AMS_GLOBAL;

}


//*****************************************************************************
// Public methods
//*****************************************************************************
AMSHypoAllocDlg::AMSHypoAllocDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AMSHypoAllocDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(AMSHypoAllocDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void AMSHypoAllocDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AMSHypoAllocDlg)

   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY AMSHypoAllocDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   return(NO_CONDITION);
}

//******************************************************************************
bool AMSHypoAllocDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
    return(true);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(AMSHypoAllocDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AMSHypoAllocDlg)

ON_BN_CLICKED( IDC_BTN_ALLOC_ADD,  OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_ALLOC_DEL,  OnBtnDel )
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL AMSHypoAllocDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//*********************************************************************
void AMSHypoAllocDlg::OnBtnAdd()
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnAdd") );
	AddToListControl( IDC_LIST_HYPO_ALLOCATION );
	GetDlgItem( IDOK )->EnableWindow( GetList(IDC_LIST_HYPO_ALLOCATION)->GetItemCount() > 0 );
}
//**********************************************************************
void AMSHypoAllocDlg::OnBtnDel()
{
  TRACE_METHOD( CLASSNAME, I_("OnBtnDel") );
  DeleteFromListControl( IDC_LIST_HYPO_ALLOCATION );
  GetDlgItem( IDOK )->EnableWindow( GetList(IDC_LIST_HYPO_ALLOCATION)->GetItemCount() > 0 );
}
//*****************************************************************************
void AMSHypoAllocDlg::OnPostInitDialog()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnInit" ) );

   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   addControls( );

   LoadListControl(IDC_LIST_FUND_ALLOCATION);
   LoadListControl(IDC_LIST_HYPO_ALLOCATION);
   GetDlgItem( IDOK )->EnableWindow( GetList(IDC_LIST_HYPO_ALLOCATION)->GetItemCount() > 0 );
   DString dstrHasPrcntAlloc;
   getParent()->getField(this,BF::NullContainerId,LIST_CHK::HasCurrPrcntAlloc, dstrHasPrcntAlloc,false );
   CString cPrcntAlloc = (dstrHasPrcntAlloc == I_("Y") ? "100.000" : "N/A");
   GetDlgItem(IDC_TXT_CURR_TOTAL_PRC_VAL)->SetWindowTextW(cPrcntAlloc);   
   GetDlgItem( IDC_LIST_FUND_ALLOCATION )->EnableWindow( (dstrHasPrcntAlloc == I_("Y") ? true : false ) );
}

//********************************************************************************

bool AMSHypoAllocDlg::addControls( )
{ 
   TRACE_METHOD( CLASSNAME, I_("addControls") );

   AddListControl(CLASSNAME, IDC_LIST_FUND_ALLOCATION, I_("AMS_FUND_ALLOC_LIST"), ifds::AMSFundAllocHeading, 
	   IFASTBP_PROC::AMS_FUND_ALLOC_LIST,0 , true, LISTFLAG_NOT_AUTO_ADD);

   AddListControl(CLASSNAME, IDC_LIST_HYPO_ALLOCATION, I_("AMS_HYPO_ALLOC_LIST"), ifds::AMSFundAllocHeading, 
	   IFASTBP_PROC::AMS_HYPO_ALLOC_LIST,0 , true, LISTFLAG_NOT_AUTO_ADD);

   AddControl( CTRL_EDIT, IDC_EDT_FUND_NUMBER, IFASTBP_PROC::AMS_HYPO_ALLOC_LIST, 
               ifds::ToFundNumber, 0 , IDC_LIST_HYPO_ALLOCATION);

   AddControl( CTRL_EDIT, IDC_EDT_FUND, IFASTBP_PROC::AMS_HYPO_ALLOC_LIST, 
               ifds::FundCode, 0 , IDC_LIST_HYPO_ALLOCATION);
   AddControl( CTRL_EDIT, IDC_EDT_CLASS, IFASTBP_PROC::AMS_HYPO_ALLOC_LIST, 
               ifds::ClassCode, 0 , IDC_LIST_HYPO_ALLOCATION);
   AddControl( CTRL_EDIT, IDC_EDT_FUND_PERCENT, IFASTBP_PROC::AMS_HYPO_ALLOC_LIST, 
               ifds::AllocPercentage, 0 , IDC_LIST_HYPO_ALLOCATION);

   AddControl( CTRL_STATIC, IDC_TXT_HYPO_TOTAL_PRC_VAL, BF::NullContainerId, 
               ifds::TotPercentage, 0 , IDC_LIST_HYPO_ALLOCATION);

   AddControl( CTRL_STATIC, IDC_TXT_CURR_TOTAL_PRC_VAL, BF::NullContainerId,
			   LIST_CHK::HasCurrPrcntAlloc, 0, 0 );
   return(true);
}

//**********************************************************************************
void AMSHypoAllocDlg::EnableControls( )
{
}

//************************************************************************************
void AMSHypoAllocDlg::DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey,
                                 bool bIsNewItem ,
                                 bool bIsDummyItem
                                 )
{	 
}

//*************************************************************************
void AMSHypoAllocDlg::ControlUpdated( UINT controlID, 
													 const DString &strValue )
{   
   switch( controlID )
   {		
		case IDC_EDT_FUND_PERCENT:
			LoadControl( IDC_TXT_HYPO_TOTAL_PRC_VAL );
			break;


		default:
			break;
	}
}

//***********************************************************************************
bool AMSHypoAllocDlg::doDisablePermCheckButton(UINT nID)
{
	return false;
}

//******************************************************************************
LRESULT AMSHypoAllocDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   DString strMarket = DSTCommonFunctions::getMarket();
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;      

	  bool bExcFund = m_uiDialogItem == IDC_EDT_FOREIGN_FUND 
					   || m_uiDialogItem == IDC_EDT_FOREIGN_CLASS 
					   || m_uiDialogItem == IDC_EDT_FOREIGN_FUND_NUM;

     bool bAssocFund = m_uiDialogItem == IDC_EDT_ASSOC_FUND 
					     || m_uiDialogItem == IDC_EDT_ASSOC_CLASS 
					     || m_uiDialogItem == IDC_EDT_ASSOC_FUND_NUM;

      CString cstr;
      GetDlgItem( m_uiDialogItem )->GetWindowText( cstr );
		DString dstr = cstr;

      // Set Search Parameters (Code, Class, Number) for Fund Class Dialog
      switch( m_uiDialogItem )
      {
         case IDC_EDT_FUND_NUMBER:
		   case IDC_EDT_FOREIGN_FUND_NUM:
         case IDC_EDT_ASSOC_FUND_NUM:
				setParameter( FUND_NUMBER, dstr );
				break;
         case IDC_EDT_FUND:
		   case IDC_EDT_FOREIGN_FUND:
         case IDC_EDT_ASSOC_FUND:
				setParameter( FUND_CODE, dstr );
				break;
		 case IDC_EDT_CLASS:
		 case IDC_EDT_FOREIGN_CLASS:
       case IDC_EDT_ASSOC_CLASS: 
				setParameter( CLASS_CODE, dstr );
				break;    
      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode,dstrClassCode,dstrFundNumber;
               getParameter ( FUND_CODE, dstrFundCode );
               getParameter ( CLASS_CODE, dstrClassCode );
               getParameter ( FUND_NUMBER, dstrFundNumber );

					if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
					{
						getParent()->setField( this, IFASTBP_PROC::AMS_HYPO_ALLOC_LIST, 
									ifds::ToFundNumber, dstrFundNumber );
					}

					getParent()->setField( this, IFASTBP_PROC::AMS_HYPO_ALLOC_LIST, 
								ifds::FundCode, dstrFundCode );
					getParent()->setField( this, IFASTBP_PROC::AMS_HYPO_ALLOC_LIST, 
			  					ifds::ClassCode, dstrClassCode );	
					LoadControl ( IDC_EDT_FUND_NUMBER );
					LoadControl ( IDC_EDT_FUND );
					LoadControl ( IDC_EDT_CLASS );
               break;
            }
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
   return(0);
}

//******************************************************************************
BOOL AMSHypoAllocDlg::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FUND_NUMBER;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_CLASS;
      }
	  else if( GetFocus() == GetDlgItem( IDC_EDT_FOREIGN_FUND_NUM ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FOREIGN_FUND_NUM;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FOREIGN_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FOREIGN_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FOREIGN_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FOREIGN_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_ASSOC_FUND_NUM ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_ASSOC_FUND_NUM;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_ASSOC_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_ASSOC_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_ASSOC_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_ASSOC_CLASS;
      }
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AMSHypoAllocDlg.cpp-arc  $
// 
//    Rev 1.0   Jul 23 2003 09:26:06   Thanisorn S.
// Initial Revision
// 
 */





