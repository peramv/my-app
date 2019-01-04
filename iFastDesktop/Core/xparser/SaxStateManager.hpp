#pragma once

#include <xercesc/parsers/saxparser.hpp>
#include <xercesc/sax/handlerbase.hpp>

// Import/Export resolution
#undef XPARSER_LINKAGE
#ifdef XPARSER_DLL
   #define XPARSER_LINKAGE CLASS_EXPORT
#else
   #define XPARSER_LINKAGE CLASS_IMPORT
#endif

namespace xp
{

   class ElementHandler;
   class RootHandler;
   class ExecutionResult;

   class XPARSER_LINKAGE SaxStateManager : public xercesc::HandlerBase 
   {
   public:
      SaxStateManager();
      virtual ~SaxStateManager();

      long getTime()
      {
         return(_time);
      }

      virtual void parse( const DStringA &xmlIn, DStringA &xmlOut, ExecutionResult &result );
      virtual void parse( const DString &uri, DStringA &xmlOut, ExecutionResult &result );

      // DocumentHandler overrides
      virtual void startElement( const XMLCh *const name, xercesc::AttributeList &attributes );
      virtual void characters( const XMLCh * const chars, const unsigned int length );
      virtual void endElement( const XMLCh * const name );

      // ErrorHandler methods
      virtual void warning( const xercesc::SAXParseException &e );
      virtual void error( const xercesc::SAXParseException &e );
      virtual void fatalError( const xercesc::SAXParseException &e );

   private:   
      void parse( const xercesc::InputSource &input, DStringA &xmlOut, ExecutionResult &result );

      xercesc::SAXParser _parser;

      RootHandler *_rootHandler;
      ElementHandler *_currentHandler;

      long _time;

   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/SaxStateManager.hpp-arc  $
//
//   Rev 1.11   Jan 27 2005 15:49:36   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.10   Mar 09 2004 11:01:28   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.9   Oct 09 2002 17:43:22   PURDYECH
//New PVCS Database
//
//   Rev 1.8   14 May 2002 16:44:14   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.7   02 Apr 2002 12:57:34   SMITHDAV
//Change the way XML processing is handled.
//
//   Rev 1.6   24 Jul 2001 20:10:22   PURDYECH
//Class is now exported.
//Added protected getWorkSet method to return the relevant workset.
//
//   Rev 1.5   Feb 09 2001 14:13:58   YINGZ
//add dstxparser project
//
//   Rev 1.4   Jan 30 2001 16:25:44   YINGZ
//for release
//
//   Rev 1.3   Jan 25 2001 17:09:18   YINGZ
//for compilable
//
//   Rev 1.2   Dec 08 2000 11:40:18   YINGZ
//performance tuning
//
//   Rev 1.1   Nov 08 2000 20:08:56   DT24433
//changed to delete state during endElement if appropriate, removeState is now private
//
//   Rev 1.0   Nov 08 2000 13:22:08   YINGZ
//Initial revision.
 * 
 */

