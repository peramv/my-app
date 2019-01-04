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
// ^FILE   : AbstractProcess.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 10/27/1998
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AbstractProcess
//    This class sets the interface for business process subclasses.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "bpglobal.h"
#include <bfutil\bfifds.hpp>
#include <bfcbo\bfdatagroupid.hpp>
#include "abstractprocess.hpp"
#include <bfcbo\bfabstractcbo.hpp>
#include <bfcbo\bfproperties.hpp>
#include "fielddetails.hpp"
#include "genericinterfacecontainer.hpp"
#include <idistring.hpp>
#include "listdetails.hpp"

#include <bfcbo\validationcontrol.hpp>

#include <bfsessn\bfcpsession.hpp>

#include "substitutelistdetails.hpp"
#include <bfcbo\bfusersession.hpp>
#include <bfcbo\bfworksession.hpp>

#include <bfcbo\bfcbo.hpp>
#include <bf/log/logstream.hpp>
#include <bfutil/seh_exception.hpp>

#include <assert.h>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME                     = I_( "AbstractProcess" );
   const I_CHAR * const ADDCONTAINER                  = I_( "addContainer" );
   const I_CHAR * const ADDFIELDDETAILS               = I_( "addFieldDetails" );
   const I_CHAR * const ADDSUBSTITUTELIST             = I_( "addSubstituteList" );
   const I_CHAR * const COMMIT                        = I_( "commit" );
   const I_CHAR * const COMMITANDCHECKTRANSACTION     = I_( "commitAndCheckTransaction" );
   const I_CHAR * const DOGETKEYFORNEWLISTITEM        = I_( "doGetKeyForNewListItem" );
   const I_CHAR * const FINDCONTAINER                 = I_( "findContainer" );
   const I_CHAR * const FINDFIELD                     = I_( "findField" );
   const I_CHAR * const FIRECROSSEDIT                 = I_( "fireCrossEdit" );
   const I_CHAR * const GETCONTAINERPTR               = I_( "getContainerPtr" );
   const I_CHAR * const GETCROSSEDITFIELDS            = I_( "getCrossEditFields" );
   const I_CHAR * const INVOKEPROCESSFROMCHILD        = I_( "invokeProcessFromChild" );
   const I_CHAR * const ISCURRENTLISTITEMNEW          = I_( "isCurrentItemNew" );
   const I_CHAR * const ISCURRENTLISTITEMDUMMY        = I_( "isCurrentItemDummy" );
   const I_CHAR * const SETCONTAINER                  = I_( "setContainer" );
   const I_CHAR * const SETGROUPID                    = I_( "setGroupID" );
   const I_CHAR * const RESETCURRENTITEM              = I_( "resetCurrentItem" );

   // Literals
   const I_CHAR * const ID = I_( "ID" );
   const I_CHAR * const KEY = I_( "KEY" );
}

namespace CND
{  // Conditions used
   extern const long BP_ERR_DUPLICATE_KEY_IN_FIELD_DETAILS;
   extern const long BP_ERR_FIELD_NOT_FOUND;
   extern const long BP_ERR_ID_OUT_OF_RANGE;
   extern const long BP_ERR_INVALID_METHOD_CALL;
   extern const long BP_ERR_LIST_NOT_FOUND;
   extern const long BP_ERR_NO_PARENT_EXISTS;
   extern const long BP_ERR_SEH_EXCEPTION;
   extern const long BP_ERR_UNKNOWN_EXCEPTION;
}

const DString AbstractProcess::s_empty_( I_( "" ) );


//******************************************************************************
//              Public Methods
//******************************************************************************

AbstractProcess::AbstractProcess( GenericInterfaceContainer *rpGIC,
                                  GenericInterface *rpGIParent,
                                  const Command &cmd) 
: GenericInterface( rpGIC, rpGIParent, cmd )
, bIgnoreWarningsOnOk2_( true )
{
   EXECHISTI( I_( "AbstractProcess( GenericInterfaceContainer *, GenericInterface *, const Command & )" ) );

   GenericInterface* pParent = getParent();
   setDataGroupId( BFDataGroupId( BFDataGroupId::getNextDataGroupId(), ( NULL != pParent ) ? ( pParent->getDataGroupId() ) : BF::HOST ) );

   bf::log::LogStream ls( bf::log::process );
   ls << bf::log::information << I_( "Process " ) << cmd.getName() << I_( " created." ) << bf::log::endlf;
}

//******************************************************************************
AbstractProcess::AbstractProcess()
: GenericInterface()
{
   EXECHIST2( I_("AbstractProcess"), 
              I_( "AbstractProcess(  )" ) );
   setDataGroupId( BFDataGroupId( BFDataGroupId::getNextDataGroupId(), BF::HOST ) );
}

//******************************************************************************
AbstractProcess::~AbstractProcess()
{
   EXECHISTI( I_( "~AbstractProcess(  )" ) );

   bf::log::LogStream ls( bf::log::process );
   ls << bf::log::information << I_( "Process " ) << getCommand().getName() << I_( " ended." ) << bf::log::endlf;

   CONTAINERS::iterator iter = _containers.begin();
   while( iter != _containers.end() )
   {
      delete ( *iter ).second;
      iter++;
   }
   _containers.clear();

   FIELDS::iterator iter2 = _fields.begin();
   while( iter2 != _fields.end() )
   {
      delete ( *iter2 ).second;
      iter2++;
   }
   _fields.clear();

   getDataGroupId().setParent( NULL );    // remove parentage for our datagroup
}

//******************************************************************************

void AbstractProcess::deregisterObserver( const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId &idField,
                                          const BFDataGroupId& idDataGroup,
                                          BFObserver &rpObserver )
{
   try
   {
      assert( hasProcessRun() );   // process should always run first
      FieldDetails *rpFieldDetails = findField( idContainer, idField );
      if( rpFieldDetails )
      {  // We have field to process
         BFContainerId idFieldContainer = idContainer;
         if( idFieldContainer == BF::NullContainerId )
         {  // User didn't pass one in, make sure we try to use field definition
            idFieldContainer = rpFieldDetails->getContainerID();
         }
         switch( rpFieldDetails->_eProcessFlags )
         {
            case SUBCLASS_PROCESS:
               // Derived process is doing all processing for this field
               doDeRegisterObserver( rpGICaller, idFieldContainer, idField, idDataGroup, rpObserver );
               return;
               break;
            case RELAY_TO_PARENT:
               // TODO - may want to try and deregister observer here
               return;
               break;
            default:
               {  // Presently, default assumes this is a ListDetails associated
                  // object with CBO's to access
                  if( idFieldContainer == BF::NullContainerId )
                  {
                     assert( 0 );
                     return;
                  }
                  BFAbstractCBO* rpPtr = getCBOItem( idFieldContainer, idDataGroup );
                  rpPtr->deleteObserver( rpFieldDetails->getFieldID(), idDataGroup,
                                         &rpObserver, FIELD_NOTIFICATIONS, E_EVENT_ALL );
                  return;
               }
               break;
         }
      }
      else
      {  // No handling for this case
         return;
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, DEREGISTEROBSERVER, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DEREGISTEROBSERVER, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

SEVERITY AbstractProcess::fireCrossEdit(
                                       const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId &crossEditID,
                                       long lValidateGroup
                                       )
{
   EXECHISTI( I_( "fireCrossEdit( const GenericInterface *, const BFContainerId &, const BFFieldId &, long )" ) );

   SEVERITY sevRtn = NO_CONDITION;
   try
   {
      assert( hasProcessRun() );   // process should always run first
      DString str;
      const BFDataGroupId& idDataGroup = getDataGroupId();

      AbstractListDetails &list = findContainer( idContainer, idDataGroup );
      if( list.isUpdatable() )
      {  // Only do this if updatable
         BFAbstractCBO* rpPtr = getCBOItem( idContainer, idDataGroup );
         if( crossEditID == ifds::NullFieldId )
         {  // Want complete validation
            sevRtn = rpPtr->validateAll( idDataGroup, lValidateGroup );
         }
         else
         {  // Fire specific validation
            sevRtn = rpPtr->validateField( crossEditID, str, idDataGroup );
         }
      }
      return(sevRtn);
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, FIRECROSSEDIT, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, FIRECROSSEDIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

const BFContainerId& AbstractProcess::getContainerID( const DString &name )
{  // Not preferred method of access since have to iterate through containers
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "getContainerID( const DString & )" ) );
   //  to search
   CONTAINERS::iterator iter = _containers.begin();

   while( iter != _containers.end() )
   {
      AbstractListDetails &container = *( ( *iter ).second );

      if( container.getName() == name )
      {  // return container id
         return(container.getContainerID());
      }
      iter++;
   }
   return( BF::CrapContainerId );   // TODO: was -1 ... now is ???
}

//******************************************************************************

void AbstractProcess::getCrossEditFields(
                                        const GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer,
                                        const BFFieldId &crossEditID,
                                        std::vector< BFFieldId > &fieldVector
                                        )
{
   EXECHISTI( I_( "getCrossEditFields( const GenericInterface *, const BFContainerId &, const BFFieldId &, std:: )" ) );

   try
   {
      assert( hasProcessRun() );   // process should always run first

      BFAbstractCBO* rpPtr = getCBOItem( idContainer, getDataGroupId() );
      rpPtr->getCrossEditFields( crossEditID, fieldVector );
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETCROSSEDITFIELDS, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETCROSSEDITFIELDS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
SEVERITY AbstractProcess::getAllErrors(
                                      GenericInterface *rpGICaller,
                                      CONDITIONVECTOR &conditions
                                      )
{
   EXECHISTI( I_( "getAllErrors( GenericInterface *, CONDITIONVECTOR & )" ) );


   // get all errors (object and field) associated
   // with the interface.  Do this by getting the WorkSessionDetails
   // object and using its recursive getAllErrors method

   try
   {
      assert( hasProcessRun() );   // process should always run first
      conditions.clear();

      const BFDataGroupId& idDataGroup = getDataGroupId();
      if( idDataGroup == BF::HOST )
      {  // Host group, no errors - so don't bother
         return(NO_CONDITION);
      }

      return(getBFWorkSession()->getAllErrors( idDataGroup, conditions, true ));
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETERRORS, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETERRORS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
SEVERITY AbstractProcess::getErrors(
                                   GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId &idField,
                                   CONDITIONVECTOR &conditions
                                   )
{
   EXECHISTI( I_( "getErrors( GenericInterface *, const BFContainerId &, const BFFieldId &, CONDITIONVECTOR & )" ) );
//   TRACE_METHOD( CLASSNAME, GETERRORS );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      assert( hasProcessRun() );   // process should always run first
      conditions.clear();

      const BFDataGroupId& idDataGroup = getDataGroupId();
      if( idDataGroup == BF::HOST )
      {  // Host group, no errors - so don't bother
         return(NO_CONDITION);
      }
      if( idField == ifds::NullFieldId && idContainer == BF::NullContainerId )
      {  // Get all non-field specific errors
         if( !getBFSession()->isBFWorkSession() )
            return(getBFSession()->getUserSession().getNonFieldErrors( idDataGroup, conditions ));
         else
            return(getBFWorkSession()->getNonFieldErrors( idDataGroup, conditions ));
      }

      FieldDetails *rpFieldDetails = findField( idContainer, idField );
      if( rpFieldDetails )
      {  // We have field to process
         BFContainerId idFieldContainer = idContainer;
         if( idFieldContainer == BF::NullContainerId )
         {  // User didn't pass one in, make sure we try to use field definition
            idFieldContainer = rpFieldDetails->getContainerID();
         }
         switch( rpFieldDetails->_eProcessFlags )
         {
            case SUBCLASS_PROCESS:
               // Derived process is doing all processing for this field
               sevRtn =  doGetErrors( rpGICaller, idFieldContainer, idField, idDataGroup, conditions );
               break;
            case RELAY_TO_PARENT:
               // Only allowed for non-container based fields to keep group
               // processing simple.  (In other words, don't use this process type
               // for any field that should have group processing.)
               if( idFieldContainer != BF::NullContainerId )
               {
                  assert( 0 );
               }
               //TODO - what do we want here?
               break;
            default:
               {  // Presently, default assumes this is a ListDetails associated
                  // object with CBO's to access
                  if( idFieldContainer == BF::NullContainerId )
                  {
                     assert( 0 );
                  }
                  else
                  {
                     BFAbstractCBO* rpPtr = getCBOItem( idFieldContainer, idDataGroup );
                     sevRtn = rpFieldDetails->getErrors( rpPtr, idDataGroup, conditions );
                  }
               }
               break;
         }
      }
      else
      {
         // Getting errors for container
         BFAbstractCBO* rpPtr = getCBOItem( idContainer, idDataGroup );
         sevRtn = rpPtr->getAllErrors( idDataGroup, conditions );
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETERRORS, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETERRORS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn);
}

//******************************************************************************
SEVERITY AbstractProcess::getItemErrors( GenericInterface *rpGICaller,
                                         const BFContainerId& idContainer,
                                         const DString* pKey,
                                         const BFFieldId &idField,
                                         CONDITIONVECTOR &conditions )
{
   EXECHISTI( I_( "getItemErrors( GenericInterface *, const BFContainerId &, const DString *, const BFFieldId &, CONDITIONVECTOR & )" ) );

   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      assert( hasProcessRun() );   // process should always run first
      conditions.clear();

      const BFDataGroupId& idDataGroup = getDataGroupId();
      if( idDataGroup == BF::HOST )
      {  // Host group, no errors - so don't bother
         return(NO_CONDITION);
      }
      if( idField == ifds::NullFieldId && idContainer == BF::NullContainerId )
      {  // Get all non-field specific errors
         if( !getBFSession()->isBFWorkSession() )
            return(getBFSession()->getUserSession().getNonFieldErrors( idDataGroup, conditions ));
         else
            return(getBFWorkSession()->getNonFieldErrors( idDataGroup, conditions ));
      }

      FieldDetails *rpFieldDetails = findField( idContainer, idField );
      if( rpFieldDetails )
      {  // We have field to process
         BFContainerId idFieldContainer = idContainer;
         if( idFieldContainer == BF::NullContainerId )
         {  // User didn't pass one in, make sure we try to use field definition
            idFieldContainer = rpFieldDetails->getContainerID();
         }
         switch( rpFieldDetails->_eProcessFlags )
         {
            case SUBCLASS_PROCESS:
               // Derived process is doing all processing for this field
               sevRtn =  doGetErrors( rpGICaller, idFieldContainer, idField, idDataGroup, conditions );
               break;
            case RELAY_TO_PARENT:
               // Only allowed for non-container based fields to keep group
               // processing simple.  (In other words, don't use this process type
               // for any field that should have group processing.)
               if( idFieldContainer != BF::NullContainerId )
               {
                  assert( 0 );
               }
               //TODO - what do we want here?
               break;
            default:
               {  // Presently, default assumes this is a ListDetails associated
                  // object with CBO's to access
                  if( idFieldContainer == BF::NullContainerId )
                  {
                     assert( 0 );
                  }
                  else
                  {
                     BFAbstractCBO* rpPtr = getCBOItem( idFieldContainer, idDataGroup, pKey );
                     sevRtn = rpFieldDetails->getErrors( rpPtr, idDataGroup, conditions );
                  }
               }
               break;
         }
      }
      else
      {
         // Getting errors for container
         BFAbstractCBO* rpPtr = getCBOItem( idContainer, idDataGroup, pKey );
         sevRtn = rpPtr->getAllErrors( idDataGroup, conditions );
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, I_( "GetItemErrors" ), CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "GetItemErrors" ), CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn);
}

//******************************************************************************
void AbstractProcess::getErrorState( GenericInterface *rpGICaller,
                                     const BFContainerId& idContainer,
                                     bool bCurrentItem,
                                     SEVERITY &sevObject,
                                     SEVERITY &sevChildren )
{
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "getErrorState( GenericInterface *, const BFContainerId &, bool, SEVERITY &, SEVERITY & )" ) );

   try
   {
      assert( hasProcessRun() );   // process should always run first

      const BFDataGroupId& idDataGroup = getDataGroupId();
      if( idDataGroup == BF::HOST )
      {  // Host group, no errors - so don't bother
         return;
      }
      if( idContainer == BF::NullContainerId )
      {  // Not valid
         assert( 0 );
         return;
      }

      // TODO - if ever get ListDetails away from abstractlistdetails - move to
      //  list details
      BFAbstractCBO* rpPtr = NULL;
      if( bCurrentItem )
      {  // Get error state for current item in container
         rpPtr = getCBOItem( idContainer, idDataGroup );
      }
      else
      {  // Get error state for container
         rpPtr = getCBOItem( idContainer, idDataGroup );
      }

      if( rpPtr )
      {
         sevObject = rpPtr->getMaxValidationSeverityForObject( idDataGroup );
         sevChildren = rpPtr->getMaxValidationSeverityForChildren( idDataGroup );
      }
      else
      {
         assert( 0 );
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETERRORSTATE, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETERRORSTATE, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
void AbstractProcess::getItemErrorState( GenericInterface *rpGICaller,
                                         const BFContainerId& idContainer,
                                         const DString* pKey,
                                         SEVERITY &sevObject,
                                         SEVERITY &sevChildren )
{
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "getItemErrorState( GenericInterface *, const BFContainerId &, const DString *, SEVERITY &, SEVERITY & )" ) );
   try
   {
      assert( hasProcessRun() );   // process should always run first

      const BFDataGroupId& idDataGroup = getDataGroupId();
      if( idDataGroup == BF::HOST )
      {  // Host group, no errors - so don't bother
         return;
      }
      if( idContainer == BF::NullContainerId )
      {  // Not valid
         assert( 0 );
         return;
      }

      // TODO - if ever get ListDetails away from abstractlistdetails - move to
      //  list details
      BFAbstractCBO* rpPtr = NULL;
      // Get error state for container
      rpPtr = getCBOItem( idContainer, idDataGroup, pKey );
      
      if( rpPtr )
      {
         sevObject = rpPtr->getMaxValidationSeverityForObject( idDataGroup );
         sevChildren = rpPtr->getMaxValidationSeverityForChildren( idDataGroup );
      }
      else
      {
         assert( 0 );
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, I_( "GetItemErrorState" ), CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "GetItemErrorState" ), CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
void AbstractProcess::getField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId &idField,
                              DString &strValueOut,
                              bool bFormatted
                              )
{
//   EXECHIST2( 
//      CLASSNAME,
//      I_( "getField( const GenericInterface *, const BFContainerId &, const BFFieldId &, DString &, bool )" ) );
//   TRACE_METHOD( CLASSNAME, GETFIELD );

   try
   {
      assert( hasProcessRun() );   // process should always run first
      const BFDataGroupId& idDataGroup = getDataGroupId();
      FieldDetails *rpFieldDetails = findField( idContainer, idField );
      if( rpFieldDetails )
      {  // We have field to process
         BFContainerId idFieldContainer = idContainer;
         if( idContainer == BF::NullContainerId )
         {  // User didn't pass one in, make sure we try to use field definition
            idFieldContainer = rpFieldDetails->getContainerID();
         }
         switch( rpFieldDetails->_eProcessFlags )
         {
            case SUBCLASS_PROCESS:
               // Derived process is doing all processing for this field
               doGetField( rpGICaller,
                           idFieldContainer,
                           idField,
                           idDataGroup,
                           strValueOut,
                           bFormatted );
               return;
            case RELAY_TO_PARENT:
               // Only allowed for non-container based fields to keep group
               // processing simple.  (In other words, don't use this process type
               // for any field that should have group processing.)
               if( idFieldContainer != BF::NullContainerId )
               {
                  assert( 0 );
                  return;
               }
               if( getParent() )
               {
                  getParent()->getField( this, idFieldContainer, idField, strValueOut, bFormatted );
                  return;
               }
               else
               {
                  assert( 0 );
                  THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_NO_PARENT_EXISTS );
               }
               break;
            default:
               {  // Presently, default assumes this is a ListDetails associated
                  // object with CBO's to access
                  if( idFieldContainer == BF::NullContainerId )
                  {
                     assert( 0 );
                     return;
                  }
                  BFAbstractCBO* rpPtr = getCBOItem( idFieldContainer, idDataGroup );

                  //I want to return an empty string !!
                  if( !rpPtr ) return;

                  rpFieldDetails->getField( rpPtr,
                                            bFormatted,
                                            strValueOut,
                                            idDataGroup );
               }
               break;
         }
      }
      else
      {  // Maybe list will deal with field directly.  This would be for
         // non-CBO based lists - otherwise an exception should be thrown from
         // the getfield
         AbstractListDetails &container = findContainer( idContainer, idDataGroup );

         container.getField( idField, bFormatted, strValueOut, idDataGroup );
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void AbstractProcess::getField(
                              const GenericInterface *rpGICaller,
                              const BFFieldId &idField,
                              DString &strValueOut,
                              bool bFormatted
                              )
{
   TRACE_METHOD( CLASSNAME, GETFIELD2 );

   // pass thru to main method
   getField( rpGICaller, BF::NullContainerId, idField, strValueOut, bFormatted );
}

//******************************************************************************

const BFProperties *AbstractProcess::getFieldAttributes(
                                                       const GenericInterface *rpGICaller,
                                                       const BFContainerId& idContainer,
                                                       const BFFieldId &idField
                                                       )
{
   TRACE_METHOD( CLASSNAME, GETFIELDATTRIBUTES );
   try
   {
      assert( hasProcessRun() );   // process should always run first
      FieldDetails *rpFieldDetails = findField( idContainer, idField );
      const BFDataGroupId& idDataGroup = getDataGroupId();

      if( rpFieldDetails )
      {  // We have field to process
         BFContainerId idFieldContainer = idContainer;
         if( idFieldContainer == BF::NullContainerId )
         {  // User didn't pass one in, make sure we try to use field definition
            idFieldContainer = rpFieldDetails->getContainerID();
         }
         switch( rpFieldDetails->_eProcessFlags )
         {
            case SUBCLASS_PROCESS:
               // Derived process is doing all processing for this field
               return(doGetFieldAttributes( rpGICaller, idFieldContainer, idField, idDataGroup ));
            case RELAY_TO_PARENT:
               // Only allowed for non-container based fields to keep group
               // processing simple.  (In other words, don't use this process type
               // for any field that should have group processing.)
               if( idFieldContainer != BF::NullContainerId )
               {
                  assert( 0 );
                  return(NULL);
               }
               if( getParent() )
               {
                  return(getParent()->getFieldAttributes( this, idFieldContainer, idField ));
               }
               else
               {
                  assert( 0 );
                  THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELDATTRIBUTES, CND::BP_ERR_NO_PARENT_EXISTS );
               }
               break;
            default:
               {  // Presently, default assumes this is a ListDetails associated
                  // object with CBO's to access
                  if( idFieldContainer == BF::NullContainerId )
                  {
                     assert( 0 );
                     return(NULL);
                  }
                  BFAbstractCBO* rpPtr = getCBOItem( idFieldContainer, idDataGroup );
                  return(rpFieldDetails->getFieldAttributes( rpPtr, idDataGroup ));
               }
               break;
         }
      }
      else
      {  // No handling for this case
         return(NULL);
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELDATTRIBUTES, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELDATTRIBUTES, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

E_COMMANDRETURN AbstractProcess::invokeProcessFromChild( GenericInterface *rpGICaller,
                                                         const I_CHAR *szCommand,
                                                         E_PROCESSTYPE type,
                                                         bool bModal,
                                                         GenericInterface **rpGIModelessOut )
{
   EXECHISTI( I_( "invokeProcessFromChild( GenericInterface *, const I_CHAR *, E_PROCESSTYPE, bool, GenericInterface ** )" ) );
   E_COMMANDRETURN eRtn;

   try
   {
      eRtn = invokeCommand( this, szCommand, type, bModal, rpGIModelessOut );
      /*
      if ( bModal )
      {  // Need to operate child process under group parentage of child that is
         // starting it.
         //setParentGroupIDForInvoke( getDataGroupId() );
         AbstractProcess *rpParent =
            dynamic_cast< AbstractProcess *> (rpGICaller->getParent()->getParent());

         if ( rpParent )
         {
            BFBase::setGlobalGroupContainement(
               rpParent->getGroupID(),
               m_GroupId );
         }
      }
      */

   }
   catch( ConditionException & )
   {
      // Force back to my group ID
      //setParentGroupIDForInvoke( getDataGroupId() );
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, INVOKEPROCESSFROMCHILD, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      // Force back to my group ID
      //      setParentGroupIDForInvoke( getDataGroupId() );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, INVOKEPROCESSFROMCHILD, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   // Force back to my group ID
   //setParentGroupIDForInvoke( getDataGroupId() );

   return(eRtn);
}

//******************************************************************************

E_COMMANDRETURN AbstractProcess::process()
{
   EXECHISTI( I_( "process()" ) );
   TRACE_METHOD( CLASSNAME, PROCESS );
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
         assert( 0 );
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, PROCESS, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************

bool AbstractProcess::registerObserver(
                                      const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId &idField,
                                      const BFDataGroupId& idDataGroup,
                                      BFObserver &rpObserver
                                      )
{
   EXECHISTI( I_( "registerObserver( const GenericInterface *, const BFContainerId &, const BFFieldId &, const BFDataGroupId &, BFObserver & )" ) );

   try
   {
      assert( hasProcessRun() );   // process should always run first
      FieldDetails *rpFieldDetails = findField( idContainer, idField );
      if( rpFieldDetails )
      {  // We have field to process
         BFContainerId idFieldContainer = idContainer;
         if( idFieldContainer == BF::NullContainerId )
         {  // User didn't pass one in, make sure we try to use field definition
            idFieldContainer = rpFieldDetails->getContainerID();
         }
         switch( rpFieldDetails->_eProcessFlags )
         {
            case SUBCLASS_PROCESS:
               // Derived process is doing all processing for this field
               return(doRegisterObserver( rpGICaller, idFieldContainer, idField, idDataGroup, rpObserver ));
               break;
            case RELAY_TO_PARENT:
               // TODO - may want to try and register observer here
               return(false);
               break;
            default:
               {  // Presently, default assumes this is a ListDetails associated
                  // object with CBO's to access
                  if( idFieldContainer == BF::NullContainerId )
                  {
                     assert( 0 );
                     return(false);
                  }
                  BFAbstractCBO *rpPtr = getCBOItem( idFieldContainer, idDataGroup );
                  return(rpPtr->registerObserver( rpFieldDetails->getFieldID(), idDataGroup, &rpObserver, FIELD_NOTIFICATIONS, E_EVENT_ALL ));
               }
               break;
         }
      }
      else
      {  // No handling for this case
         return(false);
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, REGISTEROBSERVER, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, REGISTEROBSERVER, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

SEVERITY AbstractProcess::resetCurrentItem( const BFContainerId& idContainer )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, RESETCURRENTITEM );

   const BFDataGroupId& idDataGroup = getDataGroupId();

   AbstractListDetails &container = findContainer( idContainer, idDataGroup );

   if( container.isUpdatable() )
   {  // Should only need to reset if updatable
      container.resetCurrentItem( idDataGroup );
      if( container.hasChildren() )
      {
         resetChildContainers( idContainer );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AbstractProcess::reset(
                               GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               bool bCurrentItem
                               )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, RESET );
   const BFDataGroupId& idDataGroup = getDataGroupId();

   if( idContainer == BF::AllContainerIds )
   {  // Reset all containers
      assert( !bCurrentItem );  // Should be false if doing all containers
      CONTAINERS::iterator iter = _containers.begin();
      while( iter != _containers.end() )
      {
         if( ( *iter ).second->isUpdatable() )
         {  // Should only need to reset if updatable
            ( *iter ).second->reset( idDataGroup, false );
         }
         iter++;
      }
   }
   else
   {  // Doing one container
      AbstractListDetails &container = findContainer( idContainer, idDataGroup );

      if( container.isUpdatable() )
      {  // Should only need to reset if updatable
         container.reset( idDataGroup, bCurrentItem );
         if( container.hasChildren() )
         {
            resetChildContainers( idContainer );
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************


//******************************************************************************

SEVERITY AbstractProcess::setData( GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFData *rpData )
{
   EXECHISTI( I_( "setData( GenericInterface *, const BFContainerId &, const BFData * )" ) );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      assert( hasProcessRun() );   // process should always run first
      const BFDataGroupId& idDataGroup = getDataGroupId();
      if( idContainer == BF::NullContainerId )
      {
         assert( 0 );
         // TODO - add real condition for this
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETDATA, CND::BP_ERR_NO_PARENT_EXISTS );
      }
      AbstractListDetails &container = findContainer( idContainer,
                                                      idDataGroup );
      if( !container.isUpdatable() )
      {
         // TODO Change to different condition here
         assert( 0 );
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETDATA, CND::BP_ERR_UNKNOWN_EXCEPTION );
      }
      BFCBO *rpPtr = dynamic_cast< BFCBO* >( getCBOItem( idContainer, idDataGroup ) );
      sevRtn = rpPtr->setData( *rpData, idDataGroup );
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, SETDATA, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETDATA, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn);
}

//******************************************************************************

SEVERITY AbstractProcess::setField(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId &idField,
                                  const DString &strValue,
                                  bool bFormatted
                                  )
{
   EXECHISTI( I_( "setField( const GenericInterface *, const BFContainerId &, const BFFieldId &, const DString &, bool )" ) );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      assert( hasProcessRun() );   // process should always run first
      FieldDetails *rpFieldDetails = findField( idContainer, idField );
      if( rpFieldDetails )
      {  // We have a field to process
         BFContainerId idFieldContainer = idContainer;
         if( idFieldContainer == BF::NullContainerId )
         {  // User didn't pass one in, make sure we try to use field definition
            idFieldContainer = rpFieldDetails->getContainerID();
         }

         switch( rpFieldDetails->_eProcessFlags )
         {
            case SUBCLASS_PROCESS:
               // Derived process is doing all processing for this field
               sevRtn = doSetField( rpGICaller,
                                    idFieldContainer,
                                    idField,
                                    getDataGroupId(),
                                    strValue,
                                    bFormatted );
               return(sevRtn);
            case RELAY_TO_PARENT:
               // Only allowed for non-container based fields to keep group
               // processing simple.  (In other words, don't use this process type
               // for any field that should have group processing.)
               if( idFieldContainer != BF::NullContainerId )
               {
                  assert( 0 );
                  // TODO - add real condition for this
                  THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD, CND::BP_ERR_NO_PARENT_EXISTS );
               }
               if( getParent() )
               {
                  return(getParent()->setField( this, idFieldContainer, idField, strValue, bFormatted ));
               }
               else
               {
                  assert( 0 );
                  THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD, CND::BP_ERR_NO_PARENT_EXISTS );
               }
               break;
            default:
               {  // Presently, default assumes this is a CBO container
                  const BFDataGroupId& idDataGroup = getDataGroupId();
                  if( idFieldContainer == BF::NullContainerId )
                  {
                     assert( 0 );
                     // TODO - add real condition for this
                     THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD, CND::BP_ERR_NO_PARENT_EXISTS );
                  }
                  AbstractListDetails &container = findContainer( idFieldContainer,
                                                                  idDataGroup );
                  if( !container.isUpdatable() )
                  {
                     // TODO Change to different condition here
                     assert( 0 );
                     THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD, CND::BP_ERR_UNKNOWN_EXCEPTION );
                  }
                  BFAbstractCBO *rpPtr = getCBOItem( idFieldContainer, idDataGroup );
                  return(rpFieldDetails->setField( rpPtr,
                                                   bFormatted,
                                                   strValue,
                                                   idDataGroup ));
               }
               break;
         }
      }
      else
      {  // Maybe list will deal with field directly.  This would be for
         // non-CBO based lists - otherwise an exception should be thrown from
         // the setfield
         AbstractListDetails &container = findContainer( idContainer,
                                                         getDataGroupId() );

         if( !container.isUpdatable() )
         {
            // TODO Change to different condition here
            assert( 0 );
            THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD, CND::BP_ERR_UNKNOWN_EXCEPTION );
         }
         container.setField( idField,
                             bFormatted,
                             strValue,
                             getDataGroupId() );
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn);
}

//******************************************************************************

SEVERITY AbstractProcess::setField(
                                  const GenericInterface *rpGICaller,
                                  const BFFieldId &idField,
                                  const DString &strValue,
                                  bool bFormatted
                                  )
{
   TRACE_METHOD( CLASSNAME, SETFIELD2 );

   return(setField( rpGICaller, BF::NullContainerId, idField, strValue, bFormatted ));
}

// ***************   List methods    *******************

//******************************************************************************

SEVERITY AbstractProcess::deleteItemFromList(
                                            const GenericInterface *rpGICaller,
                                            const BFContainerId& idList
                                            )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DELETEITEMFROMLIST );
   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      assert( hasProcessRun() );   // process should always run first
      AbstractListDetails &list = findContainer( idList, idDataGroup );

      // Make sure group exists in CBO
      BFAbstractCBO *rpPtr = ( BFAbstractCBO * )list.getContainer();
      if( list.deleteItem( idDataGroup ) <= WARNING )
      {  // Item changed so any child containers must be reset.
         if( list.hasChildren() )
         {
            resetChildContainers( idList );
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      ADDCONDITIONFROMFILEIDI( CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      ADDCONDITIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

const DString &AbstractProcess::getCurrentListItemKey(
                                                     const GenericInterface *rpGICaller,
                                                     const BFContainerId& idList
                                                     )
{
//   EXECHIST2( 
//      CLASSNAME,
//	I_( "getCurrentListItemKey( const GenericInterface *, const BFContainerId & )" ) );
//   TRACE_METHOD( CLASSNAME, GETCURRENTLISTITEMKEY );

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();
      AbstractListDetails &list = findContainer( idList, idDataGroup );
      return(list.getCurrentKey( idDataGroup ));
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETCURRENTLISTITEMKEY, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETCURRENTLISTITEMKEY, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

const DString &AbstractProcess::getFirstListItemKey(
                                                   const GenericInterface *rpGICaller,
                                                   const BFContainerId& idList
                                                   )
{
//   EXECHIST2( 
//      CLASSNAME,
//      I_( "getFirstListItemKey( const GenericInterface *, const BFContainerId & )" ) );

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();
      const DString *rpStr = NULL;
      AbstractListDetails &list = findContainer( idList, idDataGroup );

      if( list.getFirstKey( &rpStr, idDataGroup ) )
      {  // Item changed so any child containers must be reset.
         if( list.hasChildren() )
         {
            resetChildContainers( idList );
         }
      }
      return(*rpStr);
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

const DString &AbstractProcess::getKeyForNewListItem(
                                                    const GenericInterface *rpGICaller,
                                                    const BFContainerId& idList
                                                    )
{
//   EXECHIST2( 
//      CLASSNAME,
//      I_( "getKeyForNewListItem( const GenericInterface *, const BFContainerId & )" ) );

   DString strKey;

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      assert( hasProcessRun() );   // process should always run first
      AbstractListDetails &list = findContainer( idList, idDataGroup );

      // Make sure group exists in CBO
      BFAbstractCBO *rpPtr = ( BFAbstractCBO * )list.getContainer();

      return(list.addItem( getDataGroupId() ));
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETKEYFORNEWLISTITEM, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETKEYFORNEWLISTITEM, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

const DString &AbstractProcess::getNextListItemKey(
                                                  const GenericInterface *rpGICaller,
                                                  const BFContainerId& idList
                                                  )
{
//   EXECHIST2( 
//      CLASSNAME,
//      I_( "getNextListItemKey( const GenericInterface *, const BFContainerId & )" ) );


   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();
      const DString *rpStr = NULL;
      AbstractListDetails &list = findContainer( idList, idDataGroup );

      if( list.getNextKey( &rpStr, idDataGroup ) )
      {  // Item changed so any child containers must be reset.
         if( list.hasChildren() )
         {
            resetChildContainers( idList );
         }
      }
      return(*rpStr);
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

int AbstractProcess::getNumberOfItemsInList(
                                           const GenericInterface *rpGICaller,
                                           const BFContainerId& idList
                                           )
{
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "getNumberOfItemsInList( const GenericInterface *, const BFContainerId & )" ) );


   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      assert( hasProcessRun() );   // process should always run first
      AbstractListDetails &list = findContainer( idList, idDataGroup );

      if( !list.isContainerValid() )
      {  // Return 0 items if list invalid - if user tries to do other
         // things with the container he may fail.
         return(0);
      }
      return(list.getNumberOfItemsInList( idDataGroup ));
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETNUMBEROFITEMSINLIST, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETNUMBEROFITEMSINLIST, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

bool AbstractProcess::isCurrentListItemNew(
                                          GenericInterface *rpGICaller,
                                          const BFContainerId& idList
                                          )
{
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "isCurrentListItemNew( GenericInterface *, const BFContainerId & )" ) );
   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      assert( hasProcessRun() );   // process should always run first
      AbstractListDetails &list = findContainer( idList, idDataGroup );

      return(list.isNewItem( idDataGroup ));
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, ISCURRENTLISTITEMNEW, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, ISCURRENTLISTITEMNEW, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void AbstractProcess::setCurrentListItem(
                                        const GenericInterface *rpGICaller,
                                        const BFContainerId& idList,
                                        const DString &strListItemKey
                                        )
{
//   EXECHIST2( 
//      CLASSNAME,
//      I_( "setCurrentListItem( const GenericInterface *, const BFContainerId &, const DString & )" ) );
//   TRACE_METHOD( CLASSNAME, SETCURRENTLISTITEM );

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      assert( hasProcessRun() );   // process should always run first
      AbstractListDetails &list = findContainer( idList, idDataGroup );

      if( list.setCurrentKey( strListItemKey, idDataGroup ) )
      {  // Item changed so any child containers must be reset.
         if( list.hasChildren() )
         {
            resetChildContainers( idList );
         }
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void AbstractProcess::trySetCurrentListItem(
                                           const GenericInterface *rpGICaller,
                                           const BFContainerId& idList,
                                           const DString &strListItemKey
                                           )
{
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "trySetCurrentListItem( const GenericInterface *, const BFContainerId &, const DString & )" ) );

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      assert( hasProcessRun() );   // process should always run first
      AbstractListDetails &list = findContainer( idList, idDataGroup );

      if( list.trySetCurrentKey( strListItemKey, idDataGroup ) )
      {  // Item changed so any child containers must be reset.
         if( list.hasChildren() )
         {
            resetChildContainers( idList );
         }
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
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, I_( "trySetCurrentListItem" ), CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "trySetCurrentListItem" ), CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void AbstractProcess::addContainer(
                                  const BFContainerId& idContainer,
                                  bool bRepeatable,
                                  const BFContainerId& idParentContainer,
                                  bool bUpdatable,
                                  const DString &name
                                  )
{
   EXECHISTI( I_( "addContainer( const BFContainerId &, bool, const BFContainerId &, bool, const DString & )" ) );


   if( !_containers.insert( CONTAINERS::value_type( idContainer,
                                                    new ListDetails( this, idContainer, idParentContainer, bRepeatable, bUpdatable,
                                                                     name ) ) ).second )
   {  // Duplicate insert
      assert( 0 );  // Non-unique key value
      DString strIDI;
      addIDITagValue( strIDI, KEY, idContainer.getId() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, ADDCONTAINER,
                         CND::BP_ERR_DUPLICATE_KEY_IN_FIELD_DETAILS, strIDI );
   }

   if( idParentContainer.isValid() )
   {  // We have a parent, so set parent as having children - parent must exist
      //   first.
      CONTAINERS::iterator iter = _containers.find( idParentContainer );

      if( iter != _containers.end() )
      {
         AbstractListDetails &container = *( ( *iter ).second );
         container.setHasChild();
      }
      else
      {  // Couldn't find match for ID
         assert( 0 );
         DString strIDI;
         addIDITagValue( strIDI, ID, idContainer.getId() );
         THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, ADDCONTAINER,
                            CND::BP_ERR_LIST_NOT_FOUND, strIDI );
      }
   }
}

//******************************************************************************

void AbstractProcess::addFieldDetails(
                                     const BFFieldId &idField,
                                     const BFContainerId& idContainer,
                                     E_FIELDPROCESSFLAG eFieldProcessFlag,
                                     const I_CHAR *szTag
                                     )
{
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "addFieldDetails( const BFFieldId &, const BFContainerId &, E_FIELDPROCESSFLAG, const I_CHAR * )" ) );

   FieldDetails *pFD = new FieldDetails( idContainer, idField,
                                         eFieldProcessFlag, szTag );

   if( idContainer.isValid() )
   {  // Make sure container exists
      CONTAINERS::iterator iter = _containers.find( idContainer );
      if( iter == _containers.end() )
      {  // Container not in our map, this is a problem
         assert( 0 );
         return;
      }
   }

   FieldKey fKey( idContainer, idField );
   if( !_fields.insert( FIELDS::value_type( fKey, pFD )
                      ).second )
   {
      assert( 0 );  // Non-unique key value
      DString strIDI;
      DString strKey = asString( idContainer.getId() ) + I_( ", " );
      strKey += asString( idField.getId() );
      addIDITagValue( strIDI, KEY, strKey );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, ADDFIELDDETAILS,
                         CND::BP_ERR_DUPLICATE_KEY_IN_FIELD_DETAILS, strIDI );
   }
   if( !_fieldContainerMap.insert( FIELDCONTAINERMAP::value_type( idField,
                                                                  idContainer ) ).second )
   {  // Duplicate insert - save for later removal so we never will get a
      // singular match (matching only on field ID) on a field defined in
      // more than one container
      _duplicateFieldIDs.push_back( idField );
   }
}

//******************************************************************************

void AbstractProcess::addSubstituteList( const BFFieldId &fieldId, const DString &name )
{
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "addSubstituteList( const BFFieldId &, const DString & )" ) );


   // suspect!! containers key by long ... every other use is by a container ID except for this one
   if( !_containers.insert( CONTAINERS::value_type( BFContainerId( fieldId.getId() ),
                                                    new SubstituteListDetails( this, fieldId, name ) )
                          ).second )
   {  // Duplicate insert
      assert( 0 );  // Non-unique key value
      DString strIDI;
      addIDITagValue( strIDI, KEY, fieldId.getId() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, ADDSUBSTITUTELIST,
                         CND::BP_ERR_DUPLICATE_KEY_IN_FIELD_DETAILS, strIDI );
   }
}

//******************************************************************************

SEVERITY AbstractProcess::cancel2( GenericInterface *rpGICaller )
{
   EXECHISTI( I_( "cancel2( GenericInterface * )" ) );
   SEVERITY sevRtn = SEVERE_ERROR;

   // TODO - doCancel will change to return SEVERITY
   if( doCancel( rpGICaller ) )
   {
      // TODO - prompt for discard changes here
      return(reset( rpGICaller ));
   }
   return(sevRtn);
}

//******************************************************************************

SEVERITY AbstractProcess::doGetErrors( const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId &idField,
                                       const BFDataGroupId& idDataGroup,
                                       CONDITIONVECTOR &conditions ) const
{  // Default implementation should not ever be called
   // TODO - temporarily returning good condition
   return(NO_CONDITION);
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOGETERRORS, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

void AbstractProcess::doGetField( const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId &idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted ) const
{  // Default implementation should not ever be called
   // TODO - temporarily returning good condition
   return;
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

const BFProperties *AbstractProcess::doGetFieldAttributes( const GenericInterface *rpGICaller,
                                                           const BFContainerId& idContainer,
                                                           const BFFieldId &idField,
                                                           const BFDataGroupId& idDataGroup )
{  // Default implementation just returns NULL (which will make any control
   //  associated with this field read-only
   return(NULL);
}

//******************************************************************************

bool AbstractProcess::doRegisterObserver( const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId &idField,
                                          const BFDataGroupId& idDataGroup,
                                          BFObserver &rpObserver )
{
   return(false);
}

//******************************************************************************

void AbstractProcess::doGetKeyForNewListItem( const GenericInterface *rpGICaller,
                                              const BFContainerId& idList,
                                              DString &strListItemKeyOut )
{  // Default implementation should not ever be called
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOGETKEYFORNEWLISTITEM, CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************

bool AbstractProcess::doModelessChildComplete( const Command &cmd )
{  // Default implementation should not ever be called
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE, CND::BP_ERR_INVALID_METHOD_CALL );
   return(false);
}

//******************************************************************************

bool AbstractProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // If we try to set focus to something this should be overridden
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS, CND::BP_ERR_INVALID_METHOD_CALL );
   return(false);
}

//******************************************************************************

bool AbstractProcess::doRefresh( GenericInterface *rpGICaller,
                                 const I_CHAR *szOriginalCommand )
{
   // TODO - Should check update levels here
   getGIContainer()->refreshGUIChildren( this );
   return(true);
}

//******************************************************************************

SEVERITY AbstractProcess::doSetField( const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId &idField,
                                      const BFDataGroupId& idDataGroup,
                                      const DString &strValue,
                                      bool bFormatted )
{  // If we try to set a field this should be overridden
   // TODO - temporarily returning good condition
   return(NO_CONDITION);
   assert( 0 );
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
   return(SEVERE_ERROR);
}

//******************************************************************************
// Default implementation
SEVERITY AbstractProcess::doValidateAll( BFAbstractCBO *bfWorkSession,
                                         const BFDataGroupId& idDataGroup )
{
   return(bfWorkSession->validateAll( idDataGroup ));
}

//******************************************************************************

BFAbstractCBO *AbstractProcess::getCBOItem( const BFContainerId& idContainer,
                                            const BFDataGroupId& idDataGroup,
                                            const DString* pKey )
{
   void *rpPtr;
   AbstractListDetails &container = findContainer( idContainer, idDataGroup );
   if( container.isRepeatable() )
   {  // List CBO - get CBO for current item
      rpPtr = container.getItem( idDataGroup, pKey );
   }
   else
   {  // Normal CBO container
      rpPtr = container.getContainer();
   }
   return(static_cast< BFAbstractCBO * >( rpPtr ));
}

//******************************************************************************

BFAbstractCBO *AbstractProcess::getCBOList( const BFContainerId& idContainer,
                                            const BFDataGroupId& idDataGroup,
                                            const DString* pKey )
{
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "getCBOList( const BFContainerId &, const BFDataGroupId &, const DString * )" ) );
   void *rpPtr;
   AbstractListDetails &container = findContainer( idContainer, idDataGroup );
   if( container.isRepeatable() )
   {
      rpPtr = container.getContainer();
   }
   else
   {
      rpPtr = container.getItem( idDataGroup, pKey );
   }
   return(static_cast< BFAbstractCBO * >( rpPtr ));
}

//******************************************************************************

SEVERITY AbstractProcess::ok2( GenericInterface *rpGICaller )
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, OK2 );
   //   BFSessionManager *rpBSM = BFSessionManager::getInstance();
   //   WorkSessionDetails *rpWSD =
   //      rpBSM->getWorkSessionDetails( getWorkSessionID() );
   BFWorkSession *bfWorkSession = getBFWorkSession();
   const BFDataGroupId& idDataGroup = getDataGroupId();
   bool bSuccessFlag = false;
   bool bNeedRefresh = false;
   bool bUpdated = false;
   // Allow subclass override if need to do other things prior to any ok2
   //  processing
   bool bContinue = true;
   if( doOk( rpGICaller ) )
   {
      if( bfWorkSession )
      {  // Only if work session details exists
         if( bfWorkSession->isUpdatedForDataGroup( idDataGroup ) )
         {
            bUpdated = true;
            //            if ( doValidateAll( bfWorkSession, idDataGroup ) <= WARNING )
            SEVERITY eRtn = doValidateAll( bfWorkSession, idDataGroup );
            if( eRtn == WARNING && !bfutil::isServerContext() )
            {
               bContinue = rpGICaller->send( rpGICaller, I_( "WarningConfirm" ) );
            }
            if( bContinue )
            {
               if( eRtn < WARNING || ( eRtn == WARNING && getIgnoreWarningsOnOk2() ) ) //ConfirmationProcess doesn't get launched if we got a warning
               {
                  //and bIgnoreWarningsOnOk2_ is set to false
                  bSuccessFlag = true;
                  if( getProcessType() == PROC_SUPPORT ||
                     ( bfutil::isServerContext() && isModal() ) ||
                     ( !bfutil::isServerContext() && isModal() &&  getParent() && getParent()->isModal() ) )
                  {  // we should only do this commit if we are not about to confirm
                     //  and there should be a NON BF::HOST parent group to commit to
                     // Note that modal without parent will not commit here
                     if( !ValidationControl::get().isValidateOnly() )
                     {
                        if( bfWorkSession->commitDataGroup( idDataGroup ) <= WARNING )
                        {  // Refresh other processes
                           bNeedRefresh = true;
                        }
                        else
                        {  // Commit failed
                           PROMOTECONDITIONS();
                           bSuccessFlag = false;
                        }
                     }
                  }
               }
               else if( bfutil::isServerContext() )
               {  // for gui, errors get picked up directly from CBO's ?
                  PROMOTECONDITIONS();
               }
            } // if bContinue
         }
         else
         {  // Nothing happened - make sure and remove any dummy entries added
            bfWorkSession->deleteNonUpdatedAddedElements( idDataGroup );
            bSuccessFlag = true;
         }
      }
   }
   else
   {  // get doOK conditions, if any
      PROMOTECONDITIONS();
   }

   if (bSuccessFlag) {
      ProcessObserver* procObserver = getProcessObserver();
      if (procObserver) {
         procObserver->notifyOk(rpGICaller, this);
      }
   }

   //no need to confirm and refresh if we've been used for support
   if( bfWorkSession && bSuccessFlag && getProcessType() != PROC_SUPPORT )
   {
      if( ( bfutil::isServerContext() && !isModal() ) ||
         ( !bfutil::isServerContext() && (!getParent() || !getParent()->isModal() ) ) )
      {  // Possibly need confirmation if we are modeless, no parent, or our
         // parent is modeless
         BFCPSession *pSession = getSession();

         BFAwdSession *rpAwdSession = NULL;

         if( pSession != NULL )
         {
            rpAwdSession = pSession->getAwdSession();
         }

         if( bUpdated && !ValidationControl::get().isValidateOnly() )
         {
            // this will commit *our* datagroup (i.e. this->getDataGroupId() )
            if( CMD_OK != invokeCommand( this, CMD_BPROC_CONFIRMATION,
                                         PROC_NO_TYPE, true, NULL ) )
            {
               DString strOut;
               bSuccessFlag = false;
               PROMOTECONDITIONS();
               getParameter( I_( "TrxnsError" ), strOut );
               if( strOut == I_( "Y" ) )
               {  // Need to halt further activities in BaseMainDlg
                  rpGICaller->send( this, I_( "TrxnsError" ) );
               }
            }
            else
            {  // Force refresh for now - but not needed for all cases
               bNeedRefresh = true;

               // if we are in "server mode" then make sure
               // that all errors get reported.
               if( bfutil::isServerContext() )
               {
                  PROMOTECONDITIONS();
               }
            }
         }
      }
      if( bNeedRefresh )
      {
         getGIContainer()->refresh( this );
      }
   }

   // Allow subclass override if need to do things after ok processing
   doPostOk( rpGICaller, bSuccessFlag );
   if( bSuccessFlag )
   {
      return(NO_CONDITION);
   }
   return(SEVERE_ERROR);
}

//******************************************************************************

void AbstractProcess::setContainer(
                                  const BFContainerId& idContainer,
                                  void *rpContainer
                                  )
{  // Set container pointer, clearing any child containers as we go (child
   EXECHISTI( I_( "setContainer( const BFContainerId &, void * )" ) );
   // container pointers are no longer valid because the parent has changed).


   CONTAINERS::iterator iter = _containers.find( idContainer );

   if( iter != _containers.end() )
   {
      AbstractListDetails &container = *( ( *iter ).second );
      if( container.setContainer( rpContainer ) )
      {
         if( container.hasChildren() )
         {
            resetChildContainers( idContainer );
         }
      }
   }
   else
   {  // No such container was found !!
      assert( 0 );
      DString strIDI;
      addIDITagValue( strIDI, ID, idContainer.getId() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, SETCONTAINER,
                         CND::BP_ERR_LIST_NOT_FOUND, strIDI );
   }
}

//******************************************************************************

bool AbstractProcess::setKeyFilter(
                                  const BFContainerId& idContainer,
                                  const DString& filter
                                  )
{
   bool rtnVal = false;
   CONTAINERS::iterator iter = _containers.find( idContainer );
   if( iter != _containers.end() )
      rtnVal = (*iter).second->setKeyFilter( filter );

   return(rtnVal);
};

//******************************************************************************

void AbstractProcess::getKeyFilter(
                                  const BFContainerId& idContainer,
                                  DString& filter
                                  )
{
   filter = NULL_STRING;
   CONTAINERS::iterator iter = _containers.find( idContainer );
   if( iter != _containers.end() )
      (*iter).second->getKeyFilter( filter );
}

//******************************************************************************

void AbstractProcess::clearKeyFilter(
                                    const BFContainerId& idContainer
                                    )
{
   CONTAINERS::iterator iter = _containers.find( idContainer );
   if( iter != _containers.end() )
      (*iter).second->clearKeyFilter();
}

//******************************************************************************

bool AbstractProcess::setDataFilter(
                                   const BFContainerId& idContainer,
                                   const DString& filter
                                   )
{
   bool rtnVal = false;
   CONTAINERS::iterator iter = _containers.find( idContainer );
   if( iter != _containers.end() )
      rtnVal = (*iter).second->setDataFilter( filter );

   return(rtnVal);
}

//******************************************************************************

void AbstractProcess::getDataFilter( const BFContainerId& idContainer, DString& filter )
{
   filter = NULL_STRING;
   CONTAINERS::iterator iter = _containers.find( idContainer );
   if( iter != _containers.end() )
      (*iter).second->getDataFilter( filter );
}

//******************************************************************************

void AbstractProcess::clearDataFilter( const BFContainerId& idContainer )
{
   CONTAINERS::iterator iter = _containers.find( idContainer );
   if( iter != _containers.end() )
      (*iter).second->clearDataFilter();
}

//******************************************************************************
//              Private Methods
//******************************************************************************

FieldDetails *AbstractProcess::findField( BFContainerId idContainer,
                                          const BFFieldId &idField ) const
{
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "findField( BFContainerId, const BFFieldId & )" ) );


   if( idContainer == BF::NullContainerId )
   { // User is trying to access field without idContainer, try to get ID
      FIELDCONTAINERMAP_CONST_ITER iter = _fieldContainerMap.find( idField );

      if( iter != _fieldContainerMap.end() )
      {
         idContainer = ( *iter ).second;
      }
      else
      {  // Throw condition for field not found - field must be in field maps
         // when accessing without container ID.  The field will not be in this
         // map if there were duplicate names (so you can't identify the field
         // without the container ID).
         assert( 0 );
         DString strIDI;
         addIDITagValue( strIDI, KEY, idField.getId() );
         THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, FINDFIELD,
                            CND::BP_ERR_FIELD_NOT_FOUND, strIDI );
      }
   }

   FieldKey fKey( idContainer, idField );

   FIELDS_CONST_ITER iter = _fields.find( fKey );

   if( iter == _fields.end() )
   {
      return(NULL);
   }

   return( *iter ).second;
}

//******************************************************************************

AbstractListDetails &AbstractProcess::findContainer(
                                                   const BFContainerId& idContainer,
                                                   const BFDataGroupId& idDataGroup
                                                   )
{  // If container is found, this method validates the container pointer and
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "findContainer( const BFContainerId &, const BFDataGroupId & )" ) );
   // will give subclasses a chance to set, if NULL.


   CONTAINERS::iterator iter = _containers.find( idContainer );

   if( iter != _containers.end() )
   {
      AbstractListDetails &container = *( ( *iter ).second );

      if( !container.isContainerValid() )
      {  // Give subclass a chance to set container for this as well as any
         // parent containers.
         // Set all parents first.
         while( setParentContainers( container, idDataGroup ) );
         getContainerPtr( container, idContainer, idDataGroup );
      }
      return(container);
   }
   else
   {  // Couldn't find match for ID
      assert( 0 );
      DString strIDI;
      addIDITagValue( strIDI, ID, idContainer.getId() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, FINDCONTAINER,
                         CND::BP_ERR_LIST_NOT_FOUND, strIDI );
   }
}

//******************************************************************************
void AbstractProcess::getContainerPtr( AbstractListDetails &container,
                                       const BFContainerId& idContainer,
                                       const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETCONTAINERPTR );

   void *rpPtr = getPtrForContainer( idContainer, idDataGroup );

   SEVERITY sevRtn = GETCURRENTHIGHESTSEVERITY();

   if( sevRtn > WARNING )
   {
      // Convert condition to exception & throw
      // We are temporarily recreating condition here because ConditionException
      // doesn't support constructor with Condition

      if( CURRENTCONDITIONCOUNT() )
      {
         Condition *pCondition = GETCURRENTCONDITION( 0 );
         if( pCondition != NULL )
         {
            throw ConditionException( *pCondition );
         }
         else
         {
            THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETCONTAINERPTR, CND::BP_ERR_UNKNOWN_EXCEPTION ); 
         }
      }
   }

   container.setContainer( rpPtr );
}

//******************************************************************************

SEVERITY AbstractProcess::init2()
{
   EXECHISTI( I_( "init2(  )" ) );


   const BFDataGroupId* pIdParentDataGroup = &(BF::HOST);
   if( isModal() )
   {
      AbstractProcess *pParent = dynamic_cast< AbstractProcess *> (getParent());
      pIdParentDataGroup = pParent ? &(pParent->getDataGroupId()) : &(BF::HOST);
   }

   if( !bfutil::isServerContext() && setCommitDataGroupAsHost() )
   {
      pIdParentDataGroup = &(BF::HOST);
   }

   getDataGroupId().setParent( pIdParentDataGroup );


   // Remove duplicate Field IDs from field to container map so that end user
   // cannot try to access duplicate fields without container ID - all adds
   // should have been performed in constructor
   int count = _duplicateFieldIDs.size();

   for( int i = 0; i < count; i++ )
   {
      FIELDCONTAINERMAP::iterator iter = _fieldContainerMap.find( _duplicateFieldIDs[i] );

      if( iter != _fieldContainerMap.end() )
      {
         _fieldContainerMap.erase( iter );
      }
   }

   // Let subclass do init processing
   return(doInit());
}

//******************************************************************************

void AbstractProcess::resetChildContainers(
                                          const BFContainerId& idContainer
                                          )
{  // Set child container associated pointers to NULL
   CONTAINERS::iterator iter = _containers.begin();

   while( iter != _containers.end() )
   {
      AbstractListDetails &container = *( ( *iter ).second );

      if( container.getParentContainerID() == idContainer )
      {  // Recursively clear child container pointers
         setContainer( container.getContainerID(), NULL );
      }
      iter++;
   }
}

//******************************************************************************

bool AbstractProcess::setParentContainers(
                                         AbstractListDetails &container,
                                         const BFDataGroupId& idDataGroup
                                         )
{
   EXECHISTI( I_( "setParentContainers( AbstractListDetails &, const BFDataGroupId & )" ) );
   BFContainerId idCurrentContainer = BF::NullContainerId;
   BFContainerId idParentContainer = container.getParentContainerID();
   bool bRtn = false;

   for( ;; )
   {  // Find highest parent that is invalid
      if( idParentContainer.isValid() )
      {  // We have a parent
         AbstractListDetails &aContainer = findContainer( idParentContainer, idDataGroup );
         if( !aContainer.isContainerValid() )
         {  // We have an invalid parent - save this one and see if more parents
            idCurrentContainer = idParentContainer;
            idParentContainer = aContainer.getParentContainerID();
         }
         else
         {  // We have a valid parent, so we are done looking for invalid ones
            break;
         }
      }
      else
      {  // No more parents to check
         break;
      }
   }

   if( idCurrentContainer.isValid() )
   {  // We found the highest parent that needs setting
      AbstractListDetails &aContainer = findContainer( idCurrentContainer, idDataGroup );
      getContainerPtr( aContainer, idCurrentContainer, idDataGroup );
      bRtn = true;
   }

   return(bRtn);
}

bool AbstractProcess::isRepeatable( const BFContainerId& idContainer )
{
   AbstractListDetails &container = findContainer( idContainer, getDataGroupId() );
   return( container.isRepeatable() );
}

bool AbstractProcess::isContainerValid( const BFContainerId& idContainer )
{
   AbstractListDetails &container = findContainer( idContainer, getDataGroupId() );
   return( container.isContainerValid() );
}

const ClientLocale &AbstractProcess::getClientLocale() const
{
   return(getBFSession()->getClientLocale());
}

//******************************************************************************

void AbstractProcess::setIgnoreWarningsOnOk2( bool flag )
{
   bIgnoreWarningsOnOk2_ = flag;
}

//******************************************************************************


//******************************************************************************

bool AbstractProcess::isCurrentListItemDummy(
                                            GenericInterface *rpGICaller,
                                            const BFContainerId& idList
                                            )
{
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "isCurrentListItemDummy( GenericInterface *, const BFContainerId & )" ) );
   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      assert( hasProcessRun() );   // process should always run first
      AbstractListDetails &list = findContainer( idList, idDataGroup );

      return(list.isDummyCurrentItem( idDataGroup ));
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( SEH_Exception& seh ) 
   {
      DString strIDI;
      addIDITagValue( strIDI, I_( "INCIDENT_NUMBER" ), seh.getLogFile() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, ISCURRENTLISTITEMDUMMY, CND::BP_ERR_SEH_EXCEPTION, strIDI );
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, ISCURRENTLISTITEMDUMMY, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
void AbstractProcess::getFieldsInContainer(const BFContainerId& idContainer,
                                           FIELD_NAMES& containerFields) const
{
//   EXECHIST2( I_("AbstractProcess"), 
//              I_( "getFieldsInContainer( const BFContainerId &, FIELD_NAMES & )" ) );
   DString name;
   FIELDS_CONST_ITER iter = _fields.begin();
   while( iter != _fields.end() )
   {
      if( iter->second->getContainerID() == idContainer )
      {
         // some field name in the data dictionary contain space
         name = iter->second->getFieldName();
         containerFields.push_back( name.strip() );
      }
      ++iter;
   }
}

//******************************************************************************
// for api use
void AbstractProcess::setCurrentListItem( const GenericInterface *rpGICaller,
                                          const BFContainerId& idList,
                                          const BFData* pKeyInfo )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION,
                          CLASSNAME,
                          I_( "setCurrentListItem( GenericInterface *, long, const BFData * )" ) );
   const BFDataGroupId& idDataGroup = getDataGroupId();

   assert( hasProcessRun() );   // process should always run first
   AbstractListDetails &list = findContainer( idList, idDataGroup );

   if( list.isRepeatable() )
   {
      DString strKey;
      BFCBO *pBFCBO = dynamic_cast< BFCBO* >( reinterpret_cast< BFAbstractCBO* >( list.getContainer() ) );

      pBFCBO->getStrKey( strKey, pKeyInfo );

      if( list.setCurrentKey( strKey, idDataGroup ) )
      {  // Item changed so any child containers must be reset.
         if( list.hasChildren() )
         {
            resetChildContainers( idList );
         }
      }
   }
}

bool AbstractProcess::workSessionHasUpdates()
{
   BFWorkSession *bfWorkSession = getBFWorkSession();
   return(bfWorkSession && ( bfWorkSession->hasHostUpdates() || bfWorkSession->hasNonHostUpdates( ) ));
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfproc/AbstractProcess.cpp-arc  $
//
//   Rev 1.72   Feb 20 2009 14:48:32   purdyech
//ZTS Revision 6
//
//   Rev 1.71   Oct 22 2004 08:57:14   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.70   May 14 2004 16:12:50   SMITHDAV
//Removed "global data areas" from InterProcessData" and cleaned up the related interfaces. They are now in the BFSession objects.
//
//   Rev 1.69   Feb 18 2004 15:11:42   PURDYECH
//Added EXECHIST macros to execution history tracking
//
//   Rev 1.68   Feb 12 2004 12:19:10   PURDYECH
//Catch SEH_Exceptions and throw them as BP_ERR_SEH_EXCEPTION conditions.
//
//   Rev 1.67   Aug 12 2003 10:08:00   PURDYECH
//Added new logging method (bf::log::...)
//
//   Rev 1.66   May 26 2003 14:24:06   PURDYECH
//The ActionTypeOnOk2 mess has been replaced with the ValidationControl BFExecutionContext mess.
//
//   Rev 1.65   May 24 2003 14:56:40   PURDYECH
//Added getItemErrors and getItemErrorState
//
//   Rev 1.64   May 08 2003 15:32:46   PURDYECH
//Added console messages to be displayed whenever an AbstractProcess is created or destroyed.
//
//   Rev 1.63   May 01 2003 15:21:16   PURDYECH
//workSessionHasUpdates had inadvertent signature change.
//
//   Rev 1.62   May 01 2003 10:50:56   PURDYECH
//Added code to manipulate DataGroupId parentage in new (old?) style
//
//   Rev 1.61   Apr 24 2003 12:13:38   PURDYECH
//Cleanup.
//
//   Rev 1.60   Apr 23 2003 14:20:58   PURDYECH
//Added class member s_empty_ so that empty strings are easily available.
 * 
 *    Rev 1.59   Apr 01 2003 14:38:48   PURDYECH
 * Set parent datagroup appropriately in init2()
 * 
 *    Rev 1.58   Feb 12 2003 14:11:28   PURDYECH
 * ServerContext logic is now in bfutil namespace.
 * 
 *    Rev 1.57   Jan 14 2003 11:03:48   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.56   Jan 06 2003 16:43:06   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.55   Nov 27 2002 15:04:20   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.54   Oct 09 2002 17:40:48   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.53   Sep 19 2002 09:28:14   IVESPAUL
 * Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
 *
 *    Rev 1.52   Sep 03 2002 11:07:14   PURDYECH
 * Further BFFieldId fixes
 *
 *    Rev 1.51   Aug 29 2002 13:51:50   SMITHDAV
 * Condition split.
 *
 *    Rev 1.50   Aug 29 2002 12:51:10   SMITHDAV
 * ClientLocale and typed field changes.
 *
 *    Rev 1.49   Jul 05 2002 16:40:10   HSUCHIN
 * fix for the GUI NASU/COA
 *
 *    Rev 1.48   Jul 03 2002 15:53:26   SMITHDAV
 * Fix commit logic for server context.
 *
 *    Rev 1.47   05 Jun 2002 13:55:14   SMITHDAV
 * Fix grid refresh bug. Added trySetCurrentKey functions.
 *
 *    Rev 1.46   May 28 2002 12:16:12   PURDYECH
 * BFData Implementation - Phase II
 *
 *    Rev 1.45   22 May 2002 17:57:02   PURDYECH
 * BFData Implementation
 *
 *    Rev 1.44   Feb 25 2002 18:52:02   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 *
 *    Rev 1.43   Jan 04 2002 15:10:28   ROSIORUC
 * Added getCBOList method
 *
 *    Rev 1.42   Dec 05 2001 15:06:48   IVESPAUL
 * Merged 1.41.1.0 unto 1.42
 *
 *    Rev 1.41.1.0   Nov 09 2001 12:01:02   DINACORN
 * Temp. changes for PopUp conditions in FastGUI.
 *
 *    Rev 1.41   Oct 10 2001 08:54:32   IVESPAUL
 * removed assert so services/XML can return conditions normally.
 *
 *    Rev 1.40   Jul 27 2001 17:19:56   ROSIORUC
 * Modified getField() method in order to return from the
 * method even I have a  null pointer to container
 *
 *    Rev 1.39   26 Jul 2001 13:43:44   YINGZ
 * fix reset, cancel problems
 *
 *    Rev 1.38   Jul 05 2001 15:57:58   MCNABBGL
 * beautified source
 *
 *    Rev 1.37   04 Jul 2001 15:16:26   YINGZ
 * cleanup
 *
 *    Rev 1.36   29 Jun 2001 10:56:16   YINGZ
 * add canCancel to support cancel machenism
 *
 *    Rev 1.35   05 Jun 2001 11:40:58   HSUCHIN
 * fixed getErrors to check for User Session when field and container id is 0.
 *
 *    Rev 1.34   15 May 2001 15:39:54   YINGZ
 * data group id clean up
 *
 *    Rev 1.33   May 08 2001 11:16:08   FENGYONG
 * Add name for API
 *
 *    Rev 1.32   03 May 2001 14:03:12   SMITHDAV
 * Session management restructuring.
 *
 *    Rev 1.31   Apr 06 2001 12:06:32   YINGZ
 * make changes to datagroup
 *
 *    Rev 1.30   Mar 27 2001 13:57:20   YINGZ
 * add workSessionHasUpdates
 *
 *    Rev 1.29   Mar 23 2001 13:54:42   YINGZ
 * fix getGroupId for GUI
 *
 *    Rev 1.28   Feb 28 2001 15:41:14   YINGZ
 * make fireCrossEdit virtual and add parm lValidateGroup
 *
 *    Rev 1.27   Feb 22 2001 13:48:38   YINGZ
 * temp change getGroupID to meet api needs
 *
 *    Rev 1.26   Feb 16 2001 11:49:20   YINGZ
 * change isRepeatable to use getGroupID
 *
 *    Rev 1.25   Feb 06 2001 14:01:34   YINGZ
 * add another version of setCurrentListItem for api use
 *
 *    Rev 1.24   Jan 09 2001 13:25:40   YINGZ
 * delete setContainerValidationMode since it is not needed anymore
 *
 *    Rev 1.23   Dec 21 2000 11:10:10   YINGZ
 * add validate only
 *
 *    Rev 1.22   Dec 15 2000 13:44:32   YINGZ
 * add getFieldsInContainer, still the better way 8))
 *
 *    Rev 1.21   Dec 15 2000 10:33:16   YINGZ
 * remove getFieldsInContainer
 *
 *    Rev 1.20   Dec 13 2000 15:26:24   YINGZ
 * add getFieldsInContainer for xml
 *
 *    Rev 1.19   Dec 13 2000 13:24:32   KOVACSRO
 * Added isCurrentItemDummy()
 *
 *    Rev 1.18   Nov 30 2000 10:00:02   IVESPAUL
 * Promote conditions after confirmation process when in server context.
 *
 *    Rev 1.17   Nov 29 2000 17:27:58   WINNIE
 * add logic to pop up warning message
 *
 *    Rev 1.16   Nov 27 2000 13:18:38   VASILEAD
 * Added the prototype for setIgnoreWarningsOnOk2
 *
 *    Rev 1.15   Nov 27 2000 11:35:08   VASILEAD
 * Added setIgnoreWarningsOnOk2() to give the process a chance to not launch ConfirmationProcess if we got warnings in the validation
 *
 *    Rev 1.14   Nov 24 2000 10:06:10   DT24433
 * promote conditions if server context and doValidateAll failed
 *
 *    Rev 1.13   Nov 08 2000 20:01:50   DT24433
 * added name support for containers
 *
 *    Rev 1.12   Oct 31 2000 11:43:34   HERNANDO
 * In Ok2, Confirmation Dlg pops-up only on GUI update.
 *
 *    Rev 1.11   16 Aug 2000 11:48:42   PURDYECH
 * Added getAllErrors method to retrieve all errors for the caller, both field and object level.
 *
 *    Rev 1.10   Aug 16 2000 09:57:10   DINACORN
 * fix
 *
 *    Rev 1.9   Aug 15 2000 14:01:00   YINGZ
 * multi locale support
 *
 *    Rev 1.8   Aug 03 2000 21:06:52   IVESPAUL
 * Fixed AWD session trap correctly.
 *
 *    Rev 1.6   Aug 02 2000 15:31:32   BUZILA
 * "locale" changes
 *
 *    Rev 1.5   Jun 23 2000 12:44:04   DT24433
 * changes to support setData
 *
 *    Rev 1.4   Apr 05 2000 14:53:44   DT24433
 * changed usage of GIContainer
 *
 *    Rev 1.3   Mar 23 2000 16:23:44   BUZILA
 * CBO filtering implemented
 *
 *    Rev 1.2   Mar 08 2000 16:21:54   YINGZ
 * add isRepeatable
 *
 *    Rev 1.1   Mar 01 2000 17:20:38   BUZILA
 * added doRegisterObserver and doDeRegister observer methods
 *
 *    Rev 1.0   Feb 15 2000 10:57:34   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.47   Jan 27 2000 11:52:48   DT24433
 * reset child containers during reset
 *
 *    Rev 1.46   Jan 26 2000 19:38:10   DT24433
 * check for TRXNS_ERROR parm and send message to calling dialog if on - basemaindlg handling
 *
 *    Rev 1.45   Jan 21 2000 07:17:28   DT24433
 * implemented doGetFieldAttributes
 *
 *    Rev 1.44   Jan 19 2000 15:36:08   DT24433
 * added getErrorState, doValidateAll & changed ok2
 *
 *    Rev 1.43   Jan 18 2000 14:11:42   DT24433
 * added safety check in ok2 in case WSD not created yet
 *
 *    Rev 1.42   Jan 12 2000 19:00:08   DT24433
 * added observer for CBO destruction
 *
 *    Rev 1.41   Jan 11 2000 17:21:56   DT24433
 * changed error handling in :ok2
 *
 *    Rev 1.40   Jan 11 2000 11:27:42   DT24433
 * changed to return bool for registerObserver
 *
 *    Rev 1.39   Jan 06 2000 12:09:58   DT24433
 * enabled getCrossEditFields call
 *
 *    Rev 1.38   Jan 05 2000 17:53:08   DT24433
 * added cross-edit & validation calls, removed read only group processing
 *
 *    Rev 1.37   Dec 23 1999 14:42:10   POPESCUS
 * do not fire off the confirmation if the process is used for support
 *
 *    Rev 1.36   Dec 22 1999 12:19:58   DT24433
 * parm changed in register/deregister
 *
 *    Rev 1.35   Dec 21 1999 13:43:52   DT24433
 * initial notification changes
 *
 *    Rev 1.34   Dec 17 1999 17:53:48   DT24433
 * changes to OK2 for new confirmation model
 *
 *    Rev 1.33   Dec 16 1999 18:30:12   VASILEAD
 * Commented out remove group id when reset
 *
 *    Rev 1.32   Dec 09 1999 11:25:40   DT24433
 * refresh support
 *
 *    Rev 1.31   Dec 08 1999 16:14:46   DT24433
 * added isCurrentListItemNew & changed commit processing
 *
 *    Rev 1.30   Dec 07 1999 10:27:44   DT24433
 * removed old doGet/SetField methods
 *
 *    Rev 1.29   Dec 03 1999 13:58:26   DT24433
 * added support to start processes off of child data group
 *
 *    Rev 1.28   Dec 02 1999 10:08:28   DT24433
 * removed ConfirmSave & setUpdateGroup
 *
 *    Rev 1.27   Dec 01 1999 15:21:42   DT24433
 * refresh child containers on deleteitem
 *
 *    Rev 1.26   Nov 30 1999 19:07:00   BUZILA
 * changes for metagroups
 *
 *    Rev 1.25   Nov 23 1999 17:02:56   DT24433
 * support getting container errors
 *
 *    Rev 1.24   Nov 22 1999 18:00:36   DT24433
 * performance improvements
 *
 *    Rev 1.23   Nov 20 1999 18:51:38   VASILEAD
 * temporary return in obsolete doGetField -> must be erased when we stop using it
 *
 *    Rev 1.22   Nov 20 1999 16:01:20   VASILEAD
 * temporary return in obsolete doGetField -> must be erased when we stop using it
 *
 *    Rev 1.21   Nov 19 1999 17:50:54   DT24433
 * do not getErrors if for HOST group for default case
 *
 *    Rev 1.20   Nov 19 1999 17:30:42   DT24433
 * added several doxxx methods and add group parm to doxxx methods
 *
 *    Rev 1.19   Nov 11 1999 08:54:00   DT24433
 * changed getFieldAttributes interface
 *
 *    Rev 1.18   Nov 09 1999 16:54:26   DT24433
 * group processing changes
 *
 *    Rev 1.17   Nov 05 1999 15:23:52   DT24433
 * added getErrors
 *
 *    Rev 1.16   Nov 02 1999 12:55:00   DT24433
 * fixed bug in getCBOItem to use real group instead of defaulting to BF::HOST
 *
 *    Rev 1.15   Nov 02 1999 12:43:08   DT24433
 * added group to getPtrForContainer, getCBOItem, and findContainer
 *
 *    Rev 1.14   Oct 28 1999 16:45:00   DT24433
 * added start of implementation for ok/cancel processing and commit method
 *
 *    Rev 1.13   Oct 28 1999 12:41:58   DT24433
 * add/delete/reset & group processing
 *
 *    Rev 1.12   Oct 25 1999 10:24:16   DT24433
 * changed return for getKeyForNewListItem
 *
 *    Rev 1.11   Oct 25 1999 10:03:32   DT24433
 * changed interface and implementation for getKeyForNewListItem
 *
 *    Rev 1.10   21 Oct 1999 08:43:54   HSUCHIN
 * Changes for better  support of getPtrForContainer and added getCBOItem.
 *
 *    Rev 1.9   Sep 17 1999 07:07:26   DT24433
 * initial group processing code
 *
 *    Rev 1.8   Sep 01 1999 17:24:06   DT24433
 * removed original doGetField/doSetField implementations
 *
 *    Rev 1.7   Aug 30 1999 18:06:16   DT24433
 * added new dosetfield/dogetfield methods
 *
 *    Rev 1.6   Aug 26 1999 11:09:12   DT24433
 * removed old functionality
 *
 *    Rev 1.5   Aug 06 1999 11:11:42   DT24433
 * add reset child list support
 *
 *    Rev 1.4   Aug 05 1999 15:20:52   DT24433
 * altered functionality
 *
 *    Rev 1.3   Aug 03 1999 14:25:52   DT24433
 * container changes
 *
 *    Rev 1.2   Jul 20 1999 11:13:28   VASILEAD
 * New conditions update
 *
 *    Rev 1.1   Jul 08 1999 10:01:44   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

