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
// ^FILE   : AcctRoundingRuleDlg.cpp
// ^CLASS  : AcctRoundingRuleDlg
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\DSTCUserSession.hpp>
#include <ifastcbo\mfaccount.hpp>

#include <configmanager.hpp>
#include <bfproc\abstractprocess.hpp>

#include <ifastbp\AcctRoundingRuleProcess.hpp>
#include <ifastbp\AcctRoundingRuleProcessIncludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>

#include <uibase\dstcombobox.h>
#include <uibase\dstedit.h>
#include <uibase\DSTOleDateTime.h>
#include <uibase\DstcFuncs.h>
#include <uibase\ifdslistctrl.h>
#include <uibase\dstbutton.h>

#include <ifastdbrkr\dstcsecurity.hpp>
#include <ifastdbrkr\dstchost.hpp>
 
#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

#include "AcctRoundingRuleDlg.h"

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCT_ROUNDING_RULE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_ROUNDING_RULE;

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AcctRoundingRuleDlg > dlgCreator( CMD_GUI_ACCT_ROUNDING_RULE );

namespace
{
	const I_CHAR * const CLASSNAME       = I_( "AcctRoundingRuleDlg" );	

	const BFFieldId PRIMARY_ACCOUNT_OWNER(100L);
}

namespace CND
{
    extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
    extern CLASS_IMPORT I_CHAR * const ACCT_ROUNDING_RULE;
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId RoundFlg;
    extern CLASS_IMPORT const BFTextFieldId RecalcMthd;
	extern CLASS_IMPORT const BFIntegerFieldId UnitsPrecisionAcct;
    extern CLASS_IMPORT const BFTextFieldId AcctRoundingRuleHeadingSet;
}

namespace AUDITTYPE
{    
	extern CLASS_IMPORT I_CHAR * const ACTRDR;
}

// Message Process List Control
class LVAcctRoundingRuleData : public IFDSListCtrlRowDataBase
{
public:
    virtual ~LVAcctRoundingRuleData() {}
    DString RoundFlg, RecalcMthd, UnitsPrecisionAcct, StartDate, StopDate;

    virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
    {
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::RoundFlg, RoundFlg );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::RecalcMthd, RecalcMthd);
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::UnitsPrecisionAcct, UnitsPrecisionAcct);       
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::StartDate, StartDate);
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::StopDate, StopDate);
    }
};

class LVAcctRoundingRuleAdapter : public IFDSListCtrlAdapter< LVAcctRoundingRuleData >
{
public:
    // required overrides
    virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2 )
    {
        int result = 0;

        const BFFieldId* pFieldId = pCtrl->getColumnField( iSortColumn - 1 );
        if( 1 == iSortColumn ) {
            // Condition indicator column.  Sort on image index
            result = ( IFDSListBase::getColumnLVItem( lParam1, iSortColumn - 1)->iImage - IFDSListBase::getColumnLVItem( lParam2, iSortColumn - 1)->iImage );
        } else if( NULL == pFieldId ) {
            return( 0 );
        } else if( *pFieldId == ifds::RoundFlg ) {
            result = i_strcmp( pData1->RoundFlg.c_str(), pData2->RoundFlg.c_str() );
        } else if( *pFieldId == ifds::RecalcMthd ) {
            result = i_strcmp( pData1->RecalcMthd.c_str(), pData2->RecalcMthd.c_str() );
        } else if( *pFieldId == ifds::UnitsPrecisionAcct ) {
            result = i_strcmp( pData1->UnitsPrecisionAcct.c_str(), pData2->UnitsPrecisionAcct.c_str() );        
        } else if( *pFieldId == ifds::StartDate ) {
            result = i_strcmp( pData1->StartDate.c_str(), pData2->StartDate.c_str() );
        } else if( *pFieldId == ifds::StopDate ) {
            result = i_strcmp( pData1->StopDate.c_str(), pData2->StopDate.c_str() );
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
            } else if( *pFieldId == ifds::RoundFlg ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->RoundFlg.c_str();
            } else if( *pFieldId == ifds::RecalcMthd ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->RecalcMthd.c_str();
            } else if( *pFieldId == ifds::UnitsPrecisionAcct ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->UnitsPrecisionAcct.c_str();            
            } else if( *pFieldId == ifds::StartDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->StartDate.c_str();
            } else if( *pFieldId == ifds::StopDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->StopDate.c_str();
            }
            return( 1 );
        }
        return( 0 );
    }
};


//*****************************************************************************
// Public methods
//*****************************************************************************

// AcctRoundingRuleDlg dialog
AcctRoundingRuleDlg::AcctRoundingRuleDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AcctRoundingRuleDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
    TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
    //{{AFX_DATA_INIT(AcctRoundingRuleDlg)
    //}}AFX_DATA_INIT

}

//******************************************************************************
void AcctRoundingRuleDlg::DoDataExchange(CDataExchange* pDX)
{
    BaseMainDlg::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(AcctRoundingRuleDlg)
    //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(AcctRoundingRuleDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AcctRoundingRuleDlg)
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DELETE, OnBtnDelete )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_HISTORY, OnBtnHistorical )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// AcctRoundingRuleDlg message handlers
//******************************************************************************

SEVERITY AcctRoundingRuleDlg::doInit()
{
    TRACE_METHOD( CLASSNAME, I_("doInit"));

    return( NO_CONDITION );
}
//******************************************************************************

BOOL AcctRoundingRuleDlg::OnInitDialog() 
{
    TRACE_METHOD( CLASSNAME, ONINITDIALOG );
    BaseMainDlg::OnInitDialog();
    SetDlgCaption();

    return(TRUE);
}

//******************************************************************************

void AcctRoundingRuleDlg::OnPostInitDialog()
{
    TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

    SetUserAccesFunctionCode( UAF::ACCT_ROUNDING_RULE );
    addBtnAddForPermissionCheck( IDC_BTN_ADD, IDC_LV_ROUNDING_RULE );
    addBtnDeleteForPermissionCheck( IDC_BTN_DELETE, IDC_LV_ROUNDING_RULE );

    IFDSListCtrl* ifdsListAcctRoundingRule = 
                  new IFDSAdaptedListCtrl< LVAcctRoundingRuleAdapter >( this, CLASSNAME, IDC_LV_ROUNDING_RULE, 0, CTRLFLAG_DEFAULT, true /*ShowSelAlways*/, true /*ShowConditions*/);
   
    AddIFDSListControl( ifdsListAcctRoundingRule, I_("AcctRoundingRuleList"), IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::AcctRoundingRuleHeadingSet );   	

    AddControl( CTRL_COMBO,
                IDC_CMB_ROUNDING_FLAG,
                IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST,
                ifds::RoundFlg,
                CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                IDC_LV_ROUNDING_RULE );	

	AddControl( CTRL_COMBO,
                IDC_CMB_ROUNDING_RECALC_METHOD,
                IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST,
                ifds::RecalcMthd,
                CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                IDC_LV_ROUNDING_RULE );

	AddControl( CTRL_COMBO,
                IDC_CMB_ROUNDING_UNITS_PRECISION,
                IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST,
                ifds::UnitsPrecisionAcct,
                CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                IDC_LV_ROUNDING_RULE );

    AddControl( CTRL_DATE,
                IDC_DTP_ROUNDING_START_DATE, 
                IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST,
                ifds::StartDate,
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                IDC_LV_ROUNDING_RULE );

	AddControl( CTRL_DATE,
                IDC_DTP_ROUNDING_STOP_DATE, 
                IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST,
                ifds::StopDate,
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                IDC_LV_ROUNDING_RULE ); 

	doRefresh (this, NULL_STRING);   
}

//*****************************************************************************

bool AcctRoundingRuleDlg::doRefresh( GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
    TRACE_METHOD( CLASSNAME, I_("doRefresh") );
    
    ConnectListToData( IDC_LV_ROUNDING_RULE, true );
    LoadListControl( IDC_LV_ROUNDING_RULE );

	GetDlgItem( IDC_DTP_ROUNDING_START_DATE )->EnableWindow( false );
	GetDlgItem( IDC_DTP_ROUNDING_STOP_DATE )->EnableWindow( false );

	GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST ) );
   
    return( true );
}

//*******************************************************************************************
bool AcctRoundingRuleDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
{
    dstrOut = I_( "" );

    if( lSubstituteId == ifds::AcctRoundingRuleHeadingSet.getId() )
    {
        if( dstrColumnKey == I_("RoundFlg" ) )
        {
            getParent()->getField( this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::RoundFlg, dstrOut, false );
            return( true );
        }
        else if( dstrColumnKey == I_("RecalcMthd" ) )
        {
            getParent()->getField( this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::RecalcMthd, dstrOut, true );
            return( true );
        }
        else if( dstrColumnKey == I_("UnitsPrecisionAcct" ) )
        {
            getParent()->getField( this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::UnitsPrecisionAcct, dstrOut, true );
            return( true );
        }       
        else if( dstrColumnKey == I_("StartDate" ) )
        {
            getParent()->getField( this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::StartDate, dstrOut, true );
            return( true );
        }
        else if( dstrColumnKey == I_("StopDate" ) )
        {
            getParent()->getField( this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::StopDate, dstrOut, true );
            return( true );
        }
    }

    return( false );
}

//**********************************************************************************
void AcctRoundingRuleDlg::SetDlgCaption()
{
    TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

    DString dstrShrNum, dstrAccountNum, dstrEntityName;

    getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum, false);
    dstrAccountNum.strip().stripLeading('0');

    // Get Entity Name
    if ( !dstrAccountNum.empty() ) 
    {
        dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), dstrAccountNum, dstrEntityName);
    }

    SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
}

//******************************************************************************
void AcctRoundingRuleDlg::DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem )
{
	if( listControlID == IDC_LV_ROUNDING_RULE )
	{
		enableDisableControls();
	}
}

//******************************************************************************
void AcctRoundingRuleDlg::enableDisableControls()
{																					
	GetDlgItem( IDC_DTP_ROUNDING_START_DATE )->EnableWindow( false );
	GetDlgItem( IDC_DTP_ROUNDING_STOP_DATE )->EnableWindow( false );
}

//******************************************************************************
void AcctRoundingRuleDlg::OnBtnAdd() 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnAdd"));

	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdd" ) );

	getParent()->setField( this, IsAcctRoundingRulePendProcTrade, I_( "N" ), false );

	if (GETHIGHESTSEVERITY () >= WARNING)
	{
		ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());	
	}
	if (GETHIGHESTSEVERITY () <= WARNING)
	{
		AddToListControl( IDC_LV_ROUNDING_RULE );
	}

	GetList( IDC_LV_ROUNDING_RULE )->SetFocus();	
}

//******************************************************************************
void AcctRoundingRuleDlg::OnBtnDelete() 
{
    TRACE_METHOD( CLASSNAME, I_("OnBtnDelete"));

	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDelete" ) );

	getParent()->setField( this, IsAcctRoundingRulePendProcTrade, I_( "N" ), false );

	if (GETHIGHESTSEVERITY () >= WARNING)
	{
		ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());	
	}
	if (GETHIGHESTSEVERITY () <= WARNING)
	{
		DeleteFromListControl( IDC_LV_ROUNDING_RULE );
	}	

	GetList( IDC_LV_ROUNDING_RULE )->SetFocus();
}

//********************************************************************************
void AcctRoundingRuleDlg::OnBtnMore()
{
    TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
    CWaitCursor wait;

    SetMessageStatusBar(TXT_LOAD_ACCT_ROUNDING_RULE);

    const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST );

    if( getParent()->performSearch( this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
    {
        LoadListControl( IDC_LV_ROUNDING_RULE, crtKey );      
    }

    SetMessageStatusBar(NULL_STRING);

    GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST ) );
}

//******************************************************************************
void AcctRoundingRuleDlg::OnBtnReset() 
{
    TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));

    ResetListItem( IDC_LV_ROUNDING_RULE );

    GetList( IDC_LV_ROUNDING_RULE )->SetFocus();
}

//******************************************************************************
void AcctRoundingRuleDlg::OnBtnHistorical()
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

    historicalInfo( this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, AUDITTYPE::ACTRDR );
}


