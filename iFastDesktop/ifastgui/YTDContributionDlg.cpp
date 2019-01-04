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
// ^FILE   : YTDContributionDlg.cpp
// ^AUTHOR : 
// ^DATE   : 18/08/2001
//
// ^CLASS    : YTDContributionDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef CSISESSION_H
   #include <ifastcsi\CsiSession.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTCLISTCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif

#ifndef DSTCCSI_H
   #include <ifastcsi\ifastcsi.h>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef YTDCONTRIBUTIONDLG_H
   #include "YTDContributionDlg.h"
#endif

#ifndef YTDCONTIBUTIONPROCESSINCLUDES_H
   #include <ifastbp\YTDContributionProcessIncludes.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_YTD_CONTRIBUTION;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< YTDContributionDlg > dlgCreator( CMD_GUI_YTD_CONTRIBUTION );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME                  = I_( "YTDContributionDlg" );
   const I_CHAR * const LV_RSP_CONTRIBUTION_LIST   = I_( "RSPContributionList" );
   const I_CHAR * const LV_RSP_RECEIPTS_LIST       = I_( "RSPReceiptsList" );
   const I_CHAR * const SPOUSAL_ACCOUNT            = I_( "1" );
   const I_CHAR * const YES                        = I_( "Y" );   
   const I_CHAR * const COMMA                      = I_( "," );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveShrNum;
   extern CLASS_IMPORT const BFTextFieldId Name;
   extern CLASS_IMPORT const BFTextFieldId RSPContributionHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId RSPReceiptsHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId EDocsAccessAppl;
}

namespace CND
{  // Conditions used
    extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PDF_VIEWER;


//******************************************************************************
// Constructor
//******************************************************************************
YTDContributionDlg::YTDContributionDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( YTDContributionDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT( YTDContributionDlg )
   //}}AFX_DATA_INIT
}

//******************************************************************************
// Destructor
//******************************************************************************
YTDContributionDlg::~YTDContributionDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void YTDContributionDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( YTDContributionDlg )
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( YTDContributionDlg, BaseMainDlg )
//{{AFX_MSG_MAP( YTDContributionDlg )
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_CHANGE, OnBtnChange )
ON_BN_CLICKED( IDC_BTN_ADMINDATES, OnBtnAdminDates )
ON_BN_CLICKED( IDC_BTN_VIEW_INQ_PDF, OnBtnViewInqPDF)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL YTDContributionDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   DString  dstrAccountNum, dstrShrNum, dstrEntityName(NULL_STRING);

   GetTitleDetails(dstrShrNum, dstrAccountNum, dstrEntityName);

   SetShrAcctCaption( dstrShrNum, dstrAccountNum, dstrEntityName);
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void YTDContributionDlg::GetTitleDetails(DString &dstrShrNum, DString &dstrAccountNum, DString &dstrEntityName)
{
    getGlobal(WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum);
    getGlobal(WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum);

    if (!dstrAccountNum.empty())
    {
        dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), dstrAccountNum, dstrEntityName);
    }
}

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************
void YTDContributionDlg::OnPostInitDialog()
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   addControls( );
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );

   DisplayDeliveryOption();

   bool bEDocsAccessAppl;
   DString dstrEDocsAccessAppl;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   dstWorkSession->getOption(ifds::EDocsAccessAppl, dstrEDocsAccessAppl, getParent()->getDataGroupId());
   
   bEDocsAccessAppl = dstrEDocsAccessAppl.stripAll().upperCase() == YES;

   GetDlgItem(IDC_STATIC_DISCLAIMER_LINE1)->ShowWindow(bEDocsAccessAppl);
   GetDlgItem(IDC_STATIC_DISCLAIMER_LINE2)->ShowWindow(bEDocsAccessAppl);
   GetDlgItem(IDC_BTN_VIEW_INQ_PDF)->EnableWindow(bEDocsAccessAppl);
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY YTDContributionDlg::doInit()
{
   return(NO_CONDITION);
}

//******************************************************************************
// This method sets up the custom controls to the correct data set.
//******************************************************************************
void YTDContributionDlg::addControls( )
{
   DString dstrAccountType;
   // Initializes the RSP Contribution List.
   AddListControl( CLASSNAME, IDC_RSP_CONTRIBUTION_LIST, LV_RSP_CONTRIBUTION_LIST, ifds::RSPContributionHeadingSet, 
                   IFASTBP_PROC::RSP_CONTRIBUTION_LIST, 0, true, LISTFLAG_NOT_UPDATABLE);

   // Initializes the RSP Receipts List as the child of the RSP Contribution List
   AddListControl( CLASSNAME, IDC_RSP_RECEIPTS_LIST, LV_RSP_RECEIPTS_LIST, ifds::RSPReceiptsHeadingSet, 
                   IFASTBP_PROC::RSP_RECEIPTS_LIST, IDC_RSP_CONTRIBUTION_LIST, true, LISTFLAG_NOT_UPDATABLE);

   // Initializes the RSP Contributor details retrieved from various CBOs
   AddControl( CTRL_STATIC,   IDC_OWNER_ENTITY_NAME,     IFASTBP_PROC::RSP_RECEIPTS_LIST,       ifds::Name1 ,
               0, IDC_RSP_RECEIPTS_LIST );
   AddControl( CTRL_STATIC,   IDC_OWNER_SIN,             IFASTBP_PROC::RSP_RECEIPTS_LIST,       ifds::SIN, 
               0, IDC_RSP_RECEIPTS_LIST );
   AddControl( CTRL_STATIC,   IDC_TAX_ADDR1,             IFASTBP_PROC::RSP_RECEIPTS_LIST,       ifds::Address1, 
               0, IDC_RSP_RECEIPTS_LIST );
   AddControl( CTRL_STATIC,   IDC_RECEIPT_TYPE,          IFASTBP_PROC::RSP_RECEIPTS_LIST,       ifds::RecipientType, 
               0, IDC_RSP_RECEIPTS_LIST );
   AddControl( CTRL_STATIC,   IDC_PRE_RECEIPT_NO,        IFASTBP_PROC::RSP_RECEIPTS_LIST,       ifds::PrevRcptNo, 
               0, IDC_RSP_RECEIPTS_LIST );
   AddControl( CTRL_STATIC,   IDC_AGENT_FULL_NAEM,       IFASTBP_PROC::ACCOUNT,                 ifds::SlsrepName, 
               0, IDC_RSP_RECEIPTS_LIST );

   // Check to see if the current account is a spousal account.
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT, ifds::AcctType, dstrAccountType, false );
   // Show spousal information if the account type is spousal.
   if( dstrAccountType == SPOUSAL_ACCOUNT )
   {
      AddControl( CTRL_STATIC,   IDC_SPOUSAL_NAME,          IFASTBP_PROC::RSP_RECEIPTS_LIST,    ifds::CName1,
                  0, IDC_RSP_RECEIPTS_LIST );
      AddControl( CTRL_STATIC,   IDC_SPOUSAL_SIN,           IFASTBP_PROC::RSP_RECEIPTS_LIST,    ifds::Csin,
                  0, IDC_RSP_RECEIPTS_LIST );
      ShowSpousal ( true );
   }
   else
   {
      ShowSpousal ( false );
   }

   LoadListControl ( IDC_RSP_CONTRIBUTION_LIST );  
   ConnectControlsToData ();
   LoadControls();
}

//******************************************************************************
// Dialog Button method for OnBtnChange.  Initiates a CSI session to the account
// transaction screen on the character base.
//******************************************************************************
void YTDContributionDlg::OnBtnChange( )
{
   DString strAccountNum;
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT, ifds::AccountNum, strAccountNum );
   strAccountNum.stripLeading().stripLeading( I_CHAR( '0' ) ).stripTrailing();
   setCsiParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(strAccountNum) );
   executeCsiProcess( DcCsiProcesses::YTD_CONTRIBUTION);      
}


//******************************************************************************
void YTDContributionDlg::OnBtnViewInqPDF()
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnViewInqPDF"));

    try
    {
        DString urlParamsIDI, dstrAccountNum, dstrShrNum, dstrEntityName, dstrContribYear, dstrRcptNum, strBrowserTitle, dstrPlanType;
        E_COMMANDRETURN eRtn = CMD_OK;
        CString PDFViewer;

        GetTitleDetails(dstrShrNum, dstrAccountNum, dstrEntityName);
        getParent()->getField(this, IFASTBP_PROC::RSP_CONTRIBUTION_LIST, ifds::ContribYear, dstrContribYear, false);
        getParent()->getField(this, IFASTBP_PROC::RSP_RECEIPTS_LIST    , ifds::RcptNum,  dstrRcptNum, false);
		getParent()->getField( this, IFASTBP_PROC::ACCOUNT, ifds::PlanType, dstrPlanType, false );

        addIDITagValue(urlParamsIDI, I_("AccountNum"), dstrAccountNum);
        addIDITagValue(urlParamsIDI, I_("year"),       dstrContribYear);
        addIDITagValue(urlParamsIDI, I_("rcpNum"),     dstrRcptNum);
		if(dstrPlanType == I_("RSP"))
			addIDITagValue(urlParamsIDI, I_("pdfType"),    I_("ContribRcptRSP"));
		else if(dstrPlanType == I_("RIF"))
			addIDITagValue(urlParamsIDI, I_("pdfType"),    I_("ContribRcptRIF"));
		else
			addIDITagValue(urlParamsIDI, I_("pdfType"),    I_("ContribRcpt"));
		addIDITagValue(urlParamsIDI, I_("screen"),     I_("PDFViewer"));

        PDFViewer.LoadString(TXT_PDF_VIEWER);
        strBrowserTitle = PDFViewer + I_(": ") + 
                          GetCaptionShareNumTxt() + I_(" ") + dstrShrNum + I_("; ") + 
                          GetCaptionAcctNumTxt() + I_(" ") + dstrAccountNum + I_("; ") + 
                          dstrEntityName;

        setParameter(I_("UrlParams"), urlParamsIDI);
        setParameter(I_("BrowserTitle"), strBrowserTitle);
        setParameter(I_("from_screen"),  I_("YTDContributionDlg"));

        eRtn = invokeCommand (getParent(), CMD_BPROC_PDF_VIEWER, PROC_NO_TYPE, false, NULL);
        SetMessageStatusBar(NULL_STRING);

        switch( eRtn )
        {
        case CMD_OK:
        case CMD_CANCEL:
        case CMD_MODELESS_INPROCESS:
            break;
        default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
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
// Dialog Button method for OnBtnMore.  This button is enable if there are more
// than 25 RSP Receipts found in the database for the current 
//******************************************************************************
void YTDContributionDlg::OnBtnMore( )
{

   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel;

   // Get the key for the current list item selected in the RSP Receipts List
   cursel = GetList( IDC_RSP_RECEIPTS_LIST )->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);  
   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::RSP_RECEIPTS_LIST );

   SetMessageStatusBar( TXT_LOAD_RECEIPTS );
   if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      //reload the list control for RSP Receipts.
      LoadListControl( IDC_RSP_RECEIPTS_LIST );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_RSP_RECEIPTS_LIST )->SetSelection( crtKey );
      }
   }

   // Enable/Disable More button 
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );

   // Reset the current list item selected in the RSP Receipts List after the new records
   // have been inserted.
   GetList( IDC_RSP_RECEIPTS_LIST )->SetSelection(cursel, true, true);

   SetMessageStatusBar(NULL_STRING);   
}

//******************************************************************************
// Method to Show/Hide spousal information
// @param   bool bFlag - True to show spousal info, false otherwise
//******************************************************************************
void YTDContributionDlg::ShowSpousal( bool bFlag )
{
   GetDlgItem(IDC_SPOUSAL_NAME)->ShowWindow ( bFlag );
   GetDlgItem(IDC_SPOUSAL_SIN)->ShowWindow ( bFlag );
   GetDlgItem(IDC_STATIC_SPOUSAL_NAME)->ShowWindow ( bFlag );
   GetDlgItem(IDC_STATIC_SPOUSAL_SIN)->ShowWindow ( bFlag );
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool YTDContributionDlg::doRefresh( GenericInterface * rpGICaller, 
                                    const I_CHAR * szOriginalCommand )
{
   DString  dstrAccountNum, dstrShrNum, dstrEntityName( NULL_STRING );
   getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum );
   getGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum );
   if( !dstrAccountNum.empty() )
   {
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), dstrAccountNum, dstrEntityName);
   }
   SetShrAcctCaption( dstrShrNum, dstrAccountNum, dstrEntityName);
   //reload list control
//   AssociateControls();
   LoadListControl( IDC_RSP_CONTRIBUTION_LIST );

   return(true);
}

//******************************************************************************
bool YTDContributionDlg::GetDataForControl(UINT controlID, DString &dstrValueOut, 
                                           bool bFormatted, int index) const
{
   bool bReturn = true;

   switch( controlID )
   {
      
      case IDC_TAX_ADDR1:
         {
            DString dstrAddr;
            getParent()->getField(this, IFASTBP_PROC::RSP_RECEIPTS_LIST, ifds::Address1, dstrAddr);
            if( dstrAddr.strip() != NULL_STRING )
            {
               dstrValueOut = dstrAddr.strip();
            }

            getParent()->getField(this, IFASTBP_PROC::RSP_RECEIPTS_LIST, ifds::Address2, dstrAddr);
            if( dstrAddr.strip() != NULL_STRING )
            {
               dstrValueOut = dstrValueOut + I_("\r\n") + dstrAddr.strip();
            }
            getParent()->getField(this, IFASTBP_PROC::RSP_RECEIPTS_LIST, ifds::Address3, dstrAddr);
            if( dstrAddr.strip() != NULL_STRING )
            {
               dstrValueOut = dstrValueOut + I_("\r\n") + dstrAddr.strip();
            }
            getParent()->getField(this, IFASTBP_PROC::RSP_RECEIPTS_LIST, ifds::Address4, dstrAddr);
            if( dstrAddr.strip() != NULL_STRING )
            {
               dstrValueOut = dstrValueOut + I_("\r\n") + dstrAddr.strip();
            }
            getParent()->getField(this, IFASTBP_PROC::RSP_RECEIPTS_LIST, ifds::Address5, dstrAddr);
            if( dstrAddr.strip() != NULL_STRING )
            {
               dstrValueOut = dstrValueOut + I_("\r\n") + dstrAddr.strip();
            }

            CString strAddr;
            strAddr = dstrValueOut.c_str();
            strAddr.TrimRight(_T("\r\n"));
            dstrValueOut = (LPCTSTR)strAddr;

            getParent()->getField(this, IFASTBP_PROC::RSP_RECEIPTS_LIST, ifds::PostalCode, dstrAddr);
            dstrValueOut = dstrValueOut + I_("\r\n") + dstrAddr.strip();
            break;
         }

      default:
         bReturn = false;
         break;
   }
   return(bReturn);
}
//****************************************************************************************
CString YTDContributionDlg::constructOption( const BFFieldId &idField,UINT resID )
{
   CString cstrOption;
   DString dstrValue;
   getParent()->getField(this,IFASTBP_PROC::ACCOUNT_MAILING_LIST,
                        idField,dstrValue,false );
   dstrValue.strip().upperCase();
   if( dstrValue == YES )
   {
      cstrOption.LoadString( resID );   
   }
   return cstrOption;
}

//*********************************************************
void YTDContributionDlg::DisplayDeliveryOption()
{
   
   CString cstrDisp;
   cstrDisp = constructOption( ifds::ContributionMail,IDS_MAIL );
   cstrDisp += COMMA;
   cstrDisp += constructOption( ifds::ContributionFax,IDS_FAX );
   cstrDisp += COMMA;
   cstrDisp += constructOption( ifds::ContributionCD,IDS_CD );
   cstrDisp += COMMA;
   cstrDisp += constructOption( ifds::ContributionEmail,IDS_EMAIL );
   cstrDisp += COMMA;
   cstrDisp += constructOption( ifds::ContributionEpost,IDS_EPOST );
   cstrDisp.TrimRight(COMMA);
   GetDlgItem( IDC_TXT_DELIVERY )->SetWindowText(cstrDisp );
}

//**********************************************************************************

void YTDContributionDlg::OnBtnAdminDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::RSP_RECEIPTS_LIST );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/YTDContributionDlg.cpp-arc  $
// 
//    Rev 1.12   22 Jul 2008 13:52:50   kovacsro
// PET5517FN60C - added Admin/Dates
// 
//    Rev 1.11   Sep 15 2005 15:16:20   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.10   Dec 02 2004 11:38:58   yingbaol
// PET1137,FN01: add Epost functionalities
// 
//    Rev 1.9   May 26 2004 15:23:42   VADEANUM
// PTS 10028913 - Correct redirection to iFast.
// 
//    Rev 1.8   Mar 21 2003 18:42:26   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:56:18   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   22 May 2002 19:16:36   PURDYECH
// BFData Implementation
// 
//    Rev 1.5   27 Mar 2002 20:01:34   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.4   Jan 28 2002 11:28:16   YINGBAOL
// HLLAPI Change
// 
//    Rev 1.3   Nov 21 2001 16:42:22   ZHANGCEL
// Minor change
// 
//    Rev 1.2   Nov 20 2001 16:20:58   ZHANGCEL
// Many changes for getting Address from  view174
// 
//    Rev 1.1   20 Aug 2001 14:53:46   HSUCHIN
// added comments
// 
//    Rev 1.0   18 Aug 2001 09:29:42   HSUCHIN
// Initial revision.
 */


