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
// ^FILE   : ShrFundSponsorAgreementDlg.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : ShrFundSponsorAgreement
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#include "ShrFundSponsorAgreementdlg.h"

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\ShrFundSponsorAgreementprocessincludes.h>

#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\dstcworksession.hpp>

#include <uibase\DSTEdit.h>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SHR_FUND_SPONSOR_AGREEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_SHR_FUND_SPONSOR_AGREEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<ShrFundSponsorAgreementDlg> dlgCreator( CMD_GUI_SHR_FUND_SPONSOR_AGREEMENT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("ShrFundSponsorAgreement");
   const I_CHAR *LV_SHR_FUND_SPONSOR_AGREEMENT_LIST = I_("ShrFundSponsorAgreementList");   
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
	 extern CLASS_IMPORT I_CHAR * const SHR_FUND_SPONSOR_AGREEMENT;
}

namespace ifds
{
   //field ids used	
   extern CLASS_IMPORT const BFTextFieldId ShrFundSpAgrmntHeading;   		
}



class LVShrFundSponsorAgreementData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVShrFundSponsorAgreementData() {}
   DString FundGroup_;
   DString FundGroupDesc_;
   DString EffectiveDate_; 
	DString DistribCoopAgrmnt_;   
	
   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FundGroup,         FundGroup_ );
      FundGroup_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FundGroupDesc,     FundGroupDesc_ );
      FundGroupDesc_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::EffectiveDate,     EffectiveDate_ );
      EffectiveDate_.strip();  		
	   pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::DistribCoopAgrmnt, DistribCoopAgrmnt_ );
      DistribCoopAgrmnt_.strip();      
   }
};

class LVShrFundSponsorAgreementAdapter : public IFDSListCtrlAdapter< LVShrFundSponsorAgreementData >
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
      else if (*pFieldId == ifds::FundGroup) 
      {
         result = i_strcmp(pData1->FundGroup_.c_str(), pData2->FundGroup_.c_str());
      } 
		else if (*pFieldId == ifds::FundGroupDesc) 
      {
         result = i_strcmp(pData1->FundGroupDesc_.c_str(), pData2->FundGroupDesc_.c_str());
      } 
      else if (*pFieldId == ifds::EffectiveDate) 
      {	
			if ( DSTCommonFunctions::CompareDates( pData1->EffectiveDate_.c_str(), pData2->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = 1;
			else if ( DSTCommonFunctions::CompareDates( pData2->EffectiveDate_.c_str(), pData1->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = -1;
			// for equal, result will be 0         
      }    				
		else if (*pFieldId == ifds::DistribCoopAgrmnt) 
      {
         result = i_strcmp(pData1->DistribCoopAgrmnt_.c_str(), pData2->DistribCoopAgrmnt_.c_str());
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
         else if (*pFieldId == ifds::FundGroup) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundGroup_.c_str();
         } 
         else if (*pFieldId == ifds::FundGroupDesc) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundGroupDesc_.c_str();
         } 
			else if (*pFieldId == ifds::EffectiveDate)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->EffectiveDate_.c_str();
         }          
         else if (*pFieldId == ifds::DistribCoopAgrmnt) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->DistribCoopAgrmnt_.c_str();
         } 
         
         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
ShrFundSponsorAgreementDlg::ShrFundSponsorAgreementDlg( CWnd* pParent, 
   GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(ShrFundSponsorAgreementDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_pWndItemInFocus(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(ShrFundSponsorAgreement)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void ShrFundSponsorAgreementDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ShrFundSponsorAgreement)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY ShrFundSponsorAgreementDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter( SHR_FUND_SPONSOR_AGREEMENT::ACCOUNT_NUMBER,     _dstrAccount );
	getParameter( SHR_FUND_SPONSOR_AGREEMENT::SHAREHOLDER_NUMBER, _dstrShareholder );	
	   
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(ShrFundSponsorAgreementDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ShrFundSponsorAgreement)
ON_BN_CLICKED(IDC_BTN_ADMIN_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL ShrFundSponsorAgreementDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*****************************************************************************
void ShrFundSponsorAgreementDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);
   
	IFDSListCtrl* ifdsListControlShrFundSponsorAgreement = 
      new IFDSAdaptedListCtrl< LVShrFundSponsorAgreementAdapter >( this, 
		                                                      CLASSNAME, 
                                                            IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST, 
																				0, 
																				0, 
																				true, 
																				true );

   AddIFDSListControl( ifdsListControlShrFundSponsorAgreement, 
							  LV_SHR_FUND_SPONSOR_AGREEMENT_LIST, 
							  IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST, 
                       ifds::ShrFundSpAgrmntHeading );   

	// Default the sorting column to Fund Sponsor Code
	if ( NULL != ifdsListControlShrFundSponsorAgreement )		
		ifdsListControlShrFundSponsorAgreement->SortOnColumn( 2 );
	
	AddControl( CTRL_COMBO, 
		         IDC_CMB_FUND_SPONSOR_CODE, 
					IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST, 
               ifds::FundGroup, 
					CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST);

	AddControl( CTRL_STATIC, 
		         IDC_LBL_FUND_SPONSOR_DESC, 
					IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST, 
               ifds::FundGroupDesc, 
					CTRLFLAG_DEFAULT, 
					(UINT)IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST ); 
	
	  AddControl( CTRL_DATE, 
		         IDC_DTP_EFFECTIVE_DATE, 
					IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST, 
					ifds::EffectiveDate, 
					0, 
					IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST );    
	 
	AddControl( CTRL_COMBO, 
		         IDC_CMB_DISTRIB_COOP_AGRMNT, 
					IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST, 
               ifds::DistribCoopAgrmnt, 
					CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST);

   doRefresh(this, NULL);
}


//******************************************************************************
bool ShrFundSponsorAgreementDlg::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   //when called by the process from doRefresh, 	
   if (DString(szOriginalCommand) == I_("ReloadParams"))
   {
      getParameter( SHR_FUND_SPONSOR_AGREEMENT::ACCOUNT_NUMBER,     _dstrAccount );
		getParameter( SHR_FUND_SPONSOR_AGREEMENT::SHAREHOLDER_NUMBER, _dstrShareholder );
   }
    
   //this will load the connected controls
   LoadListControl( IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST );    
   
   DSTListCtrl *pPIDSTListCtrl = GetList( IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST );

   if( pPIDSTListCtrl )
   {
     if( pPIDSTListCtrl->GetItemCount() <= 0 )
     {         
         //add a new row if list is empty, to simulate the normal behaviour
         AddToListControl(IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST);
      }
   }
	
   SetDlgCaption();

	GetDlgItem( IDC_BTN_ADD )->EnableWindow( hasCreatePermission( UAF::SHR_FUND_SPONSOR_AGREEMENT ) );
	GetDlgItem( IDC_BTN_DELETE )->EnableWindow( hasDeletePermission( UAF::SHR_FUND_SPONSOR_AGREEMENT ) );
	GetDlgItem( IDOK )->EnableWindow( hasCreatePermission( UAF::SHR_FUND_SPONSOR_AGREEMENT ) ||
		                               hasUpdatePermission( UAF::SHR_FUND_SPONSOR_AGREEMENT ) ||
												 hasDeletePermission( UAF::SHR_FUND_SPONSOR_AGREEMENT ) );	

	GetDlgItem( IDC_BTN_RESET )->EnableWindow( hasCreatePermission( UAF::SHR_FUND_SPONSOR_AGREEMENT ) ||
															 hasUpdatePermission( UAF::SHR_FUND_SPONSOR_AGREEMENT ) ||
															 hasDeletePermission( UAF::SHR_FUND_SPONSOR_AGREEMENT ) );
	
   return true;
}

//*************************************************************************
void ShrFundSponsorAgreementDlg::SetDlgCaption()
{
   DString dstrCaption = I_("Daily Transaction Fees"); 

	DString dstrEntityName;
	dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),
																																	 _dstrAccount,
																																	 dstrEntityName );
   SetShrAcctCaption( _dstrShareholder, _dstrAccount, dstrEntityName );
}

//*************************************************************************
void ShrFundSponsorAgreementDlg::ControlUpdated( UINT controlID, 
															 const DString &strValue )
{   
   switch( controlID )
   {		
		case IDC_CMB_FUND_SPONSOR_CODE:
			{							
				LoadControl( IDC_LBL_FUND_SPONSOR_DESC );
			}
			break;					
		default:
			break;
	}
}

//******************************************************************************
void ShrFundSponsorAgreementDlg::OnBtnAdd()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnAdd"));

   CWaitCursor wait;

   AddToListControl( IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST );
}

//******************************************************************************
void ShrFundSponsorAgreementDlg::OnBtnDelete()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnDelete"));

   CWaitCursor wait;
 
	DeleteFromListControl( IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST );
}

//****************************************************************
void ShrFundSponsorAgreementDlg::OnBtnReset()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnReset"));

   CWaitCursor wait;

   ResetListItem(IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST);
}

//*************************************************************************
void ShrFundSponsorAgreementDlg::OnBtnAdmDates()
{
   ShowAdminDates( IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST );
}

//******************************************************************
BOOL ShrFundSponsorAgreementDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   //do not allow F4 on the edit controls that are not updateable   
	if (pMsg->message == WM_KEYDOWN && 
      (int)(pMsg->wParam) == VK_F4 && 
      !IsSelectedCtrlUpdateable())
   {
      return TRUE;
   }   	
	
   return BaseMainDlg::PreTranslateMessage(pMsg);
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/ShrFundSponsorAgreementDlg.cpp-arc  $
// 
//    Rev 1.4   Sep 15 2005 15:15:16   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   Aug 19 2004 12:03:52   VADEANUM
// PET1117 FN01 - Shareholder Static Data - Reset button.
// 
//    Rev 1.2   Jul 28 2004 14:45:56   VADEANUM
// PET1117 FN01 - Shareholder Static Data - Add/Delete/Ok buttons.
// 
//    Rev 1.1   Jul 27 2004 15:50:20   VADEANUM
// PET1117 FN01 - Shareholder Static Data - first working version.
// 
//    Rev 1.0   Jul 26 2004 10:35:12   VADEANUM
// Initial revision.
//
