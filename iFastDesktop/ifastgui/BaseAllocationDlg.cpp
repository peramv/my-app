// BaseAllocationDlg.cpp : implementation file
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial .,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial 
//
//******************************************************************************
//
// ^FILE   :BaseAllocationDlg.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : May 26, 2003
//
// ^CLASS    : BaseAllocationDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "BaseAllocationDlg.h"
#include <ifastbp\FromToAllocationProcessIncludes.h>
#include <uibase\dstcombobox.h>
#include <uibase\dstedit.h>
#include <uibase\dstcfuncs.h>
#include <uibase\dstlistctrl.h>
#include <ifastdataimpl\dse_dstc0068_vw.hpp>
#include <ifastbp\FundClassProcessIncludes.h>
#include "ifastbp\allocationsprocessincludes.h"
#include <ifastcbo\dstcommonfunction.hpp>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ALLOCATIONS;
namespace
{  
   const I_CHAR *	const CLASSNAME             = I_( "BaseAllocationDialog" );
   const I_CHAR *	const LV_FROM_ALLOC         = I_( "FromFundAllocList" );
   const I_CHAR *	const YES						 = I_( "Y" );
   const I_CHAR *	const NO							 = I_( "N" );
   const I_CHAR * const FUND_CODE				 = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE				 = I_( "ClassCode" );
   const I_CHAR * const FUNDNUMBER				 = I_( "FundNumber" );

}

//---------------------------------------------------------------------
namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
} 
//---------------------------------------------------------------------
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_ALLOC_INFO;
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_INFO;

}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId DelPerm;
    extern CLASS_IMPORT const BFTextFieldId ModPerm;
    extern CLASS_IMPORT const BFTextFieldId AddPerm;	
}


BEGIN_MESSAGE_MAP(BaseAllocationDlg, BaseMainDlg)
   //{{AFX_MSG_MAP(BaseAllocationDlg)
	ON_BN_CLICKED(IDC_BTN_DEF_ALLOC, OnBtnDefAlloc)
	ON_BN_CLICKED(IDC_BTN_RESET_FROM, OnBtnResetFrom)
	ON_BN_CLICKED(IDC_BTN_ADD_FROM, OnBtnAddFromAlloc)
	ON_BN_CLICKED(IDC_BTN_DEL_FROM, OnBtnDelFromAlloc)
	ON_BN_CLICKED(IDC_CHK_SET_AS_DEF_FROM, OnReplaceAsDefaultFromAlloc)
	ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassDlg )	

	//ON_MESSAGE( UM_OPENBROKERADDRESSDLG, OpenBrokerAddressDlg )dress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//************************************************************************
void BaseAllocationDlg::OnBtnDefAlloc()
{

		DString strAcctNum,strTransType;
		getParent()->getField(this,IFASTBP_PROC::MFACOUNT,ifds::AccountNum,strAcctNum,false );
		strAcctNum.strip();
		
		getParent()->getField(this,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,ifds::TransType,strTransType,false );
		strTransType.strip();

      setParameter( ALLOCATIONSPROC::ACCOUNT_NUM, strAcctNum );
      setParameter( ALLOCATIONSPROC::ALLOCATION_TYPE, 
                    ALLOCATIONSPROC::SHAREHOLDER_DEFAULT );
      setParameter( ALLOCATIONSPROC::TRANS_TYPE, strTransType );
      setParameter(I_("Caller"), I_("Default"));

		SetMessageStatusBar( TXT_LOAD_DEFAULT_ALLOCATION );
	   invokeCommand( getParent(), CMD_BPROC_ALLOCATIONS, PROC_NO_TYPE, 
									 true, NULL );
		SetMessageStatusBar( NULL_STRING );
}
//**************************************************************************
void BaseAllocationDlg::OnBtnResetFrom()
{

   TRACE_METHOD( CLASSNAME, I_( "OnBtnReset" ) );
   ResetListItem( IDC_LV_ALLOC_FROM );
   GetList( IDC_LV_ALLOC_FROM )->SetFocus();  
}
//**************************************************************************
void BaseAllocationDlg::OnBtnAddFromAlloc()
{

   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddFromAlloc" ) );
   AddToListControl( IDC_LV_ALLOC_FROM );
   GetList( IDC_LV_ALLOC_FROM )->SetFocus();
}

//**************************************************************************
void BaseAllocationDlg::OnBtnDelFromAlloc()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelFromAlloc" ) );
   DeleteFromListControl( IDC_LV_ALLOC_FROM );
   GetList( IDC_LV_ALLOC_FROM )->SetFocus();

}
//*********************************************************************
void BaseAllocationDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BaseAllocationDlg)
   DDX_Check(pDX, IDC_CHK_SET_AS_DEF_FROM, _bReplaceAsDefault);

	//IDC_CHK_SET_AS_DEF_FROM
	//}}AFX_DATA_MAP
	
}

//-------------------------------------------------------------------

BaseAllocationDlg::BaseAllocationDlg( UINT nIDD,CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( nIDD?nIDD:IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   _bReplaceAsDefault = false;
}

//------------------------------------------------------------------------------------
SEVERITY BaseAllocationDlg::doInit()
{
 //  getParameter( NASULIT::CREATING_ACCOUNT, m_strNASUFlag );
   getParent()->getParameter( FTALLOCATION::CURRENT_KEY, _curRRIFInfoKey );
   return NO_CONDITION;
}
//****************************************************************************************
void BaseAllocationDlg::addControls()
{
	TRACE_METHOD( CLASSNAME, I_("addControls"));	

	AddControl(CTRL_COMBO,IDC_CMB_AMT_TYPE,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,
		ifds::AmountType,CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_NOT_UPDATABLE );

	AddControl(CTRL_STATIC,IDC_TXT_AMT,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,
		ifds::RRIFAmount,CTRLFLAG_NOT_UPDATABLE);


	AddControl(CTRL_DATE,IDC_DT_EFFECTIVEDATE,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,
		ifds::EffectiveFrom,CTRLFLAG_NOT_UPDATABLE);

	AddControl(CTRL_COMBO,IDC_CMB_SETTLE_CURRENCY,IFASTBP_PROC::MFACOUNT,
		ifds::Currency,CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_NOT_UPDATABLE );


   AddListControl( CLASSNAME, IDC_LV_ALLOC_FROM, LV_FROM_ALLOC, ifds::LV_FundAllocation, 
                   IFASTBP_PROC::RRIF_FROM_ALLOC_LIST, 0, true );

	AddControl(CTRL_STATIC,IDC_TXT_ALLOC_TYPE_FROM,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,
		ifds::TransType,CTRLFLAG_NOT_UPDATABLE,IDC_LV_ALLOC_FROM );

	AddControl(CTRL_EDIT,IDC_EDT_FUND_NUM_FROM,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,
		ifds::ToFundNumber,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_ALLOC_FROM );

	AddControl(CTRL_EDIT,IDC_EDT_FUND_FROM,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,
		ifds::FundCode,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_ALLOC_FROM );

	AddControl(CTRL_EDIT,IDC_EDT_CLASS_FROM,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,
		ifds::ClassCode,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_ALLOC_FROM );
	AddControl(CTRL_EDIT,IDC_EDT_AMT_FROM,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,
		ifds::AllocAmount,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_ALLOC_FROM );
	AddControl(CTRL_EDIT,IDC_EDT_PERCENT_FROM,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,
		ifds::AllocPercentage,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_ALLOC_FROM );
	AddControl(CTRL_STATIC,IDC_TXT_AMT_TOTAL_FROM,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,
		ifds::TotAmount,CTRLFLAG_NOT_UPDATABLE,IDC_LV_ALLOC_FROM );
	AddControl(CTRL_STATIC,IDC_TXT_PERCET_TOTAL_FROM,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,
		ifds::TotPercentage,CTRLFLAG_NOT_UPDATABLE,IDC_LV_ALLOC_FROM );

	AddControl(CTRL_STATIC,IDC_TXT_ACCT_FROM,IFASTBP_PROC::MFACOUNT,
		ifds::AccountNum,CTRLFLAG_NOT_UPDATABLE );

    dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_AMT_FROM))->SetAllowedChars(I_("0123456789."));
	DString dstrPercentageMask = DSTCommonFunctions::getMask( ifds::Percentage );
	int iDecimalPointPos = dstrPercentageMask.find( I_( "." ) );
	DSTEdit *edtPercentDet = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_PERCENT_FROM ) );
	edtPercentDet->SetMaxCharNum( dstrPercentageMask.length() );//probably redundant
	edtPercentDet->AllowNonnegativeDecimalNumbers( iDecimalPointPos, 
                                                  dstrPercentageMask.length() - iDecimalPointPos - 2 );
	edtPercentDet->SetAllowedChars(I_("0123456789."));

	ConnectControlToData(IDC_CMB_AMT_TYPE,true );
 	ConnectControlToData(IDC_TXT_AMT,true );
	ConnectControlToData(IDC_DT_EFFECTIVEDATE,true );
	ConnectControlToData(IDC_CMB_SETTLE_CURRENCY,true );
	ConnectControlToData(IDC_TXT_ACCT_FROM,true );


	LoadControl(IDC_CMB_AMT_TYPE);
	LoadControl(IDC_TXT_AMT);
	LoadControl(IDC_DT_EFFECTIVEDATE);
	LoadControl(IDC_CMB_SETTLE_CURRENCY);
	LoadControl(IDC_TXT_ACCT_FROM);
	LoadListControl(IDC_LV_ALLOC_FROM);
	DString dstrRepDef;
	getParent()->getField(this,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,ifds::SetAsDefault,
		dstrRepDef,false);
	dstrRepDef.strip();
	_bReplaceAsDefault = dstrRepDef == YES? true:false;
	UpdateData(false);


}
//------------------------------------------------------------------------------------
void BaseAllocationDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog"));

	SetUserAccesFunctionCode(UAF::RIF_LIF_LRIF_INFO);

   addBtnAddForPermissionCheck(IDC_BTN_ADD_FROM, IDC_LV_ALLOC_FROM );
   addBtnDeleteForPermissionCheck(IDC_BTN_DEL_FROM, IDC_LV_ALLOC_FROM);
   addBtnAddForPermissionCheck(IDC_BTN_RESET_FROM, IDC_LV_ALLOC_FROM);
	getParent()->setCurrentListItem(this,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,_curRRIFInfoKey );
	(CWnd* )(GetDlgItem(IDC_CHK_SET_AS_DEF_FROM) )->EnableWindow( bIsGoodStatus() && hasUpdatePermission(UAF::RIF_LIF_LRIF_INFO ));
	addControls();    
}



//**************************************************************************************
BOOL BaseAllocationDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();
	return TRUE;
}

//----------------------------------------------------------------------------------
void BaseAllocationDlg::setDlgTitle( )
{
	CString  cstrAccount;
	DString  dstrTitle;
	cstrAccount.LoadString(TXT_ACCOUNT_NBR);	
	
//	dstrTitle = I_(":") +(LPCTSTR)cstrAccount + I_(":");

	SetCaption(dstrTitle);
}





//*******************************************************************************
bool BaseAllocationDlg::PreOk()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "PreOk" ) );

	return true;
}


//*********************************************************************************
bool  BaseAllocationDlg::doRefresh(
      GenericInterface * /*rpGICaller*/, 
      const I_CHAR * //*szOriginalCommand
      )
{  
//   getParent()->getParameter( NASULIT::CREATING_ACCOUNT, m_strNASUFlag );
   return true;
}
/*********************************************************************************
void	BaseAllocationDlg::DoListItemChanged(
      UINT ListControlID,
      const DString &strKey, 
		bool bIsNewItem , 
      bool bIsDummyItem
      )
{

}
*/
//*********************************************************************************************
bool BaseAllocationDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, 
															 DString &strOut)
{
	return false;
}
//**********************************************************************************************
bool BaseAllocationDlg::GetDataForControl(UINT controlID,  DString &strValueOut, 
														bool bFormatted, int index   ) const
{  
   return false;
}


//*******************************************************************************
void BaseAllocationDlg::ControlUpdated( UINT controlID, const DString &strValue )
{

	switch (controlID)
	{
		case IDC_EDT_AMT_FROM:	
		case IDC_EDT_PERCENT_FROM:
			{	
				LoadControl(IDC_TXT_AMT_TOTAL_FROM);
				LoadControl(IDC_TXT_PERCET_TOTAL_FROM);
			}	
			break;
   
      case IDC_EDT_FUND_NUM_FROM:
      case IDC_EDT_FUND_FROM:
      case IDC_EDT_CLASS_FROM:
         {
            LoadControl(controlID);
         }
         break;
	}

}
//***********************************************************************************

BOOL BaseAllocationDlg::PreTranslateMessage(MSG* pMsg) 
{

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_FUND_NUM_FROM ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND_NUM_FROM;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FUND_FROM ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND_FROM;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_CLASS_FROM ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_CLASS_FROM;
      }
		
	}
   return (BaseMainDlg::PreTranslateMessage( pMsg ) );
}

//************************************************************************************
LRESULT BaseAllocationDlg::OpenFundClassDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;  

  	  bool bFromFund = m_uiClassCodeDialogItem == IDC_EDT_FUND_FROM || 
							 m_uiClassCodeDialogItem == IDC_EDT_CLASS_FROM ||
							 m_uiClassCodeDialogItem ==	IDC_EDT_FUND_NUM_FROM;


	  bool bEnable = GetControl(m_uiClassCodeDialogItem )->IsEnabled();
	  if( !bEnable ) return false;

 
      switch( m_uiClassCodeDialogItem )
      {
        
		 case IDC_EDT_FUND_FROM:
            {
               CString cstrFundCode;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundCode );
               DString dstrFundCode = cstrFundCode;
               setParameter( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;

         case IDC_EDT_CLASS_FROM:
            {
               CString cstrFundClass;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundClass );
               DString dstrFundClass = cstrFundClass;
               setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::CLASS_CODE, dstrFundClass );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;
      
			case IDC_EDT_FUND_NUM_FROM:
            {
               CString cstrFundNumber;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundNumber );
               DString dstrFundNumber = cstrFundNumber;
               setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, dstrFundNumber );
            }
            break;
        
      }
		DString dstrAcctNum;
		getParent()->getField(this,IFASTBP_PROC::MFACOUNT,ifds::AccountNum,dstrAcctNum,false );
		dstrAcctNum.strip();

      setParameter( FUNDCLASSLIST::ACCT_NUM, dstrAcctNum );
      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;
               getParameter ( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               getParameter ( FUNDCLASSLIST::CLASS_CODE, dstrClassCode );
               getParameter ( FUNDCLASSLIST::FUND_NUMBER, dstrFundNumber );
					if (bFromFund)  //from fund
					{
						getParent()->setField (this,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST, ifds::FundCode, dstrFundCode );
						getParent()->setField (this,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST, ifds::ClassCode, dstrClassCode );
  						getParent()->setField (this,IFASTBP_PROC::RRIF_FROM_ALLOC_LIST, ifds::ToFundNumber, dstrFundNumber );
						LoadControl(IDC_EDT_FUND_FROM );
						LoadControl(IDC_EDT_CLASS_FROM );
						LoadControl(IDC_EDT_FUND_NUM_FROM );
					}
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


//*************************************************************************************

void BaseAllocationDlg::OnReplaceAsDefaultFromAlloc() 
{
   _bReplaceAsDefault = !_bReplaceAsDefault;
   DString dstrRepDefault = ( _bReplaceAsDefault ) ? YES : NO; 
   getParent()->setField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::SetAsDefault, 
                            dstrRepDefault, false);
	UpdateData(false);
}
//*************************************************************************************
bool BaseAllocationDlg::doDisablePermCheckButton(UINT nID)
{
	return !bIsGoodStatus();  // disable all button if it is bad
}
//*************************************************************************************
bool BaseAllocationDlg::bIsGoodStatus()
{
	DString dstrStatus;
   getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::GoodBad, dstrStatus, false);
	dstrStatus.strip();
	return dstrStatus.strip() == YES;  // 
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BaseAllocationDlg.cpp-arc  $
// 
//    Rev 1.5   Jan 14 2009 17:15:56   wongsakw
// IN1550993 Invalid warning message when fund entered in lower case for LIF allocation
// 
//    Rev 1.4   Sep 15 2005 15:10:44   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   Mar 02 2005 18:00:14   porteanm
// PET 1171 FN01 - cleanup, renamed WM_LAUNCH_BROKER_SELECT with the one declared it in win32uibase, as standard. It shouldn't have any impact, it was commented out anyway.
// 
//    Rev 1.2   Sep 03 2003 17:16:06   popescu
// fixes regarding calling the allocation screen, seems that more places that originally thought are using the allocation screen
// 
//    Rev 1.1   Jul 04 2003 10:26:34   YINGBAOL
// Percentage and amount have to be numeric
// 
//    Rev 1.0   Jun 09 2003 11:19:14   YINGBAOL
// Initial revision.
//

 */
