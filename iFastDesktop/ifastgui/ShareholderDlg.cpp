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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ShareholderDlg.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ----------------------------------------------------------
//
// ^CLASS    : ShareholderDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//
//******************************************************************************
#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef SHAREHOLDERDLG_H
   #include "ShareholderDlg.h"
#endif

#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif

#ifndef DSTCOMBOBOX_H
   #include <uibase\DSTComboBox.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef NASUPROCESSINCLUDES_H
   #include <ifastbp\NASUProcessIncludes.h>
#endif

#ifndef SHAREHOLDERPROCESSINCLUDES_H
   #include <ifastbp\ShareholderProcessIncludes.h>
#endif

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastgui\ifasthistoricalinfo.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_SHAREHOLDER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_INFO;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ShareholderDlg > dlgCreator( CMD_GUI_SHAREHOLDER );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ShareholderDlg" );
   const I_CHAR * const ADJUSTTOPROCESSTYPE = I_( "adjustToProcessType" );

   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );

   const long SHAREHOLDERNUM = 13L; // The maximum length of Shareholder number

   const int NEW_SHAREHOLDER_GROUP = 1;
   const int EXISTING_SHAREHOLDER_GROUP = 2;
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Substitute_Description;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_DETAIL;
}


//*****************************************************************************
// Public methods
//*****************************************************************************
ShareholderDlg::ShareholderDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ShareholderDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_dstrCreatingShareholder( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(ShareholderDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void ShareholderDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ShareholderDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY ShareholderDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   DString str;
   getParameter( I_("ManualShr"), str );
   if( str == YES )
      _bManualShr = true;
   else
      _bManualShr = false;
   getParameter( I_("ShrCreated"), str );
   if( str == YES )
      _bShrCreated = true;
   else
      _bShrCreated = false;

   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(ShareholderDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ShareholderDlg)
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL ShareholderDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   //I am not sure how we are going to handle that, for now leave it like this(SP)   
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      GetDlgItem( IDC_DTP_EFFECTIVE_DATE )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_EDT_EFFECTIVE_DATE )->ShowWindow( SW_HIDE );
//		dynamic_cast< CEdit * >( GetDlgItem( IDC_EDT_EFFECTIVE_DATE ) )->SetReadOnly();

      //if ShrEftConsol = 'No', IDC_TXT_CONSOL_EFT and IDC_CMB_CONSOL_EFT should not be displayed	
      DString dstrShrEFTConsol;

      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption(  ifds::ShrEFTConsol, dstrShrEFTConsol, BF::HOST );

      if( dstrShrEFTConsol == YES )
      {
         GetDlgItem( IDC_TXT_CONSOL_EFT )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_CMB_CONSOL_EFT )->ShowWindow( SW_SHOW );
      }
      else
      {
         GetDlgItem( IDC_TXT_CONSOL_EFT )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_CMB_CONSOL_EFT )->ShowWindow( SW_HIDE );
      }
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      GetDlgItem( IDC_DTP_EFFECTIVE_DATE )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_EDT_EFFECTIVE_DATE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_CONSOL_EFT )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_CMB_CONSOL_EFT )->ShowWindow( SW_HIDE );
   }
   return(TRUE);
}

//*****************************************************************************
void ShareholderDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode(UAF::ACCOUNT_DETAIL);//have to be changed to SHAREHOLDER 
   addControlGroupIDForPermissionCheck(0);
   addControlGroupIDForPermissionCheck(NEW_SHAREHOLDER_GROUP);
   addControlGroupIDForPermissionCheck(EXISTING_SHAREHOLDER_GROUP);

   //add the controls not affected by the adjustToProcessType method
   AddControl( CTRL_COMBO, IDC_CMB_FUNDS_RELATIONSHIP, IFASTBP_PROC::SHAREHOLDER_CBO, 
               ifds::FundRelnCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_RESIDENCE_PROVINCE, IFASTBP_PROC::SHAREHOLDER_CBO, 
               ifds::ResProvCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_TAX_JURISDICTION, IFASTBP_PROC::SHAREHOLDER_CBO, 
               ifds::TaxJurisCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_CONFIDENTIAL, IFASTBP_PROC::SHAREHOLDER_CBO, 
               ifds::Confidential, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_CHANNEL, IFASTBP_PROC::SHAREHOLDER_CBO, 
               ifds::Channel,CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   AddControl( CTRL_DATE, IDC_DTP_EFFECTIVE_DATE, IFASTBP_PROC::SHAREHOLDER_CBO, 
               ifds::EffectiveDate );
   AddControl( CTRL_STATIC, IDC_TXT_GROUP_NAME, IFASTBP_PROC::SHAREHOLDER_CBO, 
               ifds::GroupName1 );

   // Controls used for new shareholder
   getParent()->getField( this, BF::NullContainerId, SHRPROC::CREATING_SHAREHOLDER,
                          m_dstrCreatingShareholder );

   bool bNewShareHolder = m_dstrCreatingShareholder == YES;
   GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( !bNewShareHolder );
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      if( bNewShareHolder )
      {
         AddControl( CTRL_COMBO, IDC_CMB_ACCT_DESIGNATION, IFASTBP_PROC::SHAREHOLDER_CBO,
                     ifds::AcctDesignation, CTRLFLAG_INITCOMBO_BY_SUB_LIST, NEW_SHAREHOLDER_GROUP );
      }
      else
      {
         AddControl( CTRL_COMBO, IDC_CMB_ACCT_DESIGNATION, IFASTBP_PROC::SHAREHOLDER_CBO,
                     ifds::AcctDesignation, CTRLFLAG_INITCOMBO_BY_SUB_LIST, EXISTING_SHAREHOLDER_GROUP );
      }
      GetDlgItem( IDC_TXT_ACCT_DESIGNATION )->ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_TXT_ACCT_DESIGNATION )->EnableWindow( SW_HIDE );
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      if( bNewShareHolder )
      {
         AddControl( CTRL_STATIC, IDC_TXT_ACCT_DESIGNATION, IFASTBP_PROC::SHAREHOLDER_CBO,
                     ifds::AcctDesignationDesc, 0, NEW_SHAREHOLDER_GROUP );
      }
      else
      {
         AddControl( CTRL_STATIC, IDC_TXT_ACCT_DESIGNATION, IFASTBP_PROC::SHAREHOLDER_CBO,
                     ifds::AcctDesignationDesc, 0, EXISTING_SHAREHOLDER_GROUP );
      }
      GetDlgItem( IDC_CMB_ACCT_DESIGNATION )->ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_TXT_ACCT_DESIGNATION )->EnableWindow( SW_HIDE );
   }

   if( bNewShareHolder )
   {
      AddControl( CTRL_EDIT, IDC_EDT_SHAREHOLDER_NUMBER, BF::NullContainerId,ifds::ShrNum, 0, NEW_SHAREHOLDER_GROUP );

   }
   else
   {
      AddControl( CTRL_EDIT, IDC_EDT_SHAREHOLDER_NUMBER, BF::NullContainerId,ifds::ShrNum, 0, EXISTING_SHAREHOLDER_GROUP );

   }

   DSTEdit *dstEditShrtNum  = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_SHAREHOLDER_NUMBER ) );
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_SHAREHOLDER_NUMBER))->SetAllowedChars(I_("0123456789"));

   //shareholder number shouldn't exceed 15 chars
   dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_SHAREHOLDER_NUMBER ) )->
   SetMaxCharNum( SHAREHOLDERNUM );


   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      AddControl( CTRL_COMBO, IDC_CMB_CONSOL_EFT, IFASTBP_PROC::SHAREHOLDER_CBO,
                  ifds::ConsolEFT, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   }

   //Rule: GrpLevel in view 83 actually come back as either 'S' or 'A'. If value is 'S',
   //    group code should be display and updatable on shareholder screen. When the 
   //    value come back as 'A', Group code should be display and updatable on Account
   //    Information screen but should be disappear from the Shareholder screen.

   //get GrpCodeLevel-83

   displayGroupRelated();

   if( _bManualShr && !_bShrCreated )
   {
      ConnectControlToData( IDC_EDT_SHAREHOLDER_NUMBER, true );
      LoadControl( IDC_EDT_SHAREHOLDER_NUMBER );
      enableControls();
   }
   else
      doRefresh( this, NULL_STRING );

}

//*******************************************************************************
void  ShareholderDlg::displayGroupRelated()
{

   DString grpCodeLevel;
   getParent()->getField( this, BF::NullContainerId, ifds::GrpCodeLevel, grpCodeLevel, false );
   grpCodeLevel.strip().upperCase();

   if( I_( "A" ) == grpCodeLevel )
   {  //should be disappear from the Shareholder screen
      GetDlgItem( IDC_CMB_GROUP_NBR )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_GROUP_NAME )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_STATIC_GROUP_NBR )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_STATIC_GROUP_NAME )->ShowWindow( SW_HIDE );
   }
   else if( I_( "S" ) == grpCodeLevel )
   {
      AddControl( CTRL_COMBO, IDC_CMB_GROUP_NBR, IFASTBP_PROC::SHAREHOLDER_CBO,
                  ifds::GroupCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   }
}
//*******************************************************************************
void ShareholderDlg::adjustToProcessType()
{
   TRACE_METHOD( CLASSNAME, ADJUSTTOPROCESSTYPE );
   DString strCaption;

   //get the state of the dialog
   getParent()->getField( this, BF::NullContainerId, SHRPROC::CREATING_SHAREHOLDER,
                          m_dstrCreatingShareholder );
   bool bNewShareHolder = m_dstrCreatingShareholder == YES;

   if( !bNewShareHolder )
   { //build the caption
      getParent()->getField( this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::Name1,
                             strCaption, false );
      strCaption = I_(" ") + strCaption.strip();
   }
   ConnectControlsToData( NEW_SHAREHOLDER_GROUP, bNewShareHolder, true );
   ConnectControlsToData( EXISTING_SHAREHOLDER_GROUP, !bNewShareHolder, true );

   SetCaption( strCaption );
   GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( !bNewShareHolder );
}

//*******************************************************************************
void ShareholderDlg::PostOk( bool /*bOkStatus*/ )
{
   DString shareholderNum;

   getParent()->getField( this, BF::NullContainerId, SHRPROC::SHAREHOLDER_NUM_FIELD, shareholderNum );

   setParameter( NASULIT::CREATING_SHAREHOLDER, m_dstrCreatingShareholder );
   setParameter( SHRPROC::SHAREHOLDER_NUM, shareholderNum );
}

//******************************************************************************
void ShareholderDlg::OnBtnAdmDates() 
{
   ShowAdminDates( IFASTBP_PROC::SHAREHOLDER_CBO );
}


//******************************************************************************
bool ShareholderDlg::doRefresh(
                              GenericInterface * rpGICaller,
                              const I_CHAR* szOriginalCommand
                              )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   //get the state of the dialog
   adjustToProcessType();

   ConnectControlsToData();
   LoadControls( -1L );// Using -1 to load all controls
   GetDlgItem( IDOK )->EnableWindow( true );
   return(true);
}
//***********************************************************
void ShareholderDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   switch( controlID )
   {
      
      case IDC_EDT_SHAREHOLDER_NUMBER:
         {
            if( _bManualShr )
            {
               if( strValue != NULL_STRING )
               {
                  DSTEdit* pEdit = dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_SHAREHOLDER_NUMBER));
                  if( pEdit )
                     pEdit->SetReadOnly(true);
                  if( !_bShrCreated )
                  {
                     _bShrCreated = true;
                     doRefresh(this, NULL_STRING);
                  }
               }
            }
            else
            {
               DSTEdit* pEdit = dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_SHAREHOLDER_NUMBER));
               if( pEdit )
                  pEdit->SetReadOnly(true);
            }
         }
         break;
      default:
         break;
   }
}

//******************************************************************************
void ShareholderDlg::enableControls()
{
   GetDlgItem( IDC_CMB_ACCT_DESIGNATION )->EnableWindow( _bShrCreated );
   GetDlgItem( IDC_CMB_GROUP_NBR )->EnableWindow( _bShrCreated );
   GetDlgItem( IDC_CMB_RESIDENCE_PROVINCE )->EnableWindow( _bShrCreated );
   GetDlgItem( IDC_DTP_EFFECTIVE_DATE )->EnableWindow( _bShrCreated );
   GetDlgItem( IDC_CMB_CONSOL_EFT )->EnableWindow( _bShrCreated );
   GetDlgItem( IDC_CMB_CONFIDENTIAL )->EnableWindow( _bShrCreated );
   GetDlgItem( IDC_CMB_CHANNEL )->EnableWindow( _bShrCreated );

   GetDlgItem( IDC_CMB_FUNDS_RELATIONSHIP )->EnableWindow( _bShrCreated );
   GetDlgItem( IDC_CMB_TAX_JURISDICTION )->EnableWindow( _bShrCreated );
   //GetDlgItem( IDC_EDT_SHAREHOLDER_NUMBER )->EnableWindow( _bShrCreated );   
   GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( _bShrCreated );
   GetDlgItem( IDOK )->EnableWindow( _bShrCreated );

}

//******************************************************************************

void ShareholderDlg::OnBtnHistorical() 
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnHistorical") );

   // Set Parameters
   DString dstrShareholderNumber;
   getParent()->getField( this, BF::NullContainerId, SHRPROC::SHAREHOLDER_NUM_FIELD, dstrShareholderNumber );
   setParameter( MFCAN_IP_PARAM::SHR_NUM, dstrShareholderNumber );

   IFastHistoricalInfo historicalInfo;
   historicalInfo( this, BF::NullContainerId, I_("SHRINFO") );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ShareholderDlg.cpp-arc  $
 * 
 *    Rev 1.33   Sep 15 2005 15:15:10   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.32   Mar 16 2004 15:26:48   HERNANDO
 * PET965 FN11 - Disabled Historical button for new shareholders.
 * 
 *    Rev 1.31   Mar 10 2004 10:22:32   HERNANDO
 * PET965 FN11 - Switched to using iFastHistoricalInfo.
 * 
 *    Rev 1.30   Feb 28 2004 16:08:58   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.29   Nov 11 2003 10:26:46   FENGYONG
 * PTS 10023904, account designation overload between the combo box and edit box.
 * 
 *    Rev 1.28   Aug 21 2003 14:25:48   linmay
 * change to IDC_CMB_CHANNEL
 * 
 *    Rev 1.27   Aug 21 2003 09:24:12   linmay
 * added control for Confidential and Channel
 * 
 *    Rev 1.26   Jun 24 2003 14:27:58   ZHANGCEL
 * PTS 10018832: restore "SetUserAccesFunctionCode(UAF::ACCOUNT_DETAIL)"
 * 
 *    Rev 1.25   Mar 21 2003 18:40:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.24   Jan 13 2003 18:10:58   sanchez
 * Changes for Shareholer
 * 
 *    Rev 1.23   Oct 09 2002 23:56:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.22   22 May 2002 19:16:26   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.21   27 Mar 2002 20:01:22   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.20   Nov 14 2001 15:34:14   YINGBAOL
 * code clean up
 * 
 *    Rev 1.19   Nov 07 2001 16:46:36   YINGBAOL
 * reimplemet GroupCode Logic
 * 
 *    Rev 1.18   Nov 07 2001 13:59:54   YINGBAOL
 * avoid base showup groupcode
 * 
 *    Rev 1.17   Nov 05 2001 17:12:52   YINGBAOL
 * GrpCodeLevel is hold by Process instead of CBO
 * 
 *    Rev 1.16   Oct 25 2001 15:32:54   YINGBAOL
 * add displayGrroupRelated() method and fix related issues
 * 
 *    Rev 1.15   Aug 05 2001 03:02:30   YINGBAOL
 * fix shareholder number display issue
 * 
 *    Rev 1.14   Jul 12 2001 15:29:06   JANKAREN
 * new logic for Consolidate EFT
 * 
 *    Rev 1.13   15 Jun 2001 14:53:34   KOVACSRO
 * Added new and existing shareholder groups for perm. check.
 * 
 *    Rev 1.12   May 02 2001 10:03:20   OLTEANCR
 * modified doInit( ), onPostInitDlg( ), doRefresh;
 * added enableControls( )
 * 
 *    Rev 1.11   Apr 02 2001 12:45:42   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.10   29 Mar 2001 16:12:22   KOVACSRO
 * perm. check.
 * 
 *    Rev 1.9   27 Mar 2001 16:54:58   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.8   Feb 27 2001 16:52:40   DINACORN
 * M3/C4 synchronization - bug fix for AcctDesignation
 * 
 *    Rev 1.7   Dec 01 2000 14:51:40   KOVACSRO
 * Added permission check.
 * 
 *    Rev 1.6   Sep 29 2000 13:29:20   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.5   Aug 16 2000 10:42:06   DINACORN
 * Modified Controls for Group
 * 
 *    Rev 1.4   Jul 12 2000 10:36:50   DINACORN
 * Modified the field Acct.designation - Shareholder screen
 * 
 *    Rev 1.2   Mar 29 2000 16:34:58   YINGZ
 * code sync
 * 
 *    Rev 1.1   Mar 08 2000 09:58:04   HSUCHIN
 * added Canadian stuff
 * 
 *    Rev 1.0   Feb 15 2000 11:01:24   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.41   Jan 19 2000 15:32:06   POPESCUS
 * fixes in Shareholder
 * 
 *    Rev 1.40   Jan 06 2000 11:45:28   ZHANGCEL
 * Remove name2 from title bar
 * 
 *    Rev 1.38   Dec 21 1999 14:15:04   POPESCUS
 * cleanup the code, validations and misc
 * 
 *    Rev 1.37   Dec 14 1999 13:21:36   DT24433
 * removed commented code, misc
 * 
 *    Rev 1.36   Dec 09 1999 19:27:26   DT24433
 * various changes
 * 
 *    Rev 1.35   Dec 05 1999 18:58:42   VASILEAD
 * Friday night changes( don't be so hard on us )
 * 
 *    Rev 1.34   Nov 29 1999 11:26:52   POPESCUS
 * Fixes in NASU flow
 * 
 *    Rev 1.33   Nov 28 1999 17:59:46   POPESCUS
 * Fixes
 * 
 *    Rev 1.32   Nov 28 1999 14:39:38   POPESCUS
 * ?
 * 
 *    Rev 1.31   Nov 25 1999 17:08:50   POPESCUS
 * 
 *    Rev 1.30   Nov 25 1999 11:13:34   ZHANGCEL
 * Add ShareHolder Number length
 * 
 *    Rev 1.29   Nov 23 1999 18:05:48   POPESCUS
 * NASU flow
 * 
 *    Rev 1.28   Nov 22 1999 10:36:22   ZHANGCEL
 * Modify shareholder number validation method
 * 
 *    Rev 1.26   Nov 09 1999 18:40:10   DT24433
 * removed Ok/Cancel, commented out some code
 * 
 *    Rev 1.25   Nov 09 1999 18:11:14   ZHANGCEL
 * Modify Dialog Controls
 * 
 *    Rev 1.24   Nov 08 1999 15:18:18   ZHANGCEL
 * process  ShrNumCtrl and DefaultGrp 
 * 
 *    Rev 1.23   Nov 01 1999 13:15:16   ZHANGCEL
 *  Add SetSelItemCodeInField function
 * 
 *    Rev 1.21   Oct 27 1999 14:03:44   BUZILA
 * changes to FillInSubstituteValues
 * 
 *    Rev 1.20   Oct 27 1999 10:12:54   ZHANGCEL
 * New shareholder mechanism
 * 
 *    Rev 1.19   Oct 06 1999 17:15:04   PRAGERYA
 * Market-specific stuff
 * 
 *    Rev 1.18   Sep 24 1999 10:13:58   PRAGERYA
 * "Milestone" check in
 * 
 *    Rev 1.17   13 Sep 1999 13:53:00   HUANGSHA
 * Synchronize with M1's changes
 * 
 *    Rev 1.16   Sep 02 1999 07:43:34   BUZILA
 * commented out DBR::AcctDesignation
 * 
 *    Rev 1.15   Sep 01 1999 15:46:06   PRAGERYA
 * Incr 2 enhancements
 * 
 *    Rev 1.14   Aug 26 1999 16:11:40   PRAGERYA
 * Implementing Search for Shareholder and Account Info
 * 
 *    Rev 1.13   Aug 25 1999 15:53:56   PRAGERYA
 * getFieldFromCurrentListItem -> getField
 * 
 *    Rev 1.12   Aug 18 1999 12:22:52   PRAGERYA
 * Substitute lists in combo boxes
 * 
 *    Rev 1.11   Aug 17 1999 16:32:14   PRAGERYA
 * Filling Combo Boxes
 * 
 *    Rev 1.10   Aug 08 1999 19:34:06   PRAGERYA
 * All in!
 * 
 *    Rev 1.9   Aug 04 1999 09:40:48   PRAGERYA
 * Implementing dialog
 * 
 *    Rev 1.8   Jul 30 1999 17:28:58   PRAGERYA
 * Coded to the level of Incr1
 * 
 *    Rev 1.7   Jul 27 1999 14:07:28   BUZILA
 * fix
 * 
 *    Rev 1.6   Jul 23 1999 15:31:38   SMITHDAV
 * m21
 * 
 *    Rev 1.3   Jul 20 1999 14:23:56   YINGZ
 * add hour glass
 * 
 *    Rev 1.2   Jul 20 1999 11:19:30   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:05:52   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */





