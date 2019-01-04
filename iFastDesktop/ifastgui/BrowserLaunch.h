
#ifndef BrowserLaunch_H
#define BrowserLaunch_H
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
// ^FILE   : BrowserLaunch.h
//
// ^CLASS    : BrowserLaunch
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : This is the code for the FYI screen
//
//******************************************************************************

//{{AFX_INCLUDES()
#include <ifastgui\webbrowser.h>
#include <ifastgui\animation.h>
//}}AFX_INCLUDES

#ifndef BASEMAINDLG_H
   #include <ifastgui\basemaindlg.h>
#endif

#include "comdef.h"
#include "mshtml.h"
#include "mshtmcid.h"
#include "MSHTMDID.H"
#include "mshtmhst.h"
#include "exdispid.h"
#include "TEventHandler.h"
#include "WININET.H"

using namespace TEventHandlerNamespace;

#define CSC_NAVIGATEFORWARD 1
#define CSC_NAVIGATEBACK    2

class BrowserLaunch;
typedef TEventHandler<BrowserLaunch, IHTMLElement, HTMLButtonElementEvents> IButtonEventHandler;
//typedef TEventHandler<BrowserLaunch, IHTMLElement, HTMLInputTextElementEvents> IInputTextEventHandler;

class BrowserLaunch : public BaseMainDlg, public IDispatch
{
// Construction
public:
   BrowserLaunch(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   virtual ~BrowserLaunch();

   STDMETHODIMP QueryInterface(REFIID, void **);
   STDMETHODIMP_(ULONG) AddRef(void);
   STDMETHODIMP_(ULONG) Release(void);
   //IDispatch
   STDMETHODIMP GetTypeInfoCount(UINT* pctinfo);
   STDMETHODIMP GetTypeInfo(/* [in] */ UINT iTInfo,
       /* [in] */ LCID lcid,
       /* [out] */ ITypeInfo** ppTInfo);
   STDMETHODIMP GetIDsOfNames(
       /* [in] */ REFIID riid,
       /* [size_is][in] */ LPOLESTR *rgszNames,
       /* [in] */ UINT cNames,
       /* [in] */ LCID lcid,
       /* [size_is][out] */ DISPID *rgDispId);

   /**
     * Required implementation for the refresh method.  No refresh activity is
     * performed for this class.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(GenericInterface * /*rpGICaller*/,
                          const I_CHAR * /*szOriginalCommand*/)
   {  // Nothing to refresh here
      return(true);
   }
   HRESULT GetPostData(LPVARIANT pvPostData);

   bool updatesAlreadyPeformed();

   IHTMLDocument2 *GetDocument();
   // Get attribute of given name from of given HTML element
   BOOL GetElementAttribute(IHTMLElement *pElement,const CString & attName ,CString &value);
   // Get id of given element
   BOOL GetElementId(IHTMLElement* pElement, CString &strId);
   // Get name of given element
   BOOL GetElementName (IHTMLElement* pElement, CString &strName);
   // Get value of given element
   BOOL GetElementValue (IHTMLElement* pElement, CString &value);
   BOOL SetElementValue (IHTMLElement* pElement, CString &value);
   BOOL SetElementAttribute(IHTMLElement *pElement,const CString & attName ,CString &value);
   bool CallJScript(const CString strFunc, const CStringArray& paramArray,CComVariant* pVarResult);

   BOOL IsSelect(BSTR tag);
   BOOL IsImg(BSTR tag);
   BOOL IsImage(BSTR tag);
   BOOL IsTextArea( BSTR tag);
   BOOL IsInput( BSTR tag);
   BOOL IsButton( BSTR tag);
   int IsControl(BSTR tag);
   int GetControlType(BSTR name);
   STDMETHODIMP Invoke(DISPID dispidMember,
                                REFIID riid,
                                LCID lcid,
                                WORD wFlags,
                                DISPPARAMS* pdispparams,
                                VARIANT* pvarResult,
                                EXCEPINFO* pexcepinfo,
                                UINT* puArgErr);
   bool OnBtnClick( const CString& buttonId = "" );
   void ProcessBtnElems();
   void ProcessBtnElem(CString elementName);
   void ConnectBtnEvents (IHTMLElement* pElem, CString elementName );
   IHTMLElement* FindElement(CString strElemName, IHTMLDocument2 *pdocument );
   void FindLists(CString strListName );
   bool LaunchConfirmation();
   bool LaunchTransactionDetails();
   bool LaunchHistoricalPayments();
   void SetHomeFocus();                                           // method to set focus on home key
   void GetUrl(CString& strUrl);
   virtual SEVERITY doInit();
   void processParameters();
   DString& getParameters() { return m_parameters; }
   void LaunchWebPage();
   virtual void OnOK();
   bool haveUpdate();
   bool LaunchConfirm();
   bool LaunchAccounttDetail();
// Dialog Data
   //{{AFX_DATA(BrowserLaunch)
   enum
   {
      IDD = IDD_BROWSER_LAUNCH
   };
   CWebBrowser m_Browser_Launch;
   //CAnimation  m_Animate;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(BrowserLaunch)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Generated message map functions
   //{{AFX_MSG(BrowserLaunch)
   virtual BOOL OnInitDialog();
   afx_msg void OnWebback();
   afx_msg void OnWebfwd();
   afx_msg void OnWebhome();
   afx_msg void OnWebstop();
   afx_msg void OnCommandStateChange(long Command, BOOL Enable);
   afx_msg void OnDownloadBegin();
   afx_msg void OnDownloadComplete();
   afx_msg void OnDocumentComplete(LPDISPATCH lpDisp,VARIANT FAR* URL);
   afx_msg void OnPropertyChange( BSTR szProperty );
   afx_msg void OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel);
   afx_msg void OnNavigateComplete2(LPDISPATCH lpDisp,VARIANT FAR* URL);
   afx_msg void OnWindowClosing(short wbUID, BOOL IsChildWindow, BOOL FAR* Cancel);
   afx_msg void OnNavigateError(short wbUID, LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* TargetFrameName, VARIANT FAR* StatusCode, BOOL FAR* Cancel);
   DECLARE_EVENTSINK_MAP()
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   HRESULT BrowserLaunch::OnButtonEventInvoke
   (
      IButtonEventHandler* pButtonEventHandler,
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS* pdispparams,
      VARIANT* pvarResult,
      EXCEPINFO* pexcepinfo,
      UINT* puArgErr
   );

   /*HRESULT BrowserLaunch::OnInputTextEventInvoke
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
   );
    IInputTextEventHandler * m_pIInputTextHandler;*/
   void customResize();
private:

   void resetSessionId();

   void launchProcessFromWebTag( CString browserTitle, CString ORGID, IHTMLElement* pElem );

   void processParametersFromWebTagAttributes( IHTMLElement* pElem );

   void buildPostParams();
   void GetPageUrl(CString& strUrl);
   void SaveDesktopWebURLToFile(const CString& strUrl);

   LPDISPATCH  _topLevelFrame;

   HWND         m_hwndParent;       // Parent window handle
   CString      m_csFileDir;        // Path to data files
   DString      m_orgCommand, 
                m_parameters, 
                m_pagename, 
                m_BrowserTitle, 
                m_fromScreen,
                m_urlParams;
   ULONG        m_cRef;

   typedef std::map< CString, IButtonEventHandler * > EVENT_HANDLER_MAP;
   typedef EVENT_HANDLER_MAP::iterator          EVENT_HANDLER_MAP_ITER;
   EVENT_HANDLER_MAP m_buttonHndMap;

   IConnectionPoint*       _pIConnectionPoint;  // Ref counted of course.
   DWORD                _dwEventCookie;
   void SetupConnectionPoint();

   bool _blUpdatesAlreadyPerformed;

   CString m_strFilePathForDesktopWebURL;
   CString m_strViewLogPath;
};

#endif // BrowserLaunch_H
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BrowserLaunch.h-arc  $
//
//   Rev 1.21   Aug 10 2012 12:21:00   popescu
//IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
//
//   Rev 1.20   Sep 16 2011 12:08:44   dchatcha
//P0181953 FN01 - TFSA Amendment - Remove specific interprocess parameter passing.
//
//   Rev 1.19   Aug 10 2011 14:51:48   dchatcha
//P0165541 FN03 - Roll back to use GET method instead POST, include several code changes on other issues as well.
//
//   Rev 1.18   Jul 11 2011 07:45:20   dchatcha
//P0181953 FN01 - TFSA Amendment- integration test.
//
//   Rev 1.17   Mar 11 2011 10:56:24   dchatcha
//Restore 1.12 for R11.2_SSBL and later
//
//   Rev 1.16   Mar 11 2011 10:45:04   dchatcha
//Restore 1.13
//
//   Rev 1.15   Mar 11 2011 10:31:00   dchatcha
//PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen, recheck in after reverting code.
//
//   Rev 1.14   Mar 11 2011 10:10:44   dchatcha
//PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen, recheck in after reverting code.
//
//   Rev 1.13   Feb 28 2011 13:23:00   jankovii
//Rolled out code fix for incident 2151337.
//
//   Rev 1.12   Jan 14 2011 16:47:32   dchatcha
//PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen.
//
//   Rev 1.11   Nov 22 2010 17:57:46   popescu
//Incident 2151337 - Using POST instead of Get - added the color param back
//
//   Rev 1.10   Oct 21 2009 15:33:38   purdyech
//Missed code from original checkin
//
//   Rev 1.9   Oct 21 2009 10:30:54   purdyech
//LDAP Authorization Support
//
//   Rev 1.8   06 Dec 2007 15:20:20   popescu
//Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
//
//   Rev 1.7   Aug 10 2007 11:49:22   ivespaul
//PET2360 - Web Integration.
//
//   Rev 1.6   May 14 2007 11:18:20   ivespaul
//Incident #885542 - New env setup for destkop web and cleanup.
//
//   Rev 1.5   Apr 19 2007 18:00:52   smithdav
//Removed dialog button handling. Added support for Historical Payments screen. Use "id" attribute instead of "name" attribute on the event lookups.
//
//   Rev 1.4   Dec 19 2006 16:56:46   fengyong
//PET2282 FN01 - Add Clone Account web page
//
//   Rev 1.3   Dec 06 2006 14:57:02   fengyong
//Incident #763433 - refresh account detail after ok on fund limitation page
//
//   Rev 1.2   Aug 29 2006 16:40:04   fengyong
//PET2192 FN17 - Add transaction detail button to payment search screen
//
//   Rev 1.1   Aug 23 2006 14:53:08   fengyong
//temp check in for PET 2192
//
//   Rev 1.0   Jun 08 2006 14:01:40   fengyong
//Initial revision.
 *
 */