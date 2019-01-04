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
// ^FILE   : PriceAdditionalDlg.h
// ^AUTHOR : 
// ^DATE   : 03 May 2017
//
// ^CLASS    : PriceAdditionalDlg
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
#include "PriceAdditionalDlg.h"
#include <ifastcbo\DSTCommonFunction.hpp>

#include <uibase\DSTListCtrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <uibase\DSTComboBox.h>
#include <uibase\dstbutton.h>
#include <ifastbp\PriceAdditionalProcessIncludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_PRICE_ADDITIONAL;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<PriceAdditionalDlg> dlgCreator(CMD_GUI_PRICE_ADDITIONAL);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
	const I_CHAR * const CLASSNAME							= I_("PriceAdditionalDlg");
	const I_CHAR * const LV_PRICE_ADDITIONAL_LIST           = I_("Price Additional List");
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId PriceAdditionalHeading;
    extern CLASS_IMPORT const BFTextFieldId TransType;
    extern CLASS_IMPORT const BFTextFieldId TransTypeDesc;
    extern CLASS_IMPORT const BFDecimalFieldId UnitValue;
    extern CLASS_IMPORT const BFDecimalFieldId ChgFactor;
    extern CLASS_IMPORT const BFDateFieldId ValueAsAt;
    extern CLASS_IMPORT const BFTextFieldId FundName;
    extern CLASS_IMPORT const BFTextFieldId rxFundCode;
    extern CLASS_IMPORT const BFTextFieldId rxClassCode;
}

namespace UAF
{
}

namespace CND
{  
	extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}


//******************************************************************************
class LVPriceAdditionalData : public IFDSListCtrlRowDataBase
{
public:
    virtual ~LVPriceAdditionalData() {}

    DString fTransType, fTransTypeDesc, fUnitValue, fChgFactor;

    virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
    {
        pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::TransType, fTransType);
        pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::TransTypeDesc, fTransTypeDesc);
        pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::UnitValue, fUnitValue); 
        pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::ChgFactor, fChgFactor); 
    }
};


//******************************************************************************
class LVPriceAdditionalAdapter : public IFDSListCtrlAdapter<LVPriceAdditionalData>
{
public:
   virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2 )
   {
       int result = 0;

       const BFFieldId* pFieldId = pCtrl->getColumnField( iSortColumn - 1 );
       if (NULL == pFieldId) 
       {
           return 0;
       } 
       else if (*pFieldId == ifds::TransType) 
       {	
           result = i_strcmp(pData1->fTransType.c_str(), pData2->fTransType.c_str());    
       }
       else if (*pFieldId == ifds::TransTypeDesc) 
       {	
           result = i_strcmp(pData1->fTransTypeDesc.c_str(), pData2->fTransTypeDesc.c_str());    
       }
       else if (*pFieldId == ifds::UnitValue) 
       {	
           double unitValue1 = DSTCommonFunctions::convertToDouble(pData1->fUnitValue);
           double unitValue2 = DSTCommonFunctions::convertToDouble(pData2->fUnitValue);

           result = (unitValue1 <= unitValue2) ? -1:1; 
       }
       else if (*pFieldId == ifds::ChgFactor) 
       {	
           double chgFactor1 = DSTCommonFunctions::convertToDouble(pData1->fChgFactor);
           double chgFactor2 = DSTCommonFunctions::convertToDouble(pData2->fChgFactor);

           result = (chgFactor1 <= chgFactor2) ? -1:1;   
       }

       return (bAscending ? result : -result);
   }

	virtual LRESULT onGetDispInfo(IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo)
	{
		if (pDispInfo->item.mask & LVIF_TEXT)
		{
			const BFFieldId* pFieldId = pCtrl->getColumnField(pDispInfo->item.iSubItem);

            if (pFieldId == NULL) 
            {
                pDispInfo->item.pszText = I_("");
            } 
            else if (*pFieldId == ifds::TransType)
            {
                pDispInfo->item.pszText = (I_CHAR*)pData->fTransType.c_str();
            } 
            else if (*pFieldId == ifds::TransTypeDesc)
            {
                pDispInfo->item.pszText = (I_CHAR*)pData->fTransTypeDesc.c_str();
            } 
            else if (*pFieldId == ifds::UnitValue)
            {
                pDispInfo->item.pszText = (I_CHAR*)pData->fUnitValue.c_str();
            } 
            else if (*pFieldId == ifds::ChgFactor)
            {
                pDispInfo->item.pszText = (I_CHAR*)pData->fChgFactor.c_str();
            } 

            return 1;
        }

		return 0;
	}
};


//******************************************************************************
PriceAdditionalDlg::PriceAdditionalDlg(CWnd* pParent, 
                                       GenericInterfaceContainer* pGIC, 
                                       GenericInterface* pGIParent, 
                                       const Command& rCommand)
:BaseMainDlg(PriceAdditionalDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);   
}


//******************************************************************************
PriceAdditionalDlg::~PriceAdditionalDlg()
{
	TRACE_DESTRUCTOR(CLASSNAME);
}


//******************************************************************************
BOOL PriceAdditionalDlg::OnInitDialog()
{
	TRACE_METHOD(CLASSNAME, I_("OnInitDialog"));
	BaseMainDlg::OnInitDialog();

	return TRUE;
}


//******************************************************************************
void PriceAdditionalDlg::DoDataExchange(CDataExchange* pDX)
{
	BaseMainDlg::DoDataExchange(pDX);
}


//******************************************************************************
BEGIN_MESSAGE_MAP(PriceAdditionalDlg, BaseMainDlg)
	//{{AFX_MSG_MAP( PriceAdditionalDlg )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//******************************************************************************
void PriceAdditionalDlg::OnPostInitDialog()
{
	TRACE_METHOD(CLASSNAME, I_("OnPostInitDialog"));

    IFDSListCtrl *ifdsListControlPriceAdditional = new IFDSAdaptedListCtrl<LVPriceAdditionalAdapter>(this, 
		                                                                                             CLASSNAME, 
		                                                                                             IDC_LV_PRICE_ADDITIONAL, 
		                                                                                             0, 
		                                                                                             LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE, 
		                                                                                             true, 
		                                                                                             false);

    AddIFDSListControl(ifdsListControlPriceAdditional, 
		               LV_PRICE_ADDITIONAL_LIST, 
                       IFASTBP_PROC::PRICE_ADDITIONAL_LIST, 
		               ifds::PriceAdditionalHeading);

    AddControl(CTRL_STATIC, IDC_FUND, IFASTBP_PROC::PRICE_ADDITIONAL_LIST, ifds::rxFundCode);
    AddControl(CTRL_STATIC, IDC_CLASS, IFASTBP_PROC::PRICE_ADDITIONAL_LIST, ifds::rxClassCode);
    AddControl(CTRL_STATIC, IDC_TRADE_DATE, IFASTBP_PROC::PRICE_ADDITIONAL_LIST, ifds::ValueAsAt);
    AddControl(CTRL_STATIC, IDC_FUND_DESC, IFASTBP_PROC::PRICE_ADDITIONAL_LIST, ifds::FundName);

    LoadListControl(IDC_LV_PRICE_ADDITIONAL, NULL);
	ConnectControlsToData(IDC_LV_PRICE_ADDITIONAL, true);

    ConnectControlsToData();
    LoadControls();
}

//******************************************************************************
SEVERITY PriceAdditionalDlg::doInit()
{
	TRACE_METHOD(CLASSNAME, I_("doInit"));

	return NO_CONDITION;
}

//******************************************************************************
bool PriceAdditionalDlg::doRefresh(GenericInterface * rpGICaller, 
                                   const I_CHAR * szOriginalCommand)
{
    return true;
}