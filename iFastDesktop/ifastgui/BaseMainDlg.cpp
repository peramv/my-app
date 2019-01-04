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
// ^FILE   : BaseMainDlg.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 12/98
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BaseMainDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  : This base dialog class adds additional functionality for
//                     main modal and modeless dialogs.
//
//******************************************************************************

#include "stdafx.h"
#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif
#ifndef BASEMAINDLG_H
   #include "BaseMainDlg.h"
#endif
#ifndef BFUSERSESSION_HPP
   #include <bfcbo\BFUserSession.hpp>
#endif
#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif
#ifndef CONDITIONMESSAGEDIALOG_H
   #include <uibase\ConditionMessageDialog.h>
#endif
#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif
#ifndef GENERICINTERFACECONTAINER_HPP
   #include <bfproc\GenericInterfaceContainer.hpp>
#endif
#ifndef IDISTRING_HPP
   #include <IDIString.hpp>
#endif
#ifndef USERSESSIONPROCESSINCLUDES_H
   #include <ifastbp\UserSessionProcessIncludes.h>
#endif
#ifndef WINDOWMANAGER_HPP
   #include <uibase\WindowManager.hpp>
#endif

#ifndef DISCARDMSGDLG_H
   #include "DiscardMsgDlg.h"
#endif

#ifndef _CSISESSION_H__INCLUDED_
   #include <ifastcsi\CsiSession.h>
#endif

#ifndef DSTCGLOBALSESSION_HPP__INCLUDED
   #include <ifastcbo\DSTCGlobalSession.hpp>
#endif

#ifndef DSTCUSERSESSION_HPP__INCLUDED
   #include <ifastcbo\dstcusersession.hpp>
#endif

#ifndef MGMTCO_HPP__INCLUDED
   #include <ifastcbo\MgmtCo.hpp>
#endif

#ifndef MGMTCOOPTIONS_HPP__INCLUDED
   #include <ifastcbo\MgmtCoOptions.hpp>
#endif

#ifndef _DSTCCSI_H__INCLUDED_
   #include <ifastcsi\ifastcsi.h>
#endif

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADMINDATES;

CRect BaseMainDlg::DetailDlgRect=CRect(-1,-1,-1,-1);

namespace
{
   // Tracing literals
   const I_CHAR * const CLASSNAME      = I_( "BaseMainDlg" );
   const I_CHAR * const SHOWADMINDATES = I_( "ShowAdminDates" );

   // used for ShowAdminDates
   const I_CHAR * const MODUSER        = I_( "ModUser" );
   const I_CHAR * const MODDATE        = I_( "ModDate" );
   const I_CHAR * const USERNAME       = I_( "Username" );
   const I_CHAR * const PROCESSDATE    = I_( "ProcessDate" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFTextFieldId Username;
   extern CLASS_IMPORT const BFTextFieldId ClientName;
   extern CLASS_IMPORT const BFTextFieldId CompanyCode;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

BaseMainDlg::BaseMainDlg(
                        UINT IDD,
                        CWnd* rpParent,
                        GenericInterfaceContainer* pGIC,
                        GenericInterface* pGIParent,
                        const Command& rCommand,
                        const DString &dialogName
                        )
: AbstractBaseMainDlg( IDD, rpParent, pGIC, pGIParent, rCommand, dialogName )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

BaseMainDlg::~BaseMainDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

BEGIN_MESSAGE_MAP(BaseMainDlg, BaseDlg)
//{{AFX_MSG_MAP(BaseMainDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************

CString BaseMainDlg::GetCaptionAcctNumTxt()
{
   CString acctNum;

   acctNum.LoadString(IDS_TXT_ACCT_NUM);
   return(acctNum);
}

//******************************************************************************

CString BaseMainDlg::GetCaptionFundTxt()
{
   CString fund;

   fund.LoadString( TXT_FUND );
   return(fund);
}

//******************************************************************************

CString BaseMainDlg::GetCaptionShareNumTxt()
{
   CString shrNum;

   shrNum.LoadString(IDS_TXT_SHR_NUM);
   return(shrNum);
}

//******************************************************************************

void BaseMainDlg::ShowAdminDates(
                                const BFContainerId& idContainer
                                )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, SHOWADMINDATES );
   CWaitCursor wait;
   DString str;
   GenericInterface* rpParent = getParent();

   rpParent->getField( this, idContainer, ifds::ModUser, str );
   setParameter( MODUSER, str );

   rpParent->getField( this, idContainer, ifds::ModDate, str );
   setParameter( MODDATE, str );

   rpParent->getField( this, idContainer, ifds::ProcessDate, str );
   setParameter( PROCESSDATE, str );

   rpParent->getField( this, idContainer, ifds::Username, str );
   setParameter( USERNAME, str );
   try
   {
      E_COMMANDRETURN eRtn;
      SetMessageStatusBar( TXT_LOAD_ADMIN_DATES );
      eRtn = invokeCommand( rpParent, CMD_BPROC_ADMINDATES, PROC_NO_TYPE,
                            true /*modal*/, NULL );
      SetMessageStatusBar( NULL_STRING );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
            break;
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
//              Message Handlers
//******************************************************************************

BOOL BaseMainDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
//   unsigned array[ INDICATOR_COUNT ] =
//      { GUI_STATUSBAR_1, GUI_STATUSBAR_2, GUI_STATUSBAR_3, GUI_STATUSBAR_4 };
   DString hold;
   CString caption;

   AbstractBaseMainDlg::OnInitDialog();

   //looking in the generic interface container for the user session process;
   GenericInterface* pWorkSessionProcess = NULL;
   GenericInterface* rpGIUserSession = NULL;

   pWorkSessionProcess = getWorkSession();
   if( pWorkSessionProcess )
      rpGIUserSession = getGIContainer()->findGI( &pWorkSessionProcess->getBFSession()->getUserSession(), CMD_BPROC_USER_SESSION );
   else
      rpGIUserSession = getGIContainer()->findGI( getBFSession(), CMD_BPROC_USER_SESSION );

   // TODO - this probably should be done via getGlobal/setGlobal - don't need to get
   // user session that way.
   if( rpGIUserSession )
   {
      DString userID;
      DString awdProfile;
      DString mgmtCoName;
      DString clientName;
      DString companyID;

      rpGIUserSession->getField( this, USERID, userID );
      rpGIUserSession->getField( this, AWDPROFILE, awdProfile );
      rpGIUserSession->getField( this, MGMTCONAME, mgmtCoName );
      rpGIUserSession->getField( this, CLIENTNAME, clientName );
      rpGIUserSession->getField( this, SYSTMGMTS, companyID );

      DSTCUserSession* pUserSession = dynamic_cast<DSTCUserSession*>(rpGIUserSession->getBFSession());
      DString dstrCompanyCode = NULL_STRING;
      if( pUserSession != NULL )
      {
         DSTCGlobalSession& gs = dynamic_cast<DSTCGlobalSession&>(pUserSession->getGlobalSession());
         MgmtCo* pMgmtCo = NULL;
         MgmtCoOptions* pOptions = NULL;
         gs.findMgmtCo( companyID, pMgmtCo );

         if(pMgmtCo && pMgmtCo->getMgmtCoOptions(pOptions) <= WARNING && 
            pOptions){
               pOptions->getField( ifds::CompanyCode, dstrCompanyCode, BF::HOST, false );
         }
         dstrCompanyCode.stripAll ().upperCase ();
      }

      m_statusBar.SetProfileStatusBar( awdProfile.c_str() );
      m_statusBar.SetManagementCodeStatusBar( mgmtCoName.c_str() );
      m_statusBar.SetSystemStatusBar( userID.c_str() );
      m_statusBar.SetCompanyCodeStatusBar( dstrCompanyCode.c_str() );
      m_statusBar.SetClientNameStatusBar( clientName.c_str() );
   }
   else
   {
      m_statusBar.SetMessageStatusBar( NULL_STRING );
      m_statusBar.SetProfileStatusBar( NULL_STRING );
      m_statusBar.SetManagementCodeStatusBar( NULL_STRING );
      m_statusBar.SetSystemStatusBar( NULL_STRING );
      m_statusBar.SetCompanyCodeStatusBar( NULL_STRING );
      m_statusBar.SetClientNameStatusBar( NULL_STRING );
   }

   GetWindowText( caption );
   SetBaseCaption( caption );
   InitResizing ();
   
   // TODO - Find another way to do this.  BaseMainDlg should not be dependent
   // on any specific dialog ID's or dialogs
   // TODO - Find another way to do this.  BaseMainDlg should not be dependent
   // on any specific dialog ID's or dialogs
   UINT dlgID = GetIDD();
   if ( dlgID != IDD_LOGON && 
        dlgID != IDD_SYSTMGMT && 
        dlgID != IDD_FIRE_FIGHTER_LOGON &&
        dlgID != IDD_PROGRESS_DLG)
   {
// if details screen is not yet open, move window to GUIPOS_DESKTOPBOTTOM
      if( DetailDlgRect.left == -1 && DetailDlgRect.top == -1 && 
          DetailDlgRect.right == -1 && DetailDlgRect.bottom == -1 )
      {
         MoveDialog( GUIPOS_DESKTOPBOTTOM, 0 ); 
      }
      else
      {
         CDC *pDC = GetDC();
         long w=pDC->GetDeviceCaps(HORZRES);
         long h=pDC->GetDeviceCaps(VERTRES);

         if( DetailDlgRect.right > w || DetailDlgRect.bottom > h 
             || DetailDlgRect.left < 0 )
            MoveDialog( GUIPOS_DESKTOPBOTTOM, 0 );
         else
         {
            CRect r;
            WINDOWPLACEMENT tmp;
            GetWindowPlacement( &tmp );
            r=tmp.rcNormalPosition;

            w = r.right-r.left;
            h = r.bottom-r.top;

            r.right = DetailDlgRect.right;
            r.left = r.right-w;
            r.bottom = DetailDlgRect.bottom;
            r.top = r.bottom-h;

            MoveWindow( r );
         }
      }
   }

   //Aug 3, 1999
   CFont *pFont = ((MFDSTCApp*)(AfxGetApp()))->GetNewFont();
   if( pFont )
   {
      CWnd* pwndChild = GetWindow(GW_CHILD);
      while( pwndChild )
      {
         pwndChild->SetFont(pFont);
         pwndChild = pwndChild->GetNextWindow();
      }
   }

   ::SetClassLong( m_hWnd, GCL_HICON, (long)::getUserIcon() );

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
//              Private methods
//******************************************************************************

//DDX Function Overrides to support Multiple Markets and Locale.

void BaseMainDlg::DDX_CBIndex(CDataExchange* pDX, int nIDC, int& index)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_CBIndex(pDX,nIDC,index);
}

void BaseMainDlg::DDX_CBString(CDataExchange* pDX, int nIDC, CString& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_CBString(pDX,nIDC,value);
}

void BaseMainDlg::DDX_CBStringExact(CDataExchange* pDX, int nIDC, CString& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_CBStringExact(pDX,nIDC,value);
}

void BaseMainDlg::DDX_Check(CDataExchange* pDX, int nIDC, int& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Check(pDX,nIDC,value);
}

void BaseMainDlg::DDX_Control(CDataExchange* pDX, int nIDC, CWnd& rControl)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Control(pDX,nIDC,rControl);
}


void BaseMainDlg::DDX_DateTimeCtrl(CDataExchange* pDX, int nIDC, CTime& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_DateTimeCtrl(pDX, nIDC, value);
}

void BaseMainDlg::DDX_DateTimeCtrl(CDataExchange* pDX, int nIDC, COleDateTime& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_DateTimeCtrl(pDX, nIDC, value);
}

void BaseMainDlg::DDX_LBIndex(CDataExchange* pDX, int nIDC, int& index)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_LBIndex(pDX, nIDC, index);
}

void BaseMainDlg::DDX_LBString(CDataExchange* pDX, int nIDC, CString& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_LBString(pDX, nIDC, value);
}

void BaseMainDlg::DDX_LBStringExact(CDataExchange* pDX, int nIDC, CString& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_LBStringExact(pDX, nIDC, value);
}

void BaseMainDlg::DDX_MonthCalCtrl(CDataExchange* pDX, int nIDC, CTime& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_MonthCalCtrl(pDX, nIDC, value);
}

void BaseMainDlg::DDX_MonthCalCtrl(CDataExchange* pDX, int nIDC, COleDateTime& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_MonthCalCtrl(pDX, nIDC, value);
}

void BaseMainDlg::DDX_OCBool(CDataExchange* pDX, int nIDC, DISPID& dispid, BOOL& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCBool(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCBoolRO(CDataExchange* pDX, int nIDC, DISPID& dispid, BOOL& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCBoolRO(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCColor(CDataExchange* pDX, int nIDC, DISPID& dispid, OLE_COLOR& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCColor(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCColorRO(CDataExchange* pDX, int nIDC, DISPID& dispid, OLE_COLOR& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCColorRO(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCFloat(CDataExchange* pDX, int nIDC, DISPID& dispid, float& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCFloat(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCFloat(CDataExchange* pDX, int nIDC, DISPID& dispid, double& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCFloat(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCFloatRO(CDataExchange* pDX, int nIDC, DISPID& dispid, float& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCFloatRO(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCFloatRO(CDataExchange* pDX, int nIDC, DISPID& dispid, double& value)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCFloatRO(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCInt( CDataExchange* pDX, int nIDC, DISPID dispid, int& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCInt(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCInt( CDataExchange* pDX, int nIDC, DISPID dispid, long& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCInt(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCIntRO( CDataExchange* pDX, int nIDC, DISPID dispid, int& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCIntRO(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCIntRO( CDataExchange* pDX, int nIDC, DISPID dispid, long& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCIntRO(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCShort( CDataExchange* pDX, int nIDC, DISPID dispid, short& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCShort(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCShortRO( CDataExchange* pDX, int nIDC, DISPID dispid, short& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCShortRO(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCText( CDataExchange* pDX, int nIDC, DISPID dispid, CString& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCText(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_OCTextRO( CDataExchange* pDX, int nIDC, DISPID dispid, CString& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_OCTextRO(pDX, nIDC, dispid, value);
}

void BaseMainDlg::DDX_Radio( CDataExchange* pDX, int nIDC, int& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Radio(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Scroll( CDataExchange* pDX, int nIDC, int& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Scroll(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Slider( CDataExchange* pDX, int nIDC, int& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Slider(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Text( CDataExchange* pDX, int nIDC, BYTE& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Text(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Text( CDataExchange* pDX, int nIDC, short& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Text(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Text( CDataExchange* pDX, int nIDC, int& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Text(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Text( CDataExchange* pDX, int nIDC, UINT& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Text(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Text( CDataExchange* pDX, int nIDC, long& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Text(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Text( CDataExchange* pDX, int nIDC, DWORD& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Text(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Text( CDataExchange* pDX, int nIDC, CString& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Text(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Text( CDataExchange* pDX, int nIDC, float& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Text(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Text( CDataExchange* pDX, int nIDC, double& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Text(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Text( CDataExchange* pDX, int nIDC, COleCurrency& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Text(pDX, nIDC, value);
}

void BaseMainDlg::DDX_Text( CDataExchange* pDX, int nIDC, COleDateTime& value )
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      ::DDX_Text(pDX, nIDC, value);
}

//End of DDX Function Overrides

//DDV Function Overrides to support Multiple Markets and Locale.

void BaseMainDlg::DDV_MaxChars( CDataExchange* pDX, CString const& value, int nChars )
{
   if( pDX != NULL )
      ::DDV_MaxChars(pDX, value, nChars);
}

void BaseMainDlg::DDV_MinMaxByte( CDataExchange* pDX, BYTE value, BYTE minVal, BYTE maxVal )
{
   if( pDX != NULL )
      ::DDV_MinMaxByte(pDX, value, minVal, maxVal);
}

void BaseMainDlg::DDV_MinMaxDateTime( CDataExchange* pDX, CTime& refValue, const CTime* refMinRange, const CTime* refMaxRange )
{
   if( pDX != NULL )
      ::DDV_MinMaxDateTime(pDX, refValue, refMinRange, refMaxRange);
}

void BaseMainDlg::DDV_MinMaxDateTime( CDataExchange* pDX, COleDateTime& refValue, const COleDateTime* refMinRange, const COleDateTime* refMaxRange )
{
   if( pDX != NULL )
      ::DDV_MinMaxDateTime(pDX, refValue, refMinRange, refMaxRange);
}

void BaseMainDlg::DDV_MinMaxDouble( CDataExchange* pDX, double const& value, double minVal, double maxVal )
{
   if( pDX != NULL )
      ::DDV_MinMaxDouble(pDX, value, minVal, maxVal);
}

void BaseMainDlg::DDV_MinMaxDWord( CDataExchange* pDX, DWORD const& value, DWORD minVal, DWORD maxVal )
{
   if( pDX != NULL )
      ::DDV_MinMaxDWord(pDX, value, minVal, maxVal);
}

void BaseMainDlg::DDV_MinMaxFloat( CDataExchange* pDX, float value, float minVal, float maxVal )
{
   if( pDX != NULL )
      ::DDV_MinMaxFloat(pDX, value, minVal, maxVal);
}

void BaseMainDlg::DDV_MinMaxInt( CDataExchange* pDX, int value, int minVal, int maxVal )
{
   if( pDX != NULL )
      ::DDV_MinMaxInt(pDX, value, minVal, maxVal);
}

void BaseMainDlg::DDV_MinMaxLong( CDataExchange* pDX, long value, long minVal, long maxVal )
{
   if( pDX != NULL )
      ::DDV_MinMaxLong(pDX, value, minVal, maxVal);
}

void BaseMainDlg::DDV_MinMaxMonth( CDataExchange* pDX, CTime& refValue, const CTime* refMinRange, const CTime* refMaxRange )
{
   if( pDX != NULL )
      ::DDV_MinMaxMonth(pDX, refValue, refMinRange, refMaxRange);
}

void BaseMainDlg::DDV_MinMaxMonth( CDataExchange* pDX, COleDateTime& refValue, const COleDateTime* refMinRange, const COleDateTime* refMaxRange )
{
   if( pDX != NULL )
      ::DDV_MinMaxMonth(pDX, refValue, refMinRange, refMaxRange);
}

void BaseMainDlg::DDV_MinMaxSlider( CDataExchange* pDX, DWORD value, DWORD minVal, DWORD maxVal )
{
   if( pDX != NULL )
      ::DDV_MinMaxSlider(pDX, value, minVal, maxVal);
}

bool BaseMainDlg::canCancel()
{
   if( getUpdateFlag() )
   {
      DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_MSGA, TXT_DISCARD_MSGB, TXT_DISCARD);

      return(discardDlg.DoModal() != IDCANCEL);         
   }

   return(true);
}


//******************************************************************************
void BaseMainDlg::setCsiParameter(const DStringA& strName, const DStringA& strValue)
{
   CsiSession& csiSession = CsiSession::getInstance();
   csiSession.setParameter( strName.getImp(),  strValue.getImp());
}
//******************************************************************************
void BaseMainDlg::executeCsiProcess(const DStringA& strProcessName )
{
   CWaitCursor wait;
   SetMessageStatusBar( TXT_LOAD_HLLAPI );
   CsiSession& csiSession = CsiSession::getInstance();
   csiSession.executeProcess ( strProcessName.getImp() );  
   csiSession.clearParameters();
   SetMessageStatusBar( NULL_STRING);
}



/*
void BaseMainDlg::DDV_MinMaxUnsigned( CDataExchange* pDX, unsigned value, unsigned minVal, unsigned maxVal )
{
  if (pDX != NULL)
      ::DDV_MinMaxUnsigned(pDX, value, minVal, maxVal);
}
*/
//End of DDV Function Overrides

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BaseMainDlg.cpp-arc  $
 * 
 *    Rev 1.26   Dec 22 2009 06:23:54   dchatcha
 * IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
 * 
 *    Rev 1.25   Feb 06 2009 14:55:36   purdyech
 * Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
 * 
 *    Rev 1.24   18 Jul 2008 13:52:40   popescu
 * Incident 1190617 - excluded the progress ctrl dialog from the movedialog call
 * 
 *    Rev 1.23   Sep 19 2005 17:42:04   ZHANGCEL
 * PET1235 FN02 -- Restricted Readonly dialog should be displayed on te middle of  screen.
 * 
 *    Rev 1.22   Sep 15 2005 12:57:50   popescu
 * Incident # 403519 - saved/restored the size of the dialog in the registry
 * 
 *    Rev 1.21   Jan 10 2005 11:08:54   hernando
 * PET1189 FN1 - Dual-Monitor changes.
 * 
 *    Rev 1.20   Dec 24 2004 11:59:04   purdyech
 * PTS1031333 - getUserIcon() function is now a global function which happens to reside in MFDSTC.cpp, instead of a member of MFDSTCApp
 * 
 *    Rev 1.19   Dec 22 2004 16:58:14   zhangcel
 * PTS 10031333 -- Change logic to get icon base on the Market
 * 
 *    Rev 1.18   Mar 21 2003 18:33:30   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Mar 05 2003 11:26:34   PURDYECH
 * Added indirectInvokeCommand method.  This method allows outside callers to use the protected invokeCommand method.
 * 
 *    Rev 1.16   Oct 09 2002 23:55:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 12:57:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   22 May 2002 19:15:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.13   27 Mar 2002 20:00:58   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.12   Feb 11 2002 17:20:30   HERNANDO
 * Changed DiscardMsgDlg call.
 * 
 *    Rev 1.11   Jan 28 2002 11:27:22   YINGBAOL
 * HLLAPI Change
 * 
 *    Rev 1.10   Aug 09 2001 15:44:20   HUANGSHA
 * remove the hardcoded string
 * 
 *    Rev 1.9   04 Jul 2001 16:45:52   YINGZ
 * implement cancel to give user warning when there are updates
 * 
 *    Rev 1.8   29 Jun 2001 10:57:08   YINGZ
 * add canCancel to support cancel machenism
 * 
 *    Rev 1.7   08 Jun 2001 11:22:44   KOVACSRO
 * More changes for getting user session process.
 * 
 *    Rev 1.6   07 Jun 2001 14:29:22   KOVACSRO
 * Changed the way of getting UserSession.
 * 
 *    Rev 1.5   May 11 2000 11:48:42   HUANGSHA
 * Added LoadIcon
 * 
 *    Rev 1.4   Apr 07 2000 09:41:10   DT24433
 * removed userID parm to findGI
 * 
 *    Rev 1.3   Apr 04 2000 14:45:08   DT24433
 * changes for GIC userid change
 * 
 *    Rev 1.2   Mar 02 2000 11:13:40   DT24433
 * changes for new base class
 * 
 *    Rev 1.1   Feb 28 2000 16:53:06   DT24433
 * removed Ok/Cancel and unused active window code
 * 
 *    Rev 1.0   Feb 15 2000 11:01:08   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.38   Feb 02 2000 17:44:46   YINGZ
 * position dlg when detail dlg move out the screen
 * 
 *    Rev 1.37   Jan 28 2000 18:11:04   DT24433
 * use CancelInProgress flag during ok when ending dialog as well
 * 
 *    Rev 1.36   Jan 26 2000 19:40:08   DT24433
 * detect transaction error and avoid further processing
 * 
 *    Rev 1.35   Jan 25 2000 14:23:48   DT24433
 * changed onok to always go beyond ProcessControls no matter what it returns to allow better clean up of dummy entries
 * 
 *    Rev 1.34   Jan 25 2000 11:42:08   POPESCUS
 * fix for the crash in systematics
 * 
 *    Rev 1.33   Jan 13 2000 17:12:02   DT24433
 * changes for global error handling in OnOk
 * 
 *    Rev 1.32   Jan 11 2000 17:39:26   DT24433
 * initiate CancelInProgress
 * 
 *    Rev 1.31   Jan 04 2000 10:05:32   YINGZ
 * remove #ifdef _DEBUG around OnOK condition box
 * 
 *    Rev 1.30   Dec 24 1999 14:57:56   YINGZ
 * make ok condition conditional
 * 
 *    Rev 1.29   Dec 20 1999 10:32:22   YINGZ
 * add semicolumn to SetShrAcctCaption
 * 
 *    Rev 1.28   Dec 17 1999 15:53:40   DT24433
 * SetFocus on screen for OnOk failure
 * 
 *    Rev 1.27   Dec 09 1999 19:18:04   DT24433
 * added ShowAdminDates
 * 
 *    Rev 1.26   Dec 07 1999 09:53:00   YINGZ
 * make new caption compatiblw with the old one
 * 
 *    Rev 1.25   Dec 06 1999 16:54:34   YINGZ
 * add SetShrAcctCaption for new style caption
 * 
 *    Rev 1.24   Nov 19 1999 15:57:56   DT24433
 * fixed ok processing to work with current conditions
 * 
 *    Rev 1.23   Nov 15 1999 15:15:18   DT24433
 * only display messages if exist in OnOK failure
 * 
 *    Rev 1.22   Nov 12 1999 17:20:28   DT24433
 * implemented OnCancel processing
 * 
 *    Rev 1.21   Nov 09 1999 16:54:24   VASILEAD
 * Fixed OnCancel()
 * 
 *    Rev 1.20   Nov 04 1999 13:28:20   DT24433
 * added OnOk/OnCancel processing
 * 
 *    Rev 1.19   Nov 02 1999 14:41:42   DT24433
 * added return after Exit call in OnOk
 * 
 *    Rev 1.18   Oct 18 1999 16:43:56   DT24433
 * initial changes for OnOk to work with control container
 * 
 *    Rev 1.17   Aug 25 1999 14:22:46   HSUCHIN
 * Override DDX and DDV calls from Dialog classes.  The DDX, DDV functions now checks to see if the control exist before performing the data exchange.
 * 
 *    Rev 1.16   Aug 24 1999 14:54:44   DT24433
 * misc. cleanup
 * 
 *    Rev 1.15   Aug 24 1999 14:57:08   VASILEAD
 * For now we are setting all modeless dialogs as belonging to our main frame window.
 * 
 *    Rev 1.14   Aug 18 1999 11:04:18   VASILEAD
 * Grouped the status bar for all dialogs
 * 
 *    Rev 1.13   Aug 16 1999 11:15:42   YINGZ
 * name order
 * 
 *    Rev 1.12   Aug 16 1999 09:10:14   YINGZ
 * name display order
 * 
 *    Rev 1.11   Aug 13 1999 17:27:24   YINGZ
 * change the way the name is displayed
 * 
 *    Rev 1.10   04 Aug 1999 11:16:40   HUANGSHA
 * Same as MFDSTC.h
 * 
 *    Rev 1.9   Aug 03 1999 17:10:02   BUZILA
 * added savePosition and loadPosition methods
 * 
 *    Rev 1.8   Jul 30 1999 13:19:16   YINGZ
 * alignment
 * 
 *    Rev 1.7   Jul 28 1999 16:10:24   YINGZ
 * ?
 * 
 *    Rev 1.6   Jul 28 1999 11:45:08   YINGZ
 * alignment again
 * 
 *    Rev 1.5   Jul 28 1999 10:41:58   YINGZ
 * allow cascade for all dlg
 * 
 *    Rev 1.4   Jul 20 1999 11:18:22   VASILEAD
 * New conditions update
 * 
 *    Rev 1.3   Jul 09 1999 16:55:48   YINGZ
 * change listview support to use Jerry's fix
 * 
 *    Rev 1.2   Jul 09 1999 16:48:36   YINGZ
 * change listview support to use Jerry's fix
 * 
 *    Rev 1.1   Jul 08 1999 10:04:40   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
