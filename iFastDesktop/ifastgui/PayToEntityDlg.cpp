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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : PayToEntityDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2003
//
// ----------------------------------------------------------
//
// ^CLASS    : PayToEntityDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#include "paytoentitydlg.h"
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <bfproc\abstractprocess.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\paytoentityprocessincludes.h>
#include "ifasthistoricalinfo.hpp"
#include "discardmsgdlg.h"


extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PAYMENT_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_PAY_TO_ENTITY;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<PayToEntityDlg> dlgCreator(CMD_GUI_PAY_TO_ENTITY);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("PayToEntityDlg");
   const I_CHAR *LV_PAY_TO_ENTITY_LIST = I_("PayToEntityList");
}

namespace ifds
{ 
   extern CLASS_IMPORT const BFTextFieldId ClientName;
   extern CLASS_IMPORT const BFTextFieldId PayToEntityListMgmtCoHeading;
}


namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const PAY_TO_ENTITY;
}


class LVPayToEntityData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVPayToEntityData() {}
   DString BrokerCode_;
   DString CompanyCode_;
   DString ClientName_;
   DString BrokerName_;
   DString PaymentFor_;
   DString PayToEntity_;
   DString EffectiveDate_;
   DString StopDate_;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      //pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), 
         ifds::BrokerCode, BrokerCode_);
      BrokerCode_.strip();

      //pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), 
         ifds::BrokerName, BrokerName_);
      BrokerName_.strip();

      //pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), 
         ifds::CompanyCode, CompanyCode_);
      CompanyCode_.strip();

      //pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), 
         ifds::ClientName, ClientName_);
      ClientName_.strip();

      //pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), 
         ifds::PaymentFor, PaymentFor_);
      PaymentFor_.strip();

      //pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), 
         ifds::PayToEntity, PayToEntity_);
      PayToEntity_.strip();

      //pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), 
         ifds::EffectiveDate, EffectiveDate_);
      EffectiveDate_.strip();

      //pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), 
         ifds::StopDate, StopDate_);
      StopDate_.strip();
   }
};

class LVPayToEntityAdapter : public IFDSListCtrlAdapter< LVPayToEntityData >
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
      else if (*pFieldId == ifds::BrokerCode) 
      {
         result = i_strcmp(pData1->BrokerCode_.c_str(), pData2->BrokerCode_.c_str());
      } 
      else if (*pFieldId == ifds::CompanyCode) 
      {
         result = i_strcmp(pData1->CompanyCode_.c_str(), pData2->CompanyCode_.c_str());
      } 
      else if (*pFieldId == ifds::ClientName) 
      {
         result = i_strcmp(pData1->ClientName_.c_str(), pData2->ClientName_.c_str());
      } 
      else if (*pFieldId == ifds::BrokerName) 
      {
         result = i_strcmp(pData1->BrokerName_.c_str(), pData2->BrokerName_.c_str());
      } 
      else if (*pFieldId == ifds::PaymentFor) 
      {
         result = i_strcmp(pData1->PaymentFor_.c_str(), pData2->PaymentFor_.c_str());
      } 
      else if (*pFieldId == ifds::PayToEntity) 
      {
         result = i_strcmp(pData1->PayToEntity_.c_str(), pData2->PayToEntity_.c_str());
      } 
      else if( *pFieldId == ifds::EffectiveDate ) 
      {
         if ( DSTCommonFunctions::CompareDates( pData1->EffectiveDate_.c_str(), pData2->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
            result = -1;
         else if ( DSTCommonFunctions::CompareDates( pData2->EffectiveDate_.c_str(), pData1->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
            result = 1;
      }
      else if( *pFieldId == ifds::StopDate ) 
      {
         if ( DSTCommonFunctions::CompareDates( pData1->StopDate_.c_str(), pData2->StopDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
            result = -1;
         else if ( DSTCommonFunctions::CompareDates( pData2->StopDate_.c_str(), pData1->StopDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
            result = 1;
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
         else if (*pFieldId == ifds::BrokerCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BrokerCode_.c_str();
         } 
         else if (*pFieldId == ifds::CompanyCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->CompanyCode_.c_str();
         } 
         else if (*pFieldId == ifds::ClientName) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->ClientName_.c_str();
         } 
         else if (*pFieldId == ifds::BrokerName) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BrokerName_.c_str();
         } 
         else if (*pFieldId == ifds::PaymentFor) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->PaymentFor_.c_str();
         } 
         else if (*pFieldId == ifds::PayToEntity)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->PayToEntity_.c_str();
         }
         else if( *pFieldId == ifds::EffectiveDate ) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->EffectiveDate_.c_str();
         }
         else if( *pFieldId == ifds::StopDate )
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->StopDate_.c_str();
         }
         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
PayToEntityDlg::PayToEntityDlg(CWnd* pParent, 
   GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(PayToEntityDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_pWndItemInFocus(NULL), 
m_dstrBrokerCode(NULL_STRING),
m_dstrSearchTypeMgmt(NULL_STRING),
m_dstrBackgroundSearch(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(PayToEntityDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void PayToEntityDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(PayToEntityDlg)
   //}}AFX_DATA_MAP

}

//*****************************************************************************
SEVERITY PayToEntityDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter(MFCAN_IP_PARAM::BROKER_CODE, m_dstrBrokerCode);
   getParameter(MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, m_dstrSearchTypeMgmt);
   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(PayToEntityDlg, BaseMainDlg)
//{{AFX_MSG_MAP(PayToEntityDlg)
ON_MESSAGE(UM_OPENBROKERLISTDLG, OpenBrokerListDlg)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_PAYMENT_INSTRUCTIONS, OnBtnInstructions)
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical)
ON_NOTIFY(NM_DBLCLK, IDC_LV_PAY_TO_ENTITY_LIST, OnDblclkPayToEntityList)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL PayToEntityDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();
   return TRUE;
}

//*****************************************************************************
void PayToEntityDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);


   SetUserAccesFunctionCode(UAF::PAY_TO_ENTITY);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_PAY_TO_ENTITY_LIST);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_PAY_TO_ENTITY_LIST);

   IFDSListCtrl* pPayToEntityListCtrl = 
         new IFDSAdaptedListCtrl< LVPayToEntityAdapter >( this, CLASSNAME, 
                                                          IDC_LV_PAY_TO_ENTITY_LIST, 
                                                          0, 
                                                          0, 
                                                          true, 
                                                          true);
   if (m_dstrSearchTypeMgmt == I_("MGMTCO"))
   {
      GetDlgItem (IDC_BTN_MORE)->EnableWindow(false);		
      AddIFDSListControl( pPayToEntityListCtrl, 
                          LV_PAY_TO_ENTITY_LIST, 
                          IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                          ifds::PayToEntityListMgmtCoHeading);
/*    AddListControl ( CLASSNAME, 
                       IDC_LV_PAY_TO_ENTITY_LIST, 
                       LV_PAY_TO_ENTITY_LIST, 
                       ifds::PayToEntityListMgmtCoHeading, 
                       IFASTBP_PROC::PAY_TO_ENTITY_LIST);
*/
   }
   else
   {

      AddIFDSListControl( pPayToEntityListCtrl, 
                          LV_PAY_TO_ENTITY_LIST, 
                          IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                          ifds::PayToEntityListHeading);
   }
     
   /*AddListControl(CLASSNAME, IDC_LV_PAY_TO_ENTITY_LIST, LV_PAY_TO_ENTITY_LIST, 
      ifds::PayToEntityListHeading, IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
      0, true, 0);*/
   AddControl ( CTRL_EDIT, 
                IDC_EDT_BROKER_CODE, 
                IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                ifds::BrokerCode, 
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
                (UINT)IDC_LV_PAY_TO_ENTITY_LIST);

   AddControl ( CTRL_COMBO, 
                IDC_CMB_PAYMENT_FOR, 
                IFASTBP_PROC::PAY_TO_ENTITY_LIST,
                ifds::PaymentFor, 
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_PAY_TO_ENTITY_LIST);

   AddControl ( CTRL_COMBO, 
                IDC_CMB_ENTITY_TYPE, 
                IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                ifds::PayToEntity, 
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                (UINT)IDC_LV_PAY_TO_ENTITY_LIST);
//Effective Date
   AddControl ( CTRL_DATE, 
                IDC_DTP_EFFECTIVE_DATE, 
                IFASTBP_PROC::PAY_TO_ENTITY_LIST,
                ifds::EffectiveDate, 
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                (UINT)IDC_LV_PAY_TO_ENTITY_LIST);
//Stop Date
   AddControl ( CTRL_DATE,  
                IDC_DTP_STOP_DATE, 
                IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                ifds::StopDate, 
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                (UINT)IDC_LV_PAY_TO_ENTITY_LIST);

   ConnectControlsToData();

   GetDlgItem (IDC_STC_BROKER_CODE)->ShowWindow (m_dstrSearchTypeMgmt != I_("MGMTCO"));
   GetDlgItem (IDC_STC_CLIENT_CODE)->ShowWindow (m_dstrSearchTypeMgmt == I_("MGMTCO"));
   doRefresh (this, NULL);
}


//******************************************************************************
bool PayToEntityDlg::doRefresh ( GenericInterface *rpGICaller, 
                                 const I_CHAR *szOriginalCommand)
{
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   if (m_dstrSearchTypeMgmt == I_("MGMTCO"))
   {
      ReInitControl ( IDC_EDT_BROKER_CODE,
                      IFASTBP_PROC::PAY_TO_ENTITY_LIST,
                      ifds::CompanyCode,
                      CTRLFLAG_DEFAULT);

      ConnectListToData( IDC_LV_PAY_TO_ENTITY_LIST, true );
      LoadListControl ( IDC_LV_PAY_TO_ENTITY_LIST );
   }
   else
   {
      //when called by the process from doRefresh, 
      if (DString(szOriginalCommand) == I_("ReloadParams"))
      {
         getParameter(MFCAN_IP_PARAM::BROKER_CODE, m_dstrBrokerCode);
      }

      CWnd *pWnd = GetDlgItem(IDC_BTN_HISTORICAL);

      if (pWnd)
      {
         pWnd->EnableWindow(getParent()->
            getNumberOfItemsInList (this, IFASTBP_PROC::PAY_TO_ENTITY_LIST) > 0);
      }
      //this will load the controls
      ConnectListToData ( IDC_LV_PAY_TO_ENTITY_LIST, true );
      LoadListControl ( IDC_LV_PAY_TO_ENTITY_LIST ); 
      //enables the more button
      GetDlgItem (IDC_BTN_MORE)->EnableWindow ( getParent()->doMoreRecordsExist(this, 
                                                IFASTBP_PROC::PAY_TO_ENTITY_LIST));
   }

// display caption
   SetDlgCaption();
   return true;
}

//******************************************************************************
void PayToEntityDlg::SetDlgCaption()
{   
   if (m_dstrSearchTypeMgmt == I_("MGMTCO"))
   {
      DString dstrClientName;

      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      if (dstWorkSession->getOption (ifds::ClientName, dstrClientName, getParent()->getDataGroupId(), false ) <= WARNING)
      {
         dstrClientName = I_(": ") + dstrClientName;
         SetCaption (dstrClientName);
      }
   }
   else
   {
      DString brokerName;

      if (m_dstrBrokerCode == NULL_STRING)
      {
         CString all;

         all.LoadString(TXT_ALL);
         brokerName = all.GetBuffer(0);
      }
      else 
      {
         DString hasItemsByBrokerCode;

         getParent()->getField(this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
            HasItemsByBrokerCode, hasItemsByBrokerCode);

         if (hasItemsByBrokerCode != I_("Y"))
         {
            AddToListControl(IDC_LV_PAY_TO_ENTITY_LIST);
         }
         getParent()->getField(this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
            ifds::BrokerName, brokerName);
      }
      brokerName = I_(": ") + brokerName;
      SetCaption(brokerName);
   }
}

//*************************************************************************
void PayToEntityDlg::ControlUpdated (UINT controlID, const DString &strValue)
{
   if ( controlID == IDC_CMB_ENTITY_TYPE ||
        controlID == IDC_EDT_BROKER_CODE)
   {
      if (m_dstrSearchTypeMgmt != I_("MGMTCO")) 
      {
         bool bEnable = controlID == IDC_EDT_BROKER_CODE ||
            (controlID == IDC_CMB_ENTITY_TYPE && strValue != NULL_STRING);
         DString brokerActive;

         getParent()->getField ( this, 
                                 IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                                 BrokerActive, 
                                 brokerActive);  
         bEnable &= brokerActive == I_("Y");
         //disable the instructions button if the pay to entity is NULL_STRING and 
         //broker is not active/effective
         GetDlgItem (IDC_BTN_PAYMENT_INSTRUCTIONS)->EnableWindow (bEnable);
      }
   }
}

//*************************************************************************
bool PayToEntityDlg::PreCancel()
{
   return discardUpdates();
}

//******************************************************************************
void PayToEntityDlg::OnBtnAdd()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnAdd"));

   CWaitCursor wait;

   AddToListControl(IDC_LV_PAY_TO_ENTITY_LIST);
}

//******************************************************************************
void PayToEntityDlg::OnBtnDelete()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnDelete"));

   CWaitCursor wait;

   DeleteFromListControl(IDC_LV_PAY_TO_ENTITY_LIST);
}

//******************************************************************************
void PayToEntityDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel = GetList(IDC_LV_PAY_TO_ENTITY_LIST)->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);
   const DString *crtKey = &getParent()->getCurrentListItemKey (this, IFASTBP_PROC::PAY_TO_ENTITY_LIST);

   if (getParent()->performSearch(this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, SEARCH_NEXT_BLOCK ) <= WARNING)
   {
      LoadListControl(IDC_LV_PAY_TO_ENTITY_LIST);
      if (*crtKey != NULL_STRING)
      {
         GetList(IDC_LV_PAY_TO_ENTITY_LIST)->SetSelection(crtKey);
      }
   }
   GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist (this, IFASTBP_PROC::PAY_TO_ENTITY_LIST));
   GetList(IDC_LV_PAY_TO_ENTITY_LIST)->SetSelection(cursel, true, true);
}

//****************************************************************
void PayToEntityDlg::OnBtnReset()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnReset"));

   CWaitCursor wait;

   ResetListItem(IDC_LV_PAY_TO_ENTITY_LIST);
}

//*************************************************************************
void PayToEntityDlg::OnBtnAdmDates()
{
   ShowAdminDates (IFASTBP_PROC::PAY_TO_ENTITY_LIST);
}

//******************************************************************
void PayToEntityDlg::OnBtnInstructions()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnInstructions"));
   CWaitCursor wait;
   E_COMMANDRETURN eRtn = CMD_CANCEL;

   DString payToEntity;

   getParent()->getField(this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
      ifds::PayToEntity, payToEntity, false);
   if (payToEntity != NULL_STRING)
   {
      try
      {
         DString brokerCode, paymentFor;

         getParent()->getField ( this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                                 ifds::BrokerCode, brokerCode);
         getParent()->getField ( this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                                 ifds::PayToEntity, payToEntity, false);
         getParent()->getField ( this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                                 ifds::PaymentFor, paymentFor, false);
         setParameter (MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
         setParameter (MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, m_dstrSearchTypeMgmt);

         if (m_dstrSearchTypeMgmt == I_("MGMTCO"))
         {
            setParameter( I_("PayToEntity"), I_("CLIENT"));
            setParameter( I_("PaymentFor"), I_("CO") );
         }
         else
         {
            setParameter(I_("PayToEntity"), payToEntity);
            setParameter(I_("PaymentFor"), paymentFor);
         }
         eRtn = invokeCommand ( getParent(), CMD_BPROC_PAYMENT_INSTRUCTIONS, 
                                PROC_SUPPORT, true, NULL);
         switch (eRtn)
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
            case CMD_CANCEL:
               break;
            default:
               // Display error
               ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
               break;
         }
      }
      catch (ConditionException &ce)
      {
         ConditionMessageBox(ce);
      }
      catch (...)
      {
         DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
      }
   }
}

//******************************************************************
void PayToEntityDlg::OnDblclkPayToEntityList (NMHDR* pNMHDR, LRESULT* pResult) 
{
   OnBtnInstructions();
   *pResult = 0;
}

//******************************************************************
BOOL PayToEntityDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   //do not allow F4 on the edit controls that are not updateable
   if (pMsg->message == WM_KEYDOWN && 
      (int)(pMsg->wParam) == VK_F4 && 
      !IsSelectedCtrlUpdateable())
   {
      return TRUE;
   }
   if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4)
   {
      m_pWndItemInFocus = GetFocus();
      if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_BROKER_CODE))
      {
         PostMessage(UM_OPENBROKERLISTDLG);
      }
   }
   return BaseMainDlg::PreTranslateMessage(pMsg);
}


//******************************************************************
void PayToEntityDlg::DoListItemChanged(UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   if( listControlID == IDC_LV_PAY_TO_ENTITY_LIST )
   {

      if ( m_dstrSearchTypeMgmt != I_("MGMTCO") ) 
      {
         // History
         GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( !(bIsNewItem || bIsDummyItem) );
         //instructions
         DString brokerActive;

         getParent()->getField ( this, 
                                 IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                                 BrokerActive, 
                                 brokerActive);

         //disable the instructions button if the broker is not active/effective
         GetDlgItem (IDC_BTN_PAYMENT_INSTRUCTIONS)->EnableWindow (brokerActive == I_("Y"));
      }
   }
}

//******************************************************************************
bool PayToEntityDlg::doDisablePermCheckButton(UINT nID)
{
   TRACE_METHOD( CLASSNAME, I_( "doDisablePermCheckButtons" ));
   bool bDisableFlag = false;

   if (nID == IDC_BTN_DELETE)
   {
      DString dstrPayInstructExists;
      getParent()->getField( this, 
                            IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                            ifds::PayInstructExists, 
                            dstrPayInstructExists, 
                            false);
     dstrPayInstructExists.stripAll().upperCase();
     bDisableFlag = ( I_( "Y" ) == dstrPayInstructExists );
   }

   return( bDisableFlag );
}

//*************************************************************************
LRESULT PayToEntityDlg::OpenBrokerListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenBrokerListDlg"));
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      DString brokerCode;

      getParent()->getField(this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
         ifds::BrokerCode, brokerCode);
      setParameter(MFCAN_IP_PARAM::CALLER, I_("PaymentInstructions"));
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      eRtn = invokeCommand (getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL);
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter (MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
               if (!brokerCode.empty())
               {
                  getParent()->setField ( this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
                                          ifds::BrokerCode, brokerCode);
               }
               LoadControl (IDC_EDT_BROKER_CODE);
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
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
   return eRtn;
}

//*************************************************************************
bool PayToEntityDlg::discardUpdates()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("discardUpdates"));
   bool bDiscard = getUpdateFlag();
   
   if (!bDiscard)
   {
      bDiscard = true;
      BFWorkSession *bfWorkSession = getBFWorkSession();

      if (bfWorkSession && bfWorkSession->hasNonHostUpdates())
      {
         DiscardMsgDlg discardDlg ( NULL, 
                                    TXT_DISCARD_MSGA, 
                                    TXT_DISCARD_MSGB, 
                                    TXT_DISCARD);

         if (discardDlg.DoModal() == IDCANCEL)
         {
            bDiscard = false;
         }
         else 
         {
            //discard everything and close the dialogs
            getGIContainer()->destroyGUIChildren (this);
            //and cleanup the work session
            bfWorkSession->cleanupWorkSession();
         }
      }
   }
   return bDiscard;
}

//******************************************************************************
bool PayToEntityDlg::ListViewControlFilter (long lSubstituteId, const DString *strKey)
{
   bool bShow = true;

   if (lSubstituteId == ifds::PayToEntityListHeading.getId())
   {
      DString brokerCode;

      getParent()->getField (this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, ifds::BrokerCode, brokerCode);
      brokerCode.stripAll().upperCase();
      bShow = m_dstrBrokerCode == NULL_STRING || m_dstrBrokerCode == brokerCode;
   }
   return bShow;
}

//******************************************************************
void PayToEntityDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;
   
   // Set Parameters
   DString dstrBrokerCode;
   getParent()->getField(this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, ifds::BrokerCode, dstrBrokerCode);
   dstrBrokerCode.stripAll().upperCase();
   setParameter( I_("BROKER"), dstrBrokerCode );

   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/PayToEntityDlg.cpp-arc  $
// 
//    Rev 1.27   Jun 11 2008 06:39:10   daechach
// in#1222106 - Stop Dates not picking up properly in Pay Entities and Pay Instructions
// 
//    Rev 1.26   Sep 07 2006 21:39:08   popescu
// STP 2192/02
// 
//    Rev 1.25   Aug 28 2006 15:41:58   ZHANGCEL
// PET2212 FN10 -- Added new logic for Netting Bulking Redemption and Distribution Payment
// 
//    Rev 1.24   Jul 31 2006 11:16:36   porteanm
// Incident 640733 - syncup - Disable the Delete button in Pay to Entity when PayInstructions already exist for PayEntity. Added PayInstructExists to view 258.
// 
//    Rev 1.23   Jul 31 2006 11:08:58   ZHANGCEL
// PET2192 FN11 -- Add a new parameter
// 
//    Rev 1.22   Jul 27 2006 18:04:00   ZHANGCEL
// PET2192 FN11 - Commission Payments to MgmtCo related changes
// 
//    Rev 1.21   Sep 15 2005 15:14:38   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.20   Aug 22 2005 10:53:30   ZHANGCEL
// PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
// 
//    Rev 1.19   Mar 04 2004 18:43:02   popescu
// PTS 10027865, synch-up release 55.0.4, 1.16.1.1
// 
//    Rev 1.18   Mar 04 2004 17:57:20   popescu
// PTS 10027865, fsynch-up release 55.0.4, 1.16.1.0
// 
//    Rev 1.17   Feb 27 2004 15:58:22   HERNANDO
// PET965 FN11 - Enable/Disable Historical Button based on list item in doListItemChanged.
// 
//    Rev 1.16   Feb 18 2004 18:01:26   popescu
// PTS 10027184; - moved the ownership of the payment instructions banking list at the payment instructions CBO level.
// - clean-up the work session every time user hits 'Search' on the Features Search Dialog
// - do not add payment instructions/ pay to entity records, when refreshing the respective CBO lists in DistributorRepository, always read them from back-end. Now, this is possible since the work session is cleaned-up all the time.
// - fixed crash that happens when a new record is added to the payment instructions bank list. The scenario to get this crash is: go to pay to entity screen, then click the 'instructions' button, modify an existing payment instructions record with bank information. Hit okay, commit the changes in the parent. Go back to the payment instructions (you will notice that the previous changes are not saved -  another issue that has been fixed with this ticket), and then click the Bank button. Add a new bank record. Desktop reports an internal error.
// - use new IFDSListCtrl, for the PayToEntity list and PaymentInstructions list.
// 
//    Rev 1.15   Oct 31 2003 16:04:28   HERNANDO
// PTS 10022670 - Passing Broker Code.
// 
//    Rev 1.14   Sep 05 2003 09:55:04   popescu
// fixed showing the discard dialog twice in some cases
// 
//    Rev 1.13   Sep 02 2003 18:02:48   popescu
// convert to uppercas what comes from back-end in the filtering procedure
// 
//    Rev 1.12   Aug 20 2003 19:51:12   popescu
// PTS 10020922,
// the payment instructions screen is launched as modal and as support from pay to entity. This will ensure that all transactions in payment instructions will be commited to the parent group id and will be sent after the pay to entity transactions are sent
// 
//    Rev 1.11   Aug 17 2003 16:12:50   popescu
// fixed 52 crash in regards with the Historical button
// 
//    Rev 1.10   Aug 14 2003 13:50:38   HERNANDO
// Added OnBtnHistorical.
// 
//    Rev 1.9   Aug 07 2003 17:07:40   popescu
// payment instructions is no modeless
// 
//    Rev 1.8   Aug 07 2003 15:04:44   popescu
// Call payment instruction modal, instead of modeless
// 
//    Rev 1.7   Aug 01 2003 13:27:10   popescu
// disable/enable the Instructions button if the pay to entity type is empty string
// 
//    Rev 1.6   Jul 26 2003 21:20:34   popescu
// worked on setting the caption of the payment instructions dialog
// 
//    Rev 1.5   Jul 25 2003 14:26:26   popescu
// Fix crash in payment instructions dialog, as result of filtering the payment instructions list, cleared the address fields when the checque option is selected for the payment method
// 
//    Rev 1.4   Jul 23 2003 18:19:52   popescu
// changed list controls to the new IFDSListCtrl
// 
//    Rev 1.3   Jul 10 2003 22:21:46   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.2   Jul 09 2003 21:57:46   popescu
// Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
// 
//    Rev 1.1   Jul 01 2003 18:08:12   popescu
// Clean-up the code, new business rules, set the broker name to the dialog caption, etc...
// 
//    Rev 1.0   Jun 27 2003 18:18:12   popescu
// Initial revision.
// 
*/

