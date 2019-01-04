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
// ^FILE   : AlertMessagesDlg.h
// ^AUTHOR : 
// ^DATE   : 04 April 2016
//
// ^CLASS    : AlertMessagesDlg
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
#include "AlertMessagesDlg.h"
#include <ifastcbo\DSTCommonFunction.hpp>

#include <uibase\DSTListCtrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <uibase\DSTComboBox.h>
#include <uibase\dstbutton.h>
#include <ifastbp\AlertMessagesProcessIncludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ALERT_MESSAGES;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<AlertMessagesDlg> dlgCreator(CMD_GUI_ALERT_MESSAGES);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
	const I_CHAR * const CLASSNAME							= I_("AlertMessagesDlg");
	const I_CHAR * const LV_ALERT_MESSAGE_LIST              = I_("Alert Message List");
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId AlertMessagesHeading;
    extern CLASS_IMPORT const BFTextFieldId AlertCode;
    extern CLASS_IMPORT const BFNumericFieldId AccountNum;
    extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

namespace UAF
{
}

namespace CND
{  
	extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}


//******************************************************************************
class LVAlertMessagesData : public IFDSListCtrlRowDataBase
{
public:
    virtual ~LVAlertMessagesData() {}

    DString fAlertCode;

    virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
    {
        pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::AlertCode, fAlertCode); 
    }
};


//******************************************************************************
class LVAlertMessagesAdapter : public IFDSListCtrlAdapter<LVAlertMessagesData>
{
public:
   virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2 )
   {
       int result = 0;

       const BFFieldId* pFieldId = pCtrl->getColumnField( iSortColumn - 1 );
       if (1 == iSortColumn) {
           // Condition indicator column.  Sort on image index
           result = (IFDSListBase::getColumnLVItem( lParam1, iSortColumn - 1)->iImage - 
                     IFDSListBase::getColumnLVItem( lParam2, iSortColumn - 1)->iImage);
       }
       else if (NULL == pFieldId) 
       {
           return 0;
       } 
       else if (*pFieldId == ifds::AlertCode) 
       {	
           result = i_strcmp(pData1->fAlertCode.c_str(), pData2->fAlertCode.c_str());    
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
            else if (*pFieldId == ifds::AlertCode)
            {
                pDispInfo->item.pszText = (I_CHAR*)pData->fAlertCode.c_str();
            } 

            return 1;
        }

		return 0;
	}
};


//******************************************************************************
AlertMessagesDlg::AlertMessagesDlg(CWnd* pParent, 
                                   GenericInterfaceContainer* pGIC, 
                                   GenericInterface* pGIParent, 
                                   const Command& rCommand )
:BaseMainDlg( AlertMessagesDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);   
}


//******************************************************************************
AlertMessagesDlg::~AlertMessagesDlg()
{
	TRACE_DESTRUCTOR(CLASSNAME);
}


//******************************************************************************
BOOL AlertMessagesDlg::OnInitDialog()
{
	TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
	BaseMainDlg::OnInitDialog();

	return TRUE;
}


//******************************************************************************
void AlertMessagesDlg::DoDataExchange( CDataExchange* pDX )
{
	BaseMainDlg::DoDataExchange( pDX );
}


//******************************************************************************
BEGIN_MESSAGE_MAP( AlertMessagesDlg, BaseMainDlg )
	//{{AFX_MSG_MAP( AlertMessagesDlg )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//******************************************************************************
void AlertMessagesDlg::OnPostInitDialog()
{
	TRACE_METHOD(CLASSNAME, I_("OnPostInitDialog"));

    IFDSListCtrl *ifdsListControlAlertMessages = new IFDSAdaptedListCtrl<LVAlertMessagesAdapter>(this, 
		                                                                                         CLASSNAME, 
		                                                                                         IDC_LV_ALERT_MESSAGES, 
		                                                                                         0, 
		                                                                                         0, 
		                                                                                         true, 
		                                                                                         false);

    AddIFDSListControl(ifdsListControlAlertMessages, 
		               LV_ALERT_MESSAGE_LIST, 
                       IFASTBP_PROC::ALERT_MESSAGE_LIST, 
		               ifds::AlertMessagesHeading);

    ifdsListControlAlertMessages->SetColumnWidth(0, 550);

    LoadListControl(IDC_LV_ALERT_MESSAGES, NULL);
	ConnectControlsToData(IDC_LV_ALERT_MESSAGES, true);
	LoadControls();

    //Update screen title
    DString dstrAccountNum, dstrShrNum, dstrEntityName;
    DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

    getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum); 
    getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShrNum, dstrShrNum); 
    dstcWorkSession->getFirstSequenced01AccountholderEntityName(getDataGroupId(), dstrAccountNum, dstrEntityName);

    SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
}

//******************************************************************************
SEVERITY AlertMessagesDlg::doInit()
{
	TRACE_METHOD(CLASSNAME, I_("doInit"));

	return NO_CONDITION;
}

//******************************************************************************
bool AlertMessagesDlg::doRefresh(GenericInterface * rpGICaller, 
                                 const I_CHAR * szOriginalCommand)
{
    return true;
}