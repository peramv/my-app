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
// ^FILE   : AbstractBaseMainDlg.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 02/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AbstactBaseMainDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  : This base dialog class adds additional functionality for
//                     main modal and modeless dialogs.
//
//******************************************************************************

#include "stdafx.h"
#include "AbstractBaseMainDlg.h"

#include <ConfigManager.hpp>
#include "ConditionMessageDialog.h"
#include <bfproc\GenericInterfaceContainer.hpp>
#include <IDIString.hpp>
#include <typeinfo>
#include <bfproc\bfcontainerid.hpp>
#include <bfcbo\BFWorkSession.hpp>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   // Tracing literals
   const I_CHAR * const CLASSNAME   = I_( "AbstractBaseMainDlg" );
   const I_CHAR * const MOVEDIALOG    = I_( "MoveDialog" );
   const I_CHAR * const COLUMN      = I_( ":" );
   const I_CHAR * const SEMICOLUMN    = I_( ";" );
   const I_CHAR * const SPACE       = I_( " " );
   const I_CHAR * const WORKSTATION   = I_( "WORKSTATION" );

   const I_CHAR * const DIALOG = I_( "DIALOG" );

}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_DIALOG_CREATE_FAILED;
   extern const long GUI_ERR_DOMODAL_FAILED;
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

AbstractBaseMainDlg::AbstractBaseMainDlg( UINT IDD,
                                          CWnd* rpParent,
                                          GenericInterfaceContainer* pGIC,
                                          GenericInterface* pGIParent,
                                          const Command& rCommand,
                                          const DString &dialogName)
: BaseDlg( IDD, rpParent, pGIC, pGIParent, rCommand, dialogName )
, m_bPreDelete( false )
, m_bTransactionError( false )
, m_bWarningConfirm(true)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

AbstractBaseMainDlg::~AbstractBaseMainDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************

void AbstractBaseMainDlg::predelete()
{  // We are being deleted so don't call self destruct in PostNCDestroy
   m_bPreDelete = true;

   if( IsWindow( m_hWnd ) )
   {
      DestroyWindow();
   }
}

//******************************************************************************

void AbstractBaseMainDlg::SetAccountCaption()    // Set caption to base + acct + Fund:fund
{
   DString strFund;
   DString fund;
   DString caption;

   fund = strFund = ( LPCTSTR )GetCaptionFundTxt();
   //builds strings like 'Fund:'
   fund += COLUMN;
   strFund += COLUMN;
   strFund += GetFund();
   caption = GetBaseCaption() + COLUMN + SPACE + GetAccount();
   SetWindowText( (caption + (strFund == fund ? NULL_STRING : SPACE + strFund)).c_str() );
}

//******************************************************************************

void AbstractBaseMainDlg::SetCaption(            // Set caption to base + str
                                                 const DString &str
                                    )
{
   SetWindowText( ( GetBaseCaption() + str ).c_str() );
}

//******************************************************************************


//******************************************************************************
//              Protected Methods
//******************************************************************************

BEGIN_MESSAGE_MAP(AbstractBaseMainDlg, BaseDlg)
//{{AFX_MSG_MAP(AbstractBaseMainDlg)
ON_WM_CREATE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************

bool AbstractBaseMainDlg::doSend(
                                GenericInterface *rpGICaller,
                                const I_CHAR * szMessage
                                )
{
   DString str( szMessage );

   if( str == I_( "TrxnsError" ) )
   {
      SetTransactionError( true );
   }
   else if( str == I_( "WarningConfirm" ) && m_bWarningConfirm )
   {
      LoadControlErrorState();

      CONDITIONVECTOR conditions;
      SEVERITY sevRtn = getParent()->getAllErrors(rpGICaller, conditions);

      CONDITIONVECTOR conditionsPacked;
      CONDITIONVECTOR::iterator iter = conditions.begin();
      while( iter != conditions.end( ) )
      {
         bool bFound(false);
         CONDITIONVECTOR::iterator iterPacked = conditionsPacked.begin();
         while( iterPacked != conditionsPacked.end() )
         {
            if( (*iter)->getCode() == (*iterPacked)->getCode() &&
                *((*iter)->getMessage()) == *((*iterPacked)->getMessage()) )
            {
               bFound = true;
               break;
            }
            iterPacked++;
         }
         if( !bFound )
            conditionsPacked.push_back(*iter);

         iter++;
      }
      if( sevRtn >= WARNING )
      {
         if( ConditionMessageBox(conditionsPacked, sevRtn) != IDOK )
            return(false);
      }
   }
   return(true);
}

//******************************************************************************

void AbstractBaseMainDlg::Exit(
                              int ID )
{  // For the IDOK case, note that we are bypassing the UpdateData call in
   // CDialog::OnOK.

   if( !isModal() )
   {  // We're modeless so don't do "normal" stuff
      DestroyWindow();
   }
   else
   {
      EndDialog( ID );
   }
}

//******************************************************************************

void AbstractBaseMainDlg::MoveDialog(                // Move dialog to desired location
                                                     E_GUIPOSITION ePos,                       // Position type
                                                     int iVerticalPos                          // or pixel count vertically
                                    )
{
   TRACE_METHOD( CLASSNAME, MOVEDIALOG );
   WINDOWPLACEMENT     wpParent;            // Parents location
   WINDOWPLACEMENT     wpMe;                // Our location
   long                lWidth;
   long                lHeight;

   // Get the coordinates for both our parent and us
   CWnd *wndParent = GetMyParent();

   if( wndParent )
   {
      // Just in case this is a child of the real parent... takes care of showing
      // a dialog from a tab dialog child.
      if( WS_CHILD & ::GetWindowLong( wndParent->m_hWnd, GWL_STYLE ) )
      {
         wndParent = wndParent->GetParent();
         if( WS_CHILD & ::GetWindowLong( wndParent->m_hWnd, GWL_STYLE ) )
         {
            wndParent = wndParent->GetParent();
         }
      }
   }

   if( !wndParent )
   {
      wndParent = AfxGetMainWnd();
   }
   wndParent->GetWindowPlacement( &wpParent );
   if( wndParent != GetDesktopWindow()
       && wpParent.rcNormalPosition.top == 0 &&
       wpParent.rcNormalPosition.left == 0 )
   {  // Our parent seems to be a client window, so get parent of client window
      ( wndParent->GetParent() )->GetWindowPlacement( &wpParent );
   }
   GetWindowPlacement( &wpMe );

   // Our middle must = our parents middle.  Set our left side
   lWidth = wpMe.rcNormalPosition.right - wpMe.rcNormalPosition.left;
   lHeight = wpMe.rcNormalPosition.bottom - wpMe.rcNormalPosition.top;

   wpMe.rcNormalPosition.left = ( wpParent.rcNormalPosition.right +
                                  wpParent.rcNormalPosition.left - lWidth ) / 2;
   if( wpMe.rcNormalPosition.left < 0 )
   {
      wpMe.rcNormalPosition.left = 0;
   }

   wpMe.rcNormalPosition.right = wpMe.rcNormalPosition.left + lWidth;

   WINDOWPLACEMENT     wpDesktop;      // Desktops location
   RECT r;
   UINT a=0,b=0;
   switch( ePos )
   {
      case GUIPOS_TOP:
         // Our top must be even with our parent's top
         wpMe.rcNormalPosition.top = wpParent.rcNormalPosition.top;
         break;

      case GUIPOS_BOTTOM:
         // Our bottom must be lined up with our parents bottom
         wpMe.rcNormalPosition.top = wpParent.rcNormalPosition.bottom -
                                     lHeight;
         // if this causes the top of the dialog to go off the top of the screen,
         // position the dialog with the top lined up with the bottom of
         // the parent dialog
         if( wpMe.rcNormalPosition.top < 0 )
         {
            wpMe.rcNormalPosition.top = wpParent.rcNormalPosition.bottom;
         }
         break;

      case GUIPOS_BELOW:
         // Our top must be below our parents bottom
         wpMe.rcNormalPosition.top = wpParent.rcNormalPosition.bottom;
         break;

         // if aligned with desktop bottom and there is a gap between top window, move up to the bottom of the
         // top window
      case GUIPOS_DESKTOPBOTTOM:
         // Our bottom must be lined up with desktop bottom
/*
         GetDesktopWindow()->GetWindowPlacement( &wpDesktop );
         wpMe.rcNormalPosition.top = (wpDesktop.rcNormalPosition.bottom -lHeight< wpParent.rcNormalPosition.bottom )?
        wpDesktop.rcNormalPosition.bottom-lHeight : wpParent.rcNormalPosition.bottom;
*/
         SystemParametersInfo(SPI_GETWORKAREA, a, &r, b);
         wpMe.rcNormalPosition.top = (r.bottom -lHeight< wpParent.rcNormalPosition.bottom )?
                                     r.bottom-lHeight : wpParent.rcNormalPosition.bottom;
         break;

      case GUIPOS_DESKTOPLEFT:
         // position along left of desktop
         wpMe.rcNormalPosition.left = 0;
         wpMe.rcNormalPosition.right = lWidth;
         // default Our bottom to desktop bottom
         GetDesktopWindow()->GetWindowPlacement( &wpDesktop );
         wpMe.rcNormalPosition.top = wpDesktop.rcNormalPosition.bottom -
                                     lHeight;
         break;

      case GUIPOS_VERTICAL:
         // Positioning vertically as specified
         wpMe.rcNormalPosition.top += iVerticalPos;
         break;
      default:
         ASSERT( 0 );  // bad enum
         break;
   }
   wpMe.rcNormalPosition.bottom = wpMe.rcNormalPosition.top + lHeight;

   // We know where we're supposed to be, put 'er there
   SetWindowPlacement( &wpMe );
}

//******************************************************************************
//              Message Handlers
//******************************************************************************

void AbstractBaseMainDlg::OnCancel()
{ 
   if( canCancel() )
   {
      if( PreCancel() )
      {  // Do base processing
         if( getParent()->cancel( this ) )
         {
            // Allow derived class to do necessary cleanup, parameter passing, etc
            // TODO - Change to DialogEndInProgress
            SetCancelInProgress();
            PostCancel( true );     
            Exit( IDCANCEL );
         }
      }
      else
      {
         PostCancel( false );     
      }
   }
}

//******************************************************************************

int AbstractBaseMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if( BaseDlg::OnCreate( lpCreateStruct ) == -1 )
   {
      return(-1);
   }

   if( !isModal() )
   {  // We want all Modeless dialogs to have a button on the taskbar so add the
      // appwindow bit
      ModifyStyleEx( 0, WS_EX_APPWINDOW );
   }

   return(0);
}

//******************************************************************************

BOOL AbstractBaseMainDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
//   unsigned array[ INDICATOR_COUNT ] =
//   { 1, 2, 3, 4};   // Random numbers?

   BaseDlg::OnInitDialog();

   if( !GetMyParent() )
   {  // Get substitute parent for NULL window
      SetMyParent( AfxGetMainWnd() );
   }

   m_statusBar.Create( this, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | WS_GROUP | WS_DISABLED );
   RepositionBars( AFX_IDW_STATUS_BAR, AFX_IDW_STATUS_BAR, 0 );

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void AbstractBaseMainDlg::OnOK()
{ 
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, ONOK );
   CWaitCursor  wait;

   if (getUpdateFlag())
   {
       I_CHAR* pUserAccessCode = GetUserAccesFunctionCode();

       if (NULL != pUserAccessCode)
       {
            bool bCreatePermission = hasCreatePermission(pUserAccessCode);
            bool bUpdatePermission = hasUpdatePermission(pUserAccessCode);
            bool bDeletePermission = hasDeletePermission(pUserAccessCode);

            if (!bCreatePermission && !bUpdatePermission && !bDeletePermission)
            {
                Exit(IDOK);
                return;
            }
       }
   }

   m_statusBar.SetMessageStatusBar( NULL_STRING );
   m_bTransactionError = false;
//   if ( ProcessControls() )
   ProcessListControls();
   ProcessControls();
   ProcessTabControls();
   {  //
      if( PreOk() )                      // Give subclasses chance to process
      {
         // Only exit if subclass says ok
         if( getParent()->ok( this ) )
         {
            //it might return WARNING when there is a condition to be displayed
            //here it shouldn't be returned SEVER_ERROR !
            SEVERITY severity = GETHIGHESTSEVERITY();
            //If user choose not to refresh, warning message only come up after confirmation screen and submission of data to back end
            DString trxnsWarnings;
            getParameter( I_( "TrxnsWarnings" ), trxnsWarnings );
            if ( severity == WARNING  && trxnsWarnings == I_("Y")) 
             {
                ConditionMessageBox( FRAMEBELOW(), severity, 0, true );     
 
 // TODO - need to give user chance to halt this flow if doesn't want to continue
 //   because of warning              
             }
            // Give derived class a chance to cleanup, pass parameters, etc.
// TODO - Change to DialogEndInProgress
            SetCancelInProgress();
            PostOk( true );
            Exit( IDOK );
            return;
         }
      }
      // Check for errors on frame first
      if( CONDITIONCOUNT() > 0 )
      {
         if( GETHIGHESTSEVERITY() > WARNING )
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      }
      else  if( !IsTransactionError() ) // check if it is not transaction error
      {  // Check for general CBO errors
         CONDITIONVECTOR conditions;
         SEVERITY sevRtn = getParent()->getErrors( this, BF::NullContainerId, ifds::NullFieldId, conditions );
         if( sevRtn > WARNING )
         {
            ConditionMessageBox( conditions, sevRtn );
         }
      }
   }

   // Avoid further processing if transaction error occurred
   if( !IsTransactionError() )
   {  // We failed to leave - here we need to force regetting the error state 
      // for each control. If we are in confirmation, usualy we fail because of
      // transactions errors; we shouldn't force loading the error state, 
      // because we need to close the worksession.
      PostOk( false );
      m_statusBar.SetMessageStatusBar( NULL_STRING );
      SetFocus();
      // Reset errors and focus of first control with error (if possible)
      LoadControlErrorState();
   }
   else
   {  // Cancel this dialog
      setUpdateFlag( false ); // we don't want to see discard dlg in this case
      BFWorkSession * worksession = getBFWorkSession();
      worksession->setHadTrxnError(true);
      worksession->setIsEndSession(true);
      PostMessage( WM_COMMAND, IDCANCEL );
      if( getParent()->getCommandName() != CMD_BPROC_CONFIRMATION && isKillWorkSessiononTxnError())
      {  // Once we get to initiating dialog, be sure and end the session.
         // Transaction errors are bubbled up and we only want to do this once.
         GetMainView()->PostMessage( UM_ENDSESSION );
      }
   }
}

//******************************************************************************

void AbstractBaseMainDlg::PostNcDestroy()
{  
   if( !isModal() && !m_bPreDelete )
   {  // Tell the GenericInterfaceContainer to delete us, if not already being
      // deleted.  This should only occur when the user is closing the
      // dialog (not when the dialog is being deleted programatically).
      getGIContainer()->modelessDestroySelf( this );
   }
   else
   {
      BaseDlg::PostNcDestroy();
   }
}

//******************************************************************************
//              Private methods
//******************************************************************************

E_COMMANDRETURN AbstractBaseMainDlg::doProcess()
{
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   E_DLGCOMMANDRETURN dlgRtn = DoProcess();

   if( DLGCMD_OK == dlgRtn )
   {  // Must be DLGCMD_OK to show dialog
      if( !isModal() )
      {  // Create modeless
         try
         {  // Specifically check for creation errors
            if( Create( GetIDD(), NULL ) )
            {  // For now we are setting all modeless dialogs as belonging to 
               // our main frame window.  When we create modal dialogs, they
               // are created using the same window as a parent so all modeless
               // dialogs cannot be accessed while the modal dialog is in 
               // process.  If we want to control modal dialogs by WorkSession
               // in the future this would have to be changed - could possibly
               // iterate through modeless dialogs and disable them 
               // individually.
               // NOTE:  For some reason SetOwner has to be used (as opposed to
               // just setting the parent) or the MFC code still thinks that
               // there is no "ParentOwner" for some weird reason.  It appears
               // that MFC knows about the parent, but Windows doesn't - and
               // MFC uses a windows call to get the parent instead of relying
               // on its own information.  Anyway, without using SetOwner, 
               // windows is not preventing user input to all modeless dialogs
               // when a modal dialog is running.
               SetOwner( AfxGetMainWnd() );
               rtn = CMD_MODELESS_INPROCESS;
            }
         }
         catch( ... )
         {
         }
         if( CMD_FAILURE == rtn )
         {  // Something wrong
            DString idiStr;
            DString name = DStringA( typeid( *this ).name() );
            addIDITagValue( idiStr, DIALOG, name );
            ADDCONDITIONFROMFILEIDI( CND::GUI_ERR_DIALOG_CREATE_FAILED, idiStr );
         }
      }
      else
      {  // Create modal
         try
         {  // Specifically check for modal errors
            int iRtn = DoModal();
            switch( iRtn )
            {
               case IDOK:
                  rtn = CMD_OK;
                  break;
               case IDCANCEL:
                  rtn = CMD_CANCEL;
                  break;
               default:
                  rtn = CMD_FAILURE;
                  break;
            }
            if( GetMyParent() )
            {  // For quick refresh
               GetMyParent()->UpdateWindow();
            }
         }
         catch( ... )
         {
         }
         if( CMD_FAILURE == rtn )
         {  // Something wrong
            DString idiStr;
            DString name = DStringA( typeid( *this ).name() );
            addIDITagValue( idiStr, DIALOG, name );
            ADDCONDITIONFROMFILEIDI( CND::GUI_ERR_DOMODAL_FAILED, idiStr );
         }
      }
   }
   else switch( dlgRtn )
      {
         case DLGCMD_OKCONTINUE:
            rtn = CMD_OK;
            break;
         case DLGCMD_CANCEL:
            rtn = CMD_CANCEL;
            break;
         default:
            rtn = CMD_FAILURE;
            break;
      }
   return(rtn);
}

//******************************************************************************

bool AbstractBaseMainDlg::loadPosition()
{
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, I_( "loadPosition" ) );
   DString keyName, strHold;
   bool result = false;

   try
   {
      CRect r;
      int coord;
      WINDOWPLACEMENT tmp;
      GetWindowPlacement( &tmp );
      r = tmp.rcNormalPosition;

      ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
      keyName = getCommand().getKey();
      Configuration workstation = pWorkstation->retrieveConfig( keyName );

      strHold = workstation.getValueAsString( I_( "X" ) );
      if( strHold.empty() )
      {
         return(false);
      }
      coord = asInteger( strHold );
      if( coord <= 0 )
      {
         return(false);
      }
      r.left = r.left - r.right + coord;
      r.right = coord;

      strHold = workstation.getValueAsString( I_( "Y" ) );
      if( strHold.empty() )
      {
         return(false);
      }
      coord = asInteger( strHold );
      if( coord <= 0 )
      {
         return(false);
      }

      r.top = r.top - r.bottom + coord;
      r.bottom = coord;

      result = true;
      MoveWindow( r );

   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

   return(result);
}

//******************************************************************************

bool AbstractBaseMainDlg::savePosition()
{
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, I_( "savePosition" ) );
   DString keyName, strHold;
   bool result = false;

   try
   {
      CRect r;
      WINDOWPLACEMENT tmp;
      GetWindowPlacement( &tmp );
      r = tmp.rcNormalPosition;

      ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
      keyName = getCommand().getKey();
      Configuration workstation = pWorkstation->retrieveConfig( keyName );
      strHold = I_( "X=" );
      strHold += asString( r.right );
      workstation.set( strHold );
      strHold = I_( "Y=" );
      strHold += asString( r.bottom );
      workstation.set( strHold );
      pWorkstation->storeConfig( workstation );
      pWorkstation->persist();   // Throws on bad reg config
      result = true;
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

   return(result);
}

//******************************************************************************

// ying: i only fix this for display name in gui, so i it put here
void AbstractBaseMainDlg::getDisplayName( const BFContainerId& idContainer,
                                          const BFFieldId &idFirstName,
                                          const BFFieldId &idLastName,
                                          DString &Name,
                                          bool FirstNameLast ) const
{
   DString first, last;
   getParent()->getField( this, idContainer, idFirstName, first );
   first.strip();
   getParent()->getField( this, idContainer, idLastName, last );
   last.strip();

   if( FirstNameLast )
   {
      Name = last + SPACE + first;
   }
   else
   {
      Name = first + SPACE + last;
   }

   Name.strip();
}

//******************************************************************************

void AbstractBaseMainDlg::GetDialogText (int nIDC, DString &pt)
{
   CString strTemp;
   CWnd *pc = GetDlgItem(nIDC);

   if( pc != NULL )
   {
      pc->GetWindowText(strTemp);
      pt = DString(strTemp);
   }
}

//******************************************************************************

void AbstractBaseMainDlg::SetDialogText(int nIDC, DString &pt)
{
   CWnd *pc = GetDlgItem(nIDC);
   if( pc != NULL )
      pc->SetWindowText(pt.c_str());
}

//******************************************************************************

void AbstractBaseMainDlg::SetShrAcctCaption(
                                           DString &ShrNum,
                                           DString &AcctNum,
                                           DString &EntityName
                                           )
{
   ShrNum.strip().stripLeading( I_CHAR( '0' ) );
   AcctNum.strip().stripLeading( I_CHAR( '0' ) );
   EntityName.strip();

   CString caption = GetBaseCaption().c_str();

   // for compatibility
   int i = caption.Find( _T(":") );
   if( i != -1 )
   {
      caption = caption.Left( i );
   }

   if( ShrNum != NULL_STRING ||
       AcctNum != NULL_STRING ||
       EntityName != NULL_STRING )
   {
      caption += COLUMN;
      caption += SPACE;
   }

   if( ShrNum != NULL_STRING )
   {
      caption += GetCaptionShareNumTxt() + SPACE + ShrNum.c_str() + SEMICOLUMN;
   }

   if( AcctNum != NULL_STRING )
   {
      caption += SPACE + GetCaptionAcctNumTxt() + SPACE + AcctNum.c_str() + SEMICOLUMN;
   }

   caption += SPACE;
   caption += EntityName.c_str();

   SetWindowText( caption );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/abstractbasemaindlg.cpp-arc  $
//
//   Rev 1.22   Feb 06 2009 14:59:30   purdyech
//Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
//
//   Rev 1.21   Sep 15 2005 12:58:00   popescu
//Incident # 403519 - saved/restored the size of the dialog in the registry
//
//   Rev 1.20   Sep 07 2005 11:10:40   fengyong
//Add scroll and resize feature to dialogs
//
//   Rev 1.19   Jun 20 2005 18:43:04   porteanm
//PET1024 FN40 - Guarantee Adjustments.
//
//   Rev 1.18   Jun 20 2005 06:24:52   popescu
//PET1024 FN40 - Guarantee Adjustments - displayed the Warning Conditions Message Box.
//
//   Rev 1.17   Apr 19 2005 15:24:28   yingbaol
//Incident290524:fix crash if there is a transaction error.
 * 
 *    Rev 1.16   Jan 14 2003 11:05:02   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.15   Jan 06 2003 16:45:38   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.14   Oct 09 2002 17:42:34   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.13   Oct 07 2002 14:04:34   KOVACSRO
 * OnOK calls ProcessTabControls().
 * 
 *    Rev 1.12   Sep 10 2002 14:34:24   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.11   Sep 03 2002 12:45:08   PURDYECH
 * BFFieldId and ClientLocale changes
 * 
 *    Rev 1.10   Aug 29 2002 12:57:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   Jul 16 2002 09:53:40   KOVACSRO
 * OnOk calls ProcessListControls before calling ProcessControls (this is necessary for timer list controls)
 * 
 *    Rev 1.8   27 Mar 2002 20:04:38   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.7   04 Jul 2001 16:46:14   YINGZ
 * implement cancel to give user warning when there are updates
 * 
 *    Rev 1.6   29 Jun 2001 10:56:38   YINGZ
 * add canCancel to support cancel machenism
 * 
 *    Rev 1.5   Jun 19 2001 15:20:24   HUANGSHA
 * fix bug for adding the duplicated warning msg
 * 
 *    Rev 1.4   Nov 29 2000 17:43:24   WINNIE
 * Warning message handle by doSend method rather than ok2 : make warning pop up before sending data to backend, allow user to cancel or continue
 * 
 *    Rev 1.3   Nov 22 2000 17:11:50   HUANGSHA
 * added Warning Message Box popup function
 * 
 *    Rev 1.2   Apr 05 2000 15:15:56   DT24433
 * changed usage of GIContainer
 * 
 *    Rev 1.1   Mar 13 2000 18:05:44   DT24433
 * changed to not issue endsession from confirmation dialog when transaction errors exist, but leave this up to whoever initiated confirmation
 * 
 *    Rev 1.0   Mar 02 2000 11:39:20   MCNABBGL
 * Initial revision.
 *
 */
