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
// ^FILE   : DailyTransactionFeesDlg.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : DailyTransactionFeesDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#include "dailytransactionfeesdlg.h"

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\DailyTransactionFeesprocessincludes.h>

#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastgui\ifasthistoricalinfo.hpp>

#include <uibase\DSTEdit.h>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DAILY_TRANSACTION_FEES;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_DAILY_TRANSACTION_FEES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<DailyTransactionFeesDlg> dlgCreator( CMD_GUI_DAILY_TRANSACTION_FEES );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("DailyTransactionFeesDlg");
   const I_CHAR *LV_DAILY_TRANSACTION_FEES_LIST = I_("DailyTransactionFeesList");   
   const I_CHAR *PERCENT = I_("1");   
   const I_CHAR *CLASS_HURDLE_RATE  = I_("201"); 
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   //field ids used	
   extern CLASS_IMPORT const BFTextFieldId ADLHeadingSet;   
	extern CLASS_IMPORT const BFTextFieldId FundName;	 
	extern CLASS_IMPORT const BFTextFieldId ADLHeadingSet;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const DAILY_TRANSACTIONS_FEES;
}


class LVDailyTransactionFeesData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVDailyTransactionFeesData() {}
   DString RecordType_;
   DString FeeCode_;
   DString FundCode_;
   DString ClassCode_;
   DString FundName_;   
	DString EffectiveDate_; 
	DString StopDate_; 
	DString FeeRate_; 
	DString FeeType_; 
	
   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::RecordType, RecordType_ );
      RecordType_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FeeCode, FeeCode_ );
      FeeCode_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FundCode, FundCode_ );
      FundCode_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::ClassCode, ClassCode_ );
      ClassCode_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FundName, FundName_ );
      FundName_.strip();    		
		pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::EffectiveDate, EffectiveDate_ );
      EffectiveDate_.strip();  
		pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::StopDate, StopDate_ );
      StopDate_.strip();  
		pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FeeRate, FeeRate_ );
      FeeRate_.strip();  
	  	pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::FeeType, FeeType_ );
      FeeType_.strip();  
   }
};

class LVDailyTransactionFeesAdapter : public IFDSListCtrlAdapter< LVDailyTransactionFeesData >
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
      else if (*pFieldId == ifds::RecordType) 
      {
         result = i_strcmp(pData1->RecordType_.c_str(), pData2->RecordType_.c_str());
      } 
		else if (*pFieldId == ifds::FeeCode) 
      {
         result = i_strcmp(pData1->FeeCode_.c_str(), pData2->FeeCode_.c_str());
      } 
      else if (*pFieldId == ifds::FundCode) 
      {
         result = i_strcmp(pData1->FundCode_.c_str(), pData2->FundCode_.c_str());
      } 
      else if (*pFieldId == ifds::ClassCode) 
      {
         result = i_strcmp(pData1->ClassCode_.c_str(), pData2->ClassCode_.c_str());
      } 
      else if (*pFieldId == ifds::FundName) 
      {
         result = i_strcmp(pData1->FundName_.c_str(), pData2->FundName_.c_str());
      }   
	  else if (*pFieldId == ifds::FeeType) 
      {
         result = i_strcmp(pData1->FeeType_.c_str(), pData2->FeeType_.c_str());
      } 
		else if (*pFieldId == ifds::EffectiveDate) 
      {	
			if ( DSTCommonFunctions::CompareDates( pData1->EffectiveDate_.c_str(), pData2->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = 1;
			else if ( DSTCommonFunctions::CompareDates( pData2->EffectiveDate_.c_str(), pData1->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = -1;
			// for equal, result will be 0         
      }    
		else if (*pFieldId == ifds::StopDate) 
      {
         result = i_strcmp(pData1->StopDate_.c_str(), pData2->StopDate_.c_str());
      }    
		else if ( *pFieldId == ifds::FeeRate ) 
      {
			double dblFeeRate1 = DSTCommonFunctions::convertToDouble ( pData1->FeeRate_.c_str() );
			double dblFeeRate2 = DSTCommonFunctions::convertToDouble ( pData2->FeeRate_.c_str() );         			
			if ( dblFeeRate1 > dblFeeRate2 )
				result = 1;
			else if ( dblFeeRate1 < dblFeeRate2 )
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
         else if (*pFieldId == ifds::RecordType) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->RecordType_.c_str();
         } 
         else if (*pFieldId == ifds::FeeCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FeeCode_.c_str();
         } 
         else if (*pFieldId == ifds::FundCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundCode_.c_str();
         } 
         else if (*pFieldId == ifds::ClassCode)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->ClassCode_.c_str();
         } 
         else if (*pFieldId == ifds::FundName)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundName_.c_str();
         }          
			else if (*pFieldId == ifds::EffectiveDate)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->EffectiveDate_.c_str();
         }          
			else if (*pFieldId == ifds::StopDate)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->StopDate_.c_str();
         }          
			else if (*pFieldId == ifds::FeeRate )
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FeeRate_.c_str();
         }   
		 else if (*pFieldId == ifds::FeeType )
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FeeType_.c_str();
         }        
         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
DailyTransactionFeesDlg::DailyTransactionFeesDlg( CWnd* pParent, 
   GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(DailyTransactionFeesDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_pWndItemInFocus(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(DailyTransactionFeesDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void DailyTransactionFeesDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(DailyTransactionFeesDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY DailyTransactionFeesDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter( I_( "RecordType" ),    _dstrDailyTransFeeRecordType );
	getParameter( I_( "FeeCode" ),       _dstrFeeCode );
	getParameter( I_( "FundCode" ),      _dstrFundCode );
	getParameter( I_( "ClassCode" ),     _dstrClassCode );
	getParameter( I_( "EffectiveDate" ), _dstrEffectiveDate );	
   
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(DailyTransactionFeesDlg, BaseMainDlg)
//{{AFX_MSG_MAP(DailyTransactionFeesDlg)
ON_MESSAGE(UM_OPENFUNDLISTDLG, OpenFundListDlg)
ON_BN_CLICKED(IDC_BTN_ADMIN_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL DailyTransactionFeesDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*****************************************************************************
void DailyTransactionFeesDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);

	SetUserAccesFunctionCode(UAF::DAILY_TRANSACTIONS_FEES);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_ANTI_DILUTION_LEVY_LIST);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_ANTI_DILUTION_LEVY_LIST);
   
	IFDSListCtrl* ifdsListControlDailyFees = 
      new IFDSAdaptedListCtrl< LVDailyTransactionFeesAdapter >( this, 
		                                                      CLASSNAME, 
                                                            IDC_LV_ANTI_DILUTION_LEVY_LIST, 
																				0, 
																				0, 
																				true, 
																				true );

   AddIFDSListControl( ifdsListControlDailyFees, 
							  LV_DAILY_TRANSACTION_FEES_LIST, 
							  IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
                       ifds::ADLHeadingSet );   

	// Default the sorting column to Effective Date
	if ( NULL != ifdsListControlDailyFees )		
		ifdsListControlDailyFees->SortOnColumn( 7 );
	
	AddControl( CTRL_COMBO, 
		         IDC_CMB_FEE_CODE, 
					IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
               ifds::FeeCode, 
					CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_ANTI_DILUTION_LEVY_LIST);

	AddControl( CTRL_COMBO, 
		         IDC_CMB_RECORD_TYPE, 
					IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
               ifds::RecordType, 
					CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_ANTI_DILUTION_LEVY_LIST);
   
   AddControl( CTRL_EDIT, 
		         IDC_EDT_FUND_CODE, 
					IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
               ifds::FundCode, 
					CTRLFLAG_DEFAULT, 
					(UINT)IDC_LV_ANTI_DILUTION_LEVY_LIST);

	AddControl( CTRL_EDIT, 
		         IDC_EDT_CLASS_CODE, 
					IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
               ifds::ClassCode, 
					CTRLFLAG_DEFAULT, 
					(UINT)IDC_LV_ANTI_DILUTION_LEVY_LIST);

   AddControl( CTRL_STATIC, 
		         IDC_STC_FUND_NAME, 
					IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
               ifds::FundName, 
					CTRLFLAG_DEFAULT, 
					(UINT)IDC_LV_ANTI_DILUTION_LEVY_LIST ); 

	AddControl( CTRL_DATE, 
		         IDC_DTP_EFFECTIVE_DATE, 
					IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
					ifds::EffectiveDate, 
					0, 
					IDC_LV_ANTI_DILUTION_LEVY_LIST );    

	AddControl( CTRL_DATE, 
		         IDC_DTP_STOP_DATE, 
					IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
					ifds::StopDate, 
					0, 
					IDC_LV_ANTI_DILUTION_LEVY_LIST );    

	AddControl( CTRL_COMBO, 
		         IDC_CMB_FEE_TYPE, 
					IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
               ifds::FeeType, 
					CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_ANTI_DILUTION_LEVY_LIST);

	AddControl( CTRL_EDIT, 
		         IDC_EDT_FEE_RATE, 
					IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
               ifds::FeeRate, 
					CTRLFLAG_DEFAULT, 
					(UINT)IDC_LV_ANTI_DILUTION_LEVY_LIST);
	// Don't allow negatives for this control
	DSTEdit *dstEditFeeRate = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_FEE_RATE ) );
	if ( NULL != dstEditFeeRate )
	{
		DString dstrPercentageMask = DSTCommonFunctions::getMask( ifds::FeeRate );
      int iDecimalPointPos = dstrPercentageMask.find( I_( "." ) );		
		dstEditFeeRate->AllowNonnegativeDecimalNumbers( iDecimalPointPos, 
					                                       dstrPercentageMask.length() - iDecimalPointPos - 2 );		
	}

   doRefresh(this, NULL);
}


//******************************************************************************
bool DailyTransactionFeesDlg::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   //when called by the process from doRefresh, 	
   if (DString(szOriginalCommand) == I_("ReloadParams"))
   {
      getParameter( I_( "RecordType" ),    _dstrDailyTransFeeRecordType );
		getParameter( I_( "FeeCode" ),       _dstrFeeCode );
		getParameter( I_( "FundCode" ),      _dstrFundCode );
		getParameter( I_( "ClassCode" ),     _dstrClassCode );
		getParameter( I_( "EffectiveDate" ), _dstrEffectiveDate );	
   }
    
   //this will load the connected controls
   LoadListControl( IDC_LV_ANTI_DILUTION_LEVY_LIST ); 

   GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist( this, IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST ) );
   
   DSTListCtrl *pPIDSTListCtrl = GetList( IDC_LV_ANTI_DILUTION_LEVY_LIST );

   if( pPIDSTListCtrl )
   {
     if( pPIDSTListCtrl->GetItemCount() <= 0 )
     {         
         //add a new row if list is empty, to simulate the normal behaviour
         AddToListControl(IDC_LV_ANTI_DILUTION_LEVY_LIST);
      }
   }
	
   SetDlgCaption();
   return true;
}

//*************************************************************************
void DailyTransactionFeesDlg::SetDlgCaption()
{
   DString dstrCaption;
   CString cstrTranFee;
   cstrTranFee.LoadString(TXT_FEATURES_SEARCH_DTF);

   dstrCaption = DString(cstrTranFee);

	// If RecordType, FeeCode, and Effective Date are not blank, 
	// then search is done by Effective Date
	if( !_dstrDailyTransFeeRecordType.empty() &&
	    !_dstrFeeCode.empty() &&
	    !_dstrEffectiveDate.empty() )
	{
		CString cstrEffDate;
		cstrEffDate.LoadString(TXT_BY_EFFECTIVE_DATE);
		dstrCaption = dstrCaption + DString(cstrEffDate) + _dstrEffectiveDate;
	}
	else if( _dstrFundCode.empty() && _dstrClassCode.empty() )
	{
		CString cstrFundClass;
		cstrFundClass.LoadString(TXT_FOR_ALL_FUND_CLASS);
		dstrCaption = dstrCaption + DString(cstrFundClass);
	}
	else{
		CString cstrFund ,cstrClass;
	    cstrFund.LoadString(TXT_FOR_FUND);
		cstrClass.LoadString(TXT_AND_CLASS);
		dstrCaption = dstrCaption + DString(cstrFund) + _dstrFundCode + DString(cstrClass) + _dstrClassCode;
	}
   
   SetWindowText( dstrCaption.c_str() );
}

//*************************************************************************
void DailyTransactionFeesDlg::ControlUpdated( UINT controlID, 
															 const DString &strValue )
{   
   switch( controlID )
   {		
		case IDC_EDT_FUND_CODE:
			{							
				LoadControl( IDC_STC_FUND_NAME );
			}
			break;
		case IDC_CMB_FEE_TYPE:
			{							
				DString dstrFeeType;
				getParent()->getField( this, IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, ifds::FeeType, dstrFeeType, false);
				
				int iDecimalPoints = dstrFeeType == PERCENT ? 6 : 2;
				dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_FEE_RATE))->setMaxNumDigitsAfterDecimalPoint(iDecimalPoints);
				
				LoadControl( IDC_EDT_FEE_RATE );
  			}
			break;
		case IDC_EDT_CLASS_CODE:
			{
				LoadControl( IDC_STC_FUND_NAME );
			}
			break;
		case IDC_DTP_EFFECTIVE_DATE:
			{
				//DString dstrEffectiveDate, dstrCurrBusDate;
				//getParent()->getField( this, IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, ifds::EffectiveDate, dstrEffectiveDate );
				//dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::CurrBusDate, dstrCurrBusDate, getDataGroupId(), false ) ;
				//
				//if ( DSTCommonFunctions::CompareDates( dstrCurrBusDate.stripAll(),   dstrEffectiveDate.stripAll() ) == DSTCommonFunctions::FIRST_EARLIER ||
			 //       DSTCommonFunctions::CompareDates( dstrEffectiveDate.stripAll(), dstrCurrBusDate.stripAll() ) == DSTCommonFunctions::EQUAL ) 
				//{
				//	GetDlgItem( IDC_BTN_DELETE )->EnableWindow( true );
				//}
				//else
				//	GetDlgItem( IDC_BTN_DELETE )->EnableWindow( false );
			}
			break;
      case IDC_CMB_FEE_CODE:
         {
            DString dstrFeeCode;
				getParent()->getField( this, IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, ifds::FeeCode, dstrFeeCode, false);
            DSTEdit *dstEditFeeRate = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_FEE_RATE ) );
            //allow -ve value only for CLASS_HURDLE_RATE 
            if( CLASS_HURDLE_RATE !=_dstrFeeCode && dstEditFeeRate )
            {
 		         DString dstrPercentageMask = DSTCommonFunctions::getMask( ifds::FeeRate );
               int iDecimalPointPos = dstrPercentageMask.find( I_( "." ) );		
		         dstEditFeeRate->AllowNonnegativeDecimalNumbers( iDecimalPointPos, 
					                                                dstrPercentageMask.length() - iDecimalPointPos - 2 );		
            }
            else
            {
              dstEditFeeRate->setInputAllowedDecimal();
            }
           LoadControl( IDC_EDT_FEE_RATE );
          }
          break;
		default:
			break;
	}
}

//******************************************************************************

void DailyTransactionFeesDlg::DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey,
                                 bool bIsNewItem ,
                                 bool bIsDummyItem
                                 )
{
	if( listControlID ==  IDC_LV_ANTI_DILUTION_LEVY_LIST )
	{
		DString dstrEffectiveDate, dstrCurrBusDate;
		
		getParent()->getField( this, IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, ifds::EffectiveDate, dstrEffectiveDate );
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::CurrBusDate, dstrCurrBusDate, getDataGroupId(), false ) ;
				
		if ( DSTCommonFunctions::CompareDates( dstrCurrBusDate.stripAll(),   dstrEffectiveDate.stripAll() ) == DSTCommonFunctions::FIRST_EARLIER ||
		     DSTCommonFunctions::CompareDates( dstrEffectiveDate.stripAll(), dstrCurrBusDate.stripAll() ) == DSTCommonFunctions::EQUAL ) 
		{
			GetDlgItem( IDC_BTN_DELETE )->EnableWindow( true );
		}
		else
		{
			GetDlgItem( IDC_BTN_DELETE )->EnableWindow( false );	
		}
	}
}
//******************************************************************************
void DailyTransactionFeesDlg::OnBtnAdd()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnAdd"));

   CWaitCursor wait;

   AddToListControl( IDC_LV_ANTI_DILUTION_LEVY_LIST );
}

//******************************************************************************
void DailyTransactionFeesDlg::OnBtnDelete()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnDelete"));

   CWaitCursor wait;
 
	DeleteFromListControl( IDC_LV_ANTI_DILUTION_LEVY_LIST );
}

//******************************************************************************
void DailyTransactionFeesDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel = GetList( IDC_LV_ANTI_DILUTION_LEVY_LIST )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );
   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl(IDC_LV_ANTI_DILUTION_LEVY_LIST);
      if (*crtKey != NULL_STRING)
      {
         GetList( IDC_LV_ANTI_DILUTION_LEVY_LIST )->SetSelection( crtKey );
      }
   }

   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST));
   
	GetList( IDC_LV_ANTI_DILUTION_LEVY_LIST )->SetSelection( cursel, true, true );
}

//****************************************************************
void DailyTransactionFeesDlg::OnBtnReset()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnReset"));

   CWaitCursor wait;

   ResetListItem(IDC_LV_ANTI_DILUTION_LEVY_LIST);
}

//*************************************************************************
void DailyTransactionFeesDlg::OnBtnAdmDates()
{
   ShowAdminDates( IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );
}

//******************************************************************
BOOL DailyTransactionFeesDlg::PreTranslateMessage(MSG* pMsg) 
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
      
		if( m_pWndItemInFocus == GetDlgItem( IDC_EDT_FUND_CODE ) ||
			 m_pWndItemInFocus == GetDlgItem( IDC_EDT_CLASS_CODE ) )
      {
         PostMessage( UM_OPENFUNDLISTDLG );
      }      		
   }
   return BaseMainDlg::PreTranslateMessage(pMsg);
}

//******************************************************************
LRESULT DailyTransactionFeesDlg::OpenFundListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundListDlg" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      if( m_pWndItemInFocus == GetDlgItem( IDC_EDT_FUND_CODE ) ) 
      {
         DString dstrFundCode;

         GetControlText( IDC_EDT_FUND_CODE, dstrFundCode);
         setParameter (I_("FundCode"), dstrFundCode);
      } 
      else if( m_pWndItemInFocus == GetDlgItem( IDC_EDT_CLASS_CODE ) )
      {
         DString classCode;

         GetControlText (IDC_EDT_CLASS_CODE, classCode);
         setParameter (I_("ClassCode"), classCode);
      }
      
		//invoke the fund class dialog and process
      SetMessageStatusBar (TXT_LOAD_FUND_INFO);
      eRtn = invokeCommand( getParent(), 
								    CMD_BPROC_FUNDCLASS, 
								    PROC_SUPPORT, 
									 true, 
									 NULL );
      switch (eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, 
                       dstrClassCode;

               getParameter (I_("FundCode"), dstrFundCode);
               getParent()->setField ( this, 
                                       IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
                                       ifds::FundCode, 
                                       dstrFundCode);

               getParameter (I_("ClassCode"), dstrClassCode);
               getParent()->setField ( this, 
                                       IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, 
                                       ifds::ClassCode, 
                                       dstrClassCode);

               LoadControl( IDC_EDT_FUND_CODE );
               LoadControl( IDC_EDT_CLASS_CODE );
					LoadControl( IDC_STC_FUND_NAME );
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            SetMessageStatusBar (NULL_STRING);
            break;
      }
      SetMessageStatusBar (NULL_STRING);
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return eRtn;
}

//*****************************************************************************
void DailyTransactionFeesDlg::OnBtnHistorical() 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical") );   
	CWaitCursor wait;   
	IFastHistoricalInfo f;
	f( this, IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/DailyTransactionFeesDlg.cpp-arc  $
// 
//    Rev 1.12   Nov 19 2011 01:27:00   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.11   Jul 16 2010 15:57:22   jankovii
// PET0170770_FN01_Anti Dilution Levy
// 
//    Rev 1.10   Jul 14 2010 13:36:02   jankovii
// PET0170770_FN01_Anti Dilution Levy
// 
//    Rev 1.9   Sep 15 2005 15:11:14   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.8   Aug 22 2005 10:52:04   ZHANGCEL
// PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
// 
//    Rev 1.7   Apr 05 2004 12:10:26   VADEANUM
// PTS 10028631 - Changed key based on Sue/Lina/Winnie's request.
// 
//    Rev 1.6   Feb 23 2004 09:28:36   VADEANUM
// PET859 FN23 - ADL - Enable/Disable Delete button based on Effective Date
// 
//    Rev 1.5   Feb 12 2004 16:21:36   VADEANUM
// PET859 FN23 - Fund Name refresh.
// 
//    Rev 1.4   Feb 12 2004 13:24:06   VADEANUM
// PET859 FN23 - ADL - replaced FeePercent with FeeRate for correct display mask.
// 
//    Rev 1.3   Feb 12 2004 10:09:22   VADEANUM
// PET859 FN23 - Refresh Fund Name.
// 
//    Rev 1.2   Feb 11 2004 16:08:08   VADEANUM
// PET859 FN23 - IFDSListControl implementation.
// 
//    Rev 1.1   Feb 11 2004 11:32:34   VADEANUM
// PET859 FN23 - ADL - first working version.
// 
//    Rev 1.0   Feb 03 2004 16:56:38   VADEANUM
// Initial revision.
// 
*/

