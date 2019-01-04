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
// ^FILE   : ConditionMessageDialog.cpp
// ^AUTHOR : Kristel Weber
// ^DATE   : 7/29/97
//
// ^CLASS    : ConditionMessageDialog
//
// ^MEMBER VARIABLES :
//
// ----------------------------------------------------------
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"

#ifndef POPUPMESSAGERES_H
   #define POPUPMESSAGERES_H
   #include "PopupMessageRes.h"
#endif
#include "ConditionMessageDialog.h"
#include <configmanager.hpp>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDM_COPY_TO_CLIPBOARD (SC_SIZE - 1)
#define IDM_DISPLAY_DETAILS (SC_SIZE - 2)

//******************************************************************************

int ConditionMessageBox( const Condition *cond, int helpContext, bool bTransactionWarning )
{
   ConditionMessageDialog dlg( cond, helpContext, bTransactionWarning );
   return(dlg.DoModal());
}

//******************************************************************************

int ConditionMessageBox( const Condition &cond, int helpContext, bool bTransactionWarning )
{
   return(ConditionMessageBox( &cond, helpContext, bTransactionWarning ));
}

//******************************************************************************

int ConditionMessageBox( Frame *pFrame, SEVERITY severity, int helpContext, bool bTransactionWarning )
{
   ConditionMessageDialog dlg( pFrame, severity, helpContext, bTransactionWarning );
   return(dlg.DoModal());
}

//******************************************************************************

int ConditionMessageBox(
                       CONDITIONVECTOR &conditions,
                       SEVERITY severity,
                       int helpContext,
					   bool bTransactionWarning
                       )
{
   ConditionMessageDialog dlg( conditions, severity, helpContext, bTransactionWarning );
   return(dlg.DoModal());
}

//******************************************************************************

int ConditionMessageBox( const ConditionException &ce, int helpContext, bool bTransactionWarning )
{
   ConditionMessageDialog dlg( ce, helpContext, bTransactionWarning );
   return(dlg.DoModal());
}

//******************************************************************************

bool continueFromCondition( Frame *pFrame, SEVERITY sev )
{
   if( sev > NO_SEVERITY )
   {
      int iRet = ConditionMessageBox( pFrame, pFrame->getMaxSeverity() );
      if( iRet != IDOK || sev > WARNING )
      {
         return( false );
      }
   }
   return(true);
}

//******************************************************************************

bool continueFromCondition( Frame *pFrame, bool bRtn )
{
   if( !bRtn )
   {
      int iRet = ConditionMessageBox( pFrame, pFrame->getMaxSeverity() );
      if( iRet != IDOK )
      {
         return( false );
      }
   }
   return(true);
}

//******************************************************************************
//             PUBLIC METHODS
//******************************************************************************

BEGIN_MESSAGE_MAP(ConditionMessageDialog, ModalMessageDialog)
ON_WM_SYSCOMMAND()
ON_COMMAND(ID_ACCEL_MSGDETAIL, OnAccelMsgDetail)
END_MESSAGE_MAP()

BOOL ConditionMessageDialog::OnInitDialog() {
   setSystemMenu();
   return( ModalMessageDialog::OnInitDialog() );
}

afx_msg void ConditionMessageDialog::OnSysCommand(UINT nID, LPARAM lp)
{
  if (nID==IDM_COPY_TO_CLIPBOARD) {
      HGLOBAL clipbuffer;
      static TCHAR * buffer;

      OpenClipboard();
      EmptyClipboard();
      DWORD dw = _strDetail.length() + 1;
      clipbuffer = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, dw * sizeof(TCHAR));
      buffer = (TCHAR *)GlobalLock(clipbuffer);
      lstrcpy(buffer, _strDetail.c_str());
      GlobalUnlock(clipbuffer);
      SetClipboardData(CF_UNICODETEXT,clipbuffer);
      CloseClipboard();
  }
  else if (nID==IDM_DISPLAY_DETAILS) {
      AfxMessageBox( _strDetail.c_str() );
  }
  // pass to base class: important!
  return ModalMessageDialog::OnSysCommand(nID, lp);
}

//******************************************************************************

ConditionMessageDialog::ConditionMessageDialog( const Condition *cond,
                                                int helpContext,
											               bool bTransactionWarning
                                                ) :
ModalMessageDialog( ),
_freeCondition(false),
_condition(NULL)
{
   setIconStyle( cond->getSeverity(), helpContext, bTransactionWarning );
   DString msg;
   formatMessage( *cond, msg );
   setText( msg.c_str() );

   _condition = (Condition *)cond;
}

//******************************************************************************

ConditionMessageDialog::ConditionMessageDialog(
                                              FRAMEDEF(),
                                              SEVERITY severity,
                                              int helpContext,
											  bool bTransactionWarning
                                              ) :
ModalMessageDialog(),
_freeCondition(false),
_condition(NULL)
{
   setIconStyle( severity, helpContext, bTransactionWarning );
   formatMessage( pFrame, severity );
   _severity = severity;
}

//******************************************************************************

ConditionMessageDialog::ConditionMessageDialog(
                                              CONDITIONVECTOR &conditions,
                                              SEVERITY severity,
                                              int helpContext,
											  bool bTransactionWarning
                                              ) :
ModalMessageDialog(),
_freeCondition(false),
_condition(NULL)
{
   setIconStyle( severity, helpContext, bTransactionWarning );
   formatMessage( conditions, severity );
   _severity = severity;
}

//******************************************************************************

ConditionMessageDialog::ConditionMessageDialog(
         const ConditionException &ce,
         int helpContext,
			bool bTransactionWarning ) 
: ModalMessageDialog()
, _freeCondition(false)
, _condition(NULL)
{
   DString msg;
   _condition = new Condition( ce.getComponentName(), ce.getMethodName(),
                               ce.getCode(), ce.getCodeString(), ce.getSeverity(), ce.getFileName(), ce.getLineNumber(), 
                               ce.getMessage(), ce.getCorrection(),ce.getSuppress() );
   if( _condition )
   {
      _freeCondition = true;
      setIconStyle( ce.getSeverity(), helpContext, bTransactionWarning );
      formatMessage( *_condition, msg );
   }
   else
   {
      setIconStyle( ce.getSeverity(), helpContext, bTransactionWarning );
      msg = ce.getMessage();
   }
   setText( msg.c_str() );
}

//******************************************************************************

ConditionMessageDialog::~ConditionMessageDialog( )
{
   if( _freeCondition )
   {
      delete _condition;
   }
}

//******************************************************************************

void ConditionMessageDialog::OnAccelMsgDetail()
{
   AfxMessageBox( _strDetail.c_str() );
}

//******************************************************************************

void ConditionMessageDialog::formatDetail( const Condition &cond )
{
   _strDetail += I_( "Condition: " );
   _strDetail += cond.getMessage();
   _strDetail += I_( "\n" );

   I_CHAR str[10];
   _strDetail += I_( "code = " );
   _strDetail += i_itot( cond.getCode(), str, 10 );
   _strDetail += I_(" [");
   _strDetail += cond.getCodeString();
   _strDetail += I_("]");
   _strDetail += I_( ", severity = " );
   _strDetail += i_itot( cond.getSeverity(), str, 10 );
   _strDetail += I_( ", component name = " );
   _strDetail += cond.getComponentName();
   _strDetail += I_( ", method name = " );
   _strDetail += cond.getMethodName();
   _strDetail += I_( ", in file " );
   _strDetail += DString( DStringA( cond.getFileName() ) );
   _strDetail += I_( ", at line " );
   _strDetail += i_itot( cond.getLineNumber(), str, 10 );
   _strDetail += I_( "\n\n" );
}

//******************************************************************************

void ConditionMessageDialog::formatMessage( Frame *pFrame, SEVERITY severity )
{

#ifndef _DEBUG
   PACKFRAMECONDITIONS();
#endif

   Condition *cond;

   DString msg;
   for( int i = 0; i < pFrame->getCount(); i++ )
   {
      cond = pFrame->getCondition( i );
      if( ( NO_SEVERITY == severity ) || ( cond->getSeverity() == severity ) )
      {
         formatMessage( *cond, msg );
      }
   }
   setText( msg.c_str() );
}

//******************************************************************************

void ConditionMessageDialog::formatMessage(
                                          CONDITIONVECTOR &conditions,
                                          SEVERITY severity
                                          )
{
   Condition *cond;
   DString msg;

   for( int i = 0; i < conditions.size(); i++ )
   {
      cond = conditions[i];
      if( ( NO_SEVERITY == severity ) || ( cond->getSeverity() == severity ) )
      {
         formatMessage( *cond, msg );
      }
   }
   setText( msg.c_str() );
}

//******************************************************************************

void ConditionMessageDialog::formatMessage( const Condition &cond, DString &msg )
{
   if( msg != NULL_STRING ) {
      msg += I_( "\n" );
   }
   msg += cond.getMessage();
   DString dstrCorrection(cond.getCorrection());
   if( dstrCorrection.strip() != NULL_STRING ) {
      msg += I_( "\n--->" );
      msg += cond.getCorrection();
   }
   if( GetConfigValueAsBool( I_("Support"), I_("DisplayConditionName") ) ) {
      msg += I_("\nRef: ");
      msg += cond.getCodeString();
   }
   msg += I_("\n");

#ifdef _DEBUG
   if( CRITICAL_ERROR == cond.getSeverity() ) 
   {
      I_CHAR str[10];
      msg += I_( "\nCondition: code = " );
      msg += i_itot( cond.getCode(), str, 10 );
      msg += I_(" [");
      msg += cond.getCodeString();
      msg += I_("]");
      msg += I_( ", severity = " );
      msg += i_itot( cond.getSeverity(), str, 10 );
      msg += I_( "\ncomponent name = " );
      msg += cond.getComponentName();
      msg += I_( ", method name = " );
      msg += cond.getMethodName();
      msg += I_( "\n" );
   }
#endif

   formatDetail( cond );
}

void ConditionMessageDialog::setSystemMenu() {
   CMenu* pSysMenu = GetSystemMenu(FALSE);
   if( NULL != pSysMenu ) {
      CString strCopyMenu = "Copy to Clipboard";
      pSysMenu->AppendMenu( MF_SEPARATOR );
      pSysMenu->AppendMenu( MF_STRING, IDM_COPY_TO_CLIPBOARD, strCopyMenu );
      pSysMenu->AppendMenu( MF_STRING, IDM_DISPLAY_DETAILS, CString("Display Details") );
   }
}

//******************************************************************************
void ConditionMessageDialog::setIconStyle( SEVERITY severity, 
										   int helpContext, 
										   bool bTransactionWarning )
{
   int style = MB_OK;

   if ( bTransactionWarning )
	   style = style |= MB_ICONINFORMATION;
   else
   {
		style = ( severity == WARNING ? MB_OKCANCEL : MB_OK );

		switch( severity )
		{
			//      case TRACE_ONLY:    style |= MB_ICONINFORMATION;      break;
			case INFORMATIONAL:       style |= MB_ICONINFORMATION;      break;
			case WARNING:             style |= MB_ICONWARNING;          break;
			case SEVERE_ERROR:        style |= MB_ICONERROR;            break;
			case CRITICAL_ERROR:      style |= MB_ICONERROR;            break;
		}
   }

   if( helpContext )
   {
      style |= MB_HELP;
   }

   setStyle( style );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/conditionmessagedialog.cpp-arc  $
//
//   Rev 1.6   Sep 23 2009 01:22:22   purdyech
//Track Condition Name as well as Code.
//Add "Display Details" option to system menu on Error Popup.
//
//   Rev 1.5   Jun 05 2009 12:16:58   purdyech
//Added "Copy to Clipboard" on system menu.
//
//   Rev 1.4   Jun 20 2005 18:42:46   porteanm
//PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.3   Oct 09 2002 17:42:36   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   Sep 10 2002 14:34:26   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.1   Jan 29 2001 16:26:20   HUANGSHA
 * strip out the space for the condition action
 * 
 *    Rev 1.0   Feb 15 2000 11:01:38   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.6   Jan 21 2000 11:48:36   YINGZ
 * conditionally show message
 * 
 *    Rev 1.5   Jan 21 2000 11:47:06   YINGZ
 * conditionally show message
 * 
 *    Rev 1.4   Jan 20 2000 16:15:34   YINGZ
 * take out some msgs in release mode
 * 
 *    Rev 1.3   Jan 11 2000 17:21:50   DT24433
 * added methods to support a CONDITIONVECTOR
 * 
 *    Rev 1.2   Oct 15 1999 11:08:00   POPESCUS
 * Fixed compiling issues related to the new infra-1900
 * 
 *    Rev 1.1   Jul 08 1999 10:04:50   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
