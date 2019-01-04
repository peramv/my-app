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
//    Copyright 2003 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : MktIndexValuesMaintDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : MktIndexValuesMaintDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "MktIndexValuesMaintDlg.h"
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\MktIndexValuesMaintProcessIncludes.h>
#include <uibase\dstedit.h>
#include <bfproc\abstractprocess.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_MKT_INDEX_VALUES;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< MktIndexValuesMaintDlg > dlgCreator( CMD_GUI_MKT_INDEX_VALUES );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("MktIndexValuesMaintDlg");
   const I_CHAR * const FUNDNUMBER = I_( "FUNDNUMBER" );
   const I_CHAR * const PERCENTAGECHANGED = I_( "PERCENTAGE_CHANGED" );
   const I_CHAR * const INDEXCODE = I_( "IndexCode" );
   const I_CHAR * const INDEXNAME = I_( "IndexName" );
   const I_CHAR * const REFRESH = I_( "REFRESH" );
   const I_CHAR * const FUNDDESCRIPTION= I_( "FUNDDESCRIPTION" );
}

namespace PARAMETER
{
}

namespace CND
{
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const MKT_INDEX_VALUES;
}
namespace ifds 
{
   extern CLASS_IMPORT const BFTextFieldId SearchIndexType;
   extern CLASS_IMPORT const BFDecimalFieldId HurdleRate; 
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}
namespace SEARCH_CONTROLS
{
   const UINT INDEX_SEARCH = 1;
};
//*****************************************************************************
// Public methods
//*****************************************************************************

MktIndexValuesMaintDlg::MktIndexValuesMaintDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( MktIndexValuesMaintDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(MktIndexValuesMaintDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************

void MktIndexValuesMaintDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(MktIndexValuesMaintDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(MktIndexValuesMaintDlg, BaseMainDlg)
//{{AFX_MSG_MAP(MktIndexValuesMaintDlg)
ON_BN_CLICKED( IDC_BTN_ADD_INDEX, OnBtnAddIndex )
ON_BN_CLICKED( IDC_BTN_DEL_INDEX, OnBtnDelIndex )
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL MktIndexValuesMaintDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   DString dstrMarket = DSTCommonFunctions::getMarket();
   m_bFundNumberSupported = ( dstrMarket == MARKET_IDS::CANADA || dstrMarket == MARKET_IDS::LUXEMBOURG );

   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//******************************************************************************

void MktIndexValuesMaintDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode( UAF::MKT_INDEX_VALUES );
   addBtnAddForPermissionCheck( IDC_BTN_ADD_INDEX, IDC_LST_INDICES );
   addBtnDeleteForPermissionCheck( IDC_BTN_DEL_INDEX, IDC_LST_INDICES );

   AddListControl( CLASSNAME, IDC_LST_INDICES, I_("INDEX_INDICES"), ifds::IndexValuesHeading, IFASTBP_PROC::INDICES_LIST );
   AddListControl( CLASSNAME, IDC_LST_FUNDS, I_("INDEX_FUNDS"), ifds::IndexFundsHeading, IFASTBP_PROC::FUNDS_LIST, IDC_CMB_INDEX, true, LISTFLAG_NOT_AUTO_ADD );
   AddControl( CTRL_DATE, IDC_DTP_EFFECTIVE_DATE, IFASTBP_PROC::INDICES_LIST, ifds::EffectiveDate, 0 , IDC_LST_INDICES );
   AddControl( CTRL_COMBO, IDC_CMB_INDEX, IFASTBP_PROC::INDICES_LIST, ifds::IndexCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LST_INDICES );
   AddControl( CTRL_EDIT, IDC_EDT_CLOSE, IFASTBP_PROC::INDICES_LIST, ifds::ClosingValue, 0 , IDC_LST_INDICES );
   dynamic_cast<DSTEdit *>(GetControl( IDC_EDT_CLOSE ))->SetAllowedChars( I_("0123456789.") );
   AddControl( CTRL_STATIC, IDC_TXT_CODE, IFASTBP_PROC::INDICES_LIST, ifds::IndexCode, 0, IDC_LST_INDICES );
   AddControl( CTRL_STATIC, IDC_TXT_STATUS, IFASTBP_PROC::INDICES_LIST, ifds::GoodBad, 0, IDC_LST_INDICES );
   AddControl( CTRL_STATIC, IDC_TXT_PERCENT, IFASTBP_PROC::INDICES_LIST, ifds::PercentageChanged, 0, IDC_LST_INDICES );

   AddControl( CTRL_EDIT, IDC_EDT_HURDLE, IFASTBP_PROC::INDICES_LIST, ifds::HurdleRate, 0 , IDC_LST_INDICES ); 
   dynamic_cast<DSTEdit *>(GetControl( IDC_EDT_HURDLE ))->SetAllowedChars( I_("-0123456789.") );
   AddControl( CTRL_DATE, IDC_DTP_FROM_DATE_MKT, MKT_INDEX_SEARCH, ifds::FromDate, 0 ,SEARCH_CONTROLS::INDEX_SEARCH); 
   AddControl( CTRL_COMBO,IDC_CMB_SEARCHTYPE, MKT_INDEX_SEARCH, ifds::SearchIndexType,CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST, SEARCH_CONTROLS::INDEX_SEARCH); 
  
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );

   DString dstrCurrBusDate(NULL_STRING);
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   dstcWorkSession->getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrCurrBusDate, getDataGroupId( ), false );
   getParent()->setField (this, MKT_INDEX_SEARCH, ifds::FromDate, dstrCurrBusDate, false);

   enableControls(I_("01")); //Set "Index Value" as a default (i.e. existing screen)
   doRefresh (this, NULL_STRING);
}

//*****************************************************************************

void MktIndexValuesMaintDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   ResetListItem( IDC_LST_INDICES );
}

//*********************************************************************

void MktIndexValuesMaintDlg::OnBtnAddIndex()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAddIndex") );
   AddToListControl( IDC_LST_INDICES );
}

//**********************************************************************

void MktIndexValuesMaintDlg::OnBtnDelIndex()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnDelIndex") );
   DeleteFromListControl( IDC_LST_INDICES );
}

//************************************************************************

void MktIndexValuesMaintDlg::OnBtnAdmDates() 
{
   ShowAdminDates( IFASTBP_PROC::INDICES_LIST );
}

//************************************************************************

void MktIndexValuesMaintDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::INDICES_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::INDICES_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LST_INDICES );
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//*****************************************************************************

bool MktIndexValuesMaintDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   ConnectListToData (IDC_LST_INDICES, true);
   ConnectControlsToData (SEARCH_CONTROLS::INDEX_SEARCH, true);
   
   LoadControls (SEARCH_CONTROLS::INDEX_SEARCH);
   return( true );
}

//********************************************************************************

bool MktIndexValuesMaintDlg::doDisablePermCheckButton(UINT nID)
{
   if( nID == IDC_BTN_DEL_INDEX )
   {
      DString dstrStatusCode;
      getParent()->getField( this, IFASTBP_PROC::INDICES_LIST, ifds::GoodBad, dstrStatusCode, false );
      return( dstrStatusCode == I_("N") );   // N - BAD Record.
   }
   return false;  // return true to disable
}

//*******************************************************************************************

bool MktIndexValuesMaintDlg::filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag)
{
   bool bReturn = true;

	if( ifds::IndexFundsHeading == idSubstitute )
	{
		if( dstrTag == FUNDNUMBER )
		{
         bReturn = m_bFundNumberSupported;
		}
	}	
	return bReturn;
}

//**********************************************************************************

bool MktIndexValuesMaintDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
{
   if( lSubstituteId == ifds::IndexValuesHeading.getId() )
   {
      if( dstrColumnKey == INDEXCODE )
      {
         getParent()->getField( this, BF::NullContainerId, ifds::IndexCode, dstrOut, false );
         return( true );
      }
      else if( dstrColumnKey == INDEXNAME )
      {
         getParent()->getField( this, BF::NullContainerId, ifds::IndexCode, dstrOut, true );
         return( true );
      }
   }
   else if( lSubstituteId == ifds::IndexFundsHeading.getId() )
   {
      if( dstrColumnKey == FUNDNUMBER )
      {
         DString dstrFund, dstrClass;
         getParent()->getField (this, IFASTBP_PROC::FUNDS_LIST, ifds::FundCode, dstrFund );
         getParent()->getField (this, IFASTBP_PROC::FUNDS_LIST, ifds::ClassCode, dstrClass );
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber( dstrFund, dstrClass, dstrOut );
         return( true );
      }
      else if( dstrColumnKey == FUNDDESCRIPTION )
      {
         getParent()->getField (this, IFASTBP_PROC::FUNDS_LIST, INDEX_VALUES::FUNDDESC, dstrOut );
         return( true );
      }
   }
   return( false );
}

//**********************************************************************************

void MktIndexValuesMaintDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   DString dstInputDataType = I_(""),dstIndexCode;
   switch( controlID )
   {
		case IDC_CMB_INDEX:
         getParent()->send( this, REFRESH );
			LoadListControl( IDC_LST_FUNDS );
         LoadControl( IDC_TXT_CODE );

		 getParent()->getField( this, BF::NullContainerId, ifds::IndexCode, dstIndexCode, true );
		 setParameter (MKTINDEXPROC::INDEX_CODE, dstIndexCode);

		 getParent()->getField( this, BF::NullContainerId, InputDataType, dstInputDataType, true );
		 enableControls(dstInputDataType);

		 LoadControl( IDC_EDT_HURDLE );
		 LoadControl( IDC_EDT_CLOSE ); 
	
		break;

      default:
         break;
   }
}

//**********************************************************************************

bool MktIndexValuesMaintDlg::GetDataForControl(
                                       UINT controlID,
                                       DString &strValueOut,
                                       bool bFormatted,
                                       int index
                                       ) const
{
   if( controlID == IDC_TXT_CODE )
   {
      DString dstrIndexCode;
      getParent()->getField( this, BF::NullContainerId, ifds::IndexCode, dstrIndexCode, false);
      strValueOut = dstrIndexCode;
      return true;
   }
   return false;
};
/******************************************************************************/
void MktIndexValuesMaintDlg::OnBtnSearch()
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnSearch"));
	
	GenericInterface* pParent = getParent();

	BaseControl* pBControl = dynamic_cast<BaseControl*>(GetFocus());
    if( pBControl )  pBControl->Store();
	DString dstrUpdate;
    pParent->getField(this, BF::NullContainerId, HAS_OBJECT_UPDATE, dstrUpdate );
	bool bSearch = true;
	CString cstr;
	cstr.LoadString( TXT_WARNING_LOST_CHANGE );
	if( dstrUpdate == I_("Y")  )
	{
		if( IDNO == AfxMessageBox( TXT_WARNING_LOST_CHANGE, MB_YESNO ) )
			bSearch = false;
		else 
			ResetListItem( IDC_LST_INDICES );
	}   
	if( bSearch )
	{	
		DString strSearchIndex, strSearchFromDate, strIndexCode(I_(""));

		getParent ()->send( this, I_( "RefreshIndexData" ) );
		getParent()->getField (this, MKT_INDEX_SEARCH, ifds::SearchIndexType, strSearchIndex, false);
		getParent()->getField (this, MKT_INDEX_SEARCH, ifds::FromDate, strSearchFromDate, false);

		if( strSearchIndex != I_("ALL") )// Not 'ALL' is selected
		{
			strIndexCode = strSearchIndex;	
			strSearchIndex = I_("INDEXSEARCH");	
		}
		setParameter (MKTINDEXPROC::SEARCH_TYPE, strSearchIndex);
		setParameter (MKTINDEXPROC::INDEX_CODE, strIndexCode);
		setParameter (MKTINDEXPROC::DATE, strSearchFromDate);

		if (pParent->performSearch (this, IFASTBP_PROC::INDICES_LIST, SEARCH_START) <= WARNING)
		{
			LoadListControl (IDC_LST_INDICES);
			GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
		}
		else
		{
			// Display error
			ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
		}
	}
}
/********************************************************************************************/
void MktIndexValuesMaintDlg::DoListItemChanged ( UINT listControlID, 
                                           const DString &strKey, 
                                           bool bIsNewItem, 
                                           bool bIsDummyItem)
{
   switch (listControlID)
   {
      case IDC_LST_INDICES:
      {		 
		 int iItemNumber = 0;
		 iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::INDICES_LIST );		
		 if ( iItemNumber > 0 )
		 {
			 DString dstInputDataType,dstrIndexCode;
			 getParent()->getField( this, IFASTBP_PROC::INDICES_LIST, ifds::IndexCode, dstrIndexCode, true );
			 setParameter (MKTINDEXPROC::INDEX_CODE, dstrIndexCode);

			 getParent()->getField( this, BF::NullContainerId, InputDataType, dstInputDataType, true );
			 enableControls(dstInputDataType);
		 }
		 else
		 {
			 enableControls(I_("01")); //Set "Index Value" as a default (i.e. existing screen)
		 }
         break;
      }
      default:
         break;
   }
}
/********************************************************************************************/
void MktIndexValuesMaintDlg::enableControls ( const DString &inputDataType )
{
	if( inputDataType == I_("03") )//Hurdle
	{
		GetDlgItem(IDC_DTP_EFFECTIVE_DATE)->ShowWindow(true);			   
		GetDlgItem(IDC_EDT_CLOSE)->ShowWindow(false);		   
		GetDlgItem(IDC_EDT_HURDLE)->ShowWindow(true);
		GetDlgItem(IDC_EDT_HURDLE)->EnableWindow(true);	
	
		GetDlgItem(IDC_STATIC_EFF_DATE)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_CLOSE)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_HURDLE_RATE)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_PERCENT)->ShowWindow(true);
	}
	else if( inputDataType == I_("02") ) //Index Value with Hurdle calculation
	{
		GetDlgItem(IDC_DTP_EFFECTIVE_DATE)->ShowWindow(true);		
		GetDlgItem(IDC_EDT_CLOSE)->ShowWindow(true);		
		GetDlgItem(IDC_EDT_HURDLE)->ShowWindow(true);
		GetDlgItem(IDC_EDT_HURDLE)->EnableWindow(false);
	
		GetDlgItem(IDC_STATIC_EFF_DATE)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_CLOSE)->ShowWindow(true);		
		GetDlgItem(IDC_STATIC_HURDLE_RATE)->ShowWindow(true);	
		GetDlgItem(IDC_STATIC_PERCENT)->ShowWindow(true);

		CString cstrLabel;
		cstrLabel.LoadString(TXT_MKT_VALUE);
		GetDlgItem(IDC_STATIC_CLOSE)->SetWindowText(cstrLabel);
	}
	else if( inputDataType == I_("01") ) //Index Value
	{	
		GetDlgItem(IDC_DTP_EFFECTIVE_DATE)->ShowWindow(true);		
		GetDlgItem(IDC_EDT_CLOSE)->ShowWindow(true);		
		GetDlgItem(IDC_EDT_HURDLE)->ShowWindow(false);

		GetDlgItem(IDC_STATIC_CLOSE)->ShowWindow(true);	   		
		GetDlgItem(IDC_STATIC_PERCENT)->ShowWindow(false);	
		GetDlgItem(IDC_STATIC_EFF_DATE)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_HURDLE_RATE)->ShowWindow(false);

		CString cstrLabel;
		cstrLabel.LoadString(TXT_MKT_CLOSING_VALUE);
		GetDlgItem(IDC_STATIC_CLOSE)->SetWindowText(cstrLabel);
	}
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MktIndexValuesMaintDlg.cpp-arc  $
// 
//    Rev 1.12   Mar 06 2012 22:39:06   wp040132
// Dosend( ) is called to refresh the indices list when 'Search' button is clicked. Performance Fees - P0188394 and Incident #2845411 
// 
//    Rev 1.11   Mar 06 2012 22:31:20   wp040132
// Dosend( ) is called to refresh the indices list when 'Search' button is clicked. Performance Fess - P0188394
// 
//    Rev 1.10   Jan 26 2012 10:53:32   wp040027
// P0188394_Performance Fees - Benchmark Upload (Modifying Search Functionality)
// 
//    Rev 1.9   Jan 16 2012 13:49:04   wp040027
// P0188394_Performance Fees - Benchmark Upload
// 
//    Rev 1.8   Sep 15 2005 15:14:04   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.7   Mar 21 2003 18:39:20   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Feb 07 2003 14:16:22   HERNANDO
// Added Fund Description.
// 
//    Rev 1.5   Feb 06 2003 15:57:58   HERNANDO
// Revised Percentage Changed.
// 
//    Rev 1.4   Feb 05 2003 13:24:16   HERNANDO
// Revised UAF for MKT_INDEX.
// 
//    Rev 1.3   Feb 03 2003 15:47:06   HERNANDO
// Added GetDataForControl.
// 
//    Rev 1.2   Jan 31 2003 13:24:04   HERNANDO
// Added implementation for doDisablePermCheckButton.
// 
//    Rev 1.1   Jan 29 2003 18:30:42   HERNANDO
// Revised.
// 
//    Rev 1.0   Jan 29 2003 12:59:48   HERNANDO
// Initial Revision
// 
//    Rev 1.0   Jan 23 2003 10:32:38   HERNANDO
// Initial Revision
 * 
 */





