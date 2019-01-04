//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : SysIndexDlg.h
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 05/01/01
//
// ^CLASS    : SysIndexDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"


#include <bfdata\bfdatafieldproperties.hpp>

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef SYSINDEXDLG_H
   #include "SysIndexDlg.h"
#endif

#ifndef SYSINDEXPROCESS_HPP 
   #include <ifastbp\SysIndexProcess.hpp>
#endif

#ifndef SYSINDEXPROCESSINCLUDES_H
   #include <ifastbp\SysIndexProcessIncludes.h>
#endif

#ifndef HISTORICALSYSTEMATICINDEXPROCESSINCLUDES_H
   #include <ifastbp\HistoricalSystematicIndexProcessIncludes.h>
#endif

// borrow remarke status set
#include <ifastdataimpl\dse_DSTC0005_VWRepeat_Record.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_SYS_INDEX;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SYS_INDEX;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_SYS_INDEX;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< SysIndexDlg > dlgCreator( CMD_GUI_SYS_INDEX );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME               = I_( "SysIndexDlg" );
   const I_CHAR * const LV_SYS_INDEX            = I_( "SystematicIndexing" );
   const I_CHAR * const SAVINGS_PLAN_TRANS_TYPE = I_( "V" );
   const I_CHAR * const GOOD                    = I_( "Y" );
   const I_CHAR * const BAD                     = I_( "N" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SystematicIndexListHeading;
   extern CLASS_IMPORT const BFTextFieldId SystematicPayType;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveShrNum;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const PAC;
}

//******************************************************************************
SysIndexDlg::SysIndexDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( SysIndexDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT( SysIndexDlg )
   //}}AFX_DATA_INIT
}

//******************************************************************************
SysIndexDlg::~SysIndexDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
void SysIndexDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( SysIndexDlg )
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP( SysIndexDlg, BaseMainDlg )
//{{AFX_MSG_MAP( SysIndexDlg )
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DEL, OnBtnDel )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_ADD6, OnBtnHistorical )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//******************************************************************************
BOOL SysIndexDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   DString dstrAccountNum, dstrShrNum, dstrEntityName( NULL_STRING );
   getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum );
   getGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum );
   if( !dstrAccountNum.empty() )
   {
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), dstrAccountNum, dstrEntityName);
   }
   SetShrAcctCaption( dstrShrNum, dstrAccountNum, dstrEntityName);
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void SysIndexDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   addControls( );
   SetUserAccesFunctionCode(UAF::PAC);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_SYS_INDEX);
   addBtnDeleteForPermissionCheck(IDC_BTN_DEL, IDC_LV_SYS_INDEX);
}


//******************************************************************************
SEVERITY SysIndexDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************
bool SysIndexDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   return(true);
}

//******************************************************************************
void SysIndexDlg::OnBtnAdd() 
{
   AddToListControl( IDC_LV_SYS_INDEX );
}

//******************************************************************************
void SysIndexDlg::OnBtnDel() 
{
   DeleteFromListControl( IDC_LV_SYS_INDEX );
}

//******************************************************************************

void SysIndexDlg::OnBtnReset() 
{   
   ResetListItem( IDC_LV_SYS_INDEX );
}

//******************************************************************************

void SysIndexDlg::OnBtnHistorical() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnHistorical" ) );

   CWaitCursor wait;
   E_COMMANDRETURN eRtn;
   try
   {
      DString dstrTransNum;
      getParent()->getField( this, IFASTBP_PROC::SYSTEMATIC, ifds::TransNum, dstrTransNum, false );
      setParameter( HISTSYSINDEX::PARM_TRANSACTIONNUMBER, dstrTransNum );

      eRtn = invokeCommand(getParent(), CMD_BPROC_HISTORICAL_SYS_INDEX, PROC_SUPPORT, true, NULL);
      if( eRtn != CMD_CANCEL )
      {
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
void SysIndexDlg::addControls( )
{

   AddListControl( CLASSNAME, IDC_LV_SYS_INDEX, LV_SYS_INDEX, ifds::SystematicIndexListHeading, 
                   IFASTBP_PROC::SYS_INDEX_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD  );

   AddControl( CTRL_STATIC, IDC_TXT_PAY_TYPE,        IFASTBP_PROC::SYSTEMATIC, ifds::PayType );
   AddControl( CTRL_STATIC, IDC_TXT_STATUS,          IFASTBP_PROC::SYSTEMATIC, ifds::StatusCode );
   AddControl( CTRL_STATIC, IDC_TXT_FUND_CLASS,      IFASTBP_PROC::SYSTEMATIC, ifds::FundCode );
   AddControl( CTRL_STATIC, IDC_TXT_EFFECTIVE_DATE,  IFASTBP_PROC::SYSTEMATIC, ifds::EffectiveDate );
   AddControl( CTRL_STATIC, IDC_TXT_STOP_DATE,       IFASTBP_PROC::SYSTEMATIC, ifds::StopDate );
   AddControl( CTRL_STATIC, IDC_TXT_AMOUNT,          IFASTBP_PROC::SYSTEMATIC, ifds::Amount );
   AddControl( CTRL_STATIC, IDC_TXT_AMOUNT_TYPE,     IFASTBP_PROC::SYSTEMATIC, ifds::AmountType );
   AddControl( CTRL_STATIC, IDC_TXT_FREQUENCY,       IFASTBP_PROC::SYSTEMATIC, ifds::Frequency );
   AddControl( CTRL_STATIC, IDC_TXT_TRANS_NBR,       IFASTBP_PROC::SYSTEMATIC, ifds::TransNum );

   AddControl( CTRL_STATIC, IDC_TXT_NEXT_INDEX_DATE, IFASTBP_PROC::SYS_INDEX_LIST, ifds::NextIndexDate,  0, IDC_LV_SYS_INDEX );
   AddControl( CTRL_EDIT,   IDC_EDT_INDEX_AMOUNT,    IFASTBP_PROC::SYS_INDEX_LIST, ifds::IndexAmt,       0, IDC_LV_SYS_INDEX );
   AddControl( CTRL_COMBO,  IDC_CMB_TYPE,            IFASTBP_PROC::SYS_INDEX_LIST, ifds::IndexType,      CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SYS_INDEX );
   AddControl( CTRL_EDIT,   IDC_EDT_FREQUENCY,       IFASTBP_PROC::SYS_INDEX_LIST, ifds::IndexFrequency, 0, IDC_LV_SYS_INDEX );
   AddControl( CTRL_DATE,   IDC_DTP_EFFECTIVE_DATE,  IFASTBP_PROC::SYS_INDEX_LIST, ifds::StartDate,      0, IDC_LV_SYS_INDEX );
   AddControl( CTRL_DATE,   IDC_DTP_STOP_DATE,       IFASTBP_PROC::SYS_INDEX_LIST, ifds::EndDate,        0, IDC_LV_SYS_INDEX );

   DSTEdit *ed = dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_FREQUENCY ) );
   ed->SetMaxCharNum( 4 );
   ed->SetAllowedChars( I_("0123456789") );

   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_INDEX_AMOUNT ) )->SetAllowedChars( I_("0123456789.") );

   LoadListControl ( IDC_LV_SYS_INDEX );

   int numListItems = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::SYS_INDEX_LIST);
   if( numListItems == 0 )
      AddToListControl( IDC_LV_SYS_INDEX );

   ConnectControlsToData ();
   LoadControls();
}

//******************************************************************************

bool SysIndexDlg::GetDataForControl( UINT controlID, DString &strValueOut, bool bFormatted, int index ) const
{
   if( controlID == IDC_TXT_PAY_TYPE )
   {
      DString dstrPayType, dstrTransType;
      getParent()->getField( this, IFASTBP_PROC::SYSTEMATIC, ifds::TransType, dstrTransType, false );
      getParent()->getField( this, IFASTBP_PROC::SYSTEMATIC, ifds::PayType, dstrPayType, false );
      const BFDataFieldProperties* pProps = BFDataFieldProperties::get( ifds::SystematicPayType );
      const BFSubstitutionSet* pSubSet = pProps->getSubstitutionSet( ClientLocaleContext::get() );
      if( NULL != pSubSet && pSubSet->isKey( dstrTransType + I_("-") + dstrPayType ) )
      {
         strValueOut = pSubSet->getValue( dstrTransType + I_("-") + dstrPayType );
      }
      return(true);
   }
   return(false);
}

//******************************************************************************
bool SysIndexDlg::GetOverrideItemString(long lSubstituteId, const DString &dstrColumnKey, DString &dstrOut)
{
   if( dstrColumnKey == I_("EndDate") )
   {
      getParent()->getField( this, IFASTBP_PROC::SYS_INDEX_LIST, ifds::EndDate, dstrOut );
      if( dstrOut == NULL_STRING )
      {
         dstrOut = DSTCommonFunctions::getMask( ifds::EndDate );
         dstrOut.replace(dstrOut.find(I_("MM")), 2, I_("12"));
         dstrOut.replace(dstrOut.find(I_("dd")), 2, I_("31"));
         dstrOut.replace(dstrOut.find(I_("yyyy")), 4, I_("9999"));
         dstrOut.replace(dstrOut.find(I_("(")), 1, I_(""));
         dstrOut.replace(dstrOut.find(I_(")")), 1, I_(""));         
      }
      return(true);
   }
   return(false);
}

//******************************************************************************
bool SysIndexDlg::doDisablePermCheckButton(UINT nID){
   if( nID == IDC_BTN_ADD || nID == IDC_BTN_DEL )
   {
      DString dstrStatusCode;
      getParent()->getField( this, IFASTBP_PROC::SYSTEMATIC, ifds::StatusCode, dstrStatusCode, false );
      return(dstrStatusCode == BAD);
   }
   return(false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SysIndexDlg.cpp-arc  $
// 
//    Rev 1.18   Sep 15 2005 15:15:22   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.17   Jun 10 2003 11:48:20   popescu
// change name of the systematic cbo container to be compliant with the standard, re-named the ACCOUNT_DISTRIBUTION_BANK_LIST in ACCOUNT_DISTRIBUTION since nobody was using it, and re-used the id for banking instructions process
// 
//    Rev 1.16   Mar 21 2003 18:41:20   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.15   Oct 09 2002 23:56:14   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.14   Aug 29 2002 12:57:26   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.13   22 May 2002 19:16:28   PURDYECH
// BFData Implementation
// 
//    Rev 1.12   27 Mar 2002 20:01:24   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.11   Jan 10 2002 15:02:10   ZHANGCEL
// bug fix for delete problem
// 
//    Rev 1.10   23 Nov 2001 14:25:34   KOVACSRO
// perm check changes.
// 
//    Rev 1.9   05 Aug 2001 15:31:00   HSUCHIN
// changed code to support Frequency as Edit box and set entry restrictions to Amount and Frequency edit boxes
// 
//    Rev 1.8   02 Aug 2001 18:28:38   HSUCHIN
// added permission check
// 
//    Rev 1.7   18 Jul 2001 14:09:48   HSUCHIN
// bug fix for formatting end date
// 
//    Rev 1.6   11 Jul 2001 15:13:58   HSUCHIN
// bug fix for getoverride...
// 
//    Rev 1.5   04 Jul 2001 16:32:58   HSUCHIN
// added override for StopDate
// 
//    Rev 1.4   21 Jun 2001 10:11:42   HSUCHIN
// saving plan field name fix
// 
//    Rev 1.3   13 Jun 2001 16:42:24   HSUCHIN
// bug fix for PayType description
// 
//    Rev 1.2   Jun 01 2001 13:45:14   HERNANDO
// Added OnBtnHistorical.  Added caption.
// 
//    Rev 1.1   31 May 2001 19:30:08   HSUCHIN
// code cleanup and many enhancements
// 
//    Rev 1.0   03 May 2001 13:47:06   BUZILAMI
// Initial revision.
 * 
 */


