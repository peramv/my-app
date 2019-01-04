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

#include <uibase\BaseDlg.h>
#include <uibase\IFDSStatusBar.h>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

// Forward declares
class WindowManager;
class BFContainerId;

/**
 * Represents the different dialog DoProcess command return states.
 *
 * <pre>
 *@@ These are the valid return states:
 *@@   DLGCMD_OK              - Good return, show dialog.
 *@@   DLGCMD_CANCEL          - Escape return, don't show dialog.
 *@@   DLGCMD_OKCONTINUE      - Good return, don't show dialog.
 *@@   DLGCMD_FAILURE         - DoProcess failed to work correctly.
 * </pre>
 */
enum E_DLGCOMMANDRETURN
{
   DLGCMD_OK = CMD_OK,
   DLGCMD_CANCEL = CMD_CANCEL,
   DLGCMD_FAILURE = CMD_FAILURE,
   DLGCMD_OKCONTINUE
};

/**
 * Represents the different relative position for moving a dialog.
 *
 * <pre>
 *@@ These are the valid relative positions:
 *@@   GUIPOS_TOP             - Top = top of parent
 *@@   GUIPOS_BOTTOM          - Bottom = bottom of parent
 *@@   GUIPOS_BELOW           - Top = bottom of parent
 *@@   GUIPOS_DESKTOPBOTTOM   - Bottom = bottom of desktop
 *@@   GUIPOS_DESKTOPLEFT     - Left = left of desktop ??
 *@@   GUIPOS_VERTICAL        - Top = x pixels from top of desktop
 * </pre>
 */
enum E_GUIPOSITION
{
   GUIPOS_TOP,
   GUIPOS_BOTTOM,
   GUIPOS_BELOW,
   GUIPOS_DESKTOPBOTTOM,
   GUIPOS_DESKTOPLEFT,
   GUIPOS_VERTICAL
};

/**
 * This is the abstract base class for all main modal/modeless dialogs.
 *
 * This class provides support for using a dialog as either modal or modeless
 * along with various other features.  AbstractBaseMainDlg adds this support so
 * that the derived dialog usually does not have to concern itself with whether
 * it is running in a modal or modeless state.
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 12/10/98</dd></dl>
 * @version 0.1
 */
class WIN32UIBASE_LINKAGE AbstractBaseMainDlg : public BaseDlg
{
// Construction
public:
   AbstractBaseMainDlg( UINT IDD,
                        CWnd *rpParent,
                        GenericInterfaceContainer* pGIC,
                        GenericInterface* pGIParent,
                        const Command& rCommand,
                        const DString &dialogName);
   virtual ~AbstractBaseMainDlg();
   friend WindowManager;
   void SetDialogText(int nIDC, DString &pt);
   void GetDialogText(int nIDC, DString &pt);

//   void SetManagementCodeStatusBar( const I_CHAR *mgmtCd );
   void SetMessageStatusBar( const int nID ) {m_statusBar.SetMessageStatusBar(nID);}
   void SetMessageStatusBar( const I_CHAR *msg ) {m_statusBar.SetMessageStatusBar(msg);}
//   void SetProfileStatusBar( const I_CHAR *profile );
//   void SetSystemStatusBar( const I_CHAR *sys );

protected:
   void SetShrAcctCaption( DString& ShrNum, DString& AcctNum, DString& EntityName );
   // Generated message map functions
   //{{AFX_MSG(AbstractBaseMainDlg)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   virtual BOOL OnInitDialog();
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()

   /** Because AbstractBaseMainDlg::doProcess is used to perform required functionality,
     * subclasses must implement DoProcess.  DoProcess could be used for any
     * preliminary actions prior to dialog being created (obtaining parameters
     * must occur in doInit.  Return DLGCMD_OK to show dialog, DLGCMD_CANCEL to
     * cancel dialog, DLGCMD_OKCONTINUE for don't show dialog but do ok
     * processing on parent process, DLGCMD_FAILURE for errors.
     * @returns an enum representing the return type.
     */
   virtual E_DLGCOMMANDRETURN DoProcess()
   {
      return(DLGCMD_OK);
   }
   /**
     * If derived clases override this method, they must invoke this method 
     * prior to ending.  We are capturing transaction error indicator here
     * @param rpGICaller - A reference pointer to the calling GenericInterface.
     * @param szMessage - A string literal of the message to send.
     * @returns true if successful
     */
   virtual bool doSend( GenericInterface *rpGICaller,
                        const I_CHAR * szMessage );
   /**
     * This method may be used to directly exit the dialog bypassing and
     * subclass OnOK/OnCancel processing.  This should be exception processing
     * when the derived class knows it needs to exit without additional
     * accessing of class data.  Use instead of EndDialog.
     * @param ID - an integer that should have values IDOK, IDCANCEL, or IDABORT
     */
   void Exit( int ID );
   /**
     * Method to return the display label for Account Number in caption.  Must
     * be overridden by derived class.
     */
   virtual CString GetCaptionAcctNumTxt() = 0;
   /**
     * Get the base caption for the dialog.
     */
   /**
     * Method to return the display label for Fund in caption.  Must
     * be overridden by derived class.
     */
   virtual CString GetCaptionFundTxt() = 0;
   /**
     * Method to return the display label for Share Number in caption.  Must
     * be overridden by derived class.
     */
   virtual CString GetCaptionShareNumTxt() = 0;
   const DString &GetBaseCaption()          // Get base for caption
   {
      return(m_baseCaption.strip());
   }

   void getDisplayName( const BFContainerId& idContainer,
                        const BFFieldId &FirstName,
                        const BFFieldId &LastName,
                        DString& Name,
                        bool FirstNameLast = true ) const;

   bool IsTransactionError()
   {
      return(m_bTransactionError);
   }
   /**
     * This method positions the dialog on the screen.  
     * @param ePos - enum representing relative position
     * @param iVerticalPos - integer for specific vertical pixel position
     */
   void MoveDialog( E_GUIPOSITION ePos, int iVerticalPos );
   /**
     * This method should be overridden in the derived dialog if there is
     * OnCancel processing to be done after the base processing.  Note that
     * the OnCancel processing can no longer be "cancelled" at this point.
     * AbstractBaseMainDlg enforces its actions by making OnCancel private.
     * @param bCancelStatus - true = Cancel successful, false = Cancel failed
     */
   virtual void PostCancel( bool bCancelStatus  ) 
   {
      return;
   }
   /**
     * This method is overridden to provide proper clean up when running 
     * modelessly.  If a subclass overrides this, it must call the classes
     * method when done processing.
     */
   virtual void PostNcDestroy();
   /**
     * This method should be overridden in the derived dialog if there is
     * OnOk processing to be done after the base processing.  Note that the OnOk
     * processing can no longer be "cancelled" at this point.  AbstractBaseMainDlg 
     * enforces its actions by making OnOk private.
     * @param bOkStatus - true = Ok successful, false = Ok failed
     */
   virtual void PostOk( bool bOkStatus )
   {
      return;
   }
   /**
     * This method should be overridden in the derived dialog if there is
     * OnCancel processing to be done prior to the base processing.  If 
     * PreCancel returns false, conditions should be set.  
     * AbstractBaseMainDlg enforces its actions by making OnCancel private.
     * @returns a bool with true = perform Cancel, false = stop process -
     *   check conditions
     */
   virtual bool PreCancel()
   {
      return(true);
   }
   /**
     * This method allows for a two step destruction of GenericInterface 
     * objects. This is used by dialog objects in particular so DestroyWindow 
     * may be invoked even when being directly deleted.  The
     * GenericInterfaceContainer performs this two step process.  To make this
     * process consistent, this two step process should be implemented wherever
     * deletes occur.
     */
   virtual void predelete();                 // Override to DestroyWindow if
                                             //  necessary
   /**
     * This method should be overridden in the derived dialog if there is
     * OnOk processing to be done prior to base processing.  If PreOk returns
     * false, conditions should be set.
     * AbstractBaseMainDlg enforces its actions by making OnOk private.
     * @returns a bool with true = perform Ok, false = stop process - check
     *   conditions
     */
   virtual bool PreOk()
   {
      return(true);
   }
   /**
     * Set the caption to base caption + fund/account.
     */
   void SetAccountCaption();
   /**
     * Set the base caption for the dialog.  This is originally set to the title
     * from the dialog resource.  The base caption is used as the beginning part
     * for other captions.
     */
   void SetBaseCaption(                      // Set base caption
                                             const I_CHAR *base                     // Base to set
                      )
   {
      m_baseCaption = base;
   }
   /**
     * Set the caption to base caption + string.
     */
   void SetCaption( const DString &str);
   /**
     * Set the transaction error flag
     */
   void SetTransactionError( bool bFlag )
   {
      m_bTransactionError = bFlag;
   }
   void SetWarningConfirm( bool bFlag )
   {
      m_bWarningConfirm = bFlag;
   }

   // return true if ok to cancel
   virtual bool canCancel()
   {
      return(true);
   }

   virtual bool isKillWorkSessiononTxnError()
   {
      return(true);
   }

protected:
   IFDSStatusBar m_statusBar;

private:
   DString m_baseCaption;                   // Base part of caption
   bool m_bPreDelete;                       // Used to track if preDelete called 
   bool m_bTransactionError;                // Set to true when transaction
                                            //  errors have occurred to prevent
                                            //  further processing in ok2
   bool m_bWarningConfirm;

   bool loadPosition();
   bool savePosition();
   /**
     * Implementation to support the process method.  This method must not be
     * overridden, derived classes must implement DoProcess.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   /**
     * This method is overridden and made private to enforce proper handling
     * when the dialog is modeless.  The subclass should override Cancel.  To 
     * invoke from a subclass use PostMessage( WM_COMMAND, IDCANCEL ).
     */
   virtual void OnCancel();                  // Override for modeless
   /**
     * This method is overridden and made private to enforce proper handling
     * when the dialog is modeless.  The subclass should override Ok.  To 
     * invoke from a subclass use PostMessage( WM_COMMAND, IDOK ).
     */
   virtual void OnOK();                      // Override for modeless
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/AbstractBaseMainDlg.h-arc  $
 * 
 *    Rev 1.10   Feb 06 2009 14:59:22   purdyech
 * Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
 * 
 *    Rev 1.9   Sep 15 2005 12:58:02   popescu
 * Incident # 403519 - saved/restored the size of the dialog in the registry
 * 
 *    Rev 1.8   Jan 14 2003 11:05:06   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.7   Jan 06 2003 16:45:44   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.6   Nov 27 2002 15:05:14   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.5   Oct 09 2002 17:42:34   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.4   Aug 29 2002 12:57:04   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.3   19 Mar 2002 13:36:10   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.2   29 Jun 2001 10:56:48   YINGZ
 * add canCancel to support cancel machenism
 * 
 *    Rev 1.1   Nov 22 2000 17:11:06   HUANGSHA
 * added Warning Message box popup function
 * 
 *    Rev 1.0   Mar 02 2000 11:39:54   MCNABBGL
 * Initial revision.
 * 
 */
