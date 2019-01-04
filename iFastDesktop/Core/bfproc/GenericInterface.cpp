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
// ^FILE   : GenericInterface.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 12/01/1998
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : GenericInterface
//    This class sets the generic interface used by other classes.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "bpglobal.h"
#include "genericinterface.hpp"
#include <bfcbo\bfproperties.hpp>
#include "commanddispatcher.hpp"

#include <bfsessn\bfcpsession.hpp>

#include <bfdata\bfdata.hpp>
#include <bfdata\bfdatafieldproperties.hpp>

#include "genericinterfacecontainer.hpp"
#include "interprocessdata.hpp"
#include <bfcbo\bfsession.hpp>
#include <bfcbo\bfworksession.hpp>
#include <bfcbo\bfusersession.hpp>
#include "bfcontainerid.hpp"
#include <assert.h>
#include <bfutil/seh_exception.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "GenericInterface" );

   const I_CHAR * const CANCEL                = I_( "cancel" );
   const I_CHAR * const CLEARGLOBALS          = I_( "clearGlobals" );
   const I_CHAR * const CLEARPARAMETERS       = I_( "clearParameters" );
   const I_CHAR * const DOMORERECORDSEXIST    = I_( "doMoreRecordsExist" );
   const I_CHAR * const GETDATA               = I_( "getData" );
   const I_CHAR * const GETGLOBAL             = I_( "getGlobal" );
   const I_CHAR * const GETPARAMETER          = I_( "getParameter" );
   const I_CHAR * const INIT                  = I_( "init" );
   const I_CHAR * const MODELESSCHILDCOMPLETE = I_( "modelessChildComplete" ); 
   const I_CHAR * const MODELESSSETFOCUS      = I_( "modelessSetFocus" ); 
   const I_CHAR * const OK                    = I_( "ok" );
   const I_CHAR * const PERFORMSEARCH         = I_( "performSearch" );
   const I_CHAR * const REFRESH               = I_( "refresh" );
   const I_CHAR * const SEND                  = I_( "send" );
   const I_CHAR * const SETGLOBAL             = I_( "setGlobal" );
   const I_CHAR * const SETPARAMETER          = I_( "setParameter" );
   const I_CHAR * const RESETCURRENTITEM             = I_( "resetCurrentItem" );
}

namespace CND
{  // Conditions used
   extern const long BP_ERR_INVALID_METHOD_CALL;
   extern const long BP_ERR_NO_DATA_AREA;
   extern const long BP_ERR_SEH_EXCEPTION;
   extern const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace GENERICINTERFACELITERALS
{
   // Trace literals
   BPBASE_LINKAGE const I_CHAR *DELETEITEMFROMLIST = I_( "deleteItemFromList" );
   BPBASE_LINKAGE const I_CHAR *DEREGISTEROBSERVER = I_( "deregisterObserver" );
   BPBASE_LINKAGE const I_CHAR *DOGETDATA = I_( "doGetData" );
   BPBASE_LINKAGE const I_CHAR *DOGETERRORS = I_( "doGetErrors" );
   BPBASE_LINKAGE const I_CHAR *DOGETFIELD = I_( "doGetField" );
   BPBASE_LINKAGE const I_CHAR *DOGETFIELDATTRIBUTES = I_( "doGetFieldAttributes" );
   BPBASE_LINKAGE const I_CHAR *DOCANCEL = I_( "doCancel" );
   BPBASE_LINKAGE const I_CHAR *DOINIT = I_( "doInit" );
   BPBASE_LINKAGE const I_CHAR *DOMODELESSCHILDCOMPLETE = 
   I_( "doModelessChildComplete" );
   BPBASE_LINKAGE const I_CHAR *DOMODELESSSETFOCUS = I_( "doModelessSetFocus" );
   BPBASE_LINKAGE const I_CHAR *DOOK = I_( "doOk" );
   BPBASE_LINKAGE const I_CHAR *DOPROCESS = I_( "doProcess" );
   BPBASE_LINKAGE const I_CHAR *DOREFRESH = I_( "doRefresh" );
   BPBASE_LINKAGE const I_CHAR *DOSEND = I_( "doSend" );
   BPBASE_LINKAGE const I_CHAR *DOSETFIELD = I_( "doSetField" );
   BPBASE_LINKAGE const I_CHAR *GETCURRENTLISTITEMKEY  = I_( "getCurrentListItemKey" );
   BPBASE_LINKAGE const I_CHAR *GETALLERRORS = I_( "getAllErrors" );
   BPBASE_LINKAGE const I_CHAR *GETERRORS = I_( "getErrors" );
   BPBASE_LINKAGE const I_CHAR *GETERRORSTATE = I_( "getErrorState" );
   BPBASE_LINKAGE const I_CHAR *GETFIELD = I_( "getField" );
   BPBASE_LINKAGE const I_CHAR *GETFIELD2 = I_( "getField2" );
   BPBASE_LINKAGE const I_CHAR *GETFIELDATTRIBUTES = I_( "getFieldAttributes" );
   BPBASE_LINKAGE const I_CHAR *GETFIRSTLISTITEMKEY    = I_( "getFirstListItemKey" );
   BPBASE_LINKAGE const I_CHAR *GETKEYFORNEWLISTITEM   = I_( "getKeyForNewListItem" );
   BPBASE_LINKAGE const I_CHAR *GETNEXTLISTITEMKEY     = I_( "getNextListItemKey" );
   BPBASE_LINKAGE const I_CHAR *GETNUMBEROFITEMSINLIST = I_( "getNumberOfItemsInList" );
   BPBASE_LINKAGE const I_CHAR *INIT2 = I_( "init2" );
   BPBASE_LINKAGE const I_CHAR *OK2 = I_( "ok2" );
   BPBASE_LINKAGE const I_CHAR *PROCESS = I_( "process" );
   BPBASE_LINKAGE const I_CHAR *REGISTEROBSERVER = I_( "registerObserver" );
   BPBASE_LINKAGE const I_CHAR *RESET = I_( "reset" );
   BPBASE_LINKAGE const I_CHAR *SETCURRENTLISTITEM = I_( "setCurrentListItem" );
   BPBASE_LINKAGE const I_CHAR *SETDATA = I_( "setData" );
   BPBASE_LINKAGE const I_CHAR *SETFIELD = I_( "setField" );
   BPBASE_LINKAGE const I_CHAR *SETFIELD2 = I_( "setField2" );
   BPBASE_LINKAGE const I_CHAR *DOVALIDATEALL = I_( "doValidateAll" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************

GenericInterface::GenericInterface( GenericInterfaceContainer *rpGIC,
                                    GenericInterface *rpGIParent,
                                    const Command &cmd) 
: _bOwnsSession( false )
, _bProcessHasRun( false )
, _bXMLAPIContext( false )
, cmd_( cmd )
, idDataGroup_( BF::HOST )
, _rpGIParent( rpGIParent )
, _rpGIContainer( rpGIC )
, _rpGIWorkSession( NULL )
, _pSession( NULL )
, _bfSession( NULL )
, _procObserver(NULL)
{
   EXECHIST2( I_("GenericInterface"), 
              I_( "GenericInterface( GenericInterfaceContainer *, GenericInterface *, const Command & )" ) );

   assert( _rpGIContainer != NULL );
   if( NULL != _rpGIParent )
   {
      _pSession = _rpGIParent->getSession();
      _bfSession = _rpGIParent->getBFSession();
      _rpGIWorkSession = _rpGIParent->getWorkSession();
      _bXMLAPIContext = _rpGIParent->isXMLAPIContext();
      _procObserver = _rpGIParent->getProcessObserver();
   }
}

GenericInterface::GenericInterface() 
: _bOwnsSession( false )
, _bProcessHasRun( false )
, _bXMLAPIContext( false )
, idDataGroup_( BF::HOST )
, _rpGIParent( NULL )
, _rpGIContainer( NULL )
, _rpGIWorkSession( NULL )
, _pSession( NULL )
, _bfSession( NULL )
{
   EXECHIST2( I_("GenericInterface"), 
              I_( "GenericInterface(  )" ) );

}

//******************************************************************************
GenericInterface::~GenericInterface()
{
   EXECHIST2( I_("GenericInterface"), 
              I_( "~GenericInterface(  )" ) );

   _rpGIParent = NULL;
   _rpGIWorkSession = NULL;
   if( _bOwnsSession )
   {
      delete _pSession;
   }
   _pSession = NULL;
}

//******************************************************************************
bool GenericInterface::cancel( GenericInterface *rpGICaller )
{
   EXECHISTI( I_( "cancel( GenericInterface * )" ) );

   bool bRtn = false;

   try
   {
      assert( _bProcessHasRun );   // process should always run first
      SEVERITY sevRtn = cancel2( rpGICaller );
      if( sevRtn <= WARNING )
      {
         bRtn = true;
      }
      if( !isModal() )
      {  // User responsible for clearing if modal
         clearParameters();
      }
   }
   catch( ConditionException& )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, CANCEL, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, CANCEL, CND::BP_ERR_UNKNOWN_EXCEPTION ); 
   }
   return(bRtn);
}

//******************************************************************************
BFSession *GenericInterface::getBFSession() const
{
   if( NULL ==_bfSession )
   {
      // TODO: throw something...
      assert(0);
      throw;
   }

   return(_bfSession);
}

//******************************************************************************
BFWorkSession *GenericInterface::getBFWorkSession() const
{
   if( NULL !=_bfSession && _bfSession->isBFWorkSession() )
   {
      return(dynamic_cast<BFWorkSession *>(_bfSession));
   }
   else
   {
      // TODO: throw something...
      assert(0);
      throw;
   }
}

//******************************************************************************

void GenericInterface::clearGlobals( E_GLOBALTYPE gType )
{
   TRACE_METHOD( CLASSNAME, CLEARGLOBALS );

   BFSession* session = getBFSession();
   if ( gType == WORK_GLOBAL && session->isBFWorkSession() ) {
      session->getTempData().clear();
   } else if ( gType == USER_GLOBAL ) {
      session->getUserSession().getTempData().clear();
   } else {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, CLEARGLOBALS, CND::BP_ERR_NO_DATA_AREA );
   }

}

//******************************************************************************

void GenericInterface::clearParameters()
{
   TRACE_METHOD( CLASSNAME, CLEARPARAMETERS );

   if ( _rpGIContainer!=NULL ) {
      _rpGIContainer->getInterProcessData().clearParameters();
   }
}

//******************************************************************************

void GenericInterface::deregisterObserver( const GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer,
                                           const BFFieldId &idField,
                                           const BFDataGroupId& idDataGroup,
                                           BFObserver &rpObserver )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DEREGISTEROBSERVER, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

bool GenericInterface::doMoreRecordsExist( GenericInterface *rpGICaller,
                                           const BFContainerId& idSearch )
{
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMORERECORDSEXIST, CND::BP_ERR_INVALID_METHOD_CALL );
   return(false);
}

//******************************************************************************

bool GenericInterface::getData( GenericInterface *rpGICaller,
                                BFData *rpData ) const
{
   EXECHISTI( I_( "getData( GenericInterface *, BFData * )" ) );

   bool bRtn = false;

   try
   {
      assert( _bProcessHasRun );   // process should always run first
      bRtn = doGetData( rpGICaller, rpData );
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETDATA, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETDATA, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************
SEVERITY GenericInterface::getAllErrors( GenericInterface *rpGICaller,
                                         CONDITIONVECTOR &conditions )
{
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETALLERRORS, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************
SEVERITY GenericInterface::getErrors( GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId &idField,
                                      CONDITIONVECTOR &conditions )
{
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETERRORS, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************
SEVERITY GenericInterface::getItemErrors( GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const DString* pKey,
                                          const BFFieldId &idField,
                                          CONDITIONVECTOR &conditions )
{
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "GetItemErrors" ), CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************
void GenericInterface::getErrorState( GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      bool bCurrentItem,
                                      SEVERITY &eObjectSeverity,
                                      SEVERITY &eChildSeverity )
{
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETERRORSTATE, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************
void GenericInterface::getItemErrorState( GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const DString* pKey,
                                          SEVERITY &eObjectSeverity,
                                          SEVERITY &eChildSeverity )
{
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "GetItemErrorState" ), CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************
void GenericInterface::getField( const GenericInterface *rpGICaller,
                                 const BFFieldId &idField,
                                 DString &strValueOut,
                                 bool bFormatted )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

void GenericInterface::getField( const GenericInterface *rpGICaller,
                                 const BFContainerId& idContainer,
                                 const BFFieldId &idField,
                                 DString &strValueOut,
                                 bool bFormatted )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD2, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************
// TODO - soon to be removed
const BFDataFieldProperties* GenericInterface::getFieldAttributes( const GenericInterface *rpGICaller,
                                                                   const BFFieldId &idField ) const
{  // TODO - If CBO can change attributes, then what?
   const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
   return(pProps);
}

//******************************************************************************

const BFProperties *GenericInterface::getFieldAttributes( const GenericInterface *rpGICaller,
                                                          const BFContainerId& idContainer,
                                                          const BFFieldId &idField )
{
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELDATTRIBUTES, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

void GenericInterface::getGlobal( E_GLOBALTYPE gType,
                                  const BFFieldId &idField,
                                  DString &strValueOut ) const
{
   EXECHISTI( I_( "getGlobal( E_GLOBALTYPE, const BFFieldId &, DString & )" ) );


   BFSession* session = getBFSession();
   if ( gType == WORK_GLOBAL && session->isBFWorkSession() ) {
      session->getTempData().getField( idField, strValueOut );
   } else if ( gType == USER_GLOBAL ) {
      session->getUserSession().getTempData().getField( idField, strValueOut );
   } else {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETGLOBAL, CND::BP_ERR_NO_DATA_AREA );
   }

}

//******************************************************************************

void GenericInterface::getParameter( const DString &strTag,
                                     DString &strValueOut ) const
{
   TRACE_METHOD( CLASSNAME, GETPARAMETER );

   if ( _rpGIContainer!=NULL ) {
      _rpGIContainer->getInterProcessData().getParameter( strTag, strValueOut );
   }
}

//******************************************************************************
bool GenericInterface::hasCreatePermission( const I_CHAR *userAccessFunctionCode ) const
{
   return(getBFWorkSession()->hasCreatePermission( userAccessFunctionCode ));
}

//******************************************************************************

bool GenericInterface::hasReadPermission( const I_CHAR *userAccessFunctionCode ) const
{
   return(getBFWorkSession()->hasReadPermission( userAccessFunctionCode ));
}

//******************************************************************************

bool GenericInterface::hasUpdatePermission( const I_CHAR *userAccessFunctionCode ) const
{
   return(getBFWorkSession()->hasUpdatePermission( userAccessFunctionCode ));
}

//******************************************************************************

bool GenericInterface::hasDeletePermission( const I_CHAR *userAccessFunctionCode ) const
{
   return(getBFWorkSession()->hasDeletePermission( userAccessFunctionCode ));
}

//******************************************************************************

SEVERITY GenericInterface::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, INIT ); // TODO - ??? Why not trace method
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      sevRtn = init2();
      clearParameters();     // Parameters are gone now
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, INIT, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, INIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return( sevRtn );
}

//******************************************************************************

void GenericInterface::modelessChildComplete( const Command &cmd )
{
   EXECHISTI( I_( "modelessChildComplete( const Command & )" ) );


   try
   {
      if( _bProcessHasRun && !isModal() )
      {  // Must have run process and must be modeless
         if( _rpGIContainer!=NULL && doModelessChildComplete( cmd ) )
         {  // Everything complete, destroy self
            _rpGIContainer->modelessDestroySelf( this );
         }
      }
      else
      {
         assert( 0 );   // Why call if haven't called process or modal?
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, MODELESSCHILDCOMPLETE, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, MODELESSCHILDCOMPLETE, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

bool GenericInterface::modelessSetFocus( GenericInterface *rpGICaller )
{
   EXECHISTI( I_( "modelessSetFocus( GenericInterface * )" ) );

   bool bRtn = false;

   try
   {
      assert( _bProcessHasRun );   // process should always run first
      if( isModal() )
      {  // Can only be modeless
         assert( 0 );
      }
      else
      {
         bRtn = doModelessSetFocus( rpGICaller );
      }
      clearParameters();     // Parameters are gone now
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, MODELESSSETFOCUS, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, MODELESSSETFOCUS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************

bool GenericInterface::ok( GenericInterface *rpGICaller )
{
// TODO - change to return type SEVERITY
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, OK ); // TODO - ??? Why not trace method
   bool bRtn = false;

   try
   {
      assert( _bProcessHasRun );   // process should always run first
      SEVERITY sevRtn = ok2( rpGICaller );
      if( sevRtn <= WARNING )
      {
         bRtn = true;
      }
      if( !isModal() )
      {  // User responsible for clearing if modal
         clearParameters();     // Parameters are gone now
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, OK, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, OK, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************

SEVERITY GenericInterface::performSearch( GenericInterface *rpGICaller,
                                          const BFContainerId& idSearch,
                                          E_SEARCHACTION eSearchAction )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_INVALID_METHOD_CALL );
   return(SEVERE_ERROR);
}

//******************************************************************************

bool GenericInterface::refresh( GenericInterface *rpGICaller,
                                const I_CHAR *szOriginalCommand )
{
   EXECHISTI( I_( "refresh( GenericInterface *, const I_CHAR * )" ) );

   bool bRtn = false;

   try
   {
      assert( _bProcessHasRun );   // process should always run first
      bRtn = doRefresh( rpGICaller, szOriginalCommand );
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, REFRESH, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, REFRESH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************

bool GenericInterface::registerObserver( const GenericInterface *rpGICaller,
                                         const BFContainerId& idContainer,
                                         const BFFieldId &idField,
                                         const BFDataGroupId& idDataGroup,
                                         BFObserver &rpObserver )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, REGISTEROBSERVER, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

SEVERITY GenericInterface::reset( GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  bool bCurrentItem )
{  // Default processing is to fail
   assert( 0 );   
    ( CND::BPBASE_CONDITION, CLASSNAME, RESET, CND::BP_ERR_INVALID_METHOD_CALL );
   return(SEVERE_ERROR);
}

//******************************************************************************

SEVERITY GenericInterface::resetCurrentItem( const BFContainerId& idContainer )
{
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, RESETCURRENTITEM, CND::BP_ERR_INVALID_METHOD_CALL );
   return(SEVERE_ERROR);
}

//******************************************************************************

bool GenericInterface::send( GenericInterface *rpGICaller,
                             const I_CHAR *szMessage )
{
   EXECHISTI( I_( "send( GenericInterface *, const I_CHAR * )" ) );

   bool bRtn = false;

   try
   {
      assert( _bProcessHasRun );   // process should always run first
      bRtn = doSend( rpGICaller, szMessage );
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, SEND, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SEND, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************

SEVERITY GenericInterface::setData( GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFData *rpData )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETDATA, CND::BP_ERR_INVALID_METHOD_CALL );
   return(SEVERE_ERROR);
}

//******************************************************************************

SEVERITY GenericInterface::setField( const GenericInterface *rpGICaller,
                                     const BFFieldId &idField,
                                     const DString &strValue,
                                     bool bFormatted )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
   return(SEVERE_ERROR);
}

//******************************************************************************

SEVERITY GenericInterface::setField( const GenericInterface *rpGICaller,
                                     const BFContainerId& idContainer,
                                     const BFFieldId &idField,
                                     const DString &strValue,
                                     bool bFormatted )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD2, CND::BP_ERR_INVALID_METHOD_CALL );
   return(SEVERE_ERROR);
}

//******************************************************************************

void GenericInterface::setGlobal( E_GLOBALTYPE gType,
                                  const BFFieldId &idField,
                                  const DString &strValue )
{
   EXECHISTI( I_( "setGlobal( E_GLOBALTYPE, const BFFieldId &, const DString & )" ) );


   BFSession* session = getBFSession();
   if ( gType == WORK_GLOBAL && session->isBFWorkSession() ) {
      session->getTempData().setField( idField, strValue );
   } else if ( gType == USER_GLOBAL ) {
      session->getUserSession().getTempData().setField( idField, strValue );
   } else {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETGLOBAL, CND::BP_ERR_NO_DATA_AREA );
   }

}

//******************************************************************************

void GenericInterface::setParameter( const DString &strTag,
                                     const DString &strValue )
{
   if ( _rpGIContainer!=NULL ) {
      _rpGIContainer->getInterProcessData().setParameter( strTag, strValue );
   }
}

// ***************   List methods    *******************

//******************************************************************************

SEVERITY GenericInterface::deleteItemFromList( const GenericInterface *rpGICaller,
                                               const BFContainerId& idList )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DELETEITEMFROMLIST, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

const DString &GenericInterface::getCurrentListItemKey( const GenericInterface *rpGICaller,
                                                        const BFContainerId& idList )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETCURRENTLISTITEMKEY, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

const DString &GenericInterface::getFirstListItemKey( const GenericInterface *rpGICaller,
                                                      const BFContainerId& idList )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

const DString &GenericInterface::getKeyForNewListItem( const GenericInterface *rpGICaller,
                                                       const BFContainerId& idList )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETKEYFORNEWLISTITEM, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

const DString &GenericInterface::getNextListItemKey( const GenericInterface *rpGICaller,
                                                     const BFContainerId& idList )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

int GenericInterface::getNumberOfItemsInList( const GenericInterface *rpGICaller,
                                              const BFContainerId& idList )
{  // Default processing is to fail
   assert( 0 );   
   return(0);
}

//******************************************************************************

void GenericInterface::setCurrentListItem( const GenericInterface *rpGICaller,
                                           const BFContainerId& idList,
                                           const DString &strListItemKey )
{  // Default processing is to fail
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

E_COMMANDRETURN GenericInterface::invokeCommand( GenericInterface *rpGIParent,
                                                 const I_CHAR *szCommand,
                                                 E_PROCESSTYPE type,
                                                 bool bModal,
                                                 GenericInterface **rpGIModelessOut  /* NULL or pointer if active modeless */ )
{
   // Get instance is split out for easier debugging
   CommandDispatcher *rpDispatcher = CommandDispatcher::getInstance();
   return(rpDispatcher->invokeCommand( _rpGIContainer, rpGIParent, szCommand, type,
                                       bModal, rpGIModelessOut ));
}

//******************************************************************************

E_COMMANDRETURN GenericInterface::invokeCommand( const I_CHAR *szCommand,
                                                 E_PROCESSTYPE type,
                                                 bool bModal,
                                                 GenericInterface **rpGIModelessOut /* NULL or pointer if active modeless */ )
{  // This version uses work session for parent
   // Get instance is split out for easier debugging
   CommandDispatcher *rpDispatcher = CommandDispatcher::getInstance();
   return(rpDispatcher->invokeCommand( _rpGIContainer, _rpGIWorkSession, szCommand,
                                       type, bModal, rpGIModelessOut ));
}

//******************************************************************************

bool GenericInterface::isValidModelessInterface( GenericInterface *rpGI )
{
   if( !rpGI || !_rpGIContainer )
   {  // NULL pointer not allowed
      return(false);
   }
   return(_rpGIContainer->isValid( rpGI ));
}

//******************************************************************************

void GenericInterface::setDataGroupId( const BFDataGroupId& idDataGroup )
{
   idDataGroup_ = idDataGroup;
}

//******************************************************************************

void GenericInterface::setWorkSession( BFSession* bfSession,
                                       GenericInterface *rpGIWorkSession )
{
   _bfSession = bfSession;
   _rpGIWorkSession = rpGIWorkSession;
}

//******************************************************************************

bool GenericInterface::workSessionHasUpdates( )
{
   // should not come here
   assert( 0 );   
   return(false);
}

const DString& GenericInterface::getCommandName() const 
{
   return( cmd_.getName() );
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfproc/GenericInterface.cpp-arc  $
//
//   Rev 1.32   Feb 20 2009 14:48:40   purdyech
//ZTS Revision 6
//
//   Rev 1.31   May 14 2004 16:13:12   SMITHDAV
//Removed "global data areas" from InterProcessData" and cleaned up the related interfaces. They are now in the BFSession objects.
//
//   Rev 1.30   May 10 2004 15:08:58   SMITHDAV
//Move work-session level "global data" to the BFWorksession from InterProcessData.
//
//   Rev 1.29   Feb 12 2004 12:19:12   PURDYECH
//Catch SEH_Exceptions and throw them as BP_ERR_SEH_EXCEPTION conditions.
//
//   Rev 1.28   May 24 2003 14:56:46   PURDYECH
//Added getItemErrors and getItemErrorState
 * 
 *    Rev 1.27   Mar 20 2003 15:07:48   PURDYECH
 * performSearch and doMoreRecordsExist had bad method signatures.
 * 
 *    Rev 1.26   Feb 12 2003 14:08:38   PURDYECH
 * ServerContext code moved to BFUtil
 * 
 *    Rev 1.25   Jan 14 2003 11:04:22   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.24   Jan 06 2003 16:43:48   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.23   Oct 09 2002 17:40:56   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.22   Aug 29 2002 14:05:22   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.21   Aug 29 2002 12:51:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.20   May 28 2002 12:16:14   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.19   22 May 2002 17:57:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.18   27 Mar 2002 19:47:28   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.17   25 Oct 2001 14:02:42   SMITHDAV
 * hasPermission changes...
 * 
 *    Rev 1.16   26 Jul 2001 13:43:44   YINGZ
 * fix reset, cancel problems
 * 
 *    Rev 1.15   04 Jul 2001 15:16:28   YINGZ
 * cleanup
 * 
 *    Rev 1.14   29 Jun 2001 10:56:16   YINGZ
 * add canCancel to support cancel machenism
 * 
 *    Rev 1.13   14 Jun 2001 11:56:28   SMITHDAV
 * Re-worked user access list and permission checking code.
 * 
 *    Rev 1.12   03 May 2001 14:03:14   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.11   Mar 27 2001 13:57:24   YINGZ
 * add workSessionHasUpdates
 * 
 *    Rev 1.10   Feb 21 2001 11:32:04   YINGZ
 * add xmlapi context
 * 
 *    Rev 1.9   Nov 08 2000 12:19:00   DT24433
 * added server context flag
 * 
 *    Rev 1.8   Oct 26 2000 10:38:30   DT24433
 * Change to pass GIC instead of session
 * 
 *    Rev 1.7   16 Aug 2000 11:47:56   PURDYECH
 * Added getAllErrors method to retrieve all errors for the caller (both field level and object level).
 * 
 *    Rev 1.6   Aug 02 2000 15:31:34   BUZILA
 * "locale" changes
 * 
 *    Rev 1.5   Jun 23 2000 12:44:06   DT24433
 * changes to support setData
 * 
 *    Rev 1.4   Jun 13 2000 17:51:34   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.3   Apr 04 2000 15:45:10   DT24433
 * removed userID parm from findGI
 * 
 *    Rev 1.2   Apr 04 2000 14:37:00   DT24433
 * changed to store associated GIContainer and make available
 * 
 *    Rev 1.1   Mar 09 2000 10:54:26   DT24433
 * made haspermission virtual
 * 
 *    Rev 1.0   Feb 15 2000 10:57:36   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.24   Jan 28 2000 15:22:06   PRAGERYA
 * For release
 * 
 *    Rev 1.23   Jan 19 2000 15:15:40   DT24433
 * added getErrorState
 * 
 *    Rev 1.22   Jan 11 2000 11:25:06   DT24433
 * changed to return bool for registerObserver
 * 
 *    Rev 1.21   Jan 11 2000 11:24:02   PRAGERYA
 * Syntactic bug fixed
 * 
 *    Rev 1.20   Jan 06 2000 15:01:12   DT24433
 * changed to not clear parms during ok/cancel if modal
 * 
 *    Rev 1.19   Dec 22 1999 12:25:28   DT24433
 * parm changed in register/deregister
 * 
 *    Rev 1.18   Dec 21 1999 13:43:52   DT24433
 * initial notification changes
 * 
 *    Rev 1.17   Dec 16 1999 12:37:54   YINGZ
 * add hasPermission
 * 
 *    Rev 1.16   Nov 19 1999 17:30:42   DT24433
 * added new doxxx literals
 * 
 *    Rev 1.15   Nov 12 1999 17:11:42   DT24433
 * fixed good return on cancel
 * 
 *    Rev 1.14   Nov 11 1999 08:50:10   DT24433
 * changed getFieldAttributes interface
 * 
 *    Rev 1.13   Nov 05 1999 15:24:50   DT24433
 * added getErrors
 * 
 *    Rev 1.12   Oct 28 1999 16:44:36   DT24433
 * replaced doOk/doCancel with ok2/cancel2 since these will typically be overridden in another base class
 * 
 *    Rev 1.11   Oct 28 1999 13:48:22   VASILEAD
 * add/delete/reset & group processing
 * 
 *    Rev 1.10   Oct 25 1999 10:26:18   DT24433
 * changed return for getKeyForNewListItem
 * 
 *    Rev 1.9   Oct 25 1999 09:54:46   DT24433
 * changed interface for getKeyForNewListItem
 * 
 *    Rev 1.8   Sep 22 1999 13:19:50   VASILEAD
 * Added MAKEFRAMEAUTOPROMOTE2 for GI::doOk 
 * 
 *    Rev 1.7   Sep 01 1999 17:04:54   DT24433
 * clear parameters after cancel, modelessSetFocus and ok
 * 
 *    Rev 1.6   Aug 31 1999 16:20:22   DT24433
 * isValidModelessInterface checks for NULL now
 * 
 *    Rev 1.5   Aug 26 1999 16:36:16   DT24433
 * removed getFieldFromCurrentListItem
 * 
 *    Rev 1.4   Aug 03 1999 14:14:38   DT24433
 * container changes
 * 
 *    Rev 1.3   Jul 20 1999 11:14:04   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 16 1999 10:32:08   PRAGERYA
 * ahfd
 * 
 *    Rev 1.1   Jul 08 1999 10:02:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
