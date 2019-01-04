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

#include <uibase\basedlgconstants.h>
#include <uibase\conditionmessagedialog.h>
#include <bfproc\genericinterface.hpp>
#include <bfdata\bfdata.hpp>
#include <uibase\DSTGridWnd.h>
#include <bfutil\bfifds.hpp>

// Forward declarations
class AbstractProcess;
class BaseControl;
class CBOBase;
class DSTListCtrl;
class DSTTabCtrl;
class BFControlFactory;
class CScrollHelper;
class DlgResizeHelper;

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

namespace BASEDLGVARIABLES
{  // This namespace is used for common trace literals used by dialogs.
   extern WIN32UIBASE_LINKAGE const I_CHAR * const CANCEL;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const CLEARCONTROLS;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const DISPLAYLIST;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const DODATAEXCHANGE;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const OK;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const ONBTNCHANGE;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const ONBTNDELETE;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const ONBTNMORE;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const ONBTNSAVE;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const ONCANCEL;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const ONINITDIALOG;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const ONOK;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const ONPOSTINITDIALOG;
   extern WIN32UIBASE_LINKAGE const I_CHAR * const ONDBLCLKLBATTRIB;//yakov
   extern WIN32UIBASE_LINKAGE const I_CHAR * const PREOK;
}

/**@#-*/
using namespace BASEDLGVARIABLES;             // Make available to all dialogs
/**@#+*/

/**
 * This is the abstract base class for all dialogs.
 *
 * This class may be used to add dialog specific (as opposed to process specific)
 * base code.  This class also determines which methods of the GenericInterface
 * are required by subclasses to implement and which ones are optional.
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 12/10/98</dd></dl>
 * @version 0.1
 */

// Protected inheritance?  What does that model?  It makes no sense and prevented new from working,
// so I changed it to public inheritance.  CP 27Mar2002
#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE BaseDlg : public CDialog, public GenericInterface
{

public:
   // Constructor/Destructor
   BaseDlg( UINT IDD, 
            CWnd *rpParent,
            GenericInterfaceContainer* pGIC,
            GenericInterface* pGIParent,
            const Command& rCommand,
            const DString &dialogName);
   virtual ~BaseDlg();

   void UseScrollBar( bool bUseScroll) {  _bScroll = bUseScroll; }
   /**
    * Get the current font of the dialog
    * 
    * @param font   A reference to a LOGFONT structure which will be filled in upon
    *               return from the method.
    */
   void GetDlgFont( LOGFONT &font );
   void SetDlgFont( CFont *pCFont );

   CWnd* GetNextDlgTabItem(CWnd* pWndCtl, BOOL bPrevious = FALSE) const;

   virtual void GetCellProperties( UINT ctrlId,
                                   const DString& rowKey,
                                   const DString& colKey,
                                   BFContainerId& containerId,
                                   BFFieldId& idField,
                                   DString& listItemKey,
                                   int& nCellState,
                                   UINT& cellCtrlType,
                                   int& nCtrlInitMode,
                                   BFFieldId& idSubstitution,
                                   DString& comboList,
                                   DString& mask,
                                   int& nComboSortingMode,
								   DString& dstrAllowedChar
                                   )
   {};
   virtual bool GetCellValue( UINT ctrlId,
                              const DString &rowKey,
                              const DString &colKey,
                              DString &strOut,
                              bool bFormatted)
   {return(false);};
   virtual bool SetCellValue( UINT ctrlId,
                              const DString &rowKey,
                              const DString &colKey,
                              const DString &strIn,
                              bool bFormatted,
                              SEVERITY &sevRtn)
   {return(false);};
   /**
     * provide filtering mechanism for grid control.
     * return true if the item will be shown and false otherwise
     */
   virtual bool GridControlFilter( UINT ctrlId, const DString &rowKey )
   {
      return(true);
   }

   virtual bool OnGridSetCellValue( UINT ctrlId,
                                    const DString &rowKey,
                                    const DString &colKey,
                                    const DString &strIn)
   {return(false);};

   virtual bool OnGridSetCellValueSetKey( UINT ctrlId,
                                          const DString &rowKey,
                                          const DString &strIn){return(false);};

   virtual bool GetOverrideItemString(
                                     long lSubstituteId,
                                     const DString& ColumnKey,
                                     DString& strOut
                                     );
   bool IsCancelInProgress()
   {
      return(m_bCancelInProgress);
   }
   /**
     * provide filtering mechanism for list control.
     * return true if the item will be shown and false otherwise
     */
   virtual bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL )
   {
      return(true);
   }

   // provide action when user double click an list

   /**
     * This method provide action when user double click list control: 
    * @param lSubstituteID substitue ID which has been clicked (??)
     * @param pKey is the key of the item been clicked
     */
   virtual void doDblclkListItem( long lSubstituteID,
                                  const DString *pKey )
   {};
   /**
     * This method is used to initiate the general processing of a command.
     * Derived classes that are commands should implement doProcess for any
     * additional processing.
     * @returns an enum representing the return state
     */
   virtual E_COMMANDRETURN process();
   virtual bool HideGridRowColumn(DString& dstrTag){return(false);}

   void setUpdateFlag( bool bUpdated = true )
   {
      _bUpdated = bUpdated;
   }

   bool getUpdateFlag( )
   {
      return(_bUpdated);
   }
/*
   bool shouldValidate()
   {  // Check to see who is gaining focus and whether to skip validation or not
      // based on if part of same dialog and not an ignored control

      // May need to pass this to my parent if I am a child dialog ???
   }
   */

   static BFControlFactory* getControlFactory();
   static BFControlFactory* setControlFactory( BFControlFactory* pControlFactory );

   virtual bool filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag)
   {
      return( true );
   }

   void doSetDlgItemText( int nID, LPCTSTR lpszString, BFFieldId fieldId );
   static void DisplayFormat( DString &dstrDecimalValue, const BFFieldId& idField );
   static void DisplayUnFormat( DString &dstrDecimalValue, const BFFieldId& idField );

protected:
//******************************************************************************
//    Message handlers
//******************************************************************************
   // Generated message map functions
   //{{AFX_MSG(BaseDlg)
   virtual BOOL OnInitDialog();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonUp( UINT nFlags,  CPoint point  );
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSizing( UINT nSide,  LPRECT lpRect  );
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()

	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

   afx_msg BOOL OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult );
   void DefaultSize();
   /**
     * This method is invoked by the base architecture after OnInitDialog has
     * completed.  This should be implemented for time intensive setup so that
     * the screen can display quickly and then do this processing.
     */
   virtual void OnPostInitDialog();
   virtual BOOL PreTranslateMessage( MSG *pMsg );
   virtual LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM lParam );
   virtual void customResize(){};

   // Base implementation of parts of generic interface that aren't required
   /**
     * This method is optional, override if subclass needs to implement.  (Not
     * needed at all for GUI layer??)
     * @param rpGICaller - A reference pointer to the calling GenericInterface.
     * @returns true if successful
     */
   virtual SEVERITY cancel2( GenericInterface* rpGICaller )
   {
      return(NO_CONDITION);
   }
   //permission check stuff
   /**
   * call this method whenever you want to add an Add button for the permission check
   * you have to associate this button with the list control's ID, it will add items
   * @param nListCtrlID - the ID of the list control associated with the nID button
   * @param nID - the Add button's ID
   */
   void addBtnAddForPermissionCheck(UINT nID, int nListCtrlID = -1) ;
   /**
   * call this method whenever you want to add a Delete button for the permission check
   * you have to associate this button with the list control's ID, from which it will delete items
   * @param nListCtrlID - the ID of the list control associated with the nID button
   * @param nID - the Delete button's ID
   */
   void addBtnDeleteForPermissionCheck(UINT nID, int nListCtrlID = -1) ;
   /**
   * this method is called by addBtnAddForPermissionCheck and addBtnDeleteForPermissionCheck
   * call this method only if you want to add a list control for perm. check without adding Add and/or Delete buttons for it
   * also call this method if you want to add controls that were added with ControlGroupID = 0
   * @param nListCtrlID - the ID of the list control associated with the nID button
   */
   void addControlGroupIDForPermissionCheck(int nListCtrlID) ;
   /**
   * removes nID Button from permission check
   * @param nID - the Add button's ID
   */
   void removeBtnAddFromPermissionCheck(UINT nID) ;
   /**
   * removes nID Button from permission check
   * @param nID - the Delete button's ID
   */
   void removeBtnDeleteFromPermissionCheck(UINT nID) ;
   /**
   * removes nListCtrlID list control from permission check
   * removeBtnAddFromPermissionCheck and removeBtnDeleteFromPermissionCheck will NOT remove the associated list
   * control from permission check. To remove a list control from perm. check, call this method even
   * if you did not add it for perm. check calling addListCtrlForPermissionCheck.
   * @param nListCtrlID - the ID of the list control we want to remove from perm. check
   */
   void removeControlGroupIDFromPermissionCheck(int nListCtrlID) ;
   /**
    * Because the same Add or Delete button can be used for more list controls (not in the same time, hopefully)
    * the association between a button and a list control can be changed at any time.
    * This method removes the old association, adds the new one, adds the new list control for perm. check
    * (if not already there) and if bRemoveOldListCtrlGroupIDFromPermCheck removes the old list control from perm. check
    * 
    * @param nID    the button's ID
    * @param nListCtrlID
    *               the ID of the new list control we want to associat with the nID button
    * @param bRemoveOldControlGroupIDFromPermCheck
    */
   void changeBtnToListCtrlAssociation(UINT nID, int nListCtrlID = -1, bool bRemoveOldControlGroupIDFromPermCheck = false);
   /**
   *sets the user acces function code (in order to check permissions)
   *if buttons or list controls are added for permission check and this method is not called, CheckPermission()
   *will act as if the user does not have Modify, Add and Delete permissions
   */
   void SetUserAccesFunctionCode(I_CHAR * strUserAccesFunctionCode) { m_pUserAccesFunctionCode = strUserAccesFunctionCode;};
   /**
   *returns the user acces function code
   */
   I_CHAR* GetUserAccesFunctionCode() {return(m_pUserAccesFunctionCode);};
   /**
   * checks permissions for the current user and enables/disables only those Add or Delete buttons
   * which were added, in the derived class, to the permission check. It will enable/disable all children
   * controls for a list control that was added for permission check (either calling addListCtrlForPermissionCheck
   * or by addBtnAddForPermissionCheck or addBtnDeleteForPermissionCheck)
   * Rules for a list control children controls :
   * 1. if the control is not updeatable, CheckPermission() will do nothing (control stays readonly)
   * 2. if the current item is new and user doesn't have add permission, the control will be set as readonly
   * 3. if the current item is NOT new and user doesn't have modify permission, the control will be set as readonly
   * 4. for any other situation CheckPermission() will ENABLE the control
   * In OnPostInitDialog() in the derived class, call addBtnAddForPermissionCheck() and/or
   * addBtnDeleteForPermissionCheck() and/or addListCtrlForPermissionCheck()
   * Also call SetUserAccesFunctionCode().
   * This method is called in BaseDlg, immediately after OnPostInitDialog() and after doListItemChanged)
   * If there are bussines rules for enabling/disabling an Add or Delete button, overite doDisablePermCheckButton
   * If there are bussines rules for enabling/disabling other buttons (such as Reset), overite doDisableOtherButtons
   */
   virtual void CheckPermission();
   /**
   * implement here any bussiness rules related to the buttons that were added for permission check (add or delete buttons)
   * return true if it should be disabled and false if it should be enabled
   * DO NOT call EnableWindow() here
   * @param nID - the control's ID
   */
   virtual bool doDisablePermCheckButton(UINT nID){return(false);};
   /**
   * implement here any bussiness rules related to any buttons that were NOT added for permission check
   * example: GetDlgItem( IDC_BTN_RESET )->EnableWindow( FALSE );
   * Do not enable/disable here buttons that were added for permission check
   * this method is called just before CheckPermission returns
   */
   virtual void doDisableNonPermButtons(){};
   /**
   * if overwritten by derived class, return true if nID control should be disabled, otherwise return false
   * @param nID - the control's ID
   * @param bIsNew - current item is new
   */
   virtual bool doDisableControl(UINT nID, bool bIsNew){return(false);};
   /**
     * This method is optional - override if subclass needs to implement.
     * @param rpGICaller - A reference pointer to the calling GenericInterface.
     * @param rpData - A reference pointer to Data object for data.
     * @returns true if successful, if false check conditions
     */
   //end - permission check stuff
   virtual bool doGetData( GenericInterface* rpGICaller,
                           BFData* rpData ) const
   {
      return(false);
   }
   /**
     * This method is optional - override if subclass needs to implement.
     * The override should perform any initialization
     * required, including getting parameters from InterProcessData (they get
     * cleared after this call).
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit()
   {
      return(NO_CONDITION);
   }
   /**
     * Override is provided by this class.  This implementation should be
     * adequate.
     * Used to bring a modeless dialog (via parent process) to the top of the
     * window stack.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, check conditions if false
     */
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   /**
     * Use to add processing to the "process" method
     * This method is optional - override if subclass needs to implement.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess()
   {
      return(CMD_OK);
   }
   /**
     * This method is optional - override if subclass needs to implement.
     * @param rpGICaller - A reference pointer to the calling GenericInterface.
     * @param szMessage - A string literal of the message to send.
     * @returns true if successful
     */
   virtual bool doSend( GenericInterface* rpGICaller, const I_CHAR* szMessage )
   {
      return(false);
   }

   const DString &GetAccount() const        // Get current account
   {
      return(m_account);
   }
   const DString &GetFund() const           // Get current fund
   {
      return(m_fund);
   }
   int GetIDD() const
   {
      return(m_IDD);
   }
   CWnd *GetMyParent() const
   {
      return(m_rpParent);
   }
   CView *GetMainView() const                // Returns RoadView pointer
   {
      return(m_pDSTCView);
   }
   const DString &GetDialogName() const        // Get dialog name
   {
      return(m_dialogName);
   }
   void SetDialogName(DString Dialogname)      // Set dialog name
   {
      m_dialogName = Dialogname;
   }
   void LoadDialogSize (int &width, int &height);
   void SaveDialogSize ();
   void InitResizing ();
   AbstractProcess *getParentProcess();
   /**
     * This method is optional, override if subclass needs to implement.  (Not
     * needed at all for GUI layer??)
     * @param rpGICaller - A reference pointer to the calling GenericInterface.
     * @returns true if successful
     */
   virtual SEVERITY ok2( GenericInterface* rpGICaller )
   {
      return(NO_CONDITION);
   }

   /**
    * Set current account
    * 
    * @param acct Account to set
    */
   void SetAccount( const DString &acct );
   /**
    * Set current customer name
    * 
    * @param name Name to set
    */
   void SetCustomerName( const DString &name );
   /**
    * Set current fund
    * 
    * @param fund Fund to set
    */
   void SetFund( const DString &fund );

   /**
    * Set the internally defined parent window of this dialog.  Does not 
    * affect the actual Win32 window relationships
    * 
    * @param rpWnd  pointer to CWnd object of parent window
    */
   void SetMyParent( CWnd *rpWnd )
   {
      m_rpParent = rpWnd;
   }

//******************************************************************************
//   Methods for control support
//******************************************************************************

   friend class BaseControl;
   friend class DSTEdit;

   void FocusOnControl( UINT controlID )
   {
      ::SetFocus( GetDlgItem( controlID )->m_hWnd );
   }

   /**
   * This method is called by the framework for WM_PASTE
   */
   virtual void doPaste( UINT controlID ){}

   /**
     * This is a factory method used to create control instances associating
     * them with a Windows control, and with a container/field id in the parent
     * process.  This control is added to the _controls container.
     * Any error encountered will be thrown as an exception.
     * @param eType - Specifies the type of control to create.
     * @param controlID - Windows control ID to associate with.
     * @param idContainer - Container ID (in parent process) to associate with.
     * @param idField - Field ID (in parent process) to associate with.
     * @param flags - Flags affecting control creation - varies by control.
     * @param controlGroupID - group of controls to associate with.
     */
   BaseControl* AddControl( E_CONTROLTYPE eType,
                            UINT controlID,
                            const BFContainerId& idContainer,
                            const BFFieldId &idField,
                            UINT flags = 0,
                            UINT controlGroupID = 0 );
   /**
     * This is a helper method for cases where you do not have a container ID
     * and field ID at time of construction.  This control is added to the
     * _controls container.
     * Any error encountered will be thrown as an exception.
     * @param eType - Specifies the type of control to create.
     * @param controlID - Windows control ID to associate with.
     * @param flags - Flags affecting control creation - varies by control.
     * @param controlGroupID - group of controls to associate with.
     */
   BaseControl* AddControl( E_CONTROLTYPE eType,
                            UINT controlID,
                            UINT flags = 0,
                            UINT controlGroupID = 0 )
   {
      return( AddControl( eType, controlID, BF::NullContainerId, ifds::NullFieldId, flags, controlGroupID ) );
   }
   /**
     * This method is used to set a cross-edit that should be implemented on the
     * fly as focus moves from a control associated with the cross-edit to
     * somewhere not associated with the cross-edit.
     * @param idContainer - ID of container cross-edit is associated with
     * @param idCrossEdit - ID of cross-edit to implement.
     */
   void AddCrossEdit( const BFContainerId& idContainer, const BFFieldId &idCrossEdit );
   /**
     * This method checks to see if the control losing focus is a participant
     * in any cross-edit (set for immediate validaiton). If so, and the control
     * gaining focus is not in the same cross-edit, then the cross-edit will be
     * fired.
     * @param rpLoseFocusControl - control that is losing focus.
     * @returns SEVERITY noting any error/warning conditions
     */
   SEVERITY CheckCrossEdits( const BaseControl *rpLoseFocusControl );
   /**
     * Use this function to clear a control.
     * Exceptions will be thrown on failure
     * @param controlID - specific control to clear
     */
   void ClearControl(
                    UINT controlID
                    );
   /**
     * Use this function to clear all controls.  Controls set to manual load or
     * disabled will not be cleared.
     * Exceptions will be thrown on failure
     * @param idContainer - -1 = clear all, else clear for specified container
     */
   void ClearControls(
                     const BFContainerId& idContainer = BF::AllContainerIds
                     );
   /**
     * Use this function to connect/disconnect a control from use in the dialog.
     * This should only be used when working with individual controls within
     * a control group.  If all controls within a control group are to be
     * changed the same way, use ConnectControlsToData.
     * If disconnected, the control will be automatically disabled.  You are
     * responsible for setting the visible state.
     * Note that while a false setting will immediately take affect, for a
     * true setting, ConnectControlsToData must be called with a true value.
     * This will occur automatically for controls associated with lists if the
     * list is repopulated or has a selection change.
     * Exceptions will be thrown on failure
     * @param controlID - specific control to clear
     * @param bFlag - true = connect, false = disconnect
     */
   void ConnectControl(
                      UINT controlID,
                      bool bFlag
                      );
   /**
     * Use this function to connect all controls to associated container/field.
     * Typically derived classes will only call this to initially connect non-
     * list associated controls to their data.  Most other uses should be base
     * class driven.
     * Exceptions will be thrown on failure
     * @param controlGroupID - 0xFFFF = connect all, else connect for specified
     *   control group.
    * @param bFlag flag value to pass to ConnectToData.  Seems to have some effect upon the default hide/show state of the control(s)
     * @param bShowHideBasedOnConnection - true = use the connection state to
     *    show/hide, false = don't affect visibility
     */
   void ConnectControlsToData(
                             UINT controlGroupID = 0,   // Default to controls without parents
                             bool bFlag = true,
                             bool bShowHideBasedOnConnection = false
                             );
   /**
     * Use this function to connect a control to associated container/field.
     * Exceptions will be thrown on failure
     * @param controlID = control to connect.
    * @param bFlag flag value to pass to ConnectToData.  Seems to have some effect upon the default hide/show state of the control(s)
     * @param bShowHideBasedOnConnection - true = use the connection state to
     *    show/hide, false = don't affect visibility
     */
   void ConnectControlToData(
                            UINT controlID,
                            bool bFlag,
                            bool bShowHideBasedOnConnection = false
                            );
   /**
     * This method can be overridden to respond to data changes in a control.
     * @param controlID - ID of control that is changed.
     * @param strValue - unformatted value of change, this is not meaningful
     *   for a control associated with multiple fields at the same time.
     */
   virtual void ControlUpdated(
                              UINT controlID,
                              const DString &strValue
                              )
   {}
   /**
     * This method displays/hides tooltips as necessary.
     * @param killFocusControlID - ID of control that is losing focus.
     */
   void DisplayErrorInfo(
                        UINT killFocusControlID = 0
                        );
   /**
     * This method is used to set the enabled state of a control.
     * @param controlID - Control to set state for.
     * @param bFlag - true = set enabled
     */
   void EnableControl(
                     UINT controlID,
                     bool bFlag
                     );
   /**
     * This method is used to set focus to the first focusable control in group.
     * This ordering is established by the order the controls are added.  A
     * control group ID of 0 will find the first control across all groups that
     * is focusable.  This method may be overridden, if the base functionality
     * is not suitable.
     * @param controlGroupID - Group to search for first focusable control.
     */
   virtual void FocusOnFirstControl(
                                   UINT controlGroupID = 0
                                   );
   /**
     * This method is used to get the specified control.
     * @param controlID - Control to get pointer for.
     * @returns BaseControl pointer to control
     */
   BaseControl *GetControl(
                          UINT controlID
                          ) const;
   /**
     * This method is used to get current data associated with control.
     * @param controlID - Control to get data for.
     * @param strValueOut - String to return data for the control.
     * @param bFormatted - true = return in display format, false = return in
     * host format
     * @param index - index of field, if multiple fields for control
     * @returns DString reference of value obtained
     */
   const DString &GetControlText(
                                UINT controlID,
                                DString &strValueOut,
                                bool bFormatted = false,
                                int index = 0
                                ) const;
   /**
     * This method should be overridden if there are any controls which the
     * derived dialog supports outside of the base architecture.  This would
     * typically be if the derived dialog is supporting data not stored in the
     * parent process.
     * The default implementation is to return false - no override.
     * @param controlID - Control to get data for.
     * @param strValueOut - String to return data for the control.
     * @param bFormatted - true = return in display format, false = return in
     * host format
     * @param index - index of field, if multiple fields for control
     * @returns true if override provided for the specified control, false
     * otherwise
     */
   virtual bool GetDataForControl(
                                 UINT controlID,
                                 DString &strValueOut,
                                 bool bFormatted,
                                 int index=0
                                 ) const;
   /**
     * Override this function to provide specialized control initialization.
     * @param controlID - Windows control ID being initialized.
     */
   virtual void InitControl(
                           UINT controlID
                           );
   /**
     * Use this function to load control with data from associated
     * container/field.
     * Exceptions will be thrown on failure
     * @param controlID - Windows control ID to associate with.
     */
   void LoadControl(
                   UINT controlID
                   );
   /**
     * Use this function to load all controls with data from associated
     * container/field.  Controls set to manual load or disabled will not be
     * loaded.
     * Exceptions will be thrown on failure
     * @param idContainer - -1 = load all, else load for specified container
     */
   void LoadControls(
                    const BFContainerId& idContainer
                    );
   /**
     * Use this function to load all controls with data from associated
     * group.  This is often used to load all controls associated with a list
     * where the controlGroupID is the list control ID.
     * Exceptions will be thrown on failure
     * @param controlGroupID - group of controls to load
     */
   void LoadControls(
                    UINT controlGroupID = 0
                    );
   /**
     * This method runs through the control array forcing a reload of the error
     * state for all controls.  Finally focus will be set on "first" control
     * with an error.
     */
   void LoadControlErrorState();
   /**
     * This method runs through the control array making sure that all controls
     * have been stored.  Error indicators for all controls will be set if
     * errors > warning were encountered.
     * @returns true if no errors > WARNING encountered
     */
   bool ProcessControls();
   /**
     * Use this function to re-associate a control created using AddControl
      * to another container/field.
     * @param controlID - Windows control ID to associate with.
     * @param idContainer - Container ID (in parent process) to associate with.
     * @param idField - Field ID (in parent process) to associate with.
     * @param flags - Flags affecting control creation - varies by control.
    * @param controlGroupID 
     */
   void ReInitControl(
                     UINT controlID,
                     const BFContainerId& idContainer,
                     const BFFieldId &idField,
                     UINT flags = -1,  // flags remain unchaged
                     int controlGroupID = -1
                     );
   /**
     * This method is used to set data associated with control and control.
     * @param controlID - Control to set data for.
     * @param strValue - String to set.
     * @param bFormatted - true = string in display format, false = string in
     * host format
     * @param index - index of field, if multiple fields for control
     * @returns true if successful
     */
   bool SetControlText(
                      UINT controlID,
                      const DString &strValue,
                      bool bFormatted = false,
                      int index = 0
                      ) const;
   /**
     * This method should be overridden if there are any controls which the
     * derived dialog supports outside of the base architecture.  This would
     * typicaly be if the derived dialog is supporting data not stored in the
     * parent process.  The data provided is in display format.
     * The default implementation is to return false - no override.
     * @param controlID - Control to get data for.
     * @param strValue - String with data to validate/save.
     * @param sevRtn - SEVERITY returned if override was true.
     * @param bFormatted - true = data in display format, false = data in
     * host format
    * @param index ???
     * @returns true if override provided for the specified control, false
     * otherwise
     */
   virtual bool SetDataFromControl(
                                  UINT controlID,
                                  const DString &strValue,
                                  bool bFormatted,
                                  SEVERITY &sevRtn,
                                  int index=0
                                  );
   /**
     * This method is used to set the visible state of a control.
     * @param controlID - Control to set state for.
     * @param bFlag - true = set visible
     */
   void ShowControl(
                   UINT controlID,
                   bool bFlag
                   );
   /**
     * This method is used to establish cross-edits that should be implemented
     * for on the fly validation.
     * Any error encountered will be thrown as an exception.
     * @param idContainer - Container which implements the cross-edit.
     * @param crossEditID - Cross-edit ID.
     */
   void UseCrossEdit(
                    const BFContainerId& idContainer,
                    long crossEditID
                    );
   bool IsSelectedCtrlUpdateable();
   /**
   * This method is similar to ControlUpdated
   *
   */
   virtual void GridControlUpdated( UINT ctrlId,
                                    const DString &rowKey,
                                    const DString &colKey,
                                    const DString &strNewValue,
                                    bool bFormatted,
                                    SEVERITY nSeverity)
   {}  

//******************************************************************************
//   Methods for control support
//******************************************************************************
//   #pragma BF_REMINDER( Must remove friend class declaration for DSTListCtrl and IFDSListCtrl in BaseDlg )
   friend class DSTListCtrl;       // Temporary
   friend class IFDSListCtrl;      

   DSTListCtrl* AddListControl( const I_CHAR *dialogName,
                                UINT listControlID,
                                const I_CHAR *listName,
                                const BFFieldId &idSubstitute,
                                const BFContainerId& idContainer,
                                UINT parentControlID = 0,
                                bool bShowSelAlways = true,
                                UINT flags = 0 );

   DSTListCtrl* AddListControl( const I_CHAR *dialogName,
                                UINT listControlID,
                                UINT parentControlID = 0,
                                bool bShowSelAlways = true,
                                UINT flags = 0 )
   {
      return( AddListControl( dialogName, listControlID, NULL_STRING, ifds::NullFieldId, BF::NullContainerId, parentControlID, bShowSelAlways, flags ) ); 
   }

   IFDSListCtrl* AddIFDSListControl( IFDSListCtrl* pCtrl,
                                     const I_CHAR* pszListName,
                                     const BFContainerId& idContainer,
                                     const BFFieldId& idColumnField );


   void AddAttributeListControl( const I_CHAR *dialogName,
                                 UINT listControlID,
                                 const I_CHAR *listName,
                                 const BFFieldId &idSubstituteID,
                                 const BFFieldId &idLeftSubstituteID,
                                 const BFContainerId& idContainer,
                                 UINT parentControlID = 0,
                                 bool bShowSelAlways = true,
                                 UINT flags = 0 );
   /**
     * This method adds a row to the list (creating new CBO item) and selects
     * the row.  Error will be displayed as appropriate.
     * @param listControlID - Control ID of list to add to
     * @returns - true = successful add
     */
   bool AddToListControl( UINT listControlID );

   bool AddToGridControl( UINT controlID );

   bool DeleteFromGridControl( UINT controlID );

   /**
     * Use this function to connect/disconect the list with associated
     * container.  The list defaults to connected.
     * Exceptions will be thrown on failure
     * @param listID - list to work with.
     * @param bFlag - true = connect, false = disconnect
     * @param bShowHideBasedOnConnection - true = use the connection state to
     *    show/hide, false = don't affect visibility
     */
   void ConnectListToData(
                         UINT listID,
                         bool bFlag,
                         bool bShowHideBasedOnConnection = false
                         );
   /**
     * This method deletes the currently selected row from the list displaying
     * any errors as appropriate.
     * @param listControlID - Control ID of list to add to
     * @returns - true = delete occurred
     */
   bool DeleteFromListControl(
                             UINT listControlID
                             );
   /**
     * This method may be overridden to provide dialog specific handling
     * when list selection changes.  Note that the item will already be
     * the current item in the list (both list control and list container) and
     * the associated controls will be loaded.  This call does occur prior to
     * any loading of sub-lists.  If you need to affect the loading of controls
     * (connect/disconnect associated controls) for this list use
     * DoPreListItemChanged instead.
     * Avoid doing list control operations during this method.
     * @param listControlID - Control ID of list changing selection
     * @param strKey - reference to string key for item.
    * @param bIsNewItem 
    * @param bIsDummyItem
     */
   virtual void DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey,
                                 bool bIsNewItem ,
                                 bool bIsDummyItem
                                 )
   {
      return;
   }
   /**
     * This method may be overridden to provide dialog specific handling
     * when list selection changes.  Note that the item will already be
     * the current item in the list (both list control and list container) but
     * no controls have been loaded yet.  This would be the method to use if
     * controls connect/disconnect on a per row basis.
     * Avoid doing list control operations during this method.
     * @param listControlID - Control ID of list changing selection
     * @param strKey - reference to string key for item.
    * @param bIsNewItem
    * @param bIsDummyItem
     */
   virtual void DoPreListItemChanged(
                                    UINT listControlID,
                                    const DString &strKey,
                                    bool bIsNewItem,
                                    bool bIsDummyItem
                                    )
   {
      return;
   }
   /**
     * This method is used to set the enabled state of a control.
     * @param controlID - Control to set state for.
     * @param bFlag - true = set enabled
     */
   void EnableList(
                  UINT controlID,
                  bool bFlag
                  );
   BaseControl *GetLastControlWithFocus()
   {
      return(m_rpLastControlWithFocus);
   }
   /**
     * This method gets the requested list object.
     * Any error encountered will be thrown as an exception.
     * @param listControlID - Control ID of list to add to
     * @returns - reference pointer to list object
     */
   DSTListCtrl *GetList( UINT listControlID ) const;

   /**
     * This method is invoked by a DSTListCtrl when the item selected has
     * changed.  Derived dialogs should not override this method - override
     * DoListItemChanged instead.
     * @param listControlID - Control ID of list changing selection
     * @param strKey - reference to string key for item.
    * @param bIsNewItem
    * @param bIsDummyItem
     */
   void ListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem , bool bIsDummyItem );
   /**
     * This method loads associated data rows for any child lists.
     * @param parentListControlID - Control ID of parent
     */
   void LoadChildListControls( UINT parentListControlID );
   /**
     * This method loads associated data rows for the specified list.
     * @param listControlID - Control ID of list to load
     * @param rpStrKey - Key to set as selection, NULL = first row
     */
   void LoadListControl( UINT listControlID, const DString *rpStrKey = NULL );
   /**
     * This method forces a repaint of the currently selected row.  This can
     * be used to refresh data display for current selection.
     * @param listControlID - Control ID of list to load
     */
   void RefreshListItem( UINT listControlID );
   /**
     * This method associates a list with a substitution ID for the column
     * definitions, a idContainer for the data, and a name for the list.
     * This can be used to associate the same list with different list
     * containers at different times.
     * Any error encountered will be thrown as an exception.
     * @param listControlID - Control ID of list to add to
     * @param idSubstitute - ID of substitute to use for column definition
     * @param idContainer - ID of CBO list container to associate with for data
     * @param listName - String representing name of list view, used for storing
     *   listview settings in registry for later use.
     */
   void ReInitListControl( UINT listControlID,
                           const BFFieldId &idSubstitute,
                           const BFContainerId& idContainer,
                           const I_CHAR *listName );
   /**
     * This method resets the associated list container, removing all changes.
     * Any error encountered will be thrown as an exception.
     * @param listControlID - Control ID of list to add to
     */
   void ResetList( UINT listControlID );
   /**
     * This method resets the associated CBO of the current item in the list,
     * removing all changes.
     * Any error encountered will be thrown as an exception.
     * @param listControlID - Control ID of list to add to
     */
   void ResetListItem( UINT listControlID );
   void SetLastControlWithFocus( BaseControl *rpControl )
   {
      m_rpLastControlWithFocus = rpControl;
   }
   /**
     * This method is used to set the visible state of a control.
     * @param listID - Control to set state for.
     * @param bFlag - true = set visible
     */
   void ShowList( UINT listID, bool bFlag );
   /**
     * This method, if overwritten, should provide a BFProperties for a GuiField control.
     * @param controlID - Control for which we need the properties
     * @param idField - one of the fields associated with this control
     * returns a const pointer to a BFProperties, or NULL
     */
   const BFProperties* getGuiFieldProperties(UINT controlID, const BFFieldId &idField){return(NULL);};
   /**
   *This method re-register the observers. We need to re-register observers after a reset,
   *because reset deletes the field info
   * @param listControlID - the list control for which we need to reregister the observers
   *(it can be zero if we want to reregister observers for the controls not belonging to any list control)
   */
   void ReregisterObservers( UINT listControlID = 0);
   /**
      * This method runs through the list control array making sure that all list
     * controls will set the current list item in the process to the one selected
     * (this is necessary for the timer list controls, because user can select an item
     * and then hit 'OK' before the OnTimer is fired)
      */
   void ProcessListControls();
//******************************************************************************
//   Methods for grid support
//******************************************************************************
   friend class DSTGridWnd;
   DSTGridWnd* AddGrid( const I_CHAR* dialogName,
                        UINT controlID,
                        const I_CHAR* gridName,
                        const BFContainerId& idContainer = BF::NullContainerId,
                        UINT controlGroupID =  0,
                        const BFFieldId &idTopSubstitution = ifds::NullFieldId,
                        const BFFieldId &idLeftSubstitution = ifds::NullFieldId,
                        int gridType = DSTGridWnd::GRID_TYPE::ATTRIBUTE,
                        UINT flags = CTRLFLAG_DEFAULT);

   void ReInitGrid( const I_CHAR* dialogName,
                    UINT controlID,
                    const I_CHAR* gridName,
                    const BFContainerId& idContainer = BF::NullContainerId,
                    UINT controlGroupID = 0,
                    const BFFieldId &idTopSubstitution = ifds::NullFieldId,
                    const BFFieldId &idLeftSubstitution = ifds::NullFieldId,
                    int gridType = DSTGridWnd::GRID_TYPE::ATTRIBUTE,
                    UINT flags = CTRLFLAG_DEFAULT);

   /**
     * This method gets the requested grid object.
     * Any error encountered will be thrown as an exception.
     * @param gridControlID - Control ID of grid to add to
     * @returns - reference pointer to list object
     */
   DSTGridWnd *GetGrid( UINT gridControlID ) const;

   void LoadGrid( UINT controlID,
                  const BFFieldId &idTopSubstitution  = ifds::NullFieldId,
                  const BFFieldId &idLeftSubstitution = ifds::NullFieldId );

   void ResetGridItem( UINT gridControlID );

   DSTGridWnd *GetGrid ( UINT controlID );

//******************************************************************************
//   Methods for tab control support                                          //
//******************************************************************************
//  To add a tab control to the dialog call AddTabControl which will return the
//  DSTTabCtrl* to it. On the DSTTabCtrl* call AddTab to add pages, registerControl,
//  registerListControl, registerGridWnd to register controls with a particular
//  page. 
//  Call LoadTabControl in order for the registered controls to be displayed correctly.
//  DSTTabCtrl will show/hide the registered controls when clicking on tabs. It does
//  NOT connect/disconnect these controls to/from data. You can disconnect/connect
//  these controls overwritting isDisconnectRequired and isConnectRequired. However, it
//  is always better to use multiple controls, so connect/disconnect is not required.
//  If reInit is necessary for a registered control, overwrite reInitControl.
//  Call positionTabToControl for a better alignment of the tab control to another control
//  When clicking OK button, each tab will display an error icon, depending on the
//  max. severity of the registered controls for a given page
//  In order to refresh the warning/error icons call GetTabCtrl(tabID)->RefreshAllIcons() in 
//  methods like OnBtnReset or whenever is necessary 
//******************************************************************************
   friend class DSTTabCtrl;     

   DSTTabCtrl *AddTabControl( const I_CHAR *dialogName,
                              UINT tabControlID,
                              const I_CHAR *tabName,
                              UINT parentControlID = 0, /*not used for now */
                              UINT flags = 0 /*not used for now  */ );

   DSTTabCtrl *GetTabCtrl( UINT tabControlID );
   /**
     * @param tabControlID - ID of the tab control to be loaded
     * @param bFlag - if true the tab control is shown, else it will be hidden
     */
   void ShowTabCtrl( UINT tabControlID, bool bFlag );
   /**
     * Calling this method will : refresh the error signs on all the pages,
     * hide the registered controls with all the other pages, show the registered 
     * controls for the specified page name, select the specified page (if not
     * already selected)     
     * @param tabControlID - ID of the tab control to be loaded
     * @param pageName - Specifies the page name to be selected (if NULL_STRING, 
     * selects the first page)
     */ 
   void LoadTabControl( UINT tabControlID, const DString &pageName = NULL_STRING );
   /**
     * This method is called just before a selection change is going to happen
      * To allow the selection to happen, return true, else return false. It is the derived
     * class who has to notify the user why the selection change is not allowed
     * @param tabControlID - ID of the tab control 
      * @param strPageName - Specifies the page name to be un-selected 
      */ 
   virtual bool canTabSelChange( UINT tabControlID, const DString& strPageName ){ return(true);}
   /**
     * This method is called after the selection changed
     * @param tabControlID - ID of the tab control 
      * @param strPageName - Specifies the page name which has been selected
      */ 
   virtual void tabSelectionChanged(UINT tabControlID, const DString& strPageName){}
   /**
     * call this method to better align a tab control to another control
     * @param tabControlID - ID of the tab control 
      * @param nOtherControlID - ID of the control used to position the tab control
     * @param bLeft - the left side of the tab control will be aligned to the left
     * side of the other control (unless bRight is true, no resizing is performed)
      * @param bBottom - the bottom of the tab control will be aligned to the top
     * of the other control (the tab control will be also resized so the original
     * hight will not be changed)
      * @param bRight - the right side of the tab control will be aligned to the right
     * side of the other control (unless bLeft is true, no resizing is performed)
      */ 
   void positionTabToControl(UINT tabControlID, UINT nOtherControlID, bool bLeft=true, 
                             bool bBottom = true, bool bRight=true );
   /**
     * will refresh all the icons (error signs); it is called whenever OK button is pressed
      */ 
   void ProcessTabControls();
   /**
     * This method is called just before a selection change is going to happen
     * if the selection is allowed
     * @param tabControlID - ID of the tab control 
      * @param strPageName - Specifies the page name to be un-selected 
     * @param controlID - ID of the registered control
      * @return - true to disconnect controlID from data, else false
      */ 
   virtual bool isDisconnectRequired(UINT tabControlID, const DString& strPageName, UINT controlID)
   {return(false);};
   /**
     * This method is called after the selection changed
     * if necessary, connect here any controls to data (controls which were 
     * disconnected by isDisconnectRequired
     * returning false it does NOT mean that the connect will be disconnected;
     * it actually means that ConnectControlToData is not called for the controlID
     * @param tabControlID - ID of the tab control
      * @param strPageName - Specifies the page name to be selected 
      * @param controlID - ID of the registered control
      * @return - true to connect controlID to data, else false
      */ 
   virtual bool isConnectRequired(UINT tabControlID, const DString& strPageName, UINT controlID)
   {return(false);};
   /**
     * This method is called after the selection changed if isConnectRequired returned true
     * If necessary, reInit here any registered controls
     * @param tabControlID - ID of the tab control
      * @param strPageName - Specifies the page name to be selected 
      * @param controlID - ID of the registered control
      * @return - true to connect controlID to data, else false
      */ 
   virtual void reInitControl(UINT tabControlID, const DString& strPageName, UINT controlID){};

//******************************************************************************

   void SetCancelInProgress()
   {
      m_bCancelInProgress = true;
   }

   //******************************************************************************
   /**
     * This method formats a piece of text to have iMaxCharNum maximum characters per line and 
	 * iMaxNumLine maximum number of lines
     * @param strText - the paragraph to be formatted
     * @param iOffset - after formatting, the total length of the new text may be different
	 * a positive number means that the new text is longer by iOffset characters, while 
	 * a negative number means that it is shorter;
     * @param iMaxCharNum - the maximum number of characters per line
     * @param iMaxNumLine - the maximum number of lines
     */ 
virtual void formatParagraph( CString &strText, int& iOffset, int iMaxCharNum, int iMaxNumLine );


private:
   static BFControlFactory* s_pControlFactory_;


   typedef std::map< UINT, DSTGridWnd * > GRIDS;
#if _MSC_VER >= 1300
   typedef GRIDS::const_iterator GRID_CONST_ITER;
#else
   typedef GRIDS::iterator GRID_CONST_ITER;
#endif
   typedef GRIDS::iterator GRID_ITER;
   GRIDS m_Grids;

   //keeps a map with all list controls added for permission check
   //the key is the list control's ID, the value is a boolean that indicates if the current item in list is new
   typedef std::map< int, bool> LIST_CTRL_TO_BOOL;
   LIST_CTRL_TO_BOOL m_mapListCtrlNewItem;
   LIST_CTRL_TO_BOOL::iterator listCtrlIter;

   //keeps a map with all buttons which were associated with a list control
   //the key is the button's ID, the value is the associated list control ID (or -1 if no association)
   typedef std::map< UINT, int> BTN_TO_LIST_CTRL;
   BTN_TO_LIST_CTRL m_mapBtnToListCtrl;
   BTN_TO_LIST_CTRL::iterator btnToListCtrlIter;


   typedef std::map< UINT, BaseControl *, std::less<UINT> > CONTROLS;
#if _MSC_VER >= 1300
   typedef std::map< UINT, BaseControl *, std::less<UINT> >::const_iterator CONTROL_CONST_ITER;
#else
   typedef std::map< UINT, BaseControl *, std::less<UINT> >::iterator CONTROL_CONST_ITER;
#endif
   typedef std::map< UINT, BaseControl *, std::less<UINT> >::iterator CONTROL_ITER;

   typedef std::vector< BFFieldId > CROSSEDITVECTOR;
   typedef std::map< BFFieldId, CROSSEDITVECTOR *, std::less<BFFieldId> > CROSSEDITS;
#if _MSC_VER >= 1300
   typedef std::map< BFFieldId, CROSSEDITVECTOR *, std::less<BFFieldId> >::const_iterator CROSSEDITS_CONST_ITER;
#else
   typedef std::map< BFFieldId, CROSSEDITVECTOR *, std::less<BFFieldId> >::iterator CROSSEDITS_CONST_ITER;
#endif
   typedef std::map< BFFieldId, CROSSEDITVECTOR *, std::less<BFFieldId> >::iterator CROSSEDITS_ITER;

   DString m_account;                    // current account for dialog
   DString m_dialogName;
   // Flag set by BaseMainDlg & used to prevent BaseControl operations when
   //  cancel has been initiated.
   bool m_bCancelInProgress;
   CONTROLS m_controls;
   CROSSEDITS m_crossEdits;
   std::vector< BaseControl * > m_orderedControls;
   DString m_customerName;
   DString m_fund;                       // current fund for dialog
   int m_IDD;
   std::vector< DSTListCtrl * > m_lists;
   BaseControl *m_rpLastControlWithFocus;
   CWnd *m_rpParent;
   CView *m_pDSTCView;                    // pointer to DSTCView
   std::vector< int > m_AddButtons;//to store registered Add buttons for permission check
   std::vector< int > m_DelButtons;//to store registered Delete buttons for permission check
   std::vector< DSTTabCtrl * > m_tabs;

   I_CHAR * m_pUserAccesFunctionCode;

   bool _bUpdated, _bSizing, _bScroll;
   CRect wndRect;
   CScrollHelper* m_scrollHelper;
   DlgResizeHelper * m_resizeHelper;
   CFont * m_pFont;

   /**
     * This should never be implemented for a dialog, because they don't have
     * children.
     * modelessChildComplete is used by the GenericInterfaceContainer to tell
     * the parent that the modeless child has been destroyed.
     * @param cmd - A reference to a command representing the object that has
     * been destroyed.
     * @returns true if this modeless object should end as well, false if not
     * done yet.  When returning true, the calling modelessChildComplete method
     * will call GenericInterfaceContainer::modelessDestroySelf to delete and
     * remove this object from the container
     */
   virtual bool doModelessChildComplete(
                                       const Command & /*cmd*/                 // Command of child completed
                                       )
   {
      ASSERT( 0 );
      return(false);
   }
   /**
     * Implementation to support the init method.
     * Subclasses should implement doInit to perform any initialization
     * required, including getting parameters from InterProcessData (they get
     * cleared after this call).
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY init2();
   LRESULT DoPostInitDialog(
                           WPARAM wParam,
                           LPARAM lParam
                           );

   void CheckCtrlForReadOnly(BaseControl *rpCtrl, int nControlGroupID, bool bIsNew,bool bMod, bool bAdd, bool bIsGrid = false);
   bool isValidListCtrl(UINT controlID);
   //handleLastListCtrl();

//   friend class DlgResizeHelper;
   void GetWindowSizeFromRegistry(int &width_, int &height_);
public:
   bool IsBrowserBasedDialog() const;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/basedlg.h-arc  $
 * 
 *    Rev 1.75   Jul 24 2009 00:48:10   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
 * 
 *    Rev 1.74   24 Oct 2008 10:23:04   kovacsro
 * 1399970 - GL-1254 Desktop Screen (Remarks - odd character )
 * 
 *    Rev 1.73   16 May 2008 13:30:22   kovacsro
 * IN#1223298 - calling doPaste for WM_PASTE messages
 * 
 *    Rev 1.72   Jun 08 2006 14:31:36   fengyong
 * Add function setdialogname
 * 
 *    Rev 1.71   Oct 06 2005 16:25:40   fengyong
 * #incident 403519 - temp check in limt the resize height max to default height.
 * 
 *    Rev 1.70   Sep 30 2005 16:49:34   fengyong
 * #403519 - default sizing fix
 * 
 *    Rev 1.69   Sep 28 2005 10:48:52   fengyong
 * #Incident 403519 - Add default size feature
 * 
 *    Rev 1.68   Sep 27 2005 10:32:34   fengyong
 * Incident #40519 - resize grid control together with the screen resizing
 * 
 *    Rev 1.67   Sep 15 2005 12:58:08   popescu
 * Incident # 403519 - saved/restored the size of the dialog in the registry
 * 
 *    Rev 1.66   Sep 07 2005 11:11:12   fengyong
 * Add scroll and resize feature to dialogs
 * 
 *    Rev 1.65   Jun 24 2005 17:02:24   Fengyong
 * PET1250 FN02 - EuroPean numeric enhancement
 * 
 *    Rev 1.64   Nov 14 2004 15:02:08   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.63   Oct 01 2004 18:15:08   popescu
 * PET 1117/06, SSB Germany - Added 'flags' parameter to the grid control - not very useful for the moment
 * 
 *    Rev 1.62   May 24 2003 15:05:18   PURDYECH
 * Changed the Add*Control functions to return a pointer to what they just added.
 * Added AddIFDSListControl to add an IFDSAdaptedListCtrl<>
 * 
 *    Rev 1.61   Jan 14 2003 11:05:18   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.60   Jan 06 2003 16:46:00   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.59   Nov 27 2002 15:05:22   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.58   Nov 20 2002 11:36:06   PURDYECH
 * Added virtual filterListColumn method.
 * 
 *    Rev 1.57   Nov 13 2002 11:43:12   PURDYECH
 * Fixed up C4275 warning error.
 * 
 *    Rev 1.56   Oct 31 2002 13:33:48   KOVACSRO
 * very small change for LoadTabControl.
 * 
 *    Rev 1.55   Oct 21 2002 13:48:12   PURDYECH
 * Added class members to manage the Control Factory
 * 
 *    Rev 1.54   Oct 09 2002 17:42:36   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.53   Oct 07 2002 14:05:36   KOVACSRO
 * Added tab control support.
 * 
 *    Rev 1.52   Sep 19 2002 10:42:30   YINGBAOL
 * add parapeter to AddGrid and ReinitGrid
 * 
 *    Rev 1.51   Sep 12 2002 15:27:18   YINGBAOL
 * add HideGridRowColumn(...) method
 * 
 *    Rev 1.50   Sep 05 2002 14:00:58   HSUCHIN
 * added support for add/delete from Stingray Grid
 * 
 *    Rev 1.49   Aug 29 2002 20:09:22   SMITHDAV
 * CellProperties fixes
 * 
 *    Rev 1.48   Aug 29 2002 18:14:06   SMITHDAV
 * Additional FieldId fixes.
 * 
 *    Rev 1.47   Aug 29 2002 12:57:04   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.46   Aug 08 2002 13:34:12   KOVACSRO
 * Added GridControlUpdated
 * 
 *    Rev 1.45   Aug 08 2002 11:11:40   KOVACSRO
 * Added bFormatted parameter to GetCellValue
 * 
 *    Rev 1.44   Jul 16 2002 09:52:16   KOVACSRO
 * added ProcessListControls
 * 
 *    Rev 1.43   Jun 18 2002 12:53:02   KOVACSRO
 * Added formatted parameter to SetCellValue().
 * 
 *    Rev 1.42   Jun 05 2002 16:47:20   YINGZ
 * support reset
 * 
 *    Rev 1.41   May 30 2002 10:08:52   YINGZ
 * add grid
 * 
 *    Rev 1.40   May 23 2002 09:56:10   PURDYECH
 * BFData Implementation Verification Corrections
 * 
 *    Rev 1.39   22 Apr 2002 15:37:40   KOVACSRO
 * Added isValidListCtrl() method.
 * 
 *    Rev 1.38   27 Mar 2002 20:00:16   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.37   Mar 20 2002 17:03:48   VADEANUM
 * Added OnGridSetCellValueSetKey().
 *
 *    Rev 1.36   19 Mar 2002 13:36:00   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 *
 *    Rev 1.35   Mar 01 2002 13:14:02   YINGBAOL
 * fix reinitcontrol
 *
 *    Rev 1.34   27 Feb 2002 16:06:00   HSUCHIN
 * Added a parameter to ReInitControl to associate a group to the reinited control
 *
 *    Rev 1.33   23 Nov 2001 14:19:04   KOVACSRO
 * changed doDisablePermCheckButtons() into doDisablePermCheckButton(nID) and added  doDisableNonPermButtons()
 *
 *    Rev 1.32   08 Nov 2001 13:50:44   KOVACSRO
 * Added ReregisterObservers().
 *
 *    Rev 1.31   Sep 06 2001 14:14:44   ZHANGCEL
 * Added second parameter in ListViewControlFilter()
 *
 *    Rev 1.30   15 Aug 2001 09:45:18   YINGZ
 * support attribute type list
 *
 *    Rev 1.29   04 Jul 2001 16:46:32   YINGZ
 * implement cancel to give user warning when there are updates
 *
 *    Rev 1.28   06 Jun 2001 17:10:44   KOVACSRO
 * Added getGuiFieldProperties() protected method.
 *
 *    Rev 1.27   17 May 2001 09:43:40   YINGZ
 * support reinitgrid
 *
 *    Rev 1.26   15 May 2001 15:36:50   YINGZ
 * data group id clean up
 *
 *    Rev 1.25   08 May 2001 14:27:26   YINGZ
 * data group fix
 *
 *    Rev 1.24   27 Apr 2001 13:50:02   BUZILAMI
 * notifying the dialog on grid value changes
 *
 *    Rev 1.23   26 Apr 2001 16:48:36   KOVACSRO
 * minor change.
 *
 *    Rev 1.22   19 Apr 2001 17:09:46   KOVACSRO
 * perm. check.
 *
 *    Rev 1.21   05 Apr 2001 15:59:14   KOVACSRO
 * Added IsSelectedCtrlUpdateable.
 *
 *    Rev 1.20   05 Apr 2001 15:03:04   KOVACSRO
 * Added OnKeyDown for perm. check purposes.
 *
 *    Rev 1.19   30 Mar 2001 17:38:38   KOVACSRO
 * Added a private method.
 *
 *    Rev 1.18   29 Mar 2001 13:22:10   KOVACSRO
 * permission check stuff.
 *
 *    Rev 1.17   27 Mar 2001 16:35:16   KOVACSRO
 * permission check cleanup.
 *
 *    Rev 1.16   01 Mar 2001 16:28:18   KOVACSRO
 * Modified permission check stuff.
 *
 *    Rev 1.15   Jan 17 2001 09:42:42   KOVACSRO
 * Added some new stuff for permission check.
 *
 *    Rev 1.14   Dec 13 2000 15:08:20   KOVACSRO
 * 1. Modified DoListItemChanged, DoPreListItemChanged
 * 2.Added Dummy Item logic for perm. check.
 *
 *    Rev 1.13   Dec 05 2000 17:07:44   KOVACSRO
 * Added new item logic for permission check.
 *
 *    Rev 1.12   Dec 01 2000 11:48:58   KOVACSRO
 * Added permission check logic.
 *
 *    Rev 1.11   Jun 23 2000 13:05:20   DT24433
 * changes to support setData
 *
 *    Rev 1.10   May 29 2000 09:18:28   BUZILA
 * added GetNextDlgTabItem method
 *
 *    Rev 1.9   May 16 2000 14:00:40   HSUCHIN
 * removed DSTFundClassEdit control
 *
 *    Rev 1.8   May 08 2000 11:46:38   HSUCHIN
 * added Fund Edit control to launch Fund Search screen
 *
 *    Rev 1.7   Apr 04 2000 12:58:44   BUZILA
 * passing GridName and Dialog name to DSTGridWnd in order to be able to save/restore layout changes
 *
 *    Rev 1.6   Mar 22 2000 12:56:32   BUZILA
 * Grid changes
 *
 *    Rev 1.5   Mar 17 2000 13:54:16   YINGZ
 * add filter function for grid
 *
 *    Rev 1.4   Mar 14 2000 10:03:04   YINGZ
 * move functions from protect to public
 *
 *    Rev 1.3   Mar 14 2000 09:53:06   YINGZ
 * change nReadonly to nCellState in GetCellProperties
 *
 *    Rev 1.2   Mar 08 2000 16:22:26   YINGZ
 * add add grid support
 *
 *    Rev 1.1   Feb 15 2000 18:58:50   MCNABBGL
 * changed comment format
 *
 *    Rev 1.0   Feb 15 2000 11:00:56   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.37   Jan 27 2000 10:24:46   DT24433
 * changed list container from map to vector to maintain insert order
 *
 *    Rev 1.36   Jan 26 2000 14:11:32   DT24433
 * changed AddToListControl/DeleteFromListControl to return bool and display errors
 *
 *    Rev 1.35   Jan 13 2000 17:09:30   DT24433
 * error handling changes
 *
 *    Rev 1.34   Jan 11 2000 17:24:56   DT24433
 * added support for CancelInProgress
 *
 *    Rev 1.33   Jan 05 2000 17:55:00   DT24433
 * added cross-edit & validation calls
 *
 *    Rev 1.32   Dec 22 1999 13:17:02   DT24433
 * save last focused control
 *
 *    Rev 1.31   Dec 21 1999 13:55:12   DT24433
 * initial notification changes
 *
 *    Rev 1.30   Dec 14 1999 13:09:52   DT24433
 * made DString const in SetControlText
 *
 *    Rev 1.29   Dec 09 1999 18:44:36   DT24433
 * added Show/Hide to ConnectControl(s)ToData
 *
 *    Rev 1.28   Dec 09 1999 13:15:42   DT24433
 * changed default parms on LoadControls
 *
 *    Rev 1.27   Dec 08 1999 16:31:46   DT24433
 * changed to use basedlgconstants.h
 *
 *    Rev 1.26   Dec 06 1999 18:27:04   DT24433
 * added support for DoPreListItemChanged
 *
 *    Rev 1.25   Dec 03 1999 19:56:16   YINGZ
 * add ConnectControlToData
 *
 *    Rev 1.24   Dec 03 1999 13:12:56   DT24433
 * removed fieldvalidate functionality
 *
 *    Rev 1.23   Nov 30 1999 09:17:00   YINGZ
 * modify DlListChanged
 *
 *    Rev 1.22   Nov 29 1999 15:01:34   YINGZ
 * add bIsNewItem to DoListItemChanged and ListItemChanged
 *
 *    Rev 1.21   Nov 24 1999 11:04:50   DT24433
 * added ListItemChanged & DoListItemChanged
 *
 *    Rev 1.20   Nov 17 1999 12:51:52   DT24433
 * more control changes
 *
 *    Rev 1.19   Nov 12 1999 13:21:18   DT24433
 * listview container changes
 *
 *    Rev 1.18   Nov 11 1999 09:11:18   DT24433
 * changed some flag support
 *
 *    Rev 1.17   Nov 10 1999 09:54:22   YINGZ
 * modify parameter
 *
 *    Rev 1.16   Nov 09 1999 16:38:28   DT24433
 * changed SetControlText bFormatted default parm to false
 *
 *    Rev 1.15   Nov 09 1999 12:10:58   YINGZ
 * add list control filter
 *
 *    Rev 1.14   Nov 08 1999 12:04:00   YINGZ
 * change inheritance
 *
 *    Rev 1.13   Nov 06 1999 13:23:40   YINGZ
 * SetControlTextOnly removed
 *
 *    Rev 1.12   Nov 05 1999 10:35:50   YINGZ
 * add SetControlTextOnly and flag to REinitcontrol
 *
 *    Rev 1.11   Nov 04 1999 11:36:38   DT24433
 * misc
 *
 *    Rev 1.10   Nov 03 1999 15:12:50   DT24433
 * new control methods
 *
 *    Rev 1.9   Nov 02 1999 17:25:56   YINGZ
 * add index
 *
 *    Rev 1.8   Oct 29 1999 16:27:28   YINGZ
 * add reinitcontrol
 *
 *    Rev 1.7   Oct 28 1999 16:51:52   DT24433
 * changed doOk/doCancel to ok2/cancel2
 *
 *    Rev 1.6   Oct 27 1999 09:55:52   YINGZ
 * add ControlUpdate
 *
 *    Rev 1.5   Oct 18 1999 16:42:00   DT24433
 * misc. changes
 *
 *    Rev 1.4   Oct 14 1999 10:16:32   DT24433
 * added new methods
 *
 *    Rev 1.3   Oct 04 1999 17:42:38   DT24433
 * preliminary changes for BaseControl interaction
 *
 *    Rev 1.2   Sep 14 1999 11:04:00   YINGZ
 * add GetOverrideItemString
 *
 *    Rev 1.1   Jul 08 1999 10:04:40   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
