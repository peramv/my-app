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

#include <uibase\BaseDlgConstants.h>
#include <bfcbo\BFObserver.hpp>
#include <bfdata\bffieldid.hpp>
#include <bfproc\bfcontainerid.hpp>

// Forward references
class BaseDlg;
class BFProperties;
class DSTMsg;
class GenericInterface;

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

class WIN32UIBASE_LINKAGE BaseControl : public BFObserver
{
public:
   /**
     * Constructor - Control needs to be initialized (Init) with containerID and 
     * fieldID prior to use.
     * @param rpParent - reference pointer to parent BaseDlg instance
     * @param controlID - Associated resource ID.
     * @param controlGroupID - Associated control group.
     * @returns void pointer of list to use.
     */
   BaseControl(
              BaseDlg *rpParent,
              UINT controlID,
              UINT controlGroupID = 0
              );

   void SetControlGroupID( UINT controlGroupID )
   {
      _uiControlGroupID = controlGroupID;
   }

   virtual ~BaseControl();
   /**
     * This method sets the control to the default value
     */
// TODO - probably don't need this ???
   void Clear();

   /**
     * This method clears the control's error state
     */
   void ClearErrorState();
   /**
     * This method sets the connected state. 
     * @param bFlag - true = connected, get properties & setup
     *                false = disconnected, disable control for user input
     * @param bShowHideBasedOnConnection - true = use the connection state to
     *    show/hide, false = don't affect visibility
     */
   void ConnectToData(
                     bool bFlag,
                     bool bShowHideBasedOnConnection = false
                     );
   /**
     * This method sets the Enabled state
     * @param bFlag - true = enabled
     */
   void Enable(
              bool bFlag
              );
   /**
     * This method returns the currently associated container ID
     */
   const BFContainerId& GetContainerID() const
   {
      return( idContainer_ );
   }
   /**
     * This method returns the associated control group ID
     */
   UINT GetControlGroupID() const
   {
      return(_uiControlGroupID);
   }
   /**
     * This method returns the associated control ID
     */
   UINT GetControlID() const
   {
      return(_uiControlID);
   }
   /**
     * This method returns the control's parent dialog
     */
   BaseDlg *GetParentDlg() const
   {
      return(_rpParentDlg);
   }
   /**
     * This method returns the control's parent dialog's parent process
     */
   GenericInterface *GetParentProcess() const
   {
      return(_rpParentProcess);
   }
   /**
     * This method returns the error state.
     * @returns highest SEVERITY encountered
     */
   SEVERITY GetErrorState() const;
   /**
     * This method returns the currently associated field ID
     * @param index - index of associated field
     */
   const BFFieldId &GetFieldID(
                              int index = 0
                              ) const
   {
      return(_fieldIDs[index]);
   }
   /**
     * This method returns the number of fields for the control.
     * @returns UINT with associated bit flags
     */
   int GetFieldCount() const
   {
      return(_fieldIDs.size());
   }
// TODO - remove this method (use above method)
   int GetNumOfFields() const
   {
      return(_fieldIDs.size());
   } 
   /**
     * This method gets the value of the control in either display (formatted)
     * or host (unformatted) format.  The value actually comes from the
     * associated storage, validation of the control is forced if necessary.
     * The default function is to get the text from the associated field, but
     * this method will call BaseDlg::GetDataFromControl to provide an
     * opportunity for an override.
     * Exception will be thrown on failure.
     * @param strValueOut - reference of string where value is returned.
     * @param bFormatted - true = display format, false = host format
     * @param index - index of associated field
     */
   void GetText( DString &strValueOut, bool bFormatted=true, int index = 0 ) const;
   /**
     * This method is used to set the containerID and fieldID, setting other
     * values as appropriate.  This may be called more than once (to allow the
     * same control to be tied to different fields, depending on context).
     * @param containerID - Container to associate with.
     * @param idField - Field to associate with.
     * @param flags - flags controlling behavior, -1 = use existing flags (no
     *   replacement
     */
   void Init( const BFContainerId& idContainer, const BFFieldId &idField, UINT flags );
   /**
     * This method checks the control's connected state.  This is a programmer
     * driven flag that should be used when select controls within the same
     * control group are used/not used at different times.  (If all controls in
     * a group are connected/disconnected at the same time, use the data
     * connected flag.)
     * @returns true = connected
     */
   bool IsConnected() const
   {
      return(_bConnected);
   }
   /**
     * This method checks if a control is connected to live data.  This flag is
     * a combination of automatic and programmer driven operations and controls 
     * whether or not many other operations can occur.  If an item is not
     * data connected, it will be automatically disabled and cleared.
     * @returns true = data connected, false = disconnected
     */
   bool IsDataConnected() const
   {
      return(_bDataConnected);
   }
   /**
     * This method checks the control's enabled state.
     * @returns true = enabled
     */
   bool IsEnabled() const
   {
      return(_bEnabled);
   }
   /**
     * This method checks the "error" state.
     * @returns true = pending message
     */
   bool IsError() const
   {
      return(_errorState != NO_CONDITION);
   }
   /**
     * This method checks if a control is a masked one 
     * @returns true if the field is masked , false = if the field is not masked
     */
   bool IsMaskedField() const
   {
      return( ( _flags & CTRLFLAG_MASKED ) != 0 );  
   }
   /**
     * This method checks if a control is a GUI field.
     * @returns true = GUI field, false = process/CBO field
     */
   bool IsGUIField() const
   {
      return( ( _flags & CTRLFLAG_GUI_FIELD ) != 0 );  // Gets rid of warning
   }
   /**
     * This method checks for manual load.
     * @returns true = load should be specifically called for this control,
     *   not loaded by default.
     */
   bool IsManualLoad() const
   {
      return( ( _flags & CTRLFLAG_MANUAL_LOAD ) != 0 );  // Gets rid of warning
   }
   /**
     * This method checks the overall updateable state.
     * @returns true = updates allowed
     */
   bool IsUpdateable() const
   {
      return(_bUpdateable);
   }
   /**
     * This method checks the valid state attempting to Store modified data
     * if necessary.
     * @returns true = control is valid
     */
   bool IsValid() const;
   /**
     * This method checks the control's visibility state.
     * @returns true = visible
     */
   bool IsVisible() const
   {
      return(_bVisible);
   }
   /**
     * This method sets the control to the associated value from the HOST data
     * storage area.  This method will invoke DoSetText which must be
     * implemented by derived classes
     * Exception will be thrown on failure.
     * @param bUpdated - optional parm indicating whether should set field as
     *   updated.  true = set as updated, false = normal load
     */
   void Load(
            bool bUpdated = false
            );
   /**
     * This method forces the control to get the current error state of the
     * associated field from the parent process.
     */
   SEVERITY LoadErrorState();
   /**
     * This method gets notifications from whoever we are observing.
     * @param eventGroup - Event group of event that occurred
     * @param event - Event that occurred
     * @param strHint - hint for event (if applicable)
     */
   virtual void onNotify(
                        E_EVENT_GROUP eventGroup,
                        E_EVENT event,
                        const DString &strHint
                        );
   /**
     * This method sets the connected state. Note that if the value is true,
     * ConnectToData must be called after this, for value to take affect.
     * @param bFlag - true = connected
     */
   void SetConnected(
                    bool bFlag
                    );
   /**
     * This method sets the value of the associated storage and the control to
     * the specified value.
     * @param strValueIn - value to set.
     * @param bFormatted - true = display format, false = host format
     * @param index - index of associated field
     * @param bUpdated - optional parm indicating whether to set field as
     *   updated or not.  true = updated, false = treat like normal load
     * @returns flag with true = success, false = failure, check conditions
     */
   bool SetText(
               const DString &strValueIn,
               bool bFormatted = false,
               int index = 0,
               bool bUpdated = false
               );
   /**
// TODO - not sure if we want to allow this.  What is the need?
     * This method sets the value of the control (not any associated storage)
     * to the specified value. The value passed in should be in display format.
     * @param index - index of associated field
     * @returns flag with true = success, false = failure, check conditions
   bool SetTextOnly(
      const DString &strValueIn,
    int index = 0
      );
     */
   /**
     * This method sets the visible state
     * @param bFlag - true = visible
     */
   void Show(
            bool bFlag
            );
   /**
     * This method displays an appropriate icon depending on its error state.
     */
   void ShowIndicator();
   /**
     * This method forces a sync up between the control and the associated data
     * storage area.  (Moving data from the control to the storage area if the
     * data has been modified since last stored.) This is invoked by BaseDlg
     * during OK processing.
     * @returns flag with true = success, false = failure, check conditions
     */
   virtual bool Store();

//  Tooltip display (DSTMsg) interface
   bool IsToolTipVisible();
   void MouseLeave();
   void ToggleToolTip();
   void HideToolTip();
   bool ToolTipExists() const
   {
      return(_pToolTip != NULL);
   }
   void TriggerToolTip();
   void SetInitialLoad(
                      bool bFlag
                      )
   {
      _bInitialLoad = bFlag;
   }

protected:
   /**
     * If the error passed in is greater than the current error state, then
     * the new error state is set.  (Use ClearErrorState to set back to no
     * error.)
     */
   void AccumulateErrorState(
                            SEVERITY newState
                            );
   /**
     * This method clears any current value in the control.
     * This method must be implemented in derived classes.
     */
   virtual void DoClear()
   {
      return;
   }
   /**
     * This method gets the value from the control in display format.
     * This method must be implemented in derived classes.
     * @param strValueOut - reference of string where value is returned.
     * @param index - index of associated field
     */
   virtual void DoGetText(
                         DString &strValueOut,
                         int index
                         ) const = 0;
   /**
     * This method allows the derived subclasses to adjust for new properties.
     * This may be called more than once (to allow the same control to be tied
     * to different fields, depending on context).
     * This method must be overridden in derived class.
     */
   virtual void DoInit() = 0;
   /**
     * This method is used to force the storing of data on any change in a
     * control.  This method stores the control's data, clearing/setting any
     * error messages (tooltips), and setting error indicator as appropriate.
     */
   void DoChangeUpdate();
   /**
     * This method performs the KillFocus handling and should be invoked by
     * by the control's KillFocus handler.  This method provides the base
     * functionality of trying to store the control's data, clearing any
     * error messages (tooltips), and setting error indicator as appropriate.
     */
   void DoKillFocus();
   /**
     * This method performs the SetFocus handling and should be invoked by
     * by the control's SetFocus handler.  This method provides the base
     * functionality of displaying a tool tip as appropriate.
     */
   void DoSetFocus();
   /**
     * This method sets the value of the control to the specified value. The
     * value passed in should be in raw HOST format.  This method is used to
     * programatically set a value into a control without affecting the
     * associated field.
     * This method must be implemented in derived classes.
     * @param strValueIn - value to set.
     * @param index - index of associated field
     * @returns flag with true = success, false = failure, check conditions
     */
   virtual bool DoSetText(
                         const DString &strValueIn,
                         int index
                         ) = 0;
   /**
     * This method returns flags for the control.
     * @returns UINT with associated bit flags
     */
   UINT GetFlags() const
   {
      return(_flags);
   }
   /**
     * This method returns the associated properties object.
     * @param index - index of associated field
     * @returns const pointer to properties, NULL if none set.
     */
   const BFProperties *GetProperties(int index = 0);
   /**
     * This method returns whether the derived control is updateable.
     * @returns true if updateable, false otherwise
     */
   bool IsControlUpdateable() const
   {
      return(_bControlUpdateable);
   }
   /**
     * This method returns whether the derived control has been inited (DoInit)
     * since the last data connection.
     * @returns true if has been initialized, false otherwise
     */
   bool IsFirstTimeInit() const
   {
      return(_bFirstTimeInit);
   }
   /**
     * This method returns whether the dialog has set the control as updateable.
     * @returns true if updateable, false otherwise
     */
   bool IsGUIUpdateable() const
   {
      return( ( _flags & CTRLFLAG_NOT_UPDATABLE ) == 0 );
   }
   bool IsInitialLoad() const
   {
      return(_bInitialLoad);
   }
   bool IsRegistered() const
   {
      return(_bRegistered);
   }
   /**
     * This method gets the data from the control and stores in the associated
     * data storage area.  This is invoked during KillFocus.  This method
     * will call a virtual method in the parent BaseDlg where overrides may be
     * provided.  (See BaseDlg::SetDataFromControl)
     * This method only stores if modified, otherwise simply returns IsValid.
     * @param bDataChanged - reference to flag indicating whether save changed
     *   any data.  true = data changed
     * @returns flag with true = success, false = failure, check conditions
     */
   bool SaveAndValidate(
                       bool &bDataChanged
                       );
   /**
     * This method stores the specified value in the associated data
     * storage area.  This is invoked during KillFocus.  This method
     * will call a virtual method in the parent BaseDlg where overrides may be
     * provided.  (See BaseDlg::SetDataFromControl)
     * This method only stores if modified, otherwise simply returns IsValid.
     * @param strValueIn - value to set.
     * @param bFormatted - true = display format, false = host format
     * @param index - index of associated field
     * @param bClearErrorState - reference to flag indicating whether to clear
     *   the error state for the control.  Once cleared, the flag is set to
     *   false.
     * @param bDataChanged - reference to flag indicating whether save changed
     *   any data.  true = data changed
     * @returns flag with true = success, false = failure, check conditions
     */
   bool SaveAndValidateValue(
                            const DString &strValueIn,
                            bool bFormatted,
                            int index,
                            bool &bClearErrorState,
                            bool &bDataChanged
                            );
   /**
     * This method should be called by derived controls during their
     * constructor if the control does not allow updates (like static text
     * control).
     */
   void SetControlNotUpdateable()
   {
      _bControlUpdateable = false;
   }
   /**
     * This method sets the first time init flag.  This flag is used to
     * determine if derived control initialization (DoInit) has been called
     * at least once since the control was connected (or reconnected)
     * @param bFlag - true = need DoInit, false = DoInit called already
     */
   void SetFirstTimeInit(
                        bool bFlag
                        )
   {
      _bFirstTimeInit = bFlag;
   }
   // This method should only be called during DoInit in derived classes
   virtual void SetFlags(
                        UINT flags
                        )
   {  // Note: if a version of this is made public, need to do a CheckFlags
      //   - don't want a checkFlags for this version (or have internal
      //   methods set _flags directly instead of use this).
      _flags = flags;
   }
   /**
     * This method sets the load format.
     * @param bLoad - true = load formatted, false = load unformatted
     */
   void SetLoadDisplayFormat(
                            bool bLoad
                            )
   {
      _bLoadDisplayFormat = bLoad;
   }
   void setRegistered(
                     bool bRegistered
                     )
   {
      _bRegistered = bRegistered;
   }
   /**
     * This method sets the updateable state.
     * @param bUpdateable - true = updateable
     */
   void SetUpdateable( bool bUpdateable )
   {
      _bUpdateable = bUpdateable;
   }
   /**
     * This method sets the updated state.  Any updated control = dirty 
     * dialog.
     * @param bUpdated - true = modified
     */
   void SetUpdated( bool bUpdated )
   {
      _bUpdated = bUpdated;
   }
   /**
     * This method sets the valid state.  
     * @param bValid - true = valid
     */
   void SetValid( bool bValid )
   {
      _bValid = bValid;
   }

   friend class BaseDlg;
   void SetCtrlReadOnly(bool bReadOnly = true);
   virtual bool doSetCtrlReadOnly(bool bReadOnly){return(false);};
   void DestroyToolTip(void);

private:
   typedef std::vector< BFFieldId > FIELDIDS;
   typedef std::vector< DString > OLDVALUES;
   typedef std::vector< const BFProperties * > PROPERTIES;

   // flags for control state
   bool _bConnected;             // true = control in valid state to use
   bool _bControlUpdateable;     // true = derived control cannot be updated
   bool _bDataConnected;         // true = control connected to live data
   bool _bEnabled;               // true = control is enabled
   bool _bFirstTimeInit;         // true = control needs DoInit, false = already done
   bool _bInitialLoad;           // true = control needs to force load
   bool _bUpdateable;            // true = control can be updated
   bool _bVisible;               // true = control is visible

   // Flag used to indicate the control is currently handling a notification.  
   // This is currently only set around the call for CheckForInit to prevent
   // re-registering an observer during the notification.
   bool _bDuringNotify;        
   // Flag indicating if data to load control should be formatted for display
   bool _bLoadDisplayFormat; 
   // Flag indicating if have registered as Observer
   bool _bRegistered;
   // Flag used to indicate that control is in SaveAndValidateValue method
   bool _bSaveAndValidateValue;     
   // Associated field has been updated - this is reset on clear and load?
   bool _bUpdated;
   // Control is not in a valid state
   bool _bValid;
   CONDITIONVECTOR _conditions;
   FIELDIDS _fieldIDs;
   UINT _flags;
   // If 0, no associated container defined.
   BFContainerId idContainer_;   
   // Old values for fields
   OLDVALUES _oldValuesIn;       // Used for Load (often display format)
   OLDVALUES _oldValuesOut;      // Used for Store - always unformatted
   PROPERTIES _properties;

   DSTMsg *_pToolTip;
   // Parent dialog, used to communicate
   BaseDlg *_rpParentDlg;
   // Parent process for handling data
   GenericInterface *_rpParentProcess;
   // control group the control is associated with
   UINT _uiControlGroupID;
   // resource ID of control
   UINT _uiControlID;

   // Variables for managing error state
   // Current state of control in SEVERITY
   SEVERITY _errorState;         
   CStatic *_pIndicator;

   void CheckFlags();
   void CheckForInit(
                    bool bForceControlInit
                    );
   void ClearContainers();
   void ClearForDataConnect();
   void ControlUpdated(
                      DString &str,
                      bool bFormatted,
                      int index
                      );
   DSTMsg *GetToolTip();
   CWnd *GetWindow();
   /**
     * This method sets the data connected state
     * @param bFlag - true = data connected
     */
   void SetDataConnected(
                        bool bFlag
                        );
   void ShowToolTip();
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/basecontrol.hpp-arc  $
//
//   Rev 1.17   May 22 2012 13:43:30   dchatcha
//IN#2957144 - P0186486FN15 - Source of Fund issues on RRIF screen, issue#2 - destroy tool tips when no need to display every time, to fix display issue
 * 
 *    Rev 1.16   Jan 06 2003 16:45:52   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.15   Nov 27 2002 15:05:18   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.14   Oct 09 2002 17:42:34   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.13   Aug 29 2002 12:57:04   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.12   19 Mar 2002 13:36:12   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.11   07 Jun 2001 09:33:40   KOVACSRO
 * Modified GetProperties().
 * 
 *    Rev 1.10   16 May 2001 14:32:36   YINGZ
 * show icon for non updatable control and code sync
 * 
 *    Rev 1.9   26 Apr 2001 16:46:46   KOVACSRO
 * made CheckFlags() virtual.
 * 
 *    Rev 1.8   05 Apr 2001 15:01:54   KOVACSRO
 * Made SetCtrlReadOnly protected.
 * 
 *    Rev 1.7   03 Apr 2001 11:41:28   KOVACSRO
 * Permission check stuff.
 * 
 *    Rev 1.6   30 Mar 2001 12:03:42   KOVACSRO
 * SetCtrlReadOnly implemented in BaseControl.
 * 
 *    Rev 1.5   29 Mar 2001 13:41:14   KOVACSRO
 * Added SetCtrlReadOnly().
 * 
 *    Rev 1.4   Dec 19 2000 16:16:10   HUANGSHA
 * Added HideToolTip()
 * 
 *    Rev 1.3   May 31 2000 16:42:44   BUZILA
 * masking support
 * 
 *    Rev 1.2   May 09 2000 10:18:10   BUZILA
 * grid fixes
 * 
 *    Rev 1.1   Feb 15 2000 18:58:50   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:00:56   SMITHDAV
 * Initial revision.
// 
//    Rev 1.31   Jan 21 2000 11:36:52   YINGZ
// fix multiline reset problem
// 
//    Rev 1.30   Jan 05 2000 18:14:50   DT24433
// added cross-edit calls
// 
//    Rev 1.29   Jan 04 2000 12:41:38   DT24433
// don't register observer during notification
// 
//    Rev 1.28   Dec 31 1999 14:13:18   DT24433
// notification changes
// 
//    Rev 1.27   Dec 29 1999 11:55:26   DT24433
// fixed display bug (missing data) for Load initiated by SetText
// 
//    Rev 1.26   Dec 22 1999 16:44:42   DT24433
// prevent some load operations if value is unchanged
// 
//    Rev 1.25   Dec 22 1999 13:16:58   DT24433
// don't load during store/settext if no changes, and notification changes
// 
//    Rev 1.24   Dec 09 1999 18:43:26   DT24433
// added show/hide to ConnectControl(s)ToData
// 
//    Rev 1.23   Dec 08 1999 16:26:36   DT24433
// moved flags to basedlgconstants.h and added ControlUpdated
// 
//    Rev 1.22   Dec 06 1999 17:32:40   DT24433
// clean up
// 
//    Rev 1.21   Nov 19 1999 17:37:40   DT24433
// better error support
// 
//    Rev 1.20   Nov 17 1999 12:54:34   DT24433
// more control changes
// 
//    Rev 1.19   Nov 15 1999 14:02:00   DT24433
// changed to pass control flags in init
// 
//    Rev 1.18   Nov 12 1999 13:18:08   DT24433
// misc
// 
//    Rev 1.17   Nov 11 1999 10:53:32   DT24433
// added DoChangeUpdate and flag GUI_FIELD
// 
//    Rev 1.16   Nov 11 1999 09:11:16   DT24433
// more flag/property support
// 
//    Rev 1.15   Nov 09 1999 17:21:06   DT24433
// flag changes
// 
//    Rev 1.14   Nov 05 1999 15:33:46   DT24433
// added initial condition handling
// 
//    Rev 1.13   Nov 05 1999 12:42:58   YINGZ
// makeGetFlags const
// 
//    Rev 1.12   Nov 05 1999 11:23:00   YINGZ
// add CTRLFLAG_NOT_UPDATABLE flag
// 
//    Rev 1.11   Nov 05 1999 10:36:32   YINGZ
// add setflag
// 
//    Rev 1.10   Nov 04 1999 15:31:14   YINGZ
// Add CTRLFLAG_STRIP_LEADING_SPACE flag
// 
//    Rev 1.9   Nov 04 1999 07:52:30   DT24433
// added proper handling of ClearErrorState
// 
//    Rev 1.8   Nov 03 1999 15:12:46   DT24433
// new flags and methods
// 
//    Rev 1.7   Nov 03 1999 10:09:24   YINGZ
// add getFlags
// 
//    Rev 1.6   Nov 02 1999 17:25:54   YINGZ
// add index
// 
//    Rev 1.5   Oct 22 1999 17:06:28   YINGZ
// add getparentdlg
// 
//    Rev 1.4   Oct 18 1999 16:39:46   DT24433
// misc. changes
// 
//    Rev 1.3   Oct 14 1999 15:41:30   DT24433
// provide interface to tooltip so derived classes don't access directly and use lazy initialization for tooltip
// 
//    Rev 1.2   Oct 14 1999 13:51:10   YINGZ
// add tooltip support
// 
//    Rev 1.1   Oct 14 1999 10:11:46   DT24433
// added new methods
 * 
 *    Rev 1.0   Oct 04 1999 16:44:04   DT24433
 * First check in
 * 
 */
