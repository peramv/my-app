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
// ^FILE   : BaseDlg.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 12/98
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BaseDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  : This is the base dialog class.
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"

#include "BaseDlg.h"
#include <bfproc\AbstractProcess.hpp>
#include "BaseControl.hpp"
#include "DSTButton.h"
#include "DSTComboBox.h"
#include "DSTDateTime.h"
#include "DSTEdit.h"
#include "DSTStatic.h"
#include "DSTTimerListCtrl.h"
#include <bfdata\bfdatafieldproperties.hpp>
#include "DSTGridWnd.h"
#include "DSTTabCtrl.h"
#include "bfcontrolfactory.hpp"
#include "bfdefaultcontrolfactory.hpp"
#include <assert.h>
#include "ifdslistctrl.h"
#include <bfutil/localetraits.hpp>
#include "ScrollHelper.h"
#include "DlgResizeHelper.h"


#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   // Literals for tracing
   const I_CHAR * const CLASSNAME = I_( "BaseDlg" ); 

   const I_CHAR * const ADDCONTROL = I_( "AddControl" );
   const I_CHAR * const ADDFUNDCLASSEDITCONTROL = I_( "AddFundClassEditControl" );
   const I_CHAR * const ADDLISTCONTROL = I_( "AddListControl" );
   const I_CHAR * const ADDTOLISTCONTROL = I_( "AddToListControl" );
   const I_CHAR * const CONNECTCONTROLTODATA = I_( "ConnectControlToData" );
   const I_CHAR * const CONNECTCONTROLSTODATA = I_( "ConnectControlsToData" );
   const I_CHAR * const CONNECTLISTTODATA = I_( "ConnectListToData" );
   const I_CHAR * const DELETEFROMLISTCONTROL = I_( "DeleteFromListControl" );
   const I_CHAR * const DOPOSTINITDIALOG = I_( "DoPostInitDialog" );
   const I_CHAR * const GETCONTROLTEXT = I_( "GetControlText" );
   const I_CHAR * const GETPARENTPROCESS = I_( "getParentProcess" );
   const I_CHAR * const LISTITEMCHANGED = I_( "ListItemChanged" );
   const I_CHAR * const LOADCHILDLISTCONTROLS = I_( "LoadChildListControls" );
   const I_CHAR * const LOADCONTROL = I_( "LoadControl" );
   const I_CHAR * const LOADCONTROLERRORSTATE = I_( "LoadControlErrorState" );
   const I_CHAR * const LOADCONTROLS = I_( "LoadControlS" );
   const I_CHAR * const LOADLISTCONTROL = I_( "LoadListControl" );
   const I_CHAR * const PROCESSCONTROLS = I_( "ProcessControls" );
   const I_CHAR * const SETACCOUNT = I_("SetAccount" );
   const I_CHAR * const SETCONTROLTEXT = I_( "setControlText" );
   const I_CHAR * const SETCUSTOMERNAME = I_( "SetCustomerName" );
   const I_CHAR * const SETFUND = I_( "SetFund" );
   const I_CHAR * const WINDOWPROC = I_( "WindowProc" );
   const I_CHAR * const ADDGRIDCONTROL = I_( "AddGridControl" );
   const I_CHAR * const ADDTABCONTROL = I_( "AddTabControl" );
   const I_CHAR * const LOADTABCONTROL = I_( "LoadTabControl" );
   const I_CHAR * const HEIGHT = I_( "Height" );
   const I_CHAR * const WIDTH = I_( "Width" );
   const I_CHAR *WORKSTATION = I_( "WORKSTATION" );
}

namespace BASEDLGVARIABLES
{  // This namespace is used for common trace literals and other text
   //  literals used by dialogs.
   // Note that the trace literals are meant to be used with TRACE_METHOD.
   //  If you use MAKEFRAME you should create your own local literals
   //  preceded with MF_.
   // Trace literals
   const I_CHAR * const CANCEL = I_( "Cancel" );
   const I_CHAR * const CLEARCONTROLS = I_( "ClearControls" );
   const I_CHAR * const DISPLAYLIST = I_( "DisplayList" );
   const I_CHAR * const DODATAEXCHANGE = I_( "DoDataExchange" );
   const I_CHAR * const OK = I_( "Ok" );
   const I_CHAR * const ONBTNCHANGE = I_( "OnBtnChange" );
   const I_CHAR * const ONBTNDELETE = I_( "OnBtnDelete" );
   const I_CHAR * const ONBTNMORE = I_( "OnBtnMore" );
   const I_CHAR * const ONBTNSAVE = I_( "OnBtnSave" );
   const I_CHAR * const ONCANCEL = I_( "OnCancel" );
   const I_CHAR * const ONINITDIALOG = I_( "OnInitDialog" );
   const I_CHAR * const ONOK = I_( "OnOK" );
   const I_CHAR * const ONPOSTINITDIALOG = I_( "OnPostInitDialog" );
   const I_CHAR * const ONDBLCLKLBATTRIB = I_( "OnDblclkLbAttrib" );//yakov
   const I_CHAR * const PREOK = I_( "PreOk" );  
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId ModPerm;
   extern CLASS_IMPORT const BFTextFieldId AddPerm;
   extern CLASS_IMPORT const BFTextFieldId DelPerm;

}
#define SC_DEFAULT_SIZE         0x0002
BFControlFactory* BaseDlg::s_pControlFactory_ = BFDefaultControlFactory::getInstance();

//******************************************************************************
//              Public Methods
//******************************************************************************

BaseDlg::BaseDlg( UINT IDD,
                  CWnd *rpParentWindow,
                  GenericInterfaceContainer* pGIC,
                  GenericInterface* pGIParent,
                  const Command& rCommand,
                  const DString &dialogName )
: CDialog( IDD, rpParentWindow )
, GenericInterface( pGIC, pGIParent, rCommand )
, m_bCancelInProgress( false )
, m_IDD( IDD )
, m_rpLastControlWithFocus( NULL )
, m_rpParent( rpParentWindow )
, m_pUserAccesFunctionCode(NULL)
,_bSizing( false )
,_bScroll( false )
,m_scrollHelper (NULL)
,m_resizeHelper (NULL)
,m_dialogName (dialogName)
,m_pFont(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   // The following code depends on DSTCView being created first
   POSITION pos;
   pos = AfxGetApp()->GetFirstDocTemplatePosition();
   CDocTemplate *pDocTemp = AfxGetApp()->GetNextDocTemplate( pos );
   pos = pDocTemp->GetFirstDocPosition();
   CDocument *pDoc = pDocTemp->GetNextDoc( pos );
   pos = pDoc->GetFirstViewPosition();
   m_pDSTCView = pDoc->GetNextView( pos );
//activate the scroller 
   m_scrollHelper = new CScrollHelper;
	m_scrollHelper->AttachWnd(this);
//activate the resizer
	m_resizeHelper = new DlgResizeHelper;
}

//******************************************************************************

BaseDlg::~BaseDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   CROSSEDITS_ITER ceEnd = m_crossEdits.end();
   CONTROL_ITER cEnd = m_controls.end();

   for( CROSSEDITS_ITER ceIter = m_crossEdits.begin(); ceIter != ceEnd; ceIter++ )
   {
      delete ( *ceIter ).second;
   }
   m_crossEdits.clear();

   for( CONTROL_ITER cIter = m_controls.begin(); cIter != cEnd; cIter++ )
   {
      delete ( *cIter ).second;
   }
   m_controls.clear();
   m_orderedControls.clear();

   for( int i = 0; i < m_lists.size(); i++ )
   {
      delete m_lists[i];
   }
   m_lists.clear();

   for( GRID_ITER gIter = m_Grids.begin(); gIter != m_Grids.end(); gIter++ )
   {
      delete ( *gIter ).second;
   }
   m_Grids.clear();

   for( int i = 0; i < m_tabs.size(); i++ )
   {
      delete m_tabs[i];
   }
   m_tabs.clear();

   if (m_scrollHelper)
   {
      delete m_scrollHelper;
      m_scrollHelper = NULL;
   }
   if (m_resizeHelper)																									
   {
      delete m_resizeHelper;
      m_resizeHelper = NULL;
   }
}

//******************************************************************************
CWnd* BaseDlg::GetNextDlgTabItem(CWnd* pWndCtl, BOOL bPrevious ) const
{
   return(CDialog::GetNextDlgTabItem( pWndCtl, bPrevious ));
}
//******************************************************************************

// return true when you provide the strOut. this function must be overwritten by the derived dlg class
// to provide strOut for the listview column that does not associated with 
// a view field
bool BaseDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{
   return(false);
}

//******************************************************************************

E_COMMANDRETURN BaseDlg::process()
{
   EXECHISTI(I_("process()"));
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !hasProcessRun() )
      {
         setProcessHasRun( true );
         rtn = doProcess();
      }
      else
      {
         ASSERT( 0 );
      }
   }
   catch( ... )
   {
      ASSERT( 0 );
      throw;
   }
   return(rtn);
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool BaseDlg::doModelessSetFocus(
                                GenericInterface *rpGICaller
                                )
{
   EXECHISTI(I_("doModelessSetFocus( GenericInterface *rpGICaller") );
   bool bRtn = false;

   if( IsWindow( m_hWnd ) )
   {
      SetFocus();
      ShowWindow( SW_RESTORE );
      bRtn = true;                  
   }
   else
   {
      ASSERT( 0 );  // Why wasn't the window valid?
   }
   return(bRtn);
}

//******************************************************************************

LRESULT BaseDlg::DoPostInitDialog( WPARAM wParam,
                                   LPARAM lParam)
{
   EXECHISTI( I_("DoPostInitDialog( WPARAM wParam, LPARAM lParam )" ) );

   UpdateWindow();         // Try to force screen paint - for partial paints
   OnPostInitDialog();
   CheckPermission();

   setUpdateFlag (false);  

	{
		HMENU lSysMenu = ::GetSystemMenu(this->m_hWnd, false);
		::AppendMenu(lSysMenu, MF_SEPARATOR,0,I_(""));
		::AppendMenu(lSysMenu, MF_STRING,SC_DEFAULT_SIZE,I_("Default Size") );

		::DrawMenuBar(this->m_hWnd);
		::UpdateWindow( this->m_hWnd );
	}	

   return true;
}

//******************************************************************************
void BaseDlg::InitResizing ()
{   
//initialize the resizer
   EXECHISTI(I_("InitResizing()") );
   m_resizeHelper->Init (this->m_hWnd, this);

   int height = -1, width = -1;
//resize the dialog based on registries
   LoadDialogSize (width, height);
//resize the screen, as well
   m_resizeHelper->OnSize (width, height);

   if (width != -1 && height != -1)
   {
      WINDOWPLACEMENT tmp;
      
      GetWindowPlacement (&tmp);
      tmp.rcNormalPosition.right = tmp.rcNormalPosition.left + width;
      tmp.rcNormalPosition.bottom = tmp.rcNormalPosition.top + height;
      SetWindowPlacement (&tmp);

      customResize();
   }
//initialize the scroller
   if (height == -1 && width == -1)
   {
      GetWindowRect (&wndRect);
      height = wndRect.Height();
      width  = wndRect.Width();
   }
   m_scrollHelper->SetDisplaySize (width, height);
}

//******************************************************************************
void BaseDlg::LoadDialogSize (int &width_, int &height_)
{
   EXECHISTI( I_("LoadDialogSize(int& width, int& height)" ) );
   width_ = -1;
   height_ = -1;
//also thw controls in the window needs to resized
   if (!GetDialogName ().empty ())
   {
		if (IsBrowserBasedDialog())
		{
			Command cmd = getParent()->getCommand();

//			ModifyStyle(WS_THICKFRAME, WS_BORDER, SWP_FRAMECHANGED);// | SWP_NOSIZE);

			if (-1 != cmd.getWindowHeight() &&
				-1 != cmd.getWindowWidth())
			{
				height_ = cmd.getWindowHeight();
				width_ = cmd.getWindowWidth();
			}
			else
			{
				GetWindowSizeFromRegistry(width_, height_);
			}
		}
		else
		{
			GetWindowSizeFromRegistry(width_, height_);
		}
	}   
}

//******************************************************************************
void BaseDlg::GetWindowSizeFromRegistry(int &width_, int &height_)
{
	ConfigManager *pWorkstation = ConfigManager::getManager (WORKSTATION);
	Configuration workstation = pWorkstation->retrieveConfig (GetDialogName ());

	DString height = workstation.getValueAsString (HEIGHT), 
	width = workstation.getValueAsString (WIDTH);

	if (!height.empty () && !width.empty ())
	{
		height_ = asInteger (height);
		width_ = asInteger (width);
	}
}

//******************************************************************************
void BaseDlg::SaveDialogSize ()
{
   EXECHISTI( I_("SaveDialogSize()") );
//save the size
   if (!GetDialogName ().empty ())
   {
      ConfigManager *pWorkstation = ConfigManager::getManager (WORKSTATION);
      Configuration workstation = pWorkstation->retrieveConfig (GetDialogName ());
   //save the window configuration   
      GetWindowRect (&wndRect);
      DString strHold (WIDTH);

      strHold += I_("=");
      strHold += asString (wndRect.Width());
      workstation.set (strHold);
      strHold = HEIGHT;
      strHold += I_("=");
      strHold += asString (wndRect.Height());
      workstation.set (strHold);
      pWorkstation->storeConfig( workstation );
      pWorkstation->persist();   // Throws on bad reg config
   }
}

//******************************************************************************
AbstractProcess *BaseDlg::getParentProcess()
{
   EXECHISTI( I_("GetParentProcess()") );
   AbstractProcess *rpPtr = dynamic_cast< AbstractProcess * >( getParent() );
   if( !rpPtr )
   {
      assert( 0 );
// TODO - make better condition
      THROWFROMFILE2( CND::GUI_CONDITION, CLASSNAME, GETPARENTPROCESS,
                      CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(rpPtr);
}

//******************************************************************************

void BaseDlg::SetAccount(                    // Set current account
                                             const DString &acct                      // Account to set
                        )
{
   TRACE_METHOD( CLASSNAME, SETACCOUNT );
   m_account = acct;
   stripLeading( m_account, '0' );
}

//******************************************************************************

void BaseDlg::SetCustomerName(               // Set current customer name
                                             const DString &name                      // Name to set
                             )
{
   TRACE_METHOD( CLASSNAME, SETCUSTOMERNAME );
   m_customerName = name;
}

//******************************************************************************

void BaseDlg::SetFund(                       // Set current fund
                                             const DString &fund                      // Fund to set
                     )
{
   TRACE_METHOD( CLASSNAME, SETFUND );
   m_fund = fund;
   stripLeading( m_fund, '0' );
}

//******************************************************************************

void BaseDlg::addBtnAddForPermissionCheck(UINT nID, int nListCtrlID /*=-1*/)
{
   TRACE_METHOD( CLASSNAME, I_("addBtnAddForPermissionCheck") );

   bool bAlreadyThere = false;
   std::vector< int >::iterator iter = m_AddButtons.begin( );
   while( iter != m_AddButtons.end( ) )
   {
      if( (*iter) == nID )
      {
         bAlreadyThere =true;
         break;
      }
      ++iter;
   }
   if( !bAlreadyThere )
      m_AddButtons.push_back( nID );
   if( nListCtrlID != -1 )
      addControlGroupIDForPermissionCheck(nListCtrlID);
   //register this button with its list control, even if list control ID is -1
   btnToListCtrlIter = m_mapBtnToListCtrl.find(nID);
   if( btnToListCtrlIter == m_mapBtnToListCtrl.end() )//new entry
      m_mapBtnToListCtrl.insert(BTN_TO_LIST_CTRL::value_type(nID, nListCtrlID));
}

//******************************************************************************

void BaseDlg::addBtnDeleteForPermissionCheck(UINT nID, int nListCtrlID /*=-1*/)
{
   TRACE_METHOD( CLASSNAME, I_("addBtnDeleteForPermissionCheck") );

   bool bAlreadyThere = false;
   std::vector< int >::iterator iter = m_DelButtons.begin( );
   while( iter != m_DelButtons.end( ) )
   {
      if( (*iter) == nID )
      {
         bAlreadyThere =true;
         break;
      }
      ++iter;
   }
   if( !bAlreadyThere )
      m_DelButtons.push_back( nID );
   if( nListCtrlID != -1 )
      addControlGroupIDForPermissionCheck(nListCtrlID);
   //register this button with its list control, even if list control ID is -1
   btnToListCtrlIter = m_mapBtnToListCtrl.find(nID);
   if( btnToListCtrlIter == m_mapBtnToListCtrl.end() )//new entry
      m_mapBtnToListCtrl.insert(BTN_TO_LIST_CTRL::value_type(nID, nListCtrlID));

}

//******************************************************************************

void BaseDlg::addControlGroupIDForPermissionCheck(int nListCtrlID)
{
   TRACE_METHOD( CLASSNAME, I_("addListCtrlForPermissionCheck") );
   assert(nListCtrlID>=0);
   listCtrlIter = m_mapListCtrlNewItem.find(nListCtrlID);
   if( listCtrlIter == m_mapListCtrlNewItem.end() )//new entry
      m_mapListCtrlNewItem.insert(LIST_CTRL_TO_BOOL::value_type(nListCtrlID,false));
}

//******************************************************************************

void BaseDlg::removeBtnAddFromPermissionCheck(UINT nID)
{
   TRACE_METHOD( CLASSNAME, I_("removeBtnAddForPermissionCheck") );
   std::vector< int >::iterator iter = m_AddButtons.begin( );
   while( iter != m_AddButtons.end( ) )
   {
      if( (*iter) == nID )
      {
         m_AddButtons.erase(iter);
         break;
      }
      ++iter;
   }
   btnToListCtrlIter = m_mapBtnToListCtrl.find(nID);
   if( btnToListCtrlIter != m_mapBtnToListCtrl.end() )//button found
      m_mapBtnToListCtrl.erase(btnToListCtrlIter);
}

//******************************************************************************

void BaseDlg::removeBtnDeleteFromPermissionCheck(UINT nID)
{
   TRACE_METHOD( CLASSNAME, I_("removeBtnDeleteForPermissionCheck") );
   std::vector< int >::iterator iter = m_DelButtons.begin( );
   while( iter != m_DelButtons.end( ) )
   {
      if( (*iter) == nID )
      {
         m_DelButtons.erase(iter);
         break;
      }
      ++iter;
   }
   btnToListCtrlIter = m_mapBtnToListCtrl.find(nID);
   if( btnToListCtrlIter != m_mapBtnToListCtrl.end() )//button found
      m_mapBtnToListCtrl.erase(btnToListCtrlIter);
}

//******************************************************************************

void BaseDlg::removeControlGroupIDFromPermissionCheck(int nListCtrlID)
{
   TRACE_METHOD( CLASSNAME, I_("removeListCtrlFromPermissionCheck") );

   listCtrlIter = m_mapListCtrlNewItem.find(nListCtrlID);
   if( listCtrlIter != m_mapListCtrlNewItem.end() ) //found
   {
      m_mapListCtrlNewItem.erase(listCtrlIter);
   }

}
//******************************************************************************

void BaseDlg::changeBtnToListCtrlAssociation(UINT nID, int nListCtrlID /*=-1*/, bool bRemoveOldControlGroupIDFromPermCheck /*= false*/)
{
   TRACE_METHOD( CLASSNAME, I_("changeBtnToListCtrlAssociation") );

   //remove old assoc.
   btnToListCtrlIter = m_mapBtnToListCtrl.find(nID);
   if( btnToListCtrlIter != m_mapBtnToListCtrl.end() )//button found
   {
      //just an optimisation; if it was called with the same nListCtrlID, return
      if( (*btnToListCtrlIter).second == nListCtrlID )
         return;
      //if we want to remove the old list control from permission check
      if( bRemoveOldControlGroupIDFromPermCheck )
         removeControlGroupIDFromPermissionCheck((*btnToListCtrlIter).second);
      m_mapBtnToListCtrl.erase(btnToListCtrlIter);
   }
   //add new assoc., even if nListCtrlID == -1
   btnToListCtrlIter = m_mapBtnToListCtrl.find(nID);
   if( btnToListCtrlIter == m_mapBtnToListCtrl.end() )//new entry
      m_mapBtnToListCtrl.insert(BTN_TO_LIST_CTRL::value_type(nID, nListCtrlID));
   addControlGroupIDForPermissionCheck(nListCtrlID);
}

//******************************************************************************

void BaseDlg::CheckPermission()
{
   TRACE_METHOD( CLASSNAME, I_("CheckPermission") );

   CWnd *pWnd;

   bool bMod = false;
   bool bAdd = false;
   bool bDel = false;

   if( m_pUserAccesFunctionCode != NULL )
   {
      bMod = hasUpdatePermission( m_pUserAccesFunctionCode );
      bAdd = hasCreatePermission( m_pUserAccesFunctionCode );
      bDel = hasDeletePermission( m_pUserAccesFunctionCode );
   }

   // 1. 'MODIFY' permission check
   //iterate through each registered list control; 
   listCtrlIter = m_mapListCtrlNewItem.begin();
   while( listCtrlIter != m_mapListCtrlNewItem.end() )
   {
      int nControlGroupID = (*listCtrlIter).first;

      if( isValidListCtrl(nControlGroupID) )
      {
         if( !(GetList( nControlGroupID )->IsDataConnected()) )
         {
            listCtrlIter++;
            continue;
         }
      }

      bool bIsNew = (*listCtrlIter).second;

      //if we'll ever have updateable list controls, uncomment the following line
      //GetList(nControlGroupID)->SetCtrlReadOnly( (!bMod && !bIsNew) || (!bAdd && bIsNew) );

      //enable/disable it's children controls (does not include DSTGridWindows ...)
      for( CONTROL_ITER iter = m_controls.begin(); iter != m_controls.end(); iter++ )
         CheckCtrlForReadOnly( ( *iter ).second, nControlGroupID, bIsNew, bMod, bAdd);

      //enable/disable DSTGridWindows
      for( GRID_ITER iter1 = m_Grids.begin(); iter1 != m_Grids.end(); iter1++ )
         CheckCtrlForReadOnly( ( *iter1 ).second, nControlGroupID, bIsNew, bMod, bAdd, true);

      listCtrlIter++;
   }

   // 2. 'ADD' permission check
   std::vector< int >::iterator iter = m_AddButtons.begin( );
   while( iter != m_AddButtons.end( ) )
   {
      pWnd = NULL;
      pWnd = GetDlgItem(*iter);
      //give a chance to the derived class to apply some bussiness rules for 'Add' and 'Delete' buttons
      bool bDisable = doDisablePermCheckButton(*iter);
      if( pWnd ) pWnd->EnableWindow(bAdd & !bDisable);
      ++iter;
   }

   // 3. 'DELETE' permission check
   //security check for deleting a new object does not apply
   iter = m_DelButtons.begin( );
   while( iter != m_DelButtons.end( ) )
   {
      pWnd = NULL;
      pWnd = GetDlgItem(*iter);
      if( pWnd )
      {
         bool bIsNew = false;
         btnToListCtrlIter = m_mapBtnToListCtrl.find(*iter);
         if( btnToListCtrlIter != m_mapBtnToListCtrl.end() )//button found
         {
            int nListCtrlID = (*btnToListCtrlIter).second;
            bool bDisable = false;

            if( nListCtrlID == 0 )
               //Btn not associated with any list control
               pWnd->EnableWindow(bDel);
            else if( isValidListCtrl(nListCtrlID) )
            {
               if( GetList(nListCtrlID)->GetItemCount() )//else ask derived class for instructions
                  bDisable = doDisablePermCheckButton(*iter);
               else
                  bDisable = true;//disable delete button if there are no items in the list
            }
            if( nListCtrlID != 0 )//association found
            {
               listCtrlIter = m_mapListCtrlNewItem.find(nListCtrlID);
               if( listCtrlIter != m_mapListCtrlNewItem.end() ) //found
                  bIsNew = (*listCtrlIter).second ;
               else
                  //list not in m_mapListCtrlNewItem; this really shouldn't happen
                  assert(0);
               if( bIsNew )
                  pWnd->EnableWindow(!bDisable);//always can delete a new item, even for no permission, unless if not allowed by the derived class
               else
                  pWnd->EnableWindow(bDel & !bDisable);
            }
         }
         else
            //button not in m_mapBtnToListCtrl; this really shouldn't happen
            assert(0);

      }
      ++iter;
   }

   //this has nothing to do with permission, but it is an apropriate place for the derived class to apply 
   //some bussiness rules for buttons that were not added for permission check (such as RESET)
   doDisableNonPermButtons();
}
//******************************************************************************

void BaseDlg::CheckCtrlForReadOnly(BaseControl *rpCtrl, int nControlGroupID, bool bIsNew,bool bMod, bool bAdd, bool bIsGrid /*= false*/)
{
   if( rpCtrl->GetControlGroupID() != nControlGroupID )//this control's parent is not our list control (or zero)
      return;

   //if control not connected return
   if( !rpCtrl->IsConnected() ) return;
   if( !rpCtrl->IsEnabled() ) return;
   //if (!rpCtrl->IsVisible()) return;
   if( !bIsGrid )
      if( !rpCtrl->IsDataConnected() ) return;

   DSTEdit *pEdit = NULL;
   pEdit = dynamic_cast<DSTEdit *>(rpCtrl);

   bool bEnableControls;
   if( !rpCtrl->IsControlUpdateable() ) //this will skip DSTStatic...
      bEnableControls = false;
   else if( pEdit && pEdit->IsSetAsReadOnly() ) // if an edit control was SetReadOnly() by the developer keep it readonly
      bEnableControls = false;
   else
   {
      AbstractProcess *pAbstrProc = NULL;
      pAbstrProc = dynamic_cast<AbstractProcess*>(getParent());
      assert(pAbstrProc);
      BFContainerId idContainer = rpCtrl->GetContainerID();

      if( nControlGroupID == 0 )//orphan control
         bIsNew = pAbstrProc->isCurrentListItemNew( this, idContainer );

      if( (!bMod && !bIsNew) || (!bAdd && bIsNew) )
         bEnableControls = false;
      else
         bEnableControls = true;

      //if this control is to be enabled, 
      if( bEnableControls )
      {
         //if grid, don't have to check the field's state; it is done by the grid
         if( !bIsGrid )
         {
            //if field was set as read only in CBO, be sure to disable the control
            const BFProperties* pProp = NULL;
            BFFieldId idField = rpCtrl->GetFieldID();
            if( idField != ifds::NullFieldId )
            {
               pProp = pAbstrProc->getFieldAttributes(this, idContainer, idField);
               if( pProp )
                  bEnableControls = !pProp->isReadOnly();
            }
         }
         //if the control is still to be enabled, ask the derived class if for some reason it should be disabled
         if( bEnableControls )
            bEnableControls = !doDisableControl(rpCtrl->GetControlID(), bIsNew);
      }
   }
   rpCtrl->SetCtrlReadOnly(!bEnableControls); 
}

//******************************************************************************
//              Message Handlers
//******************************************************************************

BEGIN_MESSAGE_MAP(BaseDlg, CDialog)
//{{AFX_MSG_MAP(BaseDlg)
ON_MESSAGE(UM_POSTINITDIALOG, DoPostInitDialog)
ON_WM_HSCROLL()
ON_WM_VSCROLL()
ON_WM_LBUTTONUP()
ON_WM_SIZE()
ON_WM_SIZING()
//}}AFX_MSG_MAP
//   ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )
END_MESSAGE_MAP()

//******************************************************************************

BOOL BaseDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // use process datagroup id as dlg data group id
   setDataGroupId( getParent()->getDataGroupId() );
//   EnableToolTips(TRUE);
   // This sets the icon for the dialog class. This means that every dialog in
   // our application will have an icon on the title bar for the system menu.
   // It also means that our buttons on the taskbar will have an icon. This call
   // only needs to be executed once per application. It is very low overhead
   // and happens infrequently so we don't keep a flag to ensure that is called
   // only once.

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL BaseDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
   BOOL bRc = FALSE;
   if( 0 != wParam )
   {
      NMHDR* pNMHDR = reinterpret_cast< NMHDR* >( lParam );
      if( NULL != pNMHDR )
      {
         switch( pNMHDR->code )
         {
            case LVN_GETDISPINFO:
               {
                  if( isValidListCtrl( wParam ) ) 
                  {
                     IFDSListCtrl* pCtrl = dynamic_cast< IFDSListCtrl* >( GetList( wParam ) );
                     if( NULL != pCtrl )
                     {
                        LV_DISPINFO* pDispInfo = reinterpret_cast< LV_DISPINFO* >( lParam );
                        bRc = pCtrl->getAdapter()->getDispInfo( pCtrl, pDispInfo );
                     }
                  }
                  if( FALSE == bRc )
                  {
                     bRc = CWnd::OnNotify( wParam, lParam, pResult );
                  }
               }
               break;
            case LVN_COLUMNCLICK:
               {
                  bRc = CWnd::OnNotify( wParam, lParam, pResult );
                  if( isValidListCtrl( wParam ) ) 
                  {
                     IFDSListCtrl* pCtrl = dynamic_cast< IFDSListCtrl* >( GetList( wParam ) );
                     if( NULL != pCtrl )
                     {
                        LPNMLISTVIEW pHdr = reinterpret_cast< LPNMLISTVIEW >( lParam );
                        pCtrl->getAdapter()->columnClick( pCtrl, pHdr );
                     }
                  }
                  *pResult = 0;
                  bRc = TRUE;
               }
               break;
            default:
               bRc = CWnd::OnNotify( wParam, lParam, pResult );
               break;
         }
      }
      else
      {
         bRc = CWnd::OnNotify( wParam, lParam, pResult );
      }
   }
   else
   {
      bRc = CWnd::OnNotify( wParam, lParam, pResult );
   }
   return( bRc );
}


//******************************************************************************

void BaseDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
}

//******************************************************************************

/*
BOOL BaseDlg::OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
  TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
  UINT nID =pNMHDR->idFrom;

  if (pTTT->uFlags & TTF_IDISHWND)
  {
    BaseControl *tmp = dynamic_cast<BaseControl*>(FromHandle((HWND)pNMHDR->idFrom));
    if(tmp)
    {
      tmp->SetMsg(&(pTTT->lpszText));
      pTTT->hinst=NULL;

      return TRUE;
    }
  }

  return FALSE;
}
*/

//******************************************************************************

BOOL BaseDlg::PreTranslateMessage( MSG *pMsg )
{
   if( isModal() )
   {  // We don't skip out to other screens when running modally
      return(CDialog::PreTranslateMessage( pMsg ));
   }

   // If this is F10, focus goes to main screen
   if( pMsg->message == WM_SYSKEYDOWN )
   {
      switch( pMsg->wParam )
      {
         case VK_F10:
            m_pDSTCView->PostMessage( UM_FUNCTIONKEYPRESSED, 10, 0 );
            return(TRUE);
      }
   }
   else if( ( pMsg->message == WM_KEYDOWN ) )
   {  // We only care if this is the a virtual key
      // Handle the "Fx" keys for the buttons and some others
      switch( pMsg->wParam )
      {
         case VK_F1:
         case VK_F2:
         case VK_F3:
            //dialogs use it to display action status
//         case VK_F4:
         case VK_F5:
         case VK_F6:
         case VK_F7:
            m_pDSTCView->PostMessage( UM_FUNCTIONKEYPRESSED,
                                      pMsg->wParam - VK_F1 + 1, 0 );
            return(TRUE);
         case VK_F8:
         case VK_F9:
         case VK_F11:
			m_pDSTCView->SetFocus();
            m_pDSTCView->PostMessage( UM_FUNCTIONKEYPRESSED,
                                      pMsg->wParam - VK_F1 + 1, 0 );
            return(TRUE);
         case VK_F12:
            m_pDSTCView->PostMessage( UM_FUNCTIONKEYPRESSED,
                                      pMsg->wParam - VK_F1 + 1, 0 );
            return(TRUE);
      } // end switch
   }

   return(CDialog::PreTranslateMessage( pMsg ));
}

//******************************************************************************

LRESULT BaseDlg::WindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
   LRESULT rtn = 0;
   try
   {
      rtn = CDialog::WindowProc( message, wParam, lParam ) ;
      if( WM_INITDIALOG == message )
      {  // Issue post init here so screen has chance to paint prior to going
         //  to database
         PostMessage( UM_POSTINITDIALOG );
      }	
	  if( WM_MOUSELEAVE == message )
	  {
			if( _bSizing )
			{
				_bSizing = false;
				if( !_bScroll )
				{
					m_resizeHelper->OnSize();
					SaveDialogSize ();
				}
				LoadControlErrorState();
				RedrawWindow();
			}
	  }
	  if( WM_SYSCOMMAND == message)
	  {
		  	switch(wParam)
			{
			case SC_DEFAULT_SIZE:
				{
					DefaultSize();
					break;
				}
			}			
	  }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, WINDOWPROC );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
//   Methods for control support
//******************************************************************************

BFControlFactory* BaseDlg::getControlFactory()
{
   return s_pControlFactory_;
}

BFControlFactory* BaseDlg::setControlFactory( BFControlFactory* pControlFactory )
{
   BFControlFactory* pOldFactory = s_pControlFactory_;
   s_pControlFactory_ = pControlFactory;
   return( pOldFactory );
}

BaseControl* BaseDlg::AddControl( E_CONTROLTYPE eType,
                                  UINT controlID,
                                  const BFContainerId& idContainer,
                                  const BFFieldId &idField,
                                  UINT flags,
                                  UINT controlGroupID )
{
   BaseControl *pCtrl = NULL;

   try
   {
      if( NULL == getControlFactory() ) 
      {
         return( pCtrl );
      }
      pCtrl = getControlFactory()->createControl( eType, this, controlID );
      if( NULL == pCtrl )
      {
         return( pCtrl );
      }
      // TODO - did the next operation to avoid changing all the control constructors
      //   at this time.   
      pCtrl->SetControlGroupID( controlGroupID );
      pCtrl->Init( idContainer, idField, flags );
      m_controls.insert( CONTROLS::value_type( controlID, pCtrl ) );
      m_orderedControls.push_back( pCtrl );

      if( eType == CTRL_EDIT && idField.getId() > 40000000 )
      {
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
         int length = pProps->getLength();

         if( length > 0 )
            dynamic_cast< DSTEdit*>(pCtrl)->SetMaxCharNum( length );
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, ADDCONTROL );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return( pCtrl );
}

//******************************************************************************

void BaseDlg::AddCrossEdit( const BFContainerId& idContainer,
                            const BFFieldId &idCrossEdit )
{
   CROSSEDITVECTOR *pVector = new CROSSEDITVECTOR;
// TODO - may need to retain idContainer in map so don't have problem with same
// fieldIDs associated with different containers on same screen
   m_crossEdits.insert( CROSSEDITS::value_type( idCrossEdit, pVector ) );
   getParentProcess()->getCrossEditFields( this, idContainer, idCrossEdit, *pVector );
}

//******************************************************************************

SEVERITY BaseDlg::CheckCrossEdits( const BaseControl *rpLoseFocusControl )
{
   CROSSEDITS_ITER end = m_crossEdits.end();
   BaseControl *rpControl = NULL;
   const BFFieldId &idLoseField = rpLoseFocusControl->GetFieldID();
   const BFContainerId& idLoseContainer = rpLoseFocusControl->GetContainerID();
   BFFieldId idGainField = ifds::NullFieldId;
   BFContainerId idGainContainer;
   CWnd *rpWnd = GetFocus();
   if( rpWnd )
   {  // Check to see if we are still on one of our controls
      UINT controlID = rpWnd->GetDlgCtrlID();
      if( controlID != 0 )
      {
         CONTROL_ITER iter = m_controls.find( controlID );
         if( iter != m_controls.end() )
         {  // found one
            rpControl = ( *iter ).second;
            idGainField = rpControl->GetFieldID();
            idGainContainer = rpControl->GetContainerID();
         }
      }
   }

   // If rpControl is NULL at this point, focus has shifted outside of all
   //  controls.
   for( CROSSEDITS_ITER iter = m_crossEdits.begin(); iter != end; iter++ )
   {  // Run through list of vectors and find any this control is in - then see
      // if focus window associated field is in it as well.  If not, fire
      // cross-edit
      CROSSEDITVECTOR *rpVector = ( *iter ).second;
      int count = rpVector->size();
      int idx;
      for( idx = 0; idx < count; idx++ )
      {
// TODO - should check all fields of multi-field control
         if( ( *rpVector )[idx] == idLoseField )
         {
            break;
         }
      }
      if( idx < count )
      {  // We have potential hit
         if( rpControl )
         {
            for( idx = 0; idx < count; idx++ )
            {
               if( ( *rpVector )[idx] == idGainField )
               {
                  break;
               }
            }
         }
         if( !rpControl || idLoseContainer != idGainContainer || idx >= count )
         {  // Focus was outside all controls, control associated containers are
            // different or focus was on control outside of this group - so fire
            // edit
            getParentProcess()->fireCrossEdit( this, idLoseContainer,
                                               ( *iter ).first );
         }
      }
   }
   return(NO_CONDITION);
}

//******************************************************************************

void BaseDlg::ClearControl( UINT controlID )
{
   GetControl( controlID )->Clear();
}

//******************************************************************************

void BaseDlg::ClearControls( const BFContainerId& idContainer )
{
   for( CONTROL_ITER iter = m_controls.begin(); iter != m_controls.end();
      iter++ )
   {
      BaseControl *rpCtrl = ( *iter ).second;

      if( !rpCtrl->IsManualLoad() )
      {  // Check clear on this one
         if( idContainer == BF::AllContainerIds || 
             rpCtrl->GetContainerID() == idContainer )
         {  // We have a hit
            rpCtrl->Clear();
         }
      }
   }
}

//******************************************************************************

void BaseDlg::ConnectControl(
                            UINT controlID,
                            bool bFlag
                            )
{
   GetControl( controlID )->SetConnected( bFlag );
}

//******************************************************************************

void BaseDlg::ConnectControlToData(
                                  UINT controlID,
                                  bool bFlag,
                                  bool bShowHideBasedOnConnection /* = false */
                                  )
{
   try
   {
      GetControl( controlID )->ConnectToData( bFlag, bShowHideBasedOnConnection );
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, CONNECTCONTROLTODATA );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void BaseDlg::ConnectControlsToData(
                                   UINT controlGroupID /* = 0 */,
                                   bool bFlag, /* = true */
                                   bool bShowHideBasedOnConnection /* = false */
                                   )
{
   try
   {
      for( CONTROL_ITER iter = m_controls.begin(); iter != m_controls.end();
         iter++ )
      {
         BaseControl *rpCtrl = ( *iter ).second;

         if( controlGroupID == 0xFFFF ||
             rpCtrl->GetControlGroupID() == controlGroupID )
         {  // We have a hit
            rpCtrl->ConnectToData( bFlag, bShowHideBasedOnConnection );
         }
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, CONNECTCONTROLSTODATA );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void BaseDlg::DisplayErrorInfo(
                              UINT killFocusControlID
                              )
{
}

//******************************************************************************

void BaseDlg::EnableControl(
                           UINT controlID,
                           bool bFlag
                           )
{
   GetControl( controlID )->Enable( bFlag );
}

//******************************************************************************

void BaseDlg::FocusOnFirstControl(
                                 UINT controlGroupID /* = 0 */
                                 )
{
   int size = m_orderedControls.size();

   for( int i = 0; i < size; i++ )
   {  // Look for first focusable control
      BaseControl *rp = m_orderedControls[i];
      if( controlGroupID == 0 || rp->GetControlGroupID() == controlGroupID )
      {
         if( rp->IsDataConnected() && rp->IsEnabled() && rp->IsVisible() )
         {  // Only if we should be able to get to it
            FocusOnControl( rp->GetControlID() );
            break;
         }
      }
   }
}

//******************************************************************************

BaseControl *BaseDlg::GetControl(
                                UINT controlID
                                ) const
{
   CONTROL_CONST_ITER iter = m_controls.find( controlID );
   if( iter != m_controls.end() )
   {  // good return
      return( *iter ).second;
   }
   else
   {  // Didn't find control in our container
      assert( 0 );
// TODO - add condition here
      throw;
   }
}

//******************************************************************************

const DString &BaseDlg::GetControlText(
                                      UINT controlID,
                                      DString &strValueOut,
                                      bool bFormatted,
                                      int index
                                      ) const
{
   strValueOut = NULL_STRING;

   try
   {
      GetControl( controlID )->GetText( strValueOut, bFormatted, index );
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, GETCONTROLTEXT );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

   return(strValueOut);
}

//******************************************************************************

bool BaseDlg::GetDataForControl(
                               UINT controlID,
                               DString &strValueOut,
                               bool bFormatted,
                               int index
                               ) const
{  // Default to no override
   return(false);
}

//******************************************************************************

void BaseDlg::InitControl( UINT controlID )
{  // Should never be called unless overridden
   assert( 0 );
   return;
}

//******************************************************************************

void BaseDlg::LoadControl( UINT controlID )
{
   try
   {
      GetControl( controlID )->Load();
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, LOADCONTROL );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void BaseDlg::LoadControls( const BFContainerId& idContainer )
{
   try
   {
      for( CONTROL_ITER iter = m_controls.begin(); iter != m_controls.end();
         iter++ )
      {
         BaseControl *rpCtrl = ( *iter ).second;

         if( !rpCtrl->IsManualLoad() )
         {  // Check load on this one
            if( idContainer == BF::AllContainerIds || 
                rpCtrl->GetContainerID() == idContainer )
            {  // We have a hit
               rpCtrl->Load();
            }
         }
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, LOADCONTROLS );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void BaseDlg::LoadControls( UINT controlGroupID )
{
   try
   {
      for( CONTROL_ITER iter = m_controls.begin(); iter != m_controls.end();
         iter++ )
      {
         BaseControl *rpCtrl = ( *iter ).second;

         if( !rpCtrl->IsManualLoad() )
         {  // Check load on this one
            if( -1 == controlGroupID ||
                rpCtrl->GetControlGroupID() == controlGroupID ) 
            {  // We have a hit
               rpCtrl->Load();
            }
         }
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, LOADCONTROLS );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void BaseDlg::LoadControlErrorState()
{
   EXECHISTI( I_("LoadControlErrorState()") );
   try
   {
      int count = m_orderedControls.size();
      int saveFocus = -1;
      for( int i = 0; i < count; i++ )
      {  // Reset errors on all controls
         BaseControl *rpControl = m_orderedControls[i];
         if( rpControl->LoadErrorState() > WARNING && saveFocus == -1 )
         {
            if( rpControl->IsDataConnected() && rpControl->IsEnabled() 
                && rpControl->IsVisible() )
            {  // Only if we should get be able to get to it
               saveFocus = rpControl->GetControlID();
            }
         }
      }
      if( saveFocus != -1 ) 
      {  // Focus on first error we found
         FocusOnControl( saveFocus );
      }

      // Need to set list display error state correctly
      for( int i = 0; i < m_lists.size(); i++ )
      {  // Refresh in order
         m_lists[i]->RefreshAllItems();
      };

      for( GRID_ITER gIter = m_Grids.begin(); gIter != m_Grids.end(); gIter++ )
      {
         EXECHISTI(I_("Looping on Grids") );
         //if the focus is already set, do not let the grid to steal it
         //by setting the selection on its items...
         ( *gIter ).second->reLoadGrid (saveFocus == -1);
      };

      // Need to set tabs display error state correctly
      for( int i = 0; i < m_tabs.size(); i++ )
      {  // Refresh in order
         m_tabs[i]->RefreshAllIcons();
      };
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, LOADCONTROLERRORSTATE );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

bool BaseDlg::ProcessControls()
{
   bool bRtn = true;

   try
   {
      // Handle last control with focus first
      BaseControl *rpControl = GetLastControlWithFocus();
      if( rpControl )
      {
         rpControl->Store();
      }
      for( CONTROL_ITER iter = m_controls.begin(); iter != m_controls.end();
         iter++ )
      {
         if( !( *iter ).second->Store() )
         {  // We have an error condition
            bRtn = false;
         }
      }
   }
   catch( ConditionException &ce )
   {
      bRtn = false;
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      bRtn = false;
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, PROCESSCONTROLS );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************

void BaseDlg::ReInitControl(
                           UINT controlID,
                           const BFContainerId& idContainer,
                           const BFFieldId &idField,
                           UINT flags,
                           int controlGroupID
                           )
{
   if( controlGroupID >= 0 )
      GetControl( controlID )->SetControlGroupID( controlGroupID );
   GetControl( controlID )->Init( idContainer, idField, flags );

}

//******************************************************************************

bool BaseDlg::SetControlText(
                            UINT controlID,
                            const DString &strValue,
                            bool bFormatted,
                            int index
                            ) const
{
   bool bRtn = false;

   try
   {
      bRtn = GetControl( controlID )->SetText( strValue, bFormatted, index );
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, SETCONTROLTEXT );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************

bool BaseDlg::SetDataFromControl(
                                UINT controlID,
                                const DString &strValue,
                                bool bFormatted,
                                SEVERITY &sevRtn,
                                int index
                                )
{
   sevRtn = NO_CONDITION;
   return(false);
}

//******************************************************************************

void BaseDlg::ShowControl(
                         UINT controlID,
                         bool bFlag
                         )
{
   GetControl( controlID )->Show( bFlag );
}

//******************************************************************************

void BaseDlg::UseCrossEdit(
                          const BFContainerId& idContainer,
                          long crossEditID
                          )
{
}
//******************************************************************************

bool BaseDlg::IsSelectedCtrlUpdateable()
{
   BaseControl* pWndWithFocus = NULL;
   pWndWithFocus = dynamic_cast<BaseControl*>(CWnd::GetFocus());
   if( pWndWithFocus )//don't want to assert if selected control was not added
      if( pWndWithFocus->IsUpdateable() )
         return(true);
   return(false);
}

//******************************************************************************
//   Methods for list control support
//******************************************************************************
DSTListCtrl* BaseDlg::AddListControl(
                            const I_CHAR *dialogName,
                            UINT controlID,
                            const I_CHAR *listName,
                            const BFFieldId &idSubstitute, 
                            const BFContainerId& idContainer, 
                            UINT parentControlID,
                            bool bShowSelAlways,
                            UINT flags
                            )
{
   DSTListCtrl* pCtrl = NULL;
   try
   {
      if( NULL == getControlFactory() )
      {
         return( NULL );
      }

      pCtrl = getControlFactory()->createListControl( this,
                                                      dialogName, 
                                                      controlID,
                                                      parentControlID,
                                                      flags, 
                                                      bShowSelAlways );
      if( NULL == pCtrl )
      {
         return( NULL );
      }

      if( listName && idSubstitute != ifds::NullFieldId && idContainer != BF::NullContainerId )
      {
         pCtrl->Init( this, idSubstitute, idContainer, listName );
      }
      m_lists.push_back( pCtrl );
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, ADDLISTCONTROL );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return( pCtrl );
}

IFDSListCtrl* BaseDlg::AddIFDSListControl( IFDSListCtrl* pCtrl,
                                           const I_CHAR* pszListName,
                                           const BFContainerId& idContainer,
                                           const BFFieldId& idColumnField )
{
   try
   {
      if( NULL == pCtrl )
      {
         return( NULL );
      }

      if( NULL != pszListName && idColumnField != ifds::NullFieldId && idContainer != BF::NullContainerId )
      {
         pCtrl->Init( this, idColumnField, idContainer, pszListName );
      }
      m_lists.push_back( pCtrl );
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, I_( "AddIFDSListControl" ) );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return( pCtrl );
}

//******************************************************************************
bool BaseDlg::AddToListControl( UINT controlID )
{
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, ADDTOLISTCONTROL );
   bool bRtn = false;

   try
   {
      DSTListCtrl *rpList = GetList( controlID );
      // Make sure all controls have been stored
      ProcessControls();

      SEVERITY sevRtn = rpList->AddRow();
      if( sevRtn >= WARNING )
      {  // Do we care about warnings here?
         ConditionMessageBox( FRAMEBELOW(), sevRtn );
      }
      if( sevRtn <= WARNING )
      {
         bRtn = true;
         FocusOnFirstControl( controlID );
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************

void BaseDlg::ConnectListToData( UINT controlID,
                                 bool bFlag,
                                 bool bShowHideBasedOnConnection /* = false */ )
{
   try
   {
      GetList( controlID )->ConnectToData( bFlag, bShowHideBasedOnConnection );
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, CONNECTLISTTODATA );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

bool BaseDlg::DeleteFromListControl( UINT controlID )
{
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, DELETEFROMLISTCONTROL );
   bool bRtn = false;

   try
   {
      DSTListCtrl *rpList = GetList( controlID );
      // Make sure all controls have been stored
      ProcessControls();

      SEVERITY sevRtn = rpList->DeleteRow();
      if( sevRtn >= WARNING )
      {  // Do we care about warnings here?
         ConditionMessageBox( FRAMEBELOW(), sevRtn );
      }
      if( sevRtn <= WARNING )
      {  // Delete did occur
         bRtn = true;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************

void BaseDlg::EnableList( UINT controlID, bool bFlag )
{
   GetList( controlID )->Enable( bFlag );
}

//******************************************************************************

DSTListCtrl *BaseDlg::GetList( UINT controlID ) const
{
   int count = m_lists.size();

   for( int i = 0; i < count; i++ )
   {
      if( m_lists[i]->GetControlID() == controlID )
      {
         return(m_lists[i]);
      }
   }

   // Didn't find list in container
   assert( 0 );
   throw;
}

//******************************************************************************

void BaseDlg::ListItemChanged( UINT listControlID,
                               const DString &strKey,
                               bool bIsNewItem,
                               bool bIsDummyItem )
{
   try
   {
      // Let derived dialog have a chance
      DoListItemChanged( listControlID, strKey, bIsNewItem, bIsDummyItem );
      //current item changed; have to check permission
      listCtrlIter = m_mapListCtrlNewItem.begin();
      while( listCtrlIter != m_mapListCtrlNewItem.end() )
      {
         int nListCtrlID = (*listCtrlIter).first;
         if( nListCtrlID == listControlID )//our list
         {
            (*listCtrlIter).second = bIsNewItem;
            break;
         }
         listCtrlIter++;
      }
      LoadChildListControls( listControlID );
      CheckPermission();
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, LISTITEMCHANGED );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void BaseDlg::LoadChildListControls( UINT parentListControlID )
{
   try
   {
      // Set any nested lists
      int count = m_lists.size();
      for( int i = 0; i < count; i++ )
      {
         if( m_lists[i]->GetParentControlID() == parentListControlID )
         {  // have a nested list - repopulate
            m_lists[i]->PopulateList( NULL );
         }
      }

      CWnd* pFocusWnd = GetFocus();
      // Set any nested grids
      GRID_ITER iter = m_Grids.begin();
      while( iter != m_Grids.end() )
      {
         if( (*iter).second->GetControlGroupID() == parentListControlID )
         {  // have a nested list - repopulate
            bool setGridSelection = iter->second->GridWnd() == pFocusWnd;
            (*iter).second->reLoadGrid( setGridSelection );
         }
         ++iter;
      };


   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, LOADCHILDLISTCONTROLS );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void BaseDlg::LoadListControl( UINT controlID, const DString *rpStrKey )
{
   try
   {
      DSTListCtrl *rpList = GetList( controlID );

      rpList->PopulateList( rpStrKey );
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, LOADLISTCONTROL );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void BaseDlg::RefreshListItem( UINT listControlID )
{
   DSTListCtrl *rpList = GetList( listControlID );
   rpList->RefreshCurrentItem();
}

//******************************************************************************

void BaseDlg::ResetListItem( UINT listControlID )
{
	DSTListCtrl *rpList = GetList( listControlID );		
  	bool bIsDummy = getParentProcess()->isCurrentListItemDummy( this, rpList->getContainerId() );	  
	int cnt = rpList->GetItemCount();
	while(cnt > 1 && bIsDummy )
	{
		rpList->DeleteRow();
		bIsDummy = getParentProcess()->isCurrentListItemDummy( this, rpList->getContainerId() );	  
		cnt = rpList->GetItemCount();
	}

   for( CONTROL_ITER iter = m_controls.begin(); iter != m_controls.end();
      iter++ )
   {
      BaseControl *rpCtrl = ( *iter ).second;
      rpCtrl->SetInitialLoad( true );
   }
  
   rpList->ResetCurrentItem();

   //after reset some read-only properties or even permission stuff might change, so be sure to 
   //call check permission here
   CheckPermission();

}

//******************************************************************************

void BaseDlg::ResetGridItem( UINT gridControlID )
{
   for( CONTROL_ITER iter = m_controls.begin(); iter != m_controls.end();
      iter++ )
   {
      BaseControl *rpCtrl = ( *iter ).second;
      rpCtrl->SetInitialLoad( true );
   }

   DSTGridWnd *rpGrid = GetGrid( gridControlID );
   rpGrid->ResetCurrentItem();

   //after reset some read-only properties or even permission stuff might change, so be sure to 
   //call check permission here
   CheckPermission();
}

//******************************************************************************
void BaseDlg::ReregisterObservers( UINT listControlID )
{
   for( CONTROL_ITER iter = m_controls.begin(); iter != m_controls.end();
      iter++ )
   {
      BaseControl *rpCtrl = ( *iter ).second;

      if( ( rpCtrl->_uiControlGroupID == listControlID ) && !rpCtrl->IsGUIField() && rpCtrl->IsDataConnected() && ( rpCtrl->GetFieldID() != ifds::NullFieldId ) )
      {
         if( getParent()->registerObserver( this, rpCtrl->GetContainerID(),
                                            rpCtrl->GetFieldID(), getParent()->getDataGroupId(), *rpCtrl ) )

            rpCtrl->setRegistered( true );
      }
   }
}
//******************************************************************************


void BaseDlg::ReInitListControl( UINT controlID, 
                                 const BFFieldId &idSubstitute, 
                                 const BFContainerId& idContainer, 
                                 const I_CHAR *listName )
{
   DSTListCtrl *rpList = GetList( controlID );

   rpList->Init( this, idSubstitute, idContainer, listName );
}

//******************************************************************************

void BaseDlg::ShowList( UINT controlID, bool bFlag )
{
   GetList( controlID )->Show( bFlag );
}

//******************************************************************************
//              Private methods
//******************************************************************************

SEVERITY BaseDlg::init2()
{
   return(doInit());
}

DSTGridWnd* BaseDlg::AddGrid( const I_CHAR *dialogName,
                              UINT controlID,
                              const I_CHAR *gridName,
                              const BFContainerId& idContainer,
                              UINT controlGroupID,
                              const BFFieldId &idTopSubstitution,
                              const BFFieldId &idLeftSubstitution,
                              int gridType,
                              UINT flags)
{
   if( NULL == getControlFactory() )
   {
      return(NULL);
   }
   GXInit(); // should be init of the dll

   DSTGridWnd *pGrid = getControlFactory()->createGridControl( this, dialogName, controlID, controlGroupID, gridName, idContainer, flags );
   if( NULL == pGrid )
   {
      return( NULL );
   }
//CP   pGrid->CGXGridWnd::LockWindowUpdate();
   m_Grids.insert( GRIDS::value_type ( controlID, pGrid ) );
   pGrid->setGridType(gridType);
   if( idTopSubstitution != ifds::NullFieldId )
   {
      pGrid->CreateHeader( idTopSubstitution, idLeftSubstitution );
   }
//CP   pGrid->CGXGridWnd::UnlockWindowUpdate();
   return( pGrid );
}

void BaseDlg::LoadGrid( UINT controlID, 
                        const BFFieldId &idTopSubstitution, 
                        const BFFieldId &idLeftSubstitution )
{
   DSTGridWnd *pGrid = GetGrid( controlID );

   if( pGrid )
   {
      pGrid->LockUpdate(TRUE);
      if( idTopSubstitution != ifds::NullFieldId )
      {
         pGrid->CreateHeader( idTopSubstitution, idLeftSubstitution );
      }
      pGrid->LoadGrid( );
      pGrid->LockUpdate(FALSE);
   }
}

DSTGridWnd *BaseDlg::GetGrid ( UINT controlID )
{
   GRID_ITER Iter = m_Grids.find(controlID);

   if( Iter != m_Grids.end() )
      return(*Iter).second;
   else
      return(NULL);
}

void BaseDlg::GetDlgFont( LOGFONT &font )
{  
	if( m_pFont == NULL )
	{
		int width=-1, height=-1;
		LoadDialogSize (width, height);
		//resize the screen, as well
		if (width != -1 && height != -1)
		{
			m_resizeHelper->OnSize (width, height);
		}
		if( m_pFont == NULL )
		{
			m_pFont = GetFont();
		}

		//m_pFont = GetFont();
	}
    m_pFont->GetLogFont(&font);
}

void BaseDlg::SetDlgFont( CFont *pCFont )
{
   m_pFont = pCFont;
   SetFont( pCFont );   
}


void BaseDlg::ReInitGrid(
                        const I_CHAR    *dialogName,
                        UINT             controlID, 
                        const I_CHAR    *gridName,
                        const BFContainerId& idContainer,
                        UINT             controlGroupID,
                        const BFFieldId &idTopSubstitution, 
                        const BFFieldId &idLeftSubstitution,
                        int         gridType,
                        UINT flags
                        )
{
   DSTGridWnd *rpGrid = GetGrid( controlID );
   
   rpGrid->SetFlags (flags);
   rpGrid->setGridType( gridType );
   rpGrid->setContainer( idContainer );
   rpGrid->CreateHeader( idTopSubstitution, idLeftSubstitution );
   rpGrid->LoadGrid();
   rpGrid->RedrawWindow();
}

DSTGridWnd *BaseDlg::GetGrid(
                            UINT gridControlID
                            ) const
{
   for( GRID_CONST_ITER gIter = m_Grids.begin(); gIter != m_Grids.end(); gIter++ )
   {
      if( ( *gIter ).second->GetControlID() == gridControlID )
      {
         return( *gIter ).second;
      }
   }

   // Didn't find grid in container
   assert( 0 );
   throw;
}

void BaseDlg::AddAttributeListControl(
                                     const I_CHAR *dialogName,
                                     UINT listControlID,
                                     const I_CHAR *listName,
                                     const BFFieldId &idSubstitute, 
                                     const BFFieldId &idLeftSubstitute, 
                                     const BFContainerId& idContainer, 
                                     UINT parentControlID,
                                     bool bShowSelAlways,
                                     UINT flags
                                     )
{
   try
   {
      DSTListCtrl *pCtrl = new DSTListCtrl( this, dialogName, listControlID,
                                            parentControlID, flags, bShowSelAlways );

      if( listName && idSubstitute != ifds::NullFieldId && idContainer != BF::NullContainerId )
      {
         pCtrl->Init( this, idSubstitute, idLeftSubstitute, idContainer, listName );
      }
      m_lists.push_back( pCtrl );
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, ADDLISTCONTROL );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}
//******************************************************************************

bool BaseDlg::isValidListCtrl(UINT controlID)
{
   bool bRetVal= false;    
   for( int i = 0; i < m_lists.size(); i++ )
   {
      if( controlID == m_lists[i]->GetControlID() )
      {
         bRetVal = true;
         break;
      }
   };
   return(bRetVal);
}
//******************************************************************************

void BaseDlg::ProcessListControls()
{
   int count = m_lists.size();

   for( int i = 0; i < count; i++ )
   {
      m_lists[i]->doOk();
   }
}

//******************************************************************************

//******************************************************************************

bool BaseDlg::AddToGridControl(
                              UINT controlID
                              )
{
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, ADDGRIDCONTROL );
   bool bRtn = false;

   try
   {
      DSTGridWnd *rpGrid = GetGrid( controlID );
      // Make sure all controls have been stored
      ProcessControls();

      SEVERITY sevRtn = rpGrid->AddRow();
      if( sevRtn >= WARNING )
      {  // Do we care about warnings here?
         ConditionMessageBox( FRAMEBELOW(), sevRtn );
      }
      if( sevRtn <= WARNING )
      {
         bRtn = true;
         // puts focus on the first control.
         FocusOnFirstControl( controlID );
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************

bool BaseDlg::DeleteFromGridControl( UINT controlID )
{
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, DELETEFROMLISTCONTROL );
   bool bRtn = false;

   try
   {
      DSTGridWnd *rpGrid = GetGrid( controlID );
      // Make sure all controls have been stored
      ProcessControls();

      SEVERITY sevRtn = rpGrid->DeleteRow();
      if( sevRtn >= WARNING )
      {  // Do we care about warnings here?
         ConditionMessageBox( FRAMEBELOW(), sevRtn );
      }
      if( sevRtn <= WARNING )
      {  // Delete did occur
         bRtn = true;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************
//   Methods for tab control support
//******************************************************************************

DSTTabCtrl * BaseDlg::AddTabControl(
                                   const I_CHAR *dialogName,
                                   UINT tabControlID,
                                   const I_CHAR *tabName,
                                   UINT parentControlID,//not used for now
                                   UINT flags//not used for now
                                   )
{
   DSTTabCtrl *pCtrl = NULL;
   try
   {
//CP20021113      pCtrl = new DSTTabCtrl( this, dialogName, tabControlID, parentControlID, flags );
      pCtrl = getControlFactory()->createTabControl( this, dialogName, tabControlID, parentControlID, flags );
      pCtrl->Init( this, tabName );
      m_tabs.push_back( pCtrl );
   }
   catch( ConditionException &ce )
   {
      pCtrl = NULL;
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      pCtrl = NULL;
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, ADDTABCONTROL );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(pCtrl);
}
//******************************************************************************

DSTTabCtrl *BaseDlg::GetTabCtrl(
                               UINT tabControlID
                               )
{
   for( int i = 0; i < m_tabs.size(); i++ )
   {
      if( m_tabs[i]->GetControlID() == tabControlID )
      {
         return(m_tabs[i]);
      }
   }

   // Didn't find list in container
   return(NULL);
}
//******************************************************************************

void BaseDlg::ShowTabCtrl(
                         UINT controlID,
                         bool bFlag
                         )
{
   DSTTabCtrl * pCtrl = GetTabCtrl( controlID );
   if( pCtrl )
   {
      if( bFlag )
         pCtrl->ShowWindow( SW_SHOW );
      else
         pCtrl->ShowWindow( SW_HIDE );
   }
}

//******************************************************************************

void BaseDlg::LoadTabControl(
                            UINT tabControlID,
                            const DString &pageName
                            )
{
   try
   {
      DSTTabCtrl *rpTab = GetTabCtrl( tabControlID );
      if( rpTab )
         rpTab->Load(pageName);
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      ASSERT( 0 );
      MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, LOADTABCONTROL );

      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}
//******************************************************************************

void BaseDlg::positionTabToControl(UINT tabControlID, UINT nOtherControlID, bool bLeft, 
                                   bool bBottom, bool bRight )
{
   CRect rTab, rOtherControl;
   CWnd* pTab = GetDlgItem(tabControlID);
   pTab->GetWindowRect(rTab);
   CWnd* pOther = GetDlgItem(nOtherControlID);
   pOther->GetWindowRect(rOtherControl);


   if( bBottom )
   {
      int y = rOtherControl.top - rTab.bottom;
      rTab.bottom = rOtherControl.top;
      rTab.top += y;
   }

   if( bLeft )
      rTab.left = rOtherControl.left;

   if( bRight )
      rTab.right = rOtherControl.right;

   ScreenToClient(&rTab.TopLeft());
   ScreenToClient(&rTab.BottomRight());

   pTab->MoveWindow(&rTab);
}
//******************************************************************************

void BaseDlg::ProcessTabControls()
{
   for( int i = 0; i < m_tabs.size(); i++ )
      m_tabs[i]->RefreshAllIcons();
}

//******************************************************************************
void BaseDlg::doSetDlgItemText( int nID, LPCTSTR lpszString, BFFieldId fieldId )
{
	DString str = lpszString;
	DisplayFormat( str, fieldId );	
		
	return ( SetDlgItemText(nID, str.strip().c_str() ));
}

//******************************************************************************
void BaseDlg::DisplayFormat( DString& strText, const BFFieldId& idField )
{
   const bfutil::LocaleTraits& localeTraitsE = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
   I_CHAR RadixSeparatorE = localeTraitsE.getRadixSeparator();
   I_CHAR GroupseparatorE = localeTraitsE.getGroupSeparator();

   const bfutil::LocaleTraits& localeTraitsDisp = bfutil::LocaleTraits::get( ClientLocaleContext::get(), true );
   CString RadixSeparatorDisp = localeTraitsDisp.getRadixSeparator();
   CString GroupseparatorDisp = localeTraitsDisp.getGroupSeparator();

   DString tempchar = I_(";");

	DString dstLocaleStr = ClientLocaleContext::get().getLocale();
	if( dstLocaleStr == I_("deDE") )
	{
		bool bdecimal = false;

		//if( idField == ifds::NullFieldId || idField.getId() < 4000000   ) 
		{
			DString tmp = strText;
			tmp.stripAll('%');
			tmp.stripAll();
			bdecimal = tmp.isDecimal();
		}
		/*else 
		{
			const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
			bdecimal = pProps->isDecimal();
		}*/

		if( bdecimal )
		{
			int iPos;
			while( true )
			{
				iPos = strText.find( RadixSeparatorE );
				if( iPos == DString::npos ) break;
				strText.replace( iPos, 1, tempchar );
			}

			while( true )
			{
				iPos = strText.find( GroupseparatorE );
				if( iPos == DString::npos ) break;				
				strText.replace( iPos, 1, GroupseparatorDisp );
			}

			while( true )
			{
				iPos = strText.find( tempchar );
				if( iPos == DString::npos ) break;
				strText.replace( iPos, 1, RadixSeparatorDisp );
			}
		}
	}
}

//******************************************************************************
void BaseDlg::DisplayUnFormat( DString& strText, const BFFieldId& idField )
{
    const bfutil::LocaleTraits& localeTraitsE = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
    CString RadixSeparatorE = localeTraitsE.getRadixSeparator();
	CString GroupseparatorE = localeTraitsE.getGroupSeparator();

    const bfutil::LocaleTraits& localeTraitsDisp = bfutil::LocaleTraits::get( ClientLocaleContext::get(), true );
    I_CHAR RadixSeparatorDisp = localeTraitsDisp.getRadixSeparator();
	I_CHAR GroupseparatorDisp = localeTraitsDisp.getGroupSeparator();

	DString tempchar = I_(";");

	DString dstLocaleStr = ClientLocaleContext::get().getLocale();
	if( dstLocaleStr == I_("deDE") )
	{
		bool bdecimal = false;

		//if( idField == ifds::NullFieldId || idField.getId() < 4000000 )
		{
			DString tmp = strText;
			tmp.stripAll('%');
			tmp.stripAll();
			tmp.stripAll( GroupseparatorDisp );
			tmp.stripAll( RadixSeparatorDisp );
			bdecimal = tmp.isAllDigits();
		}
		/*else
		{
			const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
			bdecimal = pProps->isDecimal();
		}*/

		if( bdecimal )
		{
			int iPos;
			while( true )
			{
				iPos = strText.find( RadixSeparatorDisp );
				if( iPos == DString::npos ) break;
				strText.replace( iPos, 1, tempchar );
			}

			while( true )
			{
				iPos = strText.find( GroupseparatorDisp );
				if( iPos == DString::npos ) break;
				strText.replace( iPos, 1, GroupseparatorE );
			}

			while( true )
			{
				iPos = strText.find( tempchar );
				if( iPos == DString::npos ) break;
				strText.replace( iPos, 1, RadixSeparatorE );
			}
		}
	}
}

//******************************************************************************
void BaseDlg::OnSizing( UINT nSide,  LPRECT lpRect  )
{
	CDialog::OnSizing( nSide, lpRect );
	_bSizing = true;
}

//******************************************************************************
void BaseDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    m_scrollHelper->OnHScroll (nSBCode, nPos, pScrollBar);    
}

//******************************************************************************
void BaseDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    m_scrollHelper->OnVScroll (nSBCode, nPos, pScrollBar);
}

//******************************************************************************
void BaseDlg::OnSize (UINT nType, int cx, int cy)
{
   CDialog::OnSize(nType, cx, cy);

   int LeftButton = GetAsyncKeyState (VK_LBUTTON);
   int RightButton = GetAsyncKeyState (VK_RBUTTON);
	
   TRACKMOUSEEVENT MouseEvent;

   MouseEvent.cbSize = sizeof( TRACKMOUSEEVENT );
   MouseEvent.dwFlags = TME_LEAVE;
   MouseEvent.hwndTrack = m_hWnd;
   MouseEvent.dwHoverTime = 0;
   _TrackMouseEvent (&MouseEvent);
	
   if (_bScroll)
	{
      m_scrollHelper->OnSize (nType, cx, cy);	
	}
}

//******************************************************************************
void BaseDlg::OnLButtonUp (UINT nFlags,  CPoint point)
{
	CDialog::OnLButtonUp(nFlags, point);
/*	
	if( _bSizing )
	{
		_bSizing = false;
		if( !_bScroll)
		{
			m_resizeHelper->OnSize();
		}
		LoadControlErrorState();
		RedrawWindow();
	}
*/
}

//******************************************************************************
void BaseDlg::DefaultSize()
{
		CWaitCursor wait;   
		ConfigManager *pWorkstation = ConfigManager::getManager (WORKSTATION);		
		pWorkstation->RemoveConfig( m_dialogName );	

		m_resizeHelper->OnSize (0, 0);        
	  	LoadControlErrorState();			
		RedrawWindow();
}

//******************************************************************************

void BaseDlg::formatParagraph( CString &strText, int& iOffset, int iMaxCharNum, int iMaxNumLine )
{	
	int iNumLine = 1;
	int iMaxLength = iMaxNumLine * (iMaxCharNum + 2) - 2;//no EOL on the last line	
	int iInitialLength = strText.GetLength() > iMaxLength ? iMaxLength : strText.GetLength();
	int iStart = 0;
	int iPos;
	CString endOfLine = "\r\n";
	CString strCurrLine;

	while( iStart < strText.GetLength() && iNumLine <= iMaxNumLine )
	{		
		iPos = strText.Find( endOfLine, iStart );
		//if EOL not found, but more than 70 chars line, insert EOL
		bool bInsertNewLine = iPos < 0 && strText.GetLength() - iStart > iMaxCharNum;
		//or, if EOL found, but it's after 70 chars, insert new EOL
		iPos -= iStart;
		if( bInsertNewLine || iPos > iMaxCharNum )
		{		
			//find the last blank for the current line
			strCurrLine = strText.Mid( iStart, iMaxCharNum );
            int nBlankPos = strCurrLine.ReverseFind( ' ' );
			nBlankPos = nBlankPos >= 0 ? nBlankPos++ : nBlankPos = iMaxCharNum;//if no blank found on the current line insert EOL at iMaxCharNum+1			
			strText.Insert( iStart + nBlankPos, endOfLine );
			iStart += (nBlankPos+2);//2 stands for EOL
			iMaxLength = iNumLine == iMaxNumLine ? iStart-2 : iStart;//if last line, don't need an EOL at the end				
		}
		else if ( iPos >= 0 )
		{
			//newline char found before 70 chars; advance
            iStart += (iPos+2);//2 stands for EOL
            iMaxLength = iNumLine == iMaxNumLine ? iStart-2 : iStart;//if last line, don't need an EOL at the end			
		}
		else
		{
           //no newline found and there was no need to insert a newline, so this must be the last line; 
           iMaxLength = strText.GetLength();
           break;
		}
		iNumLine++;
	}

	//not more than 70 chars/line and not more than 10 lines
	if( strText.GetLength() > iMaxLength )
	{
		strText.Truncate( iMaxLength );
	}

	iOffset = strText.GetLength() - iInitialLength;
}

//******************************************************************************
bool BaseDlg::IsBrowserBasedDialog() const
{
	bool isBrowserBasedDialog = false;

	CString strDialogName = m_dialogName.c_str();
	if (strDialogName == "BrowserLaunch")
	{
		isBrowserBasedDialog = true;
	}

	return isBrowserBasedDialog;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/basedlg.cpp-arc  $
//
//   Rev 1.103   Mar 24 2009 10:30:34   purdyech
//Changes for ZTS.  Release 9 for Phase II of POC
//
//   Rev 1.102   Feb 20 2009 13:48:06   purdyech
//ZTS Revision 6
//
//   Rev 1.101   Nov 10 2008 14:44:24   wongsakw
//IN1210534 Desktop trading focus issue (sync up)
//
//   Rev 1.100   24 Oct 2008 10:23:02   kovacsro
//1399970 - GL-1254 Desktop Screen (Remarks - odd character )
//
//   Rev 1.99   Oct 20 2006 13:48:52   fengyong
//Incident # 698369 - crash on reset
//
//   Rev 1.98   Oct 13 2005 09:36:04   fengyong
//Incident 403519 - small font fix
//
//   Rev 1.97   Oct 07 2005 17:12:46   AGUILAAM
//IN 403519 - fixed crash due to font change (for yongmei)
//
//   Rev 1.96   Oct 06 2005 16:25:18   fengyong
//#incident 403519 - temp check in limt the resize height max to default height.
//
//   Rev 1.95   Oct 05 2005 16:01:46   fengyong
//#Incident 403519 - double check window size before get window font
//
//   Rev 1.93   Sep 30 2005 16:50:06   fengyong
//#403519 - default sizing fix
//
//   Rev 1.92   Sep 28 2005 10:48:40   fengyong
//#Incident 403519 - Add default size feature
//
//   Rev 1.91   Sep 27 2005 10:32:14   fengyong
//Incident #40519 - resize grid control together with the screen resizing
//
//   Rev 1.90   Sep 15 2005 12:58:04   popescu
//Incident # 403519 - saved/restored the size of the dialog in the registry
//
//   Rev 1.89   Sep 14 2005 11:55:30   popescu
//Incident# 403519 - dialog resize, added some comments
//
//   Rev 1.88   Sep 07 2005 12:31:42   fengyong
//small change for scroll and resize 
//
//   Rev 1.87   Sep 07 2005 11:11:08   fengyong
//Add scroll and resize feature to dialogs
//
//   Rev 1.86   Aug 12 2005 17:20:06   Fengyong
//Incident 378244 - european numeric: formatting code do not check field type, just check value is decimal or not.
//
//   Rev 1.85   Jul 22 2005 15:12:46   Fengyong
//PET1250FN02 - European format - syncup
//
//   Rev 1.84   Jun 30 2005 16:59:16   Fengyong
//PET1250FN02 - eropean numeric EH - Please apply Localetraits.cpp/hpp code 
//
//   Rev 1.83   Jun 24 2005 17:01:22   Fengyong
//PET1250 FN02 - EuroPean numeric enhancement
//
//   Rev 1.82   Jun 10 2005 12:52:26   popescu
//Incident# 280865 - grid should not steal focus if there is a control with focus on it, due to the fact that the error state is greater then WARNING
//
//   Rev 1.81   Apr 26 2005 10:57:08   Fengyong
//#Incident 240778 - F11 on some screen cause crash,
//
//   Rev 1.80   Nov 14 2004 15:01:54   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.79   Oct 01 2004 18:14:56   popescu
//PET 1117/06, SSB Germany - Added 'flags' parameter to the grid control - not very useful for the moment
//
//   Rev 1.78   May 07 2004 10:07:08   FENGYONG
//PTS10029890 F7 key
//
//   Rev 1.77   May 26 2003 13:22:44   PURDYECH
//BaseDlg::OnNotify method was fixed up so that default CWnd::OnNotify is called at the correct time.
//
//   Rev 1.76   May 24 2003 15:05:22   PURDYECH
//Changed the Add*Control functions to return a pointer to what they just added.
//Added AddIFDSListControl to add an IFDSAdaptedListCtrl<>
 * 
 *    Rev 1.75   Apr 14 2003 11:57:50   PURDYECH
 * LoadControls() has a silly overload which is tripped because of BFContainerId changeover.  Fixed LoadControls( UINT ) to handle special value of -1 which means all controls.
 * 
 *    Rev 1.74   Jan 14 2003 11:05:14   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.73   Jan 06 2003 16:45:56   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.72   Nov 14 2002 10:48:56   SMITHDAV
 * Sync-up from old source database.
 * 
 *    Rev 1.71   Nov 13 2002 11:43:58   PURDYECH
 * Extended BFControlFactory to include list controls, tab controls and grid windows.
 * 
 *    Rev 1.70   Oct 31 2002 13:33:36   KOVACSRO
 * very small change for LoadTabControl.
 * 
 *    Rev 1.69   Oct 21 2002 13:46:54   PURDYECH
 * Use BFControlFactroy to create basic controls.  
 * 
 *    Rev 1.68   Oct 09 2002 17:42:34   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.67   Oct 07 2002 14:28:52   KOVACSRO
 * Release 50 : Tab control support
 * 
 *    Rev 1.66   Sep 19 2002 15:50:14   PURDYECH
 * Sync back to YingBao's changes from 1.63.1.0
 * 
 *    Rev 1.65   Sep 19 2002 12:05:10   PURDYECH
 * BFFieldId has lost its operator long() method, so BFFieldId can no longer be compared to ints.  Code was changed to reflect this.
 * 
 *    Rev 1.64   Sep 10 2002 14:34:26   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.63   Sep 06 2002 16:48:08   DINACORN
 * Minor change in ReInitGrid().
 * 
 *    Rev 1.62   Sep 05 2002 14:01:00   HSUCHIN
 * added support for add/delete from Stingray Grid
 * 
 *    Rev 1.61   Sep 05 2002 10:44:30   DINACORN
 * Changed ReInitGrid().
 * 
 *    Rev 1.60   Aug 29 2002 12:57:32   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.59   23 Jul 2002 10:24:40   YINGZ
 * rollback
 * 
 *    Rev 1.57   Jul 16 2002 09:52:48   KOVACSRO
 * added ProcessListControls() which calls doOk on the list controls.
 * 
 *    Rev 1.56   Jun 05 2002 16:47:36   YINGZ
 * support reset
 * 
 *    Rev 1.55   May 23 2002 09:55:46   PURDYECH
 * BFData Implementation Verification Corrections
 * 
 *    Rev 1.54   22 Apr 2002 17:01:56   KOVACSRO
 * Bug fixed for  changeBtnToListCtrlAssociation(). Also, Delete btn. should be always disabled if there are no items in the list.
 * 
 *    Rev 1.53   11 Apr 2002 14:34:22   HSUCHIN
 * bug fix for function keys
 * 
 *    Rev 1.52   Mar 01 2002 13:13:34   YINGBAOL
 * fix reInitcontrol
 * 
 *    Rev 1.51   Feb 28 2002 17:56:10   YINGBAOL
 * fix
 * 
 *    Rev 1.50   Feb 28 2002 12:42:08   YINGBAOL
 * do not check control for readonly if it's parent list is not connected
 * 
 *    Rev 1.49   27 Feb 2002 16:06:00   HSUCHIN
 * Added a parameter to ReInitControl to associate a group to the reinited control
 * 
 *    Rev 1.48   04 Feb 2002 15:26:36   KOVACSRO
 * Added Timer List Control.
 * 
 *    Rev 1.47   23 Nov 2001 14:16:40   KOVACSRO
 * changed the way the derived class handles enable/disable buttons added for perm. check.
 * 
 *    Rev 1.46   13 Nov 2001 10:15:46   KOVACSRO
 * synch-up to 1.44.1.0
 * 
 *    Rev 1.45   25 Oct 2001 16:57:14   SMITHDAV
 * hasPermission changes
 * 
 *    Rev 1.44   Oct 24 2001 10:55:18   YINGBAOL
 * fix reset problem
 * 
 *    Rev 1.43   20 Aug 2001 12:04:46   HSUCHIN
 * bug fix for F11 Key event
 * 
 *    Rev 1.42   18 Aug 2001 09:21:50   HSUCHIN
 * bug fix for F11 key press.
 * 
 *    Rev 1.41   Aug 15 2001 10:34:22   ZHANGCEL
 * support attibute type list
 * 
 *    Rev 1.40   15 Aug 2001 09:45:02   YINGZ
 * support attribute type list
 * 
 *    Rev 1.39   Jul 10 2001 16:47:34   YINGBAOL
 * fix reset issue
 * 
 *    Rev 1.38   04 Jul 2001 16:46:16   YINGZ
 * implement cancel to give user warning when there are updates
 * 
 *    Rev 1.37   19 Jun 2001 15:24:04   YINGZ
 * fix ResetListItem
 * 
 *    Rev 1.36   08 Jun 2001 13:28:26   YINGZ
 * fix ResetListItem to re-register observer
 * 
 *    Rev 1.35   17 May 2001 09:43:24   YINGZ
 * support reinitgrid
 * 
 *    Rev 1.34   15 May 2001 15:37:04   YINGZ
 * data group id clean up
 * 
 *    Rev 1.33   07 May 2001 13:19:48   SMITHDAV
 * Session sync-up.
 * 
 *    Rev 1.32   26 Apr 2001 16:50:16   KOVACSRO
 * Added support for read only edit controls.
 * 
 *    Rev 1.31   24 Apr 2001 11:17:34   KOVACSRO
 * Added IsControlUpdateable() in checkControlForReadOnly.
 * 
 *    Rev 1.30   19 Apr 2001 17:10:56   KOVACSRO
 * perm. check.
 * 
 *    Rev 1.29   18 Apr 2001 11:55:50   KOVACSRO
 * Modified CheckCtrlForReadOnly()
 * 
 *    Rev 1.28   10 Apr 2001 14:19:02   KOVACSRO
 * Modified checkControlForReadOnly().
 * 
 *    Rev 1.27   Apr 06 2001 12:07:04   YINGZ
 * make changes to datagroup
 * 
 *    Rev 1.26   05 Apr 2001 15:59:54   KOVACSRO
 * Added IsSelectedCtrlUpdateable.
 * 
 *    Rev 1.25   05 Apr 2001 15:04:30   KOVACSRO
 * Added OnKeyDown.
 * 
 *    Rev 1.24   04 Apr 2001 16:16:00   KOVACSRO
 * perm. check
 * 
 *    Rev 1.23   03 Apr 2001 15:56:10   KOVACSRO
 * bug fixed.
 * 
 *    Rev 1.22   03 Apr 2001 11:59:10   KOVACSRO
 * Permission check stuff.
 * 
 *    Rev 1.21   30 Mar 2001 17:39:28   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.20   30 Mar 2001 12:08:52   KOVACSRO
 * perm. check .
 * 
 *    Rev 1.19   29 Mar 2001 13:37:46   KOVACSRO
 * permission check stuff.
 * 
 *    Rev 1.19   29 Mar 2001 13:24:08   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.18   27 Mar 2001 16:37:24   KOVACSRO
 * permission check cleanup.
 * 
 *    Rev 1.17   22 Mar 2001 11:42:06   BUZILAMI
 * if UserAccesFunctionCode was not set Add, Delete and Ok buttons that were added for permision check are disabled
 * 
 *    Rev 1.16   01 Mar 2001 16:29:42   KOVACSRO
 * Modified checkPrmission and added it to ListItemChanged.
 * 
 *    Rev 1.15   Jan 17 2001 09:45:00   KOVACSRO
 * Added some new stuff for permission check.
 * 
 *    Rev 1.14   Dec 13 2000 15:07:14   KOVACSRO
 * 1. Modified DoListItemChanged.
 * 2.Added Dummy Item logic for perm. check.
 * 
 *    Rev 1.13   Dec 05 2000 17:12:46   KOVACSRO
 * 1.Added new item logic for permission check.
 * 2.Modified CheckPermission to enable buttons when user has permission.
 * 
 *    Rev 1.12   Dec 01 2000 15:26:36   KOVACSRO
 * Modified CheckPermission() to prevent crash.
 * 
 *    Rev 1.11   Dec 01 2000 11:48:36   KOVACSRO
 * Added permission check logic.
 * 
 *    Rev 1.10   May 29 2000 09:18:54   BUZILA
 * added GetNextDlgTabItem method
 * 
 *    Rev 1.9   May 25 2000 13:56:30   BUZILA
 * loading grid errors to in LoadControlErrorState()
 * 
 *    Rev 1.8   May 16 2000 13:59:16   HSUCHIN
 * removed DSTFundClassEdit control
 * 
 *    Rev 1.7   May 09 2000 10:18:20   BUZILA
 * grid fixes
 * 
 *    Rev 1.6   May 08 2000 11:46:26   HSUCHIN
 * added Fund Edit control to launch Fund Search screen
 * 
 *    Rev 1.5   Apr 04 2000 12:58:42   BUZILA
 * passing GridName and Dialog name to DSTGridWnd in order to be able to save/restore layout changes
 * 
 *    Rev 1.4   Mar 22 2000 12:56:32   BUZILA
 * Grid changes
 * 
 *    Rev 1.3   Mar 14 2000 15:30:54   YINGZ
 * add GXInit to AddGrid
 * 
 *    Rev 1.2   Mar 10 2000 11:46:34   YINGZ
 * code sync
 * 
 *    Rev 1.1   Mar 08 2000 16:22:16   YINGZ
 * add grid support
 * 
 *    Rev 1.0   Feb 15 2000 11:01:38   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.42   Jan 28 2000 17:18:42   YINGZ
 * make edit control take data dictionary length
 * 
 *    Rev 1.41   Jan 27 2000 10:24:38   DT24433
 * force list refresh to occur in parent-child order
 * 
 *    Rev 1.40   Jan 26 2000 14:09:56   DT24433
 * changed AddToListControl/DeleteFromListControl to return bool and display errors
 * 
 *    Rev 1.39   Jan 25 2000 15:59:40   DT24433
 * prevent focus on controls that are disconnected/disabled/not visible
 * 
 *    Rev 1.38   Jan 21 2000 11:36:50   YINGZ
 * fix multiline reset problem
 * 
 *    Rev 1.37   Jan 18 2000 16:37:22   DT24433
 * added implementation for ResetListItem
 * 
 *    Rev 1.36   Jan 13 2000 17:08:22   DT24433
 * error handling changes
 * 
 *    Rev 1.35   Jan 11 2000 17:23:38   DT24433
 * added support for CancelInProgress & changed RefreshListItem
 * 
 *    Rev 1.34   Jan 05 2000 17:53:08   DT24433
 * added cross-edit & validation calls
 * 
 *    Rev 1.33   Dec 22 1999 13:13:28   DT24433
 * save last focused control
 * 
 *    Rev 1.32   Dec 21 1999 13:48:32   DT24433
 * initial notification changes
 * 
 *    Rev 1.31   Dec 14 1999 13:08:46   DT24433
 * made DString const in SetControlText
 * 
 *    Rev 1.30   Dec 09 1999 18:43:28   DT24433
 * added Show/Hide to ConnectControl(s)ToData
 * 
 *    Rev 1.29   Dec 08 1999 16:30:36   DT24433
 * additional support for child lists
 * 
 *    Rev 1.28   Dec 04 1999 11:54:14   DT24433
 * added try/catch and delete list controls
 * 
 *    Rev 1.27   Dec 03 1999 19:56:14   YINGZ
 * add ConnectControlToData
 * 
 *    Rev 1.26   Dec 03 1999 13:11:46   DT24433
 * removed fieldvalidate functionality
 * 
 *    Rev 1.25   Nov 29 1999 15:03:02   YINGZ
 * add bIsNewItem to DoListItemChanged and ListItemChanged
 * 
 *    Rev 1.24   Nov 24 1999 11:08:26   DT24433
 * minor name change GetParentControlID
 * 
 *    Rev 1.23   Nov 24 1999 11:01:32   DT24433
 * added ListItemChanged & DoListItemChanged
 * 
 *    Rev 1.22   Nov 17 1999 12:50:38   DT24433
 * more control changes
 * 
 *    Rev 1.21   Nov 15 1999 14:00:32   DT24433
 * changed to pass control flags in init
 * 
 *    Rev 1.20   Nov 12 1999 13:19:28   DT24433
 * listview container changes
 * 
 *    Rev 1.19   Nov 11 1999 09:06:04   DT24433
 * changed some flag support
 * 
 *    Rev 1.18   Nov 09 1999 12:10:46   YINGZ
 * add list control filter
 * 
 *    Rev 1.17   Nov 06 1999 13:23:40   YINGZ
 * SetControlTextOnly removed
 * 
 *    Rev 1.16   Nov 05 1999 10:35:50   YINGZ
 * add SetControlTextOnly and flag to REinitcontrol
 * 
 *    Rev 1.15   Nov 04 1999 11:34:30   DT24433
 * misc
 * 
 *    Rev 1.14   Nov 03 1999 15:11:46   DT24433
 * new control methods
 * 
 *    Rev 1.13   Nov 02 1999 17:25:54   YINGZ
 * add index
 * 
 *    Rev 1.12   Oct 29 1999 16:27:28   YINGZ
 * add reinitcontrol
 * 
 *    Rev 1.11   Oct 18 1999 16:40:58   DT24433
 * misc. changes
 * 
 *    Rev 1.10   Oct 14 1999 16:03:28   DT24433
 * changed for two step construction of controls
 * 
 *    Rev 1.9   Oct 14 1999 13:51:10   YINGZ
 * add tooltip support
 * 
 *    Rev 1.8   Oct 14 1999 10:14:42   DT24433
 * added new methods
 * 
 *    Rev 1.7   Oct 04 1999 17:40:48   DT24433
 * preliminary changes for BaseControl interaction
 * 
 *    Rev 1.6   Sep 14 1999 11:03:50   YINGZ
 * add GetOverrideItemString
 * 
 *    Rev 1.5   Aug 25 1999 08:14:48   DT24433
 * removed dstcfuncs.h include
 * 
 *    Rev 1.4   Jul 20 1999 11:18:22   VASILEAD
 * New conditions update
 * 
 *    Rev 1.3   Jul 09 1999 16:06:58   HSUCHIN
 * fixed log
 * 
 *    Rev 1.2   Jul 09 1999 15:33:38   VASILEAD
 * Bug fixes
*/ 



