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
#include "SaxStateManager.hpp"
#include "ElementHandlerFactory.hpp"
#include "ElementHandler.hpp"
#include "RootHandler.hpp"
#include "ExecutionResult.hpp"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SaxParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>

#include <bf/log/logstream.hpp>

#include <bfutil\bfhrtimer.hpp>

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("SaxStateManager");

   const I_CHAR *DEFAULT_PARSER_NAME = I_( "org.apache.xerces.parsers.SAXParser" );
   const I_CHAR *UTF16 = I_( "utf-16" );
   const I_CHAR *ISO88591 = I_( "ISO-8859-1" );
}

namespace CND
{
   extern const long ERR_INVALID_ROOT_ELEMENT_NAME;
   extern const long XP_REQUEST_UNPARSABLE;
   extern const long XP_UNKNOWN_EXCEPTION;
   extern const long XP_SAX_PARSE_EXCEPTION;
}

//******************************************************************************
SaxStateManager::SaxStateManager( ) 
: _parser()
, _rootHandler( NULL )
, _currentHandler( NULL )
, _time( 0 )
{
   _parser.setDocumentHandler( this );
   _parser.setErrorHandler( this );
   _parser.setValidationScheme( xercesc::SAXParser::Val_Never );
   _parser.setDoNamespaces( true );
}

//******************************************************************************
SaxStateManager::~SaxStateManager()
{
   delete _rootHandler;
}

//******************************************************************************
void SaxStateManager::parse( const xercesc::InputSource &input, DStringA &xmlOutStr, ExecutionResult &result )
{
   BFHRTimer t;

   try
   {
      try 
      {
         _parser.parse( input );
         if ( _rootHandler == NULL )
         {
            THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, I_("parse"), CND::XP_REQUEST_UNPARSABLE );
         }
      }
      catch(ConditionException&)
      {
         throw;
      }
      catch ( xercesc::SAXException &se )
      {
         DString strIDI;
         addIDITagValue( strIDI, I_("SAXMSG"), reinterpret_cast<const wchar_t*>(se.getMessage()) );
         THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, I_("parse"), CND::XP_SAX_PARSE_EXCEPTION, strIDI );
      }
      catch (...)
      {
         THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, I_("parse"), CND::XP_UNKNOWN_EXCEPTION );
      }         
   }
   catch(ConditionException &ce)
   {
      delete _rootHandler;

      _rootHandler = ElementHandlerFactory::getInstance()->createRootHandler();

      DString outStr;
      outStr.reserve( 1024 * 4 );
      _rootHandler->executeCondition( ce.getCondition(), BasicDocument( outStr ), result );
      xmlOutStr = outStr;

      delete _rootHandler;
      _rootHandler = NULL;

      return;

   }

   DString outStr;
   _rootHandler->execute( BasicDocument( outStr ), result );
   xmlOutStr = outStr;

   delete _rootHandler;
   _rootHandler = NULL;

   _time = t.elapsed();
}

//******************************************************************************
// Parse from memory   
void SaxStateManager::parse( const DStringA &xmlIn, DStringA &xmlOut, ExecutionResult &result )
{
   xercesc::MemBufInputSource buff( (const XMLByte*)xmlIn.c_str(), xmlIn.size(), reinterpret_cast<const XMLCh*>(I_( "MemBuff" )), false );
   parse( buff, xmlOut, result );
}

//******************************************************************************
// Parse from file
void SaxStateManager::parse( const DString &uri, DStringA &xmlOut, ExecutionResult &result )
{
   xercesc::LocalFileInputSource input( reinterpret_cast<const XMLCh*>(uri.c_str()) );
   parse( input, xmlOut, result );
}

// DocumentHandler overrides
//******************************************************************************
void SaxStateManager::startElement( const XMLCh *const name, xercesc::AttributeList &attributes )
{

   if( _rootHandler == NULL )
   {
       const wchar_t* pStr = ElementHandlerFactory::getInstance()->getRootElementName().c_str();
       if( pStr != (wchar_t*)name )
      {
         THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, CLASSNAME, CND::ERR_INVALID_ROOT_ELEMENT_NAME );
      }

      _rootHandler = ElementHandlerFactory::getInstance()->createRootHandler( attributes );
      _currentHandler = _rootHandler;
   }
   else
   {
//      _currentHandler = ElementHandlerFactory::getInstance()->createHandler( _currentHandler, name, attributes );
       DString dstrName((wchar_t*)name);
      _currentHandler = _currentHandler->createChildHandler( dstrName, attributes );
   }

}

//******************************************************************************
void SaxStateManager::characters( const XMLCh * const chars, const unsigned int length )
{
   if( _currentHandler )
   {
      _currentHandler->appendText( chars, length );
   }
}

//******************************************************************************
void SaxStateManager::endElement( const XMLCh * const name )
{
   if( _currentHandler )
      _currentHandler = _currentHandler->getParent();
   else
      assert(0);
}

// ErrorHandler methods
//******************************************************************************
void SaxStateManager::warning( const xercesc::SAXParseException &e )
{
   bf::log::LogStream ls( bf::log::xml );
   ls << bf::log::warning;
   ls << bf::log::endl << I_( "Warning at file " ) << e.getSystemId();
   ls << I_( ", line " ) << (int)e.getLineNumber();
   ls << I_( ", char " ) << (int)e.getColumnNumber();
   ls << bf::log::endl << I_( "  Message: " ) << e.getMessage() << bf::log::endlf;
}

//******************************************************************************
void SaxStateManager::error( const xercesc::SAXParseException &e )
{
   bf::log::LogStream ls( bf::log::xml );
   ls << bf::log::severe;
   ls << bf::log::endl << I_( "Error at file " ) << e.getSystemId();
   ls << I_( ", line " ) << (int)e.getLineNumber();
   ls << I_( ", char " ) << (int)e.getColumnNumber();
   ls << bf::log::endl << I_( "  Message: " ) << e.getMessage() << bf::log::endlf;

   throw e;
}

//******************************************************************************
void SaxStateManager::fatalError( const xercesc::SAXParseException &e )
{
   bf::log::LogStream ls( bf::log::xml );
   ls << bf::log::critical;
   ls << bf::log::endl << I_( "Fatal Error at file " ) << e.getSystemId();
   ls << I_( ", line " ) << (int)e.getLineNumber();
   ls << I_( ", char " ) << (int)e.getColumnNumber();
   ls << bf::log::endl << I_( "  Message: " ) << e.getMessage() << bf::log::endlf;

   throw e;
}

//******************************************************************************
//  Private methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/SaxStateManager.cpp-arc  $
//
//   Rev 1.24   Jan 27 2005 15:49:34   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.23   Sep 14 2004 13:46:56   SMITHDAV
//Add code to reject XML messages that are not well formed.
//
//   Rev 1.22   Mar 09 2004 11:01:26   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.21   Aug 12 2003 10:07:00   PURDYECH
//Added new logging method (bf::log::...)
// 
//    Rev 1.20   Jan 06 2003 16:47:46   PURDYECH
// BFContainerId changeover
// 
//    Rev 1.19   Oct 25 2002 14:54:16   SMITHDAV
// Fix error handling in case of parse failure.
// 
//    Rev 1.18   Oct 09 2002 17:43:22   PURDYECH
// New PVCS Database
// 
//    Rev 1.17   Aug 02 2002 17:13:42   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
// 
//    Rev 1.16   07 Jun 2002 17:08:58   SMITHDAV
// Add support for root level attributes to turn on statistics writing and verbose conditions.
// 
//    Rev 1.15   14 May 2002 16:43:00   SMITHDAV
// put xparser code namespace xp.
// 
//    Rev 1.14   02 Apr 2002 12:58:12   SMITHDAV
// Change the way XML processing is handled.
// 
//    Rev 1.13   Aug 28 2001 10:40:04   FENGYONG
// Add xparserException
// 
//    Rev 1.12   Aug 24 2001 16:18:10   FENGYONG
// pass message back to ecom when throw cnd 
// 
//    Rev 1.11   24 Jul 2001 20:09:34   PURDYECH
// Don't do buffer echoing when in non-debug mode.
// 
//    Rev 1.10   17 Jul 2001 11:36:12   PURDYECH
// Added some debugging code which compiles even into Release build!  I'll fix it later
// 
//    Rev 1.9   Feb 09 2001 16:46:56   YINGZ
// change name from saxstatefactory
// 
//    Rev 1.8   Feb 09 2001 14:13:28   YINGZ
// add dstxparser project
// 
//    Rev 1.7   Feb 05 2001 09:19:52   YINGZ
// do not use _isReusable
// 
//    Rev 1.6   Jan 30 2001 16:25:08   YINGZ
// for release
// 
//    Rev 1.5   Jan 25 2001 17:10:42   YINGZ
// for compilable
// 
//    Rev 1.4   Dec 08 2000 11:40:00   YINGZ
// performance tuning
// 
//    Rev 1.3   Dec 07 2000 15:45:28   YINGZ
// bug fixing
// 
//    Rev 1.2   Dec 07 2000 13:31:34   YINGZ
// check in for check out 8))
// 
//    Rev 1.1   Nov 08 2000 20:07:44   DT24433
// changed to delete state during endElement if appropriate, removeState is now private
// 
//    Rev 1.0   Nov 08 2000 13:18:46   YINGZ
// Initial revision.
 * 
 */