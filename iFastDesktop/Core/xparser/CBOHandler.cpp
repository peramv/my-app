/*******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 *
*******************************************************************************/
#include "stdafx.h"
#include "Process.hpp"
#include "CBOHandler.hpp"
#include "ClassAttribute.hpp"
#include "ConditionWriter.hpp"
#include "TxnStatWriter.hpp"
#include "ExecutionResult.hpp"

#include <bfdata\bffieldid.hpp>
#include <bfproc\AbstractProcess.hpp>

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("CBOHandler");
}

namespace CND
{
   extern const long ERR_MULTIPLE_KEYS_NOT_ALLOWED;
   extern const long ERR_KEY_NOT_SPECIFIED_FOR_LIST;
   extern const long ERR_KEY_SPECIFIED_FOR_NONLIST;
   extern const long ERR_CBO_NOT_FOUND_FOR_KEY;
   extern const long ERR_CBO_NOT_DEFINED;
}

//******************************************************************************
CBOHandler::CBOHandler( ElementHandler *parentHandler,
                        const DString &elementName,
                        xercesc::AttributeList &attributes,
                        bool bFieldFormatting /* = false */ )
: ElementHandler( parentHandler, elementName, ClassAttribute::CBO )
, _action( attributes )
, _recordCount( attributes )
, _echoFields( I_("echoFields"), attributes, false )
, _bFieldFormatting( bFieldFormatting )
, _keyHandler( NULL )
, _fieldList()
, _cboList()
{
}

//******************************************************************************
void CBOHandler::execute( AbstractProcess *process, RADocument &out, ProcessResult &result )
{

   result.incrementCBOActionCount(_action);
   const BFContainerId& idContainer = process->getContainerID( getName() );

   if( !idContainer.isValid() )
   {
      THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, I_("execute"), CND::ERR_CBO_NOT_DEFINED );
   }

   switch( _action )
   {
      case CBO_ACTION_QUERY:
         if( _recordCount == RecordCountAttribute::RCT_ALL_RECORDS )
         {
            executeQueryAll( process, idContainer, out, result );
         }
         else
         {
            executeQuery( process, idContainer, out, result );
         }
         break;

      case CBO_ACTION_ADD:
         executeAdd( process, idContainer, out, result );
         break;

      case CBO_ACTION_UPDATE:
         executeUpdate( process, idContainer, out, result );
         break;

      case CBO_ACTION_DELETE:
         if( _recordCount == RecordCountAttribute::RCT_ALL_RECORDS )
         {
            executeDeleteAll( process, idContainer, out, result );
         }
         else
         {
            executeDelete( process, idContainer, out, result );
         }
         break;

      case CBO_ACTION_REPLACE:
         executeReplace( process, idContainer, out, result );
         break;

//   case CBO_ACTION_PROPERTIES:
//      executePropeties( process, idContainer, out, result );
//      break;
   }

}

//******************************************************************************
void CBOHandler::executeQuery( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result )
{
   Writer writer( *this, out );
   ElementTimeWriter timeWriter( out, !writeStats() );

   if( !executeKeyLookup( process, idContainer, out ) )
      THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, I_("executeUpdate"), CND::ERR_CBO_NOT_FOUND_FOR_KEY );

   if( process->isContainerValid( idContainer ) )
   {
      executeCurrentQueryItem( process, idContainer, out, result );
   }
}

//******************************************************************************
void CBOHandler::executeQueryAll( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result )
{

   if( !process->isRepeatable(idContainer) )
   {
      Writer writer( *this, out );
      ElementTimeWriter timeWriter( out, !writeStats() );
      executeCurrentQueryItem( process, idContainer, out, result );
   }
   else if( NULL_STRING != process->getFirstListItemKey( process, idContainer ) )
   {
      do
      {
         Writer writer( *this, out );
         ElementTimeWriter timeWriter( out, !writeStats() );

         executeCurrentQueryItem( process, idContainer, out, result );

      } while( NULL_STRING != process->getNextListItemKey( process, idContainer ) );
   }

}

//******************************************************************************
void CBOHandler::executeCurrentQueryItem( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result )
{
   if( _fieldList.size() > 0 )
   {
      // get selected fields
      _fieldList.executeGet( process, idContainer, out );
   }
   else
   {
      // get all fields
      FIELD_NAMES fieldNames;
      process->getFieldsInContainer( idContainer, fieldNames );

      for( FIELD_NAMES::iterator fieldNameIter = fieldNames.begin();
         fieldNameIter != fieldNames.end();
         ++fieldNameIter )
      {
         DString value;
         process->getField( process, idContainer, BFFieldId::getId( *fieldNameIter ), value, _bFieldFormatting );
         writeField( *fieldNameIter, value, out );
      }

   }
   _cboList.execute( process, out, result );
}

//******************************************************************************
void CBOHandler::executeAdd( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result )
{
   Writer writer( *this, out );
   ElementTimeWriter timeWriter( out, !writeStats() );

   if ( process->isContainerValid( idContainer ) )
   {
      if ( process->isRepeatable( idContainer ) )
      {
         process->setCurrentListItem( process,
                                      idContainer,
                                      process->getKeyForNewListItem( process, idContainer ) );
      }

      if ( _keyHandler != NULL )
      {
         _keyHandler->executeSet( process, idContainer, out );
      }
      if ( _echoFields ) {
         _fieldList.executeSet( process, idContainer, out );
      } else {
         _fieldList.executeSet( process, idContainer );
      }

      _docPos =  out.tellPosition(); // store the current doc position
      writeFields( _action, process, idContainer, out );

      _cboList.execute( process, out, result );

      validate( process, idContainer, out, result );
   }
}

//******************************************************************************
void CBOHandler::executeUpdate( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result )
{
   Writer writer( *this, out );
   ElementTimeWriter timeWriter( out, !writeStats() );

   if( !executeKeyLookup( process, idContainer, out ) )
      THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, I_("executeUpdate"), CND::ERR_CBO_NOT_FOUND_FOR_KEY );

   if ( _echoFields ) {
      _fieldList.executeSet( process, idContainer, out );
   } else {
      _fieldList.executeSet( process, idContainer );
   }

   _docPos =  out.tellPosition(); // store the current doc position
   writeFields( _action, process, idContainer, out );

   _cboList.execute( process, out, result );

   validate( process, idContainer, out, result );
}

//******************************************************************************
void CBOHandler::executeDelete( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result )
{
   Writer writer( *this, out );
   ElementTimeWriter timeWriter( out, !writeStats() );

   if( !executeKeyLookup( process, idContainer, out ) )
      THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, I_("executeDelete"), CND::ERR_CBO_NOT_FOUND_FOR_KEY );

   process->deleteItemFromList( process, idContainer );

}

//******************************************************************************
void CBOHandler::executeDeleteAll( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result )
{
   Writer writer( *this, out );
   ElementTimeWriter timeWriter( out, !writeStats() );

   while( NULL_STRING != process->getFirstListItemKey( process, idContainer ) )
   {
      process->deleteItemFromList( process, idContainer );
   }
}

//******************************************************************************
void CBOHandler::executeReplace( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result )
{
   Writer writer( *this, out );
   ElementTimeWriter timeWriter( out, !writeStats() );

   if( executeKeyLookup( process, idContainer, out ) )
   {
      process->deleteItemFromList( process, idContainer );
   }

   process->setCurrentListItem( process,
                                idContainer,
                                process->getKeyForNewListItem( process, idContainer ) );

   if( _keyHandler != NULL )
   {
      _keyHandler->executeSet( process, idContainer );
   }
   if ( _echoFields ) {
      _fieldList.executeSet( process, idContainer, out );
   } else {
      _fieldList.executeSet( process, idContainer );
   }

   _docPos =  out.tellPosition(); // store the current doc position
   writeFields( _action, process, idContainer, out );

   _cboList.execute( process, out, result );

   validate( process, idContainer, out, result );
}

//******************************************************************************
bool CBOHandler::executeKeyLookup( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out )
{

   if( _keyHandler != NULL )
   {  // key specified... mut be a list
      if( !process->isRepeatable(idContainer) )
         THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, I_("executeKey"), CND::ERR_KEY_SPECIFIED_FOR_NONLIST );

      return(_keyHandler->executeLookup( process, idContainer, out ));
   }
   else if( process->isRepeatable(idContainer) )
   {  // repeatable container, no key... should not be more than one item
      if( process->getNumberOfItemsInList( process, idContainer ) > 1 ) {
         THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, I_("executeKey"), CND::ERR_KEY_NOT_SPECIFIED_FOR_LIST );
      }

      process->setCurrentListItem( process, idContainer, process->getFirstListItemKey( process, idContainer ) );
      return(true);
   }
   else
   {  // non-repeating, no key... ok
      return(true);
   }

}

//******************************************************************************
void CBOHandler::validate( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result )
{
   MAKEFRAMEAUTOPROMOTE2( CND::XPARSER_CONDITION, CLASSNAME, I_("validate") );

   process->fireCrossEdit( process, idContainer, ifds::NullFieldId );
   PROMOTECONDITIONS();

   SEVERITY severity = ConditionManager::getInstance()->getMaxSeverity( MYFRAME(), TRUE );

   writeHighestSeverity( severity, out );
   writeConditions( MYFRAME(), out, result );

   if( severity > WARNING || ( severity == WARNING && !ignoreWarnings() ) )
   {
      throw ElementFailure(this); // throw to batch level
   }

}

//******************************************************************************
void CBOHandler::writeCommitData( WorkSessionProcess &wsProcess, RADocument &out )
{
   switch( _action )
   {
      case CBO_ACTION_ADD:
      case CBO_ACTION_UPDATE:
      case CBO_ACTION_REPLACE:
         out.seekPosition( _docPos ); // restore doc position
         writeCommitFields( _action, wsProcess.getProcessImpl(), out );
         break;
      default:
         break;
   }

   _cboList.writeCommitData( wsProcess, out );
}

//******************************************************************************
void CBOHandler::addHandler( KeyHandler *handler )
{

   if( _keyHandler != NULL )
      THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, I_("addHandler"), CND::ERR_MULTIPLE_KEYS_NOT_ALLOWED );

   _keyHandler = handler;

}

//******************************************************************************
void CBOHandler::addHandler( FieldHandler *handler )
{
   _fieldList.add( handler );
}

//******************************************************************************
void CBOHandler::addHandler( CBOHandler *handler )
{
   _cboList.add( handler );
}

//******************************************************************************
ElementAttributeList &CBOHandler::getAttributes( ElementAttributeList &attributes ) const
{
   attributes.add( getElementClass() );
   attributes.add( _action );
   attributes.add( _recordCount );
   return(attributes);
}

//******************************************************************************
void CBOHandlerList::execute( AbstractProcess *process, RADocument &out, ProcessResult &result )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->execute( process, out, result );
      i++;
   }
}

//******************************************************************************
void CBOHandlerList::writeCommitData( WorkSessionProcess &wsProcess, RADocument &out )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->writeCommitData( wsProcess, out );
      i++;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/CBOHandler.cpp-arc  $
//
//   Rev 1.23   Apr 26 2005 11:34:00   smithdav
//Add boolean attribute to "echo" request fields in the response.
//
//   Rev 1.22   Feb 09 2005 10:47:50   smithdav
//WO#17173 - Fixed bug in which an error was raised if there is no key and there are zero items in list. Error should only be raised if > 1 items in list/
//
//   Rev 1.21   Jan 27 2005 15:48:14   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.20   May 14 2004 16:15:28   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.19   Mar 09 2004 11:00:26   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.18   Mar 05 2004 13:28:22   SMITHDAV
//Fix stupid class initialization bugs.
//
//   Rev 1.17   Aug 18 2003 14:17:34   PURDYECH
//In executeAdd make sure that the container is valid before adding elements to it.
//
//   Rev 1.16   Apr 28 2003 14:50:34   PURDYECH
//AbstractProcess::getFieldsInContainer has changed interface.
// 
//    Rev 1.15   Jan 06 2003 17:00:32   PURDYECH
// Sync back to Dave's changes for Process Initiation
// 
//    Rev 1.14   Jan 06 2003 16:47:22   PURDYECH
// BFContainerId changeover
// 
//    Rev 1.13   Oct 25 2002 14:56:38   SMITHDAV
// Move validation to the end of CBO execution (after doing contained cbo's)
// 
//    Rev 1.12   Oct 09 2002 17:43:10   PURDYECH
// New PVCS Database
// 
//    Rev 1.11   Sep 20 2002 18:05:06   IVESPAUL
// Handle query of all fields correctly.
//
//    Rev 1.10   Sep 18 2002 13:08:14   IVESPAUL
// Support for EMPTY/NULL containers from the process layer and
// support for formatting CBO fields when fetching all fields from a CBO/Container.
//
//    Rev 1.9   Aug 29 2002 12:57:38   SMITHDAV
// ClientLocale and typed field changes.
//
//    Rev 1.8   Aug 06 2002 17:23:32   FENGYONG
// fix for non list cbo
//
//    Rev 1.7   Aug 02 2002 17:13:38   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//    Rev 1.6   Jul 29 2002 15:12:40   SMITHDAV
// Fix validate() for cases where warning occur and ignoreWarnings is false.
//
//    Rev 1.5   Jul 05 2002 11:31:56   PURDYECH
// Include file fixups
//
//    Rev 1.4   07 Jun 2002 17:08:56   SMITHDAV
// Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//    Rev 1.3   14 May 2002 16:42:54   SMITHDAV
// put xparser code namespace xp.
//
//    Rev 1.2   01 May 2002 17:16:46   SMITHDAV
// Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//    Rev 1.1   30 Apr 2002 11:55:12   SMITHDAV
// Add support for field writing and sub-class field writing.
//
//    Rev 1.0   02 Apr 2002 13:50:00   SMITHDAV
// Initial revision.
 *
 */