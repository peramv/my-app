//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2013 by International Financial, Inc.
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "AWDHistoryDialog.h"
#include <ifastbp\awdhistoryprocessincludes.h>
#include <uibase\dstlistctrl.h>
#include <bf/log/log.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_AWDHISTORY;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AWDHistoryDialog > dlgCreator( CMD_GUI_AWDHISTORY );

namespace
{
   const I_CHAR *CLASSNAME             = I_( "AWDHistoryDialog" );
   const I_CHAR * const LST_WORKOBJ        = I_("WorkObjectList");
   const I_CHAR * const LST_SRCIMAGE       = I_("SourceImageList");
}


namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AWDWorkListHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId AWDSourceListHeadingSet;
}


BEGIN_MESSAGE_MAP(AWDHistoryDialog, BaseMainDlg)
//{{AFX_MSG_MAP(AWDHistoryDialog)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
AWDHistoryDialog::AWDHistoryDialog( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AWDHistoryDialog::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//--------------------------------------------
SEVERITY AWDHistoryDialog::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

//   getParameter( I_("DisplayType"), DisplayType );

   sevRtn = NO_CONDITION;
   return(sevRtn);
}
//-------------------------------------------------

void AWDHistoryDialog::OnPostInitDialog()
{

   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog")); 


   AddListControl( CLASSNAME, IDC_LST_WORKOBJ, LST_WORKOBJ, ifds::AWDWorkListHeadingSet,
                   IFASTBP_PROC::AWDWORK_LIST, 0, true, 
                   LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE);

   AddListControl( CLASSNAME, IDC_LST_SRCIMAGE, LST_SRCIMAGE, ifds::AWDSourceListHeadingSet,
                   IFASTBP_PROC::AWDSOURCE_LIST, IDC_LST_WORKOBJ, true, 
                   LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE);
   
   doRefresh(this, NULL);

}

//---------------------------------------------------------------------------
BOOL AWDHistoryDialog::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();

   UpdateData(FALSE);
//   DispInfo();
   ShowWindow(SW_SHOW);

   return(TRUE);
}

//----------------------------------------------------------------------------

void AWDHistoryDialog::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AWDHistoryDialog)
   DDX_Control(pDX, IDC_AWD_IMAGE_BROWSER, m_AwdImageBrowser);
   //}}AFX_DATA_MAP


}

//************************************************************************************
void AWDHistoryDialog::DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem )
{

   bf::log::LogStream ls( bf::log::gui );
   ls << bf::log::ltrace;
   ls << I_("AWDHistoryDialog: Change list item ") << strKey << bf::log::endlf;

   IUnknown* pUnk = m_AwdImageBrowser.GetControlUnknown();

   if ( pUnk != NULL ) {

      VARIANT varEmpty;
      varEmpty.vt =  VT_EMPTY;


      try {
         m_AwdImageBrowser.Navigate(L"about:blank", &varEmpty, &varEmpty, &varEmpty, &varEmpty);
      } catch (const std::exception &exc) {
         ls << bf::log::severe << I_("AWDHistoryDialog: Catch nav to about:blank :") <<  DStringA(exc.what()) << bf::log::endlf;
      } catch (const std::string &str) {
         ls << bf::log::severe << I_("AWDHistoryDialog: Catch nav to about:blank :") <<  DString(str) << bf::log::endlf;
      } catch(...) {
         ls << bf::log::severe << I_("AWDHistoryDialog: Catch nav to about:blank : ...") << bf::log::endlf;
      }

      try {
         do {
            MSG msg;
            Sleep(50);
            while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
            {
               TranslateMessage( &msg);
               DispatchMessage( &msg );
            }
         } while( m_AwdImageBrowser.GetBusy() );
      } catch (const std::exception &exc) {
          ls << bf::log::severe << I_("AWDHistoryDialog: Catch wait for about:blank :") <<  DStringA(exc.what()) << bf::log::endlf;
      } catch (const std::string &str) {
         ls << bf::log::severe << I_("AWDHistoryDialog: Catch wait for about:blank :") <<  DString(str) << bf::log::endlf;
      } catch(...) {
         ls << bf::log::severe << I_("AWDHistoryDialog: Catch wait for about:blank : ...") << bf::log::endlf;
      }

      if ( listControlID == IDC_LST_SRCIMAGE ) {

         DString strImageUrl;
         getParent()->getField( this, IFASTBP_PROC::AWDSOURCE_LIST, ifds::AWDImageURL, strImageUrl );

         DString strImageAuth;
         getParent()->getField( this, BF::NullContainerId, AWDHIST_PROC::AWDImageAuth, strImageAuth );

         CString strUrl = strImageUrl.c_str();

//         CString authData = "ZHN0c2V0dXA6ZHN0c2V0dXA=";
         CString authData = strImageAuth.c_str();
         CString authHeader = "Authorization: Basic " + authData + "\r\n";

         try {
            m_AwdImageBrowser.Navigate(strUrl.AllocSysString(), &varEmpty, &varEmpty, &varEmpty, COleVariant(authHeader));
         } catch (const std::exception &exc) {
            AfxMessageBox( _T("Failed to load image"), MB_OK );
            ls << bf::log::severe << I_("AWDHistoryDialog: Catch nav to Image :") <<  DStringA(exc.what()) << bf::log::endlf;
         } catch (const std::string &str) {
            AfxMessageBox( _T("Failed to load image"), MB_OK );
            ls << bf::log::severe << I_("AWDHistoryDialog: Catch nav to Image :") <<  DString(str) << bf::log::endlf;
         } catch(...) {
            AfxMessageBox( _T("Failed to load image"), MB_OK );
            ls << bf::log::severe << I_("AWDHistoryDialog: Catch nav to Image : ...") << bf::log::endlf;
         }
      }
   } else {
      AfxMessageBox( _T("Failed to load image"), MB_OK );
      ls << bf::log::severe << I_("AWDHistoryDialog: Browser control not found : ...") << bf::log::endlf;
   }

}


//************************************************************************************
bool AWDHistoryDialog::doRefresh(
                                GenericInterface * /*rpGICaller*/, 
                                const I_CHAR * //*szOriginalCommand
                                )
{  

   LoadListControl(IDC_LST_WORKOBJ);
   LoadListControl(IDC_LST_SRCIMAGE);

   GetList(IDC_LST_WORKOBJ)->SetFocus();

   ShowWindow(SW_SHOW);

   return(true);
}

