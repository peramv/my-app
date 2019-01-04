#pragma once

#include <DString.hpp>
#include <xercesc\dom\domdocument.hpp>
#include <xercesc\dom\domelement.hpp>
#include <xercesc\dom\domxpathresult.hpp>
#include <xercesc\parsers\xercesdomparser.hpp>
#include <xercesc\sax\errorhandler.hpp>
#include <xercesc\sax\saxparseexception.hpp>
#include <xercesc\util\platformutils.hpp>
#include <xercesc\framework\MemBufInputSource.hpp>

// Import/Export resolution
#undef IFASTDBRKR_LINKAGE
#ifdef IFASTDBRKR_DLL
   #define IFASTDBRKR_LINKAGE CLASS_EXPORT
#else
   #define IFASTDBRKR_LINKAGE CLASS_IMPORT
#endif

class IFASTDBRKR_LINKAGE SonicFrameworkError {
   class ErrorHandler : public xercesc::ErrorHandler {
   public:
      virtual void warning(const xercesc::SAXParseException& exc) {
      }
      virtual void error(const xercesc::SAXParseException& exc) {
      }
      virtual void fatalError(const xercesc::SAXParseException& exc) {
         throw exc;
      }
      virtual void resetErrors() {
      }
   };

private:
   xercesc::DOMDocument*   doc_;
   xercesc::DOMElement*    rootElem_;
   const char*             pszDelimiter_;

public:
   SonicFrameworkError( const std::string& str, const char* pszDelimiter )
   : rootElem_( NULL )
   , doc_( NULL )
   , pszDelimiter_( pszDelimiter )
   {
     init( str );
   }

   void init( const std::string& str );

   static DString Errorize( int code, 
                            const DStringA& dstr, 
                            const char* pszDelimiter,
                            const std::string& exception = "", 
                            const std::string& details = "" );

   DStringA getErrorMessage( void );

   bool getTextForPath(const std::wstring &pathName, std::wstring& configText ) const {
      return getElementText( getElementForPath( pathName ), configText );
   }

   bool getTextForPath(const std::wstring &pathName, std::string& configText ) const {
      return getElementText( getElementForPath( pathName ), configText );
   }

   xercesc::DOMElement* getElementForPath( const std::wstring &pathName ) const {
      return getElementForPath( pathName, rootElem_ );
   }

   bool getTextForPath(const std::wstring &pathName, xercesc::DOMElement *parentElem, std::wstring& configText) {
      return getElementText( getElementForPath( pathName, parentElem ), configText );
   }

   bool getTextForPath(const std::wstring &pathName, xercesc::DOMElement *parentElem, std::string& configText) {
      return getElementText( getElementForPath( pathName, parentElem ), configText );
   }

   static xercesc::DOMElement* getElementForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem );
   static xercesc::DOMElement* getElementFirstChild(const std::wstring &childName, xercesc::DOMElement *parentElem);
   static xercesc::DOMElement* getElementNextSibling(const std::wstring &siblingName, xercesc::DOMElement *inSiblingElem );
   static bool getElementText(xercesc::DOMElement *elem, std::wstring& configText);
   static bool getElementText(xercesc::DOMElement *elem, std::string& configText);

};

