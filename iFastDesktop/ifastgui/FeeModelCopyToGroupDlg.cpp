#include "stdafx.h"
#include "feemodelcopytogroupdlg.h"

#include <bfproc\concretedialogcreator.hpp>

#include <uibase\ifdslistctrl.h>
#include <uibase\dstcombobox.h>

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FeeModelSrc;
   extern CLASS_IMPORT const BFTextFieldId GroupDest;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCopyToGroupHeading;
}

namespace IFASTBP_PROC
{
   extern CLASS_IMPORT const BFContainerId FEE_MODEL_COPY_TO_GROUP;
}

namespace UAF
{
    extern CLASS_IMPORT I_CHAR * const FEE_MODEL;
}

namespace
{
   const I_CHAR *CLASSNAME                         = I_("FeeModelCopyToGroupDlg");
   const I_CHAR *const LV_FEE_MODEL_COPY_TO_GROUP  = I_("FeeModelCopyToGroupList");
}

//******************************************************************************
class LVFeeModelCopyToGroupData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVFeeModelCopyToGroupData() {}

   DString fFeeModelSrc, fGroupDest;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::FeeModelSrc, fFeeModelSrc); 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::GroupDest, fGroupDest); 
   }
};

//******************************************************************************
class LVFeeModelCopyToGroupAdapter : public IFDSListCtrlAdapter< LVFeeModelCopyToGroupData >
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

         // Force list to sort by repeat count from view as view already sort record
         pCtrl->sortByInsertionOrder();
      } 
      else if (NULL == pFieldId) 
      {
         return (0);
      }
      else if (*pFieldId == ifds::FeeModelSrc) 
      {
         result = i_strcmp( pData1->fFeeModelSrc.c_str(), pData2->fFeeModelSrc.c_str() );
      }
      else if (*pFieldId == ifds::GroupDest) 
      {
         result = i_strcmp( pData1->fGroupDest.c_str(), pData2->fGroupDest.c_str() );
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
         else if (*pFieldId == ifds::FeeModelSrc)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fFeeModelSrc.c_str();
         }
         else if (*pFieldId == ifds::GroupDest)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fGroupDest.c_str();
         }

         return (1);
      }

      return (0);
   }
};

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FEE_MODEL_COPY_TO;

static ConcreteDialogCreator< FeeModelCopyToGroupDlg > dlgCreator( CMD_GUI_FEE_MODEL_COPY_TO );

BEGIN_MESSAGE_MAP(FeeModelCopyToGroupDlg, BaseMainDlg)
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAddFeeModelCopiedRecord )
ON_BN_CLICKED( IDC_BTN_DEL, OnBtnDelFeeModelCopiedRecord )
END_MESSAGE_MAP()

//******************************************************************************
FeeModelCopyToGroupDlg::FeeModelCopyToGroupDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand)
      :BaseMainDlg(FeeModelCopyToGroupDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME)
{

}

//******************************************************************************
FeeModelCopyToGroupDlg::~FeeModelCopyToGroupDlg(void)
{
}

//******************************************************************************
BOOL FeeModelCopyToGroupDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void FeeModelCopyToGroupDlg::OnPostInitDialog()
{
   SetUserAccesFunctionCode (UAF::FEE_MODEL);
   addControlGroupIDForPermissionCheck(0);

   IFDSListCtrl* ifdsListControlFeeModelCopyToGroup = 
      new IFDSAdaptedListCtrl< LVFeeModelCopyToGroupAdapter >( this, 
                                                            CLASSNAME, 
                                                            IDC_LIST_FEE_MODEL_TO_GROUP, 
                                                            0, 
                                                            LISTFLAG_NOT_AUTO_ADD, 
                                                            true, 
                                                            true );

   AddIFDSListControl(ifdsListControlFeeModelCopyToGroup, 
                      LV_FEE_MODEL_COPY_TO_GROUP, 
                      IFASTBP_PROC::FEE_MODEL_COPY_TO_GROUP, 
                      ifds::FeeModelCopyToGroupHeading); 

   if (NULL != ifdsListControlFeeModelCopyToGroup)
      ifdsListControlFeeModelCopyToGroup->SortOnColumn(1);

   AddControl(CTRL_COMBO,IDC_CMB_SRC_FEE_MODEL,IFASTBP_PROC::FEE_MODEL_COPY_TO_GROUP, ifds::FeeModelSrc,CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LIST_FEE_MODEL_TO_GROUP );
   AddControl(CTRL_COMBO,IDC_CMB_DEST_GROUP,IFASTBP_PROC::FEE_MODEL_COPY_TO_GROUP, ifds::GroupDest,CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LIST_FEE_MODEL_TO_GROUP );
   
   AddControl(CTRL_STATIC,IDC_STC_SRC_FEE_MODEL);
   AddControl(CTRL_STATIC,IDC_STC_DEST_GROUP);

   AddToListControl (IDC_LIST_FEE_MODEL_TO_GROUP);

   ConnectListToData(IDC_LIST_FEE_MODEL_TO_GROUP, true);
   ConnectControlsToData(IDC_LIST_FEE_MODEL_TO_GROUP,true);

   doRefresh(this, NULL_STRING);
}

//******************************************************************************
void FeeModelCopyToGroupDlg::OnBtnReset()
{
   getParent()->reset(this, IFASTBP_PROC::FEE_MODEL_COPY_TO_GROUP);
   doRefresh(this, NULL_STRING);
}

//******************************************************************************
bool FeeModelCopyToGroupDlg::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
   LoadListControl(IDC_LIST_FEE_MODEL_TO_GROUP);
   LoadControls(IDC_LIST_FEE_MODEL_TO_GROUP);

   return(true);
}

//******************************************************************************
void FeeModelCopyToGroupDlg::OnBtnAddFeeModelCopiedRecord () 
{
   AddToListControl(IDC_LIST_FEE_MODEL_TO_GROUP);
   GetDlgItem(IDC_CMB_SRC_FEE_MODEL)->SetFocus();
}

//******************************************************************************
void FeeModelCopyToGroupDlg::OnBtnDelFeeModelCopiedRecord () 
{
   DeleteFromListControl(IDC_LIST_FEE_MODEL_TO_GROUP);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/FeeModelCopyToGroupDlg.cpp-arc  $
// 