//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : MinMaxInfoDlg.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/31/2000
//
// ^CLASS    : MinMaxInfoDlg
// ^SUBCLASS : BaseMainDlg         
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "MinMaxInfoDlg.h"
#include <ifastbp\MinMaxInfoProcessIncludes.h>
#include <uibase\DSTGridWnd.h>
#include <uibase\dstlistctrl.h>
#include <uibase\DSTOleDateTime.h>
#include <ifastdataimpl\dse_ListViewHeading.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#ifndef DSTCFUNCS_H
   #include <uibase\DstcFuncs.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_MINMAXINFO;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< MinMaxInfoDlg > dlgCreator( CMD_GUI_MINMAXINFO );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MinMaxInfoDlg dialog

namespace
{
   // trace literals
   const I_CHAR *CLASSNAME = I_( "MinMaxInfoDlg" );
   const I_CHAR *LV_MINMAX = I_( "MinMaxInfoList" );

   // Define MinMaxListTop's code
   const I_CHAR *AMOUNT       = I_( "Amount" );
   const I_CHAR *MINIMUM      = I_( "Minimum" );
   const I_CHAR *OPTION       = I_( "Optional" );
   const I_CHAR *TOTAL        = I_( "Total" );
   const I_CHAR *TAXWITHHELD  = I_( "TaxWithheld" );

   // Define MinMaxListLeft's code
   const I_CHAR *WITHDRAWN    = I_( "Withdrawn" );
   const I_CHAR *OUTSTANDING  = I_( "Outstanding" );
   const I_CHAR* const GR_MINMAXLIST =  I_( "MinMaxGrid" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

/***********************************************************************/
MinMaxInfoDlg::MinMaxInfoDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( MinMaxInfoDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(MinMaxInfoDlg)
   //}}AFX_DATA_INIT
}

/***********************************************************************/
void MinMaxInfoDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(MinMaxInfoDlg)
   DDX_Control(pDX, IDC_DTP_ASOFDATE, m_DtpAsofDate);
   //}}AFX_DATA_MAP
}

/***********************************************************************/
BEGIN_MESSAGE_MAP(MinMaxInfoDlg, BaseMainDlg)
//{{AFX_MSG_MAP(MinMaxInfoDlg)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MinMaxInfoDlg message handlers

/***********************************************************************/
SEVERITY MinMaxInfoDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));
   SEVERITY sevRtn = SEVERE_ERROR;
   getParameter( MINMAX::ACCOUNT_NUMBER, m_dstrAccountNumber );
   getParameter( MINMAX::TAX_TYPE, m_dstrTaxType );
   sevRtn = NO_CONDITION;
   return(sevRtn);
}

/***********************************************************************/
BOOL MinMaxInfoDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   // TODO: Add extra initialization here
   SetAccount( m_dstrAccountNumber);
   SetAccountCaption();

   AddControl( CTRL_STATIC, IDC_TXT_OTHAMTWITH,   IFASTBP_PROC::MINMAXINFO_CBO, ifds::OthAmtWith );
   AddControl( CTRL_STATIC, IDC_TXT_MAXAMT,       IFASTBP_PROC::MINMAXINFO_CBO, ifds::MaxAmt );
   AddControl( CTRL_STATIC, IDC_TXT_MINAMT,       IFASTBP_PROC::MINMAXINFO_CBO, ifds::MinAmt );
   AddControl( CTRL_STATIC, IDC_TXT_MAXAMTREMAIN, IFASTBP_PROC::MINMAXINFO_CBO, ifds::MaxAmtRemain );
   AddControl( CTRL_STATIC, IDC_TXT_MINAMTSHORT,  IFASTBP_PROC::MINMAXINFO_CBO, ifds::MinAmtShort );
   AddControl( CTRL_STATIC, IDC_TXT_UNL_AMT,      IFASTBP_PROC::MINMAXINFO_CBO, ifds::UnLockGrossAmt );
   AddControl( CTRL_STATIC, IDC_TXT_UNL_DATE,     IFASTBP_PROC::MINMAXINFO_CBO, ifds::UnLockDeff );

   AddGrid( CLASSNAME, IDC_GD_MINMAXLIST, GR_MINMAXLIST, IFASTBP_PROC::MINMAXINFO_CBO, 0, ifds::MinMaxListTop, ifds::MinMaxListLeft );
   /*DSTGridWnd * grdWnd = GetGrid( IDC_GD_MINMAXLIST );
   grdWnd->SetColWidth(0,0,147);
   grdWnd->SetColWidth(1,1,160);
   grdWnd->SetColWidth(2,2,160);
   grdWnd->SetColWidth(3,3,155);
   grdWnd->SetColWidth(4,4,155);*/

   UpdateData( FALSE );
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//*****************************************************************************
void MinMaxInfoDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   // Populate dialog

   DString dstrAsofDate;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   dstcWorkSession->getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrAsofDate, getDataGroupId( ), false );
   COleDateTime date;
   setOleDateFromHost(date, dstrAsofDate);
   m_DtpAsofDate.SetTime ( date );

   CWnd *StControl;
   StControl = GetDlgItem( IDC_LBL_RRIF );
   CString cstrLabel;
   cstrLabel.LoadString ( TXT_MIN_MAX_AS_OF );
   /*DString dstr;
   dstr = m_dstrTaxType + I_(" Min/Max as of: ");*/
   StControl->SetWindowText(m_dstrTaxType.c_str() + cstrLabel);

   StControl = GetDlgItem( IDC_LBL_ACCOUNTINTO);
   //dstr = m_dstrTaxType + I_(" Min/Max Information: ");
   cstrLabel.LoadString ( TXT_MIN_MAX_INFO );
   StControl->SetWindowText(m_dstrTaxType.c_str() + cstrLabel);

   ConnectControlsToData();
   LoadControls( -1L ); 
   DSTGridWnd * grdWnd = GetGrid( IDC_GD_MINMAXLIST );
   m_bClear = false;
   grdWnd->LoadGrid();   

//   LoadGrid( IDC_GD_MINMAXLIST);
}

/**********************************************************************************/
void MinMaxInfoDlg::GetCellProperties( UINT ctrlId, 
                                       const DString &rowKey,
                                       const DString &colKey, 
                                       BFContainerId& idContainer, 
                                       BFFieldId &idField,
                                       DString& listItemKey, 
                                       int& nCellState, 
                                       UINT& cellCtrlType,
                                       int& nCtrlInitMode, 
                                       BFFieldId &idSubstitution, 
                                       DString& comboList, 
                                       DString &mask, 
                                       int& nComboSortingMode ,
                                       DString& dstrAllowedChar)	 
{
   idContainer = IFASTBP_PROC::MINMAXINFO_CBO;
   dstrAllowedChar = NULL_STRING;
   nCellState = DSTGridWnd::READ_ONLY;
   if( !m_bClear )
   {
      // Data exists for designated date, so populate grid
      if( ctrlId == IDC_GD_MINMAXLIST )
      {
         if( rowKey == WITHDRAWN )    // Row "Before Redemtion"
         {
            if( colKey == AMOUNT )   
				{
					nCellState = DSTGridWnd::SKIPPED;
				}
            else if( colKey == MINIMUM ) 
				{ 
					idField = ifds::MinAmtWith;
				}
            else if( colKey == OPTION ){
					idField = ifds::OptAmtWith;
				}
            else if( colKey == TOTAL ) 
				{
					idField = ifds::TotAmtWith;
				}	
				else if( colKey == TAXWITHHELD )
				{
					idField = ifds::TaxAmtWith;
				}
         }
         if( rowKey == OUTSTANDING )    // Row "Before Redemtion"
         {
            if( colKey == AMOUNT ) 
				{
					nCellState = DSTGridWnd::SKIPPED;
				}
            else if( colKey == MINIMUM ) 
				{
					idField = ifds::MinAmtOut;
				}
            else if( colKey == OPTION )
				{
					idField = ifds::OptAmtOut;
				}
            if( colKey == TOTAL )
				{
					idField = ifds::TotAmtOut;
				}	
            if( colKey == TAXWITHHELD ) 
				{
					idField = ifds::TaxAmtOut;
				}
         }
      }
   }
   else
   {  // Data does not exist for designated date, so clear grid
      if( ctrlId == IDC_GD_MINMAXLIST )
      {
         if( rowKey == WITHDRAWN )    // Row "Before Redemtion"
         {
            if( colKey == AMOUNT )       nCellState = DSTGridWnd::SKIPPED;
            if( colKey == MINIMUM )      nCellState = DSTGridWnd::SKIPPED;
            if( colKey == OPTION )       nCellState = DSTGridWnd::SKIPPED;
            if( colKey == TOTAL )        nCellState = DSTGridWnd::SKIPPED;
            if( colKey == TAXWITHHELD )  nCellState = DSTGridWnd::SKIPPED;
         }
         if( rowKey == OUTSTANDING )    // Row "Before Redemtion"
         {
            if( colKey == AMOUNT )       nCellState = DSTGridWnd::SKIPPED;
            if( colKey == MINIMUM )      nCellState = DSTGridWnd::SKIPPED;
            if( colKey == OPTION )       nCellState = DSTGridWnd::SKIPPED;
            if( colKey == TOTAL )        nCellState = DSTGridWnd::SKIPPED;
            if( colKey == TAXWITHHELD )  nCellState = DSTGridWnd::SKIPPED;
         }
      }
   }
}

//*****************************************************************************
void MinMaxInfoDlg::OnBtnSearch() 
{
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnSearch"));

   DSTOleDateTime odtDate;
   m_DtpAsofDate.GetTime(odtDate);

   DSTOleDateTime odtCurrentDate;
   odtCurrentDate = COleDateTime::GetCurrentTime();
   if( odtDate > odtCurrentDate )
   {
      ClearControls( BF::AllContainerIds );
      m_bClear = true;    // set flag for clearing grid
      LoadGrid( IDC_GD_MINMAXLIST);
      AfxMessageBox( TXT_NO_FUTURE_DATE);
      m_DtpAsofDate.SetFocus();
      return;
   }

   if( search() )
   {
      ConnectControlsToData();
      LoadControls( -1L );
      LoadGrid( IDC_GD_MINMAXLIST);
	  DSTGridWnd * grdWnd = GetGrid( IDC_GD_MINMAXLIST ); //Added for INC0034349
	  grdWnd->LoadGrid(); //Added for INC0034349
   }
//   else
//      LoadGrid( IDC_GD_MINMAXLIST);

   SetMessageStatusBar( NULL_STRING );
}

/***********************************************************************/
bool MinMaxInfoDlg::search()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("search") );
   CWaitCursor wait;
   SetMessageStatusBar( TXT_SEARCH_FOR_DATE );
   UpdateData( TRUE );

   CString strDate;
   m_DtpAsofDate.GetDateInHostFormat( strDate );
   if( strDate == "Invalid DateTime." )
   {
      ClearControls( BF::AllContainerIds );
      m_bClear = true;    // set flag for clearing grid
      AfxMessageBox( TXT_INVALID_DATE );
      return(false);
   }

   setParameter( MINMAX::AS_OF_DATE, DString( strDate ) );
   setParameter( MINMAX::ACCOUNT_NUMBER, m_dstrAccountNumber );

   SEVERITY sevRtn = SEVERE_ERROR;
   sevRtn = getParent()->performSearch( this, BF::AllContainerIds, SEARCH_START );
   if( sevRtn == SEVERE_ERROR )
   {
      ClearControls( BF::AllContainerIds );
      AfxMessageBox( TXT_INVALID_DATE );
      m_bClear = true;    // set flag for clearing grid
      return(false);
   }
   else
   {
      m_bClear = false;   // reset flag for populateing grid
      return(true);
   }
}

/***********************************************************************/
bool MinMaxInfoDlg::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{  
   TRACE_METHOD( CLASSNAME, I_("doRefresh"));

   getParameter( MINMAX::ACCOUNT_NUMBER, m_dstrAccountNumber );

   SetAccount( m_dstrAccountNumber);
   SetAccountCaption();

   OnPostInitDialog();

   return(true);
}

//*****************************************************************************

/* $Log:   Y:/VCS/BF iFAST/ifastgui/MinMaxInfoDlg.cpp-arc  $
 * 
 *    Rev 1.19   Jul 24 2009 01:39:48   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
 * 
 *    Rev 1.18   11 Apr 2008 12:00:14   kovacsro
 * PET2255-FN47_Ontario Locked-In Products - added 2 new fields on MinMax screen
 * 
 *    Rev 1.17   Sep 15 2005 15:14:02   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.16   Jul 15 2003 14:38:16   YINGBAOL
 * tuning
 * 
 *    Rev 1.15   Jun 24 2003 14:09:06   HSUCHIN
 * PTS 10018765 - bug fix with as of date where the current bus date of the db system was not set to the control.   Code clean up and fixed grid settings not being saved.
 * 
 *    Rev 1.14   Mar 21 2003 18:39:10   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Feb 26 2003 13:24:48   linmay
 * clean up message
 * 
 *    Rev 1.12   Oct 09 2002 23:55:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 20:09:26   SMITHDAV
 * CellProperties fixes
 * 
 *    Rev 1.10   Aug 29 2002 18:27:54   SMITHDAV
 * Additional fixes.
 * 
 *    Rev 1.9   Aug 29 2002 18:14:32   SMITHDAV
 * Additional FieldId fixes.
 * 
 *    Rev 1.8   22 May 2002 19:16:18   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   27 Mar 2002 20:01:18   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.6   14 Jun 2001 11:58:26   SMITHDAV
 * Removed references to UserAccessProcess.
 * 
 *    Rev 1.5   Oct 18 2000 17:46:18   ZHANGCEL
 * Bug fixed and code clean up
 * 
 *    Rev 1.4   May 29 2000 09:21:46   BUZILA
 * maskeEdit controls
 * 
 *    Rev 1.3   Apr 05 2000 13:04:52   DT24433
 * removed unused headers
 * 
 *    Rev 1.2   Apr 05 2000 11:43:10   ZHANGCEL
 * Debug
 * 
 *    Rev 1.1   Mar 30 2000 15:25:32   ZHANGCEL
 * Change LoadGrid()
 * 
 *    Rev 1.0   Mar 22 2000 12:52:16   BUZILA
 * Initial revision.
 * 
// 
 *
 */
