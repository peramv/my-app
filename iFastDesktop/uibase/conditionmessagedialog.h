#pragma once


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
// ^DATE   : 12/16/97
//
// ^CLASS    : ConditionMessageDialog
//
// ^DESCRIPTION : This class is for a modeless message dialog
//    (MessageBox is modal). After creating an instance of the class,
//    call the createModeless function to create the dialog. Before
//    destroying the dialog instance call the DestroyWindow method.
//
//
// ----------------------------------------------------------
//
// ^METHOD      : 	ConditionMessageDialog
//
// ^DESCRIPTION : constructor
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : createModeless
//
// ^DESCRIPTION : create and display the message dialog
//
// ^PARAMETERS  : 
//   ^^ const I_CHAR *text - message text
//   ^^ CWnd *dlg - parent dialog
//   ^^ HWND hWndCtrl - field control ID to position message next to
//
// ^RETURNS     : BOOL - TRUE if created ok
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : repositionWindow
//
// ^DESCRIPTION : repositions the message dialog window - position relative
//    calling dialog is maintained
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : setMessage
//
// ^DESCRIPTION : set the text of the message to display, and display it
//
// ^PARAMETERS  : 
//   ^^ const I_CHAR *text - new message
//   ^^ HWND hWndCtrl - field control id to position message next to,
//       Defaults to 0.
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
//******************************************************************************

#include <commonport.h>
#include <uibase\ModalMessageDialog.h>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE ConditionMessageDialog : public ModalMessageDialog
{
// Construction
public:
   ConditionMessageDialog(
                         const Condition *cond,
                         int helpContext,
	      					 bool bTransactionWarning
                         );
   ConditionMessageDialog(
                         FRAMEDEF(),
                         SEVERITY severity,
                         int helpContext,
			      			 bool bTransactionWarning
                         );
   ConditionMessageDialog(
                         CONDITIONVECTOR &conditions,
                         SEVERITY severity,
                         int helpContext,
					      	 bool bTransactionWarning
                         );
   ConditionMessageDialog(
                         const ConditionException &ce,
                         int helpContext,
						       bool bTransactionWarning
                         );
   ~ConditionMessageDialog();


// Implementation
protected:
   virtual BOOL OnInitDialog();

   virtual afx_msg void OnAccelMsgDetail();
   virtual afx_msg void OnSysCommand(UINT nID, LPARAM lp);
   DECLARE_MESSAGE_MAP()

private:
   bool _freeCondition;
   Condition *_condition;
   SEVERITY _severity;
   DString _strDetail;      // Saved because frame can get blown away

   void formatMessage(
                     Frame *pFrame,
                     SEVERITY severity
                     );
   void formatMessage(
                     const Condition &cond,
                     DString &msg
                     );
   void formatMessage(
                     CONDITIONVECTOR &conditions,
                     SEVERITY severity
                     );

   void formatDetail(
                    const Condition &cond
                    );
   void setIconStyle( SEVERITY severity,
                      int helpContext,
					       bool bTransactionWarning = false
                    );
   void setSystemMenu();
};

int WIN32UIBASE_LINKAGE ConditionMessageBox( const Condition *cond, int helpContext = 0, bool bTransactionWarning = false );
int WIN32UIBASE_LINKAGE ConditionMessageBox( const Condition &cond, int helpContext = 0, bool bTransactionWarning = false );
int WIN32UIBASE_LINKAGE ConditionMessageBox(
                                           Frame *pFrame,
                                           SEVERITY severity = NO_SEVERITY,
                                           int helpContext = 0,
										   bool bTransactionWarning = false
                                           );
int WIN32UIBASE_LINKAGE ConditionMessageBox(
                                           CONDITIONVECTOR &conditions,
                                           SEVERITY severity = NO_SEVERITY,
                                           int helpContext = 0,
										   bool bTransactionWarning = false
                                           );
int WIN32UIBASE_LINKAGE ConditionMessageBox( const ConditionException &ce, int helpContext = 0, bool bTransactionWarning = false );
bool WIN32UIBASE_LINKAGE continueFromCondition( Frame *pFrame, SEVERITY sev );
bool WIN32UIBASE_LINKAGE continueFromCondition( Frame *pFrame, bool bRtn );

#define DISPLAYCONDITIONFROMFILE( code ) \
   ConditionMessageBox( Condition( cmFrame.getFrame()->getComponentName(), \
                                   cmFrame.getFrame()->getMethodName(), \
                                   code, CM_STRINGIFY(code), __FILE__, __LINE__, FALSE, \
                                   g_conditionManager.getPath(), \
                                   NO_SEVERITY, NULL_STRING ) )

#define DISPLAYCONDITIONFROMFILEIDI( code, idiStr ) \
   ConditionMessageBox( Condition( cmFrame.getFrame()->getComponentName(), \
                                   cmFrame.getFrame()->getMethodName(), \
                                   code, CM_STRINGIFY(code), __FILE__, __LINE__, FALSE, \
                                   g_conditionManager.getPath(), \
                                   NO_SEVERITY, idiStr ) )

#define DISPLAYFRAMECONDITIONS( severity ) \
   PROMOTECONDITIONS(); \
   ConditionMessageBox( cmFrame.getFrame(), severity );

#define DISPLAYCONDITIONS( severity ) \
   ConditionMessageBox( FRAMEBELOW(), severity )


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/conditionmessagedialog.h-arc  $
 * 
 *    Rev 1.7   Sep 23 2009 01:23:10   purdyech
 * Track Condition Name as well as Code.
 * Add "Display Details" option to system menu on Error Popup.
 * 
 *    Rev 1.6   Jun 05 2009 12:15:36   purdyech
 * Added "Copy to Clipboard" on system menu.
 * 
 *    Rev 1.5   Jun 20 2005 18:42:20   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.4   Nov 13 2002 11:43:14   PURDYECH
 * Fixed up C4275 warning error.
 * 
 *    Rev 1.3   Nov 08 2002 10:00:30   PURDYECH
 * Use #pragma warning(...) to remove warning C4275 (non-Dll interface class used as base for interface class).
 * 
 *    Rev 1.2   Oct 09 2002 17:42:38   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.1   19 Mar 2002 13:36:00   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.0   Feb 15 2000 11:00:56   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Jan 11 2000 17:23:32   DT24433
 * added methods to support a CONDITIONVECTOR
 * 
 *    Rev 1.1   Jul 08 1999 10:04:52   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
