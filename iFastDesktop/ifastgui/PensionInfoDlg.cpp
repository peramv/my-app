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
//    Copyright 2002 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : PensionInfoDlg.cpp
// ^AUTHOR : 
// ^DATE   : May 26, 2002
//
// ----------------------------------------------------------
//
// ^CLASS    : PensionInfoDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef PENSIONINFODLG_H
   #include "PensionInfoDlg.h"
#endif

#ifndef PENSIONINFOPROCESSINCLUDES_H
   #include <ifastbp\PensionInfoProcessIncludes.h>
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_PENSION_INFO;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< PensionInfoDlg > dlgCreator( CMD_GUI_PENSION_INFO );

namespace
{
   const I_CHAR * const CLASSNAME = I_( "PensionInfoDlg" );   
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );
}

namespace CND
{
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Pension_sub;
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP(PensionInfoDlg, BaseMainDlg)
//{{AFX_MSG_MAP(InterestAccrualDlg)
ON_EN_KILLFOCUS ( IDC_EDT_SEX_DISTINCT_AMT, OnkillFocusSexDistinct ) 
ON_BN_CLICKED ( IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// MFC DataExchange Map
//******************************************************************************

void PensionInfoDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(PensionInfoDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************
// Constructor
//******************************************************************************

PensionInfoDlg::PensionInfoDlg ( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( PensionInfoDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(PensionInfoDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
// Destructor
//******************************************************************************

PensionInfoDlg::~PensionInfoDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Initializes the Dialog by setting up the captions with Account information.
// Sets up all the controls and defaults to interest accruals
// @returns - BOOL true.
//******************************************************************************

BOOL PensionInfoDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();
   DString dstrMarket = DSTCommonFunctions::getMarket();
   _bCanLuxMarket = ( dstrMarket == MARKET_IDS::CANADA || dstrMarket == MARKET_IDS::LUXEMBOURG );

   DString dstrShrNum, dstrAccountNum, dstrEntityName;
   getParent()->getField(this, ifds::ShrNum, dstrShrNum);      
   getParent()->getField( this, ifds::AccountNum, dstrAccountNum );  
   SetAccount( dstrAccountNum );   
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), 
                                                                                                    dstrAccountNum,                                                                                                     dstrEntityName );
   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
   addControls( );
   ConnectControlsToData();
   LoadControls();   
   return(TRUE);
}

//******************************************************************************
// All the control hookups are done in this procedure.  This is called by the 
// OnInitDialog function.
// @returns void.
//******************************************************************************

void PensionInfoDlg::addControls( )
{

   AddControl( CTRL_STATIC, IDC_TXT_TAX_TYPE, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType );
   AddControl( CTRL_STATIC, IDC_TXT_ACCOUNT_TYPE, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AcctType );
   AddControl( CTRL_STATIC, IDC_TXT_PENSION_JURIS, IFASTBP_PROC::MFACCOUNT_CBO, ifds::PensionJuris );
   AddControl( CTRL_EDIT, IDC_EDT_PEN_SOURCE, IFASTBP_PROC::PENSION_INFO, ifds::Pension_sub, CTRLFLAG_FIELDS_FROM_SUB_LIST);
   AddControl( CTRL_DATE, IDC_DTP_EFFECTIVE_DATE, IFASTBP_PROC::PENSION_INFO, ifds::EffectiveDate );
   AddControl( CTRL_EDIT, IDC_EDT_MIN_AGE, IFASTBP_PROC::PENSION_INFO, ifds::MinWithAge );
   AddControl( CTRL_EDIT, IDC_EDT_UNISEX_AMT, IFASTBP_PROC::PENSION_INFO, ifds::UniSexPer );
   AddControl( CTRL_EDIT, IDC_EDT_SEX_DISTINCT_AMT, IFASTBP_PROC::PENSION_INFO, ifds::SexDistinctPer );
   AddControl( CTRL_STATIC, IDC_TXT_PORTION_OF_CMV, IFASTBP_PROC::PENSION_INFO, PENSION_INFO::PORTION_CURRENT_MARKET_VALUE );
   (dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_PEN_SOURCE)))->SetMaxCharNum( 40 );
   (dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_MIN_AGE)))->SetAllowedChars(I_("0123456789."));   
   (dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_MIN_AGE)))->SetMaxCharNum( 3 ); 
   (dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_UNISEX_AMT)))->SetAllowedChars(I_("0123456789."));   
   (dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_SEX_DISTINCT_AMT)))->SetAllowedChars(I_("0123456789."));
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
// @returns bool - true.
//******************************************************************************

bool PensionInfoDlg::doRefresh( GenericInterface * rpGICaller, 
                                const I_CHAR * szOriginalCommand )
{
   DString dstrMarket = DSTCommonFunctions::getMarket();
   _bCanLuxMarket = ( dstrMarket == MARKET_IDS::CANADA || dstrMarket == MARKET_IDS::LUXEMBOURG );   
   DString dstrShrNum, dstrAccountNum, dstrOldAccountNum, dstrEntityName;
   dstrOldAccountNum = GetAccount();
   getParent()->getField( this, ifds::AccountNum, dstrAccountNum ); 
/*   if ( dstrOldAccountNum == dstrAccountNum ) {
      ClearControls( PENSION_INFO::PENSION_INFO );
      ConnectControlsToData();
      LoadControls();
      return true;
   }
*/
   getParent()->getField(this, ifds::ShrNum, dstrShrNum); 
   SetAccount( dstrAccountNum );
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), 
                                                                                                    dstrAccountNum,                                                                                                     dstrEntityName );
   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);   
   ClearControls( );
   ConnectControlsToData();
   LoadControls();
   return(true);
}

//******************************************************************************

void PensionInfoDlg::OnkillFocusSexDistinct ()
{
   LoadControl ( IDC_TXT_PORTION_OF_CMV );
}

//******************************************************************************

void PensionInfoDlg::OnBtnReset ()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   getParent()->reset(this, IFASTBP_PROC::PENSION_INFO);
   doRefresh( this, NULL_STRING );
}

//******************************************************************************
void PensionInfoDlg::OnBtnAdmDates() 
{
   ShowAdminDates( IFASTBP_PROC::PENSION_INFO );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/PensionInfoDlg.cpp-arc  $
// 
//    Rev 1.5   Sep 15 2005 15:14:40   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.4   Mar 21 2003 18:39:28   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Oct 09 2002 23:55:50   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Jun 21 2002 16:39:48   ZHANGCEL
// Added support for Admin/Dates
// 
//    Rev 1.1   Jun 21 2002 11:27:14   HSUCHIN
// added support for reset
// 
//    Rev 1.0   Jun 02 2002 17:58:10   HSUCHIN
// Initial revision.
*/