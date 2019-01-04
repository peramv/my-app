//#include "D:\ifds\ifast\rel\ifastgui\BrowsweLaunch.h"
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
// ^FILE   : BrowserLaunch.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 5-06
//
// ----------------------------------------------------------
//
// ^CLASS    : BrowserLaunch
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the FYI dialog which contains a
//           webbrowser control that displays HTML documents.  It requires
//           Internet Explorer 3.02 to work properly.
//******************************************************************************

#include "stdafx.h"
#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef BrowserLaunch_H
   #include "BrowserLaunch.h"
#endif

#ifndef HTMLTAGSNATTRIBUTES_H
   #include "HtmlTagsNAttributes.h"
#endif

#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif

#ifndef CONFIGURATIONCONSTANTS_H
   #include "ConfigurationConstants.h"
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef DSTCUSERSESSION_HPP
   #include <ifastcbo\dstcusersession.hpp>
#endif
#include <ifastcbo\mgmtco.hpp>

#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\commanddispatcher.hpp>

#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>
#include <ifastdbrkr\dstchost.hpp>
#include <ifastbp\usersessionprocessincludes.h>
#include <ifastbp\browserlaunchprocess.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <bf/log/log.hpp>
#include <bfdbrkr/DbrkrLogger.hpp>
#include <uibase/DlgResizeHelper.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_BROWSER_LAUNCH;

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROWSER_LAUNCH;

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CONFIRMATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_PAYMENTS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_GOVT_FILING_AMENDMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SMART_FORM;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PORTFOLIO_SETUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_GLOBAL_SEARCH;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_SHARE_LOT_BROWSER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACC_DETAILS;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< BrowserLaunch > dlgCreator( CMD_GUI_BROWSER_LAUNCH );
#include ".\GuiConfig.h"
#include <comutil.h>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define HTM_TEXT_EMPTY              _T("")

#define HTMTAG_OPTION               L"OPTION"
#define HTMTAG_SELECT               L"SELECT"
#define HTMTAG_IMG                  L"IMG"
#define HTMTAG_IMAGE                L"IMAGE"
#define HTMTAG_TEXTAREA             L"TEXTAREA"
#define HTMTAG_INPUT                L"INPUT"
#define HTMATT_NAME                 L"NAME"
#define HTMTAG_BUTTON               L"BUTTON"

#define HTMITYPE_BUTTON             L"button"
#define HTMITYPE_CHECKBOX           L"checkbox"
#define HTMITYPE_HIDDEN             L"hidden"
#define HTMITYPE_IMAGE              L"image"
#define HTMITYPE_PASSWORD           L"password"
#define HTMITYPE_RADIO              L"radio"
#define HTMITYPE_RESET              L"reset"
#define HTMITYPE_SUBMIT             L"submit"
#define HTMITYPE_TEXT               L"text"
#define HTMTAG_OPT_VALUE            L"value"
#define HTMTAG_SELECTED             L"selected"

#define HTM_C_OTHER                 0
#define HTM_C_INPUT                 1
#define HTM_C_IMG                   2
#define HTM_C_IMAGE                 3
#define HTM_C_TEXTAREA              4
#define HTM_C_SELECT                5
#define HTM_C_BUTTON                6

#ifndef CONTROL_TYPE_CONSTANT
#define CONTROL_TYPE_CONSTANT
#define CNTCT_EDIT                  1
#define CNTCT_COMBO                 2
#define CNTCT_DICTCOMBO             3
#define CNTCT_RADIO                 4
#define CNTCT_CHECK                 5
#define CNTCT_DATE                  6
#define CNTCT_MULTIEDIT             7
#define CNTCT_LABEL                 8
#define CNTCT_BUTTON                9
#define CNTCT_LISTBOX               10
#define CNTCT_SCROLL                11

#define HTM_CT_BUTTON               CNTCT_BUTTON
#define HTM_CT_CHECKBOX             CNTCT_CHECK
#define HTM_CT_HIDDEN               CNTCT_EDIT
#define HTM_CT_IMAGE                CNTCT_BUTTON
#define HTM_CT_PASSWORD             CNTCT_EDIT
#define HTM_CT_RADIO                CNTCT_RADIO
#define HTM_CT_RESET                CNTCT_BUTTON
#define HTM_CT_SUBMIT               CNTCT_BUTTON
#define HTM_CT_TEXT                 CNTCT_EDIT
#define HTM_CT_SELECT               CNTCT_DICTCOMBO
#endif

namespace
{
   const I_CHAR *BI_COMPLETE      = I_( "OnDownloadComplete" );
   const I_CHAR *BI_DOWNLOAD      = I_( "OnDownloadBegin" );
   const I_CHAR *BI_ONWEBBACK     = I_( "OnWebback" );
   const I_CHAR *BI_ONWEBFWD      = I_( "OnWebfwd" );
   const I_CHAR *BI_ONWEBHOME     = I_( "OnWebhome" );
   const I_CHAR *BI_ONWEBSTOP     = I_( "OnWebstop" );
   const I_CHAR *BI_SETHOMEFOCUS  = I_( "SetHomeFocus" );
   const I_CHAR *BI_STATECHANGE   = I_( "OnCommandStateChange" );
   const I_CHAR *CLASSNAME        = I_( "BrowserLaunch" );

   gui::DStringProperty g_webPageUrl ( 'C', L"WebPages/WebPageURL", I_("") );
   gui::DStringProperty g_webCMD (     'C', L"WebPages/WebPageCmd", I_("") );
   gui::DStringProperty g_userId (     'C', L"WebPages/userid",     I_("") );
   gui::DStringProperty g_passWord (   'C', L"WebPages/password",   I_("") );
   gui::DStringProperty g_webPageName(      L"Pagename",            I_("") );
   gui::DStringProperty g_webPageCMDName(   L"CmdName",             I_("") );

   const I_CHAR * const NO                   = I_( "N" );
   const I_CHAR * const PENDING              = I_( "Pending" );
   const I_CHAR * const ALL_FUND_MODE        = I_( "AllFundMode" );
   const I_CHAR * const TRANS_ID_FIELD       = I_( "TransId" );
   const I_CHAR * const ACCOUNT_NUM          = I_( "AccountNum" );
   const I_CHAR * const TRANSNUM             = I_( "TransNum" );
   const I_CHAR * const CLASS_CODE           = I_( "ClassCode" );
   const I_CHAR * const FUND_CODE            = I_( "FundCode" );
   const I_CHAR * const REQ_TRANS_ID         = I_( "ReqTransid" );
   const I_CHAR * const TXNLEVELSEC          = I_( "TxnLevelSec" );
   const I_CHAR * const TFSA_TAX_TYPES       = I_( "V" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_DETAIL;
}

#define EXTRACT_VALUE_BY_SYMBOL(s,a,val) \
      pos = s.find (a); \
      val = s.substr (0, pos);

#define CHOP_STRING_BY_SYMBOL(s,a) \
         pos = s.find (a); \
         pos = pos != DString::npos && pos + 1 <= s.length() ? pos + 1 : DString::npos; \
         if (pos != DString::npos) \
            s = s.substr (pos); \
         else \
            s = NULL_STRING;

//******************************************************************************
// Public methods
//******************************************************************************

BrowserLaunch::BrowserLaunch( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( BrowserLaunch::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
,_pIConnectionPoint(NULL)
,_dwEventCookie(0)
,m_fromScreen( NULL_STRING )
,_blUpdatesAlreadyPerformed( false )
,_topLevelFrame(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   //{{AFX_DATA_INIT(BrowserLaunch)
   //}}AFX_DATA_INIT
   m_csFileDir = "";
   m_cRef = 0;

   CString m_strViewLogPath = DbrkrLogger::getLogDir().c_str();
   m_strFilePathForDesktopWebURL = m_strViewLogPath + "\\DesktopWebURL.txt";
}

//******************************************************************************
BrowserLaunch::~BrowserLaunch()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   EVENT_HANDLER_MAP_ITER iter = m_buttonHndMap.begin();
   while ( iter != m_buttonHndMap.end() )
   {
      delete (*iter).second;
      ++iter;
   }
   m_buttonHndMap.clear();

   if ( _pIConnectionPoint )
   {
      _pIConnectionPoint -> Unadvise(_dwEventCookie);
      _dwEventCookie = 0;
      _pIConnectionPoint -> Release();
      _pIConnectionPoint = NULL;
   }

}

//******************************************************************************
bool BrowserLaunch::updatesAlreadyPeformed()
{
   return( _blUpdatesAlreadyPerformed );
}

//******************************************************************************
void BrowserLaunch::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(BrowserLaunch)
   DDX_Control(pDX, IDC_BROWSER_LAUNCH, m_Browser_Launch);
   //DDX_Control(pDX, IDC_ANIMATION1, m_Animate);
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(BrowserLaunch, BaseMainDlg)
//{{AFX_MSG_MAP(BrowserLaunch)
ON_BN_CLICKED(IDC_WEBBACK, OnWebback)
ON_BN_CLICKED(IDC_WEBFWD, OnWebfwd)
ON_BN_CLICKED(IDC_WEBHOME, OnWebhome)
ON_BN_CLICKED(IDC_WEBSTOP, OnWebstop)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Message handlers
//******************************************************************************

BOOL BrowserLaunch::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   // Get registry datapath directory to look for files
   m_csFileDir = GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC,
                                         CONFIGURATION_CONSTANTS::DataPath,
                                         CONFIGURATION_CONSTANTS::Path ).c_str();
   m_csFileDir.TrimRight();

   SetupConnectionPoint();

   LaunchWebPage();

//   MoveDialog( GUIPOS_BOTTOM, 0 );             // Place me under my parent window

   SetWindowText( m_BrowserTitle.c_str() );
   return(TRUE);    // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void BrowserLaunch::LaunchWebPage()
{
   HRESULT hr;
   VARIANT varEmpty;
   VARIANT vPostData = {0}, vHeaders = {0};
   CString strUrl;

   GetUrl (strUrl);

   if (ConfigManager::GetSaveDesktopWebURL())
   {
		SaveDesktopWebURLToFile(strUrl);	
   }

   CString strPageUrl;
   GetPageUrl(strPageUrl);	

   buildPostParams ();
   hr = GetPostData(&vPostData);

   {
      DString::size_type pos = 0;
      DString::size_type posToken = 0;
      DString bufferCallingParam = m_parameters;
      DString workingAcctNum_;

      do
      {
         EXTRACT_VALUE_BY_SYMBOL(bufferCallingParam,I_("&"),workingAcctNum_);
         CHOP_STRING_BY_SYMBOL (bufferCallingParam,I_("&"));

         // assume that account number must be one of being passed 
         // parameter
         if(!workingAcctNum_.strip().empty() && workingAcctNum_.find (I_("AccountNum")) != DString::npos)
         {
            break;
         }
      }while(true && !bufferCallingParam.empty());

      if ((posToken = workingAcctNum_.find (I_("AccountNum"))) != DString::npos )
      {
         CHOP_STRING_BY_SYMBOL(workingAcctNum_,I_("="));
      }
   }

   BSTR bstrHeaders = NULL;
   bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded\r\n");
   V_VT(&vHeaders) = VT_BSTR;
   V_BSTR(&vHeaders) = bstrHeaders;

   if ( strPageUrl != "" )
   {
      m_Browser_Launch.Navigate( strPageUrl.AllocSysString(), &varEmpty, &varEmpty, &vPostData, &vHeaders );
   }
   if ( bstrHeaders ) SysFreeString(bstrHeaders);
   VariantClear(&vPostData);
   VariantClear(&vHeaders);
}

//******************************************************************************
void BrowserLaunch::OnWebback()
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBBACK );
   m_Browser_Launch.GoBack();
}

//******************************************************************************
void BrowserLaunch::OnWebfwd()
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBFWD );
   m_Browser_Launch.GoForward();
}

//******************************************************************************
void BrowserLaunch::OnWebhome()
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBHOME );

   CString strUrl;
   GetUrl(strUrl);

   m_Browser_Launch.Navigate(strUrl, NULL, NULL, NULL, NULL); // Display HTML doc associated with selected item
}

//******************************************************************************
void BrowserLaunch::OnWebstop()
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBSTOP );
   m_Browser_Launch.Stop();
}

//******************************************************************************
BEGIN_EVENTSINK_MAP(BrowserLaunch, BaseMainDlg)
//{{AFX_EVENTSINK_MAP(BrowserLaunch)
ON_EVENT(BrowserLaunch, IDC_BROWSER_LAUNCH, 105 /* CommandStateChange */, OnCommandStateChange, VTS_I4 VTS_BOOL)
ON_EVENT(BrowserLaunch, IDC_BROWSER_LAUNCH, 106 /* DownloadBegin */,   OnDownloadBegin, VTS_NONE)
ON_EVENT(BrowserLaunch, IDC_BROWSER_LAUNCH, 104 /* DownloadComplete */,OnDownloadComplete, VTS_NONE)
ON_EVENT(BrowserLaunch, IDC_BROWSER_LAUNCH, 112 /* PropertyChange */,  OnPropertyChange, VTS_NONE)
ON_EVENT(BrowserLaunch, IDC_BROWSER_LAUNCH, 250 /* BeforeNavigate2 */, OnBeforeNavigate2, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
ON_EVENT(BrowserLaunch, IDC_BROWSER_LAUNCH, 259 /* DocumentComplete */,OnDocumentComplete, VTS_DISPATCH VTS_PVARIANT)
ON_EVENT(BrowserLaunch, IDC_BROWSER_LAUNCH, DISPID_NAVIGATECOMPLETE2 /*252*/,  OnNavigateComplete2, VTS_DISPATCH VTS_PVARIANT)
ON_EVENT(BrowserLaunch, IDC_BROWSER_LAUNCH, DISPID_NAVIGATEERROR /*12*/, OnNavigateError, VTS_I2 VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
ON_EVENT(BrowserLaunch, IDC_BROWSER_LAUNCH, 16  /* WindowClosing */,   OnWindowClosing, VTS_I2 VTS_BOOL VTS_PBOOL)
//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//******************************************************************************
void BrowserLaunch::OnCommandStateChange(long Command, BOOL Enable)
{
   TRACE_METHOD( CLASSNAME, BI_STATECHANGE );
   //switch ( Command )
   //{
   //  default:
   //   break;
   //}
}

//******************************************************************************
void BrowserLaunch::OnWindowClosing(short wbUID, BOOL IsChildWindow, BOOL FAR* Cancel)
{
   *Cancel = VARIANT_TRUE;
   OnClose();
}

//******************************************************************************
void BrowserLaunch::OnDownloadBegin()
{
   TRACE_METHOD( CLASSNAME, BI_DOWNLOAD );

// m_Animate.Open(szFileName);
// Need to move to message file
   SetMessageStatusBar( TXT_LOAD_HTML );
}

//******************************************************************************
void BrowserLaunch::OnDownloadComplete()
{
   TRACE_METHOD( CLASSNAME, BI_COMPLETE );
   SetMessageStatusBar( NULL_STRING );
//   m_Animate.Close( );   // Same as close
}

//******************************************************************************
void BrowserLaunch::OnPropertyChange( BSTR szProperty )
{
   TRACE_METHOD( CLASSNAME, BI_COMPLETE );
   SetMessageStatusBar( L"PropertyChange" );
   //VARIANT vValue;
   //CString sProperty;
   //m_Browser_Launch.GetProperty( sProperty, vValue );
   //m_Animate.Close( );   // Same as close
}

//******************************************************************************
void BrowserLaunch::resetSessionId() 
{
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if ( NULL != pDSTCWorkSession ) {
      const DSTCSecurity *pSecurity = 
         dynamic_cast <const DSTCSecurity *> (pDSTCWorkSession->getSecurity (DSTCHost::getPrimaryHost()));
      if ( NULL != pSecurity ) {
         // reset SessionID
         CComVariant pReturnResult;
         CStringArray paramArray;
         bool ret;
//          ret = CallJScript(L"evalReturn", paramArray, &pReturnResult, iDispatch);
            ret = CallJScript(L"getSessionToken", paramArray, &pReturnResult);
//          ret = CallJScript(L"Desktop.this.getSessionToken", paramArray, &pReturnResult, iDispatch);
//          ret = CallJScript(L"Desktop.getSessionToken", paramArray, &pReturnResult, iDispatch);
//          ret = CallJScript(L"Desktop.getSessionToken()", paramArray, &pReturnResult, iDispatch);
         if( ret && pReturnResult.vt == VT_BSTR ) {
            CString strReturnResult (_bstr_t(pReturnResult).Detach ());
            DString dstrReturnResult = strReturnResult;
            const_cast<DSTCSecurity*>(pSecurity)->setSessionId(dstrReturnResult);
         }
      }
   }
}

//******************************************************************************
void BrowserLaunch::OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel)
{
   IUnknown*  pUnk;
   LPDISPATCH lpWBDisp;
   HRESULT    hr;
   pUnk = m_Browser_Launch.GetControlUnknown();
   ASSERT(pUnk);
   hr = pUnk->QueryInterface(IID_IDispatch, (void**)&lpWBDisp);
   ASSERT(SUCCEEDED(hr));
   if ( pDisp == lpWBDisp )
   {
      if ( Cancel != NULL )
      {
         *Cancel = VARIANT_FALSE;
      }
      /*
     if( !LaunchConfirmation() )
     {
        if (Cancel != NULL)
        {
           *Cancel = VARIANT_TRUE;
        }
     }
     else
     {
        if( getParent()->cancel( this ) )
        {
           SetCancelInProgress();
           PostCancel( true );
           //EndDialog( IDCANCEL );
           Exit( IDCANCEL );
        }
     }
     */
   }
   lpWBDisp->Release();
}

//******************************************************************************
void BrowserLaunch::OnDocumentComplete(LPDISPATCH lpDisp,VARIANT *URL)
{
   IUnknown*  pUnk;
   LPDISPATCH lpWBDisp;
   HRESULT    hr;

   pUnk = m_Browser_Launch.GetControlUnknown();
   ASSERT(pUnk);

   hr = pUnk->QueryInterface(IID_IDispatch, (void**)&lpWBDisp);
   ASSERT(SUCCEEDED(hr));

   if ( lpDisp == lpWBDisp )
   {
      // Top Level Frame has finished loading and is initialized.
      ProcessBtnElems();
   }
   if( _topLevelFrame == lpDisp ) {
      resetSessionId();
      _topLevelFrame = NULL;
   }
   lpWBDisp->Release();


}

//******************************************************************************
void BrowserLaunch::OnNavigateComplete2(LPDISPATCH lpDisp,VARIANT *URL)
{
   _topLevelFrame = lpDisp;
   if ( haveUpdate() )
   {
     //CWnd* pCWnd = GetDlgItem( IDCANCEL );
      CWnd* pCWnd = GetDlgItem( IDCANCEL );
      if ( pCWnd != NULL )
      {
         pCWnd->EnableWindow( false );
      }
   }
}

//******************************************************************************
bool BrowserLaunch::CallJScript(const CString strFunc, 
                                const CStringArray& paramArray,
                                CComVariant* pVarResult )
{
   bf::log::LogStream ls( bf::log::databroker );
   ls << bf::log::information;
   ls << I_("BrowserLaunch::CallJScript") << bf::log::endlf;
   bf::log::LogStream lsTrace( bf::log::databroker );
   lsTrace << bf::log::ltrace;

   IHTMLDocument2 *tmpdocument = GetDocument();
   if ( !tmpdocument )
   {
      return (false);
   }

   CComPtr<IDispatch> spScript;
   HRESULT hr = tmpdocument->get_Script(&spScript);
   if ( !SUCCEEDED(hr) )
   {
      tmpdocument->Release();
      return (false);
   }

   CComBSTR bstrMember(strFunc);
   DISPID dispid = NULL;
   hr = spScript->GetIDsOfNames(IID_NULL,&bstrMember,1,
                                LOCALE_SYSTEM_DEFAULT,&dispid);
   if ( FAILED(hr) )
   {
      ls << I_("Failed to find ") << LPCTSTR(strFunc) << bf::log::endlf;
      tmpdocument->Release();
      return (false);
   }

   ls << I_("Found ") << LPCTSTR(strFunc) << bf::log::endlf;
   const int arraySize = paramArray.GetSize();

   DISPPARAMS dispparams;
   memset(&dispparams, 0, sizeof dispparams);
   dispparams.cArgs = arraySize;
   dispparams.rgvarg = new VARIANT[dispparams.cArgs];

   for ( int i = 0; i < arraySize; i++ )
   {
      CComBSTR bstr = paramArray.GetAt(arraySize - 1 - i); // back reading
      bstr.CopyTo(&dispparams.rgvarg[i].bstrVal);
      dispparams.rgvarg[i].vt = VT_BSTR;
   }
   dispparams.cNamedArgs = 0;

   EXCEPINFO excepInfo;
   memset(&excepInfo, 0, sizeof excepInfo);
   CComVariant vaResult;
   UINT nArgErr = (UINT)-1;  // initialize to invalid arg

   hr = spScript->Invoke(dispid,IID_NULL,0,
                         DISPATCH_METHOD,&dispparams,&vaResult,&excepInfo,&nArgErr);

   delete [] dispparams.rgvarg;
   if ( FAILED(hr) )
   {
      tmpdocument->Release();
      return (false);
   }

   if ( pVarResult )
   {
      *pVarResult = vaResult;
   }
   tmpdocument->Release();
   return (true);
}

//******************************************************************************
void BrowserLaunch::SetHomeFocus()
{
   TRACE_METHOD( CLASSNAME, BI_SETHOMEFOCUS );
}

//******************************************************************************
SEVERITY BrowserLaunch::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   processParameters();

   return NO_CONDITION;
}

//******************************************************************************
void BrowserLaunch::processParameters()
{
   DString parameterName, 
      parameterValue;

   m_parameters = NULL_STRING;
//save these parameters off..   
   getParameter (I_("from_screen") , m_fromScreen);
   getParameter (I_("BrowserTitle"), m_BrowserTitle);
   getParameter (I_("UrlParams"), m_urlParams);
//transform the url params sent by screens into &name=value...

   DString _browserTitle = NULL_STRING;
   if (!m_urlParams.empty())
   {
      I_CHAR *temp = const_cast< I_CHAR* >(m_urlParams.c_str());

      do
      {
         DString paramName, 
            paramValue;

         temp = parseIdiString (temp, paramName, paramValue);
         if (paramName != I_("BrowserTitle"))   
         {
             m_parameters = m_parameters + I_("&") + paramName + I_("=") + paramValue;
         }
         else
         {
             _browserTitle = paramValue;

             if (m_BrowserTitle.empty())
             {
                 m_BrowserTitle = _browserTitle;
             }
         }

      }
      while (temp && temp != NULL_STRING && *temp);
   }

   if(!_browserTitle.empty())
   {
      DString strEncoded(_browserTitle);

      size_t found;
      found = strEncoded.find_first_of(I_("\'"));
      while( found != DString::npos ) {
         strEncoded.replace(found, 1, I_("\\\'"));
         found = strEncoded.find_first_of(I_("\'"), found + 2);
      }

      _browserTitle = I_("");
      _browserTitle = strEncoded;

      m_parameters = m_parameters + I_("&") + I_("BrowserTitle") + I_("=") + _browserTitle;

   }
}

//******************************************************************************
void BrowserLaunch::buildPostParams ()
{
   TRACE_METHOD( CLASSNAME, I_("buildPostParams") );
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   
   if (pDSTCWorkSession)
   {
      const DSTCSecurity *pSecurity = 
            dynamic_cast <const DSTCSecurity *> (pDSTCWorkSession->getSecurity (DSTCHost::getPrimaryHost()));

      if (pSecurity)
      {
         DString mgmtCoId, 
            clientId, 
            currentUserName,
            sessionId,
            pageName;

         currentUserName = pSecurity->getUserId();
         sessionId = pSecurity->getSessionId();
         {
            size_t found;
            found = sessionId.find_first_of (I_("+"));
            while( found != DString::npos ) {
               sessionId.replace(found,1,I_("%2B"));
               found = sessionId.find_first_of(I_("+"),found+1);
            }
         }
         pageName = getParent ()->getCommand().getWebPageName ();
         pDSTCWorkSession->getMgmtCo().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
         pDSTCWorkSession->getMgmtCo().getField (ifds::ClientID, clientId, BF::HOST);
         
#ifdef _DEBUG
         if( GetConfigValueAsBool( I_("Debug"), I_("OverridenDSKURLEnable") ) ) 
         {
            DString strOverridenURL = GetConfigValueAsString(I_("Debug"), I_("OverridenDSKURL") );
            if( !strOverridenURL.empty() )
            {
               m_parameters = strOverridenURL;
            }
         }
#endif

         //build the url...
         if (!pageName.empty ())
         {
#ifdef _DEBUG
            bool bIsStubBrowser =  GetConfigValueAsBool( I_("Debug"), I_("StubModeOnBrowserScreen") );
#endif

            m_parameters = m_parameters +
                              I_("&jobname=") + pageName;

#ifdef _DEBUG
							  if(bIsStubBrowser)
							  {
								  m_parameters = m_parameters + I_("&envName=")+ I_("stub");
							  }
							  else
#endif
							  {
                                  m_parameters = m_parameters + I_("&envName=")+ mgmtCoId;
							  }

			m_parameters = m_parameters +
							  I_("&companyCode=") + clientId +
                              I_("&ruserId=") + currentUserName +
                              I_("&sessionId=") + sessionId +
                              I_("&market=") + DSTCommonFunctions::getMarket();

            // Get date format - Note Progress uses a more 'compact' format... Value "mdy" or "dmy" or "ymd",
            // these are the standard values for the /RequestHeader/dateFormat element of the SmartView header.
            // to convert from MMddyy etc, we lower case it and map it..
            DString dateFormat = GetConfigValueAsString (I_( "LocaleFormats" ), I_( "HostMasks" ), I_( "D" ));

            dateFormat = dateFormat.lowerCase ();
            if (dateFormat == I_("mmddyyyy"))
            {
               dateFormat = I_("mdy");
            }
            else if (dateFormat == I_( "yyyymmdd"))
            {
               dateFormat = I_("ymd");
            }
            else if (dateFormat == I_("ddmmyyyy"))
            {
               dateFormat = I_("dmy");
            }

            m_parameters = m_parameters + I_( "&dateFormat=" ) + dateFormat;
            //-- end of date format code.

			const ClientLocale& rClientLocale = pDSTCWorkSession->getClientLocale();
            const DString clientLocale = rClientLocale.getLocale();

			DString dateFormatDisplay = GetConfigValueAsString( I_( "LocaleFormats" ), I_( "DisplayMasks" ), clientLocale + I_( "-D" ) );
		    dateFormatDisplay = dateFormatDisplay.lowerCase();
            
			m_parameters = m_parameters + I_( "&dateFormatDisplay=" ) + dateFormatDisplay;

            // add hostname so we know who is having problems in the EComm logs..
            char * pszEnvVarComputerName = getenv( "COMPUTERNAME" );
            m_parameters = m_parameters + I_("&computerName=") + DString (DStringA (pszEnvVarComputerName));

            // get the system 3D Object (aka Dialog Box colour)
            DWORD dwColor = ::GetSysColor (COLOR_BTNFACE);

            char szColor[32];
            sprintf( szColor,
                     "&bgcolor=%x%x%x",
                     GetRValue (dwColor),
                     GetGValue (dwColor),
                     GetBValue (dwColor) );           
            m_parameters = m_parameters + DString (DStringA (szColor));

#ifdef _DEBUG
            if( GetConfigValueAsBool( I_("Debug"), I_("DebugEXT") ) ) 
            {
               m_parameters = m_parameters + I_("&debug=true");
            }
#endif

            DSTCUserSession *pDSTCUserSession = dynamic_cast <DSTCUserSession *>(&getBFSession()->getUserSession());

            if (pDSTCUserSession)
            {
               if (getParent ()->getCommand().getName () == CMD_BPROC_GLOBAL_SEARCH )
               {
               
                  DString dstCompanyId (NULL_STRING),
                     dstCompanyName (NULL_STRING);

                  // Add Companies to Dynamic Menu
                  unsigned long iNumCo = pDSTCUserSession->getNumberOfCompanies( DSTCHost::getPrimaryHost() );
                  if (iNumCo > 0)
                  {
                     m_parameters = m_parameters + I_("&envList=");
                  }
                  for( unsigned long i=0; i < iNumCo; i++ )
                  {
                     pDSTCUserSession->getCompanyInfo( DSTCHost::getPrimaryHost(), i, dstCompanyId, dstCompanyName );
                     m_parameters = m_parameters + dstCompanyId + ((i >= iNumCo - 1) ? I_("") : I_(";"));
                  }
               }
			}
            const ClientLocale& rLocale = pDSTCUserSession->getClientLocale();
            const DString locale = rLocale.getLocale();
            
            m_parameters = m_parameters + I_("&locale=") + locale;
         }
      }
   }
}

//******************************************************************************
void BrowserLaunch::GetUrl(CString& strUrl)
{
   TRACE_METHOD( CLASSNAME, I_("GetUrl") );

   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   
   if (pDSTCWorkSession)
   {
      const DSTCSecurity *pSecurity = 
            dynamic_cast <const DSTCSecurity *> (pDSTCWorkSession->getSecurity (DSTCHost::getPrimaryHost()));

      if (pSecurity)
      {
         DString mgmtCoId, 
            clientId, 
            companyName,
            currentUserName,
            sessionId,
            pageName,
            webUrl;

         currentUserName = pSecurity->getUserId();
         sessionId = pSecurity->getSessionId();
         {
            size_t found;
            found = sessionId.find_first_of(I_("+"));
            while( found != DString::npos ) {
               sessionId.replace(found,1,I_("%2B"));
               found = sessionId.find_first_of(I_("+"),found+1);
            }
         }
         pageName = getParent ()->getCommand().getWebPageName ();
         pDSTCWorkSession->getMgmtCo().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
         pDSTCWorkSession->getMgmtCo().getField (ifds::ClientID, clientId, BF::HOST);
         pDSTCWorkSession->getMgmtCo().getField (ifds::CompanyName, companyName, BF::HOST);
         MgmtCoOptions* pOptions = NULL;
         pDSTCWorkSession->getMgmtCo().getMgmtCoOptions( pOptions );
         if( NULL != pOptions ) {
            pOptions->getField( ifds::CompanyUrl, webUrl, BF::HOST );
         }
         if (webUrl.empty()) //get it the old way...from the ACL
         {
            pDSTCWorkSession->getMgmtCo().getField (ifds::CompanyUrl, webUrl, BF::HOST);
         }

#ifdef _DEBUG
         if( GetConfigValueAsBool( I_("Debug"), I_("OverridenDSKURLEnable") ) ) 
         {
            DString strOverridenURL = GetConfigValueAsString(I_("Debug"), I_("OverridenDSKURL") );
            if( !strOverridenURL.empty() )
            {
               webUrl = strOverridenURL;
            }
         }
#endif

         //build the url...
         if (!pageName.empty () && !webUrl.empty())
         {
#ifdef _DEBUG
            bool bIsStubBrowser =  GetConfigValueAsBool( I_("Debug"), I_("StubModeOnBrowserScreen") );
#endif

            webUrl = webUrl + I_("&jobname=") + pageName;

#ifdef _DEBUG
            if(bIsStubBrowser)
            {
               webUrl = webUrl + I_("&envName=")+ I_("stub");
            }
            else
#endif
            {
               webUrl = webUrl + I_("&envName=")+ mgmtCoId;
            }

            webUrl = webUrl + I_("&companyCode=") + clientId +
                              I_("&ruserId=") + currentUserName +
                              I_("&sessionId=") + sessionId +
                              I_("&market=") + DSTCommonFunctions::getMarket();

            // get the system 3D Object (aka Dialog Box colour)
            DWORD dwColor = ::GetSysColor (COLOR_BTNFACE);

            char szColor[32];
            sprintf( szColor,
                     "&bgcolor=%x%x%x",
                     GetRValue (dwColor),
                     GetGValue (dwColor),
                     GetBValue (dwColor) );

            // Get date format - Note Progress uses a more 'compact' format... Value "mdy" or "dmy" or "ymd",
            // these are the standard values for the /RequestHeader/dateFormat element of the SmartView header.
            // to convert from MMddyy etc, we lower case it and map it..
            DString dateFormat = GetConfigValueAsString (I_( "LocaleFormats" ), I_( "HostMasks" ), I_( "D" ));

            dateFormat = dateFormat.lowerCase ();
            if (dateFormat == I_("mmddyyyy"))
            {
               dateFormat = I_("mdy");
            }
            else if (dateFormat == I_( "yyyymmdd"))
            {
               dateFormat = I_("ymd");
            }
            else if (dateFormat == I_("ddmmyyyy"))
            {
               dateFormat = I_("dmy");
            }

            webUrl = webUrl + I_( "&dateFormat=" ) + dateFormat;
            //-- end of date format code.

			const ClientLocale& rClientLocale = pDSTCWorkSession->getClientLocale();
            const DString clientLocale = rClientLocale.getLocale();

			DString dateFormatDisplay = GetConfigValueAsString( I_( "LocaleFormats" ), I_( "DisplayMasks" ), clientLocale + I_( "-D" ) );
		    dateFormatDisplay = dateFormatDisplay.lowerCase();

			m_parameters = m_parameters + I_( "&dateFormatDisplay=" ) + dateFormatDisplay;

            // add hostname so we know who is having problems in the EComm logs..
            char * pszEnvVarComputerName = getenv( "COMPUTERNAME" );
            webUrl = webUrl + I_("&computerName=") + DString (DStringA (pszEnvVarComputerName));
            //add the extra parameters sent by individual calls...
            webUrl = webUrl + m_parameters;

#ifdef _DEBUG
            if( GetConfigValueAsBool( I_("Debug"), I_("DebugEXT") ) ) 
            {
               webUrl = webUrl + I_("&debug=true");
            }
#endif

            DSTCUserSession *pDSTCUserSession = dynamic_cast <DSTCUserSession *>(&getBFSession()->getUserSession());

            if (pDSTCUserSession)
            {
               if (getParent ()->getCommand().getName () == CMD_BPROC_GLOBAL_SEARCH )
               {
               
                  DString dstCompanyId (NULL_STRING),
                     dstCompanyName (NULL_STRING);

                  // Add Companies to Dynamic Menu
                  unsigned long iNumCo = pDSTCUserSession->getNumberOfCompanies( DSTCHost::getPrimaryHost() );
                  if (iNumCo > 0)
                  {
                     webUrl = webUrl + I_("&envList=");
                  }
                  for( unsigned long i=0; i < iNumCo; i++ )
                  {
                     pDSTCUserSession->getCompanyInfo( DSTCHost::getPrimaryHost(), i, dstCompanyId, dstCompanyName );
                     webUrl = webUrl + dstCompanyId + ((i >= iNumCo - 1) ? I_("") : I_(";"));
                  }
               }
               const ClientLocale& rLocale = pDSTCUserSession->getClientLocale();
               const DString locale = rLocale.getLocale();
               
               webUrl = webUrl + I_("&locale=") + locale;

//reading the language from the client locale 
            }

            // convert the URL from Unicode to ASCII
            DStringA dstraConvertFromUniCode (webUrl);
            dstraConvertFromUniCode += DStringA (szColor);
            strUrl = dstraConvertFromUniCode.c_str();
         }
         else
         {
            //no page name defined for this command, check XML configuration file.
            CString cstrError;
            cstrError.LoadString(TXT_SYS_ERROR_CONTACT_ADM);
            AfxMessageBox (cstrError);
            if (getParent()->cancel (this))
            {
               SetCancelInProgress ();
               PostCancel (true);
            }
         }
      }
   }
}

//******************************************************************************
void BrowserLaunch::GetPageUrl(CString& strUrl)
{
	TRACE_METHOD( CLASSNAME, I_("GetPageUrl") );

	DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession*>(getBFWorkSession());

	if (pDSTCWorkSession)
	{
		const DSTCSecurity* pSecurity = dynamic_cast<const DSTCSecurity*>(pDSTCWorkSession->getSecurity(DSTCHost::getPrimaryHost()));

		if (pSecurity)
		{
			DString webUrl;

			MgmtCoOptions* pOptions = NULL;
			pDSTCWorkSession->getMgmtCo().getMgmtCoOptions(pOptions);
			if (NULL != pOptions) 
			{
				pOptions->getField(ifds::CompanyUrl, webUrl, BF::HOST);
			}
			if (webUrl.empty()) //get it the old way...from the ACL
			{
				pDSTCWorkSession->getMgmtCo().getField (ifds::CompanyUrl, webUrl, BF::HOST);
			}

			// convert the URL from Unicode to ASCII
			DStringA dstraConvertFromUniCode(webUrl);
			strUrl = dstraConvertFromUniCode.c_str();
		}
	}
}

//******************************************************************************
void BrowserLaunch::processParametersFromWebTagAttributes( IHTMLElement* pElem )
{
   DString tmparm = NULL_STRING, parameterName, parameterValue;
/*
//   const webguimaping* pWebMap = webpageMap::getInstance().get( m_orgCommand );

   if ( pWebMap != NULL )
   {
      m_pagename = pWebMap->getWebPage();

      SetDialogName( m_pagename );

      getParameter( I_("BrowserTitle"), m_BrowserTitle );

      if ( m_BrowserTitle == NULL_STRING )
      {
        m_BrowserTitle = m_pagename;
      }

      const std::vector<DString> parameterVec = pWebMap->getParameterVec();
      std::vector<DString>::const_iterator it = parameterVec.begin();

      while ( it != parameterVec.end() )
      {
         parameterName = *it;

         //getParameter(CurParameter, parameterValue);
         CString cstrParameterName, cstrParameterValue;

         DString attributeName = I_( "desktop" ) + parameterName;

         cstrParameterName = attributeName.c_str();

         GetElementAttribute( pElem, cstrParameterName, cstrParameterValue );

         DString parameterValue = cstrParameterValue;

         parameterValue.strip();

         if ( parameterValue != NULL_STRING )
         {
            setParameter( parameterName, parameterValue );
         }
         it++;
      }
   }
   m_parameters = tmparm;
   */
}

//******************************************************************************
// Pack some data into a SAFEARRAY of BYTEs. Return in a VARIANT
HRESULT BrowserLaunch::GetPostData(LPVARIANT pvPostData)
{
   HRESULT hr;
   LPSAFEARRAY psa;
   LPSTR pPostData;

   if ( !pvPostData )
   {
      return (E_POINTER);
   }

   VariantInit(pvPostData);

   psa = SafeArrayCreateVector(VT_UI1, 0, m_parameters.asA().size ());
   if ( !psa )
   {
      return (E_OUTOFMEMORY);
   }

   hr = SafeArrayAccessData(psa, (LPVOID*)&pPostData);
   memcpy (pPostData, m_parameters.asA().c_str (), m_parameters.asA().size ());
   hr = SafeArrayUnaccessData(psa);

   V_VT(pvPostData) = VT_ARRAY | VT_UI1;
   V_ARRAY(pvPostData) = psa;

   return (NOERROR);
}

//******************************************************************************
// *document need to be released by the calling function
IHTMLDocument2 *BrowserLaunch::GetDocument()
{
   IHTMLDocument2 *document = NULL;
   if ( &m_Browser_Launch != NULL )
   {
      IDispatch *document_dispatch = NULL;
      document_dispatch = m_Browser_Launch.GetDocument();
      if ( document_dispatch != NULL )
      {
         document_dispatch->QueryInterface(IID_IHTMLDocument2,(void **)&document);
         document_dispatch->Release();
      }
   }
   return (document);
}

//******************************************************************************
BOOL BrowserLaunch::GetElementId(IHTMLElement* pElement, CString & Name)
{
   BSTR strTemp;

   if ( pElement )
   {
      if ( FAILED(pElement->get_id (&strTemp)) )
      {
         return (FALSE);
      }
      Name = CString (strTemp);
   }

   return (TRUE);
}

//******************************************************************************
BOOL BrowserLaunch::GetElementAttribute(IHTMLElement *pElement,const CString & attName ,CString &value)
{
   BSTR strTemp= NULL;
   CComVariant var;

   if ( pElement )
   {
      if ( FAILED(pElement->getAttribute(_bstr_t(attName),0,&var)) )
         return (FALSE);

      if ( var.vt == VT_NULL )
      {
         value = HTM_TEXT_EMPTY;
         return (TRUE);
      }
      value = CString(_bstr_t(var).Detach ());
   }

   return (TRUE);
}

//******************************************************************************
BOOL BrowserLaunch::GetElementName (IHTMLElement* pElement, CString &strName)
{
   return (GetElementAttribute(pElement, HTML_ATT_NAME,strName));
}

//******************************************************************************
BOOL BrowserLaunch::GetElementValue (IHTMLElement* pElement, CString &value)
{
   return (GetElementAttribute(pElement, HTML_ATT_VALUE, value));
}

//******************************************************************************
BOOL BrowserLaunch::SetElementValue (IHTMLElement* pElement, CString &value)
{
   return (SetElementAttribute(pElement, HTML_ATT_VALUE, value));
}

//******************************************************************************
BOOL BrowserLaunch::SetElementAttribute(IHTMLElement *pElement,const CString & attName ,CString &value)
{
   BSTR strTemp= NULL;
   VARIANT var = {0};

   BSTR bstrVar = NULL;
   bstrVar = SysAllocString(value);
   V_VT(&var) = VT_BSTR;
   V_BSTR(&var) = bstrVar;

   if ( pElement )
   {
      if ( FAILED(pElement->setAttribute(_bstr_t(attName),var)) )
      {
         if ( bstrVar ) SysFreeString(bstrVar);
         VariantClear(&var);
         return (FALSE);
      }
   }

   if ( bstrVar ) SysFreeString(bstrVar);
   VariantClear(&var);

   return (TRUE);
}

//******************************************************************************
BOOL BrowserLaunch::IsSelect(BSTR tag)
{
   return (_wcsicmp(tag,HTMTAG_SELECT) == 0);
}

//******************************************************************************
BOOL BrowserLaunch::IsImg(BSTR tag)
{
   return (_wcsicmp(tag, HTMTAG_IMG) == 0);
}

//******************************************************************************
BOOL BrowserLaunch::IsImage(BSTR tag)
{
   return (_wcsicmp(tag,HTMTAG_IMAGE)==0);
}

//******************************************************************************
BOOL BrowserLaunch::IsTextArea( BSTR tag)
{
   return (_wcsicmp(tag , HTMTAG_TEXTAREA)==0);
}

//******************************************************************************
BOOL BrowserLaunch::IsInput( BSTR tag)
{
   return (_wcsicmp(tag, HTMTAG_INPUT) == 0);
}

//******************************************************************************
BOOL BrowserLaunch::IsButton( BSTR tag)
{
   return (_wcsicmp(tag, HTMTAG_BUTTON) == 0);
}

//******************************************************************************
int BrowserLaunch::IsControl(BSTR tag)
{
   if ( IsImage(tag) )
      return (HTM_C_IMAGE);
   if ( IsImg(tag ) )
      return (HTM_C_IMG);
   if ( IsInput(tag) )
      return (HTM_C_INPUT);
   if ( IsTextArea(tag) )
      return (HTM_C_TEXTAREA);
   if ( IsSelect(tag) )
      return (HTM_C_SELECT);
   if ( IsButton(tag) )
      return (HTM_C_BUTTON);

   return (HTM_C_OTHER);
}

//******************************************************************************
// Get the control type define in index.
int BrowserLaunch::GetControlType(BSTR name)
{
   _bstr_t bstrName (name);
   if ( _wcsicmp(name, HTMITYPE_BUTTON) == 0 )
      return (HTM_CT_BUTTON);

   if ( _wcsicmp(name,HTMITYPE_CHECKBOX) == 0 )
      return (HTM_CT_CHECKBOX);

   if ( _wcsicmp(name,HTMITYPE_HIDDEN) == 0 )
      return (HTM_CT_HIDDEN);

   if ( _wcsicmp(name,HTMITYPE_IMAGE) == 0 )
      return (HTM_CT_IMAGE);

   if ( _wcsicmp(name,HTMITYPE_PASSWORD) == 0 )
      return (HTM_CT_PASSWORD);

   if ( _wcsicmp(name,HTMITYPE_RADIO) == 0 )
      return (HTM_CT_RADIO);

   if ( _wcsicmp(name,HTMITYPE_RESET) == 0 )
      return (HTM_CT_RESET);

   if ( _wcsicmp(name,HTMITYPE_SUBMIT) == 0 )
      return (HTM_CT_SUBMIT);

   if ( _wcsicmp(name,HTMITYPE_TEXT) == 0 )
      return (HTM_CT_TEXT);

   return (0);
}

//******************************************************************************
STDMETHODIMP BrowserLaunch::Invoke(DISPID dispidMember,
                                   REFIID riid,
                                   LCID lcid,
                                   WORD wFlags,
                                   DISPPARAMS* pdispparams,
                                   VARIANT* pvarResult,
                                   EXCEPINFO* pexcepinfo,
                                   UINT* puArgErr)
{
   switch ( dispidMember )
   {
      case DISPID_HTMLELEMENTEVENTS_ONCLICK:
         OnBtnClick();
         break;
      case DISPID_NAVIGATEERROR :
         {
            m_Browser_Launch.Stop();

            //Extract the status code from the DISPPARAMS structure
            VARIANT * vt_statuscode = pdispparams->rgvarg[1].pvarVal;
            TCHAR tmp[50];
         #ifdef UNICODE
            _ltow(vt_statuscode->lVal, tmp, 10);
         #else
            _ltoa(vt_statuscode->lVal, tmp, 10);
         #endif
            CString strTmp(_T("Navigation Error #"));
            strTmp += tmp;

            //CALL ERROR PAGE,FILTER OUT http ERRORS
            DString pageName (NULL_STRING), 
               webUrl (NULL_STRING);
            CString strUrl;
            
            DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            
            if (pDSTCWorkSession)
            {
               pageName = getParent()->getCommand().getWebPageName();
               pDSTCWorkSession->getMgmtCo().getField (ifds::CompanyUrl, webUrl, BF::HOST);

#ifdef _DEBUG
               if( GetConfigValueAsBool( I_("Debug"), I_("OverridenDSKURLEnable") ) ) 
               {
                  DString strOverridenURL = GetConfigValueAsString(I_("Support"), I_("OverridenDSKURL") );
                  if( !strOverridenURL.empty() )
                  {
                     webUrl = strOverridenURL;
                  }
               }
#endif

               if (!pageName.empty() && !webUrl.empty())
               {
                  webUrl = webUrl + I_("&jobname=DesktopGeneral_ErrorPage");
                  strUrl = webUrl.c_str();
               }
               if (strUrl != I_(""))
               {
                  m_Browser_Launch.Navigate(strUrl, NULL, NULL, NULL, NULL);
               }
            }
         }
         break;
      default:
         break;
   }

   return (S_OK);
}

//******************************************************************************
bool BrowserLaunch::OnBtnClick (const CString& buttonId)
{
   CStringArray paramArray;
   CComVariant* pVarResult = NULL;
   bool ret = true;

   DString dstrLastAccountNum,
      invokedBrowserName = getParent()->getCommand().getName();
   
   invokedBrowserName.strip();
   
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   
   getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, dstrLastAccountNum);
   dstrLastAccountNum.strip();

   // style one - confirm dialog calls back on the javascript to perform the
   // update...
   //
   // This 'LaunchConfirm' javascript is the prefered way of bringing up the
   // confirmation dialog.. if brings up the confirmation dialog and then if
   // the user 'OK's the confirm dlg then the 'update()' javascript function
   // is called on the current webpage where you can perform your updates.
   // See ConfirmationDlg.cpp for where the update() function is called..
   if ( buttonId == "btnOK" )
   {
      DString dstrUpdateStatus = I_("N");

      bool blConfirmReturn = false;

      if ( LaunchConfirm() )
      {
       _blUpdatesAlreadyPerformed = false;
         dstrUpdateStatus = I_("Y");
         getParent()->setField( this,
                                BF::NullContainerId,
                                BROWSERLAUNCH::UPDATE_STATUS,
                                dstrUpdateStatus );

         setParameter( I_( "CalledFrom" ), I_("BrowserLaunch") );
         setParameter (I_("InvokedBrowserName"), invokedBrowserName);

         blConfirmReturn = static_cast< BrowserLaunchProcess * > ( getParent() )->confirm (this);
      }
      else
      {
         CComVariant pReturnResult;
         CStringArray paramArray;
         ret = CallJScript(L"getResult", paramArray, &pReturnResult);
         if( pReturnResult.vt == VT_NULL)
            return false;

         CString strReturnResult (_bstr_t(pReturnResult).Detach ());
         DString dstrReturnResult = strReturnResult;
         setParameter (I_("BrowserResults"), dstrReturnResult);
         CDialog::OnOK();
      }

      if ( blConfirmReturn  && getParent()->ok (this))
      {
         CDialog::OnOK();

         PostMessage( WM_SYSCOMMAND, SC_CLOSE );
      }
   }

   // style two
   // the updates have already been done but the web screens just want to show the
   // confirmation screen
   else if ( buttonId == "btnConfirmDlg" )
   {
      if ( haveUpdate() )
      {
         bool blConfirmReturn = false;

         DString dstrUpdateStatus = I_("Y");
         getParent()->setField( this,
                                BF::NullContainerId,
                                BROWSERLAUNCH::UPDATE_STATUS,
                                dstrUpdateStatus );


         // set status flag to true this will disable the confirmation dialogs 'Cancel'
         // button as the update has already been processed by the webscreen...
         _blUpdatesAlreadyPerformed = true;

         //IN2831230 - Fund Limitation Option
         setParameter( I_("InvokedBrowserName"), invokedBrowserName );
         blConfirmReturn = static_cast< BrowserLaunchProcess * > ( getParent() )->confirm( this );
         if ( blConfirmReturn && getParent()->ok( this ) )
         {
            CDialog::OnOK();
         }
      }
   }
   else if ( buttonId == "btnCancel" )
   {
      CComVariant pReturnResult;
      CStringArray paramArray;
      
      ret = CallJScript (L"getResult", paramArray, &pReturnResult);

      bool bNeedRefresh = false; 
      if( pReturnResult.vt == VT_NULL)
      {
         bNeedRefresh = false;
      }

      CString strReturnResult (_bstr_t(pReturnResult).Detach ());
      DString dstrReturnResult = strReturnResult;

      bNeedRefresh = dstrReturnResult.strip() == I_("-1") ? true : false;

      if (!dstrLastAccountNum.empty() && bNeedRefresh)
      {
         getParent()->refresh (this, I_("RefreshAccount"));
         PostMessage (WM_SYSCOMMAND, SC_CLOSE);
      }
      else
      {
         PostMessage( WM_COMMAND, IDCANCEL );
      }
   }
   else if ( buttonId == "btnClose" )
   {
      PostMessage( WM_COMMAND, IDCANCEL );
   }
   else if ( buttonId == "btnTransactionDetails" )
   {
      LaunchTransactionDetails();
   }
   else if ( buttonId == "btnHistorical" )
   {
      LaunchHistoricalPayments();
   }
   else if ( buttonId == "btnAcctDetail" )
   {
      LaunchAccounttDetail();
      PostMessage( WM_COMMAND, IDCANCEL );
   }   
   else
   {
      /**
       * Generic screen launcher
       *
       * btnLaunch<index> - to make it unquie
       *
       * <name_of_job>  plus attributes starting with the word desktop will
       * be scrapped and sent as parameters - the case is important,
       *
       * <input type="button"
       *        value="Fee Rebate Details"
       *        id="btnLaunch1"
       *        desktopORGID="BPROC_MANAGEMENT_FEE_REBATE_DETAILS"
       *        desktopBrowserTitle="Management Fee Rebate Details - Fee ID 1234"
       *        desktopFeeID="1234"/>
       *
       * OR
       *
       * <button value="Fee Details"
       *         id="btnLaunch2"
       *         desktopORGID="BPROC_MANAGEMENT_FEE_ID"
       *         desktopBrowserTitle="Management Fee Details - Fee ID 5678"
       *         desktopFeeID="5678"/>
       *
       * OR a C++ screen
       *
       * <input type="button"
       *        value="Trans Dtls"
       *        id="btnLaunch3"
       *        desktopORGID="BPROC_TRANS_HISTORY"
       *        desktopAccountNum="2029"/>
       *
       *
       * Cancel Button - close window
       *
       * <input id="btnCancel"
       *        type="button"
       *        value="Cancel"
       *        style="width:80;"/>
       *
       */

      DString dstrButtonId( buttonId );

      // note we do a 'pos' cause we have btnLaunch1, btnLaunch2 etc...
      int iPos = dstrButtonId.pos( I_( "btnLaunch" ) );

      if ( iPos != -1 )
      {
         // get the button object from the document
         IHTMLDocument2 *document = GetDocument();

         if ( document )
         {
            IHTMLElement* pElem = FindElement( buttonId, document );

            if ( pElem )
            {
               // collect the parameters
               CString desktopBrowserTitle, desktopORGID;

               GetElementAttribute( pElem, "desktopBrowserTitle", desktopBrowserTitle );
               GetElementAttribute( pElem, "desktopORGID",        desktopORGID );

               if ( CString::StringLength( desktopORGID ) > 0 )
               {
                  launchProcessFromWebTag( desktopBrowserTitle, desktopORGID, pElem );

                  // now call a refresh on the original caller screen...
                  CStringArray paramArray;
                  CComVariant pVarResult;
                  CallJScript( "doRefresh", paramArray, &pVarResult );
               }
               else
               {
                  CString cstrError;
                  cstrError.LoadString(TXT_BTN_LAUNCH_ERROR);
                  AfxMessageBox( cstrError );
               }
            }
         }
      }
   }

   return (true);
}

//******************************************************************************
void BrowserLaunch::launchProcessFromWebTag( CString browserTitle, CString ORGID, IHTMLElement* pElem )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION,
                          CLASSNAME,
                          I_( "launchWebScreen( CString, CString, IHTMLElement * )" ) );

   DString processName;

   processName = ORGID;

   setParameter( I_("ORG_CMDID"),      processName );
   setParameter( I_( "CalledFrom" ),   I_("BrowserLaunch") );
   setParameter( I_( "BrowserTitle" ), DString( browserTitle ) );

   m_fromScreen = DString( I_( "BROWSERLAUNCH" ) );
   m_orgCommand = processName;

   DString dstStatusBarText = (DString( I_( "Launching " ) ) + DString( browserTitle ) + DString( I_( "..." ) ) );

   SetMessageStatusBar( dstStatusBarText.c_str() );

   // get parameters based on config file... hopefully we can change InterProcessData in bfproc
   // one day to allow us to grab paramters from there when we are calling processes....
   // and also add the ability to generically scrap the attributes of the input or button
   // tag in the HTML to setParamter to the process....   And, it would be nice to have
   // just one standard browser screen process.... in a perfect world... it might be that way.

   processParametersFromWebTagAttributes( pElem );

   try
   {
      bool bModal = true;   // Default to modeless
      E_COMMANDRETURN eRtn = CMD_OK;

      eRtn = invokeCommand( getParent(), ORGID, PROC_NO_TYPE, bModal, NULL );

      SetMessageStatusBar( NULL_STRING );

      switch ( eRtn )
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
   catch ( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch ( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

}

//******************************************************************************
void BrowserLaunch::ProcessBtnElems()
{
   DString pageName = getParent()->getCommand().getWebPageName();

   // P0263049 T86138 Obsolete code. 
   /*if (pageName == I_("PaymentSearch_MainScreen"))
   {
      ProcessBtnElem("btnTransactionDetails");
      ProcessBtnElem("btnHistorical");
   }*/

   ProcessBtnElem("btnTransactionDetails");
   ProcessBtnElem("btnOK");
   ProcessBtnElem("btnCancel");
   ProcessBtnElem("btnClose");
   ProcessBtnElem("btnConfirmDlg");
   ProcessBtnElem("btnAcctDetail");

   // generic desktop screen launching
   ProcessBtnElem("btnLaunch");
   ProcessBtnElem("btnLaunch0");
   ProcessBtnElem("btnLaunch1");
   ProcessBtnElem("btnLaunch2");
   ProcessBtnElem("btnLaunch3");
   ProcessBtnElem("btnLaunch4");
   ProcessBtnElem("btnLaunch5");
   ProcessBtnElem("btnLaunch6");
   ProcessBtnElem("btnLaunch7");
   ProcessBtnElem("btnLaunch8");
   ProcessBtnElem("btnLaunch9");
   ProcessBtnElem("btnLaunch10");
}

//******************************************************************************
void BrowserLaunch::ProcessBtnElem(CString elementName)
{
   IHTMLElement* pElem = NULL;
   IHTMLDocument2 *tmpdocument = GetDocument();
   if ( tmpdocument )
   {
      pElem = FindElement( elementName, tmpdocument );

      if ( pElem )
      {
         ConnectBtnEvents( pElem, elementName );
         pElem->Release();
      }
      tmpdocument->Release();
   }
}

//******************************************************************************
void BrowserLaunch::FindLists(CString strListName )
{
   IHTMLDocument2 *tmpdocument = GetDocument();

   if ( tmpdocument )
   {
      IHTMLElement* pElem = FindElement(strListName, tmpdocument );
      tmpdocument->Release();
      BSTR innerHTML;
      if ( pElem )
      {
         pElem->get_innerHTML( &innerHTML );
         pElem->Release();

         CString cstrList = CString(_bstr_t(innerHTML).Detach ());
         int index = cstrList.Find(TEXT("<rows>"));
         if ( index != -1 )
         {
            CString value = cstrList.Right(CString::StringLength(cstrList) - index - 6);
            int nspace = value.Find(TEXT("</rows>"));
            if ( nspace != -1 )
            {
               value = value.Left(nspace);
            }
            cstrList = value;
         }
         AfxMessageBox( cstrList );
      }
      //use XMLparser parse this XML, fill list data
      //<row>....</row>......<row>....</row>
   }
}

//******************************************************************************
IHTMLElement* BrowserLaunch::FindElement(CString strElemName, IHTMLDocument2 *pdocument)
{
   HRESULT hr;
   IHTMLElement* pElem;
   try
   {
      if ( pdocument )
      {
         IHTMLElementCollection* pElemColl = NULL;
         hr = pdocument->get_all(&pElemColl);
         if ( SUCCEEDED(hr)&& pElemColl!=NULL )
         {
            _variant_t varIdx = 0;
            IDispatch* pElemDisp = NULL;

            VARIANT varID;
            VariantInit(&varID);
            varID.vt = VT_BSTR;
            varID.bstrVal = _bstr_t(strElemName);

            hr = pElemColl->item(varID, varIdx, &pElemDisp);
            if ( SUCCEEDED(hr) && pElemDisp!=NULL )
            {
               hr = pElemDisp->QueryInterface(IID_IHTMLElement, (void**)&pElem);
               if ( SUCCEEDED(hr) )
               {
                  VariantClear(&varID);
                  pElemDisp->Release();
                  pElemColl->Release();
                  return (pElem);
               }
               pElemDisp->Release();
            }
            VariantClear(&varID);
            pElemColl->Release();
         }
      }
   }
   catch ( ... )
   {
      //it is not an element name, can not found in the document.
   }
   return (NULL);
}

//******************************************************************************
void BrowserLaunch::ConnectBtnEvents(IHTMLElement* pElem, CString elementName )
{
   if ( pElem )
   {
      EVENT_HANDLER_MAP_ITER eventHandlerMapIter = m_buttonHndMap.find( elementName );

      if ( eventHandlerMapIter != m_buttonHndMap.end( ) )
      {
         //Element event attached already.
         delete (*eventHandlerMapIter).second;
         m_buttonHndMap.erase( eventHandlerMapIter );

      }

      // add to map
      IButtonEventHandler * m_pIButtonEventHandler = new IButtonEventHandler(*this, pElem, &BrowserLaunch::OnButtonEventInvoke);
      m_buttonHndMap.insert( EVENT_HANDLER_MAP::value_type( elementName, m_pIButtonEventHandler ));

   }
}

//******************************************************************************
STDMETHODIMP BrowserLaunch::QueryInterface( REFIID riid, void **ppvObject )
{
   if ( riid == IID_IUnknown )
   {
      *ppvObject = (IUnknown*)this;
      AddRef();
      return (S_OK);
   }

   if ( riid == IID_IDispatch )
   {
      *ppvObject = (IDispatch*)this;
      AddRef();
      return (S_OK);
   }

   return (E_NOINTERFACE);
}

//******************************************************************************
STDMETHODIMP_(ULONG) BrowserLaunch::AddRef(void)
{
   return (++m_cRef);
}

//******************************************************************************
STDMETHODIMP_(ULONG) BrowserLaunch::Release(void)
{
   return (--m_cRef);
}

//******************************************************************************
STDMETHODIMP BrowserLaunch::GetTypeInfoCount(UINT* /*pctinfo*/)
{
   return (E_NOTIMPL);
}

//******************************************************************************
STDMETHODIMP BrowserLaunch::GetTypeInfo(
                                       /* [in] */ UINT /*iTInfo*/,
                                       /* [in] */ LCID /*lcid*/,
                                       /* [out] */ ITypeInfo** /*ppTInfo*/)
{
   return (E_NOTIMPL);
}

//******************************************************************************
STDMETHODIMP BrowserLaunch::GetIDsOfNames(
                                         /* [in] */ REFIID riid,
                                         /* [size_is][in] */ OLECHAR** rgszNames,
                                         /* [in] */ UINT cNames,
                                         /* [in] */ LCID lcid,
                                         /* [size_is][out] */ DISPID* rgDispId)
{
   HRESULT hr = NOERROR;
   return (hr);
}

//******************************************************************************
bool BrowserLaunch::LaunchConfirmation()
{
   bool ret = false;
   setParameter( I_( "CalledFrom" ), I_("BrowserLaunch") );
   if ( CMD_OK == invokeCommand( this, CMD_BPROC_CONFIRMATION,
                                 PROC_NO_TYPE, true, NULL ) )
   {
      ret = true;
      if ( getParent()->cancel( this ) )
      {
         SetCancelInProgress();
         PostCancel( true );
         Exit( IDCANCEL );
         //EndDialog( IDCANCEL );
      }
   }
   return (ret);
}

//******************************************************************************
bool BrowserLaunch::LaunchTransactionDetails()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("LaunchTransactionDetails" ) );

   bool ret = false;
   CStringArray paramArray;
   CComVariant pAccountNum, pTransNum, pFundCode, pClassCode, pTransId;

   ret = CallJScript(L"getAccountNum", paramArray, &pAccountNum);
   if ( pAccountNum.vt == VT_NULL )
      return (false);
   CString strAccountNum (_bstr_t(pAccountNum).Detach ());

   ret = CallJScript(L"getTransNum", paramArray, &pTransNum);
   if ( pTransNum.vt == VT_NULL )
      return (false);
   CString strTransNum (_bstr_t(pTransNum).Detach ());

   ret = CallJScript(L"getFundCode", paramArray, &pFundCode);
   if ( pFundCode.vt == VT_NULL )
      return (false);
   CString strFundCode (_bstr_t(pFundCode).Detach ());

   ret = CallJScript(L"getClassCode", paramArray, &pClassCode);
   if ( pClassCode.vt == VT_NULL )
      return (false);
   CString strClassCode (_bstr_t(pClassCode).Detach ());

   ret = CallJScript(L"getTransId", paramArray, &pTransId);
   if ( pTransId.vt == VT_NULL )
      return (false);
   CString strTransId (_bstr_t(pTransId).Detach ());

   setParameter( I_( "CalledFrom" ), I_("BrowserLaunch") );
   setParameter( ACCOUNT_NUM, DString(strAccountNum) );
   setParameter( TRANSNUM, DString(strTransNum) );
   setParameter( FUND_CODE, DString(strFundCode) );
   setParameter( CLASS_CODE, DString(strClassCode) );
   setParameter( PENDING, NO );
   setParameter( ALL_FUND_MODE, NO );
   setParameter ( REQ_TRANS_ID, DString(strTransId));
   //setParameter ( TXNLEVELSEC, I_("Y"));

   try
   {
      bool bModal = true;   // Default to modeless
      E_COMMANDRETURN eRtn = CMD_OK;
      eRtn = invokeCommand( getParent(), CMD_BPROC_TRANS_HISTORY, PROC_NO_TYPE, bModal, NULL );
      SetMessageStatusBar( NULL_STRING );
      switch ( eRtn )
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
   catch ( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch ( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

   return (ret);
}

//******************************************************************************
bool BrowserLaunch::LaunchHistoricalPayments()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("LaunchHistoricalPayments"));

   bool ret = false;
   CStringArray paramArray;
   CComVariant pAuditRecid;

   ret = CallJScript(L"getAuditRecid", paramArray, &pAuditRecid);
   if (pAuditRecid.vt != VT_NULL)
   {
      CString strAuditRecid (_bstr_t(pAuditRecid).Detach ());
      DString urlParamsIDI;

      addIDITagValue (urlParamsIDI, I_("auditRecid"), DString(strAuditRecid));
      setParameter (I_("CalledFrom"),  I_("BrowserLaunch"));
      setParameter (I_("from_screen"), I_("BrowserLaunch"));
      CString cstrHistoricalPayment;
      cstrHistoricalPayment.LoadString(TXT_HISTORICAL_PAYMENT);
      setParameter (I_("BrowserTitle"),DString(cstrHistoricalPayment));  
      setParameter (I_("UrlParams"), urlParamsIDI);

      try
      {
         bool bModal = true;   // Default to modeless
         E_COMMANDRETURN eRtn = CMD_OK;
         eRtn = invokeCommand (getParent(), CMD_BPROC_HISTORICAL_PAYMENTS, PROC_NO_TYPE, bModal, NULL);
         SetMessageStatusBar (NULL_STRING);
         switch ( eRtn )
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
      catch (ConditionException &ce)
      {
         ConditionMessageBox (ce);
      }
      catch ( ... )
      {
         DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      }
   }
   return (ret);
}

//******************************************************************************
HRESULT BrowserLaunch::OnButtonEventInvoke ( IButtonEventHandler* pEventButtonHandler,
                                             DISPID dispidMember,
                                             REFIID riid,
                                             LCID lcid,
                                             WORD wFlags,
                                             DISPPARAMS* pdispparams,
                                             VARIANT* pvarResult,
                                             EXCEPINFO* pexcepinfo,
                                             UINT* puArgErr )
{
   CString buttonId = "";
   buttonId = pEventButtonHandler->getElementId();

   switch ( dispidMember )
   {
      case DISPID_HTMLELEMENTEVENTS_ONCLICK:
         OnBtnClick(buttonId);
         break;
      default:
         break;
   }
   return (S_OK);
}

//******************************************************************************
//StatusCode, one of HTTP_STATUS_XXX enums
void BrowserLaunch::OnNavigateError(short wbUID, LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* TargetFrameName, VARIANT FAR* StatusCode, BOOL FAR* Cancel)
{
   if ( StatusCode->vt == VT_I4 ) //LONG
   {
      switch ( StatusCode->lVal )
      {
         case HTTP_STATUS_CONTINUE:
         case HTTP_STATUS_ACCEPTED:
         case HTTP_STATUS_OK:
         case HTTP_STATUS_REDIRECT:
         case HTTP_STATUS_REQUEST_TIMEOUT: //Allow default timeout page to display
            {
               *Cancel = VARIANT_FALSE;
            }
            break;
         default:
            {
               TCHAR tmp[50];
            #ifdef UNICODE
               _ltow(StatusCode->lVal, tmp, 10);
            #else
               _ltoa(StatusCode->lVal, tmp, 10);
            #endif
               CString strTmp(_T("Navigation Error #"));
               strTmp += tmp;
               strTmp += _T(". Procceed?");
               if ( MessageBox(strTmp, _T("Navigate Error Confirmation"), MB_YESNO | MB_ICONWARNING) == IDYES )
               {
                  *Cancel = VARIANT_FALSE;
               }
            }
      }
   }

}

/*
//******************************************************************************
HRESULT BrowserLaunch::OnInputTextEventInvoke
(
  IInputTextEventHandler* pInputTextEventHandler,
  DISPID dispidMember,
  REFIID riid,
  LCID lcid,
  WORD wFlags,
  DISPPARAMS* pdispparams,
  VARIANT* pvarResult,
  EXCEPINFO* pexcepinfo,
  UINT* puArgErr
)
{
  switch (dispidMember)
  {
   case DISPID_HTMLELEMENTEVENTS_ONCLICK:
      OnBtnClick();
      break;
    default:
        break;
  }
  return S_OK;
}
*/

//******************************************************************************
void BrowserLaunch::SetupConnectionPoint()
{
   IConnectionPointContainer*   pIConnectionPointContainerTemp = NULL;
   IUnknown*              pIUnknown = NULL;

   // QI this object itself for its IUnknown pointer which will be used
   // later to connect to the Connection Point of the device_interface object.
   this -> QueryInterface(IID_IUnknown, (void**)&pIUnknown);

   if ( pIUnknown )
   {
      // QI the pdevice_interface for its connection point.
      IUnknown*  pUnk = m_Browser_Launch.GetControlUnknown();
      ASSERT(pUnk);
      pUnk->QueryInterface (IID_IConnectionPointContainer, (void**)&pIConnectionPointContainerTemp);

      if ( pIConnectionPointContainerTemp )
      {
         pIConnectionPointContainerTemp -> FindConnectionPoint(DIID_DWebBrowserEvents2 , &_pIConnectionPoint);
         pIConnectionPointContainerTemp -> Release();
         pIConnectionPointContainerTemp = NULL;
      }

      if ( _pIConnectionPoint )
      {
         _pIConnectionPoint -> Advise(pIUnknown, &_dwEventCookie);
      }

      pIUnknown -> Release();
      pIUnknown = NULL;
   }
}

//******************************************************************************
void BrowserLaunch::OnOK()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION,
                           CLASSNAME,
                           I_("OnOK")
                         );

   // PMI - OK button was removed as it lead to user confusion with web screen
   // OK buttons

}

//******************************************************************************
bool BrowserLaunch::haveUpdate()
{
   bool ret = false;
   CStringArray paramArray;
   CComVariant pUpdate;

   ret = CallJScript(L"getUpdateStatus", paramArray, &pUpdate);

   if ( ret && pUpdate.vt != VT_NULL )
   {
      CString strupdate (_bstr_t(pUpdate).Detach ());
      DString dstrupdate = strupdate;
      if ( dstrupdate == I_("-1") )
         return (true);
   }
   return (false);
}

//******************************************************************************
bool BrowserLaunch::LaunchConfirm()
{
   bool ret = false;
   CStringArray paramArray;
   CComVariant pUpdate;

   ret = CallJScript(L"LaunchConfirm", paramArray, &pUpdate);

   if ( ret && pUpdate.vt != VT_NULL )
   {
      CString strupdate (_bstr_t(pUpdate).Detach ());
      DString dstrupdate = strupdate;
      if ( dstrupdate == I_("-1") )
         return (true);
   }
   return (false);
}

//******************************************************************************
bool BrowserLaunch::LaunchAccounttDetail()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("LaunchAccounttDetail"));

   bool ret = false;
   CStringArray paramArray;
   CComVariant pAccountNum;

   ret = CallJScript(L"getAccountNum", paramArray, &pAccountNum);
   if ( pAccountNum.vt == VT_NULL )
      return (false);
   CString strAccountNum (_bstr_t(pAccountNum).Detach ());
   DString dstrAccountNum(strAccountNum);

   setParameter( I_( "CalledFrom" ), I_("BrowserLaunch") );
   setParameter( ACCOUNT_NUM, dstrAccountNum );
   dstrAccountNum.strip().upperCase();

   if(!dstrAccountNum.empty() && hasReadPermission( UAF::ACCOUNT_DETAIL ))
   {
      GenericInterface* rpGIWorkSession = NULL;  
      GenericInterface* pUserSessionProcess = getWorkSession()->getParent();

      BFSession *pBFSession = pUserSessionProcess->getBFSession();
      DSTCUserSession *pDSTCUserSession = dynamic_cast<DSTCUserSession*>(pBFSession);
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if(dstWorkSession)
      {
         AccountEntityXref *pAccountEntityXref;
         if( dstWorkSession->getAccountEntityXref( BF::HOST, pAccountEntityXref ) <= WARNING )
         {
            DString entityId;
            //get the entity id which is the account holder with sequence 1
            if( pAccountEntityXref->PopulateAccountOwner( BF::HOST, NULL_STRING, dstrAccountNum ) <= WARNING 
               && pAccountEntityXref->GetEntityIdForAccountOwnerSequence1( dstrAccountNum, BF::HOST, entityId ) <= WARNING )
            {
               setParameter( I_("AccountNum"), dstrAccountNum );
               setParameter( I_("EntityId"), entityId );
               setParameter (I_("from_screen"), I_("BrowserLaunch"));

               try
               {
                  bool bModal = true;   // Default to modeless
                  E_COMMANDRETURN eRtn = CMD_OK;

                  eRtn = CommandDispatcher::getInstance()->invokeCommand( getWorkSession(), 
                                                                        CMD_BPROC_ACC_DETAILS, 
                                                                        PROC_NO_TYPE, 
                                                                        false, 
                                                                        //true,
                                                                        NULL );
                  SetMessageStatusBar( NULL_STRING );
                  switch ( eRtn )
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
               catch ( ConditionException &ce )
               {
                  ConditionMessageBox( ce );
               }
               catch ( ... )
               {
                  DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
               }
            }
            else
            {
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            }
         }
      }
   }

   return (ret);
}


//******************************************************************************
void BrowserLaunch::SaveDesktopWebURLToFile(const CString& strUrl)
{
    CStdioFile mFileDesktopWebURL;

	if (mFileDesktopWebURL.Open(m_strFilePathForDesktopWebURL, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
	{
		CString strStarLine = "*********************************************************************************";
		mFileDesktopWebURL.SeekToEnd();
		mFileDesktopWebURL.WriteString(strUrl + "\r\n");
		mFileDesktopWebURL.WriteString(strStarLine + "\r\n");
	}
}

//******************************************************************************
void BrowserLaunch::customResize()
{
   WINDOWPLACEMENT tmp, wpBrowser;
   const CStatusBar *pStatusBar = &m_statusBar;
   const CWnd *pWebBrowser = GetDlgItem(IDC_BROWSER_LAUNCH);

   CRect origParentSize;
   ::GetWindowRect( this->GetSafeHwnd(), &origParentSize);

   int _offsetX = 47;
   int _offsetY = 93;

   if(pStatusBar && pWebBrowser) // make sute that only browserlaunch dlg will need to adjust statusbar
   {
      RECT rctStatus, rctBrowser;
      pStatusBar->GetWindowRect(&rctStatus);
      pWebBrowser->GetWindowRect(&rctBrowser);
      CSize szeTitleBar(rctStatus.right-rctStatus.left, rctBrowser.top-origParentSize.top);
      CSize szeStatus(rctStatus.right-rctStatus.left, rctStatus.bottom-rctStatus.top);
      CSize szeBrowser(rctBrowser.right-rctBrowser.left, rctBrowser.bottom-rctBrowser.top);
      CSize szeParent(origParentSize.right-origParentSize.left, origParentSize.bottom-origParentSize.top);

      LONG offsetCY = szeStatus.cy < 0 ? -szeStatus.cy : szeStatus.cy;

//      if(szeBrowser.cy > 550) _offsetY += 10;

      // resize screen
      tmp.length = sizeof(WINDOWPLACEMENT);
      GetWindowPlacement (&tmp);

      long gapOffset = (szeBrowser.cy + offsetCY) - (tmp.rcNormalPosition.bottom - tmp.rcNormalPosition.top - szeTitleBar.cy);
      tmp.rcNormalPosition.right  += _offsetX;
      tmp.rcNormalPosition.bottom += (gapOffset + offsetCY); 
      tmp.rcNormalPosition.bottom += _offsetY;

      SetWindowPlacement (&tmp);

      CRect clientRect; 
      GetClientRect(&clientRect); 

      CRect currCtrlSize; 
      currCtrlSize.left = 0;
      currCtrlSize.right = clientRect.Width();
      currCtrlSize.top    = clientRect.Height()- 18;	   
      currCtrlSize.bottom = clientRect.Height();	   
      const_cast<CStatusBar*>(pStatusBar)->MoveWindow(currCtrlSize, TRUE);

      currCtrlSize.top = 0;
      currCtrlSize.bottom = clientRect.Height() - 18;
      const_cast<CWnd*>(pWebBrowser)->MoveWindow(currCtrlSize, TRUE);
      
      RepositionBars( AFX_IDW_STATUS_BAR, AFX_IDW_STATUS_BAR, 0 );

      /*
      // resize browser control
      wpBrowser.length = sizeof(WINDOWPLACEMENT);
      pWebBrowser->GetWindowPlacement (&wpBrowser);
      wpBrowser.rcNormalPosition.right += _offsetX;
      wpBrowser.rcNormalPosition.bottom += _offsetY;
      const_cast<CWnd*>(pWebBrowser)->SetWindowPlacement (&wpBrowser);

      CStatusBar *pMovableStatusBar = const_cast<CStatusBar*>(pStatusBar);
      if(pMovableStatusBar)
      {
         // resize status bar and adjust position
         WINDOWPLACEMENT tmpStatus;
         tmpStatus.length = sizeof(WINDOWPLACEMENT);
         pMovableStatusBar->GetWindowPlacement (&tmpStatus);
         tmpStatus.rcNormalPosition.right = tmpStatus.rcNormalPosition.left + szeStatus.cx + _offsetX;
         tmpStatus.rcNormalPosition.top = tmp.rcNormalPosition.bottom - offsetCY;
         tmpStatus.rcNormalPosition.bottom = tmpStatus.rcNormalPosition.top + offsetCY;
         tmpStatus.rcNormalPosition.bottom += _offsetY;
         tmpStatus.showCmd = SW_SHOW;
         pMovableStatusBar->SetWindowPlacement (&tmpStatus);

         RepositionBars( AFX_IDW_STATUS_BAR, AFX_IDW_STATUS_BAR, 0 );
      }
*/
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BrowserLaunch.cpp-arc  $
// 
//    Rev 1.59   Aug 10 2012 12:23:20   popescu
// IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
// 
//    Rev 1.58   Aug 10 2012 12:20:52   popescu
// IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
// 
//    Rev 1.57   Aug 09 2012 14:21:04   dchatcha
// IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
// 
//    Rev 1.56   Feb 23 2012 12:06:50   popescu
// Desktop/French added language parameter to the WebUrl
// 
//    Rev 1.55   Feb 22 2012 04:48:54   panatcha
// IN2831230 - Fund limitation update not displaying in option window box
// 
//    Rev 1.54   Jan 18 2012 17:30:24   wp040027
// P0188394_Performance Fees - Launching valuation dtl/Sharelot Screens
// 
//    Rev 1.53   Nov 25 2011 15:56:50   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.52   Nov 21 2011 18:39:50   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.51   Nov 19 2011 01:47:40   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.50   Nov 02 2011 09:57:50   dchatcha
// P0181953 FN01 - TFSA Amendment - revise account refreshing logic, fix code that make infinite loop.
// 
//    Rev 1.49   Oct 28 2011 22:35:46   dchatcha
// IN# 2708991 - RL 12.1_REG_Fund Class Limitation Options are not refreshing.
// 
//    Rev 1.48   Oct 28 2011 22:23:10   dchatcha
// P0181953 FN01 - TFSA Amendment - revise account refreshing logic.
// 
//    Rev 1.47   Oct 27 2011 14:22:50   dchatcha
// P0188150 FN01 & FN02 - IWT Enhancement, redirect environment default DSKURL to developer server in debug mode
// 
//    Rev 1.46   Sep 16 2011 12:10:22   dchatcha
// P0181953 FN01 - TFSA Amendment - Remove specific interprocess parameter passing.
// 
//    Rev 1.45   Sep 16 2011 11:15:58   dchatcha
// P0186477 FN01 - GIA Enhancements, remove portfolio screen specific.
// 
//    Rev 1.44   Sep 14 2011 23:30:18   popescu
// PET186484 - Global Search - added the list of envs to url for global search
// 
//    Rev 1.43   Aug 25 2011 17:57:14   dchatcha
// P0186477 FN01 - GIA Enhancements, force browser screen close after finishing update, otherwise, the screen would send new 'add' record instead 'mod' for modified one.
// 
//    Rev 1.42   Aug 10 2011 15:51:18   dchatcha
// P0165541 FN03 - Roll back to use GET method instead POST, include several code changes on other issues as well, missing character in variable name.
// 
//    Rev 1.41   Aug 10 2011 14:52:32   dchatcha
// P0165541 FN03 - Roll back to use GET method instead POST, include several code changes on other issues as well.
// 
//    Rev 1.40   Jul 29 2011 11:02:04   dchatcha
// P0181953 FN01 - TFSA Amendment- integration test, bring code change in branch to trunk.
// 
//    Rev 1.39   Apr 29 2011 09:37:16   jankovii
// IN 2511918 - Desktop refresh not working properly with SF
// 
//    Rev 1.38   Mar 11 2011 10:57:52   dchatcha
// Restore 1.34 for R11.2_SSBL and later
// 
//    Rev 1.37   Mar 11 2011 10:47:46   dchatcha
// Restore 1.35
// 
//    Rev 1.36   Mar 11 2011 10:15:04   dchatcha
// PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen, recheck in after reverting code.
// 
//    Rev 1.35   Feb 28 2011 13:24:10   jankovii
// Rolled out code fix for incident 2151337.
//
//    Rev 1.34   Jan 14 2011 16:50:18   dchatcha
// PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen.
// 
//    Rev 1.33   Nov 22 2010 17:57:24   popescu
// Incident 2151337 - Using POST instead of Get - added the color param back
// 
//    Rev 1.32   Nov 15 2010 22:29:18   popescu
// Incident 2151337 - Using POST instead of Get
// 
//    Rev 1.31   Oct 21 2009 15:31:50   purdyech
// Missed code from original checkin
// 
//    Rev 1.30   Oct 21 2009 10:29:30   purdyech
// LDAP Authorization Support
// 
//    Rev 1.29   20 Aug 2009 15:25:56   popescu
// 95  - ACL replacement project - 
// 
//    Rev 1.28   Aug 04 2009 17:51:58   purdyech
// Get CompanyURL from MgmtCoOptions instead of DSTCSecurity as field moved from View 1 to View 149 due to ACL Migration to Base.
// 
//    Rev 1.27   17 Jul 2009 14:08:14   walkerro
// PET156681 FN03 - Postal Code Lookup on address screen
// 
//    Rev 1.26   06 Dec 2007 15:20:18   popescu
// Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
// 
//    Rev 1.25   Aug 16 2007 10:40:14   jankovii
// Sync up for inicidnet 954084.
// 
//    Rev 1.24   Aug 12 2007 15:57:08   ivespaul
// PET2360 - Web Integration - call JavaScript function doRefresh() when returning from a launched screen.  This allows the caller screen to be refreshed to reflect any changes made to the database.
//
//    Rev 1.23   Aug 10 2007 11:49:10   ivespaul
// PET2360 - Web Integration.
//
//    Rev 1.22   Jun 05 2007 17:41:42   smithdav
// Fix bug introduced in last revision. The historical button on the payments screen was not invoking the desktop event.
//
//    Rev 1.21   May 16 2007 10:26:12   ivespaul
// Incident #885542 - New env setup for destkop web and cleanup.
//
//    Rev 1.20   Apr 20 2007 13:52:22   smithdav
// Remove call out to Confirmation screen that doesn't work, and add close events for btnOK, btnCancel, and btnClose elements.
//
//    Rev 1.19   Apr 19 2007 18:00:38   smithdav
// Removed dialog button handling. Added support for Historical Payments screen. Use "id" attribute instead of "name" attribute on the event lookups.
//
//    Rev 1.18   Mar 26 2007 09:16:14   jankovii
// PET 2303 FN01 - Payment Release.
//
//    Rev 1.17   Feb 13 2007 14:58:04   jankovii
// As per Paul Ives request removed # before colour, so that right color value is passed to the browser.
//
//    Rev 1.16   Jan 23 2007 14:46:16   fengyong
// #incident 807693 - add market to url
//
//    Rev 1.15   Jan 11 2007 18:31:50   porteanm
// Incident 778724 - Convert the URL from Unicode to ASCII
//
//    Rev 1.14   Dec 19 2006 16:56:40   fengyong
// PET2282 FN01 - Add Clone Account web page
//
//    Rev 1.12   Nov 27 2006 16:28:50   fengyong
// #incident 735041 - modify envname and companycode
//
//    Rev 1.10   Oct 19 2006 16:01:38   fengyong
// Incident 735041 - Add parameters
//
//    Rev 1.9   Oct 19 2006 15:30:30   fengyong
// Incident #735041 - Add more parameters needed in web page
//
//    Rev 1.8   Oct 13 2006 14:40:04   fengyong
// Sync up with web infra change
//
//    Rev 1.7   Oct 02 2006 14:33:58   fengyong
// Fix refresh problem
//
//    Rev 1.5   Aug 29 2006 16:39:52   fengyong
// PET2192 FN17 - Add transaction detail button to payment search screen
//
//    Rev 1.3   Aug 28 2006 11:02:00   fengyong
// PET2192 FN17 - temp check in before error page done.
//
//    Rev 1.2   Aug 23 2006 14:52:52   fengyong
// temp check in for PET 2192
//
//    Rev 1.1   Jun 20 2006 14:42:02   fengyong
// small change
//
//    Rev 1.0   Jun 08 2006 14:01:28   fengyong
// Initial revision.
 */
