// FromToAllocationDlg.cpp : implementation file
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
// ^FILE   :FromToAllocationDlg.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : May 26, 2003
//
// ^CLASS    : FromToAllocationDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "FromToAllocationDlg.h"
#include "BaseAllocationDlg.h"
#include <uibase\dstcombobox.h>
#include <uibase\dstedit.h>
#include <uibase\dstcfuncs.h>
#include <uibase\dstlistctrl.h>
#include <ifastdataimpl\dse_dstc0068_vw.hpp>
#include <ifastbp\FromToAllocationProcessIncludes.h>
#include <ifastbp\FundClassProcessIncludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FROM_TO_ALLOCATION;
#include <bfproc\concretedialogcreator.hpp>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


struct FromToDialogCreator
{
	GenericInterface* operator()( GenericInterfaceContainer* pGIC, 
                                 GenericInterface* pGIParent,
                                 const Command& rCommand ) const { 
 
		DString dstrPayType,dstrKey;

		pGIParent->getParameter( FTALLOCATION::CURRENT_KEY, dstrKey );
		pGIParent->setCurrentListItem(NULL,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,dstrKey );
		pGIParent->getField(NULL,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,ifds::RIFPayType,dstrPayType,false);
		dstrPayType.strip().upperCase();
		if(dstrPayType == I_("T") )
		{
			return ( new FromToAllocationDlg( NULL,pGIC,pGIParent,rCommand ) );		
		}
		else
		{
			return ( new BaseAllocationDlg( 0,NULL,pGIC,pGIParent,rCommand ) );				
		}
      return( NULL );
   }
};

static ConcreteDialogCreator< FromToAllocationDlg, FromToDialogCreator > dlgCreator( CMD_GUI_FROM_TO_ALLOCATION );

namespace
{  
   const I_CHAR *CLASSNAME             = I_( "FromToAllocationDialog" );
   const I_CHAR *	const YES						 = I_( "Y" );
   const I_CHAR *	const NO							 = I_( "N" );
   const I_CHAR * const FUND_CODE				 = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE				 = I_( "ClassCode" );
   const I_CHAR * const FUNDNUMBER				 = I_( "FundNumber" );
   const I_CHAR *	const LV_TO_ALLOC         = I_( "ToFundAllocList" );

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
}
namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId DelPerm;
    extern CLASS_IMPORT const BFTextFieldId ModPerm;
    extern CLASS_IMPORT const BFTextFieldId AddPerm;	
}
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;


BEGIN_MESSAGE_MAP(FromToAllocationDlg, BaseAllocationDlg)
   //{{AFX_MSG_MAP(FromToAllocationDlg)
//	ON_BN_CLICKED(IDC_BTN_DEF_ALLOC, OnBtnDefAlloc)
	ON_BN_CLICKED(IDC_BTN_RESET_TO, OnBtnResetTo)
	ON_BN_CLICKED(IDC_BTN_ADD_TO, OnBtnAddToAlloc)
	ON_BN_CLICKED(IDC_BTN_DEL_TO, OnBtnDelToAlloc)
	ON_BN_CLICKED(IDC_CHK_SET_AS_DEF_TO, OnReplaceAsDefaultToAlloc)
	ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassDlg )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//************************************************************************
void FromToAllocationDlg::OnBtnResetTo() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnResetTo" ) );
   ResetListItem( IDC_LV_ALLOC_TO );
   GetList( IDC_LV_ALLOC_TO )->SetFocus();  
}

//*******************************************************************************
void FromToAllocationDlg::OnBtnDelToAlloc() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelToAlloc" ) );
   DeleteFromListControl( IDC_LV_ALLOC_TO );
   GetList( IDC_LV_ALLOC_TO )->SetFocus();
}
//*********************************************************************************
void FromToAllocationDlg::OnBtnAddToAlloc() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddFromAlloc" ) );
   AddToListControl( IDC_LV_ALLOC_TO );
   GetList( IDC_LV_ALLOC_TO )->SetFocus();
}
//*********************************************************************
void FromToAllocationDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseAllocationDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddressBookDlg)
   DDX_Check(pDX, IDC_CHK_SET_AS_DEF_TO, _bReplaceAsDefault);

	//IDC_CHK_SET_AS_DEF_FROM
	//}}AFX_DATA_MAP
	
}

//-------------------------------------------------------------------
// Construction/Destruction   LVAddressMailingRow
//--------------------------------------------------------------------

FromToAllocationDlg::FromToAllocationDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseAllocationDlg( FromToAllocationDlg::IDD, pParent, pGIC, pGIParent, rCommand ),
_bReplaceAsDefault( false ),
m_uiClassCodeDialogItem(0)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

}

//------------------------------------------------------------------------------------
SEVERITY FromToAllocationDlg::doInit()
{
   BaseAllocationDlg::doInit();
   return NO_CONDITION;
}
//****************************************************************************************
void FromToAllocationDlg::addControls()
{
	TRACE_METHOD( CLASSNAME, I_("addControls"));	
	BaseAllocationDlg::addControls();
   AddListControl( CLASSNAME, IDC_LV_ALLOC_TO, LV_TO_ALLOC, ifds::LV_FundAllocation, 
                   IFASTBP_PROC::RRIF_TO_ALLOC_LIST, 0, true );
	AddControl(CTRL_EDIT,IDC_EDT_FUND_NUM_TO,IFASTBP_PROC::RRIF_TO_ALLOC_LIST,
		ifds::ToFundNumber,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_ALLOC_TO );

	AddControl(CTRL_EDIT,IDC_EDT_FUND_TO,IFASTBP_PROC::RRIF_TO_ALLOC_LIST,
		ifds::FundCode,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_ALLOC_TO );

	AddControl(CTRL_EDIT,IDC_EDT_CLASS_TO,IFASTBP_PROC::RRIF_TO_ALLOC_LIST,
		ifds::ClassCode,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_ALLOC_TO );
	AddControl(CTRL_EDIT,IDC_EDT_AMT_TO,IFASTBP_PROC::RRIF_TO_ALLOC_LIST,
		ifds::AllocAmount,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_ALLOC_TO );
	AddControl(CTRL_EDIT,IDC_EDT_PERCENT_TO,IFASTBP_PROC::RRIF_TO_ALLOC_LIST,
		ifds::AllocPercentage,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_ALLOC_TO );
	AddControl(CTRL_STATIC,IDC_TXT_AMT_TOTAL_TO,IFASTBP_PROC::RRIF_TO_ALLOC_LIST,
		ifds::TotAmount,CTRLFLAG_NOT_UPDATABLE,IDC_LV_ALLOC_TO );
	AddControl(CTRL_STATIC,IDC_TXT_PERCENT_TOTAL_TO,IFASTBP_PROC::RRIF_TO_ALLOC_LIST,
		ifds::TotPercentage,CTRLFLAG_NOT_UPDATABLE,IDC_LV_ALLOC_TO );
	AddControl(CTRL_STATIC,IDC_TXT_ALLOC_TYPE_TO,IFASTBP_PROC::RRIF_TO_ALLOC_LIST,
		ifds::TransType,CTRLFLAG_NOT_UPDATABLE,IDC_LV_ALLOC_TO );

	AddControl(CTRL_STATIC,IDC_TXT_ACCT_TO,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,
		ifds::AccountTo,CTRLFLAG_NOT_UPDATABLE );
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_AMT_TO))->SetAllowedChars(I_("0123456789."));
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_PERCENT_TO))->SetAllowedChars(I_("0123456789."));

	ConnectControlToData(IDC_TXT_ACCT_TO,true );
	LoadControl(IDC_TXT_ACCT_TO);
	LoadListControl(IDC_LV_ALLOC_TO);
	DString dstrRepDef;
	getParent()->getField(this,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,ifds::SetRTAsDefault,
		dstrRepDef,false);
	dstrRepDef.strip();
	_bReplaceAsDefault = dstrRepDef == YES? true:false;
	UpdateData(false);
}
//------------------------------------------------------------------------------------
void FromToAllocationDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog"));
/*
   if (_InquiryOnly.strip() == YES)
      SetUserAccesFunctionCode(NULL);
   else
      SetUserAccesFunctionCode(UAF::ADDRESS_BOOK);
*/
   addBtnAddForPermissionCheck(IDC_BTN_ADD_TO, IDC_LV_ALLOC_TO);
   addBtnDeleteForPermissionCheck(IDC_BTN_DEL_TO, IDC_LV_ALLOC_TO);
   addBtnAddForPermissionCheck(IDC_BTN_RESET_TO, IDC_LV_ALLOC_TO);
	(CWnd* )(GetDlgItem(IDC_CHK_SET_AS_DEF_TO) )->EnableWindow( bIsGoodStatus() );
	BaseAllocationDlg::OnPostInitDialog();
}

//----------------------------------------------------------------------------------

void FromToAllocationDlg::OnReplaceAsDefaultToAlloc() 
{

   _bReplaceAsDefault = !_bReplaceAsDefault;
   DString dstrRepDefault = ( _bReplaceAsDefault ) ? YES : NO; 
   getParent()->setField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::SetRTAsDefault, 
                            dstrRepDefault, false);
	UpdateData(false);
}

//----------------------------------------------------------------------------------
void FromToAllocationDlg::setDlgTitle()
{
	CString  cstrAccount;
	DString  dstrTitle;
	cstrAccount.LoadString(TXT_ACCOUNT_NBR);	
/*	m_dstrShrNum.stripLeading('0');

	dstrTitle = I_(":")+m_dstrShrNum +SPACE_STRING +(LPCTSTR)cstrAccount + I_(":")+ m_dstrAccountNum + SPACE_STRING;
*/
	SetCaption(dstrTitle);
}





//*******************************************************************************
bool FromToAllocationDlg::PreOk()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "PreOk" ) );

	return true;
}


//*********************************************************************************
bool  FromToAllocationDlg::doRefresh(
      GenericInterface * /*rpGICaller*/, 
      const I_CHAR * //*szOriginalCommand
      )
{  
//   getParent()->getParameter( NASULIT::CREATING_ACCOUNT, m_strNASUFlag );
   return true;
}



/*********************************************************************************
void	FromToAllocationDlg::DoListItemChanged(
      UINT ListControlID,
      const DString &strKey, 
		bool bIsNewItem , 
      bool bIsDummyItem
      )
{




}
*/
//*********************************************************************************************
bool FromToAllocationDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, 
															 DString &strOut)
{
	return false;
}
//**********************************************************************************************
bool FromToAllocationDlg::GetDataForControl(UINT controlID,  DString &strValueOut, 
														bool bFormatted, int index   ) const
{  
   return false;
}


//*******************************************************************************
void FromToAllocationDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
	BaseAllocationDlg::ControlUpdated( controlID, strValue );

	switch (controlID)
	{
		case IDC_EDT_AMT_TO:	
		case IDC_EDT_PERCENT_TO:
			{	
				LoadControl(IDC_TXT_AMT_TOTAL_TO);
				LoadControl(IDC_TXT_PERCENT_TOTAL_TO);
			}	
			break;
		
	   case IDC_EDT_FUND_NUM_TO:
	   case IDC_EDT_FUND_TO:
	   case IDC_EDT_CLASS_TO:
	      {
	         LoadControl(controlID);
	      }
	      break;
	}
}
//***********************************************************************************

BOOL FromToAllocationDlg::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_FUND_NUM_TO ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND_NUM_TO;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FUND_TO ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND_TO;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_CLASS_TO ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_CLASS_TO;
      }
		else {
			m_uiClassCodeDialogItem = 0;
		}
		
	}
   return(BaseAllocationDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************************
LRESULT FromToAllocationDlg::OpenFundClassDlg( WPARAM wp, LPARAM lp )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );
	try
	{
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;  

  	  bool bToFund = m_uiClassCodeDialogItem == IDC_EDT_FUND_TO || 
							 m_uiClassCodeDialogItem == IDC_EDT_CLASS_TO ||
							 m_uiClassCodeDialogItem ==	IDC_EDT_FUND_NUM_TO;

	  if( !bToFund )
	  {
		  return BaseAllocationDlg::OpenFundClassDlg( wp,lp );		  
	  }
	  bool bEnable = GetControl(m_uiClassCodeDialogItem )->IsEnabled();
	  if( !bEnable ) return false;

 
      switch( m_uiClassCodeDialogItem )
      {
        
		 case IDC_EDT_FUND_TO:
            {
               CString cstrFundCode;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundCode );
               DString dstrFundCode = cstrFundCode;
               setParameter( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;

         case IDC_EDT_CLASS_TO:
            {
               CString cstrFundClass;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundClass );
               DString dstrFundClass = cstrFundClass;
               setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::CLASS_CODE, dstrFundClass );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;
      
			case IDC_EDT_FUND_NUM_TO:
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
		getParent()->getField(this,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,ifds::AccountTo,dstrAcctNum,false );
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
					if (bToFund)  //from fund
					{
						getParent()->setField (this,IFASTBP_PROC::RRIF_TO_ALLOC_LIST, ifds::FundCode, dstrFundCode );
						getParent()->setField (this,IFASTBP_PROC::RRIF_TO_ALLOC_LIST, ifds::ClassCode, dstrClassCode );
  						getParent()->setField (this,IFASTBP_PROC::RRIF_TO_ALLOC_LIST, ifds::ToFundNumber, dstrFundNumber );
						LoadControl(IDC_EDT_FUND_TO );
						LoadControl(IDC_EDT_CLASS_TO );
						LoadControl(IDC_EDT_FUND_NUM_TO );
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


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FromToAllocationDlg.cpp-arc  $
// 
//    Rev 1.4   Jan 14 2009 17:16:26   wongsakw
// IN1550993 Invalid warning message when fund entered in lower case for LIF allocation
// 
//    Rev 1.3   Jul 04 2003 10:27:18   YINGBAOL
// Percentage and Amount have to numeric
// 
//    Rev 1.2   Jun 24 2003 09:41:32   YINGBAOL
// add OnReplaceAsDefaultToAlloc
// 
//    Rev 1.1   Jun 13 2003 16:20:30   YINGBAOL
// fix search for FundClass
// 
//    Rev 1.0   Jun 09 2003 11:18:18   YINGBAOL
// Initial revision.
//

 */
