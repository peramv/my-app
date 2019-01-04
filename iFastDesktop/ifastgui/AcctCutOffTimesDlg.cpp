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
//    Copyright 2003 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : AcctCutOffTimesDlg.cpp
// ^CLASS  : AcctCutOffTimesDlg
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "acctcutofftimesdlg.h"
#include <ifastcbo\dstcworksession.hpp>
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\AcctCutOffTimesProcessIncludes.h>
#include <ifastcbo\Entity.hpp>
#include <uibase\dstedit.h>
#include <uibase\ifdslistctrl.h>
#include <bfproc\abstractprocess.hpp>
#include <ifastgui\ifasthistoricalinfo.hpp>
#include "discardmsgdlg.h"

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCT_LVL_CUT_OFF_TIMES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADMINDATES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AcctCutOffTimesDlg > dlgCreator( CMD_GUI_ACCT_LVL_CUT_OFF_TIMES );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
	const I_CHAR * const CLASSNAME		= I_("AcctCutOffTimesDlg");
	const I_CHAR * const FUNDCODE		= I_("FundCode");         
	const I_CHAR * const FUNDNUMBER		= I_("FundNumber");    
	const I_CHAR * const CLASSCODE		= I_("ClassCode");    

	const TCHAR * const CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES = I_("BPROC_ACCT_LVL_CUT_OFF_TIMES");
}

namespace CND
{
	extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;    
}

namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const ACCT_LVL_CUT_OFF_TIME;
	extern CLASS_IMPORT I_CHAR * const BROKER_CUT_OFF;      
}
namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId LastName;
	extern CLASS_IMPORT const BFTextFieldId FirstName;
	extern CLASS_IMPORT const BFTextFieldId CutOffLevel;
	extern CLASS_IMPORT const BFTextFieldId BrokerCode;
}

// Message Process List Control
class LVCutOffTimeData : public IFDSListCtrlRowDataBase
{
public:
	virtual ~LVCutOffTimeData() {}
	DString CutOffTimeType, CutOffTime, FundGroup, TimeZone, Fund, Class, CutOffDays;
		
	virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
	{
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::CutOffTimeType, CutOffTimeType);
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::CutOffTime, CutOffTime);
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::FundGroup, FundGroup);
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::TimeZoneCode, TimeZone);
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::FundCode, Fund);
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::ClassCode, Class);
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::CutOffDays, CutOffDays);
	}
};

class LVCutOffTimeAdapter : public IFDSListCtrlAdapter<LVCutOffTimeData>
{
public:
	// required overrides
	virtual int compare(IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2)
	{
		int result = 0;
			
		const BFFieldId* pFieldId = pCtrl->getColumnField(iSortColumn - 1);
		if(1 == iSortColumn) 
		{
			// Condition indicator column.  Sort on image index
			result = (IFDSListBase::getColumnLVItem(lParam1, iSortColumn - 1)->iImage - 
                IFDSListBase::getColumnLVItem( lParam2, iSortColumn - 1)->iImage );
		} 
		else if(NULL == pFieldId) 
		{
			return(0);
		} 
		else if(*pFieldId == ifds::CutOffTimeType) 
		{
			result = i_strcmp(pData1->CutOffTimeType.c_str(), pData2->CutOffTimeType.c_str());
		} 
		else if(*pFieldId == ifds::CutOffTime) 
		{
			result = i_strcmp(pData1->CutOffTime.c_str(), pData2->CutOffTime.c_str());
		} 
		else if(*pFieldId == ifds::FundGroup) 
		{
			result = i_strcmp(pData1->FundGroup.c_str(), pData2->FundGroup.c_str());
		} 
		else if(*pFieldId == ifds::FundCode) 
		{
			result = i_strcmp(pData1->Fund.c_str(), pData2->Fund.c_str());
		} 
		else if(*pFieldId == ifds::ClassCode) 
		{
			result = i_strcmp(pData1->Class.c_str(), pData2->Class.c_str());
		} 
		else if(*pFieldId == ifds::TimeZoneCode) 
		{
			result = i_strcmp(pData1->TimeZone.c_str(), pData2->TimeZone.c_str());
		} 
		else if(*pFieldId == ifds::CutOffDays) 
		{
			result = i_strcmp(pData1->CutOffDays.c_str(), pData2->CutOffDays.c_str());
		}
			
		return(bAscending ? result : -result);
	}
		
	virtual LRESULT onGetDispInfo(IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo)
	{
		if(pDispInfo->item.mask & LVIF_TEXT)
		{
			const BFFieldId* pFieldId = pCtrl->getColumnField(pDispInfo->item.iSubItem);
				
			if(NULL == pFieldId) 
			{
				pDispInfo->item.pszText = I_( "" );
			} 
			else if(*pFieldId == ifds::CutOffTimeType) 
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->CutOffTimeType.c_str();
			} 
			else if(*pFieldId == ifds::CutOffTime) 
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->CutOffTime.c_str();
			} 
			else if(*pFieldId == ifds::FundGroup) 
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->FundGroup.c_str();
			} 
			else if(*pFieldId == ifds::TimeZoneCode) 
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->TimeZone.c_str();
			} 
			else if(*pFieldId == ifds::FundCode) 
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->Fund.c_str();
			} 
			else if(*pFieldId == ifds::ClassCode) 
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->Class.c_str();
			} 
			else if(*pFieldId == ifds::CutOffDays) 
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->CutOffDays.c_str();
			} 
			return(1);
		}
		return(0);
	}
};


//*****************************************************************************
// Public methods
//*****************************************************************************

AcctCutOffTimesDlg::AcctCutOffTimesDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AcctCutOffTimesDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	//{{AFX_DATA_INIT(AcctCutOffTimesDlg)
	//}}AFX_DATA_INIT
}

//*****************************************************************************

void AcctCutOffTimesDlg::DoDataExchange(CDataExchange* pDX)
{
	BaseMainDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AcctCutOffTimesDlg)
	//}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(AcctCutOffTimesDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AcctCutOffTimesDlg)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmin)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_HISTORICAL, OnBtnHistorical)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED(IDC_BTN_RESET_SEARCH, OnBtnResetSearch)
ON_MESSAGE(UM_OPENBROKERLISTDLG, OpenBrokerListDlg)
ON_MESSAGE(UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

SEVERITY AcctCutOffTimesDlg::doInit()
{
	TRACE_METHOD(CLASSNAME, I_("doInit"));

	getParameter (I_("EntityId"), dstrEntityId);
	getParameter (I_("BrokerLevel"), dstrBrokerLevel);

	isAccountLevel = dstrEntityId.empty() && dstrBrokerLevel != I_("Y") ? true : false;
	isNetworkSenderLevel = !dstrEntityId.empty();
	isBrokerLevel = dstrBrokerLevel == I_("Y");

	return( NO_CONDITION );
}
//******************************************************************************

BOOL AcctCutOffTimesDlg::OnInitDialog() 
{
	TRACE_METHOD(CLASSNAME, ONINITDIALOG);
	BaseMainDlg::OnInitDialog();
	SetDlgCaption();

	if(isAccountLevel || isBrokerLevel)
	{
		GetDlgItem(IDC_STC_CUTOFDAYS)->ShowWindow (false);
		GetDlgItem(IDC_EDT_CUTOFDAYS)->ShowWindow (false);
	}
   
	GetDlgItem(IDC_TXT_BROKER_CODE)->ShowWindow(isBrokerLevel);
	GetDlgItem(IDC_EDT_BROKER_CODE)->ShowWindow(isBrokerLevel);
	GetDlgItem(IDC_BTN_SEARCH)->ShowWindow(isBrokerLevel);
	GetDlgItem(IDC_BTN_RESET_SEARCH)->ShowWindow(isBrokerLevel);

	return(TRUE);
}

//******************************************************************************

void AcctCutOffTimesDlg::OnPostInitDialog()
{
	TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);
	
	if(!isBrokerLevel)
		SetUserAccesFunctionCode(UAF::ACCT_LVL_CUT_OFF_TIME);
	else
		SetUserAccesFunctionCode(UAF::BROKER_CUT_OFF);

	addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_CUT_OFF_TIMES);	
	addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_CUT_OFF_TIMES);

	IFDSListCtrl* ifdsListControlCutOffTimes = new IFDSAdaptedListCtrl<LVCutOffTimeAdapter>(this, CLASSNAME, IDC_LV_CUT_OFF_TIMES, 0, CTRLFLAG_DEFAULT, true /*ShowSelAlways*/, true /*ShowConditions*/);

	BFFieldId cutOffTimesHeading;
	getHeadingList (cutOffTimesHeading);
	
	AddIFDSListControl(ifdsListControlCutOffTimes, I_("CUT_OFF_TIMES"), IFASTBP_PROC::CUT_OFF_TIMES_LIST, cutOffTimesHeading);   
	
	AddControl(CTRL_EDIT, IDC_EDT_FUND_NBR, IFASTBP_PROC::CUT_OFF_TIMES_LIST, ifds::FundNumber, CTRLFLAG_DEFAULT, IDC_LV_CUT_OFF_TIMES);
	AddControl(CTRL_EDIT, IDC_EDT_FUND, IFASTBP_PROC::CUT_OFF_TIMES_LIST, ifds::FundCode, CTRLFLAG_DEFAULT, IDC_LV_CUT_OFF_TIMES);
	AddControl(CTRL_EDIT, IDC_EDT_CLASS, IFASTBP_PROC::CUT_OFF_TIMES_LIST, ifds::ClassCode, CTRLFLAG_DEFAULT, IDC_LV_CUT_OFF_TIMES);
	if(!isAccountLevel || !isBrokerLevel)
		AddControl(CTRL_EDIT, IDC_EDT_CUTOFFDAYS, IFASTBP_PROC::CUT_OFF_TIMES_LIST, ifds::CutOffDays, CTRLFLAG_DEFAULT, IDC_LV_CUT_OFF_TIMES);
	
	if(isBrokerLevel)
	{
		// Broker Code Search
		AddControl(CTRL_EDIT, IDC_EDT_BROKER_CODE, BF::NullContainerId, ifds::BrokerCode, CTRLFLAG_DEFAULT);
		ConnectControlToData(IDC_EDT_BROKER_CODE, true);

		GetDlgItem(IDC_TXT_BROKER_CODE)->SetFocus();
		GetDlgItem(IDC_EDT_BROKER_CODE)->EnableWindow(true);
		
		SetDisabledItems(true);
	}

	// Cut Off Time Type
	AddControl(CTRL_COMBO, IDC_CMB_CUT_OFF_TIME_TYPE, IFASTBP_PROC::CUT_OFF_TIMES_LIST, 
		ifds::CutOffTimeType, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CUT_OFF_TIMES);			

	// Fund Group
	AddControl(CTRL_COMBO, IDC_CMB_FUND_GROUP, IFASTBP_PROC::CUT_OFF_TIMES_LIST, 
		ifds::FundGroup, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CUT_OFF_TIMES);	

	// Time Zone
	AddControl(CTRL_COMBO, IDC_CMB_TIME_ZONE, IFASTBP_PROC::CUT_OFF_TIMES_LIST, 
		ifds::TimeZoneCode, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CUT_OFF_TIMES);

	// Cut Off Time 
	AddControl(CTRL_TIME, IDC_CUT_OFF_TIME, IFASTBP_PROC::CUT_OFF_TIMES_LIST, 
		ifds::CutOffTime, CTRLFLAG_DEFAULT, IDC_LV_CUT_OFF_TIMES );	

	if(!isBrokerLevel)
	{
		LoadListControl(IDC_LV_CUT_OFF_TIMES);
		GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist(this, IFASTBP_PROC::CUT_OFF_TIMES_LIST));
		DString dstrCutOffLevel = isAccountLevel ? I_("01") : I_("02");
		getParent()->setField(this, IFASTBP_PROC::CUT_OFF_TIMES_LIST, ifds::CutOffLevel, dstrCutOffLevel);
	}
}

//*****************************************************************************

bool AcctCutOffTimesDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{
	TRACE_METHOD( CLASSNAME, DOREFRESH );
	return( true );
}

//*******************************************************************************************

bool AcctCutOffTimesDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
{
	return( false );
}

//**********************************************************************************

bool AcctCutOffTimesDlg::GetDataForControl(UINT controlID,
                               DString &strValueOut,
                               bool bFormatted,
                               int index
                              ) const
{
	return false;
};

//**********************************************************************************

void AcctCutOffTimesDlg::SetDlgCaption()
{
	TRACE_METHOD(CLASSNAME, I_("SetDlgCaption"));
    
	if(isAccountLevel)
	{
		DString dstrShrNum, dstrAccountNum, dstrEntityName;

		getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum, false);
		dstrAccountNum.strip().stripLeading('0');

		// Get Entity Name
		if(!dstrAccountNum.empty()) 
		{
			dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
			getDataGroupId(), dstrAccountNum, dstrEntityName);
		}

		SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
	}
	else if(isNetworkSenderLevel)
	{
		setNetworkSenderCaption ();
	}
	else if(isBrokerLevel)
	{
		setBrokerCaption();
	}
}

//************************************************************************

void AcctCutOffTimesDlg::OnBtnAdmin() 
{
	ShowAdminDates( IFASTBP_PROC::CUT_OFF_TIMES_LIST );
}

//******************************************************************************

void AcctCutOffTimesDlg::OnBtnAdd() 
{
	AddToListControl( IDC_LV_CUT_OFF_TIMES );
}

//******************************************************************************

void AcctCutOffTimesDlg::OnBtnDelete() 
{
	DeleteFromListControl( IDC_LV_CUT_OFF_TIMES );
}

//********************************************************************************

void AcctCutOffTimesDlg::OnBtnMore()
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
	CWaitCursor wait;

	const DString *crtKey = &getParent()->getCurrentListItemKey(this, IFASTBP_PROC::CUT_OFF_TIMES_LIST);

	if(getParent()->performSearch(this, IFASTBP_PROC::CUT_OFF_TIMES_LIST, SEARCH_NEXT_BLOCK ) <= WARNING)
	{
		LoadListControl( IDC_LV_CUT_OFF_TIMES, crtKey );      
	}
   
	GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist(this, IFASTBP_PROC::CUT_OFF_TIMES_LIST));
}

//******************************************************************************

void AcctCutOffTimesDlg::OnBtnReset() 
{
   ResetListItem(IDC_LV_CUT_OFF_TIMES);
}

//******************************************************************************

void AcctCutOffTimesDlg::OnBtnHistorical() 
{
	TRACE_METHOD(CLASSNAME, I_("OnBtnHistorical"));   
	CWaitCursor wait;   

	IFastHistoricalInfo historicalInfo;
	historicalInfo(this, IFASTBP_PROC::CUT_OFF_TIMES_LIST, I_("SINGLE"));
}

//******************************************************************************

void AcctCutOffTimesDlg::OnBtnSearch() 
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSearch"));
	CWaitCursor wait;
	
	DString brokerCode;
		
	GetControlText(IDC_EDT_BROKER_CODE, brokerCode);
	if(!brokerCode.empty() && brokerCode != NULL_STRING)
	{		
		GetList(IDC_LV_CUT_OFF_TIMES)->ConnectToData(true);
	
		DString isBrokerContainterValid;

		getParent()->getField(this, BF::NullContainerId, ifds::BrokerContainerValid, isBrokerContainterValid, false);

		if(isBrokerContainterValid == I_("Y"))
		{
			LoadListControl(IDC_LV_CUT_OFF_TIMES);
			GetDlgItem(IDC_EDT_BROKER_CODE)->EnableWindow(false);
			GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(false);
			SetDisabledItems(false);
		}
	}
}

//******************************************************************************

void AcctCutOffTimesDlg::OnBtnResetSearch() 
{
	DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_MSGA, TXT_DISCARD_MSGB, TXT_DISCARD);
	if(discardDlg.DoModal() == IDCANCEL)
		return;

	if(isBrokerLevel)
	{
		getParent()->send(this, I_("RESET_SEARCH"));
		ConnectControlsToData(IDC_LV_CUT_OFF_TIMES, false);
		GetList(IDC_LV_CUT_OFF_TIMES)->ConnectToData(false);

		// Disable Buttons & Screen
		SetControlText(IDC_EDT_BROKER_CODE, NULL_STRING);
		GetDlgItem (IDC_TXT_BROKER_CODE)->SetFocus();
		GetDlgItem(IDC_EDT_BROKER_CODE)->EnableWindow(true);
		GetDlgItem (IDC_BTN_SEARCH)->EnableWindow(true);		
		SetDisabledItems(true);
	}
}


//******************************************************************************
LRESULT AcctCutOffTimesDlg::OpenBrokerListDlg(WPARAM, LPARAM)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenBrokerListDlg"));
	
	try
	{
		E_COMMANDRETURN eRtn = CMD_CANCEL;
		CWaitCursor wait;
		
		DString brokerCode;
		
		GetControlText(IDC_EDT_BROKER_CODE, brokerCode);
		setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
		//invoke the broker dialog and process
		eRtn = invokeCommand(getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL);
		
		switch(eRtn)
		{
			case CMD_OK:
			case CMD_MODELESS_INPROCESS:
			{
				//get the broker code that the user selected from the branch list and 
				//set the field on the account object
				DString brokerCode;
				
				getParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
				
				if(brokerCode != NULL_STRING)
				{
					// SetControlText( IDC_EDT_BROKER_CODE, brokerCode );
					bool success = SetControlText(IDC_EDT_BROKER_CODE, brokerCode);
					BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem(IDC_EDT_BROKER_CODE));
					
					if(!success && pBC)
						pBC->Load();
					if(pBC && pBC->IsToolTipVisible())
						pBC->ToggleToolTip();
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
	catch(ConditionException &ce)
	{
		ConditionMessageBox(ce);
	}
	catch(...)
	{
		DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
	}
	return(0);
}
//******************************************************************************
LRESULT AcctCutOffTimesDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundListDlg" ) );

	E_COMMANDRETURN eRtn = CMD_CANCEL;
	CWaitCursor wait;

	try
	{
		if( GetFocus () == GetDlgItem( IDC_EDT_FUND) ) 
		{
			DString dstrFundCode;

			GetControlText( IDC_EDT_FUND, dstrFundCode);
			setParameter (FUNDCODE, dstrFundCode);
		} 
		else if( GetFocus () == GetDlgItem( IDC_EDT_CLASS) )
		{
			DString dstrClassCode;

			GetControlText (IDC_EDT_CLASS, dstrClassCode);
			setParameter (CLASSCODE, dstrClassCode);
		}
		else if( GetFocus () == GetDlgItem( IDC_EDT_FUND_NBR) )
		{
			DString dstrFundNumber;

			GetControlText (IDC_EDT_FUND_NBR, dstrFundNumber);
			setParameter (FUNDNUMBER, dstrFundNumber);
		}
		
		//invoke the fund class dialog and process
 		eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );

		switch (eRtn)
		{
			case CMD_OK:
			case CMD_MODELESS_INPROCESS:
            {
				DString dstrFundCode, dstrClassCode;

				getParameter (FUNDCODE, dstrFundCode);
				getParent()->setField ( this, IFASTBP_PROC::CUT_OFF_TIMES_LIST, ifds::FundCode, dstrFundCode);
				getParameter (FUNDNUMBER, dstrFundCode);
				getParent()->setField ( this, IFASTBP_PROC::CUT_OFF_TIMES_LIST, ifds::FundNumber, dstrFundCode);
				getParameter (CLASSCODE, dstrClassCode);
				getParent()->setField ( this, IFASTBP_PROC::CUT_OFF_TIMES_LIST, ifds::ClassCode, dstrClassCode);

				LoadControl( IDC_EDT_FUND);
				LoadControl( IDC_EDT_CLASS );
				LoadControl( IDC_EDT_FUND_NBR );
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
//******************************************************************************

BOOL AcctCutOffTimesDlg::PreTranslateMessage( MSG* pMsg ) 
{
	if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
	{
		if( GetFocus()== GetDlgItem( IDC_EDT_BROKER_CODE ))
			PostMessage( UM_OPENBROKERLISTDLG );

		if( GetFocus() == GetDlgItem( IDC_EDT_CLASS ) ||
			GetFocus() == GetDlgItem( IDC_EDT_FUND ) ||
			GetFocus() == GetDlgItem( IDC_EDT_FUND_NBR ))
		{
			PostMessage( UM_OPENFUNDCLASSLISTDLG );
		}
	}

	return BaseMainDlg::PreTranslateMessage (pMsg);
}

//******************************************************************************

void AcctCutOffTimesDlg::getHeadingList (BFFieldId& idField)
{	
	/* Removed checking level. Use the same heading in all level */
	idField = ifds::NetworkSenderLvlCutOffTimesHeading;
}

//******************************************************************************

void AcctCutOffTimesDlg::setNetworkSenderCaption ()
{
	CString caption;
		
	caption.LoadString (TXT_NETWORK_SENDER_CUTOFF_TIME);

	Entity *pEntity;
	DString dstrLastName, dstrFirstName;

    dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( getDataGroupId (), dstrEntityId, pEntity );

    if( pEntity )
	{
		pEntity->getField( ifds::LastName, dstrLastName, getDataGroupId (), false );
        pEntity->getField( ifds::FirstName, dstrFirstName, getDataGroupId (), false );
	}
	CString cstrEntityId;
	cstrEntityId.LoadString(TXT_ENTITY_ID);
	caption = caption + cstrEntityId + dstrEntityId.c_str() + I_("; ") + dstrLastName.c_str() + I_(";") + dstrFirstName.c_str(); 
	SetWindowText(caption);
}

//******************************************************************************

void AcctCutOffTimesDlg::setBrokerCaption ()
{
	CString caption;

	caption.LoadString (TXT_BROKER_CUTOFF_TIME);	
	SetWindowText(caption);
}

void AcctCutOffTimesDlg::SetDisabledItems(bool isDisabled)
{
	GetDlgItem(IDC_BTN_RESET_SEARCH)->EnableWindow(!isDisabled);

	GetDlgItem(IDC_BTN_MORE)->EnableWindow(!isDisabled && getParent()->doMoreRecordsExist(this, IFASTBP_PROC::CUT_OFF_TIMES_LIST));
	   
	GetDlgItem(IDC_CMB_CUT_OFF_TIME_TYPE)->EnableWindow(!isDisabled);
	GetDlgItem(IDC_CMB_FUND_GROUP)->EnableWindow(!isDisabled);
	GetDlgItem(IDC_CUT_OFF_TIME)->EnableWindow(!isDisabled);
	GetDlgItem(IDC_CMB_TIME_ZONE)->EnableWindow(!isDisabled);
	GetDlgItem(IDC_EDT_FUND_NBR)->EnableWindow(!isDisabled);
	GetDlgItem(IDC_EDT_FUND)->EnableWindow(!isDisabled);
	GetDlgItem(IDC_EDT_CLASS)->EnableWindow(!isDisabled);

	GetDlgItem (IDC_BTN_RESET)->EnableWindow(!isDisabled);
	GetDlgItem (IDC_BTN_HISTORICAL)->EnableWindow(!isDisabled);
	GetDlgItem (IDC_BTN_ADM_DATES)->EnableWindow(!isDisabled);
}

bool AcctCutOffTimesDlg::doDisablePermCheckButton(UINT nID)
{
	TRACE_METHOD(CLASSNAME, I_("doDisablePermCheckButtons"));
	if (nID == IDC_BTN_ADD || nID == IDC_BTN_DELETE)
	{
		if(isBrokerLevel)
		{
			DString brokerCode;
			GetControlText(IDC_EDT_BROKER_CODE, brokerCode);
			DString isBrokerContainterValid;
			
			if(!brokerCode.empty())
			{
				getParent()->getField(this, BF::NullContainerId, ifds::BrokerContainerValid, isBrokerContainterValid, false);
				return  !(isBrokerContainterValid == I_("Y"));
			}
			else
			{
				return true;
			}
		}
	}
	
	return false;
}

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/AcctCutOffTimesDlg.cpp-arc  $
// 
//    Rev 1.5   Nov 28 2011 10:22:14   popescu
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.4   Nov 24 2011 15:46:16   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.3   Jul 26 2006 14:52:04   jankovii
// PET 2192 FN02 - Dealings Sender Cut Off Time.
// 
//    Rev 1.2   Jul 21 2006 16:37:56   jankovii
// PET 2192 FN02 - Dealings - Sender Cut Off Time.
// 
//    Rev 1.1   Sep 15 2005 15:09:58   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.0   Jul 05 2005 17:41:18   hernando
// Initial revision.
