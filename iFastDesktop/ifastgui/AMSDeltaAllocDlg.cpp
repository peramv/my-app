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
//    Copyright 2002 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : AMSDeltaAllocDlg.cpp
// ^AUTHOR : Thanisorn S.
// ^DATE   : Jan. 10,2018
//
// ----------------------------------------------------------
//
// ^CLASS    : AMSDeltaAllocDlg
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "AMSDeltaAllocDlg.h"
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\AMSDeltaAllocProcessincludes.h>
#include <uibase\dstedit.h>
#include <bfproc\abstractprocess.hpp>
#include <uibase\dstlistctrl.h>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_AMS_DELTA_ALLOC;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AMSDeltaAllocDlg > dlgCreator( CMD_GUI_AMS_DELTA_ALLOC );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME = I_("AMSDeltaAllocDlg");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AMSDeltaAllocHeading;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AMS_GLOBAL;

}

//*****************************************************************************
// Public methods
//*****************************************************************************
AMSDeltaAllocDlg::AMSDeltaAllocDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(AMSDeltaAllocDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*****************************************************************************
void AMSDeltaAllocDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
}

//*****************************************************************************
SEVERITY AMSDeltaAllocDlg::doInit()
{
   TRACE_METHOD(CLASSNAME,DOINIT);
   getParameter(AMS_DELTA_ALLOC_Para::AMS_CODE,_dstrAmsCode);
   getParameter(AMS_DELTA_ALLOC_Para::ACCOUNT_NUM,_dstrAccountNum);
   return(NO_CONDITION);
}

//******************************************************************************
bool AMSDeltaAllocDlg::doRefresh(GenericInterface * rpGICaller,
                                 const I_CHAR * szOriginalCommand)
{
   return(true);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(AMSDeltaAllocDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AMSDeltaAllocDlg)
ON_BN_CLICKED( IDC_BTN_ADM_DATES,  OnBtnAdmDates)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL AMSDeltaAllocDlg::OnInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//*****************************************************************************
void AMSDeltaAllocDlg::OnPostInitDialog()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION,CLASSNAME,I_("OnInit"));
   TRACE_METHOD(CLASSNAME,ONPOSTINITDIALOG);

   CString title;

   addControls();
   LoadListControl(IDC_LIST_DELTA_ALLOCATION);
   DisableControls();

   GetWindowText(title);
   CString amsCode = " AMS Code: ";
   CString accountNum = ",Account: ";
   CString newTitile = title + amsCode + _dstrAmsCode.c_str() + 
         (_dstrAccountNum != I_("0") ? ( accountNum + _dstrAccountNum) : I_("")).c_str();
   SetWindowText(newTitile);  
}

//********************************************************************************

bool AMSDeltaAllocDlg::addControls()
{ 
   TRACE_METHOD( CLASSNAME, I_("addControls") );

   AddListControl(CLASSNAME,IDC_LIST_DELTA_ALLOCATION,I_("AMS_DELTA_ALLOC_LIST"),ifds::AMSDeltaAllocHeading,
                  IFASTBP_PROC::AMS_DELTA_ALLOC_LIST,0,true,LISTFLAG_NOT_AUTO_ADD);
   AddControl(CTRL_EDIT,IDC_EDT_FUND_NUMBER,IFASTBP_PROC::AMS_DELTA_ALLOC_LIST,
              ifds::ToFundNumber,0,IDC_LIST_DELTA_ALLOCATION);
   AddControl(CTRL_EDIT,IDC_EDT_FUND,IFASTBP_PROC::AMS_DELTA_ALLOC_LIST,
              ifds::FundCode,0,IDC_LIST_DELTA_ALLOCATION);
   AddControl(CTRL_EDIT,IDC_EDT_CLASS, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST,
              ifds::ClassCode,0,IDC_LIST_DELTA_ALLOCATION);
   AddControl(CTRL_EDIT,IDC_EDT_FUND_PERCENT,IFASTBP_PROC::AMS_DELTA_ALLOC_LIST,
              ifds::AMSAllocDelta,0,IDC_LIST_DELTA_ALLOCATION);
   AddControl(CTRL_STATIC, IDC_TXT_DELTA_TOTAL_PRC_VAL,BF::NullContainerId,
              ifds::TotPercentage,0,IDC_LIST_DELTA_ALLOCATION);
   AddControl(CTRL_DATE, IDC_DTP_EFFECTIVE_DATE, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST, 
              ifds::EffectiveDate, 0, IDC_LIST_DELTA_ALLOCATION);

   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FUND_PERCENT))->SetAllowedChars(I_("-0123456789."));
   return(true);
}

//**********************************************************************************
void AMSDeltaAllocDlg::DisableControls()
{
   /* User able to change only AMS Delta percentage */
   GetDlgItem(IDC_EDT_FUND_NUMBER)->EnableWindow(FALSE);
   GetDlgItem(IDC_EDT_FUND)->EnableWindow(FALSE);
   GetDlgItem(IDC_EDT_CLASS)->EnableWindow(FALSE);
   GetDlgItem(IDC_DTP_EFFECTIVE_DATE)->EnableWindow(FALSE);
}

//************************************************************************************
void AMSDeltaAllocDlg::DoListItemChanged(UINT listControlID,
                                         const DString &strKey,
                                         bool bIsNewItem ,
                                         bool bIsDummyItem
                                        )
{
   if(listControlID == IDC_LIST_DELTA_ALLOCATION)
      DisableControls();
}

//*************************************************************************
void AMSDeltaAllocDlg::ControlUpdated(UINT controlID,
                                      const DString &strValue )
{
   switch( controlID )
   {
      case IDC_EDT_FUND_PERCENT:
         LoadControl( IDC_TXT_DELTA_TOTAL_PRC_VAL );
         break;
      default:
         break;
   }
}

//**********************************************************************************
void AMSDeltaAllocDlg::OnBtnAdmDates()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION,CLASSNAME,I_("OnBtnAdminDates"));
   CWaitCursor wait;
   ShowAdminDates(IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
}