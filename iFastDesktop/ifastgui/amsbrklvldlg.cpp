//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AMSBrkLvlDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : AMSBrkLvlDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the AMSAcctLvl dialog
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <uibase\dstedit.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstcfuncs.h>

#include <uibase\dstcombobox.h>
#include <uibase\dstbutton.h>
#include <ifastcbo\dstcworksession.hpp>
#include "AMSBrkLvlDlg.h"
#include <ifastbp\amsmstprocessincludes.h>
#include <ifastbp\Brokerprocessincludes.h>
#include <ifastbp\BrokerAMSprocessincludes.h>
#include <bfproc\abstractprocess.hpp>
#include <assert.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_AMSBRKLVL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMS_GLOBAL;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AMSBrkLvlDlg > dlgCreator( CMD_GUI_AMSBRKLVL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME  = I_( "AMSBrkLvlDlg" );
   const I_CHAR * const YES        = I_( "Y" );
   const I_CHAR * const NO         = I_( "N" );
   const I_CHAR * const GOOD       = I_("Good");
   const I_CHAR * const BAD        = I_("Bad");
   const I_CHAR * CODE_AMSTYPE_REBALANCING = I_("RB");
}

namespace PARAMETER
{
   const I_CHAR * const FUND_CODE      = I_( "FundCode" );    // Used for F4-Fund Search Dialog
   const I_CHAR * const CLASS_CODE     = I_( "ClassCode" );   // Used for F4-Fund Search Dialog
   const I_CHAR * const AMS_CODE       = I_( "AMSCode" );     // Used for passing AMSCode to AMSCodeSearch
   const I_CHAR* const BROKER_CODE     = I_( "BrokerCode" );
   const I_CHAR* const BROKER_NAME     = I_( "BrokerName" );
   const I_CHAR * const AMSCODE        = I_( "AMSCODE" );		//AMS mstr using uppercase AMSCODE as parameter
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AMS_DETAILS;
   extern CLASS_IMPORT I_CHAR * const BROKER_AMS_RESTRICT;
}

namespace CND
{
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AMSFundAllocHeading;  // Column Heading field
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFTextFieldId BrokerAMSList;  // Column Heading field
   
}

//******************************************************************************

AMSBrkLvlDlg::AMSBrkLvlDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AMSBrkLvlDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	setItemChange( false );
   //{{AFX_DATA_INIT(AMSBrkLvlDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************

AMSBrkLvlDlg::~AMSBrkLvlDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

void AMSBrkLvlDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AMSBrkLvlDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(AMSBrkLvlDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AMSBrkLvlDlg)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_ADMIN, OnBtnAdmin)
ON_BN_CLICKED( IDC_BTN_MORE,  OnBtnMore )
ON_MESSAGE( UM_OPENAMSCODESEARCH, OpenAMSMstrListDlg )
ON_MESSAGE( UM_OPENBROKERLISTDLG, OpenBrokerListDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AMSBrkLvlDlg message handlers

BOOL AMSBrkLvlDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   DisplayCaption();
  
   GetDlgItem(IDC_BTN_ADMIN)->EnableWindow(false);
   
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void AMSBrkLvlDlg::OnPostInitDialog()
{
   
	TRACE_METHOD( CLASSNAME, I_("addControls") );
    addBtnDeleteForPermissionCheck(IDC_BTN_AMS_DEL, IDC_LST_AMSINFO);
	SetUserAccesFunctionCode(UAF::BROKER_AMS_RESTRICT);
	AddListControl(CLASSNAME, IDC_LV_AMS_CODES, I_("BROKER_AMS_CODES"), ifds::BrokerAMSList, 
		IFASTBP_PROC::BROKERAMS_LIST, 0, true/*, LISTFLAG_NOT_AUTO_ADD */);
    AddListControl(CLASSNAME, IDC_LV_ALLOCATION, I_("AMS_FUND_ALLOC"), 
		ifds::AMSFundAllocHeading, IFASTBP_PROC::AMS_FUND_ALLOC_LIST,IDC_LV_AMS_CODES,true,
		LISTFLAG_NOT_AUTO_ADD );

   // Format Columns - This could be removed if the IFDSListCtrl is used.
   CListCtrl *pDSTListCtrl = GetList( IDC_LV_ALLOCATION );
   if( pDSTListCtrl )
   {
      LVCOLUMN lvcolumn;
      lvcolumn.mask = LVCF_FMT;
      lvcolumn.fmt = LVCFMT_RIGHT;
      BOOL bReturn = pDSTListCtrl->SetColumn( 4, &lvcolumn ); // Percentage field
   }

	AddControl( CTRL_EDIT, IDC_EDT_BRK_SRC, IFASTBP_PROC::BROKERAMSSEARCH, ifds::BrokerCode);	
	AddControl( CTRL_STATIC, IDC_STATIC_BRKNAME, IFASTBP_PROC::BROKERAMSSEARCH, ifds::BrokerName);
	AddControl( CTRL_EDIT, IDC_EDT_AMS_SRC, IFASTBP_PROC::BROKERAMSSEARCH, ifds::AMSCode);
	ConnectControlToData(IDC_EDT_BRK_SRC,        true);
	ConnectControlToData(IDC_STATIC_BRKNAME,     true);
	ConnectControlToData(IDC_EDT_AMS_SRC,        true);

	
    AddControl( CTRL_EDIT, IDC_EDT_AMS, IFASTBP_PROC::BROKERAMS_LIST, ifds::AMSCode, 0, IDC_LV_AMS_CODES);
	AddControl( CTRL_STATIC, IDC_STATIC_AMSNAME, IFASTBP_PROC::BROKERAMS_LIST, ifds::AMSName, 0, IDC_LV_AMS_CODES);
	AddControl( CTRL_DATE, IDC_DTP_DEFF, IFASTBP_PROC::BROKERAMS_LIST, ifds::EffectiveDate, 0, IDC_LV_AMS_CODES);
	AddControl( CTRL_COMBO, IDC_CMB_STATUS, IFASTBP_PROC::BROKERAMS_LIST, ifds::GoodBad, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_AMS_CODES);	

	setUpdateFlag(false);
	SetDefID(IDC_BTN_SEARCH);

	//initial of dialog
	GetDlgItem(IDC_BTN_ADMIN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);		
	GetDlgItem(IDOK)->EnableWindow(false);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(false);
	GetDlgItem(IDC_BTN_DELETE)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MORE)->EnableWindow(false);
	GetDlgItem(IDC_EDT_AMS)->EnableWindow(false);
	GetDlgItem(IDC_DTP_DEFF)->EnableWindow(false);
	GetDlgItem(IDC_CMB_STATUS)->EnableWindow(false);

}

//******************************************************************************
void AMSBrkLvlDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::BROKERAMS_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::BROKERAMS_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl(IDC_LV_AMS_CODES);   
   }
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//******************************************************************************
bool AMSBrkLvlDlg::doRefresh( GenericInterface * rpGICaller, const I_CHAR * szOriginalCommand )
{
   DisplayCaption();
   LoadListControl( IDC_LV_ALLOCATION );
   return(true);
}

//******************************************************************************

void AMSBrkLvlDlg::OnBtnAdd() 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnAdd") );
	
	AddToListControl( IDC_LV_AMS_CODES );
}

//******************************************************************************

void AMSBrkLvlDlg::OnBtnSearch() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSearch" ) );

   CString cstr;
   DString dstr;
   DString brokerCode, brokerName;
   CWaitCursor wait;
   BaseControl* pBControl = dynamic_cast<BaseControl*>(GetFocus());
   if( pBControl )  pBControl->Store();

	DString dstrUpdated;
	getParent()->getField(this,IFASTBP_PROC::BROKERAMSSEARCH,
				BROKE_AMS::HAS_OBJECT_UPDATE,dstrUpdated,false );
   
	bool bSearch = true;
	if(	 dstrUpdated == YES )
	{
		  	if( AfxMessageBox(TXT_WARNING_LOST_CHANGE,MB_YESNO ) == IDNO )
			{
				bSearch = false;
			}
	}
	if( bSearch )
	{
			SEVERITY sev = getParent()->performSearch( this, IFASTBP_PROC::BROKERAMS_LIST, SEARCH_START );
			if( sev  <= WARNING )
			{
					LoadListControl(IDC_LV_AMS_CODES);
					GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
					GetDlgItem(IDC_BTN_ADD)->EnableWindow(true);
					SetDefID(IDOK); 	
			}
			else
			{      
					ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY() );
			}  
   }

}

//******************************************************************************

void AMSBrkLvlDlg::OnBtnAdmin() 
{   
	ShowAdminDates( IFASTBP_PROC::BROKERAMS_LIST );
}
//******************************************************************************

void AMSBrkLvlDlg::OnBtnDelete() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnDelete") );
   DeleteFromListControl( IDC_LV_AMS_CODES );
}

//******************************************************************************

void AMSBrkLvlDlg::OnBtnReset() 
{
   ResetListItem( IDC_LV_AMS_CODES );
//   doRefresh( this, NULL_STRING );
}


//******************************************************************************

BOOL AMSBrkLvlDlg::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
   {
      return(TRUE);
   }

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 )
   {
      if(   GetFocus() == GetDlgItem( IDC_EDT_BRK_SRC )  )
      {
         PostMessage( UM_OPENBROKERLISTDLG );      
      } 
	  else if( GetFocus() == GetDlgItem( IDC_EDT_AMS ) )
      {
         PostMessage( UM_OPENAMSCODESEARCH );
      }
      return( TRUE );
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************************

void AMSBrkLvlDlg::DisplayCaption() 
{
}

//******************************************************************************

bool AMSBrkLvlDlg::GetOverrideItemString(long lSubstituteId, const DString &dstrColumnKey, DString &dstrOut)
{
   return false;
}

//******************************************************************************

LRESULT AMSBrkLvlDlg::OpenBrokerListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

	  DString brokerCode;
      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter( PARAMETER::BROKER_CODE, brokerCode );
			   
               if( !brokerCode.empty() )
               {
						getParent()->setField( this, IFASTBP_PROC::BROKERAMSSEARCH, ifds::BrokerCode, brokerCode );
						LoadControl ( IDC_EDT_BRK_SRC );
						LoadControl ( IDC_STATIC_BRKNAME );
               }
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

LRESULT AMSBrkLvlDlg::OpenAMSMstrListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenAMSCodeListDlg" ) );
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      CString cstrValue;

      DString dstrAMSCode = NULL_STRING;
      DString dstrAMSType = CODE_AMSTYPE_REBALANCING;

      setParameter( AMS_Para::AMS_CODE, dstrAMSCode );
      setParameter( AMS_Para::AMS_TYPE, dstrAMSType );
      setParameter( AMS_Para::FROM_SCR, AMS_Para::AMS_DETAIL );

      eRtn = invokeCommand( getParent(), CMD_BPROC_AMS_GLOBAL, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter ( PARAMETER::AMSCODE, dstrAMSCode );
			   if( !dstrAMSCode.empty() )
			   {
				   getParent()->setField( this, IFASTBP_PROC::BROKERAMS_LIST, ifds::AMSCode, dstrAMSCode );
				   LoadControl( IDC_EDT_AMS );
			   }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
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

bool AMSBrkLvlDlg::GetDataForControl(
                                       UINT controlID,
                                       DString &strValueOut,
                                       bool bFormatted,
                                       int index
                                       ) const
{
   return false;
};

//******************************************************************************

void AMSBrkLvlDlg::ControlUpdated(UINT controlID, const DString &strValue )
{
   DString AMSCode;
   switch( controlID )
   {
		case IDC_EDT_AMS:			
			  if( !isItemChange() )
			  {
					getParent()->send( this, BROKE_AMS::REFRESH_ALLOCTION );
			  }
				LoadControl ( IDC_STATIC_AMSNAME );
				LoadListControl( IDC_LV_ALLOCATION );

				AMSCode = strValue;						   
				if( !AMSCode.empty() )
				{
					GetDlgItem(IDC_BTN_ADMIN)->EnableWindow(true);
				}
				else
				{
					GetDlgItem(IDC_BTN_ADMIN)->EnableWindow(false);
				}
				break;


      default:
         break;
   }
}



//**********************************************************************************
void AMSBrkLvlDlg::EnableControls(bool update )
{
}
//************************************************************************************
void AMSBrkLvlDlg::DoListItemChanged(
                                   UINT listControlID,
                                   const DString &strKey, 
                                   bool bIsNewItem ,
                                   bool bIsDummyItem
                                   )
{
   if( listControlID == IDC_LV_AMS_CODES )
   {
		setItemChange( false );

		AbstractProcess * pParentProcess = dynamic_cast<AbstractProcess *>(getParentProcess());
		if ( !pParentProcess->isCurrentListItemNew(this, IFASTBP_PROC::BROKERAMS_LIST) )
		{			
			GetDlgItem(IDC_BTN_DELETE)->EnableWindow(false);	
		}
		else
		{
			GetDlgItem(IDC_BTN_DELETE)->EnableWindow(true);	
		}
   }

}

//*****************************************************************************
/*bool AMSBrkLvlDlg::doDisableControl(UINT nID, bool bIsNew)
{
    const DString *crtKey = &getParent()->getCurrentListItemKey( this,IFASTBP_PROC::BROKERAMS_LIST );
	if( crtKey )
	{
		if(!bIsNew  )
			return true;
	}
	return false;

};*/

//******************************************************************************
/*bool AMSBrkLvlDlg::doDisablePermCheckButton(UINT nID)
{
	if( nID == IDC_BTN_DELETE )
	{
		AbstractProcess * pParentProcess = dynamic_cast<AbstractProcess *>(getParentProcess());
		if ( pParentProcess->isCurrentListItemNew(this, IFASTBP_PROC::BROKERAMS_LIST) )
		{			
				return true;			
		}
	}
	return(false);
}*/

void AMSBrkLvlDlg::doDisableNonPermButtons()
{
	int nItem = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::BROKERAMS_LIST);

	AbstractProcess * pParentProcess = dynamic_cast<AbstractProcess *>(getParentProcess());
	if (nItem < 1) 
	{
		GetDlgItem(IDC_BTN_ADMIN)->EnableWindow(false);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);		
		GetDlgItem(IDOK)->EnableWindow(false);
		GetDlgItem(IDC_BTN_MORE)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(true);		
		GetDlgItem(IDOK)->EnableWindow(true);
	}
	if (nItem == 1 && pParentProcess->isCurrentListItemDummy(this, IFASTBP_PROC::BROKERAMS_LIST) )
	{
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(true);		
		GetDlgItem(IDOK)->EnableWindow(true);
	}
};

//********************************************************************************
void AMSBrkLvlDlg::DoPreListItemChanged(
                                    UINT listControlID,
                                    const DString &strKey,
                                    bool bIsNewItem,
                                    bool bIsDummyItem
                                    )
{
   if( listControlID == IDC_LV_AMS_CODES )
	{
      setItemChange( true );
   }
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/amsbrklvldlg.cpp-arc  $
// 
//    Rev 1.17   Sep 15 2005 15:10:28   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.16   Dec 09 2003 11:01:48   YINGBAOL
// disable input fields at very begin( avoid crash)
// 
//    Rev 1.15   Nov 25 2003 16:20:56   YINGBAOL
// PTS 10024345
// 
//    Rev 1.14   Aug 20 2003 15:39:06   YINGBAOL
// Launch Global Level AMS having same behavior as at account level
// 
//    Rev 1.13   Aug 08 2003 13:25:48   YINGBAOL
// fix item change
// 
//    Rev 1.12   Aug 08 2003 10:11:14   YINGBAOL
// change search, refresh mechanism
// 
//    Rev 1.11   Jun 19 2003 15:39:26   HERNANDO
// Right-justified the percentage column.
// 
//    Rev 1.10   Apr 16 2003 11:33:32   FENGYONG
// Add more button for broker AMS
// 
//    Rev 1.9   Apr 15 2003 11:26:08   FENGYONG
// do not show validation error when nothing change
// 
//    Rev 1.8   Apr 04 2003 10:25:58   FENGYONG
// Add a namespace
// 
//    Rev 1.7   Mar 27 2003 11:12:04   FENGYONG
// fix
// 
//    Rev 1.6   Mar 25 2003 11:22:26   FENGYONG
// sync up with branch
// 
//    Rev 1.5   Mar 21 2003 18:32:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Mar 18 2003 11:38:32   FENGYONG
// fix
// 
//    Rev 1.3   Mar 14 2003 15:35:02   FENGYONG
// fix
// 
//    Rev 1.2   Mar 14 2003 11:03:14   FENGYONG
// parameter from ams globel is uppercase AMSCODE
// 
//    Rev 1.1   Mar 13 2003 18:35:08   FENGYONG
// fix
// 
//    Rev 1.0   Mar 07 2003 16:47:30   FENGYONG
// Initial revision.
// 
// Initial revision.
 */
