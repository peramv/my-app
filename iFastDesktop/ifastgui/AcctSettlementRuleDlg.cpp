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
//    Copyright 2008 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : AcctLvlSttlmntRuleDlg.cpp
// ^CLASS  : AcctLvlSttlmntRuleDlg
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\DSTCUserSession.hpp>

#include <configmanager.hpp>

#include <bfproc\abstractprocess.hpp>

#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>

#include <ifastgui\ifasthistoricalinfo.hpp>

#include <uibase\dstcombobox.h>
#include <uibase\dstedit.h>
#include <uibase\DSTOleDateTime.h>
#include <uibase\DstcFuncs.h>
#include <uibase\ifdslistctrl.h>
#include <uibase\dstbutton.h>


#include <ifastdbrkr\dstcsecurity.hpp>
#include <ifastdbrkr\dstchost.hpp>

#include <ifastcbo\mfaccount.hpp>

#include <ifastbp\AcctSettlementRuleProcessIncludes.h>


#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

#include "AcctSettlementRuleDlg.h"

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCT_LEVEL_SETTLEMENT_RULE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE;

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADMINDATES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AcctLvlSttlmntRuleDlg > dlgCreator( CMD_GUI_ACCT_LEVEL_SETTLEMENT_RULE );

namespace
{
    const I_CHAR * const CLASSNAME      = I_( "AcctLvlSttlmntRuleDlg" );
    const I_CHAR * const FUNDCODE       = I_( "FundCode" );
    const I_CHAR * const FUNDNUMBER     = I_( "FundNumber" );
    const I_CHAR * const CLASSCODE      = I_( "ClassCode" );

    const I_CHAR * const SETTLE_DAYS_ED = I_( "24" );
    const I_CHAR * const SETTLE_DAYS_PW = I_( "25" );
    const I_CHAR * const SETTLE_DAYS_TO = I_( "26" );
    const I_CHAR * const SETTLE_DAYS_TI = I_( "27" );
    const I_CHAR * const SETTLE_DAYS_EO = I_( "28" );
    const I_CHAR * const SETTLE_DAYS_EI = I_( "29" );

   const I_CHAR * const MODUSER         = I_( "ModUser" );
   const I_CHAR * const MODDATE         = I_( "ModDate" );
   const I_CHAR * const USERNAME        = I_( "Username" );
   const I_CHAR * const PROCESSDATE     = I_( "ProcessDate" );


    const BFFieldId PRIMARY_ACCOUNT_OWNER(100L);
}

namespace CND
{
    extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
    extern CLASS_IMPORT I_CHAR * const ACCT_LEVEL_SETTLEMENT_RULE;
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId SettleDays;
    extern CLASS_IMPORT const BFTextFieldId FundNumber;
    extern CLASS_IMPORT const BFTextFieldId AcctSettlementRuleHeadingSet;
}

// Message Process List Control
class LVAcctSettlementRuleData : public IFDSListCtrlRowDataBase
{
public:
    virtual ~LVAcctSettlementRuleData() {}
    DString RuleType, Fund, Class, SettleDays, EffectiveDate, StopDate, FundGroup;

    virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
    {
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::RuleType, RuleType );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundCode, Fund);
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ClassCode, Class);
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::SettleDays, SettleDays);
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EffectiveDate, EffectiveDate);
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::StopDate, StopDate);
		pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundGroup, FundGroup);
    }
};

class LVAcctSettlementRuleAdapter : public IFDSListCtrlAdapter< LVAcctSettlementRuleData >
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
        } else if( *pFieldId == ifds::RuleType ) {
            result = i_strcmp( pData1->RuleType.c_str(), pData2->RuleType.c_str() );
        } else if( *pFieldId == ifds::FundCode ) {
            result = i_strcmp( pData1->Fund.c_str(), pData2->Fund.c_str() );
        } else if( *pFieldId == ifds::ClassCode ) {
            result = i_strcmp( pData1->Class.c_str(), pData2->Class.c_str() );
        } else if( *pFieldId == ifds::SettleDays ) {
            result = i_strcmp( pData1->SettleDays.c_str(), pData2->SettleDays.c_str() );
        } else if( *pFieldId == ifds::EffectiveDate ) {
            result = i_strcmp( pData1->EffectiveDate.c_str(), pData2->EffectiveDate.c_str() );
        } else if( *pFieldId == ifds::StopDate ) {
            result = i_strcmp( pData1->StopDate.c_str(), pData2->StopDate.c_str() );
		} else if( *pFieldId == ifds::FundGroup ) {
            result = i_strcmp( pData1->FundGroup.c_str(), pData2->FundGroup.c_str() );
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
            } else if( *pFieldId == ifds::RuleType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->RuleType.c_str();
            } else if( *pFieldId == ifds::FundCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->Fund.c_str();
            } else if( *pFieldId == ifds::ClassCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->Class.c_str();
            } else if( *pFieldId == ifds::SettleDays ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->SettleDays.c_str();
            } else if( *pFieldId == ifds::EffectiveDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->EffectiveDate.c_str();
            } else if( *pFieldId == ifds::StopDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->StopDate.c_str();
			} else if( *pFieldId == ifds::FundGroup ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundGroup.c_str();
			}
            return( 1 );
        }
        return( 0 );
    }
};


//*****************************************************************************
// Public methods
//*****************************************************************************

// AcctLvlSttlmntRuleDlg dialog
AcctLvlSttlmntRuleDlg::AcctLvlSttlmntRuleDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AcctLvlSttlmntRuleDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
    TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
    //{{AFX_DATA_INIT(AcctLvlSttlmntRuleDlg)
    //}}AFX_DATA_INIT

}

//******************************************************************************
void AcctLvlSttlmntRuleDlg::DoDataExchange(CDataExchange* pDX)
{
    BaseMainDlg::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(AcctLvlSttlmntRuleDlg)
    //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(AcctLvlSttlmntRuleDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AcctLvlSttlmntRuleDlg)
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DELETE, OnBtnDelete )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmin )
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_HISTORY, OnBtnHistorical )
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// AcctLvlSttlmntRuleDlg message handlers
//******************************************************************************

SEVERITY AcctLvlSttlmntRuleDlg::doInit()
{
    TRACE_METHOD( CLASSNAME, I_("doInit"));

    return( NO_CONDITION );
}
//******************************************************************************

BOOL AcctLvlSttlmntRuleDlg::OnInitDialog() 
{
    TRACE_METHOD( CLASSNAME, ONINITDIALOG );
    BaseMainDlg::OnInitDialog();
    SetDlgCaption();

    return(TRUE);
}

//******************************************************************************

void AcctLvlSttlmntRuleDlg::OnPostInitDialog()
{
    TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

    SetUserAccesFunctionCode( UAF::ACCT_LEVEL_SETTLEMENT_RULE );
    addBtnAddForPermissionCheck( IDC_BTN_ADD, IDC_LV_SETTLEMNT_RULE );
    addBtnDeleteForPermissionCheck( IDC_BTN_DELETE, IDC_LV_SETTLEMNT_RULE );

    IFDSListCtrl* ifdsListAcctLvlSttlmntRule = 
                  new IFDSAdaptedListCtrl< LVAcctSettlementRuleAdapter >( this, CLASSNAME, IDC_LV_SETTLEMNT_RULE, 
                  0, CTRLFLAG_DEFAULT, true /*ShowSelAlways*/, true /*ShowConditions*/);
   
    AddIFDSListControl( ifdsListAcctLvlSttlmntRule, I_("ACCT_SETTLEMENT_RULE"), 
       IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::AcctSettlementRuleHeadingSet );   

    AddControl( CTRL_EDIT, IDC_EDT_FUND_NBR, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::FundNumber, CTRLFLAG_DEFAULT, IDC_LV_SETTLEMNT_RULE );
    AddControl( CTRL_EDIT, IDC_EDT_FUND, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::FundCode, CTRLFLAG_DEFAULT, IDC_LV_SETTLEMNT_RULE );
    AddControl( CTRL_EDIT, IDC_EDT_CLASS, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::ClassCode, CTRLFLAG_DEFAULT, IDC_LV_SETTLEMNT_RULE );
    AddControl( CTRL_EDIT, IDC_EDT_RULE_VALUE, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::SettleDays, CTRLFLAG_DEFAULT, IDC_LV_SETTLEMNT_RULE );

    AddControl( CTRL_COMBO,
                IDC_CMB_RULE_TYPE,
                IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST,
                ifds::RuleType,
                CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                IDC_LV_SETTLEMNT_RULE );

    AddControl( CTRL_DATE,
                IDC_DTP_START_DATE,
                IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST,
                ifds::EffectiveDate,
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                IDC_LV_SETTLEMNT_RULE );

    AddControl( CTRL_DATE,
                IDC_DTP_STOP_DATE, 
                IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST,
                ifds::StopDate,
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                IDC_LV_SETTLEMNT_RULE );

	AddControl( CTRL_COMBO,
				IDC_CMB_FUND_GROUP_TYPE, 
                IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST,
				ifds::FundGroup,
                CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST,
                IDC_LV_SETTLEMNT_RULE );

    ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_RULE_VALUE ) ) )->SetAllowedChars( I_("0123456789") );

    ConnectListToData( IDC_LV_SETTLEMNT_RULE, true );
    LoadListControl( IDC_LV_SETTLEMNT_RULE );

    GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST ) );
}

//*****************************************************************************

bool AcctLvlSttlmntRuleDlg::doRefresh( GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
    TRACE_METHOD( CLASSNAME, I_("doRefresh") );

    SetMessageStatusBar( TXT_LOAD_ACCT_SETTLEMENT_RULE );

    // display caption
    DString dstrShrNum, dstrAcctNum, dstrEntityName;
    getParent()->getField( this, ifds::ShrNum, dstrShrNum );
    getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAcctNum ); 
    getParent()->getField( this, PRIMARY_ACCOUNT_OWNER, dstrEntityName );

    ConnectListToData( IDC_LV_SETTLEMNT_RULE, true );
    LoadListControl( IDC_LV_SETTLEMNT_RULE );

    SetMessageStatusBar(NULL_STRING);
    return( true );
}

//*******************************************************************************************
bool AcctLvlSttlmntRuleDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
{
    dstrOut = I_( "" );

    if( lSubstituteId == ifds::AcctSettlementRuleHeadingSet.getId() )
    {
        if( dstrColumnKey == I_("RuleType" ) )
        {
            getParent()->getField( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::RuleType, dstrOut, false );
            return( true );
        }
        else if( dstrColumnKey == I_("FundCode" ) )
        {
            getParent()->getField( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::FundCode, dstrOut, true );
            return( true );
        }
        else if( dstrColumnKey == I_("ClassCode" ) )
        {
            getParent()->getField( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::ClassCode, dstrOut, true );
            return( true );
        }
        else if( dstrColumnKey == I_("SettleDays" ) )
        {
            getParent()->getField( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::SettleDays, dstrOut, true );
            return( true );
        }
        else if( dstrColumnKey == I_("EffectiveDate" ) )
        {
            getParent()->getField( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::EffectiveDate, dstrOut, true );
            return( true );
        }
        else if( dstrColumnKey == I_("StopDate" ) )
        {
            getParent()->getField( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::StopDate, dstrOut, true );
            return( true );
        }
		else if( dstrColumnKey == I_("FundGroup" ) )
		{
			getParent()->getField( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::FundGroup, dstrOut, true );
			return( true );
		}
    }

    return( false );
}

//**********************************************************************************
void AcctLvlSttlmntRuleDlg::SetDlgCaption()
{
    TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

    DString dstrShrNum, dstrAccountNum, dstrEntityName;

    getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum, false);
    dstrAccountNum.strip().stripLeading('0');

    // Get Entity Name
    if ( !dstrAccountNum.empty() ) 
    {
        dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
        getDataGroupId(), dstrAccountNum, dstrEntityName);
    }

    SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
}

//************************************************************************
void AcctLvlSttlmntRuleDlg::OnBtnAdmin() 
{
    TRACE_METHOD( CLASSNAME, I_("OnBtnAdmin") );

    ShowAdminDates( IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
}

//******************************************************************************

void AcctLvlSttlmntRuleDlg::OnBtnAdd() 
{
    TRACE_METHOD( CLASSNAME, I_("OnBtnAdd"));

    AddToListControl( IDC_LV_SETTLEMNT_RULE );
    GetList( IDC_LV_SETTLEMNT_RULE )->SetFocus();
}

//******************************************************************************

void AcctLvlSttlmntRuleDlg::OnBtnDelete() 
{
    TRACE_METHOD( CLASSNAME, I_("OnBtnDelete"));

	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDelete" ) );

	getParent()->setField( this, IsSettlementRulePendingTrade, I_( "N" ), false );

	if (GETHIGHESTSEVERITY () >= WARNING)
	{
		ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());	
	}
	if (GETHIGHESTSEVERITY () <= WARNING)
	{
		DeleteFromListControl( IDC_LV_SETTLEMNT_RULE );
	}

	GetList( IDC_LV_SETTLEMNT_RULE )->SetFocus();
}

//********************************************************************************
void AcctLvlSttlmntRuleDlg::OnBtnMore()
{
    TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
    CWaitCursor wait;

    SetMessageStatusBar(TXT_LOAD_ACCT_SETTLEMENT_RULE);

    const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );

    if( getParent()->performSearch( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
    {
        LoadListControl( IDC_LV_SETTLEMNT_RULE, crtKey );      
    }

    SetMessageStatusBar(NULL_STRING);

    GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST ) );
}

//******************************************************************************
void AcctLvlSttlmntRuleDlg::OnBtnReset() 
{
    TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));

    ResetListItem( IDC_LV_SETTLEMNT_RULE );
    GetList( IDC_LV_SETTLEMNT_RULE )->SetFocus();
}

//******************************************************************************
LRESULT AcctLvlSttlmntRuleDlg::OpenFundClassListDlg( WPARAM, LPARAM )
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
                getParent()->setField ( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::FundCode, dstrFundCode);
                getParameter (FUNDNUMBER, dstrFundCode);
                getParent()->setField ( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::FundNumber, dstrFundCode);
                getParameter (CLASSCODE, dstrClassCode);
                getParent()->setField ( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::ClassCode, dstrClassCode);

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
 BOOL AcctLvlSttlmntRuleDlg::PreTranslateMessage( MSG* pMsg ) 
{
    TRACE_METHOD( CLASSNAME, I_("PreTranslateMessage"));

    if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
    {
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
void AcctLvlSttlmntRuleDlg::OnBtnHistorical()
{
    TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
    CWaitCursor wait;

    E_COMMANDRETURN eRtn = CMD_CANCEL;
    DString dstrShrNum, dstrAccountNum;

    getParent()->getField( this, ifds::ShrNum, dstrShrNum, false );
    getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum ); 

    setParameter(MFCAN_IP_PARAM::SHR_NUM, dstrShrNum);
    setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum);   

    IFastHistoricalInfo historicalInfo;

    historicalInfo( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, I_( "MULTI" ) );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AcctSettlementRuleDlg.cpp-arc  $
// 
//    Rev 1.1   Apr 16 2008 18:33:22   daechach
// PET2385 FN02&07 - Modified code regarding code review.
*
*/
