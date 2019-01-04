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
// ^FILE   : BaseControl.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 10/01/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BaseControl
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"
#include "BaseControl.hpp"
#include "BaseDlg.h"
#include <bfcbo\BFProperties.hpp>
#include <bfdata\bfdatafieldproperties.hpp>
#include <bfdata\bffieldid.hpp>
#include "DSTMsg.h"
#include <IDIString.hpp>
#include <assert.h>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "BaseControl" );
}

namespace CND
{  // Conditions used
}

// TODO - not sure that _bUpdated flag is needed.  We may drive this completely
//  from CBO since other fields may not matter.

//******************************************************************************
//  Public methods
//******************************************************************************

BaseControl::BaseControl(
                        BaseDlg *rpParent,
                        UINT controlID,
                        UINT controlGroupID
                        ) :
_bConnected( true ),
_bControlUpdateable( true ),   // Non-updateable control set false in constr.
_bDataConnected( false ),
_bEnabled( true ),
_bFirstTimeInit( true ),
_bInitialLoad( true ),
_bUpdateable( true ),
_bVisible( true ),
_bDuringNotify( false ),
_bLoadDisplayFormat( true ),
_bRegistered( false ),
_bSaveAndValidateValue( false ),
_bUpdated( false ),
_bValid( false ),
_flags( 0 ),
_uiControlGroupID( controlGroupID ),
_uiControlID( controlID ),
_errorState( NO_CONDITION ),
_pIndicator( NULL ),
_pToolTip(NULL),
_rpParentDlg( rpParent )
{
   _rpParentProcess = _rpParentDlg->getParent();
}

//******************************************************************************

BaseControl::~BaseControl()
{
   ClearContainers();

   delete _pToolTip;
   _pToolTip = NULL;
   delete _pIndicator;
   _pIndicator = NULL;
}

//******************************************************************************

void BaseControl::Clear()
{
   DoClear();
   SetUpdated( false );
   ClearErrorState();
   SetValid( false );
   ShowIndicator();
}

//******************************************************************************

void BaseControl::ClearErrorState()
{
   _conditions.clear();
   _errorState = NO_CONDITION;
   HideToolTip();
}

//******************************************************************************

void BaseControl::ConnectToData(
                               bool bFlag,
                               bool bShowHideBasedOnConnection
                               )
{
   ClearForDataConnect();
   if( !IsConnected() )
   {
      bFlag = false;
   }
   if( bFlag && !IsGUIField() && ( _fieldIDs.empty() || _fieldIDs[0] == ifds::NullFieldId ) )
   {  // No field defined, has not been initialized !!
// TODO - add condition
      assert( 0 );
      bFlag = false;
   }

   if( bFlag )
   {  // This code only applies if we are connected
      CheckForInit( false );
   }

   SetDataConnected( bFlag );
   if( bShowHideBasedOnConnection )
   {  // Show/Hide based on connection
      Show( bFlag );
   }
}

//******************************************************************************

void BaseControl::Enable(
                        bool bFlag
                        )
{
   GetWindow()->EnableWindow( _bEnabled = bFlag );
}

//******************************************************************************

SEVERITY BaseControl::GetErrorState() const
{
   return(_errorState);
}

//******************************************************************************

void BaseControl::GetText(
                         DString &strValueOut,
                         bool bFormatted,
                         int index
                         ) const
{
   strValueOut = NULL_STRING;
   if( !IsDataConnected() )
   {  // Act as if successful for not connected
      return;
   }

   if( !_rpParentDlg->GetDataForControl( _uiControlID, strValueOut,
                                         bFormatted, index ) )
   {  // Not overridden, get by default method
      if( IsGUIField() )
      {  // Should have been handled in SetDataFromControl
         assert( 0 );
         throw;
      }
      _rpParentProcess->getField( _rpParentDlg, idContainer_, _fieldIDs[index],
                                  strValueOut, bFormatted );
   }

   if( !( _flags & CTRLFLAG_NO_STRIP_LEADING_SPACE ) )
   {  // strip trailing occurs in BFBase - always strip leading here unless flag
      // is set.
      strValueOut.stripLeading();
   }
}

//******************************************************************************

void BaseControl::Init(
                      const BFContainerId& idContainer,
                      const BFFieldId &idField,
                      UINT flags
                      )
{
   if( flags != -1 )
   {  // New flags to use
      SetFlags( flags );
   }
   idContainer_ = idContainer;

   ClearContainers();
   if( _flags & CTRLFLAG_FIELDS_FROM_SUB_LIST )
   {  // fieldID is associated with a sub list
      DString strIdi;
      DString strTag;
      DString strValue;

      const BFDataFieldProperties* pProps = (_rpParentDlg->getFieldAttributes( _rpParentDlg, idField ) );
      if( NULL != pProps->getSubstitutionSet( ClientLocaleContext::get() ) )
      {
         pProps->getAllSubstituteValues( strIdi, ClientLocaleContext::get(), true );
      }
      else
      {
         assert( 0 );   // problem??
         return;
      }

      I_CHAR *rpStr = const_cast< I_CHAR * >( strIdi.c_str() );

      while( *rpStr != '\0' )
      {
         rpStr = parseIdiString( rpStr, strTag, strValue );
         if( strTag != NULL_STRING )
         {
            const BFFieldId &id = BFFieldId::getId( strTag );
            _fieldIDs.push_back( id );
            _oldValuesIn.push_back( NULL_STRING );
            _oldValuesOut.push_back( NULL_STRING );
            _properties.push_back( NULL );
         }
      }
   }
   else
   {  // Normal 1 control associated with 1 field
      if( idField != ifds::NullFieldId || IsGUIField() )
      {  // We have something to work with (connected) - only allow 0 when
         //  GUI field
         _fieldIDs.push_back( idField );
         _oldValuesIn.push_back( NULL_STRING );
         _oldValuesOut.push_back( NULL_STRING );
         _properties.push_back( NULL );
      }
   }
}

//******************************************************************************

bool BaseControl::IsValid() const
{
   return(_bValid);
}

//******************************************************************************

void BaseControl::Load(
                      bool bUpdateFlag
                      )
{
   DString str;
   bool bDataChanged = false;

   if( !IsDataConnected() )
   {  // Act as if successful for not connected
      return;
   }

   ClearErrorState();

   // Load control from associated container/field(s)
   for( int i = 0; i < GetFieldCount(); i++ )
   {  // For all associated fields
      CONDITIONVECTOR conditions;
      if( !_rpParentDlg->GetDataForControl( _uiControlID, str, true, i ) )
      {  // Not overridden, get by default method
         //CONDITIONVECTOR conditions;

         if( IsGUIField() )
         {  // Should have been handled in GetDataFromControl
            assert( 0 );
            throw;
         }
         _rpParentProcess->getField( _rpParentDlg, idContainer_, _fieldIDs[i],
                                     str, _bLoadDisplayFormat );
         /*if ( IsUpdateable() ) // some non updatable control needs error msg
         {  // Accumulate errors only if updateable
            AccumulateErrorState( _rpParentProcess->getErrors( _rpParentDlg,
               idContainer_, _fieldIDs[i], conditions ) );
         }*/
      }
      if( !IsGUIField() )
      {
         AccumulateErrorState( _rpParentProcess->getErrors( _rpParentDlg,
                                                            idContainer_, _fieldIDs[i], conditions ) );
      }

      if( !( _flags & CTRLFLAG_NO_STRIP_LEADING_SPACE ) )
      {  // strip trailing occurs in BFBase - always strip leading here unless
         // flag is set.
         str.stripLeading();
      }

      if( str != _oldValuesIn[i]  || IsInitialLoad() || GetFieldCount() > 1 ) //for multiline control,we should always load  //i > 0 )
      {
         // Only load if data change or control needs initial load - except
         // always loading additional fields of multi-field control
         SetInitialLoad( false );
         bDataChanged = true;
         // Set initial value
         _oldValuesIn[i] = str;

         // Do we need any error handling here???
         DoSetText( str, i );
      }
      if( bDataChanged )
      {
         ControlUpdated( str, _bLoadDisplayFormat, i );
      }
   }

   if( IsUpdateable() )
   {
      SetUpdated( bUpdateFlag );
      if( IsGUIField() && ( str == NULL_STRING ) && GetProperties() &&
          GetProperties()->isRequired() )
      {  // If empty & required, make sure we force validation on the fly.
         // Note - we are only doing this for first field of multi-field
         // control at this point.  Change to check all if it matters
         //for fields that are in a CBO, BFBase::validateField() will do the job
         SetValid( false );
      }
      else
      {
         SetValid( GetErrorState() <= WARNING );
      }
   }

   ShowIndicator();   // Show appropriate icon
}

//******************************************************************************

SEVERITY BaseControl::LoadErrorState()
{ 
// TODO - not sure if method will be used
   if( !IsDataConnected() || /*!IsUpdateable() ||*/ IsGUIField() )
   {  // Act as if successful for not connected or not updatable
      // GUIField errors not currently supported
      return(NO_CONDITION);
   }

   ClearErrorState();

   // Load control from associated container/field(s)
   for( int i = 0; i < GetFieldCount(); i++ )
   {  // For all associated fields
      CONDITIONVECTOR conditions;

      AccumulateErrorState( _rpParentProcess->getErrors( _rpParentDlg,
                                                         idContainer_, _fieldIDs[i], conditions ) );
   }

   ShowIndicator();
   return(GetErrorState());
}

//******************************************************************************

void BaseControl::onNotify(
                          E_EVENT_GROUP eventGroup,
                          E_EVENT event,
                          const DString &strHint
                          )
{
   switch( eventGroup )
   {
      case FIELD_NOTIFICATIONS:
         switch( event )
         {
            case E_EVENT_PROPERTY_CHANGE:
            case E_EVENT_STATE_CHANGE:
               // The following flag is checked during CheckForInit
               _bDuringNotify = true;
               CheckForInit( true );
               _bDuringNotify = false;
               Load();
               break;
            case E_EVENT_VALUE_CHANGE:
               if( !_bSaveAndValidateValue )
               {
                  Load( false );

                  // setup updated flag in the dlg
                  _rpParentDlg->setUpdateFlag( true );
               }
               break;
         }
         break;
   }
   _bDuringNotify = false;
}

//******************************************************************************

void BaseControl::SetConnected(
                              bool bFlag
                              )
{
   _bConnected = bFlag;
   if( !bFlag )
   {  // If false we can immediately stop connection, but user must invoke
      // ConnectToData for a true setting to take affect
      ConnectToData( false );
   }
}

//******************************************************************************

bool BaseControl::SetText(
                         const DString &strValueIn,
                         bool bFormatted,
                         int index,
                         bool bUpdated
                         )
{  // This method is used to set control and associated storage to specified 
   // value.
   bool bRtn = false;
   bool bClearErrorState = true;
   bool bDataChanged = false;

   if( !IsDataConnected() )
   {  // Act as if successful for not connected
      return(true);
   }

   if( ( bRtn = SaveAndValidateValue( strValueIn, bFormatted, index,
                                      bClearErrorState, bDataChanged ) ) )
   {
      if( bDataChanged )
      {  // Load with appropriate update flag
         Load( bUpdated );
      }
   }

   return(bRtn);
}

//******************************************************************************
/*
bool BaseControl::SetTextOnly(
   const DString &strValueIn,
   int index
   )
{
   bool bRtn = false;
   if ( !IsDataConnected() )
   {  // Act as if successful for not connected
      return true;
   }

   bRtn = DoSetText( strValueIn, index );
   _rpParentDlg->ControlUpdated( _uiControlID );

   return bRtn;
}
*/
//******************************************************************************

void BaseControl::Show(
                      bool bFlag
                      )
{
   int nCmdShow = SW_SHOW;

   _bVisible = bFlag;
   if( !bFlag )
   {
      nCmdShow = SW_HIDE;
      if( ToolTipExists() )
      {  // Hide tooltip, if showing
         GetToolTip()->ShowMsg( false );
         DestroyToolTip();
      }
   }
   GetWindow()->ShowWindow( nCmdShow );
   // Hide/show indicator as appropriate
   ShowIndicator();
}

//******************************************************************************

void BaseControl::ShowIndicator()
{
   HICON icon = NULL;

   if( !IsDataConnected() || !IsError() || !IsVisible() )
   {
      delete _pIndicator;
      _pIndicator = NULL;
      return;
   }

   switch( _errorState )
   {
      case CRITICAL_ERROR:
      case SEVERE_ERROR:
         icon = LoadIcon( NULL, IDI_HAND );
         break;
      case WARNING:
         icon = LoadIcon( NULL, IDI_EXCLAMATION );
         break;
      case INFORMATIONAL:
         icon = LoadIcon( NULL, IDI_ASTERISK );
         break;
   }

   if( icon )
   {
/*    if( _pIndicator && _pIndicator->GetIcon() == icon )
      {  // already exists & same icon
         return;
      }
      else
      {
         delete _pIndicator;
         _pIndicator = NULL;
      }*/
//always delete the _pIndicator, this will trigger a repaint at the new location
//if the dialog is resized - Incident 403519
      delete _pIndicator;
      _pIndicator = NULL;

      CRect CtrlRect;

      CFont* pFont = _rpParentDlg->GetFont( ) ;

      LOGFONT lFont;
      pFont->GetLogFont( &lFont );

      int h=abs(lFont.lfHeight)+4;

      WINDOWPLACEMENT wp;                
      CWnd *rpCtrl = GetWindow();

      rpCtrl->GetWindowPlacement( &wp );

      CRect r( wp.rcNormalPosition.left-h, wp.rcNormalPosition.top, 
               wp.rcNormalPosition.left, wp.rcNormalPosition.top+h );

      // Create indicator and position to left of control
      _pIndicator = new CStatic;
      _pIndicator->Create( NULL, WS_CHILD | SS_ICON,  
                           r, rpCtrl->GetParent() );
      _pIndicator->SetIcon( icon );

      _pIndicator->MoveWindow( &r );
      _pIndicator->ShowWindow( SW_SHOW );
   }
   else
   {
      delete _pIndicator;
      _pIndicator = NULL;
   }
}

//******************************************************************************

bool BaseControl::Store()
{
   bool bDataChanged = false;

   if( !IsDataConnected() )
   {  // Act as if successful for not connected
      return(true);
   }

   return(SaveAndValidate( bDataChanged ));
}

//******************************************************************************
//  Tooltip display interface
//******************************************************************************

bool BaseControl::IsToolTipVisible()
{
   if( !ToolTipExists() )
   {
      return(false);
   }
   return(GetToolTip()->IsMsgAlreadyShown());
}

//******************************************************************************

void BaseControl::MouseLeave()
{
   if( !IsDataConnected() )
   {
      return;
   }
   if( ToolTipExists() )
   {
      GetToolTip()->MouseLeave();
   }
}

//******************************************************************************

void BaseControl::ToggleToolTip()
{
   if( !IsDataConnected() )
   {
      return;
   }

   GetToolTip()->ToggleMsgBox();
}

//******************************************************************************

void BaseControl::TriggerToolTip()
{
   if( !IsDataConnected() || !IsVisible() )
   {
      return;
   }
//   if( !GetToolTip()->IsMsgAlreadyShown() && !IsGUIField() )
   if( !IsGUIField() )
   {  // Controls must be associated with process/CBO field currently
      GetParentProcess()->getErrors( GetParentDlg(), GetContainerID(),
                                     GetFieldID(), _conditions );
      GetToolTip()->SetMessageFromConditions( _conditions );
      GetToolTip()->DelayedDisplay();

      TRACKMOUSEEVENT MouseEvent;
      MouseEvent.cbSize = sizeof( TRACKMOUSEEVENT );
      MouseEvent.dwFlags = TME_LEAVE;
      MouseEvent.hwndTrack = GetWindow()->m_hWnd;
      MouseEvent.dwHoverTime = 0;
      _TrackMouseEvent( &MouseEvent );
   }
}

//******************************************************************************
//  Protected methods
//******************************************************************************

void BaseControl::AccumulateErrorState(
                                      SEVERITY newState
                                      )
{
   if( newState > _errorState )
   {  // Save max error state
      _errorState = newState;
   }
   // Set valid state
   SetValid( GetErrorState() <= WARNING );
}

//******************************************************************************

void BaseControl::DoChangeUpdate()
{
   bool bDataChange = false;
   if( IsDataConnected() /*&& IsUpdateable()*/ )
   {
      DString str;

      if( IsUpdateable() )
         SaveAndValidate( bDataChange );
      else
         bDataChange = true;//force the refresh for indicator and tooltip

      if( bDataChange )
      {  // Should only matter if data changed
         ShowIndicator();
         ShowToolTip();
      }
   }
}

//******************************************************************************

void BaseControl::DoKillFocus()
{
   bool bDataChange = false;

   if( !_rpParentDlg->IsCancelInProgress() && IsDataConnected()
       /* && IsUpdateable()*/ )
   {
      DString str;

      if( SaveAndValidate( bDataChange ) )
      {  // Continue as long as not in error state - also need to check cross
         // edits whether data changed or not (because related field could
         // have been changed previously.  If crossedits don't change on the
         // fly, excessive checking could be avoided by setting flag in
         // control if involved with a cross-edit.
         SEVERITY sevRtn = _rpParentDlg->CheckCrossEdits( this );
         AccumulateErrorState( sevRtn );
      }

      ShowIndicator();

      if( ToolTipExists() )
      {  // Hide tooltip, if showing
         GetToolTip()->ShowMsg( false );
         DestroyToolTip();
      }
      //finally process the tab controls,
      _rpParentDlg->ProcessTabControls();
   }
}

//******************************************************************************

void BaseControl::DoSetFocus()
{
   _rpParentDlg->SetLastControlWithFocus( this );
   ShowToolTip();
}

//******************************************************************************

bool BaseControl::SaveAndValidate(
                                 bool &bDataChanged
                                 )
{
   bool bMyDataChanged = false;
   bDataChanged = false;

   if( !IsDataConnected() || !IsUpdateable() )
   {
      return(true);
   }

   bool bClearErrorState = true; 

   for( int i = 0; i < GetFieldCount(); i++ )
   {  // For all fields associated with this control
      DString str = _oldValuesOut[i];
      DoGetText( str, i );
      // We are defaulting format to the LoadDisplayFormat.  Derived controls
      //  should set/get in the same format
      SaveAndValidateValue( str, _bLoadDisplayFormat, i,
                            bClearErrorState, bMyDataChanged );
      if( bMyDataChanged )
      {
         bDataChanged = true;
      }
   }
   return(IsValid());
}

//******************************************************************************

bool BaseControl::SaveAndValidateValue(
                                      const DString &strValueIn,
                                      bool bFormatted,
                                      int index,
                                      bool &bClearErrorState,
                                      bool &bDataChanged
                                      )
{
// TODO - should use a semaphore or something guaranteed to get reset??
   _bSaveAndValidateValue = true;

   SEVERITY sevRtn = NO_CONDITION;
   DString str( strValueIn );

   // Start as no change
   bDataChanged = false;

   // always strip trailing spaces
   str.stripTrailing();
   if( !( _flags & CTRLFLAG_NO_STRIP_LEADING_SPACE ) )
   {  // always strip leading here unless flag is set.
      str.stripLeading();
   }

   DString oldValue = _oldValuesOut[index];  // Temporary so can see what's there
   if( _oldValuesOut[index] != str || !IsValid() )
   {
      // setup updated flag in the dlg
      _rpParentDlg->setUpdateFlag( true );

      // Something changed or was invalid before, so need to update
      _oldValuesIn[index] = I_( "XYXY" );  // Bogus value so load will be forced
      bDataChanged = true;
      if( bClearErrorState )
      {  // First change encountered, clear error state & turn flag off
         ClearErrorState();
         bClearErrorState = false;
      }
      SetValid( false );
      if( !_rpParentDlg->SetDataFromControl( _uiControlID, str,
                                             bFormatted, sevRtn, index ) )
      {  // No override provided - do default processing
         if( IsGUIField() )
         {  // Should have been handled in SetDataFromControl
            assert( 0 );
            _bSaveAndValidateValue = false;
            throw;
         }
         sevRtn = _rpParentProcess->setField( _rpParentDlg, idContainer_,
                                              _fieldIDs[index], str, bFormatted ) ;
      }

// TODO - Do error processing here...
      AccumulateErrorState( sevRtn );
      // We have updated, possibly with invalid value
      SetUpdated( true );

      ControlUpdated( str, bFormatted, index );
   }

   _bSaveAndValidateValue = false;
   return(IsValid());
}

//******************************************************************************
//  Private methods
//******************************************************************************

void BaseControl::CheckFlags()
{  // Set up flags based on - flags and BFProperties
   // Set up updateable state - can only update if both GUI and BFProperties
   // say so
   SetUpdateable( false );
   if( IsControlUpdateable() && IsGUIUpdateable() )
   {  // GUI says updateable
      if( ( GetProperties() && !GetProperties()->isReadOnly() )
          || ( !GetProperties() && ( IsGUIField() || idContainer_ == BF::NullContainerId ) ) )
      {  // Either CBO says updateable, GUI handling or someone else handling??
         SetUpdateable( true );
      }
   }
}

//******************************************************************************

void BaseControl::CheckForInit(
                              bool bForceControlInit
                              )
{
   SetInitialLoad( true );   // Force the load
   bool bPropertiesChanged = false;
   //if ( IsControlUpdateable() && IsGUIUpdateable() && !IsGUIField() )
   {  // Only need properties for updateable controls
      for( int i = 0; i < _fieldIDs.size(); i++ )
      {  // for all field ids
         if( _fieldIDs[i] != ifds::NullFieldId )
         {
            //const BFProperties *rpProp = _rpParentProcess->getFieldAttributes(
            //_rpParentDlg, GetContainerID(), id );
            const BFProperties *pOldProp = _properties[i];
            if( GetProperties(i) != pOldProp )
               bPropertiesChanged = true;
         }
      }
   }

   if( IsFirstTimeInit() || bPropertiesChanged || IsGUIField() 
       || bForceControlInit )
   {  // Give control chance to respond to properties change - GUI_FIELDS
      // Always get an init currently
      SetFirstTimeInit( false );
      CheckFlags();
      DoInit();
      if( _flags & CTRLFLAG_MANUAL_INIT )
      {  // Let parent init
         GetParentDlg()->InitControl( GetControlID() );
      }
   };

   if( !_bDuringNotify && !IsGUIField() )
   {  // Currently attempting to register as an observer for all non-GUI
      // controls
      if( IsRegistered() )
      {
// TODO Make sure that if we come back from rollback (reset) we are forcing everyone to
// reget properties/register observers.
// TODO - we are currently only registering observer for primary (first) field, depending
//  on needs this may need to change
         deRegisterObserver( );
      }
      if( _rpParentProcess->registerObserver( _rpParentDlg, GetContainerID(),
                                              GetFieldID(), _rpParentProcess->getDataGroupId(), *this ) )
      {
         setRegistered( true );
      }
   }
}

//******************************************************************************

void BaseControl::ClearContainers()
{
   _fieldIDs.clear();
   _oldValuesIn.clear();
   _oldValuesOut.clear();
   _properties.clear();
   SetUpdateable( true );
   SetFirstTimeInit( true );
   ClearForDataConnect();
}

//******************************************************************************

void BaseControl::ClearForDataConnect()
{
   ClearErrorState();
   SetValid( false );
}

//******************************************************************************

void BaseControl::ControlUpdated(
                                DString &str,
                                bool bFormatted,
                                int index
                                )
{
   // Make sure we have latest value - this is where we should set _oldValuesOut
   // since this is affected by both load and store.  Only setting _oldValuesOut
   // in store will ignore values from initial load.
   _oldValuesOut[index] = str;
   if( bFormatted )
   {  // Get unformatted value to pass to dialog
      if( !_rpParentDlg->GetDataForControl( _uiControlID, str, false, 0 ) )
      {
         _rpParentProcess->getField( _rpParentDlg, idContainer_, _fieldIDs[0],
                                     str, false );
      }
   }
   // Tell parent the control has been updated & hand them unformatted data
   _rpParentDlg->ControlUpdated( _uiControlID, str );
}

//******************************************************************************

DSTMsg *BaseControl::GetToolTip()
{
   if( _pToolTip == NULL )
   {
      _pToolTip = new DSTMsg( GetWindow() );
   }
   return(_pToolTip);
}

//******************************************************************************

CWnd *BaseControl::GetWindow()
{
   CWnd *wnd = _rpParentDlg->GetDlgItem( _uiControlID );

   if( !wnd )
   {  // bad
      assert( 0 );
// TODO - set condition
      throw;
   }
   return(wnd);
}

//******************************************************************************

void BaseControl::SetDataConnected(
                                  bool bFlag
                                  )
{
   _bDataConnected = bFlag;
   if( !bFlag )
   {  // Don't allow disconnected controls to be enabled ( but don't affect
      // Programmer set Enabled flag
      GetWindow()->EnableWindow( false );
      Clear();
   }
   else
   {
      GetWindow()->EnableWindow( IsEnabled() );
   }
}

//******************************************************************************

void BaseControl::ShowToolTip()
{
   if( IsError() )
   {
      if( !IsGUIField() )
      {  // Currently don't support errors on GUI fields
         GetParentProcess()->getErrors( GetParentDlg(), GetContainerID(),
                                        GetFieldID(), _conditions );
         GetToolTip()->SetMessageFromConditions( _conditions );
         GetToolTip()->ShowMsg( true, false );		 
      }
   }
   else if( ToolTipExists() )
   {  // Hide tooltip, if showing - error went away
      GetToolTip()->ShowMsg( false );
      DestroyToolTip();
   }
}

//******************************************************************************

void BaseControl::HideToolTip()
{
   if( IsToolTipVisible() )
   {  // Hide tooltip, if showing - error went away
      GetToolTip()->ShowMsg( false );
      DestroyToolTip();
   }
}

//******************************************************************************

void BaseControl::DestroyToolTip(void)
{
   DSTMsg *pTooltip = dynamic_cast<DSTMsg *>(GetToolTip());
   
   if(pTooltip)
   {
      delete _pToolTip;
      _pToolTip = NULL;   
   }
}

//******************************************************************************

void BaseControl::SetCtrlReadOnly(bool bReadOnly /*= true*/)
{
   if( _flags & CTRLFLAG_NOT_UPDATABLE )
      bReadOnly = true;
   if( IsUpdateable() == !bReadOnly ) return;//no change; don't do anything
   if( !IsConnected() ) return;//we don't connect/disconnect controls using this method
   SetUpdateable(!bReadOnly);
   if( !doSetCtrlReadOnly(bReadOnly) )
   {//if not handled by the derived class, here is the default implementation
      if( !bReadOnly )
      {
         if( GetFlags() & CTRLFLAG_MANUAL_INIT )
         {  // Let parent init
            GetParentDlg()->InitControl( GetControlID() );
         }
         else
            DoInit();
      }
      SetInitialLoad(true);
      Load(false);
   }
}
//******************************************************************************

const BFProperties * BaseControl::GetProperties(int index /*=0*/)
{
   const BFProperties *pNewProp = NULL;

   if( IsControlUpdateable() && IsGUIUpdateable() && !IsGUIField() )
      pNewProp = _rpParentProcess->getFieldAttributes(_rpParentDlg, idContainer_, _fieldIDs[index] );
   else if( IsGUIField() )
      pNewProp = _rpParentDlg->getGuiFieldProperties(_uiControlID, _fieldIDs[index]);
   else
      _properties[index] = NULL;

   if( _properties[index] != pNewProp )
      _properties[index] = const_cast<BFProperties *>(pNewProp);
   return(_properties[index]);

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/basecontrol.cpp-arc  $
//
//   Rev 1.33   May 22 2012 17:41:08   dchatcha
//IN#2957144 - P0186486FN15 - Source of Fund issues on RRIF screen, issue#2 - destroy tool tips when no need to display every time, to fix display issue, additional places to call to free up tool tip box.
//
//   Rev 1.32   May 22 2012 13:44:34   dchatcha
//IN#2957144 - P0186486FN15 - Source of Fund issues on RRIF screen, issue#2 - destroy tool tips when no need to display every time, to fix display issue
//
//   Rev 1.31   Sep 14 2005 10:57:50   popescu
//Incident# 403519 - dialog resize, added some comments
//
//   Rev 1.30   Sep 07 2005 11:11:00   fengyong
//Add scroll and resize feature to dialogs
//
//   Rev 1.29   Sep 27 2004 09:31:46   FENGYONG
//PTS10024458 - do not check visible before show error message
//
//   Rev 1.28   Mar 25 2004 13:52:48   popescu
//PET 1027, FN02, high risk entities, fix tab control issues related to validation of the controls attached to a page, and hide/display the error icon on the tab when focus is lost on a control; also add method to set the selection programatically.
 * 
 *    Rev 1.27   Jan 14 2003 11:05:10   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.26   Jan 06 2003 16:45:48   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.25   Oct 09 2002 17:42:34   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.24   Sep 19 2002 12:05:10   PURDYECH
 * BFFieldId has lost its operator long() method, so BFFieldId can no longer be compared to ints.  Code was changed to reflect this.
 * 
 *    Rev 1.23   Sep 10 2002 14:34:26   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.22   Aug 29 2002 12:57:32   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.21   May 28 2002 12:21:20   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.20   22 May 2002 19:17:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.19   14 Mar 2002 10:33:52   KOVACSRO
 * DoGetText() might fail (should return a bool !); if it failed, don't changed the old value into a NULL_STRING. (PTS 10006915 related)
 * 
 *    Rev 1.18   04 Jul 2001 16:46:16   YINGZ
 * implement cancel to give user warning when there are updates
 * 
 *    Rev 1.17   Jun 26 2001 19:01:56   PURDYECH
 * More Infrastructure Release 1.9 Integration stuff.
 * 
 *    Rev 1.16   07 Jun 2001 09:36:14   KOVACSRO
 * Changed the way GetProperties() work (because refresh doesn't notify the control, we're refreshing all the time the properties)
 * 
 *    Rev 1.15   Jun 01 2001 11:25:52   DINACORN
 * Show icon for non updatable controls before click OK
 * 
 *    Rev 1.14   30 May 2001 14:18:00   KOVACSRO
 * fix for not updateable controls.
 * 
 *    Rev 1.13   30 May 2001 12:23:28   KOVACSRO
 * When loading a control set it invalid if value is NULL_STRING only for GUIField; for regular controls, validation is done by BFBase anyway.
 * 
 *    Rev 1.12   May 29 2001 15:52:16   YINGBAOL
 * sync up version 1.10.1.0
 * 
 *    Rev 1.11   16 May 2001 14:32:06   YINGZ
 * show icon for non updatable control and code sync
 * 
 *    Rev 1.10   11 May 2001 11:02:02   YINGZ
 * show err icon for disabled control
 * 
 *    Rev 1.9   24 Apr 2001 11:15:10   KOVACSRO
 * checking flags in SetCtrlReadOnly.
 * 
 *    Rev 1.8   Apr 06 2001 12:07:02   YINGZ
 * make changes to datagroup
 * 
 *    Rev 1.7   03 Apr 2001 14:25:00   KOVACSRO
 * permission check.
 * 
 *    Rev 1.7   03 Apr 2001 11:49:26   KOVACSRO
 * Modified SetCtrlReadOnly().
 * 
 *    Rev 1.6   30 Mar 2001 12:17:04   KOVACSRO
 * Default implem. for SetCtrlReadOnly().
 * 
 *    Rev 1.5   Dec 19 2000 16:15:52   HUANGSHA
 * Added HideToolTip()
 * 
 *    Rev 1.4   Oct 13 2000 16:27:18   YINGBAOL
 * fix for multiline control
 * 
 *    Rev 1.3   Jun 13 2000 18:01:02   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.2   Mar 01 2000 17:19:48   BUZILA
 * changing the selection in a list control should reregister attached controls
 * 
 *    Rev 1.1   Feb 22 2000 13:15:12   DT24433
 * don't try to get properties for GUI fields
 * 
 *    Rev 1.0   Feb 15 2000 11:01:38   SMITHDAV
 * Initial revision.
// 
//    Rev 1.48   Jan 21 2000 09:54:32   DT24433
// hide tooltips when control is hidden
// 
//    Rev 1.47   Jan 20 2000 14:50:40   DT24433
// changed to use _bLoadDisplayFormat for getting & setting data to/from control
// 
//    Rev 1.46   Jan 19 2000 10:12:06   BUZILA
// refresh stuf
// 
//    Rev 1.45   Jan 18 2000 16:45:04   DT24433
// hide error icon when control is hidden & fixed load/store interaction
// 
//    Rev 1.44   Jan 18 2000 14:37:52   DT24433
// added fix to clear oldValuesIn when setting a new value
// 
//    Rev 1.43   Jan 14 2000 15:33:22   YINGZ
// fix sub list order problem
// 
//    Rev 1.42   Jan 13 2000 17:09:30   DT24433
// changed LoadErrorState
// 
//    Rev 1.41   Jan 11 2000 17:29:20   DT24433
// change to not save if CancelInProgress, register observers for all non-GUI controls
// 
//    Rev 1.40   Jan 06 2000 12:11:50   DT24433
// changed to always do cross-edit check even if data didn't change
// 
//    Rev 1.39   Jan 05 2000 18:03:42   DT24433
// added cross-edit calls
// 
//    Rev 1.38   Jan 04 2000 17:58:06   DT24433
// get fields for multi-field controls directly from datadictionary
// 
//    Rev 1.37   Jan 04 2000 12:41:02   DT24433
// don't register observer during notification
// 
//    Rev 1.36   Dec 31 1999 14:11:36   DT24433
// notification changes
// 
//    Rev 1.35   Dec 29 1999 11:54:16   DT24433
// fixed display bug (missing data) for Load initiated by SetText
// 
//    Rev 1.34   Dec 24 1999 11:05:22   DT24433
// fix for load of multi-field controls
// 
//    Rev 1.33   Dec 22 1999 16:42:56   DT24433
// prevent some load operations if value is unchanged
// 
//    Rev 1.32   Dec 22 1999 13:15:18   DT24433
// don't load during store/settext if no changes, and notification changes
// 
//    Rev 1.31   Dec 21 1999 12:34:18   YINGZ
// change icon size
// 
//    Rev 1.30   Dec 09 1999 18:42:12   DT24433
// added show/hide to ConnectControl(s)ToData
// 
//    Rev 1.29   Dec 09 1999 13:15:38   DT24433
// fix for GUI fields with field ID of 0
// 
//    Rev 1.28   Dec 08 1999 16:24:02   DT24433
// moved common ControlUpdated code to method and call GetDataForControl
// 
//    Rev 1.27   Dec 06 1999 17:31:06   DT24433
// setValid( false ) for empty, required fields - also changed DoClear to Clear in setDataConnected
// 
//    Rev 1.26   Nov 23 1999 16:40:28   DT24433
// used IsGUIField
// 
//    Rev 1.25   Nov 23 1999 11:56:10   YINGZ
// add checking in ConnectToData
// 
//    Rev 1.24   Nov 22 1999 10:29:16   DT24433
// only create new icon when change
// 
//    Rev 1.23   Nov 19 1999 17:36:42   DT24433
// better error support
// 
//    Rev 1.22   Nov 17 1999 12:53:18   DT24433
// more control changes
// 
//    Rev 1.21   Nov 15 1999 14:00:32   DT24433
// changed to pass control flags in init
// 
//    Rev 1.20   Nov 12 1999 13:16:44   DT24433
// misc
// 
//    Rev 1.19   Nov 11 1999 10:51:56   DT24433
// added DoChangeUpdate and flag GUI_FIELD
// 
//    Rev 1.18   Nov 11 1999 09:06:06   DT24433
// more flag/property support
// 
//    Rev 1.17   Nov 09 1999 17:20:26   DT24433
// flag changes
// 
//    Rev 1.16   Nov 05 1999 15:32:20   DT24433
// added initial condition handling
// 
//    Rev 1.15   Nov 05 1999 11:23:00   YINGZ
// add CTRLFLAG_NOT_UPDATABLE flag
// 
//    Rev 1.14   Nov 05 1999 10:36:30   YINGZ
// add setflag
// 
//    Rev 1.13   Nov 04 1999 15:31:12   YINGZ
// Add CTRLFLAG_STRIP_LEADING_SPACE flag
// 
//    Rev 1.12   Nov 04 1999 11:32:06   DT24433
// implemented IsValid
// 
//    Rev 1.11   Nov 04 1999 07:51:24   DT24433
// added proper handling of ClearErrorState
// 
//    Rev 1.10   Nov 03 1999 15:08:34   DT24433
// more multi-field and new flags
// 
//    Rev 1.9   Nov 02 1999 17:25:52   YINGZ
// add index
// 
//    Rev 1.8   Oct 28 1999 09:35:12   YINGZ
// for a clean Get from PVCS!
// 
//    Rev 1.7   Oct 27 1999 09:58:00   YINGZ
// add controlupdate
// 
//    Rev 1.6   Oct 19 1999 09:28:48   YINGZ
// set icon position
// 
//    Rev 1.5   Oct 18 1999 17:55:06   DT24433
// commented out test code
// 
//    Rev 1.4   Oct 18 1999 16:38:40   DT24433
// misc. changes
// 
//    Rev 1.3   Oct 14 1999 15:39:44   DT24433
// provide interface to tooltip so derived classes don't access directly and use lazy initialization for tooltip
// 
//    Rev 1.2   Oct 14 1999 13:51:08   YINGZ
// add tooltip support
// 
//    Rev 1.1   Oct 14 1999 10:13:20   DT24433
// added new methods
 * 
 *    Rev 1.0   Oct 04 1999 16:36:02   DT24433
 * First check in
 * 
 */
