//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : InvDetlDeductionDlg.cpp
// ^AUTHOR : Amelia Aguila
// ^DATE   : Jan 2005
//
// ----------------------------------------------------------
//
// ^CLASS    : InvDetlDeduction
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#include "InvDetlDeductiondlg.h"

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\InvDetlDeductionprocessincludes.h>

#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\dstcworksession.hpp>

#include <uibase\DSTEdit.h>


extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INVENTORY_DETAIL_DEDUCTION;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_INVENTORY_DETAIL_DEDUCTION;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<InvDetlDeductionDlg> dlgCreator( CMD_GUI_INVENTORY_DETAIL_DEDUCTION );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("InvDetlDeduction");
   const I_CHAR *LST_LSIF_CLAWBACK_INFO = I_("InvDetlDeductionList");   
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}


namespace ifds
{
   //field ids used	
   extern CLASS_IMPORT const BFTextFieldId InvDetlDeduction;   		
}



class InvDetlDeductionData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~InvDetlDeductionData() {}
   DString InvSummId_;
   DString InvDetlId_;
   DString DeductDesc_; 
	DString LSIFCode_;   
	DString ChargedAmount_;   
	DString DeductUnits_;   
   DString BasedOn_;   
   DString BasedOnValue_;
   DString CalculatedAmount_;


   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::InvSummId,   InvSummId_ );
      InvSummId_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::InvDetlId,    InvDetlId_ );
      InvDetlId_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::DeductDesc,   DeductDesc_ );
      DeductDesc_.strip();  		
	   pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::LSIFCode, LSIFCode_ );
      LSIFCode_.strip();      
		pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::ChargedAmount, ChargedAmount_ );
      ChargedAmount_.strip();
		pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::DeductUnits, DeductUnits_ );
      DeductUnits_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::BasedOn, BasedOn_ );
      BasedOn_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::BasedOnValue, BasedOnValue_ );
      BasedOnValue_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::CalculatedAmount, CalculatedAmount_ );
      CalculatedAmount_.strip();
   }
};

class LVInvDetlDeductionAdapter : public IFDSListCtrlAdapter< InvDetlDeductionData >
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
      else if (*pFieldId == ifds::InvSummId)
      {
         int iInvSummId1 = pData1->InvSummId_.asInteger();
         int iInvSummId2 = pData2->InvSummId_.asInteger();
         if ( iInvSummId1 > iInvSummId2 )
				result = 1;
			else if ( iInvSummId1 < iInvSummId2 )
				result = -1;
      }
      else if (*pFieldId == ifds::InvDetlId) 
      {         
			int iInvDetlId1 = pData1->InvDetlId_.asInteger();
			int iInvDetlId2 = pData2->InvDetlId_.asInteger();
			if ( iInvDetlId1 > iInvDetlId2 )
				result = 1;
			else if ( iInvDetlId1 < iInvDetlId2 )
				result = -1;
			// for equal result should be 0
      } 
		else if (*pFieldId == ifds::DeductDesc) 
      {
         result = i_strcmp(pData1->DeductDesc_.c_str(), pData2->DeductDesc_.c_str());
      } 

      else if (*pFieldId == ifds::LSIFCode) 
      {
         result = i_strcmp(pData1->LSIFCode_.c_str(), pData2->LSIFCode_.c_str());
      } 

      else if (*pFieldId == ifds::ChargedAmount) 
      {         
			double dblChargedAmount1 = DSTCommonFunctions::convertToDouble ( pData1->ChargedAmount_.c_str() );
			double dblChargedAmount2 = DSTCommonFunctions::convertToDouble ( pData2->ChargedAmount_.c_str() );         			
			if ( dblChargedAmount1 > dblChargedAmount2 )
				result = 1;
			else if ( dblChargedAmount1 < dblChargedAmount2 )
				result = -1;
			// for equal result will be 0;
      } 

      else if (*pFieldId == ifds::DeductUnits) 
      {         
			double dblDeductUnits1 = DSTCommonFunctions::convertToDouble ( pData1->DeductUnits_.c_str() );
			double dblDeductUnits2 = DSTCommonFunctions::convertToDouble ( pData2->DeductUnits_.c_str() );         			
			if ( dblDeductUnits1 > dblDeductUnits2 )
				result = 1;
			else if ( dblDeductUnits1 < dblDeductUnits2 )
				result = -1;
			// for equal result will be 0;
      } 

      else if (*pFieldId == ifds::BasedOn) 
      {
         result = i_strcmp(pData1->BasedOn_.c_str(), pData2->BasedOn_.c_str());
      } 

      else if (*pFieldId == ifds::BasedOnValue) 
      {         
			double dblBasedOnValue1 = DSTCommonFunctions::convertToDouble ( pData1->BasedOnValue_.c_str() );
			double dblBasedOnValue2 = DSTCommonFunctions::convertToDouble ( pData2->BasedOnValue_.c_str() );         			
			if ( dblBasedOnValue1 > dblBasedOnValue2 )
				result = 1;
			else if ( dblBasedOnValue1 < dblBasedOnValue2 )
				result = -1;
			// for equal result will be 0;
      }       

      else if (*pFieldId == ifds::CalculatedAmount) 
      {         
			double dblCalculatedAmount1 = DSTCommonFunctions::convertToDouble ( pData1->CalculatedAmount_.c_str() );
			double dblCalculatedAmount2 = DSTCommonFunctions::convertToDouble ( pData2->CalculatedAmount_.c_str() );         			
			if ( dblCalculatedAmount1 > dblCalculatedAmount2 )
				result = 1;
			else if ( dblCalculatedAmount1 < dblCalculatedAmount2 )
				result = -1;
			// for equal result will be 0;
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
         else if (*pFieldId == ifds::InvSummId) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->InvSummId_.c_str();
         } 
         else if (*pFieldId == ifds::InvDetlId) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->InvDetlId_.c_str();
         } 
         else if (*pFieldId == ifds::DeductDesc) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->DeductDesc_.c_str();
         } 
         else if (*pFieldId == ifds::LSIFCode)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->LSIFCode_.c_str();
         } 
         else if (*pFieldId == ifds::ChargedAmount)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->ChargedAmount_.c_str();
         }          
         else if (*pFieldId == ifds::DeductUnits)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->DeductUnits_.c_str();
         }          
         else if (*pFieldId == ifds::BasedOn)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BasedOn_.c_str();
         }          
         else if (*pFieldId == ifds::BasedOnValue)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BasedOnValue_.c_str();
         }          
         else if (*pFieldId == ifds::CalculatedAmount)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->CalculatedAmount_.c_str();
         }          

         return (1);
      }
      return (0);
   }
};


//*****************************************************************************
// Public methods
//*****************************************************************************
InvDetlDeductionDlg::InvDetlDeductionDlg( CWnd* pParent, 
												GenericInterfaceContainer* pGIC, 
												GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(InvDetlDeductionDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_pWndItemInFocus(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(InvDetlDeduction)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void InvDetlDeductionDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(InvDetlDeduction)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY InvDetlDeductionDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter( INV_DETL_DEDUCT::ACCOUNT_NUMBER,     _dstrAccount );
	getParameter( INV_DETL_DEDUCT::SHAREHOLDER_NUMBER, _dstrShareholder );	
   getParameter( INV_DETL_DEDUCT::TRANS_ID,           _dstrTransId);
	   
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(InvDetlDeductionDlg, BaseMainDlg)
//{{AFX_MSG_MAP(InvDetlDeduction)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL InvDetlDeductionDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*****************************************************************************
void InvDetlDeductionDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);

	AddControl( CTRL_STATIC, 
		         IDC_TXT_TRANS_ID, 
					IFASTBP_PROC::TRANS_LIST, 
					ifds::TransId, 
					CTRLFLAG_DEFAULT);

	AddControl( CTRL_STATIC, 
		         IDC_TXT_TRANS_NUM, 
					IFASTBP_PROC::TRANS_LIST, 
					ifds::TransNum, 
					CTRLFLAG_DEFAULT );

	AddControl( CTRL_STATIC, 
		         IDC_TXT_TRANS_TYPE, 
					IFASTBP_PROC::TRANS_LIST, 
					ifds::TransType, 
					CTRLFLAG_DEFAULT );

	AddControl( CTRL_DATE, 
		         IDC_TRADE_DATE, 
					IFASTBP_PROC::TRANS_LIST, 
               ifds::TradeDate, 
					CTRLFLAG_DEFAULT ); 

	AddControl( CTRL_DATE, 
		         IDC_SETTLE_DATE, 
					IFASTBP_PROC::TRANS_LIST, 
					ifds::SettleDate, 
					CTRLFLAG_DEFAULT );	
	
	AddControl( CTRL_STATIC, 
		         IDC_TXT_GROSS_AMT, 
					IFASTBP_PROC::TRANS_LIST, 
               ifds::GrossAmt, 
					CTRLFLAG_DEFAULT); 

	AddControl( CTRL_STATIC, 
		         IDC_TXT_TOTAL_UNITS, 
					IFASTBP_PROC::TRANS_LIST, 
               ifds::Units, 
					CTRLFLAG_DEFAULT);

   
	IFDSListCtrl* ifdsListControlInvDetlDeduction = 
      new IFDSAdaptedListCtrl< LVInvDetlDeductionAdapter >( this, 
		                                                      CLASSNAME, 
                                                            IDC_LST_LSIF_CLAWBACK_INFO, 
																				0, 
																				0, 
																				true, 
																				true );

   AddIFDSListControl( ifdsListControlInvDetlDeduction, 
							  LST_LSIF_CLAWBACK_INFO, 
							  IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST, 
                       ifds::InvDetlDeduction );   

	// Default the sorting column to InvSummId
	if ( NULL != ifdsListControlInvDetlDeduction )		
		ifdsListControlInvDetlDeduction->SortOnColumn( 1 ); 


   doRefresh(this, NULL);
}


//******************************************************************************
bool InvDetlDeductionDlg::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   //when called by the process from doRefresh, 	
   if (DString(szOriginalCommand) == I_("ReloadParams"))
   {
      getParameter( INV_DETL_DEDUCT::ACCOUNT_NUMBER,     _dstrAccount );
		getParameter( INV_DETL_DEDUCT::SHAREHOLDER_NUMBER, _dstrShareholder );
      getParameter( INV_DETL_DEDUCT::TRANS_ID,           _dstrTransId );
   }
   

   GetControl(IDC_TXT_TRANS_ID)->ConnectToData(true);
   GetControl(IDC_TXT_TRANS_NUM)->ConnectToData(true);
   GetControl(IDC_TXT_TRANS_TYPE)->ConnectToData(true);
   GetControl(IDC_TRADE_DATE)->ConnectToData(true);
   GetControl(IDC_SETTLE_DATE)->ConnectToData(true);
   GetControl(IDC_TXT_GROSS_AMT)->ConnectToData(true);
   GetControl(IDC_TXT_TOTAL_UNITS)->ConnectToData(true);

   LoadControls();

   GetControl(IDC_TRADE_DATE)->Enable(false);
   GetControl(IDC_SETTLE_DATE)->Enable(false);

   
   //this will load the connected controls
   LoadListControl( IDC_LST_LSIF_CLAWBACK_INFO );    
   
   GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST ) );
   
   DSTListCtrl *pPIDSTListCtrl = GetList( IDC_LST_LSIF_CLAWBACK_INFO );

   if( pPIDSTListCtrl )
   {
     if( pPIDSTListCtrl->GetItemCount() <= 0 )
     {         
         //add a new row if list is empty, to simulate the normal behaviour
         AddToListControl(IDC_LST_LSIF_CLAWBACK_INFO);
      }
   }
	
   SetDlgCaption();	
	
   return true;
}

//*************************************************************************
void InvDetlDeductionDlg::SetDlgCaption()
{
   DString dstrCaption = I_("Clawback Information"); 

	DString dstrEntityName;
	dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),
																																	 _dstrAccount,
																																	 dstrEntityName );
   SetShrAcctCaption( _dstrShareholder, _dstrAccount, dstrEntityName );
}

//******************************************************************************
void InvDetlDeductionDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel = GetList( IDC_LST_LSIF_CLAWBACK_INFO )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );
   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl(IDC_LST_LSIF_CLAWBACK_INFO);
      if (*crtKey != NULL_STRING)
      {
         GetList( IDC_LST_LSIF_CLAWBACK_INFO )->SetSelection( crtKey );
      }
   }

   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST));
   
	GetList( IDC_LST_LSIF_CLAWBACK_INFO )->SetSelection( cursel, true, true );
   
}

//******************************************************************
BOOL InvDetlDeductionDlg::PreTranslateMessage(MSG* pMsg) 
{
   return BaseMainDlg::PreTranslateMessage(pMsg);
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/InvDetlDeductionDlg.cpp-arc  $
// 
//    Rev 1.4   Sep 15 2005 15:13:34   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   Feb 22 2005 10:07:06   aguilaam
// PET1198_FN01: disable date fields on clawback info screen
// 
//    Rev 1.2   Feb 21 2005 15:10:36   aguilaam
// PET1198_FN01: LSIF ReasonCode enhancement
// 
//    Rev 1.1   Feb 17 2005 13:16:04   aguilaam
// PET1198_FN01: LSIF Reason Code enhancement. 
// 
//    Rev 1.0   Jan 28 2005 14:50:50   aguilaam
// Initial revision.
// 
