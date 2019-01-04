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
//    Copyright 2004 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   :InvestmentHistoryDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : InvestmentHistoryDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "InvestmentHistoryDlg.h"

#include <assert.h>
#include <configmanager.hpp>

#include <configmanager.hpp>
#include <uibase\ifdslistctrl.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstgridwnd.h>
#include <uibase\DSTEdit.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\InvestmentHistoryProcessIncludes.h>
#include <ifastbp\InvestmentHistoryProcess.hpp>
#include <ifastbp\ProgressiveIntRateProcessIncludes.h>
#include <ifastbp\ProgressiveIntRateProcess.hpp>
#include <ifastbp\InterestSegmentProcessIncludes.h>
#include <ifastbp\InterestSegmentProcess.hpp>
#include <ifastbp\FundClassProcessIncludes.h>

#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\Entity.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\dstcommonfunction.hpp>

#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>


#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

#ifndef DSTCOMBOBOX_H
   #include <uibase\DSTComboBox.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_INVESTMENT_HISTORY_LIST;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< InvestmentHistoryDlg > dlgCreator( CMD_GUI_INVESTMENT_HISTORY_LIST ); 

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PROGRESSIVE_INTEREST_RATE_LIST;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INTEREST_SEGMENT_LIST;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MATSWP_INSTRUCTIONS;

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME						= I_( "InvestmentHistoryDlg" );
   const I_CHAR * const CALLER							= I_( "Caller" );
   const I_CHAR * const INV_HISTORY						= I_( "InvHistory" );
   const I_CHAR * const INSTR_TYPE						= I_( "InstrType" );
   const I_CHAR * const MATURITY_INSTR					= I_( "MAT" );
   const I_CHAR * LV_INVESTMENT_HISTORY_LIST			= I_( "Investment History List" );			//For Grid 1
   const I_CHAR * LV_INVESTMENT_HISTORY_TRAN_LIST		= I_( "Investment History Details List" );	//For Grid 2
   const I_CHAR * LV_INVESTMENT_HISTORY_INTEREST_LIST	= I_( "Investment History Interest List" ); //For Grid 3
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const INVESTMENT_HISTORY_LIST;
   extern CLASS_IMPORT I_CHAR * const INTEREST_MAINTENANCE;
}

namespace CND //Conditions used
{  
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
   extern const long GUI_ERR_DATA_NOT_FOUND;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryDetailsList;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryDetailsTranList;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryDetailsIntList;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryFund;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryClass;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryNumber;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistorySearch;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryStatus;
	extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
}
//*****************************************************************************
// class LVInvestmentHistoryData methods
//*****************************************************************************
void LVInvestmentHistoryData::update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
{
    pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisNumber, dstrInvHisNumber); 
	dstrInvHisNumber.strip();
    pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisStatus, dstrInvHisStatus); 
	dstrInvHisStatus.strip();
    pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisIntCalcMthd, dstrInvHisIntCalcMthd); 
	dstrInvHisIntCalcMthd.strip();
    pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisIntRateType, dstrInvHisIntRateType); 
	dstrInvHisIntRateType.strip();
    pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisTerm, dstrInvHisTerm); 
	dstrInvHisTerm.strip();
    pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisIntRate, dstrInvHisIntRate); 
	dstrInvHisIntRate.strip();
	pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisDepDate, dstrInvHisDepDate); 
	dstrInvHisDepDate.strip();
	pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisMatDate, dstrInvHisMatDate); 
	dstrInvHisMatDate.strip();
	pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisPrincipal, dstrInvHisPrincipal); 
	dstrInvHisPrincipal.strip();
	pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisIntFreq, dstrInvHisIntFreq); 
	dstrInvHisIntFreq.strip();
	pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisCurMktVal, dstrInvHisCurMktVal); 
	dstrInvHisCurMktVal.strip();
	pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisLastIntCrdDate, dstrInvHisLastIntCrdDate);
	dstrInvHisLastIntCrdDate.strip();
	pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::InvHisAcurdToDate, dstrInvHisAcurdToDate); 
	dstrInvHisAcurdToDate.strip();
	pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::IntRateType, dstrIntRateType); 
	dstrIntRateType.strip();
	pDlg->getParent()->getField(pDlg, BF::NullContainerId, ifds::AddlAmt, dstrAddlAmt); 
	dstrAddlAmt.strip();
}//end of void update

//*****************************************************************************
// class LVInvestmentHistoryAdapter methods
//*****************************************************************************
int LVInvestmentHistoryAdapter::compare(	IFDSListBase* pCtrl, int iSortColumn, bool bAscending, 
											RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2 )
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
      else if (*pFieldId == ifds::InvHisNumber) 
      {
		result = i_strcmp(pData1->dstrInvHisNumber.c_str(), pData2->dstrInvHisNumber.c_str());
      } 
      else if (*pFieldId == ifds::InvHisStatus) 
      {
		result = i_strcmp(pData1->dstrInvHisStatus.c_str(), pData2->dstrInvHisStatus.c_str());
      } 
      else if (*pFieldId == ifds::InvHisIntCalcMthd) 
      {
		result = i_strcmp(pData1->dstrInvHisIntCalcMthd.c_str(), pData2->dstrInvHisIntCalcMthd.c_str());
      } 
      else if (*pFieldId == ifds::InvHisIntRateType) 
      {
		result = i_strcmp(pData1->dstrInvHisIntRateType.c_str(), pData2->dstrInvHisIntRateType.c_str());
      } 
      else if(*pFieldId == ifds::InvHisTerm)
	  {
		result = i_strcmp(pData1->dstrInvHisTerm.c_str(), pData2->dstrInvHisTerm.c_str());
	  }
	  else if(*pFieldId == ifds::InvHisIntRate) 
	  {
		result = i_strcmp( pData1->dstrInvHisIntRate.c_str(), pData2->dstrInvHisIntRate.c_str() );
	  }
      else if (*pFieldId == ifds::InvHisDepDate) 
      {
		if ( DSTCommonFunctions::CompareDates( pData1->dstrInvHisDepDate.c_str(), pData2->dstrInvHisDepDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
			result = -1;
		else if ( DSTCommonFunctions::CompareDates( pData2->dstrInvHisDepDate.c_str(), pData1->dstrInvHisDepDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
			result = 1;
      }
	  else if (*pFieldId == ifds::InvHisMatDate)
      {
		if ( DSTCommonFunctions::CompareDates( pData1->dstrInvHisMatDate.c_str(), pData2->dstrInvHisMatDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
			result = -1;
		else if ( DSTCommonFunctions::CompareDates( pData2->dstrInvHisMatDate.c_str(), pData1->dstrInvHisMatDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
			result = 1;
      }
	  else if (*pFieldId == ifds::InvHisPrincipal)
      {
         result = i_strcmp(pData1->dstrInvHisPrincipal.c_str(), pData2->dstrInvHisPrincipal.c_str());
      }
	  else if (*pFieldId == ifds::InvHisIntFreq)
	  {
		result = i_strcmp(pData1->dstrInvHisIntFreq.c_str(), pData2->dstrInvHisIntFreq.c_str());
	  }
	  else if (*pFieldId == ifds::InvHisCurMktVal)
	  {
		result = i_strcmp(pData1->dstrInvHisCurMktVal.c_str(), pData2->dstrInvHisCurMktVal.c_str());
	  }
	  else if (*pFieldId == ifds::InvHisLastIntCrdDate)
	  {
		if ( DSTCommonFunctions::CompareDates( pData1->dstrInvHisLastIntCrdDate.c_str(), pData2->dstrInvHisLastIntCrdDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
			result = -1;
		else if ( DSTCommonFunctions::CompareDates( pData2->dstrInvHisLastIntCrdDate.c_str(), pData1->dstrInvHisLastIntCrdDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
			result = 1;
	  }
	  else if (*pFieldId == ifds::InvHisAcurdToDate)
	  {
		result = i_strcmp(pData1->dstrInvHisAcurdToDate.c_str(), pData2->dstrInvHisAcurdToDate.c_str());
	  }
	  else if (*pFieldId == ifds::IntRateType)
	  {
		result = i_strcmp(pData1->dstrIntRateType.c_str(), pData2->dstrIntRateType.c_str());
	  }
	  else if (*pFieldId == ifds::AddlAmt)
	  {
		result = i_strcmp(pData1->dstrAddlAmt.c_str(), pData2->dstrAddlAmt.c_str());
	  }
	  
      return (bAscending ? result : -result);

} //end of int compare
//*****************************************************************************
LRESULT LVInvestmentHistoryAdapter::onGetDispInfo(IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo)
{
    if (pDispInfo->item.mask & LVIF_TEXT)
    {
        const BFFieldId* pFieldId = pCtrl->getColumnField(pDispInfo->item.iSubItem);
        if (NULL == pFieldId)
        {
			pDispInfo->item.pszText = I_("");
        }
        else if (*pFieldId == ifds::InvHisNumber)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisNumber.c_str();
        } 
        else if (*pFieldId == ifds::InvHisStatus)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisStatus.c_str();
        } 
        else if (*pFieldId == ifds::InvHisIntCalcMthd)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisIntCalcMthd.c_str();
        } 
        else if (*pFieldId == ifds::InvHisIntRateType)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisIntRateType.c_str();
        } 
        else if( *pFieldId == ifds::InvHisTerm)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisTerm.c_str();
        }
        else if( *pFieldId == ifds::InvHisIntRate)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisIntRate.c_str();
        }
        else if (*pFieldId == ifds::InvHisDepDate) 
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisDepDate.c_str();
        }
		else if (*pFieldId == ifds::InvHisMatDate) 
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisMatDate.c_str();
        }
		else if (*pFieldId == ifds::InvHisPrincipal)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisPrincipal.c_str();
        }
		else if (*pFieldId == ifds::InvHisIntFreq)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisIntFreq.c_str();
        }
		else if (*pFieldId == ifds::InvHisCurMktVal)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisCurMktVal.c_str();
        }
		else if (*pFieldId == ifds::InvHisLastIntCrdDate)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisLastIntCrdDate.c_str();
        }
		else if (*pFieldId == ifds::InvHisAcurdToDate)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrInvHisAcurdToDate.c_str();
        }
		else if (*pFieldId == ifds::IntRateType)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrIntRateType.c_str();
        }
		else if (*pFieldId == ifds::AddlAmt)
        {
			pDispInfo->item.pszText = (I_CHAR*)pData->dstrAddlAmt.c_str();
        }

        return 1;

    }// end of if (pDispInfo->item.mask & LVIF_TEXT)

    return 0;

}//end of LRESULT onGetDispInfo

//*****************************************************************************
// Public methods
//*****************************************************************************
InvestmentHistoryDlg::InvestmentHistoryDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( InvestmentHistoryDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_uiClassCodeDialogItem (0)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(InvestmentHistoryDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void InvestmentHistoryDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(InvestmentHistoryDlg)
   
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(InvestmentHistoryDlg, BaseMainDlg)
//{{AFX_MSG_MAP(InvestmentHistoryDlg)
ON_BN_CLICKED(IDC_BTN_MATURITY_INT_INSTR, OnBtnMaturityInt)
ON_BN_CLICKED(IDC_BTN_PROGRESSIVE_INT_RATE, OnBtnProgressiveInt)
ON_BN_CLICKED(IDC_BTN_INT_SEGMENT, OnBtnIntSegments)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_MORE_DETAILS, OnBtnMoreDetails)
ON_BN_CLICKED(IDC_BTN_MORE_INTEREST, OnBtnMoreInterest)
ON_BN_CLICKED(IDC_BTN_IHREFRESH, OnBtnRefresh)
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
//}}AFX_MSG_MAP

END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
namespace INVEST_CONTROLS
{
//group of controls with fields part of a trade object 
   const UINT GRP_SEARCH = 1;
};

BOOL InvestmentHistoryDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog();

	IFDSListCtrl* pInvestmentHistoryList = 
      new IFDSAdaptedListCtrl<LVInvestmentHistoryAdapter>(this, CLASSNAME, IDC_LV_INVEST_HISTORY_PARENT_LIST, 0, LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE, true /*ShowSelAlways*/, true /*ShowConditions*/);

	AddIFDSListControl(pInvestmentHistoryList, LV_INVESTMENT_HISTORY_LIST, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvestmentHistoryDetailsList);

	//				DlgName		ListControlID						listName								idSubstitute							idContainer
	/*
	AddListControl (CLASSNAME, IDC_LV_INVEST_HISTORY_PARENT_LIST,   LV_INVESTMENT_HISTORY_LIST,				ifds::InvestmentHistoryDetailsList,		IFASTBP_PROC::INVESTMENT_HISTORY_LIST);
	*/
	AddListControl (CLASSNAME, IDC_LV_INVEST_HISTORY_CHILD_LIST,    LV_INVESTMENT_HISTORY_TRAN_LIST,		ifds::InvestmentHistoryDetailsTranList, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST, IDC_LV_INVEST_HISTORY_PARENT_LIST, true, LISTFLAG_NOT_AUTO_ADD);
	AddListControl (CLASSNAME, IDC_LV_INVEST_HISTORY_INTEREST_LIST, LV_INVESTMENT_HISTORY_INTEREST_LIST,	ifds::InvestmentHistoryDetailsIntList,	IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST, IDC_LV_INVEST_HISTORY_PARENT_LIST, true, LISTFLAG_NOT_AUTO_ADD);

	AddControl (CTRL_EDIT, IDC_EDT_FUND_NUM,	
		INVESTMENT_HISTORY_SEARCH, ifds::FromFundNumber,			CTRLFLAG_DEFAULT, INVEST_CONTROLS::GRP_SEARCH);

	AddControl (CTRL_EDIT,  IDC_EDT_FUND,			
		INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryFund,		CTRLFLAG_DEFAULT, INVEST_CONTROLS::GRP_SEARCH);

	AddControl (CTRL_EDIT,  IDC_EDT_CLASS,			
		INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryClass,	CTRLFLAG_DEFAULT, INVEST_CONTROLS::GRP_SEARCH);

	AddControl (CTRL_EDIT,  IDC_EDT_INVEST_NUMBER,	
		INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryNumber,	CTRLFLAG_DEFAULT, INVEST_CONTROLS::GRP_SEARCH);

	AddControl (CTRL_COMBO, IDC_CMB_SEARCH,			
		INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistorySearch,	CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST, INVEST_CONTROLS::GRP_SEARCH);

	AddControl (CTRL_COMBO, IDC_CMB_INVEST_STATUS,	
		INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryStatus,	CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST, INVEST_CONTROLS::GRP_SEARCH);

	((CEdit*)GetDlgItem(IDC_EDT_INVEST_NUMBER))->ShowWindow(SW_HIDE);
	((CStatic*)GetDlgItem(IDC_STC_INV_NUM))->ShowWindow(SW_HIDE);

	((CComboBox*)GetDlgItem(IDC_CMB_INVEST_STATUS))->ShowWindow(SW_HIDE);
	((CStatic*)GetDlgItem(IDC_STC_INV_STATUS))->ShowWindow(SW_HIDE);

	UpdateData(FALSE);

	return TRUE;
}

//******************************************************************************
void InvestmentHistoryDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	SetUserAccesFunctionCode (UAF::INVESTMENT_HISTORY_LIST);
	addControlGroupIDForPermissionCheck (IDC_LV_INVEST_HISTORY_PARENT_LIST);

	doRefresh (this, I_("InitDlg"));
}

//*****************************************************************************
bool InvestmentHistoryDlg::doRefresh ( GenericInterface * rpGICaller, 
									   const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

	SetAccount( m_dstrAccountNum );
	SetDlgCaption();

	ConnectListToData (IDC_LV_INVEST_HISTORY_PARENT_LIST, true);
	ConnectListToData (IDC_LV_INVEST_HISTORY_CHILD_LIST, true);
	ConnectListToData (IDC_LV_INVEST_HISTORY_INTEREST_LIST, true);

	ConnectControlsToData (INVEST_CONTROLS::GRP_SEARCH, true);

	LoadControls (INVEST_CONTROLS::GRP_SEARCH);

	if (DString (szOriginalCommand) != NULL_STRING)
	{
		GetDlgItem (IDC_BTN_MORE)->EnableWindow (FALSE);
      GetDlgItem (IDC_BTN_MORE_DETAILS)->EnableWindow (FALSE);
      GetDlgItem (IDC_BTN_MORE_INTEREST)->EnableWindow (FALSE);
		GetDlgItem (IDC_BTN_PROGRESSIVE_INT_RATE)->EnableWindow (FALSE);
		GetDlgItem (IDC_BTN_INT_SEGMENT)->EnableWindow (FALSE);

		enableMaturityInstrs (true);
	}

	return true;
}

//**********************************************************************************
void InvestmentHistoryDlg::SetDlgCaption()
{
	TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

    DString dstrShrNum, 
		    dstrEntityName;

	//Get Entity Name
	if ( !m_dstrAccountNum.empty() ) 
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
         getDataGroupId(), m_dstrAccountNum, dstrEntityName);

	SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);
}

//*****************************************************************************
SEVERITY InvestmentHistoryDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

    getParameter (INVHISTORYPROC::ACCOUNT_NUM_VALUE, m_dstrAccountNum);

	return NO_CONDITION;
}

//*****************************************************************************
void InvestmentHistoryDlg::DoListItemChanged ( UINT listControlID,
											   const DString &strKey, 
											   bool isNewItem,
											   bool bIsDummyItem)
{  
   switch (listControlID)
   {
      case IDC_LV_INVEST_HISTORY_PARENT_LIST:
		  {
			 DString dstrRateType = NULL_STRING;
			 getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvHisIntRateType, dstrRateType, false);

			 GetDlgItem (IDC_BTN_PROGRESSIVE_INT_RATE)->EnableWindow ( dstrRateType == I_("P") );

			 DString dstrIntRateType = NULL_STRING;
			 getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::IntRateType, dstrIntRateType, false);
			 GetDlgItem (IDC_BTN_INT_SEGMENT)->EnableWindow ( (dstrIntRateType == I_("1")) || (dstrIntRateType == I_("2")) );

			 GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent()->doMoreRecordsExist (this, 
					IFASTBP_PROC::INVESTMENT_HISTORY_LIST));

			 GetDlgItem (IDC_CMB_SEARCH)->EnableWindow(FALSE);

			 enableMaturityInstrs (bIsDummyItem);

			 break;
		  }
      case IDC_LV_INVEST_HISTORY_CHILD_LIST:
         GetDlgItem (IDC_BTN_MORE_DETAILS)->
             EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST));
         break;

      case IDC_LV_INVEST_HISTORY_INTEREST_LIST:
         GetDlgItem (IDC_BTN_MORE_INTEREST)->
             EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST));
         break;

	  default:
		  break;
   }
}
//*****************************************************************************
void InvestmentHistoryDlg::ControlUpdated (UINT controlID, const DString &strValue)
{
   switch (controlID)
   {  
	 case IDC_CMB_SEARCH:
		 {
			 bool bFlag = strValue == I_("ALL");
			
			 if(bFlag)
			 {
				DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>(GetDlgItem(IDC_CMB_SEARCH));
				pComboBox->SetCurSel( pComboBox->SelectString(-1, I_("All")) );

				ConnectControl( IDC_CMB_SEARCH, true );
				GetControl( IDC_CMB_SEARCH )->ConnectToData( true );
			 }

			 ((CEdit*)GetDlgItem(IDC_EDT_INVEST_NUMBER))->ShowWindow( (!bFlag && strValue == I_("INVNUM")) ? SW_SHOW : SW_HIDE);
			 ((CStatic*)GetDlgItem(IDC_STC_INV_NUM))->ShowWindow( (!bFlag && strValue == I_("INVNUM")) ? SW_SHOW : SW_HIDE);

			 ((CComboBox*)GetDlgItem(IDC_CMB_INVEST_STATUS))->ShowWindow( (!bFlag && strValue == I_("INVSTAT")) ? SW_SHOW : SW_HIDE);
			 ((CStatic*)GetDlgItem(IDC_STC_INV_STATUS))->ShowWindow( (!bFlag && strValue == I_("INVSTAT")) ? SW_SHOW : SW_HIDE);

			 getParent()->setField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryNumber, I_(""), false);
			 getParent()->setField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryStatus, I_(""), false);

			 GetControl( IDC_EDT_INVEST_NUMBER )->Clear(); //ClearErrorState();
			 GetControl( IDC_CMB_INVEST_STATUS )->Clear(); //ClearErrorState();

			break;
		 }
			
      default:
         break;
   }
}

//*****************************************************************************
void InvestmentHistoryDlg::OnBtnMore ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnMore"));
	
	CWaitCursor wait;

	if (getParent()->performSearch (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, SEARCH_NEXT_BLOCK) <= WARNING)
	{
		LoadListControl(IDC_LV_INVEST_HISTORY_PARENT_LIST);
		GetDlgItem(IDC_BTN_MORE)->EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST));
	}
	else
	{
		// Display error
		ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
	}
}
//*****************************************************************************
void InvestmentHistoryDlg::OnBtnMoreDetails ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnMore"));
	
	CWaitCursor wait;

	if (getParent()->performSearch (this, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST, SEARCH_NEXT_BLOCK) <= WARNING)
	{
		LoadListControl(IDC_LV_INVEST_HISTORY_CHILD_LIST);
		GetDlgItem(IDC_BTN_MORE_DETAILS)->
         EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST));
	}
	else
	{
		// Display error
		ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
	}
}
//*****************************************************************************
void InvestmentHistoryDlg::OnBtnMoreInterest ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnMore"));
	
	CWaitCursor wait;

	if (getParent()->performSearch (this, IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST, SEARCH_NEXT_BLOCK) <= WARNING)
	{
      LoadListControl(IDC_LV_INVEST_HISTORY_INTEREST_LIST);
      GetDlgItem(IDC_BTN_MORE_INTEREST)->
         EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST));
	}
	else
	{
		// Display error
		ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
	}
}
//**********************************************************************************
void InvestmentHistoryDlg::enableMaturityInstrs (bool bIsDummyItem)
{
	bool bEnable = false;

	int iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST);

	if ((iItemNumber == 1 && !bIsDummyItem) || iItemNumber > 1)
	{
		bEnable= true;
	}
	
	GetDlgItem (IDC_BTN_MATURITY_INT_INSTR)->EnableWindow (bEnable);
}
//*******************************************************************************
// Function Description:
// IsInputFieldsEmpty() method checks if the Investment Number or Status input
// values are empty, if they are empty it pops up a message box.
// These validations would be moved to CBO.
//
//
//*******************************************************************************
bool InvestmentHistoryDlg::IsInputFieldsEmpty()
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("IsInputFieldsEmpty"));

	ConnectControl( IDC_EDT_FUND, true );
	GetControl( IDC_EDT_FUND )->ConnectToData( true );
	GetControl( IDC_EDT_FUND )->Store();
	SEVERITY sevRtn = GetControl(IDC_EDT_FUND)->GetErrorState();
	if ( sevRtn >= WARNING )
	{
		GetControl( IDC_EDT_FUND )->ShowIndicator(); //Fix for indicator not showing up for the first time.
		GetDlgItem(IDC_EDT_FUND)->SetFocus();
		return false;
	}

	ConnectControl( IDC_EDT_CLASS, true );
	GetControl( IDC_EDT_CLASS )->ConnectToData( true );
	GetControl( IDC_EDT_CLASS )->Store();
	sevRtn = GetControl(IDC_EDT_CLASS)->GetErrorState();
	if ( sevRtn >= WARNING )
	{
		GetControl( IDC_EDT_CLASS )->ShowIndicator(); //Fix for indicator not showing up for the first time.
		GetDlgItem(IDC_EDT_CLASS)->SetFocus();
		return false;
	}

	CString sSearchRes;
	((CComboBox*)GetDlgItem(IDC_CMB_SEARCH))->GetWindowText(sSearchRes);

   	//Check if Investment Status or Number are empty
	if( sSearchRes != I_("All") )
	{
		CString sErrMsg;
		if( ((CEdit*)GetDlgItem(IDC_EDT_INVEST_NUMBER))->IsWindowVisible() )
		{
			ConnectControl( IDC_EDT_INVEST_NUMBER, true );
			GetControl( IDC_EDT_INVEST_NUMBER )->ConnectToData( true );
			GetControl( IDC_EDT_INVEST_NUMBER )->Store();
			sevRtn = GetControl(IDC_EDT_INVEST_NUMBER)->GetErrorState();
			if ( sevRtn >= WARNING )
			{
				GetControl( IDC_EDT_INVEST_NUMBER )->ShowIndicator(); //Fix for indicator not showing up for the first time.
				GetDlgItem(IDC_EDT_INVEST_NUMBER)->SetFocus();
				return false;
			}
		}
		else if ( ((CComboBox*)GetDlgItem(IDC_CMB_INVEST_STATUS))->IsWindowVisible() )
		{
			ConnectControl( IDC_CMB_INVEST_STATUS, true );
			GetControl( IDC_CMB_INVEST_STATUS )->ConnectToData( true );
			GetControl( IDC_CMB_INVEST_STATUS )->Store();
			sevRtn = GetControl(IDC_CMB_INVEST_STATUS)->GetErrorState();
			if ( sevRtn >= WARNING )
			{
				GetControl( IDC_CMB_INVEST_STATUS )->ShowIndicator(); //Fix for indicator not showing up for the first time.
				GetDlgItem(IDC_CMB_INVEST_STATUS)->SetFocus();
				return false;
			}
		}

	} //end of if( sSearchRes != I_("All") )

	return true;
}

//*****************************************************************************
void InvestmentHistoryDlg::OnBtnSearch()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnSearch"));

   CWaitCursor wait;

	try
	{
		if(!IsInputFieldsEmpty())
			return;

		DString strSearch, strFund, strClass, strStatus, strInvNum;
		getParent()->getField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistorySearch, strSearch, false);
		getParent()->getField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryFund, strFund, false);
		getParent()->getField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryClass, strClass, false);
		getParent()->getField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryStatus, strStatus, false);
		getParent()->getField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryNumber, strInvNum, false);

		setParameter (INVHISTORYPROC::FUND, strFund);
		setParameter (INVHISTORYPROC::CLASS, strClass);
		setParameter (INVHISTORYPROC::INV_NUM, strInvNum);
		setParameter (INVHISTORYPROC::INV_STATUS, strStatus);
		setParameter (INVHISTORYPROC::SEARCHBY, strSearch);
		setParameter (INVHISTORYPROC::TRANS_ID_VALUE, NULL_STRING);

		GenericInterface* pParent = getParent();
		if (pParent->performSearch (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, SEARCH_START) <= WARNING)
		{
			LoadListControl (IDC_LV_INVEST_HISTORY_PARENT_LIST);

			int numListItems = GetList( IDC_LV_INVEST_HISTORY_PARENT_LIST )->GetItemCount();
			EnableControls(numListItems == 0 ? TRUE : FALSE);
			
			if(numListItems == 0)
			{
				setParameter (INVHISTORYPROC::FUND, I_(""));
				setParameter (INVHISTORYPROC::CLASS, I_(""));
				pParent->clearParameters();
				GetDlgItem(IDC_EDT_FUND)->SetFocus();
			}
		}
		else
		{
			// Display error
			ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());

			EnableControls(TRUE);
		}

	}//end of try
	catch (ConditionException &ce)
	{
		ConditionMessageBox (ce);
	}
	catch (...)
	{
		DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
	}
}

//******************************************************************************
void InvestmentHistoryDlg::OnBtnProgressiveInt()
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnProgressiveInt"));
	
	DString strAcctNum,
			strInvestID;

	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvHisInvestId, strInvestID, false);
	setParameter (INVHISTORYPROC::ACCOUNT_NUM_VALUE, m_dstrAccountNum);
	setParameter (INVHISTORYPROC::INVEST_ID, strInvestID);
	
	invokeCommand( getParent(), CMD_BPROC_PROGRESSIVE_INTEREST_RATE_LIST, PROC_NO_TYPE, false, NULL );
	SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void InvestmentHistoryDlg::OnBtnIntSegments()
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnIntSegments"));
	
	DString strAcctNum,
			strInvestID;
	
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvHisInvestId, strInvestID, false);
	setParameter (INVHISTORYPROC::ACCOUNT_NUM_VALUE, m_dstrAccountNum);
	setParameter (INVHISTORYPROC::INVEST_ID, strInvestID);
	
	invokeCommand( getParent(), CMD_BPROC_INTEREST_SEGMENT_LIST, PROC_NO_TYPE, false, NULL );
	SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void InvestmentHistoryDlg::EnableControls(BOOL bEnable)
{
	((CButton*)GetDlgItem(IDC_BTN_SEARCH))->EnableWindow(bEnable);
	
	((CEdit*)GetDlgItem(IDC_EDT_FUND))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDT_FUND_NUM))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDT_CLASS))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDT_INVEST_NUMBER))->EnableWindow(bEnable);

	((CComboBox*)GetDlgItem(IDC_CMB_SEARCH))->EnableWindow(bEnable);
	((CComboBox*)GetDlgItem(IDC_CMB_INVEST_STATUS))->EnableWindow(bEnable);
}

//******************************************************************************
void InvestmentHistoryDlg::OnBtnRefresh()
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnRefresh"));

	SetControlText (IDC_EDT_FUND_NUM, I_(""), false);
	GetControl( IDC_EDT_FUND_NUM )->ClearErrorState();

	SetControlText (IDC_EDT_FUND, I_(""), false);
	GetControl( IDC_EDT_FUND )->ClearErrorState();
	
	SetControlText (IDC_EDT_CLASS, I_(""), false);
	GetControl( IDC_EDT_CLASS )->ClearErrorState();

	SetControlText (IDC_EDT_INVEST_NUMBER, I_(""), false);

	getParent()->setField (this, INVESTMENT_HISTORY_SEARCH, ifds::FromFundNumber, I_(""), false);
	getParent()->setField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryFund, I_(""), false);
	getParent()->setField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryClass, I_(""), false);
	getParent()->setField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistorySearch, I_("All"), false);
	getParent()->setField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryNumber, I_(""), false);
	getParent()->setField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryStatus, I_(""), false);

	//Reset the values of Status since it is a refresh..
	DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>( GetDlgItem(IDC_CMB_INVEST_STATUS) );
	pComboBox->SetCurSel(-1);
	
	ConnectControl( IDC_CMB_INVEST_STATUS, true );
	GetControl( IDC_CMB_INVEST_STATUS )->ConnectToData( true );
	GetControl( IDC_CMB_INVEST_STATUS )->ClearErrorState();

	ConnectControl( IDC_EDT_INVEST_NUMBER, true );
	GetControl( IDC_EDT_INVEST_NUMBER )->ConnectToData( true );
	GetControl( IDC_EDT_INVEST_NUMBER )->ClearErrorState();

	EnableControls(TRUE);

	GetDlgItem (IDC_BTN_PROGRESSIVE_INT_RATE)->EnableWindow (FALSE);
	GetDlgItem (IDC_BTN_INT_SEGMENT)->EnableWindow (FALSE);

	ResetListItem ( IDC_LV_INVEST_HISTORY_PARENT_LIST );

	ConnectListToData ( IDC_LV_INVEST_HISTORY_PARENT_LIST, false);
	ConnectListToData ( IDC_LV_INVEST_HISTORY_CHILD_LIST, false);
	ConnectListToData ( IDC_LV_INVEST_HISTORY_INTEREST_LIST, false);

	doRefresh (this, I_("Refresh"));	

	ControlUpdated(IDC_CMB_SEARCH, I_("ALL"));

	GetDlgItem(IDC_EDT_FUND)->SetFocus();
}

//******************************************************************************
void InvestmentHistoryDlg::OnBtnMaturityInt()
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnMaturityInt"));

	DString strFund, strClass, strTransId, strInvId, strTransNum, strInvHisMarketValue, strInvHisAcurdToDate;	
	DString strCalcMthd, strRateType, strTerm, strIntFreq, strInvHisStatus;

	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::Fund, strFund, false);
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::Class, strClass, false);
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::TransNum, strTransNum, false);
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::TransId, strTransId, false);
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvHisInvestId, strInvId, false);
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvHisCurMktVal, strInvHisMarketValue, false);
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvHisAcurdToDate, strInvHisAcurdToDate, false);
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvHisIntCalcMthd, strCalcMthd, false);
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvHisIntRateType, strRateType, false);
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvHisTerm, strTerm, false);
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvHisIntFreq, strIntFreq, false);
	getParent()->getField (this, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, ifds::InvHisStatus, strInvHisStatus, false);
	
	setParameter (INVHISTORYPROC::FUND, strFund);
	setParameter (INVHISTORYPROC::CLASS, strClass);
	setParameter (INVHISTORYPROC::TRANS_NUM, strTransNum);
	setParameter (INVHISTORYPROC::TRANS_ID_VALUE, strTransId);
	setParameter (INVHISTORYPROC::INVEST_ID, strInvId);
	setParameter (INVHISTORYPROC::INV_PRINCIPAL, strInvHisMarketValue);
	setParameter (INVHISTORYPROC::INV_ACCRUED, strInvHisAcurdToDate);

	setParameter (INVHISTORYPROC::CALC_METHOD, strCalcMthd);
	setParameter (INVHISTORYPROC::INV_TYPE, strRateType);
	setParameter (INVHISTORYPROC::TERM, strTerm);
	setParameter (INVHISTORYPROC::FREQEUNCY, strIntFreq);
	setParameter (INVHISTORYPROC::INV_STATUS, strInvHisStatus);
	
	setParameter (CALLER, INV_HISTORY); 
	setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNum);
	setParameter (INSTR_TYPE, MATURITY_INSTR);
	setParameter (MFCAN_IP_PARAM::RESET, I_("Y"));

	invokeCommand (getParent(), CMD_BPROC_MATSWP_INSTRUCTIONS, PROC_NO_TYPE, false, NULL);
}

//******************************************************************************
BOOL InvestmentHistoryDlg::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN &&
		(int) (pMsg->wParam) == VK_F4 )
	{
		if( GetFocus() == GetDlgItem(IDC_EDT_FUND) )
		{
			PostMessage( UM_OPENFUNDCLASSLISTDLG );
			m_uiClassCodeDialogItem = IDC_EDT_FUND;
		}
		else if( GetFocus() == GetDlgItem(IDC_EDT_CLASS) )
		{
			PostMessage( UM_OPENFUNDCLASSLISTDLG );
			m_uiClassCodeDialogItem = IDC_EDT_CLASS;
		}
	}

	return BaseMainDlg::PreTranslateMessage (pMsg);
}

//******************************************************************************
LRESULT InvestmentHistoryDlg::OpenFundClassListDlg (WPARAM wParam, LPARAM lParam)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenFundClassListDlg") );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      CWaitCursor wait;

	  /*
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, m_dstrAccountNum);
	  m_dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
	  */

	  //Set Account Number
	  setParameter( FUNDCLASSLIST::ACCT_NUM, m_dstrAccountNum );

      setParameter( INVHISTORYPROC::FUND, NULL_STRING );
      setParameter( INVHISTORYPROC::CLASS, NULL_STRING );
	  
      switch( GetFocus()->GetDlgCtrlID() )
      {
         case IDC_EDT_FUND:
			{
				CString cstrFundCode;
				GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundCode );
				DString dstrFundCode = cstrFundCode;
				setParameter( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
				setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
			}
            break;

         case IDC_EDT_CLASS:
			{
				CString cstrFundClass;
				GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundClass );
				DString dstrFundClass = cstrFundClass;
				setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
				setParameter( FUNDCLASSLIST::CLASS_CODE, dstrFundClass );
			}
            break;
      }

      eRtn = invokeCommand(getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL);

      switch (eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode;
               getParameter ( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               getParameter ( FUNDCLASSLIST::CLASS_CODE, dstrClassCode );

			   getParent()->setField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryFund, dstrFundCode);
			   getParent()->setField (this, INVESTMENT_HISTORY_SEARCH, ifds::InvestmentHistoryClass, dstrClassCode);

               LoadControl( IDC_EDT_FUND );
               LoadControl( IDC_EDT_CLASS );
               break;
            }

         case CMD_CANCEL:
            break;

         default:
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;

      }//end of eRtn
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

   return (0);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/InvestmentHistoryDlg.cpp-arc  $
// 
//    Rev 1.24   Jul 17 2012 15:04:42   kitticha
// IN#2932057 - User should not be able to maintain the instruction when investment is matured.
// 
//    Rev 1.23   Jul 06 2012 05:17:34   kitticha
// IN2932057 - Display the additional amount for investment history.
// 
//    Rev 1.22   May 14 2012 18:28:38   wp040100
// IN 2886441 - Included BayCom/Fund Number 
// 1. Cash Sweep Screen.
// 2. Maturity Interest Instructions Screen.
// 3. GI investment Histroy Screen.
// 
//    Rev 1.21   Apr 18 2012 15:30:36   wp040100
// IN # 2891939 - Added "Forced Indicator" column in Grid 1 and "Status" in Grid 3.
// 
//    Rev 1.20   Apr 13 2012 15:05:20   jankovii
// IN 2892108 - SOC 63 - Combine Principal and Interest for instructions “Maturity and Interest”
// 
//    Rev 1.19   Apr 05 2012 14:13:26   jankovii
// IN 2904085 - Automatin Instructions - For reinvestment, the destination fileds s/s pre-popula
// 
//    Rev 1.18   Mar 28 2012 18:51:38   wp040100
// P0186477 FN03 - GIA - Investment History Changes -Enable sorting for InvHisAcurdToDate.
// 
//    Rev 1.17   Mar 05 2012 11:16:52   jankovii
// IN 2859411 - P0186477_FN02_Interest Instruction-Err displayed on split type 'Amount' instrctn
// 
//    Rev 1.16   Feb 28 2012 11:56:14   jankovii
// IN 2861935 - Maturity_Interest Screen issues
// 
//    Rev 1.15   Feb 22 2012 09:15:44   if991250
// cleaning the Maturity Instructions list from MFAccount
// 
//    Rev 1.14   Feb 16 2012 12:00:50   jankovii
// Disabled maturity button when there are no records.
// 
//    Rev 1.13   Feb 03 2012 10:42:36   jankovii
// IN 2813743 - P0186477FN03- Can't Access Maturity Instructions thru Investment Hist
// 
//    Rev 1.12   Jan 26 2012 20:29:16   wp040100
// IN 2817749 - P0186477 FN03 - GIA Investment History - Error Handling
// 
//    Rev 1.11   Jan 13 2012 10:48:40   wp040100
// P0186477/FN03 - GIA - Investment History Changes - Bug fixes.
// 
//    Rev 1.10   Dec 19 2011 18:22:54   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.9   Dec 14 2011 21:47:18   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.8   Dec 12 2011 18:25:40   wp040100
// P0186477/FN03 - GIA - Investment History - Integrated Fund Search
// 
//    Rev 1.7   Dec 12 2011 12:01:22   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.6   Dec 01 2011 19:05:28   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.5   Nov 27 2011 21:50:12   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.4   Nov 25 2011 17:41:14   wp040100
// P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
