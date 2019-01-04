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
#include "ElementHandler.hpp"
#include "ElementHandlerFactory.hpp"
#include "CacheEnabledElementHandler.hpp"
#include "BatchHandler.hpp"
#include "SeverityAttribute.hpp"
#include "ConditionWriter.hpp"
#include "ExecutionResult.hpp"

#include <bfutil\ElementAttribute.hpp>
#include <bfutil\clientlocalecontext.hpp>

#include <bfproc\AbstractProcess.hpp>
#include <bfproc\CommandDispatcher.hpp>
#include <bfproc\bfcontainerid.hpp>

#include <ClientLocale.hpp>
#include <frame.hpp>


using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("ElementHandler");
   const I_CHAR * const ADD_HANDLER  = I_("addHandler");

   const DString STR_HIGHEST_SEVERITY = I_("HighestSeverity");
}

namespace CND
{
   extern const long ERR_ELEMENT_CANNOT_CONTAIN_CLASS;
}

namespace ELEMENT_NAME
{
   const I_CHAR * const BATCH                 = I_( "Batch" );
   const I_CHAR * const SUCCESSFUL            = I_( "Successful" );
};

//******************************************************************************
ElementHandler::ElementHandler( ElementHandler *parentHandler,
                                const DString &elementName,
                                ClassAttribute::ElementClass elementClass )
: _parentHandler(parentHandler)
, _cachingHandler(parentHandler->_cachingHandler)
, _elementName(elementName)
, _elementClass( elementClass, parentHandler->getElementClass() )
, _bIgnoreWarnings( parentHandler->_bIgnoreWarnings )
, _retry( parentHandler->_retry )
, _bWriteStats( parentHandler->_bWriteStats )
, _bVerboseConditions( parentHandler->_bVerboseConditions )
, _bFieldFormatting( parentHandler->_bFieldFormatting )
{
}

//******************************************************************************
ElementHandler::ElementHandler( const DString &elementName )
: _parentHandler( NULL )
, _cachingHandler(NULL)
, _elementName(elementName)
, _elementClass()
, _bIgnoreWarnings( true )
, _bWriteStats( false )
, _bVerboseConditions( false )
, _bFieldFormatting( true )
, _retry ( true )
{
}

//******************************************************************************
ElementHandler::~ElementHandler()
{
}

//******************************************************************************
ElementHandler *ElementHandler::createChildHandler( const DString &elementName, xercesc::AttributeList &attributes )
{

   if( elementName == ELEMENT_NAME::BATCH )
   {
      BatchHandler *handler = new BatchHandler( this, elementName, attributes );
      addHandler( handler );
      return(handler);
   }
   else
   {
      switch( ClassAttribute( attributes, _elementClass ) )
      {
         
         case ClassAttribute::PARM:
            {
               ParmHandler *handler = new ParmHandler( this, elementName, attributes );
               addHandler( handler );
               return(handler);
            }

         case ClassAttribute::PROCESS:
            {
               ProcessHandler *handler = ElementHandlerFactory::getInstance()->createProcessHandler( this, elementName, attributes );
               if( handler == NULL )
               {
                  handler = new ProcessHandler( this, elementName, attributes );
               }

               addHandler( handler );
               return(handler);
            }

         case ClassAttribute::CBO:
            {
               CBOHandler *handler = ElementHandlerFactory::getInstance()->createCBOHandler( this, elementName, attributes );
               if( handler == NULL )
               {
                  handler = new CBOHandler( this, elementName, attributes, _bFieldFormatting );
               }

               addHandler( handler );
               return(handler);
            }

         case ClassAttribute::KEY:
            {
               KeyHandler *handler = new KeyHandler( this, elementName );
               addHandler( handler );
               return(handler);
            }

         case ClassAttribute::FIELD:
            {
               FieldHandler *handler = new FieldHandler( this, elementName, attributes, _bFieldFormatting );
               addHandler( handler );
               return(handler);
            }

         default:
            assert(0); // internally inconsistant
            throw;

      }
   }
}

//******************************************************************************
void ElementHandler::addHandler( ParmHandler *handler )
{
   DString strIDI;
   addIDITagValue( strIDI, I_("CLASS"), I_("parm") );
   addIDITagValue( strIDI, I_("ELEMENT"), getName() );

   THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, ADD_HANDLER, CND::ERR_ELEMENT_CANNOT_CONTAIN_CLASS, strIDI );
}

//******************************************************************************
void ElementHandler::addHandler( BatchHandler *handler )
{
   DString strIDI;
   addIDITagValue( strIDI, I_("CLASS"), I_("batch") );
   addIDITagValue( strIDI, I_("ELEMENT"), getName() );

   THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, ADD_HANDLER, CND::ERR_ELEMENT_CANNOT_CONTAIN_CLASS, strIDI );
}

//******************************************************************************
void ElementHandler::addHandler( ProcessHandler *handler )
{
   DString strIDI;
   addIDITagValue( strIDI, I_("CLASS"), I_("process") );
   addIDITagValue( strIDI, I_("ELEMENT"), getName() );

   THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, ADD_HANDLER, CND::ERR_ELEMENT_CANNOT_CONTAIN_CLASS, strIDI );
}

//******************************************************************************
void ElementHandler::addHandler( CBOHandler *handler )
{
   DString strIDI;
   addIDITagValue( strIDI, I_("CLASS"), I_("cbo") );
   addIDITagValue( strIDI, I_("ELEMENT"), getName() );

   THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, ADD_HANDLER, CND::ERR_ELEMENT_CANNOT_CONTAIN_CLASS, strIDI );
}

//******************************************************************************
void ElementHandler::addHandler( KeyHandler *handler )
{
   DString strIDI;
   addIDITagValue( strIDI, I_("CLASS"), I_("key") );
   addIDITagValue( strIDI, I_("ELEMENT"), getName() );

   THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, ADD_HANDLER, CND::ERR_ELEMENT_CANNOT_CONTAIN_CLASS, strIDI );
}

//******************************************************************************
void ElementHandler::addHandler( FieldHandler *handler )
{
   DString strIDI;
   addIDITagValue( strIDI, I_("CLASS"), I_("field") );
   addIDITagValue( strIDI, I_("ELEMENT"), getName() );

   THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, ADD_HANDLER, CND::ERR_ELEMENT_CANNOT_CONTAIN_CLASS, strIDI );
}

//******************************************************************************
void ElementHandler::writeParm( const DString &name, const DString& value, BFDocument &out )
{
   ElementWriter::write( out,
                         name,
                         ClassAttribute( ClassAttribute::PARM, _elementClass ),
                         value );
}

//******************************************************************************
void ElementHandler::writeField( const DString &name, const DString& value, BFDocument &out )
{
   ElementWriter::write( out,
                         name,
                         ClassAttribute( ClassAttribute::FIELD, _elementClass ),
                         value );
}

//******************************************************************************
void ElementHandler::writeField( const BFFieldId &id, AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out )
{
//CP20030410   const BFDataFieldProperties* pProps = BFDataFieldProperties::get( id );
   DString fieldname( id.getName() );

   DString str;
   process->getField( process, idContainer, id, str, _bFieldFormatting );

   writeField( fieldname, str, out );
}

//******************************************************************************
void ElementHandler::writeField( const BFData& data, const BFFieldId &id, AbstractProcess *process, BFDocument &out )
{
//CP20030410   const BFDataFieldProperties* pProps = BFDataFieldProperties::get( id );
   DString fieldName( id.getName() );

   DString str;
   data.getElementValue( id, str, BFDataField::USE_MASK | BFDataField::USE_SUBSTITUTES );

   writeField( fieldName, str, out );
}

//******************************************************************************
void ElementHandler::writeHighestSeverity( SEVERITY severity, BFDocument &out )
{
   ElementWriter::write( out,STR_HIGHEST_SEVERITY, SeverityAttribute(severity) );
}

//******************************************************************************
void ElementHandler::writeCondition( const Condition& condition, BFDocument &out, ExecResult &result )
{
   ConditionWriter( condition, out, _bVerboseConditions ).writeBody();
   result.incrementConditionCount( condition.getSeverity() );
}

//******************************************************************************
void ElementHandler::writeConditions( Frame *frame, BFDocument &out, ExecResult &result )
{
   ConditionManager *rpCM = ConditionManager::getInstance();
   SEVERITY svr = rpCM->getMaxSeverity( frame, TRUE );

   if( svr == NO_CONDITION ) return;

   frame->packConditions();
   int count = frame->getCount(  );
   if( count <= 0 )
   {  // Severity without condition ?????
      assert( 0 );
      // Might want to output something here
      return;
   }
   // Add error/warning to XML
   Condition *cnd;

   for( int i = 0; i < count; i++ )
   {
      cnd = frame->getCondition( i );
      assert( cnd );
      cnd->prepareMessage( ClientLocaleContext::get() );
      writeCondition( *cnd, out, result );
   }

}

//******************************************************************************
void ElementHandler::writeConditions( const CONDITIONVECTOR& cv, BFDocument &out, ExecResult &result )
{
   ConditionManager *rpCM = ConditionManager::getInstance();

   CONDITIONVECTOR::const_iterator iter = cv.begin();

   for( ; iter != cv.end(); ++iter )
   {
      Condition *cnd = (*iter);
      cnd->prepareMessage( ClientLocaleContext::get() );
      writeCondition( *cnd, out, result );
   }

}

//******************************************************************************
void ElementHandler::cachePut( const DString &text )
{
   cachePut( _elementName, text );
}

//******************************************************************************
void ElementHandler::cachePut( const DString &name, const DString &text )
{
   assert( _cachingHandler );
   _cachingHandler->setToCache( name, text );
}

//******************************************************************************
const DString &ElementHandler::cacheGet() const
{
   return(cacheGet( _elementName ));
}

//******************************************************************************
const DString &ElementHandler::cacheGet( const DString &name ) const
{
   assert( _cachingHandler );
   return(_cachingHandler->getFromCache( name ));
}

//******************************************************************************
ElementHandler::Writer::Writer( const ElementHandler& handler, BFDocument &out )
: ElementWriter( out, handler )
, handler_( handler )
{
//   ElementAttributeList attributes;
//   out_.writeElementStart( handler_->_elementName, handler_->getAttributes(attributes) );
}

//******************************************************************************
ElementHandler::Writer::~Writer()
{
   writeText( handler_.getText() );
}

//******************************************************************************
ElementHandler::StatusWriter::StatusWriter( BFDocument &out, ExecResult &result )
: out_(out)
, result_( result )
, success_(false)
{
}

//******************************************************************************
ElementHandler::StatusWriter::~StatusWriter()
{
   result_.setSuccessful( success_ );
   ElementWriter::write( out_, ELEMENT_NAME::SUCCESSFUL,
                      success_?I_("yes"):I_("no") );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/ElementHandler.cpp-arc  $
//
//   Rev 1.29   Nov 10 2005 18:00:08   FENGYONG
//Incident 386579 - Add attribute to API batch level
//
//   Rev 1.28   Feb 01 2005 14:59:42   smithdav
//Minor ExecutionResult fixes and tweeks. 
//
//   Rev 1.27   Jan 27 2005 15:48:30   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.26   Oct 22 2004 09:06:38   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.25   Mar 09 2004 11:00:44   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.24   Mar 05 2004 13:28:26   SMITHDAV
//Fix stupid class initialization bugs.
//
//   Rev 1.23   Mar 02 2004 10:56:18   SMITHDAV
//Change element writers to make them mor robust.
// 
//    Rev 1.22   Apr 10 2003 10:51:46   PURDYECH
// Use BFFieldId::getName() instead of BFDataFieldProperties::getName() to get field names
// 
//    Rev 1.21   Jan 15 2003 14:40:20   PURDYECH
// Fixed a small iteration bug in the ConditionWriter method 
// 
//    Rev 1.20   Jan 06 2003 17:00:42   PURDYECH
// Sync back to Dave's changes for Process Initiation
// 
//    Rev 1.18.1.0   Dec 18 2002 11:23:04   SMITHDAV
// Fixed Process initiation error problem.
// 
//    Rev 1.18   Oct 09 2002 17:43:14   PURDYECH
// New PVCS Database
// 
//    Rev 1.17   Sep 25 2002 09:21:22   IVESPAUL
// Write out all conditions not just > WARNING.
//
//    Rev 1.16   Sep 23 2002 19:20:44   IVESPAUL
// Added 'Successful' Element.
//
//    Rev 1.15   Sep 19 2002 09:28:34   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//    Rev 1.14   Sep 18 2002 13:08:16   IVESPAUL
// Support for EMPTY/NULL containers from the process layer and
// support for formatting CBO fields when fetching all fields from a CBO/Container.
//
//    Rev 1.13   Sep 03 2002 18:03:50   IVESPAUL
// Added "Package Level" attribute fieldFormatting, default is 'yes'.
//
//    Rev 1.12   Aug 29 2002 12:57:38   SMITHDAV
// ClientLocale and typed field changes.
//
//    Rev 1.11   Aug 14 2002 12:17:04   SMITHDAV
// Fix class attribute defaulting logic.
//
//    Rev 1.10   Aug 02 2002 17:13:40   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//    Rev 1.9   Jul 05 2002 11:31:58   PURDYECH
// Include file fixups
//
//    Rev 1.8   Jul 04 2002 16:09:08   SMITHDAV
// Class attribute changes.
//
//    Rev 1.7   Jun 14 2002 17:59:36   SMITHDAV
// Restored activity tracking code.
//
//    Rev 1.6   07 Jun 2002 17:08:58   SMITHDAV
// Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//    Rev 1.5   07 Jun 2002 10:55:28   SMITHDAV
// Sync-up with Chris' changes.
//
//    Rev 1.4   16 May 2002 11:55:44   SMITHDAV
// Process changes to add xp::WorkSessionProcess
// and xp::UserSessionProcess classes and make
// top level process modeless.
//
//    Rev 1.3   14 May 2002 16:42:54   SMITHDAV
// put xparser code namespace xp.
//
//    Rev 1.2   01 May 2002 17:16:48   SMITHDAV
// Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//    Rev 1.1   30 Apr 2002 11:55:12   SMITHDAV
// Add support for field writing and sub-class field writing.
//
//    Rev 1.0   02 Apr 2002 13:50:04   SMITHDAV
// Initial revision.
 *
 */
