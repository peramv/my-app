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
// ^FILE   : ForeignContentWorksheetDlg.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : ForeignContentWorksheetDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#include "foreigncontentworksheetdlg.h"

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\foreigncontentworksheetprocessincludes.h>

#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\dstcworksession.hpp>

#include <uibase\DSTEdit.h>
#include <uibase\DSTComboBox.h>



extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FOREIGN_CONTENT_WORKSHEET;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_FOREIGN_CONTENT_WORKSHEET;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<ForeignContentWorksheetDlg> dlgCreator( CMD_GUI_FOREIGN_CONTENT_WORKSHEET );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("ForeignContentWorksheetDlg");  
   const int  HYPO_GROUP		= 1000;
   const int  ACB_GROUP		= 1001;
   const I_CHAR * const START_SEARCH = I_("StartSearch");  	
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
ForeignContentWorksheetDlg::ForeignContentWorksheetDlg( CWnd* pParent, 
								  GenericInterfaceContainer* pGIC, 
								  GenericInterface* pGIParent, 
								  const Command& rCommand )
: BaseMainDlg(ForeignContentWorksheetDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_pWndItemInFocus(NULL),
m_bNotify(true)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
	m_dstrDefautTransType = TRADETYPE::PURCHASE;
   //{{AFX_DATA_INIT(ForeignContentWorksheetDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void ForeignContentWorksheetDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ForeignContentWorksheetDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY ForeignContentWorksheetDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);
   
	getParameter( FOREIGN_CONTENT_WORKSHEET::ACCOUNT_NUMBER,     _dstrAccount );	
	getParameter( FOREIGN_CONTENT_WORKSHEET::SHAREHOLDER_NUMBER, _dstrShareholder );	

   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(ForeignContentWorksheetDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ForeignContentWorksheetDlg)
ON_MESSAGE(UM_OPENFUNDLISTDLG, OpenFundListDlg)
ON_BN_CLICKED(IDC_BTN_CALCULATE, OnBtnCalculate)
ON_BN_CLICKED(ID_BTN_REFRESH, OnBtnRefresh)
//ON_CBN_KILLFOCUS(IDC_CMB_TRANSACTION, OnKillfocusCmbTransType)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL ForeignContentWorksheetDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*****************************************************************************
void ForeignContentWorksheetDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);
   


	AddControl( CTRL_COMBO, 
		         IDC_CMB_TRANSACTION, 
					IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
               ifds::TradesTransType, 
					CTRLFLAG_INITCOMBO_BY_SUB_LIST );

    AddControl( CTRL_DATE, 
		        IDC_DTP_TRADE_DATE, 
				  IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
              ifds::EffectiveDate,
				  0,HYPO_GROUP );
  	  
   AddControl( CTRL_EDIT, 
		         IDC_EDT_FUND_NUMBER, 
					IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
               ifds::FromFundNumber, 
					CTRLFLAG_DEFAULT,HYPO_GROUP );

	AddControl( CTRL_EDIT, 
		         IDC_EDT_FUND, 
					IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
               ifds::FromFund, 
					CTRLFLAG_DEFAULT,HYPO_GROUP );

	AddControl( CTRL_EDIT, 
		         IDC_EDT_CLASS, 
					IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
               ifds::FromClass, 
					CTRLFLAG_DEFAULT,HYPO_GROUP );

	AddControl( CTRL_STATIC, 
		         IDC_TXT_FUND_DESCRIPTION, 
					IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
               ifds::FromFundName, 
					CTRLFLAG_DEFAULT,
					HYPO_GROUP); 


  
	AddControl( CTRL_EDIT, 
		         IDC_EDT_TO_FUND_NUMBER, 
					IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
               ifds::ToFundNumber, 
					CTRLFLAG_DEFAULT,HYPO_GROUP );

	AddControl( CTRL_EDIT, 
		         IDC_EDT_TO_FUND, 
					IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
               ifds::ToFund, 
					CTRLFLAG_DEFAULT,HYPO_GROUP );

	AddControl( CTRL_EDIT, 
		         IDC_EDT_TO_CLASS, 
					IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
               ifds::ToClass, 
					CTRLFLAG_DEFAULT,HYPO_GROUP );

	AddControl( CTRL_STATIC, 
		         IDC_TXT_TO_FUND_DESCRIPTION, 
					IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
               ifds::ToFundName, 
					CTRLFLAG_DEFAULT,
					HYPO_GROUP ); 	


  AddControl( CTRL_EDIT, 
		        IDC_EDT_AMOUNT, 
				  IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
              ifds::Amount, 
				  CTRLFLAG_DEFAULT,HYPO_GROUP );
	 
	// Don't allow negatives for this control
	DSTEdit *dstEditAcctNum  = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_ACCT_NUM ) );   
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_AMOUNT))->SetAllowedChars(I_("0123456789."));


	
	AddControl( CTRL_COMBO, 
		         IDC_TXT_AMOUNT_TYPE_DOLLAR, 
					IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
               ifds::AmtType, 
					CTRLFLAG_INITCOMBO_BY_SUB_LIST,HYPO_GROUP ); 		
//domestic

	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_BEFORE_DOMESTIC1, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::DomesticACBAmtBefore, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 
	
	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_BEFORE_DOMESTIC2, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::DomesticPrcntBefore, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 


	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_AFTER_DOMESTIC1, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::DomesticACBCAmtAfter, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 
	
	AddControl( CTRL_STATIC, 
		      IDC_TXT_RESULT_AFTER_DOMESTIC2, 
				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
            ifds::DomesticPrcntAfter, 
				CTRLFLAG_DEFAULT,ACB_GROUP ); 
//foreign
	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_BEFORE_FC1, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::FrgnACBAmtBefore, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 
	
	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_BEFORE_FC2, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::FrgnPrcntBefore, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 


	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_AFTER_FC1, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::FrgnACBAmtAfter, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 
	
	AddControl( CTRL_STATIC, 
		      IDC_TXT_RESULT_AFTER_FC2, 
				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
            ifds::FrgnPrcntAfter, 
				CTRLFLAG_DEFAULT,ACB_GROUP ); 
// total

	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_BEFORE_TOTAL1, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::ACBTotalAmtBefore, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 
	
/*	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_BEFORE_TOTAL2, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::ACBTotalPrcntBefore, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 

*/
	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_AFTER_TOTAL1, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::ACBTotalAmtAfter, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 
/*	
	AddControl( CTRL_STATIC, 
		      IDC_TXT_RESULT_AFTER_TOTAL2, 
				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
            ifds::ACBTotalPrcntAfter, 
				CTRLFLAG_DEFAULT,ACB_GROUP ); 

*/
//  foreign allowed

	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_BEFORE_FC_ALLOWED1, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::FrgnAllowedAmtBefore, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 
	
	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_BEFORE_FC_ALLOWED2, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::FrgnAllowedPrcntBefore, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 


	AddControl( CTRL_STATIC, 
		         IDC_TXT_RESULT_AFTER_FC_ALLOWED1, 
					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
               ifds::FrgnAllowedAmtAfter, 
					CTRLFLAG_DEFAULT,ACB_GROUP ); 
	
	AddControl( CTRL_STATIC, 
		      IDC_TXT_RESULT_AFTER_FC_ALLOWED2, 
				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
            ifds::FrgnAllowedPrcntAfter, 
				CTRLFLAG_DEFAULT,ACB_GROUP ); 
	
//Unit price
	AddControl( CTRL_STATIC, 
		      IDC_TXT_NAV_RESULTS, 
				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, 
            ifds::Rate, 
				CTRLFLAG_DEFAULT,ACB_GROUP ); 	
		
	ConnectHypoControls(false);
	initTransType();
	displayLabelByTransType( );

  	doRefresh(this, NULL);
}

//******************************************************************************
void ForeignContentWorksheetDlg::initTransType()
{

	GetControl(IDC_CMB_TRANSACTION)->ConnectToData(true);
	getParent()->setField(this, IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
								 ifds::TradesTransType, m_dstrDefautTransType,false);

	DSTComboBox* pCmb = dynamic_cast<DSTComboBox* >(GetControl(IDC_CMB_TRANSACTION) );
	if( pCmb )
	{
		pCmb->SetSelectionByData(m_dstrDefautTransType);
	}
	pCmb->Enable(true);
}
//******************************************************************************
bool ForeignContentWorksheetDlg::doRefresh( GenericInterface *rpGICaller, 
                                            const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   //when called by the process from doRefresh, 	
   if (DString(szOriginalCommand) == I_("ReloadParams"))
   {      
		getParameter( FOREIGN_CONTENT_WORKSHEET::ACCOUNT_NUMBER,     _dstrAccount );
		getParameter( FOREIGN_CONTENT_WORKSHEET::SHAREHOLDER_NUMBER, _dstrShareholder );
   }
    	
   SetDlgCaption();	
	

   return true;
}

//*************************************************************************
void ForeignContentWorksheetDlg::SetDlgCaption()
{   		
	DString dstrEntityName;
	dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),
																																	 _dstrAccount,
																																	 dstrEntityName );
   SetShrAcctCaption( _dstrShareholder, _dstrAccount, dstrEntityName );
}

//*************************************************************************
void ForeignContentWorksheetDlg::ControlUpdated( UINT controlID, 
															 const DString &strValue )
{   	
   switch( controlID )
   {		
		case IDC_CMB_TRANSACTION:
			//GetControl(IDC_CMB_TRANSACTION)->Enable(false);
			if( m_bNotify )
			{
				m_bNotify = false;
				getParent()->send(this,I_("TransTypeSelect" ) );

				ConnectHypoControls( true );
				displayLabelByTransType();
				LoadControls( HYPO_GROUP );
				GetControl(IDC_CMB_TRANSACTION)->onNotify(FIELD_NOTIFICATIONS,E_EVENT_PROPERTY_CHANGE,I_("") );
			}	
				
				//Enable(false);
			break;

		case IDC_EDT_FUND_NUMBER:
		case IDC_EDT_FUND:
		case IDC_EDT_CLASS:
			{
				//LoadControl( IDC_TXT_FUND_DESCRIPTION );
			}
			break;
		case IDC_EDT_TO_FUND_NUMBER:
		case IDC_EDT_TO_FUND:
		case IDC_EDT_TO_CLASS:
			{							
				//LoadControl( IDC_TXT_TO_FUND_DESCRIPTION );
			}
			break;
		default:
			break;
	}
}

//******************************************************************************
void ForeignContentWorksheetDlg::OnBtnCalculate()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnCalculate" ) );

   CWaitCursor wait;
   BaseControl* pBControl = dynamic_cast<BaseControl*>(GetFocus());
   if( pBControl )  pBControl->Store();
	
   SEVERITY sev = getParent()->performSearch( this, IFASTBP_PROC::FOREIGN_CONTENT_TRADE,
		SEARCH_START );
   if( sev  <= WARNING )
   {
		int iUserSelection = 0;
		if ( sev == WARNING )
		{
			LoadControls(HYPO_GROUP);			
		    iUserSelection = ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY() );	
		}
		// If no Warning has been raised, then iUserSelection is 0, and the calculation results will be displayed
		// If Warning has been raised, and user selects Ok, then iUserSelection is 1, and the calculation results will be displayed
		// If Warning has been raised, and user selects Cancel, then iUserSelection is 2, and the calculation results will not be displayed
		if ( 2 != iUserSelection )
		{
			ConnectACBControls(true);
			LoadControls(ACB_GROUP);	
			GetDlgItem(IDC_BTN_CALCULATE)->EnableWindow(false);
			EnableHypoControls(false);
		}		
	}
	else
	{
		LoadControls(HYPO_GROUP);			
		ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY() );	
	}
}
//****************************************************************
void ForeignContentWorksheetDlg::OnBtnRefresh()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnRefresh"));

	CWaitCursor wait;
	getParent()->send(this,I_("OnBtnRefresh") );
	ConnectHypoControls(false);
	ConnectACBControls(false);
	initTransType();
	GetDlgItem(IDC_BTN_CALCULATE)->EnableWindow(true);
	EnableHypoControls(true);
	m_bNotify = true;
	GetDlgItem(IDC_CMB_TRANSACTION)->SetFocus();



	// enable Transaction Type
	//CheckPermission();   
}

//******************************************************************
BOOL ForeignContentWorksheetDlg::PreTranslateMessage(MSG* pMsg) 
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
      
		if( m_pWndItemInFocus == GetDlgItem( IDC_EDT_FUND_NUMBER ) ||
			 m_pWndItemInFocus == GetDlgItem( IDC_EDT_FUND ) ||
			 m_pWndItemInFocus == GetDlgItem( IDC_EDT_CLASS ) ||
			 m_pWndItemInFocus == GetDlgItem( IDC_EDT_TO_FUND_NUMBER ) ||	
			 m_pWndItemInFocus == GetDlgItem( IDC_EDT_TO_FUND ) ||
			 m_pWndItemInFocus == GetDlgItem( IDC_EDT_TO_CLASS ) )
      {
         PostMessage( UM_OPENFUNDLISTDLG );
      }      		
   }
   return BaseMainDlg::PreTranslateMessage(pMsg);
}

//******************************************************************
LRESULT ForeignContentWorksheetDlg::OpenFundListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundListDlg" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try

   {
		CString cstr;
		m_pWndItemInFocus->GetWindowText(cstr);
      setParameter ( I_("FundNumber"), I_(""));
      setParameter ( I_("FundCode"), I_(""));
      setParameter ( I_("ClassCode"), I_(""));
      setParameter ( I_("AccountNum"), _dstrAccount);

      if( m_pWndItemInFocus == GetDlgItem( IDC_EDT_FUND ) ||
			 m_pWndItemInFocus == GetDlgItem( IDC_EDT_TO_FUND ) ) 
      {
         
         setParameter (I_("FundCode"), LPCTSTR(cstr));
      } 
      else if( m_pWndItemInFocus == GetDlgItem( IDC_EDT_CLASS ) ||
			      m_pWndItemInFocus == GetDlgItem( IDC_EDT_TO_CLASS ) )
      {
         setParameter (I_("ClassCode"), LPCTSTR(cstr) );
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

					BFFieldId bfFieldIdFund, bfFieldIdClass;

					UINT uiIDFund, uiIDClass,uiIDNum,uiIDName; 
					if ( m_pWndItemInFocus == GetDlgItem( IDC_EDT_FUND ) )
					{
						bfFieldIdFund = ifds::FromFund;
						bfFieldIdClass = ifds::FromClass;
						uiIDFund        = IDC_EDT_FUND;
						uiIDClass       = IDC_EDT_CLASS;
						uiIDNum = IDC_EDT_FUND_NUMBER;
						uiIDName = IDC_TXT_FUND_DESCRIPTION;
					}
					else if ( m_pWndItemInFocus == GetDlgItem( IDC_EDT_TO_FUND ) )
					{
						bfFieldIdFund = ifds::ToFund;
						bfFieldIdClass = ifds::ToClass;
						uiIDFund        = IDC_EDT_TO_FUND;
						uiIDClass       = IDC_EDT_TO_CLASS;
						uiIDNum = IDC_EDT_TO_FUND_NUMBER;
						uiIDName = IDC_TXT_TO_FUND_DESCRIPTION;

					}

               getParent()->setField ( this, 
                                       IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
                                       bfFieldIdFund, 
                                       dstrFundCode);

               getParameter (I_("ClassCode"), dstrClassCode);
					if ( m_pWndItemInFocus == GetDlgItem( IDC_EDT_CLASS ) )
					{
						bfFieldIdFund = ifds::FromFund;
						bfFieldIdClass = ifds::FromClass;
						uiIDFund        = IDC_EDT_FUND;
						uiIDClass       = IDC_EDT_CLASS;
						uiIDNum = IDC_EDT_FUND_NUMBER;
						uiIDName = IDC_TXT_FUND_DESCRIPTION;

					}
					else if ( m_pWndItemInFocus == GetDlgItem( IDC_EDT_TO_CLASS ) )
					{
						bfFieldIdFund = ifds::ToFund;
						bfFieldIdClass = ifds::ToClass;
						uiIDFund        = IDC_EDT_FUND;
						uiIDClass       = IDC_EDT_CLASS;
						uiIDNum = IDC_EDT_FUND_NUMBER;
						uiIDName = IDC_TXT_TO_FUND_DESCRIPTION;

					}

               getParent()->setField ( this, 
                                       IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
                                       bfFieldIdClass, 
                                       dstrClassCode );

               LoadControl( uiIDFund );
               LoadControl( uiIDClass );
					LoadControl( uiIDNum );
					LoadControl( uiIDName );
			

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

//*******************************************************************************
void ForeignContentWorksheetDlg::OnKillfocusCmbTransType()
{
   DString dstrValue;
   DSTComboBox* pCmb = dynamic_cast<DSTComboBox* >(GetControl(IDC_CMB_TRANSACTION) );
   if( pCmb )
   {
      int i = pCmb->GetCurSel();
      dstrValue = *reinterpret_cast< DString * >( pCmb->GetItemData( i )  );
    
      getParent()->setField(this,IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
			ifds::TradesTransType,dstrValue,true);

		pCmb->Enable(false);


   }
}
//*************************************************************************
void ForeignContentWorksheetDlg::ConnectHypoControls(bool bConnected)
{
   GetControl(IDC_DTP_TRADE_DATE)->ConnectToData(bConnected);
   GetControl(IDC_EDT_FUND_NUMBER)->ConnectToData(bConnected);
   GetControl(IDC_EDT_FUND)->ConnectToData(bConnected);
   GetControl(IDC_EDT_CLASS)->ConnectToData(bConnected);
   GetControl(IDC_EDT_TO_FUND_NUMBER)->ConnectToData(bConnected);
   GetControl(IDC_EDT_TO_FUND)->ConnectToData(bConnected);
   GetControl(IDC_EDT_TO_CLASS)->ConnectToData(bConnected);
   GetControl(IDC_TXT_FUND_DESCRIPTION)->ConnectToData(bConnected);
   GetControl(IDC_TXT_TO_FUND_DESCRIPTION)->ConnectToData(bConnected);
   GetControl(IDC_EDT_AMOUNT)->ConnectToData(bConnected);
   GetControl(IDC_TXT_AMOUNT_TYPE_DOLLAR)->ConnectToData(bConnected);

}

//******************************************************************************
void ForeignContentWorksheetDlg::EnableHypoControls(bool bEnable)
{
   GetControl(IDC_DTP_TRADE_DATE)->Enable(bEnable);
   GetControl(IDC_EDT_FUND_NUMBER)->Enable(bEnable);
   GetControl(IDC_EDT_FUND)->Enable(bEnable);
   GetControl(IDC_EDT_CLASS)->Enable(bEnable);
   GetControl(IDC_EDT_TO_FUND_NUMBER)->Enable(bEnable);
   GetControl(IDC_EDT_TO_FUND)->Enable(bEnable);
   GetControl(IDC_EDT_TO_CLASS)->Enable(bEnable);
  // GetControl(IDC_TXT_FUND_DESCRIPTION)->Enable(bEnable);
  // GetControl(IDC_TXT_TO_FUND_DESCRIPTION)->Enable(bEnable);
   GetControl(IDC_EDT_AMOUNT)->Enable(bEnable);
   GetControl(IDC_TXT_AMOUNT_TYPE_DOLLAR)->Enable(bEnable);

}
//*****************************************************************************
void ForeignContentWorksheetDlg::ConnectACBControls(bool bConnected)
{

   GetControl(IDC_TXT_RESULT_BEFORE_DOMESTIC1)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_BEFORE_DOMESTIC2)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_AFTER_DOMESTIC1)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_AFTER_DOMESTIC2)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_BEFORE_FC1)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_BEFORE_FC2)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_AFTER_FC1)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_AFTER_FC2)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_BEFORE_TOTAL1)->ConnectToData(bConnected);
  // GetControl(IDC_TXT_RESULT_BEFORE_TOTAL2)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_AFTER_TOTAL1)->ConnectToData(bConnected);
  // GetControl(IDC_TXT_RESULT_AFTER_TOTAL2)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_BEFORE_FC_ALLOWED1)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_BEFORE_FC_ALLOWED2)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_AFTER_FC_ALLOWED1)->ConnectToData(bConnected);
   GetControl(IDC_TXT_RESULT_AFTER_FC_ALLOWED2)->ConnectToData(bConnected);
   GetControl(IDC_TXT_NAV_RESULTS)->ConnectToData(bConnected);
}

//************************************************************************************
void ForeignContentWorksheetDlg::displayLabelByTransType( )
{
	DString dstrTransType;
	getParent()->getField(this,IFASTBP_PROC::FOREIGN_CONTENT_TRADE, 
               ifds::TradesTransType, dstrTransType,false);

	dstrTransType.strip();
	bool bDispFund = dstrTransType == TRADETYPE::PURCHASE || 
							dstrTransType == TRADETYPE::REDEMPTION ;

	UINT nShowFund = bDispFund? SW_SHOW:SW_HIDE;
	UINT nShowFromFund = bDispFund?SW_HIDE:SW_SHOW;
	GetDlgItem(IDC_TXT_FROM_FUND)->ShowWindow(nShowFromFund);
	GetDlgItem(IDC_TXT_FUND)->ShowWindow(nShowFund);

}

//*************************************************************************************
void ForeignContentWorksheetDlg::OnCancel()
{
	  Exit( IDOK );

}              
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/ForeignContentWorksheetDlg.cpp-arc  $
// 
//    Rev 1.8   Sep 15 2005 15:12:22   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.7   Jan 26 2005 17:05:36   porteanm
// PTS 10035000 - Warning promotion.
// 
//    Rev 1.6   May 27 2004 17:17:04   YINGBAOL
// PET985: display tooltip message and pass account number to Fund Class Dialog.
// 
// 
//    Rev 1.5   May 26 2004 18:17:46   YINGBAOL
// PET985:fix click "X" button different from "Close" and disable search criteria part after user clicks "Calculate" button
// 
//    Rev 1.4   May 26 2004 10:10:48   YINGBAOL
// PET985:layout changes
// 
//    Rev 1.3   May 25 2004 10:08:36   YINGBAOL
// PET985:Implement FundName etc...
// 
//    Rev 1.2   May 19 2004 17:43:06   YINGBAOL
// PET985:make hypo work
// 
//    Rev 1.1   Apr 26 2004 13:31:50   VADEANUM
// PET985 FN01 - Foreign Content - work in progress.
// 
//    Rev 1.0   Apr 21 2004 15:35:38   VADEANUM
// Initial revision.
//
