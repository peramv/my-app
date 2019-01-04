//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//******************************************************************************
//
// ^FILE   : AccountRegDetailsDlg.cpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 14 June 2013
//
// ^CLASS    : AccountRegDetailsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"

#include <ConfigManager.hpp>

#include <bfutil\clientlocalecontext.hpp>
#include <bfproc\AbstractProcess.hpp>
#include "AccountRegDetailsDlg.h"
#include <ifastcbo\DSTCommonFunction.hpp>

#include <uibase\DSTListCtrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <uibase\DSTComboBox.h>
#include <uibase\dstbutton.h>
#include <ifastbp\AccountRegDetailsProcessIncludes.h>
#include <ifastcbo\MFAccount.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCT_REGIS_MAINT;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<AccountRegDetailsDlg> dlgCreator(CMD_GUI_ACCT_REGIS_MAINT);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
	const I_CHAR * const CLASSNAME							= I_("AccountRegDetailsDlg");  
	const I_CHAR * const YES								= I_("Y");
	const I_CHAR * const NO									= I_("N");   

	const I_CHAR * const LV_ACCT_REGULATORY_LIST            = I_("Account Regulatory Details List");
	const I_CHAR * const LV_ACCT_ENT_REG_JURIS_LIST         = I_("Account Entity Regulatory Jurisdiction Details List");
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId AccountRegulatoryDetailsHeading;
	extern CLASS_IMPORT const BFTextFieldId EntityRegJurisDetailsHeading1;
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId StopDate;
	extern CLASS_IMPORT const BFTextFieldId FICategory;
	extern CLASS_IMPORT const BFTextFieldId FinInstRegDetlUUID;
	extern CLASS_IMPORT const BFTextFieldId AcctRegDetailsUUID;
	extern CLASS_IMPORT const BFTextFieldId ComplyAction;
	extern CLASS_IMPORT const BFTextFieldId Consented;
	extern CLASS_IMPORT const BFNumericFieldId VersionAcctRegDetl;
	extern CLASS_IMPORT const BFNumericFieldId ShrNum;
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFDateFieldId ProcessDate;
	extern CLASS_IMPORT const BFTextFieldId Username;
	extern CLASS_IMPORT const BFDateFieldId ModDate;
	extern CLASS_IMPORT const BFTextFieldId ModUser;
	extern CLASS_IMPORT const BFTextFieldId Regulatory;
	extern CLASS_IMPORT const BFTextFieldId AcctType;
	extern CLASS_IMPORT const BFTextFieldId DefaultReportingFFI;
	extern CLASS_IMPORT const BFDateFieldId LastReviewDate;
	extern CLASS_IMPORT const BFTextFieldId CountryCode;
	extern CLASS_IMPORT const BFTextFieldId EntityType;
	extern CLASS_IMPORT const BFTextFieldId EntityName;
	extern CLASS_IMPORT const BFTextFieldId FATCACode;
	extern CLASS_IMPORT const BFTextFieldId TaxJuris;
	extern CLASS_IMPORT const BFTextFieldId TaxPayerStat;
	extern CLASS_IMPORT const BFDateFieldId TaxPayerStartDate;
	extern CLASS_IMPORT const BFTextFieldId PendingFATCASrch;
	extern CLASS_IMPORT const BFTextFieldId ReqIndiciaSearch;
	extern CLASS_IMPORT const BFTextFieldId ComplyRuleDesc;
}

namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const ACCT_REGIS_MAINT;
    extern CLASS_IMPORT I_CHAR * const UPDATE_INDICIA_SEARCH_REQUEST;
}

namespace CND
{  
	extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}


//******************************************************************************
class LVAcctRegDetailsData : public IFDSListCtrlRowDataBase
{
public:
	virtual ~LVAcctRegDetailsData() {}

   DString fEffectiveDate, fStopDate, fFinInstRegDetlUUID, fCountryCode, fComplyRuleDesc;

	virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
	{
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::EffectiveDate, fEffectiveDate); 
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::StopDate, fStopDate); 
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::FinInstRegDetlUUID, fFinInstRegDetlUUID); 
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::CountryCode, fCountryCode); 
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::ComplyRuleDesc, fComplyRuleDesc); 
	}
};


//******************************************************************************
class LVAcctRegDetailsAdapter : public IFDSListCtrlAdapter< LVAcctRegDetailsData >
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
		else if (*pFieldId == ifds::EffectiveDate) 
		{	
			if ( DSTCommonFunctions::CompareDates( pData1->fEffectiveDate.c_str(), pData2->fEffectiveDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = 1;
			else if ( DSTCommonFunctions::CompareDates( pData2->fEffectiveDate.c_str(), pData1->fEffectiveDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = -1;
			// for equal, result will be 0         
		}    
		else if (*pFieldId == ifds::StopDate) 
		{
			if ( DSTCommonFunctions::CompareDates( pData1->fStopDate.c_str(), pData2->fStopDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
			result = 1;
			else if ( DSTCommonFunctions::CompareDates( pData2->fStopDate.c_str(), pData1->fStopDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
			result = -1;
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
			else if (*pFieldId == ifds::EffectiveDate)
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->fEffectiveDate.c_str();
			}           
			else if (*pFieldId == ifds::FinInstRegDetlUUID)
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->fFinInstRegDetlUUID.c_str();
			}    
			else if (*pFieldId == ifds::CountryCode)
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->fCountryCode.c_str();
			}
			else if (*pFieldId == ifds::StopDate)
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->fStopDate.c_str();
			}
			else if (*pFieldId == ifds::ComplyRuleDesc)
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->fComplyRuleDesc.c_str();
			}

			return (1);
		}

		return (0);
	}
};

//******************************************************************************
class LVAccountEntityRegJurisDetailsData : public IFDSListCtrlRowDataBase
{
public:
	virtual ~LVAccountEntityRegJurisDetailsData() {}

	DString fEntityType, fEntityName, fFATCACode, fTaxJuris, fTaxPayerStat, fTaxPayerStartDate ;

	virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
	{
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::EntityType, fEntityType); 
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::EntityName, fEntityName); 
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::FATCACode, fFATCACode); 
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::TaxJuris, fTaxJuris); 
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::TaxPayerStat, fTaxPayerStat); 
		pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::TaxPayerStartDate, fTaxPayerStartDate); 
	}
};


//******************************************************************************
class LVAccountEntityRegJurisDetailsAdapter : public IFDSListCtrlAdapter< LVAccountEntityRegJurisDetailsData >
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
		//else if (*pFieldId == ifds::EffectiveDate) 
		//{	
		//	DSTCommonFunctions::DATE_ORDER compareResult = DSTCommonFunctions::CompareDates(pData1->fEffectiveDate.c_str(), pData2->fEffectiveDate.c_str());
		//	if ( compareResult == DSTCommonFunctions::FIRST_EARLIER )
		//		result = 1;
		//	else if ( compareResult == DSTCommonFunctions::SECOND_EARLIER ) 
		//		result = -1;
		//	// for equal, result will be 0         
		//}    
		//else if (*pFieldId == ifds::CountryCode) 
		//	result = i_strcmp( pData1->fCountryCode.c_str(), pData2->fCountryCode.c_str() );
		//else if (*pFieldId == ifds::FinInstRegDetlUUID) 
		//	result = i_strcmp( pData1->fFinInstRegDetlUUID.c_str(), pData2->fFinInstRegDetlUUID.c_str() );

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
			else if (*pFieldId == ifds::EntityType)
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->fEntityType.c_str();
			}    
			else if (*pFieldId == ifds::EntityName)
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->fEntityName.c_str();
			}
			else if (*pFieldId == ifds::FATCACode)
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->fFATCACode.c_str();
			}
			else if (*pFieldId == ifds::TaxJuris)
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->fTaxJuris.c_str();
			}
			else if (*pFieldId == ifds::TaxPayerStat)
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->fTaxPayerStat.c_str();
			} 
			else if (*pFieldId == ifds::TaxPayerStartDate)
			{
				pDispInfo->item.pszText = (I_CHAR*)pData->fTaxPayerStartDate.c_str();
			}           
 

			return (1);
		}

		return (0);
	}
};


//******************************************************************************
AccountRegDetailsDlg::AccountRegDetailsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
   :BaseMainDlg( AccountRegDetailsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
}


//******************************************************************************
AccountRegDetailsDlg::~AccountRegDetailsDlg()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
BOOL AccountRegDetailsDlg::OnInitDialog()
{
	TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
	BaseMainDlg::OnInitDialog();

	return TRUE;
}


//******************************************************************************
void AccountRegDetailsDlg::DoDataExchange( CDataExchange* pDX )
{
	BaseMainDlg::DoDataExchange( pDX );
}


//******************************************************************************
BEGIN_MESSAGE_MAP( AccountRegDetailsDlg, BaseMainDlg )
	//{{AFX_MSG_MAP( AccountRegDetailsDlg )
	ON_BN_CLICKED(IDC_BTN_ADMIN_DATES, OnBtnAdmDates)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_BN_CLICKED(IDC_BTN_HISTORICAL, OnBtnHistorical)
	ON_BN_CLICKED(IDC_BTN_REQ_INDICIA, OnBtnReqIndicia)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//******************************************************************************
void AccountRegDetailsDlg::OnPostInitDialog()
{
	TRACE_METHOD(CLASSNAME, I_( "OnPostInitDialog" ));
	
	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	DString dstrShrNum, dstrAccountNum, dstrEntityName;

	getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShrNum, dstrShrNum);
	getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum);     
	dstWorkSession->getFirstSequenced01AccountholderEntityName(getDataGroupId(), dstrAccountNum, dstrEntityName);
	
	SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);

	SetUserAccesFunctionCode(UAF::ACCT_REGIS_MAINT);
	//addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_ACCT_REGULATORY_LIST);
	//addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_ACCT_REGULATORY_LIST);

	addControls();

   DString pendingFATCASrch;
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::PendingFATCASrch, pendingFATCASrch, false);
   pendingFATCASrch.strip().upperCase();
   bool bEnableIndiciaSrchBtn = pendingFATCASrch != I_("Y");

   GetDlgItem(IDC_BTN_REQ_INDICIA)->EnableWindow(bEnableIndiciaSrchBtn && hasUpdatePermission(UAF::UPDATE_INDICIA_SEARCH_REQUEST));

}

//******************************************************************************
SEVERITY AccountRegDetailsDlg::doInit()
{
	TRACE_METHOD(CLASSNAME, I_("doInit"));

	return (NO_CONDITION);
}


//******************************************************************************
void AccountRegDetailsDlg::addControls()
{
	IFDSListCtrl* ifdsListControlAcctRegDetails = 
		new IFDSAdaptedListCtrl< LVAcctRegDetailsAdapter >( this, 
		CLASSNAME, 
		IDC_LV_ACCT_REGULATORY_LIST, 
		0, 
		0, 
		true, 
		true );

	IFDSListCtrl* ifdsListControlAccountEntityRegJurisDetails = 
		new IFDSAdaptedListCtrl< LVAccountEntityRegJurisDetailsAdapter >( this, 
		CLASSNAME, 
		IDC_LV_ACCT_ENT_REG_JURIS_LIST, 
		0, 
		0, 
		true, 
		true );

	AddIFDSListControl(ifdsListControlAcctRegDetails, 
		LV_ACCT_REGULATORY_LIST, 
		IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, 
		ifds::AccountRegulatoryDetailsHeading);

	AddIFDSListControl(ifdsListControlAccountEntityRegJurisDetails, 
		LV_ACCT_ENT_REG_JURIS_LIST, 
		IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, 
		ifds::EntityRegJurisDetailsHeading1); 

	//if (NULL != ifdsListControlAcctRegDetails)		
	//	ifdsListControlAcctRegDetails->SortOnColumn(1);

	//if (NULL != ifdsListControlAccountEntityRegJurisDetails)		
	//	ifdsListControlAccountEntityRegJurisDetails->SortOnColumn(1);

	//AddControl(CTRL_COMBO,IDC_CMB_CONSENT,				IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::Consented,				CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_REGULATORY_LIST);
	//AddControl(CTRL_COMBO,IDC_CMB_REGULATION,			IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::Regulatory,			CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_REGULATORY_LIST);
	//AddControl(CTRL_COMBO,IDC_CMB_ACTION,				IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::ComplyAction,			CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_REGULATORY_LIST);
	//AddControl(CTRL_COMBO,IDC_CMB_REPORTING_FFI,		IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::FinInstRegDetlUUID,    CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_REGULATORY_LIST);
	//AddControl(CTRL_COMBO,IDC_CMB_CLASSIFICATION,		IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::FICategory,			CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_REGULATORY_LIST);
	//AddControl(CTRL_DATE, IDC_DTP_START_DATE,			IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::EffectiveDate,			CTRLFLAG_DEFAULT,				IDC_LV_ACCT_REGULATORY_LIST);
	//AddControl(CTRL_DATE, IDC_DTP_STOP_DATE,			IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::StopDate,				CTRLFLAG_DEFAULT,				IDC_LV_ACCT_REGULATORY_LIST);
	//AddControl(CTRL_EDIT, IDC_EDT_DEFAULT_REPORTING_FFI,IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::DefaultReportingFFI,	CTRLFLAG_DEFAULT,				IDC_LV_ACCT_REGULATORY_LIST);
    AddControl( CTRL_STATIC, IDC_TXT_REVIEW_DATE,     IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::LastReviewDate,      CTRLFLAG_DEFAULT,				IDC_LV_ACCT_REGULATORY_LIST );
   //AddControl( CTRL_STATIC, IDC_TXT_REPORTING_FFI,   IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::FinInstRegDetlUUID,  CTRLFLAG_DEFAULT,				IDC_LV_ACCT_REGULATORY_LIST );
   //AddControl( CTRL_STATIC, IDC_CMB_ENTITY_COUNTRY,  IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::CountryCode,         CTRLFLAG_DEFAULT,				IDC_LV_ACCT_REGULATORY_LIST );
   //AddControl( CTRL_STATIC, IDC_TXT_EFFECTIVEDATE,   IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::EffectiveDate,       CTRLFLAG_DEFAULT,				IDC_LV_ACCT_REGULATORY_LIST );
	

	LoadListControl(IDC_LV_ACCT_REGULATORY_LIST, NULL);
	LoadListControl(IDC_LV_ACCT_ENT_REG_JURIS_LIST, NULL);
	ConnectControlsToData(IDC_LV_ACCT_REGULATORY_LIST, true);
	LoadControls();

}


//******************************************************************************
bool AccountRegDetailsDlg::doRefresh(GenericInterface * rpGICaller, 
									 const I_CHAR * szOriginalCommand)
{

	return(true);
}


//******************************************************************************
void AccountRegDetailsDlg::OnBtnAdd()
{
	TRACE_METHOD(CLASSNAME, I_("OnBtnAdd"));

   //AddToListControl(IDC_LV_ACCT_REGULATORY_LIST);
}


//********************************************************************************
void AccountRegDetailsDlg::OnBtnDelete()
{
	TRACE_METHOD(CLASSNAME, I_("OnBtnDelete"));

   //DeleteFromListControl(IDC_LV_ACCT_REGULATORY_LIST);
}


//**********************************************************************************
void AccountRegDetailsDlg::OnBtnAdmDates() 
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAdminDates"));

   //CWaitCursor wait;
   //ShowAdminDates(IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
}


//**********************************************************************************
void AccountRegDetailsDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));

   //IFastHistoricalInfo historicalInfo;

   //historicalInfo(this, IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
}


//******************************************************************************
void AccountRegDetailsDlg::OnBtnReset() 
{
	TRACE_METHOD(CLASSNAME, I_("OnBtnReset"));

   //ResetListItem(IDC_LV_ACCT_REGULATORY_LIST);
}


//******************************************************************************
void AccountRegDetailsDlg::DoListItemChanged(UINT listControlID,
											 const DString &strKey,
											 bool bIsNewItem,
											 bool bIsDummyItem)
{
   //if(listControlID == IDC_LV_ACCT_REGULATORY_LIST)
   //{
   //   GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow(!bIsNewItem && !bIsDummyItem);
   //}
}

//******************************************************************************
bool AccountRegDetailsDlg::GetDataForControl( UINT controlID,
									          DString &strValueOut,
											  bool bFormatted,
											  int index ) const
{
   //if( controlID == IDC_TXT_DOC_STATUS ||
   //   controlID == IDC_TXT_INDICIA_FOUND ||
   //   controlID == IDC_TXT_REVIEW_DATE ||
   //   controlID == IDC_TXT_REPORTING_FFI ||
   //   controlID == IDC_CMB_ENTITY_COUNTRY ||
   //   controlID == IDC_TXT_EFFECTIVEDATE )
   //{
   //   const BFFieldId& bfFieldId = GetControl(controlID)->GetFieldID();

   //   if (controlID == IDC_CMB_ENTITY_COUNTRY ||
   //      controlID == IDC_TXT_EFFECTIVEDATE ||
   //      controlID == IDC_TXT_DOC_STATUS ||
   //      controlID == IDC_TXT_INDICIA_FOUND ||
   //      controlID == IDC_TXT_REVIEW_DATE)
   //      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, bfFieldId, strValueOut, true );
   //   else
   //      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, bfFieldId, strValueOut, false );

   //   return true;
   //}

   if( controlID == IDC_TXT_REVIEW_DATE )
	{
      const BFFieldId& bfFieldId = GetControl(controlID)->GetFieldID();
      DString reviewDate;
      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, bfFieldId, reviewDate, false );
      reviewDate.strip().upperCase();

      if(reviewDate.empty() || reviewDate == I_("12319999"))
      {
         reviewDate = I_("N\\A");
      }
	  else
      {
         getParent()->getField( this, IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, bfFieldId, reviewDate, false );

         if(bFormatted)
         {
            BFDate date(reviewDate, BFDate::DATE_FORMAT::DF_MMDDCCYY );
            const ClientLocale& locale = ClientLocaleContext::get();
            const BFDate::DATE_FORMAT& fmt = getDateFormatFromClientLocale(locale);
            const DString dstrDateOut = date.get(fmt);
            if ( !dstrDateOut.empty() )
            {
               reviewDate = NULL_STRING;
               reviewDate = dstrDateOut;
            }
		 }
      }

      strValueOut = reviewDate;

      return true;
   }
   else
   {
	return false;
   }
}

//******************************************************************************
void AccountRegDetailsDlg::OnBtnReqIndicia()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnReqIndicia" ) );

   try
   {      
      getParent()->setField ( this, IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, ifds::ReqIndiciaSearch, I_("Y"), false);
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   PostMessage(WM_COMMAND, IDOK);
   //   OnOK();
   //   Exit(IDOK);
}

//*************************************************************************
BFDate::DATE_FORMAT AccountRegDetailsDlg::getDateFormatFromClientLocale(const ClientLocale& rLocale) const
{
   static const DString dstrConfiguration( I_( "DisplayMasks" ) );
   DString dstrKey = rLocale.getLocale() + I_( "-D" );

   DString mask = GetConfigValueAsString( ConfigManager::getApplication(), 
                                          dstrConfiguration,
                                          dstrKey );
   if( mask.size() == 0 )
   {
      static const DString dstrHostConfiguration( I_( "HostMasks" ) );
      static const DString dstrType( I_( "D" ) );
      DString dstrHostKey;
      dstrHostKey.append( dstrType );

      DString hostMask = GetConfigValueAsString( I_( "DICORE" ),
                                                 dstrHostConfiguration,
                                                 dstrHostKey );

      if( hostMask.size() == 0 )
      {
         return BFDate::DATE_FORMAT::DF_MMDDCCYY;
      }
      else
      {
         return inferMaskFormat( hostMask );
      }
   }
   else
   {
      return inferMaskFormat( mask );
   }
}

//*************************************************************************
BFDate::DATE_FORMAT AccountRegDetailsDlg::inferMaskFormat( const DString& dstrMask ) const
{
   // look for the dd|DD, the mm|MM, and the ccyy|CCYY|yyyy|YYYY
   int iDay = dstrMask.find( I_( "DD" ) );
   if( iDay == dstrMask.npos ) iDay = dstrMask.find( I_( "dd" ) );

   int iMonth = dstrMask.find( I_( "MM" ) );
   if( iMonth == dstrMask.npos ) iMonth = dstrMask.find( I_( "mm" ) );

   int iYear = dstrMask.find( I_( "CCYY" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "ccyy" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "YYYY" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "yyyy" ) );

   // if day, month, or year are not known then give up
   if( iDay == dstrMask.npos ||
       iMonth == dstrMask.npos ||
       iYear == dstrMask.npos )
   {
      return( BFDate::DATE_FORMAT::DF_NULL );
   }

   // what is the separator?
   bool bFS = false;
   bool bFD = false;
   if( dstrMask.find( I_( "/" ) ) != dstrMask.npos ) bFS = true;
   else if( dstrMask.find( I_( "-" ) ) != dstrMask.npos ) bFD = true;

   if( iYear < iMonth )
   {
      // it's ISO
      if( bFS ) return( BFDate::DATE_FORMAT::DF_FSISO );
      if( bFD ) return( BFDate::DATE_FORMAT::DF_FDISO );
      return( BFDate::DATE_FORMAT::DF_ISO );
   }
   else if( iDay < iMonth )
   {
      // it's European format (dd/mm/yyyy)
      if( bFS ) return( BFDate::DATE_FORMAT::DF_FSEURO );
      if( bFD ) return( BFDate::DATE_FORMAT::DF_FDEURO );
      return( BFDate::DATE_FORMAT::DF_EURO );
   }
   else if( iMonth < iDay && iDay < iYear )
   {
      // it's US format
      if( bFS ) return( BFDate::DATE_FORMAT::DF_FSUS );
      if( bFD ) return( BFDate::DATE_FORMAT::DF_FDUS );
      return( BFDate::DATE_FORMAT::DF_US );
   }
   else
   {
      //unknown format! therefore forced it as mmddyyyy
      return( BFDate::DATE_FORMAT::DF_MMDDCCYY );
   }
}